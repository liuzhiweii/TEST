/*********************************************************************
* 版权所有 (C)2005, 深圳市中兴通讯股份有限公司。
*
* 文件名称：
* 文件标识：
* 内容摘要：
* 其它说明：
* 当前版本：
* 作    者：
* 完成日期：
*
* 修改记录1：
* 修改记录2：
* 修改记录3：
**********************************************************************/

/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include "usp.h"
#include "common.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RBCB1)
#include <math.h>
#include "uhf_dbg.h"
//#include "uhf_time.h"
#include "uhf_trace.h"
#include "uhf_rf.h"
#include "Board.h"
#include "RfCtl.h"
#include "FpgaCtl.h"
#include "Pll.h"
#include "Lkcl.h"


/***********************************************************
 *                     常量定义                            *
***********************************************************/
#define FORWARD_FLAG 0
#define BACKWARD_FLAG 1

/***********************************************************
*                 文件内部使用的宏                        *
***********************************************************/


/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/


/***********************************************************
 *                     全局变量                            *
***********************************************************/
extern T_RfCtrl      g_tRfCtrl;
T_USPUHFRfPowerTable    g_tUhfRfPowerTable1;/*记录在eeprom中的定标数据*/
T_USPUHFRfPowerTable    g_tUhfRfPowerTable2;
T_USPUHFRfPowerTable    g_tUhfRfPowerTable3;
T_USPUHFRfPowerTable    g_tUhfRfPowerTable4;
T_USPUHFRfAntPower   g_atAntPower[READER_ANTENNA_COUNT + 1];
T_RfInitPara         g_tRfInitPara;
T_USPUHFGateVoltageCtrl  g_tUhfGateVoltageCtrl;

#if 0
/* 天线状态LED点灯数组 */
const T_AntStatus g_atAntStatLED[] = 
{
    {USP_OSS_LED_FLASH_ANT1_EXIST, USP_OSS_LED_FLASH_ANT1_NOT_EXIST, \
     USP_OSS_LED_FLASH_ANT1_WORK_ERR, USP_OSS_LED_FLASH_ANT1_WORKING},
    {USP_OSS_LED_FLASH_ANT2_EXIST, USP_OSS_LED_FLASH_ANT2_NOT_EXIST, \
     USP_OSS_LED_FLASH_ANT2_WORK_ERR, USP_OSS_LED_FLASH_ANT2_WORKING},
    {USP_OSS_LED_FLASH_ANT3_EXIST, USP_OSS_LED_FLASH_ANT3_NOT_EXIST, \
     USP_OSS_LED_FLASH_ANT3_WORK_ERR, USP_OSS_LED_FLASH_ANT3_WORKING},
    {USP_OSS_LED_FLASH_ANT4_EXIST, USP_OSS_LED_FLASH_ANT4_NOT_EXIST, \
     USP_OSS_LED_FLASH_ANT4_WORK_ERR, USP_OSS_LED_FLASH_ANT4_WORKING}
};
#endif
/***********************************************************
 *                     本地变量                            *
***********************************************************/


/***********************************************************
 *                     全局函数                            *
***********************************************************/
static BYTE    ACGetPowerTableIndex(WORD16 wVoltage, BYTE ucPTNum,
                                    T_USPUHFRfPowerTableEntry *ptPowerTableREntry);
static WORD16  ComputeVSWR(WORD16 wPTarget, WORD16 wVoltage, WORD16 wAntIndex);
static WORD16  SetK0GetPower(WORD16 wK0, WORD16 wAntIndex);
static void uhfRf_InitACData(BYTE ucTableCount);
static WORD32  uhfRf_SetRfPower(WORD16 wAntIndex, WORD16 wPower);
static WORD32  uhfRf_setCalibrateFreq(WORD16 wAntIndex);
extern WORD32  usp_uhf_rf_readPowerTable(T_USPUHFRfPowerTable *ptPowerTable, WORD16 wPTAddr);
extern WORD32  usp_uhf_rf_readPRData(T_USPUHFRfPowerTable *ptPowerTable, WORD16 wPTAddr);

/**********************************************************************
* 函数名称：void ClearAntPowerResult()
* 功能描述：清除存储的天线功率值
* 输入参数：无
* 输出参数：
* 返 回 值：无
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/12/17       RUP       zdx
************************************************************************/
void usp_uhf_rf_ClearPowerResult()
{
    WORD16 wLoop = 0;

    for (wLoop = 0; wLoop <= READER_ANTENNA_COUNT; wLoop++)
    {
        g_atAntPower[wLoop].wVswr = 10000;
        g_atAntPower[wLoop].wResIndex = 0;
        memset(g_atAntPower[wLoop].atPowers, 0,
               UHF_RF_ANT_POWER_COUNT * sizeof(T_USPUHFRfPowerEntry));
    }
}

/**********************************************************************
* 函数名称：T_AntCalibrate_Result* FindClibrateRes(WORD16 wAntIndex,WORD16
wTargetPower)
* 功能描述：根据天线和功率，寻找是否之前设置过相应的功率
* 输入参数：无
* 输出参数：
* 返 回 值：
                     NULL：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/12/15           RUP              zdx
************************************************************************/
T_USPUHFRfPowerEntry *usp_uhf_rf_FindPowerEntry(WORD16 wAntIndex, WORD16 wTargetPower)
{
    WORD16 wLoop = 0;

    for (wLoop = 0; wLoop < UHF_RF_ANT_POWER_COUNT; wLoop++)
    {
        if (g_atAntPower[wAntIndex].atPowers[wLoop].wTargetPower ==
            wTargetPower)
        {
            return &g_atAntPower[wAntIndex].atPowers[wLoop];
        }
    }

    return NULL;
}
/**********************************************************************
* 函数名称：usp_uhf_rf_SetPowerEntry
* 功能描述：将定标值存储到结构中
* 输入参数：无
* 输出参数：
* 返 回 值：天线参数的指针
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/8/31               RUP                 zdx
************************************************************************/
void usp_uhf_rf_SetPowerEntry(WORD16 wAntIndex, WORD16 wClibratePower,
                         WORD16 wTargetPower, WORD16 wClibrateK0,
                         WORD16 wDattVal)
{
    T_USPUHFRfPowerEntry *ptRfPowerEntry = NULL;
    WORD16 wTempIndex;
    WORD16 wIndex = g_atAntPower[wAntIndex].wResIndex;

    ptRfPowerEntry = &g_atAntPower[wAntIndex].atPowers[wIndex];
    ptRfPowerEntry->wCalibrateK0 = wClibrateK0;
    ptRfPowerEntry->wCalibratPower = wClibratePower;
    ptRfPowerEntry->wTargetPower = wTargetPower;
    ptRfPowerEntry->wDattVal = wDattVal;

    wTempIndex = wIndex + 1;
    g_atAntPower[wAntIndex].wResIndex =
        (wTempIndex >= UHF_RF_ANT_POWER_COUNT) ? 0 : wTempIndex;
}
/**********************************************************************
* 函数名称：void RecordAntVswr(WORD16 wAntIndex,WORD16 wVswr)
* 功能描述：保存驻波比
* 输入参数：无
* 输出参数：
* 返 回 值：无
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/8/31       RUP        zdx
************************************************************************/
inline void uhfRf_RecordAntVswr(WORD16 wAntIndex, WORD16 wVswr)
{
    g_atAntPower[wAntIndex].wVswr = wVswr;
}
/**********************************************************************
* 函数名称：usp_uhf_rf_queryAntVswr
* 功能描述：读取驻波比
* 输入参数：无
* 输出参数：
* 返 回 值：   乘以100以后的驻波比
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/8/31       RUP        zdx
************************************************************************/
WORD16 usp_uhf_rf_queryAntVswr(WORD16 wAntIndex)
{
    return g_atAntPower[wAntIndex].wVswr;
}
/**********************************************************************
* 函数名称：void uhfRf_startAllAction(void)
* 功能描述：射频启动。
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
#define ANT_NOT_INPOS_NOT_ALARMED (0)
#define ANT_NOT_INPOS_ALARMED     (1)

void uhfRf_dealInventAntStatus(WORD16 wAntIndex, WORD16 wAntStatus)
{
    static BYTE aucAntStatus[READER_ANTENNA_COUNT + 1] = {ANT_NOT_INPOS_NOT_ALARMED};

    if (RF_ANT_NOT_INPOS == wAntStatus)
    {
        if (ANT_NOT_INPOS_NOT_ALARMED == aucAntStatus[wAntIndex])
        {
            aucAntStatus[wAntIndex] = ANT_NOT_INPOS_ALARMED;
            LAPInsert(FILE_UHF_RFCTRL, USP_UHF_INVENT_ANT_NOT_INPOS, wAntIndex, 0);
        }
    }
    else
    {
        if (ANT_NOT_INPOS_ALARMED == aucAntStatus[wAntIndex])
        {
            aucAntStatus[wAntIndex] = ANT_NOT_INPOS_NOT_ALARMED;
        }
    }

}
/**********************************************************************
* 函数名称：void uhfRf_startAllAction(void)
* 功能描述：射频启动。
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
WORD32 uhfRf_startAllAction(void)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD16 wAntIndex = g_tRfCtrl.wAntIndex;
    struct timeval tStartTime;
    struct timeval tEndTime;
    GetCurrUsTime(&tStartTime);

    if (RF_ANT_NOT_INPOS == g_tRfCtrl.atRfAntCfg[wAntIndex].ucAntStause)
    {

        uhfRf_dealInventAntStatus(wAntIndex, RF_ANT_NOT_INPOS);
        uhfRfDevPrint("uhfRf:invent but ant %d not inpositon\r\n", wAntIndex);
        return USP_UHF_INVENT_ANT_NOT_INPOS;
    }

    /* 天线选择 */
    dwRet = usp_uhf_rf_selectAnt(wAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfRf:Rf antenna set failed!dwRet = 0x%x\r\n");
        return dwRet;
    }

    dwRet = usp_uhf_rf_removeAntAlarm();

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    dwRet = usp_uhf_rf_setPLLFreq(g_tRfCtrl.dwWorkFreq);

    if (dwRet != USP_SUCCESS)
    {
        uhfRfDevPrint("usp_uhf_rf_setPLLFreq error\r\n");
        return dwRet;
    }

    dwRet = uhfRf_SetRfPower(wAntIndex,
                             g_tRfCtrl.atRfAntCfg[wAntIndex].wInventPower * 100);

    if (dwRet != USP_SUCCESS)
    {
        uhfRfDevPrint("uhfRf_SetRfPower error!!!  dwRet = 0x%x\r\n", dwRet);
        return dwRet;
    }

    /*开启泄露对消需要则进行微调*/
    dwRet = uhfRf_FineLKCL(wAntIndex,
                           uhfRf_getFreqHopCtrl(wAntIndex , g_tRfCtrl.wProtocolType));

    if (dwRet != USP_SUCCESS)
    {
        uhfRfDevPrint("RF post proc failed\r\n");
        return dwRet;
    }

    dwRet = uhfRf_dealAlarmReport(wAntIndex);

    if (dwRet != USP_SUCCESS)
    {
        uhfRfDevPrint("check ant alarmed\r\n");
        return dwRet;
    }

    //RCP_LED_FLASH_ON(g_atAntStatLED[wAntIndex - 1].wAnt_Working);
    
    GetCurrUsTime(&tEndTime);
    uhfRfDevPrint("stage uhfRf_FineLKCL %dms\r\n",
                  CalMsTimeInterval(&tStartTime, &tEndTime));
    return USP_SUCCESS;

} /* void uhfRf_startAllAction(void) */
/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_setTxPower(WORD32 dwRfTxPower)
* 功能描述：设置射频发送功率
* 输入参数：
            WORD32 dwRfTxPower ； 功率设定值
* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
WORD32 usp_uhf_rf_setTxPower(WORD16 wAntIndex, WORD16 wTargetPower)
{
    T_USPUHFRfPowerEntry *ptPowerEntry = NULL;

    ptPowerEntry = usp_uhf_rf_FindPowerEntry(wAntIndex, wTargetPower);

    if (NULL == ptPowerEntry)
    {
        uhfRfDevPrint("uhfRf: get clibrated entry error\r\n");
        return  USP_UHF_RF_ANT_SET_ERROR;
    }

    /* add by zongjie 2013.1.10 */
    /* 跟硬件调试添加，为了解决两次清点间隔泄漏信号过大的问题 */
    FpgaRegWrite(REG_DAC_DC_VALUE_REG, 0);/* 在打开载波之前，将0x87寄存器写为0 */
    //usp_oss_vos_usleep(DAC_DC_CHANGE_DELAY);/* wzp add zhushi延时一段时间 */
    /* end 2013.1.10 */
    usp_uhf_rf_writeCtrlWord(ptPowerEntry->wCalibrateK0);
    /* 重新设置功放功率 写入前向DATT 衰减值 */
    usp_uhf_rf_setACDatt(ptPowerEntry->wDattVal);
    usp_uhf_rf_WriteAntDatt();
    /* 获取当前天线的定标功率值 */
    usp_uhf_rf_SetLO2Datt(ptPowerEntry->wCalibratPower);
    uhfRfDevPrint("uhfRf: use clibrate power %d\r\n", ptPowerEntry->wCalibratPower);
    
    return USP_SUCCESS;

}

/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_txSet(WORD32 dwRfTxAction)
* 功能描述：前向射频功率发射开关控制
* 输入参数：
            WORD32 dwRfTxAction
                                UHF_RF_START_TX：启动射频功率发送；
                                UHF_RF_STOP_TX： 关闭射频功率发送

* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void usp_uhf_rf_txSet(WORD16 wRfTxAction)
{
#if 0
    if (wRfTxAction != FpgaRegRead(SINGLETONE_SEND_CTRL))
    {
        FpgaRegWrite(SINGLETONE_SEND_CTRL, wRfTxAction);
    }
#endif
} /* WORD32 usp_uhf_rf_txSet(WORD32 dwRfTxAction) */
/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_setModulateDepth(WORD32 dwModulateDepth)
* 功能描述：射频调试深度设置
* 访问的表：无
* 修改的表：无
* 输入参数：
            WORD32 dwModulateDepth 射频调试深度：
* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010.1.4     V0.0.1       zdx   修改
************************************************************************/
void usp_uhf_rf_setModulateDepth(WORD32 dwModulateDepth)
{
    WORD16 wData = 0;

    if (dwModulateDepth > 100)
    {
        dwModulateDepth = 100;
    }

    wData = (WORD16)(((WORD32)(RF_ASK_DAC_HIGH_VALUE * (100 - dwModulateDepth))) / 100);
    FpgaRegWrite(REG_module_depth, wData);

} /* WORD32 usp_uhf_rf_setModulateDepth(WORD32 dwModulateDepth) */


/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_setRFPortocolType(WORD32 dwModulateDepth)
* 功能描述：射频调试深度设置
* 访问的表：无
* 修改的表：无
* 输入参数： 00 epc 01 iso6B
* 输出参数：
* 返 回 值：无
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010.1.4     V0.0.1       zdx   修改
************************************************************************/
void usp_uhf_rf_setRFPortocolType(WORD16 wType)
{
    FpgaRegWrite(REG_RF_PROTOCOL_TYPE,wType);
}

/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_setModulateDepth(WORD32 dwModulateDepth)
* 功能描述：射频调试深度设置
* 访问的表：无
* 修改的表：无
* 输入参数：
            WORD32 dwModulateDepth 射频调制方式
* 输出参数：
* 返 回 值：无
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010.1.4     V0.0.1       zdx   修改
************************************************************************/
void usp_uhf_rf_setRTModuleType(WORD16 wType)
{
    FpgaRegWrite(reg_module_type, wType);
}

/**********************************************************************
  * 函数名称：void SetLKCLPower()
  * 功能描述：进行泄露对消的时候需要将功率设置成30DB
  * 输入参数：无
  * 输出参数：
  * 返 回 值：
              WORD32      0：    成功
                        其他：    失败
  * 其它说明：无
  * 修改日期      版本号  修改人      修改内容
  * ---------------------------------------------------------------------
  * 2006/9/16    V0.0.1       ft          创建
  ************************************************************************/
void uhfRf_SetLKCLPowerPara(BYTE ucAntIndex)
{
    T_USPUHFRfPowerEntry *ptPowerEntry = NULL;

    ptPowerEntry = usp_uhf_rf_FindPowerEntry(ucAntIndex, LKCL_SET_POWER);

    if (NULL == ptPowerEntry)
    {
        usp_uhf_rf_writeCtrlWord(g_atAntPower[ucAntIndex].ptPowerTable->wK0);
        usp_uhf_rf_setACDatt(UHF_RF_LKCL_ATTEN);
        usp_uhf_rf_WriteAntDatt();
        usp_uhf_rf_SetLO2Datt(LKCL_SET_POWER);
        uhfRfDevPrint("uhfRf: LKCL power set use default\r\n");
    }
    else
    {
        usp_uhf_rf_writeCtrlWord(ptPowerEntry->wCalibrateK0);
        usp_uhf_rf_setACDatt(ptPowerEntry->wDattVal);
        usp_uhf_rf_WriteAntDatt();
        usp_uhf_rf_SetLO2Datt(ptPowerEntry->wCalibratPower);
        uhfRfDevPrint("uhfRf:Set LKCL 30 DB\r\n");
    }

}

/**********************************************************************
   * 函数名称：void uhfRf_SetLKCLPower()
   * 功能描述：进行泄露对消的时候需要将功率设置成30DB
   * 输入参数：无
   * 输出参数：
   * 返 回 值：
                            WORD32      0：    成功
                            其他：    失败
   * 其它说明：无
   * 修改日期      版本号  修改人      修改内容
   * ---------------------------------------------------------------------
   * 2006/9/16    V0.0.1       ft          创建
   ************************************************************************/
