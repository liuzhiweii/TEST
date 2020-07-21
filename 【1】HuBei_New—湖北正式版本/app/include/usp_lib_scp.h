/************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_lib_scp.h
* 文件标识： 
* 内容摘要： 系统主控动态库对外接口
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
#ifndef _USP_LIB_SCP_H
#define _USP_LIB_SCP_H

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
#define USP_LIB_SUCCESS             (0)

/* 检查句柄是否合法 */
#define USP_LIB_CHECK_HANDLE(handle, member) if (NULL == handle || 0x5A5A5A5A != handle->dwMagic || NULL == (handle)->member) return -1

/* 定义进程间通信选项 */
#define USP_LIB_IPC_NOWAIT          USP_LIB_VOS_IPC_NOWAIT         /* 立即返回，不阻塞 */
#define USP_LIB_IPC_FOREVERWAIT     USP_LIB_VOS_IPC_FOREVERWAIT    /* 阻塞 */

/* 单条消息最大长度 */
#define USP_LIB_IPC_MSG_MAX_SIZE    (8 * 1024)

/* 消息类型定义 */
#define USP_LIB_SCP_MSG_TYPE_GPIO   0       /* GPIO相关消息 */
#define USP_LIB_SCP_MSG_TYPE_OTHER  0xFF    /* 其他消息 */

/* 消息序号自增 */
#define USP_LIB_SCP_MSGSEQ(n)       (0xFFFF == (++(n)) ? ++(n) : (n))

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                            数据类型                                    *
 **************************************************************************/
/* SCP操作句柄抽象数据类型 */
typedef struct tagT_ScpLibHandle    *USPLibScpHandle;

/* 通信消息抽象数据类型 */
typedef struct tagT_Msg             *USPLibScpMsg;

/* 任务标识抽象数据类型 */
typedef WORD16                       USPLibScpTno;

/* 解析后的消息信息结构 */
typedef struct tagT_USPLibScpAnalyseMsg
{
    WORD16  wMsgType;   /* 消息类型 */
    WORD16  wPad;
}T_USPLibScpAnalyseMsg;

/* CPU内进程间通信消息头 */
typedef struct tagT_USPLibScpMsg
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
}T_USPLibScpMsg;

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/

/* 打开USP动态库 */
extern WORD32 usp_lib_open(USPLibHandle *pHandle, BYTE *pucDesc);

/* 关闭USP动态库 */
extern WORD32 usp_lib_close(USPLibHandle handle);

/* 打开USP动态库(包含子模块全部打开) */
extern WORD32 usp_lib_openAll(USPLibHandle * pHandle, BYTE * pucDesc);

/* 关闭USP动态库(包含子模块全部关闭) */
extern WORD32 usp_lib_closeAll(USPLibHandle handle);

/* 打开SCP模块 */
extern WORD32 usp_lib_scp_open(USPLibHandle handle, BYTE *pucDesc);

/* 关闭SCP模块 */
extern WORD32 usp_lib_scp_close(USPLibHandle handle);

/* 获取任务号 */
extern WORD32 usp_lib_scp_getTno(USPLibHandle handle, USPLibScpTno *pTno);

/* 向指定的任务号发送消息 */
extern WORD32 usp_lib_scp_sendTaskMsg(USPLibHandle handle, USPLibScpTno tno, USPLibScpMsg msg, WORD32 dwFlag);

/* 接收消息（从消息队列中顺序读取消息） */
extern WORD32 usp_lib_scp_recvMsg(USPLibHandle handle, USPLibScpMsg msg, WORD16 wSize, WORD32 dwFlag);

/* 接收特定类型的消息 */
extern WORD32 usp_lib_scp_recvMsgWithTypes(USPLibHandle handle, USPLibScpMsg msg, WORD16 wSize, WORD32 dwTimeOut, USPLibScpMsg aExpectMsg[]);

/* 复位阅读器 */
extern WORD32 usp_lib_scp_reset(USPLibHandle handle);

/* 设置阅读器时间 */
extern WORD32 usp_lib_scp_setTime (USPLibHandle handle, WORD32 dwTime);

/* 获取阅读器时间 */
extern WORD32 usp_lib_scp_getTime (USPLibHandle handle, WORD32 *pdwTime);

/* 解析消息 */
extern WORD32 usp_lib_scp_analyseMsg(USPLibScpMsg msg, T_USPLibScpAnalyseMsg *ptAnalyseMsg);

#endif  /* _USP_LIB_SCP_H */

