#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "bsp.h"

unsigned int  drvtest_key(void)
{
    unsigned int dwRet        = 0;
    pid_t  pid          = -1;
    unsigned int dwLen = 0;


    (void)bsp_epld_init();
    dwRet = bsp_key_init();

    if (0 != dwRet)
    {
        printf("init key driver fail,errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_key_ctrl(KEY_ENABLE_MODE);
    if (0 != dwRet)
    {
        printf("control key driver fail,errcode = %x\r\n", dwRet);
        return dwRet;
    }    
    pid = fork();
	
	if( pid ==0 )
	{   
	    printf("please press key!\r\n");
		while(1)
		{
            dwRet = bsp_key_read(NULL, 0, &dwLen);
            if (0 != dwRet)
            {
                printf("read key state fail,errcode = %x\r\n", dwRet);
                return dwRet;
            }  
            else
            {
                printf("test key ok!\r\n");
                exit(1);
            }
		}
	}
	return 0;
}
