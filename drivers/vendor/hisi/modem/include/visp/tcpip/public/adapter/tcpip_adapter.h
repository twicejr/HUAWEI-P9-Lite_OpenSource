/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_adapter.h
*
*  Project Code: VISPV100R005
*   Module Name: PUBILC
*  Date Created: 2004-3-8
*        Author: zhang hong yan(19316)
*   Description: VISP的可裁减配置头文件,主要给用户使用，VISP内部代码并不包含此头文件.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-03-08  zhang hong yan(19316)  Creat the first version.
*  2006-04-27  wang xin(03278)     根据编程规范，对文件进行规范化整理
*  2008-03-03  liangjicheng        BC3D01254 删除RTP模块
*******************************************************************************/
/*
  说明：
      1.若产品代码中没有Dopra组件机制，请将宏TCPIP_COMP_INITIAL定义为VRP_YES；否则，将其定义为VRP_NO。
      2.若产品要应用模块X，则将宏TCPIP_COMP_REGISTER_X定义为VRP_YES。否则，将其定义为VRP_NO。
      3.若产品将TCPIP_COMP_REGISTRE_X定义为VRP_YES，则一定要在MakeFile文件中加入对模块X的Lib库的链接。
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TCPIP_ADAPTER_H_
#define _TCPIP_ADAPTER_H_

/*If Dopra1.5B100 or above used, define this macro VRP_NO; Otherwise make it VRP_YES.*/
#define TCPIP_COMP_INITIAL               VRP_NO

/*Macro ONLY for this file.To determine if the component should be registered.*/
#define TCPIP_COMP_REGISTER_ETH          VRP_YES   /*ETHARP*/
#define TCPIP_COMP_REGISTER_PPP          VRP_YES   /*PPP*/
#define TCPIP_COMP_REGISTER_SESSION      VRP_NO   /* DISTRIBUTED IP support for session */
#define TCPIP_COMP_REGISTER_IPV6         VRP_YES    /*IPv6*/
#define TCPIP_COMP_REGISTER_PING         VRP_YES   /*PING*/
#define TCPIP_COMP_REGISTER_DNSC         VRP_NO   /*Dns Client*/
#define TCPIP_COMP_REGISTER_DHCP4C       VRP_YES    /*Dhcp4 Client. no eth,no DHCP4c.*/
#define TCPIP_COMP_REGISTER_ACL4         VRP_YES   /*ACL4*/
#define TCPIP_COMP_REGISTER_ACL6         VRP_YES   /*ACL6*/
#define TCPIP_COMP_REGISTER_ACLFW        VRP_NO   /*ACLFW*/
#define TCPIP_COMP_REGISTER_TRACEROUTE   VRP_NO   /*TraceRout*/
#define TCPIP_COMP_REGISTER_IPHC         VRP_NO    /*IPHC*/
#define TCPIP_COMP_REGISTER_PPPOECLIENT  VRP_YES    /*PPPoE Client*/
#define TCPIP_COMP_REGISTER_MP           VRP_YES    /*Multilink Protocol*/
#define TCPIP_COMP_REGISTER_PPPMUX       VRP_YES    /*PPPMUX*/
#define TCPIP_COMP_REGISTER_TCP4         VRP_YES   /*Tcp4*/
#define TCPIP_COMP_REGISTER_UDP4         VRP_YES   /*Udp4*/
#define TCPIP_COMP_REGISTER_TRUNK        VRP_YES   /*Trunk*/
#define TCPIP_COMP_REGISTER_POES         VRP_YES    /*POES*/
#define TCPIP_COMP_REGISTER_DHCP4R       VRP_NO    /*Dhcp4 Relay.*/
#define TCPIP_COMP_REGISTER_IPSEC        VRP_NO    /*IPSEC*/
#define TCPIP_COMP_REGISTER_IKEV1        VRP_NO    /*IKEV1*/
#define TCPIP_COMP_REGISTER_IKEV2        VRP_NO    /*IKEV2*/
#define TCPIP_COMP_REGISTER_DHCP6C       VRP_NO    /* DHCP6Client,如果想注册DHCP6C,请同时注册IPV6,否则无效 */
#define TCPIP_COMP_REGISTER_DHCP6R       VRP_NO    /* DHCP6Relay, 如果想注册DHCP6R,请同时注册IPV6,否则无效 */
#define TCPIP_COMP_REGISTER_BFD          VRP_YES   /* BFD裁减宏 */
#define TCPIP_COMP_REGISTER_OSICP        VRP_NO    /* OSICP裁减宏 */
#define TCPIP_COMP_REGISTER_OAM3AH       VRP_YES    /* 3AH裁减宏 */
#define TCPIP_COMP_REGISTER_OAM1AG       VRP_YES    /* 1AG裁减宏 */
#define TCPIP_COMP_REGISTER_IGMP         VRP_NO    /* IGMP裁减宏*/
#define TCPIP_COMP_REGISTER_PTP          VRP_YES    /* PTP(1588v2)协议裁减宏 */
#define TCPIP_COMP_REGISTER_VLAN         VRP_NO    /* VLAN裁减宏*/
#define TCPIP_COMP_REGISTER_IPOA         VRP_NO
#define TCPIP_COMP_REGISTER_VLINK        VRP_NO
#define TCPIP_COMP_REGISTER_DCLBASE      VRP_YES
#define TCPIP_COMP_REGISTER_RIP          VRP_YES   /*RIP可裁剪*/
#define TCPIP_COMP_REGISTER_OSPF         VRP_YES   /*OSPF可裁剪*/
#define TCPIP_COMP_REGISTER_BFDEXT       VRP_NO
#define TCPIP_COMP_REGISTER_RTP          VRP_NO
#define TCPIP_COMP_REGISTER_L2IF         VRP_YES   /* L2IF裁减宏*/
#define TCPIP_COMP_REGISTER_MSTP         VRP_YES   /* MSTP裁减宏*/
#define TCPIP_COMP_REGISTER_VRRP         VRP_YES   /* VRRP裁减宏*/
#define TCPIP_COMP_REGISTER_VRF          VRP_YES   /* VRF裁减宏*/
#define TCPIP_COMP_REGISTER_EAP          VRP_NO   /* EAP裁减宏 */
#define TCPIP_COMP_REGISTER_SYNCE        VRP_NO   /* SyncE裁减宏 */
#define TCPIP_COMP_REGISTER_ARPGUARD     VRP_NO  /* ARP防欺骗裁剪宏 */
#define TCPIP_COMP_REGISTER_LLDP          VRP_NO  /* LLDP裁剪宏 */
#define TCPIP_COMP_REGISTER_TWAMP          VRP_YES   /* TWAMP component registeration */
#define TCPIP_COMP_REGISTER_POLICYRT       VRP_YES  /* source policy route registration */
#define TCPIP_COMP_REGISTER_NSR          VRP_YES   /* NSR特性裁剪宏 */
#define TCPIP_COMP_REGISTER_VRF6          VRP_YES   /* VRF6*/
#define TCPIP_COMP_REGISTER_ATK          VRP_YES    /*ATK*/

#endif /*_TCPIP_ADAPTER_H_*/

#ifdef __cplusplus
}
#endif

