
/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： eeprom.c
* 文件标识： 
* 内容摘要：对eeprom进行读写
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/
#include "bsp.h"


i2c_dev_t pll_device;

//error code
#define WRITE_FAIL   1
#define NULL_POINTER 2
#define READ_FAIL    3
#define READ_LONG    4

#define SEGMENT_SIZE 7

static int is_fpga_pll_init = 0;

unsigned int bsp_init_pll(void)
{
    unsigned int dwRet = 0;

    bsp_epld_init();
    bsp_i2c_init();

    pll_device.addr             = 0xC8;
    pll_device.frequency           = 50;
    pll_device.p_i2c_bus              = &i2c_bus[2];
    pll_device.delay_cnt             = (unsigned short)((1000000L)/(90*50));

    dwRet = i2c_take_semaphore(&pll_device);
    if(0 != dwRet)
    {
        return dwRet;
    }

    dwRet = i2c_reset(&pll_device);
    if(0 != dwRet)
    {
        dwRet |= 11;
    }

    dwRet = i2c_give_semaphore(&pll_device);
    if(0 != dwRet)
    {
        return dwRet;
    }

    return dwRet;
}

unsigned int bsp_write_pll(unsigned int dwOffset,unsigned int dwLen ,unsigned char *pucBuf, unsigned int * pdwSndLen)
{
    unsigned int seg_num;
    unsigned int last_bytes;
    unsigned char write_buf[8];
    int i;
    unsigned char send_bytes = 0;
    unsigned int dwRet;
    int j;

    if(is_fpga_pll_init == 0)
    {
        bsp_init_pll();
        is_fpga_pll_init = 1;
    }

    seg_num = dwLen/7;
    last_bytes = dwLen%7;

    for(i=0; i<seg_num; ++i)
    {        
        write_buf[0] = 7;
        memcpy(&write_buf[1], &pucBuf[i*7], 7);
		dwRet = bsp_i2c_send(&pll_device , (unsigned char)(dwOffset+i*7), 8, write_buf, &send_bytes);
		if((0 != dwRet) || (send_bytes != 8))
		{
		    return WRITE_FAIL;
		}
    }

    write_buf[0] = last_bytes;
    memcpy(&write_buf[1], &pucBuf[7*seg_num], last_bytes);
	dwRet = bsp_i2c_send(&pll_device , (unsigned char)(dwOffset+seg_num*7), (last_bytes+1), write_buf, &send_bytes);
	if((0 != dwRet) || (send_bytes != (last_bytes+1)))
	{	    
	    return WRITE_FAIL;
	}

    *pdwSndLen = dwLen;

    return 0;
}


unsigned int  bsp_read_pll(unsigned int dwOffset, unsigned int dwLen, unsigned char *pucBuf, unsigned int * pdwRcvLen)
{
    unsigned int dwRet = 0;
    unsigned char recv_buf[8];
    
    unsigned int seg_num = 0;
    unsigned int last_bytes = 0;
    unsigned int i;
    unsigned int read_bytes = 0;
    int j;

    if(0 == is_fpga_pll_init)
    {
        bsp_init_pll();
        is_fpga_pll_init = 1;
    }
    
    if((NULL == pucBuf) || (NULL == pdwRcvLen))
    {
        return NULL_POINTER;
    }

    seg_num = dwLen/7;
    last_bytes = dwLen%7;

    if(last_bytes != 0)
    {
    	seg_num += 1;
    }

    for(i=0; i<seg_num;++i)
    {
        dwRet = bsp_i2c_rcv(&pll_device, (unsigned char)(dwOffset+i*7), 8, recv_buf, &read_bytes);
	    if((0 != dwRet) ||(8 != read_bytes))
	    {
	        return READ_FAIL;
	    }

	    if(i == (seg_num-1))
	    {
	        memcpy(&pucBuf[i*7], &recv_buf[1], last_bytes);
	    }
	    else
	    {
	        memcpy(&pucBuf[i*7], &recv_buf[1], 7);
	    }
    }

    *pdwRcvLen = dwLen;
    return 0;
}




