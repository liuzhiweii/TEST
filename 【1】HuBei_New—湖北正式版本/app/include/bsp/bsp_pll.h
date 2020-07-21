#ifndef __BSP_PLL__
#define __BSP_PLL__

#ifdef __cplusplus
extern "C"
{
#endif

unsigned int bsp_init_pll(void);
unsigned int  bsp_read_pll(unsigned int dwOffset, unsigned int dwLen, unsigned char *pucBuf, unsigned int * pdwRcvLen);
unsigned int bsp_write_pll(unsigned int dwOffset,unsigned int dwLen ,unsigned char *pucBuf, unsigned int * pdwSndLen);

#ifdef __cplusplus
}
#endif

#endif



