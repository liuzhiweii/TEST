#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
/* UHF统计信息  */
typedef struct
{
    WORD32 dwSigIONum;
    WORD32 dwSigINTNum;
    WORD32 dwSigNum;

    WORD32 dwEpcInvnetErrNum;
    WORD32 dwEpcInvnetSignalNum;

    WORD32 dwIsoSignalNum;
    WORD32 dwIsoTagNum;
} T_UhfStatis;

/* Rcp统计信息  */
static T_UhfStatis tRcpStatis;


/**********************************************************************
* 函数名称：static void signal_io_process(int sig)
* 功能描述：SIGIO信号处理函数
* 访问的表：无
* 修改的表：无
* 输入参数：int sig ：信号类型
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
static void signal_io_process(int sig)
{
    tRcpStatis.dwSigIONum++;
}

/**********************************************************************
* 函数名称：static void signal_alarm_process(int sig)
* 功能描述：SIGALRM信号处理函数
* 访问的表：无
* 修改的表：无
* 输入参数：int sig ：信号类型
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
static void signal_alarm_process(int sig)
{
    tRcpStatis.dwSigINTNum++;
    printf("sigalarm happened\r\n");
}
/**********************************************************************
* 函数名称：WORD32 InitSIGALRM(void)
* 功能描述：安装 SIGALRM 信号处理函数
* 输入参数：
* 输出参数：
* 返 回 值：WORD32
                    0：    成功
                 其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
WORD32 InitUhfSIGALRM(void)
{
    struct sigaction act;
    int iRetVal;

    sigemptyset(&act.sa_mask);
    act.sa_handler = signal_alarm_process;
    act.sa_flags = 0;

    /* bind the signal process function */
    iRetVal = sigaction(SIGALRM, &act, 0);

    if (iRetVal != 0)
    {
        perror("UHF: sigaction(SIGALRM) error ");
        exit(1);
    }

    return 0;

} /* WORD32 InitSIGALRM(void) */
#endif

