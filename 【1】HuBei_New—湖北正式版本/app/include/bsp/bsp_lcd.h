/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：
* 文件标识：
* 内容摘要：lcd 驱动头文件
* 其它说明：
* 当前版本：
* 作    者：       
* 完成日期：
* 
************************************************************************/

#ifndef _BSP_DRV_LCD_H_
#define _BSP_DRV_LCD_H_

unsigned int bsp_lcd_init(void);
unsigned int bsp_lcd_show_string(unsigned char ucxpos, unsigned char ucypos, unsigned char *pstr);
unsigned int bsp_lcd_ctrl(unsigned char ucCtl);
void bsp_clear_oled_row(unsigned char row, unsigned char color);
#endif

