#include <zmq.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <json/json.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "scheduler.h"
#include "logm.h"
#include "rsu_manager.h"
#include "jiffs.h"
#include "bsp.h"

using namespace std;

//#define logm_debug printf
//#define logm_err printf

#define check_transferchannel_head() do\
{\
    unsigned int mac_id; \
    if((recv_buffer->length < 13) \
       ||(recv_buffer->buffer[0] != 0xe2) \
       ||(recv_buffer->buffer[1] != 0x00) \
       ||(recv_buffer->buffer[6] != 0xe0) \
       ||(recv_buffer->buffer[7] != m_vByte) \
       ||(recv_buffer->buffer[8] != 0x00) \
       ||(recv_buffer->buffer[9] != 0x91) \
       ||(recv_buffer->buffer[10] != 0x18) \
       ||(recv_buffer->buffer[11] != 0x01) \
       ||(recv_buffer->buffer[12] != 0x19) \
      )\
    {\
        return NOTMATCH; \
    }\
    mac_id = (recv_buffer->buffer[2]<<24) \
             |(recv_buffer->buffer[3]<<16) \
             |(recv_buffer->buffer[4]<<8) \
             |recv_buffer->buffer[5]; \
    if(mac_id != m_macId) return NOTMATCH; \
}while(0)


#define encode_transferchannel_head() do\
{\
    m_lastAction[0] = 0xf2; \
    m_lastAction[1] = m_macId>>24; \
    m_lastAction[2] = m_macId>>16; \
    m_lastAction[3] = m_macId>>8; \
    m_lastAction[4] = m_macId; \
    m_lastAction[5] = 0x40; \
    m_lastAction[6] = m_vByte; \
    m_lastAction[7] = 0x91; \
    m_lastAction[8] = 0x05; \
    m_lastAction[9] = 0x01; \
    m_lastAction[10] = 0x03; \
    m_lastAction[11] = 0x18; \
}while(0)

#define check_timeout(errcode) do \
{\
    int timeout; \
    timeout = m_scheduler->m_config->m_obutimeout; \
    if(timeOk(m_startTime, timeout))\
    {\
        goTradeEnd(errcode); \
        return;\
    }\
}while(0)

#define check_timeout_setErrorCode(errcode) do \
{\
    int timeout; \
    timeout = m_scheduler->m_config->m_obutimeout; \
    if(timeOk(m_startTime, timeout))\
    {\
        m_Trade_State_Code = errcode; \
        return(-1);\
    }\
}while(0)

#define check_repeatnum(errcode) do \
    {\
        unsigned int repeatnum; \
        repeatnum = m_scheduler->m_config->m_obuRepeatNum; \
        m_repeatNum++;\
        if(m_repeatNum >= repeatnum)\
        {\
            goTradeEnd(errcode); \
            return;\
        }\
    }while(0)

#define check_repeatnum_setErrorCode(errcode) do \
    {\
        unsigned int repeatnum; \
        repeatnum = m_scheduler->m_config->m_obuRepeatNum; \
        m_repeatNum++;\
        if(m_repeatNum >= repeatnum)\
        {\
            m_Trade_State_Code = errcode; \
            return (-1);\
        }\
    }while(0)


#define check_waitPCAck_timeout(start_send_time) \
    ((get_jiffies() - start_send_time >= WAIT_PC_FRAME_ACK_TIMEOUT) ? 1 : 0)

#define check_waitB9Ack_timeout(start_send_time) \
    ((get_jiffies() - start_send_time >= WAIT_B9_FRAME_ACK_TIMEOUT) ? 1 : 0)

#define check_sendPCFrame_count(current_num) \
    ((current_num >= REPEAT_SEND_FRAME_PC_MAX_NUM) ? 1 : 0)



RfProxy::RfProxy(void *ctx, int rfsn, int power, int channel, const char *addr)
{
    m_ctx = ctx;
    sn = rfsn;
    strcpy(m_addr, addr);
    m_power = power;
    m_channel = channel;
    
    /* connect to antenna */
    Init_RF_ZMQ_Sock();
        
    status = rf_disconnected;

    return;
}

/* Init RF zmq_socket and connect to antenna */
void RfProxy::Init_RF_ZMQ_Sock()
{
    char buffer[32];
    int value;

/****************** create zmq_socket and connect to antenna **********************/    
    sendSock = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(sendSock);
    value = 10;
    /* Keep only last message */
    zmq_setsockopt(sendSock, ZMQ_SNDHWM, &value, sizeof(value));
    /* set close socket wait_time, wait 0ms */
    value = 0;
    zmq_setsockopt(sendSock, ZMQ_LINGER, &value, sizeof(value));    
    sprintf(buffer, "tcp://%s:5502", m_addr);
    zmq_connect(sendSock, buffer);
    
    recvSock = zmq_socket(m_ctx, ZMQ_PULL);
    assert(recvSock);
    value = 1;
    /* Keep only last message  */
    zmq_setsockopt(recvSock, ZMQ_CONFLATE, &value, sizeof(value));
    /* set close socket wait_time, wait 0ms */
    value = 0;
    zmq_setsockopt(recvSock, ZMQ_LINGER, &value, sizeof(value));
    sprintf(buffer, "tcp://%s:5503", m_addr);
    zmq_connect(recvSock, buffer);    
    
    cfgSock = zmq_socket(m_ctx, ZMQ_REQ);
    assert(cfgSock);
    value = 100; /* recv_timeout 100ms */
    zmq_setsockopt(cfgSock, ZMQ_RCVTIMEO, &value, sizeof(value));
    /* set close socket wait_time, wait 0ms */
    value = 0;
    zmq_setsockopt(cfgSock, ZMQ_LINGER, &value, sizeof(value));    
    sprintf(buffer, "tcp://%s:5525", m_addr);
    zmq_connect(cfgSock, buffer);
}

/* close pre-link and retry connect to antennas */
void RfProxy::preClose_ReConnect_Antenna()
{
    /* clsoe pre_link */
    zmq_close(sendSock);
    zmq_close(recvSock);
    zmq_close(cfgSock);

    /* connect to antenna */
    Init_RF_ZMQ_Sock();

    logm_debug("Re_Connect Ant %d\n", sn);

    /* init Antenna Channel */
    initChannel();

    /* init Antenna Power */
    //initPower();

    /* unforbid bst */
    m_rfForbidBst = false;
}

void RfProxy::initPower()
{
    set_power_t cmd;
    set_power_ack_t ack;
    int ret;

    cmd.cmdtype = SET_POWER;
    cmd.power = m_power;

    ret = zmq_send(cfgSock, &cmd, sizeof(set_power_t), 0);
    ret = zmq_recv(cfgSock, &ack, sizeof(set_power_ack_t), 0);
    if((ret != sizeof(set_power_ack_t))||(ack.status != 0))
    {
        logm_err("rf%d init power error\n", sn);
        status = rf_disconnected;
    }
    else
    {
        logm_err("rf%d init power success\n", sn);
        status = rf_connected;
    }

    return;
}

void RfProxy::initChannel()
{
    set_channel_t cmd;
    set_channel_ack_t ack;
    int ret;

    cmd.cmdtype = SET_CHANNEL;
    cmd.channel= m_channel;

    ret = zmq_send(cfgSock, &cmd, sizeof(set_channel_t), 0);
    ret = zmq_recv(cfgSock, &ack, sizeof(set_channel_ack_t), 0);
    if((ret != sizeof(set_channel_ack_t)) || (ack.status != 0)) 
    {
        logm_err("rf%d init channel error\n", sn);
        status = rf_disconnected;
    }
    else
    {
        logm_err("rf%d init channel success\n", sn);
        status = rf_connected;
    }
    return;
}

PsamProxy::PsamProxy(void *ctx, int slot, int type)
{
    int ret;
    char buffer[32];
    int value;

    m_ctx = ctx;
    m_slot = slot;
    m_type = type;

    assert(m_ctx);
    m_reqSock = zmq_socket(m_ctx, ZMQ_REQ);
    assert(m_reqSock);
    value = 300;
    zmq_setsockopt(m_reqSock, ZMQ_RCVTIMEO, &value, sizeof(value));
    sprintf(buffer, "tcp://127.0.0.1:%d", (6999 + m_slot));
    ret = zmq_connect(m_reqSock, buffer);
    assert(ret == 0);

    return;
}

int PsamProxy::exchangeApdu(unsigned char cmdLen, unsigned char *cmd, unsigned char *cmdAckLen, unsigned char *cmdAck)
{
    int ret;
    int recv_len;
    unsigned char command_buffer[256];
    unsigned char ack_buffer[256];

    command_buffer[0] = 0xf9;
    memcpy(&command_buffer[1], cmd, cmdLen);
    logm_debug("psam%d %d--> ", m_slot, cmdLen+1);
    logm_debug_buffer(command_buffer, (cmdLen+1));
    ret = zmq_send(m_reqSock, command_buffer, (cmdLen+1), 0);
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);
    logm_debug("psam%d %d<-- \n", m_slot, recv_len);
    logm_debug_buffer(ack_buffer, recv_len);

    if((recv_len > 2) && (ack_buffer[0] == 0xe9) && (ack_buffer[1] == 0x00)) 
    {
        memcpy(cmdAck, &ack_buffer[2], (recv_len-2));
        *cmdAckLen = recv_len-2;
        return 0;
    }
    else
    {
        logm_err("psamproxy recv ack fail");
        return -1;
    }

}

int PsamProxy::exchangeApduAndActive(unsigned char cmdLen, unsigned char *cmd, unsigned char *cmdAckLen, unsigned char *cmdAck)
{
    int ret;
    int recv_len;
    unsigned char command_buffer[256];
    unsigned char ack_buffer[256];

    command_buffer[0] = 0xfa;
    memcpy(&command_buffer[1], cmd, cmdLen);
    zmq_send(m_reqSock, command_buffer, (cmdLen+1), 0);
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);
    if((recv_len > 2) && (ack_buffer[0] == 0xea) && (ack_buffer[1] == 0x00))
    {
        memcpy(cmdAck, &ack_buffer[2], (recv_len-2));
        return 0;
    }
    else 
    {
        return -1;
    }
}

int PsamProxy::calcObuMac(unsigned char *iccsn, unsigned char *random, unsigned char *encpyption)
{
    int ret;
    int recv_len;
    unsigned char command_buffer[256];
    unsigned char ack_buffer[256];

    command_buffer[0] = 0xfc;
    memcpy(&command_buffer[1], iccsn, 16);
    memcpy(&command_buffer[17], random, 8);
    logm_debug("psam%d %d--> ", m_slot, 25);
    logm_debug_buffer(command_buffer, 25);
    ret = zmq_send(m_reqSock, command_buffer, 25, 0);
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);
    logm_debug("psam%d %d<-- \n", m_slot, recv_len);
    logm_debug_buffer(ack_buffer, recv_len);

    if((recv_len > 2) && (ack_buffer[0] == 0xec) && (ack_buffer[1] == 0x00))
    {
        memcpy(encpyption, &ack_buffer[2], 8);
        return 0;
    }
    else
    {
        logm_err("psamproxy recv ack fail");
        return -1;
    }
}



int PsamProxy::descryptVehicle(unsigned char *yinzi, unsigned char *vehicle, unsigned char *descryption)
{
    int ret;
    int recv_len;
    unsigned char command_buffer[256];
    unsigned char ack_buffer[256];

    command_buffer[0] = 0xfd;
    memcpy(&command_buffer[1], yinzi, 16);
    memcpy(&command_buffer[17], vehicle, 32);
    logm_debug("psam%d %d--> ", m_slot, 49);
    logm_debug_buffer(command_buffer, 49);
    ret = zmq_send(m_reqSock, command_buffer, 49, 0);
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);
    logm_debug("psam%d %d<-- \n", m_slot, recv_len);
    logm_debug_buffer(ack_buffer, recv_len);

    if((recv_len > 2) && (ack_buffer[0] == 0xed) && (ack_buffer[1] == 0x00))
    {
        memcpy(descryption, &ack_buffer[2], 16);
        return 0;
    }
    else
    {
        logm_err("psamproxy recv ack fail");
        return -1;
    }
}



void PsamProxy::sendDescryptVehicle(unsigned char *yinzi, unsigned char rk_index, unsigned char *vehicle)
{
    unsigned char command_len; 
    unsigned char command_buffer[128];   

    command_buffer[0] = 0xfd;
    command_buffer[1] = rk_index;
    memcpy(&command_buffer[2], yinzi, 16);

    /* length of vehicle information = 80 + 16 */
    memcpy(&command_buffer[18], vehicle, 96);
    command_len = 114;

    logm_debug("psam%d %d --> ", m_slot, command_len);
    logm_debug_buffer(command_buffer, command_len);
    zmq_send(m_reqSock, command_buffer, command_len, 0);

    return;
}

int PsamProxy::recvDescryptVehicle(unsigned char *descryption)
{
    int recv_len;
    unsigned char ack_buffer[128];

    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), ZMQ_NOBLOCK);
    if((recv_len >= 2) && (ack_buffer[0] == 0xed)) 
    {
        logm_debug("psam%d %d <-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);
        if(ack_buffer[1] == 0x00)
        {
            /* vehicle_infor 79 bytes */
            memcpy(descryption, &ack_buffer[2], 0x4F);
            return 0;
        }
        else
        {
            logm_err("psamproxy recvDescryptVehicle fail\n");
            return 1;
        }
    }
    else
    {
        return -1;
    }
}


void PsamProxy::sendCalcAccessCred(unsigned char *yinzi, unsigned char *rand)
{
    int ret;
    int recv_len;
    unsigned char command_buffer[256];

    command_buffer[0] = 0xf7;
    memcpy(&command_buffer[1], yinzi, 16);
    memcpy(&command_buffer[17], rand, 8);
    logm_debug("psam%d %d--> ", m_slot, 25);
    logm_debug_buffer(command_buffer, 25);
    zmq_send(m_reqSock, command_buffer, 25, 0);

    return;
}

int PsamProxy::recvCalcAccessCred(unsigned char *accesscred)
{
    int recv_len;
    unsigned char ack_buffer[256];

    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), ZMQ_NOBLOCK);
    if((recv_len >= 2) && (ack_buffer[0] == 0xe7))
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);
        if(ack_buffer[1] == 0x00) 
        {
            memcpy(accesscred, &ack_buffer[2], 8);
            return 0;
        }
        else
        {
            logm_err("psamproxy calc access cred fail\n");
            return 1;
        }
    }
    else
    {
        return -1;
    }
}

void PsamProxy::sendCalcObuMac(unsigned char *iccsn, unsigned char *random)
{
    unsigned char command_buffer[256];

    command_buffer[0] = 0xfc;
    memcpy(&command_buffer[1], iccsn, 16);
    memcpy(&command_buffer[17], random, 8);
    logm_debug("psam%d %d--> ", m_slot, 25);
    logm_debug_buffer(command_buffer, 25);
    zmq_send(m_reqSock, command_buffer, 25, 0);

    return;
}

int PsamProxy::recvCalcObuMac(unsigned char *encpyption)
{
    int recv_len;
    unsigned char ack_buffer[256];

    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), ZMQ_NOBLOCK);
    if((recv_len >= 2) && (ack_buffer[0] == 0xec)) 
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);

        if(ack_buffer[1] == 0x00) 
        {
            memcpy(encpyption, &ack_buffer[2], 8);
            return 0;
        }
        else 
        {
            logm_err("psamproxy recvCalcObuMac ack fail\n");
        }
    }
    else
    {
        return -1;
    }
}


void PsamProxy::sendGetPurchaseMac1(unsigned char *Data_CalcMac1, unsigned char *DeliveryFactor_CalcMac1)
{
    unsigned char command_buffer[256];
    
    command_buffer[0] = 0xf5;
    memcpy(&command_buffer[1], Data_CalcMac1, 20);
    memcpy(&command_buffer[21], DeliveryFactor_CalcMac1, 16);
    logm_debug("psam%d %d--> ", m_slot, 37);
    logm_debug_buffer(command_buffer, 37);
    zmq_send(m_reqSock, command_buffer, 37, 0);

    return;
}

int PsamProxy::recvGetPurchaseMac1(unsigned char *encpyption)
{
    int recv_len;
    unsigned char ack_buffer[256];

    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), ZMQ_NOBLOCK);
    if((recv_len >= 2) && (ack_buffer[0] == 0xe5)) 
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);

        if(ack_buffer[1] == 0x00) 
        {
            memcpy(encpyption, &ack_buffer[2], 8);
            memcpy(m_transSerial, &ack_buffer[2], 4);
            return 0;
        }
        else 
        {
            logm_err("psamproxy recvGetPurchaseMac1 ack fail\n");
        }
    }
    else
    {
        return -1;
    }
}

void PsamProxy::sendCreditPurchaseMac2(unsigned char *mac2)
{
    unsigned char command_buffer[16];
    
    command_buffer[0] = 0xf4;
    memcpy(&command_buffer[1], mac2, 4);
    logm_debug("psam%d %d--> ", m_slot, 5);
    logm_debug_buffer(command_buffer, 5);
    zmq_send(m_reqSock, command_buffer, 5, 0);

    return;
}

int PsamProxy::recvCreditPurchaseMac2(void)
{
    int recv_len;
    unsigned char ack_buffer[16];

    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), ZMQ_NOBLOCK);
    if((recv_len >= 2) && (ack_buffer[0] == 0xe4)) 
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);

        if(ack_buffer[1] == 0x00) 
        {            
            return 0;
        }
        else 
        {
            logm_err("psamproxy recvCreditPurchaseMac2 ack fail\n");
        }
    }
    else
    {
        return -1;
    }
    return;
}


int PsamProxy::readTerminalID()
{
    int ret;
    int recv_len;
    unsigned char command_buffer[2];
    unsigned char ack_buffer[64];

    command_buffer[0] = 0xfe;

    logm_debug("psam%d %d--> ", m_slot, 1);
    logm_debug_buffer(command_buffer, 1);
    
    ret = zmq_send(m_reqSock, command_buffer, 1, 0);
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);    

    if((recv_len > 2) && (ack_buffer[0] == 0xee) && (ack_buffer[1] == 0x00))
    {
        logm_debug("psam%d %d<-- \n", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);

        memcpy(m_terminalID, &ack_buffer[2], 6); /* terminal ID */
        memcpy(m_psamSerial, &ack_buffer[8], 10); /* psam serial */
        m_psamVersion = ack_buffer[18];  /* psam Version */
        m_psamType = ack_buffer[19];  /* psam Type, from psam_file_0015 */
        memcpy(m_psamIssueID, &ack_buffer[20], 8);  /* psam Issue ID */
        memcpy(m_psamUseAreaID, &ack_buffer[28], 8); /* psam Use Area ID */
        return 0;
    }
    else
    {
        logm_err("psamproxy recv ack fail\n");
        return -1;
    }
}

void PsamProxy::sendCmd(unsigned char cmdLen, unsigned char *cmd)
{
    int ret;
    int recv_len;
    unsigned char command_buffer[256];

    command_buffer[0] = 0xf9;
    memcpy(&command_buffer[1], cmd, cmdLen);
    zmq_send(m_reqSock, command_buffer, (cmdLen+1), 0);
    logm_debug("psam%d %d--> ", m_slot, cmdLen+1);
    logm_debug_buffer(command_buffer, (cmdLen+1));
    return;
}

int PsamProxy::recvAck(unsigned char *cmdAckLen, unsigned char *cmdAck)
{
    int recv_len;
    unsigned char ack_buffer[256];
    assert(cmdAck);

    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), ZMQ_NOBLOCK);
    if((recv_len > 2) && (ack_buffer[0] == 0xe9) && (ack_buffer[1] == 0x00))
    {
        assert(recv_len<32);
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);
        memcpy(cmdAck, &ack_buffer[2], (recv_len-2));
        *cmdAckLen = recv_len-2;
        return 0;
    }
    else
    {
        return -1;
    }

}

int PsamProxy::get_MF_random(unsigned char *get_random_ack)
{
    unsigned char command;
    int recv_len;
    unsigned char ack_buffer[16];
    
    command = 0xf3;
    logm_debug("psam%d %d--> %02x\n", m_slot, 1, command);    
    zmq_send(m_reqSock, &command, 1, 0);    
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);    
    

    if((recv_len > 2) && (ack_buffer[0] == 0xe3) && (ack_buffer[1] == 0x00)) 
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);
        memcpy(get_random_ack, &ack_buffer[2], 8);
        return 0;
    }
    else
    {
        logm_debug("psamproxy get MF random ack fail\n");
        return -1;
    }

    return;
}

int PsamProxy::cold_Reset(void)
{
    unsigned char command;
    int recv_len;
    unsigned char ack_buffer[128];
    
    command = 0xf8;
    logm_debug("psam%d %d--> %02x\n", m_slot, 1, command);    
    zmq_send(m_reqSock, &command, 1, 0);    
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);    
    

    if((recv_len > 2) && (ack_buffer[0] == 0xe8) && (ack_buffer[1] == 0x00)) 
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);
        logm_debug("psamproxy cold reset ack success\n");
        return 0;
    }
    else
    {
        logm_debug("psamproxy cold reset ack fail\n");
        return -1;
    }

    return;
}
int PsamProxy::execute_external_auth(unsigned char *auth_mac,unsigned char *auth_ack)
{
    int recv_len;
    unsigned char command[16];    
    unsigned char ack_buffer[16];
    
    command[0] = 0xf2;
    memcpy(&command[1], auth_mac, 8);

    logm_debug("psam%d %d--> ", m_slot, 9);
    logm_debug_buffer(command, 9);

    zmq_send(m_reqSock, command, 9, 0);    
    recv_len = zmq_recv(m_reqSock, ack_buffer, sizeof(ack_buffer), 0);
    
    if((recv_len > 2) && (ack_buffer[0] == 0xe2))
    {
        logm_debug("psam%d %d<-- ", m_slot, recv_len);
        logm_debug_buffer(ack_buffer, recv_len);

        memcpy(auth_ack, &ack_buffer[2], 2);
        return 0;
    }
    else
    {
        logm_debug("psamproxy external auth ack fail\n");
        return -1;
    }

    return;
}

TradeControl::TradeControl(Scheduler *scheduler, void *reporterSocket_send, void *reporterSocket_recv)
{
    m_state = vst_state;
    m_reporttradeState = trade_proc_undefine;
    m_Trade_State_Code = 0x00;
    m_sendTradeFrameCount = 0;
    m_scheduler = scheduler;
    m_macId = 0;    
    m_vByte = 0x77;
    m_needRereadFile15 = false;
    m_psam = NULL;
    m_forbidBst = false;
    m_send_b7_after = 0;
	m_control_D0 = 0;  

    m_reporterSocket_send = reporterSocket_send;
    m_reporterSocket_recv = reporterSocket_recv;

    return;
}

TradeControl::setTradeControlNum(unsigned char num)
{
    m_TradeControlNum = num;
    return;
}

void TradeControl::process()
{
    switch(m_state) 
    {
        case vst_state: 
        {
            matchVst();
            break;
        }
		
        // OBU *************
        case send_getsecure_state: 
        {
            sendGetSecure();
            break;
        }
        case recv_getsecure_state: 
        {
            recvGetSecure();
            break;
        }
        case send_descryption_state: 
        {
            sendDescryption();
            break;
        }
        case recv_descryption_state: 
        {
            recvDescryption();
            break;
        }
        case send_read_icc_files_state: 
        {
            sendReadIccFiles();
            break;
        }
        case recv_read_icc_files_state: 
        {
            recvReadIccFiles();
            break;
        }
        case send_read_file19_and_balance_state: 
        {
            sendReadFile19andBalance();
            break;
        }
        case recv_read_file19_and_balance_state: 
        {
            recvReadFile19andBalance();
            break;
        }
        case send_clear_ef04_state:
        {
            sendClearEf04();
            break;
        }
        case recv_clear_ef04_state:
        {
            recvClearEf04();
            break;
        }
        case send_read_ef04_state:
        {
            sendReadEf04();
            break;
        }
        case recv_read_ef04_state:
        {
            recvReadEf04();
            break;
        }
        case send_read_ef04_exit_state:
        {
            sendReadEf04Exit();
            break;
        }
        case recv_read_ef04_exit_state:
        {
            recvReadEf04Exit();
            break;
        }
        case send_write_ef04_state:
        {
            sendWriteEf04();
            break;
        }
        case recv_write_ef04_state:
        {
            recvWriteEf04();
            break;
        }
        case send_write_ef04_exit_state:
        {
            sendWriteEf04Exit();
            break;
        }
        case recv_write_ef04_exit_state:
        {
            recvWriteEf04Exit();
            break;
        }
        case send_write_ef04_exit_in_state:
        {
            sendWriteEf04inExit();
            break;
        }
              
        case recv_write_ef04_exit_in_state:
        {
            recvWriteEf04inExit();
            break;
        }
        case send_write_ef04_exit1_state:
        {
            sendWriteEf04Exit1();
            break;
        }
        case recv_write_ef04_exit1_state:
        {
            recvWriteEf04Exit1();
            break;
        }
        case send_write_ef04_exit2_state:
        {
            sendWriteEf04Exit2();
            break;
        }
        case recv_write_ef04_exit2_state:
        {
            recvWriteEf04Exit2();
            break;
        }
        case send_read_icc_file19_state: 
        {
            sendReadIccFile19();
            break;
        }
        case recv_read_icc_file19_state: 
        {
            recvReadIccFile19();
            break;
        }
        
        //*** process double_obu ICC purchase
        case send_init_for_purchase_state:
        {
            sendInitPurchase();
            break;
        }
        case recv_init_for_purchase_state:
        {
            recvInitPurchase();
            break;
        }
        case send_only_init_for_purchase_state:
        {
            sendOnlyInitPurchase();
            break;
        }
        case recv_only_init_for_purchase_state:
        {
            recvOnlyInitPurchase();
            break;
        }
        case send_get_Tac_And_Balance_state:
        {
            sendGetTACandBalance();
            break;
        }
        case recv_get_Tac_And_Balance_state:
        {
            recvGetTACandBalance();
            break;
        }
        case send_calc_purchase_mac1_state: // send data to PSAM, init SAM for purchase
        {
            sendCalcPurchaseMac1();
            break;
        }
        case recv_calc_purchase_mac1_state: //receive data from PSAM
        {
            recvCalcPurchaseMac1();            
            break;
        }
        case send_purchase_state: // send data to OBU by RF
        {
            sendPurchase();
            break;
        }
        case recv_purchase_state:  // receive data from OBU by RF
        {
            recvPurchase();
            break;
        }
        case send_auth_purchase_mac2_state: //send data to psam, credit sam for purchase
        {
            sendAuthPurchaseMac2();
            break;
        }
        case recv_auth_purchase_mac2_state:
        {
            recvAuthPurchaseMac2();
            break;
        }
        
        //** porcess single_obu 
        case send_calc_access_cred_state:
        {
            sendCalcAccessCred();
            break;
        }  
        case recv_calc_access_cred_state:
        {
            recvCalcAccessCred();
            break;
        }   
        case send_get_toll_data_state:
        {
            break;
        }
        case recv_get_toll_data_state:
        {
            break;
        }
        case get_random_rsu_state:
        {
            break;
        }
        case send_set_toll_data_state:
        {
            break;
        }
        case recv_set_toll_data_state:
        {
            break;
        }
        case send_auth_authenticator:
        {
            break;
        }
        case recv_auth_authenticator:
        {
            break;
        }

        //Set mmi
        case send_setmmi_state:
        {
            sendSetmmi();
            break;
        }
        case recv_setmmi_state:
        {
            recvSetmmi();
            break;
        }      
        
        // send Trade information to PC, and query pc ACK
        case report_and_query_ack_trade_state:
        {
            reportAndGetAckFromPC();
            break;
        }

        default: 
        {
            logm_err("fall into unknow state\n");
            m_state = vst_state;
            m_macId = 0;
            if(NULL != m_psam) 
            {
                m_scheduler->putPsam(m_psam);
                m_psam = NULL;
            }
            m_forbidBst = false;
        }
    }
    return;
}

/* judge the type of OBU */
void TradeControl::judgeOBUType()
{    
    if(((m_esamVersion & 0xF0) <= 0x40) || (m_esamVersion == 0xFF))
    {
        m_obuType = obu_double;
        logm_info("Tag_Type: daul_cards OBU, Alg_Type 3DES\n");

        /* support 3DES only */
        m_obu_support_RK = OBU_VEHICLE_KEY_3DES;
        
        if(m_obuStatus[0] & ICC_NOT_EXIST) /* judge OBU status */
        {
            logm_info("ic card not exist\n");
            m_OBUStatusBitmap |= ICC_NOT_EXIST;
        }
    }
    else if( ((m_esamVersion & 0xF0) >= 0x50) && ((m_equipmentCV & 0xF0) == 0x10) )
    {
        m_obuType = obu_double;
        logm_info("Tag_Type: daul_cards OBU, Alg_Type SM4\n");

        /* support 3DES and SM4 */
        m_obu_support_RK = OBU_VEHICLE_KEY_SM4;

        if(m_obuStatus[0] & ICC_NOT_EXIST) /* judge OBU status */
        {
            logm_info("ic card not exist\n");
            m_OBUStatusBitmap |= ICC_NOT_EXIST;
        }
    }
    else if( ((m_esamVersion & 0xF0) >= 0x50) && ((m_equipmentCV & 0xF0) == 0x40) )
    {
        m_obuType = obu_single;
        logm_info("Tag_Type: single_card OBU, Alg_Type SM4\n");
    }
    else
    {
        /* OBU type unknow */
        m_obuType = obu_undefine;
    }    
}

void TradeControl::send_bst_interval_to_anotherpc()
{
    if(m_scheduler->m_config->m_etc_mtc == ETC_GRAT)
    {
        if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY < (m_scheduler->m_config->m_location_Y_max + 20)) && (m_LocationY > m_scheduler->m_config->m_location_Y_max))
        {
            m_scheduler->send_bst_interval_status(0x01, 0x70);
            m_scheduler->m_car_status = 0x01;
        }
        else if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY <= (m_scheduler->m_config->m_location_Y_max)) && (m_LocationY > 350)) 
        {
            m_scheduler->send_bst_interval_status(0x01, 0x99);
            m_scheduler->m_car_status = 0x02;
        }
        else if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY <= 160) && (m_LocationY > 130)) 
        {
            m_scheduler->send_bst_interval_status(0x01, 0x99);
        }
        else if((m_LocationX < -200) || (m_LocationX > 200) || (m_LocationY > 1000))
        {
            m_scheduler->m_car_status = 0x00;
        }
    }
    else if(m_scheduler->m_config->m_etc_mtc == ETC_COIL)
    {
        if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY <= m_scheduler->m_config->m_location_Y_max) && (m_LocationY > 600)) 
        {
            m_scheduler->send_bst_interval_status(0x01, 0x99);
            m_scheduler->m_car_status = 0x02;
        }
        else if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY <= (m_scheduler->m_config->m_location_Y_max + 20)) && (m_LocationY > m_scheduler->m_config->m_location_Y_max)) 
        {
            m_scheduler->send_bst_interval_status(0x01, 0x70);
            m_scheduler->m_car_status = 0x01;
        }
        else if((m_LocationX < -200) || (m_LocationX > 200) || (m_LocationY > 1400) || (m_LocationY < 600))
        {
            m_scheduler->m_car_status = 0x00;
        }           
    }
    else if(m_scheduler->m_config->m_etc_mtc == MTC)
    {
        if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY < 1000) && (m_LocationY > 800))
        {
            m_scheduler->send_bst_interval_status(0x01, 0x70);
            m_scheduler->m_car_status = 0x01;
        }
        else if((m_LocationX > -200) && (m_LocationX < 200) && (m_LocationY <= m_scheduler->m_config->m_location_Y_max) && (m_LocationY > 350)) 
        {
            m_scheduler->send_bst_interval_status(0x01, 0x99);
            m_scheduler->m_car_status = 0x02;
        }
        else if((m_LocationX < -200) || (m_LocationX > 200) || (m_LocationY > 1000))
        {
            m_scheduler->m_car_status = 0x00;
        }
    }
}

