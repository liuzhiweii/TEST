
#include <zmq.h> 
#include <sys/time.h> 

#include "logm.h"
#include "rfs.h"
#include "bsp/bsp_fpga.h"
#include "parson.h"
#include <math.h>




void *push_socket_dispatch = NULL;
void *pull_socket_dispatch = NULL;
void *req_socket_cfg=NULL;
void *sub_socket_cfg=NULL;

rfs_ctl_t rfs_ctl;

unsigned char pll_reg_map[] = {0x01, 0x00, 0xb4, 0x04, 0x02, 0x50, 0x0e,
               0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00};
unsigned char pll_reg_map1[] = {0x00, 0x00, 0x00, 0x00, 0x4d, 0x02, 0x05,
                0x00, 0x80, 0x02, 0x1b, 0x2a, 0x00, 0x40, 0x02};
unsigned char pll_reg_map2[] = {0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x05,
                0x05, 0xf3, 0xcc, 0x33, 0xcb, 0x00, 0x40, 0x02};



#define CRC_INIT 0xffff   //CCITT初始CRC为全1
#define GOOD_CRC 0xf0b8   //校验时计算出的固定结果值
/****下表是常用ccitt 16,生成式1021反转成8408后的查询表格****/
unsigned short crc16_ccitt_table[256] =
{
0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};
/*****CRC计算函数,可将第一个参数reg_init简化掉********/
unsigned short do_crc(unsigned short reg_init, unsigned char *message, unsigned int len)
{
    unsigned short crc_reg = reg_init;
         
    while (len--)
        crc_reg = (crc_reg >> 8) ^ crc16_ccitt_table[(crc_reg ^ *message++) & 0xff];
       
    return ~crc_reg;
} 

#if 0
unsigned short cal_dsrc_crc(unsigned char *data, unsigned short length)
{
    unsigned char temp;
    unsigned short crc_value;
	unsigned short int loop;
	unsigned char tmp_data[256];

    crc_value = 0xffff;

	if((NULL==data)||(length>256))
	{
	   logm_debug("NULL pointer error,or length is more than 256,length=%d\r\n",length);
	   return -1;
	}

    logm_debug("cal dsrc crc length is %d, data is:\r\n",length);
	for(loop=0;loop<length;loop++)
	{
		printf("0x%x ",data[loop]);
	}
    logm_debug("\r\n");
    
	memcpy(tmp_data,data,length);
	for (loop =0; loop < length; loop++)
    {
        tmp_data[loop] = (tmp_data[loop] >> 7) | ((tmp_data[loop] >> 5) & 0x02) | ((tmp_data[loop] >> 3) & 0x04) | ((tmp_data[loop] >> 1) & 0x08) |
                        ((tmp_data[loop] << 1) & 0x10) | ((tmp_data[loop] << 3) & 0x20) | ((tmp_data[loop] << 5) & 0x40) | ((tmp_data[loop]<<7) & 0x80);
		printf("tmp_data[%d]=0x%x\r\n",loop,tmp_data[loop]);
    }
	crc_value = crc_ccitt(tmp_data,length);
    #if 0
	loop=0;
    while(length-- != 0)
    {
        temp = (unsigned char)(crc_value >> 8) ;
        crc_value <<= 8 ;
        crc_value ^= crc_table[temp ^ tmp_data[loop]] ;
		printf("tmp_data[%d]=0x%x crc=0x%x\r\n",loop,tmp_data[loop],crc_value);
        loop++ ;
    }
	#endif
	printf("crc is:0x%x\r\n", crc_value);
    return ~crc_value;
	
}
#endif
void clear_fpga_fifo()
{
	bsp_fpga_write_reg(0x8008a, 1);
	usleep(50);
	bsp_fpga_write_reg(0x8008a, 0);
}
unsigned int config_fpga_pll(void)
{
	unsigned int ret;
    unsigned int write_len = 0;
    
    ret = bsp_write_pll(0, sizeof(pll_reg_map), pll_reg_map, &write_len);
    if(ret != 0)
    {
         logm_debug("write pll_reg_map fail ret is %d \n", ret);
         return ret;
    }

    ret = bsp_write_pll(16, sizeof(pll_reg_map1), pll_reg_map1, &write_len);
    if(ret != 0)
    {
         logm_debug("write pll_reg_map1 fail ret is %d \n", ret);
         return ret;
    }
    ret = bsp_write_pll(32, sizeof(pll_reg_map2), pll_reg_map2, &write_len);
    if(ret != 0)
    {
         logm_debug("write pll_reg_map2 fail ret is %d \n", ret);
         return ret;
    }
    logm_debug("config_fpga_pll success\n");
    return 0;
}



void select_adc_channel(unsigned short channal)
{
    bsp_fpga_write_reg(0x800a1, channal);
    return;
}

void trig_training(void)
{
    bsp_fpga_write_reg(0x800a0, 0x0000); 
	usleep(100);
    bsp_fpga_write_reg(0x800a0, 0x0001);
	bsp_fpga_write_reg(0x800a0, 0x0000);
}

void write_adc_reg(unsigned short data)
{
    bsp_fpga_write_reg(0x800a3, data);
    bsp_fpga_write_reg(0x800a2, 0);
	usleep(100);
    bsp_fpga_write_reg(0x800a2, 1);
    bsp_fpga_write_reg(0x800a2, 0);

    return;   
}

int traing_adc(void)
{
    unsigned short reg_value = 0;
    unsigned ret;
	int count=0;
    
    select_adc_channel(0);//(rfs_ctl.pll_channelID);
    
    write_adc_reg(0x0080);
	write_adc_reg(0x0000);
	usleep(50000);
    write_adc_reg(0x0120);
    write_adc_reg(0x0200);
    write_adc_reg(0x0300);
    write_adc_reg(0x0400);
    
    trig_training();
    ret = bsp_fpga_read_reg(0x8009c, &reg_value);
	logm_debug("reg_value=0x%x\r\n",reg_value);
	while(((ret != 0) || (reg_value != 0xf0f0))&&(count<1000))
	{
	    trig_training();
		ret = bsp_fpga_read_reg(0x8009c, &reg_value);
		logm_debug("reg_value=0x%x\r\n",reg_value);
		count++;
	}
    if(reg_value != 0xf0f0)
    {
        logm_debug("training fail value is %04x\n", reg_value);
        return 1;
    }
    logm_debug("training adc success\r\n");
    return 0;
}
void write_and_triger_tx_pll(unsigned short data)
{
    int ret;
	unsigned short value;
    ret=bsp_fpga_write_reg(0x80031, data); 
	
	
	if(0!=ret)
	{
		logm_debug("bsp_fpga_write_reg fail ret=%d\r\n",ret);
	}

	bsp_fpga_write_reg(0x80032, 0x0000);
    bsp_fpga_write_reg(0x80032, 0x0001);
	bsp_fpga_write_reg(0x80032, 0x0000);
	usleep(10);
	ret=bsp_fpga_read_reg(0x80031, &value); 
	logm_debug("bsp_fpga_write_reg value=0x%x\r\n",value);
	
	if(value!=data)
	{
		logm_debug("write_and_triger_tx_pll error value=0x%x,data=0x%x\r\n",value,data);
	}
}

