#ifndef __RFS_H__
#define __RFS_H__

#define RFS_DEBUG logm_debug
#define FPGA_SEND_DATA_ADDR 0x80200
#define RECV_FRAME_TIMEOUT 200
#define CALABRATE_TABLE_NUM 5
#define CALABRATE_CHANNEL_NUM 4
#define CALABRATE_TABLE_DATA_NUM 2
#define CALABRATE_MAX_TIMES 3
#define BACKWORD_PHASE_CALIBRATE_NUM 16
#define BACKWORD_PHASE_CALIBRATE_MAX_TIMES 10

#define PI 3.1415926



#define CALABRATE_DATA_EEPROM_ADDR 0x00
#define FORWARD_PHASE_CALIBRATE_EEPROM_ADDR 420
#define BACKWARD_PHASE_CALIBRATE_EEPROM_ADDR 580




#define CHECK_FAIL_NUMBER(p,s)                             \
do\
{\
    if((p)<0)                                 \
    {                                             \
       logm_debug("%s file:%s line:%u\r\n",s,__FILE__,__LINE__);\
       exit(-1);                                 \
    }\
}while(0)

#define CHECK_NULL_POINTER_RETURN_VOID(p)\
		do\
		{\
			if(NULL==(p))								  \
			{											  \
			   logm_debug("null pointer error file:%s line:%u\r\n",__FILE__,__LINE__);\
			   return ; 								\
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


typedef struct tag_forward_phase_calibration_t
{	
	unsigned char has_calibrated;
	unsigned char phase_diff[CALABRATE_CHANNEL_NUM];
}forward_phase_calibration_t;

typedef struct tag_backward_phase_calibration_t
{	
	unsigned char has_calibrated;
	double phase_diff[BACKWORD_PHASE_CALIBRATE_NUM];
}backward_phase_calibration_t;



#pragma pack()

typedef struct tag_calabrate_table_t
{	
	unsigned short vva;
	unsigned short datt;
	         short real_power;
	unsigned short adc;
}calabrate_table_t;

typedef struct tag_calabrate_table_data_t
{	
	calabrate_table_t calabrate_table[CALABRATE_TABLE_DATA_NUM];
}calabrate_table_data_t;


typedef struct tag_calabrate_data_t
{	
	calabrate_table_data_t calabrate_table_data[CALABRATE_CHANNEL_NUM][CALABRATE_TABLE_NUM];
}calabrate_data_t;

typedef struct tag_rfs_ctl_t
{	
	unsigned char bst_interval;
	unsigned char tx_power;
	unsigned char pll_channelID;
	unsigned char pad_b;
	unsigned short send_frame_num;
	unsigned short time_out;
	unsigned short vva;
	unsigned short reg_c0; //开关
	unsigned short reg_c1; //en-tx开关
	unsigned short reg_9d; //pll开关
	unsigned short datt[CALABRATE_CHANNEL_NUM];//定标后四个通道的datt
	forward_phase_calibration_t forward_phase_calibration;
	backward_phase_calibration_t backward_phase_calibration;
}rfs_ctl_t;


int calibrate_forward_phase();


#endif
