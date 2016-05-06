/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_PAL_LIST_LIB.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年07月14日
  最近修改   :
  功能描述   : BST_PAL_LIST_LIB.c的头文件定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年07月14日
    作    者   :
    修改内容   : 建立文件

******************************************************************************/
#ifndef __BST_LIB_List_H__
#define __BST_LIB_List_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Typedefine.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define lstFirst              BST_ListFirst
#define lstGet                BST_ListGet
#define lstNext               BST_ListNext
#define lstCount              BST_ListCount
#define lstAdd                BST_ListAdd
#define lstDelete             BST_ListDelete
#define lstFree               BST_ListFree
#define lstInit               BST_ListInit
/*****************************************************************************
  3 类/结构定义
*****************************************************************************/
typedef struct BST_node
{
    struct BST_node *next;
    struct BST_node *previous;
} BST_NODE;

typedef struct
{
    BST_NODE    node;
    BST_INT16   count;
}BST_LIST;

typedef BST_NODE NODE;
typedef BST_LIST LIST;

/*****************************************************************************
  4 函数声明
*****************************************************************************/
extern NODE *       BST_ListFirst (LIST *pList);
extern NODE *       BST_ListGet (LIST *pList);
extern NODE *       BST_ListNext (NODE *pNode);
extern BST_INT16    BST_ListCount (LIST *pList);
extern BST_VOID     BST_ListAdd (LIST *pList, NODE *pNode);
extern BST_VOID     BST_ListDelete (LIST *pList, NODE *pNode);
extern BST_VOID     BST_ListFree (LIST *pList);
extern BST_VOID     BST_ListInit (LIST *pList);

#ifdef __cplusplus
}
#endif

#endif
