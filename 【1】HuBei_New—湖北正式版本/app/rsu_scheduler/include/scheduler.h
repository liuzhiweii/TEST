#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "jiffs.h"

using namespace std;

typedef enum
{
	rf_connected = 0,
	rf_disconnected
}RfStatus;

typedef enum
{
	unknown = 0,
	cpc_card,
	obu_tag
}TagType;

typedef enum
{
	obu_undefine = 0,
	obu_single,
	obu_double
}ObuType;

typedef enum
{
	undefine = 0,	
	gb_tdes_psam,
	universal_psam,
}PsamType;


typedef enum
{
	trade_proc_undefine = 0,
	send_fake_location_D0Frame_state, //send fake OBU location to PC 
	send_location_D0Frame_state, // send OBU location information to PC
	send_trade_B2Frame_state,   // send OBU System information frame to PC
	send_trade_B3Frame_state,  // send vehicle information frame to PC
	send_trade_B4Frame_state,  // send CPU_card information frame to PC
	send_trade_B5Frame_state,  // send trade end information frame to PC
	send_trade_B7Frame_state,
	send_trade_B9Frame_state,  // send EF04 infor
	send_trade_error_Frame_state, // Send error frame to PC
	
	
	// after send above CMD, enter this state, wait for PC ACK
	recv_ack_B2Frame_state,
	recv_ack_B3Frame_state,
	recv_ack_B4Frame_state,
	recv_ack_B5Frame_state,
	recv_ack_B7Frame_state,
	recv_ack_B9Frame_state,
	recv_trade_error_Frame_state,
	recv_trade_pc_command_state  // wait for C1, C2, C6, C7, C8  ack
}OBUTradeState;


#define POLL_ITEM_COUNT     (2)
#define SUPPORT_ANTENNA_NUM      (5)

#define MATCH 0
#define NOTMATCH 1
#define FAIL  2
#define CALENUM 10

//OBU status bit map
#define ICC_NOT_EXIST             (1 << 7)  // bit7
#define ICC_ERROR                 (1 << 3)
#define OBU_IS_LOCKED             (1 << 2)
#define OBU_IS_NOT_EFFECTIVE      (1 << 1)
#define OBU_BATTERY_LOW           (1 << 0)



#define SET_CHANNLE_NUM                (100)
#define SEND_B0_INTERVAL               (10000)
#define SEND_OPEN_CLOSE_ADJACENT_ANT   (2000)
#define RECV_CLOSE_ANT                 (5000)

#define WORK_MODE_MASTER              (0x01)
#define WORK_MODE_BACKUP              (0X02)
#define RECEIVE_PC_ACK_TIMEOUT       0xE1
#define PC_CMD_STOP_TRADE            0xE2
#define DG_COIL_NOT_TRIGGER          0xE3
#define COORDINAT_NOT_CHANGED        0xE4

#define ICC_PURCHASE_FAIL        100
#define ICC_GET_BALANCE_FAIL     101
#define AUTH_PURCHASE_MAC2_FAIL  102
#define READ_ICC_FILES_FAIL      103
#define READ_ICC_FILES_TIMEOUT   104
#define READ_FILE15_TIMEOUT      105
#define RECEIVE_PC_ACK_TIMEOUT   106
#define PC_CMD_STOP_TRADE        107
#define GET_LOCATION_FAILED      108
#define DG_COIL_NOT_TRIGGER      109
#define COORDINAT_NOT_CHANGED    110

/* PSAM status */
#define PSAM_AUTH_OK                    (0x00)
#define PSAM_AUTH_NO                    (0x01)
#define PSAM_STATUS_OK                  (0x00)
#define PSAM_STATUS_NOT_OK              (0x01)


/* PSAM auth_CMD excute status_code */
#define PSAM_AUTH_EXEC_OK               (0x00)
#define PSAM_AUTH_CMD_ERROR             (0x01)
#define PSAM_AUTH_EXEC_NOACK            (0x02)
#define PSAM_AUTH_EXEC_FAIL             (0x03)
#define PSAM_AUTH_KEY_LOCKED            (0x04)

/* PSAM auth step_status */
#define PSAM_AUTH_IDLE                  (0x00)
#define PSAM_AUTH_STEP_INIT             (0x01)
#define PSAM_AUTH_STEP_FINISH_OK        (0x02)
#define PSAM_AUTH_STEP_FIN_FAILED       (0x03)


/* RSU main status */
#define RSU_STATUS_OK                   (0x00)
#define RSU_PSAM_REST_FAIL              (0x01)
#define RSU_ANT_LINK_FAIL               (0x02)
#define RSU_CTRL_INIT_FAIL              (0x03)



