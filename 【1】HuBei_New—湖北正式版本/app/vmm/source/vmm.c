#include "vmm.h"

static void *zmq_context  	 = NULL;
static void *rep_to_dealer   = NULL;
static void *proxy_frontend  = NULL;
static void *proxy_backend   = NULL;
static void *rep_for_pc      = NULL;

static int   errornum        = -1;

static int   mtdfd           = -1;

static char                  sysstartflag;

static download_info_t       downloadinfo;

static version_query_info_t  verqueryinfo;

static version_status_t      initversionstatus;

mtdblock_size_t \
	mtdblockinfo[11] = {
						{0,     0x0,           0x80000 , 	"/dev/mtdblock0"},		/*uboot	A*/
						{1,     0x80000,       0x80000 , 	"/dev/mtdblock1"},		/*uboot	B*/
						{2,     0xF0100000,    0x20000 , 	"/dev/mtdblock2"},		/*dtb A*/
						{3,     0xF0120000,    0x2E0000, 	"/dev/mtdblock3"},		/*linux A*/
						{4,     0xF0400000,    0xA00000, 	"/dev/mtdblock4"},		/*ramdisk A*/
						{5,     0xF0E00000,    0x20000 , 	"/dev/mtdblock5"},		/*dtb B*/
						{6,     0xF0E20000,    0x2E0000, 	"/dev/mtdblock6"},		/*linux B*/
						{7,     0xF1100000,    0xA00000, 	"/dev/mtdblock7"},		/*ramdisk B*/
						{8,     0xF1B00000,    0x500000, 	"/dev/mtdblock8"},		/*APP*/
						{9,     0xF2000000,    0x200000, 	"/dev/mtdblock9"},		/*data*/
						{10,    0xF2200000,    0x1e00000 , 	"/dev/mtdblock10"},		/*reserved B*/
	                   };


unsigned int digit_check(const char * str)
{
	if (NULL == str)
		return ERR;
	while(*str)
		{
			if(isdigit(*str))
			{
				str++;
				continue;
			}
			else
			{
				return ERR;
			}
		}

	return SUCCESS;
}

unsigned int parse_sys_ver_info(char *buf,char * vernum,int *linuxsize,\
									int *ramdisksize,int *dtbsize)
{

	char 	verinfo[128];
	char 	*cur;
	char 	*token;
	int  	numcount;
	int  	size[3];

	/*parse start*/
	memmove(verinfo,buf + sizeof(message_head_t) + sizeof(pd_version_info_t), sizeof(verinfo));

	cur = verinfo;

	if(NULL == (token=strsep(&cur,"[")))
	{
		return ERR;
	}

	/*parse version number*/
	for(numcount = 0;numcount < 3; numcount ++)
	{
		if(NULL!=(token=strsep(&cur,".]")))
		{
			if(SUCCESS != digit_check(token))
			{
				return ERR;
			}
			else
			{
				*vernum++ = atoi(token);
				downloadinfo.sysno[numcount] = atoi(token);
			}
		}
		else
			return ERR;
	}

	/*parse boot version size & linux version size & ramdisk size*/
	for(numcount = 0;numcount < 3; numcount ++)
	{
		if(NULL != (token=strsep(&cur,"[")))
		{
			if(NULL != (token=strsep(&cur,"]")))
			{
				if(SUCCESS != digit_check(token))
				{
					return ERR;
				}
				else
				{
					size[numcount] = atoi(token);
				}
			}
			else
				return ERR;
		}
		else
			return ERR;
	}
	*linuxsize    = size[0];
	*ramdisksize  = size[1];
	*dtbsize      = size[2];

	downloadinfo.linuxsize   = size[0];
	downloadinfo.ramdisksize = size[1];
	downloadinfo.dtbsize     = size[2];

	return SUCCESS;

}

unsigned int parse_app_ver_info(char *buf)
{
	char 			verinfo[24];
	char 			*cur;
	char 			*token;
	int  			numcount;
	char            vernum[3];
	char 			*pv=vernum;

	memmove(verinfo, buf + sizeof(message_head_t) + sizeof(pd_version_info_t), sizeof(verinfo));

	cur = verinfo;

	if(NULL == (token=strsep(&cur,"v")))
	{
		return errornum=VER_INFO_HEAD_PARSE_ERR;
	}

	/*parse version number*/
	for(numcount = 0;numcount < 3; numcount ++)
	{
		if(NULL!=(token=strsep(&cur,".]")))
		{
			if(SUCCESS != digit_check(token))
			{
				return errornum=VER_INFO_HEAD_PARSE_ERR;
			}
			else
			{
				*pv++ = atoi(token);
			}
		}
		else
		{
			return errornum = VER_INFO_HEAD_PARSE_ERR;

		}
	}

	memmove(downloadinfo.appno,vernum,3);

	return SUCCESS;
}

