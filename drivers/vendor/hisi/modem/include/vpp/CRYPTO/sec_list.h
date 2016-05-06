/*
                                                                              
                Copyright 2003, Huawei Technologies Co. Ltd.                  
                            ALL RIGHTS RESERVED                               
                                                                              
------------------------------------------------------------------------------
                                                                              
                              sec_list.h                                      
                                                                              
  Project Code: SeCert                                                        
   Module Name: Common Module                                                 
  Date Created: 2005-07-05                                                    
        Author: Sanjay Vasudevan                                              
   Description: Contains typedefs,macros,and function definitions of list     
                module.  These functions are used to create,traverse,          
                manipulate, destroy the SEC_AsnList_S structure.  All          
                operations are available as macros.  The list consists of a    
                head node and multiple list nodes.  The list nodes contain the 
                pointer to the data element.                                   
                                                                              
*/

#ifndef _SEC_LIST_H
#define _SEC_LIST_H

#include "sec_sys.h"

#include "ipsi_mem.h"
#include "ipsi_types.h"


#ifdef   __cplusplus
extern  "C"{
#endif

/** @defgroup sec_list
* This section contains the sec_list Structures and Functions
*/

/** @defgroup sec_listEnum
* @ingroup sec_list
* This section contains the sec_list Enum.
*/

/** @defgroup sec_listStructures
* @ingroup sec_list
* This section contains the sec_list Structures.
*/


/* for handling ASN.1 SET OF type */
/**
* @defgroup SEC_ListNode_S
* @ingroup sec_listStructures
* @par Prototype
* @code
* typedef struct stSEC_ListNode
* {
*    struct stSEC_ListNode *prev;
*    struct stSEC_ListNode *next;
*    void                  *data;
* } SEC_ListNode_S;
* @endcode
*
* @datastruct prev The previous node in the list.
* @datastruct next The next node in the list.
* @datastruct data This must be the last field of this structure.
*/
typedef struct stSEC_ListNode
{
    struct stSEC_ListNode   *prev;  /* The previous node in the list*/
    struct stSEC_ListNode   *next;  /*The next node in the list*/
    void        *data;      /* This must be the last field of this structure  */
} SEC_ListNode_S;

/**
* @defgroup SEC_List_S
* @ingroup sec_listStructures
* @par Prototype
* @code
* typedef struct stSEC_List
* {
*    SEC_ListNode_S *first;
*    SEC_ListNode_S *last;
*    SEC_ListNode_S *curr;
*    int            count;
*    int            dataSize;
* } SEC_List_S;
* @endcode
*
* @datastruct first The first node in the list.
* @datastruct last The last node in the list.
* @datastruct curr The current node in the list.
* @datastruct count Number of elements in list.
* @datastruct dataSize Space required in each node for the data.
*/

typedef struct stSEC_List
{
    SEC_ListNode_S *first;  /*The first node in the list*/
    SEC_ListNode_S *last;   /*The last node in the list*/
    SEC_ListNode_S *curr;   /*The current node in the list*/
    int            count;       /* Number of elements in list               */
    int            dataSize;    /* Space required in each node for the data */
} SEC_List_S;


typedef SEC_List_S AsnList;
typedef SEC_ListNode_S AsnListNode;
/* the enum for specifying whether to add the element before/after the
  current element.  It is used in SEC_LIST_AddElement()
 */


typedef enum enSEC_Position
{
    LIST_POS_BEFORE,  /*Indication to to add the element before the current element*/
    LIST_POS_AFTER,   /*Indication to to add the element after the current element*/
    LIST_POS_BEGIN,   /*Indication to to add the element at the beginning of the list*/
    LIST_POS_END
} SEC_Position_E;


/**
* @defgroup PFUNC_CMP
* @ingroup Function Pointer
* @par Description
* This is a pointer to the list comparison function used in SEC_LIST_search function.
* It takes two pointers and compares them based
* on a criteria.  If the two are equal a zero is returned.  If the first
* should preceed the second, a negative is returned.  Else a positive value
* is returned.
* @par Prototype
* @code
* typedef SEC_INT32 (* PFUNC_CMP) (const void *,const void *);
* @endcode
*
*/
typedef SEC_INT32 (* PFUNC_CMP) (const void *,const void *);

/**
* @defgroup PFUNC_FREE
* @ingroup Function Pointer
* @par Description
* This is a pointer to the free function.
* The free function takes a pointer to data structure to be freed and must return void.
* @par Prototype
* @code
* typedef void (* PFUNC_FREE) (void *);
* @endcode
*
*/
typedef void (* PFUNC_FREE) (void *);


/**
* @defgroup PFUNC_DUP
* @ingroup Function Pointer
* @par Description
* This is a pointer to the Copy function.
* The copy function takes a pointer to data structure to be freed and must return void.
* @par Prototype
* @code
* typedef void* (*PFUNC_DUP) (const void*) ;
* @endcode
*
*/
typedef void* (*PFUNC_DUP) (const void*) ;



/*
  The following macros return the specified element of the list.  They do
  not change the current list pointer.
 */


/* gets the current element */
#define SEC_LIST_CURR_ELMT(pList)  \
    ((pList)? ((pList)->curr?((pList)->curr->data):SEC_NULL):SEC_NULL)

/* gets the next element */
#define SEC_LIST_NEXT_ELMT(pList)  \
    ((pList)? ((pList)->curr?((pList)->curr->next?((pList)->curr->next->data):SEC_NULL):SEC_NULL):SEC_NULL)

/* gets the previous element */
#define SEC_LIST_PREV_ELMT(pList)  \
    ((pList)? ((pList)->curr?((pList)->curr->prev?((pList)->curr->prev->data):SEC_NULL):SEC_NULL):SEC_NULL)


/* gets the last element */
#define SEC_LIST_LAST_ELMT(pList)  \
    ((pList)? ((pList)->last?((pList)->last->data):SEC_NULL):SEC_NULL)

/* gets the first element */
#define SEC_LIST_FIRST_ELMT(pList) \
    ((pList)? ((pList)->first?((pList)->first->data):SEC_NULL):SEC_NULL)

/* checks if the list is empty */
#define SEC_LIST_EMPTY(pList)      \
    ((pList)? ((pList)->count == 0):0)

/* gets the number of nodes in the list */
#define SEC_LIST_COUNT(pList)      \
    ((pList)? ((pList)->count):0)

/* checks if current node is the last one */
#define SEC_LIST_IS_END(pList)      \
    ((pList)? (SEC_NULL == (pList)->curr): 0)

/* checks if current node is the first one */
#define SEC_LIST_IS_START(pList)  \
    (pList? ((pList)->first == (pList)->curr): 0)


/* macros for creating a list,adding an
  element, deletion, traversing searching, sorting
 */

/*create a new list and initialize it*/
#define SEC_LIST_INIT(pList,iDataSize) \
    do  \
    {   \
        if (pList != SEC_NULL && iDataSize >= 0)   \
        {   \
            AsnListInit (pList,iDataSize);  \
        }   \
    }while (0)


/*create a new list and initialize it*/
#define SEC_LIST_NEW(ulSizeMemData) \
    SEC_LIST_new(ulSizeMemData)


/*Get the current element */
#define SEC_LIST_GET_CURRENT(pList) \
    ((pList)?(SEC_LIST_curr(pList)? SEC_LIST_CURR_ELMT( pList) : SEC_NULL):SEC_NULL)


/*Get the next element */
#define SEC_LIST_GET_NEXT(pList) \
    ((pList)?(SEC_LIST_next(pList)? SEC_LIST_CURR_ELMT( pList) : SEC_NULL):SEC_NULL)



/*Get the previous element */
#define SEC_LIST_GET_PREV(pList) \
    ((pList)?(SEC_LIST_prev(pList)? SEC_LIST_CURR_ELMT( pList) : SEC_NULL):SEC_NULL)


/*Get the first element */
#define SEC_LIST_GET_FIRST(pList) \
    ((pList)?(SEC_LIST_first(pList)? SEC_LIST_CURR_ELMT( pList) : SEC_NULL):SEC_NULL)



/*Get the last element */
#define SEC_LIST_GET_LAST(pList) \
    ((pList)?(SEC_LIST_last(pList)? SEC_LIST_CURR_ELMT( pList) : SEC_NULL):SEC_NULL)


/*Get the index of the element in the list  */
#define SEC_LIST_GET_ELEMENT(ulIndex,pList)  \
    SEC_LIST_getIndexNode(ulIndex,pList)


/*Get the index of the element in the list.  pElement should be an address stored
 in one of the list nodes for search to succeed
 */
#define SEC_LIST_GET_ELEMENT_INDEX(pElement,pList)  \
    ((pList && pElement)?(SEC_LIST_getElmtIndex (pElement,pList)):-1)



/*to concatinate two lists into one. pDestlist appended to pSrcList and returns the pDstList*/
#define SEC_LIST_CONCAT(pDstList,pSrcList)  \
    ((pDstList && pSrcList)?(SEC_LIST_concat(pDstList,pSrcList)):SEC_NULL)

/*Sorts the list using qsort.  It deletes the source list after sorting and returns the destination list*/
#define SEC_LIST_SORT(pList,pfCmp)  \
    SEC_LIST_sort(pList,pfCmp)



/*Add an element before/after  the current node*/
#define SEC_LIST_ADD_ELEMENT(pList,pData,enPosition)  \
    SEC_LIST_addElement(pList,pData,enPosition)

/*Add an element before/after  the current node without checking the data pointer*/
#define SEC_LIST_ADD_ELEMENT_EX(pList,pData,enPosition)  \
    SEC_LIST_addElement_ex(pList,pData,enPosition)


/*Delete all the nodes in the list and then frees the header */
#define SEC_LIST_FREE(pList,pFreeFunc)          \
        SEC_LIST_deleteAll(pList, pFreeFunc);   \
        if (SEC_NULL != pList) { ipsi_free(pList); pList = NULL;}



/*Delete all the nodes in the list.  Does not free list header */
#define SEC_LIST_DELETE_ALL(pList,pFreeFunc)        \
    SEC_LIST_deleteAll(pList,pFreeFunc)


/*Delete the current element of list.
 After deletion curr becomes next of the deleted node
 */
#define SEC_LIST_DELETE_CURRENT(pList,pFreeFunc)        \
    SEC_LIST_deleteCurrent(pList,pFreeFunc)


/*Delete all the nodes in the list and then frees the header.
 But it does not delete the data pointers inside the list nodes.
 It is used only after sort to delete the input list to the sort function.
 */
#define SEC_LIST_FREE_AFTER_SORT(pList)         \
    do                                          \
    {                                           \
        SEC_LIST_deleteAllAfterSort(pList);     \
        if (SEC_NULL != pList) { ipsi_free(pList); pList = NULL;}\
    }while (0)


/*to search the list for a particular element */
#define SEC_LIST_SEARCH(pList,pSearchFor,pSearcher)     \
    SEC_LIST_search(pList,pSearchFor,pSearcher)

#define SEC_INT_ERROR (-2)

/*to search the list for a particular element */
#define SEC_LIST_SEARCH_EX(pList,pSearchFor,pSearcher,pstErr)       \
    SEC_LIST_search_Ex(pList,pSearchFor,pSearcher,pstErr)

/*to create a copy of a list.  It returns the pointer of the new list(copy of the original pSrcList)*/
#define SEC_LIST_COPY(pSrcList,pFuncDup, pFuncFree)     \
    SEC_listCopy(pSrcList,pFuncDup, pFuncFree)


/*to create a copy of a list.  It returns the pointer of the new list(copy of the original pSrcList)*/
#define SEC_LIST_COPY_EX(pSrcList,pFuncDup, pFuncFree)      \
    SEC_listCopy_Ex(pSrcList,pFuncDup, pFuncFree)

/** @defgroup sec_listFunctions
* @ingroup sec_list
* This section contains the sec_list Functions
*/





CRYPTOLINKDLL SEC_UINT32 SEC_LIST_addElement (SEC_List_S *pstList, void *pData, SEC_Position_E enPosition);



CRYPTOLINKDLL SEC_UINT32 SEC_LIST_addElement_ex(SEC_List_S *pstList,void *pData,SEC_Position_E enPosition);



/**
* @defgroup SEC_LIST_deleteAll
* @ingroup sec_listFunctions
* @par Prototype
* @code
* void SEC_LIST_deleteAll (SEC_List_S *pstList,
* PFUNC_FREE pfFreeFunc );
* @endcode
*
* @par Purpose
* To delete all the nodes of the list but not to delete the list header.
*
* @par Description
* This function deletes all the nodes of the list but does not delete the list header.
*
* @param[in] pList The list [N/A]
* @param[in] pfFreeFunc The freefunction to free the data pointer in each node [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Void This does not return any value [N/A|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
* Does not free the list header.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL void SEC_LIST_deleteAll (SEC_List_S *pstList, PFUNC_FREE pfFreeFunc);



/**
* @defgroup SEC_LIST_deleteCurrent
* @ingroup sec_listFunctions
* @par Prototype
* @code
* void SEC_LIST_deleteCurrent (SEC_List_S *pstList, PFUNC_FREE pfFreeFunc );
* @endcode
*
* @par Purpose
* To delete the current element of list.
*
* @par Description
* This function deletes the current element of list.
*
* @param[in] pList The list [N/A]
* @param[in] pfFreeFunc The pointer to the free function
* of data [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Void This does not return any value [N/A|N/A]
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

CRYPTOLINKDLL void SEC_LIST_deleteCurrent (SEC_List_S *pstList, PFUNC_FREE pfFreeFunc);


/**
* @defgroup SEC_LIST_detachCurrent
* @ingroup sec_listFunctions
* @par Prototype
* @code
* void SEC_LIST_detachCurrent (SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To detach the current element from the list, and to free the current node, but not too free the
* data contained in the current node.
* 
*
* @par Description
* This function detaches the current element from the list, the current node will be freed, but the data contained
* in the current node will not be freed.Also the pList->first, pList->curr and pList->last will be appropriately
* updated. If the current node is the last node, then pList->curr will point to its previous node after detachment,
* else it will point to its next node.
*
* @param[in] pList The list [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Void This does not return any value [N/A|N/A]
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

CRYPTOLINKDLL void SEC_LIST_detachCurrent (SEC_List_S *pstList);



/**
* @defgroup SEC_LIST_search
* @ingroup sec_listFunctions
* @par Prototype
* @code
* void* SEC_LIST_search (SEC_List_S *pstList, void *pSearchFor, PFUNC_CMP pSearcher );
* @endcode
*
* @par Purpose
* To search a list based on the comparator function supplied (3rd param).
*
* @par Description
* This function searches a list based on the comparator function
* supplied (3rd param). The second param is given to the
* comparator as its second param and each data item on the
* list is given as its first param while searching. The
* comparator must return 0 to indicate a match.
*
* @param[in] pList The list [N/A]
* @param[in] pSearchFor The element to be searched [N/A]
* @param[in] pSearcher The pointer to the comparison function
* of data [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Void* The element which was found [Void*|N/A]
* @retval Void* If none found [SEC_NULL|N/A]
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

CRYPTOLINKDLL void* SEC_LIST_search (SEC_List_S *pstList, void *pSearchFor, PFUNC_CMP pSearcher);


/**
* @defgroup SEC_LIST_search_Ex
* @ingroup sec_listFunctions
* @par Prototype
* @code
* void* SEC_LIST_search_Ex (SEC_List_S *pstList,void *pSearchFor,PFUNC_CMP pSearcher,SEC_INT * pstErr)
* @endcode
*
* @par Purpose
* To search a list based on the comparator function supplied (3rd param).
*
* @par Description
* This function searches a list based on the comparator function
* supplied (3rd param). The second param is given to the
* comparator as its second param and each data item on the
* list is given as its first param while searching. The
* comparator must return 0 to indicate a match.\n
*
*The Search callback function should return -2(SEC_INT_ERROR) if 
* search should not be continued anymore.
*
* @param[in] pList The list. [N/A]
* @param[in] pSearchFor The element to be searched. [N/A]
* @param[in] pSearcher The pointer to the comparison function
* of data. [N/A]
* @param[out] pstErr Error codes for internal error. [-2/0]
*
* @retval Void* The element which was found [Void*|N/A]
* @retval Void* If none found [SEC_NULL|N/A]
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
CRYPTOLINKDLL void* SEC_LIST_search_Ex (SEC_List_S *pstList,void *pSearchFor,
                                     PFUNC_CMP pSearcher,SEC_INT * pstErr);

/**
* @defgroup SEC_LIST_getIndexNode
* @ingroup sec_listFunctions
* @par Prototype
* @code
* void* SEC_LIST_getIndexNode(SEC_UINT32 ulIndex, SEC_List_S* pstList);
* @endcode
*
* @par Purpose
* To return the node at the given index in the list, starting at 0.
*
* @par Description
* This function returns the node at the given index in the list, starting at 0.
*
* @param[in] pList The list [N/A]
* @param[in] ulIndex The index in the list [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Void* The element which was found [Void*|N/A]
* @retval Void* If none found [SEC_NULL|N/A]
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

CRYPTOLINKDLL void* SEC_LIST_getIndexNode(SEC_UINT32 ulIndex,SEC_List_S* pstList);



/**
* @defgroup SEC_listCopy
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_listCopy(SEC_List_S* pSrcList,PFUNC_DUP pFuncCpy,PFUNC_FREE pfFreeFunc);
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
* @retval SEC_List_S* The duplicated List pointer [SEC_List_S*|N/A]
* @retval SEC_List_S* If dup failed or memory allocation fails.[SEC_NULL|N/A]
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

CRYPTOLINKDLL SEC_List_S* SEC_listCopy(SEC_List_S* pSrcList,PFUNC_DUP pFuncCpy,PFUNC_FREE pfFreeFunc);



/**
* @defgroup SEC_LIST_sort
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_LIST_sort(SEC_List_S *pstList, PFUNC_CMP pfCmp);
* @endcode
*
* @par Purpose
* To sort the list using the comparison function provided.
*
* @par Description
* This function sorts the list using the comparison function provided.
*
* @param[in] pList The list [N/A]
* @param[in] pfCmp The comparison function [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* If unsuccessful [SEC_NULL|N/A]
* @retval SEC_List_S* If successful [The destination sorted list|N/A]
*
* @par Dependency
* sec_list.h
* 
* @par Note
* The comparison function function must act on the double pointer
* of the data. Sorts the list using qsort.  It deletes the source
* list after sorting and returns the destination list.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_List_S* SEC_LIST_sort(SEC_List_S *pstList,PFUNC_CMP pfCmp);


/**
* @defgroup SEC_LIST_new
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_List_S *SEC_LIST_new  (SEC_INT dataSize);
* @endcode
*
* @par Purpose
* To create a new list. 
*
* @par Description
* This function is used to create a new list.
*
* @param[in] dataSize Size of the list [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval SEC_List_S* An empty list of the specified size [SEC_List_S*|N/A]
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

CRYPTOLINKDLL SEC_List_S *SEC_LIST_new  (SEC_INT dataSize);

/**
* @defgroup SEC_LIST_curr
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_curr  (SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To return the data of the current element in the list.
*
* @par Description
* This function returns the data of the current element in the list.
*
* @param[in] list Input list [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Data at the current element in the list [SEC_VOID*|N/A]
* @retval SEC_VOID* If the current element does not exist in the list [SEC_NULL|N/A]
* @retval SEC_VOID* If memory allocation fails. [SEC_NULL|N/A]
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
 CRYPTOLINKDLL SEC_VOID *SEC_LIST_curr  (SEC_List_S *pstList);

/**
* @defgroup SEC_LIST_first
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_first (SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To return the data at the first element of the list.
*
* @par Description
* This function returns the data at the first element of the list.
*
* @param[in] list the list [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_VOID* Data at the first element of the list [SEC_VOID*|N/A]
* @retval SEC_VOID* If the first element does not exist [SEC_NULL|N/A]
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

CRYPTOLINKDLL SEC_VOID *SEC_LIST_first (SEC_List_S *pstList);

/**
* @defgroup SEC_LIST_last
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_last (SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To return the data at the last element of the list.
*
* @par Description
* This function returns the data at the last element of the list.
*
* @param[in] list The list [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Data at the last element of the list [SEC_VOID*|N/A]
* @retval SEC_VOID* If the last element does not exist [SEC_NULL|N/A]
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

CRYPTOLINKDLL SEC_VOID *SEC_LIST_last  (SEC_List_S *pstList);

/**
* @defgroup SEC_LIST_next
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_next (SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To advance the current pointer by one and return the data address of the new
* current node.
*
* @par Description
* This function advances the current pointer by one and returns the data address of the new
* current node. If the current pointer is off the list, the new current node
* will be the first node of the list (unless the list is empty).
*
* @param[in] list The list [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Pointer to the next element in the list [SEC_VOID*|N/A]
* @retval SEC_VOID* If the next element does not exist [SEC_NULL|N/A]
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

CRYPTOLINKDLL SEC_VOID *SEC_LIST_next  (SEC_List_S *pstList);

/**
* @defgroup SEC_LIST_prev
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID *SEC_LIST_prev (SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To back up the current pointer by one and return the data address of the new
* current node. 
*
* @par Description
* backs up the current pointer by one and returns the data address of the new
* current node. If the current pointer is off the list, the new current node
* will be the last node of the list (unless the list is empty).
*
* @param[in] list The list [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_VOID* Pointer to the previous element in the list [SEC_VOID*|N/A]
* @retval SEC_VOID* If the previous element does not exist[SEC_NULL|N/A]
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

CRYPTOLINKDLL SEC_VOID *SEC_LIST_prev  (SEC_List_S *pstList);

/**
* @defgroup SEC_LIST_getElmtIndex
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_INT32 SEC_LIST_getElmtIndex  (SEC_VOID *elmt, SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To return the index (starting a 0 for the first element)
* of the given element in the given list.
*
* @par Description
* This function returns the index (starting a 0 for the first element)
* of the given element in the given list.
* Returns -1, if the element is not in the list.
* Assumes that the list node contains a single pointer.
*
* @param[in] elmt The element whose index is to be retrieved [N/A]
* @param[in] list The list to which the element belongs to [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 The index of the specified element in the given list [SEC_INT32|N/A]
* @retval SEC_INT32 If the element is not found in the list [-1|N/A]
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

CRYPTOLINKDLL SEC_INT32 SEC_LIST_getElmtIndex  (SEC_VOID *elmt,SEC_List_S *pstList);

/**
* @defgroup SEC_LIST_concat
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_List_S *SEC_LIST_concat  (SEC_List_S *l1, SEC_List_S *l2);
* @endcode
*
* @par Purpose
* To concatenate list 2 to list 1.
*
* @par Description
* This function is used to concatenate list 2 to list 1.
*
* @param[in] l1 The list to which the 2nd list is to be concatenated to. [N/A]
* @param[in] l2 The list which is to be concatenated. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* The concatenated list. [SEC_List_S*|N/A]
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

CRYPTOLINKDLL SEC_List_S *SEC_LIST_concat  (SEC_List_S *l1, SEC_List_S *l2);

/**
* @defgroup AsnListFree
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID AsnListFree  ( AsnList *pstList );
* @endcode
*
* @par Purpose
* To free the Asn list.
*
* @par Description
* This function is used to  free the Asn list.
*
* @param[in] list Pointer to the Asn list which has to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
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

CRYPTOLINKDLL SEC_VOID AsnListFree  (AsnList *pstList);



/**
* @defgroup SEC_LIST_revList
* @ingroup sec_listFunctions
* @par Prototype
* @code
* SEC_VOID SEC_LIST_revList(SEC_List_S *pstList);
* @endcode
*
* @par Purpose
* To reverse the linked list.
*
* @par Description
* This function is used to  reverse the linked list.
*
* @param[in] pList Pointer to the list which has to be reversed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
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
CRYPTOLINKDLL SEC_VOID SEC_LIST_revList(SEC_List_S *pstList);


#ifdef  __cplusplus
}
#endif /* end of __cplusplus */




#endif /*_SEC_LIST_H*/


