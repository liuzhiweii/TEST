/************************************************************************
* 版权所有 (C)2011, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： rfctl.h
* 文件标识： 
* 内容摘要：射频主流程需要的宏定义
* 其它说明： 
* 当前版本： 
* 作    者： zdx
* 完成日期： 2010.12.26
* 
* 修改记录1： RUP 增加修改自适应
*    修改日期：2011.12.1
*    版 本 号：    RUP
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/

#ifndef _RFCTL_H
#define _RFCTL_H

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
#define UHFRF_AC_WAIT_TIME              (100000)  /*等待射频稳定时间，us为单位*/

#define READER_ANT_INIT_POWER            2000  /*初始功率值，检测天线状态用，在对照表中有这个表项*/
#define READER_AC_ATTENUATION_INIT       1900  /* 缺省衰减值19 DB 对应功率功率20DB */

#define DEMOD_LO_SEL_PLL           (0x000)
#define DEMOD_LO_SEL_COUPLE        (0x001)

#define POWER_DETECT_CTRL_SelForward    (0x001)
#define POWER_DETECT_CTRL_SelBackward   (0x000)

#define POWER_DETECT_ADC_CLK_ON    (0x01)       /* 打开功率检测ADC时钟 */
#define POWER_DETECT_ADC_CLK_OFF   (0x00)       /* 关闭功率检测ADC时钟 */

#define LKCL_DAC_CLK_ON            (0x01)       /* 打开泄漏对消DAC时钟 */
#define LKCL_DAC_CLK_OFF           (0x00)       /* 关闭泄漏对消DAC时钟 */

#define LKCL_SET_POWER                (3000)   

#define READER_AC_MAX_K0                 (0x6000)  /* 设置K0的上限值 */
#define UHF_RF_MAX_AC_ADJUST              (10)

/* LBT状态 */
#define LBT_STATUS_IDLE           (0)  /* 空闲状态       */
#define LBT_STATUS_BUSY           (1)  /* 信道被占用状态 */

#define  AMP_NO_NEED_SLEEP  (0)
#define  AMP_NEED_SLEEP     (1)

#define  UHF_RF_FAST_LKCL_ON  (1)
#define  UHF_RF_FAST_LKCL_OFF (0)


#define RF_AMP_ON   		(1)  			/* 1). 打开功放电源 */
#define RF_AMP_OFF  		(0)  			/*     关闭功放电源 */ 

#define PLL_NO_NEED_RESET   (0)
#define PLL_NEED_RESET      (1)

#define LBT_ON           (0x2)   /* LBT功能打开 */
#define LBT_OFF          (0x1)   /* LBT功能关闭 */

#define UHF_RF_PT_ANT14    (0)   /* 天线1对应定标数据，或者天线1、4共用的定标数据 */
#define UHF_RF_PT_ANT23    (1)   /* 天线2对应定标数据，或者天线2、3共用的定标数据 */
#define UHF_RF_PT_ANT3     (2)   /* 天线3对应定标数据 */
#define UHF_RF_PT_ANT4     (3)   /* 天线4对应定标数据 */

#define FOUR_POWER_TABLE   4     /* 4套定标数据 */
#define POWER_TABLE_COUNT  0x263 /* 根据EEPROM中此地址的值来判断阅读器中有几套定标数据 */

/*锁相环的配置状态，0代表上电未进行第一次配置，
   1 代表应经配置过第一个配置避免发送误告警*/
#define UHF_RF_PLL_NOT_CONFIGED (0)
#define UHF_RF_PLL_CONFIGED     (1)


#define uhf_epld_reg_read(wRegAddr)         g_pvUSPDrvEpldVirtStartAddr0[wRegAddr]
#define uhf_epld_reg_write(wRegAddr,wData)  g_pvUSPDrvEpldVirtStartAddr0[wRegAddr]=(wData)

#define uhfRf_GetAmpState()  g_pvUSPDrvEpldVirtStartAddr0[EPLD_RF_AMP_CTRL_REG]


#define REV_FILTER_40       (0)
#define REV_FILTER_80_160   (1)
#define REV_FILTER_320_640  (2)
#define REV_NO_FILTER       (3)


#define LBT_switch(wAction)               FpgaRegWrite(REG_LBT_SWITCH,wAction) 

#define SendAlarm 

