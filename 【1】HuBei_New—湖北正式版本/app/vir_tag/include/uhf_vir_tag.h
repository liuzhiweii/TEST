#ifndef __UHF_VIR_TAG__
#define  __UHF_VIR_TAG__

#define VIR_TAG_EPC_LEN   16
#define VIR_TAG_TID_LEN   12
#define VIR_TAG_USER_LEN  64


#define VIR_TAG_RCV_MSG_BUF_SIZE    4096

#define VIR_TAG_MAX_6C_TAG_NUM    256
#define VIR_TAG_MAX_6B_TAG_NUM    256
#define VIR_TAG_MAX_SELECT_LIST_LEN    256

#define VIR_TAG_INVALID_ID   65535

#define VIR_TAG_MATCH_SUCCESS   0
#define VIR_TAG_MATCH_FAIL      1

#define VIR_TAG_ERR_ID_EXCEED        1
#define VIR_TAG_ERR_MEM_FAIL         2
#define VIR_TAG_ERR_TAG_NOT_EXIST    3


#define  VIR_TAG_MATCH_DESELECT_UNMATCH_SELECT    0
#define  VIR_TAG_MATCH_DESELECT_UNMATCH_NOTHING   1
#define  VIR_TAG_MATCH_NOTHING_UNMATCH_SELECT     2
#define  VIR_TAG_MATCH_REVERSE_UNMATCH_NOTHING    3
#define  VIR_TAG_MATCH_SELECT_UNMATCH_DESELECT    4
#define  VIR_TAG_MATCH_SELECT_UNMATCH_NOTHING     5
#define  VIR_TAG_MATCH_NOTHING_UNMATCH_DESELECT   6
#define  VIR_TAG_MATCH_NOTHING_UNMATCH_REVERSE    7


#define  VIR_TAG_SHM_SIZE    1024

/* FPAG响应frame的标志定义 */
#define VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS          (0x1) /* 成功     */
#define VIR_TAG_FPGA_FRAME_FLAG_FAIL              (0x0) /* 失败     */
#define VIR_TAG_FPGA_FRAME_FLAG_INVENT_FINISH     (0x2) /* 清点结束 */
#define VIR_TAG_FPGA_FRAME_FLAG_NO_RESPONSE       (0x3)



/* FPGA的EPC frame struct */
#define VIR_TAG_FPGA_FRAME_LEN         (0)
#define VIR_TAG_FPGA_FRAME_CMD_TYPE    (1)
#define VIR_TAG_FPGA_FRAME_FLAG        (2)
#define VIR_TAG_FPGA_FRAME_GEN2_PC     (3)
#define VIR_TAG_FPGA_FRAME_GEN2_EPC    (4)

#define VIR_TAG_MEMBANK_RESERVE           0
#define VIR_TAG_MEMBANK_EPC               1
#define VIR_TAG_MEMBANK_TID               2
#define VIR_TAG_MEMBANK_USER              3

#define VIR_TAG_EPC_OFFSET                4

#define VIR_TAG_CONTINUE_PROC             0
#define VIR_TAG_BREAK_PROC                1

#define VIR_TAG_ACCESS_SUCCESS            0
#define VIR_TAG_ACCESS_FAIL               1

//#define vir_tag_debug(...)    printf(__VA_ARGS__)
#define vir_tag_debug(...) printf("<vir_tag> ", __VA_ARGS__)

#define VIR_TAG_DEFAULT_RSSI              10000

/* FPGA返回的错误码 */
/*   命令类型
--s_cpumsg_type(3 downto 0)   0000:   EPC消息
--                            0001:   read命令消息
--                            0010:   write命令消息
--                            0011:   kill命令消息
--                            0100:   lock命令消息
--                            0101:   blkwrt命令消息
--                            0110:   blkerase命令消息
--                             0111:  清点结束消息
--                            1000： 错误消息
--                            1001： blkpermalock(LOCK=0)命令消息
--                            1010： blkpermalock（LOCK=1）命令消息
--                            1011： blkreadlock（alien标签的块读锁定）
--                            1100： impinj qt写操作命令消息（如果QT没有继续其他的命令）
--                            1101：impinj qt读操作命令消息。

*/

