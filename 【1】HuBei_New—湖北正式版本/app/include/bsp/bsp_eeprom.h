

#ifndef _BSP_EEPROM_H_
#define _BSP_EEPROM_H_

#ifdef __cplusplus
extern "C"
{
#endif


unsigned int bsp_eeprom_init(void);
unsigned int  bsp_eeprom_snd(unsigned int dwOffset, unsigned int dwLen, unsigned char *pucBuf, unsigned int * pdwSndLen);
unsigned int  bsp_eeprom_rcv(unsigned int dwOffset, unsigned int dwLen, unsigned char *pucBuf, unsigned int * pdwRcvLen);

#ifdef __cplusplus
}
#endif

#endif



