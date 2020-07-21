/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_scp.h
* 文件标识： 
* 内容摘要： 系统主控对外接口
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.03.13
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_OSS_SCP_H
#define _USP_OSS_SCP_H

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/

/* 定义消息发送/接收宏 */
#if USP_OS_LINUX
#define MsgRcv(dwQueueID,pucDataBuf,wBufLen)  msgrcv((dwQueueID),((void *)pucDataBuf),(wBufLen),0,MSG_NOERROR)
#define MsgSend(dwQueueID,pucDataBuf,wBufLen)  msgsnd(((int)dwQueueID),((const void *)pucDataBuf),((size_t)(wBufLen)),0)
#endif

/* 定义错误处理选项 */
#define     USP_OSS_SCP_ERROR_TYPE_RESET        0   /* 重启 */
#define     USP_OSS_SCP_ERROR_TYPE_ALARM        1   /* 告警 */
#define     USP_OSS_SCP_ERROR_TYPE_IGNORE       2   /* 忽略 */

/* 定义系统启动原因码 */
#define     USP_OSS_SCP_STARTUP_NORMAL          (0) /* 正常启动 */
#define     USP_OSS_SCP_STARTUP_TASK_DEAD       (1) /* 因任务死掉导致重启 */

/* 发送消息到具体的任务 */
#define usp_scp_sendMsgBaseTno(tno, msg)   usp_oss_scp_sendTaskMsg(tno, msg, USP_OSS_IPC_FOREVERWAIT)

/* 信令跟踪宏定义 */
#define USP_OSS_ST_DESC_SIZE                     (24)    /* 信令描述信息的长度 */
#define USP_OSS_ST_SND                           (0)     /* 发送信令 */
#define USP_OSS_ST_RCV                           (1)     /* 接收信令 */

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/
/* 系统模块配置模板 */
#define USP_OSS_SCP_BEGIN_MODULE_CONF_DEFINE \
static T_CliModuleConf s_atCliModuleConfUser[] = {

#define USP_OSS_SCP_MODULE_CONF(ID, NAME, DESC) \
{ID, 0, (BYTE *)NAME, (BYTE *)DESC},

#define USP_OSS_SCP_END_MODULE_CONF_DEFINE \
};

/**************************************************************************
 *                            数据类型                                    *
 **************************************************************************/

/* NTP配置信息 */
typedef struct tagT_USPOssScpNtpCfg
{
    WORD32  adwNtpServerIp[5]; /* 最大为5个,第一个0表示结束,即0以前的是有效的 */
    CHAR    cTimeZoneH;        /* 时区,小时,范围-12--+13 */
    CHAR    cTimeZoneM;        /* 时区,分钟,范围0--+59 */
    WORD16  wPort;             /* 0表示使用缺省端口 */
    WORD32  dwSyncPeriod;      /* 同步周期时间，单位分钟 */
}T_USPOssScpNtpCfg;

/* 上电消息内容 */
typedef struct tagT_USPOssScpPowerOn
{    
    BYTE    ucRound;             /* 表示第几轮上电 */
    BYTE    ucPad;
    WORD16  wPad;
}T_USPOssScpPowerOn;

/* 上电应答消息内容 */
typedef struct tagT_USPOssScpPowerOnAck
{    
    BYTE    ucRound;             /* 表示第几轮上电 */
    BYTE    ucPad;
    WORD16  wPad;
}T_USPOssScpPowerOnAck;

/* 包含系统模块配置信息 */
#define _USP_OSS_SCP_H_INCLUDE
#include "scp.conf"
#undef  _USP_OSS_SCP_H_INCLUDE

/* 定义系统初始化处理函数，返回USP_SUCCESS表示成功，其它为错误码。*/
typedef WORD32 usp_oss_scp_initEntry(VOID);

/* 任务标识数据类型 */
typedef WORD16  USP_OssScpTno;

/* 定义一级任务管理抽象数据类型 */
typedef struct tagT_ScpTaskCtrl    *USP_OssScpTask;

/* 定义任务处理函数 */
typedef WORD32 usp_oss_scp_taskEntry(USP_OssScpTask task);

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/

/* 声明打印函数 */
#if USP_OS_LINUX && USP_OSS_PRINTF_USE

