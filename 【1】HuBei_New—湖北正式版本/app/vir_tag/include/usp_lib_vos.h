/************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_lib_vos.h
* 文件标识： 
* 内容摘要： 虚拟操作系统动态库对外接口
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2012.02.06
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_LIB_VOS_H
#define _USP_LIB_VOS_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <termios.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <sys/select.h>
#include <pthread.h>
#include <setjmp.h>
#include <crypt.h>
#include <sys/prctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <linux/rtnetlink.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <sched.h>
#include <linux/ppp_defs.h>
#include <linux/if_ppp.h>   
#include <sys/utsname.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/dir.h>

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
/* 定义进程间通信选项 */
#define     USP_LIB_VOS_IPC_NOWAIT          IPC_NOWAIT   /* 立即返回，不阻塞 */
#define     USP_LIB_VOS_IPC_FOREVERWAIT     (0)          /* 阻塞 */

/* 定义不可用的消息队列 */
#define     USP_LIB_VOS_MQ_INVALID          (0xFFFFFFFF)

/* 定义不可用的互斥锁 */
#define     USP_LIB_VOS_MUTEX_INVALID       (-1)

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                            数据类型                                    *
 **************************************************************************/
/* 操作系统提供的消息队列抽象数据结构 */
typedef WORD32  USPLibVosMsgQueue;

/* 操作系统提供的互斥锁抽象数据结构 */
typedef SWORD32 USPLibVosMutex;

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/

/* 创建共享内存 */
extern VOID *usp_lib_vos_createShm(WORD16 wKey, WORD32 dwSize);

/* 连接到已经存在的共享内存 */
extern VOID *usp_lib_vos_attachShm(WORD16 wKey);

/* 断开到共享内存的连接 */
extern WORD32 usp_lib_vos_dttachShm(VOID *ptr);

/* 创建消息队列 */
extern WORD32 usp_lib_vos_createMq(USPLibVosMsgQueue *pmq, WORD16 wMsgNum, WORD16 wItemSize, WORD16 wMsgQueueKey);

/* 销毁消息队列 */
extern WORD32 usp_lib_vos_destroyMq(USPLibVosMsgQueue mq);

/* 创建互斥锁 */
extern WORD32 usp_lib_vos_createMutex(USPLibVosMutex *pMutex, WORD16 wMutexKey);

/* 获取已有的互斥锁操作句柄 */
extern WORD32 usp_lib_vos_getMutex(USPLibVosMutex *pMutex, WORD16 wMutexKey);

/* 互斥锁P操作 */
extern WORD32 usp_lib_vos_takeMutex(USPLibVosMutex mutex, WORD32 dwFlag);

/* 互斥锁V操作 */
extern WORD32 usp_lib_vos_giveMutex(USPLibVosMutex mutex);

/* 发送消息 */
extern WORD32 usp_lib_vos_sendMsg(USPLibVosMsgQueue mq, VOID *msg, WORD16 wMsgLen, WORD32 dwFlag);

/* 接收消息 */
extern WORD32 usp_lib_vos_recvMsg(USPLibVosMsgQueue mq, VOID *msg, WORD16 wSize, WORD32 dwFlag);

#endif  /* _USP_LIB_VOS_H */