WORD32 uhfRf_SetLKCLPower(BYTE ucAntIndex)
{
    WORD32 dwRet = USP_SUCCESS;

    dwRet = usp_uhf_rf_autoCalibrate(ucAntIndex, LKCL_SET_POWER);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfRf:set lkcl 30db power error\r\n");
        return dwRet;
    }

    uhfRf_SetLKCLPowerPara(ucAntIndex);
    return USP_SUCCESS;
}


/**************************************************************************
* 函数名称:
* 功能描述: 单位换算
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2008年9月13日          V1.0              XXXX                XXXX
**************************************************************************/
static Double MW2dBm(Double value)
{
    return 10 * log10(value);
}

/**************************************************************************
* 函数名称:
* 功能描述:  单位换算
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2008年9月13日          V1.0              XXXX                XXXX
**************************************************************************/
static Double DBm2mW(Double value)
{
    return pow(10, value / 10);
}

/**************************************************************************
* 函数名称:uhfRf_RefreshPower
* 功能描述:  根据配置进行功率的重新定标
* 访问的表: 无
* 修改的表: 无
* 输入参数: 无
* 输出参数:无
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2012年1月13日        RUP           XXXX                XXXX
**************************************************************************/
#define POWER_INITIALIZED    (1)
#define POWER_NOT_INITIALIZED (0)
void uhfRf_RefreshPower()
{
    static WORD16 wPowerInited = POWER_NOT_INITIALIZED;

    usp_uhf_rf_removeAntAlarm();
    usp_uhf_rf_setAmp(RF_AMP_ON);
    sleep(g_tRfInitPara.wClibrateWaitTime);

    if (POWER_NOT_INITIALIZED == wPowerInited)
    {
        if (g_tRfCtrl.wLKCLSwitch == 1)
        {
            uhfRf_ReaderLKCLProc();
        }

        wPowerInited = POWER_INITIALIZED;
    }
#if UHF_BOARD_TYPE == BOARD_TYPE_RFCB7
    /* 6600C1/C2在泄漏对消完成后，关闭泄漏对消DAC时钟，解决杂散超标的问题 */
    FpgaRegWrite(LKCL_DAC_CLK_CTRL, LKCL_DAC_CLK_OFF);
#endif
    ACPowerSetProc();
}

/**************************************************************************
* 函数名称: ACPowerSetProc
* 功能描述: 上电以后对在位的天线进行上电自动定标
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:        WORD32 上电自动定标执行成功
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  07/06/13          V1.0              XXXX                XXXX
**************************************************************************/
WORD32 ACPowerSetProc()
{
    BYTE ucAntIndex = 0;
    WORD16 wPTarget = 0;
    WORD32 dwRet = USP_SUCCESS;
    WORD16 wLoop = 0;
    WORD16 wPaWarmed = 0;

    usp_uhf_rf_ClearPowerResult();

    for (ucAntIndex = 1; ucAntIndex <= READER_ANTENNA_COUNT; ucAntIndex++)
    {
        dwRet = usp_uhf_rf_getAntStatus(ucAntIndex);

        if (USP_SUCCESS == dwRet)
        {
#if (UHF_BOARD_TYPE == BOARD_TYPE_RFCB2)||(UHF_BOARD_TYPE == BOARD_TYPE_RFCB_BT)

            if (0 == wPaWarmed)
            {
                uhfRf_warmPA(UHF_RF_WARM_PA_POWER, ucAntIndex);
                wPaWarmed = 1;
            }

#endif
            g_tRfCtrl.atRfAntCfg[ucAntIndex].ucAntStause = RF_ANT_INPOS;

           // RCP_LED_FLASH_ON(g_atAntStatLED[ucAntIndex - 1].wAnt_Exist);
            //RCP_LED_FLASH_OFF(g_atAntStatLED[ucAntIndex - 1].wAnt_Not_Exist);

            for (wLoop = 0; wLoop < UHF_RF_ANT_POWER_COUNT; wLoop++)
            {
                wPTarget = g_tRfCtrl.atRfAntCfg[ucAntIndex].aucAntPower[wLoop] * 100;

                if (0 == wPTarget)
                {
                    break;
                }
                else
                {
                    dwRet = usp_uhf_rf_autoCalibrate(ucAntIndex, wPTarget);

                    if (USP_SUCCESS == dwRet)
                    {
                        uhfRfDevPrint("Ant%d power set %ddb\r\n", ucAntIndex, wPTarget);
                    }
                    else
                    {
                        uhfRfDevPrint("Ant%d power set %ddb failed, dwRet = %d\r\n", ucAntIndex, wPTarget, dwRet);
                    }
                }
            }

        }
        else
        {
            g_tRfCtrl.atRfAntCfg[ucAntIndex].ucAntStause = RF_ANT_NOT_INPOS;
            
            //RCP_LED_FLASH_OFF(g_atAntStatLED[ucAntIndex - 1].wAnt_Exist);
            //RCP_LED_FLASH_ON(g_atAntStatLED[ucAntIndex - 1].wAnt_Not_Exist);
            
            uhfRfDevPrint("Ant %d is absent\r\n", ucAntIndex);
        }

    }

    return USP_SUCCESS;
}
/**************************************************************************
* 函数名称：ACAutoCalibrateProc
* 功能描述：对指定的天线进行定标操作
* 输入参数：BYTE ucAntIndex          天线索引
*                               WORD16 wPTarget      目标功率
* 输出参数：
* 返 回 值：    定标成功  READER_AC_SUCCESS
*                               定标失败  其他
* 其它说明：
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 02/08/01	     V1.0	    XXXX	      XXXX
**************************************************************************/
WORD32 usp_uhf_rf_autoCalibrate(BYTE ucAntIndex, WORD16 wPTarget)
{
    WORD32 dwRet = 0;
    T_USPUHFRfPowerEntry *ptPowerEntry = NULL;
    BYTE   aucAlarmInfo[20];
    WORD32 dwAlarmInfoSize = 0;

    uhfRfDevPrint("uhfRf:wPTarget = %d\r\n", wPTarget);
    ptPowerEntry = usp_uhf_rf_FindPowerEntry(ucAntIndex, wPTarget);

    if (NULL != ptPowerEntry)
    {
        uhfRfDevPrint("uhfRf:the power has been autoclibrated\r\n");
        return USP_SUCCESS;
    }

    /* 选择天线*/
    dwRet = usp_uhf_rf_selectAnt(ucAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfRf:Rf antenna set failed!\r\n");
        return USP_UHF_ANT_SET_ERROR;
    }

    usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelForward);
    /* 写入天线*/
    usp_uhf_rf_WriteAntDatt();

    usp_uhf_rf_setAmp(RF_AMP_ON);
    /*去掉可能的驻波保护*/
    usp_uhf_rf_removeAntAlarm();

    /*定标时需要调整功率实际发出的频率值*/
    dwRet = uhfRf_setCalibrateFreq(ucAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfrf: ac freq set error\r\n");
        return USP_UHF_PLL_CFG_ERROR;
    }

    usp_uhf_rf_txSet(UHF_RF_START_TX);
    dwRet = usp_uhf_rf_CalibrateK0Datt(wPTarget, ucAntIndex);
    usp_uhf_rf_txSet(UHF_RF_STOP_TX);        /* 关功放关射频*/

    if (USP_SUCCESS != dwRet)
    {
        /* 定标失败，上报告警 */
        //RCP_LED_FLASH_ON(g_atAntStatLED[ucAntIndex - 1].wAnt_Work_Err);
        LAPInsert(FILE_UHF_RFCTRL, dwRet, wPTarget, 0);
        uhfRfDevPrint("uhfRf:Send Clibrate Fail to AMP!\r\n");
        dwAlarmInfoSize = snprintf((char *)aucAlarmInfo, sizeof(aucAlarmInfo), "%d", ucAntIndex);
        uhf_amp_report(EV_USP_OAM_AMP_InformReport,
                       R_RF_AC_FAILED_ALARM, 0,
                       USP_OAM_AMP_ALARM_LEVEL_SERIOUS, aucAlarmInfo, dwAlarmInfoSize);

        return dwRet;
    }

    return USP_SUCCESS;

}


