#ifndef UHF_LLRP_DISPATCH_H
#define UHF_LLRP_DISPATCH_H

#include "uhfllrpRule.h"
#define USP_LIB_UHF_MAX_PWDINDEX_LEN           32
#define USP_LIB_UHF_MAX_CMDPARA_LEN            64
#define  LLRP_PWD_DLL_PATH    "/cust/libuhfif.so.1"
typedef void ( * llrp_dealmsg )(T_Msg *);
typedef struct tagT_LlrpDispatchMsg
{
    unsigned int dwBeginMsgID;
    unsigned int dwEndMsgID;
    llrp_dealmsg pfllrp_dealmsg;

}T_LlrpDispatchMsg;

typedef struct tagT_RdpLlrpPwdIndexPara
{
    unsigned int dwMembank;
    unsigned short int wWordPointer;
    unsigned short int wWordCount;
    unsigned short int wPwdIndexBuffer[USP_LIB_UHF_MAX_PWDINDEX_LEN];
} T_RdpLlrpPwdIndexPara; 
typedef   unsigned int ( * PwdFun)();
typedef struct tagT_RdpLlrpPwdSys
{
    void *pdllHandle;
    PwdFun pfusp_lib_uhf_privateCmd;
    PwdFun pfusp_lib_uhf_getPassword;
    unsigned int dwPwdIndexNum;
    T_RdpLlrpPwdIndexPara   atPwdIndexPara[LLRP_MAX_PWDINDEX_NUM];
} T_RdpLlrpPwdSys; 

void llrp_nextTagAccessOp(T_RdpLlrpListOPCtrlSet*ptlistOpCtrlSet, LLRP_tEAirProtocols eProtocolID, void *ptTagID);
T_RdpLlrpAI * llrp_getRunAI();
T_RdpLlrpROCtrlAndParam * llrp_getRunRO();
T_RdpLlrpAccessCtrlAndParam* llrp_getRunAccess();
unsigned int llrp_cfgChangeRefresh();
T_RdpLlrpAntInv * llrp_getRunAnt();
T_RdpLlrpProtocolInvSet * llrp_getRunAP(); 
void llrp_dealCommNoticeMsg(T_Msg *ptRcvMsg);
 unsigned int llrp_tagInventory(T_RdpLlrpROCtrlAndParam *ptRdpLlrpROCtrlAndParam);
 T_RdpLlrpROEntry * llrp_findAndGetAnNodeFoAllQueueOfRO(T_RdpLlrpROEntry *ptQueueHead, unsigned int dwROIndex, unsigned int dwPriority);
void llrp_insertAnNodetoPriorityQueueOfRO(T_RdpLlrpROEntry *ptInsertNode, T_RdpLlrpROEntry *ptReadyQueueHead);
void llrp_buildAnNodeFoAllQueueOfAccess(T_RdpLlrpAccessEntry *ptQueueHead, unsigned int dwAccessIndex);
unsigned int llrp_findAndFreeAnNodeFoAllQueueOfAccess(T_RdpLlrpAccessEntry *ptQueueHead, unsigned int dwAccessIndex);
void llrp_insertAnNodetoAllQueueOfRO(T_RdpLlrpROEntry *ptInsertNode, T_RdpLlrpROEntry *ptQueueHead);
void llrp_buildAnNodeFoAllQueueOfRO(T_RdpLlrpROEntry *ptQueueHead, unsigned int dwROIndex, unsigned int dwPriority);
unsigned int llrp_findAndFreeAnNodeFoAllQueueOfRO(T_RdpLlrpROEntry *ptQueueHead, unsigned int dwROIndex, unsigned int dwPriority);
void llrp_dealUhfPrivateCmd(T_Msg *ptRcvMsg);
void llrp_dealUhfPrivateSetPassword(T_Msg *ptRcvMsg);
void  llrp_loadUserDll();
unsigned int rdp_rule_main();
unsigned int rdp_report_main();


#endif
