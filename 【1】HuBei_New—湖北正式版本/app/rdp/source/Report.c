/***************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
*
* 文件名称：Report.c
* 文件标识：
* 内容摘要：report模块实现
* 其它说明：
* 当前版本：
* 作    者：lzy 
* 完成日期：2012.03.01
*
* 修改记录1：  
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************************/


/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include "rdpapppub.h"
#include "report.h"


/***********************************************************
 *                     常量定义                            *
***********************************************************/

/***********************************************************
*                 文件内部使用的宏                        *
***********************************************************/

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/

/***********************************************************
 *                     全局变量                            *
***********************************************************/
unsigned char g_aucReportRevDataBuf[READER_MAX_RCV_MSG_LEN];
unsigned char g_aucReportSendDataBuf[READER_MAX_SEND_MSG_LEN];
T_RdpOpFilterHashEntry *g_ptRdpOpFilterHashEntry = NULL;
T_RdpTagReportFilterHashEntry *g_ptRdpTagReportFilterHashEntry = NULL;
unsigned int g_bReportInitFinish = FALSE;
T_USPRdpAdvancedConfig g_tRdpAdvancedConfig;

extern  void *ctx;
/***********************************************************
 *                     本地变量                            *
***********************************************************/



/***********************************************************
 *                     全局函数                            *
***********************************************************/

/***********************************************************
 *                     局部函数                            *
***********************************************************/
static unsigned int report_dealReportFilter(T_Msg *ptMsg);
static unsigned int report_sendLinkReport(T_Msg *ptMsg);
static unsigned int report_dealReportFilter_SendLinkReport(T_RdpLlrpSingleReportCtrl **ptAcculateReportHead);
static unsigned int report_dealRoReportFilter_SendLinkReport(T_RdpLlrpSingleReportCtrl **ptAcculateReportHead);
static unsigned int report_sendLinkReport_SendReport(T_Msg *ptMsg);
static unsigned int reportWorkProc(T_Msg *ptMsg);
static unsigned int report_dealReportFilter_DeleteFilterNode(T_RdpDeleteFilterNodes *ptDeleteFilterNode);
static void report_init();

