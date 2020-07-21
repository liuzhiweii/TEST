#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <time.h>  
#include <string.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <sys/ioctl.h>
#include <net/if.h>
#include <ifaddrs.h>
#include "ipsearch.h"
#include <errno.h>

char localIP[24];

int initSendAddr(struct sockaddr_in *addr)
{
    memset(addr,0,sizeof(struct sockaddr_in));  
    addr->sin_family      = AF_INET;  
    addr->sin_addr.s_addr = inet_addr(MULTICAST_GROUP);  
    addr->sin_port        = htons(MULTICAST_PORT);		
	return 0;
}

int initRecvAddr(struct sockaddr_in *addr)
{
    memset(addr,0,sizeof(struct sockaddr_in));  
    addr->sin_family      = AF_INET;  
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port        = htons(MULTICAST_PORT);		
	return 0;
}

int createSendFd(void)
{  
    int fd; 
	int iLoop = 0;
    if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)   
    {  
        abnormal_print("socket errno= %d\n",errno);   
    }	
	if (setsockopt(fd,IPPROTO_IP,IP_MULTICAST_LOOP,(const char *)&iLoop,sizeof(iLoop)) < 0)
	{
		abnormal_print("setsockopt errno= %d\n",errno);  
	}	
	return fd;	
}

int createRecvFd(struct sockaddr_in *addr)
{  
    int              fd; 
	struct   ip_mreq mreq;	
	unsigned int     on   = 1; 
	char ip[24];
    if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)   
    {  
        abnormal_print("socket errno= %d\n",errno);   
    }  
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) < 0)   
    {  
        abnormal_print("reusing addr failed errno= %d\n",errno);    
    }
	if (bind(fd,(struct sockaddr *)addr,sizeof(struct sockaddr_in)) < 0)  
    {  
        abnormal_print("bind errno= %d\n",errno);   
    } 	
	
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);  
    mreq.imr_interface.s_addr = inet_addr(localIP);
	
    if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)   
    {  
        abnormal_print("setsockopt errno= %d\n",errno);  
    }	

	return fd;	
}

unsigned int call_sh_script(char *cmd)
{
	 pid_t status; 
	
	status = system(cmd);  
    if (-1 == status)  
    {      	
		return ERR;
    }  
	else  
	{    
	    if (WIFEXITED(status))  
	    {  
	        if (0 != WEXITSTATUS(status))  
	        {  
				return ERR;
	        }  
	    }  
	    else  
	    {
			return ERR;
	    }  
	} 	
	return 0;
}

void addRoute(int netCardNum)
{
	char  cmdbuf[128];
	int   ret;
	int   fd;

	if(netCardNum > 2)
	{
		sprintf(cmdbuf,"route add -net 224.0.0.0 netmask 224.0.0.0 dev eth1");
	}
	else
	{
		sprintf(cmdbuf,"route add -net 224.0.0.0 netmask 224.0.0.0 dev eth0");
	}	

	ret = call_sh_script(cmdbuf);

	if(ret != 0)
	{
		abnormal_print("set route error\n");
	}	

	sleep(2);//wait 2s for route become effective
	
}

int getLocalNetCardNum(void)
{
	int           interfaceNum = 0;
	int           fd;
	struct ifreq  buf[16];
	struct ifconf ifc;	
	
    if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)   
    {  
        abnormal_print("socket errno= %d\n",errno);   
    } 	
	
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t)buf;
	
	if(0 > (ioctl(fd, SIOCGIFCONF, (char *)&ifc)))
	{
		abnormal_print("getifaddrs errno= %d\n" ,errno);	   
	}
	else
	{
		interfaceNum = ifc.ifc_len / sizeof(struct ifreq);
	}
	return interfaceNum;
}

