#ifndef _USP_ISO6B_H
#define _USP_ISO6B_H


#define ISO6B_READLENGTH     (8)
#define ISO6B_BYTE_UNLOCKED  (0)
#define ISO6B_BYTE_LOCKED    (1)

#define ISO6B_CMD_TYPE_READ_8BYTE       (1)
#define ISO6B_CMD_TYPE_READ_VRBLBYTE    (2)
#define ISO6B_CMD_TYPE_LOCK             (3)
#define ISO6B_CMD_TYPE_WRITE_BYTE       (4)
#define ISO6B_CMD_TYPE_WRITE_4BYTE      (5)
#define ISO6B_CMD_TYPE_LOCKQRY          (6)

/* FPGA的ISO18000-6B frame struct */
/* ISO18000-6B协议上报到CPU消息的数据结构
（1）清点消息组帧
     帧格式：帧头/帧长度/消息类型/UID
（2）访问命令响应消息组帧
     帧格式：帧头/帧长度/消息类型/命令类型/UID/接收错误状态指示/标签返回的消息值
（3）清点结束消息
     帧格式：帧头/帧长度/消息类型
 */
#define  FPGA_ISO6B_FRAME_LEN         (0)  /* 帧长度          */
#define  FPGA_ISO6B_FRAME_MSG_TYPE    (1)  /* 消息类型        */
#define  FPGA_ISO6B_FRAME_CMD_TYPE    (2)  /*             */
#define  FPGA_ISO6B_FRAME_UID         (3)  /* UID            */
#define  FPGA_ISO6B_FRAME_RESULT      (7)  /* 接收错误状态指示 */
#define  FPGA_ISO6B_FRAME_TAG_DATA    (8)  /* 标签返回的消息值 */



#define  FPGA_ISO6B_INVENT_FRAME_LEN                       (0)  /* 帧长度          */
#define  FPGA_ISO6B_INVENT_FRAME_MSG_TYPE             (1)  /* 消息类型        */
#define  FPGA_ISO6B_INVENT_FRAME_UID    (2)  /* UID            */
#define  FPGA_ISO6B_INVENT_FRAME_RESULT    (6)  /*  */
#define  FPGA_ISO6B_INVENT_FRAME_DATAREAD_DATA (7)
#define  FPGA_ISO6B_INVENT_FRAME_RSSI   (11)  /*清点结果后面是RSSI的值*/


/* ISO18000-6B协议消息类型：BIT1~BIT0
01：清点消息
10：访问命令消息
11：清点结束消息
*/
#define  FPGA_ISO6B_FRAME_CMD_TYPE_INVENT_MSG         (0x1)
#define  FPGA_ISO6B_FRAME_CMD_TYPE_ACCESS_MSG         (0x2)
#define  FPGA_ISO6B_FRAME_CMD_TYPE_INVENT_FINISH_MSG  (0x3)

/* ISO18000-6B协议接收错误状态指示：BIT3~BIT0
0000：无错误
0001：无信号
0010：前导码不匹配
0100：CRC校验错
1000:     标签内部错误
 */
#define  FPGA_ISO6B_FRAME_RESULT_NO_EEROR             (0x0)
#define  FPGA_ISO6B_FRAME_RESULT_NO_SIGNAL            (0x1)
#define  FPGA_ISO6B_FRAME_RESULT_PREAMBLE_NOT_MATCH   (0x2)
#define  FPGA_ISO6B_FRAME_RESULT_CRC_ERROR            (0x4)
#define  FPGA_ISO6B_FRAME_RESULT_TAG_ERROR              (0x8)


/* ISO18000-6B使用的常量定义 */
#define T_ISO18000_6_B_RCPTagInventoryReponse_fixed_bytes_len (14)  /* 清点响应消息头固定部分字节长度 */
#define T_ISO18000_6_B_RCPTagReadResponse_fixed_bytes_len      (12)  /* 读标签响应消息头固定部分字节长度 */
#define T_ISO18000_6_B_RCPTagWriteResponse_fixed_bytes_len     (10)  /* 写标签响应消息头固定部分字节长度 */

#define ISO_180006B_UID_BYTE_LEN            (8)    /* UID的字节长度 */
#define ISO_180006B_READ_RESPONSE_BYTE_LEN  (8)    /* READ响应的字节长度 */

#define ISO_18000_6B_BUFFER_MAX_TAG_NUM   (256)  /* UID缓存能存最大标签数*/
#define ISO_18000_6B_MAX_TAG_SIZE    (256)  /* 18000_6B标签最大空间 */
#define ISO_18000_6B_TAG_HEAD  (18)  /* 18000_6B标签非用户区大小*/
#define ISO_18000_6B_ZTE_ID       (192)   /* 中兴标识*/
#define ISO_18000_6B_ID_POS  (12) /* 中兴标识在iso标签中的位置*/
#define ISO_18000_6B_USERDATA_SIZE_POS  (13) /*  用户编码有效长度*/

/*此处对应读和写对应的CommandType*/

#define ISO_6B_WRITEBYTE      (0)
#define ISO_6B_WRITE4BYTE    (1)

#define ISO6B_BUFFER_SIZE   256

/*************************************************************************
  *                      	                   文件内部使用的数据类型                               *                           *
**************************************************************************/
typedef WORD32(*ISORetry)(WORD16 , BYTE , BYTE *);


/*ISO6B 标签缓存结构*/
typedef struct
{
    WORD16  wRSSI;
    WORD16  wPad;
    BYTE aucUID[ISO_180006B_UID_BYTE_LEN];
} T_ISO6BTagElement;

typedef struct
{
    WORD16 wDataIndex;
    WORD16 wDataLen;
    T_ISO6BTagElement tISO6BTags[ISO6B_BUFFER_SIZE];
} T_ISO6BTagBuffer;



typedef struct
{
    WORD32 dwModeIdentifier;
    WORD32 dwFowardLinkDataRate;
    BYTE ucDelimiters;
}
T_ISO6BUHFRFModeTableEntry;

typedef struct
{
    WORD16 wModeIndex;
    WORD16 wFowardLinkDataRate;
    WORD16 wReverseLinkDataRate;
    WORD16 wModDepth;
    WORD16 wT1_value;
    WORD16 wdelimeters;
    WORD16 wDataReadStartAddr;        
    /*ISO6B清点时发送的DataRead命令的起始地址*/
    WORD16 wLastTagRssi;

    BYTE   aucUIDforAccess[8];           /* 读写ISO标签的UID为*/

    WORD16 wReadStartAddr;               /* 读ISO标签起始地址*/
    WORD16 wReadBytesLen;                /* length (in Bytes) */
    WORD16 wReadCommandType;

    
    WORD16 wWriteStartAddr;              /* 写ISO标签起始地址*/
    WORD16 wWriteBytesLen;               /* 写ISO标签长度*/
    WORD16 wWriteCommandType;
    BYTE   aucWriteData[256];             /* 要写入的内容*/
    BYTE   ucByteMask;                       /* 写命令掩码*/
    BYTE   ucPad;
    WORD16 wVerifyTimes;

    WORD16 wLockStartAddr;
    WORD16 wLockBytesLen;

    WORD16 wLockQueryStartAddr;
    WORD16 wLockQueryBytesLen;

    WORD16 wRetryTimes;
    WORD16 wSuccessByteLen;

} T_ISO6BCtl;


WORD32 uhf_ISO6B_Proc_Invnt_Resp(void);
WORD32 uhf_ISO6B_Proc_OprtCmd_Rsp(BYTE ucCmd, WORD16 wStartAddr, BYTE ucLen,BYTE *aucOptBuf);


#endif