/**************************************************************************
* 函数名称：report_dealReportFilter_SendLinkReport
* 功能描述：上报过滤中发送报告消息处理
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpLlrpSingleReportCtrl **ptAcculateReportHead 报告链表头指针
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_dealReportFilter_SendLinkReport(T_RdpLlrpSingleReportCtrl **ptAcculateReportHead)
{
    unsigned int dwRet = RDP_SUCCESS;
    T_RdpLlrpSingleReportCtrl *ptTempReportCtrl = NULL;
    RdpReportDbgPrint("report_dealReportFilter_SendLinkReport\r\n");
    /*遍历链路报告创建操作过滤过滤结点或者更新操作过滤数据库*/
    for (ptTempReportCtrl = *ptAcculateReportHead;NULL != ptTempReportCtrl;)
    {
        RdpReportDbgPrint("ptTempReportCtrl=0x%x,RO type=%d\r\n",
                          ptTempReportCtrl, ptTempReportCtrl->ucROType);
        /*单次报告直接继续*/
        if (RO_START_TRIGGER_SINGLE == ptTempReportCtrl->ucROType)
        {
            ptTempReportCtrl = ptTempReportCtrl->ptNext;
            continue;
        }

        /*周期RO进行上报过滤处理*/
        if (ROSPEC_REPORT_DATA == ptTempReportCtrl->ucReportType)
        {
            dwRet = report_refreshRoReportFilterNode(g_ptRdpTagReportFilterHashEntry, ptTempReportCtrl);
        }
        else if (ACCESSSPEC_REPORT_DATA == ptTempReportCtrl->ucReportType)
        {
            if (0 != ptTempReportCtrl->tUID.wTagDataLen)
            {
                /*获取唯一标识*/
                dwRet = report_refreshAoReportFilterNode(g_ptRdpTagReportFilterHashEntry, ptTempReportCtrl);
            }
            else
            {
                /*删除链路结点*/
                RdpReportDbgPrint("tag report filter can not find only identifier and delete the AO report\r\n");
                dwRet = RDP_FAILED;
            }
        }
        if (RDP_SUCCESS != dwRet)
        {
            /*删除链路结点*/
            report_deleteReportNode(&ptTempReportCtrl, ptAcculateReportHead);
        }
        else
        {
            ptTempReportCtrl = ptTempReportCtrl->ptNext;
        }

    }
    return dwRet;
}
/**************************************************************************
* 函数名称：report_dealReportFilter_DeleteFilterNode
* 功能描述：上报过滤中删除过滤结点消息处理
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpDeleteFilterNodes *ptDeleteFilterNode 消息结构体
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_dealReportFilter_DeleteFilterNode(T_RdpDeleteFilterNodes *ptDeleteFilterNode)
{
    unsigned int dwRet = RDP_SUCCESS;
    if (RDP_DELETE_FILTER_TYPE_AO == ptDeleteFilterNode->ucDeleteType)
    {
        /*删除上报过滤结点*/
        dwRet = report_freeAoReportFilterNode(g_ptRdpTagReportFilterHashEntry, ptDeleteFilterNode->dwRoOrAoId);
    }
    else if (RDP_DELETE_FILTER_TYPE_RO == ptDeleteFilterNode->ucDeleteType)
    {
        /*删除上报过滤结点*/
        dwRet = report_freeRoReportFilterNode(g_ptRdpTagReportFilterHashEntry, ptDeleteFilterNode->dwRoOrAoId);
    }
    return dwRet;
}
/**************************************************************************
* 函数名称：report_dealReportFilter
* 功能描述：报告模块跟上报过滤有关的消息处理
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_Msg *ptMsg 接收到的消息
* 输出参数：T_Msg *ptMsg 消息流
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_dealReportFilter(T_Msg *ptMsg)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned short int wMsgID;
    T_RdpLlrpSingleReportCtrl *ptReportLinkCtrl = NULL;
    T_RdpDeleteFilterNodes *ptRdpDeleteFilterNodes = NULL;
    T_RdpLlrpSendReportContent *ptSendReportContent = NULL;
    if (FALSE == g_tRdpAdvancedConfig.tTagFilterCfg.ucTurnOnRFFilter)
    {
        return dwRet;
    }
    wMsgID = ptMsg->wMsgID;
    switch (wMsgID)
    {
    case EV_USP_RDP_SEND_LINK_REPORT:
        {
            RdpReportDbgPrint("(REPORT ReportFilter) receive msg EV_USP_RDP_SEND_LINK_REPORT\r\n");
            ptSendReportContent = (T_RdpLlrpSendReportContent *)(ptMsg + 1);
            ptReportLinkCtrl = ptSendReportContent->ptReportAddr;
            dwRet = report_dealReportFilter_SendLinkReport(&ptReportLinkCtrl);
            ptSendReportContent->ptReportAddr = ptReportLinkCtrl;
            break;
        }
    case EV_USP_RDP_DELETE_FILTER_NODE:
        {
            RdpReportDbgPrint("(REPORT ReportFilter) receive msg EV_USP_RDP_DELETE_FILTER_NODE\r\n");
            ptRdpDeleteFilterNodes = (T_RdpDeleteFilterNodes *)(ptMsg + 1);
            dwRet = report_dealReportFilter_DeleteFilterNode(ptRdpDeleteFilterNodes);
            break;
        }
    case EV_RDP_REPORT_TAGTRPORT_FILTER_TIMER:
        {
            RdpReportDbgPrint("(REPORT ReportFilter) receive msg EV_RDP_REPORT_TAGTRPORT_FILTER_TIMER\r\n");
            report_dealReportFilter_PollingClear(g_ptRdpTagReportFilterHashEntry);
            break;
        }

    default:
        {
            break;
        }
    }
    return dwRet;
}


/**************************************************************************
* 函数名称：report_sendLinkReport_SendReport
* 功能描述：发送报告中发送报告消息处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg 接收到的消息
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_sendLinkReport_SendReport(T_Msg *ptMsg)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned int dwSendLen = 0;
    T_RdpLlrpSendReportContent *ptSendReportContent = NULL;
    T_RdpLlrpSingleReportCtrl *ptTempReportCtrl = NULL;
    T_RdpLlrpSingleReportCtrl *ptAcculateReportHead = NULL;
    LLRP_tSRO_ACCESS_REPORT *ptRoAndAccessReport = NULL;
    LLRP_tSTagReportData * ptTagReportData = NULL;
    ptSendReportContent = (T_RdpLlrpSendReportContent *)(ptMsg + 1);
    ptAcculateReportHead = ptSendReportContent->ptReportAddr;
    RdpReportDbgPrint("SendReport ptAcculateReportHead=0x%x\r\n", ptAcculateReportHead);
    if (NULL == ptAcculateReportHead)
    {
        RdpReportDbgPrint("no report to send to client\r\n");
        return dwRet;
    }
    do
    {
        /*遍历链路报告构建报告*/
        ptRoAndAccessReport = LLRP_RO_ACCESS_REPORT_construct();
        for (ptTempReportCtrl = ptAcculateReportHead;NULL != ptTempReportCtrl;)
        {
            dwSendLen += ptTempReportCtrl->wMsgLen;
            if (dwSendLen > 1900)
            {
                /*长度超大应该发送*/
                if (ptTempReportCtrl->wMsgLen > 1900)
                {
                    /*单个长度超长应该删除*/
                    RdpWarningPrint("report is too big delete it \r\n");
                    report_deleteReportNode(&ptTempReportCtrl, &ptAcculateReportHead);
                }
                RdpReportDbgPrint("dwSendLen=%d\r\n", dwSendLen);
                dwSendLen = 0;
                break;
            }
            /*构建报告*/

            ptTagReportData = report_constructSingleTagReport(ptTempReportCtrl);
            LLRP_RO_ACCESS_REPORT_addTagReportData(ptRoAndAccessReport, ptTagReportData);
            /*删除链路结点*/
            report_deleteReportNode(&ptTempReportCtrl, &ptAcculateReportHead);
        }
        /*发送报告*/
        dwRet = report_sendReportMsgAndFree(ptMsg, ptSendReportContent->dwMessgeID, \
                                            (LLRP_tSMessage *)ptRoAndAccessReport);
    }
    while (NULL != ptTempReportCtrl) ;
    return dwRet;
}
/**************************************************************************
* 函数名称：report_sendLinkReport_SendEvent
* 功能描述：发送报告中发送事件
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg 接收到的消息
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_sendLinkReport_SendEvent(T_Msg *ptMsg)
{
    unsigned int dwRet = RDP_SUCCESS;
    T_RdpLlrpSendReportContent *ptSendReportContent = NULL;
    LLRP_tSREADER_EVENT_NOTIFICATION *ptReadEventNotification = NULL;
    ptSendReportContent = (T_RdpLlrpSendReportContent *)(ptMsg + 1);
    ptReadEventNotification = (LLRP_tSREADER_EVENT_NOTIFICATION *)ptSendReportContent->ptReportAddr;
    RdpReportDbgPrint("SendEvent addr=0x%x\r\n", ptReadEventNotification);
    /*发送报告*/
    dwRet = report_sendReportMsgAndFree(ptMsg, ptSendReportContent->dwMessgeID, \
                                        (LLRP_tSMessage *)ptReadEventNotification);

    return dwRet;
}

