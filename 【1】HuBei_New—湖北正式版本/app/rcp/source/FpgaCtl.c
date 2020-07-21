/*********************************************************************
* 版权所有 (C)2005, 深圳市中兴通讯股份有限公司。
*
* 文件名称： FpgaApi.c
* 文件标识：
* 内容摘要： 实现FPGA驱动软件接口封装
* 其它说明：
* 当前版本：
* 作    者： ft
* 完成日期： 2006-09-29
*
* 修改记录1：
* 修改记录2：
* 修改记录3：
**********************************************************************/

/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include "uhf_trace.h"
#include "uhf_epc.h"
#include "uhf_iso6b.h"
#include "uhf_gb.h"
#include "uhfFpgaRegDef.h"
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf.h"
#include "EPC.h"
#include "ISO6B.h"
#include "GB.h"
//#include "uhf_time.h"
#define FPGA_SWTICH   0

/***********************************************************
 *                     常量定义                            *
***********************************************************/



#define FPGA_CMD_WRITE_REG_BYTE_LEN (6)
#define FPGA_CMD_READ_REG_BYTE_LEN  (6)

/* FPGA cpu interface bus bits width */
#define FPGA_DATA_BUS_WIDTH         (16)

/* use mmap mode to access fpga register */
#define FPGA_MMAP_ACCESS_REG

/***********************************************************
*                 文件内部使用的宏                        *
***********************************************************/

#define RcpFpgaPrint(...) usp_oss_printf(USP_UHF_TNO,USP_OSS_PRINTF_LEVEL_DEBUG,__VA_ARGS__)

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/


/***********************************************************
 *                     全局变量                            *
***********************************************************/
extern  T_EpcCtl g_tEpcCtrl;
extern  T_GBCtl g_tGBCtrl;
/* end Add by gaoyu for DATTControl, 2007年8月17日 9:50:29 */
/***********************************************************
 *                     本地变量                            *
***********************************************************/
/* FPGA数据缓存 */
WORD16 g_awFpgaReadBuf[FPGA_BUF_BYTE_SIZE / 2];

/* 失锁应该作一种就够了 */

/*
    R Counter Latch:
    14-BIT REFERENCE COUNTER : CONTROL BITS
*/

/***********************************************************
 *                     全局函数                            *
***********************************************************/



/***********************************************************
 *                     局部函数                            *
***********************************************************/
static void StartFpgaProc(WORD16 wCmdType);
static WORD32 FpgaTestNCnt(WORD32 dwTestCnt);
static void StartFpgallrpProc(WORD16 dwCmdType);
static WORD32 FpgaTest(void);
static void StartFpgaProcessIsoCmd(void);


/**********************************************************************
* 函数名称：uhf_mac_Init
* 功能描述：加载fpga设备，同时通过检测测试寄存器
                                来判断当前是否正常，不正常则一直循环
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2012/3/16       RUP      zdx          创建
************************************************************************/
WORD32 uhf_mac_Init(void)
{
    WORD32 dwRet = USP_SUCCESS;
    WORD32 dwFpgaTestErrorCount;
#if FPGA_SWTICH
    dwRet = usp_drv_fpga_init();
#endif 
    if (USP_SUCCESS != dwRet)
    {
        printf("UHF:usp_drv_fpga_init is failed,dwRet = %d\r\n", dwRet);
        return dwRet;
    }

    /* 查询FPGA逻辑版本 */
    printf("UHF: FpgaVersion = 0x%04x \r\n", FpgaRegRead(REG_FPGA_VERSION));

    dwFpgaTestErrorCount = FpgaTestNCnt(100);

    if (dwFpgaTestErrorCount != 0)
    {
        //lapneed
        LAPInsert(FILE_FPGACTL, USP_UHF_FPGA_TEST_ABNORAML, dwFpgaTestErrorCount, 0);

        for (;;)
        {
            printf("UHF: dwFpgaBusTestErrorCount = %10u \r\n", dwFpgaTestErrorCount);
            sleep(1);
        }
    }

    return USP_SUCCESS;
}
/**********************************************************************
* 函数名称： WORD32 uhf_readFpgaFrame(WORD16 *pwReadLen)
* 功能描述： 读取fpga fifo中的数据 放到全局缓冲区中
* 输入参数： 无
* 输出参数： WORD16 *pwReadLen；
* 返 回 值：     读取成功返回0 错误返回错误码
* 其它说明：  无
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*2010\12\1     V04.00.00      zdx      创建
***********************************************************************/
#define UHF_FPGA_NEED_RESET_TIME (100)
WORD32 uhf_readFpgaFrame(WORD16 *pwReadLen)
{
    WORD32 dwCount = 0;
    int iProcErrNo = 0;
    WORD32 dwRetVal = USP_SUCCESS;
    WORD16 wIndex = 0;
    static WORD32 dwFpgaReadErrorTime = 0;

    if (NULL == pwReadLen)
    {
        uhfDevPrint("pwReadLen is NULL\r\n");
        LAPInsert(FILE_FPGACTL, USP_UHF_RCVED_PARA_ERROR, 0 , 0);
        return USP_UHF_FPGA_NO_FRAME;
    }

#if 1
    if(g_dwUSPUhfVirTagWorkFlag == TRUE)
    {
        dwRetVal = usp_vir_fpga_readFrame((BYTE *)g_awFpgaReadBuf, FPGA_BUF_BYTE_SIZE, &dwCount);
    }
    else
    {
        dwRetVal = usp_vir_fpga_readFrame((BYTE *)g_awFpgaReadBuf, FPGA_BUF_BYTE_SIZE, &dwCount);
    }
#else
#if FPGA_SWTICH

    dwRetVal = usp_drv_fpga_read_frame((BYTE *)g_awFpgaReadBuf, FPGA_BUF_BYTE_SIZE, &dwCount);
#endif
#endif

    uhfDevPrint("UHF: Fpga read Frame  %d  Bytes\r\n", dwCount);

    if (dwRetVal == USP_SUCCESS)
    {
        if (dwCount == 0)
        {
            *pwReadLen = 0;
            UHFErrorPrint("UHF read: no frame, wait for interrupt notification \r\n");
            LAPInsert(FILE_FPGACTL, USP_UHF_FPGA_NO_FRAME, iProcErrNo, 0);
            dwRetVal = USP_UHF_FPGA_NO_FRAME;
        }
        else
        {
            *pwReadLen = (WORD16)dwCount / 2; /*驱动层返回的是字节的长度*/

            if (TRUE)//usp_oss_isPrintf(USP_UHF_TNO, USP_OSS_PRINTF_LEVEL_DEBUG))
            {
                uhfDevPrint("Fpga Fifo 0x");

                for (wIndex = 0; wIndex < *pwReadLen; wIndex++)
                {
                    uhfDevPrint("%04x ", g_awFpgaReadBuf[wIndex]);
                }

                uhfDevPrint("\r\n");
            }
        }
    }
    else
    {
        uhfDevPrint("Rcv Frame error\r\n");
        dwFpgaReadErrorTime++;

        if (dwFpgaReadErrorTime > UHF_FPGA_NEED_RESET_TIME)
        {
            dwFpgaReadErrorTime = 0;

        }

        LAPInsert(FILE_FPGACTL, dwRetVal, iProcErrNo, 0);
    }

    return dwRetVal;

}

/**********************************************************************
* 函数名称： uhf_EpcStartProcAndTimer
* 功能描述： 触发Fpga开始epc流程，并启动超时定时器
* 输入参数： wCmdType  命令码
* 输出参数：无
* 返 回 值：    无
* 其它说明：触发的为FPGA一次执行完毕步等待RCP命令
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*2012\3\16   RUP     zdx      创建
***********************************************************************/

void uhf_EpcStartProcAndTimer(WORD16 wCmdType)
{
    uhf_startRcpTimer(FPGA_TIMEOUT_INTERVAL_IN_MS);
    StartFpgaProc(wCmdType);
}

/**********************************************************************
* 函数名称： uhf_EpcStartLlrpProcAndTimer
* 功能描述： 触发Fpga开始epc llrp流程，并启动超时定时器
* 输入参数： wCmdType  命令码
* 输出参数：无
* 返 回 值：    无
* 其它说明：fpga执行完成一次后等待rcp下发新的指令，
                                 直到清点不到标签为止
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*2012\3\16   RUP     zdx      创建
***********************************************************************/

