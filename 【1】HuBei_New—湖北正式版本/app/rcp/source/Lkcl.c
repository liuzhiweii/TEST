#include "usp.h"
#if (UHF_PROTOCOL_USE)&&(UHF_BOARD_TYPE !=BOARD_TYPE_RBCB1)

#if (USP_UHF_LKCL_USE)
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf_rf.h"
#include "Board.h"
#include "RfCtl.h"
//#include "uhf_time.h"
#include "Lkcl.h"


extern T_UhfRfAntFreqHopCtrl g_tFreqHopCtrl[READER_ANTENNA_COUNT + 1];
extern T_RfCtrl        g_tRfCtrl;
extern T_RfInitPara    g_tRfInitPara;
T_USPUHFLKCLInitParas g_tInintLKCLAdj;
static T_InitPhase     g_InitPhase[] = UHF_RF_INIT_PHASE;
static T_SingleAntLKCLPara g_tReaderLKCLPara[READER_ANTENNA_COUNT + 1];
static WORD32 dwtemp;


/**************************************************************************
* 函数名称：uhfRf_initLKCLParas
* 功能描述：获取一个频率表泄露对消结果的存放空间
* 输入参数：wAntIndex 天线号
                                 wFreqTableID  频率表
 * 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/

void uhfRf_initLKCLParas(void)
{
   memset(g_tReaderLKCLPara, 0,
            sizeof(T_SingleAntLKCLPara) * (READER_ANTENNA_COUNT + 1));
}

/**************************************************************************
* 函数名称：uhfRf_getLKCLParas
* 功能描述：泄露对消值结果值的获取
* 输入参数：wAntIndex 天线号
                                 wFreqTableID  频率表
                                 wFreqChnnelNo  频道号
* 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/

static T_USPUHFLKCLParas *uhfRf_getLKCLParas(WORD16 wAntIndex, WORD16 wFreqTableID, WORD16 wFreqChnnelNo)
{

    WORD16 wLoopIndex = 0;

    /*没有对消过*/
    if (0 == g_tReaderLKCLPara[wAntIndex].wLKCLTableLen)
    {
        return NULL;
    }

    /*有对消结果看看是不是和当前的频率表一致*/
    for (wLoopIndex = 0;
         wLoopIndex < g_tReaderLKCLPara[wAntIndex].wLKCLTableLen; wLoopIndex++)
    {
        if (g_tReaderLKCLPara[wAntIndex].tSingleFreqTableLKCLPara[wLoopIndex].wHopTableID
            == wFreqTableID)
        {
            break;
        }
    }

    /*没有找到*/
    if (wLoopIndex >= g_tReaderLKCLPara[wAntIndex].wLKCLTableLen)
    {
        return NULL;
    }

    /*找到了*/
    return  &g_tReaderLKCLPara[wAntIndex]\
            .tSingleFreqTableLKCLPara[wLoopIndex].tAntLKCLPara[wFreqChnnelNo];

}

/**************************************************************************
* 函数名称：uhfRf_getFreqTableLKCLParas
* 功能描述：获取一个频率表泄露对消结果的存放空间
* 输入参数：wAntIndex 天线号
                                 wFreqTableID  频率表
 * 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/

T_SingleFreqTableLKCLPara *uhfRf_getFreqTableLKCLParas(WORD16 wAntIndex, WORD16 wFreqTableID)
{

    T_SingleFreqTableLKCLPara *ptFreqTableLkclTable = NULL;

    /*如果当前的频率已经进行过泄露对消了，则返回空指针*/
    if (NULL != uhfRf_getLKCLParas(wAntIndex, wFreqTableID, 0))
    {
        return NULL;
    }

    ptFreqTableLkclTable =
        &g_tReaderLKCLPara[wAntIndex]\
        .tSingleFreqTableLKCLPara[g_tReaderLKCLPara[wAntIndex].wLKCLIndex];

    g_tReaderLKCLPara[wAntIndex].wLKCLTableLen++;

    if (g_tReaderLKCLPara[wAntIndex].wLKCLTableLen > UHF_RF_MAX_LKCL_TABLE_LEN)
    {
        g_tReaderLKCLPara[wAntIndex].wLKCLTableLen = UHF_RF_MAX_LKCL_TABLE_LEN;
    }

    g_tReaderLKCLPara[wAntIndex].wLKCLIndex++;

    if (g_tReaderLKCLPara[wAntIndex].wLKCLIndex >= UHF_RF_MAX_LKCL_TABLE_LEN)
    {
        g_tReaderLKCLPara[wAntIndex].wLKCLTableLen = 0;
    }

    return ptFreqTableLkclTable;
}

