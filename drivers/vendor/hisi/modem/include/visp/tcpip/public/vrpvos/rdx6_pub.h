/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              rdx6_pub.h
*
*  Project Code: VISP1.5
*   Module Name: Radix6  
*  Date Created: 2003-06-17
*        Author: Vinoo
*   Description: Contains prototype definition for the Radix algorithm for IPV6
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-6-17   Vinoo            Creat the first version.
*  2006-4-28   w60006501        adjust format
*  2006-05-10  lu yao(60000758)     为支持ARM CPU字节对齐特性，修改结构。
*  2007-11-28  wangmingxia      modify for A82D21611(同步V1R5C02问题单A82D21450：消除产品编译告警)
*******************************************************************************/

#ifdef _cplusplus
extern "C"
{
#endif

#ifndef _RDX6_H_
#define _RDX6_H_


typedef struct tagVOS_RDX6_INTNODE
{
    struct  tagVOS_RDX6_INTNODE   *pstLeft;             /* Left Child */
    struct  tagVOS_RDX6_INTNODE   *pstRight;            /* Right Child */
    struct  tagVOS_RDX6_INTNODE   *pstParent;           /* Parent */
    struct  tagVOS_RDX6_EXTNODE   *pstExternal;         /* Pointer to external node */
    UCHAR   ucBitlen;                                   /* Node prefix length */
    UCHAR   ucTestbyte;                                 /* Byte to test */
    UCHAR   ucTestbit;                                  /* Test bit within tbyte */
    UCHAR   ucPadding; 
} VOS_RDX6_INTNODE_S;

typedef struct tagVOS_RDX6_EXTNODE
{
    ULONG aulAddr[4];                                   /* Address to be stored */ 
    ULONG ulPrefixLength;                               /* Prefis length*/
    VOS_RDX6_INTNODE_S *pstIntNode;                     /* Pointer to the Internal Node */ 
    UINTPTR ulHandle;                                     /* Handle to the user data */
} VOS_RDX6_EXTNODE_S;


/*Converts a buffer of ulongs in network order to host order */
#define VOS_HTONBUF(pSrc, pDst)\
{\
           (pDst)[0] = VOS_NTOHL((pSrc)[0]);\
           (pDst)[1] = VOS_NTOHL((pSrc)[1]);\
           (pDst)[2] = VOS_NTOHL((pSrc)[2]);\
           (pDst)[3] = VOS_NTOHL((pSrc)[3]);\
}

#define VOS_NTOHBUF(pSrc, pDst)\
{\
           (pDst)[0] = VOS_HTONL((pSrc)[0]);\
           (pDst)[1] = VOS_HTONL((pSrc)[1]);\
           (pDst)[2] = VOS_HTONL((pSrc)[2]);\
           (pDst)[3] = VOS_HTONL((pSrc)[3]);\
}


/*****************************Error Codes*********************************************/

#define RDX6_ERROR_BASE          5000
/* Modify by w60786 for A82D21450 2007-11-20,消除产品编译告警*/
/* typedef enum RDX_ENUM */
enum RDX_ENUM
{
    VOS_RDX6_ERR_INVALIDPARAMETER = RDX6_ERROR_BASE,
    VOS_RDX6_ERR_ADDEXISTINGADDR,
    VOS_RDX6_ERR_MEMORY,
    VOS_RDX6_ERR_DELETENODE,
    VOS_RDX6_ERR_INVALIDTREEROOT,
    VOS_RDX6_ERR_DELETETREE,
    VOS_RDX6_ERR_INVALIDEXTNODE,
    VOS_RDX6_ERR_SEARCHFAILURE,
    VOS_RDX6_ERR_INVALIDINTNODE,
    VOS_RDX6_ERR_INVALIDDIRETION,
    VOS_RDX6_ENDOFTREE,
    VOS_RDX6_ERR_PARENTNOTFOUND,
    VOS_RDX6_ERR_INVALIDLIST,
    VOS_RDX6_ERR_SCANLISTCREATE,
    VOS_RDX6_ERR_INVALIDLISTHEAD
};

/***************************** Error Codes Till Here *********************************************/


/* satya-d02 */

ULONG VOS_RDX6_AddNode (ULONG ulModuleID, 
                        VOS_RDX6_INTNODE_S **ppstRootNode, 
                        VOS_RDX6_EXTNODE_S **ppstExtNode);

ULONG VOS_RDX6_DeleteNode (VOS_RDX6_INTNODE_S **ppstRootNode, 
                           VOS_RDX6_EXTNODE_S **ppstExtNode);

ULONG VOS_RDX6_DeleteAll (VOS_RDX6_INTNODE_S  **ppstRootNode);

ULONG VOS_RDX6_SearchExactNoPrefix (VOS_RDX6_EXTNODE_S   **ppstRetExtNode, 
                                    VOS_RDX6_INTNODE_S    *pstRootNode, 
                                    ULONG  *paulDstAddr,
                                    ULONG   ulMaxLoopNum);

ULONG VOS_RDX6_SearchExact(VOS_RDX6_EXTNODE_S  **ppstRetExtNode,
                           VOS_RDX6_INTNODE_S   *pstRootNode,
                           ULONG  *paulDstAddr,
                           ULONG  ulPrefixLength);

ULONG VOS_RDX6_SearchBest(VOS_RDX6_EXTNODE_S **ppstRetExtNode,
                          VOS_RDX6_INTNODE_S *pstRootNode,
                          ULONG *paulDstAddr,
                          ULONG ulPrefixLength);

ULONG VOS_RDX6_SearchBestNoPrefix (VOS_RDX6_EXTNODE_S **ppstRetExtNode,
                                   VOS_RDX6_INTNODE_S *pstRootNode,
                                   ULONG *paulDstAddr);

ULONG VOS_RDX6_SearchExactNoPrefixNetworkOrder (VOS_RDX6_EXTNODE_S   **ppstRetExtNode, 
                                                VOS_RDX6_INTNODE_S    *pstRootNode, 
                                                ULONG  *paulDstAddrNetworkOrder);

ULONG VOS_RDX6_SearchExactNetworkOrder(VOS_RDX6_EXTNODE_S  **ppstRetExtNode,
                                       VOS_RDX6_INTNODE_S   *pstRootNode,
                                       ULONG  *paulDstAddrNetworkOrder,
                                       ULONG  ulPrefixLength);

ULONG VOS_RDX6_SearchBestNetworkOrder(VOS_RDX6_EXTNODE_S **ppstRetExtNode,
                                      VOS_RDX6_INTNODE_S *pstRootNode,
                                      ULONG *paulDstAddrNetworkOrder,
                                      ULONG ulPrefixLength);

ULONG VOS_RDX6_SearchBestNoPrefixNetworkOrder (VOS_RDX6_EXTNODE_S **ppstRetExtNode,
                                               VOS_RDX6_INTNODE_S *pstRootNode,
                                               ULONG *paulDstAddrNetworkOrder);

ULONG VOS_RDX6_SearchClosest(VOS_RDX6_INTNODE_S **ppstRetIntNode,
                             VOS_RDX6_INTNODE_S *pstRootNode,
                             ULONG    *paulDstAddr,
                             ULONG    ulPrefixLength,
                             USHORT usDirection);

ULONG VOS_RDX6_GetFirst(VOS_RDX6_INTNODE_S  *pstRootNode,
                        VOS_RDX6_EXTNODE_S  **ppstRetExtNode);

ULONG VOS_RDX6_GetNext(VOS_RDX6_EXTNODE_S  *pstExtNode,
                       VOS_RDX6_EXTNODE_S  **ppstRetNxtExtNode);

ULONG VOS_RDX6_GetParent (VOS_RDX6_EXTNODE_S  **ppstExtNode,
                          VOS_RDX6_INTNODE_S  *pstRootNode,
                          ULONG *paulAddr,
                          ULONG ulPrefixLength );

ULONG  VOS_RDX6_ScanTree (ULONG ulModuleID,
                          VOS_RDX6_INTNODE_S *pstRootNode,
                          SLL_S **ppstRetListHead);

ULONG VOS_RDX6_DeleteList (SLL_S *pstScanList);


ULONG VOS_RDX6_GetChildNodes (ULONG ulModuleID, SLL_S **ppstChldLst,
                              VOS_RDX6_INTNODE_S  *ppstRootNode,
                              ULONG *paulAddr,
                              ULONG ulPrefixLength);

ULONG VOS_RDX6_GetParentList (ULONG ulModuleID,
                              SLL_S **ppstParentList,
                              VOS_RDX6_INTNODE_S *pstRootNode,
                              ULONG *paulAddr,
                              ULONG ulPrefixLength);

VOID * VOS_RDX6_WTLSTCB (VOID *pstCurrExtNode, VOID **ppstNextExtNode);

ULONG VOS_RDX6_GetFirstMidOrder (VOS_RDX6_INTNODE_S  *pstRootNode,
                                VOS_RDX6_EXTNODE_S  **ppstRetExtNode);
ULONG VOS_RDX6_GetNextMidOrder (VOS_RDX6_EXTNODE_S  *pstExtNode,
                                VOS_RDX6_EXTNODE_S  **ppstRetNxtExtNode);
ULONG VOS_RDX6_GetFirstPostOrder (VOS_RDX6_INTNODE_S  *pstRootNode,
                                VOS_RDX6_EXTNODE_S  **ppstRetExtNode);
ULONG VOS_RDX6_GetNextPostOrder (VOS_RDX6_EXTNODE_S  *pstExtNode,
                                VOS_RDX6_EXTNODE_S  **ppstRetNxtExtNode);



#endif /* end of _RDX6_H_ */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

