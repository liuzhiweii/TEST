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
#include <list>
#include <fstream>
#include <json/json.h>
#include "etc_codec_cq.h"
#include "logm.h"
#include "linkcache.h"
#include "comm_multipath_report.h"
#include "etc_codec_ff.h"
#include "utimer.h"
#include "jiffs.h"


#define MULTIPATH_SERVER_PORT   3010

using namespace std;

ReportBuffer::ReportBuffer(unsigned char *bp, unsigned int bl)
{
    m_bl = bl;
    m_bp = new unsigned char[bl];
    memcpy(m_bp, bp, bl);

    m_macid = (bp[12]<<24)|(bp[13]<<16)|(bp[14]<<8)|bp[15];

    #if 0
    if(bp[25] >= 0xa0) {
        m_macid = (bp[25]<<24)|(bp[26]<<16)|(bp[27]<<8)|bp[28];
    } else {
        m_macid = (bp[46]<<24)|(bp[47]<<16)|(bp[48]<<8)|bp[49];
    }
    #endif
}

ReportBuffer::~ReportBuffer()
{
    delete m_bp;
}




BadReportCache::BadReportCache()
{
}


void BadReportCache::pushReport(ReportBuffer * report, long Oldjiffies)
{
    logm_debug("pushReport macid: %08x \n",  report->m_macid);
    if (0 == Oldjiffies)
    {
        report->m_jiffies = get_jiffies();
    }
    else
    {
        report->m_jiffies = Oldjiffies;
    }
    m_badReportList.push_back(report);
}


ReportBuffer *BadReportCache::popReport(void)
{
    ReportBuffer *report;
    std::list<ReportBuffer *>::iterator iter;

    for(iter=m_badReportList.begin(); iter!=m_badReportList.end(); ++iter) {
        report = *iter;
        if(timeOk(report->m_jiffies, 30*1000)) {
            m_badReportList.erase(iter);
            logm_debug("popReport macid: %08x \n",  report->m_macid);
            return report;
        }
    }

    return NULL;

}


int BadReportCache::size()
{
    return m_badReportList.size();
}

void BadReportCache::eraseReport(unsigned int macid, void* pPara, long *pOldjiffies)
{
    ReportBuffer *report;
    std::list<ReportBuffer *>::iterator iter;
    int ret = 0;
    CommMultipathReport* pCommMultipathReport = pPara;

    for(iter=m_badReportList.begin(); iter!=m_badReportList.end();) 
    {
        report = *iter;
        if((report->m_macid == macid)
           && (!timeOk(report->m_jiffies,30*1000))) 
        {
            *pOldjiffies = report->m_jiffies;
            logm_debug("bad report eraseReport macid: %08x \n",  report->m_macid);
            m_badReportList.erase(iter++);
            delete report;
        }
        else
        {
            if (timeOk(report->m_jiffies,30*1000))
            {
                pthread_mutex_lock(&(pCommMultipathReport->m_mutex));
                logm_debug("cache bad Data macid:%08x\n", macid);
                ret = pCommMultipathReport->m_linkCache->cacheData(report->m_bp, report->m_bl);
                pthread_mutex_unlock(&(pCommMultipathReport->m_mutex));
                if (0 != ret)
                {
                    logm_debug("cache bad Data ret:%d\n", macid,ret);
                    ++iter;
                }
                else
                {
                    m_badReportList.erase(iter++);
                    delete report;  
                }
            }
            else
            {
                ++iter;
            }
        }
    }

    return;
}

void BadReportCache::eraseReport(unsigned int macid, void* pPara)
{
    ReportBuffer *report;
    std::list<ReportBuffer *>::iterator iter;
    int ret = 0;
    CommMultipathReport* pCommMultipathReport = pPara;

    for(iter=m_badReportList.begin(); iter!=m_badReportList.end();) 
    {
        report = *iter;
        if(report->m_macid == macid) 
        {
            logm_debug("good report eraseReport macid: %08x \n",  report->m_macid);
            m_badReportList.erase(iter++);
            delete report;
        }
        else
        {
            if (timeOk(report->m_jiffies,30*1000))
            {
                pthread_mutex_lock(&(pCommMultipathReport->m_mutex));
                logm_debug("cache bad Data macid:%08x\n", macid);
                ret = pCommMultipathReport->m_linkCache->cacheData(report->m_bp, report->m_bl);
                pthread_mutex_unlock(&(pCommMultipathReport->m_mutex));
                if (0 != ret)
                {
                    logm_debug("cache bad Data ret:%d\n", macid,ret);
                    ++iter;
                }
                else
                {
                    m_badReportList.erase(iter++);
                    delete report;  
                }
            }
            else
            {
                ++iter;
            }
        }
    }

    return;
}


