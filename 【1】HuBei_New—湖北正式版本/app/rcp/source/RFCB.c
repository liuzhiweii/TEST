/************************************************************************
* 版权所有 (C)2011, 中兴通讯天津研究所
*
* 文件名称：RFCB.c
* 文件标识：
* 内容摘要：针对硬件小改版增加泄露对消后修改
* 其它说明：
* 当前版本： ZXRIS6700 V04.00.00
* 作    者：zdx
* 完成日期：2011-01-10
*
* 修改记录1：
*    修改日期：20120316
*    版 本 号：  RUP
*    修 改 人： 对其中的函数进行的很大的修改
*    修改内容：
* 修改记录2：…
************************************************************************/
#include "usp.h"
#if (UHF_PROTOCOL_USE) &&((UHF_BOARD_TYPE == BOARD_TYPE_RFCB) || (UHF_BOARD_TYPE == BOARD_TYPE_RFCB_BT))
#include "uhf_trace.h"
#include "uhf_dbg.h"
#include "uhf_rf.h"
#include "Board.h"
#include "RfCtl.h"
//#include "uhf_time.h"
#include "uhfFpgaRegDef.h"
#define	IO_SWITCH  0
static T_I2CValue g_tI2CValue;
static T_I2CFunValue g_tI2CFunValue;

static WORD32 InitI2CValue(void);
static WORD32 InitI2CFucValue(void);

extern T_UhfRfAntFreqHopCtrl g_tFreqHopCtrl[READER_ANTENNA_COUNT + 1];             /* 跳频控制 */
extern T_RfCtrl      g_tRfCtrl;
extern T_RfInitPara  g_tRfInitPara;
extern T_USPUHFGateVoltageCtrl  g_tUhfGateVoltageCtrl;

/**************************************************************************
* 函数名称：WORD32 InitI2CValue(void)
* 功能描述：初始化I2C总线上射频相关地址的值，
                                 用来当需要写入I2C数据时进行比较
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
                                 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
*11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
static void uhfRf_SetInitPara(void)
{
    g_tRfInitPara.w20DBAtten          = UHF_RF_20DB_FPGA_ATTEN;
    g_tRfInitPara.wAntOnlineThr       = UHF_RF_ANT_ONLINE_VALUE;
    g_tRfInitPara.wClibrateWaitTime   = UHF_RF_CLIBRATE_SLEEP;
    g_tRfInitPara.swForCompensatePower = RF_FOR_COMPENSATE_POWER;
    g_tRfInitPara.swRevCompensatePower = RF_REV_COMPENSATE_POWER;
    g_tRfInitPara.wFullPower          = UHF_RF_FULL_POWER;
    g_tRfInitPara.wMaxAtten           = UHF_RF_MAX_ATTEN;
    g_tRfInitPara.wMinAtten           = UHF_RF_MIN_ATTEN;
    g_tRfInitPara.wMaxK0              = UHF_RF_MAX_K0;
    g_tRfInitPara.wPraskDefaultHigh   = RF_PRASK_DAC_DEFAULT_HIGH_VALUE;
    g_tRfInitPara.wPraskDefaultLow    = RF_PRASK_DAC_DEFAULT_LOW_VALUE;
    g_tRfInitPara.wPraskMax           = RF_PRASK_DAC_MAX_VALUE;
    g_tRfInitPara.wPraskMin           = RF_PRASK_DAC_MIN_VALUE;
    g_tRfInitPara.wRcvCompensate      = UHF_RF_RVE_COPENSATE;
    g_tRfInitPara.wLKCLAutoAdjInitVal = UHF_RF_LKCL_AUTO_ADJ_INIT_VAL;
    g_tRfInitPara.wMaxPower           = UHF_RF_MAX_POWER;
    g_tRfInitPara.wGateVolDefault0    = UHF_RF_GATE_VOL_DEFAULT0;
    g_tRfInitPara.wGateVolDefault1    = UHF_RF_GATE_VOL_DEFAULT1;

#if  (UHF_BOARD_TYPE == BOARD_TYPE_RFCB)
    if (g_tI2CFunValue.ucRFCBType == 1)
    {
        /*代表是料单修改后的修改参数*/
        g_tRfInitPara.wAntOnlineThr = 1.7;
    }
