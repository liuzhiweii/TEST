#ifndef _USP_UHF_CFG_H
#define _USP_UHF_CFG_H

/* Ant_mode_sel，0：天线工作于收发分离或LBT模式；1：天线工作在收发一体模式 */
#define ANT_MODE_DUAL_ANT     (0)  /* 天线工作于收发分离或LBT模式 */
#define ANT_MODE_SINGLE_ANT   (1)  /* 天线工作在收发一体模式           */

/*数字模块通知射频模块协议类型的宏*/
#define UHF_RF_PROTOCOL_EPC     (0)
#define UHF_RF_PROTOCOL_ISO6B   (1)
#define UHF_RF_PROTOCOL_GB   (2)




typedef struct
{
    unsigned short int wFreqChannelNum;
    unsigned short int wFreqChannel[MAX_FREQ_HOP_NUM]; /*该参数表示跳频的频道号*/
} T_USPUHFFreqHopChannel;

/*跳频配置*/
typedef struct
{
    unsigned short int                 wFreqHopMode;     /*跳频方式0顺序1随机2大间隔循环步进*/
    unsigned short int                 wHopTimer;        /*跳频时间间隔,10ms为单位*/
    T_USPUHFFreqHopChannel tfreqChannel;       /*该参数表示跳频的频道号*/
} T_USPUHFFreqHopCfg;

/*使用定频或调频的相关设置*/
typedef struct
{
    unsigned short int             wFreqTableID;      /*频率方式*/
    unsigned short int             wFreqWorkType;     /*0 定频 1 调频*/
    unsigned short int             wFixFreqChannel;
    unsigned short int             wPad;
#ifdef SUPPORT_HOP_FREQ
    T_USPUHFFreqHopCfg tFreqHopConfig;         /*跳频配置*/
#endif
} T_USPUHFRfFreqCfg;

typedef struct
{
    unsigned short int wHopTableID;
    unsigned short int wFrequeceNum;
    unsigned int dwFrequeces[64];
}T_USPUHFFreqTableEntry;


typedef struct
{
    unsigned char    ucFilterSwitch; /*0表示关闭读过滤功能，1表示开启该功能*/
    unsigned char    ucFilterThreshold;
    /*以百分比形式表示阈值，取值范围[1,100]*/
    unsigned short int  wMaxReadRSSI;    /*最大信号强度，取值范围[1,65535]*/
} T_USPUHFRSSIFilterCtl;


typedef struct
{
    T_USPUHFRSSIFilterCtl  tRSSIFilter6C; /*6CRSSI过滤控制参数*/
    T_USPUHFRSSIFilterCtl  tRSSIFilter6B; /*6BRSSI过滤控制参数*/
    T_USPUHFRSSIFilterCtl  tRSSIFilterGB; /*GBRSSI过滤控制参数*/
} T_USPUHFRSSIFilter;


typedef struct
{
    unsigned char                ucForandRevConfig;   /*天线收发方式配置,0 收发一体 1 收2  发*/
    unsigned char                ucAntennaLBT;        /*是否支持LBT工作模式,预留方式*/
    unsigned short int              wCanChkStatus;       /*是否支持在位检测*/
    unsigned char                aucAntPower[UHF_RF_ANT_POWER_COUNT];          /*天线功率表示,dbm表示*/
    unsigned short int              wRevFilterSwitch;    /*0  关闭1 打开*/
    unsigned short int              wLbtDattValue;       /*4.0版本中用的后来去掉了*/ 
    T_USPUHFRSSIFilter  tReadRSSIFilter;          /*RSSI 参数配置*/
    T_USPUHFRSSIFilter  tWriteRSSIFilter;
} T_USPUHFRfCommonCfg;


typedef enum USP_UHF_Encode_Type
{
    DATA_ENCODE_TYPE_FM0 = 0,
    DATA_ENCODE_TYPE_MILLER2 = 1,
    DATA_ENCODE_TYPE_MILLER4 = 2,
    DATA_ENCODE_TYPE_MILLER8 = 3,
} E_USPUHFDataEncodeType;

typedef enum USP_UHF_Modulate_Type
{
    Modulate_TYPE_DSB = 1,
    Modulate_TYPE_SSB = 2,
    Modulate_TYPE_PR  = 3,
} E_USPUHFModulateType;


typedef struct
{
    unsigned short int wForDataRate; /*前向速率*/
    unsigned short int wRevDataRate; /*反向速率*/
    unsigned short int wPIEValue;    /*PIE 的值*/
    unsigned short int wPad;
    E_USPUHFDataEncodeType   eDataEncodeType;  /*反向编码方式0fm0 1miller2  2mille4 3miller4*/
    E_USPUHFModulateType     eModulateType;   /*调制方式0 pr 1 dsb*/
} T_USPUHFEpcUserDefPara;

typedef struct
{
    unsigned short int wForDataRate; /*前向速率*/
    unsigned short int wRevDataRate; /*反向速率*/
    unsigned short int wPIEValue;    /*PIE 的值*/
    unsigned short int wPad;
    E_USPUHFDataEncodeType   eDataEncodeType;  /*反向编码方式0fm0 1miller2  2mille4 3miller4*/
    E_USPUHFModulateType     eModulateType;   /*调制方式0 pr 1 dsb*/
}T_USPUHFGBUserDefPara;


