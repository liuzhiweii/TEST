#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include "usp_uhf_cfg.h"
#include "uhfFpgaRegDef.h"
#include "usp_uhf_gb.h"
#include "usp_uhf_err.h"
#include "uhf_trace.h"
#include "uhf.h"
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf.h"
#include "uhf_gb.h"
#include "GB.h"

/* RTDataRate   TRDataRate  RealTRDataRate   wTc   wTpri,   dwK   M   T1min  T2min  T4min*/
/// FIX ME !!
#define   GB_TIMES_PARA_TABLE {\
        {40, 320,320, 0, 3,4,GB_QUERY_M_1,  0, 0,  0},\
        {40,  80, 80,25,12,1,GB_QUERY_M_1,118,38,150},\
        {80,  80, 80,12,12,1,GB_QUERY_M_1,118,38, 75},\
        {80, 160,160,12, 6,1,GB_QUERY_M_1, 56,19, 75},\
        {80, 320,320,13, 3,3,GB_QUERY_M_1, 32, 1, 75},\
        {160,160,160, 6, 6,3,GB_QUERY_M_1, 54,19, 38},\
        {160,320,320, 6, 3,3,GB_QUERY_M_1, 26,10, 38},\
        {80,640,640, 6, 3,7,GB_QUERY_M_1, 13, 5, 38},\
        {105,640,640,10, 3,7,GB_QUERY_M_1, 24, 0, 58}\
}
extern T_GBCtl   g_tGBCtrl; 
extern T_UhfCtrl  g_tUhfCtrl;

const T_USPUHFGBRFModeTableEntry g_tGBRFModeTable[] = GB_RFMODE_TABLE;
const T_GB_TimesPara g_GBTimesParaTable[] = GB_TIMES_PARA_TABLE;

WORD32 uhf_GB_getModeParas(WORD16 wModeIndex, WORD16 wAntIndex);
//WORD32 uhf_GB_getLockPayLoad(T_USPUHFGBLockPayloadList *ptLockPayLoad,
//                              WORD32 *pdwLockPayLoad);

