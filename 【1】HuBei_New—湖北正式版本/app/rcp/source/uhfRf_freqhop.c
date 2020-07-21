/***************************************************************************
* 版权所有 (C)2009, 深圳市中兴通讯股份有限公司。
*
* 文件名称：uhfrf_freqhop.c
* 文件标识：
* 内容摘要：6700频率控制功能的实现
* 其它说明：
* 当前版本：
* 作    者：赵董兴
* 完成日期：2012.3.20
*
* 修改记录1：
*    修改日期：2012.3.20
*    版 本 号： RUP
*    修 改 人：
*    修改内容：将跳频的功能全部放到此文件中，并增加
                                    在同一个天线下不同协议时跳频表分开的功能
**********************************************************************/
#include "usp.h"
#include "common.h"
#if UHF_PROTOCOL_USE &&(UHF_BOARD_TYPE !=BOARD_TYPE_RBCB1)
#include "uhf_dbg.h"
#include "Board.h"
#include "RfCtl.h"
#include "uhf_rf.h"
//#include "uhf_time.h"



const T_USPUHFFreqTableEntry g_FreqTable800M[] = HOPTABLE800M;
const T_USPUHFFreqTableEntry g_FreqTable900M[] = HOPTABLE900M;
const T_USPUHFFreqTableEntry g_FreqTable800900M[] = HOPTABLE800900M;
static T_USPUHFFreqTableEntry *g_ptUHFFreqTable;     /*设备的跳频表800M 900M设备不同*/

T_UhfRfAntFreqHopCtrl g_tFreqHopCtrl[READER_ANTENNA_COUNT + 1];

extern T_RfCtrl g_tRfCtrl;

static WORD32 SelectFreqPoint(WORD16 wAntIndex , T_UhfRfFreqHopCtrl *ptFreqHopCtrl);

/**************************************************************************
* 函数名称：FreqHopInit
* 功能描述：跳频控制变量初始化
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：  无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 11/11/23    RUP      赵董兴        创建
**************************************************************************/

void uhfRf_FreqHopInit(void)
{
    WORD32 dwChannelNoIndex = 0;
    WORD16 wAntHopIndex     = 0;      /*各根天线的跳频配置初始化*/
    WORD16 wIndex = 0;
	DEBUG_MSG("uhfRf_FreqHopInit start\n");
	fflush(stdout);

    if (g_tRfCtrl.wFreqType == PLL_TYPE_800M)   /*800M 设备支持一个中国800标准的跳频表*/
    {
        g_ptUHFFreqTable = (T_USPUHFFreqTableEntry *) & g_FreqTable800M[0];
    }
    else if (PLL_TYPE_900M == g_tRfCtrl.wFreqType)
    {
        g_ptUHFFreqTable = (T_USPUHFFreqTableEntry *) & g_FreqTable900M[0];
    }
    else
    {
        /*800 900M合一的牛机型*/
        g_ptUHFFreqTable = (T_USPUHFFreqTableEntry *) &g_FreqTable800900M[0];
    }

    /*此处的初始化将所有天线协议的工作模式设置
          为定频0号频点，0号频率id*/
    memset(&g_tFreqHopCtrl[0], 0x0,
           (READER_ANTENNA_COUNT + 1)*sizeof(T_UhfRfAntFreqHopCtrl));

    for(wIndex =0;wIndex <= READER_ANTENNA_COUNT;wIndex++)
    {
      /*初始化为中心频点*/
       g_tFreqHopCtrl[wIndex].tEpcFreqHopCtrl.wFixFreqChannel =10;
       g_tFreqHopCtrl[wIndex].tEpcFreqHopCtrl.wWorkChannel =10;
       g_tFreqHopCtrl[wIndex].tIso6BFreqHopCtrl.wFixFreqChannel =10;
       g_tFreqHopCtrl[wIndex].tIso6BFreqHopCtrl.wWorkChannel = 10;
       g_tFreqHopCtrl[wIndex].tGBFreqHopCtrl.wFixFreqChannel =10;
       g_tFreqHopCtrl[wIndex].tGBFreqHopCtrl.wWorkChannel = 10;
    }
    g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(10, 0);  /*初始化为跳频表0频道号为0的频率*/
   
   DEBUG_MSG("uhfRf_FreqHopInit 1\n");
   fflush(stdout);

    /* 上电后第一次配置PLL */
    usp_uhf_rf_setPLLFreq(g_tRfCtrl.dwWorkFreq);


}

