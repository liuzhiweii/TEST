#ifndef CLI_H
#define CLI_H

#define CLI_MAX_MSG_LEN 8192

/* 消息队列操作宏定义 */
#define CLI_SEND_MSG(socket,msg,len)   zmq_send (socket, msg, len, 0)
#define CLI_RECV_MSG(socket,buffer,buf_len)   zmq_recv (socket, buffer, buf_len, 0)

#define CLI_RECV_MSG_NOBLOCK(socket,buffer,buf_len)   zmq_recv (socket, buffer, buf_len, 1)


#define CHECK_FAIL_NUMBER(p,s)                             \
do\
{\
    if((p)<0)                                 \
    {                                             \
       printf("%s file:%s line:%u\r\n",s,__FILE__,__LINE__);\
       exit(-1);                                 \
    }\
}while(0)

void *create_zmq_vmm_sockets(void *ctx);
void *create_zmq_cfg_sockets(void *ctx);


#endif
