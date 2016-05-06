/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_rthdr.h
*
*  Project Code: VISP1.5
*   Module Name: Socket6
*  Date Created: 2003-9-24 
*        Author: Vikas Goel
*   Description: Routr Header Extension related
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-9-24   Vikas Goel       Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/



#ifndef _SOCK6_RTHDR_H_
#define _SOCK6_RTHDR_H_


#ifdef __cplusplus
extern "C" {
#endif

#define SOCK_TEST   0  /* For testing. To be made 0 in the final release */


ULONG  inet6_rth_space(LONG lType, LONG lSeg);
VOID  *inet6_rth_init (VOID *pBp, LONG lBpLen, LONG lType, LONG lSegments);
LONG   inet6_rth_add (VOID *pBp, IN6ADDR_S *pstAddr);
LONG   inet6_rth_reverse (const VOID *pIn, VOID *pOut);
LONG   inet6_rth_segments (const VOID *pBp);

IN6ADDR_S * inet6_rth_getaddr (VOID *pBp, LONG lIdx);

LONG inet6_opt_init (VOID *pExtbuf, ULONG ulExtlen);
LONG inet6_opt_append (VOID *pExtbuf, ULONG ulExtlen, LONG lPrevlen, UCHAR ucType,
                       ULONG ulLen, UCHAR ucAlign, VOID **ppDatabufp);
LONG inet6_opt_finish (VOID *pExtbuf, ULONG ulExtlen, LONG lPrevlen);

LONG inet6_opt_set_val (VOID *pDatabuf, ULONG ulOffset, VOID *pVal, LONG lValLen);
static LONG ip6optlen (UCHAR *pucOpt, UCHAR *pucLim);
LONG inet6_opt_next (VOID *pExtbuf, ULONG ulExtlen, LONG lPrevlen, UCHAR *pucTypep,
                     LONG *pulLenp, VOID **ppDatabufp);

LONG inet6_opt_find (VOID *pExtbuf, ULONG ulExtlen, LONG lPrevlen, UCHAR ucType,
                     ULONG *pulLenp, VOID **ppDatabufp);

LONG inet6_opt_get_val(VOID *pDatabuf, ULONG ulOffset, VOID *pVal, LONG lValLen);


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _SOCK6_RTHDR_H_ */ 

