

#ifndef _DRVTEST_DEVICECTL_H
#define _DRVTEST_DEVICECTL_H
#include "bsp.h"

unsigned int  drvtest_device_rst(unsigned int dwDeviceId);
unsigned int  drvtest_device_powctl(unsigned int dwDeviceId, unsigned int dwPowState);

#endif