void uhf_EpcStartLlrpProcAndTimer(WORD16 wCmdType)
{
    uhf_startRcpTimer(FPGA_TIMEOUT_INTERVAL_IN_MS);
    StartFpgallrpProc(wCmdType);
}
/**********************************************************************
* 函数名称：void StartFpgaProc(WORD16 wCmdType)
* 功能描述：启动FPGA协议处理
* 输入参数：
          WORD16 wCmdType 命令类型 （清点、读、写、kill等）
* 输出参数：
* 返 回 值：无
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
static void StartFpgaProc(WORD16 wCmdType)
{
    if (0 != wCmdType)
    {
        /* 先写命令类型 */
        FpgaRegWrite(REG_CPU_CMD_type, wCmdType);

    }

    /* 启动FPGA协议处理 */
    /*
    Bit0        cmd_indic
    cmd_indic：0跳变为1，CPU触发MAC命令开始工作
    CPU需要在写操作命令类型寄存器之后，之后才能写入该位。
    */

    FpgaRegWrite(REG_CPU_CMD_Trig, 0x00);
    FpgaRegWrite(REG_CPU_CMD_Trig, 0x01);
    FpgaRegWrite(REG_CPU_CMD_Trig, 0x00);


}

/**********************************************************************
* 函数名称：WORD32 StartFpgaLlrpProc(WORD32 dwCmdType)
* 功能描述：启动FPGA协议处理
* 输入参数：
            WORD32 dwCmdType ： 命令类型 （清点、读、写、kill等）
* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
static void StartFpgallrpProc(WORD16 dwCmdType)
{

    WORD16   wCpuTrigRegValue = 0;

    if (0 != dwCmdType)
    {
        FpgaRegWrite(REG_CPU_CMD_type, dwCmdType);
    }

    /* 启动FPGA  LLRP协议处理 */

    /*
     Bit3        cmd_indic
     cmd_indic：0跳变为1，CPU触发MAC命令开始LLRP 工作模式
     CPU需要在写操作命令类型寄存器之后，之后才能写入该位。
    */
    wCpuTrigRegValue = FpgaRegRead(REG_CPU_LLRP_CMD_Trig);
    FpgaRegWrite(REG_CPU_LLRP_CMD_Trig, ((~wCpuTrigRegValue) & 0x1));

} /* WORD32 StartFpgaProc(WORD32 dwCmdType) */

/**********************************************************************
* 函数名称：WORD32 uhf_StopMacProc(void)
* 功能描述：停止FPGA协议处理，使其进入空闲
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
            WORD32
                         0：    成功
                      其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
WORD32 uhf_StopMacProc(void)
{
    /* Bit1    stop mac
                  stop mac： 0跳变为1，CPU触发MAC命令停止工作 */
    FpgaRegWrite(REG_CPU_CMD_Trig, 0);
    FpgaRegWrite(REG_CPU_CMD_Trig, 0x02);

    usleep(2000);
    return 0;

} /* WORD32 uhf_StopMacProc(void) */

/**********************************************************************
* 函数名称： void uhf_ProtoHwInit(void)
* 功能描述： 设置EPC相关的协议参数以及FPGA相关的控制寄存器
* 输入参数： 无
* 输出参数： 无
* 返 回 值：
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*
***********************************************************************/
void uhf_ProtoHwInit(void)
{

    uhf_epc_setTimePara();
    FpgaRegWrite(REG_COUPLE_TYPE, 0x01);
    FpgaRegWrite(REG_MOD_EN, 0x01);
    FpgaRegWrite(REG_DAC_SLEEP, 0x00);
    FpgaRegWrite(REG_FPGA_SAM_VALID_SIGNAL_CONTROL, 0x0);

    /* 下降沿门限值调整系数寄存器，
        signal_down_thresh_reg_factor，16位，地址：0055H
       Bit15-bit9，保留
       Bit7-bit0，Factor
       上升沿门限调制值寄存器，范围从1-128。
       建议配置为28 */
    FpgaRegWrite(0x0055, 0x0020);

    /* 上升沿门限值调整系数寄存器，
        signal_up_thresh_reg_factor，16位，地址：0093H
        Bit15-bit9，保留
        Bit7-bit0，Factor
        上升沿门限调制值寄存器，范围从1-128。
        建议配置为跟下降沿相同的值 */
    FpgaRegWrite(0x0093, 0x0020);

    FpgaRegWrite(noise_test_delay_val_h, 0x0);
    FpgaRegWrite(noise_test_delay_val_l, 0xcb20);
    FpgaRegWrite(noise_test_sampoint_cnt, 0xfa0);
    FpgaRegWrite(noise_test_adj_val, 0x200); //0x40);

    FpgaRegWrite(G2_write_rcv_delay_val_h, WRITE_RCV_DELAY_H);
    FpgaRegWrite(G2_write_rcv_delay_val_l, WRITE_RCV_DELAY_L);

    FpgaRegWrite(REG_fir_sig_down_thresh_factor, 0x0040);
    FpgaRegWrite(REG_fir_sig_up_thresh_factor, 0x0040);

    FpgaRegWrite(REG_forward_filter_enable, 0x0000);
    FpgaRegWrite(REG_backward_filter_enable, 0x0003);


    FpgaRegWrite(REG_FPGA_AGC_VALUE, 0x000f); //AGC control value

    /*默认情况下打开RSSI，FPGA清点时将RSSI值通过fifo 返回*/
    FpgaRegWrite(FPGA_RSSI_SWITCH, 0x1);

}
/**********************************************************************
* 函数名称： uhf_epc_setTimePara
* 功能描述： 设置EPC相关的时间参数
* 输入参数： 无
* 输出参数： 无
* 返 回 值：
* 其它说明：此中的t值需要根据协议和硬件进行协商后确定
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*
***********************************************************************/
#define FORWARD_FILTE_CLOSE 0x0

void uhf_epc_setTimePara(void)
{
    WORD16 wData = 0;
    WORD32 dwData = 0;

    /* EPC G2协议的前向链路速率寄存器 */
    FpgaRegWrite(G2_forlink_v, (WORD16)g_tEpcCtrl.RTDataRate);

    /* EPC G2协议的反向链路数据速率寄存器 */
    if (g_tEpcCtrl.TRDataRate < 640)
    {
        wData = (WORD16)(g_tEpcCtrl.TRDataRate);
    }
    else /* 由于实现精度问题,反向后台设定640,实际上的FPGA可使用反向速率不是640 */
    {
        wData = (WORD16)(g_tEpcCtrl.RealTRDataRate);
    }

    FpgaRegWrite(G2_reverse_link_v, wData);

    /*  EPC G2协议前向前导码类型寄存器 */
    wData = (WORD16)((g_tEpcCtrl.wRTcal_div_Tari << 5) | g_tEpcCtrl.wTRcal_div_halfTari);
    FpgaRegWrite(G2_forward_preamble_type, wData);

    /* EPC G2协议的T1值寄存器, 例：T1为5uS，则该值为g_tRcpCtrl.dwFpgaClock×0.000005=160. */

    wData = (WORD16)((g_tEpcCtrl.T1min - 10) * (FPGA_FREQUENCE / 1000000));
    FpgaRegWrite(G2_t1_value, wData);

    /* EPC G2协议的T2值寄存器, 例：T2为5uS，则该值为g_tRcpCtrl.dwFpgaClock×0.000005=130 */

    wData = (WORD16)(g_tEpcCtrl.T2min * 2 * (FPGA_FREQUENCE / 1000000)); //采用比标准t2min稍大的时序参数

    if (g_tEpcCtrl.TRDataRate >= 320)
    {
        wData = (WORD16)(0); //(g_tEpcCtrl.T2min * 1 * (26000000/1000000)); // decrease T2 config to avoid tag repeat
    }

    FpgaRegWrite(G2_t2_value, wData);

    /* EPC G2协议的T4值寄存器, 例：T4为5uS，则该值为g_tRcpCtrl.dwFpgaClock×0.000005=130 */
    wData = (WORD16)(g_tEpcCtrl.T4min * 2 * (FPGA_FREQUENCE / 1000000));   //data
    FpgaRegWrite(G2_t4_value, wData);

    /* EPC G2协议中反向链路数据前导码占用的时间值寄存器 */
    /* 没有考虑是否使用了TRext, */
    if (g_tEpcCtrl.Query.M == EPC_QUERY_M_1)
    {
        FpgaRegWrite(G2_tag_code_type, 0x0); //00：FM0
        g_tEpcCtrl.Query.TRext = EPC_QUERY_TREXT_USE_PILOT_TONE; //for 同步解调算法
    }
    else
    {
        FpgaRegWrite(G2_tag_code_type, 0x1); //01：Miller
    }

    if (g_tEpcCtrl.Query.M == EPC_QUERY_M_1)
    {
        //FM0
        //dwData = (WORD32)(((12) * g_tEpcCtrl.wTpri) + (6 * g_tEpcCtrl.wTpri));  //FM0 前导码时长
        //dwData = dwData + (6 * g_tEpcCtrl.wTpri);//加大一点余量
        dwData = (WORD32)(12 + 6);   //FM0 前导码时长
        dwData = dwData + 6 + 6; //加大一点余量
        dwData = dwData * g_tEpcCtrl.wTpri;
    }
    else
    {
        //Miller
        dwData = (WORD32)(16 + 6);  //Miller 前导码码长
        dwData = dwData + (6);       //加大一点余量
        dwData = dwData * (g_tEpcCtrl.wTpri * (1 << g_tEpcCtrl.Query.M));
    }


    dwData = dwData * (FPGA_FREQUENCE / 1000000); /* FPGA的频率乘以us */
    FpgaRegWrite(G2_reverse_preamble_t_val, (dwData & 0xffff));
    FpgaRegWrite(G2_reverse_preamble_t_val_h, ((dwData >> 16) & 0xffff));

    FpgaRegWrite(REG_forward_filter_enable, FORWARD_FILTE_CLOSE);
}

