#include <zmq.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <errno.h>
#include "dispatch.h"
#include "logm.h"
#include "parson.h"
#include "bsp/bsp_parallel_psam.h"
#include "bsp/bsp_psam.h"
#include "bsp/bsp_lcd.h"
#include "bsp/bsp_device_ctrl.h"
#include "utimer.h"
#include <assert.h>
#include <syslog.h> 
#include "abn.h" 




void *push_socket_comm = NULL;
void *pull_socket_comm = NULL;
void *push_socket_rfs = NULL;
void *pull_socket_rfs = NULL;
void *req_socket_cfg = NULL;
void *sub_socket_cfg = NULL;
void *push_socket_displsy = NULL;
void *req_socket_cmm = NULL;


void *logm_socket = NULL;
int cmd_ack_flag=1;  //是否返回给pc标志
int bst_ack_send_flag=0;  //是否返回给pc标志
int cmd_ack_send_flag=0;  //是否返回给pc标志


unsigned short time_out_client=1000; //和后台之间的超时时间默认1000ms

unsigned char g_IpBuf[16] = {0};
int get_networkcard_num(void);
unsigned int getlocalIp(unsigned char *pucName, unsigned char *pucBuf);
int eth_ip_init(int interfacenum, unsigned char *pIpBuf);

void set_zmq_socket_option(void *socket, int type, int value)
{
    int rc = 0;
    rc = zmq_setsockopt(socket, type, &value, sizeof(int));
    CHECK_FAIL_NUMBER(rc, "set_zmq_socket_option zmq_setsockopt fail");
}


