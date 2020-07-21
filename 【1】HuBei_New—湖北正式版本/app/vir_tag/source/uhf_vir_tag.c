//#include "usp.h"
//#if  (USP_VIR_TAG_USE) && (UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)

#include <zmq.h>
#include "usp_typeDef.h"
#include "usp_pub.h"
#include "usp_vos.h"
#include "usp_ipc.h"
#include "usp.conf"
#include "scp.conf"
#include "uhf.conf"
#include "usp_uhf_cfg.h"
#include "usp_scp.h"
#include "usp_eventDef.h"
#include "uhf_vir_tag.h"
#include "usp_uhf_epc.h"
#include "uhf_epc.h"
#include "uhf.h"
#include "uhf_vir_fpga.h"
#include "logm.h"

#define get_6c_tag_ptr(wTagId) (wTagId< VIR_TAG_MAX_6C_TAG_NUM) ? s_aptVirTag6cTags[wTagId] : NULL


T_USPVirTag6C *s_aptVirTag6cTags[VIR_TAG_MAX_6C_TAG_NUM] = {0};
T_USPVirTag6B *s_aptVirTag6bTags[VIR_TAG_MAX_6B_TAG_NUM];
T_VirTagList s_tVirTagSelectList;
WORD16 s_wVirTagActive6cTagId = VIR_TAG_INVALID_ID;
WORD32 s_dwVirTagActive6cTagAccessFlag = FALSE;
WORD32 s_dwVirTagMacState = VIR_TAG_MAC_NOT_START;

T_VirTagMsgProc s_atVirTagMsgProcTable[] = \
{
    //{EV_USP_SCP_PowerOn, vir_tag_procPowerOn},
    {EV_USP_COMM_LinkOpened, vir_tag_procLinkOpend},
    {0x0003, vir_tag_config6cTag},
    {0x0005, vir_tag_Query6cTag},    
    {0x0001, vir_tag_Delete6cTag},
    {EV_USP_VIR_TAG_Config6bTag, vir_tag_Config6bTag},
    {EV_USP_VIR_TAG_Config6bTag, vir_tag_Query6bTag},
    {0x0007, vir_tag_remove6cTagAll},
    {EV_USP_VIR_TAG_Remove6bTagAll, vir_tag_remove6bTagAll},
    {EV_USP_VIR_TAG_StartCmd, vir_tag_startCmd},
    {EV_USP_VIR_TAG_StartLlrpCmd, vir_tag_startLlrpCmd},
    {EV_USP_VIR_TAG_StopCmd, vir_tag_stopCmd}
};

T_VirTagMatchAction s_atVirTagMatchActTable[] = { \
    {vir_tag_matchDeselectUnmatchSelect},
    {vir_tag_matchDeselectUnmatchNothing},
    {vir_tag_matchNothingUnmatchSelect},
    {vir_tag_matchReverseUnmatchNothing},
    {vir_tag_matchSelectUnmatchDeselect},
    {vir_tag_matchSelectUnmatchNothing},
    {vir_tag_matchNothingUnmatchDeselect},
    {vir_tag_matchNothingUnmatchReverse}
};

T_VirTag6cCmdFunc s_atVirTag6cCmdFuncTable[] = \
{
    {CMD_REG_EPC_SELECT, vir_tag_deal6cSelect},
    {CMD_REG_EPC_QUERY, vir_tag_deal6cQuery},
    {CMD_REG_EPC_ACCESS, vir_tag_deal6cAccess},
    {CMD_REG_EPC_READ, vir_tag_deal6cRead},
    {CMD_REG_EPC_WRITE, vir_tag_deal6cWrite},
    {CMD_REG_EPC_KILL, vir_tag_deal6cKill},
    {CMD_REG_EPC_LOCK, vir_tag_deal6cLock},
    {CMD_REG_EPC_BLOCK_LOCK, vir_tag_deal6cBlockLock},
    {CMD_REG_EPC_READ_LOCK, vir_tag_deal6cReadLock},
    {CMD_REG_EPC_IPJ_QT, vir_tag_deal6cQt},
    {CMD_REG_EPC_BLOCK_WRITE, vir_tag_deal6cWrite}
};

/* 和rcp模块共享的内存和互斥锁 */
USP_OssIpcMutex s_tUSPVirTagMutex;
WORD16 *s_pwUSPVirTagFrameBuf = NULL;  /* 存放FPGA返回的帧 */
WORD32 *s_pdwUspVirTagFrameReadyFlag = NULL;   /* 返回帧准备好的标志 */

/* 和pc通信的配置链路 */
BYTE s_ucVirTagLinkType;
BYTE s_ucVirTagLinkIndex;

void *rep_socket = NULL;
void *pull_socket = NULL;

void vir_tag_takeMutex(void)
{
    logm_debug("(vir_tag) take mutex \r\n");
    //USP_OSS_IPC_TAKE_MUTEX(s_tUSPVirTagMutex); 

    return;
}

void vir_tag_giveMutex(void)
{
    logm_debug("(vir_tag) give mutex \r\n");
    //USP_OSS_IPC_GIVE_MUTEX(s_tUSPVirTagMutex);
    return;
}


void vir_tag_removeTagFromSelectList(BYTE ucTagId)
{
    if (s_tVirTagSelectList.aucFlag[ucTagId])
    {
        s_tVirTagSelectList.dwListLength--;
        s_tVirTagSelectList.aucFlag[ucTagId] = 0;
    }

    return;
}


WORD32 vir_tag_isTagInSelectList(BYTE ucTagId)
{
    return s_tVirTagSelectList.aucFlag[ucTagId];
}


void vir_tag_insertTagToSelectList(BYTE ucTagId)
{
    if (s_tVirTagSelectList.aucFlag[ucTagId] == 0)
    {
        s_tVirTagSelectList.aucFlag[ucTagId] = 1;
        s_tVirTagSelectList.dwListLength++;
    }

    return;
}


WORD16 vir_tag_popTagFromSelectList(void)
{
    WORD16 wIndex;

    for (wIndex = 0; wIndex < VIR_TAG_MAX_SELECT_LIST_LEN; wIndex++)
    {
        if (s_tVirTagSelectList.aucFlag[wIndex])
        {
            s_tVirTagSelectList.aucFlag[wIndex] = 0;
            s_tVirTagSelectList.dwListLength--;
            return wIndex;
        }
    }

    return VIR_TAG_INVALID_ID;
}

void vir_tag_emptySelectList(void)
{
    memset(&s_tVirTagSelectList, 0, sizeof(s_tVirTagSelectList));
    return;
}

WORD32 vir_tag_getSelectListLength(void)
{
    return s_tVirTagSelectList.dwListLength;
}

void vir_tag_printSelectList(void)
{
    WORD16 wIndex;

    logm_debug("start print select list \r\n");

    for (wIndex = 0; wIndex < VIR_TAG_MAX_SELECT_LIST_LEN; wIndex++)
    {
        if (s_tVirTagSelectList.aucFlag[wIndex])
        {
            logm_debug("%d ", wIndex);
        }
    }

    logm_debug("\r\nend print \r\n");
    return;
}


/*************************************************************************
*                        标签数组操作函数
**************************************************************************/
WORD32 vir_tag_add6cTag(BYTE ucTagId, T_USPVirTag6C *pt6cTag)
{
    T_USPVirTag6C *pt6cTagPtr = NULL;

    pt6cTagPtr = s_aptVirTag6cTags[ucTagId];
    if (pt6cTagPtr == NULL)
    {
        pt6cTagPtr = (T_USPVirTag6C *)malloc(sizeof(T_USPVirTag6C));
        if (pt6cTagPtr == NULL)
        {
            return VIR_TAG_ERR_MEM_FAIL;
        }

        s_aptVirTag6cTags[ucTagId] = pt6cTagPtr;
    }

    memcpy(pt6cTagPtr, pt6cTag, sizeof(T_USPVirTag6C));

    return 0;
}

WORD32 vir_tag_delete6cTag(BYTE ucTagId)
{
    if (NULL != s_aptVirTag6cTags[ucTagId])
    {
        free(s_aptVirTag6cTags[ucTagId]);
        s_aptVirTag6cTags[ucTagId] = NULL;
    }

    return 0;
}


void vir_tag_resetMac(void)
{
    vir_tag_emptySelectList();
    s_wVirTagActive6cTagId = VIR_TAG_INVALID_ID;
    s_dwVirTagMacState = VIR_TAG_MAC_NOT_START;

    logm_debug("reset mac \r\n");
    return;
}


/*********************************************************************

*                     匹配标签相关函数

**********************************************************************/

