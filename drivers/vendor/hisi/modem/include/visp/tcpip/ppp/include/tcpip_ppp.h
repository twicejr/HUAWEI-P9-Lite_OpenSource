/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ppp.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPP 
*  Date Created: 2007-08-20
*        Author: X36317
*   Description: PPP模块对外声明的头文件,供用户使用PPP模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-08-20   X36317       Create
*
*******************************************************************************/

#ifndef _TCPIP_PPP_H_
#define _TCPIP_PPP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"  
    
/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/compbase.h"

/*PPP模块依赖的其他组件的头文件*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"

#include "tcpip/etharp/core/include/etharp_pub_type.h"  
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/socket4/core/include/macro.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */
/* 因为以前的测试代码中有一些PPPmux的相关函数，为了直接使用,故直接包含*/
#include "tcpip/ppp/include/pppmux_basic_inc.h"
/* ppp_sh_main_cen函数中包含了IPHC的显示函数，所以增加一些而外头文件 */
#include "ip4/pp4/include/pp4_pub.h"
#include "udp4/core/include/udp.h"
#include "tcp4/core/include/tcp.h"

#include "tcpip/dhcp4c/include/dhcp4c_api.h"

#include "tcpip/ppp/include/ppp_api.h"
#include "tcpip/ppp/include/ippp_inc.h"
#include "tcpip/ppp/core/include/ppp_ipcp_typ.h"

#include "tcpip/iphc/core/include/iphc_def.h"
#include "tcpip/iphc/core/include/iphc_typ.h"
#include "tcpip/iphc/include/iphc_api.h"
#include "tcpip/iphc/core/include/iphc_fun.h"

/*PPP模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/ppp/core/include/ippp.h"
#include "tcpip/ppp/core/include/ppp_lcp_type.h"
#include "tcpip/ppp/core/include/ppp_ip6cp_type.h"
#include "tcpip/ppp/core/include/ppp_chap_type.h"
#include "tcpip/ppp/core/include/ppp_pap_type.h"
#include "tcpip/ppp/core/include/ppp_core_var.h"
#include "tcpip/ppp/core/include/ppp_lqm_type.h"
#include "tcpip/ppp/shell/include/ppp_sh_main_cen.h"
#include "tcpip/ppp/core_osicp/include/osicp_type.h"
#include "tcpip/ppp/include/imp_inc.h"
#include "tcpip/ppp/core/include/ppp_core_hdr.h"
#include "tcpip/ppp/core/include/ppp_gr.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_PPP_H_ */

