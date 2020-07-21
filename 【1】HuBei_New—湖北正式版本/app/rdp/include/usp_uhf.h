#ifndef _USP_UHF_H
#define _USP_UHF_H

unsigned int usp_uhf_rf_FPGALKCLProcTry(T_USPUHFLKCLInitParas *ptInintLKCLAdj,
                                    T_USPUHFLKCLParas *ptLKCLSetPara);
unsigned int usp_uhf_rf_selectAnt(unsigned short int wAntIndex);
unsigned short int usp_uhf_rf_TransToFpgaAtten(unsigned short int wAttenuation);
unsigned int usp_uhf_rf_WriteAntDatt();
unsigned int usp_uhf_rf_setRevDatt(unsigned short int wDattVal);
unsigned int usp_uhf_rf_setRevFilter(unsigned char ucFilter);
unsigned int usp_uhf_rf_removeAntAlarm();
unsigned int usp_uhf_rf_setACDatt(unsigned short int wAttenuation);
signed short int usp_uhf_rf_ComputePower(unsigned short int wVoltage, unsigned char ucAntIndex, unsigned char flag);
unsigned int usp_uhf_rf_setPowerDir(unsigned short int wDirect);
unsigned int usp_uhf_rf_setPLLFreq(unsigned int dwRfFreq);
unsigned int usp_uhf_rf_autoCalibrate(unsigned char ucAntIndex, unsigned short int wPTarget);
unsigned int usp_uhf_rf_setTxPower(unsigned short int wAntIndex, unsigned short int wTargetPower);
unsigned int usp_uhf_rf_getAntStatus(unsigned short int wAntIndex);
unsigned short int usp_uhf_rf_readDetectVal();
unsigned short int usp_uhf_rf_queryAntVswr(unsigned short int wAntIndex);
unsigned int usp_uhf_rf_init();
void   usp_uhf_rf_setDemodLoSel(unsigned short int wType);
void   usp_uhf_rf_setRTModuleType(unsigned short int wType);
void   usp_uhf_rf_setAmp(unsigned short int wAction);
void   usp_uhf_rf_writeCtrlWord(unsigned short int wCrtlWord);
unsigned int usp_uhf_init();
void   usp_uhf_rf_txSet(unsigned short int wRfTxAction);
unsigned int usp_uhf_rf_readPowerTable(T_USPUHFRfPowerTable *ptPowerTable, unsigned short int wPTAddr);
unsigned int usp_uhf_rf_writePowerTable(T_USPUHFRfPowerTable *ptPowerTable, unsigned short int wPTAddr);
unsigned int usp_uhf_rf_readGateVoltageValue(T_USPUHFGateVoltageCtrl *ptGateVolCtrl);
unsigned int usp_uhf_rf_writeGateVoltageValue(T_USPUHFGateVoltageCtrl *ptGateVolCtrl);
unsigned int usp_uhf_rf_readPRData(T_USPUHFRfPowerTable *ptPowerTable, unsigned short int wPTAddr);
unsigned int usp_uhf_rf_writePRData(T_USPUHFRfPowerTable *ptPowerTable, unsigned short int wPTAddr);
void   usp_uhf_rf_AutoCalibrateInit();
unsigned short int usp_uhf_rf_GetFreqType(void);
unsigned int usp_uhf_rf_CalibrateK0Datt(unsigned short int wPTarget, unsigned short int wAntIndex);
unsigned int usp_uhf_rf_SetLO2Datt(unsigned short int wCurPower);
unsigned short int usp_uhf_rf_GetPowerDatt(unsigned short int wAntIndex, unsigned short int wPTarget, unsigned short int *pwFpgaAtt, unsigned short int wK0);
unsigned short int usp_uhf_rf_GetPowerK0(unsigned short int wAntIndex, unsigned short int wPTarget, unsigned short int wFpgaAtt, unsigned short int *pwK0, unsigned short int wDetectPower);
void   usp_uhf_rf_ClearPowerResult();
void   usp_uhf_rf_SetPowerEntry(unsigned short int wAntIndex, unsigned short int wClibratePower,
                                 unsigned short int wTargetPower, unsigned short int wClibrateK0, unsigned short int wDattVal);
T_USPUHFRfPowerEntry *usp_uhf_rf_FindPowerEntry(unsigned short int wAntIndex, unsigned short int wTargetPower);


#endif