/**************************************************************************
* 函数名称：void RFCB_SetLKCLInitPara(void)
* 功能描述：设置泄露对消的时的初始化参数
* 输入参数：无
* 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
void uhfRf_SetLKCLInitPara(void)
{
    WORD16  wLoop = 0;

    g_tInintLKCLAdj.wInitX0      = UHF_RF_LKCL_INIT_X0;
    g_tInintLKCLAdj.wInitX1      = UHF_RF_LKCL_INIT_X1;
    g_tInintLKCLAdj.wInitY0      = UHF_RF_LKCL_INIT_Y0;
    g_tInintLKCLAdj.wInitY1      = UHF_RF_LKCL_INIT_Y1;

    g_tInintLKCLAdj.dwAdjThrHold = UHF_RF_LKCL_ADJ_THRHOLD;

    g_tInintLKCLAdj.wIntegralMax = UHF_RF_LKCL_INTERG_MAX;
    g_tInintLKCLAdj.wIntegralMin = UHF_RF_LKCL_INTERG_MIN;

    g_tInintLKCLAdj.wInitcos     = UHF_RF_LKCL_INIT_COS;
    g_tInintLKCLAdj.wInitSin     = UHF_RF_LKCL_INIT_SIN;

    g_tInintLKCLAdj.wStopThd     = UHF_RF_LKCL_STOP_THD;
    g_tInintLKCLAdj.wFineThrHold = UHF_RF_LKCL_FINE_THRHOD;

    g_tInintLKCLAdj.wDacChange   = UHF_RF_LKCL_DAC_CHANGE;

    uhfRf_initLKCLParas();

    /*在阅读器启动的时候添加泄露对消的初始值*/
    FpgaRegWrite(s_x0_reg, g_tInintLKCLAdj.wInitX0);
    FpgaRegWrite(s_x1_reg, g_tInintLKCLAdj.wInitX1);
    FpgaRegWrite(s_y0_reg, g_tInintLKCLAdj.wInitY0);
    FpgaRegWrite(s_y1_reg, g_tInintLKCLAdj.wInitY1);

    FpgaRegWrite(s_integral_max, g_tInintLKCLAdj.wIntegralMax);
    FpgaRegWrite(s_integral_min, g_tInintLKCLAdj.wIntegralMin);

    FpgaRegWrite(s_dac_change, g_tInintLKCLAdj.wDacChange);

    FpgaRegWrite(s_threhold_val, g_tInintLKCLAdj.wStopThd);

    FpgaRegWrite(s_cos_theta, g_tInintLKCLAdj.wInitcos);
    FpgaRegWrite(s_sin_theta, g_tInintLKCLAdj.wInitSin);

    /*初始化为停止泄露对消状态同时
         将初始化的值写入并且保证在电压字校准的时候有时钟*/
    FpgaRegWrite(s_rfcl_start, 0);
    uhfRf_VAutoAdjust();

}

