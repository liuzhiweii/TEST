#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include "usp_uhf_cfg.h"
#include "uhfFpgaRegDef.h"
#include "usp_uhf_gb.h"
#include "usp_uhf_err.h"
#include "uhf_trace.h"
#include "uhf_dbg.h"
//#include "uhf_time.h"
#include "FpgaCtl.h"
#include "uhf.h"
#include "uhf_gb.h"
#include "GB.h"

static  WORD32 uhf_GB_startAccessInvent(WORD32 dwAntIndex,
                                        T_USPUHFGBTagId *ptGBTagId,
                                        WORD16 *pwCommand);
extern  WORD32 SetGBAccessInventPara(T_USPUHFGBTagId *ptGBTagId,
                                          WORD16 *pwAccessInventCommand);
extern  WORD32 uhf_SetInventRfPara(WORD16 wAntIndex, WORD16 wProtoType, WORD16 wForDataRate,
                           WORD16 wRcvDataRate, WORD16 wModDepth,
                           WORD16 wModType, T_USPUHFInventRfPara *ptRfPara);


extern T_GBCtl g_tGBCtrl;
extern T_UhfCtrl g_tUhfCtrl;
static WORD16 g_wInventStatFlag = INVENTORY_HAS_FINISH;

/**********************************************************************
* 函数名称：void GBAccessRfCtl()
* 功能描述? 根据标志控制访问后是都关闭功放
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/6/13    V1.30.00       zdx         创建
************************************************************************/
void uhf_GBAccessStopRf()
{
    if (g_wInventStatFlag == INVENTORY_HAS_FINISH)
    {
        uhf_StopTx();
    }
    else
    {
        /*在LLRP性质的清点中间不需要关闭功放*/
        return ;
    }
}

/**********************************************************************
* 函数名称：WORD32  uhf_GB_startInventory (T_USPUHFGBInventory *ptGBTagInventory)
* 功能描述：GB清点流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/

WORD32 uhf_GB_startInventory(T_USPUHFGBInventory *ptGBTagInventory)
{
    WORD32 dwRetVal = USP_SUCCESS;
    T_USPUHFGBInventoryPara *ptGBInventoryPara = NULL;
    WORD16 wFpgaInventoryCommand = 0; /*向FPGA 下发的命令BIT位精度*/
    struct timeval GB_Invent_StartTime;
    struct timeval GB_Invent_EndTime;

    GetCurrUsTime(&GB_Invent_StartTime);
    
    
    /* 配置协议参数 sort query 命令参数*/
    ptGBInventoryPara = &(ptGBTagInventory->tGBInventoryPara);
    dwRetVal = SetGBInventoryPara(ptGBInventoryPara,
                                   ptGBTagInventory->ucAntennaID,
                                   &wFpgaInventoryCommand);
    //uhfDevPrint("GB Inventory  FpgaCommand wFpgaInventoryCommand = %x\r\n", 
    //                    wFpgaInventoryCommand);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    GetCurrUsTime(&GB_Invent_EndTime);
    //uhfDevPrint("uhf SetGBInventoryPara time %dms\r\n",
    //            CalMsTimeInterval(&GB_Invent_StartTime, &GB_Invent_EndTime));
    /* 配置清点命令 */
        uhfDevPrint("uhf wwwww uhf_gb_startInventory ptGBTagInventory->ucAntennaID = %d,UHF_PROTO_TYPE_GB = %d,g_tGBCtrl.RTDataRate = %d,g_tGBCtrl.TRDataRate = %d,g_tGBCtrl.wRTModDepth = %d,g_tGBCtrl.RTModulateType = %d\r\n",
                             ptGBTagInventory->ucAntennaID,
                             UHF_PROTO_TYPE_GB,
                             g_tGBCtrl.RTDataRate,
                             g_tGBCtrl.TRDataRate,
                             g_tGBCtrl.wRTModDepth,
                             g_tGBCtrl.RTModulateType);
    dwRetVal = uhf_SetInventRfPara(ptGBTagInventory->ucAntennaID,
                                   UHF_PROTO_TYPE_GB,
                                   g_tGBCtrl.RTDataRate,
                                   g_tGBCtrl.TRDataRate,
                                   g_tGBCtrl.wRTModDepth,
                                   g_tGBCtrl.RTModulateType,
                                   &ptGBTagInventory->tInventoryRfPara);
    
    GetCurrUsTime(&GB_Invent_EndTime);
    //uhfDevPrint("GB GB_SetInventRfPara time %dus\r\n",
     //           CalMsTimeInterval(&GB_Invent_StartTime, &GB_Invent_EndTime));

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    //启动fpga  lxc
    uhf_GBStartProcAndTimer(wFpgaInventoryCommand);

    //TraceToMacMsg(EV_GB_Inventory);
    GetCurrUsTime(&GB_Invent_EndTime);
    UHFAlertPrint("gb GB_SetInventEnd time %dms\r\n",
    CalMsTimeInterval(&GB_Invent_StartTime, &GB_Invent_EndTime));
    
    return dwRetVal;

}