int config_tx_pll(unsigned char  channal_id)
{
    unsigned short reg_value = 0;
    unsigned ret;
	int loop=0;
    unsigned short pllvalue_5830[]={0x0204,0x0404,0x063e,0x084d,0x0a11,0x0c08,0x0e91,0x1030,0x1200,0x1400,0x16b9,0x180d,0x1ac0};
	unsigned short pllvalue_5840[]={0x0204,0x0404,0x063f,0x084d,0x0a11,0x0c08,0x0e92,0x1000,0x1200,0x1400,0x16b9,0x180d,0x1ac0};
	unsigned short pllvalue_5790[]={0x0204,0x0404,0x063e,0x084d,0x0a11,0x0c08,0x0e90,0x1030,0x1200,0x1400,0x16b9,0x180d,0x1ac0};
	unsigned short pllvalue_5800[]={0x0204,0x0404,0x063f,0x084d,0x0a11,0x0c08,0x0e91,0x1000,0x1200,0x1400,0x16b9,0x180d,0x1ac0};
	if(0==channal_id)
	{
	    logm_debug(" tx pll 5830\r\n");
		for(loop=0;loop<sizeof(pllvalue_5830)/sizeof(unsigned short);loop++)
		{
			write_and_triger_tx_pll(pllvalue_5830[loop]);
		}
		
	}
	else if(1==channal_id)
	{
	    logm_debug(" tx pll 5840\r\n");
		for(loop=0;loop<sizeof(pllvalue_5840)/sizeof(unsigned short);loop++)
		{
			write_and_triger_tx_pll(pllvalue_5840[loop]);
		}
		
	}
	else if(2==channal_id)
	{
	    logm_debug(" tx pll 5790\r\n");
		for(loop=0;loop<sizeof(pllvalue_5790)/sizeof(unsigned short);loop++)
		{
			write_and_triger_tx_pll(pllvalue_5790[loop]);
		}
		
	}
	else if(3==channal_id)
	{
	    logm_debug(" tx pll 5780\r\n");
		for(loop=0;loop<sizeof(pllvalue_5800)/sizeof(unsigned short);loop++)
		{
			write_and_triger_tx_pll(pllvalue_5800[loop]);
		}
		
	}
    
    return 0;
}

int is_tx_pll_locked()
{
    int ret;
	unsigned short reg_value = 0;
	ret = bsp_fpga_read_reg(0x80034, &reg_value);
    if((ret != 0) || (reg_value != 1))
    {
        logm_debug("tx pll fail locked \r\n");
        return 2;
    }
	return 0;
}

void write_and_triger_rx_pll(unsigned short data)
{
    bsp_fpga_write_reg(0x800f1, data); 
	bsp_fpga_write_reg(0x800f2, 0x0000);
    bsp_fpga_write_reg(0x800f2, 0x0001);
	bsp_fpga_write_reg(0x800f2, 0x0000);
	usleep(10);
}

int config_rx_pll(unsigned char  channal_id)
{
    unsigned short reg_value = 0;
    unsigned ret;
	int loop=0;
    unsigned short pllvalue_5730[]={0x0204,0x0404,0x063e,0x084d,0x0a11,0x0c08,0x0e8f,0x1010,0x1200,0x1400,0x16b9,0x180d,0x1ac0};
	unsigned short pllvalue_5720[]={0x0204,0x0404,0x063f,0x084d,0x0a11,0x0c08,0x0e8f,0x1000,0x1200,0x1400,0x16b9,0x180d,0x1ac0};
	if(0==channal_id)
	{
	    logm_debug(" rx pll 5720\r\n");
		for(loop=0;loop<(sizeof(pllvalue_5720)/sizeof(unsigned short));loop++)
		{
			write_and_triger_rx_pll(pllvalue_5720[loop]);
		}
		
	}
	else if(1==channal_id)
	{
	    logm_debug(" rx pll 5730\r\n");
		for(loop=0;loop<(sizeof(pllvalue_5730)/sizeof(unsigned short));loop++)
		{
			write_and_triger_rx_pll(pllvalue_5730[loop]);
		}
		
	}
    
    return 0;
}

int is_rx_pll_locked()
{
    int ret;
	unsigned short reg_value = 0;
	ret = bsp_fpga_read_reg(0x800f4, &reg_value);
    if((ret != 0) || (reg_value != 1))
    {
        logm_debug("rx pll fail locked \r\n");
        return 2;
    }
	return 0;
}
void set_zmq_socket_option(void *socket, int type, int value)
{
    int rc = 0;
    rc = zmq_setsockopt(socket, type, &value, sizeof(int));
    CHECK_FAIL_NUMBER(rc, "set_zmq_socket_option zmq_setsockopt fail");
}

void create_zmq_sockets_rfs(void)
{
    void *ctx;
    int value;
    int ret;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
        exit(-1);
    }

    /*创建rfs pull push 接口*/
    push_socket_dispatch = zmq_socket(ctx, ZMQ_PUSH);
    if(NULL == push_socket_dispatch)
    {
        printf("create push_socket_dispatch fail!\n");
        exit(-1);
    }
    ret = zmq_bind(push_socket_dispatch, "tcp://*:5501");
    if(ret < 0)
    {
        printf("bind push_socket_dispatch socket fail,errno=%d datail:%s\n",errno,zmq_strerror(errno));
        exit(-1);
    }

    pull_socket_dispatch = zmq_socket(ctx, ZMQ_PULL);
    if(NULL == pull_socket_dispatch)
    {
        printf("create pull_socket_dispatch fail!\n");
        exit(-1);
    }

    ret = zmq_bind(pull_socket_dispatch, "tcp://*:5502");
    if(ret < 0)
    {
        printf("bind pull_socket_dispatch socket fail,errno=%d datail:%s\n",errno,zmq_strerror(errno));
        exit(-1);
    }
    /*cfg zmq*/

    req_socket_cfg = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == req_socket_cfg)
    {
        printf("create tcp req_socket_cfg fail!\n");
        exit(-1);
    }

    set_zmq_socket_option(req_socket_cfg, ZMQ_RCVTIMEO, 2000);
    set_zmq_socket_option(req_socket_cfg, ZMQ_LINGER, 0);

    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE, 1);
    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_CNT, 2);
    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_IDLE, 1);
    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_INTVL, 1);

    //ret= zmq_setsockopt (req_socket, ZMQ_SNDTIMEO, 2000, 4);
    ret = zmq_connect(req_socket_cfg, "tcp://192.168.1.218:5504");
    if(ret < 0)
    {
        printf("connect req_socket_cfg fail\n");
        exit(-1);
    }
    /*cfg pub*/
	sub_socket_cfg = zmq_socket(ctx, ZMQ_SUB);
    if(NULL == sub_socket_cfg)
    {
        printf("create sub_socket_cfg fail!\n");
        exit(-1);
    }
    
    ret = zmq_connect(sub_socket_cfg, "tcp://192.168.1.218:5505");
	if(ret < 0)
    {
        printf("connect sub_socket_cfg fail\n");
        exit(-1);
    }
	ret = zmq_setsockopt (sub_socket_cfg, ZMQ_SUBSCRIBE, "", 0);
	if(ret < 0)
    {
        printf("zmq_setsockopt zmq_setsockopt fail\n");
        exit(-1);
    }
	printf("sub_socket_cfg ZMQ_SUBSCRIBE success\n");
    return;
}

void stop_send_fpga_frame()
{
	bsp_fpga_write_reg(0x80046, 1);
	usleep(10);
	bsp_fpga_write_reg(0x80046, 0);
}


