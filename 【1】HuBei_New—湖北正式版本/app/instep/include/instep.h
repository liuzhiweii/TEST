#ifndef _INSTEP_H
#define _INSTEP_H

#define SYNC_SERVER_PORT              (50005)

#define WORK_MODE_MASTER              (0x01)
#define WORK_MODE_BACKUP              (0X02)


#define SYNC_COMMUNICATE_TYPE_NET                (0)
#define SYNC_COMMUNICATE_TYPE_UART               (1)


#define M_MASTER_IP           "192.168.2.2"




class master_instep
{
public:
    master_instep();
    void zmq_sock_init();
    void getConfig();
    void init();
    void run();
    void work_mode_backup();
    void work_mode_master();
    void backup_client_func_poll();
    static void *master_server_func(void *pare);
    static void *backup_client_func(void *para);
    int connectServer();
    int create_listen_sock();

private:
    int m_socket_timer;
    int m_serverSock;
    int m_clientSock;
    void *m_ctx;
    void *m_sch_socket_send;
    void *m_sch_socket_recv;
    char m_master_ip[24];
    unsigned char m_control_ID;
    unsigned char m_control_sync_comm_type;

    unsigned char recv_thread_exist_flag;

};


#endif
