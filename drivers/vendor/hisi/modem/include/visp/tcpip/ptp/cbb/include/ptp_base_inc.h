/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_basic_inc.h
*
*  Project Code: VISPV100R007
*   Module Name: PTP
*  Date Created: 2008-6-2
*        Author: yaochengliang
*   Description: BFD(CBB & Shell)模块的C文件包含的基本头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-6-2    yaochengliang       Create
*
*******************************************************************************/
#ifndef _PTP_BASE_INC_H_
#define _PTP_BASE_INC_H_

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************/
/* PTP Extern Header Files in Non-DataCom Enviroment (VISP)           */
/**********************************************************************/
/* VOS Basic Header Files */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_intr.h"

/*TCPIP DEBUG*/
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/entry/tcpip_entry.h"
/* Added by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
#include "tcpip/public/tcpip_basefun.h"

/* use VISP's new developed IFNET's headerfile */
#include "tcpip/ifnet/include/if_def.h"
#include "tcpip/ifnet/include/iifnet_inc.h"

#include "tcpip/public/ip_dmain.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/am4/include/iam4_inc.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/ip4/pp4/include/ipp4_inc.h"
#include "tcpip/ip4/pp4/core/include/pp4_input.h"

#include "public/entry/tcpip_entry.h" 

/* the new SFIB has not defined all needed types.
 * still need the old ip module head files
 */
#include "tcpip/ip4/vrpip/ip_pub.h"
#include "tcpip/sfib4/include/ifiba_inc.h"

#include "tcpip/icmp4/include/icmp_pub.h"
#include "tcpip/icmp4/include/icmp_core.h"
#include "tcpip/icmp4/include/iicmp_inc.h"


#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"

#include "tcpip/socket4/core/include/sock_comp.h"
#include "tcpip/socket4/core/include/isock.h"
#include "tcpip/socket4/core/include/macro.h"
#include "tcpip/socket4/core/include/sock_err.h"

#include "tcpip/udp4/core/include/udp.h"
#include "tcpip/udp4/core/include/udp_var.h"
#include "tcpip/udp4/core/include/udp_cmd.h"

#include "tcpip/public/tcpip_ppi.h"

extern VOS_UINT32 VOS_QueueGetMsgNum( VOS_UINT32 ulQueueId );

/*Add By t00110672  10-1-8支持路由器关于实现最新草案的需求 */
extern UCHAR g_ucKeepAliveMode;

/*Add by dutianyi 14-7-14 支持以G8275.1标准接收处理报文*/
extern ULONG g_ulG82751Mode;
/*End of adding*/

/* Added by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
extern ULONG PTP6_CheckIfIPV6Enable(VOID);

#ifdef __cplusplus
}
#endif

#endif