/**********************************************************************
* 函数名称：void uhf_EpcSetSelectPara()
* 功能描述：写FPGA的select命令参数寄存器。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_EpcSetSelectPara(WORD16 wTruncate, WORD16 wMemBank,
                          WORD16 wAction, WORD16 wTarget)
{
    WORD16 wData;
    wData = ((wTruncate & 0x1) << 8) | ((wMemBank & 0x3) << 6)
            | ((wAction & 0x7) << 3) | ((wTarget & 0x7) << 0);
    uhfDevPrint("MemBank %d, Action %d wTarget %d truncate %d\r\n",
                wMemBank, wAction, wTarget, wTruncate);
    FpgaRegWrite(REG_G2_Select_Para, wData);

} /* void FpgaTestRegWrite(WORD16 wData) */

/**********************************************************************
* 函数名称：void uhf_EpcSetMacQueryPara(void)
* 功能描述：写FPGA的Query命令参数寄存器。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_EpcSetMacQueryPara(WORD16 wQ, WORD16 wM, WORD16 wDR)
{
    WORD16 wData = 0;
    WORD16 wTRext = 0;

    if (wM == EPC_QUERY_M_1)
    {
        wTRext = EPC_QUERY_TREXT_USE_PILOT_TONE;
    }
    else
    {
        wTRext = EPC_QUERY_TREXT_NO_PILOT_TONE;
    }

    wData = ((wQ & 0xF) << 9)/*Q*/
            | ((EPC_QUERY_TARGET_B & 0x1) << 8)/*Target*/
            | ((0x0 & 0x3) << 6)/*session*/
            | ((0x0 & 0x3) << 4)/*sel*/
            | ((wTRext & 0x1) << 3)/*TRext*/
            | ((wM & 0x3) << 1)/*M*/
            | ((wDR & 0x1) << 0);/*DR*/
    FpgaRegWrite(REG_G2_Query_Para, wData);

} /* void uhf_EpcSetMacQueryPara(void) */

/**********************************************************************
* 函数名称：WORD32 FpgaTest(void)
* 功能描述：FPGA功能测试函数，用于生产线测试。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：WORD32
                0：  FPGA工作正常
             其它：  FPGA不能正常工作
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
static WORD32 FpgaTest(void)
{
    WORD32 dwIndex;
    WORD16 wWriteData;
    WORD16 wReadData;
    WORD32 dwReadCount = 0;
    WORD32 dwTestResult = 0;

    /* FPGA测试 */
    for (dwIndex = 0 ; dwIndex < FPGA_DATA_BUS_WIDTH; dwIndex++)
    {
        wWriteData = (0x1 << dwIndex);

        FpgaRegWrite(REG_Fpga_test, wWriteData);

        for (dwReadCount = 0; dwReadCount < 3; dwReadCount++)
        {
            wReadData = FpgaRegRead(REG_Fpga_test);
            wReadData = ~wReadData;

            if (wWriteData != wReadData)
            {
                printf("fpga test error write is 0x%04x, read is 0x%04x\r\n", wWriteData, wReadData);
                dwTestResult = 1;
            }

        }

        wWriteData = ~wWriteData;
        FpgaRegWrite(REG_Fpga_test, wWriteData);

        for (dwReadCount = 0; dwReadCount < 3; dwReadCount++)
        {
            wReadData = FpgaRegRead(REG_Fpga_test);
            wReadData = ~wReadData;

            if (wWriteData != wReadData)
            {
                printf("fpga test error， write is 0x%04x, read is 0x%04x\r\n", wWriteData, wReadData);
                dwTestResult = 1;
            }
        }

    }

    /*FpgaTest success*/

    return (dwTestResult);

} /* WORD32 FpgaTest(void) */
/**********************************************************************
* 函数名称：FpgaTestNCnt
* 功能描述：fpga测试寄存器的验证函数
* 输入参数：
* 输出参数：WORD32
                0：  FPGA工作正常
             其它：  fpga工作有问题错误次数
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/

static WORD32 FpgaTestNCnt(WORD32 dwTestCnt)
{
    WORD32 dwIndex;
    WORD32 dwFpgaTestOkCount = 0;
    WORD32 dwFpgaTestErrorCount = 0;
    WORD32 dwFpgaTotalTestCount = 0;

    time_t timep;
    time(&timep);
    printf("UHF: Fpga bus Test begin  at :%s \r\n", ctime(&timep));

    /* FPGA功能测试 测试不通过系统重启*/
    for (dwIndex = 0; dwIndex < dwTestCnt; dwIndex++)
    {
        if (0 == FpgaTest())
        {
            dwFpgaTestOkCount++;
        }
        else
        {
            dwFpgaTestErrorCount++;
            sleep(2);
        }

        if (dwIndex % 1000 == 0)
        {
            printf(".");
        }
    }

    dwFpgaTotalTestCount += dwTestCnt;
    printf("UHF: dwFpgaTotalTestCount = %10u \r\n", dwFpgaTotalTestCount);
    printf("UHF: dwFpgaTestOkCount    = %10u \r\n", dwFpgaTestOkCount);
    printf("UHF: dwFpgaTestErrorCount = %10u \r\n", dwFpgaTestErrorCount);
    sleep(1);

    return dwFpgaTestErrorCount;

}

/**********************************************************************
* 函数名称：uhf_epc_setSelectMask
* 功能描述：设置select命令的mask相关数值
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
#define ROUND_BITS_TO_WORDS(BitNum)  (((BitNum) + 15)/16)

void uhf_epc_setSelectMask(WORD16 wAddr, WORD16 wMaskBitLen, WORD16 *pwData)
{
    WORD32 dwIndex;
    WORD16 wEbvAddr = 0;

    /* 大于127 第二个EBV需要有值 ,以下将值转换为EBV 表示*/
    wEbvAddr = ((wAddr >> 7) > 0) ? 0x8000 : 0;
    wEbvAddr = ((wAddr << 1) & 0x7f00) | (wAddr & 0x7f) | wEbvAddr;

    FpgaRegWrite(REG_G2_Select_Addr, wEbvAddr);
    RcpFpgaPrint("MaskBit EbvPointer %x ", wEbvAddr);
    /* 注意需要扩展EBV */

    /* MaskBitLength */
    FpgaRegWrite(REG_G2_Select_Mask_BitLen, wMaskBitLen);
    RcpFpgaPrint("MaskBitLength %d\r\nMaskData ", wMaskBitLen);


    /* select命令MASK寄存器 */
    for (dwIndex = 0; dwIndex < ROUND_BITS_TO_WORDS(wMaskBitLen); dwIndex++)
    {
        FpgaRegWrite(REG_G2_Select_Mask_Start + dwIndex, pwData[dwIndex]);
        RcpFpgaPrint(" %4x ", pwData[dwIndex]);
    }

    RcpFpgaPrint("\r\n");

}

/**********************************************************************
* 函数名称：void SetEpcReadPara(T_LLRPC1G2Read *ptEpcReadPara)
* 功能描述：设置fpga读参数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_EpcSetMacReadPara(WORD16 wMemBank, WORD16 wAddr, WORD16 wWordCount)
{
    /* read命令MemBank寄存器 */
    FpgaRegWrite(REG_G2_Read_Membank, (WORD16)(wMemBank & 0x3));
    RcpFpgaPrint("ptFpgaEpcRead->wMemBank:    0x%04x \r\n", wMemBank);

    /* read命令地址寄存器 */    /* 注意需要扩展EBV */
    FpgaRegWrite(REG_G2_Read_Addr, (wAddr & 0x7f));
    RcpFpgaPrint("ptFpgaEpcRead->wWordPointer: 0x%04x \r\n", wAddr);

    /* read命令读字个数寄存器*/
    FpgaRegWrite(REG_G2_Read_WordCount, wWordCount);
    RcpFpgaPrint("ptFpgaEpcRead->wReadWordsLen: 0x%04x \r\n", wWordCount);

} /* static int uhf_EpcSetMacReadPara(T_FpgaEpcRead *ptFpgaEpcRead) */

