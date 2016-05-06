/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ping.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PING 
*  Date Created: 2007-08-20
*        Author: X36317
*   Description: PING模块对外声明的头文件,供用户使用PING模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-08-20   X36317       Create
*
*******************************************************************************/

#ifndef _TCPIP_PING_H_
#define _TCPIP_PING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"  
    
/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/utldll.h"

#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/shell/include/if_ic.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"

#include "tcpip/ifnet/core/include/if_func.h"

/*PING模块依赖的其他组件的头文件*/
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"

#include "tcpip/ipv6/ppmng/core/include/ppmng_pub.h"

#include "tcpip/socket4/include/sock_inc.h" 
#include "tcpip/socket4/core/include/sock_pub.h" 
    
/*PING模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/ping/include/ping_api.h"
#include "tcpip/ping/core/include/ping_def.h"
#include "tcpip/ping/include/ping_pub.h"
#include "tcpip/ping/include/iping_inc.h"
#include "tcpip/ping/shell/include/ping_sh_info.h"
#include "tcpip/public/arith_cbb/include/arith_ip.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_PING_H_ */

