#include <zmq.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include "etc_codec_cq.h"
#include "logm.h"
#include "comm_multipath.h"
#include "etc_codec_ff_rsctl.h"
#include "etc_codec_ff_crc.h"
#include "jiffs.h"

#define RECV_PC_MAX_LEN               (512)
#define RECV_PC_DATA_MAX_LEN          (RECV_PC_MAX_LEN - 12)
#define SEND_PC_MAX_LEN               (512)
#define ACK_PC_MAX_LEN                (500)

void *comm_ctx = NULL ;
void *reportsock_recv = NULL;
void *reportsock_send = NULL;
int uart_fd;

unsigned char report_send_seq;
unsigned char send_b0_flag = 1;


void * get_config_socket_uart()
{    
    int value;
    void *configsock = NULL;

    if(NULL == comm_ctx)
    {
        logm_debug("create context fail (get_reportsock_socket)!\n");
        exit(-1);
    }

    configsock = zmq_socket(comm_ctx, ZMQ_REQ);
    if(NULL == configsock)
    {
        logm_debug("create REQ sock fail!\n");
        exit(-1);
    }

    value = 2000;
    zmq_setsockopt(configsock, ZMQ_RCVTIMEO, &value, sizeof(value));
    zmq_connect(configsock, "tcp://127.0.0.1:6501");

    return configsock;
}


void get_report_recv_send_socket_uart()
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
    zmq_bind(reportsock_recv, "tcp://*:5085");


    reportsock_send = zmq_socket(comm_ctx, ZMQ_PUSH);
    if(NULL == reportsock_send)
    {
        logm_debug("create reportsock_send sock fail!\n");
        exit(-1);
    }
    //Keep only last message
    zmq_setsockopt(reportsock_send, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_bind(reportsock_send, "tcp://*:5086");
}

void execute_rsu_report_command_uart(void *sock, unsigned char *command, unsigned int command_len)
{
    int ret;
    
    logm_debug("PC ack trade %d -> ", command_len);
    logm_debug_buffer(command, command_len);

    ret = zmq_send(sock, command, command_len, ZMQ_DONTWAIT);
    if(ret <= 0)
    {
        logm_err("send  error\n");
        return;
    }
}

void execute_command_uart(void *sock, unsigned char *command, unsigned int command_len, unsigned char *ack, unsigned int *ack_len)
{
    int ret;

    logm_debug("cmd to ctrl %d -> ", command_len);
    logm_debug_buffer(command, command_len);


    ret = zmq_send(sock, command, command_len, 0);
    
    ret = zmq_recv(sock, ack, ACK_PC_MAX_LEN, 0);
    if(ret <= 0)
    {
        logm_err("recv error\n");
        *ack_len = 0;
        return;
    }
    
    logm_debug("ack from ctrl %d <-  ", ret);
    logm_debug_buffer(ack, ret);

    *ack_len = ret;

    return;
}


int send_to_client_uart(unsigned char *buf, unsigned int len)
{
    int sended_len = 0;
    int fragment;

    while(sended_len < len)
    {
        fragment = write(uart_fd, &buf[sended_len], (len - sended_len));

        if(fragment < 0)
        {
            logm_debug("send to pc uart error!\n");
            return -1;
        }
        sended_len += fragment;
    }

    logm_debug("send to pc %d --> ", len);
    logm_debug_buffer(buf, len);

    return 0;
}

int execute_raw_command_uart(void *configsock, void *reportacksock, unsigned char *raw_frame, unsigned int frame_len)
{
    unsigned char *decoded_buf = NULL;
    unsigned char *response = NULL;
    unsigned int decoded_len;
    unsigned int response_len;
    unsigned int ack_len;
    int ret;
    unsigned char recv_seq;
    unsigned char ack[ACK_PC_MAX_LEN];
        

    decoded_buf = etc_decode_ff_rsctl_optimise(raw_frame, frame_len, &decoded_len);
    //decoded_buf = etc_decode_ff_crc_optimise(raw_frame, frame_len, &decoded_len);
    /* get PC ack seq */
    recv_seq = raw_frame[2]; 
    if((NULL != decoded_buf) && (decoded_len != 0))
    {
        // ETC Trade ack frame
        if ( ((decoded_buf[0] == 0xC1) && (decoded_buf[1] != 0x00))
            || (decoded_buf[0] == 0xC2) 
            || (decoded_buf[0] == 0xC3) || (decoded_buf[0] == 0xC6)
            || (decoded_buf[0] == 0xC7) || (decoded_buf[0] == 0xC9))
        {
            /* judge sequence */
           unsigned char seq_tmp = ((recv_seq & 0xF0) >> 4) | ((recv_seq & 0x0F) << 4);
                                
           if(seq_tmp != report_send_seq)
            {
                logm_debug("recv %02x and send %02x seq not match\n", recv_seq, report_send_seq);
                return -1;
           }
            execute_rsu_report_command_uart(reportacksock, decoded_buf, decoded_len);
            /* clear send sequence */
           report_send_seq = 0x00;
        }
        else
        {
            if(decoded_buf[0] == 0xC0)
            {
                send_b0_flag = 0;
            }
           
            execute_command_uart(configsock, decoded_buf, decoded_len, ack, &ack_len);                
            if(ack_len == 0)
            {
                logm_err("execute command error \n");
                return -1;
            }
            if(ack[0] != 0xFF) // PC CMD Error, and Do not ACK
            {
                //response = etc_encode_ff_crc(ack, ack_len, &response_len);
                response = etc_encode_ff_rsctl(ack, ack_len, &response_len);
                if(response[3] == 0xb0)
                {
                    response[2] = 0x08;
                    report_send_seq = response[2];
                }
                ret = send_to_client_uart(response, response_len);
                if(ret < 0)
                {
                    return -1;
                }
            }                
        }
    }
    else if((NULL != decoded_buf) && (decoded_len == 0))
    {
        logm_debug("PC Ack Temp\n");
    }
    
    return 0;
}

