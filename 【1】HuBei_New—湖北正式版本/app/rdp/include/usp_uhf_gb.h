
#ifndef _USP_UHF_GB_H
#define _USP_UHF_GB_H

/***********************GB协议相关接口**************************/

#define GB_MAX_MASK_WORD_LEN (32)
#define GB_MAX_MASK_BYTE_LEN (64)

/*GB Acees 参数*/
typedef struct
{
    unsigned short int wTagWordLen;    /* 标签数据长度，以WORD为单位，不包括PC字段  */
    unsigned short int wPad;
    unsigned char   aucTagData[0];      /* 变长 GB 数据的第一个数据段 */
} T_USPUHFGBTagId;

typedef enum
{
    GBSortAction_Match1b_NoMatch0b = 0,
    GBSortAction_MatchNothing_NoMatch0b = 1,
    GBSortAction_Match1b_NoMatchNothing = 2,
    GBSortAction_Match0b_NoMatch1b = 3,
} GBSortAction;

typedef enum
{
    GBSortTarget_Session_S0 = 0,
    GBSortTarget_Session_S1 = 1,
    GBSortTarget_Session_S2 = 2,
    GBSortTarget_Session_S3 = 3,
    GBSortTarget_Session_SL = 4,
} GBSortTarget;

typedef enum UHF_EGBDRValue
{

    GB_DRValue_DRV_8 = 0,
    GB_DRValue_DRV_64_3 = 1,
} E_USPUHFGBDRValue;

typedef enum LLRP_EGBMValue
{

    GB_MValue_MV_FM0 = 0,
    GB_MValue_MV_2 = 1,
    GB_MValue_MV_4 = 2,
    GB_MValue_MV_8 = 3,
} E_USPUHFGBMValue;


typedef enum LLRP_GBForwardLinkModulation
{

    GB_ForwardLinkModulation_PR_ASK = 0,
    GB_GBForwardLinkModulation_SSB_ASK = 1,
    GB_GBForwardLinkModulation_DSB_ASK = 2,
} E_USPUHFEGBForwardLinkModulation;


typedef enum LLRP_EGBpectralMaskIndicator
{

    GB_SpectralMaskIndicator_Unknown = 0,
    GB_SpectralMaskIndicator_SI = 1,
    GB_SpectralMaskIndicator_MI = 2,
    GB_SpectralMaskIndicator_DI = 3,
} E_USPUHFGBpectralMaskIndicator;

typedef struct
{
    unsigned int dwModeIdentifier;
    E_USPUHFGBMValue eMValue;  /* 反向编码方式 FM0*/
    E_USPUHFEGBForwardLinkModulation eForwardLinkModulation; /* 调制方式 DSB*/
    unsigned int dwFawardValue;
    unsigned int dwBDRValue;  /* 反向波特率 *//* 320 */
    unsigned int dwPw;
    unsigned int dwTc;
} T_USPUHFGBRFModeTableEntry;

/// new GB inventory structure
typedef struct
{
    unsigned short int            wMemBank;            
    /* 新国标中表示存储区00: 信息
                         01: 编码 
                         02: 安全
                         03: 用户 
    */
    unsigned short int            wMaskLength;        /* Mask length (bits) */
                                                            /* 在新国标中，这个值表示数据长度，经转化得到掩码*/
    unsigned short int            wMaskBitPointer;    /* Starting Mask bit address */
                                                            /* 在新国标中，这个值表示数据指针 */
    unsigned short int            wPad;
    GBSortTarget      ucSortTarget;
    GBSortAction      ucSortAction;
    unsigned char              ucMaskData[GB_MAX_MASK_BYTE_LEN];
    /* 变长 Mask value,得第一个字段 */
} T_USPUHFGBInventoryMask;  //T_USPUHFGBInventoryMask


typedef struct
{
    unsigned short int wMaskNum;
    unsigned short int wPad;
    T_USPUHFGBInventoryMask tGBInventoryMask[MaxGBSortNum]; //GB_SETLECT_MASK_NUM
} T_USPUHFGBInventoryMaskList;

