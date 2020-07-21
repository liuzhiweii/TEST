/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：ParallelPsamUsr.h
* 文件标识： 
* 内容摘要：并行PSAM驱动实现宏定义文件
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/

/***********************************************************
 *                包含头文件                               *
 ***********************************************************/

#ifndef  __PARALLEL_PSAMUSR_H
#define  __PARALLEL_PSAMUSR_H

//#include "bsp_typeDef.h"
//#include "bsp_pub.h"
//#include "drv.conf"

/*代表一个用户空间操作的PSAM*/
typedef struct tagT_UsrPsamDevice
{
    unsigned char ucStatus;                   /*设备文件状态*/
    char *ucDevName;                 /*设备文件名*/
    int sdwPsamDevFd;            /*PSAM文件描述符*/
} T_UsrPsamDevice;


/**********************************************************/
/*            Linux ioctl命令                             */
/**********************************************************/

#define    BSP_PSAM_IOCTL_CMD_ACTIVE           (0x00)
#define    BSP_PSAM_IOCTL_CMD_DEACTIVE         (0x01)
#define    BSP_PSAM_IOCTL_CMD_PROCESS          (0x02)
#define    BSP_PSAM_IOCTL_CMD_CLKSET           (0x03)
#define    BSP_PSAM_IOCTL_CMD_VOLTAGESET       (0x04)
#define    BSP_PSAM_IOCTL_CMD_SETPPS_STATE     (0x05)
#define    BSP_PSAM_IOCTL_CMD_SETETU_STATE     (0x06)



#define BSP_DRV_PSAM0_LINUX_DEVICE "/dev/misc/drv_psam0"
#define BSP_DRV_PSAM1_LINUX_DEVICE "/dev/misc/drv_psam1"
#define BSP_DRV_PSAM2_LINUX_DEVICE "/dev/misc/drv_psam2"
#define BSP_DRV_PSAM3_LINUX_DEVICE "/dev/misc/drv_psam3"



#endif



