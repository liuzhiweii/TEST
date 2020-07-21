/***************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
*
* 文件名称：ufhllrpRule.c
* 文件标识：
* 内容摘要：LLRPRule协议模块
* 其它说明：
* 当前版本：
* 作    者：程亮
* 完成日期：2012.05.17 
**********************************************************************/


/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include "rdppub.h" 
/***********************************************************
 *                     常量定义                            *
***********************************************************/

/***********************************************************
*                 文件内部使用的宏                        *
***********************************************************/

#define EPC_C1G2_BLOCKLOCK       (1)
#define EPC_C1G2_BLOCKLOCK_QUERY  (0)

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/


/***********************************************************
 *                     全局变量                            *
***********************************************************/
T_RdpLlrpDynamicRo g_tRdpLlrpDynamicRoLinkHead[MAX_LINK_NUM];
T_RdpLlrpDynamicAccess g_tRdpLlrpDynamicAccessLinkHead[MAX_LINK_NUM];
extern unsigned char g_aucRdpLlrpSndMsg[RDP_MAX_LEN_MSG];
extern unsigned char g_aucRdpLlrpRcvMsg[RDP_MAX_LEN_MSG];
extern T_RdpLlrpReaderDispatch g_tRdpLlrpReaderDispatch;
extern T_RdpLlrpAcculateReportData g_tRdpLlrpReaderAcculateReport[MAX_LINK_NUM];
extern T_RdpConfig g_tRdpConfig;
extern unsigned char g_ucLocalReportDataBuffer[LLRP_MAX_REPORT_BUFFER];

extern void *pair_socket_rule;
extern void *pair_socket_report;
/***********************************************************
 *                     本地变量                            *
***********************************************************/
LLRP_tSGET_ACCESSSPECS_RESPONSE *ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE = NULL;
LLRP_tSLLRPStatus *ptSLocalAoLLRPStatus = NULL;
LLRP_tSGET_ROSPECS_RESPONSE *ptLocalLLRP_tSGET_ROSPECS_RESPONSE = NULL;
LLRP_tSLLRPStatus *ptSLocalRoLLRPStatus = NULL;

/***********************************************************
 *                     全局函数                            *
***********************************************************/




/***********************************************************
 *                     局部函数                            *
***********************************************************/


