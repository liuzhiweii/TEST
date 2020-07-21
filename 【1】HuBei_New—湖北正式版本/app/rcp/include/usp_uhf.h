#ifndef _USP_UHF_H
#define _USP_UHF_H

WORD32 usp_uhf_rf_FPGALKCLProcTry(T_USPUHFLKCLInitParas *ptInintLKCLAdj,
                                    T_USPUHFLKCLParas *ptLKCLSetPara);
WORD32 usp_uhf_rf_selectAnt(WORD16 wAntIndex);
WORD16 usp_uhf_rf_TransToFpgaAtten(WORD16 wAttenuation);
WORD32 usp_uhf_rf_WriteAntDatt();
WORD32 usp_uhf_rf_setRevDatt(WORD16 wDattVal);
WORD32 usp_uhf_rf_setRevFilter(BYTE ucFilter);
WORD32 usp_uhf_rf_removeAntAlarm();
WORD32 usp_uhf_rf_setACDatt(WORD16 wAttenuation);
SWORD16 usp_uhf_rf_ComputePower(WORD16 wVoltage, BYTE ucAntIndex, BYTE flag);
WORD32 usp_uhf_rf_setPowerDir(WORD16 wDirect);
WORD32 usp_uhf_rf_setPLLFreq(WORD32 dwRfFreq);
WORD32 usp_uhf_rf_autoCalibrate(BYTE ucAntIndex, WORD16 wPTarget);
WORD32 usp_uhf_rf_setTxPower(WORD16 wAntIndex, WORD16 wTargetPower);
WORD32 usp_uhf_rf_getAntStatus(WORD16 wAntIndex);
WORD16 usp_uhf_rf_readDetectVal();
WORD16 usp_uhf_rf_queryAntVswr(WORD16 wAntIndex);
WORD32 usp_uhf_rf_init();
void   usp_uhf_rf_setDemodLoSel(WORD16 wType);
void   usp_uhf_rf_setRTModuleType(WORD16 wType);
void   usp_uhf_rf_setAmp(WORD16 wAction);
void   usp_uhf_rf_writeCtrlWord(WORD16 wCrtlWord);
WORD32 usp_uhf_init();
void   usp_uhf_rf_txSet(WORD16 wRfTxAction);
WORD32 usp_uhf_rf_readPowerTable(T_USPUHFRfPowerTable *ptPowerTable, WORD16 wPTAddr);
WORD32 usp_uhf_rf_writePowerTable(T_USPUHFRfPowerTable *ptPowerTable, WORD16 wPTAddr);
WORD32 usp_uhf_rf_readGateVoltageValue(T_USPUHFGateVoltageCtrl *ptGateVolCtrl);
WORD32 usp_uhf_rf_writeGateVoltageValue(T_USPUHFGateVoltageCtrl *ptGateVolCtrl);
WORD32 usp_uhf_rf_readPRData(T_USPUHFRfPowerTable *ptPowerTable, WORD16 wPTAddr);
WORD32 usp_uhf_rf_writePRData(T_USPUHFRfPowerTable *ptPowerTable, WORD16 wPTAddr);
void   usp_uhf_rf_AutoCalibrateInit();
WORD16 usp_uhf_rf_GetFreqType(void);
WORD32 usp_uhf_rf_CalibrateK0Datt(WORD16 wPTarget, WORD16 wAntIndex);
WORD32 usp_uhf_rf_SetLO2Datt(WORD16 wCurPower);
WORD16 usp_uhf_rf_GetPowerDatt(WORD16 wAntIndex, WORD16 wPTarget, WORD16 *pwFpgaAtt, WORD16 wK0);
WORD16 usp_uhf_rf_GetPowerK0(WORD16 wAntIndex, WORD16 wPTarget, WORD16 wFpgaAtt, WORD16 *pwK0, WORD16 wDetectPower);
void   usp_uhf_rf_ClearPowerResult();
void   usp_uhf_rf_SetPowerEntry(WORD16 wAntIndex, WORD16 wClibratePower,
                                 WORD16 wTargetPower, WORD16 wClibrateK0, WORD16 wDattVal);
T_USPUHFRfPowerEntry *usp_uhf_rf_FindPowerEntry(WORD16 wAntIndex, WORD16 wTargetPower);


#endif

