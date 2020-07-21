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
#ifdef CFG_ETC
#include "cfg.h"
#include "cfgEtc.h" 

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
int set_etc_struct_to_object(etc_config_t  *etc_config)
{   
    JSON_Object *cur_object=NULL;
    CFG_DEBUG("set_etc_struct_to_object\r\n");
    CHECK_NULL_POINTER_RETURN_INT(etc_config);

    cur_object=json_object_dotget_object(root_object,"file.rfs");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*EtcVersion*/
    json_object_set_number(cur_object,"EtcVersion",etc_config->etc_version);

    /*N4Value*/
    json_object_set_number(cur_object,"N4Value",etc_config->n4_value);

    /*BSTInterval*/
    json_object_set_number(cur_object,"BSTInterval",etc_config->bst_interval);

    /*CrcChangeFlag*/
    json_object_set_number(cur_object,"CrcChangeFlag",etc_config->crc_change_flag);

    /*PllChannelId*/
    json_object_set_number(cur_object,"PllChannelId",etc_config->pll_channel_id);

    /*TxPower*/
    json_object_set_number(cur_object,"TxPower",etc_config->tx_power);
   
    /*ucModuleDepth*/
    json_object_set_number(cur_object,"ModuleDepth",etc_config->module_depth);
    
    /*wRSUIDChangeTime*/
    json_object_set_number(cur_object,"RSUIDChangeTime",etc_config->rsuid_change_time);

    /*EndAppSendNum*/
    json_object_set_number(cur_object,"EndAppSendNum",etc_config->end_app_send_num);

    /*RSUIDChangeFlag*/
    json_object_set_boolean(cur_object,"RSUIDChangeFlag",etc_config->rsuid_change_flag);

    /*RssiControlFlag*/
    json_object_set_boolean(cur_object,"RssiControlFlag",etc_config->rssi_control_flag);

    /*CheckChannelIdFlag*/
    json_object_set_boolean(cur_object,"CheckChannelIdFlag",etc_config->check_channelId_flag);

    /*TptlFlag*/
    json_object_set_boolean(cur_object,"TptlFlag",etc_config->tptl_flag);
    
    /*LinkageFlag*/
    json_object_set_boolean(cur_object,"LinkageFlag",etc_config->linkage_flag);

    /*MaxWaitTime*/
    json_object_set_number(cur_object,"MaxWaitTime",etc_config->max_wait_time);

    /*RandomWaitTime*/
    json_object_set_number(cur_object,"RandomWaitTime",etc_config->random_wait_time);

    /*PSAMForceFlag*/
    json_object_set_boolean(cur_object,"PSAMForceFlag",etc_config->psam_force_flag);

    /*ESAMPosition*/
    json_object_set_number(cur_object,"ESAMPosition",etc_config->esam_position);

    /*ICCPosition*/
    json_object_set_number(cur_object,"ICCPosition",etc_config->icc_position);
    return 0;
}
int get_etc_struct_from_object(etc_config_t  *etc_config)
{   
    JSON_Object *cur_object=NULL;
    CFG_DEBUG("get_etc_struct_to_object\r\n");
    CHECK_NULL_POINTER_RETURN_INT(etc_config);

    cur_object=json_object_dotget_object(root_object,"file.rfs");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*EtcVersion*/
    etc_config->etc_version=(unsigned char)json_object_get_number(cur_object,"EtcVersion");

    /*N4Value*/
    etc_config->n4_value=(unsigned char)json_object_get_number(cur_object,"N4Value");

    /*BSTInterval*/
    etc_config->bst_interval=(unsigned char)json_object_get_number(cur_object,"BSTInterval");

    /*CrcChangeFlag*/
    etc_config->crc_change_flag=(unsigned char)json_object_get_number(cur_object,"CrcChangeFlag");

    /*PllChannelId*/
    etc_config->pll_channel_id=(unsigned char)json_object_get_number(cur_object,"PllChannelId");

    /*TxPower*/
    etc_config->tx_power=(unsigned char)json_object_get_number(cur_object,"TxPower");
   
    /*ucModuleDepth*/
    etc_config->module_depth=(unsigned char)json_object_get_number(cur_object,"ModuleDepth");
    
    /*wRSUIDChangeTime*/
    etc_config->rsuid_change_time=(unsigned short)json_object_get_number(cur_object,"RSUIDChangeTime");

    /*EndAppSendNum*/
    etc_config->end_app_send_num=(unsigned int)json_object_get_number(cur_object,"EndAppSendNum");

    /*RSUIDChangeFlag*/
    etc_config->rsuid_change_flag=json_object_get_boolean(cur_object,"RSUIDChangeFlag");

    /*RssiControlFlag*/
    etc_config->rssi_control_flag=json_object_get_boolean(cur_object,"RssiControlFlag");

    /*CheckChannelIdFlag*/
    etc_config->check_channelId_flag=json_object_get_boolean(cur_object,"CheckChannelIdFlag");

    /*TptlFlag*/
    etc_config->tptl_flag=json_object_get_boolean(cur_object,"TptlFlag");
    
    /*LinkageFlag*/
    etc_config->linkage_flag=json_object_get_boolean(cur_object,"LinkageFlag");

    /*MaxWaitTime*/
    etc_config->max_wait_time=(unsigned int)json_object_get_number(cur_object,"MaxWaitTime");

    /*RandomWaitTime*/
    etc_config->random_wait_time=(unsigned int)json_object_get_number(cur_object,"RandomWaitTime");

    /*PSAMForceFlag*/
    etc_config->psam_force_flag=json_object_get_boolean(cur_object,"PSAMForceFlag");

    /*ESAMPosition*/
    etc_config->esam_position=(unsigned int)json_object_get_number(cur_object,"ESAMPosition");

    /*ICCPosition*/
    etc_config->icc_position=(unsigned int)json_object_get_number(cur_object,"ICCPosition");
    return 0;
}

