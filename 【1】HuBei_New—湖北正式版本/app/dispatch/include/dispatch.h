#ifndef __DISPATCH_H__
#define __DISPATCH_H__
//EEPROM id address
#define  EEPROM_ETH1_IP_ADDR         0x33  /*33 34 35 36*/

#define DIS_DEBUG logm_debug


#define TIMER_DISPATCH_BASE 10
#define TIMER_DISPATCH_BST  (TIMER_DISPATCH_BASE)
#define TIMER_DISPATCH_ACTION  (TIMER_DISPATCH_BASE+1)

#define DISPATCH_SET_TIMER_MS(timer_id,msec)       set_timer(timer_id, (msec/1000), ((msec%1000)*1000),0)

#define CHECK_FAIL_NUMBER(p,s)                             \
do\
{\
    if((p)<0)                                 \
    {                                             \
       printf("%s file:%s line:%u\r\n",s,__FILE__,__LINE__);\
       abn_debug("%s file:%s line:%u\r\n",s,__FILE__,__LINE__);\
       exit(-1);                                 \
    }\
}while(0)


#pragma pack(1)
typedef struct tag_init_device_t
{	
    unsigned char cmd_type;
	unsigned int date_time;
	unsigned char bst_interval;
	unsigned char tx_power;
	unsigned char pll_channelID;
	unsigned short time_out;
}init_device_t;

typedef struct tag_psam_reset_t
{	
    unsigned char cmd_type;
	unsigned char psam_slot;
	unsigned char psam_bandrate;
}psam_reset_t;

typedef struct tag_device_info_t
{	
    unsigned char firm_code;
	unsigned char device_number[3];
	unsigned short version;
}device_info_t;


typedef struct tag_init_device_ack_t
{	
    unsigned char frame_type;
	unsigned char status;
	unsigned char info_len;
	device_info_t device_info;
}init_device_ack_t;

typedef struct tag_psam_reset_ack_t
{	
    unsigned char frame_type;
	unsigned char status;
	unsigned char info_len;
	unsigned char reset_data[128];
}psam_reset_ack_t;


#pragma pack()

#endif
