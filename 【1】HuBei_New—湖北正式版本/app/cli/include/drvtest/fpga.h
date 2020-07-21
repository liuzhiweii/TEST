

#ifndef _DRVTEST_FPGA_H
#define _DRVTEST_FPGA_H
#include "bsp.h"

unsigned int  drvtest_writefpga(unsigned int dwOffset,T_EpldData tVale);
unsigned int  drvtest_readfpga(unsigned int dwOffset);


#endif

