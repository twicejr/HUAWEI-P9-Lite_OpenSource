/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_config.h
*
*  Project Code: VISPV1R5
*   Module Name: Public
*  Date Created: 2004-05-28
*        Author: X36317
*   Description: 定义VISP使用的全局宏
*                这个头文件为VISP定义了所有系统级别的宏
*                这些系统级别的宏可以分为两种类别：开关和常数
*                可以通过调整这些开关和常数来配置VISP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-05-28   Liqiang17164            Create
*  2004-11-15   VISP Team               Redefine all Macro
*  2008-11-11   liangjicheng            BC3D00605 编译选项修改
*******************************************************************************/

#ifndef _TCPIP_CONFIG_H_
#define _TCPIP_CONFIG_H_

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef TCPIP_FORBALONG
#include "dopra_def.h"
#endif

#ifdef TCPIP_DOPRA_V2
#include "vos_typdef.h"
#endif

#include "tcpip_id.h"

/*************************************************************************

              以下是VISP在数通产品和非数通产品都必须提供的宏

**************************************************************************/

/************************************************************************************************
 * 注意版本号编码规则, 从质量部获取具体规则, 如果规则发生变化, 需要相应地修改HA版本号的生成方式
 * 正式版本号格式为 "VISP VxxxRxxxCxxBxxx" 或 "VISP VxxxRxxxCxxBxxxSPCxxx";
 * Draft版本号格式为 "VISP VxxxRxxxCxxBxxxDraftX”或 "VISP VxxxRxxxCxxBxxxSPCxxxDraftX"，
 * 其中x,X均为阿拉伯数字，英文字母区分大小写。
 ************************************************************************************************/
#define TCPIP_HA_VERSION "VISP V100R008C06SPC001B001" 
#define DOPRA_VISP_VERSION "DOPRA IP V300R002C30SPC070" 


/* VISP的HA修订号,  基于同一个R/C版本, R/C版本号发生变化后又从1重新开始编号 */
/* B018 -> B021 (0 -> 1) 首次协商未通过新增备份 */
/* B013 -> B015 (1 -> 2) 同步V1R7C01B039有PPP新增备份 */
/* B020 -> B021 (3 -> 4) B021版本新增tlv备份 */
/* B020 -> B021 (3 -> 4) B021版本新增ifnet tlv备份 */
/* B021 -> B022 (4 -> 5) B022版本新增1AG tlv备份 */
/* B022 -> B023 (5 -> 6) SPC020B001版本新增physical地址备份 */
/* B022 -> B023 (5 -> 6) SPC020B001版本新增PPP TLV备份 */
/* SPC010 -> SPC020 (6 -> 7) SPC020版本新增Public TLV备份 */
/* SPC010 -> SPC020 (6 -> 7) SPC020版本新增DHCP指定出接口使能备份 */
/* SPC500 版本新增TRUNK端口备份及LACP增强备份 */
/* SPC330 (9 -> 10)版本新增ARP老化时间离散全局变量备份 */
/* SPC330 (10 -> 11)版本新增ARP表象VLAN ID字段备份 */
#define VISP_HA_UPDATE 11


/******************************************************************************
 * 下面两个宏定义了“开”和“关”两个状态，直接继承VRP的相关宏。
 * 例如：
 *        #define TCPIP_IN_VRP           VRP_YES
 *        #define VRP_DISTRIBUTED        VRP_NO
 * 表示VISP放入VRPV5之中，VISP不是分布式方式应用，这样，VISP系统在编译时，
 * 就可以拆掉相关代码。
 * 需要注意的是有些意义上互斥的一对宏，不能被同时置为“VRP_YES”或“VRP_NO”，
 * 注意，请不要修改这两个宏的值。
 ******************************************************************************/
#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif

/******************************************************************************
 * Lib小型化，裁减HA宏
******************************************************************************/

#ifdef TCPIP_MODULE_BEMINI
#define TCPIP_MODULE_MINI        VRP_YES
#else
#define TCPIP_MODULE_MINI        VRP_NO
#endif

#ifndef TCPIP_MODULE_NOHA
#define TCPIP_MODULE_HA        VRP_YES
#else
#define TCPIP_MODULE_HA        VRP_NO
#endif