unsigned int call_sh_script(char *cmd)
{
	int ret;
	ret=system(cmd);

    if (-1 == ret)
    {
		return errornum = SCRIPT_EXECUTE_ERR;
    }
	else
	{
	    if (WIFEXITED(ret))
	    {
	        if (0 != WEXITSTATUS(ret))
	        {
				return errornum = SCRIPT_EXECUTE_ERR;
	        }
	    }
	    else
	    {
			return errornum = SCRIPT_EXECUTE_ERR;
	    }
	}
	return SUCCESS;
}


unsigned int erase_flash_mtdblock(int mtdno)
{
	int                  ret;
	erase_info_t         EraseInfo;
	struct mtd_info_user info;
	char                 cmdbuf[128];

	sprintf(cmdbuf,"eraseall /dev/mtd%d",mtdno);
	ret = call_sh_script(cmdbuf);

	if(SUCCESS != ret)
		return ERR;

	return SUCCESS;
}

unsigned int write_ver_flag(int vertype)
{
	int 		     ret = -1;
	unsigned int     len;
	unsigned char	 flag[4];
	if(SYS_VERSION == vertype)
	{
		flag[0] = 0; //loadflag
		flag[1] = 0; //checkflag
		if(0 == sysstartflag)
		{
			ret = bsp_eeprom_snd(EEPROM_SYS1_LOAD_FLAG_ADDR,2,flag,&len);
		}
		else if(1 == sysstartflag)
		{
			ret = bsp_eeprom_snd(EEPROM_SYS0_LOAD_FLAG_ADDR, 2, flag,&len);
		}
		if(SUCCESS != ret)
		{
			abnormal_print("eeprom write err\n");
			return errornum = EEPROM_WRITE_ERR;
		}
	}

	return SUCCESS;
}

unsigned int init_vmm_download(int versiontype, char **pwrite_position,\
									char * flashwritebuf, int *write_length,\
									int *content_total_length,int *frame_num)
{
	int ret;
	*pwrite_position      = flashwritebuf;
	*write_length         = 0;
	*content_total_length = 0;
	*frame_num            = 0;
    int mtdno             = -1;

	ret = write_ver_flag(versiontype);
	if(SUCCESS != ret)
		return ERR;

	if(APP_VERSION == versiontype)
	{
		downloadinfo.versiontype      = APP_VERSION;
		mtdno                         = 8;
	}else if(SYS_VERSION == versiontype)
	{
		downloadinfo.versiontype      = SYS_VERSION;
		if(SYS0_VER_START_FLAG == sysstartflag)
		{
			mtdno  = 6;
		}
		else if(SYS1_VER_START_FLAG == sysstartflag)
		{
			mtdno  = 3;
		}
		else
		{
			return errornum = EEPROM_SYS_START_FLAG_ERR;
		}
	}

	if(mtdno > 0)
	{
		if(mtdfd >= 0)
		{
			close(mtdfd);
			mtdfd = -1;
		}
		ret = erase_flash_mtdblock(mtdno);
		if (SUCCESS != ret)
		{
			abnormal_print("erase mtdblock%d err\n",mtdno);
			return errornum = FLASH_MTD_ERASE_ERR;
		}

		mtdfd = open(mtdblockinfo[mtdno].name, O_RDWR);

		if (mtdfd < 0)
	    {
	        return errornum = FLASH_MTD_OPEN_ERR;
	    }
	}

	return SUCCESS;
}

unsigned int open_mtd_block(char *buf, int versize, int * openflag)
{
	int mtdno = -1;
	int ret;
	pd_version_info_t *pd_head = (pd_version_info_t *)(buf + sizeof(message_head_t));
    if(SYS_VERSION == downloadinfo.versiontype)
	{
		/*read eeprom to determine which system is running */
		if((1 == pd_head->downloadprogress) && (versize == downloadinfo.linuxsize))
		{
			if(SYS0_VER_START_FLAG == sysstartflag)
			{
				mtdno = 7;
			}
			else if(SYS1_VER_START_FLAG == sysstartflag)
			{
				mtdno = 4;

			}
			*openflag = 2;/*open ramdisk mtdblock*/

		}
		else if((2 == pd_head->downloadprogress)&&(versize == downloadinfo.ramdisksize))
		{

			if(SYS0_VER_START_FLAG == sysstartflag)
			{
				mtdno = 5;
			}
			else if(SYS1_VER_START_FLAG == sysstartflag)
			{
				mtdno = 2;
			}
			*openflag = 3;/*open dtb mtdblock*/
		}
	}

	if(mtdno > 0)
	{
		if(mtdfd >= 0)
		{
			close(mtdfd);
			mtdfd = -1;
		}

		ret = erase_flash_mtdblock(mtdno);
		if (SUCCESS != ret)
		{
			abnormal_print("erase mtdblock%d err\n",mtdno);
			return ERR;
		}

		mtdfd = open(mtdblockinfo[mtdno].name, O_RDWR);
		if (mtdfd < 0)
	    {
	        return errornum = FLASH_MTD_OPEN_ERR;
		}

	}

	return SUCCESS;

}

