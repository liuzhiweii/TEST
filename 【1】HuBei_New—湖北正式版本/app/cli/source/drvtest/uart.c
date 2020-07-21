#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "bsp.h"

static unsigned int drvtest_UartOpen(unsigned int dwindex,unsigned int dwbRate, unsigned int *pdwuartfd)
{

	unsigned int dwRet = 0;
	unsigned int dwUartFd = 0;
	unsigned int dwIndex = 0;	   

	


	
	T_BSPDrvUartAttr tUartAttr;


	dwIndex = dwindex;


    //dwRet = bsp_uart_open((unsigned char) dwIndex, UART_NOCTTY | UART_RDONLY | UART_NONBLOCK, &dwUartFd);
    dwRet = bsp_uart_open((unsigned char) dwIndex, UART_NOCTTY | UART_RDWR, &dwUartFd);
    
	if(0 != dwRet)
	{
		printf("bsp_uart_open error : %d\n ",dwRet);
		return dwRet;		
	}

	tUartAttr.dwBaudRate = dwbRate;
	tUartAttr.ucDataBit = 8;
	tUartAttr.ucParity = 0;
	tUartAttr.ucStopBit = 1;
	tUartAttr.ucFlowControl = 0;
	dwRet = bsp_uart_setAttr(dwUartFd, &tUartAttr);
	
	if(0 != dwRet)
	{
		printf("bsp_uart_setAttr error : 0x%08x\n ",dwRet);
		return dwRet;		
	}
	dwRet = bsp_uart_flush(dwUartFd, UART_IOFLUSH);
	if(0 != dwRet)
	{
		printf("bsp_uart_flush error : 0x%08x\n ",dwRet);
		return dwRet;		
	}
	
	*pdwuartfd = dwUartFd;
	return 0;
}

unsigned int  drvtest_uart_revsend(unsigned int dwindex,unsigned int dwbRate)
{
    unsigned int dwRet        = 0;
    unsigned int dwSndLen     = 0;
    unsigned int dwRcvLen     = 0;
    pid_t  pid          = -1;
	unsigned int dwLoop		= 0;
	unsigned char ucSndBuf[1024] = {0};
	unsigned char ucRcvBuf[1024] = {0};
    unsigned int dwaurtfd     = 0;


    dwRet = drvtest_UartOpen(dwindex, dwbRate, &dwaurtfd);

    if (0 != dwRet)
    {
        return dwRet;
    }
    
    pid = fork();
	
	if( pid ==0 )
	{   
	    printf("uart%d:please input data!\r\n", dwindex);
		while(1)
		{

		    #if 0
		    ucRcvBuf[0] = 0xaa;
		    ucRcvBuf[1] = 0x55;
		    ucRcvBuf[2] = 0xaa;
		    ucRcvBuf[3] = 0x55;		    
            dwRet = bsp_uart_snd(dwaurtfd,4,ucRcvBuf,&dwSndLen);
            if((dwRet == 0) || dwSndLen>0)
            {
                printf("send data ok!\r\n");
            }
            else
            {
                printf("send data fail!\r\n");
            }

            bsp_uart_close(dwaurtfd);
            exit(1);
            #endif
		    memset(ucRcvBuf,0,256);
			dwRet = bsp_uart_rcv(dwaurtfd,256,ucRcvBuf,&dwRcvLen);
            
		    if((dwRet == 0) || dwRcvLen>0)
		    {
		        printf("rcv date list:\n");

		        if (('e' == ucRcvBuf[0]) && ('x' == ucRcvBuf[1])\
		            && ('i' == ucRcvBuf[2]) && ('t' == ucRcvBuf[3]))
		        {
		            printf("uart%d:exit recv test!\r\n", dwindex);
		            bsp_uart_close(dwindex);
		            exit(0);
		        }
		        
	            for(dwLoop = 0; dwLoop < dwRcvLen; dwLoop++)
	            {
                    if(dwLoop % 32)
     		        {
     			        printf("0x%x ", ucRcvBuf[dwLoop]);
     		        }
     		        else
     		        {
     			        printf("\n%");
     			        printf("0x%x ", ucRcvBuf[dwLoop]);
     		        }
	            }
	            printf("\n");

	            dwSndLen = 0;
                dwRet = bsp_uart_snd(dwaurtfd,dwRcvLen,ucRcvBuf,&dwSndLen);
                if((dwRet == 0) || dwSndLen>0)
                {
                    printf("send data ok!\r\n");
                }
                else
                {
                    printf("send data fail!\r\n");
                }
                continue;
		    }		  
		    else
		    {
                printf("rev_send fail!errorCode = 0x%x\r\n", dwRet);
		    }
		}
	}
	return 0;
}

unsigned int  drvtest_uart_loopback(unsigned int dwindex,unsigned int dwbRate, unsigned int dwLoopNum)
{
    unsigned int dwRet        = 0;
    unsigned int dwSndLen     = 0;
    unsigned int dwRcvLen     = 0;
	unsigned char ucSndBuf[256] = {0};
	unsigned char ucRcvBuf[256] = {0};

	unsigned int dwSendErrNum = 0;
	unsigned int dwSendErrPackNum = 0;
	unsigned int dwRevErrNum = 0;
	unsigned int dwRevErrPackNum = 0;
	int dwLoop = 0;
    unsigned int dwaurtfd     = 0;
	unsigned char total_buf[512];	
    
    dwRet = drvtest_UartOpen(dwindex, dwbRate, &dwaurtfd);
    if (0 != dwRet)
    {
        printf("open uart: %d fail!\n", dwaurtfd);
        return dwRet;
    }

    memset(ucSndBuf,0,256);
    for (dwLoop = 0; dwLoop < 255; dwLoop+=2)
    {
        ucSndBuf[dwLoop] = 0xaa;
        ucSndBuf[dwLoop+1] = 0x55;
    }
	
    dwLoop = dwLoopNum;
	int success_cnt = 0;	
	unsigned int totallen=0;

    while(dwLoop > 0)
    {
	    dwLoop -= 1;
	    totallen = 0;
	    memset(total_buf, 0, 256);
        dwRet = bsp_uart_snd(dwaurtfd,256,ucSndBuf,&dwSndLen);

	    while(totallen < dwSndLen)
	    {
	        dwRet = bsp_uart_rcv(dwaurtfd,256,ucRcvBuf,&dwRcvLen);
		    if(0 == dwRet)
			{
			    memcpy(&total_buf[totallen], ucRcvBuf, dwRcvLen);
			    totallen += dwRcvLen;				
			}
		    else
			{
			    printf("recv frame fail\n");
			    break;
			}
	    }

	    if(0 == memcmp(total_buf, ucSndBuf, totallen))
		{
			success_cnt += 1;
		    printf("recv frame success%d\n",success_cnt);
		}

    }

    printf("send frame nums: %d \n", dwLoopNum);
	printf("recv correct frame %d \n", success_cnt);
    bsp_uart_close(dwindex);
	
	return 0;
}


