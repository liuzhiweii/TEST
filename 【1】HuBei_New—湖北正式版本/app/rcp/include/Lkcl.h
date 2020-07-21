#ifndef LKCL_H
#define LKCL_H

/*一根天线最多有几个对消结果表*/
#define UHF_RF_MAX_LKCL_TABLE_LEN  (3) 

typedef  struct tag_initPhase
{
    SWORD16 swCos;
    SWORD16 swSin;
}T_InitPhase;


/*以美国标准定义最多的频道数，以数组下标标代表频道号*/
typedef struct
{
  WORD16 wHopTableID;
  WORD16 wTryIndex;
  T_USPUHFLKCLParas tAntLKCLPara[UHF_RF_MAX_FREQ_NUM];
}T_SingleFreqTableLKCLPara;

typedef struct
{
  WORD16 wLKCLTableLen;
  WORD16 wLKCLIndex;
  T_SingleFreqTableLKCLPara tSingleFreqTableLKCLPara[UHF_RF_MAX_LKCL_TABLE_LEN];
}T_SingleAntLKCLPara;

#define FPGA_RFADJ_CANNOT_STOP       (100)

void uhfRf_SetLKCLInitPara(void);
void uhfRf_VAutoAdjust(void);
WORD32 uhfRf_FineLKCL(BYTE ucAntIndex, T_UhfRfFreqHopCtrl *ptFreqHopCtrl);
WORD32 uhfRf_FPGALKCLProc(T_USPUHFLKCLInitParas *ptInintLKCLAdj,
                                   T_USPUHFLKCLParas *ptLKCLSetPara,
                                   WORD16 *pwTryindex);

#endif
