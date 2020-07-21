#ifndef _BSP_TSENSOR_H_
#define _BSP_TSENSOR_H_
#ifdef __cplusplus
extern "C"
{
#endif


unsigned int bsp_tsensor_init(void);
unsigned int bsp_tsensor_read_local_temp(unsigned char * pucValue);
unsigned int bsp_tsensor_read_remote_temp(unsigned char * pucValue);
unsigned int bsp_tsensor_set_temp_high(unsigned char ucValue);
unsigned int bsp_tsensor_set_temp_low(unsigned char ucValue);
unsigned int bsp_tsensor_set_remote_temp_high(unsigned char ucValue);
unsigned int bsp_tsensor_set_remote_temp_low(unsigned char ucValue);
unsigned int bsp_tsensor_get_temp_high(unsigned char * pucValue);
unsigned int bsp_tsensor_get_temp_low(unsigned char * pucValue);
unsigned int bsp_tsensor_get_remote_temp_high(unsigned char * pucValue);
unsigned int bsp_tsensor_get_remote_temp_low(unsigned char * pucValue);
unsigned int bsp_tsensor_get_alarm_status(unsigned char * pucValue);
unsigned int bsp_tsensor_get_temperature(unsigned char ucFunID,unsigned char * pucValue);
unsigned int bsp_tsensor_set_temperature(unsigned char ucFunID,unsigned char  ucValue);

#ifdef __cplusplus
}
#endif

#endif

