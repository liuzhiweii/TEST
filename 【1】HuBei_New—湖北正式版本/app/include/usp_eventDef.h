/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_eventDef.h
* 文件标识： 
* 内容摘要： 消息定义
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2008.10.14
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_EVENT_DEF_H
#define _USP_EVENT_DEF_H


/*  16bit消息编码定义:                                             
  
------------+----------------------
消息前缀    |  消息应用范围
------------+---------------------
EV_           表示是消息定义
EV_           系统全局消息
EV_USP_       USP系统消息
EV_USP_CLI_   与命令行(CLI)有关的消息
EV_RM_        RSP 与车道计算机的消息
EV_RO_        OAM与网管中心
EV_S_R_       SCP到RSP的消息
EV_S_O_       SCP到OAM的消息
EV_S_C_       SCP到COMM的消息
EV_R_S_       RSP到SCP的消息
EV_R_O_       RSP到OAM的消息
EV_O_R_       OAM到RSP的消息
EV_O_S_       OAM到SCP的消息
EV_O_C_       OAM到COMM的消息
EV_C_S_       COMM到SCP的消息
EV_C_O_       COMM到OAM的消息
EV_S_         SCP模块内部的消息
EV_C_         COMM模块内部的消息
EV_O_         OAM模块内部的消息
EV_R_         RSP模块内部的消息
EV_D_         DSRC模块内部的消息
*/

/**********************************************************************
*                             消息基值                                *
**********************************************************************/

/* 系统主控(SCP)消息基值定义 */
#define EV_USP_SCP_Begin                               ((WORD16)(0xFC00)) 

/* 命令行界面(CLI)消息基值定义 */
#define EV_USP_CLI_Begin                               ((WORD16)(0xFE00)) 

/* 日志与异常探针(LAP)消息基值定义 */
#define EV_USP_LAP_Begin                               ((WORD16)(0xFF00)) 

/* 通信模块(COMM)消息基值定义 */
#define EV_USP_COMM_Begin                              ((WORD16)(0xFD00)) 

/* IP发现模块(IPD)消息基值定义 */
#define EV_USP_COMM_IPD_Begin                          ((WORD16)(0xFB00)) 

/* 配置模块(CMP)消息基值定义 */
#define EV_USP_OAM_CMP_Begin                           ((WORD16)(0xFA00))

/* 版本管理模块(VMP)消息基值定义 */
#define EV_USP_OAM_VMP_Begin                           ((WORD16)(0xA800))

/* 诊断测试(DMP)消息基值定义*/
#define EV_USP_OAM_DMP_Begin                          ((WORD16)(0xAC00))

/* 状态监控(AMP)消息基值定义*/
#define EV_USP_OSS_SMP_Begin                          ((WORD16)(0xAE00))

/* 告警管理模块(AMP)消息基值定义 */
#define EV_USP_OAM_AMP_Begin                          ((WORD16)(0xF100)) 

/* MPI 模块消息基值定义 */
#define EV_USP_MPI_Begin                              ((WORD16)(0xF200))

/* 扩展PSAM管理任务消息基值定义 */
#define EV_USP_PSAM_EXT_Begin                           ((WORD16)(0xF300)) 

/* GPIO和RELAY控制模块消息基值定义 */
#define EV_USP_GPIO_RELAY_Begin                           ((WORD16)(0xF400))

/* 杂项任务(MISC)消息基值定义*/
#define EV_USP_OSS_MISC_Begin                          ((WORD16)(0xF500))

/* 虚拟标签模块消息基值定义 */
#define EV_USP_VIR_TAG_Begin                           ((WORD16)(0xF600)) 

/**********************************************************************
*                             消息定义                                *
**********************************************************************/

/**********************************************************************
*                             系统主控(SCP)消息定义                   *
**********************************************************************/
#define EV_USP_SCP_PowerOn                  (EV_USP_SCP_Begin + 1)  /* 进程上电消息 */
#define EV_USP_SCP_PowerOnSuccess           (EV_USP_SCP_Begin + 2)  /* 进程上电成功消息 */
#define EV_USP_SCP_PowerOnFailure           (EV_USP_SCP_Begin + 3)  /* 进程上电失败消息 */ 
#define EV_USP_SCP_StopProcess              (EV_USP_SCP_Begin + 4)  /* 停止进程，进程应该结束运行(exit)，主要用于通知VMP，CMP不要再进行任何FLASH操作 */
#define EV_USP_SCP_TimerWaitPowerOn         (EV_USP_SCP_Begin + 5)  /* 等待应用任务的上电应答定时器 */
#define EV_USP_SCP_KeepAlive                (EV_USP_SCP_Begin + 6)  /* SCP与各应用任务的握手消息，用于检测任务是否正常运行 */
#define EV_USP_SCP_KeepAliveAck             (EV_USP_SCP_Begin + 7)  /* 应用任务向SCP返回的握手应答消息 */
#define EV_USP_SCP_TimerKeepAlive           (EV_USP_SCP_Begin + 8)  /* 与应用任务握手的定时器消息 */
#define EV_USP_SCP_TimerNtpUpdate           (EV_USP_SCP_Begin + 9)  /* NTP时间同步的定时器消息 */
#define EV_USP_SCP_Reset                    (EV_USP_SCP_Begin + 10) /* 系统重启消息 */
#define EV_USP_SCP_ResetAck                 (EV_USP_SCP_Begin + 11) /* 系统重启应答消息 */
#define EV_USP_SCP_SetTime                  (EV_USP_SCP_Begin + 12) /* 设置时间消息 */
#define EV_USP_SCP_SetTimeAck               (EV_USP_SCP_Begin + 13) /* 设置时间应答消息 */
#define EV_USP_SCP_TimerIbKeepAlive         (EV_USP_SCP_Begin + 14) /* 板间SCP握手定时器消息 */
#define EV_USP_SCP_IbKeepAlive              (EV_USP_SCP_Begin + 15) /* 板间SCP握手消息 */
#define EV_USP_SCP_IbKeepAliveAck           (EV_USP_SCP_Begin + 16) /* 板间SCP握手应答消息 */
#define EV_USP_SCP_PspSave                  (EV_USP_SCP_Begin + 17) /* 定时保存性能统计信息 */
#define EV_USP_SCP_TimerBeginRecvMsg        (EV_USP_SCP_Begin + 18) /* 接收消息超时定时器起始消息 */