typedef struct
{
    unsigned short int wCCN;
    unsigned short int wCIN;
    unsigned short int wSession;
    unsigned short int wModeindex;
    unsigned char ucGBQureySel;
    unsigned char ucGBQureyAction;
    unsigned short int wPad;
    T_USPUHFGBInventoryMaskList tGBInventoryMaskList;
} T_USPUHFGBInventoryPara; // T_USPUHFGBInventoryPara

typedef struct
{
    unsigned char   ucAntennaID;            /* 天线编号 */
    unsigned char   ucProtoType;           /*协议类型没用*/
    unsigned short int wPad;
    T_USPUHFGBInventoryPara tGBInventoryPara;
    T_USPUHFInventRfPara     tInventoryRfPara;
} T_USPUHFGBInventory; // T_USPUHFGBInventory


/* 清点标签应答消息 */
typedef struct
{
    unsigned short int wProtoType;          /* 协议类型 */
    unsigned short int wAntennaIndex;       /* 天线编号 */
    unsigned short int wPC;               /*上报PC值*/
    unsigned short int wCRC;                /*目前逻辑不支持，天0xFF*/
    unsigned short int wRssi;
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned int wQueryCollisionCount;
    unsigned int wQueryNoReplyCount;
    unsigned short int wInventoryFinish;   /* 清点是否结束标志, 0：未结束 ； 1：结束 */
    unsigned short int wResult;            /* 0 -正确 其他错误码 */
    T_USPUHFGBTagId tTagId;     /* 变长标签数据 */
} T_USPUHFGBInventoryRes; // T_USPUHFGBInventoryRes


/////// new GB read structure
typedef struct
{
    unsigned char   ucMB;   /* 新国标中表示存储区 */
    unsigned char   ucPad;
    unsigned short int wWordPointer;  /* x新国标中表示起始地址 */
    unsigned short int wWordCount;    /* 新国标中表示字的数量 */
    unsigned short int wPad;
    unsigned int dwAccessPassword;
} T_USPUHFGBReadPara; // T_USPUHFGBReadPara

typedef struct
{
    unsigned int dwAntIndex;
    T_USPUHFGBReadPara tGBReadPara;
    T_USPUHFGBTagId    tTagId;
} T_USPUHFGBRead; //T_USPUHFGBRead



/* 读标签应答 */
typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;        /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned short int wResult;            /* 操作结果，0：成功；其他 ：ErrorCode*/
    unsigned short int wResultLength;          /* 结果信息：返回数据长度 ，失败时为0  */
    unsigned short int awReadData[0];          /* 变长标签数据 */
} T_USPUHFGBReadRes; //T_USPUHFGBReadRes


///////  new GB write Structure
typedef struct
{
    unsigned char   ucMB;              /* 新国标中表示存储区 */
    unsigned char   ucPad;   /*1 使用块写 0 普通写*/ /* 新国标没有用 */
    unsigned short int wWordPointer;    /* 访问的起始地址 */
    unsigned short int wWriteWordLen; /* 写入数据长度 */
    unsigned short int wPad;
    unsigned int dwAccessPassword;
    unsigned char   aucData[64];  /*变长写入数据*/
} T_USPUHFGBWritePara; // T_USPUHFGBWritePara

typedef struct
{  
    unsigned int dwAntIndex;
    T_USPUHFGBWritePara tGBWritePara;
    T_USPUHFGBTagId     tTagId;
} T_USPUHFGBWrite; // T_USPUHFGBWrite


/* 写标签应答 */
typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;         /*频率号*/
    unsigned short int wResult;               /* 操作结果，0：成功；其他：错误码 */
    unsigned short int wResultLength;        /* 结果信息：返回成功的数据长度  */
} T_USPUHFGBWriteRes; // T_USPUHFGBWriteRes


/* 擦除命令相关定义 */
typedef struct
{
    unsigned char   ucMB;              /* 新国标中表示存储区 */
    unsigned char   ucPad;
    unsigned short int wPad;
    unsigned short int wWordPointer;    /* 访问的起始地址 */
    unsigned short int wEraseWordLen; /* 写入数据长度 */
    unsigned int dwAccessPassword;
} T_USPUHFGBErasePara;

