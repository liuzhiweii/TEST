#ifndef UHF_LLRP_ISO6B_H
#define UHF_LLRP_ISO6B_H
#include "uhfllrpRule.h"
unsigned int llrp_ISO6BMatchRead(T_USPUHFISO6BTagId *ptISO6BTagId, unsigned short int wAntID, T_RdpLlrpISO6BTargetTag *ptISO6BTargetTag, T_USPUHFISO6BReadRes **ptISO6BReadRsp);
unsigned int llrp_ISO6BMatchAccessPattern(unsigned int dwByteLen, unsigned char *pucMatchData , T_RdpLlrpISO6BTargetTag *ptMatchISO6BTargetTag);
 void llrp_tagISO6BInvRsp(T_Msg *ptRcvMsg);
 void llrp_tagISO6BReadRsp(T_Msg *ptRcvMsg);
 void llrp_tagISO6BWriteRsp(T_Msg *ptRcvMsg);
 void llrp_tagISO6BLockRsp(T_Msg *ptRcvMsg);
 void llrp_tagISO6BLockQueryRsp(T_Msg *ptRcvMsg);
#endif

