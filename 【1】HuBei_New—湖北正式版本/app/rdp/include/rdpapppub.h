/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： UhfRdp.h
* 文件标识： 
* 内容摘要：RDP 内部公共头文件
* 其它说明： 
* 当前版本： 
* 作    者： lzy
* 完成日期： 2012.03.08
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _UHF_RDP_H
#define _UHF_RDP_H
#include "uhfllrpRule.h"

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
 /*删除RO对应的过滤结点*/
#define RDP_DELETE_FILTER_TYPE_RO  1

 /*删除AO对应的过滤结点*/
#define RDP_DELETE_FILTER_TYPE_AO  2

#define MAX_GPI_NUM 7
#define MAX_GPO_NUM 7


/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
 
 /*删除过滤结点消息结构体*/
 typedef struct tagT_RdpDeleteFilterNodes
{
    unsigned char ucDeleteType;         /*删除类型0:RO,1:AO*/
    unsigned char ucPad[3];
    unsigned int dwRoOrAoId;     /*RO或者AO对应的ID*/
}T_RdpDeleteFilterNodes;

typedef struct tagT_WriteOpFilter
{
    unsigned short int wAddress;
    unsigned short int wLength;

}
T_RemainWriteOp;

typedef struct tagT_ReadOpFilter
{

    unsigned short int wAddress;
    unsigned short int wLength;

}
T_RemainReadOp;

typedef union tagT_RemainOp
{
    T_RemainReadOp tRemainReadOp;
    T_RemainWriteOp tRemainWriteOp;
}T_RemainOp;

/*每个op的结果信息*/
typedef struct tagT_RdpOpResult
{
    unsigned char ucOpResult;/*OP操作结果*/
    T_RemainOp tRemainOp;/*op剩余读写长度*/
}T_RdpOpResult;

/*操作过滤中op结果信息*/
typedef struct tagT_RdpOpFilterControl
{
    unsigned char ucOpNum;/*op个数*/
    unsigned char ucPad;
    unsigned short int wPad;
    T_RdpOpResult tOpResult[MAX_NUM_OPSPECS_PER_ACCESSSPEC];/*每个op的操作结果*/
}T_RdpOpFilterCtrl;


/*操作过滤结点结构*/
typedef struct tagT_RdpOpFilterHashEntry
{
     struct tagT_RdpOpFilterHashEntry *ptNext;/*指向下一个结点*/
     struct tagT_RdpOpFilterHashEntry *ptLast;/*指向前一个结点*/
    T_RdpOpFilterCtrl tOpFilterCtrl;/*op控制信息*/
    unsigned long long dwCreatTime;/*操作过滤结点创建时间*/
    unsigned long long dwOperateTime;/*操作过滤结点操作时间*/
    T_RdpLlrpSingleReportCtrl              *ptSignalReportCtrl;/*结点报告*/
    unsigned char                                           ucLinkIndex;/*链路索引*/
    unsigned char                                           ucLinkType;/*链路类型*/
    unsigned short int                        wHasSend;
    unsigned int                         dwAccessId;/*AO id*/
    unsigned int                         dwMessageID;/*Messge id*/
    unsigned short int                         wSendTno;/*向后台发送的模块号*/
    T_RdpLlrpUID                        tRdpLlrpUID;/*唯一标识*/
}T_RdpOpFilterHashEntry;


/**************************************************************************
 *                             类声明                                      *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/
extern unsigned int g_bRdpPowerOnCfgFinish;
extern T_RdpConfig g_tRdpConfig;
extern T_RdpLlrpReaderDispatch g_tRdpLlrpReaderDispatch;
/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
unsigned int rdp_calcHashKey(T_RdpLlrpUID *ptRdpLlrpUID, unsigned short int HashTableLength);

void report_constructAccessReport(LLRP_tSTagReportData *ptTagReportData,T_RdpLlrpSingleReportCtrl *ptSignalReportCtrl);
void llrp_buildAnNodeFoDynamicAccessQueue(T_RdpLlrpDynamicAccess *ptQueueHead,LLRP_tSADD_ACCESSSPEC *ptAddAccessAddr);
void  llrp_deleteAnNodeForDynamicAccessQueue(T_RdpLlrpDynamicAccess *ptQueueHead,unsigned int dwAccessID);

#endif  /* _RDP_REPORT_H */