/**********************************************************************
* 函数名称： WORD16 uhf_GB_getModeParas(WORD16 ModeIndex)
* 功能描述： 根据给定的ModeIndex的值确定参数,调制方式，反向编码方式，PIE值（目前不可配）
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：  一下从LLRP 标准的定义参数32位转为16 位再考虑
* 修改日期2014.2        版本号     修改人      lxc    修改内容
* -----------------------------------------------
*
***********************************************************************/
WORD32 uhf_GB_getModeParas(WORD16 wModeIndex, WORD16 wAntIndex)
{
    WORD32 dwIndex = 0;
    WORD16 wModulateIndex = 0;
    WORD16 ModulateTable[] = {3, 2, 1}; /* 用于模式转换 */
    static const WORD16 wGBModeTableLen = sizeof(g_tGBRFModeTable) / sizeof(T_USPUHFGBRFModeTableEntry);

    /* 参数检测，参数值的范围是0-20*/
    uhfDevPrint("GB modeindex == %d AntennaIndex %d wGBModeTableLen = %d\r\n",
                wModeIndex, wAntIndex, wGBModeTableLen);

    if (wModeIndex == 0)
    {
        uhfDevPrint("GB eForwardLinkModulation:%d,dwFawardValue:%d,dwBDRValue:%d\r\n", g_tGBRFModeTable[wModeIndex].eForwardLinkModulation,g_tGBRFModeTable[wModeIndex].dwFawardValue,
                    g_tGBRFModeTable[wModeIndex].dwBDRValue);

        if (wModeIndex == g_tGBCtrl.wModeIndex) /* 默认是0xffff */
        {
            uhfDevPrint(" wwwww  wModeIndex == g_tGBCtrl.wModeIndex\r\n");
            return USP_SUCCESS;
        }
        else
        {
            if (wModeIndex >= wGBModeTableLen)
            {
                wModeIndex = 0;
            }

            g_tGBCtrl.wModeIndex = wModeIndex;
        }

        
        wModulateIndex = (WORD16)g_tGBRFModeTable[wModeIndex].eForwardLinkModulation;
        g_tGBCtrl.RTModulateType = ModulateTable[wModulateIndex]; /* DSB */
        g_tGBCtrl.RTDataRate = (WORD16)(g_tGBRFModeTable[wModeIndex].dwFawardValue/1000);
        g_tGBCtrl.TRDataRate = (WORD16)(g_tGBRFModeTable[wModeIndex].dwBDRValue/1000);
        g_tGBCtrl.Query.ucM = (WORD16)g_tGBRFModeTable[wModeIndex].eMValue;    
	 uhfDevPrint("GB wModeIndex:%d,dwFawardValue%d dwBDRValue: %d \r\n",wModeIndex,
                    g_tGBRFModeTable[wModeIndex].dwFawardValue, g_tGBRFModeTable[wModeIndex].dwBDRValue);
        uhfDevPrint("GB the match rate is %d  and %d RTModulateType %d  DataEncodeType %d\r\n",wModeIndex,
                    g_tGBCtrl.RTDataRate, g_tGBCtrl.TRDataRate, g_tGBCtrl.RTModulateType,g_tGBCtrl.Query.ucM);
    }
    for (dwIndex = 0; dwIndex < sizeof(g_GBTimesParaTable) / sizeof(g_GBTimesParaTable[0]); dwIndex++)
    {
        if ((g_GBTimesParaTable[dwIndex].RTDataRate == g_tGBCtrl.RTDataRate)
            && (g_GBTimesParaTable[dwIndex].TRDataRate == g_tGBCtrl.TRDataRate))
        {
            break;
        }
    }

    if (dwIndex < sizeof(g_GBTimesParaTable) / sizeof(g_GBTimesParaTable[0]))
    {
        uhfDevPrint("UHF: wwwww user set rf link data rate is found \r\n");
    }
    else
    {
        /* 不能找到匹配的速率配置，使用默认的速率配置 */
        uhfDevPrint("UHF: user set rf link data rate is invid ,use default config \r\n");
        return USP_UHF_RCVED_PARA_ERROR;
    }

    uhfDevPrint("find the GB time para is %d\r\n", dwIndex);

    /* 根据链路速率配置决定时序参数 */
    g_tGBCtrl.RealTRDataRate = g_GBTimesParaTable[dwIndex].RealTRDataRate;

    g_tGBCtrl.wTc = g_GBTimesParaTable[dwIndex].wTc;

    /// 这个DR代表什么? 与GB的那个参数相似Divide  Ratio, 与反向链路速率因子相似
    //g_tGBCtrl.Query.DR = g_GBTimesParaTable[dwIndex].DR;
    
    g_tGBCtrl.Query.ucReLinkRateDivisor = g_GBTimesParaTable[dwIndex].dwK;  //lxc 反向速率因子
    g_tGBCtrl.wTpri = g_GBTimesParaTable[dwIndex].wTpri;
    g_tGBCtrl.T1min = g_GBTimesParaTable[dwIndex].T1min;
    g_tGBCtrl.T2min = g_GBTimesParaTable[dwIndex].T2min;
    g_tGBCtrl.T4min = g_GBTimesParaTable[dwIndex].T4min;

    return (0);

}