#define VIR_TAG_ERR_EPC_CMD        0
#define VIR_TAG_ERR_READ_CMD       1
#define VIR_TAG_ERR_WRITE_CMD      2
#define VIR_TAG_ERR_KILL_CMD       3
#define VIR_TAG_ERR_LOCK_CMD       4
#define VIR_TAG_ERR_BLKWRT_CMD     5
#define VIR_TAG_ERR_BLKERASE_CMD   6
#define VIR_TAG_ERR_INVFIN_CMD     7
#define VIR_TAG_ERR_ERROR_CMD      8
#define VIR_TAG_ERR_BLKPERMLOCK    9
#define VIR_TAG_ERR_BLKPERMLOCK1   10
#define VIR_TAG_ERR_BLKREADLOCK    11
#define VIR_TAG_ERR_QTWR_CMD       12
#define VIR_TAG_ERR_QTREAD_CMD     13


/* 错误阶段
4：ACK命令阶段
6：请求handel阶段
7：REQRN16命令阶段
8：ACCESS命令阶段
9：读命令阶段
10：写命令阶段
11：KILL命令阶段
12：LOCK命令阶段
13: blkwrt命令阶段
14：blkerase命令阶段
15：blkpermaLOCK命令阶段（READ/LOCK=0）
16: blkpermaLOCK命令阶段（READ/LOCK=1）
17: blkreadlock(ALIEN标签块读锁定)
*/
#define VIR_TAG_STAGE_ERR_ACCESS          8
#define VIR_TAG_STAGE_ERR_READ            9
#define VIR_TAG_STAGE_ERR_WRITE           10
#define VIR_TAG_STAGE_ERR_KILL            11
#define VIR_TAG_STAGE_ERR_LOCK            12
#define VIR_TAG_STAGE_ERR_BLKWRT          13
#define VIR_TAG_STAGE_ERR_BLKERASE        14
#define VIR_TAG_STAGE_ERR_BLKPERMALOCK    15
#define VIR_TAG_STAGE_ERR_PERMALOCK1      16
#define VIR_TAG_STAGE_ERR_BLKREADLOCK     17


/*  自定义错误吗
B0:Timeout：无信号返回或者阅读器解不出信号
B1:Collision：已检测到信号，但是前导码不匹配（碰撞）
B2:crc error：CRC校验错
B3:tag error：标签返回错误码（i.e. Read, Write, Kill, Lock, access),见下图。
B4:handel error：handel不匹配（ie:read,write,kill,lock,access,）
B5:EPC err：ACK字段，（B1=1,B5=1）指示EPC返回的长度不够。
B6:访问密码不正确。B6=1,B0=1
*/
#define VIR_TAG_SELF_ERR_TIMEOUT    0x0001
#define VIR_TAG_SELF_ERR_COLL       0x0002
#define VIR_TAG_SELF_ERR_CRC        0x0004
#define VIR_TAG_SELF_ERR_TAG        0x0008
#define VIR_TAG_SELF_ERR_HANDLE     0x0010
#define VIR_TAG_SELF_ERR_EPC        0x0020
#define VIR_TAG_SELF_ERR_PASSWD     0x0040

/*  标签返回的错误码
USP_UHF_EPC_TAG_MEM_LOCATION_NOTEXIST   03
USP_UHF_EPC_ACCESS_NOT_PERMIT                  04
*/
#define VIR_TAG_TAG_ERR_MEM_NOT_EXIST        0x03
#define VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT    0x04
#define VIR_TAG_TAG_ERR_DEFAULT              0x00

#define VIR_TAG_PWD_WRITE_BIT            0x02
#define VIR_TAG_PERMA_LOCK_BIT           0x01
#define VIR_TAG_PWD_RW_BIT               0x02

#define VIR_TAG_BANK_ACCESSABLE          0x00
#define VIR_TAG_BANK_UNACCESSABLE        0x01

#define VIR_TAG_MAC_NOT_START           0
#define VIR_TAG_MAC_START               1

#define VIR_TAG_ADDR_OUT_BLOCK          0
#define VIR_TAG_ADDR_IN_BLOCK           1

