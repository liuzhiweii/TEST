#include <stdio.h>
#include "bsp.h"
#include "drvtest.h"

static unsigned char aucCmd[5] = {0x00, 0x84, 0x00, 0x00, 0x08};
static unsigned char aucCmd1[21] = {0x80, 0x1a, 0x59, 0x03, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xba, 0xfe, 0xc4, 
                        0xcf, 0xba, 0xfe, 0xc4, 0xcf};
static unsigned char aucCmd2[78] = { 0x80, 0xfa, 0x80, 0x00, 0x48, 0xb7, 0x9e, 0x6d, 0x6d, 0x24, 
		                 0xe8, 0xe1, 0xac, 0x2a, 0x65, 0x5e, 0xcc, 0xa1, 0x03, 0x57,
		                 0x2e, 0xf1, 0xf1, 0x61, 0x0d, 0x9e, 0x6e, 0x09, 0x7d, 0x09, 
		                 0xf7, 0x09, 0x5f, 0x4c, 0xd1, 0x5b, 0x49, 0xbb, 0xad, 0xd5, 
		                 0xd4, 0x12, 0xbd, 0xdc, 0xe3, 0x88, 0xa0, 0x65, 0xe3, 0xc5, 
		                 0x8f, 0x82, 0x9a, 0x1c, 0xac, 0x5c, 0x2c, 0x48, 0xba, 0xd8, 
		                 0x5f, 0x6b, 0x18, 0x2d, 0x89, 0x97, 0xd0, 0x22, 0x8f, 0xb8, 
		                 0xc7, 0x27, 0x24, 0x73, 0xae, 0xcd, 0xaf, 0x48};
static unsigned char aucCmd3[7] = {0x00,0xA4,0x00,0x00,0x02,0xDF,0x01};


unsigned int drvtest_psaminit(void)
{
    unsigned int dwRet = 0;

    dwRet = bsp_psam_init();
    if(0 != dwRet)
    {
        printf("init operation fail, error=0x%08x\n",dwRet);
    	return dwRet;
    }

    return 0;

}

unsigned int drvtest_psamsetclk(unsigned int dwClkDiv)
{
    unsigned int dwRet        = 0;
    
    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
	printf("drvtest_psamsetclk:clk = %x\r\n", dwClkDiv);
	dwRet = bsp_psam_clkfreq_set((unsigned char)dwClkDiv);
	if(0 != dwRet)
	{
	    printf("clock set operation fail.error=0x%08x\n",dwRet);
		return dwRet;
	}else
	{
	    printf("%clock set operation success. clk_div=%x\n",dwClkDiv);
	}

	return 0;
}

unsigned int drvtest_psamactive(unsigned int dwCardID)
{
    unsigned int dwRet        = 0;
    unsigned int dwPsamError  = 0;
    unsigned int dwLoop       = 0;
    T_CardPara tCardPara;

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
	
	dwRet = bsp_psam_active(dwCardID,&tCardPara,&dwPsamError);
	if((0 != dwRet) || (0 != dwPsamError) )
	{
	     printf("active operation error.=0x%08x, psamerror=0x%08x\n",dwRet, dwPsamError);
         return dwRet;
	}
	else
    {
    	printf("%PSamCard Etu = %d\r\n",tCardPara.wEtu);
        printf("%PSamCard Atr:\n");
        for (dwLoop = 0;dwLoop < tCardPara.dwAtrLen;dwLoop++)
        {
              printf("%x ", tCardPara.aucAtr[dwLoop]);
        }
        printf("\n");
        printf("%PSamCard History: ");
        for (dwLoop = 0;dwLoop < tCardPara.dwHistLen;dwLoop++)
        {
              printf("%x ", tCardPara.aucHistory[dwLoop]);
        }
        printf("\n");
     }
	return 0;
}

unsigned int drvtest_psamdeactive(unsigned int dwCardID)
{

    unsigned int dwRet        = 0;
    unsigned int dwPsamError  = 0;   


    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
   
	dwRet = bsp_psam_deactive(dwCardID,&dwPsamError);
	if((0 != dwRet) || (0 != dwPsamError) )
	{
        printf("%deactive operation fail.error=0x%08x,psamerror=0x%08x\n",dwRet, dwPsamError);
		return dwRet;
	}
	else
    {
        printf("deactive operation done\n");
	}	

	return 0;
}

