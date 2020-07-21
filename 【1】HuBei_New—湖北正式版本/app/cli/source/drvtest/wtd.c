#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "bsp.h"
#include "drvtest.h"

static unsigned char s_StopFlag = 0;
static pthread_t pThreadId = NULL;


void sig_handler(int sig)
{ 
    if (NULL != pThreadId)
    {
        s_StopFlag = 1;
        pthread_join(pThreadId,NULL);
    }
}


void* WeedWtdThread(void*ps)
{
    unsigned int dwRet = 0;
    while (!s_StopFlag)
    {
        dwRet = bsp_wtd_feed();
        if (0 != dwRet)
        {
            printf("bsp_wtd_feed error = 0x%08x!!!\n",dwRet);
            break;
        }
        usleep(1000);
    }
    pThreadId = NULL;
    printf("stop weed wtd thread!\r\n");
}

unsigned int  drvtest_softwtd(void)
{
    unsigned int dwRet = 0;
    unsigned int dwLoop   = 0;

    (void)bsp_epld_init();
    
    dwRet = bsp_wtd_init();
	if (0 != dwRet)
	{
		printf("wtd init fail. error=0x%08x\n",dwRet);
		return dwRet;
	}
	dwRet = bsp_wtd_setTimer(10);
	if (0 != dwRet)
	{
		printf("bsp_wtd_setTimer error = 0x%08x!!!\n",dwRet);
        return dwRet;
	}
	dwRet = bsp_wtd_enable();
	if (0 != dwRet)
	{
        printf("bsp_wtd_enable error = 0x%08x!!!\n",dwRet);
		return dwRet;
	}	
	
    pThreadId = NULL;

    signal(SIGINT, sig_handler);

  	if(pthread_create(&pThreadId,NULL,WeedWtdThread,NULL))
	{
		printf("failed to create weed wtd thread!\n");
		return ERROR;
  	}

    return 0;
}

unsigned int  drvtest_hwwtd(void)
{
    unsigned int dwRet = 0;
    unsigned int dwLoop   = 0;

    (void)bsp_epld_init();
    dwRet = bsp_wtd_init();
	if (0 != dwRet)
	{
		printf("wtd init fail. error=0x%08x\n",dwRet);
		return dwRet;
	}
	dwRet = bsp_wtd_setTimer(10);
	if (0 != dwRet)
	{
		printf("bsp_wtd_setTimer error = 0x%08x!!!\n",dwRet);
        return dwRet;
	}
	dwRet = bsp_wtd_enable();
	if (0 != dwRet)
	{
        printf("bsp_wtd_enable error = 0x%08x!!!\n",dwRet);
		return dwRet;
	}	

	dwRet = bsp_wtd_hwFeed();
	if (0 != dwRet)
	{
        printf("bsp_wtd_hwFeed error = 0x%08x!!!\n",dwRet);
		return dwRet;
	}	
    return 0;
}

unsigned int  drvtest_stopwtd(void)
{
    unsigned int dwRet = 0;
    unsigned int dwLoop   = 0;

    (void)bsp_epld_init();
    dwRet = bsp_wtd_init();
	if (0 != dwRet)
	{
		printf("wtd init fail. error=0x%08x\n",dwRet);
		return dwRet;
	}

	dwRet = bsp_wtd_disable();
	if (0 != dwRet)
	{
        printf("bsp_wtd_disable error = 0x%08x!!!\n",dwRet);
		return dwRet;
	}	


    if (NULL != pThreadId)
    {
        s_StopFlag = 1;
        pthread_join(pThreadId,NULL);
    }

    return 0;
}

