/***************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
*
* 文件名称：ReportFilter.c
* 文件标识：
* 内容摘要：report模块过滤等高级功能函数的实现
* 其它说明：
* 当前版本：
* 作    者：lzy 
* 完成日期：2012.03.01
*
* 修改记录1：  
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************************/

/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include "rdppub.h"
#include "rdpapppub.h"
#include "report.h"

/***********************************************************
 *                     常量定义                            *
***********************************************************/

/***********************************************************
*                 文件内部使用的宏                        *
***********************************************************/

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/

/***********************************************************
 *                     全局变量                            *
***********************************************************/
extern T_RdpOpFilterHashEntry *g_ptRdpOpFilterHashEntry;
extern T_RdpTagReportFilterHashEntry *g_ptRdpTagReportFilterHashEntry;
extern T_USPRdpAdvancedConfig g_tRdpAdvancedConfig;
T_RdpRssiQueueCtrl g_tRssiQueueCtrl;
T_RdpRssiQueueNode gtRssiQueueNode[RSSI_SORT_NUM];
unsigned char g_ucTagReportTime;
unsigned char g_ucTagReportDeleteTime;
unsigned char g_ucTagOpFilterTime;
unsigned char g_ucTagOpFilterDeleteTime;
/***********************************************************
 *                     本地变量                            *
***********************************************************/



/***********************************************************
 *                     全局函数                            *
***********************************************************/

/***********************************************************
 *                     局部函数                            *
***********************************************************/
static T_RdpTagReportFilterHashEntry *report_initReportFilterHashTable();
static T_RdpTagReportFilterHashEntry *report_insertRoReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
static T_RdpTagReportFilterHashEntry *report_findRoReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
static T_RdpTagReportFilterHashEntry *report_insertAoReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
static T_RdpTagReportFilterHashEntry *report_findAOReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
static void report_startReportFilterTimer(unsigned char ucDeleteTime);
static unsigned int report_constructReportFilterMemory();
static unsigned int report_sendOpFilterAccessReport(unsigned char ucLinkType, unsigned char ucLinkIndex, unsigned short int wSendTno, unsigned int dwMessageID, T_RdpLlrpSingleReportCtrl *ptOneReportControl);
static unsigned int report_sendReportWhenTimeOut(T_RdpOpFilterHashEntry *ptTagCursor);

/**************************************************************************
* 函数名称：rdp_calcHashKey
* 功能描述：计算hash表key值
* 访问的表：无
* 修改的表：无
* 输入参数：T_RdpLlrpUID *ptRdpLlrpUID 唯一标识
*                            unsigned short int HashTableLength hash桶长度
* 输出参数：无
* 返 回 值：hashkey值
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/01    V1.0       lzy        创建
**************************************************************************/
unsigned int rdp_calcHashKey(T_RdpLlrpUID *ptRdpLlrpUID, unsigned short int HashTableLength)
{
    unsigned int dwIndex = 0;
    unsigned char *ptByte = NULL ;
    unsigned int dwKey = 0;
    unsigned int dwTemp = 0;
    ptByte = &(ptRdpLlrpUID->aucTagData[0]);
    RdpReportDbgPrint("ptTag->wTagDataLen = %d\r\n", ptRdpLlrpUID->wTagDataLen);
    for (dwIndex = 0; dwIndex < ptRdpLlrpUID->wTagDataLen;dwIndex++)
    {
        RdpReportDbgPrint("ptRdpLlrpUID->aucTagData[%d] = %d\r\n", dwIndex, ptRdpLlrpUID->aucTagData[dwIndex]);
        dwKey = (dwKey << 4) + *ptByte++;
        dwTemp = dwKey & 0Xf0000000L;
        if (dwTemp)
            dwKey ^= dwTemp >> 24;
        dwKey &= ~dwTemp;
    }
    dwKey = dwKey % HashTableLength;
    RdpReportDbgPrint("hashkey= %d\r\n", dwKey);
    return dwKey;
}



/**************************************************************************
* 函数名称：report_initReportFilterHashTable
* 功能描述：上报过滤数据库申请内存
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：T_RdpTagReportFilterHashEntry 上报过滤数据库链表头指针
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/01    V1.0       lzy        创建
**************************************************************************/
static T_RdpTagReportFilterHashEntry *report_initReportFilterHashTable()
{
    T_RdpTagReportFilterHashEntry *ptHashHandle = NULL;

    ptHashHandle = (T_RdpTagReportFilterHashEntry *)malloc(sizeof(T_RdpTagReportFilterHashEntry) * HASHTABLE_LENGTH);

    if (NULL != ptHashHandle)
    {
        memset(ptHashHandle, 0, sizeof(T_RdpTagReportFilterHashEntry)*HASHTABLE_LENGTH);
    }

    return ptHashHandle;
}


