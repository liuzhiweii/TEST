#include "bsp.h"
#include "flash_def.h"

#include <mtd/mtd-abi.h>
#include <mtd/mtd-user.h> 
#include<stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>


static T_BSPDrvFlashMtd s_atMtdInfo[SYSTEM_MTD_MAX];     
static unsigned int s_dwNorTotalSize = 0;     
static unsigned int s_dwNandTotalSize = 0;    
static unsigned int s_dwNorMtdBaseIndex = SYSTEM_MTD_MAX;   
static unsigned int s_dwNandMtdBaseIndex = SYSTEM_MTD_MAX;  


static unsigned int GetMtdInfo(unsigned int dwFlashId, unsigned int dwOffset, unsigned char * pucMtdIndex, unsigned int * pdwMtdOffset)
{
    unsigned int	dwLoop = 0;
    if (NOR_FLASH == dwFlashId)
    {
        for (dwLoop = s_dwNorMtdBaseIndex; dwLoop < s_dwNandMtdBaseIndex; dwLoop++)//代码有问题
        {
            if (dwOffset < (s_atMtdInfo[dwLoop].dwMtdOffset + s_atMtdInfo[dwLoop].dwMtdSize))
            {
                *pucMtdIndex = (unsigned char)dwLoop;
                *pdwMtdOffset = dwOffset - s_atMtdInfo[dwLoop].dwMtdOffset;
                return 0;
            }
        }
      
    }
    else if(NAND_FLASH == dwFlashId)
    {
        for (dwLoop = s_dwNandMtdBaseIndex; dwLoop < SYSTEM_MTD_MAX; dwLoop++)
        {
            if (dwOffset < (s_atMtdInfo[dwLoop].dwMtdOffset + s_atMtdInfo[dwLoop].dwMtdSize))
            {
                *pucMtdIndex = (unsigned char)dwLoop;
                *pdwMtdOffset = dwOffset - s_atMtdInfo[dwLoop].dwMtdOffset;
                return 0;
            }
        }

    }
    else 
    {
        return 1;
    }
    return 2;

}

unsigned int bsp_flash_init(void)
{
	FILE  *pFile = NULL;           
	char  acBuf[128] = {0};         
	unsigned char  ucLoop = 0;     
	unsigned int dwRet = 0;
	unsigned int dwEraseSizeTemp = 0;     
	unsigned int dwNandFlag = 0;         

    s_dwNorTotalSize = 0;
    s_dwNandTotalSize = 0;
	

	for(ucLoop = 0; ucLoop < SYSTEM_MTD_MAX; ucLoop++)
	{
	    sprintf(s_atMtdInfo[ucLoop].acMtdDevName, "/dev/mtd%u", ucLoop);
	}
	pFile = fopen("/proc/mtd", "r"); 
	if (NULL == pFile)
	{
	    return 3;
	}

	if(NULL == fgets(acBuf, sizeof(acBuf), pFile))
	{
	    return 4;
	}
	s_dwNorMtdBaseIndex = 0;
	for(ucLoop = s_dwNorMtdBaseIndex; ucLoop < (sizeof(s_atMtdInfo)/sizeof(T_BSPDrvFlashMtd));ucLoop++)
	{
	    dwRet = fscanf(pFile, "%s %x %x %s", acBuf, (&(s_atMtdInfo[ucLoop].dwMtdSize)),
	    &dwEraseSizeTemp,s_atMtdInfo[ucLoop].acMtdName);
	    if(dwRet != 4) 
	    {
	        break;
	    }
	    if(0 != ucLoop)
	    {
	        s_atMtdInfo[ucLoop].dwMtdOffset = s_atMtdInfo[ucLoop - 1].dwMtdSize + s_atMtdInfo[ucLoop - 1].dwMtdOffset;
	    }
	    if(NULL != strstr(s_atMtdInfo[ucLoop].acMtdName,"nand"))
	    {
	        s_dwNandTotalSize += s_atMtdInfo[ucLoop].dwMtdSize;
	        if(0 == dwNandFlag)
	        {
	            s_dwNandMtdBaseIndex = ucLoop;
	            dwNandFlag = 1;
	        }
	    }
	    else
	    {
	        s_dwNorTotalSize += s_atMtdInfo[ucLoop].dwMtdSize;
	    }
	    #ifdef FLASH_DEBUG
	        printf("mtddevname=%s,size=%x,offset=%x,loop=%d,dwRet=%x\n",s_atMtdInfo[ucLoop].acMtdDevName,s_atMtdInfo[ucLoop].dwMtdSize,
	                s_atMtdInfo[ucLoop].dwMtdOffset,ucLoop,dwRet);
	    #endif

	}
#ifdef FLASH_DEBUG
	    printf("Nor flash size = %x,Nand flash size = %x\n",s_dwNorTotalSize,s_dwNandTotalSize);
#endif
	fclose(pFile);
	return 0;
}

unsigned int bsp_flash_read(unsigned int dwFlashId, unsigned int dwOffset, unsigned int dwLen, unsigned char * pucBuf, unsigned int *pdwReadLen)
{
	unsigned char  ucMtdIndex = 0;
	unsigned int dwRet = 0;
	unsigned int dwMtdOffset = 0;
	int  sdwFd = -1;
	int  sdwResult = -1;
	int  sdwReadLen = -1;

	if((NOR_FLASH != dwFlashId) && (NAND_FLASH != dwFlashId))
	{
	    return 6;
	}
	if((NULL == pucBuf) || (NULL == pdwReadLen))
	{
	    return 7;
	}

	dwRet = GetMtdInfo(dwFlashId, dwOffset, &ucMtdIndex, &dwMtdOffset);
	if ( 0 != dwRet)
	{
	    return dwRet;
	}
	if(dwMtdOffset + dwLen > s_atMtdInfo[ucMtdIndex].dwMtdSize)
	{
	    return 8;
	}

	sdwFd = open(s_atMtdInfo[ucMtdIndex].acMtdDevName, O_RDWR );
	if (sdwFd < 0)
	{
	    return 9;
	}

	sdwResult = lseek(sdwFd, dwMtdOffset, SEEK_SET);	
	if (sdwResult  < 0)
	{
	    close(sdwFd);
	    return 10;
	}

	sdwReadLen = read(sdwFd, pucBuf, dwLen);
	if (sdwReadLen < 0)
	{
	    close(sdwFd);
		return 11;
	}

	close(sdwFd);

	(* pdwReadLen) =  (unsigned int)sdwReadLen;
	return 0;
}


