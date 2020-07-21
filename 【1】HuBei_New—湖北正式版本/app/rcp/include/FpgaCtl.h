
#ifndef _FPGACTL_H
#define _FPGACTL_H


/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/ 
#define DEV_FPGA      "/dev/misc/usp_drv_fpga1"

/*FPGA->CPU的命令消息*/
/* FPGA命令类型 */
#define DRV_FPGA_CMD_READ_REG          (1)   /*  */
#define DRV_FPGA_CMD_WRITE_REG         (2)  /*  */
#define DRV_FPGA_CMD_EPC_INVENTORY     (3)  /*  */
#define DRV_FPGA_CMD_EPC_READ          (4)  /*  */
#define DRV_FPGA_CMD_EPC_WRTIE         (5)  /*  */
#define DRV_FPGA_CMD_READ_FRAME        (6)
#define DRV_FPGA_CMD_SET_EPC_MASK_DATA (7)
#define DRV_FPGA_CMD_SET_EPC_READ_PARA (8)
#define DRV_FPGA_CMD_SET_EPC_WRITE_PARA (9)
#define DRV_FPGA_CMD_ENABLE_INTERRUPT   (10)
#define DRV_FPGA_CMD_SET_EPC_LOCK_PARA  (11)
#define DRV_FPGA_CMD_SET_EPC_ACCESS_PARA  (12)
#define DRV_FPGA_CMD_SET_EPC_KILL_PARA  (13)


#define  FPGA_BLKPERMALOCK_CMD_MSG      (0xa)
#define  FPGA_BLKPERMALOCK_QUERY_MSG    (0x9)

/* FPAG响应frame的标志定义 */
#define FPGA_FRAME_FLAG_SUCCESSS          (0x1) /* 成功     */
#define FPGA_FRAME_FLAG_FAIL              (0x0) /* 失败     */
#define FPGA_FRAME_FLAG_INVENT_FINISH     (0x2) /* 清点结束 */
#define FPGA_FRAME_FLAG_NO_RESPONSE       (0x3)

/* FPGA驱动读写访问缓存大小 */
#define FPGA_BUF_BYTE_SIZE (1024)

/*向FPGA发送命令后的超时时间*/
#define FPGA_TIMEOUT_INTERVAL_IN_MS    (2000)

/* 中断屏蔽/使能寄存器INTM, 相应位置1打开该位对应的中
断，置0屏蔽。默认屏蔽所有中断。*/
#if (UHF_BOARD_TYPE == BOARD_TYPE_RFCB_BT) || (UHF_BOARD_TYPE == BOARD_TYPE_RFCB7)
#define RIS_EPLD_OFST_INTR_EN_MASK_REG		(0x94 >> 1)
#else
#define RIS_EPLD_OFST_INTR_EN_MASK_REG		0x94
#endif
#define START_FPGA_RF_TX     (1)   /* 启动射频功率发送；  */
#define STOP_FPGA_RF_TX      (0)   /* 关闭射频功率发送 */

#define FPGA_INT_ENABLE   (1)
#define FPGA_INT_DISABLE  (0)


#if 1
extern  WORD32 g_dwUSPUhfVirTagWorkFlag;
extern  WORD16 usp_vir_fpga_readReg(WORD32 wAddr);
extern  void usp_vir_fpga_writeReg(WORD32 wAddr, WORD16 wData);
extern  WORD32 usp_vir_fpga_readFrame(BYTE *pucDataPacket, WORD32 dwDataLen, WORD32 *pdwReadLen);

#define FpgaRegWrite(wRegAddr,wData) \
do\
{\
    if(g_dwUSPUhfVirTagWorkFlag == TRUE) \
    {\
        usp_vir_fpga_writeReg(wRegAddr, wData); \
    }\
    else\
    {\
        g_pvUSPDrvFpgaVirtStartAddr0[wRegAddr]=wData; \
    }\
}while(0)

#define FpgaRegRead(wRegAddr)  (g_dwUSPUhfVirTagWorkFlag == TRUE) ? \
         usp_vir_fpga_readReg(wRegAddr) : g_pvUSPDrvFpgaVirtStartAddr0[wRegAddr]
#else
#define FpgaRegWrite(wRegAddr,wData)   g_pvUSPDrvFpgaVirtStartAddr0[wRegAddr]=wData
#define FpgaRegRead(wRegAddr)          g_pvUSPDrvFpgaVirtStartAddr0[wRegAddr]
#endif

#define SetProtoType(wProtoType)       FpgaRegWrite(REG_PROTO_TYPE,wProtoType)
#define SetRbModulateType(wType)       FpgaRegWrite(reg_rb_module_type,wType)

#define uhf_FPGAIntEnCtrl(wAction)        \
   if(wAction == FPGA_INT_ENABLE)  \
   {\
     g_pvUSPDrvEpldVirtStartAddr0[RIS_EPLD_OFST_INTR_EN_MASK_REG] |= 0x1;\
   }else\
   {\
     g_pvUSPDrvEpldVirtStartAddr0[RIS_EPLD_OFST_INTR_EN_MASK_REG] &= 0xFE;\
   }



