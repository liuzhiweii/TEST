#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include "usp_uhf_cfg.h"
#include "uhfFpgaRegDef.h"
#include "usp_uhf_iso6b.h"
#include "uhf_iso6b.h"
#include "usp_uhf_err.h"
#include "uhf.h"
#include "uhf_trace.h"
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf.h"
#include "ISO6B.h"
//#include "uhf_time.h"

T_ISO6BCtl           g_tISO6BCtrl;
extern T_UhfCtrl     g_tUhfCtrl;

/**********************************************************************
* 函数名称： uhf_ISO6B_InitCtrlStruct
* 功能描述：初始化控制结构体
* 输入参数：
* 输出参数：无
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2009\12\1              V03.00.00           zdx              创建
**************************************************************************/
void  uhf_ISO6B_InitCtrlStruct(void)
{
    memset(&g_tISO6BCtrl, 0x0, sizeof(g_tISO6BCtrl));
    g_tISO6BCtrl.wModeIndex = 0xffff;
    g_tISO6BCtrl.wDataReadStartAddr = 0;
    g_tISO6BCtrl.wModDepth = 100;
}

/**********************************************************************
* 函数名称： void uhf_ISO6BSetInventoryRes(T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes)
* 功能描述： ISO18000-6B协议清点处理主函数
* 输入参数： T_Inventory *ptISO6BInventoryPara:  清点下发函数
* 输出参数： T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes  清点结果返回参数
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\11\26            V04.00.00       zdx       创建
**************************************************************************/
WORD32 uhf_ISO6BSetInventoryRes(T_USPUHFISO6BInventoryRes *ptISO6BInventoryRes)
{
    WORD32 dwRet = USP_SUCCESS;

    if (NULL == ptISO6BInventoryRes)
    {
        return USP_UHF_POINTER_NULL_ERROR;
    }

    ptISO6BInventoryRes->wAntennaIndex = g_tUhfCtrl.wAntIndex;
    ptISO6BInventoryRes->wProtoType = UHF_PROTO_TYPE_ISO6B;
    ptISO6BInventoryRes->wChannelIndex = g_tUhfCtrl.wWorkChannel;
    ptISO6BInventoryRes->wResult = USP_SUCCESS;

    dwRet = uhf_ISO6BGetATag(&ptISO6BInventoryRes->wRssi, ptISO6BInventoryRes->tTagId.aucTagData);

    if (USP_SUCCESS == dwRet)
    {
        ptISO6BInventoryRes->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptISO6BInventoryRes->tTagId.wTagDataLen = ISO_180006B_UID_BYTE_LEN;
        g_tISO6BCtrl.wLastTagRssi = ptISO6BInventoryRes->wRssi;
        /*记录清点时标签的RSSI,当RDP调用读操作时返回*/
    }
    else
    {
        ptISO6BInventoryRes->wInventoryFinish = INVENTORY_HAS_FINISH;
        ptISO6BInventoryRes->tTagId.wTagDataLen = 0;
        g_tISO6BCtrl.wLastTagRssi = 0xffff;
    }

    return USP_SUCCESS;

}

/**********************************************************************
* 函数名称：void SetISOReadResDefault(T_ISO180006B_LockQueryResponse *ptISO6BLockQueryRes)
* 功能描述：填充ISO6B锁查询操作公共返回参数
* 输入参数：
* 输出参数：T_ISO180006B_LockQueryResponse *ptISO6BLockQueryRes 返回结果结构体
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010/11/30       V0.0.1         zdx           创建
************************************************************************/
static void SetISOResDefault(T_USPUHFISO6BResComm *ptISO6BResComm)
{
    ptISO6BResComm->wProtoType    =  UHF_PROTO_TYPE_ISO6B;
    ptISO6BResComm->wAntennaIndex =  g_tUhfCtrl.wAntIndex;
    ptISO6BResComm->wChannelIndex =  g_tUhfCtrl.wWorkChannel;
    ptISO6BResComm->wRssi         =  g_tISO6BCtrl.wLastTagRssi;
    uhfDevPrint("tag rssi: %x\r\n", ptISO6BResComm->wRssi);
}

