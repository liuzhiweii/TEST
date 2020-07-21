/***************************************************************************
* 版权所有:
*
* 文件名称：
* 文件标识：
* 内容摘要：
* 其它说明：
* 当前版本：
* 作    者：
* 完成日期：
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************************/
#include "cfgPub.h"                                                      
/***********************************************************
 *                        包含头文件                       *
 **********************************************************/


/***********************************************************
 *                     常量定义                            *
***********************************************************/

/***********************************************************
*                 文件内部使用的宏                         *
***********************************************************/

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/

/***********************************************************
 *                     全局变量                            *
***********************************************************/      
extern JSON_Object *root_object;
/***********************************************************
 *                     本地变量                            *
***********************************************************/

/***********************************************************
 *                     全局函数                            *
***********************************************************/

/***********************************************************
 *                     局部函数                            *
***********************************************************/
void get_ntp_struct_from_object(ntp_server_cfg_t  *ntp_server_cfg)
{   
    JSON_Object *cur_object=NULL;
    unsigned int dwLoop;
    CFG_DEBUG("get_ntp_struct_from_object\r\n");
    CHECK_NULL_POINTER_RETURN_VOID(ntp_server_cfg);

    cur_object=json_object_dotget_object(root_object,"file.ntp");
    CHECK_NULL_POINTER_RETURN_VOID(cur_object);
    
    /*NtpServerIPNum*/
    ntp_server_cfg->ntp_serverip_num=(unsigned short)json_object_get_number(cur_object,"NtpServerIPNum");
    
    /*NtpServerIP0*/
    ntp_server_cfg->ntp_server_ip[0]=(unsigned int)json_object_get_number(cur_object,"NtpServerIP0");

    /*NtpServerIP1*/
    ntp_server_cfg->ntp_server_ip[1]=(unsigned int)json_object_get_number(cur_object,"NtpServerIP1");
    
    /*TimeZoneH*/
    ntp_server_cfg->tz_h=(char)json_object_get_number(cur_object,"TimeZoneH");
    /*TimeZoneH*/
    ntp_server_cfg->tz_m=(char)json_object_get_number(cur_object,"TimeZoneM");
    /*NtpPeriod*/
    ntp_server_cfg->ntp_period=(unsigned short)json_object_get_number(cur_object,"NtpPeriod");
} 
void set_ntp_struct_from_object(ntp_server_cfg_t  *ntp_server_cfg)
{   
    JSON_Object *cur_object=NULL;
    unsigned int dwLoop;
    CFG_DEBUG("set_ntp_struct_from_object\r\n");
    CHECK_NULL_POINTER_RETURN_VOID(ntp_server_cfg);

    cur_object=json_object_dotget_object(root_object,"file.ntp");
    CHECK_NULL_POINTER_RETURN_VOID(cur_object);
    
    /*NtpServerIPNum*/
    json_object_set_number(cur_object,"NtpServerIPNum",ntp_server_cfg->ntp_serverip_num);
    
    /*NtpServerIP0*/
    json_object_set_number(cur_object,"NtpServerIP0",ntp_server_cfg->ntp_server_ip[0]);

    /*NtpServerIP1*/
    json_object_set_number(cur_object,"NtpServerIP1",ntp_server_cfg->ntp_server_ip[1]);
    
    /*TimeZoneH*/
    json_object_set_number(cur_object,"TimeZoneH",ntp_server_cfg->tz_h);
    /*TimeZoneH*/
    json_object_set_number(cur_object,"TimeZoneM",ntp_server_cfg->tz_m);
    /*NtpPeriod*/
    json_object_set_number(cur_object,"NtpPeriod",ntp_server_cfg->ntp_period);
}

