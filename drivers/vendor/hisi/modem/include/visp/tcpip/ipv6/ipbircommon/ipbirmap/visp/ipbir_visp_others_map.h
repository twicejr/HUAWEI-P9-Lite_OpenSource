/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_others_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific miscellaneous macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related other macros
************************************************************************/

#ifndef _IPBIR_VISP_OTHERS_MAPP_H_
#define _IPBIR_VISP_OTHERS_MAPP_H_

#ifdef    __cplusplus
extern "C"{
#endif

#include "common/visp/VISP_IR_PPmng.h"
//#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"  /*Changed by wan, 2007-09-24*/
#include "tcpip/ipv6/ip6_pub2.h"

extern BOOL_T VRPAdapt_ETHARP_ETHVLAN_HaveVid( VOID *pstIfNet);
extern ULONG VRPAdapt_PING6_PING_Register(VOID* pstICMP6Callback);
extern ULONG VRPAdapt_PPP_IP6_Check_LinkLocalAddr(VOID* pstIpv6Addr);
extern ULONG Que_EnQueue(MBUF_S* pMBuf);

ULONG VRPAdapt_GetIPInputQueID();
ULONG IP6_Addr_GetIfnetIndex(IN6ADDR_S stAddr, USHORT usVrfIndex);
ULONG IP6_Addr_GetLinkMtu (VOID *pstIfnet, ULONG *pulMtu);
ULONG IP6_Addr_IFA_IfWithBestPrefix(SOCKADDR_IN6_S *pstSockIn6Addr,
                                       VOID *pstIfnet, IN6ADDR_S **ppstAddrOut);
ULONG IP6_Addr_SelectSourceAddr(const IN6ADDR_S *pstIp6DestAddr,
                                IN6ADDR_S *pstSrcAddr, ULONG ulIfIndex, ULONG ulVrfIndex);

ULONG IP6_Addr_IsLocalAddr(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);
ULONG IP6_ICMP6_IncrementStatistics(ULONG ulIfIndex,
                                    ICMP6STATFIELD efield, UCHAR ucType);
VOID IP6_ICMP6_Error(MBUF_S *pstMBuf, UCHAR ucType, UCHAR ucCode, LONG lParam);
IN6ADDR_S * IP6_ICMP6_SelectSrcAddr(const IN6ADDR_S *pstDstAddr,
                                              IN6ADDR_S *pstSrcAddr,
                                              USHORT usVrfIndex);
LONG IP6_ICMP6_CtlOutput(LONG lOper, UINTPTR ulSockId, LONG lLevel,
                     LONG lOptName, MBUF_S **ppMPtr);
UCHAR IP6_ND_GetHopLimit (VOID);
BOOL_T IP6_ND_IsNodeHost(VOID);



#define IPB_IR_ETHARP_VLAN_HAVEID(pstIfNet) \
    VRPAdapt_ETHARP_ETHVLAN_HaveVid(pstIfNet)

#define IPB_IR_ETHER_MAP_IP6_MULTICAST(ipaddr, enaddr) \
{ \
    (enaddr)[0] = 0x33; \
    (enaddr)[1] = 0x33; \
    (enaddr)[2] = ((UCHAR *)ipaddr)[12]; \
    (enaddr)[3] = ((UCHAR *)ipaddr)[13]; \
    (enaddr)[4] = ((UCHAR *)ipaddr)[14]; \
    (enaddr)[5] = ((UCHAR *)ipaddr)[15]; \
}

/* Mod End Reason : Compilation change   Mod:Bharath */
#define IPB_IR_PING6_REGISTER(stICMP6Callback)\
    VRPAdapt_PING6_PING_Register(&stICMP6Callback)

#define IPB_IR_PPP_IP6_CHECK_LINKLOCAL_ADDR(pstIpv6Addr) \
    VRPAdapt_PPP_IP6_Check_LinkLocalAddr(pstIpv6Addr)

/*==ADDR module==*/
#define IPB_IR_IP6_ADDR_GETIFNETINDEX(pstIn6Addr, usVrfIndex)  \
    IP6_Addr_GetIfnetIndex((*pstIn6Addr),usVrfIndex)

#define IPB_IR_IP6_ADDR_IFA_IFWITHBESTPREFIX(pstSockIn6Addr, pstIfnet, ppstIn6AddrOut)   \
    IP6_Addr_IFA_IfWithBestPrefix(pstSockIn6Addr, pstIfnet, ppstIn6AddrOut)

#define IPB_IR_IP6_ADDR_GETLINKMTU(pstIf, pulMtu)  \
    IP6_Addr_GetLinkMtu(pstIf,pulMtu)

#define IPB_IR_IP6_ADDR_ISLOCALADDR(pstIn6Addr, usVrfIndex)  \
    IP6_Addr_IsLocalAddr((VOID *)pstIn6Addr,usVrfIndex)


/*==ICMP6 module==*/
#define IPB_IR_IP6_ICMP6_INCREMENTSTAT(ulIfIndex, efield, ucType)  \
    IP6_ICMP6_IncrementStatistics(ulIfIndex,efield,ucType)

#define IPB_IR_IP6_ICMP6_ERROR(pstMBuf, ucType, ucCode, lParam)  \
    IP6_ICMP6_Error(pstMBuf,ucType,ucCode,lParam)

#define IPB_IR_IP6_ICMP6_SELECTSRCADDR(pstDstIn6Addr, pstSrcIn6Addr, usVrfIndex)  \
    IP6_ICMP6_SelectSrcAddr(pstDstIn6Addr,pstSrcIn6Addr,usVrfIndex)

#define IPB_IR_IP6_ICMP6_CTLOUPUT(lOper, ulSockId, lLevel, lOptName, ppMPtr)  \
    IP6_ICMP6_CtlOutput(lOper,ulSockId,lLevel,lOptName,ppMPtr)

#define IPB_IR_IP6_ADDR_SELECTSRCADDR(pstDstIn6Addr, pstSrcIn6Addr, ulIfIndex, ulVrfIndex) \
    IP6_Addr_SelectSourceAddr(pstDstIn6Addr,pstSrcIn6Addr, ulIfIndex, ulVrfIndex)


/*==ND module==*/ /* Added in IR V1R3 by Arvind for Hop Limit Issue*/
#define IPB_IR_IP6_ND_GET_DEFHOPLIMIT()  \
    IP6_ND_GetHopLimit()

#define IPB_IR_IP6_ND_ISNODEHOST()  \
    IP6_ND_IsNodeHost()


/*For visp has to be 16 */
#define  IP6_MAXADDRNUM_ONEIF    16
#define  IP6_MINADDRNUM_ONEIF    1

#define  IPB_IR_IPV6_ADDR_CHNL_ID 0

/* Added by Saravanya on 16-11-2007 for ND-Host - For Display of addresses on
the interface Maximum No. of Global addresses + Link local address */

#define  IPB_IR_EVENT_PMTUFLUSH    VRP_EVENT_PMTUFLUSH

#define IPB_IR_TCP6_PRODUCT_PREPROCESS_HOOK(ppstMBuf, pulOff, ulProto, pulStat,\
                                                                    pulRet)


/* James: Modified for V1R7 */
#ifdef __cplusplus
}
#endif        /* end of __cplusplus */


#endif  /* end of _IPBIR_VISP_OTHERS_MAPP_H_ */


