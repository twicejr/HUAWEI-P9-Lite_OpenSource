/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_ext.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG模块包含其它模块头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_EXT_H
#define _1AG_EXT_H

#ifdef  __cplusplus
    extern "C"{
#endif
/*包含头文件*/

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_intr.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"
#include "public/vrpvos/vrp_pktqueue.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"

#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/include/if_type.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/include/ieth_inc.h"

#include "tcpip/public/tcpip_ha.h"

#include "tcpip/trunk/include/trunk_api.h"
#include "tcpip/trunk/core/include/trunk_def.h"
#include "tcpip/trunk/core/include/trunk_typ.h"
#include "tcpip/trunk/core/include/trunk_ha.h"
#include "tcpip/trunk/core/include/trunk_fun.h"
#include "tcpip/trunk/core/include/itrunk.h"

#include "tcpip/l2if/include/tcpip_l2if.h"
#include "tcpip/vrrp/include/tcpip_vrrp.h"

#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/public/debug/tcpip_pcap.h"


#ifdef  __cplusplus
}
#endif

#endif

