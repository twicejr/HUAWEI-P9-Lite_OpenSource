/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_ext.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-27
*        Author: PBQ(RT24429)
*   Description: DHCP6R模块需要的外部头文件及函数声明
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME                DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)        Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_EXT_H_
#define _DHCP6R_EXT_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/utldll.h"
#include "visp/software/vrpcfg.h"
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
#include "v_sm.h"
#include "vos/vospubh/wlst_inc.h"

#include "tcpip/public/arith_cbb/include/arith_ip.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "tcpip/ifnet/include/if_type.h"

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/tcp4/core/include/tcp.h"
#include "tcpip/udp4/core/include/udp.h"

#include "tcpip/ipv6/ppmng/core/include/ppmng_pub.h"
#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "common/ipos/ipv6/basic/addrmng/iaddr_inc.h"

#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"
#include "tcpip/socket4/core/include/sock_deb.h"
#include "tcpip/ipv6/socket6/core/include/isock6.h" 
#include "tcpip/ipv6/socket6/core/include/sock6_pub.h"

#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_basefun.h"

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif      /* end of _DHCP6R_EXT_H_ */

