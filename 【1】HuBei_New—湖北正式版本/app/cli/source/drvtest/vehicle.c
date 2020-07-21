#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "bsp.h"
#include "drvtest.h"

unsigned int  drvtest_ver(void)
{
    unsigned int dwRet        = 0;
    pid_t  pid          = -1;
    unsigned int dwLen = 0;
    unsigned char ucVerState = 0;

    (void)bsp_epld_init();

    dwRet = bsp_ver_init();

    if (0 != dwRet)
    {
        printf("init veriche driver fail,errcode = %x\r\n", dwRet);
        return ERROR;
    }

    dwRet = bsp_ver_ctrl(VER_ENABLE_MODE);
    if (0 != dwRet)
    {
        printf("control veriche driver fail,errcode = %x\r\n", dwRet);
        return ERROR;
    }    
    pid = fork();
	
	if( pid ==0 )
	{   
	    printf("please press key!\r\n");
		while(1)
		{
            dwRet = bsp_ver_read(&ucVerState, 1, &dwLen);
            if (0 != dwRet)
            {
                printf("read key state fail,errcode = %x\r\n", dwRet);
                return ERROR;
            }  
            else
            {
                printf("test ver ok,state = 0x%x!\r\n", ucVerState);
                exit(1);
            }
		}
	}
	return 0;
}
