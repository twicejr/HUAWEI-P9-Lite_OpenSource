
#ifndef _IP6_PMTUFUNC_H
#define _IP6_PMTUFUNC_H

#ifdef  __cplusplus
extern "C"{
#endif

VOID  IP6_PMTU_NotifyMTU (IN6ADDR_S *pstDA, ULONG ulZoneid, ULONG ulMtu);

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
ULONG IP6_PMTU_Notify_PPI(ULONG ulOper, VOID *pvPMTUInfo);
#endif


#ifdef  __cplusplus
}
#endif

#endif

