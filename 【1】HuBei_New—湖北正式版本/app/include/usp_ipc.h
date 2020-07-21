/************************************************************************
* 版权所有 (C)2009, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_ipc.h
* 文件标识： 
* 内容摘要： 进程间通信对外接口
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.04.07
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_OSS_IPC_H
#define _USP_OSS_IPC_H

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/

/* 不可用的消息队列 */
#define     USP_OSS_IPC_MQ_INVALID          USP_OSS_VOS_MQ_INVALID

/* 不可用的互斥锁 */
#define     USP_OSS_IPC_MUTEX_INVALID       USP_OSS_VOS_MUTEX_INVALID

/* 非法的键值 */
#define     USP_OSS_IPC_KEY_INVALID         (0xFFFF)

/* 定义进程间通信选项 */
#define     USP_OSS_IPC_NOWAIT              (0)            /* 立即返回，不阻塞 */
#define     USP_OSS_IPC_FOREVERWAIT         (0xFFFFFFFF)   /* 阻塞 */

/* 定义互斥锁操作宏 */
#define     USP_OSS_IPC_CREATE_MUTEX(pMutex, key)   usp_oss_vos_createMutex(pMutex, key)
#define     USP_OSS_IPC_TAKE_MUTEX(mutex)           usp_oss_vos_takeMutex(mutex, USP_OSS_VOS_IPC_FOREVERWAIT)
#define     USP_OSS_IPC_GIVE_MUTEX(mutex)           usp_oss_vos_giveMutex(mutex)

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
/* 定义消息队列抽象数据结构 */
typedef     USP_OssVosMsgQueue      USP_OssIpcMsgQueue;

/* 定义互斥锁抽象数据结构 */
typedef     USP_OssVosMutex         USP_OssIpcMutex;

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
/* 创建消息队列 */
extern WORD32 usp_oss_ipc_createMq(USP_OssIpcMsgQueue *pmq, WORD16 wMsgNum, WORD16 wItemSize, WORD16 wMsgQueueKey);

/* 发送消息 */
extern WORD32 usp_oss_ipc_sendMsg(USP_OssIpcMsgQueue mq, VOID *msg, WORD32 dwFlag);

/* 接收消息 */
extern WORD32 usp_oss_ipc_recvMsg(USP_OssIpcMsgQueue mq, VOID *msg, WORD16 wSize, WORD32 dwFlag);


#endif  /* _USP_OSS_IPC_H */