/* LED闪灯参数 */
#define ANT1_EXIST        USP_OSS_LED_FLASH_ANT1_EXIST            /* 天线1在位，常亮 */  
#define ANT1_NOT_EXIST    USP_OSS_LED_FLASH_ANT1_NOT_EXIST        /* 天线1不在位，常灭 */
#define ANT1_WORK_ERR     USP_OSS_LED_FLASH_ANT1_WORK_ERR         /* 天线1操作异常，持续时间2秒，之后自动关闭，闪灯频率是1HZ */
#define ANT1_WORKING      USP_OSS_LED_FLASH_ANT1_WORKING          /* 天线1正常工作，持续时间1秒，之后自动关闭，闪灯频率是5HZ */
#define ANT2_EXIST        USP_OSS_LED_FLASH_ANT2_EXIST           
#define ANT2_NOT_EXIST    USP_OSS_LED_FLASH_ANT2_NOT_EXIST       
#define ANT2_WORK_ERR     USP_OSS_LED_FLASH_ANT2_WORK_ERR        
#define ANT2_WORKING      USP_OSS_LED_FLASH_ANT2_WORKING         
#define ANT3_EXIST        USP_OSS_LED_FLASH_ANT3_EXIST           
#define ANT3_NOT_EXIST    USP_OSS_LED_FLASH_ANT3_NOT_EXIST       
#define ANT3_WORK_ERR     USP_OSS_LED_FLASH_ANT3_WORK_ERR        
#define ANT3_WORKING      USP_OSS_LED_FLASH_ANT3_WORKING        
#define ANT4_EXIST        USP_OSS_LED_FLASH_ANT4_EXIST           
#define ANT4_NOT_EXIST    USP_OSS_LED_FLASH_ANT4_NOT_EXIST       
#define ANT4_WORK_ERR     USP_OSS_LED_FLASH_ANT4_WORK_ERR        
#define ANT4_WORKING      USP_OSS_LED_FLASH_ANT4_WORKING   

#if USP_OSS_LED_USE
#define RCP_LED_FLASH_ON(id)            usp_oss_led_on(id)
#define RCP_LED_FLASH_OFF(id)           usp_oss_led_off(id)
#else
#define RCP_LED_FLASH_ON(id)
#define RCP_LED_FLASH_OFF(id)
#endif

#define DAC_DC_CHANGE_DELAY         50    /* 将FPGA 0x87寄存器值修改后，需要延时 */


/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
typedef double Double;

/*采用RFCB2 对应的FPGA*/
typedef struct 
{
   WORD16 w20DBAtten;        /*20Db时所对应的FPGA衰减值*/
   WORD16 wFullPower;        /*衰减值为0时的功率值*/
   WORD16 wMaxAtten;         /*最大的衰减值真实值*100*/
   WORD16 wMinAtten;         /*最小的衰减值真实值*100*/
   WORD16 wMaxPower;         /*阅读器支持的最大功率值*/
   WORD16 wMaxK0;            /*判断最大的K0值*/
   WORD16 wRcvCompensate;    /*反向计算时的一个补偿参数*/
   WORD16 wClibrateWaitTime; /*功放打开后的延时时间*/
   WORD16 swForCompensatePower; /*前向的补偿功率*/
   WORD16 swRevCompensatePower; /*反向的补偿功率*/
   WORD16 wPraskDefaultLow;
   WORD16 wPraskDefaultHigh;
   WORD16 wPraskMax;
   WORD16 wPraskMin;
   WORD16 wAntOnlineThr;
   WORD16 wLKCLAutoAdjInitVal;  /*在电压字校准流程中的初始值*/
   WORD16 wGateVolDefault0;
   WORD16 wGateVolDefault1;
}T_RfInitPara;

/* 跳频控制 */
typedef struct
{
    WORD16 wFreqWorkType;         /*定频还是跳频*/
    WORD16 wWorkChannel;          /* 实际使用的当前工作信道*/
    WORD16 wFreqTableID;          /*当前采用的跳频表*/
    WORD16 wFixFreqChannel;       /* 定频频道号*/
    WORD32 dwLbtEnable;
    WORD32 dwMaxLbtCheckTimes;
#ifdef SUPPORT_HOP_FREQ
    WORD16 wFreqHopMode;         /* 多种跳频 */
    WORD16 wHopChannelNum;       /* 后台配置频道数目,包括重复频道号*/
    WORD16 wHopChannelNo[MAX_FREQ_HOP_NUM];          /* 频道号,数组内可配相同频道号*/
    WORD16 wHopChannel;            /*当前的跳频索引号*/
    WORD16 wPad;
    WORD16 wHopTimer;           /* 跳频间隔 */
    struct timeval tHopClock;       /*跳频时间计时器,当到达wFreqHopTimer时，tHopClock记录为当前时间并跳频*/
#endif
} T_UhfRfFreqHopCtrl;