void prepare_before_send_fpga_frame()
{
	bsp_fpga_write_reg(0x80020, 0x0003);
	bsp_fpga_write_reg(0x80021, 0x7ffe);
	bsp_fpga_write_reg(0x80022, 0x0c70);
	bsp_fpga_write_reg(0x80023, 0x18d0);
	bsp_fpga_write_reg(0x80024, rfs_ctl.vva);
	bsp_fpga_write_reg(0x8000e, 0x000c);
	bsp_fpga_write_reg(0x800a4, rfs_ctl.datt[0]);
	bsp_fpga_write_reg(0x800a5, rfs_ctl.datt[1]);
	bsp_fpga_write_reg(0x800a6, rfs_ctl.datt[2]);
	bsp_fpga_write_reg(0x800a7, rfs_ctl.datt[3]);
	bsp_fpga_write_reg(0x80044, rfs_ctl.bst_interval);
	bsp_fpga_write_reg(0x80045, rfs_ctl.send_frame_num);
	bsp_fpga_write_reg(0x80046, 0x0000);
}
void prepare_after_send_fpga_frame()
{
    bsp_fpga_write_reg(0x80009, 0x00);
	usleep(100);
	bsp_fpga_write_reg(0x80009, 0x03);
}

void enable_vga(unsigned int enable_addr,unsigned int trigger_addr,unsigned short value)
{
    bsp_fpga_write_reg(enable_addr, value);
	bsp_fpga_write_reg(trigger_addr, 0x00);
	usleep(50);
	bsp_fpga_write_reg(trigger_addr, 0x01);
	return;

}

void prepare_for_recv_fpga_frame()
{
	bsp_fpga_write_reg(0x8009b, 0x01);
	bsp_fpga_write_reg(0x800b5, 0x0f);
	bsp_fpga_write_reg(0x800b6, 0x0f);
	//使能8路VGA
	enable_vga(0x800b8,0x800b7,0x80);
    enable_vga(0x800b8,0x800b7,0x180);
	enable_vga(0x800c8,0x800c7,0x80);
	enable_vga(0x800c8,0x800c7,0x180);
	enable_vga(0x800d8,0x800d7,0x80);
	enable_vga(0x800d8,0x800d7,0x180);
	enable_vga(0x800e8,0x800e7,0x80);
	enable_vga(0x800e8,0x800e7,0x180);
	
	bsp_fpga_write_reg(0x80095, 0x03);
	bsp_fpga_write_reg(0x80096, 0x01);	
}

void deal_dispatch_cfg_frame(char *recv_buf)
{
	init_device_t *init_device;
	CHECK_NULL_POINTER_RETURN_VOID(recv_buf);
	init_device=(init_device_t *)recv_buf;

	rfs_ctl.bst_interval=init_device->bst_interval;
	rfs_ctl.pll_channelID=init_device->pll_channelID;
	rfs_ctl.tx_power=init_device->tx_power;
	prepare_before_send_fpga_frame();
	config_tx_pll(init_device->pll_channelID);
	if(0!=is_tx_pll_locked())
	{
	    logm_debug("tx pll unlocked\r\n");
	}
	config_rx_pll(init_device->pll_channelID);
	if(0!=is_rx_pll_locked())
	{
	    logm_debug("rx pll unlocked\r\n");
	}
	traing_adc();
}

void get_time_of_day_us(unsigned long long *current_time)
{
    struct timeval sys_time;

    gettimeofday(&sys_time, NULL);

    *current_time = (unsigned long long)(long long)sys_time.tv_sec;
    *current_time = *current_time * 1000000 + sys_time.tv_usec;

}

int recv_fpga_frame(unsigned char * buf,unsigned int buf_len,unsigned int * pdwReadLen,unsigned int time_out)
{
    int ret=0;
	unsigned long long start,now;
	double backward_phase[16];
	if((buf==NULL)||(pdwReadLen==NULL))
	{
		return -1;
	}
	get_time_of_day_us(&start);
	now=0;

	while(now<start+time_out*1000)
	{
	    ret=bsp_fpga_read_frame(buf,buf_len,pdwReadLen);
		if(0==ret)
		{
		    //应该停止空口发送帧
		    stop_send_fpga_frame();
			//计算反向相位
			calc_backward_phase_diff(backward_phase);
		    break;
		}
		get_time_of_day_us(&now);
	}
	
	return ret;
}
int write_fpga_frame(char *data,int data_len)
{
    int ret,word_len,loop,i;
	unsigned short temp_data,len,crc;
	if(NULL==data)
	{
		logm_debug("NULL pointer error\r\n");
	   return -1;
	}
	word_len=((0==data_len%2)?data_len/2:(data_len/2+1));
	logm_debug("word_len=%d  data:\r\n",word_len);

	crc=do_crc(0xffff,data,data_len);

     //奇偶数字节特殊处理
	if(0==data_len%2)
	{
		for(loop=0;loop<word_len;loop++)
		{
		    temp_data=data[2*loop+1]<<8|data[2*loop];
			logm_debug_raw("0x%x ",temp_data);
			ret=bsp_fpga_write_reg(FPGA_SEND_DATA_ADDR+loop,temp_data);
			if(0!=ret)
			{
			   return ret;
			}
		}
		logm_debug_raw("\r\n");
		bsp_fpga_write_reg(FPGA_SEND_DATA_ADDR+loop,crc);
	}
	else
	{
		for(loop=0;loop<word_len-1;loop++)
		{
		    temp_data=data[2*loop+1]<<8|data[2*loop];
			logm_debug_raw("0x%x ",temp_data);
			ret=bsp_fpga_write_reg(FPGA_SEND_DATA_ADDR+loop,temp_data);
			if(0!=ret)
			{
			   return ret;
			}
		}
		temp_data =(crc&0xff)<<8|data[2*loop];
		logm_debug_raw("0x%x ",temp_data);
		bsp_fpga_write_reg(FPGA_SEND_DATA_ADDR+loop,temp_data);
		temp_data =(crc&0xff00)>>8;
		logm_debug_raw("0x%x \r\n",temp_data);
		bsp_fpga_write_reg(FPGA_SEND_DATA_ADDR+loop+1,temp_data);
	}

	bsp_fpga_write_reg(0x80008,(unsigned short)data_len+2);
	bsp_fpga_read_reg(0x80008,&len);
	logm_debug("0x80008 fpga len=%d,data_len=%d,crc=0x%x\n",len,data_len,crc);

	prepare_after_send_fpga_frame();
	clear_fpga_fifo();
    return 0;
}
void deal_bst_frame(char *recv_buf, int msg_len)
{
    int ret;
	unsigned int length=0;
	unsigned char buf[256]={0}; 
	unsigned char send_buf[1024]={0};

    logm_debug("deal_bst_frame\r\n");
	ret=write_fpga_frame(&recv_buf[1],msg_len-1);
    if(0!=ret)
    {
 	  logm_debug("bsp_fpga_write_frame error ret=%d\r\n",ret);
    }
    logm_debug("send bst frame success\r\n");
	/*等待接收*/
    ret=recv_fpga_frame(buf,sizeof(buf),&length,RECV_FRAME_TIMEOUT);
	if(ret!=0)
	{
	    logm_debug("not recv vst ret=%d\r\n",ret);
		send_buf[0]=0xE1;
		send_buf[1]=1;
	}
	else 
	{
	    logm_debug("recv vst \r\n");
		send_buf[0]=0xE1;
		send_buf[1]=0;
		memcpy(&send_buf[2],buf,length);
	}
	/*发送给控制器*/
	zmq_send(push_socket_dispatch,send_buf,length+2,0);
}
void deal_action_frame(char *recv_buf, int msg_len)
{
    int ret;
	unsigned int length=0;
	unsigned char buf[256]={0}; 
	unsigned char send_buf[1024]={0};
	logm_debug("send action frame \r\n");
	ret=write_fpga_frame(&recv_buf[2],msg_len-2);
    if(0!=ret)
    {
 	  logm_debug("bsp_fpga_write_frame error ret=%d\r\n",ret);
    }

	/*等待接收*/
    ret=recv_fpga_frame(buf,sizeof(buf),&length,RECV_FRAME_TIMEOUT);
	if(ret!=0)
	{
	    logm_debug("not recv action rsp ret=%d\r\n",ret);
		send_buf[0]=0xE2;
		send_buf[1]=1;
	}
	else 
	{
	    logm_debug("recv action rsp \r\n");
		send_buf[0]=0xE2;
		send_buf[1]=0;
		memcpy(&send_buf[2],buf,length);
	}
	/*发送给控制器*/
	zmq_send(push_socket_dispatch,send_buf,length+2,0);
}
void deal_event_report_frame(char *recv_buf, int msg_len)
{
    int ret;
	unsigned int length=0;

	logm_debug("send event report frame \r\n");
	ret=write_fpga_frame(&recv_buf[1],msg_len-1);
    if(0!=ret)
    {
 	  logm_debug("bsp_fpga_write_frame error ret=%d\r\n",ret);
    }
}
				