/**********************************************************************
*                             命令行界面(CLI)消息定义                 *
**********************************************************************/
#define EV_USP_CLI_Cmd_Request                         (EV_USP_CLI_Begin + 1)
#define EV_USP_CLI_Cmd_Response                        (EV_USP_CLI_Begin + 2)
#define EV_USP_CLI_Alarm_Inter                         (EV_USP_CLI_Begin + 3)
#define EV_USP_CLI_Close_Shell                         (EV_USP_CLI_Begin + 4)
#define EV_USP_CLI_Monitor_Ctrl                        (EV_USP_CLI_Begin + 5) 
#define EV_USP_CLI_Monitor_Ctrl_Ack                    (EV_USP_CLI_Begin + 6) 
#define EV_USP_CLI_Trace_Ctrl                          (EV_USP_CLI_Begin + 7) 
#define EV_USP_CLI_Trace_Ctrl_Ack                      (EV_USP_CLI_Begin + 8) 
 
/**********************************************************************
*                             日志与异常探针(LAP)消息定义             *
**********************************************************************/
#define EV_USP_LAP_LogReport                                        (EV_USP_LAP_Begin + 0x01) /* 日志上报消息 */
#define EV_USP_LAP_AbnReport                                        (EV_USP_LAP_Begin + 0x02) /* 异常上报消息 */
#define EV_USP_OAM_LAP_GetReaderLog                                 (EV_USP_LAP_Begin + 0x03) /* 后台请求上传日志消息 */
#define EV_USP_OAM_LAP_GetReaderLogResponse                         (EV_USP_LAP_Begin + 0x04) /* 前台返回日志消息 */
#define EV_USP_OAM_LAP_GetReaderLogResponseAck                      (EV_USP_LAP_Begin + 0x05) /* 后台收到日志上传应答消息 */
#define EV_USP_OAM_LAP_GetReaderException                           (EV_USP_LAP_Begin + 0x06) /* 后台请求上传异常消息 */
#define EV_USP_OAM_LAP_GetReaderExceptionResponse                   (EV_USP_LAP_Begin + 0x07) /* 前台返回异常消息*/
#define EV_USP_OAM_LAP_GetReaderExceptionResponseAck                (EV_USP_LAP_Begin + 0x08) /* 后台收到异常上传应答消息 */
#define EV_USP_OAM_LAP_WaitGetReaderLogResponseAckOverTime          (EV_USP_LAP_Begin + 0x09) /* 等待后台收到日志信息应答ACK消息的定时器 */
#define EV_USP_OAM_LAP_WaitGetReaderExceptionResponseAckOverTime    (EV_USP_LAP_Begin + 0x0A) /* 等待后台收到异常信息应答ACK消息的定时器 */
#define EV_USP_OAM_LAP_LogClear                                     (EV_USP_LAP_Begin + 0x0B) /* 清空日志 */
#define EV_USP_OAM_LAP_LogClear_ACK                                 (EV_USP_LAP_Begin + 0x0C) /* 清空日志 */
#define EV_USP_OAM_LAP_AbnClear                                     (EV_USP_LAP_Begin + 0x0D) /* 清空异常探针 */
#define EV_USP_OAM_LAP_AbnClear_ACK                                 (EV_USP_LAP_Begin + 0x0E) /* 清空异常探针 */
/**********************************************************************
*                             通信模块(COMM)消息定义                  *
**********************************************************************/
#define EV_USP_COMM_CreateSocketListen      (EV_USP_COMM_Begin + 1)  /* 创建Socket服务监听端口 */
#define EV_USP_COMM_CreateSocketConnect     (EV_USP_COMM_Begin + 2)  /* 创建Socket连接 */
#define EV_USP_COMM_CreateLinkFd            (EV_USP_COMM_Begin + 3)  /* 添加通信链路数据到达监听 */
#define EV_USP_COMM_DeleteSocketConnect     (EV_USP_COMM_Begin + 4)  /* 删除Socket连接 */
#define EV_USP_COMM_LinkCloseNotice         (EV_USP_COMM_Begin + 5)  /* 链路关闭通知 */
#define EV_USP_COMM_NewLinkNotice           (EV_USP_COMM_Begin + 6)  /* 新的链路建立的通知消息  */
#define EV_USP_COMM_SendData                (EV_USP_COMM_Begin + 7)  /* 通过通信链路发送数据 */
#define EV_USP_COMM_RecvData                (EV_USP_COMM_Begin + 8)  /* 转发数据给应用模块 */
#define EV_USP_COMM_CloseLink               (EV_USP_COMM_Begin + 9)  /* 关闭链路 */
#define EV_USP_COMM_LinkOpened              (EV_USP_COMM_Begin + 10) /* 建链成功后的通知消息 (发送给应用模块) */
#define EV_USP_COMM_LinkClosed              (EV_USP_COMM_Begin + 11) /* 连接断开的通知消息 (发送给应用模块) */ 
#define EV_USP_COMM_CfgRequest              (EV_USP_COMM_Begin + 12) /* 查询配置消息 */ 
#define EV_USP_COMM_CfgRequestAck           (EV_USP_COMM_Begin + 13) /* 配置应答消息 */ 
#define EV_USP_COMM_LinkCompleteOpened      (EV_USP_COMM_Begin + 14) /* 链路完全打开 */ 
#define EV_USP_COMM_SendReportData          (EV_USP_COMM_Begin + 15)            /* 通过通信链路发送报告型数据 */
#define EV_USP_COMM_DumpCongestionData      (EV_USP_COMM_Begin + 16)            /* 保存拥塞缓存数据 */
#define EV_USP_COMM_WriteHoldData           (EV_USP_COMM_Begin + 18)            /* 保存断链缓存数据 */
#define EV_USP_COMM_InterBoardKeepAlive     (EV_USP_COMM_Begin + 19)            /* 板间通信握手消息 */
#define EV_USP_COMM_SetLinkForward          (EV_USP_COMM_Begin + 20)            /* 设置链路转发 */
#define EV_USP_COMM_CancelLinkForward       (EV_USP_COMM_Begin + 21)            /* 取消链路转发 */
#define EV_USP_COMM_SendSm                  (EV_USP_COMM_Begin + 22)            /* 发送短信 */
#define EV_USP_COMM_RecvSm                  (EV_USP_COMM_Begin + 23)            /* 接收短信 */
#define EV_USP_COMM_SmsSignalQualityReq     (EV_USP_COMM_Begin + 24)            /* GSM信号查询请求 */
#define EV_USP_COMM_SmsSignalQualityAck     (EV_USP_COMM_Begin + 25)            /* GSM信号查询应答 */
#define EV_USP_COMM_TimerBegin              (EV_USP_COMM_Begin + 30)            /* 起始定时器消息 */
#define EV_USP_COMM_KeepALive               (EV_USP_COMM_TimerBegin + 32 * 0)   /* KEEPALIVE定时器消息 */
#define EV_USP_COMM_SendCongestionData      (EV_USP_COMM_TimerBegin + 32 * 1)   /* 发送拥塞数据消息 */
#define EV_USP_COMM_SendHoldData            (EV_USP_COMM_TimerBegin + 32 * 2)   /* 发送缓存数据消息 */


