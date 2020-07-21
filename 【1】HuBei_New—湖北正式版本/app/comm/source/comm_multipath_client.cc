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
#include <fstream>
#include <json/json.h>
#include "etc_codec_cq.h"
#include "logm.h"
#include "etc_codec_ff.h"

using namespace std;

unsigned char unsent_buffer[256];
unsigned char unsend_len;
char serverip[32] = "192.168.1.180";
static int report_count = 0;

int get_server_ip(char *serverip)
{
}

int connect_server(char *serverip)
{
    int csock;
    struct sockaddr_in serv_addr;
    int ret;
    struct timeval timeout;

    csock = socket(AF_INET, SOCK_STREAM, 0);
    if(csock < 0) 
    {
        logm_debug("creat client socket fail!\n");
        exit(-1);
    }

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(csock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    setsockopt(csock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(serverip);
    serv_addr.sin_port = htons(10240);

    ret = connect(csock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0)
    {
        logm_info("connect to server %s fail \n", serverip);
        close(csock);
        return ret;
    }
    else
    {
        logm_info("connect to server %s success \n", serverip);
        return csock;
    }
}

int raw_send(int sock, unsigned char *send_buffer, unsigned char send_len)
{
    int write_len;
    int recv_len;
    unsigned char recv_buffer[256];

    write_len = write(sock, send_buffer, send_len);
    if(write_len <= 0)
    {
        close(sock);
        logm_err("write to pc error \n");
        return -1;
    }

    recv_len = read(sock, recv_buffer, 256);
    if(recv_len < 0)
    {
        close(sock);
        logm_err("read from pc error %d\n", recv_len);
        return -1;
    }

    report_count += 1;

    logm_debug("report_count %d \n", report_count);

    return 0;
}


void save_unsent_frame(unsigned char *encoded_frame, unsigned char encoded_len)
{
    memcpy(unsent_buffer, encoded_frame, encoded_len);
    unsend_len = encoded_len;

    return;
}

int resend_frame(int sock)
{
    int ret;
    if(unsend_len > 0) 
    {
        ret = raw_send(sock, unsent_buffer, unsend_len);
        if(ret < 0)
        {
        	logm_debug("resend frame fail\n");
            return -1;
        }
        else
        {
            unsend_len = 0;
        }
    }

    return 0;
}

int sendReportToServer(void *pullsock, int csock)
{
    int ret;
    int recv_len;
    int write_len;

    unsigned char recv_buffer[1024];
    unsigned char *encoded_frame;
    unsigned int encoded_len;
    unsigned int decoded_len;

    ret = resend_frame(csock);
    if(ret < 0) 
        return -1;

    while(1) 
    {
        recv_len = zmq_recv(pullsock, &recv_buffer[1], 1024,0);
        if(recv_len > 0)
        {
            recv_buffer[0] = 0x8d;
            encoded_frame = etc_encode_ff(recv_buffer, recv_len+1, &encoded_len);
            ret = raw_send(csock, encoded_frame, encoded_len);
            if(ret < 0)
            {
                save_unsent_frame(encoded_frame, encoded_len);
                return -1;
            }
        }
        else
        {
            logm_err("recv from pullsock error %d \n", recv_len);
        }
    }
    return 0;
}


void loadConfig()
{
    ifstream configfile;
    Json::Reader reader;
    Json::Value jsonConfig;
    bool parseRet;

    configfile.open("/opt/bin/scheduler.json");
    if(!configfile.is_open())
    {
        logm_err("open config file fail\n");
        return;
    }

    parseRet = reader.parse(configfile, jsonConfig, false);
    if(!parseRet)
    {
        logm_err("parse config file fail\n");
        configfile.close();
        return;
    }

    if(jsonConfig.isMember("server"))
    {
        if(jsonConfig["server"].isMember("ip"))
        {
            memset(serverip, 0 ,24);
            memcpy(serverip, jsonConfig["server"]["ip"].asCString(), 24);
            logm_debug("serverip %s\n", serverip);
        }
    }

    configfile.close();

    return;
}



int main(int argc, char *argv[])
{
    int ret;
    int client_sock;
    
    void *ctx;
    void *pullsock;

    init_logm("comm");
    loadConfig();

    ctx = zmq_init (1);
    if(NULL == ctx) 
    {
        logm_debug("create context fail!\n");
        exit(-1);
    }

    pullsock = zmq_socket(ctx, ZMQ_PULL);
    if(NULL == pullsock)
    {
        logm_debug("create PULL  sock fail!\n");
        exit(-1);
    }

    ret = zmq_bind(pullsock, "tcp://*:5080");
    if(ret < 0)
    {
        logm_debug("bind PULL  sock fail!\n");
        exit(-1);
    }

    //get_server_ip(serverip);

    while(1) 
    {
        client_sock = connect_server(serverip);
        if(client_sock > 0) 
        {
            sendReportToServer(pullsock, client_sock);
        }
        else
        {
            usleep(500000);
        }
    }

    return 0;
}




