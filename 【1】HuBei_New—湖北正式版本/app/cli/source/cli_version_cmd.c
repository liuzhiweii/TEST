/**
 * \file     test_parser.c
 * \brief    Test program for parser library. 
 * \details  This is a test program with a simple CLI that serves as a demo 
 *           as well.
 * \version  \verbatim $Id: test_parser.c 33 2009-01-22 06:45:33Z henry $ \endverbatim
 */
/*
 * Copyright (c) 2008-2009, Henry Kwok
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the project nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY HENRY KWOK ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL HENRY KWOK BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "cparser.h"
#include "cparser_token.h"
#include "parson.h"
#include "cli.h"
#include "cli_version.h"



extern void *req_socket_vmm;
extern void *ctx;
void SetErr(unsigned short int ErrorNum)
{

	switch(ErrorNum)
	{
		case TFTP_ERR_NOT_DEFINED:
			printf("TFTP Not defined, see error message (if any).\n");		
			break;
		case TFTP_FILE_NOT_FOUND:
			printf("TFTP Local Error: File not found.");
			break;
		case TFTP_FILE_ACCESS_VIOLATION:
			printf("TFTP Access violation.\n");
			break;
		case TFTP_DISK_FULL:
			printf("TFTP Disk full or allocation exceeded.\n");
			break;
		case TFTP_ILLEGAL_OPERATION:
			printf("TFTP Illegal TFTP operation mode.\n");
			break;
		case TFTP_UNKNOWN_TRANSFER_ID:
			printf("TFTP Unknown transfer ID.\n");
			break;
		case TFTP_FILE_ALREADY_EXIST:
			printf("TFTP Server Error: File already exists.\n");
			break;
		case TFTP_NO_SUCH_USER:
			printf("TFTP No such user.\n");
			break;
		case TFTPSOCK_SELECT_TIMEOUT_ERR:
			printf("TFTP timeout! please check the IP and port and ensure the tftp server is open.\n");
			break;
		case TFTPSOCK_CREATE_ERR:
			printf("TFTP create socket error\n");
			break;
		case TFTPSOCK_SEND_CMD_ERR:
			printf("TFTP send commad error\n");
			break;
		case TFTPSOCK_SELECT_ERR:
			printf("TFTP select error\n");
			break;
		case TFTPSOCK_RECV_DATA_ERR:
			printf("TFTP recv data error\n");
			break;	
		case FTP_CONNECT_ERR:
			printf("FTP connect error! please check the FTP server whether or not ready\n");		
			break;
		case FTP_LOGIN_ERR:
			printf("FTP login error! please check the login name and password\n ");
			break;
		case FTP_FILE_ACCESS_ERR:
			printf("FTP file access error! please ensure the file exist\n ");
			break;
		case FTP_FILE_SIZE_ERR:
			printf("FTP check the file size error! please check the file is or not exist \n");
			break;
		case FTP_FILE_READ_ERR:
			printf("FTP read version file error!\n");
			break;
		case FTP_FILE_LESS_THAN_FIXED_LEN:
			printf("FTP check the file error! the file length is less than 128 \n");
			break;
		case FTP_FILE_INFO_PARSE_ERR:
			printf("FTP parse the version info error! please check the version info\n");
			break;
		case FTP_FILE_WRITE_ERR:
			printf("Ftp version file read error or write error to flash\n");
			break;
		case FTP_FILE_SIZE_NOT_MATCH_INFOSIZE:
			printf("Ftp version file size is not match the size decriped in the version info\n");
			break;
		case FTP_EERPOM_READ_ERR:
			printf("Ftp EEPROM read error\n");
			break;
		case FTP_EERPOM_WRITE_ERR:
			printf("Ftp EEPROM write error\n");
			break;
		case VERSION_SWITCH_DONE_BEFORE:
			printf("Ftp version has been switched done before\n");
			break;
		case VERSION_UNSWITCH_DONE_BEFORE:
			printf("Ftp version has been unswitched done before\n");
			break;
			
	}
}


cparser_result_t cparser_cmd_version_exit(cparser_context_t *context)
{
    assert(context && context->parser);
	return cparser_submode_exit(context->parser);
}	

cparser_result_t cparser_cmd_version_download_version_ServerType_VersionType_VersionName_ServerIP_Port_UserName_PassWord(cparser_context_t *context,
    char **ServerType_ptr,
    char **VersionType_ptr,
    char **VersionName_ptr,
    uint32_t *ServerIP_ptr,
    uint32_t *Port_ptr,
    char **UserName_ptr,
    char **PassWord_ptr)

{
	int rc=0;
	int loop=0;
	int result=0;
    char recv_buf[1024]={0};
	char send_buf[1024]={0};
	message_head_t message_head;
    vmm_version_download_t vmm_version_download;
	version_ack_t *version_ack;
    assert(context && ServerType_ptr &&VersionType_ptr&& VersionName_ptr && *ServerType_ptr && 
    *VersionName_ptr &&*VersionType_ptr&& ServerIP_ptr && Port_ptr);
	memset(&vmm_version_download,0,sizeof(vmm_version_download));
	if(0==strcmp(*ServerType_ptr,"tftp"))
	{
	    //tftp
	    vmm_version_download.vmm_server_info.server_type = 0;
		vmm_version_download.vmm_server_info.server_info.tftpServer.serverip=*ServerIP_ptr;
		vmm_version_download.vmm_server_info.server_info.tftpServer.serverport=(unsigned short)*Port_ptr;
		strcpy(vmm_version_download.vmm_file_info.version_name,*VersionName_ptr);
	}
	else if(0==strcmp(*ServerType_ptr,"ftp"))
	{
	    //ftp
	    vmm_version_download.vmm_server_info.server_type = 1;
		vmm_version_download.vmm_server_info.server_info.ftpServer.serverip=*ServerIP_ptr;
		vmm_version_download.vmm_server_info.server_info.ftpServer.serverport=(unsigned short)*Port_ptr;
		assert(UserName_ptr&&*UserName_ptr&&PassWord_ptr&&*PassWord_ptr);
		strcpy(vmm_version_download.vmm_server_info.server_info.ftpServer.username,*UserName_ptr);
		strcpy(vmm_version_download.vmm_server_info.server_info.ftpServer.userpassw,*PassWord_ptr);
		strcpy(vmm_version_download.vmm_file_info.version_name,*VersionName_ptr);
	}
	else
	{
	    printf("Server type is not support\r\n");
	}
	if(0==strcmp(*VersionType_ptr,"app"))
	{
	    //app
	    vmm_version_download.vmm_server_info.version_tye= 1;
	}
	else if(0==strcmp(*VersionType_ptr,"system"))
	{
	    //system
	    vmm_version_download.vmm_server_info.version_tye= 0;
	}
	else
	{
	    printf("version type is not support\r\n");
	}
	
	message_head.message_id=VERSION_DOWNLOAD;
	message_head.message_body_len=sizeof(vmm_version_download_t);

    memset(send_buf,0,sizeof(send_buf));
	memcpy(send_buf,&message_head,sizeof(message_head));
	memcpy(send_buf+sizeof(message_head),&vmm_version_download,sizeof(vmm_version_download));
	
	//发送消息给vmm
	rc=CLI_SEND_MSG(req_socket_vmm,send_buf,sizeof(vmm_version_download)+sizeof(message_head));
	if(rc<0)
	{
	    printf("zmq send fail,download version fail errno=%d\r\n",errno);
		return CPARSER_NOT_OK;
	}

	//接收消息响应
	for(loop=0;loop<60;loop++)
	{
	    rc=CLI_RECV_MSG_NOBLOCK(req_socket_vmm,recv_buf,sizeof(recv_buf));
		if(rc>0)
		{
		    version_ack=(version_ack_t *)recv_buf;
			if((VERSION_DOWNLOAD==version_ack->message_head.message_id)&&(0==version_ack->return_value.result))
			{
				printf("\r\ndownload version succcess\r\n");
			}
		    else
			{
				printf("\r\ndownload version fail result is %d\r\n",version_ack->return_value.result);
				SetErr(version_ack->return_value.result);
			}
			break;
		}
		else 
		{
		    printf("*");
			fflush(0);
			sleep(3);
		}
	}
	if(60==loop)
	{
	    zmq_close(req_socket_vmm);
		req_socket_vmm=create_zmq_vmm_sockets(ctx);
	    printf("\r\ndownload version failed\r\n");
	}
	return CPARSER_OK;
	//CLI_RECV_MSG(req_socket_vmm,recv_buf,sizeof(recv_buf));
}
cparser_result_t cparser_cmd_version_query(cparser_context_t *context)
{
	int rc=0;
	int loop=0;
	int result=0;
    char recv_buf[512]={0};
	char send_buf[512]={0};
	message_head_t message_head;
	version_ack_t *version_ack;
	version_info_query_t *version_info_query;
    assert(context);
	memset(&message_head,0,sizeof(message_head));
	
	message_head.message_id=VERSION_QUERY;
	message_head.message_body_len=0;

    memset(send_buf,0,sizeof(send_buf));
	memcpy(send_buf,&message_head,sizeof(message_head));
	
	//发送消息给vmm
	rc=CLI_SEND_MSG(req_socket_vmm,send_buf,sizeof(message_head));
	if(rc<0)
	{
	    printf("zmq send fail,query version fail errno=%d\r\n",errno);
		return CPARSER_NOT_OK;
	}

	//接收消息响应
	for(loop=0;loop<10;loop++)
	{
	    rc=CLI_RECV_MSG_NOBLOCK(req_socket_vmm,recv_buf,sizeof(recv_buf));
		if(rc>0)
		{
		    version_ack=(version_ack_t *)recv_buf;
			if(VERSION_QUERY!=version_ack->message_head.message_id)
			{
				printf("\r\nnot query version msg continue msgid=%d\r\n",version_ack->message_head.message_id);
				continue;
			}
			if(0==version_ack->return_value.result)
			{
			    version_info_query=(version_info_query_t *)(version_ack+1);
				printf("\r\nquery version succcess\r\n");
				printf("system version:\r\n");
				printf("version   switched   isrunning\r\n");
				printf("V%d.%d.%d   %s   %s\r\n",version_info_query->sys_ver_status[0].sys_ver_num[0],
					version_info_query->sys_ver_status[0].sys_ver_num[1],
					version_info_query->sys_ver_status[0].sys_ver_num[2],
					(version_info_query->sys_ver_status[0].sys_ver_status==0?"NO":"YES"),
					(version_info_query->sys_ver_running==0?"YES":"NO"));
				printf("V%d.%d.%d   %s   %s\r\n",version_info_query->sys_ver_status[1].sys_ver_num[0],
					version_info_query->sys_ver_status[1].sys_ver_num[1],
					version_info_query->sys_ver_status[1].sys_ver_num[2],
					(version_info_query->sys_ver_status[1].sys_ver_status==0?"NO":"YES"),
					(version_info_query->sys_ver_running==1?"YES":"NO"));
				printf("\r\napp version:\r\n");
				printf("the running version number:V%d.%d.%d\r\n",version_info_query->app_ver_running_num[0],
					  version_info_query->app_ver_running_num[1],
					  version_info_query->app_ver_running_num[2]);
				if((0==version_info_query->app_ver_download_num[0])&&(0==version_info_query->app_ver_download_num[1])&&(0==version_info_query->app_ver_download_num[2]))
				{
				 	printf("no downlaod version\r\n");
				}
				else
			    {
			    	printf("\r\nthe download version number:V%d.%d.%d\r\n",version_info_query->app_ver_download_num[0],
					  version_info_query->app_ver_download_num[1],
					  version_info_query->app_ver_download_num[2]);
			    }
				
			}
		    else
			{
				printf("\r\nquery version fail result is %d\r\n",version_ack->return_value.result);
				SetErr(version_ack->return_value.result);
			}
			break;
		}
		else 
		{
		    printf("*");
			fflush(0);
			sleep(3);
		}
	}
	if(10==loop)
	{
	    zmq_close(req_socket_vmm);
		req_socket_vmm=create_zmq_vmm_sockets(ctx);
	    printf("\r\nquery version failed\r\n");
	}
	return CPARSER_OK;
	//CLI_RECV_MSG(req_socket_vmm,recv_buf,sizeof(recv_buf));
}	
cparser_result_t cparser_cmd_version_switch(cparser_context_t *context)
{
	int rc=0;
	int loop=0;
	int result=0;
	char recv_buf[512]={0};
	char send_buf[512]={0};
	message_head_t message_head;
	version_ack_t *version_ack;
	assert(context);
	memset(&message_head,0,sizeof(message_head));
	
	message_head.message_id=VERSION_SWITCH;
	message_head.message_body_len=0;

	memset(send_buf,0,sizeof(send_buf));
	memcpy(send_buf,&message_head,sizeof(message_head));
	
	//发送消息给vmm
	rc=CLI_SEND_MSG(req_socket_vmm,send_buf,sizeof(message_head));
	if(rc<0)
	{
		printf("zmq send fail,query version fail errno=%d\r\n",errno);
		return CPARSER_NOT_OK;
	}

	//接收消息响应
	for(loop=0;loop<10;loop++)
	{
		rc=CLI_RECV_MSG_NOBLOCK(req_socket_vmm,recv_buf,sizeof(recv_buf));
		if(rc>0)
		{
			version_ack=(version_ack_t *)recv_buf;
			if(VERSION_SWITCH!=version_ack->message_head.message_id)
			{
				printf("\r\nnot query version msg continue msgid=%d\r\n",version_ack->message_head.message_id);
				continue;
			}
			if(0==version_ack->return_value.result)
			{
				printf("\r\nswitch version succcess\r\n");
			}
			else
			{
				printf("\r\nswitch version fail result is %d\r\n",version_ack->return_value.result);
				SetErr(version_ack->return_value.result);
			}
			break;
		}
		else 
		{
			printf("*");
			fflush(0);
			sleep(3);
		}
	}
	if(10==loop)
	{
		zmq_close(req_socket_vmm);
		req_socket_vmm=create_zmq_vmm_sockets(ctx);
		printf("\r\nswitch version failed\r\n");
	}
	return CPARSER_OK;
	//CLI_RECV_MSG(req_socket_vmm,recv_buf,sizeof(recv_buf));
}

cparser_result_t cparser_cmd_version_unswitch(cparser_context_t *context)
{
	int rc=0;
	int loop=0;
	int result=0;
	char recv_buf[512]={0};
	char send_buf[512]={0};
	message_head_t message_head;
	version_ack_t *version_ack;
	assert(context);
	memset(&message_head,0,sizeof(message_head));
	
	message_head.message_id=VERSION_UNSWITCH;
	message_head.message_body_len=0;

	memset(send_buf,0,sizeof(send_buf));
	memcpy(send_buf,&message_head,sizeof(message_head));
	
	//发送消息给vmm
	rc=CLI_SEND_MSG(req_socket_vmm,send_buf,sizeof(message_head));
	if(rc<0)
	{
		printf("zmq send fail,query version fail errno=%d\r\n",errno);
		return CPARSER_NOT_OK;
	}

	//接收消息响应
	for(loop=0;loop<10;loop++)
	{
		rc=CLI_RECV_MSG_NOBLOCK(req_socket_vmm,recv_buf,sizeof(recv_buf));
		if(rc>0)
		{
			version_ack=(version_ack_t *)recv_buf;
			if(VERSION_UNSWITCH!=version_ack->message_head.message_id)
			{
				printf("\r\nnot query version msg continue msgid=%d\r\n",version_ack->message_head.message_id);
				continue;
			}
			if(0==version_ack->return_value.result)
			{
				printf("\r\nunswitch version succcess\r\n");
			}
			else
			{
				printf("\r\nunswitch version fail result is %d\r\n",version_ack->return_value.result);
				SetErr(version_ack->return_value.result);
			}
			break;
		}
		else 
		{
			printf("*");
			fflush(0);
			sleep(3);
		}
	}
	if(10==loop)
	{
		zmq_close(req_socket_vmm);
		req_socket_vmm=create_zmq_vmm_sockets(ctx);
		printf("\r\nunswitch version failed\r\n");
	}
	return CPARSER_OK;
	//CLI_RECV_MSG(req_socket_vmm,recv_buf,sizeof(recv_buf));
}

cparser_result_t cparser_cmd_version_help_filter(cparser_context_t *context,
    char **filter_ptr)
	{
		assert(context);
		return cparser_help_cmd(context->parser, filter_ptr ? *filter_ptr : NULL);
	}