/**********************************************************************
* 函数名称：void SetEPCWrtRtyTime(WORD16 wWriteLength)
* 功能描述：根据写入的长度判断需要重试的次数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010/6/17        V3.00.00      ZDX         修改
************************************************************************/
void SetEPCWrtRtyTime(WORD16 wWriteLength)
{
    WORD16 wFpgaRetryRegVal = 0;
    wFpgaRetryRegVal = FpgaRegRead(REG_FPGA_WRITE_READ_RETRY_TIME);

    if (wWriteLength <= 5)
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x03;
    }
    else if (wWriteLength <= 16)
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x08;
    }
    else if (wWriteLength < 32)
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x10;
    }
    else
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x20;
    }

    FpgaRegWrite(REG_FPGA_WRITE_READ_RETRY_TIME, wFpgaRetryRegVal);
}


/**********************************************************************
* 函数名称：void uhf_EpcSetMacWritePara(WORD16 wMemBank,WORD16 wAddr,WORD16 wWrWordLen,BYTE *ucdata)
* 功能描述：
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_EpcSetMacWritePara(WORD16 wMemBank, WORD16 wAddr, WORD16 wWrWordLen, BYTE *ucdata)
{
    WORD16 wIndex = 0;
    /* Write命令MemBank寄存器 */
    FpgaRegWrite(REG_G2_Write_Membank, (WORD16)(wMemBank & 0x3));
    RcpFpgaPrint("MemBank %d", wMemBank);

    /* Write命令地址寄存器 */
    FpgaRegWrite(REG_G2_Write_Addr, (wAddr & 0x7f));
    RcpFpgaPrint("WordPointer  %d", wAddr);
    /* 注意需要扩展EBV */

    /* Write命令读字个数寄存器 */
    FpgaRegWrite(REG_G2_Write_WordCount, wWrWordLen);
    RcpFpgaPrint("WriteWordsLen  %d \r\nWrite Data", wWrWordLen);

    /*根据FPGA的需求，不同的写长度写重试次数不同，提高写入的成功率*/
    SetEPCWrtRtyTime(wWrWordLen);

    /*以下设置FPGA
    的控制超时时间*/
    FpgaRegWrite(G2_write_rcv_delay_val_h, 0x0007);
    FpgaRegWrite(G2_write_rcv_delay_val_l, 0x6590);

    /* write命令数据寄存器 */
    for (wIndex = 0; wIndex < wWrWordLen; wIndex++)
    {
        FpgaRegWrite(REG_G2_BlockWrite_Data_Start + wIndex,
                     ((((WORD16)ucdata[2 * wIndex]) << 8) | ((WORD16)ucdata[2 * wIndex + 1])));
        RcpFpgaPrint("%04x",
                     ((((WORD16)ucdata[2 * wIndex]) << 8) | ((WORD16)ucdata[2 * wIndex + 1])));
    }

    RcpFpgaPrint("\r\n");
} /* static int uhf_EpcSetMacWritePara(T_FpgaEpcWrite *ptFpgaEpcWrite) */

/**********************************************************************
* 函数名称：static int uhf_EpcSetMacWritePara(T_FpgaEpcRead *ptFpgaEpcWrite)
* 功能描述：
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_EpcSetMacBlockWritePara(WORD16 wMemBank, WORD16 wAddr, WORD16 wWrWordLen, BYTE *ucdata)
{
    WORD16 wIndex = 0;
    WORD32 dwBlockWriteDelayTime = EPC_BLOCK_START_DELAY;
    /* Write命令MemBank寄存器 */
    FpgaRegWrite(REG_G2_Block_Write_Membank, (WORD16)(wMemBank & 0x3));
    RcpFpgaPrint("MemBank %d", wMemBank);

    /* Write命令地址寄存器 */
    FpgaRegWrite(REG_G2_Block_Write_Adress, (wAddr & 0x7f));
    RcpFpgaPrint("WordPointer  %d", wAddr);
    /* 注意需要扩展EBV */

    /* Write命令读字个数寄存器 */
    FpgaRegWrite(REG_G2_Block_Write_Length, wWrWordLen);
    RcpFpgaPrint("WriteWordsLen  %d \r\nWrite Data ", wWrWordLen);

    /* write命令数据寄存器 */
    for (wIndex = 0; wIndex < wWrWordLen; wIndex++)
    {
        FpgaRegWrite(REG_G2_BlockWrite_Data_Start + wIndex,
                     ((((WORD16)ucdata[2 * wIndex]) << 8) | ((WORD16)ucdata[2 * wIndex + 1])));
        RcpFpgaPrint("%04x",
                     ((((WORD16)ucdata[2 * wIndex]) << 8) | ((WORD16)ucdata[2 * wIndex + 1])));
    }

    RcpFpgaPrint("\r\n");


    wWrWordLen = (wWrWordLen > 1) ? (wWrWordLen - 1) : 0;
    dwBlockWriteDelayTime += ((FPGA_FREQUENCE/1000)* wWrWordLen * 2);
    FpgaRegWrite(G2_write_rcv_delay_val_h, (WORD16)(dwBlockWriteDelayTime >> 16));
    FpgaRegWrite(G2_write_rcv_delay_val_l, (WORD16)(dwBlockWriteDelayTime & 0xffff));

} /* static int uhf_EpcSetMacWritePara(T_FpgaEpcWrite *ptFpgaEpcWrite) */

/**********************************************************************
* 函数名称：uhf_EpcSetMacLockPara
* 功能描述：设置epc锁定参数
* 输入参数：锁定参数
* 输出参数：无
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/

void uhf_EpcSetMacLockPara(WORD32 dwLockPayLoad)
{

    /* payload_mask */
    FpgaRegWrite(REG_G2_Loc_payload_mask, ((dwLockPayLoad >> 10) & 0x3FF));
    RcpFpgaPrint("G2_Loc_payload_mask   = 0x%04x \r\n", (dwLockPayLoad >> 10) & 0x3FF);

    /* payload_Action */
    FpgaRegWrite(REG_G2_Loc_payload_Action, (dwLockPayLoad & 0x3FF));
    RcpFpgaPrint("G2_Loc_payload_Action = 0x%04x \r\n", dwLockPayLoad & 0x3FF);

}

/**********************************************************************
* 函数名称：uhf_EpcSetMacAccessPara
* 功能描述：设置epc访问命令参数，密码访问时需要
* 输入参数：访问密钥
* 输出参数：无
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/

void  uhf_EpcSetMacAccessPara(WORD32 dwAccessPassword)
{
    /* wAccessPassHigh */
    FpgaRegWrite(REG_G2_Access_Password_h, (WORD16)((dwAccessPassword >> 16) & 0xffff));
    /* wAccessPassLow */
    FpgaRegWrite(REG_G2_Access_Password_L, (WORD16)(dwAccessPassword & 0xffff));
    RcpFpgaPrint("uhf: access password   = 0x%x \r\n", dwAccessPassword);

}
/**********************************************************************
* 函数名称：uhf_EpcSetMacKillPara
* 功能描述：设置epc杀死密码杀死时需要
* 输入参数：杀死密钥
* 输出参数： 无
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/

void uhf_EpcSetMacKillPara(WORD32 dwKillPassword)
{

    RcpFpgaPrint("UHF: wKillPassWord = 0x%04x \n", dwKillPassword);
    /* wKillPassHigh */
    FpgaRegWrite(REG_G2_Kill_Password_h, (WORD16)((dwKillPassword >> 16) & 0xffff));

    /* wKillPassLow */
    FpgaRegWrite(REG_G2_Kill_Password_L, (WORD16)(dwKillPassword & 0xffff));


    FpgaRegWrite(REG_G2_Kill_RFU, 0x0000);

}
/**********************************************************************
* 函数名称：uhf_EpcSetMacKillPara
* 功能描述：设置epc 块锁的参数
* 输入参数：ucReadLock  1代表读锁定状态，0代表设置
* 输出参数： 无
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
void uhf_EpcSetMacBlockLock(BYTE ucReadLock, WORD16 wMemBank, WORD16 wBlockPtr,
                            WORD16 wBlockRang, BYTE *ucdata)
{
    WORD16      wBlockLockCmd = 0;
    WORD16      wIndex = 0;
    wBlockLockCmd = wMemBank & 0x3;

    if (ucReadLock == 1)
    {
        wBlockLockCmd |= 0x4;
    }

    /* membank */
    FpgaRegWrite(REG_G2_Block_Lock_MemBank, wBlockLockCmd);
    /* 注意需要扩展EBV */
    RcpFpgaPrint("UHF: REG_G2_Block_Lock_MemBank  = %d \r\n", wBlockLockCmd);

    /* wBlockPtr*/
    FpgaRegWrite(REG_G2_Blcokpermalock_EVB, wBlockPtr);
    RcpFpgaPrint("UHF: REG_G2_Blcokpermalock_EVB  = %d \r\n", wBlockPtr);

    /* blankrange */
    FpgaRegWrite(REG_G2_Blockpermalock_Blockrange, wBlockRang);
    RcpFpgaPrint("UHF: REG_G2_Blockpermalock_Blockrange  = %d \r\n", wBlockRang);

    if (ucReadLock == 1)
    {
        RcpFpgaPrint("Mask is");

        for (wIndex = 0; wIndex < wBlockRang; wIndex++)
        {
            FpgaRegWrite(REG_G2_BlockWrite_Data_Start + wIndex,
                         (WORD16)((((WORD16)ucdata[wIndex * 2]) << 8) | ucdata[wIndex * 2 + 1]));
            RcpFpgaPrint("0x%02x%02x", ucdata[wIndex * 2], ucdata[wIndex * 2 + 1]);
        }

        RcpFpgaPrint("\r\n");
    }
}


