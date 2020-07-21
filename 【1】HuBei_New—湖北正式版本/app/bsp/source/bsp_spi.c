#include <sys/ipc.h>
#include <sys/sem.h>
#include "bsp.h"


int   spi_mutex = 0;  
spi_bus_t spi_bus[3];
unsigned int is_spiinit = 0;

extern volatile unsigned short *p_epld_start_addr;


void spi_delay(unsigned short delay_cnt)
{ 
    volatile unsigned int i = 0;
    while(i < delay_cnt)
    {
        i++;
    }
    return;
}

void mosi_high(spi_dev_t *dev)
{
	*((unsigned short *)((dev->bus->mosi).data_reg)) |= (dev->bus->mosi).data_mask;
	spi_delay(dev->delay_cnt);
	return;
}

void mosi_low(spi_dev_t *dev)
{	
	*((unsigned short *)((dev->bus->mosi).data_reg)) &= ~((dev->bus->mosi).data_mask);
	spi_delay(dev->delay_cnt);
	return;
}

void clk_high(spi_dev_t *dev)
{	
	*((unsigned short *)((dev->bus->clk).data_reg)) |= (dev->bus->clk).data_mask;
	spi_delay(dev->delay_cnt);
	return;
}

void clk_low(spi_dev_t *dev)
{	
	*((unsigned short *)((dev->bus->clk).data_reg)) &= ~((dev->bus->clk).data_mask);
	spi_delay(dev->delay_cnt);
	return;
}

void cs_high(spi_dev_t *dev)
{	
	*((unsigned short *)((dev->bus->cs).data_reg)) |= (dev->bus->cs).data_mask;
	spi_delay(dev->delay_cnt);
	return;
}

void cs_low(spi_dev_t *dev)
{	
	*((unsigned short *)((dev->bus->cs).data_reg)) &= ~((dev->bus->cs).data_mask);
	spi_delay(dev->delay_cnt);
	return;
}

unsigned int miso_bit(spi_dev_t *dev)
{	
	return (*((unsigned short *)((dev->bus->miso).data_reg)) & (dev->bus->miso).data_mask) ? 1 : 0;
}

unsigned int spi_take_sem(spi_dev_t *dev)
{
    int ret = 0;

    struct sembuf tSemBuf;
    tSemBuf.sem_op = -1;
    if(dev->bus == &spi_bus[0])
    {
        tSemBuf.sem_num = 0;
    }
    else if (dev->bus == &spi_bus[1])
    {
        tSemBuf.sem_num = 1;
    }
    else if (dev->bus == &spi_bus[2])
    {
        tSemBuf.sem_num = 2;
    }
    else
    {
        return 6;
    }
    tSemBuf.sem_flg = SEM_UNDO;
    ret = semop(*((int*)(dev->bus->mutex)), &tSemBuf, 1);
    if (-1 == ret) 
    {
        return 7;	
    }
    return 0;
}

unsigned int spi_give_sem(spi_dev_t *dev)
{
    int ret = 0;
    if(NULL == dev)
    {
        return 8;
    }
    struct sembuf tSemBuf;
    tSemBuf.sem_op = 1;
    if(dev->bus == &spi_bus[0])
    {
        tSemBuf.sem_num = 0;
    }
    else if (dev->bus == &spi_bus[1])
    {
        tSemBuf.sem_num = 1;
    }
    else if (dev->bus == &spi_bus[2])
    {
        tSemBuf.sem_num = 2;
    }
    else
    {
        return 9;
    }
    tSemBuf.sem_flg = SEM_UNDO;
    ret = semop(*((int*)(dev->bus->mutex)), &tSemBuf, 1);
    if (-1 == ret) 
    {
        return 10;	
    }
	
    return 0;
}

unsigned int bsp_spi_cs_clr (spi_dev_t *dev)
{
    cs_low(dev);
    return 0;
}

unsigned int bsp_spi_cs_set(spi_dev_t *dev)
{
	cs_high(dev);
    return 0;
}


unsigned int create_spi_sem(void)
{
	union semun 
    {
        int val;
        unsigned short *array;
    } sem_union;

    sem_union.val = 1;
    spi_mutex = semget((key_t)9102, 3, (0666 | IPC_CREAT));
    if (-1 == spi_mutex) 
    {
        return 1;	
    }
    if (-1 == semctl(spi_mutex, 0, SETVAL, sem_union)) 
    {
        return 2;	
    }
    if (-1 == semctl(spi_mutex, 1, SETVAL, sem_union)) 
    {
        return 3;	
    }
    if (-1 == semctl(spi_mutex, 2, SETVAL, sem_union)) 
    {
        return 4;	
    }

    return 0;
}



