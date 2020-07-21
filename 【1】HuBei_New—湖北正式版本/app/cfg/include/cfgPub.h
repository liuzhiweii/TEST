#ifndef CFG_PUB_H
#define CFG_PUB_H

#include "cfg.h"
#include "cfgCapabilities.h"
#include "parson.h"
#include "logm.h"
#include "abn.h" 


/*阅读器ip配置*/
typedef struct tag_ipv4_t
{
    unsigned int                          ip_config;        /*是否使用dhcp分配地址,0表示不用,1表示使用*/ 
    unsigned int                          ip_addr;  /*阅读器ip地址*/
    unsigned int                          netmask;  /*掩码*/ 
    unsigned int                          gateway; /*网关地址*/
    unsigned int                          dns_addr;       /*域名解析服务器地址*/	
}ipv4_t;

//时间服务器配置参数
typedef struct tag_ntp_server_cfg_t
{
    int                                         is_open;
    unsigned int                                ntp_server_ip[READER_MAX_NTP_SVR_NUM]; /*最大为2个,第一个0表示结束,即0以前的是有效的*/
    char                                        tz_h;    /*时区,小时 范围-24--+24*/
    char                                        tz_m;    /*时区,分钟,-60--+60*/
    unsigned short                              ntp_serverip_num;/*时间服务器IP个数*/
    unsigned short                              ntp_period;    /* 与NTP服务器同步的时间周期 */
}ntp_server_cfg_t;


typedef struct tag_serial_cfg_t
{
    unsigned short                          serial_index;         /*串口索引号*/
    unsigned short                          serial_attr_index;        /*串口属性索引*/
}serial_cfg_t;


/*保活设置*/
typedef struct tag_keepalive_t
{
             int                        is_open ;               /*	可选值:0 :Null-不开启握手1 :Periodic*/
    unsigned int                        period;/*以毫秒记的时间.当KeepaliveTriggerType不是1时,此值被忽略.*/
}keepalive_t;


void get_ntp_struct_from_object(ntp_server_cfg_t  *ntp_server_cfg);
void set_ntp_struct_from_object(ntp_server_cfg_t  *ntp_server_cfg);

int check_value_between_min_max(int value,int min,int max);
int check_object_between_min_max(JSON_Object *input_object,const char *name,int min,int max);
int check_comm_serial_config(JSON_Object *input_object);
int check_comm_keepalive_config(JSON_Object *input_object);
int check_ip_gateway_dns(unsigned int ip_addr);
int check_ip_and_netmask(unsigned int ip_addr, unsigned int netmask);
int check_eeprom_ip_config(JSON_Object *input_object);
int check_file_ntp_config(JSON_Object *input_object);



#endif

