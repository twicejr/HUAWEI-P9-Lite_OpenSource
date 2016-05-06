/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfib6.h
*
*  Project Code: VISPV100R007
*   Module Name: sfib6  
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

#ifndef _TCPIP_SFIB6_H_
#define _TCPIP_SFIB6_H_

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
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/rdx6_pub.h"

#include "vos/vospubh/mbuf.h"
#include "tcpip/ifnet/include/iifnet_inc.h"

#include "vos/vospubh/ipc_inc.h"
#include "vos/vospubh/rpc_inc.h"
#include "vos/vospubh/systrace.h"
#include "vos/vosprih/rpc_pri.h"


#include "vos/vospubh/compbase.h"

/*Modified by limin00188004, SRM-RIB6查询, approved by qinyun62011, 2011/8/12   问题单号:C06新需求 */
#include "public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_debug.h"
/*End of modification by limin00188004, 2011/8/12   问题单号:C06新需求 */

/*sfib6模块依赖的其他组件的头文件*/
#include "tcpip/sfib4/include/ifiba_inc.h"
#include "tcpip/ipv6/sfib6/include/ifib6c_inc.h"

#include "tcpip/ip4/am4/include/am4_pub.h"

#include "tcpip/socket4/core/include/sock_err.h"
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/sock_pub.h"

#include "tcpip/ip4/pp4/include/pp4_pub.h"

#include "tcpip/socket4/core/include/in_pcb.h"

#include "tcpip/socket4/core/include/sock_deb.h"
#include "tcpip/socket4/core/include/sock_var.h"

#include "tcpip/ipv6/sfib6/shell/include/sfib6_sh_main.h"
#include "tcpip/ipv6/sfib6/shell/include/sfib6_sh_rm.h"

/*sfib6模块对外开放的宏、数据结构定义、组件接口定义*/

#include "tcpip/ipv6/sfib6/include/sfib6_api.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_SFIB6_H_ */

