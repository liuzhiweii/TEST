#ifndef  UHF_LLRP_RULE_H
#define  UHF_LLRP_RULE_H
#if 1
#include "zmq.h"
#include "zmq_utils.h"
#include "parson.h"
#include "utimer.h"
#include "uhf.conf"
#include "usp_uhf_cfg.h"
#include "usp_uhf_epc.h"
#include "usp_uhf_iso6b.h"
#include "usp_uhf_gb.h"   // support for GB
#include "usp_uhf_err.h"
#include "usp_uhf.h"
#include "usp_ltk.h"
#include "usp_uhfllrpconfig.h"
#endif

#include "rdpprotocolpub.h"

 
 /*
 void llrp_addRo(T_Msg *ptMsg, LLRP_tSADD_ROSPEC *ptLLRP_tSADDROSpec);
 void llrp_deleteRo(T_Msg *ptMsg, LLRP_tSDELETE_ROSPEC  *ptLLRP_tSDELETE_ROSPEC);
 void llrp_enableRo(T_Msg *ptMsg, LLRP_tSENABLE_ROSPEC  *ptLLRP_tSENABLE_ROSPEC);
 void llrp_disableRo(T_Msg *ptMsg, LLRP_tSDISABLE_ROSPEC *ptLLRP_tSDISABLE_ROSPEC);
 void llrp_startRo(T_Msg *ptMsg, LLRP_tSSTART_ROSPEC *ptLLRP_tSSTART_ROSPEC);
 void llrp_stopRo(T_Msg *ptMsg, LLRP_tSSTOP_ROSPEC *ptLLRP_tSSTOP_ROSPEC);
 void llrp_addAo(T_Msg *ptMsg, LLRP_tSADD_ACCESSSPEC   *ptLLRP_tSADD_ACCESSSPEC);
 void llrp_deleteAo(T_Msg *ptMsg, LLRP_tSDELETE_ACCESSSPEC   *ptLLRP_tSDELETE_ACCESSSPEC);
 void llrp_disableAo(T_Msg *ptMsg, LLRP_tSDISABLE_ACCESSSPEC *ptLLRP_tSDISABLE_ACCESSSPEC);
 void llrp_enableAo(T_Msg *ptMsg, LLRP_tSENABLE_ACCESSSPEC *ptLLRP_tSENABLE_ACCESSSPEC);
 void llrp_getRo(T_Msg *ptRcvMsg, LLRP_tSGET_ROSPECS *ptLLRP_tSGET_ROSPECS);
 void llrp_getAo(T_Msg *ptRcvMsg, LLRP_tSGET_ACCESSSPECS *ptLLRP_tSGET_ACCESSSPECS);
 void llrp_getReport(T_Msg *ptRcvMsg,LLRP_tSGET_REPORT *ptLLRP_tSGET_REPORT);
 void llrp_externPeriodtimerForRoStartTrigger(T_Msg *ptRcvMsg);
 */
/**************************Rdp的全局变量********************************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/
/*Llrp线程定义的全局变量结构*/
typedef struct tagT_RdpLlrpCtrl
{
    unsigned short int   wRDPLlrpState;
    unsigned int  bIsConfigChg;
    unsigned short int   wPad;
}T_RdpLlrpCtrl;

/**************************阅读器调度的相关数据结构**************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/

typedef struct tagT_RdpLlrpROEntry
{
    unsigned int  dwROIndex;
    unsigned int   dwPriority;
    struct tagT_RdpLlrpROEntry *ptNext;
}T_RdpLlrpROEntry;




typedef struct tagT_RdpLlrpROActiveEntry 
{
    unsigned int   dwROIndex;
}T_RdpLlrpROActiveEntry;


typedef struct tagT_RdpLlrpAccessEntry
{
    unsigned int  dwAccessIndex;
    struct tagT_RdpLlrpAccessEntry *ptNext;
}T_RdpLlrpAccessEntry;

/******************    Ro的StartTrigger 相关数据*******************************************************/

/*收到enable消息时startTrigger的处理period 和immdiate*/
typedef void ( *usp_rdp_llrp_EnableStartTrigger)(void*);
/*外部触发事件的trigger处理*/
typedef void ( *usp_rdp_llrp_ExternalStartTrigger)(void *);
/*周期性Ro结束时的重复开始*/
typedef void ( *usp_rdp_llrp_PeriodStartTrigger)(void *);
/*根据不同的startTrigger处理不同的流程*/
typedef void ( *usp_rdp_llrp_InitStartTrigger)(void  *);

typedef struct  tagT_RdpLlrpRoPeriodOfStartTrigger
{

    unsigned long long lwUTCTimestampMicroSec; 
    unsigned int dwOffset;
    unsigned int dwPeriod;
}T_RdpLlrpRoPeriodOfStartTrigger;


typedef struct tagT_RdpLlrpRoGpiOfStartTrigger
{
     unsigned int dwGPIPortNum;
     unsigned int  ucGPIEvent;
     unsigned int dwTimeout;
    
}T_RdpLlrpRoGpiOfStartTrigger;

typedef union  tagT_RdpLlrpRoParamOfStartTrigger
{
     T_RdpLlrpRoGpiOfStartTrigger        tRdpLlrpRoGpiOfStartTrigger;
     T_RdpLlrpRoPeriodOfStartTrigger    tRdpLlrpRoPeriodOfStartTrigger;
     
}T_RdpLlrpRoParamOfStartTrigger;

typedef struct tagT_RdpLlrpROStartTrigger
{
    unsigned int dwROSpecStartTriggerType;
    T_RdpLlrpRoParamOfStartTrigger         tRdpLlrpRoParamOfStartTrigger; 
    usp_rdp_llrp_InitStartTrigger            pfusp_rdp_llrp_InitStartTrigger;
    usp_rdp_llrp_EnableStartTrigger        pfusp_rdp_llrp_EnableStartTrigger;
    usp_rdp_llrp_ExternalStartTrigger      pfusp_rdp_llrp_ExternalStartTrigger;
    usp_rdp_llrp_PeriodStartTrigger         pfusp_rdp_llrp_PeriodStartTrigger;
}T_RdpLlrpROStartTrigger;

/******************    Ro的StopTrigger 相关数据*****************************************************/

/*外部触发事件的trigger处理*/
typedef void ( * usp_rdp_llrp_externalStoptTrigger)(void *);
/*每轮帧结束后即AP结束后的判断*/
typedef void ( * usp_rdp_llrp_endofAPDealforStopTrigger)(void*);
/*判断stopTrigger是否发生*/
typedef unsigned int  ( * usp_rdp_llrp_judgeHappenforStopTrigger)(void *);
/*stopTrigger的初始化*/
typedef void ( *usp_rdp_llrp_initStopTrigger)(void *);

typedef struct tagT_RdpLlrpRoGpiOfStopTrigger
{
     unsigned int dwGPIPortNum;
     unsigned int  ucGPIEvent;
     unsigned int dwTimeout;
    
}T_RdpLlrpRoGpiOfStopTrigger;


