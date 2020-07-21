
#include "vmm_eeprom_driver.h"
#include "vmm_epld_driver.h"
#include "vmm_i2c_driver.h"

#ifndef NULL
#define NULL 0
#endif

i2c_dev_t first_eeprom;
i2c_dev_t second_eeprom;

static int is_eepinit = 0;

#define PAGE_SIZE 16
#define CHIP_SIZE 512
#define SUB_SIZE  256
#define TOTAL_SIZE 512

#define ERR_WRITE_FAIL (1<<8)
#define ERR_EXCEED_LIMIT (2<<8)
#define ERR_READ_FAIL    (4<<8)
#define ERR_DEV  (8<<8)

void write_unprotect(i2c_dev_t *dev)
{
	if((dev->addr&0xfc) == 0xa8)
    {
		p_epld_start_addr[(0x42>>1)] &= ~(0x1);
    }
    else
    {
		p_epld_start_addr[(0x42>>1)] &= ~(0x2);
    }

    return;
}

void write_protect(i2c_dev_t *dev)
{	
	if((dev->addr&0xfc) == 0xa8)
	{

		p_epld_start_addr[(0x42>>1)] |= (0x1);
	}
	else
	{
		p_epld_start_addr[(0x42>>1)] |= (0x2);
	}

	return;
}

static unsigned int eeprom_write_bytes(i2c_dev_t * dev ,unsigned int offset, \
									unsigned int write_len, unsigned char *p_buf, \
									unsigned char *p_written)
{
    unsigned int ret = 0;

    write_unprotect(dev);

    ret = bsp_i2c_send(dev , (unsigned char)offset, (unsigned char)write_len, p_buf, p_written);
    if((0 != ret) ||((unsigned char)write_len != *p_written))
    {
        return ERR_WRITE_FAIL;
    }

	write_unprotect(dev);
    
    *p_written = write_len;
    return 0;

}


static unsigned int eeprom_write_page(i2c_dev_t * dev ,unsigned int offset,
										   unsigned int write_len ,unsigned char *p_buf, 
										   unsigned int * p_written)
{
    unsigned char once_len = 0;
    unsigned char once_sended = 0;
    unsigned int need_send = write_len;    
    unsigned int ret = 0;
    unsigned int page_spare_bytes = 0;

    page_spare_bytes = PAGE_SIZE - (offset%PAGE_SIZE);

    while(need_send > 0)
    {
        if(page_spare_bytes != 0)
        {
            once_len = (page_spare_bytes > need_send) ? need_send : page_spare_bytes;
            page_spare_bytes = 0;
        }
        else
        {
            once_len = (PAGE_SIZE > need_send) ? need_send : PAGE_SIZE;
        }

        
        ret = eeprom_write_bytes(dev, offset, once_len, p_buf, &once_sended);
        usleep(5000);
        if((0 != ret) || (once_len != once_sended))
        {
            * p_written += once_sended;
            return ret;
        }
        
        p_buf += once_sended;
        offset += once_sended;
        need_send -= once_sended;
        *p_written += once_sended;
    }
    return 0;
}


static i2c_dev_t * offset_to_dev(unsigned int *poffset,unsigned int write_len)
{
	if(*poffset >= 512)
	{
	    *poffset -= 512;
		return &second_eeprom;
	}
	else
	{
		return &first_eeprom;
	}
}


unsigned int  eeprom_snd_one_chip(unsigned int offset, unsigned int write_len, \
										 unsigned char *p_buf, unsigned int * p_written)
{
    unsigned int dwCurLen  = 0;
    unsigned int ret = 0;
    i2c_dev_t *ptCurEeprom = NULL;

    *p_written = 0;
    ptCurEeprom = offset_to_dev(&offset,write_len);

    if((offset + write_len) > (SUB_SIZE - 1))
    {
        if(offset <= (SUB_SIZE-1))
        {
            dwCurLen = SUB_SIZE - offset;
            ptCurEeprom->addr &= ~(0x02);
            ret = eeprom_write_page(ptCurEeprom,offset,dwCurLen,p_buf,p_written);
            if((0 != ret) || (*p_written != dwCurLen))
            {
                return ERR_WRITE_FAIL;
            }
            p_buf += dwCurLen;

            ptCurEeprom->addr |= 0x02;
            ret = eeprom_write_page(ptCurEeprom,0,(write_len - dwCurLen),p_buf,p_written);
            if((0 != ret) || (*p_written != write_len))
            {
                return ERR_WRITE_FAIL;
            }
        }
        else
        {
            ptCurEeprom->addr |= 0x02;

            offset -= SUB_SIZE;

            ret = eeprom_write_page(ptCurEeprom,offset,write_len,p_buf,p_written);
            if((0 != ret) || (*p_written != write_len))
            {
                return ERR_WRITE_FAIL;
            }
        }

    }
    else
    {
        ptCurEeprom->addr &= ~0x02;
        ret = eeprom_write_page(ptCurEeprom,offset,write_len,p_buf,p_written);
        if((0 != ret) || (*p_written != write_len))
        {
            return ERR_WRITE_FAIL;
        }
    }
    return 0;
}