/**************************************************************************
* 函数名称：llrp_getReaderuSec
* 功能描述：获得系统时间
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned long long llrp_getReaderuSec()
{
    struct timeval tCurrentTime;
    unsigned long long ldwReportuSec = 0;
    if (gettimeofday(&tCurrentTime, NULL) != 0)
    {
        RdpLlrpDbgPrint("(LLRP)gettimeofday is error\r\n");
    }
    ldwReportuSec = (unsigned)(long long)tCurrentTime.tv_sec;
    ldwReportuSec = ldwReportuSec * 1000000 + tCurrentTime.tv_usec;
    return ldwReportuSec;
}
unsigned int usp_drv_timer_get_counter(unsigned int *dwTime)
{
   return 0;
}
/**************************************************************************
* 函数名称：llrp_getBootCurrMsTime
* 功能描述：获得系统时间
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned long long llrp_getPPC8313BootCurrMsTime()
{
    unsigned int dwRet = 0;
    unsigned int dwTimerCount = 0; /* 当前的计数器值 */
    static unsigned int dwHighTimerCount = 0; /* 计数器值的高32位置 */
    static unsigned int dwPreTimerCount = 0; /* 前一次读取的计数器值 */
    unsigned long long lwCurentTime;
    dwRet = usp_drv_timer_get_counter(&dwTimerCount);
    if (0 != dwRet)
    {
        RdpLlrpDbgPrint("(LLRP): usp_drv_timer_get_counter is  error code %04x\r\n", dwRet);
        RDP_EXCEPT(RDP_LLRP_GETTIME_ERROR, dwRet, 0, 0, RDP_LLRP_RULE_ID);
        return 0;
    }
    /* 若上一次读取的计数器值大于了当前计数器值，
        表明dwTimerCount溢出了  需要dwHighTimerCount加1*/
    if ( dwPreTimerCount > dwTimerCount )
    {
        RdpLlrpDbgPrint("the timer is full over\r\n");
        dwHighTimerCount++;
    }
    lwCurentTime = ((unsigned long long)dwHighTimerCount) * 0xffffffff + (unsigned long long)dwTimerCount;
    /* 将上一次获取的计数值存储起来 */
    dwPreTimerCount = dwTimerCount;
    RdpLlrpDbgPrint("(LLRP) llrp_get8313UsTime return time %lld\r\n", lwCurentTime);
    return lwCurentTime / 1000;
}
/**************************************************************************
* 函数名称：llrp_getBootCurrMsTime
* 功能描述：获得系统时间
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned long long llrp_getPPC82xxBootCurrMsTime()
{
    unsigned int dwRet = 0;
    unsigned int dwTimerCount = 0; /* 当前的计数器值 */
    static unsigned int dwHighTimerCount = 0; /* 计数器值的高32位置 */
    static unsigned int dwPreTimerCount = 0; /* 前一次读取的计数器值 */
    unsigned long long lwCurentTime;
    dwRet = usp_drv_timer_get_counter(&dwTimerCount);
    if (0 != dwRet)
    {
        RdpLlrpDbgPrint("(LLRP): usp_drv_timer_get_counter is  error code %04x\r\n", dwRet);
        RDP_EXCEPT(RDP_LLRP_GETTIME_ERROR, dwRet, 0, 0, RDP_LLRP_RULE_ID);
        return 0;
    }
    dwTimerCount = 0x7FFFFFFF - dwTimerCount;
    /* 若上一次读取的计数器值大于了当前计数器值，
        表明dwTimerCount溢出了  需要dwHighTimerCount加1*/
    if ( dwPreTimerCount > dwTimerCount )
    {
        RdpLlrpDbgPrint("the timer is full over\r\n");
        dwHighTimerCount++;
    }
    lwCurentTime = ( ((unsigned long long)dwHighTimerCount) * 0x7fffffff + (unsigned long long)dwTimerCount) / 13;
    /* 将上一次获取的计数值存储起来 */
    dwPreTimerCount = dwTimerCount;
    //RdpLlrpDbgPrint("(LLRP) llrp_getBootCurrUsTime return time %lld\r\n", ldwCurentTime);
    return lwCurentTime / 1000;
}
/**************************************************************************
* 函数名称：llrp_dealBootTimerPollingTimer
* 功能描述：系统时间更新的定时器的处理方法
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_dealBootTimerPollingTimer(T_Msg *ptRcvMsg)
{
    GET_READER_BOOT_TIME_MS();
    LLRP_START_TIMER(TBootTimerPollingIntervalTimer, LLRP_PollingInterval);
}
/**************************************************************************
* 函数名称：llrp_sendRuleRspMsg
* 功能描述：发送规则消息的应答
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg,
                             接收的消息头
                             LLRP_tEStatusCode etLLRP_tEStatusCode, 
                             返回的状态
                             unsigned int dwSndMsgID,
                             发送的消息
                             unsigned int dwMsgSeqID
                             同步消息序列
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned int llrp_sendRuleRspMsg(T_Msg *ptRcvMsg, LLRP_tEStatusCode etLLRP_tEStatusCode, unsigned int dwSndMsgID, unsigned int dwMsgSeqID, unsigned int dwRuleID)
{
    T_RdpLlrpRuleRsp *ptRdpLlrpRuleRsp = NULL;
    unsigned int dwRet = 0;
    T_Msg *ptSndMsg = NULL;
    LLRP_tSErrorDetails pError;
    LLRP_tSADD_ROSPEC_RESPONSE *ptLLRP_tSADD_ROSPEC_RESPONSE = NULL;
    LLRP_tSENABLE_ROSPEC_RESPONSE *ptLLRP_tSENABLE_ROSPEC_RESPONSE = NULL;
    LLRP_tSDISABLE_ROSPEC_RESPONSE *ptLLRP_tSDISABLE_ROSPEC_RESPONSE = NULL;
    LLRP_tSADD_ACCESSSPEC_RESPONSE *ptLLRP_tSADD_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSSTOP_ROSPEC_RESPONSE *ptLLRP_tSSTOP_ROSPEC_RESPONSE = NULL;
    LLRP_tSSTART_ROSPEC_RESPONSE *ptLLRP_tSSTART_ROSPEC_RESPONSE = NULL;
    LLRP_tSDELETE_ROSPEC_RESPONSE *ptLLRP_tSDELETE_ROSPEC_RESPONSE = NULL;
    LLRP_tSDISABLE_ACCESSSPEC_RESPONSE *ptLLRP_tSDISABLE_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSENABLE_ACCESSSPEC_RESPONSE *ptLLRP_tSENABLE_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSDELETE_ACCESSSPEC_RESPONSE *ptLLRP_tSDELETE_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSERROR_MESSAGE *ptSERROR_MESSAG = NULL;
    /*根据不同的消息构造 返回结构*/
    switch (dwSndMsgID)
    {
    case EV_ADD_ROSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_ADD_ROSPEC_RESPONSE\r\n");
        ptLLRP_tSADD_ROSPEC_RESPONSE = LLRP_ADD_ROSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSADD_ROSPEC_RESPONSE;
        break;
    case EV_ENABLE_ROSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_ENABLE_ROSPEC_RESPONSE\r\n");
        ptLLRP_tSENABLE_ROSPEC_RESPONSE = LLRP_ENABLE_ROSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSENABLE_ROSPEC_RESPONSE;
        break;
    case EV_STOP_ROSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_STOP_ROSPEC_RESPONSE\r\n");
        ptLLRP_tSSTOP_ROSPEC_RESPONSE = LLRP_STOP_ROSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSSTOP_ROSPEC_RESPONSE;
        break;
    case EV_START_ROSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_START_ROSPEC_RESPONSE\r\n");
        ptLLRP_tSSTART_ROSPEC_RESPONSE = LLRP_START_ROSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSSTART_ROSPEC_RESPONSE;
        break;
    case EV_DISABLE_ROSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_DISABLE_ROSPEC_RESPONSE\r\n");
        ptLLRP_tSDISABLE_ROSPEC_RESPONSE = LLRP_DISABLE_ROSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDISABLE_ROSPEC_RESPONSE;
        break;
    case EV_DELETE_ROSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_DELETE_ROSPEC_RESPONSE\r\n");
        ptLLRP_tSDELETE_ROSPEC_RESPONSE = LLRP_DELETE_ROSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDELETE_ROSPEC_RESPONSE;
        break;
    case EV_ADD_ACCESSSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_ADD_ACCESSSPEC_RESPONSE\r\n");
        ptLLRP_tSADD_ACCESSSPEC_RESPONSE = LLRP_ADD_ACCESSSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSADD_ACCESSSPEC_RESPONSE;
        break;
    case EV_ENABLE_ACCESSSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_ENABLE_ACCESSSPEC_RESPONSE\r\n");
        ptLLRP_tSENABLE_ACCESSSPEC_RESPONSE = LLRP_ENABLE_ACCESSSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSENABLE_ACCESSSPEC_RESPONSE;
        break;

    case EV_DISABLE_ACCESSSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_DISABLE_ACCESSSPEC_RESPONSE\r\n");
        ptLLRP_tSDISABLE_ACCESSSPEC_RESPONSE = LLRP_DISABLE_ACCESSSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDISABLE_ACCESSSPEC_RESPONSE;
        break;

    case EV_DELETE_ACCESSSPEC_RESPONSE:
        RdpLlrpDbgPrint("(LLRP)EV_DELETE_ACCESSSPEC_RESPONSE\r\n");
        ptLLRP_tSDELETE_ACCESSSPEC_RESPONSE = LLRP_DELETE_ACCESSSPEC_RESPONSE_construct();
        ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDELETE_ACCESSSPEC_RESPONSE;
        break;
    default:
        RdpLlrpDbgPrint("(LLRP)the MessageID is not supported\r\n");
        break;
    }
    /*构造结构*/
    if (ptSERROR_MESSAG != NULL)
    {
        LLRP_tSLLRPStatus *ptSLLRPStatus = LLRP_LLRPStatus_construct();
        ptSLLRPStatus->eStatusCode = etLLRP_tEStatusCode;
        LLRP_ERROR_MESSAGE_setLLRPStatus(ptSERROR_MESSAG, ptSLLRPStatus);
        ptSERROR_MESSAG->pLLRPStatus = ptSLLRPStatus;
        ptSERROR_MESSAG->hdr.MessageID = dwMsgSeqID;
        ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
        ptSndMsg->ucLinkIndex = ptRcvMsg->ucLinkIndex;
        ptSndMsg->ucLinkType = ptRcvMsg->ucLinkType;
        ptSndMsg->mtype = 1;
        /*向外发送*/
        ptSndMsg->wMsgID = dwSndMsgID;
        /*这里wSenderTno和wReceiverTno标识路由的源和目的
        wSrcTno和wDstTno 表示上下周转的节点*/
        ptSndMsg->wSenderTno = USP_RDP_LLRP_TNO;
        ptSndMsg->wReceiverTno = ptRcvMsg->wSenderTno;
        ptSndMsg->wSrcTno = ptRcvMsg->wDstTno;
        ptSndMsg->wDstTno = ptRcvMsg->wSrcTno;
        /*只传地址所以这里是指针的长度*/
        ptSndMsg->wMsgLen = sizeof(T_RdpLlrpRuleRsp);
        ptRdpLlrpRuleRsp = (T_RdpLlrpRuleRsp *)(ptSndMsg + 1);
        ptRdpLlrpRuleRsp->dwRuleID = dwRuleID;
        ptRdpLlrpRuleRsp->ptRuleRspAddr = ptSERROR_MESSAG;
        RdpLlrpDbgPrint("(LLRP)ptSERROR_MESSAG addr =0x%4x,RULE id=%d,dwMsgSeqID=%d\r\n" ,
                        ptRdpLlrpRuleRsp->ptRuleRspAddr, ptRdpLlrpRuleRsp->dwRuleID, dwMsgSeqID);
        dwRet = RDP_SEND_MSG(pair_socket_rule, ptSndMsg);
        if (dwRet < 0)
        {
            RdpLlrpDbgPrint("(LLRP)msgsend error\r\n");
            /*写入异常*/
            RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, dwRet, 0, 0, RDP_LLRP_RULE_ID);
            return dwRet;
        }
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)the MessageID is not supported\r\n");
    }
    return dwRet;
}
/**************************************************************************
* 函数名称：llrp_doDefaultforAIStopTrigger
* 功能描述：AI的stopTrigger的触发条件
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_doDefaultforAIStopTrigger(void *ptPara)
{}
/**************************************************************************
* 函数名称：llrp_judgeAIExecuteTimeforAIStopTrigger
* 功能描述：AI的stopTrigger的判断发生
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_judgeAIExecuteTimeforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    unsigned long long lwCurTime = 0;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    lwCurTime = GET_READER_BOOT_TIME_MS();
    RdpLlrpDbgPrint("AI  run duration time judge\r\n");
    RdpLlrpDbgPrint("(LLRP) CurTime:%lld,AIStartTime:%lld,dwDuration=%d\r\n",
                    lwCurTime, ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime, ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwDuration);
    if ((lwCurTime - ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime)
            > ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwDuration)
    {
        RdpLlrpDbgPrint("(LLRP)AIStopTriggerhappend  Duration timeout happened\r\n");
        ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
    }
}
/**************************************************************************
* 函数名称：llrp_judgeAITimeoutforAIStopTrigger
* 功能描述：AI的stopTrigger的的超时时间判断
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
                             
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_judgeAITimeoutforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    unsigned long long lwCurTime = GET_READER_BOOT_TIME_MS();
    RdpLlrpDbgPrint("(LLRP)judgeAITimeoutforAIStopTrigger\r\n");
    RdpLlrpDbgPrint("(LLRP) CurTime:%lld,AIStartTime:%lld,dwDuration=%d\r\n",
                    lwCurTime, ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime, ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut);
    if (ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut == 0)
    {
        RdpLlrpDbgPrint("(LLRP)dwTimeOut is 0\r\n");
        return ;
    }
    if ((lwCurTime - ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime)
            > ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut)
    {
        RdpLlrpDbgPrint("(LLRP)AIStopTrigger timeout happened\r\n");
        ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
    }
}

/**************************************************************************
* 函数名称：llrp_judgeGpiTimeoutforAIStopTrigger
* 功能描述：AI的GpistopTrigger的超时时间判断
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
                             
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_judgeGpiTimeoutforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    RdpLlrpDbgPrint("(LLRP)judgeAITimeoutforAIStopTrigger\r\n");
    unsigned long long lwCurTime = GET_READER_BOOT_TIME_MS();
    RdpLlrpDbgPrint("(LLRP) CurTime:%lld,AIStartTime:%lld,dwTimeout=%d\r\n",
                    lwCurTime, ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime, ptAIStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwTimeout);

    if (ptAIStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwTimeout == 0)
    {
        RdpLlrpDbgPrint("(LLRP)dwTimeOut is 0\r\n");
        return ;
    }
    if ((lwCurTime - ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime)
            > ptAIStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwTimeout)
    {
        RdpLlrpDbgPrint("(LLRP)AIStopTrigger timeout happened\r\n");
        ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
    }
}
/**************************************************************************
* 函数名称：llrp_doDefaultJudgeHappenforAIStopTrigger
* 功能描述：AI的stopTrigger的判断发生
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static unsigned int llrp_doDefaultJudgeHappenforAIStopTrigger(void *ptPara)
{
    return FALSE;
}
/**************************************************************************
* 函数名称：llrp_AccmulateTagNumforAIStopTrigger
* 功能描述：AI的标签数积累
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_accmulateTagNumforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAITagNum++;
    RdpLlrpDbgPrint("(LLRP)the AI inv tags is %d\r\n", ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAITagNum);
    if ( ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfTags == 0)
    {
        return ;
    }
    if (ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAITagNum > ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfTags)
    {
        RdpLlrpDbgPrint("(LLRP)the Ai inv tags is larger than %d NumberOfTags\r\n", ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfTags);
        ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
    }
}
/**************************************************************************
* 函数名称：llrp_calculatetmsforAIStopTrigger
* 功能描述：AI的每个标签的相隔时间
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_calculatetmsforAIStopTrigger(void *ptPara)
{
    unsigned long long lwusec = 0;
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    lwusec = GET_READER_BOOT_TIME_MS();
    if (ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime == 0)
    {
        ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime = lwusec;
        RdpLlrpDbgPrint("(LLRP)the tag inv time is %lld\r\n", ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime);
    }
    else
    {
        if ((lwusec - ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime) > ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTms)
        {
            RdpLlrpDbgPrint("(LLRP)the tag inv interval  is larger than %d Tms\r\n", ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTms);
            ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
        }
        else
        {
            ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime = lwusec;
            RdpLlrpDbgPrint("(LLRP)the tag inv time is %lld\r\n", ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime);
        }
    }
}
/**************************************************************************
* 函数名称：llrp_accmulateAIExecuteTimeforAIStopTrigger
* 功能描述：AI执行的次数增加
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_accmulateAIExecuteTimeforAIStopTrigger(void *ptPara)
{
    unsigned long long lwusec = 0;
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAIExecuteTimes++;
    RdpLlrpDbgPrint("(LLRP)this Ai  CurAIExecuteTimes :%d,wNumberOfAttempts:%d\r\n",
                    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAIExecuteTimes, ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfAttempts);
    if (ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfAttempts == 0)
    {
        return ;
    }
    if (ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAIExecuteTimes >= ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfAttempts)
    {
        ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
    }
}
/**************************************************************************
* 函数名称：llrp_JudgeHappenforAIStopTrigger
* 功能描述：AI的stopTrigger是否发生
* 访问的表：无
* 修改的表：无
* 输入参数：T_GPIOEventReport *ptGPIOEventReport
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static unsigned int llrp_JudgeHappenforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    RdpLlrpDbgPrint("(LLRP)JudgeHappenforAIStopTrigger bAIStopTriggerStatus: %d\r\n",
                    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus);
    return (unsigned int)ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus;
}

/**************************************************************************
* 函数名称：llrp_doDefaultforAIStopTrigger
* 功能描述：AI的stopTrigger的触发条件
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             T_RdpLlrpAIStopTrigger  AIStopTrigger的值
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_dealGpiforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = TRUE;
    RdpLlrpDbgPrint("(LLRP)Ai Gpi Trigger happen\r\n");
}
/**************************************************************************
* 函数名称：llrp_initforAIStopTrigger
* 功能描述：AI的stopTrigger在AI开始时应该设置的参数
* 访问的表：无
* 修改的表：无
* 输入参数：T_GPIOEventReport *ptGPIOEventReport
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
static void llrp_initforAIStopTrigger(void *ptPara)
{
    T_RdpLlrpAIStopTrigger *ptAIStopTrigger = NULL;
    ptAIStopTrigger = (T_RdpLlrpAIStopTrigger *)ptPara;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime = GET_READER_BOOT_TIME_MS();
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.bAIStopTriggerStatus = FALSE;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwLastTagSeenTime = 0;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAIExecuteTimes = 0;
    ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.wAITagNum = 0;
    RdpLlrpDbgPrint("(LLRP) this AI startTime ms:%lld\r\n", ptAIStopTrigger->tRdpLlrpAIParamForStopTrigger.lwAIStartTime);
}
/**************************************************************************
* 函数名称：llrp_transferToAIStopTriggerPara
* 功能描述：转换AI的stopTrigger到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSAISpecStopTrigger *ptTempLLRP_tSAISpecStopTrigger,
                             T_RdpLlrpAIStopTrigger *ptTempAISpecStopTrigger
* 输出参数：无
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferToAIStopTriggerPara(LLRP_tSAISpecStopTrigger *ptTempLLRP_tSAISpecStopTrigger,
                                      T_RdpLlrpAIStopTrigger *ptTempAISpecStopTrigger)
{
    switch (ptTempLLRP_tSAISpecStopTrigger->eAISpecStopTriggerType)
    {
    case LLRP_AISpecStopTriggerType_Null:
        RdpLlrpDbgPrint("(LLRP)LLRP_AISpecStopTriggerType_Null\r\n");
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateForAIStopTrigger = (usp_rdp_llrp_AccmulateForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger = (usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_endAPForAIStopTrigger = (usp_rdp_llrp_endAPForAIStopTrigger)llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_initAIForAIStopTrigger = (usp_rdp_llrp_initAIForAIStopTrigger)llrp_initforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_judgeHappenForAIStopTrigger = (usp_rdp_llrp_judgeHappenForAIStopTrigger)llrp_doDefaultJudgeHappenforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger = (usp_rdp_llrp_ExternalTriggerForAIStopTrigger)llrp_doDefaultforAIStopTrigger;

        break;
    case LLRP_AISpecStopTriggerType_GPI_With_Timeout:
        RdpLlrpDbgPrint("(LLRP)LLRP_AISpecStopTriggerType_GPI_With_Timeout\r\n");
        ptTempAISpecStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwTimeout
        = ptTempLLRP_tSAISpecStopTrigger->pGPITriggerValue->Timeout;
        ptTempAISpecStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwGPIPortNum
        = ptTempLLRP_tSAISpecStopTrigger->pGPITriggerValue->GPIPortNum;
        ptTempAISpecStopTrigger->tRdpLlrpAIGpiOfStopTrigger.ucGPIEvent
        = ptTempLLRP_tSAISpecStopTrigger->pGPITriggerValue->GPIEvent;
        RdpLlrpDbgPrint("(LLRP)TimeOut:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwTimeout);
        RdpLlrpDbgPrint("(LLRP)GPIPortNum:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIGpiOfStopTrigger.dwGPIPortNum);
        RdpLlrpDbgPrint("(LLRP)GPIEvent:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIGpiOfStopTrigger.ucGPIEvent);
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateForAIStopTrigger = (usp_rdp_llrp_AccmulateForAIStopTrigger)llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger = (usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger)llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_endAPForAIStopTrigger = (usp_rdp_llrp_endAPForAIStopTrigger)(usp_rdp_llrp_endAPForAIStopTrigger)llrp_judgeGpiTimeoutforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_initAIForAIStopTrigger = (usp_rdp_llrp_initAIForAIStopTrigger)llrp_initforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_judgeHappenForAIStopTrigger = (usp_rdp_llrp_judgeHappenForAIStopTrigger)llrp_JudgeHappenforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger = (usp_rdp_llrp_ExternalTriggerForAIStopTrigger)llrp_dealGpiforAIStopTrigger;
        break;
    case LLRP_AISpecStopTriggerType_Duration:
        RdpLlrpDbgPrint("(LLRP)LLRP_AISpecStopTriggerType_Duration\r\n");
        ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwDuration = ptTempLLRP_tSAISpecStopTrigger->DurationTrigger;
        RdpLlrpDbgPrint("(LLRP)Duration:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwDuration);
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateForAIStopTrigger = (usp_rdp_llrp_AccmulateForAIStopTrigger)llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger = (usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger)llrp_doDefaultforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_endAPForAIStopTrigger = (usp_rdp_llrp_endAPForAIStopTrigger)llrp_judgeAIExecuteTimeforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_initAIForAIStopTrigger = (usp_rdp_llrp_initAIForAIStopTrigger) llrp_initforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_judgeHappenForAIStopTrigger = (usp_rdp_llrp_judgeHappenForAIStopTrigger) llrp_JudgeHappenforAIStopTrigger;
        ptTempAISpecStopTrigger->pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger = (usp_rdp_llrp_ExternalTriggerForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
        break;
    case LLRP_AISpecStopTriggerType_Tag_Observation:
        RdpLlrpDbgPrint("(LLRP)LLRP_AISpecStopTriggerType_Tag_Observation\r\n");
        switch (ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->eTriggerType)
        {
        case LLRP_TagObservationTriggerType_Upon_Seeing_N_Tags_Or_Timeout:
            RdpLlrpDbgPrint("(LLRP)LLRP_TagObservationTriggerType_Upon_Seeing_N_Tags_Or_Timeout\r\n");
            ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfTags
            = ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->NumberOfTags;
            ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut
            = ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->Timeout;
            RdpLlrpDbgPrint("(LLRP)wNumberOfTags:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfTags);
            RdpLlrpDbgPrint("(LLRP)dwTimeOut:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut);
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateForAIStopTrigger = (usp_rdp_llrp_AccmulateForAIStopTrigger)llrp_accmulateTagNumforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger = (usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_endAPForAIStopTrigger = (usp_rdp_llrp_endAPForAIStopTrigger)llrp_judgeAITimeoutforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_initAIForAIStopTrigger = (usp_rdp_llrp_initAIForAIStopTrigger) llrp_initforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_judgeHappenForAIStopTrigger = (usp_rdp_llrp_judgeHappenForAIStopTrigger) llrp_JudgeHappenforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger = (usp_rdp_llrp_ExternalTriggerForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
            break;
        case LLRP_TagObservationTriggerType_Upon_Seeing_No_More_New_Tags_For_Tms_Or_Timeout:
            RdpLlrpDbgPrint("(LLRP)LLRP_TagObservationTriggerType_Upon_Seeing_No_More_New_Tags_For_Tms_Or_Timeout\r\n");
            ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTms
            = ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->T;
            ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut
            = ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->Timeout;
            RdpLlrpDbgPrint("(LLRP)dwTms:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTms);
            RdpLlrpDbgPrint("(LLRP)dwTimeOut:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut);
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateForAIStopTrigger = (usp_rdp_llrp_AccmulateForAIStopTrigger)llrp_calculatetmsforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger = (usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_endAPForAIStopTrigger = (usp_rdp_llrp_endAPForAIStopTrigger)llrp_judgeAITimeoutforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_initAIForAIStopTrigger = (usp_rdp_llrp_initAIForAIStopTrigger) llrp_initforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_judgeHappenForAIStopTrigger = (usp_rdp_llrp_judgeHappenForAIStopTrigger) llrp_JudgeHappenforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger = (usp_rdp_llrp_ExternalTriggerForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
            break;
        case LLRP_TagObservationTriggerType_N_Attempts_To_See_All_Tags_In_FOV_Or_Timeout:
            RdpLlrpDbgPrint("(LLRP)LLRP_TagObservationTriggerType_N_Attempts_To_See_All_Tags_In_FOV_Or_Timeout\r\n");
            ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfAttempts
            = ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->NumberOfAttempts;
            ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut
            = ptTempLLRP_tSAISpecStopTrigger->pTagObservationTrigger->Timeout;
            RdpLlrpDbgPrint("(LLRP)wNumberOfAttempts:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.wNumberOfAttempts);
            RdpLlrpDbgPrint("(LLRP)dwTimeOut:%d\r\n", ptTempAISpecStopTrigger->tRdpLlrpAIParamForStopTrigger.dwTimeOut);
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateForAIStopTrigger = (usp_rdp_llrp_AccmulateForAIStopTrigger)llrp_doDefaultforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger = (usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger) llrp_accmulateAIExecuteTimeforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_endAPForAIStopTrigger = (usp_rdp_llrp_endAPForAIStopTrigger)llrp_judgeAITimeoutforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_initAIForAIStopTrigger = (usp_rdp_llrp_initAIForAIStopTrigger) llrp_initforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_judgeHappenForAIStopTrigger = (usp_rdp_llrp_judgeHappenForAIStopTrigger) llrp_JudgeHappenforAIStopTrigger;
            ptTempAISpecStopTrigger->pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger = (usp_rdp_llrp_ExternalTriggerForAIStopTrigger) llrp_doDefaultforAIStopTrigger;
            break;
        default:
            RdpLlrpDbgPrint("(LLRP)LLRP_AISpecStopTriggerType_Tag_Observation Error\r\n");
            break;
        }
        break;
    default:
        RdpLlrpDbgPrint("(LLRP)AISpecStopTriggerPa rameter Error\r\n");
        break;
    }
}
/**************************************************************************
* 函数名称：llrp_transferToAntCfgPara
* 功能描述：转换Ant的天线配置到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpProtocolInvSet *ptProtocolInv,
                             LLRP_tSAntennaConfiguration *ptTempLLRP_tSAntennaConfiguration
* 输出参数：无
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferToAntCfgPara(T_RdpLlrpProtocolInvSet *ptProtocolInv,
                               LLRP_tSAntennaConfiguration *ptTempLLRP_tSAntennaConfiguration)
{
    unsigned short int wFilterNum = 0;
    unsigned int dwTagIndex = 0;
    unsigned int dwTestID = 0;
    LLRP_tSC1G2InventoryCommand *ptTempLLRP_tSC1G2InventoryCommand = NULL;
    LLRP_tSC1G2Filter *ptTempLLRP_tSC1G2Filter = NULL;
    LLRP_tSISO6BInventoryCommand *ptTempLLRP_tSISO6BInventoryCommand = NULL;
    LLRP_tSISO6BFilter *ptTempLLRP_tSISO6BFilter = NULL;
    LLRP_tSParameter *ptTempLLRP_tSParameter = NULL;
    T_USPRdpLlrpC1G2InventoryCommand *ptTempC1G2InventoryCommand = NULL;
    T_USPRdpLlrpISO6BInventoryCommand *ptTempISO6BInventoryCommand = NULL;
    T_USPRdpLlrpC1G2FilterList *ptTempC1G2FilterList = NULL;
    T_USPRdpLlrpISO6BFilterList *ptTempISO6BFilterList = NULL;
    LLRP_tSGBInventoryCommand *ptTempLLRP_tSGBInventoryCommand = NULL;
    LLRP_tSGBFilter *ptTempLLRP_tSGBFilter = NULL;
    T_USPRdpLlrpGBInventoryCommand *ptTempGBInventoryCommand = NULL;
    T_USPRdpLlrpGBFilterList *ptTempGBFilterList = NULL;
    ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.ucAntID
    = ptTempLLRP_tSAntennaConfiguration->AntennaID;
    RdpLlrpDbgPrint("(LLRP)Antenna %d has  find AntennaConfig\r\n", ptTempLLRP_tSAntennaConfiguration->AntennaID);

    if (ptTempLLRP_tSAntennaConfiguration->pRFReceiver == NULL)
    {
        ptProtocolInv->tRdpLlrpAntConfigCtrl.bRFT_RFReceiverCtrl = TRUE;
        RdpLlrpDbgPrint("(LLRP)There is  no pRFReceiver\r\n");
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)There is   pRFReceiver\r\n");
    }

    /*RFTransmitter*/
    if (ptTempLLRP_tSAntennaConfiguration->pRFTransmitter == NULL)
    {
        ptProtocolInv->tRdpLlrpAntConfigCtrl.bRFTransmitterCtrl = TRUE;
        RdpLlrpDbgPrint("(LLRP)There is  no pRFTransmitter\r\n");
    }
    else
    {
        ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpRFTransmitterSettings.wTransmitPower
        = ptTempLLRP_tSAntennaConfiguration->pRFTransmitter->TransmitPower;
        ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpRFTransmitterSettings.wChannelIndex
        = ptTempLLRP_tSAntennaConfiguration->pRFTransmitter->ChannelIndex;
        ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpRFTransmitterSettings.wHopTableID
        = ptTempLLRP_tSAntennaConfiguration->pRFTransmitter->HopTableID;
        RdpLlrpDbgPrint("(LLRP)There is  pRFTransmitter\r\n");
        RdpLlrpDbgPrint("(LLRP)TransmitPower %d\r\n" , ptTempLLRP_tSAntennaConfiguration->pRFTransmitter->TransmitPower);
        RdpLlrpDbgPrint("(LLRP)ChannelIndex %d\r\n", ptTempLLRP_tSAntennaConfiguration->pRFTransmitter->ChannelIndex);
        RdpLlrpDbgPrint("(LLRP)HopTableID %d\r\n" , ptTempLLRP_tSAntennaConfiguration->pRFTransmitter->HopTableID);
    }

   RdpLlrpDbgPrint("(LLRP)ptProtocolInv->eProtocolID %d\r\n" , ptProtocolInv->eProtocolID);
    /*协议 和ptProtocolInveProtocolID 相对应的协议参数*/
    if (ptTempLLRP_tSAntennaConfiguration->listAirProtocolInventoryCommandSettings == NULL
            && ptProtocolInv->eProtocolID == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_EPCGlobalClass1Gen2 useing DefaultValue\r\n");
        ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpC1G2InvCtrl.bIsDefaultCfgFlag = TRUE;
    }
    else if (ptTempLLRP_tSAntennaConfiguration->listAirProtocolInventoryCommandSettings == NULL \
             && ptProtocolInv->eProtocolID == LLRP_AirProtocols_ISO18000_6B)
    {
        RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_ISO18000_6B useing DefaultValue\r\n");
        ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bIsDefaultCfgFlag = TRUE;
    }
   else if (ptTempLLRP_tSAntennaConfiguration->listAirProtocolInventoryCommandSettings == NULL \
             && ptProtocolInv->eProtocolID == LLRP_AirProtocols_GB)
    {
        RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_GB useing DefaultValue\r\n");
        ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpGBInvCtrl.bIsDefaultCfgFlag = TRUE;
    }
    else
    {
        /*这里 只有EPC 还需要添加18000-B的协议*/
        if ( ptProtocolInv->eProtocolID == LLRP_AirProtocols_EPCGlobalClass1Gen2)
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_EPCGlobalClass1Gen2  not useing DefaultValue\r\n");
            ptTempLLRP_tSParameter = ptTempLLRP_tSAntennaConfiguration->listAirProtocolInventoryCommandSettings;

            for (;ptTempLLRP_tSParameter != NULL && ptTempLLRP_tSParameter->elementHdr.pType->TypeNum != LLRP_C1G2InventoryCommand;
                    ptTempLLRP_tSParameter = ptTempLLRP_tSParameter->pNextSubParameter)
            {
                ;
            }
            if (ptTempLLRP_tSParameter == NULL)
            {
                ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpC1G2InvCtrl.bIsDefaultCfgFlag = TRUE;
            }
            /*EPC 协议 处理*/
            else
            {
                /*取指针方便操作EPC*/
                RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_EPCGlobalClass1Gen2  is find\r\n");
                ptTempC1G2InventoryCommand
                = &ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand;
                ptTempLLRP_tSC1G2InventoryCommand = (LLRP_tSC1G2InventoryCommand *)ptTempLLRP_tSParameter;

                /*赋值wTagInventoryStateAware*/
                ptTempC1G2InventoryCommand->wTagInventoryStateAware
                = ptTempLLRP_tSC1G2InventoryCommand->TagInventoryStateAware ;

                /*赋值filterlist*/
                if (ptTempLLRP_tSC1G2InventoryCommand->listC1G2Filter == NULL)

                {
                    RdpLlrpDbgPrint("(LLRP)ptTempLLRP_tSC1G2InventoryCommand->listC1G2Filter using DefaultValue\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpC1G2InvCtrl.bC1G2Filterctrl = TRUE;
                }
                else
                {
                    /*取Filter指针循环赋值*/
                    RdpLlrpDbgPrint("(LLRP)ptTempLLRP_tSC1G2InventoryCommand->listC1G2Filter not using DefaultValue\r\n");
                    ptTempC1G2FilterList = &ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter;
                    ptTempLLRP_tSC1G2Filter = ptTempLLRP_tSC1G2InventoryCommand->listC1G2Filter;

                    for (wFilterNum = 0;
                            ptTempLLRP_tSC1G2Filter;
                            ptTempLLRP_tSC1G2Filter = (LLRP_tSC1G2Filter *)ptTempLLRP_tSC1G2Filter->hdr.pNextSubParameter, wFilterNum++)
                    {
                        ptTempC1G2FilterList->wFilterNum++;
                        /*截断参数赋值*/
                        ptTempC1G2FilterList->atUSPRdpLlrpC1G2Filter[wFilterNum].eC1G2TruncateAction = ptTempLLRP_tSC1G2Filter->eT;
                        /*unwareFillter赋值*/
                        if (ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryStateUnawareFilterAction != NULL)
                        {
                            ptTempC1G2FilterList->atUSPRdpLlrpC1G2Filter[wFilterNum].tUSPRdpLlrpC1G2TagInventoryStateUnawareFilterAction.eC1G2StateUnawareAction
                            = ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryStateUnawareFilterAction->eAction;
                        }
                        else
                        {
                            ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl \
                            .tRdpLlrpC1G2InvCtrl.tRdpLlrpC12FilterCtrl.bInventoryStateUnawareFilterActionCtrl[wFilterNum] = TRUE;
                        }

                        RdpLlrpDbgPrint("(LLRP)mask MB:%d\r\n" , ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->MB);
                        RdpLlrpDbgPrint("(LLRP)Pointer:%d\r\n" , ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->Pointer);
                        RdpLlrpDbgPrint("(LLRP)TagMask Bits:%d\r\n" , ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->TagMask.nBit);
                        /*掩码清点赋值*/
                        ptTempC1G2FilterList->atUSPRdpLlrpC1G2Filter[wFilterNum].tUSPRdpLlrpEPCTargetTagMask.wMemBank
                        = ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->MB;
                        ptTempC1G2FilterList->atUSPRdpLlrpC1G2Filter[wFilterNum].tUSPRdpLlrpEPCTargetTagMask.wMaskBitPointer
                        = ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->Pointer;
                        ptTempC1G2FilterList->atUSPRdpLlrpC1G2Filter[wFilterNum].tUSPRdpLlrpEPCTargetTagMask.wMaskLength
                        = ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->TagMask.nBit;
                        RdpLlrpDbgPrint("(LLRP)Epc inv mask:");
                        for (dwTagIndex = 0;
                                dwTagIndex < BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->TagMask.nBit);
                                dwTagIndex++)
                        {
                            ptTempC1G2FilterList->atUSPRdpLlrpC1G2Filter[wFilterNum].tUSPRdpLlrpEPCTargetTagMask.ucMaskData[dwTagIndex]
                            = ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->TagMask.pValue[dwTagIndex];
                            RdpLlrpDbgPrint("0x%2x ", ptTempLLRP_tSC1G2Filter->pC1G2TagInventoryMask->TagMask.pValue[dwTagIndex]);
                        }
                        RdpLlrpDbgPrint("\r\n");
                    }
                }

                /*赋值pC1G2RFControl*/
                if (ptTempLLRP_tSC1G2InventoryCommand->pC1G2RFControl == NULL)
                {
                    RdpLlrpDbgPrint("(LLRP)RFControl use default value\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpC1G2InvCtrl.bC1G2RFCtrl = TRUE;
                }
                else
                {
                    ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2RFControl.wModeIndex
                    = ptTempLLRP_tSC1G2InventoryCommand->pC1G2RFControl->ModeIndex;
                    ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2RFControl.wTari
                    = ptTempLLRP_tSC1G2InventoryCommand->pC1G2RFControl->Tari;
                    RdpLlrpDbgPrint("(LLRP)ModeIndex:%d \r\n", ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2RFControl.wModeIndex);
                    RdpLlrpDbgPrint("(LLRP)Tari:%d\r\n", ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2RFControl.wTari);
                }
                /*赋值pC1G2SingulationControl*/
                if (ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl == NULL)
                {
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpC1G2InvCtrl.bC1G2SingulationCtrl = TRUE;
                    RdpLlrpDbgPrint("(LLRP)Epc C1G2Singulation use default value\r\n");
                }
                else
                {
                    ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2SingulationControl.ucSession
                    = ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl->Session;
                    ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2SingulationControl.wTagPopulation
                    = ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl->TagPopulation;
                    ptTempC1G2InventoryCommand->tUSPRdpLlrpC1G2SingulationControl.dwTagTransitTime
                    = ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl->TagTransitTime;
                    RdpLlrpDbgPrint("(LLRP)Session %d \r\n", ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl->Session);
                    RdpLlrpDbgPrint("(LLRP)TagPopulation %d\r\n", ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl->TagPopulation);
                    RdpLlrpDbgPrint("(LLRP)TagTransitTime %d\r\n", ptTempLLRP_tSC1G2InventoryCommand->pC1G2SingulationControl->TagTransitTime);
                }
            }
        }
        else if (ptProtocolInv->eProtocolID == LLRP_AirProtocols_ISO18000_6B)
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_AirProtocols_ISO18000_6B  is find\r\n");
            ptTempLLRP_tSParameter = ptTempLLRP_tSAntennaConfiguration->listAirProtocolInventoryCommandSettings;

            for (; ptTempLLRP_tSParameter != NULL && ptTempLLRP_tSParameter->elementHdr.pType->TypeNum != LLRP_ISO6BInventoryCommand;
                    ptTempLLRP_tSParameter = ptTempLLRP_tSParameter->pNextSubParameter)
            {
                ;
            }
            /*18000-B*/
            if (ptTempLLRP_tSParameter == NULL)
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_ISO18000_6B useing default\r\n");
                ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bIsDefaultCfgFlag = TRUE;
            }
            else
            {
                /*取指针方便操作EPC*/
                RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_ISO18000_6B  not useing default\r\n");
                ptTempISO6BInventoryCommand
                = &ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
                ptTempLLRP_tSISO6BInventoryCommand = (LLRP_tSISO6BInventoryCommand *)ptTempLLRP_tSParameter;
                /*赋值filterlist*/
                if (ptTempLLRP_tSISO6BInventoryCommand->listISO6BFilter == NULL)
                {
                    RdpLlrpDbgPrint("(LLRP)ptTempLLRP_tSISO6BInventoryCommand->listISO6BFilter useing default\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bIsDefaultCfgFlag = TRUE;
                }
                else
                {
                    /*取Filter指针循环赋值*/
                    ptTempISO6BFilterList = &ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter;
                    ptTempLLRP_tSISO6BFilter = ptTempLLRP_tSISO6BInventoryCommand->listISO6BFilter;

                    for (wFilterNum = 0;
                            ptTempLLRP_tSISO6BFilter;
                            ptTempLLRP_tSISO6BFilter = (LLRP_tSISO6BFilter *)ptTempLLRP_tSISO6BFilter->hdr.pNextSubParameter,
                            wFilterNum++)
                    {
                        ptTempISO6BFilterList->ucGroupSelectNum++;
                        /*截断参数赋值*/
                        RdpLlrpDbgPrint("(LLRP)Current ucGroupSelectNum :%d\r\n", ptTempISO6BFilterList->ucGroupSelectNum);
                        ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucAddress
                        = ptTempLLRP_tSISO6BFilter->Address;
                        ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucCommandType
                        = ptTempLLRP_tSISO6BFilter->CommandType;
                        ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucMask
                        = ptTempLLRP_tSISO6BFilter->Mask;
                        ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].wWordDataLen
                        = ptTempLLRP_tSISO6BFilter->WordData.nValue;
                        RdpLlrpDbgPrint("(LLRP)ucAddress:%d\r\n", ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucAddress);
                        RdpLlrpDbgPrint("(LLRP)ucCommandType:%d\r\n", ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucCommandType);
                        RdpLlrpDbgPrint("(LLRP)ucMask:%d\r\n", ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucMask);
                        memcpy(ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter[wFilterNum].ucWordData,
                               ptTempLLRP_tSISO6BFilter->WordData.pValue,
                               ptTempLLRP_tSISO6BFilter->WordData.nValue);
                        RdpLlrpDbgPrint("(LLRP)ISO6B filter data:");
                        for (dwTestID = 0; dwTestID < ptTempLLRP_tSISO6BFilter->WordData.nValue; dwTestID++)
                        {
                            RdpDbgPrintRaw("0x%2x ", ptTempISO6BFilterList->atUSPRdpLlrpISO6BFilter [wFilterNum].ucWordData[dwTestID]);
                        }
                        RdpLlrpDbgPrint("\r\n");
                    }
                }

                /*赋值pC1G2RFControl*/
                if (ptTempLLRP_tSISO6BInventoryCommand->pISO6BRFControl == NULL)
                {
                    RdpLlrpDbgPrint("(LLRP)SO6BRFControl  use default value\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bISORFControl = TRUE;
                }
                else
                {
                    RdpLlrpDbgPrint("(LLRP)ISO6BRFControl  does not use default value\r\n");
                    ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BRFControl.wModeIndex
                    = ptTempLLRP_tSISO6BInventoryCommand->pISO6BRFControl->ModeIndex;
                    RdpLlrpDbgPrint("(LLRP)ucModeIndex:%d\r\n" , ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BRFControl.wModeIndex);
                }
                /*新增加6B预估标签数陈杰20110216*/
                if (ptTempLLRP_tSISO6BInventoryCommand->pISO6BSingulationControl == NULL)
                {
                    RdpLlrpDbgPrint("(LLRP)ISO6BSingulationControl  use default value\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bISOSingulationControl = TRUE;

                }
                else
                {
                    RdpLlrpDbgPrint("(LLRP)ISO6BSingulationControl  does not use default value\r\n");
                    ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.dwTagTransitTime
                    = ptTempLLRP_tSISO6BInventoryCommand->pISO6BSingulationControl->TagTransitTime;
                    ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.wTagPopulation
                    = ptTempLLRP_tSISO6BInventoryCommand->pISO6BSingulationControl->TagPopulation;
                    RdpLlrpDbgPrint("(LLRP)dwTagTransitTime:%d\r\n" , ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.dwTagTransitTime);
                    RdpLlrpDbgPrint("(LLRP)wTagPopulation:%d\r\n" , ptTempISO6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.wTagPopulation);
                }

                /*赋值pISO6BSingulationControl*/
            }
        }
	else if ( ptProtocolInv->eProtocolID == LLRP_AirProtocols_GB)
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_GB  not useing DefaultValue\r\n");
            ptTempLLRP_tSParameter = ptTempLLRP_tSAntennaConfiguration->listAirProtocolInventoryCommandSettings;

            for (;ptTempLLRP_tSParameter != NULL && ptTempLLRP_tSParameter->elementHdr.pType->TypeNum != LLRP_GBInventoryCommand;
                    ptTempLLRP_tSParameter = ptTempLLRP_tSParameter->pNextSubParameter)
            {
                ;
            }
            if (ptTempLLRP_tSParameter == NULL)
            {
                ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpGBInvCtrl.bIsDefaultCfgFlag = TRUE;
            }
            /*GB 协议 处理*/
            else
            {
                /*取指针方便操作GB*/
                RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_GB  is find\r\n");
                ptTempGBInventoryCommand
                = &ptProtocolInv->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand;
                ptTempLLRP_tSGBInventoryCommand = (LLRP_tSGBInventoryCommand *)ptTempLLRP_tSParameter;

                /*赋值filterlist*/
                if (ptTempLLRP_tSGBInventoryCommand->listGBFilter == NULL)

                {
                    RdpLlrpDbgPrint("(LLRP)ptTempLLRP_tSGBInventoryCommand->listGBFilter using DefaultValue\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpGBInvCtrl.bGBFilterctrl = TRUE;
                }
                else
                {
                    /*取Filter指针循环赋值*/
                    RdpLlrpDbgPrint("(LLRP)ptTempLLRP_tSGBInventoryCommand->listGBFilter not using DefaultValue\r\n");
                    ptTempGBFilterList = &ptTempGBInventoryCommand->tUSPRdpLlrpGBFilter;
                    ptTempLLRP_tSGBFilter = ptTempLLRP_tSGBInventoryCommand->listGBFilter;

                    for (wFilterNum = 0;
                            ptTempLLRP_tSGBFilter;
                            ptTempLLRP_tSGBFilter = (LLRP_tSGBFilter *)ptTempLLRP_tSGBFilter->hdr.pNextSubParameter, wFilterNum++)
                    {
                        ptTempGBFilterList->wFilterNum++;
              
                        /*unwareFillter赋值*/
                        if (ptTempLLRP_tSGBFilter->pGBTagInventoryStateAwareFilterAction != NULL)
                        {
                            ptTempGBFilterList->atUSPRdpLlrpGBFilter[wFilterNum].tUSPRdpLlrpGBTagInventoryStateAwareFilterAction.ucGBStateAwareAction
                            = ptTempLLRP_tSGBFilter->pGBTagInventoryStateAwareFilterAction->eAction;
                            ptTempGBFilterList->atUSPRdpLlrpGBFilter[wFilterNum].tUSPRdpLlrpGBTagInventoryStateAwareFilterAction.ucGBStateAwareTarget
                            = ptTempLLRP_tSGBFilter->pGBTagInventoryStateAwareFilterAction->eTarget;
                        }
                        else
                        {
                            ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpGBInvCtrl.tRdpLlrpGBFilterCtrl.bGBTagInventoryStateAwareFilterAction[wFilterNum] = TRUE;
                        }

                        RdpLlrpDbgPrint("(LLRP)GB mask MB:%d\r\n" , ptTempLLRP_tSGBFilter->pGBTagInventoryMask->MB);
                        RdpLlrpDbgPrint("(LLRP)GB Pointer:%d\r\n" , ptTempLLRP_tSGBFilter->pGBTagInventoryMask->Pointer);
                        RdpLlrpDbgPrint("(LLRP)GB TagMask Bits:%d\r\n" , ptTempLLRP_tSGBFilter->pGBTagInventoryMask->TagMask.nBit);
                        /*掩码清点赋值*/
                        ptTempGBFilterList->atUSPRdpLlrpGBFilter[wFilterNum].tUSPRdpLlrpGBTargetTagMask.wMemBank
                        = ptTempLLRP_tSGBFilter->pGBTagInventoryMask->MB;
                        ptTempGBFilterList->atUSPRdpLlrpGBFilter[wFilterNum].tUSPRdpLlrpGBTargetTagMask.wMaskBitPointer
                        = ptTempLLRP_tSGBFilter->pGBTagInventoryMask->Pointer;
                        ptTempGBFilterList->atUSPRdpLlrpGBFilter[wFilterNum].tUSPRdpLlrpGBTargetTagMask.wMaskLength
                        = ptTempLLRP_tSGBFilter->pGBTagInventoryMask->TagMask.nBit;
                        RdpLlrpDbgPrint("(LLRP)GB inv mask:");
                        for (dwTagIndex = 0;
                                dwTagIndex < BIT_CHANGETO_BYTE(ptTempLLRP_tSGBFilter->pGBTagInventoryMask->TagMask.nBit);
                                dwTagIndex++)
                        {
                            ptTempGBFilterList->atUSPRdpLlrpGBFilter[wFilterNum].tUSPRdpLlrpGBTargetTagMask.ucMaskData[dwTagIndex]
                            = ptTempLLRP_tSGBFilter->pGBTagInventoryMask->TagMask.pValue[dwTagIndex];
                            RdpDbgPrintRaw("0x%2x ", ptTempLLRP_tSGBFilter->pGBTagInventoryMask->TagMask.pValue[dwTagIndex]);
                        }
                        RdpLlrpDbgPrint("\r\n");
                    }
                }

                /*赋值pGBRFControl*/
                if (ptTempLLRP_tSGBInventoryCommand->pGBRFControl == NULL)
                {
                    RdpLlrpDbgPrint("(LLRP)RFControl use default value\r\n");
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpGBInvCtrl.bGBRFCtrl = TRUE;
                }
                else
                {
                    ptTempGBInventoryCommand->tUSPRdpLlrpGBRFControl.wModeIndex = ptTempLLRP_tSGBInventoryCommand->pGBRFControl->ModeIndex;         
                    RdpLlrpDbgPrint("(LLRP)ModeIndex:%d \r\n", ptTempGBInventoryCommand->tUSPRdpLlrpGBRFControl.wModeIndex);
                }
                /*赋值pGBSingulationControl*/
                if (ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl == NULL)
                {
                    ptProtocolInv->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpGBInvCtrl.bGBSingulationCtrl = TRUE;
                    RdpLlrpDbgPrint("(LLRP)GB GBSingulation use default value\r\n");
                }
                else
                {
                    ptTempGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.ucSession= ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->Session;
                    ptTempGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.wCCN= ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->CCN;
                    ptTempGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.wCIN= ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->CIN;
		      ptTempGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.ucGBQureyAction= ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->eAction;
		      ptTempGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.ucGBQureySel= ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->eSel;
                    RdpLlrpDbgPrint("(LLRP)Session %d \r\n", ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->Session);
                    RdpLlrpDbgPrint("(LLRP)CCN %d\r\n", ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->CCN);
                    RdpLlrpDbgPrint("(LLRP)CIN %d\r\n", ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->CIN);
		      RdpLlrpDbgPrint("(LLRP)GBQureyAction %d\r\n", ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->eAction);
                    RdpLlrpDbgPrint("(LLRP)GBQureySel %d\r\n", ptTempLLRP_tSGBInventoryCommand->pGBSingulationControl->eSel);
                }
            }
        }
    }
}
/**************************************************************************
* 函数名称：llrp_transferToAntAndProtocolPara
* 功能描述：转换Ant下的所有协议和天线配置到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSAISpec *ptTempLLRP_tSAISpec, T_RdpLlrpAI *ptTempAI
* 输出参数：无
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferToAntAndProtocolPara(LLRP_tSAISpec *ptTempLLRP_tSAISpec, T_RdpLlrpAI *ptTempAI)
{
    unsigned char ucSetAnt[READER_ANTENNA_COUNT] = {0};
    unsigned char ucAntNum = 0;
    unsigned char ucAntennaNum = 0;
    unsigned char ucProtocolNum = 0;
    T_RdpLlrpAntInv *ptTempAntInv = NULL;
    LLRP_tSInventoryParameterSpec *ptTempLLRP_tSInventoryParameterSpec = NULL;
    LLRP_tSAntennaConfiguration *ptTempLLRP_tSAntennaConfiguration = NULL;
    /*如果天线中设置天线为0 那么内部就保存4根天线*/
    if (ptTempLLRP_tSAISpec->AntennaIDs.nValue == 1 && ptTempLLRP_tSAISpec->AntennaIDs.pValue[0] == 0)
    {
        RdpLlrpDbgPrint("(LLRP)Set All Antenna Work!\r\n");
        ucSetAnt[0] = 1;
        ucSetAnt[1] = 2;
        ucSetAnt[2] = 3;
        ucSetAnt[3] = 4;
        ptTempAI->tRdpLlrpAntsInvSet.ucAntNum = READER_ANTENNA_COUNT;
    }
    else
    {
        for (ucAntNum = 0, ptTempAI->tRdpLlrpAntsInvSet.ucAntNum = ptTempLLRP_tSAISpec->AntennaIDs.nValue;
                ucAntNum < ptTempLLRP_tSAISpec->AntennaIDs.nValue; ucAntNum++)
        {
            ucSetAnt[ucAntNum] = ptTempLLRP_tSAISpec->AntennaIDs.pValue[ucAntNum];
        }
    }

    for (ucAntennaNum = 0; ucAntennaNum < ptTempAI->tRdpLlrpAntsInvSet.ucAntNum ; ucAntennaNum++)
    {
        /*指向内部结构中的一个天线*/
        ptTempAntInv = &ptTempAI->tRdpLlrpAntsInvSet.tAntInv[ucAntennaNum];

        ptTempAntInv->ucAntIndex = ucSetAnt[ucAntennaNum];
        RdpLlrpDbgPrint("(LLRP)Ant Id is %d\r\n", ucSetAnt[ucAntennaNum]);
        /*选择 所有 天线支持的协议*/
        for (ucProtocolNum = 0, ptTempLLRP_tSInventoryParameterSpec = ptTempLLRP_tSAISpec->listInventoryParameterSpec;
                ptTempLLRP_tSInventoryParameterSpec;
                ptTempLLRP_tSInventoryParameterSpec = (LLRP_tSInventoryParameterSpec *)ptTempLLRP_tSInventoryParameterSpec->hdr.pNextSubParameter,
                ucProtocolNum++, ptTempAntInv->ucProtocolNum++)
        {
            RdpLlrpDbgPrint("(LLRP)ucProtocolNum : %d\r\n", ucProtocolNum);
            ptTempAntInv->tRdpLlrpProtocolInvSet[ucProtocolNum].wInvParamSpecID = ptTempLLRP_tSInventoryParameterSpec->InventoryParameterSpecID;
            ptTempAntInv->tRdpLlrpProtocolInvSet[ucProtocolNum].eProtocolID = ptTempLLRP_tSInventoryParameterSpec->eProtocolID;
            RdpLlrpDbgPrint("(LLRP)eProtocolID: %d\r\n", ptTempLLRP_tSInventoryParameterSpec->eProtocolID);
            /*寻找这个天线的配置，如果天线0配置，对所有天线生效，前提不可能一根天线下了两次 存在天线1的两套配置*/
            for (ptTempLLRP_tSAntennaConfiguration = ptTempLLRP_tSInventoryParameterSpec->listAntennaConfiguration ;
                    ptTempLLRP_tSAntennaConfiguration;
                    ptTempLLRP_tSAntennaConfiguration = (LLRP_tSAntennaConfiguration *)ptTempLLRP_tSAntennaConfiguration->hdr.pNextSubParameter)
            {

                if (ptTempLLRP_tSAntennaConfiguration->AntennaID == ptTempAntInv->ucAntIndex
                        || ptTempLLRP_tSAntennaConfiguration->AntennaID == 0)
                {
                    RdpLlrpDbgPrint("(LLRP)Antindex:%d find AntennaConfig!\r\n", ptTempAntInv->ucAntIndex);
                    break;
                }
            }
            if (ptTempLLRP_tSAntennaConfiguration == NULL)
            {

                RdpLlrpDbgPrint("(LLRP)Antindex:%d has not find AntennaConfig!\r\n", ptTempAntInv->ucAntIndex);
                ptTempAntInv->tRdpLlrpProtocolInvSet[ucProtocolNum].tRdpLlrpAntConfigCtrl.bIsDefaultCfgFlag = TRUE;
            }
            else
            {
                /*配置天线相关的配置项*/

                llrp_transferToAntCfgPara(&ptTempAntInv->tRdpLlrpProtocolInvSet[ucProtocolNum],
                                          ptTempLLRP_tSAntennaConfiguration);
            }
        }
    }
}
/**************************************************************************
* 函数名称：llrp_transferToAISpecPara
* 功能描述：转换成内部AI 结构
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSAISpec *ptTempLLRP_tSAISpec,T_RdpLlrpAI *ptTempAI
* 输出参数：无
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferToAISpecPara(LLRP_tSAISpec *ptTempLLRP_tSAISpec, T_RdpLlrpAI *ptTempAI)
{
    LLRP_tSAISpecStopTrigger *ptTempLLRP_tSAISpecStopTrigger = ptTempLLRP_tSAISpec->pAISpecStopTrigger;
    T_RdpLlrpAIStopTrigger *ptTempAISpecStopTrigger = &ptTempAI->tRdpLlrpAIStopTrigger;
    RdpLlrpDbgPrint("(LLRP)transfer AI StopTrigger\r\n");
    llrp_transferToAIStopTriggerPara(ptTempLLRP_tSAISpecStopTrigger, ptTempAISpecStopTrigger);
    RdpLlrpDbgPrint("(LLRP)transfer AI Ant and Protocol Para \r\n");
    llrp_transferToAntAndProtocolPara(ptTempLLRP_tSAISpec, ptTempAI);
}
/**************************************************************************
* 函数名称：llrp_buildAnNodeFoDynamicRoQueue
* 功能描述：把动态RO直接保存然后get_RO直接返回
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpDynamicRo *ptQueueHead,    
                            动态链路的头 
                            LLRP_tSADD_ROSPEC*ptAddRoAddr
                            动态Add_Access的地址
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_buildAnNodeFoDynamicRoQueue(T_RdpLlrpDynamicRo *ptQueueHead, LLRP_tSADD_ROSPEC*ptAddRoAddr)
{
    T_RdpLlrpDynamicRo *ptNewNode = NULL;
    T_RdpLlrpDynamicRo *ptNodeCursor = NULL;
    ptNewNode = (T_RdpLlrpDynamicRo *)malloc(sizeof(T_RdpLlrpDynamicRo));
    ptNewNode->ptAddRo = ptAddRoAddr;
    for (ptNodeCursor = ptQueueHead;ptNodeCursor->ptNext != NULL;ptNodeCursor = ptNodeCursor->ptNext)
    {
        ;
    }
    ptNodeCursor->ptNext = ptNewNode;
    ptNewNode->ptNext = NULL;
}
/**************************************************************************
* 函数名称：llrp_deleteAnNodeForDynamicRoQueue
* 功能描述：删除动态RO链路中的RO
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpDynamicRo *ptQueueHead,
                             动态链路的头
                             unsigned int dwROID
                             寻找的ROID
* 输出参数：
* 返 回 值：  无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_deleteAnNodeForDynamicRoQueue(T_RdpLlrpDynamicRo *ptQueueHead, unsigned int dwROID)
{
    T_RdpLlrpDynamicRo *ptLastNodeCursor = NULL;
    T_RdpLlrpDynamicRo *ptNodeCursor = NULL;
    for (ptLastNodeCursor = ptQueueHead, ptNodeCursor = ptQueueHead->ptNext ;
            ptNodeCursor != NULL;ptLastNodeCursor = ptNodeCursor, ptNodeCursor = ptNodeCursor->ptNext)
    {
        if (ptNodeCursor->ptAddRo->pROSpec->ROSpecID == dwROID)
        {
            ptLastNodeCursor->ptNext = ptNodeCursor->ptNext;
            break;
        }
    }
    if (ptNodeCursor != NULL)
    {
        usp_ltk_freeMessage((LLRP_tSMessage *)ptNodeCursor->ptAddRo);
        ptNodeCursor->ptAddRo = NULL;
        ptNodeCursor->ptNext = NULL;
        free(ptNodeCursor);
    }
}
/**************************************************************************
* 函数名称：llrp_buildAnNodeFoDynamicAccessQueue
* 功能描述：把动态Access直接保存然后get_Access直接返回
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpDynamicRo *ptQueueHead,    
                             动态链路的头 
                             LLRP_tSADD_ACCESSSPEC *ptAddAccessAddr
                             动态Add_Access的地址
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_buildAnNodeFoDynamicAccessQueue(T_RdpLlrpDynamicAccess *ptQueueHead, LLRP_tSADD_ACCESSSPEC *ptAddAccessAddr)
{
    T_RdpLlrpDynamicAccess *ptNewNode = NULL;
    T_RdpLlrpDynamicAccess *ptNodeCursor = NULL;
    ptNewNode = (T_RdpLlrpDynamicAccess *)malloc(sizeof(T_RdpLlrpDynamicAccess));
    ptNewNode->ptAddAccess = ptAddAccessAddr;
    for (ptNodeCursor = ptQueueHead;ptNodeCursor->ptNext != NULL;ptNodeCursor = ptNodeCursor->ptNext)
    {
        ;
    }
    ptNodeCursor->ptNext = ptNewNode;
    ptNewNode->ptNext = NULL;
}
/**************************************************************************
* 函数名称：llrp_deleteAnNodeForDynamicAccessQueue
* 功能描述：删除动态Access链路中的Access
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpDynamicRo *ptQueueHead,
                             动态链路的头
                             unsigned int dwAccessID
                             寻找的AccessID
* 输出参数：
* 返 回 值：  无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_deleteAnNodeForDynamicAccessQueue(T_RdpLlrpDynamicAccess *ptQueueHead, unsigned int dwAccessID)
{
    T_RdpLlrpDynamicAccess *ptLastNodeCursor = NULL;
    T_RdpLlrpDynamicAccess *ptNodeCursor = NULL;
    for (ptLastNodeCursor = ptQueueHead, ptNodeCursor = ptQueueHead->ptNext ;
            ptNodeCursor != NULL;ptLastNodeCursor = ptNodeCursor, ptNodeCursor = ptNodeCursor->ptNext)
    {
        if (ptNodeCursor->ptAddAccess->pAccessSpec->AccessSpecID == dwAccessID)
        {
            ptLastNodeCursor->ptNext = ptNodeCursor->ptNext;
            ptNodeCursor->ptNext = NULL;
            break;
        }
    }
    if (ptNodeCursor != NULL)
    {
        usp_ltk_freeMessage((LLRP_tSMessage *)ptNodeCursor->ptAddAccess);
        ptNodeCursor->ptAddAccess = NULL;
        ptNodeCursor->ptNext = NULL;
        free(ptNodeCursor);
    }
}
/**************************************************************************
* 函数名称：llrp_doDefaultforInitRoStartTrigger
* 功能描述：RostartTrigger的默认行为
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpROStartTrigger *ptROStartTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_doDefaultforInitRoStartTrigger(void *ptPara)
{
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrl = NULL;
    T_RdpLlrpROEntry *ptActiveRoEntry = NULL;
    ptActiveRoEntry = (T_RdpLlrpROEntry *)ptPara;
    /*清空Ro的定时器*/
    RdpLlrpDbgPrint("(LLRP)init for RoStartTrigger\r\n");
    LLRP_STOP_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + ptActiveRoEntry->dwROIndex);
    ptRunRoCtrl = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptActiveRoEntry->dwROIndex];
    ptRunRoCtrl->tRdpLlrpRODispatchCtrl.lwStartuSec = GET_READER_BOOT_TIME_MS();
    RdpLlrpDbgPrint("(LLRP)the Ro lwStartu ms : %lld\r\n", ptRunRoCtrl->tRdpLlrpRODispatchCtrl.lwStartuSec);
}
/**************************************************************************
* 函数名称：llrp_doDefaultforRoPeriodStartTrigger
* 功能描述：RostartTrigger的默认行为
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpROStartTrigger *ptROStartTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_doDefaultforRoPeriodStartTrigger(void *ptPara)
{    
}
/**************************************************************************
* 函数名称：llrp_doDefaultforEnableRoStartTrigger
* 功能描述：RostartTrigger的默认行为
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpROStartTrigger *ptROStartTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_doDefaultforEnableRoStartTrigger(void *ptPara)
{    
}
/**************************************************************************
* 函数名称：llrp_externGpiForRoStartTrigger
* 功能描述：外部gpi的处理对于RO的startTrigger
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                             接收的消息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_externGpiForRoStartTrigger(T_Msg *ptRcvMsg)
{
    T_RdpLlrpROEntry *ptInactiveRoEntry = NULL;
    T_RdpLlrpROEntry *ptGpioRoEntry = NULL;
    T_RdpLlrpRO *ptTempRo = NULL;
    T_RdpLlrpRoGpiOfStartTrigger *ptGpioStartTrigger = NULL;
    T_USPRdpLlrpGPIOEventReport *ptGPIOEventReport = NULL;
    ptGPIOEventReport = (T_USPRdpLlrpGPIOEventReport *)(ptRcvMsg + 1);
    if (ptGPIOEventReport == NULL)
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
    }
    RdpLlrpDbgPrint("(LLRP)llrp receive gpi event wEventID:%d,wLogicPortIndex:%d\r\n",
                    ptGPIOEventReport->wEventID, ptGPIOEventReport->wLogicPortIndex);
    /*检查trigger是否发生，按照添加的顺序对所有ro扫描*/
    for (ptInactiveRoEntry = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead.ptNext;
            ptInactiveRoEntry != NULL;ptInactiveRoEntry = ptInactiveRoEntry->ptNext)
    {
        ptTempRo
        = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptInactiveRoEntry->dwROIndex].tRdpLlrpROSpec;
        ptGpioStartTrigger
        = & ptTempRo->tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger;
        if (ptGpioStartTrigger->dwGPIPortNum == ptGPIOEventReport->wLogicPortIndex
                && ptGpioStartTrigger->ucGPIEvent == ptGPIOEventReport->wEventID)
        {
            break;
        }
    }
    if ( ptInactiveRoEntry == NULL )
    {
        /*写入异常Gpio事件没有对应的RostartTrigger*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
    }
    else
    {
        ptTempRo->tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.pfusp_rdp_llrp_ExternalStartTrigger((void*)ptInactiveRoEntry);
    }
    /*activeRo没有任何东西转换*/
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        g_tRdpLlrpReaderDispatch.pfScanROToRun(g_tRdpLlrpReaderDispatch.ptReaderRoSpecData);
    }
}
/**************************************************************************
* 函数名称：llrp_transferInactiveRotoReadyRo
* 功能描述：llrp收到Gpio消息后的处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_GPIOEventReport *ptGPIOEventReport
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferInactiveRotoReadyRo(void *ptPara)
{
    T_RdpLlrpROEntry *ptInactiveRoEntry = NULL;
    T_RdpLlrpROEntry *ptReadyRoEntry = NULL;
    T_RdpLlrpROCtrlAndParam *ptTempRoCtrlAndPara = NULL;
    ptInactiveRoEntry = (T_RdpLlrpROEntry *)ptPara;
    RdpLlrpDbgPrint("(LLRP)llrp_transferInactiveRotoReadyRo\r\n");
    ptTempRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptInactiveRoEntry->dwROIndex];
    ptReadyRoEntry = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead,
                     ptInactiveRoEntry->dwROIndex,
                     ptInactiveRoEntry->dwPriority);
    if (ptReadyRoEntry == NULL)
    {
        RdpLlrpDbgPrint("there is not Ro Id :%d ,Roindex :%d in inactive Ro queue\r\n",
                        ptTempRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID, ptInactiveRoEntry->dwROIndex);
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, ptTempRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID,
                   ptInactiveRoEntry->dwROIndex, ptInactiveRoEntry->dwPriority, RDP_LLRP_RULE_ID);
    }
    llrp_insertAnNodetoPriorityQueueOfRO(ptReadyRoEntry, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tReadyRoQueuehead);
    ptTempRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_READY;
    RdpLlrpDbgPrint("(LLRP)RoID:%d,RoIndex:%d,ucpriority:%d  change into Readyqueue\r\n",
                    ptTempRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID, ptInactiveRoEntry->dwROIndex, ptInactiveRoEntry->dwPriority);

}

/**************************************************************************
* 函数名称：llrp_transferActiveRotoInactiveRo
* 功能描述：
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             ptActiveRoEntry active队列的中的元素
                             
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferActiveRotoInactiveRo(void *ptPara)
{
    T_RdpLlrpROEntry *ptActiveRoEntry = NULL;
    T_RdpLlrpROEntry *ptFindRoEntry = NULL;
    T_RdpLlrpROCtrlAndParam *ptTempRoCtrlAndPara = NULL;
    ptActiveRoEntry = (T_RdpLlrpROEntry *)ptPara;
    ptTempRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptActiveRoEntry->dwROIndex];
    ptFindRoEntry = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO,
                    ptActiveRoEntry->dwROIndex,
                    ptActiveRoEntry->dwPriority);
    if (ptFindRoEntry == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
    }
    llrp_insertAnNodetoAllQueueOfRO(ptFindRoEntry, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead);
    ptTempRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_INACTIVE;
    RdpLlrpDbgPrint("(LLRP)RoID:%d,RoIndex:%d,ucpriority:%d  change into inactive queue\r\n",
                    ptTempRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID, ptActiveRoEntry->dwROIndex, ptActiveRoEntry->dwPriority);

}
/**************************************************************************
* 函数名称：llrp_enableRoForRoPeriodStartTrigger
* 功能描述：lenableRo时 ，周期性Ro的处理手段
* 访问的表：无
* 修改的表：无
* 输入参数：T_GPIOEventReport *ptGPIOEventReport
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_enableRoForRoPeriodStartTrigger(void *ptPara)
{
    T_RdpLlrpROEntry *ptInactiveRoEntry = NULL;
    T_RdpLlrpRoPeriodOfStartTrigger *ptRoPeriodOfStartTrigger = NULL;
    T_RdpLlrpROCtrlAndParam *ptTempRoCtrlAndPara = NULL;
    ptInactiveRoEntry = (T_RdpLlrpROEntry *)ptPara;
    ptTempRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptInactiveRoEntry->dwROIndex];
    ptRoPeriodOfStartTrigger = &ptTempRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger;
    RdpLlrpDbgPrint("(LLRP)Deal enableRomsg  for Ro PeriodStartTrigger\r\n");
    if (ptRoPeriodOfStartTrigger->lwUTCTimestampMicroSec != 0)
    {
        RdpLlrpDbgPrint("(LLRP) RoPeriodOfStartTrigger UTCTimestampMicroSec: %lld\r\n", ptRoPeriodOfStartTrigger->lwUTCTimestampMicroSec);
        RdpLlrpDbgPrint("(LLRP) RoPeriodOfStartTrigger->dwOffset: %d\r\n", ptRoPeriodOfStartTrigger->dwOffset);
        if (llrp_getReaderuSec() < (ptRoPeriodOfStartTrigger->lwUTCTimestampMicroSec + ptRoPeriodOfStartTrigger->dwOffset*1000))
        {
            RdpLlrpDbgPrint("(LLRP)set timer for enableRoMsg of Ro PeriodStartTrigger\r\n");
            LLRP_START_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + ptInactiveRoEntry->dwROIndex,
                             ( (ptRoPeriodOfStartTrigger->lwUTCTimestampMicroSec + ptRoPeriodOfStartTrigger->dwOffset*1000) - llrp_getReaderuSec()) / 1000);
        }
        else
        {
            /*直接转换到Ready队列中*/
            RdpLlrpDbgPrint("(LLRP)insertReadyQueue for enableRoMsg of Ro PeriodStartTrigger\r\n");
            llrp_transferInactiveRotoReadyRo(ptInactiveRoEntry);
        }
    }
    else
    {
        if (ptRoPeriodOfStartTrigger->dwOffset != 0)
        {
            RdpLlrpDbgPrint("(LLRP)set timer for enableRoMsg of Ro PeriodStartTrigger\r\n");
            LLRP_START_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + ptInactiveRoEntry->dwROIndex, ptRoPeriodOfStartTrigger->dwOffset);
        }
        else
        {
            /*直接转换到Ready队列中*/
            RdpLlrpDbgPrint("(LLRP)insertReadyQueue for enableRoMsg of Ro PeriodStartTrigger\r\n");
            llrp_transferInactiveRotoReadyRo(ptInactiveRoEntry);
        }
    }
}
/**************************************************************************
* 函数名称：llrp_externPeriodtimerForRoStartTrigger
* 功能描述：处理周期性Ro所定义的定时器
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                             传入的消息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_externPeriodtimerForRoStartTrigger(T_Msg *ptRcvMsg)
{
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrl = NULL;
    T_RdpLlrpROEntry *ptActiveRoEntry = NULL;
    T_RdpLlrpROEntry *ptRoEntryCusor = NULL;
    RdpLlrpDbgPrint("(LLRP)receive an timer trigger\r\n");
    if (ptRcvMsg->wMsgID < EV_RDP_LLRP_RULETIMER_BEGIN )
    {
        /*写入异常*/
        RdpLlrpDbgPrint("(LLRP)externPeriodtimerForRoStartTrigger msgId errorptRcvMsg->wMsgID:%d\r\n", ptRcvMsg->wMsgID);
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
    }
    for (ptRoEntryCusor = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead.ptNext;
            ptRoEntryCusor != NULL;ptRoEntryCusor = ptRoEntryCusor->ptNext)
    {

        if (ptRoEntryCusor->dwROIndex == ptRcvMsg->wMsgID - EV_RDP_LLRP_RULETIMER_BEGIN)
        {
            ptRunRoCtrl = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptRoEntryCusor->dwROIndex];
            break;
        }
    }
    if (ptRoEntryCusor == NULL)
    {
        RdpLlrpDbgPrint("(LLRP)the timer is not in inactive Ro queue the Roindex ignore this timer msg\r\n");
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)the timer is  in inactive Ro queue and need change into ready queue the Roindex:%d\r\n", ptRoEntryCusor->dwROIndex);
        ptRunRoCtrl->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.pfusp_rdp_llrp_ExternalStartTrigger((void *)ptRoEntryCusor);
    }
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        g_tRdpLlrpReaderDispatch.pfScanROToRun(g_tRdpLlrpReaderDispatch.ptReaderRoSpecData);
    }

}