void deal_raw_msg_dispatch(unsigned char *recv_buf, int msg_len)
{
    unsigned char frame_type = 0;
    unsigned int length;
	int ret =0;
	int loop;
	
    frame_type = recv_buf[0];

	logm_debug("deal_raw_msg_dispatch frame_type=0x%x\r\n",frame_type);

    switch (frame_type)
    {
    case 0xF0:
		{
			//发卡器初始化,记录配置信息
			deal_dispatch_cfg_frame(recv_buf);
			break;
		}
    case 0xF1:
		{
			deal_bst_frame(recv_buf, msg_len);
			break;
		}	
	case 0xF2:
    {
        //action
        deal_action_frame(recv_buf, msg_len);
        break;
    }
	case 0xF3:
    {
        //event_and_report
        deal_event_report_frame(recv_buf, msg_len);
        break;
    }
    default:
    {
        logm_debug("recv wrong cmd cmd=0x%x\r\n", frame_type);
        break;
    }
    }

}
JSON_Object *parse_string_to_object(const char *strings,JSON_Value **string_value)
{
    JSON_Object *tmp_object=NULL;
    JSON_Value *tmp_value=NULL;
 
    /* 解析默认配置 */
    tmp_value= json_parse_string(strings);
    *string_value = NULL;
    if(tmp_value==NULL)
    {
    	return NULL;
    }
   if(json_value_get_type(tmp_value) == JSONObject)
   {
      tmp_object = json_value_get_object(tmp_value);
      *string_value = tmp_value;
   }
   else
   {
       json_value_free(tmp_value);
       *string_value=NULL;
       return NULL;
   }
    return tmp_object;
}

void send_cfg_req_msg(const char *type,const char *action,const char *content)
{
    int rc=0; 
	unsigned char send_buf[512]={0};
    JSON_Value *tmp_value=NULL;
    JSON_Object *tmp_object=NULL;
 
    printf("send_msg type=%s,action=%s,content=%s\r\n",type,action,content);
    
    tmp_value=json_value_init_object();
    tmp_object=tmp_value->value.object;
    json_object_set_string(tmp_object,"type",type);
    json_object_set_string(tmp_object,"action",action);
    if(NULL!=content)
    {
       json_object_set_string(tmp_object,"content",content);
    }
    memset(send_buf,0,sizeof(send_buf));
    rc=json_serialize_to_buffer(tmp_value,send_buf,sizeof(send_buf));
    /*释放*/
    json_value_free(tmp_value);
    printf("json_serialize_to_buffer send_buf = %s \r\n", send_buf);
    zmq_send(req_socket_cfg,send_buf,strlen(send_buf)+1,0);
}
int config_pll(unsigned char pll_channal_id)
{
    int ret=0;
    config_tx_pll(pll_channal_id);
	config_rx_pll(pll_channal_id);
	
	if(0!=is_tx_pll_locked())
	{
	    ret=1;
	    logm_debug("ERROR! main tx pll unlocked\r\n");
	}
	else
	{
		 logm_debug("main tx pll locked success\r\n");
	}
   
	if(0!=is_rx_pll_locked())
	{
	     ret=2;
	    logm_debug("ERROR! main rx pll unlocked\r\n");
	}
	else
	{
	    logm_debug("main rx pll locked success\r\n");
	}
	
	return ret;
}
int close_other_channel(int channel_index)
{
   if(channel_index>3)
   	{
   	    logm_debug("channel index error channel_index=%d \r\n",channel_index);
		return 1;
   	}
   bsp_fpga_write_reg(0x800a4,0);
   bsp_fpga_write_reg(0x800a5,0);
   bsp_fpga_write_reg(0x800a6,0);
   bsp_fpga_write_reg(0x800a7,0);
   bsp_fpga_write_reg(0x800a4+channel_index,0x003f);
   return 0;
}
int autocalabrate_power(int channel_index,calabrate_table_data_t calabrate_table_data,unsigned short target_power)
{
    int ret,loop;
	unsigned short adc0,adc1,real_power0,real_power1,adc_now;
	double k,b,target_diff,target_adc;
	double adc_diff;
	ret=1;
	//粗调vva
	bsp_fpga_write_reg(0x80024,calabrate_table_data.calabrate_table[0].vva);
	rfs_ctl.vva=calabrate_table_data.calabrate_table[0].vva;
	adc0=calabrate_table_data.calabrate_table[0].adc;
	adc1=calabrate_table_data.calabrate_table[1].adc;
	real_power0=calabrate_table_data.calabrate_table[0].real_power;
	real_power1=calabrate_table_data.calabrate_table[1].real_power;
	k=(double)(adc0-adc1)/(double)(real_power0-real_power1);
	b=adc0-k*real_power0;
	target_diff=25*k;
	target_adc=k*target_power+b;
	logm_debug("adc0=%d,adc1=%d,real_power0=%d,real_power1=%d\r\n",adc0,adc1,real_power0,real_power1);
	logm_debug("k=%f,b=%f,target_diff=%f,target_adc=%f\r\n",k,b,target_diff,target_adc);
	for(loop=0x3f;loop>0;loop--)
	{
	   //细调datt
	   bsp_fpga_write_reg(0x800a4+channel_index,loop);
	   usleep(10);
	   bsp_fpga_read_reg(0x800b1,&adc_now);
	   adc_diff=adc_now-target_adc;
	   logm_debug("adc_now=%d,target_adc=%f\r\n",adc_now,target_adc);
	   logm_debug("adc_diff=%f abs=%f\r\n",adc_diff,fabs(adc_diff));
	   if(fabs(adc_diff)<=target_diff)
	   	{
	   	    logm_debug("calabrate success adc_diff=%f datt=0x%x\r\n",adc_diff,loop);
			ret=0;
			rfs_ctl.datt[channel_index]=loop;
	   	    break;
	   	}
	}
	if(0==loop)
	{
	   logm_debug("calabrate failed\r\n"); 
	   ret=1;
	}
	return ret;
}
int autocalabrate_one_channel(int channel_index,calabrate_data_t calabrate_data,unsigned short target_power)
{
    int ret,loop,i;
	unsigned short vva,datt;
    calabrate_table_data_t *calabrate_table_data;


    logm_debug("autocalabrate_one_channel channel_index=%d,target_power=%d\r\n",channel_index,target_power);
	if(channel_index>=CALABRATE_CHANNEL_NUM)
	{
	   logm_debug("channel index error\r\n");
	   return 5;
	}
	//关闭其它通道
	ret=close_other_channel(channel_index);
	if(0!=ret)
	{
	   logm_debug("close_other_channel error\r\n");
	   return 1;
	}
	
	calabrate_table_data=calabrate_data.calabrate_table_data[channel_index];

	if(target_power>calabrate_table_data[0].calabrate_table[0].real_power)
	{
	   logm_debug("target_power is too big target_power=%d max=%d\r\n",target_power,calabrate_table_data[0].calabrate_table[0].real_power);
	   return 2;
	}
	
	//判断定标功率属于哪个表
	for(loop=0;loop<CALABRATE_TABLE_NUM-1;loop++)
	{
		if((abs(target_power-calabrate_table_data[loop].calabrate_table[0].real_power))<25)
		{
		    logm_debug("has calabrated vva=%d,datt=%d,read_power=%d,loop=%d channel_index=%d\r\n",calabrate_table_data[loop].calabrate_table[0].vva,
				calabrate_table_data[loop].calabrate_table[0].datt,
				calabrate_table_data[loop].calabrate_table[0].real_power,
				loop,channel_index);
		    //需要配置vva 记录datt
		    bsp_fpga_write_reg(0x80024,calabrate_table_data[loop].calabrate_table[0].vva);
			rfs_ctl.datt[channel_index]=calabrate_table_data[loop].calabrate_table[0].datt;
			rfs_ctl.vva=calabrate_table_data[loop].calabrate_table[0].vva;
		    return 0;
		}
		else if(abs(target_power-calabrate_table_data[loop].calabrate_table[1].real_power)<25)
		{
		    logm_debug("has calabrated vva=%d,datt=%d,read_power=%d,loop=%d channel_index=%d\r\n",calabrate_table_data[loop].calabrate_table[1].vva,
				calabrate_table_data[loop].calabrate_table[1].datt,
				calabrate_table_data[loop].calabrate_table[1].real_power,
				loop,channel_index);
		    //需要配置vva datt
		    bsp_fpga_write_reg(0x80024,calabrate_table_data[loop].calabrate_table[1].vva);
			rfs_ctl.datt[channel_index]=calabrate_table_data[loop].calabrate_table[1].datt;
			rfs_ctl.vva=calabrate_table_data[loop].calabrate_table[1].vva;
		    return 0;
		}
		else if((target_power>calabrate_table_data[loop+1].calabrate_table[0].real_power)
			&&(target_power<calabrate_table_data[loop].calabrate_table[0].real_power))
		{
		    logm_debug("target power in %d table power loop=%d,power loo+1=%d\r\n",loop,calabrate_table_data[loop].calabrate_table[0].real_power,
				calabrate_table_data[loop+1].calabrate_table[0].real_power);
		    break;
	    }
     }
	//最大定3次
    do
    {
        ret= autocalabrate_power(channel_index,calabrate_table_data[loop],target_power);
		i++;
    }while((ret!=0)&&(i<CALABRATE_MAX_TIMES));
	
	return ret;
	
}

