/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_ltk.h
* 文件标识： 
* 内容摘要： LLRP工具箱对外接口
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.05.09
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_LTK_H
#define _USP_LTK_H

#include <stdarg.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> 
#include "ltkc.h"




/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/
/* LLRP消息号定义 */
#define LTK_KEEPLIVE_MSG_TYPE                               (62)        /* keelive消息类型 */
#define LTK_KEEPLIVE_ACK_MSG_TYPE                           (72)        /* keelive应答消息类型 */

#define LTK_ENABLE_EVENTS_AND_REPORTS_MSG_TYPE              (64)        /* 开启断链缓存数据上报 */
#define LTK_DELETE_SAVED_RO_ACCESS_REPORT_MSG_TYPE          (91)        /* 清空断链缓存数据 */
#define LTK_SAVED_RO_ACCESS_REPORT_ACK_MSG_TYPE             (94)        /* 断链缓存发送应答 */

#define LTK_READER_TRACK_CTRL_MSG_TYPE                      (44)        /* 信令跟踪控制消息 */
#define LTK_READER_RUNINFO_CTRL_MSG_TYPE                    (43)        /* 运行信息观察控制消息 */

#define LTK_GET_READER_LOG_MSG_TYPE                         (28)        /* 请求上传日志消息 */
#define LTK_GET_READER_LOG_RESPONSE_ACK_MSG_TYPE            (95)        /* 收到日志信息的应答消息 */
#define LTK_GET_READER_EXCEPTION_MSG_TYPE                   (29)        /* 请求上传异常消息 */
#define LTK_GET_READER_EXCEPTION_RESPONSE_ACK_MSG_TYPE      (96)        /* 收到异常信息的应答消息 */

#define LTK_READER_VERSION_ACTIVATE                   (21)
#define LTK_READER_VERSION_ACTIVATE_RESPONSE          (31)
#define LTK_READER_VERSION_UNACTIVATE                 (22)
#define LTK_READER_VERSION_UNACTIVATE_RESPONSE        (32)
#define LTK_READER_VERSION_QUERY                      (23)
#define LTK_READER_VERSION_QUERY_RESPONSE             (33)
#define LTK_READER_VERSION_DOWNLOAD_REQUEST           (24)   
#define LTK_READER_VERSION_DOWNLOAD_REQUEST_RESPONSE  (34)
#define LTK_READER_VERSION_DOWNLOAD                   (25)
#define LTK_READER_VERSION_DOWNLOAD_RESPONSE          (35)
#define LTK_READER_UBOOTVERSION_QUERY                 (26)
#define LTK_READER_UBOOTVERSION_QUERY_RESPONSE        (36)
#define LTK_READER_UBOOTVERSION_UPDATE                (27)
#define LTK_READER_UBOOTVERSION_UPDATE_RESPONSE       (37)
#define LTK_READER_CUSTVERSION_QUERY                  (107)
#define LTK_READER_CUSTVERSION_QUERY_RESPONSE         (117)
#define LTK_READER_CUSTVERSION_DOWNLOAD               (106)
#define LTK_READER_CUSTVERSION_DOWNLOAD_RESPONSE      (116)
#define LTK_READER_CUSTVERSION_DELETE                 (105)
#define LTK_READER_CUSTVERSION_DELETE_RESPONSE        (115)

#define USP_LTK_ERR_BASE 0x1000
#define USP_LTK_ERR_FRAMEENCODER_CONSTRUCTOR    ((unsigned int) (USP_LTK_ERR_BASE + 1)) /* 帧编码器构建错误 */
#define USP_LTK_ERR_FRAMEENCODE                 ((unsigned int) (USP_LTK_ERR_BASE + 2)) /* 帧编码错误 */
#define USP_LTK_ERR_XMLTEXTENCODER_CONSTRUCTOR  ((unsigned int) (USP_LTK_ERR_BASE + 3)) /* xml字符串编码器构建错误 */
#define USP_LTK_ERR_XMLTEXTENCODE               ((unsigned int) (USP_LTK_ERR_BASE + 4)) /* xml字符串编码错误 */
#define USP_LTK_ERR_BUF_OVERFLOW                ((unsigned int) (USP_LTK_ERR_BASE + 5)) /* 缓冲区溢出错误 */
#define USP_LTK_ERR_MALLOC_HANDLE               ((unsigned int) (USP_LTK_ERR_BASE + 6)) /* 获取动态库句柄内存失败 */

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/
/* 类型注册器 */
extern LLRP_tSTypeRegistry     usp_ltk_tSTypeRegistry;


/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
/* LTK初始化 */
extern unsigned int usp_ltk_init(void);

/* 把字节流形式标识的llrp消息解析成应用需要的数据结构 */
extern LLRP_tSMessage *usp_ltk_decodeMessage(unsigned char *pucBuf, unsigned short int wLen, LLRP_tSErrorDetails *pError);

/* 释放消息所占用的内存空间 */
extern void usp_ltk_freeMessage(LLRP_tSMessage *pMessage);

/* 把应用的LLRP消息数据结构编码成适用于通信链路传输的字节流形式 */
extern unsigned int usp_ltk_encodeMessage(unsigned char *pucBuf, unsigned short int *pwLen, LLRP_tSMessage *pMessage, LLRP_tSErrorDetails *pError);

/* 把消息转换为xml字符串格式 */
extern unsigned int usp_ltk_messageToXMLString(unsigned char *pucBuf, unsigned short int wLen, LLRP_tSMessage *pMessage, LLRP_tSErrorDetails *pError);


#endif  /* _USP_LTK_H */

