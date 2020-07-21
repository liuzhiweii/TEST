/***************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
*
* 文件名称：ufhllrpReport.c
* 文件标识：
* 内容摘要：LLRP协议report处理模块
* 其它说明：
* 当前版本：
* 作    者：程亮
* 完成日期：2012.05.17 
**********************************************************************/


/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include"rdppub.h" 
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
unsigned char g_ucLocalReportDataBuffer[LLRP_MAX_REPORT_BUFFER];
T_RdpLlrpAcculateReportData g_tRdpLlrpReaderAcculateReport[MAX_LINK_NUM];

extern T_RdpLlrpReaderDispatch g_tRdpLlrpReaderDispatch;
extern T_RdpConfig g_tRdpConfig;

extern void *pair_socket_report;
/***********************************************************
 *                     本地变量                            *
***********************************************************/


/***********************************************************
 *                     全局函数                            *
***********************************************************/


/***********************************************************
 *                     局部函数                            *
***********************************************************/


/**************************************************************************
* 函数名称：llrp_getReportuSec
* 功能描述：返回报告的时间
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：  
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
static unsigned long long llrp_getReportuSec()
{
    struct timeval tCurrentTime;
    unsigned long long ldwReportuSec = 0;
    if (gettimeofday(&tCurrentTime, NULL) != 0)
    {
        RdpLlrpDbgPrint("(LLRP)gettimeofday is error\r\n");
    }
    ldwReportuSec = (unsigned long long)tCurrentTime.tv_sec;
    ldwReportuSec = ldwReportuSec * 1000000 + tCurrentTime.tv_usec;
    return ldwReportuSec;
}
/**************************************************************************
* 函数名称：llrp_getTagReportContentSelector
* 功能描述：返回报告的内容
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：   T_USPRdpLlrpTagReportContentSelector * 报告的内容
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
T_USPRdpLlrpTagReportContentSelector * llrp_getTagReportContentSelector()
{
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData \
            ->tRdpLlrpROCtrlAndParam[g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext->dwROIndex] \
            .tRdpLlrpROSpec.tRdpLlrpROReport.bIsDefaultCfgFlag != TRUE )
    {
        return &g_tRdpLlrpReaderDispatch.ptReaderRoSpecData \
               ->tRdpLlrpROCtrlAndParam[g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext->dwROIndex] \
               .tRdpLlrpROSpec.tRdpLlrpROReport.tRdpLlrpTagReportContentSelector;
    }
    else
    {
        return &g_tRdpConfig.tROReportSpec.tRdpLlrpTagReportContentSelector;
    }

}

/**************************************************************************
* 函数名称：llrp_constructLocalROReport
* 功能描述：构造本地报告并插入到链表中
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned short int wProtoType,
                             unsigned short int wAntennaIndex,
                             unsigned short int wRssi,
                             unsigned short int wPC,
                             unsigned short int wCRC,
                             unsigned short int wChannelIndex,
                             unsigned short int wTagLen,
                             unsigned char     *pbTagID
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_constructLocalROReport(unsigned short int wProtoType,
                                 unsigned short int wAntennaIndex,
                                 unsigned short int wRssi,
                                 unsigned short int wPC,
                                 unsigned short int wCRC,
                                 unsigned short int wChannelIndex,
                                 unsigned short int wTagLen,
                                 unsigned char *pbTagID)
{
    unsigned int dwTestIndex = 0;
    T_RdpLlrpSingleReportCtrl *ptTempSingleReportCtr = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    T_RdpLlrpSingleReportCtrl *ptMallocSingleReportCtr = NULL;
    T_RdpLlrpTagReport *ptTempTagReport = NULL;
    T_RdpLlrpROTagReport *ptTempRoTagReport = NULL;
    T_USPUHFEpcInventoryRes *ptTempEpcInventoryRes = NULL;
    T_USPUHFISO6BInventoryRes *ptTempISO6BInventoryRes = NULL;
    T_USPRdpLlrpTagReportContentSelector *ptTempTagReportContentSelector = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpProtocolInvSet *ptProtocolInvSet = NULL;
    if ((wProtoType == LLRP_AirProtocols_EPCGlobalClass1Gen2)||(wProtoType == LLRP_AirProtocols_GB))
    {
        /*ISO6B 长度单位是字*/
        ptTempSingleReportCtr->tUID.wTagDataLen = wTagLen * sizeof(unsigned short int);
    }
    else if (wProtoType == LLRP_AirProtocols_ISO18000_6B)
    {
        /*ISO6B 长度单位是字节*/
        ptTempSingleReportCtr->tUID.wTagDataLen = wTagLen;
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)Rcp return an protocol type unsuported\r\n");
        /*写入异常*/
        RDP_EXCEPT(RDP_LLRP_PROTO_ERROR, 0, 0, 0, RDP_LLRP_REPORT_ID);
        return ;
    }
    memcpy(ptTempSingleReportCtr->tUID.aucTagData, pbTagID, ptTempSingleReportCtr->tUID.wTagDataLen);
    ptTempSingleReportCtr->ucReportType = LLRP_ROSPEC_REPORT_DATA;
    /*获得正在运行的Ro*/
    ptRunRoCtrlAndPara = llrp_getRunRO();
    if (ptRunRoCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_REPORT_ID);
        return ;
    }
    /*获取RO类型*/
    ptTempSingleReportCtr->ucROType
    = ((LLRP_ROSpecStartTriggerType_Periodic == ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.dwROSpecStartTriggerType) ? \
       RO_START_TRIGGER_PERIOD : RO_START_TRIGGER_SINGLE);
    RdpLlrpDbgPrint("(LLRP)eROSpecStartTriggerType:%d,ucROType:%d\r\n",
                    ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.dwROSpecStartTriggerType,
                    ptTempSingleReportCtr->ucROType);
    /*构建ro内部报告*/
    ptTempRoTagReport = &ptTempSingleReportCtr->tRdpLlrpTagReport.tROTagReport;
    /*获取当前Ro的报告内容选择情况*/
    ptTempTagReportContentSelector = llrp_getTagReportContentSelector();
    /*Reoport赋值*/
    ptTempRoTagReport->dwROSpecID = ptRunRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID;
    ptTempRoTagReport->wSpecIndex = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableSpecIndex,
                                    ptRunRoCtrlAndPara->tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex,
                                    LLRP_DEFAULT_REPORT_WORD16);
    /*不管配置与否*/
    ptTempRoTagReport->dwAccessSpecID = LLRP_DEFAULT_REPORT_WORD32;

    /*分别赋予 第一次和最后一次的时间*/
    ptTempRoTagReport->lwFirstSeenTimestampUTC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableFirstSeenTimestamp,
            llrp_getReportuSec(),
            LLRP_DEFAULT_REPORT_WORD32);
    ptTempRoTagReport->lwLastSeenTimestampUTC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableLastSeenTimestamp,
            llrp_getReportuSec(),
            LLRP_DEFAULT_REPORT_WORD32);

    ptTempRoTagReport->wTagCount = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableTagSeenCount,
                                   1, LLRP_DEFAULT_REPORT_WORD16);
    ptProtocolInvSet = llrp_getRunAP();
    ptTempRoTagReport->wInventoryParameterSpecID = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableInventoryParameterSpecID,
            ptProtocolInvSet->wInvParamSpecID, LLRP_DEFAULT_REPORT_WORD16);
    ptTempRoTagReport->wPeakRSSI = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnablePeakRSSI,
                                   wRssi , LLRP_DEFAULT_REPORT_WORD16);

    ptTempRoTagReport->wAntennaID = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableAntennaID,
                                    wAntennaIndex, LLRP_DEFAULT_REPORT_WORD16);
    ptTempRoTagReport->wChannelIndex = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableChannelIndex,
                                       wChannelIndex, LLRP_DEFAULT_REPORT_WORD16);
    if (wProtoType == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        /*ISO6B 长度单位是字*/
        ptTempRoTagReport->eProtocolID = LLRP_AirProtocols_EPCGlobalClass1Gen2;
        ptTempRoTagReport->wCRC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableCRC, wCRC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempRoTagReport->wPC_Bits = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnablePC, wPC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempRoTagReport->tID.tEpcID.wTagDataLen = wTagLen;
        memcpy(ptTempRoTagReport->tID.tEpcID.awTagData, pbTagID, wTagLen*sizeof(unsigned short int));
        RdpLlrpDbgPrint("(LLRP)EPC:");
        for (dwTestIndex = 0; dwTestIndex < ptTempRoTagReport->tID.tEpcID.wTagDataLen; dwTestIndex++)
        {
            RdpDbgPrintRaw("%04x  ", ptTempRoTagReport->tID.tEpcID.awTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        /**/
        ptTempSingleReportCtr->wMsgLen = struct_fixed_len(T_RdpLlrpROTagReport, tID)
                                         + struct_fixed_len(T_RdpLlrpEpcID, awTagData)
                                         + ptTempRoTagReport->tID.tEpcID.wTagDataLen * sizeof(unsigned short int);
    }
    else if (wProtoType == LLRP_AirProtocols_ISO18000_6B)
    {
        ptTempRoTagReport->eProtocolID = LLRP_AirProtocols_ISO18000_6B;
        ptTempRoTagReport->tID.tISOID.wTagDataLen = wTagLen;
        memcpy(ptTempRoTagReport->tID.tISOID.aucTagData, pbTagID, wTagLen);
        RdpLlrpDbgPrint("(LLRP)ISO6B TID :");
        for (dwTestIndex = 0; dwTestIndex < ptTempRoTagReport->tID.tISOID.wTagDataLen; dwTestIndex++)
        {
            RdpDbgPrintRaw("%02x  ", ptTempRoTagReport->tID.tISOID.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempSingleReportCtr->wMsgLen = struct_fixed_len(T_RdpLlrpROTagReport, tID)
                                         + struct_fixed_len(T_RdpLlrpISOID, aucTagData)
                                         + ptTempRoTagReport->tID.tISOID.wTagDataLen;
    }
    else if (wProtoType == LLRP_AirProtocols_GB)
    {
        /*GB 长度单位是字*/
        ptTempRoTagReport->eProtocolID = LLRP_AirProtocols_GB;
        ptTempRoTagReport->wPC_Bits = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnablePC, wPC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempRoTagReport->tID.tGBID.wTagDataLen = wTagLen;
        memcpy(ptTempRoTagReport->tID.tGBID.awTagData, pbTagID, wTagLen*sizeof(unsigned short int));
        RdpLlrpDbgPrint("(LLRP)EPC:");
        for (dwTestIndex = 0; dwTestIndex < ptTempRoTagReport->tID.tGBID.wTagDataLen; dwTestIndex++)
        {
            RdpDbgPrintRaw("%04x  ", ptTempRoTagReport->tID.tGBID.awTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        /**/
        ptTempSingleReportCtr->wMsgLen = struct_fixed_len(T_RdpLlrpROTagReport, tID)
                                         + struct_fixed_len(T_RdpLlrpGBID, awTagData)
                                         + ptTempRoTagReport->tID.tGBID.wTagDataLen * sizeof(unsigned short int);
    }
    /*如果积累加上这项*/
#if 1
    RdpLlrpDbgPrint("(LLRP)eProtocolID: %d\r\n", ptTempRoTagReport->eProtocolID );
    RdpLlrpDbgPrint("(LLRP)ROSpecID : %d\r\n", ptTempRoTagReport->dwROSpecID);
    RdpLlrpDbgPrint("(LLRP)dwAccessSpecID : %d\r\n", ptTempRoTagReport->dwAccessSpecID);
    RdpLlrpDbgPrint("(LLRP)SpecIndex : %d\r\n", ptTempRoTagReport->wSpecIndex);
    RdpLlrpDbgPrint("(LLRP)TagCount : %d\r\n", ptTempRoTagReport->wTagCount);
    RdpLlrpDbgPrint("(LLRP)scPeakRSSI : %d\r\n", ptTempRoTagReport->wPeakRSSI);
    RdpLlrpDbgPrint("(LLRP)ROSpecID : %d\r\n", ptTempRoTagReport->dwROSpecID);
    RdpLlrpDbgPrint("(LLRP)AntennaID : %d\r\n", ptTempRoTagReport->wAntennaID);
    RdpLlrpDbgPrint("(LLRP)ChannelIndex : %d\r\n", ptTempRoTagReport->wChannelIndex);
    RdpLlrpDbgPrint("(LLRP)CRC : %d\r\n", ptTempRoTagReport->wCRC);
    RdpLlrpDbgPrint("(LLRP)PC_Bits: %d\r\n", ptTempRoTagReport->wPC_Bits);
    RdpLlrpDbgPrint("(LLRP)InventoryParameterSpecID :%d\r\n", ptTempRoTagReport->wInventoryParameterSpecID);
#endif
    /*挂载节点到RO的报告链表上*/
    RdpLlrpDbgPrint("(LLRP)insert RoReport into activeRO report link\r\n");
    llrp_insertReportToRunRoReportLink(ptTempSingleReportCtr);
}

/**************************************************************************
* 函数名称：llrp_constructLocalAOReportHead
* 功能描述：构建AO报告的除去op结果的部分
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned short int wProtoType,
                             unsigned short int wAntennaIndex,
                             unsigned short int wRssi,
                             unsigned short int wPC,
                             unsigned short int wCRC,
                             unsigned short int wChannelIndex,
                             unsigned short int wTagLen,
                             unsigned char     *pbTagID
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_constructLocalAOReportHead(unsigned short int wProtoType,
                                     unsigned short int wAntennaIndex,
                                     unsigned short int wRssi,
                                     unsigned short int wPC,
                                     unsigned short int wCRC,
                                     unsigned short int wChannelIndex,
                                     unsigned short int wTagLen,
                                     unsigned char *pbTagID)
{
    unsigned int dwTestIndex = 0;
    T_RdpLlrpSingleReportCtrl *ptTempSingleReportCtr = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    T_RdpLlrpTagReport *ptTempTagReport = NULL;
    T_RdpLlrpAccessTagReport *ptTempAccessTagReport = NULL;
    T_USPRdpLlrpTagReportContentSelector *ptTempTagReportContentSelector = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptAccessCtrlAndParam = NULL;
    T_RdpLlrpProtocolInvSet *ptProtocolInvSet = NULL;
    RdpLlrpDbgPrint("(LLRP)local AoReport head: \r\n");
    if ((wProtoType == LLRP_AirProtocols_EPCGlobalClass1Gen2)
            || (wProtoType == LLRP_AirProtocols_ISO18000_6B)
            || (wProtoType == LLRP_AirProtocols_GB))
    {
        /*ISO6B 长度单位是字*/
        ptTempSingleReportCtr->tUID.wTagDataLen = wTagLen;
    }
    else
    {
        RdpLlrpDbgPrint("(LLRP)Rcp return an protocol type unsuported\r\n");
        /*写入异常*/
        RDP_EXCEPT(RDP_LLRP_PROTO_ERROR, wProtoType, 0, 0, RDP_LLRP_REPORT_ID);
        return ;
    }
    memcpy(ptTempSingleReportCtr->tUID.aucTagData, pbTagID, ptTempSingleReportCtr->tUID.wTagDataLen);
    ptTempSingleReportCtr->ucReportType = LLRP_ACCESSSPEC_REPORT_DATA;
    /*获得正在运行的Ro*/
    ptRunRoCtrlAndPara = llrp_getRunRO();
    if (ptRunRoCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_REPORT_ID);
        return ;
    }
    /*获取RO报告类型*/
    ptTempSingleReportCtr->ucROType = ((LLRP_ROSpecStartTriggerType_Periodic == ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.dwROSpecStartTriggerType) ? RO_START_TRIGGER_PERIOD : RO_START_TRIGGER_SINGLE);
    RdpLlrpDbgPrint("(LLRP)eROSpecStartTriggerType :%d,ucROType:%d\r\n",
                    ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROBoundary.tRdpLlrpROStartTrigger.dwROSpecStartTriggerType,
                    ptTempSingleReportCtr->ucROType);
    /*构建ro内部报告*/
    ptTempAccessTagReport = &ptTempSingleReportCtr->tRdpLlrpTagReport.tAccessTagReport;
    /*获取当前Ro的报告内容选择情况*/
    ptTempTagReportContentSelector = llrp_getTagReportContentSelector();
    /*Reoport赋值*/
    ptTempAccessTagReport->dwROSpecID = ptRunRoCtrlAndPara->tRdpLlrpROSpec.dwROSpecID;
    ptTempAccessTagReport->wSpecIndex = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableSpecIndex,
                                        ptRunRoCtrlAndPara->tRdpLlrpActiveROCtrlIndex.ucWorkAIIndex,
                                        LLRP_DEFAULT_REPORT_WORD16);
    /*不管配置与否*/
    ptAccessCtrlAndParam = llrp_getRunAccess();
    if (ptAccessCtrlAndParam == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_REPORT_ID);
        return ;
    }
    ptTempAccessTagReport->dwAccessSpecID = ptAccessCtrlAndParam->tRdpLlrpAccess.dwAccessSpecID;

    /*分别赋予 第一次和最后一次的时间*/
    ptTempAccessTagReport->lwFirstSeenTimestampUTC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableFirstSeenTimestamp,
            llrp_getReportuSec(),
            LLRP_DEFAULT_REPORT_WORD32);
    ptTempAccessTagReport->lwLastSeenTimestampUTC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableLastSeenTimestamp,
            llrp_getReportuSec(),
            LLRP_DEFAULT_REPORT_WORD32);

    ptTempAccessTagReport->wTagCount = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableTagSeenCount,
                                       1, LLRP_DEFAULT_REPORT_WORD16);
    ptProtocolInvSet = llrp_getRunAP();
    ptTempAccessTagReport->wInventoryParameterSpecID = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableInventoryParameterSpecID,
            ptProtocolInvSet->wInvParamSpecID, LLRP_DEFAULT_REPORT_WORD16);
    ptTempAccessTagReport->wPeakRSSI = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnablePeakRSSI,
                                       wRssi , LLRP_DEFAULT_REPORT_WORD16);
    ptTempAccessTagReport->wAntennaID = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableAntennaID,
                                        wAntennaIndex, LLRP_DEFAULT_REPORT_WORD16);
    ptTempAccessTagReport->wChannelIndex = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableChannelIndex,
                                           wChannelIndex, LLRP_DEFAULT_REPORT_WORD16);
    if (wProtoType == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        /*ISO6B 长度单位是字*/
        ptTempAccessTagReport->eProtocolID = LLRP_AirProtocols_EPCGlobalClass1Gen2;
        ptTempAccessTagReport->wCRC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableCRC, wCRC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempAccessTagReport->wPC_Bits = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnablePC, wPC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempAccessTagReport->tID.tEpcID.wTagDataLen = wTagLen / sizeof(unsigned short int);
        memcpy(ptTempAccessTagReport->tID.tEpcID.awTagData, pbTagID, wTagLen);
        RdpLlrpDbgPrint("(LLRP)EPC:");
        for (dwTestIndex = 0; dwTestIndex < ptTempAccessTagReport->tID.tEpcID.wTagDataLen; dwTestIndex++)
        {
            RdpDbgPrintRaw("%04x  ", ptTempAccessTagReport->tID.tEpcID.awTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        /**/
        ptTempSingleReportCtr->wMsgLen = struct_fixed_len(T_RdpLlrpAccessTagReport, tID)
                                         + struct_fixed_len(T_RdpLlrpEpcID, awTagData)
                                         + ptTempAccessTagReport->tID.tEpcID.wTagDataLen * sizeof(unsigned short int);
    }
    else if (wProtoType == LLRP_AirProtocols_ISO18000_6B)
    {
        ptTempAccessTagReport->eProtocolID = LLRP_AirProtocols_ISO18000_6B;
        ptTempAccessTagReport->tID.tISOID.wTagDataLen = wTagLen;
        memcpy(ptTempAccessTagReport->tID.tISOID.aucTagData, pbTagID, wTagLen);
        RdpLlrpDbgPrint("(LLRP)ISO6B TID :");
        for (dwTestIndex = 0; dwTestIndex < ptTempAccessTagReport->tID.tISOID.wTagDataLen; dwTestIndex++)
        {
            RdpDbgPrintRaw("%02x  ", ptTempAccessTagReport->tID.tISOID.aucTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        ptTempSingleReportCtr->wMsgLen = struct_fixed_len(T_RdpLlrpAccessTagReport, tID)
                                         + struct_fixed_len(T_RdpLlrpISOID, aucTagData)
                                         + ptTempAccessTagReport->tID.tISOID.wTagDataLen;
    }
     if (wProtoType == LLRP_AirProtocols_GB)
    {
        /*ISO6B 长度单位是字*/
        ptTempAccessTagReport->eProtocolID = LLRP_AirProtocols_GB;
        ptTempAccessTagReport->wCRC = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnableCRC, wCRC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempAccessTagReport->wPC_Bits = LLRP_SET_DATA_REPORT(ptTempTagReportContentSelector->bEnablePC, wPC, LLRP_DEFAULT_REPORT_WORD16);
        ptTempAccessTagReport->tID.tGBID.wTagDataLen = wTagLen / sizeof(unsigned short int);
        memcpy(ptTempAccessTagReport->tID.tGBID.awTagData, pbTagID, wTagLen);
        RdpLlrpDbgPrint("(LLRP)EPC:");
        for (dwTestIndex = 0; dwTestIndex < ptTempAccessTagReport->tID.tGBID.wTagDataLen; dwTestIndex++)
        {
            RdpDbgPrintRaw("%04x  ", ptTempAccessTagReport->tID.tGBID.awTagData[dwTestIndex]);
        }
        RdpLlrpDbgPrint("\r\n");
        /**/
        ptTempSingleReportCtr->wMsgLen = struct_fixed_len(T_RdpLlrpAccessTagReport, tID)
                                         + struct_fixed_len(T_RdpLlrpGBID, awTagData)
                                         + ptTempAccessTagReport->tID.tGBID.wTagDataLen * sizeof(unsigned short int);
    }
    /*如果积累加上这项*/
#if 1
    RdpLlrpDbgPrint("(LLRP)eProtocolID:%d  ", ptTempAccessTagReport->eProtocolID);
    RdpLlrpDbgPrint("(LLRP)wMsgLen:%d    ", ptTempSingleReportCtr->wMsgLen);
    RdpLlrpDbgPrint("(LLRP)ROSpecID : %d   ", ptTempAccessTagReport->dwROSpecID);
    RdpLlrpDbgPrint("(LLRP)SpecIndex : %d   ", ptTempAccessTagReport->wSpecIndex);
    RdpLlrpDbgPrint("(LLRP)TagCount : %d  ", ptTempAccessTagReport->wTagCount);
    RdpLlrpDbgPrint("(LLRP)scPeakRSSI : %d  ", ptTempAccessTagReport->wPeakRSSI);
    RdpLlrpDbgPrint("(LLRP)ROSpecID : %d   ", ptTempAccessTagReport->dwROSpecID);
    RdpLlrpDbgPrint("(LLRP)AntennaID : %d  ", ptTempAccessTagReport->wAntennaID);
    RdpLlrpDbgPrint("(LLRP)ChannelIndex : %d  ", ptTempAccessTagReport->wChannelIndex);
    RdpLlrpDbgPrint("(LLRP)CRC : %d  ", ptTempAccessTagReport->wCRC);
    RdpLlrpDbgPrint("(LLRP)PC_Bits: %d  ", ptTempAccessTagReport->wPC_Bits);
    RdpLlrpDbgPrint("(LLRP)InventoryParameterSpecID :%d\r\n", ptTempAccessTagReport->wInventoryParameterSpecID);
#endif
    /*挂载节点到RO的报告链表上*/

}


/**************************************************************************
* 函数名称：llrp_constructLocalAOReportHeadForClientReuqest
* 功能描述：
* 访问的表：无
* 修改的表：无
* 输入参数：构造clientreuqst返回或超时AO报告的头部
* 输出参数：
* 返 回 值：   无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_constructLocalAOReportHeadForClientReuqest()
{
    unsigned int dwTestIndex = 0;
    unsigned short int wProtoType;
    unsigned short int wAntennaIndex;
    unsigned short int wRssi;
    unsigned short int wChannelIndex;
    unsigned short int wTagLen;
    unsigned char aucTagID[USP_RDP_LLRP_UID_SIZE];
    T_RdpLlrpSingleReportCtrl *ptTempSingleReportCtr = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    T_RdpLlrpAccessTagReport *ptTempAccessTagReport = NULL;
    if (ptTempSingleReportCtr->ucReportType == LLRP_ROSPEC_REPORT_DATA)
    {
        /*写入异常报告类型错了*/
        RDP_EXCEPT(RDP_LLRP_PROTO_ERROR, 0, 0, 0, RDP_LLRP_REPORT_ID);
        RdpLlrpDbgPrint("(LLRP)this is not access report an fatal error happen\r\n");
    }
    if (ptTempAccessTagReport->eProtocolID == LLRP_AirProtocols_EPCGlobalClass1Gen2)
    {
        wProtoType = LLRP_AirProtocols_EPCGlobalClass1Gen2;
        wTagLen = ptTempAccessTagReport->tID.tEpcID.wTagDataLen * sizeof(unsigned short int);
        memcpy(aucTagID, ptTempAccessTagReport->tID.tEpcID.awTagData, wTagLen);
    }
    else if(ptTempAccessTagReport->eProtocolID == LLRP_AirProtocols_ISO18000_6B)
    {
        wProtoType = LLRP_AirProtocols_ISO18000_6B;
        wTagLen = ptTempAccessTagReport->tID.tISOID.wTagDataLen;
        memcpy(aucTagID, ptTempAccessTagReport->tID.tISOID.aucTagData, wTagLen);
    }
    else if (ptTempAccessTagReport->eProtocolID == LLRP_AirProtocols_GB)
    {
        wProtoType = LLRP_AirProtocols_GB;
        wTagLen = ptTempAccessTagReport->tID.tGBID.wTagDataLen * sizeof(unsigned short int);
        memcpy(aucTagID, ptTempAccessTagReport->tID.tGBID.awTagData, wTagLen);
    }

    wAntennaIndex = ptTempAccessTagReport->dwAccessSpecID;
    wChannelIndex = ptTempAccessTagReport->wChannelIndex;
    wRssi = ptTempAccessTagReport->wPeakRSSI;
    llrp_constructLocalAOReportHead(wProtoType,
                                    wAntennaIndex,
                                    wRssi,
                                    LLRP_DEFAULT_REPORT_WORD16,
                                    LLRP_DEFAULT_REPORT_WORD16,
                                    wChannelIndex,
                                    wTagLen,
                                    aucTagID);
}
/**************************************************************************
* 函数名称：llrp_insertReportToRunRoReportLink
* 功能描述：插入报告到Ro的Report链表中
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptLocalSingleReportCtrl
                             本地保存的报告节点
* 输出参数：
* 返 回 值：  0 成功插入
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_insertReportToRunRoReportLink(T_RdpLlrpSingleReportCtrl *ptLocalSingleReportCtrl)
{
    T_RdpLlrpSingleReportCtrl *ptReportTail = NULL;
    T_RdpLlrpSingleReportCtrl *ptMallocSingleReportCtr = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpAcculateReportData *ptActiveROReportLink = NULL;
    T_RdpLlrpOpResultCtrl *ptRdpLlrpOpResultCtrl = NULL;
    T_RdpLlrpEpcReadOpResult *ptRdpLlrpEpcReadOpResult = NULL;
    unsigned int dwTestIndex = 0;
    ptMallocSingleReportCtr = (T_RdpLlrpSingleReportCtrl *)malloc( struct_fixed_len(T_RdpLlrpSingleReportCtrl, tRdpLlrpTagReport) + ptLocalSingleReportCtrl->wMsgLen);
    /*直接拷贝内存区域*/
    memcpy(ptMallocSingleReportCtr,
           ptLocalSingleReportCtrl,
           struct_fixed_len(T_RdpLlrpSingleReportCtrl, tRdpLlrpTagReport) + ptLocalSingleReportCtrl->wMsgLen);
    ptRunRoCtrlAndPara = llrp_getRunRO();
    if (ptRunRoCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_REPORT_ID);
        return ;
    }
    ptActiveROReportLink = &ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink;
    /*增加报告积累*/
    ptActiveROReportLink->dwReportSize = + (struct_fixed_len(T_RdpLlrpSingleReportCtrl, tRdpLlrpTagReport) + ptLocalSingleReportCtrl->wMsgLen);
    /*增加报告数量*/
    ptActiveROReportLink->dwReportNum++;
    /*如果报告大于限制,要上报告警完全可以写成一个函数*/
    ptReportTail = ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptActiveRoReportTail;
    /*没有节点的情况*/
    if (ptReportTail == NULL)
    {

        ptMallocSingleReportCtr->ptlast = NULL;
        ptMallocSingleReportCtr->ptNext = NULL;
        /*更新当前RO报告的尾指针*/
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptActiveRoReportTail = ptMallocSingleReportCtr;
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptAcculateReportHead = ptMallocSingleReportCtr;
        RdpLlrpDbgPrint("(LLRP)RoReportlink is empty this report is first, RoreportLink head addr:0x%x\r\n", ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptAcculateReportHead );

    }
    else
    {
        /*更新当前RO报告指针新报告到尾节点 */
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptActiveRoReportTail->ptNext = ptMallocSingleReportCtr;
        ptMallocSingleReportCtr->ptlast = ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptActiveRoReportTail;
        ptMallocSingleReportCtr->ptNext = NULL;
        /*更新当前RO报告的尾指针*/
        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptActiveRoReportTail = ptMallocSingleReportCtr;
        RdpLlrpDbgPrint("(LLRP)insert this report into RoReportLink, RoreportLink head addr:0x%x,ReportLink tail addr:0x%x\r\n",
                        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptAcculateReportHead,
                        ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport.tActiveRoReportLink.ptActiveRoReportTail);

    }
}