#endif
}

/**************************************************************************
* 函数名称：WORD32 InitI2CValue(void)
* 功能描述：初始化I2C总线上射频相关地址的值，
                                 用来当需要写入I2C数据时进行比较
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
                                 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
*11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 uhfRf_BoardInit(void)
{
    printf("UHF:Board RFCB0\r\n");
    WORD32 dwRet = USP_SUCCESS;
    /*选择逻辑为RBCB0 FPGA 版本*/
    FpgaRegWrite(0x75, 1);
#if IO_SWITCH
    dwRet = usp_drv_ioexpander_init();
#endif
    if (dwRet != 0)
    {
        printf("UHF: init ioexpander failure %d!!!\r\n", dwRet);
        return dwRet;
    }

    InitI2CValue();
    InitI2CFucValue();

    /*初始化射频器件的参数*/
    uhfRf_SetInitPara();

    SetDATTtoZero();
    
    uhfRf_SetLKCLInitPara();

    /*驻波保护参数初始化*/
    uhfRf_initVswrAlarm();

    /*射频板设置调制方式*/
    usp_uhf_rf_setRTModuleType(MODULE_TYPE_PR);
    /*设置默认调制深度*/
    usp_uhf_rf_setModulateDepth(100);

    usp_uhf_rf_setRevDatt(0x3f);
    uhfRf_SetRevLowNoEn(LOW_NOISE_DISABLE);

    usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelBackward);
    FpgaRegWrite(prask_dac_low_value_reg, g_tRfInitPara.wPraskDefaultLow);
    FpgaRegWrite(prask_dac_high_value_reg, g_tRfInitPara.wPraskDefaultHigh);
    FpgaRegWrite(ask_dac_high_value_reg, 0x1fff);
    FpgaRegWrite(REG_DAC_DC_VALUE_REG, 0x0000);
    FpgaRegWrite(REG_GATE_VOLTAGE_CTRL0, UHF_RF_GATE_VOL_DEFAULT0);
    FpgaRegWrite(REG_GATE_VOLTAGE_CTRL1, UHF_RF_GATE_VOL_DEFAULT1);
    /*栅压的的数据为串行写入，需要100us的延时*/
    FpgaRegWrite(REG_GATE_VOLTAGE_WR_TRIGER,0);
    FpgaRegWrite(REG_GATE_VOLTAGE_WR_TRIGER,1);
    usleep(100);
    
    /*上电时置为不传送数据状态*/
    FpgaRegWrite(s_rfcl_start, 0x2);
    
    return USP_SUCCESS;

}

/**************************************************************************
* 函数名称：WORD32 uhfRf_BoardReset(void)
* 功能描述：重新初始化PURM相关射频参数配置
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
                                 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
*11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 uhfRf_BoardReset(void)
{
    uhfRfDevPrint("Board RFCB0\r\n");
    WORD32 dwRet = USP_SUCCESS;
    /*选择逻辑为RBCB0 FPGA 版本*/
    FpgaRegWrite(0x75, 1);
#if IO_SWITCH
    dwRet = usp_drv_ioexpander_init();
#endif
    if (dwRet != 0)
    {
        uhfRfDevPrint("UHF: init ioexpander failure %d!!!\r\n", dwRet);
        return dwRet;
    }


    /*驻波保护参数初始化*/
    uhfRf_initVswrAlarm();

    SetDATTtoZero();

    uhfRf_VAutoAdjust();

    /*射频板设置调制方式*/
    usp_uhf_rf_setRTModuleType(MODULE_TYPE_PR);
    /*设置默认调制深度*/
    usp_uhf_rf_setModulateDepth(100);

    usp_uhf_rf_setRevDatt(0x3f);
    uhfRf_SetRevLowNoEn(LOW_NOISE_DISABLE);

    usp_uhf_rf_setPowerDir(POWER_DETECT_CTRL_SelBackward);
    FpgaRegWrite(prask_dac_low_value_reg, g_tRfInitPara.wPraskDefaultLow);
    FpgaRegWrite(prask_dac_high_value_reg, g_tRfInitPara.wPraskDefaultHigh);
    FpgaRegWrite(ask_dac_high_value_reg, 0x1fff);
    FpgaRegWrite(REG_DAC_DC_VALUE_REG, 0x0000);
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：WORD32 InitI2CValue(void)
* 功能描述：初始化I2C总线上射频相关地址的值，
                                 用来当需要写入I2C数据时进行比较
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
                                 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