void vir_tag_moveMem(BYTE *pucSrc, WORD16 wBitoffset, BYTE *pucDest, BYTE ucByteLen)
{
    WORD32 dwIndex;
    BYTE ucBitOffset;
    
    pucSrc = pucSrc + (wBitoffset/8);
    ucBitOffset = wBitoffset%8;

    for (dwIndex = 0; dwIndex < ucByteLen; dwIndex++)
    {
        pucDest[dwIndex] = (pucSrc[dwIndex] << ucBitOffset) | (pucSrc[dwIndex + 1] >> (8 - ucBitOffset));
    }
    return;
}


WORD32 vir_tag_compareMemInBit(BYTE *pucSrc, BYTE *pucDest, WORD16 wMatchBitLen)
{
    WORD32 dwRet;
    BYTE ucByteLen;
    BYTE ucBitLen;
    
    #define  compare_byte(x, y, bitoffset)   ((x^y)>>(8-bitoffset))

    ucByteLen = wMatchBitLen / 8;
    ucBitLen = wMatchBitLen % 8;

    dwRet = memcmp(pucSrc, pucDest, ucByteLen);
    if (0 != dwRet)
    {
        return dwRet;
    }

    if (ucBitLen != 0)
    {
        dwRet = compare_byte(pucSrc[ucByteLen], pucDest[ucByteLen], ucBitLen);
    }

    return dwRet;
}

WORD32 vir_tag_matchMemory(BYTE *pucSrc, WORD16 wBitoffset,  BYTE *pucDest, WORD16 wMatchBitLen)
{
    BYTE aucBuf[256];
    WORD32 dwRet;
    
    #define  bit_to_byte(bitLengths) (bitLengths/8+(bitLengths%8?1:0))

    vir_tag_moveMem(pucSrc, wBitoffset, &aucBuf[0], bit_to_byte(wMatchBitLen));
    dwRet = vir_tag_compareMemInBit(&aucBuf[0], pucDest, wMatchBitLen);

    return dwRet;
}

BYTE *vir_tag_getMemBankAddr(T_USPVirTag6C *pt6cTag, BYTE ucMemBank)
{
    if (VIR_TAG_MEMBANK_RESERVE == ucMemBank)
    {
        return (BYTE *)&pt6cTag->wKillPassWordHigh;
    }

    if (VIR_TAG_MEMBANK_EPC == ucMemBank)
    {
        return (BYTE *)&pt6cTag->aucEpc[0];
    }

    if (VIR_TAG_MEMBANK_TID == ucMemBank)
    {
        return (BYTE *)&pt6cTag->aucTid[0];
    }

    if (VIR_TAG_MEMBANK_USER == ucMemBank)
    {
        return (BYTE *)&pt6cTag->aucUser[0];
    }

    return NULL;
}


WORD32 vir_tag_match6cTag(T_USPVirTag6C *pt6cTag, BYTE ucMemBank, WORD16 wAddr,
                          WORD16 wMaskBitLen, WORD16 *pwMaskData)
{
    WORD16 wNewAddr;
    BYTE *pucSrc = NULL;
    WORD32 dwRet;
    
    #define  translate_evb_addr(wAddr) ((((wAddr >> 8) & 0x7f) << 7) + (wAddr & 0x7f)) 

    /* reserve区不能参加匹配 */
    if ((VIR_TAG_MEMBANK_EPC != ucMemBank) && 
        (VIR_TAG_MEMBANK_TID != ucMemBank) && 
        (VIR_TAG_MEMBANK_USER != ucMemBank))
    {
        logm_debug("reserve bank can not match \r\n");
        return VIR_TAG_MATCH_FAIL;
    }

    /* 取得待匹配的地址 */
    pucSrc = vir_tag_getMemBankAddr(pt6cTag, ucMemBank);

    /* addr是EVB格式的 先转成普通格式*/
    wNewAddr = translate_evb_addr(wAddr);

    dwRet = vir_tag_matchMemory(pucSrc, wAddr, (BYTE *)pwMaskData, wMaskBitLen);

    return dwRet;
}


/****************************************************************************
*     标签匹配运算完成以后要对标签进行的操作
****************************************************************************/
void vir_tag_matchDeselectUnmatchSelect(BYTE ucTagId, WORD32 dwMatchResult)
{
    if (VIR_TAG_MATCH_SUCCESS == dwMatchResult)
    {
        vir_tag_removeTagFromSelectList(ucTagId);
    }
    else
    {
        vir_tag_insertTagToSelectList(ucTagId);
    }

    return;
}

void vir_tag_matchDeselectUnmatchNothing(BYTE ucTagId, WORD32 dwMatchResult)
{
    if (VIR_TAG_MATCH_SUCCESS == dwMatchResult)
    {
        vir_tag_removeTagFromSelectList(ucTagId);
    }

    return;
}

void vir_tag_matchNothingUnmatchSelect(BYTE ucTagId, WORD32 dwMatchResult)
{
    if (VIR_TAG_MATCH_SUCCESS != dwMatchResult)
    {
        vir_tag_insertTagToSelectList(ucTagId);
    }

    return;
}

void vir_tag_matchReverseUnmatchNothing(BYTE ucTagId, WORD32 dwMatchResult)
{
    return;
}

void vir_tag_matchSelectUnmatchDeselect(BYTE ucTagId, WORD32 dwMatchResult)
{
    if (VIR_TAG_MATCH_SUCCESS == dwMatchResult)
    {
        logm_debug("ucTagId: %d match, join select list \r\n", ucTagId);
        vir_tag_insertTagToSelectList(ucTagId);
    }
    else
    {
        vir_tag_removeTagFromSelectList(ucTagId);
    }

    return;
}

void vir_tag_matchSelectUnmatchNothing(BYTE ucTagId, WORD32 dwMatchResult)
{
    if (VIR_TAG_MATCH_SUCCESS == dwMatchResult)
    {
        vir_tag_insertTagToSelectList(ucTagId);
    }

    return;
}

void vir_tag_matchNothingUnmatchDeselect(BYTE ucTagId, WORD32 dwMatchResult)
{
    if (VIR_TAG_MATCH_SUCCESS != dwMatchResult)
    {
        vir_tag_removeTagFromSelectList(ucTagId);
    }

    return;
}

void vir_tag_matchNothingUnmatchReverse(BYTE ucTagId, WORD32 dwMatchResult)
{
    return;
}

void vir_tag_applyMatchResult(BYTE ucTagId, BYTE ucAction, WORD32 dwMatchResult)
{
    WORD32 dwTableSize = sizeof(s_atVirTagMatchActTable) / sizeof(T_VirTagMatchAction);


    if (ucAction < dwTableSize)
    {
        s_atVirTagMatchActTable[ucAction].pActFunc(ucTagId, dwMatchResult);
    }

    return;
}


WORD16 vir_tag_getMaxBankWordCount(BYTE ucMemBank, T_USPVirTag6C *pt6cTag)
{

    if (VIR_TAG_MEMBANK_RESERVE == ucMemBank)
    {
        return 4;
    }
    else if (VIR_TAG_MEMBANK_EPC == ucMemBank)
    {
        return pt6cTag->wEpcLen / 2;
    }
    else if (VIR_TAG_MEMBANK_TID == ucMemBank)
    {
        return pt6cTag->wTidLen / 2;
    }
    else
    {
        return pt6cTag->wUserLen / 2;
    }

}


WORD16 vir_tag_getBankState(BYTE ucMemBank, WORD16 wAddr, T_USPVirTag6C *pt6cTag)
{
    if (VIR_TAG_MEMBANK_EPC == ucMemBank)
    {
        return pt6cTag->wEpcState;
    }

    if (VIR_TAG_MEMBANK_TID == ucMemBank)
    {
        return pt6cTag->wTidState;
    }

    if (VIR_TAG_MEMBANK_USER == ucMemBank)
    {
        return pt6cTag->wUserState;
    }

    return 0;
}

WORD32 vir_tag_checkIfAddrInBlock(WORD32 wStartAddr, WORD32 wEndAddr, WORD32 dwBlkNum)
{
    if ((wStartAddr*2 >= (dwBlkNum * 8 + 8)) || (wEndAddr*2 <= (dwBlkNum * 8)))
    {
        return VIR_TAG_ADDR_OUT_BLOCK;
    }
    else
    {
        return VIR_TAG_ADDR_IN_BLOCK;
    }
}

WORD32 vir_tag_checkIfUserAccessable(WORD16 wAddr, WORD16 wCount, BYTE ucLockMask)
{
    WORD16 wEndAddr;
    WORD32 dwIndex;
    WORD32 dwIfWriteable;

    /* 最简单的方法就是分成8个块一块一块比较 */
    wEndAddr = wAddr + wCount;

    for (dwIndex = 0; dwIndex < 8; dwIndex++)
    {
        if (ucLockMask & 0x80)
        {
            dwIfWriteable = vir_tag_checkIfAddrInBlock(wAddr, wEndAddr, dwIndex);
            if (VIR_TAG_ADDR_IN_BLOCK == dwIfWriteable)
            {
                return VIR_TAG_BANK_UNACCESSABLE;
            }
        }

        ucLockMask = ucLockMask << 1;
    }

    return VIR_TAG_BANK_ACCESSABLE;
}