/**************************************************************************
* 函数名称：llrp_initPeriodforRoStartTrigger
* 功能描述：周期Ro开始时，需要调用的部分
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             通用参数这里传入运行Ro的开始时间域
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_initPeriodForRoStartTrigger(void *ptPara)
{
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrl = NULL;
    T_RdpLlrpROEntry *ptActiveRoEntry = NULL;
    ptActiveRoEntry = (T_RdpLlrpROEntry *)ptPara;
    /*清空Ro的定时器*/
    RdpLlrpDbgPrint("(LLRP)init for RoStartTrigger for peirod Ro startrigger \r\n");
    LLRP_STOP_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + ptActiveRoEntry->dwROIndex);
    ptRunRoCtrl = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptActiveRoEntry->dwROIndex];
    ptRunRoCtrl->tRdpLlrpRODispatchCtrl.lwStartuSec = GET_READER_BOOT_TIME_MS();
    RdpLlrpDbgPrint("(LLRP)the Ro lwStartu ms : %lld\r\n", ptRunRoCtrl->tRdpLlrpRODispatchCtrl.lwStartuSec);
}
/**************************************************************************
* 函数名称：llrp_startnextPeriodforRoStartTrigger
* 功能描述：周期Ro开始时,Ro结束时Ro的startTrigger的处理
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             传入Ro的控制节点
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_startnextPeriodforRoStartTrigger(void *ptPara)
{
    unsigned long long lwReaderuSec = 0;
    unsigned int dwInterval = 0;
    T_RdpLlrpROEntry *ptInactiveRoEntry = NULL;
    T_RdpLlrpRoPeriodOfStartTrigger *ptRoPeriodOfStartTrigger = NULL;
    T_RdpLlrpROCtrlAndParam *ptTempRoCtrlAndPara = NULL;
    ptInactiveRoEntry = (T_RdpLlrpROEntry *)ptPara;
    ptTempRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptInactiveRoEntry->dwROIndex];
    ptRoPeriodOfStartTrigger = &ptTempRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary \
                               .tRdpLlrpROStartTrigger.tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger;
    lwReaderuSec = GET_READER_BOOT_TIME_MS();
    dwInterval = (lwReaderuSec - ptTempRoCtrlAndPara->tRdpLlrpRODispatchCtrl.lwStartuSec);
    RdpLlrpDbgPrint("(LLRP)startnextPeriodforRoStartTriggerdwPeriod: %d,curTime:%lld,startTime:%lld,Inteval:%d\r\n",
                    ptRoPeriodOfStartTrigger->dwPeriod, lwReaderuSec, ptTempRoCtrlAndPara->tRdpLlrpRODispatchCtrl.lwStartuSec,
                    dwInterval);
    if (dwInterval >= ptRoPeriodOfStartTrigger->dwPeriod)
    {
        llrp_transferInactiveRotoReadyRo(ptInactiveRoEntry);
        RdpLlrpDbgPrint("(LLRP)Ro run time is longer than period time , need run imediately\r\n");
    }
    else
    {
        LLRP_START_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + ptInactiveRoEntry->dwROIndex,
                         (ptRoPeriodOfStartTrigger->dwPeriod - dwInterval));
        RdpLlrpDbgPrint("(LLRP)set an timer for Ro next start timerID:%d,msec:%d\r\n",
                        (EV_RDP_LLRP_RULETIMER_BEGIN + ptInactiveRoEntry->dwROIndex),
                        (ptRoPeriodOfStartTrigger->dwPeriod - dwInterval));
    }
}

/**************************************************************************
* 函数名称：llrp_doDefaultforExternalStartTrigger
* 功能描述：llrp收到Gpio消息后的处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_GPIOEventReport *ptGPIOEventReport
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_doDefaultforExternalStartTrigger(void *ptPara)
{}
/**************************************************************************
* 函数名称：llrp_transferROStartTriggerPara
* 功能描述：转换Ro的startTrigger的内容到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSROSpecStartTrigger *ptTempLLRP_tSROSpecStartTrigger,
                             T_RdpLlrpROStartTrigger *ptTempROSpecStartTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferROStartTriggerPara(LLRP_tSROSpecStartTrigger *ptTempLLRP_tSROSpecStartTrigger,
                                     T_RdpLlrpROStartTrigger *ptTempROSpecStartTrigger)
{
    ptTempROSpecStartTrigger->dwROSpecStartTriggerType = ptTempLLRP_tSROSpecStartTrigger->eROSpecStartTriggerType;
    switch (ptTempLLRP_tSROSpecStartTrigger->eROSpecStartTriggerType)
    {
    case LLRP_ROSpecStartTriggerType_Null:
        RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStartTriggerType_Null\r\n");
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_EnableStartTrigger = llrp_doDefaultforEnableRoStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_ExternalStartTrigger = llrp_doDefaultforExternalStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_InitStartTrigger = llrp_doDefaultforInitRoStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_PeriodStartTrigger = llrp_doDefaultforRoPeriodStartTrigger;
        break;
    case LLRP_ROSpecStartTriggerType_GPI:
        RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStartTriggerType_GPI\r\n");
        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger.dwGPIPortNum
        = ptTempLLRP_tSROSpecStartTrigger->pGPITriggerValue->GPIPortNum;
        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger.dwTimeout
        = ptTempLLRP_tSROSpecStartTrigger->pGPITriggerValue->Timeout;
        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger.ucGPIEvent
        = ptTempLLRP_tSROSpecStartTrigger->pGPITriggerValue->GPIEvent;
        RdpLlrpDbgPrint("(LLRP)dwGPIPortNum:%d\r\n" ,
                        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger.dwGPIPortNum);
        RdpLlrpDbgPrint("(LLRP)ucGPIEvent:%d\r\n" ,
                        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger.ucGPIEvent);
        RdpLlrpDbgPrint("(LLRP)dwTimeout:%d\r\n" ,
                        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoGpiOfStartTrigger.dwTimeout);
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_ExternalStartTrigger = llrp_transferInactiveRotoReadyRo;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_EnableStartTrigger = llrp_doDefaultforEnableRoStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_InitStartTrigger = llrp_doDefaultforInitRoStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_PeriodStartTrigger = llrp_doDefaultforRoPeriodStartTrigger;
        break;
    case LLRP_ROSpecStartTriggerType_Immediate:
        RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStartTriggerType_Immediate\r\n");
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_ExternalStartTrigger = llrp_doDefaultforExternalStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_EnableStartTrigger = llrp_transferInactiveRotoReadyRo;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_InitStartTrigger = llrp_doDefaultforInitRoStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_PeriodStartTrigger = llrp_doDefaultforRoPeriodStartTrigger;
        break;
    case LLRP_ROSpecStartTriggerType_Periodic:
        /*如果不设置UTC时间值 那么 设置UTC为0*/
        RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStartTriggerType_Periodic\r\n");
        if (ptTempLLRP_tSROSpecStartTrigger->pPeriodicTriggerValue->pUTCTimestamp == NULL)
        {
            ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger.lwUTCTimestampMicroSec = 0;
        }
        else
        {
            ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger.lwUTCTimestampMicroSec
            = ptTempLLRP_tSROSpecStartTrigger->pPeriodicTriggerValue->pUTCTimestamp->Microseconds;
        }
        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger.dwOffset
        = ptTempLLRP_tSROSpecStartTrigger->pPeriodicTriggerValue->Offset;
        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger.dwPeriod
        = ptTempLLRP_tSROSpecStartTrigger->pPeriodicTriggerValue->Period;
        RdpLlrpDbgPrint("(LLRP)lwUTCTimestampMicroSec:%lld\r\n" ,
                        ptTempROSpecStartTrigger->tRdpLlrpRoParamOfStartTrigger.tRdpLlrpRoPeriodOfStartTrigger.lwUTCTimestampMicroSec);
        RdpLlrpDbgPrint("(LLRP)Offset:%d\r\n" ,
                        ptTempLLRP_tSROSpecStartTrigger->pPeriodicTriggerValue->Offset);
        RdpLlrpDbgPrint("(LLRP)Period:%d\r\n" ,
                        ptTempLLRP_tSROSpecStartTrigger->pPeriodicTriggerValue->Period);
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_ExternalStartTrigger = llrp_transferInactiveRotoReadyRo;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_EnableStartTrigger = llrp_enableRoForRoPeriodStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_InitStartTrigger = llrp_initPeriodForRoStartTrigger;
        ptTempROSpecStartTrigger->pfusp_rdp_llrp_PeriodStartTrigger = llrp_startnextPeriodforRoStartTrigger;
        break;
    default:

        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
        break;
    }
}
/**************************************************************************
* 函数名称：llrp_doDefaultforRoStopTrigger
* 功能描述：Ro的stopTrigger的默认处理
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                            
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_doDefaultforRoStopTrigger(void *ptPara)
{}
/**************************************************************************
* 函数名称：llrp_externGpiForRoStartTrigger
* 功能描述：外部gpi的处理对于RO的stopTrigger
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                             接收的消息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_externGpiForRoStopTrigger(T_Msg *ptRcvMsg)
{
    T_RdpLlrpROEntry *ptActiveRoEntry = NULL;
    T_RdpLlrpROEntry *ptGpioRoEntry = NULL;
    T_RdpLlrpRO *ptTempRo = NULL;
    T_RdpLlrpRoGpiOfStopTrigger *ptGpioStopTrigger = NULL;
    T_USPRdpLlrpGPIOEventReport *ptGPIOEventReport = NULL;
    ptGPIOEventReport = (T_USPRdpLlrpGPIOEventReport *)(ptRcvMsg + 1);
    if (ptGPIOEventReport == NULL)
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
    }
    RdpLlrpDbgPrint("(LLRP)llrp receive gpi event wEventID:%d,wLogicPortIndex:%d\r\n",
                    ptGPIOEventReport->wEventID, ptGPIOEventReport->wLogicPortIndex);
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, 0, 0, 0, RDP_LLRP_RULE_ID);
        RdpLlrpDbgPrint("(LLRP) there is not an active Ro\r\n");
        return ;
    }
    /*检查trigger是否发生，按照添加的顺序对所有ro扫描*/
    for (ptActiveRoEntry = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext;
            ptActiveRoEntry != NULL;ptActiveRoEntry = ptActiveRoEntry->ptNext)
    {
        ptTempRo
        = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptActiveRoEntry->dwROIndex].tRdpLlrpROSpec;
        ptGpioStopTrigger
        = & ptTempRo->tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger;
        if (ptGpioStopTrigger->dwGPIPortNum == ptGPIOEventReport->wLogicPortIndex
                && ptGpioStopTrigger->ucGPIEvent == ptGPIOEventReport->wEventID)
        {
            break;
        }
    }
    if ( ptActiveRoEntry == NULL )
    {
        /*写入异常Gpio事件没有对应的RostopTrigger*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
    }
    else
    {
        ptTempRo->tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.pfusp_rdp_llrp_externalStoptTrigger((void *)ptActiveRoEntry);
    }
    /*activeRo没有任何东西转换*/


}

/**************************************************************************
* 函数名称：llrp_externGpiForRoStartTrigger
* 功能描述：外部gpi的处理对于RO的stopTrigger
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                             接收的消息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_externGpiForAIStopTrigger(T_Msg *ptRcvMsg)
{
    T_RdpLlrpROEntry *ptActiveRoEntry = NULL;
    T_RdpLlrpROEntry *ptGpioRoEntry = NULL;
    T_RdpLlrpAIGpiOfStopTrigger *ptGpioStopTrigger = NULL;
    T_USPRdpLlrpGPIOEventReport *ptGPIOEventReport = NULL;
    T_RdpLlrpAI *ptRdpLlrpAI = NULL;
    ptGPIOEventReport = (T_USPRdpLlrpGPIOEventReport *)(ptRcvMsg + 1);
    if (ptGPIOEventReport == NULL)
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
    }
    RdpLlrpDbgPrint("(LLRP)llrp receive gpi event wEventID:%d,wLogicPortIndex:%d\r\n",
                    ptGPIOEventReport->wEventID, ptGPIOEventReport->wLogicPortIndex);
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, 0, 0, 0, RDP_LLRP_RULE_ID);
        RdpLlrpDbgPrint("(LLRP) there is not an active Ro\r\n");
        return ;
    }
    /*检查trigger是否发生，按照添加的顺序对所有ro扫描*/
    for (ptActiveRoEntry = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext;
            ptActiveRoEntry != NULL;ptActiveRoEntry = ptActiveRoEntry->ptNext)
    {
        ptRdpLlrpAI = llrp_getRunAI();
        ptGpioStopTrigger = &ptRdpLlrpAI->tRdpLlrpAIStopTrigger.tRdpLlrpAIGpiOfStopTrigger;
        if (ptGpioStopTrigger->dwGPIPortNum == ptGPIOEventReport->wLogicPortIndex
                && ptGpioStopTrigger->ucGPIEvent == ptGPIOEventReport->wEventID)
        {
            break;
        }
    }
    if ( ptActiveRoEntry == NULL )
    {
        /*写入异常Gpio事件没有对应的RostopTrigger*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
    }
    else
    {
        ptRdpLlrpAI->tRdpLlrpAIStopTrigger.pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger(&ptRdpLlrpAI->tRdpLlrpAIStopTrigger);
    }
    /*activeRo没有任何东西转换*/


}
/**************************************************************************
* 函数名称：llrp_dealExternGpiForReader
* 功能描述：外部gpi的处理对于Reader
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                             接收的消息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_dealExternGpiForReader(T_Msg *ptRcvMsg)
{
    /*这里同时要处理三种Gpi  顺序无所谓*/
    /*如果ActiveRo的stopTrigger 要置标志位等待调度*/
    llrp_externGpiForRoStopTrigger(ptRcvMsg);
    /*如果ActiveAI的stopTrigger 要置标志位等待调度*/
    llrp_externGpiForAIStopTrigger(ptRcvMsg);
    /*如果是inactiveRO ,要转换队列到ready*/
    llrp_externGpiForRoStartTrigger(ptRcvMsg);
}
/**************************************************************************
* 函数名称：llrp_judgeGpioRoRuntimeforRoStopTrigger
* 功能描述：llrp在在调度Ro时，判断Ro的时间是否超时
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             当前运行的Ro的控制结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_judgeGpioRoRuntimeforRoStopTrigger(void *ptPara)
{
    unsigned long long lwCurentuSec = 0;
    unsigned int dwTimeout = 0;
    T_RdpLlrpROCtrlAndParam *ptRunROCtrlAndPara = NULL;
    ptRunROCtrlAndPara = (T_RdpLlrpROCtrlAndParam *)ptPara;
    lwCurentuSec = GET_READER_BOOT_TIME_MS();
    dwTimeout = ptRunROCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary \
                .tRdpLlrpROStopTrigger.tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.dwTimeout;
    if (dwTimeout == 0 )
    {
        RdpLlrpDbgPrint("(LLRP)Ro Gpio StopTrigger not timeout,continue to run Ro\r\n");
        return ;
    }
    if ((lwCurentuSec - ptRunROCtrlAndPara->tRdpLlrpRODispatchCtrl.lwStartuSec) > dwTimeout)
    {
        RdpLlrpDbgPrint("(LLRP)Ro Gpio StopTrigger timerout,need stop Ro\r\n");
        ptRunROCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.dwROStopTriggerState = TRUE;
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)Ro Gpio StopTrigger not timeout,continue to run Ro\r\n");
    }
}
/**************************************************************************
* 函数名称：llrp_judgeDurationRoRuntimeforRoStopTrigger
* 功能描述：llrp在在调度Ro时，判断Ro的时间是否超时
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             当前运行的Ro的控制结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_judgeDurationRoRuntimeforRoStopTrigger(void *ptPara)
{
    unsigned long long lwCurentuSec = 0;
    unsigned int dwDuration = 0;
    T_RdpLlrpROCtrlAndParam *ptRunROCtrlAndPara = NULL;
    ptRunROCtrlAndPara = (T_RdpLlrpROCtrlAndParam *)ptPara;
    lwCurentuSec = GET_READER_BOOT_TIME_MS();
    dwDuration = ptRunROCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary \
                 .tRdpLlrpROStopTrigger.tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoDurationOfStopTrigger.dwDuration;
    if (dwDuration == 0)
    {
        RdpLlrpDbgPrint("(LLRP)Ro duration StopTrigger not timeout,continue to run Ro\r\n");
        return ;
    }
    if ((lwCurentuSec - ptRunROCtrlAndPara->tRdpLlrpRODispatchCtrl.lwStartuSec) > dwDuration)
    {
        RdpLlrpDbgPrint("(LLRP)Ro duration StopTrigger timerout,need stop Ro\r\n");
        ptRunROCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.dwROStopTriggerState = TRUE;
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)Ro duration StopTrigger not timeout,continue to run Ro\r\n");
    }
}
/**************************************************************************
* 函数名称：llrp_judgehappenforRoStopTrigger
* 功能描述：判断Ro的stopTrigger是否发生
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             当前运行的Ro的控制结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned int llrp_judgehappenforRoStopTrigger(void *ptPara)
{
    T_RdpLlrpROCtrlAndParam *ptRunROCtrlAndPara = NULL;
    ptRunROCtrlAndPara = (T_RdpLlrpROCtrlAndParam *)ptPara;
    return ptRunROCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.dwROStopTriggerState;
}

/**************************************************************************
* 函数名称：llrp_initforRoStopTrigger
* 功能描述：初始化Ro的停止条件的一些内容
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             当前运行的Ro的控制结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_initforRoStopTrigger(void *ptPara)
{
    T_RdpLlrpROCtrlAndParam *ptRunROCtrlAndPara = NULL;
    ptRunROCtrlAndPara = (T_RdpLlrpROCtrlAndParam *)ptPara;
    ptRunROCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.dwROStopTriggerState = FALSE;
    ptRunROCtrlAndPara->tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex = 0;
    ptRunROCtrlAndPara->tRdpLlrpActiveROCtrlIndex.ucWorkAntIndex = 0;
    ptRunROCtrlAndPara->tRdpLlrpActiveROCtrlIndex.ucWorkProtocolIndex = 0;
}
/**************************************************************************
* 函数名称：llrp_transferROStopTriggerPara
* 功能描述：转换Ro的stopTrigger的内容到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSROSpecStopTrigger *ptTempLLRP_tSROSpecStopTrigger,
                             T_RdpLlrpROStopTrigger *ptTempROSpecStopTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferROStopTriggerPara(LLRP_tSROSpecStopTrigger *ptTempLLRP_tSROSpecStopTrigger,
                                    T_RdpLlrpROStopTrigger *ptTempROSpecStopTrigger)
{
    switch (ptTempLLRP_tSROSpecStopTrigger->eROSpecStopTriggerType)
    {
    case LLRP_ROSpecStopTriggerType_Null:
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStopTriggerType_Null\r\n");
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_endofAPDealforStopTrigger = llrp_doDefaultforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_externalStoptTrigger = llrp_doDefaultforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_initStopTrigger = llrp_initforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_judgeHappenforStopTrigger = llrp_judgehappenforRoStopTrigger;
            break;
        }
    case LLRP_ROSpecStopTriggerType_GPI_With_Timeout:
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStopTriggerType_GPI_With_Timeout\r\n");
            ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.dwGPIPortNum
            = ptTempLLRP_tSROSpecStopTrigger->pGPITriggerValue->GPIPortNum;
            ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.ucGPIEvent
            = ptTempLLRP_tSROSpecStopTrigger->pGPITriggerValue->GPIEvent;
            /*对于StartTrigger timeout不起作用 */
            ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.dwTimeout
            = ptTempLLRP_tSROSpecStopTrigger->pGPITriggerValue->Timeout;
            RdpLlrpDbgPrint("(LLRP)dwGPIPortNum:%d\r\n", ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.dwGPIPortNum);
            RdpLlrpDbgPrint("(LLRP)ucGPIEvent:%d\r\n", ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.ucGPIEvent);
            RdpLlrpDbgPrint("(LLRP)dwTimeout:%d\r\n", ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoGpiOfStopTrigger.dwTimeout);
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_endofAPDealforStopTrigger = llrp_judgeGpioRoRuntimeforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_externalStoptTrigger = llrp_transferActiveRotoInactiveRo;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_initStopTrigger = llrp_initforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_judgeHappenforStopTrigger = llrp_judgehappenforRoStopTrigger;
            break;
        }
    case LLRP_ROSpecStopTriggerType_Duration:
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStopTriggerType_Duration\r\n");
            ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoDurationOfStopTrigger.dwDuration
            = ptTempLLRP_tSROSpecStopTrigger->DurationTriggerValue;
            RdpLlrpDbgPrint("(LLRP)dwDuration:%d\r\n", ptTempROSpecStopTrigger->tRdpLlrpRoParamOfStopTrigger.tRdpLlrpRoDurationOfStopTrigger.dwDuration);
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_endofAPDealforStopTrigger = llrp_judgeDurationRoRuntimeforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_externalStoptTrigger = llrp_doDefaultforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_initStopTrigger = llrp_initforRoStopTrigger;
            ptTempROSpecStopTrigger->pfusp_rdp_llrp_judgeHappenforStopTrigger = llrp_judgehappenforRoStopTrigger;
            break;
        }
    default:
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecStopTriggerType Error\r\n");
            /*写入异常*/
            RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
            break;
        }
    }
}
/**************************************************************************
* 函数名称：llrp_doDefaultforRoReportTrigger
* 功能描述：Ro的ReportTrigger的默认行为
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                            
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_doDefaultforRoReportTrigger(void *ptPara)
{}
/**************************************************************************
* 函数名称：llrp_linkReportBufferforRoReportTrigger
* 功能描述：Ro的ReportTrigger为NULL时在Ro结束时上报报告
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                            
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_linkReportBufferforRoReportTrigger(void *ptPara)
{
    T_RdpLlrpROReport *ptRoReport = NULL;
    T_RdpLlrpSingleReportCtrl *ptLinkReporthead = NULL;
    T_RdpLlrpSingleReportCtrl *ptLinkReportCursor = NULL;
    ptRoReport = (T_RdpLlrpROReport *)ptPara;
    T_RdpLlrpAcculateReportData *ptReaderAcculateReport = &g_tRdpLlrpReaderAcculateReport[ptRoReport->tActiveRoReportLink.ucLinkIndex];
    if (ptRoReport->tActiveRoReportLink.ptAcculateReportHead != NULL)
    {
        if (ptReaderAcculateReport->ptAcculateReportHead == NULL)
        {
            /*如果报告积累数量超过一定数量则上报告警 并删除新产生报告*/
            if ( ptReaderAcculateReport->dwReportSize > RDP_LLRP_MAX_ACCULATE_SIZE )
            {
                RdpLlrpDbgPrint("(LLRP)Acculate report is larger than LLRP_MAX_ACCULATE_SIZE,need alarm and free new report \r\n ");
                llrp_reportReaderEventNotification(LLRP_NotificationEventType_Report_Buffer_Fill_Warning, (LLRP_tEROSpecEventType)0);
                llrp_freeReportToROReportLink(&ptRoReport->tActiveRoReportLink);
            }
            else
            {
                RdpLlrpDbgPrint("(LLRP)the %d linkindex report is empty  connect report into  %d linkindex\r\n",
                                ptRoReport->tActiveRoReportLink.ucLinkIndex, ptRoReport->tActiveRoReportLink.ucLinkIndex);
                ptReaderAcculateReport->ptAcculateReportHead = ptRoReport->tActiveRoReportLink.ptAcculateReportHead;
                ptReaderAcculateReport->dwReportNum += ptRoReport->tActiveRoReportLink.dwReportNum;
                ptReaderAcculateReport->dwReportSize += ptRoReport->tActiveRoReportLink.dwReportSize;
                /*上报缓存告警*/
                RdpLlrpDbgPrint("(LLRP)the %d linkindex report num %d reportsize %d\r\n",
                                ptRoReport->tActiveRoReportLink.ucLinkIndex,
                                ptReaderAcculateReport->dwReportNum,
                                ptReaderAcculateReport->dwReportSize);
            }
        }
        else
        {
            /*如果报告积累数量超过一定数量则上报告警 并删除新产生报告*/
            if ( ptReaderAcculateReport->dwReportSize > RDP_LLRP_MAX_ACCULATE_SIZE )
            {
                RdpLlrpDbgPrint("(LLRP)Acculate report is larger than LLRP_MAX_ACCULATE_SIZE,need alarm and free new report \r\n ");
                llrp_reportReaderEventNotification(LLRP_NotificationEventType_Report_Buffer_Fill_Warning, (LLRP_tEROSpecEventType)0);
                llrp_freeReportToROReportLink(&ptRoReport->tActiveRoReportLink);
            }
            else
            {
                for (ptLinkReportCursor = ptReaderAcculateReport->ptAcculateReportHead;ptLinkReportCursor->ptNext != NULL;
                        ptLinkReportCursor = ptLinkReportCursor->ptNext)
                {
                    ;
                }
                ptLinkReportCursor->ptNext = ptRoReport->tActiveRoReportLink.ptAcculateReportHead;
                ptRoReport->tActiveRoReportLink.ptAcculateReportHead->ptlast = ptLinkReportCursor;
                ptReaderAcculateReport->dwReportNum += ptRoReport->tActiveRoReportLink.dwReportNum;
                ptReaderAcculateReport->dwReportSize += ptRoReport->tActiveRoReportLink.dwReportSize;
                RdpLlrpDbgPrint("(LLRP)the %d linkindex report num %d reportsize %d\r\n",
                                ptRoReport->tActiveRoReportLink.ucLinkIndex,
                                ptReaderAcculateReport->dwReportNum,
                                ptReaderAcculateReport->dwReportSize);
            }
        }
        ptRoReport->tActiveRoReportLink.ptAcculateReportHead = NULL;
        ptRoReport->tActiveRoReportLink.ptActiveRoReportTail = NULL;
        ptRoReport->tActiveRoReportLink.dwReportNum = 0;
        ptRoReport->tActiveRoReportLink.dwReportSize = 0;
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)the RO does not inv any Tag\r\n");
    }

}