/**********************************************************************
* 函数名称：WORD32  SetGBInventoryPara (T_USPUHFGBInventoryPara *ptGBInventoryPara,
                                                                             WORD16 wAntInde, 
                                                                             WORD16 *pwFpgaInventoryCommand)
* 功能描述：GB清点流程处理。
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
#define SELECT_ACTION_LEN (6)
WORD32 SetGBInventoryPara(T_USPUHFGBInventoryPara *ptGBInventoryPara,
                           WORD16 wAntInde, WORD16 *pwFpgaInventoryCommand)
{
    // 干什么用的lxc ,可能需要根据fpga 从新定义
    //FIX ME!!
    //WORD16 actionTable[] = {4, 5, 6, 1, 0, 2}; /*用于将LLRP 标准的ACTION 对应为EPC标准的ACTION */
    WORD32 dwRet = USP_SUCCESS;
    T_USPUHFGBInventoryMaskList *pGBMaskList = NULL;
    WORD16 wAction = 0;

    /* 根据射频模式表配置时序参数 */ /* 这个时序值是不是有变换 lxc */
    /* wModeindex 是不是都是10000  lxc*/
    dwRet = uhf_GB_getModeParas(ptGBInventoryPara->wModeindex, wAntInde);

    if (USP_SUCCESS != dwRet)
    {
        return dwRet;
    }

    //配置反向速率，计算前导，关闭滤波 Timing T1,T2,T3 need to be fixed with Yong
    uhf_GB_setTimePara();  

    /* MAC协议层寄存器 */
    /* Maybe change */
    /* 0004h  10 表示中国标准#define  UHF_PROTO_TYPE_GB   0x2 -- lxc*/
    //SetProtoType(UHF_PROTO_TYPE_GB);

    pGBMaskList = &ptGBInventoryPara->tGBInventoryMaskList;

    if (pGBMaskList->tGBInventoryMask[0].wMaskLength
        > GB_MAX_MASK_WORD_NUM * 16)
    {
        uhfDevPrint("MaskWordLen Error!\r\n");
        return USP_UHF_RCVED_PARA_ERROR;
    }

    //设置掩码
    uhf_GB_setSelectMask(pGBMaskList->tGBInventoryMask[0].wMaskBitPointer,
                                      pGBMaskList->tGBInventoryMask[0].wMaskLength,
                    (WORD16 *)pGBMaskList->tGBInventoryMask[0].ucMaskData);

    wAction = pGBMaskList->tGBInventoryMask[0].ucSortAction;  
    
    uhfDevPrint("Action number ucSortAction = %d\r\n",wAction);
    if (wAction > SELECT_ACTION_LEN)
    {
        uhfDevPrint("Rcv invalied action number\r\n");
        wAction = 0;
    }

    /* 写FPGA的sort 命令参数寄存器 */
    /// Bit15~Bit12  保留	Bit11~Bit10   规则	Bit9~Bit6   目标	Bit5~Bit0  存储区lxc
    // 新国标有4中action，怎么与LLRP中的action对应?
    // FIX ME !! Action Para
    #if 0
    uhf_GBSetSelectPara(wAction/*Action (rule)*/, 
                                       0x0,/*target*/
                                       pGBMaskList->tGBInventoryMask[0].wMemBank/*membank*/);
    *pwFpgaInventoryCommand |= CMD_REG_GB_SORT;
    #endif

    /* 填写uhf_GB_Query掩码参数 g_tGBCtrl.Query.DR
       g_tGBCtrl.Query.M  在uhf_GB_getModeParas函数中配置*/

    //   保留 Bit15～Bit14
   // 条件    Bit13～Bit10
   // 会话   Bit9～Bit8
   // 目标     Bit7
   //   TRext  Bit6
  //  反向链路速率因子    Bit5～Bit2 
   // 编码选择Bit1～Bit0      lxc
   // 预估标签数国标去掉了

    /* 其他参数是否需要配置? 增加一个入参，作为query的其他参数 */
    uhf_GBSetMacQueryPara(g_tGBCtrl.Query.ucM/*M*/, g_tGBCtrl.Query.ucReLinkRateDivisor/*DR*/);

    *pwFpgaInventoryCommand |= (CMD_REG_GB_QUERY);
    return dwRet;

}


