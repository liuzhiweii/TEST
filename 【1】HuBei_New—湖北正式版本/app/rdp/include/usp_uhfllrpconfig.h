#ifndef USP_UHFLLRPCONFIG
#define  USP_UHFLLRPCONFIG


//#define READER_ANTENNA_COUNT           4   /*阅读器最大支持的天线数*/

#define READER_MAX_EVENT_NUM           9   /*EPC最大掩码字数*/
#define EPC_MAX_MASK_WORD_NUM           32   /*EPC最大掩码字数*/
#define MaxISO6BGroupSelectNum 10 /*最大的select数 对应ISO6BFilter最大成员项*/
#define   MaxEPCSelectNum                           3     /*最大EPC 支持select 数*/
#define   MaxGBSortNum                           1    /*最大GB 支持sort 数*/
#define MAX_NUM_SORT_FILTER_PERQUERY 1

/**************************天线的配置的定义************************************************/
/*天线的扩展配置*/

typedef struct  tagT_USPRdpLllrpRFReceiver
{
    unsigned short int wReceiverSensitivity;
    unsigned short int wPad;
}T_USPRdpLlrpRFReceiver;


typedef struct   tagT_USPRdpLlrpRFTransmitter
{
    unsigned short int wTransmitPower;
    unsigned short int wHopTableID;             /*选择LLRP能力中跳频表,这里搞成跳频标准*/
    unsigned short int wChannelIndex;
    unsigned short int wPad;
}T_USPRdpLlrpRFTransmitter;

typedef struct   tagT_USPRdpLlrpTargetTagMask
{
    unsigned short int wMemBank;                                                              /* 00: RFU； 01: EPC； 10: TID； 11: User */
    unsigned short int wMaskLength;                                                          /* Mask length (bits) */
    unsigned short int wMaskBitPointer;         
    unsigned short int wPad;
    /* Starting Mask bit address */
    unsigned char ucMaskData[EPC_MAX_MASK_WORD_NUM * 2];   /* 变长 Mask value,得第一个字段 */
}T_USPRdpLlrpTargetTagMask;

typedef struct   tagT_USPRdpLlrpC1G2TagInventoryStateUnawareFilter
{
   /*LLRP_tEC1G2StateUnawareAction*/
    unsigned int  eC1G2StateUnawareAction;
}T_USPRdpLlrpC1G2TagInventoryStateUnawareFilter;

typedef struct   tagT_USPRdpLlrpC1G2RFControl
{
    unsigned short int wModeIndex;               /*表项 能力中有的*/
    unsigned short int wTari;                           /*参数校验根据表项 选能力中的表 比较邋Tari 0 和 表指定都有效*/
}T_USPRdpLlrpC1G2RFControl;        /*链路速录和，调制方式等*/

typedef struct   tagT_USPRdpLlrpC1G2SingulationControl
{
    unsigned char        ucSession;
    unsigned char        ucPad;
    unsigned short int  wTagPopulation;
    unsigned int  dwTagTransitTime;
}T_USPRdpLlrpC1G2SingulationControl; /*这项 就看session 可否确定*/

typedef struct   tagT_USPRdpLlrpISO6BRFControl
{
    unsigned short int wModeIndex;
    unsigned short int wPad;
}T_USPRdpLlrpISO6BRFControl;

typedef struct  tagT_USPRdpLlrpISO6BFilter
{
    unsigned char       ucCommandType;
    unsigned char       ucAddress;
    unsigned char       ucMask;
    unsigned char       ucPad;
    unsigned short int wWordDataLen;
    unsigned short int   wPad;
    unsigned char       ucWordData[8];         /* 变长 Mask value,from 0~8 byte in length. 长度由wWordDataLen字段决定, MSB first */
}T_USPRdpLlrpISO6BFilter;

typedef struct   tagT_USPRdpLlrpISO6BFilterList
{
    unsigned char                              ucGroupSelectNum;
    unsigned char                              ucPad[3];
    T_USPRdpLlrpISO6BFilter atUSPRdpLlrpISO6BFilter[MaxISO6BGroupSelectNum];
}T_USPRdpLlrpISO6BFilterList;

typedef struct   tagT_USPRdpLlrpISO6BSingulationControl  
{
    unsigned short int  wTagPopulation;
    unsigned short int  wPad;
    unsigned int  dwTagTransitTime;
}T_USPRdpLlrpISO6BSingulationControl;

typedef struct   tagT_USPRdpLlrpISO6BInventoryCommand
{
    T_USPRdpLlrpISO6BRFControl                tUSPRdpLlrpISO6BRFControl;   /*链路速录和调制方式等*/
    T_USPRdpLlrpISO6BFilterList                  tUSPRdpLlrpISO6BFilter ; /*最大select数个filter*/
    T_USPRdpLlrpISO6BSingulationControl    tUSPRdpLlrpISO6BSingulationControl;/*预估标签数*/
}T_USPRdpLlrpISO6BInventoryCommand;