/**********************************************************************
*                             IP发现模块(IPD)消息定义                  *
**********************************************************************/
#define  EV_USP_IPD_CloseLink                       (EV_USP_COMM_IPD_Begin + 1) /* 关闭建立的临时TCP链路 */
#define  EV_USP_IPD_KeepAliveTimer                  (EV_USP_COMM_IPD_Begin + 2) /* 定时器到时消息 */
#define  EV_USP_IPD_ReaderEventNotification         (EV_USP_COMM_IPD_Begin + 3) /* 发送ReaderEventNotification给发送线程消息id */
#define  EV_USP_IPD_GetReaderCfgReq				    (EV_USP_COMM_IPD_Begin + 4) /* 向配置模块发送获取配置请求消息 */
#define  EV_USP_IPD_GetReaderCfgAck				    (EV_USP_COMM_IPD_Begin + 5) /* 收到配置模块发来的获取配置应答消息 */
#define  EV_USP_IPDUDP_GetReaderCfgReq				(EV_USP_COMM_IPD_Begin + 6) /* 向CMP模块发送获取配置请求消息，UDP方式使用 */
#define  EV_USP_IPDUDP_GetReaderCfgAck				(EV_USP_COMM_IPD_Begin + 7) /* 收到CMP模块发来的获取配置应答消息，UDP方式使用 */
#define  EV_USP_IPDUDP_SetReaderCfgReq              (EV_USP_COMM_IPD_Begin + 8) /* 向CMP模块发送设置配置请求消息，UDP方式使用 */
#define  EV_USP_IPDUDP_SetReaderCfgAck              (EV_USP_COMM_IPD_Begin + 9) /* 收到CMP模块发来的设置配置应答消息，UDP方式使用 */
#define  EV_USP_IPDUDP_WaitGetReaderCfgAckOverTime  (EV_USP_COMM_IPD_Begin + 10) /* 等待CMP模块发来的获取配置应答消息超时消息，UDP方式使用 */
#define  EV_USP_IPDUDP_WaitSetReaderCfgAckOverTime  (EV_USP_COMM_IPD_Begin + 11) /* 等待CMP模块发来的设置配置应答消息超时消息，UDP方式使用 */
#define  EV_USP_IPDUDP_WaitClearMsqOverTime         (EV_USP_COMM_IPD_Begin + 12) /* 等待清空消息队列缓冲区超时 */
#define  EV_USP_OAM_IPD_IPDiscoveryReq              (EV_USP_COMM_IPD_Begin + 13) /* IP发现请求消息 */
#define  EV_USP_OAM_IPD_IPDiscoveryAck              (EV_USP_COMM_IPD_Begin + 14) /* IP发现应答消息 */
#define  EV_USP_OAM_IPD_SetReaderCfgReq             (EV_USP_COMM_IPD_Begin + 15) /* 设置设备请求消息 */
#define  EV_USP_OAM_IPD_SetReaderCfgAck             (EV_USP_COMM_IPD_Begin + 16) /* 设置设备应答消息 */
#define  EV_USP_OAM_IPD_ResetReq                    (EV_USP_COMM_IPD_Begin + 17) /* 复位设备请求消息 */
#define  EV_USP_OAM_IPD_ResetAck                    (EV_USP_COMM_IPD_Begin + 18) /* 复位设备应答消息 */
#define  EV_USP_OAM_IPD_WaitClearMsqOverTime        (EV_USP_COMM_IPD_Begin + 19) /* 等待清空消息队列缓冲区超时 */
#define  EV_USP_OAM_IPD_WaitIPDiscoveryAckOverTime  (EV_USP_COMM_IPD_Begin + 20) /* 等待CMP模块发来的获取配置应答消息超时消息 */
#define  EV_USP_OAM_IPD_WaitSetReaderCfgAckOverTime (EV_USP_COMM_IPD_Begin + 21) /* 等待CMP模块发来的设置配置应答消息超时消息 */

