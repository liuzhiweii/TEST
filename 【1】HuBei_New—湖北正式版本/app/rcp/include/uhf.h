/************************************************************************
* 版权所有 (C)2011, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： uhf.h
* 文件标识： 
* 内容摘要：超高频协议所用到的宏定义
* 其它说明： 
* 当前版本： 
* 作    者： zdx
* 完成日期： 2011.12.1
* 
* 修改记录1： 
*    修改日期：
*    版 本 号：   
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/

#ifndef _UHF_H
#define _UHF_H


/************************************************/

#define UHF_CFG_TIMEOUT_TIME     (1000)               /*平台定时器采用10ms精度*/
#define UHF_AUTO_RF_CLOSE_TIME   (3000)
#define UHF_CFG_RF_CFG_WAIT_TIME (3000)
/* RFID协议类型 */
#define UHF_PROTO_TYPE_EPC      (0x0)   /* GEN2 */
#define UHF_PROTO_TYPE_ISO6B    (0x1)   /* 18000-6 Type B */
#define UHF_PROTO_TYPE_GB        (0x2)


#define INVENTORY_NOT_FINISH      (0)   /* 标签清点还未结束 */
#define INVENTORY_HAS_FINISH      (1)   /* 标签清点已经结束 */

/* 清点时工作状态定义 */
#define MAC_INVENTORY_PROCESS_FINISH                 (0)
#define MAC_INVENTORY_PROCESS_SUCCESS              (1)


/* QUERY命令M参数定义 */
#define EPC_QUERY_M_1   (0)
#define EPC_QUERY_M_2   (1)
#define EPC_QUERY_M_4   (2)
#define EPC_QUERY_M_8   (3)
// For GB
#define GB_QUERY_M_1   (0)
#define GB_QUERY_M_2   (1)
#define GB_QUERY_M_4   (2)
#define GB_QUERY_M_8   (3)


/* QUERY命令TRext参数定义 */
#define EPC_QUERY_TREXT_NO_PILOT_TONE    (0)
#define EPC_QUERY_TREXT_USE_PILOT_TONE   (1)
// For GB --------FIX ME !!
#define GB_QUERY_TREXT_NO_PILOT_TONE    (0)
#define GB_QUERY_TREXT_USE_PILOT_TONE   (1)


/* QUERY命令DR参数定义 */
#define EPC_QUERY_DR_8          (0)
#define EPC_QUERY_DR_64_DIV_3   (1)
#define EPC_QUERY_DR_GB         (3)
//for GB  -------FIX ME !!
#define GB_QUERY_DR_8          (0)
#define GB_QUERY_DR_64_DIV_3   (1)
#define GB_QUERY_DR_GB         (3)

/* Rcp进程状态 */
#define UHF_STATE_INIT                  (0)   /* 进程初始状态     */
#define UHF_STATE_WORK                  (1)   /* 工作状态         */
#define UHF_STATE_WAITE_CONFIG          (2)   /* 在工作状态下进行RF的配置 */
#define UHF_STATE_RF_CONFIG             (3)

/* RCP消息缓存最大容量bytes */
#define UHF_MAX_MSG_SIZE  (2048)
#define TRACEBUFFERLEN  1024

#if (UHF_BOARD_TYPE == BOARD_TYPE_RBCB1)
#define FPGA_FREQUENCE         (30720000)
#define WRITE_RCV_DELAY_H      (0x0009)  
#define WRITE_RCV_DELAY_L      (0x6000)
#define EPC_BLOCK_START_DELAY  (0X8BD51)
#define UHF_BEFORE_SIG_SND_TIME (460)
#elif (UHF_BOARD_TYPE == BOARD_TYPE_RFCB)
#define FPGA_FREQUENCE          (26000000)
#define WRITE_RCV_DELAY_H       (0x0007)  
#define WRITE_RCV_DELAY_L       (0x6590)
#define EPC_BLOCK_START_DELAY  (0x76590)
#define UHF_BEFORE_SIG_SND_TIME (460)
#elif (UHF_BOARD_TYPE == BOARD_TYPE_PURM)
#define FPGA_FREQUENCE         (26000000)
#define WRITE_RCV_DELAY_H      (0x0007)  
#define WRITE_RCV_DELAY_L      (0x6590)
#define EPC_BLOCK_START_DELAY  (0x76590)
#define UHF_BEFORE_SIG_SND_TIME (460)
#else
#define FPGA_FREQUENCE         (26000000)
#define WRITE_RCV_DELAY_H      (0x0007)  
#define WRITE_RCV_DELAY_L      (0x6590)
#define EPC_BLOCK_START_DELAY  (0x76590)
#define UHF_BEFORE_SIG_SND_TIME (460)
#endif


#define GetUhfMsgIndex(wMsgId)    ((wMsgId)-EV_USP_UHF_WORDK_MSG_START -1)

#define ReadLowLevelFrame(pwReadLen) uhf_readFpgaFrame(pwReadLen)

#define TraceToMacMsg(EV_Command)  if (usp_cli_isTraceByTno(USP_FPGA_TNO))\
{\
 uhf_SendTraceMsg(EV_RCP_TO_FPGA, EV_Command, 0, NULL);\
}


typedef WORD32 usp_uhf_Protocol_fun(T_Msg *,T_Msg *);

typedef struct tagTMsgFunDef
{
  WORD32 dwRcvMsgId;
  WORD32 dwSndMsgId;
  usp_uhf_Protocol_fun *ptProcFun;
  WORD16 wReceiverTno;
  WORD16 wPad;
}T_MsgFunDef;

typedef struct
{
    BYTE ucTurnOnFilter;
    BYTE ucPad;
    WORD16 wRSSIThreshHold;
} T_RssiCfg;

typedef struct
{
    BYTE   ucModeIndex;         /*阅读器默认协议优化配置表，每个天线一个值*/
    BYTE   ucAntStause;         /*天线是否在位*/
    WORD16 wPad;
    T_USPUHFEpcUserDefPara   tEpcUserDefPara;  
    T_USPUHFGBUserDefPara   tGBUserDefPara;    
    T_USPUHFRFModeCfg         tRfModeCfg;
    T_RssiCfg                tEPCReadRssiCfg;
    T_RssiCfg                tEPCWriteRssiCfg;
    T_RssiCfg                tISO6BReadRssiCfg;
    T_RssiCfg                tISO6BWriteRssiCfg;
    T_RssiCfg                tGBReadRssiCfg;
    T_RssiCfg                tGBWriteRssiCfg;
} T_AntCfgs;

typedef struct
{
   WORD16 wAntIndex;   /* 当前工作天线 从射频板获得*/
   WORD16 wWorkChannel;
   /* 当前工作频率, 单位：kHz,  */
   WORD32 dwWorkFreq;         
   T_AntCfgs atRfAntCfg[READER_ANTENNA_COUNT + 1];
} T_UhfCtrl;



WORD32 uhf_SendTraceMsg(WORD16 wSendOrRecv, WORD16 wMsgID, WORD16 ParaLen, WORD16 *pwPara);
WORD16 uhf_getInventQ(WORD16 wTagPopulation);


#endif