/* Add by p00193127 2012-3-30 DTS2012033004012,修改原因:网络整改,剥离分层获取报文过滤 */
/******************************************************************************
 * 剥离分层获取报文功能,默认没有该功能
******************************************************************************/
#ifndef TCPIP_ENABLEPCAP
#define TCPIP_MODULE_PCAP             VRP_NO
#else
#define TCPIP_MODULE_PCAP             VRP_YES
#endif

#ifndef TCPIP_ENABLEDCC
#define TCPIP_MODULE_DCC             VRP_NO
#else
#define TCPIP_MODULE_DCC             VRP_YES
#endif

#ifndef TCPIP_FORUSP
#define TCPIP_FOR_USP             VRP_NO
#else
#define TCPIP_FOR_USP             VRP_YES
#endif

#ifndef TCPIP_FORHERT
#define TCPIP_FOR_HERT             VRP_NO
#else
#define TCPIP_FOR_HERT             VRP_YES
#endif

#ifndef TCPIP_FORBALONG
#define TCPIP_FOR_BALONG           VRP_NO
#else
#define TCPIP_FOR_BALONG           VRP_YES
#endif
/*Added by yanlei00216869, 【代码检视】通过增加编译宏控制，使得以.so方式提供给bluestar的visp，不依赖产品代码, 2014/10/25   问题单号:DTS2014102504024  */
#ifndef TCPIP_FORBLUESTAR
#define TCPIP_FOR_BLUESTAR           VRP_NO
#else
#define TCPIP_FOR_BLUESTAR           VRP_YES
#endif
/* End of Added by yanlei00216869, 2014/10/25   问题单号:DTS2014102504024  */
/************************************************************************
 * 有些函数被声明为static，这样在单元测试时就无法调用该函数，因此，在
 * 单元测试之前，将static改成STATIC，STATIC定义如下
 ************************************************************************/
#ifdef VRP_UNIT_TEST
#define STATIC
#else
#define STATIC  static
#endif

/******************************************************************************
 * 标识数通领域和非数通领域的全局宏
 *   VISP项目在数通领域使用时即放入VRPV5R2中以功能子集的方式使用，全局宏定义为：
 *                  #define TCPIP_IN_VRP    VRP_YES
 *   VISP项目在非数通领域使用时即以mini VRP的方式使用，全局宏定义为：
 *                  #define TCPIP_IN_VRP    VRP_NO
 ******************************************************************************/
#ifndef TCPIP_NOVRP
#define TCPIP_IN_VRP             VRP_YES
#else
#define TCPIP_IN_VRP             VRP_NO
#endif

#ifndef TCPIP_NONSR
#define TCPIP_NSR               VRP_YES
#else
#define TCPIP_NSR                VRP_NO
#endif

#define  VOS_FUNC_TYPE_USER     1  /*产品自定义vos函数集，如控制器，非安全的*/
#define  VOS_FUNC_TYPE_SAFE     2  /*安全vos函数集*/
#define  VOS_FUNC_TYPE_BALONG   3  /*balong  vos 函数集*/

/*Added by yanlei00216869, 支持控制器安全函数适配, 2015/1/6   问题单号:DTS2015010508058 */
#define  VOS_FUNC_TYPE_SAFE_MBSC     4  /*配套控制器产品的安全函数集*/
/* End of Added by yanlei00216869, 2015/1/6   问题单号:DTS2015010508058 */

#ifdef TCPIP_FORBALONG
    #define  TCPIP_VOS_FUNC_TYPE  VOS_FUNC_TYPE_BALONG
#else
/* default unsafe */
#ifndef TCPIP_VOS_FUNC_TYPE
    #define  TCPIP_VOS_FUNC_TYPE  VOS_FUNC_TYPE_USER
#endif
#endif

#if (TCPIP_VOS_FUNC_TYPE == VOS_FUNC_TYPE_BALONG) /*balong 预编译,转定义 */
   #include "vos_redef.h"
#endif

/* 安全整改公共头文件，包含安全/BALONG/非安全宏定义 */
#include "vos_safedef.h"