//RSU send trade frame to PC error_code
#define TRADE_NORMAL                            (0x00)
#define CPU_CARD_INIT_PURCHASE_FAIL             (0x03)
#define PSAM_INIT_PURCHASE_FAIL                 (0x05)
#define PSAM_AUTHEN_MAC2_FAIL                   (0x07)
#define DSRC_NO_COMM_TIMEOUT                    (0x08) // timeout > 3s
#define CPU_CARD_DEBIT_PURCHASE_FAIL            (0x09)
#define ONLY_CPU_CARD_DEBIT_PURCHASE_FAIL       (0xE1)
#define CPU_CARD_READ_FILE0002_FAIL             (0x51)
#define CPU_CARD_READ_FILE0019_FAIL             (0x52)
#define WRITE_EF04_SUCCESS_PURCHASE_FAIL        (0xE2)
#define CPU_CARD_EXIT                           (0x65)

#define OBU_IS_MILITARY_VEHICLE                 (0x0F)
#define DSRC_REPEAT_NUM_ABOVE                   (0x11)
#define VST_NO_SYSTEM_INFOR                     (0x12)
#define TRANSFER_CHANNEL_NOT_MATCH              (0x13)
#define APDULSIT_NOT_MATCH                      (0x14)
#define OBU_GET_TAC_FAIL                        (0x15)
#define OBU_ACK_DATALEN_ERROR                   (0x16)
#define OBU_READ_ICC_FILE02_FAIL                (0x17)
#define OBU_READ_ICC_FILE15_FAIL                (0x22)
#define OBU_CALC_MAC_FAIL2                      (0x05)  //lrz
#define OBU_CALC_MAC2_FAIL2                     (0x07)  //fail times 2
#define OBU_EXAUTHEN_REMAIN1                    (0x25)   // remain 1
#define ICC_ACK_LEN_FAIL                        (0x26)
#define PSAM_DESCRYP_AND_AUTHEN_INITESAM_FAIL   (0x30)
#define PSAM_DESCRYP_VEHICLE_FAIL               (0x31)
#define PSAM_CALC_VEHICLE_MAC_FAIL              (0x32)
#define PSAM_AUTHEN_OBU_MAC_NOT_MATCH           (0x33)
#define PSAM_CALC_DES_FAIL                      (0x36)
#define PSAM_AUTHEN_ANFANG                      (0x39)
#define PSAM_ENCRYP_FILE08_RAND_FAIL            (0x3A)
#define PSAM_ENCRYP_CPC_RAND_FAIL               (0x3E)
#define CPU_CARD_READ_FILE0015_FAIL             (0x50)
#define CPU_CARD_READ_FILE0002_FAIL             (0x51)
#define CPU_CARD_READ_FILE0019_FAIL             (0x05)
#define CPU_CARD_READ_FILE0012_FAIL             (0x53)
#define CPU_CARD_WRITE_FILE0019_FAIL            (0x03)
#define CPU_CARD_GET_RAND_FAIL                  (0x57)
#define CPU_CARD_EXTERN_AUTHEN_FAIL             (0x58)
#define CPU_CARD_WRITE_FILE0012_FAIL            (0x59)
#define CPU_CARD_GET_TAC_FAIL                   (0x5A)
#define CPU_CARD_READ_FILE0008_FAIL             (0x02)
#define CPU_CARD_WRITE_FILE0008_FAIL            (0x5E)
#define CPU_CARD_EXAUTHEN_FILE0008_FAIL         (0x5F)
#define CLEAR_EF04_FAIL                         (0xE4)
#define ONLY_CLEAR_EF04_FAIL                    (0x66) //lzw
#define CLEAR_FILE0008_ERROR                    (0x0D)
#define READ_EF04_FAIL                          (0x05)


#define TRANS_RESULT_SUCCESS          (0x00)
#define EF04_SUCCESS_FILE08_FAIL      (0x01)
#define EF04_FAIL_FILE08_SUCCESS      (0x02)
#define EF04_FAIL_FILE08_FAIL         (0x03)
#define CPC_EF02_FAIL                 (0x04)
#define EF04_SUCCESS_NO_IC            (0x65)
#define EF04_FAIL_NO_ICC              (0x66)
#define CHARGE_FAIL                   (0x02)
#define EF04_RW_SUCCESS               (0x00)
#define EF04_RW_FAIL                  (0x01)
#define EF04_RD_SUCCESS_WD_FAIL       (0x03)
#define EF04_RD_FAIL_WD_SUCCESS       (0x02)




#define TAG_CACHE_TIME_ROAD            6*60*1000
#define TAG_CACHE_TIME_LAB             45*1000
#define TAG_CACHE_TIME_AUTH_FAIL       30*60*1000

#define SEND_TICK_PACKET_INTERVAL      (10*1000) // 10s  system_tick = 1000Hz

#define BCD2HEX(bcd) ((bcd/16)*10 + bcd%16)
#define HEX2BCD(hex) ((hex/10)*16 + hex%10)
#define RSU_TRADE_IDLE                   (0x00)
#define RSU_TRADE_BUSY                   (0x01)


#define BEACONID_CHANGE_CYCLE              1000
#define ROUTE_CHANGE_CYCLE                 1000
#define TRADE_FAIL_BEACONID_CHANGE_CYCLE   3000

