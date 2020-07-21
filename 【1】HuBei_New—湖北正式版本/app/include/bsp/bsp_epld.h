/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：bsp_drvEpld.h
* 文件标识：
* 内容摘要：EPLD 驱动头文件
* 其它说明：
* 当前版本：
* 作    者：       
* 完成日期：
* 修改日期:    
************************************************************************/
#ifndef _BSP_DRV_EPLD_H_
#define _BSP_DRV_EPLD_H_

#ifdef __cplusplus
extern "C"
{
#endif


/**************************************************************************
*                                                        常量                                                            *
**************************************************************************/


/**************************************************************************
*                                                     宏定义                                                          *
**************************************************************************/


/**************************************************************************
*                                                  数据类型                                                       *
**************************************************************************/
/*  epld的数据类型定义*/

typedef unsigned short* T_EpldAddr;
typedef unsigned short  T_EpldData;


/**************************************************************************
*                                              全局变量声明                                                *
**************************************************************************/
/*  epld起始虚拟地址*/
extern volatile unsigned short * p_epld_start_addr;

/*获取EPLD寄存器地址*/
#define BSP_DRV_EPLD_LINUX_DEVICE "/dev/misc/drv_epld"

#define BSP_DRV_EPLD_ADDR_WIDTH (0x400000)
#define BSP_DRV_EPLD_PORT_WIDTH (0x10)
#undef BSP_EPLD_INT_CTRL_USE


#define EPLD_REG_ADDR(OFFSET)        ((p_epld_start_addr) + OFFSET)
#define WRITE_EPLD_REG(OFFSET,DATA)   p_epld_start_addr[OFFSET]=(T_EpldData)DATA
#define READ_EPLD_REG(OFFSET)         p_epld_start_addr[OFFSET]


/**************************************************************************
*                                           全局函数原型                                                   *
**************************************************************************/
/*  epld模块初始化接口*/
unsigned int bsp_epld_init(void);
unsigned int bsp_epld_read(unsigned int dwRegOffset, unsigned short * ptRegValue);
unsigned int bsp_epld_write(unsigned int dwRegOffset, T_EpldData tRegValue);

#ifdef __cplusplus
}
#endif

		
#endif/* _BSP_DRV_EPLD_H_  */