#define usp_oss_printf(ucModule, ucLevel, ...)              usp_cli_printf(ucModule, ucLevel, __VA_ARGS__)
#define usp_oss_isPrintf(ucModule, ucLevel)                 usp_cli_isPrintf(ucModule, ucLevel)

#else

#define usp_oss_printf(ucModule, ucLevel, ...)  
#define usp_oss_isPrintf(ucModule, ucLevel)                 FALSE

#endif  /* USP_OS_LINUX && USP_OSS_PRINTF_USE */

/* 声明信令跟踪函数 */
#if USP_OS_LINUX  && USP_OSS_TRACE_USE && USP_OSS_ST_USE
#define usp_oss_trace(ucType, pucDesc, ptMsg)               usp_cli_trace(ucType, pucDesc, ptMsg)
#define usp_oss_isTraceByTno(wTno)                          usp_cli_isTraceByTno(wTno)
#define usp_oss_isTraceById(wId)                            usp_cli_isTraceById(wId)
#else
#define usp_oss_trace(ucType, pucDesc, ptMsg)  
#define usp_oss_isTraceByTno(wTno)                          FALSE
#define usp_oss_isTraceById(wId)                            FALSE
#endif  /* USP_OS_LINUX && USP_OSS_TRACE_USE */

/* 分布式结构中对任务号的拆分和合并 */
#define usp_oss_scp_getSubDevID(wTno)                       (BYTE)(((WORD16)(wTno) & 0xFFC0) >> 6)
#define usp_oss_scp_getSubTno(wTno)                         (BYTE)((WORD16)(wTno) & 0x003F)
#define usp_oss_scp_getTno(subDevID, subTno)                (WORD16)(((WORD16)(subDevID) << 6) | (WORD16)(subTno))
#define usp_oss_scp_getMinTno(subDevID)                     usp_oss_scp_getTno((subDevID), 0)
#define usp_oss_scp_getMaxTno(subDevID)                     usp_oss_scp_getTno((subDevID), 0x003F)

/* 消息序号自增 */
#define USP_OSS_SCP_MSGSEQ(n)                               (0xFFFF == (++(n)) ? ++(n) : (n))

/* 发送消息给指定的任务 */
extern WORD32 usp_oss_scp_sendTaskMsg(USP_OssScpTno tno, VOID *msg, WORD32 dwFlag);

/* 从指定的任务接收消息 */
extern WORD32 usp_oss_scp_recvTaskMsg(USP_OssScpTno tno, VOID *msg, WORD16 wSize, WORD32 dwFlag);

/* 接收特定类型的消息 */
extern WORD32 usp_oss_scp_recvTaskMsgWithTypes(USP_OssScpTno tno, VOID *msg, WORD16 wSize, WORD32 dwTimeOut, T_Msg *aptExpectMsg[]);

/* 显示消息缓存中的内容 */
extern WORD32 usp_oss_scp_showTaskMsgBuff( USP_OssScpTno tno );

/* 得到缓存中消息的条数 */
extern WORD32 usp_oss_scp_countTaskMsgBuff( USP_OssScpTno tno, WORD32 * pdwMsgCount );

/* 设置应用任务的当前状态 */
extern VOID usp_oss_scp_setTaskStatus(USP_OssScpTask task, WORD16 wStatus);

/* 获取应用任务的当前状态 */
extern WORD16 usp_oss_scp_getTaskStatus(USP_OssScpTask task);

/* 发送握手应答消息 */
extern WORD32 usp_oss_scp_keepAliveAck(USP_OssScpTno tno);

/* 获取与任务相关的消息队列句柄 */
//extern WORD32 usp_oss_scp_getMsgQueueHandle(USP_OssScpTno tno, USP_OssIpcMsgQueue *mq);

/* 停止喂狗接口 */
extern WORD32 usp_scp_stopFeedWatchDog(VOID);

/* 系统控制服务任务入口函数 */
extern WORD32 usp_scp_serviceEntry(USP_OssScpTask task);

/* 设置系统启动原因 */
extern WORD32 usp_oss_scp_setStartupReason(BYTE ucWhy);

/* 获取系统启动原因 */
extern WORD32 usp_oss_scp_getStartupReason(BYTE *pucWhy);

/* 初始化性能统计信息 */
extern WORD32 usp_oss_scp_pspInit(VOID);

#endif  /* _USP_OSS_SCP_H */


