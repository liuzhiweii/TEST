#ifndef _RFCB7_H
#define _RFCB7_H

#if  UHF_BOARD_TYPE == BOARD_TYPE_RFCB7

/*等待射频稳定时间，s为单位*/
#define  UHFRF_PA_WARM_TIME           (2)  

#define  UHF_RF_20DB_FPGA_ATTEN       (0x19)
#define  UHF_RF_FULL_POWER            (3900)
#define  UHF_RF_MAX_POWER             (3300)
#define  UHF_RF_MAX_ATTEN             (3150)
#define  UHF_RF_MIN_ATTEN             (0)
#define  UHF_RF_MIN_REAL_ATTEN        (0)
#define  UHF_RF_MIN_FPGA_ATTEN        (0x3f)
#define  UHF_RF_MAX_K0                (0x6000)
#define  UHF_RF_RVE_COPENSATE         (0)
#define  UHF_RF_CLIBRATE_SLEEP        (0)
#define  UHF_RF_WARM_PA_POWER         (3000)

#define  RF_FOR_COMPENSATE_POWER  (300)
#define  RF_REV_COMPENSATE_POWER  (-300)
#define  UHF_RF_ANT_ONLINE_VALUE  (200)
#define  UHF_RF_LKCL_ATTEN         (0x35)
#define  UHF_RF_LKCL_WAIT_TIME    (500)

#define  RF_CLI_DATA_ADDR_ANT14      (512+0x64)
#define  RF_CLI_DATA_ADDR_ANT23      (512+0xC8)

#define  RF_EEPROM_PR_VALUE_ANT14    (512+0x12C)  
#define  RF_EEPROM_PR_VALUE_ANT23    (512+0x130)

#define  RF_PRASK_DAC_DEFAULT_LOW_VALUE     (0x2000)
#define  RF_PRASK_DAC_DEFAULT_HIGH_VALUE    (0x1fff)
#define  RF_PRASK_DAC_MIN_VALUE             (0x1666)
#define  RF_PRASK_DAC_MAX_VALUE             (0x2999)
#define  RF_ASK_DAC_HIGH_VALUE              (0x1fff)


#define  UHF_RF_LKCL_INIT_X0   (32767)
#define  UHF_RF_LKCL_INIT_X1   (32767)
#define  UHF_RF_LKCL_INIT_Y0   (32767)
#define  UHF_RF_LKCL_INIT_Y1   (32767)


#define  UHF_RF_LKCL_ADJ_THRHOLD        (4000)
#define  UHF_RF_LKCL_ADJ_THRHOLD_STAGE2 (20000)

#define UHF_RF_LKCL_INTERG_MAX         (57000)
#define UHF_RF_LKCL_INTERG_MIN         (32000)
#define UHF_RF_LKCL_INIT_COS           (3000)
#define UHF_RF_LKCL_INIT_SIN           (3000)
#define UHF_RF_LKCL_STOP_THD           (40)
#define UHF_RF_LKCL_STOP_THD_STAGE2    (400)
#define UHF_RF_LKCL_FINE_THRHOD        (0)
#define UHF_RF_LKCL_DAC_CHANGE         (0)
#define UHF_RF_LKCL_AUTO_ADJ_INIT_VAL  (0x8000)

/*泄露对消微调的调节时间*/
#define UHF_RF_LKCL_FINE_WAIT_TIME     (250) 
/*泄露对消所需要的功放打开后的等待时间*/
#define UHF_RF_LKCL_RX_OPEN_WAIT_TIME  (450)  
//15
#define UHF_RF_LKCL_ADJ_RESOLUTION_TIME (125) 
#define UHF_RF_MAX_LKCL_ADJ_COUNT       (20)

#define LOW_NOISE_ENABLE  (1)
#define LOW_NOISE_DISABLE (0)

#if 1
#define UHF_RF_INIT_PHASE \
{\
   	{11480,27720},\
	{21210,21210},\
	{27720,11480},\
	{30000,0},\
	{27720,-11480},\
	{21210,-21210},\
	{11480,-27720},\
	{0,-30000},\
	{-11480,-27720},\
	{-21210,-21210},\
	{-27720,-11480},\
	{-30000,0},\
	{-27720,11480},\
	{-21210,21210},\
	{-11480,27720},\
	{0,30000}\
}
#endif

#if 0
#define UHF_RF_INIT_PHASE \
{\
   	{3827,9240},\
	{7070,7070},\
	{9240,3827},\
	{10000,0},\
	{9240,-3827},\
	{7070,-7070},\
	{3827,-9240},\
	{0,-10000},\
	{-3827,-9240},\
	{-7070,-7070},\
	{-9240,-3827},\
	{-10000,0},\
	{-9240,3827},\
	{-7070,7070},\
	{-3827,9240},\
	{0,10000}\
}
#endif

/* 栅压值读取地址 */
#define RF_EEPROM_GATE_VOL_VALUE0       (512+0x134)
#define RF_EEPROM_GATE_VOL_VALUE1       (512+0x136)

/* 栅压默认值 */
#define UHF_RF_GATE_VOL_DEFAULT0         (0x450) 
#define UHF_RF_GATE_VOL_DEFAULT1         (0x450)

/* 栅压限值 */
#define UHF_RF_GATE_VOL_0_MAX           (0x700)
#define UHF_RF_GATE_VOL_0_MIN           (0x200)
#define UHF_RF_GATE_VOL_1_MAX           (0x700)
#define UHF_RF_GATE_VOL_1_MIN           (0x200)

#endif


#endif

