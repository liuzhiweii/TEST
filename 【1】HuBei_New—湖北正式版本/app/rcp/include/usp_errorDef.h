/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_errorDef.h
* 文件标识： 
* 内容摘要： 错误码定义
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2008.10.14
* 
* 修改记录1：
*    修改日期：2009.12.01
*    版 本 号：V01.10.00
*    修 改 人：高峰
*    修改内容：根据代码走查意见规范错误码定义文件
* 修改记录2：…
************************************************************************/
#ifndef _USP_ERROR_DEF_H
#define _USP_ERROR_DEF_H


/***********************************************************
 *                     错误码基值                          *
***********************************************************/
/* 状态监控模块(SMP)错误码基值*/
#define  USP_ERR_OSS_SMP_BASE           (0xF0220000)

/* 公共模块(PUB)错误码基值 */
#define  USP_ERR_PUB_BASE           (0xF0270000)

/* 命令行界面(CLI)错误码基值 */
#define  USP_ERR_OAM_CLI_BASE        (0xF0250000)

/* 系统主控(SCP)错误码基值 */
#define  USP_ERR_OSS_SCP_BASE        (0xF0210000)

/* 数据存储模块(DSM)错误码基值 */
#define  USP_ERR_OSS_DSM_BASE        (0xF02E0000)

/* 内存管理模块(MM)错误码基值 */
#define  USP_ERR_OSS_MM_BASE         (0xF02F0000)

/* 版本管理(VMP)错误码基值 */
#define  USP_ERR_OAM_VMP_BASE        (0xF02A0000)

/* 日志和异常探针(LAP)错误码基值 */
#define  USP_ERR_OAM_LAP_BASE        (0xF0001000)

/* LLRP工具箱(LTK)错误码基值 */
#define  USP_LTK_ERR_BASE        (0xF0002000)

/* 虚拟操作系统(VOS)错误码基值 */
#define  USP_OSS_VOS_ERR_BASE    (0xF0003000)

/* Socket通信(NET)错误码基值 */
#define  USP_OSS_NET_ERR_BASE    (0xF0004000)

/* 定时器(TIMER)错误码基值 */
#define  USP_OSS_TIMER_ERR_BASE  (0xF0005000)

/* 通信模块(COMM)错误码基值 */
#define  USP_COMM_ERR_BASE       (0xF0006000)

/* IP发现模块(IPD)错误码基值 */
#define  USP_COMM_IPD_ERR_BASE   (0xF0011000)

/* 配置模块(CMP)错误码基值 */
#define  USP_OAM_CMP_ERR_BASE    (0xF0012000)

/* 诊断测试模块(DMP)错误码基值 */
#define  USP_OAM_DMP_ERR_BASE    (0xF02B0000)

/* 告警管理模块(AMP)错误码基值 */
#define  USP_OAM_AMP_ERR_BASE    (0xF02D0000)

/* GPIO和Relay模块(GPIO)错误码基址 */
#define  USP_GPIO_ERR_BASE       (0xF0260000)

/*   FLASH系统参数区访问接口 错误码基值    */
#define  USP_ERR_OSS_SYSDATA_START  (0xF0007000)

/* U-Boot 错误码基值*/
#define USP_ERR_UBOOT_BASE                 (0xFD000000)


/* MPI 模块(MPI)错误码基值 */
#define  USP_MPI_ERR_BASE       (0xF0008000)

/* 扩展PSAM管理任务错误码基值 */
#define  USP_ERR_OSS_PSAM_EXT_BASE      (0xF0240000)

/* 杂项任务错误码基值 */
#define  USP_ERR_OSS_MISC_BASE          (0xF0270000)

/*   驱动平台(Drv) 错误码基值    */

/*   驱动平台Flash模块 错误码基值    */
#define USP_ERR_DRV_FLASH_START                                       (0xFF000000)
/*   驱动平台打印机控制模块 错误码基值    */
#define USP_ERR_DRV_PRINTER_START                                     (0xFF001000)
/* 串口模块错误码基值 */
#define USP_ERR_DRV_UART_START                                        (0xFF002000)
/* 磁条读卡器模块错误码基值 */
#define USP_ERR_DRV_MCR_START                                         (0xFF003000)
/* 485控制模块错误码基值 */
#define USP_ERR_DRV_CTRL485_START                                     (0xFF004000)
/* 密码键盘模块错误码基值 */
#define USP_ERR_DRV_CODEKBD_START                                     (0xFF005000)
/*   驱动平台温度传感器模块 错误码基值    */
#define USP_ERR_DRV_TSENSOR_START                                     (0xFF006000)
/*   驱动平台韦根模块 错误码基值    */
#define USP_ERR_DRV_WG_START                                          (0xFF007000)
/* GPRS模块错误码基值 */
#define USP_ERR_DRV_GPRS_START                                        (0xFF008000)
/*   驱动平台EEPROM模块 错误码基值    */
#define USP_ERR_DRV_EEPROM_START                                      (0xFF009000)
/*   驱动平台I2C模块 错误码基值    */
#define USP_ERR_DRV_I2C_START                                         (0xFF00A000)
/*   驱动平台IOPORT模块 错误码基值    */
#define USP_ERR_DRV_IOPORT_START                                      (0xFF00B000)
/*   驱动平台FPGA模块 错误码基值    */
#define USP_ERR_DRV_FPGA_START                                        (0xFF00C000)
/*   驱动平台Epld模块 错误码基值    */
#define USP_ERR_DRV_EPLD_START                                        (0xFF00D000)
/*   驱动平台Rtc模块 错误码基值    */
#define USP_ERR_DRV_RTC_START                                         (0xFF00E000)		
/*   驱动平台Lcd模块 错误码基值    */	
#define USP_ERR_DRV_LCD_START                                         (0xFF00F000)		
/*   驱动平台Modem模块 错误码基值    */
#define USP_ERR_DRV_MODEM_START                                       (0xFF010000)				
/*   驱动平台Keyboard模块 错误码基值    */
#define USP_ERR_DRV_KEYBOARD_START                                    (0xFF020000)
/*   驱动平台Wtd模块 错误码基值    */
#define USP_ERR_DRV_WTD_START                                         (0xFF030000)
/*   驱动平台Led模块 错误码基值    */
#define USP_ERR_DRV_LED_START                                         (0xFF040000)
/*   驱动平台psam模块 错误码基值    */
#define USP_ERR_DRV_PSAM_START                                        (0xFF050000)
/*   驱动平台gpio模块 错误码基值    */
#define USP_ERR_DRV_GPIO_START                                        (0xFF060000)
/*   驱动平台ioexpander模块 错误码基值    */
#define USP_ERR_DRV_IOE_START                                         (0xFF070000)
/*   驱动平台timer模块 错误码基值    */
#define USP_ERR_DRV_TIMER_START                                       (0xFF080000)
/*   驱动平台get system info 模块 错误码基值    */
#define USP_ERR_DRV_GET_SYSTEM_INFO_START                             (0xFF090000)
/*   驱动平台clockgen  模块 错误码基值    */
#define USP_ERR_DRV_CLOCKGEN_START                                    (0xFF0A0000)

/*   驱动平台Variant SPI  模块 错误码基值    */
#define USP_ERR_DRV_VARSPI_START                                      (0xFF0B0000)

/*   驱动平台Relay  模块 错误码基值    */
#define USP_ERR_DRV_RELAY_START                                      (0xFF0C0000)

/***********************************************************
*   系统监控(SMP)错误码                                  *
***********************************************************/
#define USP_OSS_SMP_ERR_RECV_MSG                    ((WORD32) (USP_ERR_OSS_SMP_BASE +  1)) /* 接收消息错误 */
#define USP_OSS_SMP_ERR_TIMERSET                    ((WORD32) (USP_ERR_OSS_SMP_BASE +  2)) /* 设置定时器错误*/
#define USP_OSS_SMP_ERR_UNKNOWN_MSG                 ((WORD32) (USP_ERR_OSS_SMP_BASE +  3)) /* 接收到未知消息 */      
#define USP_OSS_SMP_ERR_FUNC_EXECU                  ((WORD32) (USP_ERR_OSS_SMP_BASE +  4)) /* 监控函数处理失败 */     
#define USP_OSS_SMP_ERR_OPEN_FILE                   ((WORD32) (USP_ERR_OSS_SMP_BASE +  5)) /* 打开文件失败 */  
#define USP_OSS_SMP_ERR_MATCH_STR                   ((WORD32) (USP_ERR_OSS_SMP_BASE +  6)) /* CLI命令码错误 */  
#define USP_OSS_SMP_ERR_SSCANF                      ((WORD32) (USP_ERR_OSS_SMP_BASE +  7)) /* CLI命令处理错误 */  
#define USP_OSS_SMP_ERR_GET_CPU_STAT                ((WORD32) (USP_ERR_OSS_SMP_BASE +  8)) /* 获取CPU状态错误 */  
#define USP_OSS_SMP_ERR_GET_SYSINFO                 ((WORD32) (USP_ERR_OSS_SMP_BASE +  9)) /* 获取系统状态错误 */  
#define USP_OSS_SMP_ERR_FUNC_STATFS                 ((WORD32) (USP_ERR_OSS_SMP_BASE + 10)) /* 函数statfs 返回错误 */  
#define USP_OSS_SMP_ERR_MSGCTL                      ((WORD32) (USP_ERR_OSS_SMP_BASE + 11)) /* 函数msgctl 返回错误 */  
#define USP_OSS_SMP_ERR_NULL_POINTER                ((WORD32) (USP_ERR_OSS_SMP_BASE + 12)) /* 空指针 */
#define USP_OSS_SMP_ERR_MSG_LEN                     ((WORD32) (USP_ERR_OSS_SMP_BASE + 13)) /* 消息长度错误 */
#define USP_OSS_SMP_ERR_NOT_FOUND_ITEM              ((WORD32) (USP_ERR_OSS_SMP_BASE + 14)) /* 找不到监控项 */
/***********************************************************
*   命令行界面(CLI)错误码                                  *
***********************************************************/
#define USP_ERR_OAM_CLI_SOCKET_ACCEPT            ((WORD32) (USP_ERR_OAM_CLI_BASE + 1))  /* 接收用户连接错误 */
#define USP_ERR_OAM_CLI_NO_RESOURCE              ((WORD32) (USP_ERR_OAM_CLI_BASE + 2))  /* 没有可用的资源 */   
#define USP_ERR_OAM_CLI_NULL_POINTER             ((WORD32) (USP_ERR_OAM_CLI_BASE + 3))  /* 空指针 */   
#define USP_ERR_OAM_CLI_SELECT                   ((WORD32) (USP_ERR_OAM_CLI_BASE + 4))  /* select 函数错误 */   
#define USP_ERR_OAM_CLI_WRITE_SOCKET             ((WORD32) (USP_ERR_OAM_CLI_BASE + 5))  /* 向客户端写数据错误 */   
#define USP_ERR_OAM_CLI_CA                       ((WORD32) (USP_ERR_OAM_CLI_BASE + 6))  /* 用户权限验证没有通过 */   
#define USP_ERR_OAM_CLI_OPEN_PASSWD_FILE         ((WORD32) (USP_ERR_OAM_CLI_BASE + 7))  /* 打开密码文件错误 */
#define USP_ERR_OAM_CLI_MATCH_QUOTATION_MARK     ((WORD32) (USP_ERR_OAM_CLI_BASE + 8))  /* 引号不匹配 */   
#define USP_ERR_OAM_CLI_PARAM_TOO_MANY           ((WORD32) (USP_ERR_OAM_CLI_BASE + 9))  /* 参数过多 */   
#define USP_ERR_OAM_CLI_READ_PASSWD_FILE         ((WORD32) (USP_ERR_OAM_CLI_BASE + 10)) /* 读密码文件错误 */   
#define USP_ERR_OAM_CLI_NON_DIGATAL              ((WORD32) (USP_ERR_OAM_CLI_BASE + 11)) /* 非数字 */   
#define USP_ERR_OAM_CLI_NUMBER_OVERFLOW          ((WORD32) (USP_ERR_OAM_CLI_BASE + 12)) /* 数值溢出 */  
#define USP_ERR_OAM_CLI_INIT_PRINTF_SHM          ((WORD32) (USP_ERR_OAM_CLI_BASE + 13)) /* 初始化打印控制共享内存错误 */  
#define USP_ERR_OAM_CLI_INIT_PRINTF_PIPE         ((WORD32) (USP_ERR_OAM_CLI_BASE + 14)) /* 初始化打印信息传递管道错误 */  
#define USP_ERR_OAM_CLI_CMD_CHILD_SET_OVERFLOW   ((WORD32) (USP_ERR_OAM_CLI_BASE + 15)) /* 设置的子命令集层数溢出 */  
#define USP_ERR_OAM_CLI_CMD_NODE_KEY_OVERFLOW    ((WORD32) (USP_ERR_OAM_CLI_BASE + 16)) /* 命令集节点数过多 */  
#define USP_ERR_OAM_CLI_CMD_PARAM_INDEX          ((WORD32) (USP_ERR_OAM_CLI_BASE + 17)) /* 命令参数索引错误 */  
#define USP_ERR_OAM_CLI_INIT_INNER_PIPE          ((WORD32) (USP_ERR_OAM_CLI_BASE + 18)) /* 初始化CLI内部信息传递管道错误 */  
#define USP_ERR_OAM_CLI_BIND_SOCKET              ((WORD32) (USP_ERR_OAM_CLI_BASE + 19)) /* 绑定socket错误 */  
#define USP_ERR_OAM_CLI_LISTEN_SOCKET            ((WORD32) (USP_ERR_OAM_CLI_BASE + 20)) /* 设置监听socket错误 */  
#define USP_ERR_OAM_CLI_CREATE_SOCKET            ((WORD32) (USP_ERR_OAM_CLI_BASE + 21)) /* 创建socket错误 */  
#define USP_ERR_OAM_CLI_INIT_ST_SHM              ((WORD32) (USP_ERR_OAM_CLI_BASE + 22)) /* 初始化信令跟踪共享内存错误 */  
#define USP_ERR_OAM_CLI_SEND_DATA                ((WORD32) (USP_ERR_OAM_CLI_BASE + 23)) /* 通过Socket发送数据失败 */  
#define USP_ERR_OAM_CLI_TIMEOUT_SEND             ((WORD32) (USP_ERR_OAM_CLI_BASE + 24)) /* 通过Socket发送数据超时 */  
#define USP_ERR_OAM_CLI_INIT_ST_PIPE             ((WORD32) (USP_ERR_OAM_CLI_BASE + 25)) /* 初始化信令跟踪信息传递管道错误 */  
#define USP_ERR_OAM_CLI_INIT_ST_BUF              ((WORD32) (USP_ERR_OAM_CLI_BASE + 26)) /* 初始化信令跟踪信息存储区域错误 */  
#define USP_ERR_OAM_CLI_LLRP_DECODE              ((WORD32) (USP_ERR_OAM_CLI_BASE + 27)) /* LLRP解码错误 */
#define USP_ERR_OAM_CLI_LLRP_ENCODE              ((WORD32) (USP_ERR_OAM_CLI_BASE + 28)) /* LLRP编码错误 */
#define USP_ERR_OAM_CLI_LLRP_UNKNOW_MSG          ((WORD32) (USP_ERR_OAM_CLI_BASE + 29)) /* 未知的LLRP消息 */
#define USP_ERR_OAM_CLI_LLRP_PARAMETER           ((WORD32) (USP_ERR_OAM_CLI_BASE + 30)) /* LLRP参数错误 */
#define USP_ERR_OAM_CLI_UNKNOW_MSG               ((WORD32) (USP_ERR_OAM_CLI_BASE + 31)) /* 消息号错误 */
#define USP_ERR_OAM_CLI_INIT_PRINTF_BUF          ((WORD32) (USP_ERR_OAM_CLI_BASE + 32)) /* 初始化打印控制信息存储区域错误 */  
#define USP_ERR_OAM_CLI_MALLOC_HANDLE            ((WORD32) (USP_ERR_OAM_CLI_BASE + 33)) /* 获取动态库句柄内存失败 */
#define USP_ERR_OAM_CLI_ATTACH_PRINTF            ((WORD32) (USP_ERR_OAM_CLI_BASE + 34)) /* 连接到打印控制共享内存失败 */