CommMultipathReport::CommMultipathReport()
{
    m_ctx = NULL;
    m_reportsock = NULL;
    m_linksock = -1;
    m_timersock = -1;
    m_poll_num = 2;
    m_badReportCache = new BadReportCache();

    return;
}

void CommMultipathReport::initEnv()
{
    int ret;


    m_ctx = zmq_init(1);
    if (NULL == m_ctx) {
        logm_err("create context fail!\n");
        exit(-1);
    }


    m_reportsock = zmq_socket(m_ctx, ZMQ_PULL);
    if(NULL == m_reportsock) {
        logm_debug("create PULL  sock fail!\n");
        exit(-1);
    }

    ret = zmq_bind(m_reportsock, "tcp://*:5080");
    if(ret < 0) {
        logm_debug("bind PULL  sock fail!\n");
        exit(-1);
    }



    m_timersock = init_timer();

	m_linkCache = new LinkCache();		
	m_linkCache->connectDb();

    return;
}


void CommMultipathReport::loadConfig()
{
    ifstream configfile;
    Json::Reader reader;
    Json::Value jsonConfig;
    bool parseRet;

    configfile.open("/opt/bin/scheduler.json");
    if(!configfile.is_open()) {
        logm_err("open config file fail\n");
        return;
    }

    parseRet = reader.parse(configfile, jsonConfig, false);
    if(!parseRet) {
        logm_err("parse config file fail\n");
        configfile.close();
        return;
    }

    if(jsonConfig.isMember("server")) {
        if(jsonConfig["server"].isMember("ip")) {
            memset(m_serverip, 0 ,24);
            memcpy(m_serverip, jsonConfig["server"]["ip"].asCString(), 24);
        }
    }

    configfile.close();
    logm_debug("load_config success serverip %s\n", m_serverip);

    return;
}

