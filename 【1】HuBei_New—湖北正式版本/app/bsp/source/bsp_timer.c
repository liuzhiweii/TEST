/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： timerUsr.c
* 文件标识： 
* 内容摘要：timer驱动实现用户态接口程序
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

#include "timer_def.h"

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <stdio.h>



/***********************************************************
 *                                       常量定义                                       *
***********************************************************/


/***********************************************************
*                             文件内部使用的宏                             *
***********************************************************/
#define BSP_DRV_TIMER_USR_CODE_DEBUG

/***********************************************************
*                     文件内部使用的数据类型                    *
***********************************************************/


/***********************************************************
 *                                      全局变量                                         *
***********************************************************/

volatile T_TimerAddr *g_pTimerUsrSpaceBaseAddr = NULL;


/***********************************************************
 *                                      本地变量                                         *
***********************************************************/

static volatile int s_TimerFd = -1;



/**************************************************************************
* 函数名称：bsp_timer_init
* 功能描述：timer模块初始化函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_timer_init(void)
{
    if (s_TimerFd < 0)
    {
        s_TimerFd = open(BSP_DRV_TIMER_LINUX_DEVICE, O_RDWR);
		if (s_TimerFd > 0)
        {
            g_pTimerUsrSpaceBaseAddr = (T_TimerAddr *)mmap(0, BSP_DRV_TIMER_ADDR_WIDTH, 
                                                      PROT_READ | PROT_WRITE, 
                                                      MAP_SHARED, s_TimerFd, 0);
            
			if (MAP_FAILED == (void *)g_pTimerUsrSpaceBaseAddr)
            {
			    printf("mmap funtion in Timer init error,ErrorCode = 0x%08x!\n",(unsigned int)g_pTimerUsrSpaceBaseAddr);
				return 1;
            }
            else
            {
                #ifdef BSP_DRV_TIMER_USR_CODE_DEBUG
			        printf("Timer mmap Succeed !\n");
		            printf("The base address of Timer in physical space = 0x%08x \n", (unsigned int)BSP_DRV_TIMER_BASE_ADDR);
		            printf("The base address of Timer in usr space = 0x%08x \n", (unsigned int)g_pTimerUsrSpaceBaseAddr);
			    #endif
                TIMER_INIT();
                TIMER_START();
				return 0;
            }
        }
        else
        {

			printf("open funtion in Timer init error,ErrorCode = 0x%08x!\n",s_TimerFd);
			return 1;
        }
    }
	else
	{
        printf("timer has been inited!\n");
		return 0;
	}
	
}

/**************************************************************************
* 函数名称：bsp_timer_get_counter
* 功能描述：获取当前计数值
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
**************************************************************************/	
unsigned int bsp_timer_get_counter(unsigned int *pdwCounter)
{
    unsigned int dwCurrenCounter = 0;
    GET_CURRENT_COUNTER();
    *pdwCounter = dwCurrenCounter;
    return 0;
}
/**************************************************************************
* 函数名称：bsp_timer_control
* 功能描述：启动或停止计数器
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/	
unsigned int bsp_timer_control(unsigned int dwCmd)
{
  
	/*启动定时器,从计数寄存器原有值开始计数*/
	if(BSP_DRV_TIMER_START== dwCmd) 
    {
        TIMER_START();
    }
	/*停止定时器,计数寄存器值保持为停止时刻的值*/
	else if(BSP_DRV_TIMER_STOP == dwCmd)
	{
		TIMER_STOP();
    }
	/*清零定时器,计数寄存器从零开始计数*/
	else if(BSP_DRV_TIMER_CLEAR == dwCmd)
	{
		TIMER_CLEAR();
    }
	else
	{
        return 2;
	}

	return 0;
}

/**************************************************************************
* 函数名称：bsp_timer_usleep
* 功能描述：微秒级别的延迟函数
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned int dwUsec: 要延迟的微秒数
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
void bsp_timer_usleep(unsigned int dwUsec)
{    
    unsigned int           dwEnd;
    unsigned int           dwPower = 0;
    volatile unsigned int  dwPre;
    volatile unsigned int  dwNow;
    #if (BSP_CPU_TYPE == BSP_CPU_MPC8241)       /* 13MHz, 31Bits, Subtracter */
	    bsp_timer_get_counter(&dwNow);
	    dwEnd = dwNow - dwUsec * 13;

	    do
	    {
	        dwPre = dwNow;
	        bsp_timer_get_counter(&dwNow);
	        if (dwNow > dwPre)
	        {
	            dwPower = 0x80000000;            
	        }
	        dwNow += dwPower;
	    } while ((int)(dwEnd) - (int)(dwNow) < 0);    
	#else                           /* 1MHz, 32Bits, Adder */
	    bsp_timer_get_counter(&dwNow);
	    dwEnd = dwNow + dwUsec;
	    
	    do
	    {        
	        bsp_timer_get_counter(&dwNow);
	    } while ((int)(dwNow) - (int)(dwEnd) < 0);
	#endif


    return;
}
/**************************************************************************
* 函数名称：bsp_timer_msleep
* 功能描述：毫秒级别的延迟函数
* 访问的表：无
* 修改的表：无
* 输入参数：unsigned int dwMsec: 要延迟的毫秒数
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_timer_msleep(unsigned int dwMsec)
{    
    #ifdef TIMER_USE_INT_MODE
		int sdwRet = 0;
		if(s_TimerFd <= 0)
	    {
	        return BSP_ERR_DRV_TIMER_INIT_FD;
		}
		dwMsec = dwMsec * 10;/*10K Hz*/
		if(dwMsec > 0xFFFF)
		{
            return BSP_ERR_DRV_TIMER_CONTROL_PARA;
		}
		sdwRet = ioctl(s_TimerFd,TIMER_SLEEP_SET,&dwMsec);
		if (sdwRet < 0)
		{
	        printf("bsp_timer_msleep ioctl error = 0x%08x",sdwRet);
		    return BSP_ERR_DRV_TIMER_CONTROL_PARA;
		}
	#endif
    return 0;
}	