/**********************************************************************
*                             配置模块(CMP)消息定义                  *
**********************************************************************/
#define EV_USP_OAM_CMP_CfgParaChg               (EV_USP_OAM_CMP_Begin + 1)  /* 配置变更通知消息 */
#define EV_USP_OAM_CMP_SetCfgPara               (EV_USP_OAM_CMP_Begin + 2)  /* 设置配置数据消息 */
#define EV_USP_OAM_CMP_GetCfgPara               (EV_USP_OAM_CMP_Begin + 3)  /* 查询配置数据消息 */
#define EV_USP_OAM_CMP_GetCfgParaByTno          (EV_USP_OAM_CMP_Begin + 4)  /* 根据任务号查询与之相关的配置数据消息 */
#define EV_USP_OAM_CMP_SetCfgParaAck            (EV_USP_OAM_CMP_Begin + 5)  /* 设置配置数据消息响应 */
#define EV_USP_OAM_CMP_GetCfgParaAck            (EV_USP_OAM_CMP_Begin + 6)  /* 查询配置数据消息响应 */
#define EV_USP_OAM_CMP_GetCfgParaByTnoAck       (EV_USP_OAM_CMP_Begin + 7)  /* 根据任务号查询与之相关的配置数据消息响应 */
#define EV_USP_OAM_CMP_Reset                    (EV_USP_OAM_CMP_Begin + 8)  /* 重启设备消息 */
#define EV_USP_OAM_CMP_SetFactoryDefault        (EV_USP_OAM_CMP_Begin + 9)  /* 恢复出厂设置 */
#define EV_USP_OAM_CMP_AMPConfigRequest         (EV_USP_OAM_CMP_Begin + 10) /* 请求AMP配置 */
#define EV_USP_OAM_CMP_AMPConfigRequestAck      (EV_USP_OAM_CMP_Begin + 11) /* 请求AMP配置应答 */
#define EV_USP_OAM_CMP_SMPConfigRequest         (EV_USP_OAM_CMP_Begin + 12) /* 请求SMP配置 */
#define EV_USP_OAM_CMP_SMPConfigRequestAck      (EV_USP_OAM_CMP_Begin + 13) /* 请求SMP配置应答 */
#define EV_USP_OAM_CMP_SaveCfgPara              (EV_USP_OAM_CMP_Begin + 14) /* 保存配置消息 */
#define EV_USP_OAM_CMP_SaveCfgParaAck           (EV_USP_OAM_CMP_Begin + 15) /* 保存配置应答消息 */
#define EV_USP_OAM_CMP_NTPConfigRequest         (EV_USP_OAM_CMP_Begin + 16) /* 请求NTP配置 */
#define EV_USP_OAM_CMP_NTPConfigRequestAck      (EV_USP_OAM_CMP_Begin + 17) /* 请求NTP配置应答 */
#define EV_USP_OAM_CMP_RDPConfigRequest         (EV_USP_OAM_CMP_Begin + 18) /* 请求RDP配置 */
#define EV_USP_OAM_CMP_RDPConfigRequestAck      (EV_USP_OAM_CMP_Begin + 19) /* 请求RDP配置应答 */
#define EV_USP_OAM_CMP_RCPConfigRequest         (EV_USP_OAM_CMP_Begin + 20) /* 请求RCP配置 */
#define EV_USP_OAM_CMP_RCPConfigRequestAck      (EV_USP_OAM_CMP_Begin + 21) /* 请求RCP配置应答 */
#define EV_USP_OAM_CMP_MPIConfigRequest         (EV_USP_OAM_CMP_Begin + 22) /* 请求MPI配置 */
#define EV_USP_OAM_CMP_MPIConfigRequestAck      (EV_USP_OAM_CMP_Begin + 23) /* 请求MPI配置应答 */
#define EV_USP_OAM_CMP_ETCConfigRequest         (EV_USP_OAM_CMP_Begin + 24) /* 请求ETC配置 */
#define EV_USP_OAM_CMP_ETCConfigRequestAck      (EV_USP_OAM_CMP_Begin + 25) /* 请求ETC配置应答 */
#define EV_USP_OAM_CMP_SetCfgIntegrated         (EV_USP_OAM_CMP_Begin + 26) /* 设置全部配置数据消息 */
#define EV_USP_OAM_CMP_SetCfgIntegratedAck      (EV_USP_OAM_CMP_Begin + 27) /* 设置全部配置数据消息响应 */
#define EV_USP_OAM_CMP_GetCfgIntegrated         (EV_USP_OAM_CMP_Begin + 28) /* 查询全部配置数据消息 */
#define EV_USP_OAM_CMP_GetCfgIntegratedAck      (EV_USP_OAM_CMP_Begin + 29) /* 查询全部配置数据消息响应 */
#define EV_USP_OAM_CMP_SetFactoryDefaultAck     (EV_USP_OAM_CMP_Begin + 30) /* 恢复出厂设置应答 */
#define EV_USP_OAM_CMP_GPIOConfigRequest        (EV_USP_OAM_CMP_Begin + 31) /* 请求GPIO配置 */
#define EV_USP_OAM_CMP_GPIOConfigRequestAck     (EV_USP_OAM_CMP_Begin + 32) /* 请求GPIO配置应答*/

