/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_vos.h
* 文件标识： 
* 内容摘要： 与操作系统有关的通用头文件
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
#ifndef _USP_OSS_VOS_H
#define _USP_OSS_VOS_H

#define USP_OS_LINUX 1

#if USP_OS_LINUX

/**************************************************************************
 *                包含与具体操作系统有关的头文件                          *
 **************************************************************************/
#ifdef _UBOOT_
#include <common.h>
#else
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
#include <float.h>
#include <math.h>
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
#include <dlfcn.h>
#include <linux/ppp_defs.h>
#include <linux/if_ppp.h>   
#include <sys/utsname.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/dir.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <pthread.h>
#endif

/**************************************************************************
 *                      宏定义                                            *
 **************************************************************************/
/* 秒级别的睡眠 */
#define USP_OSS_VOS_SLEEP_SEC(sec)      sleep((sec))

/* 毫秒级别的睡眠 */
#define USP_OSS_VOS_SLEEP_MSEC(msec)    usleep((msec) * 1000)

/* 微秒级别的睡眠 */
//#define USP_OSS_VOS_SLEEP_USEC(usec)    usp_oss_vos_usleep(usec)    
#define USP_OSS_VOS_SLEEP_USEC(usec)    usleep(usec)   


/* 定义进程间通信选项 */
#define     USP_OSS_VOS_IPC_NOWAIT          IPC_NOWAIT   /* 立即返回，不阻塞 */
#define     USP_OSS_VOS_IPC_FOREVERWAIT     (0)          /* 阻塞 */

/* 定义不可用的消息队列 */
#define     USP_OSS_VOS_MQ_INVALID      (0xFFFFFFFF)

/* 定义不可用的互斥锁 */
#define     USP_OSS_VOS_MUTEX_INVALID   (-1)

/* 定义文件类型 */
#define     USP_OSS_VOS_FILE_TYPE_DIR   0
#define     USP_OSS_VOS_FILE_TYPE_FILE  1

/* 定义WIFI加密方式 */
#define     USP_OSS_VOS_WIFI_MODE_WEP   0
#define     USP_OSS_VOS_WIFI_MODE_WPA   1

/**************************************************************************
 *                      数据类型                                          *
 **************************************************************************/
/* 操作系统提供的消息队列抽象数据结构 */
typedef WORD32  USP_OssVosMsgQueue;

/* 操作系统提供的互斥锁抽象数据结构 */
typedef SWORD32 USP_OssVosMutex;

/* 文件夹包含的文件信息 */
typedef struct tagT_USPOssVosDirInFo
{ 
    BYTE            aucFileName[64];       /* 文件名 */
    BYTE            ucType;                /* 文件类型 */
    BYTE            ucPad;
    WORD16          wPad;
}T_USPOssVosDirInFo;

#endif  /* USP_OS_LINUX */

#if USP_OS_FREERTOS

/**************************************************************************
 *                包含与具体操作系统有关的头文件                          *
 **************************************************************************/
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "rspdebugproxy.h"

/**************************************************************************
 *                      宏定义                                            *
 **************************************************************************/
/* 秒级别的睡眠 */
#define USP_OSS_VOS_SLEEP_SEC(sec)      vTaskDelay((sec) * 1000 / portTICK_RATE_MS)

/* 毫秒级别的睡眠 */
#define USP_OSS_VOS_SLEEP_MSEC(msec)    vTaskDelay((msec) / portTICK_RATE_MS)

/* 微秒级别的睡眠 */
//#define USP_OSS_VOS_SLEEP_USEC(usec)    usp_oss_vos_usleep(usec)
#define USP_OSS_VOS_SLEEP_USEC(usec)    usleep(usec)

/* 定义进程间通信选项 */
#define     USP_OSS_VOS_IPC_NOWAIT          portNO_DELAY   /* 立即返回，不阻塞 */
#define     USP_OSS_VOS_IPC_FOREVERWAIT     portMAX_DELAY  /* 阻塞 */

/* 定义不可用的消息队列 */
#define     USP_OSS_VOS_MQ_INVALID      NULL

/* 定义不可用的互斥锁 */
#define     USP_OSS_VOS_MUTEX_INVALID   NULL

/**************************************************************************
 *                      数据类型                                          *
 **************************************************************************/
/* 操作系统提供的消息队列抽象数据结构 */
typedef xQueueHandle  USP_OssVosMsgQueue;

