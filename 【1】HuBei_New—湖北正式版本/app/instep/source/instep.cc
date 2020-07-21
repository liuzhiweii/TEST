#include <zmq.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <json/json.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "utimer.h"
#include "logm.h"
#include "jiffs.h"
#include "bsp.h"
#include "instep.h"
#include <abn.h>

using namespace std;


void master_instep::init()
{
	getConfig();
	// init zmq_socket
	zmq_sock_init();
}

void master_instep::run()
{
	if(m_control_ID == WORK_MODE_MASTER)
	{
		// master, controller ID = 1
		work_mode_master();
	}
	else
	{
		// backup, controller ID = 2
		work_mode_backup();
	}	
}

void master_instep::zmq_sock_init()
{
	int value = 1;

	m_ctx = zmq_init(1);
    assert(m_ctx);

// *********************** socket for scheduler *************************** //
	m_sch_socket_send = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(m_sch_socket_send);    
    //Keep only last message 
    zmq_setsockopt(m_sch_socket_send, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_connect(m_sch_socket_send, "tcp://127.0.0.1:7990");

    m_sch_socket_recv = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_sch_socket_recv);
    //Keep only last message
    zmq_setsockopt(m_sch_socket_recv, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_connect(m_sch_socket_recv, "tcp://127.0.0.1:7991");
// ***********************************************************************//

}

void master_instep::work_mode_master()
{
	pthread_attr_t a_thread_attr;
	pthread_t  a_thread_server;

	pthread_attr_init(&a_thread_attr);   // set a thread attribute detached
	pthread_attr_setdetachstate(&a_thread_attr, PTHREAD_CREATE_DETACHED);
	

	// if control communicate_type is Net

	int listenSock = -1;
	struct sockaddr_in addr;
	socklen_t len = 0;	
    unsigned char recv_buf[64];	
    int recv_len;
    int ret;


	listenSock =  create_listen_sock();

	while(1)
	{
		memset(&addr, 0, sizeof(addr));
		m_serverSock =  accept(listenSock, (struct sockaddr *)&addr, &len);

        if(m_serverSock > 0)
        {
            
            if(recv_thread_exist_flag != 0)
                {
                    pthread_cancel(a_thread_server);  //close old thread
                    recv_thread_exist_flag = 0;
                    logm_debug("Old recv Thread Cancled\n");
                }
            
            logm_debug("listen one client\n");
            ret = pthread_create(&a_thread_server, &a_thread_attr, master_server_func, (void *)this);
            if(ret == 0)
            {
                recv_thread_exist_flag = 1;
            }
        }
    }

    pthread_attr_destroy(&a_thread_attr);

    return;
}
                   


void master_instep::work_mode_backup()
{
    unsigned char recv_buf[64];
    int recv_len;
    int ret;
	pthread_attr_t a_thread_attr;
	pthread_t  a_thread_server;

	pthread_attr_init(&a_thread_attr);
	pthread_attr_setdetachstate(&a_thread_attr, PTHREAD_CREATE_DETACHED);

	// if control communicate_type is Net
    
    while(1)
    {
    
            m_clientSock = connectServer();
	        if(m_clientSock < 0)
	        {
                sleep(50);
	        }
            else
            { 
                backup_client_func_poll();
                /*
                if(recv_thread_exist_flag != 0)
                {
                    pthread_cancel(a_thread_server);  //close old thread
                    recv_thread_exist_flag = 0;
                    logm_debug("Old recv Thread Cancled\n");
                }
                
                ret = pthread_create(&a_thread_server, &a_thread_attr, backup_client_func, (void *)this);
                if(ret == 0)
                {
                    recv_thread_exist_flag = 1;
                }
                */
            }
        
    }
    pthread_attr_destroy(&a_thread_attr);

    return;
}


void master_instep::getConfig()
{
	ifstream configfile;
    Json::Reader reader;
    Json::Value jsonConfig;
    bool parseRet;	

    configfile.open("/config/scheduler.json");
    if(!configfile.is_open())
    {
        logm_err("open config file fail, next to open init_config file\n");

        configfile.open("/opt/bin/scheduler.json");
        if(!configfile.is_open())
        {
            logm_err("open init_config file fail\n");
            return;
        }
    }

 
    parseRet = reader.parse(configfile, jsonConfig, false);
    if(!parseRet) 
	{
        logm_err("parse config file fail\n");
        configfile.close();
        return;
    }

	if(jsonConfig.isMember("control_id"))
	{
		m_control_ID = jsonConfig["control_id"].asInt();
        logm_debug("m_control_ID %d\n", m_control_ID);
	}

	if(jsonConfig.isMember("control_master_ip"))
    {        
        memset(m_master_ip, 0 ,24);
        memcpy(m_master_ip, jsonConfig["control_master_ip"].asCString(), 24);
        logm_debug("m_master_ip %s\n", m_master_ip);
    }
    configfile.close();
}

int master_instep::connectServer()
{
    int ret;
	int linksock = -1;

    linksock = socket(AF_INET, SOCK_STREAM, 0);
    if(linksock < 0) 
	{
        logm_debug("creat m_clientSock socket fail!\n");
        return -1;
    }

    struct timeval timeout;
    struct sockaddr_in serv_addr;
	//m_master_ip = M_MASTER_IP;

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(linksock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    setsockopt(linksock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(M_MASTER_IP);
    serv_addr.sin_port = htons(SYNC_SERVER_PORT);

    ret = connect(linksock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0)
	{   printf("4\n");
        logm_info("connect to server %s fail \n", m_master_ip);
        close(linksock);
        return ret;
    }
	else 
	{   printf("5\n");
        logm_info("connect to server %s success \n", m_master_ip);
        return linksock;
    }
}

int master_instep::create_listen_sock()
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
    addr.sin_port = htons(SYNC_SERVER_PORT);

    ret = bind(lsock, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        logm_debug("bind to port %d fail!\n", SYNC_SERVER_PORT);
        exit(-1);
    }

    listen(lsock, 2);

    return lsock;
}

void *master_instep::master_server_func(void *para)
{

	master_instep *master_instep_handle;	
	master_instep_handle = (master_instep *)para;
    zmq_pollitem_t m_pollItems[2];

    int recv_len;
	int send_len;
    unsigned char recv_buf[64];
	unsigned char send_buf[64];
    int ret;    

    memset(m_pollItems, 0, (sizeof(zmq_pollitem_t) * 2));    
    m_pollItems[0].socket = NULL;
    m_pollItems[0].fd = master_instep_handle->m_serverSock;
    m_pollItems[0].events = ZMQ_POLLIN;
    m_pollItems[1].socket = master_instep_handle->m_sch_socket_recv;
    m_pollItems[1].events = ZMQ_POLLIN;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , NULL); 

    while(1)
    {
        ret = zmq_poll(m_pollItems, 2, -1);

        if(m_pollItems[0].revents & ZMQ_POLLIN)
        {
            recv_len = recv(master_instep_handle->m_serverSock, recv_buf, 64, MSG_NOSIGNAL);
                if(recv_len <= 0)
                {
                    //close(master_instep_handle->m_serverSock);
                    logm_debug("recv from pc-2 failed so close socket\n");
                    break;
                }
                else if(recv_len > 2)
                {
                    logm_debug("recv data from pc-2 :");
                    logm_debug_buffer(recv_buf,recv_len);
                
                    ret = zmq_send(master_instep_handle->m_sch_socket_send, recv_buf, recv_len, ZMQ_DONTWAIT);
                    if(ret < 0)
                    {
                        logm_debug("send data to sch failed!\n");
                        break;
                    }                   
                    else
                    {
                        logm_debug("send data to sch --->");
                        logm_debug_buffer(recv_buf,recv_len);
                    }
                }
                else
                {
                    logm_debug("recv data from pc-2 :");
                    logm_debug_buffer(recv_buf,recv_len);
                }
        }

        if(m_pollItems[1].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(master_instep_handle->m_sch_socket_recv, recv_buf, 64, ZMQ_DONTWAIT);
            if(recv_len > 0)
            {
                ret = send(master_instep_handle->m_serverSock, recv_buf, recv_len, MSG_NOSIGNAL);
                if(ret < 0)
                {
                    logm_debug("send data to pc-2 failed!\n");
                }
                else
                {
                    logm_debug("send data to pc-2 :");
                    logm_debug_buffer(recv_buf,recv_len);
                }
            }
        }
    }

    close((int)master_instep_handle->m_serverSock);  
    logm_debug("recv thread_exit\n");
    return (void *)0;

}

void master_instep::backup_client_func_poll()
{
    
    zmq_pollitem_t m_pollItems[2];


    int recv_len;
    unsigned char recv_buf[64]; 
    int ret;

    memset(m_pollItems, 0, (sizeof(zmq_pollitem_t) * 2));    
    m_pollItems[0].socket = NULL;
    m_pollItems[0].fd = m_clientSock;
    m_pollItems[0].events = ZMQ_POLLIN;
    m_pollItems[1].socket = m_sch_socket_recv;
    m_pollItems[1].events = ZMQ_POLLIN;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , NULL); 


    while(1)
    {
        ret = zmq_poll(m_pollItems, 2, -1);
        if(m_pollItems[0].revents & ZMQ_POLLIN)
        {
            recv_len = recv(m_clientSock, recv_buf, 64, MSG_NOSIGNAL);
            if(recv_len > 2)
            {
                ret = zmq_send(m_sch_socket_send, recv_buf, recv_len, ZMQ_DONTWAIT);
                if(ret < 0)
                {
                    logm_debug("send data to sch failed!\n");
                }
                 else
                {
                    logm_debug("pc2 send data to sch -->");
                    logm_debug_buffer(recv_buf,recv_len);
                }
            }
            else if(recv_len == 2)
            {
                logm_debug("recv pc_1 send data ack -->");
                logm_debug_buffer(recv_buf,recv_len);
            }
            else
            {
                close(m_clientSock);
                logm_debug("recv data from pc_1 failed, so close it\n");
                break;
            }
            
                    
        }
        if(m_pollItems[1].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(m_sch_socket_recv, recv_buf, 64, ZMQ_DONTWAIT);
                if(recv_len > 0)
                {
                    ret = send(m_clientSock, recv_buf, recv_len, MSG_NOSIGNAL);
                    if(ret < 0)
                    {
                        logm_debug("send data to pc-1 failed!\n"); 
                        break;                    
                    }
                    else
                    {
                        logm_debug("send data to pc-1 -->");
                        logm_debug_buffer(recv_buf,recv_len);
                    }
                }
        }

    }
    
    close(m_clientSock);
    logm_debug("recv thread_exit\n");
    return;
}

