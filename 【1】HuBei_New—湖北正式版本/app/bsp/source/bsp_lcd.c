#include <stdio.h>
#include "bsp.h"
#include "lcd_def.h"

#define ERR_INVALID_CHR  0xff

unsigned char g_ucGBTableSize = sizeof(gbk_char_table)/sizeof(T_GBTable);
spi_dev_t oled_dev;
int is_lcdinit = 0;

void reset_oled(void)
{
	int i = 10000;	
	
	bsp_epld_write((0xEA>>1), 0);
	while(i>0)
	{
		i--;
	}
	bsp_epld_write((0xEA>>1), 1);
	return;
}

void dc_off(void)
{
	bsp_epld_write((0xe8>>1), 0);
	return;
}

void dc_on(void)
{
	bsp_epld_write((0xe8>>1), 1);
	return;
}

unsigned int write_reg(unsigned char data)
{
	unsigned int ret = 0;
	
	ret = spi_take_sem(&oled_dev);
	if(0 != ret)
    {
        printf("write_reg :spi_take_sem fail!\r\n");
        return ret;
    }

    bsp_spi_cs_clr(&oled_dev);
    dc_off();    
    bsp_spi_send_byte(&oled_dev, data);
    dc_on();
    bsp_spi_cs_set(&oled_dev);

    ret = spi_give_sem(&oled_dev);
    if(0 != ret)
    {
        printf("write_reg:spi_give_sem fail!\r\n");
        return ret;
    }

    return 0;
}

unsigned int write_parameter(unsigned char data)
{
	unsigned int ret = 0;
	
	ret = spi_take_sem(&oled_dev);
	if(0 != ret)
    {
        printf("write_reg:spi_take_sem fail!\r\n");
        return ret;
    }

    bsp_spi_cs_clr(&oled_dev);
    dc_on();    
    bsp_spi_send_byte(&oled_dev, data);
    dc_on();
    bsp_spi_cs_set(&oled_dev);

    ret = spi_give_sem(&oled_dev);
    if(0 != ret)
    {
        printf("write_reg:spi_give_sem fail1\r\n");
        return ret;
    }

    return 0;
}


void set_colume_addr(unsigned char addr1,unsigned char addr2)
{
	write_reg(0x15); 
    write_parameter(addr1+28); 	
    write_parameter(addr2+28);  	
}

void set_row_addr(unsigned char addr1,unsigned char addr2)
{
	write_reg(0x75); 
    write_parameter(addr1); 	
    write_parameter(addr2);  	
}

void clear_oled (unsigned char color)
{
	unsigned char x,y;

	set_colume_addr(0,63);
	set_row_addr(0,63);
        
	write_reg(0x5C);    
	
	for(y=0;y<64;y++)
	{                   
		for(x=0;x<128;x++)
		{    
			write_parameter(color | (color << 4));
		}
	}
}

void bsp_clear_oled_row(unsigned char row, unsigned char color)
{
	unsigned char x,y;

	set_colume_addr(0,63);
	set_row_addr(row*16,(row + 1)*16 - 1);
        
	write_reg(0x5C);    
	
	for(y=0;y<16;y++)
	{                   
		for(x=0;x<128;x++)
		{    
			write_parameter(color | (color << 4));
		}
	}

}

void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{
    unsigned char c=0,i=0;	
	unsigned char j;
	unsigned char Data1,Data2,Data3,Data4,DATA1=0,DATA2=0;
	c=chr-' ';
    set_colume_addr(x/4,(x+8)/4-1);  

	
	set_row_addr(y,y+7);
	write_reg(0x5c);
	for(j=0;j<2;j++)
	{
		Data1=g_aucEn[c*16+4*j+0];
		Data2=g_aucEn[c*16+4*j+1];
		Data3=g_aucEn[c*16+4*j+2];
		Data4=g_aucEn[c*16+4*j+3];
		for(i=0;i<8;i++)
		{
			if(Data1&(0x01<<i))	
			{
				DATA1=0xF0;
			}
			if(Data2&(0x01<<i))
			{
				DATA1|=0x0F;
			}	
			write_parameter (DATA1);
			DATA1=0;
			if(Data3&(0x01<<i))	
			{
				DATA2=0xF0;
			}
			if(Data4&(0x01<<i))
			{
				DATA2|=0x0F;
			}
			
			write_parameter (DATA2);
			DATA2=0;
		}
	}
	

	set_colume_addr(x/4,(x+8)/4-1);  
	set_row_addr(y+8,y+15);
	write_reg(0x5c);
	for(j=2;j<4;j++)
	{
		Data1=g_aucEn[c*16+4*j+0];
		Data2=g_aucEn[c*16+4*j+1];
		Data3=g_aucEn[c*16+4*j+2];
		Data4=g_aucEn[c*16+4*j+3];
		for(i=0;i<8;i++)
		{
			if(Data1&(0x01<<i))	
			{
				DATA1=0xF0;
			}
			if(Data2&(0x01<<i))
			{
				DATA1|=0x0F;
			}	
			write_parameter (DATA1);
			DATA1=0;
			if(Data3&(0x01<<i))	
			{
				DATA2=0xF0;
			}
			if(Data4&(0x01<<i))
			{
				DATA2|=0x0F;
			}
			
			write_parameter (DATA2);
			DATA2=0;
		}
	}
}	


