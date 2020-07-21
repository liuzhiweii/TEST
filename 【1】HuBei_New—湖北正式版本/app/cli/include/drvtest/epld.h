

#ifndef _DRVTEST_EPLD_H
#define _DRVTEST_EPLD_H
#include "bsp.h"

unsigned int  drvtest_writepld(unsigned int dwOffset,T_EpldData tVale);
unsigned int  drvtest_readepld(unsigned int dwOffset);


#endif

