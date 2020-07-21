#include <stdio.h>
#include "bsp.h"
#include "drvtest.h"

unsigned int  drvtest_writepld(unsigned int dwOffset,T_EpldData tVale)
{
    unsigned int dwRet = 0;
    unsigned int dwRegOffset = 0;
    T_EpldData tWriteValue = 0;


    tWriteValue = tVale;

    dwRet = bsp_epld_init();

    if (0 != dwRet)
    {
        printf("init epld fail!\r\n");
        return dwRet;
    }
    else
    {
        dwRegOffset = (dwOffset>>1);
        printf("offset = %x\r\n", dwRegOffset);
        dwRet = bsp_epld_write(dwRegOffset, tWriteValue);
        if (0 != dwRet)
        {
            printf("Epld write test fail!,error = 0x%x\r\n", dwRet);
            return ERROR;
        }
        else
        {
            printf("Epld write test Ok!\r\n");
        }
    }

    return 0;

}

unsigned int  drvtest_readepld(unsigned int dwOffset)
{
    unsigned int dwRet = 0;
    unsigned int dwRegOffset = 0;
    T_EpldData tReadValue = 0;

    
    dwRet = bsp_epld_init();

    if (0 != dwRet)
    {
        printf("init epld fail!\r\n");
        return dwRet;
    }
    else
    {
        dwRegOffset = (dwOffset>>1);
        dwRet = bsp_epld_read(dwRegOffset, &tReadValue);
        if (0 != dwRet)
        {
            printf("Epld read test fail!,error = 0x%x\r\n", dwRet);
            return ERROR;
        }
        else
        {
            printf("Epld read test Ok!RegValue = 0x%x\r\n", tReadValue);
        }
    }

    return 0;

}