/**************************************************************************
* 函数名称：llrp_increaseNtagforRoReportTrigger
* 功能描述：每构造一个报告就要计算是否上报
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                            
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_increaseNtagforRoReportTrigger(void *ptPara)
{
    T_Msg *ptSndMsg = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpROReport *ptRoReport = NULL;
    T_RdpLlrpSingleReportCtrl *ptLinkReporthead = NULL;
    T_RdpLlrpSingleReportCtrl *ptLinkReportCursor = NULL;
    ptRoReport = (T_RdpLlrpROReport *)ptPara;
    if (ptRoReport->wThresholdOfReportNum == 0)
    {
        RdpLlrpDbgPrint("(LLRP)wThresholdOfReportNum is zero need not accumulate\r\n");
        return ;
    }
    RdpLlrpDbgPrint("(LLRP)now the ReportNum is %d the wThresholdOfReportNum is %d \r\n",
                    ptRoReport->tActiveRoReportLink.dwReportNum, ptRoReport->wThresholdOfReportNum);
    if (ptRoReport->tActiveRoReportLink.dwReportNum >= ptRoReport->wThresholdOfReportNum)
    {
        ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
        ptSndMsg->ucLinkIndex = ptRoReport->tActiveRoReportLink.ucLinkIndex;
        ptSndMsg->ucLinkType = ptRoReport->tActiveRoReportLink.ucLinkType;
        ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
        ptSndMsg->wDstTno = USP_RDP_REPORT_TNO;
        ptSndMsg->wMsgLen = sizeof(T_RdpLlrpSendReportContent);
        ptRunRoCtrlAndPara = llrp_getRunRO();
        if (ptRunRoCtrlAndPara == NULL)
        {
            RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
            return ;
        }
        ptSndMsg->wSenderTno = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wSenderTno;
        ptSndMsg->wReceiverTno = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wReceiverTno;
        llrp_sendReport(ptRoReport->tActiveRoReportLink.ptAcculateReportHead,
                        ptSndMsg, ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID);
        ptRoReport->tActiveRoReportLink.ptAcculateReportHead = NULL;
        ptRoReport->tActiveRoReportLink.ptActiveRoReportTail = NULL;
        ptRoReport->tActiveRoReportLink.dwReportNum = 0;
        ptRoReport->tActiveRoReportLink.dwReportSize = 0;
    }
}
/**************************************************************************
* 函数名称：llrp_SendReportforRoReportTrigger
* 功能描述：在Ro或者Ai结束时上报报告
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                            
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_sendReportforRoReportTrigger(void *ptPara)
{
    T_Msg *ptSndMsg = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpROReport *ptRoReport = NULL;
    RdpLlrpDbgPrint("(LLRP)Ro send current report to Report module\r\n");
    ptRoReport = (T_RdpLlrpROReport *)ptPara;
    ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    ptSndMsg->ucLinkIndex = ptRoReport->tActiveRoReportLink.ucLinkIndex;
    ptSndMsg->ucLinkType = ptRoReport->tActiveRoReportLink.ucLinkType;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_REPORT_TNO;
    ptSndMsg->wMsgLen = sizeof(T_RdpLlrpSendReportContent);
    ptRunRoCtrlAndPara = llrp_getRunRO();
    if (ptRunRoCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
    }
    ptSndMsg->wSenderTno = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wSenderTno;
    ptSndMsg->wReceiverTno = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wReceiverTno;
    llrp_sendReport(ptRoReport->tActiveRoReportLink.ptAcculateReportHead,
                    ptSndMsg, ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID);

    ptRoReport->tActiveRoReportLink.ptAcculateReportHead = NULL;
    ptRoReport->tActiveRoReportLink.ptActiveRoReportTail = NULL;
    ptRoReport->tActiveRoReportLink.dwReportNum = 0;
    ptRoReport->tActiveRoReportLink.dwReportSize = 0;

}
/**************************************************************************
* 函数名称：llrp_transferToROReportPara
* 功能描述：转换成Ro内部报告存储
* 访问的表：无
* 修改的表：无
* 输入参数：void *ptPara
                             当前运行的Ro的控制结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferToROReportPara(LLRP_tSROReportSpec *ptTempLLRP_tSROReportSpec , T_RdpLlrpROReport *ptTempRoReport)
{
    LLRP_tSC1G2EPCMemorySelector *ptTempLLRP_tSC1G2EPCMemorySelector = NULL;
    ptTempRoReport->tActiveRoReportLink.ptAcculateReportHead = NULL;
    ptTempRoReport->tActiveRoReportLink.ptActiveRoReportTail = NULL;
    if (ptTempLLRP_tSROReportSpec == NULL)
    {
        ptTempRoReport->bIsDefaultCfgFlag = TRUE;
        switch (g_tRdpConfig.tROReportSpec.eROReportTrigger)
        {
        case LLRP_ROReportTriggerType_None:
            ptTempRoReport->wThresholdOfReportNum = 0;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger)llrp_linkReportBufferforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger)llrp_doDefaultforRoReportTrigger;
            break;
        case LLRP_ROReportTriggerType_Upon_N_Tags_Or_End_Of_AISpec:
            ptTempRoReport->wThresholdOfReportNum = g_tRdpConfig.tROReportSpec.wThresholdOfReportNum;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger) llrp_sendReportforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger) llrp_increaseNtagforRoReportTrigger;
            break;

        case LLRP_ROReportTriggerType_Upon_N_Tags_Or_End_Of_ROSpec:
            ptTempRoReport->wThresholdOfReportNum = g_tRdpConfig.tROReportSpec.wThresholdOfReportNum;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger) llrp_sendReportforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger)llrp_increaseNtagforRoReportTrigger;
            break;
        case LLRP_ROReportTriggerType_No_ROReport:
            ptTempRoReport->wThresholdOfReportNum = 0;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger) llrp_sendReportforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger)llrp_doDefaultforRoReportTrigger;
            break;
        default:
            break;
        }

        RdpLlrpDbgPrint("(LLRP)ROReport use default value\r\n");

    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)ROReport does not not use default value\r\n");
        ptTempRoReport->bIsDefaultCfgFlag = FALSE;
        switch (ptTempLLRP_tSROReportSpec->eROReportTrigger)
        {
        case LLRP_ROReportTriggerType_None:
            ptTempRoReport->wThresholdOfReportNum = 0;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger) llrp_linkReportBufferforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger)llrp_doDefaultforRoReportTrigger;
            break;
        case LLRP_ROReportTriggerType_Upon_N_Tags_Or_End_Of_AISpec:
            ptTempRoReport->wThresholdOfReportNum = ptTempLLRP_tSROReportSpec->N;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger) llrp_sendReportforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger) llrp_increaseNtagforRoReportTrigger;
            break;

        case LLRP_ROReportTriggerType_Upon_N_Tags_Or_End_Of_ROSpec:
            ptTempRoReport->wThresholdOfReportNum = ptTempLLRP_tSROReportSpec->N;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger)llrp_sendReportforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger) llrp_increaseNtagforRoReportTrigger;
            break;
        case LLRP_ROReportTriggerType_No_ROReport:
            ptTempRoReport->wThresholdOfReportNum = 0;
            ptTempRoReport->pfusp_rdp_llrp_EndAIForReportTrigger = (usp_rdp_llrp_EndAIForReportTrigger)llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_EndROForReportTrigger = (usp_rdp_llrp_EndROForReportTrigger)llrp_sendReportforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitAIForReportTrigger = (usp_rdp_llrp_InitAIForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_InitROForReportTrigger = (usp_rdp_llrp_InitROForReportTrigger) llrp_doDefaultforRoReportTrigger;
            ptTempRoReport->pfusp_rdp_llrp_JudgeReportNumForReportTrigger = (usp_rdp_llrp_JudgeReportNumForReportTrigger) llrp_doDefaultforRoReportTrigger;
            break;
        default:
            break;

        }
        /*Report Select内容*/
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableAccessSpecID
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableAccessSpecID;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableAntennaID
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableAntennaID;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableChannelIndex
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableChannelIndex;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableFirstSeenTimestamp
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableFirstSeenTimestamp;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableInventoryParameterSpecID
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableInventoryParameterSpecID;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableLastSeenTimestamp
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableLastSeenTimestamp;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnablePeakRSSI
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnablePeakRSSI;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableROSpecID
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableROSpecID;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableSpecIndex
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableSpecIndex;
        ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableTagSeenCount
        = ptTempLLRP_tSROReportSpec->pTagReportContentSelector->EnableTagSeenCount;

        /*陈杰 暂时修改，pc epc目前配置中也没有进行配置*/
        if (NULL != ptTempLLRP_tSROReportSpec \
                ->pTagReportContentSelector->listAirProtocolEPCMemorySelector)
        {
            ptTempLLRP_tSC1G2EPCMemorySelector
            = (LLRP_tSC1G2EPCMemorySelector *)ptTempLLRP_tSROReportSpec \
              ->pTagReportContentSelector->listAirProtocolEPCMemorySelector;
            ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnableCRC
            = ptTempLLRP_tSC1G2EPCMemorySelector->EnableCRC;
            ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnablePC
            = ptTempLLRP_tSC1G2EPCMemorySelector->EnablePCBits;
        }
        else
        {
            ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnablePC = FALSE;
            ptTempRoReport->tRdpLlrpTagReportContentSelector.bEnablePC = FALSE;
        }

    }
}

