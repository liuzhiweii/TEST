
#ifndef _USP_UHF_ISO6B_H
#define _USP_UHF_ISO6B_H

/***********************ISO6B协议相关接口**************************/
#define ISO6B_RES_COMM        \
    WORD16 wProtoType; \
    WORD16 wAntennaIndex;   \
    WORD16 wChannelIndex; \
    WORD16 wRssi;

/*此四格变量对应6B返回值的前四个变量，保证下面的
   返回结构可以强制转换到此结构，以在返回时用一个
   公共的函数处理*/
typedef struct
{
    WORD16 wProtoType;      
    WORD16 wAntennaIndex;         
    WORD16 wChannelIndex; 
    WORD16 wRssi;
} T_USPUHFISO6BResComm;

typedef struct
{
    BYTE   ucCommandType;
    BYTE   ucAddress;
    BYTE   ucMask;
    BYTE   ucMaskLen;
    BYTE   aucMaskData[8];
    /* 变长 Mask value,from 0~8 byte in length. 长度由wWordDataLen字段决定, MSB first */
} T_USPUHFISO6BInventoryMask;

typedef struct
{
    WORD16 wModeIndex;
    WORD16 wEstimateTag;
    T_USPUHFISO6BInventoryMask tISO6BInventoryMask;
} T_USPUHFISO6BInventoryPara;

typedef struct
{
    WORD32 dwAntIndex;
    T_USPUHFISO6BInventoryPara tISO6BInventoryPara;
    T_USPUHFInventRfPara          tInventoryRfPara;
} T_USPUHFISO6BInventory;


typedef struct
{
    WORD16 wTagDataLen;
	WORD16 wPad;
    /* 变长 UID 数据的第一个数据段，长度由wUID_bits_Len
                                                                  字段决定,目前长度为64bit   */
    BYTE aucTagData[8];
} T_USPUHFISO6BTagId;


/* 清点标签应答消息 */
typedef struct
{
    WORD16 wProtoType;      
    WORD16 wAntennaIndex;         
    WORD16 wChannelIndex; 
    WORD16 wRssi;
    WORD16 wInventoryFinish;
    /* 清点是否结束标志, 0：未结束；1：结束；*/
    WORD16 wResult;      /* 本消息中的标签数目；或者错误码  */
	
    T_USPUHFISO6BTagId tTagId;  /* 变长标签数据 */

} T_USPUHFISO6BInventoryRes;

typedef struct
{
    BYTE ucCommandType;
    BYTE ucRetryTimes;
    WORD16 wPad;
} T_USPUHFISO6BReadCtl;

typedef struct
{   
    WORD32 dwAntIndex;
    BYTE ucBytePtr;
    BYTE ucByteCount;
    WORD16 wPad;
    T_USPUHFISO6BReadCtl tISO6BReadctl;
    T_USPUHFISO6BTagId   tTagId;
} T_USPUHFISO6BRead;


/*ISO 读标签应答 */
typedef struct
{
    WORD16 wProtoType;      
    WORD16 wAntennaIndex;         
    WORD16 wChannelIndex; 
    WORD16 wRssi;
    WORD16 wResult;              /* 操作结果，0：成功；其他Error Code */
    WORD16 wResultLength;        /* 读取长度，错误时填0 */
    BYTE   aucReadData[0];          /* 变长标签数据的第一个数据字段 */
} T_USPUHFISO6BReadRes;



typedef struct
{
    BYTE ucCommandType;
    BYTE ucRetryTimes;
    BYTE ucVerifyTimes;
    BYTE ucPad;
} T_USPUHFISO6BWriteCtl;

typedef struct
{
    WORD32 dwAntIndex;
    BYTE ucBytePtr;
    BYTE ucByteCount;
	WORD16 wPad;
    BYTE aucWriteData[256];  /*要写入的数据*/
    T_USPUHFISO6BWriteCtl tISO6BWriteCtl;
    T_USPUHFISO6BTagId    tTagId;
} T_USPUHFISO6BWrite;



/* 写标签命令响应 */
typedef struct
{
    WORD16 wProtoType;      
    WORD16 wAntennaIndex;         
    WORD16 wChannelIndex; 
    WORD16 wRssi;
    WORD16 wResultLength;          /* 读取长度，错误时填0 */
    WORD16 wResult;                    /* 操作结果，0：成功；其他Error Code */
} T_USPUHFISO6BWriteRes;


typedef struct
{
    BYTE ucRetryTimes;
    BYTE ucVerifyTimes;
    WORD16 wPad;
} T_USPUHFISO6BLockCtl;

typedef struct
{
    WORD32 dwAntIndex;
    BYTE ucBytePtr;
    BYTE ucByteCount;
	WORD16 wPad;
    T_USPUHFISO6BLockCtl tISO6BLockCtl;
    T_USPUHFISO6BTagId   tTagId;
} T_USPUHFISO6BLock;

/* 锁标签应答 */
typedef struct
{
    WORD16 wProtoType;      
    WORD16 wAntennaIndex;         
    WORD16 wChannelIndex; 
    WORD16 wRssi;
    WORD16 wResultLength;          /* 读取长度，错误时填0 */
    WORD16 wResult;                     /* 操作结果，0：成功；其他Error Code*/
    BYTE   aucLockData[0];        /* 变长标签数据的第一个数据字段 */
} T_USPUHFISO6BLockRes;


typedef struct
{
    BYTE ucRetryTimes;
    BYTE ucPad;
    WORD16 wPad;
} T_USPUHFISO6BLockQueryCtl;

typedef struct
{
    WORD32 dwAntIndex;
    BYTE ucBytePtr;
    BYTE ucByteCount;
	WORD16 wPad;
    T_USPUHFISO6BLockQueryCtl tISO6BLockQueryCtl;
    T_USPUHFISO6BTagId        tTagId;
} T_USPUHFISO6BLockQuery;


/* 锁查询应答 */
typedef struct
{
    WORD16 wProtoType;      
    WORD16 wAntennaIndex;         
    WORD16 wChannelIndex; 
    WORD16 wRssi;
    WORD16 wResult;         /* 操作结果，0：成功；其他Error Code */
    WORD16 wResultLength;         /* 结果信息长度 */
    BYTE   aucLockQueryData[0];   /* 变长标签数据的第一个数据字段 */
} T_USPUHFISO6BLockQueryRes;


WORD32 usp_uhf_iso6b_inventory(T_USPUHFISO6BInventory*ptISO6BInventoryPara,
                                T_USPUHFISO6BInventoryRes *ptISO6BInventoryRes);
WORD32 usp_uhf_iso6b_read(T_USPUHFISO6BRead *ptISO6BReadPara,
                                T_USPUHFISO6BReadRes *ptISO6BReadRes);
WORD32 usp_uhf_iso6b_lockquery(T_USPUHFISO6BLockQuery *ptISO6BLockQueryPara,
                                   T_USPUHFISO6BLockQueryRes *ptISO6BLockQueryRes);
WORD32 usp_uhf_iso6b_write(T_USPUHFISO6BWrite *ptISO6BWritePara,
                                       T_USPUHFISO6BWriteRes *ptISO6BWriteRes);
WORD32 usp_uhf_iso6b_gettag(T_USPUHFISO6BInventoryRes *ptISO6BInventoryRes);
WORD32 usp_uhf_iso6b_lock(T_USPUHFISO6BLock *ptISO6BLockPara,
                                      T_USPUHFISO6BLockRes *ptISO6BLockRes);



#endif


