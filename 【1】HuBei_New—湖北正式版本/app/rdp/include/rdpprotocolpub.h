#ifndef  RDP_PROTOCOLPUB_H
#define RDP_PROTOCOLPUB_H
#include "logm.h"
/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/

#define   MAX_NUM_SELECT_FILTER_PERQUERY  1
#define   MAX_NUM_SORT_FILTER_PERQUERY  1

#define USP_OSS_PRINTF_MODULE_RDP USP_RDP_RULE_TNO

#define RdpDbgPrint    logm_debug
#define RdpWarningPrint  logm_warn
#define RdpErrorPrint     logm_err
#define RdpAlertPrint      logm_alert


#define RdpLlrpDbgPrint    logm_debug
#define RdpLlrpWarningPrint  logm_warn
#define RdpLlrpErrorPrint       logm_err
#define RdpLlrpAlertPrint      logm_alert

#define RdpReportDbgPrint    logm_debug
#define RdpReportWarningPrint  logm_warn
#define RdpReportErrorPrint       logm_err
#define RdpReportAlertPrint      logm_alert

#define RdpRuleDbgPrint    logm_debug
#define RdpRuleWarningPrint  logm_warn
#define RdpRuleErrorPrint     logm_err
#define RdpRuleAlertPrint      logm_alert

#define RdpDbgPrintRaw    logm_debug_raw



#define     RDP_EXCEPT(exceptCode, var1, var2, var3,FileId)   \
            RdpDbgPrint("RDP Exception exceptCode = %u, line = %u, var1 = %u, var2 = %u, var3 = %u fileid = %u\r\n", exceptCode, __LINE__, var1, var2, var3,FileId)

#define struct_fixed_len(structtype,member)  /*lint -save -e413 -e545 */(unsigned short int)((unsigned int)((unsigned char *)&(((structtype *)0)->member)))/*lint -restore */

/*bit转byte*/
#define BIT_CHANGETO_BYTE(bitLengths) (bitLengths/8+(bitLengths%8?1:0))
void GetRDPLLTime(struct timeval *ptCurrentTime);
#define     RDPStartTimer(timer_id,msec)               set_timer(timer_id, (msec/1000), ((msec%1000)*1000),0)
#define     RDPStopTimer(timer_id)                             del_timer(timer_id)


/*消息定义*/
#define EV_USP_RDP_Begin                          ((unsigned short int)(0xC000)) 
#define EV_USP_RDP_SEND_LINK_REPORT    (EV_USP_RDP_Begin+1)
#define EV_USP_RDP_DELETE_FILTER_NODE (EV_USP_RDP_Begin+2)
#define EV_RDP_DELETE_OPERATION_COUNT_ACCESS  (EV_USP_RDP_Begin+3)
/*ROSpec相关的业务命令 */
#define EV_ADD_ROSPEC                                          20 /*增加RoSpec消息*/
#define EV_DELETE_ROSEPC                                     21 /*删除RoSpec消息*/
#define EV_START_ROSPEC                                       22 /*开始RoSpec消息*/
#define EV_STOP_ROSPEC                                         23 /*停止ROSpec*/
#define EV_ENABLE_ROSPEC                                     24 /*使能ROspec*/
#define EV_DISABLE_ROSPEC                                    25 /*禁止ROspec*/
#define EV_GET_ROSPEC                                           26 /*禁止ROspec*/
#define EV_ADD_ROSPEC_RESPONSE                        30
#define EV_DELETE_ROSPEC_RESPONSE                   31
#define EV_START_ROSPEC_RESPONSE                     32
#define EV_STOP_ROSPEC_RESPONSE                       33
#define EV_ENABLE_ROSPEC_RESPONSE                   34
#define EV_DISABLE_ROSPEC_RESPONSE                 35
#define EV_GET_ROSPEC_RESPONSE                        36


