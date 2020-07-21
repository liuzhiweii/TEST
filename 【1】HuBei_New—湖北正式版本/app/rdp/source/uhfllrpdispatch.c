/***************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
*
* 文件名称：ufhllrpdispatch.c
* 文件标识：
* 内容摘要：LLRP模块调度
* 其它说明：
* 当前版本：
* 作    者：程亮
* 完成日期：2012.05.17 
**********************************************************************/

/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include "rdppub.h"
#include <pthread.h>
#include <dlfcn.h>

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
/*接收最大消息*/
unsigned char g_aucRdpLlrpSndMsg[RDP_MAX_LEN_MSG];
unsigned char g_aucRdpLlrpRcvMsg[RDP_MAX_LEN_MSG];
/*Llrp模块的消息ID*/
/*三个线程共享的全局变量*/
unsigned int g_bRdpPowerOnCfgFinish = FALSE;
T_RdpLlrpCtrl g_tRdpLlrpCtrl;
T_RdpConfig g_tRdpConfig;
T_RdpLlrpReaderDispatch g_tRdpLlrpReaderDispatch;
unsigned short int g_wMsgSequence = 0;
unsigned short int g_wInnerMsgSequence = 0;
T_RdpLlrpPwdSys g_tRdpPwdSys;
int sock_timer;
void *req_socket_rcp=NULL;
void *pull_socket_comm=NULL;
void *push_socket_comm=NULL;
void *req_socket_cfg=NULL;
void *sub_socket_cfg=NULL;
void *pair_socket_rule=NULL;
void *pair_socket_report=NULL;
void *ctx;


extern unsigned int g_dwLlrpTagAccessErrTimes;
extern T_RdpLlrpDynamicRo g_tRdpLlrpDynamicRoLinkHead[MAX_LINK_NUM];
extern T_RdpLlrpDynamicAccess g_tRdpLlrpDynamicAccessLinkHead[MAX_LINK_NUM];
/***********************************************************
 *                     本地变量                            *
***********************************************************/
static unsigned int s_dwRdpLlrpStatus;
static unsigned int g_bLLrpCfgChangeFlag = 0;
static T_RdpLlrpReaderRoData g_tRdpLlrpReaderRoData;
static T_RdpLlrpReaderAccessData g_tRdpLlrpReaderAccessData;
static T_LlrpDispatchMsg g_tLlrpWorkDispatchMsg[] =
    {
        { EV_ADD_ROSPEC, EV_ADD_ROSPEC, llrp_addRo},
        { EV_ENABLE_ROSPEC, EV_ENABLE_ROSPEC, llrp_enableRo},
        { EV_DISABLE_ROSPEC, EV_DISABLE_ROSPEC, llrp_disableRo},
        { EV_DELETE_ROSEPC, EV_DELETE_ROSEPC, llrp_deleteRo},
        { EV_START_ROSPEC, EV_START_ROSPEC, llrp_startRo},
        { EV_STOP_ROSPEC, EV_STOP_ROSPEC, llrp_stopRo},
        { EV_ADD_ACCESSSPEC, EV_ADD_ACCESSSPEC, llrp_addAo},
        { EV_ENABLE_ACCESSSPEC, EV_ENABLE_ACCESSSPEC, llrp_enableAo},
        { EV_DISABLE_ACCESSSPEC, EV_DISABLE_ACCESSSPEC, llrp_disableAo},
        { EV_DELETE_ACCESSSPEC, EV_DELETE_ACCESSSPEC, llrp_deleteAo},
        { EV_GET_ACCESSSPECS, EV_GET_ACCESSSPECS, llrp_getAo},
        { EV_GET_ROSPEC, EV_GET_ROSPEC, llrp_getRo},
        { EV_GET_REPOERT, EV_GET_REPOERT, llrp_getReport},
        { EV_CLIENT_REQUEST_OP_RESPONSE, EV_CLIENT_REQUEST_OP_RESPONSE, llrp_clientRequestRsp},
        { EV_USP_UHF_EPC_INVENT_RES, EV_USP_UHF_EPC_INVENT_RES, llrp_tagEpcInvRsp},
        { EV_USP_UHF_EPC_READ_RES, EV_USP_UHF_EPC_READ_RES, llrp_tagEpcReadRsp},
        { EV_USP_UHF_EPC_WRITE_RES, EV_USP_UHF_EPC_WRITE_RES, llrp_tagEpcWriteRsp},
        { EV_USP_UHF_EPC_LOCK_RES, EV_USP_UHF_EPC_LOCK_RES, llrp_tagEpcLockRsp},
        { EV_USP_UHF_EPC_IPJQT_RES, EV_USP_UHF_EPC_IPJQT_RES, llrp_tagEpcIPJQTRsp},
        { EV_USP_UHF_EPC_KILL_RES, EV_USP_UHF_EPC_KILL_RES, llrp_tagEpcKillRsp},
        { EV_USP_UHF_EPC_VERIFY_READ_RES, EV_USP_UHF_EPC_VERIFY_READ_RES, llrp_tagEpcVeriyReadRsp},
        { EV_USP_UHF_EPC_BLOCKLOCK_RES, EV_USP_UHF_EPC_BLOCKLOCK_RES, llrp_tagEpcBlockLockRsp},
        { EV_USP_UHF_EPC_READLOCK_RES, EV_USP_UHF_EPC_READLOCK_RES, llrp_tagEpcReadLockRsp},
        { EV_USP_UHF_ISO6B_INVENT_RES, EV_USP_UHF_ISO6B_INVENT_RES, llrp_tagISO6BInvRsp},
        { EV_USP_UHF_ISO6B_READ_RES, EV_USP_UHF_ISO6B_READ_RES, llrp_tagISO6BReadRsp},
        { EV_USP_UHF_ISO6B_WRITE_RES, EV_USP_UHF_ISO6B_WRITE_RES, llrp_tagISO6BWriteRsp},
        { EV_USP_UHF_ISO6B_LOCK_RES, EV_USP_UHF_ISO6B_LOCK_RES, llrp_tagISO6BLockRsp},
        { EV_USP_UHF_ISO6B_LOCKQUERY_RES, EV_USP_UHF_ISO6B_LOCKQUERY_RES, llrp_tagISO6BLockQueryRsp},
        { EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN, EV_RDP_LLRP_PROTIMEOUT_TIMER_END, llrp_dealRcpRspTimeOut},
        { EV_RDP_LLRP_RULETIMER_BEGIN, EV_RDP_LLRP_RULETIMER_END, llrp_externPeriodtimerForRoStartTrigger},
        { EV_RDP_GPIO_InputEventReport, EV_RDP_GPIO_InputEventReport, llrp_dealExternGpiForReader},
        { TBootTimerPollingIntervalTimer, TBootTimerPollingIntervalTimer, llrp_dealBootTimerPollingTimer},
        { EV_UHF_PRIVATE_CMD, EV_UHF_PRIVATE_CMD, llrp_dealUhfPrivateCmd},
        { EV_UHF_PRIVATE_SETPASSWORD, EV_UHF_PRIVATE_SETPASSWORD, llrp_dealUhfPrivateSetPassword},
        { EV_USP_UHF_GB_INVENT_RES, EV_USP_UHF_GB_INVENT_RES, llrp_tagGBInvRsp},
        { EV_USP_UHF_GB_READ_RES, EV_USP_UHF_GB_READ_RES, llrp_tagGBReadRsp},
        { EV_USP_UHF_GB_WRITE_RES, EV_USP_UHF_GB_WRITE_RES, llrp_tagGBWriteRsp},
        { EV_USP_UHF_GB_LOCK_RES, EV_USP_UHF_GB_LOCK_RES, llrp_tagGBLockRsp},
        { EV_USP_UHF_GB_KILL_RES, EV_USP_UHF_GB_KILL_RES, llrp_tagGBKillRsp},
        { EV_USP_UHF_GB_ERASE_RES, EV_USP_UHF_GB_ERASE_RES, llrp_tagGBEraseRsp}
    };


/***********************************************************
 *                     全局函数                            *
***********************************************************/




/***********************************************************
 *                     局部函数                            *
***********************************************************/



