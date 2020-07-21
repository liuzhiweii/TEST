/***************************************************************************
* 版权所有 (C)2009, 深圳市中兴通讯股份有限公司。
*
* 文件名称：scp.c
* 文件标识：
* 内容摘要：系统主控(SCP)实现
* 其它说明：
* 当前版本：
* 作    者：高峰 
* 完成日期：2009.08.18
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************************/

//#include "usp.h"
//#if USP_OSS_SCP_USE
#include "usp_typeDef.h"
#include "usp_pub.h"
#include "usp_vos.h"
#include "usp_ipc.h"
#include "usp.conf"
#include "usp_pubAdt.h"
#include "usp_eventDef.h"
/***********************************************************
 *                        包含头文件                       *
 **********************************************************/
#include "usp_errorDef.h"
#include "usp_lib.h"
#include "usp_lib_scp.h"
#include "usp_scp.h"
#include "scp.h"
#define _OSS_SCP_C_INCLUDE
#include "scp.conf"
#undef  _OSS_SCP_C_INCLUDE

/***********************************************************
 *                     常量定义                            *
***********************************************************/

/***********************************************************
*                 文件内部使用的宏                         *
***********************************************************/

#ifndef SCP_KEEPALIVE_TIMER
/* 与应用任务定时握手的时间间隔(毫秒) */
#define SCP_KEEPALIVE_TIMER                 (10 * 1000)
#endif

#ifndef SCP_PRINTF_BUF_SIZE
/* 系统启动阶段打印控制缓冲区大小 */
#define SCP_PRINTF_BUF_SIZE                 (0)
#endif

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/

/***********************************************************
 *                     全局变量                            *
***********************************************************/
#if USP_OS_FREERTOS
/* 
 * 调试代理需要使用的全局变量。
 * 先暂时放在这里，以后可以考虑放在打印代理实现文件中。
 */
xQueueHandle        g_DebugProxyQueue;
xSemaphoreHandle    xPrintSem;
#endif  

/***********************************************************
 *                     本地变量                            *
***********************************************************/
static BYTE                 *s_pucScpTnoCtrl = NULL;        /* TNO与所属的一级任务管理结构对应关系 */
static T_ScpMainTaskCtrl    *s_ptScpMainTaskCtrl = NULL;    /* 主任务管理结构头指针 */
static WORD16               s_wScpMainTaskNum = 0;          /* 主任务个数 */
static T_ScpTaskCtrl        *s_ptScpTaskCtrl = NULL;        /* 一级任务管理结构头指针 */
static BYTE                 s_ucScpIsSendStopMsg = FALSE;   /* 是否需要发送停止消息 */
static BYTE                 s_aucScpKeepLive[SCP_MAX_TNO];  /* 保存与应用任务的握手结果 */

static BYTE                 s_aucScpRecvMsgBuf[64];         /* 定义消息接收缓冲区 */
#if USP_OAM_CLI_USE
static BYTE                 s_aucScpSendMsgBuf[4096];       /* 定义消息发送缓冲区 */
#else
static BYTE                 s_aucScpSendMsgBuf[64];         /* 定义消息发送缓冲区 */
#endif

/* 上电顺序表 */
static WORD32               *s_apdwScpPowerOnTnoSet[] = {
    //s_adwScpFirstPowerOnTno,
    //s_adwScpSecondPowerOnTno,
    //s_adwScpThirdPowerOnTno
};

static BYTE                 s_aucScpLog[64];                 /* 临时存放日志信息 */

#if USP_OAM_CLI_USE
/* 错误处理类型的文字描述 */
static BYTE                 *s_apucScpErrorType[] = {
    (BYTE *)"RESET",
    (BYTE *)"ALARM",
    (BYTE *)"IGNORE"
};
#endif

#if USP_OS_FREERTOS
static BYTE                 s_ucIsDebug = FALSE;            /* 是否可以输出调试信息 */
#endif

#if USP_DRV_WTD_USE
/* 控制喂狗任务是否喂狗 */
static BYTE                 s_ucScpIsFeedWatchDog = TRUE;
static BYTE                 *s_pucScpIsFeedWatchDogCtrl = &s_ucScpIsFeedWatchDog; 
#endif

#if SCP_NTP_USE
/* 记录NTP同步是否成功 */
static BYTE                 s_ucScpIsNtpUpdateSuccess = TRUE;
/* NTP配置信息 */
static T_USPOssScpNtpCfg    s_tScpNtpCfg = {{0}, 0, 0, 0, SCP_NTP_UPDATE_TIMER};
/* NTP客户端进程号 */
static USP_OssVosPid        s_scpNtpPid = 0;
#endif

/* USP系统初始化 */
static T_ScpAppInitItem     s_atScpUspInitItem[] = {
    #if USP_OSS_SYSDATA_USE
    //{usp_oss_sysdata_init, USP_OSS_SCP_ERROR_TYPE_RESET},
    #endif

    #if USP_OAM_VMP_BODY_USE
    //{usp_oam_vmp_init, USP_OSS_SCP_ERROR_TYPE_RESET},
    #endif

    #if USP_OAM_CMP_USE
    //{usp_oam_cmp_init, USP_OSS_SCP_ERROR_TYPE_IGNORE},
    #endif

    #if USP_OS_LINUX
    //{usp_oss_scp_pspInit, USP_OSS_SCP_ERROR_TYPE_IGNORE},
    #endif

    {NULL, 0}
};

/* 系统初始化入口 */
static T_ScpAppInitItem     *s_aptScpInitEntry[] = {
   // s_atScpUspInitItem,
    //s_atScpAppInitItem,
    NULL
};

#if USP_OSS_ST_USE
/* 信令跟踪描述信息 */
static BYTE                 s_aucScpTraceSendDesc[USP_OSS_ST_DESC_SIZE] = {0}; 
static BYTE                 s_aucScpTraceRecvDesc[USP_OSS_ST_DESC_SIZE] = {0}; 
#endif

/***********************************************************
 *                     全局函数                            *
***********************************************************/
#if SCP_NTP_USE && USP_OSS_PRINTF_USE
extern WORD32 SCP_GET_NTP_CONFIG(T_USPOssScpNtpCfg *ptUSPOssScpNtpCfg);
#else
#undef SCP_GET_NTP_CONFIG
#define SCP_GET_NTP_CONFIG(cfg) USP_OSS_SCP_ERR_GET_NTP_CFG
#endif

/***********************************************************
 *                     局部函数                            *
***********************************************************/
static WORD32 scp_initBsp(VOID);
static WORD32 scp_startWatchDog(VOID);
static WORD32 scp_startLedFlash(VOID);
static VOID scp_reset(VOID);
static VOID scp_initUsp(VOID);
static VOID scp_initApp(VOID);
static VOID scp_runTask(VOID);
static VOID scp_initTCB(VOID);
static VOID scp_startTasks(VOID);
static VOID scp_poweronTasks(VOID);
static VOID scp_mainTaskEntry(VOID *arg);
static VOID scp_taskEntry(VOID *arg);
#if USP_OS_LINUX
static VOID scp_setZombieAndStackdump(VOID);
static VOID scp_pspSave(VOID);
#endif
#if SCP_NTP_USE
static VOID scp_updateNtp(BYTE ucIsUpdateTimeZone, BYTE ucIsCfgChg);
#if USP_OAM_AMP_USE
#define SCP_ALARM_NTP \
do \
{ \
    if (FALSE == s_ucScpIsNtpUpdateSuccess \
     && USP_PUB_OAM_IF_TYPE_LLRP == g_tUSPPubConfig.ucOamIfType) \
    { \
        SCP_DEBUG("(SCP_ALARM_NTP) running...... \r\n"); \
        usp_amp_reportAlarm(EV_USP_OAM_AMP_InformReport, \
                            R_OSS_NTP_SERVER_CANNOT_CONNECT_ALARM, \
                            RSN_INVALID, \
                            USP_OAM_AMP_ALARM_LEVEL_INFORM, \
                            NULL, \
                            0); \
    } \
} while (0)
#else
#define SCP_ALARM_NTP
#endif
#endif
static WORD32 scp_setTime(WORD32 dwTime);

#if (USP_OS_LINUX && USP_OSS_PRINTF_USE) || USP_OS_FREERTOS
/**************************************************************************
* 函数名称：main
* 功能描述：应用程序入口
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
#if USP_OS_LINUX
#if 0
int main(int argc, char *argv[])
{
    extern char *optarg;	
    extern int  optind;	
    int         opt;
    WORD32      dwRet;    
    T_Msg       *ptMsg = (T_Msg *)s_aucScpSendMsgBuf;

    memset(&g_tUSPPubConfig, 0 ,sizeof(g_tUSPPubConfig));
    
    /* 解析程序运行参数 */    
    #if USP_IS_DISTRIBUTED
    g_tUSPPubConfig.ucIsDistributed = TRUE;
    #endif
    #if USP_VERSION_DEBUG
    g_tUSPPubConfig.ucIsDebug = TRUE;
    #endif
    
    while ((opt = getopt(argc, argv, "sd")) != EOF) 
    {
        switch (opt) 
        {
            case 's':
                g_tUSPPubConfig.ucIsDistributed = FALSE;
                break;

            case 'd':
                g_tUSPPubConfig.ucIsDebug = TRUE;
                break;                
        }
    }   
#endif 
#else
int main(void)
{
    WORD32      dwRet;    
    T_Msg       *ptMsg = (T_Msg *)s_aucScpSendMsgBuf;

    memset(&g_tUSPPubConfig, 0 ,sizeof(g_tUSPPubConfig));
#endif
    
    #if USP_IDTE_USE
    /* 初始化IDTE */
    BYTE        *pucIDTE;
    pucIDTE = (BYTE *)usp_oss_mm_staticMalloc(USP_IDTE_SHM_KEY, 64 * 1024);
    if (NULL == pucIDTE)
    {
       SCP_TERMINAL_PRINT("malloc pucIDTE error! \r\n");
       return 0;
    }
    
    g_pIDTEbProcFlag = pucIDTE;
    g_pIDTEbExist = pucIDTE + 4;
    g_pIDTEApp = pucIDTE + 8;
    *g_pIDTEbProcFlag = 0;
    *g_pIDTEbExist = 0;
    #endif

    SCP_TERMINAL_PRINT("Application start! \r\n");

    #if USP_OAM_LAP_USE
    /* 初始化日志和异常探针 */
    dwRet = usp_lap_init();
    SCP_DEBUG("Init lap dwRet = %u \r\n", dwRet);
    #endif
    
    #if USP_OAM_CLI_USE    
    /* 初始化打印控制 */
    dwRet = usp_cli_initPrintf(SCP_PRINTF_BUF_SIZE);
    if (USP_SUCCESS != dwRet)
    {
        sprintf((char *)s_aucScpLog, "Initialize printf error, code = %u", dwRet);        
        SCP_TERMINAL_PRINT((char *)s_aucScpLog);
        scp_reset();
    }
    SCP_DEBUG("Init printf success! \r\n");

    #if USP_OSS_ST_USE
    /* 初始化信令跟踪 */
    dwRet = usp_cli_initTrace();    
    if (USP_SUCCESS != dwRet)
    {
        sprintf((char *)s_aucScpLog, "Initialize signaling trace error, code = %u", dwRet);
        SCP_TERMINAL_PRINT((char *)s_aucScpLog);
        scp_reset();
    }    
    strcpy((char *)s_aucScpTraceSendDesc, "usp_oss_scp_sendTaskMsg");
    strcpy((char *)s_aucScpTraceRecvDesc, "usp_oss_scp_recvTaskMsg");    
    #endif
    
    #endif

    /* 初始化硬件 */
    dwRet = scp_initBsp();
    if (USP_SUCCESS != dwRet)
    {
        sprintf((char *)s_aucScpLog, "Initialize BSP error, code = %u", dwRet);
        scp_reset();
    }

    /* 启动看门狗 */
    dwRet = scp_startWatchDog();
    if (USP_SUCCESS != dwRet)
    {
        sprintf((char *)s_aucScpLog, "Start WatchDog error, code = %u", dwRet);
        scp_reset();
    }

    /* 启动闪灯任务 */
    dwRet = scp_startLedFlash();
    if (USP_SUCCESS != dwRet)
    {
        sprintf((char *)s_aucScpLog, "Start Led Flash error, code = %u", dwRet);
        scp_reset();
    }

    /* 系统公共信息初始化 */
    dwRet = usp_pub_init();
    if (USP_SUCCESS != dwRet)
    {
       // SCP_EXCEPT(dwRet, 0, 0, 0);
    }
    
    /* 初始化通信设施 */
    dwRet = usp_oss_vos_initComm();
    if (USP_SUCCESS != dwRet)
    {
        //SCP_EXCEPT(USP_OSS_SCP_ERR_INIT_COMM, dwRet, 0, 0);
    }

    #if SCP_NTP_USE
    /* ntp时间同步, 以保证系统运行后时间的准确性 */
    scp_updateNtp(TRUE, FALSE);
    #endif
    
    /* 记录系统开始运行日志 */
    SCP_LOG_START((BYTE *)"Application start"); 

    /* USP平台初始化 */
    scp_initUsp();

    /* 应用初始化 */     
    scp_initApp();

    /* 打印配置信息 */
    SCP_DEBUG("PubConfig: wDevID = %u, ucIsSetDefault = %u, ucBigEndian = %u, ucIsDistributed = %u, ucIsDebug = %u, ucOamIfType = %u, wDevType = 0x%04x, wDevSpec = 0x%04x, dwDevModel = 0x%08x, dwVersion = 0x%08x, aucSerialNum = %02x%02x%02x%02x%02x%02x%02x%02x%02x, aucMacAddress = %02x:%02x:%02x:%02x:%02x:%02x \r\n", \
              g_tUSPPubConfig.wDevID, \
              g_tUSPPubConfig.ucIsSetDefault, \
              g_tUSPPubConfig.ucBigEndian, \
              g_tUSPPubConfig.ucIsDistributed, \
              g_tUSPPubConfig.ucIsDebug, \
              g_tUSPPubConfig.ucOamIfType, \
              g_tUSPPubConfig.wDevType, \
              g_tUSPPubConfig.wDevSpec, \
              g_tUSPPubConfig.dwDevModel, \
              g_tUSPPubConfig.dwVersion, \
              g_tUSPPubConfig.aucSerialNum[0], g_tUSPPubConfig.aucSerialNum[1], g_tUSPPubConfig.aucSerialNum[2], \
              g_tUSPPubConfig.aucSerialNum[3], g_tUSPPubConfig.aucSerialNum[4], g_tUSPPubConfig.aucSerialNum[5], \
              g_tUSPPubConfig.aucSerialNum[6], g_tUSPPubConfig.aucSerialNum[6], g_tUSPPubConfig.aucSerialNum[8], \
              g_tUSPPubConfig.aucMacAddress[0], g_tUSPPubConfig.aucMacAddress[1], g_tUSPPubConfig.aucMacAddress[2], \
              g_tUSPPubConfig.aucMacAddress[3], g_tUSPPubConfig.aucMacAddress[4], g_tUSPPubConfig.aucMacAddress[5]);

    /* 启动应用任务 */
    scp_runTask();

    /* 启动系统控制服务 */
    ptMsg->mtype = 1;
    ptMsg->wSenderTno = USP_OSS_SCP_TNO;
    ptMsg->wMsgLen = 0;
    ptMsg->wMsgID = EV_USP_SCP_PowerOn;
    usp_oss_scp_sendTaskMsg(USP_OSS_SCP_TNO, ptMsg, USP_OSS_IPC_FOREVERWAIT);
    
    #if USP_OS_FREERTOS    
    /* 开始任务调度 */
    vTaskStartScheduler();    
    #else
    /* 睡眠 */
    for (; ;)
    {
        USP_OSS_VOS_SLEEP_SEC(60 * 60);
    }    
    #endif

    //return USP_SUCCESS;
}
#endif  /* (USP_OS_LINUX && USP_OSS_PRINTF_USE) || USP_OS_FREERTOS */

