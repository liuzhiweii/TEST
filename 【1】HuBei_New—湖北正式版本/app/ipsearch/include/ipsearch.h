#ifndef __IPSEARCH__
#define __IPSEARCH__

#define	MULTICAST_SEARCH  0
#define	MULTICAST_ACK     1  
#define	MULTICAST_PORT    12345  
#define MULTICAST_GROUP   "225.0.0.77"  
#define MSGBUFSIZE        256  
#define ABNORMAL 		  1
#define ERR               0xffff
typedef struct deviceIP
{
	char IP[24];
}deviceIP_t;

typedef struct multicast
{
	int messageID;	
}multicast_t;


#if ABNORMAL
#define abnormal_print(format,args...)\
    do\
    {\
        printf("[%d]"format,__LINE__,## args);\
        fflush(stdout);\
    }while(0)
#else
#define abnormal_print(format,args...)
#endif 

#endif
