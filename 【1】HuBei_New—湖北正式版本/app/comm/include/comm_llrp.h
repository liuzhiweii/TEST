#ifndef __COMM_LLRP__
#define __COMM_LLRP__

typedef struct tagT_Msg
{
    long        mtype;          /* Message type, used by linux */
    unsigned char        ucLinkType;     /* 链路物理类型 */
    unsigned char        ucLinkIndex;    /* 链路索引号 */
    unsigned short      wSenderTno;     /* 发送端任务号 */
    unsigned short      wReceiverTno;   /* 接收端任务号 */    
    unsigned short      wMsgID;         /* 消息事件号 */
    unsigned short      wMsgLen;        /* 消息长度，不包括消息头，BYTE为单位 */
    unsigned short      wMsgSequence;   /* 消息序号 */ 
    unsigned short      wSrcTno;        /* 源任务号 */
    unsigned short      wDstTno;        /* 目的任务号 */
    unsigned short      wRelayMagic;    /* 中继消息魔术字 */
    unsigned short      wPad;
}T_Msg;



#endif


