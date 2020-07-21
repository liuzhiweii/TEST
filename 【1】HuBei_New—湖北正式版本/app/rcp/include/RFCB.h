
#ifndef _RFCB_H
#define _RFCB_H

#if  UHF_BOARD_TYPE == BOARD_TYPE_RFCB

/*采用RFCB0 对应的FPGA*/
#define  UHF_RF_20DB_FPGA_ATTEN       (0x25)
#define  UHF_RF_FULL_POWER            (3300)
#define  UHF_RF_MAX_POWER             (3000)
#define  UHF_RF_MAX_ATTEN             (3150)
#define  UHF_RF_MIN_ATTEN             (0)
#define  UHF_RF_MIN_REAL_ATTEN        (0)
#define  UHF_RF_MIN_FPGA_ATTEN        (0x3f)
#define  UHF_RF_MAX_K0                (0x6000)
#define  UHF_RF_RVE_COPENSATE         (0)
#define  RF_CLI_DATA_ADDR_ANT14      (512+0xea)
#define  RF_CLI_DATA_ADDR_ANT23      (512+0x130)

#define  RF_EEPROM_PR_VALUE_ANT14    (512+0x122)  
#define  RF_EEPROM_PR_VALUE_ANT23    (512+0x126)


#define  UHF_RF_CLIBRATE_SLEEP     (2)
#define  UHF_RF_ANT_ONLINE_VALUE   (200)
#define  UHF_RF_LKCL_ATTEN         (0x39)
#define  UHF_RF_LKCL_WAIT_TIME    (500)

#define  UHF_RF_LKCL_INIT_X0 (32767)
#define  UHF_RF_LKCL_INIT_X1 (32767)
#define  UHF_RF_LKCL_INIT_Y0 (32767)
#define  UHF_RF_LKCL_INIT_Y1 (32767)

#define  UHF_RF_LKCL_ADJ_THRHOLD        (0x10000)
#define  UHF_RF_LKCL_ADJ_THRHOLD_STAGE2 (0x40000)

#define UHF_RF_LKCL_INTERG_MAX      (57000)
#define UHF_RF_LKCL_INTERG_MIN      (32000)

#define UHF_RF_LKCL_INIT_COS        (3000)
#define UHF_RF_LKCL_INIT_SIN        (3000)

#define UHF_RF_LKCL_STOP_THD        (0x400)
#define UHF_RF_LKCL_STOP_THD_STAGE2 (0x2000)
#define UHF_RF_LKCL_FINE_THRHOD     (100)

#define UHF_RF_LKCL_DAC_CHANGE      (0)
#define UHF_RF_LKCL_AUTO_ADJ_INIT_VAL (0x8000)

/*泄露对消微调的调节时间*/
#define UHF_RF_LKCL_FINE_WAIT_TIME     (250) 
/*泄露对消所需要的功放打开后的等待时间*/
#define UHF_RF_LKCL_RX_OPEN_WAIT_TIME  (150)  

#define UHF_RF_LKCL_ADJ_RESOLUTION_TIME (250) 
#define UHF_RF_MAX_LKCL_ADJ_COUNT       (3)


#define UHF_RF_INIT_PHASE \
{\
   	{1148,2772},\
	{2121,2121},\
	{2772,1148},\
	{3000,},\
	{2772,-1148},\
	{2121,-2121},\
	{1148,-2772},\
	{0,-3000},\
	{-1148,-2772},\
	{-2121,-2121},\
	{-2772,-1148},\
	{-3000,0},\
	{-2772,1148},\
	{-2121,2121},\
	{-1148,2772},\
	{0,3000}\
}


#define  RF_FOR_COMPENSATE_POWER   (0)
#define  RF_REV_COMPENSATE_POWER   (0)


#define  RF_PRASK_DAC_DEFAULT_LOW_VALUE     (0x2000)
#define  RF_PRASK_DAC_DEFAULT_HIGH_VALUE    (0x1fff)
#define  RF_PRASK_DAC_MIN_VALUE             (0x1666)
#define  RF_PRASK_DAC_MAX_VALUE             (0x2999)
#define  RF_ASK_DAC_HIGH_VALUE              (0x1fff)


#define LOW_NOISE_ENABLE  (1)
#define LOW_NOISE_DISABLE (0)



/*根据I2C总线上各个器件的值去顶39地址的值*/
#define Adr39ValClrDatt (g_tI2CFunValue.ucAntIndex<<USP_IOE_ANT_CONTROL_POS)

/*根据I2C总线上各个器件的值去顶39地址的值*/
#define GetAdr39Val ((g_tI2CFunValue.ucAntIndex<<USP_IOE_ANT_CONTROL_POS)|\
                               (g_tI2CFunValue.ucFwDatt<<USP_IOE_TX_DATT_POS))

/*根据I2C总线上各个器件的值去顶3A地址的值*/
#define GetAdr3AVal ((g_tI2CFunValue.ucRwCryseCho<<USP_IOE_RX_LO_SEL_POS)|\
                         (g_tI2CFunValue.ucLowNoEn<<USP_IOE_RX_LNA_EN_POS)|\
                             (g_tI2CFunValue.ucRwDatt<<USP_IOE_RX_DATT_POS))

/*根据I2C总线上各个器件的值去顶3B地址的值*/
#define GetAdr3BVal ((g_tI2CFunValue.ucLo2Datt<<USP_IOE_RX_LO_DATT_POS)|\
                       (g_tI2CFunValue.ucLinkCho<<USP_IOE_PWRDET_SEL_POS)|\
                         (g_tI2CFunValue.ucRwFilter<<USP_IOE_ADG704_A_POS))


#endif

#endif


