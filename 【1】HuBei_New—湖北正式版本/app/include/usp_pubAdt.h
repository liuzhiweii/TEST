/************************************************************************
* 版权所有 (C)2011, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_pubAdt.h
* 文件标识： 
* 内容摘要： 抽象数据结构头文件
* 其它说明： 
* 当前版本： 
* 作    者： 陈善君
* 完成日期： 2011.06.18
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/

#ifndef _USP_PUB_ADT_H
#define _USP_PUB_ADT_H
/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**************************************************************************
 *                          宏定义                                         *
 **************************************************************************/ 


/**************************************************************************
 *                            数据类型                                     *
 **************************************************************************/ 

typedef struct tagT_USPPubAdtListNode
{
    struct tagT_USPPubAdtListNode  *ptNext;
    struct tagT_USPPubAdtListNode  *ptPrevious;
} T_USPPubAdtListNode;

typedef struct tagT_USPPubAdtList
{
    WORD32                 dwCount;
    T_USPPubAdtListNode    tNode;
}T_USPPubAdtList;


/**************************************************************************
 *                             类声明                                      *
 **************************************************************************/

/**************************************************************************
 *                           模板                                         *
 **************************************************************************/


/**************************************************************************
 *                         全局变量声明                                    *
 **************************************************************************/

/**************************************************************************
 *                        全局函数原型                                     *
 **************************************************************************/

VOID                    usp_pub_adt_listInit( T_USPPubAdtList *ptPubAdtList );
VOID                    usp_pub_adt_listInsert( T_USPPubAdtList *ptPubAdtList, T_USPPubAdtListNode *ptPrev, T_USPPubAdtListNode *ptNode );
VOID                    usp_pub_adt_listAdd( T_USPPubAdtList *ptPubAdtList, T_USPPubAdtListNode *ptNode );
VOID                    usp_pub_adt_listDelete( T_USPPubAdtList *ptPubAdtList, T_USPPubAdtListNode *ptNode );
T_USPPubAdtListNode    *usp_pub_adt_listFirst( T_USPPubAdtList *ptPubAdtList );
T_USPPubAdtListNode    *usp_pub_adt_listLast(  T_USPPubAdtList *ptPubAdtList );
T_USPPubAdtListNode    *usp_pub_adt_listGet( T_USPPubAdtList *ptPubAdtList );
T_USPPubAdtListNode    *usp_pub_adt_listNext( T_USPPubAdtListNode *ptNode );
T_USPPubAdtListNode    *usp_pub_adt_listPrevious( T_USPPubAdtListNode *ptNode );
T_USPPubAdtListNode    *usp_pub_adt_listNth( T_USPPubAdtList *ptPubAdtList, WORD32 dwNodeNum );
VOID                    usp_pub_adt_listConcat( T_USPPubAdtList *ptDstList, T_USPPubAdtList *ptAddList );
WORD32                  usp_pub_adt_listCount( T_USPPubAdtList *ptPubAdtList );


#endif  /* _USP_PUB_ADT_H */

