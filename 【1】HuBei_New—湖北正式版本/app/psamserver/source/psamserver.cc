#include <unistd.h>
#include<sys/types.h>
#include <zmq.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "logm.h"
#include "psamserver.h"
#include  <errno.h>
#include  <sys/ioctl.h>
#include <string.h>
#include <asm-generic/ioctl.h>
#include "bsp.h"



#define    CMD_ACTIVE           (0x00)
#define    CMD_DEACTIVE         (0x01)
#define    CMD_PROCESS          (0x02)
#define    CMD_CLKSET           (0x03)
#define    CMD_VOLTAGESET       (0x04)
#define    CMD_SETPPS_STATE     (0x05)
#define    CMD_SETETU_STATE     (0x06)
#define    MAX_WAIT_TIME        (0x8ab9)  /*about 200ms*/

unsigned int psam_WT_addr[4] = {0x81107, 0x81207, 0x81307, 0x81407};


using namespace std;


PsamDevice::PsamDevice()
{
    m_fd = -1;
}

PsamDevice::~PsamDevice()
{
     if(m_fd > 0)
    {
        close(m_fd);
    }
}


int PsamDevice::connect(unsigned char slot)
{
    char name[64];

    sprintf(name, "/dev/misc/drv_psam%d", slot);

    m_fd = open(name, O_RDWR);
    if(m_fd > 0)
    {
        printf("open psam %s success\n", name);
    }
    else
    {
        printf("open psam %s fail\n", name);
    }

    m_slot = slot;
    return 0;
}


int PsamDevice::active(unsigned char *atrLen, unsigned char *atr)
{
    int ret;

    ret = ioctl(m_fd, CMD_ACTIVE, atr);
    *atrLen = (ret == 0) ? 82 : 0;

    return ret;
}

int PsamDevice::disablePPS(void)
{
    unsigned char pps = 0;

    ioctl(m_fd, CMD_SETPPS_STATE, &pps);

    return 0;
}


int PsamDevice::exchangeApdu(unsigned char cmdLen, unsigned char *cmd, unsigned char *cmdAckLen, unsigned char *cmdAck)
{
    int ret;
    psam_exapdu_t apdu;

    apdu.slot = m_slot;
    apdu.cmd_len = cmdLen;
    memcpy(apdu.cmd, cmd, cmdLen);

    ret = ioctl(m_fd, CMD_PROCESS, &apdu);
    if((ret == 0) && (apdu.error_code == 0))
    {
        *cmdAckLen = apdu.ack_len;
        memcpy(cmdAck, apdu.ack, apdu.ack_len);
    }
    else
    {
        logm_debug("PsamDevice exchangeApdu fail %d, %08x\n", ret, apdu.error_code);
        ret = (int)apdu.error_code;
    }

    return ret;
}


PsamServer::PsamServer(int slot)
{
    int ret;
    char nameBuffer[20];

    m_ctx = zmq_init (1);
    if(NULL == m_ctx)
    {
        logm_debug("create context fail!\n");
        exit(-1);
    }

    m_repSocket = zmq_socket(m_ctx, ZMQ_REP);
    if(NULL == m_repSocket)
    {
        logm_debug("create m_repSocket fail!\n");
        exit(-1);
    }

    sprintf(nameBuffer, "tcp://*:%d", (7000 + slot));
    ret = zmq_bind(m_repSocket, nameBuffer);
    if(ret < 0)
    {
        logm_debug("bind m_repSocket fail\n");
        exit(-1);
    }

    m_slot = slot;

    m_device = new PsamDevice();
    m_device->connect(m_slot);

    return;
}

PsamServer::~PsamServer()
{
    delete m_device;
    zmq_close(m_repSocket);
}

