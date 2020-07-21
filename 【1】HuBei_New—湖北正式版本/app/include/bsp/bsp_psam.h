/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：bsp_drvPsam.h
* 文件标识：
* 内容摘要：PSAM 驱动头文件
* 其它说明：
* 当前版本：
* 作            者：
* 完成日期：
************************************************************************/

#ifndef _BSP_DRV_PSAM_H_
#define _BSP_DRV_PSAM_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct tagT_CardResetPara
{
    unsigned char   ucSockId;
    unsigned char   aucPad[3];
    unsigned short wEtu;
    unsigned short wPad;
    unsigned int dwErrCode;
    unsigned int dwAtrLen;
    unsigned char   aucAtr[32];
    unsigned int dwHistLen;
    unsigned char   aucHistory[32];
}T_CardResetPara;

typedef struct tagT_CardProcPara
{
    unsigned char   ucSockId;
    unsigned char   ucPad;
    unsigned char   ucCmdLen;
    unsigned char   ucResLen;    
    
    unsigned int dwErrCode;
    unsigned char   aucCmd[256];
    unsigned char   aucRes[256];
}T_CardProcPara;	
typedef struct tagT_CardPara
{
    unsigned short wEtu;
    unsigned short wPad;
    unsigned int dwAtrLen;
    unsigned char   aucAtr[32];

    unsigned int dwHistLen;
    unsigned char   aucHistory[32];
}T_CardPara;

/*错误码定义*/
/* rcv send char error */
#define  PHY7816_ERR_CTL_PTR            0x00000001    /*控制结构空指针*/
#define  PHY7816_ERR_DATA_ADDR          0x00000002    /*数据线地址空指针*/
#define  PHY7816_ERR_TIME_OUT           0x00000004    /*接收字符超时*/
#define  PHY7816_ERR_PARITY             0x00000008    /*接收字符奇偶校验错*/
#define  PHY7816_ERR_SEND_char          0x00000010    /* 发送字符错误*/
#define  PHY7816_ERR_SIGNAL_INT         0x00000020    /* 信号中断错误*/


/*ATR*/
#define  PHY7816_ERR_NO_TS              0x00000100    /*没收到TS*/
#define  PHY7816_ERR_TS_NOT_3B          0x00000200    /*TS不是3B*/
#define  PHY7816_ERR_NO_T0              0x00000400    /*没收到T0*/
#define  PHY7816_ERR_HISTORY            0x00000800    /*接收历史字节错误*/

/*active */
#define PHY7816_ERR_START_ETU           0x00001000    /*不支持的START_ETU*/
#define PHY7816_ERR_ATR                 0x00002000    /* 接收ATR失败*/
#define PHY7816_ERR_PPS_RCV             0x00004000    /*  PPS过程中，接收数据失败*/
#define PHY7816_ERR_PPS                 0x00008000    /* PPS失败*/

/* apdu transcieve  */
#define  PHY7816_ERR_CMD_PARA           0x00010000    /*命令参数错误*/
#define  PHY7816_ERR_SND_CMD_HEADER     0x00020000    /* 发送命令头失败*/
#define  PHY7816_ERR_RCV_INS            0X00040000    /*接收INS失败*/
#define  PHY7816_ERR_SND_LC_DATA        0x00080000    /* 发送LC后面的数据失败*/
#define  PHY7816_ERR_RCV_LE_DATA        0x00100000    /* 接收LE后面的返回数据失败*/
#define  PHY7816_ERR_RCV_FIRST_STATUS   0x00200000    /* 接收卡片返回的第一个字节数据失败*/
#define  PHY7816_ERR_RCV_SECOND_STATUS  0x00400000    /* 接收卡片返回的第二个字节数据失败*/
#define  PHY7816_ERR_SND_GETRESPONSE    0x00800000    /* 发送get_response失败*/

#define  PHY7816_ERR_OPEN_FILE          0x01000000    /* 打开PSAM驱动失败*/
#define  PHY7816_ERR_IOCTL              0x02000000    /*IOCTL系统调用失败*/
#define  PHY7816_ERR_FD                 0x04000000    /* 错误的文件描述符*/
#define  PHY7816_MAP_FAILED             0x08000000    /* mmap系统调用失败*/

#define  PSAM_VOLTAGE_3V3               0x1           /*电压设置值3.3V*/
#define  PSAM_VOLTAGE_1V8               0x0           /*电压设置值1.8V*/


#define BSP_DRV_PSAM_NR (0x4)
#define BSP_DRV_PSAM_LINUX_DEVICE "/dev/misc/drv_psam"
#define BSP_DRV_PSAM_CLKFLEQ_MAX (15)
#define BSP_DRV_PSAM_BASE_ADDR (0xc0000000)
#define BSP_DRV_PSAM_ADDR_WIDTH (0x01000000)


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
unsigned int bsp_psam_init (void);
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
unsigned int bsp_psam_active (unsigned char ucSockId, T_CardPara *ptCardPara,unsigned int *pdwPsamErrorCode);
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
unsigned int bsp_psam_cmd(unsigned char ucSockId, unsigned char ucCmdLen, unsigned char *pucCmdApdu, unsigned char *pucResLen, unsigned char *pucResTpdu,unsigned int *pdwPsamErrorCode);
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
unsigned int bsp_psam_deactive(unsigned char ucSockId,unsigned int *pdwPsamErrorCode);
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
unsigned int bsp_psam_clkfreq_set(unsigned char ucClkDiv);

/**********************************************************************
* 函数名称：bsp_psam_voltage_set
* 功能描述：修改PSAM卡的供电电压
* 输入参数：ucSockId:卡槽号;电压值 
* 返 回 值：错误码
* 其它说明：无
* 修改日期		版本号	修改人		修改内容
* ---------------------------------------------------------------------
************************************************************************/

unsigned int bsp_psam_voltage_set(unsigned char ucSockId,unsigned char ucVoltage);

#ifdef __cplusplus
}
#endif

#endif/* _BSP_DRV_PSAM_H_  */