/**************************************************************************
* 函数名称：scp_initApp
* 功能描述：系统初始化
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_initApp(VOID)
{
    WORD32      dwRet;
    WORD16      wLoop;
    WORD16      wLoopEntry;

    /* 根据配置一步步进行系统初始化 */
    SCP_DEBUG("(scp_initApp) start application init \r\n");

    for (wLoopEntry = 0; NULL != s_aptScpInitEntry[wLoopEntry]; wLoopEntry++)
    {
        for (wLoop = 0; NULL != s_aptScpInitEntry[wLoopEntry][wLoop].initEntry; wLoop++)
        {
            dwRet = (*(s_aptScpInitEntry[wLoopEntry][wLoop].initEntry))();

            SCP_DEBUG("(scp_initApp) init %u, ret = %u \r\n", wLoop, dwRet);
                
            if (USP_SUCCESS != dwRet)
            {
                /* 根据用户配置进行错误处理 */
                if (USP_OSS_SCP_ERROR_TYPE_RESET == s_aptScpInitEntry[wLoopEntry][wLoop].ucErrorType)
                {
                    //SCP_LED_FLASH_ON(SCP_LED_APP_START_ERR);
                    sprintf((char *)s_aucScpLog, "Initialize application error, code = %u", dwRet);
                    scp_reset();
                }
                else
                {
                    //SCP_EXCEPT(dwRet, 0, 0, 0);                
                }            
            }
        }
    }

    return;
}

/**************************************************************************
* 函数名称：scp_runTask
* 功能描述：运行应用任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_runTask(VOID)
{
    #if 0
    /* 初始化任务控制信息 */
    scp_initTCB();

    #if USP_OAM_LAP_USE
    /* 此时设置标记，表明可以以正常消息收发方式记录日志和异常 */
    usp_lap_setRun();
    #endif

    /* 启动应用任务 */
    scp_startTasks();
    
    #endif
    return;
}

/**************************************************************************
* 函数名称：scp_initTCB
* 功能描述：初始化任务控制信息
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_initTCB(VOID)
{
    #if 0
    WORD32                  dwRet;
    WORD32                  dwMSize;    
    WORD16                  wLoop;
    WORD16                  wLoopInter;
    WORD16                  wMainTaskNum = 0;
    WORD16                  wTaskNum = 0;
    BYTE                    ucTaskCtrl = 0;
    BYTE                    ucErrorType;
    T_ScpMainTaskCtrl       *ptMainTaskCtrl;
    T_ScpTaskConfig         *ptTaskConfig;
    T_ScpTcbCtrl            *ptTcbCtrl;

    SCP_DEBUG("(scp_initTCB) running ...... \r\n");
    
    /*
     * 获取任务控制内存空间。
     * 首先计算所需的内存空间，然后再申请内存。
     */
    dwMSize = sizeof(T_ScpTcbCtrl);
    dwMSize += sizeof(BYTE) * SCP_MAX_TNO;

//    wMainTaskNum = sizeof(s_atScpMainTaskConfig) / sizeof(T_ScpMainTaskConfig);    
    for (wLoop = 0; wLoop < wMainTaskNum; wLoop++)
    {
//        if (!(s_atScpMainTaskConfig[wLoop].dwDevModel & g_tUSPPubConfig.dwDevModel))
        {
            /* 过滤掉机型不匹配的任务 */
            continue;
        }

        s_wScpMainTaskNum++;
        //for(wLoopInter = 0; ;
//            wLoopInter < SCP_MAX_TASK_NUM && NULL != s_atScpMainTaskConfig[wLoop].atScpTaskConfig[wLoopInter].pcName; \
          //  wLoopInter++)        
        {
        //    wTaskNum++;
        }        
    }
    #ifdef SCP_MAX_CUST_TASK_NUM
    dwMSize += sizeof(BYTE) * SCP_MAX_CUST_TASK_NUM;
    wTaskNum += SCP_MAX_CUST_TASK_NUM;
    #endif
    dwMSize += sizeof(T_ScpMainTaskCtrl) * s_wScpMainTaskNum + sizeof(T_ScpTaskCtrl) * wTaskNum;    
    
    SCP_DEBUG("(scp_initTCB) malloc task control, total size = %u(Bytes) \r\n", \
              dwMSize);

    ptTcbCtrl = (T_ScpTcbCtrl *)usp_oss_mm_staticMalloc(USP_OSS_SCP_TCB_SHM_KEY, dwMSize);    
    if (NULL == ptTcbCtrl)
    {
//        SCP_LED_FLASH_ON(SCP_LED_APP_START_ERR);
        sprintf((char *)s_aucScpLog, "Malloc task control error");
        scp_reset();
    }

    memset(ptTcbCtrl, 0, dwMSize);
    s_pucScpTnoCtrl = (BYTE *)(ptTcbCtrl + 1);
    s_ptScpMainTaskCtrl = (T_ScpMainTaskCtrl *)(s_pucScpTnoCtrl + SCP_MAX_TNO);    
    s_ptScpTaskCtrl = (T_ScpTaskCtrl *)(s_ptScpMainTaskCtrl + s_wScpMainTaskNum);    

    ptTcbCtrl->dwTnoCtrlPos = (BYTE *)s_pucScpTnoCtrl - (BYTE *)ptTcbCtrl;
    ptTcbCtrl->dwMainTaskCtrlPos = (BYTE *)s_ptScpMainTaskCtrl - (BYTE *)ptTcbCtrl;
    ptTcbCtrl->dwTaskCtrlPos = (BYTE *)s_ptScpTaskCtrl - (BYTE *)ptTcbCtrl;

    /* 初始化TNO与所属的一级任务管理结构对应关系 */
    for (wLoop = 0; wLoop < SCP_MAX_TNO; wLoop++)
    {
        s_pucScpTnoCtrl[wLoop] = SCP_INVALID_TASK_CTRL_INDEX;
    }

    /* 
     * 初始化任务控制结构, 同时分配任务所需的资源。
     */
    SCP_DEBUG("(scp_initTCB) start init task control \r\n");
    
    for (wLoop = 0, ptMainTaskCtrl = s_ptScpMainTaskCtrl; wLoop < wMainTaskNum; wLoop++)
    {
//        if (!(s_atScpMainTaskConfig[wLoop].dwDevModel & g_tUSPPubConfig.dwDevModel))
        {
            /* 过滤掉机型不匹配的任务 */
            continue;
        }
        
        /* 初始化主任务控制结构 */
//        ptMainTaskCtrl->ptScpMainTaskConfig = &(s_atScpMainTaskConfig[wLoop]);
        ptMainTaskCtrl->ucTaskCtrl = ucTaskCtrl;
        ptMainTaskCtrl->ucIsValid = TRUE;
        ptMainTaskCtrl->ucRealTaskNum = 0;

//        ptTaskConfig = s_atScpMainTaskConfig[wLoop].atScpTaskConfig;
        ucErrorType = USP_OSS_SCP_ERROR_TYPE_IGNORE;

        SCP_DEBUG("(scp_initTCB) start init main task %s, priority = %d \r\n", 
                  ptMainTaskCtrl->ptScpMainTaskConfig->pcName,
                  ptMainTaskCtrl->ptScpMainTaskConfig->swPriority);

        /* 初始化一级任务控制结构 */
        for(wLoopInter = 0; \
            wLoopInter < SCP_MAX_TASK_NUM && NULL != ptTaskConfig[wLoopInter].pcName; \
            wLoopInter++, ucTaskCtrl++)
        {            
            if (ucErrorType > ptTaskConfig[wLoopInter].ucErrorType)
            {
                ucErrorType = ptTaskConfig[wLoopInter].ucErrorType;
            }

            if (NULL != ptTaskConfig[wLoopInter].taskEntry)
            {
                ptMainTaskCtrl->ucRealTaskNum++;   
            }

            s_pucScpTnoCtrl[ptTaskConfig[wLoopInter].tno] = ucTaskCtrl;
            s_ptScpTaskCtrl[ucTaskCtrl].ptScpTaskConfig = &(ptTaskConfig[wLoopInter]);
            s_ptScpTaskCtrl[ucTaskCtrl].ucIsValid = TRUE;
            s_ptScpTaskCtrl[ucTaskCtrl].msgQueue = USP_OSS_IPC_MQ_INVALID;
            s_ptScpTaskCtrl[ucTaskCtrl].ucKeepAliveStat = SCP_KEEPALIVE_STAT_LIVE;

            if (0 != ptTaskConfig[wLoopInter].wMaxMsgNum)
            {
                /* 创建消息队列 */
                dwRet = usp_oss_ipc_createMq(&(s_ptScpTaskCtrl[ucTaskCtrl].msgQueue), \
                                             ptTaskConfig[wLoopInter].wMaxMsgNum, \
                                             ptTaskConfig[wLoopInter].wMsgItemSize, \
                                             ptTaskConfig[wLoopInter].wMsgQueueKey);
                if (USP_SUCCESS != dwRet)
                {
                    if (USP_OSS_SCP_ERROR_TYPE_RESET == ptTaskConfig[wLoopInter].ucErrorType)
                    {
//                        SCP_LED_FLASH_ON(SCP_LED_APP_START_ERR);
                        sprintf((char *)s_aucScpLog, "Create %s msg queue error, code = %u", \
                                ptTaskConfig[wLoopInter].pcName, \
                                dwRet);
                        scp_reset();
                    }
                    else
                    {
//                        SCP_EXCEPT(dwRet, ptTaskConfig[wLoopInter].tno, 0, 0);
                    }

                    s_ptScpTaskCtrl[ucTaskCtrl].ucIsValid = FALSE;
                }   

                /* 初始化消息缓存*/
                usp_pub_adt_listInit(&(s_ptScpTaskCtrl[ucTaskCtrl].tScpMsgBuff.tListMsgBuff));
                s_ptScpTaskCtrl[ucTaskCtrl].tScpMsgBuff.dwSpace = SCP_MSG_BUF_MAX_SIZE;
            }

            SCP_DEBUG("(scp_initTCB) init task %s, StackDepth = %u, Priority = %d, tno = %u, TaskCtrl = %u, ErrorType = %u, IsKeepAlive = %u, IsStopMsg = %u, MaxMsgNum = %u, MsgItemSize = %u, MsgQueueKey = %u, IsValid = %u \r\n", \
                      ptTaskConfig[wLoopInter].pcName, \
                      ptTaskConfig[wLoopInter].wStackDepth, \
                      ptTaskConfig[wLoopInter].swPriority, \
                      ptTaskConfig[wLoopInter].tno, \
                      ucTaskCtrl, \
                      ptTaskConfig[wLoopInter].ucErrorType, \
                      ptTaskConfig[wLoopInter].ucIsKeepAlive, \
                      ptTaskConfig[wLoopInter].ucIsStopMsg, \
                      ptTaskConfig[wLoopInter].wMaxMsgNum, \
                      ptTaskConfig[wLoopInter].wMsgItemSize, \
                      ptTaskConfig[wLoopInter].wMsgQueueKey, \
                      s_ptScpTaskCtrl[ucTaskCtrl].ucIsValid);
            
        }

        ptMainTaskCtrl->ucErrorType = ucErrorType;
        ptMainTaskCtrl->ucTaskNum = wLoopInter;

        SCP_DEBUG("(scp_initTCB) end init main task %s, ErrorType = %u, TaskNum = %u \r\n", \
                  ptMainTaskCtrl->ptScpMainTaskConfig->pcName, \
                  ptMainTaskCtrl->ucErrorType, \
                  ptMainTaskCtrl->ucTaskNum);

        ptMainTaskCtrl++;
    }

    #ifdef SCP_MAX_CUST_TASK_NUM
    /* 初始化用户自定义任务控制信息 */    
    USP_OSS_IPC_CREATE_MUTEX(&ptTcbCtrl->custMutex, USP_OSS_SCP_CUST_MUTEX_KEY);
    ptTcbCtrl->dwCustAllocPos = (BYTE *)(s_ptScpTaskCtrl + wTaskNum)- (BYTE *)ptTcbCtrl;
    ptTcbCtrl->wCustAllocCur = 0;
    ptTcbCtrl->wCustTaskMax = SCP_MAX_CUST_TASK_NUM;
    
    for (wLoop = 0; wLoop < SCP_MAX_CUST_TASK_NUM; wLoop++, ucTaskCtrl++)
    {
        s_pucScpTnoCtrl[USP_CUST_TNO_START + wLoop] = ucTaskCtrl;
        s_ptScpTaskCtrl[ucTaskCtrl].ucIsValid = FALSE;
        s_ptScpTaskCtrl[ucTaskCtrl].msgQueue = USP_OSS_IPC_MQ_INVALID;
    }
    #endif

    return;
    #endif
}

/**************************************************************************
* 函数名称：scp_startTask
* 功能描述：启动应用任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_startTasks(VOID)
{
    #if 0
    WORD32              dwRet;
    WORD16              wLoop;
    T_ScpMainTaskCtrl   *ptMainTaskCtrl = s_ptScpMainTaskCtrl;

    SCP_DEBUG("(scp_startTasks) running ...... \r\n");

    /* 循环创建主任务并运行 */
    for (wLoop = 0; wLoop < s_wScpMainTaskNum; wLoop++, ptMainTaskCtrl++)
    {        
        if (0 == ptMainTaskCtrl->ucRealTaskNum)
        {
            /* 该任务是虚的，只是为了创建消息队列 */
            ptMainTaskCtrl->pid = 0;
            continue;
        }
        
        dwRet = usp_oss_vos_createProcess(scp_mainTaskEntry, \
                                          (VOID *)ptMainTaskCtrl, \
                                          (BYTE *)ptMainTaskCtrl->ptScpMainTaskConfig->pcName, \
                                          ptMainTaskCtrl->ptScpMainTaskConfig->swPriority, \
                                          &(ptMainTaskCtrl->pid));
        
        SCP_DEBUG("(scp_startTasks) create main task %s, pid = %u, ret = %u \r\n", 
                  ptMainTaskCtrl->ptScpMainTaskConfig->pcName,
                  ptMainTaskCtrl->pid,
                  dwRet);
        
        if (USP_SUCCESS != dwRet)
        {
            if (USP_OSS_SCP_ERROR_TYPE_RESET == ptMainTaskCtrl->ucErrorType)
            {
                //SCP_LED_FLASH_ON(SCP_LED_APP_START_ERR);
                sprintf((char *)s_aucScpLog, "Create %s process error, code = %u", \
                        ptMainTaskCtrl->ptScpMainTaskConfig->pcName, \
                        dwRet);
                scp_reset();
            }
            else
            {
              //  SCP_EXCEPT(dwRet, 0, 0, 0);
            }
            
            ptMainTaskCtrl->ucIsValid = FALSE;
        }
    }
    #endif
    return;
}