void PsamServer::_preWork(void)
{
    int ret;
    unsigned char atrLen;
    unsigned char atr[128];
    unsigned char enter_df01[] = {0x00, 0xa4, 0x00, 0x00, 0x02, 0xdf, 0x01};
    unsigned char cardAck[256];
    unsigned char cardAckLen;

    //m_device->disablePPS();
    ret = m_device->active(&atrLen, atr);
    if((ret == 0) && (atr[8] == 0)
       && (atr[9] == 0) && (atr[10] == 0) && (atr[11] == 0))
    {
        ret = m_device->exchangeApdu(7, &enter_df01[0], &cardAckLen, cardAck);
        if(ret == 0)
        {
            logm_debug("psam %d prepare psam success\n", m_slot);
        }
        else
        {
            logm_err("psam %d exchangeApdu fail, ret:%08x cardAckLen:%d \n", m_slot+1, ret, cardAckLen);
        }
    }
    else
    {
        logm_err("psam %d active psam fail ret: %08x \n" , m_slot+1, ret);
        logm_debug_buffer(atr, 12);
    }

    /* set max wait time */
    bsp_fpga_write_reg(psam_WT_addr[m_slot], MAX_WAIT_TIME);

    return;
}
char PsamServer::_preWorkRest(void)
{
    unsigned char atrLen;
    unsigned char atr[128];
    int ret;
    char ret_code = 0;

    ret = m_device->active(&atrLen, atr);
    if((ret == 0) && (atr[8] == 0) && (atr[9] == 0) && (atr[10] == 0) && (atr[11] == 0))
    {
        logm_debug("psam_%d reset ok\n", m_slot + 1);
        ret_code = 0;
    }
    else
    {
        logm_debug("psam_%d reset failed, ret: %08x\n", m_slot + 1, ret);
        ret_code = -1;
    }

    /* set max wait time */
    bsp_fpga_write_reg(psam_WT_addr[m_slot], MAX_WAIT_TIME);

    return ret_code;
}

void PsamServer::coldReset(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    unsigned char atrLen;
    unsigned char atr[128];
    int ret;

    ack[0]= 0xe8;
    ret = m_device->active(&atrLen, atr);
    if((ret == 0) && (atr[8] == 0) && (atr[9] == 0) && (atr[10] == 0) && (atr[11] == 0))
    {
        logm_debug("psam_%d active ok: ", m_slot + 1);
        logm_debug_buffer(atr, atrLen);

        ack[1] = 0;
        ack[2] = atrLen;
        memcpy(&ack[3], atr, atrLen);
        *ack_len = atrLen + 3;
    }
    else
    {
        logm_debug("psam_%d active failed, ret: %08x\n", m_slot + 1, ret);

        ack[1] = 1;
        *ack_len = 2;
    }

    /* set max wait time */
    bsp_fpga_write_reg(psam_WT_addr[m_slot], MAX_WAIT_TIME);

    return;
}



void PsamServer::exchangeApdu(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[256];
    unsigned char cardAckLen;

    ack[0] = 0xe9;
    ret = m_device->exchangeApdu(command[1], &command[2], &cardAckLen, cardAck);
    if(ret == 0)
    {
        ack[1] = 0;
        ack[2] = cardAckLen;
        memcpy(&ack[3] , cardAck, cardAckLen);
        *ack_len = cardAckLen + 3;
    }
    else
    {
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
    }

    return;
}


void PsamServer::exchangeApduActive(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[256];
    unsigned char cardAckLen;

    ack[0] = 0xea;
    ret = m_device->exchangeApdu(command[1], &command[2], &cardAckLen, cardAck);
    if(ret == 0)
    {
        ack[1] = 0;
        ack[2] = cardAckLen;
        memcpy(&ack[3] , cardAck, cardAckLen);
        *ack_len = cardAckLen + 3;
    }
    else
    {
        ack[1] = 1;
        *ack_len = 2;
    }

    _preWork();
    return;
}