/**************************************************************************
* 函数名称：ACGetPowerTableIndex
* 功能描述：根据电压值查找计算区间
* 访问的表：
* 修改的表：
* 输入参数：WORD16 wVoltage 电压值
* 输出参数：
* 返 回 值：    WORD32  g_atPowerTable表中电压计算区间下限索引
* 其它说明：
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 02/08/01	     V1.0	    XXXX	      XXXX
**************************************************************************/
static BYTE ACGetPowerTableIndex(WORD16 wVoltage, BYTE ucPTNum,
                                 T_USPUHFRfPowerTableEntry *ptPowerTableREntry)
{
    BYTE ucLoop = 0;

    /* 如果读取的电压比表中最低电压还低，使用前两条记录作为计算区间*/
    if (wVoltage < ptPowerTableREntry[0].wVoltage)
    {
        return 0;
    }

    /* 否则寻找电压所在的区间*/
    for (ucLoop = 0; ucLoop < (ucPTNum - 2); ucLoop++)
    {
        if (wVoltage >= ptPowerTableREntry[ucLoop].wVoltage
            && wVoltage <= ptPowerTableREntry[ucLoop + 1].wVoltage)
        {
            return ucLoop;
        }
    }

    /* 如果读取电压值比表中次高电压还高,使用最后两条记录作为计算区间*/
    return ucLoop;


}
//#if BOARD_TYPE_RFCB7
#if 0
/**************************************************************************
* 函数名称：ACComputePower
* 功能描述：针对RFCB7使用的定标算法，计算指定天线当前的功率
*           天线1、4使用的公式:Pout=(Ln((D1+k)/34.599))/0.1099
*           天线2、3使用的公式:Pout=(Ln((D2+k)/36.242))/0.1081
* 访问的表：
* 修改的表：
* 输入参数：WORD16 wVoltage 电压值
*           BYTE ucAntIndex  天线索引
* 输出参数：
* 返 回 值：WORD16 wCurPower 当前的功率
* 其它说明：
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 2012/08/24  V1.0       宗杰        创建
**************************************************************************/
SWORD16 uhfRf_ComputePower(WORD16 wVoltage, BYTE ucAntIndex, BYTE flag)
{
    SWORD16 swCurPower = 0;
    Double  dCompensate = 0.0;/* 计算功率补偿值 */

    if ((1 == ucAntIndex) || (4 == ucAntIndex))
    {
        swCurPower = (SWORD16)(log(((Double)wVoltage + dCompensate)/34.599)/0.1099);
    }
    else if ((2 == ucAntIndex) || (3 == ucAntIndex))
    {
        swCurPower = (SWORD16)(log(((Double)wVoltage + dCompensate)/36.242)/0.1081);
    }
    else
    {
        uhfRfDevPrint("AntIndex = %d   error!!\r\n", ucAntIndex);
    }
    uhfRfDevPrint("wVoltage = 0x%x, swCurPower = %d\r\n", wVoltage, swCurPower);

    return swCurPower;
}

#else
/**************************************************************************
* 函数名称：usp_uhf_rf_ComputePower
* 功能描述：计算指定天线当前的功率
* 访问的表：
* 修改的表：
* 输入参数：WORD16 wVoltage 电压值
*                               BYTE ucAntIndex  天线索引
* 输出参数：
* 返 回 值：    WORD16 wCurPower 当前的功率
* 其它说明：
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 02/08/01	     V1.0	    XXXX	      XXXX
**************************************************************************/
SWORD16 usp_uhf_rf_ComputePower(WORD16 wVoltage, BYTE ucAntIndex, BYTE flag)
{
    BYTE ucTableIndex = 0;
    SWORD16 swPLow = 0;
    SWORD16 swPHigh = 0;
    WORD16 wVLow = 0;
    WORD16 wVHigh = 0;
    SWORD16 swCurPower = 0;
    T_USPUHFRfPowerTable   *ptPowerTable = g_atAntPower[ucAntIndex].ptPowerTable;
    T_USPUHFRfPowerTableEntry  *ptPowerTableREntry = NULL;

    if (FORWARD_FLAG == flag)
    {
        ptPowerTableREntry = ptPowerTable->atFwTable;
        ucTableIndex = ACGetPowerTableIndex(wVoltage, RF_FORWARD_PT_NUM,
                                            ptPowerTableREntry);
    }
    else
    {
        ptPowerTableREntry = ptPowerTable->atBwTable;
        ucTableIndex = ACGetPowerTableIndex(wVoltage, RF_BACKWARD_PT_NUM,
                                            ptPowerTableREntry);
    }



    /* 计算当前的K0 和功率值*/
    wVLow = ptPowerTableREntry[ucTableIndex].wVoltage;
    wVHigh = ptPowerTableREntry[ucTableIndex + 1].wVoltage;
    swPLow = ptPowerTableREntry[ucTableIndex].swPower;
    swPHigh = ptPowerTableREntry[ucTableIndex + 1].swPower;
    swCurPower = swPLow + ((wVoltage - wVLow) * (swPHigh - swPLow)) / (wVHigh - wVLow);

    return swCurPower;
}
#endif
/**************************************************************************
* 函数名称：uhfRf_WriteCtrlWord
* 功能描述：设置控制字K0
* 访问的表：
* 修改的表：
* 输入参数：WORD16 wCrtlWord  写入的控制字K0
* 输出参数：
* 返 回 值：    WORD16  成功返回0
* 其它说明：
* 修改日期    版本号     修改人	     修改内容
* -----------------------------------------------
* 02/08/01	     V1.0	    XXXX	      XXXX
*12/6/4            BT          zdx           增加对于K0值为负值时的考虑
**************************************************************************/
#define UHF_RF_MAX_POSITIVE_K0    (0x6000)
#define UHF_RF_MIN_NEGATIVE_K0    (0xA000)
void usp_uhf_rf_writeCtrlWord(WORD16 wCrtlWord)
{
    if ((wCrtlWord > UHF_RF_MIN_NEGATIVE_K0) || (wCrtlWord < UHF_RF_MAX_POSITIVE_K0))
    {
        FpgaRegWrite(REG_FORWARD_PWADJ, wCrtlWord);
    }
    else
    {
        //LAPInsert(FILE_UHF_RFCTRL, USP_UHF_RF_K0_ABNORMAL, wCrtlWord, 0);
    }

    uhfRfDevPrint("uhfRf:write ctl word %x\r\n", wCrtlWord);
}

/**************************************************************************
* 函数名称:usp_uhf_rf_readDetectVal
* 功能描述: 读取检测到的电压值
* 访问的表:
* 修改的表:
* 输入参数: B
* 输出参数:
* 返回值:       WORD16    读取到的电压值
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  12/8/2              RUP               zdx        
**************************************************************************/
#define DETECTCOUNT 5
WORD16 usp_uhf_rf_readDetectVal()  
{
  WORD16 wLoop=0;
  WORD16 wReadData=0;
  
  for(wLoop=0;wLoop<DETECTCOUNT;wLoop++)
  {
   // wReadData += FpgaRegRead(POWER_DETECT_VAL);
  }
  
  wReadData/=DETECTCOUNT;
  return wReadData;
}

/**************************************************************************
* 函数名称: usp_uhf_rf_getAntStatus
* 功能描述: 判断天线是否在位
* 访问的表:
* 修改的表:
* 输入参数: BYTE ucAntIndex 天线索引
* 输出参数:
* 返回值:       WORD32    0 天线在位
*                                               其他 天线不在位
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  07/06/13          V1.0              XXXX                XXXX
*  12/5/3              RUP               zdx         增加对反向检测后驻波保护的变化
**************************************************************************/

