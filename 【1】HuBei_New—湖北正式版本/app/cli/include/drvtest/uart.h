

#ifndef _DRVTEST_UART_H
#define _DRVTEST_UART_H
#include "bsp.h"


unsigned int  drvtest_uart_revsend(unsigned int dwindex,unsigned int dwbRate);
unsigned int  drvtest_uart_loopback(unsigned int dwindex,unsigned int dwbRate, unsigned int dwLoopNum);

#endif

