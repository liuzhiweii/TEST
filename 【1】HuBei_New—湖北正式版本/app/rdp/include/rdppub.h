/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： RdpPub.h
* 文件标识： 
* 内容摘要：RDP三个模块公用头文件
* 其它说明： 
* 当前版本： 
* 作    者： lzy
* 完成日期： 2012.03.19
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _RDP_PUB_H
#define _RDP_PUB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/prctl.h>
#include <sys/time.h> 
#include <sys/resource.h>
#include <unistd.h>
#include <assert.h>

#include "rdpprotocolpub.h"
#include "uhfllrpRule.h"
#include "uhfllrpDispatch.h"
#include "uhfllrpReport.h"
#include "uhfllrpEpc.h"
#include "uhfllrpISO6B.h"
#include "uhfllrpGB.h"






#define USP_LIB_SCP_MSGSEQ(n)       (0xFFFF == (++(n)) ? ++(n) : (n))


#define CHECK_FAIL_NUMBER(p,s)                             \
do\
{\
    if((p)<0)                                 \
    {                                             \
       printf("%s file:%s line:%u\r\n",s,__FILE__,__LINE__);\
       exit(-1);                                 \
    }\
}while(0)

#define CHECK_NULL_POINTER_RETURN_VOID(p)\
		do\
		{\
			if(NULL==(p))								  \
			{											  \
			   RdpLlrpDbgPrint("null pointer error file:%s line:%u\r\n",__FILE__,__LINE__);\
			   return ; 								\
			}\
		}while(0)




#endif  /* _RDP_PUB_H */

