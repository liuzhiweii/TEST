#ifndef _CFG_H
#define _CFG_H



/* 消息队列操作宏定义 */
#define CFG_SEND_MSG(socket,msg,len)   zmq_send (socket, msg, len, 0);

/* 配置文件路径 */
//#define CFG_CONFIG_FILE     "/mnt/config/config.txt"
//#define CFG_DEFAULT_CONFIG_FILE     "/version/data/defaultConfig.txt"

#define CFG_CONFIG_FILE        "/opt/config.txt"
#define CFG_DEFAULT_CONFIG_FILE     "/etc/defaultConfig.txt"



/* 关键字的最大长度 */
#define CFG_MAX_NAME_LEN     (1023)
#define CFG_MAX_MSG_LEN                 (16 * 1024)




#define EEPROM_EPC_ADDR             (0x000)
#define EEPROM_MAC_ADDR             (0x010)


#define EEPROM_COMMUNICATION_MODE_ADDR              (0x024)
#define EEPROM_IP_CONFIG_ADDR              (0x025)

#define EEPROM_IP_ADDR              (0x027)
#define EEPROM_NETMASK_ADDR              (0x0x2b)
#define EEPROM_GATEWAY_ADDR              (0x02f)


#define EEPROM_MWIP_ADDR              (0x087)







#ifdef CFG_ETC
#define CHECK_CFG(x) check_etc_config(x)
#elif defined CFG_UHF
#define CHECK_CFG(x) check_uhf_config(x)
#else
#define CHECK_CFG(x) 0
#endif


#define CFG_DEBUG logm_debug
#define CHECK_NONZERO_NUMBER(p)                               \
do\
{\
    if(0!=(p))                                 \
    {                                             \
       CFG_DEBUG("nonzero error file:%s line:%u\r\n",__FILE__,__LINE__);\
       return -1;                                 \
    }\
}while(0)


#define CHECK_NULL_POINTER_RETURN_INT(p)\
do\
{\
    if(NULL==(p))                                 \
    {                                             \
       CFG_DEBUG("null pointer error file:%s line:%u\r\n",__FILE__,__LINE__);\
       abn_debug("null pointer error \r\n");     \
       return -1;                                 \
    }\
}while(0)


#define CHECK_NULL_POINTER_RETURN_VOID(p)\
    do\
    {\
        if(NULL==(p))                                 \
        {                                             \
           CFG_DEBUG("null pointer error file:%s line:%u\r\n",__FILE__,__LINE__);\
           abn_debug("null pointer error\r\n");\
           return ;                                 \
        }\
    }while(0)



#define CHECK_FAIL_NUMBER(p,s)                               \
do\
{\
    if((p)<0)                                 \
    {                                             \
       CFG_DEBUG("%s errno:%d file:%s line:%u\r\n",s,errno,__FILE__,__LINE__);\
       abn_debug("%s errno:%d \r\n",s,errno);\
       exit(-1);                                 \
    }\
}while(0)


typedef void ( * deal_cfg_msg )(const char *);

/*接收 消息表结构 */
typedef struct tag_msg_func_t
{
    const char               type[24];                       /* 消息ID */
    const char               action[12];                       /* 消息ID */
    deal_cfg_msg                msg_func;
}msg_func_t;


/* nvram数据结构 */
#pragma pack(1)
typedef struct tag_cfg_eeprom_t
{   
    //unsigned short            reader_id;                  /* 阅读器ID */
    unsigned char             comm_mode;                 /* 通信模式 */
	unsigned short             ip_config;              /**/
    unsigned int              ip_addr;                /* 阅读器IP地址 */
    unsigned int              netmask;                  /* 阅读器子网掩码 */
    unsigned int              gateway;                 /* 网关1 */
    unsigned int              dns;                     /* DNS1 */
    unsigned int              ip_addr2;                /* 阅读器IP地址 */
    unsigned int              netmask2;                  /* 阅读器子网掩码 */
    unsigned int              gateway2;                 /* 网关1 */
    unsigned int              dns2;                     /* DNS1 */                    /* DNS2 */
}cfg_eeprom_t;
#pragma pack()




 void set_inner_config(const char *content);
 void get_inner_config(const char *content);
 void save_inner_config(const char *content);
 void restore_factory_defaults(const char *content);
 void deal_comm_request_config(const char *content);
 void deal_uhf_request_config(const char *content); 
 void deal_rfs_request_config(const char *content); 
 void deal_rfs_change_request_config(const char *content);
 void deal_dispatch_request_config(const char *content);
 void deal_client_get_config(const char *content);
 void deal_client_set_config(const char *content);
 void get_client_comm_config(const char *content);
 void set_client_comm_config(const char *content);
 void get_client_business_config(const char *content);
 void set_client_business_config(const char *content);
 void reset_reader(const char *content);
 void restore_factory_defaults(const char *content);
 void deal_cmm_keepalive_msg(const char *content);

#endif 
/*  */

