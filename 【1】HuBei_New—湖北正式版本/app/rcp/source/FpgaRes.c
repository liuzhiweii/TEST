/*********************************************************************
* 版权所有 (C)2010, 深圳市中兴通讯股份有限公司。
*
* 文件名称： EPC.c
* 文件标识：
* 内容摘要： EPC协议相关的清点读写锁等操作的实现函数
* 其它说明： 提供接口给RCP.c调用
* 当前版本： V04.00.00
* 作    者：        zdx
* 完成日期： 2010年12月2日
*
* 修改记录1：
*    修改日期： 2010/12/2
*    版 本 号：
*    修 改 人：     zdx
*    修改内容： 创建
* 修改记录2：…
**********************************************************************/
#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include "usp_uhf_cfg.h"
#include "uhfFpgaRegDef.h"
#include "usp_uhf_epc.h"
#include "usp_uhf_iso6b.h"
#include "usp_uhf_gb.h"
#include "usp_uhf_err.h"
#include "uhf.h"
#include "uhf_trace.h"
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf.h"
#include "ISO6B.h"
#include "EPC.h"
#include "GB.h"
#include "uhf_epc.h"
#include "uhf_iso6b.h"
#include "uhf_gb.h"
//#include "uhf_time.h"



/**********************************************************
   *                       常量定义                                                               *
**********************************************************/

/**********************************************************
   *                       文件内部使用的宏                                      *
**********************************************************/

/* FPGA的EPC frame struct */
#define FPGA_FRAME_LEN         (0)
#define FPGA_FRAME_CMD_TYPE    (1)
#define FPGA_FRAME_FLAG        (2)
#define FPGA_FRAME_GEN2_PC     (3)
#define FPGA_FRAME_GEN2_EPC    (4)
// GB frame struct
#define FPGA_GB_FRAME_LEN         (1)
#define FPGA_GB_FRAME_CMD_TYPE    (1)
#define FPGA_GB_FRAME_FLAG        (3)
#define FPGA_GB_FRAME_PC_LEN      (4)
#define FPGA_GB_FRAME_GEN2_CODE  (4)
#define FPGA_GB_FRAME_ERROR_STEP  (5)
#define FPGA_GB_FRAME_SELF_ERROR_CODE (6)
#define FPGA_GB_FRAME_TAG_ERROR_CODE  (7)

#define FPGA_GB_FRAME_READ_DATA_LEN  (5)
#define FPGA_GB_FRAME_WRITE_DATA_LEN (5)

#define FPGA_FRAME_INVENTORY_HEAD_LENGTH              (4)
#define FPGA_FRAME_INVENTORY_HEAD_LENGTH_RSSI    (5)
/* FPGA错误阶段： */
#define FPGA_ERR_STEP_ACK        4   /* ：ACK命令阶段      */
#define FPGA_ERR_STEP_REQHANDLE  6   /* ：REQ handle命令阶段 */
#define FPGA_ERR_STEP_REQRN16    7   /* ：REQRN16命令阶段 */
#define FPGA_ERR_STEP_ACCESS     8   /* ：ACCESS命令阶段  */
#define FPGA_ERR_STEP_READ       9   /* ：读命令阶段       */
#define FPGA_ERR_STEP_WRITE     10   /* ：写命令阶段       */
#define FPGA_ERR_STEP_KILL      11   /* : KILL命令阶段    */
#define FPGA_ERR_STEP_LOCK      12   /* ：LOCK命令阶段    */

/* FPGA自定义错误码：
Bit5 EPC err	Bit4 handel error	Bit3 tag error	Bit2 crc error	Bit1 Collision	Bit0 Timeout
*/
#define FPGA_SELF_ERRCODE_TIMEOUT         (0x01)   /* ：超时，无信号     */
#define FPGA_SELF_ERRCODE_COLLISION       (0x02)   /* ：碰撞             */
#define FPGA_SELF_ERRCODE_CRC_ERROR       (0x04)   /* ：CRC校验错        */
#define FPGA_SELF_ERRCODE_TAG_ERROR       (0x08)   /* ：标签返回错误码   */
#define FPGA_SELF_ERRCODE_HANDEL_MISMATCH (0x10)   /* ：HANDEL不匹配    */
#define FPGA_SELF_ERRCODE_EPC_ERR         (0x20)   /* ：EPC代码不匹配   */
#define FPGA_SELF_ERRCODE_ACCESS_ERR      (0x40)   /*EPC Read Write Error*/

/**********************************************************
   *                      外部变量                                                    *
**********************************************************/
extern WORD16        g_awFpgaReadBuf[FPGA_BUF_BYTE_SIZE / 2];

/**********************************************************
   *                       文件内部使用的数据类型                  *
**********************************************************/
extern T_EpcCtl   g_tEpcCtrl;              /* GEN2协议控制数据结构 */
extern T_ISO6BCtl g_tISO6BCtrl;
extern T_GBCtl    g_tGBCtrl;
extern T_UhfCtrl  g_tUhfCtrl;

inline WORD16 GetCollisionCount(void)
{
    return FpgaRegRead(0x29);
}

inline WORD16 GetNoReplyCount(void)
{
    return FpgaRegRead(0x2a);
}

inline WORD16 GetWriteSuccessLen()
{
    return (FpgaRegRead(0x6f) & 0xff);
}
/**********************************************************
   *                      局部函数声明                                                    *
**********************************************************/
static WORD32 TransferTagErrorCode(WORD16 wTagErrCode);
extern WORD32 uhf_ISO6BRecordValidTag(WORD16 wRSSI, BYTE *pucUID);


static WORD32 TranferErrCode(WORD16 wSelfDefErrCode, WORD16 wTagErrCode)
{
    /* FPGA自定义错误码：
         Bit5 EPC err	Bit4 handel error	Bit3 tag error	Bit2 crc error	Bit1 Collision	Bit0 Timeout
     */
    WORD32 dwErrorCode = USP_UHF_EPC_FPGA_TIMEOUT;

    uhfDevPrint("Error Code %x %x \r\n", wSelfDefErrCode, wTagErrCode);

    if (wSelfDefErrCode & FPGA_SELF_ERRCODE_CRC_ERROR)
    {
        dwErrorCode = USP_UHF_EPC_CRC_ERROR;
        uhfDevPrint("Crc error \r\n");

    }
    else if (wSelfDefErrCode & FPGA_SELF_ERRCODE_TAG_ERROR)
    {
        uhfDevPrint("Tag reply selfdef error \r\n");
        dwErrorCode = TransferTagErrorCode(wTagErrCode);

    }
    else if (wSelfDefErrCode & FPGA_SELF_ERRCODE_HANDEL_MISMATCH)
    {
        dwErrorCode = USP_UHF_EPC_HANDLE_UNMATCH;
        uhfDevPrint("Handle unmatch \r\n");

    }
    else if (wSelfDefErrCode & FPGA_SELF_ERRCODE_EPC_ERR)
    {
        dwErrorCode = USP_UHF_EPC_PREAMBLE_NOT_MATCH;
        uhfDevPrint("UHF: EPC_PREAMBLE_NOT_MATCH \r\n");

    }
    else if (wSelfDefErrCode & FPGA_SELF_ERRCODE_ACCESS_ERR)
    {
        dwErrorCode = USP_UHF_EPC_ACCESS_NOT_PERMIT;
        uhfDevPrint("UHF: Access PassWord Error\r\n");
    }
    else if (wSelfDefErrCode & FPGA_SELF_ERRCODE_TIMEOUT)
    {
        dwErrorCode = USP_UHF_EPC_FPGA_TIMEOUT;
        uhfDevPrint("Tag  no reply Fpga Timeout \r\n");
    }
    else if (wSelfDefErrCode & FPGA_SELF_ERRCODE_COLLISION)
    {
        dwErrorCode = USP_UHF_EPC_PREAMBLE_NOT_MATCH;
        uhfDevPrint("Collision \r\n");
    }
    else
    {
        dwErrorCode = USP_UHF_EPC_UNKNOW_ERROR;
        uhfDevPrint("UHF: FPGA EPC_UNKNOW_ERROR \r\n");
    }

    return dwErrorCode;

}