/**************************************************************************
* 函数名称：llrp_freeReportToROReportLink
* 功能描述：释放Ro报告链表的空间
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpAcculateReportData *ptActiveRoReportLink
                             当前的Ro链表结构
* 输出参数：
* 返 回 值：  0 成功插入
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_freeReportToROReportLink(T_RdpLlrpAcculateReportData *ptActiveRoReportLink)
{
    T_RdpLlrpSingleReportCtrl *ptReportCursor = NULL;
    RdpLlrpDbgPrint("(LLRP)active Ro delete or disable  free Report\r\n");
    while (ptActiveRoReportLink->ptAcculateReportHead != NULL)
    {

        ptReportCursor = ptActiveRoReportLink->ptAcculateReportHead;
        ptActiveRoReportLink->ptAcculateReportHead = ptReportCursor->ptNext;
        free(ptReportCursor);
    }
    ptActiveRoReportLink->dwReportNum = 0;
    ptActiveRoReportLink->dwReportSize = 0;
    ptActiveRoReportLink->ptActiveRoReportTail = NULL;
    
}

/**************************************************************************
* 函数名称：llrp_sendReport
* 功能描述：发送报告给Report模块
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpSingleReportCtrl *ptSendReport,
                             报告的头节点地址
                             T_Msg *ptSndMsg
                             报告中有msgID等相关信息
* 输出参数：
* 返 回 值：  0 成功插入
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_sendReport(T_RdpLlrpSingleReportCtrl *ptSendReport, T_Msg *ptSndMsg, unsigned int dwMessgeID)
{
    /*直接把地址发送给Report模块*/
    T_RdpLlrpSendReportContent *ptSendReportContent = NULL;
    ptSendReportContent = (T_RdpLlrpSendReportContent *)(ptSndMsg + 1);
    ptSndMsg->wMsgID = EV_USP_RDP_SEND_LINK_REPORT;
    ptSendReportContent->dwMessgeID = dwMessgeID;
    ptSendReportContent->ptReportAddr = ptSendReport;
    if (NULL != ptSendReportContent->ptReportAddr)
    {
        RdpLlrpDbgPrint("(LLRP)llrp send report to Report module,the report head addr =0x%x,dwMessgeID=%d\r\n",
                        ptSendReportContent->ptReportAddr, dwMessgeID);
        if (0 > RDP_SEND_MSG(pair_socket_report, ptSndMsg))
        {
            /*发送失败写入异常*/
            RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, 0, 0, 0, RDP_LLRP_REPORT_ID);
        }
    }
}
/**************************************************************************
* 函数名称：llrp_getRunRoMsgID
* 功能描述：获取正在运行Ro的消息号
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：  0 成功插入
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
unsigned int llrp_getRunRoMsgID()
{ 
    T_RdpLlrpROCtrlAndParam *ptTempRdpLlrpROCtrlAndPara = NULL;
    ptTempRdpLlrpROCtrlAndPara =  llrp_getRunRO();
    if(ptTempRdpLlrpROCtrlAndPara == NULL)
    {
        RDP_EXCEPT(RDP_RO_STATE_ERROR, 0, 0, 0, RDP_LLRP_REPORT_ID);
    }
    else
    {
        return ptTempRdpLlrpROCtrlAndPara->tRdpLlrpRODispatchCtrl.dwRevMessageID;
    }
    return 0;
}
