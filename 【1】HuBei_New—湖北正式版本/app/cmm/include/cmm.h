/************************************************************************

************************************************************************/
#ifndef _CMM_H
#define _CMM_H

#include "parson.h"

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
/* 消息队列操作宏定义 */
#define CMM_SEND_MSG(socket,msg,len)   zmq_send (socket, msg, len, 0);


/* 关键字的最大长度 */
#define CMM_MAX_NAME_LEN     (64)
#define CMM_MAX_MSG_LEN      (256)

/*最大的模块数*/
#define CMM_MAX_MODULE_NUM     (10)

/*和各模块之间的保活定时器ID*/
#define CMM_KEEPALIVE_TIMER_ID     (1)
#define CMM_KEEPALIVE_TIMER_INTERVAL (20)

#define LOG_FILE_MAX_SIZE (100000)
#define LOG_FILE_PATH "/opt/log.txt"
#define LOG_BAK_FILE_PATH "/opt/log_bak.txt"




#define CMM_DEBUG logm_debug
#define CHECK_NULL_POINTER_RETURN_INT(p)\
do\
{\
    if(NULL==(p))                                 \
    {                                             \
       CMM_DEBUG("null pointer error file:%s line:%u\r\n",__FILE__,__LINE__);\
       return -1;                                 \
    }\
}while(0)
#define CHECK_NULL_POINTER_RETURN_void(p)\
    do\
    {\
        if(NULL==(p))                                 \
        {                                             \
           CMM_DEBUG("null pointer error file:%s line:%u\r\n",__FILE__,__LINE__);\
           return ;                                 \
        }\
    }while(0)

#define CHECK_NONZERO_NUMBER(p)                               \
do\
{\
    if(0!=(p))                                 \
    {                                             \
       CMM_DEBUG("nonzero error file:%s line:%u\r\n",__FILE__,__LINE__);\
       return -1;                                 \
    }\
}while(0)

enum 
{
  CMM_RESET,
  CMM_RESTART,
  CMM_DONOTHING
};


/**************************************************************************
 *                            数据类型                                    *
 **************************************************************************/
typedef struct tag_cmm_config_t 
{
    const char module_name[CMM_MAX_NAME_LEN]; //模块名
    const char msg_queue_id[CMM_MAX_NAME_LEN]; //模块对应消息队列ID
    int   process_mode; //保活失败后的处理方式
}cmm_config_t;

typedef struct tag_module_cfg_t 
{
    void *req_socket;
    cmm_config_t cmm_cfg;
}module_cfg_t;

typedef struct tag_cmm_ctl_t 
{
    int module_num;
    module_cfg_t module_cfg[CMM_MAX_MODULE_NUM];
    char send_buf[CMM_MAX_MSG_LEN];
    char recv_buf[CMM_MAX_MSG_LEN];
    void *rep_socket;
}cmm_ctl_t;



/**************************************************************************
 *                             类声明                                      *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/
 
/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
  
#endif  /* _OAM_CMP_H */

