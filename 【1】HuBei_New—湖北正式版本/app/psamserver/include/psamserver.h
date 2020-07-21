#ifndef __PSAM_SERVER__
#define __PSAM_SERVER__


#define COLD_RESET               0xf8
#define EXCHANGE_APDU            0xf9  
#define EXCHANGE_APDU_ACTIVE     0xfa
#define CALC_CPC_MAC             0xfb
#define CALC_OBU_MAC             0xfc
#define DESCRYPT_VEHICLE         0xfd
#define READ_TERMINAL_ID         0xfe
#define CALC_ACCSESS_CRED        0xf7
#define GET_RANDOM               0xf6
#define CALC_PURCHASE_MAC1       0xf5
#define AUTH_PURCHASE_MAC2       0xf4
//#define DELIVERY_KEY_VEHICLE     0xf3
//#define DESCRYPT_VEHICLE_INFOR   0xf2
#define GET_MF_RANDOM_8          0xf3
#define PSAM_EX_AUTH             0xf2




typedef struct 
{
    unsigned char   slot;
    unsigned char   pad;
    unsigned char   cmd_len;
    unsigned char   ack_len;        
    unsigned int    error_code;
    unsigned char   cmd[256];
    unsigned char   ack[256];
}psam_exapdu_t;	




class PsamDevice
{
public:
	PsamDevice();
	~PsamDevice();
	int connect(unsigned char slot);
	int active(unsigned char *atrLen, unsigned char *atr);
	int exchangeApdu(unsigned char cmdLen, unsigned char *cmd, unsigned char *cmdAckLen, unsigned char *cmdAck);
	int disablePPS(void);

private:
	unsigned char m_slot;
	int m_fd;
};


class PsamServer
{
public:
	PsamServer(int slot);
	~PsamServer();
	void startRun();
	void coldReset(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void exchangeApdu(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void exchangeApduActive(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void calcCpcMac(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void calcObuMac(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void descryptVehicle(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
    void calcAccessCred(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void readTerminalID(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
    void getRand(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void calcPurchaseMac1(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	void authPurchaseMac2(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	//void descryptVehicle_Key_delivery(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
	//void descryptVehicle_infor(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
    void psam_external_auth(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
    void get_MF_random8(unsigned char *command, unsigned char command_len, unsigned char *ack, unsigned char *ack_len);
private:	
	void _preWork(void);
	char _preWorkRest(void);
	int m_slot;
	void *m_ctx;
	void *m_repSocket;
	PsamDevice *m_device;
	
};

#endif