WORD32 vir_tag_checkIfBankAccessable(WORD16 wBankState)
{
    if ((wBankState & VIR_TAG_PWD_RW_BIT) &&
        ( (wBankState & VIR_TAG_PERMA_LOCK_BIT) || 
          (s_dwVirTagActive6cTagAccessFlag == FALSE)))
    {
        return VIR_TAG_BANK_UNACCESSABLE;
    }
    else
    {
        return VIR_TAG_BANK_ACCESSABLE;
    }
}

WORD32 vir_tag_checkIfReserveAccessable(WORD16 wAddr, WORD16 wCount, T_USPVirTag6C *pt6cTag)
{
    WORD32 dwIfAccessabel;

    if((wAddr+wCount)<=2)
    {
         dwIfAccessabel = vir_tag_checkIfBankAccessable(pt6cTag->wKillState);
    }
    else if(wAddr >= 2)
    {
        dwIfAccessabel = vir_tag_checkIfBankAccessable(pt6cTag->wAccessState);
    }
    else
    {
        dwIfAccessabel = ( vir_tag_checkIfBankAccessable(pt6cTag->wKillState)
                           || vir_tag_checkIfBankAccessable(pt6cTag->wAccessState));
    }

    return dwIfAccessabel;
}

WORD32 vir_tag_checkIfBankWriteable(BYTE ucMemBank, WORD16 wWrAddr, T_USPVirTag6C *pt6cTag)
{
    WORD16 wBankState;
    WORD32 dwIfWriteable;

    wBankState = vir_tag_getBankState(ucMemBank, wWrAddr, pt6cTag);
    dwIfWriteable = vir_tag_checkIfBankAccessable(wBankState);

    return dwIfWriteable;
}

WORD32 vir_tag_checkIfWriteable(BYTE ucMemBank, WORD16 wWrAddr, WORD16 wWrCount, T_USPVirTag6C *pt6cTag)
{
    WORD16 wBankState;
    WORD16 dwIfWriteable;

    if(ucMemBank == VIR_TAG_MEMBANK_RESERVE)
    {
        dwIfWriteable = vir_tag_checkIfReserveAccessable(wWrAddr, wWrCount, pt6cTag);
        
        return dwIfWriteable;
    }

    dwIfWriteable = vir_tag_checkIfBankWriteable(ucMemBank, wWrAddr, pt6cTag);
    if(dwIfWriteable == VIR_TAG_BANK_UNACCESSABLE)
    {
        return dwIfWriteable;
    }

    /* 如果要写的区域是user区还要判断user区的block lock标志 */
    if (ucMemBank == VIR_TAG_MEMBANK_USER)
    {
        dwIfWriteable = vir_tag_checkIfUserAccessable(wWrAddr, wWrCount, pt6cTag->ucUserPermaLockMask);
        return dwIfWriteable;
    }

    return VIR_TAG_BANK_ACCESSABLE;
}

WORD32 vir_tag_checkIfReadable(BYTE ucMemBank, WORD16 wReadAddr, WORD16 wReadCount,  T_USPVirTag6C *pt6cTag)
{
    WORD16 wBankState;
    WORD32 dwIfReadable;

    if(ucMemBank == VIR_TAG_MEMBANK_RESERVE)
    {
        dwIfReadable = vir_tag_checkIfReserveAccessable(wReadAddr, wReadCount, pt6cTag);
        return dwIfReadable;
    }

    /* 如果是user去还要检查是否存在读锁定的情况 */
    if((ucMemBank == VIR_TAG_MEMBANK_USER) && (s_dwVirTagActive6cTagAccessFlag == FALSE))
    {
        dwIfReadable = vir_tag_checkIfUserAccessable(wReadAddr, wReadCount, \
                                                   pt6cTag->ucUserReadLockMask);
        return dwIfReadable;
    }

    return VIR_TAG_BANK_ACCESSABLE;
}

WORD32 vir_tag_checkIfLockable(WORD16 wMask, WORD16 wAction, WORD16 wState)
{
    wMask = wMask & 0x03;
    wAction = wAction & 0x03;
    wState = wState & 0x03;

    if ((wMask & VIR_TAG_PERMA_LOCK_BIT)
        && (wState & VIR_TAG_PERMA_LOCK_BIT)
        && (wAction != wState))
    {
        return VIR_TAG_BANK_UNACCESSABLE;
    }
    else
    {
        return VIR_TAG_BANK_ACCESSABLE;
    }
}

WORD32 vir_tag_checkIfUserLockable(WORD16 wMask, WORD16 wAction, T_USPVirTag6C *pt6cTag)
{
    WORD16 wUserState;
    BYTE ucBlockLockMask;

    wUserState = pt6cTag->wUserState;
    ucBlockLockMask = pt6cTag->ucUserPermaLockMask;

    vir_tag_changeLockBit(wMask, wAction, &wUserState);

    if (((wUserState & 0x03) == 0x0001) && (ucBlockLockMask != 0))
    {
        return VIR_TAG_BANK_UNACCESSABLE;
    }
    else
    {
        return VIR_TAG_BANK_ACCESSABLE;
    }

}

WORD32 vir_tag_checkLockCondition(WORD16 wMask, WORD16 wAction, T_USPVirTag6C *pt6cTag)
{
    WORD32 dwRet;
    WORD32 dwErrCode = (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;

    if (s_dwVirTagActive6cTagAccessFlag == FALSE)
    {
        return dwErrCode;
    }

    /* 检查user区是否可锁定 */
    dwRet = vir_tag_checkIfLockable(wMask, wAction, pt6cTag->wUserState);
    if (VIR_TAG_BANK_ACCESSABLE != dwRet)
    {
        return dwErrCode;
    }

    dwRet = vir_tag_checkIfLockable((wMask >> 2), (wAction >> 2), pt6cTag->wTidState);
    if (VIR_TAG_BANK_ACCESSABLE != dwRet)
    {
        return dwErrCode;
    }

    dwRet = vir_tag_checkIfLockable((wMask >> 4), (wAction >> 4), pt6cTag->wEpcState);
    if (VIR_TAG_BANK_ACCESSABLE != dwRet)
    {
        return dwErrCode;
    }

    dwRet = vir_tag_checkIfLockable((wMask >> 6), (wAction >> 6), pt6cTag->wAccessState);
    if (VIR_TAG_BANK_ACCESSABLE != dwRet)
    {
        return dwErrCode;
    }

    dwRet = vir_tag_checkIfLockable((wMask >> 8), (wAction >> 8), pt6cTag->wKillState);
    if (VIR_TAG_BANK_ACCESSABLE != dwRet)
    {
        return dwErrCode;
    }

    /* 主要是检查user区是否有block lock的块 */
    dwRet = vir_tag_checkIfUserLockable(wMask, wAction, pt6cTag);
    if (VIR_TAG_BANK_ACCESSABLE != dwRet)
    {
        return dwErrCode;
    }

    return 0;
}



WORD32 vir_tag_check6cReadCondition(T_VirTagEffectiveRegs *ptRegs, T_USPVirTag6C *pt6cTag)
{
    WORD16 wMaxWordCount;
    WORD32 dwIfReadable;
    BYTE ucMemBank;

    ucMemBank = ptRegs->wREG_G2_Read_Membank & 0x3;

    /* 地址超出范围 */
    wMaxWordCount = vir_tag_getMaxBankWordCount(ucMemBank, pt6cTag);
    if ((ptRegs->wREG_G2_Read_Addr + ptRegs->wREG_G2_Read_WordCount) > wMaxWordCount)
    {
        logm_debug("read mem location not exist \r\n");
        return (VIR_TAG_SELF_ERR_TAG << 16) | (VIR_TAG_TAG_ERR_MEM_NOT_EXIST);
    }

    /* 判断该区域是否可读 */
    dwIfReadable = vir_tag_checkIfReadable(ucMemBank, ptRegs->wREG_G2_Read_Addr, \
                                           ptRegs->wREG_G2_Read_WordCount, pt6cTag);
    if (dwIfReadable == VIR_TAG_BANK_UNACCESSABLE)
    {
        logm_debug("read mem denied \r\n");
        return (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;
    }

    return 0;
}



WORD32 vir_tag_checkWriteCondition(T_WriteCmdPara *ptWritePara, T_USPVirTag6C *pt6cTag)
{
    WORD16 wMaxWordCount;
    WORD32 dwIfWriteable;

    /* 地址超出范围 */
    wMaxWordCount = vir_tag_getMaxBankWordCount(ptWritePara->ucMemBank, pt6cTag);
    if ((ptWritePara->wWriteAddr+ ptWritePara->wWriteCount) > wMaxWordCount)
    {
        logm_debug("write mem location not exist \r\n");
        return (VIR_TAG_SELF_ERR_TAG << 16) | (VIR_TAG_TAG_ERR_MEM_NOT_EXIST);
    }

    /* 判断该区域是否可写 */
    dwIfWriteable = vir_tag_checkIfWriteable(ptWritePara->ucMemBank, ptWritePara->wWriteAddr, 
                                             ptWritePara->wWriteCount, pt6cTag);
    if (dwIfWriteable == VIR_TAG_BANK_UNACCESSABLE)
    {
        logm_debug("write mem denied \r\n");
        return (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;
    }

    return 0;
}

WORD32 vir_tag_checkKillContiditon(WORD16 wPasswdHigh, WORD16 wPasswdLow, T_USPVirTag6C *pt6cTag)
{
    if ((wPasswdHigh == 0) && (wPasswdLow == 0))
    {
        return (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;
    }

    if ((wPasswdHigh != pt6cTag->wKillPassWordHigh)
        || (wPasswdLow != pt6cTag->wKillPassWordLow))
    {
        return (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;
    }

    return 0;
}



WORD32 vir_tag_checkBlockLockCondition(WORD16 wUserState)
{
    WORD32 dwErrCode = (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;

    if (s_dwVirTagActive6cTagAccessFlag == FALSE)
    {
        return dwErrCode;
    }

    if (wUserState == 0x01)
    {
        return dwErrCode;
    }

    return 0;
}


void vir_tag_setQueryFinishFrame(void)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = 2;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_EPC_CMD;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_INVENT_FINISH;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;
    vir_tag_giveMutex();
    return;
}

void vir_tag_setQuerySuccessFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 4;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_EPC_CMD;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    /*RSSI*/
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = VIR_TAG_DEFAULT_RSSI;
    logm_debug("inventoried one tag, set frame ready flag \r\n");
    *s_pdwUspVirTagFrameReadyFlag = TRUE;
    vir_tag_giveMutex();

    return;
}


/* 存在问题，帧长度是什么意思
   RSSI从哪里来 ?*/
void vir_tag_setQueryRespFrame(T_USPVirTag6C *pt6cTag)
{
    if (NULL == pt6cTag)
    {
        vir_tag_setQueryFinishFrame();
    }
    else
    {
        vir_tag_setQuerySuccessFrame(pt6cTag);
    }

    return ;
}


void vir_tag_setFailFrame(WORD16 wErrType, WORD16 wStage, WORD16 wSelfErr, WORD16 wTagErr, T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();
    if (NULL == pt6cTag)
    {
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] =  2;
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = wErrType;
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_FAIL;
    }
    else
    {
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 6;
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = wErrType;
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_FAIL;
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
        memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
               &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET));
        /* 错误命令类型 */
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = wStage;
        /* 自定义错误码 */
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 1] = wSelfErr;
        /* 标签返回的错误码 */
        s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 2] = wTagErr;
    }

    *s_pdwUspVirTagFrameReadyFlag = TRUE;
    vir_tag_giveMutex();
}

