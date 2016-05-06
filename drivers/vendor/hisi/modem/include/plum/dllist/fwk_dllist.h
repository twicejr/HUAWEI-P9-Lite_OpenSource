/** ***************************************************************************

                   (C), 2001-2011,

 ******************************************************************************
 * @file
 * @brief
 * Interface for a double linked list library.
 * @author    f73150
 * @author    Frans Roselius
 * @version
 * @date      1990-2011
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/
#ifndef INCLUSION_GUARD_DLLIST_H_
#define INCLUSION_GUARD_DLLIST_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*****************************************************************************
  1 Other files included
*****************************************************************************/

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
#define DLL_ListEntry(ptr, type, member)                \
    ((type *)((char *)(ptr) - offsetof(type, member)))

/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/
#ifndef DLL_NDEBUG

/**
 * Magic values for linked list. Used for debug only.
 */
enum DLL_DEBUG_ENUM
{
    DLL_INITIALIZED = 0xdd00,           /**< Value in a initialized linked lisd. */
    DLL_UNLINKED    = 0xdd01,           /**< Value for a Node that is removed from a list.*/
    DLL_LINKED      = 0xdd02,           /**< Value for a Node that is currently in a list. */
    DLL_DEAD        = 0x5eaddead        /**< Pointer values for a unlinked element. */
};
#endif

/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/

/*****************************************************************************
  5 Message declarations
*****************************************************************************/

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/
struct __DLL_LIST_STRU__ {
    struct __DLL_LIST_STRU__ *pstNext;  /**< Pointer to next element.*/
    struct __DLL_LIST_STRU__ *pstPrev;  /**< Pointer to previous element.*/
#ifndef DLL_NDEBUG
    enum DLL_DEBUG_ENUM enDbg;          /**< Debug element to have better visibility in linked lists.*/
#endif
};


/*****************************************************************************
  7 UNION declarations
*****************************************************************************/

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/
/**
 * Is used as a list head.
 */
typedef struct __DLL_LIST_STRU__ DLL_LIST_STRU;

/**
 * Declare a Node in a Double linked list.
 */
typedef struct __DLL_LIST_STRU__ DLL_NODE_STRU;


/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*lint -sem( DLL_InsertFirst, 2p, custodial(2) )*/
/*lint -sem( DLL_InsertLast, 2p, custodial(2) )*/
/*lint -sem( DLL_InsertBefore, 2p, custodial(2) )*/
/*lint -sem( DLL_InsertAfter, 2p, custodial(2) )*/
/*lint -sem( DLL_IsEmpty, pure )*/
/*lint -sem( DLL_First, pure )*/
/*lint -sem( DLL_Next, pure )*/
/*lint -sem( DLL_Last, pure )*/
/*lint -sem( DLL_Prev, pure )*/
/*lint -sem( DLL_NrElements, pure )*/


/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/**
 * Initilize a linked list.
 *
 * @param[in,out] pstList Pointer to a DLL_LIST_STRU that will be initilized.
 *
 */
void DLL_Init(DLL_LIST_STRU *pstList);

/**
 * Insert a DLL_NODE_STRU at the begining of a DLL_LIST_STRU
 *
 * @note The node is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking on the second parameter. Make sure the the pointer
 * sent really are of the type DLL_NODE_STRU.
 *
 * @param[in] pstList Pointer to a list where the node is to be inserted.
 * @param[in] pstNodeIn Pointer to a node to be inserted to the list.
 */
void DLL_InsertFirst(DLL_LIST_STRU *pstList, void *pstNodeIn);

/**
 * Insert a DLL_NODE_STRU at the end of a DLL_LIST_STRU
 *
 * @note The node is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking on the second parameter. Make sure the the pointer
 * sent really are of the type DLL_NODE_STRU.
 *
 * @param[in] pstList Pointer to a list where the node is to be inserted.
 * @param[in] pstNodeIn Pointer to a node to be inserted to the list.
 */
void DLL_InsertLast(DLL_LIST_STRU *pstList, void *pstNodeIn);

/**
 * Insert a DLL_NODE_STRU before a specified element in a list.
 *
 * @note The node is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking on the second parameter. Make sure the the pointer
 * sent really are of the type DLL_NODE_STRU.
 *
 * @param[in] pstRefIn Pointer to a node in the list.
 * @param[in] pstNodeIn Pointer to a new node that will be inserted before the reference element.
 */
void DLL_InsertBefore(void *pstRefIn, void *pstNodeIn);

/**
 * Insert a DLL_NODE_STRU after a specified element in a list.
 *
 * @note The node is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking on the second parameter. Make sure the the pointer
 * sent really are of the type DLL_NODE_STRU.
 *
 * @param[in] pstRefIn Pointer to a node in the list.
 * @param[in] pstNodeIn Pointer to a new node that will be inserted after the reference element.
 */
void DLL_InsertAfter(void *pstRefIn, void *pstNodeIn);

