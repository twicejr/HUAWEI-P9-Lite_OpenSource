/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln_inc.h
*
*  Project Code: VISPV100R007
*   Module Name: Ethvlan  
*  Date Created: 2008-08-01
*        Author: qinyun(62011)
*   Description: ethvln_inc.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME           DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-01   qinyun(62011)  Create the first version.
*******************************************************************************/

#ifndef _ETHVLN_INC_H
#define _ETHVLN_INC_H

#ifdef  __cplusplus
extern "C"{
#endif
#include "tcpip/public/tcpip_config.h"
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_lib.h"

#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"

#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/entry/tcpip_entry.h"

/* use VISP's new developed IFNET's headerfile */
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"

#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/include/ieth_inc.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/core/include/etharp_core_api.h"
#include "tcpip/etharp/core/include/ieth.h"
#include "tcpip/trunk/include/trunk_inc.h"

#include "tcpip/vlan/core/include/ethvln_def.h"
#include "tcpip/vlan/core/include/ethvln_public.h"
#include "tcpip/vlan/include/ethvln_api.h"
#include "tcpip/vlan/core/include/ethvln.h"
#include "tcpip/vlan/core/include/ethvln_cfg.h"
#include "tcpip/vlan/core/include/ethvln_var.h"
#include "tcpip/vlan/core/include/ethvln_ha.h"
#include "tcpip/vlan/shell/include/ethvln_sh.h"

#include "tcpip/public/tcpip_ppi.h"

#include "tcpip/public/tcpip_ha.h"
#include "tcpip/etharp/core/include/etharp_ha.h"

#include "tcpip/ipv6/ppmng/core/include/ppmng_pub.h"
#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "common/ipos/ipv6/basic/addrmng/iaddr_inc.h"
#include "common/ipos/ipv6/basic/nd/ind_inc.h"

#include "tcpip/public/dopra/waitlist.h"

extern ULONG g_ulCreateVlanTimeTotal;
extern ULONG g_ulCreateVlanPPITimeTotal;
extern ULONG g_ulCreateVlanLinkTimeTotal;
extern ULONG g_ulCreateVlanInsertTimeTotal;
extern ULONG g_ulCreateVlanCount;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif 