/**************************************************************************
* 函数名称：report_sendLinkReport
* 功能描述：发送报告模块消息处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg 接收到的消息
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_sendLinkReport(T_Msg *ptMsg)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned short int wMsgID = 0;
    wMsgID = ptMsg->wMsgID;
    switch (wMsgID)
    {
    case EV_USP_RDP_SEND_LINK_REPORT:
        {
            RdpReportDbgPrint("(REPORT send report) receive msg EV_USP_RDP_SEND_LINK_REPORT\r\n");
            report_sendLinkReport_SendReport(ptMsg);
            break;
        }
    case EV_READER_EVENT_NOTIFICATION:
        {
            RdpReportDbgPrint("(REPORT send report) receive msg EV_READER_EVENT_NOTIFICATION\r\n");
            report_sendLinkReport_SendEvent(ptMsg);
            break;
        }
    default:
        {
            break;
        }
    }
    return dwRet;
}
/**************************************************************************
* 函数名称：report_init
* 功能描述：报告模块初始化处理
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/05/04    V1.0       lzy        创建
**************************************************************************/
static void report_init()
{
    /* 初始化全局变量 */
    g_ptRdpOpFilterHashEntry = NULL;
    g_ptRdpTagReportFilterHashEntry = NULL;
    memset(g_aucReportRevDataBuf, 0, sizeof(g_aucReportRevDataBuf));
    memset(g_aucReportSendDataBuf, 0, sizeof(g_aucReportSendDataBuf));
    memset(&g_tRdpAdvancedConfig, 0, sizeof(g_tRdpAdvancedConfig));

    memcpy(&g_tRdpAdvancedConfig, &(g_tRdpConfig.tUSPRdpAdvancedConfig), sizeof(T_USPRdpAdvancedConfig));
    /*申请操作过滤和上报过滤数据库内存*/
    report_dealReportFilterMemory();
    g_bReportInitFinish = TRUE;
    return ;
}

