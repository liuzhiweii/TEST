#include <zmq.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "bsp.h"
#include "device_proxy.h"

#define logm_debug printf


void *rep_socket = NULL;

struct msg_proc_t msg_procs[] =
{
    {DEVICE_FPGA, fpga_ctrl},
    {DEVICE_EEPROM, eeprom_ctrl},
    {DEVICE_PLL, pll_ctrl},
    {DEVICE_EPLD, epld_ctrl},
    {DEVICE_RTC, rtc_ctrl},
    {DEVICE_SENSOR, sensor_ctrl},
    {DEVICE_PSAM, psam_ctrl}
    
};

struct fpga_action_t fpga_actions[] = 
{
    {_fpga_init, fpga_init},
    {_fpga_read_reg, fpga_read_reg},
    {_fpga_write_reg, fpga_write_reg}
};

struct device_action_t pll_actions[] = 
{
    {_pll_init, pll_init},
    {_pll_read, pll_read},
    {_pll_write, pll_write}
};

struct device_action_t epld_actions[] = 
{
    {_epld_init, epld_init},
    {_epld_read, epld_read},
    {_epld_write, epld_write},
    {_epld_write_fifo, epld_write_fifo},
    
};

struct device_action_t eeprom_actions[] = 
{
    {_pll_init, eeprom_init},
    {_pll_read, eeprom_read},
    {_pll_write, eeprom_write}
};

struct device_action_t rtc_actions[] = 
{
    {_rtc_init, rtc_init},
    {_rtc_set, rtc_set},
    {_rtc_read, rtc_read},    
};

struct device_action_t sensor_actions[] = 
{
    {_sensor_init, sensor_init},
    {_set_local_limit, set_local_limit},
    {_set_remote_limit, set_remote_limit},       
    {_read_local_limit, read_local_limit},   
    {_read_remote_limit, read_remote_limit},  
    {_read_local_temp, read_local_temp},   
    {_read_remote_temp, read_remote_temp}, 
    {_read_sensor_status, read_sensor_status},       
};


struct device_action_t psam_actions[] = 
{
    {_psam_init, psam_init},
    {_psam_active, psam_active},
    {_psam_setclk, psam_setclk},       
    {_psam_exchange_apdu, psam_exchange_apdu},   
    {_psam_deactive, psam_deactive},      
};

void fpga_init(unsigned char *args)
{
    unsigned int ret;
    ret = htonl(bsp_fpga_init());

    printf("fpga init ret is %d \n", ret);
    
    zmq_send(rep_socket, &ret, sizeof(unsigned int), 0);
    return;
}

void fpga_read_reg(unsigned char *args)
{
    unsigned int ret;
    unsigned int reg_offset;
    unsigned short reg_value;
    unsigned char send_buf[16];

    reg_offset = *((unsigned int *)(args));

    printf("read fpga offset is %08X \n", reg_offset);

    ret = bsp_fpga_read_reg(reg_offset, &reg_value);

    printf("fpga read ret is %d value is %04X \n", ret, reg_value);

    ret = htonl(ret);
    reg_value = htons(reg_value);

    memcpy(send_buf, &ret, sizeof(unsigned int));
    memcpy(&send_buf[4], &reg_value, sizeof(unsigned short));

    zmq_send(rep_socket, send_buf, 6, 0);

    return;
}

void fpga_write_reg(unsigned char *args)
{
    unsigned int ret;
    unsigned int reg_offset;
    unsigned short reg_value;

    reg_offset = htonl(*((unsigned int *)args));
    reg_value = htons(*((unsigned short *)(args + 4)));

    printf("fpga write reg offset is %08X value is %04X \n", reg_offset, reg_value);

    ret = htonl(bsp_fpga_write_reg(reg_offset, reg_value));

    printf("write fpga ret is %d \n", ret);
    
    ret = htonl(ret);

    zmq_send(rep_socket, &ret, 4, 0);

    return;
}

void reply_default_msg(void)
{
     int status = htonl(-1000);

     printf("reply default msg \n");
     zmq_send(rep_socket, &status, 4, 0);

     return;
}