#define  UHF_RF_ABNORMAL_K0 (0)
WORD32 usp_uhf_rf_getAntStatus(WORD16 wAntIndex)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD16 wReadData = 0;
    WORD16 wVSWR = 0;
    WORD16 wLoop = 0;
    SWORD16 swPower = 0;
    BYTE   aucAlarmInfo[20];
    WORD32 dwAlarmInfoSize = 0;

    /* 选择天线RFCB 单板需要如下的两个步骤*/
    dwRet = usp_uhf_rf_selectAnt(wAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfRf:Rf antenna set failed! %d\r\n", dwRet);
        return USP_UHF_ANT_SET_ERROR;
    }

    usp_uhf_rf_WriteAntDatt();

    if (UHF_RF_ABNORMAL_K0 == g_atAntPower[wAntIndex].ptPowerTable->wK0)
    {
        /*定标数据错误时直接返回错误 通过
               在定标数据读取时判断的结果来设置*/
        uhfRfDevPrint("uhfRf: abnormal powertable data!!!!!!!!!!!\r\n");
        return USP_UHF_ANT_NOT_INPOS_ERROR;
    }

    /* 去掉驻波保护 */
    usp_uhf_rf_removeAntAlarm();
    /*开功放*/
    usp_uhf_rf_setAmp(RF_AMP_ON);
    usp_uhf_rf_txSet(UHF_RF_START_TX);
    usleep(1000);
    /* 设置功率值为20db 的功率值0x250  Datt 衰减值设置为定标表中*/
    usp_uhf_rf_setACDatt(g_tRfInitPara.w20DBAtten);
    usp_uhf_rf_WriteAntDatt();
    usp_uhf_rf_writeCtrlWord(g_atAntPower[wAntIndex].ptPowerTable->wK0);
    /* 设置功率检测控制寄存器检测反向功率*/
    usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelForward);
    /* 打开功率检测ADC的时钟 */
    FpgaRegWrite(POWER_DETECT_ADC_CLK_CTRL, POWER_DETECT_ADC_CLK_ON);

    /* 延时等待*/
    usleep(UHFRF_AC_WAIT_TIME);

    if (USP_UHF_ANT_IS_PROTECTED == uhfRf_IsAntProtected())
    {
        wVSWR = 10000;
    }
    else
    {
        /* 读取功率检测值寄存器的值*/
        wReadData = usp_uhf_rf_readDetectVal();
        uhfRfDevPrint("uhfRf:Foward Voltage detect 0X%x ", wReadData);
        swPower = usp_uhf_rf_ComputePower(wReadData, wAntIndex, FORWARD_FLAG);
        uhfRfDevPrint("Computed power is %d\r\n", swPower);
        swPower += g_tRfInitPara.swForCompensatePower;

        if (swPower <= 0)
        {
            wVSWR = 10000;
        }
        else
        {
            usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelBackward);
            usleep(UHFRF_AC_WAIT_TIME);
            wReadData= usp_uhf_rf_readDetectVal();
            wVSWR = ComputeVSWR(swPower, wReadData, wAntIndex);
        }
    }

    if (USP_UHF_ANT_IS_PROTECTED == uhfRf_IsAntProtected())
    {
        /*增加检测反向后vswr的判断*/
        wVSWR = 10000;
    }

    usp_uhf_rf_txSet(UHF_RF_STOP_TX);
    /* 关闭功率检测ADC的时钟 */
    FpgaRegWrite(POWER_DETECT_ADC_CLK_CTRL, POWER_DETECT_ADC_CLK_OFF);
    uhfRf_RecordAntVswr(wAntIndex, wVSWR);
    uhfRfDevPrint("uhfRf:Ant %d VSWR is %d !\r\n", wAntIndex, wVSWR);

    if (g_tRfInitPara.wAntOnlineThr < wVSWR)
    {
        dwAlarmInfoSize = snprintf((char *)aucAlarmInfo, sizeof(aucAlarmInfo), "%d", wAntIndex);
        uhf_amp_report(EV_USP_OAM_AMP_InformReport,
                       R_RF_AC_ANTABSENT_ALARM, 0,
                       USP_OAM_AMP_ALARM_LEVEL_SERIOUS, aucAlarmInfo, dwAlarmInfoSize);
        return USP_UHF_ANT_NOT_INPOS_ERROR; /*天线不在位*/
    }

    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称: usp_uhf_rf_CalibrateK0Datt
* 功能描述: 根据当前功率和控制字对指定天线进行闭环反馈定标
* 访问的表:
* 修改的表:
* 输入参数: WORD16 wPCurrent    天线当前功率
*                           WORD16 wPTarget      定标目标功率
*                           WORD16 wCurCtrlWord 当前控制字
*                           BYTE ucAntIndex           天线索引号
* 输出参数:
* 返回值:
* 其它说明   此函数中的打印信息追踪定标的整个过程，用于定位定标过程中算法出现的震荡所导致的不成功现象
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  07/06/13          V1.0              XXXX                XXXX
**************************************************************************/
WORD32 usp_uhf_rf_CalibrateK0Datt(WORD16 wPTarget, WORD16 wAntIndex)
{
    WORD16  wK0 = g_atAntPower[wAntIndex].ptPowerTable->wK0;
    SWORD16 swPowerDiff = 0;
    WORD16  wDattVal = 0;
    WORD16  wDetectPower = 0;

    if (wPTarget > g_tRfInitPara.wMaxPower)
    {
        uhfRfDevPrint("uhfrf:power exceed max power\r\n");
        return USP_UHF_RF_POWER_EXCEEDED;
    }

    //uhfRf_warmPA(wPTarget,wAntIndex);
    /*用DATT 粗调*/
    wDetectPower = usp_uhf_rf_GetPowerDatt(wAntIndex, wPTarget, &wDattVal, wK0);

    swPowerDiff = wDetectPower - wPTarget;

    if (abs(swPowerDiff) > 1000)
    {
        return USP_UHF_CLIBRITE_ABNORAML;
    }

    if (abs(swPowerDiff) > 25)
    {
        /*用K0微调*/
        wDetectPower = usp_uhf_rf_GetPowerK0(wAntIndex, wPTarget,
                                        wDattVal, &wK0, wDetectPower);
    }

    usp_uhf_rf_SetPowerEntry(wAntIndex, wDetectPower, wPTarget, wK0, wDattVal);
    uhfRfDevPrint("uhfRf: ant %d calibrate power %d Success!\r\n\r\n",
                  wAntIndex, wDetectPower);

    return USP_SUCCESS;
}

/**********************************************************************
* 函数名称: usp_uhf_rf_GetPowerK0
* 功能描述:通过K0进行微调
* 输入参数: WORD16 wAntIndex    天线号
*                           WORD16 wPTarget      定标目标功率
*                           WORD16 wFpgaAtt  当前控制字
*                           WORD16 *pwK0  完成后的K0
                             WORD16 wDetectPower 调整datt结束后的功率值
* 输出参数:
* 返回值:     WORD16  定标后检测到的功率值
* 其它说明  此函数将功率控制到0.5db之内
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
* 12/01/11          V1.0              赵董兴               创建
***********************************************************************/
WORD16 usp_uhf_rf_GetPowerK0(WORD16 wAntIndex, WORD16 wPTarget,
                               WORD16 wFpgaAtt, WORD16 *pwK0, WORD16 wDetectPower)
{
    WORD16  wK0AdjLoop = 0;
    WORD16  wK0 = *pwK0;
    SWORD16 swPowerDiff = 0;
    float   fPowValue = 0.0;

    usp_uhf_rf_setACDatt(wFpgaAtt);
    usp_uhf_rf_WriteAntDatt();


    for (wK0AdjLoop = 0; wK0AdjLoop < UHF_RF_MAX_AC_ADJUST; wK0AdjLoop++)
    {
        swPowerDiff = wPTarget - wDetectPower;

        /*小于0.25db 退出调整流程*/
        if (abs(swPowerDiff) <= 25)
        {
            break;
        }

        /*公式K1=K0*(10^((P1-P0)/20)) 其中P1为目标功率
                P2为当前计算功率，结果为要设置的K0*/
        fPowValue = pow(10, (float)swPowerDiff / 2000);
        uhfRfDevPrint("uhfRf: %d fPowValue %f\r\n", swPowerDiff, fPowValue);
        /*避免出现过大的值，此时可能有问题*/
        fPowValue = (fPowValue > 1.5) ? 1.5 : fPowValue;

        wK0 = wK0 * fPowValue;

        /*限制K0的值不能太大*/
        if (wK0 > g_tRfInitPara.wMaxK0)
        {
            wK0 = UHF_RF_MAX_K0;
            uhfRfDevPrint("uhfRf:Alram K0 is too High %x!\r\n", wK0);
        }

        wDetectPower = SetK0GetPower(wK0, wAntIndex);

    }

    *pwK0 = wK0;
    return  wDetectPower;
}

/**********************************************************************
* 函数名称: uhfRf_warmPA
* 功能描述:PA在检测之前应该先预热一下
* 输入参数: WORD16 wAntIndex    天线号
*                           WORD16 wPTarget      定标目标功率
*                           WORD16 wK0
* 输出参数:
* 返回值:     无
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
* 12/01/11          V1.0              赵董兴               创建
***********************************************************************/

void uhfRf_warmPA(WORD16 wPTarget, WORD16 wAntIndex)
{
    WORD16  wFpgaAtten = 0;
    WORD16  wPowerAtt = 0;
    WORD16  wK0 = g_atAntPower[wAntIndex].ptPowerTable->wK0;
    /*计算初始衰减值*/
    wPowerAtt = g_tRfInitPara.wFullPower - wPTarget;
    wPowerAtt = (wPowerAtt <= g_tRfInitPara.wMinAtten) ? g_tRfInitPara.wMinAtten : wPowerAtt;
    uhfRfDevPrint("Change wPowerAtt to %d and ", wPowerAtt);
    wFpgaAtten = usp_uhf_rf_TransToFpgaAtten(wPowerAtt);
    usp_uhf_rf_setACDatt(wFpgaAtten);
    usp_uhf_rf_WriteAntDatt();
    usp_uhf_rf_writeCtrlWord(wK0);
    /* 设置功率检测控制寄存器检测前向功率*/
    usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelForward);

    sleep(UHFRF_PA_WARM_TIME);    /* 延时等待*/

}

