/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_cfg.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 此文件主要负责DNS的数据配置
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/

#ifndef _DNS_CFG_H_
#define _DNS_CFG_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif
extern ULONG  DNS_QueryEnable(ULONG ulNoFlag);
extern ULONG  DNS_Core_SetServer(SetServer_S *pstSetServer);
extern ULONG  DNS_SetServer(SetServer_S *pstSetServer);
extern ULONG  DNS_GetServerList(DomainInfo_S *pstDomainInfo);
extern ULONG  DNS_Core_SetDomainSuffix(ULONG  ulNoFlag , CHAR  szDomainName[DNS_DOMAIN_LIST_NAME_LENGTH + 1] ,ULONG  ulDomainNameFlag);
extern ULONG  DNS_SetDomainSuffix(ULONG  ulNoFlag , CHAR  szDomainName[DNS_DOMAIN_LIST_NAME_LENGTH + 1] ,ULONG  ulDomainNameFlag);
extern ULONG  DNS_GetDomainList(DomainInfo_S *pstDomainInfo);
extern ULONG  DNS_ClearDynamicHost(ULONG ulProtocolFlag);
extern ULONG  DNS_OpenDynamicHostTbl(UINTPTR *ulDnsCacheHandle,WAITLIST_GETNEXTFUNC pfGetNextFunc);
extern ULONG  DNS_CloseDynamicHostTbl(UINTPTR ulDnsCacheHandle);
extern DNS_CACHE_S*  DNS_GetDynamicHostFirst(UINTPTR ulDnsCacheHandle);
extern ULONG   DNS_GetDynamicHostNext(UINTPTR ulDnsCacheHandle,DNS_CACHE_S **ppstDnsCache);
extern ULONG  DNS_Core_SetServerAddr(ULONG ulNoFlag, ULONG ulServerIp);
extern ULONG  DNS_SetServerAddr(ULONG ulNoFlag, ULONG ulServerIp);

extern ULONG DNS_SetDebugSwitch(ULONG ulswitch);
extern ULONG DNS_GetDebugSwitch(ULONG *pulswitch);

extern struct hostent *DNSC_GetHost_PT(CHAR *pName,LONG laddrtype, ULONG ulPolicy);
extern ULONG   DNS_ClearDynamicHost_PT(ULONG ulProtocolFlag);
extern DNS_CACHE_S* DNS_GetDynamicHostFirst_PT(UINTPTR ulDnsCacheHandle);
extern ULONG DNS_GetDynamicHostNext_PT(UINTPTR ulDnsCacheHandle,DNS_CACHE_S **ppstDnsCache);

extern ULONG DNS_SetTos(UCHAR ucTos);
extern ULONG DNS_GetTos(UCHAR *pucTos);

extern ULONG DNS_SetCompatibleSwitch(ULONG ulSwitch);
extern ULONG DNS_GetCompatibleSwitch(ULONG *pulSwitch);

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif


#endif 

