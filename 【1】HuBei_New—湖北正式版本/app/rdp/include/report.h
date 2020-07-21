/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： Report.h
* 文件标识： 
* 内容摘要：report模块内部头文件
* 其它说明： 
* 当前版本： 
* 作    者： lzy
* 完成日期： 2012.03.07
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _RDP_REPORT_H
#define _RDP_REPORT_H


/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
#define INVENTORY_PERIOD                                    (unsigned int)0
#define INVENTORY_SINGLE                                    (unsigned int)1
#define INDENTIFIER_INVENTORY                               (unsigned int)0
#define INDENTIDIER_READ                                    (unsigned int)1


 /*删除RO对应的过滤结点*/
#define RDP_DELETE_FILTER_TYPE_RO  1

 /*删除AO对应的过滤结点*/
#define RDP_DELETE_FILTER_TYPE_AO  2

/*定义RSSI排序数组个数*/
#define RSSI_SORT_NUM          5

#define REPORT_HAS_SEND_REPORT 1

#define REPORT_HAS_NOT_SEND_REPORT 0

/*RSSI由16位变成8位有符号值转化所需常量*/
#define REPORT_RSSI_CONSTANT_VALUE 85

/*标签过滤轮询时间*/
#define TAGFILTER_OPPOLLTIME 20
#define TAGFILTER_RFPOLLTIME 20
#define TAGFILTER_RFOPERATETIME 5
/*收发消息定义*/
#define     REPORT_SEND_MSG(socket, msg)     zmq_send(socket, msg,(T_Msg *)msg->wMsgLen,0)
#define     REPORT_RECV_MSG(socket, buf,len) zmq_recv(socket, buf, len, 0)

/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/

/*上报过滤内部结构： */
typedef struct tagT_RdpReportFilterHashEntry
{
    struct tagT_RdpReportFilterHashEntry *ptNext;/*指向下一个结点*/
    struct tagT_RdpReportFilterHashEntry *ptLast;/*指向前一个结点*/
    unsigned short int wNumOfOpSpect;/*op个数*/
    unsigned short int wAllOpResult;/*AO中所有op的操作结果指示*/
    unsigned int dwOpResult[8];/*每个op的操作结果*/
    unsigned long long dwCreatTime;/*结点创建时间*/
    unsigned int dwAccessId;/*ao id*/
    unsigned int dwROSpecId;/*ro id*/
    T_RdpLlrpUID tRdpLlrpUID;/*唯一标识*/
}T_RdpTagReportFilterHashEntry;

/*Rssi 相关操数据结构 */
/*Rssi排序的队列*/
typedef struct tagT_RdpRssiQueueNode
{
    unsigned short int wRssiAccmulation;/*Rssi累加值*/
    unsigned short int wPad;
    unsigned int dwRssiBuildTime;/*创建时间*/
    struct tagT_RdpRssiQueueNode *ptNext;/*指向下一个结点*/
    T_RdpLlrpUID tRssiTagId;/*唯一标识*/
}T_RdpRssiQueueNode;

/*Rssi排序队列的控制结构*/
typedef struct tagT_RdpRssiQueueCtrl
{
    unsigned short int wRssiNodeNum;                           /*Rssi结点数*/
    unsigned short int wPad;
    T_RdpRssiQueueNode *ptHeadOfRssiQueue;/*结点头指针*/
    T_RdpRssiQueueNode *ptTailOfRssiQueue;  /*结点尾指针*/
}T_RdpRssiQueueCtrl ;

/*rssi排序内部结构*/
typedef struct tagT_RdpRssiSort
{
    unsigned short int wRssiAccmulation;           /*Rssi累加值*/
    T_RdpLlrpUID tRssiTagId;                /*唯一标识*/
}T_RdpRssiSort;

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
 unsigned int usp_rdp_report_Entry();
unsigned int report_refreshRoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHashHandle, 
                                                                                 T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
unsigned int report_refreshAoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHashHandle,
                                                                                T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
unsigned int report_freeAoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
                                                                         unsigned int dwAccessID);
unsigned int report_freeRoReportFilterNode(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle,
                                                                          unsigned int dwROSpecID);
unsigned int report_dealReportFilter_PollingClear(T_RdpTagReportFilterHashEntry *ptTagReportFilterHandle);
void report_dealReportFilterMemory();
unsigned int report_deleteReportNode(T_RdpLlrpSingleReportCtrl **ptOneReportCursor, T_RdpLlrpSingleReportCtrl **ptSendReportHead);
void report_insertReportNodeInHead(T_RdpLlrpSingleReportCtrl **ptSendReportHead, T_RdpOpFilterHashEntry *ptCurrOpFilterNode);
unsigned int report_insertReportNodeInTail(T_RdpLlrpSingleReportCtrl **ptSendReportHead, 
                                                                         T_RdpLlrpSingleReportCtrl *ptSingleReportCtrl);
LLRP_tSTagReportData *report_constructSingleTagReport(T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
unsigned int report_sendReportMsgAndFree(T_Msg *ptReceiveMsg, unsigned int dwMessageID , LLRP_tSMessage *ptMessage);


#endif  /* _RDP_REPORT_H */