void vir_tag_setAccessFailFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_WRITE_CMD, VIR_TAG_STAGE_ERR_ACCESS, \
                         VIR_TAG_SELF_ERR_PASSWD, 0, pt6cTag);
    return;
}


void vir_tag_setReadFailFrame(WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_READ_CMD, VIR_TAG_STAGE_ERR_READ, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);
    return;
}



void vir_tag_setWriteFailFrame(WORD16 wWriteCmd, WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(wWriteCmd, VIR_TAG_STAGE_ERR_WRITE, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);

    return;
}


void vir_tag_setKillFailFrame(WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_KILL_CMD, VIR_TAG_STAGE_ERR_KILL, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);
    return;
}

void vir_tag_setBlockLockFailFrame(WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_BLKPERMLOCK1, VIR_TAG_STAGE_ERR_BLKPERMALOCK, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);
    return;
}

void vir_tag_setBlockLockQueryFailFrame(WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_BLKPERMLOCK, VIR_TAG_STAGE_ERR_PERMALOCK1, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);
    return;
}


void vir_tag_setLockFailFrame(WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_LOCK_CMD, VIR_TAG_STAGE_ERR_LOCK, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);
    return;
}

void vir_tag_setReadLockFailFrame(WORD32 dwErrCode, T_USPVirTag6C *pt6cTag)
{
    vir_tag_setFailFrame(VIR_TAG_ERR_BLKREADLOCK, VIR_TAG_STAGE_ERR_BLKREADLOCK, \
                         dwErrCode >> 16, dwErrCode, pt6cTag);
    return;
}


void vir_tag_setReadSuccessFrame(T_USPVirTag6C *pt6cTag, BYTE *pucSrc, WORD16 wReadLen)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 5 + wReadLen;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_READ_CMD;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));

    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = wReadLen;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 1], \
           pucSrc, wReadLen * 2);
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 1 + wReadLen] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;
   
    vir_tag_giveMutex();

    return;
}


void vir_tag_setWriteSuccessFrame(WORD16 wWriteCmd, T_USPVirTag6C *pt6cTag, WORD16 wWriteLen)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 5;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = wWriteCmd;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = wWriteLen;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 1] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;
    
    vir_tag_giveMutex();
    return;
}


void vir_tag_setKillSuccessFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 4;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_KILL_CMD;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;

    vir_tag_giveMutex();
    return;
}

void vir_tag_setBlockLockSuccessFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 4;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_BLKPERMLOCK1;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;

    vir_tag_giveMutex();
    return;
}

void vir_tag_setBlockLockQuerySuccessFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 6;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_BLKPERMLOCK;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = 1;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 1] = (pt6cTag->ucUserPermaLockMask) << 8;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 2] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;

    vir_tag_giveMutex();
    return;
}

void vir_tag_setLockSuccessFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 4;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_LOCK_CMD;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;
   
    vir_tag_giveMutex();

    return;
}

void vir_tag_setReadLockSuccessFrame(T_USPVirTag6C *pt6cTag)
{
    vir_tag_takeMutex();

    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_LEN] = ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2) + 4;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_CMD_TYPE] = VIR_TAG_ERR_BLKREADLOCK;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_FLAG] = VIR_TAG_FPGA_FRAME_FLAG_SUCCESSS;
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_PC] = (pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) << 10;
    memcpy(&s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC], \
           &pt6cTag->aucEpc[VIR_TAG_EPC_OFFSET], ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET)));
    s_pwUSPVirTagFrameBuf[VIR_TAG_FPGA_FRAME_GEN2_EPC + ((pt6cTag->wEpcLen-VIR_TAG_EPC_OFFSET) / 2)] = VIR_TAG_DEFAULT_RSSI;
    *s_pdwUspVirTagFrameReadyFlag = TRUE;
    
    vir_tag_giveMutex();

    return;
}

void vir_tag_printInventoriedTagId(WORD16 wTagId)
{
    if(VIR_TAG_INVALID_ID == wTagId)
    {
        logm_debug("inventoried no tag \r\n");
    }
    else
    {    
        logm_debug("inventoried tag: %d \r\n", wTagId);
    }

    return;
}

void vir_tag_setAccessFlagInQuery(T_USPVirTag6C *pt6cTag)
{   
    if ((NULL != pt6cTag)
        && (pt6cTag->wAccessPassWordHigh == 0)
        && (pt6cTag->wAccessPassWordLow == 0))
    {
        logm_debug("access password all zero\r\n");
        s_dwVirTagActive6cTagAccessFlag = TRUE;
    }
    else
    {
        logm_debug("access password not zero\r\n");
        s_dwVirTagActive6cTagAccessFlag = FALSE;
    }

    return;
}


WORD32 vir_tag_do6cAccess(T_VirTagEffectiveRegs *ptRegs, T_USPVirTag6C *pt6cTag)
{
    if ((NULL != pt6cTag)
        &&(ptRegs->wREG_G2_Access_Password_h == pt6cTag->wAccessPassWordHigh)
        &&(ptRegs->wREG_G2_Access_Password_L == pt6cTag->wAccessPassWordLow))
    {
        return VIR_TAG_ACCESS_SUCCESS;
    }
    else
    {
        return VIR_TAG_ACCESS_FAIL;
    }
}


void vir_tag_printTagState(T_USPVirTag6C *pt6cTag)
{
    if(NULL != pt6cTag)
    {
        logm_debug("(vir_tag)  s_dwVirTagActive6cTagAccessFlag is %d \r\n", s_dwVirTagActive6cTagAccessFlag);
        logm_debug("(vir_tag) access state is %04X, user state is %04X \r\n", pt6cTag->wAccessState, pt6cTag->wUserState);
        logm_debug("(vir_tag) user block lock is %02X, user read lock is %02X \r\n", pt6cTag->ucUserPermaLockMask, pt6cTag->ucUserReadLockMask);
    }
    else
    {
        logm_debug("(vir_tag) tag not exists! \r\n");
    }
    return;
}

