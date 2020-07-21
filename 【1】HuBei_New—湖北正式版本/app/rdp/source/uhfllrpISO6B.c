/***************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
*
* 文件名称：ufhllrpISO6B.c
* 文件标识：
* 内容摘要：LLRPISO6B协议模块
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

extern unsigned char g_ucLocalReportDataBuffer[LLRP_MAX_REPORT_BUFFER];
extern unsigned char g_aucRdpLlrpSndMsg[RDP_MAX_LEN_MSG];
extern unsigned char g_aucRdpLlrpRcvMsg[RDP_MAX_LEN_MSG];
extern T_RdpConfig g_tRdpConfig;
extern T_RdpLlrpReaderDispatch g_tRdpLlrpReaderDispatch;
extern unsigned short int g_wMsgSequence;

extern void *req_socket_rcp;
extern void *pair_socket_rule;
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
* 函数名称：llrp_assembleISO6BInvProtocolPara
* 功能描述：构造清点参数中的协议参数
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucAntennaIndex
                             天线ID
                            T_RdpLlrpProtocolInvSet  *ptTempProtocolInvSet
                             这根天线下的ISO6B协议的参数
* 输出参数：T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory
                            返回 清点参数
* 返 回 值：   0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_assembleISO6BInvProtocolPara( unsigned char ucAntennaIndex,
                                        T_RdpLlrpProtocolInvSet*ptTempProtocolPara,
                                        T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory)
{
    unsigned short int wloop = 0;
    T_USPRdpLlrpAntennaConfiguration *ptAntConfig = NULL;
    T_USPRdpLlrpAntennaExtConfiguration *ptAntExtConfig = NULL;
    T_USPRdpLlrpISO6BInventoryCommand *ptConfigISO6BInventoryCommand = NULL;
    T_USPRdpLlrpISO6BInventoryCommand *ptISO6BInventoryCommand = NULL;
    ptAntConfig = &g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[ucAntennaIndex - 1];
    ptAntExtConfig = &g_tRdpConfig.trAntennaExtConfiguration[ucAntennaIndex - 1];

    if (ptTempProtocolPara->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bISOFilterControl == TRUE)
    {
        ptISO6BInventoryCommand = &ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;

        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMask
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucMask;

        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucAddress
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucAddress;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucCommandType
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucCommandType;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMaskLen
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].wWordDataLen;
        memcpy(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData,
               ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucWordData,
               sizeof(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData));
    }
    else
    {
        ptISO6BInventoryCommand
        = &ptTempProtocolPara->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMask
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucMask;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucAddress
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucAddress;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucCommandType
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucCommandType;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMaskLen
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].wWordDataLen;
        memcpy(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData,
               ptISO6BInventoryCommand->tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucWordData,
               sizeof(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData));
    }

    if (ptTempProtocolPara->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bISORFControl == TRUE)
    {
        ptISO6BInventoryCommand = &ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.wModeIndex = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BRFControl.wModeIndex;
    }
    else
    {
        ptISO6BInventoryCommand
        = &ptTempProtocolPara->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.wModeIndex = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BRFControl.wModeIndex;
    }

    /*增加population*/
    if (ptTempProtocolPara->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bISOSingulationControl == TRUE)
    {
        ptISO6BInventoryCommand = &ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.wEstimateTag
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.wTagPopulation;
    }
    else
    {
        ptISO6BInventoryCommand
        = &ptTempProtocolPara->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.wEstimateTag
        = ptISO6BInventoryCommand->tUSPRdpLlrpISO6BSingulationControl.wTagPopulation ;
    }
}

