
#ifndef _USP_UHF_EPC_H
#define _USP_UHF_EPC_H

/***********************EPC协议相关接口**************************/
#define EPC_BLOCK_WRITE  (1)
#define EPC_WORD_WRITE   (0)


#define EPC_MAX_MASK_WORD_LEN (32)
#define EPC_MAX_MASK_BYTE_LEN (64)

/*EPC Acees 参数*/
typedef struct
{
    unsigned short int wTagWordLen;    /* 标签数据长度，以WORD为单位，不包括PC字段  */
	unsigned short int wPad;
    unsigned char   aucTagData[0];      /* 变长 EPC 数据的第一个数据段 */
} T_USPUHFEpcTagId;

typedef enum
{
    EPC_Action_Select_Unselect = 0,
    EPC_Action_Select_DoNothing = 1,
    EPC_Action_DoNothing_Unselect = 2,
    EPC_Action_Unselect_DoNothing = 3,
    EPC_Action_Unselect_Select = 4,
    EPC_Action_DoNothing_Select = 5,
} EPCSelectAction;

typedef enum UHF_EEPCDRValue
{

    EPC_DRValue_DRV_8 = 0,
    EPC_DRValue_DRV_64_3 = 1,
} E_USPUHFEpcDRValue;

typedef enum LLRP_EEPCMValue
{

    EPC_MValue_MV_FM0 = 0,
    EPC_MValue_MV_2 = 1,
    EPC_MValue_MV_4 = 2,
    EPC_MValue_MV_8 = 3,
} E_USPUHFEpcMValue;


typedef enum LLRP_EpcForwardLinkModulation
{

    EPC_ForwardLinkModulation_PR_ASK = 0,
    EPC_C1G2ForwardLinkModulation_SSB_ASK = 1,
    EPC_C1G2ForwardLinkModulation_DSB_ASK = 2,
} E_USPUHFEEpcForwardLinkModulation;


typedef enum LLRP_EEPCpectralMaskIndicator
{

    EPC_SpectralMaskIndicator_Unknown = 0,
    EPC_SpectralMaskIndicator_SI = 1,
    EPC_SpectralMaskIndicator_MI = 2,
    EPC_SpectralMaskIndicator_DI = 3,
} E_USPUHFEPCpectralMaskIndicator;

typedef struct
{
    unsigned int dwModeIdentifier;
    E_USPUHFEpcDRValue tDRValue;
    unsigned char ucEPCHAGTCConformance;
    E_USPUHFEpcMValue eMValue;
    E_USPUHFEEpcForwardLinkModulation eForwardLinkModulation;
    E_USPUHFEPCpectralMaskIndicator    eSpectralMaskIndicator;
    unsigned int dwBDRValue;
    unsigned int dwPIEValue;
    unsigned int dwMinTariValue;
    unsigned int dwMaxTariValue;
    unsigned int dwStepTariValue;
} T_USPUHFEpcRFModeTableEntry;


typedef struct
{
    unsigned short int            wMemBank;
    /* 00: RFU； 01: EPC； 10: TID； 11: User */
    unsigned short int            wMaskLength;        /* Mask length (bits) */
    unsigned short int            wMaskBitPointer;    /* Starting Mask bit address */
    unsigned short int            wPad;
    EPCSelectAction   eSelectAction;
    unsigned char                ucMaskData[EPC_MAX_MASK_BYTE_LEN];
    /* 变长 Mask value,得第一个字段 */
} T_USPUHFEpcInventoryMask;


typedef struct
{
    unsigned short int wMaskNum;
    unsigned short int wPad;
    T_USPUHFEpcInventoryMask tEpcInventoryMask[EPC_SETLECT_MASK_NUM];
} T_USPUHFEpcInventoryMaskList;

typedef struct
{
    unsigned short int wEstimatedTagNum;
    unsigned short int wSession;
    unsigned short int wModeindex;
    unsigned short int wPad;
    unsigned int dwRcvSenses;
    unsigned int dwUhfBitCommand;
    T_USPUHFEpcInventoryMaskList tEpcInventoryMaskList;
} T_USPUHFEpcInventoryPara;

