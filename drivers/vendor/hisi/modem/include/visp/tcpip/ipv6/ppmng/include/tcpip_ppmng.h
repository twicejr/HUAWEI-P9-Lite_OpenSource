/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ppmng.h
*
*  Project Code: VISPV100R007
*   Module Name: socket6  
*  Date Created: 2008-04-09
*        Author: wangbin62223
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-09   wangbin62223       Create
*
*******************************************************************************/

#ifndef _TCPIP_PPMNG_H_
#define _TCPIP_PPMNG_H_

#ifdef __cplusplus
extern "C" {
#endif
    
#include "tcpip/public/tcpip_config.h" 
    
/* 对VRPVOS的头文件依赖 */

#include    "vos/vospubh/basetype.h"
#include    "vos/vospubh/mbuf.h"
#include    "vos/vospubh/compbase.h"
#include    "vos/vospubh/vos_id.h"
#include    "vos/vospubh/vos_ker.h"
#include    "vos/vospubh/vos_err.h"
#include    "vos/vospubh/vos_mem.h"
#include    "vos/vospubh/vos_tmr.h"
#include    "vos/vospubh/compbase.h"
#include    "vos/vospubh/iunknown.h"
#include    "vos/vospubh/icompfactory.h"
#include    "vos/vospubh/paf.h"
#include    "vos/vospubh/license.h"
#include    "vos/vospubh/systrace.h"

#include    "vos/vospubh/utldll.h"
#include    "vos/vospubh/utlsll.h"

/*ppmng模块依赖的其他组件的头文件*/
#include    "tcpip/ifnet/include/iifnet_inc.h"
#include    "tcpip/ifnet/core/include/if_index.h"

/*ppmng块对外开放的宏、数据结构定义、组件接口定义*/

#include    "tcpip/ipv6/ppmng/core/include/ippmng.h"
#include    "tcpip/socket4/core/include/macro.h"

#include    "tcpip/ipv6/ppmng/core/include/ppmng_pub.h"
#include    "tcpip/ipv6/ppmng/core/include/ppmng_input.h"
#include    "tcpip/ipv6/ppmng/core/include/ppmng_intermediate.h"
#include    "tcpip/ipv6/ppmng/core/include/ppmng_extension.h"
#include    "tcpip/ipv6/ppmng/core/include/ppmng_proto_mgnt.h"
#include    "tcpip/socket4/core/include/sock_com.h"
#include    "tcpip/ipv6/socket6/core/include/sock6_pub.h"
#include    "tcpip/socket4/core/include/sock_comp.h"
#include    "tcpip/ipv6/ppmng/core/include/ppmng_var.h"

#include    "ipv6/ip6_pub.h"
#include    "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include    "common/ipos/ipv6/basic/addrmng/addr_public.h"
#include    "common/ipos/ipv6/basic/nd/nd_public.h"
#include    "common/ipos/ipv6/basic/nd/ind_inc.h"
#include    "common/ipos/ipv6/basic/icmp6/iicmp6_inc.h"
#include    "tcpip/sfib4/include/ifiba_inc.h"

#include    "tcpip/ipv6/ppmng/core/include/ippmng.h"
#include    "tcpip/ipv6/ppmng/core/include/ppmng.h"
#include    "tcpip/ipv6/ppmng/include/ippmng_inc.h"


#include    "tcpip/ipv6/ppmng/include/ppmng_api.h"
#include    "public/entry/tcpip_entry.h"

#include    "tcpip/public/tcpip_debug.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_PPMNG_H_ */

