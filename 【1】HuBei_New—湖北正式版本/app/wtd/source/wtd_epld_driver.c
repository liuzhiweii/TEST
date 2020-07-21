#include <fcntl.h>
#include <sys/mman.h> 

#define ERR_MAP_FAIL  1
#define ERR_OPEN_FAIL 2
#define ERR_ADDR_EXCEED 3

#ifndef NULL
#define NULL 0
#endif


volatile unsigned short *p_epld_start_addr = NULL;
static volatile int epld_fd   = -1;
static volatile unsigned int is_epld_init  = 0;


unsigned int bsp_epld_init(void)
{
    unsigned int ret;
    
    if (0 == is_epld_init)
    {
        epld_fd = open("/dev/misc/drv_epld", O_RDWR);
        if (-1 != epld_fd)
        {
            p_epld_start_addr = (unsigned short *)mmap(0, (0x400000), 
                                                   PROT_READ | PROT_WRITE, 
                                                   MAP_SHARED, epld_fd, 0);
            if (NULL == p_epld_start_addr )
            {
            	close(epld_fd);
            	return ERR_MAP_FAIL;
            }
            else
            {
            	is_epld_init = 1;
            }
        }
        else
        {
            return  ERR_OPEN_FAIL;
        }
    }

    return 0;
}


unsigned int bsp_epld_read(unsigned int offset, unsigned short * p_value)
{
    unsigned int ret;
    
    ret = bsp_epld_init();
    if(ret != 0)
    {
    	return ret;
    }
    
	if (offset >= 0x400000)
	{
	    return ERR_ADDR_EXCEED;
	}

	*p_value = p_epld_start_addr[offset];
	return 0;
}

unsigned int bsp_epld_write(unsigned int offset, unsigned short value)
{
    unsigned int ret;
    
    ret = bsp_epld_init();
    if(ret != 0)
    {
    	return ret;
    }
    
    if (offset >= 0x400000)
    {
        return ERR_ADDR_EXCEED;
    }
    p_epld_start_addr[offset] = value;
    
    return 0;
}