void getLocalIP(char *ip, int netCardNum) 
{
    struct ifaddrs *ifAddrStruct;
    void           *tmpAddrPtr=NULL;
	char            tmpIp[24];
	char            netCardName[24];

	if(netCardNum > 2)
	{
		strcpy(netCardName, "eth1");
	}
	else
	{
		strcpy(netCardName, "eth0");
	}	
	
    if(0 != (getifaddrs(&ifAddrStruct)))
    {
    	abnormal_print("getifaddrs errno= %d\n",errno);
    }
	
    while (ifAddrStruct != NULL) 
	{
        if (ifAddrStruct->ifa_addr->sa_family==AF_INET) 
		{
            tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, tmpIp, INET_ADDRSTRLEN);
			if(!strcmp(netCardName,ifAddrStruct->ifa_name))
			{
				strcpy(ip,tmpIp);
			}           
        }
        ifAddrStruct=ifAddrStruct->ifa_next;
    }	
    freeifaddrs(ifAddrStruct);
	
}

void sendLocalIP(int sendFd, struct sockaddr *sendAddr, char *buf)
{
	multicast_t    *pMulticast;
	deviceIP_t     *pDeviceIPInfo;
	
	pMulticast            = (multicast_t *)buf;
	pDeviceIPInfo         = (deviceIP_t *)(buf + sizeof(multicast_t));
	pMulticast->messageID = MULTICAST_ACK;
	
	strcpy(pDeviceIPInfo->IP,localIP);
	
    if (sendto(sendFd, buf, sizeof(multicast_t) + sizeof(deviceIP_t), 0, sendAddr, sizeof(*sendAddr)) < 0)   
    {  
        abnormal_print("sendto errno= %d\n",errno);  
    }
}

void process(int recvFd, struct sockaddr *recvAddr, int sendFd, struct sockaddr *sendAddr, char *sendBuf)
{	
	char           recvBuf[MSGBUFSIZE];
	int            addrlen;
	multicast_t   *pMulticast;
	deviceIP_t    *pDeviceIPInfo;
	int            ret;
	struct ip_mreq mreq;  
	ssize_t        nbytes;
	fd_set         readFds;

	addrlen = sizeof(struct sockaddr_in);

	while (1)
	{
		FD_ZERO(&readFds);
		FD_SET(recvFd,&readFds);
		ret = select(recvFd+1,&readFds,NULL,NULL,0);
		if(0 >= ret)
		{
		    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);  
		    mreq.imr_interface.s_addr = inet_addr(localIP);			
		    if (setsockopt(recvFd,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)   
		    {  
		        abnormal_print("setsockopt errno= %d\n",errno);  
		    }		
			if (setsockopt(recvFd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)   
		    {  
		        abnormal_print("setsockopt errno= %d\n",errno);  
		    }
			continue;
		}
		else
		{
			if((nbytes = recvfrom(recvFd,recvBuf,MSGBUFSIZE,0,recvAddr,&addrlen))<0)
			{
				abnormal_print("recvfrom nbytes=%d errno =%d addrlen =%d\n",nbytes,errno,addrlen);	
			}
			pMulticast = (multicast_t *)recvBuf;			
			if(MULTICAST_SEARCH == pMulticast->messageID)
			{
				sendLocalIP(sendFd, sendAddr, sendBuf);
			}		
		}
	}
	
}

int main(void)
{
	struct sockaddr_in sendAddr,recvAddr;
	int                sendFd,recvFd;
	char               sendBuf[24];
	int                netCardNum;
	
	sleep(2); //wait 2s for vmm set eth0 	
	netCardNum = getLocalNetCardNum();
	getLocalIP(localIP,netCardNum);
	addRoute(netCardNum);
	initSendAddr(&sendAddr);
	initRecvAddr(&recvAddr);	
	sendFd = createSendFd();
	recvFd = createRecvFd(&recvAddr);	
	process(recvFd, (struct sockaddr *)(&recvAddr), sendFd, (struct sockaddr *)(&sendAddr), sendBuf);

	return 0;
}

