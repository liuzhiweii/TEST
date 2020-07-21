#ifndef _BSP_DRV_RTC_H_
#define _BSP_DRV_RTC_H_
	
#ifdef __cplusplus
extern "C"
{
#endif


typedef struct tagrtc_time_t
{
    unsigned int tm_sec;
    unsigned int tm_min;
    unsigned int tm_hour;
    unsigned int tm_mday;//DAY OF MONTH
    unsigned int tm_mon;
    unsigned int tm_year;
    unsigned int tm_wday;//WEEK of DAY
    unsigned int tm_yday;//
    unsigned int tm_isdst;
} rtc_time_t;
	
typedef struct
{
	unsigned char tm_sec;
	unsigned char tm_min;
	unsigned char tm_hour;
	unsigned char tm_wday;
	unsigned char tm_mday;
	unsigned char tm_mon;
	unsigned char tm_year;
}rtc_time_ext;

unsigned int bsp_rtc_init(void);
unsigned int bsp_rtc_read_time(rtc_time_t *ptDrvRtcTm, unsigned char *pucOpt);
unsigned int bsp_rtc_write_time(rtc_time_t *ptDrvRtcTm, unsigned char *pucOpt);

#ifdef __cplusplus
}
#endif

		
#endif/* _BSP_DRV_RTC_H_  */