/***********************************************************
*   日志和异常探针(LAP)错误码                              *
***********************************************************/
#define USP_ERR_OAM_LAP_OPEN_FILE           ((WORD32) (USP_ERR_OAM_LAP_BASE +  1)) /* 打开文件失败 */
#define USP_ERR_OAM_LAP_READ_FILE           ((WORD32) (USP_ERR_OAM_LAP_BASE +  2)) /* 读文件失败 */
#define USP_ERR_OAM_LAP_WRITE_FILE          ((WORD32) (USP_ERR_OAM_LAP_BASE +  3)) /* 写文件失败 */
#define USP_ERR_OAM_LAP_FSEEK_FILE          ((WORD32) (USP_ERR_OAM_LAP_BASE +  4)) /* 定位文件失败 */
#define USP_ERR_OAM_LAP_FTP_SEND            ((WORD32) (USP_ERR_OAM_LAP_BASE +  5)) /* 向ftp服务器发送数据失败 */
#define USP_ERR_OAM_LAP_FTP_CREATE          ((WORD32) (USP_ERR_OAM_LAP_BASE +  6)) /* 与ftp服务器建链失败 */
#define USP_ERR_OAM_LAP_IN_MSG_ADAPTER      ((WORD32) (USP_ERR_OAM_LAP_BASE +  7)) /* LLRP格式解码错误 */
#define USP_ERR_OAM_LAP_OUT_MSG_ADAPTER     ((WORD32) (USP_ERR_OAM_LAP_BASE +  8)) /* LLRP格式编码错误 */
#define USP_ERR_OAM_LAP_NO_DATA             ((WORD32) (USP_ERR_OAM_LAP_BASE +  9)) /* 文件不存在，或者里面没有数据 */
#define USP_ERR_OAM_LAP_INVALID_MSG_LEN     ((WORD32) (USP_ERR_OAM_LAP_BASE + 10)) /* 消息长度不匹配 */
#define USP_ERR_OAM_LAP_INVALID_MSG         ((WORD32) (USP_ERR_OAM_LAP_BASE + 11)) /* 无效的消息*/
#define USP_ERR_OAM_LAP_SEND_MSG            ((WORD32) (USP_ERR_OAM_LAP_BASE + 12)) /* 发送消息失败 */
#define USP_ERR_OAM_LAP_RECV_MSG            ((WORD32) (USP_ERR_OAM_LAP_BASE + 13)) /* 接收消息失败 */
#define USP_ERR_OAM_LAP_PARA_NULL           ((WORD32) (USP_ERR_OAM_LAP_BASE + 14)) /* 参数为空指针 */
#define USP_ERR_OAM_LAP_MALLOC              ((WORD32) (USP_ERR_OAM_LAP_BASE + 15)) /* 分配内存失败 */
#define USP_ERR_OAM_LAP_BUFF_LACK           ((WORD32) (USP_ERR_OAM_LAP_BASE + 16)) /* 缓存空间不够 */
#define USP_ERR_OAM_LAP_FILE_LEN            ((WORD32) (USP_ERR_OAM_LAP_BASE + 17)) /* 文件长度非法 */
#define USP_ERR_OAM_LAP_SQNO_INVALID        ((WORD32) (USP_ERR_OAM_LAP_BASE + 18)) /* 序列号非法 */
#define USP_ERR_OAM_LAP_SQNO_POS            ((WORD32) (USP_ERR_OAM_LAP_BASE + 19)) /* 具有该序列号的条目在文件中的位置非法 */
#define USP_ERR_OAM_LAP_FILE_DESC           ((WORD32) (USP_ERR_OAM_LAP_BASE + 20)) /* 文件描述非法 */

/***********************************************************
*   LLRP工具箱(LTK)错误码                                  *
***********************************************************/
#define USP_LTK_ERR_FRAMEENCODER_CONSTRUCTOR    ((WORD32) (USP_LTK_ERR_BASE + 1)) /* 帧编码器构建错误 */
#define USP_LTK_ERR_FRAMEENCODE                 ((WORD32) (USP_LTK_ERR_BASE + 2)) /* 帧编码错误 */
#define USP_LTK_ERR_XMLTEXTENCODER_CONSTRUCTOR  ((WORD32) (USP_LTK_ERR_BASE + 3)) /* xml字符串编码器构建错误 */
#define USP_LTK_ERR_XMLTEXTENCODE               ((WORD32) (USP_LTK_ERR_BASE + 4)) /* xml字符串编码错误 */
#define USP_LTK_ERR_BUF_OVERFLOW                ((WORD32) (USP_LTK_ERR_BASE + 5)) /* 缓冲区溢出错误 */
#define USP_LTK_ERR_MALLOC_HANDLE               ((WORD32) (USP_LTK_ERR_BASE + 6)) /* 获取动态库句柄内存失败 */

/***********************************************************
*   虚拟操作系统(VOS)错误码                                *
***********************************************************/
#define USP_OSS_VOS_ERR_CONFIG_COREDUMP             ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x01)) /* 配置core dump错误 */     
#define USP_OSS_VOS_ERR_SET_EHTERNET_IP             ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x02)) /* 配置以太网IP错误 */
#define USP_OSS_VOS_ERR_SET_EHTERNET_NETMASK        ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x03)) /* 配置以太网子网掩码错误 */
#define USP_OSS_VOS_ERR_SET_EHTERNET_GATEWAY        ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x04)) /* 配置以太网网关错误 */
#define USP_OSS_VOS_ERR_DELETE_ROUTE                ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x05)) /* 删除路由错误 */     
#define USP_OSS_VOS_ERR_INVALID_TIMEZONE            ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x06)) /* 非法的时区值 */     
#define USP_OSS_VOS_ERR_SET_TIMEZONE                ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x07)) /* 设置时区错误 */     
#define USP_OSS_VOS_ERR_UPDATE_NTP                  ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x08)) /* ntp时间同步错误 */     
#define USP_OSS_VOS_ERR_CARETE_MQ                   ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x09)) /* 创建消息队列错误 */     
#define USP_OSS_VOS_ERR_CARETE_PROCESS              ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x0A)) /* 创建进程错误 */     
#define USP_OSS_VOS_ERR_CARETE_THREAD               ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x0B)) /* 创建线程错误 */     
#define USP_OSS_VOS_ERR_SEND_MSG                    ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x0C)) /* 发送消息错误 */     
#define USP_OSS_VOS_ERR_RECV_MSG                    ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x0D)) /* 接收消息错误 */     
#define USP_OSS_VOS_ERR_CARETE_MUTEX                ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x0E)) /* 创建互斥锁错误 */     
#define USP_OSS_VOS_ERR_INIT_MUTEX                  ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x0F)) /* 初始化互斥锁错误 */     
#define USP_OSS_VOS_ERR_MUTEX_INVALID               ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x10)) /* 非法的互斥锁 */ 
#define USP_OSS_VOS_ERR_OPEN_FILE                   ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x11)) /* 打开文件错误 */ 
#define USP_OSS_VOS_ERR_WRITE_FILE                  ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x12)) /* 写文件错误 */ 
#define USP_OSS_VOS_ERR_NULL_POINTER                ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x13)) /* 空指针 */
#define USP_OSS_VOS_ERR_OPEN_DIR                    ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x14)) /* 打开文件夹错误 */ 
#define USP_OSS_VOS_ERR_PROCESS_NOT_FIND            ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x15)) /* 没有找到对应的进程 */     
#define USP_OSS_VOS_ERR_DTTACH_SHM                  ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x16)) /* 断开到共享内存区域的连接错误 */
#define USP_OSS_VOS_ERR_SYNC_FILE                   ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x17)) /* 同步文件到flash错误 */ 
#define USP_OSS_VOS_ERR_RENAME_FILE                 ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x18)) /* 重命名文件错误 */ 
#define USP_OSS_VOS_ERR_GET_MUTEX                   ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x19)) /* 获取互斥锁错误 */
#define USP_OSS_VOS_ERR_DESTROY_THREAD              ((WORD32) (USP_OSS_VOS_ERR_BASE + 0x1A)) /* 销毁线程失败 */

/***********************************************************
*   Socket通信模块(NET)错误码                              *
***********************************************************/
#define USP_OSS_NET_ERR_IPADDR                      ((WORD32) (USP_OSS_NET_ERR_BASE + 1)) /* IP地址不正确错误 */
#define USP_OSS_NET_ERR_PROTOCOL_TYPE               ((WORD32) (USP_OSS_NET_ERR_BASE + 2)) /* 协议类型错误 */
#define USP_OSS_NET_ERR_CREATE_SOCKET               ((WORD32) (USP_OSS_NET_ERR_BASE + 3)) /* 创建Socket接口错误 */
#define USP_OSS_NET_ERR_BIND                        ((WORD32) (USP_OSS_NET_ERR_BASE + 4)) /* bind错误 */
#define USP_OSS_NET_ERR_NULL_POINTER                ((WORD32) (USP_OSS_NET_ERR_BASE + 5)) /* 空指针 */
#define USP_OSS_NET_ERR_CONNECT                     ((WORD32) (USP_OSS_NET_ERR_BASE + 6)) /* 创建Socket链接失败 */
#define USP_OSS_NET_ERR_ACCEPT                      ((WORD32) (USP_OSS_NET_ERR_BASE + 7)) /* accept错误 */
#define USP_OSS_NET_ERR_RECVFROM                    ((WORD32) (USP_OSS_NET_ERR_BASE + 8)) /* recvfrom错误 */
#define USP_OSS_NET_ERR_SENDTO                      ((WORD32) (USP_OSS_NET_ERR_BASE + 9)) /* sendto错误 */
#define USP_OSS_NET_ERR_INVALID_SOCKET_OPT          ((WORD32) (USP_OSS_NET_ERR_BASE + 10)) /* 非法的Socket选项 */
#define USP_OSS_NET_ERR_SEND                        ((WORD32) (USP_OSS_NET_ERR_BASE + 11)) /* send错误 */
#define USP_OSS_NET_ERR_RECV                        ((WORD32) (USP_OSS_NET_ERR_BASE + 12)) /* recv错误 */
#define USP_OSS_NET_ERR_TIMEOUT_SEND                ((WORD32) (USP_OSS_NET_ERR_BASE + 13)) /* send超时 */
#define USP_OSS_NET_ERR_INVALID_LINK_TYPE           ((WORD32) (USP_OSS_NET_ERR_BASE + 14)) /* 非法的链路物理类型 */
#define USP_OSS_NET_ERR_BIND_DEVICE                 ((WORD32) (USP_OSS_NET_ERR_BASE + 15)) /* 绑定网络设备接口错误 */
#define USP_OSS_NET_ERR_IPADDR_FORMAT               ((WORD32) (USP_OSS_NET_ERR_BASE + 16)) /* IP地址字符串格式错误 */
#define USP_OSS_NET_ERR_GET_SOCK_INFO               ((WORD32) (USP_OSS_NET_ERR_BASE + 17)) /* 获取Socket链接信息错误 */

/***********************************************************
*   定时器(TIMER)错误码                                    *
***********************************************************/
#define USP_OSS_TIMER_ALLOT_BUF_FAIL                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 1))  /*没有空闲的定时器可以分配*/  
#define USP_OSS_TIMER_BUF_ALLOTED                   ((WORD32) (USP_OSS_TIMER_ERR_BASE + 2))  /*该定时器已经用着*/  
#define USP_OSS_TIMER_BUF_CTRL_ERROR                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 3))  /*操作定时器错误*/  
#define USP_OSS_TIMER_P_ERROR                       ((WORD32) (USP_OSS_TIMER_ERR_BASE + 4))  /* P操作失败 */   
#define USP_OSS_TIMER_BUF_INDEDX_ERROR              ((WORD32) (USP_OSS_TIMER_ERR_BASE + 5))  /*缓存索引错误*/   
#define USP_OSS_TIMER_NOT_EXIST                     ((WORD32) (USP_OSS_TIMER_ERR_BASE + 6))  /*相应定时器不存在*/   
#define USP_OSS_TIMER_GET_POINTER_FAIL              ((WORD32) (USP_OSS_TIMER_ERR_BASE + 7))  /*在获取全局指针得时候错误*/   
#define USP_OSS_TIMER_ALREADY_EXISTS                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 8))  /*已经设置了该定时器*/   
#define USP_OSS_TIMER_FUNC_PARAM_PTR_NULL           ((WORD32) (USP_OSS_TIMER_ERR_BASE + 9))  /* 函数参数为空指针 */
#define USP_OSS_TIMER_CREATE_SHM_ERROR              ((WORD32) (USP_OSS_TIMER_ERR_BASE + 10)) /* 创建共享内存区有误 */
#define USP_OSS_TIMER_GET_SHM_ERROR                 ((WORD32) (USP_OSS_TIMER_ERR_BASE + 11)) /* 获得共享内存区有误 */
#define USP_OSS_TIMER_CTRL_SHM_ERROR                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 12)) /* 操作共享内存区有误 */
#define USP_OSS_TIMER_CTRL_SEM_ERROR                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 13)) /* 操作信号量出错 */
#define USP_OSS_TIMER_CREATE_SEM_ERROR              ((WORD32) (USP_OSS_TIMER_ERR_BASE + 14)) /* 创建信号量出错 */
#define USP_OSS_TIMER_GET_SEM_ERROR                 ((WORD32) (USP_OSS_TIMER_ERR_BASE + 15)) /* 获取信号量出错 */
#define USP_OSS_TIMER_SET_TIMER_ERROR               ((WORD32) (USP_OSS_TIMER_ERR_BASE + 16)) /* 设置定时器出错 */
#define USP_OSS_TIMER_SEM_TAKE_ERROR                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 17)) /* 获取信号量出错 */
#define USP_OSS_TIMER_V_ERROR                       ((WORD32) (USP_OSS_TIMER_ERR_BASE + 18)) /* V操作失败 */
#define USP_OSS_TIMER_SEM_GIVE_ERROR                ((WORD32) (USP_OSS_TIMER_ERR_BASE + 19)) /* 释放信号量出错 */ 
#define USP_OSS_TIMER_SHMAT_ERROR                   ((WORD32) (USP_OSS_TIMER_ERR_BASE + 20)) /* 连接共享内存失败 */
#define USP_OSS_TIMER_MALLOC_ERROR                  ((WORD32) (USP_OSS_TIMER_ERR_BASE + 21)) /* 动态申请内存失败 */
#define USP_OSS_TIMER_SENDMSG_ERROR                 ((WORD32) (USP_OSS_TIMER_ERR_BASE + 22)) /* 发送消息失败 */

