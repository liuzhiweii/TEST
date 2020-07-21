#ifndef UHF_LLRP_REPORT_H
#define UHF_LLRP_REPORT_H
#include "uhfllrpRule.h"
void llrp_freeReportToROReportLink(T_RdpLlrpAcculateReportData *ptActiveRoReportLink);
void llrp_constructLocalROReport(unsigned short int wProtoType,
                                 unsigned short int wAntennaIndex,
                                 unsigned short int wRssi,
                                 unsigned short int wPC,
                                 unsigned short int wCRC,
                                 unsigned short int wChannelIndex,
                                 unsigned short int wTagLen,
                                 unsigned char *pbTagID);
 void llrp_constructLocalAOReportHead(unsigned short int wProtoType,
                                     unsigned short int wAntennaIndex,
                                     unsigned short int wRssi,
                                     unsigned short int wPC,
                                     unsigned short int wCRC,
                                     unsigned short int wChannelIndex,
                                     unsigned short int wTagLen,
                                     unsigned char *pbTagID);   
void llrp_sendReport(T_RdpLlrpSingleReportCtrl *ptSendReport, T_Msg *ptSndMsg, unsigned int dwMessgeID);
void llrp_insertReportToRunRoReportLink(T_RdpLlrpSingleReportCtrl *ptLocalSingleReportCtrl);
unsigned int llrp_getRunRoMsgID();                                
#endif
