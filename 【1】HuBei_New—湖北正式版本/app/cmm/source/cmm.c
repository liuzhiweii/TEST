#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/prctl.h>
#include <sys/time.h> 
#include <sys/resource.h>
#include "zmq.h"
#include "zmq_utils.h"
#include "cmm.h"
#include "utimer.h"
#include "logm.h"
#include <time.h>
#include <syslog.h>
#include <abn.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>   
#include <fcntl.h>
#include <errno.h>
#include "bsp/bsp_epld.h"
#include "bsp/bsp_parallel_psam.h"
#include "bsp/bsp_psam.h"
#include "bsp/bsp_led.h"





cmm_ctl_t cmm_ctl;


static cmm_config_t cmm_config[]=
{
    {"cfg","tcp://127.0.0.1:5504", CMM_RESET },
    {"comm","ipc://cmm_comm.ipc", CMM_RESTART},
    {"vm","ipc://cmm_vm.ipc", CMM_DONOTHING},
    {"rfs","ipc://cmm_rfs.ipc", CMM_RESET},
    {"dispatch","ipc://cmm_dispatch.ipc", CMM_DONOTHING},
};





/*���̳�ʼ��*/
static void init_process()
{
    prctl(PR_SET_NAME, "cmm"); /* �������� */
    setpriority(PRIO_PROCESS, getpid(), 1); /* �������ȼ� */
    return;
}

/*cmm��ʼ��*/
static void init_cmm()
{
    int loop=0;
    memset(&cmm_ctl,0,sizeof(cmm_ctl));
    cmm_ctl.module_num=sizeof(cmm_config)/sizeof(cmm_config_t);
    for(loop=0;loop<cmm_ctl.module_num;loop++)
    {
        cmm_ctl.module_cfg[loop].req_socket=NULL;
        memcpy(&cmm_ctl.module_cfg[loop].cmm_cfg,&cmm_config[loop],sizeof(cmm_config_t));
    }
    return;
}

int create_zmq_sockets()
{
    void *ctx=NULL;
    void *req_socket=NULL;
    void *tmp_socket=NULL;
    int value=0;
    int ret=0;
    int loop=0;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        CMM_DEBUG("create context fail!\n");
		abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
        return -1;
    }

    #if 0
    /*������ʱ����Ϣ����*/
    tmp_socket= zmq_socket(ctx, ZMQ_REQ);
    if(NULL == tmp_socket)
    {
        CMM_DEBUG("create tmp_socket fail!\n");
        return -1;
    }
    
    value=0;
    ret =zmq_setsockopt(tmp_socket,ZMQ_LINGER,&value,sizeof(value));
    if(ret < 0)
    {
        CMM_DEBUG("bind zmq_setsockopt ZMQ_LINGER fail\n");
        return -1;
    }
    ret = zmq_connect(tmp_socket, "ipc://timer.ipc");
    if(ret < 0)
    {
        CMM_DEBUG("bind req_socket fail\n");
        return -1;
    }
    cmm_ctl.rep_socket =req_socket;
   #endif
    /*������ģ��REQ��Ϣ����*/
    for(loop=0;loop<sizeof(cmm_config)/sizeof(cmm_config_t);loop++)
    {
        req_socket= zmq_socket(ctx, ZMQ_REQ);
        if(NULL == req_socket)
        {
            CMM_DEBUG("create  req_socket fail!\n");
			abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
            return -1;
        }
        
        value=0;
        ret =zmq_setsockopt(req_socket,ZMQ_LINGER,&value,sizeof(value));
        if(ret < 0)
        {
            CMM_DEBUG("bind zmq_setsockopt ZMQ_LINGER fail\n");
			abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
            return -1;
        }
        value=2000;
        ret =zmq_setsockopt(req_socket,ZMQ_RCVTIMEO,&value,sizeof(value));
        if(ret < 0)
        {
            CMM_DEBUG("bind zmq_setsockopt ZMQ_LINGER fail\n");
			abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
            return -1;
        }
        ret = zmq_connect(req_socket, cmm_config[loop].msg_queue_id);
        if(ret < 0)
        {
            CMM_DEBUG("bind ipc_rep_socket fail\n");
			abn_debug("error:%s errno:%d\r\n",zmq_strerror(errno),errno);
            return -1;
        }
        cmm_ctl.module_cfg[loop].req_socket =req_socket;
    }
    return 0;
}