/***********************************************************
*   通信模块(COMM)错误码                                   *
***********************************************************/
#define USP_COMM_ERR_RECV_MSG                   ((WORD32) (USP_COMM_ERR_BASE + 1)) /* 接收消息错误 */
#define USP_COMM_ERR_UNKNOW_MSG                 ((WORD32) (USP_COMM_ERR_BASE + 2)) /* 未知的消息 */
#define USP_COMM_ERR_CREATE_LINK_CTRL_TASK      ((WORD32) (USP_COMM_ERR_BASE + 3)) /* 创建链路管理线程错误 */
#define USP_COMM_ERR_CREATE_LINK_CTRL_SOCKET    ((WORD32) (USP_COMM_ERR_BASE + 4)) /* 创建链路管理线程监听UDP/TCP端口错误 */
#define USP_COMM_ERR_CONNECT                    ((WORD32) (USP_COMM_ERR_BASE + 5)) /* 建立Socket链接错误 */
#define USP_COMM_ERR_SELECT                     ((WORD32) (USP_COMM_ERR_BASE + 6)) /* select错误 */
#define USP_COMM_ERR_ACCEPT                     ((WORD32) (USP_COMM_ERR_BASE + 7)) /* accept错误 */
#define USP_COMM_ERR_READ_LINK_CTRL_MSG         ((WORD32) (USP_COMM_ERR_BASE + 8)) /* 读取链路管理线程控制消息错误 */
#define USP_COMM_ERR_CREATE_SOCKET_LISTEN       ((WORD32) (USP_COMM_ERR_BASE + 9)) /* 创建Socket监听端口错误 */
#define USP_COMM_ERR_FULL_LINK_CTRL             ((WORD32) (USP_COMM_ERR_BASE + 10)) /* 链路管理线程控制结构已满 */
#define USP_COMM_ERR_CONFIG_INFO_OVERLOAD       ((WORD32) (USP_COMM_ERR_BASE + 11)) /* 通信配置信息过大 */
#define USP_COMM_ERR_OPEN_LINK                  ((WORD32) (USP_COMM_ERR_BASE + 12)) /* 回调打开链路函数错误 */
#define USP_COMM_ERR_FULL_LINK_ID_CTRL          ((WORD32) (USP_COMM_ERR_BASE + 13)) /* 链路控制结构已满 */
#define USP_COMM_ERR_INVALID_LINK_STATUS        ((WORD32) (USP_COMM_ERR_BASE + 14)) /* 非法的链路状态 */
#define USP_COMM_ERR_INVALID_LINK_TYPE          ((WORD32) (USP_COMM_ERR_BASE + 15)) /* 非法的链路物理类型 */
#define USP_COMM_ERR_INVALID_LINK_ID            ((WORD32) (USP_COMM_ERR_BASE + 16)) /* 非法的链路标识符 */
#define USP_COMM_ERR_CLOSE_LINK                 ((WORD32) (USP_COMM_ERR_BASE + 17)) /* 链路关闭错误 */
#define USP_COMM_ERR_FULL_LLRP_LINK_CTRL        ((WORD32) (USP_COMM_ERR_BASE + 18)) /* llrp链路控制结构已满 */
#define USP_COMM_ERR_INVALID_APP_TYPE           ((WORD32) (USP_COMM_ERR_BASE + 19)) /* 非法的链路应用类型 */
#define USP_COMM_ERR_NULL_POINTER               ((WORD32) (USP_COMM_ERR_BASE + 20)) /* 空指针 */   
#define USP_COMM_ERR_INVALID_LINK               ((WORD32) (USP_COMM_ERR_BASE + 21)) /* 非法的链路 */
#define USP_COMM_ERR_SEND_CONN_ATTEMPT_EVENT    ((WORD32) (USP_COMM_ERR_BASE + 22)) /* 发送ConnectionAttemptEvent失败 */
#define USP_COMM_ERR_SEND_LLRP_KEEPLIVE         ((WORD32) (USP_COMM_ERR_BASE + 23)) /* 发送KeepLive消息失败 */
#define USP_COMM_ERR_LLRP_MSG_OVERLOAD          ((WORD32) (USP_COMM_ERR_BASE + 24)) /* 接收数据时发现llrp消息的长度超过了预设的缓冲区 */
#define USP_COMM_ERR_LLRP_MSG_LEN               ((WORD32) (USP_COMM_ERR_BASE + 25)) /* llrp消息长度错误 */
#define USP_COMM_ERR_LLRP_ENCODE_SERIAL_FRAME   ((WORD32) (USP_COMM_ERR_BASE + 26)) /* 编码llrp串口数据帧错误 */
#define USP_COMM_ERR_LLRP_UNKNOW_MSG            ((WORD32) (USP_COMM_ERR_BASE + 27)) /* 未知的llrp消息 */
#define USP_COMM_ERR_LLRP_DECODE_SERIAL_FRAME   ((WORD32) (USP_COMM_ERR_BASE + 28)) /* 解码llrp串口数据帧错误 */
#define USP_COMM_ERR_LLRP_KEEPLIVE              ((WORD32) (USP_COMM_ERR_BASE + 29)) /* llrp链路保活失败 */
#define USP_COMM_ERR_UNKNOW_CLI_CMD             ((WORD32) (USP_COMM_ERR_BASE + 30)) /* 未知的Cli命令 */
#define USP_COMM_ERR_LLRP_RECV                  ((WORD32) (USP_COMM_ERR_BASE + 31)) /* llrp链路接收消息失败 */
#define USP_COMM_ERR_LLRP_DECODE_MSG            ((WORD32) (USP_COMM_ERR_BASE + 32)) /* 解码llrp消息失败 */
#define USP_COMM_ERR_LLRP_MSG                   ((WORD32) (USP_COMM_ERR_BASE + 33)) /* llrp消息内容错误 */
#define USP_COMM_ERR_FULL_CONFIG                ((WORD32) (USP_COMM_ERR_BASE + 34)) /* 通信配置信息空间已满 */
#define USP_COMM_ERR_LLRP_CONN_EVENT_TIMEOUT    ((WORD32) (USP_COMM_ERR_BASE + 35)) /* 在规定的时间内没有收到成功的ConnectionAttemptEvent事件 */
#define USP_COMM_ERR_CREATE_MQ                  ((WORD32) (USP_COMM_ERR_BASE + 36)) /* 创建消息队列错误 */
#define USP_COMM_ERR_START_COMM                 ((WORD32) (USP_COMM_ERR_BASE + 37)) /* 启动通信模块错误 */
#define USP_COMM_ERR_LINK_NOTICE_TYPE           ((WORD32) (USP_COMM_ERR_BASE + 38)) /* 链路通知信息类型错误 */
#define USP_COMM_ERR_OPEN_SERIAL_PORT           ((WORD32) (USP_COMM_ERR_BASE + 39)) /* 打开串口错误 */
#define USP_COMM_ERR_SET_ATTR_SERIAL_PORT       ((WORD32) (USP_COMM_ERR_BASE + 40)) /* 设置串口属性错误 */
#define USP_COMM_ERR_CREATE_CONN_CTRL_TASK      ((WORD32) (USP_COMM_ERR_BASE + 41)) /* 创建网络建链线程错误 */
#define USP_COMM_ERR_FULL_CONN_CTRL             ((WORD32) (USP_COMM_ERR_BASE + 42)) /* 建链管理线程控制结构已满 */
#define USP_COMM_ERR_CREATE_COMM_TASK           ((WORD32) (USP_COMM_ERR_BASE + 43)) /* 创建通信模块主任务失败 */
#define USP_COMM_ERR_DECODE_CRC_NOT_MATCH       ((WORD32) (USP_COMM_ERR_BASE + 44)) /* 解码串口数据帧时CRC校验不匹配 */
#define USP_COMM_ERR_DECODE_OVERLOAD            ((WORD32) (USP_COMM_ERR_BASE + 45)) /* 解码串口数据帧时发现帧长度超过了预设的缓冲区 */
#define USP_COMM_ERR_DECODE_FRAME_LENGTH        ((WORD32) (USP_COMM_ERR_BASE + 46)) /* 串口数据帧长度错误 */
#define USP_COMM_ERR_DECODE_FRAME_FORMAT        ((WORD32) (USP_COMM_ERR_BASE + 47)) /* 串口数据帧格式错误 */
#define USP_COMM_ERR_TIMEOUT_SEND               ((WORD32) (USP_COMM_ERR_BASE + 48)) /* 发送数据超时 */
#define USP_COMM_ERR_CREATE_CONN_CTRL_MQ        ((WORD32) (USP_COMM_ERR_BASE + 49)) /* 创建建链管理线程消息队列错误 */
#define USP_COMM_ERR_ETC_FULL_LINK_CTRL         ((WORD32) (USP_COMM_ERR_BASE + 50)) /* etc链路控制结构已满 */
#define USP_COMM_ERR_ETC_ENCODE_FRAME           ((WORD32) (USP_COMM_ERR_BASE + 51)) /* 编码etc数据帧错误 */
#define USP_COMM_ERR_DECODE_BCC_NOT_MATCH       ((WORD32) (USP_COMM_ERR_BASE + 52)) /* 解码etc数据帧时BCC校验不匹配 */
#define USP_COMM_ERR_ETC_DECODE_FRAME           ((WORD32) (USP_COMM_ERR_BASE + 53)) /* 解码etc数据帧错误 */
#define USP_COMM_ERR_ETC_UNKNOW_CMDTYPE         ((WORD32) (USP_COMM_ERR_BASE + 54)) /* 未知的etc命令类型 */
#define USP_COMM_ERR_MALLOC_CONGESTION_BUF      ((WORD32) (USP_COMM_ERR_BASE + 55)) /* 获取拥塞控制缓存失败 */
#define USP_COMM_ERR_FULL_CONGESTION_BUF        ((WORD32) (USP_COMM_ERR_BASE + 56)) /* 拥塞缓存已满 */
#define USP_COMM_ERR_INVALID_PARAM              ((WORD32) (USP_COMM_ERR_BASE + 57)) /* 函数参数错误 */
#define USP_COMM_ERR_FULL_SEND_BUF              ((WORD32) (USP_COMM_ERR_BASE + 58)) /* 通信链路的发送缓冲区已满 */
#define USP_COMM_ERR_INSERT_HOLD_STORAGE        ((WORD32) (USP_COMM_ERR_BASE + 59)) /* 保存数据到断链缓存存储区域失败 */
#define USP_COMM_ERR_GET_HOLD_STORAGE           ((WORD32) (USP_COMM_ERR_BASE + 60)) /* 读取断链缓存数据失败 */
#define USP_COMM_ERR_DELETE_HOLD_STORAGE        ((WORD32) (USP_COMM_ERR_BASE + 61)) /* 删除断链缓存数据失败 */
#define USP_COMM_ERR_TRUNCATE_HOLD_STORAGE      ((WORD32) (USP_COMM_ERR_BASE + 62)) /* 清空断链缓存数据失败 */
#define USP_COMM_ERR_HOLD_RECV_UNKNOW_DATA      ((WORD32) (USP_COMM_ERR_BASE + 63)) /* 断链缓存处理任务收到未知类型数据 */
#define USP_COMM_ERR_HOLD_SEQUENCE_NOT_MATCH    ((WORD32) (USP_COMM_ERR_BASE + 64)) /* 断链缓存处理任务收到序列号不匹配的应答消息 */
#define USP_COMM_ERR_HOLD_SEND_UNKNOW_DATA      ((WORD32) (USP_COMM_ERR_BASE + 65)) /* 断链缓存处理任务发送未知类型数据 */
#define USP_COMM_ERR_ZTE_MSG_MAGIC_NOT_MATCH    ((WORD32) (USP_COMM_ERR_BASE + 66)) /* 接收数据时发现zte私有消息的魔术字不匹配 */
#define USP_COMM_ERR_ZTE_MSG_OVERLOAD           ((WORD32) (USP_COMM_ERR_BASE + 67)) /* 接收数据时发现zte私有消息的长度超过了预设的缓冲区 */
#define USP_COMM_ERR_ZTE_KEEPLIVE               ((WORD32) (USP_COMM_ERR_BASE + 68)) /* zte私有链路保活失败 */
#define USP_COMM_ERR_FULL_UHF_UDP_LINK_CTRL     ((WORD32) (USP_COMM_ERR_BASE + 69)) /* 超高频UDP链路控制结构已满 */
#define USP_COMM_ERR_RECV_CLOSE_LINK_MSG        ((WORD32) (USP_COMM_ERR_BASE + 70)) /* 收到请求关闭链路消息 */
#define USP_COMM_ERR_CONFIG_CHANGE              ((WORD32) (USP_COMM_ERR_BASE + 71)) /* 通信配置发生了变化 */
#define USP_COMM_ERR_CLOSE_OLD_LINK             ((WORD32) (USP_COMM_ERR_BASE + 72)) /* 关闭原有链路 */
#define USP_COMM_ERR_RECV_DMP_CLOSE_MSG         ((WORD32) (USP_COMM_ERR_BASE + 73)) /* 收到诊断测试发出的链路关闭消息 */
#define USP_COMM_ERR_REJECT_NEW_LINK            ((WORD32) (USP_COMM_ERR_BASE + 74)) /* 拒绝新链路 */
#define USP_COMM_ERR_SEND_LINK_CTRL_MSG         ((WORD32) (USP_COMM_ERR_BASE + 75)) /* 向链路管理线程发送消息错误 */
#define USP_COMM_ERR_CREATE_LINK_CTRL_TCP       ((WORD32) (USP_COMM_ERR_BASE + 76)) /* 创建链路管理线程TCP链路错误 */
#define USP_COMM_ERR_CREATE_LINK_CTRL_PIPE      ((WORD32) (USP_COMM_ERR_BASE + 77)) /* 创建链路管理线程PIPE链路错误 */
#define USP_COMM_ERR_INTER_BOARD_MSG_OVERLOAD   ((WORD32) (USP_COMM_ERR_BASE + 78)) /* 接收数据时发现板间消息的长度超过了预设的缓冲区 */
#define USP_COMM_ERR_INTER_BOARD_KEEPLIVE       ((WORD32) (USP_COMM_ERR_BASE + 79)) /* 板间通信链路保活失败 */
#define USP_COMM_ERR_INTER_BOARD_INVALID_TNO    ((WORD32) (USP_COMM_ERR_BASE + 80)) /* 板间通信进行消息转发时任务号错误 */     
#define USP_COMM_ERR_MPI_INVALID_HEAD           ((WORD32) (USP_COMM_ERR_BASE + 81)) /* mpi协议起始头字节错误 */
#define USP_COMM_ERR_MPI_MSG_OVERLOAD           ((WORD32) (USP_COMM_ERR_BASE + 82)) /* 接收数据时发现mpi消息的长度超过了预设的缓冲区 */
#define USP_COMM_ERR_MPI_MSG_CRC                ((WORD32) (USP_COMM_ERR_BASE + 83)) /* mpi协议消息CRC校验错误 */
#define USP_COMM_ERR_MPI_DECODE_UNCOMPLETE      ((WORD32) (USP_COMM_ERR_BASE + 84)) /* mpi协议消息解码未完成 */
#define USP_COMM_ERR_FULL_MPI_LINK_CTRL         ((WORD32) (USP_COMM_ERR_BASE + 85)) /* mpi链路控制结构已满 */
#define USP_COMM_ERR_MALLOC_HANDLE              ((WORD32) (USP_COMM_ERR_BASE + 86)) /* 获取动态库句柄内存失败 */
#define USP_COMM_ERR_ZTE_UNKNOW_MSG             ((WORD32) (USP_COMM_ERR_BASE + 87)) /* 未知的zte消息 */
#define USP_COMM_ERR_SMS_DECODE_FRAME           ((WORD32) (USP_COMM_ERR_BASE + 88)) /* 解码sms数据帧错误 */
#define USP_COMM_ERR_SMS_SEND                   ((WORD32) (USP_COMM_ERR_BASE + 89)) /* 发送sms数据帧错误 */
#define USP_COMM_ERR_SMS_RECV                   ((WORD32) (USP_COMM_ERR_BASE + 90)) /* 接收sms数据帧错误 */
#define USP_COMM_ERR_SMS_DELE                   ((WORD32) (USP_COMM_ERR_BASE + 91)) /* 删除短消息错误 */
#define USP_COMM_ERR_SMS_TEL_LEN                ((WORD32) (USP_COMM_ERR_BASE + 92)) /* 电话号码长度不正确 */
#define USP_COMM_ERR_SMS_PDU_TYPE               ((WORD32) (USP_COMM_ERR_BASE + 93)) /* 未知的PDU编码编码类型 */
#define USP_COMM_ERR_SMS_CSQ                    ((WORD32) (USP_COMM_ERR_BASE + 94)) /* 查询短信信号强度错误 */

/***********************************************************
*   配置模块(CMP)错误码                                   *
***********************************************************/
#define   USP_OAM_CMP_GET_MSGQUE_ERR            ((WORD32) (USP_OAM_CMP_ERR_BASE + 1))   //获取消息队列出错
#define   USP_OAM_CMP_RECV_MSGQUE_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 2))   //接受消息出错
#define   USP_OAM_CMP_PARAM_POINTER_NULL        ((WORD32) (USP_OAM_CMP_ERR_BASE + 3))   //参数指针为空
#define   USP_OAM_CMP_INVALID_PROC_STATE        ((WORD32) (USP_OAM_CMP_ERR_BASE + 4))   //非法进程状态
#define   USP_OAM_CMP_INVALID_MSG               ((WORD32) (USP_OAM_CMP_ERR_BASE + 5))   //无效的消息
#define   USP_OAM_CMP_CFG_FILE_DATA_ERR         ((WORD32) (USP_OAM_CMP_ERR_BASE + 6))   //配置文件中数据有误
#define   USP_OAM_CMP_FLASH_DATA_ERR            ((WORD32) (USP_OAM_CMP_ERR_BASE + 7))   //FLASH中数据有误
#define   USP_OAM_CMP_EEPROM_DATA_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 8))   //EEPROM中数据有误
#define   USP_OAM_CMP_DATA_SIZE_ERR             ((WORD32) (USP_OAM_CMP_ERR_BASE + 9))   //数据大小不匹配
#define   USP_OAM_CMP_CRC_ERR                   ((WORD32) (USP_OAM_CMP_ERR_BASE + 10))  //crc校验数据不匹配
#define   USP_OAM_CMP_CFG_FILE_NONE             ((WORD32) (USP_OAM_CMP_ERR_BASE + 11))  //没有配置文件
#define   USP_OAM_CMP_MALLOC_ERR                ((WORD32) (USP_OAM_CMP_ERR_BASE + 12))  //分配动态内存有误
#define   USP_OAM_CMP_SEND_MSGQUE_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 13))  //发送消息出错
#define   USP_OAM_CMP_READ_EEPROM_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 14))  //读取eeprom出错
#define   USP_OAM_CMP_FILE_CTL_ERR              ((WORD32) (USP_OAM_CMP_ERR_BASE + 15))  //对文件的读写定位等操作有误
#define   USP_OAM_CMP_CFG_ITEM_ERR              ((WORD32) (USP_OAM_CMP_ERR_BASE + 16))  //不存在这样的配置项
#define   USP_OAM_CMP_READ_FLASH_ERR            ((WORD32) (USP_OAM_CMP_ERR_BASE + 17))  //读取flash出错
#define   USP_OAM_CMP_WRITE_FLASH_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 18))  //写flash出错
#define   USP_OAM_CMP_WRITE_EEPROM_ERR          ((WORD32) (USP_OAM_CMP_ERR_BASE + 19))  //写eeprom出错
#define   USP_OAM_CMP_OUT_MSG_ADAPTER_ERR       ((WORD32) (USP_OAM_CMP_ERR_BASE + 20))  //归一化输出适配出错
#define   USP_OAM_CMP_IN_MSG_ADAPTER_ERR        ((WORD32) (USP_OAM_CMP_ERR_BASE + 21))  //归一化输入适配出错
#define   USP_OAM_CMP_MODULE_CONF_FILE_ERR      ((WORD32) (USP_OAM_CMP_ERR_BASE + 22))  //配置模块的配置文件有误
#define   USP_OAM_CMP_SET_DEFAULT_CFG_ERR       ((WORD32) (USP_OAM_CMP_ERR_BASE + 23))  //归一化设置默认配置出错
#define   USP_OAM_CMP_INIT_EEPROM_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 24))  //eeprom初始化出错
#define   USP_OAM_CMP_MEMORY_BEYOND_ERR         ((WORD32) (USP_OAM_CMP_ERR_BASE + 25))  //内存越界          
#define   USP_OAM_CMP_INIT_EPLD_ERR             ((WORD32) (USP_OAM_CMP_ERR_BASE + 26))  //初始化epld出错  
#define   USP_OAM_CMP_ERASE_FLASH_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 27))  //擦除flash出错
#define   USP_OAM_CMP_CFG_DATA_TOO_LONG         ((WORD32) (USP_OAM_CMP_ERR_BASE + 28))  //配置数据过大，无法发送消息返回，可以修改消息缓存大小USP_OAM_CMP_MAX_MSG_LEN
#define   USP_OAM_CMP_INIT_IOPORT_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 29))  //初始化IOPORT出错  
#define   USP_OAM_CMP_INIT_FLASH_ERR            ((WORD32) (USP_OAM_CMP_ERR_BASE + 30))  //初始化FLASH出错  
#define   USP_OAM_CMP_DEV_MODLE_NOT_MATCH_ERR   ((WORD32) (USP_OAM_CMP_ERR_BASE + 31))  //机型不匹配
#define   USP_OAM_CMP_PARSE_DEFAULT_CFG_ERR     ((WORD32) (USP_OAM_CMP_ERR_BASE + 32))  //解析默认配置错误
#define   USP_OAM_CMP_READ_FILE_ERR             ((WORD32) (USP_OAM_CMP_ERR_BASE + 33))  //读配置文件错误
#define   USP_OAM_CMP_PARSE_FILE_ERR            ((WORD32) (USP_OAM_CMP_ERR_BASE + 34))  //解析配置文件错误
#define   USP_OAM_CMP_PARSE_KEY_ERR             ((WORD32) (USP_OAM_CMP_ERR_BASE + 35))  //解析关键字错误
#define   USP_OAM_CMP_SEARCH_KEY_ERR            ((WORD32) (USP_OAM_CMP_ERR_BASE + 36))  //搜索关键字错误
#define   USP_OAM_CMP_INVALID_TYPE_ERR          ((WORD32) (USP_OAM_CMP_ERR_BASE + 37))  //数据类型错误
#define   USP_OAM_CMP_OPEN_FILE_ERR             ((WORD32) (USP_OAM_CMP_ERR_BASE + 38))  //打开配置文件错误
#define   USP_OAM_CMP_MALLOC_HANDLE_ERR         ((WORD32) (USP_OAM_CMP_ERR_BASE + 39))  //获取动态库句柄内存失败
#define   USP_OAM_CMP_KEY_TOO_LARGE_ERR         ((WORD32) (USP_OAM_CMP_ERR_BASE + 40))  //关键字过大
#define   USP_OAM_CMP_STRING_TOO_LARGE_ERR      ((WORD32) (USP_OAM_CMP_ERR_BASE + 41))  //字符串值过大
#define   USP_OAM_CMP_INVALID_LINK_TYPE_ERR     ((WORD32) (USP_OAM_CMP_ERR_BASE + 42))  //非法的链路物理类型
#define   USP_OAM_CMP_INVALID_RS_ATTR_INDEX_ERR ((WORD32) (USP_OAM_CMP_ERR_BASE + 43))  //非法的串口属性索引
#define   USP_OAM_CMP_READ_SYSDATA_ERR          ((WORD32) (USP_OAM_CMP_ERR_BASE + 44))  //读取系统参数区出错
#define   USP_OAM_CMP_CREATE_SOCK_ERR           ((WORD32) (USP_OAM_CMP_ERR_BASE + 45))  //创建socket套接字失败
#define   USP_OAM_CMP_IOCTL_ERR                 ((WORD32) (USP_OAM_CMP_ERR_BASE + 46))  //调用ioctl失败