#define WAIT_PC_FRAME_ACK_TIMEOUT          1000 //240 // receive trade ACK timeout
#define WAIT_B9_FRAME_ACK_TIMEOUT          300 //240 // receive B7 ACK timeout
#define REPEAT_SEND_FRAME_PC_MAX_NUM       3 // timeout count 3

#define PSAM_OPERATE_TIMEOUT_INTERVAL          (200) // PSAM operate timeout
#define GET_LOCATION_TIMEOUT_INTERVAL          (10)  

#define LANE_MODE_ENTRANCE                 0x03
#define LANE_MODE_EXIT                     0x04
#define LANE_MODE_OPEN                     0x06
#define LANE_MODE_JOINT_CONSTRUCT          0x08

#define TDES                               0x00
#define SM4                                0x04

#define ETC_GRAT                           0x00
#define ETC_COIL                           0x01
#define MTC                                0x02

#define NEAR_END				(2)
#define MID_END					(3)
#define FAR_END					(1)
/* ant direction */
#define LEFT                    (0)
#define RIGHT                   (1)
/* select trade flow 1 is priority send B2 */
#define TRADE_FLOW_SEL          (1)
#define OLDANT                  (1)
#define NEWANT                  (2)
/* trade zmq select */
#define TRADE_ZMQ_SEL_NET          (0x01)
#define TRADE_ZMQ_SEL_UART         (0x02)

/* OBU ESAM Algorithm Type */
#define OBU_VEHICLE_KEY_3DES                 (0x00)
#define OBU_VEHICLE_KEY_SM4                  (0x40)

/* PSAM descrypt vehicle key version */
#define PSAM_DESCRYPT_VEHICLE_3DES           (0x03)
#define PSAM_DESCRYPT_VEHICLE_SM4            (0x43)
typedef enum
{
	vst_state = 0,
	
	send_descryption_state,
	recv_descryption_state,
	send_getsecure_state,
	recv_getsecure_state,
	send_read_icc_files_state,
	recv_read_icc_files_state,
	send_read_file19_and_balance_state,
	recv_read_file19_and_balance_state,
	send_read_ef04_state,
	recv_read_ef04_state,
	send_write_ef04_state,
	recv_write_ef04_state,
	send_read_ef04_exit_state,
	recv_read_ef04_exit_state,
	send_write_ef04_exit_state,
	recv_write_ef04_exit_state,
	send_write_ef04_exit1_state,
	recv_write_ef04_exit1_state,
	send_write_ef04_exit2_state,
	recv_write_ef04_exit2_state,

    send_write_ef04_exit_in_state, //lzw
	recv_write_ef04_exit_in_state, //lzw
	
	send_read_icc_file19_state,
	recv_read_icc_file19_state,
	
	send_clear_ef04_state,
	recv_clear_ef04_state,

	//process double_obu purchase 
	send_init_for_purchase_state,
	recv_init_for_purchase_state,
	send_only_init_for_purchase_state,
	recv_only_init_for_purchase_state,
	send_get_Tac_And_Balance_state,
	recv_get_Tac_And_Balance_state,
	send_calc_purchase_mac1_state,
	recv_calc_purchase_mac1_state,
	send_purchase_state,
	recv_purchase_state,
	send_auth_purchase_mac2_state,
	recv_auth_purchase_mac2_state,

	//process single_obu
	send_calc_access_cred_state,
	recv_calc_access_cred_state,
	send_get_toll_data_state,
	recv_get_toll_data_state,
	get_random_rsu_state,
	send_set_toll_data_state,
	recv_set_toll_data_state,
	send_auth_authenticator,
	recv_auth_authenticator,
	

	send_setmmi_state,
	recv_setmmi_state,	
	
	report_and_query_ack_trade_state	    
}TagState;



typedef struct
{
	int rfsn;
	int rssi;
	int length;
	unsigned char buffer[256];
}recv_buffer_t;

#pragma pack(1)
typedef struct
{
	unsigned int macID;
	float X_Coordinate;
	float Y_Coordinate;
}recv_location_t;

typedef struct
{
	unsigned int macid;
	unsigned long jffies;
}tag_jiffies_t;




typedef struct
{
	unsigned int mac_id;
	int location_X;
	int location_Y1;
	int location_Y2;
	int location_Y3;
	int rssi;
	int rssi_num;
	int num;
	unsigned long lasttime;
}obu_coordinate_t;



class PsamProxy;
class Scheduler;
class TradeControl;
class SchedulerConfig;
class TagCache;

class TradeControl
{
public:
	TradeControl(Scheduler *scheduler,  void *reporterSocket_send, void *reporterSocket_recv);
	setTradeControlNum(unsigned char num);
	void process(void);
	
	void enableSendBst(void);
	void forbidRfSendBst(int rfsn);
	void matchVst(void);
	
