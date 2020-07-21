

#ifndef _DRVTEST_EEPROM_H
#define _DRVTEST_EEPROM_H
#include "bsp.h"

unsigned int drvtest_eeprom_write(unsigned char ucdata);
unsigned int drvtest_eeprom_read(void);
unsigned int drvtest_eeprom_savedata(void);
unsigned int drvtest_eeprom_recoverdata(void);
unsigned int drvtest_seteeprom(char *pFilePath);

#endif

