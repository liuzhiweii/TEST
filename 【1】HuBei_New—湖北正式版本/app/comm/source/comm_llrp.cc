
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
#include "comm_llrp.h"
#include "logm.h"


#define SERVER_PORT   5555

void *push_socket = NULL;
void *pull_socket = NULL;
int listen_socket;
int connect_socket = -1;



void create_listen_socket(void)
{
    int ret;
    int level;
    int name;
    int value;
    struct sockaddr_in  addr;

    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_socket < 0)
    {
        logm_debug("creat stream socket fail!\n");
        exit(-1);
    }

    level = SOL_SOCKET;
    name = SO_REUSEADDR;
    value = 1;
    setsockopt(listen_socket, level, name, &value, sizeof(int));
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(SERVER_PORT); 

    ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        logm_debug("bind to port 3009 fail!\n");
        exit(-1);
    }

    listen(listen_socket, 1);

    return;
}

void create_zmq_service_sockets(void)
{
    void *ctx;
    int value;
    int ret;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        logm_debug("create context fail!\n");
        exit(-1);
    }

    push_socket = zmq_socket(ctx, ZMQ_PUSH);
    if(NULL == push_socket)
    {
        logm_debug("create push_socket fail!\n");
        exit(-1);
    }
    ret = zmq_bind(push_socket, "tcp://*:5010");
    if(ret < 0)
    {
        logm_debug("bind push socket fail\n");
        exit(-1);
    }

    value = 10;
    zmq_setsockopt(push_socket, ZMQ_SNDHWM, &value, sizeof(int));

    pull_socket = zmq_socket(ctx, ZMQ_PULL);
    if(NULL == pull_socket)
    {
        logm_debug("create pull_socket fail!\n");
        exit(-1);
    }
    
    ret = zmq_bind(pull_socket, "tcp://*:5011");
    if(ret < 0)
    {
        logm_debug("bind pull socket fail\n");
        exit(-1);
    }


    return;
}

void set_connect_socket_opt(int sock)
{
    int level;
    int name;
    int value;
    struct linger socket_linger;
    int flags;

    level = SOL_SOCKET;
    name = SO_LINGER;
    socket_linger.l_onoff = 1;
    socket_linger.l_linger = 0;    
    setsockopt(sock, level, name, &socket_linger, sizeof(socket_linger));

    level = IPPROTO_TCP;
    name = TCP_NODELAY;
    value = 1;
    setsockopt(sock, level, name, &value, sizeof(int));

    flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags |= O_NONBLOCK); 

    return;
}

void accept_new_link(zmq_pollitem_t *items)
{
    struct sockaddr_in addr;
    socklen_t len = 0;
    memset(&addr, 0, sizeof(addr));
    
    connect_socket =  accept(listen_socket, (struct sockaddr *)&addr, &len);
    if(connect_socket < 0)
    {
        logm_debug("accept_new_link fail!\n");
        perror("");
        return;
    }
    else
    {
        logm_debug("accept_new_link success\n");
    }

    set_connect_socket_opt(connect_socket);

    items[1].fd = connect_socket;
    items[1].events = ZMQ_POLLIN;

    return;
}

#define LLRP_HEAD 0
#define LLRP_DATA 1




unsigned char *decode_llrp_msg(unsigned char ch, unsigned int *decode_len)
{
    static unsigned char decoded_buf[2048];
    static unsigned int decode_pos = 0;
	static unsigned int llrp_data_len = 0;
    unsigned char *start_pos = &decoded_buf[sizeof(T_Msg)];
    
    start_pos[decode_pos++] = ch;
    
    if(decode_pos == 10)
    {
        llrp_data_len = start_pos[2];
        llrp_data_len <<= 8;
        llrp_data_len |= start_pos[3];
        llrp_data_len <<= 8;
        llrp_data_len |= start_pos[4];
        llrp_data_len <<= 8;
        llrp_data_len |= start_pos[5];       
    }

    if(decode_pos == llrp_data_len)
    {
        *decode_len = decode_pos+sizeof(T_Msg);
        decode_pos = 0;
        llrp_data_len = 0;        
        return &decoded_buf[0];
    }

    return NULL;

}



void deal_llrp_socket_msg(zmq_pollitem_t *items)
{
    int recv_len;
    unsigned char recv_buf[8192];
    unsigned char *decoded_buf = NULL;
    unsigned int decoded_len = 0;

    // llrp msg head length is 10 bytes
    recv_len = recv(connect_socket, recv_buf, 8192, MSG_NOSIGNAL);
    logm_debug("recv %d bytes from pc socket \n", recv_len);

    if(recv_len < 0)
    {
        logm_debug("pc socket error, so close it !\n");
        close(connect_socket);
        connect_socket = -1;
        items[1].fd = listen_socket;
        items[1].events = ZMQ_POLLIN;
    }
    else if(recv_len == 0)
    {
        logm_debug("pc closed its socket\n");
        close(connect_socket);
        connect_socket = -1;
        items[1].fd = listen_socket;
        items[1].events = ZMQ_POLLIN;
    }
    else
    {
        int i;
        int send_len;
        T_Msg *ptMsg = NULL;
        
        logm_debug("begin decode_llrp_msg \n");

        for(i=0; i<recv_len; ++i)
        {
            decoded_buf = decode_llrp_msg(recv_buf[i], &decoded_len);
            if(NULL != decoded_buf)
            {
                ptMsg = (T_Msg *)decoded_buf;
                ptMsg->mtype = 1;
                ptMsg->wSenderTno = 8;
                ptMsg->ucLinkType = 1;
                ptMsg->ucLinkIndex = 1;
                ptMsg->wMsgID = 0xFD08;
                ptMsg->wMsgLen = decoded_len - sizeof(T_Msg);
                send_len = zmq_send(push_socket, decoded_buf, decoded_len, ZMQ_DONTWAIT);
                logm_debug("send %d bytes to push socket \n", decoded_len);
            }
        }
    }

    return;
}


int main(int argc, char *argv[])
{
    zmq_pollitem_t  items[3];
    int item_num;
    int rc;

    init_logm("comm");
    
    create_zmq_service_sockets();
    create_listen_socket();

    memset(items, 0, (sizeof(zmq_pollitem_t)*3));

    items[0].socket = pull_socket;
    items[0].events = ZMQ_POLLIN;
    
    items[1].socket = NULL;
    items[1].fd = listen_socket;
    items[1].events = ZMQ_POLLIN;

    
    while(1)
    {
        rc = zmq_poll(&items[0], 2, -1);
        logm_debug("zmq_poll return , return %d \n", rc);

        if(items[0].revents & ZMQ_POLLIN)
        {
            int recv_len;
            unsigned char recv_buf[8192];
            unsigned int encoded_len = 0;
            int send_len;
            unsigned char *encoded_buf;

            recv_len = zmq_recv(pull_socket, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) continue;
            logm_debug("recv from pull socket %d bytes \n", recv_len);  

            if((recv_len > sizeof(T_Msg)) && (connect_socket > 0))
            {
                send_len = send(connect_socket, &recv_buf[sizeof(T_Msg)], (recv_len-sizeof(T_Msg)), MSG_NOSIGNAL);
                logm_debug("send %d bytes to llrp client \n", send_len);
            }
                       
        }
        else if(items[1].revents & ZMQ_POLLIN)
        {
            if(items[1].fd == listen_socket)
            {
                accept_new_link(items);
            }
            else
            {
                deal_llrp_socket_msg(items);
            }
        }
        else
        {
            logm_debug("pull error ? \n");
        }
    }
}


