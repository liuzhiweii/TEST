/************************************************************************
* 版权所有 (C)2009, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： scp.h
* 文件标识： 
* 内容摘要： 系统主控内部头文件
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.08.18
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _OSS_SCP_H
#define _OSS_SCP_H


/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/

/* 看门狗任务名称 */
#define SCP_WTD_TASK_NAME                   (BYTE *)"usp_wtd"

/* 闪灯任务名称 */
#define SCP_LED_FLASH_TASK_NAME             (BYTE *)"usp_led"

/* 僵死进程检测和堆栈dump宏定义 */
#define SCP_MAX_PROC_TERM_LOG_SIZE     	    (2 * 1024)                          /* 记录进程终止信息文件最大尺寸 */
#define SCP_MAX_STACK_DUMP_LOG_SIZE         (32 * 1024)                         /* 记录堆栈dump信息文件最大尺寸 */
#define SCP_MAX_STACK_DUMP_LOG_PROBE_DEEP   (30)                                /* 堆栈信息的最大探测深度 */
#if USP_CPU_TYPE_ppc_8xx || USP_CPU_TYPE_ppc_82xx
#define SCP_PROC_TERM_LOG   			    "/mnt/app/dump/ProcTermLog.txt"	    /* 记录进程终止信息文件名称 */
#define SCP_PROC_TERM_LOG_BAK			    "/mnt/app/dump/ProcTermLogBak.txt"	/* 记录进程终止信息备份文件名称 */
#define SCP_STACK_DUMP_LOG   			    "/mnt/app/dump/StackDump.txt"	    /* 记录堆栈dump信息文件名称 */
#define SCP_STACK_DUMP_LOG_BAK			    "/mnt/app/dump/StackDumpBak.txt"    /* 记录堆栈dump信息备份文件名称 */
#else
#define SCP_PROC_TERM_LOG   			    "/mnt/var/dump/ProcTermLog.txt"	    /* 记录进程终止信息文件名称 */
#define SCP_PROC_TERM_LOG_BAK			    "/mnt/var/dump/ProcTermLogBak.txt"	/* 记录进程终止信息备份文件名称 */
#define SCP_STACK_DUMP_LOG   			    "/mnt/var/dump/StackDump.txt"	    /* 记录堆栈dump信息文件名称 */
#define SCP_STACK_DUMP_LOG_BAK			    "/mnt/var/dump/StackDumpBak.txt"    /* 记录堆栈dump信息备份文件名称 */
#endif

/* 系统TNO的最大值 */
#define SCP_MAX_TNO                         (255)

/* 每个主任务包含的一级任务的最大个数 */
#define SCP_MAX_TASK_NUM                    (8)

/* 非法的一级任务控制结构索引 */
#define SCP_INVALID_TASK_CTRL_INDEX         (0xFF)

/* NTP定时同步时间(分钟) */
#define SCP_NTP_UPDATE_TIMER                (60)

/* 等待上电响应的最大尝试次数 */
#define SCP_WAIT_POWERON_MAXTRY             (3)

/* 与应用任务握手的失败尝试次数 */
#define SCP_WAIT_KEEPALIVE_MAXTRY           (3)

/* 定时握手状态 */
#define SCP_KEEPALIVE_STAT_LIVE             (1)
#define SCP_KEEPALIVE_STAT_DEAD             (0)

/* 系统启动原因码存放的文件 */
#if USP_CPU_TYPE_ppc_8xx || USP_CPU_TYPE_ppc_82xx
#define SCP_STARTUP_REASON_FILE             "/mnt/app/ResetStatus"
#else
#define SCP_STARTUP_REASON_FILE             "/mnt/var/ResetStatus"
#endif

/* 每个消息队列所具有的消息缓存最大空间 */
#if USP_OS_LINUX
#define SCP_MSG_BUF_MAX_SIZE                (16 * 1024)
#else
#define SCP_MSG_BUF_MAX_SIZE                (0)
#endif

/* 板间SCP定时握手的时间间隔(毫秒) */
#define SCP_IB_KEEPALIVE_TIMER              (10 * 1000)