/**************************************************************************
* 函数名称：void uhfRf_ResetLKCLInitPara(void)
* 功能描述：设置泄露对消的时的初始化参数
* 输入参数：无
* 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
void uhfRf_VAutoAdjust(void)
{
    SWORD16 swAdcQ = 0;
    SWORD16 swAdcI = 0;
    SWORD32 sdwAdcValue = g_tRfInitPara.wLKCLAutoAdjInitVal;

    FpgaRegWrite(REG_LKCL_SWITCH, 1);
    usp_uhf_rf_setAmp(RF_AMP_OFF);
    usp_uhf_rf_txSet(UHF_RF_STOP_TX);
    usp_uhf_rf_setRevDatt(0);

    /*每次检测前需要初始化一下*/
    FpgaRegWrite(REG_I_LKCL_ADJ1, sdwAdcValue);
    FpgaRegWrite(REG_I_LKCL_ADJ2, sdwAdcValue);
    usleep(100000);

    swAdcI = FpgaRegRead(I_ADC_idata);
    swAdcQ = FpgaRegRead(I_ADC_qdata);
    printf("uhfRf:I %d q %d fixed value %d\r\n", swAdcI, swAdcQ, sdwAdcValue);
    swAdcI = sdwAdcValue + (swAdcI * 8);
    swAdcQ = sdwAdcValue + (swAdcQ * 8);
    printf("uhfRf:caculated i %x q %x\r\n", swAdcI, swAdcQ);
    FpgaRegWrite(REG_I_LKCL_ADJ1, swAdcI);
    FpgaRegWrite(REG_I_LKCL_ADJ2, swAdcQ);
}