void vir_tag_changeLockBit(WORD16 wLockMask, WORD16 wAction, WORD16 *pwLockState)
{
    WORD16 wPwdWriteBit;
    WORD16 wPermaLockBit;

    wPwdWriteBit = (wLockMask & VIR_TAG_PWD_WRITE_BIT) ? (wAction & VIR_TAG_PWD_WRITE_BIT) : (*pwLockState)&VIR_TAG_PWD_WRITE_BIT;
    wPermaLockBit = (wLockMask & VIR_TAG_PERMA_LOCK_BIT) ? (wAction & VIR_TAG_PERMA_LOCK_BIT) : (*pwLockState)&VIR_TAG_PERMA_LOCK_BIT;

    *pwLockState = wPwdWriteBit | wPermaLockBit;

    return;
}

void vir_tag_changeLockState(WORD16 wMask, WORD16 wAction, T_USPVirTag6C *pt6cTag)
{
    vir_tag_changeLockBit(wMask, wAction, &pt6cTag->wUserState);
    vir_tag_changeLockBit(wMask >> 2, wAction >> 2, &pt6cTag->wTidState);
    vir_tag_changeLockBit(wMask >> 4, wAction >> 4, &pt6cTag->wEpcState);
    vir_tag_changeLockBit(wMask >> 6, wAction >> 6, &pt6cTag->wAccessState);
    vir_tag_changeLockBit(wMask >> 8, wAction >> 8, &pt6cTag->wKillState);

    return;
}


void vir_tag_changeBlockLockMask(WORD16 wBlkLockMask, T_USPVirTag6C *pt6cTag)
{
    pt6cTag->ucUserPermaLockMask = wBlkLockMask >> 8;
    return;
}

void vir_tag_do6cBlockLock(WORD16 wBlkLockMask, T_USPVirTag6C *pt6cTag)
{
    WORD32 dwRet;

    logm_debug("(vir_tag) block lock user state is %04X, access flag is %d \r\n", pt6cTag->wUserState, s_dwVirTagActive6cTagAccessFlag);

    dwRet = vir_tag_checkBlockLockCondition(pt6cTag->wUserState);
    if (0 != dwRet)
    {
        logm_debug("(vir_tag) block lock fail \r\n");
        vir_tag_setBlockLockFailFrame(dwRet, pt6cTag);
    }
    else
    {
        logm_debug("(vir_tag) block lock success \r\n");
        vir_tag_changeBlockLockMask(wBlkLockMask, pt6cTag);
        vir_tag_setBlockLockSuccessFrame(pt6cTag);
    }

    return;
}

void vir_tag_do6cBlockQueryLock(T_USPVirTag6C *pt6cTag)
{
    WORD32 dwErrCode = (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;

    logm_debug("(vir_tag) do block query \r\n");
    
    if (s_dwVirTagActive6cTagAccessFlag == FALSE)
    {
        vir_tag_setBlockLockQueryFailFrame(dwErrCode, pt6cTag);
    }
    else
    {
        vir_tag_setBlockLockQuerySuccessFrame(pt6cTag);
    }

    return;
}


/****************************************************************************
*                6c标签操作函数
*****************************************************************************/
/*****************************************************************************
 函 数 名  : vir_tag_deal6cSelect
 功能描述  : 处理select命令，将选中的标签放进选中链表中
 输入参数  : T_VirTagEffectiveRegs *ptRegs
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_getSelectCmdPara(T_VirTagEffectiveRegs *ptRegs, T_VirTagSelectCmdPara *ptSelectPara)
{
    ptSelectPara->ucMemBank = (ptRegs->wREG_G2_Select_Para & 0xc0) >> 6;
    ptSelectPara->ucAction = (ptRegs->wREG_G2_Select_Para & 0x38) >> 3;
    ptSelectPara->wAddr = ptRegs->wREG_G2_Select_Addr;
    ptSelectPara->wMaskBitLen = ptRegs->wREG_G2_Select_Mask_BitLen;
    ptSelectPara->pwMaskDataAddr = (WORD16 *)(ptRegs + 1);

    logm_debug("select cmd para, ucMemBank: %02X, ucAction:%02X, wAddr:%04X, wMaskBitLen %04X, first MaskData %04X",
                   ptSelectPara->ucMemBank, ptSelectPara->ucAction,
                   ptSelectPara->wAddr, ptSelectPara->wMaskBitLen,
                   *ptSelectPara->pwMaskDataAddr);
    return;
}



void vir_tag_getWriteCmdPara(T_VirTagEffectiveRegs *ptRegs, T_WriteCmdPara *ptWritePara)
{
    if (ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_BLOCK_WRITE)
    {
        ptWritePara->wWriteCmd = VIR_TAG_ERR_BLKWRT_CMD;
        ptWritePara->ucMemBank = ptRegs->wREG_G2_Block_Write_Membank;
        ptWritePara->wWriteAddr = ptRegs->wREG_G2_Block_Write_Adress;
        ptWritePara->wWriteCount = ptRegs->wREG_G2_Block_Write_Length;        
    }
    else
    {
        ptWritePara->wWriteCmd = VIR_TAG_ERR_WRITE_CMD;
        ptWritePara->ucMemBank = ptRegs->wREG_G2_Write_Membank;
        ptWritePara->wWriteAddr = ptRegs->wREG_G2_Write_Addr;
        ptWritePara->wWriteCount = ptRegs->wREG_G2_Write_WordCount;
    }

    return;
}


void vir_tag_matchAndproc6cTags(T_VirTagSelectCmdPara *ptSelectPara)
{
    WORD16 wTagId;
    WORD32 dwMatchResult;
    
    for (wTagId = 0; wTagId < VIR_TAG_MAX_6C_TAG_NUM; wTagId++)
    {
        if (NULL == s_aptVirTag6cTags[wTagId])
        {
            continue;
        }
        
        dwMatchResult = vir_tag_match6cTag(s_aptVirTag6cTags[wTagId],
                                           ptSelectPara->ucMemBank,
                                           ptSelectPara->wAddr,
                                           ptSelectPara->wMaskBitLen,
                                           ptSelectPara->pwMaskDataAddr);

        vir_tag_applyMatchResult(wTagId, ptSelectPara->ucAction, dwMatchResult);
    }

    return;
}


WORD32 vir_tag_deal6cSelect(T_VirTagEffectiveRegs *ptRegs)
{
    T_VirTagSelectCmdPara tSelectPara;

    logm_debug("(vir_tag) deal 6c select \r\n");

    s_wVirTagActive6cTagId = VIR_TAG_INVALID_ID;
    s_dwVirTagActive6cTagAccessFlag = FALSE;

    vir_tag_getSelectCmdPara(ptRegs, &tSelectPara);
    vir_tag_matchAndproc6cTags(&tSelectPara);

    return VIR_TAG_CONTINUE_PROC;
}


/*****************************************************************************
 函 数 名  : vir_tag_deal6cQuery
 功能描述  : 处理query命令

 输入参数  : T_VirTagEffectiveRegs *ptRegs
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/


WORD32 vir_tag_deal6cQuery(T_VirTagEffectiveRegs *ptRegs)
{       
    T_USPVirTag6C *pt6cTag = NULL;
    
    logm_debug("vir_tag_deal6cQuery \r\n");

    s_wVirTagActive6cTagId = vir_tag_popTagFromSelectList();       
    vir_tag_printInventoriedTagId(s_wVirTagActive6cTagId);

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    vir_tag_setAccessFlagInQuery(pt6cTag);
      
    if(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION)
    {
        vir_tag_setQueryRespFrame(pt6cTag);
        return VIR_TAG_BREAK_PROC;
    }
    else
    {
        return VIR_TAG_CONTINUE_PROC;
    }
}

WORD32 vir_tag_deal6cAccess(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;
    WORD32 dwAccessResult;

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    dwAccessResult = vir_tag_do6cAccess(ptRegs, pt6cTag);

    if(VIR_TAG_ACCESS_SUCCESS == dwAccessResult)
    {
        s_dwVirTagActive6cTagAccessFlag = TRUE;
        return VIR_TAG_CONTINUE_PROC;
    }
    else
    {
        logm_debug("access fail \r\n");
        vir_tag_setAccessFailFrame(pt6cTag);
        /* 重新加入select队列 */
        vir_tag_insertTagToSelectList(s_wVirTagActive6cTagId);
        s_wVirTagActive6cTagId = VIR_TAG_INVALID_ID;
        s_dwVirTagActive6cTagAccessFlag = FALSE;
        return VIR_TAG_BREAK_PROC;
    }

}