void TradeControl::setAntWorkMode(int y_coordinate)
{
    switch(m_scheduler->m_ant_work_mode)
    {
        case NEAR_END:
            if(y_coordinate > m_scheduler->m_config->m_near_switch)
            {
                if(y_coordinate > 1000)
                {
                    m_scheduler->m_near_num-=3;
                }
                else
                {
                    m_scheduler->m_near_num-=2;
                }
                m_scheduler->m_mid_to_near_num = 0;
                if(m_scheduler->m_near_num <= 0)
                {
                    m_scheduler->m_ant_work_mode = MID_END;
                    m_scheduler->m_near_num = 0;
                    m_scheduler->m_mid_to_near_num = 5;
                    m_scheduler->m_mid_to_far_num = 5;
                    m_scheduler->m_far_num = 0;
                    logm_debug("because coordinate near_mode change to mid_mode\n");
                }
            }
            else if(y_coordinate <= m_scheduler->m_config->m_near_switch)
            {
                if(m_scheduler->m_near_num < 7)
                {
                    m_scheduler->m_near_num++;
                }
                m_scheduler->m_mid_to_near_num = 0;
                m_scheduler->m_mid_to_far_num = 0;
                m_scheduler->m_far_num = 0;
            }
            break;
        case MID_END:
            if(y_coordinate <= m_scheduler->m_config->m_mid_near_switch)
            {
                m_scheduler->m_mid_to_near_num-=2;
                if(m_scheduler->m_mid_to_near_num <= 0)
                {
                    m_scheduler->m_ant_work_mode = NEAR_END;
                    m_scheduler->m_near_num = 5;
                    m_scheduler->m_mid_to_near_num = 0;
                    m_scheduler->m_mid_to_far_num = 0;
                    m_scheduler->m_far_num = 0;
                    logm_debug("because coordinate mid_mode change to near_mode\n");
                }
            }  
            else if((y_coordinate > m_scheduler->m_config->m_mid_far_switch) && (m_scheduler->m_config->m_etc_mtc == ETC_COIL))
            {
                m_scheduler->m_mid_to_far_num-=2;
                if(m_scheduler->m_mid_to_far_num <= 0)
                {
                    m_scheduler->m_ant_work_mode = FAR_END;
                    m_scheduler->m_near_num = 0;
                    m_scheduler->m_mid_to_near_num = 0;
                    m_scheduler->m_mid_to_far_num = 0;
                    m_scheduler->m_far_num = 5;
                    logm_debug("because coordinate mid_mode change to far_mode\n");
                }
            }
            else
            {
                m_scheduler->m_ant_work_mode = MID_END;
                m_scheduler->m_near_num = 0;
                m_scheduler->m_mid_to_near_num = 5;
                m_scheduler->m_mid_to_far_num = 5;
                m_scheduler->m_far_num = 0;
            }
            break;
        case FAR_END:
            if(y_coordinate < m_scheduler->m_config->m_far_switch)
            {
                if(y_coordinate < 500)
                {
                    m_scheduler->m_far_num-=3;
                }
                else
                {
                    m_scheduler->m_far_num-=2;
                }               
                m_scheduler->m_mid_to_near_num = 0;
                m_scheduler->m_mid_to_far_num = 0;
                m_scheduler->m_near_num = 0;
                if(m_scheduler->m_far_num <= 0)
                {
                    m_scheduler->m_ant_work_mode = MID_END;
                    m_scheduler->m_near_num = 0;
                    m_scheduler->m_mid_to_near_num = 5;
                    m_scheduler->m_mid_to_far_num = 5;
                    m_scheduler->m_far_num = 0;
                    logm_debug("because coordinate far_mode change to mid_mode\n");
                }
            }
            else if(y_coordinate >= m_scheduler->m_config->m_far_switch)
            {
                if(m_scheduler->m_near_num < 5)
                {
                    m_scheduler->m_near_num++;
                }
                m_scheduler->m_near_num = 0;
                m_scheduler->m_mid_to_near_num = 0;
                m_scheduler->m_mid_to_far_num = 0;
                
            }
            break;
        default:
            break;
    }
    return;
}


void TradeControl::cal_average_coordinate_mtc(unsigned int m_macid, int *m_LocationX, int *m_LocationY, int *m_Rssi, int *m_Rssi_num)
{
	obu_coordinate_t * obu_coordinate;
	obu_coordinate_t * old_obu_coordinate;
    
    /* obu list is empty */
    
    if(m_scheduler->m_obuCoordinate.empty())
	{
		obu_coordinate = new obu_coordinate_t();
		obu_coordinate->mac_id = m_macid;
		obu_coordinate->location_X = *m_LocationX;
		obu_coordinate->location_Y3 = *m_LocationY;
        obu_coordinate->location_Y2 = 0;
        obu_coordinate->location_Y1 = 0;  
        obu_coordinate->rssi = *m_Rssi; 
        obu_coordinate->rssi_num = 1;
		obu_coordinate->num = 1;
        m_coord_average_over = 0;
        obu_coordinate->lasttime = get_jiffies();
		
		m_scheduler->m_obuCoordinate.push_back(obu_coordinate);
	}	
	else 
	{
		for(std::list<obu_coordinate_t *>::iterator iter=m_scheduler->m_obuCoordinate.begin();
			iter != m_scheduler->m_obuCoordinate.end(); ++iter)
			{
				if(m_macid == (*iter)->mac_id)
				{
                    /* same obu timeout 5000ms, clear this obu */
                    if(timeOk((*iter)->lasttime, 5000)) 
                    {
                        (*iter)->location_X = *m_LocationX;
		                (*iter)->location_Y3 = *m_LocationY;
                        (*iter)->location_Y2 = 0;
                        (*iter)->location_Y1 = 0;  
                        (*iter)->rssi = *m_Rssi;
                        (*iter)->rssi_num = 1;
		                (*iter)->num = 1;
                        m_coord_average_over = 0;
                        (*iter)->lasttime = get_jiffies();
                        m_search = 0;
                        return;
                    } 
                    (*iter)->lasttime = get_jiffies();
                    if((*iter)->num == -1)
                    {                    
                        if((*iter)->location_X < 0)
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) - 0.5);
                        }
                        else
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) + 0.5);                       
                        }
                        (*iter)->location_Y2 = (*iter)->location_Y3;
                        (*iter)->location_Y3 = *m_LocationY;
                        (*iter)->num += 1;
                        m_search = 1;
                        m_coord_average_over = 0;
                        *m_LocationX = (*iter)->location_X;
                        *m_LocationY = ((*iter)->location_Y2 + (*iter)->location_Y3)/2;

                        logm_debug("mtc num is : %d\n",(*iter)->num);
                    }
                    else if((*iter)->num >= 1)
                    {
                        if((*iter)->num > 5)
                        {
                            if(((*m_LocationX - (*iter)->location_X) > 150) || ((*m_LocationX - (*iter)->location_X) < -150))
                            {
                                *m_LocationY = 2000;
                                m_search = 0;
                                return;
                            }
                        }
                        if((*iter)->location_X < 0)
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) - 0.5);
                        }
                        else
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) + 0.5);                       
                        }
                        
                        if((*iter)->num < 13)
                        {
                            //(*iter)->location_Y3 = (int)((((float)(*iter)->location_Y3 * (*iter)->num )+ (float)(*m_LocationY) )/((*iter)->num + 1) + 0.5);
                           (*iter)->location_Y3 = 1500;
                            *m_LocationY = 1500;
                        }
                        else if((*iter)->num >= 13)
                        {
                            (*iter)->location_Y3 = (int)((((float)(*iter)->location_Y3 * 13 )+ (float)(*m_LocationY) )/14 + 0.5);
                            *m_LocationY = (*iter)->location_Y3;
                        }  

                        /* rssi and rssi num accumulative to  compare*/
                        (*iter)->rssi += *m_Rssi;
                        (*iter)->rssi_num +=1;
                        if((*iter)->rssi < 0)
                        {
                            (*iter)->rssi = 2147483647;
                        }
                        if((*iter)->rssi_num < 0)
                        {
                            (*iter)->rssi_num = 2147483647;
                        }

                        (*iter)->num += 1;                  
                        m_search = 1;
                        m_coord_average_over = 1;
                        *m_LocationX = (*iter)->location_X;     
                        *m_Rssi = (*iter)->rssi;
                        *m_Rssi_num = (*iter)->rssi_num;                 
                        if((*iter)->num > 100)
                        {
                            (*iter)->num = 50;
                        }
                        logm_debug("mtc num is : %d\n",(*iter)->num);
                        logm_debug("rssi num is : %d\n", (*iter)->rssi_num);
                        logm_debug("rssi add up to : %d\n", (*iter)->rssi);
                        if(((*iter)->num == 5) || ((*iter)->num == 8))
                        {
                            if(((*iter)->location_X <= 800) && ((*iter)->location_X >= 500))
                            {
                                m_scheduler->m_config->m_bstInterval = 200;
                            }
                            else if(((*iter)->location_X >= -800) && ((*iter)->location_X <= -500))
                            {
                                m_scheduler->m_config->m_bstInterval = 200;
                            }
                        }
                    }
				}
			}
			if((m_scheduler->m_obuCoordinate.size() < 6) && (m_search !=1))
				{
					obu_coordinate = new obu_coordinate_t();
					obu_coordinate->mac_id = m_macid;
					obu_coordinate->location_X = *m_LocationX;
                    obu_coordinate->location_Y3 = *m_LocationY;
                    obu_coordinate->location_Y2 = 0;
                    obu_coordinate->location_Y1 = 0;
                    obu_coordinate->rssi = *m_Rssi; 
                    obu_coordinate->rssi_num = 1;
					obu_coordinate->num = 1;
                    m_coord_average_over = 0;
                    obu_coordinate->lasttime = get_jiffies();
		
					m_scheduler->m_obuCoordinate.push_back(obu_coordinate);
				}
			else if((m_scheduler->m_obuCoordinate.size() == 6)&&(m_search !=1))
				{
				    old_obu_coordinate = m_scheduler->m_obuCoordinate.front();
					m_scheduler->m_obuCoordinate.pop_front();
					delete old_obu_coordinate;
					
					obu_coordinate = new obu_coordinate_t();
					obu_coordinate->mac_id = m_macid;
					obu_coordinate->location_X = *m_LocationX;
                    obu_coordinate->location_Y3 = *m_LocationY;
                    obu_coordinate->location_Y2 = 0;
                    obu_coordinate->location_Y1 = 0;
                    obu_coordinate->rssi = *m_Rssi; 
                    obu_coordinate->rssi_num = 1;
					obu_coordinate->num = 1;
                    m_coord_average_over = 0;
                    obu_coordinate->lasttime = get_jiffies();
		
					m_scheduler->m_obuCoordinate.push_back(obu_coordinate);
					
				}
	}
	m_search = 0;
    return;
}

void TradeControl::cal_average_coordinate(unsigned int m_macid, int *m_LocationX, int *m_LocationY, int *m_Rssi, int *m_Rssi_num)
{
	obu_coordinate_t * obu_coordinate;
	obu_coordinate_t * old_obu_coordinate;
    
    if(m_scheduler->m_obuCoordinate.empty())
	{
		obu_coordinate = new obu_coordinate_t();
		obu_coordinate->mac_id = m_macid;
		obu_coordinate->location_X = *m_LocationX;
		obu_coordinate->location_Y3 = *m_LocationY;
        obu_coordinate->location_Y2 = 0;
        obu_coordinate->location_Y1 = 0;  
        obu_coordinate->rssi = *m_Rssi; 
        obu_coordinate->rssi_num = 1; 
		obu_coordinate->num = 1;
        m_coord_average_over = 0;
        obu_coordinate->lasttime = get_jiffies();
		
		m_scheduler->m_obuCoordinate.push_back(obu_coordinate);
	}	
	else 
	{
		for(std::list<obu_coordinate_t *>::iterator iter = m_scheduler->m_obuCoordinate.begin();
			iter != m_scheduler->m_obuCoordinate.end(); ++iter)
			{
				if(m_macid == (*iter)->mac_id)
				{
                    if(timeOk((*iter)->lasttime, 5000)) 
                    {
                        (*iter)->location_X = *m_LocationX;
		                (*iter)->location_Y3 = *m_LocationY;
                        (*iter)->location_Y2 = 0;
                        (*iter)->location_Y1 = 0; 
                        (*iter)->rssi = *m_Rssi;
                        (*iter)->rssi_num = 1;  
		                (*iter)->num = 1;
                        m_coord_average_over = 0;
                        (*iter)->lasttime = get_jiffies();
                        m_search = 0;
                        return;
                    } 
                    (*iter)->lasttime = get_jiffies();
                    if((*iter)->num == 1)
                    {                    
                        if((*iter)->location_X < 0)
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) - 0.5);
                        }
                        else
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) + 0.5);                       
                        }
                        (*iter)->location_Y2 = (*iter)->location_Y3;
                        (*iter)->location_Y3 = *m_LocationY;
                        (*iter)->num += 1;
                        (*iter)->rssi += *m_Rssi;
                        (*iter)->rssi_num +=1;
                        m_search = 1;
                        m_coord_average_over = 0;
                        *m_LocationX = (*iter)->location_X;
                        *m_LocationY = ((*iter)->location_Y2 + (*iter)->location_Y3)/2;
                        *m_Rssi = (*iter)->rssi;
                        *m_Rssi_num = (*iter)->rssi_num; 

                        logm_debug("etc num is : %d\n",(*iter)->num);
                    }
                    else if((*iter)->num >= 2)
                    {
                        if((*iter)->location_X < 0)
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) - 0.5);
                        }
                        else
                        {
                            (*iter)->location_X = (int)((((float)(*iter)->location_X * (*iter)->num )+ (float)(*m_LocationX) )/((*iter)->num + 1) + 0.5);                       
                        }
                        (*iter)->location_Y1 = (*iter)->location_Y2;
                        (*iter)->location_Y2 = (*iter)->location_Y3;
                        (*iter)->location_Y3 = *m_LocationY;
                        (*iter)->num += 1;
                        /* if num is vary big ,location_x is cannot change */
                        if((*iter)->num > 100)
                        {
                            (*iter)->num = 50;
                        }

                        /* rssi and rssi num accumulative to  compare*/
                        (*iter)->rssi += *m_Rssi;
                        (*iter)->rssi_num +=1;
                        if((*iter)->rssi < 0)
                        {
                            (*iter)->rssi = 2147483647;
                        }
                        if((*iter)->rssi_num < 0)
                        {
                            (*iter)->rssi_num = 2147483647;
                        }

                        m_search = 1;
                        m_coord_average_over = 1;
                        *m_LocationX = (*iter)->location_X;
                        *m_LocationY = ((*iter)->location_Y1 + (*iter)->location_Y2 + (*iter)->location_Y3)/3;
                        *m_Rssi = (*iter)->rssi;
                        *m_Rssi_num = (*iter)->rssi_num;  

                        logm_debug("etc num is : %d\n",(*iter)->num);
                        if(((*iter)->num == 8) || ((*iter)->num == 15))
                        {
                            if((m_scheduler->m_config->m_direction == LEFT) && (((*iter)->location_X <= 850) && ((*iter)->location_X >= 400)))
                            {
                                m_scheduler->m_config->m_bstInterval = 200;
                                //m_scheduler->send_obu_coordinate_message(m_macid, *m_LocationX, *m_LocationY);
                            }
                            else if((m_scheduler->m_config->m_direction == RIGHT) && (((*iter)->location_X >= -850) && ((*iter)->location_X <= -400)))
                            {
                                m_scheduler->m_config->m_bstInterval = 200;
                                //m_scheduler->send_obu_coordinate_message(m_macid, *m_LocationX, *m_LocationY);
                            }
                        }
                    }
				}
			}
			if((m_scheduler->m_obuCoordinate.size() < 8) && (m_search !=1))
				{
					obu_coordinate = new obu_coordinate_t();
					obu_coordinate->mac_id = m_macid;
					obu_coordinate->location_X = *m_LocationX;
                    obu_coordinate->location_Y3 = *m_LocationY;
                    obu_coordinate->location_Y2 = 0;
                    obu_coordinate->location_Y1 = 0;
                    obu_coordinate->rssi = *m_Rssi; 
                    obu_coordinate->rssi_num = 1; 
					obu_coordinate->num = 1;
                    m_coord_average_over = 0;
                    obu_coordinate->lasttime = get_jiffies();
		
					m_scheduler->m_obuCoordinate.push_back(obu_coordinate);
				}
			else if((m_scheduler->m_obuCoordinate.size() == 8)&&(m_search !=1))
				{
				    old_obu_coordinate = m_scheduler->m_obuCoordinate.front();
					m_scheduler->m_obuCoordinate.pop_front();
					delete old_obu_coordinate;
					
					obu_coordinate = new obu_coordinate_t();
					obu_coordinate->mac_id = m_macid;
					obu_coordinate->location_X = *m_LocationX;
                    obu_coordinate->location_Y3 = *m_LocationY;
                    obu_coordinate->location_Y2 = 0;
                    obu_coordinate->location_Y1 = 0;
                    obu_coordinate->rssi = *m_Rssi; 
                    obu_coordinate->rssi_num = 1; 
					obu_coordinate->num = 1;
                    m_coord_average_over = 0;
                    obu_coordinate->lasttime = get_jiffies();
		
					m_scheduler->m_obuCoordinate.push_back(obu_coordinate);
					
				}
	}
	m_search = 0;
    return;
}

bool TradeControl::decodeVst(recv_buffer_t *recv_buffer)
{
    if((recv_buffer->length < 50)
        ||(recv_buffer->buffer[0] != 0xe1)
        ||(recv_buffer->buffer[1] != 0x00)
        ||(recv_buffer->buffer[9] != 0xd0)) 
    {
        return false;
    }
    else if((recv_buffer->length != (103 + m_scheduler->m_config->m_vst_len))  && recv_buffer->length >80)
    {
        logm_info("VST abnormal\n");
        return false;
    }

    m_macId = (recv_buffer->buffer[2] << 24) | (recv_buffer->buffer[3] << 16)
                | (recv_buffer->buffer[4] << 8) | (recv_buffer->buffer[5]);
    
    memcpy(m_sysInfo, &recv_buffer->buffer[16], 26);
    m_esamVersion = m_sysInfo[9];

#if 0 /* location information not in VST */
    m_equipmentCV = recv_buffer->buffer[recv_buffer->length - 5]; // get epuipment Status
    memcpy(m_obuStatus, &recv_buffer->buffer[recv_buffer->length - 4], 2); // OBU Status
#else /* 8 bytes location information before RSSI */
    m_equipmentCV = recv_buffer->buffer[recv_buffer->length - 13]; /* get epuipment Status */
    memcpy(m_obuStatus, &recv_buffer->buffer[recv_buffer->length - 12], 2); /* OBU Status */

    /* judg macid whether need to trade */
    if((m_macId == m_scheduler->m_instep_macid) && (m_scheduler->m_instep_fake_status == 1))
    {
        logm_debug("goto fake 1\n");
        m_scheduler->m_instep_fake_status = 0;
        m_scheduler->m_instep_macid = 0;
        m_control_D0 = 1;
        goto loop;
    }
    
    /* jump two bytes FCS,  get OBU Coordinate information */
    if((memcmp(&m_LocationX, &recv_buffer->buffer[recv_buffer->length - 8], 4) == 0)
        && (memcmp(&m_LocationY, &recv_buffer->buffer[recv_buffer->length - 4], 4) == 0) )
    {
        // m_macId = 0; /* clear the last mac_id */
        logm_debug("the X Coordinate is %dcm, the Y Coordinate is %dcm\n", m_LocationX, m_LocationY);
        logm_debug("The coordinate information is not changed!\n");
        m_research_obu = 0x01;
        goTradeEnd(COORDINAT_NOT_CHANGED);
        return false;
    }
    memcpy(&m_LocationX, &recv_buffer->buffer[recv_buffer->length - 8], 4);
    memcpy(&m_LocationY, &recv_buffer->buffer[recv_buffer->length - 4], 4);    
    /* save vst rssi value to  judge adjacent */
    m_RSSI = recv_buffer->rssi; 
    logm_debug("before average the X Coordinate is %dcm, the Y Coordinate is %dcm\n", m_LocationX, m_LocationY);
#endif

    loop:
    logm_debug("m_equipmentCV: %02x, m_obuStatus: %02x%02x\n", m_equipmentCV, m_obuStatus[0], m_obuStatus[1]);
    
    /* judge the type of OBU */
    judgeOBUType();

    if(recv_buffer->buffer[42 + m_scheduler->m_config->m_vst_len] == 0x28) 
    {
        memcpy(m_file15, &recv_buffer->buffer[43 + m_scheduler->m_config->m_vst_len], 43);
        m_IccVersion = m_file15[9]; /* get ICC Version */

        logm_debug("ICC_FIle_15:");
        logm_debug_buffer(m_file15, 43);
        logm_debug("ICC_version: %02X\n", m_IccVersion);

        /* for some obu, read file15 from offset_8 */
        if(isBjObu() && (m_file15[2] == 0x11) && (m_file15[3] == 0x01)) 
        {
            memmove(&m_file15[8], &m_file15[0], 35);
            memcpy(m_file15, m_sysInfo, 8);
        }
    }
    else if((recv_buffer->buffer[42 + m_scheduler->m_config->m_vst_len] == 0x1d) && (recv_buffer->buffer[51 + m_scheduler->m_config->m_vst_len] == 0x28))
    {
        /* get icc_file_0015 */
        memcpy(m_file15, &recv_buffer->buffer[52 + m_scheduler->m_config->m_vst_len], 43);
        m_IccVersion = m_file15[9]; /* get ICC version */

        logm_debug("ICC_File_0015: ");
        logm_debug_buffer(m_file15, 43);
        logm_debug("ICC_version: %02X\n", m_IccVersion);

        if(isBjObu() && (m_file15[2] == 0x11) && (m_file15[3] == 0x01))
        {
            memmove(&m_file15[8], &m_file15[0], 35);
            memcpy(m_file15, m_sysInfo, 8);
        }
    }
    else if((recv_buffer->buffer[42 + m_scheduler->m_config->m_vst_len] == 0x1d) && (recv_buffer->buffer[51 + m_scheduler->m_config->m_vst_len] == 0x06))
    {
        if(isBjObu())
        {
            m_needRereadFile15 = true;
        }
    }
    else
    {
        /* OBU status --> ICC exist */
        if((m_OBUStatusBitmap & ICC_NOT_EXIST) == 0x00)
        {
            logm_info("VST not with IC information\n");

            /* VST without IC information, try to read ICC in TransferChannel */
            m_needRereadFile15 = true;
        }
    }

    return true;
}



int TradeControl::decodeTransferChannelAck(recv_buffer_t *recv_buffer, unsigned char *papdu)
{
    unsigned char apdulist;
    unsigned char sectlen;
    unsigned char pos;
    unsigned movedlen;

    check_transferchannel_head();

    apdulist = recv_buffer->buffer[14];
    pos = 15;
    movedlen = 0;
    for(int i=0; i<apdulist; ++i) 
    {
        sectlen = recv_buffer->buffer[pos];
        if((recv_buffer->buffer[pos+sectlen-1] != 0x90)
           ||(recv_buffer->buffer[pos+sectlen] != 0x00))
        {
            return FAIL;           
        }        
        if(movedlen > 128)
            return FAIL;
        memcpy(&papdu[movedlen], &recv_buffer->buffer[pos], sectlen+1);
        movedlen += sectlen-2;
        pos += sectlen + 1;
    }

    if(recv_buffer->buffer[pos] != 0x00)
    {
        return FAIL;
    }        

    return MATCH;
}

int TradeControl::decodeFastReq(recv_buffer_t *recv_buffer)
{
    unsigned int mac_id;
    unsigned char apdulist;
    unsigned char sectlen;
    unsigned char pos;
    unsigned movedlen;
    
    if((recv_buffer->length < 13))
    {
        if ((recv_buffer->buffer[0] != 0xe2) 
            ||(recv_buffer->buffer[1] != 0x00)
            ||(recv_buffer->buffer[6] != 0xe0)
            ||(recv_buffer->buffer[7] != m_vByte)
            ||(recv_buffer->buffer[8] != 0x30))
        {
            return NOTMATCH;
        }
        else
        {
            return MATCH;
        }
    }
    else
    {
        return NOTMATCH;
    }
}

int TradeControl::decodeGetSecure(recv_buffer_t *recv_buffer)
{
    unsigned int mac_id;

    if((recv_buffer->length < 13)
       ||(recv_buffer->buffer[0] != 0xe2)
       ||(recv_buffer->buffer[1] != 0x00)
       ||(recv_buffer->buffer[6] != 0xe0)
       ||(recv_buffer->buffer[7] != m_vByte)
       ||(recv_buffer->buffer[8] != 0x00)
       ||(recv_buffer->buffer[9] != 0x91)
       ||(recv_buffer->buffer[10] != 0x18)
       ||(recv_buffer->buffer[11] != 0x01)
       ||(recv_buffer->buffer[12] != 0x15)
       ||(recv_buffer->buffer[13] != 0x01) )
    {
        return NOTMATCH;
    }

    mac_id = (recv_buffer->buffer[2]<<24) |(recv_buffer->buffer[3]<<16)
             | (recv_buffer->buffer[4]<<8) | recv_buffer->buffer[5];

    if(mac_id != m_macId)
    {
        return NOTMATCH;
    }
    
    memcpy(m_vehicle, &recv_buffer->buffer[14], 96);   /* 16Bytes + 80 Bytes Vechile information */
    
    return MATCH;
}


int TradeControl::decodeInitPurchase(recv_buffer_t *recv_buffer)
{
    unsigned char init_resp_len = 0;

    check_transferchannel_head();

    init_resp_len = recv_buffer->buffer[15];
    if( (init_resp_len != 0x11) 
        || (recv_buffer->buffer[15 + init_resp_len - 1] != 0x90)
        || (recv_buffer->buffer[15 + init_resp_len] != 0x00))
    {
        m_Trade_State_Code = CPU_CARD_INIT_PURCHASE_FAIL;
        return FAIL;
    }
    else if((recv_buffer->buffer[15 + init_resp_len + 1] != 0x02)
            || (recv_buffer->buffer[15 + init_resp_len + 2] != 0x90)
            || (recv_buffer->buffer[15 + init_resp_len + 3] != 0x00))
    {
        m_Trade_State_Code = CPU_CARD_WRITE_FILE0019_FAIL;
        return FAIL;
    }
    else
    {
        memcpy(m_remainMoney, &recv_buffer->buffer[15 + 1], 4);
        memcpy(m_icc_tradesn, &recv_buffer->buffer[15 + 5], 2);
        memcpy(m_creditLine, &recv_buffer->buffer[15 + 7], 3);
        m_purchaseKeyVersion = recv_buffer->buffer[15 + 10];
        m_purchaseKeyAlgorithID = recv_buffer->buffer[15 + 11];
        memcpy(m_purchaseRandom, &recv_buffer->buffer[15 + 12], 4);
    }
    return MATCH;
}

int TradeControl::decodeOnlyInitPurchase(recv_buffer_t *recv_buffer)
{
    unsigned char init_resp_len = 0;

    check_transferchannel_head();

    init_resp_len = recv_buffer->buffer[15];
    if( (init_resp_len != 0x11) 
        || (recv_buffer->buffer[15 + init_resp_len - 1] != 0x90)
        || (recv_buffer->buffer[15 + init_resp_len] != 0x00))
    {
        m_Trade_State_Code = CPU_CARD_INIT_PURCHASE_FAIL;
        return NOTMATCH;
    }
    else
    {
        memcpy(m_remainMoney, &recv_buffer->buffer[15 + 1], 4);
        memcpy(m_icc_tradesn, &recv_buffer->buffer[15 + 5], 2);
        memcpy(m_creditLine, &recv_buffer->buffer[15 + 7], 3);
        m_purchaseKeyVersion = recv_buffer->buffer[15 + 10];
        m_purchaseKeyAlgorithID = recv_buffer->buffer[15 + 11];
        memcpy(m_purchaseRandom, &recv_buffer->buffer[15 + 12], 4);
    }
    return MATCH;
}

int TradeControl::decodeGetTACandBalance(recv_buffer_t *recv_buffer)
{    
    unsigned char get_tac_len;
    unsigned char read_balance_len; 

    check_transferchannel_head();   

    //read the data of File_0019
    get_tac_len = recv_buffer->buffer[15];   
    if((recv_buffer->buffer[14 + get_tac_len] == 0x90)
       &&(recv_buffer->buffer[15 + get_tac_len] == 0x00)) 
    {
        memcpy(m_tradePurchaseMac2, &recv_buffer->buffer[16], 4);
        memcpy(m_tradePurchaseTac, &recv_buffer->buffer[20], 4);
        logm_debug("Last MAC2: ");
        logm_debug_buffer(m_tradePurchaseMac2, 4);
        logm_debug("Last TAC: ");
        logm_debug_buffer(m_tradePurchaseTac, 4);
    }
    else
    {
        m_Trade_State_Code = OBU_GET_TAC_FAIL;
        logm_err("Get Last TAC and MAC error!\n");
        //return FAIL;
    }

    read_balance_len = recv_buffer->buffer[16 + get_tac_len];
    if( (read_balance_len == 0x06) 
        && (recv_buffer->buffer[15 + get_tac_len + read_balance_len] == 0x90)
        && (recv_buffer->buffer[16 + get_tac_len + read_balance_len] == 0x00))
    {
        memcpy(m_icc_balance, &recv_buffer->buffer[17 + get_tac_len], 4);
        logm_debug("ICC_Balance: ");
        logm_debug_buffer(m_icc_balance, 4);
    }
    else
    {
        m_Trade_State_Code = OBU_READ_ICC_FILE02_FAIL;

        logm_err("Read ICC_Balance fail!\n");
        //return FAIL;
    }
    m_Trade_State_Code = TRADE_NORMAL;
    return MATCH;
}

int TradeControl::decodePurchase(recv_buffer_t *recv_buffer)
{
    unsigned char pur_resp_len = 0;    

    check_transferchannel_head();

    pur_resp_len = recv_buffer->buffer[15];
    if( (pur_resp_len != 0x0A) 
        || (recv_buffer->buffer[15 + pur_resp_len - 1] != 0x90)
        || (recv_buffer->buffer[15 + pur_resp_len] != 0x00))
    {
        m_Trade_State_Code = CPU_CARD_DEBIT_PURCHASE_FAIL;
        return FAIL;
    }
    else
    {
        memcpy(m_tradePurchaseTac, &recv_buffer->buffer[15 + 1], 4);
        memcpy(m_tradePurchaseMac2, &recv_buffer->buffer[15 + 5], 4);

        logm_debug("Purchase Tac: ");
        logm_debug_buffer(m_tradePurchaseTac, 4);
        logm_debug("Purchase Mac2: ");
        logm_debug_buffer(m_tradePurchaseMac2, 4);
    }

#if 1  // just purchase, do not read ICC balance
    unsigned char get_balance_len = 0;
    get_balance_len = recv_buffer->buffer[16 + pur_resp_len];
    if( (get_balance_len != 0x06) 
        || (recv_buffer->buffer[16 + pur_resp_len + get_balance_len - 1] != 0x90)
        || (recv_buffer->buffer[16 + pur_resp_len + get_balance_len] != 0x00))
    {
        m_Trade_State_Code = CPU_CARD_READ_FILE0002_FAIL;
        return FAIL;
    }
    else
    {
        memcpy(m_after_purchase_balance, &recv_buffer->buffer[17 + pur_resp_len], 4);
        logm_debug("After Purchase ICC_Balance: ");
        logm_debug_buffer(m_after_purchase_balance, 4);
    }
#endif

    return MATCH;
}

int TradeControl::decodeReadIccFiles(recv_buffer_t *recv_buffer)
{
    unsigned char read_file15_len;
    unsigned char read_file19_len;
    unsigned char read_balance_len; 

    check_transferchannel_head();
    
    //read the data of File_0015
    read_file15_len = recv_buffer->buffer[15];
    if((recv_buffer->buffer[15 + read_file15_len - 1] == 0x90)
       &&(recv_buffer->buffer[15 + read_file15_len] == 0x00))
    {
        memcpy(m_file15, &recv_buffer->buffer[15 + 1], (read_file15_len-2));
        logm_debug("ICC_File_0015: ");
        logm_debug_buffer(m_file15, (read_file15_len-2));
    }
    else
    {
        m_Trade_State_Code = CPU_CARD_READ_FILE0015_FAIL;
        
        logm_err("read file_0015 fail!\n");
        return FAIL;
    }    

    //read the data of File_0019
    read_file19_len = recv_buffer->buffer[16 + read_file15_len];   
    if((recv_buffer->buffer[15 + read_file15_len + read_file19_len] == 0x90)
       &&(recv_buffer->buffer[16 + read_file15_len + read_file19_len] == 0x00)) 
    {
        memcpy(m_file19, &recv_buffer->buffer[17 + read_file15_len], (read_file19_len-2));
        logm_debug("ICC_File_0019: ");
        logm_debug_buffer(m_file19, (read_file19_len-2));
    } 
    else
    {
        m_Trade_State_Code = CPU_CARD_READ_FILE0019_FAIL;
                
        logm_err("read file 0019 error !\n");
        return FAIL;
    }

    read_balance_len = recv_buffer->buffer[17 + read_file15_len + read_file19_len];
    if( (read_balance_len == 0x06) 
        && (recv_buffer->buffer[16 + read_file15_len + read_file19_len + read_balance_len] == 0x90)
        && (recv_buffer->buffer[17 + read_file15_len + read_file19_len + read_balance_len] == 0x00))
    {
        memcpy(m_icc_balance, &recv_buffer->buffer[18 + read_file15_len + read_file19_len], 4);
        logm_debug("ICC_Balance: ");
        logm_debug_buffer(m_icc_balance, 4);        
    }
    else
    {
        m_Trade_State_Code = CPU_CARD_READ_FILE0002_FAIL;

        logm_err("Read ICC_Balance fail!\n");
        return FAIL;
    }

    return MATCH;
}



int TradeControl::decodeReadEf04(recv_buffer_t *recv_buffer)
{
    unsigned char select_fileef04_len;
    unsigned char read_fileef04_len;

    check_transferchannel_head();

 
    select_fileef04_len = recv_buffer->buffer[15];
    read_fileef04_len = recv_buffer->buffer[15+select_fileef04_len+1];
    if((recv_buffer->buffer[15 + select_fileef04_len - 1] == 0x90)
    &&(recv_buffer->buffer[15 + select_fileef04_len] == 0x00)
    &&(read_fileef04_len == m_scheduler->m_initef04len + 2) 
    &&(recv_buffer->buffer[15+select_fileef04_len+read_fileef04_len] == 0x90)
    &&(recv_buffer->buffer[15+select_fileef04_len+1+read_fileef04_len] == 0x00))
    {
        memcpy(m_Ef04Info, &recv_buffer->buffer[15 + select_fileef04_len +2], m_scheduler->m_initef04len);
        logm_debug("ICC_File_ef04: ");
        logm_debug_buffer(m_Ef04Info, m_scheduler->m_initef04len);  
    }
    else
    {
        m_Trade_State_Code = READ_EF04_FAIL;
        m_EF04RdStatus = 0x01;
        memset(m_Ef04Info, 0,m_scheduler->m_initef04len);
        logm_debug("read file ef04 error !\n");
        return FAIL;
    }
    m_EF04RdStatus = 0x00;
    return MATCH;
}