/**************************************************************************
* 函数名称：static WORD32 uhfRf_SetLKCLFreq(WORD32 dwFreq)
* 功能描述：泄露对消的时候设置频率记录入频率的全局
                                 变量
* 输入参数：deFreq 设置的频率
* 输出参数：
* 返 回 值：    成功返回0其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
static WORD32 uhfRf_SetLKCLFreq(WORD32 dwFreq)
{
    g_tRfCtrl.dwWorkFreq = dwFreq;
    return usp_uhf_rf_setPLLFreq(g_tRfCtrl.dwWorkFreq);
}
/**************************************************************************
* 返 回 值：    成功返回0其他错误
* 函数名称：WORD32 RFCB_RFFreqLKCL(T_FreqHopCtrl *ptAntFreqHopCtrl, BYTE ucAntIndex)
* 功能描述：泄露对消流程处理，针对一根天线
* 输入参数：T_FreqHopCtrl *ptAntFreqHopCtrl 当前天线调频设置
                                     BYTE ucAntIndex  天线号
* 输出参数：
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 uhfRf_FreqLKCL(T_USPUHFFreqTableEntry *ptHopTable, BYTE ucAntIndex)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD16 wLoop = 0;
    WORD32 dwFreq = 0;
    WORD32 dwVswrAlarmVal = 0;
    T_SingleFreqTableLKCLPara *ptAntLKCLPara =
        uhfRf_getFreqTableLKCLParas(ucAntIndex, ptHopTable->wHopTableID);

    /*如果是NULL 说明已经对消过了*/
    if (NULL == ptAntLKCLPara)
    {
        uhfRfDevPrint("uhfRf: has been lkcled\r\n");
        return USP_SUCCESS;
    }

    uhfRfDevPrint("uhfRf:Ant index %d LKCLStart\r\n", ucAntIndex);
    ptAntLKCLPara->wHopTableID = ptHopTable->wHopTableID;

    dwRet = usp_uhf_rf_selectAnt(ucAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfRf:Rf antenna set failed!  dwRet = 0x%x\r\n", dwRet);
        return USP_UHF_RF_ANT_SET_ERROR;
    }

    /* 写入天线*/
    usp_uhf_rf_WriteAntDatt();
    
    dwRet = uhfRf_SetLKCLPower(ucAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        uhfRfDevPrint("uhfRf:Set 30DB Error happens use default!  dwRet = 0x%x\r\n", dwRet);
    }

    dwVswrAlarmVal = uhfRf_IsAntProtected();

    if (USP_UHF_ANT_IS_PROTECTED == dwVswrAlarmVal)
    {
        uhfRfDevPrint("uhfRf:Vswr is Protected Cannot LKCL\r\n");
        usp_uhf_rf_txSet(UHF_RF_STOP_TX);
        return USP_UHF_ANT_IS_PROTECTED;
    }
    uhfRf_SetLKCLSwitch(UHF_RF_FAST_LKCL_ON);
    usp_uhf_rf_txSet(UHF_RF_START_TX);

    /* 等待射频信号稳定 */
    //USP_OSS_VOS_SLEEP_USEC(1000); /*延时让射频稳定*/
    //usp_drv_timer_usleep(1500);
    
    while (wLoop < ptHopTable->wFrequeceNum)
    {
        dwFreq = ptHopTable->dwFrequeces[wLoop];
        dwRet = uhfRf_SetLKCLFreq(dwFreq);

        if (USP_SUCCESS != dwRet)
        {
            break;
        }

        /*设置定标成功后的K0和DATT*/
        uhfRf_SetLKCLPowerPara(ucAntIndex);
        //USP_OSS_VOS_SLEEP_USEC(1000); /*延时让射频稳定*/
        //usp_drv_timer_usleep(1500);
        
        dwRet = uhfRf_FPGALKCLProc(&g_tInintLKCLAdj,
                                   &ptAntLKCLPara->tAntLKCLPara[wLoop],
                                   &ptAntLKCLPara->wTryIndex);

        if (USP_SUCCESS != dwRet)
        {
            if (UHF_RF_LKCL_STOP_THD_STAGE2 != g_tInintLKCLAdj.wStopThd)
            {
                g_tInintLKCLAdj.dwAdjThrHold = UHF_RF_LKCL_ADJ_THRHOLD_STAGE2;
                g_tInintLKCLAdj.wStopThd = UHF_RF_LKCL_STOP_THD_STAGE2;

            }
            else
            {
                LAPInsert(FILE_RFCB2, USP_UHF_LKCL_FAILED, dwFreq, 0);
                uhfRfDevPrint("uhfRf:============lck Freq %d Failed===========\r\n", dwFreq);
                break;
            }
        }
        else
        {
            wLoop++;  /*转到下一个频点进行泄露对消*/
            uhfRfDevPrint("uhfRf:=========LKCL Freq %d Success stopthd %d=============\r\n", 
                                                   dwFreq,g_tInintLKCLAdj.wStopThd);

            /*每次对消都从最小的约束值开始*/
            g_tInintLKCLAdj.dwAdjThrHold = UHF_RF_LKCL_ADJ_THRHOLD;
            g_tInintLKCLAdj.wStopThd = UHF_RF_LKCL_STOP_THD;
        }
    }

    usp_uhf_rf_txSet(UHF_RF_STOP_TX);
    uhfRf_SetLKCLSwitch(UHF_RF_FAST_LKCL_OFF);
    return dwRet;
}
/**********************************************************************
* 函数名称：FPGALKCLProcTry
* 功能描述：针对一个角度进行泄露对消尝试,文件内函数
* 输入参数：T_USPUHFLKCLInitParas *ptInintLKCLAdj  泄露对消的初始化参数
                                 T_USPUHFLKCLParas *ptLKCLSetPara 对消成功后的记录值
* 输出参数：
* 返 回 值    ：成功返回0 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/12/12	        RUP平台化	    zdx	      创建
***********************************************************************/
WORD32 usp_uhf_rf_FPGALKCLProcTry(T_USPUHFLKCLInitParas *ptInintLKCLAdj,
                                    T_USPUHFLKCLParas *ptLKCLSetPara)
{
    WORD16 wDigLoop = 0;
    WORD16 wIsStoped = 0;
    WORD32 dwRet = USP_SUCCESS;
    SWORD16 swI0 = 0;
    SWORD16 swQ0 = 0;
    WORD32  dwI2Q20 = 0;

    FpgaRegWrite(s_x0_reg, ptInintLKCLAdj->wInitX0);
    FpgaRegWrite(s_x1_reg, ptInintLKCLAdj->wInitX1);
    FpgaRegWrite(s_y0_reg, ptInintLKCLAdj->wInitY0);
    FpgaRegWrite(s_y1_reg, ptInintLKCLAdj->wInitY1);

    FpgaRegWrite(s_integral_max, ptInintLKCLAdj->wIntegralMax);
    FpgaRegWrite(s_integral_min, ptInintLKCLAdj->wIntegralMin);

    FpgaRegWrite(s_dac_change, ptInintLKCLAdj->wDacChange);

    FpgaRegWrite(s_threhold_val, ptInintLKCLAdj->wStopThd);

    FpgaRegWrite(s_cos_theta, ptInintLKCLAdj->wInitcos);
    FpgaRegWrite(s_sin_theta, ptInintLKCLAdj->wInitSin);

    FpgaRegWrite(s_rfcl_start, 0x0);
    usleep(100);
    FpgaRegWrite(s_rfcl_start, 0x1);


    while (wDigLoop < UHF_RF_MAX_LKCL_ADJ_COUNT)
    {
        //usleep(50000);
        //USP_OSS_VOS_SLEEP_USEC(UHF_RF_LKCL_ADJ_RESOLUTION_TIME);
        wIsStoped = FpgaRegRead(I_stop);

        if (wIsStoped == 1)
        {
            swI0 = FpgaRegRead(I_ADC_idata);
            swQ0 = FpgaRegRead(I_ADC_qdata);
            dwI2Q20 = swI0 * swI0 + swQ0 * swQ0;
            uhfRfDevPrint("Fine LKCL Value %x\r\n", dwI2Q20);

            if (dwI2Q20 < ptInintLKCLAdj->dwAdjThrHold)
            {

                ptLKCLSetPara->wX0 = FpgaRegRead(I_i1_data);
                ptLKCLSetPara->wX1 = FpgaRegRead(I_i2_data);
                ptLKCLSetPara->wY0 = FpgaRegRead(I_q1_data);
                ptLKCLSetPara->wY1 = FpgaRegRead(I_q2_data);

                FpgaRegWrite(s_x0_reg, ptLKCLSetPara->wX0);
                FpgaRegWrite(s_x1_reg, ptLKCLSetPara->wX1);
                FpgaRegWrite(s_y0_reg, ptLKCLSetPara->wY0);
                FpgaRegWrite(s_y1_reg, ptLKCLSetPara->wY1);
                
                /*设置每个频点的微调角度*/
                ptLKCLSetPara->wInitCos = ptInintLKCLAdj->wInitcos;
                ptLKCLSetPara->wInitSin = ptInintLKCLAdj->wInitSin;

                uhfRfDevPrint("uhfRf:lkcl loop %d reslts %x %x %x %x\r\n",wDigLoop, ptLKCLSetPara->wX0,
                           ptLKCLSetPara->wX1, ptLKCLSetPara->wY0, ptLKCLSetPara->wY1);

                ptLKCLSetPara->wIsCrossed = FpgaRegRead(s_dac_change);
                ptLKCLSetPara->wIsConfiged = 1;

                FpgaRegWrite(s_rfcl_start, 0x2);
                break;
            }
            else
            {
                uhfRfDevPrint("uhfRf:eb is 1 but e5 e6 not right\r\n");
            }
        }

        wDigLoop++;
        uhfRfDevPrint("%d", wIsStoped);
    }

    if (wDigLoop >= UHF_RF_MAX_LKCL_ADJ_COUNT)
    {
        uhfRfDevPrint("uhfRf:LKCL Failed\r\n");
        FpgaRegWrite(s_rfcl_start, 0x2);
        ptLKCLSetPara->wIsConfiged = 0;

        dwRet = FPGA_RFADJ_CANNOT_STOP;
    }

    return dwRet;
}

