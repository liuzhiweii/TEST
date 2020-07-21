/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：bsp_ossLed.h
* 文件标识： 
* 内容摘要： 闪灯管理对外接口
* 其它说明： 
* 当前版本： 
* 作    者： 
* 完成日期： 
************************************************************************/
#ifndef _BSP_OSS_LED_H
#define _BSP_OSS_LED_H

#define BSP_DRV_LED_LED_DATA_OFFSET     (0xDA>>1)
#define BSP_DRV_LED_ALARM_MASK          (0x01)
#define BSP_DRV_LED_ALARM_EN            (0x00)
#define BSP_DRV_LED_RUN_MASK            (0x02)
#define BSP_DRV_LED_RUN_EN              (0x00)
#define BSP_DRV_LED_PSAM_MASK           (0x04)
#define BSP_DRV_LED_PSAM_EN             (0x00)

unsigned int bsp_led_initl(void);
//运行灯ucState:1开 0:关
unsigned int bsp_led_run_ctl(unsigned char ucState);
//告警灯ucState:1开 0:关
unsigned int bsp_led_alarm_ctl(unsigned char ucState);
//PSAM状态指示灯ucState:1开 0:关
unsigned int bsp_led_psam_ctl(unsigned char ucState);
#endif/*  _BSP_OSS_LED_H  */

