/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： uart.c
* 文件标识： 
* 内容摘要：提供对串口访问的接口
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/


/***********************************************************
 *                        包含头文件                       *
 ***********************************************************/
#include <termios.h>
#include "bsp.h"


/***********************************************************
 *                     全局变量                            *
***********************************************************/
/*****************************************************************************
* 函数名称： bsp_uart_open
* 功能描述：打开串口
* 修改变量：
* 输入参数： ucSerialNum : 串口编号
*                              dwMode : 串口打开模式
* 输出参数： * pdwIndex : 打开串口的索引
* 返 回 值：    0 or 错误码
* 其他说明：
* 修改日期   版本号    修改人  修改内容
* ----------------------------------------------------
 
******************************************************/


unsigned int bsp_uart_open(unsigned char ucSerialNum, unsigned int dwMode, unsigned int * pdwIndex)
{
    unsigned int swIndex = 0;
    unsigned int dwRet = 0;
    /* 打开时设置默认属性 */
    T_BSPDrvUartAttr tDefaultAttr;
    /* 判断串口编号是否大于串口总数 */
    if (ucSerialNum >= 4)
    {
        return 1;
    }

    switch (ucSerialNum)
    {
        case 0:
        {
            swIndex = open("/dev/ttyS0", dwMode);
            break;
        }
        case 1:
        {
            swIndex = open("/dev/ttyS1", dwMode);
            break;
        }
        case 2:
        {
            unsigned short wData = 0;
            wData = READ_EPLD_REG(BSP_DRV_422_EN_OFFSET);
            wData |= BSP_DRV_422_EN_MASK;
            wData &=~BSP_DRV_422_DISEN_MASK;
            WRITE_EPLD_REG(BSP_DRV_422_EN_OFFSET, wData);

            wData = READ_EPLD_REG(BSP_DRV_UART_INTERRUP_OFFSET);
            wData |= BSP_DRV_UART_INTERRUP_MASK;
            WRITE_EPLD_REG(BSP_DRV_UART_INTERRUP_OFFSET, wData);
            swIndex = open("/dev/ttyS2", dwMode);
            break;
        }
        case 3:
        {
            swIndex = open("/dev/ttyS3", dwMode);
            break;
        }
        default:
        {
            return 2;
        }

    }

    if (swIndex < 0)
    {
        return 2;
    }
    *pdwIndex = swIndex;

    /* 默认属性值 */
    tDefaultAttr.dwBaudRate = 115200;
    tDefaultAttr.ucDataBit = 8;
    tDefaultAttr.ucStopBit = 1;
    tDefaultAttr.ucParity = 0;
    tDefaultAttr.ucFlowControl = NO_FLOWCTRL;
    dwRet = bsp_uart_setAttr((*pdwIndex), &tDefaultAttr);
    if (0 != dwRet)
    {
        bsp_uart_close(*pdwIndex);
        return dwRet;
    }

    return 0;
}

/*****************************************************************************
* 函数名称： bsp_uart_snd
* 功能描述： 串口发送函数
* 修改变量：
* 输入参数： dwIndex : 串口索引
*                              dwLen : 待发送数据的长度
*                              pucSndBuf : 发送数据缓冲区
* 输出参数： * pdwSndLen : 实际发送长度
* 返 回 值：    0
* 其他说明：
* 修改日期   版本号    修改人  修改内容
* ----------------------------------------------------
 
******************************************************/
unsigned int bsp_uart_snd (unsigned int dwIndex, unsigned int dwLen, unsigned char * pucSndBuf, unsigned int * pdwSndLen)
{
     int sdwRet = 0;
    sdwRet = write(dwIndex, pucSndBuf, dwLen);
    if (sdwRet < 0)
    {
        return 3;
    }
    else
    {
        * pdwSndLen = (unsigned int)sdwRet;
    }

    return 0;
}