/*Access相关的业务命令*/
#define EV_ADD_ACCESSSPEC                                    40
#define EV_DELETE_ACCESSSPEC                               41
#define EV_ENABLE_ACCESSSPEC                               42
#define EV_DISABLE_ACCESSSPEC                             43
#define EV_GET_ACCESSSPECS                                  44
#define EV_CLIENT_REQUEST_OP                              45
#define EV_ADD_ACCESSSPEC_RESPONSE                 50
#define EV_DELETE_ACCESSSPEC_RESPONSE           51
#define EV_ENABLE_ACCESSSPEC_RESPONSE           52
#define EV_DISABLE_ACCESSSPEC_RESPONSE         53
#define EV_GET_ACCESSSPECS_RESPONSE              54
#define EV_CLIENT_REQUEST_OP_RESPONSE          55 
/*Report相关的业务命令*/
#define EV_GET_REPOERT                                         60
#define EV_READER_EVENT_NOTIFICATION                63
#define EV_ENABLE_ENVENTS_AND_REPORTS          64
#define EV_UHF_PRIVATE_CMD                            73
#define EV_UHF_PRIVATE_CMD_ACK                    83
#define EV_UHF_PRIVATE_SETPASSWORD            74
#define EV_UHF_PRIVATE_SETPASSWORD_ACK     84


/*无效报告定义*/
#define INVALID_REPORT                        1 

/*Report的定义*/
#define ROSPEC_REPORT_DATA                     0
#define ACCESSSPEC_REPORT_DATA                  1
#define EVENT_REPORT_DATA                      2

/*RO类型的定义*/
#define RO_START_TRIGGER_SINGLE                    0
#define RO_START_TRIGGER_PERIOD                 1


/*积累最大次数*/
#define MAX_ACCUMULATEDCNT                   5 
/*Access TagPattern最大数*/
#define MaxTagPatternNUM                    2 
/*AISpec的TypeNum号*/
#define AISPEC_PARAMETER_TYPENUM             183

#define RFSURVEY_PARAMETER_TYPENUM           187 

#define LLRP_C1G2InventoryCommand    330
#define LLRP_ISO6BInventoryCommand    632
#define LLRP_GBInventoryCommand    750


/*6C,6BAccess操作 相关*/
#define LLRP_ClientRequestOpSpec             210
#define LLRP_C1GOperationType_Read           341
#define LLRP_C1GOperationType_Write          342
#define LLRP_C1GOperationType_Kill           343
#define LLRP_C1GOperationType_Lock           344
#define LLRP_C1GOperationType_BLOCKWrite     347


#define LLRP_ISO6BOperationType_Read         637
#define LLRP_ISO6BOperationType_Write        639
#define LLRP_ISO6BOperationType_Lock         641
#define LLRP_ISO6BOperationType_QueryLock    643
#define LLRP_ISO6BExOperationType_Read       677
#define LLRP_ISO6BExOperationType_Write      678
#define LLRP_ISO6BExOperationType_Lock       679
#define LLRP_ISO6BExOperationType_QueryLock  680

#define LLRP_GBOperationType_Read           758
#define LLRP_GBOperationType_Write          759
#define LLRP_GBOperationType_Erase         760
#define LLRP_GBOperationType_Lock           761
#define LLRP_GBOperationType_Kill              764


#define LLRP_C1G2ReadCustomUID               703
#define LLRP_ISO6BReadCustomUID              704
#define LLRP_GBReadCustomUID                     770

#define LLRP_ImpinjSetQTConfig                     709
#define LLRP_ImpinjGetQTConfig                     711


/*Psam发卡标识相关操作*/
#define LLRP_C1G2BlockPermalockOpSpecResult             691
#define LLRP_C1G2BlockPermalockQueryOpSpecResult 693

