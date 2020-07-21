#ifndef UHFGB_H
#define UHFGB_H

/* FPGA CPU命令类型寄存器的命令类型定义 */
#define CMD_REG_GB_SORT              (0x0001)
#define CMD_REG_GB_QUERY               (0x0002)
#define CMD_REG_GB_ACCESS              (0x0004)
#define CMD_REG_GB_READ                (0x0008)
#define CMD_REG_GB_WRITE               (0x0010)
#define CMD_REG_GB_KILL                (0x0020)
#define CMD_REG_GB_LOCK                (0x0040)
#define CMD_REG_GB_ERASE              (0x0100)
#define CMD_REG_GB_LLRP_OPERATION      (0x0100)

/* Query命令参数定义 */
#define GB_QUERY_TARGET_A     (0)
#define GB_QUERY_TARGET_B     (1)

/* QUERY命令SESSION参数定义 */
#define GB_QUERY_SESSION_S0   (0)
#define GB_QUERY_SESSION_S1   (1)
#define GB_QUERY_SESSION_S2   (2)
#define GB_QUERY_SESSION_S3   (3)


#define GB_MAX_LENGTH         (64)
#define GB_READ_WRITE_MAX_LEN (127)
#define GB_MAX_MEM_BLOCK_LEN  (4)
#define GB_MAX_MASK_WORD_NUM  (32)   /*GB最大掩码字数*/

#define ZTE_RF_MODEINDEX     (10000)

void MarkInventoryStart();
void MarkInventoryFinish();
void uhf_GB_InitCtrlStruct();
WORD32 uhf_GB_startInventory(T_USPUHFGBInventory *ptGBTagInventory);
WORD32 uhf_GB_startQuery();
WORD32 uhf_GB_startRead(T_USPUHFGBRead *ptGBRead);
WORD32 uhf_GB_startWrite(T_USPUHFGBWrite *ptGBWrite);
WORD32 uhf_GB_startLock(T_USPUHFGBLock *ptGBLock);
WORD32 uhf_GB_startKill(T_USPUHFGBKill *ptGBKill);
WORD32 uhf_GB_startErase(T_USPUHFGBErase *ptGBErase);

WORD32 SetGBInventoryPara(T_USPUHFGBInventoryPara *ptGBInventoryPara,
                         WORD16 wAntInde,WORD16 *pwFpgaInventoryCommand);
void SetGBReadPara(T_USPUHFGBReadPara *ptGBReadPara,
                    WORD16 *pwFpgaGBReadCommand);
void SetGBWritePara(T_USPUHFGBWritePara *ptGBWritePara,
                     WORD16 *pwFpgaGBWriteCommand);
WORD32 SetGBLockPara(T_USPUHFGBLockPara *ptGBLockPara,
                    WORD16 *pwFpgaGBLockCommand);

void SetGBKillPara(T_USPUHFGBKillPara *ptGBKillPara, WORD16 *pwMacGBKillCommand);
void SetGBKillErase(T_USPUHFGBErasePara *ptGBErasePara, WORD16 *pwMacGBEraseCommand);


#endif

