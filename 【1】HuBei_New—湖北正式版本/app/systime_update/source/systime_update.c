#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "bsp.h"

int main(void)
{
    unsigned int dwRet = 0;
    rtc_time_t tTime;
    char modify_date[64];
    unsigned char ucopt;

    (void)bsp_epld_init();
    dwRet = bsp_rtc_init();
    if (0 != dwRet)
    {
        printf("rtc init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    while(1)
    {
        sleep(60*20);
        
        dwRet = bsp_rtc_read_time((rtc_time_t *)&tTime, &ucopt);
        if ((0 != dwRet))
        {
            printf("rtc bsp_rtc_read_time error= 0x%08x\r\n",dwRet);
            //return dwRet;
        }
        sprintf(modify_date, "date -s \"%02d%02d%02d%02d%04d.%02d\"", \
                tTime.tm_mon, tTime.tm_mday, tTime.tm_hour, tTime.tm_min,
                tTime.tm_year, tTime.tm_sec);
        
        system(modify_date);
    }

    return 0;
}

