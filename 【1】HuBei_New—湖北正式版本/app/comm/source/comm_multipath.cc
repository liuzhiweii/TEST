#include <zmq.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include "etc_codec_cq.h"
#include "logm.h"
#include "comm_multipath.h"
#include "etc_codec_ff_rsctl.h"
#include "etc_codec_ff_crc.h"
#include "jiffs.h"


#define MULTIPATH_SERVER_PORT   9527
#define BUF_MAX_LEN             (1024)

unsigned char cmd_conn[2]= {0x11, 0x01}; // cmd net connected
unsigned char cmd_disconn[2]= {0x11, 0x00}; // cmd net disconnected


void *comm_ctx = NULL;
void *reportsock_recv = NULL;
void *reportsock_send = NULL;
void *pc_cmd_configsock = NULL;


unsigned char recv_thread_exist_flag = 0;
unsigned char send_thread_exist_flag = 0;

unsigned char report_send_seq;


int get_listen_sock(void)
{
    int ret;
    int level;
    int name;
    int value;
    struct sockaddr_in  addr;
    int lsock;

    lsock = socket(AF_INET, SOCK_STREAM, 0);
    if(lsock < 0)
    {
        logm_debug("creat listen socket fail!\n");
        exit(-1);
    }

    level = SOL_SOCKET;
    name = SO_REUSEADDR; 
    value = 1;
    setsockopt(lsock, level, name, &value, sizeof(int));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(MULTIPATH_SERVER_PORT);

    ret = bind(lsock, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        logm_debug("bind to port 9527 fail!\n");
        exit(-1);
    }

    listen(lsock, 2);

    return lsock;
}

