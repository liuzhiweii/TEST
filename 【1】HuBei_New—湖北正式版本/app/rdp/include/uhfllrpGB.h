#ifndef _UHF_LLRP_GB_H
#define _UHF_LLRP_GB_H
#include "uhfllrpRule.h"

void llrp_assembleGBInvPara( unsigned char ucAntennaIndex,T_RdpLlrpProtocolInvSet *ptTempProtocolPara,T_USPUHFGBInventory *ptUSPUHFGBInventory);
void llrp_tagGBInvRsp(T_Msg *ptRcvMsg);
void llrp_tagGBReadRsp(T_Msg *ptRcvMsg);
void llrp_tagGBWriteRsp(T_Msg *ptRcvMsg);
void llrp_tagGBEraseRsp(T_Msg *ptRcvMsg);
void llrp_tagGBLockRsp(T_Msg *ptRcvMsg);
void llrp_tagGBKillRsp(T_Msg *ptRcvMsg);
unsigned int llrp_getGBAccessPassword(T_USPUHFGBTagId *ptGBTagId, unsigned short int wAntID, unsigned int *pdwAccessPassword);
unsigned int llrp_GBMatchRead(T_USPUHFGBTagId *ptGBTagId, unsigned short int wAntID, T_RdpLlrpGBTargetTag *ptGBTargetTag, T_USPUHFGBReadRes **ptGBReadRsp, T_RdpLlrpAccess*ptMatchAccess);
unsigned int llrp_GBMatchAccessPattern(unsigned int dwByteLen, unsigned char *pucMatchData , T_RdpLlrpGBTargetTag *ptMatchGBTargetTag);
void llrp_setGBAccessFlag();
void llrp_ClearGBAccessFlag();
unsigned int llrp_getOpGBAccessPassword(unsigned int dwOpAccessPassword, T_USPUHFGBTagId * ptGBTagId, unsigned short int wAntID);
unsigned int llrp_nextGBAccessOp(T_Msg *ptSndMsg , T_RdpLlrpListOPCtrlSet*ptlistOpCtrlSet, void *ptTagID);
#endif
