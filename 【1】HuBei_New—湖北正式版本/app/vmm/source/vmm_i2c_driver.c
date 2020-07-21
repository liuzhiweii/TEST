#include "vmm_eeprom_driver.h"
#include "vmm_epld_driver.h"
#include "vmm_i2c_driver.h"

#include <sys/ipc.h>
#include <sys/sem.h>


int i2c_mutex = 0;  
i2c_bus_t i2c_bus[3];
static int is_i2cinit = 0;

#define ERR_BUSY   1
#define ERR_NO_ACK 2
#define ERR_RESET  3
#define ERR_CREATE_SEM 4
#define ERR_SET_SEM  5
#define ERR_TAKE_SEM 6
#define ERR_GIVE_SEM 7
#define ERR_INVALID_BUS 8

#define BUS_BUSY  0
#define BUS_FREE  1

#define ACK_RETRY_CNT 5
#define RESET_CNT  10

#define I2C1_SCL_REG  ((p_epld_start_addr + (0x3c>>1)))
#define I2C1_SDA_REG  ((p_epld_start_addr + (0x3c>>1)))

#define I2C2_SCL_REG  ((p_epld_start_addr + (0x4c>>1)))
#define I2C2_SDA_REG  ((p_epld_start_addr + (0x4c>>1)))

#define I2C3_SCL_REG   ((p_epld_start_addr + (0xe0>>1)))
#define I2C3_SDA_REG   ((p_epld_start_addr + (0xe0>>1)))



void i2c_delay(unsigned short delay_cnt)
{ 
    volatile unsigned int i = 0;
    
    while(i < delay_cnt)
    {
        i++;
    }
}

void i2c_scl_high(i2c_dev_t *dev)
{
	*((unsigned short *)((dev->p_i2c_bus->scl).data_reg)) |= (dev->p_i2c_bus->scl).data_mask;
	i2c_delay(dev->delay_cnt);
	return;
}

void i2c_scl_low(i2c_dev_t *dev)
{
	*((unsigned short *)((dev->p_i2c_bus->scl).data_reg)) &= ~((dev->p_i2c_bus->scl).data_mask);
	i2c_delay(dev->delay_cnt);
	return;
}

void i2c_sda_high(i2c_dev_t *dev)
{
    *((unsigned short *)((dev->p_i2c_bus->sda).data_reg)) |=  (dev->p_i2c_bus->sda).data_mask;
	i2c_delay(dev->delay_cnt);
    return;
}

void i2c_sda_low(i2c_dev_t *dev)
{	
	*((unsigned short *)((dev->p_i2c_bus->sda).data_reg)) &= ~((dev->p_i2c_bus->sda).data_mask);
	i2c_delay(dev->delay_cnt);
    return;
}

unsigned int i2c_scl(i2c_dev_t *dev)
{	
	unsigned int scl;
	scl =  (*((unsigned short *)((dev->p_i2c_bus->scl).data_reg + dev->p_i2c_bus->scl_offset * sizeof(T_EpldData)) ) & 
									(dev->p_i2c_bus->scl).data_mask) ? 1 : 0;
	i2c_delay(dev->delay_cnt);
	return scl;
}


unsigned int i2c_sda(i2c_dev_t *dev)
{	
	unsigned int sda;
	
	sda = (*((unsigned short *)((dev->p_i2c_bus->sda).data_reg +dev->p_i2c_bus->sda_offset * sizeof(T_EpldData)) ) & 
									(dev->p_i2c_bus->sda).data_mask) ? 1 : 0;
	i2c_delay(dev->delay_cnt);
	return sda;
}

static unsigned int i2c_bus_detect(i2c_dev_t *dev)
{
	i2c_sda_high(dev);
	
	if((1 != i2c_sda(dev)) || (1 != i2c_scl(dev)))
	{
	    return ERR_BUSY;
	}
	
    return 0;
}


unsigned int  i2c_start (i2c_dev_t *dev)
{
	unsigned int ret = 0;
	
    if(BUS_FREE == dev->p_i2c_bus->status)
    {
        ret = i2c_bus_detect(dev);
    	if(0 != ret)
    	{
    		return ret;	
    	}
    }

    i2c_sda_high(dev);
    i2c_scl_high(dev);
    i2c_sda_low(dev);
    i2c_scl_low(dev);
    dev->p_i2c_bus->status = BUS_BUSY;
    
	return 0;

}