typedef struct    tagT_USPRdpLlrpC1G2Filter
{
    T_USPRdpLlrpTargetTagMask tUSPRdpLlrpEPCTargetTagMask;
     /*LLRP_tEC1G2TruncateAction变成unsigned int*/
    unsigned int  eC1G2TruncateAction;
    T_USPRdpLlrpC1G2TagInventoryStateUnawareFilter tUSPRdpLlrpC1G2TagInventoryStateUnawareFilterAction;
}T_USPRdpLlrpC1G2Filter; /*掩码，select命令参数*/

typedef struct   tagT_USPRdpLlrpC1G2FilterList
{
    unsigned short int                       wFilterNum;
    unsigned short int                       wPad;
    T_USPRdpLlrpC1G2Filter atUSPRdpLlrpC1G2Filter[MaxEPCSelectNum];
}T_USPRdpLlrpC1G2FilterList;

typedef struct   tagT_USPRdpLlrpC1G2InventoryCommand
{
    unsigned short int                                            wTagInventoryStateAware;
    unsigned short int                                            wPad;
    /*不支持是否还存在 这个结构 考虑一下 参数校验忽略*/
    T_USPRdpLlrpC1G2FilterList                 tUSPRdpLlrpC1G2Filter;                       /*select 链表*/
    T_USPRdpLlrpC1G2RFControl               tUSPRdpLlrpC1G2RFControl;                /*链路速率和调制方式等*/
    T_USPRdpLlrpC1G2SingulationControl  tUSPRdpLlrpC1G2SingulationControl;
}T_USPRdpLlrpC1G2InventoryCommand;

typedef struct   tagT_USPRdpLlrpGBRFControl
{
    unsigned short int wModeIndex;               /*表项 能力中有的*/
    unsigned short int wPad;                           
}T_USPRdpLlrpGBRFControl;        

typedef struct   tagT_USPRdpLlrpGBSingulationControl
{
    unsigned short int  wCCN;
    unsigned short int  wCIN;
    unsigned char        ucSession;
    unsigned char        ucGBQureySel;
    unsigned char        ucGBQureyAction;
    unsigned char        ucPad;
}T_USPRdpLlrpGBSingulationControl; /*这项 就看session 可否确定*/
typedef struct   tagT_USPRdpLlrpGBTagInventoryStateAwareFilterAction
{
    unsigned char  ucGBStateAwareTarget;
    unsigned char  ucGBStateAwareAction;
    unsigned short int wPad;
}T_USPRdpLlrpGBTagInventoryStateAwareFilterAction;

typedef struct    tagT_USPRdpLlrpGBFilter
{
    T_USPRdpLlrpTargetTagMask tUSPRdpLlrpGBTargetTagMask;
    T_USPRdpLlrpGBTagInventoryStateAwareFilterAction tUSPRdpLlrpGBTagInventoryStateAwareFilterAction;
}T_USPRdpLlrpGBFilter; /*掩码，select命令参数*/

typedef struct   tagT_USPRdpLlrpGBFilterList
{
    unsigned short int                       wFilterNum;
    unsigned short int                       wPad;
    T_USPRdpLlrpGBFilter atUSPRdpLlrpGBFilter[MAX_NUM_SORT_FILTER_PERQUERY];
}T_USPRdpLlrpGBFilterList;

typedef struct   tagT_USPRdpLlrpGBInventoryCommand
{
    /*不支持是否还存在 这个结构 考虑一下 参数校验忽略*/
    T_USPRdpLlrpGBFilterList                 tUSPRdpLlrpGBFilter;                       /*select 链表*/
    T_USPRdpLlrpGBRFControl               tUSPRdpLlrpGBRFControl;                /*链路速率和调制方式等*/
    T_USPRdpLlrpGBSingulationControl  tUSPRdpLlrpGBSingulationControl;
}T_USPRdpLlrpGBInventoryCommand;

typedef struct   tagT_USPRdpLlrpAirProtocolInventoryCommand
{
    T_USPRdpLlrpC1G2InventoryCommand  tUSPRdpLlrpC1G2InventoryCommand;
    T_USPRdpLlrpISO6BInventoryCommand tUSPRdpLlrpISO6BInventoryCommand;
    T_USPRdpLlrpGBInventoryCommand tUSPRdpLlrpGBInventoryCommand;
}T_USPRdpLlrpAirProtocolInventoryCommand;

