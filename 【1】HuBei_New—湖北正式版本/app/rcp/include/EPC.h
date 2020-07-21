
#ifndef _USP_EPC_H
#define _USP_EPC_H

#define MAX_EPC_MASK_WORD_LEN     (256)
#define MAX_EPC_WRITE_WORD_LEN    (256)

/* 16bits的WORD拷贝 */
#define mem_words_cpy(dst, src, word_len)  memcpy((dst), (src), ((word_len)*2))


/**************************************************************************/
typedef struct
{
    BYTE   ucMB;
    BYTE   ucPad;
    WORD16 wMaskBitLength;        /* Mask length (bits) */
    WORD16 wMaskBitPointer;       /* Starting Mask bit address */
    WORD16 awMaskData[MAX_EPC_MASK_WORD_LEN];         /* 变长 Mask value,得第一个字段 */

} T_EpcMacSelectMask;

typedef struct
{
    WORD16 wMemBank;              /* 00: RFU ；01: EPC； 10: TID； 11: User */
    WORD16 wPad;
    WORD16 wReadWordsLen;         /* length (in words) */
    WORD16 wWordPointer;          /* Starting word address */
} T_EpcMacRead;


typedef struct
{
    WORD16 wIsBlockWrite;
    WORD16 wMemBank;              /* 00: RFU ；01: EPC； 10: TID； 11: User */
    WORD16 wWriteWordsLen;          /* length (in words) */
    WORD16 wWordPointer;          /* Starting word address */
    WORD16 awWriteData[MAX_EPC_WRITE_WORD_LEN];       /* 变长数据 */

} T_EpcMacWrite;

typedef struct
{
    WORD16 ucMemBank;              /* 00: RFU ；01: EPC； 10: TID； 11: User */
    WORD16 ucReadLock;
    WORD16 wPad;
    WORD16 wBlockPtr;
    WORD16 wBlockRange;
    WORD16 ucMask[1]; /*变长数据*/
} T_EpcMacBlockLock;

typedef struct
{
    WORD16 wMask;
    WORD16 wPad;
} T_EpcMacReadLock;

typedef struct
{
    WORD32 dwPwd;
} T_EpcMacAccessPwd;

typedef struct
{
    WORD32 dwLockPayLoad;
} T_EpcMacLock;

typedef struct
{
    WORD32 dwKillPwd;

} T_EpcMacKill;

/* EPC协议Query命令参数定义 */
typedef struct
{
    WORD16 Q;
    WORD16 Target;
    WORD16 Session;
    WORD16 Sel;
    WORD16 TRext;     /*  T=>R use the extended preamble  */
    WORD16 M;         /* M: Number of subcarrier cycles per symbol，取值为1，2，4，8 */
    WORD16 DR;        /* Divide Ratio, 取值为64/3 或者 8 */
} T_uhf_Epc_Query;

/* EPC协议Select命令参数定义 */
typedef struct
{
    WORD16 Truncate;
    WORD16 MemBank;            /* 当前访问的存储区 */
    WORD16 Action;
    WORD16 Target;
} T_uhf_Epc_Select;


/* GEN2协议控制数据结构 */
typedef struct
{
    WORD16 wModeIndex;
    WORD16 RTDataRate;            /* R=>T数据速率 */
    WORD16 TRDataRate;            /* T=>R数据速率 */
    WORD16 RealTRDataRate;     /* T=>R实际上使用的数据速率 */
    WORD16 TRLinkRate;             /* T=>R两个链路速率 */
    float Tari;                        /* 阅读器到标签R=>T的信号传输中数据0的标准时间间隔 */
    float RTcal;                      /* Interrogator-to-Tag calibration symbol */
    float TRcal;                      /* Tag-to-Interrogator calibration symbol */
    WORD16 wRTcal_div_Tari;
    WORD16 wTRcal_div_halfTari;
    WORD16 wTpri;
    WORD16 T1min;
    WORD16 T1max;
    WORD16 T2min;
    WORD16 T2max;
    WORD16 T4min;

    WORD16 wLastTagRssi;

    WORD16 TRCodeType;            /*T=>R编码模式，有FM0基带编码和Miller副载波编码两种*/
    WORD16 RTModulateType;      /* R=>T调制模式 */
    WORD16 wRTModDepth;

    WORD16 PIE_data_1_len;      /*  data-1用" 110 "或者" 1110 "表示*/
    WORD16 Session;                   /* 当前标签的Session */


    WORD16 Command;                /* 当前处理的命令 */
    WORD16 MemBank;                 /* 当前访问的存储区 */
    WORD16 Sel;
    WORD16 Target;
    WORD16 Truncate;
    WORD16 Action;

    BYTE ucRcpUserDataLoad;      /*Rcp的附加操作说明：*/
    /*0：没有附加操作*/
    /*1：测速配置标志*/
    /*其他：未定义操作*/

    BYTE ucPad;

    WORD32 dwDefaultInventQ;

    T_uhf_Epc_Select Select;

    T_uhf_Epc_Query Query;

    T_EpcMacSelectMask tEpcSelectMask;

    T_EpcMacRead tEpcRead;

    T_EpcMacWrite tEpcWrite;

    T_EpcMacAccessPwd tEpcAccess;

    T_EpcMacLock tEpcLock;

    T_EpcMacKill tEpcKill;

    T_EpcMacBlockLock tEpcBlockLock;

    T_EpcMacReadLock tEpcReadLock;

} T_EpcCtl;


/* EPC GEN2 协议时序参数配置 */
typedef struct
{
    WORD16 RTDataRate;             /* R=>T数据速率 */
    WORD16 TRDataRate;             /* T=>R数据速率 */
    WORD16 RealTRDataRate;       /* T=>R实际上使用的数据速率 */
    WORD16 wTari;
    WORD16 wTpri;
    WORD16 wFT;
    WORD16 wRTcal_div_Tari;
    WORD16 wTRcal_div_halfTari;
    WORD16 DR;                          /* Divide Ratio, 取值为64/3 或者 8 */
    WORD16 M;                            /* M: Number of subcarrier cycles per symbol，取值为1，2，4，8 */
    WORD16 T1min;
    WORD16 T2min;
    WORD16 T4min;
} T_EPC_TimesPara;



void uhf_ProtoHwInit(void);


WORD32 uhf_Epc_Invetory_Resp(T_USPUHFEpcInventoryRes *ptEpcTagInventoryResp);
WORD32 uhf_Epc_Read_Resp(T_USPUHFEpcReadRes *ptEPCReadResp);
WORD32 uhf_Epc_Write_Resp(T_USPUHFEpcWriteRes *ptEPCWriteResp);
WORD32 uhf_Epc_Lock_Resp(T_USPUHFEpcLockRes *ptEPCLockResp);
WORD32 uhf_Epc_Kill_Resp(T_USPUHFEpcKillRes *ptEPCKillResp);
WORD32 uhf_Epc_BlockLock_Resp(T_USPUHFEpcBlockLockRes *ptEPCBlockLockResp);
WORD32 uhf_Epc_ReadLock_Resp(T_USPUHFEpcReadLockRes *ptEPCReadLockResp);
WORD32 uhf_Epc_IPJQT_Resp(T_USPUHFEpcIPJQTRes *ptEPCIPJQtResp);

#endif