void deal_power_autocalabrate(unsigned short target_power)
{
   int recv_len,ret,loop;
   calabrate_data_t calabrate_data;
   //读取定标数据
   ret= bsp_eeprom_rcv(CALABRATE_DATA_EEPROM_ADDR,sizeof(calabrate_data_t),&calabrate_data,&recv_len);
   if((0!=ret)||(recv_len!=sizeof(calabrate_data_t)))
   {
   	   logm_debug("bsp_eeprom_rcv error ret=%d,recv_len=%d\r\n",ret,recv_len);
	   return;
   }
   //init_calabrate_data(&calabrate_data);
   int i,j;
   for(i=0;i<CALABRATE_TABLE_NUM;i++)
   {
      for(j=0;j<CALABRATE_TABLE_DATA_NUM;j++)
      {
         logm_debug("i:%d,j%d,vva:0x%x,datt:0x%x,real_power:%d 0x%x,adc:%d\r\n",i,j,calabrate_data.calabrate_table_data[0][i].calabrate_table[j].vva,
		 	calabrate_data.calabrate_table_data[0][i].calabrate_table[j].datt,
		 	calabrate_data.calabrate_table_data[0][i].calabrate_table[j].real_power,
		 	calabrate_data.calabrate_table_data[0][i].calabrate_table[j].real_power,
		 	calabrate_data.calabrate_table_data[0][i].calabrate_table[j].adc);
      }
   }

   // 四个通道定标
   for(loop=0;loop<CALABRATE_CHANNEL_NUM;loop++)
   {
      autocalabrate_one_channel(loop,calabrate_data,target_power);
   }
   
    //定标完成后，写入四个通道的datt
   for(loop=0;loop<CALABRATE_CHANNEL_NUM;loop++)
   {
      bsp_fpga_write_reg(0x800a4+loop,rfs_ctl.datt[loop]);
   }
  
   return;
   
}
void config_rf_parameter()
{
    int ret=0;
	ret=config_pll(rfs_ctl.pll_channelID);
	if(0!=ret)
	{
	   logm_debug("config_pll fail ret=%d\r\n",ret);
	}
	deal_power_autocalabrate(rfs_ctl.tx_power*100);
	calibrate_forward_phase();
	return;
}
void deal_raw_msg_cfg(unsigned char *recv_buf, int msg_len)
{
    int rc = 0;
    unsigned char ret = 0;
    const char *type = NULL;
    const char *content = NULL;
    char *send_content = NULL;
    int result = 0;
    JSON_Value *cur_value = NULL;
    JSON_Object *cur_object = NULL;
    JSON_Value *rfs_value = NULL;
    JSON_Object *rfs_object = NULL;
    JSON_Value *tmp_value = NULL;
    JSON_Value *cur_value_set = NULL;
    JSON_Object *cur_object_set = NULL;
    unsigned int number = 0;

    cur_object = parse_string_to_object(recv_buf, &cur_value);
    if(NULL == cur_object)
    {
        logm_debug("NULL Pointer ERROR\r\n");
        return ;
    }
    type = json_object_get_string(cur_object, "type");
	if(0 == strcmp(type, "change_cfg"))
	{
	   logm_debug("recv change_cfg msg\r\n");
	   send_cfg_req_msg("rfs","request",NULL);
	}
	else if(0 == strcmp(type, "rfs_ack"))
	{
	    result = (int)json_object_get_number(cur_object, "result");
    	content = json_object_get_string(cur_object, "content");
	   logm_debug("rfs get ack result=%d content:%s\r\n",result, content);

	   if((0!=result)||(NULL==content))
	   	{ 
	   	    json_value_free(cur_value);
	   	    return;
	   	}
        //将content转化为对象，修改其中的值
        rfs_object = parse_string_to_object(content, &rfs_value);
        if(NULL == rfs_object)
        {
            json_value_free(cur_value);
            return;
        }
        rfs_ctl.bst_interval = (unsigned char)json_object_get_number(rfs_object, "BSTInterval");
        rfs_ctl.tx_power= (unsigned char)json_object_get_number(rfs_object, "TxPower");
        rfs_ctl.pll_channelID= (unsigned char)json_object_get_number(rfs_object, "PllChannelId");
        //rfs_ctl.time_out = (unsigned char)json_object_get_number(rfs_object, "TimeOut");
        logm_debug("bst_interval=%d\r\n", rfs_ctl.bst_interval);
		logm_debug("tx_power=%d\r\n", rfs_ctl.tx_power);
		logm_debug("pll_channelID=%d\r\n", rfs_ctl.pll_channelID);
		logm_debug("time_out=%d\r\n", rfs_ctl.time_out);
		config_rf_parameter();
        json_value_free(rfs_value);
	}
    else
    {
        logm_debug("wrong cfg type=%s\r\n", type);
    }
    json_value_free(cur_value);
    return;
}

