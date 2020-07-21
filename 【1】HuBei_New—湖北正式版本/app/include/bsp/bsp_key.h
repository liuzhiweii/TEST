/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：bsp_drvKey.h
* 文件标识： 
* 内容摘要：按键中断接口
* 其它说明： 
* 当前版本： 
* 作    者： 
* 完成日期： 
************************************************************************/
#ifndef _BSP_OSS_KEY_H
#define _BSP_OSS_KEY_H
//使能按键中断
#define    KEY_ENABLE_MODE    (0x00)
//禁止按键中断
#define    KEY_DISABLE_MODE   (0x01)

#define BSP_DRV_KEY_LINUX_DEVICE "/dev/misc/drv_key"


unsigned int bsp_key_init(void);
//阻塞读，返回成功表示有按键中断
unsigned int bsp_key_read(unsigned char* pucDataPacket,unsigned int dwDataLen,unsigned int *pdwReadLen);

unsigned int bsp_key_ctrl(unsigned int dwCtrlMod);
#endif/*  _BSP_OSS_KEY_H  */

