/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_pub.h
* 文件标识： 
* 内容摘要： 定义公共数据(需要重新规划)
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.03.10
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_PUB_H
#define _USP_PUB_H

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
#define USP_SUCCESS         (0)
#define ERROR               (-1)

/* 定义打印信息级别 */
#define	USP_OSS_PRINTF_LEVEL_ALERT 	    ((BYTE)(0x02))	/* 异常信息 */
#define	USP_OSS_PRINTF_LEVEL_ERROR 		((BYTE)(0x04))	/* 错误信息 */
#define	USP_OSS_PRINTF_LEVEL_WARNING 	((BYTE)(0x08))	/* 告警信息 */
#define	USP_OSS_PRINTF_LEVEL_NOTICE 	((BYTE)(0x10))	/* 重要提示信息 */
#define	USP_OSS_PRINTF_LEVEL_INFO 		((BYTE)(0x20))	/* 一般提示信息 */
#define	USP_OSS_PRINTF_LEVEL_DEBUG 		((BYTE)(0x40))	/* 调试信息 */

/* 基于Linux的消息队列、互斥锁和共享内存键值定义 */
#define USP_OSS_TIMER_MUTEX_KEY          (1000)  /* 定时器模块，定时器缓存互斥信号量缓存 */
#define USP_OSS_SYSDATA_MUTEX_KEY        (9100)  /* 系统参数区互斥信号量 */
#define USP_DRV_I2C_MUTEX1_KEY           (9101)  /* I2C读写互斥锁 */
#define USP_DRV_I2C_MUTEX2_KEY           (9102)  /* I2C读写互斥锁 */
#define USP_OSS_ST_MUTEX_KEY             (9103)  /* 信令跟踪内存管理互斥锁 */
#define USP_OSS_PRINTF_MUTEX_KEY         (9104)  /* 打印控制互斥锁 */
#define USP_OSS_LED_MUTEX_KEY            (9105)  /* 闪灯管理互斥锁 */
#define USP_OSS_SCP_CUST_MUTEX_KEY       (9106)  /* 用户自定义任务管理互斥锁 */
#define USP_OSS_MPI_RF_CHECK_MUTEX_KEY   (9107)  /* 二义性射频检测互斥锁 */
#define USP_OSS_GPIO_MUTEX_KEY           (9108)  /* GPIO管理互斥锁 */
#define USP_VIR_TAG_MUTEX_KEY            (9109)  /* 虚拟标签互斥锁 */

#define USP_OSS_SCP_TCB_SHM_KEY          (9200)  /* 任务控制块共享内存键值 */
#define USP_OSS_SCP_WTD_CTRL_SHM_KEY     (9201)  /* 看门狗控制共享内存键值 */
#define USP_OSS_PRINTF_CTRL_SHM_KEY      (9202)  /* 打印控制共享内存键值 */
#define USP_OSS_ST_CTRL_SHM_KEY          (9203)  /* 信令跟踪控制信息共享内存键值 */
#define USP_OSS_ST_BUF_SHM_KEY           (9204)  /* 信令跟踪存储共享内存键值 */
#define USP_OSS_PRINTF_BUF_SHM_KEY       (9205)  /* 打印控制存储共享内存键值 */
#define USP_IDTE_SHM_KEY                 (9206)  /* IDTE共享内存键值 */
#define USP_OSS_LED_SHM_KEY              (9207)  /* 闪灯管理共享内存键值 */
#define USP_PUB_PSP_SHM_KEY              (9208)  /* 性能统计共享内存键值 */
#define USP_OSS_TIMER_SHM_KEY            (1500)  /* 定时器模块共享内存键值 */
#define USP_VIR_TAG_SHM_KEY              (9209)  /* 虚拟标签模块共享内存*/
#define USP_VIR_TAG_SHM1_KEY             (9210)  /* 虚拟标签模块共享内存*/

