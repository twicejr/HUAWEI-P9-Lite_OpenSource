/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                            if_sh_ipv6.h
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2003/12/23
 *        Author: Sachin
 *   Description: To avoid direct call to different component functions , 
                  shell functions are moved to ifnet
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2003/12/23      Sachin          Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/
#ifndef _IF_SH_IPV6_H_
#define _IF_SH_IPV6_H_

#ifdef  __cplusplus
extern "C"{
#endif
 
VOID IP6_ND_SH_PhyUpDownNotify(IFNET_S *pIf,ULONG ulCmd,CHAR * pData);

VOID IP6_ND_SH_ShutDownNotify(ULONG ulIfIndex);

VOID IP6_ND_SH_UpDownNotify(IFNET_S *pIf,ULONG ulCmd,CHAR * pData);

VOID IP6_SH_ND_LLAddrNotify(IFNET_S *pstIf, CHAR * pData );

ULONG IP6_SH_ND_GetVlinkStatus();

ULONG IP6_Addr_SH_PhyUpDownNotify(IFNET_S *pstIf, ULONG ulCmd, CHAR *pcData);

ULONG IP6_Addr_SH_LLC_Notify(IFNET_S *pstIf, ULONG ulCmd, CHAR *pcData);

ULONG IP6_SH_IF_Attach( IFNET_S *pstIf );

ULONG IP6_SH_IF_Detach( IFNET_S *pstIf );

VOID IP6_SH_IF_GetIPv6ComIntVtbl();
ULONG IP6_SH_Addr_IF_HaveIp6Addr(IFNET_S * pstIf);

/* Added by fengjing physical地址发生改变，不下发DOWN */
#define IP6_IS_MAC_CHANGE       1
#define IP6_IS_NOT_MAC_CHANGE   0

extern ULONG g_ulMacChangedIpv6Statewitch;

#ifdef  __cplusplus
}
#endif

#endif