/**************************************************************************
* 函数名称：llrp_debugRdpCfg
* 功能描述：打印Rdp接收到打印内容
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/
void llrp_debugRdpCfg()
{
    unsigned int dwIndex = 0;
    unsigned int dwSubIndex = 0;
    unsigned int dwSub1Index = 0;
    T_USPRdpLlrpC1G2Filter *ptUSPRdpLlrpC1G2Filter = NULL;
    T_USPRdpLlrpISO6BFilter *ptUSPRdpLlrpISO6BFilter = NULL;
    T_USPRdpLlrpGBFilter *ptUSPRdpLlrpGBFilter = NULL;
    RdpLlrpDbgPrint("(LLRP)Rdp config content \r\n");

    for (dwIndex = 0;dwIndex < MAX_NUM_ANT_SUPPORT;dwIndex++)
    {
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].ttUSPRdpLlrpRFTransmitterSettings.wChannelIndex =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpRFTransmitterSettings.wChannelIndex);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpRFTransmitterSettings.wHopTableID =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpRFTransmitterSettings.wHopTableID);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpRFTransmitterSettings.wTransmitPower =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpRFTransmitterSettings.wTransmitPower);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.wTagInventoryStateAware =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.wTagInventoryStateAware);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2RFControl.wModeIndex =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2RFControl.wModeIndex);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2RFControl.wTari =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2RFControl.wTari);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2SingulationControl.dwTagTransitTime=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2SingulationControl.dwTagTransitTime);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2SingulationControl.ucSession=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2SingulationControl.ucSession);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2SingulationControl.wTagPopulation=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2SingulationControl.wTagPopulation);

        for (dwSubIndex = 0;dwSubIndex < g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2Filter.wFilterNum;dwSubIndex++)
        {
            ptUSPRdpLlrpC1G2Filter = &g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand.tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[dwSubIndex];
            RdpLlrpDbgPrint("(LLRP)C1G2Filter dwSubIndex %d eC1G2TruncateAction =%d\r\n", dwSubIndex, ptUSPRdpLlrpC1G2Filter->eC1G2TruncateAction);
            RdpLlrpDbgPrint("(LLRP)C1G2Filter dwSubIndex %d eC1G2StateUnawareAction =%d\r\n", dwSubIndex, ptUSPRdpLlrpC1G2Filter->tUSPRdpLlrpC1G2TagInventoryStateUnawareFilterAction.eC1G2StateUnawareAction);
            RdpLlrpDbgPrint("(LLRP)C1G2Filter dwSubIndex %d wMaskBitPointer =%d\r\n", dwSubIndex, ptUSPRdpLlrpC1G2Filter->tUSPRdpLlrpEPCTargetTagMask.wMaskBitPointer);
            RdpLlrpDbgPrint("(LLRP)C1G2Filter dwSubIndex %d wMaskLength =%d\r\n", dwSubIndex, ptUSPRdpLlrpC1G2Filter->tUSPRdpLlrpEPCTargetTagMask.wMaskLength);
            RdpLlrpDbgPrint("(LLRP)C1G2Filter dwSubIndex %d wMemBank =%d\r\n", dwSubIndex, ptUSPRdpLlrpC1G2Filter->tUSPRdpLlrpEPCTargetTagMask.wMemBank);
            RdpLlrpDbgPrint("(LLRP)filter data:");
            for (dwSub1Index = 0 ;dwSub1Index < ptUSPRdpLlrpC1G2Filter->tUSPRdpLlrpEPCTargetTagMask.wMaskLength*sizeof(unsigned short int);dwSub1Index++)
            {
                RdpDbgPrintRaw("0x%02x ", ptUSPRdpLlrpC1G2Filter->tUSPRdpLlrpEPCTargetTagMask.ucMaskData[dwSub1Index]);
            }
            RdpLlrpDbgPrint("\r\n");
        }
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBRFControl.wModeIndex =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBRFControl.wModeIndex);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.wCCN=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.wCCN);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.wCIN=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.wCIN);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.ucSession=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.ucSession);
	 RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.ucGBQureyAction=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.ucGBQureyAction);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.ucGBQureySel=%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBSingulationControl.ucGBQureySel);

        for (dwSubIndex = 0;dwSubIndex < g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBFilter.wFilterNum;dwSubIndex++)
        {
            ptUSPRdpLlrpGBFilter = &g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand.tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[dwSubIndex];
            RdpLlrpDbgPrint("(LLRP)GBFilter dwSubIndex %d ucGBStateAwareTarget =%d\r\n", dwSubIndex, ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTagInventoryStateAwareFilterAction.ucGBStateAwareTarget);
	     RdpLlrpDbgPrint("(LLRP)GBFilter dwSubIndex %d ucGBStateAwareAction =%d\r\n", dwSubIndex, ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTagInventoryStateAwareFilterAction.ucGBStateAwareAction);
            RdpLlrpDbgPrint("(LLRP)GBFilter dwSubIndex %d wMaskBitPointer =%d\r\n", dwSubIndex, ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTargetTagMask.wMaskBitPointer);
            RdpLlrpDbgPrint("(LLRP)GBFilter dwSubIndex %d wMaskLength =%d\r\n", dwSubIndex, ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTargetTagMask.wMaskLength);
            RdpLlrpDbgPrint("(LLRP)GBFilter dwSubIndex %d wMemBank =%d\r\n", dwSubIndex, ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTargetTagMask.wMemBank);
            RdpLlrpDbgPrint("(LLRP)filter data:");
            for (dwSub1Index = 0 ;dwSub1Index < ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTargetTagMask.wMaskLength*sizeof(unsigned short int);dwSub1Index++)
            {
                RdpDbgPrintRaw("0x%02x ", ptUSPRdpLlrpGBFilter->tUSPRdpLlrpGBTargetTagMask.ucMaskData[dwSub1Index]);
            }
            RdpLlrpDbgPrint("\r\n");
        }
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BRFControl.wModeIndex =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BRFControl.wModeIndex);

        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BSingulationControl.dwTagTransitTime =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BSingulationControl.dwTagTransitTime);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[%d].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BSingulationControl.wTagPopulation =%d\r\n",
                        dwIndex, g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BSingulationControl.wTagPopulation);

        for (dwSubIndex = 0;dwSubIndex < g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.ucGroupSelectNum;dwSubIndex++)
        {
            ptUSPRdpLlrpISO6BFilter = &g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[dwIndex].tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[dwSubIndex];
            RdpLlrpDbgPrint("(LLRP)ISO6BFilter dwSubIndex %d ucAddress =%d\r\n", dwSubIndex, ptUSPRdpLlrpISO6BFilter->ucAddress);
            RdpLlrpDbgPrint("(LLRP)ISO6BFilter dwSubIndex %d ucCommandType =%d\r\n", dwSubIndex, ptUSPRdpLlrpISO6BFilter->ucCommandType);
            RdpLlrpDbgPrint("(LLRP)ISO6BFilter dwSubIndex %d ucMask =%d\r\n", dwSubIndex, ptUSPRdpLlrpISO6BFilter->ucMask);
            RdpLlrpDbgPrint("(LLRP)filter data:");
            for (dwSub1Index = 0 ;dwSub1Index < 8;dwSub1Index++)
            {
                RdpDbgPrintRaw("0x%02x ", ptUSPRdpLlrpISO6BFilter->ucWordData[dwSub1Index]);
            }
            RdpLlrpDbgPrint("(LLRP)\r\n");
        }
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].eForandRevConfigTypey =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].eForandRevConfigType);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].wAntennaID =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].wAntennaID);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFreqWorkType =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFreqWorkType);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFixFreqChannel =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFixFreqChannel);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFreqTableID =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFreqTableID);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.wHopTimer =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.wHopTimer);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.wFreqHopMode =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.wFreqHopMode);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannelNum =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannelNum);
        RdpLlrpDbgPrint("(LLRP)hop channel table data:");
        for (dwSub1Index = 0 ;dwSub1Index < g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannelNum;dwSub1Index++)
        {
            RdpDbgPrintRaw("0x%02x ", g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannel[dwSub1Index]);
        }
        RdpLlrpDbgPrint("\r\n");

        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFreqWorkType =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFreqWorkType);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFixFreqChannel =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFixFreqChannel);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFreqTableID =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFreqTableID);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.wHopTimer =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.wHopTimer);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.wFreqHopMode =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.wFreqHopMode);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannelNum =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannelNum);
        RdpLlrpDbgPrint("(LLRP)hop channel table data:");
        for (dwSub1Index = 0 ;dwSub1Index < g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannelNum;dwSub1Index++)
        {
            RdpDbgPrintRaw("0x%02x ", g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannel[dwSub1Index]);
        }
        RdpLlrpDbgPrint("\r\n");
	RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFreqWorkType =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFreqWorkType);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFixFreqChannel =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFixFreqChannel);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFreqTableID =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFreqTableID);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.wHopTimer =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.wHopTimer);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.wFreqHopMode =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.wFreqHopMode);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannelNum =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannelNum);
        RdpLlrpDbgPrint("(LLRP)hop channel table data:");
        for (dwSub1Index = 0 ;dwSub1Index < g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannelNum;dwSub1Index++)
        {
            RdpDbgPrintRaw("0x%02x ", g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannel[dwSub1Index]);
        }
        RdpLlrpDbgPrint("\r\n");
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tTransmitPower.wTransmitPower6B =%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tTransmitPower.wTransmitPower6B);
        RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tTransmitPower.wTransmitPower6C=%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tTransmitPower.wTransmitPower6C);
	 RdpLlrpDbgPrint("(LLRP)g_tRdpConfig.trAntennaExtConfiguration[%d].tTransmitPower.wTransmitPowerGB=%d\r\n",
                        dwIndex, g_tRdpConfig.trAntennaExtConfiguration[dwIndex].tTransmitPower.wTransmitPowerGB);
    }

    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tAccessReportSpec.eAccessReportTriggerType = %d\r\n", g_tRdpConfig.tAccessReportSpec.eAccessReportTriggerType);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.eROReportTrigger = %d\r\n", g_tRdpConfig.tROReportSpec.eROReportTrigger);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.wThresholdOfReportNum = %d\r\n", g_tRdpConfig.tROReportSpec.wThresholdOfReportNum);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableAccessSpecID = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableAccessSpecID);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableAntennaID = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableAntennaID);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableChannelIndex = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableChannelIndex);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableCRC = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableCRC);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableFirstSeenTimestamp = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableFirstSeenTimestamp);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableInventoryParameterSpecID = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableInventoryParameterSpecID);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableLastSeenTimestamp = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableLastSeenTimestamp);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnablePC = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnablePC);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnablePeakRSSI = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnablePeakRSSI);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableROSpecID = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableROSpecID);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableSpecIndex = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableSpecIndex);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableTagSeenCount = %d\r\n", g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector.bEnableTagSeenCount);
    for ( dwIndex = 0 ;dwIndex < READER_MAX_EVENT_NUM;dwIndex++)
    {
        RdpDbgPrintRaw("(LLRP) g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[%d].tNotificationEventType= %d\r\n", dwIndex, g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[dwIndex].tNotificationEventType);
        RdpDbgPrintRaw("(LLRP) g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[%d].bNotificationState= %d\r\n", dwIndex, g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[dwIndex].bNotificationState);
    }

    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucTurnOnOPFilter= %d\r\n", g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucTurnOnOPFilter);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucOPKeepaliveTime= %d\r\n", g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucOPKeepaliveTime);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucOPPollTime= %d\r\n", g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucOPPollTime);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucTurnOnRFFilter= %d\r\n", g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucTurnOnRFFilter);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucRFKeepaliveTime= %d\r\n", g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucRFKeepaliveTime);
    RdpLlrpDbgPrint("(LLRP) g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucRFPollTime= %d\r\n", g_tRdpConfig.tUSPRdpAdvancedConfig.tTagFilterCfg.ucRFPollTime);
}

/**************************************************************************
* 函数名称：llrp_cfgChangeRefresh
* 功能描述：工作状态下检测配置是否发生改变
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned int * pdwCfgChangeFlag
* 输出参数：
* 返 回 值： 无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
unsigned int llrp_cfgChangeRefresh()
{
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    if (g_bLLrpCfgChangeFlag == TRUE )
    {
        /*请求配置*/
        send_cfg_msg("rdp","request",NULL);
        RdpLlrpDbgPrint("(LLRP)send_cfg_msg\r\n");
        return LLRP_CFG_CHANGE;
    }
    else
    {
        /*继续工作*/
        return LLRP_CFG_NOTCHANGE;
    }
}
/**************************************************************************
* 函数名称：rdp_llrp_scanReadytoRun
* 功能描述：llrp扫描运行Ro
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/
void rdp_llrp_scanReadytoRun(T_RdpLlrpReaderRoData* ptRdpLlrpReaderRoData)
{
    /*消息太多使用表驱动方法*/
    unsigned int dwRet = 0;
    T_RdpLlrpROEntry *ptRunROEntry = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpAI *ptRunLlrpAI = NULL;
    ptRunROEntry = ptRdpLlrpReaderRoData->tReadyRoQueuehead.ptNext;
    if (ptRunROEntry == NULL)
    {
        RdpLlrpDbgPrint("(LLRP)there is not ready Ro to run\r\n ");
        return ;
    }
    else
    {
        /*摘除头节点到active状态*/
        ptRdpLlrpReaderRoData->tReadyRoQueuehead.ptNext = ptRunROEntry->ptNext;
        ptRunROEntry->ptNext = NULL;
        ptRdpLlrpReaderRoData->tActiveRO.ptNext = ptRunROEntry;

        /*获取activeRo的参数 并初始化 相关参数*/
        ptRunRoCtrlAndPara = llrp_getRunRO();
        ptRunRoCtrlAndPara->tRdpLlrpRODispatchCtrl.dwDispatchStatus = LLRP_RODISPATCH_STATE_ACTIVE;
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.eCurrentState = LLRP_ROSpecState_Active;
        /*初始化trigger的参数*/
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.pfusp_rdp_llrp_InitStartTrigger(ptRunROEntry);
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStopTrigger.pfusp_rdp_llrp_initStopTrigger(ptRunRoCtrlAndPara);
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.pfusp_rdp_llrp_InitROForReportTrigger(ptRunRoCtrlAndPara);
        ptRunLlrpAI = llrp_getRunAI();
        ptRunLlrpAI->tRdpLlrpAIStopTrigger.pfusp_rdp_llrp_initAIForAIStopTrigger(&ptRunLlrpAI->tRdpLlrpAIStopTrigger);
        llrp_reportReaderEventNotification(LLRP_NotificationEventType_ROSpec_Event , LLRP_ROSpecEventType_Start_Of_ROSpec);
    }
    dwRet = llrp_tagInventory(&ptRdpLlrpReaderRoData->tRdpLlrpROCtrlAndParam[ptRdpLlrpReaderRoData->tActiveRO.ptNext->dwROIndex]);
    if (dwRet != 0)
    {
        /*写入调用RO异常*/
        RDP_EXCEPT(RDP_INVALID_STATE, dwRet, 0, 0, RDP_LLRP_DISPATCH_ID);
    }
}
/**************************************************************************
* 函数名称：llrp_dealCommNoticeMsg
* 功能描述：处理通信的建链消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/
void llrp_dealCommNoticeMsg(T_Msg *ptRcvMsg)
{
    RdpLlrpDbgPrint("(LLRP)Receive CommNoticeMsg ptRcvMsg->wMsgID: %d,ptRcvMsg->wMsgLen: %d,ptRcvMsg->ucLinkIndex: %d,ptRcvMsg->ucLinkType: %d\r\n",
                    ptRcvMsg->wMsgID, ptRcvMsg->wMsgLen, ptRcvMsg->ucLinkIndex, ptRcvMsg->ucLinkType);
}
/**************************************************************************
* 函数名称：llrp_init
* 功能描述：Rdp中的llrp中init
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/
void llrp_init()
{
    g_bRdpPowerOnCfgFinish = FALSE;
    s_dwRdpLlrpStatus = RDP_LLRP_INIT_STATUS;
    memset(&g_tRdpLlrpCtrl, 0, sizeof(T_RdpLlrpCtrl));
    memset(&g_tRdpConfig, 0, sizeof(T_RdpConfig));
    memset(&g_tRdpLlrpReaderDispatch, 0, sizeof(T_RdpLlrpReaderDispatch));
    memset(&g_tRdpLlrpReaderRoData, 0, sizeof(T_RdpLlrpReaderRoData));
    memset(&g_tRdpLlrpReaderAccessData, 0, sizeof(T_RdpLlrpReaderAccessData));
    memset(g_tRdpLlrpDynamicRoLinkHead, 0, sizeof(g_tRdpLlrpDynamicRoLinkHead));
    memset(g_tRdpLlrpDynamicAccessLinkHead, 0, sizeof(g_tRdpLlrpDynamicAccessLinkHead));
    memset(&g_tRdpPwdSys, 0, sizeof(g_tRdpPwdSys));
    g_tRdpLlrpReaderDispatch.pfScanROToRun = rdp_llrp_scanReadytoRun;
    g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData = &g_tRdpLlrpReaderAccessData;
    g_tRdpLlrpReaderDispatch.ptReaderRoSpecData = &g_tRdpLlrpReaderRoData;
    g_wMsgSequence = 0;
    g_wInnerMsgSequence = 0;
    INIT_READER_BOOT_TIME_MS();
	LLRP_START_TIMER(TBootTimerPollingIntervalTimer, LLRP_PollingInterval);

	
}

/**************************************************************************
* 函数名称：rdp_llrp_rcvmsgForWorkStatus
* 功能描述：llrp的work状态下收到的消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/
static void deal_business_msg(T_Msg *ptRcvMsg)
{
    /*消息太多使用表驱动方法*/
    unsigned int dwIndex = 0;
    for (dwIndex = 0; dwIndex < sizeof(g_tLlrpWorkDispatchMsg) / sizeof(T_LlrpDispatchMsg);dwIndex++)
    {
        if ( ptRcvMsg->wMsgID >= g_tLlrpWorkDispatchMsg[dwIndex].dwBeginMsgID
                && ptRcvMsg->wMsgID <= g_tLlrpWorkDispatchMsg[dwIndex].dwEndMsgID)
        {
            g_tLlrpWorkDispatchMsg[dwIndex].pfllrp_dealmsg(ptRcvMsg);
            break;
        }
    }
    
    if (dwIndex == (sizeof(g_tLlrpWorkDispatchMsg) / sizeof(T_LlrpDispatchMsg)) )
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_MSG_PROC_ERROR, ptRcvMsg->wMsgID, ptRcvMsg->wMsgLen, 0, RDP_LLRP_DISPATCH_ID);
        RdpLlrpDbgPrint("(LLRP)LLrp workstate receive unsupport msg\r\n");
    }
}