unsigned int write_ver_no(int vertype)
{
	int 		     ret = -1;
	unsigned int     len;

	if(APP_VERSION == vertype)
	{
		ret = bsp_eeprom_snd(EEPROM_APP_VER_NO_ADDR, 3,\
			(unsigned char *)downloadinfo.appno, &len);
	}
	else if(UBOOT_VERSION == vertype)
	{
		ret = SUCCESS;
	}
	else if(SYS_VERSION == vertype)
	{
		if(0 == sysstartflag)
		{
			ret = bsp_eeprom_snd(EEPROM_SYS1_VER_NO_ADDR, 3,\
				(unsigned char *)downloadinfo.sysno, &len);
		}
		else if(1 == sysstartflag)
		{
			ret = bsp_eeprom_snd(EEPROM_SYS0_VER_NO_ADDR, 3,\
				(unsigned char *)downloadinfo.sysno, &len);

		}
	}

	if(SUCCESS != ret)
	{
		abnormal_print("eeprom write err\n");
		return errornum = EEPROM_WRITE_ERR;
	}

	if(APP_VERSION == vertype)
	{
		memmove(verqueryinfo.app_download_no,downloadinfo.appno,3);
	}
	else if(SYS_VERSION == vertype)
	{
		if(0 == sysstartflag)
		{
			memmove(verqueryinfo.sys1no,downloadinfo.sysno,3);
		}
		else if(1 == sysstartflag)
		{
			memmove(verqueryinfo.sys0no,downloadinfo.sysno,3);
		}
	}
	return SUCCESS;

}

unsigned int ver_down_load(int versiontype, char *recvbuf, int len,\
								char **pwrite_position, char * flashwritebuf, \
								int *write_length,int *content_total_length,int *frame_num)
{
	pd_version_info_t *pd_head;
	int ret        = -2;
	int actual_len = 0;
	int openflag   = 0;
	int head_len   = sizeof(pd_version_info_t)+sizeof(message_head_t);

	pd_head = (pd_version_info_t *)(recvbuf + sizeof(message_head_t));

	if((len <= head_len)||(len > (1024 + head_len)))
	{
		return errornum = FRAME_LENGTH_ERR;
	}

	actual_len = len - head_len;

	*write_length += actual_len;

	if((*write_length == 1024)&&(pd_head->frametype != 2))
	{
		memmove(*pwrite_position, recvbuf + head_len, actual_len);

		*pwrite_position += actual_len;
	}
	else
	{
		memmove(*pwrite_position,recvbuf + head_len, actual_len);

		if(*write_length > 1024)
		  *pwrite_position = flashwritebuf;

		ret = write(mtdfd, *pwrite_position, *write_length);
		if (ret != *write_length)
		{
			abnormal_print("write flash err write_length =%d ret =%d \n",*write_length,ret);
		    close(mtdfd);
			return errornum = FLASH_WRITE_ERR;
		}

		*content_total_length += *write_length;
		*write_length         = 0;
	}

	*frame_num = *frame_num + 1;

	ret = open_mtd_block(recvbuf,*content_total_length,&openflag);
	if(SUCCESS != ret)
	{
		abnormal_print("open_mtd_block err\n");
		perror("reason:");
		return ERR;
	}

	if(2 == openflag || 3 == openflag)
	{
		*pwrite_position      = flashwritebuf;
		*write_length         = 0;
		*content_total_length = 0;
	}

	if(pd_head->frametype == 2)
	{
		close(mtdfd);
		ret = write_ver_no(ntohl(pd_head->versiontype));
		if(SUCCESS != ret)
			return ERR;
	}

	return SUCCESS;
}

unsigned int ver_init(void)
{
	int  			ret;
	unsigned char 	buf[16];
	unsigned int	len;
	/*init the version infomation,read from eeprom and assign to the global variable eepverinfo*/
	ret = bsp_eeprom_rcv(EEPROM_SYS_START_FLAG_ADDR, 14, buf, &len);
	if (SUCCESS == ret)
	{
		/*init the gloabal variable verinfoquery used as cli querying or pc querying*/

		sysstartflag = buf[0];
		verqueryinfo.sys_ver_running = sysstartflag;
		verqueryinfo.sys_ver_switchedstatus = 0;
		memset(verqueryinfo.app_download_no,0,sizeof(verqueryinfo.app_download_no));
		memmove(verqueryinfo.sys0no,&buf[5],3);
		memmove(verqueryinfo.sys1no,&buf[8],3);
		memmove(verqueryinfo.app_running_no,&buf[11],3);
		memset(verqueryinfo.app_download_no,0,3);

		initversionstatus.sys0loadflag  = buf[1];
		initversionstatus.sys0checkflag = buf[2];
		initversionstatus.sys1loadflag  = buf[3];
		initversionstatus.sys1checkflag = buf[4];

	}
	else
	{
		abnormal_print("reserved !! function ver_init() eeprom read error\n");
		return errornum = EERPOM_READ_ERR;
	}

	return SUCCESS;

}

