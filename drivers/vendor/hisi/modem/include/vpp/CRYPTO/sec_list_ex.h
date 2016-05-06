/******************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_list_ex.h
Version: 1
Author:  Mallesh
Creation Date: 2009-4-24
Description: This file declares the thread safe thread macros and functions
codes

Function List:


History:<author>   <date>          <desc>
              
*********************************************/

#ifndef _SEC_LIST_EX_H
#define _SEC_LIST_EX_H

#include "ipsi_mem.h"
#include "ipsi_types.h"
#include "sec_sys.h"

#include "sec_list.h"

#ifdef   __cplusplus
extern  "C"{
#endif

/**
* @defgroup Thread_safe_list_functions
* This section contains Thread safe Functions
*/

/**
* @defgroup SEC_LIST_firstNode
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_ListNode_S *SEC_LIST_firstNode ( SEC_List_S *list);
* @endcode
*
* @par Purpose
* This function will return the first node in the list.
*
* @par Description
* This function returns the first element of the list.
*
* @param[in] list The list. [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ListNode_S* first element of the list [SEC_ListNode_S*|N/A]
* @retval SEC_ListNode_S* If the first element does not exist [SEC_NULL|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_ListNode_S * SEC_LIST_firstNode (SEC_List_S *list);

/**
* @defgroup SEC_LIST_getData
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_getData ( SEC_ListNode_S *pstNode);
* @endcode
*
* @par Purpose
* To return the data of the passed list node.
*
* @par Description
* This function returns the data of the passed list node.
*
* @param[in] pstNode The node.[N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Data of the passed list node. [SEC_VOID*|N/A]
* @retval SEC_VOID* If the data is not present in the list node. [SEC_NULL|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID * SEC_LIST_getData (SEC_ListNode_S *pstNode);

/**
* @defgroup SEC_LIST_getNextNode
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_getNextNode ( SEC_List_S *pstList,
*                                 SEC_ListNode_S *pstListNode);
* @endcode
*
* @par Purpose
* To advance the current reference pointer by one and return the new 
* current node.
*
* @par Description
* This function advances the current reference pointer by one and returns the 
* new current node. If the current reference pointer is off the list, 
* the new current node will be the first node of the list 
* (unless the list is empty).
*
* @param[in] pstList The list. [N/A]
* @param[in] pstListNode The list node.[N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ListNode_S* Pointer to next element in the list. [SEC_VOID*|N/A]
* @retval SEC_ListNode_S* If the next element does not exist. [SEC_NULL|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_ListNode_S * SEC_LIST_getNextNode (SEC_List_S *pstList,
                                                  SEC_ListNode_S *pstListNode);

/**
* @defgroup SEC_LIST_getPrevNode
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_getPrevNode ( SEC_ListNode_S *pstListNode);
* @endcode
*
* @par Purpose
* To back up the current reference pointer by one and return the new
* current node. 
*
* @par Description
* This function backs up the current reference pointer by one and returns the 
* new current node. 
*
* @param[in] pstListNode The list node.[N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ListNode_S* Pointer to the previous element in the list 
* [SEC_VOID*|N/A]
* @retval SEC_ListNode_S* If the previous element does not exist[SEC_NULL|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_ListNode_S * SEC_LIST_getPrevNode (SEC_ListNode_S *pstListNode);


/**
* @defgroup SEC_LIST_getIndexNode_ex
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_VOID * SEC_LIST_getIndexNode_ex( SEC_UINT32 ulIndex,
*                                        SEC_ListNode_S *pstListNode,
*                                        SEC_List_S* pstList);
* @endcode
*
* @par Purpose
* To return the data of the node at the given index in the list, starting at 0.
*
* @par Description
* This function returns the data of the node at the given index in the list, 
* starting at 0.
*
* @param[in] pstList The list. [N/A]
* @param[in] pstListNode The list node.[N/A]
* @param[in] ulIndex The index in the list. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* The element which was found. [SEC_VOID *|N/A]
* @retval SEC_VOID* If none found. [SEC_NULL|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID * SEC_LIST_getIndexNode_ex(SEC_UINT32 ulIndex,
                                          SEC_ListNode_S *pstListNode,
                                          SEC_List_S* pstList);

/**
* @defgroup SEC_LIST_deleteNode
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_VOID SEC_LIST_deleteNode( SEC_List_S *pstList, 
*              SEC_ListNode_S *pstListNode,
*              PFUNC_FREE pfFreeFunc);
* @endcode
*
* @par Purpose
* It will delete the matching input node from the input list.
*
* @par Description
* This function deletes the matching input node from the input list.
*
* @param[in] pstList The list. [N/A]
* @param[in] pstListNode The current reference node.[N/A]
* @param[in] pfFreeFunc The pointer to the free function
* of data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Void This does not return any value. [N/A|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID SEC_LIST_deleteNode(SEC_List_S *pstList, 
               SEC_ListNode_S *pstListNode,
               PFUNC_FREE pfFreeFunc);


/**
* @defgroup SEC_LIST_detachNode
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_VOID SEC_LIST_detachNode ( SEC_List_S *pstList,
*             SEC_ListNode_S *pstListNode);
* @endcode
*
* @par Purpose
* It will detach the matching input node from the input list,
* and it will free the current node, but not frees the data 
* contained in the current node. 
*
* @par Description
* This function detaches the matching input node from the input list.
* The node will be freed but, the data contained in the 
* node will not be freed, and also the pList->first, pList->curr, 
* and pList->last will be appropriately updated. If the matching node
* is the last node, then pList->curr will point to its previous node 
* after detachment, else it will point to its next node.
*
* @param[in] pstList The list. [N/A]
* @param[in] pstListNode The list node.[N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value. [N/A|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/ 
CRYPTOLINKDLL SEC_VOID SEC_LIST_detachNode (SEC_List_S *pstList,
              SEC_ListNode_S **pstListNode);


/**
* @defgroup SEC_listCopy_Ex
* @ingroup Thread_safe_list_functions
* @par Prototype
* @code
* SEC_List_S* SEC_listCopy_Ex(SEC_List_S* pSrcList,
*                   PFUNC_DUP pFuncCpy,
*                   PFUNC_FREE pfFreeFunc);
* @endcode
*
* @par Purpose
* To dup a list by copying the list by creating a copy of the list
* and to return the destinaton list pointer.
*
* @par Description
* This function dups a list by copying the list by creating a copy of list
* and returns the destinaton list pointer.
*
* @param[in] pSrcList The list [N/A]
* @param[in] pFuncCpy The dup function for the data in the node [N/A]
* @param[in] pfFreeFunc The pointer to the free function for the data in the node
* of data [N/A]
* @param[out] N/A N/A [N/A]
*
*
* @retval SEC_List_S* The duplicated List pointer [SEC_List_S*|N/A]
* @retval SEC_List_S* If dup failed or memory allocation fails.[SEC_NULL|N/A]
*
* @par Dependency
* sec_list_ex.h
* 
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_List_S* SEC_listCopy_Ex(SEC_List_S* pSrcList,
                    PFUNC_DUP pFuncCpy,
                    PFUNC_FREE pfFreeFunc);


/* Declares and initializes the current reference node in case of single list*/
#define SEC_LIST_ITERATOR \
        SEC_ListNode_S *pstRefNode = SEC_NULL;

/* gets the first element in case of single list*/
#define SEC_LIST_GET_FIRST_EX(pList) \
        ((pList)?((NULL != (pstRefNode=SEC_LIST_firstNode(pList)))?\
            SEC_LIST_getData(pstRefNode):SEC_NULL):(SEC_NULL))

/* gets the next element in case of single list*/
#define SEC_LIST_GET_NEXT_EX(pList) \
((pList) ?((NULL != (pstRefNode = SEC_LIST_getNextNode(pList,pstRefNode)))? \
    SEC_LIST_getData(pstRefNode):SEC_NULL):(SEC_NULL))

/* Deletes the current element in case of single list*/
#define SEC_LIST_DELETE_CURRENT_EX(pList,pFreeFunc) \
        SEC_LIST_deleteNode(pList,pstRefNode,pFreeFunc)

/* Detaches the current element in case of single list*/
#define SEC_LIST_DETACH_CURRENT_EX(pList) \
        SEC_LIST_detachNode(pList,&pstRefNode)

/* Gives the current element in case of single list*/
#define SEC_LIST_GET_CURRENT_EX(pList) \
        ((pList) ? (SEC_LIST_getData(pstRefNode)):(SEC_NULL))

/* Declares and initializes the current reference node in case of multiple 
 list*/
#define SEC_LIST_VAR_ITERATOR(pList) \
        SEC_ListNode_S *pstRefNode##_##pList = SEC_NULL

/* gets the first element in case of multiple list*/
#define SEC_LIST_VAR_GET_FIRST_EX(pList) \
        ((pList)?((NULL != (pstRefNode##_##pList=SEC_LIST_firstNode(pList)))?\
            SEC_LIST_getData(pstRefNode##_##pList):SEC_NULL):(SEC_NULL))

/* gets the next element in case of multiple list*/
#define SEC_LIST_VAR_GET_NEXT_EX(pList) \
        ((pList) ?((NULL != (pstRefNode##_##pList \
        = SEC_LIST_getNextNode(pList,pstRefNode##_##pList)))? \
            SEC_LIST_getData(pstRefNode##_##pList):SEC_NULL):(SEC_NULL))

/* Deletes the current element in case of multiple list*/
#define SEC_LIST_VAR_DELETE_CURRENT_EX(pList,pFreeFunc) \
        SEC_LIST_deleteNode(pList,pstRefNode##_##pList,pFreeFunc)

/* Detaches the current element in case of multiple list*/
#define SEC_LIST_VAR_DETACH_CURRENT_EX(pList) \
        SEC_LIST_detachNode(pList,&pstRefNode##_##pList)

/* Gives the current element in case of multiple list*/
#define SEC_LIST_VAR_GET_CURRENT_EX(pList) \
        ((pList) ? (SEC_LIST_getData(pstRefNode##_##pList)):(SEC_NULL))

/* checks if current node is the last one in case of multiple list*/
#define SEC_LIST_VAR_IS_END_EX(pList) \
((pList)? (SEC_NULL == pstRefNode##_##pList): 0)

/*Get the index of the element in the list in case of single list */
#define SEC_LIST_GET_ELEMENT_EX(ulIndex,pList)  \
    SEC_LIST_getIndexNode_ex(ulIndex,pstRefNode,pList)


/*Get the index of the element in the list in case of single list */
#define SEC_LIST_VAR_GET_ELEMENT_EX(ulIndex,pList)  \
    SEC_LIST_getIndexNode_ex(ulIndex,pstRefNode##_##pList,pList)

/* checks if current node is the last one in case of single list*/
#define SEC_LIST_IS_END_EX(pList) \
((pList)? (SEC_NULL == pstRefNode): 0)

#ifdef    __cplusplus
}
#endif /* end of __cplusplus */

#endif /*_SEC_LIST_EX_H*/