/**********************************************************************
* 函数名称：uhf_EpcSetMacReadLock
* 功能描述：根据生成的读保护的掩码来设置读锁定的块
* 输入参数：wReadLockMask都锁定的掩码，其中的位为0代表解锁
                                1 代表锁定
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010/1/28    V0.0.1          chenjie        创建
************************************************************************/
void uhf_EpcSetMacReadLock(WORD16 wReadLockMask)
{
    /*Read Lock 写入掩码*/
    FpgaRegWrite(REG_G2_Blockreadlock_mask, wReadLockMask);

    RcpFpgaPrint("UHF: REG_G2_Blockreadlock_mask  = 0x%04x \n", wReadLockMask);
}

/**********************************************************************
* 函数名称：uhf_EpcSetMacIPJQT
* 功能描述：设置impinj标签fpga相关的寄存器
* 输入参数：ucReadOrWrite 0 代表读1代表写
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2011/9/14    V4.60.00      zdx         创建
************************************************************************/
void uhf_EpcSetMacIPJQT(BYTE ucReadOrWrite, BYTE ucPersistence,
                        BYTE ucQT_SR, BYTE ucQT_MEM)
{
    FpgaRegWrite(REG_I_QT_WR_PER, (((ucReadOrWrite & 0x1) << 1) | (ucPersistence & 0x1)));
    FpgaRegWrite(REG_I_QT_PAYLOAD, (((ucQT_SR & 0x1) << 15) | ((ucQT_MEM & 0x1) << 14)));
    uhfDevPrint("uhf:readorwrite %d persistence %d SR %d Memory map %d\r\n",
                ucReadOrWrite, ucPersistence, ucQT_SR, ucQT_MEM);

}

/**********************************************************************
* 函数名称： void uhf_ISO6BSetProtoPara(T_ISO6BCtl *ptISO6BCtrl)
* 功能描述： 设置FPGA 6B协议参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
#define FORWARD_FILTE_OPEN 0x3
void uhf_ISO6BSetProtoPara(WORD16 wFowardLinkDataRate, WORD16 wReverseLinkDataRate,
                           WORD16 wT1_value, WORD16 wdelimeters, WORD16 wISO6BModulateDepth)
{
    SetProtoType(UHF_PROTO_TYPE_ISO6B);
    /* 前向速率设在40K，反向速率为40K */
    FpgaRegWrite(G2_forlink_v, wFowardLinkDataRate);
    FpgaRegWrite(G2_reverse_link_v, wReverseLinkDataRate);

    /* 接收超时技术器T1，需要设置的较大，0x5000，可以用 */
    FpgaRegWrite(G2_t1_value, wT1_value);/*guanyi modify 2007.09.26*/

    /* 这里改变了与EPC协议共用的寄存器，在开始EPC协议签需要重新设置为EPC需要的参数 */

    /* MAC协议层寄存器 */
    FpgaRegWrite(ISO18000_6B_forward_preamble_type, wdelimeters);

    /*打开FPGA前向滤波器*/
    FpgaRegWrite(REG_forward_filter_enable, FORWARD_FILTE_OPEN);

}
/**********************************************************************
* 函数名称： uhf_ISO6BSetUIDPara
* 功能描述： 设置ISO协议操作的uid码
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/

void uhf_ISO6BSetUIDPara(BYTE *pucUID)
{
    FpgaRegWrite(REG_18000B_access_UID_3, ((((WORD16)pucUID[0]) << 8) | ((WORD16)pucUID[1])));
    FpgaRegWrite(REG_18000B_access_UID_2, ((((WORD16)pucUID[2]) << 8) | ((WORD16)pucUID[3])));
    FpgaRegWrite(REG_18000B_access_UID_1, ((((WORD16)pucUID[4]) << 8) | ((WORD16)pucUID[5])));
    FpgaRegWrite(REG_18000B_access_UID_0, ((((WORD16)pucUID[6]) << 8) | ((WORD16)pucUID[7])));
}

/**********************************************************************
* 函数名称：uhf_ISO6BSetRead8BytePara
* 功能描述： 写入fpga中8bye读命令参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/

void uhf_ISO6BSetRead8BytePara(WORD16 wStartAddr)
{
    FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_direct_access);
    FpgaRegWrite(REG_18000B_accesscmd_type, ISO18000B_accesscmd_type_READ);
    FpgaRegWrite(REG_18000B_access_Address, wStartAddr);
}

/**********************************************************************
* 函数名称：uhf_ISO6BSetReadVrblPara
* 功能描述： 写入fpga中变长读命令参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/

void uhf_ISO6BSetReadVrblPara(WORD16 wStartAddr, WORD16 wFpgaReadLen)
{
    /* 填写单次读相关参数*/
    FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_direct_access);
    FpgaRegWrite(REG_18000B_accesscmd_type, ISO18000B_accesscmd_type_Variable_READ);
    /*协议规定此命令时读取长度减1*/
    FpgaRegWrite(REG_18000B_Read_Variable_Len, wFpgaReadLen);
    FpgaRegWrite(REG_18000B_access_Address, wStartAddr);
}

/**********************************************************************
* 函数名称：uhf_ISO6BSetWriteBytePara
* 功能描述： 写入fpga中普通写命令的参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
void uhf_ISO6BSetWriteBytePara(WORD16 wStartAddr, BYTE *pucWriteData)
{
    /* 填写单次写相关参数*/
    FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_direct_access);
    FpgaRegWrite(REG_18000B_accesscmd_type, ISO18000B_accesscmd_type_WriteByte);
    FpgaRegWrite(REG_18000B_access_Address, wStartAddr);
    /* 填写单次写内容*/
    FpgaRegWrite(REG_18000B_write_data_0, ((WORD16)*pucWriteData));
    FpgaRegWrite(REG_18000B_write_continue, 0x0001);

}

/**********************************************************************
* 函数名称：uhf_ISO6BSetWrite4BytePara
* 功能描述： 写入fpga中4字节写命令的参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
void uhf_ISO6BSetWrite4BytePara(WORD16 wStartAddr, BYTE *pucWriteData)
{
    /* 填写单次写相关参数*/
    FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_direct_access);
    FpgaRegWrite(REG_18000B_accesscmd_type, ISO18000B_accesscmd_type_Write4Bytes);
    FpgaRegWrite(REG_18000B_access_Address, wStartAddr);
    /* 填写单次写内容*/
    FpgaRegWrite(REG_18000B_write_data_0, ((((WORD16)pucWriteData[2]) << 8) | ((WORD16)pucWriteData[3])));
    FpgaRegWrite(REG_18000B_write_data_1, ((((WORD16)pucWriteData[0]) << 8) | ((WORD16)pucWriteData[1])));
    /* 填写掩码*/
    FpgaRegWrite(REG_18000B_write_bytemask, 0xff);
    FpgaRegWrite(REG_18000B_write_continue, 0x0001);
}

/**********************************************************************
* 函数名称：uhf_ISO6BSetLockBytePara
* 功能描述： 写入fpga中字节锁定命令的参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/

void uhf_ISO6BSetLockBytePara(WORD16 wStartAddr)
{
    /* 填写单次写相关参数*/
    FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_direct_access);
    FpgaRegWrite(REG_18000B_accesscmd_type, ISO18000B_accesscmd_type_Lock);
    FpgaRegWrite(REG_18000B_access_Address, wStartAddr);

}

/**********************************************************************
* 函数名称：uhf_ISO6BSetLockQueryPara
* 功能描述： 写入fpga中字节锁定查询命令的参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
void uhf_ISO6BSetLockQueryPara(WORD16 wStartAddr)
{
    /* 填写单次写相关参数*/
    FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_direct_access);
    FpgaRegWrite(REG_18000B_accesscmd_type, ISO18000B_accesscmd_type_LockQuery);
    FpgaRegWrite(REG_18000B_access_Address, wStartAddr);
}


