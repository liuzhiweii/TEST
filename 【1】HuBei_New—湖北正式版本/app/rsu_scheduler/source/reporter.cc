
#include <stdlib.h>
#include "zmq.h"
#include "logm.h"
#include "reporter.h"
#include "utimer.h"

using namespace std;



Reporter::Reporter()
{
}


void Reporter::getServerIp()
{
	strcpy(m_serverIp, "192.168.2.180");
	m_serverPort = 5050;
	
}

void Reporter::init(void)
{
    m_ctx = zmq_init(1);
    assert(m_ctx);

    m_pullSock = zmq_socket(m_ctx, ZMQ_PULL);
    assert(m_pullSock);
    zmq_connect(m_pullSock, "tcp://127.0.0.1:6820");

    m_timerSock = init_timer();
    getServerIp();

    #if 0
	m_serverSock= socket(AF_INET, SOCK_STREAM, 0);
	if(m_serverSock < 0)
	{
		logm_debug("creat  m_serverSock fail!\n");
		exit(-1);
	}
	#endif
			


    
    


    return;
}

int Reporter::sendReportToServer(unsigned char *send_buffer, unsigned int send_len)
{
	int ret;

}

void Reporter::processTagReport(void)
{
	int recv_len;
    unsigned char recv_buf[8192];
    int send_len;

    recv_len = zmq_recv(m_pullSock, recv_buf, sizeof(recv_buf), 0);
    if (recv_len <= 0) return;

    sendReportToServer(recv_buf, recv_len);

    return;
}


void Reporter::reconnectServer(void)
{
	
}





void Reporter::run(void)
{
    int ret;
    zmq_pollitem_t  items[2];
    memset(items, 0, (sizeof(zmq_pollitem_t)*2));

    items[0].socket = m_pullSock;
    items[0].events = ZMQ_POLLIN;
    items[1].socket = NULL;
    items[1].fd = m_timerSock;
    items[1].events = ZMQ_POLLIN;

    while(1)
    {
        ret = zmq_poll(&items[0], 2, -1);
        logm_debug("zmq_poll return , return %d \n", ret);

        if(items[0].revents & ZMQ_POLLIN)
        {
        	processTagReport();
        }
        else if(items[0].revents & ZMQ_POLLIN)
        {
        	reconnectServer();
        }


    }
}



int main(int argc, char *argv[])
{
    Reporter reporter;


    reporter.init();
    reporter.run();

    return 0;
}