void fpga_ctrl(unsigned char *args)
{
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    for(i=0; i<(sizeof(fpga_actions)/sizeof(fpga_action_t)); ++i)
    {
        if(action_type == fpga_actions[i].action_type)
        {
            fpga_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }

    
}

void eeprom_ctrl(unsigned char *args)
{    
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    printf("enter eeprom_ctrl\n");
    printf("action type is %d\n", action_type);

    for(i=0; i<(sizeof(eeprom_actions)/sizeof(device_action_t)); ++i)
    {
        if(action_type == eeprom_actions[i].action_type)
        {
            eeprom_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }
    
}


void pll_ctrl(unsigned char *args)
{
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    logm_debug("enter pll_ctrl\n");
    logm_debug("action type is %d\n", action_type);

    for(i=0; i<(sizeof(pll_actions)/sizeof(device_action_t)); ++i)
    {
        if(action_type == pll_actions[i].action_type)
        {
            pll_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }
}

void epld_ctrl(unsigned char *args)
{
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    printf("enter epld_ctrl \n");

    for(i=0; i<(sizeof(epld_actions)/sizeof(fpga_action_t)); ++i)
    {
        if(action_type == epld_actions[i].action_type)
        {
            epld_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }
}

void rtc_ctrl(unsigned char *args)
{
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    printf("enter rtc_ctrl, action type is %d \n", action_type);

    for(i=0; i<(sizeof(rtc_actions)/sizeof(device_action_t)); ++i)
    {
        if(action_type == rtc_actions[i].action_type)
        {
            rtc_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }
}



void sensor_ctrl(unsigned char *args)
{
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    printf("enter sensor_ctrl, action type is %d \n", action_type);

    for(i=0; i<(sizeof(sensor_actions)/sizeof(device_action_t)); ++i)
    {
        if(action_type == sensor_actions[i].action_type)
        {
            sensor_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }
}


void psam_ctrl(unsigned char *args)
{
    int i;
    int status = 1;
    int action_type = htonl(*((unsigned int *)args));
    int processed = 0;

    printf("enter psam_ctrl, action type is %d \n", action_type);

    for(i=0; i<(sizeof(psam_actions)/sizeof(device_action_t)); ++i)
    {
        if(action_type == psam_actions[i].action_type)
        {
            psam_actions[i].action(args+4);
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
        reply_default_msg();
    }
}


void pll_init(unsigned char *args)
{
    unsigned int ret;


    printf("enter pll_init 111\n");
    
    ret = htonl(bsp_init_pll());
    
    zmq_send(rep_socket, &ret, sizeof(unsigned int), 0);

    printf("pll init return\n");
    return;
}

void pll_read(unsigned char *args)
{
    unsigned int ret;
    unsigned int dwOffset = *((unsigned int *)(args));
    unsigned int dwLen = *((unsigned int *)(args+4));
    unsigned int recv_len = 0;
    unsigned char send_buf[128];

    printf("enter pll_read \n");

    if(dwLen > 64)
    {
        ret = 1;
    }
    else
    {   
        printf("offset is %d, length is %d \n", dwOffset, dwLen);
        ret = bsp_read_pll(dwOffset, dwLen, &send_buf[8], &recv_len);
    }

    
    printf("read ret is %d, read length is %d \n", ret, recv_len);
    printf("read byte is %02X \n", send_buf[8]);

    ret = htonl(ret);
    recv_len = htonl(recv_len);

    
    memcpy(send_buf, &ret, 4);
    memcpy(&send_buf[4], &recv_len, 4);    

    zmq_send(rep_socket, send_buf, (recv_len + 8), 0);
    return;
    
}


void pll_write(unsigned char * args)
{
    unsigned int ret;
    unsigned int dwOffset = *((unsigned int *)(args));
    unsigned int dwLen = *((unsigned int *)(args+4));
    unsigned int send_len = 0;
    unsigned char send_buf[8];

    printf("write offset is %d, len is %d, value is %02X \n", dwOffset, dwLen, args[8]);

    ret = bsp_write_pll(dwOffset, dwLen, (args + 8), &send_len);

    printf("write ret is %d len is %d \n", ret, send_len);

    ret = htonl(ret);
    send_len = htonl(send_len);

    memcpy(send_buf, &ret, 4);
    memcpy(&send_buf[4], &send_len, 4);

    zmq_send(rep_socket, send_buf, 8, 0);

    return;
}

void epld_init(unsigned char *args)
{
    unsigned int ret;
    ret = htonl(bsp_epld_init());

    printf("epld init ret is %d \n", ret);
    
    zmq_send(rep_socket, &ret, sizeof(unsigned int), 0);
    return;
}

void epld_read(unsigned char *args)
{
    unsigned int ret;
    unsigned int reg_offset;
    unsigned short reg_value;
    unsigned char send_buf[16];

    reg_offset = *((unsigned int *)(args));
    reg_offset = reg_offset>>1;

    printf("read epld offset is %d \n", reg_offset);

    ret = bsp_epld_read(reg_offset, &reg_value);

    printf("epld read ret is %d value is %04X \n", ret, reg_value);

    ret = htonl(ret);
    reg_value = htons(reg_value);

    memcpy(send_buf, &ret, sizeof(unsigned int));
    memcpy(&send_buf[4], &reg_value, sizeof(unsigned short));

    zmq_send(rep_socket, send_buf, 6, 0);

    return;
}


void epld_write(unsigned char *args)
{
    unsigned int ret;
    unsigned int reg_offset;
    unsigned short reg_value;

    reg_offset = htonl(*((unsigned int *)args));
    reg_value = htons(*((unsigned short *)(args + 4)));

    reg_offset = reg_offset>>1;

    printf("epld write reg offset is %d value is %04X \n", reg_offset, reg_value);

    ret = htonl(bsp_epld_write(reg_offset, reg_value));

    printf("write epld ret is %d \n", ret);
    
    ret = htonl(ret);

    zmq_send(rep_socket, &ret, 4, 0);

    return;
}

static void delay_us(unsigned int us)
{
    volatile unsigned int i = 0;
    for (i = 0;i < (16 * us); i++);
    return;
}


void epld_write_fifo(unsigned char *args)
{
    unsigned int ret;
    unsigned int reg_offset;
    unsigned int write_num;
    unsigned char *p_reg_value;
    int i;

    reg_offset = htonl(*((unsigned int *)args));
    write_num = htonl(*((unsigned int *)(args+4)));
    
    p_reg_value = (unsigned char *)(args+8);

    reg_offset = reg_offset>>1;

    printf("epld write fifo reg offset is %04X \n", reg_offset);
    printf("epld write fifo len is %d \n", write_num);
    
    for(i=0; i<write_num; ++i)
    {
        ret = htonl(bsp_epld_write(reg_offset, p_reg_value[i]));
        delay_us(5);
        if(ret != 0)
        {
        	break;
        }        
    }

    printf("write epld fifo ret is %d \n", ret);
    
    ret = htonl(ret);

    zmq_send(rep_socket, &ret, 4, 0);

    return;
}



void eeprom_write(unsigned char *args)
{
    unsigned int ret;
    unsigned int offset;
    unsigned int write_num;
    unsigned char *p_data;
	unsigned int written_len;
	
    offset = htonl(*((unsigned int *)args));
    write_num = htonl(*((unsigned int *)(args+4)));
    p_data = (unsigned char *)(args+8);


    printf("eeprom_write offset is %d \n", offset);
    printf("eeprom_write len is %d \n", write_num);
    
    ret = bsp_eeprom_snd(offset, write_num, p_data, &written_len);

    printf("eeprom_write ret is %d \n", ret);
    
    zmq_send(rep_socket, &ret, 4, 0);

    return;
}

void eeprom_init(unsigned char *args)
{
	int ret = 0;

	zmq_send(rep_socket, &ret, 4, 0);
	return ;
}


void eeprom_read(unsigned char *args)
{
    unsigned int ret;
    unsigned int offset;
    unsigned int read_len;
    unsigned char read_buf[1024];
    unsigned int rcv_len = 0;
    unsigned char reply_buf[1024*2];
	
    offset = htonl(*((unsigned int *)args));
    read_len = htonl(*((unsigned int *)(args+4)));


    printf("eeprom_read offset is %d \n", offset);
    printf("eeprom_read len is %d \n", read_len);
    
    ret = bsp_eeprom_rcv(offset, read_len, read_buf, &rcv_len);

    printf("eeprom_read ret is %d \n", ret);    
    printf("eeprom_read rcv_len is %d \n", rcv_len);

    if(ret != 0)
    {
        memcpy(reply_buf, &ret, 4);        
        memcpy(&reply_buf[4], &rcv_len, 4);       
		zmq_send(rep_socket, &reply_buf, 8, 0);
    }
    else
    {
        memcpy(reply_buf, &ret, 4);        
        memcpy(&reply_buf[4], &rcv_len, 4);
        memcpy(&reply_buf[8], read_buf, rcv_len);
        zmq_send(rep_socket, reply_buf, (rcv_len+8), 0);
    }
    
    return;
}


void rtc_init(unsigned char *args)
{
	int ret = 0;

	zmq_send(rep_socket, &ret, 4, 0);
	return ;
}




void rtc_set(unsigned char *args)
{
    unsigned int ret;

	rtc_time_t *ptTime = (rtc_time_t *)args;

	ret = bsp_rtc_write_time(ptTime, 0);

    printf("rtc_set ret is %d \n", ret);
    
    zmq_send(rep_socket, &ret, 4, 0);

    return;
}

void rtc_read(unsigned char *args)
{
    unsigned int ret;
	rtc_time_t time;
	unsigned char reply_buf[256];

	ret = bsp_rtc_read_time(&time, 0);
	
    printf("rtc_read ret is %d \n", ret);
    memcpy(reply_buf, &ret, 4);
    memcpy(&reply_buf[4], &time, sizeof(rtc_time_t));
    
    zmq_send(rep_socket, reply_buf, (sizeof(rtc_time_t)+4), 0);

    return;
}

void sensor_init(unsigned char *args)
{
	unsigned int ret = 0;

	bsp_epld_init();

    ret = bsp_i2c_init();
    if (0 != ret)
    {
        printf("tsensor i2c init fail!errcode = %x\r\n", ret);
    }
    else
    {
        ret = bsp_tsensor_init();
		if(ret != 0)
		{
		    printf("tsensor init failed!errcode = %x\r\n", ret);
	    }
    }

    printf("tsensor init success\n");

	zmq_send(rep_socket, &ret, 4, 0);
	return ;
}

void set_local_limit(unsigned char *args)
{
	unsigned int ret;
    int limit_low = *((int *)args);
    int limit_high = *((int *)(args + 4));

    printf("set local limit low:%d high:%d \n", limit_low, limit_high);

    ret = bsp_tsensor_set_temp_low(limit_low);
    if(ret != 0)
    {        
        printf("bsp_tsensor_set_temp_low fail ! errcode = %x\r\n", ret);
    }
    else
    {
        ret = bsp_tsensor_set_temp_high(limit_high);
        if(ret != 0)
	    {        
	        printf("bsp_tsensor_set_temp_high fail ! errcode = %x\r\n", ret);
	    }
    }
    
	zmq_send(rep_socket, &ret, 4, 0);
	return;
}
void set_remote_limit(unsigned char *args)
{
	unsigned int ret;
    int limit_low = *((int *)args);
    int limit_high = *((int *)(args + 4));

    printf("set_remote_limit low:%d high:%d \n", limit_low, limit_high);

    ret = bsp_tsensor_set_remote_temp_low(limit_low);
    if(ret != 0)
    {        
        printf("bsp_tsensor_set_remote_temp_low fail ! errcode = %x\r\n", ret);
    }
    else
    {
        ret = bsp_tsensor_set_remote_temp_high(limit_high);
        if(ret != 0)
	    {        
	        printf("bsp_tsensor_set_remote_temp_high fail ! errcode = %x\r\n", ret);
	    }
    }

    printf("set_remote_limit success \n");
    
	zmq_send(rep_socket, &ret, 4, 0);
	return;
}

void read_local_limit(unsigned char *args)
{
	unsigned int ret;
	signed char value;
	int limit_low = 0;
	int limit_high = 0;
	unsigned char reply_buf[12];

	ret = bsp_tsensor_get_temp_low((unsigned char *)&value);
	if(ret != 0)
	{
	    printf("bsp_tsensor_get_temp_low fail: %d\n", ret);
	    goto fail_reply;
	}

    limit_low = value;
    printf("limit low is %d \n", limit_low);

	ret = bsp_tsensor_get_temp_high((unsigned char *)&value);
	if(ret != 0)
	{
	    printf("bsp_tsensor_get_temp_high fail: %d\n", ret);
	    goto fail_reply;
	}

    limit_high = value;
    printf("limit high is %d \n", limit_high);

    memcpy(reply_buf, &ret, 4);
    memcpy(&reply_buf[4], &limit_low, 4);    
    memcpy(&reply_buf[8], &limit_high, 4);    
	zmq_send(rep_socket, reply_buf, 12, 0);
	return;
	
fail_reply:
	
	zmq_send(rep_socket, &ret, 4, 0);
	return;
}

void read_remote_limit(unsigned char *args)
{
	unsigned int ret;
	signed char value;
	int limit_low = 0;
	int limit_high = 0;
	unsigned char reply_buf[12];

	ret = bsp_tsensor_get_remote_temp_low((unsigned char *)&value);
	if(ret != 0)
	{
		printf("bsp_tsensor_get_remote_temp_low fail: %d\n", ret);
		goto fail_reply;
	}

	limit_low = value;
	printf("limit low is %d \n", limit_low);

	ret = bsp_tsensor_get_remote_temp_high((unsigned char *)&value);
	if(ret != 0)
	{
		printf("bsp_tsensor_get_remote_temp_high fail: %d\n", ret);
		goto fail_reply;
	}

	limit_high = value;
	printf("limit high is %d \n", limit_high);

	memcpy(reply_buf, &ret, 4);
	memcpy(&reply_buf[4], &limit_low, 4);	 
	memcpy(&reply_buf[8], &limit_high, 4);	  
	zmq_send(rep_socket, reply_buf, 12, 0);
	return;
	
fail_reply:
	
	zmq_send(rep_socket, &ret, 4, 0);

}
void read_local_temp(unsigned char *args)
{
    unsigned int ret;
    int temperature;
    signed char value;
    unsigned char reply_buf[8];

    ret = bsp_tsensor_read_local_temp((unsigned char *)&value);
    if(0 != ret)
    {
        printf("bsp_tsensor_read_local_temp fail! ret is %08x \n", ret);
        zmq_send(rep_socket, &ret, 4, 0);
    }
    else
    {
        temperature = value;        
        printf("read local temp success %d \n", temperature);
        memcpy(reply_buf, &ret, 4);
        memcpy(&reply_buf[4], &temperature, 4);        
		zmq_send(rep_socket, reply_buf, 8, 0);
    }

    return;
}
void read_remote_temp(unsigned char *args)
{
    unsigned int ret;
    int temperature;
    signed char value;
    unsigned char reply_buf[8];

    ret = bsp_tsensor_read_remote_temp((unsigned char *)&value);
    if(0 != ret)
    {
        printf("bsp_tsensor_read_remote_temp fail! ret is %08x \n", ret);
        zmq_send(rep_socket, &ret, 4, 0);
    }
    else
    {
        temperature = value;
        printf("read remote temp success %d \n", temperature);
        memcpy(reply_buf, &ret, 4);
        memcpy(&reply_buf[4], &temperature, 4);        
		zmq_send(rep_socket, reply_buf, 8, 0);
    }

    return;
}

void read_sensor_status(unsigned char *args)
{
	unsigned int ret;
    unsigned int status;
    unsigned char value;
    unsigned char reply_buf[8];

    ret = bsp_tsensor_get_alarm_status(&value);
    if(0 != ret)
    {
        printf("read_sensor_status fail! ret is %08x \n", ret);
        zmq_send(rep_socket, &ret, 4, 0);
    }
    else
    {
        status = value;
        printf("status is %d \n", status);
        memcpy(reply_buf, &ret, 4);
        memcpy(&reply_buf[4], &status, 4);        
		zmq_send(rep_socket, reply_buf, 8, 0);
    }

    return;
}

void psam_init(unsigned char *args)
{
    unsigned int ret;

	ret = bsp_psam_init();
	
	printf("psam init ret %d \n", ret);
	
	zmq_send(rep_socket, &ret, 4, 0);
	return;
}

void psam_active(unsigned char *args)
{
    unsigned int ret;
    int sock_id;
    T_CardPara card_para;
    unsigned int err_code;
    unsigned char reply_buf[8+sizeof(T_CardPara)];

    sock_id = *((int *)args);

    ret = bsp_psam_active(sock_id, &card_para, &err_code);

    printf("active psam slot:%d ret :%d err_code %08x \n", sock_id, ret, err_code);

    memcpy(reply_buf, &ret, 4);
    memcpy(&reply_buf[4], &err_code, 4);
	memcpy(&reply_buf[8], &card_para, sizeof(T_CardPara));
	
	zmq_send(rep_socket, reply_buf, (8+sizeof(T_CardPara)), 0);

	return;
}

void psam_setclk(unsigned char *args)
{
	unsigned int ret;
	unsigned int clk_div;

	clk_div = *((unsigned int *)args);

	ret = bsp_psam_clkfreq_set(clk_div);

	printf("set psam clk div %d ret %d \n", clk_div, ret);

	zmq_send(rep_socket, &ret, 4, 0);

	return;
}
void psam_exchange_apdu(unsigned char *args)
{
	unsigned int ret;
	unsigned int sock_id = *((unsigned int *)args);
	unsigned int cmd_len = *((unsigned int *)(args + 4));
	unsigned char res_len = 0;
	unsigned char res_buf[256];
	unsigned int err_code;
	unsigned char reply_buf[512];

	printf("psam_exchange_apdu slot:%d cmd len:%d \n");
	int i;
	for(i=0; i<cmd_len; ++i)
	{
	    printf("%02X", args[8+i]);
	}

	printf("\n");

	ret = bsp_psam_cmd(sock_id, cmd_len, (args+8), &res_len, res_buf, &err_code);

	printf("response len is %d \n", res_len);

	for(i=0; i<res_len; ++i)
	{
		printf("%x", res_buf[i]);
	}
	printf("\n");

	memcpy(reply_buf, &ret , 4);	
	memcpy(&reply_buf[4], &err_code , 4);	
	memcpy(&reply_buf[8], &res_len , 4);
	memcpy(&reply_buf[12], res_buf, res_len);
	
	printf("psam exchange apdu ret %d errcode %d \n", ret, err_code);
	zmq_send(rep_socket, reply_buf, (12 + res_len), 0);

	return;
}

void psam_deactive(unsigned char *args)
{
	unsigned int ret;
	unsigned int sock_id = *((unsigned int *)args);
	unsigned int err_code;

	ret = bsp_psam_deactive(sock_id, &err_code);

	zmq_send(rep_socket, &ret, 4, 0);
	return;
}




void deal_msg(int msg_len, unsigned char *buf)
{
    int i;
    int processed = 0;
    unsigned int status = 1;
    
    int device_type = htonl(*((unsigned int *)buf));

    printf("recv msg from client, device_type is %d\n", device_type);

    for(i=0; i<(sizeof(msg_procs)/sizeof(struct msg_proc_t)); ++i)
    {
        if(device_type == msg_procs[i].device_type)
        {
            msg_procs[i].action(buf+sizeof(unsigned int));
            processed = 1;
            break;
        }
    }

    if(processed == 0)
    {
       reply_default_msg();
    }

    return;
}


int main(int argc , char *argv[])
{
    void *ctx;
	int recv_len;
	unsigned char recv_buf[1024*10];
	int ret;
	
    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
        exit(-1);
    }

    rep_socket = zmq_socket(ctx, ZMQ_REP);
    if(NULL == rep_socket)
    {
        printf("create rep_socket fail!\n");
        exit(-1);
    }
    ret = zmq_bind(rep_socket, "tcp://*:5100");
    if(ret < 0)
    {
        printf("bind rep_socket  fail\n");
        exit(-1);
    }

	while(1)
	{
		recv_len = zmq_recv(rep_socket, recv_buf, sizeof(recv_buf), 0);
		if(recv_len > 0)
		{
		    deal_msg(recv_len, recv_buf);
		}
	}
	
}



