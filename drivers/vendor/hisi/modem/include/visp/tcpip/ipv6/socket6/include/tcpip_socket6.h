/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_socket6.h
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

#ifndef _TCPIP_SOCKET6_H_
#define _TCPIP_SOCKET6_H_

#ifdef __cplusplus
extern "C" {
#endif
    
#include "tcpip/public/tcpip_config.h" 
    
/* 对VRPVOS的头文件依赖 */


#include "dopra/vos/config/vrpvos/vos/vospubh/basetype.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_err.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_ker.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_mem.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/mbuf.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_util.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_id.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/compbase.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_tmr.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_task.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_def.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_lib.h"


/*socket6模块依赖的其他组件的头文件*/
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/public/ip_dmain.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "ipv6/ppmng/core/include/ppmng_pub.h"
#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/ipv6/socket6/core/include/sock6_pub.h" 




/*socket6模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/socket4/core/include/prod.h"
#include "tcpip/socket4/core/include/sock_key.h"
#include "tcpip/socket4/core/include/sock_comp.h"
#include "tcpip/socket4/core/include/in_pcb.h"
#include "tcpip/ipv6/socket6/core/include/in6_pcb.h"
#include "tcpip/socket4/core/include/sock_fun.h"
#include "tcpip/socket4/core/include/sock_deb.h"
#include "tcpip/socket4/core/include/asynsock.h"
#include "tcpip/socket4/core/include/isock.h"
#include "tcpip/socket4/core/include/sock_deb.h"
#include "tcpip/ipv6/socket6/core/include/isock6.h"
#include "tcpip/socket4/core/include/sock_var.h"
#include "tcpip/ipv6/socket6/core/include/sock6_var.h"
#include "tcpip/socket4/core/include/socktemp.h"

#include "public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_debug.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_SOCKET6_H_ */