WORD32 vir_tag_deal6cRead(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;
    WORD32 dwIfReadable;
    BYTE *pucBankAddr = NULL;

    logm_debug("in vir_tag_deal6cRead function \r\n");

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    if (NULL == pt6cTag)
    {
        vir_tag_setReadFailFrame(0, NULL);
        return VIR_TAG_BREAK_PROC;
    }

    vir_tag_printTagState(pt6cTag);

    dwIfReadable = vir_tag_check6cReadCondition(ptRegs, pt6cTag);
    if (0 != dwIfReadable)
    {
        logm_debug("(vir_tag) check read condition fail \r\n");
        vir_tag_setReadFailFrame(dwIfReadable, pt6cTag);
    }
    else
    {
        pucBankAddr = vir_tag_getMemBankAddr(pt6cTag, ptRegs->wREG_G2_Read_Membank & 0x03);
        pucBankAddr += ptRegs->wREG_G2_Read_Addr * 2;
        vir_tag_setReadSuccessFrame(pt6cTag, pucBankAddr, ptRegs->wREG_G2_Read_WordCount);
    }

    if(!(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION))
    {
        vir_tag_resetMac();
    }

    return VIR_TAG_BREAK_PROC;
}

WORD32 vir_tag_deal6cWrite(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;
    WORD32 dwRet;
    BYTE *pucBankStartAddr = NULL;
    BYTE *pucDestAddr = NULL;
    BYTE *pucSrcAddr = NULL;
    T_WriteCmdPara tWritePara;
    
    vir_tag_getWriteCmdPara(ptRegs, &tWritePara);

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    if (NULL == pt6cTag)
    {
        vir_tag_setWriteFailFrame(tWritePara.wWriteCmd, 0, NULL);
        return VIR_TAG_BREAK_PROC;
    }

    dwRet = vir_tag_checkWriteCondition(&tWritePara, pt6cTag);
    if (0 != dwRet)
    {
        vir_tag_setWriteFailFrame(tWritePara.wWriteCmd, dwRet, pt6cTag);
    }
    else
    {
        vir_tag_setWriteSuccessFrame(tWritePara.wWriteCmd, pt6cTag, tWritePara.wWriteCount);
        pucBankStartAddr = vir_tag_getMemBankAddr(pt6cTag, tWritePara.ucMemBank);
        pucDestAddr = pucBankStartAddr + tWritePara.wWriteAddr* 2;
        pucSrcAddr = (BYTE *)(ptRegs + 1) + (VIR_FPGA_SELECT_MASK_LEN * 2);
        memcpy(pucDestAddr, pucSrcAddr, tWritePara.wWriteCount * 2);
    }

    if(!(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION))
    {
        vir_tag_resetMac();
    }

    return VIR_TAG_BREAK_PROC;
}

WORD32 vir_tag_deal6cKill(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;
    WORD32 dwRet;

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    if (NULL == pt6cTag)
    {
        vir_tag_setKillFailFrame(0, NULL);
        return VIR_TAG_BREAK_PROC;
    }

    dwRet = vir_tag_checkKillContiditon(ptRegs->wREG_G2_Kill_Password_h, 
                                        ptRegs->wREG_G2_Kill_Password_L, 
                                        pt6cTag);
    if (0 != dwRet)
    {
        vir_tag_setKillFailFrame(dwRet, pt6cTag);
    }
    else
    {
        vir_tag_setKillSuccessFrame(pt6cTag);
        vir_tag_delete6cTag(s_wVirTagActive6cTagId);
        s_wVirTagActive6cTagId = VIR_TAG_INVALID_ID;
    }

    if(!(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION))
    {
        vir_tag_resetMac();
    }
    return VIR_TAG_BREAK_PROC;
}




WORD32 vir_tag_deal6cLock(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;
    WORD32 dwRet;

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    if (NULL == pt6cTag)
    {
        vir_tag_setLockFailFrame(0, NULL);
        return VIR_TAG_BREAK_PROC;
    }

    dwRet = vir_tag_checkLockCondition(ptRegs->wREG_G2_Loc_payload_mask,
                                       ptRegs->wREG_G2_Loc_payload_Action,
                                       pt6cTag);
    if (0 != dwRet)
    {
        vir_tag_setLockFailFrame(dwRet, pt6cTag);
    }
    else
    {
        vir_tag_changeLockState(ptRegs->wREG_G2_Loc_payload_mask,
                                ptRegs->wREG_G2_Loc_payload_Action,
                                pt6cTag);
        vir_tag_setLockSuccessFrame(pt6cTag);
    }

    if(!(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION))
    {
        vir_tag_resetMac();
    }
    return VIR_TAG_BREAK_PROC;
}


WORD32 vir_tag_deal6cBlockLock(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;    
    WORD16 wBlkLockMask;

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    if (NULL == pt6cTag)
    {
        vir_tag_setBlockLockFailFrame(0, NULL);
        return VIR_TAG_BREAK_PROC;
    }

    if (ptRegs->wREG_G2_Block_Lock_MemBank & 0x04)
    {
        wBlkLockMask = *((WORD16 *)(ptRegs + 1) + 32);
        vir_tag_do6cBlockLock(wBlkLockMask, pt6cTag);
    }
    else
    {
        vir_tag_do6cBlockQueryLock(pt6cTag);
    }

    if(!(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION))
    {
        vir_tag_resetMac();
    }

    return VIR_TAG_BREAK_PROC;
}


WORD32 vir_tag_deal6cReadLock(T_VirTagEffectiveRegs *ptRegs)
{
    T_USPVirTag6C *pt6cTag = NULL;    
    WORD16 wBlkLockMask;
    WORD32 dwErrCode = (VIR_TAG_SELF_ERR_TAG << 16) | VIR_TAG_TAG_ERR_ACCESS_NOT_PERMIT;

    pt6cTag = get_6c_tag_ptr(s_wVirTagActive6cTagId);
    if (NULL == pt6cTag)
    {
        vir_tag_setReadLockFailFrame(0, NULL);
        return VIR_TAG_BREAK_PROC;
    }

    if(s_dwVirTagActive6cTagAccessFlag == FALSE)
    {
        vir_tag_setReadLockFailFrame(dwErrCode, pt6cTag);
    }
    else
    {
        pt6cTag->ucUserReadLockMask = ptRegs->wREG_G2_Blockreadlock_mask;
        logm_debug("(vir_tag) read lock mask is %02X", pt6cTag->ucUserReadLockMask);
        vir_tag_setReadLockSuccessFrame(pt6cTag);
    }

    if(!(ptRegs->wREG_CPU_CMD_type & CMD_REG_EPC_LLRP_OPERATION))
    {
        vir_tag_resetMac();
    }
    return VIR_TAG_BREAK_PROC;
}


WORD32 vir_tag_deal6cQt(T_VirTagEffectiveRegs *ptRegs)
{
    return 0;
}

void vir_tag_deal6cLlrpCmd(T_VirTagEffectiveRegs *ptRegs)
{
    WORD32 dwIndex;
    WORD16 wCmdType;
    WORD32 dwTableSize;
    WORD32 dwRet;


    dwTableSize = sizeof(s_atVirTag6cCmdFuncTable) / sizeof(T_VirTag6cCmdFunc);
    wCmdType = ptRegs->wREG_CPU_CMD_type;
    for (dwIndex = 0; dwIndex < dwTableSize; dwIndex++)
    {
        if (wCmdType & s_atVirTag6cCmdFuncTable[dwIndex].wCmdMask)
        {
            dwRet = s_atVirTag6cCmdFuncTable[dwIndex].pf6cCmdFunc(ptRegs);
            if (dwRet != 0)
            {
                break;
            }
        }
    }

    logm_debug("(vir_tag) return from deal 6c llrp cmd \r\n");
    return;
}