/**************************************************************************
* 函数名称：scp_poweron
* 功能描述：给应用任务上电
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno: 任务号
*           BYTE ucRound: 表示第几轮上电
*           WORD32 dwTimeOut: 超时时间(单位: 毫秒)
* 输出参数：无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_poweron(USP_OssScpTno tno, BYTE ucRound, WORD32 dwTimeOut)
{
    WORD32              dwRet;
    T_Msg               *ptSendMsg = (T_Msg *)s_aucScpSendMsgBuf;
    T_Msg               *ptRecvMsg = (T_Msg *)s_aucScpRecvMsgBuf;
    WORD32              dwLoop;
    
    /* 给应用任务上电 */
    ptSendMsg->mtype = 1;
    ptSendMsg->wSenderTno = USP_OSS_SCP_TNO;
    ptSendMsg->wMsgLen = sizeof(T_USPOssScpPowerOn);
    ptSendMsg->wMsgID = EV_USP_SCP_PowerOn;
    ((T_USPOssScpPowerOn *)(ptSendMsg + 1))->ucRound = ucRound;

    dwRet = usp_oss_scp_sendTaskMsg(tno, ptSendMsg, USP_OSS_IPC_NOWAIT);
                
    if (USP_SUCCESS != dwRet)
    {
        return dwRet;
    }
                    
    /* 发送上电消息成功, 等待响应 */
    for (dwLoop = 0; dwLoop < (dwTimeOut / 50); dwLoop++)
    {
        USP_OSS_VOS_SLEEP_MSEC(50);
        
        dwRet = usp_oss_scp_recvTaskMsg(USP_OSS_SCP_TNO, ptRecvMsg, \
                                        sizeof(s_aucScpRecvMsgBuf), USP_OSS_IPC_NOWAIT);
        if (USP_SUCCESS == dwRet && ptRecvMsg->wSenderTno == tno)
        {
            #if SCP_VERIFY_POWERON_ROUND
            if (((T_USPOssScpPowerOnAck *)(ptRecvMsg + 1))->ucRound != ucRound)
            {
                continue;
            }
            #endif
            
            if (EV_USP_SCP_PowerOnSuccess == ptRecvMsg->wMsgID)
            {
                /* 成功 */
                return USP_SUCCESS;
            }
            else if (EV_USP_SCP_PowerOnFailure == ptRecvMsg->wMsgID)
            {
                /* 失败 */
                return USP_OSS_SCP_ERR_RECV_POWERON_FAIL;
            }
        }
        
    }

    /* 超时 */
    return USP_OSS_SCP_ERR_RECV_POWERON_TIMEOUT;
}

/**************************************************************************
* 函数名称：scp_poweronTask
* 功能描述：给所有应用任务上电
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_poweronTasks(VOID)
{
    WORD32              dwRet;
    WORD32              dwTimeOut;
    WORD16              wLoop;
    BYTE                ucRound;    
    BYTE                ucTaskCtrlIndex;
    WORD16              wTry;
    USP_OssScpTno       tno;

    SCP_DEBUG("(scp_poweronTasks) running ...... \r\n");

    /* 设置重启时发送停止消息 */
    s_ucScpIsSendStopMsg = TRUE;    

    /* 一共需要进行三轮上电 */
    for (ucRound = 0; ucRound < 3; ucRound++)
    {
        #ifdef SCP_WAIT_POWERON_TIMER
        for (wLoop = 1; 0xFFFFFFFF != s_apdwScpPowerOnTnoSet[ucRound][wLoop]; wLoop++)
        {
            dwTimeOut = SCP_WAIT_POWERON_TIMER;
        #else
        for (wLoop = 1; 0xFFFFFFFF != s_apdwScpPowerOnTnoSet[ucRound][wLoop]; wLoop += 2)
        {
            dwTimeOut = s_apdwScpPowerOnTnoSet[ucRound][wLoop + 1];
        #endif
            tno = (USP_OssScpTno)s_apdwScpPowerOnTnoSet[ucRound][wLoop];            
            
            ucTaskCtrlIndex = s_pucScpTnoCtrl[tno];

            if (SCP_INVALID_TASK_CTRL_INDEX == ucTaskCtrlIndex)
            {
                //SCP_EXCEPT(USP_OSS_SCP_ERR_INVALID_POWERON_TNO, \
                 //          tno, 0, 0);
                continue;
            }

            if (FALSE == s_ptScpTaskCtrl[ucTaskCtrlIndex].ucIsValid)
            {
               // SCP_EXCEPT(USP_OSS_SCP_ERR_INVALID_TASK, \
                 //          tno, 0, 0);
                continue;
            }

            for (wTry = 0; wTry < SCP_WAIT_POWERON_MAXTRY; wTry++)
            {        
                SCP_DEBUG("(scp_poweronTasks) send power on msg to %s(%u) ucRound = %u, wTry = %u, dwTimeOut = %u(ms) \r\n", 
                          s_ptScpTaskCtrl[ucTaskCtrlIndex].ptScpTaskConfig->pcName, \
                          tno, ucRound, wTry, dwTimeOut);
                    
                dwRet = scp_poweron(tno, ucRound, dwTimeOut);
                if (USP_SUCCESS == dwRet)
                {
                    /* 上电成功 */
                    s_ptScpTaskCtrl[ucTaskCtrlIndex].ucIsValid = TRUE;
                    SCP_DEBUG("((scp_poweronTasks) power on %s success \r\n", \
                              s_ptScpTaskCtrl[ucTaskCtrlIndex].ptScpTaskConfig->pcName);

                    break;
                }
                else
                {
                    SCP_DEBUG("((scp_poweronTasks) power on %s fail, dwRet = %u \r\n", \
                              s_ptScpTaskCtrl[ucTaskCtrlIndex].ptScpTaskConfig->pcName, \
                              dwRet);
                    //SCP_EXCEPT(dwRet, s_ptScpTaskCtrl[ucTaskCtrlIndex].ptScpTaskConfig->tno, dwRet, ucRound);
                }
            }  
                
            if (SCP_WAIT_POWERON_MAXTRY == wTry)
            {
                /* 上电失败 */
                if (USP_OSS_SCP_ERROR_TYPE_RESET == s_ptScpTaskCtrl[ucTaskCtrlIndex].ptScpTaskConfig->ucErrorType)
                {
                   // SCP_LED_FLASH_ON(SCP_LED_APP_START_ERR);
                    sprintf((char *)s_aucScpLog, "PowerOn %s task error, code = %u", \
                            s_ptScpTaskCtrl[ucTaskCtrlIndex].ptScpTaskConfig->pcName, \
                            dwRet);
                    scp_reset();
                }
                else
                {
                    //SCP_EXCEPT(USP_OSS_SCP_ERR_POWERON, tno, dwRet, 0);
                }
                s_ptScpTaskCtrl[ucTaskCtrlIndex].ucIsValid = FALSE;
                s_ptScpTaskCtrl[ucTaskCtrlIndex].ucKeepAliveStat = SCP_KEEPALIVE_STAT_DEAD;
            }   
        }    
    }
    
    return;
}

#if USP_OAM_CLI_USE

/**************************************************************************
* 函数名称：scp_showTask
* 功能描述：显示应用任务运行信息
* 访问的表：无
* 修改的表：无
* 输入参数：USP_CliCommandResp resp: 命令响应
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
#if 0
static WORD32 scp_showTask(USP_CliCommandResp resp)
{
    BYTE                *pucInfo = NULL;
    T_ScpMainTaskCtrl   *ptMainTaskCtrl = s_ptScpMainTaskCtrl;
    T_ScpTaskCtrl       *ptTaskCtrl;
    WORD16              wLoop;
    WORD16              wLoopInter;
    BYTE                aucMqKey[8];
    BYTE                *pucKeepAliveStat = NULL;
    
    usp_cli_getRespInfo(resp, &pucInfo); 
    strcpy((char *)pucInfo, "\r\nPlease view the output form the monitor interface!");

    for (wLoop = 0; wLoop < s_wScpMainTaskNum; wLoop++, ptMainTaskCtrl++)
    {
        /* 主任务信息 */
        SCP_INFO("MainTask: %s, Valid: %s, Err:%s \r\n", \
                 ptMainTaskCtrl->ptScpMainTaskConfig->pcName,
                 ptMainTaskCtrl->ucIsValid ? "TRUE" : "FALSE",
                 s_apucScpErrorType[ptMainTaskCtrl->ucErrorType]);    

        ptTaskCtrl = &(s_ptScpTaskCtrl[ptMainTaskCtrl->ucTaskCtrl]);
        for (wLoopInter = 0; wLoopInter < ptMainTaskCtrl->ucTaskNum; wLoopInter++, ptTaskCtrl++)
        {
            /* 一级任务信息 */
            if (0 == ptTaskCtrl->ptScpTaskConfig->wMaxMsgNum)
            {
                aucMqKey[0] = '\0';
            }
            else
            {
                sprintf((char *)aucMqKey, "0x%x", ptTaskCtrl->ptScpTaskConfig->wMsgQueueKey);
            }

            if (TRUE == ptTaskCtrl->ptScpTaskConfig->ucIsKeepAlive)
            {
                if (SCP_KEEPALIVE_STAT_LIVE == ptTaskCtrl->ucKeepAliveStat)
                {
                    pucKeepAliveStat = (BYTE *)"LIVE";
                }
                else
                {
                    pucKeepAliveStat = (BYTE *)"DEAD";
                }
            }
            else
            {
                pucKeepAliveStat = (BYTE *)"";
            }

            SCP_INFO("\tTask: %s, Valid: %s, Err: %s, MqKey: %s, Tno: %u, KA_Stat: %s, Run_Stat: %u, MsgBuf: %u \r\n", \
                     ptTaskCtrl->ptScpTaskConfig->pcName, \
                     ptTaskCtrl->ucIsValid ? "TRUE" : "FALSE", \
                     s_apucScpErrorType[ptTaskCtrl->ptScpTaskConfig->ucErrorType], \
                     aucMqKey, \
                     ptTaskCtrl->ptScpTaskConfig->tno, \
                     (char *)pucKeepAliveStat, \
                     ptTaskCtrl->wRunStatus, \
                     ptTaskCtrl->ucIsValid ? usp_pub_adt_listCount(&(ptTaskCtrl->tScpMsgBuff.tListMsgBuff)) : 0);
        }
    }

    return USP_SUCCESS;
}
#endif
/**************************************************************************
* 函数名称：scp_cmdEntry
* 功能描述：CLI命令处理入口
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 命令消息
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_cmdEntry(T_Msg *ptMsg)
{
    #if 0
    T_Msg                   *ptSendMsg;
    USP_CliCommandParam     param;
    USP_CliCommandResp      resp;
    WORD32                  dwRet = USP_SUCCESS;
    WORD16                  wCmd;

    param = (USP_CliCommandParam)(ptMsg + 1);
    ptSendMsg = (T_Msg *)s_aucScpSendMsgBuf;
    resp = (USP_CliCommandResp)(ptSendMsg + 1);

    usp_cli_initResp(param, resp);
    ptSendMsg->mtype = 1;
    ptSendMsg->wSenderTno = USP_OSS_SCP_TNO;
    ptSendMsg->wReceiverTno = USP_OAM_CLI_TNO;
    ptSendMsg->wMsgID = EV_USP_CLI_Cmd_Response;

    usp_cli_getCmd(param, &wCmd);
    
    switch (wCmd)
    {
        case USP_CLI_CMDID_OAM_CLI_SHOW_TASK:
            dwRet = scp_showTask(resp);
            break;

        default:
        {
            dwRet = USP_OSS_SCP_ERR_CLI_CMD;
            break;
        }
    }

    if (USP_SUCCESS != dwRet)
    {
        return dwRet;
    }

    /* 发送应答消息 */
    usp_cli_getRespSize(resp, &(ptSendMsg->wMsgLen));

    return usp_oss_scp_sendTaskMsg(USP_OAM_CLI_TNO, ptSendMsg, USP_OSS_IPC_NOWAIT);
    #endif
}

#endif  /* USP_OAM_CLI_USE */

/**************************************************************************
* 函数名称：scp_keepAlive
* 功能描述：通过向应用任务发送握手消息来检测任务的活动状态
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_keepAlive(VOID)
{
    WORD16              wLoop;
    WORD16              wLoopInter;
    T_ScpMainTaskCtrl   *ptMainTaskCtrl = s_ptScpMainTaskCtrl;
    T_ScpTaskCtrl       *ptTaskCtrl;  
    T_Msg               *ptMsg = (T_Msg *)s_aucScpSendMsgBuf;
    WORD32              dwRet;

    SCP_DEBUG("(scp_keepAlive) running ...... \r\n");

    /* 发送握手消息 */
    ptMsg->mtype = 1;
    ptMsg->wSenderTno = USP_OSS_SCP_TNO;
    ptMsg->wMsgLen = 0;
    ptMsg->wMsgID = EV_USP_SCP_KeepAlive;
        
    for (wLoop = 0; wLoop < s_wScpMainTaskNum; wLoop++, ptMainTaskCtrl++)
    {
        if (FALSE == ptMainTaskCtrl->ucIsValid)
        {
            continue;
        }
        
        ptTaskCtrl = &(s_ptScpTaskCtrl[ptMainTaskCtrl->ucTaskCtrl]);
        for (wLoopInter = 0; wLoopInter < ptMainTaskCtrl->ucTaskNum; wLoopInter++, ptTaskCtrl++)
        {
            if (TRUE == ptTaskCtrl->ucIsValid && TRUE == ptTaskCtrl->ptScpTaskConfig->ucIsKeepAlive)
            {
                if (0 == s_aucScpKeepLive[ptTaskCtrl->ptScpTaskConfig->tno])
                {
                    /* 多次握手均没有应答, 任务已经不再存活 */     
                    ptTaskCtrl->ucKeepAliveStat = SCP_KEEPALIVE_STAT_DEAD;

                    SCP_DEBUG("(scp_keepAlive) %s keeplive fail \r\n", \
                              ptTaskCtrl->ptScpTaskConfig->pcName);

                    if (USP_OSS_SCP_ERROR_TYPE_RESET == ptTaskCtrl->ptScpTaskConfig->ucErrorType)        
                    {
                        /* 需要重启系统 */
                        //SCP_LED_FLASH_ON(SCP_LED_ERR_FATAL);
                        sprintf((char *)s_aucScpLog, "%s task dead", \
                                ptTaskCtrl->ptScpTaskConfig->pcName);
                        usp_oss_scp_setStartupReason(USP_OSS_SCP_STARTUP_TASK_DEAD);
                        scp_reset();
                    }
                    else
                    {                        
                        /* 记录异常 */
                        //SCP_EXCEPT(USP_OSS_SCP_ERR_KEEPLIVE, \
                         //          ptTaskCtrl->ptScpTaskConfig->tno, \
                                   0, 0);
                    }

                    /* 恢复原值, 下次可以继续检测其活动状态 */
                    s_aucScpKeepLive[ptTaskCtrl->ptScpTaskConfig->tno] = SCP_WAIT_KEEPALIVE_MAXTRY;
                    continue;
                }              
                
                dwRet = usp_oss_scp_sendTaskMsg(ptTaskCtrl->ptScpTaskConfig->tno, \
                                                ptMsg, USP_OSS_IPC_NOWAIT);

                SCP_DEBUG("(scp_keepAlive) send keepalive msg to %s, ret = %u \r\n",
                          ptTaskCtrl->ptScpTaskConfig->pcName,
                          dwRet);
                
                if (USP_SUCCESS != dwRet)
                {
                    //SCP_EXCEPT(USP_OSS_SCP_ERR_SEND_KEEPALIVE, dwRet, \
                     //          ptTaskCtrl->ptScpTaskConfig->tno, 0);
                }
                s_aucScpKeepLive[ptTaskCtrl->ptScpTaskConfig->tno]--;
            }
        }
    }
    
    return;
}