static WORD32 TransferTagErrorCode(WORD16 wTagErrCode)
{

    WORD32 dwErrCode = USP_UHF_EPC_TAG_UKNOWN_ERROR;

    /* Tag error codes */
    if (wTagErrCode == 0x00)
    {
        uhfDevPrint("Catch-all for errors not covered by other codes \r\n");
        dwErrCode = USP_UHF_EPC_TAG_UKNOWN_ERROR;
    }
    else if (wTagErrCode == 0x03)
    {

        uhfDevPrint("The specified memory location does not exist or the PC value is not supported by the Tag \r\n");
        dwErrCode = USP_UHF_EPC_TAG_MEM_LOCATION_NOTEXIST;

    }
    else if (wTagErrCode == 0x04)
    {
        uhfDevPrint("Error Description = The specified memory location is locked and/or per-malocked and is either not writeable or not readable. \r\n");
        dwErrCode = USP_UHF_EPC_ACCESS_NOT_PERMIT;

    }
    else if (wTagErrCode == 0x0B)
    {
        uhfDevPrint("The Tag has insufficient power to perform the mem-ory-write operation \r\n");
        dwErrCode = USP_UHF_EPC_TAG_POWER_NOT_ENOUGH;
    }
    else if (wTagErrCode == 0x0F)
    {
        uhfDevPrint("Error Description = The Tag does not support error-specific codes \r\n");
        dwErrCode = USP_UHF_EPC_TAG_UKNOWN_ERROR;
    }
    else
    {
        dwErrCode = USP_UHF_EPC_TAG_UKNOWN_ERROR;
        uhfDevPrint("Error Description = Unkonow error\r\n");
    }

    return dwErrCode;

}

/**********************************************************************
* 函数名称：WORD32  uhf_Epc_Invetory_Resp(void)
* 功能描述：EPC清点标签响应数据处理。
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
   2010/11/23    V0.0.2      zdx          修改
************************************************************************/
WORD32 uhf_Epc_Invetory_Resp(T_USPUHFEpcInventoryRes *ptEpcInventoryResp)
{
    WORD16 wIndex = 0;
    WORD32 dwRetVal = MAC_INVENTORY_PROCESS_FINISH;
    WORD32 dwEPC_WordLength = 0;
    WORD16 wFrameLen = 0;
    WORD32 dwWordIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wErrorCode = 0;
    WORD16 wTraceLen = 0;
    dwRetVal = ReadLowLevelFrame(&wReadLen);
    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /*全局变量记录清点时标签的RSSI,当RDP调用读操作时返回*/
    g_tEpcCtrl.wLastTagRssi = 0xffff;

    /* 清点标签响应帧数据结构（成功）：
            帧长度/命令类型/成功/PC/EPC
        标签响应帧数据结构（标签访问结束）：
            帧长度/命令类型/结束                                   */

    wFrameLen = g_awFpgaReadBuf[FPGA_FRAME_LEN];

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("UHF: Invetory_Resp(), FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptEpcInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptEpcInventoryResp->wPC = g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC];
        ptEpcInventoryResp->wQueryCollisionCount = GetCollisionCount();
        ptEpcInventoryResp->wQueryNoReplyCount = GetNoReplyCount();
        ptEpcInventoryResp->wResult = USP_SUCCESS;
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC ] >> 11) & 0x1F; //高5bit表示epc长度

        if ((dwEPC_WordLength > EPC_MAX_LENGTH) || (dwEPC_WordLength > wFrameLen))
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_Inventory_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Inventory_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        UHFAlertPrint("UHF: Epc Tag data: 0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            UHFAlertPrint("%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        UHFAlertPrint("\r\n");

        ptEpcInventoryResp->wRssi = g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + dwEPC_WordLength];
        UHFAlertPrint("RSSI is %x\r\n", ptEpcInventoryResp->wRssi);
        /*全局变量记录清点时标签的RSSI,当RDP调用读操作时返回*/
        g_tEpcCtrl.wLastTagRssi = ptEpcInventoryResp->wRssi;


        if (g_tUhfCtrl.atRfAntCfg[g_tUhfCtrl.wAntIndex].tEPCReadRssiCfg.ucTurnOnFilter == 1)
        {
            if ((ptEpcInventoryResp->wRssi) <
                g_tUhfCtrl.atRfAntCfg[g_tUhfCtrl.wAntIndex].tEPCReadRssiCfg.wRSSIThreshHold)
            {
                UHFAlertPrint("Throw a tag!\r\n");
                ptEpcInventoryResp->wResult = USP_UHF_EPC_RSSI_NOT_ENOUGH;
            }
        }

        ptEpcInventoryResp->tTagId.wTagWordLen = dwEPC_WordLength;
        mem_words_cpy(ptEpcInventoryResp->tTagId.aucTagData, &g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC], dwEPC_WordLength);

        /* 如果清点没有完成，则继续接收标签清点响应数据。*/
        uhfDevPrint("UHF: continue to read next frame \r\n");
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;

    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        /* 清点结束 */
        uhfDevPrint("UHF: inventory has finished \r\n");
