/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_trrt.h
*
*  Project Code: VISPV100R006
*   Module Name: trrt  
*  Date Created: 2007-08-20
*        Author: X36317
*   Description: trrt模块对外声明的头文件,供用户使用trrt模块包含使用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-08-20   X36317                Create
*  2007-09-19   y62007                modify A82D20213 for 头文件包含路径错误，致使编译不能通过。
*******************************************************************************/

#ifndef _TCPIP_TRRT_H_
#define _TCPIP_TRRT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"

/* 对VRPVOS的头文件依赖 */
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

/*trrt模块依赖的其他组件的头文件*/
#include "tcpip/ip4/am4/include/tcpip_am4.h"
#include "tcpip/socket4/include/tcpip_socket4.h"    

/*trrt模块对外开放的宏、数据结构定义、组件接口定义*/
#include "tracert/include/trrt_api.h"
#include "tracert/include/trrt_pub.h"
#include "tracert/include/itrrt_inc.h"
#include "tracert/include/trrt_ext.h"
#include "tracert/shell/include/trrt_sh_info.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_TRRT_H_ */

