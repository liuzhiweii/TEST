#ifndef PURM_H
#define PURM_H

#if  UHF_BOARD_TYPE == BOARD_TYPE_PURM

/*采用PURM0对应的FPGA*/
#define  UHF_RF_20DB_FPGA_ATTEN       (0x0d)
#define  UHF_RF_FULL_POWER        (4500)
#define  UHF_RF_MAX_POWER         (3300)
#define  UHF_RF_MAX_ATTEN             (3150)
#define  UHF_RF_MIN_ATTEN             (1100)
#define  UHF_RF_MIN_REAL_ATTEN        (11)
#define  UHF_RF_MIN_FPGA_ATTEN        (0x29)
#define  UHF_RF_MAX_K0                (0x6000)
#define  UHF_RF_RVE_COPENSATE         (1.5)

#define  RF_CLI_DATA_ADDR_ANT14   (0xea)
#define  RF_CLI_DATA_ADDR_ANT23   (0xea)


#define  UHF_RF_CLIBRATE_SLEEP    (0)
#define  UHF_RF_ANT_ONLINE_VALUE  (250)
#define  UHF_RF_LKCL_ATTEN         (0)
#define  UHF_RF_LKCL_WAIT_TIME    (500)

#define  RF_FOR_COMPENSATE_POWER   (0)
#define  RF_REV_COMPENSATE_POWER   (0)

#define  RF_PRASK_DAC_DEFAULT_LOW_VALUE     (0x2000)
#define  RF_PRASK_DAC_DEFAULT_HIGH_VALUE    (0x1fff)
#define  RF_PRASK_DAC_MIN_VALUE             (0x1666)
#define  RF_PRASK_DAC_MAX_VALUE             (0x2999)
#define  RF_ASK_DAC_HIGH_VALUE              (0x1fff)



#define LOW_NOISE_ENABLE  (1)
#define LOW_NOISE_DISABLE (0)

#endif

#endif