typedef struct  tagT_RdpLlrpRoDurationOfStopTrigger
{
    unsigned int dwDuration;   
    
}T_RdpLlrpRoDurationOfStopTrigger;



typedef union  tagT_RdpLlrpRoParamOfStopTrigger
{
     
     T_RdpLlrpRoGpiOfStopTrigger            tRdpLlrpRoGpiOfStopTrigger ;
     T_RdpLlrpRoDurationOfStopTrigger    tRdpLlrpRoDurationOfStopTrigger;
     
}T_RdpLlrpRoParamOfStopTrigger;


typedef struct tagT_RdpLlrpROStopTrigger   
{
    unsigned int dwROStopTriggerState;/*发生为1 未发生为0*/    
    T_RdpLlrpRoParamOfStopTrigger                tRdpLlrpRoParamOfStopTrigger; 
    usp_rdp_llrp_initStopTrigger                          pfusp_rdp_llrp_initStopTrigger;
    usp_rdp_llrp_externalStoptTrigger                  pfusp_rdp_llrp_externalStoptTrigger;
    usp_rdp_llrp_endofAPDealforStopTrigger         pfusp_rdp_llrp_endofAPDealforStopTrigger;
    usp_rdp_llrp_judgeHappenforStopTrigger           pfusp_rdp_llrp_judgeHappenforStopTrigger;
    
}T_RdpLlrpROStopTrigger;

/**************************RO和Ao的报告相关数据结构***************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/


/*Access操作的控制结构*/
typedef struct  T_RdpLlrpOpResultCtrl
{
    unsigned short int wOpSpecID; /*OpId*/ 
    unsigned short int wOpType; /*Op的类型*/
    unsigned short int wResult; 
    unsigned short int wOpResultAddr;
    unsigned short int wOpResultlen;
    unsigned short int wOpOriginalLen;
    unsigned short int wOpOriginalAddr;
    unsigned short int wPad;
}T_RdpLlrpOpResultCtrl;

typedef LLRP_tEAirProtocols EAirProtocols;



typedef struct tagT_RdpLlrpISOID
{
    unsigned short int wTagDataLen;    /* 标签数据长度，以WORD为单位，不包括PC字段  */
    unsigned char      aucTagData[2];      /* 变长 EPC 数据的第一个数据段 */
    
}T_RdpLlrpISOID;


typedef struct  tagT_RdpLlrpEpcID
{
    unsigned short int wTagDataLen;    /* 标签数据长度，以WORD为单位，不包括PC字段  */
    unsigned short int awTagData[1];      /* 变长 EPC 数据的第一个数据段 */
    
}T_RdpLlrpEpcID;

typedef struct  tagT_RdpLlrpGBID
{
    unsigned short int wTagDataLen;    /* 标签数据长度，以WORD为单位，不包括PC字段  */
    unsigned short int awTagData[1];      /* 变长 EPC 数据的第一个数据段 */
}T_RdpLlrpGBID;

typedef union  tagT_RdpLlrpID
{
    T_RdpLlrpEpcID    tEpcID;
    T_RdpLlrpISOID    tISOID;
    T_RdpLlrpGBID    tGBID;
}T_RdpLlrpID;


typedef struct  tagT_RdpLlrpROTagReport
{
    unsigned int                  dwROSpecID;
    unsigned short int                  wSpecIndex;
    unsigned short int                  wInventoryParameterSpecID;
    unsigned short int                  wAntennaID;
    unsigned short int                  wPeakRSSI;
    unsigned short int                  wChannelIndex;
    unsigned long long                  lwFirstSeenTimestampUTC;
    unsigned long long                  lwLastSeenTimestampUTC;
    unsigned short int                  wTagCount;
    unsigned short int                  wPC_Bits;
    unsigned short int                  wCRC;
    unsigned int                  dwAccessSpecID; 
    EAirProtocols            eProtocolID;
    T_RdpLlrpID              tID;
    
}T_RdpLlrpROTagReport;


 #define USP_RDP_LLRP_UID_SIZE        (unsigned int)62


/*唯一性标识*/
typedef struct tagT_RdpLlrpUID
{
    unsigned short int wTagDataLen;    /*字节为单位*/
    unsigned char      aucTagData[USP_RDP_LLRP_UID_SIZE];      
    
}T_RdpLlrpUID;

typedef struct  tagT_RdpLlrpAccessTagReport
{
    unsigned int                  dwROSpecID;
    unsigned short int                  wSpecIndex;
    unsigned short int                  wInventoryParameterSpecID;
    unsigned short int                  wAntennaID;
    unsigned short int                  wPeakRSSI;
    unsigned short int                  wChannelIndex;
    unsigned long long                  lwFirstSeenTimestampUTC;
    unsigned long long                  lwLastSeenTimestampUTC;
    unsigned short int                  wTagCount;
    unsigned short int                  wPC_Bits;
    unsigned short int                  wCRC;
    unsigned int                  dwAccessSpecID; 
    EAirProtocols            eProtocolID;
    unsigned int                    dwOpNum;
    T_RdpLlrpOpResultCtrl    tListofOpResultCtrl[MAX_NUM_OPSPECS_PER_ACCESSSPEC];
    T_RdpLlrpID        tID;
    unsigned char aucData[0];    
}T_RdpLlrpAccessTagReport;

typedef union  tagT_RdpLlrpTagReport
{
    T_RdpLlrpROTagReport         tROTagReport;
    T_RdpLlrpAccessTagReport   tAccessTagReport;
    
 }T_RdpLlrpTagReport;

typedef struct tagT_RdpLlrpSignalReportCtrl
{
    unsigned char                                  ucReportType; /*0 ROReport 1 AccessReport */
    unsigned char                                  ucROType; /*0 单次 1 周期 */
    unsigned short int                                  wMsgLen;
    /*每个报告都有唯一性标识赋值到这里*/
    T_RdpLlrpUID                      tUID;
    struct tagT_RdpLlrpSignalReportCtrl   *ptlast;
    struct tagT_RdpLlrpSignalReportCtrl   *ptNext;   
    T_RdpLlrpTagReport   tRdpLlrpTagReport;
}T_RdpLlrpSingleReportCtrl;

/* 用于保存RO的上报条件为NULL的积累报告的数量*/

typedef struct   tagT_RdpLlrpAcculateReportData
{
    /*链路标识和控制*/
    unsigned char ucLinkIndex;
    unsigned char ucLinkType;
    unsigned char ucPad[2];
    unsigned int dwReportSize;  
    unsigned int dwReportNum;  	
    T_RdpLlrpSingleReportCtrl *ptAcculateReportHead;    
    T_RdpLlrpSingleReportCtrl *ptActiveRoReportTail;
}T_RdpLlrpAcculateReportData;


typedef struct  tagT_RdpLlrpSendReportContent
{
   unsigned int dwMessgeID;
   T_RdpLlrpSingleReportCtrl *ptReportAddr;
}T_RdpLlrpSendReportContent;