void init_rfs()
{
   memset(&rfs_ctl,0,sizeof(rfs_ctl));
   rfs_ctl.bst_interval=10;
   rfs_ctl.pll_channelID=0;
   rfs_ctl.send_frame_num=10;
   rfs_ctl.tx_power=30;
   rfs_ctl.datt[0]=0x3f;
   rfs_ctl.datt[1]=0x3f;
   rfs_ctl.datt[2]=0x3f;
   rfs_ctl.datt[3]=0x3f;
   rfs_ctl.vva=0x18d0;
   prepare_before_send_fpga_frame();
   prepare_for_recv_fpga_frame();
}
#if 0
void init_calabrate_data(calabrate_data_t *calabrate_data)
{
    
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].vva=0;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].real_power=2374;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].adc=3252;
	
    calabrate_data->calabrate_table_data[0][0].calabrate_table[1].vva=0;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[1].real_power=2006;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[1].adc=3199;

	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].vva=0x1008;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].real_power=1881;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].adc=2965;
	
    calabrate_data->calabrate_table_data[0][1].calabrate_table[1].vva=0x1008;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[1].real_power=1381;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[1].adc=2890;

	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].vva=0x10d3;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].real_power=1363;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].adc=2663;
	
    calabrate_data->calabrate_table_data[0][2].calabrate_table[1].vva=0x10d3;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[1].real_power=865;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[1].adc=2608;

	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].vva=0x1190;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].real_power=876;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].adc=2413;
	
    calabrate_data->calabrate_table_data[0][3].calabrate_table[1].vva=0x1190;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[1].real_power=378;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[1].adc=2333;

	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].vva=0x127f;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].real_power=378;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].adc=2122;
	
    calabrate_data->calabrate_table_data[0][4].calabrate_table[1].vva=0x127f;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[1].real_power=-115;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[1].adc=2057;

	memcpy(calabrate_data->calabrate_table_data[1],calabrate_data->calabrate_table_data[0],sizeof(calabrate_data->calabrate_table_data[0]));
	memcpy(calabrate_data->calabrate_table_data[2],calabrate_data->calabrate_table_data[0],sizeof(calabrate_data->calabrate_table_data[0]));
	memcpy(calabrate_data->calabrate_table_data[3],calabrate_data->calabrate_table_data[0],sizeof(calabrate_data->calabrate_table_data[0]));
}
#endif

#if 1
void init_calabrate_data(calabrate_data_t *calabrate_data)
{
    
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].vva=0;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].real_power=2380;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[0].adc=2870;
	
    calabrate_data->calabrate_table_data[0][0].calabrate_table[1].vva=0;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[1].real_power=2010;
	calabrate_data->calabrate_table_data[0][0].calabrate_table[1].adc=2719;

	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].vva=0x1008;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].real_power=1887;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[0].adc=2576;
	
    calabrate_data->calabrate_table_data[0][1].calabrate_table[1].vva=0x1008;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[1].real_power=1388;
	calabrate_data->calabrate_table_data[0][1].calabrate_table[1].adc=2391;

	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].vva=0x10d3;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].real_power=1367;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[0].adc=2280;
	
    calabrate_data->calabrate_table_data[0][2].calabrate_table[1].vva=0x10d3;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[1].real_power=868;
	calabrate_data->calabrate_table_data[0][2].calabrate_table[1].adc=2091;

	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].vva=0x1190;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].real_power=878;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[0].adc=2020;
	
    calabrate_data->calabrate_table_data[0][3].calabrate_table[1].vva=0x1190;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[1].real_power=380;
	calabrate_data->calabrate_table_data[0][3].calabrate_table[1].adc=1842;

	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].vva=0x127f;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].datt=0x3f;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].real_power=378;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[0].adc=1765;
	
    calabrate_data->calabrate_table_data[0][4].calabrate_table[1].vva=0x127f;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[1].datt=0x2b;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[1].real_power=-115;
	calabrate_data->calabrate_table_data[0][4].calabrate_table[1].adc=1586;

	memcpy(calabrate_data->calabrate_table_data[1],calabrate_data->calabrate_table_data[0],sizeof(calabrate_data->calabrate_table_data[0]));
	memcpy(calabrate_data->calabrate_table_data[2],calabrate_data->calabrate_table_data[0],sizeof(calabrate_data->calabrate_table_data[0]));
	memcpy(calabrate_data->calabrate_table_data[3],calabrate_data->calabrate_table_data[0],sizeof(calabrate_data->calabrate_table_data[0]));
}
#endif


