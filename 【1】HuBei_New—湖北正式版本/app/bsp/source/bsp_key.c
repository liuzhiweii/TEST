/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： keyUsr.c
* 文件标识： 
* 内容摘要：key驱动实现用户态接口程序
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

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h> 


/***********************************************************
 *                                      全局变量                                         *
***********************************************************/


/***********************************************************
 *                                      本地变量                                         *
***********************************************************/
static volatile int s_sdwDrvKeyFd   = -1;
static volatile unsigned int s_dwDrvKeyInitFag  = 0;

/**************************************************************************
* 函数名称：unsigned int bsp_key_init
* 功能描述：按键 模块初始化函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_key_init(void)
{
    unsigned int dwRetVal= 0;
    if (0 == s_dwDrvKeyInitFag)
    {
        s_sdwDrvKeyFd = open(BSP_DRV_KEY_LINUX_DEVICE, O_RDWR);
        if (-1 != s_sdwDrvKeyFd)
        {
            s_dwDrvKeyInitFag = 1;
        }
        else
        {
            dwRetVal =  1;
        }
    }
    else
    {
        return 0;
    }
    return dwRetVal;
}
/**************************************************************************
* 函数名称：bsp_key_read
* 功能描述：读key帧数据函数
* 访问的表：无
* 修改的表：无
* 输入参数：pucDataPacket：读出数据存放目的指针
*           dwDataLen：要读取数据的长度
* 输出参数：pdwReadLen：实际读出数据的长度
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_key_read(unsigned char* pucDataPacket,unsigned int dwDataLen,unsigned int *pdwReadLen)
{
    int sdwRet = 0;

    #if 0
    if((NULL == pucDataPacket) || (NULL == pdwReadLen))
    {
        return BSP_ERROR_DRV_KEY_READ_FRAME_PARA;
	}
	#endif
    if(s_sdwDrvKeyFd <= 0)
    {
        return 2;
	}
	sdwRet = read(s_sdwDrvKeyFd,pucDataPacket,dwDataLen);
	if(sdwRet < 0)
	{
		printf("bsp_key_read read faile.error = 0x%x\r\n", sdwRet);
		return 3;
	}
	else
	{
        *pdwReadLen = sdwRet;
		return 0;
	}

}
/**************************************************************************
* 函数名称：bsp_key_ctrl
* 功能描述：key控制
* 访问的表：无
* 修改的表：无
* 输入参数：dwCtrlMod：key控制命令
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_key_ctrl(unsigned int dwCtrlMod)
{
        int sdwRet = 0;

        sdwRet = ioctl(s_sdwDrvKeyFd,dwCtrlMod);
        if (sdwRet < 0)
        {
            printf("bsp_key_ctrl ioctl error = 0x%08x",sdwRet);
            return 4;
        }

        return 0;
}


