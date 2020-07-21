/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： flash.h
* 文件标识： 
* 内容摘要：模块内部头文件
* 其它说明：  
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/
#ifndef _FLASH_H_
#define _FLASH_H_

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
//#define FLASH_DEBUG
struct mtd_partition {
	char *name;			/* identifier string */
	unsigned int size;			/* partition size */
	unsigned int offset;		/* offset within the master MTD space */
	unsigned int mask_flags;		/* master MTD flags to mask out for this partition */
};

typedef struct tagT_BSPDrvFlashMtd
{
	char acMtdDevName[16];   /*MTD设备名*/
	unsigned int dwMtdOffset;      /*MTD设备地址偏移*/
	unsigned int dwMtdSize;        /*MTD大小*/
    char acMtdName[64];      /*MTD名称*/
} T_BSPDrvFlashMtd;



#define SYSTEM_MTD_MAX         24

#define BSP_DRV_NOR_SECTOR_SIZE         0x20000
#define BSP_DRV_NAND_SECTOR_SIZE       0x20000
#endif