/* 板间SCP握手的失败尝试次数 */
#define SCP_IB_WAIT_KEEPALIVE_MAXTRY        (12)

/* 性能统计定时保存的时间间隔(毫秒) */
#define SCP_PSP_SAVE_TIMER                  (10 * 1000)

/* 闪灯定义 */
#if USP_OSS_LED_USE
#define SCP_LED_NO                          USP_OSS_LED_FLASH_NO
#define SCP_LED_STARTUPING                  USP_OSS_LED_FLASH_STARTUPING
#define SCP_LED_APP_START_ERR               USP_OSS_LED_FLASH_APP_START_ERR
#define SCP_LED_RUNNING                     USP_OSS_LED_FLASH_RUNNING
#define SCP_LED_ERR_FATAL                   USP_OSS_LED_FLASH_ERR_FATAL

#define SCP_LED_FLASH_ON(id)                usp_oss_led_on(id)
#define SCP_LED_FLASH_OFF(id)               usp_oss_led_off(id)
#else
#define SCP_LED_FLASH_ON(id)
#define SCP_LED_FLASH_OFF(id)
#endif

#if USP_OS_LINUX

/* 打印宏定义 */
#define     SCP_TERMINAL_PRINT(info)                perror(info)
#define     SCP_DEBUG(...)                          usp_oss_printf(USP_OSS_SCP_TNO, USP_OSS_PRINTF_LEVEL_DEBUG, __VA_ARGS__)
#define     SCP_IS_DEBUG                            usp_oss_isPrintf(USP_OSS_SCP_TNO, USP_OSS_PRINTF_LEVEL_DEBUG)
#define     SCP_ERROR(...)                          usp_oss_printf(USP_OSS_SCP_TNO, USP_OSS_PRINTF_LEVEL_ERROR, __VA_ARGS__)
#define     SCP_INFO(...)                           usp_oss_printf(USP_OSS_SCP_TNO, USP_OSS_PRINTF_LEVEL_INFO, __VA_ARGS__)

/* 日志和异常记录宏定义 */
#define     SCP_LOG_START(info)                             \
            USP_LAP_START_REPORT(info)

#define     SCP_LOG_RESET(info)                             \
            USP_LAP_RESET_REPORT(info);                     \
            SCP_ERROR("SCP Log(Reset): %s \r\n", info)

#define     SCP_LOG_INFO(info)                              \
            USP_LAP_LOG_REPORT(USP_LAP_INFO, info);         \
            SCP_DEBUG("SCP Log(Info): %s \r\n", info)
            
#define     SCP_EXCEPT(exceptCode, var1, var2, var3)        \
            USP_LAP_ABN_REPORT(var1, var2, var3, USP_LAP_ABN_FILE_ID_OSS, exceptCode); \
            SCP_ERROR("%s exception: exceptCode = %u, line = %u, var1 = %u, var2 = %u, var3 = %u \r\n", __FILE__, exceptCode, __LINE__, var1, var2, var3)

#endif  /* USP_OS_LINUX */

#if USP_OS_FREERTOS

/* 打印宏定义 */
#if USP_VERSION_DEBUG
#define     SCP_TERMINAL_PRINT(info)    \
do                                      \
{                                       \
    if (s_ucIsDebug)                    \
    {                                   \
        cprintf(info);                  \
    }                                   \
} while (0)

#define     SCP_DEBUG(...)              \
do                                      \
{                                       \
    if (s_ucIsDebug)                    \
    {                                   \
        cprintf(__VA_ARGS__);           \
    }                                   \
} while (0)

#define     SCP_IS_DEBUG                            TRUE   
#else
#define     SCP_TERMINAL_PRINT(info)             
#define     SCP_DEBUG(...)              
#define     SCP_IS_DEBUG                            FALSE
#endif
#define     SCP_ERROR                               SCP_DEBUG
#define     SCP_INFO                                SCP_DEBUG

/* 日志和异常记录宏定义 */
#define     SCP_LOG_START(info)