#if USP_IS_DISTRIBUTED
/**************************************************************************
* 函数名称：scp_ibKeepAlive
* 功能描述：通过板间SCP握手消息来检测子板的活动状态
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptRecvMsg: 输入消息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/04/19    V1.0       高峰        创建
**************************************************************************/
static VOID scp_ibKeepAlive(T_Msg *ptRecvMsg)
{
    static BYTE             ucKeepAliveTry = SCP_IB_WAIT_KEEPALIVE_MAXTRY;
    T_Msg                   *ptSendMsg = (T_Msg *)s_aucScpSendMsgBuf;
    T_ScpIbKeepAliveAck     *ptIbKeepAliveAck= NULL;
    WORD32                  dwMyTime;
    time_t                  setTime;

    SCP_DEBUG("(scp_ibKeepAlive) running. wMsgID = 0x%x, ucKeepAliveTry = %u \r\n", \
              ptRecvMsg->wMsgID, ucKeepAliveTry);

    if (EV_USP_SCP_TimerIbKeepAlive == ptRecvMsg->wMsgID)
    {
        /* 握手定时器消息 */
        #if USP_MY_DEVID == USP_RB_DEVID
        /* 数字板 */
        if (0 == --ucKeepAliveTry)
        {
            //SCP_EXCEPT(USP_OSS_SCP_ERR_IB_KEEPLIVE, 0, 0, 0);
            ucKeepAliveTry = SCP_IB_WAIT_KEEPALIVE_MAXTRY;      
        }
        #else
        /* 射频板 */
        if (0 == --ucKeepAliveTry)
        {
           // SCP_EXCEPT(USP_OSS_SCP_ERR_IB_KEEPLIVE, 0, 0, 0);
            ucKeepAliveTry = SCP_IB_WAIT_KEEPALIVE_MAXTRY;      
        }
        ptSendMsg->mtype = 1;
        ptSendMsg->wSenderTno = USP_OSS_SCP_TNO;
        ptSendMsg->wReceiverTno = usp_oss_scp_getTno(USP_RB_DEVID, usp_oss_scp_getSubTno(USP_OSS_SCP_TNO));
        ptSendMsg->wMsgID = EV_USP_SCP_IbKeepAlive;
        ptSendMsg->wMsgLen = 0;
        usp_oss_scp_sendTaskMsg(ptSendMsg->wReceiverTno, ptSendMsg, USP_OSS_IPC_NOWAIT);
        #endif

        usp_oss_timer_setRelTimer(EV_USP_SCP_TimerIbKeepAlive, \
                                  SCP_IB_KEEPALIVE_TIMER, \
                                  USP_OSS_SCP_TNO, \
                                  NULL);
    }
    else if (EV_USP_SCP_IbKeepAlive == ptRecvMsg->wMsgID)
    {    
        /* 握手请求消息 */
        ucKeepAliveTry = SCP_IB_WAIT_KEEPALIVE_MAXTRY;
        
        ptSendMsg->mtype = 1;
        ptSendMsg->wSenderTno = USP_OSS_SCP_TNO;
        ptSendMsg->wReceiverTno = ptRecvMsg->wSenderTno;
        ptSendMsg->wMsgID = EV_USP_SCP_IbKeepAliveAck;
        ptSendMsg->wMsgLen = sizeof(T_ScpIbKeepAliveAck);
        ptIbKeepAliveAck = (T_ScpIbKeepAliveAck *)(ptSendMsg + 1);
        ptIbKeepAliveAck->dwTime = time(NULL);
        usp_oss_scp_sendTaskMsg(ptSendMsg->wReceiverTno, ptSendMsg, USP_OSS_IPC_NOWAIT);
    }
    else 
    {
        /* 握手应答消息 */
        ucKeepAliveTry = SCP_IB_WAIT_KEEPALIVE_MAXTRY;

        ptIbKeepAliveAck = (T_ScpIbKeepAliveAck *)(ptRecvMsg + 1);
        dwMyTime = time(NULL);
        SCP_DEBUG("(scp_ibKeepAlive) dwMyTime = %u, dwTime = %u \r\n", \
                  dwMyTime, ptIbKeepAliveAck->dwTime);

        if ((dwMyTime + 60) < ptIbKeepAliveAck->dwTime \
         || dwMyTime > (ptIbKeepAliveAck->dwTime + 60))
        {            
            setTime = ptIbKeepAliveAck->dwTime;
            stime(&setTime);
            SCP_LOG_INFO("InterBoard KeepAlive update time!");
        }        
    }

    return;
}
#endif  /* USP_IS_DISTRIBUTED */

/**************************************************************************
* 函数名称：usp_scp_serviceEntry
* 功能描述：系统控制服务任务入口函数
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTask task: 任务管理结构
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_scp_serviceEntry(USP_OssScpTask task)
{    
    #if 0
    T_Msg           *ptRecvMsg = (T_Msg *)s_aucScpRecvMsgBuf;
    T_Msg           *ptSendMsg = (T_Msg *)s_aucScpSendMsgBuf;
    WORD32          dwRet;
    USP_OssScpTno   tno;
    WORD32          dwSetDefault = FALSE;

    SCP_DEBUG("(usp_scp_serviceEntry) running ...... \r\n");

    /* 循环接收消息, 只有收到系统上电消息后才开始工作 */
    for (; ;)
    {
        dwRet = usp_oss_scp_recvTaskMsg(USP_OSS_SCP_TNO, s_aucScpRecvMsgBuf, \
                                        sizeof(s_aucScpRecvMsgBuf), USP_OSS_IPC_FOREVERWAIT);
        if (USP_SUCCESS == dwRet && EV_USP_SCP_PowerOn == ptRecvMsg->wMsgID)
        {
            break;
        }
    }

    /* 上电 */
    scp_poweronTasks();

    /* 上电完成，清空系统启动标志 */
    usp_oss_scp_setStartupReason(USP_OSS_SCP_STARTUP_NORMAL);

    #if USP_OSS_SYSDATA_USE
    if (TRUE == g_tUSPPubConfig.ucIsSetDefault)
    {
        /* 清空恢复出厂标志 */
        dwRet = usp_oss_sysdata_write((BYTE *)USP_PUB_SET_DEFAULT_ITEM, (BYTE *)&dwSetDefault, sizeof(dwSetDefault));
        if (USP_SUCCESS != dwRet)
        {
            //SCP_EXCEPT(dwRet, 0, 0, 0);
        }
    }
    #endif

    /* 启动NTP服务器 */
    #if SCP_NTP_SERVER_USE
    SCP_DEBUG("(usp_scp_serviceEntry) start ntpserver \r\n");
    system("/zxris/tools/ntpstools.bin &");
    #endif
        
    /* 启动WEB服务器BOA */
    #if USP_OAM_LMT_USE || SCP_LMT_USE    
    SCP_DEBUG("(usp_scp_serviceEntry) start boa \r\n");
    system("ln -s /zxris/lib/libusp.so.1 /lib/libusp.so.1");
    system("boa");
    #endif

    #if USP_OAM_CLI_USE
    SCP_DEBUG("Application poweron finish! \r\n");
    usp_cli_stopBufPrintf();
    #endif

    SCP_TERMINAL_PRINT("Application startup success! \r\n");

    //SCP_LED_FLASH_ON(SCP_LED_RUNNING);

    /* 初始化KeepAlive状态数组 */
    memset(s_aucScpKeepLive, SCP_WAIT_KEEPALIVE_MAXTRY, sizeof(s_aucScpKeepLive));

    /* 设置定时器 */
    usp_oss_timer_setRelTimer(EV_USP_SCP_TimerKeepAlive, SCP_KEEPALIVE_TIMER, \
                              USP_OSS_SCP_TNO, NULL);

    #if USP_IS_DISTRIBUTED
    usp_oss_timer_setRelTimer(EV_USP_SCP_TimerIbKeepAlive, SCP_IB_KEEPALIVE_TIMER, \
                              USP_OSS_SCP_TNO, NULL);
    #endif
    
    #if SCP_NTP_USE
    usp_oss_timer_setRelTimer(EV_USP_SCP_TimerNtpUpdate, s_tScpNtpCfg.dwSyncPeriod * 60 * 1000, \
                              USP_OSS_SCP_TNO, NULL);

    SCP_ALARM_NTP;
    #endif

    #if USP_OS_LINUX
    /* 设置性能统计保存定时器 */
    usp_oss_timer_setRelTimer(EV_USP_SCP_PspSave, SCP_PSP_SAVE_TIMER, \
                              USP_OSS_SCP_TNO, NULL);
    #endif
    
    /* 循环接收消息进行处理 */
    for (; ;)
    {
        dwRet = usp_oss_scp_recvTaskMsg(USP_OSS_SCP_TNO, s_aucScpRecvMsgBuf, \
                                        sizeof(s_aucScpRecvMsgBuf), USP_OSS_IPC_FOREVERWAIT);
        if (USP_SUCCESS != dwRet)
        {
            /* 接收消息错误,记录异常 */
            //SCP_EXCEPT(USP_OSS_SCP_ERR_RECV_SERVICE_MSG, dwRet, 0, 0);
            continue;
        }

        SCP_DEBUG("(usp_scp_serviceEntry) recv msg, MsgID = %u \r\n", ptRecvMsg->wMsgID);

        /* 根据不同的消息分别进行处理 */
        switch (ptRecvMsg->wMsgID)
        {
            case EV_USP_SCP_TimerKeepAlive:
            {
                /* 与应用握手,检测其是否存活 */                
                scp_keepAlive();
                usp_oss_timer_setRelTimer(EV_USP_SCP_TimerKeepAlive, \
                                          SCP_KEEPALIVE_TIMER, \
                                          USP_OSS_SCP_TNO, \
                                          NULL);
                break;
            }

            case EV_USP_SCP_KeepAliveAck:
            {
                /* 更新KeepAlive状态 */
                tno = *((USP_OssScpTno *)(ptRecvMsg + 1));
                s_aucScpKeepLive[tno] = SCP_WAIT_KEEPALIVE_MAXTRY;
                s_ptScpTaskCtrl[s_pucScpTnoCtrl[tno]].ucKeepAliveStat = SCP_KEEPALIVE_STAT_LIVE;

                SCP_DEBUG("(usp_scp_serviceEntry) recv keepalive ack from %s \r\n",
                          s_ptScpTaskCtrl[s_pucScpTnoCtrl[tno]].ptScpTaskConfig->pcName);
                
                break;
            }
            
            #if SCP_NTP_USE
            case EV_USP_SCP_TimerNtpUpdate:
            {
                scp_updateNtp(FALSE, FALSE);
                break;
            }
            
            case EV_USP_OAM_CMP_CfgParaChg:
            {
                scp_updateNtp(FALSE, TRUE);
                break;            
            }
            #endif  /* SCP_NTP_USE */

            #if USP_OAM_CLI_USE
            case EV_USP_CLI_Cmd_Request:
            {
                /* 响应CLI命令 */
                dwRet = scp_cmdEntry(ptRecvMsg);

                SCP_DEBUG("(usp_scp_serviceEntry) process cli cmd ret = 0x%x \r\n", dwRet);

                if (USP_SUCCESS != dwRet)
                {
                   // SCP_EXCEPT(USP_OSS_SCP_ERR_CLI_PROCESS, dwRet, 0, 0);
                }                
                break;
            }
            #endif  /* USP_OAM_CLI_USE */

            case EV_USP_SCP_Reset:
            {
                /* 重启设备 */                
                ptSendMsg->mtype = ptRecvMsg->mtype;
                ptSendMsg->wSenderTno = USP_OSS_SCP_TNO;
                ptSendMsg->wReceiverTno = ptRecvMsg->wSenderTno;
                ptSendMsg->wMsgID = EV_USP_SCP_ResetAck;
                ptSendMsg->wMsgLen = 0;
                ptSendMsg->wMsgSequence = ptRecvMsg->wMsgSequence;
                dwRet = usp_oss_scp_sendTaskMsg(ptSendMsg->wReceiverTno, ptSendMsg, USP_OSS_IPC_FOREVERWAIT);
                sprintf((char *)s_aucScpLog, "Receive EV_USP_SCP_Reset Msg from %u", ptSendMsg->wReceiverTno);

                scp_reset();                             
                break;
            }

            case EV_USP_SCP_SetTime:
            {
                /* 设置时间 */
                ptSendMsg->mtype = ptRecvMsg->mtype;
                ptSendMsg->wSenderTno = USP_OSS_SCP_TNO;
                ptSendMsg->wReceiverTno = ptRecvMsg->wSenderTno;
                ptSendMsg->wMsgID = EV_USP_SCP_SetTimeAck;
                ptSendMsg->wMsgLen = sizeof(WORD32);
                ptSendMsg->wMsgSequence = ptRecvMsg->wMsgSequence;
                *((WORD32 *)(ptSendMsg + 1)) = scp_setTime(*((WORD32 *)(ptRecvMsg + 1)));                
                dwRet = usp_oss_scp_sendTaskMsg(ptSendMsg->wReceiverTno, ptSendMsg, USP_OSS_IPC_FOREVERWAIT);                
                break;
            }

            #if USP_IS_DISTRIBUTED
            case EV_USP_SCP_TimerIbKeepAlive:
            case EV_USP_SCP_IbKeepAlive:
            case EV_USP_SCP_IbKeepAliveAck:
            {
                /* 板间SCP握手 */
                scp_ibKeepAlive(ptRecvMsg);
                break;
            }
            #endif

            case EV_USP_SCP_PspSave:
            {
                /* 持久化性能统计信息 */
                scp_pspSave();
                usp_oss_timer_setRelTimer(EV_USP_SCP_PspSave, SCP_PSP_SAVE_TIMER, \
                                          USP_OSS_SCP_TNO, NULL);
                break;
            }
                       
            default:
            {
                /* 未知的消息 */
                //SCP_EXCEPT(USP_OSS_SCP_ERR_RECV_UNKNOW_MSG, ptRecvMsg->wMsgID, 0, 0);
                break;            
            }
        }        
    }
    #endif
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：scp_mainTaskEntry
* 功能描述：主任务入口
* 访问的表：无
* 修改的表：无
* 输入参数：VOID *arg: 主任务控制信息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/04/07    V1.0       高峰        创建
**************************************************************************/
static VOID scp_mainTaskEntry(VOID *arg)
{
    #if 0
    T_ScpMainTaskCtrl   *ptMainTaskCtrl = (T_ScpMainTaskCtrl *)arg;
    WORD32              dwRet;
    WORD16              wLoop;
    WORD16              wTaskNum = 0;
    T_ScpTaskCtrl       *ptTaskCtrl = &(s_ptScpTaskCtrl[ptMainTaskCtrl->ucTaskCtrl]);

    SCP_DEBUG("(scp_mainTaskEntry) start main task entry, Name = %s \r\n",
              ptMainTaskCtrl->ptScpMainTaskConfig->pcName);
    
    if (0 == ptMainTaskCtrl->ucTaskNum)
    {
        return;
    }

    #if USP_OS_LINUX
    wTaskNum = ptMainTaskCtrl->ucTaskNum - 1;
    #endif 

    #if USP_OS_FREERTOS
    wTaskNum = ptMainTaskCtrl->ucTaskNum;
    #endif

    /* 对每个一级任务创建一个运行线程 */    
    for (wLoop = 0; wLoop < wTaskNum; wLoop++, ptTaskCtrl++)
    {
        if (FALSE == ptTaskCtrl->ucIsValid \
         || NULL == ptTaskCtrl->ptScpTaskConfig->taskEntry)
        {
            continue;
        }

        dwRet = usp_oss_vos_createThread(scp_taskEntry, \
                                         (VOID *)ptTaskCtrl, \
                                         (BYTE *)ptTaskCtrl->ptScpTaskConfig->pcName, \
                                         ptTaskCtrl->ptScpTaskConfig->wStackDepth, \
                                         ptTaskCtrl->ptScpTaskConfig->swPriority, \
                                         NULL);

        SCP_DEBUG("(scp_mainTaskEntry) create task %s, ret = %u \r\n", \
                  ptTaskCtrl->ptScpTaskConfig->pcName, \
                  dwRet);

        if (USP_SUCCESS != dwRet)
        {
            if (USP_OSS_SCP_ERROR_TYPE_RESET == ptTaskCtrl->ptScpTaskConfig->ucErrorType)
            {
                //SCP_LED_FLASH_ON(SCP_LED_APP_START_ERR);
                sprintf((char *)s_aucScpLog, "Create %s task error, code = %u", \
                        ptTaskCtrl->ptScpTaskConfig->pcName, \
                        dwRet);
                scp_reset();
            }
            else
            {
                //SCP_EXCEPT(dwRet, ptTaskCtrl->ptScpTaskConfig->tno, 0, 0);
            }
            
            ptTaskCtrl->ucIsValid = FALSE;
        }
    }

    #if USP_OS_LINUX
    if (NULL != ptTaskCtrl->ptScpTaskConfig->taskEntry)
    {
        /* 对于最后一个一级任务, 回调一级任务入口函数即可, 无需再创建新的线程 */
        SCP_DEBUG("(scp_mainTaskEntry) create task %s \r\n", ptTaskCtrl->ptScpTaskConfig->pcName);
    
        scp_taskEntry(ptTaskCtrl); 
    }
    #endif  /* USP_OS_LINUX */
    
    #endif
    return;
}