#define USP_OAM_CLI_MSG_KEY              (9001)  /* 命令行界面(CLI)消息队列关键字 */
#define USP_OAM_LAP_MSG_KEY              (9002)  /* 日志与异常探针(LAP)消息队列关键字 */
#define USP_COMM_MSG_KEY                 (9003)  /* 通信模块(COMM)消息队列关键字 */
#define USP_OSS_SCP_MSG_KEY              (9004)  /* 系统主控(SCP)消息队列关键字 */
#define USP_COMM_IPD_MSG_KEY             (9005)  /* ip发现工具使用 */
#define USP_OAM_CMP_MSG_KEY              (9006)  /* 配置管理(CMP)消息队列关键字 */
#define USP_COMM_HOLD_MSG_KEY            (9007)  /* 断链缓存处理模块(COMM_HOLD)消息队列关键字 */
#define USP_OSS_ST_MSG_KEY               (9008)  /* 信令跟踪模块(ST)消息队列关键字 */
#define USP_OAM_VMP_MSG_KEY              (9009)  /* 版本管理(VMP)消息队列关键字 */
#define USP_OAM_DMP_MSG_KEY              (9010)  /* 诊断测试(DMP)消息队列关键字 */
#define USP_OSS_SMP_MSG_KEY	             (9011)  /* 状态监控(SMP)消息队列关键字 */
#define USP_IDTE_SUB_MSG_KEY             (9012)  /* 集成测试工具(IDTE)辅助任务消息队列关键字 */
#define USP_IDTE_CASE_MSG_KEY            (9013)  /* 集成测试工具(IDTE)用例任务消息队列关键字 */
#define USP_OAM_AMP_MSG_KEY              (9014)  /* 告警管理(AMP)消息队列关键字 */
#define USP_UHF_PROTOCOL_KEY             (9015)  /* 超高频协议处理消息队列关键字 */
#define USP_UHF_RF_KEY                   (9016)  /* 超高频射频处理消息队列关键字 */
#define USP_ETC_PROTOCOL_KEY             (9017)  /* ETC 协议处理消息队列关键字 */
#define USP_ETC_RF_KEY                   (9018)  /* ETC 射频处理消息队列关键字 */
#define USP_UHF_RDP_RULE_KEY             (9019)  /* UHF 规则下发消息队列关键字 */
#define USP_UHF_RDP_REPORT_KEY           (9020)  /* UHF 报告处理消息队列关键字 */
#define USP_UHF_RDP_LLRP_KEY             (9021)  /* UHF 规则处理消息队列关键字 */
#define USP_MPI_PROTOCOL_KEY             (9022)  /* MPI 协议处理消息队列关键字 */
#define USP_MPI_RF_KEY      	         (9023)  /* MPI 射频处理消息队列关键字 */
#define USP_OSS_PSAM_EXT_MSG_KEY         (9024)  /* 扩展PSAM处理任务消息队列关键字 */
#define USP_OSS_GPIO_MSG_KEY             (9025)  /* GPIO处理任务消息队列关键字 */
#define USP_OSS_MISC_MSG_KEY             (9026)  /* 杂项处理任务消息队列关键字 */
#define USP_VIR_TAG_MSG_KEY              (9027)  /* 虚拟标签进程消息对列关键字 */
#define USP_COMM_SMS_MSG_KEY             (9028)  /* 短消息模块消息队列关键字 */

#define USP_CUST_MSG_KEY_START           (9051)  /* 用户自定义任务消息队列起始关键字 */

/* 定义消息格式 */
#define USP_PUB_MSG_FORMAT_LLRP               (0)     /* LLRP消息格式 */
#define USP_PUB_MSG_FORMAT_STRUCT             (1)     /* 结构类型消息格式 */

/* 中继消息魔术字 */
#define USP_PUB_MSG_RELAY                     (0x5A5A)

/* 前台内部使用的设备类型 */
#define USP_PUB_DEV_MODEL_COMMON              (0xFFFFFFFF)     /* 通用 */
#define USP_PUB_DEV_MODEL_READER_UHF          (0x1)            /* 超高频阅读器 */
#define USP_PUB_DEV_MODEL_READER_ETC          (0x2)            /* ETC阅读器 */
#define USP_PUB_DEV_MODEL_READER_MPI          (0x4)            /* 二义性阅读器 */
#define USP_PUB_DEV_MODEL_HANDSET_UHF         (0x8)            /* 超高频手持机 */
#define USP_PUB_DEV_MODEL_HANDSET_ETC         (0x10)           /* ETC手持机 */
#define USP_PUB_DEV_MODEL_UNKNOW              (0x80000000)     /* 未知 */

/* 网管接口类型 */
#define USP_PUB_OAM_IF_TYPE_LLRP              0                /* LLRP协议 */
#define USP_PUB_OAM_IF_TYPE_ZTE               1                /* ZTE协议 */

/* 计算结构中，某变量前的长度 */
#define usp_pub_getStructFixedLen(structType, member)   /*lint -save -e413 */ (WORD16)((WORD32)((BYTE *)&(((structType *)0)->member))) /*lint -restore */

/* 恢复出厂设置的参数名称 */
#define USP_PUB_SET_DEFAULT_ITEM        "set_default"

/* CPU类型定义 */
#define USP_CPU_MPC852        (0)
#define USP_CPU_MPC8241       (1)
#define USP_CPU_MPC8306       (2)
#define USP_CPU_MPC8313       (3)
#define USP_CPU_LPC2138       (4)
#define USP_CPU_LPC2148       (5)
#define USP_CPU_LPC2468       (6)

/* LINUX内核版本定义 */
#define USP_OS_LINUX_15       (0) /*linux 2.6.15版本*/
#define USP_OS_LINUX_38       (1) /*linux 2.6.38版本*/


