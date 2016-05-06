/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              IDnsc_inc.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_DNSC_INC_H_
#define _I_DNSC_INC_H_

struct hostent;

DECLARE_INTERFACE(IIF_COMP_DNSC_ComIntFUN) 
{
    IUNKNOWN_METHODS
    METHOD_( struct hostent *,pfDns_GetHost)(CHAR *pName,LONG laddrtype, ULONG ulPolicy);
    METHOD_( ULONG, pfDNS_SetServerAddr)(ULONG ulNoFlag, ULONG ulAddr); 
    METHOD_( ULONG, pfDNS_SetDomainSuffix)(ULONG ulNoFlag, CHAR  *pszDomainName ,ULONG  ulDomainNameFlag);
};


#endif  /* _I_DNS_INC_H_  */
#ifdef  __cplusplus
}
#endif