/**************************************************************************
* 函数名称：uhfRf_checkLBTStatus
* 功能描述：检测LBT的状态，目前没有采用
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：  无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 11/11/23    RUP      赵董兴        创建
**************************************************************************/
WORD32 uhfRf_checkLBTStatus(void)
{
    WORD32 dwRetVal = LBT_STATUS_IDLE;

    return (dwRetVal);
}

/**********************************************************************
* 函数名称：  WORD16 uhfRf_FreqHopCtrl(void)
* 功能描述：  通过设置PLL锁相环的参数，使阅读器实现跳频方式工作?* 输入参数：  无
* 输出参数：  无
* 返 回 值：     0 正确 其他 错误
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*2010/12/5        V4.0.0   zdx     优化流程
***********************************************************************/
WORD16 uhfRf_FreqHopCtrl(WORD16 wAntIndex, WORD16 wProtoType)
{
    WORD32 dwIndex;
    WORD32 dwRetVal;
    WORD32 wMsHopInterval = 0;
    struct timeval tCurrentTime;
    T_UhfRfFreqHopCtrl *ptMemFreqHopCtrl = NULL;

    if (UHF_RF_PROTOCOL_EPC == wProtoType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl;

    }
    else if (UHF_RF_PROTOCOL_GB == wProtoType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl;
    }
    else
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl;
    }

    if (ptMemFreqHopCtrl->wFreqWorkType == FIXED_FREQ)
    {
        /* 不需要重配置PLL */
        ptMemFreqHopCtrl->wWorkChannel = ptMemFreqHopCtrl->wFixFreqChannel;
        g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(
                                   ptMemFreqHopCtrl->wWorkChannel,
                                   ptMemFreqHopCtrl->wFreqTableID);

    }
    else
    {
#ifdef SUPPORT_HOP_FREQ
        GetCurrUsTime(&tCurrentTime);
        wMsHopInterval = CalMsTimeInterval(&ptMemFreqHopCtrl->tHopClock, &tCurrentTime);
        uhfRfDevPrint("Hoptimer scope is %d the timeinterval in ms is %d\r\n",
                      ptMemFreqHopCtrl->wHopTimer * 10, wMsHopInterval);

        if (wMsHopInterval > (ptMemFreqHopCtrl->wHopTimer) * 10)   /*后台下发的跳频间隔以10MS为单位*/
        {
            GetCurrUsTime(&ptMemFreqHopCtrl->tHopClock);
            uhfRfDevPrint("Freq hop happens\r\n");
            /* 获取当前天线的LBT配置 */
            ptMemFreqHopCtrl->dwLbtEnable
            = g_tRfCtrl.atRfAntCfg[wAntIndex].ucAntennaLBT;

            if (0 == ptMemFreqHopCtrl->dwLbtEnable)
            {
                /* LBT功能关闭 */
                /*  选择一个频点 */
                SelectFreqPoint(wAntIndex, ptMemFreqHopCtrl);
            }
            else
            {
                /* LBT功能打开 */
                for (dwIndex = 0; dwIndex < ptMemFreqHopCtrl->dwMaxLbtCheckTimes; dwIndex++)
                {
                    /*  选择一个频点 */
                    SelectFreqPoint(wAntIndex, ptMemFreqHopCtrl);

                    /* 检测该频点的状态 */
                    dwRetVal = uhfRf_checkLBTStatus();

                    if (LBT_STATUS_IDLE == dwRetVal)
                    {
                        /* 频点空闲,可用 */
                        break;
                    }
                }
            }
        }             /*达到了跳频间隔，进行跳频*/
        else
        {
            g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(
                                       ptMemFreqHopCtrl->wWorkChannel,
                                       ptMemFreqHopCtrl->wFreqTableID);
            uhfRfDevPrint("No need to hop \r\n");
        } /*没有达到跳频时刻，直接返回*/

#endif
    }

    return USP_SUCCESS;

} /* WORD16 uhfRf_FreqHopCtrl(void) */

