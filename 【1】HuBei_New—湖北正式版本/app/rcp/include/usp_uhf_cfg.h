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
    WORD16 wFreqChannelNum;
    WORD16 wFreqChannel[MAX_FREQ_HOP_NUM]; /*该参数表示跳频的频道号*/
} T_USPUHFFreqHopChannel;

/*跳频配置*/
typedef struct
{
    WORD16                 wFreqHopMode;     /*跳频方式0顺序1随机2大间隔循环步进*/
    WORD16                 wHopTimer;        /*跳频时间间隔,10ms为单位*/
    T_USPUHFFreqHopChannel tfreqChannel;       /*该参数表示跳频的频道号*/
} T_USPUHFFreqHopCfg;

/*使用定频或调频的相关设置*/
typedef struct
{
    WORD16             wFreqTableID;      /*频率方式*/
    WORD16             wFreqWorkType;     /*0 定频 1 调频*/
    WORD16             wFixFreqChannel;
    WORD16             wPad;
#ifdef SUPPORT_HOP_FREQ
    T_USPUHFFreqHopCfg tFreqHopConfig;         /*跳频配置*/
#endif
} T_USPUHFRfFreqCfg;

typedef struct
{
    WORD16 wHopTableID;
    WORD16 wFrequeceNum;
    WORD32 dwFrequeces[64];
}T_USPUHFFreqTableEntry;


typedef struct
{
    BYTE    ucFilterSwitch; /*0表示关闭读过滤功能，1表示开启该功能*/
    BYTE    ucFilterThreshold;
    /*以百分比形式表示阈值，取值范围[1,100]*/
    WORD16  wMaxReadRSSI;    /*最大信号强度，取值范围[1,65535]*/
} T_USPUHFRSSIFilterCtl;


typedef struct
{
    T_USPUHFRSSIFilterCtl  tRSSIFilter6C; /*6CRSSI过滤控制参数*/
    T_USPUHFRSSIFilterCtl  tRSSIFilter6B; /*6BRSSI过滤控制参数*/
    T_USPUHFRSSIFilterCtl  tRSSIFilterGB; /*GBRSSI过滤控制参数*/
} T_USPUHFRSSIFilter;


typedef struct
{
    BYTE                ucForandRevConfig;   /*天线收发方式配置,0 收发一体 1 收2  发*/
    BYTE                ucAntennaLBT;        /*是否支持LBT工作模式,预留方式*/
    WORD16              wCanChkStatus;       /*是否支持在位检测*/
    BYTE                aucAntPower[UHF_RF_ANT_POWER_COUNT];          /*天线功率表示,dbm表示*/
    WORD16              wRevFilterSwitch;    /*0  关闭1 打开*/
    WORD16              wLbtDattValue;       /*4.0版本中用的后来去掉了*/ 
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
    WORD16 wForDataRate; /*前向速率*/
    WORD16 wRevDataRate; /*反向速率*/
    WORD16 wPIEValue;    /*PIE 的值*/
    WORD16 wPad;
    E_USPUHFDataEncodeType   eDataEncodeType;  /*反向编码方式0fm0 1miller2  2mille4 3miller4*/
    E_USPUHFModulateType     eModulateType;   /*调制方式0 pr 1 dsb*/
} T_USPUHFEpcUserDefPara;

typedef struct
{
    WORD16 wForDataRate; /*前向速率*/
    WORD16 wRevDataRate; /*反向速率*/
    WORD16 wPIEValue;    /*PIE 的值*/
    WORD16 wPad;
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
    WORD16                  wEPCModuleDepth;    /*0-80,1-90,2-100*/
    WORD16                  wISO6BModuleDepth;  /*6B调制深度0-18 1-100*/
    WORD16                  wGBModuleDepth;  /* GB 调制深度 lxc */
    WORD16                  wIQConfig;          /*I Q路配置，目前没用*/
    BYTE                    ucTurnOnLKCL;       /*泄露对消开关0 关闭1打开*/
    BYTE                    ucRecvDATT;         /*反向DATT控制*/
    WORD16                  wFreqType;          /*阅读器的功率属性800 or 900 or 800900*/
    WORD16                  wPad;
} T_USPUHFReaderCfg;