/*Begin BC3D00605 liangjicheng  2008-11-11*/
#if 1
/* Modified by wujie 61195 for BC3D00428 */
/*缺省为windows*/
#if (TCPIP_NOVRP_VXWORKS == VRP_YES)
#define VRP_OS_WINDOWS           VRP_NO
#define VRP_OS_VXWORKS           VRP_YES
#define VRP_OS_LINUX             VRP_NO
#elif (TCPIP_NOVRP_LINUX == VRP_YES)
#define VRP_OS_WINDOWS           VRP_NO
#define VRP_OS_VXWORKS           VRP_NO
#define VRP_OS_LINUX             VRP_YES
#else
#define VRP_OS_WINDOWS           VRP_YES
#define VRP_OS_VXWORKS           VRP_NO
#define VRP_OS_LINUX             VRP_NO
#endif

/*缺省为小头序*/
#ifndef TCPIP_BIG_ENDIAN
#define VRP_LITTLE_ENDIAN        VRP_YES
#define VRP_BIG_ENDIAN           VRP_NO
#else
#define VRP_LITTLE_ENDIAN        VRP_NO
#define VRP_BIG_ENDIAN           VRP_YES
#endif

#else
#if (VOS_OS_VER == VOS_WIN32)
#define VRP_OS_WINDOWS              VRP_YES
#define VRP_OS_VXWORKS              VRP_NO

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN           VRP_NO
#define VRP_BIG_ENDIAN              VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#endif

#elif (VOS_OS_VER == VOS_VXWORKS)
#define VRP_OS_WINDOWS              VRP_NO
#define VRP_OS_VXWORKS              VRP_YES

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN           VRP_NO
#define VRP_BIG_ENDIAN              VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#elif (VOS_CPU_TYPE == VOS_ARM)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#elif (VOS_CPU_TYPE == VOS_MIPS)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#endif

#elif (VOS_OS_VER == VOS_LINUX)
#define VRP_OS_WINDOWS              VRP_NO
#define VRP_OS_VXWORKS              VRP_YES

#if (VOS_CPU_TYPE == VOS_MIPS32)
#define VRP_LITTLE_ENDIAN           VRP_NO
#define VRP_BIG_ENDIAN              VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN           VRP_YES
#define VRP_BIG_ENDIAN              VRP_NO
#endif

#endif
#endif
/*End BC3D00605 liangjicheng  2008-11-11*/
#ifndef VOS_ARM
#define VOS_ARM                        8
#endif


/********************************************************************
 * 下面两个宏的开与关可以决定编译出的VISP版本是“发行版本”
 * 还是“调试版本”，这两个宏的设置也是互斥的。在调试版本
 * 中，应用程序可以嵌入大量的调试信息，而在发行版本中，这是不允许的
 ********************************************************************/
#define TCPIP_VERSION_RELEASE     VRP_NO
#define TCPIP_VERSION_DEBUG       VRP_YES



/* 欺骗哪些要求必须包含vrpcfg.h的文件 */
#ifndef _VRPCFG_H_
#define _VRPCFG_H_
#endif

/* Added by X36317, 新增为支持ARM CPU字节对齐特性的公共宏, 2006/5/9 */
#ifdef TCPIP_SUPPORT_ARMCPU
/*字节对齐专用宏，VOS_CopyVar(Dest, Src) ，将数据结构（或基本数据类型）变量Src的内容拷贝到Dest。
注意：Dest和Src的数据结构类型，在操作时，必须保证正确而且一致。*/
#define VOS_CopyVar(Dest, Src)\
{\
    (VOID)TCPIP_Mem_Copy((VOID *)&(Dest), sizeof(Dest),(VOID *)&(Src), sizeof(Dest));\
}
/*  Macro for Boundary algin for ARM   2006-5-12   x43050  */
#define NOT_4BYTE_BONDARY(p)  (((ULONG)(p)& 0x00000003) != 0)
#define NOT_2BYTE_BONDARY(p)  (((ULONG)(p)& 0x00000001) != 0)
#else
#define VOS_CopyVar(Dest, Src)  {(Dest) = (Src);}
#endif