unsigned int  i2c_stop (i2c_dev_t *dev)
{	
	i2c_sda_low(dev);
	i2c_scl_high(dev);
	i2c_sda_high(dev);

    dev->p_i2c_bus->status = BUS_FREE;

	return 0;
}

unsigned int i2c_send_byte(i2c_dev_t *dev, unsigned char data)
{
	int bits_cnt = 0;

	i2c_scl_low(dev);
	
	for(bits_cnt = 7; bits_cnt >= 0; bits_cnt--)
	{
		if(data & (1<< bits_cnt))
		{
			i2c_sda_high(dev);					
		}
		else
		{
			i2c_sda_low(dev);
		}

		i2c_scl_high(dev);
		i2c_scl_low(dev);
	}

	return 0;
}


unsigned int  i2c_rcv_byte (i2c_dev_t *dev , unsigned char * pdata)
{
	unsigned int sda_bit;
	
	int bits_cnt = 0;
	unsigned char temp = 0;
	
	i2c_scl_low(dev);

	for(bits_cnt = 7; bits_cnt >= 0; bits_cnt--)
	{
		i2c_scl_high(dev);
		sda_bit = i2c_sda(dev);				
		temp |= (sda_bit<< bits_cnt);
		i2c_scl_low(dev);
	}
	
    *pdata = temp;

    return 0;
}

void i2c_send_ack(i2c_dev_t *dev)
{
	i2c_sda_low(dev);
	i2c_scl_high(dev);
	i2c_scl_low(dev);	
	i2c_sda_high(dev);	

	return;
}

void i2c_send_nack(i2c_dev_t *dev)
{
	i2c_sda_high(dev);
	i2c_scl_high(dev);	
	i2c_scl_low(dev);	
	i2c_sda_high(dev);	

	return;
}

unsigned int  i2c_rcv_ack (i2c_dev_t *dev)
{
	unsigned int sda_bit;	
	unsigned char retry_cnt = 0;
		
	i2c_sda_high(dev);		
	i2c_scl_high(dev);
	
	do
	{
		sda_bit = i2c_sda(dev);
		retry_cnt++;
	}while ( (sda_bit != 0) && (retry_cnt < ACK_RETRY_CNT) );
	
	i2c_scl_low(dev);	
	
	if (0 != sda_bit)
	{
		return ERR_NO_ACK;
	}

	return 0;
}


unsigned int  i2c_reset (i2c_dev_t *dev)
{
	unsigned char i = 0;
	unsigned int sda_bit = 0;
	unsigned int scl_bit = 0;
       
	for(i = 0; i < RESET_CNT; i++)
	{
        i2c_scl_low(dev);            
        i2c_sda_low(dev);
        i2c_scl_high(dev);		
        i2c_sda_high(dev);

		sda_bit = i2c_sda(dev);
		scl_bit = i2c_scl(dev);

		if((sda_bit == 1) && (scl_bit == 1))
		{
			return 0;
		}			
	}

	return ERR_RESET;
}

unsigned int create_i2c_sem(void)
{
	unsigned int ret;

	union semun 
    {
        int val;
        unsigned short *array;
    } sem_union;

    sem_union.val = 1;

    i2c_mutex = semget((key_t)i2c_mutex_key, 3, (0666 | IPC_CREAT));
    if (-1 == i2c_mutex) 
    {
        return ERR_CREATE_SEM;	
    }
    if (-1 == semctl(i2c_mutex, 0, SETVAL, sem_union)) 
    {
        return ERR_SET_SEM;	
    }
    if (-1 == semctl(i2c_mutex, 1, SETVAL, sem_union)) 
    {
        return ERR_SET_SEM;	
    }
    if (-1 == semctl(i2c_mutex, 2, SETVAL, sem_union)) 
    {
        return ERR_SET_SEM;	
    }

    return 0;			
}