int calibrate_forward_phase()
{
    int ret,recv_len,loop;
	unsigned short adc,max,reg_a9,reg_aa,reg_ab,reg_ac;
    forward_phase_calibration_t forward_phase_calibration;
	//读取前向相位校准数据
    ret= bsp_eeprom_rcv(FORWARD_PHASE_CALIBRATE_EEPROM_ADDR,sizeof(forward_phase_calibration_t),&forward_phase_calibration,&recv_len);
    if((0!=ret)||(recv_len!=sizeof(forward_phase_calibration_t)))
    {
        logm_debug("bsp_eeprom_rcv error ret=%d,recv_len=%d\r\n",ret,recv_len);
 	   return ret;
    }

	if(1==forward_phase_calibration.has_calibrated)
	{
	    memcpy(&rfs_ctl.forward_phase_calibration,&forward_phase_calibration,sizeof(forward_phase_calibration));
		//写入寄存器
		bsp_fpga_write_reg(0x800a9,rfs_ctl.forward_phase_calibration.phase_diff[0]);
		bsp_fpga_write_reg(0x800aa,rfs_ctl.forward_phase_calibration.phase_diff[1]);
		bsp_fpga_write_reg(0x800ab,rfs_ctl.forward_phase_calibration.phase_diff[2]);
		bsp_fpga_write_reg(0x800ac,rfs_ctl.forward_phase_calibration.phase_diff[3]);
		logm_debug("forward phase has calibrated reg[a9-ac]:%d,%d,%d,%d\r\n",rfs_ctl.forward_phase_calibration.phase_diff[0],
			rfs_ctl.forward_phase_calibration.phase_diff[1],
			rfs_ctl.forward_phase_calibration.phase_diff[2],
			rfs_ctl.forward_phase_calibration.phase_diff[3]);
		return 0;
	}

	//校准前向相位，使输出功率最大
	max=0;
	reg_aa=0;
	bsp_fpga_read_reg(0x800a9,&reg_a9);
	//校准1，2通道，关闭3，4通道datt
	bsp_fpga_write_reg(0x800a4,rfs_ctl.datt[0]);
	bsp_fpga_write_reg(0x800a5,rfs_ctl.datt[1]);
	bsp_fpga_write_reg(0x800a6,0);
	bsp_fpga_write_reg(0x800a7,0);
	for(loop=0;loop<0x3f;loop++)
	{
	    bsp_fpga_write_reg(0x800aa,loop);
		usleep(10);
		bsp_fpga_read_reg(0x800b1,&adc);
		if(adc>max)
		{
		    max=adc;
			reg_aa=loop;
		}
	}
	logm_debug("1,2 adc max=%d\r\n",max);
	//校准3通道
	reg_ab=0;
	bsp_fpga_write_reg(0x800aa,reg_aa);
	bsp_fpga_write_reg(0x800a6,rfs_ctl.datt[2]);
	for(loop=0;loop<0x3f;loop++)
	{
	    bsp_fpga_write_reg(0x800ab,loop);
		usleep(10);
		bsp_fpga_read_reg(0x800b1,&adc);
		if(adc>max)
		{
		    max=adc;
			reg_ab=loop;
		}
	}
	logm_debug("1,2 3 adc max=%d\r\n",max);
	//校准4通道
	reg_ac=0;
	bsp_fpga_write_reg(0x800ab,reg_ab);
	bsp_fpga_write_reg(0x800a7,rfs_ctl.datt[3]);
	for(loop=0;loop<0x3f;loop++)
	{
	    bsp_fpga_write_reg(0x800ac,loop);
		usleep(10);
		bsp_fpga_read_reg(0x800b1,&adc);
		if(adc>max)
		{
		    max=adc;
			reg_ac=loop;
		}
	}
	logm_debug("1,2 3 4 adc max=%d\r\n",max);
	bsp_fpga_write_reg(0x800ac,reg_ac);
	rfs_ctl.forward_phase_calibration.has_calibrated=1;
	rfs_ctl.forward_phase_calibration.phase_diff[0]=reg_a9;
	rfs_ctl.forward_phase_calibration.phase_diff[1]=reg_aa;
	rfs_ctl.forward_phase_calibration.phase_diff[2]=reg_ab;
	rfs_ctl.forward_phase_calibration.phase_diff[3]=reg_ac;
	logm_debug("reg_a9-ac:%d,%d,%d,%d\r\n",reg_a9,reg_aa,reg_ab,reg_ac);
	//写入eeprom
	ret= bsp_eeprom_snd(FORWARD_PHASE_CALIBRATE_EEPROM_ADDR,sizeof(forward_phase_calibration_t),&rfs_ctl.forward_phase_calibration,&recv_len);
    if((0!=ret)||(recv_len!=sizeof(forward_phase_calibration_t)))
    {
    	   logm_debug("bsp_eeprom_snd error ret=%d,recv_len=%d\r\n",ret,recv_len);
 	   return ret;
    }
	return ret;
}
double calc_one_backward_phase(unsigned int fpga_reg_low)
{
    unsigned short low_value,middle_value,high_value;
	int real,image;
	double abs_divide_value,degree;
    bsp_fpga_read_reg(fpga_reg_low,&low_value);
	bsp_fpga_read_reg(fpga_reg_low+1,&middle_value);
	bsp_fpga_read_reg(fpga_reg_low+2,&high_value);
	logm_debug("low_value=0x%x,middle_value=0x%x,high_value=0x%x\r\n",low_value,middle_value,high_value); 
	real=(((middle_value&0xff)<<16)|low_value)&0xffffff;
	if((middle_value & 0x0080) != 0)
	{
	   real = (-1)*(((~real)&0x007fffff)+1);
	}
	image = ((high_value<<8)|((middle_value&0xff00)>>8))&0xffffff;
    if((high_value & 0x8000) != 0)
    {
        image = (-1)*(((~image)&0x007fffff)+1);
    }
	logm_debug("fpga_reg_low=0x%x,real=%d,image=%d\r\n",fpga_reg_low,real,image); 
	
	//计算相位
	if(0==real)
	{
	   if(image>0)
		{
		    degree=90;
		}
		else if(image<0)
		{
		    degree=270;
		}
		else
		{
		    degree=0;
		}
		return degree;
	}
	
	
	
	#if 0
	abs_divide_value=fabs((double)image/(double)real);
	if((real>0)&&(image>=0))
	{
	    degree=atan(abs_divide_value)/PI*180;
	}
	else if((real>0)&&(image<0))
	{
	    degree=360-atan(abs_divide_value)/PI*180;
	}
	else if((real<0)&&(image>=0))
	{
	    degree=180-atan(abs_divide_value)/PI*180;
	}
	else if((real<0)&&(image<0))
	{
	    degree=180+atan(abs_divide_value)/PI*180;
	}
	else
	{
	    logm_debug("error\r\n"); 
	}
	#endif
	degree=atan2(image, real)*180/PI;
	//degree=atan((double)image/(double)real)/PI*180;
	return degree;
      
}
int calc_backward_phase_diff(double *delta_degree)
{
    int loop,ret,i,j,k;
    double degree[8];
	if(NULL==delta_degree)
	{
	    logm_debug("calc_backward_phase_diff null pointer error\r\n");
	    return -1;
	}
	
	for(loop=0;loop<5;loop++)
	{
		degree[loop]=calc_one_backward_phase(0x80060+loop*3);
		logm_debug("degree[%d]=%f\r\n",loop,degree[loop]);
	}
	for(loop=5;loop<8;loop++)
	{
		degree[loop]=calc_one_backward_phase(0x80050+(loop-5)*3);
		logm_debug("degree[%d]=%f\r\n",loop,degree[loop]);
	}
    //计算差值
    for(i=0,k=0;i<4;i++)
	{
	    for(j=i+1;j<5;j++)
	    {
	        delta_degree[k]=degree[i]-degree[j];
			if(delta_degree[k]<0)
			{
			    delta_degree[k]=delta_degree[k]+360;
			}
			logm_debug("delta_degree[%d]=%f\r\n",k,delta_degree[k]);
			k++;
	    }
	}
	for(i=4;i<7;i++)
	{
	    for(j=i+1;j<8;j++)
	    {
	        delta_degree[k]=degree[i]-degree[j];
			if(delta_degree[k]<0)
			{
			    delta_degree[k]=delta_degree[k]+360;
			}
			logm_debug("delta_degree[%d]=%f\r\n",k,delta_degree[k]);
			k++;
	    }
	}
	return 0;
}
void recover_old_fpgadata_after_calibrate_backphase()
{
    int ret;
    //配置发射频率
	config_tx_pll(rfs_ctl.pll_channelID);
	
	if(0!=is_tx_pll_locked())
	{
	    ret=1;
	    logm_debug("ERROR! main tx pll unlocked\r\n");
		return ret;
	}
	else
	{
		 logm_debug(" tx pll locked success\r\n");
	}

	//恢复定标功率
	bsp_fpga_write_reg(0x80024,rfs_ctl.vva); //vva
	bsp_fpga_write_reg(0x800c0,rfs_ctl.reg_c0); //开关
	bsp_fpga_write_reg(0x800c1,rfs_ctl.reg_c1); //EN-TX打开
	bsp_fpga_write_reg(0x8009d,rfs_ctl.reg_9d); //pll打开
	bsp_fpga_write_reg(0x800a4,rfs_ctl.datt[0]);//datt
	bsp_fpga_write_reg(0x800a5,rfs_ctl.datt[1]);
	bsp_fpga_write_reg(0x800a6,rfs_ctl.datt[2]);
	bsp_fpga_write_reg(0x800a7,rfs_ctl.datt[3]);

	bsp_fpga_write_reg(0x800f6,2); 

	return;
}
int calibrate_backward_phase()
{
	int ret,recv_len,loop,loop1;
	backward_phase_calibration_t backward_phase_calibration;

	double phase_diff[BACKWORD_PHASE_CALIBRATE_MAX_TIMES][BACKWORD_PHASE_CALIBRATE_NUM],sum;

	logm_debug("calibrate backword phase\r\n");
	//读取反向相位校准数据
    /*ret= bsp_eeprom_rcv(BACKWARD_PHASE_CALIBRATE_EEPROM_ADDR,sizeof(backward_phase_calibration_t),&rfs_ctl.backward_phase_calibration,&recv_len);
    if((0!=ret)||(recv_len!=sizeof(backward_phase_calibration_t)))
    {
        logm_debug("bsp_eeprom_rcv error ret=%d,recv_len=%d\r\n",ret,recv_len);
 	   return ret;
    }
	if(1==rfs_ctl.backward_phase_calibration.has_calibrated)
	{
		logm_debug("has calibrate backword phase\r\n");
		return 0;
	}*/

	//配置发射频率为反向接收频率
	config_tx_pll(rfs_ctl.pll_channelID+2);
	
	if(0!=is_tx_pll_locked())
	{
	    ret=1;
	    logm_debug("ERROR! tx pll unlocked\r\n");
		return ret;
	}
	else
	{
		 logm_debug("tx pll locked success\r\n");
	}
	//记录寄存器值
	bsp_fpga_read_reg(0x800c0,&rfs_ctl.reg_c0); //开关
	bsp_fpga_write_reg(0x800c1,&rfs_ctl.reg_c1); //EN-TX打开
	bsp_fpga_write_reg(0x8009d,&rfs_ctl.reg_9d); //pll打开
	//发送最大功率
	bsp_fpga_write_reg(0x80024,0); //vva
	bsp_fpga_write_reg(0x800c0,1); //开关
	bsp_fpga_write_reg(0x800c1,1); //EN-TX打开
	bsp_fpga_write_reg(0x8009d,1); //pll打开
	bsp_fpga_write_reg(0x800a4,0);//datt
	bsp_fpga_write_reg(0x800a5,0);
	bsp_fpga_write_reg(0x800a6,0);
	bsp_fpga_write_reg(0x800a7,0);
	//打开接收开关
	bsp_fpga_write_reg(0x800f6,1); 
    
	//计算相位差
	for(loop=0;loop<BACKWORD_PHASE_CALIBRATE_MAX_TIMES;loop++)
	{
	    //启动单音相位校准
		bsp_fpga_write_reg(0x8005c,0); 
		usleep(10);
		bsp_fpga_write_reg(0x8005c,1);
		usleep(10);
		bsp_fpga_write_reg(0x8005c,0); 
		usleep(1000);

		//计算相位差
	    calc_backward_phase_diff(phase_diff[loop]);
	}
	for(loop=0;loop<BACKWORD_PHASE_CALIBRATE_NUM;loop++)
	{
	    sum=0;
	    for(loop1=0;loop1<BACKWORD_PHASE_CALIBRATE_MAX_TIMES;loop1++)
	    {
	        sum+=phase_diff[loop1][loop];
	    }
		rfs_ctl.backward_phase_calibration.phase_diff[loop]=sum/BACKWORD_PHASE_CALIBRATE_MAX_TIMES;
		logm_debug("rfs_ctl.backward_phase_calibration.phase_diff[%d]=%f\r\n",loop,rfs_ctl.backward_phase_calibration.phase_diff[loop]);
	}
	rfs_ctl.backward_phase_calibration.has_calibrated=1;

    //保存到eeprom
	/*ret= bsp_eeprom_snd(BACKWARD_PHASE_CALIBRATE_EEPROM_ADDR,sizeof(backward_phase_calibration_t),&rfs_ctl.backward_phase_calibration,&recv_len);
    if((0!=ret)||(recv_len!=sizeof(backward_phase_calibration_t)))
    {
        logm_debug("bsp_eeprom_snd error ret=%d,recv_len=%d\r\n",ret,recv_len);
 	   return ret;
    }*/

	//恢复原始数据
	recover_old_fpgadata_after_calibrate_backphase();
	return 0;
}