	void sendGetSecure(void);
	void recvGetSecure(void);	
	void sendDescryption(void);	
	void recvDescryption(void);
	
	void sendSetmmi(void);
	void recvSetmmi(void);	
	void TradeSuccess(void);
	void judgeOBUType();
	bool decodeVst(recv_buffer_t *recv_buffer);	
	int decodeTransferChannelAck(recv_buffer_t *recv_buffer, unsigned char *papdu);
	void goTradeEnd(unsigned char recode);
	void goIgnore(void);
	void encodeTransferChannel(unsigned char channelId, unsigned char *papdulist, unsigned int apdulist_len);
	void encodeSetMmi();
	void sendActionCmd();
	int decodeFastReq(recv_buffer_t *recv_buffer);
	int decodeGetSecure(recv_buffer_t *buffer);
	void encodeGetSecure();
	void sendEventReport(void);
	void _resendAction(int interval, unsigned int errorcode);
	int _resendAction_setErrorCode(int interval, unsigned char errorcode);
	bool isBjObu(void);		
	bool isMilitaryObu(void);
	bool isBjIccCard(void);	
	
	void sendCalcAccessCred(void);
	void recvCalcAccessCred(void);
	void encodeInitPurchase();
	int decodeInitPurchase(recv_buffer_t *recv_buffer);
	void encodeOnlyInitPurchase();
	int decodeOnlyInitPurchase(recv_buffer_t *recv_buffer);
	void encodeGetTACandBalance();
	int decodeGetTACandBalance(recv_buffer_t *recv_buffer);
	void encodePurchase();
	int decodePurchase(recv_buffer_t *recv_buffer);
	void encodeGetBalance();
	int decodeGetBalance(recv_buffer_t *recv_buffer);
	void encodeReadIccFiles();
	int decodeReadIccFiles(recv_buffer_t *recv_buffer);
	void encodeReadFile19andBalance();
	int decodeReadFile19andBalance(recv_buffer_t *recv_buffer);
	
	void encodeClearEf04();
	int decodeClearEf04(recv_buffer_t * recv_buffer);
	void encodeReadEf04();
	int decodeReadEf04(recv_buffer_t *recv_buffer);
	void encodeReadEf04Exit();
	int decodeReadEf04Exit(recv_buffer_t *recv_buffer);
	void encodeWriteEf04();
	int decodeWriteEf04(recv_buffer_t *recv_buffer);
	void encodeWriteEf04Exit();
	int decodeWriteEf04Exit(recv_buffer_t *recv_buffer);
    void encodeWriteEf04inExit();
	int decodeWriteEf04inExit(recv_buffer_t *recv_buffer);
	void encodeWriteEf04Exit1();
	int decodeWriteEf04Exit1(recv_buffer_t *recv_buffer);
	void encodeWriteEf04Exit2();
	int decodeWriteEf04Exit2(recv_buffer_t *recv_buffer);
	void encodeReadIccFile19();
	int decodeReadIccFile19(recv_buffer_t *recv_buffer);
	void sendInitPurchase();
	void recvInitPurchase();
	void sendOnlyInitPurchase();
	void recvOnlyInitPurchase();
	void sendGetTACandBalance();
	void recvGetTACandBalance();
	void sendCalcPurchaseMac1();
	void recvCalcPurchaseMac1();
	void sendPurchase();
	void recvPurchase();
	void sendReadIccFiles(void);
	void recvReadIccFiles(void);
	void sendReadFile19andBalance(void);
	void recvReadFile19andBalance(void);
	
	void sendClearEf04(void);
	void recvClearEf04(void);
	void sendReadEf04(void);
	void recvReadEf04(void);
	void sendReadEf04Exit(void);
	void recvReadEf04Exit(void);
	void sendWriteEf04(void);
	void recvWriteEf04(void);
	void sendWriteEf04Exit(void);
	void recvWriteEf04Exit(void);
	void sendWriteEf04inExit(void);//lzw
	void recvWriteEf04inExit(void);//lzw
	void sendWriteEf04Exit1(void);
	void recvWriteEf04Exit1(void);
	void sendWriteEf04Exit2(void);
	void recvWriteEf04Exit2(void);
	void sendReadIccFile19(void);
	void recvReadIccFile19(void);
	void sendGetBalance();
	void recvGetBalance();
	void sendAuthPurchaseMac2(void);
	void recvAuthPurchaseMac2(void);

	//process report to PC
	void sendFakeD0FrameToPC();
	void sendD0FrameToPC();
	void sendB2FrameToPC();
	void recvB2AckFromPC();
	void sendB3FrameToPC();
	void recvB3AckFromPC();
	void sendB4FrameToPC();
	void recvB4AckFromPC();
	void sendB5FrameToPC();
	void recvB5AckFromPC();
	void sendB9FrameToPC();
	void recvB9AckFromPC();
	void sendErrorFrameToPC();
	void recvErrorAckFromPC();
	void reportAndGetAckFromPC();