/**************************************************************************
* 函数名称：static WORD32 uhfRf_FPGALKCLProc(T_USPUHFLKCLInitParas *ptInintLKCLAdj,
                                  T_USPUHFLKCLParas *ptLKCLSetPara,
                                  WORD16 *pwTryindex)
* 功能描述：针对一个频率进行一次泄露对消尝试
* 输入参数：T_LKCLInitParas *ptInintLKCLAdj 泄露对消初始化参数
                                 T_LKCLParas *ptLKCLSetPara  泄露对消成功后存入此结构中

* 输出参数：
* 返 回 值：    成功返回0   其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 uhfRf_FPGALKCLProc(T_USPUHFLKCLInitParas *ptInintLKCLAdj,
                                 T_USPUHFLKCLParas *ptLKCLSetPara,
                                 WORD16 *pwTryindex)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD16 wLoopCount = 0;
    WORD16 wLoop = 0;

    /*wLoopCount 代表所要搜索的角度的个数,同时也是角度的索引*/
    wLoopCount = sizeof(g_InitPhase) / sizeof(T_InitPhase);

    for (wLoop = 0; wLoop < wLoopCount; wLoop++, (*pwTryindex)++)
    {
        if (*pwTryindex >= wLoopCount)
        {
            *pwTryindex = 0;
        }

        ptInintLKCLAdj->wInitcos = g_InitPhase[(*pwTryindex)].swCos;
        ptInintLKCLAdj->wInitSin = g_InitPhase[(*pwTryindex)].swSin;
        uhfRfDevPrint("uhfRf:Try cos %d  sin %d \r\n", ptInintLKCLAdj->wInitcos, ptInintLKCLAdj->wInitSin);
        dwRet = usp_uhf_rf_FPGALKCLProcTry(ptInintLKCLAdj, ptLKCLSetPara);

        if (dwRet != USP_SUCCESS)
        {
            continue;

        }
        else
        {
            break;
        }

    }

    if (wLoop >= wLoopCount)
    {
        dwRet = FPGA_RFADJ_CANNOT_STOP;
    }

    return dwRet;
}
/**************************************************************************
* 函数名称：WORD32 uhfRf_FineLKCL(BYTE ucAntIndex, T_FreqHopCtrl *ptFreqHopCtrl)
* 功能描述：清点的时候发现泄露变大需要进行泄露对消微调
* 输入参数：BYTE ucAntIndex 天线号
                                T_FreqHopCtrl *ptFreqHopCtrl
                                此变量主要是确定是否进行了频率配置的改变
* 输出参数：
* 返 回 值：    成功返回0   其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
* -----------------------------------------------
* 12/01/16	     V05.00.00	    宗杰      根据硬件要求，将6600C1/C2快速泄漏对消关闭
**************************************************************************/

