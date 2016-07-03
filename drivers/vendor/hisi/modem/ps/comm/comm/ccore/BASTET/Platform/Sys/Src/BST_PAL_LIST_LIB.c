

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_PAL_LIST.h"
#include "BST_OS_Memory.h"
#include "stdlib.h"
#if (VOS_RTOSCK == VOS_OS_VER)
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_LIST_LIB_C

/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/

/******************************************************************************
   6 函数实现
******************************************************************************/


BST_VOID BST_ListInit( LIST *pList )
{
    if( BST_NULL_PTR == pList )
    {
        return;
    }

    pList->node.next     = BST_NULL_PTR;
    pList->node.previous = BST_NULL_PTR;
    pList->count         = 0;

    return;
}


BST_VOID BST_ListAdd( LIST *pList, NODE *pNode )
{
    NODE                               *pNext;
    NODE                               *pPrev;

    if( ( BST_NULL_PTR == pList ) || ( BST_NULL_PTR == pNode ) )
    {
        return;
    }

    pPrev = pList->node.previous;

    if (pPrev == BST_NULL_PTR)
    {
        pNext            = pList->node.next;
        pList->node.next = pNode;
    }
    else
    {
        pNext = pPrev->next;
        pPrev->next = pNode;
    }

    if (pNext == BST_NULL_PTR)
    {
        pList->node.previous = pNode;
    }
    else
    {
        pNext->previous = pNode;
    }

    pNode->next = pNext;
    pNode->previous = pPrev;

    pList->count++;

    return;
}


BST_INT16 BST_ListCount( LIST *pList )
{
    if( BST_NULL_PTR == pList )
    {
        return 0;
    }

    return (pList->count);
}


BST_VOID BST_ListDelete( LIST *pList, NODE *pNode )
{
    if( ( BST_NULL_PTR == pList ) || ( BST_NULL_PTR == pNode ) )
    {
        return;
    }

    if (pNode->previous == BST_NULL_PTR)
    {
        pList->node.next = pNode->next;
    }
    else
    {
        pNode->previous->next = pNode->next;
    }

    if (pNode->next == BST_NULL_PTR)
    {
        pList->node.previous = pNode->previous;
    }
    else
    {
        pNode->next->previous = pNode->previous;
    }

    if( pList->count > 0 )
    {
        pList->count--;
    }

    return;
}


NODE *BST_ListFirst ( LIST *pList )
{
    if( BST_NULL_PTR == pList )
    {
        return BST_NULL_PTR;
    }

    return (pList->node.next);
}


NODE *BST_ListGet( LIST *pList )
{
    NODE                               *pNode;

    if( BST_NULL_PTR == pList )
    {
        return BST_NULL_PTR;
    }

    pNode = pList->node.next;

    if (pNode != BST_NULL_PTR)
    {
        pList->node.next = pNode->next;

        if (pNode->next == BST_NULL_PTR)
        {
            pList->node.previous = BST_NULL_PTR;
        }
        else
        {
            pNode->next->previous = BST_NULL_PTR;
        }

        if( pList->count > 0 )
        {
            pList->count--;
        }
    }

    return (pNode);
}


NODE *BST_ListNext( NODE *pNode )
{
    if( BST_NULL_PTR == pNode )
    {
        return BST_NULL_PTR;
    }

    return (pNode->next);
}


BST_VOID BST_ListFree( LIST *pList )
{
    NODE                               *p1;
    NODE                               *p2;

    if( BST_NULL_PTR == pList )
    {
        return;
    }

    if (pList->count > 0)
    {
        p1 = pList->node.next;

        while (p1 != BST_NULL_PTR)
        {
            p2 = p1->next;
            BST_OS_FREE( p1 );
            p1 = p2;
        }

        pList->count         = 0;
        pList->node.next     = BST_NULL_PTR;
        pList->node.previous = BST_NULL_PTR;
    }

    return;
}
#endif