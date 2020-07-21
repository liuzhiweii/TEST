#include <stdio.h>

unsigned int drvtest_settsensor(unsigned char ucfunID, unsigned char ucValue)
{
    unsigned int dwRet = 0;
    
    (void)bsp_epld_init();

    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("tsensor i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_tsensor_init();
	if(dwRet != 0)
	{
	    printf("tsensor init failed!errcode = %x\r\n", dwRet);
	    return dwRet;
    }

	dwRet = bsp_tsensor_set_temperature(ucfunID, ucValue);
	if (0 != dwRet)
	{
		printf("tsensor test: bsp_tsensor_set_temperature error= 0x%08x\r\n",dwRet);
		return dwRet;
	}

	printf("tsensor set ok!\r\n");

    return 0;
}
unsigned int drvtest_gettsensor(unsigned char ucfunID)
{
    unsigned int dwRet = 0;
    unsigned char ucValue = 0;
    unsigned char ucRcvData= 0;

    (void)bsp_epld_init();

    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("tsensor i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_tsensor_init();
	if(dwRet != 0)
	{
	    printf("tsensor init failed!errcode = %x\r\n", dwRet);
	    return dwRet;
    }

	dwRet = bsp_tsensor_get_temperature(ucfunID, &ucValue);
	if (0 != dwRet)
	{
		printf("tsensor test: bsp_tsensor_get_temperature error= 0x%08x\r\n",dwRet);
		return dwRet;
	}
    ucRcvData = (ucValue & 0x80) ? (~ucValue + 1) : ucValue;
    printf("temperature = %s%dC\r\n",((ucValue & 0x80)?"-":""), ucRcvData);

    return 0;
}



