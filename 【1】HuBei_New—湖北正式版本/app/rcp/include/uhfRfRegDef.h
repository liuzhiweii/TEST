/************************************************************************
* 版权所有 (C)2012深圳市中兴通讯股份有限公司。
* 
* 文件名称： uhfRfRegDef.h
* 文件标识： 
* 内容摘要： 6700射频寄存器定义文件
* 其它说明： 基于硬件fpga对于架构一样的阅读器采用
                                 相同的fpga和epld寄存器地址
* 当前版本： 
* 作    者： 赵董兴
* 完成日期： 2012.5.3
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef UHFRFREGDEF_H
#define UHFRFREGDEF_H

#if USP_IS_DISTRIBUTED

/*EPLD Regs*/
/* 功放电源控制寄存器 PAPWR, 默认关闭功放电源 */
#define  EPLD_RF_AMP_CTRL_REG	         (0x16)
#define  REG_VSWR_ALARM_MASK             (0x46)
#define  REG_VSWR_ALARM                  (0x19)
#define  REG_PA_EN_TRIG                  (0x17)
#define  UHF_RF_TSENSOR_LOCAL_TEMP_LOW    FIRST_TSENSOR_LOCAL_TEMP_LOW
#define  UHF_RF_TSENSOR_LOCAL_TEMP_HIGH   FIRST_TSENSOR_LOCAL_TEMP_HIGH
#define  UHF_RF_TSENSOR_REMOTE_TEMP_LOW   FIRST_TSENSOR_REMOTE_TEMP_LOW
#define  UHF_RF_TSENSOR_REMOTE_TEMP_HIGH  FIRST_TSENSOR_REMOTE_TEMP_HIGH
#define  UHF_RF_TSENSOR_LOCAL_TEMP        FIRST_TSENSOR_LOCAL_TEMP
#define  UHF_RF_TSENSOR_REMOTE_TEMP       FIRST_TSENSOR_REMOTE_TEMP
#define  UHF_RF_TSENSOR_ALARM_STATUS      FIRST_TSENSOR_ALARM_STATUS
#define  UHF_RF_TSENSOR_CLEAR_INT         SECOND_TSENSOR_CLEAR_INT


/*ADC DAC 控制寄存器*/
#define    ADC_CONFIG_START             (0x000a)
#define    ADC_CONFIG_FINISH            (0x000b)
#define    ADC_CONFIG_DATA              (0x0025)
#define    reg_module_type              (0x000c)
#define    FOWARD_LINK_RATE             (0x000d)              
#define    FOWARD_FILTER_SWITCH         (0x000e)
#define    REG_FORWARD_PWADJ            (0x000f)
#define    REG_DAC_DC_VALUE_REG         (0x0011)
#define    prask_dac_low_value_reg      (0x0012)
#define    prask_dac_high_value_reg     (0x0013)
#define    REG_module_depth             (0x0014)
#define    ask_dac_high_value_reg       (0x0015)
#define    DAC_CONFIG_START             (0x0016)
#define    DAC_CONFIG_DATA              (0x0017)
#define    DAC_CONFIG_READ              (0x0018)
#define    DAC_CONFIG_FINISH            (0x0019)
#define    DAC_HARDWARE_RESET           (0x001a)
#define    DAC_CLOCK_ENABLE             (0x001b)
#define    SINGLETONE_SEND_CTRL         (0x001c)

/* 泄露对消ADC,DAC时钟关闭 */
/* 解决RFCB7单板杂散超标的问题 */
#define    LKCL_DAC_CLK_CTRL            (0x0208)
/* 功率检测ADC时钟控制 */
/* 在不使用功率检测功能时，关闭ADC的时钟信号，提高反向灵敏度 */
#define    POWER_DETECT_ADC_CLK_CTRL  (0x0209)  

 /*DATT 衰减寄存器*/
#define    RDA1005_SND_START          (0x0035)
#define    RDA1005_SND_DATA           (0x0036)
#define    RDA1005_SND_FINISH         (0x0037)

#define    RDA1005_RCV_START          (0x0038)
#define    RDA1005_RCV_DATA           (0x0039)
#define    RDA1005_RCV_FINISH         (0x003a)
#define    REG_LKCL_SWITCH_UNUSED     (0x003b)
#define    REG_REV_FILTER             (0x003d)
#define    REG_RX_LO2_DATT            (0x003e) 
#define    REG_LNA_CTRL               (0x003f)
#define    REG_DEMOD_LO_SEL           (0x0040)
#define    POWER_DETECT_CTRL          (0x0041)
#define    POWER_DETECT_VAL           (0x0042)
#define    REG_LBT_SWITCH             (0x0006)  /*RFCB2 无用*/


#define    s_cos_theta          (0x0043)
#define    s_sin_theta          (0x0044)
#define    s_rfcl_start         (0x0045)
#define    s_rfcl_time_indic    (0x0046)
#define    s_threhold_val       (0x0047)
#define    s_integral_max       (0x0048)
#define    s_integral_min       (0x0049)
#define    s_x0_reg             (0x004A)
#define    s_x1_reg             (0x004B)
#define    s_y0_reg             (0x004C)
#define    s_y1_reg             (0x004D)
#define    s_dac_change         (0x004E)
#define    I_ADC_idata          (0x004F)
#define    I_ADC_qdata          (0x0050)
#define    I_i1_data            (0x0051)
#define    I_i2_data            (0x0052)
#define    I_q1_data            (0x0053)
#define    I_q2_data            (0x0054)
#define    I_stop               (0x0055)