/**********************************************************************
* 函数名称： void uhf_ISO6B_Inventory_Process(T_Inventory *ptISO6BInventoryPara,T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes)
* 功能描述： ISO18000-6B协议清点处理主函数
* 输入参数： T_Inventory *ptISO6BInventoryPara:  清点下发函数
* 输出参数： T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes  清点结果返回参数
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\11\26            V04.00.00       zdx       创建
**************************************************************************/
WORD32  usp_uhf_iso6b_inventory(T_USPUHFISO6BInventory *ptISO6BInventoryPara,
                                T_USPUHFISO6BInventoryRes *ptISO6BInventoryRes)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD32 dwFpgaRet = MAC_INVENTORY_PROCESS_FINISH;

    uhfDevPrint("ISO Inventory start\r\n");

    if (NULL == ptISO6BInventoryPara || NULL == ptISO6BInventoryRes)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    dwRet = uhf_ISO6B_Inventory_Start(ptISO6BInventoryPara);

    if (USP_SUCCESS != dwRet)
    {
        uhf_StopMacProc();
    }
    else
    {
        dwFpgaRet = uhf_ISO6B_Proc_Invnt_Resp();

        if (MAC_INVENTORY_PROCESS_FINISH != dwFpgaRet)
        {
            uhf_StopMacProc();
        }
    }

    uhf_stopRcpTimer();
    uhf_StopTx();

    dwRet = uhf_ISO6BSetInventoryRes(ptISO6BInventoryRes);

    if (USP_SUCCESS != dwRet)
    {
        uhfDevPrint("uhf_ISO6BSetInvent error %d\r\n", dwRet);
    }

    uhfDevPrint("ISO Inventory ends\r\n");
    return USP_SUCCESS;

}
/**********************************************************************
* 函数名称：
WORD32  uhf_ISO6B_GetTag_Process(T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes)
* 功能描述： 获取6B 标签，标签为上次清点到的未上报给RDP的标签
* 输入参数：
* 输出参数： T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes  清点结果返回参数
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\11\26            V04.00.00       zdx       创建
**************************************************************************/
WORD32  usp_uhf_iso6b_gettag(T_USPUHFISO6BInventoryRes *ptISO6BInventoryRes)
{
    WORD32 dwRet = USP_SUCCESS;

    if (NULL == ptISO6BInventoryRes)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    dwRet = uhf_ISO6BSetInventoryRes(ptISO6BInventoryRes);

    if (USP_SUCCESS != dwRet)
    {
        uhfDevPrint("uhf_ISO6BSetInvent error %d\r\n", dwRet);
    }

    return USP_SUCCESS;
}


/**********************************************************************
* 函数名称： void uhf_ISO6B_Read_Process(T_ISO6BRead *ptISO6BReadPara,T_ISO180006B_TagInventoryReponse *ptISO6BInventoryRes)
* 功能描述： ISO18000-6B协议清点处理主函数
* 输入参数： T_ISO6BRead *ptISO6BReadPara:  读下发参数
* 输出参数： T_ISO180006B_ReadResponse *ptISO6BReadRes  读结果返回
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\11\29              V04.00.00           zdx              创建
**************************************************************************/
WORD32 usp_uhf_iso6b_read(T_USPUHFISO6BRead *ptISO6BReadPara, T_USPUHFISO6BReadRes *ptISO6BReadRes)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD32 dwFpgaRet = USP_SUCCESS;;
    WORD16 wIndex = 0;

    uhfDevPrint("ISO Read start\r\n");

    if (NULL == ptISO6BReadPara || NULL == ptISO6BReadRes)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    uhfDevPrint("\r\nISO Read Start\r\n");
    uhfDevPrint("ISO Read Addr %d Length %d\r\n", ptISO6BReadPara->ucBytePtr, ptISO6BReadPara->ucByteCount);
    uhfDevPrint("ISO Read Retry Time %d \r\nUID ", ptISO6BReadPara->tISO6BReadctl.ucRetryTimes);

    for (wIndex = 0; wIndex < ISO_180006B_UID_BYTE_LEN; wIndex++)
    {
        uhfDevPrint("%02x ", ptISO6BReadPara->tTagId.aucTagData[wIndex]);
    }

    uhfDevPrint("\r\n");

    dwRet = uhf_ISO6B_Process_Start(ptISO6BReadPara->dwAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        ptISO6BReadRes->wResult = dwRet;
        ptISO6BReadRes->wResultLength = 0;
    }
    else
    {
        dwFpgaRet = uhf_ISO6B_ReadData(ptISO6BReadPara, ptISO6BReadRes);

        if (dwFpgaRet > USP_UHF_ERROR_NEED_RESET_FGPA)
        {
            ptISO6BReadRes->wResultLength = 0;
            uhf_StopMacProc();
        }

        ptISO6BReadRes->wResult = dwFpgaRet;
    }

    uhfDevPrint("ISO Read Result %d length %d\r\n",
                ptISO6BReadRes->wResult, ptISO6BReadRes->wResultLength);
    uhfDevPrint("ISO Read Data:");

    for (wIndex = 0; wIndex < ptISO6BReadRes->wResultLength; wIndex++)
    {
        uhfDevPrint("%02x ", ptISO6BReadRes->aucReadData[wIndex]);
    }

    uhfDevPrint("\r\n");

    uhf_stopRcpTimer();
    uhf_StopTx();
    SetISOResDefault((T_USPUHFISO6BResComm *)ptISO6BReadRes);
    uhfDevPrint("ISO Read ends\r\n");
    return USP_SUCCESS;
}