/**********************************************************************
* 函数名称：T_USPUHFRfFreqCfg
* 功能描述： 确定当前的射频配置是否改变
* 输入参数： ptFreqCfg 要配置的射频参数
                                  wAntIndex  天线号
                                  wProtocolType 协议类型
* 输出参数： 无
* 返 回 值：      0 相同 1改变
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010\11\23               zdx                          创建
* 2012\3\20                zdx         根据但天线多协议频率控制修改
***********************************************************************/
WORD16 IsFreqCfgChanged(T_USPUHFRfFreqCfg *ptFreqCfg, WORD16 wAntIndex,
                        WORD16 wProtocolType)
{
    T_UhfRfFreqHopCtrl *ptMemFreqHopCtrl = NULL;

    if (UHF_RF_PROTOCOL_EPC == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl;

    }
    else if (UHF_RF_PROTOCOL_GB == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl;
    }
    else
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl;
    }

    return ((ptMemFreqHopCtrl->wFreqTableID != ptFreqCfg->wFreqTableID)
            || (ptMemFreqHopCtrl->wFreqWorkType != ptFreqCfg->wFreqWorkType)
            || ((ptMemFreqHopCtrl->wFreqWorkType == FIXED_FREQ) && (ptMemFreqHopCtrl->wFixFreqChannel != ptFreqCfg->wFixFreqChannel))
#ifdef SUPPORT_HOP_FREQ
            || ((ptMemFreqHopCtrl->wFreqWorkType == FREQ_HOP) && ((ptMemFreqHopCtrl->wHopChannelNum != ptFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannelNum)
                    || (ptMemFreqHopCtrl->wFreqHopMode != ptFreqCfg->tFreqHopConfig.wFreqHopMode)
                    || (ptMemFreqHopCtrl->wHopTimer != ptFreqCfg->tFreqHopConfig.wHopTimer)
                    || memcmp(&(ptFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannel[0]), &(ptMemFreqHopCtrl->wHopChannelNo[0]), (ptMemFreqHopCtrl->wHopChannelNum * 2))))
#endif
           );

}