unsigned int ver_update_load(void)
{
	unsigned char    loadflag,checkflag;
	int 	         ret;
    unsigned int     len;
	/*check the loadflag which whether or not setted by boot .
	    if setted to 1 meanning that the started version is downloaded or manual switched
	    last time the device powered on. now change the checkflag to 1 ,show that the current
	    version is normal running */
	if(0 == sysstartflag)
	{
		loadflag	= initversionstatus.sys0loadflag;
		checkflag 	= initversionstatus.sys0checkflag;
	}
	else if(1 == sysstartflag)
	{
		loadflag	= initversionstatus.sys1loadflag;
		checkflag 	= initversionstatus.sys1checkflag;
	}
	else
	{
		sysstartflag = 0;
		loadflag	= initversionstatus.sys0loadflag;
		checkflag 	= initversionstatus.sys0checkflag;
		ret = bsp_eeprom_snd(EEPROM_SYS_START_FLAG_ADDR, 1,\
			(unsigned char *)(&sysstartflag), &len);

		if (SUCCESS != ret)
		{
			abnormal_print("eeprom write err\n");
			return errornum = EEPROM_WRITE_ERR;
		}
	}

	if(1 == loadflag)
	{
		if(1 == loadflag && 0 == checkflag)
		{
			checkflag = 1;
			if(0 == sysstartflag)
			{
				ret = bsp_eeprom_snd(EEPROM_SYS0_CHECK_FLAG_ADDR, 1, &checkflag, &len);
				initversionstatus.sys0checkflag= checkflag;
			}
			else if(1 == sysstartflag)
			{
				ret = bsp_eeprom_snd(EEPROM_SYS1_CHECK_FLAG_ADDR, 1, &checkflag, &len);
				initversionstatus.sys1checkflag= checkflag;
			}

			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}

			/*syn to global variable eepverinfo */
			initversionstatus.sys0checkflag= checkflag;
		}
	}
	else
	{
		loadflag	= 1;
		checkflag	= 1;

		if(0 == sysstartflag)
		{
			ret = bsp_eeprom_snd(EEPROM_SYS0_LOAD_FLAG_ADDR,  1,  &loadflag, &len);
			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}
			ret = bsp_eeprom_snd(EEPROM_SYS0_CHECK_FLAG_ADDR, 1,  &checkflag, &len);
			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}
			/*syn to global variable eepverinfo */
			initversionstatus.sys0checkflag= checkflag;
			initversionstatus.sys0loadflag = loadflag;
		}
		else if(1 == sysstartflag)
		{
			ret = bsp_eeprom_snd(EEPROM_SYS1_LOAD_FLAG_ADDR,  1,  &loadflag, &len);
			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}
			ret = bsp_eeprom_snd(EEPROM_SYS1_CHECK_FLAG_ADDR, 1, &checkflag, &len);
			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}
			/*syn to global variable eepverinfo */
			initversionstatus.sys1checkflag= checkflag;
			initversionstatus.sys1loadflag = loadflag;
		}

		/*syn to global variable eepverinfo */
	}

	return SUCCESS;
}

unsigned int ver_query(char *sendbuf)
{
	message_head_t * messagehead;
	version_query_info_t *verquery;

	messagehead            = (message_head_t*)sendbuf;
	messagehead->messageid = VERSION_QUERY;
	messagehead->result    = SUCCESS;

	verquery  = (version_query_info_t *)(sendbuf+sizeof(message_head_t));
    *verquery = verqueryinfo;

	return SUCCESS;
}

unsigned int ver_switch(char *sendbuf)
{
	int 				  ret;
	unsigned int 		  len;
	unsigned char		  verofswitched;
	unsigned char         flag[4];
	message_head_t        *messagehead;
	version_query_info_t  *verquery;

	messagehead            = (message_head_t *)(sendbuf);
	messagehead->messageid = SYS_VERSION_SWITCH;

	verquery  = (version_query_info_t *)(sendbuf+sizeof(message_head_t));
    *verquery = verqueryinfo;

	/*if the version is switched done then return and set the errornum*/

	if(1 == verqueryinfo.sys_ver_switchedstatus)
		return errornum = VERSION_SWITCH_DONE_BEFORE;

	/*manual switch to the another version:  if now runnging the system_version_0 (verstarflg== 0),
	    then modify the value verstarflg to 1 (1 - verstarflg ),and write to the eeprom. according to the
	    value of verstarflg boot choose load the corresponding version(0:system_version_0
	    1:system_version_1)  The relevant address value refer to the design doc(EEPROM)*/

	verofswitched = 1 - sysstartflag;

	/*syn to the global variable verinfoquery, the flag of the version switched to setted to be switched
	   and set the sys_ver_switchedstatus */

	if(verofswitched == 0)
	{
		if((initversionstatus.sys0checkflag == 1)&&(initversionstatus.sys0loadflag == 1))
		{
			//do nothing
		}
		else
		{
			flag[0] = 0;
			flag[1] = 0;

			ret = bsp_eeprom_snd(EEPROM_SYS0_LOAD_FLAG_ADDR, 2, flag, &len);
			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}
		}
	}
	else if(verofswitched == 1)
	{
		if((initversionstatus.sys1checkflag == 1)&&(initversionstatus.sys1loadflag == 1))
		{
			//do nothing
		}
		else
		{
			flag[0] = 0;
			flag[1] = 0;

			ret = bsp_eeprom_snd(EEPROM_SYS1_LOAD_FLAG_ADDR, 2, flag, &len);
			if (SUCCESS != ret)
			{
				abnormal_print("eeprom write err\n");
				return errornum = EEPROM_WRITE_ERR;
			}
		}
	}
	ret = bsp_eeprom_snd(EEPROM_SYS_START_FLAG_ADDR, 1, &verofswitched, &len);
	if (SUCCESS != ret)
	{
		abnormal_print("eeprom write err\n");
		return errornum = EEPROM_WRITE_ERR;
	}

	verqueryinfo.sys_ver_switchedstatus = 1;

	return SUCCESS;
}