/**************************************************************************
* 函数名称：report_findRoReportFilterHashNode
* 功能描述 :   查找上报过滤数据库
* 访问的表：上报过滤数据库hash表
* 修改的表：
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle 上报过滤数据库头结点
                              unsigned int dwKey hash表key值
                              T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl 标签报告
* 输出参数：无
* 返 回 值：T_RdpTagReportFilterHashEntry 查到的上报过滤结点
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static T_RdpTagReportFilterHashEntry *report_findRoReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl)
{
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;

    RdpReportDbgPrint("dwKey = %d\r\n", dwKey);
    RdpReportDbgPrint("[report_findRoReportFilterHashNode]:ptTagReportFilterHandle[dwKey] = 0x%x\r\n", ptTagReportFilterHandle[dwKey].ptNext);

    if (NULL == ptTagReportFilterHandle[dwKey].ptNext)
    {
        RdpReportDbgPrint("there is not the Tag TagReportFilterHashFind\r\n");
        return NULL;
    }

    for (ptTagCursor = ptTagReportFilterHandle[dwKey].ptNext; NULL != ptTagCursor; ptTagCursor = ptTagCursor->ptNext)
    {
        RdpReportDbgPrint("[report_findRoReportFilterHashNode]:ptTagCursor = 0x%x\r\n", ptTagCursor);

        if (ptTagCursor->tRdpLlrpUID.wTagDataLen != ptSignalReportCtrl->tUID.wTagDataLen)
        {
            continue;
        }

        if (0 != memcmp(ptTagCursor->tRdpLlrpUID.aucTagData, ptSignalReportCtrl->tUID.aucTagData,
                        ptTagCursor->tRdpLlrpUID.wTagDataLen))
        {
            continue;
        }

        if (ptTagCursor->dwROSpecId != ptSignalReportCtrl->tRdpLlrpTagReport.tROTagReport.dwROSpecID)
        {
            continue;
        }
        RdpReportDbgPrint("[report_findRoReportFilterHashNode]: return ptTagCursor = 0x%x\r\n", ptTagCursor);
        break;

    }

    return ptTagCursor;
}
/**************************************************************************
* 函数名称：report_insertAoReportFilterHashNode
* 功能描述：将结点插入到上报过滤数据库
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle 上报过滤数据库头结点
                              unsigned int dwKey hash表key值
                              T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl 标签报告
* 输出参数：无
* 返 回 值：T_RdpTagReportFilterHashEntry 插入的上报过滤结点
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static T_RdpTagReportFilterHashEntry *report_insertAoReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl)
{

    unsigned long long dwCurrentTime;
    unsigned short int wLoop = 0;
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;
    T_RdpLlrpAccessTagReport *ptAccessTagReport = NULL;
    ptAccessTagReport = &(ptSignalReportCtrl->tRdpLlrpTagReport.tAccessTagReport);

    for (ptTagCursor = &ptTagReportFilterHandle[dwKey]; NULL != ptTagCursor->ptNext; ptTagCursor = ptTagCursor->ptNext)
    {
        ;
    }

    ptTagCursor->ptNext = (T_RdpTagReportFilterHashEntry *)malloc(sizeof(T_RdpTagReportFilterHashEntry));
    if (NULL == ptTagCursor->ptNext)
    {
        RDP_EXCEPT(RDP_NULLPOINTER_EXCEPTION, (unsigned int)ptTagCursor->ptNext, 0, 0, RDP_FILTER_ID);
        return NULL;
    }
    dwCurrentTime = (GET_READER_BOOT_TIME_MS() / 1000);
    memset((void *)ptTagCursor->ptNext, 0, sizeof(T_RdpTagReportFilterHashEntry));
    ptTagCursor->ptNext->dwCreatTime = (unsigned long long)dwCurrentTime;
    ptTagCursor->ptNext->dwROSpecId = 0;
    ptTagCursor->ptNext->dwAccessId = ptAccessTagReport->dwAccessSpecID;
    ptTagCursor->wAllOpResult = RDP_SUCCESS;
    memcpy(&(ptTagCursor->ptNext->tRdpLlrpUID), &(ptSignalReportCtrl->tUID),
           sizeof(ptTagCursor->ptNext->tRdpLlrpUID));
    ptTagCursor->ptNext->wNumOfOpSpect = ptAccessTagReport->dwOpNum;
    /*记录每个op 的操作结果*/
    for (wLoop = 0;wLoop < ptAccessTagReport->dwOpNum;wLoop++)
    {
        ptTagCursor->ptNext->dwOpResult[wLoop] = ptAccessTagReport->tListofOpResultCtrl[wLoop].wResult;
        if (RDP_SUCCESS != ptTagCursor->ptNext->dwOpResult[wLoop])
        {
            ptTagCursor->ptNext->wAllOpResult = RDP_FAILED;
        }
    }

    ptTagCursor->ptNext->ptLast = ptTagCursor;
    ptTagCursor->ptNext->ptNext = NULL;

    RdpReportDbgPrint(" make a node success in TagAOReportFilterHashInsert\r\n ");
    return ptTagCursor->ptNext;

}
/**************************************************************************
* 函数名称：report_findAOReportFilterHashNode
* 功能描述：查找上报过滤数据库
* 访问的表：上报过滤数据库hash表
* 修改的表：
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle 上报过滤数据库头结点
                              unsigned int dwKey hash表key值
                              T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl 标签报告
* 输出参数：无
* 返 回 值：T_RdpTagReportFilterHashEntry 查到的上报过滤结点
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static T_RdpTagReportFilterHashEntry *report_findAOReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
        unsigned int dwKey,
        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl)
{
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;

    RdpReportDbgPrint("dwKey = %d\r\n", dwKey);
    RdpReportDbgPrint("ptTagReportFilterHandle = 0x%x\r\n", ptTagReportFilterHandle);
    RdpReportDbgPrint("ptTagReportFilterHandle[dwKey] = 0x%x\r\n", &ptTagReportFilterHandle[dwKey]);

    if (NULL == ptTagReportFilterHandle[dwKey].ptNext)
    {
        RdpReportDbgPrint("there is not the Tag TagAOReportFilterHashFind\r\n");
        return NULL;
    }

    for (ptTagCursor = ptTagReportFilterHandle[dwKey].ptNext; NULL != ptTagCursor; ptTagCursor = ptTagCursor->ptNext)
    {
        RdpReportDbgPrint("[savor]:in tagReportFilterHashFind ptTagCursor = %u\r\n", ptTagCursor);


        if (ptTagCursor->tRdpLlrpUID.wTagDataLen != ptSignalReportCtrl->tUID.wTagDataLen)
        {
            continue;
        }

        if (memcmp(ptTagCursor->tRdpLlrpUID.aucTagData,
                   ptSignalReportCtrl->tUID.aucTagData, ptTagCursor->tRdpLlrpUID.wTagDataLen) != 0)
        {
            continue;
        }

        if (ptTagCursor->dwAccessId != ptSignalReportCtrl->tRdpLlrpTagReport.tAccessTagReport.dwAccessSpecID)
        {
            continue;
        }

        break;
    }

    return ptTagCursor;
}

/**************************************************************************
* 函数名称：report_refreshRoReportFilterNode
* 功能描述：更新上报过滤数据库
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle 上报过滤数据库头结点
                              T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl 标签报告
* 输出参数：无
* 返 回 值：0 上报 其他删除
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
unsigned int report_refreshRoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHashHandle,
                                        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl)
{
    unsigned long long dwCurrentTime;
    unsigned int dwHashKey = 0;
    unsigned long long dwJudgeTime = 0;
    unsigned short int wLoop = 0;
    T_RdpTagReportFilterHashEntry *ptTagReportFilterCursor = NULL;

    RdpReportDbgPrint("[savor]:this is RO report\r\n");
    dwHashKey = rdp_calcHashKey(&(ptSignalReportCtrl->tUID), HASHTABLE_LENGTH);
    for (wLoop = 0;wLoop < ptSignalReportCtrl->tUID.wTagDataLen;wLoop++)
    {
        RdpDbgPrintRaw("UID[%d]=0x%02x \r\n", wLoop, ptSignalReportCtrl->tUID.aucTagData[wLoop]);
    }
    RdpReportDbgPrint("\r\n");
    ptTagReportFilterCursor = report_findRoReportFilterHashNode(ptTagReportFilterHashHandle, dwHashKey, ptSignalReportCtrl);
    if (NULL != ptTagReportFilterCursor)
    {
        /*如果不为空，则寻找是否有缓存报告，以及缓存报告是否在允许的时间内*/
        dwCurrentTime = (GET_READER_BOOT_TIME_MS() / 1000);
        dwJudgeTime = (unsigned long long)dwCurrentTime;
        RdpReportDbgPrint("dwJudgeTime  = %lld,ptTagReportFilterCursor->dwCreatTime+ ucTagReportTime = %lld\r\n", dwJudgeTime, (unsigned long long)(ptTagReportFilterCursor->dwCreatTime + g_ucTagReportTime));

        if (dwJudgeTime > (ptTagReportFilterCursor->dwCreatTime + g_ucTagReportTime))  //5为配置的时间，单位是秒
        {
            /*超时间了，重新填写上报时间*/
            RdpReportDbgPrint("time is out of range,report RO\r\n");
            ptTagReportFilterCursor->dwCreatTime = dwJudgeTime;
            return RDP_SUCCESS;
        }
        else
        {
            ptTagReportFilterCursor->dwCreatTime = dwJudgeTime;
            RdpReportDbgPrint("time is not out of range,do not report RO\r\n");
            return RDP_FAILED;
        }
    }
    else
    {
        ptTagReportFilterCursor = report_insertRoReportFilterHashNode(ptTagReportFilterHashHandle, dwHashKey, ptSignalReportCtrl);

        if (NULL == ptTagReportFilterCursor)
        {
            RdpReportDbgPrint("[RO]:*ptTagReportFilterCursorSet can not malloc mem\r\n");
        }
        RdpReportDbgPrint("[savor]:new node address is %u\r\n", ptTagReportFilterCursor);
        return RDP_SUCCESS;
    }
}

