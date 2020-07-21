/***************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
*
* 文件名称：Rule.c
* 文件标识：
* 内容摘要：Rule模块实现
* 其它说明：
* 当前版本：
* 作    者：lzy 
* 完成日期：2012.02.29
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

#include "rdppub.h"
#include "rdpapppub.h"
#include "rule.h"


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
extern T_RdpConfig g_tRdpConfig;
T_RuleAODenymicList *s_ptRuleAODenymicList = NULL;
static unsigned char s_aucRuleRevDataBuf[READER_MAX_RCV_MSG_LEN];
static unsigned char s_aucRuleSendDataBuf[READER_MAX_SEND_MSG_LEN];
T_RuleROCtrlAndParam g_tRuleROCtrlAndParam[MAX_NUM_RO_SPEC];
void *pair_socket_rule_llrp=NULL;
void *pair_socket_rule_report=NULL;


extern void *push_socket_comm;
extern void *pull_socket_comm;
extern void *ctx;

/***********************************************************
 *                     本地变量                            *
***********************************************************/



/***********************************************************
 *                     全局函数                            *
***********************************************************/

/***********************************************************
 *                     局部函数                            *
***********************************************************/
static unsigned int ruleworkProc(T_Msg *ptMsg, LLRP_tSMessage *ptMessage);
static unsigned int rule_decodeMessage(T_Msg *ptMsg, LLRP_tSMessage **ptMessage);
static unsigned int rule_checkParameter(T_Msg *ptMsg, LLRP_tSMessage *ptMessage);
static unsigned int rule_transferAndSendMessage(T_Msg *ptMsg, LLRP_tSMessage *ptMessage);
static unsigned int rule_sendInnerMessageToLlrp(T_Msg *ptMsg, LLRP_tSMessage *ptMessage);
static unsigned int rule_sendAOInnerMessageToLlrp(T_Msg *ptMsg, unsigned int dwAOReportTrigger,LLRP_tSMessage *ptMessage);
static unsigned int rule_SendSuccessReponseMsgToClient(T_Msg *ptReceiveMsg, unsigned int dwMessageID);
static unsigned int rule_sendDeleteFilterNodeMsgToReport(T_RdpDeleteFilterNodes *ptDeleteFilterNodes);
static void rule_init();
/**************************************************************************
* 函数名称：void GetRDPLLTime()
* 功能描述：获得当前时间
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：struct timeval *ptCurrentTime 获取的时间
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/16    V1.0       lzy        创建
**************************************************************************/
void GetRDPLLTime(struct timeval *ptCurrentTime)
{

    if (gettimeofday(ptCurrentTime, NULL) != 0)
    {
        RdpRuleDbgPrint("gettimeofday is error\r\n");
    }

}
/**************************************************************************
* 函数名称：rule_SendSuccessReponseMsgToClient
* 功能描述：rule模块发送消息给后台
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptReceiveMsg 接收到的消息
*                             unsigned int dwMessageID llrp消息MessageID
*                             LLRP_tSMessage *ptLLRPMessage LLRP消息体
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/26    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_SendSuccessReponseMsgToClient(T_Msg *ptReceiveMsg, unsigned int dwMessageID)
{
    unsigned int dwRet = RDP_SUCCESS;
    T_Msg *ptSendMsg = NULL;
    LLRP_tSErrorDetails pError;
    T_RdpDeleteFilterNodes tDeleteFilterNodes;
    LLRP_tSADD_ROSPEC_RESPONSE *ptLLRP_tSADD_ROSPEC_RESPONSE = NULL;
    LLRP_tSADD_ACCESSSPEC_RESPONSE *ptLLRP_tSADD_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSDISABLE_ROSPEC_RESPONSE *ptLLRP_tSDISABLE_ROSPEC_RESPONSE = NULL;
    LLRP_tSDELETE_ROSPEC_RESPONSE *ptLLRP_tSDELETE_ROSPEC_RESPONSE = NULL;
    LLRP_tSDISABLE_ACCESSSPEC_RESPONSE *ptLLRP_tSDISABLE_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSDELETE_ACCESSSPEC_RESPONSE *ptLLRP_tSDELETE_ACCESSSPEC_RESPONSE = NULL;
    LLRP_tSSTOP_ROSPEC_RESPONSE *ptLLRP_tSSTOP_ROSPEC_RESPONSE = NULL;
    LLRP_tSERROR_MESSAGE *ptSERROR_MESSAG = NULL;
    LLRP_tSMessage *ptTempMessage = NULL;
    T_RdpLlrpRuleRsp *ptRdpLlrpRuleRsp = NULL;
    ptRdpLlrpRuleRsp = (T_RdpLlrpRuleRsp *)(ptReceiveMsg + 1);
    ptTempMessage = (LLRP_tSMessage *)ptRdpLlrpRuleRsp->ptRuleRspAddr;

    /*根据不同的消息构造 返回结构*/
    switch (ptReceiveMsg->wMsgID)
    {
    case EV_ADD_ROSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_ADD_ROSPEC_RESPONSE\r\n");
            ptLLRP_tSADD_ROSPEC_RESPONSE = LLRP_ADD_ROSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSADD_ROSPEC_RESPONSE;
            break;
        }
    case EV_ADD_ACCESSSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_ADD_ACCESSSPEC_RESPONSE\r\n");
            ptLLRP_tSADD_ACCESSSPEC_RESPONSE = LLRP_ADD_ACCESSSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSADD_ACCESSSPEC_RESPONSE;
            break;
        }
    case EV_DISABLE_ROSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_DISABLE_ROSPEC_RESPONSE\r\n");
            ptLLRP_tSDISABLE_ROSPEC_RESPONSE = LLRP_DISABLE_ROSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDISABLE_ROSPEC_RESPONSE;
            /*向Report 模块发送删除过滤结点消息*/
            tDeleteFilterNodes.ucDeleteType = RDP_DELETE_FILTER_TYPE_RO;
            tDeleteFilterNodes.dwRoOrAoId = ptRdpLlrpRuleRsp->dwRuleID;
            rule_sendDeleteFilterNodeMsgToReport(&tDeleteFilterNodes);
            break;
        }
    case EV_DELETE_ROSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_DELETE_ROSPEC_RESPONSE\r\n");
            ptLLRP_tSDELETE_ROSPEC_RESPONSE = LLRP_DELETE_ROSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDELETE_ROSPEC_RESPONSE;
            /*向Report 模块发送删除过滤结点消息*/
            tDeleteFilterNodes.ucDeleteType = RDP_DELETE_FILTER_TYPE_RO;
            tDeleteFilterNodes.dwRoOrAoId = ptRdpLlrpRuleRsp->dwRuleID;
            rule_sendDeleteFilterNodeMsgToReport(&tDeleteFilterNodes);
            break;
        }
    case EV_DISABLE_ACCESSSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_DISABLE_ACCESSSPEC_RESPONSE\r\n");
            ptLLRP_tSDISABLE_ACCESSSPEC_RESPONSE = LLRP_DISABLE_ACCESSSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDISABLE_ACCESSSPEC_RESPONSE;
            /*向Report 模块发送删除过滤结点消息*/
            tDeleteFilterNodes.ucDeleteType = RDP_DELETE_FILTER_TYPE_AO;
            tDeleteFilterNodes.dwRoOrAoId = ptRdpLlrpRuleRsp->dwRuleID;
            rule_sendDeleteFilterNodeMsgToReport(&tDeleteFilterNodes);
            break;
        }

    case EV_DELETE_ACCESSSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_DELETE_ACCESSSPEC_RESPONSE\r\n");
            ptLLRP_tSDELETE_ACCESSSPEC_RESPONSE = LLRP_DELETE_ACCESSSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSDELETE_ACCESSSPEC_RESPONSE;
            /*向Report 模块发送删除过滤结点消息*/
            tDeleteFilterNodes.ucDeleteType = RDP_DELETE_FILTER_TYPE_AO;
            tDeleteFilterNodes.dwRoOrAoId = ptRdpLlrpRuleRsp->dwRuleID;
            rule_sendDeleteFilterNodeMsgToReport(&tDeleteFilterNodes);
            break;
        }
    case EV_STOP_ROSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)EV_STOP_ROSPEC_RESPONSE\r\n");
            ptLLRP_tSSTOP_ROSPEC_RESPONSE = LLRP_STOP_ROSPEC_RESPONSE_construct();
            ptSERROR_MESSAG = (LLRP_tSERROR_MESSAGE *)ptLLRP_tSSTOP_ROSPEC_RESPONSE;
            break;
        }
    case EV_ENABLE_ROSPEC_RESPONSE:
    case EV_START_ROSPEC_RESPONSE:
    case EV_ENABLE_ACCESSSPEC_RESPONSE:
        {
            RdpRuleDbgPrint("(RULE)RESPONSE NEED DESTRUCT\r\n");
            break;
        }
    default:
        {
            RdpRuleDbgPrint("(RULE)the Msg ID is not supported =%d\r\n", ptReceiveMsg->wMsgID);
            RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, ptReceiveMsg->wMsgID, 0, 0, RDP_RULE_ID);
            break;
        }

    }

    if (NULL != ptTempMessage)
    {
        usp_ltk_freeMessage((LLRP_tSMessage *)ptTempMessage);
    }

    /*构造结构*/
    if (ptSERROR_MESSAG != NULL)
    {
        LLRP_tSLLRPStatus *ptSLLRPStatus = LLRP_LLRPStatus_construct();
        ptSLLRPStatus->eStatusCode = LLRP_StatusCode_M_Success;
        LLRP_ERROR_MESSAGE_setLLRPStatus(ptSERROR_MESSAG, ptSLLRPStatus);
        ptSERROR_MESSAG->pLLRPStatus = ptSLLRPStatus;
        ptSERROR_MESSAG->hdr.MessageID = dwMessageID;
        ptSendMsg = (T_Msg *)s_aucRuleSendDataBuf;
        ptSendMsg->ucLinkIndex = ptReceiveMsg->ucLinkIndex;
        ptSendMsg->ucLinkType = ptReceiveMsg->ucLinkType;
        ptSendMsg->mtype = ptReceiveMsg->mtype;
        ptSendMsg->wMsgSequence = ptReceiveMsg->wMsgSequence;
        ptSendMsg->wSenderTno = USP_RDP_RULE_TNO;
        ptSendMsg->wReceiverTno = ptReceiveMsg->wReceiverTno;
        ptSendMsg->wMsgID = EV_USP_COMM_SendData;
        ptSendMsg->wMsgLen = READER_MAX_SEND_MSG_LEN - sizeof(T_Msg);
        RdpRuleDbgPrint("(RULE)ptSendMsg->wReceiverTno=%d\r\n" , ptSendMsg->wReceiverTno);
        /*向外发送*/
        dwRet = usp_ltk_encodeMessage((unsigned char *)(ptSendMsg + 1),
                                      &ptSendMsg->wMsgLen,
                                      (LLRP_tSMessage *)ptSERROR_MESSAG, &pError);

        if (dwRet != RDP_SUCCESS)
        {
            RdpRuleDbgPrint("(RULE)usp_ltk_encodeMessage Error ptSendMsg->dwRet=%d\r\n" , dwRet);
            RDP_EXCEPT(RDP_ENCODE_MESSAGE_ERROR, dwRet, 0, 0, RDP_RULE_ID);
            usp_ltk_freeMessage((LLRP_tSMessage *)ptSERROR_MESSAG);
            return dwRet;
        }

        if (RDP_SUCCESS > RDP_SEND_MSG(push_socket_comm, ptSendMsg))
        {
            RdpRuleDbgPrint("(RULE)MsgSend Error\r\n");
            RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, 0, 0, 0, RDP_RULE_ID);
            usp_ltk_freeMessage((LLRP_tSMessage *)ptSERROR_MESSAG);
            return RDP_SEND_MESSGAE_ERROR;
        }

        RdpRuleDbgPrint("(RULE)MsgSend Success dwMessageID=%d\r\n", dwMessageID);
        usp_ltk_freeMessage((LLRP_tSMessage *)ptSERROR_MESSAG);

    }
    return dwRet;
}
/**************************************************************************
* 函数名称：rule_SendMsgToClient
* 功能描述：rule模块发送消息给后台
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptReceiveMsg 接收到的消息
*                             unsigned int dwMessageID llrp消息MessageID
*                             LLRP_tSMessage *ptLLRPMessage LLRP消息体
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/26    V1.0       lzy        创建
**************************************************************************/
unsigned int rule_SendMsgToClient(T_Msg *ptReceiveMsg,
                            unsigned int dwMessageID ,
                            LLRP_tSMessage *ptLLRPMessage)
{

    unsigned int dwRet = RDP_SUCCESS;
    T_Msg *ptSendMsg = NULL;
    LLRP_tSErrorDetails pError;

    ptSendMsg = (T_Msg *)s_aucRuleSendDataBuf;
    ptLLRPMessage->MessageID = dwMessageID;
    ptSendMsg->ucLinkIndex = ptReceiveMsg->ucLinkIndex;
    ptSendMsg->ucLinkType = ptReceiveMsg->ucLinkType;
    ptSendMsg->mtype = ptReceiveMsg->mtype;
    ptSendMsg->wMsgSequence = ptReceiveMsg->wMsgSequence;
    ptSendMsg->wSenderTno = USP_RDP_RULE_TNO;
    ptSendMsg->wReceiverTno = ptReceiveMsg->wSenderTno;
    ptSendMsg->wSrcTno = USP_RDP_RULE_TNO;
    ptSendMsg->wDstTno = ptReceiveMsg->wSrcTno;
    ptSendMsg->wMsgID = EV_USP_COMM_SendData;
    ptSendMsg->wMsgLen = READER_MAX_SEND_MSG_LEN - sizeof(T_Msg);
    /*向外发送*/
    RdpRuleDbgPrint("(RULE)ptSendMsg->wReceiverTno=%d\r\n" , ptSendMsg->wReceiverTno);
    dwRet = usp_ltk_encodeMessage((unsigned char *)(ptSendMsg + 1), &ptSendMsg->wMsgLen, ptLLRPMessage, &pError);

    if (dwRet != RDP_SUCCESS)
    {
        RdpRuleDbgPrint("(RULE)usp_ltk_encodeMessage Error ptSendMsg->dwRet=%d\r\n" , dwRet);
        return dwRet;
    }

    if (RDP_SUCCESS > RDP_SEND_MSG(push_socket_comm, ptSendMsg))
    {
        RdpRuleDbgPrint("(RULE)MsgSend Error\r\n");
        return dwRet;

    }

    RdpRuleDbgPrint("(RULE)rule_SendMsgToClient MsgSend Success\r\n");
    return dwRet;

}