#define     SCP_LOG_RESET(info)                         \
            SCP_ERROR("SCP Log(Reset): %s \r\n", info)

#define     SCP_EXCEPT(exceptCode, var1, var2, var3)    \
            SCP_ERROR("%s exception: exceptCode = %u, line = %u, var1 = %u, var2 = %u, var3 = %u \r\n", __FILE__, exceptCode, __LINE__, var1, var2, var3)

#endif  /* USP_OS_FREERTOS */

/**************************************************************************
 *                            数据类型                                    *
 **************************************************************************/
/* 消息缓存数据结构 */
typedef struct tagT_ScpMsgBuff
{
    WORD32                  dwSpace;             /* 剩余空间 */
    T_USPPubAdtList         tListMsgBuff;        /* 数据块链表 */
}T_ScpMsgBuff;
        
/* 消息缓存节点数据结构*/
typedef struct tagT_ScpMsgBlock
{
    T_USPPubAdtListNode     tNode;
    BYTE				    *pucBlock;           /* 指向缓存块的起始地址 */
    WORD16                  wBlockLength;        /* 缓存块长度 */
    WORD16                  wPad;
}T_ScpMsgBlock;
        
/* 定义系统初始化配置条目 */
typedef struct tagT_ScpAppInitItem
{
    usp_oss_scp_initEntry   *initEntry;    /* 初始化函数 */
    BYTE                    ucErrorType;   /* 出错后的处理方式 */
}T_ScpAppInitItem;

/* 一级任务配置数据结构 */
typedef struct tagT_ScpTaskConfig
{
    char                    *pcName;        /* 一级任务名称 */
    usp_oss_scp_taskEntry   *taskEntry;     /* 任务处理入口函数 */
    WORD16                  wStackDepth;    /* 一级任务的堆栈大小(单位: 字节) */
    SWORD16                 swPriority;     /* 一级任务的优先级 */
    USP_OssScpTno           tno;            /* 任务标识 */   
    WORD16                  wMaxMsgNum;     /* 任务消息队列中包含的消息最大个数 */
    WORD16                  wMsgItemSize;   /* 消息队列中包含的单个消息大小 */
    WORD16                  wMsgQueueKey;   /* 消息队列的键值 */
    BYTE                    ucErrorType;    /* 出错后的处理方法 */
    BYTE                    ucIsStopMsg;    /* 是否需要接收停止消息 */
    BYTE                    ucIsKeepAlive;  /* 是否需要定时握手 */
}T_ScpTaskConfig;

/* 主任务配置数据结构 */
typedef struct tagT_ScpMainTaskConfig
{
    char                    *pcName;                            /* 主任务名称 */
    SWORD16                 swPriority;                         /* 主任务的优先级 */
	WORD32                  dwDevModel;                         /* 适用的机型 */
    T_ScpTaskConfig         atScpTaskConfig[SCP_MAX_TASK_NUM];  /* 一级任务配置信息 */
}T_ScpMainTaskConfig;

/* 主任务管理数据结构 */
typedef struct tagT_ScpMainTaskCtrl
{ 
    T_ScpMainTaskConfig         *ptScpMainTaskConfig;  /* 指向主任务配置结构 */
    USP_OssVosPid               pid;                   /* 系统分配的标识符 */
    BYTE                        ucTaskCtrl;            /* 第一个一级任务控制信息索引 */
    BYTE                        ucTaskNum;             /* 包含的一级任务个数 */
    BYTE                        ucErrorType;           /* 包含的子任务出错后的最严厉的处理方式 */                  
    BYTE                        ucIsValid;             /* 任务是否可用 */
    BYTE                        ucRealTaskNum;         /* 包含的真实任务个数 */
    BYTE                        ucPad;
    WORD16                      wPad;        
}T_ScpMainTaskCtrl;

