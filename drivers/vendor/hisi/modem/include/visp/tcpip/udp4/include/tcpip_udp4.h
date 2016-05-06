/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_udp4.h
*
*  Project Code: VISPV100R006C02
*   Module Name: udp4 
*  Date Created: 2007-07-31
*        Author: zhanghuihui(55157)
*   Description: udp4模块对外声明的头文件,供用户使用udp4模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   zhanghuihui(55157)      Create
*
*******************************************************************************/

#ifndef _TCPIP_UDP4_H_
#define _TCPIP_UDP4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h" 

/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"


/*UDP4模块依赖的其他组件的头文件*/
#include "tcpip/ip4/am4/include/am4_pub.h"


/*UDP4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/udp4/core/include/udp.h"
#include "tcpip/udp4/core/include/udp_cmd.h"
#include "tcpip/udp4/core/include/iudp.h"
#include "tcpip/udp4/include/udp_api.h"

#include "tcpip/public/tcpip_debug.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_UDP4_H_ */