#if 0

        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_Inventory_Finish_RESP_Trace);
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Inventory_Finish_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        ptEpcInventoryResp->wRssi = 0;
        ptEpcInventoryResp->wResult = USP_SUCCESS;
        ptEpcInventoryResp->wInventoryFinish = INVENTORY_HAS_FINISH;
        ptEpcInventoryResp->tTagId.wTagWordLen = 0;
        dwRetVal = MAC_INVENTORY_PROCESS_FINISH;
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }
#if 0

        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_Inventory_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Inventory_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength;
        /* 错误阶段 */
        UHFErrorPrint("UHF: read tag wErrorStep 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);
        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        wErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);
        UHFErrorPrint("UHF:Inventory Error happens Code %d\r\n", wErrorCode);
        ptEpcInventoryResp->wRssi = 0;
        ptEpcInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptEpcInventoryResp->tTagId.wTagWordLen = 0;
        ptEpcInventoryResp->wResult = wErrorCode;
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;
    }
    else
    {
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = FPGA_ERROR_TRACE_LEN * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_FPGA_UNKNOW_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        UHFWarningPrint("UHF: uhf_Epc_Invetory_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);
        uhfDevPrint("UHF: frame data for analize: ");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x  ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");

        ptEpcInventoryResp->wRssi = 0;
        ptEpcInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptEpcInventoryResp->tTagId.wTagWordLen = 0;
        ptEpcInventoryResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;
    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Invetory_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_Epc_Read_Resp(void)
* 功能描述：EPC读标签响应数据处理。
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
WORD32 uhf_Epc_Read_Resp(T_USPUHFEpcReadRes *ptEPCReadResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength;
    WORD32 dwWordIndex;
    WORD16 wReadWordCount;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wErrorCode = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
       读标签响应帧数据结构（成功）：
       帧长度命令类型成功 PC EPC   读数据长度   标签数据

      读标签响应帧数据结构（失败）：
      帧长度    命令类型  失败  PC  EPC 错误阶段 自定义错误码  标签返回的错误码
     */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {

        uhfDevPrint("UHF: read tag data success \r\n");
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        /* the tag epc code */
        uhfDevPrint("UHF: Epc ID: 0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");

        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength;

        /* tag data word length that is readed */
        wReadWordCount = g_awFpgaReadBuf[dwWordIndex];

        if (wReadWordCount > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, wReadWordCount, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        uhfDevPrint("read success length is %d\r\n", wReadWordCount);
        ptEPCReadResp->wResult = USP_SUCCESS;
        ptEPCReadResp->wResultLength = g_tEpcCtrl.tEpcRead.wReadWordsLen;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_READ_RESP_Trace) + (wReadWordCount + dwEPC_WordLength) * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Read_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        /*指向读到的标签数据*/
        dwWordIndex++;
        /* 复制读到的标签内存数据 */
        mem_words_cpy(ptEPCReadResp->awReadData, &g_awFpgaReadBuf[dwWordIndex], wReadWordCount);

        uhfDevPrint("UHF: read tag data:0x");

        for (wIndex = 0; wIndex < wReadWordCount; wIndex++)
        {
            uhfDevPrint("%04x ", ptEPCReadResp->awReadData[wIndex]);
        }

        uhfDevPrint("\r\n");

    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 读标签失败 */
        UHFErrorPrint("UHF: read tag data fail \r\n");

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_READ_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Read_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength;
        /* 错误阶段 */
        UHFErrorPrint("UHF: read tag wErrorStep 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);
        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        wErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptEPCReadResp->wResult = wErrorCode;
        ptEPCReadResp->wResultLength = 0;

    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("UHF: cannot invent tag when read tag\r\n");

        ptEPCReadResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
        ptEPCReadResp->wResultLength = 0;
    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: uhf_Epc_Read_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);
        uhfDevPrint("UHF: frame data for analize: 0x");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");

        ptEPCReadResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        ptEPCReadResp->wResultLength = 0;

    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Read_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_Epc_Write_Resp(void)
* 功能描述：EPC写标签响应数据处理。
* 输入参数：
* 输出参数：T_EPC_WriteResponse *ptEPCWriteResp   写入结果
* 返 回 值： WORD32
                              0：    成功
                             其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2006/9/16    V0.0.1       ft          创建
   2010/10/24  V0.0.3       zdx      修改
************************************************************************/
WORD32 uhf_Epc_Write_Resp(T_USPUHFEpcWriteRes *ptEPCWriteResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex;
    WORD16 wWriteWordCount;
    WORD16 wErrorStep;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;


    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /*
        写标签响应帧数据结构（成功）：
        帧长度   命令类型    成功    PC   EPC   写数据长度

        写标签响应帧数据结构（失败）：
        帧长度   命令类型    失败     PC    EPC   错误阶段   自定义错误码      标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {

        uhfDevPrint("UHF: Epc write success \r\n");

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;               /* the tag epc code */

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        uhfDevPrint("UHF: Epc ID: ");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("0x%04x  ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");

        ptEPCWriteResp->wResult = USP_SUCCESS;

        if (g_tEpcCtrl.tEpcWrite.wIsBlockWrite == EPC_BLOCK_WRITE)
        {
            ptEPCWriteResp->wResultLength =
                g_tEpcCtrl.tEpcWrite.wWriteWordsLen;
        }
        else
        {
            dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength;

            wWriteWordCount = g_awFpgaReadBuf[dwWordIndex];
            uhfDevPrint("UHF: wWriteWordCount = %d  \r\n", wWriteWordCount);

            if (wWriteWordCount > EPC_MAX_LENGTH)
            {
                LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, wWriteWordCount, 0);
                return USP_UHF_FPGA_UNKNOW_FRAME;
            }

            ptEPCWriteResp->wResultLength = wWriteWordCount;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_WRITE_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Write_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {

        uhfDevPrint("EPC Write Error\r\n");
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        /* the tag epc code */
        uhfDevPrint("UHF: Epc ID:0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: write tag wErrorStep= 0x%04x \r\n", wErrorStep);
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];

        /* 自定义错误码 */
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];

        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);
        ptEPCWriteResp->wResult = (WORD16)dwErrorCode;

        if (g_tEpcCtrl.tEpcWrite.wIsBlockWrite == EPC_WORD_WRITE)
        {
            ptEPCWriteResp->wResultLength = GetWriteSuccessLen();
            uhfDevPrint("Has Write %d Words\r\n", ptEPCWriteResp->wResultLength);
        }
        else
        {
            ptEPCWriteResp->wResultLength = 0;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_WRITE_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Write_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("UHF: cannot invent tag when read tag\r\n");

        ptEPCWriteResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
        ptEPCWriteResp->wResultLength = 0;

    }
    else
    {

        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: uhf_Epc_Write_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptEPCWriteResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        ptEPCWriteResp->wResultLength = 0;
    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Write_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_Epc_Write_Resp(void)
* 功能描述：EPC写标签响应数据处理。
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
WORD32 uhf_Epc_Lock_Resp(T_USPUHFEpcLockRes *ptEPCLockResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex;
    WORD16 wErrorStep;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
        LOCK标签数据结构：
         帧长度    命令类型     成功    PC    EPC

        LOCK标签数据结构：
          帧长度  命令类型     失败   PC   EPC   错误阶段  自定义错误码   标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        /* record finish time */
        uhfDevPrint("UHF: Lock success \r\n");

        /* 生成写标签响应消息，发送到RDP。*/
        ptEPCLockResp->wResult = USP_SUCCESS;

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;               /* the tag epc code */

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: Epc ID: ");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_LOCK_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Lock_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* Lock标签失败 */
        UHFErrorPrint("UHF: Lock fail \r\n");
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: Epc ID:0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: write tag wErrorStep = 0x%04x \r\n", wErrorStep);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptEPCLockResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_LOCK_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Lock_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("cannot invent tag when read tag\r\n");
        ptEPCLockResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
    }
    else
    {

        //FPGATrace(wTraceLen);
        UHFWarningPrint("uhf_Epc_Lock_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("frame data for analize: ");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("%04x  ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptEPCLockResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Lock_Resp(void) */

WORD32 uhf_Epc_Kill_Resp(T_USPUHFEpcKillRes *ptEPCKillResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength = 0;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
        LOCK标签数据结构：
         帧长度命令类型   成功   PC   EPC

        LOCK标签数据结构：
         帧长度     命令类型     失败   PC   EPC     错误阶段    自定义错误码    标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        uhfDevPrint("UHF: Kill success \r\n");

        ptEPCKillResp->wResult = USP_SUCCESS;
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;               /* the tag epc code */

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: Epc ID: ");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x  ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_KILL_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Kill_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* Kill标签失败 */
        UHFErrorPrint("UHF: Kill tag failed \r\n");

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: Epc ID: ");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        UHFErrorPrint("UHF: Kill tag wErrorStep = 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptEPCKillResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_KILL_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Kill_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("cannot invent tag when read tag\r\n");
        ptEPCKillResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: uhf_Epc_Kill_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptEPCKillResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Kill_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  Fpga_uhf_Epc_Block_Lock_Resp(void)
* 功能描述：EPC块锁标签响应数据处理。
* 输入参数：
* 输出参数：
* 返 回 值：
            WORD32
                      0：    成功
                   其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010/1/26    V0.0.1       chenjie          创建
************************************************************************/
WORD32 uhf_Epc_BlockLock_Resp(T_USPUHFEpcBlockLockRes *ptEPCBlockLockResp)
{

    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength = 0;
    WORD32 dwWordIndex = 0;
    WORD32 dwErrorCode = 0;
    WORD16 wCmdType = 0;
    WORD16 wBlockLockWordCount = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (0 != dwRetVal)
    {
        return dwRetVal;
    }

    /*
        块锁定（读状态，READ/LOCK=0时）
        blkpermaLOCK标签数据结构：帧长度/命令类型/成功/ PC/EPC/读锁定的数据长度/permallockbits
        blkpermaLOCK标签数据结构：帧长度/命令类型/失败/PC/EPC/错误阶段/自定义错误码/标签返回的错误码
        blkpermaLOCK标签数据结构：帧长度/命令类型/结束

        块锁定（锁定状态，READ/LOCK=1时）
        blkpermaLOCK标签数据结构：帧长度/命令类型/成功/ PC/EPC
        blkpermaLOCK标签数据结构：帧长度/命令类型/失败/PC/EPC/错误阶段/自定义错误码/标签返回的错误码
        blkpermaLOCK标签数据结构：帧长度/命令类型/结束

    */
    wCmdType = g_awFpgaReadBuf[FPGA_FRAME_CMD_TYPE];

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        uhfDevPrint("EPC BlockLock Success\r\n");
        ptEPCBlockLockResp->wResult = USP_SUCCESS;

        if (wCmdType == FPGA_BLKPERMALOCK_CMD_MSG)
        {
            /*响应的是块锁定的消息命令*/
            ptEPCBlockLockResp->ucReadLock = 1;
        }
        else if (wCmdType == FPGA_BLKPERMALOCK_QUERY_MSG)
        {
            /*响应的是块查询的消息命令*/
            ptEPCBlockLockResp->ucReadLock = 0;
        }
        else
        {
            ptEPCBlockLockResp->ucReadLock = g_tEpcCtrl.tEpcBlockLock.ucReadLock;
            uhfDevPrint("UHF:IN block lock,fpga return a wrong cmd type\r\n");
        }

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;               /* the tag epc code */

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: Epc ID: 0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x  ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_BlkPermaLOCK_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_BlkPermaLock_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        if (ptEPCBlockLockResp->ucReadLock == 0)
        {
            /*如果是读锁定需要提取剩余的字节*/
            dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; //指向写数据长度
            wBlockLockWordCount = g_awFpgaReadBuf[dwWordIndex];

            if (wBlockLockWordCount > EPC_MAX_LENGTH)
            {
                LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
                return USP_UHF_FPGA_UNKNOW_FRAME;
            }

            dwWordIndex++;
            mem_words_cpy(ptEPCBlockLockResp->ucLockState,
                          (BYTE *)&g_awFpgaReadBuf[dwWordIndex],
                          wBlockLockWordCount * 2);
            ptEPCBlockLockResp->wLockStateLen = wBlockLockWordCount * 2;
            uhfDevPrint("UHF: ptBlockLockResponse->wLockStateLen = %d  \r\n",
                        ptEPCBlockLockResp->wLockStateLen);

            for (wIndex = 0; wIndex < ptEPCBlockLockResp->wLockStateLen; wIndex++)
            {
                uhfDevPrint("UHF:ptBlockLockResponse->ucLockState[%d] = %d\r\n", wIndex, ptEPCBlockLockResp->ucLockState[wIndex]);
            }
        }
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 块锁或者块锁查询标签失败 */
        uhfDevPrint("EPC BlockLock Error\r\n");
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: Epc ID: \r\n");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        UHFErrorPrint("UHF: BlockLock tag wErrorStep = 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptEPCBlockLockResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_BlkPermaLOCK_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_BlkPermaLock_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        UHFErrorPrint("UHF: cannot invent tag when write tag\r\n");
        ptEPCBlockLockResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
    }
    else
    {
        //FPGATrace(wTraceLen);
        uhfDevPrint("EPC BlockLock Error\r\n");
        UHFWarningPrint("UHF: Fpga_uhf_Epc_BlockLokc_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptEPCBlockLockResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;

    }

    return dwRetVal;
}


WORD32 uhf_Epc_ReadLock_Resp(T_USPUHFEpcReadLockRes *ptEPCReadLockResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength = 0;
    WORD32 dwWordIndex = 0;
    WORD32 dwErrorCode = 0;
    WORD16 wFrameLen = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (0 != dwRetVal)
    {
        return dwRetVal;
    }

    wFrameLen = g_awFpgaReadBuf[FPGA_FRAME_LEN];

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {

        ptEPCReadLockResp->wResult = USP_SUCCESS;

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;               /* the tag epc code */

        if ((dwEPC_WordLength > EPC_MAX_LENGTH) || (dwEPC_WordLength > wFrameLen))
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: Epc ID: 0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_BlkReadLOCK_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_BlkReadLock_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        uhfDevPrint("EPC ReadLock Success\r\n");

    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: Epc ID: \r\n");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        UHFErrorPrint("UHF: ReadLock tag wErrorStep = 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        /* 标签返回的错误码 */
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        /*在读保护操作中如果标签没有返回
                  则认为是密码下发错误*/
        /*用0密码对有密码的标签进行读保护操作，返回超时错误*/
        if (USP_UHF_EPC_FPGA_TIMEOUT == dwErrorCode)
        {
            uhfDevPrint("Access PassWord Error\r\n");
            dwErrorCode = USP_UHF_EPC_ACCESS_NOT_PERMIT;
        }

        ptEPCReadLockResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_BlkReadLOCK_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_BlkReadLock_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        uhfDevPrint("EPC ReadLock Error\r\n");
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        UHFErrorPrint("UHF: cannot invent tag when write tag\r\n");

        ptEPCReadLockResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: Fpga_uhf_Epc_AlienReadLock_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");

        ptEPCReadLockResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        uhfDevPrint("EPC ReadLock Error\r\n");
    }

    return dwRetVal;
}


WORD32 uhf_Epc_IPJQT_Resp(T_USPUHFEpcIPJQTRes *ptEPCIPJQtResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwEPC_WordLength = 0;
    WORD32 dwWordIndex = 0;
    WORD32 dwErrorCode = 0;
    WORD16 wFrameLen = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (0 != dwRetVal)
    {
        return dwRetVal;
    }

    wFrameLen = g_awFpgaReadBuf[FPGA_FRAME_LEN];

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {

        ptEPCIPJQtResp->wResult = USP_SUCCESS;

        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;               /* the tag epc code */

        if ((dwEPC_WordLength > EPC_MAX_LENGTH) || (dwEPC_WordLength > wFrameLen))
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: Epc ID: 0x");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        uhfDevPrint("\r\n");

        /*0是读   1是写*/
        if (EPC_IPJ_QT_READ == ptEPCIPJQtResp->wReadOrWrite)
        {
            dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength;
            uhfDevPrint("QT length %d\r\n", g_awFpgaReadBuf[dwWordIndex]);
            dwWordIndex++;

            ptEPCIPJQtResp->wDataProfile = ((g_awFpgaReadBuf[dwWordIndex] >> 14) & 0x1);
            ptEPCIPJQtResp->wAccessRange = g_awFpgaReadBuf[dwWordIndex] >> 15;
        }
        else
        {
            ptEPCIPJQtResp->wDataProfile = 0;
            ptEPCIPJQtResp->wAccessRange = 0;
        }
        
        uhfDevPrint("EPC IPJ qt Success\r\n");

    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 获得EPC长度 */
        dwEPC_WordLength = (g_awFpgaReadBuf[FPGA_FRAME_GEN2_PC] >> 11) & 0x1F;

        if (dwEPC_WordLength > EPC_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwEPC_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: Epc ID: \r\n");

        for (wIndex = 0; wIndex < dwEPC_WordLength; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[FPGA_FRAME_GEN2_EPC + wIndex]);
        }

        dwWordIndex = FPGA_FRAME_GEN2_EPC + dwEPC_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        UHFErrorPrint("UHF: ReadLock tag wErrorStep = 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        /* 标签返回的错误码 */
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        /*在读保护操作中如果标签没有返回
                  则认为是密码下发错误*/
        /*用0密码对有密码的标签进行读保护操作，返回超时错误*/
        if (USP_UHF_EPC_FPGA_TIMEOUT == dwErrorCode)
        {
            uhfDevPrint("Access PassWord Error\r\n");
            dwErrorCode = USP_UHF_EPC_ACCESS_NOT_PERMIT;
        }

        ptEPCIPJQtResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_BlkReadLOCK_Error_RESP_Trace) + dwEPC_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_BlkReadLock_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        uhfDevPrint("EPC ReadLock Error\r\n");
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        UHFErrorPrint("UHF: cannot invent tag when write tag\r\n");

        ptEPCIPJQtResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: Fpga_uhf_Epc_AlienReadLock_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");

        ptEPCIPJQtResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        uhfDevPrint("EPC IPJQT Error\r\n");
    }

    return dwRetVal;
}


/**********************************************************************
* 函数名称：WORD32 uhf_ISO6B_TransErrorCode(WORD16 wFPGAErrorCode)
* 功能描述：将FPGA返回的错误码转换为RCP错误码，发给RDP
* 输入参数：WORD16 wFPGAErrorCode FPGA错误码
* 输出参数：WORD32 RCP采用的错误码
* 返 回 值：
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010/11/26     V04.00.00       zdx         创建
************************************************************************/
static WORD32 uhf_ISO6B_TransErrorCode(WORD16 wFPGAErrorCode)
{
    WORD32 dwErrorCode = USP_UHF_ISO6B_RESULT_UNKNOW_ERROR;

    if (wFPGAErrorCode == FPGA_ISO6B_FRAME_RESULT_NO_SIGNAL)
    {
        dwErrorCode = USP_UHF_ISO6B_NO_SIGNAL;
    }
    else if (wFPGAErrorCode == FPGA_ISO6B_FRAME_RESULT_PREAMBLE_NOT_MATCH)
    {
        dwErrorCode = USP_UHF_ISO6B_PREAMBLE_NOT_MATCH;
    }
    else if (wFPGAErrorCode == FPGA_ISO6B_FRAME_RESULT_CRC_ERROR)
    {
        dwErrorCode = USP_UHF_ISO6B_RESULT_CRC_ERROR;

    }
    else if (wFPGAErrorCode == FPGA_ISO6B_FRAME_RESULT_TAG_ERROR)
    {
        dwErrorCode = USP_UHF_ISO6B_WRITE_AREA_LOCKED;

    }
    else
    {
        dwErrorCode = USP_UHF_ISO6B_RESULT_UNKNOW_ERROR;
    }

    uhfDevPrint("ISO6B Error %4x \r\n", dwErrorCode);
    return  dwErrorCode;
}

WORD32 uhf_ISO6B_Proc_OprtCmd_Rsp(BYTE ucCmd, WORD16 wStartAddr, BYTE ucLen,
                                  BYTE *aucOptBuf)
{
    WORD16 wMsgType;
    WORD16 wIndex;
    WORD16 wTraceLen = 0;
    WORD16 wIsoAccessErrorNo;
    WORD32 dwRetVal = USP_SUCCESS;
    WORD16 wAbandonLen;
    WORD16 wIsoLockQueryData;
    WORD16 wRealStartAddr;
    WORD16 wReadLen;

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return   dwRetVal;
    }

    /* 检查标签响应数据格式 */
    wMsgType = g_awFpgaReadBuf[FPGA_ISO6B_FRAME_MSG_TYPE] & 0x03;

    /* 返回非写结果 */
    if (FPGA_ISO6B_FRAME_CMD_TYPE_ACCESS_MSG == wMsgType)
    {
        wIsoAccessErrorNo = g_awFpgaReadBuf[FPGA_ISO6B_FRAME_RESULT] & 0xff;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_6B_Access_RESP_Trace);
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_6B_Acess_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        if (wIsoAccessErrorNo == FPGA_ISO6B_FRAME_RESULT_NO_EEROR)
        {
            UHFErrorPrint("UHF: ISO6B_OptCmd %x SUCCESS \r\n", ucCmd);

            switch (ucCmd)
            {
                case ISO6B_CMD_TYPE_WRITE_BYTE:
                    break;

                case ISO6B_CMD_TYPE_WRITE_4BYTE:
                    break;

                case ISO6B_CMD_TYPE_READ_VRBLBYTE:
                    memmove(aucOptBuf, &g_awFpgaReadBuf[FPGA_ISO6B_FRAME_TAG_DATA], ucLen);
                    break;

                case ISO6B_CMD_TYPE_READ_8BYTE:

                    if (wStartAddr > ISO_18000_6B_MAX_TAG_SIZE - 8)
                    {
                        wRealStartAddr = ISO_18000_6B_MAX_TAG_SIZE - 8;
                    }
                    else
                    {
                        wRealStartAddr = wStartAddr;
                    }

                    wAbandonLen = wStartAddr - wRealStartAddr;
                    memmove(aucOptBuf, &g_awFpgaReadBuf[FPGA_ISO6B_FRAME_TAG_DATA + wAbandonLen], ISO_180006B_READ_RESPONSE_BYTE_LEN - wAbandonLen);
                    break;

                case ISO6B_CMD_TYPE_LOCK:
                    break;

                case ISO6B_CMD_TYPE_LOCKQRY:
                    /* 拷贝标签字节锁状态 */
                    wIsoLockQueryData = (g_awFpgaReadBuf[FPGA_ISO6B_FRAME_TAG_DATA] & 0xff);

                    if ((wIsoLockQueryData == 0x00) || (wIsoLockQueryData == 0x01))
                    {
                        *aucOptBuf = ISO6B_BYTE_UNLOCKED;
                    }
                    else if ((wIsoLockQueryData == 0xFE) || (wIsoLockQueryData == 0xFF))
                    {
                        *aucOptBuf = ISO6B_BYTE_LOCKED;
                    }
                    else
                    {
                        /* 标签返回内容不符合协议*/
                        dwRetVal = USP_UHF_FPGA_UNKNOW_FRAME;
                    }

                    break;

                default:
                    break;
            }
        }
        else
        {
            UHFErrorPrint("UHF: ISO6B_OptCmd %x Fail \r\n", ucCmd);
            dwRetVal = uhf_ISO6B_TransErrorCode(wIsoAccessErrorNo);
        }

    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: Fpga_Iso_Invetory_Resp() , invalid g_awFpgaReadBuf[FPGA_ISO6B_FRAME_CMD_TYPE] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_ISO6B_FRAME_CMD_TYPE]);
        uhfDevPrint("UHF: frame data for analize: 0x");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("%04x  \r\n", g_awFpgaReadBuf[wIndex]);
        }

        dwRetVal = USP_UHF_FPGA_UNKNOW_FRAME;
    }

    return dwRetVal;

}
/**********************************************************************
* 函数名称：WORD32 uhf_ISO6B_Proc_Invnt_Resp(void)
* 功能描述：接收并解析fpga返回数据，并将结果放入到ISO6B缓存中
* 输入参数：无
* 输出参数：无
* 返 回 值：    WORD32 : USP_SUCCESS 成功
                                 其余:错误码
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2010/11/26      V04.00.00       zdx         创建
************************************************************************/
WORD32 uhf_ISO6B_Proc_Invnt_Resp(void)
{
    WORD32 dwRetVal = MAC_INVENTORY_PROCESS_FINISH;
    WORD16 wFrameLen = 0;
    WORD16 wReadLen = 0;
    WORD16 wWord_HasRead = 0;
    WORD16 wIndex = 0;
    BYTE   *pucUID = NULL;
    BYTE   *pucDRCmdData = NULL;
    WORD16 wRSSI = 0;
    WORD16 wMsgType = 0;
    WORD16 wTraceLen = 0;


    for (; ;)
    {
        dwRetVal = ReadLowLevelFrame(&wReadLen);

        if (USP_SUCCESS != dwRetVal)
        {
            return   dwRetVal;
        }

        wWord_HasRead = 0;
        /*收到一次FPGA的返回后，重新设置超时定时器*/
        uhf_startRcpTimer(FPGA_TIMEOUT_INTERVAL_IN_MS);

        while (wWord_HasRead < wReadLen)
        {
            wFrameLen = g_awFpgaReadBuf[FPGA_ISO6B_FRAME_LEN + wWord_HasRead];
            wMsgType = g_awFpgaReadBuf[FPGA_ISO6B_FRAME_MSG_TYPE] & 0x03;

            if (wMsgType == FPGA_ISO6B_FRAME_CMD_TYPE_INVENT_MSG)
            {
                wRSSI = g_awFpgaReadBuf[FPGA_ISO6B_INVENT_FRAME_RSSI + wWord_HasRead];
                pucUID = (BYTE *)&g_awFpgaReadBuf[FPGA_ISO6B_INVENT_FRAME_UID + wWord_HasRead];
                pucDRCmdData = (BYTE *)&g_awFpgaReadBuf[FPGA_ISO6B_INVENT_FRAME_DATAREAD_DATA + wWord_HasRead];
#if 0
                if (usp_cli_isTraceByTno(USP_FPGA_TNO))
                {
                    wTraceLen = sizeof(T_6B_Inventory_RESP_Trace);
                    uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_6B_Inventory_RESP, wTraceLen, &g_awFpgaReadBuf[wWord_HasRead]);
                }
#endif
                uhfDevPrint("UID ");

                for (wIndex = 0; wIndex < 8; wIndex++)
                {
                    uhfDevPrint("%02x ", pucUID[wIndex]);
                }

                uhfDevPrint("\r\nRssi %x\r\n", wRSSI);

                if ((g_awFpgaReadBuf[FPGA_ISO6B_INVENT_FRAME_RESULT + wWord_HasRead] & 0xff)
                    == FPGA_ISO6B_FRAME_RESULT_NO_EEROR)
                {
                    /*如果DATAREAD的起始地址为0 ，
                                         则认为需要对清点到的UID进行校验*/
                    if (g_tISO6BCtrl.wDataReadStartAddr == 0)
                    {
                        if (memcmp(pucUID, pucDRCmdData, 8) == 0)
                        {
                            uhf_ISO6BRecordValidTag(wRSSI, pucUID);
                        }
                        else
                        {
                            UHFErrorPrint("Fpga Rtn a success Frame but not equle to Readed UID \r\n");
                        }
                    }
                    else
                    {
                        uhf_ISO6BRecordValidTag(wRSSI, pucUID);
                    }
                }
                else
                {
                    UHFErrorPrint("Fpga Return a Error tag!\r\n");
                }

                wWord_HasRead = wWord_HasRead + wFrameLen + 1;
                dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;

            }
            else if (wMsgType == FPGA_ISO6B_FRAME_CMD_TYPE_INVENT_FINISH_MSG)
            {
#if 0
				if (usp_cli_isTraceByTno(USP_FPGA_TNO))
                {
                    wTraceLen = sizeof(T_6B_Inventory_Finish_RESP_Trace);
                    uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_6B_Inventory_Finish_RESP, wTraceLen, &g_awFpgaReadBuf[wWord_HasRead]);
                }
#endif
                dwRetVal = MAC_INVENTORY_PROCESS_FINISH;
                break;
            }
            else
            {
                //FPGATrace(wTraceLen);
                UHFWarningPrint("UHF: Fpga_ISO6B_Invetory_Resp() , invalid g_awFpgaReadBuf[FPGA_ISO6B_FRAME_CMD_TYPE] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_ISO6B_FRAME_CMD_TYPE + wWord_HasRead]);
                uhfDevPrint("UHF: frame data for analize: ");

                for (wIndex = 0; wIndex < 12; wIndex++)
                {
                    uhfDevPrint("0x%04x  ", g_awFpgaReadBuf[wIndex + wWord_HasRead]);
                }

                dwRetVal = USP_UHF_FPGA_UNKNOW_FRAME;
                break;
            }

        }

        /* continue to read next frame */
        if (dwRetVal != MAC_INVENTORY_PROCESS_SUCCESS)
        {
            break;
        }

    } /* for ( ; ; ) */

    return (dwRetVal);
}

/**********************************************************************
* 函数名称：WORD32  uhf_GB_Invetory_Resp(void)
* 功能描述：GB清点标签响应数据处理。
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
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
unsigned int flag = 0;
typedef struct
{
    WORD16 wSecMode:2;
    WORD16 wTidLen:8;
    WORD16 wPad:6;
}T_ResTidLen;

WORD32 uhf_GB_Invetory_Resp(T_USPUHFGBInventoryRes *ptGBInventoryResp)
{
    WORD16 wIndex = 0;
    WORD32 dwRetVal = MAC_INVENTORY_PROCESS_FINISH;
    WORD32 dwGB_WordLength = 0;
    WORD16 wFrameLen = 0;
    WORD32 dwWordIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wErrorCode = 0;
    WORD16 wTraceLen = 0;
    WORD16 wTidLen = 0;
    WORD16 wErrorStep = 0;

    T_ResTidLen *t_TidLen = NULL;

    //debug for link success default is success ---lxc 
    if(RCP_RES_DEBUG == 1)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("xxxxxFpgaRes: Invetory_Resp(), FPGA_FRAME_FLAG_SUCCESSS \r\n");
        //ptGBInventoryResp->wPC = g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_PC];
        ptGBInventoryResp->wQueryCollisionCount = GetCollisionCount();
        ptGBInventoryResp->wQueryNoReplyCount = GetNoReplyCount();
        if(0 == (flag %2)){
            uhfDevPrint("xxxxxFpgaRes: Invetory_Resp(),wInventoryFinish = INVENTORY_NOT_FINISH \r\n");
            ptGBInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
            flag++;
        }
        else
        {
            uhfDevPrint("xxxxxFpgaRes:,wInventoryFinish = INVENTORY_HAS_FINISH \r\n");
            ptGBInventoryResp->wInventoryFinish = INVENTORY_HAS_FINISH;
            flag++;
        }
        ptGBInventoryResp->tTagId.wTagWordLen = 0;
        ptGBInventoryResp->wResult = USP_SUCCESS;

        ptGBInventoryResp->wRssi = 222;
        g_tGBCtrl.wLastTagRssi = 222;
        ptGBInventoryResp->tTagId.wTagWordLen = 8;
        /// fake tag --lxc
        g_awFpgaReadBuf[0] = 1;
        g_awFpgaReadBuf[1] = 2;
        g_awFpgaReadBuf[2] = 1;
        g_awFpgaReadBuf[3] = 2;
        g_awFpgaReadBuf[4] = 1;
        g_awFpgaReadBuf[5] = 2;
        g_awFpgaReadBuf[6] = 1;
        g_awFpgaReadBuf[7] = 2; 
        mem_words_cpy(ptGBInventoryResp->tTagId.aucTagData, &g_awFpgaReadBuf[0], 8);
        
        return MAC_INVENTORY_PROCESS_SUCCESS;
    }

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        uhfDevPrint("ReadLowLevelFrame ERROR %d \r\n",dwRetVal);
        return dwRetVal;
    }

    /*全局变量记录清点时标签的RSSI,当RDP调用读操作时返回*/
    g_tEpcCtrl.wLastTagRssi = 0xffff;

    /* 清点标签响应帧数据结构（成功）：
            帧长度/命令类型/成功/PC/EPC/GB
        标签响应帧数据结构（标签访问结束）：
            帧长度/命令类型/结束                                   */

    wFrameLen = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN];

    for (wIndex = 2; wIndex < wFrameLen; wIndex++)
    {
        UHFAlertPrint("%04x ", g_awFpgaReadBuf[wIndex]);
    }

    if(1)
    {
        wTidLen = wFrameLen - 4; /* 去掉帧的其他字段 */
    }
    else
    {
        wTidLen = wFrameLen - 3; /* 字段不带rssi */
    }

    t_TidLen = &g_awFpgaReadBuf[FPGA_GB_FRAME_PC_LEN];

    if (g_awFpgaReadBuf[FPGA_GB_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("UHF: Invetory_Resp(), FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptGBInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptGBInventoryResp->wPC = t_TidLen->wTidLen;
        ptGBInventoryResp->wQueryCollisionCount = GetCollisionCount();
        ptGBInventoryResp->wQueryNoReplyCount = GetNoReplyCount();
        ptGBInventoryResp->wResult = USP_SUCCESS;
        /* 获得EPC长度 */
        /* need fix */
        dwGB_WordLength = t_TidLen->wTidLen; //高5bit表示epc长度       
        
        if ((dwGB_WordLength > EPC_MAX_LENGTH) || (dwGB_WordLength > wFrameLen))
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_Inventory_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Inventory_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        UHFAlertPrint("UHF: GB Tag data: 0x");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            UHFAlertPrint("%04x ", g_awFpgaReadBuf[FPGA_GB_FRAME_PC_LEN + wIndex]);
        }

        UHFAlertPrint("\r\n");
        //最后一个字表示rssi
        ptGBInventoryResp->wRssi = g_awFpgaReadBuf[FPGA_GB_FRAME_PC_LEN + dwGB_WordLength];
        UHFAlertPrint("RSSI is %x\r\n", ptGBInventoryResp->wRssi);
        /*全局变量记录清点时标签的RSSI,当RDP调用读操作时返回*/
        g_tGBCtrl.wLastTagRssi = ptGBInventoryResp->wRssi;


        if (g_tUhfCtrl.atRfAntCfg[g_tUhfCtrl.wAntIndex].tGBReadRssiCfg.ucTurnOnFilter == 1)
        {
            if ((ptGBInventoryResp->wRssi) <
                g_tUhfCtrl.atRfAntCfg[g_tUhfCtrl.wAntIndex].tGBReadRssiCfg.wRSSIThreshHold)
            {
                UHFAlertPrint("Throw a tag!\r\n");
                ptGBInventoryResp->wResult = USP_UHF_GB_RSSI_NOT_ENOUGH;
            }
        }

        ptGBInventoryResp->tTagId.wTagWordLen = dwGB_WordLength;
        mem_words_cpy(ptGBInventoryResp->tTagId.aucTagData, 
                                    &g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE],
                                    dwGB_WordLength);

        /* 如果清点没有完成，则继续接收标签清点响应数据。*/
        uhfDevPrint("UHF: continue to read next frame \r\n");
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;

    }
    else if (g_awFpgaReadBuf[FPGA_GB_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        /* 清点结束 */
        uhfDevPrint("UHF: inventory has finished \r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_Inventory_Finish_RESP_Trace);
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Inventory_Finish_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        ptGBInventoryResp->wRssi = 0;
        ptGBInventoryResp->wResult = USP_SUCCESS;
        ptGBInventoryResp->wInventoryFinish = INVENTORY_HAS_FINISH;
        ptGBInventoryResp->tTagId.wTagWordLen = 0;
        dwRetVal = MAC_INVENTORY_PROCESS_FINISH;
    }
    else if (g_awFpgaReadBuf[FPGA_GB_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 6;
       
        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_Inventory_Error_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Inventory_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_GB_FRAME_GEN2_CODE + dwGB_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: Invetery tag wErrorStep= 0x%04x \r\n", wErrorStep);
        
        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];

        /* 标签错误码 */
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];

        
        wErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);
        UHFErrorPrint("UHF:Inventory Error happens Code %d\r\n", wErrorCode);
        ptGBInventoryResp->wRssi = 0;
        ptGBInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptGBInventoryResp->tTagId.wTagWordLen = 0;
        ptGBInventoryResp->wResult = wErrorCode;
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;
    }
    else
    {
#if 0
		if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = FPGA_ERROR_TRACE_LEN * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_FPGA_UNKNOW_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        UHFWarningPrint("UHF: uhf_GB_Invetory_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);
        uhfDevPrint("UHF: frame data for analize: ");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x  ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");

        ptGBInventoryResp->wRssi = 0;
        ptGBInventoryResp->wInventoryFinish = INVENTORY_NOT_FINISH;
        ptGBInventoryResp->tTagId.wTagWordLen = 0;
        ptGBInventoryResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;
    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Invetory_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_GB_Read_Resp(void)
* 功能描述：GB读标签响应数据处理。
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
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_Read_Resp(T_USPUHFGBReadRes *ptGBReadResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwGB_WordLength;
    WORD32 dwWordIndex;
    WORD16 wReadWordCount;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wErrorCode = 0;
    WORD16 wErrorStep = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    if(RCP_RES_DEBUG == 1)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("xxxxxFpgaRes: uhf_GB_Read_Resp, FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptGBReadResp->wResult=0;
	 ptGBReadResp->wResultLength=g_tGBCtrl.tGBRead.wReadWordsLen;

        memset(g_awFpgaReadBuf,0,sizeof(g_awFpgaReadBuf));
        mem_words_cpy(ptGBReadResp->awReadData, &g_awFpgaReadBuf[0], ptGBReadResp->wResultLength*2);
        
        return 0;
    }

    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
       读标签响应帧数据结构（成功）：
       帧长度命令类型成功 PC GB   读数据长度   标签数据

      读标签响应帧数据结构（失败）：
      帧长度    命令类型  失败  PC  GB 错误阶段 自定义错误码  标签返回的错误码
     */

    if (g_awFpgaReadBuf[FPGA_GB_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {

        uhfDevPrint("UHF: read tag data success \r\n"); 
        /* 获得GB长度*/
        // 新国标中回应数据包中没有帧长度，是fpga  返回的帧长度吗?
        // 整帧长度
        
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE] - g_awFpgaReadBuf[FPGA_GB_FRAME_READ_DATA_LEN] - 4;
        
        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        /* the tag epc code */
        uhfDevPrint("UHF: GB ID: 0x");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");

        dwWordIndex = dwGB_WordLength + FPGA_GB_FRAME_GEN2_CODE;

        /* tag data word length that is readed */
        // g_awFpgaReadBuf[dwWordIndex] 表示数据长度?        wReadWordCount = g_awFpgaReadBuf[dwWordIndex];

        if (wReadWordCount >GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, wReadWordCount, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        uhfDevPrint("read success length is %d\r\n", g_awFpgaReadBuf[FPGA_GB_FRAME_READ_DATA_LEN]);
        ptGBReadResp->wResult = USP_SUCCESS;
        ptGBReadResp->wResultLength = g_tGBCtrl.tGBRead.wReadWordsLen;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_READ_RESP_Trace) + (g_awFpgaReadBuf[FPGA_FRAME_LEN]) * 2; //乘2  干啥
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Read_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        /*指向读到的标签数据*/
        dwWordIndex++;
        /* 复制读到的标签内存数据 */
        mem_words_cpy(ptGBReadResp->awReadData, 
                                    &g_awFpgaReadBuf[dwWordIndex], 
                                    g_awFpgaReadBuf[FPGA_GB_FRAME_READ_DATA_LEN]);

        uhfDevPrint("UHF: read tag data:0x");

        for (wIndex = 0; wIndex < wReadWordCount; wIndex++)
        {
            uhfDevPrint("%04x ", ptGBReadResp->awReadData[wIndex]);
        }

        uhfDevPrint("\r\n");

    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* 读标签失败 */
        UHFErrorPrint("UHF: read tag data fail !!!\r\n");
                /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 6;

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_READ_Error_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Read_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
        dwWordIndex = FPGA_GB_FRAME_GEN2_CODE + dwGB_WordLength;
        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: read tag wErrorStep= 0x%04x \r\n", wErrorStep);
        
        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];

        /* 标签错误码 */
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];

        
        wErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);
        UHFErrorPrint("UHF:Read Error happens Code %d\r\n", wErrorCode);
        ptGBReadResp->wRssi = 0;
       // ptGBReadResp->wInventoryFinish = INVENTORY_NOT_FINISH;
       // ptGBReadResp->tTagId.wTagWordLen = 0;
        ptGBReadResp->wResult = wErrorCode;
        dwRetVal = MAC_INVENTORY_PROCESS_SUCCESS;


    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("UHF: cannot invent tag when read tag\r\n");

        ptGBReadResp->wResult = USP_UHF_GB_CANNOT_FIND_TAG;
        ptGBReadResp->wResultLength = 0;
    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: uhf_GB_Read_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", 
                                     g_awFpgaReadBuf[FPGA_GB_FRAME_FLAG]);
        uhfDevPrint("UHF: frame data for analize: 0x");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");

        ptGBReadResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        ptGBReadResp->wResultLength = 0;

    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Read_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_GB_Write_Resp(void)
* 功能描述：GB写标签响应数据处理。
* 输入参数：
* 输出参数：T_GB_WriteResponse *ptEPCWriteResp   写入结果
* 返 回 值： WORD32
                              0：    成功
                             其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/

WORD32 uhf_GB_Write_Resp(T_USPUHFGBWriteRes *ptGBWriteResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwGB_WordLength;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex;
    WORD16 wWriteWordCount;
    WORD16 wErrorStep;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    if(RCP_RES_DEBUG == 1)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("xxxxxFpgaRes: uhf_GB_Write_Resp, FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptGBWriteResp->wResult=0;
	 ptGBWriteResp->wResultLength=g_tGBCtrl.tGBWrite.wWriteWordsLen;
        
        return 0;
    }
    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /*
        写标签响应帧数据结构（成功）：
        帧长度   命令类型    成功    PC   EPC   写数据长度

        写标签响应帧数据结构（失败）：
        帧长度   命令类型    失败     PC    EPC   错误阶段   自定义错误码      标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {

        uhfDevPrint("UHF: GB write success \r\n");

        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 4;               /* the tag epc code */

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        uhfDevPrint("UHF: GB ID: ");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("0x%04x  ", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");

        ptGBWriteResp->wResult = USP_SUCCESS;

        wWriteWordCount = g_awFpgaReadBuf[FPGA_GB_FRAME_WRITE_DATA_LEN];
        uhfDevPrint("UHF: wWriteWordCount = %d  \r\n", wWriteWordCount);

        if (wWriteWordCount > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, wWriteWordCount, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        ptGBWriteResp->wResultLength = wWriteWordCount;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_WRITE_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_EPC_Write_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {

        uhfDevPrint("GB Write Error\r\n");
        /* 获得GB长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 6;

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;
        }

        /* the tag epc code */
        uhfDevPrint("UHF: GB ID:0x");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_GB_FRAME_GEN2_CODE + dwGB_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: write tag wErrorStep= 0x%04x \r\n", wErrorStep);
        
        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];

        /* 标签错误码 */
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];

        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);
        ptGBWriteResp->wResult = (WORD16)dwErrorCode;

        ptGBWriteResp->wResultLength = 0;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_WRITE_Error_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Write_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("UHF: cannot invent tag when read tag\r\n");

        ptGBWriteResp->wResult = USP_UHF_EPC_CANNOT_FIND_TAG;
        ptGBWriteResp->wResultLength = 0;

    }
    else
    {

        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: uhf_GB_Write_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", 
                                     g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptGBWriteResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
        ptGBWriteResp->wResultLength = 0;
    }

    return (dwRetVal);

} /* WORD32  uhf_GB_Write_Resp(void) */