*11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
static WORD32 InitI2CValue(void)
{
#if 0
    WORD32 dwValue = 0;
    WORD32 dwRet = USP_SUCCESS;
    dwRet = usp_drv_ioexpander_rcv(USP_IOE_RFCB_TYPE_ID, &dwValue);

    if (dwRet != 0)
    {
        return  dwRet;
    }

    g_tI2CValue.ucADR38 = (BYTE)dwValue;

    dwRet = usp_drv_ioexpander_rcv(USP_IOE_ICB_FUN_ALL, &dwValue);

    if (dwRet != 0)
    {
        return  dwRet;
    }

    g_tI2CValue.ucADR39 = (BYTE)dwValue;

    dwRet = usp_drv_ioexpander_rcv(USP_IOE_ICC_FUN_ALL, &dwValue);

    if (dwRet != 0)
    {
        return  dwRet;
    }

    g_tI2CValue.ucADR3A = (BYTE)dwValue;

    dwRet = usp_drv_ioexpander_rcv(USP_IOE_ICD_FUN_ALL, &dwValue);

    if (dwRet != 0)
    {
        return  dwRet;
    }

    g_tI2CValue.ucADR3B = (BYTE)dwValue;

    dwRet = usp_drv_ioexpander_rcv(USP_IOE_RFCB_VER_ID, &dwValue);

    if (dwRet != 0)
    {
        return  dwRet;
    }

    g_tI2CValue.ucADR3C = (BYTE)dwValue;
	#endif
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：WORD32 InitI2CFucValue(void)
* 功能描述：初始化I2C总线上各个器件的值，调用必须在
                                 WORD32 InitI2CValue(void)之后
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
                                 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
*11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
static WORD32 InitI2CFucValue(void)
{
    g_tI2CFunValue.ucRFCBType = g_tI2CValue.ucADR38;
    g_tI2CFunValue.ucRFCBVer = g_tI2CValue.ucADR3C;
    g_tI2CFunValue.ucAntIndex = (g_tI2CValue.ucADR39 & USP_IOE_ANT_CONTROL_MASK) >> USP_IOE_ANT_CONTROL_POS;
    g_tI2CFunValue.ucFwDatt = (g_tI2CValue.ucADR39 & USP_IOE_RX_DATT_MASK) >> USP_IOE_RX_DATT_POS;
    g_tI2CFunValue.ucLinkCho = (g_tI2CValue.ucADR3B & USP_IOE_PWRDET_SEL_MASK) >> USP_IOE_PWRDET_SEL_POS;
    g_tI2CFunValue.ucLo2Datt = (g_tI2CValue.ucADR3B & USP_IOE_RX_LO_DATT_MASK) >> USP_IOE_RX_LO_DATT_POS;
    g_tI2CFunValue.ucLowNoEn = (g_tI2CValue.ucADR3A & USP_IOE_RX_LNA_EN_MASK) >> USP_IOE_RX_LNA_EN_POS;
    g_tI2CFunValue.ucRwCryseCho = (g_tI2CValue.ucADR3A & USP_IOE_RX_LO_SEL_MASK) >> USP_IOE_RX_LO_SEL_POS;
    g_tI2CFunValue.ucRwDatt =  (g_tI2CValue.ucADR3A & USP_IOE_RX_DATT_MASK) >> USP_IOE_RX_DATT_POS;
    g_tI2CFunValue.ucRwFilter = (g_tI2CValue.ucADR3B & USP_IOE_ADG704_A_MASK) >> USP_IOE_ADG704_A_POS;
    g_tI2CFunValue.ucLKCLSwitch = 0; /*上电关闭*/
    return USP_SUCCESS;
}
/**************************************************************************
* 函数名称：邋邋RFCB_SetACDatt
* 功能描述：设置DATT衰减值
* 输入参数：写入的功放DATT衰减值
* 输出参数：
* 返 回 值：    WORD16  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 09/07/29	     V03.00.00	    XXXX	      XXXX
**************************************************************************/
WORD32 usp_uhf_rf_setACDatt(WORD16 wAttenuation)
{
    WORD16 wTempAttenuation;
    wTempAttenuation = (~(wAttenuation >> 1)) & (0x1f);
    uhfRfDevPrint("uhfRf:The Real Attenuation is %d\r\n", wTempAttenuation);
    uhfRfDevPrint("uhfRf:The Atten limit is %d Fpga Atten %x\r\n",
                  UHF_RF_MIN_REAL_ATTEN, wAttenuation);

    g_tI2CFunValue.ucFwDatt = ((BYTE)(wAttenuation) & (0x3f));

    return 0;
}


/**************************************************************************
* 函数名称：uhfRf_setPowerToZero
* 功能描述：写入根据PR值计算出来的功率最小时
                                的K0值
* 输入参数：当前工作天线值
* 输出参数：无
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 2012/02/17	         赵董兴           创建
**************************************************************************/

void uhfRf_setPowerToZero()
{
    uhfDevPrint("wAntIndex=%d\r\n",g_tRfCtrl.wAntIndex);
    WORD16 wMinK0 = uhfRf_getPRMinK0(g_tRfCtrl.wAntIndex);
    /*停止发送载波的时候把控制字设小，减小待机泄露*/
    FpgaRegWrite(REG_FORWARD_PWADJ, wMinK0);   
    /* add by zongjie 2013.1.10 */
    /* 跟硬件调试添加，为了解决两次清点间隔泄漏信号过大的问题 */
    /* 在关闭载波之后，将0x87寄存器写为0x1fff，以使K0值起作用，降低清点间隔的泄漏 */
    FpgaRegWrite(REG_DAC_DC_VALUE_REG, 0x1fff);
    //usp_oss_vos_usleep(DAC_DC_CHANGE_DELAY);
    /* end 2013.1.10 */
}

/**************************************************************************
* 函数名称：uhfRf_SetForDataRate
* 功能描述：设置设置前向速率，只在RUP中有用
* 输入参数：无
* 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 2012/02/17	         赵董兴           创建
**************************************************************************/

void  uhfRf_SetForDataRate(WORD16 wForRate)
{

}

/**************************************************************************
* 函数名称：Set_DATT_to_0
* 功能描述：设置DATT为全衰
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 2011/06/17	          宗杰           创建
**************************************************************************/
WORD32 SetDATTtoZero(void)
{
    g_tI2CFunValue.ucFwDatt = 0;
    usp_uhf_rf_WriteAntDatt();
    return USP_SUCCESS;
}
/**************************************************************************
* 函数名称: void usp_uhf_rf_setPowerDir(WORD16 wDirect)
* 功能描述: 设置功率检测的方向
* 输入参数: WORD16 wDirect 方向
                              POWER_DETECT_CTRL_SelBackward
* 输出参数:
* 返回值:       WORD32    0 成功
*                                               其他 错误
* 其它说明
* 修改日期   版本号   修改人     修改内容
* -------------------------------------------
*  11/01/15          V1.0              zdx             创建
**************************************************************************/
WORD32  usp_uhf_rf_setPowerDir(WORD16 wDirect)
{
    WORD32 dwRet = USP_SUCCESS;
    BYTE ucI2CVal = 0;

    if (wDirect > POWER_DETECT_CTRL_SelForward)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }
    else
    {
        g_tI2CFunValue.ucLinkCho = wDirect;
        ucI2CVal = GetAdr3BVal;
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICD_FUN_ALL, (WORD32)ucI2CVal);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }
    }

    g_tI2CValue.ucADR3B = ucI2CVal;
    return USP_SUCCESS;
}

