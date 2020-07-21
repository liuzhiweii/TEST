/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： wtd.c
* 文件标识： 
* 内容摘要：wtd驱动实现用户态接口程序
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/

/***********************************************************
 *                                      包含头文件                                   *
 ***********************************************************/
#include "wtd_epld_driver.h"
#include "wtd_driver.h"

/***********************************************************
*                             文件内部使用的宏                             *
***********************************************************/
#define BSP_DRV_WTD_WST_DATA READ_EPLD_REG(BSP_DRV_WTD_WST_DATA_OFFSET)
#define BSP_DRV_WTD_WDI_DATA READ_EPLD_REG(BSP_DRV_WTD_WDI_DATA_OFFSET)
#define BSP_DRV_WTD_WMS_DATA READ_EPLD_REG(BSP_DRV_WTD_WMS_DATA_OFFSET)
#define BSP_DRV_WTD_WDI_DIR  (0)
#define BSP_DRV_WTD_WMS_DIR  (0)
#define BSP_DRV_WTD_WST_DIR  (0)




/***********************************************************
 *                                       常量定义                                       *
***********************************************************/


/***********************************************************
*                     文件内部使用的数据类型                    *
***********************************************************/


/***********************************************************
 *                                      全局变量                                         *
***********************************************************/


/***********************************************************
 *                                      本地变量                                         *
***********************************************************/


/***********************************************************
 *                                      全局函数                                         *
***********************************************************/
/**************************************************************************
* 函数名称：unsigned int bsp_wtd_init
* 功能描述：wtd 模块初始化函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_wtd_init(void)
{

	//(void)bsp_wtd_disable();
	return 0;
}

/**************************************************************************
* 函数名称：unsigned int bsp_wtd_enable
* 功能描述：开启wtd函数,在6700中wtd启动寄存器只能写一次
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_wtd_enable(void)
{
	unsigned char ucWtdFlag = 0;
	#if BSP_DRV_WTD_HWFEED == 1
		#if BSP_DRV_WTD_WMS == 0
			BSP_DRV_WTD_WMS_DATA |= BSP_DRV_WTD_WMS_MASK;
		#else
			BSP_DRV_WTD_WMS_DATA &= ~BSP_DRV_WTD_WMS_MASK;
		#endif
	#endif
	ucWtdFlag = BSP_DRV_WTD_START;
	if (0 == ucWtdFlag)
	{
		BSP_DRV_WTD_WST_DATA &= ~BSP_DRV_WTD_WST_MASK;
	}
	else
	{
		BSP_DRV_WTD_WST_DATA |= BSP_DRV_WTD_WST_MASK;
	}
	return 0;
}


/**************************************************************************
* 函数名称：unsigned int bsp_wtd_setTimer
* 功能描述：设置wtd溢出时间函数
* 访问的表：无
* 修改的表：无
* 输入参数：dwTimeMs:时间,单位为ms
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：目前遇到的硬件单板均不支持此功能
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_wtd_setTimer(unsigned int dwTimeMs)
{
	return 0;
}


/**************************************************************************
* 函数名称：unsigned int bsp_wtd_disable
* 功能描述：禁用wtd函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_wtd_disable(void)
{
	unsigned char ucWtdFlag = 0;
	
	#if BSP_DRV_WTD_HWFEED == 1
		#if BSP_DRV_WTD_WMS == 0
			BSP_DRV_WTD_WMS_DATA |= BSP_DRV_WTD_WMS_MASK;
		#else
			BSP_DRV_WTD_WMS_DATA &= ~BSP_DRV_WTD_WMS_MASK;
		#endif
	#endif
	ucWtdFlag = BSP_DRV_WTD_STOP;
	if (0 == ucWtdFlag)
	{
		BSP_DRV_WTD_WST_DATA &= ~BSP_DRV_WTD_WST_MASK;
	}
	else
	{
		BSP_DRV_WTD_WST_DATA |= BSP_DRV_WTD_WST_MASK;
	}
	return 0;
}


/**************************************************************************
* 函数名称：unsigned int bsp_wtd_feed
* 功能描述：喂狗函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_wtd_feed(void)
{
	#if BSP_DRV_WTD_FEED_TYPE == 1/*  手动反转*/
		unsigned int dwWdi;
		dwWdi = BSP_DRV_WTD_WDI_DATA;
		dwWdi = ((~(dwWdi & BSP_DRV_WTD_WDI_MASK)) & BSP_DRV_WTD_WDI_MASK) |
			      (dwWdi & (~BSP_DRV_WTD_WDI_MASK));
		BSP_DRV_WTD_WDI_DATA = dwWdi;
	#else/*  自动反转*/
		if (0 == BSP_DRV_WTD_FEED)
		{
			BSP_DRV_WTD_WDI_DATA &= ~BSP_DRV_WTD_WDI_MASK;
		}
		else
		{
			BSP_DRV_WTD_WDI_DATA |= BSP_DRV_WTD_WDI_MASK;
		}
	#endif
	return 0;
}

/**************************************************************************
* 函数名称：unsigned int bsp_wtd_feed
* 功能描述：启动硬件喂狗函数，调用bsp_wtd_enable退出硬件喂狗
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_wtd_hwFeed(void)
{
	#if BSP_DRV_WTD_HWFEED == 1
		#if BSP_DRV_WTD_WMS == 1
			BSP_DRV_WTD_WMS_DATA |= BSP_DRV_WTD_WMS_MASK;
		#else
			BSP_DRV_WTD_WMS_DATA &= ~BSP_DRV_WTD_WMS_MASK;
		#endif
	#endif
	return 0;
}

