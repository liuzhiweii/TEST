#ifndef RFCB2_H
#define RFCB2_H

#if  UHF_BOARD_TYPE == BOARD_TYPE_RFCB2

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

#define  UHF_RF_GATE_VOL_DEFAULT0         (0x69f) 
#define  UHF_RF_GATE_VOL_DEFAULT1         (0x580)

#define  RF_FOR_COMPENSATE_POWER  (300)
#define  RF_REV_COMPENSATE_POWER  (-300)
#define  UHF_RF_ANT_ONLINE_VALUE  (200)
#define  UHF_RF_LKCL_ATTEN         (0x35)
#define  UHF_RF_LKCL_WAIT_TIME    (1000)

#define  RF_CLI_DATA_ADDR_ANT14    (0x100)
#define  RF_CLI_DATA_ADDR_ANT23    (0x150)

#define  RF_EEPROM_PR_VALUE_ANT14  (0x22)  
#define  RF_EEPROM_PR_VALUE_ANT23  (0x26)

#define  RF_PRASK_DAC_DEFAULT_LOW_VALUE     (0x8000)
#define  RF_PRASK_DAC_DEFAULT_HIGH_VALUE    (0x7fff)
#define  RF_PRASK_DAC_MIN_VALUE             (0x6000)
#define  RF_PRASK_DAC_MAX_VALUE             (0x8000)
#define  RF_ASK_DAC_HIGH_VALUE              (0x7fff)


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
#define UHF_RF_LKCL_STOP_THD_STAGE2    (200)
#define UHF_RF_LKCL_FINE_THRHOD        (0)
#define UHF_RF_LKCL_DAC_CHANGE         (0)
#define UHF_RF_LKCL_AUTO_ADJ_INIT_VAL  (0x7450)
#define UHF_RF_MAX_LKCL_ADJ_COUNT      (3)

/*泄露对消微调的调节时间*/
#define UHF_RF_LKCL_FINE_WAIT_TIME     (250) 
/*泄露对消所需要的功放打开后的等待时间*/
#define UHF_RF_LKCL_RX_OPEN_WAIT_TIME  (30)  
//15
#define UHF_RF_LKCL_ADJ_RESOLUTION_TIME (125) /*500us*/

#define LOW_NOISE_ENABLE  (1)
#define LOW_NOISE_DISABLE (0)

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

#endif