/**********************************************************************
* 函数名称：WORD32 uhf_GB_Lock_Resp(T_USPUHFGBLockRes *ptGBLockResp)
* 功能描述：GB锁定标签响应处理
* 输入参数：
* 输出参数：
* 返 回 值： WORD32
                              0：    成功
                             其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_Lock_Resp(T_USPUHFGBLockRes *ptGBLockResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwGB_WordLength;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex;
    WORD16 wErrorStep;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    if(RCP_RES_DEBUG == 1)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("xxxxxFpgaRes: uhf_GB_Lock_Resp, FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptGBLockResp->wResult=0;       
        return 0;
    }
    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
        LOCK标签数据结构：
         帧长度    命令类型     成功    PC    EPC

        LOCK标签数据结构：
          帧长度  命令类型     失败   PC   EPC   错误阶段  自定义错误码   标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        /* record finish time */
        uhfDevPrint("UHF: Lock success \r\n");

        /* 生成写标签响应消息，发送到RDP。*/
        ptGBLockResp->wResult = USP_SUCCESS;

        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 3;               /* the tag epc code */

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: GB ID: ");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_EPC_LOCK_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Lock_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* Lock标签失败 */
        UHFErrorPrint("UHF: Lock fail \r\n");
        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 6;

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: GB ID:0x");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_GB_FRAME_GEN2_CODE + dwGB_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: write tag wErrorStep = 0x%04x \r\n", wErrorStep);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptGBLockResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_LOCK_Error_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Lock_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("cannot invent tag when read tag\r\n");
        ptGBLockResp->wResult = USP_UHF_GB_CANNOT_FIND_TAG;
    }
    else
    {

        //FPGATrace(wTraceLen);
        UHFWarningPrint("uhf_GB_Lock_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("frame data for analize: ");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("%04x  ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptGBLockResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
    }

    return (dwRetVal);

} /* WORD32  uhf_Epc_Lock_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_GB_Erase_Resp(void)
* 功能描述：GB擦除标签响应处理
* 输入参数：
* 输出参数：
* 返 回 值：
            WORD32
                      0：    成功
                   其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/
WORD32 uhf_GB_Erase_Resp(T_USPUHFGBEraseRes *ptGBEraseResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwGB_WordLength;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex;
    WORD16 wErrorStep;
    WORD16 wSelfDefErrCode;
    WORD16 wTagErrCode;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;

    if(RCP_RES_DEBUG == 1)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("xxxxxFpgaRes: uhf_GB_Erase_Resp, FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptGBEraseResp->wResult=0;
	 ptGBEraseResp->wResultLength=g_tGBCtrl.tGBErase.wEraseWordsLen;
        
        return 0;
    }
    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
        Erase标签数据结构：
         帧长度    命令类型     成功    PC    EPC

        Erase标签数据结构：
          帧长度  命令类型     失败   PC   EPC   错误阶段  自定义错误码   标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        /* record finish time */
        uhfDevPrint("UHF: Erase success \r\n");

        /* 生成写标签响应消息，发送到RDP。*/
        ptGBEraseResp->wResult = USP_SUCCESS;

        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 3;               /* the tag epc code */

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("GB: GB ID: ");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_ERASE_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Erase_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* Lock标签失败 */
        UHFErrorPrint("UHF: Erase fail \r\n");
        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 6;

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: GB ID:0x");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_GB_FRAME_GEN2_CODE + dwGB_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        wErrorStep = g_awFpgaReadBuf[dwWordIndex];
        UHFErrorPrint("UHF: Erase tag wErrorStep = 0x%04x \r\n", wErrorStep);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptGBEraseResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_ERASE_Error_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Erase_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("cannot invent tag when read tag\r\n");
        ptGBEraseResp->wResult = USP_UHF_GB_CANNOT_FIND_TAG;
    }
    else
    {

        //FPGATrace(wTraceLen);
        UHFWarningPrint("uhf_GB_Erase_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("frame data for analize: ");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("%04x  ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptGBEraseResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
    }

    return (dwRetVal);

} /* WORD32  uhf_GB_Lock_Resp(void) */

