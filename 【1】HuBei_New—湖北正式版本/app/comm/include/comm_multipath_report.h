#ifndef __COMM_MULTIPATH__
#define __COMM_MULTIPATH__


#define REPORT_SOCK 0
#define LINK_SOCK 1
#define TIMER_SOCK 1


using namespace std;


#define timeOk(before, cycle) (((long)(get_jiffies()) - (long)before) >= cycle)


class ReportBuffer
{
public:
	ReportBuffer(unsigned char *bp, unsigned int bl);
	~ReportBuffer();
	
	unsigned char *m_bp;
	unsigned int m_bl;
	unsigned int m_macid;
	long m_jiffies;
};

class BadReportCache
{
public:
	BadReportCache();
	void pushReport(ReportBuffer * report, long Oldjiffies);
	ReportBuffer *popReport(void);
	bool empty();
	int size();	
	void eraseReport(unsigned int macid, void* pPara, long *pOldjiffies);
	void BadReportCache::eraseReport(unsigned int macid, void* pPara);

private:
	std::list<ReportBuffer *> m_badReportList;
};

class CommMultipathReport
{
public:
	CommMultipathReport();
	void initEnv();
	void run(void);	
	void loadConfig();	
	int connectServer();
	void recvReport();		
	int rawSendReport(unsigned char *pdata, unsigned char len);
	int m_linksock;
	LinkCache *m_linkCache;
	pthread_mutex_t m_mutex;	
private:
	void *m_ctx;
	void *m_reportsock;
	int m_timersock;
	zmq_pollitem_t m_pollItems[2];
	int m_poll_num;	
	char m_serverip[32];
	std::list<ReportBuffer *> m_reportBufferList;
	BadReportCache *m_badReportCache;
	unsigned int getMacId(unsigned char* pdata);	
};

void sendReport(void *arg);  

#endif



