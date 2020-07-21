/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： verUsr.c
* 文件标识： 
* 内容摘要：ver驱动实现用户态接口程序
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

#include <fcntl.h>
#include <sys/mman.h> 


/***********************************************************
 *                                      全局变量                                         *
***********************************************************/


/***********************************************************
 *                                      本地变量                                         *
***********************************************************/
static volatile int s_sdwDrvVerFd   = -1;
static volatile unsigned int s_dwDrvVerInitFag  = 0;

/**************************************************************************
* 函数名称：unsigned int bsp_ver_init
* 功能描述：车检器模块初始化函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_ver_init(void)
{
    unsigned int dwRetVal= 0;
    if (0 == s_dwDrvVerInitFag)
    {
        s_sdwDrvVerFd = open(BSP_DRV_VER_LINUX_DEVICE, O_RDWR);
        if (-1 != s_sdwDrvVerFd)
        {
            s_dwDrvVerInitFag = 1;
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
* 函数名称：bsp_ver_read
* 功能描述：读ver帧数据函数
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
unsigned int bsp_ver_read(unsigned char* pucDataPacket,unsigned int dwDataLen,unsigned int *pdwReadLen)
{
    int sdwRet = 0;
    unsigned int dwVerEven = 0;


    if((NULL == pucDataPacket) || (NULL == pdwReadLen))
    {
        return 2;
	}

    if(s_sdwDrvVerFd <= 0)
    {
        return 3;
	}
	sdwRet = read(s_sdwDrvVerFd,pucDataPacket,dwDataLen);
	if(sdwRet < 0)
	{
		printf("bsp_ver_read read faile.error = 0x%x\r\n", sdwRet);
		return 4;
	}
	else
	{
        *pdwReadLen = sdwRet;
		return 0;
	}

}
/**************************************************************************
* 函数名称：bsp_ver_ctrl
* 功能描述：车检器控制
* 访问的表：无
* 修改的表：无
* 输入参数：dwCtrlMod：ver控制命令
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_ver_ctrl(unsigned int dwCtrlMod)
{
        int sdwRet = 0;

        sdwRet = ioctl(s_sdwDrvVerFd,dwCtrlMod);
        if (sdwRet < 0)
        {
            printf("bsp_ver_ctrl ioctl error = 0x%08x",sdwRet);
            return 5;
        }

        return 0;
}