unsigned int i2c_init_dev(void)
{	
	unsigned int ret;
	
	ret = bsp_epld_init();
	if(ret !=0)
	{
		return ret;
	}

	i2c_bus[0].io_type = 0;	
	i2c_bus[0].scl.data_reg  = (unsigned int)I2C1_SCL_REG;
	i2c_bus[0].scl.data_mask = (unsigned int)2;
	i2c_bus[0].scl.dir_reg	 = (unsigned int)0;
	i2c_bus[0].scl.dir_mask  = (unsigned int)2; 
	i2c_bus[0].sda.data_reg  = (unsigned int)I2C1_SDA_REG;
	i2c_bus[0].sda.data_mask = (unsigned int)0x1;
	i2c_bus[0].sda.dir_reg	 = (unsigned int)0;
	i2c_bus[0].sda.dir_mask  = (unsigned int)0x1;
	i2c_bus[0].scl_offset = 0x1;
	i2c_bus[0].sda_offset = 0x1;
	i2c_bus[0].status = BUS_FREE;
	i2c_bus[0].mutex = &i2c_mutex;
	p_epld_start_addr[0x40>>1] |= 0x01;
	
	i2c_bus[1].io_type = 0;	
	i2c_bus[1].scl.data_reg  = (unsigned int)I2C2_SCL_REG;
	i2c_bus[1].scl.data_mask = (unsigned int)0x2;
	i2c_bus[1].scl.dir_reg	 = (unsigned int)0x0;
	i2c_bus[1].scl.dir_mask  = (unsigned int)0x2;	
	i2c_bus[1].sda.data_reg  = (unsigned int)I2C2_SDA_REG;
	i2c_bus[1].sda.data_mask = (unsigned int)0x1;
	i2c_bus[1].sda.dir_reg	 = (unsigned int)0;
	i2c_bus[1].sda.dir_mask  = (unsigned int)0x1;
	i2c_bus[1].scl_offset = 0x1;
	i2c_bus[1].sda_offset = 0x1;
	i2c_bus[1].status = BUS_FREE;
	i2c_bus[1].mutex = &i2c_mutex;
	
	p_epld_start_addr[0x48 >> 1] |= 0x01;
	
	i2c_bus[2].io_type = 0;	
	i2c_bus[2].scl.data_reg  = (unsigned int)I2C3_SCL_REG;
	i2c_bus[2].scl.data_mask = (unsigned int)0x2;
	i2c_bus[2].scl.dir_reg	 = (unsigned int)0x0;
	i2c_bus[2].scl.dir_mask  = (unsigned int)0x2;	
	i2c_bus[2].sda.data_reg  = (unsigned int)I2C3_SDA_REG;
	i2c_bus[2].sda.data_mask = (unsigned int)0x1;
	i2c_bus[2].sda.dir_reg	 = (unsigned int)0;
	i2c_bus[2].sda.dir_mask  = (unsigned int)0x1;
	i2c_bus[2].scl_offset			= 0x6;
	i2c_bus[2].sda_offset			= 0x6;
	 i2c_bus[2].status			 = BUS_FREE;
	i2c_bus[2].mutex = &i2c_mutex;
	p_epld_start_addr[0x28] |= 0x01;

	return 0;
}

unsigned int i2c_take_semaphore(i2c_dev_t *dev)
{
	unsigned int ret;
    struct sembuf sem_buf;
    
    sem_buf.sem_op = -1;
    
    if(dev->p_i2c_bus == &i2c_bus[0])
    {
        sem_buf.sem_num = 0;
    }
    else if (dev->p_i2c_bus == &i2c_bus[1])
    {
        sem_buf.sem_num = 1;
    }
    else if (dev->p_i2c_bus == &i2c_bus[2])
    {
        sem_buf.sem_num = 2;
    }
    else
    {
        return ERR_INVALID_BUS;
    }
    
    sem_buf.sem_flg = SEM_UNDO;
    ret = semop(*((int*)(dev->p_i2c_bus->mutex)), &sem_buf, 1);
    if (-1 == ret) 
    {
        perror("i2c_take_semaphore failed:");
        return ERR_TAKE_SEM;	
    }
    
    return 0;
}

unsigned int i2c_give_semaphore(i2c_dev_t *dev)
{
    int ret = 0;

    struct sembuf sem_buf;
    sem_buf.sem_op = 1;
    
    if(dev->p_i2c_bus == &i2c_bus[0])
    {
        sem_buf.sem_num = 0;
    }
    else if (dev->p_i2c_bus == &i2c_bus[1])
    {
        sem_buf.sem_num = 1;
    }
    else if (dev->p_i2c_bus == &i2c_bus[2])
    {
        sem_buf.sem_num = 2;
    }
    else
    {
        return ERR_INVALID_BUS;
    }
    
    sem_buf.sem_flg = SEM_UNDO;
    ret = semop(*((int*)(dev->p_i2c_bus->mutex)), &sem_buf, 1);
    if (-1 == ret) 
    {
        perror("i2c_give_semaphore failed:");
        return ERR_GIVE_SEM;	
    }
	
    return 0;
}


