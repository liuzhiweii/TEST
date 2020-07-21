#include "bsp.h"
#include "drvtest.h"
#include <stdio.h>


#define FLASH_SECTOR_SIZE   (0x20000)
/*避免申请内存过大，最大读写2个扇区*/
#define MAX_FLASE_TEST_SIZE (FLASH_SECTOR_SIZE*2)


unsigned int drvtest_flash_write(unsigned int dwOffset, unsigned int dwLen, unsigned char ucdata)
{
    unsigned int dwRet = 0;
    unsigned char *pucWriteBuf = NULL;
    unsigned int dwWriteLen = 0;
    unsigned int dwLoop = 0;

	if(dwLen > MAX_FLASE_TEST_SIZE)
	{
		printf("write len is more than %d Byte\r\n", MAX_FLASE_TEST_SIZE);
		return 0x1;
	}

	pucWriteBuf = (char*)malloc(dwLen);
	if(NULL == pucWriteBuf)
	{
		printf("malloc error\r\n");
		return 0x2;
	}
	
	memset(pucWriteBuf,ucdata,dwLen);
    dwRet = bsp_flash_init();
    if(0 != dwRet)
    {
        printf("Flash init fail. errorcode=0x%x\r\n", dwRet);
        return dwRet;
    }
    dwRet = bsp_flash_write(NOR_FLASH, dwOffset, dwLen, pucWriteBuf, &dwWriteLen);
    if((0 != dwRet) || (dwLen != dwWriteLen))
    {
        printf("Flash write fail. errorcode=0x%x, readLen=0x%x!\r\n", dwRet, dwWriteLen);
        return dwRet;
    }

    printf("Flash write ok!\r\n", dwRet);
    return dwRet;
}

unsigned int drvtest_flash_read(unsigned int dwOffset, unsigned int dwLen)
{
    unsigned int dwRet = 0;
    unsigned char *pucRcvBuf = NULL;
    unsigned int dwReadLen = 0;
    unsigned int dwLoop = 0;

	if(dwLen > MAX_FLASE_TEST_SIZE)
	{
		printf("read len is more than %d Byte\r\n", MAX_FLASE_TEST_SIZE);
		return 0x1;
	}

	pucRcvBuf = (char*)malloc(dwLen);
	if(NULL == pucRcvBuf)
	{
		printf("malloc error\r\n");
		return 0x2;
	}
	
	memset(pucRcvBuf,0,dwLen);
    dwRet = bsp_flash_init();
    if(0 != dwRet)
    {
        printf("Flash init fail. errorcode=0x%x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_flash_read(NOR_FLASH, dwOffset, dwLen, pucRcvBuf, &dwReadLen);
    if((0 != dwRet) || (dwLen != dwReadLen))
    {
        printf("Flash read fail. errorcode=0x%x, readLen=0x%x!\r\n", dwRet, dwReadLen);
        return dwRet;
    }
    else
    {
        printf("Flash read data ok:\r\n");
        for (dwLoop = 0; dwLoop < dwReadLen; dwLoop++)
        {
            if (0 == dwLoop%32)
            {
                printf("\r\n");
            }
            printf("%02x ", pucRcvBuf[dwLoop]);
        }
        printf("\r\n");
    }


    return dwRet;
}

unsigned int drvtest_flash_erase(unsigned int dwOffset, unsigned int dwLen)
{
    unsigned int dwRet = 0;

	if(dwLen > MAX_FLASE_TEST_SIZE)
	{
		printf("erase len is more than %d Byte\r\n", MAX_FLASE_TEST_SIZE);
		return 0x1;
	}

    dwRet = bsp_flash_init();
    if(0 != dwRet)
    {
        printf("Flash init fail. errorcode=0x%x\r\n", dwRet);
        return dwRet;
    }

    
    dwRet = bsp_flash_erase(NOR_FLASH, dwOffset, dwLen);
    if(0 != dwRet)
    {
        printf("Flash erase fail. errorcode=0x%x\r\n", dwRet);
        return dwRet;
    }

    printf("Flash erase ok!\r\n", dwRet);
    return dwRet;
}

unsigned int drvtest_flash_info(void)
{
    unsigned int dwRet = 0;
    unsigned int dwSize = 0;

    dwRet = bsp_flash_init();
    if(0 != dwRet)
    {
        printf("Flash init fail. errorcode=0x%x\r\n", dwRet);
        return dwRet;
    }

    dwSize = bsp_flash_size();

    printf("flash length=0x%x!\r\n",dwSize);	

    return dwRet;
}

