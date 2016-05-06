/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_am4.h
*
*  Project Code: VISPV100R006
*   Module Name: AM4 
*  Date Created: 2007-07-30
*        Author: zengshaoyang62531
*   Description: am4模块对外声明的头文件,供用户使用am4模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-30   zengshaoyang62531       Create
*
*******************************************************************************/

#ifndef _TCPIP_AM4_H_
#define _TCPIP_AM4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"  
    
/* 对VRPVOS的头文件依赖 */
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

/*AM4模块依赖的其他组件的头文件*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/shell/include/if_ic.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/public/tcpip_ppi.h"

#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/core/include/etharp_core_api.h"
#include "tcpip/etharp/core/include/ieth.h"
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/select.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_err.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/arith_cbb/include/arith_ip.h"
    
/*AM4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/am4/core/include/am4_common.h"
#include "tcpip/ip4/am4/core/include/am4_addr.h"
#include "tcpip/ip4/am4/core/include/am4_cfg.h"
#include "tcpip/ip4/am4/core/include/am4_ha.h"

#include "tcpip/ppp/include/tcpip_ppp.h"
#include "tcpip/sfib4/include/sfib4_api.h"
#include "tcpip/sfib4/shell/include/sfib_sh_rm.h"
#include "tcpip/public/tcpip_pub_api.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_AM4_H_ */