/* 一级任务管理数据结构 */
typedef struct tagT_ScpTaskCtrl
{ 
    T_ScpTaskConfig             *ptScpTaskConfig;      /* 指向一级任务配置结构 */
    USP_OssIpcMsgQueue          msgQueue;              /* 消息队列 */
    WORD16                      wRunStatus;            /* 任务的当前状态 */
    BYTE                        ucIsValid;             /* 任务是否可用 */
    BYTE                        ucKeepAliveStat;       /* 定时握手状态 */
    T_ScpMsgBuff                tScpMsgBuff;           /* 消息缓存 */
}T_ScpTaskCtrl;

/* TCB管理数据结构 */
typedef struct tagT_ScpTcbCtrl
{ 
    WORD32                      dwTnoCtrlPos;
    WORD32                      dwMainTaskCtrlPos;
    WORD32                      dwTaskCtrlPos;    
    WORD32                      dwCustAllocPos;
    USP_OssIpcMutex             custMutex;
    WORD16                      wCustAllocCur;
    WORD16                      wCustTaskMax;
}T_ScpTcbCtrl;

/* SCP动态库操作句柄抽象数据类型 */
typedef struct tagT_ScpLibHandle
{
    USPLibScpTno                localTno;                               /* 用户脚本任务号 */
    USPLibScpTno                scpTno;                                 /* SCP模块任务号 */
    WORD16		                wMsgSequence;                           /* 消息序号 */
    WORD16                      wPad;
    BYTE                        aucMsgBuf[USP_LIB_IPC_MSG_MAX_SIZE];    /* 消息收发缓冲区 */
    T_ScpTcbCtrl                *ptTcbCtrl;                             /* TCB管理数据结构 */
    BYTE                        *pucTnoCtrl;                            /* TNO与所属的一级任务管理结构对应关系 */
    T_ScpTaskCtrl               *ptTaskCtrl;                            /* 一级任务管理结构头指针 */
    BYTE                        *pucCustAlloc;
}T_ScpLibHandle;

/* 板间SCP握手消息应答 */
typedef struct tagT_ScpIbKeepAliveAck
{
    WORD32                      dwTime;                 /* 当前时间 */
}T_ScpIbKeepAliveAck;

/**************************************************************************
 *                             类声明                                      *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/
/* 声明初始化入口函数 */
#define SCP_DECLEAR_INIT_ENTRY(NAME) \
extern usp_oss_scp_initEntry NAME;

/* 开始配置系统初始化信息 */
#define SCP_BEGIN_APPINIT_DEFINE \
static T_ScpAppInitItem s_atScpAppInitItem[] = {

/* 自定义系统初始化 */
#define SCP_IMPLEMENT_APPINIT(ENTRY, ERROR_TYPE) \
{ENTRY, ERROR_TYPE},

/* 结束配置系统初始化信息 */
#define  SCP_END_APPINIT_DEFINE \
{NULL, 0} \
};

/* 声明任务入口函数 */
#define SCP_DECLEAR_TASK_ENTRY(NAME) \
extern usp_oss_scp_taskEntry NAME;

/* 声明一级任务配置信息 */
#define SCP_DECLEAR_UPPERTASK(NAME) \
static T_ScpTaskConfig NAME[];

/* 开始任务配置 */
#define SCP_BEGIN_TASK_DEFINE \
static T_ScpMainTaskConfig s_atScpMainTaskConfig[] = {

/* 结束任务配置 */
#define SCP_END_TASK_DEFINE \
};

/* 配置第一轮上电进程 */
#define SCP_FIRST_POWERON_TNO(TNO_SET...) \
static WORD32 s_adwScpFirstPowerOnTno[] = {0xFFFFFFFF, ## TNO_SET, 0xFFFFFFFF};

/* 配置第二轮上电进程 */
#define SCP_SECOND_POWERON_TNO(TNO_SET...) \
static WORD32 s_adwScpSecondPowerOnTno[] = {0xFFFFFFFF, ## TNO_SET, 0xFFFFFFFF};

/* 配置第三轮上电进程 */
#define SCP_THIRD_POWERON_TNO(TNO_SET...) \
static WORD32 s_adwScpThirdPowerOnTno[] = {0xFFFFFFFF, ## TNO_SET, 0xFFFFFFFF};

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/
 
/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/


#endif  /* _OSS_SCP_H */

