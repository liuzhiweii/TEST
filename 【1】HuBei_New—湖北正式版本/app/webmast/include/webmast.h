#ifndef _INSTEP_H
#define _INSTEP_H

#define WEBMAST_SERVER_PORT              (50006)

/********************* device proxy ************************/
#define DEVICE_TYPE_SENSOR                  (6)
#define DEVICE_ACTION_INIT                  (1)
#define ACTION_READ_LOCAL_TEMP              (6)
/*****************************************************************/

#pragma pack(1)
typedef struct 
{
	unsigned char rf_antenna_ID;
	unsigned int rf_status;
	char rf_Temperature[2];
	void *proxy_req_sock;
}antenna_Infor_t;

typedef struct
{
	unsigned int psam_id; 
	bool psam_isEnable; 
	int config_type;	
}Psam_Para;

typedef struct 
{
	unsigned int rfsn;
	bool rf_isEnable;
	char rf_ipaddr[24];	
}Rf_Para;

class webmast_config
{
public:
    webmast_config();
    void LoadBaseInforConfig();

    std::vector<Psam_Para *> m_psamConfig;
	std::vector<Rf_Para *> m_rfConfig;
};

class web_mast
{
public:
    web_mast();
    void zmq_sock_init();
    void init();
    void run();
    void work_mode_master();
    void get_Temperature_Infor();
    void read_Ant_Temperature();
    static void *web_mast_func(void *pare);
    int create_listen_sock();
    char m_controlTemperature[2];
    unsigned char m_antennaNum;
	unsigned char m_PSAMNum;
    webmast_config *m_config;
    antenna_Infor_t m_antInfor[12];

private:
    int m_socket_timer;
    int m_serverSock;
    void *m_ctx;
    void *m_sch_socket_send;
    void *m_sch_socket_recv;
    char m_master_ip[24];
    unsigned char m_control_ID;
    unsigned char m_control_sync_comm_type;

    unsigned char recv_thread_exist_flag;

};


#endif
