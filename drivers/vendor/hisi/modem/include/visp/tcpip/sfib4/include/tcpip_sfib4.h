/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfib4.h
*
*  Project Code: VISPV100R006
*   Module Name: SFIB4  
*  Date Created: 2007-07-30
*        Author: zengshaoyang62531
*   Description: SFIB4模块对外声明的头文件,供用户使用SFIB4模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-30   zengshaoyang62531       Create
*
*******************************************************************************/

#ifndef _TCPIP_SFIB4_H_
#define _TCPIP_SFIB4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"   
    
/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_id.h"    
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_que.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_ev.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/ipc_inc.h"
#include "vos/vospubh/rpc_inc.h"
#include "vos/vospubh/systrace.h"
#include "vos/vosprih/rpc_pri.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/systrace.h"
#include "vos/vosprih/rpc_pri.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/paf.h"
#include "vos/vospubh/rdx6_pub.h"
#include "vos/vospubh/compbase.h"

/*sfib4模块依赖的其他组件的头文件*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/select.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_err.h"
#include "tcpip/socket4/core/include/in_pcb.h"
#include "tcpip/socket4/core/include/uio.h"
#include "tcpip/socket4/core/include/sock.h"
#include "tcpip/ipv6/ip6_pub.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/rawip4/core/include/raw_ip_pub.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/public/arith_cbb/include/arith_ip.h"
#include "tcpip/ifnet/core/include/if_func.h"


/*sfib4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/sfib4/include/ifiba_inc.h"
#include "tcpip/sfib4/include/ifib4c_inc.h"
#include "tcpip/ipv6/sfib6/include/ifib6c_inc.h"
#include "tcpip/sfib4/shell/include/sfib_sh_main.h"
#include "tcpip/sfib4/shell/include/sfib_sh_rm.h"
#include "tcpip/ipv6/sfib6/shell/include/sfib6_sh_rm.h"
#include "tcpip/sfib4/core_fiba/include/fiba_pub_defs.h"
#include "tcpip/sfib4/shell/include/sfib_sh_ha.h"
#include "tcpip/sfib4/core_fiba/include/fiba_pub_type.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_SFIB4_H_ */