void create_zmq_sockets(void)
{
    void *ctx;
    int value;
    int ret;
    char aucBuf[50];

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
		abn_debug("zmq_init error:%s\r\n",zmq_strerror(errno));
        exit(-1);
    }

    /*和comm模块接口*/
    push_socket_comm = zmq_socket(ctx, ZMQ_PUSH);
    if(NULL == push_socket_comm)
    {
        printf("zmq_socket fail!\n");
		abn_debug("zmq_socket error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }
    ret = zmq_connect(push_socket_comm, "tcp://127.0.0.1:5011");
    if(ret < 0)
    {
        printf("bind push_socket_comm socket fail\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }

    set_zmq_socket_option(push_socket_comm, ZMQ_SNDHWM, 10);

    pull_socket_comm = zmq_socket(ctx, ZMQ_PULL);
    if(NULL == pull_socket_comm)
    {
        printf("create pull_socket_comm fail!\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }

    ret = zmq_connect(pull_socket_comm, "tcp://127.0.0.1:5010");
    if(ret < 0)
    {
        printf("bind pull_socket_comm socket fail\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }

    /*创建rfs pull push 接口*/
    push_socket_rfs = zmq_socket(ctx, ZMQ_PUSH);
    if(NULL == push_socket_rfs)
    {
        printf("create push_socket_comm fail!\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }
    ret = zmq_connect(push_socket_rfs, "tcp://222.255.255.253:5502");
    if(ret < 0)
    {
        printf("connect push_socket_rfs socket fail\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }
    set_zmq_socket_option(push_socket_rfs, ZMQ_LINGER, 0);
    value = 10;
    zmq_setsockopt(push_socket_rfs, ZMQ_SNDHWM, &value, sizeof(int));

    pull_socket_rfs = zmq_socket(ctx, ZMQ_PULL);
    if(NULL == pull_socket_rfs)
    {
        printf("create pull_socket_rfs fail!\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }

    ret = zmq_connect(pull_socket_rfs, "tcp://222.255.255.253:5501");
    if(ret < 0)
    {
        printf("connect pull_socket_rfs socket fail\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }
	set_zmq_socket_option(pull_socket_rfs, ZMQ_LINGER, 0);
	
    /*cfg zmq*/
    req_socket_cfg = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == req_socket_cfg)
    {
        printf("create tcp req_socket_cfg fail!\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }

    set_zmq_socket_option(req_socket_cfg, ZMQ_RCVTIMEO, 2000);
    set_zmq_socket_option(req_socket_cfg, ZMQ_LINGER, 0);

    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE, 1);
    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_CNT, 2);
    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_IDLE, 1);
    set_zmq_socket_option(req_socket_cfg, ZMQ_TCP_KEEPALIVE_INTVL, 1);

    //ret= zmq_setsockopt (req_socket, ZMQ_SNDTIMEO, 2000, 4);
    ret = zmq_connect(req_socket_cfg, "tcp://127.0.0.1:5504");
    if(ret < 0)
    {
        printf("connect req_socket_cfg fail\n");
		abn_debug("zmq_connect failed errno=%d\r\n",errno);
        exit(-1);
    }

    /*cfg pub*/
	sub_socket_cfg = zmq_socket(ctx, ZMQ_SUB);
    if(NULL == sub_socket_cfg)
    {
        printf("create sub_socket_cfg fail!\n");
		abn_debug("zmq_socket failed errno=%d\r\n",errno);
        exit(-1);
    }

    sprintf(aucBuf, "tcp://%s:5505", g_IpBuf);
    ret = zmq_connect(sub_socket_cfg, aucBuf);
    //ret = zmq_connect(sub_socket_cfg, "tcp://192.168.1.218:5505");
	if(ret < 0)
    {
        printf("connect sub_socket_cfg fail\n");
		abn_debug("zmq_connect failed errno=%d\r\n",errno);
        exit(-1);
    }
	ret = zmq_setsockopt (sub_socket_cfg, ZMQ_SUBSCRIBE, "", 0);
	if(ret < 0)
    {
        printf("zmq_setsockopt zmq_setsockopt fail\n");
		abn_debug("zmq_setsockopt failed errno=%d\r\n",errno);
        exit(-1);
    }
	printf("sub_socket_cfg ZMQ_SUBSCRIBE success\n");

    /*cmm zmq*/
    req_socket_cmm = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == req_socket_cmm)
    {
        printf("create tcp req_socket_cmm fail!\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        exit(-1);
    }

    set_zmq_socket_option(req_socket_cmm, ZMQ_RCVTIMEO, 2000);
    set_zmq_socket_option(req_socket_cmm, ZMQ_LINGER, 0);

    ret = zmq_connect(req_socket_cmm, "ipc://cmm_dispatch.ipc");
    if(ret < 0)
    {
        printf("connect req_socket_cmm fail\n");
		abn_debug("zmq_connect failed errno=%d\r\n",errno);
        exit(-1);
    }

    return;
}




/*下发配置*/
void send_cfg_msg(const char *type, const char *action, const char *content)
{
    int rc = 0;
    char send_buffer[4096];
    JSON_Value *tmp_value = NULL;
    JSON_Object *tmp_object = NULL;

    printf("send_cfg_msg type=%s,action=%s,content=%s\r\n", type, action, content);

    tmp_value = json_value_init_object();
    tmp_object = tmp_value->value.object;
    json_object_set_string(tmp_object, "type", type);
    json_object_set_string(tmp_object, "action", action);
    if(NULL != content)
    {
        json_object_set_string(tmp_object, "content", content);
    }
    memset(send_buffer, 0, sizeof(send_buffer));
    rc = json_serialize_to_buffer(tmp_value, send_buffer, sizeof(send_buffer));
    /*释放*/
    json_value_free(tmp_value);
    DIS_DEBUG("json_serialize_to_buffer send_buffer = %s \r\n", send_buffer);
    zmq_send (req_socket_cfg, send_buffer, strlen(send_buffer) + 1, 0);
}
/*转化string类型的json 为对象*/
JSON_Object *parse_string_to_object(const char *strings, JSON_Value **string_value)
{
    JSON_Object *tmp_object = NULL;
    JSON_Value *tmp_value = NULL;
    DIS_DEBUG("parse_string_to_object \r\n");

    /* 解析默认配置 */
    tmp_value = json_parse_string(strings);
    *string_value = NULL;
    if(NULL == tmp_value)
    {
        DIS_DEBUG("(parse_string_to_object) error null pointer\r\n");
		abn_debug("json_parse_string return null\r\n");
        return NULL;
    }

    if(json_value_get_type(tmp_value) == JSONObject)
    {
        tmp_object = json_value_get_object(tmp_value);
        *string_value = tmp_value;
    }
    else
    {
        DIS_DEBUG("error! not an object type=%d\r\n", json_value_get_type(tmp_value));
		abn_debug("not json object\r\n");
        json_value_free(tmp_value);
        *string_value = NULL;
        return NULL;
    }
    return tmp_object;
}

unsigned char set_cfg_throw_get(init_device_t *init_device)
{
    int rc = 0;
    unsigned char ret = 0;
    char recv_buf[8196] = {0};
    const char *type = NULL;
    const char *content = NULL;
    char *send_content = NULL;
    int result = 0;
    JSON_Value *cur_value = NULL;
    JSON_Object *cur_object = NULL;
    JSON_Value *set_value = NULL;
    JSON_Object *set_object = NULL;
    JSON_Value *tmp_value = NULL;
    JSON_Value *cur_value_set = NULL;
    JSON_Object *cur_object_set = NULL;
    unsigned int number = 0;

    send_cfg_msg("client", "get", NULL);
    memset(recv_buf, 0, sizeof(recv_buf));
    rc = zmq_recv(req_socket_cfg, recv_buf, sizeof(recv_buf), 0);
    if(rc <= 0)
    {
        return 1;
    }
    cur_object = parse_string_to_object(recv_buf, &cur_value);
    if(NULL == cur_object)
    {
        return 1;
    }
    type = json_object_get_string(cur_object, "type");
    result = (int)json_object_get_number(cur_object, "result");
    content = json_object_get_string(cur_object, "content");
    if((0 == strcmp(type, "client_get_ack")) && (0 == result))
    {
        DIS_DEBUG("client get content:%s\r\n", content);
        //将content转化为对象，修改其中的值
        set_object = parse_string_to_object(content, &set_value);
        if(NULL == set_object)
        {
            json_value_free(cur_value);
            return 1;
        }
        json_object_dotset_number(set_object, "file.rfs.BSTInterval", init_device->bst_interval);
        json_object_dotset_number(set_object, "file.rfs.TxPower", init_device->tx_power);
        json_object_dotset_number(set_object, "file.rfs.PllChannelId", init_device->pll_channelID);
        json_object_dotset_number(set_object, "file.rfs.TimeOut", init_device->time_out);
        send_content = json_serialize_to_string(set_value);
        send_cfg_msg("client", "set", send_content);
        json_value_free(set_value);
        json_free_serialized_string(send_content);
        memset(recv_buf, 0, sizeof(recv_buf));
        rc = zmq_recv(req_socket_cfg, recv_buf, sizeof(recv_buf), 0);
        if(rc > 0)
        {
            cur_object_set = parse_string_to_object(recv_buf, &cur_value_set);
            if(NULL == cur_object_set)
            {
                //记录异常
                DIS_DEBUG("cur_object is null");
				abn_debug("null pointer\r\n");
                return 1;
            }
            type = json_object_get_string(cur_object_set, "type");
            result = (int)json_object_get_number(cur_object_set, "result");
            if((0 == strcmp(type, "set_ack")) && (0 == result))
            {
                DIS_DEBUG("set cfg success\r\n");
                ret = 0;
            }
            else
            {
                DIS_DEBUG("set cfg failed\r\n");
                ret = 1;
            }
            json_value_free(cur_value_set);
        }
        else
        {
            DIS_DEBUG("recv msg error rc=%d\r\n", rc);
			abn_debug("zmq_recv error rc=%d\r\n",rc);
        }

    }
    else
    {
        DIS_DEBUG("get cfg failed type=%s,result=%d\r\n", type, result);
    }
    json_value_free(cur_value);
    return ret;
}

void init_device(char *recv_buf)
{
    int rc = -1;
    unsigned char status = 0;
    char send_buf[512] = {0};
    char recv_buffer[512] = {0};
    init_device_t *init_device = NULL;
    init_device_ack_t init_device_ack;
    const char *type = NULL;
    int result = 0;
    JSON_Value *cur_value = NULL;
    JSON_Object *cur_object = NULL;
    struct timeval time_tv;


    /*发卡器初始化*/
    init_device = (init_device_t *)recv_buf;
    DIS_DEBUG("system time :0x%x,time_out:%d\n", init_device->date_time, init_device->time_out);
    //设置系统时间
    time_tv.tv_sec = init_device->date_time;
    time_tv.tv_usec = 0;
    settimeofday(&time_tv, NULL);
	time_out_client = init_device->time_out;


	//lcd显示
	show_lcd_string(init_device->tx_power,init_device->pll_channelID);
    /*发送给rfs*/
	zmq_send (push_socket_rfs, init_device, sizeof(init_device_t), 0);
#if 1
    //下发配置
    sprintf(send_buf, "{\"BSTInterval\":%d,\"TxPower\":%d,\"PllChannelId\":%d,\"TimeOut\":%d}",
            init_device->bst_interval, init_device->tx_power, init_device->pll_channelID, init_device->time_out);
    DIS_DEBUG("cfg content:%s", send_buf);
    send_cfg_msg("rfs", "set", send_buf);

    //接受配置响应，返回给comm
    rc = zmq_recv(req_socket_cfg, recv_buffer, 512, 0);
    if(rc > 0)
    {
        cur_object = parse_string_to_object(recv_buffer, &cur_value);
        if(NULL == cur_object)
        {
            //记录异常
            DIS_DEBUG("cur_object is null:%s");
            return;
        }
        type = json_object_get_string(cur_object, "type");
        result = (int)json_object_get_number(cur_object, "result");
        if((0 == strcmp(type, "set_ack")) && (0 == result))
        {
            DIS_DEBUG("success\r\n");
            status = 0;
        }
        else
        {
            DIS_DEBUG("set cfg failed\r\n");
            status = 1;
        }
        json_value_free(cur_value);
    }
    else
    {
        DIS_DEBUG("recv msg error rc=%d\r\n", rc);
    }


    //下发配置
    status = set_cfg_throw_get(init_device);
   #endif
    init_device_ack.frame_type = 0xE0;
    init_device_ack.status = status;
    init_device_ack.device_info.firm_code = 1;
    init_device_ack.device_info.version = 10;
    init_device_ack.info_len = sizeof(device_info_t);
    zmq_send (push_socket_comm, &init_device_ack, sizeof(init_device_ack), 0);
    return;
	
}


void reset_psam(char *recv_buf)
{
    int rc = 0;
    psam_reset_t *psam_reset = NULL;
	T_CardPara tCardPara;
	unsigned int PsamErrorCode;
    psam_reset_ack_t psam_reset_ack;
    //psam通道复位
    psam_reset = (psam_reset_t *)recv_buf;
    //调用驱动
    rc=bsp_psam_active(psam_reset->psam_slot,&tCardPara,&PsamErrorCode);
	if(0!=rc)
	{
	    DIS_DEBUG("bsp_drv_psam_active fail ,rc:%d, errorcode %d \n", rc,PsamErrorCode);
	}
    //返回响应
    memset(&psam_reset_ack, 0, sizeof(psam_reset_ack));
    psam_reset_ack.frame_type = 0xE8;
    psam_reset_ack.status = rc;
    psam_reset_ack.info_len=sizeof(T_CardPara);
	memcpy(psam_reset_ack.reset_data,&tCardPara,sizeof(tCardPara));
    zmq_send (push_socket_comm, &psam_reset_ack, 3+sizeof(tCardPara), 0);
    return;
}

void opetate_psam_cmd(char *recv_buf)
{
    int rc = 0;
    int loop = 0;

    unsigned char psam_slot = 0;
    unsigned char cmd_num = 0;
    unsigned char cur_cmd_len = 0;
    unsigned char cur_cmd[128] = {0};
    unsigned char *p = NULL;

    unsigned char send_buf[512]={0};
    unsigned char *q = NULL;
    unsigned char *status = NULL;
    unsigned char *cmd_ack_num = NULL;
    unsigned char cur_ack_len = 0;
    unsigned char cur_cmd_ack[128] = {0};
	unsigned int error_code;

    p = recv_buf;
    p++;
    psam_slot = p[0];

    p++;
    cmd_num = p[0];

    q = send_buf;
    q[0] = 0xE9;
    q++;
    status = q;
    q++;
    cmd_ack_num = q;
    q++;
    for(loop = 0, p++; loop < cmd_num; loop++)
    {
        cur_cmd_len = p[0];
        p++;
		memset(cur_cmd,0,sizeof(cur_cmd));
		memset(cur_cmd_ack,0,sizeof(cur_cmd_ack));

		if(cur_cmd_len>sizeof(cur_cmd))
		{
		    logm_debug("opetate_psam_cmd error cur_cmd_len=%d\r\n",cur_cmd_len);
			*status = 1;
		    break;
		}
        memcpy(cur_cmd, p, cur_cmd_len);
		
        //调用驱动
        rc=bsp_psam_cmd(psam_slot,cur_cmd_len,cur_cmd,&cur_ack_len,cur_cmd_ack,&error_code);
        if(0 != rc)
        {
            *status = 1;
            break;
        }
        *status = 0;
        q[0] = cur_ack_len;
        q++;
		if(cur_ack_len>sizeof(cur_cmd_ack))
		{
		    logm_debug("opetate_psam_cmd error cur_ack_len=%d\r\n",cur_ack_len);
			*status = 1;
		    break;
		}
        memcpy(q, cur_cmd_ack, cur_ack_len);
        q += cur_ack_len;

        p += cur_cmd_len;
    }
    *cmd_ack_num = loop;
    //返回响应
    zmq_send (push_socket_comm, send_buf, q-send_buf, 0);
    return;
}

void deal_comm_raw_msg(char *recv_buf, int msg_len)
{
    unsigned char cmd = 0;
	int ret=0;
    cmd = recv_buf[0];
	DIS_DEBUG("deal_comm_raw_msg cmdtype=0x%x\r\n",cmd);
    switch (cmd)
    {
    case 0xF0:
    {
        /*发卡器初始化*/
        init_device(recv_buf);
        break;
    }
    case 0xF1:
	{
		//转发给rfs BST
   		 ret=zmq_send(push_socket_rfs, recv_buf, msg_len, 0);
		 if(ret<0)
		 {
		     DIS_DEBUG("zmq_send error :%s\r\n",zmq_strerror(errno));
		 }
		 DIS_DEBUG("recv bst zmq_send ret :%d\r\n",ret);
		 DISPATCH_SET_TIMER_MS(TIMER_DISPATCH_BST,time_out_client);
		 bst_ack_send_flag=0; 
		 break;
	}
    case 0xF2:
	{
		//转发给rfs  ACTION
   		 ret=zmq_send(push_socket_rfs, recv_buf, msg_len, 0);
		 if(ret<0)
		 {
		     DIS_DEBUG("zmq_send error :%s\r\n",zmq_strerror(errno));
		 }
		 if(1==recv_buf[1])
		 {
		 	DISPATCH_SET_TIMER_MS(TIMER_DISPATCH_ACTION,time_out_client);
			cmd_ack_flag =1;
			cmd_ack_send_flag=0;
		 }
		 else
		 {
		    cmd_ack_flag = 0;
		 }
		 break;
		 
	}
    case 0xF3:
    {   //EVENT REPORT
        zmq_send(push_socket_rfs, recv_buf, msg_len, 0);
        break;
    }
    case 0xF8:
    {
        reset_psam(recv_buf);
        break;
    }
    case 0xF9:
    {
        opetate_psam_cmd(recv_buf);
        break;
    }
    default:
    {
        DIS_DEBUG("recv wrong cmd cmd=0x%x\r\n", cmd);
		abn_debug("cmd=0x%x\r\n",cmd);
        break;
    }
    }

}
void deal_timer_raw_msg(char *recv_buf)
{
	unsigned int timer_id;
	unsigned char send_buf[256]={0};
	timer_id=*(unsigned int *)recv_buf;
	DIS_DEBUG("deal_timer_raw_msg timerid=%d\r\n", timer_id);
	del_timer(timer_id);
    if(TIMER_DISPATCH_BST==timer_id)
    {
       //回复响应
       if(0==bst_ack_send_flag)
		{
			//转发给comm
			DIS_DEBUG("RECV VST TIMEOUT send to comm\r\n");
  	       send_buf[0]=0xE1;
  		   send_buf[1]=1;
  		   zmq_send(push_socket_comm,send_buf,2,0);
			bst_ack_send_flag=1;
		}
        else
        {
        	DIS_DEBUG("error !!! RECV VST TIMEOUT ,HAS SENT,so not send again\r\n");
        }
       
    }
	else if(TIMER_DISPATCH_ACTION==timer_id)
	{
	   //回复响应
	   if((1==cmd_ack_flag)&&(0==cmd_ack_send_flag))
        {
           DIS_DEBUG("RECV ACTION TIMEOUT  dispatch send cmd rsp to comm\r\n");
           send_buf[0]=0xE2;
	       send_buf[1]=1;
	       zmq_send(push_socket_comm,send_buf,2,0);
		   cmd_ack_send_flag=1;
        }
		else
		{
		    DIS_DEBUG("RECV ACTION TIMEOUT  but not need send cmd rsp to comm cmd_ack_flag=%d\r\n",cmd_ack_flag);
		}
	   
	}
	else
	{
	}

}


void deal_rfs_raw_msg(char *recv_buf, int msg_len)
{
    unsigned char frame_type = 0;

    frame_type = recv_buf[0];
    switch (frame_type)
    {
    case 0xE1:
	{
		del_timer(TIMER_DISPATCH_BST);
		if(0==bst_ack_send_flag)
		{
			//转发给comm
			DIS_DEBUG("RECV VST from rfs ,send vst to comm\r\n");
        	zmq_send(push_socket_comm, recv_buf, msg_len, 0);
			bst_ack_send_flag=1;
		}
        else
        {
        	DIS_DEBUG("RECV VST ,HAS SENT,so not send again status=%d\r\n", recv_buf[1]);
        }
		
        break;
    }
    case 0xE2:
    {
        //转发给comm,需要判断是否需要返回给pc
        del_timer(TIMER_DISPATCH_ACTION);
        if((1==cmd_ack_flag)&&(0==cmd_ack_send_flag))
        {
           DIS_DEBUG("RECV ACTION RSP from rfs ,send cmd rsp to comm\r\n");
           zmq_send(push_socket_comm, recv_buf, msg_len, 0);
		   cmd_ack_send_flag=1;
        }
		else
		{
		    DIS_DEBUG("dispatch recv cmd rsp but not need send cmd rsp to comm,status=%d\r\n", recv_buf[1]);
		}

        break;
    }
    default:
    {
        DIS_DEBUG("recv wrong cmd cmd=0x%x\r\n", frame_type);
        break;
    }
    }

}
int init_device_ctl()
{
    int ret=0;
	unsigned short a;
    ret=bsp_epld_init();
	if(0!=ret)
	{
	   abn_debug("bsp_epld_init error ret=%d\r\n",ret);
	   return ret;
	}

    ret=bsp_fpga_init();
	if(0!=ret)
	{
	   abn_debug("bsp_fpga_init error ret=%d\r\n",ret);
	   return ret;
	}    
	
    ret=bsp_devicectl_init();
	if(0!=ret)
	{
	   abn_debug("bsp_devicectl_init error ret=%d\r\n",ret);
	   return ret;
	}   

    return 0;
}
int init_lcd()
{
    int ret=0;
	unsigned short a;
    ret=bsp_epld_init();
	if(0!=ret)
	{
	   abn_debug("bsp_epld_init error ret=%d\r\n",ret);
	   return ret;
	}

    bsp_device_power_ctl(DRV_DEV_OLED, DEVICE_POWR_ON);
    usleep(10000);

	ret=bsp_lcd_init();
	if(0!=ret)
	{
	   abn_debug("bsp_lcd_init error ret=%d\r\n",ret);
	   return ret;
	}

	bsp_lcd_ctrl(0x00);
	return ret;
}

void show_lcd_string(int tx_power,int pll_channal_id)
{
    unsigned char buf[1024]={0};
	int pll_freq=0;
	int rc,rc1,rc2,rc3;
    int interfaceNum;
	
	if(0==pll_channal_id)
	{ 
	   pll_freq=5830;
	}
	else
	{
	   pll_freq=5840;
	}

    interfaceNum = get_networkcard_num();   

	logm_debug("show_lcd_string\r\n");
	bsp_clear_oled_row(1, 0x0);
	sprintf(buf,"功率: %d  信道: %d",tx_power,pll_freq);
	rc2=bsp_lcd_show_string(2, 16, buf);
	memset(buf, 0, sizeof(buf));
	logm_debug("ip addr %s\r\n", g_IpBuf);	
	sprintf(buf, "IP: %s", g_IpBuf);
	rc3=bsp_lcd_show_string(2, 32, buf);
	log_debug("show_lcd_string rc1=%d,rc2=%d\r\n",rc1,rc2);
	return;
}
void send_cfg_req_msg(const char *type,const char *action,const char *content)
{
    int rc=0; 
	unsigned char send_buf[512]={0};
    JSON_Value *tmp_value=NULL;
    JSON_Object *tmp_object=NULL;
 
    printf("send_msg type=%s,action=%s,content=%s\r\n",type,action,content);
    
    tmp_value=json_value_init_object();
    tmp_object=tmp_value->value.object;
    json_object_set_string(tmp_object,"type",type);
    json_object_set_string(tmp_object,"action",action);
    if(NULL!=content)
    {
       json_object_set_string(tmp_object,"content",content);
    }
    memset(send_buf,0,sizeof(send_buf));
    rc=json_serialize_to_buffer(tmp_value,send_buf,sizeof(send_buf));
    /*释放*/
    json_value_free(tmp_value);
    printf("json_serialize_to_buffer send_buf = %s \r\n", send_buf);
    zmq_send(req_socket_cfg,send_buf,strlen(send_buf)+1,0);
}
void deal_cfg_raw_msg(unsigned char *recv_buf, int msg_len)
{
    int rc = 0;
    unsigned char ret = 0;
    const char *type = NULL;
    const char *content = NULL;
    char *send_content = NULL;
    int result = 0;
    JSON_Value *cur_value = NULL;
    JSON_Object *cur_object = NULL;
    JSON_Value *rfs_value = NULL;
    JSON_Object *rfs_object = NULL;
    JSON_Value *tmp_value = NULL;
    JSON_Object *tmp_object = NULL;
    JSON_Value *psam_value = NULL;
    JSON_Object *psam_object = NULL;    
    JSON_Value *cur_value_set = NULL;
    JSON_Object *cur_object_set = NULL;
    unsigned int number = 0;
	int tx_power,pll_channelID;
	unsigned char ucPsamFlag = 0;
	int iLoop = 0;
	char aucBuf[30] = {0};
	unsigned int iRet = 0;

    cur_object = parse_string_to_object(recv_buf, &cur_value);
    if(NULL == cur_object)
    {
        logm_debug("NULL Pointer ERROR\r\n");
		abn_debug("NULL Pointer ERROR\r\n");
        return ;
    }
    type = json_object_get_string(cur_object, "type");
	if(0 == strcmp(type, "change_cfg"))
	{
	   logm_debug("recv change_cfg msg\r\n");
	   //send_cfg_req_msg("rfs","request",NULL);
	   send_cfg_req_msg("dispatch","request",NULL);
	}
	else if(0 == strcmp(type, "rfs_ack"))
	{
        result = (int)json_object_get_number(cur_object, "result");
        content = json_object_get_string(cur_object, "content");
        logm_debug("rfs get ack result=%d content:%s\r\n",result, content);

	    if((0!=result)||(NULL==content))
	   	{ 
	   	    abn_debug("result=%d content=0x%x\r\n",result,content);
	   	    json_value_free(cur_value);
	   	    return;
	   	}
        //将content转化为对象，修改其中的值
        rfs_object = parse_string_to_object(content, &rfs_value);
        if(NULL == rfs_object)
        {
            json_value_free(rfs_value);
			abn_debug("rfs_object=0x%x\r\n",rfs_object);
            return;
        }
        
        tx_power= (int)json_object_get_number(rfs_object, "TxPower");
        pll_channelID= (int)json_object_get_number(rfs_object, "PllChannelId");

		logm_debug("tx_power=%d\r\n", tx_power);
		logm_debug("pll_channelID=%d\r\n", pll_channelID);

		//Lcd显示
		show_lcd_string(tx_power,pll_channelID);
        json_value_free(rfs_value);
	}
	else if(0 == strcmp(type, "dispatch_ack"))
	{
	    logm_debug("recv dispatch_ack msg\r\n");
        result = (int)json_object_get_number(cur_object, "result");
        content = json_object_get_string(cur_object, "content");
        logm_debug("dispatch get ack result=%d content:%s\r\n",result, content);

	    if((0!=result)||(NULL==content))
	   	{ 
	   	    abn_debug("result=%d content=0x%x\r\n",result,content);
	   	    json_value_free(cur_value);
	   	    return;
	   	}

        //将content转化为对象，修改其中的值
        tmp_object = parse_string_to_object(content, &tmp_value);
        if(NULL == tmp_object)
        {
            json_value_free(tmp_value);
			abn_debug("dispatch_object=0x%x\r\n",tmp_object);
            return;
        }

        rfs_object = json_object_get_object(tmp_object, "rfs");
        if(NULL == rfs_object)
        {
            json_value_free(tmp_value);
			abn_debug("dispatch_object=0x%x\r\n",rfs_object);
            return;
        }

        tx_power= (int)json_object_get_number(rfs_object, "TxPower");
        pll_channelID= (int)json_object_get_number(rfs_object, "PllChannelId");

		logm_debug("tx_power=%d\r\n", tx_power);
		logm_debug("pll_channelID=%d\r\n", pll_channelID);

		//Lcd显示
		show_lcd_string(tx_power,pll_channelID);
        json_value_free(rfs_value);

        psam_object = json_object_get_object(tmp_object, "psam");
        if(NULL == psam_object)
        {
            json_value_free(tmp_value);
            abn_debug("dispatch_object=0x%x\r\n",psam_object);
            return;
        }
        
        for (iLoop = 0; iLoop < BSP_DRV_PSAM_NR; iLoop++)
        {
            sprintf(aucBuf, "PsamPPS%d", iLoop);
            ucPsamFlag = (unsigned char)json_object_get_number(psam_object, aucBuf);
            logm_debug("PsamPPS%d:%d\r\n", iLoop, ucPsamFlag);
            iRet = bsp_psam_pps_set(iLoop, ucPsamFlag);
            if (0 != iRet)
            {
                logm_debug("set PsamPPS%d:%d fail,errorcode = 0x%x\r\n", iLoop, ucPsamFlag, iRet);
                abn_debug("set PsamPPS%d:%d fail,errorcode = 0x%x\r\n", iLoop, ucPsamFlag, iRet);
            }
        }

        for (iLoop = 0; iLoop < BSP_DRV_PSAM_NR; iLoop++)
        {
            sprintf(aucBuf, "PsamEtu%d", iLoop);
            ucPsamFlag = (unsigned char)json_object_get_number(psam_object, aucBuf);
            logm_debug("PsamEtu%d:%d\r\n", iLoop, ucPsamFlag);
            iRet = bsp_psam_etu_set(iLoop, ucPsamFlag);
            if (0 != iRet)
            {
                logm_debug("set PsamEtu%d:%d fail,errorcode = 0x%x\r\n", iLoop, ucPsamFlag, iRet);
                abn_debug("set PsamEtu%d:%d fail,errorcode = 0x%x\r\n", iLoop, ucPsamFlag, iRet);
            }
        }

	}
    else
    {
        logm_debug("wrong cfg type=%s\r\n", type);
    }
    json_value_free(cur_value);
    return;
}

void deal_cmm_raw_msg(unsigned char *recv_buf, int msg_len)
{
    int rc = 0;
    const char *type = NULL;
    const char *action = NULL;
    JSON_Value *cur_value = NULL;
    JSON_Object *cur_object = NULL;

    JSON_Value *tmp_value=NULL;
    JSON_Object *tmp_object=NULL;
    unsigned char send_buf[512]={0};

    logm_debug("deal_cmm_keepalive_msg content=%s\r\n",recv_buf);

    cur_object = parse_string_to_object(recv_buf, &cur_value);
    if(NULL == cur_object)
    {
        logm_debug("NULL Pointer ERROR\r\n");
		abn_debug("NULL Pointer ERROR\r\n");
        return ;
    }
    type = json_object_get_string(cur_object, "type");
    action = json_object_get_string(cur_object, "action");
	if((0 == strcmp(type, "cmm")) && (0 == strcmp(action, "keepalive")))
	{
	   logm_debug("recv keepalive msg\r\n");
       tmp_value=json_value_init_object();
       tmp_object=tmp_value->value.object;
       json_object_set_string(tmp_object,"type","dispatch");
       json_object_set_string(tmp_object,"action","keepalive_ack");
       
       memset(send_buf,0,sizeof(send_buf));
       rc=json_serialize_to_buffer(tmp_value,send_buf,sizeof(send_buf));
       /*释放*/
       json_value_free(tmp_value);
       logm_debug("json_serialize_to_buffer send_buf = %s \r\n", send_buf);
       zmq_send(req_socket_cmm,send_buf,strlen(send_buf)+1,0);
	}
    else
    {
        logm_debug("wrong cmm type=%s\r\n", type);
    }
    json_value_free(cur_value);

    return;
}


int get_networkcard_num(void)
{
	int    fd;
	int    interfaceNum = 0;
	struct ifreq  buf[16];
	struct ifconf ifc;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
	   perror("socket");
	   close(fd);
	   return -1;
	}
	
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t)buf;
	if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
	{
	   interfaceNum = ifc.ifc_len / sizeof(struct ifreq);
	   DIS_DEBUG("interface num = %d\r\n", interfaceNum);

	}
	return interfaceNum;
}

unsigned int getlocalIp(unsigned char *pucName, unsigned char *pucBuf)  
{  
    int sock_get_ip;  
    char ipaddr[50];  
  
    struct   sockaddr_in *sin;  
    struct   ifreq ifr_ip;     
  
    if ((sock_get_ip = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
         DIS_DEBUG("socket create fail!\r\n");  
         return 1;  
    }  
     
    memset(&ifr_ip, 0, sizeof(ifr_ip));     
    strncpy(ifr_ip.ifr_name, pucName, sizeof(ifr_ip.ifr_name) - 1);     
   
    if( ioctl( sock_get_ip, SIOCGIFADDR, &ifr_ip) < 0 )     
    {   
         DIS_DEBUG("send sock get ip cmd fail!\r\n");  
         return 2;     
    }       
    sin = (struct sockaddr_in *)&ifr_ip.ifr_addr;     
    strcpy(ipaddr,inet_ntoa(sin->sin_addr));         
      
    DIS_DEBUG("local %s ip:%s \r\n",pucName,ipaddr);      
    close( sock_get_ip );  

    memcpy(pucBuf, ipaddr, sizeof(ipaddr));
    return 0;  
}  

int eth_ip_init(int interfacenum, unsigned char *pIpBuf)
{
	int ret;
	int iLen = 0;
    unsigned char aucIpBuf[50];
    unsigned char auceepromIpBuf[4] = {0};
    unsigned char aucEthName[20] = "eth1";

    if (NULL == pIpBuf)
    {
        return 1;
    }

	if(interfacenum > 2)
	{
		if(0 != bsp_eeprom_rcv(EEPROM_ETH1_IP_ADDR, 4, auceepromIpBuf, &iLen))
		{
			DIS_DEBUG("bsp_eeprom_rcv read error\n");
			return 2;
		}
	}

	ret = getlocalIp(aucEthName, aucIpBuf);
	if (0 != ret)
	{
        DIS_DEBUG("bsp_eeprom_rcv getlocalIp error\n");
        return 3;
	}
    sprintf(pIpBuf, "%d.%d.%d.%d",\
        auceepromIpBuf[0], auceepromIpBuf[1], auceepromIpBuf[2], auceepromIpBuf[3]);
    //实际使用ip与eeprom中IP不符合使用实际使用ip
	if (0 != memcmp(aucIpBuf, auceepromIpBuf, 8))
	{
        memcpy(pIpBuf, aucIpBuf, 8);
	}
	
	return 0;
}

void main(int argc, char *argv[])
{
    zmq_pollitem_t  items[5];
    int item_num,sock_timer;
    int rc;
    int recv_len;
    unsigned char recv_buf[1024*2];
	int loop;
	int interfaceNum;

    init_logm("dispatch");
	sock_timer=init_timer();

	rc=bsp_psam_init();
	if(0!=rc)
	{
	    DIS_DEBUG("bsp_drv_psam_init fail , return %d \n", rc);
		abn_debug("bsp_psam_init failed rc:%d",rc);
	}

    rc=bsp_eeprom_init();
	if(0!=rc)
	{
	    DIS_DEBUG("bsp_eeprom_init fail , return %d \n", rc);
		abn_debug("bsp_eeprom_init failed rc:%d",rc);
	}  

	interfaceNum = get_networkcard_num();    

	rc = eth_ip_init(interfaceNum, g_IpBuf);
	if(0 != rc)
	{
	    DIS_DEBUG("eth_ip_init fail , return %d \n", rc);
		abn_debug("eth_ip_init failed rc:%d",rc);
	}

    create_zmq_sockets();

    rc=init_device_ctl();
	if(0!=rc)
	{
	    DIS_DEBUG("init_device_ctl fail , return %d \n", rc);
		abn_debug("init_device_ctl failed rc:%d",rc);
	} 
	
    rc=init_lcd();
	if(0!=rc)
	{
	    DIS_DEBUG("init_lcd fail , return %d \n", rc);
		abn_debug("init lcd failed rc:%d",rc);
		
	}

	//send_cfg_req_msg("rfs","request",NULL);
	send_cfg_req_msg("dispatch","request",NULL);
    items[0].socket = pull_socket_comm;
    items[0].events = ZMQ_POLLIN;
	
    items[1].socket = pull_socket_rfs;
    items[1].events = ZMQ_POLLIN;

	items[2].socket = NULL;
	items[2].fd = sock_timer;
    items[2].events = ZMQ_POLLIN;

	items[3].socket = req_socket_cfg;
    items[3].events = ZMQ_POLLIN;

	items[4].socket = sub_socket_cfg;
    items[4].events = ZMQ_POLLIN;

	items[5].socket = req_socket_cmm;
    items[5].events = ZMQ_POLLIN;

    while(1)
    {
        rc = zmq_poll(items, 5, -1);
        DIS_DEBUG("zmq_poll return , return %d \n", rc);
		if(rc<0)
		{
		    DIS_DEBUG("zmq_poll error: %s \n", zmq_strerror(errno));
			abn_debug("zmq_poll error:%s",zmq_strerror(errno));
			continue;
		}
        memset(recv_buf, 0, sizeof(recv_buf));
        if(items[0].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(pull_socket_comm, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) 
			{
			   abn_debug("zmq_recv error:%s",zmq_strerror(errno));
			   continue;
			}

            DIS_DEBUG("recv from comm pull socket %d bytes recv data:\n", recv_len);
			for(loop=0;loop<recv_len;loop++)
			{
			    logm_debug_raw(" 0x%x ",recv_buf[loop]);
			} 
			logm_debug_raw("\r\n");
            deal_comm_raw_msg(recv_buf, recv_len);
        }
        else if(items[1].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(pull_socket_rfs, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) 
			{
			   abn_debug("zmq_recv error:%s",zmq_strerror(errno));
			   continue;
			}

            DIS_DEBUG("recv from rfs pull socket %d bytes recv data:\n", recv_len);
			for(loop=0;loop<recv_len;loop++)
			{
			    logm_debug_raw(" 0x%x ",recv_buf[loop]);
			} 
			logm_debug_raw("\r\n");
            deal_rfs_raw_msg(recv_buf, recv_len);
        }
		else if(items[2].revents & ZMQ_POLLIN)
        {
            recv_len=read(sock_timer, recv_buf, sizeof(recv_buf));
            if(recv_len < 0) 
			{
			   abn_debug("zmq_recv error:%s",zmq_strerror(errno));
			   continue;
			}

            DIS_DEBUG("recv from timer  socket %d bytes \n", recv_len);
            deal_timer_raw_msg(recv_buf);
        }
		else if(items[3].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(req_socket_cfg, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) 
			{
			   abn_debug("zmq_recv error:%s",zmq_strerror(errno));
			   continue;
			}
            DIS_DEBUG("recv from cfg req socket %d bytes recv data:\n", recv_len);
            deal_cfg_raw_msg(recv_buf, recv_len);
        }
		else if(items[4].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(sub_socket_cfg, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) 
			{
			   abn_debug("zmq_recv error:%s",zmq_strerror(errno));
			   continue;
			}

            DIS_DEBUG("recv from cfg sub socket %d bytes recv data:\n", recv_len);
            deal_cfg_raw_msg(recv_buf, recv_len);
        }
		else if(items[5].revents & ZMQ_POLLIN)
        {
            recv_len = zmq_recv(req_socket_cmm, recv_buf, sizeof(recv_buf), 0);
            if(recv_len < 0) 
			{
			   abn_debug("zmq_recv error:%s",zmq_strerror(errno));
			   continue;
			}

            DIS_DEBUG("recv from cmm req socket %d bytes recv data:\n", recv_len);
            deal_cmm_raw_msg(recv_buf, recv_len);
        }

        else
        {
            DIS_DEBUG("poll error \r\n ");
			abn_debug("poll error\r\n");
        }
    }
}