typedef struct  tagT_RdpAddAo
{
   /*Ao报告的方式*/
   unsigned int dwAOReportSndTrigger;
   LLRP_tSMessage *ptAddAoMsgAddr;
}T_RdpAddAo;


/*以下是设置的各种操作返回结果的内部结构*/

typedef struct   tagT_RdpLlrpEpcWriteOpResult
{
    LLRP_tEC1G2WriteResultType eResult;
    unsigned short int                               wOpSpecID;
    unsigned short int                               wNumWordsWritten;
}T_RdpLlrpEpcWriteOpResult;


typedef struct  tagT_RdpLlrpEpcReadOpResult
{
    LLRP_tEC1G2ReadResultType eResult;
    unsigned short int                              wOpSpecID;
    unsigned short int                              wDataLength;
    unsigned char                                    aucData[0];
}T_RdpLlrpEpcReadOpResult;

typedef struct   tagT_RdpLlrpEpcKillOpResult
{
    LLRP_tEC1G2KillResultType eResult;
    unsigned short int                            wOpSpecID;  
}T_RdpLlrpEpcKillOpResult;

typedef struct    tagT_RdpLlrpEpcLockOpResult
{
    LLRP_tEC1G2LockResultType eResult;
    unsigned short int                              wOpSpecID;
}T_RdpLlrpEpcLockOpResult;

typedef struct   tagT_RdpLlrpEpcBlcokLockOpResult
{
    unsigned short int     wOpSpecID;
    unsigned short int     wReadLock;
    unsigned int     dwResult; 
    unsigned short int     wLockStateLen;
    unsigned char          ucLockState[1];
    unsigned char          ucPad[1];  
}T_RdpLlrpEpcBlcokLockOpResult;

typedef struct  tagT_RdpLlrpEpcAlienReadLockOpResult
{
    unsigned short int     wOpSpecID;
    unsigned short int     wPad;
    unsigned int     dwResult; 

}T_RdpLlrpEpcAlienReadLockOpResult;


typedef struct  TagT_RdpLlrpEpcWriteVerifyResult
{
    unsigned short int  wOpSpecID;
    unsigned short int  wPad;
    unsigned int  dwResult;  
}T_RdpLlrpEpcWriteVerifyResult;
typedef struct   tagT_RdpLlrpISO6BReadOpResult
{
    unsigned char       ucResult;
    unsigned char       ucSuccessLength;
    unsigned short int   wOpSpecID;
    unsigned short int   wDataLength;
    unsigned char       aucData[2];
}T_RdpLlrpISO6BReadOpResult;

typedef struct   tagT_RdpLlrpISO6BWriteOpResult
{
    unsigned char       ucResult;
    unsigned char       ucPad[3];
    unsigned short int wOpSpecID;
    unsigned short int wNumWordsWritten;
}T_RdpLlrpISO6BWriteOpResult;

typedef struct  tagT_RdpLlrpISO6BLockOpResult
{
    unsigned char       ucResult;
    unsigned short int wOpSpecID;
    unsigned short int wDataLength;
    unsigned char       aucData[3];
}T_RdpLlrpISO6BLockOpResult;
  
typedef struct  tagT_RdpLlrpISO6BLockQueryOpResult
{
    unsigned short int  wOpSpecID;
    unsigned short int  wDataLength;
    unsigned char        aucData[0];
}T_RdpLlrpISO6BLockQueryOpResult;


typedef struct tagT_RdpLlrpEpcImpinjSetQTOpResult
{
    unsigned short int wOpSpecID;
    unsigned short int wResult;	
}T_RdpLlrpEpcImpinjSetQTOpResult;

typedef struct  tagT_RdpLlrpEpcImpinjGetQTOpResult
{
    unsigned short int wOpSpecID;
    unsigned short int wResult;	
    unsigned short int wDataProfile;	
    unsigned short int wAccessRange;		 
	
}T_RdpLlrpEpcImpinjGetQTOpResult;

typedef struct   tagT_RdpLlrpGBWriteOpResult
{
    unsigned int                               dwResult;
    unsigned short int                               wOpSpecID;
    unsigned short int                               wNumWordsWritten;
}T_RdpLlrpGBWriteOpResult;

typedef struct   tagT_RdpLlrpGBEraseOpResult
{
    unsigned int                               dwResult;
    unsigned short int                               wOpSpecID;
    unsigned short int                               wNumWordsErase;
}T_RdpLlrpGBEraseOpResult;


typedef struct  tagT_RdpLlrpGBReadOpResult
{
    unsigned int                               dwResult;
    unsigned short int                              wOpSpecID;
    unsigned short int                              wDataLength;
    unsigned char                                    aucData[0];
}T_RdpLlrpGBReadOpResult;

typedef struct   tagT_RdpLlrpGBKillOpResult
{
    unsigned int                               dwResult;
    unsigned short int                            wOpSpecID;  
}T_RdpLlrpGBKillOpResult;

typedef struct    tagT_RdpLlrpGBLockOpResult
{
    unsigned int                               dwResult;
    unsigned short int                              wOpSpecID;
}T_RdpLlrpGBLockOpResult;

/******************    Ro的report Trigger 即相关报告数据相关数据********************/

 /*外部触发事件的trigger处理*/
 
typedef void ( * usp_rdp_llrp_InitAIForReportTrigger) (void *);
typedef void ( * usp_rdp_llrp_InitROForReportTrigger)(void *); 

/*每轮帧结束后即AP结束后的判断*/
typedef unsigned int ( * usp_rdp_llrp_JudgeReportNumForReportTrigger)(void *);
/*判断stopTrigger是否发生*/
typedef unsigned int  ( * usp_rdp_llrp_EndAIForReportTrigger)(void *);
/*stopTrigger的初始化*/
typedef unsigned int ( *usp_rdp_llrp_EndROForReportTrigger)(void *);


typedef struct tagT_rdpLlrpROReport
{
    unsigned int                                                           bIsDefaultCfgFlag;
    unsigned short int                                                            wThresholdOfReportNum;  
    unsigned short int                                                            wPad;  
    T_USPRdpLlrpTagReportContentSelector               tRdpLlrpTagReportContentSelector ;   
    usp_rdp_llrp_InitAIForReportTrigger                   pfusp_rdp_llrp_InitAIForReportTrigger;
    usp_rdp_llrp_InitROForReportTrigger                  pfusp_rdp_llrp_InitROForReportTrigger;
    usp_rdp_llrp_JudgeReportNumForReportTrigger   pfusp_rdp_llrp_JudgeReportNumForReportTrigger;
    usp_rdp_llrp_EndAIForReportTrigger                   pfusp_rdp_llrp_EndAIForReportTrigger;
    usp_rdp_llrp_EndROForReportTrigger                  pfusp_rdp_llrp_EndROForReportTrigger;
    /*当前Ro产生的报告*/
    T_RdpLlrpAcculateReportData                        tActiveRoReportLink;
}T_RdpLlrpROReport;      