/**************************************************************************
* 函数名称：scp_upperTaskEntry
* 功能描述：一级任务入口
* 访问的表：无
* 修改的表：无
* 输入参数：VOID *arg: 一级任务控制信息
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/04/07    V1.0       高峰        创建
**************************************************************************/
static VOID scp_taskEntry(VOID *arg)
{
    WORD32             dwRet = USP_SUCCESS;
    T_ScpTaskCtrl      *ptUpperTaskCtrl = (T_ScpTaskCtrl *)arg;
    
    SCP_DEBUG("(scp_taskEntry) start task entry, Name = %s \r\n", \
              ptUpperTaskCtrl->ptScpTaskConfig->pcName);
    
    dwRet = (*(ptUpperTaskCtrl->ptScpTaskConfig->taskEntry))(ptUpperTaskCtrl);

   // SCP_EXCEPT(USP_OSS_SCP_ERR_INVALID_TASK, ptUpperTaskCtrl->ptScpTaskConfig->tno, dwRet, 0);

    ptUpperTaskCtrl->ucIsValid = FALSE;    
    
    return;
}

/**************************************************************************
* 函数名称：scp_reset
* 功能描述：重新启动设备，首先发送EV_S_StopProcess消息，然后等待20秒后重启。
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/04/07    V1.0       高峰        创建
**************************************************************************/
static VOID scp_reset(VOID)
{
    #if 0
    WORD16              wLoop;
    WORD16              wLoopInter;
    T_ScpMainTaskCtrl   *ptMainTaskCtrl = s_ptScpMainTaskCtrl;
    T_ScpTaskCtrl       *ptTaskCtrl;  
    T_Msg               *ptMsg;

    SCP_TERMINAL_PRINT("System will restart after 20 seconds! \r\n");

    /* 记录日志 */
    SCP_LOG_RESET(s_aucScpLog);

    if (TRUE == s_ucScpIsSendStopMsg)
    {
        ptMsg = (T_Msg *)s_aucScpSendMsgBuf;
        ptMsg->mtype = 1;
        ptMsg->wSenderTno = USP_OSS_SCP_TNO;
        ptMsg->wMsgLen = 0;
        ptMsg->wMsgID = EV_USP_SCP_StopProcess;
        
        /* 发送EV_USP_SCP_StopProcess消息 */
        for (wLoop = 0; wLoop < s_wScpMainTaskNum; wLoop++, ptMainTaskCtrl++)
        {
            if (FALSE == ptMainTaskCtrl->ucIsValid)
            {
                continue;
            }
            
            ptTaskCtrl = &(s_ptScpTaskCtrl[ptMainTaskCtrl->ucTaskCtrl]);
            for (wLoopInter = 0; \
                 wLoopInter < ptMainTaskCtrl->ucTaskNum; \
                 wLoopInter++, ptTaskCtrl++)
            {
                if (TRUE == ptTaskCtrl->ucIsValid \
                 && TRUE == ptTaskCtrl->ptScpTaskConfig->ucIsStopMsg)
                {
                    usp_oss_scp_sendTaskMsg(ptTaskCtrl->ptScpTaskConfig->tno, \
                                            ptMsg, USP_OSS_IPC_NOWAIT);
                }
            }
        }
    }

    /* 重启设备 */
    for (; ;)
    {
        #if USP_OS_LINUX
        USP_OSS_VOS_SLEEP_SEC(20);
        #endif

        #if USP_OS_FREERTOS
        for (wLoop = 0; wLoop < (10 * 150); wLoop++)
        {
            usp_oss_vos_usleep(1000);
        }
        #endif
        
        usp_oss_vos_reset();
    }
    
    //return;
    #endif
}

/**************************************************************************
* 函数名称：usp_scp_sendTaskMsg
* 功能描述：发送消息给指定的任务
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno：任务号
*           VOID *msg：消息缓冲区指针
*           WORD16 wFlag：发送选项
* 输出参数：无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_sendTaskMsg(USP_OssScpTno tno, VOID *msg, WORD32 dwFlag)
{
    #if 0
    WORD32              dwRet = USP_SUCCESS;
    T_Msg               *ptMsg = (T_Msg *)msg;
    USP_OssScpTno       dstTno = tno;
    WORD16              wRelayMagic = 0;
    BYTE                ucTaskCtrlIndex;    

    if (NULL == msg)
    {
        return USP_OSS_SCP_ERR_NULL_POINTER;
    }

    if (SCP_MAX_TNO <= tno)
    {
        return USP_OSS_SCP_ERR_INVALID_TNO;
    }

    ucTaskCtrlIndex = s_pucScpTnoCtrl[tno];        
    if (SCP_INVALID_TASK_CTRL_INDEX == ucTaskCtrlIndex)
    {
        if (usp_oss_scp_getMinTno(USP_MY_DEVID) <= tno \
         && usp_oss_scp_getMaxTno(USP_MY_DEVID) >= tno)
        {
            return USP_OSS_SCP_ERR_INVALID_TNO;
        }
        
        #if USP_IS_DISTRIBUTED        
        dstTno = USP_COMM_TNO;
        wRelayMagic = USP_PUB_MSG_RELAY;
        ucTaskCtrlIndex = s_pucScpTnoCtrl[USP_COMM_TNO];
        #else
        return USP_OSS_SCP_ERR_INVALID_TNO;
        #endif
    }
    
    if (FALSE == s_ptScpTaskCtrl[ucTaskCtrlIndex].ucIsValid)
    {
        return USP_OSS_SCP_ERR_INVALID_TASK;
    }

    if (USP_OSS_IPC_MQ_INVALID == s_ptScpTaskCtrl[ucTaskCtrlIndex].msgQueue)
    {
        return USP_OSS_SCP_ERR_INVALID_MQ;
    }

    /* 发送消息 */    
    ptMsg->wDstTno = dstTno;
    ptMsg->wRelayMagic = wRelayMagic;
    dwRet = usp_oss_ipc_sendMsg(s_ptScpTaskCtrl[ucTaskCtrlIndex].msgQueue, msg, dwFlag);
    if (USP_SUCCESS == dwRet)
    {
        usp_oss_trace(USP_OSS_ST_SND, s_aucScpTraceSendDesc, ptMsg);
    }
    
    return dwRet;
    #endif
}

/**************************************************************************
* 函数名称：scp_isExpectMsg
* 功能描述：判断是否是希望接收到的消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_Msg *ptMsg: 要比较的消息
*           T_Msg *aptExpectMsg[]: 期望消息数组
* 输出参数：无
* 返 回 值：TRUE: 要比较的消息是期望消息; FALSE: 要比较的消息不是期望消息
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/06    V1.0       高峰        创建
**************************************************************************/
static BOOLEAN scp_isExpectMsg(T_Msg *ptMsg, T_Msg *aptExpectMsg[])
{
    WORD32      dwLoop;
    
    if (NULL == aptExpectMsg)
    {
        return TRUE;
    }

    for (dwLoop = 0; NULL != aptExpectMsg[dwLoop]; dwLoop++)
    {
        if ((0xFF   == aptExpectMsg[dwLoop]->ucLinkType   || ptMsg->ucLinkType   == aptExpectMsg[dwLoop]->ucLinkType)  \
         && (0xFF   == aptExpectMsg[dwLoop]->ucLinkIndex  || ptMsg->ucLinkIndex  == aptExpectMsg[dwLoop]->ucLinkIndex) \
         && (0xFFFF == aptExpectMsg[dwLoop]->wSenderTno   || ptMsg->wSenderTno   == aptExpectMsg[dwLoop]->wSenderTno)  \
         && (0xFFFF == aptExpectMsg[dwLoop]->wMsgID       || ptMsg->wMsgID       == aptExpectMsg[dwLoop]->wMsgID)      \
         && (0xFFFF == aptExpectMsg[dwLoop]->wMsgLen      || ptMsg->wMsgLen      == aptExpectMsg[dwLoop]->wMsgLen)     \
         && (0xFFFF == aptExpectMsg[dwLoop]->wMsgSequence || ptMsg->wMsgSequence == aptExpectMsg[dwLoop]->wMsgSequence))        
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

/**************************************************************************
* 函数名称：scp_getMsgFromBuff
* 功能描述：从消息缓存中取出一个消息
* 访问的表：无
* 修改的表：无
* 输入参数：T_ScpMsgBuff *ptScpMsgBuff: 消息缓存
*           VOID *msg：消息缓冲区指针
*           WORD16 wSize：消息缓冲区尺寸
*           T_Msg *aptExpectMsg[]：期望接收消息类型，为NULL是表示可读任意消息
* 输出参数无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/06    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_getMsgFromBuff(T_ScpMsgBuff *ptScpMsgBuff, VOID *msg, WORD16 wSize, T_Msg *aptExpectMsg[])
{
    #if 0
    WORD32          dwRet = USP_OSS_SCP_ERR_NOT_FOUND_IN_MSG_BUFF;
    T_ScpMsgBlock   *ptScpMsgBlock = NULL;
    
    /* 遍历链表 */
    for(ptScpMsgBlock = (T_ScpMsgBlock *)usp_pub_adt_listFirst(&ptScpMsgBuff->tListMsgBuff);
        NULL != ptScpMsgBlock;
        ptScpMsgBlock = (T_ScpMsgBlock *)usp_pub_adt_listNext((T_USPPubAdtListNode *)ptScpMsgBlock))
    {
        if (scp_isExpectMsg((T_Msg *)(ptScpMsgBlock->pucBlock), aptExpectMsg))
        {
            break;
        }
    }
    
    if (NULL != ptScpMsgBlock)
    {        
        if(ptScpMsgBlock->wBlockLength > wSize)
        {
            dwRet = USP_OSS_SCP_ERR_MSG_BUFF_SIZE_LARGE;
        }
        else
        {       
            memmove(msg, ptScpMsgBlock->pucBlock, ptScpMsgBlock->wBlockLength);
            dwRet = USP_SUCCESS;
        }
        ptScpMsgBuff->dwSpace += (ptScpMsgBlock->wBlockLength + sizeof(T_ScpMsgBlock));
        usp_pub_adt_listDelete(&ptScpMsgBuff->tListMsgBuff, (T_USPPubAdtListNode *)ptScpMsgBlock);
        free(ptScpMsgBlock);        
    }
    
    return dwRet;
    #endif
}

/**************************************************************************
* 函数名称：scp_putMsgToBuff
* 功能描述：放置一个消息到缓存中
* 访问的表：无
* 修改的表：无
* 输入参数：T_ScpMsgBuff *ptScpMsgBuff: 消息缓存ID
*           VOID *msg：消息缓冲区指针
*           WORD16 wSize：消息缓冲区尺寸
* 输出参数无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/06    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_putMsgToBuff(T_ScpMsgBuff *ptScpMsgBuff, VOID *msg, WORD16 wSize)
{
    #if 0
    T_ScpMsgBlock   *ptScpMsgBlock;
    WORD32          dwTotalSpace;

    dwTotalSpace = (WORD32)wSize + sizeof(T_ScpMsgBlock);
    dwTotalSpace = (dwTotalSpace + 3) & ~0x3; /* 4字节对齐 */
    if (ptScpMsgBuff->dwSpace < dwTotalSpace)
    {
        return USP_OSS_SCP_ERR_MSG_BUFF_OVERFLOW;
    }

    ptScpMsgBlock = (T_ScpMsgBlock *)malloc(dwTotalSpace);
    if (NULL == ptScpMsgBlock)
    {
        return USP_OSS_SCP_ERR_LACK_OF_MEMORY;
    }

    ptScpMsgBuff->dwSpace -= dwTotalSpace;
    ptScpMsgBlock->pucBlock = (BYTE *)(ptScpMsgBlock + 1);
    ptScpMsgBlock->wBlockLength = wSize;        
    memmove(ptScpMsgBlock->pucBlock, msg, wSize);    
    //usp_pub_adt_listAdd(&ptScpMsgBuff->tListMsgBuff, (T_USPPubAdtListNode *)ptScpMsgBlock);
    
    return USP_SUCCESS;
    #endif
}