	void reconnect_reportServer();
	int check_timeout_and_repeatNum(unsigned char timeout_error, unsigned char repeatError, unsigned char checkFlag);
	int PSAM_check_timeout(unsigned char timeout_error, unsigned long timeout_interval);
	void cal_average_coordinate(unsigned int mac_id, int *m_LocationX, int *m_LocationY, int *m_Rssi, int *m_Rssi_num);
	void cal_average_coordinate_mtc(unsigned int mac_id, int *m_LocationX, int *m_LocationY, int *m_Rssi, int *m_Rssi_num);
	void send_bst_interval_to_anotherpc();
	void setAntWorkMode(int y_coordinate);
	
	void *m_reporterSocket_send;
	void *m_reporterSocket_recv;
	
	TagState m_state;
	unsigned char m_ant_stute;
	unsigned char m_time_interval;
	unsigned char m_research_obu;
	unsigned int m_macId;
	unsigned char m_equipmentCV;
	unsigned char m_obuStatus[2];
	unsigned int m_OBUStatusBitmap;	
	unsigned char m_random[8];
	unsigned char m_encryption[16];
	unsigned char m_vByte;
	unsigned long m_startTime;
	unsigned long m_lastSend;
	unsigned long m_psam_StartTime;	

	unsigned int m_WriteFileTime;

	
	int m_tradeTime;
	unsigned char m_Keytype;
	unsigned char m_tradeResult;
	unsigned char m_sysInfo[26];
	unsigned char m_file15[50];
	unsigned char m_file19[63];
	unsigned char m_OpMode;
	unsigned char OperateEF04Flag;
	unsigned char UpdateEF04Flag;
	unsigned char m_Ef04Off[2];
	unsigned char m_Ef04Len[2];
	unsigned int  m_ef04len;
	unsigned int  m_ef04len_c9;//lzw
	unsigned int  m_ef04len_c7;
	unsigned int  m_ef04len_write_c9;//lzw
	unsigned int  m_ef04len_write_c7;
	unsigned char m_Ef04Info[332];
	unsigned char m_EF04Info_C9_RD[332];
	unsigned char m_EF04Info_C9_WD[332];
	unsigned char m_EF04ReadOffSet[2];
	unsigned char m_EF04ReadLen[2];
	unsigned char m_EF04WriteOffSet[2];//lzw
	unsigned char m_EF04WriteLen[2];
	unsigned char m_EF04RdStatus;
	unsigned char m_EF04WdStatus;
	unsigned char m_IccVersion;
	unsigned char m_needReadFile15Tail;
	unsigned char m_RouteFlag[24];
	unsigned char m_icc_balance[4];
	unsigned char m_after_purchase_balance[4];	
	unsigned char m_vehicle[128];
	unsigned char m_descryptedVehicle[80];
	unsigned char m_ef04[9];
	unsigned char m_ef04_sign[332];
	unsigned char m_ef04_province[174];
	unsigned char m_file08_sign[124];
	unsigned char m_file08[3];
	unsigned char m_ef04_signnum;
	unsigned char m_ef04_provincenum;
	unsigned char m_file08_signnum;
	unsigned char m_esamVersion;
	bool m_supportPinJie;
	bool m_needRereadFile15;
	bool m_forbidBst;
	int m_rfsn;
	int m_rssi;
	int m_seleRfsn;
	int m_getLocation_Rfsn;
	int m_LocationX;
	int m_LocationY;
	int m_RSSI;
	int m_rssi_num;
	unsigned char m_accessCred[8];
	unsigned int m_repeatNum;
	unsigned int m_TradeControlNum;
	unsigned char m_terminal_id[6];
	unsigned char m_psam_transSerial[4];
	unsigned char m_purchaseDateTime[7];
	unsigned char m_transaction_fees[4];
	unsigned char m_CardDivFactor[8];	
	unsigned char m_WriteRecordNum;
	unsigned char m_remainMoney[4];
	unsigned char m_icc_tradesn[2];
	unsigned char m_creditLine[3];
	unsigned char m_purchaseKeyVersion;
	unsigned char m_purchaseKeyAlgorithID;
	unsigned char m_purchaseRandom[4];
	unsigned char m_tradePurchaseTac[4];
	unsigned char m_tradePurchaseMac2[4];
	unsigned char m_randomRsuForAuth[8];
	
	unsigned char m_search;
	unsigned char m_coord_average_over;
	unsigned char m_recv_error_instruct;
	unsigned char m_send_b9_after;//lzw
	unsigned char m_send_b7_after;
	unsigned char m_obu_support_RK;
	unsigned char m_psam_descrypt_KeyVersion;
	unsigned char m_control_D0;
private:	
	ObuType m_obuType;	
	unsigned char m_Trade_State_Code;
	OBUTradeState m_reporttradeState;
	unsigned long m_lastSendFrameTime;
	unsigned char m_sendTradeFrameCount;
	Scheduler *m_scheduler;	
	PsamProxy *m_psam;
	unsigned char m_lastAction[256];
	int m_lastActionLen;
	
};