typedef struct   tagT_USPRdpLlrpAntennaConfiguration
{
    unsigned char                                                          ucAntID;    /* 天线编号 */
    unsigned char                                                          ucPad[3];        
    //T_USPRdpLlrpRFReceiver                             tUSPRdpLlrpRFReceiverSettings;
    T_USPRdpLlrpRFTransmitter                         tUSPRdpLlrpRFTransmitterSettings;          /*是否把上面结构组成一个结构*/
    T_USPRdpLlrpAirProtocolInventoryCommand tUSPRdpLlrpAirProtocolInventoryCommandSettings;   
}T_USPRdpLlrpAntennaConfiguration;


typedef struct tagT_USPRdpLlrpReaderEventNotificationSpec
{
          /*LLRP_tENotificationEventType变成unsigned int*/
    unsigned int          tNotificationEventType;   /*事件号,有个表中会有index-value的索引表示*/
    unsigned int                                      bNotificationState;/*通知的状态*/
}T_USPRdpLlrpReaderEventNotificationSpec;

 /*事件上报通知的设置*/
  typedef struct tagT_USPRdpLlrpAntennaProperties
{
    unsigned short int             wAntennaID;      /*天线编号*/   
    signed short int           swAntennaGain;      /*天线增益*/ 
    unsigned int            bAntennaConnected;    /*天线是否连接False = 未连接.True = 连接*/
}T_USPRdpLlrpAntennaProperties;

typedef struct  tagT_USPRdpLlrpTagReportContentSelector
{
    unsigned int                  bEnableROSpecID;
    unsigned int                  bEnableSpecIndex;
    unsigned int                  bEnableInventoryParameterSpecID;
    unsigned int                  bEnableAntennaID;
    unsigned int                  bEnableChannelIndex;
    unsigned int                  bEnablePeakRSSI;
    unsigned int                  bEnableFirstSeenTimestamp;
    unsigned int                  bEnableLastSeenTimestamp;
    unsigned int                  bEnableTagSeenCount;
    unsigned int                  bEnableAccessSpecID;
    unsigned int                  bEnablePC;
    unsigned int                  bEnableCRC;

}T_USPRdpLlrpTagReportContentSelector;

typedef struct tagT_USPRdpLlrpROReportConfig
{
     /*LLRP_tEROReportTriggerType变成unsigned int*/
    unsigned int                              eROReportTrigger;
    unsigned short int                                                            wThresholdOfReportNum;               
    unsigned short int                                                            wPad;
    T_USPRdpLlrpTagReportContentSelector               tRdpLlrpTagReportContentSelector;
}T_USPRdpLlrpROReportConfig;
/*Accesss 触发条件，只有两种*/
typedef struct tagT_USPRdpLlrpAccessReportConifg
{
    /*LLRP_tEROReportTriggerType变成unsigned int*/
    unsigned int  eAccessReportTriggerType; /* 0    Whenever ROReport is generated for the RO that    triggered the execution of this AccessSpec.   1    End of AccessSpec */
}T_USPRdpLlrpAccessReportConifg;

typedef struct tagT_USPRdpLlrpEventsAndReports
{
   unsigned int  bHoldEventsAndReportsUponReconnect ;  /*False表示不缓存报告与事件,True则表示缓存.*/
}T_USPRdpLlrpEventsAndReports;


/* 阅读器配置6B6C发射功率 */


/*使用定频或调频的相关设置*/
typedef struct  tagT_USPRdpLlrpRfFreqCfg
{
    T_USPUHFRfFreqCfg      tUSPUHFRfFreqCfg6B;
    T_USPUHFRfFreqCfg      tUSPUHFRfFreqCfg6C;
    T_USPUHFRfFreqCfg      tUSPUHFRfFreqCfgGB;
} T_USPRdpLlrpRfFreqCfg;
typedef struct  tagT_USPRdpLlrpTransmitPower
{
    unsigned short int wTransmitPower6B;
    unsigned short int wTransmitPower6C;
    unsigned short int wTransmitPowerGB;
}T_USPRdpLlrpTransmitPower;

/*天线的扩展配置*/
typedef struct tagT_USPRdpLlrpAntennaExtConfiguration
{
    unsigned short int                               wAntennaID ;                                 /*如果该值为0,则表示该配置应用于所有天线*/
     /*LLRP_tEForandRevConfigType变成unsigned int*/
    unsigned int eForandRevConfigType;            /*可选值:0 :只做接受天线1 :只做发送天线2 :收发一体*/
    T_USPRdpLlrpRfFreqCfg      tUSPRdpLlrpRfFreqCfg;   /*使用定频或调频的相关设置*/
    T_USPRdpLlrpTransmitPower   tTransmitPower; 
}T_USPRdpLlrpAntennaExtConfiguration;

