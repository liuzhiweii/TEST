/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：bsp_drvWtd.h
* 文件标识：
* 内容摘要：WTD 驱动头文件
* 其它说明：
* 当前版本：
* 作    者：      
* 完成日期：
************************************************************************/

#ifndef _BSP_DRV_WTD_H_
#define _BSP_DRV_WTD_H_
/**************************************************************************
*                                           全局函数原型                                                   *
**************************************************************************/

#define BSP_DRV_WTD_HWFEED (1)
#define BSP_DRV_WTD_WMS_DATA_OFFSET (0xBC>>1)
#define BSP_DRV_WTD_WMS_MASK (0x01)
#define BSP_DRV_WTD_WMS (0x0)
#define BSP_DRV_WTD_WMS_DIR_OFFSET (0x0)

#define BSP_DRV_WTD_START (0)
#define BSP_DRV_WTD_STOP (1)
#define BSP_DRV_WTD_FEED_TYPE (1)
#define BSP_DRV_WTD_FEED (1)
/*
 * WST configuration
 */

#define BSP_DRV_WTD_WST_DIR_ADDR (0x)
#define BSP_DRV_WTD_WST_SET_ADDR (0x)
#define BSP_DRV_WTD_WST_CLR_ADDR (0x)
#define BSP_DRV_WTD_WST_MASK (0x01)
/*
 * WST configuration
 */
#define BSP_DRV_WTD_WST_DATA_OFFSET (0xB8>>1)
#define BSP_DRV_WTD_WST_DIR_OFFSET (0x0)

/*
 * WDI configuration
 */
#define BSP_DRV_WTD_WDI_DATA_OFFSET (0xC0>>1)
#define BSP_DRV_WTD_WDI_DIR_OFFSET (0x0)
#define BSP_DRV_WTD_WDI_MASK (0x01)

/*
 * WMS configuration
 */
#define BSP_DRV_WTD_HWFEED (1)
#define BSP_DRV_WTD_WMS_DATA_OFFSET (0xBC>>1)
#define BSP_DRV_WTD_WMS_MASK (0x01)
#define BSP_DRV_WTD_WMS (0x0)
#define BSP_DRV_WTD_WMS_DIR_OFFSET (0x0)


/*  初始化WTD模块接口*/
unsigned int bsp_wtd_init(void);
/*  使能WTD接口*/
unsigned int bsp_wtd_enable(void);
/*  设置wtd溢出时间接口*/
unsigned int bsp_wtd_setTimer(unsigned int dwTimeMs);
/*  禁用WTD 接口*/
unsigned int bsp_wtd_disable(void);
/*  喂狗接口*/
unsigned int bsp_wtd_feed(void);
/*  硬件喂狗接口*/
unsigned int bsp_wtd_hwFeed(void);

		
#endif/* _BSP_DRV_WTD_H_  */

