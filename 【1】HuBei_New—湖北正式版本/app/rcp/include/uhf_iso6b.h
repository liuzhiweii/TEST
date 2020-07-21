#ifndef UHF_ISO6B_H
#define UHF_ISO6B_H
#define ISO6B_READLENGTH     (8)
#define ISO6B_BYTE_UNLOCKED  (0)
#define ISO6B_BYTE_LOCKED    (1)

void  uhf_ISO6B_InitCtrlStruct(void);
void uhf_ISO6B_Cal_Mode_Para(WORD16 ModeIndex);
WORD32 uhf_ISO6B_Read_8_byte(WORD16 wStartAddr, BYTE ucLen, BYTE *aucRcvBuf);
WORD32 uhf_ISO6B_ReadData(T_USPUHFISO6BRead *ptISO6BReadPara,T_USPUHFISO6BReadRes *ptISO6BReadRes);
WORD32 uhf_ISO6B_WriteByte(WORD16 wStartAddr, BYTE ucMask, BYTE *pucWriteData);
WORD32 uhf_ISO6B_Write_4_byte(WORD16 wStartAddr, BYTE ucMask, BYTE *pucWriteData);
WORD32 uhf_ISO6B_8Byte_Verify_Write(WORD16 wStartAddr, WORD16 wLen, WORD16 *pwWriteSuccessLen, BYTE *pucWriteData, BYTE ucByteWriteMask, WORD16 wRetryTimes, WORD16 wVerifyTimes);
WORD32 uhf_ISO6B_4X2Byte_Verify_Write(WORD16 wStartAddr, WORD16 wLen, WORD16 *pwWriteSuccessLen, BYTE *pucWriteData, BYTE ucByteWriteMask, WORD16 wRetryTimes, WORD16 wVerifyTimes);
WORD32 uhf_ISO6B_WriteData(T_USPUHFISO6BWrite *ptISO6BWritePara, T_USPUHFISO6BWriteRes *ptISO6BWriteRes);
WORD32 uhf_ISO6B_LockByte(WORD16 wStartAddr, BYTE wLen,/*没用*/BYTE *pucState/*没用*/);
WORD32 uhf_ISO6B_LockData(T_USPUHFISO6BLock *ptISO6BLockPara, T_USPUHFISO6BLockRes *ptISO6BLockRes);
WORD32 uhf_ISO6B_LockQueryByte(WORD16 wStartAddr, BYTE ucLen, BYTE *pucLockStat);
WORD32 uhf_ISO6B_LockQueryData(T_USPUHFISO6BLockQuery *ptISO6BLockQueryPara, T_USPUHFISO6BLockQueryRes *ptISO6BLockQueryRes);
WORD32 uhf_ISO6B_Write_8_Byte(WORD16 wStartAddr, WORD16 wLength, WORD16 *pwWriteSuccessLen, BYTE *pucWriteData, BYTE ucByteWriteMask, WORD16 wRetryTimes);
WORD32 uhf_ISO6B_Write_8_ByteVerify(WORD16 wStartAddr, WORD16 wLength, BYTE *pucWriteData, BYTE *pByteWriteMask, WORD16 wRetryTimes);
WORD32 uhf_ISO6B_Write_4x2_Byte(WORD16 wStartAddr, WORD16 wLength, WORD16 *pwWriteSuccessLen, BYTE *pucWriteData, BYTE ucByteWriteMask, WORD16 wRetryTimes);
WORD32 uhf_ISO6B_Write_4x2_ByteVerify(WORD16 wStartAddr, WORD16 wLength, BYTE *pucWriteData, BYTE *pByteWriteMask, WORD16 wRetryTimes);
WORD32 uhf_ISO6B_LockByteVerify(WORD16 wStartAddr, WORD16 wRetryTimes, WORD16 wVerifyTimes);
WORD32 uhf_ISO6BGetATag(WORD16 *pwRSSI, BYTE *pucUID);
WORD32 uhf_ISO6B_Process_Start(WORD32 dwAntIndex);
WORD32 uhf_ISO6B_Inventory_Start(T_USPUHFISO6BInventory *ptISO6BInventoryPara);

#endif