/* 操作系统提供的互斥锁抽象数据结构 */
typedef xQueueHandle  USP_OssVosMutex;

#endif  /* USP_OS_FREERTOS */

/**************************************************************************
 *                      数据类型                                          *
 **************************************************************************/
/* 进程在系统中的标识符定义 */
typedef WORD32  USP_OssVosPid;

/* 线程在系统中的标识符定义 */
typedef WORD32  USP_OssVosTid;

/* 定义工作入口函数 */
typedef VOID USP_OssVosWorkEntry(VOID *arg);

/**************************************************************************
 *                      封装的全局函数原型                                *
 **************************************************************************/

/* 创建消息队列 */
extern WORD32 usp_oss_vos_createMq(USP_OssVosMsgQueue *pmq, WORD16 wMsgNum, WORD16 wItemSize, WORD16 wMsgQueueKey);

/* 发送消息 */
extern WORD32 usp_oss_vos_sendMsg(USP_OssVosMsgQueue mq, VOID *msg, WORD16 wMsgLen, WORD32 dwFlag);

/* 接收消息 */
extern WORD32 usp_oss_vos_recvMsg(USP_OssVosMsgQueue mq, VOID *msg, WORD16 wSize, WORD32 dwFlag);

/* 创建进程 */
extern WORD32 usp_oss_vos_createProcess(USP_OssVosWorkEntry *entry, VOID *arg, BYTE *pucName, SWORD16 swPriority, USP_OssVosPid *pid);

/* 创建线程 */
extern WORD32 usp_oss_vos_createThread(USP_OssVosWorkEntry *entry, VOID *arg, BYTE *pucName, WORD16 wStackDepth, SWORD16 swPriority, USP_OssVosTid *tid);

/* 销毁线程 */
extern WORD32 usp_oss_vos_destroyThread(USP_OssVosTid tid);

/* 设置进程名称 */
extern VOID usp_oss_vos_setProcessName(BYTE *pucName);

/* 重新启动系统 */
extern VOID usp_oss_vos_reset(VOID);

/* 配置Coredump */
extern WORD32 usp_oss_vos_configCoredump(VOID);

/* 申请共享内存 */
extern VOID *usp_oss_vos_malloc(WORD16 wKey, WORD32 dwSize);

/* 设置操作系统时区 */
extern WORD32 usp_oss_vos_setTimezone(CHAR cTimeZoneH, CHAR cTimeZoneM);

/* NTP时间同步 */
extern WORD32 usp_oss_vos_updateNtp(WORD32 dwNtpServerIp);

/* 初始化设备的通信设施 */
extern WORD32 usp_oss_vos_initComm(VOID);

/* 微秒级别的延迟函数 */
extern VOID usp_oss_vos_usleep(WORD32 dwUsec);

/* 创建互斥锁 */
extern WORD32 usp_oss_vos_createMutex(USP_OssVosMutex *pMutex, WORD16 wMutexKey);

/* 互斥锁P操作 */
extern WORD32 usp_oss_vos_takeMutex(USP_OssVosMutex mutex, WORD32 dwFlag);

/* 互斥锁V操作 */
extern WORD32 usp_oss_vos_giveMutex(USP_OssVosMutex mutex);

/* 根据进程名称查找进程号 */
extern WORD32 usp_oss_vos_getpid(BYTE *pucPName, BYTE *pucPID);

/* 启动GPRS拨号 */
extern WORD32 usp_oss_vos_startGprsPPP(BYTE *pucAPN);

/* 断开GPRS拨号链路 */
extern WORD32 usp_oss_vos_stopGprsPPP(VOID);

/* 查询GPRS拨号链路状态 */
extern WORD32 usp_oss_vos_statusGprsPPP(BYTE *pucStatus);

/* 读取文件夹包含的文件信息 */
extern WORD32 usp_oss_vos_readDir(BYTE *pucDir, T_USPOssVosDirInFo *ptUSPOssVosDirInFo, WORD16 *pwNum);

/* 原子写文件 */
extern WORD32 usp_oss_vos_fileAtomicWrite(BYTE *pucFileName, BYTE *pucBuf, WORD32 dwLen);

/* 开启WIFI */
extern WORD32 usp_oss_vos_WifiStart(BYTE ucMode, BYTE *pucEssId, BYTE *pucKey);

/* 停止WIFI */
extern WORD32 usp_oss_vos_WifiStop(VOID);

#endif  /* _USP_OSS_VOS_H */