int TradeControl::decodeReadEf04Exit(recv_buffer_t *recv_buffer)
{
    unsigned char select_fileef04_len;
    unsigned char read_fileef04_len;

    check_transferchannel_head();

 
    select_fileef04_len = recv_buffer->buffer[15];
    read_fileef04_len = recv_buffer->buffer[15+select_fileef04_len+1];
    if((recv_buffer->buffer[15 + select_fileef04_len - 1] == 0x90)
    &&(recv_buffer->buffer[15 + select_fileef04_len] == 0x00)
    &&(read_fileef04_len == m_ef04len_c9 + 2) 
    &&(recv_buffer->buffer[15+select_fileef04_len + read_fileef04_len] == 0x90)
    &&(recv_buffer->buffer[15+select_fileef04_len+1+read_fileef04_len] == 0x00))
    {
        memcpy(m_EF04Info_C9_RD, &recv_buffer->buffer[15 + select_fileef04_len +2], m_scheduler->m_initef04len);
        logm_debug("OBU_File_ef04_exit: ");
        logm_debug_buffer(m_EF04Info_C9_RD, m_ef04len_c9);  
    }
    else
    {
        logm_debug("m_ef04len_c9 is %d\n", m_ef04len_c9);
        m_Trade_State_Code = READ_EF04_FAIL;
        m_EF04RdStatus = 0x02;
        logm_debug("read file ef04 error !\n");
        return FAIL;
    }
    m_EF04RdStatus = 0x00;
    return MATCH;
}




int TradeControl::decodeClearEf04(recv_buffer_t *recv_buffer)
{
    unsigned char apdulist1;
    unsigned char apdulist2;
    unsigned char write_ef04_head_len;



    check_transferchannel_head();
    
    write_ef04_head_len = recv_buffer->buffer[15];
    if((recv_buffer->buffer[15+write_ef04_head_len-1] != 0x90)
       ||(recv_buffer->buffer[15+write_ef04_head_len] != 0x00)) 
    {
        logm_err("write ef04 fail\n");
        m_Trade_State_Code = CLEAR_EF04_FAIL;   
    } 
    
    return MATCH;
}

int TradeControl::decodeWriteEf04(recv_buffer_t *recv_buffer)
{
    unsigned char select_ef04_len;
    unsigned char write_ef04_len;

    check_transferchannel_head();

    select_ef04_len = recv_buffer->buffer[15];
    write_ef04_len = recv_buffer->buffer[15+select_ef04_len+1];
    if((recv_buffer->buffer[15 + select_ef04_len - 1] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len] == 0x00)
    &&(recv_buffer->buffer[15 + select_ef04_len + write_ef04_len] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len + 1 + write_ef04_len] == 0x00))
    {
       if(((m_obuStatus[0] >> 7) & 0x01) == 0x01)
       {
           m_Trade_State_Code = EF04_SUCCESS_NO_IC;
           return MATCH;
       }
       
       
        return MATCH;   
    } 
    else
    {
      
       if(((m_obuStatus[0] >> 7) & 0x01) == 0x01)
       {
           logm_err("write ef04 fail\n");
           m_Trade_State_Code = EF04_FAIL_NO_ICC;
           return FAIL; 
       }
      
        logm_err("write ef04 fail\n");
        m_Trade_State_Code = CLEAR_EF04_FAIL;
        return FAIL; 
    } 
}
int TradeControl::decodeWriteEf04inExit(recv_buffer_t *recv_buffer)
{
    unsigned char select_ef04_len_in;
    unsigned char write_ef04_len_in;
    unsigned char write_ef04_len_2;

    check_transferchannel_head();

    
    select_ef04_len_in = recv_buffer->buffer[15];
    write_ef04_len_in = recv_buffer->buffer[15+select_ef04_len_in+1];
    
    write_ef04_len_2 = recv_buffer->buffer[15 + select_ef04_len_in + 1 + write_ef04_len_in + 1];
    if((recv_buffer->buffer[15 + select_ef04_len_in - 1] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len_in] == 0x00)
    &&(recv_buffer->buffer[15 + select_ef04_len_in + write_ef04_len_in] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len_in + 1 + write_ef04_len_in] == 0x00)
    &&(recv_buffer->buffer[15 + select_ef04_len_in + 1 + write_ef04_len_in + write_ef04_len_2] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len_in + 1 + write_ef04_len_in + write_ef04_len_2 + 1] == 0x00)
     )
     {
        if(m_EF04RdStatus ==0x00)
        {
             m_Trade_State_Code = EF04_RW_SUCCESS;
        }
        else
        {
            m_Trade_State_Code = EF04_RD_FAIL_WD_SUCCESS;
        }
       
        return MATCH;
      }
     else
     {
        logm_err("clear ef04 fail\n");
        if(m_EF04RdStatus ==0x00)
        {
             m_Trade_State_Code = EF04_RD_SUCCESS_WD_FAIL;
        }
        else
        {
            m_Trade_State_Code = EF04_RW_FAIL;
        }
         
        return FAIL;
    }     
    
    
    
}


int TradeControl::decodeWriteEf04Exit(recv_buffer_t *recv_buffer)
{
    unsigned char select_ef04_len;
    unsigned char write_ef04_len;
    unsigned char write_ef04_len_2;

    check_transferchannel_head();

    
    select_ef04_len = recv_buffer->buffer[15];
    write_ef04_len = recv_buffer->buffer[15+select_ef04_len+1];
    if(m_ef04len_write_c9 == 0)
    {
        if((recv_buffer->buffer[15 + select_ef04_len - 1] == 0x90)
        &&(recv_buffer->buffer[15 + select_ef04_len] == 0x00))
        {
            if(m_EF04RdStatus ==0x00)
            {
                m_Trade_State_Code = EF04_RW_SUCCESS;
            }
            else
            {
                m_Trade_State_Code = EF04_RD_FAIL_WD_SUCCESS;
            }
                 
            return MATCH;
        }
        else
        {
            logm_err("clear ef04 fail\n");
           if(m_EF04RdStatus ==0x00)
             {
                  m_Trade_State_Code = EF04_RD_SUCCESS_WD_FAIL;
             }
           else
            {
            m_Trade_State_Code = EF04_RW_FAIL;
            }
           
            return FAIL;
        }     
    }
    else
    {
      //  write_ef04_len_2 = recv_buffer->buffer[15 + select_ef04_len + 1 + write_ef04_len + 1];
        if((recv_buffer->buffer[15 + select_ef04_len - 1] == 0x90)
        &&(recv_buffer->buffer[15 + select_ef04_len] == 0x00)
        &&(recv_buffer->buffer[15 + select_ef04_len + write_ef04_len] == 0x90)
        &&(recv_buffer->buffer[15 + select_ef04_len + 1 + write_ef04_len] == 0x00)
         )
        {
           if(m_EF04RdStatus ==0x00)
            {
                m_Trade_State_Code = EF04_RW_SUCCESS;
            }
            else
            {
                m_Trade_State_Code = EF04_RD_FAIL_WD_SUCCESS;
            }
           
            return MATCH;
        }
        else
        {
            logm_err("clear ef04 fail\n");
            if(m_EF04RdStatus ==0x00)
             {
                  m_Trade_State_Code = EF04_RD_SUCCESS_WD_FAIL;
             }
            else
            {
                  m_Trade_State_Code = EF04_RW_FAIL;
            }
           
            return FAIL;
        }     
    }
    
    
}

int TradeControl::decodeWriteEf04Exit1(recv_buffer_t *recv_buffer)
{
    unsigned char select_ef04_len;
    unsigned char write_ef04_len;
    unsigned char write_ef04_len_2;

    check_transferchannel_head();
    
    select_ef04_len = recv_buffer->buffer[15];
    write_ef04_len = recv_buffer->buffer[15+select_ef04_len+1];

    if((recv_buffer->buffer[15 + select_ef04_len - 1] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len] == 0x00)
    &&(recv_buffer->buffer[15 + select_ef04_len + write_ef04_len] == 0x90)
    &&(recv_buffer->buffer[15 + select_ef04_len + 1 + write_ef04_len] == 0x00)
    )
    {
        return MATCH;
    }
    else
    {
        logm_err("clear ef04 fail\n");
        m_Trade_State_Code = CLEAR_EF04_FAIL; 
        return FAIL;
    }     
}

int TradeControl::decodeWriteEf04Exit2(recv_buffer_t *recv_buffer)
{
    unsigned char select_ef04_len;
    unsigned char write_ef04_len;
    unsigned char write_ef04_len_2;

    check_transferchannel_head();

    if(m_ef04len != 0)
    {
        write_ef04_len = recv_buffer->buffer[15];
        if((recv_buffer->buffer[15 + write_ef04_len - 1] == 0x90)
        &&(recv_buffer->buffer[15 + write_ef04_len] == 0x00)
        )
        {
            return MATCH;
        }
        else
        {
            logm_err("clear ef04 fail\n");
            m_Trade_State_Code = CLEAR_EF04_FAIL; 
            return FAIL;
        } 
    }
    else
    {
        select_ef04_len = recv_buffer->buffer[15];
        write_ef04_len = recv_buffer->buffer[15+select_ef04_len+1];
        if((recv_buffer->buffer[15 + select_ef04_len - 1] == 0x90)
        &&(recv_buffer->buffer[15 + select_ef04_len] == 0x00)
        &&(recv_buffer->buffer[15 + select_ef04_len + write_ef04_len] == 0x90)
        &&(recv_buffer->buffer[15 + select_ef04_len + 1 + write_ef04_len] == 0x00)
        )
        {
            return MATCH;
        }
        else
        {
            logm_err("clear ef04 fail\n");
            m_Trade_State_Code = CLEAR_EF04_FAIL; 
            return FAIL;
        }     
    } 
}


int TradeControl::decodeReadFile19andBalance(recv_buffer_t *recv_buffer)
{    
    unsigned char read_file19_len;
    unsigned char read_balance_len;

    check_transferchannel_head();

    /* read the data of File_0019 */
    read_file19_len = recv_buffer->buffer[15];   
    if( (read_file19_len == 0x2d)
        && (recv_buffer->buffer[14 + read_file19_len] == 0x90)
        && (recv_buffer->buffer[15 + read_file19_len] == 0x00))
    {
        memcpy(m_file19, &recv_buffer->buffer[16], (read_file19_len - 2));
        logm_debug("ICC_File_0019: ");
        logm_debug_buffer(m_file19, (read_file19_len - 2));
    }
    else
    {        
        m_Trade_State_Code = CPU_CARD_READ_FILE0019_FAIL;
        logm_err("read file 0019 error !\n");        
        
        return FAIL;
    }

    read_balance_len = recv_buffer->buffer[16 + read_file19_len];
    if( (read_balance_len == 0x06) 
        && (recv_buffer->buffer[15 + read_file19_len + read_balance_len] == 0x90)
        && (recv_buffer->buffer[16 + read_file19_len + read_balance_len] == 0x00))
    {
        memcpy(m_icc_balance, &recv_buffer->buffer[17 + read_file19_len], 4);
        logm_debug("ICC_Balance: ");
        logm_debug_buffer(m_icc_balance, 4);
    }
    else
    {        
        m_Trade_State_Code = CPU_CARD_READ_FILE0002_FAIL;
        logm_err("Read ICC_Balance fail!\n");
    
        return FAIL;
    }  

    /* if ICCVersion = 0x4X, read file15 tail 7 bytes */
    if((m_IccVersion & 0xF0) == 0x40)
    {
        unsigned char read_file15_len; 

        read_file15_len = recv_buffer->buffer[17 + read_file19_len + read_balance_len];
        if( (read_file15_len == 0x09) 
            && (recv_buffer->buffer[16 + read_file19_len + read_balance_len + read_file15_len] == 0x90)
            && (recv_buffer->buffer[17 + read_file19_len + read_balance_len + read_file15_len] == 0x00))
        {
            memcpy(&m_file15[43], &recv_buffer->buffer[18 + read_file19_len + read_balance_len], 7);
            logm_debug("Add ICC_File_15 Tail: ");
            logm_debug_buffer(m_file15, 50);
        }
        else
        {
            m_Trade_State_Code = OBU_READ_ICC_FILE15_FAIL;
            logm_err("Read ICC_File15 Tail fail!\n");
        }
    }

    return MATCH;
}


int TradeControl::decodeReadIccFile19(recv_buffer_t *recv_buffer)
{    
    unsigned char read_file19_len;

    check_transferchannel_head();
    
    //read the data of File_0019
    read_file19_len = recv_buffer->buffer[15];
    if((recv_buffer->buffer[15 + read_file19_len - 1] == 0x90)
       &&(recv_buffer->buffer[15 + read_file19_len] == 0x00))
    {
        memcpy(m_file19, &recv_buffer->buffer[15 + 1], (read_file19_len-2));
        logm_debug("ICC_File_0019: ");
        logm_debug_buffer(m_file19, (read_file19_len-2));
    }
    else
    {
        m_Trade_State_Code = CPU_CARD_READ_FILE0019_FAIL;

        logm_err("read file_0019 fail!\n");
        return FAIL;
    }    

    return MATCH;
}


void TradeControl::encodeTransferChannel(unsigned char channelId, unsigned char *papdulist, unsigned int apdulist_len)
{
    encode_transferchannel_head();

    m_lastAction[12] = channelId;
    memcpy(&m_lastAction[13], papdulist, apdulist_len);

    m_lastActionLen = apdulist_len + 13;

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
}


void TradeControl::encodeGetSecure()
{
    m_lastAction[0] = 0xf2;
    m_lastAction[1] = m_macId>>24;
    m_lastAction[2] = m_macId>>16;
    m_lastAction[3] = m_macId>>8;
    m_lastAction[4] = m_macId;
    m_lastAction[5] = 0x40;
    m_lastAction[6] = m_vByte;
    m_lastAction[7] = 0x91;
    m_lastAction[8] = 0x05;
    m_lastAction[9] = 0x01;    /* DID */
    m_lastAction[10] = 0x00;   /* ActionType  GetSecureType */
    m_lastAction[11] = 0x14;   /* GetSecureRq  Container */
    m_lastAction[12] = 0x80;   /* KeyID for Encrypt Option, bit7->exist */
    m_lastAction[13] = 0x01;   /* FID -> file ID of vehicle information */
    m_lastAction[14] = 0x00;   /* vehicle information offset_1 */
    m_lastAction[15] = 0x00;   /* vehicle information offset_2 */
    //m_lastAction[16] = 0x40; /* 0x40 -> 64 >> length of vehicle information */
    //m_lastAction[16] = 0x3B; /* 0x3B -> 59 >> length of vehicle information */    
    m_lastAction[16] = 0x4F;   /* 0x4F -> 79 >> length of vehicle information */
    
    /* RSU_Random 8 Bytes */
    unsigned int GetSecure_rand;
    GetSecure_rand = rand();
    m_lastAction[17] = GetSecure_rand >> 24;
    m_lastAction[18] = GetSecure_rand >> 16;
    m_lastAction[19] = GetSecure_rand >> 8;
    m_lastAction[20] = GetSecure_rand;
    GetSecure_rand = rand();
    m_lastAction[21] = GetSecure_rand >> 24;
    m_lastAction[22] = GetSecure_rand >> 16;
    m_lastAction[23] = GetSecure_rand >> 8;
    m_lastAction[24] = GetSecure_rand;

    /* check key version */
    if((!m_scheduler->m_universalPsams.empty()) && (m_obu_support_RK == OBU_VEHICLE_KEY_SM4))
    {
        /* KeyID for Authen,  0x40 -> SM4 */
        m_lastAction[25] = 0x40;
        /* KeyID for Encrypt, 0x40 -> SM4 */
        m_lastAction[26] = 0x40;

        /* psam descrypt vehicle key version -> SM4 */
        m_psam_descrypt_KeyVersion = PSAM_DESCRYPT_VEHICLE_SM4;
    }
    else
    {
        /* KeyID for Authen,  0x00 -> 3DES*/
        m_lastAction[25] = 0x00;
        /* KeyID for Encrypt, 0x00 -> 3DES */
        m_lastAction[26] = 0x00;

        /* psam descrypt vehicle key version -> 3DES */
        m_psam_descrypt_KeyVersion = PSAM_DESCRYPT_VEHICLE_3DES;
    }

    m_lastActionLen = 27;

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
}

void TradeControl::encodeInitPurchase(void)
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x01;
    m_lastAction[13] = 0x02;

    /* CMD for init purchase */
    m_lastAction[14] = 0x10;
    m_lastAction[15] = 0x80;
    m_lastAction[16] = 0x50;
    m_lastAction[17] = 0x03;
    m_lastAction[18] = 0x02;
    m_lastAction[19] = 0x0B;

    /* check psam_version and icc_version */
    if((m_psam->m_psamVersion >= 0x05)
        && (((m_IccVersion & 0xf0) >= 0x50) && (m_IccVersion != 0xFF)))
    {
        m_lastAction[20] = 0x41;  /* key_index, 0x41 -> SM4 */
    }
    else
    {
        m_lastAction[20] = 0x01;  /* key_index, 0x01 -> 3DES */
    }

    memcpy(&m_lastAction[21], m_transaction_fees, 4);    
    memcpy(&m_lastAction[25], m_terminal_id, 6);

    /* update 0019 cache */
    m_lastAction[31] = 0x30;
    m_lastAction[32] = 0x80;
    m_lastAction[33] = 0xDC;
    m_lastAction[34] = 0xAA;
    m_lastAction[35] = 0xC8;
    m_lastAction[36] = 0x2B; // Length of Data
#if 0
    m_lastAction[37] = 0xAA; // Compound consumption ID --> 0xAA
    m_lastAction[38] = 0x29; // Length of record
    m_lastAction[39] = 0x00; // lock_flag: 0x00 -> unlock, 0x01 -> lock
    memcpy(&m_lastAction[40], &m_file19[3], 40);
#else
    memcpy(&m_lastAction[37], m_file19, 43);
#endif

    m_lastActionLen = 80;
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
}

void TradeControl::encodeOnlyInitPurchase(void)
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x01;
    m_lastAction[13] = 0x01;

    //CMD for init purchase
    m_lastAction[14] = 0x10;
    m_lastAction[15] = 0x80;
    m_lastAction[16] = 0x50;
    m_lastAction[17] = 0x03;
    m_lastAction[18] = 0x02;
    m_lastAction[19] = 0x0B;
    m_lastAction[20] = 0x01;
    m_lastAction[21] = m_transaction_fees[0];
    m_lastAction[22] = m_transaction_fees[1];
    m_lastAction[23] = m_transaction_fees[2];
    m_lastAction[24] = m_transaction_fees[3];
    memcpy(&m_lastAction[25], m_terminal_id, 6);

    m_lastActionLen = 31;
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
}

void TradeControl::encodeGetTACandBalance(void)
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x01; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x02; // APDU List

    // get TAC
    m_lastAction[14] = 0x08;
    m_lastAction[15] = 0x80;
    m_lastAction[16] = 0x5A;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x09; // Compound consumption 
    m_lastAction[19] = 0x02; // LC
    m_lastAction[20] = m_icc_tradesn[0]; 
    m_lastAction[21] = m_icc_tradesn[1];
    m_lastAction[22] = 0x08; // length to read 

    //CMD for get balance
    m_lastAction[23] = 0x05;
    m_lastAction[24] = 0x80;
    m_lastAction[25] = 0x5C;
    m_lastAction[26] = 0x00;
    m_lastAction[27] = 0x02;
    m_lastAction[28] = 0x04;

    m_lastActionLen = 29;

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;

    return;
}

void TradeControl::encodePurchase(void)
{  
    encode_transferchannel_head();
    m_lastAction[12] = 0x01;

#if 1  // get ICC balance
    m_lastAction[13] = 0x02; // APDU List

    //CMD for purchase
    m_lastAction[14] = 0x14;
    m_lastAction[15] = 0x80;
    m_lastAction[16] = 0x54;
    m_lastAction[17] = 0x01;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x0F;
    memcpy(&m_lastAction[20], &m_encryption[0], 4); // PSAM Trans Serial
    memcpy(&m_lastAction[24], &m_purchaseDateTime[0], 7); // Trans Time
    memcpy(&m_lastAction[31], &m_encryption[4], 4); // MAC1

    //Get ICC Balance after purchase
    m_lastAction[35] = 0x05;
    m_lastAction[36] = 0x80;
    m_lastAction[37] = 0x5C;
    m_lastAction[38] = 0x00;
    m_lastAction[39] = 0x02;
    m_lastAction[40] = 0x04;

    m_lastActionLen = 41; // length of DSRC

#else // just purchase, do not read ICC balance
    m_lastAction[13] = 0x01; // APDU List

    //CMD for purchase
    m_lastAction[14] = 0x14;
    m_lastAction[15] = 0x80;
    m_lastAction[16] = 0x54;
    m_lastAction[17] = 0x01;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x0F;
    memcpy(&m_lastAction[20], &m_encryption[0], 4); // PSAM Trans Serial
    memcpy(&m_lastAction[24], &m_purchaseDateTime[0], 7); // Trans Time
    memcpy(&m_lastAction[31], &m_encryption[4], 4); // MAC1
    
    m_lastActionLen = 35; // length of DSRC
#endif

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
}

void TradeControl::encodeReadIccFiles()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x01;//
    m_lastAction[13] = 0x03;

    // read File_0015 of ICC
    m_lastAction[14] = 0x05;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xb0;
    m_lastAction[17] = 0x95;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x2b; // length of file_15 to read

    // read File_0019 of ICC  -------> *** Note: need modify
    m_lastAction[20] = 0x05;
    m_lastAction[21] = 0x00;
    m_lastAction[22] = 0xb2;
#if 0
    m_lastAction[23] = 0xAA;
    m_lastAction[24] = 0xC8;
#else
    m_lastAction[23] = 0x01;
    m_lastAction[24] = 0xCC;
#endif
    m_lastAction[25] = 0x2b; // length of file_19 to read 

    //CMD for get balance
    m_lastAction[26] = 0x05;
    m_lastAction[27] = 0x80;
    m_lastAction[28] = 0x5C;
    m_lastAction[29] = 0x00;
    m_lastAction[30] = 0x02;
    m_lastAction[31] = 0x04;    

    m_lastActionLen = 32;

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
}

void TradeControl::encodeWriteEf04Exit()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x02; // APDU List

    // read File_ef04 of esam  
    m_lastAction[14] = 0x07;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xa4;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x02;
    m_lastAction[20] = 0xef;
    m_lastAction[21] = 0x04;

   
    if(m_ef04len_write_c9 != 0)
    {
        m_lastAction[22] = m_EF04WriteLen[1] + 5;
        m_lastAction[23] = 0x00;
        m_lastAction[24] = 0xd6;
        m_lastAction[25] = m_EF04WriteOffSet[0];
        m_lastAction[26] = m_EF04WriteOffSet[1];
        m_lastAction[27] = m_EF04WriteLen[1]; // length of ef04 to write
        memcpy(&m_lastAction[28],m_EF04Info_C9_WD, m_ef04len_write_c9);
        m_lastActionLen = 28 + m_ef04len_write_c9;
    }
    else
    {
        m_lastAction[13] = 0x01; // APDU List
        m_lastActionLen = 22;
    }
    
    
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
   
}

void TradeControl::encodeWriteEf04inExit()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x03; // APDU List

    // read File_ef04 of esam  
    m_lastAction[14] = 0x07;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xa4;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x02;
    m_lastAction[20] = 0xef;
    m_lastAction[21] = 0x04;

    m_lastAction[22] = 0x08;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0xd6;
    m_lastAction[25] = 0x01;
    m_lastAction[26] = 0x3A;
    m_lastAction[27] = 3; // length of ef04 to write

    //memset(&m_lastAction[28], 0, m_ef04len);
    memset(&m_lastAction[28], 0, 3);

    
    m_lastAction[31] = 85;
    m_lastAction[32] = 0x00;
    m_lastAction[33] = 0xd6;
    m_lastAction[34] = 0x01;
    m_lastAction[35] = 0x95;
    m_lastAction[36] = 80; // length of ef04 to write
    memset(&m_lastAction[37], 0, 80);
       
    m_lastActionLen = 117;

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
   
}





void TradeControl::encodeWriteEf04Exit1()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x02; // APDU List

    // read File_ef04 of esam  
    m_lastAction[14] = 0x07;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xa4;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x02;
    m_lastAction[20] = 0xef;
    m_lastAction[21] = 0x04;

    m_lastAction[22] = m_Ef04Len[1] + 5;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0xd6;
    m_lastAction[25] = m_Ef04Off[0];
    m_lastAction[26] = m_Ef04Off[1];
    m_lastAction[27] = m_Ef04Len[1]; // length of ef04 to write

    //memset(&m_lastAction[28], 0, m_ef04len);
    memcpy(&m_lastAction[28], m_Ef04Info, m_ef04len);

    m_lastActionLen = 28 + m_ef04len;
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
   
}

void TradeControl::encodeWriteEf04Exit2()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x01; // APDU List
    
    if(m_ef04len != 0)
    {
        m_lastAction[14] = m_EF04WriteLen[1] + 5;
        m_lastAction[15] = 0x00;
        m_lastAction[16] = 0xd6;
        m_lastAction[17] = m_EF04ReadOffSet[0];
        m_lastAction[18] = m_EF04ReadOffSet[1];

        m_lastAction[19] = m_EF04WriteLen[1]; // length of ef04 to read
        
        memset(&m_lastAction[20], 0, m_ef04len_write_c7);
        m_lastActionLen = 20 + m_ef04len_write_c7;
    }
    else
    {
        m_lastAction[13] = 0x02; // APDU List
        m_lastAction[14] = 0x07;
        m_lastAction[15] = 0x00;
        m_lastAction[16] = 0xa4;
        m_lastAction[17] = 0x00;
        m_lastAction[18] = 0x00;
        m_lastAction[19] = 0x02;
        m_lastAction[20] = 0xef;
        m_lastAction[21] = 0x04;
        
        m_lastAction[22] = m_EF04WriteLen[1] + 5;
        m_lastAction[23] = 0x00;
        m_lastAction[24] = 0xd6;
        m_lastAction[25] = m_EF04ReadOffSet[0];
        m_lastAction[26] = m_EF04ReadOffSet[1];

        m_lastAction[27] = m_EF04WriteLen[1]; // length of ef04 to read
        
        memset(&m_lastAction[28], 0, m_ef04len_write_c7);
        m_lastActionLen = 28 + m_ef04len_write_c7;
    }
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
}

void TradeControl::encodeWriteEf04()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x02; // APDU List

    // read File_ef04 of esam  
    m_lastAction[14] = 0x07;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xa4;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x02;
    m_lastAction[20] = 0xef;
    m_lastAction[21] = 0x04;

    m_lastAction[22] = m_Ef04Len[1] + 5;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0xd6;
    m_lastAction[25] = m_Ef04Off[0];
    m_lastAction[26] = m_Ef04Off[1];
    if(m_Ef04Len[0] == 0x00)
    {
        m_lastAction[27] = m_Ef04Len[1]; // length of ef04 to read
    }
    memcpy(&m_lastAction[28], m_Ef04Info, m_ef04len);

        
    m_lastActionLen = 28 + m_ef04len;
    
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;

    return;
}

void TradeControl::encodeReadEf04()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x02; // APDU List

    // read File_ef04 of esam  
    m_lastAction[14] = 0x07;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xa4;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x02;
    m_lastAction[20] = 0xef;
    m_lastAction[21] = 0x04;

    m_lastAction[22] = 0x05;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0xb0;
    m_lastAction[25] = m_scheduler->m_InitEf04Offset[0];
    m_lastAction[26] = m_scheduler->m_InitEf04Offset[1];
    if(m_scheduler->m_InitEf04Len[0] == 0x00)
    {
        m_lastAction[27] = m_scheduler->m_InitEf04Len[1]; // length of ef04 to read 
    }
        
    m_lastActionLen = 28;
    
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;

    return;
}

void TradeControl::encodeReadEf04Exit()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x02; // channel_ID=1 --> ICC
    m_lastAction[13] = 0x02; // APDU List

    // read File_ef04 of esam  
    m_lastAction[14] = 0x07;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xa4;
    m_lastAction[17] = 0x00;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x02;
    m_lastAction[20] = 0xef;
    m_lastAction[21] = 0x04;

    m_lastAction[22] = 0x05;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0xb0;
    m_lastAction[25] = m_EF04ReadOffSet[0];
    m_lastAction[26] = m_EF04ReadOffSet[1];
    if(m_EF04ReadLen[0] == 0x00)
    {
        m_lastAction[27] = m_EF04ReadLen[1]; // length of ef04 to read 
    }   
    m_lastActionLen = 28;
    
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;

    return;
}




void TradeControl::encodeClearEf04(void)
{
    encode_transferchannel_head();

    m_lastAction[12] = 0x02;
    m_lastAction[13] = 0x01;

    m_lastAction[14] = 0x0b;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xd6;
    m_lastAction[17] = 0x84;
    m_lastAction[18] = 0x00;
    m_lastAction[19] = 0x06;
    m_lastAction[20] = 0x00;
    m_lastAction[21] = 0x00;
    m_lastAction[22] = 0x00;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0x00;
    m_lastAction[25] = 0x00;

    m_lastActionLen = 26;
    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;

    return;
}


void TradeControl::encodeReadFile19andBalance()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x01; // channel_ID=1 --> ICC

    //m_lastAction[13] = 0x02; // APDU List

    // read File_0019 of ICC 
    m_lastAction[14] = 0x05;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xb2;
#if 0
    m_lastAction[17] = 0xAA;
    m_lastAction[18] = 0xC8;
#else
    m_lastAction[17] = 0x01;
    m_lastAction[18] = 0xCC;
#endif
    m_lastAction[19] = 0x2b; // length of file_19 to read 

    //CMD for get balance
    m_lastAction[20] = 0x05;
    m_lastAction[21] = 0x80;
    m_lastAction[22] = 0x5C;
    m_lastAction[23] = 0x00;
    m_lastAction[24] = 0x02;
    m_lastAction[25] = 0x04;

   if((m_IccVersion & 0xF0) == 0x40)  // ICC version 4X
    {
        // reads file_0015 tail 7 bytes
        m_lastAction[26] = 0x05;
        m_lastAction[27] = 0x00;
        m_lastAction[28] = 0xb0;
        m_lastAction[29] = 0x95;
        m_lastAction[30] = 0x2B;
        m_lastAction[31] = 0x07; // length of file_15 to read

        m_lastAction[13] = 0x03; // APDU List
        m_lastActionLen = 32;   // Length of DSRC
    }
    else
    {
        m_lastAction[13] = 0x02; // APDU List
        m_lastActionLen = 26;   // Length of DSRC
    }  

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
}

void TradeControl::encodeReadIccFile19()
{
    encode_transferchannel_head();
    m_lastAction[12] = 0x01;//
    m_lastAction[13] = 0x01;

    // read File_0019 of ICC 
    m_lastAction[14] = 0x05;
    m_lastAction[15] = 0x00;
    m_lastAction[16] = 0xb2;
#if 0
    m_lastAction[17] = 0xAA;
    m_lastAction[18] = 0xC8;
#else
    m_lastAction[17] = 0x01;
    m_lastAction[18] = 0xCC;
#endif
    m_lastAction[19] = 0x2b; // length of file_19 to read       

    m_lastActionLen = 20;

    m_vByte = (m_vByte == 0x77) ? 0xf7 : 0x77;
    return;
}


void TradeControl::encodeSetMmi()
{
    m_lastAction[0] = 0xf2;
    m_lastAction[1] = m_macId>>24;
    m_lastAction[2] = m_macId>>16;
    m_lastAction[3] = m_macId>>8;
    m_lastAction[4] = m_macId;
    m_lastAction[5] = 0x40;
    m_lastAction[6] = m_vByte;
    m_lastAction[7] = 0x91;
    m_lastAction[8] = 0x05;
    m_lastAction[9] = 0x01;
    m_lastAction[10] = 0x04;
    m_lastAction[11] = 0x1a;
    m_lastAction[12] = 0x00;

    m_lastActionLen = 13;
    return;
}

void TradeControl::enableSendBst(void)
{
    if (m_TradeControlNum > 1)
    {
        m_forbidBst = false;
    }

    return;
}

void TradeControl::forbidRfSendBst(int rfsn)
{
    m_rfsn = rfsn;
    if (m_seleRfsn != rfsn)
    {
        m_scheduler->forbidRfSendBst(m_seleRfsn, false);
        m_scheduler->forbidRfSendBst(rfsn, true);
    }
}

void TradeControl::matchVst(void)
{
    
    recv_buffer_t *recvVst = NULL;

    if(m_scheduler->m_recvVsts.empty()) 
    {
        return;
    }

    recvVst = m_scheduler->m_recvVsts.front();
    m_scheduler->m_recvVsts.pop_front();
  

    if(!decodeVst(recvVst)) 
    {
        goto END;
    }

    m_rfsn = recvVst->rfsn;
    m_rssi = recvVst->rssi;
    m_seleRfsn = recvVst->rfsn;
    m_startTime = get_jiffies();
    m_forbidBst = true;
    m_scheduler->forbidRfSendBst(m_rfsn, true);  
    
    if(m_scheduler->m_tagCache->findTag(m_macId))
    {
        goIgnore();
    }
    else if(isBjObu()
            && ((m_esamVersion == 0x00)
            || (m_esamVersion == 0x10)
            || (m_esamVersion == 0x11)
            || (m_esamVersion == 0x12) ))  // add BjObu esamVersion = 0x12
    {
        goIgnore();
    }
    else
    {
    #if 1 // get coordinate information from VST
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B2Frame_state;  
                   
    #else // send cmd to get coordinate information 
        m_state = send_get_location_state;
    #endif
        
        logm_debug("macid:%08x match vst success\n", m_macId);
    }    

END:
    delete recvVst;
    return;
}


void TradeControl::sendGetSecure()
{
    encodeGetSecure();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_getsecure_state;

    return;
}