/**************************************************************************
* 函数名称：report_refreshAoReportFilterNode
* 功能描述：更新上报过滤数据库
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle 上报过滤数据库头结点
                              T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl 标签报告
* 输出参数：无
* 返 回 值：0 上报 其他删除
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/ 
/*lint -efunc(420,TagAoReportFilterRefresh)*/
unsigned int report_refreshAoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHashHandle,
                                        T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl)
{
    unsigned long long dwCurrentTime;
    unsigned int dwHashKey = 0;
    unsigned long long dwJudgeTime;
    unsigned int dwIndex;
    unsigned int dwResult = RDP_FAILED;
    unsigned short int wLoop = 0;
    T_RdpTagReportFilterHashEntry *ptTagReportFilterCursor = NULL;
    T_RdpLlrpAccessTagReport *ptTempAccessTagReportData = NULL;

    RdpReportDbgPrint("[report_refreshAoReportFilterNode]:this is AO report\r\n");
    ptTempAccessTagReportData = &(ptSignalReportCtrl->tRdpLlrpTagReport.tAccessTagReport);
    dwHashKey = rdp_calcHashKey(&(ptSignalReportCtrl->tUID), HASHTABLE_LENGTH);
    RdpReportDbgPrint("dwHashKey=%d\r\n", dwHashKey);
    for (wLoop = 0;wLoop < ptSignalReportCtrl->tUID.wTagDataLen;wLoop++)
    {
        RdpDbgPrintRaw("UID[%d]=0x%02x \r\n", wLoop, ptSignalReportCtrl->tUID.aucTagData[wLoop]);
    }
    RdpReportDbgPrint("\r\n");
    ptTagReportFilterCursor = report_findAOReportFilterHashNode(ptTagReportFilterHashHandle,
                              dwHashKey, ptSignalReportCtrl);

    if (NULL != ptTagReportFilterCursor)
    {

        dwCurrentTime = (GET_READER_BOOT_TIME_MS() / 1000);
        dwJudgeTime = (unsigned long long)dwCurrentTime;
        RdpReportDbgPrint("dwCurrentTime  = %lld,ptTagReportFilterCursor->dwCreatTime = %lld,g_ucTagReportTime = %d\r\n",
                          dwJudgeTime, ptTagReportFilterCursor->dwCreatTime, g_ucTagReportTime);

        if (dwJudgeTime > (ptTagReportFilterCursor->dwCreatTime + g_ucTagReportTime))  //5为配置的时间，单位是秒
        {
            /*超时间了，重新填写上报时间*/
            RdpReportDbgPrint("[AO]:outof time report AO\r\n");
            ptTagReportFilterCursor->dwCreatTime = dwJudgeTime;
            return RDP_SUCCESS;
        }
        else
        {
            /*判断之前的是否是成功，若是，则不发，若不是，而当前是则发，并更新*/
            RdpReportDbgPrint("[AO]:not outof time ptTagReportFilterCursor->wAllOpResult=%d\r\n", ptTagReportFilterCursor->wAllOpResult);
            if (RDP_SUCCESS != ptTagReportFilterCursor->wAllOpResult)
            {
                for (dwIndex = 0; dwIndex < ptTagReportFilterCursor->wNumOfOpSpect; dwIndex++)
                {
                    if (RDP_SUCCESS != ptTempAccessTagReportData->tListofOpResultCtrl[dwIndex].wResult)
                    {
                        RdpReportDbgPrint("exist failed op\r\n");
                        break;
                    }
                }

                if (dwIndex == ptTagReportFilterCursor->wNumOfOpSpect)
                {
                    RdpReportDbgPrint("[AO]:all is succssful report AO\r\n");
                    ptTagReportFilterCursor->wAllOpResult = RDP_SUCCESS;
                    ptTagReportFilterCursor->dwCreatTime = dwJudgeTime;
                    return RDP_SUCCESS;
                }
                else //判断一下这次的OP失败是否与上次的OP操作相同，如果有上次OP的成功，则发送
                {
                    for (dwIndex = 0; dwIndex < ptTagReportFilterCursor->wNumOfOpSpect; dwIndex++)
                    {
                        /*如果两者不相等，则是这次成功了，上次没有成功，则上报，并重新打时间戳*/
                        if (RDP_SUCCESS != ptTagReportFilterCursor->dwOpResult[dwIndex]
                                && RDP_SUCCESS == ptTempAccessTagReportData->tListofOpResultCtrl[dwIndex].wResult)
                        {
                            RdpReportDbgPrint("[AO]:last is wrong now is right report AO\r\n");
                            ptTagReportFilterCursor->dwOpResult[dwIndex] = RDP_SUCCESS;
                            ptTagReportFilterCursor->dwCreatTime = dwJudgeTime;
                            dwResult = RDP_SUCCESS;
                        }
                    }

                    for (dwIndex = 0; dwIndex < ptTagReportFilterCursor->wNumOfOpSpect; dwIndex++)
                    {
                        if (RDP_SUCCESS != ptTagReportFilterCursor->dwOpResult[dwIndex])
                        {
                            break;
                        }
                    }

                    if (dwIndex == ptTagReportFilterCursor->wNumOfOpSpect)
                    {
                        ptTagReportFilterCursor->wAllOpResult = RDP_SUCCESS;
                    }
                    return dwResult;
                }
            }
            else
            {
                RdpReportDbgPrint("all success but time is not out of range,do not report AO\r\n");
                ptTagReportFilterCursor->dwCreatTime = dwJudgeTime;
                return RDP_FAILED;
            }
        }
    }
    /*如果操作都完成 返回错误*/
    else
    {
        ptTagReportFilterCursor = report_insertAoReportFilterHashNode(ptTagReportFilterHashHandle,
                                  dwHashKey, ptSignalReportCtrl);

        if (NULL == ptTagReportFilterCursor)
        {
            RdpReportDbgPrint("[AO]:report_insertAoReportFilterHashNode can not malloc mem\r\n");
            return RDP_SUCCESS;
        }
        return RDP_SUCCESS;
    }
}

