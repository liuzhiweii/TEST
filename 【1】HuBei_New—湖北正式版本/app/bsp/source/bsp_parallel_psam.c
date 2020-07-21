/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：ParallelPsamUsr.h
* 文件标识： 
* 内容摘要：并行psam驱动实现用户接口源程序
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/

/***********************************************************
 *                包含头文件                               *
 ***********************************************************/
#include "bsp.h"


	
#include  <stdio.h>
#include  <fcntl.h>      /*文件控制定义*/
#include  <unistd.h>     /*Unix 标准函数定义*/
#include  <errno.h>
#include  <stdlib.h>

#include  <sys/ioctl.h>  /* for ioctl() */
#include  <sys/mman.h>   /* mmap相关的宏定义 */
#include <asm-generic/ioctl.h> 





/***********************************************************
 *                内部宏定义                               *
***********************************************************/

//#define BSP_DRV_PSAM_USR_CODE_DEBUG

/***********************************************************
 *               本地全局变量                              *
***********************************************************/
static T_UsrPsamDevice s_atUsrPsamDev[]=
{
    {0,BSP_DRV_PSAM0_LINUX_DEVICE,-1},
    {0,BSP_DRV_PSAM1_LINUX_DEVICE,-1},
    {0,BSP_DRV_PSAM2_LINUX_DEVICE,-1},
    {0,BSP_DRV_PSAM3_LINUX_DEVICE,-1}
};


/**********************************************************************
* 函数名称：bsp_psam_init
* 功能描述：psam初始化函数
* 输入参数：无
* 输出参数：无
* 返 回 值：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/
unsigned int bsp_psam_init (void)
{
    unsigned char ucLoop = 0;
    for(ucLoop = 0;ucLoop < BSP_DRV_PSAM_NR;ucLoop++)
    {
        if(0 == s_atUsrPsamDev[ucLoop].ucStatus)/*之前未打开*/
        {
            s_atUsrPsamDev[ucLoop].sdwPsamDevFd = open(s_atUsrPsamDev[ucLoop].ucDevName, O_RDWR);
            if(s_atUsrPsamDev[ucLoop].sdwPsamDevFd < 0)
            {
                printf("\nopen psam %d error,errno = 0x%08x",ucLoop,errno);
                perror(":"); 
                return 1;
            }
            else
            {
                s_atUsrPsamDev[ucLoop].ucStatus = 1;
            }
        }    
        else
        {
            #ifdef BSP_DRV_PSAM_USR_CODE_DEBUG
                printf("\npsam %d init have been inited!\n",ucLoop);
            #endif
        }
    }
    return 0;
}

