/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ipoa.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-08-01
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-08-01   wangbin (62223)         Create
*
*******************************************************************************/
#include "tcpip/public/tcpip_config.h"

#ifndef _TCPIP_IPOA_H_
#define _TCPIP_IPOA_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


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
#include "tcpip/public/vrpvos/vrp_pktqueue.h"
#include "tcpip/public/tcpip_pub_api.h"

#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/shell/include/if_ic.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"
#include "tcpip/ifnet/core/include/if_ha.h"

#include "tcpip/vlink/include/tcpip_vlink.h"

#include "tcpip/ipoa/include/ipoa_api.h"
#include "tcpip/ipoa/include/ipoa_def.h"
#include "tcpip/ipoa/include/ipoa_err.h"
#include "tcpip/ipoa/include/ipoa_type.h"
#include "tcpip/ipoa/include/ipoa_fun.h"
#include "tcpip/ipoa/include/ipoa_waitlist.h"

#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_basefun.h"

#include "tcpip/public/com_waitlist.h"


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TCPIP_IPOA_H_ */