/**************************************************************************
* 函数名称：llrp_assembleISO6BInvPara
* 功能描述：构造清点参数中的协议参数
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned char ucAntennaIndex
                             天线ID
                            T_RdpLlrpProtocolInvSet  *ptTempProtocolInvSet
                             这根天线下的ISO6B协议的参数
* 输出参数：T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory
                            返回 清点参数
* 返 回 值：   0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_assembleISO6BInvPara( unsigned char ucAntennaIndex,
                                T_RdpLlrpProtocolInvSet*ptTempProtocolPara,
                                T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory)
{
    unsigned short int wloop = 0;
    T_USPRdpLlrpAntennaConfiguration *ptAntConfig = NULL;
    T_USPRdpLlrpAntennaExtConfiguration *ptAntExtConfig = NULL;
    T_USPUHFRfFreqCfg *ptUSPRdpLlrpRfFreqCfg = NULL;
    ptAntConfig = &g_tRdpConfig.tUSPRdpLlrpAntennaConfiguration[ucAntennaIndex - 1];
    ptAntExtConfig = &g_tRdpConfig.trAntennaExtConfiguration[ucAntennaIndex - 1];
    ptUSPRdpLlrpRfFreqCfg = &ptAntExtConfig->tUSPRdpLlrpRfFreqCfg.tUSPUHFRfFreqCfg6B;
    ptUSPUHFISO6BInventory->dwAntIndex = (unsigned int)ucAntennaIndex;
    /*天线配置继承 直接赋系统默认的值*/
    if (ptTempProtocolPara->tRdpLlrpAntConfigCtrl.bIsDefaultCfgFlag == TRUE)
    {
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.wEstimateTag
        = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BSingulationControl.wTagPopulation;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.wModeIndex
        = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BRFControl.wModeIndex;
        memcpy (ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel.wFreqChannel,
                ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannel,
                sizeof(ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel.wFreqChannel));
        ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel.wFreqChannelNum
        = ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannelNum;
        ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.wFreqHopMode
        = ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.wFreqHopMode;
        ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.wHopTimer
        = ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.wHopTimer;
        ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFixFreqChannel
        = ptUSPRdpLlrpRfFreqCfg->wFixFreqChannel;
        ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqTableID
        = ptUSPRdpLlrpRfFreqCfg->wFreqTableID;
        ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqWorkType
        = ptUSPRdpLlrpRfFreqCfg->wFreqWorkType;
        ptUSPUHFISO6BInventory->tInventoryRfPara.wTransmitPower
        = ptAntExtConfig->tTransmitPower.wTransmitPower6B;

        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMask
        = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucMask;

        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucAddress
        = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucAddress;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucCommandType
        = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucCommandType;
        ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMaskLen
        = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].wWordDataLen;
        memcpy(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData,
               ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucWordData,
               sizeof(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData));

    }
    else
    {
        if (ptTempProtocolPara->tRdpLlrpAntConfigCtrl.bRFTransmitterCtrl == TRUE)
        {
            memcpy (ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel.wFreqChannel,
                    ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannel,
                    sizeof(ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel.wFreqChannel));
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel.wFreqChannelNum
            = ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannelNum;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.wFreqHopMode
            = ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.wFreqHopMode;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.wHopTimer
            = ptUSPRdpLlrpRfFreqCfg->tFreqHopConfig.wHopTimer;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFixFreqChannel
            = ptUSPRdpLlrpRfFreqCfg->wFixFreqChannel;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqTableID
            = ptUSPRdpLlrpRfFreqCfg->wFreqTableID;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqWorkType
            = ptUSPRdpLlrpRfFreqCfg->wFreqWorkType;
            ptUSPUHFISO6BInventory->tInventoryRfPara.wTransmitPower
            = ptAntExtConfig->tTransmitPower.wTransmitPower6B;

        }
        else
        {
            ptUSPUHFISO6BInventory->tInventoryRfPara.wTransmitPower
            = ptTempProtocolPara->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpRFTransmitterSettings.wTransmitPower;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.wHopTimer = 1;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqTableID
            = ptTempProtocolPara->tUSPRdpLlrpAntennaConfiguration.tUSPRdpLlrpRFTransmitterSettings.wHopTableID;
            ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqWorkType = TRUE;
            /*根据跳频 协议初始化跳频表*/
            llrp_frequencyTransfer(ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.wFreqTableID,
                                   &ptUSPUHFISO6BInventory->tInventoryRfPara.tFreqCfg.tFreqHopConfig.tfreqChannel);
        }

        if (ptTempProtocolPara->tRdpLlrpAntConfigCtrl.tRdpLlrpAirProtocolInvCtrl.tRdpLlrpISOInvCtrl.bIsDefaultCfgFlag == TRUE)
        {
            ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMask
            = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucMask;
            ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucAddress
            = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucAddress;
            ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucCommandType
            = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucCommandType;
            ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.ucMaskLen
            = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].wWordDataLen;
            memcpy(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData,
                   ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BFilter.atUSPRdpLlrpISO6BFilter[0].ucWordData,
                   sizeof(ptUSPUHFISO6BInventory->tISO6BInventoryPara.tISO6BInventoryMask.aucMaskData));
            ptUSPUHFISO6BInventory->tISO6BInventoryPara.wEstimateTag
            = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BSingulationControl.wTagPopulation;
            ptUSPUHFISO6BInventory->tISO6BInventoryPara.wModeIndex
            = ptAntConfig->tUSPRdpLlrpAirProtocolInventoryCommandSettings.tUSPRdpLlrpISO6BInventoryCommand.tUSPRdpLlrpISO6BRFControl.wModeIndex;
        }
        else
        {
            llrp_assembleISO6BInvProtocolPara( ucAntennaIndex, ptTempProtocolPara, ptUSPUHFISO6BInventory);
        }



    }
}
/**************************************************************************
* 函数名称：llrp_ISO6BMatchAccessPattern
* 功能描述：ISO6B匹配模板
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：
* 返 回 值：   LLRP_EPCMatchTAG_SUCCESS: 匹配成功；
                             LLRP_EPCMatchTAG_FAIL: 匹配失败；
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
unsigned int llrp_ISO6BMatchAccessPattern(unsigned int dwByteLen, unsigned char *pucMatchData , T_RdpLlrpISO6BTargetTag *ptMatchISO6BTargetTag)
{
    unsigned char ucTempTagDataFirstHaft = 0;
    unsigned char ucTempTagDataLastHaft = 0;
    unsigned char aucTagData[256] = {0};
    unsigned char dwTagDataIndex = 0;
    unsigned int dwIndex = 0;
    unsigned int dwTagMaskAndDataOffset = 0;
    unsigned int dwTagMaskAndDataCmpTimes = 0;
    T_RdpLlrpMatchParam *ptMatchData = NULL;
    dwTagMaskAndDataCmpTimes = dwTagMaskAndDataOffset = BIT_CHANGETO_BYTE(ptMatchISO6BTargetTag->tRdpLlrpMatchParam.wMaskBitCount);
    ptMatchData = &ptMatchISO6BTargetTag->tRdpLlrpMatchParam;
    memcpy(aucTagData, pucMatchData, dwByteLen);
    /*计算EPC的匹配的第几个字节*/
    /*这个字节的第几个bit*/
    for (dwIndex = 0; dwIndex < dwTagMaskAndDataCmpTimes; dwIndex++, dwTagDataIndex++)
    {
        RdpLlrpWarningPrint("(LLRP) ISO6B Tagdata :0x%2x,mask data:0x%2x,pattern data:0x%2x\r\n",
                            aucTagData[dwTagDataIndex], ptMatchData->aucTagData[dwIndex],
                            ptMatchData->aucTagData[dwIndex + dwTagMaskAndDataOffset]);
        /*如果是匹配这个模板 应该 标签首先按照位与匹配数据 异或
         然后在和掩码进行与操作，例如 1^0 = 1 说明数据不匹配  1&0 =0 说明不掩这位 结果为0
        1^0 =1 但是 1&1=1 说明掩这位 那么这样就不符合模板了 退出*/
        if ((ptMatchISO6BTargetTag->bMatch == TRUE) \
                && (((aucTagData[dwTagDataIndex] \
                      ^ ptMatchData->aucTagData[dwIndex + dwTagMaskAndDataOffset])\
                     & (ptMatchData->aucTagData[dwIndex])) != 0))
        {
            RdpWarningPrint("(LLRP)access match pattern is equal the byte cmp fail  ISO6B Tagdata :0x%2x,mask data:0x%2x,pattern data:0x%2x\r\n",
                            aucTagData[dwTagDataIndex], ptMatchData->aucTagData[dwIndex],
                            ptMatchData->aucTagData[dwIndex + dwTagMaskAndDataOffset]);
            RdpLlrpDbgPrint("(LLRP)match failed\r\n");
            return LLRP_ISO6BMATCHTAG_FAIL;
        }
        /*如果是不匹配这个模板 应该 标签首先按照位与匹配数据 同或
        然后在和掩码进行与操作*/
        if ((ptMatchISO6BTargetTag->bMatch == FALSE)
                && (((~(aucTagData[dwTagDataIndex] \
                        ^ ptMatchData->aucTagData[dwIndex + dwTagMaskAndDataOffset]))
                     & (ptMatchData->aucTagData[dwIndex])) != 0))
        {
            RdpWarningPrint("(LLRP)access match pattern is  not equal the byte cmp fail  ISO6B Tagdata :0x%2x,mask data:0x%2x,pattern data:0x%2x\r\n",
                            aucTagData[dwTagDataIndex], ptMatchData->aucTagData[dwIndex],
                            ptMatchData->aucTagData[dwIndex + dwTagMaskAndDataOffset]);
            return LLRP_ISO6BMATCHTAG_FAIL;
        }
    }
    return LLRP_ISO6BMATCHTAG_SUCCESS;
}