void TradeControl::recvGetSecure(void)
{
    recv_buffer_t *recv_buffer = NULL;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;
    unsigned int rand_time;

    for(iter=m_scheduler->m_recvBuffers.begin(); iter!= m_scheduler->m_recvBuffers.end(); ++iter)  
    {
        recv_buffer = (*iter);
        ret = decodeGetSecure(recv_buffer);        
        if(NOTMATCH == ret)
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;
      
        m_state = send_descryption_state;
        m_psam_StartTime = get_jiffies();
      
        return;
    }
    
     /*set send getscure interval is rand*/
    rand_time = rand() % 10 + (m_scheduler->m_config->m_obuGetsecureInterval - 5);
    
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, rand_time, 1) != 0)
    {
       // logm_debug("go to end\n");
      //  goTradeEnd(DSRC_NO_COMM_TIMEOUT);
         m_state = report_and_query_ack_trade_state;
         m_reporttradeState = send_trade_B3Frame_state;
                      
    }

    return;
}


void TradeControl::sendDescryption(void)
{
    unsigned char fensanyinzi[16];

    memset(m_terminal_id, 0, 6);

    memcpy(fensanyinzi, &m_sysInfo[10], 8);
    memcpy(&fensanyinzi[8], &m_sysInfo[0], 4);
    memcpy(&fensanyinzi[12], &m_sysInfo[0], 4);

    /* try to get universal psam */
    m_psam = m_scheduler->getPsam(universal_psam);

    /* if get failed, try to get gb_tdes_psam */
    if((NULL == m_psam) && (m_psam_descrypt_KeyVersion == PSAM_DESCRYPT_VEHICLE_3DES))
    {
        m_psam = m_scheduler->getPsam(gb_tdes_psam);
    }

    if(NULL != m_psam)
    {
        memcpy(m_terminal_id, m_psam->m_terminalID, 6);
        m_psam->sendDescryptVehicle(fensanyinzi, m_psam_descrypt_KeyVersion, m_vehicle);
        m_state = recv_descryption_state;
        m_psam_StartTime = get_jiffies();
    }
    else
    {
        if(PSAM_check_timeout(PSAM_DESCRYP_VEHICLE_FAIL, PSAM_OPERATE_TIMEOUT_INTERVAL))
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B3Frame_state;
           // m_reporttradeState = send_trade_B2Frame_state;

            logm_debug("get PSAM failed\n");
        }
    }
    return;
}

void TradeControl::recvDescryption(void)
{
    int ret;

    ret = m_psam->recvDescryptVehicle(m_descryptedVehicle);
    if(ret == 0) 
    {      
                 
        m_EF04RdStatus = 0x00;
        if(m_scheduler->m_InitEf04Opt == 0x00)//0表示不读取
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B3Frame_state;
        }
        else
        {
            m_state = send_read_ef04_state;
            m_reporttradeState = trade_proc_undefine; 
        }
    
    } 
    else if(ret == 1) 
    {
        if(NULL != m_psam) 
        {
            m_scheduler->putPsam(m_psam);
            m_psam = NULL;
        }

        
        m_Trade_State_Code = PSAM_DESCRYP_VEHICLE_FAIL;

        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B3Frame_state;
        //m_reporttradeState = send_trade_B2Frame_state;
        return;
    }

    if(PSAM_check_timeout(PSAM_DESCRYP_VEHICLE_FAIL, PSAM_OPERATE_TIMEOUT_INTERVAL))
    {
          m_state = report_and_query_ack_trade_state;
          m_reporttradeState = send_trade_B3Frame_state;
         // m_state = send_read_ef04_state;
         // m_reporttradeState = trade_proc_undefine;
           
    }
    return;
}


void TradeControl::sendInitPurchase()
{
    encodeInitPurchase();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_init_for_purchase_state;
    
    return;
}

void TradeControl::recvInitPurchase()
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter = m_scheduler->m_recvBuffers.begin();
        iter != m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeInitPurchase(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(FAIL == ret)
        {            
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B5Frame_state;
        }
        else
        {            
            m_state = send_calc_purchase_mac1_state;
            m_psam_StartTime = get_jiffies();
        }
        return;
    }    

    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    }
}

void TradeControl::sendOnlyInitPurchase()
{
    encodeOnlyInitPurchase();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_only_init_for_purchase_state;
    
    return;
}

void TradeControl::recvOnlyInitPurchase()
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter = m_scheduler->m_recvBuffers.begin();
        iter != m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeOnlyInitPurchase(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(FAIL == ret)
        {            
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B5Frame_state;
        }
        else
        {            
            m_state = send_get_Tac_And_Balance_state;
            m_psam_StartTime = get_jiffies();
        }
        return;
    }    

    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    }
}

void TradeControl::sendGetTACandBalance(void)
{
    encodeGetTACandBalance();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_get_Tac_And_Balance_state;

    return;
}

void TradeControl::recvGetTACandBalance(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeGetTACandBalance(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(m_OpMode == 0x00)
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B5Frame_state;
        }
        else if(m_OpMode == 0x01)
        {
            m_state = send_write_ef04_state;
            m_reporttradeState = trade_proc_undefine;
        }
        
        return;
    }

    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuReadFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    }
    
    return;
}

//calculate the mac1 by PSAM,  init PSAM for Purchase
void TradeControl::sendCalcPurchaseMac1()
{
    unsigned char tradeData[20];
    unsigned char keyDeliveryFactor[16];

    memcpy(&tradeData[0], m_purchaseRandom, 4);
    memcpy(&tradeData[4], m_icc_tradesn, 2);
    memcpy(&tradeData[6], m_transaction_fees, 4);
    tradeData[10] = 0x09; // trade type
    memcpy(&tradeData[11], &m_purchaseDateTime[0], 4); //date
    memcpy(&tradeData[15], &m_purchaseDateTime[4], 3); //time
    tradeData[18] = m_purchaseKeyVersion;
    tradeData[19] = m_purchaseKeyAlgorithID;

    memcpy(keyDeliveryFactor, &m_file15[12], 8);
    memcpy(&keyDeliveryFactor[8], &m_file15[0], 4);
    memcpy(&keyDeliveryFactor[12], &m_file15[0], 4);

    if(NULL != m_psam)
    {
        m_psam->sendGetPurchaseMac1(tradeData, keyDeliveryFactor);
        m_state = recv_calc_purchase_mac1_state;
        m_psam_StartTime = get_jiffies();
    }
    else
    {
        if(PSAM_check_timeout(PSAM_INIT_PURCHASE_FAIL, PSAM_OPERATE_TIMEOUT_INTERVAL))        
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B5Frame_state;
        }
    }

    return;
}

void TradeControl::recvCalcPurchaseMac1()
{
    int ret;

    ret = m_psam->recvGetPurchaseMac1(m_encryption);
    if(0 == ret) 
    {        
        memcpy(m_psam_transSerial, m_psam->m_transSerial, 4);
        m_state = send_purchase_state;
    } 
    else if(1 == ret)
    {       
        if(NULL != m_psam)
        {
            m_scheduler->putPsam(m_psam);
            m_psam = NULL;
        }        
        m_Trade_State_Code = PSAM_INIT_PURCHASE_FAIL;
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
        return;
    }

    if(PSAM_check_timeout(PSAM_INIT_PURCHASE_FAIL, PSAM_OPERATE_TIMEOUT_INTERVAL))
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    }
    return;
}

void TradeControl::sendPurchase()
{
    encodePurchase();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_purchase_state;
    return;
}

void TradeControl::recvPurchase()
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter = m_scheduler->m_recvBuffers.begin();
        iter != m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodePurchase(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

    #if 1
        if(FAIL == ret)
        {   
            if((m_scheduler->m_WorkMode == LANE_MODE_ENTRANCE) && (OperateEF04Flag != 0x02))
            {
                m_Trade_State_Code = WRITE_EF04_SUCCESS_PURCHASE_FAIL;
            }
            else if(OperateEF04Flag == 0x02)
            {
                m_Trade_State_Code = ONLY_CPU_CARD_DEBIT_PURCHASE_FAIL;
            }
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B5Frame_state;
        }
        else
        {
            m_state = send_auth_purchase_mac2_state;
            m_psam_StartTime = get_jiffies();
        }
    #else
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    #endif
        return;
    }
    
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
        m_Trade_State_Code = CHARGE_FAIL;
    }
}

// credit sam for purchase
void TradeControl::sendAuthPurchaseMac2(void)
{ 
    unsigned char creditMac2[4];
    memcpy(creditMac2, m_tradePurchaseMac2, 4);

    if(NULL != m_psam)
    {
        m_psam->sendCreditPurchaseMac2(creditMac2);
        m_state = recv_auth_purchase_mac2_state;
        
        
        
    }
    else
    {
        if(PSAM_check_timeout(PSAM_AUTHEN_MAC2_FAIL, PSAM_OPERATE_TIMEOUT_INTERVAL))
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B5Frame_state;
        }
    }

    return;
}

void TradeControl::recvAuthPurchaseMac2(void)
{
    int ret;

    ret = m_psam->recvCreditPurchaseMac2();
    if(0 == ret) 
    {

        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;   
    } 
    else if(1 == ret)
    {
        if(NULL != m_psam)
        {
            m_scheduler->putPsam(m_psam);
            m_psam = NULL;
        }
        m_Trade_State_Code = PSAM_AUTHEN_MAC2_FAIL;
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
        return;
    }

    if(PSAM_check_timeout(PSAM_AUTHEN_MAC2_FAIL, PSAM_OPERATE_TIMEOUT_INTERVAL))
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    }
    return;
}

void TradeControl::sendReadIccFiles(void)
{
    encodeReadIccFiles();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_read_icc_files_state;

    return;
}

void TradeControl::recvReadIccFiles(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeReadIccFiles(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;
        if(FAIL == ret)
        {
            //goTradeEnd(READ_ICC_FILES_TIMEOUT);
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B4Frame_state;
        }
        else
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B4Frame_state;
        }
        return;
    }

    //check_timeout(READ_ICC_FILES_TIMEOUT);
    //_resendAction(m_scheduler->m_config->m_obuReadFileInterval, READ_ICC_FILES_TIMEOUT);

    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuReadFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B4Frame_state;
    }
    
    return;
}

void TradeControl::sendReadFile19andBalance(void)
{
    encodeReadFile19andBalance();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_read_file19_and_balance_state;

    return;
}

void TradeControl::recvReadFile19andBalance(void)
{
    recv_buffer_t *recv_buffer = NULL;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeReadFile19andBalance(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }
        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn; 
      
        
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B4Frame_state;
             
                
        return;
    }

    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuReadFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B4Frame_state;
    }
    
    return;
}


void TradeControl::sendClearEf04(void)
{
    encodeClearEf04();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_clear_ef04_state;
    return;
}

void TradeControl::recvClearEf04(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter)
    {
        recv_buffer = (*iter);
        ret = decodeClearEf04(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;
        if((m_scheduler->m_WorkMode == LANE_MODE_ENTRANCE))
        {
            if(FAIL == ret)
            {
                m_reporttradeState = send_trade_B5Frame_state;  
                m_state = report_and_query_ack_trade_state; 
            }
            else 
            {
                m_state = send_init_for_purchase_state;    
            }
        }
        else 
        {
            m_state = send_setmmi_state;
        }
        
        return;
    }

    check_timeout(CLEAR_EF04_FAIL);
    _resendAction(m_scheduler->m_config->m_obuWriteFileInterval, CLEAR_EF04_FAIL);

    return;
}

void TradeControl::sendWriteEf04Exit(void)
{
    encodeWriteEf04Exit();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_write_ef04_exit_state;
    return;
}

void TradeControl::recvWriteEf04Exit(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeWriteEf04Exit(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(ret == FAIL)
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B9Frame_state;
        }
        else
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B9Frame_state;
        }
        
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
       
       if(m_EF04RdStatus ==0x00)
       {
            m_Trade_State_Code = EF04_RD_SUCCESS_WD_FAIL;
       }
       else
       {
            m_Trade_State_Code = EF04_RW_FAIL;
       }
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B9Frame_state;
    }
    return;
}


void TradeControl::sendWriteEf04inExit(void)
{
    encodeWriteEf04inExit();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_write_ef04_exit_in_state;
    return;
}

void TradeControl::recvWriteEf04inExit(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeWriteEf04inExit(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(ret == FAIL)
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B9Frame_state;
        }
        else
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B9Frame_state;
        }
        
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
       if(m_EF04RdStatus ==0x00)
        {
             m_Trade_State_Code = EF04_RD_SUCCESS_WD_FAIL;
        }
        else
        {
            m_Trade_State_Code = EF04_RW_FAIL;
        }
       
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B9Frame_state;
    }
    return;
}


void TradeControl::sendWriteEf04Exit1(void)
{
    encodeWriteEf04Exit1();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_write_ef04_exit1_state;
    return;
}

void TradeControl::recvWriteEf04Exit1(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeWriteEf04Exit1(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(ret == FAIL)
        {
            m_state = send_setmmi_state;
            m_reporttradeState = trade_proc_undefine;
        }
        else
        {
            if(m_ef04len_write_c7 != 0)
            {
                m_state = send_write_ef04_exit2_state;
            }
            else
            {
                m_state = send_setmmi_state;
            }
            m_reporttradeState = trade_proc_undefine;
        }
        
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
        m_state = send_setmmi_state;
        m_reporttradeState = trade_proc_undefine;
    }
    return;
}

void TradeControl::sendWriteEf04Exit2(void)
{
    encodeWriteEf04Exit2();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_write_ef04_exit2_state;
    return;
}

void TradeControl::recvWriteEf04Exit2(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeWriteEf04Exit2(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

       
        m_state = send_setmmi_state;
        m_reporttradeState = trade_proc_undefine;
        
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
        m_state = send_setmmi_state;
        m_reporttradeState = trade_proc_undefine;
    }
    return;
}

void TradeControl::sendWriteEf04(void)
{
    encodeWriteEf04();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_write_ef04_state;
    return;
}

void TradeControl::recvWriteEf04(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeWriteEf04(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

        if(OperateEF04Flag == 0x00)
        {
                      
           // if(ret == FAIL)
           // {
           //     m_state = report_and_query_ack_trade_state;
           //     m_reporttradeState = send_trade_B5Frame_state;
           // }
          //  else
           // {
                m_state = send_init_for_purchase_state;
                m_reporttradeState = trade_proc_undefine;
           // }
        }
        else if(OperateEF04Flag == 0x01)
        {
            if(ret == FAIL)
            {
                m_Trade_State_Code = ONLY_CLEAR_EF04_FAIL;
                m_state = report_and_query_ack_trade_state;
                m_reporttradeState = send_trade_B5Frame_state;
            }
            else
            {
                m_state = report_and_query_ack_trade_state;
                m_reporttradeState = send_trade_B5Frame_state;
            }           
        }
        
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuWriteFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B5Frame_state;
    }
    return;
}

void TradeControl::sendReadEf04(void)
{
    encodeReadEf04();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_read_ef04_state;
    return;
}

void TradeControl::recvReadEf04(void)
{
    recv_buffer_t *recv_buffer = NULL;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeReadEf04(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }
        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;
        if(FAIL == ret)
        {
            m_Trade_State_Code = TRADE_NORMAL;
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B3Frame_state;
        }
        else
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B3Frame_state;
        }
        
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuReadFileInterval, 1) != 0)
    {
        m_EF04RdStatus = 0x01;
        m_Trade_State_Code = TRADE_NORMAL;
        memset(m_Ef04Info, 0, m_scheduler->m_initef04len);
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B3Frame_state;
    }
    return;
}

void TradeControl::sendReadEf04Exit(void)
{
    encodeReadEf04Exit();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_read_ef04_exit_state;
    return;
}

void TradeControl::recvReadEf04Exit(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeReadEf04Exit(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;
        if(UpdateEF04Flag == 0x00)
        {
            m_state = send_write_ef04_exit_in_state;
            m_reporttradeState = trade_proc_undefine;

        }
        else
        {
            m_state = send_write_ef04_exit_state;
            m_reporttradeState = trade_proc_undefine;
        }
              
        return;
    }
    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuReadFileInterval, 1) != 0)
    {
        if(UpdateEF04Flag == 0x00)
        {
            m_state = send_write_ef04_exit_in_state;
            m_reporttradeState = trade_proc_undefine;

        }
        else
        {
            m_state = send_write_ef04_exit_state;
            m_reporttradeState = trade_proc_undefine;
        }

    }
    return;
}




void TradeControl::sendReadIccFile19(void)
{
    encodeReadIccFile19();
    sendActionCmd();

    m_repeatNum = 0;
    m_lastSend = get_jiffies();
    m_state = recv_read_icc_file19_state;

    return;
}

void TradeControl::recvReadIccFile19(void)
{
    recv_buffer_t *recv_buffer;
    std::vector<recv_buffer_t *>::iterator iter;
    int ret;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        ret = decodeReadIccFile19(recv_buffer);
        if(NOTMATCH == ret) 
        {
            continue;
        }

        recv_buffer->length = 0;        
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;

    #if 0
        if(FAIL == ret)
        {            
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = recv_ack_B3Frame_state;
        }
        else
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = recv_ack_B3Frame_state;
        }
    #else
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B4Frame_state;
    #endif

        return;
    }   

    if(check_timeout_and_repeatNum(DSRC_NO_COMM_TIMEOUT, m_scheduler->m_config->m_obuReadFileInterval, 1) != 0)
    {
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_B4Frame_state;
    }
    
    return;
}
void TradeControl::sendFakeD0FrameToPC()
{
    unsigned char send_buffer[128];
    unsigned char send_bufferLen;    
    int ret;
    
	m_LocationX = 10;
    m_LocationY = 800;

    send_buffer[0] = 0xD0; // location
    send_buffer[1] = (m_macId >> 24);
    send_buffer[2] = (m_macId >> 16);
    send_buffer[3] = (m_macId >> 8);
    send_buffer[4] = m_macId;
    send_buffer[5] = 0xb2; // FrameType
    send_buffer[6] = 0x00; // 0->success, not 0 -> fail
    memcpy(&send_buffer[7], &m_LocationX, sizeof(m_LocationX));
	memcpy(&send_buffer[11], &m_LocationY, sizeof(m_LocationY));

    send_bufferLen = 15; // length of frame	

    
    logm_debug("sendD0FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendD0FrameToPC by internet Error! %d\n", ret);
        logm_err("sendD0FrameToPC by internet Error!\n");
    }
    

    #if 1
    m_reporttradeState = send_trade_B2Frame_state;
    #else
    m_state = send_getsecure_state;
    m_reporttradeState = trade_proc_undefine;
    #endif
    return;
}
void TradeControl::sendD0FrameToPC()
{
    unsigned char send_buffer[128] = {0x00};
    unsigned char send_bufferLen;    
    int ret;

    if((m_LocationX > -850) && (m_LocationX < 850) && (m_LocationY < 2000) && (m_LocationY > -300))
    {    
        if((m_scheduler->m_config->m_etc_mtc == ETC_GRAT) || (m_scheduler->m_config->m_etc_mtc == ETC_COIL))
        {
             cal_average_coordinate(m_macId, &m_LocationX, &m_LocationY, &m_RSSI, &m_rssi_num);
        }
        else if(m_scheduler->m_config->m_etc_mtc == MTC)
        {
             cal_average_coordinate_mtc(m_macId, &m_LocationX, &m_LocationY, &m_RSSI, &m_rssi_num);
        }

        logm_debug("after average the X Coordinate is %dcm, the Y Coordinate is %dcm\n", m_LocationX, m_LocationY);
        
        if(m_coord_average_over == 0)
        {
            m_research_obu = 0x01;
            goTradeEnd(PC_CMD_STOP_TRADE);
            return;
        }

        if(m_scheduler->m_config->m_etc_mtc != MTC)
        {
            send_bst_interval_to_anotherpc();
        } 
    }
    else
    {
        logm_debug("no average the X Coordinate is %dcm, the Y Coordinate is %dcm\n", m_LocationX, m_LocationY);
    }
    
    /* according to y set ant work mode */
    if(m_scheduler->m_config->m_rfsmode == NEWANT)
    {
        if((m_LocationX > -250) && (m_LocationX < 250))
        {
            setAntWorkMode(m_LocationY);
        }
    }

    if( (m_scheduler->m_config->m_coil_trigger_enable)
        &&  (m_LocationY <= m_scheduler->m_config->m_coil_trigger_confine) )
    {
        if(m_scheduler->m_coil_trigger_flag == 0)
        {
            logm_debug("DiGan Coil is not triggered!\n");
            m_research_obu = 0x01;
            goTradeEnd(DG_COIL_NOT_TRIGGER);
            return;
        }
    }

    /* if open location_limit */
    if(m_scheduler->m_config->m_location_limit)
    {
        if((m_LocationX > m_scheduler->m_config->m_location_X1) 
            || (m_LocationX < m_scheduler->m_config->m_location_X2)
            || (m_LocationY > m_scheduler->m_config->m_location_Y_max)
            || (m_LocationY < m_scheduler->m_config->m_location_Y_min) )
        {
            logm_debug("Coordinate beyond the confines\n");
            m_research_obu = 0x01;
            goTradeEnd(PC_CMD_STOP_TRADE);
            return;
        }
        else if(m_LocationY >= m_scheduler->m_config->m_location_sub_Y)
        {
            if( (m_LocationX > m_scheduler->m_config->m_location_sub_X1)
                || (m_LocationX < m_scheduler->m_config->m_location_sub_X2) )
            {
                logm_debug("Coordinate Abnormal(beyond sub-confines)\n");
                m_research_obu = 0x01;
                goTradeEnd(PC_CMD_STOP_TRADE);
                return;
            }
        }
    }    
	
    send_buffer[0] = 0xD0; // location
    send_buffer[1] = (m_macId >> 24);
    send_buffer[2] = (m_macId >> 16);
    send_buffer[3] = (m_macId >> 8);
    send_buffer[4] = m_macId;
    send_buffer[5] = 0xb2; // FrameType
    send_buffer[6] = 0x00; // 0->success, not 0 -> fail
    memcpy(&send_buffer[7], &m_LocationX, sizeof(m_LocationX));
	memcpy(&send_buffer[11], &m_LocationY, sizeof(m_LocationY));

    send_bufferLen = 15; // length of frame	

    
    logm_debug("sendD0FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendD0FrameToPC by internet Error! %d\n", ret);
        logm_err("sendD0FrameToPC by internet Error!\n");
    }
    

    if(m_scheduler->m_config->m_etc_mtc != MTC)
    {
        m_reporttradeState = send_trade_B2Frame_state;
    }
    else
    {
        m_state = send_getsecure_state;
        m_reporttradeState = trade_proc_undefine;
    }
    return;
}

void TradeControl::sendB2FrameToPC()
{
    unsigned char send_buffer[128]  = {0x00} ;
    unsigned char send_bufferLen;
    int ret;

     if((m_LocationX > -850) && (m_LocationX < 850) && (m_LocationY < 2000) && (m_LocationY > -300))
    {    
        if((m_scheduler->m_config->m_etc_mtc == ETC_GRAT) || (m_scheduler->m_config->m_etc_mtc == ETC_COIL))
        {
            cal_average_coordinate(m_macId, &m_LocationX, &m_LocationY, &m_RSSI, &m_rssi_num);
        }
        else if(m_scheduler->m_config->m_etc_mtc == MTC)
        {
            cal_average_coordinate_mtc(m_macId, &m_LocationX, &m_LocationY, &m_RSSI, &m_rssi_num);
        }

        logm_debug("after average the X Coordinate is %dcm, the Y Coordinate is %dcm\n", m_LocationX, m_LocationY);
        
        if(m_coord_average_over == 0)
        {
            m_research_obu = 0x01;
            goTradeEnd(PC_CMD_STOP_TRADE);
            return;
        }

        if(m_scheduler->m_config->m_etc_mtc != MTC)
        {
            send_bst_interval_to_anotherpc();
        } 
    }
    else
    {
        logm_debug("no average the X Coordinate is %dcm, the Y Coordinate is %dcm\n", m_LocationX, m_LocationY);
    }
    
    /* according to y set ant work mode */
    if(m_scheduler->m_config->m_rfsmode == NEWANT)
    {
        if((m_LocationX > -250) && (m_LocationX < 250))
        {
            setAntWorkMode(m_LocationY);
        }
    }

    if( (m_scheduler->m_config->m_coil_trigger_enable)
        &&  (m_LocationY <= m_scheduler->m_config->m_coil_trigger_confine) )
    {
        if(m_scheduler->m_coil_trigger_flag == 0)
        {
            logm_debug("DiGan Coil is not triggered!\n");
            m_research_obu = 0x01;
            goTradeEnd(DG_COIL_NOT_TRIGGER);
            return;
        }
    }

    /* if open location_limit */
    if(m_scheduler->m_config->m_location_limit)
    {
        if((m_LocationX > m_scheduler->m_config->m_location_X1) 
            || (m_LocationX < m_scheduler->m_config->m_location_X2)
            || (m_LocationY > m_scheduler->m_config->m_location_Y_max)
            || (m_LocationY < m_scheduler->m_config->m_location_Y_min) )
        {
            logm_debug("Coordinate beyond the confines\n");
            m_research_obu = 0x01;
            goTradeEnd(PC_CMD_STOP_TRADE);
            return;
        }
        else if(m_LocationY >= m_scheduler->m_config->m_location_sub_Y)
        {
            if( (m_LocationX > m_scheduler->m_config->m_location_sub_X1)
                || (m_LocationX < m_scheduler->m_config->m_location_sub_X2) )
            {
                logm_debug("Coordinate Abnormal(beyond sub-confines)\n");
                m_research_obu = 0x01;
                goTradeEnd(PC_CMD_STOP_TRADE);
                return;
            }
        }
    }
    /* send transcation obu inform to adjacent */
    m_scheduler->send_obu_coordinate_rssi_num_message(m_macId, m_LocationX, m_LocationY, m_RSSI, m_rssi_num);

    if(m_Trade_State_Code != TRADE_NORMAL)
    {
        send_buffer[0] = 0xB2; // system information frame of OBU
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = m_Trade_State_Code; // error code
        memset(&send_buffer[6], 0, 29);
        send_bufferLen = 35; // length of frame
    }
    else
    {
        send_buffer[0] = 0xB2; // system information frame of OBU
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x00; // error code
        memcpy(&send_buffer[6], &m_sysInfo[0], 8); // (ESAM system information) IssuerIdentifier
        send_buffer[14] = 0x01; //contractType
        send_buffer[15] = 0x01; //contractVersion
        memcpy(&send_buffer[16], &m_sysInfo[10], 8); //(ESAM system information) SerialNumber
        memcpy(&send_buffer[24], &m_sysInfo[18], 8); //(ESAM system information) DateofIssue and DateofExpire
        send_buffer[32] = m_equipmentCV;   // --------> EquipmentStatus
        memcpy(&send_buffer[33], m_obuStatus, 2); // OBU status
             
        send_bufferLen = 35; // length of frame        
    }

    logm_debug("sendB2FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendB2FrameToPC Error! %d\n", ret);
        logm_err("sendB2FrameToPC Error!\n");
    }
  
    m_lastSendFrameTime = get_jiffies();
    m_sendTradeFrameCount++;

#if 0 	
	m_state = send_getsecure_state;
    m_reporttradeState = trade_proc_undefine;
#else 
    m_reporttradeState = recv_ack_B2Frame_state;
#endif

    return;
}


void TradeControl::recvB2AckFromPC()
{
    int recv_len;
    unsigned char recv_buffer[256];
    

    recv_len = zmq_recv(m_reporterSocket_recv, recv_buffer, 256, ZMQ_DONTWAIT);
    if(recv_len <= 0)
    {    
        if(check_waitPCAck_timeout(m_lastSendFrameTime))
        {
            #if 0
            if(check_sendPCFrame_count(m_sendTradeFrameCount))
            {
                logm_debug("receive B2 Ack TimeOut count is overflow! >>>> Trade stop! \n");
                goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
            }
            else
            {
                m_reporttradeState = send_trade_B2Frame_state;
                logm_debug("receive B2 Ack From Comm_process TimeOut! >>>> Retry to Send! \n");
            }
            #else
                logm_debug("receive B2 Ack TimeOut ! >> Trade stop! \n");
                goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
            #endif            
        }
        return;
    }

       
    logm_debug("recvB2AckFromPC %d <-- ", recv_len);
    logm_debug_buffer(recv_buffer, recv_len);

    if(memcmp((unsigned char *)&m_macId, &recv_buffer[1], 4) != 0) // judge OBU MAIC_ID
    {
        logm_debug("receive B2 Ack From PC, OBU_MAC Not Match \n");
        return;
    }

    if(recv_buffer[0] == 0xC1)  // continue to trade
    {
        m_state = send_getsecure_state;
        m_reporttradeState = trade_proc_undefine;  
        m_sendTradeFrameCount = 0; // set Count as 0
        m_Trade_State_Code = TRADE_NORMAL;                 
    } 
        
   
    else if(recv_buffer[0] == 0xC2)
    {        
        //m_research_obu = 0x01;
        goTradeEnd(PC_CMD_STOP_TRADE);
    }
   /*
    else
    {
        m_recv_error_instruct = recv_buffer[0];
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_error_Frame_state;
    }
*/
    return;
}

void TradeControl::sendB3FrameToPC()
{
    unsigned char send_buffer[256];
    unsigned char send_bufferLen;
    int ret;
    unsigned char instep_status;
    if(m_Trade_State_Code != TRADE_NORMAL)
    {
        send_buffer[0] = 0xB3; // vehicle information frame of OBU
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = m_Trade_State_Code; // error code
        memset(&send_buffer[6], 0, 79);
        send_buffer[85] = m_EF04RdStatus;
        memset(&send_buffer[86], 0, m_scheduler->m_initef04len);
        send_bufferLen = 86 + m_scheduler->m_initef04len;
    }
    else
    {
        send_buffer[0] = 0xB3; // vehicle information frame of OBU
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x00; // error code
        memcpy(&send_buffer[6], m_descryptedVehicle, 79); // vehicle information
        
         if(m_scheduler->m_InitEf04Opt == 0x00)
         {
             send_bufferLen = 85;

         }
         else
         {
             send_buffer[85] = m_EF04RdStatus;
            if(m_EF04RdStatus!= 0)
            {
                memset(&send_buffer[86], 0, m_scheduler->m_initef04len);
            }
            else 
            {
               memcpy(&send_buffer[86], m_Ef04Info, m_scheduler->m_initef04len);
            }
            send_bufferLen = 86 + m_scheduler->m_initef04len;
            logm_debug("m_initef04len is : %d\n", m_scheduler->m_initef04len);

         }
        
    }  

    logm_debug("sendB3FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
       logm_debug("sendB3FrameToPC Error! %d\n", ret); 
    }
   
    m_lastSendFrameTime = get_jiffies();
    m_sendTradeFrameCount++;

#if 0	
	m_state=send_read_icc_file19_state;
    m_reporttradeState = trade_proc_undefine;
#else
    m_reporttradeState = recv_ack_B3Frame_state;
    instep_status = 0x01;
    m_scheduler->send_instep_obuId_to_adjacent(instep_status, m_macId);
#endif
    return;
}

void TradeControl::recvB3AckFromPC()
{ 
    int recv_len;
    unsigned char recv_buffer[256];
    
    recv_len = zmq_recv(m_reporterSocket_recv, recv_buffer, 256, ZMQ_DONTWAIT);
    if(recv_len <= 0)
    {
        if(check_waitPCAck_timeout(m_lastSendFrameTime))
        {
            #if 0
            if(check_sendPCFrame_count(m_sendTradeFrameCount))
            {
                logm_debug("receive B3 Ack TimeOut count is overflow! >>>> Trade stop! \n");
                goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
            }
            else
            {
                m_reporttradeState = send_trade_B3Frame_state;
                logm_debug("receive B3 Ack From Comm_process TimeOut! >>>> Retry to Send! \n");
            }  
            #else
                logm_debug("receive B3 Ack TimeOut ! >> Trade stop! \n");
                goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
            #endif          
        }
        return;
    }    

        
    logm_debug("recvB3AckFromPC %d <-- ", recv_len);
    logm_debug_buffer(recv_buffer, recv_len);

    if(memcmp((unsigned char *)&m_macId, &recv_buffer[1], 4) != 0) // judge OBU MAIC_ID
    {
        logm_debug("receive B3 Ack From PC, OBU_MAC Not Match \n");
        return;
    }

    if(recv_buffer[0] == 0xC1)  // continue to trade
    {
        if(((m_obuStatus[0] >> 7) & 0x01) == 0x01) //标签无卡
        {
           
                m_Trade_State_Code = CPU_CARD_EXIT;
                m_state = report_and_query_ack_trade_state;
                m_reporttradeState = send_trade_B4Frame_state;
                logm_err("no cpu card!\n");
           
        }
        else
        {
            m_state = send_read_file19_and_balance_state;
            m_reporttradeState = trade_proc_undefine;
            m_sendTradeFrameCount = 0; // set Count as 0
            m_Trade_State_Code = TRADE_NORMAL;
        } 
         
    }
    else if(recv_buffer[0] == 0xC2 ) // research OBU
    {
        goTradeEnd(PC_CMD_STOP_TRADE);
    }
    else
    {
        m_recv_error_instruct = recv_buffer[0];
        m_state = report_and_query_ack_trade_state;
        m_reporttradeState = send_trade_error_Frame_state;
    }
    
    return;
}

