/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： bsp_flash.h
* 文件标识： 
* 内容摘要： flash模块对外接口头文件
* 其它说明： 
* 当前版本： 
* 作    者： 
* 完成日期：
* 
************************************************************************/


#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_


#define NOR_FLASH   0         /*NOR FALSH*/
#define NAND_FLASH  1         /*NAND FALSH*/



unsigned int bsp_flash_init(void);
unsigned int bsp_flash_read(unsigned int dwFlashId, unsigned int dwOffset, unsigned int dwLen, unsigned char * pucBuf, unsigned int *pdwReadLen);
unsigned int bsp_flash_write(unsigned int dwFlashId, unsigned int dwOffset, unsigned int dwLen, unsigned char * pucBuf, unsigned int *pdwWriteLen);
unsigned int bsp_flash_erase(unsigned int dwFlashId, unsigned int dwOffset, unsigned int dwLen);
unsigned int bsp_flash_size(void);
unsigned int bsp_flash_totalsize(unsigned int dwFlashId,unsigned int *pdwSize);


#endif