/**********************************************************************
* 函数名称：WORD32  uhf_GB_Kill_Resp(void)
* 功能描述：GB 杀死标签响应处理
* 输入参数：
* 输出参数：
* 返 回 值：
            WORD32
                      0：    成功
                   其他：    失败
* 其它说明：无
* 修改日期      版本号  修改人      修改内容
* ---------------------------------------------------------------------
* 2014/2/16    V0.0.1       lxc          创建
************************************************************************/

WORD32 uhf_GB_Kill_Resp(T_USPUHFGBKillRes *ptGBKillResp)
{
    WORD32 dwRetVal = USP_SUCCESS;
    WORD32 dwGB_WordLength = 0;
    WORD32 dwErrorCode = 0;
    WORD32 dwWordIndex = 0;
    WORD16 wSelfDefErrCode = 0;
    WORD16 wTagErrCode = 0;
    WORD16 wIndex = 0;
    WORD16 wReadLen = 0;
    WORD16 wTraceLen = 0;


    if(RCP_RES_DEBUG == 1)
    {
        /*清点上来一个标签后重新设置RCP 超时定时器*/
        uhfDevPrint("xxxxxFpgaRes: uhf_GB_Kill_Resp, FPGA_FRAME_FLAG_SUCCESSS \r\n");
        ptGBKillResp->wResult=0;        
        return 0;
    }
    dwRetVal = ReadLowLevelFrame(&wReadLen);

    if (USP_SUCCESS != dwRetVal)
    {
        return dwRetVal;
    }

    /* 检查标签响应数据格式 */
    /*
        LOCK标签数据结构：
         帧长度命令类型   成功   PC   EPC

        LOCK标签数据结构：
         帧长度     命令类型     失败   PC   EPC     错误阶段    自定义错误码    标签返回的错误码
    */

    if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_SUCCESSS)
    {
        uhfDevPrint("UHF: Kill success \r\n");

        ptGBKillResp->wResult = USP_SUCCESS;
        /* 获得GB长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 3;               /* the tag epc code */

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        uhfDevPrint("UHF: GB ID: ");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x  ", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_KILL_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Kill_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_FAIL)
    {
        /* Kill标签失败 */
        UHFErrorPrint("UHF: Kill tag failed \r\n");

        /* 获得EPC长度 */
        dwGB_WordLength = g_awFpgaReadBuf[FPGA_GB_FRAME_LEN] - 6;

        if (dwGB_WordLength > GB_MAX_LENGTH)
        {
            LAPInsert(FILE_UHF_FPGARES, USP_UHF_FPGA_UNKNOW_FRAME, dwGB_WordLength, 0);
            return USP_UHF_FPGA_UNKNOW_FRAME;

        }

        /* the tag epc code */
        uhfDevPrint("UHF: GB ID: ");

        for (wIndex = 0; wIndex < dwGB_WordLength; wIndex++)
        {
            uhfDevPrint("%04x ", g_awFpgaReadBuf[FPGA_GB_FRAME_GEN2_CODE + wIndex]);
        }

        uhfDevPrint("\r\n");
        dwWordIndex = FPGA_GB_FRAME_GEN2_CODE + dwGB_WordLength; /* 指向错误阶段 */

        /* 错误阶段 */
        UHFErrorPrint("UHF: Kill tag wErrorStep = 0x%04x \r\n", g_awFpgaReadBuf[dwWordIndex]);

        /* 自定义错误码 */
        dwWordIndex++;
        wSelfDefErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwWordIndex++;
        wTagErrCode = g_awFpgaReadBuf[dwWordIndex];
        dwErrorCode = TranferErrCode(wSelfDefErrCode, wTagErrCode);

        ptGBKillResp->wResult = dwErrorCode;
#if 0
        if (usp_cli_isTraceByTno(USP_FPGA_TNO))
        {
            wTraceLen = sizeof(T_GB_KILL_Error_RESP_Trace) + dwGB_WordLength * 2;
            uhf_SendTraceMsg(EV_FPGA_TO_RCP, EV_GB_Kill_Error_RESP, wTraceLen, g_awFpgaReadBuf);
        }
#endif
    }
    else if (g_awFpgaReadBuf[FPGA_FRAME_FLAG] == FPGA_FRAME_FLAG_INVENT_FINISH)
    {
        uhfDevPrint("cannot invent tag when read tag\r\n");
        ptGBKillResp->wResult = USP_UHF_GB_CANNOT_FIND_TAG;
    }
    else
    {
        //FPGATrace(wTraceLen);
        UHFWarningPrint("UHF: uhf_GB_Kill_Resp() , invalid g_awFpgaReadBuf[FPGA_FRAME_FLAG] == 0x%04x \r\n", g_awFpgaReadBuf[FPGA_FRAME_FLAG]);

        uhfDevPrint("UHF: frame data for analize: \r\n");

        for (wIndex = 0; wIndex < 6; wIndex++)
        {
            uhfDevPrint("0x%04x ", g_awFpgaReadBuf[wIndex]);
        }

        uhfDevPrint("\r\n");
        ptGBKillResp->wResult = USP_UHF_FPGA_UNKNOW_FRAME;
    }

    return (dwRetVal);

} /* WORD32  uhf_GB_Kill_Resp(void) */

#endif