/****************************************公共接口相关******************/
WORD32 uhf_readFpgaFrame(WORD16 *pwReadLen);
WORD32 uhf_StopMacProc(void);
WORD32 uhf_mac_Init(void);

/****************************************EPC口函数******************/
void uhf_epc_setTimePara(void);
void uhf_EpcSetSelectPara(WORD16 wTruncate,WORD16 wMemBank,WORD16 wAction,WORD16 wTarget);
void uhf_EpcSetMacQueryPara(WORD16 wQ,WORD16 wM,WORD16 wDR);
void uhf_EpcSetMacReadLock(WORD16 wReadLockMask);
void uhf_EpcSetMacIPJQT(BYTE ucReadOrWrite, BYTE ucPersistence,
                               BYTE ucQT_SR,BYTE ucQT_MEM);
void uhf_EpcSetMacBlockLock(BYTE ucReadLock,WORD16 wMemBank,WORD16 wBlockPtr,
                                      WORD16 wBlockRang,BYTE *ucdata);
void uhf_EpcSetMacKillPara(WORD32 dwKillPassword);
void uhf_EpcSetMacAccessPara(WORD32 dwAccessPassword);
void uhf_EpcSetMacLockPara(WORD32 dwLockPayLoad);
void uhf_EpcSetMacBlockWritePara(WORD16 wMemBank,WORD16 wAddr,WORD16 wWrWordLen,BYTE *ucdata);
void uhf_EpcSetMacWritePara(WORD16 wMemBank,WORD16 wAddr,WORD16 wWrWordLen,BYTE *ucdata);
void uhf_EpcSetMacReadPara(WORD16 wMemBank,WORD16 wAddr,WORD16 wWordCount);
void uhf_epc_setSelectMask(WORD16 wAddr,WORD16 wMaskBitLen,WORD16 *pwData);
void uhf_EpcStartProcAndTimer(WORD16 wCmdType);
void uhf_EpcStartLlrpProcAndTimer(WORD16 wCmdType);

/****************************************ISO接口函数***************/
void uhf_ISO6BSetInventoryPara(WORD16 wISOCommand, WORD16 wMaskByteAddr, 
  WORD16 wInventQ, WORD16 wMask, WORD16 wDataReadStartAddr, BYTE * pucMaskData);
void uhf_ISO6BSetLockQueryPara(WORD16 wStartAddr);
void uhf_ISO6BSetLockBytePara(WORD16 wStartAddr);
void uhf_ISO6BSetWrite4BytePara(WORD16 wStartAddr, BYTE *pucWriteData);
void uhf_ISO6BSetWriteBytePara(WORD16 wStartAddr, BYTE *pucWriteData);
void uhf_ISO6BSetReadVrblPara(WORD16 wStartAddr, WORD16 wFpgaReadLen);
void uhf_ISO6BSetRead8BytePara(WORD16 wStartAddr);
void uhf_ISO6BSetUIDPara(BYTE *pucUID);
void uhf_ISO6BSetProtoPara(WORD16 wFowardLinkDataRate, WORD16 wReverseLinkDataRate,
     WORD16 wT1_value, WORD16 wdelimeters, WORD16 wISO6BModulateDepth);
void uhf_IsoStartProcAndTimer(void);


void uhf_TxSet(WORD16 wFpgaTxAction);
void uhf_StopTx(void);

///////////////////////////
////  GB Function Interface
///////////////////////////
void uhf_GB_setTimePara(void);
void uhf_GB_setSelectMask(WORD16 wAddr, WORD16 wMaskBitLen, WORD16 *pwData);
void uhf_GBStartLlrpProcAndTimer(WORD16 wCmdType);
void uhf_GBStartProcAndTimer(WORD16 wCmdType);

void uhf_GBSetSelectPara(WORD16 wRule,WORD16 wTarget, WORD16 wMemBank);
void uhf_GBSetMacQueryPara(BYTE ucM, BYTE ucReLinkRateDivisor);
void uhf_GBSetMacErasePara(WORD16 wMemBank, WORD16 wAddr, WORD16 wErWordLen);
void uhf_GBSetMacAccessPara(WORD32 dwAccessPassword,BYTE ucMB,BYTE ucAccessType);
void uhf_GBSetMacLockPara(BYTE ucDataArea,BYTE ucAreaCfg, BYTE ucAreaAction, BYTE ucSecAction );
void uhf_GBSetMacReadPara(BYTE ucMemBank, WORD16 wAddr, WORD16 wWordCount);
void uhf_GBSetMacWritePara(WORD16 wMemBank, WORD16 wAddr, WORD16 wWrWordLen, BYTE *ucdata);
void uhf_GBSetMacKillPara(WORD32 dwKillPassword);

#endif


