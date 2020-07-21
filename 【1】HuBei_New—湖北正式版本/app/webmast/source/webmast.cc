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
#include "webmast.h"
#include <abn.h>

using namespace std;


void web_mast::init()
{
    
    m_config = new webmast_config();
    m_config->LoadBaseInforConfig();
    m_PSAMNum = m_config->m_psamConfig.size();
    m_antennaNum = m_config->m_rfConfig.size();

	zmq_sock_init();
}

void web_mast::run()
{	
	work_mode_master();	
}

void web_mast::zmq_sock_init()
{
	int value = 1;
    int ret;
    char ip_buffer[32];

	m_ctx = zmq_init(1);
    assert(m_ctx);

// *********************** socket for scheduler *************************** //
	m_sch_socket_send = zmq_socket(m_ctx, ZMQ_PUSH);
    assert(m_sch_socket_send);    
    //Keep only last message 
    zmq_setsockopt(m_sch_socket_send, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_connect(m_sch_socket_send, "tcp://127.0.0.1:6601");

    m_sch_socket_recv = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_sch_socket_recv);
    //Keep only last message
    zmq_setsockopt(m_sch_socket_recv, ZMQ_CONFLATE, &value, sizeof(value));
    zmq_connect(m_sch_socket_recv, "tcp://127.0.0.1:6600");
// ***********************************************************************//

/*********************** socket for ant_device ***************************/
    for(int i = 0; i < m_antennaNum; i++)
    {
        m_antInfor[i].proxy_req_sock = zmq_socket(m_ctx, ZMQ_REQ);
        assert(m_antInfor[i].proxy_req_sock);
        value = 500; /* recv_timeout 500ms */
        zmq_setsockopt(m_antInfor[i].proxy_req_sock, ZMQ_RCVTIMEO, &value, sizeof(value));

        sprintf(ip_buffer, "tcp://%s:5100", m_config->m_rfConfig[i]->rf_ipaddr);
        ret = zmq_connect(m_antInfor[i].proxy_req_sock, ip_buffer);
        
        assert(ret == 0);
    }
    

/************************************************************************/  

}

void web_mast::work_mode_master()
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
            ret = pthread_create(&a_thread_server, &a_thread_attr, web_mast_func, (void *)this);
            if(ret == 0)
            {
                recv_thread_exist_flag = 1;
            }
        }
    }

    pthread_attr_destroy(&a_thread_attr);

    return;
}
                   

int web_mast::create_listen_sock()
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
    addr.sin_port = htons(WEBMAST_SERVER_PORT);

    ret = bind(lsock, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        logm_debug("bind to port %d fail!\n", WEBMAST_SERVER_PORT);
        exit(-1);
    }

    listen(lsock, 2);

    return lsock;
}