/**************************************************************************
* 函数名称：llrp_ISO6BMatchRead
* 功能描述：匹配ISO6B读操作
* 访问的表：无
* 修改的表：无
* 输入参数：T_USPUHFISO6BTagId *ptISO6BTagId,
                             标签的ISO6BTagId
                             unsigned short int wAntID,
                             天线
                             T_RdpLlrpISO6BTargetTag *ptISO6BTargetTag,
                             匹配模板
* 输出参数：T_USPUHFISO6BReadRes **ptISO6BReadRsp
                             返回结果指针
* 返 回 值：   LLRP_ACCESS_MATCH_SUCCESS: 匹配成功；
                             LLRP_ACCESS_MATCH_FAIL: 匹配失败；
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
unsigned int llrp_ISO6BMatchRead(T_USPUHFISO6BTagId *ptISO6BTagId, unsigned short int wAntID, T_RdpLlrpISO6BTargetTag *ptISO6BTargetTag, T_USPUHFISO6BReadRes **ptISO6BReadRsp)
{
    T_Msg tSyncMsg;
    T_Msg *ptSyncMsg[] = {&tSyncMsg, NULL};
    int dwRet = 0;
    unsigned int dwIndex = 0;
    unsigned int dwTestIndex = 0;
    unsigned int ucRevBuf[8192] = {0};
    T_USPUHFISO6BRead *ptISO6BRead = NULL;
    T_Msg *ptSndMsg = (T_Msg *)g_aucRdpLlrpSndMsg;
    T_Msg *ptRcvMsg = (T_Msg *)ucRevBuf;
    RdpLlrpDbgPrint("(LLRP)ptISO6BTagId->wTagDataLen :%d\r\n", ptISO6BTagId->wTagDataLen);
    ptSndMsg->mtype = 1;
    ptSndMsg->wMsgID = EV_USP_UHF_ISO6B_MATCH_READ;
    ptSndMsg->wSrcTno = USP_RDP_LLRP_TNO;
    ptSndMsg->wDstTno = USP_UHF_TNO;
    ptSndMsg->wMsgSequence = USP_LIB_SCP_MSGSEQ(g_wMsgSequence);
    ptISO6BRead = (T_USPUHFISO6BRead *)(ptSndMsg + 1);
    ptISO6BRead->dwAntIndex = wAntID;
    ptISO6BRead->tISO6BReadctl.ucCommandType = 0;
    ptISO6BRead->tISO6BReadctl.ucRetryTimes = 3;
    ptISO6BRead->ucBytePtr = ptISO6BTargetTag->wBytePtr;
    ptISO6BRead->ucByteCount = BIT_CHANGETO_BYTE(ptISO6BTargetTag->tRdpLlrpMatchParam.wMaskBitCount);
    ptISO6BRead->tTagId.wTagDataLen = ptISO6BTagId->wTagDataLen;
    memcpy(ptISO6BRead->tTagId.aucTagData, ptISO6BTagId->aucTagData, ptISO6BTagId->wTagDataLen);
    ptSndMsg->wMsgLen = sizeof(T_USPUHFISO6BRead);
    RdpLlrpDbgPrint("(LLRP)AntIndex :%d\r\n", ptISO6BRead->dwAntIndex);
    RdpLlrpDbgPrint("(LLRP)ucCommandType :%d\r\n", ptISO6BRead->tISO6BReadctl.ucCommandType);
    RdpLlrpDbgPrint("(LLRP)ucRetryTimes :%d\r\n", ptISO6BRead->tISO6BReadctl.ucRetryTimes);
    RdpLlrpDbgPrint("(LLRP)ucBytePtr :%d\r\n", ptISO6BRead->ucBytePtr);
    RdpLlrpDbgPrint("(LLRP)ucByteCount :%d\r\n", ptISO6BRead->ucByteCount);
    RdpLlrpDbgPrint("(LLRP)ISO6BId:");
    for (dwTestIndex = 0;dwTestIndex < ptISO6BRead->tTagId.wTagDataLen;dwTestIndex++)
    {
        RdpDbgPrintRaw("0x%02x ", ptISO6BRead->tTagId.aucTagData[dwTestIndex]);
    }
    RdpLlrpDbgPrint("\r\n");
    if (0 > RDP_SEND_MSG(req_socket_rcp, ptSndMsg))
    {
        /*发送失败写入异常*/
        RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return LLRP_ACCESSPATTERN_MATCHREAD_FAIL;
    }
    memset(&tSyncMsg, 0xff, sizeof(T_Msg));
    tSyncMsg.wMsgID = EV_USP_UHF_ISO6B_MATCH_READ_RES;
    tSyncMsg.wMsgSequence = g_wMsgSequence;
    dwRet = RDP_RECV_SYNC_MSG(req_socket_rcp, ptRcvMsg, RDP_MAX_LEN_MSG);
    if (dwRet < 0 )
    {
        /*写入异常*/
        RDP_EXCEPT(RDP_SEND_MESSGAE_ERROR, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return LLRP_ACCESSPATTERN_MATCHREAD_FAIL;
    }
    *ptISO6BReadRsp = (T_USPUHFISO6BReadRes *)(ptRcvMsg + 1);
    RdpLlrpDbgPrint("(LLRP)matchread wResult:%d\r\n", (*ptISO6BReadRsp)->wResult);
    if ((*ptISO6BReadRsp)->wResult != 0)
    {
        return LLRP_ACCESSPATTERN_MATCHREAD_FAIL;
    }
    return LLRP_ACCESSPATTERN_MATCHREAD_SUCCESS;

}
/**************************************************************************
* 函数名称：llrp_tagISO6BInvRsp
* 功能描述：处理Rcp的ISO6B清点返回消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：
* 返 回 值：   
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_tagISO6BInvRsp(T_Msg *ptRcvMsg)
{
    unsigned int dwRet = 0;
    T_USPUHFISO6BInventoryRes *ptTempTagISO6BInvRsp = NULL;
    T_RdpLlrpROCtrlAndParam *ptRunRoCtrlAndPara = NULL;
    T_RdpLlrpAI *ptRdpLlrpAI = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptMatchAccessCtrlAndPara = NULL;
    RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BInvRsp \r\n");
    if (g_tRdpLlrpReaderDispatch.ptReaderRoSpecData->tActiveRO.ptNext == NULL)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    if (ptRcvMsg->wMsgSequence != g_wMsgSequence)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, g_wMsgSequence, ptRcvMsg->wMsgSequence, 0, RDP_LLRP_ISO6B_ID);
        RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BInvRsp wMsgSequence error\r\n");
        return ;
    }
    /*杀定时器*/
    LLRP_STOP_TIMER(TFpgaResp);
    /*获得当前运行的AI*/
    ptRdpLlrpAI = llrp_getRunAI();
    ptTempTagISO6BInvRsp = (T_USPUHFISO6BInventoryRes *) (ptRcvMsg + 1);
    /*RO的Report不保持 根据Trigger上报*/
    if (ptTempTagISO6BInvRsp->wResult == 0)
    {
        /*正常清点到标签*/
        RdpLlrpDbgPrint("(LLRP)RCP Fpga Return success \r\n");
        if (ptTempTagISO6BInvRsp->wInventoryFinish == 0)
        {
            /*如果Trigger已经发生 退出程序 不取得以后的标签*/
            RdpLlrpDbgPrint("(LLRP)RCP Fpga  Return an Tag\r\n");
            ptRdpLlrpAI->tRdpLlrpAIStopTrigger \
            .pfusp_rdp_llrp_AccmulateForAIStopTrigger((void *)&ptRdpLlrpAI->tRdpLlrpAIStopTrigger);
            if ( ptRdpLlrpAI->tRdpLlrpAIStopTrigger \
                    .pfusp_rdp_llrp_judgeHappenForAIStopTrigger((void *)&ptRdpLlrpAI->tRdpLlrpAIStopTrigger) == TRUE )
            {
                RdpLlrpDbgPrint("(LLRP)active AI stoptrigger happen need not to save tag\r\n");
                llrp_sendNextISO6BInv();
            }
            else
            {
                /*access命令大于三次出错设定为访问错误*/

                /*匹配,成功退出，不成功构造报告*/
                dwRet = llrp_matchAccess(LLRP_AirProtocols_ISO18000_6B,
                                         ptTempTagISO6BInvRsp->wAntennaIndex,
                                         &ptTempTagISO6BInvRsp->tTagId);
                if ( dwRet == LLRP_ACCESS_MATCH_FAIL )
                {
                    /*构造报告*/
                    RdpLlrpDbgPrint("(LLRP)match Access fail,need to build an Ro Report and insert active Ro report link,len=%d\r\n", ptTempTagISO6BInvRsp->tTagId.wTagDataLen);
                    llrp_constructLocalROReport(LLRP_AirProtocols_ISO18000_6B,
                                                ptTempTagISO6BInvRsp->wAntennaIndex,
                                                ptTempTagISO6BInvRsp->wRssi,
                                                LLRP_DEFAULT_REPORT_WORD16,
                                                LLRP_DEFAULT_REPORT_WORD16,
                                                ptTempTagISO6BInvRsp->wChannelIndex,
                                                ptTempTagISO6BInvRsp->tTagId.wTagDataLen,
                                                ptTempTagISO6BInvRsp->tTagId.aucTagData);
                    ptRunRoCtrlAndPara = llrp_getRunRO();
                    if (ptRunRoCtrlAndPara == NULL)
                    {
                        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
                        return ;
                    }
                    /*增加报告积累后判断报告是否上报*/
                    ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport \
                    .pfusp_rdp_llrp_JudgeReportNumForReportTrigger((void *)&ptRunRoCtrlAndPara->tRdpLlrpROSpec.tRdpLlrpROReport);
                    llrp_sendNextISO6BInv();
                }
                else
                {
                    RdpLlrpDbgPrint("(LLRP)match Access success,inventory over begin do Access Op\r\n");
                    ptMatchAccessCtrlAndPara = llrp_getRunAccess();
                    if (ptMatchAccessCtrlAndPara == NULL)
                    {
                        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
                        return ;
                    }
                    ptMatchAccessCtrlAndPara->tRdpLlrpAccessDispatchCtrl.dwDispatchStatus = LLRP_ACCESSDISPATCH_STATE_ACTIVE;
                    /*初始化Ao的stoptrigger */
                    ptMatchAccessCtrlAndPara->tRdpLlrpAccess.tRdpLlrpAccessStopTrigger \
                    .pfusp_rdp_llrp_initAOStopTrigger(ptMatchAccessCtrlAndPara);
                    /*保存匹配的标签*/
                    ptMatchAccessCtrlAndPara->tMatchUID.wTagDataLen = ptTempTagISO6BInvRsp->tTagId.wTagDataLen;
                    memcpy(ptMatchAccessCtrlAndPara->tMatchUID.aucTagData,
                           ptTempTagISO6BInvRsp->tTagId.aucTagData, ptMatchAccessCtrlAndPara->tMatchUID.wTagDataLen);
                    /*下发指令*/
                    llrp_nextTagAccessOp(&ptMatchAccessCtrlAndPara->tRdpLlrpAccess.tRdpLlrpAccessCmdCtrl.tRdpLlrpListOPCtrlSet,
                                         LLRP_AirProtocols_ISO18000_6B, &ptMatchAccessCtrlAndPara->tMatchUID);
                }
            }
        }
        /*结束清点*/
        else
        {
            RdpLlrpDbgPrint("(LLRP)RCP Fpga  Return ISO6B finish frame \r\n");
            /*响应响应的结束条件然后完成Ro,AI,AP的调度*/
            llrp_dispatchTagInv();
        } /*结束清点完*/
    }
    /*失败结束这次清点进行下一个次*/
    else
    {
        RdpLlrpDbgPrint("(LLRP)RCP Fpga Return epc failed frame\r\n");
        if (ptTempTagISO6BInvRsp->wInventoryFinish == 0)
        {
            RdpLlrpDbgPrint("(LLRP)Rcp Fpga return ISO6B failed and need to  continue epc inventory \r\n");
            llrp_sendNextISO6BInv();
        }
        else
        {
            RdpLlrpDbgPrint("(LLRP)Rcp Fpga return ISO6B failed and need to continue a big epc inventory \r\n");
            llrp_dispatchTagInv();
        }
    }
    /*RO的Report保持 知道*/
}
/**************************************************************************
* 函数名称：llrp_refreshISO6BReadOpResult
* 功能描述：更新ISO6B的读结果
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
static void llrp_refreshISO6BReadOpResult(T_USPUHFISO6BReadRes *ptRcpISO6BReadRes)
{
    unsigned int dwTestIndex = 0;
    unsigned int dwOpCtrlIndex = 0;
    unsigned int dwOpResultAddr = 0;
    T_RdpLlrpSingleReportCtrl *ptRunSingleReportCtrl = NULL;
    T_RdpLlrpAccessTagReport *ptAccessTagReport = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunListOpSet = NULL;
    T_USPUHFISO6BRead*ptISO6BReadOp = NULL;
    T_RdpLlrpISO6BReadOpResult *ptISO6BReadOpResult = NULL;
    if (ptRcpISO6BReadRes->wResultLength > 1024)
    {
        ptRcpISO6BReadRes->wResultLength = 200;
        RDP_EXCEPT(RDP_INVALID_STATE, ptRcpISO6BReadRes->wResultLength, 0, 0, RDP_LLRP_ISO6B_ID);
        RdpLlrpDbgPrint("(LLRP)iso read return an error len ptRcpISO6BReadRes->wResultLength=%d\r\n", ptRcpISO6BReadRes->wResultLength);
    }
    ptRunSingleReportCtrl = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    ptAccessTagReport = &ptRunSingleReportCtrl->tRdpLlrpTagReport.tAccessTagReport;
    ptRunListOpSet = llrp_getRunListOpSet();
    if (ptRunListOpSet == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    dwOpResultAddr = ptAccessTagReport->tID.tISOID.wTagDataLen - sizeof(unsigned short int);
    if (ptAccessTagReport->dwOpNum > 0)
    {
        dwOpResultAddr = ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultAddr
                         + ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultlen;
    }
    ptAccessTagReport->dwOpNum++;
    dwOpCtrlIndex = ptAccessTagReport->dwOpNum - 1;
    ptISO6BReadOp = (T_USPUHFISO6BRead *) & ptRunListOpSet->tSingleOp[ptRunListOpSet->wOpIndex];
    ptISO6BReadOpResult = (T_RdpLlrpISO6BReadOpResult *) & ptAccessTagReport->aucData[dwOpResultAddr];

    ptISO6BReadOpResult->wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptISO6BReadOpResult->ucResult = ptRcpISO6BReadRes->wResult;
    ptISO6BReadOpResult->wDataLength = ptRcpISO6BReadRes->wResultLength;
    memcpy(ptISO6BReadOpResult->aucData, ptRcpISO6BReadRes->aucReadData, ptRcpISO6BReadRes->wResultLength);
    /*取得ISO6B读操作指令*/
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wResult = ptRcpISO6BReadRes->wResult;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalLen = ptISO6BReadOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalAddr = ptISO6BReadOp->ucBytePtr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultAddr = dwOpResultAddr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen
    = struct_fixed_len(T_RdpLlrpISO6BReadOpResult, aucData) + ptISO6BReadOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpType = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpType;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptRunSingleReportCtrl->wMsgLen += ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen;
    RdpLlrpDbgPrint("(LLRP)ISO6B Read Rsp result:\r\n");
    RdpLlrpDbgPrint("(LLRP)OpSpecID: %d\r\n", ptISO6BReadOpResult->wOpSpecID);
    RdpLlrpDbgPrint("(LLRP)Result: %d\r\n", ptISO6BReadOpResult->ucResult);
    RdpLlrpDbgPrint("(LLRP)DataLength: %d\r\n", ptISO6BReadOpResult->wDataLength);
    RdpLlrpDbgPrint("(LLRP)ISO6B read data:");
    for (dwTestIndex = 0 ;dwTestIndex < ptISO6BReadOpResult->wDataLength;dwTestIndex++)
    {
        RdpDbgPrintRaw("0x%2x ", ptISO6BReadOpResult->aucData[dwTestIndex]);
    }
    RdpLlrpDbgPrint("\r\n");
    if (ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpType == LLRP_ISO6BReadCustomUID)
    {
        RdpLlrpDbgPrint("(LLRP)read customer uid need cpy read Result to UID area\r\n");
        if (ptISO6BReadOpResult->ucResult == 0)
        {
            ptRunSingleReportCtrl->tUID.wTagDataLen = ptISO6BReadOpResult->wDataLength;
            memcpy(ptRunSingleReportCtrl->tUID.aucTagData, ptISO6BReadOpResult->aucData, ptISO6BReadOpResult->wDataLength);
        }
        else
        {
            ptRunSingleReportCtrl->tUID.wTagDataLen = 0;
        }
    }
}
/**************************************************************************
* 函数名称：llrp_tagISO6BReadRsp
* 功能描述：处理Rcp的读返回
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：
* 返 回 值：   
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_tagISO6BReadRsp(T_Msg *ptRcvMsg)
{
    T_RdpLlrpISO6BReadOpResult *ptISO6BReadOpResult = NULL;
    unsigned int dwOpReportIndex = 0;
    T_USPUHFISO6BReadRes *ptISO6B_ReadResponse = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunLsitOpSet = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptRunAccess = NULL;
    /*是第一个操作*/
    RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BReadRsp\r\n");
    /* 异常操作怎么操作再议*/
    if (ptRcvMsg->wMsgSequence != g_wMsgSequence)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, g_wMsgSequence, ptRcvMsg->wMsgSequence, 0, RDP_LLRP_ISO6B_ID);
        RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BReadRsp wMsgSequence error\r\n");
        return ;
    }
    LLRP_STOP_TIMER(TFpgaReadResp);
    ptRunAccess = llrp_getRunAccess();
    if (ptRunAccess == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    ptRunLsitOpSet = llrp_getRunListOpSet();
    ptISO6B_ReadResponse = (T_USPUHFISO6BReadRes*)(ptRcvMsg + 1);
    if (ptRunLsitOpSet->wOpIndex == 0)
    {
        /*利用缓冲构建报告*/
        /*构建相关的和ro类似的内容*/
        RdpLlrpDbgPrint("(LLRP)first Opindex need construct AoReport head\r\n");
        llrp_constructLocalAOReportHead(LLRP_AirProtocols_ISO18000_6B,
                                        ptISO6B_ReadResponse->wAntennaIndex,
                                        ptISO6B_ReadResponse->wRssi,
                                        0xffff,
                                        0xffff,
                                        ptISO6B_ReadResponse->wChannelIndex,
                                        ptRunAccess->tMatchUID.wTagDataLen,
                                        ptRunAccess->tMatchUID.aucTagData);

        llrp_refreshISO6BReadOpResult(ptISO6B_ReadResponse);
    }
    /*不是第一个操作操作，更新操作结果 */
    else
    {
        llrp_refreshISO6BReadOpResult(ptISO6B_ReadResponse);
    }
    ptRunLsitOpSet->wOpIndex++;
    llrp_dispatchTagAccess();
}
/**************************************************************************
* 函数名称：llrp_refreshISO6BWriteOpResult
* 功能描述：更新ISO6B的写结果
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
static void llrp_refreshISO6BWriteOpResult(T_USPUHFISO6BWriteRes *ptRcpISO6BWriteRes)
{
    unsigned int dwTestIndex = 0;
    unsigned int dwOpCtrlIndex = 0;
    unsigned int dwOpResultAddr = 0;
    T_RdpLlrpSingleReportCtrl *ptRunSingleReportCtrl = NULL;
    T_RdpLlrpAccessTagReport *ptAccessTagReport = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunListOpSet = NULL;
    T_USPUHFISO6BWrite*ptISO6BWriteOp = NULL;
    T_RdpLlrpISO6BWriteOpResult *ptISO6BWriteOpResult = NULL;
    ptRunSingleReportCtrl = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    ptAccessTagReport = &ptRunSingleReportCtrl->tRdpLlrpTagReport.tAccessTagReport;
    ptRunListOpSet = llrp_getRunListOpSet();
    if (ptRunListOpSet == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    dwOpResultAddr = ptAccessTagReport->tID.tISOID.wTagDataLen - sizeof(unsigned short int);
    if (ptAccessTagReport->dwOpNum > 0)
    {
        dwOpResultAddr = ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultAddr
                         + ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultlen;
    }
    ptAccessTagReport->dwOpNum++;
    dwOpCtrlIndex = ptAccessTagReport->dwOpNum - 1;
    ptISO6BWriteOp = (T_USPUHFISO6BWrite *) & ptRunListOpSet->tSingleOp[ptRunListOpSet->wOpIndex];
    // RdpLlrpDbgPrint("(LLRP)llrp_refreshISO6BWriteOpResult dwOpResultAddr=%d,dwOpNum=%d\r\n",dwOpResultAddr,ptAccessTagReport->dwOpNum);
    ptISO6BWriteOpResult = (T_RdpLlrpISO6BWriteOpResult *) & ptAccessTagReport->aucData[dwOpResultAddr];

    ptISO6BWriteOpResult->wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptISO6BWriteOpResult->ucResult = ptRcpISO6BWriteRes->wResult;
    ptISO6BWriteOpResult->wNumWordsWritten = ptRcpISO6BWriteRes->wResultLength;
    /*取得ISO6B读操作指令*/
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wResult = ptRcpISO6BWriteRes->wResult;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalLen = ptISO6BWriteOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalAddr = ptISO6BWriteOp->ucBytePtr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultAddr = dwOpResultAddr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen = sizeof(T_RdpLlrpISO6BWriteOpResult) ;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpType = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpType;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptRunSingleReportCtrl->wMsgLen += ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen;
    RdpLlrpDbgPrint("(LLRP)ISO6B Write Rsp result: \r\n");
    RdpLlrpDbgPrint("(LLRP)OpSpecID: %d\r\n", ptISO6BWriteOpResult->wOpSpecID);
    RdpLlrpDbgPrint("(LLRP)Result: %d\r\n", ptISO6BWriteOpResult->ucResult);
    RdpLlrpDbgPrint("(LLRP)NumWordsWritten: %d\r\n", ptISO6BWriteOpResult->wNumWordsWritten);
    /*读结果*/
}
/**************************************************************************
* 函数名称：llrp_tagISO6BWriteRsp
* 功能描述：处理Rcp的写返回
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：
* 返 回 值：   
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_tagISO6BWriteRsp(T_Msg *ptRcvMsg)
{
    T_RdpLlrpISO6BWriteOpResult *ptISO6BWriteOpResult = NULL;
    unsigned int dwOpReportIndex = 0;
    T_USPUHFISO6BWriteRes *ptISO6B_WriteResponse = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunLsitOpSet = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptRunAccess = NULL;
    /*是第一个操作*/
    RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BWriteRsp\r\n");
    /* 异常操作怎么操作再议
    if ( RDP_FAILED == Check_ActiveAOSpecParameter(&g_tWriteerRDPProc.tMatchAccessCtrl) )
    {
        RDP_EXCEPT(RDP_AO_DOOP_STATE_ERROR,
                   g_tWriteerRDPProc.tMatchAccessCtrl.ucAccessIndex,
                   g_tWriteerRDPProc.tMatchAccessCtrl.ucOpIndex,
                   0,
                   RDP_FILED_ID);
        return RDP_FAILED;
    }
    */
    if (ptRcvMsg->wMsgSequence != g_wMsgSequence)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, g_wMsgSequence, ptRcvMsg->wMsgSequence, 0, RDP_LLRP_ISO6B_ID);
        RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BWriteRsp wMsgSequence error\r\n");
        return ;
    }
    LLRP_STOP_TIMER(TFpgaWriteResp);
    ptRunAccess = llrp_getRunAccess();
    if (ptRunAccess == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    ptRunLsitOpSet = llrp_getRunListOpSet();
    ptISO6B_WriteResponse = (T_USPUHFISO6BWriteRes*)(ptRcvMsg + 1);
    if (ptRunLsitOpSet->wOpIndex == 0)
    {
        /*利用缓冲构建报告*/
        /*构建相关的和ro类似的内容*/
        RdpLlrpDbgPrint("(LLRP)first Opindex need construct AoReport head\r\n");
        llrp_constructLocalAOReportHead(LLRP_AirProtocols_ISO18000_6B,
                                        ptISO6B_WriteResponse->wAntennaIndex,
                                        ptISO6B_WriteResponse->wRssi,
                                        0xffff,
                                        0xffff,
                                        ptISO6B_WriteResponse->wChannelIndex,
                                        ptRunAccess->tMatchUID.wTagDataLen,
                                        ptRunAccess->tMatchUID.aucTagData);

        llrp_refreshISO6BWriteOpResult(ptISO6B_WriteResponse);
    }
    /*不是第一个操作操作，更新操作结果 */
    else
    {
        llrp_refreshISO6BWriteOpResult(ptISO6B_WriteResponse);
    }
    ptRunLsitOpSet->wOpIndex++;
    llrp_dispatchTagAccess();
}
/**************************************************************************
* 函数名称：llrp_refreshISO6BLockOpResult
* 功能描述：更新ISO6B的写结果
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
static void llrp_refreshISO6BLockOpResult(T_USPUHFISO6BLockRes *ptRcpISO6BLockRes)
{
    unsigned int dwTestIndex = 0;
    unsigned int dwOpCtrlIndex = 0;
    unsigned int dwOpResultAddr = 0;
    T_RdpLlrpSingleReportCtrl *ptRunSingleReportCtrl = NULL;
    T_RdpLlrpAccessTagReport *ptAccessTagReport = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunListOpSet = NULL;
    T_USPUHFISO6BLock*ptISO6BLockOp = NULL;
    T_RdpLlrpISO6BLockOpResult *ptISO6BLockOpResult = NULL;
    ptRunSingleReportCtrl = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    ptAccessTagReport = &ptRunSingleReportCtrl->tRdpLlrpTagReport.tAccessTagReport;
    ptRunListOpSet = llrp_getRunListOpSet();
    if (ptRunListOpSet == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    dwOpResultAddr = ptAccessTagReport->tID.tISOID.wTagDataLen - sizeof(unsigned short int);
    if (ptAccessTagReport->dwOpNum > 0)
    {
        dwOpResultAddr = ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultAddr
                         + ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultlen;
    }
    ptAccessTagReport->dwOpNum++;
    dwOpCtrlIndex = ptAccessTagReport->dwOpNum - 1;
    ptISO6BLockOp = (T_USPUHFISO6BLock *) & ptRunListOpSet->tSingleOp[ptRunListOpSet->wOpIndex];
    ptISO6BLockOpResult = (T_RdpLlrpISO6BLockOpResult *) & ptAccessTagReport->aucData[dwOpResultAddr];
    ptISO6BLockOpResult->wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptISO6BLockOpResult->ucResult = ptRcpISO6BLockRes->wResult;
    ptISO6BLockOpResult->wDataLength = ptRcpISO6BLockRes->wResultLength;
    memcpy(ptISO6BLockOpResult->aucData, ptRcpISO6BLockRes->aucLockData, ptISO6BLockOpResult->wDataLength);
    /*取得ISO6B读操作指令*/
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wResult = ptRcpISO6BLockRes->wResult;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalLen = ptISO6BLockOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalAddr = ptISO6BLockOp->ucBytePtr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultAddr = dwOpResultAddr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen = struct_fixed_len(T_RdpLlrpISO6BLockOpResult, aucData) + ptISO6BLockOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpType = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpType;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptRunSingleReportCtrl->wMsgLen += ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen;
    RdpLlrpDbgPrint("(LLRP)ISO6B Lock Rsp result:\r\n");
    RdpLlrpDbgPrint("(LLRP)OpSpecID: %d\r\n", ptISO6BLockOpResult->wOpSpecID);
    RdpLlrpDbgPrint("(LLRP)Result: %d\r\n", ptISO6BLockOpResult->ucResult);
    RdpLlrpDbgPrint("(LLRP)DataLength: %d\r\n", ptISO6BLockOpResult->wDataLength);
    RdpLlrpDbgPrint("(LLRP)ISO6B lock data:");
    for (dwTestIndex = 0 ;dwTestIndex < ptISO6BLockOpResult->wDataLength;dwTestIndex++)
    {
        RdpDbgPrintRaw("0x%x2x ", ptISO6BLockOpResult->aucData[dwTestIndex]);
    }
    RdpLlrpDbgPrint("\r\n");
    /*读结果*/
}
/**************************************************************************
* 函数名称：llrp_tagISO6BLockRsp
* 功能描述：处理Rcp的写返回
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：
* 返 回 值：   
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_tagISO6BLockRsp(T_Msg *ptRcvMsg)
{
    T_RdpLlrpISO6BLockOpResult *ptISO6BLockOpResult = NULL;
    unsigned int dwOpReportIndex = 0;
    T_USPUHFISO6BLockRes *ptISO6B_LockResponse = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunLsitOpSet = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptRunAccess = NULL;
    /*是第一个操作*/
    RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BLockRsp\r\n");
    /* 异常操作怎么操作再议*/
    if (ptRcvMsg->wMsgSequence != g_wMsgSequence)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, g_wMsgSequence, ptRcvMsg->wMsgSequence, 0, RDP_LLRP_ISO6B_ID);
        RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BLockRsp wMsgSequence error\r\n");
        return ;
    }
    LLRP_STOP_TIMER(TFpgaLockResp);
    ptRunAccess = llrp_getRunAccess();
    if (ptRunAccess == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    ptRunLsitOpSet = llrp_getRunListOpSet();
    ptISO6B_LockResponse = (T_USPUHFISO6BLockRes*)(ptRcvMsg + 1);
    if (ptRunLsitOpSet->wOpIndex == 0)
    {
        /*利用缓冲构建报告*/
        /*构建相关的和ro类似的内容*/
        RdpLlrpDbgPrint("(LLRP)first Opindex need construct AoReport head\r\n");
        llrp_constructLocalAOReportHead(LLRP_AirProtocols_ISO18000_6B,
                                        ptISO6B_LockResponse->wAntennaIndex,
                                        ptISO6B_LockResponse->wRssi,
                                        0xffff,
                                        0xffff,
                                        ptISO6B_LockResponse->wChannelIndex,
                                        ptRunAccess->tMatchUID.wTagDataLen,
                                        ptRunAccess->tMatchUID.aucTagData);

        llrp_refreshISO6BLockOpResult(ptISO6B_LockResponse);
    }
    /*不是第一个操作操作，更新操作结果 */
    else
    {
        llrp_refreshISO6BLockOpResult(ptISO6B_LockResponse);
    }
    ptRunLsitOpSet->wOpIndex++;
    llrp_dispatchTagAccess();
}
/**************************************************************************
* 函数名称：llrp_refreshISO6BLockQueryOpResult
* 功能描述：更新ISO6B的写结果
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
static void llrp_refreshISO6BLockQueryOpResult(T_USPUHFISO6BLockQueryRes *ptRcpISO6BLockQueryRes)
{
    unsigned int dwTestIndex = 0;
    unsigned int dwOpCtrlIndex = 0;
    unsigned int dwOpResultAddr = 0;
    T_RdpLlrpSingleReportCtrl *ptRunSingleReportCtrl = NULL;
    T_RdpLlrpAccessTagReport *ptAccessTagReport = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunListOpSet = NULL;
    T_USPUHFISO6BLockQuery*ptISO6BLockQueryOp = NULL;
    T_RdpLlrpISO6BLockQueryOpResult *ptISO6BLockQueryOpResult = NULL;
    ptRunSingleReportCtrl = (T_RdpLlrpSingleReportCtrl *)g_ucLocalReportDataBuffer;
    ptAccessTagReport = &ptRunSingleReportCtrl->tRdpLlrpTagReport.tAccessTagReport;
    ptRunListOpSet = llrp_getRunListOpSet();
    if (ptRunListOpSet == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    dwOpResultAddr = ptAccessTagReport->tID.tISOID.wTagDataLen - sizeof(unsigned short int);
    if (ptAccessTagReport->dwOpNum > 0)
    {
        dwOpResultAddr = ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultAddr
                         + ptAccessTagReport->tListofOpResultCtrl[ptAccessTagReport->dwOpNum - 1].wOpResultlen;
    }
    ptAccessTagReport->dwOpNum++;
    dwOpCtrlIndex = ptAccessTagReport->dwOpNum - 1;
    ptISO6BLockQueryOp = (T_USPUHFISO6BLockQuery *) & ptRunListOpSet->tSingleOp[ptRunListOpSet->wOpIndex];
    ptISO6BLockQueryOpResult = (T_RdpLlrpISO6BLockQueryOpResult *) & ptAccessTagReport->aucData[dwOpResultAddr];

    ptISO6BLockQueryOpResult->wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptISO6BLockQueryOpResult->wDataLength = ptRcpISO6BLockQueryRes->wResultLength;
    memcpy(ptISO6BLockQueryOpResult->aucData, ptRcpISO6BLockQueryRes->aucLockQueryData, ptISO6BLockQueryOpResult->wDataLength);
    /*取得ISO6B读操作指令*/
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wResult = ptRcpISO6BLockQueryRes->wResult;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalLen = ptISO6BLockQueryOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpOriginalAddr = ptISO6BLockQueryOp->ucBytePtr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultAddr = dwOpResultAddr;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen = struct_fixed_len(T_RdpLlrpISO6BLockQueryOpResult, aucData) + ptISO6BLockQueryOp->ucByteCount;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpType = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpType;
    ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpSpecID = ptRunListOpSet->tRdpLlrpOPCtr[ptRunListOpSet->wOpIndex].wOpID;
    ptRunSingleReportCtrl->wMsgLen += ptAccessTagReport->tListofOpResultCtrl[dwOpCtrlIndex].wOpResultlen;
    RdpLlrpDbgPrint("(LLRP)ISO6B LockQuery Rsp result:\r\n");
    RdpLlrpDbgPrint("(LLRP)OpSpecID: %d\r\n", ptISO6BLockQueryOpResult->wOpSpecID);
    RdpLlrpDbgPrint("(LLRP)DataLength: %d\r\n", ptISO6BLockQueryOpResult->wDataLength);
    RdpLlrpDbgPrint("(LLRP)ISO6B lock data:");
    for (dwTestIndex = 0 ;dwTestIndex < ptISO6BLockQueryOpResult->wDataLength;dwTestIndex++)
    {
        RdpDbgPrintRaw("0x%x2x ", ptISO6BLockQueryOpResult->aucData[dwTestIndex]);
    }
    RdpLlrpDbgPrint("\r\n");
    /*读结果*/
}
/**************************************************************************
* 函数名称：llrp_tagISO6BLockQueryRsp
* 功能描述：处理Rcp的锁查询返回
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRcvMsg
* 输出参数：
* 返 回 值：   
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 2012/02/24    V1.0       程亮        创建
*****************************************************************************/
void llrp_tagISO6BLockQueryRsp(T_Msg *ptRcvMsg)
{
    T_RdpLlrpISO6BLockQueryOpResult *ptISO6BLockQueryOpResult = NULL;
    unsigned int dwOpReportIndex = 0;
    T_USPUHFISO6BLockQueryRes *ptISO6B_LockQueryResponse = NULL;
    T_RdpLlrpListOPCtrlSet *ptRunLsitOpSet = NULL;
    T_RdpLlrpAccessCtrlAndParam *ptRunAccess = NULL;
    /*是第一个操作*/
    RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BLockQueryRsp\r\n");
    /* 异常操作怎么操作再议*/
    if (ptRcvMsg->wMsgSequence != g_wMsgSequence)
    {
        /*写入异常恢复状态机*/
        RDP_EXCEPT(RDP_RO_STATE_ERROR, g_wMsgSequence, ptRcvMsg->wMsgSequence, 0, RDP_LLRP_ISO6B_ID);
        RdpLlrpDbgPrint("(LLRP)llrp_tagISO6BLockQueryRsp wMsgSequence error\r\n");
        return ;
    }
     LLRP_STOP_TIMER(TFpgaLockResp);
    ptRunAccess = llrp_getRunAccess();
    if (ptRunAccess == NULL)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, 0, 0, 0, RDP_LLRP_ISO6B_ID);
        return ;
    }
    ptRunLsitOpSet = llrp_getRunListOpSet();
    ptISO6B_LockQueryResponse = (T_USPUHFISO6BLockQueryRes*)(ptRcvMsg + 1);
    if (ptRunLsitOpSet->wOpIndex == 0)
    {
        /*利用缓冲构建报告*/
        /*构建相关的和ro类似的内容*/
        RdpLlrpDbgPrint("(LLRP)first Opindex need construct AoReport head\r\n");
        llrp_constructLocalAOReportHead(LLRP_AirProtocols_ISO18000_6B,
                                        ptISO6B_LockQueryResponse->wAntennaIndex,
                                        ptISO6B_LockQueryResponse->wRssi,
                                        0xffff,
                                        0xffff,
                                        ptISO6B_LockQueryResponse->wChannelIndex,
                                        ptRunAccess->tMatchUID.wTagDataLen,
                                        ptRunAccess->tMatchUID.aucTagData);

        llrp_refreshISO6BLockQueryOpResult(ptISO6B_LockQueryResponse);
    }
    /*不是第一个操作操作，更新操作结果 */
    else
    {
        llrp_refreshISO6BLockQueryOpResult(ptISO6B_LockQueryResponse);
    }
    ptRunLsitOpSet->wOpIndex++;
    llrp_dispatchTagAccess();
}