/*ת��string���͵�json Ϊ����*/
JSON_Object *parse_string_to_object(const char *strings,JSON_Value **string_value)
{
    JSON_Object *tmp_object=NULL;
    JSON_Value *tmp_value=NULL;
    CMM_DEBUG("parse_string_to_object \r\n");
 
    /* ����Ĭ������ */
    tmp_value= json_parse_string(strings);
    *string_value = NULL;
    if(NULL==tmp_value)
    {
       CMM_DEBUG("(parse_string_to_object) error null pointer\r\n");
	   abn_debug("null pointer error\r\n");
       return NULL;
    }

   if(json_value_get_type(tmp_value) == JSONObject)
   {
      tmp_object = json_value_get_object(tmp_value);
      *string_value = tmp_value;
   }
   else
   {
       abn_debug("error! not an object type=%d\r\n",json_value_get_type(tmp_value));
       CMM_DEBUG("error! not an object type=%d\r\n",json_value_get_type(tmp_value));
       json_value_free(tmp_value);
       *string_value=NULL;
       return NULL;
   }
  
    return tmp_object;
}



/*������Ӧ��Ϣ*/
void send_keepalive_msg(const char *type,const char *action,void *req_socket)
{
    int rc=0;     
    JSON_Value *tmp_value=NULL;
    JSON_Object *tmp_object=NULL;

    if((NULL==type)&&(NULL==action)&&(NULL==req_socket))
    {
        CMM_DEBUG("null pointer\r\n");
		abn_debug("null pointer error\r\n");
        return;
    }
 
    CMM_DEBUG("send_keepalive_msg type=%s action=%s\r\n",type,action);
    
    tmp_value=json_value_init_object();
    tmp_object=tmp_value->value.object;
    json_object_set_string(tmp_object,"type",type);
    json_object_set_string(tmp_object,"action",action);
    memset(cmm_ctl.send_buf,0,sizeof(cmm_ctl.send_buf));
    rc=json_serialize_to_buffer(tmp_value,cmm_ctl.send_buf,CMM_MAX_MSG_LEN);
    /*�ͷ�*/
    json_value_free(tmp_value);
    CMM_DEBUG("json_serialize_to_buffer send_buf = %s \r\n", cmm_ctl.send_buf);
    CMM_SEND_MSG(req_socket,cmm_ctl.send_buf,strlen(cmm_ctl.send_buf)+1);
}

void deal_keepalive_response_msg(int module_index,void *req_socket)
{
    /*��Ϣ̫��ʹ�ñ���������*/
    int rc=0;
    const char *tpye=NULL;
    const char *action=NULL;
    JSON_Object *cur_object=NULL;
    JSON_Value *cur_value=NULL;
    CMM_DEBUG("deal_keepalive_response_msg\r\n");
    memset(cmm_ctl.recv_buf,0,sizeof(cmm_ctl.recv_buf));
    rc=zmq_recv(req_socket,cmm_ctl.recv_buf,CMM_MAX_MSG_LEN,0);
    if(rc<0)
    {
        /*�����쳣*/
        if(CMM_RESET==cmm_ctl.module_cfg[module_index].cmm_cfg.process_mode)
        {
            /*��λ*/
            CMM_DEBUG("CMM_RESET\r\n");
			log_debug("module_name:%s RESET\r\n",cmm_ctl.module_cfg[module_index].cmm_cfg.module_name);
            //system("reboot");
        }
        else if(CMM_RESTART==cmm_ctl.module_cfg[module_index].cmm_cfg.process_mode)
        {
            /*������ģ��*/
            CMM_DEBUG("CMM_RESTART\r\n");
            CMM_DEBUG("module_name:%s RESTART\r\n",cmm_ctl.module_cfg[module_index].cmm_cfg.module_name);
			log_debug("module_name:%s RESTART\r\n",cmm_ctl.module_cfg[module_index].cmm_cfg.module_name);
            execl(cmm_ctl.module_cfg[module_index].cmm_cfg.module_name,NULL);
        }
        else
        {
            log_debug("module_name:%s DONOTHING\r\n",cmm_ctl.module_cfg[module_index].cmm_cfg.module_name);
            CMM_DEBUG("CMM_DONOTHING\r\n");
            CMM_DEBUG("module_name:%s DONOTHING\r\n",cmm_ctl.module_cfg[module_index].cmm_cfg.module_name);
        }
        
        return;
    }
    cur_object = parse_string_to_object(cmm_ctl.recv_buf,&cur_value);
    tpye=json_object_get_string(cur_object,"type");
    action=json_object_get_string(cur_object,"action");
    CMM_DEBUG("receive keepalive response type=%s action=%s\r\n",tpye,action);
    json_value_free(cur_value);
}
void check_log_file()
{
   int ret,fd,size;
   struct stat f_stat;
   fd = open((const char *)LOG_FILE_PATH, O_RDONLY);
   if (0 > fd)
   {
      CMM_DEBUG("log file not exist\r\n");
	  abn_debug("log file not exist\r\n");
	  return;
   }
   ret = fstat(fd, &f_stat);
   size = f_stat.st_size;
   CMM_DEBUG("log size:%d\r\n", f_stat.st_size);
   if (ret < 0)
   {
       CMM_DEBUG("check file size error errno=%d\r\n",errno);
	   abn_debug("check file size error errno=%d\r\n",errno);
	   return;
   }
   if(size>=LOG_FILE_MAX_SIZE)
   {
       //��Ҫ�����ļ������Ȳ鿴�ļ��Ƿ����
       ret=access(LOG_BAK_FILE_PATH, 0);
	   if(0==ret)
	   {
	      remove(LOG_BAK_FILE_PATH);
	   }
	   rename(LOG_FILE_PATH, LOG_BAK_FILE_PATH);
   }
   return;
}
unsigned int  light_led_run(unsigned int dwState)
{
    if (0 != dwState)
    {
        dwState = 1;
    }

    (void)bsp_led_run_ctl(dwState);

    return 0;
}