void set_zmq_socket_option(void *socket, int type, int value)
{
    int rc = 0;
    rc = zmq_setsockopt(socket, type, &value, sizeof(int));
    CHECK_FAIL_NUMBER(rc, "set_zmq_socket_option zmq_setsockopt fail");
}


void create_zmq_sockets_rdp(void)
{
    int value;
    int ret;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
        exit(-1);
    }

    /*和rcp模块接口*/
    req_socket_rcp = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == req_socket_rcp)
    {
        printf("create req_socket_rcp fail!\n");
        exit(-1);
    }
    ret = zmq_connect(req_socket_rcp, "ipc://rdp_rcp.ipc");
    if(ret < 0)
    {
        printf("connect req_socket_rcp socket fail\n");
        exit(-1);
    }
    set_zmq_socket_option(req_socket_rcp, ZMQ_SNDHWM, 10);
	
    /*comm pull*/
    pull_socket_comm = zmq_socket(ctx, ZMQ_PULL);
    if(NULL == pull_socket_comm)
    {
        printf("create pull_socket_comm fail!\n");
        exit(-1);
    }

    ret = zmq_connect(pull_socket_comm, "tcp://127.0.0.1:5010");
    if(ret < 0)
    {
        printf("zmq_connect pull_socket_comm socket fail\n");
        exit(-1);
    }

    /*创建comm push 接口*/
    push_socket_comm = zmq_socket(ctx, ZMQ_PUSH);
    if(NULL == push_socket_comm)
    {
        printf("create push_socket_comm fail!\n");
        exit(-1);
    }
    ret = zmq_connect(push_socket_comm, "tcp://127.0.0.1:5011");
    if(ret < 0)
    {
        printf("zmq_connect push_socket_comm socket fail\n");
        exit(-1);
    }

    value = 10;
    zmq_setsockopt(push_socket_comm, ZMQ_SNDHWM, &value, sizeof(int));

    /*cfg zmq*/
    req_socket_cfg = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == req_socket_cfg)
    {
        printf("create tcp req_socket_cfg fail!\n");
        exit(-1);
    }

    set_zmq_socket_option(req_socket_cfg, ZMQ_RCVTIMEO, 2000);
    set_zmq_socket_option(req_socket_cfg, ZMQ_LINGER, 0);
    //set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE, 1);
    //set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_CNT, 2);
    //set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_IDLE, 1);
    //set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_INTVL, 1);

    //ret= zmq_setsockopt (req_socket, ZMQ_SNDTIMEO, 2000, 4);
    ret = zmq_connect(req_socket_cfg, "tcp://127.0.0.1:5504");
    if(ret < 0)
    {
        printf("connect req_socket_cfg fail\n");
        exit(-1);
    }

	/*cfg pub*/
	sub_socket_cfg = zmq_socket(ctx, ZMQ_SUB);
    if(NULL == sub_socket_cfg)
    {
        printf("create sub_socket_cfg fail!\n");
        exit(-1);
    }
    
    ret = zmq_connect(sub_socket_cfg, "tcp://127.0.0.1:5505");
	
    /*inproc */
	pair_socket_rule = zmq_socket(ctx, ZMQ_PAIR);
    if(NULL == pair_socket_rule)
    {
        printf("create pair_socket_rule fail!\n");
        exit(-1);
    }
    ret = zmq_bind(pair_socket_rule, "inproc://rule.inproc");

	pair_socket_report = zmq_socket(ctx, ZMQ_PAIR);
    if(NULL == pair_socket_report)
    {
        printf("create pair_socket_report fail!\n");
        exit(-1);
    }
    ret = zmq_bind(pair_socket_report, "inproc://report.inproc");
    return;
}

