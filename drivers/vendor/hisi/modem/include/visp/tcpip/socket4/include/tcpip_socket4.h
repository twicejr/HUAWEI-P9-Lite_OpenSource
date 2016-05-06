/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_socket4.h
*
*  Project Code: VISPV100R006C02
*   Module Name: socket4 
*  Date Created: 2007-08-20
*        Author: X36317
*   Description: socket4模块对外声明的头文件,供用户使用socket4模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-08-20   X36317       Create
*  2007-09-19   y62007       modify for A82D20237 头文件归一
*  2008-01-16   w60786       Modify for A82D22480
*******************************************************************************/

#ifndef _TCPIP_SOCKET4_H_
#define _TCPIP_SOCKET4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"  
    
/* 对VRPVOS的头文件依赖 */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"


/*socket4模块依赖的其他组件的头文件*/
#include "tcpip/ip4/am4/include/am4_pub.h"
#include "tcpip/ip4/pp4/include/pp4_pub.h"
#include "tcpip/ip4/pp4/core/include/pp4_input.h"
#include "tcpip/public/arith_cbb/include/arith_ip.h"

    
/*socket4模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tcpip/socket4/core/include/sock_com.h"
#include "tcpip/socket4/core/include/in_pcb.h"
#include "tcpip/socket4/core/include/sock_err.h"
#include "tcpip/socket4/core/include/sock_pub.h"
#include "tcpip/socket4/core/include/sock_deb.h"
#include "tcpip/socket4/core/include/sock_var.h"
#include "tcpip/socket4/core/include/isock.h"
#include "tcpip/socket4/core/include/asynsock.h"
#include "tcpip/socket4/core/include/select.h"
#include "tcpip/socket4/core/include/uio.h"
#include "tcpip/socket4/core/include/sock.h"
#include "tcpip/socket4/shell/include/sock_sh_cfg.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */
    
#endif  /* end of _TCPIP_SOCKET4_H_ */