/**********************************************************************
* 函数名称： uhfRf_SetFreqCfg
* 功能描述： 设置频率相关参数，配置流程中使用
* 输入参数： ptFreqCfg 要设置的射频参数
                                  wAntIndex  天线号
                                  wProtocolType 协议类型
* 输出参数： 频率值
* 返 回 值：
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010\11\23               zdx                          创建
* 2012\3\20               zdx            根据单天线多协议射频参数进行修改
***********************************************************************/
void uhfRf_SetFreqCfg(T_USPUHFRfFreqCfg *ptFreqCfg, WORD16 wAntIndex,
                      WORD16 wProtocolType)
{
    WORD32  dwChannelNoIndex = 0;
    T_UhfRfFreqHopCtrl *ptMemFreqHopCtrl = NULL;

    if (UHF_RF_PROTOCOL_EPC == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl;
        uhfRfDevPrint("uhfRf:EPC Freq Changed \r\n");
    }
    else if (UHF_RF_PROTOCOL_GB == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl;
        uhfRfDevPrint("uhfRf:GB Freq Changed \r\n");
    }
    else
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl;
        uhfRfDevPrint("uhfRf:ISO6B Freq Changed \r\n");
    }

    uhfRfDevPrint("uhfRf:EPC Freq Changed \r\n");
    ptMemFreqHopCtrl->wFreqWorkType = ptFreqCfg->wFreqWorkType; //定频跳频设置
    ptMemFreqHopCtrl->wFreqTableID = ptFreqCfg->wFreqTableID;
    uhfRfDevPrint("uhfRf:FreqWorkType = %d  HopTableID= %d\r\n",
                  ptMemFreqHopCtrl->wFreqWorkType, ptMemFreqHopCtrl->wFreqTableID);

    if (ptMemFreqHopCtrl->wFreqWorkType == FIXED_FREQ)
    {
        ptMemFreqHopCtrl->wFixFreqChannel = ptFreqCfg->wFixFreqChannel;
        ptMemFreqHopCtrl->wWorkChannel = ptFreqCfg->wFixFreqChannel;
        uhfRfDevPrint("uhfrf:fixed Freq chanel %d\r\n", ptMemFreqHopCtrl->wWorkChannel);
        g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(ptMemFreqHopCtrl->wWorkChannel,
                               ptMemFreqHopCtrl->wFreqTableID);
    }
    else
    {
#ifdef SUPPORT_HOP_FREQ
        ptMemFreqHopCtrl->wHopTimer = ptFreqCfg->tFreqHopConfig.wHopTimer;
        ptMemFreqHopCtrl->wHopChannelNum =
            ptFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannelNum;
        //自定义跳频表长度

        uhfRfDevPrint("uhfRf:Freq  channelNum %d  ", ptMemFreqHopCtrl->wHopChannelNum);

        ptMemFreqHopCtrl->wFreqHopMode = ptFreqCfg->tFreqHopConfig.wFreqHopMode;
        //跳频方式 随机跳 顺序跳

        /*自定义跳频表号*/
        for (dwChannelNoIndex = 0;
             dwChannelNoIndex < ptMemFreqHopCtrl->wHopChannelNum;
             dwChannelNoIndex++)
        {
            ptMemFreqHopCtrl->wHopChannelNo[dwChannelNoIndex] =
                ptFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannel[dwChannelNoIndex];
            uhfRfDevPrint("%d ", ptMemFreqHopCtrl->wHopChannelNo[dwChannelNoIndex]);
        }

        uhfRfDevPrint("\r\n");

        if ((ptMemFreqHopCtrl->wFreqHopMode == FREQ_HOP_SCAN_STEP_CHANNEL)
            || (ptMemFreqHopCtrl->wFreqHopMode == FREQ_HOP_SCAN_RANDOM_CHANNEL))
        {
            /* 步进和随机算法初始随机化*/
            srand((int)(time(0)));
            ptMemFreqHopCtrl->wHopChannel = (rand() % ptMemFreqHopCtrl->wHopChannelNum);
        }
        else
        {
            ptMemFreqHopCtrl->wHopChannel = 0;
        }

        ptMemFreqHopCtrl->wWorkChannel =
            ptMemFreqHopCtrl->wHopChannelNo[ptMemFreqHopCtrl->wHopChannel];

        GetCurrUsTime(&ptMemFreqHopCtrl->tHopClock);
        g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(ptMemFreqHopCtrl->wWorkChannel,
                               ptMemFreqHopCtrl->wFreqTableID);
#endif
    }
}
/**************************************************************************
* 函数名称：CheckFrqPara
* 功能描述：检测从后台来的配置是否正确
* 访问的表：无
* 修改的表：无
* 输入参数：T_USPUHFRfFreqCfg *ptFreqCfg 射频配置
* 输出参数：无
* 返 回 值：  USP_SUCCESS 正确
                               USP_UHF_RCVED_PARA_ERROR  异常
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 11/11/23    RUP      赵董兴        创建
**************************************************************************/

