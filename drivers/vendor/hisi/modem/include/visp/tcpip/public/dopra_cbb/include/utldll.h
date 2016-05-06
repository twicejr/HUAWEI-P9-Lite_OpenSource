/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              utldll.h
*
*  Project Code: VISPV1R5
*   Module Name: DLL(Doubly Linked List)  
*  Date Created: 2006-7-10
*        Author: X36317
*   Description: Contains prototype declaration for functions supported by 
*                DLL Library 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-7-10  X36317         Creat the first version.
*
*******************************************************************************/

/*暂不修改为_UTLDLL_H_, 因为目前VISP代码中有些地方同时包含了utldll.h和vrp_dll.h*/
//#ifndef __VRP_DLL_H__  /* 升级DopraV2后vrp_dll.h改了预编译宏为__VRP_DLL_H__, */
/*为了防止同时包含两个头文件导致重定义, 添加此预编译宏 h00121208 091113*/
#ifndef _VRP_DLL_H
#ifndef __VRP_DLL_H__
#define _VRP_DLL_H
#define __VRP_DLL_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


typedef struct DLL_NODE
{
    struct DLL_NODE *pNext;      /* Points at the next node in the list */
    struct DLL_NODE *pPrev;      /* Points at the previous node in the list */
    UINTPTR      ulHandle;    /* Only used by user, e.g. used to save user data */
} DLL_NODE_S;


typedef struct DLL
{
    DLL_NODE_S  Head;            /* Header List Node */
    VOS_UINT32  u4_Count;        /* Number Of Nodes In List */
}DLL_S;



/* This Macro get the handle value of DLL node */
#ifndef DLL_GET_HANDLE
#define DLL_GET_HANDLE( pNode )              ((pNode)->ulHandle)
#endif


/* This Macro set the handle value of DLL node */
#ifndef DLL_SET_HANDLE
#define DLL_SET_HANDLE( pNode, ulValue )     ((pNode)->ulHandle = (VOS_UINT32)(ulValue))
#endif


/* This Macro initial a DLL list */
#ifndef DLL_Init
#define DLL_Init(pList) \
    {\
        (pList)->Head.pNext = &(pList)->Head; \
        (pList)->Head.pPrev = &(pList)->Head; \
        (pList)->u4_Count   = 0; \
    }
#endif


/* This Macro Initialises The Node */
#ifndef DLL_Init_Node
#define DLL_Init_Node( pNode ) \
        (pNode)->pPrev = (pNode)->pNext = NULL;
#endif


/* This mocro used to add a dll node */
#ifndef DLL_Add
#define DLL_Add(pList,pNode) \
        DLL_Insert_In_Middle((pList),(pList)->Head.pPrev,(pNode),&(pList)->Head)
#endif

/* This mocro used to get node count */
#ifndef DLL_Count
#define DLL_Count(pList) ((pList)->u4_Count)
#endif

/* This mocro used to get first node */
#ifndef DLL_First
#define DLL_First( pList ) \
        ((DLL_Count((pList)) == 0) ? NULL: (pList)->Head.pNext)
#endif

/* This mocro used to get last node */
#ifndef DLL_Last
#define DLL_Last( pList ) \
        ((DLL_Count((pList)) == 0) ? NULL : (pList)->Head.pPrev)
#endif

/* This mocro used to get next node */
#ifndef DLL_Next
#define DLL_Next(pList,pNode) \
        (((pNode) == NULL) ? DLL_First(pList) : \
        (((pNode)->pNext == &(pList)->Head) ? NULL : (pNode)->pNext))
#endif

/* This mocro used to get previous node */
#ifndef DLL_Previous
#define DLL_Previous(pList,pNode) \
        (((pNode) == NULL) ? DLL_Last(pList) : \
        (((pNode)->pPrev == &(pList)->Head) ? NULL : (pNode)->pPrev))
#endif

/* This mocro used to judge the node is in list or not */
#ifndef DLL_Is_Node_In_List
#define DLL_Is_Node_In_List(pNode) \
        (((pNode)->pNext != NULL) && \
         ((pNode)->pPrev != NULL) && \
         ((pNode)->pNext->pPrev == pNode) && \
         ((pNode)->pPrev->pNext == pNode))
#endif

/* This Macro Is Useful For Scanning Through The Entire List 'pNode' Is A Temp. */
/* Variable Of Type 'TypeCast'. pList is the Pointer To linked_list */
#ifndef DLL_Scan
#define DLL_Scan( pList, pNode, TypeCast ) \
        for( pNode = (TypeCast)(DLL_First((pList))); \
             pNode != NULL; \
             pNode = (TypeCast)(DLL_Next((pList),((DLL_NODE_S *)(pNode)))) )
#endif


extern DLL_NODE_S* DLL_Find( DLL_S *pList, VOS_VOID *pKey, VOS_INT32 (*fnValCmp)(VOS_VOID *, DLL_NODE_S *) );
extern DLL_NODE_S* DLL_Get( DLL_S *pList );
extern VOS_VOID    DLL_Insert_In_Middle( DLL_S *pList, DLL_NODE_S *pPrev, DLL_NODE_S *pMid, DLL_NODE_S *pNext );
extern VOS_VOID    DLL_Insert( DLL_S *pList, DLL_NODE_S *pPrev, DLL_NODE_S *pNode );
extern VOS_VOID    DLL_Delete_In_Middle( DLL_S *pList, DLL_NODE_S *pPrev, DLL_NODE_S *pNode, DLL_NODE_S *pNext );
extern VOS_VOID    DLL_Delete( DLL_S *pList, DLL_NODE_S *pNode );
extern VOS_VOID    DLL_FreeAll( DLL_S *pList, VOS_VOID (*fnFree)(VOS_VOID *) );
extern VOS_INT32   DLL_Walk( DLL_S *pList, VOS_VOID (*fnVisit)(DLL_NODE_S *) );


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VRP_DLL_H */
#endif /* __VRP_DLL_H__*/

