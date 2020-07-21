#ifndef CLI_VERSION_H
#define CLI_VERSION_H

#define TFTP_ERR_NOT_DEFINED 			1 
#define TFTP_FILE_NOT_FOUND				2
#define TFTP_FILE_ACCESS_VIOLATION		3
#define TFTP_DISK_FULL   				4
#define TFTP_ILLEGAL_OPERATION			5
#define TFTP_UNKNOWN_TRANSFER_ID		6
#define	TFTP_FILE_ALREADY_EXIST			7
#define	TFTP_NO_SUCH_USER				8
#define TFTPSOCK_SELECT_TIMEOUT_ERR  	9
#define TFTPSOCK_CREATE_ERR           	10
#define TFTPSOCK_SEND_CMD_ERR         	11 
#define TFTPSOCK_SELECT_ERR   	      	12 
#define TFTPSOCK_RECV_DATA_ERR        	13

#define FTP_CONNECT_ERR       	           20
#define FTP_LOGIN_ERR			           21
#define FTP_FILE_ACCESS_ERR		           22
#define FTP_FILE_READ_ERR                  23
#define FTP_FILE_LESS_THAN_FIXED_LEN       24     /*the length of system file on the ftp server less than 128 */
#define FTP_FILE_SIZE_ERR                  25
#define FTP_FILE_INFO_PARSE_ERR            26
#define FTP_FILE_WRITE_ERR            	   27
#define FTP_FILE_SIZE_NOT_MATCH_INFOSIZE   28
#define FTP_EERPOM_READ_ERR                29
#define FTP_EERPOM_WRITE_ERR               30
#define VERSION_SWITCH_DONE_BEFORE         41
#define VERSION_UNSWITCH_DONE_BEFORE       42


#define VERSION_DOWNLOAD        		1
#define VERSION_QUERY              		2
#define VERSION_SWITCH                  3
#define VERSION_UNSWITCH                4

typedef struct message_head
{
	int    message_id;
	int    message_body_len;
}message_head_t;



typedef struct return_value
{
	unsigned int 		result;   /*0:success  others:errornum*/
}return_value_t;


typedef struct version_ack
{
	message_head_t		message_head;  
	return_value_t      return_value;
}version_ack_t;


typedef struct vmm_file_info
{
	unsigned char     version_name[32];
	
}vmm_file_info_t;

typedef struct Ftp_Server
{
    unsigned int        serverip;             /* Ftp serverip address*/  
	unsigned short int  serverport;           /* Ftp server port */
    unsigned short int  wPad;
    unsigned char       username[32];        /* user name */
    unsigned char       userpassw[32];       /* password*/
}Ftp_Server_t;

/* tftp服务器信息 */
typedef struct Tftp_Server
{
    unsigned int        serverip;              /* Tftp server ip address*/  
	unsigned short int  serverport;            /* Tftp server port*/
    unsigned short int  wPad;
}Tftp_Server_t;


typedef union server_socket
{
    Ftp_Server_t     ftpServer;       /* ftp server*/    
    Tftp_Server_t    tftpServer;      /* tftp server*/   
}server_socket_t;


typedef struct vmm_server_info
{
	char              server_type;    /*0:TFTP server 1:FTP server*/
	char              version_tye;    /*0:system version 1:app version*/
	char              pad[2];
	server_socket_t   server_info;	
}vmm_server_info_t;

typedef struct version_status
{
	unsigned char sys_ver_num[3];       		/*system verion number*/
	unsigned char sys_ver_status;      			/*system status  0:ok  1:to be switched  2:err*/
}version_status_t;

typedef struct version_info_query
{
	unsigned char		sys_ver_running;        /*running version 0:system_version_0  1:system_version_1*/
	unsigned char 		sys_ver_switchedstatus; /*switched status 0:not switched 1:switched*/
	unsigned char		pad[2];
	version_status_t 	sys_ver_status[2];      /*verstatus[0] :system_version_0   verstatus[1]:system_version_1 */
	unsigned char 		app_ver_running_num[3];
	unsigned char 		padc1;
	unsigned char 		app_ver_download_num[3];
	unsigned char 		padc2;
}version_info_query_t;

typedef struct vmm_version_download
{
	vmm_server_info_t vmm_server_info;
	vmm_file_info_t vmm_file_info;
 }vmm_version_download_t;

/* 消息队列操作宏定义 */


#endif