/**********************************************************************
* 函数名称：WORD32  uhf_GB_startQuery ()
* 功能描述：GB继续清点触发
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc         创建
************************************************************************/
WORD32 uhf_GB_startQuery()
{
    uhf_GBStartLlrpProcAndTimer(CMD_REG_GB_QUERY);
    return USP_SUCCESS;
}


/**********************************************************************
* 函数名称：uhf_GB_startAccessInvent(T_USPUHFGBTagId *ptGBTagId,WORD16 *pwCommand)
* 功能描述：根据清点的情况看是否发送访问前的清点
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/13    V1.30.00       lxc         创建
************************************************************************/
//新国标必须发送访问命令
static WORD32 uhf_GB_startAccessInvent(WORD32 dwAntIndex,
                                        T_USPUHFGBTagId *ptGBTagId,
                                        WORD16 *pwCommand)
{
    WORD32 dwRetVal = USP_SUCCESS;
    //设置访问命令参数
    dwRetVal = SetGBAccessInventPara(ptGBTagId, pwCommand);

    if (dwRetVal != USP_SUCCESS)
    {
        UHFErrorPrint("UHF: Set GB access inventory failed \r\n");
        return dwRetVal;
    }
    //设置射频参数
    dwRetVal = uhf_SetInventRfPara(dwAntIndex,
                                   UHF_PROTO_TYPE_GB,
                                   g_tGBCtrl.RTDataRate,
                                   g_tGBCtrl.TRDataRate,
                                   g_tGBCtrl.wRTModDepth,
                                   g_tGBCtrl.RTModulateType,
                                   NULL);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    return dwRetVal;
}

/**********************************************************************
* 函数名称：uhf_GB_startAccess
* 功能描述?  GB标签访问命令的开始阶段
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/13    V1.30.00       lxc         创建
************************************************************************/
//// CMD_REG_GB_LLRP_OPERATION --- FPGA 没有这个寄存器
///FIX ME!!!
static WORD32 uhf_GB_startAccess(T_USPUHFGBTagId *ptGBTagId, WORD16 wAccessCommand)
{
    WORD32 dwRetVal = USP_SUCCESS;

    if (g_wInventStatFlag == INVENTORY_HAS_FINISH)
    {
        uhf_GBStartProcAndTimer(wAccessCommand);  //配置完FPGA 参数，启动fpga协议处理
    }
    else  //跟重庆版本有什么关系?  看以前的fpga寄存器
    {
        wAccessCommand |= CMD_REG_GB_LLRP_OPERATION; //bit 12 0x0005 重庆版本继续操作指示
        uhf_GBStartLlrpProcAndTimer(wAccessCommand);
    }

    return  dwRetVal;
}