int get_comm_struct_from_object(comm_cfg_t  *comm_cfg)
{   
    JSON_Object *cur_object=NULL;
    unsigned int dwLoop;
    CFG_DEBUG("get_comm_struct_from_object\r\n");
    CHECK_NULL_POINTER_RETURN_INT(comm_cfg);

    cur_object=json_object_dotget_object(root_object,"file.comm.Keepalive");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*IsOpen*/
    comm_cfg->keepalive.is_open=json_object_get_boolean(cur_object,"IsOpen");

    /*Period*/
    comm_cfg->keepalive.period=(unsigned int)json_object_get_number(cur_object,"Period");

    cur_object=json_object_dotget_object(root_object,"file.comm.NetCfg");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*HostPort*/
    comm_cfg->net_cfg.port=(unsigned short)json_object_get_number(cur_object,"HostPort");
 
    cur_object=json_object_dotget_object(root_object,"file.comm.SerialCfg");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*SerialIndex*/
    comm_cfg->serial_cfg.serial_index=(unsigned short)json_object_get_number(cur_object,"SerialIndex");

    /*SerialPortIndex*/
    comm_cfg->serial_cfg.serial_attr_index=(unsigned short)json_object_get_number(cur_object,"SerialAttributeIndex");

    /*ntp*/
    get_ntp_struct_from_object(&comm_cfg->ntp_server_cfg);

    
    cur_object=json_object_dotget_object(root_object,"nvram");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*IPAddress*/
    comm_cfg->reader_ip.ip_addr=(unsigned int)json_object_get_number(cur_object,"IPAddress");
    /*Netmask*/
    comm_cfg->reader_ip.netmask=(unsigned int)json_object_get_number(cur_object,"Netmasks");
    /*Gateway*/
    comm_cfg->reader_ip.gateway=(unsigned int)json_object_get_number(cur_object,"Gateway");
    /*DNS*/
    comm_cfg->reader_ip.dns_addr=(unsigned int)json_object_get_number(cur_object,"DNS");
    /*IsDhcp*/
    comm_cfg->reader_ip.ip_config=(unsigned short)json_object_get_number(cur_object,"IPConfig");
    return 0;
}
int set_comm_struct_from_object(comm_cfg_t  *comm_cfg)
{   
    JSON_Object *cur_object=NULL;
    unsigned int dwLoop;
    CFG_DEBUG("set_comm_struct_from_object\r\n");
    CHECK_NULL_POINTER_RETURN_INT(comm_cfg);

    cur_object=json_object_dotget_object(root_object,"file.comm.Keepalive");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*IsOpen*/
    json_object_set_boolean(cur_object,"IsOpen",comm_cfg->keepalive.is_open);

    /*Period*/
    json_object_set_number(cur_object,"Period",comm_cfg->keepalive.period);

    cur_object=json_object_dotget_object(root_object,"file.comm.NetCfg");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*HostPort*/
    json_object_set_number(cur_object,"HostPort",comm_cfg->net_cfg.port);
 
    cur_object=json_object_dotget_object(root_object,"file.comm.SerialCfg");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*SerialIndex*/
    json_object_set_number(cur_object,"SerialIndex",comm_cfg->serial_cfg.serial_index);

    /*SerialPortIndex*/
    json_object_set_number(cur_object,"SerialAttributeIndex",comm_cfg->serial_cfg.serial_attr_index);

    /*ntp*/
    set_ntp_struct_from_object(&comm_cfg->ntp_server_cfg);

    
    cur_object=json_object_dotget_object(root_object,"nvram");
    CHECK_NULL_POINTER_RETURN_INT(cur_object);
    
    /*IPAddress*/
    json_object_set_number(cur_object,"IPAddress",comm_cfg->reader_ip.ip_addr);
    /*Netmask*/
    json_object_set_number(cur_object,"Netmasks",comm_cfg->reader_ip.netmask);
    /*Gateway*/
    json_object_set_number(cur_object,"Gateway",comm_cfg->reader_ip.gateway);
    /*DNS*/
    json_object_set_number(cur_object,"DNS",comm_cfg->reader_ip.dns_addr);
    /*ipconfig*/
    json_object_set_number(cur_object,"IPConfig",comm_cfg->reader_ip.ip_config);
    return 0;
}