#define LLRP_C1G2_BLOCKLOCK                  690
#define LLRP_C1G2_BLOCKLOCKQUERY             692
#define LLRP_C1G2_ALIENREADLOCK             706
#define LLRP_C1G2WriteVerify               (unsigned short int)(713) 
#define LLRP_C1G2WriteVerifyResult           (unsigned short int)(714)
#define   RDP_SUCCESS                             (unsigned int) 0
#define   RDP_FAILED                                (unsigned int) 1
#define   RDP_NONE                               (unsigned int) 2
#define   RDP_EXCEPTION_FAILED                     (unsigned int)0xff

#define READER_MAX_RCV_MSG_LEN     5120    /*接收的最大消息长度*/
#define READER_MAX_SEND_MSG_LEN    5120    /*最大发送消息长度*/
/*实测数据已经超过50%的占用率*/
#define RDP_LLRP_MAX_ACCULATE_SIZE    10000000

#define  APP_ERR_RDP_BASE	            0x00020000
/**************************************************************************
 *                RDP 错误码定义                     *
 **************************************************************************/

#define  RDP_OPEN_HOLDROCFGFILE_FAILED          (APP_ERR_RDP_BASE + 1)
#define  RDP_WRITE_HOLDROCFGFILE_FAILED         (APP_ERR_RDP_BASE + 2)
#define  RDP_READ_HOLDROCFGFILE_FAILED          (APP_ERR_RDP_BASE + 3)
#define  RDP_OPEN_HOLDAOCFGFILE_FAILED          (APP_ERR_RDP_BASE + 4)
#define  RDP_WRITE_HOLDAOCFGFILE_FAILED         (APP_ERR_RDP_BASE + 5)
#define  RDP_READ_HOLDAOCFGFILE_FAILED          (APP_ERR_RDP_BASE + 6)

#define  RDP_NULLPOINTER_EXCEPTION              (APP_ERR_RDP_BASE + 7)
#define  RDP_DECODE_MESSAGE_ERROR               (APP_ERR_RDP_BASE + 8)

#define  RDP_INVALID_STATE                      (APP_ERR_RDP_BASE + 9)
#define  RDP_SEND_MESSGAE_ERROR                 (APP_ERR_RDP_BASE + 10)

#define  RDP_INVALID_MESSAGE_TYPE               (APP_ERR_RDP_BASE + 11)
#define  RDP_BUF_NO_SPARE_MEM                   (APP_ERR_RDP_BASE + 12)  /*没有空闲内存*/
#define  RDP_RSSI_NODE_NUM_ERROR                   (APP_ERR_RDP_BASE + 13)  /*RSSI节点数错误*/
#define  RDP_RSSI_REPORT_SIZE_TOO_BIGGER_ERROR                   (APP_ERR_RDP_BASE + 14)  /*RSSI上报的包数过大错误*/
#define  RDP_RECV_MESSGAE_ERROR                      (APP_ERR_RDP_BASE + 15)
#define  RDP_MSG_PROC_ERROR                      (APP_ERR_RDP_BASE + 16)
#define  RDP_ENCODE_MESSAGE_ERROR                      (APP_ERR_RDP_BASE + 17)

#define  RDP_RO_STATE_ERROR                                         (APP_ERR_RDP_BASE + 18)  /*Ro状态异常*/
#define  RDP_AO_MATCH_ERROR                                        (APP_ERR_RDP_BASE + 19) /*AO匹配时 状态异常*/
#define  RDP_AO_DOOP_STATE_ERROR                              (APP_ERR_RDP_BASE + 20) /*AO做OP操作时状态异常*/
#define  RDP_LLRP_PROTO_ERROR                                     (APP_ERR_RDP_BASE + 21) /*Rdp中协议异常*/
#define  RDP_LLRP_LEN_ERROR                                        (APP_ERR_RDP_BASE + 22) /*Rdp长度参数长度异常*/
#define  RDP_LLRP_VERIYREAD_ERROR                                        (APP_ERR_RDP_BASE + 23) /*AO做OP操作时状态异常*/
#define  RDP_LLRP_GETTIME_ERROR                                        (APP_ERR_RDP_BASE + 24) /*Rdp获取时间时异常*/
#define  RDP_LLRP_UNSUPPORTEVENT_ERROR                                        (APP_ERR_RDP_BASE + 25) /*Rdp获取时间时异常*/
                       
