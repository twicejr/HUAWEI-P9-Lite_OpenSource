/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              radixprivate.h
*
*  Project Code: VISPV100R005
*   Module Name: Radix  
*  Date Created: 2001-5-6
*        Author: Prashant Bajpai
*   Description: Private header file for the Radix library to be
*                  included in the Radix code file for compialtion.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2001-5-6  Prashant Bajpai    Creat the first version.
*  2006-4-27 wang xin(03278)    根据编程规范，对文件进行规范化整理
*******************************************************************************/
 
#ifdef _cplusplus
extern "C"
{
#endif

#ifndef _RADIXPRIVATE_H_
#define _RADIXPRIVATE_H_

/* MACRO Mininmum Mask/Maximun Mask/Prefix */
#define VOS_RDX_MAXMASK          0xffffffff
#define VOS_RDX_MINMASK          0x00000000
#define VOS_RDX_DEFADDR          0x00000000
#define VOS_RDX_MAXMASK_LEN      32

#define VOS_RDX_RNBBY            8
#define VOS_RDX_RNSHIFT          3
#define VOS_RDX_MAXADDRLEN       0x20

#define VOS_RDX_BIT(x)           (0x80 >> ((x) & (VOS_RDX_RNBBY-1)))
#define VOS_RDX_BYTE(x)          ((x) >> VOS_RDX_RNSHIFT)
#define VOS_RDX_MAXKEYBITS       (VOS_RDX_MAXADDRLEN * VOS_RDX_RNBBY)
#define VOS_RDX_MAXDEPTH         (VOS_RDX_MAXKEYBITS + 1)
#define VOS_RDX_MIN(a, b)        ((a) < (b) ? (a) : (b))
#define VOS_RDX_BIT_TEST(f, b)   ((f) & (b))

#define VOS_RDX_GETMASK(ulAddr, ulMask)                             \
{                                                                   \
    ULONG ulCounter = 0;                                            \
    if (ulAddr == VOS_RDX_DEFADDR)                                  \
    {                                                               \
        ulMask = VOS_RDX_MINMASK;                                   \
    }                                                               \
    else                                                            \
    {                                                               \
        do                                                          \
        {                                                           \
            ulMask |= (0xff000000 >> ( VOS_RDX_RNBBY * ulCounter)); \
            ulCounter++;                                            \
        }                                                           \
        while ((ulAddr & ulMask) != ulAddr);                        \
    }                                                               \
}


/* Prototypes for Internal functions common to both Address/Mask and ULONG search. */
ULONG VOS_RADIX_MaskToPrefixInet_H (ULONG ulMaskInput, UCHAR *pucMaskLen);
ULONG VOS_RDX_AddListNode_H (ULONG ulModuleID, VOID *pstExtNode, SLL_S *pstList); 
ULONG VOS_RDX_DeleteList_H (SLL_S *ppstListHead);
VOID VOS_RDX_Free_H (VOID *pNodeToFree);

/* Prototypes for Internal functions for Address serach. */
BOOL_T VOS_RDX_MatchAddress_H (ULONG ulAddr, ULONG ulMask, ULONG ulDstAddr);
ULONG VOS_RDX_BuildList_H (ULONG ulModuleID, VOS_RDX_INTNODE_S *pstRootHead, SLL_S *pstList);

/* Removed by xuxiaofei on Sep 10th, 2002.
   After adjusting the scaning order to middle->left->right, VOS_RDX_GetFirst_H()
   is not useful any longer because we don't treat 0.0.0.0/0 specially. */


/* Removed by xuxiaofei on Sep 10th, 2002.
   After adjusting the scaning order to middle->left->right, VOS_RDX_GetFirst_H()
   is not useful any longer because we don't treat 0.0.0.0/0 specially. */

/* Prototypes for Internal functions for ULONG Key serach. */
ULONG VOS_RDX_KeyIntNodeAlloc_H (ULONG ulModuleID, CHAR chTaskName[4], VOS_RDX_KEY_INTNODE_S **ppstRadixNode);
VOID  VOS_RDX_DeleteTree_H (VOS_RDX_KEY_INTNODE_S **ppstRootNode);
ULONG VOS_RDX_BulidScanList_H (ULONG ulModuleID, VOS_RDX_KEY_INTNODE_S  *pstRootNode, SLL_S *pstList); 

#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

