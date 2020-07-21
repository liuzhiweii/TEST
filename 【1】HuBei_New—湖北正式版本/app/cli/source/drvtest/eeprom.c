#include "bsp.h"
#include "drvtest.h"
#include <stdio.h>


#define EEPROM_SIZE 512
//eeprom备份数据
unsigned char aucBuf[EEPROM_SIZE] = {0};

unsigned int drvtest_eeprom_write(unsigned char ucdata)
{
    unsigned char aucWriteBuf[EEPROM_SIZE] = {0};
    unsigned char aucReadBuf[EEPROM_SIZE] = {0};
    unsigned int iloop = 0;
    unsigned int dwRet = 0;
    unsigned int dwRcvLen = 0;

    memset(aucWriteBuf,ucdata, EEPROM_SIZE);

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_snd(0, EEPROM_SIZE, aucWriteBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("write eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }

    dwRet = bsp_eeprom_rcv(0, EEPROM_SIZE, aucReadBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("read eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }

    if(0 == memcmp(aucWriteBuf, aucReadBuf, EEPROM_SIZE))
    {
        printf("write eeprom ok!\r\n");
    }
    else
    {
        printf("eeprom data:\r\n");
        for (iloop = 0; iloop < EEPROM_SIZE; iloop++)
        {
            if (iloop%16)
            {
                printf("\r\n");
            }
            printf("%02x ", aucReadBuf[iloop]);
        }
    }
    printf("\r\n");
    return dwRet;
}
int change_char_to_int(unsigned char c)
{
   if((c>='0')&&(c<='9'))
   	{
   	   return c-'0';
   	}
   else if((c>='a')&&(c<='f'))
   	{
   	   return c-'a'+10;
   	}
   else if((c>='A')&&(c<='F'))
   	{
   	   return c-'A'+10;
   	}
}
void change_str_to_hex(char *data,unsigned char *hexdata)
{
   int len,i;
   char buf[2048];
   if(NULL==data)
   	return;
   len=strlen(data);
   memset(buf,0,sizeof(buf));
   if(len%2!=0)
   {
   	  buf[0]='0';
	  memcpy(&buf[1],data,len+1);
   }
   else
   {
      memcpy(&buf,data,len+1);
   }
   for(i=0;i<strlen(buf)/2;i++)
   {
      hexdata[i]=change_char_to_int(buf[2*i])*16+change_char_to_int(buf[2*i+1]);
   }
   return;
}
unsigned int drvtest_eeprom_write_addr_len_data(int addr, int len, char *data)
{
    unsigned char hexdata[2048] = {0};
    unsigned char aucReadBuf[EEPROM_SIZE] = {0};
    unsigned int iloop = 0;
    unsigned int dwRet = 0;
    unsigned int dwRcvLen = 0;
	unsigned char data1;


    if(addr+len>2048)
    {
        printf("addr is more than 2048 error\r\n");
        return dwRet;
    }
	//将data 转化为hex
	change_str_to_hex(data,hexdata);
    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_snd(addr, len, hexdata, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("write eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }

    dwRet = bsp_eeprom_rcv(addr, len, aucReadBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("read eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }

    if(0 == memcmp(hexdata, aucReadBuf, len))
    {
        printf("write eeprom ok!\r\n");
    }
    else
    {
        printf("write eeprom error  data:0x%x data1:0x%x\r\n",data,data1);
        
    }
    printf("\r\n");
    return dwRet;
}

unsigned int drvtest_eeprom_read_addr_len(int addr, int len)
{
    unsigned char aucReadBuf[EEPROM_SIZE] = {0};
    unsigned int iloop = 0;
    unsigned int dwRet = 0;
    unsigned int dwRcvLen = 0;

    memset(aucReadBuf,0, EEPROM_SIZE);

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_rcv(addr, len, aucReadBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("read eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }
    else
    {
        printf("eeprom data:\r\n");
        for (iloop = 0; iloop < len; iloop++)
        {
            if (0 == iloop%32)
            {
                printf("\r\n");
            }
            printf("%02x ", aucReadBuf[iloop]);
        }
    }
    printf("\r\n");
    return dwRet;
}

unsigned int drvtest_eeprom_read(void)
{
    unsigned char aucReadBuf[EEPROM_SIZE] = {0};
    unsigned int iloop = 0;
    unsigned int dwRet = 0;
    unsigned int dwRcvLen = 0;

    memset(aucReadBuf,0, EEPROM_SIZE);

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_rcv(0, EEPROM_SIZE, aucReadBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("read eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }
    else
    {
        printf("eeprom data:\r\n");
        for (iloop = 0; iloop < EEPROM_SIZE; iloop++)
        {
            if (0 == iloop%32)
            {
                printf("\r\n");
            }
            printf("%02x ", aucReadBuf[iloop]);
        }
    }
    printf("\r\n");
    return dwRet;
}

unsigned int drvtest_eeprom_savedata(void)
{
    unsigned int dwRet = 0;
    unsigned int dwRcvLen = 0;
    unsigned int iloop = 0;

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_rcv(0, EEPROM_SIZE, aucBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("read eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }
    else
    {
        printf("eeprom data:\r\n");
        for (iloop = 0; iloop < EEPROM_SIZE; iloop++)
        {
            if (0 == iloop%32)
            {
                printf("\r\n");
            }
            printf("%02x ", aucBuf[iloop]);
        }
    }
    printf("\r\n");

    return dwRet;
}


unsigned int drvtest_eeprom_recoverdata(void)
{
    unsigned int dwRet = 0;
    unsigned int dwRcvLen = 0;

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }
    
    dwRet = bsp_eeprom_snd(0, EEPROM_SIZE, aucBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("write eeprom data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }
    
    printf("recover eeprom data ok!\r\n");
    return dwRet;
}
//进行出厂设置
unsigned int drvtest_eeprom_setdefault(char *pFilePath)
{
    FILE *pf = NULL;
    unsigned char  aucBuf[EEPROM_SIZE];
    unsigned int dwRet = 0;
	unsigned int iReadSize = 0;
	unsigned int iloop = 0;
    unsigned int dwRcvLen = 0;

    (void)bsp_epld_init();
    dwRet = bsp_i2c_init();
    if (0 != dwRet)
    {
        printf("rtc i2c init fail!errcode = %x\r\n", dwRet);
        return dwRet;
    }

    pf = fopen((const char *)pFilePath,"rb");
    if(NULL == pf)
    {
        printf("Can't open eeprom config file\r\n");
        return 0x1;
    }
    printf("open eeprom config file is successfully found!\n");
    iReadSize = fread(aucBuf,sizeof(unsigned char),EEPROM_SIZE,pf);

    if(iReadSize < 0)
    {
        printf("Read eeprom config file error\r\n");
        return 0x2;
    }
    printf("Read eeprom config file successfully, ReadSize is %d \r\n", iReadSize);
    printf("eeprom config data:\r\n");
    
    for (iloop = 0; iloop < iReadSize; iloop++)
    {
        if (0 == iloop%32)
        {
            printf("\r\n");
        }
        printf("%02x ", aucBuf[iloop]);
    }
    
    dwRet = bsp_eeprom_init();

    if (0 != dwRet)
    {
        printf("init eeprom fail,errorcode = 0x%x\r\n", dwRet);
        return dwRet;
    }
    
    dwRet = bsp_eeprom_snd(0, iReadSize, aucBuf, &dwRcvLen);
    if (0 != dwRet)
    {
       printf("write eeprom config data fail,errorcode = 0x%x\r\n", dwRet);
       return dwRet;
    }
    
    printf("write eeprom config data ok!\r\n");
    return dwRet;
}