#define  RDP_LLRP_UNSUPORT_OPTYPE                                (APP_ERR_RDP_BASE + 26) /*Rdp发现Optyepe不支持*/
#define HASHTABLE_LENGTH                      (unsigned short int)509 

/*文件ID*/
#define     EV_APP_RDP_FNO_BASE	                   0x0200
#define     RDP_SEND_ID    EV_APP_RDP_FNO_BASE
#define     RDP_CHECK_ID    EV_APP_RDP_FNO_BASE+1
#define     RDP_FILTER_ID    EV_APP_RDP_FNO_BASE+2
#define     RDP_REPORT_ID    EV_APP_RDP_FNO_BASE+3
#define     RDP_RULE_ID    EV_APP_RDP_FNO_BASE+4
#define     RDP_LLRP_RULE_ID    EV_APP_RDP_FNO_BASE+5
#define     RDP_LLRP_EPC_ID    EV_APP_RDP_FNO_BASE+6
#define     RDP_LLRP_ISO6B_ID    EV_APP_RDP_FNO_BASE+7
#define     RDP_LLRP_DISPATCH_ID    EV_APP_RDP_FNO_BASE+8
#define     RDP_LLRP_REPORT_ID    EV_APP_RDP_FNO_BASE+9
#define     RDP_LLRP_GB_ID    EV_APP_RDP_FNO_BASE+10

/*收发消息定义*/
#define     RDP_SEND_MSG(socket, msg)     zmq_send(socket, msg,(T_Msg *)msg->wMsgLen+sizeof(T_Msg),0)
#define     RDP_RECV_MSG(socket,buf, len)     zmq_recv(socket, buf, len,0)
#define     RDP_RECV_SYNC_MSG(socket,buf, len)   zmq_recv(socket, buf, len,0) 

//#define     RDP_SEND_MSG(socket, msg)     1
/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
 

/**************************************************************************
 *                             类声明                                      *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
#define LLRP_FINDANDFREENODE_FAIL           0
#define LLRP_FINDANDFREENODE_SUCCESS     1
#define LLRP_CFG_CHANGE  1
#define LLRP_CFG_NOTCHANGE  2
#define  LLRP_ASYN_MSG      2
#define  LLRP_SYN_MSG        1
#define    LLRP_RODISPATCH_STATE_DELETE     0
#define    LLRP_RODISPATCH_STATE_DISABLE   1
#define    LLRP_RODISPATCH_STATE_INACTIVE  2
#define    LLRP_RODISPATCH_STATE_READY      3
#define    LLRP_RODISPATCH_STATE_ACTIVE     4

#define  LLRP_MAX_ACCESS_ERROR_TIMES   3
#define  LLRP_INIT_ACCESS_ERROR_TIMES  0 

#define EV_RDP_TIMER_BEGIN	              (unsigned short int)0x0
#define EV_RDP_TIMER_END                  (unsigned short int)0x3f

#define EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN	              (unsigned short int)0x0
#define EV_RDP_LLRP_PROTIMEOUT_TIMER_END                     (unsigned short int)(EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN+0x0010) 

#define EV_RDP_LLRP_RULETIMER_BEGIN	              (unsigned short int)(0x0011)
#define EV_RDP_LLRP_RULETIMER_END	                    (unsigned short int)(EV_RDP_LLRP_RULETIMER_BEGIN+0x0010)




#define TFpgaResp                                      (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 1)     /*fpga inventory resp max_time*/
#define TFpgaReadResp                               (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 2)     /*fpga read resp max_time*/
#define TFpgaWriteResp                              (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 3)    /*fpga Write resp max_time*/
#define TClientRequestOpSpecTimeout         (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 4)   /*ClientRequest的timeout事件*/ 
#define TFpgaLockResp                               (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 5)    /*fpga Lock tag resp max_time*/ 
#define TFpgaKillResp                                  (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 6)    /*fpga kill tag resp max_time*/
#define TFpgaBlockLockResp                        (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 7)  /*fpga */
/* Added by gaoyu for  6BLock */
#define TFpgaLockQueryResp                       (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 8)    /*fpga Lock query tag resp max_time*/ 
#define TFpgaIPJQTResp                              (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 9)
#define TFpgaAlienReadLockResp                 (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 10)
#define TFpgaEraseResp                 (EV_RDP_LLRP_PROTIMEOUT_TIMER_BEGIN + 11)