/**************************************************************************
* 函数名称：llrp_addRo
* 功能描述：添加Ro
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSADD_ROSPEC *ptLLRP_tSADDROSpec 
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_addRo(T_Msg *ptRcvMsg)
{
    unsigned int dwROIndex = 0;
    unsigned int dwAIIndex = 0;
    T_RdpLlrpROCtrlAndParam *ptIdleRoCtrlAndPara = NULL;
    LLRP_tSROSpec *ptLLRP_tSROSpec = NULL;
    LLRP_tSAISpec *ptTempLLRP_tSAISpec = NULL;
    T_RdpLlrpAISet *ptAISet = NULL;

    LLRP_tSADD_ROSPEC *ptLLRP_tSADDROSpec = *(LLRP_tSADD_ROSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_ADD_ROSPEC msg\r\n");
    ptLLRP_tSROSpec = ptLLRP_tSADDROSpec->pROSpec;
    for (dwROIndex = 0; dwROIndex < MAX_NUM_RO_SPEC ; dwROIndex++)
    {
        ptIdleRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
        if (ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == FALSE)
        {
            break;
        }
    }
    if (dwROIndex == MAX_NUM_RO_SPEC)
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
        RdpLlrpDbgPrint("(LLRP)there is not empty space for Ro\r\n");
        llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_A_OutOfRange, EV_ADD_ROSPEC_RESPONSE, ptLLRP_tSADDROSpec->hdr.MessageID, ptLLRP_tSROSpec->ROSpecID);
        return ;
    }
    /*填写内部RO的控制结构*/
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing = TRUE;
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType = ptRcvMsg->ucLinkType;
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wReceiverTno = ptRcvMsg->wReceiverTno;
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wSenderTno = ptRcvMsg->wSenderTno;
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID = ptLLRP_tSADDROSpec->hdr.MessageID;
    ptIdleRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
    /*RO的参数内容*/
    ptIdleRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState = ptLLRP_tSROSpec->eCurrentState;
    ptIdleRoCtrlAndPara->tRdpLlrpROSpec.ucPriority = ptLLRP_tSROSpec->Priority;
    ptIdleRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID = ptLLRP_tSROSpec->ROSpecID;
    RdpLlrpDbgPrint("(LLRP) eCurrentState:%d\r\n", ptIdleRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState);
    RdpLlrpDbgPrint("(LLRP) ucPriority : %d\r\n", ptIdleRoCtrlAndPara->tRdpLlrpROSpec.ucPriority);
    RdpLlrpDbgPrint("(LLRP) dwROSpecID : %d\r\n", ptIdleRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
    RdpLlrpDbgPrint("(LLRP)transfer Ro startTrigger \r\n");
    RdpLlrpDbgPrint("(LLRP)Trigger type :%d\r\n", ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.dwROSpecStartTriggerType);
    llrp_transferROStartTriggerPara(ptLLRP_tSROSpec->pROBoundarySpec->pROSpecStartTrigger,
                                    &ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger);
    RdpLlrpDbgPrint("(LLRP)transfer Ro stopTrigger \r\n");
    llrp_transferROStopTriggerPara(ptLLRP_tSROSpec->pROBoundarySpec->pROSpecStopTrigger,
                                   &ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStopTrigger);
    ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ucLinkType = ptRcvMsg->ucLinkType;
    RdpLlrpDbgPrint("(LLRP)transfer Ro ReportTrigger \r\n");
    llrp_transferToROReportPara(ptLLRP_tSROSpec->pROReportSpec ,
                                &ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport);
    ptTempLLRP_tSAISpec = (LLRP_tSAISpec *)ptLLRP_tSROSpec->listSpecParameter;
    RdpLlrpDbgPrint("(LLRP)ROIndex: %d ,ROID:%d\r\n" , dwROIndex, ptIdleRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
    while (ptTempLLRP_tSAISpec != NULL)
    {
        ptAISet = (T_RdpLlrpAISet *) & ptIdleRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpAISet;
        ptAISet->wAINum++;
        RdpLlrpDbgPrint("(LLRP)the %d Ai change \r\n", ptAISet->wAINum);
        llrp_transferToAISpecPara(ptTempLLRP_tSAISpec, &ptAISet->tRdpLlrpAI[ptAISet->wAINum - 1]);
        ptTempLLRP_tSAISpec = (LLRP_tSAISpec *)ptTempLLRP_tSAISpec->hdr.pNextSubParameter;
    }

    /*同时插入Add队列和Disable队列*/
    RdpLlrpDbgPrint("(LLRP)insert ro into add queue and disable queue\r\n");
    llrp_buildAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tAddQueuehead,
                                   dwROIndex,
                                   ptIdleRoCtrlAndPara->tRdpLlrpROSpec.ucPriority);
    llrp_buildAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tDisableRoQueuehead,
                                   dwROIndex,
                                   ptIdleRoCtrlAndPara->tRdpLlrpROSpec.ucPriority);
    RdpLlrpDbgPrint("(LLRP)send Add_Ro Rsp\r\n");
    llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_ADD_ROSPEC_RESPONSE, ptLLRP_tSADDROSpec->hdr.MessageID, ptLLRP_tSROSpec->ROSpecID);
    RdpLlrpDbgPrint("(LLRP)save dynamic Ro for get_RoRsp\r\n");
    llrp_buildAnNodeFoDynamicRoQueue(&g_tRdpLlrpDynamicRoLinkHead[ptRcvMsg->ucLinkIndex], ptLLRP_tSADDROSpec);
}
/**************************************************************************
* 函数名称：llrp_deleteLocalROPara
* 功能描述：删除RO本地参数和队列
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucLinkIndex,
                             T_RdpLlrpROCtrlAndParam ptRoCtrlAndPara,
                             unsigned int dwROIndex,
                             unsigned int dwPriority
                             unsigned int *pbSendRspFlag,
                             unsigned int dwRuleID
                             unsigned int dwMsgID
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_deleteLocalROPara(T_Msg *ptRcvMsg, T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara, unsigned int dwROIndex, unsigned int dwPriority, unsigned int *pbSendRspFlag, unsigned int dwRuleID, unsigned int dwMsgID)
{
    unsigned int dwDeleteROSpecID = 0;
    dwDeleteROSpecID = ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID;
    RdpLlrpDbgPrint("(LLRP)llrp_deleteLocalROPara dwRuleID =%d dwMsgID=%d\r\n",dwRuleID,dwMsgID);
    if (ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState == LLRP_ROSpecState_Active)
    {
        if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_INACTIVE)
        {
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_STOP_ROSPEC_RESPONSE,
                                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwStopRoMsgID, ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            RdpLlrpDbgPrint("(LLRP)the Ro Id %d has receive an stop msg and need set disable sign \r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DELETE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DISABLE)
        {
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DISABLE_ROSPEC_RESPONSE,
                                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoMsgID, ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoID);
            RdpLlrpDbgPrint("(LLRP)the Ro Id %d has receive an disable msg and need set delete sign \r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DELETE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DELETE)
        {
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DELETE_ROSPEC_RESPONSE,
                                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID, ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID);
            RdpLlrpDbgPrint("(LLRP)the Ro Id %d has receive an delete msg and need set delete sign \r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DELETE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_ACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)delete Ro ID %d State is Active make an sign wait delete\r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DELETE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)Ro other rule msg priority is larger than disable msg need not to deal,dwDispatchStatus is %d\r\n", ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus);
        }

    }
    else
    {
        if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DISABLE)
            /*防止删除Ro之前对ActiveRo进行了disable 操作，这时就要判断当前Ro不是在运行 */
        {
            RdpLlrpDbgPrint("(LLRP)delete Ro State is disable\r\n");
            llrp_findAndFreeAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tDisableRoQueuehead,
                                                 dwROIndex, dwPriority);
            llrp_findAndFreeAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tAddQueuehead,
                                                 dwROIndex, dwPriority);
            memset(ptRoCtrlAndPara, 0, sizeof(T_RdpLlrpROCtrlAndParam));
        }
        else if ( ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_INACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)delete Ro State is inactive \r\n");
            llrp_findAndFreeAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tAddQueuehead,
                                                 dwROIndex, dwPriority);
            llrp_findAndFreeAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead,
                                                 dwROIndex, dwPriority);
            memset(ptRoCtrlAndPara, 0, sizeof(T_RdpLlrpROCtrlAndParam));
            LLRP_STOP_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + dwROIndex);
        }
        else if ( ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_READY)
        {
            RdpLlrpDbgPrint("(LLRP)delete Ro State is ready \r\n");
            llrp_findAndFreeAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tAddQueuehead,
                                                 dwROIndex, dwPriority);
            llrp_findAndFreeAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tReadyRoQueuehead,
                                                 dwROIndex, dwPriority);
            memset(ptRoCtrlAndPara, 0, sizeof(T_RdpLlrpROCtrlAndParam));
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_ACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)delet Ro State is Active make an sign wait delete\r\n");
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DELETE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDeleteRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)delet Ro State is not suported ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus: %d\r\n", ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus);
            /*写入异常*/
            RDP_EXCEPT(RDP_INVALID_STATE, ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus, 0, 0, RDP_LLRP_RULE_ID);
        }
    }

    llrp_deleteAnNodeForDynamicRoQueue(&g_tRdpLlrpDynamicRoLinkHead[ptRcvMsg->ucLinkIndex], dwDeleteROSpecID);

}
/**************************************************************************
* 函数名称：llrp_clearRoListforGetRoRsp
* 功能描述：对于现在存在的动态Ro,首先要从
                             ptLocalLLRP_tSGET_ROSPECS_RESPONSE 上的链表中摘除，
                             否则free时，会相互影响
                           
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucLinkIndex
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
*************************************************************************/
void llrp_clearRoListforGetRoRsp(unsigned char ucLinkIndex)
{

    LLRP_tSROSpec *ptLLRP_tSROSpec = NULL;
    LLRP_tSROSpec *ptFreeLLRP_tSROSpec = NULL;
    if (ptLocalLLRP_tSGET_ROSPECS_RESPONSE != NULL)
    {
        for (ptLLRP_tSROSpec = LLRP_GET_ROSPECS_RESPONSE_beginROSpec(ptLocalLLRP_tSGET_ROSPECS_RESPONSE);
                ptLLRP_tSROSpec != NULL;)
        {
            ptFreeLLRP_tSROSpec = ptLLRP_tSROSpec;
            ptLLRP_tSROSpec = LLRP_GET_ROSPECS_RESPONSE_nextROSpec(ptLLRP_tSROSpec);
            LLRP_Element_removeSubParameterFromAllList((LLRP_tSElement *)ptLocalLLRP_tSGET_ROSPECS_RESPONSE, (LLRP_tSParameter *)ptFreeLLRP_tSROSpec);
        }
        usp_ltk_freeMessage((LLRP_tSMessage *)ptLocalLLRP_tSGET_ROSPECS_RESPONSE);
        ptLocalLLRP_tSGET_ROSPECS_RESPONSE = NULL;
    }

}
/**************************************************************************
* 函数名称：llrp_deleteRo
* 功能描述：删除Ro操作
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSDELETE_ROSPEC  *ptLLRP_tSDELETE_ROSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0       高峰        创建
**************************************************************************/
void llrp_deleteRo(T_Msg *ptRcvMsg)
{
    unsigned int bSendRspFlag = TRUE;
    unsigned int dwROIndex = 0;
    T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara = NULL;
    LLRP_tSDELETE_ROSPEC *ptLLRP_tSDELETE_ROSPEC = *(LLRP_tSDELETE_ROSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_DELETE_ROSPEC msg RoID %d\r\n", ptLLRP_tSDELETE_ROSPEC->ROSpecID);
    llrp_clearRoListforGetRoRsp(ptRcvMsg->ucLinkIndex);
    if (ptLLRP_tSDELETE_ROSPEC->ROSpecID == 0)
    {
        for (dwROIndex = 0;dwROIndex < MAX_NUM_RO_SPEC;dwROIndex++)
        {
            ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType)
            {
                llrp_deleteLocalROPara(ptRcvMsg, ptRoCtrlAndPara, dwROIndex, ptRoCtrlAndPara->tRdpLlrpROSpec.ucPriority,
                                       &bSendRspFlag, ptLLRP_tSDELETE_ROSPEC->ROSpecID, ptLLRP_tSDELETE_ROSPEC->hdr.MessageID);
            }
        }

    }
    else
    {
        for (dwROIndex = 0;dwROIndex < MAX_NUM_RO_SPEC;dwROIndex++)
        {
            ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType
                    && ptLLRP_tSDELETE_ROSPEC->ROSpecID == ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID)
            {
                break;
            }
        }
        if ( dwROIndex == MAX_NUM_RO_SPEC)
        {
            RDP_EXCEPT(RDP_INVALID_STATE, ptLLRP_tSDELETE_ROSPEC->ROSpecID, 0, 0, RDP_LLRP_RULE_ID);
            RdpLlrpDbgPrint("(LLRP)delete Ro :%d is not in Reader\r\n", ptLLRP_tSDELETE_ROSPEC->ROSpecID);
        }
        else
        {
            llrp_deleteLocalROPara(ptRcvMsg, ptRoCtrlAndPara, dwROIndex, ptRoCtrlAndPara->tRdpLlrpROSpec.ucPriority,
                                   &bSendRspFlag, ptLLRP_tSDELETE_ROSPEC->ROSpecID, ptLLRP_tSDELETE_ROSPEC->hdr.MessageID);
        }
    }
    if (bSendRspFlag == TRUE)
    {
        RdpLlrpDbgPrint("(LLRP)bSendRspFlag is true\r\n");
        llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DELETE_ROSPEC_RESPONSE,
                            ptLLRP_tSDELETE_ROSPEC->hdr.MessageID, ptLLRP_tSDELETE_ROSPEC->ROSpecID);
    }

    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSDELETE_ROSPEC);
}
/**************************************************************************
* 函数名称：llrp_enableRo
* 功能描述：使能Ro
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                               LLRP_tSENABLE_ROSPEC  *ptLLRP_tSENABLE_ROSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_enableRo(T_Msg *ptRcvMsg)
{
    unsigned int dwROIndex = 0;
    T_RdpLlrpROEntry *ptInsertNode = NULL;
    T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara = NULL;
    LLRP_tSENABLE_ROSPEC *ptLLRP_tSENABLE_ROSPEC = *(LLRP_tSENABLE_ROSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_ENABLE_ROSPEC msg RoID %d\r\n", ptLLRP_tSENABLE_ROSPEC->ROSpecID);
    if (ptLLRP_tSENABLE_ROSPEC->ROSpecID == 0)
    {
        for (dwROIndex = 0;dwROIndex < MAX_NUM_RO_SPEC;dwROIndex++)
        {

            ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType
                    && ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DISABLE
                    && ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState == LLRP_ROSpecState_Disabled)
            {
                ptInsertNode = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tDisableRoQueuehead,
                               dwROIndex, ptRoCtrlAndPara->tRdpLlrpROSpec.ucPriority);
                if (ptInsertNode != NULL)
                {
                    RdpLlrpDbgPrint("(LLRP)insert RoId %d,Roindex :%d  into RoInactiveQueue\r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID, ptInsertNode->dwROIndex);
                    llrp_insertAnNodetoAllQueueOfRO(ptInsertNode, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead);
                }
                else
                {
                    RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
                }
                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_INACTIVE;
                ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState = LLRP_ROSpecState_Inactive;
                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID = ptLLRP_tSENABLE_ROSPEC->hdr.MessageID ;
                ptRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.pfusp_rdp_llrp_EnableStartTrigger((void *)ptInsertNode);
            }
        }
    }
    else
    {
        for (dwROIndex = 0;dwROIndex < MAX_NUM_RO_SPEC;dwROIndex++)
        {
            ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType
                    && ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DISABLE
                    && ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState == LLRP_ROSpecState_Disabled
                    && ptLLRP_tSENABLE_ROSPEC->ROSpecID == ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID)
            {
                break;
            }
        }
        if ( dwROIndex == MAX_NUM_RO_SPEC)
        {
            RdpLlrpDbgPrint("(LLRP)enable Ro :%d is not in Reader\r\n", ptLLRP_tSENABLE_ROSPEC->ROSpecID);
        }
        else
        {
            ptInsertNode = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tDisableRoQueuehead,
                           dwROIndex, ptRoCtrlAndPara->tRdpLlrpROSpec.ucPriority);
            if (ptInsertNode != NULL)
            {
                RdpLlrpDbgPrint("(LLRP)insert RoId %d,Roindex :%d  into RoInactiveQueue\r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID, ptInsertNode->dwROIndex);
                llrp_insertAnNodetoAllQueueOfRO(ptInsertNode, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead);
            }
            else
            {
                RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
            }
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_INACTIVE;
            ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState = LLRP_ROSpecState_Inactive;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID = ptLLRP_tSENABLE_ROSPEC->hdr.MessageID ;
            ptRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.pfusp_rdp_llrp_EnableStartTrigger((void *)ptInsertNode);
        }
    }
    llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_ENABLE_ROSPEC_RESPONSE, ptLLRP_tSENABLE_ROSPEC->hdr.MessageID, ptLLRP_tSENABLE_ROSPEC->ROSpecID);
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSENABLE_ROSPEC);
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        RdpLlrpDbgPrint("(LLRP)there is not active ro need scan ready queue\r\n");
        g_tRdpLlrpReaderDispatch.pfScanROToRun(g_tRdpLlrpReaderDispatch.ptReaderRoSpecData);
    }
}
/**************************************************************************
* 函数名称：llrp_disableLocalRoPara
* 功能描述：disableRo队列和状态
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg,
                             T_RdpLlrpROCtrlAndParam ptRoCtrlAndPara,
                             unsigned int dwROIndex,
                             unsigned int dwPriority
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_disableLocalRoPara(T_Msg *ptRcvMsg, T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara, unsigned int dwROIndex, unsigned int dwPriority, unsigned int *pbSendRspFlag, unsigned int dwRuleID, unsigned int dwMsgID)
{
    T_RdpLlrpROEntry *ptInsertNode = NULL;
    /*如果是Ro的状态是Active 而调度状态
      不是LLRP_RODISPATCH_STATE_ACTIVE 
      说明在disable命令之前还有其他指令*/
    if (ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState == LLRP_ROSpecState_Active)
    {
        if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_INACTIVE)
        {
            /*这种情况是activeRo收到了stop消息后，
            又收到了disable消息，那么首先回应stop消息应答然后处理disable消息*/
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_STOP_ROSPEC_RESPONSE,
                                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwStopRoMsgID, ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            RdpLlrpDbgPrint("(LLRP)the Ro Id %d has receive an stop msg and need set disable sign \r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DISABLE)
        {
            /*这种情况是activeRo收到了disable消息后，
            又收到了disable消息，那么首先回应先前的disable消息应答然后处理disable消息*/
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DISABLE_ROSPEC_RESPONSE,
                                ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoMsgID, ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoID);
            RdpLlrpDbgPrint("(LLRP)the Ro Id %d has receive an disable msg and need set disable sign \r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else if ( ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_ACTIVE)
        {
            /*收到了disable消息或者是delete消息，都忽略但是可能后者的消息号在上一个消息之前回应*/
            RdpLlrpDbgPrint("(LLRP)disable Ro ID %d  State is Active make an sign wait disable\r\n", ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID);
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)Ro other rule msg priority is larger than disable msg need not to deal,dwDispatchStatus is %d\r\n", ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus);
        }
    }
    else
    {
        if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_DISABLE)
        {
            RdpLlrpDbgPrint("(LLRP)disable Ro State is disable\r\n");
        }
        else if ( ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_INACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)disable Ro State is inactive \r\n");
            ptInsertNode = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead,
                           dwROIndex, dwPriority);
            if (ptInsertNode != NULL)
            {
                llrp_insertAnNodetoAllQueueOfRO(ptInsertNode, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tDisableRoQueuehead);
            }
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
            ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState = LLRP_ROSpecState_Disabled;
            LLRP_STOP_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + dwROIndex);
        }
        else if ( ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_READY)
        {
            RdpLlrpDbgPrint("(LLRP)disable Ro State is Ready \r\n");
            ptInsertNode = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tReadyRoQueuehead,
                           dwROIndex, dwPriority);
            if (ptInsertNode != NULL)
            {
                llrp_insertAnNodetoAllQueueOfRO(ptInsertNode, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tDisableRoQueuehead);
            }
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
            ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState = LLRP_ROSpecState_Disabled;
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_ACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)disable Ro State is Active make an sign wait disable\r\n");
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_DISABLE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoID = dwRuleID;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDisableRoMsgID = dwMsgID;
            *pbSendRspFlag = FALSE;
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)disable Ro State is not suported \r\n");
            /*写入异常*/
            RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
        }

    }

}
/**************************************************************************
* 函数名称：llrp_disableRo
* 功能描述：反使能Ro
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSDISABLE_ROSPEC *ptLLRP_tSDISABLE_ROSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_disableRo(T_Msg *ptRcvMsg)
{
    unsigned int bSendRspFlag = TRUE;
    unsigned int dwROIndex = 0;
    T_RdpLlrpROEntry *ptInsertNode = NULL;
    T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara = NULL;
    LLRP_tSDISABLE_ROSPEC *ptLLRP_tSDISABLE_ROSPEC = *(LLRP_tSDISABLE_ROSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_DISABLE_ROSPEC msg RoID %d\r\n", ptLLRP_tSDISABLE_ROSPEC->ROSpecID);
    if (ptLLRP_tSDISABLE_ROSPEC->ROSpecID == 0)
    {
        for (dwROIndex = 0;dwROIndex < MAX_NUM_RO_SPEC;dwROIndex++)
        {

            ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType )
            {
                llrp_disableLocalRoPara(ptRcvMsg, ptRoCtrlAndPara, dwROIndex, ptRoCtrlAndPara->tRdpLlrpROSpec.ucPriority,
                                        &bSendRspFlag, ptLLRP_tSDISABLE_ROSPEC->ROSpecID, ptLLRP_tSDISABLE_ROSPEC->hdr.MessageID);
            }
        }
    }
    else
    {
        for (dwROIndex = 0;dwROIndex < MAX_NUM_RO_SPEC;dwROIndex++)
        {
            ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType
                    && ptLLRP_tSDISABLE_ROSPEC->ROSpecID == ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID)
            {
                break;
            }
        }
        if ( dwROIndex == MAX_NUM_RO_SPEC)
        {
            RdpLlrpDbgPrint("(LLRP)enable Ro :%d is not in Reader\r\n", ptLLRP_tSDISABLE_ROSPEC->ROSpecID);
        }
        else
        {
            llrp_disableLocalRoPara(ptRcvMsg, ptRoCtrlAndPara, dwROIndex, ptRoCtrlAndPara->tRdpLlrpROSpec.ucPriority,
                                    &bSendRspFlag, ptLLRP_tSDISABLE_ROSPEC->ROSpecID, ptLLRP_tSDISABLE_ROSPEC->hdr.MessageID);

        }
    }
    if (bSendRspFlag == TRUE)
    {
        llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DISABLE_ROSPEC_RESPONSE,
                            ptLLRP_tSDISABLE_ROSPEC->hdr.MessageID, ptLLRP_tSDISABLE_ROSPEC->ROSpecID);
    }
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSDISABLE_ROSPEC);
}

/**************************************************************************
* 函数名称：llrp_startRo
* 功能描述：开始Ro
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSSTART_ROSPEC *ptLLRP_tSSTART_ROSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_startRo(T_Msg *ptRcvMsg)
{
    T_RdpLlrpROEntry *ptRoCursor = NULL;
    T_RdpLlrpROEntry *ptInsertNode = NULL;
    T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara = NULL;
    LLRP_tSSTART_ROSPEC *ptLLRP_tSSTART_ROSPEC = *(LLRP_tSSTART_ROSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_START_ROSPEC msg RoID %d\r\n", ptLLRP_tSSTART_ROSPEC->ROSpecID);
    for (ptRoCursor = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead.ptNext;
            ptRoCursor != NULL;ptRoCursor = ptRoCursor->ptNext)
    {
        ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptRoCursor->dwROIndex];
        if (ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType
                && ptLLRP_tSSTART_ROSPEC->ROSpecID == ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID)
        {
            break;
        }
    }
    /*这里是不是应该校验一下Ready队列不用了这里直接返回成功就行，
    因为rule模块会先回应应答消息，会保证Ro是可以开始的，
    这里的工作只是找到inactive队列中的RO转到ready*/
    if ( ptRoCursor == NULL )
    {
        RdpLlrpDbgPrint("(LLRP)start Ro :%d is not in Reader\r\n", ptLLRP_tSSTART_ROSPEC->ROSpecID);
    }
    else
    {
        ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID = ptLLRP_tSSTART_ROSPEC->hdr.MessageID ;
        llrp_transferInactiveRotoReadyRo((void *)ptRoCursor);
    }
    llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_START_ROSPEC_RESPONSE, ptLLRP_tSSTART_ROSPEC->hdr.MessageID, ptLLRP_tSSTART_ROSPEC->ROSpecID);
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSSTART_ROSPEC);
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        RdpLlrpDbgPrint("(LLRP)there is not active ro need scan ready queue\r\n");
        g_tRdpLlrpReaderDispatch.pfScanROToRun(g_tRdpLlrpReaderDispatch.ptReaderRoSpecData);
    }
}
/**************************************************************************
* 函数名称：llrp_stopRo
* 功能描述：停止Ro
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSSTART_ROSPEC *ptLLRP_tSSTART_ROSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_stopRo(T_Msg *ptRcvMsg)
{
    T_RdpLlrpROEntry *ptRoCursor = NULL;
    T_RdpLlrpROEntry *ptInsertNode = NULL;
    T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara = NULL;
    LLRP_tSSTOP_ROSPEC *ptLLRP_tSSTOP_ROSPEC = *(LLRP_tSSTOP_ROSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_STOP_ROSPEC msg RoID %d\r\n", ptLLRP_tSSTOP_ROSPEC->ROSpecID);
    for (ptRoCursor = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tAddQueuehead.ptNext;
            ptRoCursor != NULL;ptRoCursor = ptRoCursor->ptNext)
    {
        ptRoCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptRoCursor->dwROIndex];
        if (ptRcvMsg->ucLinkIndex == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex
                && ptRcvMsg->ucLinkType == ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType
                && ptLLRP_tSSTOP_ROSPEC->ROSpecID == ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID)
        {
            break;
        }
    }
    if ( ptRoCursor == NULL )
    {
        RdpLlrpDbgPrint("(LLRP)stop Ro :%d is not in Reader\r\n", ptLLRP_tSSTOP_ROSPEC->ROSpecID);
    }
    else
    {
        if ( ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_READY)
        {
            ptInsertNode = llrp_findAndGetAnNodeFoAllQueueOfRO(&g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tReadyRoQueuehead,
                           ptRoCursor->dwROIndex, ptRoCursor->dwPriority);
            if (ptInsertNode != NULL)
            {
                llrp_insertAnNodetoAllQueueOfRO(ptInsertNode, &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tInactiveRoQueuehead);
            }
            else
            {
                RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
            }
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_INACTIVE;
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_STOP_ROSPEC_RESPONSE, ptLLRP_tSSTOP_ROSPEC->hdr.MessageID, ptLLRP_tSSTOP_ROSPEC->ROSpecID);
        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_ACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)stop Ro State is Active make an sign wait stop\r\n");
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_INACTIVE;
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwStopRoMsgID = ptLLRP_tSSTOP_ROSPEC->hdr.MessageID;

        }
        else if (ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus == LLRP_RODISPATCH_STATE_INACTIVE)
        {
            RdpLlrpDbgPrint("(LLRP)stop Ro State is inactive need delet timer for period Ro\r\n");
            ptRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwStopRoMsgID = ptLLRP_tSSTOP_ROSPEC->hdr.MessageID;
            /*对于周期性的Ro来说，要停止定时器要不然会影响后面的相同ROid的运行行为*/
            LLRP_STOP_TIMER(EV_RDP_LLRP_RULETIMER_BEGIN + ptRoCursor->dwROIndex);    
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_STOP_ROSPEC_RESPONSE, ptLLRP_tSSTOP_ROSPEC->hdr.MessageID, ptLLRP_tSSTOP_ROSPEC->ROSpecID);
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)stop Ro State is not suported \r\n");
            /*写入异常*/
            RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
            llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_STOP_ROSPEC_RESPONSE, ptLLRP_tSSTOP_ROSPEC->hdr.MessageID, ptLLRP_tSSTOP_ROSPEC->ROSpecID);
        }
    }
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSSTOP_ROSPEC);
}
/**************************************************************************
* 函数名称：llrp_doDefaultforAOStopTrigger
* 功能描述：AOstopTrigger的默认行为
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessStopTrigger *ptAccessStopTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_initforAOStopTrigger(void *ptPara)
{
    T_RdpLlrpAccessCtrlAndParam *ptRunAccessCtrlAndPara = NULL;
    ptRunAccessCtrlAndPara = (T_RdpLlrpAccessCtrlAndParam *)ptPara;
    ptRunAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_ACTIVE;
    T_RdpLlrpAccess *ptAccess = (T_RdpLlrpAccess *) & ptRunAccessCtrlAndPara->tRdpLlrpAccess;
    ptAccess->tRdpLlrpAccessCmdCtrl.tRdpLlrpListOPCtrlSet.wOpIndex = 0;
    ptAccess->tRdpLlrpAccessCmdCtrl.bClientRequest = FALSE;
    memset(g_ucLocalReportDataBuffer, 0, sizeof(g_ucLocalReportDataBuffer));

}

/**************************************************************************
* 函数名称：llrp_doDefaultforIncreaseConditionAndJudeEndAOStopTrigger
* 功能描述：AOstopTrigger的默认行为
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessStopTrigger *ptAccessStopTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned int llrp_doDefaultforIncreaseConditionAndJudeEndAOStopTrigger(void *ptPara)
{
    return LLRP_ACCESS_CONTINUE_DO;

}

/**************************************************************************
* 函数名称：llrp_AccessOperationTimesForinitAOStopTrigger
* 功能描述：对于AOstopTrigger为执行次数的初始化处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessStopTrigger *ptAccessStopTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_AccessOperationTimesForinitAOStopTrigger(void *ptPara)
{

    T_RdpLlrpAccessCtrlAndParam *ptRunAccessCtrlAndPara = NULL;
    ptRunAccessCtrlAndPara = (T_RdpLlrpAccessCtrlAndParam *)ptPara;
    ptRunAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_ACTIVE;
    T_RdpLlrpAccess *ptAccess = (T_RdpLlrpAccess *) & ptRunAccessCtrlAndPara->tRdpLlrpAccess;
    T_RdpLlrpAccessStopTrigger * ptAccessStopTrigger = (T_RdpLlrpAccessStopTrigger *) & ptAccess->tRdpLlrpAccessStopTrigger;
    ptAccess->tRdpLlrpAccessCmdCtrl.tRdpLlrpListOPCtrlSet.wOpIndex = 0;
    ptAccess->tRdpLlrpAccessCmdCtrl.bClientRequest = FALSE;
    memset(g_ucLocalReportDataBuffer, 0, sizeof(g_ucLocalReportDataBuffer));
}
/**************************************************************************
* 函数名称：llrp_AccessOperationTimesForIncreaseAndJudgeEndAO
* 功能描述：对于AOstopTrigger为执行次数的初始条件积累处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessStopTrigger *ptAccessStopTrigger
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
unsigned int llrp_AccessOperationTimesForIncreaseAndJudgeEndAO(void *ptPara)
{
    T_RdpLlrpAccessStopTrigger * ptAccessStopTrigger = (T_RdpLlrpAccessStopTrigger *)ptPara;
    ptAccessStopTrigger->tRdpLlrpAccessParamStopTrigger.wCurrentOperationValue ++;
    RdpLlrpDbgPrint("(LLRP)wCurrentOperationValue:%d ,wOperationCountValue:%d\r\n",
                    ptAccessStopTrigger->tRdpLlrpAccessParamStopTrigger.wCurrentOperationValue,
                    ptAccessStopTrigger->tRdpLlrpAccessParamStopTrigger.wOperationCountValue);
    if (ptAccessStopTrigger->tRdpLlrpAccessParamStopTrigger.wCurrentOperationValue
            >= ptAccessStopTrigger->tRdpLlrpAccessParamStopTrigger.wOperationCountValue)
    {
        return LLRP_ACCESS_DELETE;
    }
    else
    {
        return LLRP_ACCESS_CONTINUE_DO;
    }
}
/**************************************************************************
* 函数名称：llrp_AccessOperationTimesForIncreaseAndJudgeEndAO
* 功能描述：对于AOstopTrigger为执行次数的初始条件积累处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_insertAOReportToRunRoReportLink(T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl)
{
    /*分配地址并出入到当前运行RO的报告链表*/
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    llrp_insertReportToRunRoReportLink(ptLocalAccessReportCtrl);
    ptRunRoCtrlAndPara = llrp_getRunRO();
    if (ptRunRoCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
    }
    ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport \
    .pfusp_rdp_llrp_JudgeReportNumForReportTrigger((void *)&ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport);
}
/**************************************************************************
* 函数名称：llrp_sendAOReportImdiate
* 功能描述：AO规则中的报告立即上报
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_sendAOReportImdiate(T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl )
{
    /*分配地址并出入到当前运行RO的报告链表*/
    unsigned int dwSndMessageID;
    T_RdpLlrpSingleReportCtrl *ptMallocSingleReportCtr = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptRunAccessCtrl = NULL;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    RdpLlrpDbgPrint("(LLRP)Ao ReportTrigger is imdiate need send Report now\r\n");
    ptMallocSingleReportCtr = malloc( struct_fixed_len(T_RdpLlrpSingleReportCtrl, tRdpLlrpTagReport) + ptLocalAccessReportCtrl->wMsgLen);
    /*直接拷贝内存区域*/
    memcpy(ptMallocSingleReportCtr,
           ptLocalAccessReportCtrl,
           struct_fixed_len(T_RdpLlrpSingleReportCtrl, tRdpLlrpTagReport) + ptLocalAccessReportCtrl->wMsgLen);
    ptRunAccessCtrl = llrp_getRunAccess();
    if (ptRunAccessCtrl == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
    }
    ptSndMsg->mtype = 1;
    ptSndMsg->ucLinkIndex = ptRunAccessCtrl->tRdpLlrpAccessDispatchCtrl.ucLinkIndex;
    ptSndMsg->ucLinkType = ptRunAccessCtrl->tRdpLlrpAccessDispatchCtrl.ucLinkType;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_REPORT_TNO;
    ptSndMsg->wSenderTno = ptRunAccessCtrl->tRdpLlrpAccessDispatchCtrl.wSenderTno;
    ptSndMsg->wReceiverTno = ptRunAccessCtrl->tRdpLlrpAccessDispatchCtrl.wReceiverTno;
    if(ptRunAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwReportTrigger ==  LLRP_AccessReportTriggerType_Whenever_ROReport_Is_Generated)
    {
         dwSndMessageID = llrp_getRunRoMsgID();
    }
    else
    {
        dwSndMessageID =  ptRunAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwMessageID;
    }
    llrp_sendReport(ptMallocSingleReportCtr, ptSndMsg,dwSndMessageID);
}
/**************************************************************************
* 函数名称：llrp_transferAccessEpcPatternPara
* 功能描述：转换Epc的匹配内容
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSC1G2TagSpec *pLLRP_tSC1G2TagSpec,
                             llrp动态匹配结构
                            T_RdpLlrpAirProtocolTagCtrl* ptLocalEpcTagPattern
                            本地保存结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferAccessEpcPatternPara( LLRP_tSC1G2TagSpec *pLLRP_tSC1G2TagSpec, T_RdpLlrpAirProtocolTagCtrl* ptLocalEpcTagPattern)
{
    unsigned int dwTestIndex = 0;
    T_RdpLlrpC1G2TargetTag *ptTempC1G2TargetTag = NULL;
    LLRP_tSC1G2TargetTag *ptTempLLRP_tSC1G2TargetTag = NULL;
    ptTempLLRP_tSC1G2TargetTag = (LLRP_tSC1G2TargetTag *) pLLRP_tSC1G2TagSpec->listC1G2TargetTag;
    while (ptTempLLRP_tSC1G2TargetTag != NULL)
    {
        ptLocalEpcTagPattern->dwTagPatternNum ++;
        ptTempC1G2TargetTag = (T_RdpLlrpC1G2TargetTag *) & ptLocalEpcTagPattern->tTagPattern[ ptLocalEpcTagPattern->dwTagPatternNum - 1];
        ptTempC1G2TargetTag->ucMB = ptTempLLRP_tSC1G2TargetTag->MB;
        ptTempC1G2TargetTag->bMatch = ptTempLLRP_tSC1G2TargetTag->Match;
        ptTempC1G2TargetTag->wPointer = ptTempLLRP_tSC1G2TargetTag->Pointer;
        /*掩码和数据 都写在缓冲区内 方便管理*/
        ptTempC1G2TargetTag->tRdpLlrpMatchParam.wMaskBitCount = ptTempLLRP_tSC1G2TargetTag->TagMask.nBit;
        RdpLlrpDbgPrint("(LLRP)this is  %d Epc pattern\r\n" , ptLocalEpcTagPattern->dwTagPatternNum);
        RdpLlrpDbgPrint("(LLRP) MB   %d\r\n", ptTempC1G2TargetTag->ucMB);
        RdpLlrpDbgPrint("(LLRP) Match  %d\r\n", ptTempC1G2TargetTag->bMatch);
        RdpLlrpDbgPrint("(LLRP) Pointer  %d\r\n", ptTempC1G2TargetTag->wPointer);
        RdpLlrpDbgPrint("(LLRP) MaskBitCount  %d\r\n", ptTempC1G2TargetTag->tRdpLlrpMatchParam.wMaskBitCount);
        memcpy(ptTempC1G2TargetTag->tRdpLlrpMatchParam.aucTagData,
               ptTempLLRP_tSC1G2TargetTag->TagMask.pValue,
               BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagMask.nBit));

        RdpLlrpDbgPrint("(LLRP)tagmask:");
        for (dwTestIndex = 0;dwTestIndex < BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagMask.nBit); dwTestIndex++)
        {

            RdpDbgPrintRaw("0x%2x ", ptTempC1G2TargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempC1G2TargetTag->tRdpLlrpMatchParam.wDataBitCount = ptTempLLRP_tSC1G2TargetTag->TagData.nBit;
        memcpy(ptTempC1G2TargetTag->tRdpLlrpMatchParam.aucTagData + BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagMask.nBit),
               ptTempLLRP_tSC1G2TargetTag->TagData.pValue, BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagData.nBit));
        RdpLlrpDbgPrint("(LLRP)tagdata:");
        for (dwTestIndex = BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagMask.nBit);
                dwTestIndex < (BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagMask.nBit) + BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2TargetTag->TagData.nBit));
                dwTestIndex++)
        {
            RdpDbgPrintRaw("0x%2x ", ptTempC1G2TargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempLLRP_tSC1G2TargetTag = (LLRP_tSC1G2TargetTag *)ptTempLLRP_tSC1G2TargetTag->hdr.pNextSubParameter;

    }
    /*赋值长度*/
}
/**************************************************************************
* 函数名称：llrp_transferAccessISO6BPatternPara
* 功能描述：转换ISO6B的匹配的内容
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSISO6BTagSpec *ptLLRP_tSISO6BTagSpec,
                             后台下发的ISO匹配模板参数
                            T_RdpLlrpAirProtocolTagCtrl* ptLocalISO6BTagPattern
                            本地结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferAccessISO6BPatternPara( LLRP_tSISO6BTagSpec *ptLLRP_tSISO6BTagSpec, T_RdpLlrpAirProtocolTagCtrl* ptLocalISO6BTagPattern)
{
    unsigned int dwTestIndex = 0;
    LLRP_tSISO6BTargetTag *ptTempLLRP_tSISO6BTargetTag = NULL;
    T_RdpLlrpISO6BTargetTag *ptTempISO6BTargetTag = NULL;
    ptTempLLRP_tSISO6BTargetTag = (LLRP_tSISO6BTargetTag *)ptLLRP_tSISO6BTagSpec->listISO6BTargetTag;
    while (ptTempLLRP_tSISO6BTargetTag != NULL)
    {
        ptLocalISO6BTagPattern->dwTagPatternNum ++;
        ptTempISO6BTargetTag = (T_RdpLlrpISO6BTargetTag *) & ptLocalISO6BTagPattern->tTagPattern[ ptLocalISO6BTagPattern->dwTagPatternNum - 1];
        ptTempISO6BTargetTag->wBytePtr = ptTempLLRP_tSISO6BTargetTag->BytePtr;
        ptTempISO6BTargetTag->bMatch = ptTempLLRP_tSISO6BTargetTag->Match;
        RdpLlrpDbgPrint("(LLRP)this is  %d ISO6B pattern\r\n" , ptLocalISO6BTagPattern->dwTagPatternNum);
        RdpLlrpDbgPrint("(LLRP)BytePtr:%d\r\n" , ptTempISO6BTargetTag->wBytePtr);
        RdpLlrpDbgPrint("(LLRP)bMatch:%d\r\n" , ptTempISO6BTargetTag->bMatch);
        ptTempISO6BTargetTag->tRdpLlrpMatchParam.wMaskBitCount = ptTempLLRP_tSISO6BTargetTag->TagMask.nBit * 8;

        for (dwTestIndex = 0; dwTestIndex < ptTempLLRP_tSISO6BTargetTag->TagMask.nBit; dwTestIndex++)
        {
            if (((ptTempLLRP_tSISO6BTargetTag->TagMask.pValue[0] << dwTestIndex) & 0x80) != 0)
            {
                ptTempISO6BTargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex] = 0xff;
            }
            else
            {
                ptTempISO6BTargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex] = 0x00;
            }
        }
        memcpy(ptTempISO6BTargetTag->tRdpLlrpMatchParam.aucTagData + ptTempLLRP_tSISO6BTargetTag->TagMask.nBit,
               ptTempLLRP_tSISO6BTargetTag->TagData.pValue,
               ptTempLLRP_tSISO6BTargetTag->TagData.nValue);
        RdpLlrpDbgPrint("(LLRP)tagmask:");
        for (dwTestIndex = 0;dwTestIndex < ptTempLLRP_tSISO6BTargetTag->TagMask.nBit; dwTestIndex++)
        {

            RdpDbgPrintRaw("0x%02x ", ptTempISO6BTargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        RdpLlrpDbgPrint("(LLRP)tagdata:");
        ptTempISO6BTargetTag->tRdpLlrpMatchParam.wDataBitCount = ptTempLLRP_tSISO6BTargetTag->TagData.nValue * 8;
        for (dwTestIndex = ptTempLLRP_tSISO6BTargetTag->TagMask.nBit;dwTestIndex < ptTempLLRP_tSISO6BTargetTag->TagMask.nBit + ptTempLLRP_tSISO6BTargetTag->TagData.nValue; dwTestIndex++)
        {

            RdpDbgPrintRaw("0x%02x ", ptTempISO6BTargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempLLRP_tSISO6BTargetTag = (LLRP_tSISO6BTargetTag *)ptTempLLRP_tSISO6BTargetTag->hdr.pNextSubParameter;

    }
}
/**************************************************************************
* 函数名称：llrp_transferAccessGBPatternPara
* 功能描述：转换GB的匹配内容
* 访问的表：无
* 修改的表：无
* 输入参数：LLRP_tSGBTagSpec *pLLRP_tSGBTagSpec,
                             llrp动态匹配结构
                            T_RdpLlrpAirProtocolTagCtrl* ptLocalGBTagPattern
                            本地保存结构
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferAccessGBPatternPara( LLRP_tSGBTagSpec *pLLRP_tSGBTagSpec, T_RdpLlrpAirProtocolTagCtrl* ptLocalGBTagPattern)
{
    unsigned int dwTestIndex = 0;
    T_RdpLlrpGBTargetTag *ptTempGBTargetTag = NULL;
    LLRP_tSGBTargetTag *ptTempLLRP_tSGBTargetTag = NULL;
    ptTempLLRP_tSGBTargetTag = (LLRP_tSGBTargetTag *) pLLRP_tSGBTagSpec->listGBTargetTag;
    while (ptTempLLRP_tSGBTargetTag != NULL)
    {
        ptLocalGBTagPattern->dwTagPatternNum++;
        ptTempGBTargetTag = (T_RdpLlrpGBTargetTag *) & ptLocalGBTagPattern->tTagPattern[ ptLocalGBTagPattern->dwTagPatternNum - 1];
        ptTempGBTargetTag->ucMB = ptTempLLRP_tSGBTargetTag->MB;
        ptTempGBTargetTag->bMatch = ptTempLLRP_tSGBTargetTag->Match;
        ptTempGBTargetTag->wPointer = ptTempLLRP_tSGBTargetTag->Pointer;
        /*掩码和数据 都写在缓冲区内 方便管理*/
        ptTempGBTargetTag->tRdpLlrpMatchParam.wMaskBitCount = ptTempLLRP_tSGBTargetTag->TagMask.nBit;
        RdpLlrpDbgPrint("(LLRP)this is  %d GB pattern\r\n" , ptLocalGBTagPattern->dwTagPatternNum);
        RdpLlrpDbgPrint("(LLRP) MB   %d\r\n", ptTempGBTargetTag->ucMB);
        RdpLlrpDbgPrint("(LLRP) Match  %d\r\n", ptTempGBTargetTag->bMatch);
        RdpLlrpDbgPrint("(LLRP) Pointer  %d\r\n", ptTempGBTargetTag->wPointer);
        RdpLlrpDbgPrint("(LLRP) MaskBitCount  %d\r\n", ptTempGBTargetTag->tRdpLlrpMatchParam.wMaskBitCount);
        memcpy(ptTempGBTargetTag->tRdpLlrpMatchParam.aucTagData,
               ptTempLLRP_tSGBTargetTag->TagMask.pValue,
               BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagMask.nBit));

        RdpLlrpDbgPrint("(LLRP)tagmask:");
        for (dwTestIndex = 0;dwTestIndex < BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagMask.nBit); dwTestIndex++)
        {

            RdpDbgPrintRaw("0x%2x ", ptTempGBTargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempGBTargetTag->tRdpLlrpMatchParam.wDataBitCount = ptTempLLRP_tSGBTargetTag->TagData.nBit;
        memcpy(ptTempGBTargetTag->tRdpLlrpMatchParam.aucTagData + BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagMask.nBit),
               ptTempLLRP_tSGBTargetTag->TagData.pValue, BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagData.nBit));
        RdpLlrpDbgPrint("(LLRP)tagdata:");
        for (dwTestIndex = BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagMask.nBit);
                dwTestIndex < (BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagMask.nBit) + BIT_CHANGETO_BYTE(ptTempLLRP_tSGBTargetTag->TagData.nBit));
                dwTestIndex++)
        {
            RdpDbgPrintRaw("0x%2x ", ptTempGBTargetTag->tRdpLlrpMatchParam.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempLLRP_tSGBTargetTag = (LLRP_tSGBTargetTag *)ptTempLLRP_tSGBTargetTag->hdr.pNextSubParameter;

    }
    /*赋值长度*/
}
/**************************************************************************
* 函数名称：llrp_transferAccessEpcOpPara
* 功能描述：转换Epc的相应的Op操作到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferAccessEpcOpPara( T_RdpLlrpListOPCtrlSet *ptListOpSet, LLRP_tSParameter *ptTempParameter)
{
    unsigned int dwOpNum = 0;
    unsigned short int wOpIndex = 0;
    unsigned int dwTestIndex = 0;
    LLRP_tSParameter *ptTempLLRP_tSParameter = NULL;
    LLRP_tSC1G2ReadCustomUID *ptTempLLRP_tSC1G2ReadCustomUID = NULL;
    LLRP_tSC1G2Read *ptTempLLRP_tSC1G2Read = NULL;
    LLRP_tSC1G2BlockWrite *ptTempLLRP_tSC1G2BlockWrite = NULL;
    LLRP_tSC1G2Write *ptTempLLRP_tSC1G2Write = NULL;
    LLRP_tSC1G2Lock *ptTempLLRP_tSC1G2Lock = NULL;
    LLRP_tSC1G2Kill *ptTempLLRP_tSC1G2Kill = NULL;
    LLRP_tSC1G2LockPayload *ptTempLLRP_tSC1G2LockPayload = NULL;
    LLRP_tSC1G2BlockReadlock *ptTempLLRP_tSC1G2BlockReadLock = NULL;
    LLRP_tSC1G2BlockPermalock *ptTempLLRP_tSC1G2BlockPermalock = NULL;
    LLRP_tSC1G2BlockPermalockQuery *ptTempLLRP_tSC1G2BlockPermalockQuery = NULL;
    LLRP_tSImpinjSetQTConfig *ptTempLLRP_tSImpinjSetQTConfig = NULL;
    LLRP_tSImpinjGetQTConfig *ptTempLLRP_tSImpinjGetQTConfig = NULL;
    T_RdpLlrpC1G2Read *ptTempLLRPC1G2Read = NULL;
    T_RdpLlrpC1G2Write *ptTempLLRPC1G2Write = NULL;
    T_RdpLlrpC1G2Lock *ptTempLLRPC1G2Lock = NULL;
    T_RdpLlrpC1G2Kill *ptTempLLRPC1G2Kill = NULL;
    T_RdpLlrpC1G2ReadLock *ptTempLLRPC1G2AlienReadLock = NULL;
    T_RdpLlrpC1G2BlockLock *ptTempLLRPC1G2BlockLock = NULL;
    LLRP_tSC1G2WriteVerify *ptLLRP_tSC1G2WriteVerify = NULL;
    T_RdpLlrpClientRequestOpSpec *ptTempClientRequestOpSpec = NULL; //这个有用吗，要讨论一下
    LLRP_tSClientRequestOpSpec *ptTempLLRP_tSClientRequestOpSpec = NULL;
    T_RdpLlrpC1G2IPJQT *ptTempLLRPC1G2IPJQT	= NULL;
    for (ptTempLLRP_tSParameter = ptTempParameter;
            NULL != ptTempLLRP_tSParameter;
            ptTempLLRP_tSParameter = ptTempLLRP_tSParameter->pNextSubParameter, ptListOpSet->wOPNum++)
    {
        wOpIndex = ptListOpSet->wOPNum;
        switch (ptTempLLRP_tSParameter->elementHdr.pType->TypeNum)
        {

        case LLRP_C1G2ReadCustomUID:
            {
                /*标识access定义了唯一性标识*/
                RdpLlrpDbgPrint("(LLRP)LLRP_C1G2ReadCustomUID\r\n");
                ptTempLLRP_tSC1G2ReadCustomUID = (LLRP_tSC1G2ReadCustomUID *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Read = (T_RdpLlrpC1G2Read *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Read->dwAccessPassword = ptTempLLRP_tSC1G2ReadCustomUID->AccessPassword;
                ptTempLLRPC1G2Read->ucMB = ptTempLLRP_tSC1G2ReadCustomUID->MB;
                ptTempLLRPC1G2Read->wWordPointer = ptTempLLRP_tSC1G2ReadCustomUID->WordPtr;
                ptTempLLRPC1G2Read->wWordCount = ptTempLLRP_tSC1G2ReadCustomUID->WordCount;
                ptTempLLRPC1G2Read->wOpSpecID = ptTempLLRP_tSC1G2ReadCustomUID->OpSpecID;
                ptTempLLRPC1G2Read->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1G2ReadCustomUID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Read->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2Read->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wWordCount: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Read->ucMB, ptTempLLRPC1G2Read->wWordPointer,
                                ptTempLLRPC1G2Read->wWordCount, ptTempLLRPC1G2Read->dwAccessPassword,
                                ptTempLLRPC1G2Read->wOpSpecID);
                break;
            }
        case LLRP_C1GOperationType_Read:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1GOperationType_Read\r\n");
                ptTempLLRP_tSC1G2Read = (LLRP_tSC1G2Read *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Read = (T_RdpLlrpC1G2Read *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Read->dwAccessPassword = ptTempLLRP_tSC1G2Read->AccessPassword;
                ptTempLLRPC1G2Read->ucMB = ptTempLLRP_tSC1G2Read->MB;
                ptTempLLRPC1G2Read->wWordPointer = ptTempLLRP_tSC1G2Read->WordPointer;
                ptTempLLRPC1G2Read->wWordCount = ptTempLLRP_tSC1G2Read->WordCount;
                ptTempLLRPC1G2Read->wOpSpecID = ptTempLLRP_tSC1G2Read->OpSpecID;
                ptTempLLRPC1G2Read->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1GOperationType_Read;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Read->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2Read->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wWordCount: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Read->ucMB, ptTempLLRPC1G2Read->wWordPointer,
                                ptTempLLRPC1G2Read->wWordCount, ptTempLLRPC1G2Read->dwAccessPassword,
                                ptTempLLRPC1G2Read->wOpSpecID);
                break;
            }
        case LLRP_C1GOperationType_Write:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1GOperationType_Write\r\n");
                ptTempLLRP_tSC1G2Write = (LLRP_tSC1G2Write *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Write = (T_RdpLlrpC1G2Write *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Write->dwAccessPassword = ptTempLLRP_tSC1G2Write->AccessPassword;
                ptTempLLRPC1G2Write->ucMB = ptTempLLRP_tSC1G2Write->MB;
                ptTempLLRPC1G2Write->wWordPointer = ptTempLLRP_tSC1G2Write->WordPointer;
                ptTempLLRPC1G2Write->wDataLength = ptTempLLRP_tSC1G2Write->WriteData.nValue;
                ptTempLLRPC1G2Write->wOpSpecID = ptTempLLRP_tSC1G2Write->OpSpecID;
                ptTempLLRPC1G2Write->dwRCPCommand = 0;
                memcpy(ptTempLLRPC1G2Write->aucData,
                       ptTempLLRP_tSC1G2Write->WriteData.pValue,
                       sizeof(unsigned short int)*ptTempLLRP_tSC1G2Write->WriteData.nValue);
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wDataLength: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Write->ucMB, ptTempLLRPC1G2Write->wWordPointer,
                                ptTempLLRPC1G2Write->wDataLength, ptTempLLRPC1G2Write->dwAccessPassword,
                                ptTempLLRPC1G2Write->wOpSpecID);
                RdpLlrpDbgPrint("(LLRP)write data:");
                for (dwTestIndex = 0 ; dwTestIndex < ptTempLLRPC1G2Write->wDataLength * sizeof(unsigned short int); dwTestIndex++)
                {
                    RdpDbgPrintRaw("0x%2x ", ptTempLLRPC1G2Write->aucData[dwTestIndex]);
                }
                RdpLlrpDbgPrint("\r\n");
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1GOperationType_Write;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Write->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2Write->dwAccessPassword;
                RdpLlrpDbgPrint("ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = 0x%x\r\n", ptTempLLRPC1G2Write->dwAccessPassword);
                break;
            }
        case LLRP_C1GOperationType_BLOCKWrite:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1GOperationType_BLOCKWrite\r\n");
                ptTempLLRP_tSC1G2BlockWrite = (LLRP_tSC1G2BlockWrite *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Write = (T_RdpLlrpC1G2Write *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Write->ucMB = ptTempLLRP_tSC1G2BlockWrite->MB;
                ptTempLLRPC1G2Write->wWordPointer = ptTempLLRP_tSC1G2BlockWrite->WordPointer;
                ptTempLLRPC1G2Write->wDataLength = ptTempLLRP_tSC1G2BlockWrite->WriteData.nValue;
                ptTempLLRPC1G2Write->wOpSpecID = ptTempLLRP_tSC1G2BlockWrite->OpSpecID;
                ptTempLLRPC1G2Write->dwAccessPassword = ptTempLLRP_tSC1G2BlockWrite->AccessPassword;
                ptTempLLRPC1G2Write->dwRCPCommand = 0;
                memcpy(ptTempLLRPC1G2Write->aucData,
                       ptTempLLRP_tSC1G2BlockWrite->WriteData.pValue,
                       ptTempLLRP_tSC1G2BlockWrite->WriteData.nValue*sizeof(unsigned short int));
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wDataLength: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Write->ucMB, ptTempLLRPC1G2Write->wWordPointer,
                                ptTempLLRPC1G2Write->wDataLength, ptTempLLRPC1G2Write->dwAccessPassword,
                                ptTempLLRPC1G2Write->wOpSpecID);
                RdpLlrpDbgPrint("(LLRP)write data:");
                for (dwTestIndex = 0 ; dwTestIndex < ptTempLLRPC1G2Write->wDataLength * sizeof(unsigned short int); dwTestIndex++)
                {
                    RdpDbgPrintRaw("0x%2x ", ptTempLLRPC1G2Write->aucData[dwTestIndex]);
                }
                RdpLlrpDbgPrint("\r\n");
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1GOperationType_BLOCKWrite;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Write->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2Write->dwAccessPassword;
                break;
            }
        case LLRP_C1GOperationType_Lock:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1GOperationType_Lock\r\n");
                ptTempLLRP_tSC1G2Lock = (LLRP_tSC1G2Lock *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Lock = (T_RdpLlrpC1G2Lock *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Lock->dwAccessPassword = ptTempLLRP_tSC1G2Lock->AccessPassword;
                ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum = 0;
                ptTempLLRPC1G2Lock->dwRCPCommand = 0;
                for (ptTempLLRP_tSC1G2LockPayload = ptTempLLRP_tSC1G2Lock->listC1G2LockPayload;
                        ptTempLLRP_tSC1G2LockPayload;
                        ptTempLLRP_tSC1G2LockPayload = (LLRP_tSC1G2LockPayload *)ptTempLLRP_tSC1G2LockPayload->hdr.pNextSubParameter,
                        ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum++)
                {
                    ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.tRdpLlrpC1G2LockPayLoad[ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum].Privilege
                    = ptTempLLRP_tSC1G2LockPayload->ePrivilege;
                    ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.tRdpLlrpC1G2LockPayLoad[ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum].DataField
                    = ptTempLLRP_tSC1G2LockPayload->eDataField;
                    RdpLlrpDbgPrint("(LLRP)Epc LockPayLoad[%d].Privilege :%d\r\n",
                                    ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum,
                                    ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad \
                                    .tRdpLlrpC1G2LockPayLoad[ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum].Privilege);
                    RdpLlrpDbgPrint("(LLRP)Epc LockPayLoad[%d].DataField :%d\r\n",
                                    ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum,
                                    ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad \
                                    .tRdpLlrpC1G2LockPayLoad[ptTempLLRPC1G2Lock->tRdpLlrpC1G2LockPayLoad.wPayLoadNum].DataField);
                }
                ptTempLLRPC1G2Lock->wOpSpecID = ptTempLLRP_tSC1G2Lock->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1GOperationType_Lock;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Lock->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2Lock->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Lock->dwAccessPassword, ptTempLLRPC1G2Lock->wOpSpecID);
                break;
            }
        case LLRP_C1GOperationType_Kill:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1GOperationType_Kill\r\n");
                ptTempLLRP_tSC1G2Kill = (LLRP_tSC1G2Kill *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Kill = (T_RdpLlrpC1G2Kill *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Kill->wKillPassword = ptTempLLRP_tSC1G2Kill->KillPassword;
                ptTempLLRPC1G2Kill->wOpSpecID = ptTempLLRP_tSC1G2Kill->OpSpecID;
                ptTempLLRPC1G2Kill->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1GOperationType_Kill;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Kill->wOpSpecID;
                /*杀死密钥不能付给accesspassword直接赋值为0*/
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = 0;
                RdpLlrpDbgPrint("(LLRP)wKillPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Kill->wKillPassword, ptTempLLRPC1G2Kill->wOpSpecID);
                break;
            }
        case LLRP_C1G2_ALIENREADLOCK:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1G2_ALIENREADLOCK\r\n");
                ptTempLLRP_tSC1G2BlockReadLock = (LLRP_tSC1G2BlockReadlock *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2AlienReadLock = (T_RdpLlrpC1G2ReadLock *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2AlienReadLock->ucMask = ptTempLLRP_tSC1G2BlockReadLock->Mask;
                ptTempLLRPC1G2AlienReadLock->dwAccessPassword = ptTempLLRP_tSC1G2BlockReadLock->AccessPassword;
                ptTempLLRPC1G2AlienReadLock->dwRCPCommand = 0;
                RdpLlrpDbgPrint("(LLRP)ucMask :%d\r\n", ptTempLLRPC1G2AlienReadLock->ucMask);
                ptTempLLRPC1G2AlienReadLock->wOpSpecID = ptTempLLRP_tSC1G2BlockReadLock->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1G2_ALIENREADLOCK;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2AlienReadLock->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2AlienReadLock->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)ucMask: %d    dwAccessPassword: %d     wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2AlienReadLock->ucMask,
                                ptTempLLRPC1G2AlienReadLock->dwAccessPassword, ptTempLLRPC1G2AlienReadLock->wOpSpecID);
                break;
            }
        case LLRP_C1G2_BLOCKLOCK:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1G2_BLOCKLOCK\r\n");
                ptTempLLRP_tSC1G2BlockPermalock = (LLRP_tSC1G2BlockPermalock *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2BlockLock = (T_RdpLlrpC1G2BlockLock *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2BlockLock->ucMB = ptTempLLRP_tSC1G2BlockPermalock->MB;
                ptTempLLRPC1G2BlockLock->ucReadLock = EPC_C1G2_BLOCKLOCK;
                ptTempLLRPC1G2BlockLock->wOpSpecID = ptTempLLRP_tSC1G2BlockPermalock->OpSpecID;
                ptTempLLRPC1G2BlockLock->ucRFU = 0;
                ptTempLLRPC1G2BlockLock->wBlockPtr = ptTempLLRP_tSC1G2BlockPermalock->BlockPtr;
                ptTempLLRPC1G2BlockLock->wBlockRange = ptTempLLRP_tSC1G2BlockPermalock->BlockRange;
                ptTempLLRPC1G2BlockLock->dwAccessPassword = ptTempLLRP_tSC1G2BlockPermalock->AccessPassword;
                ptTempLLRPC1G2BlockLock->dwRCPCommand = 0;
                memcpy(ptTempLLRPC1G2BlockLock->ucMask,
                       ptTempLLRP_tSC1G2BlockPermalock->Mask.pValue,
                       BIT_CHANGETO_BYTE(ptTempLLRP_tSC1G2BlockPermalock->Mask.nBit));
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1G2_BLOCKLOCK;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2BlockLock->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2BlockLock->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB: %d    wBlockPtr: %d    wBlockRange: %d    dwAccessPassword: %d    wOpSpecID:%d\r\n",
                                ptTempLLRPC1G2BlockLock->ucMB, ptTempLLRPC1G2BlockLock->wBlockPtr,
                                ptTempLLRPC1G2BlockLock->wBlockRange, ptTempLLRPC1G2BlockLock->dwAccessPassword, ptTempLLRPC1G2BlockLock->wOpSpecID);
                break;
            }
        case LLRP_C1G2_BLOCKLOCKQUERY:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1G2_BLOCKLOCKQUERY\r\n");
                ptTempLLRP_tSC1G2BlockPermalockQuery = (LLRP_tSC1G2BlockPermalockQuery *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2BlockLock = (T_RdpLlrpC1G2BlockLock *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2BlockLock->ucReadLock = EPC_C1G2_BLOCKLOCK_QUERY;
                ptTempLLRPC1G2BlockLock->wOpSpecID = ptTempLLRP_tSC1G2BlockPermalockQuery->OpSpecID;
                ptTempLLRPC1G2BlockLock->ucRFU = 0;
                ptTempLLRPC1G2BlockLock->wBlockPtr = ptTempLLRP_tSC1G2BlockPermalockQuery->BlockPtr;
                ptTempLLRPC1G2BlockLock->wBlockRange = ptTempLLRP_tSC1G2BlockPermalockQuery->BlockRange;
                ptTempLLRPC1G2BlockLock->dwAccessPassword = ptTempLLRP_tSC1G2BlockPermalockQuery->AccessPassword;
                ptTempLLRPC1G2BlockLock->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1G2_BLOCKLOCKQUERY;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2BlockLock->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2BlockLock->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)wBlockPtr: %d    wBlockRange: %d    dwAccessPassword: %d    wOpSpecID:%d\r\n",
                                ptTempLLRPC1G2BlockLock->wBlockPtr, ptTempLLRPC1G2BlockLock->wBlockRange,
                                ptTempLLRPC1G2BlockLock->dwAccessPassword, ptTempLLRPC1G2BlockLock->wOpSpecID);
                break;
            }
        case LLRP_C1G2WriteVerify:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_C1G2WriteVerify\r\n");
                ptLLRP_tSC1G2WriteVerify = (LLRP_tSC1G2WriteVerify *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2Read = (T_RdpLlrpC1G2Read *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2Read->dwAccessPassword = 0;
                ptTempLLRPC1G2Read->ucMB = ptLLRP_tSC1G2WriteVerify->MB;
                ptTempLLRPC1G2Read->wWordPointer = ptLLRP_tSC1G2WriteVerify->WordPtr;
                ptTempLLRPC1G2Read->wWordCount = ptLLRP_tSC1G2WriteVerify->WordCount;
                ptTempLLRPC1G2Read->dwAccessPassword = ptLLRP_tSC1G2WriteVerify->AccessPassword;
                ptTempLLRPC1G2Read->wOpSpecID = ptLLRP_tSC1G2WriteVerify->OpSpecID;
                ptTempLLRPC1G2Read->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_C1G2WriteVerify;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2Read->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2Read->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wWordCount: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2Read->ucMB, ptTempLLRPC1G2Read->wWordPointer,
                                ptTempLLRPC1G2Read->wWordCount, ptTempLLRPC1G2Read->dwAccessPassword,
                                ptTempLLRPC1G2Read->wOpSpecID);
                break;
            }
            /*chongqing highway 100524*/
        case LLRP_ClientRequestOpSpec:
            {
                //注意，这个在一个被调用函数中没有用，需要问一下
                RdpLlrpDbgPrint("(LLRP)LLRP_ClientRequestOpSpec\r\n");
                ptTempLLRP_tSClientRequestOpSpec = (LLRP_tSClientRequestOpSpec *)ptTempLLRP_tSParameter;
                ptTempClientRequestOpSpec = (T_RdpLlrpClientRequestOpSpec *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempClientRequestOpSpec->wOpSpecID = ptTempLLRP_tSClientRequestOpSpec->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ClientRequestOpSpec;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempClientRequestOpSpec->wOpSpecID;
                break;
            }
        case LLRP_ImpinjSetQTConfig:
            {
                //注意，这个在一个被调用函数中没有用，需要问一下
                RdpLlrpDbgPrint("(LLRP)LLRP_ImpinjSetQTConfig\r\n");
                ptTempLLRP_tSImpinjSetQTConfig = (LLRP_tSImpinjSetQTConfig *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2IPJQT = (T_RdpLlrpC1G2IPJQT *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2IPJQT->wOpSpecID = ptTempLLRP_tSImpinjSetQTConfig->OpSpecID;
                ptTempLLRPC1G2IPJQT->wDataProfile = ptTempLLRP_tSImpinjSetQTConfig->DataProfile;
                ptTempLLRPC1G2IPJQT->wAccessRange = ptTempLLRP_tSImpinjSetQTConfig->AccessRange;
                ptTempLLRPC1G2IPJQT->wPersistence = ptTempLLRP_tSImpinjSetQTConfig->Persistence;
                ptTempLLRPC1G2IPJQT->dwAccessPassword = ptTempLLRP_tSImpinjSetQTConfig->AccessPassword;
                ptTempLLRPC1G2IPJQT->wReadOrWrite = 1 ;
                ptTempLLRPC1G2IPJQT->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ImpinjSetQTConfig;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2IPJQT->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2IPJQT->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)wDataProfile:%d    wAccessRange: %d   wPersistence: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2IPJQT->wDataProfile, ptTempLLRPC1G2IPJQT->wAccessRange,
                                ptTempLLRPC1G2IPJQT->wPersistence, ptTempLLRPC1G2IPJQT->dwAccessPassword,
                                ptTempLLRPC1G2IPJQT->wOpSpecID);
                break;
            }
        case LLRP_ImpinjGetQTConfig:
            {
                //注意，这个在一个被调用函数中没有用，需要问一下
                RdpLlrpDbgPrint("(LLRP)LLRP_ImpinjGetQTConfig\r\n");
                ptTempLLRP_tSImpinjGetQTConfig = (LLRP_tSImpinjGetQTConfig *)ptTempLLRP_tSParameter;
                ptTempLLRPC1G2IPJQT = (T_RdpLlrpC1G2IPJQT *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPC1G2IPJQT->wOpSpecID = ptTempLLRP_tSImpinjGetQTConfig->OpSpecID;
                ptTempLLRPC1G2IPJQT->dwAccessPassword = ptTempLLRP_tSImpinjGetQTConfig->AccessPassword;
                ptTempLLRPC1G2IPJQT->wReadOrWrite = 0;
                ptTempLLRPC1G2IPJQT->dwRCPCommand = 0;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ImpinjGetQTConfig;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPC1G2IPJQT->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPC1G2IPJQT->dwAccessPassword;
                RdpLlrpDbgPrint("(LLRP)dwAccessPassword: %d     wOpSpecID: %d\r\n",
                                ptTempLLRPC1G2IPJQT->dwAccessPassword, ptTempLLRPC1G2IPJQT->wOpSpecID);
                break;
            }
        default:
            RdpLlrpDbgPrint("(LLRP)Wrong cmd,opType = %d\r\n", ptTempLLRP_tSParameter->elementHdr.pType->TypeNum);
            break;
        }
    }
}
/**************************************************************************
* 函数名称：llrp_transferAccessISO6BOpPara
* 功能描述：转换ISO6B的相应的Op操作到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferAccessISO6BOpPara( T_RdpLlrpListOPCtrlSet *ptListOpSet, LLRP_tSParameter *ptTempParameter)
{
    unsigned short int wOpIndex = 0;
    unsigned int dwTestIndex = 0;
    LLRP_tSParameter *ptTempLLRP_tSParameter = NULL;
    LLRP_tSISO6BRead *ptTempLLRP_tSISO6BRead = NULL;
    LLRP_tSISO6BWrite *ptTempLLRP_tSISO6BWrite = NULL;
    LLRP_tSISO6BLock *ptTempLLRP_tSISO6BLock = NULL;
    LLRP_tSISO6BReadCustomUID *ptTempLLRP_tSISO6BReadCustomUID = NULL;
    LLRP_tSISO6BQueryLock *ptTempLLRP_tSISO6BQueryLock = NULL;
    LLRP_tSClientRequestOpSpec *ptTempLLRP_tSClientRequestOpSpec = NULL;
    T_USPUHFISO6BRead *ptTempISO6BRead = NULL;
    T_USPUHFISO6BWrite *ptTempISO6BWrite = NULL;
    T_USPUHFISO6BLock *ptTempISO6BLock = NULL;
    T_USPUHFISO6BLockQuery *ptTempISO6BQueryLock = NULL;
    T_RdpLlrpClientRequestOpSpec *ptTempClientRequestOpSpec = NULL; //这个有用吗，要讨论一下
    for (ptTempLLRP_tSParameter = ptTempParameter;
            NULL != ptTempLLRP_tSParameter;
            ptTempLLRP_tSParameter = ptTempLLRP_tSParameter->pNextSubParameter, ptListOpSet->wOPNum++)
    {
        wOpIndex = ptListOpSet->wOPNum;
        switch (ptTempLLRP_tSParameter->elementHdr.pType->TypeNum)
        {

        case LLRP_ISO6BReadCustomUID:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ISO6BReadCustomUID,TransferAccessISO6BOpPara\r\n");
                ptTempLLRP_tSISO6BReadCustomUID = (LLRP_tSISO6BReadCustomUID *)ptTempLLRP_tSParameter;
                ptTempISO6BRead = (T_USPUHFISO6BRead *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempISO6BRead->ucBytePtr = ptTempLLRP_tSISO6BReadCustomUID->BytePtr;
                ptTempISO6BRead->ucByteCount = ptTempLLRP_tSISO6BReadCustomUID->ByteCount;
                if (NULL == ptTempLLRP_tSISO6BReadCustomUID->pISO6BReadControl)
                {
                    ptTempISO6BRead->tISO6BReadctl.ucCommandType = 0;
                    ptTempISO6BRead->tISO6BReadctl.ucRetryTimes = 3;
                }
                else
                {
                    ptTempISO6BRead->tISO6BReadctl.ucCommandType
                    = ptTempLLRP_tSISO6BReadCustomUID->pISO6BReadControl->CommandType;
                    ptTempISO6BRead->tISO6BReadctl.ucRetryTimes
                    = ptTempLLRP_tSISO6BReadCustomUID->pISO6BReadControl->RetryTimes;
                }
                RdpLlrpDbgPrint("(LLRP)ucBytePtr: %d    ucByteCount: %d    ucCommandType: %d    ucRetryTimes: %d\r\n",
                                ptTempISO6BRead->ucBytePtr, ptTempISO6BRead->ucByteCount,
                                ptTempISO6BRead->tISO6BReadctl.ucCommandType,
                                ptTempISO6BRead->tISO6BReadctl.ucRetryTimes);
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ISO6BReadCustomUID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRP_tSISO6BReadCustomUID->OpSpecID;
                break;
            }
        case LLRP_ISO6BOperationType_Read:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ISO6BOperationType_Read\r\n");
                ptTempLLRP_tSISO6BRead = (LLRP_tSISO6BRead *)ptTempLLRP_tSParameter;
                ptTempISO6BRead = (T_USPUHFISO6BRead *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempISO6BRead->ucBytePtr = ptTempLLRP_tSISO6BRead->BytePtr;
                ptTempISO6BRead->ucByteCount = ptTempLLRP_tSISO6BRead->ByteCount;
                if (ptTempLLRP_tSISO6BRead->pISO6BReadControl == NULL)
                {
                    ptTempISO6BRead->tISO6BReadctl.ucCommandType = 0;
                    ptTempISO6BRead->tISO6BReadctl.ucRetryTimes = 3;
                }
                else
                {
                    ptTempISO6BRead->tISO6BReadctl.ucCommandType
                    = ptTempLLRP_tSISO6BRead->pISO6BReadControl->CommandType;
                    ptTempISO6BRead->tISO6BReadctl.ucRetryTimes
                    = ptTempLLRP_tSISO6BRead->pISO6BReadControl->RetryTimes;

                }
                RdpLlrpDbgPrint("(LLRP)ucBytePtr: %d    ucByteCount: %d    ucCommandType: %d    ucRetryTimes: %d\r\n",
                                ptTempISO6BRead->ucBytePtr, ptTempISO6BRead->ucByteCount,
                                ptTempISO6BRead->tISO6BReadctl.ucCommandType,
                                ptTempISO6BRead->tISO6BReadctl.ucRetryTimes);
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ISO6BOperationType_Read;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRP_tSISO6BRead->OpSpecID;
                break;
            }
        case LLRP_ISO6BOperationType_Write:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ISO6BOperationType_Write\r\n");
                ptTempLLRP_tSISO6BWrite = (LLRP_tSISO6BWrite *)ptTempLLRP_tSParameter;
                ptTempISO6BWrite = (T_USPUHFISO6BWrite *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempISO6BWrite->ucBytePtr = ptTempLLRP_tSISO6BWrite->BytePtr;
                ptTempISO6BWrite->ucByteCount = ptTempLLRP_tSISO6BWrite->ByteCount;

                if (ptTempLLRP_tSISO6BWrite->pISO6BWriteControl == NULL)
                {
                    ptTempISO6BWrite->tISO6BWriteCtl.ucCommandType = 1;
                    ptTempISO6BWrite->tISO6BWriteCtl.ucRetryTimes = 3;
                    ptTempISO6BWrite->tISO6BWriteCtl.ucVerifyTimes = 0;
                }
                else
                {
                    ptTempISO6BWrite->tISO6BWriteCtl.ucCommandType
                    = ptTempLLRP_tSISO6BWrite->pISO6BWriteControl->CommandType;
                    ptTempISO6BWrite->tISO6BWriteCtl.ucRetryTimes
                    = ptTempLLRP_tSISO6BWrite->pISO6BWriteControl->RetryTimes;
                    ptTempISO6BWrite->tISO6BWriteCtl.ucVerifyTimes
                    = ptTempLLRP_tSISO6BWrite->pISO6BWriteControl->VerifyTimes;
                }
                //ptTempLLRPC1G2Write->wOpSpecID =  ptTempLLRP_tSC1G2Write->OpSpecID;
                memcpy(ptTempISO6BWrite->aucWriteData,
                       ptTempLLRP_tSISO6BWrite->WriteData.pValue,
                       ptTempLLRP_tSISO6BWrite->ByteCount);
                RdpLlrpDbgPrint("(LLRP)ucBytePtr: %d    ucByteCount: %d    ucCommandType: %d    ucRetryTimes: %d    ucVerifyTimes: %d\r\n",
                                ptTempISO6BWrite->ucBytePtr, ptTempISO6BWrite->ucByteCount,
                                ptTempISO6BWrite->tISO6BWriteCtl.ucCommandType,
                                ptTempISO6BWrite->tISO6BWriteCtl.ucRetryTimes,
                                ptTempISO6BWrite->tISO6BWriteCtl.ucVerifyTimes);
                RdpLlrpDbgPrint("(LLRP)ISO6B Writedata:");
                for (dwTestIndex = 0 ; dwTestIndex < ptTempISO6BWrite->ucByteCount; dwTestIndex++)
                {
                    RdpDbgPrintRaw("0x%2x ", ptTempISO6BWrite->aucWriteData[dwTestIndex]);
                }
                RdpLlrpDbgPrint("\r\n");
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ISO6BOperationType_Write;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRP_tSISO6BWrite->OpSpecID;
                break;
            }
        case LLRP_ISO6BOperationType_Lock:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ISO6BOperationType_Lock\r\n");
                ptTempLLRP_tSISO6BLock = (LLRP_tSISO6BLock *)ptTempLLRP_tSParameter;
                ptTempISO6BLock = (T_USPUHFISO6BLock *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempISO6BLock->ucBytePtr = ptTempLLRP_tSISO6BLock->BytePtr;
                ptTempISO6BLock->ucByteCount = ptTempLLRP_tSISO6BLock->ByteCount;
                if (ptTempLLRP_tSISO6BLock->pISO6BLockControl == NULL)
                {
                    ptTempISO6BLock->tISO6BLockCtl.ucRetryTimes = 3;
                    ptTempISO6BLock->tISO6BLockCtl.ucVerifyTimes = 0;
                }
                else
                {
                    ptTempISO6BLock->tISO6BLockCtl.ucRetryTimes = ptTempLLRP_tSISO6BLock->pISO6BLockControl->RetryTimes;
                    ptTempISO6BLock->tISO6BLockCtl.ucVerifyTimes = ptTempLLRP_tSISO6BLock->pISO6BLockControl->VerifyTimes;

                }
                RdpLlrpDbgPrint("(LLRP)ucBytePtr: %d    ucByteCount: %d    ucRetryTimes: %d\r\n",
                                ptTempISO6BLock->ucBytePtr,
                                ptTempISO6BLock->ucByteCount, ptTempISO6BLock->tISO6BLockCtl.ucRetryTimes);
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ISO6BOperationType_Lock;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRP_tSISO6BLock->OpSpecID;
                break;
            }
        case LLRP_ISO6BOperationType_QueryLock:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ISO6BOperationType_QueryLock\r\n");
                ptTempLLRP_tSISO6BQueryLock = (LLRP_tSISO6BQueryLock *)ptTempLLRP_tSParameter;
                ptTempISO6BQueryLock = (T_USPUHFISO6BLockQuery*) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempISO6BQueryLock->ucBytePtr = ptTempLLRP_tSISO6BQueryLock->BytePtr;
                ptTempISO6BQueryLock->ucByteCount = ptTempLLRP_tSISO6BQueryLock->ByteCount;

                if (ptTempLLRP_tSISO6BQueryLock->pISO6BQueryLockControl == NULL)
                {
                    ptTempISO6BQueryLock->tISO6BLockQueryCtl.ucRetryTimes = 3;
                }
                else
                {
                    ptTempISO6BQueryLock->tISO6BLockQueryCtl.ucRetryTimes
                    = ptTempLLRP_tSISO6BQueryLock->pISO6BQueryLockControl->RetryTimes;
                }
                RdpLlrpDbgPrint("(LLRP)ucBytePtr: %d    ucByteCount: %d    ucRetryTimes: %d\r\n",
                                ptTempISO6BQueryLock->ucBytePtr,
                                ptTempISO6BQueryLock->ucByteCount, ptTempISO6BQueryLock->tISO6BLockQueryCtl.ucRetryTimes);
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ISO6BOperationType_QueryLock;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRP_tSISO6BQueryLock->OpSpecID;
                break;
            }
        case LLRP_ClientRequestOpSpec:
            {
                //注意，这个在一个被调用函数中没有用，需要问一下
                RdpLlrpDbgPrint("(LLRP)LLRP_ClientRequestOpSpec\r\n");
                ptTempLLRP_tSClientRequestOpSpec = (LLRP_tSClientRequestOpSpec *)ptTempLLRP_tSParameter;
                ptTempClientRequestOpSpec = (T_RdpLlrpClientRequestOpSpec *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempClientRequestOpSpec->wOpSpecID = ptTempLLRP_tSClientRequestOpSpec->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ClientRequestOpSpec;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempClientRequestOpSpec->wOpSpecID;
                break;
            }
        default:
            {
                RdpLlrpDbgPrint("(LLRP)Wrong cmd,opType = %d\r\n", ptTempLLRP_tSParameter->elementHdr.pType->TypeNum);
                break;
            }
        }
    }
}

/**************************************************************************
* 函数名称：llrp_transferAccessGBOpPara
* 功能描述：转换GB的相应的Op操作到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptLocalAccessReportCtrl
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_transferAccessGBOpPara( T_RdpLlrpListOPCtrlSet *ptListOpSet, LLRP_tSParameter *ptTempParameter)
{
    unsigned int dwOpNum = 0;
    unsigned short int wOpIndex = 0;
    unsigned int dwTestIndex = 0;
    LLRP_tSParameter *ptTempLLRP_tSParameter = NULL;
    LLRP_tSGBReadCustomUID *ptTempLLRP_tSGBReadCustomUID = NULL;
    LLRP_tSGBRead *ptTempLLRP_tSGBRead = NULL;
    LLRP_tSGBWrite *ptTempLLRP_tSGBWrite = NULL;
    LLRP_tSGBErase *ptTempLLRP_tSGBErase = NULL;
    LLRP_tSGBLock *ptTempLLRP_tSGBLock = NULL;
    LLRP_tSGBLockMemoryMode *ptLLRPGBLockMemoryMode=NULL;
    LLRP_tSGBLockSecureMode *ptLLRPGBLockSecureMode=NULL;
    LLRP_tSGBKill *ptTempLLRP_tSGBKill = NULL;
    T_RdpLlrpGBRead *ptTempLLRPGBRead = NULL;
    T_RdpLlrpGBWrite *ptTempLLRPGBWrite = NULL;
    T_RdpLlrpGBErase *ptTempLLRPGBErase = NULL;
    T_RdpLlrpGBLock *ptTempLLRPGBLock = NULL;
    T_RdpLlrpGBKill *ptTempLLRPGBKill = NULL;    
    T_RdpLlrpClientRequestOpSpec *ptTempClientRequestOpSpec = NULL; //这个有用吗，要讨论一下
    LLRP_tSClientRequestOpSpec *ptTempLLRP_tSClientRequestOpSpec = NULL;
    for (ptTempLLRP_tSParameter = ptTempParameter;
            NULL != ptTempLLRP_tSParameter;
            ptTempLLRP_tSParameter = ptTempLLRP_tSParameter->pNextSubParameter, ptListOpSet->wOPNum++)
    {
        wOpIndex = ptListOpSet->wOPNum;
        switch (ptTempLLRP_tSParameter->elementHdr.pType->TypeNum)
        {

        case LLRP_GBReadCustomUID:
            {
                /*标识access定义了唯一性标识*/
                RdpLlrpDbgPrint("(LLRP)LLRP_GBReadCustomUID\r\n");
                ptTempLLRP_tSGBReadCustomUID = (LLRP_tSGBReadCustomUID *)ptTempLLRP_tSParameter;
                ptTempLLRPGBRead = (T_RdpLlrpGBRead *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPGBRead->dwReadPassword = ptTempLLRP_tSGBReadCustomUID->ReadPassword;
                ptTempLLRPGBRead->ucMB = ptTempLLRP_tSGBReadCustomUID->MB;
                ptTempLLRPGBRead->wWordPointer = ptTempLLRP_tSGBReadCustomUID->WordPointer;
                ptTempLLRPGBRead->wWordCount = ptTempLLRP_tSGBReadCustomUID->WordCount;
                ptTempLLRPGBRead->wOpSpecID = ptTempLLRP_tSGBReadCustomUID->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_GBReadCustomUID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPGBRead->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPGBRead->dwReadPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wWordCount: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPGBRead->ucMB, ptTempLLRPGBRead->wWordPointer,
                                ptTempLLRPGBRead->wWordCount, ptTempLLRPGBRead->dwReadPassword,
                                ptTempLLRPGBRead->wOpSpecID);
                break;
            }
        case LLRP_GBOperationType_Read:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_GBOperationType_Read\r\n");
                ptTempLLRP_tSGBRead = (LLRP_tSGBRead *)ptTempLLRP_tSParameter;
                ptTempLLRPGBRead = (T_RdpLlrpGBRead *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPGBRead->dwReadPassword = ptTempLLRP_tSGBRead->ReadPassword;
                ptTempLLRPGBRead->ucMB = ptTempLLRP_tSGBRead->MB;
                ptTempLLRPGBRead->wWordPointer = ptTempLLRP_tSGBRead->WordPointer;
                ptTempLLRPGBRead->wWordCount = ptTempLLRP_tSGBRead->WordCount;
                ptTempLLRPGBRead->wOpSpecID = ptTempLLRP_tSGBRead->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_GBOperationType_Read;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPGBRead->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPGBRead->dwReadPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wWordCount: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPGBRead->ucMB, ptTempLLRPGBRead->wWordPointer,
                                ptTempLLRPGBRead->wWordCount, ptTempLLRPGBRead->dwReadPassword,
                                ptTempLLRPGBRead->wOpSpecID);
                break;
            }
        case LLRP_GBOperationType_Write:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_GBOperationType_Write\r\n");
                ptTempLLRP_tSGBWrite = (LLRP_tSGBWrite *)ptTempLLRP_tSParameter;
                ptTempLLRPGBWrite = (T_RdpLlrpGBWrite *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPGBWrite->dwWritePassword = ptTempLLRP_tSGBWrite->WritePassword;
                ptTempLLRPGBWrite->ucMB = ptTempLLRP_tSGBWrite->MB;
                ptTempLLRPGBWrite->wWordPointer = ptTempLLRP_tSGBWrite->WordPointer;
                ptTempLLRPGBWrite->wDataLength = ptTempLLRP_tSGBWrite->WriteData.nValue;
                ptTempLLRPGBWrite->wOpSpecID = ptTempLLRP_tSGBWrite->OpSpecID;
                memcpy(ptTempLLRPGBWrite->aucData,
                       ptTempLLRP_tSGBWrite->WriteData.pValue,
                       sizeof(unsigned short int)*ptTempLLRP_tSGBWrite->WriteData.nValue);
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   wDataLength: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPGBWrite->ucMB, ptTempLLRPGBWrite->wWordPointer,
                                ptTempLLRPGBWrite->wDataLength, ptTempLLRPGBWrite->dwWritePassword,
                                ptTempLLRPGBWrite->wOpSpecID);
                RdpLlrpDbgPrint("(LLRP)write data:");
                for (dwTestIndex = 0 ; dwTestIndex < ptTempLLRPGBWrite->wDataLength * sizeof(unsigned short int); dwTestIndex++)
                {
                    RdpDbgPrintRaw("0x%2x ", ptTempLLRPGBWrite->aucData[dwTestIndex]);
                }
                RdpLlrpDbgPrint("\r\n");
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_GBOperationType_Write;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPGBWrite->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPGBWrite->dwWritePassword;
                RdpLlrpDbgPrint("ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = 0x%x\r\n", ptTempLLRPGBWrite->dwWritePassword);
                break;
            }
	case LLRP_GBOperationType_Erase:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_GBOperationType_Erase\r\n");
                ptTempLLRP_tSGBErase = (LLRP_tSGBErase *)ptTempLLRP_tSParameter;
                ptTempLLRPGBErase = (T_RdpLlrpGBErase *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPGBErase->dwWritePassword = ptTempLLRP_tSGBErase->WritePassword;
                ptTempLLRPGBErase->ucMB = ptTempLLRP_tSGBErase->MB;
                ptTempLLRPGBErase->wWordPointer = ptTempLLRP_tSGBErase->WordPointer;
                ptTempLLRPGBErase->wWordCount = ptTempLLRP_tSGBErase->WordCount;
		  ptTempLLRPGBErase->wOpSpecID = ptTempLLRP_tSGBErase->OpSpecID;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d    wWordPointer: %d   WordCount: %d    dwAccessPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPGBErase->ucMB, ptTempLLRPGBErase->wWordPointer,
                                ptTempLLRPGBErase->wWordCount, ptTempLLRPGBErase->dwWritePassword,
                                ptTempLLRPGBErase->wOpSpecID);
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_GBOperationType_Erase;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPGBErase->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPGBErase->dwWritePassword;
                RdpLlrpDbgPrint("ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = 0x%x\r\n", ptTempLLRPGBErase->dwWritePassword);
                break;
            }
        case LLRP_GBOperationType_Lock:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_GBOperationType_Lock\r\n");
                ptTempLLRP_tSGBLock = (LLRP_tSGBLock *)ptTempLLRP_tSParameter;
                ptTempLLRPGBLock = (T_RdpLlrpGBLock *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPGBLock->dwLockPassword= ptTempLLRP_tSGBLock->LockPassword;
		  ptTempLLRPGBLock->ucConfig = ptTempLLRP_tSGBLock->eConfig;
		  ptTempLLRPGBLock->ucMB= ptTempLLRP_tSGBLock->MB;
                if(LLRP_GBLockConfig_MemoryMode==ptTempLLRP_tSGBLock->eConfig)
		  {
		      ptLLRPGBLockMemoryMode=(LLRP_tSGBLockMemoryMode *)ptTempLLRP_tSGBLock->pGBLockAction;
		      ptTempLLRPGBLock->tRdpLlrpGBLockAction.ucGBLockMemoryMode = ptLLRPGBLockMemoryMode->eMemoryMode;
		      RdpLlrpDbgPrint("(LLRP)ucGBLockMemoryMode: %d  \r\n",ptTempLLRPGBLock->tRdpLlrpGBLockAction.ucGBLockMemoryMode);
		  }
		  else
		  {
		      ptLLRPGBLockSecureMode=(LLRP_tSGBLockSecureMode *)ptTempLLRP_tSGBLock->pGBLockAction;
		      ptTempLLRPGBLock->tRdpLlrpGBLockAction.ucGBLockSecureMode = ptLLRPGBLockSecureMode->eSecureMode;
		      RdpLlrpDbgPrint("(LLRP)ucGBLockSecureMode: %d  \r\n",ptTempLLRPGBLock->tRdpLlrpGBLockAction.ucGBLockSecureMode);
		  }
                ptTempLLRPGBLock->wOpSpecID = ptTempLLRP_tSGBLock->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_GBOperationType_Lock;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPGBLock->wOpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = ptTempLLRPGBLock->dwLockPassword;
                RdpLlrpDbgPrint("(LLRP)ucMB:%d  dwAccessPassword: %d    wOpSpecID: %d  ucConfig: %d  \r\n",ptTempLLRPGBLock->ucMB,
                                ptTempLLRPGBLock->dwLockPassword, ptTempLLRPGBLock->wOpSpecID,ptTempLLRPGBLock->ucConfig );
                break;
            }
        case LLRP_GBOperationType_Kill:
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_GBOperationType_Kill\r\n");
                ptTempLLRP_tSGBKill = (LLRP_tSGBKill *)ptTempLLRP_tSParameter;
                ptTempLLRPGBKill = (T_RdpLlrpGBKill *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempLLRPGBKill->dwKillPassword = ptTempLLRP_tSGBKill->KillPassword;
                ptTempLLRPGBKill->wOpSpecID = ptTempLLRP_tSGBKill->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_GBOperationType_Kill;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempLLRPGBKill->wOpSpecID;
                /*杀死密钥不能付给accesspassword直接赋值为0*/
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].dwAccessPassword = 0;
                RdpLlrpDbgPrint("(LLRP)wKillPassword: %d    wOpSpecID: %d\r\n",
                                ptTempLLRPGBKill->dwKillPassword, ptTempLLRPGBKill->wOpSpecID);
                break;
            }
            /*chongqing highway 100524*/
        case LLRP_ClientRequestOpSpec:
            {
                //注意，这个在一个被调用函数中没有用，需要问一下
                RdpLlrpDbgPrint("(LLRP)LLRP_ClientRequestOpSpec\r\n");
                ptTempLLRP_tSClientRequestOpSpec = (LLRP_tSClientRequestOpSpec *)ptTempLLRP_tSParameter;
                ptTempClientRequestOpSpec = (T_RdpLlrpClientRequestOpSpec *) & ptListOpSet->tSingleOp[wOpIndex];
                ptTempClientRequestOpSpec->wOpSpecID = ptTempLLRP_tSClientRequestOpSpec->OpSpecID;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpType = LLRP_ClientRequestOpSpec;
                ptListOpSet->tRdpLlrpOPCtr[wOpIndex].wOpID = ptTempClientRequestOpSpec->wOpSpecID;
                break;
            }
        default:
            RdpLlrpDbgPrint("(LLRP)Wrong cmd,opType = %d\r\n", ptTempLLRP_tSParameter->elementHdr.pType->TypeNum);
            break;
        }
    }
}
/**************************************************************************
* 函数名称：llrp_addAo
* 功能描述：添加AO
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                               LLRP_tSADD_ACCESSSPEC   *ptLLRP_tSADD_ACCESSSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_addAo(T_Msg *ptRcvMsg)
{
    unsigned int dwRet = 0;
    unsigned int dwAccessIndex = 0;
    T_RdpLlrpAccessCtrlAndParam *ptTempAccessCtrl = NULL;
    T_RdpLlrpAccess *ptTempAccess = NULL;
    LLRP_tSAccessSpecStopTrigger *ptTempLLRP_tSAccessSpecStopTrigger = NULL;
    T_RdpLlrpAccessStopTrigger *ptTempAccessSpecStopTrigger = NULL;
    LLRP_tSAccessSpec *ptTempLLRP_tSAccessSpec = NULL;
    T_RdpLlrpListOPCtrlSet *ptTempListOpCtrlSet = NULL;
    LLRP_tSC1G2TagSpec *ptTempLLRP_tSC1G2TagSpec = NULL;
    LLRP_tSC1G2TargetTag *ptTempLLRP_tSC1G2TargetTag = NULL;
    LLRP_tSISO6BTagSpec *ptTempLLRP_tSISO6BTagSpec = NULL;
    LLRP_tSISO6BTargetTag *ptTempLLRP_tSISO6BTargetTag = NULL;
    LLRP_tSC1G2CustomerSetting *ptTempLLRP_tSC1G2CustomerSetting = NULL;
    LLRP_tSGBTagSpec *ptTempLLRP_tSGBTagSpec = NULL;
    LLRP_tSGBTargetTag *ptTempLLRP_tSGBTargetTag = NULL;
    unsigned int dwTestIndex;
    T_RdpAddAo *ptRdpAddAo = NULL;
    ptRdpAddAo = (T_RdpAddAo *)(ptRcvMsg+1);
    LLRP_tSADD_ACCESSSPEC *ptLLRP_tSADD_ACCESSSPEC = ptRdpAddAo->ptAddAoMsgAddr;
    RdpLlrpDbgPrint("(LLRP)receive an  EV_ADD_ACCESSSPEC msg\r\n");
    for (dwAccessIndex = 0; dwAccessIndex < MAX_NUM_ACCESSSPECS; dwAccessIndex++)
    {
        ptTempAccessCtrl = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
        if (ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.ucUseing == FALSE)
        {
            break;
        }
    }
    ptTempLLRP_tSAccessSpec = ptLLRP_tSADD_ACCESSSPEC->pAccessSpec;
    if (dwAccessIndex == MAX_NUM_ACCESSSPECS)
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_RULE_ID);
        RdpLlrpDbgPrint("(LLRP)there is not empty space for access\r\n");
        llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_A_OutOfRange, EV_ADD_ACCESSSPEC_RESPONSE , ptLLRP_tSADD_ACCESSSPEC->hdr.MessageID, ptTempLLRP_tSAccessSpec->AccessSpecID);
        return ;
    }
    /*设置这块区域为使用*/
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.ucUseing = TRUE;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.ucLinkType = ptRcvMsg->ucLinkType;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.wSenderTno = ptRcvMsg->wSenderTno;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.wReceiverTno = ptRcvMsg->wReceiverTno;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwMessageID = ptLLRP_tSADD_ACCESSSPEC->hdr.MessageID;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwReportTrigger =ptRdpAddAo->dwAOReportSndTrigger;
    ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_DISABLE;
    /*指向转换的Access规则*/

    ptTempAccess = &ptTempAccessCtrl->tRdpLlrpAccess;
    /*赋值相关参数*/
    ptTempAccess->dwAccessSpecID = ptTempLLRP_tSAccessSpec->AccessSpecID;
    ptTempAccess->dwROSpecID = ptTempLLRP_tSAccessSpec->ROSpecID;
    ptTempAccess->eCurrentState = ptTempLLRP_tSAccessSpec->eCurrentState;
    ptTempAccess->eProtocolID = ptTempLLRP_tSAccessSpec->eProtocolID;
    ptTempAccess->wAntennaID = ptTempLLRP_tSAccessSpec->AntennaID;
    RdpLlrpDbgPrint("(LLRP) AccessSpecID = %d\r\n", ptTempAccess->dwAccessSpecID);
    RdpLlrpDbgPrint("(LLRP) ROSpecID = %d\r\n", ptTempAccess->dwROSpecID);
    RdpLlrpDbgPrint("(LLRP) CurrentState = %d\r\n", ptTempAccess->eCurrentState);
    RdpLlrpDbgPrint("(LLRP) eProtocolID = %d\r\n", ptTempAccess->eProtocolID);
    RdpLlrpDbgPrint("(LLRP) AntennaID = %d\r\n", ptTempAccess->wAntennaID);
    RdpLlrpDbgPrint("(LLRP) dwMessageID = %d\r\n", ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwMessageID);

    /*转换Trigger*/
    ptTempLLRP_tSAccessSpecStopTrigger = ptTempLLRP_tSAccessSpec->pAccessSpecStopTrigger;
    ptTempAccessSpecStopTrigger = &ptTempAccess->tRdpLlrpAccessStopTrigger;
    ptTempAccessSpecStopTrigger->tRdpLlrpAccessParamStopTrigger.wCurrentOperationValue = 0;
    RdpLlrpDbgPrint("(LLRP)Access StopTrigger\r\n");
    switch (ptTempLLRP_tSAccessSpecStopTrigger->eAccessSpecStopTrigger)
    {
    case LLRP_AccessSpecStopTriggerType_Null:
        RdpLlrpDbgPrint("(LLRP)LLRP_AccessSpecStopTriggerType_Null\r\n");
        ptTempAccessSpecStopTrigger->tRdpLlrpAccessParamStopTrigger.wOperationCountValue = 0;
        ptTempAccessSpecStopTrigger->pfusp_rdp_llrp_initAOStopTrigger = llrp_initforAOStopTrigger;
        ptTempAccessSpecStopTrigger->pfusp_rdp_llrp_IncreaseConditionAndJudeEndForAOStopTrigger = llrp_doDefaultforIncreaseConditionAndJudeEndAOStopTrigger;
        break;
    case LLRP_AccessSpecStopTriggerType_Operation_Count:
        RdpLlrpDbgPrint("(LLRP)LLRP_AccessSpecStopTriggerType_Operation_Count\r\n");
        ptTempAccessSpecStopTrigger->tRdpLlrpAccessParamStopTrigger.wOperationCountValue
        = ptTempLLRP_tSAccessSpecStopTrigger->OperationCountValue;
        RdpLlrpDbgPrint("(LLRP)wOperationCountValue:%d\r\n", ptTempAccessSpecStopTrigger->tRdpLlrpAccessParamStopTrigger.wOperationCountValue);
        ptTempAccessSpecStopTrigger->pfusp_rdp_llrp_initAOStopTrigger = llrp_AccessOperationTimesForinitAOStopTrigger;
        ptTempAccessSpecStopTrigger->pfusp_rdp_llrp_IncreaseConditionAndJudeEndForAOStopTrigger = llrp_AccessOperationTimesForIncreaseAndJudgeEndAO;
        break;
    default:
        break;
    }
    RdpLlrpDbgPrint("(LLRP)Access ReportTrigger\r\n");

    if (ptTempLLRP_tSAccessSpec->pAccessReportSpec == NULL)
    {
        RdpLlrpDbgPrint("(LLRP)AccessReportSpec use default\r\n");
        ptTempAccess->tRdpLlrpAccessReport.bIsDefaultCfgFlag = TRUE;
        if (g_tRdpConfig.tAccessReportSpec.eAccessReportTriggerType == LLRP_AccessReportTriggerType_End_Of_AccessSpec )
        {
            ptTempAccess->tRdpLlrpAccessReport.pfusp_rdp_llrp_sendOneAOReportForAOReportTrigger = llrp_sendAOReportImdiate;

        }
        else if (g_tRdpConfig.tAccessReportSpec.eAccessReportTriggerType == LLRP_AccessReportTriggerType_Whenever_ROReport_Is_Generated)
        {
            ptTempAccess->tRdpLlrpAccessReport.pfusp_rdp_llrp_sendOneAOReportForAOReportTrigger = llrp_insertAOReportToRunRoReportLink;
        }
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)AccessReportSpec not use default type=%d\r\n", ptTempLLRP_tSAccessSpec->pAccessReportSpec->eAccessReportTrigger);
        ptTempAccess->tRdpLlrpAccessReport.bIsDefaultCfgFlag = FALSE;
        if (ptTempLLRP_tSAccessSpec->pAccessReportSpec->eAccessReportTrigger == LLRP_AccessReportTriggerType_End_Of_AccessSpec )
        {
            ptTempAccess->tRdpLlrpAccessReport.pfusp_rdp_llrp_sendOneAOReportForAOReportTrigger = llrp_sendAOReportImdiate;

        }
        else if (ptTempLLRP_tSAccessSpec->pAccessReportSpec->eAccessReportTrigger == LLRP_AccessReportTriggerType_Whenever_ROReport_Is_Generated)
        {
            ptTempAccess->tRdpLlrpAccessReport.pfusp_rdp_llrp_sendOneAOReportForAOReportTrigger = llrp_insertAOReportToRunRoReportLink;
        }
    }

    if (ptTempLLRP_tSAccessSpec->eProtocolID == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        /*定位匹配模板的位置*/

        RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_EPCGlobalClass1Gen2\r\n");

        ptTempLLRP_tSC1G2CustomerSetting = (LLRP_tSC1G2CustomerSetting *)ptTempLLRP_tSAccessSpec->pAccessCommand->pC1G2CustomerSetting;

        if ( NULL == ptTempLLRP_tSC1G2CustomerSetting )
        {
            ptTempAccess->tRdpLlrpAccessCmdCtrl.bCircumstanceSetting = FALSE;
        }
        else
        {
            ptTempAccess->tRdpLlrpAccessCmdCtrl.bCircumstanceSetting = (unsigned int)ptTempLLRP_tSC1G2CustomerSetting->CircumstanceSetting ;

        }
        RdpLlrpDbgPrint("(LLRP)impinj CircumstanceSetting =%d\r\n", ptTempAccess->tRdpLlrpAccessCmdCtrl.bCircumstanceSetting);

        /*定位第一个Target的位置*/

        ptTempLLRP_tSC1G2TagSpec = (LLRP_tSC1G2TagSpec *)ptTempLLRP_tSAccessSpec->pAccessCommand->pAirProtocolTagSpec;

        llrp_transferAccessEpcPatternPara(ptTempLLRP_tSC1G2TagSpec, &ptTempAccess->tRdpLlrpAccessCmdCtrl.tAirProtocolTag);
        /*赋值长度*/
        /*定位操作数据相关*/
        ptTempListOpCtrlSet = &ptTempAccess->tRdpLlrpAccessCmdCtrl.tRdpLlrpListOPCtrlSet;
        llrp_transferAccessEpcOpPara(ptTempListOpCtrlSet,
                                     (LLRP_tSParameter *) ptTempLLRP_tSAccessSpec->pAccessCommand->listAccessCommandOpSpec);

    }
    /*18000-B的先不写*/
    else if (ptTempLLRP_tSAccessSpec->eProtocolID == LLRP_AirProtocols_ISO18000_6B)
    {
        RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_ISO18000_6B\r\n");
        /*定位第一个Target的位置*/
        ptTempLLRP_tSISO6BTagSpec
        = (LLRP_tSISO6BTagSpec *)ptTempLLRP_tSAccessSpec->pAccessCommand->pAirProtocolTagSpec;
        llrp_transferAccessISO6BPatternPara( ptTempLLRP_tSISO6BTagSpec, &ptTempAccess->tRdpLlrpAccessCmdCtrl.tAirProtocolTag);
        ptTempListOpCtrlSet = &ptTempAccess->tRdpLlrpAccessCmdCtrl.tRdpLlrpListOPCtrlSet;
        llrp_transferAccessISO6BOpPara(ptTempListOpCtrlSet,
                                       (LLRP_tSParameter *) ptTempLLRP_tSAccessSpec->pAccessCommand->listAccessCommandOpSpec);
    }
    else if (ptTempLLRP_tSAccessSpec->eProtocolID == LLRP_AirProtocols_GB)
    {
        /*定位匹配模板的位置*/

        RdpLlrpDbgPrint("(LLRP)LLRP_AirProtocols_GB\r\n");

        /*定位第一个Target的位置*/

        ptTempLLRP_tSGBTagSpec = (LLRP_tSGBTagSpec *)ptTempLLRP_tSAccessSpec->pAccessCommand->pAirProtocolTagSpec;

        llrp_transferAccessGBPatternPara(ptTempLLRP_tSGBTagSpec, &ptTempAccess->tRdpLlrpAccessCmdCtrl.tAirProtocolTag);
        /*赋值长度*/
        /*定位操作数据相关*/
        ptTempListOpCtrlSet = &ptTempAccess->tRdpLlrpAccessCmdCtrl.tRdpLlrpListOPCtrlSet;
        llrp_transferAccessGBOpPara(ptTempListOpCtrlSet,
                                     (LLRP_tSParameter *) ptTempLLRP_tSAccessSpec->pAccessCommand->listAccessCommandOpSpec);

    }
    /*插入到添加Accessadd队列中*/
    llrp_buildAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tAddAccessQueue, dwAccessIndex);
    /*if (LLRP_AccessSpecState_Active == ptTempAccess->eCurrentState)
    {
        RdpLlrpDbgPrint("(LLRP)add an active Access and insert Enable queue\r\n");
        ptTempAccessCtrl->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_ENABLE;
        llrp_buildAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tEnableAccessQueue, dwAccessIndex);
    }*/
    RdpLlrpDbgPrint("(LLRP)save dynamic Access for get_AccessRsp\r\n");
    llrp_buildAnNodeFoDynamicAccessQueue(&g_tRdpLlrpDynamicAccessLinkHead[ptRcvMsg->ucLinkIndex], ptLLRP_tSADD_ACCESSSPEC);
    llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_ADD_ACCESSSPEC_RESPONSE , ptLLRP_tSADD_ACCESSSPEC->hdr.MessageID, ptTempLLRP_tSAccessSpec->AccessSpecID);
}
/**************************************************************************
* 函数名称：llrp_deleteLocalAoPara
* 功能描述：删除AO 本地参数和队列
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucLinkIndex,
                            T_RdpLlrpAccessCtrlAndParam ptAccessCtrlAndPara,
                             unsigned int dwAccessIndex
                             unsigned int *pbSendRspFlag
                             unsigned int dwRuleID
                             unsigned int dwMsgID
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_deleteLocalAoPara(unsigned char ucLinkIndex, T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndPara, unsigned int dwAccessIndex, unsigned int *pbSendRspFlag, unsigned int dwRuleID, unsigned int dwMsgID)
{
    unsigned int dwDeleteAccessID = 0;
    dwDeleteAccessID = ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID;
    RdpLlrpDbgPrint("(LLRP)dwDeleteAccessID = %d\r\n", dwDeleteAccessID);
    if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_DISABLE)

        /*防止删除Ro之前对ActiveAccess进行了disable 操作，这时就要判断当前Access不是在运行 */
    {

        if ( g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRunAccess.ptNext == NULL
                || (g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRunAccess.ptNext != NULL
                    && g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRunAccess.ptNext->dwAccessIndex != dwAccessIndex))
        {
            llrp_findAndFreeAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tAddAccessQueue,
                    dwAccessIndex);
            memset(ptAccessCtrlAndPara, 0, sizeof(T_RdpLlrpAccessCtrlAndParam));

        }
        RdpLlrpDbgPrint("(LLRP)delete Access State is disable\r\n");

    }
    else if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_ENABLE)
    {
        RdpLlrpDbgPrint("(LLRP)delete Access State is enable\r\n");
        llrp_findAndFreeAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tAddAccessQueue,
                dwAccessIndex);
        llrp_findAndFreeAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tEnableAccessQueue,
                dwAccessIndex);
        memset(ptAccessCtrlAndPara, 0, sizeof(T_RdpLlrpAccessCtrlAndParam));
    }
    else if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_ACTIVE)
    {
        RdpLlrpDbgPrint("(LLRP)delete Access State is active\r\n");
        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_DELETE;
        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDeleteAccessID = dwRuleID;
        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDeleteAccessMsgID = dwMsgID;
        RdpLlrpDbgPrint("(LLRP)ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDeleteAccessID = %d", ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDeleteAccessID);
        *pbSendRspFlag = FALSE;

    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)delete Access State is unsuported ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus=%d\r\n",
                        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus);
    }
    llrp_deleteAnNodeForDynamicAccessQueue(&g_tRdpLlrpDynamicAccessLinkHead[ucLinkIndex], dwDeleteAccessID);

}
/**************************************************************************
* 函数名称：llrp_clearAccessListforGetAccessRsp
* 功能描述：对于现在存在的动态Ao,首先要从
                             ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE 上的链表中摘除，
                             否则free时，会相互影响
                           
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucLinkIndex
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
*************************************************************************/
void llrp_clearAccessListforGetAccessRsp(unsigned char ucLinkIndex)
{

    LLRP_tSAccessSpec *ptLLRP_tSAccessSpec = NULL;
    LLRP_tSAccessSpec *ptFreeLLRP_tSAccessSpec = NULL;
    if (ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE != NULL)
    {
        for (ptLLRP_tSAccessSpec = LLRP_GET_ACCESSSPECS_RESPONSE_beginAccessSpec(ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE);
                ptLLRP_tSAccessSpec != NULL;)
        {
            ptFreeLLRP_tSAccessSpec = ptLLRP_tSAccessSpec;
            ptLLRP_tSAccessSpec = LLRP_GET_ACCESSSPECS_RESPONSE_nextAccessSpec(ptLLRP_tSAccessSpec);
            LLRP_Element_removeSubParameterFromAllList((LLRP_tSElement *)ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE, (LLRP_tSParameter *)ptFreeLLRP_tSAccessSpec);
        }
        usp_ltk_freeMessage((LLRP_tSMessage *)ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE);
        ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE = NULL;
    }

}
/**************************************************************************
* 函数名称：llrp_deleteAo
* 功能描述：删除AO
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                               LLRP_tSDELETE_ACCESSSPEC   *ptLLRP_tSDELETE_ACCESSSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_deleteAo(T_Msg *ptRcvMsg)
{
    unsigned int bSendRspFlag = TRUE;
    unsigned int dwAccessIndex = 0;
    T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndPara = NULL;
    LLRP_tSDELETE_ACCESSSPEC *ptLLRP_tSDELETE_ACCESSSPEC = *(LLRP_tSDELETE_ACCESSSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_DELETE_ACCESSSPEC msg AccessId %d\r\n", ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID);
    llrp_clearAccessListforGetAccessRsp(ptRcvMsg->ucLinkIndex);
    if (ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID == 0)
    {
        for (dwAccessIndex = 0;dwAccessIndex < MAX_NUM_ACCESSSPECS;dwAccessIndex++)
        {
            ptAccessCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkType)
            {
                RdpLlrpDbgPrint("(LLRP)delete   Access :%d\r\n ", ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID);
                llrp_deleteLocalAoPara(ptRcvMsg->ucLinkIndex, ptAccessCtrlAndPara, dwAccessIndex,
                                       &bSendRspFlag, ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID, ptLLRP_tSDELETE_ACCESSSPEC->hdr.MessageID);
            }
        }
    }
    else
    {
        for (dwAccessIndex = 0;dwAccessIndex < MAX_NUM_ACCESSSPECS;dwAccessIndex++)
        {
            ptAccessCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkType
                    && ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID == ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID)

            {
                break;
            }
        }
        if ( dwAccessIndex == MAX_NUM_ACCESSSPECS )
        {
            RdpLlrpDbgPrint("(LLRP)delete Access :%d is not in Reader\r\n", ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID);
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)delete   Access :%d\r\n ", ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID);
            llrp_deleteLocalAoPara(ptRcvMsg->ucLinkIndex, ptAccessCtrlAndPara, dwAccessIndex,
                                   &bSendRspFlag, ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID, ptLLRP_tSDELETE_ACCESSSPEC->hdr.MessageID);
        }
    }
    if (bSendRspFlag == TRUE )
    {

        llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DELETE_ACCESSSPEC_RESPONSE,
                            ptLLRP_tSDELETE_ACCESSSPEC->hdr.MessageID, ptLLRP_tSDELETE_ACCESSSPEC->AccessSpecID);
    }

    usp_ltk_freeMessage((LLRP_tSMessage * )ptLLRP_tSDELETE_ACCESSSPEC);
}

/**************************************************************************
* 函数名称：llrp_disableLocalAoPara
* 功能描述：禁止AO 本地参数和队列
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucLinkIndex,
                            T_RdpLlrpAccessCtrlAndParam ptAccessCtrlAndPara,
                             unsigned int dwAccessIndex
                             unsigned int *pbSendRspFlag
                             unsigned int dwRuleID
                             unsigned int dwMsgID
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_disableLocalAoPara(unsigned char ucLinkIndex, T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndPara, unsigned int dwAccessIndex, unsigned int *pbSendRspFlag, unsigned int dwRuleID, unsigned int dwMsgID)
{
    if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_ENABLE)
    {
        RdpLlrpDbgPrint("(LLRP)disable Access State is enable\r\n");
        llrp_findAndFreeAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tEnableAccessQueue,
                dwAccessIndex);
    }
    else if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_ACTIVE)
    {
        RdpLlrpDbgPrint("(LLRP)disable Access State is active\r\n");
        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_DISABLE;
        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDisableAccessID = dwRuleID;
        ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDisableAccessMsgID = dwMsgID;
        *pbSendRspFlag = FALSE;

    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)disable Access State is unsuported\r\n");
    }

}
/**************************************************************************
* 函数名称：llrp_disableAo
* 功能描述：禁止AO
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSDISABLE_ACCESSSPEC *ptLLRP_tSDISABLE_ACCESSSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_disableAo(T_Msg *ptRcvMsg)
{
    unsigned int bSendRspFlag = TRUE;
    unsigned int dwAccessIndex = 0;
    T_RdpLlrpAccessEntry *ptInsertNode = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndPara = NULL;
    LLRP_tSDISABLE_ACCESSSPEC *ptLLRP_tSDISABLE_ACCESSSPEC = *(LLRP_tSDISABLE_ACCESSSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_DISABLE_ACCESSSPEC msg AccessId %d\r\n", ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID);
    if (ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID == 0)
    {
        for (dwAccessIndex = 0;dwAccessIndex < MAX_NUM_ACCESSSPECS;dwAccessIndex++)
        {
            ptAccessCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkType
                    && ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState != LLRP_AccessSpecState_Disabled)
            {
                RdpLlrpDbgPrint("(LLRP)disableAo   Access :%d\r\n ", ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID);
                llrp_disableLocalAoPara(ptRcvMsg->ucLinkIndex, ptAccessCtrlAndPara, dwAccessIndex, &bSendRspFlag, ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID, ptLLRP_tSDISABLE_ACCESSSPEC->hdr.MessageID);
                ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwMessageID = ptLLRP_tSDISABLE_ACCESSSPEC->hdr.MessageID;
                ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_DISABLE;
                ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState = LLRP_AccessSpecState_Disabled;
            }
        }
    }
    else
    {
        for (dwAccessIndex = 0;dwAccessIndex < MAX_NUM_ACCESSSPECS;dwAccessIndex++)
        {
            ptAccessCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkType
                    && ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState != LLRP_AccessSpecState_Disabled
                    && ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID == ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID)

            {
                break;
            }
        }
        if ( dwAccessIndex == MAX_NUM_ACCESSSPECS )
        {
            RdpLlrpDbgPrint("(LLRP)disableAo :%d is not in Reader\r\n", ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID);
        }
        else
        {
            llrp_disableLocalAoPara(ptRcvMsg->ucLinkIndex, ptAccessCtrlAndPara, dwAccessIndex, &bSendRspFlag, ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID, ptLLRP_tSDISABLE_ACCESSSPEC->hdr.MessageID);
            ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwMessageID = ptLLRP_tSDISABLE_ACCESSSPEC->hdr.MessageID;
            ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_DISABLE;
            ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState = LLRP_AccessSpecState_Disabled;
        }
    }
    if (bSendRspFlag == TRUE)
    {
        llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_DISABLE_ACCESSSPEC_RESPONSE,
                            ptLLRP_tSDISABLE_ACCESSSPEC->hdr.MessageID, ptLLRP_tSDISABLE_ACCESSSPEC->AccessSpecID);
    }

    usp_ltk_freeMessage((LLRP_tSMessage * )ptLLRP_tSDISABLE_ACCESSSPEC);
}

/**************************************************************************
* 函数名称：llrp_enableAo
* 功能描述：使能AO
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg   消息头
                              LLRP_tSENABLE_ACCESSSPEC *ptLLRP_tSENABLE_ACCESSSPEC
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_enableAo(T_Msg *ptRcvMsg)
{
    unsigned int dwAccessIndex = 0;
    T_RdpLlrpAccessEntry *ptInsertNode = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndPara = NULL;
    LLRP_tSENABLE_ACCESSSPEC *ptLLRP_tSENABLE_ACCESSSPEC = *(LLRP_tSENABLE_ACCESSSPEC **)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)receive an  EV_ENABLE_ACCESSSPEC msg AccessId %d\r\n", ptLLRP_tSENABLE_ACCESSSPEC->AccessSpecID);
    if (ptLLRP_tSENABLE_ACCESSSPEC->AccessSpecID == 0)
    {
        for (dwAccessIndex = 0;dwAccessIndex < MAX_NUM_ACCESSSPECS;dwAccessIndex++)
        {
            ptAccessCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkType
                    && ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_DISABLE
                    && ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState == LLRP_AccessSpecState_Disabled)
            {
                RdpLlrpDbgPrint("(LLRP)enableAo   Access :%d\r\n ", ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID);
                llrp_buildAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tEnableAccessQueue, dwAccessIndex);
                ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwMessageID = ptLLRP_tSENABLE_ACCESSSPEC->hdr.MessageID;
                ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_ENABLE;
                ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState = LLRP_AccessSpecState_Active;
            }
        }
    }
    else
    {
        for (dwAccessIndex = 0;dwAccessIndex < MAX_NUM_ACCESSSPECS;dwAccessIndex++)
        {
            ptAccessCtrlAndPara = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucUseing == TRUE
                    && ptRcvMsg->ucLinkIndex == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkIndex
                    && ptRcvMsg->ucLinkType == ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.ucLinkType
                    && ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus == LLRP_ACCESSDISPATCH_STATE_DISABLE
                    && ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState == LLRP_AccessSpecState_Disabled
                    && ptLLRP_tSENABLE_ACCESSSPEC->AccessSpecID == ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID)

            {
                break;
            }
        }
        if ( dwAccessIndex == MAX_NUM_ACCESSSPECS )
        {
            RdpLlrpDbgPrint("(LLRP)enableAo :%d is not in Reader\r\n", ptLLRP_tSENABLE_ACCESSSPEC->AccessSpecID);
        }
        else
        {
            llrp_buildAnNodeFoAllQueueOfAccess(&g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tEnableAccessQueue, dwAccessIndex);
            ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwMessageID = ptLLRP_tSENABLE_ACCESSSPEC->hdr.MessageID;
            ptAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_ENABLE;
            ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState = LLRP_AccessSpecState_Active;
        }
    }
    llrp_sendRuleRspMsg(ptRcvMsg, LLRP_StatusCode_M_Success, EV_ENABLE_ACCESSSPEC_RESPONSE, ptLLRP_tSENABLE_ACCESSSPEC->hdr.MessageID, ptLLRP_tSENABLE_ACCESSSPEC->AccessSpecID);
    usp_ltk_freeMessage((LLRP_tSMessage * )ptLLRP_tSENABLE_ACCESSSPEC);
}
/**************************************************************************
* 函数名称：llrp_getRo
* 功能描述：获得Ro消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg, LLRP_tSGET_ROSPECS *ptLLRP_tSGET_ROSPECS
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_getRo(T_Msg *ptRcvMsg)
{
    unsigned int dwRet = 0;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    T_RdpLlrpDynamicRo *ptCursorDynamicRo = NULL;
    T_RdpLlrpROEntry *ptInsertNode = NULL;
    T_RdpLlrpROEntry *ptRoCursor = NULL;
    T_RdpLlrpROCtrlAndParam *ptRoCtrlAndPara = NULL;
    LLRP_tSGET_ROSPECS *ptLLRP_tSGET_ROSPECS = *(LLRP_tSGET_ROSPECS **)(ptRcvMsg + 1);
    LLRP_tSROSpec *ptLLRP_tSROSpec = NULL;
    LLRP_tSROSpec *ptFreeLLRP_tSROSpec = NULL;
    RdpLlrpDbgPrint("(LLRP)llrp receive an get Ro msg\r\n");
    if (ptLocalLLRP_tSGET_ROSPECS_RESPONSE != NULL)
    {
        for (ptLLRP_tSROSpec = LLRP_GET_ROSPECS_RESPONSE_beginROSpec(ptLocalLLRP_tSGET_ROSPECS_RESPONSE);
                ptLLRP_tSROSpec != NULL;)
        {
            ptFreeLLRP_tSROSpec = ptLLRP_tSROSpec;
            ptLLRP_tSROSpec = LLRP_GET_ROSPECS_RESPONSE_nextROSpec(ptLLRP_tSROSpec);
            LLRP_Element_removeSubParameterFromAllList((LLRP_tSElement *)ptLocalLLRP_tSGET_ROSPECS_RESPONSE, (LLRP_tSParameter *)ptFreeLLRP_tSROSpec);
        }
        usp_ltk_freeMessage((LLRP_tSMessage *)ptLocalLLRP_tSGET_ROSPECS_RESPONSE);
        ptLocalLLRP_tSGET_ROSPECS_RESPONSE = NULL;
    }
    ptLocalLLRP_tSGET_ROSPECS_RESPONSE = LLRP_GET_ROSPECS_RESPONSE_construct();
    ptSLocalRoLLRPStatus = LLRP_LLRPStatus_construct();
    ptSLocalRoLLRPStatus->eStatusCode = LLRP_StatusCode_M_Success;
    LLRP_GET_ROSPECS_RESPONSE_setLLRPStatus(ptLocalLLRP_tSGET_ROSPECS_RESPONSE, ptSLocalRoLLRPStatus);
    for (ptCursorDynamicRo = g_tRdpLlrpDynamicRoLinkHead[ptRcvMsg->ucLinkIndex].ptNext;
            ptCursorDynamicRo != NULL;ptCursorDynamicRo = ptCursorDynamicRo->ptNext)
    {
        for (ptRoCursor = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tAddQueuehead.ptNext;
                ptRoCursor != NULL;ptRoCursor = ptRoCursor->ptNext)
        {
            ptRoCtrlAndPara
            = &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[ptRoCursor->dwROIndex];
            if (ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID == ptCursorDynamicRo->ptAddRo->pROSpec->ROSpecID)
            {
                RdpLlrpDbgPrint("(LLRP)get dynamic RoID %d and change CurrenState %d \r\n",
                                ptRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID, ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState);
                ptCursorDynamicRo->ptAddRo->pROSpec->eCurrentState = ptRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState;
                LLRP_GET_ROSPECS_RESPONSE_addROSpec(ptLocalLLRP_tSGET_ROSPECS_RESPONSE,
                                                    ptCursorDynamicRo->ptAddRo->pROSpec);
                break;
            }
        }
        if (ptRoCursor == NULL)
        {
            RdpLlrpDbgPrint("(LLRP)Ro ID %d is not in Reader\r\n", ptCursorDynamicRo->ptAddRo->pROSpec->ROSpecID);
            RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, ptCursorDynamicRo->ptAddRo->pROSpec->ROSpecID, 0, 0, RDP_LLRP_RULE_ID);
        }
    }
    RdpLlrpDbgPrint("(LLRP)return an GetRoRsp\r\n");
    ptLocalLLRP_tSGET_ROSPECS_RESPONSE->hdr.MessageID = ptLLRP_tSGET_ROSPECS->hdr.MessageID;
    ptSndMsg->mtype = LLRP_SYN_MSG;
    ptSndMsg->ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptSndMsg->ucLinkType = ptRcvMsg->ucLinkType;
    /*这里wSenderTno和wReceiverTno标识路由的源和目的
     wSrcTno和wDstTno 表示上下周转的节点*/
    ptSndMsg->wSenderTno = ptRcvMsg->wReceiverTno;
    ptSndMsg->wReceiverTno = ptRcvMsg->wSenderTno;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_RULE_TNO;
    ptSndMsg->wMsgID = EV_GET_ROSPEC_RESPONSE;
    /*传输的是地址指针 所以这里是指针所占地址长度*/
    ptSndMsg->wMsgLen = sizeof(ptLocalLLRP_tSGET_ROSPECS_RESPONSE);
    *(LLRP_tSGET_ROSPECS_RESPONSE **)(ptSndMsg + 1) = ptLocalLLRP_tSGET_ROSPECS_RESPONSE;
    RdpLlrpDbgPrint("(LLRP)get Rospec Rsp addr ,0x%4x,dynamic point %d\r\n", *(unsigned int *)(ptSndMsg + 1), ptLocalLLRP_tSGET_ROSPECS_RESPONSE);
    dwRet = RDP_SEND_MSG(pair_socket_rule, ptSndMsg);
    if (dwRet < 0)
    {
        RdpLlrpDbgPrint("(LLRP)msgsend error\r\n");
        /*写入异常*/
        RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, dwRet, 0, 0, RDP_LLRP_RULE_ID);
    }
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSGET_ROSPECS);

}

