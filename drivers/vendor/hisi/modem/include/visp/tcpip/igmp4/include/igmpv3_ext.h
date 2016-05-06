/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_ext.h
*
*  Project Code: VISPV100R007
*   Module Name: igmp  
*  Date Created: 2008-04-10
*        Author: zengshaoyang62531
*   Description: IGMP模块依赖其他模块的头文件集
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-10   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_EXT_H_
#define _IGMPV3_EXT_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*igmp依赖于dopra的头文件*/
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_intr.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"
#include "public/vrpvos/vrp_pktqueue.h"
#include "v_sm.h"
#include "public/dopra/waitlist.h"
#include "vos/vospubh/vos_util.h"
#include "tcpip/public/entry/tcpip_entry.h"

#include "tcpip/public/tcpip_log.h"
#include "tcpip/public/tcpip_debug.h"

/*infet*/
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/include/if_type.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "ifnet/core/include/if_cfg.h"


#include "tcpip/igmp4/include/igmpv3_api.h"
/*ip*/
#include "tcpip/ip4/am4/include/am4_api.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/core/include/am4_addr.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/ip4/pp4/core/include/pp4_input.h"
#include "tcpip/ip4/pp4/core/include/pp4_output.h"


/*arith cbb*/
#include "tcpip/public/arith_cbb/include/arith_ip.h"

#include "tcpip/public/tcpip_ha.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_err.h"

#include "tcpip/public/tcpip_ppi.h"

extern VOS_VOID   VOS_GetCpuTick( ULONG *plow,ULONG *phigh );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IGMPV3_EXT_H_ */

