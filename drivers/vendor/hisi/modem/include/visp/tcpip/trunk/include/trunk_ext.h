/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_ext.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块需要的外部头文件及函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/


#ifndef _TRUNK_EXT_H_
#define _TRUNK_EXT_H_

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

#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/tcp4/core/include/tcp.h"
#include "tcpip/udp4/core/include/udp.h"

#include "tcpip/socket4/core/include/macro.h"
/*#include "tcpip/socket4/core/include/sock_pub.h" */
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"

#include "ipv6/ppmng/core/include/ppmng_pub.h"
#include "tcpip/ipv6/socket6/core/include/sock6_pub.h" 

#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "common/ipos/ipv6/basic/addrmng/addr_public.h"

#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/public/tcpip_ha.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/public/tcpip_hdr.h"

#include "tcpip/dhcp4r/include/tcpip_dhcp4r.h"
#include "tcpip/3ah/include/tcpip_3ah.h"
#include "tcpip/1ag/include/tcpip_1ag.h"
#include "tcpip/synce/include/tcpip_synce.h"

#include "bfd/cbb/include/bfd_inc.h"
#include "tcpip/public/debug/tcpip_pcap.h"

/*添加NSR功能相关的头文件*/
#include "tcpip/nsr/include/nsr_api.h"
#include "tcpip/nsr/include/nsr_common.h"
#include "tcpip/nsr/include/insr.h"


extern ULONG TCPIP_ADP_GetMacAddress(ULONG ulTrunkId, UCHAR* pucMacAddr);
extern VOID TCPIP_ADP_FreeMacAddress(ULONG ulTrunkId, UCHAR* pucMacAddr);
extern IFNET_S * IF_GetIfByFullName(CHAR * szFull);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_EXT_H_ */