/**************************************************************************
* 函数名称：report_startReportFilterTimer
* 功能描述：开启上报过滤数据库结点轮循删除定时器
* 访问的表：
* 修改的表：
* 输入参数：unsigned char ucDeleteTime删除周期时间单位为秒
* 输出参数：无
* 返 回 值：
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static void report_startReportFilterTimer(unsigned char ucDeleteTime)
{
    RdpReportDbgPrint("StartTagReportFilterTimer ucDeleteTime =%d\r\n", ucDeleteTime);
    RDPStartTimer(EV_RDP_REPORT_TAGTRPORT_FILTER_TIMER, ucDeleteTime * 1000);
}
#if 0 
/**************************************************************************
* 函数名称：report_stopReportFilterTimer
* 功能描述：停止上报过滤数据库结点轮循删除定时器
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：无
* 返 回 值：
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static void report_stopReportFilterTimer()
{
    RDPStopTimer(EV_RDP_REPORT_TAGTRPORT_FILTER_TIMER);
}
#endif

/**************************************************************************
* 函数名称：report_freeRoReportFilterNode
* 功能描述：删除RO上报过滤数据库结点
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle:上报过滤数据库链表指针
*                            unsigned int dwROSpecID RO id
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/03    V1.0       lzy        创建
**************************************************************************/
unsigned int report_freeRoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
                                     unsigned int dwROSpecID)
{
    unsigned int dwHashIndex = 0;
    T_RdpTagReportFilterHashEntry *ptTagHashHandle = NULL;
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;
    T_RdpTagReportFilterHashEntry *ptTagFreeNode = NULL;

    if ((0 == g_ucTagReportTime) || (NULL == ptTagReportFilterHandle))
    {
        RdpReportDbgPrint(" report_freeRoReportFilterNode tag filter node handle is null\r\n ");
        return RDP_FAILED;
    }

    ptTagHashHandle = ptTagReportFilterHandle;
    RdpReportDbgPrint("delete ROSpecID %d TagReportFilter Record\r\n", dwROSpecID);
    if (0 == dwROSpecID)
    {
        /*删除所有RO*/
        for (dwHashIndex = 0 ; dwHashIndex < HASHTABLE_LENGTH; dwHashIndex++)
        {
            for (ptTagCursor = ptTagHashHandle[dwHashIndex].ptNext; NULL != ptTagCursor;)
            {
                /*尾节点*/

                if (0 != ptTagCursor->dwROSpecId)
                {
                    RdpReportDbgPrint("the node is build by ROSpecID =%d,need free\r\n", dwROSpecID);

                    if (ptTagCursor->ptNext == NULL)
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                    }
                    else
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                        ptTagCursor->ptNext->ptLast = ptTagCursor->ptLast;
                    }

                    /*给free临时节点*/
                    ptTagFreeNode = ptTagCursor;
                    /*先指向下一个节点 在free*/
                    ptTagCursor = ptTagCursor->ptNext;
                    free(ptTagFreeNode);
                }
                else
                {
                    ptTagCursor = ptTagCursor ->ptNext;
                }
            }
        }
    }
    else
    {
        for (dwHashIndex = 0 ; dwHashIndex < HASHTABLE_LENGTH; dwHashIndex++)
        {
            for (ptTagCursor = ptTagHashHandle[dwHashIndex].ptNext; NULL != ptTagCursor;)
            {
                /*尾节点*/

                if (ptTagCursor->dwROSpecId == dwROSpecID)
                {
                    RdpReportDbgPrint("the node is build by ROSpecID =%d,need free\r\n", dwROSpecID);

                    if (ptTagCursor->ptNext == NULL)
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                    }
                    else
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                        ptTagCursor->ptNext->ptLast = ptTagCursor->ptLast;
                    }

                    /*给free临时节点*/
                    ptTagFreeNode = ptTagCursor;
                    /*先指向下一个节点 在free*/
                    ptTagCursor = ptTagCursor->ptNext;
                    free(ptTagFreeNode);
                }
                else
                {
                    ptTagCursor = ptTagCursor ->ptNext;
                }
            }
        }
    }
    return RDP_SUCCESS;
}
/**************************************************************************
* 函数名称：report_freeAoReportFilterNode
* 功能描述：删除AO上报过滤数据库结点
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle:上报过滤数据库链表指针
*                            unsigned int dwAccessID AO id
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/03    V1.0       lzy        创建
**************************************************************************/
unsigned int report_freeAoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
                                     unsigned int dwAccessID)
{
    unsigned int dwHashIndex = 0;
    T_RdpTagReportFilterHashEntry *ptTagHashHandle = NULL;
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;
    T_RdpTagReportFilterHashEntry *ptTagFreeNode = NULL;

    if ((0 == g_ucTagReportTime) || (NULL == ptTagReportFilterHandle))
    {
        RdpReportDbgPrint(" report_freeAoReportFilterNode tag filter node handle is null\r\n ");
        return RDP_FAILED;
    }

    ptTagHashHandle = ptTagReportFilterHandle;
    RdpReportDbgPrint("delete AOSpecID %d TagReportFilter Record\r\n", dwAccessID);

    if (0 == dwAccessID)
    {
        /*删除所有结点*/
        for (dwHashIndex = 0 ; dwHashIndex < HASHTABLE_LENGTH; dwHashIndex++)
        {
            for (ptTagCursor = ptTagHashHandle[dwHashIndex].ptNext; NULL != ptTagCursor;)
            {
                /*尾节点*/

                if (0 != ptTagCursor->dwAccessId)
                {
                    RdpReportDbgPrint("the node is build by AOSpecID =%d,need free\r\n", dwAccessID);

                    if (NULL == ptTagCursor->ptNext)
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                    }
                    else
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                        ptTagCursor->ptNext->ptLast = ptTagCursor->ptLast;
                    }

                    /*给free临时节点*/
                    ptTagFreeNode = ptTagCursor;
                    /*先指向下一个节点 在free*/
                    ptTagCursor = ptTagCursor->ptNext;
                    free(ptTagFreeNode);
                }
                else
                {
                    ptTagCursor = ptTagCursor ->ptNext;
                }
            }
        }
    }
    else
    {

        for (dwHashIndex = 0 ; dwHashIndex < HASHTABLE_LENGTH; dwHashIndex++)
        {
            for (ptTagCursor = ptTagHashHandle[dwHashIndex].ptNext; NULL != ptTagCursor;)
            {
                /*尾节点*/

                if (ptTagCursor->dwAccessId == dwAccessID)
                {
                    RdpReportDbgPrint("the node is build by AOSpecID =%d,need free\r\n", dwAccessID);

                    if (NULL == ptTagCursor->ptNext)
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                    }
                    else
                    {
                        ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                        ptTagCursor->ptNext->ptLast = ptTagCursor->ptLast;
                    }

                    /*给free临时节点*/
                    ptTagFreeNode = ptTagCursor;
                    /*先指向下一个节点 在free*/
                    ptTagCursor = ptTagCursor->ptNext;
                    free(ptTagFreeNode);
                }
                else
                {
                    ptTagCursor = ptTagCursor ->ptNext;
                }
            }
        }
    }
    return RDP_SUCCESS;
}