void init_ipc_zmq_socket()
{
    int value = 1;
    
    comm_ctx = zmq_init (1);
    if(NULL == comm_ctx)
    {
        logm_debug("create context fail!\n");
        exit(-1);
    }    

    reportsock_recv = zmq_socket(comm_ctx, ZMQ_PULL);
    if(NULL == reportsock_recv)
    {
        logm_debug("create reportsock_recv sock fail!\n");
        exit(-1);
    }
    //Keep only last message
    zmq_setsockopt(reportsock_recv, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_bind(reportsock_recv, "tcp://*:5081");

    reportsock_send = zmq_socket(comm_ctx, ZMQ_PUSH);
    if(NULL == reportsock_send)
    {
        logm_debug("create reportsock_send sock fail!\n");
        exit(-1);
    }
    //Keep only last message
    zmq_setsockopt(reportsock_send, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_bind(reportsock_send, "tcp://*:5082");
    
    pc_cmd_configsock = zmq_socket(comm_ctx, ZMQ_REQ);
    if(NULL == pc_cmd_configsock)
    {
        logm_debug("create REQ sock fail!\n");
        exit(-1);
    }
    value = 2000;
    zmq_setsockopt(pc_cmd_configsock, ZMQ_RCVTIMEO, &value, sizeof(value));
    zmq_connect(pc_cmd_configsock, "tcp://127.0.0.1:6500");

}

void execute_rsu_report_command(void *sock, unsigned char *command, unsigned int command_len)
{
    int ret;
    
    logm_debug("PC ack Trade %d -> ", command_len);
    logm_debug_buffer(command, command_len);

    ret = zmq_send(sock, command, command_len, ZMQ_DONTWAIT);
    if(ret <= 0)
    {
        logm_err("send  error\n");
        return;
    }
}

void execute_command(void *sock, unsigned char *command, unsigned int command_len, unsigned char *ack, unsigned int *ack_len)
{
    int ret;

    logm_debug("To CTRL %d -> ", command_len);
    logm_debug_buffer(command, command_len);

    ret = zmq_send(sock, command, command_len, 0);
    ret = zmq_recv(sock, ack, BUF_MAX_LEN, 0);
    if(ret <= 0)
    {
        logm_err("execute command error\n");
        *ack_len = 0;
        return;
    }
    
    logm_debug("From CTRL %d <- ", ret);
    logm_debug_buffer(ack, ret);

    *ack_len = ret;

    return;
}


int send_to_client(int sock, unsigned char *buf, unsigned int len)
{
    int sended_len = 0;
    int fragment;

    while(sended_len < len)
    {
        fragment = send(sock, &buf[sended_len], (len - sended_len), MSG_NOSIGNAL);

        if(fragment < 0)
        {
            logm_debug("send to pc socket error!\n");
            return -1;
        }
        sended_len += fragment;
    }

    logm_debug("To PC %d --> ", len);
    logm_debug_buffer(buf, len);

    return 0;
}

int execute_raw_command(void *configsock, void *reportacksock,int servesock, unsigned char *raw_frame, unsigned int frame_len)
{
    unsigned char *decoded_buf = NULL;
    unsigned char *response = NULL;
    unsigned int decoded_len;
    unsigned int response_len;
    unsigned int ack_len;
    int ret;
    unsigned char recv_seq;
    unsigned char ack[BUF_MAX_LEN];
       

    decoded_buf = etc_decode_ff_rsctl_optimise(raw_frame, frame_len, &decoded_len);
    //decoded_buf = etc_decode_ff_crc_optimise(raw_frame, frame_len, &decoded_len);
    /* get PC ack seq */
    recv_seq = raw_frame[3]; 
    if(NULL != decoded_buf)
    {
        // ETC Trade ack frame
        if ((decoded_buf[0] == 0xC1) || (decoded_buf[0] == 0xC2) 
            || (decoded_buf[0] == 0xC3) || (decoded_buf[0] == 0xC6)
            || (decoded_buf[0] == 0xC7) || (decoded_buf[0] == 0xC9))
        {
             /* judge sequence */
             /*
            unsigned char seq_tmp = ((recv_seq & 0xF0) >> 4) | ((recv_seq & 0x0F) << 4);
            if(seq_tmp != report_send_seq)
            {
                logm_debug("recv %02x and send %02x seq not match\n", recv_seq, report_send_seq);
                return -1;
            }
            */
            execute_rsu_report_command(reportacksock, decoded_buf, decoded_len);
            /* clear send sequence */
            report_send_seq = 0x00;
        }
        else
        {
            execute_command(configsock, decoded_buf, decoded_len, ack, &ack_len);
            if(ack_len == 0)
            {
                // cmd excute failed                
                return -1;
            }
            if (ack[0] != 0xFF) // PC CMD Error, and Do not ACK
            {
               // response = etc_encode_ff_crc(ack, ack_len, &response_len);
                response = etc_encode_ff_rsctl(ack, ack_len, &response_len);
                ret = send_to_client(servesock, response, response_len);
                if(ret < 0)
                {
                    return -1;
                }
            }
        }
    }
    else
    {
        logm_debug("PC_CMD decode error\n");
    }
    

    return 0;
}

int process_report_Trade(void *rsuReportSock, void *pcsock)
{
    int recv_len, ret;
    unsigned char *response = NULL;
    unsigned int response_len;
    unsigned char recv_buffer[BUF_MAX_LEN];
        

    //recv_len = zmq_recv(rsuReportSock, recv_buffer, 512, ZMQ_DONTWAIT);
    recv_len = zmq_recv(rsuReportSock, recv_buffer, BUF_MAX_LEN, 0);
    if(recv_len > 0)
    {
        logm_debug("From CTRL_Trade %d <- ", recv_len);
        logm_debug_buffer(recv_buffer, recv_len);        

        //response = etc_encode_ff_crc(recv_buffer, recv_len, &response_len);
        response = etc_encode_ff_rsctl(recv_buffer, recv_len, &response_len);
        /* record RSU send_data sequence */
        report_send_seq = response[2];
        ret = send_to_client((int)pcsock, response, response_len);
        if(ret < 0)
        {
            return -1;
        }        
        return 0;
    }
    else
    {
        return 1;
    }
}

#if 0
void notify_scheduler_Net_connected(void *notifysock)
{    
    unsigned char notify_ack[8];    

    zmq_send(notifysock, cmd_conn, 2, 0);
    zmq_recv(notifysock, notify_ack, 8, 0);
    logm_debug("Notify Scheduler that Network is connected!\n");
}
#endif

void notify_scheduler_Net_disconnect(void *notifysock)
{    
    unsigned char notify_ack[8];

    zmq_send(notifysock, cmd_disconn, 2, 0);
    zmq_recv(notifysock, notify_ack, 8, 0);
    logm_debug("Notify Scheduler that Network is disconnected!\n");
}

void *send_thread_func(void *servesock)
{
    int ret;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , NULL); //

    while(1)
    {
        ret = process_report_Trade(reportsock_recv, servesock);
        if(ret == -1) //send trade frame to PC failed
        {
            break;
        }
    }

    // notify scheduler process that the net is disconnected
    notify_scheduler_Net_disconnect(pc_cmd_configsock);

    close((int)servesock);  
    send_thread_exist_flag = 0;
    logm_debug("send thread_exit\n");
    return (void *)0;
}

void *serve_func(void *servesock)
{
    int recv_len;
    int ret;
    unsigned char recv_buf[BUF_MAX_LEN];
    
    
    while(1)
    {
        recv_len = recv((int)servesock, recv_buf, 1024, MSG_NOSIGNAL);

        if(recv_len <= 0)
        {
            // notify scheduler process that the net is disconnected
            notify_scheduler_Net_disconnect(pc_cmd_configsock);
            logm_debug("pc socket error, so close it !\n");            
            break;
        }
        else if (recv_len > 0)
        {
            logm_debug("From PC %d <-- ", recv_len);
            logm_debug_buffer(recv_buf, recv_len);
            
            execute_raw_command(pc_cmd_configsock, reportsock_send, (int)servesock, recv_buf, recv_len);                
        }
    }

    // notify scheduler process that the net is disconnected
    notify_scheduler_Net_disconnect(pc_cmd_configsock);

    close((int)servesock);  
    recv_thread_exist_flag = 0;
    logm_debug("recv thread_exit\n");
    return (void *)0;
}

int main(int argc, char *argv[])
{
    int listensock;
    int serversock;
    struct sockaddr_in addr;
    socklen_t len = 0;
    int flags, ret;
    pthread_attr_t a_thread_attr;
    pthread_t  a_thread_recv;    
    pthread_t  a_thread_send;
    int serversock_before = 0;
    
    init_jiffs();  // set_1 debug information display  time
    init_logm("comm");
    set_timeflag(); // set_2 debug information display  time

    listensock = get_listen_sock();
    int enable = 1;
    setsockopt(listensock, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));
    init_ipc_zmq_socket();

    pthread_attr_init(&a_thread_attr);   // set a thread attribute detached
    pthread_attr_setdetachstate(&a_thread_attr, PTHREAD_CREATE_DETACHED);

    while(1)
    {
        memset(&addr, 0, sizeof(addr));
        serversock =  accept(listensock, (struct sockaddr *)&addr, &len);
        if(serversock > 0)
        {
            if((recv_thread_exist_flag != 0) && (send_thread_exist_flag != 0))
            {
                pthread_cancel(a_thread_recv);  //close old thread
                pthread_cancel(a_thread_send);  //close old thread
                //usleep(1000);
                close(serversock_before); // close socket port
                recv_thread_exist_flag = 0;
                send_thread_exist_flag = 0;
                logm_debug("Old server Thread Cancled\n");
            }
            else
            {
                if(recv_thread_exist_flag != 0)
                {
                    pthread_cancel(a_thread_recv);  //close old thread
                    recv_thread_exist_flag = 0;
                    logm_debug("Old recv Thread Cancled\n");
                }
                else if(send_thread_exist_flag != 0)
                {
                   pthread_cancel(a_thread_send);  //close old thread
                   send_thread_exist_flag = 0;
                   logm_debug("Old send Thread Cancled\n");
                }                
            }
                        
        #if 0 // if 0, set socket Block
            flags = fcntl(serversock, F_GETFL, 0);  
            fcntl(serversock, F_SETFL, flags | O_NONBLOCK); // set socket fd as NonBlock
        #endif
            
            // when create a thread, and set the thread attribute as detached
            ret = pthread_create(&a_thread_recv, &a_thread_attr, serve_func, (void *)serversock);
            if(ret == 0)
            {
                recv_thread_exist_flag = 1;
            }
            // when create a thread, and set the thread attribute as detached
            ret = pthread_create(&a_thread_send, &a_thread_attr, send_thread_func, (void *)serversock);
            if(ret == 0)
            {
                send_thread_exist_flag = 1;
            }
            serversock_before = serversock;
        }
    }
    zmq_close(reportsock_recv);
    zmq_close(reportsock_send);
    zmq_close(pc_cmd_configsock);
    zmq_ctx_destroy(comm_ctx);
    pthread_attr_destroy(&a_thread_attr);

    return 0;
}