unsigned int drvtest_psam_enable_pps(unsigned int dwCardID)
{
    unsigned int dwRet = 0; 

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
   
	dwRet = bsp_psam_pps_set(dwCardID, 1);
	if(0 != dwRet)
	{
        printf("psam%d set pps flag operation fail.error=0x%08x\n",dwCardID,dwRet);
		return dwRet;
	}
	else
    {
        printf("psam%d set pps flag operation done\n", dwCardID);
	}	

	return 0;
}

unsigned int drvtest_psam_disable_pps(unsigned int dwCardID)
{
    unsigned int dwRet = 0; 

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
   
	dwRet = bsp_psam_pps_set(dwCardID, 0);
	if(0 != dwRet)
	{
        printf("psam%d set pps flag operation fail.error=0x%08x\n",dwCardID,dwRet);
		return dwRet;
	}
	else
    {
        printf("psam%d set pps flag operation done\n", dwCardID);
	}	

	return 0;
}



unsigned int drvtest_psamrandomdata(unsigned int dwCardID)
{
    unsigned int dwRet        = 0;
    unsigned int dwPsamError  = 0;
    unsigned int dwLoop       = 0;
    unsigned char   ucResLen     = 0;
	unsigned char   aucRes[100]  = {0};

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
	

	dwRet = bsp_psam_cmd(dwCardID, 5, aucCmd, &ucResLen, aucRes,&dwPsamError);
	if((0 != dwRet) || (0 != dwPsamError) )
	{
        printf("get random-data operation fail. error=0x%08x,psamerror=0x%08x\n",dwRet, dwPsamError);
		return dwRet;
	}
	else
    {
        printf("get random-data operation done.\n");
        printf("%s Data List:\n");
        for (dwLoop = 0; dwLoop < ucResLen; dwLoop++)
        {
            if(dwLoop % 10)
		    {
			    printf(" 0x%x  ", aucRes[dwLoop]);
		    }
		    else
		    {
			    printf("\n%");
			    printf(" 0x%x  ", aucRes[dwLoop]);
		    }
        }
        printf("\n");
				
    }

	return 0;
}

static unsigned int Psamchoseapp(unsigned int dwCardID,unsigned int dwOutPutFlag)
{
	unsigned int dwRet 		= 0;
    unsigned int dwPsamError  = 0;
    unsigned int dwLoop       = 0;
    unsigned char   ucResLen     = 0;
	unsigned char   aucRes[100]  = {0};    

	memset(aucRes,0,100);

    dwRet = bsp_psam_cmd(dwCardID, 7, aucCmd3, &ucResLen, aucRes,&dwPsamError);
	if((0 != dwRet) || (0 != dwPsamError) )
	{
        printf("applicaton-chosen operation fail. error=0x%08x,psamerror=0x%08x,\n",dwRet, dwPsamError);
        return dwRet;
	}
	else
	{
		if(ENABLE_OUTPUT == dwOutPutFlag)
		{
		    printf("slot number:%d\n",dwCardID);
		//    printf("%s",OUTPUT_ALIGN);
           // printf("\n卡槽 %d 选择应用命令返回数据:\n",dwCardID);
        	for (dwLoop = 0; dwLoop < ucResLen; dwLoop++)
        	{
        	    if(dwLoop % 10)
        	    {
        	        printf(" 0x%x  ", aucRes[dwLoop]);
        		}
        		else
        		{
        		    printf("\n%");
        		    printf(" 0x%x  ", aucRes[dwLoop]);
        		}
            }
			printf("\n");
		}
		if((aucRes[ucResLen - 1] == 0x00) && (aucRes[ucResLen - 2] == 0x90))
		{
		    printf("applicaton-chosen operation success\n");
		}
		else
		{
		    printf("%s applicaton-chosen operation fail\n");
			return ERROR;
		}
	}

	return 0;
}

unsigned int drvtest_psamchoseapp(unsigned int dwCardID)
{
    unsigned int dwRet        = 0;

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
	
	return Psamchoseapp(dwCardID,ENABLE_OUTPUT);
}