void send_cfg_msg(const char *type,const char *action,const char *content)
{
    int rc=0;     
	char send_buf[1024]={0};
    JSON_Value *tmp_value=NULL;
    JSON_Object *tmp_object=NULL;
 
    RdpLlrpDbgPrint("send_msg type=%s,action=%s,content=%s\r\n",type,action,content);
    
    tmp_value=json_value_init_object();
    tmp_object=tmp_value->value.object;
    json_object_set_string(tmp_object,"type",type);
    json_object_set_string(tmp_object,"action",action);
    if(NULL!=content)
    {
       json_object_set_string(tmp_object,"content",content);
    }
    memset(send_buf,0,sizeof(send_buf));
    rc=json_serialize_to_buffer(tmp_value,send_buf,sizeof(send_buf));
    /*释放*/
    json_value_free(tmp_value);
    RdpLlrpDbgPrint("json_serialize_to_buffer send_buf = %s \r\n", send_buf);
    zmq_send(req_socket_cfg,send_buf,(strlen(send_buf)+1),0);
}
JSON_Object *parse_string_to_object(const char *strings,JSON_Value **string_value)
{
    JSON_Object *tmp_object=NULL;
    JSON_Value *tmp_value=NULL;
 
    /* 解析默认配置 */
    tmp_value= json_parse_string(strings);
    *string_value = NULL;
	if(NULL==tmp_value)
	{
		printf("json_parse_string null pointer error \r\n");
		return NULL;
	}
   if(json_value_get_type(tmp_value) == JSONObject)
   {
      tmp_object = json_value_get_object(tmp_value);
      *string_value = tmp_value;
   }
   else
   {
       json_value_free(tmp_value);
       *string_value=NULL;
       return NULL;
   }
    return tmp_object;
}
void tranfer_antenna_cfg_to_inner(JSON_Object *antenna_obj,T_USPRdpLlrpAntennaConfiguration *ptRdpLlrpAntennaConfiguration)
{
   int loop=0;
   int maskbytelen,maskbitlen;
   JSON_Array * array;
   T_USPRdpLlrpC1G2InventoryCommand  *ptC1G2InventoryCommand;
   T_USPRdpLlrpISO6BInventoryCommand *pt6BInventoryCommand;
   T_USPRdpLlrpGBInventoryCommand *ptGBInventoryCommand;
   JSON_Object *C1G2InvCmd_obj;
   JSON_Object *ISO6BInvCmd_obj;
   JSON_Object *GBInvCmd_obj;
   RdpDbgPrint("come into tranfer_antenna_cfg_to_inner\r\n");
   CHECK_NULL_POINTER_RETURN_VOID(antenna_obj&&ptRdpLlrpAntennaConfiguration);
   ptRdpLlrpAntennaConfiguration->ucAntID=(unsigned char)json_object_get_number(antenna_obj,"AntennaID");
   ptRdpLlrpAntennaConfiguration->tUSPRdpLlrpRFTransmitterSettings.wChannelIndex=(unsigned short int)json_object_dotget_number(antenna_obj,"RFTransmitter.ChannelIndex");
   ptRdpLlrpAntennaConfiguration->tUSPRdpLlrpRFTransmitterSettings.wHopTableID=(unsigned short int)json_object_dotget_number(antenna_obj,"RFTransmitter.HopTableID");
   ptRdpLlrpAntennaConfiguration->tUSPRdpLlrpRFTransmitterSettings.wTransmitPower=(unsigned short int)json_object_dotget_number(antenna_obj,"RFTransmitter.TransmitPower");

   //C1G2InventoryCommand
   C1G2InvCmd_obj=json_object_dotget_object(antenna_obj,"AirProtocolInventoryCommandSettings.C1G2InventoryCommand");
   ptC1G2InventoryCommand=&ptRdpLlrpAntennaConfiguration->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpC1G2InventoryCommand;
   ptC1G2InventoryCommand->wTagInventoryStateAware =(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"TagInventoryStateAware");
   ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.wFilterNum=(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.FilterNum");
   ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].eC1G2TruncateAction=(unsigned int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TruncateAction");
   ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].tUSPRdpLlrpC1G2TagInventoryStateUnawareFilterAction.eC1G2StateUnawareAction=(unsigned int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryStateUnawareFilterAction");
   ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].tUSPRdpLlrpEPCTargetTagMask.wMaskBitPointer=(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.Pointer");
   ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].tUSPRdpLlrpEPCTargetTagMask.wMaskLength=(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.MaskBitLen");
   ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].tUSPRdpLlrpEPCTargetTagMask.wMemBank=(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.MB");

   	maskbitlen=ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].tUSPRdpLlrpEPCTargetTagMask.wMaskLength;
	maskbytelen= ((maskbitlen/8==0)?maskbitlen/8:maskbitlen/8+1);
	array=json_object_dotget_array(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.MaskData");
	for(loop=0;loop<maskbytelen;loop++)
    {
       ptC1G2InventoryCommand->tUSPRdpLlrpC1G2Filter.atUSPRdpLlrpC1G2Filter[0].tUSPRdpLlrpEPCTargetTagMask.ucMaskData[loop]= (unsigned char)json_array_get_number(array,loop);
    }

	ptC1G2InventoryCommand->tUSPRdpLlrpC1G2RFControl.wModeIndex=(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2RFControl.ModeIndex");
	ptC1G2InventoryCommand->tUSPRdpLlrpC1G2RFControl.wTari=(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2RFControl.Tari");

	ptC1G2InventoryCommand->tUSPRdpLlrpC1G2SingulationControl.wTagPopulation =(unsigned short int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2SingulationControl.TagPopulation");
	ptC1G2InventoryCommand->tUSPRdpLlrpC1G2SingulationControl.dwTagTransitTime=(unsigned int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2SingulationControl.TagTransitTime");
	ptC1G2InventoryCommand->tUSPRdpLlrpC1G2SingulationControl.ucSession=(unsigned char)json_object_dotget_number(C1G2InvCmd_obj,"C1G2SingulationControl.Session");

	//6BInventoryCommand
   ISO6BInvCmd_obj =json_object_dotget_object(antenna_obj,"AirProtocolInventoryCommandSettings.6BInventoryCommand");
   pt6BInventoryCommand=&ptRdpLlrpAntennaConfiguration->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
   pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.ucGroupSelectNum =(unsigned char)json_object_dotget_number(ISO6BInvCmd_obj,"6BFilter.GroupSelectNum");
   pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucAddress=(unsigned char)json_object_dotget_number(ISO6BInvCmd_obj,"6BFilter.6BFilter1.Address");
   pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucCommandType=(unsigned char)json_object_dotget_number(ISO6BInvCmd_obj,"6BFilter.6BFilter1.CommandType");
   pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].wWordDataLen=(unsigned short int)json_object_dotget_number(ISO6BInvCmd_obj,"6BFilter.6BFilter1.WordDataLen");
   pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucMask=(unsigned char)json_object_dotget_number(ISO6BInvCmd_obj,"6BFilter.6BFilter1.Mask");

	maskbytelen= pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].wWordDataLen;
	array=json_object_dotget_array(ISO6BInvCmd_obj,"6BFilter.6BFilter1.WordData");
	for(loop=0;loop<maskbytelen;loop++)
    {
       pt6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucWordData[loop]= (unsigned char)json_array_get_number(array,loop);
    }

	pt6BInventoryCommand->tUSPRdpLlrpISO6BRFControl.wModeIndex=(unsigned short int)json_object_dotget_number(ISO6BInvCmd_obj,"6BRFControl.ModeIndex");
	pt6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.wTagPopulation =(unsigned short int)json_object_dotget_number(ISO6BInvCmd_obj,"6BSingulationControl.TagPopulation");
	pt6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.dwTagTransitTime=(unsigned int)json_object_dotget_number(ISO6BInvCmd_obj,"6BSingulationControl.TagTransitTime");
   RdpDbgPrint("4444\r\n");
	
	//GBInventoryCommand
	   GBInvCmd_obj=json_object_dotget_object(antenna_obj,"AirProtocolInventoryCommandSettings.GBInventoryCommand");
	   RdpDbgPrint("GBInvCmd_obj=0x%x\r\n",GBInvCmd_obj);
	   ptGBInventoryCommand=&ptRdpLlrpAntennaConfiguration->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpGBInventoryCommand;
	   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.wFilterNum=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.FilterNum");
	   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTagInventoryStateAwareFilterAction.ucGBStateAwareAction=(unsigned char)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTagInventoryStateAwareFilterAction.Action");
	   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTagInventoryStateAwareFilterAction.ucGBStateAwareTarget=(unsigned char)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTagInventoryStateAwareFilterAction.Target");
	   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTargetTagMask.wMaskBitPointer=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.Pointer");
	   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTargetTagMask.wMaskLength=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.MaskBitLen");
	   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTargetTagMask.wMemBank=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.MB");
	   RdpDbgPrint("5555\r\n");
		maskbitlen=ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTargetTagMask.wMaskLength;
		maskbytelen= ((maskbitlen/8==0)?maskbitlen/8:maskbitlen/8+1);
		array=json_object_dotget_array(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.MaskData");
		for(loop=0;loop<maskbytelen;loop++)
		{
		   ptGBInventoryCommand->tUSPRdpLlrpGBFilter.atUSPRdpLlrpGBFilter[0].tUSPRdpLlrpGBTargetTagMask.ucMaskData[loop]= (unsigned char)json_array_get_number(array,loop);
		}
	RdpDbgPrint("6666\r\n");
		ptGBInventoryCommand->tUSPRdpLlrpGBRFControl.wModeIndex=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBRFControl.ModeIndex");
		
		ptGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.wCCN=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBSingulationControl.CCN");
		ptGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.wCIN=(unsigned int)json_object_dotget_number(GBInvCmd_obj,"GBSingulationControl.CIN");
		ptGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.ucSession=(unsigned char)json_object_dotget_number(GBInvCmd_obj,"GBSingulationControl.Session");
		ptGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.ucGBQureyAction=(unsigned char)json_object_dotget_number(GBInvCmd_obj,"GBSingulationControl.GBQureyAction");
		ptGBInventoryCommand->tUSPRdpLlrpGBSingulationControl.ucGBQureySel=(unsigned char)json_object_dotget_number(GBInvCmd_obj,"GBSingulationControl.GBQureySel");
		RdpDbgPrint("6666\r\n");
}

void tranfer_antenna_extcfg_to_inner(JSON_Object *antenna_obj,T_USPRdpLlrpAntennaExtConfiguration *ptAntennaExtConfiguration)
{
   int loop=0;
   int maskbytelen,maskbitlen;
   JSON_Array * array;
   T_USPRdpLlrpC1G2InventoryCommand  *ptC1G2InventoryCommand;
   T_USPRdpLlrpISO6BInventoryCommand *pt6BInventoryCommand;
   T_USPRdpLlrpGBInventoryCommand *ptGBInventoryCommand;

   CHECK_NULL_POINTER_RETURN_VOID(antenna_obj&&ptAntennaExtConfiguration);
   ptAntennaExtConfiguration->wAntennaID=(unsigned short int)json_object_get_number(antenna_obj,"AntennaID");
   ptAntennaExtConfiguration->eForandRevConfigType =(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.ForandRevConfig");
   ptAntennaExtConfiguration->tTransmitPower.wTransmitPower6C=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.TransmitPower6C");
   ptAntennaExtConfiguration->tTransmitPower.wTransmitPower6B=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.TransmitPower6B");
   ptAntennaExtConfiguration->tTransmitPower.wTransmitPowerGB=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.TransmitPowerGB");

   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFreqWorkType=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.IsHopFreq");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFixFreqChannel=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.ChannelIndex");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.wFreqTableID=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.HopTableID");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.wFreqHopMode =(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.HopType");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.wHopTimer=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.HopInterval");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannelNum=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.FreqChannelNum");
   
   array=json_object_dotget_array(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.FreqChannel");
	   for(loop=0;loop<ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannelNum && loop<MAX_FREQ_HOP_NUM;loop++)
	   {
		  ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6C.tFreqHopConfig.tfreqChannel.wFreqChannel[loop]= (unsigned short int)json_array_get_number(array,loop);
	   }
   
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFreqWorkType=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.IsHopFreq");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFixFreqChannel=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.ChannelIndex");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.wFreqTableID=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.HopTableID");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.wFreqHopMode =(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.HopType");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.wHopTimer=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.HopInterval");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannelNum=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.FreqChannelNum");
   
   array=json_object_dotget_array(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.FreqChannel");
	   for(loop=0;loop<ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannelNum && loop<MAX_FREQ_HOP_NUM;loop++)
	   {
		  ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B.tFreqHopConfig.tfreqChannel.wFreqChannel[loop]= (unsigned short int)json_array_get_number(array,loop);
	   }

   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFreqWorkType=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.IsHopFreq");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFixFreqChannel=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.ChannelIndex");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.wFreqTableID=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.HopTableID");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.wFreqHopMode =(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.HopType");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.wHopTimer=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.HopInterval");
   ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannelNum=(unsigned short int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.FreqChannelNum");
   
   array=json_object_dotget_array(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.FreqChannel");
	   for(loop=0;loop<ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannelNum && loop<MAX_FREQ_HOP_NUM;loop++)
	   {
		  ptAntennaExtConfiguration->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfgGB.tFreqHopConfig.tfreqChannel.wFreqChannel[loop]= (unsigned short int)json_array_get_number(array,loop);
	   }
}

void tranfer_event_report_to_inner(JSON_Object *uhf_object)
{
   int loop=0;
   CHECK_NULL_POINTER_RETURN_VOID(uhf_object);
   for(loop=0;loop<READER_MAX_EVENT_NUM;loop++)
   {
   		g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[loop].tNotificationEventType = loop;
   }
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[0].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.Upon_Hopping_To_Next_Channel");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[1].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.GPI_Event");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[2].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.ROSpec_Event");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[3].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.Report_Buffer_Fill_Warning");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[4].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.Reader_Exception_Event");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[5].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.RFSurvey_Event");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[6].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.AISpec_Event");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[7].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.AISpec_Event_With_Details");
   g_tRdpConfig.tUSPRdpLlrpReaderEventNotificationSpec[8].bNotificationState= json_object_dotget_boolean(uhf_object,"ReaderEventNotificationSpec.Antenna_Event");
}
void tranfer_ro_report_to_inner(JSON_Object *uhf_object,T_USPRdpLlrpROReportConfig *ptROReportConfig)
{
   CHECK_NULL_POINTER_RETURN_VOID(uhf_object&&ptROReportConfig);
   ptROReportConfig->eROReportTrigger = json_object_dotget_number(uhf_object,"ROReportSpec.ROReportTrigger");
   ptROReportConfig->wThresholdOfReportNum= json_object_dotget_number(uhf_object,"ROReportSpec.N");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableROSpecID= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableROSpecID");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableSpecIndex= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableSpecIndex");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableInventoryParameterSpecID= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableInventoryParameterSpecID");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableAntennaID= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableAntennaID");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableChannelIndex= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableChannelIndex");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnablePeakRSSI= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnablePeakRSSI");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableFirstSeenTimestamp= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableFirstSeenTimestamp");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableLastSeenTimestamp= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableLastSeenTimestamp");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableTagSeenCount= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableTagSeenCount");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableAccessSpecID= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.EnableAccessSpecID");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnableCRC= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.AirProtocolEPCMemorySelector.C1G2EPCMemorySelector.EnableCRC");
   ptROReportConfig->tRdpLlrpTagReportContentSelector.bEnablePC= json_object_dotget_boolean(uhf_object,"ROReportSpec.reportContents.AirProtocolEPCMemorySelector.C1G2EPCMemorySelector.EnablePCBits");
}

void tranfer_advance_cfg_to_inner(JSON_Object *uhf_object,T_USPRdpAdvancedConfig *ptAdvancedConfig)
{
   CHECK_NULL_POINTER_RETURN_VOID(uhf_object&&ptAdvancedConfig);
   ptAdvancedConfig->tTagFilterCfg.ucTurnOnOPFilter= (unsigned char)json_object_dotget_number(uhf_object,"TagReportFilter.IsOpenOPFilter");
   ptAdvancedConfig->tTagFilterCfg.ucTurnOnRFFilter= (unsigned char)json_object_dotget_number(uhf_object,"TagReportFilter.IsOpenRFFilter");
   ptAdvancedConfig->tTagFilterCfg.ucOPKeepaliveTime= (unsigned char)json_object_dotget_number(uhf_object,"TagReportFilter.OPKeepaliveTime");
   ptAdvancedConfig->tTagFilterCfg.ucRFKeepaliveTime= (unsigned char)json_object_dotget_number(uhf_object,"TagReportFilter.RFKeepaliveTime");
   ptAdvancedConfig->tTagFilterCfg.ucOPPollTime= (unsigned char)json_object_dotget_number(uhf_object,"TagReportFilter.OPPollTime");
   ptAdvancedConfig->tTagFilterCfg.ucRFPollTime= (unsigned char)json_object_dotget_number(uhf_object,"TagReportFilter.RFPollTime");

}

