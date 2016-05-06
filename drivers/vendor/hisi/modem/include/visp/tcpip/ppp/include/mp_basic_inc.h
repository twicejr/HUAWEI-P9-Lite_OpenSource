/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                            mp_basic_inc.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-15
 *        Author: YaoChengliang
 *   Description: MP模块的C文件包含的基本头文件
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-15      YaoChengliang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2006-05-13      l48923          Delete useless code
 *
 *************************************************************************/

#ifndef _MP_BASIC_INC_H_
#define _MP_BASIC_INC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"

/**********************************************************************/
/* MP Extern Header Files in Non-DataCom Enviroment (VISP)            */
/**********************************************************************/
/* VOS Basic Header Files */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_util.h" 
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_intr.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/wlst_inc.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"
#include "vos/vospubh/systrace.h"
#include "vos/vospubh/vos_time.h"

#include "public/vrpvos/vrp_pktqueue.h"
#include "public/entry/tcpip_entry.h" 
#include "public/tcpip_debug.h"
#include "tcpip/public/tcpip_debug.h"

/* IFNET Basic Header Files */
#include "ifnet/include/iifnet_inc.h"
#include "ifnet/core/include/iifnet.h"
#include "ifnet/shell/include/if_ic.h" 
#include "ifnet/core/include/if_func.h"

/* IPv4 Basic Header Files */
#include "ip4/am4/include/am4_pub.h"
#include "ip4/pp4/include/pp4_pub.h"
#include "tcp4/core/include/tcp.h"

/* Added by t45114: 共享数据保护,2006/03/21 */
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_com.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */
/*#include "tcpip/socket4/core/include/sock_key.h" */
#include "tcpip/socket4/core/include/sock_comp.h"
#include "tcpip/socket4/core/include/in_pcb.h"
#include "tcpip/socket4/core/include/sock_deb.h"
/*#include "tcpip/socket4/core/include/sock_var.h" */
/* End of addition */

/* PPP Basic Header Files*/
#include "ppp/core/include/ppp_core_def.h"
#include "ppp/core_mp/include/mp_def.h"
#include "ppp/include/mp_api.h"
#include "ppp/core/include/ppp_core_type.h"
#include "ppp/core/include/ippp.h" 
#include "ppp/include/ippp_inc.h"
#include "ppp/core/include/ppp_lcp_type.h"

#include "ppp/core/include/ppp_lqm_type.h"

#include "ppp/core/include/ppp_ipcp_typ.h"
#include "ppp/core/include/ppp_vj_func.h"
#include "ppp/core/include/ppp_core_var.h"
#include "ppp/core/include/ppp_core_fun.h"
#include "ppp/core/include/ppp_ip6cp_type.h"

/* ETHARP Basic Header Files*/
#include "public/tcpip_ppi.h"
#include "etharp/include/ieth_inc.h"

/* PPPoE Client Basic Header Files*/
#include "pppoec/include/ipoec_inc.h"

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/tcp4/core/include/tcp.h"
#include "tcpip/udp4/core/include/udp.h"
#include "tcpip/iphc/include/iiphc_inc.h"
#include "tcpip/iphc/core/include/iiphc.h"


/*********************************************************************/
/* MP Inner Header Files in All Enviroment                           */
/*********************************************************************/
#include "ppp/core_mp/include/mp_type.h"
#include "ppp/core_mp/include/mp_var.h"
#include "ppp/include/imp_inc.h"

#ifdef __cplusplus
}
#endif

#endif
