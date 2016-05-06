/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_etharp.h
*
*  Project Code: VISPV100R006
*   Module Name: etharp  
*  Date Created: 2007-07-30
*        Author: zengshaoyang62531
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-30   zengshaoyang62531       Create
*
*******************************************************************************/

#ifndef _TCPIP_ETHARP_H_
#define _TCPIP_ETHARP_H_

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

/*etharp模块依赖的其他组件的头文件*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/shell/include/if_ic.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/socket4/core/include/macro.h"
/*#include "tcpip/socket4/core/include/sock_pub.h"*/
#include "tcpip/public/arith_cbb/include/arith_ip.h"

#include "tcpip/vlink/include/tcpip_vlink.h"
    
/*etharp模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/core/include/etharp_core_api.h"
#include "tcpip/etharp/core/include/ieth.h"
#include "tcpip/etharp/core/include/etharp_ha.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_ETHARP_H_ */

