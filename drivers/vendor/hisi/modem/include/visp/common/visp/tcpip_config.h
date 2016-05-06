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

/*----------------------------------------------------------------------
 * 下面两个宏定义了“开”和“关”两个状态，直接继承VRP的相关宏。
 *  例如：
 *        #define TCPIP_IN_VRP           VRP_YES
 *        #define VRP_DISTRIBUTED        VRP_NO
 * 表示VISP放入VRPV5之中，VISP不是分布式方式应用，这样，VISP系统在编译时，
 * 就可以拆掉相关代码。
 * 需要注意的是有些意义上互斥的一对宏，不能被同时置为“VRP_YES”或“VRP_NO”，
 * 注意，请不要修改这两个宏的值。
 */
#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif


/*----------------------------------------------------------------------
 * 标识数通领域和非数通领域的全局宏
 *   VISP项目在数通领域使用时即放入VRPV5R2中以功能子集的方式使用，全局宏定义为：
 *                  #define TCPIP_IN_VRP    VRP_YES
 *   VISP项目在非数通领域使用时即以mini VRP的方式使用，全局宏定义为：
 *                  #define TCPIP_IN_VRP    VRP_NO
 */

/*Modified by dengxiong for D00173*/
#ifndef TCPIP_NOVRP
#define TCPIP_IN_VRP             VRP_YES
#else
#define TCPIP_IN_VRP             VRP_NO
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
   #include "tcpip/public/vos_redef.h"
#endif

/* 安全整改公共头文件，包含安全/BALONG/非安全宏定义 */
#include "tcpip/public/vos_safedef.h"

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
#define VRP_OS_WINDOWS           	VRP_YES
#define VRP_OS_VXWORKS           	VRP_NO

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN        	VRP_NO
#define VRP_BIG_ENDIAN           	VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#endif

#elif (VOS_OS_VER == VOS_VXWORKS)
#define VRP_OS_WINDOWS           	VRP_NO
#define VRP_OS_VXWORKS           	VRP_YES

#if (VOS_CPU_TYPE == VOS_PPC)
#define VRP_LITTLE_ENDIAN        	VRP_NO
#define VRP_BIG_ENDIAN           	VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#elif (VOS_CPU_TYPE == VOS_ARM)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#elif (VOS_CPU_TYPE == VOS_MIPS)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#endif 

#elif (VOS_OS_VER == VOS_LINUX)
#define VRP_OS_WINDOWS           	VRP_NO
#define VRP_OS_VXWORKS           	VRP_YES

#if (VOS_CPU_TYPE == VOS_MIPS32)
#define VRP_LITTLE_ENDIAN        	VRP_NO
#define VRP_BIG_ENDIAN           	VRP_YES
#elif (VOS_CPU_TYPE == VOS_X86)
#define VRP_LITTLE_ENDIAN        	VRP_YES
#define VRP_BIG_ENDIAN           	VRP_NO
#endif

#endif
#endif
/*End BC3D00605 liangjicheng  2008-11-11*/
#ifndef VOS_ARM
#define VOS_ARM                        8
#endif

/*----------------------------------------------------------------------
 * 下面两个宏的开与关可以决定编译出的VISP版本是“发行版本”
 * 还是“调试版本”，这两个宏的设置也是互斥的。在调试版本
 * 中，应用程序可以嵌入大量的调试信息，而在发行版本中，这是
 * 不允许的
 */
#define TCPIP_VERSION_RELEASE     VRP_NO
#define TCPIP_VERSION_DEBUG       VRP_YES

/*----------------------------------------------------------------------*/

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


#define VRP_MODULE_HA_DATA                  VRP_NO
#define VRP_MODULE_HA_SLAVE2MAIN            VRP_NO
#define VRP_MODULE_SNMP                     VRP_NO
#define VRP_MODULE_CFG_CLI_BASE             VRP_NO
/*End, 2005-12-01*/


/*Add for IR IPSec/IKE*/
#define VRP_MODULE_SEC_IPSEC                VRP_YES 

#define VRP_MODULE_SEC_IKE                  VRP_YES

#define VRP_MODULE_SEC_ENCRY_BLOWFISH       VRP_YES
#define VRP_MODULE_SEC_ENCRY_3DES           VRP_YES
#define VRP_MODULE_SEC_ENCRY_CAST           VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_ENCRY_DES            VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_ENCRY_RIPEMD         VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_ENCRY_SHA            VRP_YES
#define VRP_MODULE_SEC_ENCRY_SKIPJACK       VRP_YES /* YES & NO*/
#define VRP_MODULE_SEC_IKE_GNU              VRP_YES /* YES & NO*/

/* Added by Vivek, for DH changes (OpenSource) */
#define VRP_MODULE_UTIL_BN                  VRP_YES /* YES & NO*/


/*#include "dopra_def.h"*/
#include "v_configOS.h"

#ifdef  __cplusplus
}
#endif

#endif  /* end of _TCPIP_CONFIG_H_ */


