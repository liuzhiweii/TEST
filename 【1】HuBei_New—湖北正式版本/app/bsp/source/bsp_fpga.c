/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： fpgaUsr.c
* 文件标识： 
* 内容摘要：fpga驱动实现用户态接口程序
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/
/***********************************************************
 *                                      包含头文件                                   *
 ***********************************************************/

#include "bsp/bsp_fpga.h"

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <asm-generic/ioctl.h> 
#include <stdio.h>



/***********************************************************
 *                                      全局变量                                    *
***********************************************************/
/*FPGA用户空间首地址,用于兼容旧的应用程序,
   新应用程序不建议使用*/
T_FpgaVirtAddr g_pvBSPDrvFpgaVirtStartAddr0 = NULL;


/***********************************************************
 *                                      本地变量                                    *
***********************************************************/
/*FPGA设备文件描述符*/	
static int  s_sdwFpgaFd = -1; 

/*FPGA用户空间基址*/
static T_FpgaVirtAddr  s_pFpgaUsrSpaceBaseAddr = NULL;	 


/***********************************************************
 *                                      内部宏定义                                *
***********************************************************/
/*写数据*/
#undef WRITE_FPGA_REG
#define WRITE_FPGA_REG(OFFSET,DATA)   s_pFpgaUsrSpaceBaseAddr[OFFSET]=(T_FpgaData)DATA

/*读数据*/
#undef READ_FPGA_REG
#define READ_FPGA_REG(OFFSET)         (T_FpgaData)s_pFpgaUsrSpaceBaseAddr[OFFSET]

/*打印开关*/
//#define BSP_DRV_FPGA_DEBUG