/* 硬件类型定义 */
#define USP_HD_EC00_BOARD0    (0) /*EC00老版*/
#define USP_HD_6601_BOARD0    (1) /*6601老版*/
#define USP_HD_8801_BOARD0    (2) /*8801老版*/
#define USP_HD_8700_BOARD0    (3) /*8700老版*/
#define USP_HD_8900_BOARD0    (4) /*8900B   版*/
#define USP_HD_8900_BOARD1    (5) /*8900RUP 版*/
#define USP_HD_6700_BOARD0    (6) /*6700老版*/
#define USP_HD_6700_BOARD1    (7) /*6700小改版*/
#define USP_HD_6700_BOARD2_D  (8) /*6700RUP版数字板*/
#define USP_HD_6700_BOARD2_R  (9) /*6700RUP版射频板*/
#define USP_HD_8700_BOARD1_R  (10)/*8700RUP版射频板*/

/*OS类型定义 */
#define OS_LINUX              (0) /*LINUX*/
#define OS_FREERTOS           (1) /*FREERTOS*/
#define OS_UBOOT              (2) /*UBOOT*/

/*T_IOType 类型定义 */
#define DRV_EPLD              (0) /*EPLD*/
#define DRV_IOPORT            (1) /*IOPORT*/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
/* CPU内进程间通信消息头 */
typedef struct tagT_Msg
{
    long        mtype;          /* Message type, used by linux */
    BYTE        ucLinkType;     /* 链路物理类型 */
    BYTE        ucLinkIndex;    /* 链路索引号 */
    WORD16      wSenderTno;     /* 发送端任务号 */
    WORD16      wReceiverTno;   /* 接收端任务号 */    
    WORD16      wMsgID;         /* 消息事件号 */
    WORD16      wMsgLen;        /* 消息长度，不包括消息头，BYTE为单位 */
    WORD16      wMsgSequence;   /* 消息序号 */ 
    WORD16      wSrcTno;        /* 源任务号 */
    WORD16      wDstTno;        /* 目的任务号 */
    WORD16      wRelayMagic;    /* 中继消息魔术字 */
    WORD16      wPad;
}T_Msg;

/* 系统配置信息 */
typedef struct tagT_USPPubConfig
{
    WORD16      wDevID;             /* 设备号 */
    BYTE        ucIsSetDefault;     /* 是否恢复出厂设置 */
    BYTE        aucSerialNum[9];    /* 电子序列号 */
    BYTE        aucMacAddress[6];   /* MAC地址 */
    BYTE        ucBigEndian;        /* 大端字节序? */
    BYTE        ucIsDistributed;    /* 是否是分布式系统 */
    BYTE        ucIsDebug;          /* 是否是调试版本 */
    BYTE        ucOamIfType;        /* 网管接口类型 */    
    BYTE        aucPad[2];
    WORD16      wDevType;           /* 设备型号 */
    WORD16      wDevSpec;           /* 设备规格 */
    WORD32      dwDevModel;         /* 前台内部使用的设备类型 */
    WORD32      dwVersion;          /* 版本号 */
    WORD32      dwNet1Addr;         /* 第二块网卡的IP地址 */
}T_USPPubConfig;

/* 性能统计信息数据结构 */
typedef struct tagT_USPPubStatisticsConf
{
    char        *pcName;        /* 名称 */
    WORD32      dwDevModel;     /* 适用的机型 */
}T_USPPubStatisticsConf;

typedef union tagT_USPPubStatisticsInfo
{
    WORD32      adwVal[64];     /* 统计值 */
}T_USPPubStatisticsInfo;

/* I2C, SPI模块可共用 */
#if 0
typedef volatile enum tagT_IOType
{
	    DRV_EPLD = 0,   /* epld管脚模拟 */
	    DRV_IOPORT		/* io口模拟 */
}T_IOType;
#endif
typedef BYTE T_IOType ;

typedef struct tagT_USPDrvIO
{
    WORD32 data_mask;   /* 数据寄存器掩码 */
    WORD32 dir_mask;    /* 方向寄存器掩码 */
    WORD32 data_reg;    /* 数据寄存器 */
    WORD32 dir_reg;     /* 方向寄存器 */
}T_USPDrvIO;

/* 输入输出 ：驱动部分可以共用 */
typedef enum tagT_DrvIODirc
{
	    DRV_OUT=0x1,
	    DRV_IN=0
} T_DrvIODirc;



/* IO信号：驱动部分可以共用 */




/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/* 系统配置信息 */
extern T_USPPubConfig           g_tUSPPubConfig;

/* 性能统计配置信息 */
extern T_USPPubStatisticsConf   g_atUSPPubStatisticsConf[];

/* 性能统计信息 */
extern T_USPPubStatisticsInfo  *g_ptUSPPubStatisticsInfo;

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
WORD32 usp_pub_countCRC32(BYTE * pucData, WORD32 dwLen);
WORD16 usp_pub_countCRC16(BYTE *pucData, WORD16 wLength, WORD16 wPreCRC16);
extern WORD32 usp_pub_init(VOID);
#endif  /*_USP_PUB_H */

