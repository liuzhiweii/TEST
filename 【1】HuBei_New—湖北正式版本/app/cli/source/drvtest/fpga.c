#include "bsp.h"
#include "drvtest.h"

unsigned int  drvtest_writefpga(unsigned int dwOffset,T_EpldData tVale)
{
    unsigned int dwRet = 0;
    unsigned int dwRegOffset = 0;
    T_FpgaData tWriteValue = 0;


    tWriteValue = tVale;

    dwRet = bsp_fpga_init();

    if (0 != dwRet)
    {
        printf("init fpga fail!\r\n");
        return dwRet;
    }
    else
    {   
        dwRegOffset = dwOffset | 0x80000;
        dwRet = bsp_fpga_write_reg(dwRegOffset, tWriteValue);
        //printf("dwRet = %x\r\n", dwRet);
        if (0 != dwRet)
        {
            printf("Fpga write test fail!,error = 0x%x\r\n", dwRet);
            return ERROR;
        }
        else
        {
            printf("Fpga write test Ok!\r\n");
        }
    }

    return 0;

}

unsigned int  drvtest_readfpga(unsigned int dwOffset)
{
    unsigned int dwRet = 0;
    unsigned int dwRegOffset = 0;
    T_FpgaData tReadValue = 0;

    
    dwRet = bsp_fpga_init();

    if (0 != dwRet)
    {
        printf("init fpga fail!\r\n");
        return dwRet;
    }
    else
    {
        dwRegOffset = dwOffset | 0x80000;
        dwRet = bsp_fpga_read_reg(dwRegOffset, &tReadValue);
        if (0 != dwRet)
        {
            printf("Fpag read test fail!,error = 0x%x\r\n", dwRet);
            return ERROR;
        }
        else
        {
            printf("Fpag read test Ok!RegValue = 0x%x\r\n", tReadValue);
        }
    }

    return 0;

}