#define TBootTimerPollingIntervalTimer                     (EV_RDP_LLRP_RULETIMER_END+ 1)     /*Rdp的时间基准的轮询定时器*/
#define EV_RDP_REPORT_TAGTRPORT_FILTER_TIMER  (EV_RDP_LLRP_PROTIMEOUT_TIMER_END+2)


#define TFpgaRespCount                (9000)                   /*9s*/ 
#define INIT_BOOT_TIME   do{\
if (0 != usp_drv_timer_init())\
{\
    RDP_EXCEPT(RDP_INVALID_STATE, 0, 0, 0, RDP_LLRP_DISPATCH_ID);\
    printf("usp_drv_timer_init init failure in rdp!\r\n");\
}\
else\
{\
    usp_drv_timer_control(USP_DRV_TIMER_CLEAR);\
    usp_drv_timer_control(USP_DRV_TIMER_START);\
    printf("usp_drv_timer_init init success!\r\n");\
}\
}while(0)
/*RUP 和小改版bt版本*/
#if USP_CPU_TYPE_ppc_8313 
#define   INIT_READER_BOOT_TIME_MS()     //INIT_BOOT_TIME 

#define   GET_READER_BOOT_TIME_MS()         llrp_getPPC8313BootCurrMsTime()        
#define LLRP_PollingInterval                        (100000)   
/*老版和小改版*/
#elif USP_CPU_TYPE_ppc_82xx
#define   INIT_READER_BOOT_TIME_MS()        //INIT_BOOT_TIME
#define   GET_READER_BOOT_TIME_MS()         llrp_getPPC82xxBootCurrMsTime()
#define LLRP_PollingInterval                        (100000)     
#else
#define   INIT_READER_BOOT_TIME_MS()          
#define   GET_READER_BOOT_TIME_MS()         (llrp_getReaderuSec()/1000)
#define LLRP_PollingInterval                        (0)    
#endif

#define  EV_RDP_GPIO_BASE                           (unsigned short int)(0x0B00)
#define  EV_RDP_GPIO_InputEventReport         (unsigned short int)(EV_RDP_GPIO_BASE+0x0001)

#define     LLRP_START_TIMER(timer_id,msec)               set_timer(timer_id, (msec/1000), ((msec%1000)*1000),0)
#define     LLRP_STOP_TIMER(timer_id)                           del_timer(timer_id)
#define     RDP_MAX_LEN_MSG                  (unsigned int)(16 * 1024)
#define     RDP_LLRP_INIT_STATUS          (unsigned int)0
#define     RDP_LLRP_WORK_STATUS        (unsigned int)1

typedef struct tagT_USPRdpLlrpGPIOEventReport
{
    unsigned short int wLogicPortIndex;               /* 逻辑 IO 端口编号 */
    unsigned short int wEventID;                      /* 事件的ID */
}T_USPRdpLlrpGPIOEventReport;