unsigned int ver_unswitch(char *sendbuf)
{
	int 				 ret;
	unsigned int		 len;
	message_head_t       *msgheadsend;
	version_query_info_t *verquery;

	msgheadsend 				=  (message_head_t *)(sendbuf);
	msgheadsend->messageid 		=  SYS_VERSION_UNSWITCH;
	verquery                    = (version_query_info_t *)(sendbuf+sizeof(message_head_t));
    *verquery                   = verqueryinfo;
	/*if the version is unswitched done then return and set the errornum*/
	if(0 == verqueryinfo.sys_ver_switchedstatus)
		return errornum = VERSION_UNSWITCH_DONE_BEFORE;

	/*syn to the global variable verinfoquery, the flag of the version switched to setted to be switched
	   and set the sys_ver_switchedstatus */
	if(sysstartflag == 0)
	{
		ret = bsp_eeprom_snd(EEPROM_SYS0_LOAD_FLAG_ADDR, 1,\
			(unsigned char *)(&initversionstatus.sys0loadflag), &len);

		if (SUCCESS != ret)
		{
			abnormal_print("eeprom write err\n");
			return errornum = EEPROM_WRITE_ERR;
		}
		ret = bsp_eeprom_snd(EEPROM_SYS0_CHECK_FLAG_ADDR, 1,\
			(unsigned char *)(&initversionstatus.sys0checkflag), &len);

		if (SUCCESS != ret)
		{
			abnormal_print("eeprom write err\n");
			return errornum = EEPROM_WRITE_ERR;
		}
	}
	else if(sysstartflag == 1)
	{
		ret = bsp_eeprom_snd(EEPROM_SYS1_LOAD_FLAG_ADDR, 1,\
			(unsigned char *)(&initversionstatus.sys1loadflag), &len);

		if (SUCCESS != ret)
		{
			abnormal_print("eeprom write err\n");
			return errornum = EEPROM_WRITE_ERR;
		}
		ret = bsp_eeprom_snd(EEPROM_SYS1_CHECK_FLAG_ADDR, 1,\
			(unsigned char *)(&initversionstatus.sys1checkflag), &len);

		if (SUCCESS != ret)
		{
			abnormal_print("eeprom write err\n");
			return errornum = EEPROM_WRITE_ERR;
		}
	}
	ret = bsp_eeprom_snd(EEPROM_SYS_START_FLAG_ADDR, 1,\
		(unsigned char *)(&sysstartflag), &len);

	if (SUCCESS != ret)
	{
		abnormal_print("eeprom write err\n");
		return errornum = EEPROM_WRITE_ERR;
	}

	verqueryinfo.sys_ver_switchedstatus = 0;

	return SUCCESS;
}

unsigned int device_reboot(void)
{
	int  ret;
	char cmdbuf[128];

	sprintf(cmdbuf,"reboot");

	ret = call_sh_script(cmdbuf);
	if(SUCCESS != ret)
		return ERR;

	return SUCCESS;
}

unsigned int open_uboot_mtd(int mtdno)
{
	int ret;
	if(mtdfd >= 0)
	{
		close(mtdfd);
		mtdfd = -1;
	}
	ret = erase_flash_mtdblock(mtdno);
	if(SUCCESS != ret)
	{
		abnormal_print("flash erase err\n");
		return ERR;
	}
	mtdfd = open(mtdblockinfo[mtdno].name, O_RDWR);
	if (mtdfd < 0)
	{
		abnormal_print("mtd open  err\n");
		return errornum = FLASH_MTD_OPEN_ERR;
	}

	return SUCCESS;
}

