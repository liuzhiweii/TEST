#ifndef _USP_GB_H
#define _USP_GB_H

#define MAX_GB_MASK_WORD_LEN     (256)
#define MAX_GB_WRITE_WORD_LEN    (256)

/* 16bits的WORD拷贝 */
#define mem_words_cpy(dst, src, word_len)  memcpy((dst), (src), ((word_len)*2))

/**************************************************************************/
typedef struct
{
    BYTE   ucMB;
    BYTE   ucPad;
    WORD16 wMaskBitLength;        /* Mask length (bits) */
    WORD16 wMaskBitPointer;       /* Starting Mask bit address */
    WORD16 awMaskData[MAX_GB_MASK_WORD_LEN];         /* 变长 Mask value,得第一个字段 */
    //WORD16 awMaskData[0];
} T_GBMacSelectMask;

typedef struct
{
    WORD16 wMemBank;             
    WORD16 wPad;
    WORD16 wReadWordsLen;         /* length (in words) */
    WORD16 wWordPointer;          /* Starting word address */
} T_GBMacRead;


typedef struct
{
    WORD16 wMemBank;             
    WORD16 wWriteWordsLen;          /* length (in words) */
    WORD16 wWordPointer;          /* Starting word address */
    WORD16 awWriteData[MAX_GB_WRITE_WORD_LEN];       /* 变长数据 */
    //WORD16 awWriteData[0]; 
} T_GBMacWrite;

typedef struct
{
    WORD16 wMemBank;              
    WORD16 wEraseWordsLen;          /* length (in words) */
    WORD16 wWordPointer;          /* Starting word address */
    WORD16 wPad;
} T_GBMacErase;


typedef struct
{
    WORD16 ucMemBank;             
    WORD16 ucReadLock;
    WORD16 wPad;
    WORD16 wBlockPtr;
    WORD16 wBlockRange;
    WORD16 ucMask[1]; /*变长数据*/
} T_GBMacBlockLock;

typedef struct
{
    WORD16 wMask;
    WORD16 wPad;
} T_GBMacReadLock;

typedef struct
{
    WORD32 dwPwd;
} T_GBMacAccessPwd;

typedef struct
{
    WORD32 dwLockPayLoad;
} T_GBMacLock;

typedef struct
{
    WORD32 dwKillPwd;

} T_GBMacKill;


/* 国标协议Query命令参数定义 lxc */
typedef struct
{
    BYTE ucM;                            //编码选择，miller or FM bit 0-bit 1
    BYTE ucReLinkRateDivisor;   //反向链路速率因子 bit 2 - bit 5
    BYTE ucTRext;                      //前导信号指示 bit 6
    BYTE ucTarget;                     //目标 , 盘点标志bit 7
    BYTE ucSession;                   //会话 bit8 -bit9
    BYTE ucCondition;                // 条件bit10 - bit 13
    BYTE ucReserved;                //保留 bit14 - bit15
    BYTE ucPad;
} T_uhf_GB_Query;

/////lxc sort
/* 新国标协议sort命令参数定义 */
typedef struct
{
    BYTE ucMemBank;   //存储区 bit0-bit5
    BYTE ucTarget;        //目标bit6-bit9
    BYTE ucRule;           //规则bit10-bit11
    BYTE ucReserved;
} T_uhf_GB_Sort;


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
    WORD16 wTc;

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

    BYTE ucGBUserDataLoad;      /*Rcp的附加操作说明：*/
    /*0：没有附加操作*/
    /*1：测速配置标志*/
    /*其他：未定义操作*/

    BYTE ucPad;

    WORD32 dwDefaultInventQ;

    T_uhf_GB_Sort Select;

    T_uhf_GB_Query Query;

    T_GBMacSelectMask tGBSelectMask;

    T_GBMacRead tGBRead;

    T_GBMacWrite tGBWrite;

    T_GBMacErase tGBErase;

    T_GBMacAccessPwd tGBAccess;

    T_GBMacLock tGBLock;

    T_GBMacKill tGBKill;

} T_GBCtl;

/* GB 协议时序参数配置 */
typedef struct
{
    WORD16 RTDataRate;             /* R=>T数据速率 */ //160
    WORD16 TRDataRate;             /* T=>R数据速率 */ //320
    WORD16 RealTRDataRate;       /* T=>R实际上使用的数据速率 */
    WORD16 wTc;
    WORD16 wTpri;
    WORD16 dwK;                    /* 反向速率因子 */
    WORD16 M;                            /* M: Number of subcarrier cycles per symbol，取值为1，2，4，8 */
    WORD16 T1min;
    WORD16 T2min;
    WORD16 T4min;
} T_GB_TimesPara;



void uhf_ProtoHwInit(void);


WORD32 uhf_GB_Invetory_Resp(T_USPUHFGBInventoryRes *ptGBTagInventoryResp);
WORD32 uhf_GB_Read_Resp(T_USPUHFGBReadRes *ptGBReadResp);
WORD32 uhf_GB_Write_Resp(T_USPUHFGBWriteRes *ptGBWriteResp);
WORD32 uhf_GB_Lock_Resp(T_USPUHFGBLockRes *ptGBLockResp);
WORD32 uhf_GB_Erase_Resp(T_USPUHFGBEraseRes *ptGBEraseResp);
WORD32 uhf_GB_Kill_Resp(T_USPUHFGBKillRes *ptGBKillResp);




#endif


