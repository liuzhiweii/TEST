#ifndef __RSU_MANAGER__
#define __RSU_MANAGER__


#define set_send_tick            0x11
#define query_ant                0x80
#define set_beaconid             0x81
#define set_default_config       0x82
#define set_lane_mode            0x83
#define set_ant_config           0x84
#define set_psam_config          0x85
#define set_congtrol_master_ip   0x86
#define set_control_id           0x87
#define set_time_para            0x88
#define set_coordinate_limit     0x89
#define set_workmode             0x8a
#define set_coil_trigger         0x8b
#define set_rfsmode              0x8c
#define set_antmode_switch       0x8d
#define set_vst_len              0x8e
#define set_beaconid_test        0xfd

#define query_ant_ack            0x90
#define set_beaconid_ack         0x91
#define set_default_config_ack   0x92
#define set_lane_mode_ack        0x93
#define set_ant_config_ack       0x94
#define set_psam_config_ack      0x95
#define set_master_ip_ack        0x96
#define set_control_id_ack       0x97
#define set_time_para_ack        0x98
#define set_coordinate_limit_ack 0x99
#define set_workmode_ack         0x9a
#define set_coil_trigger_ack     0x9b
#define set_rfsmode_ack          0x9c
#define set_antmode_switch_ack   0x9d
#define set_vst_len_ack          0x9e
#define set_beaconid_test_ack    0xed

#define SET_POWER         0x60
#define SET_CHANNEL       0x61

#define SET_POWER_ACK      0x70
#define SET_CHANNEL_ACK    0x71


#define RF_TEST_INIT              0xFE
#define RF_TEST_SEND              0xFB
#define RF_TEST_RECV              0xFC


#define RF_TEST_INIT_ACK          0xEA
#define RF_TEST_SEND_ACK          0xEB
#define RF_TEST_RECV_ACK          0xEC



#define ACTION_OPEN_ANT    1
#define ACTION_CLOSE_ANT   0

#define ACTION_QUERY_ANT   3

#define ACTION_SET_BEACONID  1
#define ACTION_QUERY_BEACONID 2

#define ACTION_SET_ROUTE_INFO 1
#define ACTION_QUERY_ROUTE_INFO 2


#define ACTION_SET_TRADE_MODE  1
#define ACTION_QUERY_TRADE_MODE 2

#define ACTION_SET_SLEEPTIME  1
#define ACTION_QUERY_SLEEPTIME 2

#define ACTION_SET_WORKMODE  1
#define ACTION_QUERY_WORKMODE 2


#define ACTION_SET_TIMEPARA  1
#define ACTION_QUERY_TIMEPARA 2

#define ACTION_SET_SERVERIP 1
#define ACTION_READ_SERVERIP 2

#define ACTION_SET_PSAMCONFIG 1
#define ACTION_READ_PSAMCONFIG 2

#define ACTION_SET_RFCONFIG 1
#define ACTION_READ_RFCONFIG 2

#define ACTION_SET_PARALLEL 1
#define ACTION_READ_PARALLEL 2

#define ACTION_SET_LANEMODE 1
#define ACTION_READ_LANEMODE 2

#define ACTION_SET_DEFAULT_CONFIG 1



#define REBOOT_RSU               0xDF
#define REBOOT_RSU_ACK           0xFD

#define INIT_RSU                 0xC0
#define AFTER_ACK_INIT_OPEN_ANT  0xC1
#define INIT_RSU_ACK             0xB0
#define PC_CTRL_RSU_PORT         0xC4
#define PC_OPEN_CLOSE_ANT        0x4C
#define COIL_TRIGGER             0xFA
#define PC_CTRL_RFID             0xCD
#define INIT_SAFETY_MEDIA        0xCA
#define INIT_SAFETY_ACK          0xBA
#define AUTHORIZE_SAFETY_MEDIA   0xCB
#define AUTHORIZE_SAFETY_ACK     0xBB




typedef struct
{
	unsigned char cmdtype;
	unsigned char power;
}set_power_t;


typedef struct
{
	unsigned char acktype;
	unsigned char status;
}set_power_ack_t;

typedef struct
{
	unsigned char cmdtype;
	unsigned char channel;
}set_channel_t;

typedef struct
{
	unsigned char acktype;
	unsigned char status;
}set_channel_ack_t;


typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
}open_ant_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char ant_status;
}open_ant_ack_t;

#pragma pack(1)
typedef struct
{
	unsigned char cmd_type;
	//unsigned char DgNum;
	unsigned char coil_status;
}coil_status_t;
#pragma pack(1)
/***********新增**************///lzw
typedef struct
{
	unsigned char cmd_type;
	unsigned char rsu_id;
}pc_ctrl_state_t;






typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char ifchange;
	unsigned char change_cycle; //seconds
	unsigned char beaconid[4];
}set_beaconid_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char ifchange;
	unsigned char change_cycle; //seconds
	unsigned char beaconid[4];
}set_beaconid_ack_t;