/**************************************************************************
* 函数名称：scp_recvMsg
* 功能描述：接收消息
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno：任务号
*           VOID *msg：消息缓冲区指针
*           WORD16 wSize：消息缓冲区尺寸
*           WORD32 dwTimeOut：超时时间，单位：毫秒
*           T_Msg *aptExpectMsg[]：期望接收消息类型，为NULL是表示可读任意消息
* 输出参数：无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/02/06    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_recvMsg(USP_OssScpTno tno, VOID *msg, WORD16 wSize, WORD32 dwTimeOut, T_Msg *aptExpectMsg[])
{    
    #if 0
    WORD32              dwRet;
    T_Msg               *ptMsg = (T_Msg *)msg;
    WORD32              dwIpcFlag;
    WORD16              wTimerId = 0;
    BYTE                ucIsTimer = FALSE;
    BYTE                ucTaskCtrlIndex;    

    /* 入参判断 */
    if (NULL == msg)
    {
        return USP_OSS_SCP_ERR_NULL_POINTER;
    }
    
    if (SCP_MAX_TNO <= tno)
    {
        return USP_OSS_SCP_ERR_INVALID_TNO;
    }

    ucTaskCtrlIndex = s_pucScpTnoCtrl[tno];

    if (SCP_INVALID_TASK_CTRL_INDEX == ucTaskCtrlIndex)
    {
        return USP_OSS_SCP_ERR_INVALID_TNO;
    }

    if (FALSE == s_ptScpTaskCtrl[ucTaskCtrlIndex].ucIsValid)
    {
        return USP_OSS_SCP_ERR_INVALID_TASK;
    }

    if (USP_OSS_IPC_MQ_INVALID == s_ptScpTaskCtrl[ucTaskCtrlIndex].msgQueue)
    {
        return USP_OSS_SCP_ERR_INVALID_MQ;
    }

    /* 尝试从消息缓存中获取 */
    dwRet = scp_getMsgFromBuff(&s_ptScpTaskCtrl[ucTaskCtrlIndex].tScpMsgBuff, \
                               msg, wSize, aptExpectMsg);
    if (USP_SUCCESS == dwRet)
    {
        ptMsg->wDstTno = tno;
        usp_oss_trace(USP_OSS_ST_RCV, s_aucScpTraceRecvDesc, ptMsg);
        return dwRet;
    }
    if (USP_OSS_SCP_ERR_MSG_BUFF_SIZE_LARGE == dwRet)
    {
        return dwRet;
    }   
    
    /* 根据超时时间分别进行处理 */    
    if (USP_OSS_IPC_FOREVERWAIT == dwTimeOut)
    {    
        dwIpcFlag = USP_OSS_VOS_IPC_FOREVERWAIT;
    }
    else if (USP_OSS_IPC_NOWAIT == dwTimeOut)
    {
        dwIpcFlag = USP_OSS_VOS_IPC_NOWAIT;
    }
    else
    {
        dwIpcFlag = USP_OSS_VOS_IPC_FOREVERWAIT;
        ucIsTimer = TRUE;
        wTimerId = EV_USP_SCP_TimerBeginRecvMsg + ucTaskCtrlIndex;
        usp_oss_timer_killRelTimer(wTimerId);
        usp_oss_timer_setRelTimer(wTimerId, dwTimeOut, tno, NULL);
    }

    /* 接收消息 */
    do
    {
        dwRet = usp_oss_vos_recvMsg(s_ptScpTaskCtrl[ucTaskCtrlIndex].msgQueue, \
                                    msg, wSize, dwIpcFlag);        
        if (USP_SUCCESS == dwRet)           
        {
            if (TRUE == ucIsTimer && ptMsg->wMsgID == wTimerId)
            {
                /* 超时 */
                dwRet = USP_OSS_SCP_ERR_RECV_MSG_TIMEOUT;
            }
            else if (scp_isExpectMsg(ptMsg, aptExpectMsg))
            {
                /* 收到正确的消息 */                  
                ptMsg->wDstTno = tno;
                usp_oss_trace(USP_OSS_ST_RCV, s_aucScpTraceRecvDesc, ptMsg);
                break;
            }
            else
            {
                /* 放置消息到缓存中 */
                scp_putMsgToBuff(&s_ptScpTaskCtrl[ucTaskCtrlIndex].tScpMsgBuff, msg, ptMsg->wMsgLen + sizeof(T_Msg));

                if (USP_OSS_IPC_NOWAIT == dwTimeOut)
                {
                    dwRet = USP_OSS_SCP_ERR_RECV_MSG;
                }
            }
        }                    
    } while (USP_SUCCESS == dwRet);

    /* 取消定时器 */
    if (TRUE == ucIsTimer)
    {
        usp_oss_timer_killRelTimer(wTimerId);
    } 

    return dwRet;       
    #endif
}

/**************************************************************************
* 函数名称：usp_scp_recvTaskMsg
* 功能描述：从指定的任务接收消息
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno：任务号
*           VOID *msg：消息缓冲区指针
*           WORD16 wSize：消息缓冲区尺寸
*           WORD32 dwFlag：发送选项
* 输出参数：无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_recvTaskMsg(USP_OssScpTno tno, VOID *msg, WORD16 wSize, WORD32 dwFlag)
{
    return scp_recvMsg(tno, msg, wSize, dwFlag, NULL);
}

/**************************************************************************
* 函数名称：usp_oss_scp_recvTaskMsgWithTypes
* 功能描述：接收特定类型的消息
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno：任务号
*           VOID *msg：消息缓冲区指针
*           WORD16 wSize：消息缓冲区尺寸
*           WORD32 dwTimeOut：超时时间，单位：毫秒
*           T_Msg *aptExpectMsg[]：期望接收消息类型，为NULL是表示可读任意消息
* 输出参数：无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_recvTaskMsgWithTypes(USP_OssScpTno tno, VOID *msg, WORD16 wSize, WORD32 dwTimeOut, T_Msg *aptExpectMsg[])
{
    return scp_recvMsg(tno, msg, wSize, dwTimeOut, aptExpectMsg);
}

#if USP_OS_LINUX

/*lint -save -e1055 -e64 -e40 */
/**************************************************************************
* 函数名称：scp_getMstrSlvFile
* 功能描述：获得采用主备文件形式记录信息的文件描述符
* 访问的表：无
* 修改的表：无
* 输入参数：WORD16 wMaxFileSize: 文件最大限制尺寸(单位: 字节)
*           BYTE *pucMstrFile: 主文件名
*           BYTE *pucSlvFile: 备份文件名
* 输出参数：无
* 返 回 值：打开的文件描述符
* 其它说明：无
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static int scp_getMstrSlvFile(WORD16 wMaxFileSize, BYTE *pucMstrFile, BYTE *pucSlvFile)
{
    int         fd;
    struct stat f_stat;

    /* 首先生成上层dump目录。以后此处需要改进, 使得能够根据文件名自动生成不存在的目录 */
    #if USP_CPU_TYPE_ppc_8xx || USP_CPU_TYPE_ppc_82xx    
    mkdir("/mnt/app/dump", (S_IRUSR | S_IWUSR | S_IXUSR));
    #else
    mkdir("/mnt/var/dump", (S_IRUSR | S_IWUSR | S_IXUSR));
    #endif

    /* 记录信息到文件中, 如果主文件超过限制大小, 则备份主文件, 然后清空 */
    if(0 > (fd = open((char *)pucMstrFile, O_RDWR | O_APPEND | O_CREAT, (S_IRUSR | S_IWUSR))))
    {
        return fd;
    }
    fstat(fd, &f_stat);
    
    if (wMaxFileSize <= f_stat.st_size)
    {
        close(fd);
        rename((char *)pucMstrFile, (char *)pucSlvFile);
        fd = open((char *)pucMstrFile, O_RDWR | O_TRUNC | O_CREAT, (S_IRUSR | S_IWUSR));
    }

    return fd;
}

/**************************************************************************
* 函数名称：scp_sigchldProcess
* 功能描述：SIGCHLD信号处理程序
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_sigchldProcess(int sig)
{
    int         pid;	
    int         status;
    int         fd;
    WORD16      wLen;
    char        acMsg[256];
    char        acStatInfo[128];
    char        *pcMsgFormat = "%s PID:%d, PNAME:%s, %s\r\n";
    struct tm	tm_ptr;
	time_t	    the_time;
    char        tm_buf[24];
    char        *pcName = NULL;
    WORD16      wLoop;

    /* 获取退出的子进程状态信息 */
    if ( 0 >= (pid = waitpid(-1, &status, WNOHANG)))
    {
        return;
    }

    #if SCP_NTP_USE
    /* 是否是NTP客户端 */
    if (pid == s_scpNtpPid)
    {
        s_scpNtpPid = 0;
        return;
    }
    #endif

    /* 查找子进程名称 */
    for (wLoop = 0; wLoop < s_wScpMainTaskNum; wLoop++)
    {
        if (pid == s_ptScpMainTaskCtrl[wLoop].pid)
        {
            pcName = s_ptScpMainTaskCtrl[wLoop].ptScpMainTaskConfig->pcName;
            break;
        }
    }

    if (NULL == pcName)
    {
        return;
    }

    /* 解析子进程退出状态 */
    if (WIFEXITED(status))    /* 正常终止 */
    {
        sprintf(acStatInfo, "Normal termination, exit status:%d", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) /* 异常终止 */
    {
        sprintf(acStatInfo, "Abnormal termination, signal id:%d, signal desc:%s", WTERMSIG(status), sys_siglist[WTERMSIG(status)]);
    }
    else if (WIFSTOPPED(status))  /* 进程暂停 */
    {
        sprintf(acStatInfo, "Stoped, signal id:%d, signal desc:%s", WSTOPSIG(status), sys_siglist[WSTOPSIG(status)]);
    }

    (void)time(&the_time);
    localtime_r(&the_time, &tm_ptr);
    strftime(tm_buf, 32, "%Y-%m-%d %H:%M:%S", &tm_ptr);
    
    wLen = sprintf(acMsg, pcMsgFormat, tm_buf, pid, pcName, acStatInfo);

    /* 记录信息到文件中 */
    fd = scp_getMstrSlvFile(SCP_MAX_PROC_TERM_LOG_SIZE, (BYTE *)SCP_PROC_TERM_LOG, (BYTE *)SCP_PROC_TERM_LOG_BAK);
    if (0 > fd)
    {
        return;
    }
    else
    {
        write(fd, acMsg, wLen);
        fsync(fd);
        close(fd);
    }

    return;
}

/**************************************************************************
* 函数名称：scp_sigStackDumpProcess
* 功能描述：发生异常信号时保存进程的堆栈信息
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_sigStackDumpProcess(int sig)
{
    VOID        *infoArray[SCP_MAX_STACK_DUMP_LOG_PROBE_DEEP]; 
    size_t      size;
    char        **stackInfo;
    int         fd;
    WORD16      wLoop;
    char        acMsg[256];
    WORD16      wLen;
    char        *pcMsgStartFormat = "# Start %s PID:%d, PNAME:%s, Error:%s(%d)\r\n";
    char        *pcMsgEndFormat = "# End ########################################\r\n";
    struct tm	tm_ptr;
	time_t	    the_time;
    char        tm_buf[24];
    char        acPName[24];

    /* 获取当前进程的堆栈信息 */
    size = backtrace(infoArray, SCP_MAX_STACK_DUMP_LOG_PROBE_DEEP);
    stackInfo = backtrace_symbols(infoArray, size);

    /* 记录信息到文件中 */
    fd = scp_getMstrSlvFile(SCP_MAX_STACK_DUMP_LOG_SIZE, (BYTE *)SCP_STACK_DUMP_LOG, (BYTE *)SCP_STACK_DUMP_LOG_BAK);
    if (0 > fd)
    {
        free(stackInfo);
        return;
    }

    (void)time(&the_time);
    localtime_r(&the_time, &tm_ptr);
    strftime(tm_buf, 32, "%Y-%m-%d %H:%M:%S", &tm_ptr);

    prctl(PR_GET_NAME, acPName);
    wLen = sprintf(acMsg, pcMsgStartFormat, tm_buf, getpid(), acPName, sys_siglist[sig], sig);
    write(fd, acMsg, wLen);
        
    for (wLoop = 0; wLoop < size; wLoop++)
    {
        wLen = sprintf(acMsg, "%s\r\n", stackInfo[wLoop]);
        write(fd, acMsg, wLen);
    }
        
    write(fd, pcMsgEndFormat, strlen(pcMsgEndFormat));
    fsync(fd);
    close(fd);

    free(stackInfo);

    /* 进程终止 */
    exit(sig);

    //return;
}