WORD32 uhfRf_CheckFrqPara(T_USPUHFRfFreqCfg *ptFreqCfg)
{
    if ((ptFreqCfg->wFreqTableID > g_tRfCtrl.wMaxFreqTable) ||
        ((ptFreqCfg->wFixFreqChannel) > (uhfRf_GetHopTable(ptFreqCfg->wFreqTableID)->wFrequeceNum))
#ifdef SUPPORT_HOP_FREQ
        || ((ptFreqCfg->wFreqWorkType == 1)
            && (ptFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannelNum > MAX_FREQ_HOP_NUM))
#endif
       )
    {
        uhfRfDevPrint("uhfRf:Rcved invalid Freq Cfg Para FreqTableID %d channel %d num %d\r\n",
                      ptFreqCfg->wFreqTableID, ptFreqCfg->wFixFreqChannel,
                      ptFreqCfg->tFreqHopConfig.tfreqChannel.wFreqChannelNum);
        return USP_UHF_RCVED_PARA_ERROR;
    }

    return USP_SUCCESS;

}

/**********************************************************************
* 函数名称： uhfRf_GetHopTable
* 功能描述：根据频率表获得控制结构
* 输入参数： 天线号
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010\11\23               zdx                          创建
***********************************************************************/

T_USPUHFFreqTableEntry *uhfRf_GetHopTable(WORD16 wHopTableId)
{

    return &g_ptUHFFreqTable[wHopTableId];
}



/**************************************************************************
* 函数名称：uhfRf_ConvChannelToFreq
* 功能描述：将频道号转化为相应的频率
* 访问的表：无
* 修改的表：无
* 输入参数：WORD16 wChannelNo   所采用的频道号
                                 WORD16 wHopTableID  所使用的频道表
* 输出参数：无
* 返 回 值：  获取的真正频率
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 11/11/23    RUP      赵董兴        创建
* 12/3/20      RUP     赵董兴         返回值返回获得的频率
**************************************************************************/

WORD32 uhfRf_ConvChannelToFreq(WORD16 wChannelNo, WORD16 wHopTableID)
{
    /* 频道号异常频率设定为0号频率*/
    if ((wChannelNo > g_ptUHFFreqTable[wHopTableID].wFrequeceNum - 1))
    {
        UHFErrorPrint("uhfrf: ChannelNo is %d abnormal ! \r\n", wChannelNo);
        //LAPInsert(FILE_UHF_RF, USP_UHF_CHANNEL_NO_ERROR, wChannelNo, 0);
        return g_ptUHFFreqTable[wHopTableID].dwFrequeces[0];
    }

    return g_ptUHFFreqTable[wHopTableID].dwFrequeces[wChannelNo];

}

/**********************************************************************
* 函数名称：SelectFreqPoint
* 功能描述：根据频率的配置选择频点
* 输入参数：wAntIndex 天线号
                                 ptFreqHopCtrl 当前跳频的控制结构
* 输出参数：设置全局变量的workfreq
* 返 回 值：    0 成功 其他 错误
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
* 12/3/20      RUP     赵董兴         根据单天线多频率配置修改
************************************************************************/
static WORD32 SelectFreqPoint(WORD16 wAntIndex , T_UhfRfFreqHopCtrl *ptFreqHopCtrl)
{

    if (NULL == ptFreqHopCtrl)
    {
        return  USP_UHF_POINTER_NULL_ERROR;

    }

    ptFreqHopCtrl->wWorkChannel =
        ptFreqHopCtrl->wHopChannelNo[ptFreqHopCtrl->wHopChannel];
    /* 记录当前频道号*/
    uhfRfDevPrint("HopChannel %d WorkChannel %d\r\n",
                  ptFreqHopCtrl->wHopChannel, ptFreqHopCtrl->wWorkChannel);


    g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(ptFreqHopCtrl->wWorkChannel,
                           ptFreqHopCtrl->wFreqTableID);

    if (ptFreqHopCtrl->wFreqHopMode == FREQ_HOP_SCAN_CHANNEL)
    {
        //逐频道扫描
        ptFreqHopCtrl->wHopChannel++;

        if (ptFreqHopCtrl->wHopChannel >= ptFreqHopCtrl->wHopChannelNum)
        {
            ptFreqHopCtrl->wHopChannel = 0;
        }
    }
    else if (ptFreqHopCtrl->wFreqHopMode == FREQ_HOP_SCAN_RANDOM_CHANNEL)
    {
        //频道号内随机跳
        ptFreqHopCtrl->wHopChannel = (rand() % ptFreqHopCtrl->wHopChannelNum);

    }
    else
    {
        /* 大间隔循环步进跳频*/
        /* Ni+1=(Ni+INT((Nl-Nf)/2)) MOD （Nl-Nf+1)，
                 其中初始Ni为Nf与Nl之间随机产生，如Ni+1=0,则Ni+1=Nl*/
        ptFreqHopCtrl->wHopChannel =
            ((ptFreqHopCtrl->wHopChannel + 1)\
             + (WORD16)((ptFreqHopCtrl->wHopChannelNum - 1) / 2))\
            % (ptFreqHopCtrl->wHopChannelNum);

        if (ptFreqHopCtrl->wHopChannel == 0)
        {
            ptFreqHopCtrl->wHopChannel = ptFreqHopCtrl->wHopChannelNum;
        }

        /* 改回到真实频道频道配置序号 */
        ptFreqHopCtrl->wHopChannel--;
    }

    return USP_SUCCESS;

}