typedef struct
{
    unsigned char   ucAntennaID;            /* 天线编号 */
    unsigned char   ucProtoType;           /*协议类型没用*/
    unsigned short int wPad;
    T_USPUHFEpcInventoryPara tEpcInventoryPara;
    T_USPUHFInventRfPara     tInventoryRfPara;
} T_USPUHFEpcInventory;


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
    T_USPUHFEpcTagId tTagId;     /* 变长标签数据 */
} T_USPUHFEpcInventoryRes;



typedef struct
{
    unsigned char   ucMB;
    unsigned char   ucPad;
    unsigned short int wWordPointer;
    unsigned short int wWordCount;
	unsigned short int wPad;
    unsigned int dwAccessPassword;
    unsigned int dwUhfBitCommand;
} T_USPUHFEpcReadPara;

typedef struct
{
    unsigned int dwAntIndex;
    T_USPUHFEpcReadPara tEpcReadPara;
    T_USPUHFEpcTagId    tTagId;
} T_USPUHFEpcRead;



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
} T_USPUHFEpcReadRes;



typedef struct
{
    unsigned char   ucMB;
    unsigned char   ucWriteType;   /*1 使用块写 0 普通写*/
    unsigned short int wWordPointer;    
    unsigned short int wWriteWordLen;
    unsigned short int wPad;
    unsigned int dwAccessPassword;
    unsigned int dwUhfBitCommand;
    unsigned char   aucData[64];  /*变长写入数据*/
} T_USPUHFEpcWritePara;

typedef struct
{  
    unsigned int dwAntIndex;
    T_USPUHFEpcWritePara tEpcWritePara;
    T_USPUHFEpcTagId     tTagId;
} T_USPUHFEpcWrite;


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
} T_USPUHFEpcWriteRes;

typedef struct
{
   unsigned short int wDataProfile;
   unsigned short int wAccessRange;
   unsigned short int wPersistence;
   unsigned short int wReadOrWrite;
   unsigned int dwAccessPassword;
   unsigned int dwUhfBitCommand;
}T_USPUHFEpcIPJQTPara;


typedef struct
{  
    unsigned int dwAntIndex;
    T_USPUHFEpcIPJQTPara tEpcIPJQTPara;
    T_USPUHFEpcTagId     tTagId;
} T_USPUHFEpcIPJQT;


typedef struct
{
    unsigned short int wProtoType;          /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;       /* 天线编号0 ~ 3 */
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned short int wResult;             /*QT 命令的读返回*/
    unsigned short int wDataProfile;        /*标签模式 1：私有模式 2：公有模式*/
    unsigned short int wAccessRange;         /*是否开启Short_range功能1：关闭   2：开启*/
    unsigned short int wReadOrWrite;        /*0 是读1是写*/
    unsigned short int wRssi;;
}T_USPUHFEpcIPJQTRes;


typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;         /*频率号*/
} CommonRes;

typedef enum E_USPEpcLockPrivilege
{
    Epc_LockPrivilege_Read_Write = 0,
    Epc_LockPrivilege_Perma_Lock = 1,
    Epc_LockPrivilege_Perma_Unlock = 2,
    Epc_LockPrivilege_Unlock = 3,
} E_EpcLockPrivilege;


typedef enum E_USPEpcLockDataField
{

    Epc_LockDataField_Kill_Password = 0,
    Epc_LockDataField_Access_Password = 1,
    Epc_LockDataField_EPC_Memory = 2,
    Epc_LockDataField_TID_Memory = 3,
    Epc_LockDataField_User_Memory = 4,
} E_EpcLockDataField;


typedef struct
{
    E_EpcLockPrivilege Privilege;
    E_EpcLockDataField DataField;
} T_USPUHFEpcLockPayload;

typedef struct
{
    unsigned short int wPayLoadNum;
	unsigned short int wPad;
    T_USPUHFEpcLockPayload taEpcLockPayLoad[5];
} T_USPUHFEpcLockPayloadList;

typedef struct
{
    unsigned int dwAccessPassword;
    unsigned int dwUhfBitCommand;
    T_USPUHFEpcLockPayloadList tEpcLockPayLoad;   /*锁和解锁操作的定义组*/
} T_USPUHFEPcLockPara;