void TradeControl::sendB4FrameToPC()
{
    unsigned char send_buffer[256];
    unsigned char send_bufferLen;
    int ret;
    
    logm_debug("begin send B4 to PC\n");
    if(m_Trade_State_Code != TRADE_NORMAL)
    {
        send_buffer[0] = 0xB4; // IC_card information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = m_Trade_State_Code; // error code
        memset(&send_buffer[6], 0, 97);
        send_bufferLen = 103;
              
    }
    else 
    {
        send_buffer[0] = 0xB4; // IC_card information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x00; // error code
          
        memcpy(&send_buffer[6], m_icc_balance, 4); // IIC remain momey --> balance file_0002
        memcpy(&send_buffer[10], m_file15, 50); // ICC file_0015--> issue data file
        memcpy(&send_buffer[60], m_file19, 43); // ICC file_0019--> purchase record file
      
    }
    logm_debug("sendB4FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendB4FrameToPC Error! %d\n", ret);
        logm_err("sendB4FrameToPC Error!\n");
    }
   
    m_lastSendFrameTime = get_jiffies();
    m_sendTradeFrameCount++;
    
    m_reporttradeState = recv_ack_B4Frame_state;
    return;
}

void TradeControl::recvB4AckFromPC()
{
    int recv_len;
    unsigned char recv_buffer[256];
    memset(recv_buffer,0,256);
    recv_len = zmq_recv(m_reporterSocket_recv, recv_buffer, 256, ZMQ_DONTWAIT);
    if(recv_len <= 0)
    {
        if(check_waitPCAck_timeout(m_lastSendFrameTime))
        {
            logm_debug("receive B4 Ack TimeOut ! >> Trade stop! \n");
            goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);         
        }        
        return;
    }    

        
    logm_debug("recvB4AckFromPC %d <-- ", recv_len);
    logm_debug_buffer(recv_buffer, recv_len);

    if(memcmp((unsigned char *)&m_macId, &recv_buffer[1], 4) != 0) // judge OBU MAIC_ID
    {
        logm_debug("receive B4 Ack From PC, OBU_MAC Not Match \n");
        return;
    }
    
    // continue to trade, Receive C6 Frame
    // ****  entry mode ******
    if(recv_buffer[0] == 0xC6)
    {    
        OperateEF04Flag = recv_buffer[5];

        memcpy(m_transaction_fees, &recv_buffer[6], 4); // Consume Money   
        memcpy(m_file19, &recv_buffer[10], 43); // station information
        memcpy(m_purchaseDateTime, &recv_buffer[53], 7); // ICC purchase Date time
        memcpy(m_Ef04Off, &recv_buffer[60], 2);
        memcpy(m_Ef04Len, &recv_buffer[62], 2);
        m_ef04len = m_Ef04Len[0] * 256 + m_Ef04Len[1];
        if(m_ef04len != 0)
        {
            memcpy(m_Ef04Info, &recv_buffer[64], m_ef04len);
            logm_debug("Ef04info is :");
            logm_debug_buffer(m_Ef04Info, m_ef04len);
        }
        logm_debug("OBUtradeType is : %d\n", OperateEF04Flag);
        logm_debug("Ef04Off is :");
        logm_debug_buffer(m_Ef04Off, 2);
        logm_debug("Ef04Len is :");
        logm_debug_buffer(m_Ef04Len, 2);

              

        if(( (OperateEF04Flag == 0x00)) || (OperateEF04Flag == 0x01))
        {
            if((m_ef04len == 0) && (OperateEF04Flag == 0x00))
            {
                m_state = send_init_for_purchase_state;
                m_reporttradeState = trade_proc_undefine;
            }
            else if((m_ef04len == 0) && (OperateEF04Flag == 0x01))
            {
                m_reporttradeState = send_trade_B5Frame_state;
            }
            else
            {
                m_state = send_write_ef04_state;
                m_reporttradeState = trade_proc_undefine;
            }
            m_sendTradeFrameCount = 0; // set Count as 0
            m_Trade_State_Code = TRADE_NORMAL;

            m_scheduler->send_bst_interval_status(0x01, 0x20);
        }
        else if(OperateEF04Flag == 0x02)
        {
            m_state = send_init_for_purchase_state;
            m_reporttradeState = trade_proc_undefine;

            m_sendTradeFrameCount = 0; // set Count as 0
            m_Trade_State_Code = TRADE_NORMAL;

            m_scheduler->send_bst_interval_status(0x01, 0x20);
        }   
    }
    else if(recv_buffer[0] == 0xC7) // Get TAC
    {    
       // memcpy(m_purchaseDateTime, &recv_buffer[6], 7); // ICC purchase Date time
      //  memcpy(m_file19, &recv_buffer[13], 43); // station information    
        memset(m_transaction_fees, 0x00, 4); // Consume Money ,,  0
        m_OpMode = recv_buffer[5];
        memcpy(m_Ef04Off, &recv_buffer[6], 2);
        memcpy(m_Ef04Len, &recv_buffer[8], 2);
        m_ef04len = m_Ef04Len[0] * 256 + m_Ef04Len[1];
        if(m_ef04len != 0)
        {
            memcpy(m_Ef04Info, &recv_buffer[10], m_ef04len);
            logm_debug("Ef04info is :");
            logm_debug_buffer(m_Ef04Info, m_ef04len);
        }

        logm_debug("OpMode is : %d\n", m_OpMode);
        logm_debug_buffer(m_Ef04Off, 2);
        logm_debug("Ef04Len is :");
        logm_debug_buffer(m_Ef04Len, 2);
        
        
        m_state = send_only_init_for_purchase_state;
        m_reporttradeState = trade_proc_undefine;

        m_sendTradeFrameCount = 0; // set Count as 0
        m_Trade_State_Code = TRADE_NORMAL;

        m_scheduler->send_bst_interval_status(0x01, 0x20);
    }
     else if((recv_buffer[0] == 0xC2) || (recv_buffer[0] == 0xC1)) // research OBU
    {
        goTradeEnd(PC_CMD_STOP_TRADE);
    } 
     
    return;
}

void TradeControl::sendB5FrameToPC()
{
    unsigned char send_buffer[128];
    unsigned char send_bufferLen;
    int ret;

     if(m_Trade_State_Code == 0x02)
    {
        send_buffer[0] = 0xB5; // trade end information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x02; // error code

        memcpy(&send_buffer[6], m_purchaseDateTime, 7); // trans time
        memcpy(&send_buffer[13], m_psam_transSerial, 4); // PSAM trans serial
        memcpy(&send_buffer[17], m_icc_tradesn, 2); // ICC Pay serial
        send_buffer[19] = 0x09; // Trans Type
        memset(&send_buffer[20], 0xFF, 4); // balance after purchase
        memset(&send_buffer[24], 0xFF, 4); // TAC

        send_buffer[28] = m_WriteFileTime >> 24; // WrFileTime
        send_buffer[29] = m_WriteFileTime >> 16; // WrFileTime
        send_buffer[30] = m_WriteFileTime >> 8; // WrFileTime
        send_buffer[31] = m_WriteFileTime;      // WrFileTime
        send_buffer[32] = 0x01;
        send_bufferLen = 33; // length of frame

    }
    else if(m_Trade_State_Code != TRADE_NORMAL)    
    {
        send_buffer[0] = 0xB5; // trade end information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = m_Trade_State_Code; // error code        
        memset(&send_buffer[6], 0, 27);
        send_bufferLen = 33; // length of frame
        
    }
    else if(OperateEF04Flag == 0x01)
    {
        send_buffer[0] = 0xB5; // trade end information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x00; // error code

        memset(&send_buffer[6], 0, 27); // trans time 没进行消费
      /*
        memset(&send_buffer[20], 0, 15);
        memcpy(&send_buffer[13], m_psam_transSerial, 4); // PSAM trans serial
        memcpy(&send_buffer[17], m_icc_tradesn, 2); // ICC Pay serial
        send_buffer[19] = 0x09; // Trans Type
        memset(&send_buffer[20], 0xFF, 4); // balance after purchase
        memset(&send_buffer[24], 0xFF, 4); // TAC

        send_buffer[28] = m_WriteFileTime >> 24; // WrFileTime
        send_buffer[29] = m_WriteFileTime >> 16; // WrFileTime
        send_buffer[30] = m_WriteFileTime >> 8; // WrFileTime
        send_buffer[31] = m_WriteFileTime;      // WrFileTime
        send_buffer[32] = 0x01;
        */
        send_bufferLen = 33; // length of frame
        
    }
    else
    {
         send_buffer[0] = 0xB5; // trade end information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x00; // error code


        memcpy(&send_buffer[6], m_purchaseDateTime, 7); // trans time
        memcpy(&send_buffer[13], m_psam_transSerial, 4); // PSAM trans serial
        memcpy(&send_buffer[17], m_icc_tradesn, 2); // ICC Pay serial
        send_buffer[19] = 0x09; // Trans Type
        memcpy(&send_buffer[20], m_after_purchase_balance, 4); // balance after purchase
        memcpy(&send_buffer[24], m_tradePurchaseTac, 4); // TAC

        send_buffer[28] = m_WriteFileTime >> 24; // WrFileTime
        send_buffer[29] = m_WriteFileTime >> 16; // WrFileTime
        send_buffer[30] = m_WriteFileTime >> 8; // WrFileTime
        send_buffer[31] = m_WriteFileTime;      // WrFileTime
        send_buffer[32] = 0x01;
        send_bufferLen = 33; // length of frame
               
    }        

    logm_debug("sendB5FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendB5FrameToPC Error! %d\n", ret);
        logm_err("sendB5FrameToPC Error!\n");
    }
    
    m_lastSendFrameTime = get_jiffies();
    m_sendTradeFrameCount++;
    
    m_reporttradeState = recv_ack_B5Frame_state;
    return;
}

void TradeControl::recvB5AckFromPC()
{
    int recv_len;
    unsigned char recv_buffer[256];
    

    recv_len = zmq_recv(m_reporterSocket_recv, recv_buffer, 256, ZMQ_DONTWAIT);
    if(recv_len <= 0)
    {
        if(check_waitPCAck_timeout(m_lastSendFrameTime))
        {

            logm_debug("receive B5 Ack TimeOut ! >> Trade stop! \n");
            goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
                    
        }
        return;
    }

        
    logm_debug("recvB5AckFromPC %d <-- ", recv_len);
    logm_debug_buffer(recv_buffer, recv_len);

    if(memcmp((unsigned char *)&m_macId, &recv_buffer[1], 4) != 0) // judge OBU MAIC_ID
    {
        logm_debug("receive B5 Ack From PC, OBU_MAC Not Match \n");
        return;
    }   

    if((recv_buffer[0] == 0xC1) && (m_scheduler->m_WorkMode == LANE_MODE_ENTRANCE))  // continue to trade
    {
        m_state = send_setmmi_state;
        m_reporttradeState = trade_proc_undefine;
        m_sendTradeFrameCount = 0; // set Count as 0
        m_Trade_State_Code = TRADE_NORMAL;
    }
    else if((recv_buffer[0] == 0xC1) && (m_scheduler->m_WorkMode != LANE_MODE_ENTRANCE))
    {

        m_state = send_setmmi_state;
        m_reporttradeState = trade_proc_undefine;
    
        m_sendTradeFrameCount = 0; // set Count as 0
        m_Trade_State_Code = TRADE_NORMAL;
    }
    else if((recv_buffer[0] == 0xC9) )
    {
        memcpy(m_EF04ReadOffSet, &recv_buffer[5], 2);
        memcpy(m_EF04ReadLen, &recv_buffer[7], 2);
       
        UpdateEF04Flag = recv_buffer[9];

        memcpy(m_EF04WriteOffSet, &recv_buffer[10], 2);
        memcpy(m_EF04WriteLen, &recv_buffer[12], 2);
        

        m_ef04len_c9 = m_EF04ReadLen[0] * 256 + m_EF04ReadLen[1];
        m_ef04len_write_c9 = m_EF04WriteLen[0] * 256 + m_EF04WriteLen[1];
        memcpy(m_EF04Info_C9_WD,&recv_buffer[14],m_ef04len_write_c9);

        if(m_ef04len_c9 == 0 &&  m_ef04len_write_c9 ==0)
        {
            m_state = report_and_query_ack_trade_state;
            m_reporttradeState = send_trade_B9Frame_state;
        }
        else
        {
            m_state = send_read_ef04_exit_state;
            m_reporttradeState = trade_proc_undefine;
        }

        m_sendTradeFrameCount = 0; // set Count as 0
        m_Trade_State_Code = TRADE_NORMAL;
    }

    else if(recv_buffer[0] == 0xC2) // research OBU
    //else if(recv_buffer[0] == 0xC2) // research OBU
    {
        goTradeEnd(PC_CMD_STOP_TRADE);
    }
    
     return;
}

void TradeControl::sendB9FrameToPC()
{
    unsigned char send_buffer[128];
    unsigned char send_bufferLen;
    int ret;

    if(m_Trade_State_Code != TRADE_NORMAL)    
    {
        send_buffer[0] = 0xB9; // trade end information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = m_Trade_State_Code; // error code        
        memcpy(&send_buffer[6],&m_EF04ReadLen[0],2);
        if(m_EF04RdStatus !=0x00)
        {
           memset(&send_buffer[8],0,m_ef04len_c9); 
        }
        memcpy(&send_buffer[8],&m_EF04Info_C9_RD[0],m_ef04len_c9);
        send_bufferLen = 8 + m_ef04len_c9; // length of frame
        //send_bufferLen = 6; // length of frame
    }
    else
    {
        send_buffer[0] = 0xB9; // trade end information frame
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x00; // error code
        memcpy(&send_buffer[6],&m_EF04ReadLen[0],2);
        if(m_EF04RdStatus !=0x00)
        {
           memset(&send_buffer[8],0,m_ef04len_c9); 
        }
        memcpy(&send_buffer[8],&m_EF04Info_C9_RD[0],m_ef04len_c9);
       
        send_bufferLen = 8 + m_ef04len_c9; // length of frame
               
    }        

    logm_debug("sendB9FrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);


    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendB9FrameToPC by internet Error! %d\n", ret);
        logm_err("sendB9FrameToPC by internet Error!\n");
    }
    
        m_send_b9_after = 1;
        m_lastSendFrameTime = get_jiffies();
        m_sendTradeFrameCount=0;
  
        m_state = send_setmmi_state;
        m_reporttradeState = trade_proc_undefine;
  
    return;
}

void TradeControl::recvB9AckFromPC()
{
    int recv_len;
    unsigned char recv_buffer[256];
     

    recv_len = zmq_recv(m_reporterSocket_recv, recv_buffer, 256, ZMQ_DONTWAIT);
    if(recv_len <= 0)
    {
        if(check_waitB9Ack_timeout(m_lastSendFrameTime))
        {
            logm_debug("receive B9 Ack TimeOut ! >>>> Trade stop! \n");
            goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
        }
        return;
    }
 
    
    logm_debug("recvB9AckFromPC %d <-- ", recv_len);
    logm_debug_buffer(recv_buffer, recv_len);
   
    goTradeEnd(0);

    return;
}

void TradeControl::sendErrorFrameToPC()
{
    unsigned char send_buffer[128];
    unsigned char send_bufferLen;
    int ret;

    m_Trade_State_Code = PC_CMD_STOP_TRADE;
    if(m_Trade_State_Code != TRADE_NORMAL)    
    {
        if(m_recv_error_instruct == 0xC6)
        {
            send_buffer[0] = 0xB5; // trade end information frame
        }
        else if(m_recv_error_instruct == 0xC7)
        {
            send_buffer[0] = 0xB7;
        }
        else
        {
            send_buffer[0] = 0xB2;
        }
        send_buffer[1] = (m_macId >> 24);
        send_buffer[2] = (m_macId >> 16);
        send_buffer[3] = (m_macId >> 8);
        send_buffer[4] = m_macId;
        send_buffer[5] = 0x08; // error code        

        send_bufferLen = 6; // length of frame
    }
    
    logm_debug("sendErrorFrameToPC %d --> ", send_bufferLen);
    logm_debug_buffer(send_buffer, send_bufferLen);

    ret = zmq_send(m_reporterSocket_send, send_buffer,  send_bufferLen, ZMQ_DONTWAIT);
    if (ret < 0)
    {
        logm_debug("sendErrorFrameToPC by internet Error! %d\n", ret);
        logm_err("sendErrorFrameToPC by internet Error!\n");
    }
    
    m_lastSendFrameTime = get_jiffies();
    m_sendTradeFrameCount++;
    m_reporttradeState = recv_trade_error_Frame_state;
    return;
}

void TradeControl::recvErrorAckFromPC()
{
    int recv_len;
    unsigned char recv_buffer[256];
    

     recv_len = zmq_recv(m_reporterSocket_recv, recv_buffer, 256, ZMQ_DONTWAIT);
    if(recv_len <= 0)
    {    
        if(check_waitPCAck_timeout(m_lastSendFrameTime))
        {
            #if 0

            #else
                logm_debug("receive Error Ack TimeOut ! >>>> Trade stop! \n");
                goTradeEnd(RECEIVE_PC_ACK_TIMEOUT);
            #endif            
        }
        return;
    }

    
    
    logm_debug("recvErrorAckFromPC %d <-- ", recv_len);
    logm_debug_buffer(recv_buffer, recv_len);

    if(memcmp((unsigned char *)&m_macId, &recv_buffer[1], 4) != 0) // judge OBU MAIC_ID
    {
        logm_debug("receive Error Ack From PC, OBU_MAC Not Match \n");
        return;
    }

    goTradeEnd(PC_CMD_STOP_TRADE);
    
    return;
}

// report trade frame to PC, and get ACK information from PC
void TradeControl::reportAndGetAckFromPC()
{
    switch(m_reporttradeState)
    {
         case send_fake_location_D0Frame_state:
        {
            sendFakeD0FrameToPC();
            break;
        }
        case send_location_D0Frame_state:
        {
            sendD0FrameToPC();
            break;
        }
        case send_trade_B2Frame_state:
        {
            sendB2FrameToPC();
            break;
        }
        case recv_ack_B2Frame_state:
        {
            recvB2AckFromPC();
            break;
        }
        case send_trade_B3Frame_state:
        {
            sendB3FrameToPC();
            break;
        }
        case recv_ack_B3Frame_state:
        {
            recvB3AckFromPC();
            break;
        }
        case send_trade_B4Frame_state:
        {
            sendB4FrameToPC();
            break;
        }
        case recv_ack_B4Frame_state:
        {
            recvB4AckFromPC();
            break;
        }
        case send_trade_B5Frame_state:
        {
            sendB5FrameToPC();
            break;
        }
        case recv_ack_B5Frame_state:
        {
            recvB5AckFromPC();
            break;
        }
        case send_trade_B9Frame_state:
        {
            sendB9FrameToPC();
            break;
        }
        case recv_ack_B9Frame_state:
        {
            recvB9AckFromPC();
            break;
        }
        case send_trade_error_Frame_state:
        {
            sendErrorFrameToPC();
            break;
        }
        case recv_trade_error_Frame_state:
        {
            recvErrorAckFromPC();
            break;
        }
        default:
        {
            logm_err("reportAndGetAckFromPC fall into unknow state\n");
            m_reporttradeState = trade_proc_undefine;
            m_state = vst_state;
        }
    }
    return;
}


void TradeControl::sendCalcAccessCred(void)
{
    unsigned char fensanyinzi[16];

    memcpy(fensanyinzi, &m_sysInfo[10], 8);
    memcpy(&fensanyinzi[8], &m_sysInfo[0], 4);
    memcpy(&fensanyinzi[12], &m_sysInfo[0], 4);
    
    m_psam = m_scheduler->getPsam(universal_psam);
    if(NULL != m_psam)
    {
        m_psam->sendCalcAccessCred(fensanyinzi, m_random);
        m_state = recv_calc_access_cred_state;
    }
    else
    {
       
    }

    return;
}

void TradeControl::recvCalcAccessCred(void)
{
    int ret;

    ret = m_psam->recvCalcAccessCred(m_accessCred);
    if(ret == 0) 
    {
        if(NULL != m_psam) 
        {
            m_scheduler->putPsam(m_psam);
            m_psam = NULL;
        }
        m_state = send_get_toll_data_state;
    } 
    else if(ret == 1) 
    {
        if(NULL != m_psam) 
        {
            m_scheduler->putPsam(m_psam);
            m_psam = NULL;
        }
        
        return;
    }
    
    return;
}

void TradeControl::sendSetmmi(void)
{
    encodeSetMmi();
    sendActionCmd();

    m_repeatNum = m_scheduler->m_config->m_obuRepeatNum; // repeatnum = 0, SetMMI 
    m_lastSend = get_jiffies();
    m_state = recv_setmmi_state;

    return;
}

void TradeControl::recvSetmmi(void)
{
    recv_buffer_t *recv_buffer = NULL;
    unsigned int mac_id;
    
    std::vector<recv_buffer_t *>::iterator iter;
    unsigned char errcode = 0x00;

    for(iter=m_scheduler->m_recvBuffers.begin();
        iter!= m_scheduler->m_recvBuffers.end();
        ++iter) 
    {
        recv_buffer = (*iter);
        if((recv_buffer->length < 13)
           ||(recv_buffer->buffer[0] != 0xe2)
           || (recv_buffer->buffer[1] != 0x00)) 
        {
            continue;
        }
        mac_id = (recv_buffer->buffer[2]<<24)
                 |(recv_buffer->buffer[3]<<16)
                 |(recv_buffer->buffer[4]<<8)
                 |recv_buffer->buffer[5];
        
        if(mac_id != m_macId)
        {
            continue;
        }    


        recv_buffer->length = 0;
        forbidRfSendBst(recv_buffer->rfsn);
        m_rssi = recv_buffer->rssi;
        m_seleRfsn = recv_buffer->rfsn;  
     //   if((m_scheduler->m_WorkMode != LANE_MODE_ENTRANCE) && (m_send_b9_after == 1) && (m_scheduler->m_config->m_etc_mtc == MTC))
      //  {
       //     m_lastSendFrameTime = get_jiffies();
       //     m_sendTradeFrameCount++;

       //     m_state = report_and_query_ack_trade_state;
       ////     m_reporttradeState = recv_ack_B7Frame_state;
      //      m_send_b7_after = 0;
      //  }   
      //  else
     //   {
            goTradeEnd(errcode);
      //  }
        return;
    }

    check_timeout(errcode);
    _resendAction(m_scheduler->m_config->m_obuReadFileInterval, errcode);
}


void TradeControl::goTradeEnd(unsigned char retcode)
{
    unsigned short trade_time;

    if(m_research_obu != 0x01)
    {
        sendEventReport();
    }
    
    m_scheduler->forbidRfSendBst(m_seleRfsn, false);

    if(PC_CMD_STOP_TRADE == retcode) 
    {
        m_scheduler->m_lastChangeIdTime = get_jiffies();
        m_scheduler->m_change_beaconid = true;
        logm_info("change beaconid true\n");
        m_research_obu = 0x01;
    }

    if(retcode == 0)// Trade success, cache MAC_ID
    {
        m_scheduler->m_tagCache->cacheTag(m_macId); 
        m_scheduler->m_config->m_bstInterval = 200; 
        m_scheduler->m_car_status = 0x00;
    }
    
    trade_time = (unsigned short)diffTimeVal(get_jiffies(), m_startTime);    

    logm_info("macid:%08x trade end, retcode: %02x, RSU_Error: %x, esamversion: %x, rfsn: %x, rssi: %x, trade_time: %d\n",\
               m_macId, retcode, m_Trade_State_Code, m_esamVersion, m_seleRfsn, m_rssi, trade_time);

    m_state = vst_state;
    m_reporttradeState = trade_proc_undefine;
    m_Trade_State_Code = 0x00;
    m_sendTradeFrameCount = 0;
    m_macId = 0;
    m_vByte = 0x77;
    memset(m_obuStatus, 0, 2);
    memset(m_file15, 0, 50);    
    memset(m_file19, 0, 63);
    memset(m_icc_balance, 0x00, 4);
    memset(m_after_purchase_balance, 0x00, 4);
    memset(m_psam_transSerial, 0x00, 4);
    memset(m_descryptedVehicle, 0x00, 64);
    m_needRereadFile15 = false;  
    m_research_obu = 0x00;  
    m_EF04RdStatus = 0x00;
    
    if(NULL != m_psam)
    {
        m_scheduler->putPsam(m_psam);
        m_psam = NULL;
    }

    m_forbidBst = false;

    return;
}



void TradeControl::goIgnore(void)
{
    sendEventReport();
    logm_info("macid:%08x ignored\n", m_macId);
    m_state = vst_state;
    m_reporttradeState = trade_proc_undefine;
    m_Trade_State_Code = 0x00;    
    m_sendTradeFrameCount = 0;
    m_macId = 0;
    m_vByte = 0x77; 
    m_control_D0 = 0;
    memset(m_obuStatus, 0, 2);
    memset(m_sysInfo, 0x00, 26);
    memset(m_file15, 0x00, 50);   
    if(NULL != m_psam) 
    {
        m_scheduler->putPsam(m_psam);
        m_psam = NULL;
    }
    m_forbidBst = false;
    m_scheduler->forbidRfSendBst(m_rfsn, false); 

    return;
}

//check trade timeout or check repeat count
int TradeControl::check_timeout_and_repeatNum(unsigned char timeout_error, 
                                            unsigned char repeatError, unsigned char checkFlag)
{
    //check timeout
    check_timeout_setErrorCode(timeout_error);

    if(checkFlag != 0)
    {
        // check timeout count
        //if(timeOk(m_lastSend, m_scheduler->m_config->m_obuGetsecureInterval)) 
        if(timeOk(m_lastSend, repeatError)) 
        {
            check_repeatnum_setErrorCode(timeout_error);
            m_lastSend = get_jiffies();
            sendActionCmd();
            usleep(1000);
        }
    }        

    return 0;
}

int TradeControl::PSAM_check_timeout(unsigned char timeout_error, unsigned long timeout_interval)
{
    if(timeOk(m_psam_StartTime, timeout_interval))
    {
        m_Trade_State_Code = timeout_error;
        return 1;
    }
    return 0;
}

void TradeControl::sendActionCmd()
{
    m_scheduler->sendDsrcFrameByRf(m_lastAction, m_lastActionLen, m_rfsn);
    m_scheduler->m_rfsList.remove(m_rfsn);
    m_scheduler->m_rfsList.push_back(m_rfsn);
    m_rfsn = m_scheduler->m_rfsList.front();
}

void TradeControl::sendEventReport(void)
{
    unsigned char tx_frame[32];

    tx_frame[0] = 0xf2;
    tx_frame[1] = m_macId>>24;
    tx_frame[2] = m_macId>>16;
    tx_frame[3] = m_macId>>8;
    tx_frame[4] = m_macId;
    tx_frame[5] = 0x40;
    tx_frame[6] = 0x03;
    tx_frame[7] = 0x91;
    tx_frame[8] = 0x60;
    tx_frame[9] = 0x00;
    tx_frame[10] = 0x00;

    for(int i = 0; i < 5; ++i)
    {
        m_scheduler->sendDsrcFrameByRf(tx_frame, 11, m_rfsn);
    }

    return;
}

void TradeControl::_resendAction(int interval, unsigned int errorcode)
{
    if(timeOk(m_lastSend, interval))
    {
        check_repeatnum(errorcode);    
        m_lastSend = get_jiffies();
        sendActionCmd();
        usleep(1000);
    }
    return;
}

int TradeControl::_resendAction_setErrorCode(int interval, unsigned char errorcode)
{
    if(timeOk(m_lastSend, interval))
    {
        check_repeatnum_setErrorCode(errorcode);
        m_lastSend = get_jiffies();
        sendActionCmd();
        usleep(1000);
    }
    return 0;
}

