#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_


#define SPI_CPOLHA00   0	/* CPOL = 0, CPHA = 0 */
#define SPI_CPOLHA01   1		/* CPOL = 0, CPHA = 1 */
#define SPI_CPOLHA10   2		/* CPOL = 1, CPHA = 0 */
#define SPI_CPOLHA11   3		/* CPOL = 1, CPHA = 1 */


typedef struct tagspi_bus_t 
{
	_io_t  clk;
	_io_t  mosi;
	_io_t  miso;
	_io_t  cs;
	void * mutex;
} spi_bus_t;


typedef struct tagspi_dev_t 
{
	unsigned int mode;
	unsigned short delay_cnt;          /*spiÑÓ³Ù¼ÆÊý*/
    spi_bus_t *bus;
} spi_dev_t;


extern spi_bus_t spi_bus[3];

unsigned int  bsp_spi_init (void);
unsigned int  bsp_spi_cs_clr (spi_dev_t *poled_dev);
unsigned int  bsp_spi_cs_set (spi_dev_t *poled_dev);
void bsp_spi_send_byte (spi_dev_t *poled_dev, unsigned char ucData);
unsigned int  bsp_spi_recv_byte (spi_dev_t *poled_dev, unsigned char * pucData);

#endif 