/**********************************************************************
* 函数名称: usp_uhf_rf_GetPowerDatt
* 功能描述: 根据目标功率将功率控制到0.5db之内
* 输入参数: WORD16 wAntIndex    天线号
*                           WORD16 wPTarget      定标目标功率
*                           WORD16 *pwFpgaAtt  当前控制字
*                           WORD16 wK0
* 输出参数:
* 返回值:     WORD16  定标后检测到的功率值
* 其它说明  此函数将功率控制到0.5db之内
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
* 12/01/11          V1.0              赵董兴               创建
***********************************************************************/
WORD16 usp_uhf_rf_GetPowerDatt(WORD16 wAntIndex, WORD16 wPTarget,
                                 WORD16 *pwFpgaAtt, WORD16 wK0)
{
    SWORD16 swPowerDiff = 0;
    WORD16  wAttenAdjLoop = 0;
    WORD16  wFpgaAtten = 0;
    WORD16  wDetectPower = 0;
    WORD16  wPowerAtt = 0;

    /*计算初始衰减值*/
    wPowerAtt = g_tRfInitPara.wFullPower - wPTarget;

    for (wAttenAdjLoop = 0; wAttenAdjLoop < UHF_RF_MAX_AC_ADJUST; wAttenAdjLoop++)
    {
        wPowerAtt = (wPowerAtt <= g_tRfInitPara.wMinAtten) ? g_tRfInitPara.wMinAtten : wPowerAtt;
        uhfRfDevPrint("uhfRf:Change wPowerAtt to %d and ", wPowerAtt);
        wFpgaAtten = usp_uhf_rf_TransToFpgaAtten(wPowerAtt);
        usp_uhf_rf_setACDatt(wFpgaAtten);
        usp_uhf_rf_WriteAntDatt();
        wDetectPower = SetK0GetPower(wK0, wAntIndex);
        swPowerDiff = wDetectPower - wPTarget;

        /*已经是最大衰减但是还是小于目地值*/
        if ((g_tRfInitPara.wMaxAtten == wPowerAtt) && (0 < swPowerDiff))
        {
            break;
        }

        /*已经是最小衰减但是还是大于目地值*/
        if ((g_tRfInitPara.wMinAtten == wPowerAtt) && (0 > swPowerDiff))
        {
            break;
        }

        /*小于0.25db 退出调整流程*/
        if (abs(swPowerDiff) <= 25)
        {
            break;
        }

        /*发现异常，硬件有问题，不再调整*/
        if (abs(swPowerDiff) > 1000)
        {
            LAPInsert(FILE_UHF_RFCTRL, USP_UHF_CLIBRITE_ABNORAML, swPowerDiff, 2);
            uhfRfDevPrint("uhfRf:att adjust power detected %d db\r\n", wDetectPower);
            break;
        }

        /*根据检测功率值调整衰减值*/
        if ((swPowerDiff < 0) && (abs(swPowerDiff) > wPowerAtt))
        {
            /*避免wPowerAtt += swPowerDiff  出现负值的情况*/
            wPowerAtt = 0;
        }
        else
        {
            wPowerAtt += swPowerDiff;
        }
    }

    *pwFpgaAtt = wFpgaAtten;
    return wDetectPower;
}


WORD16 usp_uhf_rf_TransToFpgaAtten(WORD16 wAttenuation)
{
    WORD16 wDiff = 0;
    uhfRfDevPrint("uhfRf:Receive Attenuation %d\r\n", wAttenuation);
    wDiff = wAttenuation - wAttenuation / 50 * 50;

    if (wDiff < 25)
    {
        wAttenuation = wAttenuation / 50 * 50;
    }
    else
    {
        wAttenuation = (wAttenuation / 50 + 1) * 50;
    }

    wAttenuation = (wAttenuation < g_tRfInitPara.wMaxAtten) ? wAttenuation : g_tRfInitPara.wMaxAtten;
    uhfRfDevPrint("uhfRf:Transfer  Attenuation to  %d\r\n", wAttenuation);

    wAttenuation = ((wAttenuation / 100) << 1) | ((wAttenuation / 50) % 2);
    return (~wAttenuation) & (0x3F);
}

/**************************************************************************
* 函数名称: SetK0GetPower
* 功能描述:设置K0以后通过读取电压计算真是检测的功率
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:   检测到的功率值
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2007年7月27日          V1.0              XXXX                XXXX
**************************************************************************/

static WORD16 SetK0GetPower(WORD16 wK0, WORD16 wAntIndex)
{
    SWORD16 swPower;
    WORD16 wVoltage;
    WORD16 wLoop = 0;
    usp_uhf_rf_writeCtrlWord(wK0);
    /* 设置功率检测控制寄存器检测前向功率*/
    usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelForward);
    /* 打开功率检测ADC的时钟 */
    FpgaRegWrite(POWER_DETECT_ADC_CLK_CTRL, POWER_DETECT_ADC_CLK_ON);
    //usp_uhf_rf_setAmp(RF_AMP_ON);
    usleep(UHFRF_AC_WAIT_TIME);    /* 延时等待*/
    /* 获取电压值赋给wVoltage*/
    wVoltage = usp_uhf_rf_readDetectVal();
    swPower = usp_uhf_rf_ComputePower(wVoltage, wAntIndex, FORWARD_FLAG);
    uhfRfDevPrint("uhfRf:set K0 0x%x get voltage 0x%x power %d\r\n", wK0, wVoltage, swPower);

    if (swPower < 0)
    {
        uhfRfDevPrint("uhfRf:RF is Abnomal now \r\n");
        //LAPInsert(FILE_UHF_RFCTRL, USP_UHF_CLIBRITE_ABNORAML, swPower, 0);
        swPower = 0;
    }
    /* 关闭功率检测ADC的时钟 */
    FpgaRegWrite(POWER_DETECT_ADC_CLK_CTRL, POWER_DETECT_ADC_CLK_OFF);
    /*判断定标后功率是否超过额定功率*/
    return (WORD16)swPower;

}

/**************************************************************************
* 函数名称: usp_uhf_rf_AutoCalibrateInit
* 功能描述: 全局变量初始化
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2007年7月27日          V1.0              XXXX                XXXX
**************************************************************************/
void usp_uhf_rf_AutoCalibrateInit()
{
    WORD32 dwRcvLen = 0;
    BYTE ucPowerTableCount = 0;
#if EEPROM_SWITCH
    usp_drv_eeprom_rcv(POWER_TABLE_COUNT, 1, &ucPowerTableCount, &dwRcvLen);
#endif
    uhfRfDevPrint("uhfRf:ucPowerTableCount = %d\r\n", ucPowerTableCount);
    
    uhfRf_InitACData(ucPowerTableCount);
    memset(&g_atAntPower, 0, sizeof(g_atAntPower));
    g_atAntPower[0].ptPowerTable = &g_tUhfRfPowerTable1;
    g_atAntPower[1].ptPowerTable = &g_tUhfRfPowerTable1;
    g_atAntPower[2].ptPowerTable = &g_tUhfRfPowerTable2;
    
    if (FOUR_POWER_TABLE == ucPowerTableCount)
    {
        g_atAntPower[3].ptPowerTable = &g_tUhfRfPowerTable3;
        g_atAntPower[4].ptPowerTable = &g_tUhfRfPowerTable4;
    }
    else
    {
        g_atAntPower[3].ptPowerTable = &g_tUhfRfPowerTable2;
        g_atAntPower[4].ptPowerTable = &g_tUhfRfPowerTable1;
    }
    
}

/**************************************************************************
* 函数名称:
* 功能描述: 计算驻波比
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:驻波比*100(驻波比精确到小数点后两位)
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2008年9月13日          V1.0              XXXX                XXXX
**************************************************************************/
static WORD16 ComputeVSWR(WORD16 wPTarget, WORD16 wVoltage, WORD16 wAntIndex)
{
    SWORD16 swPower = 0;
    Double returnLoss = 0.0;
    Double dVSWR = 0.0;
    Double dPower = 0.0;

    dPower = (double)wPTarget / (double)100;

    swPower = usp_uhf_rf_ComputePower(wVoltage, wAntIndex, BACKWARD_FLAG);
    uhfRfDevPrint("uhfRf:Detect Power is %d\r\n", swPower);

    swPower += g_tRfInitPara.swRevCompensatePower;

    /*zdx modified  DBm2mW(-10) to DBm2mW(-8)*/
    if (swPower < -999)
    {
        dVSWR = 1.02;
    }
    else
    {
        returnLoss = (double)dPower - (MW2dBm(DBm2mW((double)swPower / (double)100) - DBm2mW(-10)) + g_tRfInitPara.wRcvCompensate);
        uhfRfDevPrint("uhfRf:returnLoss is %f\r\n", returnLoss);

        if (returnLoss < 1)
        {
            dVSWR = 100;
        }
        else if (returnLoss > 40)
        {
            dVSWR = 1.02;
        }
        else
        {
            dVSWR = (1 + pow(10, (returnLoss / (-20)))) / (1 - pow(10, (returnLoss / (-20))));
        }
    }


    if (dVSWR < 1.02)
    {
        dVSWR = 1.02;
        uhfRfDevPrint("uhfRf:~~~~~~VSWR Comput error !~~~~~~~~~\r\n");
    }

    uhfRfDevPrint("uhfRf:Backward Power = %d, wPTarget = %d\r\n", swPower, wPTarget);
    uhfRfDevPrint("uhfRf:ReturnLoss = %0.2f, VSWR = %0.2f\r\n", returnLoss, dVSWR);
    uhfRfDevPrint("uhfRf:come in ComputeVSWR out\r\n");
    return (WORD16)(dVSWR * 100);
}