#pragma pack(1)
typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	int coordinate_x1;
	int coordinate_x2;
	int coordinate_y_max;
	int coordinate_y_min;
	int coordinate_sub_y;
	int coordinate_sub_x1;
	int coordinate_sub_x2;
	unsigned char ifusing;
}set_coordinate_t;

#pragma pack(1)
typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	int coordinate_x1;
	int coordinate_x2;
	int coordinate_y_max;
	int coordinate_y_min;
	int coordinate_sub_y;
	int coordinate_sub_x1;
	int coordinate_sub_x2;
	unsigned char ifusing;	
}set_coordinate_ack_t;


#pragma pack(1)
typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char coil_trig_antenna;
	unsigned char coil_trig_confine_ifuse;
	int coil_trig_confine;
}set_coil_trigger_t;

#pragma pack(1)
typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char coil_trig_antenna;
	unsigned char coil_trig_confine_ifuse;
	int coil_trig_confine;
}set_coil_trigger_ack_t;


typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char aid;
	unsigned char mode;
	unsigned char trade_schme;
}set_trade_mode_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char aid;
	unsigned char mode;
	unsigned char trade_schme;
}set_trade_mode_ack_t;



typedef struct
{
	unsigned char antid;
	unsigned char ifenable;
	unsigned char power;
	unsigned char channel;
	unsigned char ipaddr[4];
}ant_config_t;

typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	ant_config_t config[5];
}set_ant_config_t;


typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	ant_config_t config[5];
}set_ant_config_ack_t;


typedef struct
{
	unsigned char psamid;
	unsigned char ifenable;
	unsigned char type;
}psam_config_t;

typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	psam_config_t config[12];	
}set_psam_config_t;


typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	psam_config_t config[12];
}set_psam_config_ack_t;


typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char number;
}set_parallel_number_t;

typedef struct 
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char control_master_ip[24];
	
}set_control_master_ip_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char number;
}set_control_id_ack_t;

typedef struct 
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char control_master_ip[24];
}set_control_master_ip_ack_t;

typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char lanemode;
	unsigned char etcmtc;
}set_lane_mode_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char lanemode;
	unsigned char etcmtc;
}set_lane_mode_ack_t;

typedef struct 
{
	unsigned char cmd_type;
	unsigned char action_type;
}set_default_config_t;

typedef struct 
{
	unsigned char ack_type;
	unsigned char status;
}set_default_config_ack_t;




typedef struct
{
	unsigned char bst_interval; //ms	
	unsigned char obu_getsecure_interval;
	unsigned char obu_read_file_interval;
	unsigned char obu_write_file_interval;
	unsigned char obu_timeout[2];
	unsigned char obu_repeat_num;
}time_para_t;

typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	time_para_t time_para;
}set_time_para_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	time_para_t time_para;
}set_time_para_ack_t;


typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char workmode;
	unsigned short wait_time;
}set_workmode_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char workmode;
	unsigned short wait_time;
}set_workmode_ack_t;



typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char workmode;
	unsigned char direction;
}set_rfsmode_t;

typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char workmode;
	unsigned char direction;
}set_rfsmode_ack_t;

#pragma pack(1)
typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	int near_switch;
	int mid_near_switch;
	int mid_far_switch;
	int far_switch;

}set_antmode_switch_t;

#pragma pack(1)
typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	int near_switch;
	int mid_near_switch;
	int mid_far_switch;
	int far_switch;

}set_antmode_switch_ack_t;
#pragma pack(1)
typedef struct
{
	unsigned char cmd_type;
	unsigned char action_type;
	unsigned char vst_len;
}set_vst_len_t;

#pragma pack(1)
typedef struct
{
	unsigned char ack_type;
	unsigned char status;
	unsigned char vst_len;
}set_vst_len_ack_t;


typedef struct
{
	unsigned char cmdtype;
	unsigned char beaconidstatus;
	unsigned char beaconid[4];
}set_beaconid_test_t;


typedef struct 
{
	unsigned char acktype;
	unsigned char errcode;
	unsigned char beaconidstatus;
	unsigned char beaconid[4];
}set_beaconid_test_ack_t;


typedef struct
{
	unsigned char cmd;
	unsigned char Seconds[4]; // seconds since 2000/1/1 00:00:00 
	unsigned char time[7]; // date and time YY-YY-MM-DD-HH-MM-SS
	unsigned char lanmode; // 0x03->entrance mode, 0x04->exit, 0x06->development, 0x08->open mode
	unsigned char wait_time; // Min reRead interval
	unsigned char Main_TxPower; // main_antenna power
	unsigned char PllChannelID; // channel_ID	
    unsigned char AuthFlag;
	unsigned char Ef04Opt;//是否读取EF04开关标记
	unsigned char Ef04Offset[2];
	unsigned char Ef04Len[2];
		
}init_rsu_t;
/*
typedef struct
{
	unsigned char cmd_ack;
	unsigned char RSUStatus;
	unsigned char PSAMNum; // the number of PSAM
	unsigned char Psam1TerminalID[6]; // GB_PSAM
	unsigned char Psam2TerminalID[6]; // reserve PSAM
	unsigned char RSUAlgID; // algorithm ID
	unsigned char RSUManuID[2];  // Manufacturer ID
	unsigned char RSU_ID[2];  // individual ID
	unsigned char RSUVersion[2];  //RSU soft version
	unsigned char Reserved[5]; //first four Bytes-->date of antenna version(YYYY-MM-DD),
	                           // the last Byte-->number of antenna: first 0x01, second 0x02, ...
}init_rsu_ack_t;
*/

