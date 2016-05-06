/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              avltree.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-02-02
*        Author: qinyun (62011)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-02   qinyun (62011)          Create
*
*******************************************************************************/
#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef LONG (COMM_COMPARE)(VOID *, VOID * );

typedef struct tagAVL3_NODE
{
  struct tagAVL3_NODE *parent;
  struct tagAVL3_NODE *left;
  struct tagAVL3_NODE *right;
  SHORT sLeftHeight;
  SHORT sRightHeight;
} AVL3_NODE_S;


typedef struct tagAVL3_TREE_INFO
{
  COMM_COMPARE *compare;
  USHORT usKeyOffset;
  USHORT usNodeOffset;
} AVL3_TREE_INFO_S;

typedef struct tagAVL3_TREE
{
  AVL3_NODE_S *root;
  AVL3_NODE_S *first;
  AVL3_NODE_S *last;
} AVL3_TREE_S;

#define VOS_MAX(X, Y)   (((X)>(Y)) ? (X) : (Y))

VOID *AVL3_FindToInsert(AVL3_TREE_S *pstAvlTree,AVL3_NODE_S *pstAvlNode,AVL3_TREE_INFO_S *pstTreeInfo );
VOID AVL3_DeleteNode(AVL3_TREE_S *pstAvlTree, AVL3_NODE_S *pstAvlNode);
VOID *AVL3_FindNode(AVL3_TREE_S *pstAvlTree,VOID *pKey,AVL3_TREE_INFO_S *pstTreeInfo);
VOID *AVL3_GetFirstNode(AVL3_TREE_S *pstAvlTree,AVL3_TREE_INFO_S *pstTreeInfo);
VOID *AVL3_GetLastNode(AVL3_TREE_S *pstAvlTree,AVL3_TREE_INFO_S *pstTreeInfo);
VOID *AVL3_GetNextNode(AVL3_NODE_S *pstAvlNode,AVL3_TREE_INFO_S *pstTreeInfo);
VOID *AVL3_GetPrevNode(AVL3_NODE_S *pstAvlNode,AVL3_TREE_INFO_S *pstTreeInfo);
VOID AVL3_BalanceAvlTree(AVL3_TREE_S *pstAvlTree,AVL3_NODE_S *pstAvlNode);
VOID AVL3_RebalanceAvlTree(AVL3_NODE_S **pstSubTreeNode);
VOID AVL3_RotateRightSubTree(AVL3_NODE_S **pstSubTreeNode);
VOID AVL3_RotateLeftSubTree(AVL3_NODE_S **pstSubTreeNode);
VOID AVL3_SwapAvlRightNodeMost(AVL3_TREE_S *pstAvlTree,AVL3_NODE_S *pstSubTreeNode,AVL3_NODE_S *pstAvlNode);
VOID AVL3_SwapAvlLeftNodeMost(AVL3_TREE_S *pstAvlTree,AVL3_NODE_S *pstSubTreeNode,AVL3_NODE_S *pstAvlNode);
VOID *AVL3_FindCurrentOrNextNode(AVL3_TREE_S *pstAvlTree,VOID *pKey,BOOL_T blEqual,AVL3_TREE_INFO_S *pstTreeInfo);
VOID AVL3_VerifyAvlTree(AVL3_TREE_S *pstAvlTree,AVL3_TREE_INFO_S *pstTreeInfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AVLTREE_H_ */