typedef struct
{   
    unsigned int dwAntIndex;
    T_USPUHFEPcLockPara tEpcLockPara;
    T_USPUHFEpcTagId    tTagId;   /*变长EPC码*/
} T_USPUHFEpcLock;

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
} T_USPUHFEpcLockRes;


typedef struct
{
    unsigned int dwKillPassword;
    unsigned int dwUhfBitCommand;
} T_USPUHFEpcKillPara;


typedef struct
{
    unsigned int dwAntIndex;
    T_USPUHFEpcKillPara tEpcKillPara;
    T_USPUHFEpcTagId    tTagId;   /*变长EPC码*/
} T_USPUHFEpcKill;


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
} T_USPUHFEpcKillRes;


typedef struct
{
    unsigned char   ucMB;
    unsigned char   ucReadLock;
    unsigned short int wOpSpecID;
    unsigned short int ucRFU;
    unsigned short int wBlockPtr;
    unsigned short int wBlockRange;
    unsigned short int wPad;
    unsigned int dwAccessPassword;
    unsigned int dwUhfBitCommand;
    unsigned char   ucMask[512];
} T_USPUHFEpcBlockLockPara;



typedef struct
{
    unsigned int dwAntIndex;
    T_USPUHFEpcBlockLockPara tEpcBlockLockPara;
    T_USPUHFEpcTagId         tTagId;
} T_USPUHFEpcBlockLock;

typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned short int wResult;               /* 操作结果，0：成功；其他：错误码 */
    unsigned short int wRssi;
    unsigned char     ucReadLock;
    unsigned char     ucPad;
    unsigned short int wLockStateLen;   /*字节长度*/
    unsigned short int wPad;
    unsigned char   ucLockState[512];
} T_USPUHFEpcBlockLockRes;


typedef struct
{
    unsigned char     ucMask;
    unsigned char     ucPad;
    unsigned short int   wPad;
    unsigned int   dwAccessPassword;
    unsigned int   dwUhfBitCommand;
} T_USPUHFEpcReadLockPara;

/*ALEN 专有接口读保护*/
typedef struct
{
    unsigned int dwAntIndex;
    T_USPUHFEpcReadLockPara   tEpcReadLockPara;
    T_USPUHFEpcTagId          tTagId;        /* 标签标识数据 */
} T_USPUHFEpcReadLock;



typedef struct
{
    unsigned short int wProtoType;
    /* 协议类型 0:GEN2 ; 1:18000-6 Type A ; 2:18000-6 Type B */
    unsigned short int wAntennaIndex;         /* 天线编号0 ~ 3 */
    unsigned short int wRssi;
    unsigned short int wChannelIndex;       /*频率号*/
    unsigned short int wResult;  /*读保护的结果*/
} T_USPUHFEpcReadLockRes;


void usp_uhf_epc_inventory(T_USPUHFEpcInventory*ptEpcInventoryPara,
                                  T_USPUHFEpcInventoryRes*ptEpcTagInventoryResp);
void usp_uhf_epc_read(T_USPUHFEpcRead *ptEpcReadPara,T_USPUHFEpcReadRes *ptEPCReadResp);
void usp_uhf_epc_write(T_USPUHFEpcWrite *ptEpcWritePara,T_USPUHFEpcWriteRes *ptEPCWriteResp);
void usp_uhf_epc_lock(T_USPUHFEpcLock *ptEpcLockPara,T_USPUHFEpcLockRes *ptEPCLockResp);
void usp_uhf_epc_kill(T_USPUHFEpcKill *ptEpcKillPara,T_USPUHFEpcKillRes *ptEPCKillResp);
void usp_uhf_epc_blocklock(T_USPUHFEpcBlockLock *ptEpcBlockLockPara,
                                    T_USPUHFEpcBlockLockRes *ptEPCBlockLockResp);
void usp_uhf_epc_readlock(T_USPUHFEpcReadLock *ptEpcReadLock,
                                   T_USPUHFEpcReadLockRes *ptEPCReadLockResp);
void usp_uhf_epc_query(T_USPUHFEpcInventoryRes*ptEpcTagInventoryResp);
void usp_uhf_epc_ipjqt(T_USPUHFEpcIPJQT *ptEpcIPJQT,
                              T_USPUHFEpcIPJQTRes *ptEpcIPJQTResp);



#endif