/**************************************************************************
* 函数名称：bsp_fpga_init
* 功能描述：fpga 模块初始化函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值    ：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_fpga_init(void)
{
    int sdwRet = 0;
	if (s_sdwFpgaFd < 0)/*未初始化*/
	{
	    s_sdwFpgaFd = open("/dev/misc/drv_fpga", O_RDWR);
		if (s_sdwFpgaFd > 0)
		{
             s_pFpgaUsrSpaceBaseAddr = (T_FpgaVirtAddr)mmap(0, BSP_DRV_FPGA_ADDR_WIDTH, 
                                                           PROT_READ | PROT_WRITE, 
                                                           MAP_SHARED, s_sdwFpgaFd, 0);
             
             if (NULL == s_pFpgaUsrSpaceBaseAddr)
             {
                 close(s_sdwFpgaFd);
                 return  1;
             }
			 else
			 {
                g_pvBSPDrvFpgaVirtStartAddr0 = s_pFpgaUsrSpaceBaseAddr;


			         printf("FPGA mmap Succeed !\n");
		             printf("The base address of FPGA in physical space = 0x%08x \n", (unsigned int)BSP_DRV_FPGA_BASE_ADDR);
		             printf("The base address of FPGA in usr space = 0x%08x \n", (unsigned int)s_pFpgaUsrSpaceBaseAddr);

				 return 0;
		     }
         }
		 else
		 {
			 return 3;
		 }
		
	}
    else
    {
        printf("fpga fd have been inited\r\n");
		return 0;
	}
	
}
/**************************************************************************
* 函数名称：bsp_fpga_read_reg
* 功能描述：读FPGA寄存器函数
* 访问的表：无
* 修改的表：无
* 输入参数：dwRegOffset：FPGA寄存器偏移
* 输出参数：pwRegData：独到寄存器数据的指针
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_fpga_read_reg(unsigned int dwRegOffset,T_FpgaData *ptRegData)
{
    unsigned int sdwRet = 0;

    if(s_sdwFpgaFd < 0)
    {
        sdwRet = bsp_fpga_init();
        if(sdwRet != 0)
        {
            return sdwRet;
        }
    }

    if(NULL == ptRegData)
    {
        return 4;
	}
	if(dwRegOffset > BSP_DRV_FPGA_ADDR_WIDTH)
	{
        return 5;
	}
	*ptRegData = READ_FPGA_REG(dwRegOffset);
	#if 0
	sdwRet = ioctl(s_sdwFpgaFd,FPGA_READ_REG, &dwRegOffset);
	if (sdwRet < 0)
	{
        printf("bsp_fpga_read_reg ioctl error = 0x%08x\r\n",sdwRet);
	    return BSP_ERROR_DRV_FPGA_WRITE_FRAME_IOCTL;
	}
	*ptRegData = dwRegOffset;
    #endif
    return 0;
}
/**************************************************************************
* 函数名称：bsp_fpga_write_reg
* 功能描述：写FPGA寄存器函数
* 访问的表：无
* 修改的表：无
* 输入参数：wRegOffset：FPGA寄存器偏移
*           wRegData：需要写入的数据
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/

unsigned int bsp_fpga_write_reg(unsigned int dwRegOffset,T_FpgaData tRegData)
{
    unsigned int sdwRet = 0;

    if(s_sdwFpgaFd < 0)
    {
        sdwRet = bsp_fpga_init();
        if(sdwRet != 0)
        {
            return sdwRet;
        }
    }
    
    if(dwRegOffset > BSP_DRV_FPGA_ADDR_WIDTH)
	{
        return 6;
	}
	
	WRITE_FPGA_REG(dwRegOffset,tRegData);
	//printf("bsp_fpga_write_frame write ok");
	#if 0
	sdwRet = ioctl(s_sdwFpgaFd,FPGA_WRITE_REG, &dwRegOffset);
	if (sdwRet < 0)
	{
        printf("bsp_fpga_write_reg ioctl error = 0x%08x\r\n",sdwRet);
	    return BSP_ERROR_DRV_FPGA_WRITE_FRAME_IOCTL;
	}
    #endif
	return 0;
}
/**************************************************************************
* 函数名称：bsp_fpga_write_frame
* 功能描述：写FPGA帧数据函数
* 访问的表：无
* 修改的表：无
* 输入参数：pucDataPacket：要写入的数据包指针
*           dwDataLen：要写入数据的长度
*           ucflag：写帧数据标志,唤醒模式或非唤醒模式(8900)
* 输出参数：pdwWriteLen：实际写入数据的长度
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/

unsigned int bsp_fpga_write_frame(unsigned char*pucDataPacket,unsigned int dwDataLen, unsigned char ucflag, unsigned int *pdwWriteLen)
{
    int sdwRet = 0;
	if((NULL == pucDataPacket) || (NULL == pdwWriteLen))
    {
        return 7;
	}
	/*长度是否正确*/
    if (dwDataLen > FPGA_SEND_FIFO_WIDTH)
	{
        return 8;
	}
	/*文件描述符是否正确*/
	if(s_sdwFpgaFd <= 0)
    {
        return 9;
	}
	/*设置唤醒标志*/
    if(BSP_DRV_FPGA_WAKEUP_ENABLE == ucflag)
    {
        sdwRet = ioctl(s_sdwFpgaFd,FPGA_ENABLE_WAKEUP_MODE);
	}
	else if(BSP_DRV_FPGA_WAKEUP_DISABLE == ucflag)
	{
        sdwRet = ioctl(s_sdwFpgaFd,FPGA_DISABLE_WAKEUP_MODE);
	}
	else
	{
        return 10;
	}
	if (sdwRet < 0)
	{
        printf("bsp_fpga_write_frame ioctl error = 0x%08x",sdwRet);
	    return 11;
	}
	/*发送数据*/
	sdwRet = write(s_sdwFpgaFd,pucDataPacket,dwDataLen);
	if(sdwRet < 0)
	{
       printf("bsp_fpga_write_frame write error = 0x%08x",sdwRet);
       return 12;
	}
	else
	{
       *pdwWriteLen = sdwRet;
	   return 0;
	}
}
/**************************************************************************
* 函数名称：bsp_fpga_read_frame
* 功能描述：读FPGA帧数据函数
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
unsigned int bsp_fpga_read_frame(unsigned char* pucDataPacket,unsigned int dwDataLen,unsigned int *pdwReadLen)
{
    int sdwRet = 0;
    if((NULL == pucDataPacket) || (NULL == pdwReadLen))
    {
        return 13;
	}
    if(s_sdwFpgaFd <= 0)
    {
        return 14;
	}
	sdwRet = read(s_sdwFpgaFd,pucDataPacket,dwDataLen);
	if(sdwRet < 0)
	{
		perror("\nbsp_fpga_read_frame read error:");
		return 15;
	}
	else
	{
        *pdwReadLen = sdwRet;
		return 0;
	}
}
/**************************************************************************
* 函数名称：bsp_fpga_reset
* 功能描述：FPGA 复位函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/
unsigned int bsp_fpga_reset(void)
{
    /*复位FPGA内部FIFO*/
	//FPGA_FIFO_RESET();
	return 0;

}
/**************************************************************************
* 函数名称：bsp_fpga_int_enable
* 功能描述：FPGA 中断使能函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/

unsigned int bsp_fpga_int_enable(void)
{
	int sdwRet = 0;
	if(s_sdwFpgaFd <= 0)
    {
        return 16;
	}
	sdwRet = ioctl(s_sdwFpgaFd,FPGA_ENABLE_INTERRUPT);
	if (sdwRet < 0)
	{
        printf("bsp_fpga_int_enable ioctl error = 0x%08x",sdwRet);
	    return 17;
	}
	return 0;
}
/**************************************************************************
* 函数名称：bsp_fpga_int_disenable
* 功能描述：FPGA 中断禁能函数
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：无
* 返 回 值：0: 成功；其他为失败
* 其它说明：
* 修改日期    版本号     修改人      修改内容
* -----------------------------------------------
**************************************************************************/

unsigned int bsp_fpga_int_disable(void)
{
    int sdwRet = 0;
	if(s_sdwFpgaFd <= 0)
    {
        return 18;
	}
	sdwRet = ioctl(s_sdwFpgaFd,FPGA_DISABLE_INTERRUPT);
	if (sdwRet < 0)
	{
        printf("bsp_fpga_int_disable ioctl error = 0x%08x",sdwRet);
	    return 29;
	}
	return 0;
}



