

#ifndef _IPB_IR_IPV6BASIC_TAILOR_H
#define _IPB_IR_IPV6BASIC_TAILOR_H

#ifdef _cplusplus
extern "C"{
#endif

#define IPB_IR_IPV6_MODULE_IND                      VRP_NO

#define IP6_BASIC_IPOS_IC_LOG_ENABLE                VRP_YES

#define IP6_BASIC_IPOS_IC_DBG_ENABLE                VRP_YES



/* Purify tool applicability in IPv6 Basic modules */
#define IPBIR_IPV6_BASIC_MODULES_PURIFY_TEST        VRP_NO
#define IPBIR_IPV6_ND_PURIFY_TEST                   VRP_NO
#define IPBIR_IPV6_ADDR_PURIFY_TEST                 VRP_NO
#define IPBIR_IPV6_ICMP6_PURIFY_TEST                VRP_NO
#define IPBIR_IPV6_PMTU_PURIFY_TEST                 VRP_NO

/*Enable calling testability call back on global semaphore lock and unlock*/
#define IPBIR_IPV6_SEM_TEST                     VRP_NO

/* WVRP Router, 8070 Router, VISP Router the macro should be set to VRP_NO
   VISP Host the macro should be set to VRP_YES */
/*Enable IPv6 NDHOST feature*/
#ifdef NDHOST /* NDHOST */
#define IP6_NDHOST                              VRP_YES
#else
#define IP6_NDHOST                              VRP_NO
#endif /* NDHOST */
#define IP6_NDHOST_FORWARD_PATH_DEBUG           VRP_NO

#define IPBIR_IPV6_NP_SUPPORT                     VRP_YES

#ifdef VRP_MODULE_BEMINI
#define VRP_MODULE_MINI        VRP_YES
#else
#define VRP_MODULE_MINI        VRP_NO
#endif


#ifndef VRP_MODULE_IPV6_ATM
#define VRP_MODULE_IPV6_ATM     VRP_NO
#endif

#ifndef VRP_MODULE_IPV6_FR
#define VRP_MODULE_IPV6_FR      VRP_NO
#endif

#ifndef VRP_MODULE_IPV6_SUPPORT_DAD_ON_ATM
#define VRP_MODULE_IPV6_SUPPORT_DAD_ON_ATM      VRP_NO
#endif

#ifndef VRP_MODULE_IPV6_SUPPORT_DAD_ON_FR
#define VRP_MODULE_IPV6_SUPPORT_DAD_ON_FR       VRP_NO
#endif

#ifndef VRP_MODULE_IPV6_TUNNEL
#define VRP_MODULE_IPV6_TUNNEL      VRP_NO
#endif


#define IPBIR_IPV6_VLANIF_SUPPORT                                 VRP_NO
#define IPBIR_IPV6_VLANIF_PROXY_SUPPORT                     VRP_NO




#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* _IPB_IR_IPV6BASIC_TAILOR_H */