static void *master_instep::backup_client_func(void *para)
{
    master_instep *backup_instep_handle;	
	backup_instep_handle = (master_instep *)para;
    zmq_pollitem_t m_pollItems[2];


    int recv_len;
    unsigned char recv_buf[64]; 
    int ret;

    memset(m_pollItems, 0, (sizeof(zmq_pollitem_t) * 2));    
    m_pollItems[0].socket = NULL;
    m_pollItems[0].fd = backup_instep_handle->m_clientSock;
    m_pollItems[0].events = ZMQ_POLLIN;
    m_pollItems[1].socket = backup_instep_handle->m_sch_socket_recv;
    m_pollItems[1].events = ZMQ_POLLIN;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , NULL); 


    while(1)
    {
        ret = zmq_poll(m_pollItems, 2, -1);
        if(m_pollItems[0].revents & ZMQ_POLLIN)
        {
            recv_len = recv(backup_instep_handle->m_clientSock, recv_buf, 64, MSG_NOSIGNAL);
            if(recv_len > 2)
            {
                ret = zmq_send(backup_instep_handle->m_sch_socket_send, recv_buf, recv_len, ZMQ_DONTWAIT);
                if(ret < 0)
                {
                    logm_debug("send data to sch failed!\n");
                }
                 else
                {
                    logm_debug("pc2 send data to sch -->");
                    logm_debug_buffer(recv_buf,recv_len);
                }
            }
            else
            {
                logm_debug("pc2 send data to sch -->");
                logm_debug_buffer(recv_buf,recv_len);
            }
                    
        }
        if(m_pollItems[1].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(backup_instep_handle->m_sch_socket_recv, recv_buf, 64, ZMQ_DONTWAIT);
                if(recv_len > 0)
                {
                    ret = send(backup_instep_handle->m_clientSock, recv_buf, recv_len, MSG_NOSIGNAL);
                    if(ret < 0)
                    {
                        logm_debug("send data to pc-1 failed!\n"); 
                        break;                    
                    }
                    else
                    {
                        logm_debug("send data to pc-1 -->");
                        logm_debug_buffer(recv_buf,recv_len);
                    }
                }
        }

    }
    backup_instep_handle->recv_thread_exist_flag = 0;
    close(backup_instep_handle->m_clientSock);
    logm_debug("recv thread_exit\n");
    return (void *)0;
}


master_instep::master_instep()
{
	m_ctx = NULL;
	m_control_sync_comm_type = 0;
    recv_thread_exist_flag = 0;

}


int main(int argc, char *argv[])
{
	// register mbm to logm, and set debug_infor to display jiffies
	init_jiffs(); 
	init_logm("instep");
	set_timeflag();

	master_instep master_Instep;
	master_Instep.init();
	master_Instep.run();

    return 0;
}