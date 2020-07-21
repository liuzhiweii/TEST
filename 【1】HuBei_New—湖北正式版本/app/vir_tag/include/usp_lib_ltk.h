/************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_lib_ltk.h
* 文件标识： 
* 内容摘要： LLRP工具箱动态库对外接口
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2012.02.06
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_LIB_LTK_H
#define _USP_LIB_LTK_H

#include "usp_lib_ltkc.h"

/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/

/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/

/* LTK操作句柄抽象数据类型 */
typedef struct tagT_LtkLibHandle    *USPLibLtkHandle;

/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/
/* 打开LTK模块 */
extern WORD32 usp_lib_ltk_open(USPLibHandle handle, BYTE *pucDesc);

/* 关闭LTK模块 */
extern WORD32 usp_lib_ltk_close(USPLibHandle handle);

/* 把字节流形式标识的llrp消息解析成应用需要的数据结构 */
extern LLRP_tSMessage *usp_lib_ltk_decodeMessage(USPLibHandle handle, BYTE *pucBuf, WORD16 wLen, LLRP_tSErrorDetails *pError);

/* 释放消息所占用的内存空间 */
extern VOID usp_lib_ltk_freeMessage(USPLibHandle handle, LLRP_tSMessage *pMessage);

/* 把应用的LLRP消息数据结构编码成适用于通信链路传输的字节流形式 */
extern WORD32 usp_lib_ltk_encodeMessage(USPLibHandle handle, BYTE *pucBuf, WORD16 *pwLen, LLRP_tSMessage *pMessage, LLRP_tSErrorDetails *pError);

/* 把消息转换为xml字符串格式 */
extern WORD32 usp_lib_ltk_messageToXMLString(USPLibHandle handle, BYTE *pucBuf, WORD16 wLen, LLRP_tSMessage *pMessage, LLRP_tSErrorDetails *pError);


#endif  /* _USP_LIB_LTK_H */

