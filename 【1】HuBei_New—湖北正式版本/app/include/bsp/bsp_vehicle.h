/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：bsp_drvVer.h
* 文件标识：
* 内容摘要：车检器 驱动头文件
* 其它说明：
* 当前版本：
* 作    者：       
* 完成日期：
************************************************************************/

#ifndef _BSP_DRV_VER_H_
#define _BSP_DRV_VER_H_
/**************************************************************************
*                                           全局函数原型                                                   *
**************************************************************************/

#define BSP_DRV_VER_LINUX_DEVICE "/dev/misc/drv_ver"

    //使能按键中断
#define    VER_ENABLE_MODE    (0x00)
    //禁止按键中断
#define    VER_DISABLE_MODE   (0x01)
    
unsigned int bsp_ver_init(void);
//阻塞读，返回成功表示有按键中断
unsigned int bsp_ver_read(unsigned char* pucDataPacket,unsigned int dwDataLen,unsigned int *pdwReadLen);

unsigned int bsp_ver_ctrl(unsigned int dwCtrlMod);
#endif/* _BSP_DRV_VER_H_  */

