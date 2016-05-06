/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ip6_avl.h
  Version       : Initial Draft
  Author        : Prabhu H 71185
  Project Code  : IPB IR V1R2
  Created       : 2006/8/23
  Last Modified :
  Description   : AVL Tree related data structures and function declarations

  Function List :
  History       :
  1.Date        : 2006/8/23
    Author      : Prabhu H 71185
    Modification: Created file for IPBIRV100R002.IP.E001

******************************************************************************/

#ifndef _IP6_AVL_H
#define _IP6_AVL_H

#ifdef _cplusplus
extern "C"{
#endif

#define IP6_AVL_INSERT_OK           0
#define IP6_AVL_INSERT_FAIL_DUPE    1
#define IP6_AVL_INSERT_FAIL_MALLOC  2
#define IP6_AVL_INSERT_FAIL_TOODEEP 3
#define IP6_AVL_INSERT_FAIL_CMP     4
#define IP6_AVL_MAX_STACK_DEPTH     50

#define IP6_AVL_STATE_NEITHER 1
#define IP6_AVL_STATE_LEFT    2
#define IP6_AVL_STATE_RIGHT   3

typedef int (*pfIP6_AvlCmpKeyFn)(VOID*, VOID*);
typedef VOID (*pfIP6_AvlFreeFn)(VOID*);

/* Structure element of single Avl Node */
typedef struct tagIP6_AVL_NODE
{
    VOID *pData;
    struct tagIP6_AVL_NODE *pstLeft, *pstRight;
    ULONG ulHeight;
} IP6_AVL_NODE_S;

/* Structure element of Avl Tree pointing to the 'root' node */
typedef struct tagIP6_AVL_TREE
{
    IP6_AVL_NODE_S *pstRoot;
    pfIP6_AvlCmpKeyFn pfCmpkey;
    pfIP6_AvlFreeFn pfFreefn;
} IP6_AVL_TREE_S;

IP6_AVL_TREE_S* IPB_IR_IP6_AvlHeadAlloc(
    pfIP6_AvlCmpKeyFn pfCmpKeyFn, pfIP6_AvlFreeFn pfFreeFn, ULONG ulMid);
VOID IPB_IR_IP6_AvlHeadFree(IP6_AVL_TREE_S *pstAvl);
VOID* IPB_IR_IP6_AvlSearch(IP6_AVL_TREE_S *pstAvl, VOID *pkey);
VOID* IPB_IR_IP6_AvlSearchNext(IP6_AVL_TREE_S *pstAvl, VOID *pKey);
ULONG IPB_IR_IP6_AvlInsert(IP6_AVL_TREE_S *pstAvl, VOID *pData, ULONG ulMid);
VOID* IPB_IR_IP6_AvlDelete(IP6_AVL_TREE_S *pstAvl, VOID *pKey);
ULONG IPB_IR_IP6_AvlCalcHt(IP6_AVL_NODE_S *pstNode);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* _IP6_AVL_H */