/**************************************************************************
* 函数名称:
* 功能描述: 从EEPROM中读取20dbm的控制字和功率电压对照表
* 访问的表:
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2008年9月13日          V1.0              XXXX                XXXX
**************************************************************************/
static void uhfRf_InitACData(BYTE ucTableCount)
{
    WORD32 dwRet = USP_SUCCESS;
    /*第一次的数据总认为成功*/
    dwRet = usp_uhf_rf_readPowerTable(&g_tUhfRfPowerTable1, UHF_RF_PT_ANT14);
    if (USP_SUCCESS != dwRet)
    {
        /*将K0值设置为0保护以后的流程不发功率*/
        g_tUhfRfPowerTable1.wK0 = 0;
    }

    dwRet = usp_uhf_rf_readPowerTable(&g_tUhfRfPowerTable2, UHF_RF_PT_ANT23);

    if (USP_SUCCESS != dwRet)
    {
        memcpy(&g_tUhfRfPowerTable2, &g_tUhfRfPowerTable1,
               sizeof(T_USPUHFRfPowerTable));
    }

    if (FOUR_POWER_TABLE == ucTableCount)
    {
        dwRet = usp_uhf_rf_readPowerTable(&g_tUhfRfPowerTable3, UHF_RF_PT_ANT3);
        if (USP_SUCCESS != dwRet)
        {
            memcpy(&g_tUhfRfPowerTable3, &g_tUhfRfPowerTable2,
                   sizeof(T_USPUHFRfPowerTable));
        }

        dwRet = usp_uhf_rf_readPowerTable(&g_tUhfRfPowerTable4, UHF_RF_PT_ANT4);

        if (USP_SUCCESS != dwRet)
        {
            memcpy(&g_tUhfRfPowerTable4, &g_tUhfRfPowerTable1,
                   sizeof(T_USPUHFRfPowerTable));
        }
    }

#if ((UHF_BOARD_TYPE == BOARD_TYPE_RFCB_BT) || (UHF_BOARD_TYPE == BOARD_TYPE_RFCB7))
    /* 从EEPROM中读取栅压值 */
    dwRet = usp_uhf_rf_readGateVoltageValue(&g_tUhfGateVoltageCtrl);

    if (USP_SUCCESS != dwRet)
    {
        g_tUhfGateVoltageCtrl.wGateVoltage0 = UHF_RF_GATE_VOL_DEFAULT0;
        g_tUhfGateVoltageCtrl.wGateVoltage1 = UHF_RF_GATE_VOL_DEFAULT1;
    }
#endif

#if UHF_RF_ADJUST_PR_BALANCE
    dwRet = usp_uhf_rf_readPRData(&g_tUhfRfPowerTable1, UHF_RF_PT_ANT14);

    if (USP_SUCCESS != dwRet)
    {
        g_tUhfRfPowerTable1.wPR1Value = g_tRfInitPara.wPraskDefaultHigh;
        g_tUhfRfPowerTable1.wPR2Value = g_tRfInitPara.wPraskDefaultLow;
        g_tUhfRfPowerTable1.swMinK0   = 0;
    }

    dwRet = usp_uhf_rf_readPRData(&g_tUhfRfPowerTable2, UHF_RF_PT_ANT23);

    if (USP_SUCCESS != dwRet)
    {
        g_tUhfRfPowerTable2.wPR1Value = g_tUhfRfPowerTable1.wPR1Value;
        g_tUhfRfPowerTable2.wPR2Value = g_tUhfRfPowerTable1.wPR2Value;
        g_tUhfRfPowerTable2.swMinK0   = g_tUhfRfPowerTable1.swMinK0;
    }

    g_tUhfRfPowerTable3.wPR1Value = g_tUhfRfPowerTable2.wPR1Value;
    g_tUhfRfPowerTable3.wPR2Value = g_tUhfRfPowerTable2.wPR2Value;
    g_tUhfRfPowerTable3.swMinK0   = g_tUhfRfPowerTable2.swMinK0;

    g_tUhfRfPowerTable4.wPR1Value = g_tUhfRfPowerTable1.wPR1Value;
    g_tUhfRfPowerTable4.wPR2Value = g_tUhfRfPowerTable1.wPR2Value;
    g_tUhfRfPowerTable4.swMinK0   = g_tUhfRfPowerTable1.swMinK0;
#else
    /*如果没有配置则采用默认的值*/
    g_tUhfRfPowerTable1.wPR1Value = g_tRfInitPara.wPraskDefaultHigh;
    g_tUhfRfPowerTable1.wPR2Value = g_tRfInitPara.wPraskDefaultLow;
    g_tUhfRfPowerTable1.swMinK0   = 0;

    g_tUhfRfPowerTable2.wPR1Value = g_tRfInitPara.wPraskDefaultHigh;
    g_tUhfRfPowerTable2.wPR2Value = g_tRfInitPara.wPraskDefaultLow;
    g_tUhfRfPowerTable2.swMinK0   = 0;

    g_tUhfRfPowerTable3.wPR1Value = g_tRfInitPara.wPraskDefaultHigh;
    g_tUhfRfPowerTable3.wPR2Value = g_tRfInitPara.wPraskDefaultLow;
    g_tUhfRfPowerTable3.swMinK0   = 0;

    g_tUhfRfPowerTable4.wPR1Value = g_tRfInitPara.wPraskDefaultHigh;
    g_tUhfRfPowerTable4.wPR2Value = g_tRfInitPara.wPraskDefaultLow;
    g_tUhfRfPowerTable4.swMinK0   = 0;

#endif

}

/**************************************************************************
* 函数名称: uhfRf_setCalibrateFreq
* 功能描述: 在功率配置前设置所需要的频率，以epc的为准
* 访问的表: 无
* 修改的表:
* 输入参数:
* 输出参数:
* 返回值:
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  2008年9月13日          V1.0              XXXX                XXXX
**************************************************************************/
///// need to be FIXED ??
static WORD32 uhfRf_setCalibrateFreq(WORD16 wAntIndex)
{
    g_tRfCtrl.dwWorkFreq = uhfRf_ConvChannelToFreq(
                               uhfRf_getFreqWorkChannel(wAntIndex, UHF_RF_PROTOCOL_EPC),
                               uhfRf_getFreqTableId(wAntIndex, UHF_RF_PROTOCOL_EPC));
    return usp_uhf_rf_setPLLFreq(g_tRfCtrl.dwWorkFreq);

}

void SendAntAbnoramlAlarm(WORD16 wAntIndex, WORD32 dwAlarmType)
{

    uhfRfDevPrint("Ant %d don't present.\r\n", wAntIndex);

    /* 上报告警,返回天线功率和状态*/
    if (1 == wAntIndex)
    {
        uhf_amp_report(dwAlarmType,
                       R_RF_AC_ANT1_VSWR_PROTECTED_ALARM, 0,
                       USP_OAM_AMP_ALARM_LEVEL_FATAL, NULL, 0);
    }
    else if (2 == wAntIndex)
    {
        uhf_amp_report(dwAlarmType,
                       R_RF_AC_ANT2_VSWR_PROTECTED_ALARM, 0,
                       USP_OAM_AMP_ALARM_LEVEL_FATAL, NULL, 0);
    }
    else if (3 == wAntIndex)
    {
        uhf_amp_report(dwAlarmType,
                       R_RF_AC_ANT3_VSWR_PROTECTED_ALARM, 0,
                       USP_OAM_AMP_ALARM_LEVEL_FATAL, NULL, 0);
    }
    else
    {
        uhf_amp_report(dwAlarmType,
                       R_RF_AC_ANT4_VSWR_PROTECTED_ALARM, 0,
                       USP_OAM_AMP_ALARM_LEVEL_FATAL, NULL, 0);
    }

}


void SendAntABSAlarm(BYTE ucAntIndex)
{
    // char ucSprintfBuf[50] = {0};    /* 上报告警的信息，长度不超过49个字符 */
    // BYTE ucSprintfLen = 0;
    uhfRfDevPrint("Ant %d don't present.\r\n", ucAntIndex);
    /* 上报告警,返回天线功率和状态*/
    SendAlarm
}


