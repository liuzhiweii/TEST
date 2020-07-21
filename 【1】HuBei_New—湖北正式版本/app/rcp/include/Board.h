/************************************************************************
* 版权所有 (C)2011, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： board.h
* 文件标识： 
* 内容摘要： 不同射频板采用的宏定义文件
* 其它说明： 
* 当前版本： 
* 作    者： zdx
* 完成日期： 2010.12.26
* 
* 修改记录1： RUP 增加RFCB2定义
*    修改日期：2011.12.1
*    版 本 号：    RUP
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "uhfRfRegDef.h"
#include "RFCB.h"
#include "RFCB2.h"
#include "PURM.h"
#include "RFCB_BT.h"
#include "RFCB7.h"

#define MODULE_TYPE_DSB  (1)
#define MODULE_TYPE_PR   (3)

extern WORD32 g_dwUSPUhfVirTagWorkFlag;

#define FpgaRegWrite(wRegAddr,wData)   g_pvUSPDrvFpgaVirtStartAddr0[wRegAddr]=wData
#define FpgaRegRead(wRegAddr)          g_pvUSPDrvFpgaVirtStartAddr0[wRegAddr]


/* 缺省功率，实际功率乘以100以后的值 */
#define UHF_RF_MAX_FREQ_NUM                   (50)
#define UHF_RF_MIN_POWER                      (1500)

void uhfRf_initVswrAlarm(void);
void uhfRf_ReaderLKCLProc();
void uhfRf_SetForDataRate(WORD16 wForRate);

WORD32 uhfRf_BoardInit(void);

WORD32 usp_uhf_rf_setLO2Datt(WORD16 wCurPower);
WORD16 uhfRf_dealAlarmReport(WORD16 wAntIndex);
WORD32 uhfRf_SetLKCLSwitch(BYTE ucSwitch);
WORD32 uhfRf_SetRevLowNoEn(BYTE ucLowNoEn);
WORD32 uhfRf_IsAntProtected(void);
WORD32 uhfRf_ChooseRevFilter(WORD16 wLinkRate, BYTE ucSwitch);
WORD32 uhfRf_BoardReset(void);
WORD32 SetDATTtoZero(void);


#endif

