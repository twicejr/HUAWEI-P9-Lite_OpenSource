/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                          poec_basic_inc.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2005-09-15
 *        Author: zhukun
 *   Description: PPPoE Client模块的C文件包含的基本头文件
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE            NAME                DESCRIPTION
 *  2005-09-15      z36377              Create   
 *  2005-10-20      wanghui             Adjust
 *  2006-03-30      liai                Adjust for D00660
 *  2006/04/21      liai                Adjust for D00865
 *  2006-05-13      l48923              Delete useless code
 * 
 ************************************************************************/

#ifndef  _POEC_BASIC_INC_H_
#define  _POEC_BASIC_INC_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "tcpip/public/tcpip_config.h"

/**********************************************************************/
/* PPPoE Client Extern Header Files in Non-DataCom Enviroment (VISP)  */
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
#include "vos/vospubh/vos_tmr.h"

#include "public/vrpvos/vrp_pktqueue.h"
#include "public/entry/tcpip_entry.h" 
#include "public/tcpip_debug.h"

/* IFNET Basic Header Files */
#include "ifnet/include/iifnet_inc.h"
#include "ifnet/core/include/iifnet.h"
#include "ifnet/shell/include/if_ic.h" 

/* IPv4 Basic Header Files */
#include "ip4/am4/include/am4_pub.h"
#include "ip4/pp4/include/pp4_pub.h"

#include "tcpip/public/tcpip_ppi.h"

/* ETHARP Basic Header Files*/
#include "tcpip/etharp/include/etharp_api.h"
#include "etharp/core/include/etharp_pub_type.h"
#include "public/tcpip_ppi.h"
#include "etharp/core/include/ieth.h"

/* PPP Basic Header Files*/
#include "ppp/core/include/ppp_core_def.h"
#include "ppp/core_mp/include/mp_def.h"
#include "ppp/include/mp_api.h"
#include "ppp/core/include/ppp_core_type.h"
#include "ppp/core/include/ippp.h" 


/*********************************************************************/
/* PPPoE Client Inner Header Files in All Enviroment                 */
/*********************************************************************/
#include "pppoec/include/ipoec_inc.h"



#ifdef __cplusplus
}
#endif

#endif /* end of _POEC_BASIC_INC_H_ */