/**********************************************************************
* 函数名称：uhf_ISO6BSetInventoryPara
* 功能描述： 写入fpga中清点命令的参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
void uhf_ISO6BSetInventoryPara(WORD16 wISOCommand, WORD16 wMaskByteAddr,
                               WORD16 wInventQ, WORD16 wMask, WORD16 wDataReadStartAddr, BYTE *pucMaskData)
{
    WORD16 wIndex = 0;

    SetProtoType(UHF_PROTO_TYPE_ISO6B);
    FpgaRegWrite(REG_18000B_selectcmd_type, wISOCommand);
    FpgaRegWrite(REG_18000B_sel_address, wMaskByteAddr);
    FpgaRegWrite(REG_FPGA_ISO6B_INVENTQ, wInventQ);

    FpgaRegWrite(REG_18000B_sel_mask, (wMask & 0x00ff));
    uhfDevPrint("ISOCommand %d MaskByteAddr %d InventQ %d Mask %d\r\n",
                wISOCommand, wMaskByteAddr, wInventQ, wMask);

    /*此REG_18000B_accesscmd_type 寄存器由于read_varible 命令中添加
    	   设置为了0x51，FPGA根据这个值去判断物理层解码的长度
    	   在清点命令时需要将其清0*/
    FpgaRegWrite(REG_18000B_accesscmd_type, 0x0);

    if (wISOCommand >= GROUP_SELECT_EQ_FLAGS)
    {
        FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_noinit_invent);
        /*当使用FLAGAS命令是需要写入的数据*/
        FpgaRegWrite(REG_18000B_sel_flags_Byte_data, (WORD16)pucMaskData[0]);
    }
    else
    {
        FpgaRegWrite(REG_18000B_cmd_mode, ISO18000B_cmd_mode_invent);
        /*当使用其他命令是需要写入的数据*/
        FpgaRegWrite(REG_18000B_sel_worddata_3, (((WORD16)(pucMaskData[0]) << 8) | pucMaskData[1]));
        FpgaRegWrite(REG_18000B_sel_worddata_2, (((WORD16)(pucMaskData[2]) << 8) | pucMaskData[3]));
        FpgaRegWrite(REG_18000B_sel_worddata_1, (((WORD16)(pucMaskData[4]) << 8) | pucMaskData[5]));
        FpgaRegWrite(REG_18000B_sel_worddata_0, (((WORD16)(pucMaskData[6]) << 8) | pucMaskData[7]));
    }

    uhfDevPrint("Mask data ");

    for (wIndex = 0; wIndex < 8; wIndex++)
    {
        uhfDevPrint("%2x", pucMaskData[wIndex]);
    }

    uhfDevPrint("\r\n");

    /*以下地址是为了确定在清点到标签发送dataread命令使
    						标签进入到DATAExchange命令时读取的起始地址*/
    FpgaRegWrite(REG_18000B_access_Address, wDataReadStartAddr);

}

//////////////////////
/// GB Operation  lxc
//////////////////////
/**********************************************************************
* 函数名称：void SetGBWrtRtyTime(WORD16 wWriteLength)
* 功能描述：根据写入的长度判断需要重试的次数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/17        V3.00.00      lxc        修改
************************************************************************/
void SetGBWrtRtyTime(WORD16 wWriteLength)
{
    WORD16 wFpgaRetryRegVal = 0;
    wFpgaRetryRegVal = FpgaRegRead(REG_GB_FPGA_WRITE_READ_RETRY_TIME);

    if (wWriteLength <= 5)
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x03;
    }
    else if (wWriteLength <= 16)
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x08;
    }
    else if (wWriteLength < 32)
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x10;
    }
    else
    {
        wFpgaRetryRegVal = (wFpgaRetryRegVal & (0xff00)) | 0x20;
    }

    FpgaRegWrite(REG_GB_FPGA_WRITE_READ_RETRY_TIME, wFpgaRetryRegVal);
}


/**********************************************************************
* 函数名称： uhf_GBStartLlrpProcAndTimer
* 功能描述： 触发Fpga开始epc llrp流程，并启动超时定时器
* 输入参数： wCmdType  命令码
* 输出参数：无
* 返 回 值：    无
* 其它说明：fpga执行完成一次后等待rcp下发新的指令，
                                 直到清点不到标签为止
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*2012\3\16   RUP     zdx      创建
***********************************************************************/

void uhf_GBStartLlrpProcAndTimer(WORD16 wCmdType)
{
    uhf_startRcpTimer(FPGA_TIMEOUT_INTERVAL_IN_MS);
    StartFpgallrpProc(wCmdType);
}

/**********************************************************************
* 函数名称： uhf_GB_setTimePara
* 功能描述： 设置GB相关的时间参数
* 输入参数： 无
* 输出参数： 无
* 返 回 值：
* 其它说明：此中的t值需要根据协议和硬件进行协商后确定
* 修改日期2014.2        版本号     修改人  lxc        修改内容
* -----------------------------------------------
*
***********************************************************************/

void uhf_GB_setTimePara(void)  // 是不是需要根据新国标协议重新配置时序
{
    WORD16 wData = 0;
    WORD32 dwData = 0;

    /* GB协议的前向链路速率寄存器 */ /* 具体参数写0 、1 */
    FpgaRegWrite(G2_forlink_v, (WORD16)g_tGBCtrl.RTDataRate);

    /* GB协议的反向链路数据速率寄存器 */
    if (g_tGBCtrl.TRDataRate < 640)
    {
        wData = (WORD16)(g_tGBCtrl.TRDataRate);
    }
    else /* 由于实现精度问题,反向后台设定640,实际上的FPGA可使用反向速率不是640 */
    {
        wData = (WORD16)(g_tGBCtrl.RealTRDataRate);
    }
    FpgaRegWrite(G2_reverse_link_v, wData);

    /*  GB 协议前向前导码类型寄存器 */ /* 国标定死 */
    //wData = (WORD16)((g_tGBCtrl.wRTcal_div_Tari << 5) | g_tGBCtrl.wTRcal_div_halfTari);
    //FpgaRegWrite(G2_forward_preamble_type, wData);

    /* GB 协议的T1值寄存器, 例：T1为5uS，则该值为g_tRcpCtrl.dwFpgaClock×0.000005=160. */
    //wData = (WORD16)((g_tGBCtrl.T1min - 10) * (FPGA_FREQUENCE / 1000000));
     wData = (WORD16)(40 * (FPGA_FREQUENCE / 1000000));
    FpgaRegWrite(G2_t1_value, wData);

    /* GB 协议的T2值寄存器, 例：T2为5uS，则该值为g_tRcpCtrl.dwFpgaClock×0.000005=130 */
    wData = (WORD16)(g_tGBCtrl.T2min * 2 * (FPGA_FREQUENCE / 1000000)); //采用比标准t2min稍大的时序参数

    if (g_tGBCtrl.TRDataRate >= 320)
    {
        wData = (WORD16)(0); //(g_tGBCtrl.T2min * 1 * (26000000/1000000)); // decrease T2 config to avoid tag repeat
    }
    wData = (WORD16)(63 * (FPGA_FREQUENCE / 1000000));
    FpgaRegWrite(G2_t2_value, wData);

    /* GB协议的T4值寄存器, 例：T4为5uS，则该值为g_tRcpCtrl.dwFpgaClock×0.000005=130 */
    wData = (WORD16)(g_tGBCtrl.T4min * 2 * (FPGA_FREQUENCE / 1000000));   //data
    FpgaRegWrite(G2_t4_value, wData);
    
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// lxc
    /* GB 协议中反向链路数据前导码占用的时间值寄存器 */
    /* 没有考虑是否使用了TRext, */
    if (g_tGBCtrl.Query.ucM == GB_QUERY_M_1)
    {
        FpgaRegWrite(G2_tag_code_type, 0x0); //00：FM0
        //TRext表示是否加入前导信号
        g_tGBCtrl.Query.ucTRext = EPC_QUERY_TREXT_USE_PILOT_TONE; //for 同步解调算法
    }
    else
    {
        FpgaRegWrite(G2_tag_code_type, 0x1); //01：Miller
    }

    //计算前导码占用时间lxc
    if (g_tGBCtrl.Query.ucM == GB_QUERY_M_1)
    {
        //FM0
        //dwData = (WORD32)(((12) * g_tEpcCtrl.wTpri) + (6 * g_tEpcCtrl.wTpri));  //FM0 前导码时长
        //dwData = dwData + (6 * g_tEpcCtrl.wTpri);//加大一点余量
        dwData = (WORD32)(12 + 8);   //FM0 前导码时长
        dwData = dwData + 6 + 6; //加大一点余量
        dwData = dwData * g_tGBCtrl.wTpri;
    }
    else
    {
        //Miller
        dwData = (WORD32)(16 + 8);  //Miller 前导码码长
        dwData = dwData + (6);       //加大一点余量
        dwData = dwData * (g_tGBCtrl.wTpri * (1 << g_tGBCtrl.Query.ucM));
    }

    RcpFpgaPrint("G2_reverse_preamble_t_val :%d", dwData);
    dwData = dwData * (FPGA_FREQUENCE / 1000000);
    //FpgaRegWrite(G2_reverse_preamble_t_val, (dwData & 0xffff));
    //FpgaRegWrite(G2_reverse_preamble_t_val_h, ((dwData >> 16) & 0xffff));

    FpgaRegWrite(G2_reverse_preamble_t_val, 0xdc6);
    FpgaRegWrite(G2_reverse_preamble_t_val_h, 0x2);
    //前向滤波使能关闭
    FpgaRegWrite(REG_forward_filter_enable, FORWARD_FILTE_CLOSE);
}

