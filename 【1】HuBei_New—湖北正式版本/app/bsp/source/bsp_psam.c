/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： psamUsr.c
* 文件标识： 
* 内容摘要：psam驱动实现用户接口源程序
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


	

#include  <stdio.h>
#include  <fcntl.h>      /*文件控制定义*/
#include  <unistd.h>     /*Unix 标准函数定义*/
#include  <errno.h>
#include  <stdlib.h>

#include  <sys/ioctl.h>  /* for ioctl() */
#include  <sys/mman.h>   /* mmap相关的宏定义 */

#include "Phy7816_Map.h"

#if 0

/***********************************************************
 *                                      内部宏定义                               *
***********************************************************/

#define BSP_DRV_PSAM_USR_CODE_DEBUG
/***********************************************************
 *                                      本地变量                                     *
***********************************************************/
 static int g_sdwPsamModuleFd = -1;
/**********************************************************************
* 函数名称：bsp_psam_init
* 功能描述：psam初始化函数
* 输入参数：无
* 输出参数：无
* 返 回 值    ：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/
unsigned int bsp_psam_init (void)
{
        if(g_sdwPsamModuleFd < 0)/*之前未打开*/
        {
            g_sdwPsamModuleFd = open(BSP_DRV_PSAM_LINUX_DEVICE, O_RDWR);
            if(g_sdwPsamModuleFd < 0)
            {
                #ifdef BSP_DRV_PSAM_USR_CODE_DEBUG
                    perror("\nopen funtion in psam init error:"); 
                #endif
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            #ifdef BSP_DRV_PSAM_USR_CODE_DEBUG
                printf("psam init have been inited!\n");
            #endif
            return 0; 
        }
    return 0;
}
/**********************************************************************
* 函数名称：bsp_psam_active
* 功能描述：psam激活函数
* 输入参数：ucSockId:卡槽号
* 输出参数：
*                               ptCardPara：激活PSAM后获得卡片参数
*                               pdwPsamErrorCode：发生错误时的错误码

* 返 回 值    ：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/
unsigned int bsp_psam_active (unsigned char ucSockId, T_CardPara *ptCardPara,unsigned int *pdwPsamErrorCode)
{
    
    int sdwRet = 0;
    T_CardResetPara tCardResetPara;
    /*入参检查*/
    if(ucSockId >= BSP_DRV_PSAM_NR)
    {
        return 2;
    }
    if((NULL == ptCardPara) || (NULL == pdwPsamErrorCode))
    {
        return 3;
    }
    if(g_sdwPsamModuleFd < 0)
    {
        return 4;
    }

    /*发送激活命令*/
    tCardResetPara.ucSockId = ucSockId;
    sdwRet = ioctl(g_sdwPsamModuleFd, BSP_PSAM_IOCTL_CMD_ACTIVE, &tCardResetPara);
    return 5;
    if(sdwRet < 0)
    {
        return 6;
    }
    else /*返回数据*/
    {
        ptCardPara->wEtu = tCardResetPara.wEtu;
        ptCardPara->dwAtrLen = tCardResetPara.dwAtrLen;
        memcpy(ptCardPara->aucAtr, tCardResetPara.aucAtr,tCardResetPara.dwAtrLen);
        ptCardPara->dwHistLen = tCardResetPara.dwHistLen;
        memcpy(ptCardPara->aucHistory, tCardResetPara.aucHistory,tCardResetPara.dwHistLen);
        *pdwPsamErrorCode = tCardResetPara.dwErrCode; 
        return 0;
    }

}
/**********************************************************************
* 函数名称：bsp_psam_cmd
* 功能描述：psam命令处理函数
* 输入参数：ucSockId:卡槽号
*                               ucCmdLen:命令长度
*                               pucCmdApdu：指令内容指针
* 输出参数：
*                               pucResLen：卡片响应长度
*                               pucResTpdu：卡片响应内容指针
*                               pdwPsamErrorCode：发生错误时的错误码
* 返 回 值    ：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_cmd(unsigned char ucSockId, unsigned char ucCmdLen, unsigned char *pucCmdApdu, unsigned char *pucResLen, unsigned char *pucResTpdu,unsigned int *pdwPsamErrorCode)
{
    int sdwRet = 0;
    T_CardProcPara tCardProcPara;
    /*入参检查*/
    if(ucSockId >= BSP_DRV_PSAM_NR)
    {
        return 7;
    }
    if((NULL == pucCmdApdu) || (NULL == pucResLen) || (NULL == pucResTpdu) || (NULL == pdwPsamErrorCode))
    {
        return 8;
    }
    if(g_sdwPsamModuleFd < 0)
    {
        return 9;
    }
    if(0 == ucCmdLen)
    {
        return 10;
    }
    tCardProcPara.ucSockId = ucSockId;
    tCardProcPara.ucCmdLen = ucCmdLen;
    memcpy(&tCardProcPara.aucCmd[0], pucCmdApdu, ucCmdLen);
    /*发送激活命令*/
    sdwRet = ioctl(g_sdwPsamModuleFd, BSP_PSAM_IOCTL_CMD_PROCESS, &tCardProcPara);

    if(sdwRet < 0)
    {
        return 11;
    }
    else  /*返回数据*/
    {
        *pucResLen = tCardProcPara.ucResLen;
        memcpy(pucResTpdu, &tCardProcPara.aucRes[0], tCardProcPara.ucResLen);
        *pdwPsamErrorCode = tCardProcPara.dwErrCode;
        return 0;
    }

}