/**************************************************************************
* 函数名称：llrp_getAo
* 功能描述：获得Ao消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg, LLRP_tSGET_ACCESSSPECS *ptLLRP_tSGET_ACCESSSPECS
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_getAo(T_Msg *ptRcvMsg)
{
    unsigned int dwRet = 0;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    T_RdpLlrpDynamicAccess *ptCursorDynamicAccess = NULL;
    T_RdpLlrpAccessEntry *ptInsertNode = NULL;
    T_RdpLlrpAccessEntry *ptAoCursor = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndPara = NULL;
    LLRP_tSGET_ACCESSSPECS *ptLLRP_tSGET_ACCESSSPECS = *(LLRP_tSGET_ACCESSSPECS **)(ptRcvMsg + 1);
    LLRP_tSAccessSpec *ptLLRP_tSAccessSpec = NULL;
    LLRP_tSAccessSpec *ptFreeLLRP_tSAccessSpec = NULL;
    RdpLlrpDbgPrint("(LLRP)llrp receive an get AO msg \r\n");
    if (ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE != NULL)
    {
        for (ptLLRP_tSAccessSpec = LLRP_GET_ACCESSSPECS_RESPONSE_beginAccessSpec(ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE);
                ptLLRP_tSAccessSpec != NULL;)
        {
            ptFreeLLRP_tSAccessSpec = ptLLRP_tSAccessSpec;
            ptLLRP_tSAccessSpec = LLRP_GET_ACCESSSPECS_RESPONSE_nextAccessSpec(ptLLRP_tSAccessSpec);
            LLRP_Element_removeSubParameterFromAllList((LLRP_tSElement *)ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE, (LLRP_tSParameter *)ptFreeLLRP_tSAccessSpec);
        }
        usp_ltk_freeMessage((LLRP_tSMessage *)ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE);
        ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE = NULL;
    }
    ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE = LLRP_GET_ACCESSSPECS_RESPONSE_construct();
    ptSLocalAoLLRPStatus = LLRP_LLRPStatus_construct();
    ptSLocalAoLLRPStatus->eStatusCode = LLRP_StatusCode_M_Success;
    LLRP_GET_ACCESSSPECS_RESPONSE_setLLRPStatus(ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE, ptSLocalAoLLRPStatus);
    for (ptCursorDynamicAccess = g_tRdpLlrpDynamicAccessLinkHead[ptRcvMsg->ucLinkIndex].ptNext;
            ptCursorDynamicAccess != NULL;ptCursorDynamicAccess = ptCursorDynamicAccess->ptNext)
    {
        for (ptAoCursor = g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tAddAccessQueue.ptNext;
                ptAoCursor != NULL;ptAoCursor = ptAoCursor->ptNext)
        {
            ptAccessCtrlAndPara
            = &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[ptAoCursor->dwAccessIndex];
            if (ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID == ptCursorDynamicAccess->ptAddAccess->pAccessSpec->AccessSpecID)
            {
                RdpLlrpDbgPrint("(LLRP)get dynamic AoID %d and change CurrenState %d\r\n",
                                ptAccessCtrlAndPara->tRdpLlrpAccess.dwAccessSpecID, ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState);
                ptCursorDynamicAccess->ptAddAccess->pAccessSpec->eCurrentState = ptAccessCtrlAndPara->tRdpLlrpAccess.eCurrentState;

                LLRP_GET_ACCESSSPECS_RESPONSE_addAccessSpec(ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE, ptCursorDynamicAccess->ptAddAccess->pAccessSpec);
                RdpLlrpDbgPrint("(LLRP)dwAccessID :%d  \r\n", ptCursorDynamicAccess->ptAddAccess->pAccessSpec->AccessSpecID);
                break;
            }
        }
        if (ptAoCursor == NULL)
        {
            RdpLlrpDbgPrint("(LLRP)Ao ID %d is not in Reader\r\n", ptCursorDynamicAccess->ptAddAccess->pAccessSpec->AccessSpecID);
            RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, ptCursorDynamicAccess->ptAddAccess->pAccessSpec->AccessSpecID, 0, 0, RDP_LLRP_RULE_ID);
        }
    }
    RdpLlrpDbgPrint("(LLRP)return an GetAoRsp\r\n");
    ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE->hdr.MessageID = ptLLRP_tSGET_ACCESSSPECS->hdr.MessageID;
    ptSndMsg->mtype = LLRP_SYN_MSG;
    ptSndMsg->ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptSndMsg->ucLinkType = ptRcvMsg->ucLinkType;
    /*这里wSenderTno和wReceiverTno标识路由的源和目的
     wSrcTno和wDstTno 表示上下周转的节点*/
    ptSndMsg->wSenderTno = ptRcvMsg->wReceiverTno;
    ptSndMsg->wReceiverTno = ptRcvMsg->wSenderTno;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_RULE_TNO;
    ptSndMsg->wMsgID = EV_GET_ACCESSSPECS_RESPONSE;
    /*传输的是地址指针 所以这里是指针所占地址长度*/
    ptSndMsg->wMsgLen = sizeof(ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE);
    *(LLRP_tSGET_ACCESSSPECS_RESPONSE **)(ptSndMsg + 1) = ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE;
    RdpLlrpDbgPrint("(LLRP)get Aospec Rsp addr ,0x%4x,dynamic point %d\r\n", *(unsigned int *)(ptSndMsg + 1), ptLocalLLRP_tSGET_ACCESSSPECS_RESPONSE);
    dwRet = RDP_SEND_MSG(pair_socket_rule, ptSndMsg);
    if (dwRet < 0)
    {
        RdpLlrpDbgPrint("(LLRP)msgsend error\r\n");
        RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, dwRet, 0, 0, RDP_LLRP_RULE_ID);
    }
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSGET_ACCESSSPECS);
}