/**********************************************************************
*                             版本管理模块(VMP)消息定义               *
**********************************************************************/
#define EV_USP_OAM_VMP_VerDownload                      (EV_USP_OAM_VMP_Begin + 1)  /* 版本下载 */
#define EV_USP_OAM_VMP_VerDownloadAck                   (EV_USP_OAM_VMP_Begin + 2)  /* 版本下载应答 */
#define EV_USP_OAM_VMP_VerDownloadQuery                 (EV_USP_OAM_VMP_Begin + 3)  /* 请求下载版本信息 */
#define EV_USP_OAM_VMP_VerDownloadQueryAck              (EV_USP_OAM_VMP_Begin + 4)  /* 请求下载版本信息应答 */
#define EV_USP_OAM_VMP_VerActive                        (EV_USP_OAM_VMP_Begin + 5)  /* 版本激活 */
#define EV_USP_OAM_VMP_VerActiveAck                     (EV_USP_OAM_VMP_Begin + 6)  /* 版本激活应答 */
#define EV_USP_OAM_VMP_VerUnActive                      (EV_USP_OAM_VMP_Begin + 7)  /* 版本反激活 */
#define EV_USP_OAM_VMP_VerUnActiveAck                   (EV_USP_OAM_VMP_Begin + 8)  /* 版本反激活应答 */
#define EV_USP_OAM_VMP_VerDelete                        (EV_USP_OAM_VMP_Begin + 9)  /* 版本删除 */
#define EV_USP_OAM_VMP_VerDeleteAck                     (EV_USP_OAM_VMP_Begin + 10) /* 版本删除应答 */
#define EV_USP_OAM_VMP_VerQuery                         (EV_USP_OAM_VMP_Begin + 11)  /* 版本查询 */
#define EV_USP_OAM_VMP_VerQueryAck                      (EV_USP_OAM_VMP_Begin + 12) /* 版本查询应答 */
#define EV_USP_OAM_VMP_BootDownload                     (EV_USP_OAM_VMP_Begin + 13) /* boot升级 */
#define EV_USP_OAM_VMP_BootDownloadAck                  (EV_USP_OAM_VMP_Begin + 14) /* boot升级应答 */
#define EV_USP_OAM_VMP_BootQuery                        (EV_USP_OAM_VMP_Begin + 15) /* boot查询 */
#define EV_USP_OAM_VMP_BootQueryAck                     (EV_USP_OAM_VMP_Begin + 16) /* boot查询应答 */
#define EV_USP_OAM_VMP_SubDevBootDownload               (EV_USP_OAM_VMP_Begin + 17) /* 子设备boot升级 */
#define EV_USP_OAM_VMP_SubDevBootDownloadAck            (EV_USP_OAM_VMP_Begin + 18) /* 子设备boot升级应答 */
#define EV_USP_OAM_VMP_SubDevBootQuery                  (EV_USP_OAM_VMP_Begin + 19) /* 子设备boot查询 */
#define EV_USP_OAM_VMP_SubDevBootQueryAck               (EV_USP_OAM_VMP_Begin + 20) /* 子设备boot查询应答 */
#define EV_USP_OAM_VMP_VerUpdateStart                   (EV_USP_OAM_VMP_Begin + 21) /* 版本更新开始 */
#define EV_USP_OAM_VMP_VerUpdateStartAck                (EV_USP_OAM_VMP_Begin + 22) /* 版本更新开始应答 */
#define EV_USP_OAM_VMP_VerUpdateData                    (EV_USP_OAM_VMP_Begin + 23) /* 版本更新数据 */
#define EV_USP_OAM_VMP_VerUpdateDataAck                 (EV_USP_OAM_VMP_Begin + 24) /* 版本更新数据应答 */
#define EV_USP_OAM_VMP_VerUpdateEnd                     (EV_USP_OAM_VMP_Begin + 25) /* 版本更新结束 */
#define EV_USP_OAM_VMP_VerUpdateEndAck                  (EV_USP_OAM_VMP_Begin + 26) /* 版本更新结束应答 */
#define EV_USP_OAM_VMP_SubDevBootQueryTimeout           (EV_USP_OAM_VMP_Begin + 27) /* 子设备boot查询超时 */
#define EV_USP_OAM_VMP_SubDevBootDownloadTimeout        (EV_USP_OAM_VMP_Begin + 28) /* 子设备boot升级超时 */
#define EV_USP_OAM_VMP_LMT_Begin                        (EV_USP_OAM_VMP_Begin + 50)     /* LMT相关的起始消息号 */
#define EV_USP_OAM_VMP_LMT_VerDownload                  (EV_USP_OAM_VMP_LMT_Begin + 1)  /* 版本下载 */ 
#define EV_USP_OAM_VMP_LMT_VerDownloadAck               (EV_USP_OAM_VMP_LMT_Begin + 2)  /* 版本下载响应 */
#define EV_USP_OAM_VMP_LMT_VersionDownloadRequest       (EV_USP_OAM_VMP_LMT_Begin + 3)  /* 请求版本下载信息 */
#define EV_USP_OAM_VMP_LMT_VersionDownloadRequestAck    (EV_USP_OAM_VMP_LMT_Begin + 4)  /* 请求版本下载信息响应 */
#define EV_USP_OAM_VMP_LMT_VerActivate                  (EV_USP_OAM_VMP_LMT_Begin + 5)  /* 版本激活 */ 
#define EV_USP_OAM_VMP_LMT_VerActivateAck               (EV_USP_OAM_VMP_LMT_Begin + 6)  /* 版本激活响应 */ 
#define EV_USP_OAM_VMP_LMT_VerUnActivate                (EV_USP_OAM_VMP_LMT_Begin + 7)  /* 版本去激活 */ 
#define EV_USP_OAM_VMP_LMT_VerUnActivateAck             (EV_USP_OAM_VMP_LMT_Begin + 8)  /* 版本去激活响应 */
#define EV_USP_OAM_VMP_LMT_VersionQuery                 (EV_USP_OAM_VMP_LMT_Begin + 9)  /* 版本查询 */ 
#define EV_USP_OAM_VMP_LMT_VersionQueryAck              (EV_USP_OAM_VMP_LMT_Begin + 10) /* 版本查询响应 */
#define EV_USP_OAM_VMP_LMT_UbootVersionQueryRequest     (EV_USP_OAM_VMP_LMT_Begin + 11) /* uboot版本查询 */
#define EV_USP_OAM_VMP_LMT_UbootVersionQueryRequestAck  (EV_USP_OAM_VMP_LMT_Begin + 12) /* uboot版本查询响应 */
#define EV_USP_OAM_VMP_LMT_UBootUpdateRequest           (EV_USP_OAM_VMP_LMT_Begin + 13) /* uboot版本下载 */
#define EV_USP_OAM_VMP_LMT_UBootUpdateRequestAck        (EV_USP_OAM_VMP_LMT_Begin + 14) /* uboot版本下载响应 */