WORD32 uhfRf_FineLKCL(BYTE ucAntIndex, T_UhfRfFreqHopCtrl *ptFreqHopCtrl)
{
    T_USPUHFLKCLParas *ptLKCLSetPara = NULL;
    WORD32  dwRet = USP_SUCCESS;
    SWORD16 swI0 = 0;
    SWORD16 swQ0 = 0;
    WORD32  dwI2Q20 = 0;
    WORD32  dwI2Q21 = 0;

    ptLKCLSetPara =
        uhfRf_getLKCLParas(ucAntIndex, ptFreqHopCtrl->wFreqTableID,
                           ptFreqHopCtrl->wWorkChannel);

    uhfRfDevPrint("uhfRf:Ant %d WorkChannel %d\r\n", ucAntIndex,
                  ptFreqHopCtrl->wWorkChannel);

    /*当此频点没有配置或者和对消时使用HopTableID不一致时*/
    if ((NULL == ptLKCLSetPara)
        || (ptLKCLSetPara->wIsConfiged == 0))
    {
        FpgaRegWrite(s_x0_reg, 0x7fff);
        FpgaRegWrite(s_x1_reg, 0x7fff);
        FpgaRegWrite(s_y0_reg, 0x7fff);
        FpgaRegWrite(s_y1_reg, 0x7fff);

        FpgaRegWrite(s_rfcl_start, 0);
#if (!USP_IS_DISTRIBUTED)
       usp_uhf_rf_txSet(UHF_RF_START_TX);
       
       //USP_OSS_VOS_SLEEP_USEC(UHF_RF_LKCL_WAIT_TIME);
       //usp_drv_timer_usleep(1520);
#endif
    }
    else
    {
        usp_uhf_rf_txSet(UHF_RF_START_TX);

    #if UHF_BOARD_TYPE != BOARD_TYPE_RFCB7
        /* 6600C1/C2不打开快速泄漏对消 */
        uhfRf_SetLKCLSwitch(UHF_RF_FAST_LKCL_ON);
    #endif
        FpgaRegWrite(s_x0_reg, ptLKCLSetPara->wX0);
        FpgaRegWrite(s_x1_reg, ptLKCLSetPara->wX1);
        FpgaRegWrite(s_y0_reg, ptLKCLSetPara->wY0);
        FpgaRegWrite(s_y1_reg, ptLKCLSetPara->wY1);
        uhfRfDevPrint("uhfRf:X0 0x%x  X1 0x%x Y0 0x%x Y1 0x%x\r\n", ptLKCLSetPara->wX0,
                      ptLKCLSetPara->wX1, ptLKCLSetPara->wY0, ptLKCLSetPara->wY1);

        FpgaRegWrite(s_rfcl_start, 0);
        /*RFCB2 400us    PURM RFCB  1.5ms*/
        //USP_OSS_VOS_SLEEP_USEC(UHF_RF_LKCL_RX_OPEN_WAIT_TIME);
        
        swI0 = FpgaRegRead(I_ADC_idata);
        swQ0 = FpgaRegRead(I_ADC_qdata);
        dwI2Q20 = swI0 * swI0 + swQ0 * swQ0;

        uhfRfDevPrint("uhfRf:Fine LKCL Value i %d  q %d i2q2 %d\r\n", swI0, swQ0, dwI2Q20);

        if (dwI2Q20 > g_tInintLKCLAdj.dwAdjThrHold)
        {
            uhfRfDevPrint("uhfRf:Need to Fine LKCL Para Cnt %d\r\n",
                          ptLKCLSetPara->wCheckFineCnt);
            ptLKCLSetPara->wCheckFineCnt++;

            if (ptLKCLSetPara->wCheckFineCnt > g_tInintLKCLAdj.wFineThrHold)
            {
                uhfRfDevPrint("uhfRf:Fine LKCL \r\n");


                FpgaRegWrite(s_cos_theta, ptLKCLSetPara->wInitCos);
                FpgaRegWrite(s_sin_theta, ptLKCLSetPara->wInitSin);

                uhfRfDevPrint("uhfRf:Cos %d sin %d",ptLKCLSetPara->wInitCos,ptLKCLSetPara->wInitSin);
                FpgaRegWrite(s_rfcl_start, 1);
                //USP_OSS_VOS_SLEEP_USEC(UHF_RF_LKCL_FINE_WAIT_TIME); /*1ms*/
                swI0 = FpgaRegRead(I_ADC_idata);
                swQ0 = FpgaRegRead(I_ADC_qdata);
                dwI2Q21 = swI0 * swI0 + swQ0 * swQ0;
                uhfRfDevPrint("uhfRf:Fine LKCL dwI2Q21 = %d\r\n", dwI2Q21);

                if (dwI2Q21 <= dwI2Q20)
                {
                    uhfRfDevPrint("uhfRf:Fine LKCL success\r\n");
                    ptLKCLSetPara->wX0 = FpgaRegRead(I_i1_data);
                    ptLKCLSetPara->wX1 = FpgaRegRead(I_i2_data);
                    ptLKCLSetPara->wY0 = FpgaRegRead(I_q1_data);
                    ptLKCLSetPara->wY1 = FpgaRegRead(I_q2_data);
                    ptLKCLSetPara->wCheckFineCnt = 0;
                }
                else
                {
                    uhfRfDevPrint("uhfRf:Fine LKCL Failed\r\n");
                    FpgaRegWrite(s_x0_reg, ptLKCLSetPara->wX0);
                    FpgaRegWrite(s_x1_reg, ptLKCLSetPara->wX1);
                    FpgaRegWrite(s_y0_reg, ptLKCLSetPara->wY0);
                    FpgaRegWrite(s_y1_reg, ptLKCLSetPara->wY1);

                    FpgaRegWrite(s_rfcl_start, 0);
                    //USP_OSS_VOS_SLEEP_USEC(UHF_RF_LKCL_RX_OPEN_WAIT_TIME); /*300us*/
                }
            }
        }
        else
        {
            ptLKCLSetPara->wCheckFineCnt = 0;
            uhfRfDevPrint("uhfRf:No need to Fine LKCL Para\r\n");
        }
        uhfRf_SetLKCLSwitch(UHF_RF_FAST_LKCL_OFF);
#if USP_IS_DISTRIBUTED
        /*RFCB2需要关闭单音发送，由数字板再控制信号发送*/
        usp_uhf_rf_txSet(UHF_RF_STOP_TX);
#endif
        
    }

    FpgaRegWrite(s_rfcl_start, 2);

    return  dwRet;
}