void tranfer_llrp_cfg_to_inner(JSON_Object *cfg_object)
{
    int loop=0;
	unsigned char tmpBuf[256]={0};
	JSON_Object *antenna_obj=NULL;
	RdpLlrpDbgPrint("come into tranfer_llrp_cfg_to_inner \r\n");
    /*天线配置*/
	CHECK_NULL_POINTER_RETURN_VOID(cfg_object);
	for(loop=0;loop<READER_ANTENNA_COUNT;loop++)
	{
	    sprintf(tmpBuf,"Antenna%d",loop+1);
	    antenna_obj=json_object_dotget_object(cfg_object,tmpBuf);
		CHECK_NULL_POINTER_RETURN_VOID(antenna_obj);
		tranfer_antenna_cfg_to_inner(antenna_obj,&g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[loop]);
		tranfer_antenna_extcfg_to_inner(antenna_obj,&g_tRdpConfig.trAntennaExtConfiguration[loop]);
	}
	
	tranfer_event_report_to_inner(cfg_object);
	tranfer_ro_report_to_inner(cfg_object,&g_tRdpConfig.tROReportSpec);
	tranfer_advance_cfg_to_inner(cfg_object,&g_tRdpConfig.tUSPRdpAdvancedConfig);
	g_tRdpConfig.tAccessReportSpec.eAccessReportTriggerType=(unsigned int)json_object_get_number(cfg_object,"TAccessReportTrigger");
	g_tRdpConfig.tEventsAndReports.bHoldEventsAndReportsUponReconnect=(unsigned int)json_object_get_boolean(cfg_object,"HoldEventsAndReportsUponReconnect");
}
void deal_llrp_cfg_msg(int loop,unsigned char *recv_msg)
{
	int rc=0;
    const char *type=NULL;
	const char *content=NULL;
    int result=0;
	JSON_Object *cur_object=NULL;
    JSON_Value *cur_value=NULL;
	JSON_Object *cfg_object=NULL;
    JSON_Value *cfg_value=NULL;
	RdpLlrpDbgPrint("come into deal_llrp_cfg_msg \r\n");
	cur_object=parse_string_to_object(recv_msg,&cur_value);
	CHECK_NULL_POINTER_RETURN_VOID(cur_object);
	   type=json_object_get_string(cur_object,"type");
    if(1==loop)
    {   //request cfg ack
       result=(int)json_object_get_number(cur_object,"result");
	   content=json_object_get_string(cur_object,"content");
	   RdpLlrpDbgPrint("cfg request ack result=%d,content=%s\r\n",result,content);
	   cfg_object=parse_string_to_object(content,&cfg_value);
       if(NULL==cur_object) 
	   	{
	   	   RdpLlrpDbgPrint("deal_llrp_cfg_msg null pointer error 11\r\n");
		   json_value_free(cur_value);
	   	   return;
	   	}
	   tranfer_llrp_cfg_to_inner(cfg_object);
	   llrp_debugRdpCfg();
	   json_value_free(cfg_value);
	   if (s_dwRdpLlrpStatus == RDP_LLRP_INIT_STATUS )
		   {
			   RdpLlrpDbgPrint("(LLRP)Rdp Poweron Success begin to work\r\n");
			   g_bRdpPowerOnCfgFinish = TRUE;
			   s_dwRdpLlrpStatus = RDP_LLRP_WORK_STATUS;
		   }
		   else
		   {
			   RdpLlrpDbgPrint("(LLRP)Rdp config refresh complete\r\n");
			   g_bLLrpCfgChangeFlag = FALSE;
			   RdpLlrpDbgPrint("(LLRP)Rdp is idle need scan Ro node to work\r\n");
			   g_tRdpLlrpReaderDispatch.pfScanROToRun(g_tRdpLlrpReaderDispatch.ptReaderRoSpecData);
	   
		   }
    }
	else
	{  
	   //pub cfg change
	   if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext != NULL)
       {
           RdpLlrpDbgPrint("(LLRP)Rdp work and wait Rdp ilde request cfg\r\n");
           g_bLLrpCfgChangeFlag = TRUE;
       }
       else
       {
           send_cfg_msg("rdp","request",NULL);
           RdpLlrpDbgPrint("(LLRP)send_cfg_msg\r\n");
       }
	   
	}
	json_value_free(cur_value);
	return;
}
void deal_llrp_timer_msg(unsigned char *recv_msg)
{
    unsigned int timer_id;
	T_Msg *ptRcvMsg=NULL;
	timer_id=*(unsigned int *)recv_msg;
	ptRcvMsg=(T_Msg *)recv_msg;
	ptRcvMsg->wMsgID=timer_id;
	if((timer_id>=EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN)&&(timer_id<=EV_RDP_LLRP_PROTIMEOUT_TIMER_END))
	{
	   llrp_dealRcpRspTimeOut(ptRcvMsg);
	}
	else if((timer_id>=EV_RDP_LLRP_RULETIMER_BEGIN)&&(timer_id<=EV_RDP_LLRP_RULETIMER_END))
	{
	   llrp_externPeriodtimerForRoStartTrigger(ptRcvMsg);
	}
	else if(TBootTimerPollingIntervalTimer==timer_id)
	{
	   llrp_dealBootTimerPollingTimer(ptRcvMsg);
	}
    return;
}
void deal_llrp_rawmsg(int loop,unsigned char *recv_msg)
{
    if(NULL==recv_msg)
    {
    	return;
    }
    if((1==loop)||(2==loop))
    {
        //cfg消息处理
        deal_llrp_cfg_msg(loop,recv_msg);
    }
	else if(5==loop)
    {
        //timer消息处理
        deal_llrp_timer_msg(recv_msg);
    }
	else
	{
	    deal_business_msg((T_Msg *)recv_msg);
	}
	/*清空缓冲区*/
    memset(g_aucRdpLlrpRcvMsg, 0, sizeof(g_aucRdpLlrpRcvMsg));
}
int create_thread(void *entry, void *arg,pthread_t *tid)
{
    pthread_t       p_id;
    pthread_attr_t  p_attr;
    
	pthread_attr_init(&p_attr);
	pthread_attr_setdetachstate(&p_attr, PTHREAD_CREATE_DETACHED);
    
    if (0 != (pthread_create(&p_id, &p_attr, (void *(*)(void *))entry, arg)))
    {
        return -1;
    }

    if(NULL != tid)
    {
        *tid = p_id;
    }
    
    return 0;
}

