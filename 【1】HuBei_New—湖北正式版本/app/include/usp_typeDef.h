/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_typeDef.h
* 文件标识： 
* 内容摘要： 定义公用数据类型
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.03.10
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

#define USP_CPU_WORD_SIZE 32  /* 机器字长定义 */

/***********************************************************
 *                       数据类型定义                      *
 ***********************************************************/

#if (USP_CPU_WORD_SIZE == 32)
typedef unsigned short int  WORD16;    
typedef signed short int    SWORD16;

typedef unsigned int        WORD32;
typedef signed   int        SWORD32;

typedef unsigned long long  WORD64;
typedef signed long long    SWORD64;

typedef unsigned int        BOOLEAN;

typedef float               FP32;
typedef double              FP64;
#endif

#if (USP_CPU_WORD_SIZE == 16)
typedef unsigned short int  WORD16;    
typedef signed short int    SWORD16;

typedef unsigned long       WORD32;
typedef signed   long       SWORD32;

typedef unsigned short int  BOOLEAN;

typedef float               FP32;
#endif

#if (USP_CPU_WORD_SIZE == 64)
/* 
 * 64位机目前还没有定义
 */
#endif

typedef unsigned char       BYTE;
typedef signed char         CHAR;

#ifndef WIN32
#define VOID                void
#endif


#endif  /* _USP_TYPE_DEF_H */