/*****************************************************************************
* 函数名称： bsp_uart_rcv
* 功能描述： 串口接收函数
* 修改变量：
* 输入参数： dwIndex : 串口索引
*                              dwLen : 期望接收数据的长度
*                              pucRcvBuf : 接收数据存放的缓冲区
* 输出参数： * pdwRcvLen : 实际接收长度
* 返 回 值：    0
* 其他说明：
* 修改日期   版本号    修改人  修改内容
* ----------------------------------------------------
 
******************************************************/
unsigned int bsp_uart_rcv (unsigned int dwIndex , unsigned int dwLen , unsigned char * pucRcvBuf, unsigned int *pdwRcvLen)
{
     int sdwRet = 0;

    /* linux、arm都默认非阻塞，是否把模式默认为非阻塞 */
    sdwRet = read(dwIndex, pucRcvBuf, dwLen);
    if (sdwRet < 0)
    {
        return 4;
    }
    else
    {
        * pdwRcvLen = (unsigned int)sdwRet;
    }
    return 0;

}

/*****************************************************************************
* 函数名称： bsp_uart_setAttr
* 功能描述： 串口设置属性函数
* 修改变量：
* 输入参数： dwIndex : 串口索引
*                              ptUartAttr : 属性变量指针
* 输出参数： 
* 返 回 值：    0 or 错误码
* 其他说明：
* 修改日期   版本号    修改人  修改内容
* ----------------------------------------------------
 
******************************************************/

unsigned int bsp_uart_setAttr (unsigned int dwIndex, T_BSPDrvUartAttr * ptUartAttr)
{
    int sdwRet = 0;
    struct termios tNewTio;
    bzero(&tNewTio, sizeof(tNewTio));
    cfmakeraw(&tNewTio);

    /* 设置波特率 */
    switch (ptUartAttr->dwBaudRate)
    {
        case 1000000:
        {
            cfsetispeed(&tNewTio, B1000000);
            cfsetospeed(&tNewTio, B1000000);
            break;
        }
        case 921600:
        {
            cfsetispeed(&tNewTio, B921600);
            cfsetospeed(&tNewTio, B921600);
            break;
        }
        case 576000:
        {
            cfsetispeed(&tNewTio, B576000);
            cfsetospeed(&tNewTio, B576000);
            break;
        }
        case 115200:
        {
            cfsetispeed(&tNewTio, B115200);
            cfsetospeed(&tNewTio, B115200);
            break;
        }
        case 57600:
        {
            cfsetispeed(&tNewTio, B57600);
            cfsetospeed(&tNewTio, B57600);
            break;
        }
        case 38400:
        {
            cfsetispeed(&tNewTio, B38400);
            cfsetospeed(&tNewTio, B38400);
            break;
        }
        case 19200:
        {
            cfsetispeed(&tNewTio, B19200);
            cfsetospeed(&tNewTio, B19200);
            break;
        }
        case 9600:
        {
            cfsetispeed(&tNewTio, B9600);
            cfsetospeed(&tNewTio, B9600);
            break;
        }
        default:
        {
            return 5;
        }
    }
    /* 更改立即生效 */
    sdwRet = tcsetattr(dwIndex, TCSANOW, &tNewTio);
    if (sdwRet != 0)
    {
        perror("set_Baut tcgetattr error!");
        return 10;
    }
    /* 刷新缓冲区 */
    tcflush(dwIndex, TCIOFLUSH);
    sdwRet = tcgetattr( dwIndex, &tNewTio);
    if ( sdwRet != 0)
    {
        perror("set_parity tcgetattr error!");
        return 11;
    }
    /*  数据位设置 */
    switch (ptUartAttr->ucDataBit)
    {
        case 5:
        {
            tNewTio.c_cflag &= ~CSIZE;
            tNewTio.c_cflag |= CS5;
            break;
        }
        case 6:
        {
            tNewTio.c_cflag &= ~CSIZE;
            tNewTio.c_cflag |= CS6;
            break;
        }

        case 7:
        {
            tNewTio.c_cflag &= ~CSIZE;
            tNewTio.c_cflag |= CS7;
            break;
        }
        case 8:
        {
            tNewTio.c_cflag &= ~CSIZE;
            tNewTio.c_cflag |= CS8;
            break;
        }
        default:
        {
            return 6;
        }
    }
    /* 奇偶校验设置 */
    switch (ptUartAttr->ucParity)
    {
        case 0:
        {
            tNewTio.c_cflag &= ~PARENB;
            tNewTio.c_iflag &= ~INPCK;
            break;
        }
        case 1:
        {
            tNewTio.c_iflag |= (INPCK | ISTRIP);
            tNewTio.c_cflag |= PARENB;
            tNewTio.c_cflag &= ~PARODD;
            break;
        }
        case 2:
        {
            tNewTio.c_cflag |= PARENB;
            tNewTio.c_cflag |= PARODD;
            tNewTio.c_iflag |= (INPCK | ISTRIP);
            break;
        }
        default:
        {
            return 7;
        }
    }
    /* 停止位设置 */
    switch (ptUartAttr->ucStopBit)
    {
        case 1:
        {
            tNewTio.c_cflag &= ~CSTOPB;
            break;
        }
        case 2:
        {
            tNewTio.c_cflag |= CSTOPB;
            break;
        }
        default:
        {
            return 8;
        }
    }

    tNewTio.c_oflag &= ~OPOST;
    tNewTio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tNewTio.c_cc[VTIME] = 0;
    tNewTio.c_cc[VMIN] = 1;
    tNewTio.c_cflag |= (CLOCAL | CREAD);
    tNewTio.c_iflag &= ~(BRKINT | ICRNL | IXON);


    /* 设置串口流控 */
    switch (ptUartAttr->ucFlowControl)
    {
        case NO_FLOWCTRL:
        {
            tNewTio.c_cflag &= ~CRTSCTS;
            tNewTio.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        }
        case HARDWARE_FLOWCTRL:
        {
            tNewTio.c_cflag |= CRTSCTS;
            break;
        }
        case SOFTWARE_FLOWCTRL:
        {
            tNewTio.c_cflag |= (IXON | IXOFF | IXANY);
            break;
        }

        default:                                                                                                                                                                           /* 缺省不设置流控 */
        {
            tNewTio.c_cflag &= ~CRTSCTS;
            tNewTio.c_iflag &= ~(IXON | IXOFF | IXANY);

            break;
        }
    }

    /* 更改立即生效 */
    sdwRet = tcsetattr(dwIndex, TCSANOW, &tNewTio);
    if (sdwRet != 0)
    {
        return 9;
    }
    /* 刷新缓冲区 */
    tcflush(dwIndex, TCIOFLUSH);
    return 0;

}