/*************************************************************************

 以下是VISP在非数通产品都必须使用的宏，包括：
 1、VRPV5R2的vrpcfg.h文件中的部分宏，根据VISP的需要，原封不动地继承到VISP之中
 2、VISP的IFENT和链路层模块的宏

 注意：对于原封不动地继承的宏，坚决不要对这些宏的名称做任何改动

**************************************************************************/
#define VRP_MODULE_IPHC            VRP_YES
#define VRP_MODULE_LINK_FRF20      VRP_NO
#define VRP_MODULE_VOS_IPC         VRP_NO
#define VRP_MODULE_RTPRO_RM        VRP_NO
#define VRP_MODULE_CFG_IC_BASE     VRP_NO
#define VRP_MODULE_QUEUE           VRP_NO
#define VRP_MODULE_SEC_L2TP        VRP_NO
#define VRP_MODULE_LINK_PPP_CCP    VRP_NO
#define VRP_MODULE_LINK_PPP_OSICP  VRP_NO
#define VRP_MODULE_CFG_BASE        VRP_NO

#define VRP_MODULE_IPV6         VRP_YES
#define VRP_DISTRIBUTED         VRP_NO
#define VRP_MAIN_BOARD          VRP_NO
#define VRP_IO_BOARD            VRP_NO
#define VRP_CENTERALIZATION     VRP_YES
#define VRP_MAX_BOARD_NUM       32
#define VRP_MODULE_LINK_PPP     VRP_YES
#define VRP_PRODUCT_GSR         VRP_NO
#define TCPIP_MODULE_SFIB_RM    VRP_YES
#define TCPIP_MODULE_SFIB6_RM   VRP_YES
#define VRP_MODULE_FIB6CONTR    VRP_YES
#define VRP_MODULE_SEC_ACL      VRP_YES
#define VRP_VERSION_5           VRP_YES


#define VRP_MODULE_LINK_PPP_PAP     VRP_YES
#define VRP_MODULE_LINK_PPP_CHAP    VRP_YES
#define VRP_MODULE_LINK_PPP_IPCP    VRP_YES
#define VRP_MODULE_LINK_PPP_IP6CP   VRP_YES
#define VRP_MODULE_LINK_PPP_CBCP    VRP_NO
#define VRP_MODULE_LINK_PPP_DNS     VRP_YES
#define VRP_MODULE_LINK_PPP_MPLSCP  VRP_NO

#define VRP_MODULE_LINK_PPP_MP          VRP_YES
#define VRP_MODULE_LINK_PPPOE_CLIENT    VRP_YES
#define VRP_MODULE_LINK_PPP_MP_INBOARD  VRP_YES


#define VRP_MODULE_IP_BASE        VRP_YES
#define VRP_MODULE_IP_SOCKET      VRP_YES
#define VRP_MODULE_IP_TCP         VRP_YES
#define VRP_MODULE_IP_UDP         VRP_YES
#define VRP_MODULE_IP_ARP_PROXY   VRP_YES
#define VRP_MODULE_VJCOMP         VRP_YES


#define TCPIP_MODULE_FIBA         VRP_YES
#define VRP_MODULE_DNS_CLIENT     VRP_YES
#define VRP_MODULE_DHCP4C_BASE    VRP_YES
#define VRP_MODULE_IP_MCAST_BASE  VRP_YES  /* 多播收发Added by x36317 2004-9-30*/

#define VRP_MODULE_CFG_PING       VRP_YES
#define VRP_MODULE_LINK_PPPOE     VRP_YES
#define VRP_MODULE_SEC_ACLACC     VRP_NO
#define VRP_MODULE_SEC_ETH_ACL    VRP_YES
#define VRP_MODULE_CFG_TRACERT    VRP_YES  /*end x36308*/
#define VRP_MODULE_SEC_ATK        VRP_YES

#define VRP_MODULE_IFNET         VRP_YES
#define VRP_IFNET_LOGIC_ENHENCE  VRP_YES
#define VRP_MAX_ADAPTOR_NUM      3
#define VRP_IFNET_MP_GROUP       VRP_YES
#define VRP_IP_ICMP_REDIRECTS    VRP_YES /*added by x36530  trace to D03534 20041124 控制重定向报文的发送*/
#define VRP_IP_ICMP_HOST_UNREACH VRP_YES /*added by x36530  trace to D03534 20041124 控制主机不可达报文的发送*/

