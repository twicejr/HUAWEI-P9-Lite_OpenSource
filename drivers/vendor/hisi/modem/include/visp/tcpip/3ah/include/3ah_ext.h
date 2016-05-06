/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_ext.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块需要的外部头文件和函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_EXT_H_
#define _3AH_EXT_H_

#ifdef __cplusplus
extern "C"{
#endif

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
#include "v_sm.h"
#include "public/dopra/waitlist.h"

#include "tcpip/l2if/include/tcpip_l2if.h"

#include "tcpip/public/arith_cbb/include/arith_ip.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"


#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/include/if_type.h"

#include "tcpip/etharp/include/tcpip_etharp.h"

#include "tcpip/trunk/include/trunk_inc.h"

#include "tcpip/public/tcpip_ha.h"

#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_public.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_ppi.h"

#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/public/debug/tcpip_pcap.h"


extern VOS_VOID  VOS_GetCpuTick( VOS_UINT32 *plow,VOS_UINT32 *phigh );

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_EXT_H_   */