bool TradeControl::isBjObu(void)
{
    unsigned char bj_provider[4] = {0xB1, 0xB1, 0xBE, 0xA9};

    if((memcmp(&m_sysInfo[0], &bj_provider[0], 4) == 0)) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TradeControl::isMilitaryObu(void)
{

    #if 0
    unsigned char military[4] = {0xBE, 0xFC, 0xB3, 0xB5};
    if((memcmp(&m_sysInfo[0], &military[0], 4) == 0)) 
    #else
    unsigned char military[2] = {0x05, 0x01};
    if((memcmp(&m_sysInfo[4], &military[0], 2) == 0))
    #endif
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool TradeControl::isBjIccCard(void)
{
    if(m_file15[10] == 0x11) 
    {
        return true;
    }
    else
    {
        return false;
    }
}





SchedulerConfig::SchedulerConfig()
{
    m_enableRuning = true;
    m_testmode = false;
}

void SchedulerConfig::loadConfig()
{
    ifstream configfile;
    Json::Reader reader;
    Json::Value jsonConfig;
    bool parseRet;


    configfile.open("/config/scheduler.json");
    if(!configfile.is_open())
    {
        logm_err("open config file fail, next to open init_config file\n");

        configfile.open("/opt/bin/scheduler.json");
        if(!configfile.is_open())
        {
            logm_err("open init_config file fail\n");
            return;
        }
    }

    parseRet = reader.parse(configfile, jsonConfig, false);
    if(!parseRet) 
    {
        logm_err("parse config file fail\n");
        configfile.close();
        return;
    }

    fromJson(jsonConfig);
    configfile.close();

    return;
}

void SchedulerConfig::loadDefaultConfig()
{
    ifstream configfile;
    Json::Reader reader;
    Json::Value jsonConfig;
    bool parseRet;


    configfile.open("/opt/bin/scheduler.json");
    if(!configfile.is_open())
    {
        logm_err("open init_config file fail\n");
        return;
    }
    

    parseRet = reader.parse(configfile, jsonConfig, false);
    if(!parseRet) 
    {
        logm_err("parse config file fail\n");
        configfile.close();
        return;
    }

    fromJson(jsonConfig);
    configfile.close();

    return;
}


void SchedulerConfig::clearPsamConfig()
{
    for(std::vector<PsamPara *>::iterator iter=m_psamConfig.begin();
        iter!=m_psamConfig.end(); ++iter)
    {
        delete *iter;
    }

    m_psamConfig.clear();

    return;
}

void SchedulerConfig::clearRfConfig()
{
    for(std::list<RfPara *>::iterator iter=m_rfConfig.begin();
        iter!=m_rfConfig.end(); ++iter) 
    {
        delete *iter;
    }
    m_rfConfig.clear();

    return;
}

void SchedulerConfig::clearConfig()
{
    clearPsamConfig();
    clearRfConfig();

    return;
}

void SchedulerConfig::saveConfig()
{
    Json::StyledWriter writer;
    Json::Value jsonConfig;
    string targetStr;
    ofstream configfile;

    toJson(jsonConfig);
    targetStr = writer.write(jsonConfig);

    #if 0
    configfile.open("/opt/bin/scheduler.json", ios::out|ios::trunc);
    #else
    configfile.open("/config/scheduler.json", ios::out|ios::trunc);
    #endif
    if(configfile.is_open()) 
    {
        configfile.write(targetStr.c_str(), targetStr.length());
    }
    configfile.close();
    return;
}


void SchedulerConfig::fromJson(Json::Value &jsonConfig)
{
    clearConfig();

    if(jsonConfig.isMember("enable_runing")) 
    {
        m_enableRuning = jsonConfig["enable_runing"].asBool();
        logm_debug("m_enableRuning %d \n", m_enableRuning);
    }

    if(jsonConfig.isMember("testmode"))
    {
        m_testmode = jsonConfig["testmode"].asBool();
        logm_debug("m_testmode %d \n", m_testmode);
    }

    if(jsonConfig.isMember("lanmode")) 
    {
        m_lanmode = jsonConfig["lanmode"].asInt();
    }
    if(jsonConfig.isMember("rfsmode")) 
    {
        m_rfsmode = jsonConfig["rfsmode"].asInt();
    }
    if(jsonConfig.isMember("etcmtc")) 
    {
        m_etc_mtc = jsonConfig["etcmtc"].asInt();
    }

    if(jsonConfig.isMember("wait_time")) 
    {
        m_waitTime = jsonConfig["wait_time"].asInt();
    }

    if(jsonConfig.isMember("heart_beat")) 
    {
        m_heartBeat = jsonConfig["heart_beat"].asInt();
    }
    if(jsonConfig.isMember("vst_len")) 
    {
        m_vst_len = jsonConfig["vst_len"].asInt();
    }
    if(jsonConfig.isMember("control_id"))
    {
        m_control_ID = jsonConfig["control_id"].asInt();
    }
    if(jsonConfig.isMember("control_master_ip"))
    {
        strcpy(m_master_ip, jsonConfig["control_master_ip"].asCString());
    }

    if(jsonConfig.isMember("location_X1"))
    {
        m_location_X1 = jsonConfig["location_X1"].asInt();
    }

    if(jsonConfig.isMember("location_X2"))
    {
        m_location_X2 = jsonConfig["location_X2"].asInt();
    }
    
    if(jsonConfig.isMember("location_Y_max"))
    {
        m_location_Y_max = jsonConfig["location_Y_max"].asInt();
    }

    if(jsonConfig.isMember("location_Y_min"))
    {
        m_location_Y_min = jsonConfig["location_Y_min"].asInt();
    }

    if(jsonConfig.isMember("location_limit")) 
    {
        m_location_limit = jsonConfig["location_limit"].asBool();
        logm_debug("m_location_limit %d \n", m_location_limit);
    }

    if(jsonConfig.isMember("location_sub_Y")) 
    {
        m_location_sub_Y = jsonConfig["location_sub_Y"].asInt();
        logm_debug("m_location_sub_Y %d \n", m_location_sub_Y);
    }

    if(jsonConfig.isMember("location_sub_X1")) 
    {
        m_location_sub_X1 = jsonConfig["location_sub_X1"].asInt();
        logm_debug("m_location_sub_X1 %d \n", m_location_sub_X1);
    }

    if(jsonConfig.isMember("location_sub_X2")) 
    {
        m_location_sub_X2 = jsonConfig["location_sub_X2"].asInt();
        logm_debug("m_location_sub_X2 %d \n", m_location_sub_X2);
    }
    if(jsonConfig.isMember("near_switch"))
    {
        m_near_switch = jsonConfig["near_switch"].asInt();
        logm_debug("m_near_switch %d \n", m_near_switch);
    }

    if(jsonConfig.isMember("mid_near_switch"))
    {
        m_mid_near_switch = jsonConfig["mid_near_switch"].asInt();
        logm_debug("mid_near_switch %d \n", m_mid_near_switch);
    }

    if(jsonConfig.isMember("mid_far_switch"))
    {
        m_mid_far_switch = jsonConfig["mid_far_switch"].asInt();
        logm_debug("mid_far_switch %d \n", m_mid_far_switch);
    }

    if(jsonConfig.isMember("far_switch"))
    {
        m_far_switch = jsonConfig["far_switch"].asInt();
        logm_debug("m_far_switch %d \n", m_far_switch);
    }
    if(jsonConfig.isMember("direction"))
    {
        m_direction = jsonConfig["direction"].asInt();
        logm_debug("m_direction %d \n", m_direction);
    }
    if(jsonConfig.isMember("coil_trigger_antenna")) 
    {
        m_coil_trigger_antenna = jsonConfig["coil_trigger_antenna"].asBool();
        logm_debug("coil_trigger_antenna %d \n", m_coil_trigger_antenna);
    }

    if(jsonConfig.isMember("coil_trigger_enable")) 
    {
        m_coil_trigger_enable = jsonConfig["coil_trigger_enable"].asBool();
        logm_debug("coil_trigger_enable %d \n", m_coil_trigger_enable);
    }

    if(jsonConfig.isMember("coil_trigger_confine"))
    {
        m_coil_trigger_confine = jsonConfig["coil_trigger_confine"].asInt();
        logm_debug("coil_trigger_confine %d \n", m_coil_trigger_confine);
    }
    
    if(jsonConfig.isMember("beaconid_config")) 
    {
        if(jsonConfig["beaconid_config"].isMember("beaconid")) 
        {
            string2hex(jsonConfig["beaconid_config"]["beaconid"].asCString(), 8, m_beaconId);
            logm_debug("m_beaconId %02x%02x%02x%02x\n", m_beaconId[0], m_beaconId[1],m_beaconId[2],m_beaconId[3]);
        }
        if(jsonConfig["beaconid_config"].isMember("ifchange")) 
        {
            m_ifBeaconidChange = jsonConfig["beaconid_config"]["ifchange"].asBool();
            logm_debug("m_ifBeaconidChange %d \n", m_ifBeaconidChange);
        }
        if(jsonConfig["beaconid_config"].isMember("cycle")) 
        {
            m_beaconidCycle= jsonConfig["beaconid_config"]["cycle"].asInt();
            logm_debug("m_beaconidCycle %d \n", m_beaconidCycle);
        }
    }    

    if(jsonConfig.isMember("parallel"))
    {
        m_parallelTrade = jsonConfig["parallel"].asInt();
        logm_debug("m_parallelTrade %d\n", m_parallelTrade);
    }

    if(jsonConfig.isMember("timepara")) 
    {
        if(jsonConfig["timepara"].isMember("bst_interval")) 
        {
            m_bstInterval = jsonConfig["timepara"]["bst_interval"].asInt();
            logm_debug("m_bstInterval %d\n", m_bstInterval);
        }        

        if(jsonConfig["timepara"].isMember("obu_getsecure_interval")) 
        {
            m_obuGetsecureInterval = jsonConfig["timepara"]["obu_getsecure_interval"].asInt();
            logm_debug("m_obuGetsecureInterval %d\n", m_obuGetsecureInterval);
        }

        if(jsonConfig["timepara"].isMember("obu_readfile_interval")) 
        {
            m_obuReadFileInterval = jsonConfig["timepara"]["obu_readfile_interval"].asInt();
            logm_debug("m_obuReadFileInterval %d\n", m_obuReadFileInterval);
        }

        if(jsonConfig["timepara"].isMember("obu_writefile_interval")) 
        {
            m_obuWriteFileInterval = jsonConfig["timepara"]["obu_writefile_interval"].asInt();
            logm_debug("m_obuWriteFileInterval %d\n", m_obuWriteFileInterval);
        }

        if(jsonConfig["timepara"].isMember("obu_timeout")) 
        {
            m_obutimeout = jsonConfig["timepara"]["obu_timeout"].asInt();
            logm_debug("m_obutimeout %d\n", m_obutimeout);
        }

        if(jsonConfig["timepara"].isMember("obu_repeat_num")) 
        {
            m_obuRepeatNum = jsonConfig["timepara"]["obu_repeat_num"].asInt();
            logm_debug("m_obuRepeatNum %d\n", m_obuRepeatNum);
        }             
    }

    if(jsonConfig.isMember("psamconfig")) 
    {
        Json::Value psam;
        PsamPara *psamPara;

        for(int i=0; i<jsonConfig["psamconfig"].size(); ++i) 
        {
            psam = jsonConfig["psamconfig"][i];
            if(psam.isMember("psamid")&&psam.isMember("enable")
               &&psam.isMember("type")) {
                psamPara = new PsamPara();
                psamPara->psamid = psam["psamid"].asInt();
                psamPara->isEnable = psam["enable"].asBool();
                psamPara->type = psam["type"].asInt();
                m_psamConfig.push_back(psamPara);
                logm_debug("psam %d %d %d\n", psamPara->psamid,
                           psamPara->isEnable, psamPara->type);
            }
        }
    }

    if(jsonConfig.isMember("rfconfig")) 
    {
        Json::Value rf;
        RfPara *rfPara;

        for(int i=0; i<jsonConfig["rfconfig"].size(); ++i) 
        {
            rf = jsonConfig["rfconfig"][i];

            if(rf.isMember("rfsn") && rf.isMember("enable")
               && rf.isMember("power") && rf.isMember("addr")
               && rf.isMember("channel")) 
            {
                rfPara = new RfPara();
                rfPara->rfsn = rf["rfsn"].asInt();
                rfPara->isEnable = rf["enable"].asBool();
                rfPara->power = rf["power"].asInt();
                rfPara->channel = rf["channel"].asInt();
                strcpy(rfPara->ipaddr, rf["addr"].asCString());
                m_rfConfig.push_back(rfPara);
                logm_debug("rf %d %d %d %d %s \n", rfPara->rfsn, rfPara->isEnable,\
                           rfPara->power, rfPara->channel, rfPara->ipaddr);
            }
        }
    }
}

void SchedulerConfig::toJson(Json::Value &jsonConfig)
{
    Json::Value beaconidConfig;
    char beaconidstring[10];

    //jsonConfig["enable_runing"] = m_enableRuning;
    jsonConfig["enable_runing"] = false;
    jsonConfig["testmode"] = m_testmode;
    jsonConfig["rfsmode"] = m_rfsmode;
    jsonConfig["rfsmode"] = m_rfsmode;
    jsonConfig["lanmode"] = m_lanmode;
    jsonConfig["etcmtc"] = m_etc_mtc;
    jsonConfig["wait_time"] = m_waitTime;
    jsonConfig["heart_beat"] = m_heartBeat;
    jsonConfig["vst_len"] = m_vst_len;
    
    jsonConfig["location_X1"] = m_location_X1;
    jsonConfig["location_X2"] = m_location_X2;
    jsonConfig["location_Y_max"] = m_location_Y_max;
    jsonConfig["location_Y_min"] = m_location_Y_min;
    jsonConfig["location_limit"] = m_location_limit;

    jsonConfig["location_sub_Y"] = m_location_sub_Y;
    jsonConfig["location_sub_X1"] = m_location_sub_X1;
    jsonConfig["location_sub_X2"] = m_location_sub_X2;

    jsonConfig["near_switch"] = m_near_switch;
    jsonConfig["mid_near_switch"] = m_mid_near_switch;
    jsonConfig["mid_far_switch"] = m_mid_far_switch;
    jsonConfig["far_switch"] = m_far_switch;
    jsonConfig["direction"] = m_direction;

    jsonConfig["coil_trigger_antenna"] = m_coil_trigger_antenna;
    jsonConfig["coil_trigger_enable"] = m_coil_trigger_enable;
    jsonConfig["coil_trigger_confine"] = m_coil_trigger_confine;

    jsonConfig["control_id"] = m_control_ID;
    jsonConfig["control_master_ip"] = m_master_ip;
    
    hex2string(m_beaconId, 4, beaconidstring);
    beaconidstring[8] = 0;

    beaconidConfig["beaconid"] = beaconidstring;
    beaconidConfig["ifchange"] = m_ifBeaconidChange;
    beaconidConfig["cycle"] = m_beaconidCycle;

    jsonConfig["beaconid_config"] = beaconidConfig;

    Json::Value timepara;
    
    timepara["bst_interval"] = m_bstInterval;
    timepara["obu_getsecure_interval"] = m_obuGetsecureInterval;
    timepara["obu_readfile_interval"] = m_obuReadFileInterval;
    timepara["obu_writefile_interval"] = m_obuWriteFileInterval;
    timepara["obu_timeout"] = m_obutimeout;
    timepara["obu_repeat_num"] = m_obuRepeatNum;

    jsonConfig["timepara"] = timepara;    

    jsonConfig["parallel"] = m_parallelTrade;

    Json::Value psam;
    Json::Value psamconfig;

    for(std::vector<PsamPara *>::iterator iter=m_psamConfig.begin();
        iter!=m_psamConfig.end(); ++iter) 
    {
        psam["psamid"] = (*iter)->psamid;
        psam["enable"] = (*iter)->isEnable;
        psam["type"] = (*iter)->type;
        psamconfig.append(psam);
    }

    jsonConfig["psamconfig"] = psamconfig;

    Json::Value rf;
    Json::Value rfconfig;

    for(std::list<RfPara*>::iterator iter=m_rfConfig.begin();
        iter!=m_rfConfig.end(); ++iter)
    {
        rf["rfsn"] = (*iter)->rfsn;
        rf["enable"] = (*iter)->isEnable;
        rf["power"] = (*iter)->power;
        rf["addr"] = (*iter)->ipaddr;
        rf["channel"] = (*iter)->channel;
        rfconfig.append(rf);
    }

    jsonConfig["rfconfig"] = rfconfig;
    return;
}






Scheduler::Scheduler()
{
    m_ctx = NULL;
    m_tagCache = new TagCache();
    m_tagCache->setCacheTime(TAG_CACHE_TIME_ROAD);    
    m_rand_beaconid = rand()%255;
    assert(m_tagCache); 
    m_lastBeaconIdTime = get_jiffies();    
    m_lastChangeIdTime= get_jiffies();       
    m_send_tick_flag = 0; // send tick to PC
    m_send_init_b0_flag = 1;
    
    
    m_coil_trigger_flag = 0; // DiGan coil trigger flag
    m_send_bst_num = 0;
    m_send_bst_num2 = 0;
    m_send_bst_num3 = 0;
    m_car_status == 0x00;
    m_ant_work_mode = 2;// init ant is FAR_end
    m_num_ctrlbstmode = 1;
   
    m_far_num = 0;
    m_mid_to_near_num = 0;
    m_mid_to_far_num = 0;
    m_near_num = 5;
    m_instep_fake_status = 0;

    m_WorkType_7 = 0x00;
    m_WorkType_1 = 0x00;
    m_WorkType_0 = 0x00;
    m_InitEf04Opt = 0x01;
    m_InitEf04Offset[0] = 0x01;
    m_InitEf04Offset[1] = 0x3a;
    m_InitEf04Len[0] = 0x00;
    m_InitEf04Len[1] = 0x5b;
    m_initef04len = 91;
    PsamAutState = 0x00;//lzw
    
    m_setantchannel = 0x00;
    m_adjacent_ant_status = 0x00;
    m_close_ant_from_master = 0x00;
    m_send_tick_adjacent_flag = 0x00;
    /* set trade port default Net*/
    m_trade_zmq_select = TRADE_ZMQ_SEL_NET;

}


void Scheduler::initRfProxy()
{
    RfProxy *rfProxy = NULL;

    for(std::list<RfPara *>::iterator iter = m_config->m_rfConfig.begin();
        iter != m_config->m_rfConfig.end(); ++iter)
    {
        if((*iter)->isEnable)
        {
            rfProxy = new RfProxy(m_ctx, (*iter)->rfsn, (*iter)->power, (*iter)->channel, (*iter)->ipaddr);
            rfProxy->initChannel();
            //rfProxy->initPower();
            rfProxy->m_rfForbidBst = false;

            m_rfs.push_back(rfProxy);
            m_rfsMap[rfProxy->sn] = rfProxy;
            m_rfsList.push_back(rfProxy->sn);
        }
    }
    m_rfsIter = m_rfs.begin();
    return;
}

/* re-connect and init antenna */
void Scheduler::ReConnect_Antenna()
{
    for(std::vector<RfProxy *>::iterator iter = m_rfs.begin(); iter != m_rfs.end(); ++iter)
    {
        if((*iter)->status == rf_disconnected)
        {
            /* close link and repeat to connect antenna */
            (*iter)->preClose_ReConnect_Antenna();
        }
    }    
}

void Scheduler::push_psam_vector(PsamProxy *psamProxy)
{
    if(psamProxy->m_psamVersion < 0x05)
    {
        /* GB-3DES */
        m_gbtdesPsams.push_back(psamProxy);
    }
    else
    {
        /* GB-3DES and SM4 */
        m_universalPsams.push_back(psamProxy);
    }    
}


void Scheduler::initPsamProxy()
{
    PsamProxy *psamProxy = NULL;
    int ret;

    for(std::vector<PsamPara *>::iterator iter=m_config->m_psamConfig.begin();
        iter != m_config->m_psamConfig.end(); ++iter)
    {
        if((*iter)->isEnable)
        {
            psamProxy = new PsamProxy(m_ctx, (*iter)->psamid, (*iter)->type);
            m_psamproxy[(*iter)->psamid - 1] = psamProxy;
            ret = psamProxy->readTerminalID();
            if(ret == 0)
            {
                (*iter)->status = PSAM_STATUS_OK;
                (*iter)->version = psamProxy->m_psamVersion;
                (*iter)->psam_type = psamProxy->m_psamType; // psam Type, from psam_file_0015 //lrz
                memcpy((*iter)->terminal_id, psamProxy->m_terminalID, 6);
                memcpy((*iter)->psam_serial, psamProxy->m_psamSerial, 10);  //lrz
                memcpy((*iter)->issueID, psamProxy->m_psamIssueID, 8);      //lrz
                memcpy((*iter)->useAreaID, psamProxy->m_psamUseAreaID, 8);  //lrz

                /* set psam auth_status */
                (*iter)->AuthStatus = ((*iter)->version < 0x05) ? PSAM_AUTH_OK : PSAM_AUTH_NO;
                
                /* push psam into vector for trade */
                push_psam_vector(psamProxy);
            }
            else
            {
                (*iter)->status = PSAM_STATUS_NOT_OK;
            }
        }
    }
}


void Scheduler::initTradeControl()
{
    TradeControl *tagControl = NULL;
    int tradeConNum = 0;    
    std::vector<TradeControl *>::iterator iter;
    
    for(int i = 0; i < m_config->m_parallelTrade; ++i)
    {
        tagControl = new TradeControl(this, m_reporterSocket_send_net, m_reporterSocket_recv_net);
        assert(tagControl);
        m_tradeControls.push_back(tagControl);
    }

    tradeConNum = m_tradeControls.size();
    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter)
    {
        (*iter)->setTradeControlNum(tradeConNum);
    }
    
    return;
}

void Scheduler::initBst()
{
    unsigned int currentTime;

    currentTime = (unsigned int)time(NULL);
    m_encodedBst[0] = 0xf1;
    m_encodedBst[1] = 0xff;
    m_encodedBst[2] = 0xff;
    m_encodedBst[3] = 0xff;
    m_encodedBst[4] = 0xff;
    m_encodedBst[5] = 0x50;
    m_encodedBst[6] = 0x03;
    m_encodedBst[7] = 0x91;
    m_encodedBst[8] = 0xc0;
    m_encodedBst[9] = m_config->m_beaconId[0];
    m_encodedBst[10] = m_config->m_beaconId[1];
    m_encodedBst[11] = m_config->m_beaconId[2];
    m_encodedBst[12] = m_config->m_beaconId[3];
    m_encodedBst[13] = currentTime>>24;
    m_encodedBst[14] = currentTime>>16;
    m_encodedBst[15] = currentTime>>8;
    m_encodedBst[16] = currentTime;
    m_encodedBst[17] = 0;
    m_encodedBst[18] = 0x01;
    m_encodedBst[19] = 0x41;
    m_encodedBst[20] = 0x87;
    m_encodedBst[21] = 0x29;
    m_encodedBst[22] = 0x30;
    m_encodedBst[23] = 0x1a;
    m_encodedBst[24] = 0x00;
    m_encodedBst[25] = 0x2b;
    m_encodedBst[26] = 0x00;
    m_encodedBst[27] = 0x04;
    m_encodedBst[28] = 0x00;
    m_bstLen = 29;
    
    m_change_beaconid = false;

    m_lastBst = get_jiffies();
}

/* Init all zmq_socket */
void Scheduler::init_zmqSock()
{
    m_ctx = zmq_init(1);
    assert(m_ctx);

    /* internet manage port */
    m_manageSocket = zmq_socket(m_ctx, ZMQ_REP);
    assert(m_manageSocket);
    zmq_bind(m_manageSocket, "tcp://*:6500");

    /* uart manage port */
    m_manageSocket_uart = zmq_socket(m_ctx, ZMQ_REP);
    assert(m_manageSocket_uart);
    zmq_bind(m_manageSocket_uart, "tcp://*:6501");

    m_items[0].socket = m_manageSocket;
    m_items[0].events = ZMQ_POLLIN;
    m_items[1].socket = m_manageSocket_uart;
    m_items[1].events = ZMQ_POLLIN;

    m_reporterSocket_send_net = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(m_reporterSocket_send_net);
    int value = 1;
    /* Keep only last message  */
    zmq_setsockopt(m_reporterSocket_send_net, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_connect(m_reporterSocket_send_net, "tcp://127.0.0.1:5081");

    m_reporterSocket_recv_net = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_reporterSocket_recv_net);
    /* Keep only last message */
    zmq_setsockopt(m_reporterSocket_recv_net, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_connect(m_reporterSocket_recv_net, "tcp://127.0.0.1:5082");

    /* trade report and ack by UART */
    m_reporterSocket_send_uart = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(m_reporterSocket_send_uart);
    int value_uart = 1;
    /* Keep only last message */
    zmq_setsockopt(m_reporterSocket_send_uart, ZMQ_CONFLATE, &value_uart, sizeof(value_uart));
    zmq_connect(m_reporterSocket_send_uart, "tcp://127.0.0.1:5085");

    m_reporterSocket_recv_uart = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_reporterSocket_recv_uart);
    /* Keep only last message */
    zmq_setsockopt(m_reporterSocket_recv_uart, ZMQ_CONFLATE, &value_uart, sizeof(value_uart));
    zmq_connect(m_reporterSocket_recv_uart, "tcp://127.0.0.1:5086");


    // *********************** socket for instep ***************************** //
    m_sync_socket_send = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(m_sync_socket_send);
    int value_sync = 1;
    /* Keep only last message */
    zmq_setsockopt(m_sync_socket_send, ZMQ_CONFLATE, &value_sync, sizeof(value_sync));
    zmq_bind(m_sync_socket_send, "tcp://*:7991");

    m_sync_socket_recv = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_sync_socket_recv);
    /* Keep only last message */
    zmq_setsockopt(m_sync_socket_recv, ZMQ_CONFLATE, &value_sync, sizeof(value_sync));
    zmq_bind(m_sync_socket_recv, "tcp://*:7990");
    // ***********************************************************************//

    // *********************** socket for collect rsu status **************** //
    m_rsustatusSocket_send = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(m_rsustatusSocket_send);
    int value_status = 1;
    /* Keep only last message */
    zmq_setsockopt(m_rsustatusSocket_send, ZMQ_CONFLATE, &value_status, sizeof(value_status));
    zmq_bind(m_rsustatusSocket_send, "tcp://*:6600");

    m_rsustatusSocket_recv = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_rsustatusSocket_recv);
    /* Keep only last message */
    zmq_setsockopt(m_rsustatusSocket_recv, ZMQ_CONFLATE, &value_status, sizeof(value_status));
    zmq_bind(m_rsustatusSocket_recv, "tcp://*:6601");
    // ***********************************************************************//
}

void Scheduler::init()
{
    /* init sys_time from RTC */
    initSysTime();

    /* init ZMQ Sockets */
    init_zmqSock();

    m_config = new SchedulerConfig();
    assert(m_config);
    m_config->loadConfig();

    if(m_config->m_testmode) 
    {
        //m_tagCache->setCacheTime(TAG_CACHE_TIME_LAB);
        m_tagCache->setCacheTime(m_config->m_waitTime * 1000);
    }
    else
    {
        m_tagCache->setCacheTime(TAG_CACHE_TIME_ROAD);
    }

    /* set default lanmode */
    m_WorkMode = m_config->m_lanmode;    
    /* set send heart_beat interval */
    m_send_tick_interval = m_config->m_heartBeat * 1000;
        
    initRfProxy();
    initPsamProxy();
    initTradeControl();
    initBst();

    logm_debug("scheduler init success\n");

    return;
}


void Scheduler::run()
{
    
    logm_info("scheduler start run\n ");
    

    control_bst_time();

    rsu_status_report();

    while(1) 
    {
        if(m_config->m_enableRuning) 
        {
            sendBst();
            recvDsrcFrame();
            processTrade();
            usleep(500);
        }
        else
        {
            usleep(2000);
            monitor_RF_connected();
        }
        /* send Heart Beat to PC */
        send_tick();
        processManage();    
    }
}

void Scheduler::processTrade()
{
    std::vector<TradeControl *>::iterator iter;

    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter) 
    {
        (*iter)->process();
    }
    emptyRecvBuffer();

    return;
}

void Scheduler::sendDsrcFrame(unsigned char *txFrame, int txLength)
{
    RfProxy *rf = NULL;
    int ret;

    rf = *m_rfsIter;
    logm_debug("rf%d %d--> ", rf->sn, txLength);
    logm_debug_buffer(txFrame, txLength);

    ret = zmq_send(rf->sendSock, txFrame, txLength, ZMQ_DONTWAIT);
    if(ret < 0)
    {
        logm_err("send frame by rf%d fail \n", rf->sn);
        perror("sendDsrcFrame ");
        rf->status = rf_disconnected;
    }
    else
    {
        rf->status = rf_connected;
    }
    

    usleep((txLength/32)*1000 + 500);

    m_rfsIter++;
    if(m_rfsIter == m_rfs.end())
    {
        m_rfsIter = m_rfs.begin();
    }

    return;
}

void Scheduler::sendDsrcFrameByRf(unsigned char *txFrame, int txLength, int rfsn)
{
    int ret;

    RfProxy *rf = NULL;

    rf = m_rfsMap[rfsn];

    logm_debug("rf%d %d--> %02x%02x%02x%02x ", rf->sn, txLength,
               txFrame[1], txFrame[2], txFrame[3], txFrame[4]);
    logm_debug_buffer(txFrame, txLength);

    ret = zmq_send(rf->sendSock, txFrame, txLength, ZMQ_DONTWAIT);
    if(ret < 0) 
    {
        logm_err("send frame by rf%d fail\n", rf->sn);
        perror("sendDsrcFrameByRf ");
        rf->status = rf_disconnected;
    }
    else
    {
        rf->status = rf_connected;
    }
    

    usleep((txLength/32)*1000);

    return;
}

bool Scheduler::getSendBstRf(void)
{
    RfProxy *rf = NULL;
    int rfNum = 0;
    int i = 0;
    
    rfNum = m_rfs.size();
    for (i = 0; i < rfNum; i++)
    {
        rf = *m_rfsIter;
        if (rf->m_rfForbidBst)
        {
            m_rfsIter++;
            if(m_rfsIter == m_rfs.end()) 
            {
                m_rfsIter = m_rfs.begin();
            }
        }
        else
        {    
           return true;
        }
    }
    
    return false;
}

void Scheduler::sendClearRfFilo(void)
{
    RfProxy *rf = NULL;
    std::vector<RfProxy *>::iterator iter;
    RfProxy *rfSend = NULL;   
    int ret;
    unsigned char ClearFiloCmd[2] = {0xf5,0x00};

    rfSend = *m_rfsIter;
    for(iter=m_rfs.begin(); iter!=m_rfs.end(); ++iter) 
    {
        rf = *iter;
        if (rf->sn != rfSend->sn)
        {
            ret = zmq_send(rf->sendSock, ClearFiloCmd, 1, ZMQ_DONTWAIT);
            if(ret < 0) 
            {
                logm_err("send clear filo by rf%d fail\n", rf->sn);
            }            
        }
    }
  
    return;
}

void Scheduler::monitor_RF_connected()
{
    unsigned char test_buffer[2] = {0xFF, 0xFF};
    int ret;

    std::vector<RfProxy *>::iterator iter;
    for(iter = m_rfs.begin(); iter != m_rfs.end(); ++iter) 
    {
        ret = zmq_send((*iter)->sendSock, test_buffer, 2, ZMQ_DONTWAIT);
        if(ret < 0) 
        {
            (*iter)->status = rf_disconnected;            
        }
        else
        {
            (*iter)->status = rf_connected;
        }         
    }
}

bool Scheduler::sendBstFrame(void)
{
    RfProxy *rf = NULL;
    int ret;

    if (true == getSendBstRf())
    {
        rf = *m_rfsIter;
        logm_debug("rf%d send bst\n", rf->sn);        
        ret = zmq_send(rf->sendSock, m_encodedBst, m_bstLen, ZMQ_DONTWAIT);
        if(ret < 0) 
        {
            m_send_tick_flag = 0x00;
            rf->status = rf_disconnected;

            logm_err("send frame by rf%d fail\n", rf->sn);
            perror("sendBstFrame ");            
        }
        else
        {
            m_send_tick_flag = 0x01;

            /* if pre_status is disconnected */
            if(rf->status == rf_disconnected)
            {
                /* close old connect adn re_connect antenna */
                rf->preClose_ReConnect_Antenna();
                rf->status = rf_connected;
            }
        }
        
        usleep(500);

        m_rfsIter++;
        if(m_rfsIter == m_rfs.end())
        {
            m_rfsIter = m_rfs.begin();
        }

        return true;
    }

    return false;
}



void Scheduler::encodeBst()
{
    unsigned int currentTime;
    unsigned int beaconid;    

    currentTime = (unsigned int)time(NULL);

    /* test_mode and beacon_id change flag(configure parameter) */
    if(m_config->m_testmode && m_config->m_ifBeaconidChange) 
    {
        beaconid = m_lastBeaconId;
    #if 0
        if (m_change_beaconid)
        {
            beaconid =  (m_config->m_beaconId[0]<<24)
                           |(m_config->m_beaconId[1]<<16)
                           |(m_config->m_beaconId[2]<<8)
                           |(m_rand_beaconid);
            logm_debug("change becaonid1 = %x\n", beaconid);
        }
    #endif
    }
    else 
    {
        if (m_change_beaconid)
        {
            beaconid =  (m_config->m_beaconId[0]<<24)
                           |(m_config->m_beaconId[1]<<16)
                           |(m_config->m_beaconId[2]<<8)
                           |(m_rand_beaconid);
            logm_debug("change becaonid2 = %x\n", beaconid);
        }
        else
        {
            beaconid =  (m_config->m_beaconId[0]<<24)
                           |(m_config->m_beaconId[1]<<16)
                           |(m_config->m_beaconId[2]<<8)
                           |(m_config->m_beaconId[3]);
        }
    }

    m_encodedBst[10] = beaconid>>16;
    m_encodedBst[11] = beaconid>>8;
    m_encodedBst[12] = beaconid;
    m_encodedBst[13] = currentTime>>24;
    m_encodedBst[14] = currentTime>>16;
    m_encodedBst[15] = currentTime>>8;
    m_encodedBst[16] = currentTime;

    /* BST information comment
    ** m_encodedBst[17] Profile INTEGER, 0x00->A_ch_1, 0x01->A_ch_2,  0x10->B_ch_1, 0x11->B_ch_2
    ** m_encodedBst[18] MandApplications

    ** m_encodedBst[17] --> Antenna channel,  Antenna set this value(0x00 or 0x01)
    ** m_encodedBst[18] --> MandApplications, Control set this value(0x01)
    */
    
    m_encodedBst[19] = 0x41;  /* aid=1 */
    m_encodedBst[20] = 0x87;  /* Option indicator(ICC Transmode), Container exist */
    m_encodedBst[21] = 0x29;  /* Application parameter, Container Type = 0x29 */

    /* Option indicator(controll preread information option) */
    m_encodedBst[22] = 0x20;  /* OBU->PreRead file15(bit5) */

    m_encodedBst[23] = (0x1a + m_config->m_vst_len); /* length of sysInfo */

    m_encodedBst[24] = 0x00;  /* offset of file15 */
    m_encodedBst[25] = 0x2B;  /* lenght 0f file15 */

    if(OLDANT == m_config->m_rfsmode)
    {
        m_encodedBst[26] = 0x00;  /* ProfileList */
    }        
    else if(NEWANT == m_config->m_rfsmode)
    {
        m_encodedBst[26] = m_ant_work_mode;
    }
    m_bstLen = 27;

    return;
}

void Scheduler::control_bst_time()
{
    pthread_attr_t a_thread_attr;
    pthread_t a_thread_recv_sch;

    pthread_attr_init(&a_thread_attr);
    pthread_attr_setdetachstate(&a_thread_attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&a_thread_recv_sch, &a_thread_attr, recv_bst_time_status, (void *)this);


    return;
}

void Scheduler::rsu_status_report()
{
    pthread_attr_t a_thread_attr;
    pthread_t a_thread_recv_sch;

    pthread_attr_init(&a_thread_attr);
    pthread_attr_setdetachstate(&a_thread_attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&a_thread_recv_sch, &a_thread_attr, recv_rsu_status_collect, (void *)this);


    return;
}

void Scheduler::setAntChannel()
{
    initRfProxy();
    return;
}

void Scheduler::sendBst()
{    
    std::vector<TradeControl *>::iterator iter;

    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter) 
    {
        if((*iter)->m_forbidBst)
        {
            return;
        }   
    }

    if(timeOk(m_lastBst, m_config->m_bstInterval))
    {
        if(m_config->m_bstInterval == 70)
        {
            if(++m_send_bst_num > 7)
            {
                m_config->m_bstInterval = 20;
                m_send_bst_num = 0;
            }      
        }
        else if(m_config->m_bstInterval == 250)
        {
            usleep(50);
            if(++m_send_bst_num2 > 1)
            {
                m_config->m_bstInterval = 20;
                m_send_bst_num2 = 0;
            }      
        }
        else if(m_config->m_bstInterval == 200)
        {
            m_config->m_bstInterval = 20;    
        }
        /* if new phase antenna */
        
        /*
        if(m_config->m_rfsmode == NEWANT)
        {
            setAntModeBybst();
        }
        */
        encodeBst();
        if (true == sendBstFrame())
        {
            m_lastBst = get_jiffies();
        }
    }

    if(timeOk(m_lastBeaconIdTime, BEACONID_CHANGE_CYCLE)) 
    {
        m_lastBeaconIdTime = get_jiffies();
        m_lastBeaconId = rand();
    }

    if(timeOk(m_lastChangeIdTime, TRADE_FAIL_BEACONID_CHANGE_CYCLE)) 
    {
        m_lastChangeIdTime = get_jiffies();
        m_rand_beaconid = rand() % 255;
        m_change_beaconid = false;
    }
    return;
}

void Scheduler::initSysTime()
{
    unsigned int ret;
	rtc_time_t time;
    char modify_date[64];

	ret = bsp_rtc_read_time(&time, 0);    
	if (0 == ret) 
    {
        sprintf(modify_date, "date -s \"%02d%02d%02d%02d%04d.%02d\"", \
                time.tm_mon, time.tm_mday, time.tm_hour, time.tm_min,
                time.tm_year, time.tm_sec);
        
        system(modify_date);    
	}
	else
    {
        logm_debug("init sys time fail ret =%d", ret);
	}
}

PsamProxy *Scheduler::getPsam(int type)
{
    PsamProxy *psam = NULL;

    if(type == gb_tdes_psam)
    {
        if(m_gbtdesPsams.empty())
        {
            return NULL;
        }
        psam = m_gbtdesPsams.front();
        m_gbtdesPsams.pop_front();
        return psam;
    }
    else
    {
        if(m_universalPsams.empty())
        {
            return NULL;
        }
        psam = m_universalPsams.front();
        m_universalPsams.pop_front();
        return psam;
    }
}

void Scheduler::putPsam(PsamProxy *psam)
{
    if(psam->m_type == gb_tdes_psam)
    {
        m_gbtdesPsams.push_back(psam);
    }
    else
    {
        m_universalPsams.push_back(psam);
    }

    return;
}

bool Scheduler::_macIdExist(unsigned int macId)
{
    std::vector<TradeControl *>::iterator iter;

    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter)
    {
        if((*iter)->m_macId == macId)
        {
             return true;
        }   
    }

    return false;
}