#define  MAX_ACCESS_NUM_ERROR       1
#define LLRP_ACCESS_DELETE   1
#define LLRP_ACCESS_CONTINUE_DO 2
#define LLRP_ACCESS_DELETE   1
#define LLRP_ACCESS_CONTINUE_DO 2




 #define    LLRP_ACCESSDISPATCH_STATE_DELETE     0
 #define    LLRP_ACCESSDISPATCH_STATE_DISABLE   1
  #define    LLRP_ACCESSDISPATCH_STATE_ENABLE   2
 #define    LLRP_ACCESSDISPATCH_STATE_ACTIVE     3


#define LLRP_MAX_REPORT_BUFFER          2048

#define LLRP_ISO6BMATCHTAG_SUCCESS     0
#define LLRP_ISO6BMATCHTAG_FAIL            1 

#define  LLRP_MAX_ACCESS_ERROR_TIMES   3
#define  LLRP_INIT_ACCESS_ERROR_TIMES  0 
#define  LLRP_ACCESS_MATCH_SUCCESS    0
#define  LLRP_ACCESS_MATCH_FAIL           1
#define LLRP_ACCESSPATTERN_MATCH_SUCCESS    0
#define LLRP_EPCMATCHTAG_SUCCESS     0
#define LLRP_EPCMATCHTAG_FAIL            1 
#define LLRP_ACCESSPATTERN_MATCH_FAIL           1 
#define LLRP_ACCESSPATTERN_MATCHREAD_SUCCESS    0
#define LLRP_ACCESSPATTERN_MATCHREAD_FAIL           1 
#define LLRP_EPC_READ_PWDINDEX_SUCCESS                0
#define LLRP_EPC_READ_PWDINDEX_FAIL                       1 

#define LLRP_GB_READ_PWDINDEX_FAIL                       1 
#define LLRP_GB_READ_PWDINDEX_SUCCESS                  0 
#define LLRP_GBMATCHTAG_SUCCESS     0
#define LLRP_GBMATCHTAG_FAIL            1 

#define BIT_CHANGETO_WORD16(bitLengths) ((bitLengths)/16+((bitLengths)%16?1:0))
#define MAX_LINK_NUM  2
#define ERR_FPGA_TIMEOUT                             (2)  /* FPGA不正常, 超时，不能返回操作结果   */
#define LLRP_ROSPEC_REPORT_DATA                         0
#define LLRP_ACCESSSPEC_REPORT_DATA                  1
#define EVENT_REPORT_DATA                      2
#define LLRP_SET_DATA_REPORT(iscfg,data, defaultdata)    (iscfg == TRUE? data:defaultdata) 
#define LLRP_DEFAULT_REPORT_WORD64   0xffffffff
#define LLRP_DEFAULT_REPORT_WORD32   0xffffffff
#define LLRP_DEFAULT_REPORT_WORD16   0xffff
#define  LLRP_CLIENTREQUEST_TIMEOUT    10000
#define LLRP_MAX_PWDINDEX_NUM      4

#define LLRP_MB_TID 0x00
#define LLRP_MB_EPC 0x10
#define LLRP_MB_SEC 0x20

typedef enum tagT_USPOssModuleID
{
    
        
    USP_COMM_TNO,                                       /* 通信任务 */
    USP_FPGA_TNO,                                       /* FPGA处理 */
    USP_UHF_TNO,                                        /* UHF协议处理 */ 
    USP_RDP_RULE_TNO,                                   /* UHF规则下发 */
    USP_RDP_REPORT_TNO,                                 /* UHF报告处理 */
    USP_RDP_LLRP_TNO,                                   /* UHF规则处理 */     
    USP_OSS_GPIO_TNO,                                   /* GPIO管理 */ 
    USP_VIR_TAG_TNO,                                    /*  */
}T_USPOssModuleID;


#define EV_USP_COMM_SendData                (0xFD07)  /* 通过通信链路发送数据 */
#define EV_USP_COMM_RecvData                (0xFD08)  /* 转发数据给应用模块 */
#define EV_USP_COMM_SendReportData          (0xFD0F)


#endif
