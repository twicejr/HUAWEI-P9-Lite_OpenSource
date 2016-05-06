/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_ext.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-23
*        Author: LY(57500)
*   Description: DHCP4R模块需要的外部头文件及函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-23  LY(57500)     Create the first version.
*  2008-4-18  f54882        for A82D24952, Modify path of the waitlist.h
*
*******************************************************************************/

#ifndef _DHCP4R_EXT_H_
#define _DHCP4R_EXT_H_

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
#include "vos/vospubh/wlst_inc.h"

#include "tcpip/public/arith_cbb/include/arith_ip.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "tcpip/ifnet/include/if_type.h"

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/am4_core.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/tcp4/core/include/tcp.h"
#include "tcpip/udp4/core/include/udp.h"

#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"

#include "tcpip/dhcp4c/include/dhcp4c_api.h"
#include "tcpip/dhcp4c/core/include/dhcp4c_def.h"
#include "tcpip/dhcp4c/core/include/dhcp4c_type.h"

#include "tcpip/public/tcpip_ha.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_basefun.h"

#include "tcpip/sfib4/include/ifiba_inc.h"
#include "tcpip/sfib4/include/ifib4c_inc.h"
extern void * TCPIP_MemMove(void *pVoidDes,const void *pVoidSrc,ULONG ulLen);

#ifdef __cplusplus
}
#endif      /* end of __cplusplus       */

#endif      /* end of _DHCP4R_EXT_H_    */