typedef struct tagT_RdpLlrpDynamicRo
{
  struct tagT_RdpLlrpDynamicRo *ptNext;
  LLRP_tSADD_ROSPEC *ptAddRo;
}T_RdpLlrpDynamicRo;

typedef struct tagT_RdpLlrpDynamicAccess
{
  struct tagT_RdpLlrpDynamicAccess*ptNext;
  LLRP_tSADD_ACCESSSPEC *ptAddAccess;
}T_RdpLlrpDynamicAccess;
/*全局变量不应该在这里*/

/*阅读器各条链路缓存的报告等待GetReport消息上报报告*/





/**************************AI的stopTrigger的参数定义************************************************/

 /*外部触发事件的trigger处理*/
 
typedef void ( * usp_rdp_llrp_initAIForAIStopTrigger) (void   *);
 /*AI结束条件积累，例如n个标签每次清点时 获取*/
typedef void ( * usp_rdp_llrp_AccmulateForAIStopTrigger)(void *);  

/*AI的stopTrigger 外部触发条件处理*/
typedef void ( * usp_rdp_llrp_ExternalTriggerForAIStopTrigger)(void *); 

/*每轮帧结束后即AP结束后的判断*/
typedef unsigned int ( * usp_rdp_llrp_judgeHappenForAIStopTrigger)(void *);

/*每轮AP结束后判断AI结束条件*/
typedef unsigned int  ( * usp_rdp_llrp_endAPForAIStopTrigger)(void *);
typedef unsigned int  ( * usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger)(void *);

 
typedef struct   tagT_RdpLlrpAIParamForStopTrigger
{   
    
    unsigned short int  wAIExecuteTimes;
    unsigned short int  wNumberOfAttempts;
    unsigned short int  wNumberOfTags;
    unsigned short int  wAITagNum;  
    unsigned int  bAIStopTriggerStatus;
    unsigned long long  lwAIStartTime;
    unsigned long long  lwLastTagSeenTime;
    unsigned int  dwDuration;
    unsigned int  dwTimeOut;
    unsigned int  dwTms;
   
}T_RdpLlrpAIParamForStopTrigger;

typedef struct tagT_RdpLlrpAIGpiOfStopTrigger
{
     unsigned int dwGPIPortNum;
     unsigned int  ucGPIEvent;
     unsigned int dwTimeout;
    
}T_RdpLlrpAIGpiOfStopTrigger;
typedef struct   tagT_RdpLlrpAIStopTrigger
{              
    T_RdpLlrpAIParamForStopTrigger                     tRdpLlrpAIParamForStopTrigger;
    T_RdpLlrpAIGpiOfStopTrigger                          tRdpLlrpAIGpiOfStopTrigger;
    usp_rdp_llrp_initAIForAIStopTrigger                       pfusp_rdp_llrp_initAIForAIStopTrigger;
    usp_rdp_llrp_AccmulateForAIStopTrigger                pfusp_rdp_llrp_AccmulateForAIStopTrigger;
    usp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger  pfusp_rdp_llrp_AccmulateExecuteTimesForAIStopTrigger;
    usp_rdp_llrp_ExternalTriggerForAIStopTrigger         pfusp_rdp_llrp_ExternalTriggerForAIStopTrigger;
    usp_rdp_llrp_judgeHappenForAIStopTrigger            pfusp_rdp_llrp_judgeHappenForAIStopTrigger;
    usp_rdp_llrp_endAPForAIStopTrigger                      pfusp_rdp_llrp_endAPForAIStopTrigger;
    
}T_RdpLlrpAIStopTrigger;

/**************************天线的配置继承控制结构************************************************/

typedef struct   tagT_RdpLlrpC12FilterCtrl
{
    unsigned int bIsDefaultCfgFlag;
    unsigned int bInventoryStateUnawareFilterActionCtrl[MaxEPCSelectNum];
}T_RdpLlrpC12FilterCtrl;

typedef struct   tagT_RdpLlrpISOInvCtrl
{
    unsigned int bIsDefaultCfgFlag;
    unsigned int bISOFilterControl;
    unsigned int bISORFControl;
    unsigned int bISOSingulationControl;
}T_RdpLlrpISOInvCtrl;

typedef struct   tagT_RdpLlrpC1G2InvCtrl

{
    unsigned int                         bIsDefaultCfgFlag;
    unsigned int                         bC1G2Filterctrl;
    unsigned int                         bC1G2RFCtrl;
    unsigned int                         bC1G2SingulationCtrl;
    T_RdpLlrpC12FilterCtrl    tRdpLlrpC12FilterCtrl;
}T_RdpLlrpC1G2InvCtrl;

typedef struct   tagT_RdpLlrpGBFilterCtrl
{
    unsigned int bIsDefaultCfgFlag;
    unsigned int bGBTagInventoryStateAwareFilterAction[MaxGBSortNum];
}T_RdpLlrpGBFilterCtrl;

typedef struct   tagT_RdpLlrpGBInvCtrl

{
    unsigned int                         bIsDefaultCfgFlag;
    unsigned int                         bGBFilterctrl;
    unsigned int                         bGBRFCtrl;
    unsigned int                         bGBSingulationCtrl;
    T_RdpLlrpGBFilterCtrl    tRdpLlrpGBFilterCtrl;
}T_RdpLlrpGBInvCtrl;

typedef struct   tagT_RdpLlrpAirProtocolInvCtrl
{
    T_RdpLlrpC1G2InvCtrl                  tRdpLlrpC1G2InvCtrl;
    T_RdpLlrpISOInvCtrl                     tRdpLlrpISOInvCtrl;
    T_RdpLlrpGBInvCtrl                  tRdpLlrpGBInvCtrl;
}T_RdpLlrpAirProtocolInvCtrl;


typedef struct   tagT_RdpLlrpAntConfigCtrl
{
    /*1 继承 0 携带*/
    unsigned int                             bIsDefaultCfgFlag;
    unsigned int                             bRFT_RFReceiverCtrl;
    unsigned int                             bRFTransmitterCtrl;
    T_RdpLlrpAirProtocolInvCtrl     tRdpLlrpAirProtocolInvCtrl;
}T_RdpLlrpAntConfigCtrl;


/**************************AI的天线和协议的参数定义************************************************/
typedef struct  tagT_RdpLlrpProtocolInvSet
{
    unsigned short int                                                     wInvParamSpecID;
    unsigned short int                                                     wPad;
    EAirProtocols                                               eProtocolID;  
    T_USPRdpLlrpAntennaConfiguration                  tUSPRdpLlrpAntennaConfiguration;
    /*天线配置是否继承的关系*/
    T_RdpLlrpAntConfigCtrl                                  tRdpLlrpAntConfigCtrl;
}T_RdpLlrpProtocolInvSet;