bool Scheduler::_macIdClear(unsigned int macId)
{
    std::vector<TradeControl *>::iterator iter;

    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter)
    {
        logm_debug("self macid is %08x\n", (*iter)->m_macId);
        if((*iter)->m_macId == macId)
        {
            logm_debug("macid is same\n");
            (*iter)->goIgnore();
            (*iter)->m_macId = 0;
            return true;
        } 
    }
    logm_debug("macid is different\n");
    return false;
}
void Scheduler::addRecvFrame(unsigned char *frame, unsigned int frameLen, int rfsn)
{
    std::vector<recv_buffer_t *>::iterator iter;
    std::list<recv_buffer_t *>::iterator iter_vst;
    recv_buffer_t *recv_buffer = NULL;
    recv_buffer_t *buffer_new = NULL;
    unsigned int macId;
    int rssi_n;

    if(frame[0] == 0xe1)
    {
        macId = (frame[2]<<24)|(frame[3]<<16)|(frame[4]<<8)|frame[5];
        if(_macIdExist(macId))
        {
            return;
        }   
    }

    for(iter = m_recvBuffers.begin(); iter != m_recvBuffers.end(); ++iter)
    {
        recv_buffer = *iter;
        if((recv_buffer->length == frameLen-2)
           && (memcmp(frame, recv_buffer->buffer, 6) == 0))
           {
                rssi_n = (frame[frameLen-2]<<8) | frame[frameLen-1];
                if (rssi_n > recv_buffer->rssi)
                {
                    logm_debug("action3:rf%d,rssi=%x\n", rfsn,rssi_n);
                    recv_buffer->rfsn = rfsn;
                    recv_buffer->rssi = rssi_n;
                }
                return;
           }
    }

    for(iter_vst = m_recvVsts.begin(); iter_vst != m_recvVsts.end(); ++iter_vst)
    {
        recv_buffer = *iter_vst;
        if((recv_buffer->length == frameLen-2)
           && (memcmp(frame, recv_buffer->buffer, 6) == 0)) 
        {
            rssi_n = (frame[frameLen-2]<<8) | frame[frameLen-1];
            if (rssi_n > recv_buffer->rssi)
            {
                logm_debug("vst:rf%d,rssi=%x\n", rfsn,rssi_n);
                recv_buffer->rfsn = rfsn;
                recv_buffer->rssi = rssi_n;
            }
            return;
        }
    }    

    buffer_new = new recv_buffer_t();
    assert(buffer_new);
    // delete rssi
    memcpy(buffer_new->buffer, frame, frameLen-2);
    buffer_new->rfsn = rfsn;
    buffer_new->length = frameLen-2;    
    buffer_new->rssi = (frame[frameLen-2]<<8) | frame[frameLen-1];

    if(frame[0] == 0xe1)
    {
        m_recvVsts.push_back(buffer_new);
    }
    else
    {
        m_recvBuffers.push_back(buffer_new);
    }
}

/* Recv DSRC From Antanna */
void Scheduler::recvDsrcFrame(void)
{
    int recv_len;
    std::vector<RfProxy *>::iterator iter;
    RfProxy *rf = NULL;
    unsigned char rbuffer[512];    
    int rssi = 0;
    unsigned char rfList[SUPPORT_ANTENNA_NUM] = {0};
    unsigned char recvRfNum = 0;

    for(iter = m_rfs.begin(); iter != m_rfs.end(); ++iter)
    {
        rf = *iter;
        recv_len = zmq_recv(rf->recvSock, rbuffer, 256, ZMQ_NOBLOCK);
        if(recv_len <= 0)
        {
            continue;
        }
        rfList[rf->sn - 1] = 1;
        recvRfNum++;
        
        logm_debug("rf%d %d<-- ", rf->sn, recv_len);
        logm_debug_buffer(rbuffer, recv_len);
        
        rssi = (rbuffer[recv_len-2]<<8) | rbuffer[recv_len-1];
        logm_debug("rssi%d %x\n", rf->sn, rssi);

        addRecvFrame(rbuffer, recv_len, rf->sn);
    }

    if (0 != recvRfNum)
    {
        for(iter = m_rfs.begin(); iter != m_rfs.end(); ++iter) 
        {
            rf = *iter;
            if (1 == rfList[rf->sn - 1])
            {
                continue;
            }
            else
            {
                recv_len = zmq_recv(rf->recvSock, rbuffer, 256, ZMQ_NOBLOCK);
                if(recv_len <= 0)
                {
                    continue;
                }
                logm_debug("rf%d recv data\n", rf->sn);
                logm_debug("rf%d %d<-- ", rf->sn, recv_len);
                logm_debug_buffer(rbuffer, recv_len);
                
                rssi = (rbuffer[recv_len-2]<<8) | rbuffer[recv_len-1];
                logm_debug("rssi%d %x\n", rf->sn, rssi);
                
                addRecvFrame(rbuffer, recv_len, rf->sn);
            }
        }
    }
    return;
}

void Scheduler::emptyRecvBuffer(void)
{
    std::vector<recv_buffer_t *>::iterator iter;
    std::list<recv_buffer_t *>::iterator iterVst;
    
    if(!m_recvBuffers.empty())
    {
        for(iter = m_recvBuffers.begin(); iter != m_recvBuffers.end(); ++iter)
        {
            delete (*iter);
        }
        
        m_recvBuffers.clear();
    }

    if(!(m_recvVsts.empty()))
    {
        for(iterVst = m_recvVsts.begin(); iterVst != m_recvVsts.end(); ++iterVst)
        {
            delete (*iterVst);
        }
        
        m_recvVsts.clear();
    }
    return;
}
/* judge trade busy or idle
** @return 0 --> idle
** @return 1 --> busy
*/
unsigned char Scheduler::judge_trade_Busy_or_Idle()
{    
    std::vector<TradeControl *>::iterator iter;

    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter) 
    {
        /* if m_tradeControls state = vst_state, trade idle */
        if( (*iter)->m_state != vst_state)
        {
            /* trade busy, return 1 */
            return RSU_TRADE_BUSY;
        }
    }

    /* trade idle, return 0 */
    return RSU_TRADE_IDLE;
}

void Scheduler::send_tick()
{
    static unsigned long lastSendTickTime = get_jiffies();
    unsigned char send_tick_cmd[6] = {0xB2, 0x00, 0x00, 0x00, 0x00, 0x80};
    int ret;

    if(m_send_tick_flag)
    {
        /* if Trade is not idle, do not send tick to PC */
        if(judge_trade_Busy_or_Idle() != RSU_TRADE_IDLE)
        {
            return;
        }

        /* check heart_beat interval */
        if((get_jiffies() - lastSendTickTime) >= m_send_tick_interval)
        {
            if(m_trade_zmq_select == TRADE_ZMQ_SEL_NET)
            {
                ret = zmq_send(m_reporterSocket_send_net, send_tick_cmd, 0x06, ZMQ_DONTWAIT);
            }
            else
            {
                ret = zmq_send(m_reporterSocket_send_uart, send_tick_cmd, 0x06, ZMQ_DONTWAIT);
            }        
            
            if (ret < 0)
            {
                logm_debug("Send Heart Beat Failed! %d\n", ret);
                return;
            }

            logm_debug("send Heart Beat -> ");
            logm_debug_buffer(send_tick_cmd, 6);
            lastSendTickTime = get_jiffies();
        }
    }
}
void Scheduler::send_init_b0()
{
    static unsigned long lastSendTickTime = get_jiffies();
    unsigned char send_tick_cmd[64];
    int send_len;
    int ret;

    if(m_send_init_b0_flag)
    {
        // if Trade is idle, do not send tick to PC
        std::vector<TradeControl *>::iterator iter;    
        for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter) 
        {
            if( (*iter)->m_state != vst_state)
            {
                return;
            }
        }
        initB0(send_tick_cmd, &send_len);
        if((get_jiffies() - lastSendTickTime) >= SEND_B0_INTERVAL)
        {
            
            ret = zmq_send(m_reporterSocket_send_uart, send_tick_cmd, send_len, ZMQ_DONTWAIT); // cmd_len = 0x01
            if (ret < 0)
            {
                logm_debug("send Tick Frame by uart To PC Error! %d\n", ret);
                logm_err("send Tick Frame by uart To PC Error!\n");
                return;            
            }

            logm_debug("send Init B0 To PC -> ");
            logm_debug_buffer(send_tick_cmd, send_len);
            lastSendTickTime = get_jiffies();
        }
    }
}

void Scheduler::open_or_close_adjacent_ant()
{
    static unsigned long lastSendInstepTime = get_jiffies();
    
    if(m_config->m_control_ID == WORK_MODE_MASTER)
    {
        /* if Trade is not idle, do not send tick to PC */
        if(judge_trade_Busy_or_Idle() != RSU_TRADE_IDLE)
        {
            return;
        }

        if((get_jiffies() - lastSendInstepTime) >= SEND_OPEN_CLOSE_ADJACENT_ANT)
        {
            send_bst_interval_status(m_adjacent_ant_status, 0x30);
            m_config->m_enableRuning = (m_adjacent_ant_status == 0x00) ? true : false;
            m_adjacent_ant_status = (m_adjacent_ant_status == 0x00) ? 0x01 : 0x00;
            lastSendInstepTime = get_jiffies();
        }
    }
    else
    {
        if((get_jiffies() - lastSendInstepTime) >= RECV_CLOSE_ANT)
        {
            if((m_config->m_enableRuning == false) && (m_close_ant_from_master == 1))
            {
                m_config->m_enableRuning = true;
                m_close_ant_from_master = 0;
            }
            lastSendInstepTime = get_jiffies();
        }
    }
}

/* set Trade zmq_sockets */
void Scheduler::TradeZmqSelect(unsigned char select_flag)
{
    std::vector<TradeControl *>::iterator iter;    
    for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter) 
    {
        (*iter)->m_reporterSocket_send = (select_flag == TRADE_ZMQ_SEL_UART) ? m_reporterSocket_send_uart 
                                            : m_reporterSocket_send_net;

        (*iter)->m_reporterSocket_recv =  (select_flag == TRADE_ZMQ_SEL_UART) ? m_reporterSocket_recv_uart 
                                            : m_reporterSocket_recv_net;
    }
}

void Scheduler::processManage(void)
{
    int recv_len;
    unsigned char recv_buffer[512];
    int send_len;
    unsigned char send_buffer[512];
     int poll_rtn; 
    
    send_init_b0();
    if((m_config->m_etc_mtc == MTC) && (m_send_tick_adjacent_flag == 0x01))
    {
        open_or_close_adjacent_ant();
    }
    
    poll_rtn = zmq_poll(m_items, POLL_ITEM_COUNT, 0);
    if(poll_rtn <= 0)
    {
        return;
    }
    
    /* internet zmq */
    if(m_items[0].revents & ZMQ_POLLIN)
    {
        recv_len = zmq_recv(m_manageSocket, recv_buffer, 512, ZMQ_NOBLOCK);
        if(recv_len <= 0)
        {
            return;
        }
        
        executeManageCommand(recv_buffer, recv_len, send_buffer, &send_len);
        zmq_send(m_manageSocket, send_buffer,  send_len, 0);

        /* Trade  */
        m_trade_zmq_select = TRADE_ZMQ_SEL_NET;
    }

    /* uart */
    if(m_items[1].revents & ZMQ_POLLIN)
    {
        recv_len = zmq_recv(m_manageSocket_uart, recv_buffer, 512, ZMQ_NOBLOCK);
        if(recv_len <= 0)
        {
            return;
        }
        
        executeManageCommand(recv_buffer, recv_len, send_buffer, &send_len);
        zmq_send(m_manageSocket_uart, send_buffer,  send_len, 0);

        m_trade_zmq_select = TRADE_ZMQ_SEL_UART;
    }
    
    /* init_cmd or open-close command */
    if((recv_buffer[0] == INIT_RSU) || (recv_buffer[0] == PC_CTRL_RSU_PORT))
    {
        /* Set trade zmq_socket */
        TradeZmqSelect(m_trade_zmq_select);

        /* check if antenna not link */
        ReConnect_Antenna();        
    }

    return;
}

void Scheduler::openAnt(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    open_ant_t *pcmd = NULL;
    open_ant_ack_t *pack = NULL;

    pcmd = (open_ant_t *)command;

    if(pcmd->action_type == ACTION_CLOSE_ANT)
    {
        m_config->m_enableRuning = false;
          m_send_tick_adjacent_flag = 0x00; //stop to send tick adjacent       
    }
    else if((pcmd->action_type >= 1) && (pcmd->action_type <= 3))
    {
        m_config->m_enableRuning = true;    
         m_send_tick_adjacent_flag = 0x01;//start to send tick adjacent     
    }

#if 0 // ack
    pack = (open_ant_ack_t *)ack;
    pack->ack_type = 0x90;
    pack->status = 0;
    pack->ant_status = m_Antenna_EnableRuning ? 1 : 0;
    *ack_len = sizeof(open_ant_ack_t);
#else // do not ack to pc
    ack[0] = 0xFF;
    *ack_len = 0x01;
#endif

    return;
}

void Scheduler::coilTrigger(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    coil_status_t *pcmd;

    pcmd = (coil_status_t *)command;
    
    if(pcmd->coil_status != 0)
    {        
        m_coil_trigger_flag = 1;

        // coil_trigger, open antenna
        if(m_config->m_coil_trigger_antenna)
        {
            m_config->m_enableRuning = true;
        }
    }
    else
    {
        m_coil_trigger_flag = 0;

        // coil_trigger disappear, close antenna
        if(m_config->m_coil_trigger_antenna)
        {
            m_config->m_enableRuning = false;
        }
    }
    
    logm_debug("Coil Trigger status %02x \n", pcmd->coil_status);
    
    ack[0] = 0xFF;
    *ack_len =0x01;
}
/*********************************湖北新增***************************************/
void Scheduler::pcctrlrfid(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    pc_ctrl_state_t *pcmd;

    pcmd = (pc_ctrl_state_t *)command;
    
    if(pcmd->rsu_id == 0)
    {        
         m_config->m_ifBeaconidChange = false;
    }
    else
    {
      m_config->m_ifBeaconidChange = true;
    }
    
    logm_debug("PC Ctrl RSUID is %02x \n", pcmd->rsu_id);
    
    ack[0] = 0xff;
    *ack_len = 1;
}


void Scheduler::QueryAntStatus(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    open_ant_t *pcmd;
    open_ant_ack_t *pack;

    pcmd = (open_ant_t *)command;
    
    pack = (open_ant_ack_t *)ack;
    pack->ack_type = query_ant_ack;
    pack->status = 0;
    pack->ant_status = m_config->m_enableRuning ? 1 : 0;

    *ack_len = sizeof(open_ant_ack_t);

    return;
}

void Scheduler::setBeaconId(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_beaconid_t *pcmd;
    set_beaconid_ack_t *pack;

    pcmd = (set_beaconid_t *)command;
    pack = (set_beaconid_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_BEACONID)
    {
        m_config->m_ifBeaconidChange = pcmd->ifchange ? true : false;
        m_config->m_beaconidCycle = pcmd->change_cycle;
        memcpy(m_config->m_beaconId, pcmd->beaconid, 4);
        m_config->saveConfig();
    }

    pack->ack_type = set_beaconid_ack;
    pack->status = 0;
    pack->ifchange = m_config->m_ifBeaconidChange;
    pack->change_cycle = m_config->m_beaconidCycle;
    memcpy(pack->beaconid, m_config->m_beaconId, 4);

    *ack_len = sizeof(set_beaconid_ack_t);

    return;
}

void Scheduler::setCoordinateLimit(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_coordinate_t *pcmd;
    set_coordinate_ack_t *pack;

    pcmd = (set_coordinate_t *)command;
    pack = (set_coordinate_ack_t *)ack;
    
    // set coordinate parameter
    if(pcmd->action_type == 1)
    {
        m_config->m_location_X1 = pcmd->coordinate_x1;
        m_config->m_location_X2 = pcmd->coordinate_x2;
        m_config->m_location_Y_max = pcmd->coordinate_y_max;
        m_config->m_location_Y_min = pcmd->coordinate_y_min;
        m_config->m_location_sub_Y = pcmd->coordinate_sub_y;
        m_config->m_location_sub_X1 = pcmd->coordinate_sub_x1;
        m_config->m_location_sub_X2 = pcmd->coordinate_sub_x2;
        m_config->m_location_limit = pcmd->ifusing ? true : false;
        m_config->saveConfig();
    }        

    pack->ack_type = set_coordinate_limit_ack;
    pack->status = 0x00;
    pack->coordinate_x1 = m_config->m_location_X1;
    pack->coordinate_x2 = m_config->m_location_X2;
    pack->coordinate_y_max = m_config->m_location_Y_max;
    pack->coordinate_y_min = m_config->m_location_Y_min;
    pack->coordinate_sub_y = m_config->m_location_sub_Y;
    pack->coordinate_sub_x1 = m_config->m_location_sub_X1;
    pack->coordinate_sub_x2 = m_config->m_location_sub_X2;
    pack->ifusing = m_config->m_location_limit;

    *ack_len = sizeof(set_coordinate_ack_t);
}

void Scheduler::setCoilTrigger(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_coil_trigger_t *pcmd;
    set_coil_trigger_ack_t *pack;

    pcmd = (set_coil_trigger_t *)command;
    pack = (set_coil_trigger_ack_t *)ack;

    if(pcmd->action_type == 1)
    {
        m_config->m_coil_trigger_antenna = pcmd->coil_trig_antenna ? true : false;
        m_config->m_coil_trigger_enable = pcmd->coil_trig_confine_ifuse ? true : false;
        m_config->m_coil_trigger_confine = pcmd->coil_trig_confine;
        m_config->saveConfig();
    }

    pack->ack_type = set_coil_trigger_ack;
    pack->status = 0x00;
    pack->coil_trig_antenna = m_config->m_coil_trigger_antenna;
    pack->coil_trig_confine_ifuse = m_config->m_coil_trigger_enable;
    pack->coil_trig_confine = m_config->m_coil_trigger_confine;

    *ack_len = sizeof(set_coil_trigger_ack_t);
}


void Scheduler::setBeaconIdTest(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_beaconid_test_t *pcmd;
    set_beaconid_test_ack_t *pack;

    pcmd = (set_beaconid_test_t *)command;
    pack = (set_beaconid_test_ack_t *)ack;

    pack->acktype = 0xed;
    pack->errcode = 0;

    if(pcmd->beaconidstatus == 0)
    {
        m_config->m_ifBeaconidChange = false;
        memcpy(m_config->m_beaconId, pcmd->beaconid, 4);
        m_config->saveConfig();
    }
    else if(pcmd->beaconidstatus == 1)
    {
        m_config->m_ifBeaconidChange = true;
        m_config->saveConfig();
    }

    pack->beaconidstatus = m_config->m_ifBeaconidChange ? 0x01 : 0x00;
    memcpy(pack->beaconid, m_config->m_beaconId, 4);

    *ack_len = sizeof(set_beaconid_test_ack_t);
    return;
}

static void *Scheduler::recv_bst_time_status(void *para)
{
    Scheduler *Scheduler_handle = NULL;

    Scheduler_handle = (Scheduler *)para;

    unsigned char recv_buffer[64];
    unsigned char send_buffer[64];
    int recv_len;
    int send_len;
    while(1)
    {
        recv_len = zmq_recv(Scheduler_handle->m_sync_socket_recv, recv_buffer, 64, 0);
        if(recv_len < 0)
        {
            logm_debug("recv change bst interval fail \n");
        }
        else if(recv_len > 2)
        {
            Scheduler_handle->ExecuteBstIntervalCommand(recv_buffer, recv_len, send_buffer, &send_len);
  
            zmq_send(Scheduler_handle->m_sync_socket_send, send_buffer, send_len, 0);

        }  
    }
    return;
}


static void *Scheduler::recv_rsu_status_collect(void *para)
{
    Scheduler *Scheduler_handle =NULL;
    int recv_len;
    int send_len;
    Scheduler_handle = (Scheduler *)para;

    unsigned char recv_buffer[64];
    unsigned char send_buffer[64];
    
    while(1)
    {
        recv_len = zmq_recv(Scheduler_handle->m_rsustatusSocket_recv, recv_buffer, 64, 0);
        
        if(recv_len < 0)
        {
            logm_debug("recv change bst interval fail \n");
        }
        else if(recv_len >= 2)
        {
            logm_debug("recv data from master:");
            logm_debug_buffer(recv_buffer, recv_len);
            Scheduler_handle->ExecuteRsuStatusCommand(recv_buffer, recv_len, send_buffer, &send_len);
  
            zmq_send(Scheduler_handle->m_rsustatusSocket_send, send_buffer, send_len, 0);

        }  
    }
    return;
}

void Scheduler::send_bst_interval_status(unsigned char ant_stute, unsigned char time_interval)
{
    
    unsigned char send_buff[64] = {0xBF, 0x01, 0x20, 0x00, 0x00, 0xBF};//open rfs interval 100ms
    int send_len = 6;
    int ret;
    send_buff[1] = ant_stute;
    send_buff[2] = time_interval;
    ret = zmq_send(m_sync_socket_send, send_buff, send_len, ZMQ_DONTWAIT);
    if(ret < 0)
    {
        logm_debug("send bst interval failed \n");
    }
    else
    {
        logm_debug("send data to pc len  is %d -->",send_len);
        logm_debug_buffer(send_buff,send_len);
    }
}
void Scheduler::send_obu_coordinate_message(unsigned int macid, int location_x, int location_y)
{
    
    unsigned char send_buff[64] = {0xBE};//open rfs interval 100ms
    int send_len = 13;
    int ret;
    memcpy(&send_buff[1], &macid, 4);
    memcpy(&send_buff[5], &location_x, 4);
    memcpy(&send_buff[9], &location_y, 4);
    ret = zmq_send(m_sync_socket_send, send_buff, send_len, ZMQ_DONTWAIT);
    if(ret < 0)
    {
        logm_debug("send obu coordinate message failed \n");
    }
    else
    {
        logm_debug("send obu coordinate message to pc len  is %d -->",send_len);
        logm_debug_buffer(send_buff,send_len);
    }
}

void Scheduler::send_instep_obuId_to_adjacent(unsigned char status,unsigned int macid)
{
    unsigned char send_buff[64] = {0xBD};//open rfs interval 100ms
    int send_len = 6;
    int ret;
    send_buff[1] = status;
    memcpy(&send_buff[2], &macid, 4);
    ret = zmq_send(m_sync_socket_send, send_buff, send_len, ZMQ_DONTWAIT);
    if(ret < 0)
    {
        logm_debug("send obuID to adjacent failed \n");
    }
    else
    {
        logm_debug("send obuID to adjacent len is %d -->",send_len);
        logm_debug_buffer(send_buff,send_len);
    }
}

void Scheduler::send_obu_coordinate_rssi_num_message(unsigned int macid, int location_x, int location_y, int rssi, int rssi_num)
{
    
    unsigned char send_buff[64] = {0xBC};//open rfs interval 100ms
    int send_len = 21;
    int ret;
    memcpy(&send_buff[1], &macid, 4);
    memcpy(&send_buff[5], &location_x, 4);
    memcpy(&send_buff[9], &location_y, 4);
    memcpy(&send_buff[13], &rssi, 4);
    memcpy(&send_buff[17], &rssi_num, 4);

    ret = zmq_send(m_sync_socket_send, send_buff, send_len, ZMQ_DONTWAIT);
    if(ret < 0)
    {
        logm_debug("send obu coordinate message failed \n");
    }
    else
    {
        logm_debug("send obu coordinate message to pc len  is %d -->",send_len);
        logm_debug_buffer(send_buff,send_len);
    }
}

int Scheduler::judgeWhetherTranscation(unsigned int macid, int location_x, int location_y, int rssi, int rssi_num)
{
    for(std::list<obu_coordinate_t *>::iterator iter=m_obuCoordinate.begin();
		iter != m_obuCoordinate.end(); ++iter)
        {
            if(macid != (*iter)->mac_id)
            {
                logm_debug("no search same obu,agree to transcation\n");
                return 1;
            }
            else
            {
                if(((*iter)->location_X > m_config->m_location_X1) || ((*iter)->location_X < m_config->m_location_X2))
                {
                    logm_debug("my lane X is %dcm\n", (*iter)->location_X);
                    logm_debug("this obu do not in my lane\n");
                    return 1;
                }
                else
                {
                    if(rssi > (*iter)->rssi)
                    {
                        logm_debug("my lane rssi is %d, other lane rssi is %d\n", (*iter)->rssi, rssi);
                        logm_debug("rssi is small, this obu do not in my lane\n");
                        return 1;
                    }
                    else
                    {
                        logm_debug("my lane rssi is %d, other lane rssi is %d\n", (*iter)->rssi, rssi);
                        logm_debug("rssi is big, this obu in my lane\n");
                        return 0;
                    }
                    
                }
                
            }
            
        }
}

void Scheduler::setAntConfig(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_ant_config_t *pcmd;
    set_ant_config_ack_t *pack;
    RfPara *rfPara;

    pcmd = (set_ant_config_t *)command;
    pack = (set_ant_config_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_RFCONFIG)
    {
        m_config->clearRfConfig();
        for(int i=0; i<5; ++i) // modify 4-->5, support 5 annts
        {
            rfPara = new RfPara();
            assert(rfPara);
            rfPara->rfsn = pcmd->config[i].antid;
            rfPara->isEnable = pcmd->config[i].ifenable;
            rfPara->power = pcmd->config[i].power;
            rfPara->channel = pcmd->config[i].channel;
            sprintf(rfPara->ipaddr, "%d.%d.%d.%d", pcmd->config[i].ipaddr[0], \
                    pcmd->config[i].ipaddr[1], pcmd->config[i].ipaddr[2],
                    pcmd->config[i].ipaddr[3]);
            m_config->m_rfConfig.push_back(rfPara);
        }
        m_config->saveConfig();
    }

    pack->ack_type = set_ant_config_ack;
    pack->status = 0;

    int i=0;
    struct in_addr ipaddr;
    for(std::list<RfPara *>::iterator iter=m_config->m_rfConfig.begin();
        iter!=m_config->m_rfConfig.end(); ++iter)
    {
        pack->config[i].antid = (*iter)->rfsn;
        pack->config[i].ifenable = (*iter)->isEnable;
        pack->config[i].power = (*iter)->power;
        pack->config[i].channel = (*iter)->channel;
        inet_aton((*iter)->ipaddr, &ipaddr);
        pack->config[i].ipaddr[0] = ipaddr.s_addr>>24;
        pack->config[i].ipaddr[1] = ipaddr.s_addr>>16;
        pack->config[i].ipaddr[2] = ipaddr.s_addr>>8;
        pack->config[i].ipaddr[3] = ipaddr.s_addr;
        ++i;
    }

    *ack_len = sizeof(set_ant_config_ack_t);

    return;
}

void Scheduler::setPsamConfig(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_psam_config_t *pcmd;
    set_psam_config_ack_t *pack;
    PsamPara *psamPara;

    pcmd = (set_psam_config_t *)command;
    pack = (set_psam_config_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_PSAMCONFIG)
    {
        m_config->clearPsamConfig();
        for(int i=0; i<12; ++i)
        {
            psamPara = new PsamPara();
            assert(psamPara);
            psamPara->psamid = pcmd->config[i].psamid;
            psamPara->isEnable = pcmd->config[i].ifenable;
            psamPara->type = pcmd->config[i].type;
            m_config->m_psamConfig.push_back(psamPara);
        }
        m_config->saveConfig();
    }

    pack->ack_type = set_psam_config_ack;
    pack->status = 0;

    int i=0;
    for(std::vector<PsamPara *>::iterator iter=m_config->m_psamConfig.begin();
        iter!=m_config->m_psamConfig.end(); ++iter) 
    {
        pack->config[i].psamid = (*iter)->psamid;
        pack->config[i].ifenable = (*iter)->isEnable;
        pack->config[i].type = (*iter)->type;
        ++i;
    }

    *ack_len = sizeof(set_psam_config_ack_t);

    return;
}

void Scheduler::setLaneMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_lane_mode_t *pcmd;
    set_lane_mode_ack_t *pack;

    pcmd = (set_lane_mode_t *)command;
    pack = (set_lane_mode_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_LANEMODE)
    {
        m_config->m_lanmode = pcmd->lanemode;
        m_config->m_etc_mtc = pcmd->etcmtc;
        m_config->saveConfig();
    }

    pack->ack_type = set_lane_mode_ack;
    pack->status = 0;
    pack->lanemode = m_config->m_lanmode;
    pack->etcmtc = m_config->m_etc_mtc;
    *ack_len = sizeof(set_lane_mode_ack_t);

    return;
}

void Scheduler::setDefaultConfig(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_default_config_t *pcmd;
    set_default_config_ack_t *pack;

    pcmd = (set_default_config_t *)command;
    pack = (set_default_config_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_DEFAULT_CONFIG)
    {
        m_config->loadDefaultConfig();
        m_config->saveConfig();
    }

    pack->ack_type = set_default_config_ack;
    pack->status = 0;
    *ack_len = sizeof(set_default_config_ack_t);
    return;
}

void Scheduler::setControlId(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_parallel_number_t *pcmd;
    set_control_id_ack_t *pack;

    pcmd = (set_parallel_number_t *)command;
    pack = (set_control_id_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_PARALLEL)
    {
        m_config->m_control_ID = pcmd->number;
        m_config->saveConfig();
    }

    pack->ack_type = set_control_id_ack;
    pack->status = 0;
    pack->number = m_config->m_control_ID;

    *ack_len = sizeof(set_control_id_ack_t);

    return;
}

void Scheduler::setControlMasterIp(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_control_master_ip_t *pcmd;
    set_control_master_ip_ack_t *pack;

    pcmd = (set_control_master_ip_t *)command;
    pack = (set_control_master_ip_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_PARALLEL)
    {
        //memcpy(m_config->m_master_ip, pcmd->control_master_ip, 24);
        sprintf(m_config->m_master_ip, "%d.%d.%d.%d", pcmd->control_master_ip[0], \
                    pcmd->control_master_ip[1], pcmd->control_master_ip[2],
                    pcmd->control_master_ip[3]);
        m_config->saveConfig();
    }

    pack->ack_type = set_master_ip_ack;
    pack->status = 0;

    struct in_addr master_ip;

    inet_aton(m_config->m_master_ip, &master_ip);
    pack->control_master_ip[0] = master_ip.s_addr>>24;
    pack->control_master_ip[1] = master_ip.s_addr>>16;
    pack->control_master_ip[2] = master_ip.s_addr>>8;
    pack->control_master_ip[3] = master_ip.s_addr;
        

    *ack_len = sizeof(set_control_master_ip_ack_t);
    return;
}

void Scheduler::setTradeTimePara(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_time_para_t *pcmd;
    set_time_para_ack_t *pack;

    pcmd = (set_time_para_t *)command;
    pack = (set_time_para_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_TIMEPARA)
    {
        m_config->m_bstInterval = pcmd->time_para.bst_interval;        
        m_config->m_obuGetsecureInterval = pcmd->time_para.obu_getsecure_interval;
        m_config->m_obuReadFileInterval = pcmd->time_para.obu_read_file_interval;
        m_config->m_obuWriteFileInterval = pcmd->time_para.obu_write_file_interval;
        m_config->m_obutimeout = (pcmd->time_para.obu_timeout[0]<<8)|pcmd->time_para.obu_timeout[1];
        m_config->m_obuRepeatNum = pcmd->time_para.obu_repeat_num;
        m_config->saveConfig();
    }

    pack->ack_type = set_time_para_ack;
    pack->status = 0;
    pack->time_para.bst_interval = m_config->m_bstInterval;      
    pack->time_para.obu_getsecure_interval = m_config->m_obuGetsecureInterval;
    pack->time_para.obu_read_file_interval = m_config->m_obuReadFileInterval;
    pack->time_para.obu_write_file_interval = m_config->m_obuWriteFileInterval;
    pack->time_para.obu_timeout[0] = m_config->m_obutimeout>>8;
    pack->time_para.obu_timeout[1] = m_config->m_obutimeout;
    pack->time_para.obu_repeat_num = m_config->m_obuRepeatNum;

    *ack_len = sizeof(set_time_para_ack_t);

    return;
}

void Scheduler::setWorkMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_workmode_t *pcmd;
    set_workmode_ack_t *pack;

    pcmd = (set_workmode_t *)command;
    pack = (set_workmode_ack_t *)ack;

    if(pcmd->action_type == ACTION_SET_WORKMODE)
    {
        m_config->m_testmode = (pcmd->workmode == 2);
        m_config->m_waitTime = pcmd->wait_time;
        if(m_config->m_testmode)
        {
            //m_tagCache->setCacheTime(30*1000);
            m_tagCache->setCacheTime(m_config->m_waitTime * 1000);
        }
        else
        {
            m_tagCache->setCacheTime(6*60*1000);
        }
        m_config->saveConfig();
    }

    pack->ack_type = set_workmode_ack;
    pack->status = 0;
    pack->workmode = m_config->m_testmode ? 2 : 1;
    pack->wait_time = m_config->m_waitTime;

    *ack_len = sizeof(set_workmode_ack_t);

    return;
}
void Scheduler::setRfsMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_rfsmode_t *pcmd;
    set_rfsmode_ack_t *pack;

    pcmd = (set_rfsmode_t *)command;
    pack = (set_rfsmode_ack_t *)ack;
    if(pcmd->action_type == ACTION_SET_WORKMODE)
    {
        m_config->m_rfsmode = pcmd->workmode;
        m_config->m_direction = pcmd->direction;
        m_config->saveConfig();
    }
    pack->ack_type = set_rfsmode_ack;
    pack->status = 0;
    pack->workmode = m_config->m_rfsmode;
    pack->direction = m_config->m_direction;
    *ack_len = sizeof(set_rfsmode_ack_t);
    return;
}