void *web_mast::web_mast_func(void *para)
{

	web_mast *webmast_handle;	
	webmast_handle = (web_mast *)para;
    zmq_pollitem_t m_pollItems[2];

    int recv_len;
	int send_len;
    unsigned char recv_buf[64];
	unsigned char send_buf[64];
    signed char rfs_temp[16];
    int ret, i;    

    memset(m_pollItems, 0, (sizeof(zmq_pollitem_t) * 2));    
    m_pollItems[0].socket = NULL;
    m_pollItems[0].fd = webmast_handle->m_serverSock;
    m_pollItems[0].events = ZMQ_POLLIN;
    m_pollItems[1].socket = webmast_handle->m_sch_socket_recv;
    m_pollItems[1].events = ZMQ_POLLIN;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , NULL); 

    while(1)
    {
        ret = zmq_poll(m_pollItems, 2, -1);

        if(m_pollItems[0].revents & ZMQ_POLLIN)
        {
            recv_len = recv(webmast_handle->m_serverSock, recv_buf, 64, MSG_NOSIGNAL);
                if(recv_len <= 0)
                {
                    //close(master_instep_handle->m_serverSock);
                    logm_debug("recv from webmast failed so close socket\n");
                    break;
                }
                else if(recv_len >= 2)
                {
                    logm_debug("recv data from webmast :");
                    logm_debug_buffer(recv_buf,recv_len);
                
                    ret = zmq_send(webmast_handle->m_sch_socket_send, recv_buf, recv_len, ZMQ_DONTWAIT);
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
                    logm_debug("recv data from webmast :");
                    logm_debug_buffer(recv_buf,recv_len);
                }
        }

        if(m_pollItems[1].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(webmast_handle->m_sch_socket_recv, recv_buf, 64, ZMQ_DONTWAIT);
            if(recv_len > 0)
            {
                webmast_handle->get_Temperature_Infor();
                memcpy(&recv_buf[recv_len], webmast_handle->m_controlTemperature, 2);
                for(i = 0; i < webmast_handle->m_antennaNum; i++)
                {
                    memcpy(&rfs_temp[i * 2], webmast_handle->m_antInfor[i].rf_Temperature, 2);
                }
                memcpy(&recv_buf[recv_len + 2], rfs_temp, webmast_handle->m_antennaNum *2);
                ret = send(webmast_handle->m_serverSock, recv_buf, recv_len + 2 + webmast_handle->m_antennaNum *2, MSG_NOSIGNAL);
                if(ret < 0)
                {
                    logm_debug("send data to webmast failed!\n");
                }
                else
                {
                    logm_debug("send data to webmast :");
                    logm_debug_buffer(recv_buf,recv_len + 2 + webmast_handle->m_antennaNum *2);
                }
            }
        }
    }

    close((int)webmast_handle->m_serverSock);  
    logm_debug("recv thread_exit\n");
    return (void *)0;

}




void read_local_temp(char *tem_buff)
{
    unsigned int ret;
    signed char value;
    int temperature;
    int j;

    bsp_epld_init();

    ret = bsp_i2c_init();
    if (0 != ret)
    {
        logm_debug("tsensor i2c init fail! errcode = %x\r\n", ret);
        tem_buff[0] = '\0';
        return;
    }
    else
    {
        ret = bsp_tsensor_init();
		if(ret != 0)
		{
		    logm_debug("tsensor init failed! errcode = %x\r\n", ret);
            tem_buff[0] = '\0';
            return;
	    }
    }

    ret = bsp_tsensor_read_local_temp((unsigned char *)&value);
    if(0 != ret)
    {
        logm_debug("bsp_tsensor_read_local_temp fail! ret is %08x \n", ret);
        tem_buff[0] = '\0';
    }
    else
    {
        temperature = value;
        logm_debug("control Temperature %d \n", temperature);        
        //sprintf(tem_buff, "%x", temperature);
        for(j=0;j<2;j++)
	    {
		    tem_buff[1 - j]=((temperature>>(8*j))&0xff);
	    }
    }
}

void web_mast::get_Temperature_Infor()
{
    /* read control local temperature */
    memset(m_controlTemperature, 0, 2);
    read_local_temp(m_controlTemperature);   

    /* read antenna temperature */
    read_Ant_Temperature();

}