typedef struct   tagT_RdpLlrpAntInv
{
    unsigned char                                     ucAntIndex;  
    unsigned char                                     ucProtocolNum;
    T_RdpLlrpProtocolInvSet           tRdpLlrpProtocolInvSet[MAX_NUM_INVENTORY_PARA_SPECS_PERAISPEC];
}T_RdpLlrpAntInv;

typedef struct   tagT_RdpLlrpAntsInvSet
{
    unsigned char                           ucAntNum;  /* 天线数量*/
    unsigned char                           ucPad[3];
    T_RdpLlrpAntInv     tAntInv[MAX_NUM_ANT_SUPPORT];
}T_RdpLlrpAntsInvSet;


/**************************AI的内部参数定义************************************************/

  typedef struct   tagT_RdpLlrpAI
{
    T_RdpLlrpAIStopTrigger    tRdpLlrpAIStopTrigger;
    T_RdpLlrpAntsInvSet       tRdpLlrpAntsInvSet;
}T_RdpLlrpAI;


typedef struct  tagT_RdpLlrpAISet
    
{
    unsigned short int  wAINum; //RO中specs的数量
    T_RdpLlrpAI  tRdpLlrpAI[MAX_NUM_SPECS_PERROSPEC];
}T_RdpLlrpAISet;



/**************************RO内部参数定义******************************************************/

/*这种怎么定义直接用标准的还是生成一个，枚举的怎么定义*/
typedef struct tagT_RdpLlrpROBoundary
{
    T_RdpLlrpROStartTrigger          tRdpLlrpROStartTrigger;
    T_RdpLlrpROStopTrigger           tRdpLlrpROStopTrigger;
}
T_RdpLlrpROBoundary;
 
typedef struct   tagT_RdpLlrpRO
{
    unsigned int dwROSpecID;
    unsigned char ucPriority;
    LLRP_tEROSpecState          eCurrentState;
    T_RdpLlrpROBoundary         tRdpLlrpROBoundary;
    T_RdpLlrpROReport             tRdpLlrpROReport;   
    T_RdpLlrpAISet                   tRdpLlrpAISet;   
     
}T_RdpLlrpRO;

/**************************RO内部控制结构*******************************************************/
typedef struct tagT_RdpLlrpRODispatchCtrl
{
   
    unsigned char       ucLinkIndex; /*判断链路标识*/
    unsigned char       ucLinkType; 
    unsigned int   wReceiverTno;
    unsigned int   wSenderTno;  
    unsigned char       ucPad[2];
    unsigned int dwUseing; //这个结构是否用到	
    unsigned int dwDispatchStatus; /*保存Ro的调度状态，这里包含Ready和RO的标准状态*/
    LLRP_tEROSpecState  eCurrentState;
    unsigned int dwRevMessageID; /*在Enble时，要赋予他的MessageID ，然后产生报告要添加这个*/
    unsigned int dwDeleteRoMsgID; 
    unsigned int dwDisableRoMsgID; 
    unsigned int dwStopRoMsgID; 
    unsigned int dwDeleteRoID;     /*对于ActiveRo来说 要记录下deleteRo的ID号，以便操作过滤删除掉对应Ro的结构*/
    unsigned int dwDisableRoID;     /*对于ActiveRo来说 要记录下deleteRo的ID号，以便操作过滤删除掉对应Ro的结构*/
    unsigned long long lwStartuSec;
	
}T_RdpLlrpRODispatchCtrl;


typedef struct  tagT_RdpLlrpActiveROCtrlIndex
{
    /*调度用的当前的天线下表，当前的协议下标*/
    unsigned char ucWorkAIIndex;
    unsigned char ucWorkAntIndex;
    unsigned char ucWorkProtocolIndex;
    unsigned char ucPad[1];
}T_RdpLlrpActiveROCtrlIndex;
/***********************************Access stopTrigger的内部结构***********************************************/

typedef void  ( * usp_rdp_llrp_initAOStopTrigger)(void *);
typedef unsigned int ( * usp_rdp_llrp_IncreaseConditionAndJudeEndForAOStopTrigger)(void *);


typedef struct    tagT_RdpLlrpAccessParamStopTrigger
{
    
    unsigned short int wOperationCountValue; /*匹配成功的次数*/
    unsigned short int wCurrentOperationValue;    
}T_RdpLlrpAccessParamStopTrigger;

typedef struct    tagT_RdpLlrpAccessStopTrigger
{  
    T_RdpLlrpAccessParamStopTrigger                                       tRdpLlrpAccessParamStopTrigger;
    usp_rdp_llrp_initAOStopTrigger                                            pfusp_rdp_llrp_initAOStopTrigger;
    usp_rdp_llrp_IncreaseConditionAndJudeEndForAOStopTrigger pfusp_rdp_llrp_IncreaseConditionAndJudeEndForAOStopTrigger;
}T_RdpLlrpAccessStopTrigger;

/***********************************Access Report 内部调度和数据结构***********************************************/
typedef void ( * usp_rdp_llrp_sendOneAOReportForAOReportTrigger)(T_RdpLlrpSingleReportCtrl *);
/*其中参数2是默认的配置*/
typedef void  ( * usp_rdp_llrp_ConstructAOReportForAOReportTrigger)(T_RdpLlrpSingleReportCtrl *);



 /*报告构建函数是不是也可以封装到Ro和Ao内部来，如果封装 AO中应该有一份报告的内容的配置
    构造报告的函数指针*/
typedef struct tagT_RdpLlrpAccessReport
{
    unsigned int                                                                 bIsDefaultCfgFlag;
    /*匹配成功就拷贝一份从Ro到AO中*/
    T_USPRdpLlrpTagReportContentSelector                   tUSPRdpLlrpTagReportContentSelector; 
    usp_rdp_llrp_sendOneAOReportForAOReportTrigger    pfusp_rdp_llrp_sendOneAOReportForAOReportTrigger;  
    usp_rdp_llrp_ConstructAOReportForAOReportTrigger pfusp_rdp_llrp_ConstructAOReportForAOReportTrigger; 
}T_RdpLlrpAccessReport;
 


/***************************Access command 的内部结构**********************************************************/
#define MAX_PATTERN_Buffer  512

typedef unsigned char T_TagPatternBuffer[512];

#define MAX_OP_Buffer 300

typedef unsigned char T_OpBuffer[MAX_OP_Buffer];

#define MAX_TAG_PATTERN_NUM  2
typedef struct   tagT_RdpLlrpOPCtrl
{
    unsigned short int wOpType; 
    unsigned short int wOpID;
    unsigned short int wOpLen;
    unsigned short int wPad;
    unsigned int dwAccessPassword;
}T_RdpLlrpOPCtrl;    

 typedef struct   tagT_RdpLlrpAirProtocolTagCtrl
{
    unsigned int                  dwTagPatternNum;
    T_TagPatternBuffer   tTagPattern[MAX_TAG_PATTERN_NUM];  
}T_RdpLlrpAirProtocolTagCtrl;


 typedef struct  tagT_RdpLlrpListOPCtrlSet
{
    unsigned short int             wOPNum;
    unsigned short int             wOpIndex;
    T_RdpLlrpOPCtrl   tRdpLlrpOPCtr[MAX_NUM_OPSPECS_PER_ACCESSSPEC]; /*存储最大数量*/
    T_OpBuffer         tSingleOp[MAX_NUM_OPSPECS_PER_ACCESSSPEC];
}T_RdpLlrpListOPCtrlSet;
 

