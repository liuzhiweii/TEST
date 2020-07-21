

#ifndef _DRVTEST_PSAM_H
#define _DRVTEST_PSAM_H
#include "bsp.h"

enum
{
	ENABLE_OUTPUT,
	DISABLE_OUTPUT,
};

unsigned int drvtest_psaminit(void);
unsigned int drvtest_psamsetclk(unsigned int dwClkDiv);
unsigned int drvtest_psamactive(unsigned int dwCardID);
unsigned int drvtest_psamdeactive(unsigned int dwCardID);
unsigned int drvtest_psamrandomdata(unsigned int dwCardID);
unsigned int drvtest_psamchoseapp(unsigned int dwCardID);
unsigned int drvtest_psamassignkey(unsigned int dwCardID);
unsigned int drvtest_psamdecryptinfo(unsigned int dwCardID);
unsigned int drvtest_autodecrypt (unsigned int dwCardID);
unsigned int drvtest_psam_enable_pps(unsigned int dwCardID);
unsigned int drvtest_psam_disable_pps(unsigned int dwCardID);


#define ERROR -1
#endif

