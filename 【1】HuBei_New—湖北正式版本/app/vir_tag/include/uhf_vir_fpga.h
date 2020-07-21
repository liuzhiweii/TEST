#ifndef __UHF_VIR_FPGA__
#define __UHF_VIR_FPGA__


#define VIR_FPGA_REG_TABLE_SIZE            65536
#define VIR_FPGA_SELECT_MASK_LEN           32
#define VIR_FPGA_BLOCK_DATA_LEN             32


#define vir_fpga_debug(...) 


extern void usp_vir_fpga_initReg(void);
extern void usp_vir_fpga_writeReg(WORD32 wAddr, WORD16 wData);
extern WORD16 usp_vir_fpga_readReg(WORD32 wAddr);
extern WORD16 usp_vir_fpga_readReg(WORD32 wAddr);


#endif


