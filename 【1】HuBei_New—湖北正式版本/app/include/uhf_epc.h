#ifndef UHFEPC_H
#define UHFEPC_H

/* FPGA CPU命令类型寄存器的命令类型定义 */
#define CMD_REG_EPC_SELECT              (0x0001)
#define CMD_REG_EPC_QUERY               (0x0002)
#define CMD_REG_EPC_ACCESS              (0x0004)
#define CMD_REG_EPC_READ                (0x0008)
#define CMD_REG_EPC_WRITE               (0x0010)
#define CMD_REG_EPC_KILL                (0x0020)
#define CMD_REG_EPC_LOCK                (0x0040)
#define CMD_REG_EPC_BLOCK_WRITE         (0x0080)
#define CMD_REG_EPC_BLOCK_LOCK          (0x0200)
#define CMD_REG_EPC_BLOCK_LOCK_QUERY    (0x0300)
#define CMD_REG_EPC_READ_LOCK           (0x0400)
#define CMD_REG_EPC_GROUP_READ_WRITE    (0x0800)
#define CMD_REG_EPC_LLRP_OPERATION      (0x1000)
#define CMD_REG_EPC_IPJ_QT              (0x2000)



/* Query命令参数定义 */
#define EPC_QUERY_TARGET_A     (0)
#define EPC_QUERY_TARGET_B     (1)

/* QUERY命令SESSION参数定义 */
#define EPC_QUERY_SESSION_S0   (0)
#define EPC_QUERY_SESSION_S1   (1)
#define EPC_QUERY_SESSION_S2   (2)
#define EPC_QUERY_SESSION_S3   (3)


#define EPC_MAX_LENGTH         (64)
#define EPC_READ_WRITE_MAX_LEN (127)
#define EPC_MAX_MEM_BLOCK_LEN  (3)
#define EPC_MAX_MASK_WORD_NUM  (32)   /*EPC最大掩码字数*/

#define ZTE_RF_MODEINDEX     (10000)
#define EPC_IPJ_QT_READ   (0)
#define EPC_IPJ_QT_WRITE  (1)

#define  EPC_IPJ_QT_NOT_PERSIS (0)
#define  EPC_IPJ_QT_PERSIS     (1)

#define  EPC_IPJ_QT_NOT_REDUCE (0)
#define  EPC_IPJ_QT_REDUCE     (1)

#define  EPC_IPJ_QT_MEM_PUB     (1)
#define  EPC_IPJ_QT_MEM_PRIVATE (0)


void MarkInventoryStart();
void MarkInventoryFinish();
void uhf_Epc_InitCtrlStruct();
WORD32 uhf_epc_startInventory(T_USPUHFEpcInventory *ptEpcTagInventory);
WORD32 uhf_epc_startQuery();
WORD32 uhf_epc_startRead(T_USPUHFEpcRead *ptEpcRead);
WORD32 uhf_epc_startWrite(T_USPUHFEpcWrite *ptEpcWrite);
WORD32 uhf_epc_startLock(T_USPUHFEpcLock *ptEpcLock);
WORD32 uhf_epc_startKill(T_USPUHFEpcKill *ptEPCKill);
WORD32 uhf_epc_startBlockLock(T_USPUHFEpcBlockLock *ptEpcBlockLock);
WORD32 uhf_epc_startReadLock(T_USPUHFEpcReadLock *ptEpcReadLock);
WORD32 uhf_epc_startIPJQT(T_USPUHFEpcIPJQT *ptEpcIPJQT);

WORD32 SetEpcInventoryPara(T_USPUHFEpcInventoryPara *ptEPCInventoryPara,
                         WORD16 wAntInde,WORD16 *pwFpgaInventoryCommand);
void SetEpcReadPara(T_USPUHFEpcReadPara *ptEPCReadPara,
                    WORD16 *pwFpgaEpcReadCommand);
void SetEpcWritePara(T_USPUHFEpcWritePara *ptEPCWritePara,
                     WORD16 *pwFpgaEpcWriteCommand);
WORD32 SetEpcLockPara(T_USPUHFEPcLockPara *ptEPCLockPara,
                    WORD16 *pwFpgaEpcLockCommand);
WORD32 SetEpcImpinjQtPara(T_USPUHFEpcIPJQTPara*ptEPCIPJQTPara,
                      WORD16 *pwFpgaEpcImpinjQtCommand);

void SetEpcKillPara(T_USPUHFEpcKillPara *ptEPCKillPara, WORD16 *pwMacEpcKillCommand);

WORD32 SetEpcBlockLockPara(T_USPUHFEpcBlockLockPara *ptEPCBlockLockPara,
                         WORD16 *pwMacEpcBlockLockCommand);

void SetEpcReadLockPara(T_USPUHFEpcReadLockPara *ptEPCReadLockPara,
                        WORD16 *pwmacEpcReadLockCommand);

#endif