int check_value_between_min_max(int value,int min,int max)
{
   if((value>=min)&&(value<=max))
   {
      return 0;
   }
   else
   {
      return -1;
   }
}
int check_object_between_min_max(JSON_Object *input_object,const char *name,int min,int max)
{
    int rc=0; 
    int value=0;
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    value=(int)json_object_dotget_number(input_object,name);
    rc=check_value_between_min_max(value,min,max);
    if(0!=rc)
    {
       CFG_DEBUG("name :%s error\r\n",name);
    }
    return rc;
}
int check_comm_serial_config(JSON_Object *input_object)
{
    int rc=0; 
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    rc=check_object_between_min_max(input_object,"portIndex",0,CFG_COMM_CAPABILITY_SERIAL_PORT_NUM);
    CHECK_NONZERO_NUMBER(rc); 
    rc=check_object_between_min_max(input_object,"attributeIndex",0,SERIALATTRIBUTE_LEN);
    CHECK_NONZERO_NUMBER(rc); 
    return rc;
} 
int check_comm_keepalive_config(JSON_Object *input_object)
{
    int rc=0; 
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    rc=check_object_between_min_max(input_object,"period",1000,7000);
    CHECK_NONZERO_NUMBER(rc);  
    return rc;
} 
int check_ip_gateway_dns(unsigned int ip_addr)
{
    int rc = 0;
    unsigned char aucAddr[4] = {0};

    aucAddr[0] = (unsigned char)((ip_addr & 0xFF000000) >> 24);
    aucAddr[1] = (unsigned char)((ip_addr & 0x00FF0000) >> 16);
    aucAddr[2] = (unsigned char)((ip_addr & 0x0000FF00) >> 8);
    aucAddr[3] = (unsigned char)((ip_addr & 0x000000FF));

    //aucAddr = (BYTE *)IPAddress;
    CFG_DEBUG("check_ip_gateway_dns:Input is %d. %d. %d. %d\r\n", aucAddr[0], aucAddr[1], aucAddr[2], aucAddr[3]);

    if ((223 < aucAddr[0]) || (255 == aucAddr[0]) || (0 == aucAddr[0]))
    {
        CFG_DEBUG("Addr is wrong!!! aucAddr[0] = %d\r\n", aucAddr[0]);
        rc=-1;
    }

    return rc;
}
int check_ip_and_netmask(unsigned int ip_addr, unsigned int netmask)
{
    unsigned char ip_byte[4] = {0};
    unsigned char netmask_byte[4] = {0};
    int rc = 0;
    unsigned char segmentNum;
    unsigned char leftNum;
    unsigned char i;
    unsigned char j;
    unsigned char combineResult = 0;
    unsigned char combineResult_1[4] = {0};

    ip_byte[0] = (unsigned char)((ip_addr & 0xFF000000) >> 24);
    ip_byte[1] = (unsigned char)((ip_addr & 0x00FF0000) >> 16);
    ip_byte[2] = (unsigned char)((ip_addr & 0x0000FF00) >> 8);
    ip_byte[3] = (unsigned char)((ip_addr & 0x000000FF));
    netmask_byte[0] = (unsigned char)((netmask & 0xFF000000) >> 24);
    netmask_byte[1] = (unsigned char)((netmask & 0x00FF0000) >> 16);
    netmask_byte[2] = (unsigned char)((netmask & 0x0000FF00) >> 8);
    netmask_byte[3] = (unsigned char)((netmask & 0x000000FF));
    CFG_DEBUG("cfg:ip_byte[0] = %d\r\n", ip_byte[0]);
    CFG_DEBUG("cfg:ip_byte[1] = %d\r\n", ip_byte[1]);
    CFG_DEBUG("cfg:ip_byte[2] = %d\r\n", ip_byte[2]);
    CFG_DEBUG("cfg:ip_byte[3] = %d\r\n", ip_byte[3]);
    CFG_DEBUG("cfg:netmask_byte[0] = %d\r\n", netmask_byte[0]);
    CFG_DEBUG("cfg:netmask_byte[1] = %d\r\n", netmask_byte[1]);
    CFG_DEBUG("cfg:netmask_byte[2] = %d\r\n", netmask_byte[2]);
    CFG_DEBUG("cfg:netmask_byte[3] = %d\r\n", netmask_byte[3]);
    for (i = 0; i < 4; i++)
    {
        if (netmask_byte[i] != 255)
        {
            segmentNum = netmask_byte[i];
            leftNum = 256 - segmentNum;

            if ((leftNum & (leftNum - 1)) != 0)
            {
                CFG_DEBUG( "CheckIPAndIpmask is wrong1\r\n");
                return -1;
            }
            else if (i < 3)
            {
                for (j = i + 1; j < 4; j++)
                {
                    if (netmask_byte[j] != 0)
                    {
                        CFG_DEBUG( "CheckIPAndIpmask is wrong2\r\n");
                        return -1;
                    }
                }
            }
            rc = 0;
        }
    }


    if (ip_byte[0] < 127)
    {
        if (255 != netmask_byte[0])
        {
            CFG_DEBUG("frist IPmask  must be 255!\r\n");
            return -1;
        }
    }
    else if (ip_byte[0] > 127 && ip_byte[0] < 192)
    {
        if (255 != netmask_byte[0] || 255 != netmask_byte[1])
        {
            CFG_DEBUG("frist and second IPmask  must be 255!\r\n");
            return -1;
        }
    }
    else if (ip_byte[0] > 191 && ip_byte[0] < 224)
    {
        if (255 != netmask_byte[0] || 255 != netmask_byte[1] || 255 != netmask_byte[2])
        {
            CFG_DEBUG("frist second third IPmask  must be 255!\r\n");
            return -1;
        }
    }



    combineResult += ~netmask_byte[0] & ip_byte[0];
    combineResult += ~netmask_byte[1] & ip_byte[1];
    combineResult += ~netmask_byte[2] & ip_byte[2];
    combineResult += ~netmask_byte[3] & ip_byte[3];

    if (0 == combineResult)
    {
        CFG_DEBUG("ip can not be all zero in ipmask limit\r\n");
        return -1;
    }


    combineResult_1[0] = netmask_byte[0] | ip_byte[0];
    combineResult_1[1] = netmask_byte[1] | ip_byte[1];
    combineResult_1[2] = netmask_byte[2] | ip_byte[2];
    combineResult_1[3] = netmask_byte[3] | ip_byte[3];
    if ((combineResult_1[0] == 255) && (combineResult_1[1] == 255) && (combineResult_1[2] == 255) && (combineResult_1[3] == 255))
    {
        CFG_DEBUG("ip can not be all one in ipmask limit\r\n");
        return -1;
    }
    return rc;
}
int check_eeprom_ip_config(JSON_Object *input_object)
{
    int rc=0; 
    unsigned int ip_addr,netmask,dns,gateway;
    int is_open=0;
    int serverip_num=0;
    CHECK_NULL_POINTER_RETURN_INT(input_object);

    ip_addr=(unsigned int)json_object_get_number(input_object,"IPAddress");
    rc=check_ip_gateway_dns(ip_addr);
    CHECK_NONZERO_NUMBER(rc);

    gateway=(unsigned int)json_object_get_number(input_object,"Gateway");
    rc=check_ip_gateway_dns(gateway);
    CHECK_NONZERO_NUMBER(rc);

    gateway=(unsigned int)json_object_get_number(input_object,"DNS");
    dns=check_ip_gateway_dns(dns);
    CHECK_NONZERO_NUMBER(rc);

    netmask=(unsigned int)json_object_get_number(input_object,"Netmask");
    rc=check_ip_and_netmask(ip_addr,netmask);
    CHECK_NONZERO_NUMBER(rc);
    return rc;
}
int check_file_ntp_config(JSON_Object *input_object)
{
    int rc=0; 
    unsigned int ip_addr;
    int is_open=0;
    int serverip_num=0;
    JSON_Object *tmp_object=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    
    is_open=json_object_get_boolean(input_object,"IsOpen");
    if(0==is_open)
    {
       return 0;
    }
    
    rc=check_object_between_min_max(input_object,"TimeZoneH",-23,23);
    CHECK_NONZERO_NUMBER(rc);

    rc=check_object_between_min_max(input_object,"TimeZoneM",-59,59);
    CHECK_NONZERO_NUMBER(rc);

    rc=check_object_between_min_max(input_object,"NtpPeriod",1,6);
    CHECK_NONZERO_NUMBER(rc);

    rc=check_object_between_min_max(input_object,"NtpServerIPNum",1,2);
    CHECK_NONZERO_NUMBER(rc);
    
    ip_addr=(unsigned int)json_object_get_number(input_object,"NtpServerIP0");
    rc=check_ip_gateway_dns(ip_addr);
    CHECK_NONZERO_NUMBER(rc);

    serverip_num=json_object_get_number(input_object,"NtpServerIPNum");
    if(2==serverip_num)
    {
       ip_addr=(unsigned int)json_object_get_number(input_object,"NtpServerIP1");
       rc=check_ip_gateway_dns(ip_addr);
       CHECK_NONZERO_NUMBER(rc);
    }
    return rc;
}