/***********************************************************
*   IP发现模块(IPD)错误码                                   *
***********************************************************/
#define   USP_COMM_IPD_INVOKE_THREAD_FAIL               ((WORD32) (USP_COMM_IPD_ERR_BASE + 1)) /* 启动线程失败 */
#define   USP_COMM_IPD_PARAM_POINTER_NULL               ((WORD32) (USP_COMM_IPD_ERR_BASE + 2)) /* 参数指针为空指针 */
#define   USP_COMM_IPD_CREATE_SOCK_ERROR                ((WORD32) (USP_COMM_IPD_ERR_BASE + 3)) /* 创建socket套接字失败 */
#define   USP_COMM_IPD_BIND_SOCK_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 4)) /* bind()失败 */            
#define   USP_COMM_IPD_ADD_MULTICAST_FAIL               ((WORD32) (USP_COMM_IPD_ERR_BASE + 5)) /* 加入多播组失败 */
#define   USP_COMM_IPD_SET_MULTICAST_TTL_FAIL           ((WORD32) (USP_COMM_IPD_ERR_BASE + 6)) /* 设置ttl失败 */            
#define   USP_COMM_IPD_SET_MULTICAST_LOOP_FAIL          ((WORD32) (USP_COMM_IPD_ERR_BASE + 7)) /* 设置loop失败 */               
#define   USP_COMM_IPD_DE_ENCODE_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 8)) /* llrp编解码有误 */
#define   USP_COMM_IPD_MULTICAST_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 9)) /* 多播出错 */
#define   USP_COMM_IPD_SOCK_RECV_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 10)) /* 接受数据出错 */
#define   USP_COMM_IPD_SET_IFADDR_ERROR                 ((WORD32) (USP_COMM_IPD_ERR_BASE + 11)) /* 添加新接口到网卡上 */                                
#define   USP_COMM_IPD_SET_NETMASK_ERROR                ((WORD32) (USP_COMM_IPD_ERR_BASE + 12)) /* 设置掩码有误 */                            
#define   USP_COMM_IPD_CONNECT_SOCK_ERROR               ((WORD32) (USP_COMM_IPD_ERR_BASE + 13)) /* connect有误 */
#define   USP_COMM_IPD_GET_IFFLAGS_ERROR                ((WORD32) (USP_COMM_IPD_ERR_BASE + 14)) /* 获取接口信息有误 */
#define   USP_COMM_IPD_SET_IFFLAGS_ERROR                ((WORD32) (USP_COMM_IPD_ERR_BASE + 15)) /* 设置接口信息有误 */
#define   USP_COMM_IPD_SEND_MSG_ERROR                   ((WORD32) (USP_COMM_IPD_ERR_BASE + 16)) /* 发送消息有误 */
#define   USP_COMM_IPD_SOCK_SEND_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 17)) /* 发送数据有误 */
#define   USP_COMM_IPD_RCV_MSG_ERR                      ((WORD32) (USP_COMM_IPD_ERR_BASE + 18)) /* 接受数据有误 */
#define   USP_COMM_IPD_GET_MSGQUEUE_ERR                 ((WORD32) (USP_COMM_IPD_ERR_BASE + 19)) /* 获取消息队列有误 */
#define   USP_COMM_IPD_INVALID_SOCKET_FD                ((WORD32) (USP_COMM_IPD_ERR_BASE + 20)) /* 无效的套接字 */
#define   USP_COMM_IPD_DEL_TEMP_IP_ERROR                ((WORD32) (USP_COMM_IPD_ERR_BASE + 21)) /* 删除临时ip有误 */
#define   USP_COMM_IPD_SIGACTION_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 22)) /* 使用sigaction出错 */
#define   USP_COMM_IPD_SELECT_ERROR                     ((WORD32) (USP_COMM_IPD_ERR_BASE + 23)) /* 使用select出错 */ 
#define   USP_COMM_IPD_CHECKCRC_ERROR                   ((WORD32) (USP_COMM_IPD_ERR_BASE + 24)) /* CRC校验失败 */
#define   USP_COMM_IPD_WAITMSG_OVERTIME_ERROR           ((WORD32) (USP_COMM_IPD_ERR_BASE + 25)) /* 等待消息超时处理 */
#define   USP_COMM_IPD_MAGIC_ERROR                      ((WORD32) (USP_COMM_IPD_ERR_BASE + 26)) /* 魔术字错误 */
#define   USP_COMM_IPD_CHECKWORD_ERROR                  ((WORD32) (USP_COMM_IPD_ERR_BASE + 27)) /* 校验字错误 */
#define   USP_COMM_IPD_IOCTL_ERROR                      ((WORD32) (USP_COMM_IPD_ERR_BASE + 28)) /* ioctl错误 */
#define   USP_COMM_IPD_INVALID_MSG                      ((WORD32) (USP_COMM_IPD_ERR_BASE + 29)) /* 非法消息 */ 
#define   USP_COMM_IPD_DECODEMESSAGE_ERROR              ((WORD32) (USP_COMM_IPD_ERR_BASE + 30)) /* 解码失败 */
#define   USP_COMM_IPD_ENCODEMESSAGE_ERROR              ((WORD32) (USP_COMM_IPD_ERR_BASE + 31)) /* 编码失败 */
#define   USP_COMM_IPD_MSGLEN_ERROR                     ((WORD32) (USP_COMM_IPD_ERR_BASE + 32)) /* 消息长度错误 */

/***********************************************************
*   系统主控(SCP)错误码                                    *
***********************************************************/
#define USP_OSS_SCP_ERR_INVALID_TNO             ((WORD32) (USP_ERR_OSS_SCP_BASE + 1)) /* 错误的任务号 */     
#define USP_OSS_SCP_ERR_INVALID_TASK            ((WORD32) (USP_ERR_OSS_SCP_BASE + 2)) /* 任务不可用 */  
#define USP_OSS_SCP_ERR_POWERON                 ((WORD32) (USP_ERR_OSS_SCP_BASE + 3)) /* 上电失败 */  
#define USP_OSS_SCP_ERR_RECV_POWERON_TIMEOUT    ((WORD32) (USP_ERR_OSS_SCP_BASE + 4)) /* 接收上电应答超时 */     
#define USP_OSS_SCP_ERR_RECV_POWERON_FAIL       ((WORD32) (USP_ERR_OSS_SCP_BASE + 5)) /* 收到上电失败应答 */     
#define USP_OSS_SCP_ERR_RECV_SERVICE_MSG        ((WORD32) (USP_ERR_OSS_SCP_BASE + 6)) /* 提供系统控制服务时接收消息失败 */ 
#define USP_OSS_SCP_ERR_RECV_UNKNOW_MSG         ((WORD32) (USP_ERR_OSS_SCP_BASE + 7)) /* 收到未知的消息 */ 
#define USP_OSS_SCP_ERR_SEND_KEEPALIVE          ((WORD32) (USP_ERR_OSS_SCP_BASE + 8)) /* 发送握手消息错误 */  
#define USP_OSS_SCP_ERR_KEEPLIVE                ((WORD32) (USP_ERR_OSS_SCP_BASE + 9)) /* 应用任务死掉 */  
#define USP_OSS_SCP_ERR_CLI_CMD                 ((WORD32) (USP_ERR_OSS_SCP_BASE + 10)) /* CLI命令码错误 */  
#define USP_OSS_SCP_ERR_CLI_PROCESS             ((WORD32) (USP_ERR_OSS_SCP_BASE + 11)) /* CLI命令处理错误 */  
#define USP_OSS_SCP_ERR_INVALID_MQ              ((WORD32) (USP_ERR_OSS_SCP_BASE + 12)) /* 消息队列不可用 */  
#define USP_OSS_SCP_ERR_INVALID_POWERON_TNO     ((WORD32) (USP_ERR_OSS_SCP_BASE + 13)) /* 需要上电的任务号不正确 */  
#define USP_OSS_SCP_ERR_SET_TIME                ((WORD32) (USP_ERR_OSS_SCP_BASE + 14)) /* 设置系统时间错误 */  
#define USP_OSS_SCP_ERR_MALLOC_WTD_CTRL         ((WORD32) (USP_ERR_OSS_SCP_BASE + 15)) /* 获取看门狗控制内存失败 */
#define USP_OSS_SCP_ERR_INIT_COMM               ((WORD32) (USP_ERR_OSS_SCP_BASE + 16)) /* 初始化通信设施失败 */
#define USP_OSS_SCP_ERR_NULL_POINTER            ((WORD32) (USP_ERR_OSS_SCP_BASE + 17)) /* 空指针 */
#define USP_OSS_SCP_ERR_OPEN_RESET_STATUS_FILE  ((WORD32) (USP_ERR_OSS_SCP_BASE + 18)) /* 打开重启状态记录文件失败 */
#define USP_OSS_SCP_ERR_READ_RESET_STATUS_FILE  ((WORD32) (USP_ERR_OSS_SCP_BASE + 19)) /* 读重启状态记录文件失败 */
#define USP_OSS_SCP_ERR_WRITE_RESET_STATUS_FILE ((WORD32) (USP_ERR_OSS_SCP_BASE + 20)) /* 写重启状态记录文件失败 */
#define USP_OSS_SCP_ERR_LACK_OF_MEMORY          ((WORD32) (USP_ERR_OSS_SCP_BASE + 21)) /* 内存分配失败 */
#define USP_OSS_SCP_ERR_MSG_BUFF_SIZE_LARGE     ((WORD32) (USP_ERR_OSS_SCP_BASE + 22)) /* 缓存长度大于接收buff长度 */
#define USP_OSS_SCP_ERR_MSG_BUFF_SIZE_SMALL     ((WORD32) (USP_ERR_OSS_SCP_BASE + 23)) /* 缓存长度小于接收到消息的长度 */
#define USP_OSS_SCP_ERR_NOT_FOUND_IN_MSG_BUFF   ((WORD32) (USP_ERR_OSS_SCP_BASE + 24)) /* 在缓存中未找到指定消息 */
#define USP_OSS_SCP_ERR_MSG_BUFF_OVERFLOW       ((WORD32) (USP_ERR_OSS_SCP_BASE + 25)) /* 缓存已满 */
#define USP_OSS_SCP_ERR_MALLOC_HANDLE           ((WORD32) (USP_ERR_OSS_SCP_BASE + 26)) /* 获取动态库句柄内存失败 */
#define USP_OSS_SCP_ERR_INVALID_HANDLE          ((WORD32) (USP_ERR_OSS_SCP_BASE + 27)) /* 非法的动态库句柄 */
#define USP_OSS_SCP_ERR_ATTACH_TCB              ((WORD32) (USP_ERR_OSS_SCP_BASE + 28)) /* 连接到任务控制共享内存失败 */
#define USP_OSS_SCP_ERR_CUST_FULL               ((WORD32) (USP_ERR_OSS_SCP_BASE + 29)) /* 用户脚本个数达到了最大值 */
#define USP_OSS_SCP_ERR_SEND_MSG                ((WORD32) (USP_ERR_OSS_SCP_BASE + 30)) /* 发送消息错误 */
#define USP_OSS_SCP_ERR_RECV_MSG                ((WORD32) (USP_ERR_OSS_SCP_BASE + 31)) /* 接收消息错误 */
#define USP_OSS_SCP_ERR_RECV_MSG_TIMEOUT        ((WORD32) (USP_ERR_OSS_SCP_BASE + 32)) /* 接收消息超时 */
#define USP_OSS_SCP_ERR_IB_KEEPLIVE             ((WORD32) (USP_ERR_OSS_SCP_BASE + 33)) /* 板间SCP握手失败 */
#define USP_OSS_SCP_ERR_GET_NTP_CFG             ((WORD32) (USP_ERR_OSS_SCP_BASE + 34)) /* 获取NTP配置失败 */
#define USP_OSS_SCP_ERR_NTP_UPDATE              ((WORD32) (USP_ERR_OSS_SCP_BASE + 35)) /* NTP同步失败 */

/***********************************************************
*   数据存储模块(DSM)错误码                                *
***********************************************************/
#define USP_OSS_DSM_ERR_NULL_POINTER            ((WORD32) (USP_ERR_OSS_DSM_BASE + 1))  /* 空指针 */     
#define USP_OSS_DSM_ERR_OPEN                    ((WORD32) (USP_ERR_OSS_DSM_BASE + 2))  /* 打开存数区域失败 */ 
#define USP_OSS_DSM_ERR_READ                    ((WORD32) (USP_ERR_OSS_DSM_BASE + 3))  /* 读存数区域失败 */ 
#define USP_OSS_DSM_ERR_WRITE                   ((WORD32) (USP_ERR_OSS_DSM_BASE + 4))  /* 写存储区域失败 */ 
#define USP_OSS_DSM_ERR_ERASE                   ((WORD32) (USP_ERR_OSS_DSM_BASE + 5))  /* 擦除存储区域失败 */ 
#define USP_OSS_DSM_ERR_INVALID_DEVICE_TYPE     ((WORD32) (USP_ERR_OSS_DSM_BASE + 6))  /* 非法的存储设备类型 */ 
#define USP_OSS_DSM_ERR_INVALID_DATA_STRUCT     ((WORD32) (USP_ERR_OSS_DSM_BASE + 7))  /* 非法的存储结构类型 */ 
#define USP_OSS_DSM_ERR_INVALID_DATA_SIZE       ((WORD32) (USP_ERR_OSS_DSM_BASE + 8))  /* 非法的数据长度 */ 
#define USP_OSS_DSM_ERR_NOT_OPEN                ((WORD32) (USP_ERR_OSS_DSM_BASE + 9))  /* 存储区域还没有初始化 */ 
#define USP_OSS_DSM_ERR_NOT_ENOUTH_SPACE        ((WORD32) (USP_ERR_OSS_DSM_BASE + 10)) /* 存储区域空间不够 */ 
#define USP_OSS_DSM_ERR_STORAGE_EMPTY           ((WORD32) (USP_ERR_OSS_DSM_BASE + 11)) /* 存储区域中没有数据 */ 
#define USP_OSS_DSM_ERR_BUF_TOO_SMALL           ((WORD32) (USP_ERR_OSS_DSM_BASE + 12)) /* 缓冲区空间不够 */ 
#define USP_OSS_DSM_ERR_BLOCK_DESTROY           ((WORD32) (USP_ERR_OSS_DSM_BASE + 13)) /* 存储区域数据块损坏 */ 
#define USP_OSS_DSM_ERR_TRUNCATE                ((WORD32) (USP_ERR_OSS_DSM_BASE + 14)) /* 清空存储区域失败 */ 
#define USP_OSS_DSM_ERR_MALLOC                  ((WORD32) (USP_ERR_OSS_DSM_BASE + 15)) /* 动态获取内存失败 */ 
#define USP_OSS_DSM_ERR_INVALID_KEY             ((WORD32) (USP_ERR_OSS_DSM_BASE + 16)) /* 非法的存储区域键值 */ 
#define USP_OSS_DSM_ERR_MALLOC_HANDLE           ((WORD32) (USP_ERR_OSS_DSM_BASE + 17)) /* 获取动态库句柄内存失败 */

