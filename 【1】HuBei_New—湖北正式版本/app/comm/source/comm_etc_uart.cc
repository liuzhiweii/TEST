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

void *push_socket = NULL;
void *pull_socket = NULL;

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

void *thread_func(void *uart_fd)
{
    int read_len;
    unsigned char read_buf[1024];
    unsigned char *decoded_buf = NULL;
    unsigned int decoded_len = 0;
    int i;
    int send_len;

    while(1)
    {
        read_len = read((int)uart_fd, read_buf, 1024);
        if(read_len > 0)
        {
        	for(i=0; i<read_len; ++i)
             {
                  decoded_buf = etc_decode_cq(read_buf[i], &decoded_len);
            	     if(NULL != decoded_buf)
                  {
                        send_len = zmq_send(push_socket, decoded_buf, decoded_len, ZMQ_DONTWAIT);
                        logm_debug("send %d bytes to push socket \n", decoded_len);
                   }
              }
        }
    }
}

void create_read_uart_thread(int fd)
{
    int ret;
     pthread_t  a_thread;

     ret = pthread_create(&a_thread, NULL, thread_func, (void *)fd);
    if (ret != 0) 
    {
    	perror("");
    	exit(-1);
    }
}


int main(int argc, char *argv[])
{
    int uart_fd;
    zmq_pollitem_t  items[1];
    int item_num;
    int rc;

    init_logm("comm");

    uart_fd = open("/dev/ttyS0", O_NOCTTY|O_RDWR);
    if(uart_fd < 0) 
    {
        perror("");
        exit(-1);
    }

    logm_debug("open /dev/ttyS0 success!\n");

    create_zmq_service_sockets();
    create_read_uart_thread(uart_fd);

    items[0].socket = pull_socket;
    items[0].events = ZMQ_POLLIN;

    while(1)
    {
        rc = zmq_poll(items, 1, -1);
        logm_debug("zmq_poll return , return %d \n", rc);

        if(items[0].revents & ZMQ_POLLIN)
        {
            int recv_len;
            unsigned char recv_buf[8192];
            unsigned int encoded_len = 0;
            int send_len;
            unsigned char *encoded_buf;

            recv_len = zmq_recv(pull_socket, recv_buf, sizeof(recv_buf), 0);
            if(recv_len <= 0)  continue;

            logm_debug("recv from pull socket %d bytes \n", recv_len);  
            //send_log_msg("hellow\n");
            encoded_buf = etc_encode_cq(recv_buf, recv_len, &encoded_len);
            if(NULL != encoded_buf)
            {
            	   write(uart_fd, encoded_buf, encoded_len);
            }            
        }
    }

    return 0;
}