/**********************************************************************
* 函数名称：uhfRf_SetRevLowNoEn
* 功能描述：低噪放使能函数,目前都为不使能
* 输入参数：是否使能
* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2009/8/3    V03.00.00       zdx          修改
************************************************************************/

WORD32 uhfRf_SetRevLowNoEn(BYTE ucLowNoEn)
{
    WORD32 dwRet = USP_SUCCESS;
    BYTE ucI2CVal = 0;

    g_tI2CFunValue.ucLowNoEn = (ucLowNoEn) & (0x1);
    ucI2CVal = GetAdr3AVal;
#if IO_SWITCH
    dwRet = usp_drv_ioexpander_snd(USP_IOE_ICC_FUN_ALL, (WORD32)ucI2CVal);
#endif
    if (dwRet != USP_SUCCESS)
    {
        uhfRfDevPrint("Set Low En Error\r\n");
        return dwRet;
    }

    g_tI2CValue.ucADR3A = ucI2CVal;
    return USP_SUCCESS;
}

/**********************************************************************
* 函数名称：WORD32 usp_uhf_rf_selectAnt(WORD32 dwAntennaIndex)
* 功能描述：天线选择
* 输入参数：
            WORD32 dwAntennaIndex ；天线索引 0 ~ 3：
* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2009/8/3    V03.00.00       zdx          修改
************************************************************************/
WORD32 usp_uhf_rf_selectAnt(WORD16 wAntIndex)
{
    WORD32 dwRet = USP_SUCCESS;
    BYTE ucI2CValue = 0;

    if ((wAntIndex == 0) || (wAntIndex > 4))
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    /*写入PR包络的值*/
    FpgaRegWrite(prask_dac_high_value_reg, uhfRf_getPRDacHigh(wAntIndex));
    FpgaRegWrite(prask_dac_low_value_reg, uhfRf_getPRDacLow(wAntIndex));

    /* 此版本只可工作在收发一体模式而且不支持LBT */
    g_tI2CFunValue.ucRwCryseCho = DEMOD_LO_SEL_COUPLE;

    ucI2CValue = GetAdr3AVal;

    if (g_tI2CValue.ucADR3A != ucI2CValue)
    {
        uhfRfDevPrint("Write reverse I2C Datt\r\n");
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICC_FUN_ALL, (WORD32)ucI2CValue);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }

        g_tI2CValue.ucADR3A = ucI2CValue;
    }

    if (1 == wAntIndex)
    {
        g_tI2CFunValue.ucAntIndex = 0x2;
    }
    else if (2 == wAntIndex)
    {
        g_tI2CFunValue.ucAntIndex = 0x0;
    }
    else if (3 == wAntIndex)
    {
        g_tI2CFunValue.ucAntIndex = 0x3;
    }
    else if (4 == wAntIndex)
    {
        g_tI2CFunValue.ucAntIndex = 0x1;
    }


    uhfRfDevPrint("uhfRf:Selceted FPGA %x\r\n", g_tI2CFunValue.ucAntIndex);
    return 0;

}


