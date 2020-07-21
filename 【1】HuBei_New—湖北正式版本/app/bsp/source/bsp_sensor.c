#include "bsp.h"
#include <stdio.h>

#define    TSENSOR_RLTS_R      0x00      /* read local temperature; returns latest temperature */
#define    TSENSOR_RRTE_R      0x01     /* read temote temperature; returns latest temperature */
#define    TSENSOR_RSL_R       0x02     /* read status byte(flags, busy signal) */
#define    TSENSOR_RCL_R       0x03      /* read configuration byte */
#define    TSENSOR_RCRA_R      0x04      /* read conversion rate byte */
#define    TSENSOR_RLHN_R      0x05     /* read local Thigh limit */
#define    TSENSOR_RLLI_R      0x06     /* read local Tlow limit */
#define    TSENSOR_RRHI_R      0x07     /* read remote Thigh limit */
#define    TSENSOR_RRLS_R      0x08     /* read remote Tlow limit */
#define    TSENSOR_WCA_W       0x09    /* write configuration byte */
#define    TSENSOR_WCRW_W      0x0A    /* write conversion rate byte */
#define    TSESOR_WLHO_W       0x0B    /* write local Thigh limit */
#define    TSENSOR_WLLM_W      0x0C     /* write local Tlow limit */
#define    TSENSOR_WRHA_W      0x0D    /* write remote Thigh limit */
#define    TSENSOR_WRLN_W      0x0E     /* write remote Tlow limit */
#define    TSENSOR_OSHT        0x0F     /* one-shot command (use send-byte format) */


i2c_dev_t first_tsensor;
unsigned int is_tsensorinit = 0;


static unsigned int __write_byte(i2c_dev_t * dev, unsigned char ucCmd, unsigned char value)
{
    unsigned int ret = 0;
    unsigned char ucRealLen = 0;
    ret = bsp_i2c_send(dev , ucCmd, 1, &value, &ucRealLen);
    if((0 != ret) ||(1 != ucRealLen))
    {
        return ret;
    }
    return 0;
}


static unsigned int __read_byte(i2c_dev_t * dev, unsigned char ucCmd, unsigned char * pvalue)
{
    unsigned int ret = 0;
    unsigned int dwRealLen = 0;
    if(NULL == pvalue)
    {
        return 1;
    }
    ret = bsp_i2c_rcv(dev , ucCmd, 1, pvalue, &dwRealLen);
    if((0 != ret) ||(1 != dwRealLen))
    {
        return ret;
    }
    return 0;
}

static unsigned int __tsensor_detect(i2c_dev_t * dev)
{
    unsigned char value = 0;
    unsigned int ret = 0;

    ret = __read_byte(dev, TSENSOR_RSL_R, &value);
    if((ret != 0) || ((value & 0x03) != 0x00))
    {
        printf("read status byte error,ret = 0x%x,status = %x",ret,value);
        return 3;
    }

    ret = __read_byte(dev, TSENSOR_RCL_R, &value);
    if((ret != 0) || ((value & 0x3F) != 0x00))
    {
        printf("read config byte error,ret = 0x%x,config = %x",ret,value);
        return 4;
    }

    ret = __read_byte(dev, TSENSOR_RCRA_R, &value);
    if((ret != 0) || ((value & 0xF8) != 0x00))
    {
        printf("read conversion byte error,ret = 0x%x,conver = %x",ret,value);
        return 5;
    }
    
    /* init configuration byte and conversion rate byte */	
    ret = __write_byte(dev, TSENSOR_WCA_W, 0x00);
    if(ret != 0) 
    {
        printf("write config byte error!");
        return 6;
    }
    ret = __write_byte(dev, TSENSOR_WCRW_W, 0x04);
    if(ret != 0) 
    {
        printf("write convesion byte error!");
        return 7;
    }

    return  0;
}


unsigned int bsp_tsensor_init(void)
{
    unsigned int ret = 0;

    if(is_tsensorinit == 1)
    {
    	return 0;
    }
    
    first_tsensor.addr = 0x30;
    first_tsensor.frequency = 50;
    first_tsensor.delay_cnt = (unsigned short)((1000000L)/(90*50));
    first_tsensor.p_i2c_bus = &i2c_bus[1];
    first_tsensor.p_i2c_bus->mutex = &i2c_mutex;


    ret = __tsensor_detect(&first_tsensor);
    if(0 != ret)
    {
        return ret;
    }

    is_tsensorinit = 1;
    return 0;
}


unsigned int bsp_tsensor_read_local_temp(unsigned char * pvalue)
{
	unsigned int ret = 0;

	ret = __read_byte(&first_tsensor, TSENSOR_RLTS_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}

	return 0;
}

unsigned int bsp_tsensor_read_remote_temp(unsigned char * pvalue)
{
	unsigned int ret = 0;

	ret = __read_byte(&first_tsensor, TSENSOR_RRTE_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}

	return 0;
}

unsigned int bsp_tsensor_set_temp_high(unsigned char value)
{
	unsigned int ret = 0;

	ret = __write_byte(&first_tsensor, TSESOR_WLHO_W, value);
	if(0 != ret)
	{
		return ret;
	}

	return 0;

}

unsigned int bsp_tsensor_set_temp_low(unsigned char value)
{
	unsigned int ret = 0;

	ret = __write_byte(&first_tsensor, TSENSOR_WLLM_W, value);
	if(0 != ret)
	{
		return ret;
	}

	return 0;
}

unsigned int bsp_tsensor_set_remote_temp_high(unsigned char value)
{
	unsigned int ret = 0;

	ret = __write_byte(&first_tsensor, TSENSOR_WRHA_W, value);
	if(0 != ret)
	{
		return ret;
	}

	return 0;

}

unsigned int bsp_tsensor_set_remote_temp_low(unsigned char value)
{
	unsigned int ret = 0;

	ret = __write_byte(&first_tsensor, TSENSOR_WRLN_W, value);
	if(0 != ret)
	{
		return ret;
	}

	return 0;

}

unsigned int bsp_tsensor_get_temp_high(unsigned char * pvalue)
{
	unsigned int ret = 0;

	ret = __read_byte(&first_tsensor, TSENSOR_RLHN_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}

	return 0;

}

unsigned int bsp_tsensor_get_temp_low(unsigned char * pvalue)
{
	unsigned int ret = 0;
	ret = __read_byte(&first_tsensor, TSENSOR_RLLI_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}
	
	return 0;

}

unsigned int bsp_tsensor_get_remote_temp_high(unsigned char * pvalue)
{
	unsigned int ret = 0;

	ret = __read_byte(&first_tsensor, TSENSOR_RRHI_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}

	return 0;
}


unsigned int bsp_tsensor_get_remote_temp_low(unsigned char * pvalue)
{
	unsigned int ret = 0;

	ret = __read_byte(&first_tsensor, TSENSOR_RRLS_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}

	return 0;
}

unsigned int bsp_tsensor_get_alarm_status(unsigned char * pvalue)
{
	unsigned int ret = 0;

	ret = __read_byte(&first_tsensor, TSENSOR_RSL_R, pvalue);
	if(0 != ret)
	{
		return ret;
	}

	return 0;

}

unsigned int bsp_tsensor_get_temperature(unsigned char ucFunID,unsigned char * pvalue)
{
    return 0;
}


unsigned int bsp_tsensor_set_temperature(unsigned char ucFunID,unsigned char  value)
{
    return 0;
}

