#ifndef UHF_RF_H
#define UHF_RF_H


#define RF_POWER_STATE_ON     (0)
#define RF_POWER_STATE_OFF    (1)


#define RF_ANT_INPOS     (1)
#define RF_ANT_NOT_INPOS (0)     


#define  POWER_TABLE_LEN    19
#define  RF_POWER_TABLE 	{15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33}

/* 天线状态 */
#define  ANTENNA_STATUS_OK      (1)   /* 正常 */
#define  ANTENNA_STATUS_ERROR   (0)   /* 异常 */
#define  ANTENNA_STATUS_UNKNOWN (2)   /* 状态未知,如阅读器不支持天线状态查询 */


/* 射频单元状态 */
#define  RF_STATUS_OK      (0)   /* 正常 */
#define  RF_STATUS_ERROR   (1)   /* 异常 */

#define UHF_RF_START_TX     (1)   /* 启动射频功率发送；  */
#define UHF_RF_STOP_TX      (0)   /* 关闭射频功率发送 */

#define  NEED_RESET_POWER  (1)
#define  NO_NEED_RESET_POWER  (0)


/* 射频单元PLL状态 */
#define  RF_PLL_STATUS_OK      (1)   /* 正常 */
#define  RF_PLL_STATUS_ERROR   (0)   /* 异常 */

//跳频或者定频模式
#define FIXED_FREQ                (0) /*定频模式*/
#define FREQ_HOP                  (1) /*跳频模式*/

//跳频模式
#define FREQ_HOP_SCAN_CHANNEL  (0)           /* 逐段*/
#define FREQ_HOP_SCAN_RANDOM_CHANNEL  (1)  /* 随机*/
#define FREQ_HOP_SCAN_STEP_CHANNEL  (2)  /* 大间隔循环步进*/


#define PLL_TYPE_800M         (0x0)
#define PLL_TYPE_900M         (0x1)
#define PLL_TYPE_800900M      (0x3)


/*硬件第二版支持天线收发分离,1,3以及2,4分别为一对,
  同时可以支持一对分离,另外两个为收发一体*/
typedef struct
{
    WORD16 wAnt_mode;           /* 0：天线工作于收发分离或LBT模式；1：天线工作在收发一体模式 */
    WORD16 wAgcDatt;
    BYTE   wRcvOrSnd;          /*接收天线号,如果收发一体则与发送天线号相同*/
    BYTE   ucAntennaLBT;          /*是否支持LBT工作模式*/
    BYTE   ucSupportCheckStatus;  /*是否支持在位检测*/
    BYTE   ucAntStause;           /*天线是否在位*/
    BYTE   aucAntPower[UHF_RF_ANT_POWER_COUNT];
    BYTE   ucRevFilterSwitch;
    BYTE   ucPad;
    WORD16 wInventPower;
} T_AntennaCfg;

/* 射频模块控制数据结构 */
typedef struct
{
    WORD16 wConfigAntNum;
    WORD16 wLKCLSwitch;
    WORD16 wRcvDatt;
    WORD16 wLowNoEn;
    WORD16 wAntIndex;         /* 当前工作天线 */
    WORD16 wFreqType;          /*800M 900M锁相环*/
    WORD16 wWorkChannel;
    WORD16 wMaxFreqTable;
    WORD16 wProtocolType;
    WORD16 wPad;
    WORD32 dwWorkFreq;         /* 当前工作频率, 单位：kHz,  */
    WORD32 dwPllWorkFreq;      /* 锁相环目前工作的频率值*/
    T_AntennaCfg    atRfAntCfg[READER_ANTENNA_COUNT + 1];
} T_RfCtrl;

#define RF_CFG_NOT_EXIST (0)
#define RF_CFG_EXIST (1)
typedef struct
{
   WORD16 wAntIndex;
   WORD16 wForDataRate;/*前向速率40 80 160 */
   WORD16 wRevDataRate;
   WORD16 wModulateType; /*调制方式01 DSB  11 PR*/
   WORD16 wModulateDepth;
   WORD16 wProtocolType;
   WORD16 wPad;
   WORD16 wRfCfgExist;
   T_USPUHFInventRfPara tRfCfg;
}T_UhfInventRfConfigPara;


typedef struct 
{
  WORD16 wResult;  /*0 成功*/
  WORD16 wChannelNo;
  WORD16 wAntIndex;
  WORD16 wPad;
}T_UhfInventRfConfigRes;

   
typedef struct
{
   WORD16 wAntIndex;
   BYTE   aucPower[UHF_RF_ANT_POWER_COUNT]; 
   WORD16 wRevFilterSwitch;
   WORD16 wAntMode;
   WORD16 wAntLBT;
   WORD16 wAgcDatt;
   T_USPUHFRfFreqCfg tFreqCtrl;
}T_UhfRfAntConfigPara;

typedef struct
{
   WORD16 wConfigAntNum;
   WORD16 wRcvDatt;
   WORD16 wLKCLSwitch;
   WORD16 wLowNoEn;
   T_UhfRfAntConfigPara tAntConfigPara[READER_ANTENNA_COUNT]; 
}T_UhfRfConfigPara;


void uhfRf_SetFreqCfg(T_USPUHFRfFreqCfg *ptFreqCfg, WORD16 wAntIndex,
                                                   WORD16  wProtocolType);
WORD16 uhfRf_FreqHopCtrl(WORD16 wAntIndex,WORD16 wProtoType);
WORD32 uhfRf_CalRFPara(T_UhfInventRfConfigPara *ptInventRfConfigPara);
void   uhfRf_FreqHopInit(void);
T_USPUHFFreqTableEntry *uhfRf_GetHopTable(WORD16 wHopTableId);
WORD32 uhfRf_Init();
WORD32 uhfRf_Reset();
void uhfRf_SetCfgs(T_USPUHFReaderCfg *ptRfConfigPara);
void uhfRf_CreateDmpResMsg(T_Msg *ptRcvMsg,T_Msg *ptSndMsg);


#endif