unsigned int message_process(zmq_pollitem_t *zmq_socket_p, char *recvbuf,\
									int recvlen,char **pwrite_position,char * flashwritebuf,\
									int *write_length,int *content_total_length,int *frame_num)
{
    int  send_len;
	int  sendsize;
	int  ret=-1;
	char send_buf[128];
	char vernum[3];
	int  linuxsize,ramdisksize,dtbsize;
	pd_version_info_t * precv_version_info_t;
	pd_version_info_t * psend_version_info_t;

	message_head_t *recvmessagehead;
	message_head_t *sendmessagehead;

	recvmessagehead      = (message_head_t *)recvbuf;
	sendmessagehead      = (message_head_t *)send_buf;
	precv_version_info_t = (pd_version_info_t *)(recvbuf +sizeof(message_head_t));
	psend_version_info_t = (pd_version_info_t *)(send_buf+sizeof(message_head_t));

	switch(ntohl(recvmessagehead->messageid))
	{
		case VERSION_DOWNLOAD:
			switch(ntohl(precv_version_info_t->frametype))
			{
				case VERSION_INFO_FRAME:
					{
						if(0 == ntohl(precv_version_info_t->versiontype))
						{
							ret = parse_app_ver_info(recvbuf);
						}
						else if(1 == ntohl(precv_version_info_t->versiontype))
						{
							ret = parse_sys_ver_info(recvbuf,vernum,&linuxsize,\
								&ramdisksize,&dtbsize);
						}
						else if(2 == ntohl(precv_version_info_t->versiontype))
						{
							ret = open_uboot_mtd(0);
							break;
						}

					    if(SUCCESS == ret)
						{
							ret = init_vmm_download(ntohl(precv_version_info_t->versiontype),\
								pwrite_position,flashwritebuf, write_length,content_total_length,frame_num);
						}
						break;
					}
				case VERSION_CONTENT_FRAME:
				case VERSION_END_FRAME:
					{
						ret = ver_down_load(ntohl(precv_version_info_t->versiontype),\
							recvbuf,recvlen,pwrite_position, flashwritebuf, write_length,\
							content_total_length,frame_num);
						break;
					}
				default:
					{
						errornum = VER_INFO_PARSE_ERR;
						break;
					}
			}

			sendmessagehead->messageid 		  =  htonl(VERSION_DOWNLOAD);
			psend_version_info_t->num	      =	 htonl(*frame_num);
			psend_version_info_t->frametype   =  htonl(precv_version_info_t->frametype);
			psend_version_info_t->length      =	 htonl(recvlen);
			sendsize                          =  sizeof(message_head_t) + sizeof(pd_version_info_t);
			break;
		case VERSION_QUERY:
			{
				ret      = ver_query(send_buf);
				sendsize = sizeof(version_query_info_t) + sizeof(message_head_t);
				break;
			}
		case SYS_VERSION_SWITCH:
			{
				ret      = ver_switch(send_buf);
				sendsize = sizeof(message_head_t) + sizeof(version_query_info_t);
				break;
			}
		case SYS_VERSION_UNSWITCH:
			{
				ret      = ver_unswitch(send_buf);
				sendsize = sizeof(message_head_t) + sizeof(version_query_info_t);
				break;
			}
		case DEVICE_REBOOT:
			{
				sendmessagehead->result = SUCCESS;
				sendsize                = sizeof(message_head_t);
				send_len = zmq_send(zmq_socket_p,send_buf,sendsize,ZMQ_DONTWAIT);
				if(0 > send_len)
				{
					abnormal_print("zmq send error!\n");
					return ERR;
				}
				ret      = device_reboot();
				break;
			}

		default:
			{
				errornum = MESSAGE_HEAD_PARSE_ERR;
			}
	}
	if(SUCCESS == ret)
	{
		sendmessagehead->result		  =  htonl(SUCCESS);
	}
	else
	{
		sendmessagehead->result		  =  htonl(errornum);
	}

	send_len = zmq_send(zmq_socket_p,send_buf,sendsize,ZMQ_DONTWAIT);
	if(0 > send_len)
	{
		abnormal_print("zmq send error!\n");
		return ERR;
	}

	return SUCCESS;
}

void recv_message(zmq_pollitem_t *zmq_socket_p)
{
	zmq_pollitem_t items[1];
	int    ret;
	int    recv_len;
	char   recv_buf[1056];
	char   flash_write_buf[2048];

	char * pwrite_position;
	int    write_length         = 0;
	int    content_total_length = 0;
	int    frame_num            = 0;

	pd_version_info_t * precv_version_info_t;

	precv_version_info_t = (pd_version_info_t *)(recv_buf+sizeof(message_head_t));

	pwrite_position      = flash_write_buf;


	items[0].socket = zmq_socket_p;
	items[0].events = ZMQ_POLLIN;

    memset(recv_buf,0,sizeof(recv_buf));

	 /* loop receive message  */
    while ( 1 )
    {
        ret = zmq_poll(items, 1, -1);

		if(0 > ret)
		{
			abnormal_print("ret= %d\n",ret);
			sleep(3);
			continue;
		}

		if(items[0].revents & ZMQ_POLLIN)
			{
				memset(recv_buf,0,sizeof(recv_buf));
				recv_len = zmq_recv(zmq_socket_p, recv_buf, sizeof(recv_buf), 0);
				if(recv_len < 0)
				{
					abnormal_print("recv error\n");
					continue;
				}

				message_process(zmq_socket_p,recv_buf,recv_len,&pwrite_position,\
					flash_write_buf,&write_length,&content_total_length,&frame_num);

				continue;
			}
		else
			{
				abnormal_print("poll error\n");
			}

	}

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
	   return ERR;
	}

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t)buf;
	if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
	{
	   interfaceNum = ifc.ifc_len / sizeof(struct ifreq);
	}
	return interfaceNum;
}