/**
 * Insert node in a sorted list.
 *
 * @param[in] pstNodeIn Pointer to a new node that will be inserted after the reference element.
 * @param[in] ascending true if the elements should be in ascending order, false if they should
 *                      be desending.
 * @param[in] compare function that compare the two nodes. If the ref node is smaller then Node in
 *                    is returns a negative value if it is bigger it returns a positive value.
 *                    If the two nodes it shall return 0.
 */
void DLL_InsertSorted(DLL_LIST_STRU *pstList,
                      void *pstNodeIn,
                      int ascending,
                      int (*compare)(void *pstRefNode, void *pstNodeIn));

/**
 * Removes a node from a list.
 *
 * @note The node is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking on the second parameter. Make sure the the pointer
 * sent really are of the type DLL_NODE_STRU.
 *
 * @param[in] pstNodeIn Pointer to a node in the list that shall be removed.
 */
void DLL_RemoveNode(void *pstNodeIn);

/**
 * Returns the first element in a list.
 *
 * @note The return value is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking for the return value.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @return Pointer to the first node in the list.
 */
void *DLL_First(DLL_LIST_STRU const *pstList);

/**
 * Returns the next element in a list.
 *
 * @note The return value is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking for the return value.
 *
 * @param[in] pstList Pointer to a list.
 * @param[in] pstNodeIn Pointer to a node in a list.
 *
 * @return Pointer to the next element in the list or NULL if pstNodeIn is the last element.
 */
void *DLL_Next(DLL_LIST_STRU const *pstList, void const *pstNodeIn);

/**
 * Returns the previous element in a list.
 *
 * @note The return value is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking for the return value.
 *
 * @param[in] pstList Pointer to a list.
 * @param[in] pstNodeIn Pointer to a node in a list.
 *
 * @return Pointer to the previous element in the list or NULL if pstNodeIn is the first element.
 */
void *DLL_Prev(DLL_LIST_STRU const *pstList, void const *pstNodeIn);

/**
 * Returns the last element in a list.
 *
 * @note The return value is declared as a void pointer to releax the type checking.
 * This  make it possible to define the node structures in a more free way but it
 * take away all type checking for the return value.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @return Pointer to the last element in the list or NULL if pstNodeIn is the first element.
 */
void *DLL_Last(DLL_LIST_STRU const *pstList);

/**
 * Checks if the list is empty or not.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @return True if the list is empty.
 */
int DLL_IsEmpty(DLL_LIST_STRU const *pstList);

/**
 * Returns number of elements in a list.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @return Number of elements in list.
 */
int DLL_NrElements (DLL_LIST_STRU const *pstList);

/**
 * Traverse a List and call the callback for each element in the list.
 * if the callback returns true it will continue to the next element
 * if the callback returns false it will stop traversing the list.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @param[in] pvExtra Pointer to a traverse object that will ge given
 *                    together with the node to the traveler function.
 *
 * @param[in] traveler Function that will be called for each element
 *                     in the list.  the traveler should return a true
 *                     value to get to the next element in the list.
 *                     If it return zero it will end the journey and
 *                     DLL_Travers will return current element in the
 *                     list.
 *
 * @return The element selected by the traveler or NULL if the
 *         traveler never want to get off the train.
 */
void *DLL_Traverse(DLL_LIST_STRU const *pstList,
                   void *pvExtra,
                   int (*traveler)(void*, void*));

/**
 * Traverse a List from a given node and call the callback for each
 * element in the list. If the callback returns true it will continue
 * to the next element if the callback returns false it will stop
 * traversing the list.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @param[in] pvExtra Pointer to a traverse object that will ge given
 *                    together with the node to the traveler function.
 *
 * @param[in] startNode Starting point for the travel.
 *
 * @param[in] traveler Function that will be called for each element
 *                     in the list.  the traveler should return a true
 *                     value to get to the next element in the list.
 *                     If it return zero it will end the journey and
 *                     DLL_Travers will return current element in the
 *                     list.
 *
 * @return The element selected by the traveler or NULL if the
 *         traveler never want to get off the train.
 */
void *DLL_TraverseFrom(DLL_LIST_STRU const *pstList,
                       void  *startNode,
                       void *pvExtra,
                       int (*traveler)(void*, void*));

/**
 * Traverse a List from start to a given node and call the callback
 * for each element in the list. If the callback returns true it will
 * continue to the next element if the callback returns false it will
 * stop when the element == endNode.
 *
 * @param[in] pstList Pointer to a list.
 *
 * @param[in] pvExtra Pointer to a traverse object that will ge given
 *                    together with the node to the traveler function.
 *
 * @param[in] endNode List will be traversed untill this
 *                    element. treveler will not be called for node ==
 *                    endNode.
 *
 * @param[in] traveler Function that will be called for each element
 *                     in the list.  the traveler should return a true
 *                     value to get to the next element in the list.
 *                     If it return zero it will end the journey and
 *                     DLL_Travers will return current element in the
 *                     list.
 *
 * @return The element selected by the traveler or NULL if the
 *         traveler never want to get off the train.
 */
void *DLL_TraverseTo(DLL_LIST_STRU const *pstList,
                     void  *endNode,
                     void *pvExtra,
                     int (*traveler)(void*, void*));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_DLLIST_H_ */