unsigned int  bsp_i2c_init (void)
{
	unsigned int ret;

	if(is_i2cinit == 1)
	{
		return 0;
	}

	ret = create_i2c_sem();
	if(ret != 0)
	{
		return ret;
	}
	
	ret = i2c_init_dev();
	if(ret != 0)
	{
		return ret;
	}

	is_i2cinit = 1;
	return 0;
}


unsigned int bsp_i2c_send(i2c_dev_t * dev ,unsigned char offset, \
							unsigned char send_len, unsigned char *p_data, \
							unsigned char *p_sended)
{
	unsigned char i = 0;	
	unsigned int ret = 0;

	ret = bsp_i2c_init();
	if(ret != 0)
	{
		return ret;
	}
	
	*p_sended = 0;

	ret = i2c_take_semaphore(dev);
	if(0 != ret)
    {
        return ret;
    }
	ret = i2c_start(dev);
	if(0 != ret)
	{
		i2c_give_semaphore(dev);
        return ret;
	}
	i2c_send_byte(dev, (dev->addr & 0xfe));
	ret = i2c_rcv_ack(dev);
	if(0 != ret)
	{
        i2c_stop(dev);
		i2c_give_semaphore(dev);
        return ret;
	}

	i2c_send_byte(dev, offset);
	ret = i2c_rcv_ack(dev);
	if(0 != ret)
	{
        i2c_stop(dev);
		i2c_give_semaphore(dev);
        return ret;
	}

	for(i = 0; i < send_len; i++)
	{
		i2c_send_byte(dev, *p_data);
		ret = i2c_rcv_ack(dev);
		if(0 != ret)
		{
            i2c_stop(dev);
			*p_sended = i + 1;
			i2c_give_semaphore(dev);
            return ret;
		}
		p_data++;
	}

	i2c_stop (dev);

	ret = i2c_give_semaphore(dev);
    if(0 != ret)
    {
        return ret;
    }
    
    *p_sended = send_len;
	return 0;

}


unsigned int bsp_i2c_rcv(i2c_dev_t * dev , unsigned char offset, unsigned int rcv_len, 
							unsigned char *p_data, unsigned int *p_rcved_len)
{
	unsigned int dwByteCnt = 0;
	unsigned int ret = 0;

	//add this, you don't worry about init
	ret = bsp_i2c_init();
	if(ret != 0)
	{
		return ret;
	}
	
	*p_rcved_len = 0;
   
	ret = i2c_take_semaphore(dev);
    if(0 != ret)
    {
        return ret;
    }
	ret = i2c_start(dev);
	if(0  != ret)
	{
		i2c_give_semaphore(dev);
        return ret;
	}

	i2c_send_byte(dev, (dev->addr & 0xfe));
	ret = i2c_rcv_ack(dev);
	if(0 != ret)
	{
        i2c_stop(dev);
		i2c_give_semaphore(dev);
        return ret;
	}

	i2c_send_byte(dev, offset);
	ret = i2c_rcv_ack(dev);
	if(0 != ret)
	{        
        i2c_stop(dev);
		i2c_give_semaphore(dev);
        return ret;
	}

	ret = i2c_start(dev);
	if(0  != ret)
	{
		 i2c_give_semaphore(dev);
         return ret;
	}

	i2c_send_byte(dev, dev->addr | 0x1);
	ret = i2c_rcv_ack(dev);
	if(0  != ret)
	{
        i2c_stop(dev);
		i2c_give_semaphore(dev);
        return ret;
	}

	for (dwByteCnt = 0; dwByteCnt < rcv_len; dwByteCnt++)
	{
		i2c_rcv_byte(dev, p_data);
		p_data++;

		if (dwByteCnt < (rcv_len - 1)) 
		{
			i2c_send_ack(dev);
		}
		else
		{
			i2c_send_nack(dev);
		}
	}

	i2c_stop(dev);
	
	ret = i2c_give_semaphore(dev);
    if(0 != ret)
    {
        return ret;
    }
    
    *p_rcved_len = rcv_len;

    return 0;
}