/**********************************************************************
* 函数名称：void uhfRf_ReaderLKCLProc()
* 功能描述：对各个天线进行泄露对消
* 输入参数：无
* 输出参数：
            成功：0
            失败：错误码
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2009/12/1           V5.0.0           zdx            创建
************************************************************************/
#define LKCLPOWER 3000
void uhfRf_ReaderLKCLProc()
{
    WORD16 wAntIndex = 1;
    T_USPUHFFreqTableEntry *ptHopTable = NULL;
    WORD32 dwRet = USP_SUCCESS;

    for (wAntIndex = 1; wAntIndex <= READER_ANTENNA_COUNT; wAntIndex++)
    {
        dwRet = usp_uhf_rf_getAntStatus(wAntIndex);

        if (USP_SUCCESS == dwRet)
        {

            ptHopTable =
                uhfRf_GetHopTable(g_tFreqHopCtrl[wAntIndex].tEpcFreqHopCtrl.wFreqTableID);

            if (ptHopTable != NULL)
            {
                uhfRf_FreqLKCL(ptHopTable, wAntIndex);
            }

            ptHopTable =
                uhfRf_GetHopTable(g_tFreqHopCtrl[wAntIndex].tGBFreqHopCtrl.wFreqTableID);

            if (ptHopTable != NULL)
            {
                uhfRf_FreqLKCL(ptHopTable, wAntIndex);
            }
            
            ptHopTable =
                uhfRf_GetHopTable(g_tFreqHopCtrl[wAntIndex].tIso6BFreqHopCtrl.wFreqTableID);

            if (ptHopTable != NULL)
            {
                uhfRf_FreqLKCL(ptHopTable, wAntIndex);
            }
        }
        else
        {
            uhfRfDevPrint("uhfRf:No Need to LKCL Ant%d is absent!\r\n", wAntIndex);
        }
    }
}

#else
#include "Board.h"
#include "uhf_rf.h"
#include "RfCtl.h"

void uhfRf_ReaderLKCLProc()
{

}

WORD32 uhfRf_FineLKCL(BYTE ucAntIndex, T_UhfRfFreqHopCtrl *ptFreqHopCtrl)
{
    usp_uhf_rf_txSet(UHF_RF_START_TX);
    /*1.5ms 的射频延时，保证稳定和标签启动*/
    //USP_OSS_VOS_SLEEP_USEC(UHF_RF_LKCL_WAIT_TIME);
    //usp_drv_timer_usleep(1520);
    return USP_SUCCESS;
}
#endif


#endif