typedef struct
{  
    unsigned int dwAntIndex;
    T_USPUHFGBErasePara tGBErasePara;
    T_USPUHFGBTagId     tTagId;
} T_USPUHFGBErase;


/*擦除标签应答 */
typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;         /*频率号*/
    unsigned short int wResult;               /* 操作结果，0：成功；其他：错误码 */
    unsigned short int wResultLength;        /* 结果信息：返回成功的数据长度  */
} T_USPUHFGBEraseRes;


typedef enum E_USPGBLockDataArea   //与ucMB参数的取值相同
{
    GB_LockDataField_Info_Area = 0,   //信息区
    GB_LockDataField_Coding_Area = 1, //编码区
    GB_LockDataField_Sec_Area = 2,     //安全区
    GB_LockDataField_User_Area = 3,    //用户区
} E_GBLockDataArea;

typedef enum E_USPGBLockAreaCfg
{
    GB_LockCfg_Store_Area = 0,  // 配置存储区
    GB_LockCfg_Sec_Area    = 1,  //配置安全属性
}E_GBLockAreaCfg;

typedef enum E_USPGBLockActionCfg
{
    GB_LockAction_RW  = 0,  // 可读可写
    GB_LockAction_RO  = 1,  // 可读不可写
    GB_LockAction_WO  = 2,  // 不可读可写
    GB_LockAction_N   = 3,  // 不可读不可写
}E_GBLockActionCfg;


typedef struct  // lock 参数透传即可
{
    unsigned int dwAccessPassword;
    unsigned char  ucMB; // DataArea 
    unsigned char  ucConfig; // AreaCfg 0 or 1
    unsigned char ucAeraMode; // ActionCfg
    unsigned char ucSecureMode;  // securit mode cfg
} T_USPUHFGBLockPara;

//typedef struct
//{
//    unsigned int dwAccessPassword;
//    E_GBLockDataArea DataArea;
//    E_GBLockAreaCfg   AreaCfg;
//    E_GBLockActionCfg ActionCfg;  
//} T_USPUHFGBLockPara;


typedef struct
{   
    unsigned int dwAntIndex;
    T_USPUHFGBLockPara tGBLockPara;
    T_USPUHFGBTagId    tTagId;   /*变长GB码*/
} T_USPUHFGBLock;

/* 锁标签操作应答 */
typedef struct
{
    unsigned short int wProtoType;    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6
Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned short int wResult;               /* 操作结果，0：成功；其他：错误码 */
	unsigned short int wPad;
} T_USPUHFGBLockRes;


typedef struct
{
    unsigned int dwKillPassword;
} T_USPUHFGBKillPara;


typedef struct
{
    unsigned int dwAntIndex;
    T_USPUHFGBKillPara tGBKillPara;
    T_USPUHFGBTagId    tTagId;   /*变长GB码*/
} T_USPUHFGBKill;


/* 杀死标签应答 */
typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned short int wResult;           /* 操作结果，0：成功；其他 错误码 */
    unsigned short int wPad;
} T_USPUHFGBKillRes;



void usp_uhf_gb_inventory(T_USPUHFGBInventory*ptGBInventoryPara,T_USPUHFGBInventoryRes*ptGBTagInventoryResp);
void usp_uhf_gb_read(T_USPUHFGBRead *ptGBReadPara,T_USPUHFGBReadRes *ptGBReadResp);
void usp_uhf_gb_write(T_USPUHFGBWrite *ptGBWritePara,T_USPUHFGBWriteRes *ptGBWriteResp);
void usp_uhf_gb_lock(T_USPUHFGBLock *ptGBLockPara,T_USPUHFGBLockRes *ptGBLockResp);
void usp_uhf_gb_erase(T_USPUHFGBErase *ptGBErase,T_USPUHFGBEraseRes *ptGBEraseResp);
void usp_uhf_gb_kill(T_USPUHFGBKill *ptGBKillPara,T_USPUHFGBKillRes *ptGBKillResp);

#endif

