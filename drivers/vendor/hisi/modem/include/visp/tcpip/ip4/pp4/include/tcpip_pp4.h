/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pp4.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PP4
*  Date Created: 2007-07-31
*        Author: jiangtao(51916)
*   Description: PP4模块对外声明的头文件,供用户使用PP4模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   jiangtao(51916)         Create
*
*******************************************************************************/

#ifndef _TCPIP_PP4_H_
#define _TCPIP_PP4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"

/* 对dopra的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/vos_task.h"

/*PP4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/public/ip_dmain.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/pp4/include/pp4_core.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/ip4/pp4/core/include/pp4_cfg.h"
#include "tcpip/ip4/pp4/include/ipp4_inc.h"
#include "tcpip/ip4/pp4/core/include/pp4_intermediate.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_debug.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_PP4_H_ */