/**************************************************************************
* 函数名称：reportWorkProc
* 功能描述：报告模块功能处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg 接收到的消息
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static unsigned int reportWorkProc(T_Msg *ptMsg)
{
    unsigned int dwRet = RDP_SUCCESS;

    /*处理上报过滤*/
    report_dealReportFilter(ptMsg);
	
    /*发送报告*/
    report_sendLinkReport(ptMsg);
    return dwRet;
}
void *pair_socket_report_llrp=NULL;
void *pair_socket_report_rule=NULL;

void create_zmq_sockets_report(void)
{
    int value;
    int ret;
	
    /*inproc llrp*/
	pair_socket_report_llrp = zmq_socket(ctx, ZMQ_PAIR);
    if(NULL == pair_socket_report_llrp)
    {
        printf("create pair_socket_report_llrp fail!\n");
        exit(-1);
    }
    ret = zmq_connect(pair_socket_report_llrp, "inproc://report.inproc");
	if(ret<0)
    {
        printf("zmq_connect pair_socket_report_llrp fail!\n");
        exit(-1);
    }

	/*inproc rule */
	pair_socket_report_rule = zmq_socket(ctx, ZMQ_PAIR);
    if(NULL == pair_socket_report_rule)
    {
        printf("create pair_socket_report_rule fail!\n");
        exit(-1);
    }
    ret = zmq_connect(pair_socket_report_rule, "inproc://rule_report.inproc");
	if(ret<0)
    {
        printf("zmq_connect pair_socket_report_rule fail!\n");
        exit(-1);
    }
    return;
}

/**************************************************************************
* 函数名称：usp_rdp_report_Entry
* 功能描述：rdp报告处理线程入口函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/05    V1.0       lzy        创建
**************************************************************************/
unsigned int rdp_report_main()
{
    zmq_pollitem_t	items[2];
	int item_num;
	int rc;
    T_Msg *ptMsg = NULL;
    unsigned int dwRet = RDP_SUCCESS;

    RdpReportDbgPrint("(usp_rdp_report_Entry) running...... \r\n");

	create_zmq_sockets_report();

    /*模块初始化*/
    report_init();
	
    /* 等待配置完成 */
    while (FALSE == g_bRdpPowerOnCfgFinish)
    {
        usleep(10000);
    }
    RdpReportDbgPrint("(Report)come into rdp_report_main\r\n");

	memset(items,0,sizeof(items));
		 items[0].socket = pair_socket_report_llrp;
		 items[0].events = ZMQ_POLLIN;
		 items[1].socket = pair_socket_report_rule;
		 items[1].events = ZMQ_POLLIN;

    /*  进入消息处理 */
    for (;;)
    {
       rc = zmq_poll(items, 2, -1);
			 if(rc<0)
			 {
				printf("(Report)zmq_poll return , return %d %d,%s\n", rc,errno,zmq_strerror(errno));
				continue;
			 }
			 if(items[0].revents & ZMQ_POLLIN)
			 {
			     dwRet=REPORT_RECV_MSG(pair_socket_report_llrp,g_aucReportRevDataBuf,READER_MAX_RCV_MSG_LEN);
			 }
			 else if(items[1].revents & ZMQ_POLLIN)
			 {
			     dwRet=REPORT_RECV_MSG(pair_socket_report_rule,g_aucReportRevDataBuf,READER_MAX_RCV_MSG_LEN);
			 }

        

        if (dwRet<=0)
        {
            /*消息队列接收出错*/
            RdpErrorPrint("(Report)REPORT:MsgRcv Error\r\n");
            RDP_EXCEPT(RDP_RECV_MESSGAE_ERROR, dwRet, 0, 0, RDP_REPORT_ID);
            continue;
        }
		ptMsg = (T_Msg *)g_aucReportRevDataBuf;
        RdpReportDbgPrint("(Report)ptMsg->ucLinkType=%d\r\n", ptMsg->ucLinkType);
        RdpReportDbgPrint("(Report)ptMsg->ucLinkIndex=%d\r\n", ptMsg->ucLinkIndex);
        RdpReportDbgPrint("(Report)ptMsg->wMsgLen=%d\r\n", ptMsg->wMsgLen);
        RdpReportDbgPrint("(Report)ptMsg->wMsgID=%d\r\n", ptMsg->wMsgID);

        dwRet = reportWorkProc(ptMsg);
        if (RDP_SUCCESS != dwRet)
        {
            RdpErrorPrint("(Report) reportWorkProc error dwRet=0x%x\r\n", dwRet);
            continue;
        }
    }

    return RDP_SUCCESS;
}