typedef struct  tagT_RdpLlrpAccessCmdCtrl
{
    unsigned int                               bCircumstanceSetting;
    unsigned int                               bClientRequest;
    T_RdpLlrpAirProtocolTagCtrl       tAirProtocolTag;
    T_RdpLlrpListOPCtrlSet             tRdpLlrpListOPCtrlSet;
    T_RdpLlrpUID                          tUID;
}T_RdpLlrpAccessCmdCtrl;

typedef struct tagT_RdpLlrpClientRequestOpSet
{
    LLRP_tEAirProtocols eProtocolID; 
    T_RdpLlrpListOPCtrlSet tListOp;
    T_RdpLlrpUID tMatchUID;
}T_RdpLlrpClientRequestOpSet;


/**************************AO内部结构参数定义************************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/
typedef struct  tagT_RdpLlrpActiveAccessCtrlIndex
{
    /*调度用的当前的天线下表，当前的协议下标*/
    unsigned char ucWorkOpIndex;
    unsigned char ucPad[3];
}T_RdpLlrpActiveAccessCtrlIndex;

typedef struct   tagT_RdpLlrpAccess
{
   
    unsigned int                                    dwAccessSpecID;
    unsigned short int                                    wAntennaID;
    unsigned short int                                    wPad;
    unsigned int                                    dwROSpecID; /*0所有的都适用*/
    LLRP_tEAirProtocols                     eProtocolID; /*EPC 1 18000-B 100*/
    /*access的当前状态 在运行时接收到delete等命令，转换状态，
    每次匹配返回时，先检测状态，进行相应操作*/
    LLRP_tEAccessSpecState             eCurrentState;
    T_RdpLlrpAccessStopTrigger        tRdpLlrpAccessStopTrigger;
    T_RdpLlrpAccessReport               tRdpLlrpAccessReport;
    T_RdpLlrpAccessCmdCtrl             tRdpLlrpAccessCmdCtrl;
    /*空间应该不存在问题 可以静态分配*/
}T_RdpLlrpAccess;

typedef struct   tagT_RdpLlrpAccessDispatchCtrl
{
    unsigned int    ucUseing; //这个结构是否用到
    unsigned char        ucLinkIndex; /*判断链路标识*/
    unsigned char        ucLinkType;
    unsigned int   wReceiverTno;
    unsigned int   wSenderTno;    
    unsigned int  dwMessageID; /*记录最后一条AO指令*/
    unsigned int  dwDeleteAccessMsgID; /*记录最后一条AO指令*/
    unsigned int  dwDisableAccessMsgID; /*记录最后一条AO指令*/
    unsigned int dwDeleteAccessID;     /*对于ActiveAccess来说 要记录下deleteAccess的ID号，以便操作过滤删除掉对应Access的结构*/
    unsigned int dwDisableAccessID;     /*对于ActiveAccess来说 要记录下deleteAccess的ID号，以便操作过滤删除掉对应Access的结构*/
    unsigned int  dwReportTrigger;
    unsigned int  dwDispatchStatus;
}T_RdpLlrpAccessDispatchCtrl;

typedef struct  tagT_RdpLlrpAccessCtrlAndParam
{
    T_RdpLlrpAccessDispatchCtrl   tRdpLlrpAccessDispatchCtrl;
    T_RdpLlrpActiveAccessCtrlIndex     tRdpLlrpActiveAccessCtrlIndex; 
    T_RdpLlrpUID                       tMatchUID;/*匹配的EPC或者ISO码字*/
    T_RdpLlrpAccess                  tRdpLlrpAccess;
}T_RdpLlrpAccessCtrlAndParam;

/**************************RO内部结构参数定义************************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/
typedef struct  tagT_RdpLlrpROCtrlAndParam
{
    T_RdpLlrpRODispatchCtrl      tRdpLlrpRODispatchCtrl;
    T_RdpLlrpActiveROCtrlIndex tRdpLlrpActiveROCtrlIndex;
    T_RdpLlrpAccessCtrlAndParam *ptMatchAccessCtrlAndPara;
    T_RdpLlrpRO                       tRdpLlrpROSpec;
}T_RdpLlrpROCtrlAndParam;

typedef struct  TagT_RdpLlrpReaderRoData
{
      T_RdpLlrpROEntry          tAddQueuehead;  
      T_RdpLlrpROEntry          tAddQueuetail;  
      T_RdpLlrpROEntry           tDisableRoQueuehead;
      T_RdpLlrpROEntry           tInactiveRoQueuehead;   
      T_RdpLlrpROEntry           tReadyRoQueuehead; 
      T_RdpLlrpROEntry           tActiveRO;   
      T_RdpLlrpROCtrlAndParam   tRdpLlrpROCtrlAndParam[MAX_NUM_RO_SPEC];
}T_RdpLlrpReaderRoData;

typedef struct  TagT_RdpLlrpReaderAccessData
{
      T_RdpLlrpAccessEntry              tAddAccessQueue;   
      T_RdpLlrpAccessEntry              tEnableAccessQueue;
      T_RdpLlrpAccessEntry              tRunAccess;
      T_RdpLlrpAccessCtrlAndParam   tRdpLlrpAccessCtrlAndParam[MAX_NUM_ACCESSSPECS];
}T_RdpLlrpReaderAccessData;

/*Ro调度的相关数据结构*/
typedef void ( *Add_RO)(T_Msg *,void *,T_RdpLlrpReaderRoData *);
typedef void ( *Enable_RO)(T_Msg *,void *,T_RdpLlrpReaderRoData *);
typedef void ( *Disable_RO)(T_Msg *,void *,T_RdpLlrpReaderRoData *);
typedef void ( *Start_RO)(T_Msg *,void *,T_RdpLlrpReaderRoData *);
typedef void ( *Stop_RO)(T_Msg *,void *,T_RdpLlrpReaderRoData *);
typedef void ( *Delete_RO)(T_Msg *,void *,T_RdpLlrpReaderRoData *);
 typedef void ( *Add_Access)(T_Msg *,void *,T_RdpLlrpReaderAccessData *);
 typedef void ( *Enable_Access)(T_Msg *,void *,T_RdpLlrpReaderAccessData *);
 typedef void ( *Disable_Access)(T_Msg *,void *,T_RdpLlrpReaderAccessData *);
 typedef void ( *Delete_Access)(T_Msg *,void *,T_RdpLlrpReaderAccessData *);
 /*扫描Ro进入到工作状态*/
