/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Idns.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2004-03-12
*        Author: Zhang Hongyan(19316)
*   Description: Defines Component ID, and All Interface IDs for
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-03-12  Zhang Hongyan(19316)         Creat the first version.
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_DNS_H_
#define _I_DNS_H_
#include "tcpip/dnsc/include/idnsc_inc.h"
/*用于DNS的信号量*/
extern ULONG g_ulSemForDNSC;

DECLARE_INTERFACE(IIF_COMP_DNSC_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfDNS_InitCom)(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
    METHOD_(ULONG, pfDNS_ActivateCom)();
    METHOD_(ULONG, pfDNS_SedModuleInfo)(DNS_MOD_INFO_S  *pstMInfo);
    METHOD_(ULONG, pfDNS_QueryEnable)(ULONG ulNOFlag);
    METHOD_(ULONG, pfDNS_SetServer)(SetServer_S * stSetServer);
    METHOD_(ULONG, pfDNS_GetServerList)(DomainInfo_S *pstDomainInfo);
    METHOD_(ULONG, pfDNS_SetDomainSuffix)(ULONG  ulNoFlag , CHAR  szDomainName[DNS_DOMAIN_LIST_NAME_LENGTH + 1] ,ULONG  ulDomainNameFlag);
    METHOD_(ULONG, pfDNS_GetDomainList)(DomainInfo_S *pstDomainInfo);
    METHOD_(ULONG, pfDNS_OpenDynamicHostTbl)(UINTPTR *ulDnsCacheHandle,WAITLIST_GETNEXTFUNC pfGetNextFunc);
    METHOD_(ULONG, pfDNS_CloseDynamicHostTbl)(UINTPTR ulDnsCacheHandle);
    METHOD_(DNS_CACHE_S *,pfDNS_GetDynamicHostFirst)(UINTPTR ulDnsCacheHandle);
    METHOD_(ULONG, pfDNS_GetDynamicHostNext)(UINTPTR ulDnsCacheHandle,DNS_CACHE_S **ppstDnsCache);
    METHOD_(ULONG, pfDNS_ClearDynamicHost)( ULONG ulProtocolFlag);
    METHOD_(VOID , pfDNS_Sock_TimeCallBack)();
    METHOD_(ULONG, pfDNS_SetDebugSwitch)( ULONG ulswitch );
    METHOD_(ULONG, pfDNS_GetDebugSwitch)( ULONG *pulswitch );

    METHOD_(ULONG, pfDNS_SetTos)(UCHAR ucTos);
    METHOD_(ULONG, pfDNS_GetTos)(UCHAR *pucTos);
};


DECLARE_INTERFACE(IIF_COMP_DNSC_ComIntSSA)
{
    IUNKNOWN_METHODS
    METHOD_( ULONG, pfDNS_RegShellApi)(DNSC_CALLBACK_SET_S *pstDnsCallBack);
    METHOD_( ULONG, pfDNS_RegisterIcCallbacks)(tagDNS_SendICDebugInfo pstDnsCallBack);
};


ULONG DNSC_Res_Init(ULONG ulTaskID);
VOID DNSC_Res_Free(ULONG ulTaskID);

#endif  /*  _I_PP4_H_  */


#ifdef  __cplusplus
}
#endif

