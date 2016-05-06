/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ifnet.h
*
*  Project Code: VISPV100R006C02
*   Module Name: ifnet模块的对外头文件  
*  Date Created: 2007-07-28
*        Author: lijing(52889)
*   Description: 外部模块要使用ifnet特性，只需要包含该头文件即可
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-28   lijing(52889)           Create
*
*******************************************************************************/
#include "tcpip/public/tcpip_config.h"

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_IFNET_H
#define _TCPIP_IFNET_H

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/paf.h"

#include "vos/vospubh/compbase.h"

#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/shell/include/if_ic.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/include/if_type.h"
#include "tcpip/ifnet/core/include/if_vlink.h"
#include "tcpip/ifnet/include/if_pub.h"
#include "ifnet/shell/include/if_sh_fun.h"

#include "tcpip/public/tcpip_ppi.h"

#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/core/include/etharp_core_api.h"
#include "tcpip/etharp/core/include/ieth.h"  

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"

#include "tcpip/socket4/core/include/macro.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */

#include "public/entry/tcpip_entry.h"

#include "tcpip/public/tcpip_ha.h"

#include "tcpip/ifnet/include/if_def.h"
#include "tcpip/ifnet/include/if_pub.h"
#include "tcpip/ifnet/include/if_type.h"
#include "tcpip/ifnet/include/if_vos.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/if_cfg.h"
#include "tcpip/ifnet/core/include/if_dev.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "tcpip/ifnet/core/include/if_ha.h"
#include "tcpip/ifnet/core/include/if_index.h"
#include "tcpip/ifnet/core/include/if_init.h"
#include "tcpip/ifnet/core/include/if_ipc.h"
#include "tcpip/ifnet/core/include/if_que.h"
#include "tcpip/ifnet/core/include/if_tree.h"
#include "tcpip/ifnet/core/include/if_var.h"
#include "tcpip/ifnet/core/include/if_vlink.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#endif  /* end of _TCPIP_IFNET_H_ */

#ifdef  __cplusplus
}
#endif