/**********************************************************************
*                            诊断测试模块(DMP)消息定义        *
**********************************************************************/
#define EV_USP_OAM_DMP_HostRequest            (EV_USP_OAM_DMP_Begin + 1) /* 外部模块发送诊断测试请求消息*/
#define EV_USP_OAM_DMP_HostResponse           (EV_USP_OAM_DMP_Begin + 2) /* 外部模块发送诊断测试应答消息 */
#define EV_USP_OAM_DMP_Request                (EV_USP_OAM_DMP_Begin + 3) /* 其他内部模块发送诊断测试请求消息 */
#define EV_USP_OAM_DMP_Response               (EV_USP_OAM_DMP_Begin + 4) /* 其他内部模块发送诊断测试应答消息 */
#define EV_USP_OAM_DMP_AppRequest             (EV_USP_OAM_DMP_Begin + 5) /* 诊断测试模块发送具体业务应用模块诊断测试请求消息 */
#define EV_USP_OAM_DMP_AppResponse            (EV_USP_OAM_DMP_Begin + 6) /* 诊断测试模块发送具体业务应用模块诊断测试应答消息*/
#define EV_USP_OAM_DMP_WaitAppResponse        (EV_USP_OAM_DMP_Begin + 7) /* 增加诊断测试模块等待业务应用模块应答时间的消息 */
#define EV_USP_OAM_DMP_CLOSEREQUEST           (EV_USP_OAM_DMP_Begin + 8) /* DMP关任务请求消息 */
#define EV_USP_OAM_DMP_CLOSERESPONSE          (EV_USP_OAM_DMP_Begin + 9) /* DMP关任务应答消息 */
#define EV_USP_OAM_DMP_OPENREQUEST            (EV_USP_OAM_DMP_Begin +10) /* DMP开任务请求消息 */
#define EV_USP_OAM_DMP_OPENRESPONSE           (EV_USP_OAM_DMP_Begin +11) /* DMP开任务应答消息 */

