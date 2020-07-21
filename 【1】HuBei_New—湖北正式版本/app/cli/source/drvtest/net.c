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
#include <signal.h>

#include "bsp.h"

void *ser_socket = NULL;
void *clien_socket = NULL;
static unsigned char s_StopFlag = 0;
static pthread_t pSerThreadId = NULL;
static pthread_t pClienThreadId = NULL;
static unsigned int s_loopNum = 0;

#define MAX_MSG_LEN 256

void sig_nethandler(int sig)
{ 
    if ((NULL != pSerThreadId) || (NULL != pClienThreadId))
    {
        s_StopFlag = 1;
        pthread_join(pSerThreadId,NULL);
        pthread_join(pClienThreadId,NULL);
    }
}

void* SerThread(void*ps)
{
    unsigned int dwRet = 0;
    unsigned char aucBuf[MAX_MSG_LEN];
    int rc = 0;
    void *ctx;
    int value;
    int ret;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
        exit(-1);
    }

    ser_socket = zmq_socket(ctx, ZMQ_REP);
    if(NULL == ser_socket)
    {
        printf("server:create ser_socket fail!\n");
        exit(-1);
    }
    ret = zmq_bind(ser_socket, "tcp://10.86.20.220:6060");
    if(ret < 0)
    {
        printf("server:bind server socket fail\n");
        exit(-1);
    }

    value = 0;
    ret = zmq_setsockopt(ser_socket, ZMQ_LINGER, &value, sizeof(int));
    if(ret < 0)
    {
        printf("server:zmq_setsockopt fail\n");
        exit(-1);
    }
    value=1000;
    ret = zmq_setsockopt(ser_socket,ZMQ_RCVTIMEO,&value,sizeof(value));
    if(ret < 0)
    {
        printf("server:zmq_setsockopt fail\n");
        return -1;
    }

    while ((!s_StopFlag) && s_loopNum)
    {
        
        rc = zmq_recv(ser_socket,aucBuf,MAX_MSG_LEN,0);
        if(rc < 0)
        {
           printf("ser:zmq_recv error errno=%d\r\n", rc);
           continue;
        }
        else
        {
            rc = zmq_send(ser_socket,aucBuf,MAX_MSG_LEN,0);
            if(rc < 0)
            {
               printf("ser:zmq_send error errno=%d\r\n", rc);
               continue;
            }
        }
    }
    pSerThreadId = NULL;
    zmq_close(ser_socket);
}

void* ClienThread(void*ps)
{
    unsigned int dwRet = 0;
    unsigned char aucBuf[MAX_MSG_LEN];
    unsigned char aucRecBuf[MAX_MSG_LEN];
    int rc = 0;
    unsigned int dwSucessNum = 0;
    unsigned int dwErrorNum = 0;
    unsigned int dwSendErrorNum = 0;
    unsigned int i = 0;
    void *ctx;
    int value;
    int ret;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
        exit(-1);
    }

    clien_socket = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == clien_socket)
    {
        printf("client:create clien_socket fail!\n");
        exit(-1);
    }
    ret = zmq_connect(clien_socket, "tcp://192.168.1.230:6090");
    if(ret < 0)
    {
        printf("client:zmq_connect client socket fail,error = %x\n", ret);
        exit(-1);
    }

    value = 0;
    ret = zmq_setsockopt(clien_socket, ZMQ_LINGER, &value, sizeof(int));
    if(ret < 0)
    {
        printf("client:zmq_setsockopt fail\n");
        exit(-1);
    }

    value=1000;
    ret = zmq_setsockopt(clien_socket,ZMQ_RCVTIMEO,&value,sizeof(value));
    if(ret < 0)
    {
        printf("client:zmq_setsockopt fail\n");
        return -1;
    }


    for (i = 0; i < MAX_MSG_LEN/2; i++)
    {
        aucBuf[i] = 0xaa;
        aucBuf[i+1] = 0x55;
    }

    while ((!s_StopFlag) && s_loopNum)
    {
        usleep(500);
        s_loopNum--;
        rc = zmq_send(clien_socket,aucBuf,MAX_MSG_LEN,0);
        if(rc < 0)
        {
           dwSendErrorNum++;
           printf("client:zmq_send error errno=%d\r\n", rc);
           continue;
        }
        else
        {
            memset(aucRecBuf, 0, MAX_MSG_LEN);
            rc = zmq_recv(clien_socket,aucRecBuf,MAX_MSG_LEN,0);
            if(rc < 0)
            {
               dwErrorNum++;
               printf("client:zmq_recv error errno=%d\r\n", rc);
               continue;
            }
            else
            {
                if (0 == memcmp(aucBuf, aucRecBuf, MAX_MSG_LEN))
                {
                    dwSucessNum ++;
                    printf("net success%d\r\n", dwSucessNum);
                }
                else
                {
                    dwErrorNum++;
                }
            }
        }
    }
    s_StopFlag = 0;
    pClienThreadId = NULL;
    zmq_close(clien_socket);
    printf("success num =%d\r\n", dwSucessNum);
    printf("rec error num =%d\r\n", dwErrorNum);
    printf("send error num =%d\r\n", dwSendErrorNum);
}


unsigned int  drvtest_net_loopback(unsigned int dwLoopNum)
{
    s_StopFlag = 0;
    pSerThreadId = NULL;
    pClienThreadId = NULL;
    s_loopNum = dwLoopNum;
    signal(SIGINT, sig_nethandler);

  	if(pthread_create(&pSerThreadId,NULL,SerThread,NULL))
	{
		printf("failed to create server thread!\n");
		return 1;
  	}

  	if(pthread_create(&pClienThreadId,NULL,ClienThread, NULL))
	{
		printf("failed to create client thread!\n");
		return 2;
  	}

	return 0;
}
