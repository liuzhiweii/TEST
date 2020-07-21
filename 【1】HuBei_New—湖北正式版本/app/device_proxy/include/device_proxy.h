#ifndef __DEVICE_PROXY__
#define __DEVICE_PROXY__


struct msg_proc_t
{
    unsigned int device_type;
    void (*action)(unsigned char *proc_args);
};

struct fpga_action_t 
{
    unsigned int action_type;
    void (*action)(unsigned char *action_args);
};


struct device_action_t 
{
    unsigned int action_type;
    void (*action)(unsigned char *action_args);
};


#define DEVICE_FPGA    1
#define DEVICE_EEPROM  2
#define DEVICE_PLL     3
#define DEVICE_EPLD    4
#define DEVICE_RTC     5
#define DEVICE_SENSOR  6
#define DEVICE_PSAM    7

#define _fpga_init  1
#define _fpga_read_reg  2
#define _fpga_write_reg  3
#define _fpga_read_frame  4
#define _fpga_write_frame  5

#define _pll_init   1
#define _pll_read  2
#define _pll_write 3

#define _epld_init  1
#define _epld_read  2
#define _epld_write 3
#define _epld_write_fifo 4

#define _rtc_init  1
#define _rtc_read  2
#define _rtc_set   3

#define  _sensor_init   1
#define  _set_local_limit   2        
#define  _set_remote_limit  3
#define  _read_local_limit  4
#define  _read_remote_limit  5
#define  _read_local_temp    6
#define  _read_remote_temp   7
#define  _read_sensor_status   8

#define _psam_init  1
#define _psam_active 2
#define _psam_setclk 3
#define _psam_exchange_apdu 4
#define _psam_deactive 5

void fpga_init(unsigned char *args);
void fpga_read_reg(unsigned char *args);
void fpga_write_reg(unsigned char *args);

void fpga_ctrl(unsigned char *args);

void eeprom_ctrl(unsigned char *args);
void pll_ctrl(unsigned char *args);
void epld_ctrl(unsigned char *args);

void pll_init(unsigned char *args);
void pll_read(unsigned char *args);
void pll_write(unsigned char *args);

void epld_init(unsigned char *args);
void epld_read(unsigned char *args);
void epld_write(unsigned char *args);
void epld_write_fifo(unsigned char *args);

void eeprom_init(unsigned char *args);

void eeprom_write(unsigned char *args);

void eeprom_read(unsigned char *args);

void rtc_ctrl(unsigned char * args);

void rtc_init(unsigned char * args);

void rtc_set(unsigned char * args);

void rtc_read(unsigned char * args);

void sensor_ctrl(unsigned char *args);
void sensor_init(unsigned char *args);
void set_local_limit(unsigned char *args);
void set_remote_limit(unsigned char *args);
void read_local_limit(unsigned char *args);
void read_remote_limit(unsigned char *args);
void read_local_temp(unsigned char *args);
void read_remote_temp(unsigned char *args);
void read_sensor_status(unsigned char *args);

void psam_ctrl(unsigned char *args);
void psam_init(unsigned char *args);
void psam_active(unsigned char *args);
void psam_setclk(unsigned char *args);
void psam_exchange_apdu(unsigned char *args);
void psam_deactive(unsigned char *args);

#endif

