#include "bsp.h"
#include "drvtest.h"

unsigned int drvtest_settime(rtc_time_t tTime)
{
    unsigned int dwRet = 0;
    unsigned char ucopt = 0;

    rtc_time_t tTemp;

    memcpy(&tTemp, &tTime, sizeof(rtc_time_t));

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }


    dwRet = bsp_rtc_init();
    if (0 != dwRet)
    {
        printf("rtc init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

	dwRet = bsp_rtc_write_time((rtc_time_t *)&tTemp, &ucopt);
	if (0 != dwRet)
	{
		printf("rtc test bsp_rtc_write_time error= 0x%08x\r\n",dwRet);
		return dwRet;
	}

	printf("set rtc time: %d-%d-%d,%d,%d:%d:%d ok\r\n",tTime.tm_year,tTime.tm_mon,tTime.tm_mday,tTime.tm_wday,
	                                                      tTime.tm_hour,tTime.tm_min,tTime.tm_sec);

    return 0;
}
unsigned int drvtest_gettime(void)
{
    unsigned int dwRet = 0;
    unsigned char ucopt = 0;
    rtc_time_t tTime;

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_rtc_init();
    if (0 != dwRet)
    {
        printf("rtc init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

	dwRet = bsp_rtc_read_time((rtc_time_t *)&tTime, &ucopt);
    if ((0 != dwRet))
    {
        printf("rtc test bsp_rtc_read_time error= 0x%08x\r\n",dwRet);
        return dwRet;
    }
    else
    {
       printf("get rtc time: %d-%d-%d,%d,%d:%d:%d \r\n",tTime.tm_year,tTime.tm_mon,tTime.tm_mday,tTime.tm_wday,
                                                          tTime.tm_hour,tTime.tm_min,tTime.tm_sec);
    }   
    return 0;
}


