/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_iphc.h
*
*  Project Code: VISPV100R006C02
*   Module Name: IPHC 头文件  
*  Date Created: 2007-7-30
*        Author: yebo(62004)
*   Description: IPHC 头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2007-7-30  yebo(62004)         Create the first version.
*
*******************************************************************************/
#ifndef _TCPIP_IPHC_H
#define _TCPIP_IPHC_H


#ifdef __cplusplus
extern "C" {
#endif

/* 配置头文件 */
#include "tcpip/public/tcpip_config.h"

/*VOS 头文件 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_intr.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"
#include "public/vrpvos/vrp_pktqueue.h"

/* IPHC 依赖ifnet组件的头文件 */
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"  

#include "tcpip/public/entry/tcpip_entry.h"

/* IPHC 依赖ppp组件的头文件 */
#include "tcpip/ppp/include/ippp_inc.h"
#include "tcpip/ppp/core/include/ippp.h"
#include "tcpip/ppp/core/include/ppp_lcp_type.h"
#include "tcpip/ppp/core/include/ppp_ipcp_typ.h"
#include "tcpip/ppp/core/include/ppp_ip6cp_type.h"
#include "tcpip/ppp/core/include/ppp_chap_type.h"
#include "tcpip/ppp/core/include/ppp_pap_type.h"
#include "tcpip/ppp/core/include/ppp_core_var.h"
#include "tcpip/ppp/core/include/ppp_core_fun.h"

/* IPHC 依赖am4组件的头文件 */
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"

/* IPHC 依赖Socket组件的头文件 */
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_comp.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */

#include "tcpip/public/tcpip_debug.h"

/* IPHC 依赖Socket组件的头文件 */
#include "ip4/pp4/include/pp4_pub.h"
#include "udp4/core/include/udp.h"
#include "tcp4/core/include/tcp.h"


/* IPHC 头文件 */
#include "iphc/include/iphc_api.h"
#include "iphc/core/include/iphc_def.h"
#include "iphc/core/include/iphc_typ.h"
#include "iphc/core/include/iphc_fun.h"
#include "iphc/core/include/iiphc.h"

#ifdef __cplusplus
}
#endif

#endif