/**************************************************************************
* 函数名称：RFCB_ACWriteAntAndDatt
* 功能描述：设置DATT衰减值和天线号
* 输入参数：天线号和衰减值组成的一个字节的I2C 数据
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 usp_uhf_rf_WriteAntDatt()
{
    BYTE ucI2CValue = 0;
    BYTE ucI2CClrValue = 0;
    WORD32 dwRet = USP_SUCCESS;

    ucI2CValue = GetAdr39Val;

    if (g_tI2CValue.ucADR39 != ucI2CValue)
    {
        ucI2CClrValue = Adr39ValClrDatt;

        if (g_tI2CValue.ucADR39 != ucI2CClrValue)
        {
            uhfRfDevPrint("uhfRf:Write I2C Datt 0x%x ", ucI2CClrValue);
#if IO_SWITCH
            dwRet = usp_drv_ioexpander_snd(USP_IOE_ICB_FUN_ALL, (WORD32)ucI2CClrValue);
#endif
            if (dwRet != USP_SUCCESS)
            {
                return dwRet;
            }

            g_tI2CValue.ucADR39 = ucI2CClrValue;
        }

        uhfRfDevPrint("uhfRf:Write I2C Datt 0x%x\r\n", ucI2CValue);
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICB_FUN_ALL, (WORD32)ucI2CValue);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }

        g_tI2CValue.ucADR39 = ucI2CValue;
    }

    return dwRet;
}

/**************************************************************************
* 函数名称：RFCB_SetRevDatt
* 功能描述：反向DATT控制
* 输入参数：天线号和衰减值组成的一个字节的I2C 数据
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 usp_uhf_rf_setRevDatt(WORD16 wDattVal)
{
    BYTE ucI2CValue = 0;
    WORD32 dwRet = USP_SUCCESS;

    g_tI2CFunValue.ucRwDatt = wDattVal & 0x3f;
    ucI2CValue = GetAdr3AVal;

    if (g_tI2CValue.ucADR3A != ucI2CValue)
    {
        uhfRfDevPrint("uhfRf:Write I2C Reverse Datt %x\r\n", ucI2CValue);
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICC_FUN_ALL, (WORD32)ucI2CValue);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }

        g_tI2CValue.ucADR3A = ucI2CValue;
    }

    return dwRet;
}

/**************************************************************************
* 函数名称：WORD32 usp_uhf_rf_setRevFilter(BYTE ucFilter)
* 功能描述：反向滤波器设置
* 输入参数：滤波器编号
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 usp_uhf_rf_setRevFilter(BYTE ucFilter)
{
    BYTE ucI2CValue = 0;
    WORD32 dwRet = USP_SUCCESS;

    g_tI2CFunValue.ucRwFilter = (ucFilter & 0x03);
    ucI2CValue = GetAdr3BVal;

    if (g_tI2CValue.ucADR3B != ucI2CValue)
    {
        uhfRfDevPrint("Write I2C Reverse Filter %x\r\n", ucI2CValue);
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICD_FUN_ALL, (WORD32)ucI2CValue);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }

        g_tI2CValue.ucADR3B = ucI2CValue;
    }

    return dwRet;
}



/**************************************************************************
* 函数名称：SetLO2Datt
* 功能描述：设置反向解调器的本振的衰减值寄存器
* 输入参数：写入的功放DATT衰减值
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 usp_uhf_rf_SetLO2Datt(WORD16 wCurPower)
{
    WORD16 wData = 0;
    WORD16 wLoop = 0;
    WORD16 awAdjustTable[5] = {800, 400, 200, 100 , 50};
    WORD32 dwRet = USP_SUCCESS;
    BYTE   ucI2CValue = 0;

    wData = (g_tI2CValue.ucADR3B & USP_IOE_RX_LO_DATT_MASK) >> USP_IOE_RX_LO_DATT_POS;

    /* 根据调控算法进行调解 */
    if (2700 >= wCurPower)
    {
        wData |= 0x001f;
    }
    else if (2700 < wCurPower && 4250 > wCurPower)
    {
        /* 获取需要调解的值 */
        wCurPower = wCurPower - 2700;
        wData = wData | 0x001f;

        for (wLoop = 0; wLoop < 5; wLoop++)
        {
            if (wCurPower >= awAdjustTable[wLoop])
            {
                wData &= ~((WORD16)(1 << (4 - wLoop)));
                wCurPower -= awAdjustTable[wLoop];
            }
        }

    }
    else
    {
        wData = wData & 0xffe0;
    }
   /*最后一位不控制，舍掉*/
    g_tI2CFunValue.ucLo2Datt = (wData & 0x1e);

    ucI2CValue = GetAdr3BVal;

    if (g_tI2CValue.ucADR3B != ucI2CValue)
    {
        uhfRfDevPrint("uhfRf:Write I2C Lo2Datt\r\n");
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICD_FUN_ALL, (WORD32)ucI2CValue);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }

        g_tI2CValue.ucADR3B = ucI2CValue;
    }


    uhfRfDevPrint("uhfRf:Use Lo2 Datt 0x%x \r\n", wData);
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：uhfRf_SetLKCLSwitch
* 功能描述：快速泄露对消开关，对消时打开
* 输入参数：开关
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
WORD32 uhfRf_SetLKCLSwitch(BYTE ucSwitch)
{
    WORD32 dwRet = USP_SUCCESS;
    BYTE   ucI2CValue = 0;
    
    uhfRfDevPrint("uhfRf:lkcl switch %d\r\n",ucSwitch);
    
    g_tI2CFunValue.ucLKCLSwitch= (ucSwitch & 0x01);
    ucI2CValue = GetAdr3BVal;
    if (g_tI2CValue.ucADR3B != ucI2CValue)
    {
        uhfRfDevPrint("uhfRf:Write I2C lkclswitch\r\n");
#if IO_SWITCH
        dwRet = usp_drv_ioexpander_snd(USP_IOE_ICD_FUN_ALL, (WORD32)ucI2CValue);
#endif
        if (dwRet != USP_SUCCESS)
        {
            return dwRet;
        }

        g_tI2CValue.ucADR3B = ucI2CValue;
    }
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：WORD32 uhfRf_ChooseRevFilter(WORD16 wLinkRate, BYTE ucSwitch)
* 功能描述：根据速率选择滤波器
* 输入参数：
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
#define FILTER40      0x0
#define FILTER80160   0x1
#define FILTER320640  0x2
#define NOFILTER      0x3
WORD32 uhfRf_ChooseRevFilter(WORD16 wLinkRate, BYTE ucSwitch)
{
    uhfRfDevPrint("Filter sWitch %d\r\n", ucSwitch);

    if (ucSwitch == 0)
    {
        usp_uhf_rf_setRevFilter(NOFILTER);
    }
    else
    {
        if (wLinkRate > 160)
        {
            usp_uhf_rf_setRevFilter(FILTER320640);
        }
        else if (wLinkRate > 40)
        {
            usp_uhf_rf_setRevFilter(FILTER80160);
        }
        else
        {
            usp_uhf_rf_setRevFilter(FILTER40);
        }
    }

    return USP_SUCCESS;
}


/**************************************************************************
* 函数名称：uhfRf_SetAmp
* 功能描述：epld控制的功放电源寄存器，关掉後灯灭，同时
                                 功率输出为0，
* 输入参数：0 关闭 1 打开
* 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 12/02/17	     RUP       zdx	        创建
* 12/06/7	     RUP       zongjie	             增加在bt版本中对于栅压的控制
**************************************************************************/

void usp_uhf_rf_setAmp(WORD16 wAction)
{
#if (UHF_BOARD_TYPE == BOARD_TYPE_RFCB_BT)
    /* 打开功放时，首先打开栅压，再打开功放 */
    if (RF_AMP_ON == wAction)
    {
       FpgaRegWrite(REG_GATE_VOLTAGE_CTRL0, g_tUhfGateVoltageCtrl.wGateVoltage0);
       FpgaRegWrite(REG_GATE_VOLTAGE_CTRL1, g_tUhfGateVoltageCtrl.wGateVoltage1);
       uhf_epld_reg_write(EPLD_RF_AMP_CTRL_REG, wAction);
    }
    else/* 关闭功放时，先关闭功放，再关闭栅压 */
    {
       uhf_epld_reg_write(EPLD_RF_AMP_CTRL_REG, wAction);
       FpgaRegWrite(REG_GATE_VOLTAGE_CTRL0, 0);
       FpgaRegWrite(REG_GATE_VOLTAGE_CTRL1, 0);
    }
#else
      uhf_epld_reg_write(EPLD_RF_AMP_CTRL_REG, wAction);
#endif
}


/**********************************************************************
* 函数名称：usp_uhf_rf_setDemodLoSel
* 功能描述：射频本振方式
* 输入参数：
            WORD16 wType  本振选择 1  前向耦合 0 锁相环
* 输出参数：
* 返 回 值：无
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010.1.4     V0.0.1       zdx   修改
************************************************************************/
void usp_uhf_rf_setDemodLoSel(WORD16 wType)
{
   FpgaRegWrite(REG_DEMOD_LO_SEL, wType);
}


#endif