typedef struct
{
    WORD16             wTransmitPower;
#if USE_INVENTORY_RF_CONFIG 
    WORD16             wReceiverSensitivity;
    T_USPUHFRfFreqCfg  tFreqCfg;
#endif
} T_USPUHFInventRfPara;



typedef struct
{
    /*I+ I- Q+ Q-的初始值*/
    WORD16 wInitX0;
    WORD16 wInitX1;
    WORD16 wInitY0;
    WORD16 wInitY1;
     /*泄露对消的积分上下限*/
    WORD16 wIntegralMax;
    WORD16 wIntegralMin;
    /*泄露对消停止门限*/
    WORD16 wStopThd;
    /*泄露对消的初始相位*/
    WORD16 wInitcos;   
    WORD16 wInitSin;

    WORD32 dwAdjThrHold;
    WORD16 wFineThrHold;  /*连续多次检测到需要微调後进行微调*/
    WORD16 wDacChange;

}T_USPUHFLKCLInitParas;


typedef struct
{
    /*I+ I- Q+ Q-的初始值*/
    WORD16 wX0;
    WORD16 wX1;
    WORD16 wY0;
    WORD16 wY1;
    WORD16 wInitCos;
    WORD16 wInitSin;
    WORD16 wIsCrossed;   /*是否需要交叉*/
    WORD16 wIsConfiged;  /*判断当前的频点是否已经泄露对消完毕*/
    WORD16 wCheckFineCnt;
    WORD16 wADCidata;
    WORD16 wADCqdata;
    WORD16 wAdjCount;
}T_USPUHFLKCLParas;

typedef struct
{
    SWORD16 swPower;   /*功率，以db为单位，最小单位0.01db,使用*100来描述*/
    WORD16  wVoltage;  /*对应的电压值*/
}T_USPUHFRfPowerTableEntry;

typedef struct
{
   WORD16 wGateVoltage0;     /* 栅压控制字0 */
   WORD16 wGateVoltage1;     /* 栅压控制字1 */
}T_USPUHFGateVoltageCtrl;

typedef struct
{
   WORD16  wK0;
   SWORD16 swMinK0;
   WORD16  wPR1Value;
   WORD16  wPR2Value;
   T_USPUHFRfPowerTableEntry atFwTable[RF_FORWARD_PT_NUM];
   T_USPUHFRfPowerTableEntry atBwTable[RF_BACKWARD_PT_NUM];
}T_USPUHFRfPowerTable;

typedef struct
{
   WORD32 dwVersion;
   T_USPUHFRfPowerTable tUhfRfPowerTable1;
   T_USPUHFRfPowerTable tUhfRfPowerTable2;
}T_USPUHFFlashRfData;

typedef struct 
{
    WORD16  wCalibrateK0;   /* 定标结束时的K0值*/
    WORD16  wCalibratPower; /* 定标结束时的功率值*/
    WORD16  wTargetPower;   
    WORD16  wDattVal;       /*DATT 衰减值*/
}T_USPUHFRfPowerEntry;

typedef struct
{  
   WORD16 wResIndex;     /*记录当前的定标结果*/
   WORD16 wVswr;         /* 驻波比* 100*/
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
    WORD16 wantennaId;
    WORD16 wForDataRate;
    WORD16 wRevDataRate;
    EM_value_Type eM_value;
    EForward_link_Type eForward_link_modulation;
    WORD16 wPIE_Value;
} T_USPUHFRFModeCfg;

WORD32 usp_uhf_set_cfg(T_USPUHFReaderCfg *ptReaderCfg);

#endif