/**********************************************************************
* 函数名称：uhf_epc_setSelectMask
* 功能描述：设置select命令的mask相关数值
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
///// 是否需要掩码lxc
////  需要掩码，并且多了一个命令指针寄存器
////  EBV 表示指向起始地址，与国标中的指针相同
////  sort命令指针寄存器，地址：C002H
void uhf_GB_setSelectMask(WORD16 wAddr, WORD16 wMaskBitLen, WORD16 *pwData)
{
    WORD32 dwIndex;
    WORD16 wEbvAddr = 0;//新国标中的指针pointer

     wEbvAddr = wAddr;

    /* 大于127 第二个EBV需要有值 ,以下将值转换为EBV 表示*/
    //wEbvAddr = ((wAddr >> 7) > 0) ? 0x8000 : 0;
    //wEbvAddr = ((wAddr << 1) & 0x7f00) | (wAddr & 0x7f) | wEbvAddr;

    // sort 命令掩码寄存器
    // 新国标没有特别指明是否采用EBV格式的掩码
    // 写C002h，命令指针寄存器
    //lxc
    FpgaRegWrite(REG_GB_Sort_Cmd_Ptr, wEbvAddr); 
    RcpFpgaPrint("MaskBit Sort_Cmd_Ptr %x ", wEbvAddr);
    /* 注意需要扩展EBV */

    /* MaskBitLength */
    /* ?	sort命令长度寄存器，地址，C003H   lxc */
    FpgaRegWrite(REG_GB_Sort_Cmd_BitLen, wMaskBitLen);
    RcpFpgaPrint("Sort_Cmd_BitLen %d\r\nMaskData ", wMaskBitLen);


    /* select命令MASK寄存器 */
    // sort命令掩码寄存器，该数据组采用DPRAM方式实现，
    // 地址空间为10000H－1FFFFH，总共128K，基址为10000H，实际占用64字节
    //掩码的长度和数据的长度相等
    //lxc
    for (dwIndex = 0; dwIndex < ROUND_BITS_TO_WORDS(wMaskBitLen); dwIndex++)
    {
        FpgaRegWrite(REG_GB_Select_Mask_Start + dwIndex, pwData[dwIndex]);
        RcpFpgaPrint(" %4x ", pwData[dwIndex]);
    }

    RcpFpgaPrint("\r\n");

}

/**********************************************************************
* 函数名称：void uhf_GBSetSelectPara()
* 功能描述：写FPGA的select命令参数寄存器。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1      lxc          创建
************************************************************************/

void uhf_GBSetSelectPara(WORD16 wRule,WORD16 wTarget, WORD16 wMemBank)
{
    WORD16 wData;
     /// 命令结构变化
     /// Bit15~Bit12  保留	Bit11~Bit10   规则	Bit9~Bit6   目标	Bit5~Bit0  存储区lxc
    wData = (((wRule & 0x3) << 10) |( (wTarget & 0xF) << 6) | ((wMemBank & 0x3F) << 0));
    uhfDevPrint("wRule %d, wTarget %d wMemBank %d wData:0x%x\r\n",
                        wRule, wTarget, wMemBank,wData);
    //// sort命令参数寄存器，地址：C001H  lxc
    wData=0x31;
    FpgaRegWrite(REG_GB_Sort_Para, wData);

} /* void FpgaTestRegWrite(WORD16 wData) */

/**********************************************************************
* 函数名称：void uhf_GBSetMacQueryPara(void)
* 功能描述：写FPGA的Query命令参数寄存器。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
//以前有个Q值，现在没有Q值这个参数了?
void uhf_GBSetMacQueryPara(BYTE ucM, BYTE ucReLinkRateDivisor)
{

   // 保留 Bit15～Bit14
   // 条件    Bit13～Bit10  => sel
   // 会话   Bit9～Bit8   => session
   // 目标     Bit7            => Target
   // TRext  Bit6                  => TRext
  //  反向链路速率因子    Bit5～Bit2   => ucDr
   // 编码选择Bit1～Bit0      lxc    =>  ucM
    WORD16 wData = 0;
    BYTE       ucTRext = 1;
    BYTE       ucTarget = 1;
    BYTE       ucSession = 0;
    BYTE       ucSel = 0;

    if (ucM == GB_QUERY_M_1) 
    {
        ucTRext = GB_QUERY_TREXT_USE_PILOT_TONE;
    }
    else
    {
        ucTRext = GB_QUERY_TREXT_NO_PILOT_TONE;
    }

        wData = ((ucSel & 0xF) << 10) /*sel*/                 //((0x0 & 0x3) << 4) 
            | ((ucSession & 0x3) << 8)/*session*/            //((0x0 & 0x3) << 6)
            | ((ucTarget & 0x1) << 7)/*Target*/               //EPC_QUERY_TARGET_B in EPC
            | ((ucTRext & 0x1) << 6)/*TRext*/ 
            | ((ucReLinkRateDivisor & 0xF) << 2)/*DR*/ // 反向链路速率因子
            | ((ucM & 0x3) << 0);/*M*/                           // 编码选择

    uhfDevPrint("GBSetMacQueryPara wData = 0x%x\r\n",wData);

    
    ///  Query命令参数寄存器，地址：C004H    lxc
    wData=0x4c;
    FpgaRegWrite(REG_GB_Query_Para, wData);

} /* void uhf_EpcSetMacQueryPara(void) */

/**********************************************************************
* 函数名称： uhf_GBStartProcAndTimer
* 功能描述： 触发Fpga开始GB流程，并启动超时定时器
* 输入参数： wCmdType  命令码
* 输出参数：无
* 返 回 值：    无
* 其它说明：触发的为FPGA一次执行完毕步等待RCP命令
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
*2014\2\16   RUP    lxc      创建
***********************************************************************/

void uhf_GBStartProcAndTimer(WORD16 wCmdType)
{
    uhf_startRcpTimer(FPGA_TIMEOUT_INTERVAL_IN_MS);
    StartFpgaProc(wCmdType);
}

/**********************************************************************
* 函数名称：uhf_GBSetMacAccessPara
* 功能描述：设置GB访问命令参数，密码访问时需要
* 输入参数：访问密钥
* 输出参数：无
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
/* need change */
void  uhf_GBSetMacAccessPara(WORD32 dwAccessPassword,BYTE ucMB,BYTE ucAccessType)
{
    WORD16 wData = 0;
    
    wData =(ucAccessType << 6) |( (ucMB & 0x3F) << 0) ;  
    FpgaRegWrite(REG_GB_Access_Membank, wData);

    /* wAccessPassHigh */
    FpgaRegWrite(REG_GB_Access_Password_H, (WORD16)((dwAccessPassword >> 16) & 0xffff));
    /* wAccessPassLow */
    FpgaRegWrite(REG_GB_Access_Password_L, (WORD16)(dwAccessPassword & 0xffff));

    RcpFpgaPrint("uhf: GB access password   = 0x%x \r\n", dwAccessPassword);
    
#if 0
    switch(ucAccessType){

        case ACCESS_READ:
            //读取访问口令，先发0110，再发0111
            //这里先考虑实现一个写入口令，需要与fpga  协商
            wData =((0b0111) << 10) | ((0b0110) << 6) |( (ucMB & 0x3F) << 0) ;
            break;

        case ACCESS_WRITE:
            //写入访问口令，先发1000，再发1001
            wData =((0b0111) << 10) | ((0b0110) << 6) |( (ucMB & 0x3F) << 0) ;
            break;
            
        case ACCESS_KILL:
            break;
            
        case ACCESS_LOCK;
            break;
            
        default:
            break;
    }

    FpgaRegWrite(REG_GB_Access_Membank, wData);
    /* wAccessPassHigh */
    FpgaRegWrite(REG_GB_Access_Password_H, (WORD16)((dwAccessPassword >> 16) & 0xffff));
    /* wAccessPassLow */
    FpgaRegWrite(REG_GB_Access_Password_L, (WORD16)(dwAccessPassword & 0xffff));
    RcpFpgaPrint("uhf: access password   = 0x%x \r\n", dwAccessPassword);
#endif
}