/***********************************************************
*   TFTP错误码                                             *
***********************************************************/
#define USP_ERR_PUB_TFTP_BEGIN                  ((WORD32) (USP_ERR_PUB_BASE + 1))
#define USP_ERR_PUB_TFTP_OPTION                 ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 1))   /* 操作选项错误 */
#define USP_ERR_PUB_TFTP_SOCKET                 ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 2))   /* Socket错误 */
#define USP_ERR_PUB_TFTP_BIND                   ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 3))   /* Bind错误 */
#define USP_ERR_PUB_TFTP_SENDTO                 ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 4))   /* 发送数据错误 */
#define USP_ERR_PUB_TFTP_RECV                   ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 5))   /* 接收数据错误 */
#define USP_ERR_PUB_TFTP_BUF_TOO_SMALL          ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 6))   /* 接收缓冲区太小 */
#define USP_ERR_PUB_TFTP_NO_LINK                ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 7))   /* 还没有建立tftp链路 */
#define USP_ERR_PUB_TFTP_TIMEOUT                ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 8))   /* 接收超时 */
#define USP_ERR_PUB_UFTP_OPTION                 ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 9))   /* 操作选项错误 */
#define USP_ERR_PUB_UFTP_CONNECT                ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 10))  /* Connect错误 */
#define USP_ERR_PUB_UFTP_SEND                   ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 11))  /* 发送数据错误 */
#define USP_ERR_PUB_UFTP_RECV                   ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 12))  /* 接收数据错误 */
#define USP_ERR_PUB_UFTP_BUF_TOO_SMALL          ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 13))  /* 接收缓冲区太小 */
#define USP_ERR_PUB_UFTP_NO_LINK                ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 14))  /* 还没有建立uftp链路 */
#define USP_ERR_PUB_UFTP_TIMEOUT                ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 15))  /* 接收超时 */
#define USP_ERR_PUB_UFTP_DATA                   ((WORD32) (USP_ERR_PUB_TFTP_BEGIN + 16))  /* 数据错误 */

/***********************************************************
*   PSP错误码                                              *
***********************************************************/
#define USP_ERR_PUB_PSP_BEGIN                   ((WORD32) (USP_ERR_PUB_BASE + 50))
#define USP_ERR_PUB_PSP_MALLOC_INFO             ((WORD32) (USP_ERR_PUB_PSP_BEGIN + 1))    /* 获取统计信息内存失败 */
#define USP_ERR_PUB_PSP_MALLOC_HANDLE           ((WORD32) (USP_ERR_PUB_PSP_BEGIN + 2))    /* 获取动态库句柄内存失败 */
#define USP_ERR_PUB_PSP_ATTACH_INFO             ((WORD32) (USP_ERR_PUB_PSP_BEGIN + 3))    /* 连接到统计信息共享内存失败 */
#define USP_ERR_PUB_PSP_INVALID_ID              ((WORD32) (USP_ERR_PUB_PSP_BEGIN + 4))    /* 非法的统计信息编号 */

/***********************************************************
*   内存管理模块(MM)错误码                                 *
***********************************************************/
#define USP_OSS_MM_ERR_STATIC_MALLOC            ((WORD32) (USP_ERR_OSS_MM_BASE + 1))  /* 不能获取内存空间 */     
#define USP_OSS_MM_ERR_NULL_POINTER             ((WORD32) (USP_ERR_OSS_MM_BASE + 2))  /* 空指针 */
#define USP_OSS_MM_ERR_ZERO_SIZE                ((WORD32) (USP_ERR_OSS_MM_BASE + 3))  /* 空间为零 */
#define USP_OSS_MM_ERR_FIFO_FULL                ((WORD32) (USP_ERR_OSS_MM_BASE + 4))  /* FIFO已满 */
#define USP_OSS_MM_ERR_FIFO_EMPTY               ((WORD32) (USP_ERR_OSS_MM_BASE + 5))  /* FIFO为空 */ 
#define USP_OSS_MM_ERR_MUTEX_INVALID            ((WORD32) (USP_ERR_OSS_MM_BASE + 6))  /* 互斥锁不可用 */ 
#define USP_OSS_MM_ERR_FIFO_ITEM_INVALID        ((WORD32) (USP_ERR_OSS_MM_BASE + 7))  /* FIFO条目不可用 */ 


/***********************************************************
*   诊断测试模块(DMP)错误码                                   *
***********************************************************/
#define USP_OAM_DMP_ERR_INVALID_PROC_STATE                ((WORD32)(USP_OAM_DMP_ERR_BASE + 1)) /* 非法的任务状态 */
#define USP_OAM_DMP_ERR_INVALID_PARA                      ((WORD32)(USP_OAM_DMP_ERR_BASE + 2)) /* 非法的参数*/
#define USP_OAM_DMP_ERR_UNKNOWN_MSG                       ((WORD32)(USP_OAM_DMP_ERR_BASE + 3)) /* 未知的消息 */
#define USP_OAM_DMP_ERR_NULL_POINTER                      ((WORD32)(USP_OAM_DMP_ERR_BASE + 4)) /* 空指针 */
#define USP_OAM_DMP_ERR_OVERFLOW_TESTNUM                  ((WORD32)(USP_OAM_DMP_ERR_BASE + 5)) /* 超出最大诊断测试项个数 */
#define USP_OAM_DMP_ERR_INVALID_TESTID                    ((WORD32)(USP_OAM_DMP_ERR_BASE + 6)) /* 非法的诊断测试项ID  */
#define USP_OAM_DMP_ERR_SENDMSG_FAIL                      ((WORD32)(USP_OAM_DMP_ERR_BASE + 8)) /* 发送消息失败 */
#define USP_OAM_DMP_ERR_RCVMSG_FAIL                       ((WORD32)(USP_OAM_DMP_ERR_BASE + 9)) /* 接收消息失败 */
#define USP_OAM_DMP_ERR_INVALID_MSGID                     ((WORD32)(USP_OAM_DMP_ERR_BASE + 10)) /* 非法的消息ID  */
#define USP_OAM_DMP_ERR_ACK_ERR                           ((WORD32)(USP_OAM_DMP_ERR_BASE + 11)) /* 错误的应答结果 */
#define USP_OAM_DMP_ERR_INVALID_TNO                       ((WORD32)(USP_OAM_DMP_ERR_BASE + 12)) /* 错误的任务号 */
#define USP_OAM_DMP_ERR_DATA_OVERFLOW                     ((WORD32)(USP_OAM_DMP_ERR_BASE + 13)) /* 数据溢出 */
#define USP_OAM_DMP_ERR_IN_MSG_ADAPTER_ERR                ((WORD32)(USP_OAM_DMP_ERR_BASE + 14)) /* 输入消息适配函数转换失败 */
#define USP_OAM_DMP_ERR_OUT_MSG_ADAPTER_ERR               ((WORD32)(USP_OAM_DMP_ERR_BASE + 15)) /* 输出消息适配函数转换失败 */
#define USP_OAM_DMP_ERR_INCLICMDPARAERROR                 ((WORD32)(USP_OAM_DMP_ERR_BASE + 16)) /* 命令行输入参数转换失败 */
#define USP_OAM_DMP_ERR_OUTCLICMDPARAERROR                ((WORD32)(USP_OAM_DMP_ERR_BASE + 17)) /* 命令行输出参数转换失败 */
#define USP_OAM_DMP_ERR_WAITAPPRESPONSEOVERTIME           ((WORD32)(USP_OAM_DMP_ERR_BASE + 18)) /* 等待业务应用模块超时 */
#define USP_OAM_DMP_ERR_RECVUNEXPECTEDMSG                 ((WORD32)(USP_OAM_DMP_ERR_BASE + 19)) /* 接收到了不期待的消息 */
#define USP_OAM_DMP_ERR_READEEPROMERROR                   ((WORD32)(USP_OAM_DMP_ERR_BASE + 20)) /* 读EEPROM出错 */
#define USP_OAM_DMP_ERR_EEPROMRWTESTERROR                 ((WORD32)(USP_OAM_DMP_ERR_BASE + 21)) /* EEPROM读写测试出错 */
#define USP_OAM_DMP_ERR_WRITEEEPROMERROR                  ((WORD32)(USP_OAM_DMP_ERR_BASE + 22)) /* 写EEPROM出错 */
#define USP_OAM_DMP_ERR_GPIOSETINPUTERROR                 ((WORD32)(USP_OAM_DMP_ERR_BASE + 23)) /* GPIO设置出错 */
#define USP_OAM_DMP_ERR_INVALIDADDRERROR                  ((WORD32)(USP_OAM_DMP_ERR_BASE + 24)) /* 非法的地址 */
#define USP_OAM_DMP_ERR_PARAMETERERROR                    ((WORD32)(USP_OAM_DMP_ERR_BASE + 25)) /* 参数错误 */
#define USP_OAM_DMP_ERR_NOTUSPTESTID                      ((WORD32)(USP_OAM_DMP_ERR_BASE + 26)) /* 非平台测试项 */
#define USP_OAM_DMP_ERR_NON_DIGATAL                       ((WORD32) (USP_OAM_DMP_ERR_BASE + 27)) /* 非数字 */   
#define USP_OAM_DMP_ERR_MALLOC_HANDLE                     ((WORD32) (USP_OAM_DMP_ERR_BASE + 28)) /* 获取动态库句柄内存失败 */ 
#define USP_OAM_DMP_ERR_NON_DEVMODLE                      ((WORD32) (USP_OAM_DMP_ERR_BASE + 29)) /* 没有与之匹配的机型 */
#define USP_OAM_DMP_ERR_CLINOTSUPPORT                     ((WORD32) (USP_OAM_DMP_ERR_BASE + 28)) /* 命令行不支持该诊断测试项 */ 
/***********************************************************
*                  告警管理模块(AMP)错误码                          *
***********************************************************/
/*AMP模块返回给后台的错误码*/
#define USP_OAM_AMP_ERR_NULL_POINTER                    (USP_OAM_AMP_ERR_BASE + 0)/*参数指针为空*/
#define USP_OAM_AMP_ERR_IN_MSG_ADAPTER_ERR              (USP_OAM_AMP_ERR_BASE + 1)/*归一化输入适配出错*/
#define USP_OAM_AMP_ERR_OUT_MSG_ADAPTER_ERR             (USP_OAM_AMP_ERR_BASE + 2)/*归一化输出适配出错*/
#define USP_OAM_AMP_ERR_UNKNOWN_MSG                     (USP_OAM_AMP_ERR_BASE + 3)/*接收到未知消息*/
#define USP_OAM_AMP_ERR_DEAL_DELETE_MSG                 (USP_OAM_AMP_ERR_BASE + 4)/*处理删除告警出错*/
#define USP_OAM_AMP_ERR_DEAL_SYNC_MSG                   (USP_OAM_AMP_ERR_BASE + 5)/*处理同步告警出错*/
#define USP_OAM_AMP_ERR_SEND_MSG                        (USP_OAM_AMP_ERR_BASE + 6)/*发送消息出错*/
#define USP_OAM_AMP_ERR_RECV_MSG                        (USP_OAM_AMP_ERR_BASE + 7)/*接收消息出错*/
#define USP_OAM_AMP_ERR_AID_NUM                         (USP_OAM_AMP_ERR_BASE + 7)/*错误的aid值*/
#define USP_OAM_AMP_ERR_SAVE_PACKAGE                    (USP_OAM_AMP_ERR_BASE + 8)/*保存同步数据包出错*/
#define USP_OAM_AMP_ERR_SAVE_ALL_PACKAGE                (USP_OAM_AMP_ERR_BASE + 9)/*接收不完整的同步数据包*/
#define USP_OAM_AMP_ERR_DEAL_BCK_MSG                    (USP_OAM_AMP_ERR_BASE + 10)/*处理后台消息出错*/
#define USP_OAM_AMP_ERR_DEAL_SCRALARM_MSG               (USP_OAM_AMP_ERR_BASE + 11)/*处理告警源消息出错*/
#define USP_OAM_AMP_ERR_MALLOC_SPACE                    (USP_OAM_AMP_ERR_BASE + 12)/*申请空间失败*/
#define USP_OAM_AMP_ERR_REALLOCATE_AID                  (USP_OAM_AMP_ERR_BASE + 13)/*重新分配AID失败*/
#define USP_OAM_AMP_ERR_DEAL_FULL_PROC                  (USP_OAM_AMP_ERR_BASE + 14)/*处理告警池满出错*/
#define USP_OAM_AMP_ERR_RECV_SRC_MSG                    (USP_OAM_AMP_ERR_BASE + 15)/*前台接收到错误的告警源消息*/
#define USP_OAM_AMP_ERR_POOL_OVERFLOW                   (USP_OAM_AMP_ERR_BASE + 16)/*告警池溢出*/
#define USP_OAM_AMP_ERR_POOL_PUT                        (USP_OAM_AMP_ERR_BASE + 17)/*告警池插入出错*/
#define USP_OAM_AMP_ERR_POOL_MISS_FULL_ALARM            (USP_OAM_AMP_ERR_BASE + 18)/*丢失告警池满告警*/
#define USP_OAM_AMP_ERR_REPEAT_RESTORE                  (USP_OAM_AMP_ERR_BASE + 19)/*重复上报告警恢复*/
#define USP_OAM_AMP_ERR_RECV_BCK_INVALID_MSG            (USP_OAM_AMP_ERR_BASE + 20)/*接收到后台无效消息*/
#define USP_OAM_AMP_ERR_ALARM_POOL_EMPTY                (USP_OAM_AMP_ERR_BASE + 21)/*前台告警池空*/
#define USP_OAM_AMP_ERR_MSG_LEN_OVERFLOW                (USP_OAM_AMP_ERR_BASE + 22)/*告警信息长度溢出*/
#define USP_OAM_AMP_ERR_INVALID_PARAM                   (USP_OAM_AMP_ERR_BASE + 23)/*无效参数*/


/***********************************************************                   
*                   U-Boot 错误码                                  *
***********************************************************/
#define USP_ERR_UBOOT_FPGA_LOAD_TIMEOUT           ((WORD32) (USP_ERR_UBOOT_BASE + 1))
#define USP_ERR_UBOOT_RAM_TEST_PARAM                 ((WORD32) (USP_ERR_UBOOT_BASE + 2))
#define USP_ERR_UBOOT_ILLEGAL_PARAM                    ((WORD32) (USP_ERR_UBOOT_BASE + 3))
#define USP_ERR_UBOOT_FLASH_TEST_PARAM              ((WORD32) (USP_ERR_UBOOT_BASE + 4))
#define USP_ERR_UBOOT_FLASH_TEST_OUT_OF_BANK  ((WORD32) (USP_ERR_UBOOT_BASE + 5))
#define USP_ERR_UBOOT_FLASH_TEST                            ((WORD32) (USP_ERR_UBOOT_BASE + 6))
#define USP_ERR_UBOOT_EEPROM_READ                        ((WORD32) (USP_ERR_UBOOT_BASE + 7))
#define USP_ERR_UBOOT_EEPROM_WRITE                      ((WORD32) (USP_ERR_UBOOT_BASE + 8))
#define USP_ERR_UBOOT_FTRUN_LEN                             ((WORD32) (USP_ERR_UBOOT_BASE + 9))
#define USP_ERR_UBOOT_FTRUN_TYPE                           ((WORD32) (USP_ERR_UBOOT_BASE + 10))
#define USP_ERR_UBOOT_RAM_TEST                               ((WORD32) (USP_ERR_UBOOT_BASE + 11))
#define USP_ERR_UBOOT_PL_INIT_EEPROM                    ((WORD32) (USP_ERR_UBOOT_BASE + 12))
#define USP_ERR_UBOOT_IP_CONFIG_PARAM                 ((WORD32) (USP_ERR_UBOOT_BASE + 13))
#define USP_ERR_UBOOT_FPGA_LD_TIMEOUT                 ((WORD32) (USP_ERR_UBOOT_BASE + 14))