void thread_rb_vmm_proxy(void)
{
	int ret = 0;

	proxy_frontend = zmq_socket(zmq_context,ZMQ_ROUTER);
	if(NULL == proxy_frontend)
	{
		abnormal_print("proxy_frontend create error\n");
	}

	proxy_backend  = zmq_socket(zmq_context,ZMQ_DEALER);
	if(NULL == proxy_backend)
	{
		abnormal_print("proxy_backend create error\n");
	}

	 /*rsu_rb unit wait for pc to connect port:XXXXX (rsu_rb eth1:port <---> pc)*/
	ret = zmq_bind(proxy_frontend,"tcp://eth1:10011");
	if(ret != 0)
	{
		abnormal_print("zmq bind proxy_frontend error\n");
	}

	/*rsu_rb unit wait for rsu_rf unit to connect port:XXXXX (rsu_rb  eth0:port<--->rsu_rf)*/
	ret = zmq_bind(proxy_backend,"tcp://eth0:10010");
	if(ret != 0)
	{
		abnormal_print("zmq bind proxy_backend error\n");
	}

	zmq_proxy(proxy_backend,proxy_frontend,NULL);

	zmq_close (proxy_frontend);
	zmq_close (proxy_backend);
	zmq_term  (zmq_context);

}

void thread_rf_vmm(void)
{
	int ret = 0;

	rep_to_dealer = zmq_socket(zmq_context,ZMQ_REP);
	if(NULL == rep_to_dealer)
	{
		abnormal_print("rep_to_dealer create error\n");
	}

	/*rsu_rf unit to connect  ip:xx.xx.xx.xx port:xxxx  of rsu_rb unit (rsu_rf <---> rsu_rb ip:port)*/
	ret = zmq_connect(rep_to_dealer,"tcp://222.255.255.254:10010");
	if(ret != 0)
	{
		abnormal_print("rep_to_dealer connect rsu_rb backend error\n");
	}

	recv_message((zmq_pollitem_t *)rep_to_dealer);
}

int eth_ip_init(int interfacenum)
{
	unsigned char ipbuf[16];
	char          cmdbuf[128];
	unsigned int  readlen;
	int 		  ret;

	memset(ipbuf,0,sizeof(ipbuf));
	memset(cmdbuf,0,sizeof(cmdbuf));

	if(0 != bsp_eeprom_rcv(EEPROM_ETH0_IP_ADDR, 8, ipbuf, &readlen))
	{
		abnormal_print("bsp_eeprom_rcv read error\n");
		return ERR;
	}
	sprintf(cmdbuf,"ifconfig eth0 %d.%d.%d.%d netmask %d.%d.%d.%d",\
		ipbuf[0],ipbuf[1],ipbuf[2],ipbuf[3],ipbuf[4],ipbuf[5],ipbuf[6],ipbuf[7]);

	ret = call_sh_script(cmdbuf);
	if(SUCCESS != ret)
	{
		abnormal_print("ip set error\n");
		if(interfacenum > 2)
		{
			sprintf(cmdbuf,"ifconfig eth0 222.255.255.254 netmask 255.255.255.0");
		}
		else
		{
			sprintf(cmdbuf,"ifconfig eth0 222.255.255.253 netmask 255.255.255.0");
		}
		ret = call_sh_script(cmdbuf);
		if(SUCCESS != ret)
		{
			abnormal_print("set eth0 default ip error ,exit!!\n ");
			return ERR;
		}
	}

	if(0 != bsp_eeprom_rcv(EEPROM_ETH0_MAC_ADDR, 6, ipbuf, &readlen))
	{
		abnormal_print("bsp_eeprom_rcv read error\n");
	}
	else
	{
        if ((0xff == ipbuf[0]) && (0xff == ipbuf[1]) && (0xff == ipbuf[2])\
            && (0xff == ipbuf[3]) && (0xff == ipbuf[4]) && (0xff == ipbuf[5]))
        {
            ;
        }
        else
        {
            sprintf(cmdbuf,"ifconfig eth0 hw ether %x:%x:%x:%x:%x:%x",\
                ipbuf[0],ipbuf[1],ipbuf[2],ipbuf[3],ipbuf[4],ipbuf[5]);
            (void)call_sh_script(cmdbuf);
        }
	}

	if(0 != bsp_eeprom_rcv(EERPOM_ETH0_GATEWAY_ADDR, 4, ipbuf, &readlen))
	{
		abnormal_print("bsp_eeprom_rcv read error\n");
	}
	else
	{
        if ((0xff == ipbuf[0]) && (0xff == ipbuf[1]) && (0xff == ipbuf[2])\
            && (0xff == ipbuf[3]))
        {
            ;
        }
        else
        {
            sprintf(cmdbuf,"route add default gw %d.%d.%d.%d eth0",\
                ipbuf[0],ipbuf[1],ipbuf[2],ipbuf[3]);
            (void)call_sh_script(cmdbuf);
        }
	}	

	if(interfacenum > 2)
	{
		if(0 != bsp_eeprom_rcv(EEPROM_ETH1_IP_ADDR, 8, ipbuf, &readlen))
		{
			abnormal_print("bsp_eeprom_rcv read error\n");
			return ERR;
		}
		sprintf(cmdbuf,"ifconfig eth1 %d.%d.%d.%d netmask %d.%d.%d.%d",\
			ipbuf[0],ipbuf[1],ipbuf[2],ipbuf[3],ipbuf[4],ipbuf[5],ipbuf[6],ipbuf[7]);
		ret = call_sh_script(cmdbuf);
		if(SUCCESS != ret)
		{
			abnormal_print("ip set error\n");
			sprintf(cmdbuf,"ifconfig eth1 192.168.1.254 netmask 255.255.255.0");
			ret = call_sh_script(cmdbuf);
			if(SUCCESS != ret)
			{
				abnormal_print("set eth1 default ip 192.168.1.254 error ,exit!!\n ");
				return ERR;
			}
		}
		
        if(0 != bsp_eeprom_rcv(EEPROM_ETH1_MAC_ADDR, 6, ipbuf, &readlen))
        {
            abnormal_print("bsp_eeprom_rcv read error\n");
        }
        else
        {
            if ((0xff == ipbuf[0]) && (0xff == ipbuf[1]) && (0xff == ipbuf[2])\
                && (0xff == ipbuf[3]) && (0xff == ipbuf[4]) && (0xff == ipbuf[5]))
            {
                ;
            }
            else
            {
                sprintf(cmdbuf,"ifconfig eth1 hw ether %x:%x:%x:%x:%x:%x",\
                    ipbuf[0],ipbuf[1],ipbuf[2],ipbuf[3],ipbuf[4],ipbuf[5]);
                (void)call_sh_script(cmdbuf);
            }
        }

    	if(0 != bsp_eeprom_rcv(EEPROM_ETH1_GATEWAY_ADDR, 4, ipbuf, &readlen))
    	{
    		abnormal_print("bsp_eeprom_rcv read error\n");
    	}
    	else
    	{
            if ((0xff == ipbuf[0]) && (0xff == ipbuf[1]) && (0xff == ipbuf[2])\
                && (0xff == ipbuf[3]))
            {
                ;
            }
            else
            {
                sprintf(cmdbuf,"route add default gw %d.%d.%d.%d eth1",\
                    ipbuf[0],ipbuf[1],ipbuf[2],ipbuf[3]);
                (void)call_sh_script(cmdbuf);
            }
    	}        
	}
	return SUCCESS;
}