typedef void ( *ScanReadyROToRun)(T_RdpLlrpReaderRoData *);
 
/*RO的调度队列 */
typedef struct  tagT_RdpLlrpReaderDispatch
{
      Add_RO      pfAdd_RO;   
      Enable_RO  pfEnable_RO;
      Disable_RO pfDisable_RO;   
      Start_RO    pfStart_RO;   
      Stop_RO    pfStop_RO;   
      Delete_RO pfDelete_RO;   
      Add_Access   *pfAdd_Access;
      Enable_Access   *pfEnable_Access;
      Disable_Access   *pfDisable_Access;
      Delete_Access    *pfDelete_Access;
      
      ScanReadyROToRun            pfScanROToRun;
      T_RdpLlrpReaderAccessData *ptReaderAccessSpecData;            
      T_RdpLlrpReaderRoData        *ptReaderRoSpecData;
}T_RdpLlrpReaderDispatch;
     

/**************************RO和Ao的报告相关数据结构***************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/

typedef struct  tagT_RdpLlrpC1G2Read
{
    unsigned int     dwRCPCommand;
    unsigned char          ucMB;
    unsigned char           ucPad;
    unsigned short int     wOpSpecID;
    unsigned int     dwAccessPassword;
    unsigned short int     wWordPointer;
    unsigned short int     wWordCount;
   
}T_RdpLlrpC1G2Read;


typedef struct  tagT_RdpLlrpC1G2Write
{ 
    unsigned int     dwRCPCommand;
    unsigned short int    wOpSpecID;
    unsigned char         ucMB;
    unsigned char         ucIsBlockWrite;   /*1 使用块写 0 普通写*/ 
    unsigned char         wPad[2];
    unsigned int   dwAccessPassword;
    unsigned short int   wWordPointer;
    unsigned short int   wDataLength;
      
    unsigned char        aucData[0]; /*变长写入数据*/
}T_RdpLlrpC1G2Write;

typedef struct  tagT_RdpLlrpC1G2LockPayload
{
    LLRP_tEC1G2LockPrivilege  Privilege;
    LLRP_tEC1G2LockDataField DataField;
}T_RdpLlrpC1G2LockPayload;

typedef struct   tagT_RdpLlrpC1G2LockPayloadList
{
    unsigned short int                            wPayLoadNum;
    unsigned short int                            wPad;
    T_RdpLlrpC1G2LockPayload tRdpLlrpC1G2LockPayLoad[5];
}T_RdpLlrpC1G2LockPayloadList;

typedef struct   tagT_RdpLlrpC1G2Lock
{
     unsigned int                                dwRCPCommand;
    unsigned short int                                 wOpSpecID;
    unsigned short int                                 wPad;
    unsigned int                                 dwAccessPassword;
    T_RdpLlrpC1G2LockPayloadList tRdpLlrpC1G2LockPayLoad;   /*锁和解锁操作的定义组*/
}T_RdpLlrpC1G2Lock;

typedef struct   tagT_RdpLlrpC1G2Kill
{
    unsigned int     dwRCPCommand;
    unsigned short int wOpSpecID;
    unsigned short int wPad;
    unsigned int wKillPassword;
}T_RdpLlrpC1G2Kill;
 
typedef struct   tagT_RdpLlrpC1G2BlockLock
{
    unsigned int     dwRCPCommand;
    unsigned char        ucMB;
    unsigned char        ucReadLock;
    unsigned short int  wOpSpecID;
    unsigned short int  ucRFU;
    unsigned short int  wBlockPtr;
    unsigned short int  wBlockRange;
    unsigned int  dwAccessPassword;
    unsigned char       ucMask[512];
}T_RdpLlrpC1G2BlockLock;

/*ALEN 专有接口读保护*/
 
typedef struct   tagT_RdpLlrpC1G2ReadLock
{
    unsigned int     dwRCPCommand;
    unsigned short int      wOpSpecID;
    unsigned char          ucMask;
    unsigned char          ucPad;
    unsigned int    dwAccessPassword;
}T_RdpLlrpC1G2ReadLock;

 typedef struct T_RdpLlrpC1G2IPJQT
{
   unsigned short int wOpSpecID;
   unsigned short int wDataProfile;
   unsigned short int wAccessRange;
   unsigned short int wPersistence;
   unsigned short int wReadOrWrite;
   unsigned short int wpad;
   unsigned int dwAccessPassword;
   unsigned int dwRCPCommand;
}T_RdpLlrpC1G2IPJQT;
/* ISO6B Access 参数*/

typedef struct tagISO6BTagId
{
    unsigned short int wTagDataLen;    /* 变长 UID 数据的第一个数据段，长度由wUID_bits_Len字段决定,目前长度为64bit   */
    unsigned char aucTagData[8];
}
T_ISO6BTagId;

typedef struct tagISO6BReadControl
{
    unsigned char ucCommandType;
    unsigned char ucRetryTimes;
}
T_ISO6BReadControl;

typedef struct tagISO6BRead
{
    unsigned char ucBytePtr;
    unsigned char ucByteCount;
    T_ISO6BReadControl t6BReadControl;
    T_ISO6BTagId tTagId;
}
T_ISO6BRead;

typedef struct tagISO6BWriteControl
{
    unsigned char ucCommandType;
    unsigned char ucRetryTimes;
    unsigned char ucVerifyTimes;
}
T_ISO6BWriteControl;

typedef struct tagT_ISO6BWrite
{
    unsigned char ucBytePtr;
    unsigned char ucByteCount;
    unsigned char aucWriteData[256];  /*要写入的数据*/
    T_ISO6BWriteControl t6BWriteControl;
    T_ISO6BTagId tTagId;
}T_ISO6BWrite;


typedef struct tagT_ISO6BLockControl
{
    unsigned char ucRetryTimes;
    unsigned char ucVerifyTimes;
}T_ISO6BLockControl;

typedef struct tagT_ISO6BLock
{
    unsigned char ucBytePtr;
    unsigned char ucByteCount;
    T_ISO6BLockControl t6BLockControl;
    T_ISO6BTagId tTagId;
}T_ISO6BLock;


typedef struct tagT_ISO6BQueryLockControl
{
    unsigned char ucRetryTimes;
}
T_ISO6BQueryLockControl;

typedef struct tagISO6BQueryLock
{
    unsigned char ucBytePtr;
    unsigned char ucByteCount;
    T_ISO6BQueryLockControl t6BQueryLockControl;
    T_ISO6BTagId tTagId;
}T_ISO6BQueryLock;


typedef struct  tagT_RdpLlrpClientRequestOpSpec
{
    unsigned short int wOpSpecID;
    unsigned short int wPad;
}T_RdpLlrpClientRequestOpSpec;

//国标部分
typedef struct  tagT_RdpLlrpGBRead
{
    unsigned char          ucMB;
    unsigned char           ucPad;
    unsigned short int     wOpSpecID;
    unsigned int     dwReadPassword;
    unsigned short int     wWordPointer;
    unsigned short int     wWordCount;
   
}T_RdpLlrpGBRead;


