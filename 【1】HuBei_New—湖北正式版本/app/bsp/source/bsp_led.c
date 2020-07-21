/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： oss_led.c
* 文件标识： 
* 内容摘要：oss_led驱动实现用户态接口程序
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/

/***********************************************************
 *                                      包含头文件                                   *
 ***********************************************************/
#include "bsp.h"

/***********************************************************
 *                                       常量定义                                       *
***********************************************************/
#define OSS_LED_ALARM                                        (0)
#define OSS_LED_RUN                                          (1)
#define OSS_LED_PSAM                                         (2)

volatile unsigned short * g_pvBSPDrvLedVirtStartAddr0 = NULL;

#define WRITE_LED_REG(OFFSET,DATA)   g_pvBSPDrvLedVirtStartAddr0[OFFSET]=(T_EpldData)DATA
#define READ_LED_REG(OFFSET)         g_pvBSPDrvLedVirtStartAddr0[OFFSET]


//Led控制位索引
static unsigned int s_aLedList[][2]=
{
    {BSP_DRV_LED_ALARM_MASK, BSP_DRV_LED_ALARM_EN},
    {BSP_DRV_LED_RUN_MASK, BSP_DRV_LED_RUN_EN},
    {BSP_DRV_LED_PSAM_MASK, BSP_DRV_LED_PSAM_EN}
};

/**************************************************************************
* 函数名称：unsigned int bsp_led_set
* 功能描述：设置led状态函数
* 访问的表：无
* 修改的表：无
* 输入参数：dwLedNo:led号;dwState:状态,
*                               0:OFF;1:ON;
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
static unsigned int bsp_led_set(unsigned int dwLedIndex, unsigned int dwState)
{
    unsigned int dwData = 0;

    dwData = READ_LED_REG(BSP_DRV_LED_LED_DATA_OFFSET);
    if (dwState)
    {
        if (s_aLedList[dwLedIndex][1])
        {
            dwData |= s_aLedList[dwLedIndex][0];
        }
        else
        {
            dwData &= (~s_aLedList[dwLedIndex][0]);
        }
    }
    else
    {
        if (s_aLedList[dwLedIndex][1])
        {
            dwData &= (~s_aLedList[dwLedIndex][0]);
        }
        else
        {
            dwData |= s_aLedList[dwLedIndex][0];
        }
    }
    WRITE_LED_REG(s_aLedList[dwLedIndex][0], dwData);
    return 0;
}
/**************************************************************************
* 函数名称：unsigned int oss_led_run_ctl
* 功能描述：run  灯 控制函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_led_initl(void)
{
    g_pvBSPDrvLedVirtStartAddr0 = p_epld_start_addr;
    return 0;
}
/**************************************************************************
* 函数名称：unsigned int oss_led_run_ctl
* 功能描述：run  灯 控制函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_led_run_ctl(unsigned char ucState)
{
    unsigned short reg_value;
	
    reg_value = p_epld_start_addr[0x00DA>>1];

	reg_value = (reg_value & 0xfffd);

	ucState = (ucState == 0) ? 0x02: 0;
	
    reg_value |= ucState;

	p_epld_start_addr[0x00DA>>1] = reg_value;
	
	#if 0
    switch (ucState)
    {
        case 0:
        {
            bsp_led_set(OSS_LED_RUN, 0);
            break;
        }
        case 1:
        {
            bsp_led_set(OSS_LED_RUN, 1);
            break;
        }
        default:
        {
            break;
        }
    }
	#endif
	
    return 0;
}

/**************************************************************************
* 函数名称：unsigned int oss_led_alarm_ctl
* 功能描述：alarm  灯 控制函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：ucState:0 for off,1 for on
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_led_alarm_ctl(unsigned char ucState)
{

	unsigned short reg_value;
		
	reg_value = p_epld_start_addr[0x00DA>>1];
	
	reg_value = (reg_value & 0xfffe);
	
	ucState = (ucState == 0) ? 0x01: 0;
		
	reg_value |= ucState;
	
	p_epld_start_addr[0x00DA>>1] = reg_value;
		

    #if 0
    switch (ucState)
    {
        case 0:
        {
            bsp_led_set(OSS_LED_ALARM, 0);
            break;
        }
        case 1:
        {
            bsp_led_set(OSS_LED_ALARM, 1);
            break;
        }
        default:
        {
            break;
        }
    }
	#endif
	
    return 0;
}

/**************************************************************************
* 函数名称：unsigned int oss_led_psam_ctl
* 功能描述：PSAM  灯 控制函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：ucState:0 for off,1 for on
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_led_psam_ctl(unsigned char ucState)
{
    unsigned short reg_value;
		
	reg_value = p_epld_start_addr[0x00DA>>1];
	
	reg_value = (reg_value & 0xfffb);
	
	ucState = (ucState == 0) ? 0x04: 0;
		
	reg_value |= ucState;
	
	p_epld_start_addr[0x00DA>>1] = reg_value;
	
    #if 0
    switch (ucState)
    {
        case 0:
        {
            bsp_led_set(OSS_LED_PSAM, 0);
            break;
        }
        case 1:
        {
            bsp_led_set(OSS_LED_PSAM, 1);
            break;
        }
        default:
        {
            break;
        }
    }
	#endif
    return 0;
}