int CommMultipathReport::connectServer()
{
    int ret;

    m_linksock = socket(AF_INET, SOCK_STREAM, 0);
    if(m_linksock < 0) {
        logm_debug("creat m_linksock socket fail!\n");
        return -1;
    }

    struct timeval timeout;
    struct sockaddr_in serv_addr;

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(m_linksock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    setsockopt(m_linksock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_serverip);
    serv_addr.sin_port = htons(10240);

    ret = connect(m_linksock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0) {
        logm_info("connect to server %s fail \n", m_serverip);
        close(m_linksock);
        return ret;
    } else {
        logm_info("connect to server %s success \n", m_serverip);
        return m_linksock;
    }
}


void CommMultipathReport::recvReport()
{
    int recv_len;
    unsigned char recv_buffer[1024];
    int ret;
    ReportBuffer *report;
    unsigned int macid = 0;
    long Oldjiffies = 0;

    recv_len = zmq_recv(m_reportsock, &recv_buffer[1], 1024,0);
    if(recv_len > 0) 
    {
        recv_buffer[0] = 0x8d;
        logm_debug("pullsock<-");
        logm_debug_buffer(recv_buffer,recv_len+1);

        if(recv_buffer[1] != 0) 
        {
            if(m_badReportCache->size() < 1000) 
            {
                Oldjiffies = 0;
                report = new ReportBuffer(recv_buffer, recv_len+1);
                m_badReportCache->eraseReport(report->m_macid, (void *)this, &Oldjiffies);
                m_badReportCache->pushReport(report, Oldjiffies);
                logm_debug("cache bad report macid:%08x\n", report->m_macid);
            }
        } 
        else  
        {
            macid = getMacId(recv_buffer);
            pthread_mutex_lock(&m_mutex);
            logm_debug("cache good Data macid:%08x\n", macid);
            ret = m_linkCache->cacheData(recv_buffer, recv_len+1);
            pthread_mutex_unlock(&m_mutex);
            if (0 != ret)
            {                
                logm_debug("cache good report macid:%08x\n,cacheData ret:%d", macid,ret);
            }
            m_badReportCache->eraseReport(macid, (void *)this);
        }
    } 
    else 
    {
        logm_err("recv from m_reportsock error %d \n", recv_len);
    }

    return;
}

int CommMultipathReport::rawSendReport(unsigned char *pdata, unsigned char len)
{
    unsigned char *encoded_frame;
    unsigned int encoded_len;
    int write_len;
    int recv_len;
    unsigned char recv_buffer[256];
    unsigned int macid;

    if(m_linksock > 0) 
    {
        encoded_frame = etc_encode_ff(pdata, len, &encoded_len);
        write_len = write(m_linksock, encoded_frame, encoded_len);
        if(write_len <= 0) {
            close(m_linksock);
            logm_err("write to pc error \n");
            m_linksock = -1;
            goto FAIL;
        }

        recv_len = read(m_linksock, recv_buffer, 256);
        if(recv_len < 0) {
            close(m_linksock);
            logm_err("read from pc error %d\n", recv_len);
            m_linksock =-1;
            goto FAIL;
        }
        macid = getMacId(pdata);
		logm_debug("rawSendReport macid:%08x success\n", macid);     
        return 0;
    }
FAIL:
    return 1;
}

void sendReport(void *arg)
{
    int ret;
	unsigned char buffer[256];
    unsigned int bufferLen;    
    CommMultipathReport *pCommMultipathReport = arg;   

    while(1)
    {
        if(pCommMultipathReport->m_linksock > 0) 
        {
            pthread_mutex_lock(&(pCommMultipathReport->m_mutex));
            ret = pCommMultipathReport->m_linkCache->getData(buffer, &bufferLen);
            pthread_mutex_unlock(&(pCommMultipathReport->m_mutex));
            logm_debug("restoreData ret:%d\n",ret);
            if (0 == ret)
            {
                ret = pCommMultipathReport->rawSendReport(buffer, bufferLen);
                if (0 != ret)
                {
                    logm_debug("send report fail ret:%d\n",ret);
                    pthread_mutex_lock(&(pCommMultipathReport->m_mutex));
                    ret = pCommMultipathReport->m_linkCache->cacheData(buffer, bufferLen);
                    pthread_mutex_unlock(&(pCommMultipathReport->m_mutex));
                    if (0 != ret)
                    {                
                        logm_debug("cache send fail report err ret:%d",ret);
                    }
                }
            }
            else if (1 == ret)
            {
                logm_debug("the last frame\n");
                pthread_mutex_lock(&(pCommMultipathReport->m_mutex));
                pCommMultipathReport->m_linkCache->removeDb();
                pCommMultipathReport->m_linkCache->closeDb();
                pCommMultipathReport->m_linkCache->connectDb();   
                pthread_mutex_unlock(&(pCommMultipathReport->m_mutex));
                sleep(2);
            }
            else
            {
                logm_debug("get tag from db failed\n");
                sleep(10);
            }
        }
        else
        {
            sleep(5);
        }
    }

    return;
}

unsigned int CommMultipathReport::getMacId(unsigned char* pdata)
{
    unsigned int macid = 0;

    macid = (pdata[12]<<24)|(pdata[13]<<16)|(pdata[14]<<8)|pdata[15];

    #if 0
    if(pdata[25] >= 0xa0) {
        macid = (pdata[25]<<24)|(pdata[26]<<16)|(pdata[27]<<8)|pdata[28];
    } else {
        macid = (pdata[46]<<24)|(pdata[47]<<16)|(pdata[48]<<8)|pdata[49];
    }
    #endif

    return macid;
}

void CommMultipathReport::run()
{
    int ret;
    int poll_num = 2;
    unsigned int timer_id;
    pthread_t sendReport_id;

    memset(m_pollItems, 0, (sizeof(zmq_pollitem_t) * 2));
    m_pollItems[REPORT_SOCK].socket = m_reportsock;
    m_pollItems[REPORT_SOCK].events = ZMQ_POLLIN;
    m_pollItems[TIMER_SOCK].socket = NULL;
    m_pollItems[TIMER_SOCK].fd = m_timersock;
    m_pollItems[TIMER_SOCK].events = ZMQ_POLLIN;

    set_timer(1, 2, 0, TIMER_PERSIST);

    if(pthread_mutex_init(&m_mutex, NULL) < 0)  
    {
        logm_debug("Create pthread mutex init error!n");
    }

    ret = pthread_create(&sendReport_id, NULL, (void *)sendReport, (void *)this);
    if(0 != ret)
    {
        logm_debug("Create send report pthread error!n");
    }

    while(1) {
        ret = zmq_poll(m_pollItems, 2, -1);
        logm_debug("zmq_poll  return %d \n", ret);

        if(m_pollItems[REPORT_SOCK].revents & ZMQ_POLLIN) {
            logm_debug("recvReport \n");
            recvReport();
        }

        if(m_pollItems[TIMER_SOCK].revents & ZMQ_POLLIN) {
            logm_debug("timer event occur\n");
            read(m_timersock, &timer_id, sizeof(int));
            if(m_linksock < 0) {
                m_linksock = connectServer();
            }
        }

       //sendReport();
    }
}


int main(int argc, char *argv[])
{
    CommMultipathReport inst;

    init_jiffs();
    init_logm("comm");

    logm_debug("comm_report start run \n");

    inst.loadConfig();
    inst.initEnv();
    inst.run();

    return 0;
}