/**********************************************************************
* 函数名称： void uhf_ISO6B_LockQuery_Process(T_ISO6BQueryLock *ptISO6BLockQueryPara,T_ISO180006B_LockQueryResponse *ptISO6BLockQueryRes)

* 功能描述： ISO18000-6B协议锁查询处理主函数
* 输入参数： T_ISO6BRead *ptISO6BReadPara:  锁查询下发参数
* 输出参数： T_ISO180006B_ReadResponse *ptISO6BReadRes  锁查询结果返回
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\11\29              V04.00.00           zdx              创建
**************************************************************************/
WORD32  usp_uhf_iso6b_lockquery(T_USPUHFISO6BLockQuery *ptISO6BLockQueryPara, T_USPUHFISO6BLockQueryRes *ptISO6BLockQueryRes)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD32 dwFpgaRet = USP_SUCCESS;

    uhfDevPrint("ISO LockQuery start\r\n");

    if (NULL == ptISO6BLockQueryPara || NULL == ptISO6BLockQueryRes)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    uhfDevPrint("\r\nISO LockQuery Start\r\n");
    dwRet = uhf_ISO6B_Process_Start(ptISO6BLockQueryPara->dwAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        memset(ptISO6BLockQueryRes->aucLockQueryData, dwRet, ptISO6BLockQueryPara->ucByteCount);
    }
    else
    {
        dwFpgaRet = uhf_ISO6B_LockQueryData(ptISO6BLockQueryPara, ptISO6BLockQueryRes);

        if (dwFpgaRet > USP_UHF_ERROR_NEED_RESET_FGPA)
        {
            uhf_StopMacProc();
        }
    }

    ptISO6BLockQueryRes->wResult = USP_SUCCESS;
    ptISO6BLockQueryRes->wResultLength = ptISO6BLockQueryPara->ucByteCount;
    uhf_stopRcpTimer();
    uhf_StopTx();
    SetISOResDefault((T_USPUHFISO6BResComm *)ptISO6BLockQueryRes);
    uhfDevPrint("ISO LockQuery ends\r\n");
    return USP_SUCCESS;

}
/**********************************************************************
* 函数名称： void uhf_ISO6B_LockQuery_Process(T_ISO6BQueryLock *ptISO6BLockQueryPara,T_ISO180006B_LockQueryResponse *ptISO6BLockQueryRes)

* 功能描述： ISO18000-6B协议锁查询处理主函数
* 输入参数： T_ISO6BRead *ptISO6BReadPara:  锁查询下发参数
* 输出参数： T_ISO180006B_ReadResponse *ptISO6BReadRes  锁查询结果返回
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\11\29              V04.00.00           zdx              创建
**************************************************************************/
WORD32  usp_uhf_iso6b_write(T_USPUHFISO6BWrite *ptISO6BWritePara, T_USPUHFISO6BWriteRes *ptISO6BWriteRes)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD32 dwFpgaRet = USP_SUCCESS;


    uhfDevPrint("\r\nISO Write Start\r\n");

    if (NULL == ptISO6BWritePara || NULL == ptISO6BWriteRes)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    /*检查写阈值是否满求进行写的要求*/
    if (g_tUhfCtrl.atRfAntCfg[g_tUhfCtrl.wAntIndex].tISO6BWriteRssiCfg.ucTurnOnFilter == 1)
    {
        if ((g_tISO6BCtrl.wLastTagRssi) <
            g_tUhfCtrl.atRfAntCfg[g_tUhfCtrl.wAntIndex].tISO6BWriteRssiCfg.wRSSIThreshHold)
        {
            UHFAlertPrint("Throw iso6b write a tag!\r\n");
            ptISO6BWriteRes->wResult = USP_UHF_EPC_RSSI_NOT_ENOUGH;
            ptISO6BWriteRes->wResultLength = 0;
            SetISOResDefault((T_USPUHFISO6BResComm *)ptISO6BWriteRes);
            return  USP_UHF_EPC_RSSI_NOT_ENOUGH;
        }
    }

    dwRet = uhf_ISO6B_Process_Start(ptISO6BWritePara->dwAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        ptISO6BWriteRes->wResult = dwRet;
        ptISO6BWriteRes->wResultLength = 0;
    }
    else
    {
        dwFpgaRet = uhf_ISO6B_WriteData(ptISO6BWritePara, ptISO6BWriteRes);

        if (dwFpgaRet > USP_UHF_ERROR_NEED_RESET_FGPA)
        {
            uhf_StopMacProc();
        }

        ptISO6BWriteRes->wResult = dwFpgaRet;
    }

    /*成功时返回的长度不对*/
    if (ptISO6BWriteRes->wResult == USP_SUCCESS
        && (ptISO6BWritePara->ucByteCount != ptISO6BWriteRes->wResultLength))
    {
        //LAPInsert(FILE_UHF_ISO6B, USP_UHF_SUCCEEBUTERROR,ptISO6BWriteRes->wResultLength, 0);
    }

    uhfDevPrint("ISO Write Result %d Length %d\r\n",
                ptISO6BWriteRes->wResult, ptISO6BWriteRes->wResultLength);
    uhf_stopRcpTimer();
    uhf_StopTx();
    SetISOResDefault((T_USPUHFISO6BResComm *)ptISO6BWriteRes);
    uhfDevPrint("ISO Write ends\r\n");
    return USP_SUCCESS;

}
/**********************************************************************
* 函数名称： void uhf_ISO6B_Lock_Process(T_ISO6BLock *ptISO6BLockPara,T_ISO180006B_LockResponse *ptISO6BLockRes)
* 功能描述： ISO18000-6B协议锁处理主函数
* 输入参数： T_ISO6BLock *ptISO6BLockPara:  锁下发参数
* 输出参数： T_ISO180006B_LockResponse *ptISO6BLockRes 锁结果返回
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2010\12\1              V04.00.00           zdx              创建
**************************************************************************/
WORD32 usp_uhf_iso6b_lock(T_USPUHFISO6BLock *ptISO6BLockPara, T_USPUHFISO6BLockRes *ptISO6BLockRes)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD32 dwFpgaRet = USP_SUCCESS;

    uhfDevPrint("\r\nISO Lock Start\r\n");

    if (NULL == ptISO6BLockPara || NULL == ptISO6BLockRes)
    {
        return USP_UHF_RCVED_PARA_ERROR;
    }

    dwRet = uhf_ISO6B_Process_Start(ptISO6BLockPara->dwAntIndex);

    if (USP_SUCCESS != dwRet)
    {
        memset(ptISO6BLockRes->aucLockData, dwRet, ptISO6BLockPara->ucByteCount);
    }
    else
    {
        dwFpgaRet = uhf_ISO6B_LockData(ptISO6BLockPara, ptISO6BLockRes);

        if (dwFpgaRet > USP_UHF_ERROR_NEED_RESET_FGPA)
        {
            memset(ptISO6BLockRes->aucLockData, dwFpgaRet, ptISO6BLockPara->ucByteCount);
            uhf_StopMacProc();
        }
    }

    ptISO6BLockRes->wResult = USP_SUCCESS;
    ptISO6BLockRes->wResultLength = ptISO6BLockPara->ucByteCount;

    uhf_stopRcpTimer();
    uhf_StopTx();
    SetISOResDefault((T_USPUHFISO6BResComm *)ptISO6BLockRes);
    uhfDevPrint("ISO Lock ends\r\n");
    return USP_SUCCESS;
}
#endif