/**************************************************************************
* 函数名称：report_tagReportFilter_PollingClear
* 功能描述：轮循删除上报过滤数据库结点
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle:上报过滤数据库链表指针
* 输出参数：无
* 返 回 值：0 成功 其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
unsigned int report_dealReportFilter_PollingClear(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle)
{
    unsigned int dwHashIndex = 0 ;
    unsigned long long dwCurrentTime;
    unsigned long long dwTimeNow = 0;
    T_RdpTagReportFilterHashEntry *ptTagHashHandle = NULL;
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;
    T_RdpTagReportFilterHashEntry *ptTagFreeNode = NULL;
    dwCurrentTime = (GET_READER_BOOT_TIME_MS() / 1000);
    dwTimeNow = (unsigned)(long long)dwCurrentTime;
    if (NULL == ptTagReportFilterHandle )
    {
        RdpReportDbgPrint("the TagReportFilterHashHandle is null  need not release node\r\n");
        RDP_EXCEPT(RDP_MSG_PROC_ERROR, 0, 0, 0, RDP_FILTER_ID);
        return RDP_FAILED;
    }
    ptTagHashHandle = ptTagReportFilterHandle;

    for (dwHashIndex = 0 ; dwHashIndex < HASHTABLE_LENGTH; dwHashIndex++)
    {
        for (ptTagCursor = ptTagHashHandle[dwHashIndex].ptNext; NULL != ptTagCursor;)
        {
            /*尾节点*/

            RdpReportDbgPrint("g_ucTagReportTime=%d,ptTagCursor=0x%x,dwHashIndex=%d\r\n",
                              (unsigned int)g_ucTagReportTime, ptTagCursor, dwHashIndex);

            if (ptTagCursor->dwCreatTime + g_ucTagReportTime < dwTimeNow)
            {
                RdpReportDbgPrint("the node is out of timeof live in TagReportFilterClear ptTagCursor=0x%x\r\n",
                                  ptTagCursor);

                if (NULL == ptTagCursor->ptNext)
                {
                    ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                }
                else
                {
                    ptTagCursor->ptLast->ptNext = ptTagCursor->ptNext;
                    ptTagCursor->ptNext->ptLast = ptTagCursor->ptLast;
                }

                /*给free临时节点*/
                ptTagFreeNode = ptTagCursor;
                /*先指向下一个节点 在free*/
                ptTagCursor = ptTagCursor->ptNext;
                free(ptTagFreeNode);
            }
            else
            {
                ptTagCursor = ptTagCursor ->ptNext;
            }
        }
    }

    report_startReportFilterTimer(g_ucTagReportDeleteTime);
    return RDP_SUCCESS;
}
/**************************************************************************
* 函数名称：report_constructReportFilterMemory
* 功能描述：创建上报过滤数据库存储区
* 访问的表：
* 修改的表：
* 输入参数：无
* 输出参数：无
* 返 回 值：0 成功  其他失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/06    V1.0       lzy        创建
**************************************************************************/
static unsigned int report_constructReportFilterMemory()
{
    unsigned int dwRet = RDP_SUCCESS;
    if (FALSE == g_tRdpAdvancedConfig.tTagFilterCfg.ucTurnOnRFFilter)
    {
        return RDP_FAILED;
    }
    if (NULL == g_ptRdpTagReportFilterHashEntry)
    {
        g_ptRdpTagReportFilterHashEntry = report_initReportFilterHashTable();

        if (NULL == g_ptRdpTagReportFilterHashEntry)
        {
            /*申请内存失败，则关闭上报过滤操作*/
            RDP_EXCEPT(RDP_BUF_NO_SPARE_MEM, 0, 0, 0, RDP_FILTER_ID);
            RdpReportDbgPrint("[RDP]:tagReport HASH malloc is failed,so shut down the op\r\n");
            dwRet = RDP_FAILED;
        }
        else
        {
            RdpReportDbgPrint("[RDP]:tagReport HASH malloc is successfule,,ptg_TagReportFilterHashHandle = %u\r\n",
                              g_ptRdpTagReportFilterHashEntry);
            dwRet = RDP_SUCCESS;
        }
    }
    else
    {
        dwRet = RDP_FAILED;
        RDP_EXCEPT(RDP_BUF_NO_SPARE_MEM, 0, 0, 0, RDP_FILTER_ID);
        RdpReportDbgPrint("[RDP]:ptg_TagReportFilterHashHandle should be NULL,but now is NO\r\n");
    }
    return dwRet;
}
/**************************************************************************
* 函数名称：report_dealReportFilterMemory
* 功能描述：处理上报过滤数据库存储区
* 访问的表：
* 修改的表：
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/06    V1.0       lzy        创建
**************************************************************************/
void report_dealReportFilterMemory()
{
    unsigned int dwRet = RDP_SUCCESS;
    if (TRUE == g_tRdpAdvancedConfig.tTagFilterCfg.ucTurnOnRFFilter)
    {
        /*需要删除所有的动态内存*/
        dwRet = report_constructReportFilterMemory();
        if (RDP_SUCCESS == dwRet)
        {
            g_ucTagReportTime = g_tRdpAdvancedConfig.tTagFilterCfg.ucRFKeepaliveTime;
            g_ucTagReportDeleteTime = TAGFILTER_RFPOLLTIME;
        }
        else
        {
            g_ucTagReportTime = 0;
            g_ucTagReportDeleteTime = 0;
        }
    }
    else
    {
        g_ucTagReportTime = 0;
        g_ucTagReportDeleteTime = 0;
    }
    report_startReportFilterTimer(g_ucTagReportDeleteTime);
    return ;
}
/**************************************************************************
* 函数名称：report_insertRoReportFilterHashNode
* 功能描述：将结点插入到上报过滤数据库
* 访问的表：上报过滤数据库hash表
* 修改的表：上报过滤数据库hash表
* 输入参数：T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle 上报过滤数据库头结点
                              unsigned int dwKey hash表key值
                              T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl 标签报告
* 输出参数：无
* 返 回 值：T_RdpTagReportFilterHashEntry 插入的上报过滤结点
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
* 12/03/02    V1.0       lzy        创建
**************************************************************************/
static T_RdpTagReportFilterHashEntry *report_insertRoReportFilterHashNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle, unsigned int dwKey, T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl)
{
    unsigned long long dwCurrentTime;
    T_RdpTagReportFilterHashEntry *ptTagCursor = NULL;

    for (ptTagCursor = &ptTagReportFilterHandle[dwKey]; NULL != ptTagCursor->ptNext; ptTagCursor = ptTagCursor->ptNext)
    {
        ;
    }

    ptTagCursor->ptNext = (T_RdpTagReportFilterHashEntry *)malloc(sizeof(T_RdpTagReportFilterHashEntry)) ;

    if (NULL == ptTagCursor->ptNext)
    {
        RdpReportDbgPrint(" report_insertRoReportFilterHashNode malloc failed \r\n ");
        RDP_EXCEPT(RDP_MSG_PROC_ERROR, 0, 0, 0, RDP_FILTER_ID);
        return NULL;
    }

    memset((void *)ptTagCursor->ptNext, 0, sizeof(T_RdpTagReportFilterHashEntry));
    dwCurrentTime = (GET_READER_BOOT_TIME_MS() / 1000);
    ptTagCursor->ptNext->dwCreatTime = (unsigned long long)dwCurrentTime;
    ptTagCursor->ptNext->dwROSpecId = ptSignalReportCtrl->tRdpLlrpTagReport.tROTagReport.dwROSpecID;
    ptTagCursor->ptNext->dwAccessId = 0;
    memcpy(&(ptTagCursor->ptNext->tRdpLlrpUID), &(ptSignalReportCtrl->tUID), sizeof(ptTagCursor->ptNext->tRdpLlrpUID));
    ptTagCursor->ptNext->ptLast = ptTagCursor;
    ptTagCursor->ptNext->ptNext = NULL;

    RdpReportDbgPrint(" make a node success in report_insertRoReportFilterHashNode\r\n ");
    return ptTagCursor->ptNext;

}
