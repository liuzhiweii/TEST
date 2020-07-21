#include <stdio.h>
#include "bsp.h"


#define bcd_to_bin(val)	(((val) & 0x0f) + ((val)>>4)*10)
#define bin_to_bcd(val)	((((val)/10)<<4) + (val)%10)

#define ERR_TIME_FORMAT  1

static i2c_dev_t    rtc_dev;
static int is_rtc_init = 0;

unsigned int bsp_rtc_init(void)
{
    unsigned char data = 0;
    unsigned char send_len = 0;
    unsigned int ret = 0;
    unsigned int read_len = 0;

    if(is_rtc_init == 1)
    {
        return 0;
    }

    ret = bsp_i2c_init();
    if(ret != 0)
    {
    	return ret;
    }

    rtc_dev.addr = 0xd0;
    rtc_dev.frequency = 50;
    rtc_dev.delay_cnt =   (unsigned short)((1000000L) / (90 * 50));    
    rtc_dev.p_i2c_bus = &i2c_bus[2];

    ret = i2c_reset(&rtc_dev);
    if( 0 != ret )
    {
        return ret;
    }

    ret = bsp_i2c_rcv(&rtc_dev, 0x00,1,&data,&read_len);
    if( 0 != ret )
    {
        return ret;
    }
    data &= ~0x80;
    ret = bsp_i2c_send(&rtc_dev,0x00,1,&data,&send_len);
    if( 0 != ret )
    {
        return ret;
    }
    
    ret = bsp_i2c_rcv(&rtc_dev,0x02,1,&data,&read_len);
    if( 0 != ret )
    {
        return ret;
    }
    data &= ~0x40;
    ret = bsp_i2c_send(&rtc_dev,0x02,1,&data,&send_len);
    if( 0 != ret )
    {
        return ret;
    }
    
    ret = bsp_i2c_rcv(&rtc_dev,0x07,1,&data,&read_len);
    if( 0 != ret )
    {
        return ret;
    }
    data &= ~0x20;
    ret = bsp_i2c_send(&rtc_dev,0x07,1,&data,&send_len);
    if( 0 != ret )
    {
        return ret;
    }

    is_rtc_init = 1;
    return 0;
}


unsigned int bsp_rtc_read_time(rtc_time_t *p_time, unsigned char *opt)
{
    unsigned char time_buf[7] = {0};
    unsigned int read_len = 0;
    unsigned int ret = 0;

    ret = bsp_rtc_init();
    if(0 != ret)
    {
        return ret;
    }

    ret = bsp_i2c_rcv(&rtc_dev,0x00,7,time_buf,&read_len);
    if((0 != ret))
    {
        return ret;
    }
   
    p_time->tm_sec   = (time_buf[0]&0x7f);
    p_time->tm_min   = (time_buf[1]&0x7f);
    p_time->tm_hour  = (time_buf[2]&0x3f);
    p_time->tm_wday  = (time_buf[3]&0x7);
    p_time->tm_mday  = (time_buf[4]&0x3f);
    p_time->tm_mon   = (time_buf[5]&0x1f);
    p_time->tm_year  =  time_buf[6];


	#if 1
    p_time->tm_sec = bcd_to_bin(p_time->tm_sec);
    p_time->tm_min = bcd_to_bin(p_time->tm_min);
    p_time->tm_hour = bcd_to_bin(p_time->tm_hour);
    p_time->tm_mday = bcd_to_bin(p_time->tm_mday);
    p_time->tm_mon = bcd_to_bin(p_time->tm_mon);	
    p_time->tm_wday = bcd_to_bin(p_time->tm_wday);
    p_time->tm_year = bcd_to_bin(p_time->tm_year);



    p_time->tm_year = p_time->tm_year + 2000;
    #if 0
    p_time->tm_year += ((p_time->tm_mon & 0x80) ? 100 : 0);
    p_time->tm_year = p_time->tm_year + 1900;
    if(p_time->tm_year < 1970)
    {
        p_time->tm_year += 100;
    }
    #endif
    #endif
    return 0;
}

unsigned int bsp_rtc_write_time(rtc_time_t *p_time, unsigned char *opt)
{
    unsigned char read_len = 0;
    unsigned char time_buf[7] = {0};
    unsigned int ret = 0;

    ret = bsp_rtc_init();
    if(0 != ret)
    {
        return ret;
    }

    
    if ((p_time->tm_year < 2000) ||
        (p_time->tm_mon > 12)    ||
        (p_time->tm_mday == 0)   ||
        (p_time->tm_hour >= 24)  ||
        (p_time->tm_min >= 60)   ||
        (p_time->tm_sec >= 60)   ||
        (p_time->tm_wday > 7))
    {
        return ERR_TIME_FORMAT;
    }
           
    p_time->tm_year = p_time->tm_year % 100;
    time_buf[6] = bin_to_bcd(p_time->tm_year);
    time_buf[5] = bin_to_bcd(p_time->tm_mon);
    time_buf[4] = bin_to_bcd(p_time->tm_mday);
    time_buf[3] = bin_to_bcd(p_time->tm_wday);
    time_buf[2] = bin_to_bcd(p_time->tm_hour);
    time_buf[1] = bin_to_bcd(p_time->tm_min) | 0x80;
    time_buf[0] = bin_to_bcd(p_time->tm_sec);

    printf("write sec: %d min:%d hour:%d wday: %d mday:%d mon:%d year:%d \n",
          time_buf[0], 
          time_buf[1],
          time_buf[2],
          time_buf[3],
          time_buf[4],
          time_buf[5],
          time_buf[6]);

    
    ret = bsp_i2c_send(&rtc_dev, 0x00,7,time_buf,&read_len);
    if(0 != ret)
    {
        return 11;
    }

    return 0;
}




int bsp_rtc_read(rtc_time_ext *rtc_time)
{
	unsigned int read_len;
	return bsp_i2c_rcv(&rtc_dev, 0x00 , 7, (unsigned char *)rtc_time, &read_len);
}

int bsp_rtc_write(rtc_time_ext *rtc_time)
{
	unsigned int read_len;
	return bsp_i2c_send(&rtc_dev, 0x00,7, (unsigned char *)rtc_time,&read_len);
}