class RfProxy
{
public:
	RfProxy(void *ctx, int rfsn, int power, int channel, const char *addr);
	void Init_RF_ZMQ_Sock();
	void preClose_ReConnect_Antenna();
	void initPower();
	void initChannel();
	void *sendSock;
	void *recvSock;
	void *cfgSock;
	void *SpSock;
	int sn;
	RfStatus status;
	char m_addr[24];
	int m_power;
	int m_channel;
	bool m_rfForbidBst;
private:
	void *m_ctx;
};

class PsamProxy
{
public:
	PsamProxy(void *ctx, int slot, int type);
	int exchangeApdu(unsigned char cmdLen, unsigned char *cmd, unsigned char *cmdAckLen, unsigned char *cmdAck);
	int exchangeApduAndActive(unsigned char cmdLen, unsigned char *cmd, unsigned char *cmdAckLen, unsigned char *cmdAck);	
	int calcObuMac(unsigned char *iccsn, unsigned char *random, unsigned char *encpyption);
	int descryptVehicle(unsigned char *yinzi, unsigned char *vehicle, unsigned char *descryption);
	void sendCmd(unsigned char cmdLen, unsigned char *cmd);
	int recvAck(unsigned char *cmdAckLen, unsigned char *cmdAck);	
	void sendDescryptVehicle(unsigned char *yinzi, unsigned char rk_index, unsigned char *vehicle);		
	void sendDescryptVehicle(unsigned char *yinzi, unsigned char *vehicle);		
	int recvDescryptVehicle(unsigned char *descryption);
	
	void sendCalcObuMac(unsigned char *iccsn, unsigned char *random);	
	int recvCalcObuMac(unsigned char *encpyption);
	int readTerminalID();
	void sendCalcAccessCred(unsigned char *yinzi, unsigned char *rand);
	int recvCalcAccessCred(unsigned char *accesscred);
	void sendGetPurchaseMac1(unsigned char *Data_CalcMac1, unsigned char *DeliveryFactor_CalcMac1);
	int recvGetPurchaseMac1(unsigned char *encpyption);
	void sendCreditPurchaseMac2(unsigned char *mac2);
	int recvCreditPurchaseMac2(void);
	int get_MF_random(unsigned char *get_random_ack);
	int cold_Reset(void);
	int execute_external_auth(unsigned char *auth_mac,unsigned char *auth_ack);
	
	int m_slot;
	int m_type;
	char m_addr[24];
	bool m_status;

	unsigned char m_terminalID[6];
	unsigned char m_psamSerial[10];
	unsigned char m_psamVersion;
	unsigned char m_psamType;
	unsigned char m_psamIssueID[8];
	unsigned char m_psamUseAreaID[8];
	unsigned char m_iccPurchaseKeyId;
	unsigned char m_obuCipherKeyVer;
	unsigned char m_transSerial[4];
	
private:
	void *m_ctx;
	void *m_reqSock;	
};

typedef struct 
{
	unsigned int rfsn;
	bool isEnable;
	unsigned int power;
	unsigned int channel;
	char  ipaddr[24];
}RfPara;


typedef struct
{
	unsigned int psamid;
	bool isEnable;
	int type;
	unsigned char status;
	unsigned char version;
	unsigned char psam_type;
	unsigned char terminal_id[6];
	unsigned char psam_serial[10];
	unsigned char issueID[8];
	unsigned char useAreaID[8];
	unsigned char AuthStatus;
}PsamPara;

class SchedulerConfig
{
public:
	SchedulerConfig();
	void loadConfig();
	void loadDefaultConfig();
	void saveConfig();
	void fromJson(Json::Value & jsonConfg);
	void toJson(Json::Value &jsonConfig);	
	void clearPsamConfig();	
	void clearRfConfig();
	
	std::vector<PsamPara *> m_psamConfig;
	std::list<RfPara *> m_rfConfig;
	unsigned int m_sleepTime;
	unsigned int m_parallelTrade;
	unsigned char m_beaconId[5];
	unsigned int m_obutimeout;
	unsigned int m_obuGetsecureInterval;
	unsigned int m_obuReadFileInterval;
	unsigned int m_obuWriteFileInterval;
	unsigned int m_obuRepeatNum;	
	bool m_ifBeaconidChange;
	unsigned char m_beaconidCycle;
	bool m_ifRouteInfoChange;
	unsigned char m_routeInfoCycle;
	unsigned char m_bstInterval;
	bool m_enableRuning;
	bool m_testmode;
	unsigned char m_etc_mtc;
	unsigned char m_lanmode;
	unsigned char m_areaid;
	unsigned char m_tradeScheme;
	unsigned short m_waitTime;
	unsigned char m_heartBeat;
	int m_location_X1;
	int m_location_X2;
	int m_location_Y_max;
	int m_location_Y_min;
	bool m_location_limit;
	int m_location_sub_X1;
	int m_location_sub_X2;
	int m_location_sub_Y;
	bool m_coil_trigger_antenna;
	bool m_coil_trigger_enable;
	int m_coil_trigger_confine;
	char m_master_ip[24];
    unsigned char m_control_ID;
	unsigned char m_rfsmode;
	int m_near_switch;
	int m_mid_near_switch;
	int m_mid_far_switch;
	int m_far_switch;
	unsigned char m_direction;
	unsigned char m_vst_len;
private:
	void clearConfig();
};