int main(int argc, char *argv[])
{

    zmq_pollitem_t  items[3];
    int item_num;
    int ret,loop;
    int recv_len;
	unsigned char recv_buf[2048];

    init_logm("rfs");
	create_zmq_sockets_rfs();
	
	
    init_rfs();
    logm_debug("rfs begin\r\n");

    bsp_fpga_init();
	bsp_eeprom_init();
    config_fpga_pll();
	ret=config_pll(0);
	if(0!=ret)
	{
	   logm_debug("config_pll fail ret=%d\r\n",ret);
	}
	ret = traing_adc();
    if(0!=ret)
    {
	    logm_debug("ERROR! traing_adc failed\r\n");
	}
	else
	{
	    logm_debug("main traing_adc success\r\n");
	}

	//校准反向相位
	calibrate_backward_phase();
	
    items[0].socket = pull_socket_dispatch;
    items[0].events = ZMQ_POLLIN;
    items[1].socket = req_socket_cfg;
    items[1].events = ZMQ_POLLIN;
	items[2].socket = sub_socket_cfg;
    items[2].events = ZMQ_POLLIN;

	send_cfg_req_msg("rfs","request",NULL);

	logm_debug("begin while loop\r\n");
    while(1)
    {
        ret = zmq_poll(items, 3, -1);
        logm_debug("rfs zmq_poll return , return %d \n", ret);
        memset(recv_buf, 0, sizeof(recv_buf));
        if(items[0].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(pull_socket_dispatch, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) continue;

            logm_debug("recv from dispatch pull socket %d bytes  recv data:\n", recv_len);
			for(loop=0;loop<recv_len;loop++)
			{
				logm_debug_raw("0x%x ",recv_buf[loop]); 
			}
	        logm_debug_raw("\r\n");
            deal_raw_msg_dispatch(recv_buf, recv_len);
        }
        else if(items[1].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(req_socket_cfg, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) continue;

            logm_debug("recv from cfg req socket %d bytes \n", recv_len);
            deal_raw_msg_cfg(recv_buf, recv_len);
        }
		else if(items[2].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(sub_socket_cfg, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) continue;

            logm_debug("recv from cfg sub socket %d bytes \n", recv_len);
            deal_raw_msg_cfg(recv_buf, recv_len);
        }
        else
        {
            logm_debug("pull error \r\n ");
        }
    }

    return 0;
}



