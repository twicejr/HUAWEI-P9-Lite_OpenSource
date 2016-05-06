

#ifndef _IPB_IR_IPV6_TAILOR_H
#define _IPB_IR_IPV6_TAILOR_H

#ifdef _cplusplus
extern "C"{
#endif

/* Changed by karthik as part of macro clean-up*/
#define IPB_IR_IPV6_TRANS_NEW_MIB_SUPPORT     VRP_NO

/* Removed by karthik as part of macro clean-up*/
/*#define IPB_IR_IPV6_AVL_TREE_SUPPORT            VRP_YES*/

/* Added by Prabhu H (71185) for MIB Coupling */
#define IPB_IR_VERSION_INDEPENDENT_TRANSPORT_MIB    VRP_NO

/* Reason: Socket6 in VISP has not merged VPNv6 changes,
   so we cant compile our code with socket6, hence defining
   TCP6_VRP_MODULE_IPV6_VPN as VRP_MODULE_IPV6_VPN */
#ifndef VRP_MODULE_IPV6_VPN
#define VRP_MODULE_IPV6_VPN VRP_NO
#endif
#define TCP6_VRP_MODULE_IPV6_VPN   VRP_YES
#define UDP6_VRP_MODULE_IPV6_VPN   VRP_YES
#define RAWIP6_VRP_MODULE_IPV6_VPN VRP_YES

#ifndef VRP_MODULE_RTPRO_BGP
#define VRP_MODULE_RTPRO_BGP VRP_NO
#endif
#define TCP6_VRP_MODULE_RTPRO_BGP VRP_NO

#ifndef VRP_MODULE_MPLS
#define VRP_MODULE_MPLS VRP_NO
#endif
#define TCP6_VRP_MODULE_MPLS VRP_MODULE_MPLS

/* Purify tool applicability in IPv6 Transport modules */
#define IPBIR_IPV6_TRANS_MODULES_PURIFY_TEST    VRP_NO
#define IPBIR_IPV6_TCP6_PURIFY_TEST             VRP_NO
#define IPBIR_IPV6_UDP6_PURIFY_TEST             VRP_NO
#define IPBIR_IPV6_RAWIP6_PURIFY_TEST           VRP_NO

/*Enable calling testability call back on global semaphore lock and unlock*/
#define IPBIR_IPV6_SEM_TEST                     VRP_NO

/* For using Stub framework */
#define IPBIR_USE_PIPE_STUB                     VRP_YES

/* Enable / Disable Pipe Support */
#define IPBIR_IPV6_TRANSPORT_PIPE_SUPPORT       VRP_NO


/* For NULL Pointer Validation related to IN6PCB Callbacks */
#ifndef VRP_MODULE_SEC_IPSEC6
#define VRP_MODULE_SEC_IPSEC6                   VRP_NO
#endif



#define TEST_TCP6_APP                                    VRP_NO



/*Added by guojianjun178934, 删除此宏定义，直接使用vos_id.h中的定义, 2013/12/19   问题单号:20131219_1_Compile */
/* End of Added by guojianjun178934, 2013/12/19   问题单号:20131219_1_Compile */


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* _IPB_IR_IPV6_TAILOR_H */