/**********************************************************************
* 函数名称：WORD32  SetGBReadPara(T_USPUHFGBReadPara *ptGBReadPara,
                                                                     WORD16 *pwGBReadCommand)
* 功能描述：GB设置读取参数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/24      V0.0.1         lxc         创建
************************************************************************/
void SetGBReadPara(T_USPUHFGBReadPara *ptGBReadPara,
                    WORD16 *pwGBReadCommand)
{

    /* 读流程，首先发送随机数获取命令 (fpga 发送)
                               发送access  命令，先发0-15bit，再发16-31bit  (高地位同时写入)
                               发送读命令
    */
    
    /* 程序发送获取随机数的命令，还是fpga 发送?  fpga 发送
        口令是口令和16位随机数异或的结果，谁来做异或的操作fpga做
        程序是否需要下发两次access命令，fpga做
        是否需要配置口令类别 ?   同时写入两次的口令类别
        lxc
    */

    
    BYTE       ucAccessType = ACCESS_READ;  //口令类别

    /* 获取read 口令的访问命令 */
    if (ptGBReadPara->dwAccessPassword != 0)
    {
        uhf_GBSetMacAccessPara(ptGBReadPara->dwAccessPassword, ptGBReadPara->ucMB,ucAccessType);
        *pwGBReadCommand |= CMD_REG_GB_ACCESS;
    }

    /* 填写GB_Read命令参数 lxc*/
    uhf_GBSetMacReadPara(ptGBReadPara->ucMB, ptGBReadPara->wWordPointer,
                          ptGBReadPara->wWordCount);
    *pwGBReadCommand |= CMD_REG_GB_READ;
}

/**********************************************************************
* 函数名称：WORD32  SetGBReadPara(T_USPUHFGBWritePara *ptGBReadCommand,
                                                                      WORD16 *pwFpgaGBReadCommand)
* 功能描述：GB设置读取参数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/24      V0.0.1         lxc         创建
************************************************************************/

void SetGBWritePara(T_USPUHFGBWritePara *ptGBWritePara,
                     WORD16 *pwGBWriteCommand)
{
    g_tGBCtrl.tGBWrite.wWriteWordsLen = ptGBWritePara->wWriteWordLen;

    BYTE ucAccessType = ACCESS_WRITE;

    if (ptGBWritePara->dwAccessPassword != 0)
    {
        uhf_GBSetMacAccessPara(ptGBWritePara->dwAccessPassword, ptGBWritePara->ucMB, ucAccessType);
        *pwGBWriteCommand |= CMD_REG_GB_ACCESS;
    }

    uhf_GBSetMacWritePara(ptGBWritePara->ucMB, ptGBWritePara->wWordPointer,
                               ptGBWritePara->wWriteWordLen, ptGBWritePara->aucData);
    *pwGBWriteCommand |= CMD_REG_GB_WRITE;
}

/**********************************************************************
* 函数名称：WORD32 SetGBLockPara(T_USPUHFGBLockPara *ptGBLockPara,
                                                                   WORD16 *pwFpgaGBLockCommand)
* 功能描述：GB设置锁参数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/24      V0.0.1         lxc         创建
************************************************************************/

WORD32 SetGBLockPara(T_USPUHFGBLockPara *ptGBLockPara,
                      WORD16 *pwFpgaGBLockCommand)
{
    WORD32 dwLockPayLoad = 0;
    WORD32 dwRet = USP_SUCCESS;
    BYTE       ucAccessType = ACCESS_LOCK;

    if (ptGBLockPara->dwAccessPassword != 0)
    {
        uhf_GBSetMacAccessPara(ptGBLockPara->dwAccessPassword, (BYTE)ptGBLockPara->ucMB, ucAccessType);
        *pwFpgaGBLockCommand |= CMD_REG_GB_ACCESS;
    }
#if 0
    /* 填写GB_Lock命令参数 */
    dwRet = uhf_epc_getLockPayLoad(&ptEPCLockPara->tEpcLockPayLoad, &dwLockPayLoad);

    if (dwRet != USP_SUCCESS)
    {
        return dwRet;
    }
#endif

    uhf_GBSetMacLockPara(ptGBLockPara->ucMB, ptGBLockPara->ucConfig, 
                                      ptGBLockPara->ucAeraMode,ptGBLockPara->ucSecureMode);
    *pwFpgaGBLockCommand |= (CMD_REG_GB_LOCK);

    return dwRet;
}