void PsamServer::calcCpcMac(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[64];
    unsigned char cardAckLen;
    unsigned char deliverkey[21];
    unsigned char calcmac[21];

    deliverkey[0] = 0x80;
    deliverkey[1] = 0x1a;
    deliverkey[2] = command[1]; /* cpc_key_usage */
    deliverkey[3] = command[2]; /* cpc_key_ID */
    if(command[1] == 0x28) /* delivery Level = 1 */
    {        
        deliverkey[4] = 0x08; /* cmd Data Length */
        memcpy(&deliverkey[5], &command[3], 8);

        logm_debug("Calc_mac_delivery: ");
        logm_debug_buffer(deliverkey, 13);
        
        ret = m_device->exchangeApdu(13, deliverkey, &cardAckLen, cardAck);        
    }
    else /* delivery Level = 2 */
    {
        deliverkey[4] = 0x10; /* cmd Data Length */
        memcpy(&deliverkey[5], &command[3], 16);

        logm_debug("Calc_mac_delivery: ");
        logm_debug_buffer(deliverkey, 21);        
        
        ret = m_device->exchangeApdu(21, deliverkey, &cardAckLen, cardAck);        
    }

    logm_debug("delivery_ack: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0) || (cardAckLen != 2) || (cardAck[0] != 0x90) || (cardAck[1] != 0x00))
    {
        ack[0] = 0xeb;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    calcmac[0] = 0x80;
    calcmac[1] = 0xfa;
    calcmac[2] = 0x00;
    calcmac[3] = 0x00;
    calcmac[4] = 0x10;
    memcpy(&calcmac[5], &command[19], 8);
    memset(&calcmac[13], 0, 8);

    logm_debug("cmd calc mac:");
    logm_debug_buffer(calcmac, 21);

    ret = m_device->exchangeApdu(21, calcmac, &cardAckLen, cardAck);
    
    logm_debug("CPC calc_mac ack: ");
    logm_debug_buffer(cardAck, cardAckLen);
    
    if((ret != 0) || (cardAckLen != 18) || (cardAck[cardAckLen-2] != 0x90) || (cardAck[cardAckLen-1] != 0x00))
    {
        ack[0] = 0xeb;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    ack[0] = 0xeb;
    ack[1] = 0x00;
    memcpy(&ack[2], &cardAck[0], 16);

    *ack_len = 18;
    return;
}


void PsamServer::calcObuMac(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[256];
    unsigned char cardAckLen;
    unsigned char deliverkey[21];
    unsigned char calcmac[13];

    deliverkey[0] = 0x80;
    deliverkey[1] = 0x1a;
    deliverkey[2] = 0x48;
    deliverkey[3] = 0x01;
    deliverkey[4] = 0x10;
    memcpy(&deliverkey[5], &command[1], 16);
    ret = m_device->exchangeApdu(21, deliverkey, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAckLen != 2)
       || (cardAck[0] != 0x90)
       || (cardAck[1] != 0x00))
    {
        ack[0] = 0xec;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    calcmac[0] = 0x80;
    calcmac[1] = 0xfa;
    calcmac[2] = 0x00;
    calcmac[3] = 0x00;
    calcmac[4] = 0x08;
    memcpy(&calcmac[5], &command[17], 8);
    ret = m_device->exchangeApdu(13, calcmac, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAckLen != 10)
       || (cardAck[8] != 0x90)
       || (cardAck[9] != 0x00))
    {
        ack[0] = 0xec;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    ack[0] = 0xec;
    ack[1] = 0x00;
    memcpy(&ack[2], cardAck, 8);

    *ack_len = 10;
    return;
}


void PsamServer::descryptVehicle(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAckLen;
    unsigned char key_version;
    unsigned char cipher_len;
    unsigned char vechile_len;
    unsigned char deliverkey[21];
    unsigned char cardAck[128];    
    unsigned char descrypt_vechicle[128];

    /* check command_Len */
    if(command_len <= 18)
    {
        ack[0] = 0xed;
        ack[1] = 1;
        *ack_len = 2;        
        return;
    }

    /* get descrypt key version */
    key_version = command[1];

    /* get cipher length: cmd_len - (cmd_tye(1byte) + keyVersion(1byte) + delivery_factor(16bytes) ) */
    cipher_len = command_len - 18;

    /* delivery key */
    deliverkey[0] = 0x80;
    deliverkey[1] = 0x1a;
    deliverkey[2] = 0x59;  /* key usage */
    deliverkey[3] = key_version;  /* key version */
    deliverkey[4] = 0x10;  /* LC */
    memcpy(&deliverkey[5], &command[2], 16);

    logm_debug("descryptVehicle_delivery: ");
    logm_debug_buffer(deliverkey, 21);

    ret = m_device->exchangeApdu(21, deliverkey, &cardAckLen, cardAck);

    logm_debug("delivery_ack: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0) || (cardAckLen != 2) || (cardAck[0] != 0x90) || (cardAck[1] != 0x00))
    {
        ack[0] = 0xed;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    /* descrypt vehicle infor */
    descrypt_vechicle[0] = 0x80;
    descrypt_vechicle[1] = 0xfa;
    descrypt_vechicle[2] = 0x80;
    descrypt_vechicle[3] = 0x00;
    descrypt_vechicle[4] = cipher_len; /* cipher length */
    memcpy(&descrypt_vechicle[5], &command[18], cipher_len);

    logm_debug("descryptVehicle cmd: ");
    logm_debug_buffer(descrypt_vechicle, cipher_len + 5);

    ret = m_device->exchangeApdu(cipher_len + 5, descrypt_vechicle, &cardAckLen, cardAck);

    logm_debug("descryptVehicle ack: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0) || (cardAck[cardAckLen - 2] != 0x90) || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xed;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    /* PSAM Descrypt Vehicle Note
    * (1) 3DES(RK2)-> Lenght(1Byte) + MAC(8Bytes) + Vehicle
    * (2) 3DES(RK2)-> Lenght(1Byte) + MAC(16Bytes) + Vehicle
    */

    /* ack vehicle infor */
    ack[0] = 0xed;
    ack[1] = 0x00;

    /* check key_version, 0x43->SM4, 0x03->3DES */
    if(key_version == 0x43)
    {
        /* calc vehicle_len = cardAckLen - mac_len - first - SW */
        vechile_len = cardAckLen - 19;

        /* jump length and MAC */
        memcpy(&ack[2], &cardAck[17], vechile_len);        
    }
    else
    {
        /* calc vehicle_len = cardAckLen - mac_len - first - SW */
        vechile_len = cardAckLen - 11;

        /* jump length and MAC */
        memcpy(&ack[2], &cardAck[9], vechile_len);
    }

    *ack_len  = 2 + vechile_len;

    return;
}
/* calc single_card OBU Access Creddentials */
void PsamServer::calcAccessCred(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[64];
    unsigned char cardAckLen;
    unsigned char deliverkey[21];
    unsigned char encrypt[21];

    deliverkey[0] = 0x80;
    deliverkey[1] = 0x1a;
    deliverkey[2] = 0x48; /* key usage: delivery_2, encrypt */
    deliverkey[3] = 0x4A; /* key identify: ETC AccessCred key_1 OPNK11 */
    deliverkey[4] = 0x10;
    memcpy(&deliverkey[5], &command[1], 16);

    logm_debug("calc_cred delivery: ");
    logm_debug_buffer(deliverkey, 21);

    ret = m_device->exchangeApdu(21, deliverkey, &cardAckLen, cardAck);
    
    logm_debug("delivery ack: ");
    logm_debug_buffer(cardAck, cardAckLen);
    
    if((ret != 0) || (cardAckLen != 2) || (cardAck[0] != 0x90) || (cardAck[1] != 0x00))
    {
        ack[0] = 0xe7;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    encrypt[0] = 0x80;
    encrypt[1] = 0xfa;
    encrypt[2] = 0x00;
    encrypt[3] = 0x00;
    encrypt[4] = 0x10;
    memcpy(&encrypt[5], &command[17], 8);
    memset(&encrypt[13], 0x00, 8);

    logm_debug("calcAccessCred cmd:");
    logm_debug_buffer(encrypt, 21);

    ret = m_device->exchangeApdu(21, encrypt, &cardAckLen, cardAck);

    logm_debug("calcAccessCred ack: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0) || (cardAckLen != 18) || (cardAck[cardAckLen - 2] != 0x90) || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xe7;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    ack[0] = 0xe7;
    ack[1] = 0x00;
    memcpy(&ack[2], &cardAck[0], 16);

    *ack_len  = 18;

    return;
}

void PsamServer::getRand(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
     int ret;
    unsigned char cardAck[16];
    unsigned char cardAckLen;
    unsigned char getrandom[5] = {0x00, 0x84, 0x00, 0x00, 0x08};    

    ret = m_device->exchangeApdu(5, getrandom, &cardAckLen, cardAck);
    
    logm_debug("getRand PSAM_ACK: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0) || (cardAckLen != 10) || (cardAck[cardAckLen-2] != 0x90) || (cardAck[cardAckLen-1] != 0x00))
    {
        ack[0] = 0xe6;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    ack[0] = 0xe6;
    ack[1] = 0x00;
    memcpy(&ack[2], &cardAck[0], 8);

    *ack_len  = 10;

    return;
}


//init SAM for purchase
void PsamServer::calcPurchaseMac1(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[32];
    unsigned char cardAckLen;
    unsigned char cmdData[42];

    cmdData[0] = 0x80;
    cmdData[1] = 0x70;
    cmdData[2] = 0x00;
    cmdData[3] = 0x00;
    cmdData[4] = 0x24;
    memcpy(&cmdData[5], &command[1], 0x24);
    cmdData[41] = 0x08;
    logm_debug("calcPurchaseMac1 cmd: ");
    logm_debug_buffer(cmdData, 42);

    ret = m_device->exchangeApdu(42, cmdData, &cardAckLen, cardAck);
    logm_debug("calcPurchaseMac1 PSAM_ACK: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0) || (cardAckLen != 10) || (cardAck[cardAckLen-2] != 0x90) || (cardAck[cardAckLen-1] != 0x00))
    {    
        ack[0] = 0xe5;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
    
    ack[0] = 0xe5;
    ack[1] = 0x00;
    memcpy(&ack[2], cardAck, 8);

    *ack_len = 10;
    
    return;
}


void PsamServer::authPurchaseMac2(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[4];
    unsigned char cardAckLen;
    unsigned char cmdData[10];

    cmdData[0] = 0x80;
    cmdData[1] = 0x72;
    cmdData[2] = 0x00;
    cmdData[3] = 0x00;
    cmdData[4] = 0x04;
    memcpy(&cmdData[5], &command[1], 4);
    logm_debug("authPurchaseMac2 cmd: ");
    logm_debug_buffer(cmdData, 9);
    

    ret = m_device->exchangeApdu(9, cmdData, &cardAckLen, cardAck);
    logm_debug("authPurchaseMac2 PSAM_ACK: ");
    logm_debug_buffer(cardAck, cardAckLen);
    if((ret != 0) || (cardAckLen != 2) || (cardAck[0] != 0x90) || (cardAck[1] != 0x00))
    {    
        ack[0] = 0xe4;
        ack[1] = 1;        
        memcpy(&ack[2], cardAck, 2);
        *ack_len = 4;
        _preWork();
        return;
    }

    memcpy(&ack[2], cardAck, 2); // auth MAC2 result 

    ack[0] = 0xe4;
    ack[1] = 0x00;
    *ack_len = 4;
    
    return;
}

void PsamServer::get_MF_random8(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[32];
    unsigned char cardAckLen;

#if 0
    unsigned char enter_mf[7];
    enter_mf[0] = 0x00;
	enter_mf[1] = 0xa4;
	enter_mf[2] = 0x00;
	enter_mf[3] = 0x00;
	enter_mf[4] = 0x02;
	enter_mf[5] = 0x3f;
	enter_mf[6] = 0x00;
    ret = m_device->exchangeApdu(7, enter_mf, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAck[cardAckLen - 2] != 0x90)
       || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xe3;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
#else
    /* reset psam */
    if(_preWorkRest() != 0)
    {
        ack[0] = 0xe3;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
#endif

    unsigned char getrandom[5] = {0x00, 0x84, 0x00, 0x00, 0x08};

    logm_debug("get_MF_random8 cmd: ");
    logm_debug_buffer(getrandom, 5);

    ret = m_device->exchangeApdu(5, getrandom, &cardAckLen, cardAck);

    logm_debug("get_MF_random8 ack: ");
    logm_debug_buffer(cardAck, cardAckLen);
    
    if((ret != 0) || (cardAck[cardAckLen - 2] != 0x90) || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xe3;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    ack[0] = 0xe3;
    ack[1] = 0x00;
    memcpy(&ack[2], cardAck, 8);

    *ack_len  = 10;

    return;
}

void PsamServer::psam_external_auth(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[32];
    unsigned char cardAckLen;    
    unsigned char cmd_exauth[14] = {0x00, 0x82, 0x00, 0x41, 0x08};

    memcpy(&cmd_exauth[5], &command[1], 8);
    //memcpy(&cmd_exauth[0], &command[1], 13);

    logm_debug("external_auth cmd: ");
    logm_debug_buffer(cmd_exauth, 13);

    ret = m_device->exchangeApdu(13, cmd_exauth, &cardAckLen, cardAck);

    logm_debug("external_auth ack: ");
    logm_debug_buffer(cardAck, cardAckLen);
    
    if(ret != 0)
    {
        /* cmd excute failed */
        ack[0] = 0xe2;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
    else
    {
        /* cmd excute successfully */
        ack[0] = 0xe2;
        ack[1] = 0;
        ack[2] = cardAck[0];
        ack[3] = cardAck[1];
        *ack_len = 4;
    }
    
    /* enter DF01 */
    unsigned char enter_df01[7] = {0x00, 0xa4, 0x00, 0x00, 0x02, 0xdf, 0x01};
    m_device->exchangeApdu(7, enter_df01, &cardAckLen, cardAck);
}

/*
void PsamServer::descryptVehicle_Key_delivery(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[256];
    unsigned char cardAckLen;
    unsigned char deliverkey[21];    

    deliverkey[0] = 0x80;
    deliverkey[1] = 0x1a;
    deliverkey[2] = 0x59;
    deliverkey[3] = 0x03;
    deliverkey[4] = 0x10;
    memcpy(&deliverkey[5], &command[1], 16);

    ret = m_device->exchangeApdu(21, deliverkey, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAckLen != 2)
       || (cardAck[0] != 0x90)
       || (cardAck[1] != 0x00))
    {
        ack[0] = 0xe3;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }    

    ack[0] = 0xe3;
    ack[1] = 0x00;    

    *ack_len  = 2;

    return;
}
*/
/*
void PsamServer::descryptVehicle_infor(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[256];
    unsigned char cardAckLen;
    unsigned char descrypt_vechicle[123];    

    descrypt_vechicle[0] = 0x80;
    descrypt_vechicle[1] = 0xfa;
    descrypt_vechicle[2] = 0x80;
    descrypt_vechicle[3] = 0x00;
    descrypt_vechicle[4] = 80;
    memcpy(&descrypt_vechicle[5], &command[17], 80);

    ret = m_device->exchangeApdu(85, descrypt_vechicle, &cardAckLen, cardAck);

    logm_debug("descryptVehicle PSAM_ACK: ");
    logm_debug_buffer(cardAck, cardAckLen);

    if((ret != 0)
       || (cardAckLen != 82)
       || (cardAck[cardAckLen - 2] != 0x90)
       || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xe2;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    ack[0] = 0xe2;
    ack[1] = 0x00;
    memcpy(&ack[2], &cardAck[9], 64);

    *ack_len  = 66;

    return;
}
*/

/*
void PsamServer::readTerminalID(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[256];
    unsigned char cardAckLen;
    unsigned char enter_3f00[7];
    unsigned char read_0016[5];
    unsigned char read_0015[5];
    unsigned char enter_df01[5];

    enter_3f00[0] = 0x00;
    enter_3f00[1] = 0xa4;
    enter_3f00[2] = 0x00;
    enter_3f00[3] = 0x00;
    enter_3f00[4] = 0x02;
    enter_3f00[5] = 0x3f;
    enter_3f00[6] = 0x00;
    ret = m_device->exchangeApdu(7, enter_3f00, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAck[cardAckLen-2] != 0x90)
       || (cardAck[cardAckLen-1] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        return;
    }

    read_0016[0] = 0x00;
    read_0016[1] = 0xb0;
    read_0016[2] = 0x96;
    read_0016[3] = 0x00;
    read_0016[4] = 0x06;
    ret = m_device->exchangeApdu(5, read_0016, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAckLen != 8)
       || (cardAck[6] != 0x90)
       || (cardAck[7] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        return;
    }

    memcpy(&ack[2], cardAck, 6);

    read_0015[0] = 0x00;
    read_0015[1] = 0xb0;
    read_0015[2] = 0x95;
    read_0015[3] = 0x0a;
    read_0015[4] = 0x01;
    ret = m_device->exchangeApdu(5, read_0015, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAckLen != 3)
       || (cardAck[1] != 0x90)
       || (cardAck[2] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        return;
    }

    ack[0] = 0xee;
    ack[1] = 0;
    ack[8] = cardAck[0];
    *ack_len = 9;

    enter_df01[0] = 0x00;
    enter_df01[1] = 0xa4;
    enter_df01[2] = 0x00;
    enter_df01[3] = 0x00;
    enter_df01[4] = 0x02;
    enter_df01[5] = 0xdf;
    enter_df01[6] = 0x01;
    ret = m_device->exchangeApdu(7, enter_df01, &cardAckLen, cardAck);

    return;
}
*/

void PsamServer::readTerminalID(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len)
{
    int ret;
    unsigned char cardAck[128];
    unsigned char cardAckLen;
    unsigned char psam_cmd[7];    

    // Enter MF
    psam_cmd[0] = 0x00;
    psam_cmd[1] = 0xa4;
    psam_cmd[2] = 0x00;
    psam_cmd[3] = 0x00;
    psam_cmd[4] = 0x02;
    psam_cmd[5] = 0x3f;
    psam_cmd[6] = 0x00;
    ret = m_device->exchangeApdu(7, psam_cmd, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAck[cardAckLen-2] != 0x90)
       || (cardAck[cardAckLen-1] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    // Read terminal ID
    psam_cmd[0] = 0x00;
    psam_cmd[1] = 0xb0;
    psam_cmd[2] = 0x96;
    psam_cmd[3] = 0x00;
    psam_cmd[4] = 0x06;
    ret = m_device->exchangeApdu(5, psam_cmd, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAckLen != 8)
       || (cardAck[cardAckLen - 2] != 0x90)
       || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
    memcpy(&ack[2], cardAck, 6); // terminal ID

    // Read PSAM_serial and version
    psam_cmd[0] = 0x00;
    psam_cmd[1] = 0xb0;
    psam_cmd[2] = 0x95;
    psam_cmd[3] = 0x00;
    psam_cmd[4] = 0x0C;
    ret = m_device->exchangeApdu(5, psam_cmd, &cardAckLen, cardAck);
    if((ret != 0)       
       || (cardAck[cardAckLen - 2] != 0x90)
       || (cardAck[cardAckLen - 1] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
    memcpy(&ack[8], cardAck, 12); // PSAM serial version type

    // endter DF01
    psam_cmd[0] = 0x00;
    psam_cmd[1] = 0xa4;
    psam_cmd[2] = 0x00;
    psam_cmd[3] = 0x00;
    psam_cmd[4] = 0x02;
    psam_cmd[5] = 0xdf;
    psam_cmd[6] = 0x01;
    ret = m_device->exchangeApdu(7, psam_cmd, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAck[cardAckLen-2] != 0x90)
       || (cardAck[cardAckLen-1] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }

    // read issue ID  and use_area ID
    psam_cmd[0] = 0x00;
    psam_cmd[1] = 0xb0;
    psam_cmd[2] = 0x97;
    psam_cmd[3] = 0x01;
    psam_cmd[4] = 0x10;
    ret = m_device->exchangeApdu(5, psam_cmd, &cardAckLen, cardAck);
    if((ret != 0)
       || (cardAck[cardAckLen-2] != 0x90)
       || (cardAck[cardAckLen-1] != 0x00))
    {
        ack[0] = 0xee;
        ack[1] = 1;
        *ack_len = 2;
        _preWork();
        return;
    }
    memcpy(&ack[20], cardAck, 16); // Issue ID and use_area ID

    ack[0] = 0xee;
    ack[1] = 0x00;
    *ack_len = 36;

    return;
}

void PsamServer::startRun(void)
{
    unsigned char recvLen;
    unsigned char sendLen;
    int ret;

    unsigned char buffer[1024];

    _preWork();

    while(1)
    {
        ret = zmq_recv(m_repSocket, buffer, sizeof(buffer), 0);
        if(ret > 0)
        {
            recvLen = ret;
             logm_debug("psam_%d recv cmd %d <-- ", m_slot + 1, recvLen);
            logm_debug_buffer(buffer, recvLen);
            switch(buffer[0])
            {
                case COLD_RESET:
                {
                    coldReset(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case EXCHANGE_APDU:
                {
                    exchangeApdu(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case EXCHANGE_APDU_ACTIVE:
                {
                    exchangeApduActive(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case CALC_CPC_MAC:
                {
                    calcCpcMac(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case CALC_OBU_MAC:
                {
                    calcObuMac(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case DESCRYPT_VEHICLE:
                {
                    descryptVehicle(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case READ_TERMINAL_ID:
                {
                    readTerminalID(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case CALC_ACCSESS_CRED:
                {
                    calcAccessCred(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case GET_RANDOM:
                {
                    getRand(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case CALC_PURCHASE_MAC1:
                {
                    //init PSAM for purchase
                    calcPurchaseMac1(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case AUTH_PURCHASE_MAC2:
                {
                    //Credit SAM for Purchase
                    authPurchaseMac2(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case GET_MF_RANDOM_8:
                {
                    get_MF_random8(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case PSAM_EX_AUTH:
                {
                    psam_external_auth(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                /*
                case DELIVERY_KEY_VEHICLE:
                {
                    descryptVehicle_Key_delivery(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                case DESCRYPT_VEHICLE_INFOR:
                {
                    descryptVehicle_infor(buffer, recvLen, buffer, &sendLen);
                    break;
                }
                */
                default:
                {
                    buffer[0] = 1;
                    sendLen = 1;
                    break;
                }
            }

            logm_debug("psam_%d send ack %d --> ", m_slot + 1, sendLen);
            logm_debug_buffer(buffer, sendLen);
            
            zmq_send(m_repSocket, buffer, sendLen, 0);
        }
    }
    return;
}





