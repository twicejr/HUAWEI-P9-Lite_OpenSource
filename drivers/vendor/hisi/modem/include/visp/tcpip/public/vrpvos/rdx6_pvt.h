/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              rdx6_pvt.h
*
*  Project Code: VISP1.5
*   Module Name: Radix6  
*  Date Created: 2003-06-17
*        Author: Vinoo
*   Description: Contains helper function declarartions used by the Radix algorithm implementation for IPV6
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-6-17   Vinoo            Creat the first version.
*  2006-4-28   w60006501        adjust format
*******************************************************************************/

#ifdef _cplusplus
extern "C"
{
#endif

#ifndef _RDX6HFUNCS_H_
#define _RDX6HFUNCS_H_


#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/vos_err.h" 

#include "vos/vospubh/wlst_inc.h"
#include "vos/vospubh/vos_id.h"



#define VOS_IPV6_ADDRESS_BIT_LEN            128
#define VOS_IPV6_ADDRESS_LEN                16
#define VOS_IPV6_ADDRESS_WORD_LEN           4



/*TBD - note that the values for these #defines need to be defined later*/

#define VOS_RDX6_MID                500
    
#define VOS_RDX6_RTWALK_UP          0
#define VOS_RDX6_RTWALK_DOWN        1


#define VOS_RDX6_LIST_SUCCESS   VOS_OK
#define VOS_RDX6_MATCHSUCCESS   VOS_OK
#define VOS_RDX6_MATCHFAILURE   VOS_ERR

#define VOS_RDX6_RNBBY            8
#define VOS_RDX6_MAXADDRLEN       128

#define VOS_RDX6_MAXKEYBITS   (VOS_RDX6_MAXADDRLEN * VOS_RDX6_RNBBY)
#define VOS_RDX6_MAXDEPTH     (VOS_RDX6_MAXKEYBITS + 1)
 

/* 
 * pDest and pSrc must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pDest and pSrc is equal
 *      0 -- pDest and pSrc isn't equal
 */
#define VOS_IPV6_IS_ADDRESS_EQUAL( pDest, pSrc )      \
    ( ((pDest)[0] == (pSrc)[0]) \
     && ((pDest)[1] == (pSrc)[1]) \
     && ((pDest)[2] == (pSrc)[2]) \
     && ((pDest)[3] == (pSrc)[3]) )




ULONG VOS_RDX6_MatchAddress_H (ULONG *paulAddr,
                               ULONG ulPrefixLength,
                               ULONG *paulDstAddr);

ULONG VOS_RDX6_AddListNode_H (ULONG ulModuleID,
                              VOID *pstExtNode,
                              SLL_S *pstList);

ULONG VOS_RDX6_BuildList_H (ULONG ulModuleID, 
                            VOS_RDX6_INTNODE_S *pstRootNode,
                            SLL_S *pstList);

VOID VOS_RDX6_Free_H (VOID *pNodeToFree);


#endif /* end of _RDX6HFUNCS_H_ */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


