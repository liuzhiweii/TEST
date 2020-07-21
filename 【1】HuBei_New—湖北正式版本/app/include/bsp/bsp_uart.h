/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： bsp_uart.h
* 文件标识： 
* 内容摘要： 串口模块对外接口头文件
* 其它说明： 
* 当前版本：
* 作    者： 
* 完成日期： 
************************************************************************/

#ifndef _BSP_UART_H
#define _BSP_UART_H

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/

/* 流控的取值 */
#define  NO_FLOWCTRL    0
#define  HARDWARE_FLOWCTRL    1
#define  SOFTWARE_FLOWCTRL     2

/* 打开模式保持和linux内核的定义一致 */
#define UART_NONBLOCK   0x00000800
#define UART_NOCTTY     0x00000100
#define UART_RDONLY     0x00000000
#define UART_WRONLY     0x00000001
#define UART_RDWR       0x00000002

#define BSP_DRV_422_EN_OFFSET          (0xdc>>1)
#define BSP_DRV_422_EN_MASK            (0x02)
#define BSP_DRV_422_DISEN_MASK         (0x01)

#define BSP_DRV_UART_INTERRUP_OFFSET   (0x94>>1)
#define BSP_DRV_UART_INTERRUP_MASK     (0x02)


/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/
/* 串口属性 */
typedef struct tagT_BSPDrvUartAttr
{
	unsigned int         dwBaudRate;          /*波特率*/
	unsigned char            ucDataBit;           /*数据位5，6，7，8 */
	unsigned char            ucStopBit;           /*停止位1 和2  */
	unsigned char            ucParity;            /*校验位 0 =None ，1 = Even， 2 =Odd*/
	unsigned char            ucFlowControl;       /*流控制*/
}T_BSPDrvUartAttr;


typedef enum tagT_BSPDrvUartFlushMode
{
	UART_INFLUSH = 0,
	UART_OUTFLUSH,
	UART_IOFLUSH
} T_BSPDrvUartFlushMode;

/**************************************************************************
 *                            函数声明                                     *
 **************************************************************************/
unsigned int  bsp_uart_open(unsigned char ucSerialNum, unsigned int dwMode, unsigned int * pdwIndex);
unsigned int  bsp_uart_snd (unsigned int dwIndex, unsigned int dwLen, unsigned char * ucSndBuf, unsigned int * pdwSndLen);
unsigned int  bsp_uart_rcv (unsigned int dwIndex , unsigned int dwLen , unsigned char * ucRcvBuf, unsigned int *pdwRcvLen);
unsigned int  bsp_uart_close(unsigned int dwIndex);
unsigned int  bsp_uart_setAttr (unsigned int dwIndex, T_BSPDrvUartAttr * ptUartAttr);
unsigned int  bsp_uart_flush (unsigned int dwIndex, T_BSPDrvUartFlushMode tMode);

#endif
