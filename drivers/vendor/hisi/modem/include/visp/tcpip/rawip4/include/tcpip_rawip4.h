/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_rawip4.h
*
*  Project Code: VISPV100R006C02
*   Module Name: rawip4 
*  Date Created: 2007-07-31
*        Author: zhanghuihui(55157)
*   Description: rawip4模块对外声明的头文件,供用户使用rawip4模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   zhanghuihui(55157)      Create
*
*******************************************************************************/
#ifndef _TCPIP_RAWIP4_H_
#define _TCPIP_RAWIP4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h" 

/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_mem.h" 
#include "vos/vospubh/vos_id.h" 
#include "vos/vospubh/vos_util.h" 
#include "vos/vospubh/vos_intr.h" 
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_ker.h"  
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/ipc_inc.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/wlst_inc.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlhash.h"
#include "vos/vospubh/vos_lib.h"

#include "vos/vospubh/compbase.h"

#include "vos/vospubh/vos_que.h"
#include "vos/vospubh/vos_ev.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/gads_api.h"
#include "vos/vosprih/wlst_pri.h"
#include "vos/vosregex/vos_regx.h"

/*RAWIP4模块依赖的其他组件的头文件*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "ifnet/include/iifnet_inc.h"
#include "ip4/am4/include/am4_pub.h"
#include "socket4/core/include/macro.h"
#include "socket4/core/include/sock_com.h"
#include "socket4/core/include/select.h"
#include "socket4/core/include/sock_pub.h"
#include "socket4/core/include/sock_err.h"
#include "ip4/pp4/include/pp4_pub.h"

#include "ipv6/ppmng/core/include/ppmng_pub.h"
#include "ipv6/socket6/core/include/sock6_pub.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_debug.h"

#include "tcpip/public/arith_cbb/include/arith_ip.h"

/*RAWIP4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/rawip4/core/include/raw_ip_pub.h"
#include "tcpip/rawip4/core/include/raw_ip_var.h"
#include "tcpip/rawip4/core/include/raw_ip_func.h"
#include "tcpip/rawip4/core/include/iraw_ip.h"
#include "tcpip/rawip4/core/include/raw_ip_typ.h"
#include "tcpip/rawip4/include/rawip_api.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_RAWIP4_H_ */