/*****************************************************************************
 函 数 名  : vir_tag_findMsgFunc
 功能描述  : 根据消息id找到消息处理函数
 输入参数  : WORD16 wMsgId
 输出参数  : 无
 返 回 值  : void

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void *vir_tag_findMsgFunc(WORD16 wMsgId)
{
    WORD32 dwIndex;

    for (dwIndex = 0; dwIndex < (sizeof(s_atVirTagMsgProcTable) / sizeof(T_VirTagMsgProc)); dwIndex++)
    {
        if (wMsgId == s_atVirTagMsgProcTable[dwIndex].wMsgId)
        {
            return (void *)(s_atVirTagMsgProcTable[dwIndex].pMsgFunc);
        }
    }

    return NULL;
}

/*****************************************************************************
 函 数 名  : vir_tag_procMsg
 功能描述  : 处理接收到的函数
 输入参数  : T_Msg *ptRcvMsg
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
typedef void (*P_MSG_FUNC)(struct tagT_Msg *);

void vir_tag_procMsg(int *msg_id)
{
    P_MSG_FUNC pMsgFunc;

    pMsgFunc = (P_MSG_FUNC)vir_tag_findMsgFunc((WORD16)(*msg_id));
    if (NULL != pMsgFunc)
    {
        pMsgFunc((T_Msg *)msg_id);
    }

    return;
}

void vir_tag_procRcpMsg(T_Msg *ptRcvMsg)
{
    P_MSG_FUNC pMsgFunc;

    pMsgFunc = (P_MSG_FUNC)vir_tag_findMsgFunc(ptRcvMsg->wMsgID);
    if (NULL != pMsgFunc)
    {
        pMsgFunc(ptRcvMsg);
    }

    return;
}



void *vir_tag_mallocShm(WORD16 wKey, WORD32 dwSize)
{
    SWORD32 sdwShmId;

    sdwShmId = shmget((key_t)wKey, 0, 0666);
    if(-1 != sdwShmId)
    {
        return shmat(sdwShmId, (void *)0, SHM_RND);
    }
    else
    {
        sdwShmId = shmget((key_t)wKey, dwSize, 0666|IPC_CREAT);
        if(sdwShmId < 0)
        {
            return NULL;
        }
        else
        {
            return shmat(sdwShmId, (void *)0, SHM_RND);
        }
    }
}

void vir_tag_creatShareMem(void)
{
    /* 创建共享内存 */
    //USP_OSS_IPC_CREATE_MUTEX(&s_tUSPVirTagMutex, USP_VIR_TAG_MUTEX_KEY);
    s_pwUSPVirTagFrameBuf = (WORD16 *)vir_tag_mallocShm(USP_VIR_TAG_SHM_KEY, VIR_TAG_SHM_SIZE);
    s_pdwUspVirTagFrameReadyFlag = (WORD32 *)vir_tag_mallocShm(USP_VIR_TAG_SHM1_KEY, sizeof(WORD32));
    memset(s_pwUSPVirTagFrameBuf, 0, VIR_TAG_SHM_SIZE);
    memset(s_pdwUspVirTagFrameReadyFlag, 0, sizeof(WORD32));

    return;
}

/*****************************************************************************
*                              消息处理函数
******************************************************************************/
void vir_tag_procPowerOn(int *ptRcvMsg)
{
    WORD32 adwMsgBuf[128];
    WORD32 dwRet;
    T_Msg *ptMsg = NULL;

    /* 创建共享内存 */
    //USP_OSS_IPC_CREATE_MUTEX(&s_tUSPVirTagMutex, USP_VIR_TAG_MUTEX_KEY);
    s_pwUSPVirTagFrameBuf = (WORD16 *)vir_tag_mallocShm(USP_VIR_TAG_SHM_KEY, VIR_TAG_SHM_SIZE);
    s_pdwUspVirTagFrameReadyFlag = (WORD32 *)vir_tag_mallocShm(USP_VIR_TAG_SHM1_KEY, sizeof(WORD32));
    memset(s_pwUSPVirTagFrameBuf, 0, VIR_TAG_SHM_SIZE);
    memset(s_pdwUspVirTagFrameReadyFlag, 0, sizeof(WORD32));

    ptMsg = (T_Msg *)&adwMsgBuf[0];
    ptMsg->mtype = 1;
    ptMsg->wMsgID = EV_USP_SCP_PowerOnSuccess;
    ptMsg->wMsgLen = sizeof(T_USPOssScpPowerOnAck);
    ptMsg->wSenderTno = USP_VIR_TAG_TNO;
    ptMsg->wReceiverTno = USP_OSS_SCP_TNO;

    ((T_USPOssScpPowerOnAck *)(ptMsg + 1))->ucRound = ((T_USPOssScpPowerOnAck *)(ptRcvMsg + 1))->ucRound;
    dwRet = usp_oss_scp_sendTaskMsg(USP_OSS_SCP_TNO, ptMsg, USP_OSS_IPC_FOREVERWAIT);
    if(0 == dwRet)
    {
        logm_debug("(vir tag) poweron success \r\n");
    }
    else
    {
        logm_debug("(vir tag) power on fail \r\n");
    }
    return;
}

void vir_tag_procLinkOpend(int *ptRcvMsg)
{
    T_Msg tMsg;

    tMsg.mtype = 1;
    tMsg.wMsgID = EV_USP_VIR_TAG_StartWork;
    tMsg.wMsgLen = 0;

    //usp_oss_scp_sendTaskMsg(USP_UHF_TNO, &tMsg, USP_OSS_IPC_FOREVERWAIT);
    //zmq_send(rep_socket, &tMsg, sizeof(T_Msg), 0);
    //s_ucVirTagLinkType = ptRcvMsg->ucLinkType;
    //s_ucVirTagLinkIndex = ptRcvMsg->ucLinkIndex;

    return;
}