/**************************************************************************
* 函数名称：scp_setZombieAndStackdump
* 功能描述：设置僵死进程检测和堆栈dump功能
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/04/07    V1.0       高峰        创建
**************************************************************************/
static VOID scp_setZombieAndStackdump(VOID)
{
    struct sigaction act;

    /* 设置信号处理函数 */
    sigfillset(&act.sa_mask); /* 屏蔽所有信号 */
	act.sa_flags = 0;
	
	act.sa_handler = scp_sigchldProcess;        /* 子进程退出 */
	sigaction(SIGCHLD, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 段错误 */
	sigaction(SIGSEGV, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 总线错误 */
	sigaction(SIGBUS, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 向一个没有读进程的管道写数据 */
	sigaction(SIGPIPE, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 浮点异常 */
	sigaction(SIGFPE, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 非法指令 */
	sigaction(SIGILL, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 执行I/O自陷 */
	sigaction(SIGIOT, &act, 0);

    act.sa_handler = scp_sigStackDumpProcess;   /* 无效的系统调用 */
	sigaction(SIGSYS, &act, 0);
   
    return;
}
/*lint -restore */

/**************************************************************************
* 函数名称：usp_oss_scp_pspInit
* 功能描述：初始化性能统计信息
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：USP_SUCCESS：成功；其它为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/10/31    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_pspInit(VOID)
{    
    SWORD32 sdwFd = -1;
    
    //g_ptUSPPubStatisticsInfo = (T_USPPubStatisticsInfo *)usp_oss_mm_staticMalloc(USP_PUB_PSP_SHM_KEY, sizeof(T_USPPubStatisticsInfo));
    //if (NULL == g_ptUSPPubStatisticsInfo)
    {
        return USP_ERR_PUB_PSP_MALLOC_INFO;
    }
    //memset(g_ptUSPPubStatisticsInfo, 0, sizeof(T_USPPubStatisticsInfo));
    
    sdwFd = open((char *)"/mnt/var/log/pspLog", O_RDWR);
    if (0 <= sdwFd)
    {
        read(sdwFd, g_ptUSPPubStatisticsInfo, sizeof(T_USPPubStatisticsInfo));
      //  close(sdwFd);
    }
    
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：scp_pspSave
* 功能描述：持久化性能统计信息
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/10/31    V1.0       高峰        创建
**************************************************************************/
static VOID scp_pspSave(VOID)
{
    SWORD32 sdwFd = -1;

    SCP_DEBUG("(scp_pspSave) running...... \r\n");
              
    sdwFd = open((char *)"/mnt/var/log/pspLog", O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR));
    if (0 <= sdwFd)
    {
        //write(sdwFd, g_ptUSPPubStatisticsInfo, sizeof(T_USPPubStatisticsInfo));
        fsync(sdwFd);
        close(sdwFd);
    }
}

#endif  /* USP_OS_LINUX */

#if SCP_NTP_USE
/**************************************************************************
* 函数名称：scp_mktime
* 功能描述：根据分解时间转化为日历时间。
*           此算法(Gauss算法)来自Linux操作系统。
* 访问的表：无
* 修改的表：无
* 输入参数：WORD32 year: 年
*           WORD32 mon: 月
*           WORD32 day: 日
*           WORD32 hour: 时
*           WORD32 min: 分
*           WORD32 sec: 秒
* 输出参数：无
* 返 回 值：time_t类型的时间值
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static time_t scp_mktime(WORD32 year, WORD32 mon, WORD32 day, WORD32 hour, WORD32 min, WORD32 sec)
{
    if (0 >= (int) (mon -= 2)) 	{  /* 1..12 -> 11,12,1..10 */
         mon += 12;      /* Puts Feb last since it has leap day */
         year -= 1;
    }

    return (((
             (WORD32) (year/4 - year/100 + year/400 + 367*mon/12 + day) +
             year*365 - 719499
          )*24 + hour /* now have hours */
       )*60 + min  /* now have minutes */
    )*60 + sec;  /* finally seconds */
}

/**************************************************************************
* 函数名称：scp_ntpClient
* 功能描述：NTP客户端
* 访问的表：无
* 修改的表：无
* 输入参数：T_USPOssScpNtpCfg *ptNtpCfg: NTP配置信息
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/11/22    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_ntpClient(T_USPOssScpNtpCfg *ptNtpCfg)
{
    WORD32                  dwRet;
    WORD16                  wLoop;
    #if USP_OS_LINUX && USP_DRV_RTC_USE
    struct tm               *tm_ptr = NULL;
    time_t                  the_time;
    T_USPDrvRTCTime         tUSPDrvRTCTime;
    #endif
    
    /* ntp时间同步 */
    for (wLoop = 0; \
         wLoop < (sizeof(ptNtpCfg->adwNtpServerIp) / sizeof(WORD32)) \
      && 0 != ptNtpCfg->adwNtpServerIp[wLoop]; \
         wLoop++)
    {
        dwRet = usp_oss_vos_updateNtp(ptNtpCfg->adwNtpServerIp[wLoop]);
        if (USP_SUCCESS == dwRet)
        {
            SCP_DEBUG("(scp_ntpClient) update ntp success server = 0x%x \r\n", \
                      ptNtpCfg->adwNtpServerIp[wLoop]);

            #if USP_OS_LINUX && USP_DRV_RTC_USE
            /* 更新RTC, RTC中存储的是国际标准时间 */
            the_time = time(NULL);
            tm_ptr = gmtime(&the_time);
            tUSPDrvRTCTime.tm_year = tm_ptr->tm_year + 1900;
            tUSPDrvRTCTime.tm_mon  = tm_ptr->tm_mon + 1;
            tUSPDrvRTCTime.tm_mday = tm_ptr->tm_mday;
            tUSPDrvRTCTime.tm_hour = tm_ptr->tm_hour;
            tUSPDrvRTCTime.tm_min  = tm_ptr->tm_min;
            tUSPDrvRTCTime.tm_sec  = tm_ptr->tm_sec;
            tUSPDrvRTCTime.tm_wday = tm_ptr->tm_wday + 1;

            SCP_DEBUG("(scp_ntpClient) write RTC: %u/%u/%u %u:%u:%u \r\n", \
                      tUSPDrvRTCTime.tm_year, tUSPDrvRTCTime.tm_mon, tUSPDrvRTCTime.tm_mday, \
                      tUSPDrvRTCTime.tm_hour, tUSPDrvRTCTime.tm_min, tUSPDrvRTCTime.tm_sec);
            
            dwRet = usp_drv_rtc_writeTime(&tUSPDrvRTCTime, NULL);

            SCP_DEBUG("(scp_ntpClient) write RTC dwRet = %u \r\n", dwRet);
            #endif
            
            return USP_SUCCESS;
        }
        else
        {
            //SCP_EXCEPT(dwRet, ptNtpCfg->adwNtpServerIp[wLoop], 0, 0);
        }
    }

    SCP_DEBUG("(scp_ntpClient) update ntp fail! \r\n");

    #if USP_OS_LINUX && USP_DRV_RTC_USE
    /* 使用RTC时间 */
    dwRet = usp_drv_rtc_readTime(&tUSPDrvRTCTime, NULL);    
    if (USP_SUCCESS == dwRet)
    {
        the_time = scp_mktime(tUSPDrvRTCTime.tm_year, tUSPDrvRTCTime.tm_mon, \
                              tUSPDrvRTCTime.tm_mday, tUSPDrvRTCTime.tm_hour, \
                              tUSPDrvRTCTime.tm_min, tUSPDrvRTCTime.tm_sec);
        stime(&the_time);
    }         

    SCP_DEBUG("(scp_ntpClient) read RTC dwRet = %u, %u/%u/%u %u:%u:%u, the_time = %u \r\n", 
              dwRet, \
              tUSPDrvRTCTime.tm_year, tUSPDrvRTCTime.tm_mon, tUSPDrvRTCTime.tm_mday, \
              tUSPDrvRTCTime.tm_hour, tUSPDrvRTCTime.tm_min, tUSPDrvRTCTime.tm_sec, \
              the_time);    
    #endif

    return USP_OSS_SCP_ERR_NTP_UPDATE;
}

/**************************************************************************
* 函数名称：scp_updateNtp
* 功能描述：NTP时间同步
* 访问的表：无
* 修改的表：无
* 输入参数：BYTE ucIsUpdateTimeZone: 是否更新时区
*           BYTE ucIsCfgChg: 是否配置变更引起的时间同步
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_updateNtp(BYTE ucIsUpdateTimeZone, BYTE ucIsCfgChg)
{
    WORD32                      dwRet;
    T_USPOssScpNtpCfg           tNtpCfg;
    WORD16                      wLoop;

    SCP_DEBUG("(scp_updateNtp) running. ucIsUpdateTimeZone = %u, ucIsCfgChg = %u \r\n", \
              ucIsUpdateTimeZone, ucIsCfgChg);

    /* 获取ntp服务器配置信息 */
    memset(&tNtpCfg, 0, sizeof(T_USPOssScpNtpCfg));
    dwRet = SCP_GET_NTP_CONFIG(&tNtpCfg);
    if (USP_SUCCESS != dwRet)
    {
       // SCP_EXCEPT(dwRet, 0, 0, 0);
        return;
    }    

    if (0 == tNtpCfg.dwSyncPeriod)
    {
        tNtpCfg.dwSyncPeriod = SCP_NTP_UPDATE_TIMER;
    }
        
    if (SCP_IS_DEBUG)
    {
        SCP_DEBUG("(scp_updateNtp) ntp server info: TimeZoneH = %d, TimeZoneM = %d, Port = %u, dwSyncPeriod = %u \r\n", \
                  tNtpCfg.cTimeZoneH, tNtpCfg.cTimeZoneM, tNtpCfg.wPort, tNtpCfg.dwSyncPeriod);

        for (wLoop = 0; \
             wLoop < (sizeof(tNtpCfg.adwNtpServerIp) / sizeof(WORD32)) \
          && 0 != tNtpCfg.adwNtpServerIp[wLoop]; \
             wLoop++)
        {
            SCP_DEBUG("Ntp server %u = 0x%x \r\n", wLoop, tNtpCfg.adwNtpServerIp[wLoop]);
        }
    }    

    if (TRUE == ucIsCfgChg && 0 == memcmp(&s_tScpNtpCfg, &tNtpCfg, sizeof(T_USPOssScpNtpCfg)))
    {            
        SCP_DEBUG("(scp_updateNtp) ntp config is not changed! \r\n");
        return;
    }

    s_tScpNtpCfg = tNtpCfg;
    
    /* 第一次时间同步 */
    if (TRUE == ucIsUpdateTimeZone)
    {
        dwRet = usp_oss_vos_setTimezone(tNtpCfg.cTimeZoneH, tNtpCfg.cTimeZoneM);
        if (USP_SUCCESS != dwRet)
        {
           // SCP_EXCEPT(dwRet, tNtpCfg.cTimeZoneH, tNtpCfg.cTimeZoneM, 0);
        }
                
        if (USP_SUCCESS == scp_ntpClient(&tNtpCfg))
        {
            s_ucScpIsNtpUpdateSuccess = TRUE;
        }
        else
        {
            s_ucScpIsNtpUpdateSuccess = FALSE;
        }
        return;
    }

    /* 启动子进程进行时间同步 */    
    if (0 != s_scpNtpPid)
    {
        kill(s_scpNtpPid, SIGKILL);
    }

    if (0 == (s_scpNtpPid = fork()))
    {
        prctl(PR_SET_NAME, "usp_ntpupdate");

        if (USP_SUCCESS == scp_ntpClient(&tNtpCfg))
        {
            s_ucScpIsNtpUpdateSuccess = TRUE;
        }
        else
        {
            s_ucScpIsNtpUpdateSuccess = FALSE;
        }        
        SCP_ALARM_NTP;
        
        exit(0);
    }

    /* 设置定时器 */
    usp_oss_timer_killRelTimer(EV_USP_SCP_TimerNtpUpdate);
    usp_oss_timer_setRelTimer(EV_USP_SCP_TimerNtpUpdate, s_tScpNtpCfg.dwSyncPeriod * 60 * 1000, \
                              USP_OSS_SCP_TNO, NULL);

    return;   
}
#endif  /* SCP_NTP_USE */

/**************************************************************************
* 函数名称：scp_setTime
* 功能描述：设置系统时间, 如果有RTC, 则同步更新RTC时间
* 访问的表：无
* 修改的表：无
* 输入参数：WORD32 dwTime：阅读器时间（从1970.1.1经过的秒数）
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/19    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_setTime(WORD32 dwTime)
{
    WORD32                  dwRet = USP_SUCCESS;   
    #if USP_OS_LINUX 
    time_t                  the_time = dwTime;
    #if USP_DRV_RTC_USE    
    struct tm               *tm_ptr = NULL;    
    T_USPDrvRTCTime         tUSPDrvRTCTime;
    #endif

    SCP_DEBUG("(scp_setTime) running. dwTime = %u \r\n", dwTime);

    /* 设置操作系统时间 */
    if (0 != stime(&the_time))
    {
        return USP_OSS_SCP_ERR_SET_TIME;
    }    

    #if USP_DRV_RTC_USE
    /* 更新RTC, RTC中存储的是国际标准时间 */
    tm_ptr = gmtime(&the_time);
    tUSPDrvRTCTime.tm_year = tm_ptr->tm_year + 1900;
    tUSPDrvRTCTime.tm_mon  = tm_ptr->tm_mon + 1;
    tUSPDrvRTCTime.tm_mday = tm_ptr->tm_mday;
    tUSPDrvRTCTime.tm_hour = tm_ptr->tm_hour;
    tUSPDrvRTCTime.tm_min  = tm_ptr->tm_min;
    tUSPDrvRTCTime.tm_sec  = tm_ptr->tm_sec;
    tUSPDrvRTCTime.tm_wday = tm_ptr->tm_wday + 1;

    SCP_DEBUG("(scp_setTime) write RTC: %u/%u/%u %u:%u:%u \r\n", \
              tUSPDrvRTCTime.tm_year, tUSPDrvRTCTime.tm_mon, tUSPDrvRTCTime.tm_mday, \
              tUSPDrvRTCTime.tm_hour, tUSPDrvRTCTime.tm_min, tUSPDrvRTCTime.tm_sec);
    
    dwRet = usp_drv_rtc_writeTime(&tUSPDrvRTCTime, NULL);

    SCP_DEBUG("(scp_setTime) write RTC dwRet = %u \r\n", dwRet);
    #endif    
    #endif
    
    return dwRet;   
}

/**************************************************************************
* 函数名称：usp_scp_setTaskStatus
* 功能描述：设置应用任务的当前状态
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTask task：任务标识
*           WORD16 wStatus：状态
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
VOID usp_oss_scp_setTaskStatus(USP_OssScpTask task, WORD16 wStatus)
{
    task->wRunStatus = wStatus;
    return;
}

/**************************************************************************
* 函数名称：usp_scp_getTaskStatus
* 功能描述：获取应用任务的当前状态
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTask task：任务标识
* 输出参数：无
* 返 回 值：应用任务的当前状态
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD16 usp_oss_scp_getTaskStatus(USP_OssScpTask task)
{
    return task->wRunStatus;
}

/**************************************************************************
* 函数名称：usp_oss_scp_keepAliveAck
* 功能描述：发送握手应答消息
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno：任务号
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_keepAliveAck(USP_OssScpTno tno)
{
    BYTE        aucBuf[48];
    T_Msg       *ptMsg = (T_Msg *)aucBuf;

    ptMsg->mtype = 1;
    ptMsg->wSenderTno = tno;
    ptMsg->wMsgID = EV_USP_SCP_KeepAliveAck;
    ptMsg->wMsgLen = sizeof(USP_OssScpTno);
    *((USP_OssScpTno *)(ptMsg + 1)) = tno;

    return usp_oss_scp_sendTaskMsg(USP_OSS_SCP_TNO, ptMsg, USP_OSS_IPC_NOWAIT);
}

/**************************************************************************
* 函数名称：usp_oss_scp_getMsgQueueHandle
* 功能描述：获取与任务相关的消息队列句柄
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTno tno：任务号
* 输出参数：USP_OssIpcMsgQueue *mq: 与任务号对应的消息队列句柄
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_getMsgQueueHandle(USP_OssScpTno tno, USP_OssIpcMsgQueue *mq)
{
    BYTE    ucTaskCtrlIndex;

    if (SCP_MAX_TNO <= tno)
    {
        return USP_OSS_SCP_ERR_INVALID_TNO;
    }

    ucTaskCtrlIndex = s_pucScpTnoCtrl[tno];

    if (SCP_INVALID_TASK_CTRL_INDEX == ucTaskCtrlIndex)
    {
        return USP_OSS_SCP_ERR_INVALID_TNO;
    }

    if (FALSE == s_ptScpTaskCtrl[ucTaskCtrlIndex].ucIsValid)
    {
        return USP_OSS_SCP_ERR_INVALID_TASK;
    }

    if (USP_OSS_IPC_MQ_INVALID == s_ptScpTaskCtrl[ucTaskCtrlIndex].msgQueue)
    {
        return USP_OSS_SCP_ERR_INVALID_MQ;
    }

    *mq = s_ptScpTaskCtrl[ucTaskCtrlIndex].msgQueue;
    return USP_SUCCESS;
}

#if USP_OS_LINUX
/**************************************************************************
* 函数名称：scp_initUsp
* 功能描述：USP平台初始化。包括硬件设备、CPU、网络、打印控制等等。           
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_initUsp(VOID)
{    
    /* 配置CoreDump */
    #if USP_VERSION_DEBUG
    WORD32      dwRet;
    dwRet = usp_oss_vos_configCoredump();
    if (USP_SUCCESS != dwRet)
    {
        //SCP_EXCEPT(dwRet, 0, 0, 0);
    }
    SCP_DEBUG("(scp_initApp) config core dump ret = %u \r\n", dwRet);
    #endif

    /* 初始化僵死进程检测和堆栈dump */
    SCP_DEBUG("(scp_initApp) set check zombie and stack dump \r\n");    
    scp_setZombieAndStackdump();
    
    return;
}
#endif  /* USP_OS_LINUX */