/**********************************************************************
* 函数名称：WORD32  uhf_GB_startRead(T_USPUHFGBRead *ptGBRead)
* 功能描述：GB读标签流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_startRead(T_USPUHFGBRead *ptGBRead)
{

    WORD16 wMacGBReadCommand = 0;
    WORD32 dwRet = USP_SUCCESS;

    if (ptGBRead->tGBReadPara.wWordCount > GB_MAX_LENGTH) 
    {
        //LAPInsert(FILE_UHF_GB_START, USP_UHF_RCVED_PARA_ERROR, ptGBRead->tGBReadPara.wWordCount, 0);
        return USP_UHF_RCVED_PARA_ERROR;
    }
    
    // 每个存储区的最大地址可能不同
    //新国标中没有规定每个区的大小 
    // FIX ME !!!----lxc
   #if 0
    if (ptGBRead->tGBReadPara.wWordPointer > GB_READ_WRITE_MAX_LEN
        || ptGBRead->tGBReadPara.ucMB > GB_MAX_MEM_BLOCK_LEN) //新国标中有4个存储区0~3
    {
        uhfDevPrint("Para error  www ! wWordPointer = %d, ucMB = %d\r\n",
                            ptGBRead->tGBReadPara.wWordPointer,
                            ptGBRead->tGBReadPara.ucMB);
        return USP_UHF_RCVED_PARA_ERROR;
    }
#endif

    /*返回读长度结果时用FPGA返回的长度正确可去掉此行*/
    g_tGBCtrl.tGBRead.wReadWordsLen = ptGBRead->tGBReadPara.wWordCount;

    SetGBReadPara(&ptGBRead->tGBReadPara, &wMacGBReadCommand); //设置read命令寄存器

    /* 新国标访问前必须发送清点命令 */
    dwRet = uhf_GB_startAccessInvent(ptGBRead->dwAntIndex, &ptGBRead->tTagId,
                                      &wMacGBReadCommand);  //配置访问命令及射频参数，打开射频

    if (dwRet != USP_SUCCESS)
    {
        return  dwRet;
    }

    //发送访问命令其中包含了read 命令
    dwRet = uhf_GB_startAccess(&ptGBRead->tTagId, wMacGBReadCommand);
    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    //TraceToMacMsg(EV_GB_Read);

    uhfDevPrint("FPGA Read Command wwww %x\r\n", wMacGBReadCommand);
    return USP_SUCCESS;

}