/**********************************************************************
* 函数名称：bsp_psam_active
* 功能描述：psam激活函数
* 输入参数：ucSockId:卡槽号
* 输出参数：ptCardPara：激活PSAM后获得卡片参数
*           pdwPsamErrorCode：发生错误时的错误码

* 返 回 值：错误码
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
    if(s_atUsrPsamDev[ucSockId].sdwPsamDevFd < 0)
    {
        return 4;
    }
    /*发送激活命令*/
    sdwRet = ioctl(s_atUsrPsamDev[ucSockId].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_ACTIVE, &tCardResetPara);
    if(sdwRet < 0)
    {
        return 5;
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
*           ucCmdLen:命令长度
*           pucCmdApdu：指令内容指针
* 输出参数：
*           pucResLen：卡片响应长度
*           pucResTpdu：卡片响应内容指针
*           pdwPsamErrorCode：发生错误时的错误码
* 返 回 值 ：错误码
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
        return 6;
    }
    if((NULL == pucCmdApdu) || (NULL == pucResLen) || (NULL == pucResTpdu) || (NULL == pdwPsamErrorCode))
    {
        return 7;
    }
    if(s_atUsrPsamDev[ucSockId].sdwPsamDevFd < 0)
    {
        return 8;
    }
  
    if(0 == ucCmdLen)
    {
        return 9;
    }
    tCardProcPara.ucSockId = ucSockId;
    tCardProcPara.ucCmdLen = ucCmdLen;
    memcpy(&tCardProcPara.aucCmd[0], pucCmdApdu, ucCmdLen);
    /*发送激活命令*/
    sdwRet = ioctl(s_atUsrPsamDev[ucSockId].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_PROCESS, &tCardProcPara);
    if(sdwRet < 0)
    {
        return 10;
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
* 输出参数：pdwPsamErrorCode：发生错误时的错误码
* 返 回 值：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_deactive(unsigned char ucSockId,unsigned int *pdwPsamErrorCode)
{
    int sdwRet = 0;
    /*入参检测*/
    if(ucSockId >= BSP_DRV_PSAM_NR)
    {
        return 11;
    }
    if(NULL == pdwPsamErrorCode)
    {
        return 12;
    }
  
    if(s_atUsrPsamDev[ucSockId].sdwPsamDevFd < 0)
    {
        return 13;
    }
    /*发送去激活命令*/
    sdwRet = ioctl(s_atUsrPsamDev[ucSockId].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_DEACTIVE);
    if(sdwRet < 0)
    {
        return 14;
    }
    return 0;
}

/**********************************************************************
* 函数名称：bsp_psam_clkfreq_set
* 功能描述：修改PSAM卡CLK的分频系数
* 输入参数：ucClkDiv：分频系数 
* 返 回 值：错误码
* 其它说明：无
* 修改日期	   版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_clkfreq_set(unsigned char ucClkDiv)
{
    int sdwRet = 0;
    if(s_atUsrPsamDev[0].sdwPsamDevFd < 0)
	{
		return 15;
	}
	if(ucClkDiv > BSP_DRV_PSAM_CLKFLEQ_MAX)
	{
        return 16;
	}
	sdwRet = ioctl(s_atUsrPsamDev[0].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_CLKSET, &ucClkDiv);
    if(sdwRet < 0)
    {
        return 17;
    }
    return 0;		
}

/**********************************************************************
* 函数名称：bsp_psam_voltage_set
* 功能描述：修改PSAM卡的供电电压
* 输入参数：ucSockId:卡槽号;电压值 
* 返 回 值：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_voltage_set(unsigned char ucSockId,unsigned char ucVoltage)
{
    int sdwRet = 0;
    /*入参检测*/
    if(ucSockId >= BSP_DRV_PSAM_NR)
    {
        return 18;
    }
    if(s_atUsrPsamDev[ucSockId].sdwPsamDevFd < 0)
	{
		return 19;
	}
	if((ucVoltage != PSAM_VOLTAGE_3V3) && (ucVoltage != PSAM_VOLTAGE_1V8))
	{
        return 20;
	}
	sdwRet = ioctl(s_atUsrPsamDev[ucSockId].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_VOLTAGESET, &ucVoltage);
    if(sdwRet < 0)
    {
        return 21;
    }
    return 0;		
}

/**********************************************************************
* 函数名称：bsp_psam_pps_set
* 功能描述：修改PSAM卡是否倍频
* 输入参数：ucSockId:卡槽号;ucPPSFlag
* 返 回 值：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_pps_set(unsigned char ucSockId,unsigned char ucPPSFlag)
{
    int sdwRet = 0;
    /*入参检测*/
    if(ucSockId >= BSP_DRV_PSAM_NR)
    {
        return 22;
    }
    if(s_atUsrPsamDev[ucSockId].sdwPsamDevFd < 0)
	{
		return 23;
	}
	if((ucPPSFlag != 0) && (ucPPSFlag != 1))
	{
        return 24;
	}
	sdwRet = ioctl(s_atUsrPsamDev[ucSockId].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_SETPPS_STATE, &ucPPSFlag);
    if(sdwRet < 0)
    {
        return 25;
    }
    return 0;		
}


/**********************************************************************
* 函数名称：bsp_psam_etu_set
* 功能描述：修改PSAM卡是否使用默认ETU
* 输入参数：ucSockId:卡槽号;ucEtuFlag
* 返 回 值：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/	
unsigned int bsp_psam_etu_set(unsigned char ucSockId,unsigned char ucEtuFlag)
{
    int sdwRet = 0;
    /*入参检测*/
    if(ucSockId >= BSP_DRV_PSAM_NR)
    {
        return 26;
    }
    if(s_atUsrPsamDev[ucSockId].sdwPsamDevFd < 0)
	{
		return 27;
	}
	if((ucEtuFlag != 0) && (ucEtuFlag != 1))
	{
        return 28;
	}
	sdwRet = ioctl(s_atUsrPsamDev[ucSockId].sdwPsamDevFd, BSP_PSAM_IOCTL_CMD_SETETU_STATE, &ucEtuFlag);
    if(sdwRet < 0)
    {
        return 29;
    }
    return 0;		
}

