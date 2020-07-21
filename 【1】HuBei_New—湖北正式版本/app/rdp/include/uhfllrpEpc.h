#ifndef UHF_LLRP_EPC_H
#define UHF_LLRP_EPC_H
#include "uhfllrpRule.h"

#define  LLRP_AI_NEXT_INV                              1
#define  LLRP_AP_CONTINUE_INV                      2
#define  LLRP_AI_DONE_INV                             3
#define  LLRP_RO_DONE_INV                            4
#define  LLRP_AI_CONTINUE_INV                      5

void llrp_sendNextEpcInv();
void llrp_sendNextISO6BInv();
void llrp_sendNextGBInv();
 unsigned int llrp_nextEpcAccessOp(T_Msg *ptSndMsg ,T_RdpLlrpListOPCtrlSet*ptlistOpCtrlSet,void *ptTagID);
 unsigned int llrp_nextISO6BAccessOp(T_Msg *ptSndMsg ,T_RdpLlrpListOPCtrlSet*ptlistOpCtrlSet,void *ptTagID);
void llrp_assembleEpcInvPara( unsigned char ucAntennaIndex,T_RdpLlrpProtocolInvSet *ptTempProtocolPara,T_USPUHFEpcInventory *ptUSPUHFEpcInventory);
void llrp_assembleEpcInvProtocolPara( unsigned char ucAntennaIndex, T_RdpLlrpProtocolInvSet*ptTempProtocolPara, T_USPUHFEpcInventory *ptUSPUHFEpcInventory);
void llrp_assembleISO6BInvPara( unsigned char ucAntennaIndex,T_RdpLlrpProtocolInvSet*ptTempProtocolPara,T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory);
void llrp_assembleISO6BInvProtocolPara( unsigned char ucAntennaIndex,T_RdpLlrpProtocolInvSet*ptTempProtocolPara,T_USPUHFISO6BInventory *ptUSPUHFISO6BInventory);
void llrp_frequencyTransfer(unsigned short int whopid, T_USPUHFFreqHopChannel *ptFreqChannel);
unsigned int  llrp_matchAccess(LLRP_tEAirProtocols eProtocolID,unsigned short int wAntID,void *pTaID );
void llrp_dispatchTagInv();
T_RdpLlrpListOPCtrlSet *llrp_getRunListOpSet();
void llrp_dispatchTagAccess();
 void llrp_tagEpcInvRsp(T_Msg *ptRcvMsg);
 void llrp_tagEpcReadRsp(T_Msg *ptRcvMsg);
 void llrp_tagEpcWriteRsp(T_Msg *ptRcvMsg);
 void llrp_tagEpcLockRsp(T_Msg *ptRcvMsg);
 void llrp_tagEpcBlockLockRsp(T_Msg *ptRcvMsg);
 void llrp_tagEpcReadLockRsp(T_Msg *ptRcvMsg);
  void llrp_tagEpcIPJQTRsp(T_Msg *ptRcvMsg);
  void llrp_tagEpcKillRsp(T_Msg *ptRcvMsg);
   void llrp_tagEpcVeriyReadRsp(T_Msg *ptRcvMsg);
   void llrp_clientRequestRsp(T_Msg *ptRcvMsg);
 void llrp_dealRcpRspTimeOut(T_Msg *ptRcvMsg);
unsigned int llrp_getPassword(void * Para ,unsigned int *pdwAccessPassword);
void llrp_setEpcAccessFlag();
#endif