void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
	
			j++;
	}
}


unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}				  
	  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/8)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+8*t,y,temp+'0'); 
	}
}

void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char *chn)
{
	unsigned char i,j;
	unsigned char Data1,Data2,Data3,Data4,DATA1=0,DATA2=0;
	
	set_colume_addr(x/4,(x+16)/4-1);  
	set_row_addr(y,y+7);
	write_reg(0x5c);
	for(j=0;j<(4);j++)
	{
		Data1=*chn++;
		Data2=*chn++;
		Data3=*chn++;
		Data4=*chn++;
		for(i=0;i<8;i++)
		{
			if(Data1&(0x01<<i))	
			{
				DATA1=0xF0;
			}
			if(Data2&(0x01<<i))
			{
				DATA1|=0x0F;
			}	
			write_parameter (DATA1);
			DATA1=0;
			if(Data3&(0x01<<i))	
			{
				DATA2=0xF0;
			}
			if(Data4&(0x01<<i))
			{
				DATA2|=0x0F;
			}
			
			write_parameter (DATA2);
			DATA2=0;
		}
	}
	

	set_colume_addr(x/4,(x+16)/4-1);  
	set_row_addr(y+8,y+15);
	write_reg(0x5c);
	for(j=0;j<(4);j++)
	{
		Data1=*chn++;
		Data2=*chn++;
		Data3=*chn++;
		Data4=*chn++;
		for(i=0;i<8;i++)
		{
			if(Data1&(0x01<<i))	
			{
				DATA1=0xF0;
			}
			if(Data2&(0x01<<i))
			{
				DATA1|=0x0F;
			}	
			write_parameter (DATA1);
			DATA1=0;
			if(Data3&(0x01<<i))	
			{
				DATA2=0xF0;
			}
			if(Data4&(0x01<<i))
			{
				DATA2|=0x0F;
			}
			
			write_parameter (DATA2);
			DATA2=0;
		}
	}
}	

void OLED_DrawBMP(unsigned char *BMP,unsigned char Gray_Level,unsigned char Color)
{
	unsigned char i,j,k;
	unsigned char Data1,Data2,Data3,Data4,DATA1=0,DATA2=0;
	if(Gray_Level==0)
	{
    	for(k=0;k<8;k++)
    	{
        	set_colume_addr(0,64);	
        	set_row_addr(8*k,8*k+7);
        	write_reg(0x5c);
        						
    		{
        		for(j=0;j<(64);j++)
        		{
        			Data1=*BMP++;
        			Data2=*BMP++;
        			Data3=*BMP++;
        			Data4=*BMP++;
        			for(i=0;i<8;i++)
        			{
        				if(Data1&(0x01<<i))	
        				{
        					DATA1=(Color << 4);
        				}
        				if(Data2&(0x01<<i))
        				{
        					DATA1|=Color;
        				}	
        				write_parameter (DATA1);
        				DATA1=0;
        				if(Data3&(0x01<<i))	
        				{
        					DATA2=(Color << 4);
        				}
        				if(Data4&(0x01<<i))
        				{
        					DATA2|=Color;
        				}
        				
        				write_parameter (DATA2);
        				DATA2=0;
        			}
        		}
    	    }

    					}			
		}				
		else
		{//16位灰度图片（取模方向为数据垂直，字节水平）
    		for(k=0;k<64;k++)
        	{
            	set_colume_addr(k,k+2);	
            	set_row_addr(0,63);
            	write_reg(0x5c);
            						
                {
                    for(j=0;j<(64);j++)
                    {
                        write_parameter (*(BMP+128*k+j));
                        write_parameter (*(BMP+128*k+j+64));									
                    }

                }

        	}
        }

}

unsigned int bsp_lcd_ctrl(unsigned char ucCtl)
{

    switch(ucCtl)
    {
        case 0:
        {
            clear_oled(0);
            break;
        }
        case 1:
        {
            clear_oled(0xFF);
            break;
        }

    }
    return 0;
}

int gbk_chr_to_offset(unsigned short gbk_chr)
{
	
}

void show_gbk_char(unsigned char x, unsigned char y, unsigned short gbk_chr)
{
	
}