void create_rdp_thread()
{
    pthread_t rule_tid,report_tid;
	int rc;
	rc=create_thread(rdp_rule_main,NULL,&rule_tid);
	if(0!=rc)
	{
	    printf("create rule thread error\r\n");
		exit(-1);
	}
	rc=create_thread(rdp_report_main,NULL,&report_tid);
	if(0!=rc)
	{
	    printf("create report thread error\r\n");
		exit(-1);
	}
	RdpDbgPrint("rule_tid=%u,report_tid=%u\r\n",rule_tid,report_tid);
	return;
}
/**************************************************************************
* 函数名称：usp_Rdp_llrpEntry
* 功能描述：Rdp模块中的llrp线程的入口函数
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTask task
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/
int main()
{
    unsigned int dwRet = 0;
	zmq_pollitem_t  items[7];
    int item_num;
    int rc,ret;
	int loop=0;

	usp_ltk_init();
	init_logm("rdp");
	create_zmq_sockets_rdp();
	create_rdp_thread();
    llrp_init();
	sock_timer=init_timer();
	/*密钥库函数初始化*/
	//发送请求配置消息
	 send_cfg_msg("uhf","request",NULL);
	 memset(items,0,sizeof(items));
     items[0].socket = req_socket_rcp;
     items[0].events = ZMQ_POLLIN;
	 items[1].socket = req_socket_cfg;
     items[1].events = ZMQ_POLLIN;
	 items[2].socket = sub_socket_cfg;
     items[2].events = ZMQ_POLLIN;
	 items[3].socket = pair_socket_rule;
     items[3].events = ZMQ_POLLIN;
	 items[4].socket = pair_socket_report;
     items[4].events = ZMQ_POLLIN;
	 items[5].socket= NULL;
	 items[5].fd = sock_timer;
     items[5].events = ZMQ_POLLIN;
	 
     
     while(1)
     {
         ret = zmq_poll(items, 6, -1);
		 RdpLlrpDbgPrint("(llrp) zmq_poll return ret=%d\n", ret);
         if(ret<0)
         {
            RdpLlrpDbgPrint("(llrp)zmq_poll return , return %d %d,%s\n", ret,errno,zmq_strerror(errno));
            continue;
         }
		 for(loop=0;loop<6;loop++)
		 {
		     if(items[loop].revents & ZMQ_POLLIN)
             {
                 if(5==loop)
                 {
                    RdpLlrpDbgPrint("timer msg\n");
                    rc=read(items[loop].fd, g_aucRdpLlrpRcvMsg, sizeof(g_aucRdpLlrpRcvMsg));
                 }
                 else
                 {
                    rc=zmq_recv(items[loop].socket,g_aucRdpLlrpRcvMsg,sizeof(g_aucRdpLlrpRcvMsg),0);
                 }
				 RdpLlrpDbgPrint("(llrp)zmq_recv loop =%d length=%d\r\n",loop,rc);
                 if(rc<=0)
                 {
                    RdpLlrpDbgPrint("(llrp)zmq_recv error loop=%d error:%s\r\n",loop,zmq_strerror(errno));
                    continue;
                 }
				 
                 deal_llrp_rawmsg(loop,g_aucRdpLlrpRcvMsg);            
             }
		 }
     }

    return 0;
}
/**************************************************************************
* 函数名称：llrp_dealInvDelay
* 功能描述：清点延时
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值： 无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_dealInvDelay()
{
}
/**************************************************************************
* 函数名称：llrp_tagInventory
* 功能描述：清点标签命令构造
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpRODispatchCtrl   *ptActiveRODispatchCtrl
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
**************************************************************************/ 
/*lint -efunc(522,TagInventoryOne)*/
unsigned int llrp_tagInventory(T_RdpLlrpROCtrlAndParam *ptRdpLlrpROCtrlAndParam)
{
    unsigned int dwRet = 0;
    unsigned int dwTestIndex = 0;
    unsigned int dwDataIndex = 0;
    unsigned char ucAntennaID = 0;
    unsigned char ucWorkAIIndex = 0;
    unsigned char ucWorkAntIndex = 0;
    unsigned char ucWorkProtocolIndex = 0;
    memset(g_aucRdpLlrpSndMsg, 0, sizeof(g_aucRdpLlrpSndMsg));
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    T_RdpLlrpProtocolInvSet *ptProtocolInvSet = NULL;
    /*发送到Rcp清点结构*/
    T_USPUHFEpcInventory *ptUSPUHFEpcInventory = NULL;
    T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory = NULL;
    T_USPUHFGBInventory *ptUSPUHFGBInventory = NULL;
    g_dwLlrpTagAccessErrTimes = LLRP_INIT_ACCESS_ERROR_TIMES;
    ucWorkAIIndex = ptRdpLlrpROCtrlAndParam->tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex;
    ucWorkAntIndex = ptRdpLlrpROCtrlAndParam->tRdpLlrpActiveROCtrlIndex.ucWorkAntIndex;
    ucWorkProtocolIndex = ptRdpLlrpROCtrlAndParam->tRdpLlrpActiveROCtrlIndex.ucWorkProtocolIndex;
    ucAntennaID = ptRdpLlrpROCtrlAndParam->tRdpLlrpROSpec.tRdpLlrpAISet.tRdpLlrpAI[ucWorkAIIndex] \
                  .tRdpLlrpAntsInvSet.tAntInv[ucWorkAntIndex].ucAntIndex;

    /*取天线下的指定的协议*/
    ptProtocolInvSet = &ptRdpLlrpROCtrlAndParam->tRdpLlrpROSpec.tRdpLlrpAISet.tRdpLlrpAI[ucWorkAIIndex] \
                       .tRdpLlrpAntsInvSet.tAntInv[ucWorkAntIndex].tRdpLlrpProtocolInvSet[ucWorkProtocolIndex];
    RdpLlrpDbgPrint("(LLRP)begin Big Inventory\r\n");
    RdpLlrpDbgPrint("(LLRP)WorkRoID:%d\r\n", ptRdpLlrpROCtrlAndParam->tRdpLlrpROSpec.dwROSpecID);
    RdpLlrpDbgPrint("(LLRP)WorkAIIndex:%d\r\n", ucWorkAIIndex);
    RdpLlrpDbgPrint("(LLRP)WorkAntIndex:%d,AntId:%d\r\n", ucWorkAntIndex,
                    ptRdpLlrpROCtrlAndParam->tRdpLlrpROSpec.tRdpLlrpAISet.tRdpLlrpAI[ucWorkAIIndex].tRdpLlrpAntsInvSet.tAntInv[ucWorkAntIndex].ucAntIndex);
    RdpLlrpDbgPrint("(LLRP)WorkProtocolIndex:%d,eProtocolID:%d\r\n", ucWorkProtocolIndex, ptProtocolInvSet->eProtocolID);
    /*设置发送缓冲*/
    //llrp_dealInvDelay();
    if (ptProtocolInvSet->eProtocolID == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        RdpLlrpDbgPrint("(LLRP) assemble EPCInvPara \r\n");
        ptUSPUHFEpcInventory = (T_USPUHFEpcInventory *)(ptSndMsg + 1);
        llrp_assembleEpcInvPara(ucAntennaID, ptProtocolInvSet, ptUSPUHFEpcInventory);
        ptSndMsg->wMsgID = EV_USP_UHF_EPC_INVENT;
        ptSndMsg->wMsgLen = sizeof(T_USPUHFEpcInventory);
        RdpLlrpDbgPrint("(LLRP)wModeindex :%d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.wModeindex);
        RdpLlrpDbgPrint("(LLRP)wSession : %d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.wSession);
        RdpLlrpDbgPrint("(LLRP)wEstimatedTagNum : %d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.wEstimatedTagNum);
        for (dwTestIndex = 0 ;dwTestIndex < ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.wMaskNum;dwTestIndex++)
        {
            RdpLlrpDbgPrint("(LLRP)eSelectAction : %d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.tEpcInventoryMask[dwTestIndex].eSelectAction);
            RdpLlrpDbgPrint("(LLRP)wMaskBitPointer : %d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.tEpcInventoryMask[dwTestIndex].wMaskBitPointer);
            RdpLlrpDbgPrint("(LLRP)wMemBank : %d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.tEpcInventoryMask[dwTestIndex].wMemBank);
            RdpLlrpDbgPrint("(LLRP)wMaskLength :%d\r\n", ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.tEpcInventoryMask[dwTestIndex].wMaskLength);
            RdpLlrpDbgPrint("(LLRP)maskdata: ");
            for (dwDataIndex = 0 ;dwDataIndex < BIT_CHANGETO_BYTE(ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.tEpcInventoryMask[dwTestIndex].wMaskLength);dwDataIndex++)
            {
                RdpDbgPrintRaw("%02x ", ptUSPUHFEpcInventory->tEpcInventoryPara.tEpcInventoryMaskList.tEpcInventoryMask[dwTestIndex].ucMaskData[dwDataIndex]);
            }
            RdpLlrpDbgPrint("\r\n");
        }
    }
    /*18000-b 协议*/
    else if (ptProtocolInvSet->eProtocolID == LLRP_AirProtocols_ISO18000_6B)
    {
        RdpLlrpDbgPrint("(LLRP) assemble ISO6BInvPara \r\n");
        ptUSPUHFISO6BInventory = (T_USPUHFISO6BInventory *)(ptSndMsg + 1);
        llrp_assembleISO6BInvPara( ucAntennaID, ptProtocolInvSet, ptUSPUHFISO6BInventory);
        ptSndMsg->wMsgID = EV_USP_UHF_ISO6B_INVENT;
        ptSndMsg->wMsgLen = sizeof(T_USPUHFISO6BInventory);
        RdpLlrpDbgPrint("(LLRP)wModeindex : %d\r\n", ptUSPUHFISO6BInventory->tISO6BInventoryPara.wModeIndex);
        RdpLlrpDbgPrint("(LLRP)wEstimateTag : %d\r\n", ptUSPUHFISO6BInventory->tISO6BInventoryPara.wEstimateTag);
        RdpLlrpDbgPrint("(LLRP)ucCommandType : %d\r\n", ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucCommandType);
        RdpLlrpDbgPrint("(LLRP)ucMask : %d\r\n", ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMask);
        RdpLlrpDbgPrint("(LLRP)ucAddress : %d\r\n", ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucAddress);
        RdpLlrpDbgPrint("(LLRP)ucMaskLen : %d\r\n", ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMaskLen);
        RdpLlrpDbgPrint("(LLRP)maskdata:");
        for (dwTestIndex = 0 ;dwTestIndex < ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMaskLen;dwTestIndex++)
        {
            RdpDbgPrintRaw("%02x ", ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
    }
   else if (ptProtocolInvSet->eProtocolID == LLRP_AirProtocols_GB)
    {
        RdpLlrpDbgPrint("(LLRP) assemble GBInvPara \r\n");
        ptUSPUHFGBInventory = (T_USPUHFGBInventory *)(ptSndMsg + 1);
        llrp_assembleGBInvPara(ucAntennaID, ptProtocolInvSet, ptUSPUHFGBInventory);
        ptSndMsg->wMsgID = EV_USP_UHF_GB_INVENT;
        ptSndMsg->wMsgLen = sizeof(T_USPUHFGBInventory);
        RdpLlrpDbgPrint("(LLRP)wModeindex :%d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.wModeindex);
        RdpLlrpDbgPrint("(LLRP)wSession : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.wSession);
        RdpLlrpDbgPrint("(LLRP)ucGBGBQureyAction : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.ucGBQureyAction);
	 RdpLlrpDbgPrint("(LLRP)ucGBQureySel : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.ucGBQureySel);
	 RdpLlrpDbgPrint("(LLRP)wCCN : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.wCCN);
	 RdpLlrpDbgPrint("(LLRP)wCIN : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.wCIN);
        for (dwTestIndex = 0 ;dwTestIndex < ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.wMaskNum;dwTestIndex++)
        {
            RdpLlrpDbgPrint("(LLRP)ucSortAction : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].ucSortAction);
	     RdpLlrpDbgPrint("(LLRP)ucSortTarget : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].ucSortTarget);
            RdpLlrpDbgPrint("(LLRP)wMaskBitPointer : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].wMaskBitPointer);
            RdpLlrpDbgPrint("(LLRP)wMemBank : %d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].wMemBank);
            RdpLlrpDbgPrint("(LLRP)wMaskLength :%d\r\n", ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].wMaskLength);
            RdpLlrpDbgPrint("(LLRP)maskdata: ");
            for (dwDataIndex = 0 ;dwDataIndex < BIT_CHANGETO_BYTE(ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].wMaskLength);dwDataIndex++)
            {
                RdpDbgPrintRaw("%02x ", ptUSPUHFGBInventory->tGBInventoryPara.tGBInventoryMaskList.tGBInventoryMask[dwTestIndex].ucMaskData[dwDataIndex]);
            }
            RdpLlrpDbgPrint("\r\n");
        }
    }
    else
    {
        dwRet = RDP_LLRP_PROTO_ERROR;
        RdpLlrpDbgPrint("(LLRP)llrp_tagInventory abnormal  protocol is %d\r\n", ptProtocolInvSet->eProtocolID);
        /*写入异常*/
        RDP_EXCEPT(RDP_LLRP_PROTO_ERROR, ptProtocolInvSet->eProtocolID, 0, 0, RDP_LLRP_DISPATCH_ID);
        return dwRet;
        /*状态机恢复机制*/
    }
    LLRP_START_TIMER(TFpgaResp, TFpgaRespCount);
    ptSndMsg->mtype = LLRP_SYN_MSG;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_UHF_TNO;
    ptSndMsg->wSenderTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wReceiverTno = USP_UHF_TNO;
    ptSndMsg->wMsgSequence = USP_LIB_SCP_MSGSEQ(g_wMsgSequence);
    if (0 > RDP_SEND_MSG(req_socket_rcp, ptSndMsg))
    {
        RdpLlrpDbgPrint("(LLRP)send msg error for TagInventoryOne\r\n");
        dwRet = RDP_SEND_MESSGAE_ERROR;
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)llrp_tagInventory send rcp success\r\n");
    }
    return dwRet;
}
/**************************************************************************
* 函数名称：llrp_buildAnNodeFoAllQueueOfRO
* 功能描述：根据RO的状态和优先级创建一个节点
                            一般由于AddRo和disableRO队列
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_buildAnNodeFoAllQueueOfRO(T_RdpLlrpROEntry *ptQueueHead, unsigned int dwROIndex, unsigned int dwPriority)
{
    T_RdpLlrpROEntry *ptNewNode = NULL;
    T_RdpLlrpROEntry *ptNodeCursor = NULL;
    ptNewNode = (T_RdpLlrpROEntry *)malloc(sizeof(T_RdpLlrpROEntry));
    ptNewNode->dwROIndex = dwROIndex;
    ptNewNode->dwPriority = dwPriority;
    for (ptNodeCursor = ptQueueHead;ptNodeCursor->ptNext != NULL;ptNodeCursor = ptNodeCursor->ptNext)
    {
        ;
    }
    ptNodeCursor->ptNext = ptNewNode;
    ptNewNode->ptNext = NULL;
}
/**************************************************************************
* 函数名称：llrp_buildAnNodeFoAllQueueOfAO
* 功能描述：创建一个节点插入到队列中
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessEntry *ptQueueHead,
                             unsigned int dwAccessIndex
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_buildAnNodeFoAllQueueOfAccess(T_RdpLlrpAccessEntry *ptQueueHead, unsigned int dwAccessIndex)
{
    T_RdpLlrpAccessEntry *ptNewNode = NULL;
    T_RdpLlrpAccessEntry *ptNodeCursor = NULL;
    ptNewNode = (T_RdpLlrpAccessEntry *)malloc(sizeof(T_RdpLlrpAccessEntry));
    ptNewNode->dwAccessIndex = dwAccessIndex;
    for (ptNodeCursor = ptQueueHead;ptNodeCursor->ptNext != NULL;ptNodeCursor = ptNodeCursor->ptNext)
    {
        ;
    }
    ptNodeCursor->ptNext = ptNewNode;
    ptNewNode->ptNext = NULL;
}
/**************************************************************************
* 函数名称：llrp_findAnNodeFoAllQueueOfRO
* 功能描述：根据dwROindex和dwPriory返回队列节点
                             所有队列使用
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpROEntry *ptQueueHead,
                             unsigned int dwROIndex,
                             unsigned int dwPriority
* 输出参数：
* 返 回 值：  T_RdpLlrpROEntry * 返回节点的指针
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpROEntry * llrp_findAndGetAnNodeFoAllQueueOfRO(T_RdpLlrpROEntry *ptQueueHead, unsigned int dwROIndex, unsigned int dwPriority)
{
    T_RdpLlrpROEntry *ptNewNode = NULL;
    T_RdpLlrpROEntry *ptLastNodeCursor = NULL;
    T_RdpLlrpROEntry *ptNodeCursor = NULL;
    for (ptLastNodeCursor = ptQueueHead, ptNodeCursor = ptQueueHead->ptNext ;
            ptNodeCursor != NULL;ptLastNodeCursor = ptNodeCursor, ptNodeCursor = ptNodeCursor->ptNext)
    {
        if (ptNodeCursor->dwROIndex == dwROIndex && ptNodeCursor->dwPriority == dwPriority)
        {
            ptLastNodeCursor->ptNext = ptNodeCursor->ptNext;
            break;
        }
    }
    return ptNodeCursor;

}
/**************************************************************************
* 函数名称：llrp_findAndFreeAnNodeFoAllQueueOfRO
* 功能描述：查找节点并释放节点
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
unsigned int llrp_findAndFreeAnNodeFoAllQueueOfRO(T_RdpLlrpROEntry *ptQueueHead, unsigned int dwROIndex, unsigned int dwPriority)
{
    T_RdpLlrpROEntry *ptFindNode = NULL;
    ptFindNode = llrp_findAndGetAnNodeFoAllQueueOfRO(ptQueueHead, dwROIndex, dwPriority);
    if (ptFindNode == NULL)
    {
        return LLRP_FINDANDFREENODE_FAIL;
    }
    else
    {
        free(ptFindNode);
        return LLRP_FINDANDFREENODE_SUCCESS;
    }
}
/**************************************************************************
* 函数名称：llrp_findAndGetAnNodeFoAllQueueOfAccess
* 功能描述：根据dwAccess返回节点
                             所有队列使用
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessEntry *ptQueueHead,
                             unsigned int dwAccessIndex
* 输出参数：
* 返 回 值：  T_RdpLlrpAccessEntry * 返回节点的指针
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpAccessEntry * llrp_findAndGetAnNodeFoAllQueueOfAccess(T_RdpLlrpAccessEntry *ptQueueHead, unsigned int dwAccessIndex)
{
    T_RdpLlrpAccessEntry *ptNewNode = NULL;
    T_RdpLlrpAccessEntry *ptLastNodeCursor = NULL;
    T_RdpLlrpAccessEntry *ptNodeCursor = NULL;
    for (ptLastNodeCursor = ptQueueHead, ptNodeCursor = ptQueueHead->ptNext ;
            ptNodeCursor != NULL;ptLastNodeCursor = ptNodeCursor, ptNodeCursor = ptNodeCursor->ptNext)
    {
        if (ptNodeCursor->dwAccessIndex == dwAccessIndex)
        {
            ptLastNodeCursor->ptNext = ptNodeCursor->ptNext;
            break;
        }
    }
    return ptNodeCursor;

}
/**************************************************************************
* 函数名称：llrp_findAndFreeAnNodeFoAllQueueOfAccess
* 功能描述：查找节点并释放节点
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAccessEntry *ptQueueHead,
                             unsigned int dwAccessIndex
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
unsigned int llrp_findAndFreeAnNodeFoAllQueueOfAccess(T_RdpLlrpAccessEntry *ptQueueHead, unsigned int dwAccessIndex)
{
    T_RdpLlrpAccessEntry *ptFindNode = NULL;
    ptFindNode = llrp_findAndGetAnNodeFoAllQueueOfAccess(ptQueueHead, dwAccessIndex);
    if (ptFindNode == NULL)
    {
        return LLRP_FINDANDFREENODE_FAIL;
    }
    else
    {
        free(ptFindNode);
        return LLRP_FINDANDFREENODE_SUCCESS;
    }
}
/**************************************************************************
* 函数名称：llrp_insertAnNodetoPriorityQueueOfRO
* 功能描述：插入一个节点到Ready队列
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值： 无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_insertAnNodetoPriorityQueueOfRO(T_RdpLlrpROEntry *ptInsertNode, T_RdpLlrpROEntry *ptReadyQueueHead)
{
    T_RdpLlrpROEntry *ptNewNode = NULL;
    T_RdpLlrpROEntry *ptNodeCursor = NULL;
    T_RdpLlrpROEntry *ptLastNodeCursor = NULL;
    if (ptInsertNode == NULL)
    {
        /*写入异常 退出*/
        return ;
    }
    for (ptLastNodeCursor = ptReadyQueueHead, ptNodeCursor = ptReadyQueueHead->ptNext;
            ptNodeCursor != NULL;
            ptLastNodeCursor = ptNodeCursor, ptNodeCursor = ptNodeCursor->ptNext)
    {
        if (ptInsertNode->dwPriority < ptNodeCursor->dwPriority)
        {
            ptLastNodeCursor->ptNext = ptInsertNode;
            ptInsertNode->ptNext = ptNodeCursor;
            break;
        }
    }
    if (ptNodeCursor == NULL)
    {
        ptLastNodeCursor->ptNext = ptInsertNode;
        ptInsertNode->ptNext = NULL;
    }
}
/**************************************************************************
* 函数名称：llrp_insertAnNodetoAllQueueOfRO
* 功能描述：插入一个节点到队列中
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值： 无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_insertAnNodetoAllQueueOfRO(T_RdpLlrpROEntry *ptInsertNode, T_RdpLlrpROEntry *ptQueueHead)
{
    T_RdpLlrpROEntry *ptNewNode = NULL;
    T_RdpLlrpROEntry *ptNodeCursor = NULL;
    if (ptInsertNode == NULL)
    {
        /*写入异常 退出*/
        RdpLlrpDbgPrint("(LLRP)error happened RO Queue is NULL\r\n ");
        return ;
    }
    for (ptNodeCursor = ptQueueHead;ptNodeCursor->ptNext != NULL;ptNodeCursor = ptNodeCursor->ptNext)
    {
        ;
    }
    ptNodeCursor->ptNext = ptInsertNode;
    ptInsertNode->ptNext = NULL;
}

/**************************************************************************
* 函数名称：llrp_insertAnNodetoAllQueueOfAccess
* 功能描述：插入一个节点到Access队列中
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值： 无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_insertAnNodetoAllQueueOfAccess(T_RdpLlrpAccessEntry *ptInsertNode, T_RdpLlrpAccessEntry *ptQueueHead)
{
    T_RdpLlrpAccessEntry *ptNewNode = NULL;
    T_RdpLlrpAccessEntry *ptNodeCursor = NULL;
    RdpLlrpDbgPrint("(LLRP)insert An Node to All Queue Of AO\r\n ");
    if (ptInsertNode == NULL)
    {
        /*写入异常 退出*/
        RdpLlrpDbgPrint("(LLRP)error happened AO Queue is NULL\r\n ");
        return ;
    }
    for (ptNodeCursor = ptQueueHead;ptNodeCursor->ptNext != NULL;ptNodeCursor = ptNodeCursor->ptNext)
    {
        ;
    }
    ptNodeCursor->ptNext = ptInsertNode;
    ptInsertNode->ptNext = NULL;
}
/**************************************************************************
* 函数名称：llrp_getRunRO
* 功能描述：返回正在执行的RO参数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpROCtrlAndParam * llrp_getRunRO()
{
    unsigned char ucWorkAIIndex = 0;
    unsigned int dwROIndex = 0;
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext != NULL)
    {
        dwROIndex = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext->dwROIndex;
        return &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex];
    }
    else
    {
        /*写入异常*/
        //RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
        RdpLlrpDbgPrint("(LLRP) llrp_getRunRO error\r\n");
        return NULL;
    }
}
/**************************************************************************
* 函数名称：llrp_getRunAI
* 功能描述：返回正在执行的AI参数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpAI * llrp_getRunAI()
{
    unsigned char ucWorkAIIndex = 0;
    unsigned int dwROIndex = 0;
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext != NULL)
    {
        dwROIndex = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext->dwROIndex;
        ucWorkAIIndex = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex] \
                        .tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex;

        return &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex].tRdpLlrpROSpec.tRdpLlrpAISet.tRdpLlrpAI[ucWorkAIIndex];
    }
    else
    {
        /*写入异常*/
        //RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
        RdpLlrpDbgPrint("(LLRP) llrp_getRunAI error\r\n");
        return NULL;

    }

}


/**************************************************************************
* 函数名称：llrp_getRunAP
* 功能描述：返回正在执行的天线下的协议参数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   T_RdpLlrpProtocolInvSet *  协议参数
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpProtocolInvSet * llrp_getRunAP()
{
    unsigned char ucWorkAIIndex = 0;
    unsigned int dwROIndex = 0;
    unsigned char ucWorkAntIndex = 0;
    unsigned char ucWorkProtocolIndex = 0;
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext != NULL)
    {
        dwROIndex = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext->dwROIndex;
        ucWorkAIIndex
        = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex].tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex;
        ucWorkAntIndex
        = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex].tRdpLlrpActiveROCtrlIndex.ucWorkAntIndex;
        ucWorkProtocolIndex
        = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex].tRdpLlrpActiveROCtrlIndex.ucWorkProtocolIndex;
        return &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex] \
               .tRdpLlrpROSpec.tRdpLlrpAISet.tRdpLlrpAI[ucWorkAIIndex].tRdpLlrpAntsInvSet.tAntInv[ucWorkAntIndex] \
               .tRdpLlrpProtocolInvSet[ucWorkProtocolIndex];

    }
    else
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
        RdpLlrpDbgPrint("(LLRP) llrp_getRunAP error\r\n");
        return NULL;
    }


}
/**************************************************************************
* 函数名称：llrp_getRunAnt
* 功能描述：返回正在执行的天线参数集合
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   T_RdpLlrpProtocolInvSet *  协议参数
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpAntInv * llrp_getRunAnt()
{
    unsigned char ucWorkAIIndex = 0;
    unsigned int dwROIndex = 0;
    unsigned char ucWorkAntIndex = 0;
    unsigned char ucWorkProtocolIndex = 0;
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext != NULL)
    {
        dwROIndex = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext->dwROIndex;
        ucWorkAIIndex
        = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex].tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex;
        ucWorkAntIndex
        = g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex].tRdpLlrpActiveROCtrlIndex.ucWorkAntIndex;

        return &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tRdpLlrpROCtrlAndParam[dwROIndex] \
               .tRdpLlrpROSpec.tRdpLlrpAISet.tRdpLlrpAI[ucWorkAIIndex].tRdpLlrpAntsInvSet.tAntInv[ucWorkAntIndex];
    }
    else
    {
        /*写入异常*/
        // RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
        RdpLlrpDbgPrint("(LLRP) llrp_getRunAnt error\r\n");
        return NULL;
    }



}
/**************************************************************************
* 函数名称：llrp_getRunAccess
* 功能描述：返回正在运行的Access
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   T_RdpLlrpAccessCtrlAndParam * Access的参数
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_RdpLlrpAccessCtrlAndParam* llrp_getRunAccess()
{
    unsigned int dwAccessIndex = 0;
    if (g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRunAccess.ptNext != NULL)
    {
        dwAccessIndex = g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRunAccess.ptNext->dwAccessIndex;
        return &g_tRdpLlrpReaderDispatch.ptReaderAccessSpecData->tRdpLlrpAccessCtrlAndParam[dwAccessIndex];
    }
    else
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
        RdpLlrpDbgPrint("(LLRP) llrp_getRunAccess error\r\n");
        return NULL;
    }

}
/**************************************************************************
* 函数名称：llrp_nextTagAccessOp
* 功能描述：下发access的下一个Op
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpListOPCtrlSet*ptlistOpCtrlSet,
                            LLRP_tEAirProtocols eProtocolID,
                            void *ptTagID
                            
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_nextTagAccessOp(T_RdpLlrpListOPCtrlSet*ptlistOpCtrlSet, LLRP_tEAirProtocols eProtocolID, void *ptTagID)
{
    unsigned int dwRet = RDP_SUCCESS;
    T_RdpLlrpUID *ptLlrpUID=NULL;
    memset(g_aucRdpLlrpSndMsg, 0, sizeof(g_aucRdpLlrpSndMsg));
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    ptSndMsg->mtype = LLRP_SYN_MSG;
    ptSndMsg->wSenderTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wReceiverTno = USP_UHF_TNO;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_UHF_TNO;
    ptSndMsg->wMsgSequence = USP_LIB_SCP_MSGSEQ(g_wMsgSequence);
    RdpLlrpDbgPrint("(LLRP) llrp_nextTagAccessOp\r\n");
    if (eProtocolID == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        /*EPC协议读写规则下发*/

        dwRet = llrp_nextEpcAccessOp(ptSndMsg , ptlistOpCtrlSet, ptTagID);
        if (dwRet == RDP_LLRP_UNSUPORT_OPTYPE)
        {
            llrp_sendNextEpcInv();
            return ;
        }
    }
    else if (eProtocolID == LLRP_AirProtocols_ISO18000_6B)
    {
        /*ISO6B协议读写规则下发*/
        dwRet = llrp_nextISO6BAccessOp(ptSndMsg , ptlistOpCtrlSet, ptTagID);
        if (dwRet == RDP_LLRP_UNSUPORT_OPTYPE)
        {
            llrp_sendNextISO6BInv();
            return ;
        }
    }
    else if (eProtocolID == LLRP_AirProtocols_GB)
    {
        /*GB协议读写规则下发*/
	  ptLlrpUID=(T_RdpLlrpUID *)ptTagID;
	  RdpLlrpDbgPrint("(LLRP)ptLlrpUID->wTagDataLen=%d\r\n",ptLlrpUID->wTagDataLen);
        dwRet = llrp_nextGBAccessOp(ptSndMsg , ptlistOpCtrlSet, ptTagID);
        if (dwRet == RDP_LLRP_UNSUPORT_OPTYPE)
        {
            llrp_sendNextGBInv();
            return ;
        }
    }
    else
    {
        /*写入异常复位状态机*/

        RDP_EXCEPT(RDP_LLRP_PROTO_ERROR, eProtocolID, 0, 0, RDP_LLRP_DISPATCH_ID);
        if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
        {
            RdpLlrpDbgPrint("(LLRP)there is not active ro need scan ready queue\r\n");
            g_tRdpLlrpReaderDispatch.pfScanROToRun(g_tRdpLlrpReaderDispatch.ptReaderRoSpecData);
        }
        return ;
    }
    if (LLRP_ClientRequestOpSpec != dwRet)
    {
        if (0 > RDP_SEND_MSG(req_socket_rcp, ptSndMsg))
        {
            /*发送失败写入异常*/
            RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, ptSndMsg->wMsgID, ptSndMsg->wMsgLen, 0, RDP_LLRP_DISPATCH_ID);
        }
    }
}

