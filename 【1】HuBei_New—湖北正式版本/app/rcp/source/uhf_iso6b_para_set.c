#include "usp.h"
#if (UHF_PROTOCOL_USE) &&(UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include "usp_uhf_cfg.h"
#include "uhfFpgaRegDef.h"
#include "usp_uhf_iso6b.h"
#include "usp_uhf_err.h"
#include "uhf.h"
#include "uhf_trace.h"
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf.h"
#include "ISO6B.h"

extern T_ISO6BCtl g_tISO6BCtrl;
static const T_ISO6BUHFRFModeTableEntry g_ISO6BUHFRFModeTable[] = ISO6B_RFMODE_TABLE;
/**********************************************************************
* 函数名称： void uhf_ISO6B_Cal_Mode_Para(WORD16 ModeIndex)
* 功能描述：根据ModeIndex确定6B协议的时序参数
* 输入参数： ModeIndex :序号
* 输出参数：无
* 返 回 值：    无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------ -----------------
* 2009\12\1              V03.00.00           zdx              创建
**************************************************************************/
void uhf_ISO6B_Cal_Mode_Para(WORD16 ModeIndex)
{
    static const WORD16 wISO6BModeIndexLen = sizeof(g_ISO6BUHFRFModeTable) / sizeof(T_ISO6BUHFRFModeTableEntry);
    /* 参数检测，参数值的范围是0-20*/
    uhfDevPrint("UHF Using ModeIndex %d,wISO6BModeIndexLen %d\r\n", ModeIndex, wISO6BModeIndexLen);

    if (ModeIndex == g_tISO6BCtrl.wModeIndex)
    {
        return ;
    }
    else
    {
        if (ModeIndex >= wISO6BModeIndexLen)
        {
            g_tISO6BCtrl.wModeIndex = 0;
        }

        g_tISO6BCtrl.wModeIndex = ModeIndex;
    }

    g_tISO6BCtrl.wFowardLinkDataRate = (WORD16)g_ISO6BUHFRFModeTable[ModeIndex].dwFowardLinkDataRate / 1000;

    uhfDevPrint("g_tISO6BCtrl.wFowardLinkDataRate == %d\r\n", g_tISO6BCtrl.wFowardLinkDataRate);
    uhfDevPrint("g_ISO6BUHFRFModeTable[ModeIndex].ucDelimiters == %d\r\n", g_ISO6BUHFRFModeTable[ModeIndex].ucDelimiters);

    if (ModeIndex == 0)
    {
        g_tISO6BCtrl.wReverseLinkDataRate = g_tISO6BCtrl.wFowardLinkDataRate;
        g_tISO6BCtrl.wdelimeters = ISO18000_6B_forward_delimeter1;
        g_tISO6BCtrl.wT1_value = 0x4000;
    }
    else if (ModeIndex == 1)
    {
        uhfDevPrint("Using Reverse DataRate 160\r\n");
        g_tISO6BCtrl.wReverseLinkDataRate = 4 * g_tISO6BCtrl.wFowardLinkDataRate;
        g_tISO6BCtrl.wdelimeters = ISO18000_6B_forward_delimeter4;
        g_tISO6BCtrl.wT1_value = 0x5C0;/*根据EPC 160速率协议参数设置*/
    }
    else
    {
        uhfDevPrint("Using Reverse DataRate 80\r\n");
        g_tISO6BCtrl.wReverseLinkDataRate = 4 * g_tISO6BCtrl.wFowardLinkDataRate;
        g_tISO6BCtrl.wdelimeters = ISO18000_6B_forward_delimeter4;
        g_tISO6BCtrl.wT1_value = 0x2000;
    }
}
#endif