/**********************************************************************
*                            状态监控(SMP)消息定义                   *
**********************************************************************/
#define EV_USP_SMP_MonitorTimerId            (EV_USP_OSS_SMP_Begin + 1) /* 监控周期定时器消息 */
#define EV_USP_SMP_ConfigAckTimeId           (EV_USP_OSS_SMP_Begin + 2) /* 等待配置超时消息*/

/**********************************************************************
*                            告警源发给前台AMP告警消息定义                   *
**********************************************************************/
#define EV_USP_OAM_AMP_AlarmReport              (EV_USP_OAM_AMP_Begin + 1)//前台告警模块发送给后台的告警消息
#define EV_USP_OAM_AMP_AlarmRestoreReport       (EV_USP_OAM_AMP_Begin + 2)//前台告警模块发送给后台的告警恢复消息
#define EV_USP_OAM_AMP_InformReport             (EV_USP_OAM_AMP_Begin + 3)//前台告警模块发送给后台的告警通知消息
#define EV_USP_OAM_AMP_REPORT_ALL_ALARM         (EV_USP_OAM_AMP_Begin + 4)//将告警池中的所有告警发送给后台
#define EV_B_O_ALARM                            EV_USP_OAM_AMP_AlarmReport         /* 告警源上报告警 */
#define EV_B_O_ALARMRESTORE                     EV_USP_OAM_AMP_AlarmRestoreReport  /* 告警源上报告警恢复 */
#define EV_B_O_INFORM                           EV_USP_OAM_AMP_InformReport        /* 告警源上报告警通知 */

/**********************************************************************
*                            MPI 模块消息定义                    *
**********************************************************************/
#define EV_USP_MPI_OPENRF                       (EV_USP_MPI_Begin + 1)/* 动态库向协议模块打开射频*/
#define EV_USP_MPI_OPENRFAck                    (EV_USP_MPI_Begin + 2)/* 协议模块向动态库打开射频应答*/
#define EV_USP_MPI_CLOSERF                      (EV_USP_MPI_Begin + 3)/* 动态库向协议模块关闭射频*/
#define EV_USP_MPI_CLOSERFAck                   (EV_USP_MPI_Begin + 4)/* 协议模块向动态库关闭射频应答*/
#define EV_USP_MPI_RB_OpenRf                    (EV_USP_MPI_Begin + 7)/* MPI 协议内部打开射频*/
#define EV_USP_MPI_RB_OpenRfAck	                (EV_USP_MPI_Begin + 8)/* MPI 协议内部打开射频应答*/
#define EV_USP_MPI_RB_CloseRf                   (EV_USP_MPI_Begin + 9)/* MPI 协议内部关闭射频*/
#define EV_USP_MPI_RB_CloseRfAck                (EV_USP_MPI_Begin +10)/* MPI 协议内部关闭射频应答*/
#define EV_USP_MPI_RF_CmpAckOverTime            (EV_USP_MPI_Begin +11)/* MPI 射频板请求配置应答超时*/
#define EV_USP_MPI_RF_ResetCC1101Time           (EV_USP_MPI_Begin +12)/* MPI 射频板复位CC1101 定时*/
#define EV_USP_MPI_RB_NoticeShellTno            (EV_USP_MPI_Begin +13)/* 告知射频板脚本任务号*/
#define EV_USP_MPI_RF_ReportObuInfo             (EV_USP_MPI_Begin +14)/* 射频板上报OBU信息*/

/**********************************************************************
*                             扩展PSAM管理任务消息定义                *
**********************************************************************/
#define EV_USP_PSAM_EXT_Detect                  (EV_USP_PSAM_EXT_Begin + 1)  /* PSAM探测请求消息 */
#define EV_USP_PSAM_EXT_DetectAck               (EV_USP_PSAM_EXT_Begin + 2)  /* PSAM探测应答消息 */
#define EV_USP_PSAM_EXT_Cmd                     (EV_USP_PSAM_EXT_Begin + 3)  /* PSAM命令处理请求消息 */
#define EV_USP_PSAM_EXT_CmdAck                  (EV_USP_PSAM_EXT_Begin + 4)  /* PSAM命令处理应答消息 */
#define EV_USP_PSAM_EXT_Ec02Check               (EV_USP_PSAM_EXT_Begin + 5)  /* EC02在位检测定时器消息 */
#define EV_USP_PSAM_EXT_Active                  (EV_USP_PSAM_EXT_Begin + 7)  /* PSAM激活命令处理请求消息 */
#define EV_USP_PSAM_EXT_ActiveAck               (EV_USP_PSAM_EXT_Begin + 8)  /* PSAM激活命令处理应答消息 */