typedef struct tagT_USPRdpLlrpAntSwitchDelayCfg
{
    unsigned char        ucTurnOnDelay; /*0表示关闭天线切换延时，1表示开启*/
    unsigned char        ucPad;
    unsigned short int   wDelayTime; /*延时时间，单位ms，取值范围[10,1000]*/
}T_USPRdpLlrpAntSwitchDelayCfg;

typedef struct tagT_USPRdpLlrpTagFilterCfg
{
    unsigned char              ucTurnOnOPFilter;//0表示关闭操作过滤，1表示开启
    unsigned char              ucTurnOnRFFilter;//0表示关闭上报过滤，1表示开启
    unsigned char              ucOPKeepaliveTime;//操作过滤保活时间，取值范围[1,255]
    unsigned char              ucOPPollTime;//操作过滤轮询时间，固定为20
    unsigned char              ucRFKeepaliveTime;//上报过滤保活时间，取值范围[1,255]
    unsigned char              ucRFPollTime;//上报过滤轮询时间，固定为20
    unsigned short int         wPad;
}T_USPRdpLlrpTagFilterCfg;

typedef struct tagT_USPRdpLlrpPerAntUDPCfg
{
    unsigned int        dwReaderIP; /*边界天线相邻阅读器IP */
    unsigned char              ucAntIndex; /*边界天线号，1-4*/
    unsigned char              ucLinkNo;//链路号，固定为5和6
    unsigned short int        wPort;//端口号，固定为8088
}T_USPRdpLlrpPerAntUDPCfg;

typedef struct tagT_USPRdpLlrpAntCoopUDPCfg
{
    unsigned char                  ucAntNum; /*临界天线数，可取值为1 2*/
    unsigned char                  ucT1;//固定为20ms
    unsigned char                  ucN1;//固定为2
    unsigned char                  ucPad;//填充字节，保证对齐
    unsigned short int             wT2;//固定为1000ms
    unsigned short int             wPad;
    T_USPRdpLlrpPerAntUDPCfg  atPerAntUDPCfg [2]; /*Udp的ip配置*/
}T_USPRdpLlrpAntCoopUDPCfg; 

typedef struct tagT_USPRdpLlrpAntCoopCfg
{
    unsigned char                       ucTurnOnAntCoop; /*天线联动开关，0表示关闭该功能，1表示UDP联动方式，2表示GPIO联动 方式（暂不支持）*/
    unsigned char                       ucPad;
    unsigned short int                  wPad;
    T_USPRdpLlrpAntCoopUDPCfg    tAntCoopUDPCfg; /*UDP联动配置*/
}T_USPRdpLlrpAntCoopCfg;

typedef struct tagT_USPRdpLlrpRSSISortCfg
{
    unsigned char        ucTurnOnSort; /*0表示关闭排序功能，1表示开启*/
    unsigned char        ucPad;
    unsigned short int   wSortNodeNum;/*固定为5，宏定义*/
    unsigned short int   wOTTime; /*排序超时时间，单位为s，取值范围[1,65535]，默认值为30*/
    unsigned short int   wpad;
} T_USPRdpLlrpRSSISortCfg;

typedef struct tagT_USPRdpLlrpAdvancedConfig
{
    T_USPRdpLlrpTagFilterCfg                                   tTagFilterCfg; 
}T_USPRdpAdvancedConfig;

 typedef struct tagT_RdpConfig
{
    T_USPRdpLlrpReaderEventNotificationSpec     tUSPRdpLlrpReaderEventNotificationSpec[READER_MAX_EVENT_NUM];/*事件上报通知的设置READER_MAX_EVENT_NUM = 9*/ 
    T_USPRdpLlrpAntennaProperties                    tUSPLlrpRdpAntennaProperties[READER_ANTENNA_COUNT];/*一根天线属性  READER_ANTENNA_COUNT = 4*/
    T_USPRdpLlrpAntennaConfiguration               tUSPRdpLlrpAntennaConfiguration[READER_ANTENNA_COUNT];/*一根天线的配置*/ 
    T_USPRdpLlrpROReportConfig                       tROReportSpec;                       /*ro报告配置*/
    T_USPRdpLlrpAccessReportConifg                 tAccessReportSpec ;                  /*ACCESS触发条件*/
    T_USPRdpLlrpEventsAndReports                    tEventsAndReports;                    /*断链缓存报告设置*/    
    T_USPRdpLlrpAntennaExtConfiguration           trAntennaExtConfiguration[READER_ANTENNA_COUNT];      /*天线的扩展配置*/     
    T_USPRdpAdvancedConfig                        tUSPRdpAdvancedConfig;
}T_RdpConfig;
 


#endif
