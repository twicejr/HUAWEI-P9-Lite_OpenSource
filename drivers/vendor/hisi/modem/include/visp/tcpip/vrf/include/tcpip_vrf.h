/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_vrf.h
*
* Project Code: VISPV100R007
*  Module Name: VRF  
* Date Created: 2009-01-20
*       Author: Qinyun
*  Description: VRF模块对外提供的宏定义、结构、函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-01-20   Qinyun                  Create
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_VRF_H_
#define _TCPIP_VRF_H_

#include "tcpip/public/tcpip_config.h"

#include "dopra/vos/config/vrpvos/vos/vospubh/basetype.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_err.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_def.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_ker.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_mem.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/mbuf.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_util.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_id.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_ev.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/compbase.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/systrace.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/arith_cbb/include/avltree.h"
#include "tcpip/public/tcpip_log.h"

/* use VISP's new developed IFNET's headerfile */
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/if_vlink.h"
#include "tcpip/ifnet/core/include/iifnet.h"

#include "tcpip/public/tcpip_ha.h"


#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/vrpip/ip_pub.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/core/include/ieth.h"

#include "tcpip/dhcp4c/include/tcpip_dhcp4c.h"
#include "tcpip/trunk/include/tcpip_trunk.h"
#include "tcpip/pppoec/include/tcpip_poec.h"
#include "tcpip/poes/include/tcpip_poes.h"

#include "vrf/include/vrf_api.h"
#include "vrf/core/include/vrf_pub.h"
#include "vrf/core/include/vrf_core.h"

#include "vrf6/include/vrf6_api.h"
#include "vrf6/core/include/ivrf6_inc.h"
#include "vrf6/core/include/ivrf6.h"
#include "vrf6/core/include/vrf6_core.h"
#include "vrf6/core/include/vrf6_sh_init.h"


#include "vrf/core/include/ivrf_inc.h"
#include "vrf/core/include/ivrf.h"
#include "vrf/shell/include/vrf_sh_init.h"
#include "vrf/core/include/vrf_tree.h"
#include "vrf/core/include/vrf_ha.h"

#endif  /* _TCPIP_VRF_H_  */

#ifdef  __cplusplus
}
#endif