/**********************************************************************
* 函数名称：WORD32 uhf_GB_startWrite(T_C1G2Write *ptRcpTagWrite)
* 功能描述：GB写标签流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_startWrite(T_USPUHFGBWrite *ptGBWrite)
{
    WORD16 wMacGBWriteCommand = 0;
    WORD32 dwRet = USP_SUCCESS;
#if 0
    if (ptGBWrite->tGBWritePara.wWriteWordLen > GB_MAX_LENGTH)
    {
        //LAPInsert(FILE_UHF_GB_START, USP_UHF_RCVED_PARA_ERROR,ptGBWrite->tGBWritePara.wWriteWordLen, 0);
        return USP_UHF_RCVED_PARA_ERROR;
    }

    if (ptGBWrite->tGBWritePara.wWordPointer > GB_READ_WRITE_MAX_LEN
        || ptGBWrite->tGBWritePara.ucMB > GB_MAX_MEM_BLOCK_LEN)
    {
        uhfDevPrint("Para error\r\n");
        return USP_UHF_RCVED_PARA_ERROR;
    }
#endif

    uhfDevPrint("UHF:write membank %d start word %d length %d\r\n",
                ptGBWrite->tGBWritePara.ucMB, ptGBWrite->tGBWritePara.wWordPointer,
                ptGBWrite->tGBWritePara.wWriteWordLen);
    SetGBWritePara(&ptGBWrite->tGBWritePara, &wMacGBWriteCommand); 

    dwRet = uhf_GB_startAccessInvent(ptGBWrite->dwAntIndex, &ptGBWrite->tTagId,
                                      &wMacGBWriteCommand);

    if (dwRet != USP_SUCCESS)
    {
        return  dwRet;
    }


    dwRet = uhf_GB_startAccess(&ptGBWrite->tTagId, wMacGBWriteCommand);

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    //TraceToMacMsg(EV_GB_Write);

    uhfDevPrint("FPGA Write Command %x\r\n", wMacGBWriteCommand);

    return USP_SUCCESS;

}

/**********************************************************************
* 函数名称：WORD32 uhf_GB_startLock(T_USPUHFGBLock *ptGBLock)
* 功能描述：GB lock标签流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_startLock(T_USPUHFGBLock *ptGBLock)
{
    WORD16 wMacGBLockCommand = 0;
    WORD32 dwRet = USP_SUCCESS;

    uhfDevPrint("UHF:lock membank = %d, AreaCfg = %d, AreaMode = %d, SecMode = %d\r\n",
                       ptGBLock->tGBLockPara.ucMB, ptGBLock->tGBLockPara.ucConfig,
                       ptGBLock->tGBLockPara.ucAeraMode, ptGBLock->tGBLockPara.ucSecureMode);
    dwRet = SetGBLockPara(&ptGBLock->tGBLockPara, &wMacGBLockCommand);

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    dwRet = uhf_GB_startAccessInvent(ptGBLock->dwAntIndex, &ptGBLock->tTagId,
                                      &wMacGBLockCommand);

    if (dwRet != USP_SUCCESS)
    {
        return  dwRet;
    }


    dwRet = uhf_GB_startAccess(&ptGBLock->tTagId, wMacGBLockCommand);

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    //TraceToMacMsg(EV_GB_Lock);

    uhfDevPrint("Fpga Lock  Command %x\r\n", wMacGBLockCommand);
    return dwRet;
}

/**********************************************************************
* 函数名称：WORD32 uhf_GB_startErase(T_USPUHFGBErase *ptGBErase)
* 功能描述：GB erase 标签流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
//// FIX ME !!!
WORD32 uhf_GB_startErase(T_USPUHFGBErase *ptGBErase)
{
    WORD16 wMacGBEraseCommand = 0;
    WORD32 dwRet = USP_SUCCESS;
#if 0
    if (ptGBErase->tGBErasePara.wEraseWordLen > GB_MAX_LENGTH)
    {
        //LAPInsert(FILE_UHF_GB_START, USP_UHF_RCVED_PARA_ERROR,ptGBErase->tGBErasePara.wEraseWordLen, 0);
        return USP_UHF_RCVED_PARA_ERROR;
    }

    if (ptGBErase->tGBErasePara.wWordPointer > GB_READ_WRITE_MAX_LEN
        || ptGBErase->tGBErasePara.ucMB > GB_MAX_MEM_BLOCK_LEN)
    {
        uhfDevPrint("Para error\r\n");
        return USP_UHF_RCVED_PARA_ERROR;
    }
#endif

    uhfDevPrint("UHF:Erase membank %d start word %d length %d\r\n",
                ptGBErase->tGBErasePara.ucMB, ptGBErase->tGBErasePara.wWordPointer,
                ptGBErase->tGBErasePara.wEraseWordLen);
    SetGBErasePara(&ptGBErase->tGBErasePara, &wMacGBEraseCommand);

    // 擦除不需要发送访问命令,直接设置射频参数

    dwRet = uhf_SetInventRfPara(ptGBErase->dwAntIndex,
                                   UHF_PROTO_TYPE_GB,
                                   g_tGBCtrl.RTDataRate,
                                   g_tGBCtrl.TRDataRate,
                                   g_tGBCtrl.wRTModDepth,
                                   g_tGBCtrl.RTModulateType,
                                   NULL);
    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    dwRet = uhf_GB_startAccess(&ptGBErase->tTagId, wMacGBEraseCommand);

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    //TraceToMacMsg(EV_GB_Erase);

    uhfDevPrint("FPGA GB Erase Command %x\r\n", wMacGBEraseCommand);

    return USP_SUCCESS;

}


/**********************************************************************
* 函数名称：WORD32 uhf_GB_startKill(T_USPUHFGBKill *ptGBKill)
* 功能描述：GB Kill标签流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_startKill(T_USPUHFGBKill *ptGBKill)
{
    WORD16 wMacGBKillCommand = 0;
    WORD32 dwRet = USP_SUCCESS;


    SetGBKillPara(&ptGBKill->tGBKillPara, &wMacGBKillCommand);

    dwRet = uhf_GB_startAccessInvent(ptGBKill->dwAntIndex, &ptGBKill->tTagId,
                                      &wMacGBKillCommand);

    if (dwRet != USP_SUCCESS)
    {
        return  dwRet;
    }


    dwRet = uhf_GB_startAccess(&ptGBKill->tTagId, wMacGBKillCommand);

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }

    //TraceToMacMsg(EV_GB_Kill);

    return (0);
}

#endif


