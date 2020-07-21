#include <zmq.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <net/if.h>
#include <pthread.h>
#include "vmm_eeprom_driver.h"
#include <mtd/mtd-user.h>
#include <sys/mount.h>

#define  ERR                        0xFFFF
#define  SUCCESS                    0x0

#define  VER_INFO_HEAD_PARSE_ERR    101
#define  VER_EERPOM_WRITE_ERR       102
#define  FRAME_LENGTH_ERR           103
#define  VER_INFO_PARSE_ERR         104
#define  FLASH_MTD_OPEN_ERR         105
#define  FLASH_WRITE_ERR            106
#define  FLASH_MTD_ERASE_ERR        107
#define  MESSAGE_HEAD_PARSE_ERR     108
#define  VERSION_SWITCH_DONE_BEFORE         109
#define  VERSION_UNSWITCH_DONE_BEFORE       110
#define  EEPROM_WRITE_ERR           111
#define  EERPOM_READ_ERR            112
#define  SCRIPT_EXECUTE_ERR         113
#define  EEPROM_SYS_START_FLAG_ERR  114

/* to be modified*/
#define  EEPROM_SYS_START_FLAG_ADDR  20
#define  EEPROM_SYS0_LOAD_FLAG_ADDR  21
#define  EEPROM_SYS0_CHECK_FLAG_ADDR 22
#define  EEPROM_SYS1_LOAD_FLAG_ADDR  23
#define  EEPROM_SYS1_CHECK_FLAG_ADDR 24

#define  EEPROM_SYS0_VER_NO_ADDR      25   /*25-26-27  sysverno addr*/
#define  EEPROM_SYS1_VER_NO_ADDR      28   /*28-29-30  sysverno addr*/
#define  EEPROM_APP_VER_NO_ADDR       31   /*31-32-33  appverno addr*/
#define  EEPROM_UBOOT_VER_NO_ADDR     34   /*34-35-36  appverno addr*/

#define  EEPROM_ETH0_IP_ADDR         0x27  /*27 28 29 2A*/
#define  EEPROM_ETH0_NETMASK_ADDR    0x2B  /*2B 2C 2D 2E*/
#define  EERPOM_ETH0_GATEWAY_ADDR    0x2F  /*2F 30  31  32*/
#define  EEPROM_ETH1_IP_ADDR         0x33  /*33 34 35 36*/
#define  EEPROM_ETH1_NETMASK_ADDR    0x37  /*37 38 39 3A*/
#define  EEPROM_ETH1_GATEWAY_ADDR    0x3B  /*3B 3C 3D 3E*/
#define  EEPROM_ETH0_MAC_ADDR        0x40  /*40 41 42 43 44 45*/
#define  EEPROM_ETH1_MAC_ADDR        0x46  /*46 47 48 49 4A 4B*/

/*to be modified*/
#define  MTDBLOCK_NO                11

#define  SYS0_VER_START_FLAG        0
#define  SYS1_VER_START_FLAG        1

#define  APP_VERSION                0
#define  SYS_VERSION                1
#define  UBOOT_VERSION              2

#define  VERSION_INFO_FRAME         0
#define  VERSION_CONTENT_FRAME      1
#define  VERSION_END_FRAME          2

#define  VERSION_DOWNLOAD        	1
#define  VERSION_QUERY              2
#define  SYS_VERSION_SWITCH         3
#define  SYS_VERSION_UNSWITCH       4
#define  DEVICE_REBOOT              100

#define  APP_VER_FLASH_MTD_BLOCK    "/dev/mtdblock8"
#define  LINUX_S0_FLASH_MTD_BLOCK   "/dev/mtdblock3"
#define  LINUX_S1_FLASH_MTD_BLOCK   "/dev/mtdblock6"
#define  RAMDISK_S0_FLASH_MTD_BLOCK "/dev/mtdblock4"
#define  RAMDISK_S1_FLASH_MTD_BLOCK "/dev/mtdblock7"
#define  DTB_S0_FLASH_MTD_BLOCK     "/dev/mtdblock2"
#define  DTB_S1_FLASH_MTD_BLOCK     "/dev/mtdblcok5"
#define  NOR_FLASH_SECTOR_SIZE       0x20000

#define  LINUX_VER_FLASH_START_ADDR 0x00120000
#define  LINUX_VER_FLASH_END_ADDR   0x00400000

#define debug 0
#define abnormal 1

#if debug
#define dbg_print(format,args...)\
    do\
    {\
        printf("[%d]"format,__LINE__,## args);\
        fflush(stdout);\
    }while(0)
#else
#define dbg_print(format,args...)
#endif

#if abnormal
#define abnormal_print(format,args...)\
    do\
    {\
        printf("[%d]"format,__LINE__,## args);\
        fflush(stdout);\
    }while(0)
#else
#define abnormal_print(format,args...)
#endif


typedef struct message_head
{
	int messageid;
	int result;
}message_head_t;

typedef struct pd_version_info
{
    /*frame size <=1024 byte*/
	int versiontype;   		/*0:app version  1:system version 2:uboot version*/
	int downloadprogress;   /*0:app 1:linux  2:ramdisk  3:dtb*/
	int frametype;          /*0:version info frame 1:version content frame 2: end frame*/
	int num;                /*frame count from 0*/
	int length;             /*actual frame length*/
}pd_version_info_t;

typedef struct download_info
{
	int  versiontype;        /*0:app version 1:system version*/	
	char appno[4];            
	char sysno[4];
	int  linuxsize;
	int  ramdisksize;
	int  dtbsize;
}download_info_t;

typedef struct version_query_info
{
	int  sys_ver_running;        /*0 :system version 0 1:system version 1*/
	int  sys_ver_switchedstatus; /*switched status 0:not switched 1:switched*/
	char app_running_no[4];
	char app_download_no[4];
	char sys0no[4];
	char sys1no[4];
}version_query_info_t;

typedef struct version_status
{
	char sys0loadflag;
	char sys0checkflag;
	char sys1loadflag;
	char sys1checkflag;
}version_status_t;

typedef struct mtdblock_size
{
	int  mtdblockno;
	int  offset;
	int  size;
	char name[24];
}mtdblock_size_t;