/**********************************************************************
*                            GPIO和RELAY控制模块消息基值定义          *
**********************************************************************/
#define EV_USP_GPIO_Config                     (EV_USP_GPIO_RELAY_Begin + 0)  /* GPIO模块配置*/
#define EV_USP_GPIO_ConfigAck                  (EV_USP_GPIO_RELAY_Begin + 1)  /* GPIO模块配置应答*/
#define EV_USP_GPIO_InterruptReport            (EV_USP_GPIO_RELAY_Begin + 2)  /* GPIO模块中断上报*/
#define EV_USP_GPIO_IOStatusReq                (EV_USP_GPIO_RELAY_Begin + 3)  /* GPIO模块中断上报*/
#define EV_USP_GPIO_IOStatusReport             (EV_USP_GPIO_RELAY_Begin + 4)  /* GPIO模块状态上报 */
#define EV_USP_GPIO_SetOut                     (EV_USP_GPIO_RELAY_Begin + 5)  /* GPIO模块状态输出 */
#define EV_USP_GPIO_SetOutAck                  (EV_USP_GPIO_RELAY_Begin + 6)  /* GPIO模块状态输出应答 */
#define EV_USP_RELAY_SetOut                    (EV_USP_GPIO_RELAY_Begin + 7)  /* GPIO模块继电器输出 */
#define EV_USP_RELAY_SetOutAck                 (EV_USP_GPIO_RELAY_Begin + 8)  /* GPIO模块继电器输出应答 */
#define EV_USP_GPIO_ConfigReq                  (EV_USP_GPIO_RELAY_Begin + 9)  /* GPIO模块配置请求消息*/
#define EV_USP_GPIO_SetGpiReport               (EV_USP_GPIO_RELAY_Begin + 10) /* GPIO模块GPI状态报告设置 */
#define EV_USP_GPIO_SetGpiReportAck            (EV_USP_GPIO_RELAY_Begin + 11) /* GPIO模块GPI状态报告设置应答 */
#define EV_USP_GPIO_TimerInitiative            (EV_USP_GPIO_RELAY_Begin + 12) /* 主动上报定时器消息 */


/**********************************************************************
*                             杂项(MISC)消息定义                      *
**********************************************************************/
#define EV_USP_OSS_MISC_BuzzerOn                (EV_USP_OSS_MISC_Begin + 1)  /* 打开蜂鸣器 */
#define EV_USP_OSS_MISC_BuzzerOff               (EV_USP_OSS_MISC_Begin + 2)  /* 关闭蜂鸣器 */
#define EV_USP_OSS_MISC_BuzzerInterval          (EV_USP_OSS_MISC_Begin + 3)  /* 间隔蜂鸣 */
#define EV_USP_OSS_MISC_SetWiegand              (EV_USP_OSS_MISC_Begin + 4)  /* 设置韦根参数 */
#define EV_USP_OSS_MISC_GetWiegand              (EV_USP_OSS_MISC_Begin + 5)  /* 获取韦根参数 */
#define EV_USP_OSS_MISC_SendWiegandReport       (EV_USP_OSS_MISC_Begin + 6)  /* 通过韦根发送报告 */
#define EV_USP_OSS_MISC_SwitchGpioAndWiegand    (EV_USP_OSS_MISC_Begin + 7)  /* 韦根与GPIO的切换 */

/***********************************************************************
*                虚拟标签模块消息定义
************************************************************************/
#define EV_USP_VIR_TAG_Config6cTag              (EV_USP_VIR_TAG_Begin + 1)  /*配置6c标签*/
#define EV_USP_VIR_TAG_Config6cTagResponse      (EV_USP_VIR_TAG_Begin + 2)  /* 配置6c标签结果返回 */
#define EV_USP_VIR_TAG_Query6cTag               (EV_USP_VIR_TAG_Begin + 3)
#define EV_USP_VIR_TAG_Query6cTagResponse       (EV_USP_VIR_TAG_Begin + 4)
#define EV_USP_VIR_TAG_Config6bTag              (EV_USP_VIR_TAG_Begin + 5) 
#define EV_USP_VIR_TAG_Config6bTagResponse      (EV_USP_VIR_TAG_Begin + 6)
#define EV_USP_VIR_TAG_Query6bTag               (EV_USP_VIR_TAG_Begin + 7)
#define EV_USP_VIR_TAG_Query6bTagResponse       (EV_USP_VIR_TAG_Begin + 8)
#define EV_USP_VIR_TAG_OperateTag               (EV_USP_VIR_TAG_Begin + 9)
#define EV_USP_VIR_TAG_StartCmd                 (EV_USP_VIR_TAG_Begin + 10)
#define EV_USP_VIR_TAG_StartLlrpCmd             (EV_USP_VIR_TAG_Begin + 11)
#define EV_USP_VIR_TAG_StopCmd                  (EV_USP_VIR_TAG_Begin + 12)
#define EV_USP_VIR_TAG_Remove6cTagAll           (EV_USP_VIR_TAG_Begin + 13)
#define EV_USP_VIR_TAG_Remove6bTagAll           (EV_USP_VIR_TAG_Begin + 14)
#define EV_USP_VIR_TAG_StartWork                (EV_USP_VIR_TAG_Begin + 15)
#define EV_USP_VIR_TAG_Delete6cTag              (EV_USP_VIR_TAG_Begin + 16)
#define EV_USP_VIR_TAG_Delete6cTagResponse      (EV_USP_VIR_TAG_Begin + 17)
#define EV_USP_VIR_TAG_Delete6bTag              (EV_USP_VIR_TAG_Begin + 18)
#define EV_USP_VIR_TAG_Delete6bTagResponse      (EV_USP_VIR_TAG_Begin + 19)

#endif  /* _USP_EVENT_DEF_H */

