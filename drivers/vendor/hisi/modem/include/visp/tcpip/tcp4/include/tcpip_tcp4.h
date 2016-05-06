/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_tcp4.h
*
*  Project Code: VISPV100R006C02
*   Module Name: tcp4  
*  Date Created: 2007-7-31
*        Author: l48923(48923)
*   Description: tcp4 header for user
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2007-7-31   l48923(48923)    Create the first version.
*
*******************************************************************************/

#ifndef  _TCPIP_TCP4_H_
#define  _TCPIP_TCP4_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "tcpip/public/tcpip_config.h" 

/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"

/*TCP4模块依赖的其他组件的头文件*/
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/socket4/core/include/sock_com.h"

/*TCP4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/tcp4/core/include/tcp.h"
#include "tcpip/tcp4/core/include/tcp_cmd.h"
#include "tcpip/tcp4/core/include/tcp_time.h"
#include "tcpip/tcp4/core/include/tcp_fsm.h"
#include "tcpip/tcp4/core/include/tcp_var.h"
#include "tcpip/tcp4/core/include/tcp_ha.h"
#include "tcpip/tcp4/core/include/itcp.h"
#include "tcpip/tcp4/shell/include/tcp_sh_cfg.h"
#include "tcpip/tcp4/include/tcp_api.h"

#include "tcpip/public/tcpip_debug.h"

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */
    
#endif  /* end of _TCPIP_TCP4_H_ */