typedef struct  tagT_RdpLlrpGBWrite
{ 
    unsigned short int    wOpSpecID;
    unsigned char         ucMB;
    unsigned char         aucPad[3];
    unsigned int   dwWritePassword;
    unsigned short int   wWordPointer;
    unsigned short int   wDataLength;
    unsigned char        aucData[0]; /*变长写入数据*/
}T_RdpLlrpGBWrite;

typedef struct  tagT_RdpLlrpGBErase
{ 
    unsigned short int    wOpSpecID;
    unsigned char         ucMB;
    unsigned char         aucPad[3];
    unsigned int   dwWritePassword;
    unsigned short int   wWordPointer;
    unsigned short int   wWordCount;
}T_RdpLlrpGBErase;


typedef union   tagT_RdpLlrpGBLockAction
{
    unsigned char                            ucGBLockMemoryMode;
    unsigned char                            ucGBLockSecureMode;
    unsigned short int                      wPad;
}T_RdpLlrpGBLockAction;


typedef struct   tagT_RdpLlrpGBLock
{
    unsigned short int                                 wOpSpecID;
    unsigned char                                       ucMB;
    unsigned char                                       ucConfig;
    unsigned int                                 dwLockPassword;
    T_RdpLlrpGBLockAction           tRdpLlrpGBLockAction;   /*锁操作的行为*/
}T_RdpLlrpGBLock;

typedef struct   tagT_RdpLlrpGBKill
{
    unsigned short int wOpSpecID;
    unsigned short int wPad;
    unsigned int dwKillPassword;
}T_RdpLlrpGBKill;

/**************************************Ao的匹配参数***************************/
/*
typedef union  tagT_RdpLlrpAirProtocolTag
{
    T_RdpLlrpC1G2TargetTag  tRdpLlrpC1G2TargetTag;
    T_RdpLlrpISO6BTag          tIRdpLlrpISO6BTag;
}T_RdpLlrpAirProtocolTag;
*/
/*
typedef struct  tagT_RdpLlrpC1G2Tag
{
    unsigned int                           dwC1G2TargetTagNum; 
    T_RdpLlrpC1G2TargetTag   tRdpLlrpC1G2TargetTag[MaxTagPatternNUM];
}T_RdpLlrpC1G2Tag;

*/

/*
typedef struct  tagT_RdpLlrpISO6BTag
{
    unsigned int                          dwISO6BTargetTagNum;
    T_RdpLlrpISO6BTargetTag tRdpLlrpISO6BTargetTag[MaxTagPatternNUM];
}T_RdpLlrpISO6BTag;
*/

typedef struct  T_RdpLlrpMatchParam
{
    unsigned short int wMaskBitCount;
    unsigned short int wDataBitCount;
    unsigned char      aucTagData[2];/*字节对齐写成2，原来是1，对代码可能有影响*/
}T_RdpLlrpMatchParam;

typedef struct   tagT_RdpLlrpC1G2TargetTag
{
    unsigned char                           ucMB;
    unsigned char                           ucPad;
    unsigned int                       bMatch;
    unsigned short int                      wPointer; /*开始匹配的指针 bit指针*/
    /*匹配的数据相关*/
    T_RdpLlrpMatchParam   tRdpLlrpMatchParam;
}T_RdpLlrpC1G2TargetTag;

typedef struct   tagT_RdpLlrpISO6BTargetTag
{
    unsigned short int       wBytePtr;
    unsigned short int       wPad;
    unsigned int      bMatch;
    T_RdpLlrpMatchParam  tRdpLlrpMatchParam;
}T_RdpLlrpISO6BTargetTag;

typedef struct   tagT_RdpLlrpGBTargetTag
{
    unsigned char                           ucMB;
    unsigned char                           ucPad;
    unsigned int                       bMatch;
    unsigned short int                      wPointer; /*开始匹配的指针 bit指针*/
    /*匹配的数据相关*/
    T_RdpLlrpMatchParam   tRdpLlrpMatchParam;
}T_RdpLlrpGBTargetTag;

/*typedef struct
{
    unsigned short int antennaId;
    unsigned short int ForDataRate;
    unsigned short int RevDataRate;
    EM_value_Type eM_value;
    EForward_link_Type eForward_link_modulation;
    unsigned short int PIE_Value;
} T_RFModeCfg;*/

/*规则处理消息应答*/
typedef struct tagT_RdpLlrpRuleRsp 
{
    unsigned int   dwRuleID;
    LLRP_tSERROR_MESSAGE *ptRuleRspAddr;
   
}T_RdpLlrpRuleRsp;

/*************************函数接口的声明******************************************************
*                                                                                                                                                                                *
*                                                                                                                                                                                *
*****************************************************************************************************/
 void llrp_addRo(T_Msg *ptMsg);
 void llrp_deleteRo(T_Msg *ptMsg);
 void llrp_enableRo(T_Msg *ptMsg);
 void llrp_disableRo(T_Msg *ptMsg);
 void llrp_startRo(T_Msg *ptMsg);
 void llrp_stopRo(T_Msg *ptMsg);
 void llrp_addAo(T_Msg *ptMsg);
 void llrp_deleteAo(T_Msg *ptMsg);
 void llrp_disableAo(T_Msg *ptMsg);
 void llrp_enableAo(T_Msg *ptMsg);
 void llrp_getRo(T_Msg *ptRcvMsg);
 void llrp_getAo(T_Msg *ptRcvMsg);
 void llrp_getReport(T_Msg *ptRcvMsg);
 void llrp_externPeriodtimerForRoStartTrigger(T_Msg *ptRcvMsg);
void llrp_reportReaderEventNotification(LLRP_tENotificationEventType eEventType,LLRP_tEROSpecEventType eSubEventType);
unsigned int llrp_sendRuleRspMsg(T_Msg *ptRcvMsg, LLRP_tEStatusCode etLLRP_tEStatusCode, unsigned int dwSndMsgID, unsigned int dwMsgSeqID,unsigned int dwRuleID);
void llrp_dealExternGpiForReader(T_Msg *ptRcvMsg);
void llrp_transferAccessEpcOpPara( T_RdpLlrpListOPCtrlSet *ptListOpSet, LLRP_tSParameter *ptTempParameter);
void llrp_transferAccessISO6BOpPara( T_RdpLlrpListOPCtrlSet *ptListOpSet, LLRP_tSParameter *ptTempParameter);
void llrp_transferAccessGBOpPara( T_RdpLlrpListOPCtrlSet *ptListOpSet, LLRP_tSParameter *ptTempParameter);
void llrp_dealBootTimerPollingTimer(T_Msg *ptRcvMsg);
 unsigned long long  llrp_getPPC8313BootCurrMsTime();
 unsigned long long  llrp_getPPC82xxBootCurrMsTime();
 void llrp_clearAccessListforGetAccessRsp(unsigned char ucLinkIndex);

#endif
