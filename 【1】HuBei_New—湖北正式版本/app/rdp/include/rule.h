/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： Report.h
* 文件标识： 
* 内容摘要：report模块内部头文件
* 其它说明： 
* 当前版本： 
* 作    者： lzy
* 完成日期： 2012.02.26
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _RDP_RULE_H
#define _RDP_RULE_H


/**************************************************************************
 *                        常量                                            *
 **************************************************************************/
 #define RDP_CLIENT_REQUEST_OPSPEC_ID 38975
 #define RDP_MAX_LLRP_DEPTH  8

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
 /*消息是否向后走*/
#define  RULE_SENG_MESSAGE_TO_LLRP_YES 0
#define  RULE_SENG_MESSAGE_TO_LLRP_NO 1

/*唯一标识类型*/
#define RDP_IDENTIFY_TYPE_INVENTORY  0
#define RDP_IDENTIFY_TYPE_READOP 1

/*op类型*/
#define RDP_LLRP_C1G2_OPRESULTTYPE_READ         349
#define RDP_LLRP_ISO6B_OPRESULTTYPE_READ         645
#define RDP_LLRP_GB_OPRESULTTYPE_READ         765

#define RDP_LLRP_TAGSPEC_TYPE_EPC 338
#define RDP_LLRP_TAGSPEC_TYPE_ISO6B 635
#define RDP_LLRP_TAGSPEC_TYPE_GB 756

/*报告中标签的协议类型*/
#define RDP_LLRP_TAG_C1G2        241
#define RDP_LLRP_TAG_ISO6B       626
#define RDP_LLRP_TAG_GB       771


/*收发消息*/
#define     RULE_SEND_MSG(socket, msg)     (zmq_send(socket, msg,(T_Msg *)msg->wMsgLen+sizeof(T_Msg),0)<0?1:0)
#define     RULE_RECV_MSG(socket, buf,len) zmq_recv(socket, buf, len, 0)

/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
 /*参数校验错误所需参数*/
 typedef struct tagT_ParameterError
{  
    unsigned int bIsLastField;/*最后一个错误是否是field 错误*/
    unsigned short int wFieldNum;/*field 序号*/
    unsigned short int wLastParameterErrorCode;/*最后一个参数错误的错误码*/
    unsigned short int wFieldErrorCode;/*field错误的错误码*/
    unsigned short int wParameterDepth;/*参数递归深度*/
    unsigned short int wParameterType[7];/*每层参数的类型*/
    unsigned char ErrorDetail[100];/*错误描述*/
}T_ParameterError;

/*AO唯一标识对应表*/
typedef struct tagT_RuleAOIdentifyTable
{
    unsigned char ucIdentifyType;/*0,清点，1读op*/
    unsigned char ucOpSpecId;/*op id*/
    unsigned char ucOpIndex;/*唯一标识所在的opIndex*/
    unsigned char ucPad;
}T_RuleAOIdentifyTable;

/*AO动态链表*/
typedef struct tagT_RuleAODenymicList
{
    unsigned int dwAccessOriginalState;    /*AO状态*/
    T_RuleAOIdentifyTable tRuleAOIdentifyTable;/*AO唯一标识对应*/
     LLRP_tSADD_ACCESSSPEC * pAddAccessspec; /*AO动态结构*/
    struct tagT_RuleAODenymicList *ptNext;/*下一个结点*/
}T_RuleAODenymicList;

/*事件和enable后返回问题；enable先返回，遇到start问题，
 需要RULE和LLRP线程同步，因此引入此结构，将RO校验控制结构放于RULE模块*/
typedef struct tagT_RuleROCtrlAndParam
{
   
    unsigned char       ucLinkIndex; /*判断链路标识*/
    unsigned char       ucLinkType; 
    unsigned char       ucPad[2];
    unsigned int   dwROSpecID;
    unsigned int   dwUseing; //这个结构是否用到	
    LLRP_tEROSpecState  eCurrentState;
}T_RuleROCtrlAndParam;

/**************************************************************************
 *                             类声明                                      *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/
extern T_RdpOpFilterHashEntry *g_ptRdpOpFilterHashEntry;
extern unsigned int g_bReportInitFinish;
extern T_USPRdpAdvancedConfig g_tRdpAdvancedConfig;
/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
unsigned int usp_rdp_rule_Entry();
unsigned int rule_checkAddAccessspec(T_Msg *ptMsg , LLRP_tSADD_ACCESSSPEC *ptLLRP_tSADD_ACCESSSPEC);
unsigned int rule_checkDeleteAccesssSpec(T_Msg *ptMsg, LLRP_tSDELETE_ACCESSSPEC *ptLLRP_tSDELETE_ACCESSSPEC);
unsigned int rule_checkDeleteROSpec(T_Msg *ptMsg, LLRP_tSDELETE_ROSPEC *ptLLRP_tSDELETE_ROSPEC);
unsigned int rule_checkAddROSpec(T_Msg *ptMsg, LLRP_tSADD_ROSPEC *ptLLRPAddRospec);
unsigned int rule_checkDisableAccesssSpec(T_Msg *ptMsg, LLRP_tSDISABLE_ACCESSSPEC *ptLLRP_tSDISABLE_ACCESSSPEC);
unsigned int rule_checkDisableROSpec(T_Msg *ptMsg, LLRP_tSDISABLE_ROSPEC *ptLLRP_tSDISABLE_ROSPEC);
unsigned int rule_checkEnableAccesssSpec(T_Msg *ptMsg, LLRP_tSENABLE_ACCESSSPEC *ptLLRP_tSENABLE_ACCESSSPEC);
unsigned int rule_checkEnableROSpec(T_Msg *ptMsg, LLRP_tSENABLE_ROSPEC *ptLLRP_tSENABLE_ROSPEC);
unsigned int rule_checkStopROSpec(T_Msg *ptMsg, LLRP_tSSTOP_ROSPEC *ptLLRP_tSSTOP_ROSPEC);
unsigned int rule_checkStartROSpec(T_Msg *ptMsg, LLRP_tSSTART_ROSPEC *ptLLRP_tSSTART_ROSPEC);
unsigned int rule_SendMsgToClient(T_Msg *ptReceiveMsg, unsigned int dwMessageID , LLRP_tSMessage *ptLLRP_tSMessage);

#endif  /* _RDP_REPORT_H */