/*********************************************************************
*                   命令码定义
**********************************************************************/
#define  VIR_TAG_DELTE_6C_TAG               1
#define  VIR_TAG_DELETE_6C_TAG_RESPONSE     2
#define  VIR_TAG_CONFIG_6C_TAG              3
#define  VIR_TAG_CONFIG_6C_TAG_RESPONSE     4
#define  VIR_TAG_QUERY_6C_TAG               5
#define  VIR_TAG_QUERY_6C_TAG_RESPONSE      6
#define  VIR_TAG_REMOVE_ALL_6C_TAG          7
#define  VIR_TAG_REMOVE_ALL_6C_TAG_RESPONSE          8
#define  VIR_TAG_DELTE_6B_TAG               9
#define  VIR_TAG_DELETE_6B_TAG_RESPONSE     10
#define  VIR_TAG_CONFIG_6B_TAG              11
#define  VIR_TAG_CONFIG_6B_TAG_RESPONSE     12
#define  VIR_TAG_QUERY_6B_TAG               13
#define  VIR_TAG_QUERY_6B_TAG_RESPONSE      14
#define  VIR_TAG_REMOVE_ALL_6B_TAG          15
#define  VIR_TAG_REMOVE_ALL_6B_TAG_RESPONSE          16


typedef struct tagT_VirTagEffectiveRegs
{
    WORD16 wREG_CPU_CMD_type;
    WORD16 wREG_PROTO_TYPE;
    WORD16 wREG_G2_Select_Addr;
    WORD16 wREG_G2_Select_Mask_BitLen;
    WORD16 wREG_G2_Select_Para;
    WORD16 wREG_G2_Query_Para;
    WORD16 wREG_G2_Access_Password_h;
    WORD16 wREG_G2_Access_Password_L;
    WORD16 wREG_I_QT_WR_PER;
    WORD16 wREG_I_QT_PAYLOAD;
    WORD16 wREG_G2_Read_Membank;
    WORD16 wREG_G2_Read_Addr;
    WORD16 wREG_G2_Read_WordCount;
    WORD16 wREG_G2_Write_Membank;
    WORD16 wREG_G2_Write_Addr;
    WORD16 wREG_G2_Write_WordCount;
    WORD16 wREG_G2_Block_Write_Membank;
    WORD16 wREG_G2_Block_Write_Adress;
    WORD16 wREG_G2_Block_Write_Length;
    WORD16 wREG_G2_Loc_payload_mask;
    WORD16 wREG_G2_Loc_payload_Action;
    WORD16 wREG_G2_Kill_Password_h;
    WORD16 wREG_G2_Kill_Password_L;
    WORD16 wREG_G2_Kill_RFU;
    WORD16 wREG_G2_Block_Lock_MemBank;
    WORD16 wREG_G2_Blcokpermalock_EVB;
    WORD16 wREG_G2_Blockpermalock_Blockrange;
    WORD16 wREG_G2_Blockreadlock_mask;
} T_VirTagEffectiveRegs;

typedef struct tagT_VirTagSelectCmdPara
{
    BYTE ucMemBank;
    BYTE ucAction;
    WORD16 wAddr;
    WORD16 wMaskBitLen;
    WORD16 *pwMaskDataAddr;
}T_VirTagSelectCmdPara;

typedef struct tagT_WriteCmdPara
{
    WORD16 wWriteCmd;
    BYTE ucMemBank;
    BYTE ucPad;
    WORD16 wWriteAddr;
    WORD16 wWriteCount;
}T_WriteCmdPara;

typedef struct tagT_USP_VirTag6C
{
    WORD16 wKillState;
    WORD16 wAccessState;
    WORD16 wKillPassWordHigh;
    WORD16 wKillPassWordLow;
    WORD16 wAccessPassWordHigh;
    WORD16 wAccessPassWordLow;
    WORD16 wEpcState;
    WORD16 wEpcLen;
    BYTE aucEpc[VIR_TAG_EPC_LEN];
    WORD16 wTidState;
    WORD16 wTidLen;
    BYTE aucTid[VIR_TAG_TID_LEN];
    BYTE ucUserReadLockMask;
    BYTE ucUserPermaLockMask;
    WORD16 wUserState;
    WORD16 wUserLen;
    BYTE aucUser[VIR_TAG_USER_LEN];
} T_USPVirTag6C;


typedef struct tagT_USPVirTagConfig6cTag
{
    BYTE ucTagId;
    BYTE ucPad;
    T_USPVirTag6C t6cTag;
} T_USPVirTagConfig6cTag;


typedef struct tagT_USPVirTagConfig6cTagResponse
{
    WORD32 dwMsgId;
    WORD32 dwResult;
} T_USPVirTagConfig6cTagResponse;


typedef struct tagT_USPVirTagQuery6cTag
{
    BYTE ucTagId;
    BYTE ucPad;
    WORD16 wPad;
} T_USPVirTagQuery6cTag;

