/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ipv6.h
*
*  Project Code: V1.1.0
*   Module Name: IPV6
*  Date Created: 2010-2-4
*        Author: w60786
*   Description: VISP给用户提供的统一IPV6头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2010-2-4     w60786           Creat the first version.
*
*******************************************************************************/

#ifndef  _TCPIP_IPV6_H_
#define  _TCPIP_IPV6_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*******************************************************************************
*  产品使用说明:
*  1. 产品只使用ipv4功能时,只需要包含tcpip.h即可;
*  2. 产品需要使用ipv6功能时,必须先包含tcpip.h头文件,再包含tcpip_ipv6.h头文件;
*******************************************************************************/

/* 修改该文件时需注意,要保证单独包含tcpip_ipv6.h文件时可以编译通过 */
/* Add for DTS2011120204259, by zhaoyue00171897, at 2011-12-02. 修改原因: 增加acl6头文件 */
#include "tcpip/public/tcpip_basetype.h"
#include "tcpip/public/vrpvos/mbuf.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/ipv6/ppmng/include/ppmng_api.h"
#include "tcpip/acl6/include/acl6_cbb_api.h"
#include "tcpip/acl6/include/acl6_api.h"

#include "tcpip/public/dopra_cbb/include/utlsll.h"

#include    "common/ipos/ipv6/ip6_pub.h"
#include    "common/ipos/ipv6/raw_ip6_public.h"

#include    "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include    "common/ipos/ipv6/basic/addrmng/addr_public.h"
#include    "common/ipos/ipv6/basic/nd/nd_public.h"
#include    "common/ipos/ipv6/basic/pathmtu/pmtu_public.h"

#include    "common/ipos/ipv6/ipv6_ppi.h"
#include    "common/ipos/ipv6/tcp6_public.h"

#include    "common/ipos/adapter/addr_api.h"
#include    "common/ipos/adapter/icmpv6_api.h"
#include    "common/ipos/adapter/nd_api.h"
#include    "common/ipos/adapter/pmtu_api.h"
#include    "common/ipos/adapter/rawip6_api.h"
#include    "common/ipos/adapter/tcp6_api.h"
#include    "common/ipos/adapter/udp6_api.h"

/* 未包含算法和dopra CBB的对外头文件，因为可能和dopra的头文件冲突,请根据需要自行包含 */

#ifdef __cplusplus
}
#endif

#endif 

