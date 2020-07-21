#include "usp.h"
#if (UHF_PROTOCOL_USE)

void GetCurrUsTime(struct timeval *ptTimeVal)
{
    //struct timeval get_time1;

    if (gettimeofday(ptTimeVal, NULL) != 0)
    {
        //usp_oss_printf(USP_UHF_TNO, USP_OSS_PRINTF_LEVEL_DEBUG, "can not get time\r\n") ;

    }
    else
    {
        //printf("UHF: time: %ld second : %ld us \r\n", ptTimeVal->tv_sec, ptTimeVal->tv_usec) ;
    }
}

/**********************************************************************
* 函数名称：static void uhf_startRcpTimer( void )
* 功能描述：启动定时器。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_startRcpTimer(WORD32 dwMS)
{
    struct itimerval tim_ticks;
    tim_ticks.it_value.tv_sec = (dwMS / 1000); //s
    tim_ticks.it_value.tv_usec = (dwMS % 1000) * 1000; //us
    tim_ticks.it_interval.tv_sec = (dwMS / 1000);
    tim_ticks.it_interval.tv_usec = (dwMS % 1000) * 1000;
    //10; /* 设置it_value为0;或者当计数器计数完毕后，而it_interval为0，这时候计数器就停止工作。 */

    setitimer(ITIMER_REAL, &tim_ticks, 0);
} /* static void uhf_startRcpTimer( void ) */

/**********************************************************************
* 函数名称：static void uhf_stopRcpTimer( void )
* 功能描述：停止定时器。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_stopRcpTimer(void)
{
    struct itimerval tim_ticks;
    tim_ticks.it_value.tv_sec = 0; //s
    tim_ticks.it_value.tv_usec = 0; //us
    tim_ticks.it_interval.tv_sec = 0;
    tim_ticks.it_interval.tv_usec = 0; //10; /* 设置it_value为0;或者当计数器计数完毕后，而it_interval为0，这时候计数器就停止工作。 */

    setitimer(ITIMER_REAL, &tim_ticks, 0);
} /* static void uhf_stopRcpTimer( void ) */

WORD32 CalMsTimeInterval(struct timeval *ptStartTime, struct timeval *ptCurrTime)
{
    WORD32 use_ms_time;
    use_ms_time = (ptCurrTime->tv_sec - ptStartTime->tv_sec) * 1000
                  + ((ptCurrTime->tv_usec - ptStartTime->tv_usec)/1000) ;
    return (use_ms_time);
}


#endif