/*****************************************************************************
 函 数 名  : vir_tag_startCmd
 功能描述  : 标签操作函数，完成fpga的标签操作功能，将结果写在共享内存中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_startLlrpCmd(T_Msg *ptRcvMsg)
{
    T_VirTagEffectiveRegs *ptEffectiveRegs = NULL;

    if(s_dwVirTagMacState == VIR_TAG_MAC_NOT_START)
    {
        logm_debug("(vir_tag) mac not start !!!!\r\n");
        return;
    }

    ptEffectiveRegs = (T_VirTagEffectiveRegs *)(ptRcvMsg + 1);
    if (ptEffectiveRegs->wREG_PROTO_TYPE == UHF_PROTO_TYPE_EPC)
    {
        logm_debug("begin llrp cmd \r\n");
        vir_tag_deal6cLlrpCmd(ptEffectiveRegs);
        return;
    }
}

void vir_tag_startCmd(T_Msg* ptRcvMsg)
{
    logm_debug("start mac \r\n");
    s_dwVirTagMacState = VIR_TAG_MAC_START;
    vir_tag_startLlrpCmd(ptRcvMsg);
    return;
}


/*****************************************************************************
 函 数 名  : vir_tag_configTag
 功能描述  : 配置标签内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_config6cTag(int *ptMsg)
{
    WORD32 dwRet;
    T_USPVirTagConfig6cTag *ptConfig6cTag = NULL;
    BYTE aucSendMsgBuf[256];
    T_Msg *ptSendMsg = (T_Msg *) & (aucSendMsgBuf[0]);
    T_USPVirTagConfig6cTagResponse *ptResponse = NULL;

    ptConfig6cTag = (T_USPVirTagConfig6cTag *)(ptMsg + 1);
    dwRet = vir_tag_add6cTag(ptConfig6cTag->ucTagId, &ptConfig6cTag->t6cTag);

    logm_debug("(vir_tag) config 6c tag id: %d \r\n", ptConfig6cTag->ucTagId);
    logm_debug("(vir_tag) epc len is %d \r\n", ptConfig6cTag->t6cTag.wEpcLen);
    logm_debug("(vir_tag) epc 12 byte is %d \r\n", ptConfig6cTag->t6cTag.aucEpc[15]);

    #if 0
    ptSendMsg->mtype = 1;
    ptSendMsg->wMsgID = EV_USP_COMM_SendData;
    ptSendMsg->wMsgLen = sizeof(T_USPVirTagConfig6cTagResponse);
    ptSendMsg->ucLinkIndex = s_ucVirTagLinkIndex;
    ptSendMsg->ucLinkType = s_ucVirTagLinkType;
    #endif
    
    ptResponse = (T_USPVirTagConfig6cTagResponse *)(ptSendMsg);
    ptResponse->dwMsgId = VIR_TAG_CONFIG_6C_TAG_RESPONSE;
    ptResponse->dwResult = dwRet;

    //usp_oss_scp_sendTaskMsg(USP_COMM_TNO, ptSendMsg, USP_OSS_IPC_FOREVERWAIT);

    zmq_send(rep_socket, ptSendMsg, sizeof(T_USPVirTagConfig6cTagResponse), 0);
    
    return;
}

/*****************************************************************************
 函 数 名  : vir_tag_QueryTag
 功能描述  : 查询标签内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_Query6cTag(int *ptMsg)
{
    WORD32 dwRet;
    T_USPVirTagQuery6cTag *ptQuery6cTag = NULL;
    BYTE aucSendMsgBuf[256];
    T_Msg *ptSendMsg = (T_Msg *)&aucSendMsgBuf[0];
    T_USPVirTagQuery6cTagResponse *ptResponse = NULL;

    #if 0
    ptSendMsg->mtype = 1;
    ptSendMsg->wMsgID = EV_USP_COMM_SendData;
    ptSendMsg->wMsgLen = sizeof(T_USPVirTagQuery6cTagResponse);
    ptSendMsg->ucLinkIndex = s_ucVirTagLinkIndex;
    ptSendMsg->ucLinkType = s_ucVirTagLinkType;
    #endif

    ptQuery6cTag = (T_USPVirTagQuery6cTag *)(ptMsg + 1);
    ptResponse = (T_USPVirTagQuery6cTagResponse *)(ptSendMsg);
    ptResponse->dwMsgId = VIR_TAG_QUERY_6C_TAG_RESPONSE;

    if (s_aptVirTag6cTags[ptQuery6cTag->ucTagId] != NULL)
    {
        ptResponse->dwRet = 0;
        memcpy(&(ptResponse->t6cTag), s_aptVirTag6cTags[ptQuery6cTag->ucTagId], \
               sizeof(T_USPVirTag6C));
        logm_debug("(vir_tag) find tag id :%d \r\n", ptQuery6cTag->ucTagId);
    }
    else
    {
        ptResponse->dwRet = VIR_TAG_ERR_TAG_NOT_EXIST;
        logm_debug("(vir_tag) not find tag id :%d \r\n", ptQuery6cTag->ucTagId);
    }

    //usp_oss_scp_sendTaskMsg(USP_COMM_TNO, ptSendMsg, USP_OSS_IPC_FOREVERWAIT);
    zmq_send(rep_socket, ptSendMsg, (sizeof(T_USPVirTagQuery6cTagResponse)), 0);

    return;
}


void vir_tag_Delete6cTag(int *ptMsg)
{
    WORD32 dwRet;
    BYTE aucSendMsgBuf[256];
    T_Msg *ptSendMsg = (T_Msg *)&aucSendMsgBuf[0];
    T_USPVirTagDelete6cTag *ptDelete6cTag = NULL;
    T_USPVirTagDelete6cTagResponse *ptResponse = NULL;

    #if 0
    ptSendMsg->mtype = 1;
    ptSendMsg->wMsgID = EV_USP_COMM_SendData;
    ptSendMsg->wMsgLen = sizeof(T_USPVirTagDelete6cTagResponse);
    ptSendMsg->ucLinkIndex = s_ucVirTagLinkIndex;
    ptSendMsg->ucLinkType = s_ucVirTagLinkType;
    #endif

    ptDelete6cTag = (T_USPVirTagDelete6cTag *)(ptMsg + 1);
    ptResponse = (T_USPVirTagDelete6cTagResponse *)(ptSendMsg);
    ptResponse->dwResult = 0;
    ptResponse->dwMsgId = VIR_TAG_DELETE_6C_TAG_RESPONSE;

    if (s_aptVirTag6cTags[ptDelete6cTag->ucTagId] != NULL)
    {
        free(s_aptVirTag6cTags[ptDelete6cTag->ucTagId]);
        s_aptVirTag6cTags[ptDelete6cTag->ucTagId] = NULL;
    }

    vir_tag_removeTagFromSelectList(ptDelete6cTag->ucTagId);
    //usp_oss_scp_sendTaskMsg(USP_COMM_TNO, ptSendMsg, USP_OSS_IPC_FOREVERWAIT);
    zmq_send(rep_socket, ptSendMsg, (sizeof(T_USPVirTagDelete6cTagResponse)), 0);
    
    logm_debug("delete 6c tag succss, tag id: %d \r\n", ptDelete6cTag->ucTagId);
    return;    
}

/*****************************************************************************
 函 数 名  : vir_tag_Config6bTag
 功能描述  : 配置6b标签
 输入参数  : T_Msg *ptMsg
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_Config6bTag(T_Msg *ptMsg)
{
    ;
}


/*****************************************************************************
 函 数 名  : vir_tag_Query6bTag
 功能描述  : 查询6b标签
 输入参数  : T_Msg *ptMsg
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_Query6bTag(T_Msg *ptMsg)
{
    ;
}

/*****************************************************************************
 函 数 名  : vir_tag_remove6cTagAll
 功能描述  : 移除标签消息处理函数
 输入参数  : T_Msg *ptMsg
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_remove6cTagAll(int *ptMsg)
{
    BYTE aucMsgBuf[256];
    int *pSendMsg = (int *)&aucMsgBuf[0];
   
    memset(&s_aptVirTag6cTags[0], 0, sizeof(s_aptVirTag6cTags));    
    vir_tag_emptySelectList();

    #if 0
    pSendMsg->mtype = 1;
    pSendMsg->wMsgID = EV_USP_COMM_SendData;
    pSendMsg->wMsgLen = 4;
    pSendMsg->ucLinkIndex = s_ucVirTagLinkIndex;
    pSendMsg->ucLinkType = s_ucVirTagLinkType;
    #endif

    *(WORD32 *)(pSendMsg) = VIR_TAG_REMOVE_ALL_6C_TAG_RESPONSE;

    //usp_oss_scp_sendTaskMsg(USP_COMM_TNO, pSendMsg, USP_OSS_IPC_FOREVERWAIT);
    zmq_send(rep_socket, pSendMsg, 4, 0);
    logm_debug("remove all 6c tags \r\n");
    return;
}


/*****************************************************************************
 函 数 名  : vir_tag_remove6bTagAll
 功能描述  : 移除6b标签消息处理函数
 输入参数  : T_Msg *ptMsg
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_tag_remove6bTagAll(T_Msg *ptMsg)
{
    WORD32 dwIndex;

    for (dwIndex = 0; dwIndex < VIR_TAG_MAX_6C_TAG_NUM; dwIndex++)
    {
        if (s_aptVirTag6bTags[dwIndex] != NULL)
        {
            free(s_aptVirTag6bTags[dwIndex]);
            s_aptVirTag6bTags[dwIndex] = NULL;
        }
    }

    return;
}



void vir_tag_stopCmd(T_Msg *ptMsg)
{
    vir_tag_resetMac();
    return;
}

/*****************************************************************************
 函 数 名  : usp_vir_tagEntry
 功能描述  : 虚拟标签入口函数
 输入参数  : void
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void main(void)
{
    WORD32 dwRet;
    WORD32 s_dwRcvMsgBuf[VIR_TAG_RCV_MSG_BUF_SIZE / 4];
    T_Msg *ptRcvMsg = (T_Msg *)s_dwRcvMsgBuf;
    int ret;
    void *ctx = NULL;
    zmq_pollitem_t  items[3];
    int rc;
    int *msg_id = (int *)s_dwRcvMsgBuf;

    init_logm("vir_tag");

	ctx = zmq_init (1);
	if(NULL == ctx)
	{
		logm_debug("create context fail!\n");
		exit(-1);
	}
	
	rep_socket = zmq_socket(ctx, ZMQ_REP);
	if(NULL == rep_socket)
	{
		logm_debug("create rep_socket fail!\n");
		exit(-1);
	}

	ret = zmq_bind(rep_socket, "tcp://*:5110");
	if(ret < 0)
	{
		logm_debug("bind rep_socket  fail\n");
		exit(-1);
	}    

	pull_socket = zmq_socket(ctx, ZMQ_PULL);
	if(NULL == pull_socket)
	{
	    logm_debug("create pull_socket fail!\n");
		exit(-1);
	}

	ret = zmq_bind(pull_socket, "tcp://*:5111");
	if(ret < 0)
	{
		logm_debug("bind pull_socket  fail\n");
		exit(-1);
	}   

    logm_debug("(vir tag) process start \r\n");

    vir_tag_creatShareMem();

    items[0].socket = rep_socket;
    items[0].events = ZMQ_POLLIN;    
    items[1].socket = pull_socket;
    items[1].events = ZMQ_POLLIN;


    for (;;)
    {        
		rc = zmq_poll(&items[0], 2, -1);
		
        logm_debug("(vir_tag) begin receive msg \r\n");
        
        /*
              dwRet = usp_oss_scp_recvTaskMsg(USP_VIR_TAG_TNO, (void *)ptRcvMsg, VIR_TAG_RCV_MSG_BUF_SIZE, \
                                        USP_OSS_IPC_FOREVERWAIT);
             */

        if(items[0].revents & ZMQ_POLLIN)
        {
            dwRet = zmq_recv(rep_socket, (void *)msg_id, 4096, 0);
	        if (dwRet <= 0)
	        {
	            continue;
	        }	       
	        
            logm_debug("(vir tag) receive msg id is %04X \r\n", *msg_id);
            vir_tag_procMsg(msg_id);
	        
        }
        else if(items[1].revents & ZMQ_POLLIN)
        {
            dwRet = zmq_recv(pull_socket, (T_Msg *)ptRcvMsg, 4096, 0);
	        if (dwRet <= 0)
	        {
	            continue;
	        }

	        logm_debug("(vir tag) receive msg id is %04X \r\n", ptRcvMsg->wMsgID);
            vir_tag_procRcpMsg(ptRcvMsg);
        }
        else
        {
            continue;
        }        
    }

    return;

}

//#endif