class Scheduler 
{
public:
	Scheduler();
	void init();
	void init_zmqSock();
	void run();		
	void initBst();	
	void encodeBst();
	void setAntChannel();
	void monitor_RF_connected();
	void sendBst();
	void control_bst_time();
	void rsu_status_report();
	void initSysTime();	
	PsamProxy *getPsam(int type);
	void putPsam(PsamProxy *);
	void sendDsrcFrame(unsigned char *txFrame, int txLength);		
	void sendDsrcFrameByRf(unsigned char *txFrame, int txLength, int rfsn);
	bool getSendBstRf(void);
	void sendClearRfFilo(void);
	bool sendBstFrame(void);	
	void recvDsrcFrame(void);
    void addRecvFrame(unsigned char *frame, unsigned int frameLen, int rfsn);
	void processTrade(void);
	void emptyRecvBuffer(void);	
	void processManage(void);
	void TradeZmqSelect(unsigned char select_flag);	
	void executeManageCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void openAnt(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void QueryAntStatus(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void coilTrigger(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void pcctrlrfid(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);//lzw
	void setBeaconId(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);	
	void setCoordinateLimit(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setAntModeSwitch(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setVstLen(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setCoilTrigger(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setBeaconIdTest(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);	
	void setRouteInfo(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setTradeMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setAntConfig(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);	
	void setPsamConfig(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);	
	void setServerIp(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setControlId(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setLaneMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setDefaultConfig(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setControlMasterIp(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);	
	void setTradeTimePara(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);	
	void rfTestCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setWorkMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setRfsMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void initRsu(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void AfterInit_OpenAnt(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void setTestMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void readTestMode(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void readPsamParameter(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void readRsuVersion(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void rebootRsu(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);    
    void rsuStatus(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void initSafetyMedia(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void AuthSafetyMedia(unsigned char *command, int command_len, unsigned char *ack, int *ack_len); 
	void forbidRfSendBst(int rfsn, bool flag);
	void setSendTickToPC(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	unsigned char  judge_trade_Busy_or_Idle();
	void send_tick();	
	void send_init_b0();
	void open_or_close_adjacent_ant();
	void initB0(unsigned char *send, int *send_len);

    static void *recv_bst_time_status(void *para);
	static void *recv_rsu_status_collect(void *para);
	void ExecuteBstIntervalCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void ExecuteRsuStatusCommand(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void set_bst_interval(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void collect_rsu_status(unsigned char *command, int command_len, unsigned char *ack, int *ack_len);
	void send_bst_interval_status(unsigned char ant_stute, unsigned char time_interval);
	void send_obu_coordinate_rssi_num_message(unsigned int macid, int location_x, int location_y, int rssi, int rssi_num);
	void send_obu_coordinate_message(unsigned int macid, int location_x, int location_y);
	void send_instep_obuId_to_adjacent(unsigned char status,unsigned int macid);
	int collect_psam_status(unsigned char *statusBuffer, unsigned char *psam_run_status);
	unsigned char collect_Antenna_Status(unsigned char *Ant_StatusBuffer);
	void setAntModeBybst(void);
	int judgeWhetherTranscation(unsigned int macid, int location_x, int location_y, int rssi, int rssi_num);

	std::list<obu_coordinate_t *> m_obuCoordinate;
	struct timeval m_startRunTime;
	std::vector<recv_buffer_t *> m_recvBuffers;
	std::list<recv_buffer_t *> m_recvVsts;
	std::list <PsamProxy *> m_universalPsams;	
	SchedulerConfig *m_config;
	TagCache *m_tagCache;
	
	void *m_reporterSocket;
	unsigned int m_reportTime;
	unsigned int m_bst_interval;
	unsigned char m_yymmss[7];	
	unsigned int m_lastBeaconId;
	unsigned long m_lastBeaconIdTime;
	std::list<int> m_rfsList;
	unsigned char m_bstRepeatNum;
	unsigned int m_change_beaconid;
	unsigned long m_lastChangeIdTime;
	unsigned char m_rand_beaconid;
	void *m_reporterSocket_send_net;
	void *m_reporterSocket_recv_net;
	void *m_reporterSocket_send_uart;
	void *m_reporterSocket_recv_uart;
	void *m_sync_socket_send;
	void *m_sync_socket_recv;
	void *m_rsustatusSocket_send;
	void *m_rsustatusSocket_recv;
	unsigned char m_trade_zmq_select;
	unsigned char m_WorkMode;
	unsigned char m_BstInterval;
	unsigned char m_TxPower;
	unsigned char m_PllChannelId;
	unsigned char m_WaitTime;
	unsigned char m_InitEf04Opt;
	unsigned char m_InitEf04Offset[2];
	unsigned char m_InitEf04Len[2];
	unsigned int  m_initef04len;
	unsigned char m_WorkType;
	unsigned char m_IsAuth;//lzw
	unsigned char PsamAutState;
	unsigned char m_WorkType_0;
	unsigned char m_WorkType_1;
	unsigned char m_WorkType_7;
	unsigned char m_Len_ef04;
	unsigned char m_Len_0008;
	unsigned char m_Len_0009;
	std::map<int, RfProxy*> m_rfsMap;
	unsigned char m_coil_trigger_flag; // 0x00->not trigger   0x01->trigger
	unsigned int m_send_bst_num;
	unsigned int m_send_bst_num2;
	unsigned int m_send_bst_num3;
	unsigned char m_car_status;
	unsigned char m_setantchannel;
	unsigned char m_PC_Init_Ant_Txpower;
	unsigned char m_PC_Init_PLLChannelID;
	unsigned char m_adjacent_ant_status;
	unsigned char m_close_ant_from_master;

	unsigned char m_ant_work_mode;
	int m_num_ctrlbstmode;
	int m_near_num;
	int m_mid_to_near_num;
	int m_mid_to_far_num;
	int m_far_num;

	unsigned int m_instep_macid;
	unsigned int m_instep_lettrade_macid;
	unsigned char m_instep_fake_status;
	unsigned char m_instep_lettrade_status;
	int m_instep_locationX;
	int m_instep_locationY;
	int m_instep_rssi;
	int m_instep_num;

private:	
	void initRfProxy();	
	void ReConnect_Antenna();
	void initPsamProxy();
	void push_psam_vector(PsamProxy *psamProxy);
	void initTradeControl();
	bool _macIdExist(unsigned int macId);
	bool _macIdClear(unsigned int macId);	
	void *m_ctx;	
	std::vector <RfProxy *> m_rfs;
	std::vector <RfProxy *>::iterator m_rfsIter;	
	
	std::list <PsamProxy *> m_sm4Psams;	
	std::list <PsamProxy *> m_gbtdesPsams;	
	std::list <PsamProxy *> m_bjtdesPsams;	
	std::list <PsamProxy *> m_singleObuPsams;
	std::vector<TradeControl *> m_tradeControls;	
	void *m_manageSocket;	
	void *m_manageSocket_uart;
	zmq_pollitem_t m_items[POLL_ITEM_COUNT];
	unsigned char m_encodedBst[64];
	unsigned char m_bstLen;
	unsigned long m_lastBst;
	unsigned char m_send_tick_flag;
	unsigned char m_send_init_b0_flag;
	unsigned char m_send_tick_adjacent_flag;
	unsigned int m_send_tick_interval;
	unsigned int m_send_init_b0_interval;
	PsamProxy *m_psamproxy[12];
};

class TagCache
{
public:
	TagCache();
	void cacheTag(unsigned int macid);
	bool findTag(unsigned int macid);	
	int findTagCount(unsigned int macid);
	void setCacheTime(unsigned int time);
private:
	unsigned long m_first;
	unsigned long m_last;
	unsigned int m_cacheTime;
	std::list <tag_jiffies_t *> m_taglist;
};

#define timeOk(before, cycle) (((long)(get_jiffies()) - (long)before) >= cycle)

#define diffTimeVal(now, before) ((long)(now) - (long)before)


inline void hex2string(const unsigned char *hex, int hex_len, char *ascii_string)
{
	unsigned char upper;
	unsigned char lower;
	
	for(int i=0; i<hex_len; ++i)
	{
		upper = hex[i]>>4;
		lower = hex[i]&0x0f;
		ascii_string[2*i] = (upper>9) ? (upper+87) : (upper+48);
		ascii_string[2*i+1] = (lower>9) ? (lower+87) : (lower+48);
	}

	return;
}

inline void string2hex(const char *ascii_string, int ascii_len, unsigned char *hex)
{
	unsigned char upper;
	unsigned char lower;
	int i;


	int len = ascii_len>>1;
	
	for(i=0; i<len; ++i)
	{
		upper = ascii_string[2*i];
		lower = ascii_string[2*i+1];
		hex[i] = (((upper>96) ? (upper-87) : (upper > 64) ? (upper - 55) : (upper-48))<<4)|
				  ((lower>96) ? (lower-87) : (lower > 64) ? (lower - 55) : (lower-48));
	}

	if(0!=ascii_len%2)
	{
	    upper = ascii_string[2*i];
		hex[i]=(((upper>96) ? (upper-87) : (upper-48)))<<4;
	}

	return;	
}


#endif