typedef struct tagT_USPVirTagQuery6cTagResponse
{
    WORD32 dwMsgId;
    WORD32 dwRet;
    T_USPVirTag6C t6cTag;
} T_USPVirTagQuery6cTagResponse;

typedef struct tagT_USPVirTagDelete6cTag
{
    BYTE ucTagId;
    BYTE ucPad;
    WORD16 wPad;
}T_USPVirTagDelete6cTag;

typedef struct tagT_USPVirTagDelete6cTagResponse
{
    WORD32 dwMsgId;
    WORD32 dwResult;
} T_USPVirTagDelete6cTagResponse;



/** 6b标签配置和查询接口 **/

typedef struct tagT_USP_VirTag6B
{
    BYTE ucPad;
    BYTE ucPad1;
} T_USPVirTag6B;


typedef struct tagT_USPVirTagConfig6bTag
{
    BYTE ucTagId;
    BYTE ucPad;
    T_USPVirTag6B t6bTag;
} T_USPVirTagConfig6bTag;

typedef struct tagT_USPVirTagConfig6bTagResponse
{
    WORD32 dwRet;
} T_USPVirTagConfig6bTagResponse;



typedef struct tagT_VirTagMsgProc
{
    WORD16 wMsgId;
    void (*pMsgFunc)(struct tagT_Msg *);
} T_VirTagMsgProc;

typedef struct tagT_VirTagList
{
    WORD32 dwListLength;
    BYTE aucFlag[VIR_TAG_MAX_SELECT_LIST_LEN];
} T_VirTagList;

typedef struct tagT_VirTagMatchAction
{
    void (*pActFunc)(BYTE , WORD32);
} T_VirTagMatchAction;

typedef struct tagT_VirTag6cCmdFunc
{
    WORD16 wCmdMask;
    WORD32(*pf6cCmdFunc)(T_VirTagEffectiveRegs *);
} T_VirTag6cCmdFunc;


extern void vir_tag_insertTagToSelectList(BYTE ucTagId);
extern void vir_tag_removeTagFromSelectList(BYTE ucTagId);
extern WORD32 vir_tag_isTagInSelectList(BYTE ucTagId);
extern WORD16 vir_tag_popTagFromSelectList(void);

extern void vir_tag_emptySelectList(void);
extern WORD32 vir_tag_getSelectListLength(void);
extern void vir_tag_printSelectList(void);

extern WORD32 vir_tag_matchMemory(BYTE *pucSrc, WORD16 wBitoffset,  BYTE *pucDest, WORD16 wMatchBitLen);



extern void vir_tag_matchDeselectUnmatchSelect(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchDeselectUnmatchNothing(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchNothingUnmatchSelect(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchReverseUnmatchNothing(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchSelectUnmatchDeselect(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchSelectUnmatchNothing(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchNothingUnmatchDeselect(BYTE ucTagId, WORD32 dwMatchResult);
extern void vir_tag_matchNothingUnmatchReverse(BYTE ucTagId, WORD32 dwMatchResult);


extern WORD32 vir_tag_deal6cSelect(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cQuery(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cAccess(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cRead(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cWrite(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cKill(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cLock(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cBlockLock(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cReadLock(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cQt(T_VirTagEffectiveRegs *ptRegs);
extern WORD32 vir_tag_deal6cBlockWrite(T_VirTagEffectiveRegs *ptRegs);
extern void vir_tag_changeLockBit(WORD16 wLockMask, WORD16 wAction, WORD16 *pwLockState);
void vir_tag_procMsg(T_Msg *ptRcvMsg);


/************************************************************************
*                           外部函数接口
**************************************************************************/
extern void usp_vir_fpga_initReg();
extern void usp_vir_fpga_writeReg(WORD32 wAddr, WORD16 wData);
extern WORD16 usp_vir_fpga_readReg(WORD32 wAddr);
extern WORD32 usp_vir_fpga_readFrame(BYTE *pucDataPacket, WORD32 dwDataLen, WORD32 *pdwReadLen);
extern void vir_tag_procPowerOn(int *ptRcvMsg);
extern void vir_tag_operateTag(T_Msg *ptRcvMsg);
extern void vir_tag_config6cTag(int *ptMsg);
extern void vir_tag_Query6cTag(int *ptMsg);
extern void vir_tag_Delete6cTag(int *ptMsg);
extern void vir_tag_Config6bTag(T_Msg *ptMsg);
extern void vir_tag_Query6bTag(T_Msg *ptMsg);


#endif