void web_mast::read_Ant_Temperature()
{    
    unsigned char cmd_req[8] = {0};
    unsigned char recv_ack[8] = {0};
    int value, ret, temp, j;
    unsigned int device_type, device_action;


        /*************** init device ******************/
    for(int i = 0; i < m_antennaNum; i++)
    {    
        device_type = DEVICE_TYPE_SENSOR;
        device_action = DEVICE_ACTION_INIT;
        memcpy(&cmd_req[0], &device_type, 4);
        memcpy(&cmd_req[4], &device_action, 4);
        zmq_send(m_antInfor[i].proxy_req_sock, (char *)cmd_req, sizeof(cmd_req), 0);
        ret = zmq_recv(m_antInfor[i].proxy_req_sock, (char *)recv_ack, sizeof(recv_ack), 0);
        if((ret <= 0) || (htonl(*((unsigned int *)&recv_ack)) != 0))
        {
            logm_debug("Antenna temperature_sensor init failed\n");
            temp = 0;            
        }
        else
        {
            /************ Read temperature *****************/
            device_type = DEVICE_TYPE_SENSOR;
            device_action = ACTION_READ_LOCAL_TEMP;
            memcpy(&cmd_req[0], &device_type, 4);
            memcpy(&cmd_req[4], &device_action, 4);
            zmq_send(m_antInfor[i].proxy_req_sock, (char *)cmd_req, sizeof(cmd_req), 0);
            ret = zmq_recv(m_antInfor[i].proxy_req_sock, (char *)recv_ack, sizeof(recv_ack), 0);
            if((ret > 0) && (htonl(*((unsigned int *)&recv_ack)) == 0))
            {
                temp = htonl(*((unsigned int *)&recv_ack[4]));
                logm_debug("Antenna temperature %d\n", temp);
            }
            else
            {
                temp = 0;                
                logm_debug("Antenna get temperature Failed %d\n", ret);
            }
        }
        //sprintf(rf_Temperature, "%2d", temp);
        for(j=0;j<2;j++)
	    {
		    m_antInfor[i].rf_Temperature[1 - j]=((temp>>(8*j))&0xff);
	    }

    }

}



web_mast::web_mast()
{
	m_ctx = NULL;
	m_control_sync_comm_type = 0;
    recv_thread_exist_flag = 0;

}

webmast_config::webmast_config()
{
    int i = 0;
}


void webmast_config::LoadBaseInforConfig()
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

    /* parse config File to jsonConfig */
    parseRet = reader.parse(configfile, jsonConfig, false);
    if(!parseRet) 
	{
        logm_err("parse config file fail\n");
        configfile.close();
        return;
    }

    if(jsonConfig.isMember("psamconfig")) 
    {
        Json::Value psam;
        Psam_Para *psamPara;

        for(int i = 0; i < jsonConfig["psamconfig"].size(); ++i)
        {
            psam = jsonConfig["psamconfig"][i];
            if(psam.isMember("psamid") && psam.isMember("enable") && psam.isMember("type"))
            {
                if(psam["enable"].asBool())
                {
                    psamPara = new Psam_Para();
                    psamPara->psam_id = psam["psamid"].asInt();
                    psamPara->psam_isEnable = psam["enable"].asBool();
                    psamPara->config_type = psam["type"].asInt();
                    
                    m_psamConfig.push_back(psamPara);
                    logm_debug("psam %d %d %d\n", psamPara->psam_id, 
                            psamPara->psam_isEnable, psamPara->config_type);
                }                
            }
        }
    }

    if(jsonConfig.isMember("rfconfig")) 
    {
        Json::Value rf;
        Rf_Para *rfPara;

        for(int i = 0; i < jsonConfig["rfconfig"].size(); ++i) 
        {
            rf = jsonConfig["rfconfig"][i];

            if(rf.isMember("rfsn") && rf.isMember("enable") && rf.isMember("addr"))
            {
                if(rf["enable"].asBool())
                {
                    rfPara = new Rf_Para();
                    rfPara->rfsn = rf["rfsn"].asInt();
                    rfPara->rf_isEnable = rf["enable"].asBool();                
                    strcpy(rfPara->rf_ipaddr, rf["addr"].asCString());
                    m_rfConfig.push_back(rfPara);
                    logm_debug("rf %d %d %s \n", rfPara->rfsn, rfPara->rf_isEnable, rfPara->rf_ipaddr);
                }
            }     
        }
    }

    configfile.close();    
}


int main(int argc, char *argv[])
{
	// register mbm to logm, and set debug_infor to display jiffies
	init_jiffs(); 
	init_logm("webmast");
	set_timeflag();

	web_mast web_Mast;
	web_Mast.init();
	web_Mast.run();

    return 0;
}