/**********************************************************************
* 函数名称：void SetGBReadPara(BYTE ucMemBank, WORD16 wAddr, WORD16 wWordCount)
* 功能描述：设置fpga读参数
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
void uhf_GBSetMacReadPara(BYTE ucMemBank, WORD16 wAddr, WORD16 wWordCount)
{
    /* read命令MemBank寄存器 */
    FpgaRegWrite(REG_GB_Read_Membank, (WORD16)(ucMemBank & 0x3));
    RcpFpgaPrint("www ptFpgaGBRead->wMemBank:    0x%04x \r\n", ucMemBank);

    /* read命令地址寄存器 */    /* 注意需要扩展EBV */
    FpgaRegWrite(REG_GB_Read_Addr, (wAddr & 0x7f));
    RcpFpgaPrint("www ptFpgaGBRead->wWordPointer: 0x%04x \r\n", wAddr);

    /* read命令读字个数寄存器*/
    FpgaRegWrite(REG_GB_Read_WordCount, wWordCount);
    RcpFpgaPrint("www ptFpgaGBRead->wReadWordsLen: 0x%04x \r\n", wWordCount);

} /* static int uhf_GBSetMacReadPara(T_FpgaGBRead *ptFpgaGBRead) */

/**********************************************************************
* 函数名称：void uhf_EpcSetMacWritePara(WORD16 wMemBank,WORD16 wAddr,
                                                                          WORD16 wWrWordLen,BYTE *ucdata)
* 功能描述：
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
void uhf_GBSetMacWritePara(WORD16 wMemBank, WORD16 wAddr, WORD16 wWrWordLen, BYTE *ucdata)
{
    WORD16 wIndex = 0;
    /* Write命令MemBank寄存器 */
    FpgaRegWrite(REG_GB_Write_Membank, (WORD16)(wMemBank & 0x3));
    RcpFpgaPrint("MemBank %d", wMemBank);

    /* Write命令地址寄存器 */
    FpgaRegWrite(REG_GB_Write_Addr, (wAddr & 0x7f));
    RcpFpgaPrint("WordPointer  %d", wAddr);

    /* Write命令读字个数寄存器 */
    FpgaRegWrite(REG_GB_Write_WordCount, wWrWordLen);
    RcpFpgaPrint("WriteWordsLen  %d \r\nWrite Data", wWrWordLen);

    /*根据FPGA的需求，不同的写长度写重试次数不同，提高写入的成功率*/
    SetGBWrtRtyTime(wWrWordLen);

    /*以下设置FPGA
    的控制超时时间*/
    //FpgaRegWrite(G2_write_rcv_delay_val_h, 0x0007);
    //FpgaRegWrite(G2_write_rcv_delay_val_l, 0x6590);

    /* write命令数据寄存器 */
    for (wIndex = 0; wIndex < wWrWordLen; wIndex++)
    {
        FpgaRegWrite(REG_GB_BlockWrite_Data_Start + wIndex,
                     ((((WORD16)ucdata[2 * wIndex]) << 8) | ((WORD16)ucdata[2 * wIndex + 1])));
        RcpFpgaPrint("%04x",
                     ((((WORD16)ucdata[2 * wIndex]) << 8) | ((WORD16)ucdata[2 * wIndex + 1])));
    }

    RcpFpgaPrint("\r\n");
} /* static int uhf_EpcSetMacWritePara(T_FpgaEpcWrite *ptFpgaEpcWrite) */

/**********************************************************************
* 函数名称：uhf_GBSetMacReadLock
* 功能描述：
* 输入参数：
                                1 代表锁定
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/28    V0.0.1          lxc        创建
************************************************************************/
void uhf_GBSetMacLockPara(BYTE ucDataArea,BYTE ucAreaCfg, BYTE ucAreaAction, BYTE ucSecAction )
{
    WORD16 wData = 0;

    if (0 == ucAreaCfg) //配置 存储区
        wData = ((ucAreaAction << 8) & 0x3) | ((ucAreaCfg << 6) & 0x3) | ((ucDataArea << 0) & 0x3F);
    else // 配置安全区
        wData = ((ucSecAction << 8) & 0x3) | ((ucAreaCfg << 6) & 0x3) | ((ucDataArea << 0) & 0x3F);
    /* payload_mask */
    FpgaRegWrite(REG_GB_Lock_Para, wData);
    RcpFpgaPrint("REG_GB_Lock_Para   = 0x%04x \r\n", wData);
}

/**********************************************************************
* 函数名称：void uhf_GBSetMacErasePara
* 功能描述：设置擦写参数
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
void uhf_GBSetMacErasePara(WORD16 wMemBank, WORD16 wAddr, WORD16 wErWordLen)
{
    /* Erase命令MemBank寄存器 */
    FpgaRegWrite(REG_GB_Erase_Membank, (WORD16)(wMemBank & 0x3));
    RcpFpgaPrint("MemBank %d", wMemBank);

    /* Erase命令地址寄存器 */
    FpgaRegWrite(REG_GB_Erase_Membank, (wAddr & 0x7f));
    RcpFpgaPrint("WordPointer  %d", wAddr);

    /* Erase命令字个数寄存器 */
    FpgaRegWrite(REG_GB_Erase_WordCount, wErWordLen);
    RcpFpgaPrint("EraseWordsLen  %d \r\nWrite Data", wErWordLen);

    /*根据FPGA的需求，不同的写长度写重试次数不同，提高写入的成功率*/
    //SetGBWrtRtyTime(wErWordLen);

    RcpFpgaPrint("\r\n");
} /* static int uhf_EpcSetMacWritePara(T_FpgaEpcWrite *ptFpgaEpcWrite) */

/**********************************************************************
* 函数名称：uhf_GBSetMacKillPara
* 功能描述：设置GB杀死密码杀死时需要
* 输入参数：杀死密钥
* 输出参数： 无
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
/// FIX ME !! fpga 还没有给出kill命令的寄存器地址
void uhf_GBSetMacKillPara(WORD32 dwKillPassword)
{

    RcpFpgaPrint("UHF: wKillPassWord = 0x%04x \n", dwKillPassword);
    /* wKillPassHigh */
    FpgaRegWrite(REG_GB_Kill_Password_H, (WORD16)((dwKillPassword >> 16) & 0xffff));

    /* wKillPassLow */
    FpgaRegWrite(REG_GB_Kill_Password_L, (WORD16)(dwKillPassword & 0xffff));


    FpgaRegWrite(REG_GB_Kill_RFU, 0x0000);

}


/**********************************************************************
* 函数名称：StartFpgaProcessIsoCmd
* 功能描述： 写入fpga中清点命令的参数
* 输出参数： 无
* 返 回 值：     无
* 其它说明：启动FPGA开始处理ISO协议流程
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
static void StartFpgaProcessIsoCmd(void)
{
    FpgaRegWrite(REG_CPU_CMD_Trig, 0x00);
    FpgaRegWrite(REG_CPU_CMD_Trig, 0x01);
    FpgaRegWrite(REG_CPU_CMD_Trig, 0x00);
}

/**********************************************************************
* 函数名称：uhf_IsoStartProcAndTimer
* 功能描述： 触发fpga流程同时启动定时器
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
void uhf_IsoStartProcAndTimer(void)
{

    StartFpgaProcessIsoCmd();
#if FPGA_SWTICH
    usp_drv_fpga_int_enable();
#endif
    uhf_startRcpTimer(FPGA_TIMEOUT_INTERVAL_IN_MS);
}


/**********************************************************************
* 函数名称：uhf_TxSet
* 功能描述：数载板这边的信号发送开始开关
* 输出参数： 无
* 返 回 值：     无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* -----------------------------------------------
* 2010/11/26           V04.00.00           zdx                   创建
***********************************************************************/
void uhf_TxSet(WORD16 wFpgaTxAction)
{

    if (wFpgaTxAction != FpgaRegRead(REG_RF_TX_Ctrl))
    {
        FpgaRegWrite(REG_RF_TX_Ctrl, wFpgaTxAction);
    }

} /* WORD32 usp_uhf_rf_txSet(WORD32 dwRfTxAction) */

/**********************************************************************
* 函数名称：void uhf_StopTx(void)
* 功能描述：空中接口协议流程结束。
* 访问的表：无
* 修改的表：无
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
************************************************************************/
#define UHF_STOP_TX_WAIT_TIME  (50)
void uhf_StopTx(void)
{
    /* 关闭射频功率发送 */
    uhf_TxSet(STOP_FPGA_RF_TX);
    /*此处必须在关闭前向后，延时，然后才能将K0的值
          设置为最小，否则会导致频谱占用带宽变大，影响其他
          阅读器*/
    //USP_OSS_VOS_SLEEP_USEC(UHF_STOP_TX_WAIT_TIME);
#if (!USP_IS_DISTRIBUTED)
    /*在分布式系统中不进行此个优化*/
    uhfRf_setPowerToZero();
   
#endif

} /* void uhf_StopTx(void) */


#endif


/**************************************************** file end ********************************************************************/