unsigned int bsp_lcd_show_string(unsigned char xpos, unsigned char ypos, unsigned char *pstr)
{
    unsigned short wGBK = 0;
    unsigned char ucCnt = 0;
    unsigned char ucOffset = 0;
    unsigned short need_display;
    unsigned char *pstrBuf = NULL;
    unsigned char ucXpos = 0;
    unsigned char ucYpos = 0;

    if (((xpos + LCD_MAX_XPIX) > LCD_MAX_XPOS) || ((ypos + LCD_MAX_YPIX) > LCD_MAX_YPOS)\
        || (NULL == pstr))
    {
        return 1;
    }

    pstrBuf = pstr;
    ucXpos = xpos;
    ucYpos = ypos;
    need_display = strlen((char *)pstr);
    printf("wGBK ###############\r\n");
    while(need_display)
    {
        //汉字
        if (*pstrBuf > 0x80)
        {
            /*　处理汉字　*/
            wGBK = (*pstrBuf << 8) | *(pstrBuf + 1);    
            for(ucCnt = 0; ucCnt < g_ucGBTableSize; ucCnt++)
            {
                if (wGBK == gbk_char_table[ucCnt].wGBK)
                {
                    ucOffset = gbk_char_table[ucCnt].wOffset;
					printf("wGBK =0x%x,ucOffset=%d\r\n", wGBK,ucOffset);
                    break;
                }
            }
            //换行
            if ((ucXpos + LCD_MAX_XPIX*2) > LCD_MAX_XPOS)
            {
                if ((ucYpos + LCD_MAX_YPIX) > LCD_MAX_YPOS)
                {
                    return 1;
                }
                ucYpos += LCD_MAX_YPIX;
                ucXpos = 0;
                printf("ucYpos = %d\r\n", ucYpos);
            }
            OLED_ShowCHinese(ucXpos, ucYpos, &g_aucChinese[ucOffset*LCD_CHINESE_LEN]);
            pstrBuf += 2;
            ucXpos += LCD_MAX_XPIX*2;
            need_display -= 2;

        }
        else
        {
            if ((ucXpos + LCD_MAX_XPIX) > LCD_MAX_XPOS)
            {
                if ((ucYpos + LCD_MAX_YPIX) > LCD_MAX_YPOS)
                {
                    return 1;
                }
                ucYpos += LCD_MAX_YPIX;
                ucXpos = 0;
                printf("ucYpos = %d\r\n", ucYpos);
            }
            OLED_ShowChar(ucXpos, ucYpos, *pstrBuf);
            pstrBuf++;
            ucXpos += LCD_MAX_XPIX;
            need_display--;
        }
    }
}

unsigned int bsp_lcd_init(void)
{	
	unsigned int ret;

	if(is_lcdinit == 1)
	{
		return 0;
	}

	ret = bsp_spi_init();
	if(ret != 0)
	{
		return ret;
	}

    oled_dev.bus = &spi_bus[0];
    oled_dev.mode = SPI_CPOLHA11;
    oled_dev.delay_cnt = 0;    

    reset_oled();

    write_reg(0xfd);  /*Command Lock*/ 
    write_parameter(0x12);

    write_reg(0xae); //Sleep In 

    write_reg(0xb3);	//Set Display Clock Divide Ratio/Oscillator Frequency 
    write_parameter(0x91);

    write_reg(0xca);	//Set Multiplex Ratio 
    write_parameter(0x3f);

    write_reg(0xa2);	//Set Display Offset 
    write_parameter(0x00);	//

    write_reg(0xa1);	//Set Display Start Line 
    write_parameter(0x00);	//

    write_reg(0xa0);	//Set Re-Map $ Dual COM Line Mode
    write_parameter(0x15);	//

    write_reg(0xB5);	//Set GPIO 
    write_parameter(0x00);
    	
    write_reg(0xab);	//Function Selection
    write_parameter(0x01);	//

    write_reg(0xb4);	//Enable External VSL 
    write_parameter(0xa0);	//
    write_parameter(0xfd);	//

    write_reg(0xc1);	//Set Contrast Current
    write_parameter(0xff);	

    write_reg(0xc7);	//Master Contrast Current Control
    write_parameter(0x0f);	//

    write_reg(0xb9);	//Select Default Linear Gray Scale Table 

    write_reg(0xb1);	//Set Phase Length
    write_parameter(0xe2);	

    write_reg(0xd1);	//Enhance Driving Scheme Capability 
    write_parameter(0x82);	
    write_parameter(0x20);	

    write_reg(0xbb);	//Set Pre-Charge Voltage 
    write_parameter(0x1f);	

    write_reg(0xb6);	//Set Second Pre-Charge Period 
    write_parameter(0x08);	

    write_reg(0xbe);	//Set VCOMH Deselect Level 
    write_parameter(0x07);		

    write_reg(0xa6);	//Set Display Mode

    write_reg(0xaf);	//Sleep Out

	is_lcdinit = 1;
    return 0;
	
}