typedef struct
{
    T_USPUHFEpcUserDefPara  tAntEpcUserDefPara[READER_ANTENNA_COUNT];
   // T_USPUHFGBUserDefPara    tAntGBUserDefPara[READER_ANTENNA_COUNT]; 暂时不要
    T_USPUHFRfCommonCfg     tAntRfCommonCfg[READER_ANTENNA_COUNT];
    T_USPUHFRfFreqCfg       tAntEpcRfFreqCfg[READER_ANTENNA_COUNT];
    T_USPUHFRfFreqCfg       tAntISO6BRfFreqCfg[READER_ANTENNA_COUNT];
    T_USPUHFRfFreqCfg       tAntGBRfFreqCfg[READER_ANTENNA_COUNT];
    unsigned short int                  wEPCModuleDepth;    /*0-80,1-90,2-100*/
    unsigned short int                  wISO6BModuleDepth;  /*6B调制深度0-18 1-100*/
    unsigned short int                  wGBModuleDepth;  /* GB 调制深度 lxc */
    unsigned short int                  wIQConfig;          /*I Q路配置，目前没用*/
    unsigned char                    ucTurnOnLKCL;       /*泄露对消开关0 关闭1打开*/
    unsigned char                    ucRecvDATT;         /*反向DATT控制*/
    unsigned short int                  wFreqType;          /*阅读器的功率属性800 or 900 or 800900*/
    unsigned short int                  wPad;
} T_USPUHFReaderCfg;


typedef struct
{
    unsigned short int             wTransmitPower;
    unsigned short int             wReceiverSensitivity;
    T_USPUHFRfFreqCfg  tFreqCfg;
} T_USPUHFInventRfPara;



typedef struct
{
    /*I+ I- Q+ Q-的初始值*/
    unsigned short int wInitX0;
    unsigned short int wInitX1;
    unsigned short int wInitY0;
    unsigned short int wInitY1;
     /*泄露对消的积分上下限*/
    unsigned short int wIntegralMax;
    unsigned short int wIntegralMin;
    /*泄露对消停止门限*/
    unsigned short int wStopThd;
    /*泄露对消的初始相位*/
    unsigned short int wInitcos;   
    unsigned short int wInitSin;

    unsigned int dwAdjThrHold;
    unsigned short int wFineThrHold;  /*连续多次检测到需要微调後进行微调*/
    unsigned short int wDacChange;

}T_USPUHFLKCLInitParas;


typedef struct
{
    /*I+ I- Q+ Q-的初始值*/
    unsigned short int wX0;
    unsigned short int wX1;
    unsigned short int wY0;
    unsigned short int wY1;
    unsigned short int wInitCos;
    unsigned short int wInitSin;
    unsigned short int wIsCrossed;   /*是否需要交叉*/
    unsigned short int wIsConfiged;  /*判断当前的频点是否已经泄露对消完毕*/
    unsigned short int wCheckFineCnt;
    unsigned short int wADCidata;
    unsigned short int wADCqdata;
    unsigned short int wAdjCount;
}T_USPUHFLKCLParas;

typedef struct
{
    signed short int swPower;   /*功率，以db为单位，最小单位0.01db,使用*100来描述*/
    unsigned short int  wVoltage;  /*对应的电压值*/
}T_USPUHFRfPowerTableEntry;

typedef struct
{
   unsigned short int wGateVoltage0;     /* 栅压控制字0 */
   unsigned short int wGateVoltage1;     /* 栅压控制字1 */
}T_USPUHFGateVoltageCtrl;

typedef struct
{
   unsigned short int  wK0;
   signed short int swMinK0;
   unsigned short int  wPR1Value;
   unsigned short int  wPR2Value;
   T_USPUHFRfPowerTableEntry atFwTable[RF_FORWARD_PT_NUM];
   T_USPUHFRfPowerTableEntry atBwTable[RF_BACKWARD_PT_NUM];
}T_USPUHFRfPowerTable;

typedef struct
{
   unsigned int dwVersion;
   T_USPUHFRfPowerTable tUhfRfPowerTable1;
   T_USPUHFRfPowerTable tUhfRfPowerTable2;
}T_USPUHFFlashRfData;

typedef struct 
{
    unsigned short int  wCalibrateK0;   /* 定标结束时的K0值*/
    unsigned short int  wCalibratPower; /* 定标结束时的功率值*/
    unsigned short int  wTargetPower;   
    unsigned short int  wDattVal;       /*DATT 衰减值*/
}T_USPUHFRfPowerEntry;

typedef struct
{  
   unsigned short int wResIndex;     /*记录当前的定标结果*/
   unsigned short int wVswr;         /* 驻波比* 100*/
   T_USPUHFRfPowerEntry      atPowers[UHF_RF_ANT_POWER_COUNT];
   T_USPUHFRfPowerTable     *ptPowerTable;
}T_USPUHFRfAntPower;

typedef enum
{
    M_value_Type_FM0 = 0,
    M_value_Type_Miller = 1,
    M_value_Type_Miller4 = 2,
    M_value_Type_Miller8 = 3,
} EM_value_Type;

typedef enum
{
    Forward_link_Type_PR_ASK = 0,
    Forward_link_Type_SSB_ASK = 1,
    Forward_link_Type_DSB_ASK = 2,
} EForward_link_Type;

typedef struct
{
    unsigned short int wantennaId;
    unsigned short int wForDataRate;
    unsigned short int wRevDataRate;
    EM_value_Type eM_value;
    EForward_link_Type eForward_link_modulation;
    unsigned short int wPIE_Value;
} T_USPUHFRFModeCfg;

unsigned int usp_uhf_set_cfg(T_USPUHFReaderCfg *ptReaderCfg);

#endif