typedef struct
{
	unsigned char cmd_ack;
	unsigned char RSUStatus;
	unsigned char Psam1TerminalID[6];
    unsigned char RSUAlgID; // RSU AlgID , 0x00
	unsigned char RSUManuID; // Manu_ID	
	unsigned char RSUID[3]; 
    unsigned char RSUVersion[2]; // RSU version
    unsigned char Psam1Ver;
	unsigned char PSAMAuthStatus;//lzw
   	unsigned char Reserve[5]; // reserve
}init_rsu_ack_t;


typedef struct
{
	unsigned char cmd;
	
}read_psam_t;


typedef struct
{
	unsigned char psam_sn;
	unsigned char psam_exist;
	unsigned char psam_version;
	unsigned char psam_status;
	unsigned char psam_terminnal_id[6];
}psam_info_t;

typedef struct
{
	unsigned char cmd_ack;
	unsigned char psam_count;
	psam_info_t psam_info[12];	
}read_psam_ack_t;

typedef struct
{
	unsigned char cmd;
}read_rsu_version_t;


typedef struct
{
	unsigned char cmd_ack;
	unsigned char version[20];
}read_rsu_version_ack_t;

typedef struct
{
	unsigned char cmd;
}reboot_rsu_t;


typedef struct
{
	unsigned char cmd_ack;
	unsigned char status;
}reboot_rsu_ack_t;

#pragma pack(1)  // align by one byte
typedef struct
{
	unsigned char cmd_ack; // Frame Type
	unsigned char ErrorCode; // Error Code
	unsigned char DateTime[7]; // current time YYYY-MM-DD-HH-MM-SS (BCD) 
	unsigned char PSAMCount; // PSAM count
}init_auth_ack_head_t;

#pragma pack(1)  // align by one byte
typedef struct 
{
	unsigned char cmd_ack; // Frame Type
	unsigned char ErrorCode; // error code
	unsigned char AuthCount; 
}auth_safety_ack_head_t;

#pragma pack(1)  // align by one byte
typedef struct 
{
	unsigned char psam_channel_id;
	unsigned char status;
	unsigned char sw1sw2[2];
}psam_auth_ack_t;

typedef struct
{
	unsigned char channel_ID;
	unsigned char terminal_ID[6];
	unsigned char SerialNo[10];
	unsigned char psamVersion;
	unsigned char psamType;
	unsigned char random[8];
	unsigned char useAreaID[8];	
}init_safety_psaminfor_ack;

typedef struct 
{
	unsigned char psam_channel;
	unsigned char psam_auth_status;
	unsigned char exauth_apdu_mac[13];
}auth_infor_t;


typedef struct
{
	//unsigned char flag;
	unsigned char cmd;	
    unsigned char time[7];
}rsu_status_t;


#pragma pack(1)  // align by one byte
typedef struct
{
	unsigned char PsamState;
	unsigned char RSUGate;
	unsigned char RF_State;
	unsigned char Txpower;
	unsigned char PLLCannnelID;
	unsigned char StationNo[2];
	unsigned char EsamSpare;
	unsigned char IccSpare;
	unsigned char TongBuLogic;
	unsigned char MarkMode;
	unsigned char RES;
}rsu_ant_status_t;

#pragma pack(1)  // align by one byte
typedef struct
{
	unsigned char cmd_ack;
	unsigned char rsuNum;
	unsigned char currentTime[4];
	rsu_ant_status_t ant_status_data[5];
}rsu_status_ack_t;


#pragma pack(1)  // align by one byte
typedef struct
{
	unsigned char psam_channel; // chanel_ID
	unsigned char psam_RunStatus; // PSAM RunStatus  0x00->normal  0x01->abnormal
	unsigned char psam_AuthStatus; // PSAM AuthStatus  0x00->auth_ok, 0x01->
}collect_psam_status_t;

#pragma pack(1)  // align by one byte
typedef struct
{
	unsigned char ant_sn; // antenna ID
	unsigned char ant_run_status; // run_status: 0x00->normal, 0x01->comm_abnormal, 0x02->rf_abnormal, 0x03->other_abnormal
	unsigned char ant_PllChannel; // 0x00->channel_1,   0x01->channel_2
	unsigned char ant_power; // Antenna power  0x00~0x1F	
}collect_antenna_status_t;

#pragma pack(1)  // align by one byte
typedef struct 
{
	unsigned char cmd;
    unsigned char rsustatus;
    unsigned char beaconid[4];
}rsu_collect_status_t;


#endif




