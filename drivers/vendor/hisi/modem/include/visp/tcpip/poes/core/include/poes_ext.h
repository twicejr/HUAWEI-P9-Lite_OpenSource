/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_ext.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES模块的外部头文件和外部函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_EXT_H_
#define  _POES_EXT_H_

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
#include "tcpip/ifnet/core/include/if_func.h"


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
/*#include "tcpip/socket4/core/include/sock_pub.h"*/
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"

#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/public/tcpip_ha.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/public/dopra/waitlist.h"



extern ULONG TCPIP_HA_CanSendPack(ULONG ulModeId);
extern ULONG TCPIP_HA_ModuleSendMsg(UCHAR *pucMsg, ULONG ulMsgLen);

/* 全局信号量 */
extern ULONG g_ulSemForTightMods;

#ifdef __cplusplus
}
#endif

#endif