/**********************************************************************
* 函数名称：uhfRf_getFreqTableId
* 功能描述：获得当前的频率表索引
* 输入参数：wAntIndex 天线号
                                 wProtocolType 协议类型
* 输出参数：无
* 返 回 值：    频率表ID
* 其它说明：为获取频率以及泄露对消时准备
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 12/3/20      RUP     赵董兴         创建
************************************************************************/

WORD16 uhfRf_getFreqTableId(WORD16 wAntIndex, WORD16 wProtocolType)
{
    T_UhfRfFreqHopCtrl *ptMemFreqHopCtrl = NULL;

    if (UHF_RF_PROTOCOL_EPC == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl;
    }
    else if (UHF_RF_PROTOCOL_GB == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl;
    }
    else
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl;
    }

    return  ptMemFreqHopCtrl->wFreqTableID;
}


/**********************************************************************
* 函数名称：uhfRf_getFreqWorkChannel
* 功能描述：获得当前的工作频道号
* 输入参数：wAntIndex 天线号
                                 wProtocolType 协议类型
* 输出参数：无
* 返 回 值：    频率表ID
* 其它说明：为获取频率以及泄露对消时准备
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 12/3/20      RUP     赵董兴         创建
************************************************************************/

WORD16 uhfRf_getFreqWorkChannel(WORD16 wAntIndex, WORD16 wProtocolType)
{
    T_UhfRfFreqHopCtrl *ptMemFreqHopCtrl = NULL;

    if (UHF_RF_PROTOCOL_EPC == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl;

    }
    else if (UHF_RF_PROTOCOL_GB == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl;
    }
    else
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl;
    }

    return  ptMemFreqHopCtrl->wWorkChannel;
}


/**********************************************************************
* 函数名称：uhfRf_getFreqHopCtrl
* 功能描述：获得当前的工作频道号
* 输入参数：wAntIndex 天线号
                                 wProtocolType 协议类型
* 输出参数：无
* 返 回 值：    频率表ID
* 其它说明：为获取频率以及泄露对消时准备
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 12/3/20      RUP     赵董兴         创建
************************************************************************/

T_UhfRfFreqHopCtrl *uhfRf_getFreqHopCtrl(WORD16 wAntIndex, WORD16 wProtocolType)
{
    T_UhfRfFreqHopCtrl *ptMemFreqHopCtrl = NULL;

    if (UHF_RF_PROTOCOL_EPC == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl;

    }
    else if (UHF_RF_PROTOCOL_GB == wProtocolType)
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl;
    }
    else
    {
        ptMemFreqHopCtrl = &g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl;
    }

    return  ptMemFreqHopCtrl;
}

#endif