void Scheduler::setAntModeSwitch(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_antmode_switch_t *pcmd;
    set_antmode_switch_ack_t *pack;

    pcmd = (set_antmode_switch_t *)command;
    pack = (set_antmode_switch_ack_t *)ack;

    if(pcmd->action_type == 1)
    {
        m_config->m_near_switch = pcmd->near_switch;
        m_config->m_mid_near_switch = pcmd->mid_near_switch;
        m_config->m_mid_far_switch = pcmd->mid_far_switch;
        m_config->m_far_switch = pcmd->far_switch;
        m_config->saveConfig();
    }

    pack->ack_type = set_antmode_switch_ack;
    pack->status = 0x00;
    pack->near_switch = m_config->m_near_switch;
    pack->mid_near_switch = m_config->m_mid_near_switch;
    pack->mid_far_switch = m_config->m_mid_far_switch;
    pack->far_switch = m_config->m_far_switch;
    
    *ack_len = sizeof(set_antmode_switch_ack_t);
    return;
}
void Scheduler::setVstLen(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    set_vst_len_t *pcmd;
    set_vst_len_ack_t *pack;

    pcmd = (set_vst_len_t *)command;
    pack = (set_vst_len_ack_t *)ack;

    if(pcmd->action_type == 1)
    {
        m_config->m_vst_len = pcmd->vst_len;
        m_config->saveConfig();
    }

    pack->ack_type = set_vst_len_ack;
    pack->status = 0x00;
    pack->vst_len = m_config->m_vst_len;
  
    *ack_len = sizeof(set_vst_len_ack_t);
    return;
}

void Scheduler::rfTestCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    int ret;
    void *sock;
    std::vector <RfProxy *>::iterator iter;

    for(iter = m_rfs.begin(); iter!= m_rfs.end(); ++iter)
    {
        logm_debug(" rfsn is %d\n", (*iter)->sn);
        sock = (*iter)->cfgSock;
        ret = zmq_send(sock, command, command_len, 0);
        if(ret <= 0) 
        {
            logm_err("send  error\n");
            *ack_len = 0;
            return;
        }
        ret = zmq_recv(sock, ack, 256, 0);
        if(ret <= 0) 
        {
            logm_err("recv error\n");
            *ack_len = 0;
            return;
        }
    }

    *ack_len = ret;
    return;
}

/*
data format is
typedef struct {
    unsigned char rsustatus;
    unsigned char beaconid[4];
    unsigned char temp[2];
    unsigned char rfs_status;
    unsigned char rfs_channel;
    unsigned char rfs_power;
    unsigned char rfs_send_status;
    unsigned char rfs_recv_status;
    unsigned char rfs_temp[2];
}rsu_status_t;
*/
void Scheduler::collect_rsu_status(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    unsigned char control_status;
    unsigned char *PSAM_Num1_ptr = NULL;
    unsigned char *RSU_AntennaConfigNum_ptr = NULL;
    unsigned char *RSU_AntennaNormalNum_ptr = NULL;
    rsu_collect_status_t * pack;
    pack = (rsu_collect_status_t *)ack;
    switch(command[1])
        {
            case 0x01://collect rsu status
            {
                pack->cmd = 0xbc;
                pack->rsustatus = 0x00;
                pack->beaconid[0] = m_config->m_beaconId[0];
                pack->beaconid[1] = m_config->m_beaconId[1];
                pack->beaconid[2] = m_config->m_beaconId[2];
                pack->beaconid[3] = m_config->m_beaconId[3];
                 //collect psam status
                PSAM_Num1_ptr = &ack[sizeof(rsu_collect_status_t)];
                *PSAM_Num1_ptr = 0;
                collect_psam_status(PSAM_Num1_ptr, &control_status);
                RSU_AntennaConfigNum_ptr = &PSAM_Num1_ptr[1 + (*PSAM_Num1_ptr) * sizeof(collect_psam_status_t)];
                collect_Antenna_Status(RSU_AntennaConfigNum_ptr);

                *ack_len = sizeof(rsu_collect_status_t) + 1 + (*PSAM_Num1_ptr) * sizeof(collect_psam_status_t) + 
                2 + (*RSU_AntennaConfigNum_ptr) * sizeof(collect_antenna_status_t);
                break;
            }
            case 0x02:
            {
                break;
            }
            case 0x03:
            {
                break;
            }
            default:
            {
                break;
            }
        }
    //*ack_len = sizeof(rsu_collect_status_t);
    return;
}

int Scheduler::collect_psam_status(unsigned char *statusBuffer, unsigned char *psam_run_status)
{
    int i = 0;
    int infor_len;
    collect_psam_status_t *PSAM_Status = NULL;
    unsigned char psam_normal = 0x00;

    /* (1) first byte: PSAM_number
       (2) other bytes(three bytes in a group): psam_channel ID and PSAM_Status  psam_AuthStatus
       (3) PSAM_Status: 0x00->normal, 0x01->abnormal
       (4) psam_AuthStatus: 0x00->auth_ok, 0x01->not auth 
    */

    // set value_status 0x00
    *psam_run_status = 0x00;

    /* current Control PSAM status */
    std::vector<PsamPara *>::iterator iter = m_config->m_psamConfig.begin();
    for(; iter != m_config->m_psamConfig.end(); ++iter)
    {
        if((*iter)->isEnable) /* judge enable and status */
        {
            PSAM_Status = (collect_psam_status_t *)(&statusBuffer[1 + i * sizeof(collect_psam_status_t)]);
            PSAM_Status->psam_channel = (*iter)->psamid;
            PSAM_Status->psam_RunStatus = (*iter)->status;
            PSAM_Status->psam_AuthStatus = (*iter)->AuthStatus;
            i++;

            /* if psams_status = 0x01 --> abnormal */
            if((*iter)->status == PSAM_STATUS_OK)
            {                
                psam_normal++;
            }


        }
    }
    statusBuffer[0] = i; // set PSAM number

    /* all psam abnormal */
    if(psam_normal == 0x00)
    {
        /* set controll_psam status */
        *psam_run_status = PSAM_STATUS_NOT_OK;
    }

    infor_len = 1 + i * sizeof(collect_psam_status_t);

    return infor_len;
}

unsigned char Scheduler::collect_Antenna_Status(unsigned char *Ant_StatusBuffer)
{
    unsigned char i = 0;
    unsigned char ant_normal_num = 0;
    collect_antenna_status_t *Ant_Status = NULL;

    // antenna status
    std::vector<RfProxy *>::iterator iter;
    for(iter = m_rfs.begin(); iter != m_rfs.end(); ++iter) 
    {
        Ant_Status = (collect_antenna_status_t *)(&Ant_StatusBuffer[2 + i * sizeof(collect_antenna_status_t)]);
        Ant_Status->ant_sn = (*iter)->sn;  // ant_ID
        Ant_Status->ant_run_status = (*iter)->status; // run status
        Ant_Status->ant_PllChannel = (*iter)->m_channel;  // PLL channel
        Ant_Status->ant_power = (*iter)->m_power;  // antenna power
        i++;

        //set number of ant
        Ant_StatusBuffer[0] = i;
        // number of normal_antennas
        if((*iter)->status == 0x00)
        {
            ant_normal_num++;
        }
        Ant_StatusBuffer[1] = ant_normal_num;
    }

    return ant_normal_num;
}
void Scheduler::setAntModeBybst(void)
{
    unsigned int num;
    switch(m_ant_work_mode)
    {
        case NEAR_END:
        {
            m_near_num--;
            if(m_near_num <= 0)
            {
                m_ant_work_mode = MID_END;
                m_near_num = 0;
                m_mid_to_near_num = 5;
                m_mid_to_far_num = 5;
                m_far_num = 0;
                logm_debug("near_mode no recv vst change to mid_mode\n");
            }
            break;
        }
        case MID_END:
        {
            m_mid_to_near_num--;
            m_mid_to_far_num--;
            if(m_config->m_etc_mtc == ETC_COIL)
            {
                if(m_mid_to_near_num <= 0)
                {
                    m_ant_work_mode = NEAR_END;
                    m_near_num = 5;
                    m_mid_to_near_num = 0;
                    m_mid_to_far_num = 0;
                    m_far_num = 0;
                    logm_debug("mid_mode no recv vst change to near_mode\n");
                }
                else if(m_mid_to_far_num <= 0)
                {
                    m_ant_work_mode = FAR_END;
                    m_near_num = 0;
                    m_mid_to_near_num = 0;
                    m_mid_to_far_num = 0;
                    m_far_num = 5;
                    logm_debug("mid_mode no recv vst change to far_mode\n");
                }
            }
            else
            {
                if(m_mid_to_near_num <= 0)
                {
                    m_ant_work_mode = NEAR_END;
                    m_near_num = 5;
                    m_mid_to_near_num = 0;
                    m_mid_to_far_num = 0;
                    m_far_num = 0;
                    logm_debug("mid_mode no recv vst change to near_mode\n");
                }
            }
            break;
        }
        case FAR_END:
        {
            m_far_num--;
            if(m_far_num <= 0)
            {
                m_ant_work_mode = NEAR_END;
                m_near_num = 5;
                m_mid_to_near_num = 0;
                m_mid_to_far_num = 0;
                m_far_num = 0;
                logm_debug("far_mode no recv vst change to near_mode\n");
            }
            break;
        }
        default:
            break;
    }
    return;
}
void Scheduler::set_bst_interval(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    if(command[1] == 0x00)
    {
        std::vector<TradeControl *>::iterator iter;    
        for(iter = m_tradeControls.begin(); iter != m_tradeControls.end(); ++iter) 
        {
            if((*iter)->m_state != vst_state)
            {
                m_config->m_enableRuning = true;
                m_config->m_bstInterval = 25;
            }
            else
            {
                m_config->m_enableRuning = false;
                m_close_ant_from_master = 1;
            }
        } 
    }
    else if(command[1] == 0x01)
    {
        //m_config->m_enableRuning = true;
        switch(command[2])
        {
        case 0x20:
        {
            m_config->m_bstInterval = 20;
            m_send_bst_num = 0;
            m_send_bst_num2 = 0;
            //m_bst_interval = 20;
            break;
        }
        case 0x30:
        {
            m_config->m_bstInterval = 30;
            m_config->m_enableRuning = true;
            //m_bst_interval = 40;
            break;
        }
        case 0x40:
        {
            m_config->m_bstInterval = 45;
            break;
        }
        case 0x70:
        {
            if(m_car_status == 0x01)
            {
                m_config->m_bstInterval = 50;
            }
            else
            {
                m_config->m_bstInterval = 70;
            }           
            //m_bst_interval = 90;
            break;
        }
        case 0x99:
        {
            if(m_car_status == 0x02)
            {
                m_config->m_bstInterval = 40;
            }
            else
            {
                m_config->m_bstInterval = 250;
            }           
            break;
        }
        default:
        {
            break;
        }
        }
    }
    ack[0] = 0xff;
    ack[1] = 0x00;
    *ack_len = 2;
    return;
}
void Scheduler::initB0(unsigned char *send, int *send_len)
{
    init_rsu_ack_t *pack;
    pack = (init_rsu_ack_t *)send;

    pack->cmd_ack = INIT_RSU_ACK;
    pack->RSUStatus = 0x00; // RSU Status
    
    //PSAM information
    PsamProxy *psam = m_gbtdesPsams.front();
    memcpy(pack->Psam1TerminalID, psam->m_terminalID, 6); 

    pack->RSUAlgID = 0x00;
    pack->RSUManuID = m_config->m_beaconId[0];
    memcpy(pack->RSUID, &m_config->m_beaconId[1], 3);
    pack->RSUVersion[0] = 0xA4;
    pack->RSUVersion[1] = 0xA7;

    PsamProxy *psam1 = m_gbtdesPsams.front();
    pack->Psam1Ver=psam1->m_psamVersion;
    pack->PSAMAuthStatus = PsamAutState;
    memset(pack->Reserve, 0x00, 5);

    *send_len = sizeof(init_rsu_ack_t);

    return;
}
void Scheduler::initRsu(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    init_rsu_t *pcmd = NULL;
    init_rsu_ack_t *pack = NULL;
    
    RfProxy *rfProxy = NULL;
    rtc_time_t time;
    char modify_date[64];    
    
    pcmd = (init_rsu_t *)command;
    pack = (init_rsu_ack_t *)ack;

    time.tm_year = BCD2HEX(pcmd->time[0])*100 + BCD2HEX(pcmd->time[1]);
    time.tm_mon = BCD2HEX(pcmd->time[2]);
    time.tm_mday = BCD2HEX(pcmd->time[3]);
    time.tm_hour = BCD2HEX(pcmd->time[4]);
    time.tm_min = BCD2HEX(pcmd->time[5]);
    time.tm_sec = BCD2HEX(pcmd->time[6]);

    logm_debug("write sec: %d min:%d hour:%d mday:%d mon:%d year:%d \n",
          time.tm_sec, time.tm_min, time.tm_hour, time.tm_mday, time.tm_mon, time.tm_year);

    sprintf(modify_date, "date -s \"%02d%02d%02d%02d%04d.%02d\"", \
            time.tm_mon, time.tm_mday, time.tm_hour, time.tm_min, time.tm_year, time.tm_sec);
    
    system(modify_date);

    time.tm_wday = 1;
    (void)bsp_rtc_write_time(&time, 0);
    
    // get parameter from PC init Cmd
    m_PC_Init_Ant_Txpower = pcmd->Main_TxPower; // RSU power (1-31)
    m_WorkMode = pcmd->lanmode;
    m_IsAuth = pcmd->AuthFlag; //是否授权
    m_InitEf04Opt = pcmd->Ef04Opt;
    m_InitEf04Offset[0] = pcmd->Ef04Offset[0];
    m_InitEf04Offset[1] = pcmd->Ef04Offset[1];
    m_InitEf04Len[0] = pcmd->Ef04Len[0];
    m_InitEf04Len[1] = pcmd->Ef04Len[1];

    m_initef04len = (m_InitEf04Len[0] << 8) + m_InitEf04Len[1];
    m_send_init_b0_flag = 0;

    // ACK infomation to PC
    pack->cmd_ack = INIT_RSU_ACK;
    pack->RSUStatus = 0x00; // RSU Status
    
    PsamProxy *psam = m_gbtdesPsams.front();
    memcpy(pack->Psam1TerminalID, psam->m_terminalID, 6); 
   
   
    pack->RSUAlgID = 0x00;
    pack->RSUManuID = m_config->m_beaconId[0];
    memcpy(pack->RSUID, &m_config->m_beaconId[1], 3);

    pack->RSUVersion[0] = 0xA4;
    pack->RSUVersion[1] = 0xA7;
  
    PsamProxy *psam1 = m_gbtdesPsams.front();
  
    pack->Psam1Ver=psam1->m_psamVersion;
    
    pack->PSAMAuthStatus = PsamAutState;
      
   
    memset(pack->Reserve, 0x00,5);


    *ack_len = sizeof(init_rsu_ack_t);
      

    m_send_tick_flag = 0x01; // start to send HeartBeat
    m_config->m_enableRuning = false; // close ant

#if 0
    
    logm_debug("receive PC init cmd, start to send tick to PC...!\n");
#endif

    return;
}

void Scheduler::AfterInit_OpenAnt(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    if(m_config->m_coil_trigger_antenna == false)
    {
        /* Open antenna */
        m_config->m_enableRuning = true;
    }

    m_send_tick_flag = 0x01;           /* start to send HeartBeat */
    m_send_tick_adjacent_flag = 0x01;  /* start to send tick adjacent */
    logm_debug("RSU Init Completed, Start Heat Beat...!\n");

    *ack = 0xff;
    *ack_len = 0x01;

    return;
}


void Scheduler::rebootRsu(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    reboot_rsu_t *pcmd;
    reboot_rsu_ack_t *pack;

    pcmd = (reboot_rsu_t *)command;
    pack = (reboot_rsu_ack_t *)ack;
    pack->cmd_ack = REBOOT_RSU_ACK;

    system("reboot");

    *ack_len = sizeof(reboot_rsu_ack_t);
    return;
}


void Scheduler::setSendTickToPC(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    unsigned char cmd_type;

    cmd_type = command[1];
    if(cmd_type == 0x01)
    {
        //m_send_tick_flag = 0x01;
        //logm_debug("Network Connected, Start Heart Beat...!\n");
    }
    else
    {
        m_send_tick_flag = 0x00;
        logm_debug("Network Disonnected, Stop Heart Beat...!\n");
    }

    ack[0] = 0x21;
    ack[1] = 0x00;
    *ack_len = 0x02;
}

void Scheduler::initSafetyMedia(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    
    if(!m_IsAuth)
    {
        *ack = 0xff;
        *ack_len = 0x01;
        return ;
    }
        
    unsigned short pc_PSAMChannel = 0x00;
    init_auth_ack_head_t *pack;
    init_safety_psaminfor_ack *psam_infor;
    unsigned char psam_cmd_getRandom[7] = {0x00, 0x84, 0x00, 0x00, 0x08};
    unsigned char random_buffer[8] = {0x00};
    rtc_time_t rtc_time;	
	unsigned char opt;
    unsigned char currentTime[7] = {0};

    //get PSAMChannel from PC_CMD -> PSAMChannel to Init
    pc_PSAMChannel = command[1]; 
    logm_debug("pc_PSAMChannel = %02x\n", pc_PSAMChannel);

    pack = (init_auth_ack_head_t *)ack;

    // Get Current Date and Time
    bsp_rtc_read_time(&rtc_time, &opt);
    currentTime[0] = HEX2BCD(20);
    currentTime[1] = HEX2BCD((unsigned char)(rtc_time.tm_year - 2000));
    currentTime[2] = HEX2BCD(rtc_time.tm_mon);
    currentTime[3] = HEX2BCD(rtc_time.tm_mday);
    currentTime[4] = HEX2BCD(rtc_time.tm_hour);
    currentTime[5] = HEX2BCD(rtc_time.tm_min);
    currentTime[6] = HEX2BCD(rtc_time.tm_sec);

    pack->cmd_ack = INIT_SAFETY_ACK;
    pack->ErrorCode = 0x00; // error code: 0x00->sucess  0x01->init failed
    memcpy(pack->DateTime, currentTime, 7);
    pack->PSAMCount = 0x00; // number of psam

    //PSAM information
    std::vector<PsamPara *>::iterator iter = m_config->m_psamConfig.begin();
    if(pc_PSAMChannel == 0x00)
    {
        for(; iter != m_config->m_psamConfig.end(); ++iter)
        {      
            if(((*iter)->isEnable) && ((*iter)->status == 0)) // judge enable and status
            {
                psam_infor = (init_safety_psaminfor_ack *) (ack + 10 + sizeof(init_safety_psaminfor_ack) * pack->PSAMCount);
                psam_infor->channel_ID = (*iter)->psamid;
                memcpy(psam_infor->terminal_ID, (*iter)->terminal_id, 6); 
                memcpy(psam_infor->SerialNo, (*iter)->psam_serial, 10);
                psam_infor->psamVersion = (*iter)->version;
                psam_infor->psamType = (*iter)->psam_type;
                memcpy(psam_infor->useAreaID, (*iter)->useAreaID, 8);
                
                // get random
                if(m_psamproxy[(*iter)->psamid - 1]->get_MF_random(random_buffer) != 0)
                {
                    // if get psam_random, set error_code 0x01
                    pack->ErrorCode = 0x01; 
                    break;
                }
                
                memcpy(psam_infor->random, random_buffer, 8);
                memset(random_buffer, 0x00, 8); // clear buffer                
                pack->PSAMCount++;
            }
            else if(((*iter)->isEnable) && ((*iter)->status != 0)) // judge enable and status
            {
                pack->ErrorCode = 0x01; // power on, init failed
                break;
            }
        }
    }
    else if((pc_PSAMChannel >= 0x01) && (pc_PSAMChannel <= 0x08))
    {
        if((m_config->m_psamConfig[pc_PSAMChannel-1]->isEnable) 
            && (m_config->m_psamConfig[pc_PSAMChannel-1]->status == 0)) // judge enable and status
        {
            psam_infor = (init_safety_psaminfor_ack *) (ack + 10);
            psam_infor->channel_ID = m_config->m_psamConfig[pc_PSAMChannel-1]->psamid;
            memcpy(psam_infor->terminal_ID, m_config->m_psamConfig[pc_PSAMChannel-1]->terminal_id, 6); 
            memcpy(psam_infor->SerialNo, m_config->m_psamConfig[pc_PSAMChannel-1]->psam_serial, 10);
            psam_infor->psamVersion = m_config->m_psamConfig[pc_PSAMChannel-1]->version;
            psam_infor->psamType = m_config->m_psamConfig[pc_PSAMChannel-1]->psam_type;
            memcpy(psam_infor->useAreaID, m_config->m_psamConfig[pc_PSAMChannel-1]->useAreaID, 8);
            m_psamproxy[pc_PSAMChannel - 1]->get_MF_random(random_buffer); // get random
            memcpy(psam_infor->random, random_buffer, 8);
            memset(random_buffer, 0x00, 8); // clear buffer
            pack->PSAMCount++;
        }
        else
        {
            pack->ErrorCode = 0x01; // power on, init failed
        }
    }
    else
    {
        pack->ErrorCode = 0x01; // power on, init failed
    }   
    *ack_len = 10 + pack->PSAMCount * sizeof(init_safety_psaminfor_ack);
}

void Scheduler::ExecuteBstIntervalCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    int ret = 0;
    logm_debug("command %d <-- ", command_len);
    logm_debug_buffer(command, command_len);
    switch(command[0])
    {
        case 0xBF:
        {
            if(m_send_tick_adjacent_flag == 0x01)
            {
                set_bst_interval(command, command_len, ack, ack_len);
            }
            break;
        }
        case 0xBE:
        {          
            m_instep_fake_status = 1;
            m_instep_macid = (command[1] << 24)
                | (command[2] << 16)
                | (command[3] << 8)
                | (command[4]);
            m_instep_locationX = (command[5] << 24)
                | (command[6] << 16)
                | (command[7] << 8)
                | (command[8]);
            m_instep_locationY = (command[9] << 24)
                | (command[10] << 16)
                | (command[11] << 8)
                | (command[12]);
            logm_debug("recv instep fake locationX is %dcm  locationY is %dcm\n",m_instep_locationX, m_instep_locationY);


            ack[0] = 0xff;
            ack[1] = 0x00;
            *ack_len = 2;
            
            break;
        }
        case 0xBD:
        {
            m_instep_lettrade_status = command[1]; //1 is clear macid
            m_instep_lettrade_macid = (command[2] << 24)
                | (command[3] << 16)
                | (command[4] << 8)
                | (command[5]);
            logm_debug("recv instep lettrade status is %d\n", m_instep_lettrade_status);

            if(m_instep_lettrade_status == 1)
            {
                if(_macIdClear(m_instep_lettrade_macid))
                {
                    logm_debug("m_macId %08x is clear to 0\n", m_instep_lettrade_macid);
                }
                else
                {
                    logm_debug("m_macID different\n");
                }
                m_instep_lettrade_status = 0;
                m_instep_lettrade_macid = 0;
            }
            ack[0] = 0xff;
            ack[1] = 0x00;
            *ack_len = 2;
            break;
        }
        case 0xBC:
        {
            /* inform adjacent obu id location rssi num judge whether to transaction */
            m_instep_macid = (command[1] << 24)
                | (command[2] << 16)
                | (command[3] << 8)
                | (command[4]);
            m_instep_locationX = (command[5] << 24)
                | (command[6] << 16)
                | (command[7] << 8)
                | (command[8]);
            m_instep_locationY = (command[9] << 24)
                | (command[10] << 16)
                | (command[11] << 8)
                | (command[12]);
            m_instep_rssi = (command[13] << 24)
                | (command[14] << 16)
                | (command[15] << 8)
                | (command[16]);
            m_instep_num = (command[17] << 24)
                | (command[18] << 16)
                | (command[19] << 8)
                | (command[20]);
            ret = judgeWhetherTranscation(m_instep_macid, m_instep_locationX, m_instep_locationY, m_instep_rssi, m_instep_num);
            if(ret)
            {
                /* agree to transaction */
                ack[1] = 0x01;    
            }
            else
            {   
                /* disagree to transaction */
                ack[1] = 0x00;
            }
            memcpy(&ack[2], &command[1], 4);
            ack[0] = 0xBB;
            *ack_len = 6;
            break;
        }
        case 0xBB:
        {
            /* ack 0xBC */
            m_instep_lettrade_macid = (command[2] << 24)
                | (command[3] << 16)
                | (command[4] << 8)
                | (command[5]);
            if(command[1] == 0)
            {
                /* judge obuID is same to over this transation */
                if(_macIdClear(m_instep_lettrade_macid))
                {
                    logm_debug("m_macId %08x is not to transcation\n", m_instep_lettrade_macid);
                }
            }
            ack[0] = 0xff;
            ack[1] = 0x00;
            *ack_len = 2;
            break;
        }
        default:
        {
            ack[0] = 0xff;
            *ack_len = 1;
            break;
        }
    }

    logm_debug("ack %d --> ", *ack_len);
    logm_debug_buffer(ack, *ack_len);

    return;
}

void Scheduler::ExecuteRsuStatusCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    logm_debug("command %d <-- ", command_len);
    logm_debug_buffer(command, command_len);
    switch(command[0])
    {
        case 0xBB:
        {
            collect_rsu_status(command, command_len, ack, ack_len);
            break;
        }
        default:
        {
            ack[0] = 0xff;
            *ack_len = 1;
            break;
        }
    }

    logm_debug("ack %d --> ", *ack_len);
    logm_debug_buffer(ack, *ack_len);

    return;
}

void Scheduler::AuthSafetyMedia(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    auth_safety_ack_head_t *pack;
    unsigned char psam_auth_count = 0;    
    auth_infor_t *psam_exauth_infor;
    psam_auth_ack_t *auth_result;
    int ret = 0;
    int i;
    unsigned char auth_statword[2] = {0x00};

    // get number of external auth
    psam_auth_count = command[1];    
    
    // process ack information
    pack = (auth_safety_ack_head_t *)ack;
    pack->cmd_ack = AUTHORIZE_SAFETY_ACK;
    pack->ErrorCode = 0x00; // error code
    pack->AuthCount = 0x00; // PSAM auth count

    for(i = 0; i < psam_auth_count; i++, pack->AuthCount++)
    {
        psam_exauth_infor = (auth_infor_t *)(&command[2] + i * sizeof(auth_infor_t));
        if(psam_exauth_infor->psam_auth_status != 0)
        {
            auth_result = (psam_auth_ack_t *)(ack + 3 + pack->AuthCount * sizeof(psam_auth_ack_t));
            // CMD execute failed
            auth_result->status = 0x01;
            memset(auth_result->sw1sw2, 0x00, 2);
            // AuthStatus 0x01->not authorized
            m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->AuthStatus = PSAM_AUTH_NO;

            continue;
        }

        if( (m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->status != PSAM_STATUS_NOT_OK)
            && (m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->isEnable) )
        {
            auth_result = (psam_auth_ack_t *)(ack + 3 + pack->AuthCount * sizeof(psam_auth_ack_t));
            ret = m_psamproxy[psam_exauth_infor->psam_channel - 1]->execute_external_auth(psam_exauth_infor->exauth_apdu_mac, auth_statword);        
            if(ret != 0)
            {
                // CMD execute failed
                auth_result->status = 0x01;
                // AuthStatus 0x01->not authorized
                m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->AuthStatus = PSAM_AUTH_NO;
            }
            else
            {
                // CMD execute successfully
                auth_result->status = 0x00;
                if((auth_statword[0] == 0x90) && (auth_statword[1] == 0x00))
                {
                    // 0x00->authorize successfully
                    m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->AuthStatus = PSAM_AUTH_OK;
                }
                else
                {
                    // AuthStatus 0x01->not authorized
                    m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->AuthStatus = PSAM_AUTH_NO; 
                    
                    if((auth_statword[0] == 0x69) && (auth_statword[1] == 0x83))
                    {
                        // 0x6983 PSAM_key_locked, PSAM Status 0x01-> abnormal
                        m_config->m_psamConfig[psam_exauth_infor->psam_channel - 1]->status = PSAM_STATUS_NOT_OK;
                    }
                }
            }
            auth_result->psam_channel_id = psam_exauth_infor->psam_channel;
            memcpy(auth_result->sw1sw2, auth_statword, 2);
            memset(auth_statword, 0x00, 2); // clear buffer
        }        
    }

    *ack_len = 3 + pack->AuthCount * sizeof(psam_auth_ack_t);
    PsamAutState = 0x01;//标记为已授权
}
void Scheduler::forbidRfSendBst(int rfsn, bool flag)
{
    RfProxy *rfProxy = NULL;
    if (flag)
    {
        logm_debug("rfsn %d--> forbidbst\n", rfsn);
    }
    else
    {
        logm_debug("rfsn %d--> unforbidbst\n", rfsn);
    }
    rfProxy = m_rfsMap[rfsn];
    rfProxy->m_rfForbidBst = flag;
}

void Scheduler::executeManageCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len)
{
    logm_debug("cmd %d <-- ", command_len);
    logm_debug_buffer(command, command_len);

    switch(command[0]) 
    {
        case INIT_RSU: 
        {
            initRsu(command, command_len,  ack, ack_len);
            break;
        }
        case AFTER_ACK_INIT_OPEN_ANT:
        {
            AfterInit_OpenAnt(command, command_len,  ack, ack_len);
            break;
        }        
        case PC_CTRL_RSU_PORT: // open-close antan
        case PC_OPEN_CLOSE_ANT:
        {
            openAnt(command, command_len, ack, ack_len);
            break;
        }
        case COIL_TRIGGER:
        {
            coilTrigger(command, command_len, ack, ack_len);
            break;
        }

        case PC_CTRL_RFID://新增lzw
        {
            pcctrlrfid(command, command_len, ack, ack_len);
            break;
        }
        case set_send_tick:
        {
            setSendTickToPC(command, command_len,  ack, ack_len);
            break;
        }
        case INIT_SAFETY_MEDIA:
        {
            initSafetyMedia(command, command_len,  ack, ack_len);
            break;
        }
        case AUTHORIZE_SAFETY_MEDIA:
        {
            AuthSafetyMedia(command, command_len,  ack, ack_len);
            break;
        }
        case set_coordinate_limit: 
        {
            setCoordinateLimit(command,command_len,ack, ack_len);
            break;
        }
        case set_coil_trigger:
        {
            setCoilTrigger(command,command_len,ack, ack_len);
            break;
        }
        case query_ant:
        {
            QueryAntStatus(command, command_len,  ack, ack_len);
            break;
        }
        case set_beaconid: 
        {
            setBeaconId(command, command_len, ack, ack_len);
            break;
        }
        case set_ant_config: 
        {
            setAntConfig(command,command_len,ack, ack_len);
            break;
        }
        case set_psam_config: 
        {
            setPsamConfig(command,command_len,ack, ack_len);
            break;
        }
        case set_congtrol_master_ip:
        {
            setControlMasterIp(command,command_len,ack,ack_len);
            break;
        }
        case set_control_id: 
        {
            setControlId(command,command_len,ack, ack_len);
            break;
        }
        case set_lane_mode:
        {
            setLaneMode(command, command_len, ack, ack_len);
            break;
        }
        case set_default_config:
        {
            setDefaultConfig(command, command_len, ack, ack_len);
            break;
        }
        case set_time_para: 
        {
            setTradeTimePara(command,command_len,ack, ack_len);
            break;
        }        
        case set_workmode: 
        {
            setWorkMode(command,command_len,ack, ack_len);
            break;
        }
         case set_rfsmode:
        {
            setRfsMode(command,command_len,ack, ack_len);
            break;
        }
        case set_vst_len:
        {
            setVstLen(command,command_len,ack, ack_len);
            break;
        }
        case set_antmode_switch:
        {
            setAntModeSwitch(command,command_len,ack, ack_len);
            break;
        }

        case set_beaconid_test: 
        {
            setBeaconIdTest(command, command_len,  ack, ack_len);
            break;
        }        
        case RF_TEST_INIT:
        case RF_TEST_SEND:
        case RF_TEST_RECV: 
        {
            rfTestCommand(command, command_len,  ack, ack_len);
            break;
        }
        case REBOOT_RSU: 
        {
            rebootRsu(command, command_len,  ack, ack_len);
            break;
        }
        default: 
        {
            ack[0] = 0xff;
            *ack_len = 1;
            break;
        }
    }

    logm_debug("ack %d --> ", *ack_len);
    logm_debug_buffer(ack, *ack_len);

    return;
}


TagCache::TagCache()
{
    m_cacheTime = 0;
}

void TagCache::setCacheTime(unsigned int time)
{
    m_cacheTime = time;    
}


void TagCache::cacheTag(unsigned int macid)
{
    unsigned long current;
    tag_jiffies_t *newtag = NULL;
    tag_jiffies_t *oldtag = NULL;

    current = get_jiffies();
    if(m_taglist.empty()) 
    {
        m_first = current;
        m_last = current;
    }

    newtag = new tag_jiffies_t();
    newtag->jffies = current;
    newtag->macid = macid;
    m_taglist.push_back(newtag);
    m_last = current;

    while(timeOk(m_first, m_cacheTime)) 
    {
        oldtag = m_taglist.front();
        m_taglist.pop_front();
        delete oldtag;
        if(m_taglist.empty())
        {
            break;
        }
        m_first = m_taglist.front()->jffies;
    }

    return;
}

bool TagCache::findTag(unsigned int macid)
{
    for(std::list<tag_jiffies_t *>::iterator iter=m_taglist.begin();
        iter != m_taglist.end(); ++iter) 
    {
        if((*iter)->macid == macid) 
        {
            if(timeOk((*iter)->jffies, m_cacheTime)) 
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}


int TagCache::findTagCount(unsigned int macid)
{
    int count = 0;

    for(std::list<tag_jiffies_t *>::iterator iter=m_taglist.begin();
        iter != m_taglist.end(); ++iter)
    {
        if((*iter)->macid == macid)
        {
            if(timeOk((*iter)->jffies, m_cacheTime))
            {
                continue;
            }
            else
            {
                count += 1;
            }
        }
    }
    return count;
}


int main(int argc, char *argv[])
{
    init_jiffs();
    bsp_rtc_init();
    init_logm("scheduler");
    set_timeflag();

    Scheduler scheduler;
    scheduler.init();
    scheduler.run();

    return 0;
}