/**************************************************************************
* 函数名称：rule_decodeMessage
* 功能描述：Rule模块解码消息处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要处理的消息
                              LLRP_tSMessage *ptMessage 要处理的llrp内容
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_decodeMessage(T_Msg *ptMsg, LLRP_tSMessage **ptMessage)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned char *pucDataBuf = NULL;
    LLRP_tSErrorDetails tError;
    LLRP_tSMessage *ptMeMessage = NULL;
	int loop=0;
    if (EV_USP_COMM_RecvData == ptMsg->wMsgID)
    {
        RdpRuleDbgPrint("this is EV_USP_COMM_RecvData Msg\r\n");
        pucDataBuf = (unsigned char *)(ptMsg + 1);
		for(loop=0;loop<ptMsg->wMsgLen;loop++)
		{
			RdpDbgPrintRaw("0x%x ",pucDataBuf[loop]);
		}
		RdpDbgPrintRaw("\r\n");
        ptMeMessage = usp_ltk_decodeMessage(pucDataBuf, ptMsg->wMsgLen, &tError);

        if (LLRP_RC_OK != tError.eResultCode || NULL == ptMeMessage)
        {
            RdpRuleDbgPrint("usp_ltk_decodeMessage Error,pError.eResultCode = %d\r\n", tError.eResultCode);
            RDP_EXCEPT(RDP_DECODE_MESSAGE_ERROR, tError.eResultCode, 0, 0, RDP_RULE_ID);
            return RDP_DECODE_MESSAGE_ERROR;
        }
        ptMsg->wMsgID = ptMeMessage->elementHdr.pType->TypeNum;
    }
    *ptMessage = ptMeMessage;
    return dwRet;
}

/**************************************************************************
* 函数名称：rule_transROToInnerCtrlState
* 功能描述：Rule模块转变RO控制信息到内部结构
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要处理的消息
            LLRP_tSMessage *ptMessage 要处理的llrp内容
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_transROToInnerCtrlState(T_Msg *ptMsg, LLRP_tSMessage *ptMessage)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned short int wMsgID = 0;
    unsigned short int wSenderTno = 0;     /* 发送端任务号 */
    unsigned short int wLoop = 0;
    LLRP_tSADD_ROSPEC *ptAddRospec = NULL;
    LLRP_tSENABLE_ROSPEC *ptEnableRospec = NULL;
    LLRP_tSDISABLE_ROSPEC *ptDisableRospec = NULL;
    LLRP_tSDELETE_ROSPEC *ptDeleteRospec = NULL;
    LLRP_tSSTOP_ROSPEC *ptStopRospec = NULL;
    LLRP_tSSTART_ROSPEC *ptStartRospec = NULL;
    wSenderTno = ptMsg->wSenderTno;
    wMsgID = ptMsg->wMsgID;
    if (NULL == ptMessage)
    {
        RdpRuleDbgPrint("(rule_transROToInnerCtrlState)wSenderTno is not Client meg.wSenderTno=%d,wMsgID=%d\r\n", wSenderTno, wMsgID);
        return RULE_SENG_MESSAGE_TO_LLRP_YES;
    }

    switch (wMsgID)
    {
    case EV_ADD_ROSPEC:
        {
            ptAddRospec = (LLRP_tSADD_ROSPEC *)ptMessage;
            for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
            {
                if (FALSE == g_tRuleROCtrlAndParam[wLoop].dwUseing)
                {
                    break;
                }
            }
            if (MAX_NUM_RO_SPEC == wLoop)
            {
                RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, ptAddRospec->pROSpec->ROSpecID, 0, RDP_RULE_ID);
                return RDP_FAILED;
            }
            g_tRuleROCtrlAndParam[wLoop].dwROSpecID = ptAddRospec->pROSpec->ROSpecID;
            g_tRuleROCtrlAndParam[wLoop].eCurrentState = ptAddRospec->pROSpec->eCurrentState;
            g_tRuleROCtrlAndParam[wLoop].dwUseing = TRUE;
            g_tRuleROCtrlAndParam[wLoop].ucLinkIndex = ptMsg->ucLinkIndex;
            g_tRuleROCtrlAndParam[wLoop].ucLinkType = ptMsg->ucLinkType;
            break;
        }
    case EV_ENABLE_ROSPEC:
        {
            ptEnableRospec = (LLRP_tSENABLE_ROSPEC *)ptMessage;
            if (0 != ptEnableRospec->ROSpecID)
            {
                for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
                {
                    if ((ptEnableRospec->ROSpecID == g_tRuleROCtrlAndParam[wLoop].dwROSpecID)
                            && (ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                            && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                            && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                    {
                        break;
                    }
                }
                if (MAX_NUM_RO_SPEC == wLoop)
                {
                    RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, ptEnableRospec->ROSpecID, ptMsg->ucLinkIndex, RDP_RULE_ID);
                    return RDP_FAILED;
                }
                g_tRuleROCtrlAndParam[wLoop].eCurrentState = LLRP_ROSpecState_Inactive;
            }
            else
            {
                for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
                {
                    if ((ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                            && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                            && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing)
                            && (LLRP_ROSpecState_Disabled == g_tRuleROCtrlAndParam[wLoop].eCurrentState))
                    {
                        g_tRuleROCtrlAndParam[wLoop].eCurrentState = LLRP_ROSpecState_Inactive;
                    }
                }
            }
            break;
        }
    case EV_DISABLE_ROSPEC:
        {
            ptDisableRospec = (LLRP_tSDISABLE_ROSPEC *)ptMessage;
            if (0 != ptDisableRospec->ROSpecID)
            {
                for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
                {
                    if ((ptDisableRospec->ROSpecID == g_tRuleROCtrlAndParam[wLoop].dwROSpecID)
                            && (ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                            && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                            && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                    {
                        break;
                    }
                }
                if (MAX_NUM_RO_SPEC == wLoop)
                {
                    RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, ptDisableRospec->ROSpecID, ptMsg->ucLinkIndex, RDP_RULE_ID);
                    return RDP_FAILED;
                }
                g_tRuleROCtrlAndParam[wLoop].eCurrentState = LLRP_ROSpecState_Disabled;
            }
            else
            {
                for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
                {
                    if ((ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                            && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                            && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                    {
                        g_tRuleROCtrlAndParam[wLoop].eCurrentState = LLRP_ROSpecState_Disabled;
                    }
                }
            }
            break;
        }
    case EV_DELETE_ROSEPC:
        {
            ptDeleteRospec = (LLRP_tSDELETE_ROSPEC *)ptMessage;
            if (0 != ptDeleteRospec->ROSpecID)
            {
                for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
                {
                    if ((ptDeleteRospec->ROSpecID == g_tRuleROCtrlAndParam[wLoop].dwROSpecID)
                            && (ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                            && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                            && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                    {
                        break;
                    }
                }
                if (MAX_NUM_RO_SPEC == wLoop)
                {
                    RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, ptDeleteRospec->ROSpecID, ptMsg->ucLinkIndex, RDP_RULE_ID);
                    return RDP_FAILED;
                }
                memset(&g_tRuleROCtrlAndParam[wLoop], 0, sizeof(g_tRuleROCtrlAndParam[wLoop]));
                g_tRuleROCtrlAndParam[wLoop].dwUseing = FALSE;
            }
            else
            {
                for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
                {
                    if ((ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                            && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                            && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                    {
                        memset(&g_tRuleROCtrlAndParam[wLoop], 0, sizeof(g_tRuleROCtrlAndParam[wLoop]));
                        g_tRuleROCtrlAndParam[wLoop].dwUseing = FALSE;
                    }
                }
            }
            break;
        }
    case EV_STOP_ROSPEC:
        {
            ptStopRospec = (LLRP_tSSTOP_ROSPEC *)ptMessage;
            for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
            {
                if ((ptStopRospec->ROSpecID == g_tRuleROCtrlAndParam[wLoop].dwROSpecID)
                        && (ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                        && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                        && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                {
                    break;
                }
            }
            if (MAX_NUM_RO_SPEC == wLoop)
            {
                RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, ptStopRospec->ROSpecID, ptMsg->ucLinkIndex, RDP_RULE_ID);
                return RDP_FAILED;
            }
            g_tRuleROCtrlAndParam[wLoop].eCurrentState = LLRP_ROSpecState_Inactive;
            break;
        }
    case EV_START_ROSPEC:
        {
            ptStartRospec = (LLRP_tSSTART_ROSPEC *)ptMessage;
            for (wLoop = 0;wLoop < MAX_NUM_RO_SPEC;wLoop++)
            {
                if ((ptStartRospec->ROSpecID == g_tRuleROCtrlAndParam[wLoop].dwROSpecID)
                        && (ptMsg->ucLinkIndex == g_tRuleROCtrlAndParam[wLoop].ucLinkIndex)
                        && (ptMsg->ucLinkType == g_tRuleROCtrlAndParam[wLoop].ucLinkType)
                        && (TRUE == g_tRuleROCtrlAndParam[wLoop].dwUseing))
                {
                    break;
                }
            }
            if (MAX_NUM_RO_SPEC == wLoop)
            {
                RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, ptStartRospec->ROSpecID, ptMsg->ucLinkIndex, RDP_RULE_ID);
                return RDP_FAILED;
            }
            g_tRuleROCtrlAndParam[wLoop].eCurrentState = LLRP_ROSpecState_Active;
            break;
        }
    default:
        {
            RdpRuleDbgPrint("(rule_transROToInnerCtrlState)receive not needed id wMsgid= %d\r\n", wMsgID);
            break;
        }
    }
    return dwRet;

}
/**************************************************************************
* 函数名称：rule_checkParameter
* 功能描述：Rule模块LLRP消息参数校验
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要处理的消息
                              LLRP_tSMessage *ptMessage 要处理的llrp内容
* 输出参数：无
* 返 回 值：0:消息往下走其他不往下走
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_checkParameter(T_Msg *ptMsg, LLRP_tSMessage *ptMessage)
{
    unsigned int dwRet = RULE_SENG_MESSAGE_TO_LLRP_YES;
    unsigned short int wMsgID = 0;
    unsigned short int wSenderTno = 0;     /* 发送端任务号 */
    wSenderTno = ptMsg->wSenderTno;
    wMsgID = ptMsg->wMsgID;
    if (NULL == ptMessage)
    {
        RdpRuleDbgPrint("(Rule rule_checkParameter)wSenderTno is not Client meg.wSenderTno=%d,wMsgID=%d\r\n", wSenderTno, wMsgID);
        return RULE_SENG_MESSAGE_TO_LLRP_YES;
    }

   
   RdpRuleDbgPrint("(Rule check)ptMessage->MessageID=%d\r\n", ptMessage->MessageID);
    switch (wMsgID)
    {
    case EV_ADD_ROSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_ADD_ROSPEC\r\n");
            dwRet = rule_checkAddROSpec(ptMsg, (LLRP_tSADD_ROSPEC *)ptMessage);
            break;
        }
    case EV_ENABLE_ROSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_ENABLE_ROSPEC\r\n");
            dwRet = rule_checkEnableROSpec(ptMsg, (LLRP_tSENABLE_ROSPEC *)ptMessage);
            break;
        }
    case EV_DISABLE_ROSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_DISABLE_ROSPEC\r\n");
            dwRet = rule_checkDisableROSpec(ptMsg, (LLRP_tSDISABLE_ROSPEC *)ptMessage);
            break;
        }
    case EV_DELETE_ROSEPC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_DELETE_ROSEPC\r\n");
            dwRet = rule_checkDeleteROSpec(ptMsg, (LLRP_tSDELETE_ROSPEC *)ptMessage);
            break;
        }
    case EV_STOP_ROSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_STOP_ROSPEC\r\n");
            dwRet = rule_checkStopROSpec(ptMsg, (LLRP_tSSTOP_ROSPEC *)ptMessage);
            break;
        }
    case EV_START_ROSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg receive msg EV_START_ROSPEC\r\n");
            dwRet = rule_checkStartROSpec(ptMsg, (LLRP_tSSTART_ROSPEC *)ptMessage);
            break;
        }
    case EV_ADD_ACCESSSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_ADD_ACCESSSPEC\r\n");
            dwRet = rule_checkAddAccessspec(ptMsg, (LLRP_tSADD_ACCESSSPEC *)ptMessage);
            break;
        }
    case EV_ENABLE_ACCESSSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_ENABLE_ACCESSSPEC\r\n");
            dwRet = rule_checkEnableAccesssSpec(ptMsg, (LLRP_tSENABLE_ACCESSSPEC *)ptMessage);
            break;
        }
    case EV_DISABLE_ACCESSSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_DISABLE_ACCESSSPEC\r\n");
            dwRet = rule_checkDisableAccesssSpec(ptMsg, (LLRP_tSDISABLE_ACCESSSPEC *)ptMessage);
            break;
        }
    case EV_DELETE_ACCESSSPEC:
        {
            RdpRuleDbgPrint("(Rule check)receive msg EV_DELETE_ACCESSSPEC\r\n");
            dwRet = rule_checkDeleteAccesssSpec(ptMsg, (LLRP_tSDELETE_ACCESSSPEC *)ptMessage);
            break;
        }
    case EV_GET_ACCESSSPECS:
    case EV_GET_REPOERT:
    case EV_GET_ROSPEC:
    case EV_UHF_PRIVATE_CMD:
    case EV_UHF_PRIVATE_SETPASSWORD:
    case EV_CLIENT_REQUEST_OP_RESPONSE:
    

        {
            RdpRuleDbgPrint("(Rule check)receive  wMsgid= %d,continue\r\n", wMsgID);
            break;
        }
    default:
        {
            RdpRuleDbgPrint("(Rule check)receive wrong id wMsgid= %d\r\n", wMsgID);
            RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, 0, 0, RDP_RULE_ID);
            break;
        }
    }
    if (RDP_SUCCESS != dwRet)
    {
        dwRet = RULE_SENG_MESSAGE_TO_LLRP_NO;
    }
    else
    {
        dwRet = RULE_SENG_MESSAGE_TO_LLRP_YES;
        /*将RO转为内部状态*/
        rule_transROToInnerCtrlState(ptMsg, ptMessage);
    }
    return dwRet;

}
/**************************************************************************
* 函数名称：rule_sendInnerMessageToLlrp
* 功能描述：发送消息给llrp模块
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要处理的消息
                              LLRP_tSMessage *ptMessage 要发送的llrp内容
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_sendInnerMessageToLlrp(T_Msg *ptMsg, LLRP_tSMessage *ptMessage)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned int *pdwTempAddr = NULL;
    T_Msg *ptSendMsg = NULL;
    ptSendMsg = (T_Msg *)s_aucRuleSendDataBuf;
    memcpy(ptSendMsg, ptMsg, sizeof(T_Msg));
    pdwTempAddr = (unsigned int *)(ptSendMsg + 1);
    ptSendMsg->wSrcTno = USP_RDP_RULE_TNO;
    ptSendMsg->wDstTno = USP_RDP_LLRP_TNO;
    ptSendMsg->wSenderTno = ptMsg->wSenderTno;
    ptSendMsg->wReceiverTno = ptMsg->wReceiverTno;
    ptSendMsg->wMsgLen = sizeof(unsigned int);
    *pdwTempAddr = (unsigned int)ptMessage;
    dwRet = RULE_SEND_MSG(pair_socket_rule_llrp, ptSendMsg);
    RdpRuleDbgPrint("(RULE)rule send Inner Message To Llrp dwRet=%d,ptMessage=0x%x\r\n", dwRet, ptMessage);
    return dwRet;
}
/**************************************************************************
* 函数名称：rule_sendAOInnerMessageToLlrp
* 功能描述：发送消息给llrp模块
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg, 
                              unsigned int dwAOReportTrigger,
                              Ao的原有的reportTrigger 
                              LLRP_tSMessage *ptMessage
                              Ao的地址
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_sendAOInnerMessageToLlrp(T_Msg *ptMsg, unsigned int dwAOReportTrigger,LLRP_tSMessage *ptMessage)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned int *pdwTempAddr = NULL;
    T_RdpAddAo *ptRdpAddAo = NULL;
    T_Msg *ptSendMsg = NULL;
    ptSendMsg = (T_Msg *)s_aucRuleSendDataBuf;
    memcpy(ptSendMsg, ptMsg, sizeof(T_Msg));
    ptRdpAddAo = (T_RdpAddAo *)(ptSendMsg+1);
    ptSendMsg->wSrcTno = USP_RDP_RULE_TNO;
    ptSendMsg->wDstTno = USP_RDP_LLRP_TNO;
    ptSendMsg->wSenderTno = ptMsg->wSenderTno;
    ptSendMsg->wReceiverTno = ptMsg->wReceiverTno;
    ptSendMsg->wMsgLen = sizeof(T_RdpAddAo);
    ptRdpAddAo->dwAOReportSndTrigger =dwAOReportTrigger;
    ptRdpAddAo->ptAddAoMsgAddr = ptMessage;
    dwRet = RULE_SEND_MSG(pair_socket_rule_llrp, ptSendMsg);
    RdpRuleDbgPrint("(RULE)rule send Inner Message To Llrp dwRet=%d,ptMessage=0x%x\r\n", dwRet, ptMessage);
    return dwRet;
}

/**************************************************************************
* 函数名称：rule_sendDeleteFilterNodeMsgToReport
* 功能描述：发送删除过滤结点消息给report模块
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpDeleteFilterNodes *ptDeleteFilterNodes删除结点结构体
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_sendDeleteFilterNodeMsgToReport(T_RdpDeleteFilterNodes *ptDeleteFilterNodes)
{
    unsigned int dwRet = RDP_SUCCESS;
    T_Msg *ptSendMsg = NULL;
    T_RdpDeleteFilterNodes *ptTempDeleteFilterNodes = NULL;
    ptSendMsg = (T_Msg *)s_aucRuleSendDataBuf;
    ptTempDeleteFilterNodes = (T_RdpDeleteFilterNodes *)(ptSendMsg + 1);
    ptSendMsg->mtype = 1;
    ptSendMsg->wSenderTno = USP_RDP_RULE_TNO;
    ptSendMsg->wReceiverTno = USP_RDP_REPORT_TNO;
    ptSendMsg->wSrcTno = USP_RDP_RULE_TNO;
    ptSendMsg->wDstTno = USP_RDP_REPORT_TNO;
    ptSendMsg->wMsgID = EV_USP_RDP_DELETE_FILTER_NODE;
    ptSendMsg->wMsgLen = sizeof(T_RdpDeleteFilterNodes);
    memcpy(ptTempDeleteFilterNodes, ptDeleteFilterNodes, sizeof(T_RdpDeleteFilterNodes));
    dwRet = RULE_SEND_MSG(pair_socket_rule_report, ptSendMsg);
    RdpRuleDbgPrint("(Rule)rule_sendDeleteFilterNodeMsgToReport dwRet=%d\r\n", dwRet);
    return dwRet;
}

/**************************************************************************
* 函数名称：rule_transferAndSendMessage
* 功能描述：透传模块处理
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要处理的消息
                              LLRP_tSMessage *ptMessage 要处理的llrp内容
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int rule_transferAndSendMessage(T_Msg *ptMsg, LLRP_tSMessage *ptMessage)
{
    unsigned int dwRet = RDP_SUCCESS;
    unsigned short int wMsgID = 0;
    unsigned short int wSenderTno = 0;
    LLRP_tSERROR_MESSAGE *ptRuleRsp = NULL;
    T_RdpLlrpRuleRsp *ptRdpLlrpRuleRsp = NULL;
    LLRP_tSMessage *ptTempMessage = NULL;
    LLRP_tSADD_ACCESSSPEC * ptAddAccessspec = NULL;
    wMsgID = ptMsg->wMsgID;
    wSenderTno = ptMsg->wSenderTno;
    RdpRuleDbgPrint("(Rule transfer)wMsgID=%d,wSenderTno=%d\r\n", wMsgID, wSenderTno);
    if ((USP_RDP_LLRP_TNO != wSenderTno) && (NULL != ptMessage))
    {
        /*向LLRP模块透传LLRP消息*/
        RdpRuleDbgPrint("(Rule transfer)Client Message transfer to LLRP module\r\n");

       
        if( EV_ADD_ACCESSSPEC == ptMessage->elementHdr.pType->TypeNum )
        {
             ptAddAccessspec = (LLRP_tSADD_ACCESSSPEC *)ptMessage;
             RdpRuleDbgPrint("(Rule transfer)test1\r\n");
   
             
             dwRet = rule_sendAOInnerMessageToLlrp(ptMsg,
                                                                             ptAddAccessspec->pAccessSpec->pAccessReportSpec  == NULL? \
                                                                             g_tRdpConfig.tAccessReportSpec.eAccessReportTriggerType: \
                                                                             ptAddAccessspec->pAccessSpec->pAccessReportSpec->eAccessReportTrigger ,ptMessage);               
        }
        else
        {
        dwRet = rule_sendInnerMessageToLlrp(ptMsg, ptMessage);
    }
        
        
    }
    else
    {
        if (NULL != ptMessage)
        {
            RDP_EXCEPT(RDP_MSG_PROC_ERROR, ptMsg->wDstTno, ptMsg->wMsgID, ptMsg->wSenderTno, RDP_RULE_ID);
            RdpRuleDbgPrint("(Rule transfer)inner msg but ptMessage is not NULL ptMsg->wMsgID=%d ,wSenderTno=%d\r\n",
                            ptMsg->wMsgID, wSenderTno);
            usp_ltk_freeMessage(ptMessage);
            return RDP_MSG_PROC_ERROR;
        }

        switch (wMsgID)
        {
        case EV_ADD_ROSPEC_RESPONSE:
        case EV_ENABLE_ROSPEC_RESPONSE:
        case EV_DISABLE_ROSPEC_RESPONSE:
        case EV_DELETE_ROSPEC_RESPONSE:
        case EV_STOP_ROSPEC_RESPONSE:
        case EV_START_ROSPEC_RESPONSE:
        case EV_ADD_ACCESSSPEC_RESPONSE:
        case EV_DISABLE_ACCESSSPEC_RESPONSE:
        case EV_ENABLE_ACCESSSPEC_RESPONSE:
        case EV_DELETE_ACCESSSPEC_RESPONSE:
            {
                ptRdpLlrpRuleRsp = (T_RdpLlrpRuleRsp *)(ptMsg + 1);
                ptRuleRsp = ptRdpLlrpRuleRsp->ptRuleRspAddr;
                RdpRuleDbgPrint("(Rule transfer)Inner msg from module LLRP the addr is 0x%x,Rule ID=%d\r\n",
                                ptRuleRsp, ptRdpLlrpRuleRsp->dwRuleID);
                rule_SendSuccessReponseMsgToClient(ptMsg, ptRuleRsp->hdr.MessageID);
                break;
            }
        case EV_GET_ACCESSSPECS_RESPONSE:
        case EV_GET_ROSPEC_RESPONSE:
        case EV_CLIENT_REQUEST_OP:
        case EV_UHF_PRIVATE_CMD_ACK:
        case EV_UHF_PRIVATE_SETPASSWORD_ACK:
            {
                if (USP_RDP_RULE_TNO == ptMsg->wReceiverTno)
                {
                    RDP_EXCEPT(RDP_MSG_PROC_ERROR, ptMsg->wDstTno, ptMsg->wMsgID, 0, RDP_RULE_ID);
                    RdpRuleDbgPrint("(Rule transfer) rule_transferAndSendMessage wDstTno error ptMsg->wDstTno=%d,ptMsg->wMsgID=%d\r\n",
                                    ptMsg->wDstTno, ptMsg->wMsgID);
                }
                ptTempMessage = (LLRP_tSMessage *)(*(unsigned int *)(ptMsg + 1));
                /*不开起操作过滤天线联动时转发给后台*/
                ptMsg->wSenderTno = ptMsg->wReceiverTno;
                ptMsg->wSrcTno = ptMsg->wDstTno;
                dwRet = rule_SendMsgToClient(ptMsg, ptTempMessage->MessageID, (LLRP_tSMessage *)ptTempMessage);
                if (wMsgID != EV_GET_ACCESSSPECS_RESPONSE && wMsgID != EV_GET_ROSPEC_RESPONSE)
                {
                    usp_ltk_freeMessage((LLRP_tSMessage *)ptTempMessage);
                }
                break;
            }
        case EV_RDP_DELETE_OPERATION_COUNT_ACCESS:
            {
                RdpRuleDbgPrint("((Rule transfer) receive an EV_RDP_DELETE_OPERATION_COUNT_ACCESS msg\r\n");
                break;
            }
        default:
            {
                RdpRuleDbgPrint("(Rule transfer) inner msg default wMsgID=%d\r\n", wMsgID);
                RDP_EXCEPT(RDP_INVALID_STATE, wMsgID, 0, 0, RDP_RULE_ID);
                break;
            }
        }
    }
    return dwRet;
}
/**************************************************************************
* 函数名称：rule_init
* 功能描述：规则下发模块初始化处理
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
static void rule_init()
{
    /* 初始化全局变量 */
    memset(s_aucRuleRevDataBuf, 0, sizeof(s_aucRuleRevDataBuf));
    memset(s_aucRuleSendDataBuf, 0, sizeof(s_aucRuleSendDataBuf));
    memset(g_tRuleROCtrlAndParam, 0, sizeof(g_tRuleROCtrlAndParam));
    return ;
}
/**************************************************************************
* 函数名称：ruleworkProc
* 功能描述：rule模块功能模块处理 
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要处理的消息
                              LLRP_tSMessage *ptMessage 要处理的llrp内容
* 输出参数：无
* 返 回 值：0:成功;其他:失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/27    V1.0       lzy        创建
**************************************************************************/
static unsigned int ruleworkProc(T_Msg *ptMsg, LLRP_tSMessage *ptMessage)
{
    unsigned int dwRet = RULE_SENG_MESSAGE_TO_LLRP_YES;

    /*参数校验*/
    dwRet = rule_checkParameter(ptMsg, ptMessage);
    if (RULE_SENG_MESSAGE_TO_LLRP_YES != dwRet)
    {
        /*不需要透传给LLRP模块时，需要析构动态内存*/
        if (NULL != ptMessage)
        {
            usp_ltk_freeMessage(ptMessage);
        }
        return dwRet;
    }
    /*透传消息*/
    dwRet = rule_transferAndSendMessage(ptMsg, ptMessage);
    return dwRet;
}