unsigned int  eeprom_rcv_one_chip(unsigned int offset, unsigned int write_len, unsigned char *p_buf, unsigned int * p_rcv_len)
{
    unsigned int ret = 0;
    i2c_dev_t *ptCurEeprom = NULL;

    *p_rcv_len = 0;
    ptCurEeprom = offset_to_dev(&offset,write_len);

    if(offset > (SUB_SIZE - 1))
    {
        ptCurEeprom->addr |= 0x02;
        offset -= SUB_SIZE;
    }
    else
    {
        ptCurEeprom->addr &= ~0x02;
    }
    ret = bsp_i2c_rcv(ptCurEeprom , (unsigned char)offset, write_len, p_buf, p_rcv_len);
    if((0 != ret) ||(write_len != *p_rcv_len))
    {
        return ERR_READ_FAIL;
    }
    
    return 0;
}


unsigned int bsp_eeprom_init(void)
{
    unsigned int ret;

    if(is_eepinit == 1) 
    {
    	return 0;
    }

    ret = bsp_i2c_init();
    if(ret != 0)
    {
    	return ret;
    }
    
    first_eeprom.addr  = 0xa8;
    first_eeprom.frequency = 100;
    first_eeprom.p_i2c_bus = &i2c_bus[0];
    first_eeprom.delay_cnt = (unsigned short)((1000000L)/(90*100));

    second_eeprom.addr = 0xa4;
    second_eeprom.frequency = 100;
    second_eeprom.p_i2c_bus = &i2c_bus[0];
    second_eeprom.delay_cnt = (unsigned short)((1000000L)/(90*100));

    write_protect(&first_eeprom);
    i2c_take_semaphore(&first_eeprom);    
    ret = i2c_reset(&first_eeprom);    
    i2c_give_semaphore(&first_eeprom);

	if(ret == 0) 
	{
		is_eepinit = 1;
	}

	return ret;
}




unsigned int  bsp_eeprom_snd(unsigned int offset, unsigned int write_len, unsigned char *p_buf, unsigned int * p_written)
{
	unsigned int ret;

	//add this you don't worry about init
	ret = bsp_eeprom_init();
	if(ret != 0)
	{
		return ret;
	}
	
	if((offset + write_len) > TOTAL_SIZE)
	{
		return ERR_EXCEED_LIMIT;
	}

	if(((offset+write_len)<= CHIP_SIZE) || (offset >= CHIP_SIZE))
	{
		return eeprom_snd_one_chip(offset, write_len, p_buf, p_written);
	}
	else
	{
		unsigned int first_wlen = CHIP_SIZE-offset;
		unsigned int second_wlen = write_len-first_wlen;

		ret = eeprom_snd_one_chip(offset, first_wlen, p_buf, p_written);
		if((ret != 0) || (*p_written != first_wlen))
		{
			return ERR_WRITE_FAIL;
		}
		
		ret = eeprom_snd_one_chip(CHIP_SIZE, second_wlen, &p_buf[first_wlen], p_written);
		if((ret != 0) || (*p_written != second_wlen))
		{
			return ERR_WRITE_FAIL;
		}

		*p_written = write_len;

		return 0;
	}

}


unsigned int  bsp_eeprom_rcv(unsigned int offset, unsigned int write_len,
                         unsigned char *p_buf, unsigned int * p_rcv_len)
{
	unsigned int ret;

	ret = bsp_eeprom_init();
	if(ret != 0)
	{
		return ret;
	}

	if((offset + write_len) > TOTAL_SIZE)
	{
		return ERR_EXCEED_LIMIT;
	}

	if(((offset+write_len)<= CHIP_SIZE) || (offset >= CHIP_SIZE))
	{
		return eeprom_rcv_one_chip(offset, write_len, p_buf, p_rcv_len);
	}
	else
	{
		unsigned int first_wlen = CHIP_SIZE-offset;
		unsigned int second_wlen = write_len-first_wlen;

		ret = eeprom_rcv_one_chip(offset, first_wlen, p_buf, p_rcv_len);
		if((ret != 0) || (*p_rcv_len != first_wlen))
		{
			return ERR_READ_FAIL;
		}

		ret = eeprom_rcv_one_chip(CHIP_SIZE, second_wlen, &p_buf[first_wlen], p_rcv_len);
		if((ret != 0) || (*p_rcv_len != second_wlen))
		{
			return ERR_READ_FAIL;
		}

		*p_rcv_len = write_len;

		return 0;
	}
}



