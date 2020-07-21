/************************************************************************
* 版权所有 (C)2009, 深圳市中兴通讯股份有限公司。
* 
* 文件名称：usp_drvEpld.h
* 文件标识：
* 内容摘要：EPLD 驱动头文件
* 其它说明：
* 当前版本：V01.00.00
* 作    者：       余海峰
* 完成日期：2009-10-10
* 修改日期:    2011-09-22    修改人: cdj wuqi  
************************************************************************/
#ifndef _USP_DRV_EPLD_H_
#define _USP_DRV_EPLD_H_

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
#if USP_DRV_EPLD_PORT_WIDTH == 8
    typedef BYTE*   unsigned short *;
    typedef BYTE  T_EpldData;
#elif USP_DRV_EPLD_PORT_WIDTH == 16
    typedef WORD16* unsigned short *;
    typedef WORD16  T_EpldData;
#elif USP_DRV_EPLD_PORT_WIDTH == 32
    typedef WORD32* unsigned short *;
    typedef WORD32  T_EpldData;
#else
    typedef BYTE*   unsigned short *;
    typedef BYTE  T_EpldData;

#endif

/**************************************************************************
*                                              全局变量声明                                                *
**************************************************************************/
/*  epld起始虚拟地址*/
//extern volatile unsigned short * g_pvUSPDrvEpldVirtStartAddr0;

/*获取EPLD寄存器地址*/

#define EPLD_REG_ADDR(OFFSET)        ((g_pvUSPDrvEpldVirtStartAddr0) + OFFSET)
#define WRITE_EPLD_REG(OFFSET,DATA)   g_pvUSPDrvEpldVirtStartAddr0[OFFSET]=(T_EpldData)DATA
#define READ_EPLD_REG(OFFSET)         g_pvUSPDrvEpldVirtStartAddr0[OFFSET]


/**************************************************************************
*                                           全局函数原型                                                   *
**************************************************************************/
/*  epld模块初始化接口*/
WORD32 usp_drv_epld_init(VOID);
WORD32 usp_drv_epld_read(WORD32 dwRegOffset, unsigned short * ptRegValue);
WORD32 usp_drv_epld_write(WORD32 dwRegOffset, T_EpldData tRegValue);

#if (USP_OS_TYPE == OS_FREERTOS)
    WORD32 usp_drv_epld_write_reg_hold(WORD32 dwRegOffset, T_EpldData tRegValue, BYTE uchold);
#endif
		
#endif/* _USP_DRV_EPLD_H_  */