unsigned int  light_led_psam(unsigned int dwState)
{

    if (0 != dwState)
    {
        dwState = 1;
    }

    (void)bsp_led_psam_ctl(dwState);

    return 0;


}
void check_psam_and_light()
{
   int loop,rc;
   T_CardPara card_para;
   unsigned int psam_error_code;
   
   for(loop=0;loop<4;loop++)
   	{
   	   rc=bsp_psam_active(loop,&card_para,&psam_error_code);
	   if(0==rc)
	   {
	       break;
	   }
	   
   	}
    if(4==loop)
    {
       logm_debug("psam not in position\r\n");
       light_led_psam(0);
    }
	else
	{
	   logm_debug("psam in position psamID=%d\r\n",loop);
	   light_led_psam(1);
	}
	return;
}

void deal_timer_func()
{
    int loop=0;
	//check_psam_and_light();
	check_log_file();
	
    for(loop=0;loop<cmm_ctl.module_num;loop++)
    {
        send_keepalive_msg("cmm","keepalive",cmm_ctl.module_cfg[loop].req_socket);
        deal_keepalive_response_msg(loop,cmm_ctl.module_cfg[loop].req_socket);
    }
}


int main(int argc, char *argv[])
{
    int rc,ret_timerid;
	int socket_timer;
    init_process();
    init_cmm();
	init_logm("cmm");
    create_zmq_sockets();


	 //��־
    char buf[128]={0};
	sprintf(buf,"syslogd -O %s ","/etc/log.txt");
    //system(buf);
	//openlog("cmm", LOG_PID, LOG_DEBUG|LOG_USER);
	//setlogmask(LOG_ERR);

	//����run��
	bsp_epld_init();
	bsp_psam_init();
	bsp_led_initl();
	light_led_run(1);
	check_psam_and_light();
	socket_timer = init_timer();
    if(socket_timer < 0)
    {
        printf("timer process not exist, exit now!\n");
		abn_debug("init_timer error\r\n");
        exit(-1);
    }

	set_timer(CMM_KEEPALIVE_TIMER_ID, CMM_KEEPALIVE_TIMER_INTERVAL, 0, TIMER_PERSIST);
    #if 0
    while(1)
    {
        rc=read(socket_timer, &ret_timerid, sizeof(int));
		if(rc<=0)
		{
		   CMM_DEBUG("read error rc=%d\r\n",rc);
		   abn_debug("read error rc=%d\r\n",rc);
		   continue;
		}
		if(CMM_KEEPALIVE_TIMER_ID==ret_timerid)
	    {
	       deal_timer_func();
	    }
        //sleep(10);
    }
    #endif
    close_timer();
    return 0;
 }

