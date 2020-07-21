#ifndef _BSP_I2C_H_
#define _BSP_I2C_H_
#ifdef __cplusplus
extern "C"
{
#endif


#define i2c_mutex_key           (9101)  

typedef struct tag_io_t
{
    unsigned int data_mask;  
    unsigned int dir_mask;    
    unsigned int data_reg;    
    unsigned int dir_reg;     
}_io_t;


typedef struct tagi2c_bus_t
{
    unsigned char io_type;
    _io_t sda;
    _io_t scl;
    char sda_offset;
    char scl_offset;
    unsigned char status;
    void * mutex;
} i2c_bus_t;

typedef struct tagi2c_dev_t 
{
    unsigned char addr;
    unsigned char frequency;  
    unsigned short delay_cnt; 
    i2c_bus_t *p_i2c_bus;
    
} i2c_dev_t;


unsigned int  bsp_i2c_init (void);
unsigned int bsp_i2c_send(i2c_dev_t * dev ,unsigned char offset, \
							unsigned char send_len, unsigned char *p_data, \
							unsigned char *p_sended);
unsigned int bsp_i2c_rcv(i2c_dev_t * dev , unsigned char offset, unsigned int rcv_len, 
							unsigned char *p_data, unsigned int *p_rcved_len);


extern int   i2c_mutex;   
extern i2c_bus_t i2c_bus[3];

#ifdef __cplusplus
}
#endif


#endif