static WORD32 uhfRf_SetRfPower(WORD16 wAntIndex, WORD16 wPower)
{
    /*当前天线的功率值发生改变是需要重新定标*/
    WORD32 dwRet = USP_SUCCESS;

    if (wPower < UHF_RF_MIN_POWER || wPower > g_tRfInitPara.wMaxPower)
    {
        uhfRfDevPrint("uhfRf: rcv power %ddb abnormal\r\n", wPower);
        return USP_UHF_RF_POWER_EXCEEDED;
    }

    if (NULL == usp_uhf_rf_FindPowerEntry(wAntIndex, wPower))
    {
        dwRet = usp_uhf_rf_autoCalibrate(wAntIndex, wPower);
        uhfRfDevPrint("uhfRf:invent autocalibrate power %ddb\r\n", wPower);

        if (USP_SUCCESS != dwRet)
        {
            uhfRfDevPrint("uhfRf:invent autocalibrate failed!\r\n");
            return dwRet;
        }
        
    }

    /* 设置射频发送功率 ，写入K0的过程，如果RO下发的功率值发生了变化，要重新定标*/
    dwRet = usp_uhf_rf_setTxPower(wAntIndex, wPower);

    if (USP_SUCCESS != dwRet)
    {
        return dwRet;
    }

    return USP_SUCCESS;
}


/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_setPLLFreq(WORD32 dwRfFreq)
* 功能描述：PLL锁相环配置
* 访问的表：无
* 修改的表：无
* 输入参数：WORD32 dwRfFreq : PLL工作频率
* 输出参数：
* 返 回 值：WORD32
                         0：    成功
                      其他：    失败

* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
WORD32 usp_uhf_rf_setPLLFreq(WORD32 dwRfFreq)
{

    WORD32 dwRetVal = USP_SUCCESS;
    WORD16 wNeedReset = PLL_NO_NEED_RESET;
    /*上电时候的锁相环失锁不记入异常*/
    static WORD16 wPllConfigStatus = UHF_RF_PLL_NOT_CONFIGED;
    WORD16 wAmpState = RF_AMP_OFF;
	DEBUG_MSG("usp_uhf_rf_setPLLFreq start\n");
	fflush(stdout);

    uhfRfDevPrint("uhfRf:uhfrf Frequence %d\r\n", dwRfFreq);

    wNeedReset = uhfRf_CheckPLLStatus(&wPllConfigStatus);/* 检测锁相环状态 */
   
    if ((dwRfFreq == g_tRfCtrl.dwPllWorkFreq) && (wNeedReset != PLL_NEED_RESET))
    {
        return USP_SUCCESS;
    }
	DEBUG_MSG("uhfRf_GetAmpState start\n");
	fflush(stdout);

    /*硬件需求在功率配置时关闭功放电源2009.9.9*/
    wAmpState = uhfRf_GetAmpState();
	DEBUG_MSG("usp_uhf_rf_setAmp start\n");
	fflush(stdout);
    usp_uhf_rf_setAmp(RF_AMP_OFF);
	DEBUG_MSG("uhfRf_PLLChipCfg start\n");
	fflush(stdout);
    dwRetVal = uhfRf_PLLChipCfg(dwRfFreq, wNeedReset);
    usp_uhf_rf_setAmp(wAmpState);
	DEBUG_MSG("usp_uhf_rf_setAmp end\n");
	fflush(stdout);

    if (dwRetVal != 0)
    {
        uhfRfDevPrint("uhfRf:hardware PLL config fail\r\n");
        g_tRfCtrl.dwPllWorkFreq = 0;
        LAPInsert(FILE_FPGAAPI, USP_UHF_PLL_LOSE, dwRetVal, 0);
    }
    else
    {
        g_tRfCtrl.dwPllWorkFreq = dwRfFreq;
        uhfRfDevPrint("uhfRf:hardware PLL config success\r\n");
    }

    /* 配置锁相环完成后，再次检测锁相环是否失锁 */
    uhfRf_CheckPLLStatus(&wPllConfigStatus);

    return dwRetVal;

}
/**********************************************************************
* 函数名称：uhfRf_CheckPLLStatus
* 功能描述：查看PLL的状态
* 访问的表：无
* 修改的表：无
* 输入参数：WORD16 *wPLLConfigStatus: 锁相环是否配置过
* 输出参数：
* 返 回 值：是否需要重新配置锁相环

* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2012/8/31             宗杰        创建  
************************************************************************/
WORD16 uhfRf_CheckPLLStatus(WORD16 *pwPLLConfigStatus)
{
    WORD32 dwRetVal = USP_SUCCESS;
    static WORD16 wPLLAlarmFlag = PLL_NO_ALARM;
    WORD16 wPLLResetStatus = PLL_NO_NEED_RESET;
	DEBUG_MSG("uhfRf_CheckPLLStatus start\n");
	fflush(stdout);

    if (UHF_RF_PLL_NOT_CONFIGED == *pwPLLConfigStatus)/* 锁相环之前没有配置过 */
    {
		DEBUG_MSG("UHF_RF_PLL_NOT_CONFIGED == *pwPLLConfigStatus\n");
		fflush(stdout);
        wPLLResetStatus = PLL_NEED_RESET;/* 必须重新配置 */
        *pwPLLConfigStatus = UHF_RF_PLL_CONFIGED;
    }
    else
    {
    /* 检测锁相环的状态 */
    dwRetVal = uhfRf_getPLLStatus();


    if (RF_PLL_STATUS_OK != dwRetVal)
    {
            /* PLL状态不对，需要重新配置 */
        uhfRfDevPrint("\r\nuhfRf:RF PLL should be lock but loesed !!! \r\n\r\n");
            /* PLL工作过程中检测到应该锁定而没有锁定的次*/
            LAPInsert(FILE_RFCB, USP_UHF_PLL_LOSE, dwRetVal, 0);
            /* 发送告警 */
            uhf_amp_report(EV_USP_OAM_AMP_AlarmReport,
                           R_RF_PLL_BEING_LOSED_ALARM, 0,
                           USP_OAM_AMP_ALARM_LEVEL_FATAL, NULL, 0);
            wPLLAlarmFlag = PLL_ALARMED;

        /* 重新配置全部寄存器，而不是只配置N Counter */
            wPLLResetStatus = PLL_NEED_RESET;
    }
    else
    {
        /* PLL状态OK  */
        if (PLL_ALARMED == wPLLAlarmFlag)
        {
            uhf_amp_report(EV_USP_OAM_AMP_AlarmRestoreReport,
                           R_RF_PLL_BEING_LOSED_ALARM, 0,
                           USP_OAM_AMP_ALARM_LEVEL_FATAL, NULL, 0);
            wPLLAlarmFlag = PLL_NO_ALARM;
        }
    }
    }

    return wPLLResetStatus;
}

/**********************************************************************
* 函数名称：uhfRf_getPRMinK0
* 功能描述：返回包络不平衡后调节后的PR DAC的high值
* 访问的表：无
* 修改的表：无
* 输入参数：wAntIndex 天线号
* 输出参数：
* 返 回 值：WORD16 存储的PR值

* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2012/3/5  赵董兴         创建  RUP平台化
************************************************************************/

WORD16 uhfRf_getPRMinK0(WORD16 wAntIndex)
{
    return g_atAntPower[wAntIndex].ptPowerTable->swMinK0;
}


/**********************************************************************
* 函数名称：uhfRf_getPRDacHigh
* 功能描述：返回包络不平衡后调节后的PR DAC的high值
* 访问的表：无
* 修改的表：无
* 输入参数：wAntIndex 天线号
* 输出参数：
* 返 回 值：WORD16 存储的PR值

* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2012/3/5  赵董兴         创建  RUP平台化
************************************************************************/

WORD16 uhfRf_getPRDacHigh(WORD16 wAntIndex)
{
    return g_atAntPower[wAntIndex].ptPowerTable->wPR1Value;
}


/**********************************************************************
* 函数名称：uhfRf_getPRDacHigh
* 功能描述：返回包络不平衡后调节后的PR DAC的low值
* 访问的表：无
* 修改的表：无
* 输入参数：wAntIndex 天线号
* 输出参数：
* 返 回 值：WORD16 存储的PR值

* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2012/3/5  赵董兴         创建  RUP平台化
************************************************************************/

WORD16 uhfRf_getPRDacLow(WORD16 wAntIndex)
{
    return g_atAntPower[wAntIndex].ptPowerTable->wPR2Value;
}


/**********************************************************************
* 函数名称：uhfRf_InitCtrlStruct
* 功能描述：初始化射频的参数
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：

* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2012/3/5  赵董兴         创建  RUP平台化
************************************************************************/

void uhfRf_InitCtrlStruct()
{
    BYTE ucForAntIndex = 0;
    memset(&g_tRfCtrl, 0x0, sizeof(g_tRfCtrl));

    for (ucForAntIndex = 0; ucForAntIndex < (READER_ANTENNA_COUNT + 1); ucForAntIndex++)
    {
        g_tRfCtrl.atRfAntCfg[ucForAntIndex].wRcvOrSnd = 3;
        g_tRfCtrl.atRfAntCfg[ucForAntIndex].aucAntPower[0] = 20;
    }

    g_tRfCtrl.wAntIndex = 1;

}
#endif

