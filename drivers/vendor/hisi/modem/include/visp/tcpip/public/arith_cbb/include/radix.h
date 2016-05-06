/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              radix.h
*
*  Project Code: VISPV100R005
*   Module Name: Radix 
*  Date Created: 2001-5-6
*        Author: Prashant Bajpai
*   Description: Header file for the Radix library to be included
*                for using the Radix API's.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2001-5-6  Prashant Bajpai    Creat the first version.
*  2006-4-27 wang xin(03278)    根据编程规范，对文件进行规范化整理
*  2006-5-10 Luyao              Adjust for ARM CPU
*******************************************************************************/

#ifdef _cplusplus
extern "C"
{
#endif

#ifndef _RADIX_H_
#define _RADIX_H_

/*****************************************************************************
*                                                                            *
*                             MACRO DEFINITIONS                              *
*                                                                            *
*****************************************************************************/

/* MACRO for closest search. */
#define VOS_RDX_WALK_UP                 1
#define VOS_RDX_WALK_DOWN               2

/* RADIX TREE OPERATION ERROR CODES */
#define VOS_RDX_ERR_MEMORY              2
#define VOS_RDX_ERR_INVALIDLIST         3
#define VOS_RDX_ERR_INVALIDPARAMETER    4
#define VOS_RDX_ERR_INVALIDMASK         5
#define VOS_RDX_ERR_ADDEXISTINGADDR     6
#define VOS_RDX_ERR_WAITLIST            7
#define VOS_RDX_ERR_DELETENODE          8
#define VOS_RDX_ERR_SEARCHFAILURE       9
#define VOS_RDX_ERR_INVALIDEXTNODE      10
#define VOS_RDX_ERR_INVALIDTREEROOT     11
#define VOS_RDX_ERR_INVALIDINTNODE      12
#define VOS_RDX_ERR_INVALIDDIRETION     13
#define VOS_RDX_ERR_PARENTNOTFOUND      14
#define VOS_RDX_ERR_SCANLISTCREATE      15
#define VOS_RDX_ERR_DELETETREE          16
#define VOS_RDX_ERR_ADDEXISTINGKEY      17
#define VOS_RDX_ENDOFTREE               18


/*****************************************************************************
*                                                                            *
*                       STRUCTURE DEFINITIONS                                *
*                                                                            *
*****************************************************************************/

struct tagVOS_RDX_EXTNODE;
struct tagVOS_RDX_KEY_EXTNODE;



/* Radix Tree Internal node structure for Address/mask search. */
typedef struct tagVOS_RDX_INTNODE
{
    struct  tagVOS_RDX_INTNODE   *pstLeft;      /* Left Child */
    struct  tagVOS_RDX_INTNODE   *pstRight;     /* RightChild */
    struct  tagVOS_RDX_INTNODE   *pstParent;    /* Parent */
    struct  tagVOS_RDX_EXTNODE   *pstExternal;  /* Pointer to external node */
    UCHAR   ucBitlen;                           /* Node mask length */
    UCHAR   ucTestbyte;                         /* Byte to test */
    UCHAR   ucTestbit;                          /* Test bit within tbyte */
    UCHAR   ucPadding; 
} VOS_RDX_INTNODE_S;




/* Radix Tree External node structure for Address/Mask search. */
typedef struct tagVOS_RDX_EXTNODE
{
    ULONG               ulAddr;         /* Address to be stored */
    ULONG               ulMask;         /* Mask to be stored */
    VOS_RDX_INTNODE_S  *pstIntNode;     /* Pointer to the Internal Node */
    UINTPTR         ulHandle;       /* Handle to the user data */
} VOS_RDX_EXTNODE_S;





/* Radix Tree Internal node structure for ULONG search. */
typedef struct tagVOS_RDX_KEY_INTNODE
{
    struct  tagVOS_RDX_KEY_INTNODE *pstLeft;      /* Left Child */
    struct  tagVOS_RDX_KEY_INTNODE *pstRight;     /* RightChild */
    struct  tagVOS_RDX_KEY_INTNODE *pstParent;    /* Parent */
    struct  tagVOS_RDX_KEY_EXTNODE *pstExternal;  /* Pointer to external node */
    UCHAR   ucBitlen;                             /* Node mask length */
    UCHAR   ucTestbyte;                           /* Byte containing test bit */
    UCHAR   ucTestbit;                            /* Bit to be tested */
    UCHAR   ucPadding; 
} VOS_RDX_KEY_INTNODE_S;






/* Radix Tree External node structure for ULONG Key search. */
typedef struct tagVOS_RDX_KEY_EXTNODE
{
    ULONG                   ulSearchKey;    /* Search key */
    VOS_RDX_KEY_INTNODE_S  *pstIntNode;     /* Pointer to the Internal node */
    UINTPTR             ulHandle;       /* Handle to the user data */
} VOS_RDX_KEY_EXTNODE_S;







/*****************************************************************************
*                                                                            *
*                        FUNCTION PROTOTYPES                                 *
*                                                                            *
*****************************************************************************/


/* Prototypes of the API'S provided by Radix tree for Address/Mask search */
/****************************************************************************
*    Func Name: VOS_RDX_AddNode()
*  Description: Add a radix tree external node containing address and mask as well
*               as user-specific information to a particular radix tree specified by the
*               root node.
*        Input: ULONG ulModuleID:模块号
*               VOS_RDX_INTNODE_S **ppstRootNode:Root node of the tree. 
*               VOS_RDX_EXTNODE_S **ppstExtNode:External node to be added containing
*                   the address and mask as well as the user-specific information. 
*       Output: VOS_RDX_INTNODE_S **ppstRootNode:The root node may be changed due to
*                   the newly added external node. 
*               VOS_RDX_EXTNODE_S **ppstExtNode:The internal node address is supposed
*                   to be set after adding.
*       Return: 无
*      Caution: The root node may be changed due to the newly added external node
*               if a split node is required between the existing root node and the new
*               external node. That's why its double pointer.
*        
*               VOS_RDX_AddNode() is key function since it is called
*               many many times during routes addition. It is making sense to code this
*               function smarter and more neat 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_AddNode (ULONG ulModuleID, VOS_RDX_INTNODE_S **ppstRootNode, VOS_RDX_EXTNODE_S **ppstExtNode);
/****************************************************************************
*    Func Name: VOS_RDX_DeleteNode()
*  Description: Delete the specified external node from the radix tree. Owing to
*               external node deletion, a part of the tree structure maybe adjusted. Owing
*               to tree structure adjustment partly, the root node maybe adjusted 
*               accordingly.
*        Input: VOS_RDX_INTNODE_S **ppstRootNode:Root node of the tree
*               VOS_RDX_EXTNODE_S **ppstDelExtNode:External node to be deleted
*       Output: VOS_RDX_EXTNODE_S **ppstRootNode:Adjusted root node of the tree
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_INVALIDPARAMETER:无效参数
*               VOS_RDX_ERR_DELETENODE:删除节点错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_DeleteNode (VOS_RDX_INTNODE_S **ppstRootNode, VOS_RDX_EXTNODE_S **ppstDelExtNode);
/****************************************************************************
*    Func Name: VOS_RDX_SearchExact()
*  Description: Searches the Radix tree for an exact match and equates the
*               external node pointer provided by the caller to an external 
*               information node if an exact match is found else equates
*               the external node pointer to NULL.
*        Input: VOS_RDX_INTNODE_S  *pstRootNode:Rootnode of the tree.
*               ULONG ulDstAddr:Destination Address. 
*               ULONG ulMask:Mask
*       Output: VOS_RDX_EXTNODE_S **ppstExtNode:Searched external node
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_SearchExact (VOS_RDX_EXTNODE_S **ppstRetExtNode, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulDstAddr, ULONG ulMask);
/****************************************************************************
*    Func Name: VOS_RDX_SearchExactNoMask()
*  Description: Searches the Radix tree for an exact match if a net mask is 
*               not available and equates the external node pointer provided by
*               the caller to an external information node if an exact match 
*               is found else equates the external node pointer to NULL.
*        Input: VOS_RDX_INTNODE_S  *pstRootNode:Rootnode of the tree.
*               ULONG ulDstAddr:Destination Address.  
*       Output: VOS_RDX_EXTNODE_S **ppstExtNode:Searched external node.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_SearchExactNoMask (VOS_RDX_EXTNODE_S **ppstRetExtNode, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulDstAddr);
/****************************************************************************
*    Func Name: VOS_RDX_SearchBest()
*  Description: Searches the Radix tree for the best match and returns a
*               pointer to external node for the best match for the given
*               destination.
*        Input: VOS_RDX_INTNODE_S *pstRootNode:Rootnode of the tree.
*               ULONG ulAddr:Destination Address.  
*               ULONG ulMask:Mask 
*       Output: VOS_RDX_EXTNODE_S **ppstExtNode:Searched internal node.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_SearchBest (VOS_RDX_EXTNODE_S **ppstRetExtNode, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulDstAddr, ULONG ulDstMask);
/****************************************************************************
*    Func Name: VOS_RDX_SearchBestNoMask()
*  Description: Searches the Radix tree for the best match if we donot have 
*               a mask and returns a pointer to external node for the best
*               match for the given destination.
*        Input: VOS_RDX_INTNODE_S *pstRootNode:Rootnode of the tree.
*               ULONG ulDstAddr:Destination Address.  
*       Output: VOS_RDX_EXTNODE_S **ppstExtNode:Searched internal node.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_SearchBestNoMask (VOS_RDX_EXTNODE_S **ppstRetExtNode, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulDstAddr);
/****************************************************************************
*    Func Name: VOS_RDX_SearchClosest()
*  Description: Searches the 'closest' route matching a given destination.
*               Mode is VOS_RDX_WALK_UP for a less specific route
*               VOS_RDX_WALK_DOWN for a more specific route.
*        Input: VOS_RDX_INTNODE_S *pstRootNode:Rootnode of the tree.
*               ULONG ulAddr:Destination Address.  
*               ULONG ulMask:Mask 
*               UCHAR ucDirection:VOS_RDX_WALK_UP   : Less specific 
*                                 VOS_RDX_WALK_DOWN : More specific
*       Output: VOS_RDX_INTNODE_S **ppstIntNode:Searched internal node.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDINTNODE:无效INTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_INVALIDDIRETION:无效方向
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_SearchClosest (VOS_RDX_INTNODE_S **ppstRetIntNode, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulDstAddr, ULONG ulMask, UCHAR ucDirection);
/****************************************************************************
*    Func Name: VOS_RDX_GetFirstPreOrder()
*  Description: Get the first external node from a particular tree in an order of
*               middle->left->right. If there is 0.0.0.0/0, it is attached to the root
*               node and will be the answer.
*        Input: VOS_RDX_INTNODE_S *pstRootNode:Root node of the radix tree.
*       Output: VOS_RDX_EXTNODE_S **ppstExtNode:External node in the toppest 
*                                 level of the tree.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDPARAMETER:无效参数
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetFirstPreOrder (VOS_RDX_INTNODE_S *pstRootNode, VOS_RDX_EXTNODE_S **ppstRetExtNode);
/****************************************************************************
*    Func Name: VOS_RDX_GetNextPreOrder()
*  Description: Get the external node next to the current one in the order of middle
*                     ->left->right.
*        Input: VOS_RDX_EXTNODE_S *pstCurrExtNode:Current external node.
*       Output: VOS_RDX_EXTNODE_S **ppstNextExtNode:Next external node in the 
*                                 order of middle->left->right.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDPARAMETER:无效参数
*               VOS_RDX_ENDOFTREE:Radix树结束
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetNextPreOrder (VOS_RDX_EXTNODE_S *pstCurrExtNode, VOS_RDX_EXTNODE_S **ppstNextExtNode);

/* functions VOS_RDX_GetFirstClassfulNode & VOS_RDX_GetNextClassfulNode
   rely on RM_LIB, removed by Terry, 2003/07/24 */

/****************************************************************************
*    Func Name: VOS_RDX_GetParent()
*  Description: Gets the parent for the given Address/Mask. 
*        Input: VOS_RDX_EXTNODE_S **ppstExtNode:Root of the tree
*               ULONG ulAddr:Address
*               ULONG ulMask:Mask 
*       Output: VOS_RDX_INTNODE_S *pstRootNode:Output node
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_INVALIDDIRETION:无效方向
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetParent (VOS_RDX_EXTNODE_S **ppstExtNode, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulAddr, ULONG ulMask);
/****************************************************************************
*    Func Name: VOS_RDX_GetChildNodes()
*  Description: Get the children of the network specified by the address. The
*               caller does not have to allocate memory for the head of the list.
*               The mask is optional and should be set to zero if not specified. 
*        Input: ULONG ulModuleID:模块号
*               VOS_RDX_INTNODE_S *pstRootNode:Root of the tree
*               ULONG ulAddr:Address
*               ULONG ulMask:Mask (optional)
*       Output: SLL_S **ppstChldLst:Output SLL of all child nodes
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_INVALIDLIST:无效LIST
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetChildNodes (ULONG ulModuleID, SLL_S **pstChldLst, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulAddr, ULONG ulMask);
/****************************************************************************
*    Func Name: VOS_RDX_ScanTree()
*  Description: Traverses the Radix tree and creates a linked list containing
*               pointers to all the external information nodes in the Radix 
*               tree and returns the pointer to the head of the scan list,
*               to the caller.The list is a singly linked list containing  
*               a handle which is a poinmter to the external node.
*        Input: ULONG ulModuleID:模块号
*                     VOS_RDX_INTNODE_S *pstRootNode:Root of the tree. 
*       Output: SLL_S **ppstScanList:Head of the created list.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_SCANLISTCREATE:扫描表创建错误
*               VOS_RDX_ERR_INVALIDLIST:无效LIST
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_ScanTree (ULONG ulModuleID, VOS_RDX_INTNODE_S *pstRootNode, SLL_S **ppstRetListHead);
/****************************************************************************
*    Func Name: VOS_RDX_DeleteAll()
*  Description: Delete the whole Radix tree and makes the rootnode NULL.
*        Input: VOS_RDX_INTNODE_S **ppstRootNode:Rootnode of the tree. 
*       Output: 无
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_DELETETREE:树删除错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_DeleteAll (VOS_RDX_INTNODE_S **ppstRootNode);
/****************************************************************************
*    Func Name: VOS_RDX_GetParentList()
*  Description: Gets the list of all the parents for a given address.The output
*               list does not contain the extnode corresponding to the given ip 
*               address.
*        Input: ULONG ulModuleID:模块号
*                     VOS_RDX_INTNODE_S *pstRootNode:Rootnode of the tree.
*                     ULONG ulAddr:Destination Address.  
*       Output: SLL_S **ppstParentList:Searched internal node.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDINTNODE:无效INTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_INVALIDDIRETION:无效方向
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetParentList (ULONG ulModuleID, SLL_S **ppstParentList, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulAddr);

/****************************************************************************
*    Func Name: VOS_RDX_GetFirstMidOrder()
*  Description: Get the first external node from a particular tree in an order of
*               left->middle->right. 
*        Input: VOS_RDX_INTNODE_S *pstRootNode:Root node of the radix tree.
*       Output: VOS_RDX_EXTNODE_S **ppstExtNode:External node returned
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetFirstMidOrder (VOS_RDX_INTNODE_S *pstRootNode, VOS_RDX_EXTNODE_S **ppstExtNode);
/****************************************************************************
*    Func Name: VOS_RDX_GetNextMidOrder()
*  Description: Get the external node next to the current one in the order of 
*               left->middle->right.
*        Input: VOS_RDX_EXTNODE_S *pstPrevExtNode:Current external node.
*       Output: VOS_RDX_EXTNODE_S **ppstRetExtNode:Next external node in the 
*                   order of left->middle->right.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetNextMidOrder (VOS_RDX_EXTNODE_S *pstPrevExtNode, VOS_RDX_EXTNODE_S **ppstRetExtNode);
/****************************************************************************
*    Func Name: VOS_RDX_GetParentListWithMask()
*  Description: VOS_RDX_GetParentList takes only ulAddr and gives the parentlist
*               But for some modules (e.g., RIP) parent list is needed based on 
*               address and mask to consider cases like
*               
*               Two routes in radix 10.0.0.0/8, 10.0.0.0/16 (zero subnet)
*               To get the parent list of 10.0.0.0/16, we need to even pass
*               mask.                    
*               This API even gives the exact seach node in the 
*               parent list
*        Input: ULONG ulModuleId:(MID_APP | SID_APP_RADIX) of the caller
*               SLL_S **ppstParentList:
*               VOS_RDX_INTNODE_S *pstRootNode:Rootnode of the tree.
*               ULONG ulAddr:Route network address.
*               ULONG ulMask:Route mask
*       Output: SLL_S **ppstParentList:Searched internal node.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_PARENTNOTFOUND:未找到父节点
*      Caution: 
 *------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_GetParentListWithMask (ULONG ulModuleId, SLL_S **ppstParentList, VOS_RDX_INTNODE_S *pstRootNode, ULONG ulAddr, ULONG ulMask);

/****************************************************************************
*    Func Name: VOS_RDX_SearchKeyNode()
*  Description: Searches the Radix tree for an exact match for the key 
*               and equates the pointer provided by the caller to an extenal
*               information node of the tree contaning the details of the key. 
*        Input: VOS_RDX_KEY_INTNODE_S  *pstRootNode:Rootnode of the tree.
*               ULONG ulKey:key
*       Output: VOS_RDX_KEY_EXTNODE_S **ppstExtNode:Node be find. 
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDEXTNODE:无效EXTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_SearchKeyNode (VOS_RDX_KEY_EXTNODE_S **ppstRetExtNode, VOS_RDX_KEY_INTNODE_S  *pstRootNode, ULONG ulKey);
/****************************************************************************
*    Func Name: VOS_RDX_ScanKeyTree()
*  Description: Traverses the Radix tree and creates a linked list containing
*               pointers to all the external information nodes in the Radix 
*               tree and returns the pointer to the head of the scan list,
*               to the caller.The list is a singly linked list containing  
*               a handle which is a poinmter to the external node.
*        Input: ULONG ulModuleID:模块号
*               VOS_RDX_KEY_INTNODE_S *pstRootNode:Root of the tree.
*       Output: SLL_S **ppstScanList:Head of the created list.
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_INVALIDLIST:无效链表
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_SCANLISTCREATE:扫描表创建失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_ScanKeyTree (ULONG ulModuleID, VOS_RDX_KEY_INTNODE_S *pstRootNode, SLL_S **ppstRetListHead);
/****************************************************************************
*    Func Name: VOS_RDX_DeleteTree()
*  Description: Delete the whole Radix tree and makes the rootnode NULL.
*        Input: VOS_RDX_KEY_INTNODE_S **ppstRootNode:
*       Output: 无
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_MEMORY:内存错误
*               VOS_RDX_ERR_SEARCHFAILURE:查找失败
*               VOS_RDX_ERR_INVALIDMASK:无效MASK
*               VOS_RDX_ERR_INVALIDINTNODE:无效INTNODE
*               VOS_RDX_ERR_INVALIDTREEROOT:无效TREEROOT 
*               VOS_RDX_ERR_INVALIDDIRETION:无效方向
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_DeleteTree (VOS_RDX_KEY_INTNODE_S **ppstRootNode);

/****************************************************************************
*    Func Name: VOS_RDX_DeleteScanList()
*  Description: 删除扫描表
*        Input: SLL_S *pstList:待删除的表
*       Output: 无
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_INVALIDLIST:无效表
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_DeleteScanList (SLL_S *pstScanList);
/****************************************************************************
*    Func Name: VOS_RDX_DeleteKeyScanList()
*  Description: 删除key扫描表
*        Input: SLL_S *pstList:待删除的表
*       Output: 
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_INVALIDLIST:无效表
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_DeleteKeyScanList (SLL_S *pstScanList);
/****************************************************************************
*    Func Name: VOS_RDX_DeleteList()
*  Description: 删除表
*        Input: SLL_S *pstList:待删除的表
*       Output: 
*       Return: VOS_OK:成功
*               VOS_RDX_ERR_INVALIDLIST:无效表
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2001-5-6  Prashant B         Create the first version.
*
*******************************************************************************/
ULONG VOS_RDX_DeleteList (SLL_S *pstScanList);

#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

