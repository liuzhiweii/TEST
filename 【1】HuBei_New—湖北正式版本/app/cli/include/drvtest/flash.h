

#ifndef _DRVTEST_FLASH_H
#define _DRVTEST_FLASH_H
#include "bsp.h"

unsigned int drvtest_flash_write(unsigned int dwOffset, unsigned int dwLen, unsigned char ucdata);
unsigned int drvtest_flash_read(unsigned int dwOffset, unsigned int dwLen);
unsigned int drvtest_flash_erase(unsigned int dwOffset, unsigned int dwLen);
unsigned int drvtest_flash_info(void);

#endif