int check_etc_business_config(JSON_Object *input_object)
{
    int rc=0; 
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    rc=check_object_between_min_max(input_object,"Version",0,0);
    CHECK_NONZERO_NUMBER(rc);
    
    rc=check_object_between_min_max(input_object,"N4Value",1,127);
    CHECK_NONZERO_NUMBER(rc);

    rc=check_object_between_min_max(input_object,"BSTInterval",1,127);
    CHECK_NONZERO_NUMBER(rc);
    
    rc=check_object_between_min_max(input_object,"crc_chang_flag",0,1);
    CHECK_NONZERO_NUMBER(rc);

    rc=check_object_between_min_max(input_object,"PllChannelId",0,1);
    CHECK_NONZERO_NUMBER(rc);
    
    rc=check_object_between_min_max(input_object,"TxPower",0,18);
    CHECK_NONZERO_NUMBER(rc);
    
    rc=check_object_between_min_max(input_object,"ModuleDepth",0,CFG_ETC_MODULE_DEPTH_LEN);
    CHECK_NONZERO_NUMBER(rc);
    return rc;
}

int check_etc_comm_net_config(JSON_Object *input_object)
{
    int rc=0; 
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    rc=check_object_between_min_max(input_object,"HostPort",1024,65535);
    CHECK_NONZERO_NUMBER(rc);    
    return rc;
}  

int check_etc_file_comm_config(JSON_Object *input_object)
{
    int rc=0; 
    JSON_Object *tmp_object=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);

    tmp_object=json_object_get_object(input_object,"Keepalive");
    rc=check_comm_keepalive_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"NetCfg");
    rc=check_etc_comm_net_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);
    
    tmp_object=json_object_get_object(input_object,"SerialCfg");
    rc=check_comm_serial_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);
    return rc;
}    

int check_etc_file_config(JSON_Object *input_object)
{
    int rc=0; 
    JSON_Object *tmp_object=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    
    tmp_object=json_object_get_object(input_object,"rfs");
    rc=check_etc_business_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"comm");
    rc=check_etc_file_comm_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"ntp");
    rc=check_file_ntp_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);
    return rc;
}

int check_etc_config(JSON_Object *input_object)
{
    int rc=0; 
    JSON_Object *tmp_object=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);

    tmp_object=json_object_get_object(input_object,"file");
    rc=check_etc_file_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"eeprom");
    rc=check_eeprom_ip_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);
}

#endif