/**************************************************************************
* 函数名称：llrp_getReport
* 功能描述：获得Report报告
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg,LLRP_tSGET_REPORT *ptLLRP_tSGET_REPORT
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24     V1.0      程亮  创建
**************************************************************************/
void llrp_getReport(T_Msg *ptRcvMsg)
{
    T_Msg *ptSndMsg = NULL;
    T_RdpLlrpSendReportContent *ptSendReportContent = NULL;
    T_RdpLlrpSingleReportCtrl *ptLinkReporthead = NULL;
    T_RdpLlrpSingleReportCtrl *ptLinkReportCursor = NULL;
    RdpLlrpDbgPrint("(LLRP) llrp receive get_report msg\r\n");
    LLRP_tSGET_REPORT *ptLLRP_tSGET_REPORT = *(LLRP_tSGET_REPORT **)(ptRcvMsg + 1);
    ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    ptSendReportContent = (T_RdpLlrpSendReportContent *)(ptSndMsg + 1);
    ptSendReportContent->dwMessgeID = ptLLRP_tSGET_REPORT->hdr.MessageID;
    ptSndMsg->ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptSndMsg->ucLinkType = ptRcvMsg->ucLinkType;
    ptSndMsg->wSenderTno = ptRcvMsg->wSenderTno;
    ptSndMsg->wReceiverTno = ptRcvMsg->wReceiverTno;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_REPORT_TNO;
    ptSndMsg->wMsgLen = sizeof(T_RdpLlrpSendReportContent);
    llrp_sendReport(g_tRdpLlrpReaderAcculateReport[ptRcvMsg->ucLinkIndex].ptAcculateReportHead,
                    ptSndMsg, ptLLRP_tSGET_REPORT->hdr.MessageID);
    g_tRdpLlrpReaderAcculateReport[ptRcvMsg->ucLinkIndex].ptAcculateReportHead = NULL;
    g_tRdpLlrpReaderAcculateReport[ptRcvMsg->ucLinkIndex].dwReportNum = 0;
    g_tRdpLlrpReaderAcculateReport[ptRcvMsg->ucLinkIndex].dwReportSize = 0;
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSGET_REPORT);

}
/**************************************************************************
* 函数名称：llrp_reportReaderEventNotification
* 功能描述：上报事件报告
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucLinkIndex
                              unsigned char ucLinkType
                              T_OneReportControl *ptOneReportControl  报告的控制结构
 
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/10/26    V1.0       程亮        创建
**************************************************************************/ 
/*lint -efunc(669,ReaderEventNotificationFuction)*/
void llrp_reportReaderEventNotification(LLRP_tENotificationEventType eEventType, LLRP_tEROSpecEventType eSubEventType)
{
    unsigned int dwRet = 0;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    LLRP_tSErrorDetails pError;
    LLRP_tSREADER_EVENT_NOTIFICATION *ptReadEventNotification = NULL;
    LLRP_tSReaderEventNotificationData *ptLLRP_tSReaderEventNotificationData = NULL;
    LLRP_tSReportBufferOverflowErrorEvent *ptLLRP_tSReportBufferOverflowErrorEvent = NULL;
    LLRP_tSROSpecEvent *ptLLRP_tSROSpecEvent = NULL;
    LLRP_tSAISpecEvent *ptLLRP_tSAISpecEvent = NULL;
    LLRP_tSUTCTimestamp *ptLLRP_tSUTCTimestamp = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpSendReportContent *ptSendReportContent = NULL;
    ptRunRoCtrlAndPara = llrp_getRunRO();
    if (ptRunRoCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
    }
    /*根据不同的事件构造结构 上报参数*/
    switch (eEventType)
    {
        /*不支持*/
    case LLRP_NotificationEventType_ROSpec_Event:
        /* 使能这个事件则要上报否则不上报*/
        if (g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[LLRP_NotificationEventType_ROSpec_Event].bNotificationState == TRUE)
        {

            if (eSubEventType == LLRP_ROSpecEventType_Start_Of_ROSpec)
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecEvent is config and LLRP_ROSpecEventType_Start_Of_ROSpec happend \r\n");

            }
            else
            {
                RdpLlrpDbgPrint("(LLRP)LLRP_ROSpecEvent is config and LLRP_ROSpecEventType_End_Of_ROSpec happend \r\n");
            }
            ptReadEventNotification = LLRP_READER_EVENT_NOTIFICATION_construct();
            ptLLRP_tSReaderEventNotificationData = LLRP_ReaderEventNotificationData_construct();
            ptLLRP_tSUTCTimestamp = LLRP_UTCTimestamp_construct();
            LLRP_ReaderEventNotificationData_setTimestamp(ptLLRP_tSReaderEventNotificationData,
                    (LLRP_tSParameter *) ptLLRP_tSUTCTimestamp);
            LLRP_READER_EVENT_NOTIFICATION_setReaderEventNotificationData(ptReadEventNotification,
                    ptLLRP_tSReaderEventNotificationData);
            /*如果配置了保持报告则要把报告插入到链路中*/
            ptLLRP_tSROSpecEvent = LLRP_ROSpecEvent_construct();
            ptLLRP_tSROSpecEvent->eEventType = (LLRP_tEROSpecEventType)eSubEventType;
            /*ROSpecID保存在dwEventPara[0]中*/
            ptLLRP_tSROSpecEvent->ROSpecID = ptRunRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID;
            ptLLRP_tSUTCTimestamp->Microseconds = llrp_getReaderuSec();
            LLRP_ReaderEventNotificationData_setROSpecEvent(ptLLRP_tSReaderEventNotificationData, ptLLRP_tSROSpecEvent);
            ptReadEventNotification->hdr.MessageID = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID;

        }
        else
        {
            return ;
        }
        break;
    case LLRP_NotificationEventType_AISpec_Event:
        if (g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[LLRP_NotificationEventType_AISpec_Event].bNotificationState == TRUE)
        {
            RdpLlrpDbgPrint("(LLRP)LLRP_AISpecEndEvent is config and happend\r\n");
            ptReadEventNotification = LLRP_READER_EVENT_NOTIFICATION_construct();
            ptLLRP_tSReaderEventNotificationData = LLRP_ReaderEventNotificationData_construct();
            ptLLRP_tSUTCTimestamp = LLRP_UTCTimestamp_construct();
            LLRP_ReaderEventNotificationData_setTimestamp(ptLLRP_tSReaderEventNotificationData,
                    (LLRP_tSParameter *) ptLLRP_tSUTCTimestamp);
            LLRP_READER_EVENT_NOTIFICATION_setReaderEventNotificationData(ptReadEventNotification,
                    ptLLRP_tSReaderEventNotificationData);
            /*不用传入参数了 利用全局变量赋值*/
            ptLLRP_tSUTCTimestamp->Microseconds = llrp_getReaderuSec();
            ptLLRP_tSAISpecEvent = LLRP_AISpecEvent_construct();
            ptLLRP_tSAISpecEvent->eEventType = 0;
            ptLLRP_tSAISpecEvent->ROSpecID = ptRunRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID;
            ptLLRP_tSAISpecEvent->SpecIndex = ptRunRoCtrlAndPara->tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex;
            LLRP_ReaderEventNotificationData_setAISpecEvent(ptLLRP_tSReaderEventNotificationData,
                    ptLLRP_tSAISpecEvent);
            ptReadEventNotification->hdr.MessageID = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID;
        }
        else
        {
            return ;
        }
        break;
    case LLRP_NotificationEventType_Report_Buffer_Fill_Warning:
        if (g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[LLRP_NotificationEventType_Report_Buffer_Fill_Warning].bNotificationState == TRUE)
        {



            RdpLlrpDbgPrint("(LLRP)LLRP_NotificationEventType_Report_Buffer_Fill_Warning is config and happend\r\n");
            ptReadEventNotification = LLRP_READER_EVENT_NOTIFICATION_construct();
            ptLLRP_tSReaderEventNotificationData = LLRP_ReaderEventNotificationData_construct();
            ptLLRP_tSUTCTimestamp = LLRP_UTCTimestamp_construct();
            LLRP_ReaderEventNotificationData_setTimestamp(ptLLRP_tSReaderEventNotificationData,
                    (LLRP_tSParameter *) ptLLRP_tSUTCTimestamp);
            ptLLRP_tSUTCTimestamp->Microseconds = llrp_getReaderuSec();
            LLRP_READER_EVENT_NOTIFICATION_setReaderEventNotificationData(ptReadEventNotification,
                    ptLLRP_tSReaderEventNotificationData);
            /*不用传入参数了 利用全局变量赋值*/

            ptLLRP_tSReportBufferOverflowErrorEvent = LLRP_ReportBufferOverflowErrorEvent_construct();
            LLRP_ReaderEventNotificationData_setReportBufferOverflowErrorEvent(ptLLRP_tSReaderEventNotificationData,
                    ptLLRP_tSReportBufferOverflowErrorEvent);
            ptReadEventNotification->hdr.MessageID = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID;
        }
        else
        {
            return ;
        }
        break;
    default:
        RdpLlrpDbgPrint("(LLRP) report an unsupport event:%d,eSubEventType:%d\r\n", eEventType, eSubEventType);
        RDP_EXCEPT(RDP_LLRP_UNSUPPORTEVENT_ERROR, 0, 0, 0, RDP_LLRP_RULE_ID);
        return ;
        break;
    }
    ptSndMsg->mtype = LLRP_SYN_MSG;
    ptSndMsg->wMsgID = EV_READER_EVENT_NOTIFICATION;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_REPORT_TNO;
    ptSndMsg->wSenderTno = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wSenderTno;
    ptSndMsg->wReceiverTno = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.wReceiverTno;
    ptSndMsg->ucLinkIndex = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkIndex;
    ptSndMsg->ucLinkType = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.ucLinkType;
    ptSndMsg->wMsgLen = sizeof(T_RdpLlrpSendReportContent);
    ptSendReportContent = (T_RdpLlrpSendReportContent *)(ptSndMsg + 1);
    ptSendReportContent->dwMessgeID = ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID;
    /*此处强转一下地址*/
    ptSendReportContent->ptReportAddr = (T_RdpLlrpSingleReportCtrl *)ptReadEventNotification;
    dwRet = RDP_SEND_MSG(pair_socket_report, ptSndMsg);
    if (dwRet < 0)
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, ptSndMsg->wMsgID, ptSndMsg->wMsgLen, (unsigned int)ptSendReportContent->ptReportAddr, RDP_LLRP_RULE_ID);
        RdpLlrpDbgPrint("(LLRP) send event msg error\r\n");
    }
}