void create_zmq_sockets_rule(void)
{
    
    int value;
    int ret;
	
    /*inproc llrp*/
	pair_socket_rule_llrp = zmq_socket(ctx, ZMQ_PAIR);
    if(NULL == pair_socket_rule_llrp)
    {
        printf("create pair_socket_rule_llrp fail!\n");
        exit(-1);
    }
    ret = zmq_connect(pair_socket_rule_llrp, "inproc://rule.inproc");
	if(ret<0)
    {
        printf("zmq_connect pair_socket_rule_llrp fail!\n");
        exit(-1);
    }

	/*inproc report */
	pair_socket_rule_report = zmq_socket(ctx, ZMQ_PAIR);
    if(NULL == pair_socket_rule_report)
    {
        printf("create pair_socket_rule_report fail!\n");
        exit(-1);
    }
    ret = zmq_bind(pair_socket_rule_report, "inproc://rule_report.inproc");
	if(ret<0)
    {
        printf("zmq_connect pair_socket_rule_report fail!\n");
        exit(-1);
    }
    return;
}

/**************************************************************************
* 函数名称：usp_rdp_rule_Entry
* 功能描述：rdp规则处理线程入口函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/1    V1.0       lzy        创建
**************************************************************************/
unsigned int rdp_rule_main()
{
    zmq_pollitem_t	items[2];
	int item_num;
	int rc;
    T_Msg *ptMsg = NULL;
    unsigned int dwRet = RDP_SUCCESS;
    LLRP_tSMessage *ptMessage = NULL;

    RdpRuleDbgPrint("(usp_rdp_rule_Entry) running...... \r\n");
	
	create_zmq_sockets_rule();

	/*模块初始化*/
    rule_init();

    /* 等待配置完成 */
    while ((FALSE == g_bRdpPowerOnCfgFinish) && (FALSE == g_bReportInitFinish))
    {
        usleep(10000);
    }
    
     memset(items,0,sizeof(items));
		 items[0].socket = pull_socket_comm;
		 items[0].events = ZMQ_POLLIN;
		 items[1].socket = pair_socket_rule_llrp;
		 items[1].events = ZMQ_POLLIN;
    RdpRuleDbgPrint("(RULE)come into rdp_rule_main\r\n");
    /*  进入消息处理 */
    for (;;)
    {
		rc = zmq_poll(items, 2, -1);
			 if(rc<0)
			 {
				RdpRuleDbgPrint("(RULE)zmq_poll return , return %d %d,%s\n", rc,errno,zmq_strerror(errno));
				continue;
			 }
			 if(items[0].revents & ZMQ_POLLIN)
			 {
			     dwRet=RULE_RECV_MSG(pull_socket_comm,s_aucRuleRevDataBuf,READER_MAX_RCV_MSG_LEN);
			 }
			 else if(items[1].revents & ZMQ_POLLIN)
			 {
			     dwRet=RULE_RECV_MSG(pair_socket_rule_llrp,s_aucRuleRevDataBuf,READER_MAX_RCV_MSG_LEN);
			 }
        

        if (dwRet<=0)
        {
            /*消息队列接收出错*/
            RdpErrorPrint("(RULE)MsgRcv Error\r\n");
            RDP_EXCEPT(RDP_RECV_MESSGAE_ERROR, dwRet, 0, 0, RDP_RULE_ID);
            continue;
        }
        ptMsg = (T_Msg *)s_aucRuleRevDataBuf;
        dwRet = rule_decodeMessage(ptMsg, &ptMessage);
        if (RDP_SUCCESS != dwRet)
        {
            RDP_EXCEPT(RDP_MSG_PROC_ERROR, dwRet, ptMsg->wMsgID, (unsigned int)ptMessage, RDP_RULE_ID);
            RdpErrorPrint("(Rule) rule_decodeMessage error dwRet=0x%x\r\n", dwRet);
            continue;
        }
        RdpRuleDbgPrint("(Rule)ptMsg->wSenderTno=%d\r\n", ptMsg->wSenderTno);
        RdpRuleDbgPrint("(Rule)ptMsg->ucLinkIndex=%d\r\n", ptMsg->ucLinkIndex);
        RdpRuleDbgPrint("(Rule)ptMsg->wMsgLen=%d\r\n", ptMsg->wMsgLen);
        RdpRuleDbgPrint("(Rule)ptMsg->wMsgID=%d\r\n", ptMsg->wMsgID);
        RdpRuleDbgPrint("(Rule)ptMessage=0x%x\r\n", ptMessage);

        dwRet = ruleworkProc(ptMsg, ptMessage);
        if (RDP_SUCCESS != dwRet)
        {
            RdpRuleDbgPrint("(Rule) ruleworkProc Msg not continue dwRet=0x%x\r\n", dwRet);
            continue;
        }
    }

    return RDP_SUCCESS;
}