/***********************************************************                   
*                   驱动平台(Drv) 错误码                                  *
***********************************************************/

/***********************************************************
*                   驱动平台Epld模块错误码                            *
***********************************************************/
#define USP_ERROR_DRV_EPLD_READY                        (USP_ERR_DRV_EPLD_START+0)
#define USP_ERROR_DRV_EPLD_OPEN                         (USP_ERR_DRV_EPLD_START+1)
#define USP_ERROR_DRV_EPLD_MMAP                         (USP_ERR_DRV_EPLD_START+2)
#define USP_ERROR_DRV_EPLD_RWWIDTH                      (USP_ERR_DRV_EPLD_START+3)
#define USP_ERROR_DRV_EPLD_NULL_POINTER                 (USP_ERR_DRV_EPLD_START+4)

/***********************************************************
*                   驱动平台Fpga模块错误码                            *
***********************************************************/
#define USP_ERROR_DRV_FPGA_INIT_FD                     (USP_ERR_DRV_FPGA_START+0)
#define USP_ERROR_DRV_FPGA_INIT_OPEN                   (USP_ERR_DRV_FPGA_START+1)
#define USP_ERROR_DRV_FPGA_INIT_MMAP_EPLD              (USP_ERR_DRV_FPGA_START+2)
#define USP_ERROR_DRV_FPGA_INIT_MMAP_FPGA              (USP_ERR_DRV_FPGA_START+3)
#define USP_ERROR_DRV_FPGA_READ_REG_DATA               (USP_ERR_DRV_FPGA_START+4)
#define USP_ERROR_DRV_FPGA_READ_REG_OFFSET             (USP_ERR_DRV_FPGA_START+5)
#define USP_ERROR_DRV_FPGA_WRITE_REG_OFFSET            (USP_ERR_DRV_FPGA_START+6)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_PARA            (USP_ERR_DRV_FPGA_START+7)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_LEN             (USP_ERR_DRV_FPGA_START+8)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_FLAG            (USP_ERR_DRV_FPGA_START+9)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_FD              (USP_ERR_DRV_FPGA_START+10)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_IOCTL           (USP_ERR_DRV_FPGA_START+11)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_WRITE           (USP_ERR_DRV_FPGA_START+12)
#define USP_ERROR_DRV_FPGA_READ_FRAME_PARA             (USP_ERR_DRV_FPGA_START+13)
#define USP_ERROR_DRV_FPGA_READ_FRAME_FD               (USP_ERR_DRV_FPGA_START+14)
#define USP_ERROR_DRV_FPGA_WRITE_FRAME_READ            (USP_ERR_DRV_FPGA_START+15)
#define USP_ERROR_DRV_FPGA_INT_EN_FD                   (USP_ERR_DRV_FPGA_START+16)
#define USP_ERROR_DRV_FPGA_INT_EN_IOCTL                (USP_ERR_DRV_FPGA_START+17)
#define USP_ERROR_DRV_FPGA_INT_DISEN_FD                (USP_ERR_DRV_FPGA_START+18)
#define USP_ERROR_DRV_FPGA_INT_DISEN_IOCTL             (USP_ERR_DRV_FPGA_START+19)
#define USP_ERROR_DRV_FPGA_INIT_IOCTL_TOG              (USP_ERR_DRV_FPGA_START+20)
#define USP_ERROR_DRV_FPGA_INIT_IOCTL_RESET            (USP_ERR_DRV_FPGA_START+21)
#define USP_ERROR_DRV_FPGA_1101_SEND_BROADCAST_TIMEOUT (USP_ERR_DRV_FPGA_START+22)
#define USP_ERROR_DRV_FPGA_1101_SEND_OBUID_TIMEOUT     (USP_ERR_DRV_FPGA_START+23)


/***********************************************************
*                   驱动平台Wtd模块错误码                   *
***********************************************************/
#define USP_ERROR_DRV_WTD_PARAM                               (USP_ERR_DRV_WTD_START+0)

/***********************************************************
*                   驱动平台LED模块错误码                   *
***********************************************************/
#define USP_ERROR_DRV_LED_NUMBER                              (USP_ERR_DRV_LED_START+0)
#define USP_ERROR_DRV_LED_STATE                                 (USP_ERR_DRV_LED_START+1)

/***********************************************************
*                   驱动平台Psam模块错误码                            *
***********************************************************/
#define USP_ERR_DRV_PSAM_INIT_OPEN                          (USP_ERR_DRV_PSAM_START+0)
#define USP_ERR_DRV_PSAM_INIT_DONE                          (USP_ERR_DRV_PSAM_START+1)
#define USP_ERR_DRV_PSAM_ACTIVE_ID                          (USP_ERR_DRV_PSAM_START+2)
#define USP_ERR_DRV_PSAM_ACTIVE_PARA                        (USP_ERR_DRV_PSAM_START+3)
#define USP_ERR_DRV_PSAM_ACTIVE_FD                          (USP_ERR_DRV_PSAM_START+4)
#define USP_ERR_DRV_PSAM_ACTIVE_IOCTL                       (USP_ERR_DRV_PSAM_START+5)
#define USP_ERR_DRV_PSAM_CMD_ID                             (USP_ERR_DRV_PSAM_START+6)
#define USP_ERR_DRV_PSAM_CMD_FD                             (USP_ERR_DRV_PSAM_START+7)
#define USP_ERR_DRV_PSAM_CMD_PARA                           (USP_ERR_DRV_PSAM_START+8)
#define USP_ERR_DRV_PSAM_CMD_LEN                            (USP_ERR_DRV_PSAM_START+9)
#define USP_ERR_DRV_PSAM_CMD_IOCTL                          (USP_ERR_DRV_PSAM_START+10)
#define USP_ERR_DRV_PSAM_DEACTIVE_ID                        (USP_ERR_DRV_PSAM_START+11)
#define USP_ERR_DRV_PSAM_DEACTIVE_PARA                      (USP_ERR_DRV_PSAM_START+12)
#define USP_ERR_DRV_PSAM_DEACTIVE_FD                        (USP_ERR_DRV_PSAM_START+13)
#define USP_ERR_DRV_PSAM_DEACTIVE_IOCTL                     (USP_ERR_DRV_PSAM_START+14)
#define USP_ERR_DRV_PSAM_CLKFREQ_FD                         (USP_ERR_DRV_PSAM_START+15)
#define USP_ERR_DRV_PSAM_CLKFREQ_DATA                       (USP_ERR_DRV_PSAM_START+16)
#define USP_ERR_DRV_PSAM_CLKSET_IOCTL                       (USP_ERR_DRV_PSAM_START+17)
#define USP_ERR_DRV_PSAM_VOLTAGE_FD                         (USP_ERR_DRV_PSAM_START+18)
#define USP_ERR_DRV_PSAM_VOLTAGE_DATA                       (USP_ERR_DRV_PSAM_START+19)
#define USP_ERR_DRV_PSAM_VOLTAGE_IOCTL                      (USP_ERR_DRV_PSAM_START+20)
#define USP_ERR_DRV_PSAM_MALLOC_HANDLE                      (USP_ERR_DRV_PSAM_START+21)
#define USP_ERR_DRV_PSAM_CLKFREQ_ID                         (USP_ERR_DRV_PSAM_START+22)
#define USP_ERR_DRV_PSAM_VOLTAGE_ID                         (USP_ERR_DRV_PSAM_START+23)
#define USP_ERR_DRV_PSAM_CLKFREQ_MMAP                       (USP_ERR_DRV_PSAM_START+24)
#define USP_ERR_DRV_PSAM_DETECT_PARA                        (USP_ERR_DRV_PSAM_START+25)

/***********************************************************
*                   驱动平台gpio 模块错误码                            *
***********************************************************/
#define USP_ERROR_DRV_GPIO_READY                               (USP_ERR_DRV_GPIO_START+0)
#define USP_ERROR_DRV_GPIO_OPEN                                 (USP_ERR_DRV_GPIO_START+1)
#define USP_ERROR_DRV_GPIO_MMAP                                (USP_ERR_DRV_GPIO_START+2)
#define USP_ERROR_DRV_GPIO_RWWIDTH                         (USP_ERR_DRV_GPIO_START+3)
#define USP_ERROR_DRV_GPIO_PARAM                               (USP_ERR_DRV_GPIO_START+4)
#define USP_ERROR_DRV_GPIO_READ                                  (USP_ERR_DRV_GPIO_START+5)
#define USP_ERROR_DRV_GPIO_WRITE                                (USP_ERR_DRV_GPIO_START+6)

/***********************************************************
*                   驱动平台Rtc模块错误码                            *
***********************************************************/
#define USP_ERR_DRV_RTC_BUSINI                                             (USP_ERR_DRV_RTC_START+0)//初始化i2c总线失败
#define USP_ERR_DRV_RTC_WRITEADDR                                     (USP_ERR_DRV_RTC_START+1)
#define USP_ERR_DRV_RTC_READCH                                           (USP_ERR_DRV_RTC_START+2)
#define USP_ERR_DRV_RTC_WRITECH                                         (USP_ERR_DRV_RTC_START+3)
#define USP_ERR_DRV_RTC_READOSF                                         (USP_ERR_DRV_RTC_START+4)
#define USP_ERR_DRV_RTC_WRITEOSF                                       (USP_ERR_DRV_RTC_START+5)
#define USP_ERR_DRV_RTC_READSQW                                        (USP_ERR_DRV_RTC_START+6)
#define USP_ERR_DRV_RTC_WRITESQW                                      (USP_ERR_DRV_RTC_START+7)
#define USP_ERR_DRV_RTC_READOUT                                         (USP_ERR_DRV_RTC_START+8)
#define USP_ERR_DRV_RTC_WRITEOUT                                       (USP_ERR_DRV_RTC_START+9)
#define USP_ERR_DRV_RTC_READTIME                                       (USP_ERR_DRV_RTC_START+10)
#define USP_ERR_DRV_RTC_WRITETIME                                     (USP_ERR_DRV_RTC_START+11)	
#define USP_ERR_DRV_RTC_READHOURFORMAT                         (USP_ERR_DRV_RTC_START+12)
#define USP_ERR_DRV_RTC_WRITEHOURFORMAT                       (USP_ERR_DRV_RTC_START+13)
#define USP_ERR_DRV_RTC_CH_EXCEP                                       (USP_ERR_DRV_RTC_START+14)
#define USP_ERR_DRV_RTC_OSF_STOP                                       (USP_ERR_DRV_RTC_START+15)
#define USP_ERR_DRV_RTC_TIME_INVALID                                (USP_ERR_DRV_RTC_START+16)
#define USP_ERR_DRV_RTC_READ_PARAM                                (USP_ERR_DRV_RTC_START+17)


/***********************************************************
*                   驱动平台I2c模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_I2C_PIN                                (USP_ERR_DRV_I2C_START+1)
#define USP_ERR_DRV_I2C_FREE                               (USP_ERR_DRV_I2C_START+2)
#define USP_ERR_DRV_I2C_ACK                                (USP_ERR_DRV_I2C_START+3)
#define USP_ERR_DRV_I2C_SNDBUF                             (USP_ERR_DRV_I2C_START+4)
#define USP_ERR_DRV_I2C_RESET                              (USP_ERR_DRV_I2C_START+5)
#define USP_ERR_DRV_I2C_SEMCREATE			               (USP_ERR_DRV_I2C_START+6)
#define USP_ERR_DRV_I2C_SEM_INIT			               (USP_ERR_DRV_I2C_START+7)
#define USP_ERR_DRV_I2C_SEM_P			                   (USP_ERR_DRV_I2C_START+8)
#define USP_ERR_DRV_I2C_SEM_V			                   (USP_ERR_DRV_I2C_START+9)



/***********************************************************
*                   驱动平台Ioport模块错误码                            *
***********************************************************/
#define USP_ERROR_DRV_IOPORT_READY                               (USP_ERR_DRV_IOPORT_START+0)
#define USP_ERROR_DRV_IOPORT_OPEN                                 (USP_ERR_DRV_IOPORT_START+1)
#define USP_ERROR_DRV_IOPORT_MMAP                                (USP_ERR_DRV_IOPORT_START+2)
#define USP_ERROR_DRV_IOPORT_RWWIDTH                         (USP_ERR_DRV_IOPORT_START+3)

/***********************************************************
*                   驱动平台Lcd模块错误码                            *
***********************************************************/
#define USP_ERROR_DRV_LCD_PLDBASEADDR                            (USP_ERR_DRV_LCD_START+0)
#define USP_ERROR_DRV_LCD_PARAM                                        (USP_ERR_DRV_LCD_START+1)
#define USP_ERROR_DRV_LCD_IORWWIDTH                               (USP_ERR_DRV_LCD_START+2)

/***********************************************************
*                   驱动平台Modem模块错误码                       *
***********************************************************/
#define USP_ERR_DRV_MODEM_INIT_MODEM                            (USP_ERR_DRV_MODEM_START+0)
#define USP_ERR_DRV_MODEM_INIT_UART                               (USP_ERR_DRV_MODEM_START+1)
#define USP_ERR_DRV_MODEM_DIAL                                         (USP_ERR_DRV_MODEM_START+2)
#define USP_ERR_DRV_MODEM_DIALOFF                                   (USP_ERR_DRV_MODEM_START+3)
#define USP_ERR_DRV_MODEM_CLRRECVBUF                             (USP_ERR_DRV_MODEM_START+4)/*  清除接收缓冲区失败*/
#define USP_ERR_DRV_MODEM_CLRSNDBUF                               (USP_ERR_DRV_MODEM_START+5)/*  清除发送缓冲区失败*/
#define USP_ERR_DRV_MODEM_READ                                         (USP_ERR_DRV_MODEM_START+6)/*  读失败*/
#define USP_ERR_DRV_MODEM_WRITE                                       (USP_ERR_DRV_MODEM_START+7)/*  写失败*/
#define USP_ERR_DRV_MODEM_RELEASE                                   (USP_ERR_DRV_MODEM_START+8)/*  清除接收缓冲区失败*/
#define USP_ERR_DRV_MODEM_PARAM                                      (USP_ERR_DRV_MODEM_START+9)/*  清除接收缓冲区失败*/
#define USP_ERR_DRV_MODEM_READY                                       (USP_ERR_DRV_MODEM_START+10)


/***********************************************************
*                   驱动平台Keyboard模块错误码                   *
***********************************************************/
#define USP_ERROR_DRV_KEYBOARD_OPEN                             (USP_ERR_DRV_KEYBOARD_START+0)
#define USP_ERROR_DRV_KEYBOARD_CLOSE                           (USP_ERR_DRV_KEYBOARD_START+1)
#define USP_ERROR_DRV_KEYBOARD_READ                             (USP_ERR_DRV_KEYBOARD_START+2)
#define USP_ERROR_DRV_KEYBOARD_READY                           (USP_ERR_DRV_KEYBOARD_START+3)

/***********************************************************
*                   驱动平台EEPROM模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_EEPROM_INIT_FIRST          (USP_ERR_DRV_EEPROM_START+1)
#define USP_ERR_DRV_EEPROM_INIT_SECOND         (USP_ERR_DRV_EEPROM_START+2)
#define USP_ERR_DRV_EEPROM_INIT_ALL            (USP_ERR_DRV_EEPROM_START+3)
#define USP_ERR_DRV_EEPROM_SND_PARAM           (USP_ERR_DRV_EEPROM_START+4)
#define USP_ERR_DRV_EEPROM_RCV_PARAM           (USP_ERR_DRV_EEPROM_START+5)
#define USP_ERR_DRV_EEPROM_OFFSET              (USP_ERR_DRV_EEPROM_START+6)
#define USP_ERR_DRV_EEPROM_RCV_DATA            (USP_ERR_DRV_EEPROM_START+7)
#define USP_ERR_DRV_EEPROM_RCV_PARAM_SECOND    (USP_ERR_DRV_EEPROM_START+8)
#define USP_ERR_DRV_EEPROM_SND_PARAM_SECOND    (USP_ERR_DRV_EEPROM_START+9)
#define USP_ERR_DRV_EEPROM_SND_DATA            (USP_ERR_DRV_EEPROM_START+10)
#define USP_ERR_DRV_EEPROM_SND_WRITE_PAGE            (USP_ERR_DRV_EEPROM_START+11)


/***********************************************************
*                   驱动平台FLASH模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_FLASH_OFFSET                                         (USP_ERR_DRV_FLASH_START+1)
#define USP_ERR_DRV_FLASH_MTDINDEX                                    (USP_ERR_DRV_FLASH_START+2)
#define USP_ERR_DRV_FLASH_MTDOPEN                                      (USP_ERR_DRV_FLASH_START+3)
#define USP_ERR_DRV_FLASH_READ                                            (USP_ERR_DRV_FLASH_START+4)
#define USP_ERR_DRV_FLASH_WRITE                                          (USP_ERR_DRV_FLASH_START+5)
#define USP_ERR_DRV_FLASH_ERASEMALLOC                              (USP_ERR_DRV_FLASH_START+6)
#define USP_ERR_DRV_FLASH_ERASE                                          (USP_ERR_DRV_FLASH_START+7)
#define USP_ERR_DRV_FLASH_NULL_POINTER                                   (USP_ERR_DRV_FLASH_START+8)
#define USP_ERR_DRV_FLASH_OPEN_FILE                                      (USP_ERR_DRV_FLASH_START+9)
#define USP_ERR_DRV_FLASH_READ_FILE                                      (USP_ERR_DRV_FLASH_START+10)
#define USP_ERR_DRV_FLASH_TYPE                                     (USP_ERR_DRV_FLASH_START+11)

/***********************************************************
*                   驱动平台PRINTERCTL模块错误码                   *
***********************************************************/