/*每根天线有两个频率控制结构，6B和6c是分开的*/
typedef struct tagT_UhfRfAntFreqHopCtrl
{
   T_UhfRfFreqHopCtrl  tEpcFreqHopCtrl;
   T_UhfRfFreqHopCtrl  tIso6BFreqHopCtrl;
   T_UhfRfFreqHopCtrl  tGBFreqHopCtrl;
}T_UhfRfAntFreqHopCtrl;



typedef struct
{
    BYTE ucADR38;
    BYTE ucADR39;
    BYTE ucADR3A;
    BYTE ucADR3B;
    BYTE ucADR3C;
    BYTE ucPad;
    WORD16 wPad;
} T_I2CValue;

typedef struct
{
    BYTE ucRFCBType;
    BYTE ucFwDatt;
    BYTE ucAntIndex;
    BYTE ucRwDatt;
    BYTE ucLowNoEn;
    BYTE ucRwCryseCho;   /*反向本振选择*/
    BYTE ucLo2Datt;
    BYTE ucLinkCho;
    BYTE ucRwFilter;
    BYTE ucRFCBVer;
    BYTE ucLKCLSwitch;
    BYTE ucPad;
} T_I2CFunValue;

/* 天线状态闪灯结构体 */
typedef struct tagT_AntStatus
{
    WORD16 wAnt_Exist;        /* 天线在位 */ 
    WORD16 wAnt_Not_Exist;    /* 天线不在位 */
    WORD16 wAnt_Work_Err;     /* 天线工作异常 */
    WORD16 wAnt_Working;      /* 天线正在工作 */
} T_AntStatus;

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/
/**************************************************************************
 *                         全局函数                                    *
 **************************************************************************/
void    usp_uhf_rf_txSet(WORD16 dwRfTxAction);
void    SendAntAbnoramlAlarm(WORD16 wAntIndex, WORD32 dwAlarmType);
WORD32  uhfRf_SetLKCLPower(BYTE ucAntIndex);
void    uhfRf_RefreshPower();
void    usp_uhf_rf_setModulateDepth(WORD32 dwModulateDepth);
void    uhfRf_SetLKCLPowerPara(BYTE ucAntIndex);
void    usp_uhf_rf_writeCtrlWord(WORD16 wCrtlWord);
WORD32  usp_uhf_rf_getAntStatus(WORD16 wAntIndex);
WORD32  uhfRf_ConvChannelToFreq(WORD16 wChannelNo, WORD16 wHopTableID);
WORD32  uhfRf_startAllAction(void);
void    uhfRf_InitCtrlStruct();
WORD32 usp_uhf_rf_setPLLFreq(WORD32 dwRfFreq);
WORD16 uhfRf_getPRDacHigh(WORD16 wAntIndex);
WORD16 uhfRf_getPRDacLow(WORD16 wAntIndex);
WORD16 uhfRf_getPRMinK0(WORD16 wAntIndex);
T_UhfRfFreqHopCtrl* uhfRf_getFreqHopCtrl(WORD16 wAntIndex,WORD16 wProtocolType);
WORD16 uhfRf_getFreqWorkChannel(WORD16 wAntIndex,WORD16 wProtocolType);
WORD16 uhfRf_getFreqTableId(WORD16 wAntIndex,WORD16 wProtocolType);
void   uhfRf_warmPA(WORD16 wPTarget,WORD16 wAntIndex);
WORD32 ACPowerSetProc();
WORD16 usp_uhf_rf_queryAntVswr(WORD16 wAntIndex);
WORD16 uhfRf_CheckPLLStatus(WORD16 *pwPLLConfigStatus);
WORD32 usp_uhf_rf_autoCalibrate(BYTE ucAntIndex, WORD16 wPTarget);


#endif