/**************************************************************************
* 函数名称：llrp_dealdllopen
* 功能描述：打开动态库
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char *ptdllPath 
                            
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void * llrp_dealdllopen(unsigned char *ptdllPath)
{
    void *pdllHandle = NULL;
    void *pszErr = NULL;
    pdllHandle = dlopen(ptdllPath, RTLD_LAZY); // RTLD_LAZY 延迟加载
    pszErr = dlerror();
    if (NULL == pdllHandle || pszErr )
    {
        RdpLlrpDbgPrint("(LLRP) load dll %s,error\r\n", ptdllPath);
        return NULL;
    }
    return pdllHandle;
}
/**************************************************************************
* 函数名称：llrp_dealdllsym
* 功能描述：查找动态库函数
* 访问的表：无
* 修改的表：无
* 输入参数：void *pdllHandle:动态库句柄
           unsigned char *pfunName:函数名称                            
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void * llrp_dealdllsym(void *pdllHandle , unsigned char *pfunName)
{
    void *pszErr = NULL;
    if (pdllHandle == NULL)
    {
        return NULL;
    }
    void (*pfun)() = dlsym(pdllHandle, pfunName); // 定位动态链接库中的函数
    pszErr = dlerror();
    if (NULL == pfun || pszErr)
    {
        RdpLlrpDbgPrint("(LLRP) Find symbol  %s failed!%s\n", pfunName, pszErr);
        dlclose(pdllHandle);
        return NULL;
    }
    return pfun;
}
/**************************************************************************
* 函数名称：llrp_loadUserDll
* 功能描述：加载动态库中的函数
* 访问的表：无
* 修改的表：无
* 输入参数：
                           
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_loadUserDll()
{
    static unsigned char s_ucHasRun = FALSE;
    unsigned int dwRet = 0;
    PwdFun pInitfun;

    if (s_ucHasRun)
    {
        return;
    }

    s_ucHasRun = TRUE;
    
    g_tRdpPwdSys.pdllHandle = llrp_dealdllopen(LLRP_PWD_DLL_PATH);
    RdpLlrpDbgPrint("llrp_loadUserDll g_tRdpPwdSys.pdllHandle=0x%x\r\n", g_tRdpPwdSys.pdllHandle);
    if (g_tRdpPwdSys.pdllHandle != NULL)
    {
        pInitfun = llrp_dealdllsym(g_tRdpPwdSys.pdllHandle, "usp_uhf_adapter_init");
        if (NULL == pInitfun)
        {
            RdpLlrpDbgPrint("pInitfun is NULL\r\n");
            RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
            g_tRdpPwdSys.pfusp_lib_uhf_privateCmd = NULL;
            g_tRdpPwdSys.pfusp_lib_uhf_getPassword = NULL;
            return ;
        }
        dwRet = pInitfun();
        RdpLlrpDbgPrint("pInitfun dwRet=%d\r\n", dwRet);
        if (dwRet != 0)
        {
            RdpLlrpDbgPrint("INIT PSAM FAILED 11\r\n");
            RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, dwRet, 0, 0, RDP_LLRP_DISPATCH_ID);
            g_tRdpPwdSys.pfusp_lib_uhf_privateCmd = NULL;
            g_tRdpPwdSys.pfusp_lib_uhf_getPassword = NULL;
            return ;
        }
        RdpLlrpDbgPrint("the dynamic lib load success\r\n");
        g_tRdpPwdSys.pfusp_lib_uhf_privateCmd = llrp_dealdllsym(g_tRdpPwdSys.pdllHandle, "usp_lib_uhf_privateCmd");
        g_tRdpPwdSys.pfusp_lib_uhf_getPassword = llrp_dealdllsym(g_tRdpPwdSys.pdllHandle, "usp_lib_uhf_getPassword");
        if ((NULL == g_tRdpPwdSys.pfusp_lib_uhf_privateCmd)
                || (NULL == g_tRdpPwdSys.pfusp_lib_uhf_getPassword))
        {
            RdpLlrpDbgPrint("error happened pfusp_lib_uhf_privateCmd=0x%x,pfusp_lib_uhf_getPassword=0x%x\r\n",
                            g_tRdpPwdSys.pfusp_lib_uhf_privateCmd,
                            g_tRdpPwdSys.pfusp_lib_uhf_getPassword);
            RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_DISPATCH_ID);
            return ;
        }
    }
    else
    {
        g_tRdpPwdSys.pfusp_lib_uhf_privateCmd = NULL;
        g_tRdpPwdSys.pfusp_lib_uhf_getPassword = NULL;
        RdpLlrpDbgPrint("the dynamic lib load failed\r\n");
    }
}
/**************************************************************************
* 函数名称：llrp_dealUhfPrivateCmd
* 功能描述：处理业务透传指令
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                            
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_dealUhfPrivateCmd(T_Msg *ptRcvMsg)
{
    unsigned short int wloop = 0;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    unsigned int dwRet = 0;
    unsigned char ucalarminfo[5] = {0};
    LLRP_tSLLRPStatus *ptSLLRPStatus = LLRP_LLRPStatus_construct();
    LLRP_tSUHF_PRIVATE_CMD * ptLLRP_tSUHF_PRIVATE_CMD = *(LLRP_tSUHF_PRIVATE_CMD **)(ptRcvMsg + 1);
    LLRP_tSUHF_PRIVATE_CMD_RESPONSE * ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE = LLRP_UHF_PRIVATE_CMD_RESPONSE_construct();
    LLRP_UHF_PRIVATE_CMD_RESPONSE_setLLRPStatus(ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE, ptSLLRPStatus);
    ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE->hdr.MessageID = ptLLRP_tSUHF_PRIVATE_CMD->hdr.MessageID;
    ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE->CmdID = ptLLRP_tSUHF_PRIVATE_CMD->CmdID;
    unsigned char auBuffer[512] = {0};
    unsigned short int wOutputLen = 0;
    RdpLlrpDbgPrint("(LLRP)receive an lUhfPrivateCmd dymamic addr =%4x,point addr %4x\r\n", *(unsigned int *)(ptRcvMsg + 1), ptLLRP_tSUHF_PRIVATE_CMD);
    if (g_tRdpPwdSys.pfusp_lib_uhf_privateCmd == NULL)
    {
        RdpLlrpDbgPrint("the dynamic lib load failed return error\r\n");
        ptSLLRPStatus->eStatusCode = LLRP_StatusCode_R_DeviceError;
    }
    else
    {
        RdpLlrpDbgPrint("CmdID %d\r\n", ptLLRP_tSUHF_PRIVATE_CMD->CmdID);
        RdpLlrpDbgPrint("the dynamic lib load success  do usp_lib_uhf_privateCmd\r\n");
        for (wloop = 0;wloop < ptLLRP_tSUHF_PRIVATE_CMD->CmdPara.nValue;wloop++)
        {
            RdpDbgPrintRaw("%d ", ptLLRP_tSUHF_PRIVATE_CMD->CmdPara.pValue[wloop]);
        }
        RdpLlrpDbgPrint("\r\n");
        dwRet = g_tRdpPwdSys.pfusp_lib_uhf_privateCmd(ptLLRP_tSUHF_PRIVATE_CMD->CmdID,
                                                                                    ptLLRP_tSUHF_PRIVATE_CMD->CmdPara.pValue,
                                                                                    ptLLRP_tSUHF_PRIVATE_CMD->CmdPara.nValue,
                                                                                    auBuffer, &wOutputLen);
        if (dwRet == 0)
        {
            if (wOutputLen == 0)
            {
                RdpDbgPrint("pfusp_lib_uhf_privateCmd  return nothing \r\n");
                ptSLLRPStatus->eStatusCode = LLRP_StatusCode_R_DeviceError;
            }
            else
            {
                if (0 == auBuffer[0])
                {
                    RdpLlrpDbgPrint("pfusp_lib_uhf_privateCmd  do success and send alarm restore\r\n");                    

                }
                else
                {
                    sprintf((char *)ucalarminfo,"%d",auBuffer[0]);
                    RdpLlrpDbgPrint("pfusp_lib_uhf_privateCmd  do success and send alarm alarm code %d\r\n",auBuffer[0]);                    

                }
                ptSLLRPStatus->eStatusCode = LLRP_StatusCode_M_Success;
                LLRP_UHF_PRIVATE_CMD_RESPONSE_setCmdAckPara(ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE, LLRP_u8v_construct(wOutputLen));
                memcpy(ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE->CmdAckPara.pValue , auBuffer, ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE->CmdAckPara.nValue);
                RdpLlrpDbgPrint("pfusp_lib_uhf_privateCmd return value\r\n");
                for (wloop = 0;wloop < ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE->CmdAckPara.nValue;wloop++)
                {
                    RdpDbgPrintRaw("%d ", ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE->CmdAckPara.pValue[wloop]);
                }
                RdpLlrpDbgPrint("\r\n");
            }
         }   
        else
        {            
                RdpLlrpDbgPrint("pfusp_lib_uhf_privateCmd  do user lib fail\r\n");
                ptSLLRPStatus->eStatusCode = LLRP_StatusCode_R_DeviceError;
         }
         ptSndMsg->mtype = LLRP_SYN_MSG;
         ptSndMsg->ucLinkIndex = ptRcvMsg->ucLinkIndex;
         ptSndMsg->ucLinkType = ptRcvMsg->ucLinkType;
         /*这里wSenderTno和wReceiverTno标识路由的源和目的
          wSrcTno和wDstTno 表示上下周转的节点*/
         ptSndMsg->wSenderTno = ptRcvMsg->wReceiverTno;
         ptSndMsg->wReceiverTno = ptRcvMsg->wSenderTno;
         ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
         ptSndMsg->wDstTno = USP_RDP_RULE_TNO;
         ptSndMsg->wMsgID = EV_UHF_PRIVATE_CMD_ACK;
         ptSndMsg->wMsgSequence = ptRcvMsg->wMsgSequence;
         /*传输的是地址指针 所以这里是指针所占地址长度*/
         ptSndMsg->wMsgLen = sizeof(ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE);
         *(LLRP_tSUHF_PRIVATE_CMD_RESPONSE **)(ptSndMsg + 1) = ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE;
         RdpLlrpDbgPrint("(LLRP)uhf private cmd Rsp addr ,0x%4x,dynamic point %d\r\n", *(unsigned int *)(ptSndMsg + 1), ptLLRP_tSUHF_PRIVATE_CMD_RESPONSE);
         dwRet = RDP_SEND_MSG(pair_socket_rule, ptSndMsg);
         if (dwRet < 0)
         {
             RdpLlrpDbgPrint("(LLRP)msgsend error\r\n");
             /*写入异常*/
             RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, dwRet, 0, 0, RDP_LLRP_DISPATCH_ID);
         }
         usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSUHF_PRIVATE_CMD);
     }
}
/**************************************************************************
* 函数名称：llrp_dealUhfPrivateSetPassword
* 功能描述：设置密钥消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
                     
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_dealUhfPrivateSetPassword(T_Msg *ptRcvMsg)
{
    unsigned int dwRet = 0;
    unsigned int dwIndex = 0;
    LLRP_tSPwdIndexPara *ptTempLLRP_tSPwdIndexPara = NULL;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    LLRP_tSUHF_PRIVATE_SETPASSWORD * ptLLRP_tSUHF_PRIVATE_SETPASSWORD = *(LLRP_tSUHF_PRIVATE_SETPASSWORD **)(ptRcvMsg + 1);
    LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE * ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE = LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_construct();
    ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE->hdr.MessageID = ptLLRP_tSUHF_PRIVATE_SETPASSWORD->hdr.MessageID;
    if (ptLLRP_tSUHF_PRIVATE_SETPASSWORD->listPwdIndexPara == NULL)
    {
        RdpLlrpDbgPrint("(LLRP)there is not PwdIndex , use the default getPassword func\r\n");
        ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE->Result = 0;
        g_tRdpPwdSys.dwPwdIndexNum = 0;
        g_tRdpPwdSys.pfusp_lib_uhf_getPassword = NULL;
    }
    else
    {
        for (dwIndex = 0 , g_tRdpPwdSys.dwPwdIndexNum = 0, ptTempLLRP_tSPwdIndexPara = ptLLRP_tSUHF_PRIVATE_SETPASSWORD->listPwdIndexPara;
                ptTempLLRP_tSPwdIndexPara;
                ptTempLLRP_tSPwdIndexPara = (LLRP_tSPwdIndexPara *)ptTempLLRP_tSPwdIndexPara->hdr.pNextSubParameter, dwIndex++, g_tRdpPwdSys.dwPwdIndexNum++)
        {

            g_tRdpPwdSys.atPwdIndexPara[dwIndex].dwMembank = ptTempLLRP_tSPwdIndexPara->MB;
            g_tRdpPwdSys.atPwdIndexPara[dwIndex].wWordPointer = ptTempLLRP_tSPwdIndexPara->WordPointer;
            g_tRdpPwdSys.atPwdIndexPara[dwIndex].wWordCount = ptTempLLRP_tSPwdIndexPara->WordCount;
            RdpLlrpDbgPrint("(LLRP)%d pwdindex mb %d \r\n", dwIndex, g_tRdpPwdSys.atPwdIndexPara[dwIndex].dwMembank);
            RdpLlrpDbgPrint("(LLRP)%d pwdindex WordCount %d \r\n", dwIndex, g_tRdpPwdSys.atPwdIndexPara[dwIndex].wWordCount);
            RdpLlrpDbgPrint("(LLRP)%d pwdindex WordPointer %d \r\n", dwIndex, g_tRdpPwdSys.atPwdIndexPara[dwIndex].wWordPointer);
            if (g_tRdpPwdSys.dwPwdIndexNum == LLRP_MAX_PWDINDEX_NUM )
            {
                RdpLlrpDbgPrint("(LLRP)the PwdIndex num is larger than the largest num\r\n");
                break;
            }
        }
        if (ptTempLLRP_tSPwdIndexPara != NULL)
        {
            RdpLlrpDbgPrint("(LLRP)init the g_tRdpPwdSys return error");
            memset(&g_tRdpPwdSys, 0, sizeof(T_RdpLlrpPwdSys));
            ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE->Result = 1;
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)set pwdinex success return success\r\n");
            ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE->Result = 0;
        }
    }
    ptSndMsg->mtype = LLRP_SYN_MSG;
    ptSndMsg->ucLinkIndex = ptRcvMsg->ucLinkIndex;
    ptSndMsg->ucLinkType = ptRcvMsg->ucLinkType;
    /*这里wSenderTno和wReceiverTno标识路由的源和目的
     wSrcTno和wDstTno 表示上下周转的节点*/
    ptSndMsg->wSenderTno = ptRcvMsg->wReceiverTno;
    ptSndMsg->wReceiverTno = ptRcvMsg->wSenderTno;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_RDP_RULE_TNO;
    ptSndMsg->wMsgID = EV_UHF_PRIVATE_SETPASSWORD_ACK;
    ptSndMsg->wMsgSequence = ptRcvMsg->wMsgSequence;
    /*传输的是地址指针 所以这里是指针所占地址长度*/
    ptSndMsg->wMsgLen = sizeof(ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE);
    *(LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE **)(ptSndMsg + 1) = ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE;
    RdpLlrpDbgPrint("(LLRP)uhf private cmd Rsp addr ,0x%4x,dynamic point %d\r\n", *(unsigned int *)(ptSndMsg + 1), ptLLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE);
    dwRet = RDP_SEND_MSG(pair_socket_rule, ptSndMsg);
    if (dwRet < 0)
    {
        RdpLlrpDbgPrint("(LLRP)msgsend error\r\n");
        /*写入异常*/
        RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, dwRet, 0, 0, RDP_LLRP_DISPATCH_ID);
    }
    usp_ltk_freeMessage((LLRP_tSMessage *)ptLLRP_tSUHF_PRIVATE_SETPASSWORD);
}