#define USP_ERR_DRV_PRINTER_NOTCOMPLETED                       (USP_ERR_DRV_PRINTER_START+1)
#define USP_ERR_DRV_PRINTER_LACKPAPER                               (USP_ERR_DRV_PRINTER_START+2)
#define USP_ERR_DRV_PRINTER_OVERHEAT                                 (USP_ERR_DRV_PRINTER_START+3)
#define USP_ERR_DRV_PRINTER_WRONGCMD                               (USP_ERR_DRV_PRINTER_START+4)
#define USP_ERR_DRV_PRINTER_CMD_SND                                   (USP_ERR_DRV_PRINTER_START+5)
#define USP_ERR_DRV_PRINTER_CMD_PARA                                 (USP_ERR_DRV_PRINTER_START+6)
#define USP_ERR_DRV_PRINTERCTL_BUF_NULL                             (USP_ERR_DRV_PRINTER_START+7)
#define USP_ERR_DRV_PRINTERCTL_BUF_LEN                               (USP_ERR_DRV_PRINTER_START+8)

/***********************************************************
*                   驱动平台串口模块错误码                   *
***********************************************************/

/* 串口编号大于串口总数 */
#define  USP_ERR_DRV_UART_NUM                                                 (USP_ERR_DRV_UART_START+1)
/* 打开已经打开的串口 */
#define  USP_ERR_DRV_UART_EXIST                                                 (USP_ERR_DRV_UART_START+2)
/* 未知原因打开失败 */
#define USP_ERR_DRV_UART_OPEN                                                 (USP_ERR_DRV_UART_START+3)
/* 不支持的波特率 */
#define USP_ERR_DRV_UART_BAUDRATE                                                 (USP_ERR_DRV_UART_START+4)
/* 不支持的数据位 */
#define USP_ERR_DRV_UART_DATABIT                                                 (USP_ERR_DRV_UART_START+5)
/* 不支持的奇偶检验 */
#define USP_ERR_DRV_UART_PARITY                                                 (USP_ERR_DRV_UART_START+6)
/* 不支持的停止位 */
#define USP_ERR_DRV_UART_STOPBIT                                                 (USP_ERR_DRV_UART_START+7)

/* 串口索引不正确 */
#define USP_ERR_DRV_UART_INDEX                                                 (USP_ERR_DRV_UART_START+8)

/* 刷新串口缓冲区错误 */
#define USP_ERR_DRV_UART_FLUSH                                                 (USP_ERR_DRV_UART_START+9)

/* 定义的串口中断号错误 */
#define USP_DRV_UART_IRQNUMBER_ERR                                                 (USP_ERR_DRV_UART_START+0x0A)

/* 关闭串口错误 */
#define USP_DRV_UART_CLOSE_ERR                                                 (USP_ERR_DRV_UART_START+0x0B)
/* 接收串口数据错误 */
#define USP_DRV_UART_READ_ERR                                                 (USP_ERR_DRV_UART_START+0x0C)
/* 设置串口属性错误  */
#define USP_DRV_UART_SETATTR_ERR                                                  (USP_ERR_DRV_UART_START+0x0D)
/* 串口发送数据错误 */
#define USP_DRV_UART_WRITE_ERR                                                 (USP_ERR_DRV_UART_START+0x0E)

/***********************************************************
*                   驱动平台磁条读卡器模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_MCR_OPEN                                                   (USP_ERR_DRV_MCR_START+0x01)
#define USP_ERR_DRV_MCR_PARA                                                   (USP_ERR_DRV_MCR_START+0x02)
#define USP_ERR_DRV_MCR_READ                                                   (USP_ERR_DRV_MCR_START+0x03)
#define USP_ERR_DRV_MCR_DATA_INVALID                                   (USP_ERR_DRV_MCR_START+0x04)
#define USP_ERR_DRV_MCR_PARITY                                               (USP_ERR_DRV_MCR_START+0x05)
#define USP_ERR_DRV_MCR_CLOSE                                                 (USP_ERR_DRV_MCR_START+0x06)

/***********************************************************
*                   驱动平台485控制模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_CTRL485_PARAM                                                (USP_ERR_DRV_CTRL485_START+0x01)


/***********************************************************
*                   驱动平台密码键盘模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_CODEKBD_CMD_SND                                (USP_ERR_DRV_CODEKBD_START+0x01)
#define USP_ERR_DRV_CODEKBD_RES_RCV        				 (USP_ERR_DRV_CODEKBD_START+0x02)
#define USP_ERR_DRV_CODEKBD_CMD_PARA     				 (USP_ERR_DRV_CODEKBD_START+0x03)
#define USP_ERR_DRV_CODEKBD_TIMEOUT                                 (USP_ERR_DRV_CODEKBD_START+0x04)
#define USP_ERR_DRV_CODEKBD_TMKINVALID                           (USP_ERR_DRV_CODEKBD_START+0x05)
#define USP_ERR_DRV_CODEKBD_WPINVALID                             (USP_ERR_DRV_CODEKBD_START+0x06)
#define USP_ERR_DRV_CODEKBD_CMDTMKINVALID                    (USP_ERR_DRV_CODEKBD_START+0x07)
#define USP_ERR_DRV_CODEKBD_BATTERY                                 (USP_ERR_DRV_CODEKBD_START+0x08)
#define USP_ERR_DRV_CODEKBD_CMDBATTERY                          (USP_ERR_DRV_CODEKBD_START+0x09)
#define USP_ERR_DRV_CODEKBD_CMDINVALID                           (USP_ERR_DRV_CODEKBD_START+0x0A)
#define USP_ERR_DRV_CODEKBD_UNKNOWN                               (USP_ERR_DRV_CODEKBD_START+0x0B)
#define USP_ERR_DRV_CODEKBD_PWD_RCV                                (USP_ERR_DRV_CODEKBD_START+0x0C)
#define USP_ERR_DRV_CODEKBD_PWD_CANEL                            (USP_ERR_DRV_CODEKBD_START+0x0D)
#define USP_ERR_DRV_CODEKBD_ACTIVEWPCMD_SND               (USP_ERR_DRV_CODEKBD_START+0x0E)
#define USP_ERR_DRV_CODEKBD_ACTIVEWPRES_RCV                (USP_ERR_DRV_CODEKBD_START+0x0F)
#define USP_ERR_DRV_CODEKBD_SETALGPARACMD_SND            (USP_ERR_DRV_CODEKBD_START+0x10)
#define USP_ERR_DRV_CODEKBD_SETALGPARARES_RCV             (USP_ERR_DRV_CODEKBD_START+0x11)
#define USP_ERR_DRV_CODEKBD_SWITCHBZCMD_SND                (USP_ERR_DRV_CODEKBD_START+0x12)
#define USP_ERR_DRV_CODEKBD_SWITCHBZRES_RCV                 (USP_ERR_DRV_CODEKBD_START+0x13)
#define USP_ERR_DRV_CODEKBD_ENCRYPTCMD_SND                   (USP_ERR_DRV_CODEKBD_START+0x14)
#define USP_ERR_DRV_CODEKBD_ENCRYPTRES_RCV                   (USP_ERR_DRV_CODEKBD_START+0x15)
#define USP_ERR_DRV_CODEKBD_GETPINCMD_SND                     (USP_ERR_DRV_CODEKBD_START+0x16)
#define USP_ERR_DRV_CODEKBD_GETPINRES_RCV                      (USP_ERR_DRV_CODEKBD_START+0x17)
#define USP_ERR_DRV_CODEKBD_DECRYPTCMD_SND                   (USP_ERR_DRV_CODEKBD_START+0x18)
#define USP_ERR_DRV_CODEKBD_DECRYPTRES_RCV                   (USP_ERR_DRV_CODEKBD_START+0x19)
#define USP_ERR_DRV_CODEKBD_EXIT                                         (USP_ERR_DRV_CODEKBD_START+0x1A)
#define USP_ERR_DRV_CODEKBD_UART_TIMEOUT                       (USP_ERR_DRV_CODEKBD_START+0x1B)

/***********************************************************
*                   驱动平台SYSDATA模块错误码             *
***********************************************************/
#define USP_ERROR_OSS_SYSDATA_PARAERR                          (USP_ERR_OSS_SYSDATA_START+0)
#define USP_ERROR_OSS_SYSDATA_FLASH_READ                       (USP_ERR_OSS_SYSDATA_START+1)
#define USP_ERROR_OSS_SYSDATA_FLASH_WRITE                      (USP_ERR_OSS_SYSDATA_START+2)
#define USP_ERROR_OSS_SYSDATA_FLASH_ERASE                      (USP_ERR_OSS_SYSDATA_START+3)
#define USP_ERROR_OSS_SYSDATA_FAILED                           (USP_ERR_OSS_SYSDATA_START+4)
#define USP_ERROR_OSS_SYSDATA_FULL                             (USP_ERR_OSS_SYSDATA_START+5)
#define USP_ERROR_OSS_SYSDATA_INIT_MUTEX                       (USP_ERR_OSS_SYSDATA_START+6)

/***********************************************************
*   版本管理(VMP)错误码                                    *
***********************************************************/
#define USP_ERR_OAM_VMP_LOAD_APP_INFO            ((WORD32) (USP_ERR_OAM_VMP_BASE + 1))  /* 读取应用程序信息错误 */
#define USP_ERR_OAM_VMP_APP_VER_INCORRENT        ((WORD32) (USP_ERR_OAM_VMP_BASE + 2))  /* 应用程序版本不正确 */
#define USP_ERR_OAM_VMP_APP_RUN_INFO             ((WORD32) (USP_ERR_OAM_VMP_BASE + 3))  /* 没有可以运行的应用程序版本 */
#define USP_ERR_OAM_VMP_RECV_MSG                 ((WORD32) (USP_ERR_OAM_VMP_BASE + 4))  /* 接收消息错误 */
#define USP_ERR_OAM_VMP_POWERON_ROUND            ((WORD32) (USP_ERR_OAM_VMP_BASE + 5))  /* 上电消息的轮次号不正确 */
#define USP_ERR_OAM_VMP_STATUS                   ((WORD32) (USP_ERR_OAM_VMP_BASE + 6))  /* VMP任务状态错误 */
#define USP_ERR_OAM_VMP_NULL_POINTER             ((WORD32) (USP_ERR_OAM_VMP_BASE + 7))  /* 空指针 */
#define USP_ERR_OAM_VMP_VER_CTRL_INFO_DESTROY    ((WORD32) (USP_ERR_OAM_VMP_BASE + 8))  /* 版本控制信息损坏 */
#define USP_ERR_OAM_VMP_UNKNOW_STORE_TYPE        ((WORD32) (USP_ERR_OAM_VMP_BASE + 9))  /* 版本存储类型错误 */
#define USP_ERR_OAM_VMP_NO_RUN_VERSION           ((WORD32) (USP_ERR_OAM_VMP_BASE + 10)) /* 没有可以运行的版本 */
#define USP_ERR_OAM_VMP_SET_VER_CTRL_INFO        ((WORD32) (USP_ERR_OAM_VMP_BASE + 11)) /* 更新版本控制信息失败 */
#define USP_ERR_OAM_VMP_UNKNOW_MSG               ((WORD32) (USP_ERR_OAM_VMP_BASE + 12)) /* 消息号错误 */
#define USP_ERR_OAM_VMP_LLRP_DECODE              ((WORD32) (USP_ERR_OAM_VMP_BASE + 13)) /* LLRP解码错误 */
#define USP_ERR_OAM_VMP_LLRP_ENCODE              ((WORD32) (USP_ERR_OAM_VMP_BASE + 14)) /* LLRP编码错误 */
#define USP_ERR_OAM_VMP_LLRP_UNKNOW_MSG          ((WORD32) (USP_ERR_OAM_VMP_BASE + 15)) /* 未知的LLRP消息 */
#define USP_ERR_OAM_VMP_INVALID_MAIN_INDEX       ((WORD32) (USP_ERR_OAM_VMP_BASE + 16)) /* 非法的版本编号 */
#define USP_ERR_OAM_VMP_INVALID_PARAM            ((WORD32) (USP_ERR_OAM_VMP_BASE + 17)) /* 非法的参数 */
#define USP_ERR_OAM_VMP_FTP_OPEN                 ((WORD32) (USP_ERR_OAM_VMP_BASE + 18)) /* 打开FTP链接失败 */
#define USP_ERR_OAM_VMP_FTP_RECV                 ((WORD32) (USP_ERR_OAM_VMP_BASE + 19)) /* 接收FTP数据失败 */
#define USP_ERR_OAM_VMP_FILE_OPEN                ((WORD32) (USP_ERR_OAM_VMP_BASE + 20)) /* 打开文件失败 */
#define USP_ERR_OAM_VMP_FILE_WRITE               ((WORD32) (USP_ERR_OAM_VMP_BASE + 21)) /* 写文件失败 */
#define USP_ERR_OAM_VMP_FLASH_WRITE              ((WORD32) (USP_ERR_OAM_VMP_BASE + 22)) /* 写FLASH失败 */
#define USP_ERR_OAM_VMP_LMT_UNKNOW_MSG           ((WORD32) (USP_ERR_OAM_VMP_BASE + 23)) /* 未知的LMT消息 */
#define USP_ERR_OAM_VMP_FPGA_LOAD                ((WORD32) (USP_ERR_OAM_VMP_BASE + 24)) /* 加载FPGA失败 */
#define USP_ERR_OAM_VMP_READ_VERSION             ((WORD32) (USP_ERR_OAM_VMP_BASE + 25)) /* 读版本文件失败 */
#define USP_ERR_OAM_VMP_VERSION_DESTROY          ((WORD32) (USP_ERR_OAM_VMP_BASE + 26)) /* 版本损坏 */
#define USP_ERR_OAM_VMP_OPEN_UBOOT               ((WORD32) (USP_ERR_OAM_VMP_BASE + 27)) /* 打开Uboot分区错误 */
#define USP_ERR_OAM_VMP_READ_UBOOT               ((WORD32) (USP_ERR_OAM_VMP_BASE + 28)) /* 读Uboot分区错误 */
#define USP_ERR_OAM_VMP_WRITE_UBOOT              ((WORD32) (USP_ERR_OAM_VMP_BASE + 29)) /* 写Uboot分区错误 */
#define USP_ERR_OAM_VMP_UBOOT_INFO               ((WORD32) (USP_ERR_OAM_VMP_BASE + 30)) /* Uboot版本信息格式错误 */
#define USP_ERR_OAM_VMP_UNKNOW_CLI_CMD           ((WORD32) (USP_ERR_OAM_VMP_BASE + 31)) /* 未知的Cli命令 */
#define USP_ERR_OAM_VMP_BUF_TOO_SMALL            ((WORD32) (USP_ERR_OAM_VMP_BASE + 32)) /* 数据缓冲区太小 */
#define USP_ERR_OAM_VMP_STRING_FORMAT            ((WORD32) (USP_ERR_OAM_VMP_BASE + 33)) /* 字符串格式错误 */
#define USP_ERR_OAM_VMP_NOT_SUPPORT_UPDATE_BOOT  ((WORD32) (USP_ERR_OAM_VMP_BASE + 34)) /* 不支持BOOT升级 */
#define USP_ERR_OAM_VMP_VERSION_INFO_STRING      ((WORD32) (USP_ERR_OAM_VMP_BASE + 35)) /* 版本信息字符串格式错误 */
#define USP_ERR_OAM_VMP_CRC_CHECK                ((WORD32) (USP_ERR_OAM_VMP_BASE + 36)) /* CRC校验错误 */
#define USP_ERR_OAM_VMP_LOAD_CUST                ((WORD32) (USP_ERR_OAM_VMP_BASE + 37)) /* 加载用户自定义版本失败 */
#define USP_ERR_OAM_VMP_CUST_NOT_EXIST           ((WORD32) (USP_ERR_OAM_VMP_BASE + 38)) /* 用户自定义版本不存在 */
#define USP_ERR_OAM_VMP_VERSION_IS_RUN           ((WORD32) (USP_ERR_OAM_VMP_BASE + 39)) /* 版本正在运行 */
#define USP_ERR_OAM_VMP_VERSION_NOT_RUN          ((WORD32) (USP_ERR_OAM_VMP_BASE + 40)) /* 版本没有运行 */
#define USP_ERR_OAM_VMP_CLI_PARAM                ((WORD32) (USP_ERR_OAM_VMP_BASE + 41)) /* 命令行参数错误 */
#define USP_ERR_OAM_VMP_LLRP_PARAM               ((WORD32) (USP_ERR_OAM_VMP_BASE + 42)) /* LLRP参数错误 */
#define USP_ERR_OAM_VMP_FILE_SIZE                ((WORD32) (USP_ERR_OAM_VMP_BASE + 43)) /* 版本文件尺寸错误 */
#define USP_ERR_OAM_VMP_DATA_SIZE                ((WORD32) (USP_ERR_OAM_VMP_BASE + 44)) /* 版本数据帧尺寸错误 */
#define USP_ERR_OAM_VMP_NOT_UPDATE_STAT          ((WORD32) (USP_ERR_OAM_VMP_BASE + 45)) /* 没有处于版本更新状态 */
#define USP_ERR_OAM_VMP_FRAME_INDEX              ((WORD32) (USP_ERR_OAM_VMP_BASE + 46)) /* 数据帧序号不正确 */
#define USP_ERR_OAM_VMP_FRAME_UNKNOW_MSG         ((WORD32) (USP_ERR_OAM_VMP_BASE + 47)) /* 未知的消息 */
#define USP_ERR_OAM_VMP_LOAD_VERSION             ((WORD32) (USP_ERR_OAM_VMP_BASE + 48)) /* 版本加载失败 */
#define USP_ERR_OAM_VMP_TFTP_OPEN                ((WORD32) (USP_ERR_OAM_VMP_BASE + 49)) /* 打开TFTP链接失败 */
#define USP_ERR_OAM_VMP_SIZE_ZERO                ((WORD32) (USP_ERR_OAM_VMP_BASE + 50)) /* 版本大小为零 */
#define USP_ERR_OAM_VMP_NO_VER_CTRL_INFO         ((WORD32) (USP_ERR_OAM_VMP_BASE + 51)) /* 没有找到版本控制信息 */
#define USP_ERR_OAM_VMP_ERASE_VER_CTRL_INFO      ((WORD32) (USP_ERR_OAM_VMP_BASE + 52)) /* 擦除版本控制信息错误 */
#define USP_ERR_OAM_VMP_READ_VER_CTRL_INFO       ((WORD32) (USP_ERR_OAM_VMP_BASE + 53)) /* 读版本控制信息错误 */
#define USP_ERR_OAM_VMP_WRITE_VER_CTRL_INFO      ((WORD32) (USP_ERR_OAM_VMP_BASE + 54)) /* 写版本控制信息错误 */
#define USP_ERR_OAM_VMP_LOAD_SUB_DEV_VER         ((WORD32) (USP_ERR_OAM_VMP_BASE + 55)) /* 加载子板版本失败 */
#define USP_ERR_OAM_VMP_MANAGER_SUB_DEV_VER      ((WORD32) (USP_ERR_OAM_VMP_BASE + 56)) /* 子板版本管理失败 */
#define USP_ERR_OAM_VMP_FPGA_SIZE                ((WORD32) (USP_ERR_OAM_VMP_BASE + 57)) /* FPGA文件大小错误 */
#define USP_ERR_OAM_VMP_FPGA_NAME                ((WORD32) (USP_ERR_OAM_VMP_BASE + 58)) /* FPGA文件名错误 */
#define USP_ERR_OAM_VMP_RECV_MSG_TIMEOUT         ((WORD32) (USP_ERR_OAM_VMP_BASE + 59)) /* 接收消息超时 */
#define USP_ERR_OAM_VMP_UNKNOW_DEV_MODLE         ((WORD32) (USP_ERR_OAM_VMP_BASE + 60)) /* 未知的设备类型 */
#define USP_ERR_OAM_VMP_ZTE_UNKNOW_MSG           ((WORD32) (USP_ERR_OAM_VMP_BASE + 61)) /* 未知的ZTE私有消息 */
#define USP_ERR_OAM_VMP_MALLOC_HANDLE            ((WORD32) (USP_ERR_OAM_VMP_BASE + 62)) /* 获取动态库句柄内存失败 */
#define USP_ERR_OAM_VMP_UNKNOW_VER_TYPE          ((WORD32) (USP_ERR_OAM_VMP_BASE + 63)) /* 未知的版本类型 */
#define USP_ERR_OAM_VMP_SSCANF                   ((WORD32) (USP_ERR_OAM_VMP_BASE + 64)) /* 解析字符串错误 */