#ifndef VRP_NO_VRF6
#define VRP_MODULE_VRF6  VRP_YES
#else
#define VRP_MODULE_VRF6  VRP_NO
#endif

#ifndef FALSE
#define    FALSE          0
#endif
#ifndef TRUE
#define    TRUE           1
#endif
/*End,20040923*/

#define VRP_MODULE_MPLS_LSPM_VPN            VRP_NO
#define VRP_MODULE_RTPRO_MPLS_VPN           VRP_NO
#define VRP_MODULE_RTPRO_BGP                VRP_NO
#define VRP_OPTIM_MBUF                      VRP_NO
#define VRP_MODULE_HA_DATA                  VRP_NO
#define VRP_MODULE_HA_SLAVE2MAIN            VRP_NO
#define VRP_MODULE_CFA                      VRP_NO
#define VRP_MODULE_SNMP                     VRP_NO
#define VRP_MODULE_LINK_VLAN                VRP_NO
#define USR_8011                            VRP_NO
#define L3_8011                             VRP_NO
#define VRP_MODULE_BAS_ACM                  VRP_NO
#define VRP_MODULE_LINK_ATM                 VRP_NO
#define VRP_MODULE_IP_VRRP                  VRP_NO
#define VRP_MODULE_SOCKET_ISIS              VRP_NO
#define VRP_MODULE_CFG_CLI_BASE             VRP_NO
#define VRP_MODULE_CFG_EXEC                 VRP_NO
#define VRP_MODULE_CFG_CLI_CFGFILE          VRP_NO
/*End, 2005-12-01*/

#define IPV6_VLAN                             VRP_NO
#define VRP_MODULE_LINK_IPX                   VRP_NO
#define VRP_MODULE_LINK_IPOEOA                VRP_NO
#define VRP_MODULE_IP_MPLS_SOFTFW             VRP_NO
#define VRP_MODULE_SEC_NAT                    VRP_NO
#define VRP_MODULE_NATPT                      VRP_NO
#define VRP_MODULE_IP_SAN_FORWARD             VRP_NO
#define VRP_MODULE_WCCP2                      VRP_NO
#define VRP_IP_DIRECT_BROADCAST               VRP_NO
#define VRP_MODULE_SAN_TRVS                   VRP_NO
#define VRP_MODULE_LSPM_VPN                   VRP_NO
#define VRP_MODULE_IP_POLICY                  VRP_NO
#define VRP_MODULE_SEC_TIMERNG                VRP_NO
#define VRP_PRODUCT_8060                      VRP_NO
#define R8060_NP                              VRP_NO
#define VRP_MODULE_SACL                       VRP_NO
#define VRP_PRODUCT_8060_ROUTER_NE20          VRP_NO
#define PLATFORM_PRODUCT_SEPARATION_API       VRP_NO
#define PPI_CUSTOMIZE_QOS_FEATURE_ON          VRP_NO
#define R8070_MODULE_SECP                     VRP_NO
#define VRP_MODULE_IP_FAST_FORWARDING         VRP_NO
#define VRP_MODULE_MPLS_L2VPN_INTERWORKING    VRP_NO
#define VRP_MODULE_SEC_GRE                    VRP_NO
#define VRP_MODULE_IP_DHCP_SERVER             VRP_NO
#define VRP_MODULE_SEC_BLS                    VRP_NO
#define VRP_MODULE_TP                         VRP_NO
#define VRP_MODULE_IP_URPF                    VRP_NO
#define VRP_MODULE_IP_DHCP                    VRP_NO
#define VRP_HWPING_SNMP                       VRP_NO
#define MODULE_GRE_8011                       VRP_NO
#define VRP_MODULE_LINK_ETHERNET              VRP_NO
#define VRP_MODULE_MPLS                       VRP_NO
#define VRP_IP_VERIFY_SOURADD                 VRP_NO
#define VRP_CLEAR_IP_DF                       VRP_NO
#define VRP_MODULE_IP_PBR                     VRP_NO
#define VRP_MODULE_IP_DHCP_RELAY              VRP_NO
#define VRP_MODULE_IP_HELPER_ADDRESS          VRP_NO
#define VRP_PRODUCT_8060_FW                   VRP_NO
#define VRP_MODULE_SEC_ACLVPN                 VRP_NO
#define VRP_MODULE_NE5000QOS                  VRP_NO
#define VRP_PRODUCT_NE5000                    VRP_NO
#define VRP_MODULE_IP_MCAST_FORWARD           VRP_NO
#define VRP_MODULE_IP_MCAST_POLICY            VRP_NO
#define VRP_MODULE_SEC_IPSEC                  VRP_YES
#define VRP_MODULE_HRP                        VRP_NO
#define VRP_MODULE_LINK_MFR                   VRP_NO
#define NE80_MODULE_ADP                       VRP_NO
#define VRP_MODULE_NETSTREAM                  VRP_NO
#define VRP_MODULE_MPLSQOS                    VRP_NO
#define GSR_8011                              VRP_NO
#define VRP_MODULE_RTPRO_MCAST                VRP_NO
#define VRP_MODULE_RTPRO_MCAST_LOCAL          VRP_NO
#define VRP_OPTIM_VP                          VRP_NO
/*End, 2005-12-01*/