#define    REG_GATE_VOLTAGE_CTRL0    (0x0056)
#define    REG_GATE_VOLTAGE_CTRL1    (0x0057)
#define    REG_I_LKCL_ADJ1           (0x0058)
#define    REG_I_LKCL_ADJ2           (0x0059)
#define    REG_RF_PROTOCOL_TYPE      (0x005a)
#define    LKCL_ORIGIN_X             (0x005B)
#define    LKCL_ORIGIN_Y             (0x005C)

#define    REG_DATT_ATTENUATION      (0x005d)
#define    REG_LKCL_SWITCH           (0x005e)


#else

/* 功放电源控制寄存器 PAPWR, 默认关闭功放电源 */
#if (UHF_BOARD_TYPE == BOARD_TYPE_RFCB_BT || UHF_BOARD_TYPE == BOARD_TYPE_RFCB7)
#define EPLD_RF_AMP_CTRL_REG	      (0x160 >> 1)
#define REG_VSWR_ALARM_MASK        (0x1f4 >> 1)
#define REG_VSWR_ALARM             (0x30 >> 1)
#define REG_PA_EN_TRIG             (0x34 >> 1)

/*ADC控制寄存器*/
#define ADC_CFG_TRIG               (0x0400)
#define ADC_CFG_DATA               (0x0401)
#define ADC_READY                  (0x0402)

#else
#define EPLD_RF_AMP_CTRL_REG	   (0x160)
#define REG_VSWR_ALARM_MASK        (0x1f4)
#define REG_VSWR_ALARM             (0x30)
#define REG_PA_EN_TRIG             (0x34)  
#endif

#define UHF_RF_TSENSOR_LOCAL_TEMP_LOW     SECOND_TSENSOR_LOCAL_TEMP_LOW
#define UHF_RF_TSENSOR_LOCAL_TEMP_HIGH    SECOND_TSENSOR_LOCAL_TEMP_HIGH
#define UHF_RF_TSENSOR_REMOTE_TEMP_LOW    SECOND_TSENSOR_REMOTE_TEMP_LOW
#define UHF_RF_TSENSOR_REMOTE_TEMP_HIGH   SECOND_TSENSOR_REMOTE_TEMP_HIGH
#define UHF_RF_TSENSOR_LOCAL_TEMP         SECOND_TSENSOR_LOCAL_TEMP
#define UHF_RF_TSENSOR_REMOTE_TEMP        SECOND_TSENSOR_REMOTE_TEMP
#define UHF_RF_TSENSOR_ALARM_STATUS       SECOND_TSENSOR_ALARM_STATUS
#define UHF_RF_TSENSOR_CLEAR_INT          SECOND_TSENSOR_CLEAR_INT



#define  REG_FORWARD_PWADJ        (0x0044)

#define  REG_GATE_VOLTAGE_CTRL0      (0x0203)
#define  REG_GATE_VOLTAGE_CTRL1      (0x0204)
#define  REG_GATE_VOLTAGE_WR_TRIGER  (0x0205)


#define  REG_RX_LO2_DATT          (0x00b5) 
#define  POWER_DETECT_CTRL        (0x00b2)
#define  REG_DEMOD_LO_SEL         (0x00b4)
#define  POWER_DETECT_VAL         (0x00b3) 
#define  reg_module_type          (0x0049)
#define  REG_module_depth         (0x004B)
#define  prask_dac_low_value_reg  (0x008f)
#define  prask_dac_high_value_reg (0x0084)
#define  ask_dac_high_value_reg   (0x0086)
#define  REG_DAC_DC_VALUE_REG     (0x0087)

/* 泄露对消ADC,DAC时钟关闭 */
/* 解决RFCB7单板杂散超标的问题 */
#define  LKCL_DAC_CLK_CTRL        (0x0208)
/* 功率检测ADC时钟控制 */
/* 在不使用功率检测功能时，关闭ADC的时钟信号，提高反向灵敏度 */
#define  POWER_DETECT_ADC_CLK_CTRL (0x0209)  

/* LBT切换寄存器 */
#define  REG_LBT_SWITCH           (0x005E)
#define  SINGLETONE_SEND_CTRL     (0x0074)

#define  REG_RF_PROTOCOL_TYPE      (0x01)/*无用的寄存器*/
#define  REG_LKCL_SWITCH           (0x01)/*无用的寄存器*/
#define  REG_DATT_ATTENUATION      (0x00D3)   /*DATT 衰减寄存器*/


/*泄露对消相关的寄存器*/
#define  s_cos_theta          (0x00D9)   
#define  s_sin_theta          (0x00DA)  
#define  s_rfcl_start         (0x00DB)  
#define  s_rfcl_time_indic    (0x00DC)
#define  s_threhold_val       (0x00DD)
#define  s_integral_max       (0x00DE)
#define  s_integral_min       (0x00DF)
#define  s_x0_reg             (0x00E0)    
#define  s_x1_reg             (0x00E1)    
#define  s_y0_reg             (0x00E2)   
#define  s_y1_reg             (0x00E3)
#define  s_dac_change         (0x00E4)
#define  I_ADC_idata          (0x00E5)      
#define  I_ADC_qdata          (0x00E6)     
#define  I_i1_data            (0x00E7)    
#define  I_i2_data            (0x00E8)       
#define  I_q1_data            (0x00E9)       
#define  I_q2_data            (0x00EA)
#define  I_stop               (0x00EB)
#define  REG_I_LKCL_ADJ1      (0x0201)
#define  REG_I_LKCL_ADJ2      (0x0202)
#define  LKCL_ORIGIN_X        (0x00EC)
#define  LKCL_ORIGIN_Y        (0x00ED)


#endif


#endif