/***********************************************************
*                   驱动平台温度传感器模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_TSENSOR_INIT_FIRST      (USP_ERR_DRV_TSENSOR_START+1)
#define USP_ERR_DRV_TSENSOR_INIT_SECOND     (USP_ERR_DRV_TSENSOR_START+2)
#define USP_ERR_DRV_TSENSOR_INIT_ALL        (USP_ERR_DRV_TSENSOR_START+3)
#define USP_ERR_DRV_TSENSOR_SND_PARAM       (USP_ERR_DRV_TSENSOR_START+4)
#define USP_ERR_DRV_TSENSOR_RCV_PARAM       (USP_ERR_DRV_TSENSOR_START+5)
#define USP_ERR_DRV_TSENSOR_OFFSET          (USP_ERR_DRV_TSENSOR_START+6)
#define USP_ERR_DRV_TSENSOR_POR_STATE       (USP_ERR_DRV_TSENSOR_START+7)
#define USP_ERR_DRV_TSENSOR_CONFIG          (USP_ERR_DRV_TSENSOR_START+8)
#define USP_ERR_DRV_TSENSOR_FUN_NUM         (USP_ERR_DRV_TSENSOR_START+9)
#define USP_ERR_DRV_TSENSOR_POR_CONFIG      (USP_ERR_DRV_TSENSOR_START+10)
#define USP_ERR_DRV_TSENSOR_POR_CONVER      (USP_ERR_DRV_TSENSOR_START+11)
#define USP_ERR_DRV_TSENSOR_CONVER          (USP_ERR_DRV_TSENSOR_START+12)
/***********************************************************
*                   驱动平台韦根模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_WG_NUM                                        (USP_ERR_DRV_WG_START+1)
#define USP_ERR_DRV_WG_OPEN                                      (USP_ERR_DRV_WG_START+2)
#define USP_ERR_DRV_WG_INDEX                                    (USP_ERR_DRV_WG_START+3)
#define USP_ERR_DRV_WG_IOCTL                                    (USP_ERR_DRV_WG_START+4)
#define USP_ERR_DRV_WG_READ                                      (USP_ERR_DRV_WG_START+5)
#define USP_ERR_DRV_WG_CLOSE                                    (USP_ERR_DRV_WG_START+6)

/***********************************************************
*                   驱动平台GPRS模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_GPRS_PARA                                   (USP_ERR_DRV_GPRS_START+0x01)
#define USP_ERR_DRV_GPRS_CMD        				            (USP_ERR_DRV_GPRS_START+0x02)
#define USP_ERR_DRV_GPRS_RES_NOTCOMPLETE     			        (USP_ERR_DRV_GPRS_START+0x03)
#define USP_ERR_DRV_GPRS_RES_PARA                               (USP_ERR_DRV_GPRS_START+0x04)
#define USP_ERR_DRV_GPRS_BUF_FULL                               (USP_ERR_DRV_GPRS_START+0x05)
#define USP_ERR_DRV_GPRS_TIMEOUT                                (USP_ERR_DRV_GPRS_START+0x06)
#define USP_ERR_DRV_GPRS_CTRL_POWER                             (USP_ERR_DRV_GPRS_START+0x07)
#define USP_ERR_DRV_GPRS_CTRL_ONOFF                             (USP_ERR_DRV_GPRS_START+0x08)


/***********************************************************
*                   驱动平台ioexpander模块错误码                   *
***********************************************************/
#define USP_ERR_DRV_IOE_INIT               (USP_ERR_DRV_IOE_START + 0x1)  /*初始化错误*/
#define USP_ERR_DRV_IOE_SND_ADDR           (USP_ERR_DRV_IOE_START + 0x2)  /*发送函数获取地址错误*/
#define USP_ERR_DRV_IOE_SND_START          (USP_ERR_DRV_IOE_START + 0x3)  /*发送函数发送起始位错误*/
#define USP_ERR_DRV_IOE_SND_ACK            (USP_ERR_DRV_IOE_START + 0x4)  /*发送函数等待应答位错误*/
#define USP_ERR_DRV_IOE_RCV_ADDR           (USP_ERR_DRV_IOE_START + 0x5)  /*接收函数获取地址错误*/
#define USP_ERR_DRV_IOE_RCV_START          (USP_ERR_DRV_IOE_START + 0x6)  /*接收函数发送起始位错误*/
#define USP_ERR_DRV_IOE_RCV_ACK            (USP_ERR_DRV_IOE_START + 0x7)  /*接收函数等待应答位错误*/
/***********************************************************
*			驱动平台timer模块错误码		    *
***********************************************************/
#define USP_ERR_DRV_TIMER_INIT_FD          (USP_ERR_DRV_TIMER_START + 0x1)  /*初始化函数中文件描述符错误*/
#define USP_ERR_DRV_TIMER_INIT_OPEN        (USP_ERR_DRV_TIMER_START + 0x2)  /*初始化函数中open函数错误*/
#define USP_ERR_DRV_TIMER_INIT_MMAP        (USP_ERR_DRV_TIMER_START + 0x3)  /*初始化函数中mmap函数错误*/
#define USP_ERR_DRV_TIMER_CONTROL_PARA     (USP_ERR_DRV_TIMER_START + 0x4)  /*控制函数参数错误*/
/***********************************************************
*			驱动平台GET_SYSTEM_INFO模块错误码  		    * 
***********************************************************/
#define USP_ERROR_DRV_GET_SYSTEM_INFO_OPEN (USP_ERR_DRV_GET_SYSTEM_INFO_START + 0x1)  /*初始化函数中文件打开失败*/
#define USP_ERROR_DRV_GET_JIFFIES          (USP_ERR_DRV_GET_SYSTEM_INFO_START + 0x2)  /*获取JIFFIES失败*/
#define USP_ERROR_DRV_GET_HZ               (USP_ERR_DRV_GET_SYSTEM_INFO_START + 0x3)  /*获取HZ失败*/
#define USP_ERROR_DRV_PAR_ERROR            (USP_ERR_DRV_GET_SYSTEM_INFO_START + 0x4)  /*入参错误*/
/***********************************************************
*			驱动平台clockgen 模块错误码  		    * 
***********************************************************/
#define USP_ERROR_DRV_CLOCKGEN_CONFIG_TYPE  (USP_ERR_DRV_CLOCKGEN_START + 0x1)  /**/
#define USP_ERROR_DRV_CLOCKGEN_WRITE_REG    (USP_ERR_DRV_CLOCKGEN_START + 0x2)
#define USP_ERROR_DRV_CLOCKGEN_WRITE        (USP_ERR_DRV_CLOCKGEN_START + 0x3)
#define USP_ERROR_DRV_CLOCKGEN_READ_REG     (USP_ERR_DRV_CLOCKGEN_START + 0x4)
#define USP_ERROR_DRV_CLOCKGEN_CLOCK        (USP_ERR_DRV_CLOCKGEN_START + 0x5)
#define USP_ERROR_DRV_CLOCKGEN_UNLOCK       (USP_ERR_DRV_CLOCKGEN_START + 0x6)

/***********************************************************
*			驱动平台Variant SPI 模块错误码  		    * 
***********************************************************/
#define USP_ERR_DRV_VARSPI_PARAM            (USP_ERR_DRV_VARSPI_START + 0x1)
#define USP_ERR_DRV_VARSPI_TIMEOUT          (USP_ERR_DRV_VARSPI_START + 0x2)
#define USP_ERR_DRV_VARSPI_OPERATION        (USP_ERR_DRV_VARSPI_START + 0x3)
#define USP_ERR_DRV_VARSPI_FUNC_ID          (USP_ERR_DRV_VARSPI_START + 0x4)

/***********************************************************
*			驱动平台Relay 模块错误码  		    * 
***********************************************************/
#define USP_ERR_DRV_RELAY_PARAM             (USP_ERR_DRV_RELAY_START + 0x1)

/***********************************************************
*			 		MPI 模块错误码						          *
***********************************************************/
#define USP_ERR_MPI_MALLOC_HANDLE			(USP_MPI_ERR_BASE + 1)	/* 获取动态库句柄内存失败 */
#define USP_ERR_MPI_INVALID_TNO             (USP_MPI_ERR_BASE + 2)	/* 获取脚本任务号失败 */
#define USP_ERR_MPI_RFTEST          		(USP_MPI_ERR_BASE + 3)	/* 433M 信号检测失败 */
#define USP_ERR_MPI_CCTEST          		(USP_MPI_ERR_BASE + 4)	/* CC1101 检测失败 */
#define USP_ERR_MPI_SENDMSGTORF				(USP_MPI_ERR_BASE + 5)	/* MPI 数字板任务向射频板任务发消息失败 */
#define USP_ERR_MPI_RECVMSGFROMRF           (USP_MPI_ERR_BASE + 6)	/* MPI 数字板任务从射频板任务收消息失败 */
#define USP_ERR_MPI_SENDMSGACK				(USP_MPI_ERR_BASE + 7)	/* MPI 数字板任务向脚本回消息失败 */
#define USP_ERR_MPI_RFBSPINIT				(USP_MPI_ERR_BASE + 8)	/* 射频板硬件初始化失败 */
#define USP_ERR_MPI_POWEROUTRANGE			(USP_MPI_ERR_BASE + 9)	/* 射频功率超范围*/
#define USP_ERR_MPI_AUTOCALIBRATE			(USP_MPI_ERR_BASE + 10)	/* 射频功率自校准失败 */
#define USP_ERR_MPI_READSYSINFODATA			(USP_MPI_ERR_BASE + 11)	/* 读取射频定标数据失败 */
#define USP_ERR_MPI_BSPCCINIT          		(USP_MPI_ERR_BASE + 12)	/* CC1101 初始化失败 */
#define USP_ERR_MPI_RXCC_RX_OVERTIME        (USP_MPI_ERR_BASE + 13)	/* 反向检测芯片接收数据帧失败 */
#define USP_ERR_MPI_DECCC_RX_OVERTIME       (USP_MPI_ERR_BASE + 14)	/* 自校准芯片接收数据帧失败 */
#define USP_ERR_MPI_INVALID_RETURNINFO		(USP_MPI_ERR_BASE + 15)	/* 无效的返回信息 */
#define USP_ERR_MPI_RFHARDWARE              (USP_MPI_ERR_BASE + 16)	/* 射频硬件错误 */
#define USP_ERR_MPI_LIB_OPENRF              (USP_MPI_ERR_BASE + 17)	/* 动态库打开射频失败 */
#define MPI_SHELL_ERROR_PSAM_ACTIVE         (USP_MPI_ERR_BASE + 18)	/* 动态库激活PSAM 卡失败 */

/***********************************************************
*   扩展PSAM管理任务错误码                                 *
***********************************************************/
#define USP_OSS_PSAM_EXT_ERR_UNKNOW_MSG     ((WORD32) (USP_ERR_OSS_PSAM_EXT_BASE + 1)) /* 未知的消息 */
#define USP_OSS_PSAM_EXT_ERR_CMD_ACK        ((WORD32) (USP_ERR_OSS_PSAM_EXT_BASE + 2)) /* 错误的PSAM命令操作应答消息 */
#define USP_OSS_PSAM_EXT_ERR_KEEP_ALIVE     ((WORD32) (USP_ERR_OSS_PSAM_EXT_BASE + 3)) /* 错误的心跳消息 */
#define USP_OSS_PSAM_EXT_ERR_ACTIVE_ACK     ((WORD32) (USP_ERR_OSS_PSAM_EXT_BASE + 4)) /* 错误的PSAM激活操作应答消息 */


/***********************************************************
*   GPIO和Relay模块任务错误码                                 *
***********************************************************/
#define  USP_GPIO_ERR_DECODE_MSG            ((WORD32) (USP_GPIO_ERR_BASE + 1)) /* 解码失败*/
#define  USP_GPIO_ERR_SEND_MSG              ((WORD32) (USP_GPIO_ERR_BASE + 2)) /* 发送消息失败*/
#define  USP_GPIO_UNKOWN_MSG                ((WORD32) (USP_GPIO_ERR_BASE + 3)) /* 未知消息*/
#define  USP_GPIO_ERR_INVALID_PARA          ((WORD32) (USP_GPIO_ERR_BASE + 4)) /* 非法的参数*/
#define  USP_GPIO_ERR_MALLOC_HANDLE         ((WORD32) (USP_GPIO_ERR_BASE + 5)) /* 获取动态库句柄内存失败 */ 
#define  USP_GPIO_ERR_INVALID_TNO           ((WORD32) (USP_GPIO_ERR_BASE + 6)) /* 错误的任务号 */
#define  USP_GPIO_ERR_INTERRUPT_PORT        ((WORD32) (USP_GPIO_ERR_BASE + 7)) /* 错误的中断端口号*/

/***********************************************************
*   杂项任务错误码                                         *
***********************************************************/
#define USP_ERR_OSS_MISC_MALLOC_HANDLE      ((WORD32) (USP_ERR_OSS_MISC_BASE + 1)) /* 获取动态库句柄内存失败 */
#define USP_ERR_OSS_MISC_INVALID_PARAM      ((WORD32) (USP_ERR_OSS_MISC_BASE + 2)) /* 非法的参数 */


#endif  /* _USP_ERROR_DEF_H */