unsigned int bsp_spi_init (void)
{
    unsigned int ret;

    if(is_spiinit == 1)
    {
    	return 0;
    }

    ret = create_spi_sem();
    if(ret != 0)
    {
    	return ret;
    }

	ret = bsp_epld_init();
	if(ret != 0)
	{
    	return ret;
	}

    spi_bus[0].cs.data_reg = (p_epld_start_addr + (0xe6>>1)); 
    spi_bus[0].cs.data_mask = 0x01;
    spi_bus[0].clk.data_reg = (p_epld_start_addr + (0xe4>>1)); 
    spi_bus[0].clk.data_mask = 0x01;
    spi_bus[0].mosi.data_reg = (p_epld_start_addr + (0xe2>>1)); 
    spi_bus[0].mosi.data_mask = 0x01;
    spi_bus[0].miso.data_reg = (p_epld_start_addr + (0xe2>>1)); 
    spi_bus[0].miso.data_mask = 0x02;
    spi_bus[0].mutex = &spi_mutex; 

	is_spiinit = 1;
    return 0;
}



void bsp_spi_send_byte (spi_dev_t *dev, unsigned char data)
{
    unsigned char i = 0;

    if (SPI_CPOLHA00 == dev->mode)
    {
        for (i = 0; i < 8; i++ )
        {
            if (data &(1 << 7))   
            {
                mosi_high(dev);
            }
            else
            {
                mosi_low(dev);
            }
            data <<= 1;
            clk_high(dev);
            clk_low(dev);
        }
    }
    else if (SPI_CPOLHA01 == dev->mode)
    {
        for (i = 0; i < 8; i++ )
        {
            clk_high(dev);
            if (data &(1 << 7))   /* MSB先传输 */
            {
                mosi_high(dev);
            }
            else
            {
                mosi_low(dev);
            }
            data <<= 1;
            clk_low(dev);
        }
    }
    else if (SPI_CPOLHA10 == dev->mode)
    {
        for (i = 0; i < 8; i++ )
        {
            if (data &(1 << 7))   /* MSB先传输 */
            {
                mosi_high(dev);
            }
            else
            {
                mosi_low(dev);
            }
            data <<= 1;
            clk_low(dev);
            clk_high(dev);
        }
    }
    else if (SPI_CPOLHA11 == dev->mode)
    {
        for (i = 0; i < 8; i++ )
        {
            clk_low(dev);
            if (data &(1 << 7))   /* MSB先传输 */
            {
                mosi_high(dev);
            }
            else
            {
                mosi_low(dev);
            }
            data <<= 1;
            clk_high(dev);
        }
    }

    return 0;
}


unsigned int bsp_spi_recv_byte (spi_dev_t *dev, unsigned char * pdata)
{
    unsigned char bit_cnts = 0;
    unsigned int miso;
    unsigned char byte_value = 0;
    

    if (SPI_CPOLHA00 == dev->mode)
    {
        for (bit_cnts = 7; bit_cnts > 0; bit_cnts-- )
        {
            clk_high(dev);
            miso = miso_bit(dev);
            byte_value |= (miso << bit_cnts);
            clk_low(dev);
        }

    }
    else if (SPI_CPOLHA01 == dev->mode)
    {
        for (bit_cnts = 7; bit_cnts > 0; bit_cnts-- )
        {
            clk_high(dev);
            clk_low(dev);
            miso = miso_bit(dev);
            byte_value |= (miso << bit_cnts);
        }

    }

    else if (SPI_CPOLHA10 == dev->mode)
    {
        for (bit_cnts = 7; bit_cnts > 0; bit_cnts-- )
        {

            clk_low(dev);

            miso = miso_bit(dev);
            byte_value |= (miso << bit_cnts);

            clk_high(dev);

        }
    }
    else if (SPI_CPOLHA11 == dev->mode)
    {
        for (bit_cnts = 7; bit_cnts > 0; bit_cnts-- )
        {

            clk_low(dev);
            clk_high(dev);

            miso = miso_bit(dev);
            byte_value |= (miso << bit_cnts);
        }
    }
    
    *pdata = byte_value;
    
    return 0;
}