static unsigned int Psamassignkey(unsigned int dwCardID,unsigned int dwOutPutFlag)
{
	unsigned int dwRet		= 0;
    unsigned int dwPsamError  = 0;
    unsigned int dwLoop       = 0;
    unsigned char   ucResLen     = 0;
	unsigned char   aucRes[100]  = {0};

	memset(aucRes,0,100);

    dwRet = bsp_psam_cmd(dwCardID, 21, aucCmd1, &ucResLen, aucRes,&dwPsamError);
	if((0 != dwRet) || (0 != dwPsamError) )
	{
	    printf("assign key operation fail. error=0x%08x, psamerror=0x%08x\n",dwRet, dwPsamError);
		return dwRet;
	}
	else
	{
		if(ENABLE_OUTPUT== dwOutPutFlag)
		{
		    printf("data returned of assign-key command\n");

            for (dwLoop = 0; dwLoop < ucResLen; dwLoop++)
            {
                if(dwLoop % 10)
        		{
        		    printf(" 0x%x  ", aucRes[dwLoop]);
        		}
        		else
        		{
        		    printf("\n%");
        		    printf(" 0x%x  ", aucRes[dwLoop]);
        		} 
            }
			printf("\n");
		}
		if((aucRes[ucResLen -1] == 0x00) && (aucRes[ucResLen - 2] == 0x90))
		{
		    printf("assign-key operation success\n");
		}
		else
		{
		    printf("assign-key operation fail\n");
			return ERROR;
		}
	}

	return 0;
}

 unsigned int drvtest_psamassignkey(unsigned int dwCardID)
{

    unsigned int dwRet        = 0;

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}

	return Psamassignkey(dwCardID,ENABLE_OUTPUT);
	
}

static unsigned int Psamdecryptinfo(unsigned int dwCardID,unsigned int dwOutPutFlag)
{
    unsigned int dwRet		= 0;
    unsigned int dwPsamError  = 0;
    unsigned int dwLoop	   = 0;
    unsigned char   ucResLen	   = 0;
    unsigned char   aucRes[100]  = {0};

	memset(aucRes,0,100);

    dwRet = bsp_psam_cmd(dwCardID, 78, aucCmd2, &ucResLen, aucRes,&dwPsamError);
	if((0 != dwRet) || (0 != dwPsamError) )
	{
	    printf("decrypt operation fail.error=0x%08x\n, psamerror=0x%08x\n",dwRet, dwPsamError);
	    
	    return dwRet;
	}
	else
	{
		if(ENABLE_OUTPUT == dwOutPutFlag)
		{
		    printf("data returned of decryption command\n");
	
     	    for (dwLoop = 0; dwLoop < ucResLen; dwLoop++)
     	    {
     	        if(dwLoop % 10)
     		    {
     		        printf(" 0x%x  ", aucRes[dwLoop]);
     			}
     		    else
     		    {
     			    printf("\n%");
     				printf(" 0x%x  ", aucRes[dwLoop]);
     		    }
     	    }
			printf("\n");
		}
		if((aucRes[ucResLen -1] == 0x00) && (aucRes[ucResLen - 2] == 0x90))
	    {
	        printf("decryption opeartion success\n");
		}
		else
		{
		    printf("%s decryption opeartion fail\n");
			return ERROR;
		}
	}

	return 0;
}

unsigned int drvtest_psamdecryptinfo(unsigned int dwCardID)
{
	unsigned int dwRet		= 0;

    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}

	return Psamdecryptinfo(dwCardID,ENABLE_OUTPUT);
}

unsigned int drvtest_autodecrypt (unsigned int dwCardID)
{
    unsigned int dwRet = 0;
    unsigned int dwPsamError  = 0;
    T_CardPara tCardPara;
	unsigned int dwLoop = 0;

    
	/*初始化*/
    dwRet = bsp_psam_init();
	if(0 != dwRet)
	{
        printf("init operation fail, error=0x%08x\n",dwRet);
		return dwRet;
	}
	
	printf("PSAM will be tested 3 times\n");
	
	for(dwLoop=0; dwLoop<3; dwLoop++)
	{
	    printf("\n");
		printf("start testing %d\n",dwLoop+1);
		/*激活*/
		printf("active operation start...\n");
	    dwRet = bsp_psam_active(dwCardID,&tCardPara,&dwPsamError);
	    if((0 != dwRet) || (0 != dwPsamError) )
	    {
            printf("%active operation fail.error=0x%08x\n, psamerror=0x%08x\n",dwRet, dwPsamError);
            return dwRet;
	    }
	    else
	    {
            printf("%active operation success.\n");
	    }        
		
		/*选择应用*/
		dwRet = Psamchoseapp(dwCardID,DISABLE_OUTPUT);
		if(0 != dwRet)
		{
			return dwRet;
		}
		
		/*分散密钥*/
		dwRet = Psamassignkey(dwCardID,DISABLE_OUTPUT);
		if(0 != dwRet)
		{
			return dwRet;
		}
		
		/*解密*/
		dwRet = Psamdecryptinfo(dwCardID,DISABLE_OUTPUT);
		if(0 != dwRet)
		{
			return dwRet;
		}	
	}

    return 0;
}

