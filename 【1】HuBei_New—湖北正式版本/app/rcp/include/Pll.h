#ifndef PLL_H
#define PLL_H

/* ÔÄ¶ÁÆ÷×îÐ¡ÉäÆµÆµÂÊ */
#define MIN_RF_FREQUENCY                  (831000)   /* khz */
#define MIN_RF_FREQUENCY_MX2531_LQ1742    (880000)	 /* khz */
#define MIN_RF_FREQUENCY_MX2531_LQ1700E   (831000)	 /* khz */

#define DEFAULT_800M_FREQUENCY            (840125)
#define DEFAULT_900M_FREQUENCY            (920125)

/* ÔÄ¶ÁÆ÷×î´óÉäÆµÆµÂÊ */
#define MAX_RF_FREQUENCY                  (960000)   /* khz */
#define MAX_RF_FREQUENCY_MX2531_LQ1742    (933000)   /* khz */
#define MAX_RF_FREQUENCY_MX2531_LQ1700E   (885000)   /* khz */


#define  PLL2531_LOCK_STATUS    (0x0064)
/*wzp modify PLL_CHECK_MAX_TIMES from 0x50000 to 0x5*/
#define  PLL_CHECK_MAX_TIMES    (0x5)
#define  PLL_NO_ALARM           (0)
#define  PLL_ALARMED            (1)

#define  ADF4350_CFG_START      (0x0030)
#define  ADF4350_CFG_DATA_H     (0x0031)
#define  ADF4350_CFG_DATA_L     (0x0032)
#define  ADF4350_LOCK_STATUS    (0x0033)
#define  ADF4350_CFG_FINISH     (0x0034)

#if UHF_BOARD_TYPE == BOARD_TYPE_RFCB2
#define  LMX2541_CFG_START      (0x0030)
#define  LMX2541_CFG_DATA_H     (0x0031)
#define  LMX2541_CFG_DATA_L     (0x0032)
#define  LMX2541_LOCK_STATUS    (0x0033)
#define  LMX2541_CFG_FINISH     (0x0034)
#else
#define  LMX2541_CFG_START      (0x0061)
#define  LMX2541_CFG_DATA_H     (0x005f)
#define  LMX2541_CFG_DATA_L     (0x0060)
#define  LMX2541_LOCK_STATUS    (0x0064)
#define  LMX2541_CFG_FINISH     (0x0063)

#endif

#define  ADF4350_R5_VAL         (0x00400005)
#define  ADF4350_R4_VAL         (0x00af603c)
#define  ADF4350_R3_VAL         (0x000004b3)
#define  ADF4350_R2_VAL         (0x60005e42)
#define  ADF4350_R1_VAL         (0x0800b001)
#define  ADF4350_R0_VAL 



#define  MX2541_R7_VAL          (0x00000017)
#define  MX2541_R13_VAL         (0x0000008d)
#define  MX2541_R12_VAL         (0x0000001c)
#define  MX2541_R9_VAL          (0x28001409)
#define  MX2541_R8_VAL          (0x0111ce58)
#define  MX2541_R6_VAL          (0x001f3326)
#define  MX2541_R5_VAL          (0xa0000005)
#define  MX2541_R4_VAL          (0x88043284)
#define  MX2541_R3_VAL          (0x0d806003)
#define  MX2541_R2_VAL          (0x04000642)
#define  MX2541_R1_VAL          (0x00051401)
#define  MX2541_R0_VAL          (0x000067f0)


typedef struct 
{
   WORD32 dwUsrR6;
   WORD32 dwUsrR3;
}T_RfPllUsrCfg;



WORD32 uhfRf_getPLLStatus(void);
WORD32 uhfRf_PLLChipCfg(WORD32 dwRfFreq, WORD16 wNeedReset);


#endif