int main(int argc, char **argv)
{
	int       ret           = 0;
	int       interfaceNum  = 0;
	pthread_t vmmproxyid;
	pthread_t vmmrfid;

	memset(&downloadinfo,0,sizeof(download_info_t));

	bsp_eeprom_init();

	ret = ver_init();
	if(SUCCESS != ret)
	{
		abnormal_print("ver_init error!!\n");
	}

	ret = ver_update_load();
	if(SUCCESS != ret)
	{
		abnormal_print("ver_update_load error!!\n");
	}

	zmq_context  = zmq_ctx_new();

	rep_for_pc   = zmq_socket(zmq_context,ZMQ_REP);

	if(NULL == rep_for_pc)
	{
		abnormal_print("rep_for_pc socket create error\n");
	}

	interfaceNum = get_networkcard_num();

	ret = eth_ip_init(interfaceNum);
	if(SUCCESS != ret)
	{
		abnormal_print("eth_ip_init error!!\n");;
	}

	if(interfaceNum >2)
	{

		/*rsu_rf or rsu_rb wait for pc to connect eth1:10012   (rsu_rf or rsu_rb eth1:10012<----> pc)*/
		ret= zmq_bind(rep_for_pc,"tcp://*:10012");
		if(SUCCESS != ret)
		{
			abnormal_print("zmq bind rep_for_pc eth1 error\n");
		}

		ret = pthread_create(&vmmproxyid,NULL,(void *)thread_rb_vmm_proxy,NULL);
		if(SUCCESS != ret)
		{
			abnormal_print ("Create thread_rb_vmm_proxy pthread error!n");
		}
	}
	else
	{
		/*rsu_rf or uhf wait for pc to connect eth0:10012   (rsu_rf or uhf eth0:10012<----> pc)*/
		ret= zmq_bind(rep_for_pc,"tcp://*:10012");
		if(SUCCESS != ret)
		{
			abnormal_print("zmq bind rep_for_pc eth0 error\n");
		}

		ret = pthread_create(&vmmrfid,NULL,(void *)thread_rf_vmm,NULL);
		if(SUCCESS != ret)
		{
			abnormal_print ("Create thread_rf_vmm pthread error!n");
		}
	}

	recv_message(rep_for_pc);

	zmq_close(proxy_backend);

	zmq_close(proxy_frontend);

	zmq_close(rep_for_pc);

	zmq_close(rep_to_dealer);

	zmq_term(zmq_context);

    return 0;
}


