#ifndef __REPORTER__
#define __REPORTER__

#include "scheduler.pb.h"
using namespace scheduler;


class Reporter
{
public:
	Reporter();
	void init(void);
	void run(void);	
	void processTagReport(void);	
	void reconnectServer(void);	
	void getServerIp(void);	
	int sendReportToServer(unsigned char *send_buffer, unsigned int send_len);
private:
	void *m_ctx;
	void *m_pullSock;
	int m_timerSock;
	int m_serverSock;
	char m_serverIp[24];
	int m_serverPort;
};



#endif