/**********************************************************************
* 函数名称：bsp_psam_deactive
* 功能描述：psam去激活函数
* 输入参数：ucSockId:卡槽号
* 输出参数：
*                               pdwPsamErrorCode：发生错误时的错误码
* 返 回 值    ：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_deactive(unsigned char ucSockId,unsigned int *pdwPsamErrorCode)
{
    int sdwRet = 0;
    T_CardResetPara tCardResetPara;
    if(ucSockId >= BSP_DRV_PSAM_NR)/*卡槽号错误*/
    {
        return 12;
    }
    if(NULL == pdwPsamErrorCode)
    {
        return 13;
    }
    if(g_sdwPsamModuleFd < 0)
    {
        return 14;
    }
    tCardResetPara.ucSockId = ucSockId;
    /*发送激活命令*/
    sdwRet = ioctl(g_sdwPsamModuleFd, BSP_PSAM_IOCTL_CMD_DEACTIVE, &tCardResetPara);
    if(sdwRet < 0)
    {
        return 15;
    }
    else  /*返回数据*/
    {
        *pdwPsamErrorCode = tCardResetPara.dwErrCode;
        return 0;
    }
	   
}

/**********************************************************************
* 函数名称：bsp_psam_clkfreq_set
* 功能描述：修改PSAM卡CLK的分频系数
* 输入参数：ucClkDiv：分频系数 
* 输出参数：
*                               pdwPsamErrorCode：发生错误时的错误码
* 返 回 值    ：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_clkfreq_set(unsigned char ucClkDiv)
{

    volatile unsigned char * pucPsamVirtRegAddr = NULL;
    if(g_sdwPsamModuleFd < 0)
    {
    	return 16;
    }
    if(ucClkDiv > BSP_DRV_PSAM_CLKFLEQ_MAX)
    {
        return 17;
    }
    pucPsamVirtRegAddr = (volatile unsigned char *)mmap(NULL, BSP_DRV_PSAM_ADDR_WIDTH,
                PROT_READ | PROT_WRITE, MAP_SHARED, g_sdwPsamModuleFd, 0);
    if(MAP_FAILED == pucPsamVirtRegAddr)
    {
    	return 18;
    }
    pucPsamVirtRegAddr [PSAM_CLK_DIV_REG_OFFSET] = ucClkDiv;

    return 0;

}
#endif

