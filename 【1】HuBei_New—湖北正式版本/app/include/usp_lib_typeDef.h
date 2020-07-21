/************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_lib_typeDef.h
* 文件标识： 
* 内容摘要： 定义公用数据类型
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
#ifndef _USP_TYPE_DEF_H
#define _USP_TYPE_DEF_H

/***********************************************************
 *                       数据类型定义                      *
 ***********************************************************/
typedef unsigned short int  WORD16;    
typedef signed short int    SWORD16;

typedef unsigned int        WORD32;
typedef signed   int        SWORD32;

typedef unsigned long long  WORD64;
typedef signed long long    SWORD64;

typedef unsigned int        BOOLEAN;

typedef float               FP32;
typedef double              FP64;

typedef unsigned char       BYTE;
typedef signed char         CHAR;

#ifndef WIN32
#define VOID                void                
#endif

#endif  /* _USP_TYPE_DEF_H */