/**********************************************************************
* 函数名称： void SetGBErasePara(T_USPUHFGBErasePara *ptGBErasePara,
                                                              WORD16 *pwGBEraseCommand)
* 功能描述： 擦除参数设置
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期     2014.2      lxc   
* -----------------------------------------------
*
***********************************************************************/
void SetGBErasePara(T_USPUHFGBErasePara *ptGBErasePara,
                     WORD16 *pwGBEraseCommand)
{
    g_tGBCtrl.tGBErase.wEraseWordsLen = ptGBErasePara->wEraseWordLen;
    // 擦除不需要访问命令
    //BYTE ucAccessType = ACCESS_WRITE;

    //if (ptGBErasePara->dwAccessPassword != 0)
    //{
    //    uhf_EpcSetMacAccessPara(ptGBErasePara->dwAccessPassword, ptGBErasePara->ucMB, ucAccessType);
    //    *pwGBEraseCommand |= CMD_REG_EPC_ACCESS;
    //}

    uhf_GBSetMacErasePara(ptGBErasePara->ucMB, ptGBErasePara->wWordPointer,
                               ptGBErasePara->wEraseWordLen);
    *pwGBEraseCommand |= CMD_REG_GB_WRITE;
}

/**********************************************************************
* 函数名称：void SetGBKillPara(T_USPUHFGBKillPara *ptGBKillPara, 
                                                         WORD16 *pwMacGBKillCommand)
* 功能描述：GB设置杀死参数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/24      V0.0.1         lxc         创建
************************************************************************/
/* 未完成 */
void SetGBKillPara(T_USPUHFGBKillPara *ptGBKillPara, WORD16 *pwMacGBKillCommand)
{
    BYTE ucAccessType = ACCESS_KILL;
    /* 填写访问命令参数 */
    if (ptGBKillPara->dwKillPassword!= 0)
    {
        uhf_GBSetMacAccessPara(ptGBKillPara->dwKillPassword,0,ucAccessType);
        *pwMacGBKillCommand |= CMD_REG_GB_ACCESS;
    }
    /* 填写GB_Lock命令参数 */
    uhf_GBSetMacKillPara(ptGBKillPara->dwKillPassword);
    *pwMacGBKillCommand |= (CMD_REG_GB_KILL);
}

/**********************************************************************
* 函数名称：WORD32 SetGBAccessInventPara(T_USPUHFGBTagId *ptGBTagId,WORD16 *pwAccessInventCommand)
* 功能描述：GB访问开始参数设置
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/13    V1.30.00         lxc         创建
************************************************************************/
#define MEMBANKGB         (1)
#define GBSTARTBITADDR  (32)
#define GBBITLEN             (96)
WORD32 SetGBAccessInventPara(T_USPUHFGBTagId *ptGBTagId, WORD16 *pwAccessInventCommand)
{
    WORD16 actionTable[] = {4, 5, 6, 1, 0, 2}; /*用于将LLRP 标准的ACTION 对应为EPC标准的ACTION */

    uhf_GB_setTimePara();

    /* MAC协议层寄存器 */
    //SetProtoType(UHF_PROTO_TYPE_GB);  //调试阶段，对上层都是EPC保持不变，对FPGA都是新国标

    // 掩码寄存器有什么用?    uhf_epc_setSelectMask(EPCSTARTBITADDR, ptEpcTagId->wTagWordLen * 16, (WORD16 *)ptEpcTagId->aucTagData);

    //使用哪一个存储区的信息进行匹配需要确认
    //新国标中的rule 与actionTable 类似，具体怎么对应还有确认
    //去掉之前的截断/非截断 
    uhf_GBSetSelectPara(0x0/*wRule*/, 0x0/*target*/,MEMBANKGB/*membank*/);

    *pwAccessInventCommand |= CMD_REG_GB_SORT;

    /* 填写GB_Query掩码参数 g_tGBCtrl.Query.DR
     g_tGBCtrl.Query.M  在uhf_GB_getModeParas函数中配置*/
    uhf_GBSetMacQueryPara(g_tGBCtrl.Query.ucM/*M*/,
                                            g_tGBCtrl.Query.ucReLinkRateDivisor/*DR*/);
    *pwAccessInventCommand |= CMD_REG_GB_QUERY;

    return USP_SUCCESS;
}
#endif