/**************************************************************************
* 函数名称： bsp_uart_flush
* 功能描述：刷新串口缓冲区
* 修改变量：
* 输入参数： dwIndex : 串口索引
*                              tMode : 刷新模式
* 输出参数： 
* 返 回 值：    0 or 错误码
* 其他说明：
* 修改日期   版本号    修改人  修改内容
* ----------------------------------------------------
 
******************************************************/

unsigned int bsp_uart_flush (unsigned int dwIndex, T_BSPDrvUartFlushMode tMode)
{
    int sdwRet = 0;
    sdwRet = tcflush(dwIndex, tMode);
    if (0 != sdwRet)
    {
        return 10;
    }

    return 0;
}

/**************************************************************************
* 函数名称： bsp_uart_close
* 功能描述：串口关闭函数
* 修改变量：
* 输入参数： dwIndex : 串口索引
* 输出参数： 
* 返 回 值：    0 or 错误码
* 其他说明：
* 修改日期   版本号    修改人  修改内容
* ----------------------------------------------------
 
******************************************************/

unsigned int bsp_uart_close(unsigned int dwIndex)
{
    int swRet = 0;
        if (2 == dwIndex)
    {
        
        unsigned short wData = 0;
        wData = READ_EPLD_REG(BSP_DRV_422_EN_OFFSET);
        wData |= BSP_DRV_422_DISEN_MASK;
        wData &= ~BSP_DRV_422_EN_MASK;
        WRITE_EPLD_REG(BSP_DRV_422_EN_OFFSET, wData);
        
        wData = READ_EPLD_REG(BSP_DRV_UART_INTERRUP_OFFSET);
        wData &= ~BSP_DRV_UART_INTERRUP_MASK;
        WRITE_EPLD_REG(BSP_DRV_UART_INTERRUP_OFFSET, wData);

    }
    swRet = close(dwIndex);
    if (swRet < 0)
    {
        return 11;
    }

    return 0;

}


