/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_basic_inc.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description: OSICP模块的C文件包含的基本头文件
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/

#ifndef _OSICP_BASIC_INC_H_
#define _OSICP_BASIC_INC_H_

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************/
/* OSICP Extern Header Files in Non-DataCom Enviroment (VISP)         */
/**********************************************************************/
/* VOS Basic Header Files */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_util.h" 
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_intr.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/wlst_inc.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"
#include "vos/vospubh/systrace.h"
#include "vos/vospubh/vos_time.h"
#include "v_sm.h"

#include "public/vrpvos/vrp_pktqueue.h"
#include "public/entry/tcpip_entry.h" 
#include "public/tcpip_debug.h"

/* IFNET Basic Header Files */
#include "ifnet/include/iifnet_inc.h"
#include "ifnet/core/include/iifnet.h"

/* IPv4 Basic Header Files */
#include "ip4/am4/include/am4_pub.h"
#include "ip4/pp4/include/pp4_pub.h"

#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_key.h"
#include "tcpip/socket4/core/include/sock_comp.h"
#include "tcpip/socket4/core/include/in_pcb.h"
#include "tcpip/socket4/core/include/sock_deb.h"
#include "tcpip/socket4/core/include/sock_var.h"

/* PPP Basic Header Files*/
#include "ppp/core/include/ppp_core_def.h"
#include "ppp/include/tcpip_mp.h"
#include "ppp/core_mp/include/mp_def.h"

#include "ppp/include/mp_api.h"
#include "ppp/core/include/ppp_core_type.h"
#include "ppp/core/include/ppp_core_fun.h"
#include "ppp/core/include/ippp.h" 


/*********************************************************************/
/* OSICP Inner Header Files in All Enviroment                       */
/*********************************************************************/
#include "ppp/include/iosicp_inc.h"


#ifdef __cplusplus
}
#endif
#endif /* end of _OSICP_BASIC_INC_H_ */