unsigned int bsp_flash_erase(unsigned int dwFlashId, unsigned int dwOffset, unsigned int dwLen)
{
	unsigned char  ucMtdIndex = 0;
	unsigned int dwRet = 0;
	unsigned int dwMtdOffset = 0;

	int  sdwFd = -1;
	int  sdwResult = -1;

	erase_info_t * tEraseInfo;
	unsigned int dwSectorSize = 0;

	if((NOR_FLASH != dwFlashId) && (NAND_FLASH != dwFlashId))
	{
	    return 12;
	}

	dwRet = GetMtdInfo(dwFlashId, dwOffset, &ucMtdIndex, &dwMtdOffset);
	if ( 0 != dwRet)
	{
	    return dwRet;
	}
	if(dwMtdOffset + dwLen > s_atMtdInfo[ucMtdIndex].dwMtdSize)
	{
	    return 13;
	}

	sdwFd = open(s_atMtdInfo[ucMtdIndex].acMtdDevName, O_RDWR );
	if (sdwFd < 0)
	{
	    return 14;
	}

	tEraseInfo = (erase_info_t *) malloc(sizeof(erase_info_t));
	if (NULL == tEraseInfo)	
	{
	    return 15;
	}

	switch(dwFlashId)
	{
	    case 0:
	    {
	        dwSectorSize = BSP_DRV_NOR_SECTOR_SIZE;
	        break;
	    }
	    case 1:
	    {
	        dwSectorSize = BSP_DRV_NAND_SECTOR_SIZE;
	        break;
	    }
	    default:
	    {
	        dwSectorSize = BSP_DRV_NOR_SECTOR_SIZE;			
	    }
	}

	tEraseInfo->start = (u_int32_t)((dwMtdOffset / dwSectorSize)* dwSectorSize);
	if((((dwMtdOffset + dwLen) / dwSectorSize) * dwSectorSize) < (dwMtdOffset + dwLen))
	{
	    tEraseInfo->length = (u_int32_t)(((((dwMtdOffset + dwLen) / dwSectorSize) - (dwMtdOffset /dwSectorSize))+1) * dwSectorSize);
	}
	else
	{
	    tEraseInfo->length = (u_int32_t)((((dwMtdOffset + dwLen) / dwSectorSize) - (dwMtdOffset /dwSectorSize)) * dwSectorSize);
	}

	sdwResult = ioctl(sdwFd, MEMERASE, &(tEraseInfo->start));/* MEMERASE define in kernel, we use direct number, that is 0x80084d02 */
	if (sdwResult < 0)
	{
	    close(sdwFd);
	    free(tEraseInfo);
	    return 16;
	}

	close(sdwFd);
	free(tEraseInfo);

	return 0;
}

	
unsigned int bsp_flash_write(unsigned int dwFlashId, unsigned int dwOffset, unsigned int dwLen, unsigned char * pucBuf, unsigned int *pdwWriteLen)
{
	unsigned char ucMtdIndex = 0;
	unsigned int dwRet = 0;
	unsigned int dwMtdOffset = 0;
	int  sdwFd = -1;
	int  sdwResult = -1;
	int  sdwWriteLen = -1;

	if((NOR_FLASH != dwFlashId) && (NAND_FLASH != dwFlashId))
	{
	    return 17;
	}
	if((NULL == pucBuf) || (NULL == pdwWriteLen))
	{
	    return 18;
	}

	dwRet = GetMtdInfo(dwFlashId, dwOffset, &ucMtdIndex, &dwMtdOffset);
	if ( 0 != dwRet)
	{
	    return dwRet;
	}
	if(dwMtdOffset + dwLen > s_atMtdInfo[ucMtdIndex].dwMtdSize)
	{
	    return 19;
	}

	sdwFd = open(s_atMtdInfo[ucMtdIndex].acMtdDevName, O_RDWR );
	if (sdwFd < 0)
	{
	    return 20;
	}

	sdwResult = lseek(sdwFd, dwMtdOffset, SEEK_SET);	
	if (sdwResult  < 0)
	{
	    close(sdwFd);
	    return 21;
	}

	sdwWriteLen = write(sdwFd, pucBuf, dwLen);
	if (sdwWriteLen < 0)
	{
	    close(sdwFd);
		return 22;
	}
	close(sdwFd);
	(* pdwWriteLen) =  (unsigned int)sdwWriteLen;
	return 0;
}


unsigned int bsp_flash_size(void)
{
	return s_dwNorTotalSize;
}



unsigned int bsp_flash_totalsize(unsigned int dwFlashId,unsigned int *pdwSize)
{
	if(NOR_FLASH == dwFlashId)
	{
	    *pdwSize = s_dwNorTotalSize;
	    return 0;
	}
	else if(NAND_FLASH == dwFlashId)
	{
	    *pdwSize = s_dwNandTotalSize;
	    return 0;
	}
	else
	{
	    return 23;
	}
    
}
