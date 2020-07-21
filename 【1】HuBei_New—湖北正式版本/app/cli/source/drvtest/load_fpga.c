#include <stdio.h>
#include "bsp.h"
#include "drvtest.h"

#define EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET      0x92   /*控制寄存器偏移*/
#define EPLD_FPGA_DOWNLOAD_DATA_REG_OFFSET     0x94   /*数据寄存器偏移*/
#define FPGA_DELAY_US                          16      /*延时基数*/
#define FPGA_CONFIG_DONE_TIME_OUT              1000     /*CONFIGDONE延时时间*/
#define EPLD_FPGA_RESET                        0xa2

#define NCONFIG_BIT_MASK                       0x1     /*config引脚掩码*/
#define NSTATUS_BIT_MASK                       0x2     /*nstatus引脚掩码*/
#define CONFDONE_BIT_MASK                      0x4     /*configdone引脚掩码*/
#define INITDONE_BIT_MASK                      0x8     /*initdone引脚掩码*/

#define PIN_HIGH                               0x1     /*输出高电平*/
#define PIN_LOW                                0x0     /*输出低电平*/

#define VER_LOAD_BUF_LEN                       0x200000  
#define FPGA_DOWNLOAD_START  		           0x10	   /* 用于指示FPGA代码分段下载的开始标志 */
#define FPGA_DOWNLOAD_CLOSE    		           0x01	   /* 用于指示FPGA代码分段下载的结束标志 */


#define WRITE_FPGA_DOWNLOAD_REG(OFFSET,BITOFFSET,DATA) ((DATA > 0) ? (p_epld_start_addr[OFFSET]|=BITOFFSET) : (p_epld_start_addr[OFFSET]&=~BITOFFSET))
#define READ_FPGA_DOWNLOAD_REG(OFFSET,BITOFFSET) (((p_epld_start_addr[OFFSET] & BITOFFSET) > 0) ? 0x1 : 0x0)

#define FPGA_DOWNLOAD_ERROR_CONFIG_LOW         0x1     /*config引脚拉低时发生错误*/
#define FPGA_DOWNLOAD_ERROR_CONFIG_HIGH        0x2     /*config引脚拉高时发生错误*/
#define FPGA_DOWNLOAD_ERROR_CONFIG_DONE        0x3     /*config_done引脚拉高时发生错误*/



static void os_usDelay(unsigned int us)
{
    volatile unsigned int i = 0;
    for (i = 0;i < (FPGA_DELAY_US * us); i++);
    return;
}

static void initFpgaLoadAddr(void)
{
    unsigned short dwRet;

    dwRet = bsp_epld_init();
    if (0 != dwRet)
    {
        printf("init epld fail!\r\n");
        return dwRet;
    }
}

static unsigned int drv_fpga_download(unsigned char * buff, int len)
{
    unsigned int dwTimeOut = 0;
    unsigned int i = 0;
    
    printf("FPGA version download start\r\n");
    WRITE_FPGA_DOWNLOAD_REG(EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET,NCONFIG_BIT_MASK,PIN_LOW);

    #if 1
    dwTimeOut = FPGA_CONFIG_DONE_TIME_OUT;


    while ((READ_FPGA_DOWNLOAD_REG(EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET,CONFDONE_BIT_MASK) != 0)\ 
			    && (dwTimeOut > 0))
    {   
        //os_usDelay(1);
        dwTimeOut--;
    }
    if (dwTimeOut == 0)
    {
        printf("set config pin low error!\r\n");
	    return FPGA_DOWNLOAD_ERROR_CONFIG_LOW;
    }
    #endif
    os_usDelay(1);
    /* CONFIG 写高电平 */
    WRITE_FPGA_DOWNLOAD_REG(EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET,NCONFIG_BIT_MASK,PIN_HIGH);

    #if 1
    /* 这个时候, STATUS也会变成高电平 */
    dwTimeOut = FPGA_CONFIG_DONE_TIME_OUT;
    while ((READ_FPGA_DOWNLOAD_REG(EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET,NSTATUS_BIT_MASK) != 1) && (dwTimeOut > 0))
    {
        os_usDelay(1);
        dwTimeOut--;
    }
    if (dwTimeOut == 0)
    {
        printf("set config pin high error!\r\n");
	    return FPGA_DOWNLOAD_ERROR_CONFIG_HIGH;
    }
    #endif
    os_usDelay(5);
    /* 循环：写数据(字节)+少量延时(1us) */
    for (i = 0;i < len;i++)
    {

        p_epld_start_addr[EPLD_FPGA_DOWNLOAD_DATA_REG_OFFSET] = buff[i];
        if (i % 10000 == 0)
        {
            printf(".");
        }
        os_usDelay(5);
    }
    //数据下载完需要在产生2个clk时钟
    p_epld_start_addr[EPLD_FPGA_DOWNLOAD_DATA_REG_OFFSET] = 0x0;
    printf("\r\nFPGA version download end\r\n");
    /* FPGA数据本身自带CRC等信息, 在收到所需要的数据以后, CONFIG_DONE引脚就会变成高电平 */
    printf("CONFIG_DONE %x\r\n",p_epld_start_addr[EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET]);

    #if 0
    dwTimeOut = FPGA_CONFIG_DONE_TIME_OUT;
    while ((READ_FPGA_DOWNLOAD_REG(EPLD_FPGA_DOWNLOAD_CTL_REG_OFFSET,CONFDONE_BIT_MASK) != 1) && (dwTimeOut > 0))
    {
	    os_usDelay(2000);
        dwTimeOut--;
    }
    if (dwTimeOut == 0)
    {
        printf("CONFIG_DONE error when timeout!\r\n");
        return FPGA_DOWNLOAD_ERROR_CONFIG_DONE;
    }

    #endif

    return 0;
}

unsigned int drvtest_loadfpag(char *pFpgaFilePath)
{
    FILE *pf = NULL;
    unsigned char  aucfpgaBuf[VER_LOAD_BUF_LEN];
    unsigned int dwRet = 0;
	unsigned int iReadSize = 0;
	unsigned short tReadVale = 0;
	unsigned short tWriteValue = 0x55aa;
	unsigned short dwRegOffset = 0;
	T_FpgaData tFpgaTemp = 0;

    (void)initFpgaLoadAddr();

  
	//printf("drvtest_LoadFpag run...,file path=%s\r\n", pFpgaFilePath);
    pf = fopen((const char *)pFpgaFilePath,"rb");
    if(NULL == pf)
    {
        printf("Can't open FPGA Version file\r\n");
        return 0x1;
    }
    printf("FPGA Version file is successfully found!\n");
    iReadSize = fread(aucfpgaBuf,sizeof(unsigned char),VER_LOAD_BUF_LEN,pf);
    if(iReadSize < 0)
    {
        printf("Read Fpga File error\r\n");
        return 0x2;
    }
    printf("Read FPGA bin file successfully, ReadSize is %d \r\n", iReadSize);
    
    dwRet = drv_fpga_download(aucfpgaBuf,iReadSize);
    if (0 != dwRet)
    {
        printf("drv_fpga_download error!\r\n");
        return dwRet;
    }

    //bsp_epld_write(0x144, 0x00);
    os_usDelay(1000);
    //bsp_epld_write(0x144, 0x01);

    return 0;
}