#if USP_OS_FREERTOS

#ifdef INCLUDE_DEBUG
/**************************************************************************
* 函数名称：usp_rspDebugProxyEntry
* 功能描述：FreeRTOS下的打印代理任务入口           
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTask task: 任务管理结构
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_rspDebugProxyEntry(USP_OssScpTask task)
{
    rspDebugProxy(NULL);
    
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：usp_rspDebugInputEntry
* 功能描述：FreeRTOS下的串口输入代理任务入口           
* 访问的表：无
* 修改的表：无
* 输入参数：USP_OssScpTask task: 任务管理结构
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_rspDebugInputEntry(USP_OssScpTask task)
{
    rspDebugInput(NULL);
    
    return USP_SUCCESS;
}
#endif  /* INCLUDE_DEBUG */

/**************************************************************************
* 函数名称：scp_initUsp
* 功能描述：USP平台初始化。包括硬件设备、CPU、网络、打印控制等等。           
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/08/18    V1.0       高峰        创建
**************************************************************************/
static VOID scp_initUsp(VOID)
{    
    /* 设置调试代理 */    
    #ifdef INCLUDE_DEBUG  
    
    g_DebugProxyQueue = xQueueCreate(DEBUGPROXY_MSG_ITEM_COUNT, DEBUGPROXY_MSG_ITEM_SIZE);        
    vSemaphoreCreateBinary(xPrintSem);

    ConfigDebugDevice();

    #if 0
    xTaskCreate(rspDebugProxy, "rspDebugProxy", 200, NULL, SCP_DEBUG_TASK_PRIO, NULL);
    #if 0
    xTaskCreate( rspDebugNetwork,(  signed portCHAR *  ) "rspDebugNetwork", 256, NULL, 2, ( xTaskHandle * ) NULL );
    #else
    xTaskCreate(rspDebugInput, "rspDebugInput", 256, NULL, SCP_DEBUG_TASK_PRIO, NULL);
    #endif
    #endif

    s_ucIsDebug = TRUE;

    #endif

    /* 设置网络(LWIP) */
    #if USP_OSS_NET_USE
    tcpip_init(NULL, NULL);
    #endif          
    
    return;
}

#ifdef USE_SDRAM
/* 
 * 实现扩展SDRAM驱动
 */
static VOID os_msDelay(WORD32 dwTime)
{
    WORD32 dwDelay = dwTime * 12000;
    for(; dwDelay > 0; dwDelay--)
    {
        ;
    }
}

VOID InitSDram(VOID)
{
	WORD32 i, dummy = dummy;

	/*************************************************************************
	 Initialize EMC and SDRAM
	*************************************************************************/
	//  SCS     |= 0x00000002;		/* Reset EMC */ 
	EMC_CTRL = 0x00000001;		/*Disable Address mirror*/
	PCONP   |= 0x00000800;		/* Turn On EMC PCLK */
	//PINSEL4 = (PINSEL4 & 0xCFFFFFFF) | 0x10000000;
	PINSEL5  = 0x05010155;
	PINSEL6  = 0x55555555;
	PINSEL8  = 0x55555555;
	PINSEL9  = 0x50051555;  


	EMC_DYN_RD_CFG = 1;		/* Command delayed strategy */

	/* Default setting, RAS latency 3 CCLKs, CAS latenty 3 CCLKs. */
	EMC_DYN_RASCAS0 = 0x00000303;


	/* 256MB, 16Mx16, 4 banks, row=12, column=9 */
	EMC_DYN_CFG0 = 0x00000480;

	/* 256MB, 16Mx16, 4 banks, row=13, column=9 */
	//EMC_DYN_CFG0 = 0x00000680;

	os_msDelay(100);			/* use timer 1 */

	/* Mem clock enable, CLKOUT runs, send command: NOP */
	EMC_DYN_CTRL = 0x00000183;
	os_msDelay(200);			/* use timer 1 */
    
	/* Send command: PRECHARGE-ALL, shortest possible refresh period */
	EMC_DYN_CTRL = 0x00000103;

	/* set 32 CCLKs between SDRAM refresh cycles */
	EMC_DYN_RFSH = 0x00000002;
	for(i = 0; i < 0x40; i++);	/* wait 128 AHB clock cycles */
    
	/* set 28 x 16CCLKs=448CCLK=7us between SDRAM refresh cycles */
	EMC_DYN_RFSH = 28;
  //EMC_DYN_RFSH = 46;
    
	/* To set mode register in SDRAM, enter mode by issue
	MODE command, after finishing, bailout and back to NORMAL mode. */    
	/* Mem clock enable, CLKOUT runs, send command: MODE */
	EMC_DYN_CTRL = 0x00000083;
  
	/* Set mode register in SDRAM */
	/* Mode regitster table for Micron's MT48LCxx */
	/* bit 9:   Programmed burst length(0)
     bit 8~7: Normal mode(0)
	 bit 6~4: CAS latency 3
	 bit 3:   Sequential(0)
	 bit 2~0: Burst length is 8
	 row position is 12 */
	dummy = *((volatile WORD32 *)(0xA0000000 | (0x33 << 12)));
  
	EMC_DYN_CTRL = 0x00000000;	  /* Send command: NORMAL */

	EMC_DYN_CFG0 |= 0x00080000;	  /* Enable buffer */

	os_msDelay(1);				  /* Use timer 1 */

  return;

}
#endif

#endif  /* USP_OS_FREERTOS */

#if USP_DRV_WTD_USE

/**************************************************************************
* 函数名称：usp_scp_stopFeedWatchDog
* 功能描述：停止喂狗
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/12/29    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_scp_stopFeedWatchDog(VOID)
{
    *s_pucScpIsFeedWatchDogCtrl = FALSE;
    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：scp_feedWatchDog
* 功能描述：喂狗任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/12/29    V1.0       高峰        创建
**************************************************************************/
static VOID scp_feedWatchDog(VOID *arg)
{
    /* 启动看门狗 */
    usp_drv_wtd_enable();
        
    /* 每隔0.5s软件喂狗一次 */
    for (; ;)
    {    
        if (TRUE == *s_pucScpIsFeedWatchDogCtrl)
        {
            SCP_DEBUG("(scp_feedWatchDog) running ...... \r\n");
            usp_drv_wtd_feed();
        }
        USP_OSS_VOS_SLEEP_MSEC(500);
    }
    
    //return;
}

/**************************************************************************
* 函数名称：scp_startWatchDog
* 功能描述：启动喂狗任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/12/29    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_startWatchDog(VOID)
{
    WORD32      dwRet;
    
    SCP_DEBUG("(scp_startWatchDog) running ...... \r\n");
    
    #if USP_OS_LINUX
    s_pucScpIsFeedWatchDogCtrl = (BYTE *)usp_oss_mm_staticMalloc(USP_OSS_SCP_WTD_CTRL_SHM_KEY, sizeof(BYTE));
    if (NULL == s_pucScpIsFeedWatchDogCtrl)
    {
        return USP_OSS_SCP_ERR_MALLOC_WTD_CTRL;
    }    
    
    *s_pucScpIsFeedWatchDogCtrl = TRUE;    
    dwRet = usp_oss_vos_createProcess(scp_feedWatchDog, NULL, SCP_WTD_TASK_NAME, -10, NULL);
    #endif

    #if USP_OS_FREERTOS
    dwRet = usp_oss_vos_createThread(scp_feedWatchDog, NULL, SCP_WTD_TASK_NAME, 256, configMAX_PRIORITIES - 1, NULL);
    #endif    
    
    return dwRet;
}

#else

/**************************************************************************
* 函数名称：scp_startWatchDog
* 功能描述：启动喂狗任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/12/29    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_startWatchDog(VOID)
{    
    return USP_SUCCESS;
}

#endif  /* USP_DRV_WTD_USE */

#if USP_DRV_LED_USE && USP_OSS_LED_USE

/**************************************************************************
* 函数名称：scp_startLedFlash
* 功能描述：启动闪灯任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 11/09/19    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_startLedFlash(VOID)
{    
    WORD32          dwRet;

    SCP_DEBUG("(scp_startLedFlash) running ...... \r\n");
    
    dwRet = usp_oss_led_init();
    if (USP_SUCCESS != dwRet)
    {
        return dwRet;
    }

    //SCP_LED_FLASH_ON(SCP_LED_STARTUPING);
    
    #if USP_OS_LINUX
    dwRet = usp_oss_vos_createProcess(usp_oss_led_entry, NULL, SCP_LED_FLASH_TASK_NAME, 0, NULL);
    #endif

    #if USP_OS_FREERTOS
    dwRet = usp_oss_vos_createThread(usp_oss_led_entry, NULL, SCP_LED_FLASH_TASK_NAME, 256, 4, NULL);
    #endif    
    
    return dwRet;
}

#else

/**************************************************************************
* 函数名称：scp_startLedFlash
* 功能描述：启动闪灯任务
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 11/09/19    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_startLedFlash(VOID)
{    
    return USP_SUCCESS;
}

#endif  /* USP_DRV_LED_USE && USP_OSS_LED_USE */

/**************************************************************************
* 函数名称：scp_initBsp
* 功能描述：硬件初始化，根据系统的驱动配置情况来初始化硬件设备。
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 09/12/29    V1.0       高峰        创建
**************************************************************************/
static WORD32 scp_initBsp(VOID)
{
    WORD32                  dwRet = USP_SUCCESS;
    WORD16                  wLoop;

    /* 定义硬件初始化函数列表 */
    usp_oss_scp_initEntry   *pInitEntry[] = {
        
        #if USP_DRV_IOPORT_USE
        usp_drv_ioport_init,
        #endif  

        #if USP_DRV_EPLD_USE
        usp_drv_epld_init,
        #endif 

        #if USP_DRV_FPGA_USE
        usp_drv_fpga_init,
        #endif         

        #if USP_DRV_I2C_USE
        usp_drv_i2c_init,
        #endif

        #if USP_DRV_RTC_USE
        usp_drv_rtc_init,
        #endif 

        #if USP_DRV_WTD_USE
        usp_drv_wtd_init,
        #endif

        #if USP_DRV_EEPROM_USE
        usp_drv_eeprom_init,
        #endif

        #if 0
        #if USP_DRV_CODEKBD_USE
        usp_drv_codekbd_init,
        #endif
        #endif

        #if USP_DRV_FLASH_USE
        usp_drv_flash_init,
        #endif

        #if 0
        #if USP_DRV_PRINTERCTL_USE
        usp_drv_printerctl_init,
        #endif
        #endif
        
        #if USP_DRV_TSENSOR_USE
        usp_drv_tsensor_init,
        #endif

        #if 0
        #if USP_DRV_GPRS_USE
        usp_drv_gprs_init,
        #endif
        #endif
        
        #if USP_DRV_LCD_USE
        usp_drv_lcd_init,
        #endif

        #if USP_DRV_LED_USE
        usp_drv_led_init,
        #endif

        #if USP_DRV_GPIO_USE
        usp_drv_gpio_init,
        #endif

        #if USP_DRV_GET_SYSTEM_INFO_USE
        usp_drv_get_system_info_init,
        #endif

        #if USP_DRV_TIMER_USE
        usp_drv_timer_init,
        #endif

        NULL,
        
    };

    #if USP_OS_FREERTOS
    /* 初始化CPU */
    ConfigurePLL();
    GPIOResetInit();
    #endif

    /* 按照顺序一步步初始化硬件设备 */
    for (wLoop = 0; NULL != pInitEntry[wLoop]; wLoop++)
    {
        dwRet = (*(pInitEntry[wLoop]))();
        if (USP_SUCCESS != dwRet)
        {
            return dwRet;
        }
    }
    
    return dwRet;    
}

//#if USP_OS_LINUX
/**************************************************************************
* 函数名称：usp_oss_scp_setStartupReason
* 功能描述：设置系统启动原因
* 访问的表：无
* 修改的表：无
* 输入参数：BYTE ucWhy：原因码
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 10/11/06    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_setStartupReason(BYTE ucWhy)
{
    int         fd = -1;
    int         len = 0;

    /* 记录重启状态到文件中 */
    if(0 > (fd = open(SCP_STARTUP_REASON_FILE, O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR))))
    {
        return USP_OSS_SCP_ERR_OPEN_RESET_STATUS_FILE;
    }

    len = write(fd, &ucWhy, sizeof(BYTE));
    fsync(fd);
    close(fd);
    
    if (sizeof(BYTE) != len)
    {
        return USP_OSS_SCP_ERR_WRITE_RESET_STATUS_FILE;
    }

    return USP_SUCCESS;
}

/**************************************************************************
* 函数名称：usp_oss_scp_getStartupReason
* 功能描述：获取系统启动原因
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：BYTE *pucWhy: 原因码
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 10/11/06    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_getStartupReason(BYTE *pucWhy)
{
    int         fd = -1;
    int         len = 0;

    /* 读取重启状态 */
    if(0 > (fd = open(SCP_STARTUP_REASON_FILE, O_RDWR)))
    {
        /* 文件不存在，返回正常状态 */
        *pucWhy = USP_OSS_SCP_STARTUP_NORMAL;
        return USP_SUCCESS;
    }
    
    len = read(fd, pucWhy, sizeof(BYTE));
    close(fd);
    
    if (sizeof(BYTE) != len)
    {
        return USP_OSS_SCP_ERR_READ_RESET_STATUS_FILE;
    }

    return USP_SUCCESS;
}

//#else
#if 0
/**************************************************************************
* 函数名称：usp_oss_scp_setStartupReason
* 功能描述：设置系统启动原因
* 访问的表：无
* 修改的表：无
* 输入参数：BYTE ucWhy：原因码
* 输出参数：无
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 10/11/06    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_setStartupReason(BYTE ucWhy)
{
    return USP_SUCCESS;    
}

/**************************************************************************
* 函数名称：usp_oss_scp_getStartupReason
* 功能描述：获取系统启动原因
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：BYTE *pucWhy: 原因码
* 返 回 值：USP_SUCCESS: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 10/11/06    V1.0       高峰        创建
**************************************************************************/
WORD32 usp_oss_scp_getStartupReason(BYTE *pucWhy)
{
    *pucWhy = USP_OSS_SCP_STARTUP_NORMAL;
    return USP_SUCCESS;
}
#endif
//#endif

//#endif  /* USP_OSS_SCP_USE */