#define VRP_MODULE_VOS_VFS                    VRP_NO
#define VRP_MODULE_LSPV                       VRP_NO

/*Moved by x36317 from mp_basic_inc.h, 2006-05-22*/
#define VRP_MODULE_RADIUS_MP                VRP_NO
#define VRP_MODULE_PPP_BACKUP               VRP_NO
#define VRP_MAIN_BOARD_INTERFACE            VRP_NO
#define VRP_MODULE_LINK_IB                  VRP_NO
#define R8070_IFNET_IFBACKUP                VRP_NO
#define VRP_MODULE_LINK_PPP_IPXCP           VRP_NO
#define VRP_MODULE_STAC                     VRP_NO
#define VRP_MODULE_LINK_DDR                 VRP_NO
#define VRP_MODULE_QOS_LFI                  VRP_NO
#define VRP_MODULE_MPQOS                    VRP_NO
#define VRP_MODULE_QOS                      VRP_NO

/*Moved by x36317 from poec_basic_inc.h, 2006-05-22*/
#define VRP_MODULE_LINK_DDRS                VRP_NO
#define VRP_MODULE_SEC_FIREWALL             VRP_NO

/* Added by X36317, 定义如下宏以消除PC-LINT告警, 2006/5/23 */
#define IF_HOT_CTL                          VRP_NO
#define IF_INFO_CTL                         VRP_NO
#define VRP_MODULE_LINK_DLSW                VRP_NO
#define VRP_MODULE_VPN_L2VPN                VRP_NO
#define VRP_MODULE_TB_BASE                  VRP_NO
#define VRP_IFNET_INTERFACE_ENHANCE         VRP_NO
#define VRP_MODULE_LINK_FR                  VRP_NO
#define VRP_IFNET_ATMEXTEND                 VRP_NO
#define VRP_IFNET_E1_T1_E3_T3_CPOS          VRP_NO
#define VRP_MODULE_SEC_IKE                  VRP_YES
#define VRP_MODULE_SEC_ACL6                 VRP_NO
#define VRP_MODULE_TRUNK                    VRP_NO
#define VRP_MODULE_MPLS_LSPM                VRP_NO

/* 为消ipv6三个模块的pc-lint告警加这两个宏 */
#define VRPV5_PERF_OPT_VER                  VRP_NO
#define NE80_MODULE_DPT                     VRP_NO


/*As linux need more memory giving 512k  stack size for linux and 16k for others*/

#if (VOS_OS_VER == VOS_LINUX)
#define TCPIP_DEFAULT_STACK_SIZE 512*1024
#define TCPIP_LLDP_STACK_SIZE  512*1024
#else
#define TCPIP_DEFAULT_STACK_SIZE 16*1024
#define TCPIP_LLDP_STACK_SIZE  16*1024
#endif


#define TCPIP_PPPMUX_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE
#define TCPIP_DHCP4C_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE
#define TCPIP_DHCP4R_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE
#define TCPIP_DHCP6R_STACK_SIZE TCPIP_DEFAULT_STACK_SIZE

/*#include "dopra_def.h"*/
#include "v_configOS.h"
#include "tcpip_cpu.h"

#ifdef  __cplusplus
}
#endif

#endif  /* end of _TCPIP_CONFIG_H_ */