int process_report_Trade_uart(void *rsuReportSock)
{
    int recv_len, ret;
    unsigned char *response = NULL;
    unsigned int response_len;
    unsigned char recv_buffer[SEND_PC_MAX_LEN];
    
    recv_len = zmq_recv(rsuReportSock, recv_buffer, SEND_PC_MAX_LEN, 0);
    if(recv_len > 0)
    {
        logm_debug("From ctrl_trade %d <-  ", recv_len);
        logm_debug_buffer(recv_buffer, recv_len);        

      // response = etc_encode_ff_crc(recv_buffer, recv_len, &response_len);
        response = etc_encode_ff_rsctl(recv_buffer, recv_len, &response_len);

        /* record RSU send_data sequence */
        
        if((send_b0_flag) && (response[3] == 0xb0))
        {
            response[2] = 0x98;
            report_send_seq = response[2];
            
            
        }
        else
        {
            report_send_seq = response[2];
        }
        
        ret = send_to_client_uart(response, response_len);
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


void *serve_func_uart(void *para)
{
    int recv_len = 0;
    int already_recv_len = 0;
    int ret;
    void *configsock = NULL;
    unsigned int data_len = RECV_PC_DATA_MAX_LEN;
  
    unsigned char recv_buf[RECV_PC_DATA_MAX_LEN];
    
    
        
    configsock = get_config_socket_uart();        

    while(1)
    {
        recv_len = read(uart_fd, &recv_buf[already_recv_len], 1);
        already_recv_len += recv_len;
        /*set recv length threshold */
        if(already_recv_len <=3)
        {
            continue;
        }
        // judge STX 
        if((recv_buf[0] != 0xFF) || (recv_buf[1] != 0xFF))
        {
            recv_len = 0;
            already_recv_len = 0;
            data_len = RECV_PC_DATA_MAX_LEN;
            memset(recv_buf, 0x00, SEND_PC_MAX_LEN);
            continue;
        }
        
        #if 0
        if((already_recv_len >= 8) && (data_len == RECV_PC_DATA_MAX_LEN))
        {
            /* get data_field length */
            data_len = (recv_buf[6] << 8) | recv_buf[7];
        }
        #endif

        // judge ETX
        if((already_recv_len > 2) && (recv_buf[already_recv_len - 1] != 0xFF))//lzw
        {
            if(already_recv_len > SEND_PC_MAX_LEN)
            {
                recv_len = 0;
                already_recv_len = 0;
                data_len = RECV_PC_DATA_MAX_LEN;
                memset(recv_buf, 0x00, SEND_PC_MAX_LEN);
            }
            continue;
        }
                
        if(already_recv_len >3)
        {
            logm_debug("Recv from pc %d <--",already_recv_len);
            logm_debug_buffer(recv_buf,already_recv_len);
            execute_raw_command_uart(configsock, reportsock_send, recv_buf, already_recv_len); 
        }

        recv_len = 0;
        already_recv_len = 0;
        data_len = RECV_PC_DATA_MAX_LEN;
        memset(recv_buf, 0x00, SEND_PC_MAX_LEN);   
    }
    zmq_close(configsock);    

    return (void *)0;
}

int main(int argc, char *argv[])
{
    pthread_t uart_recv;

    init_jiffs();
    init_logm("uart");
    set_timeflag();

    //the serial port in the back rd50-c is /dev/ttyS1
    uart_fd = open("/dev/ttyS1", O_NOCTTY | O_RDWR);
    if(uart_fd < 0) 
    {
        perror("open /dev/ttyS1 failed\n");
        exit(-1);
    }
    logm_debug("open /dev/ttyS1 success!\n");

    get_report_recv_send_socket_uart();

    pthread_create(&uart_recv, NULL, serve_func_uart, NULL);
    
    while(1)
    {
        process_report_Trade_uart(reportsock_recv);
    }
    
    zmq_close(reportsock_recv);
    zmq_close(reportsock_send);
    zmq_ctx_destroy(comm_ctx);
    close(uart_fd);

    return 0;
}






