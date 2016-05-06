/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_inc.h
*
*  Project Code: V2R3C06
*   Module Name:   
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: 基础头文件集合
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
#ifndef _LLDP_INC_H_
#define _LLDP_INC_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_config.h"


//#include "tcpip/public/entry/tcpip_entry.h"  //依赖于tcpip_entry.c

#include "dopra/vos/config/vrpvos/vos/vospubh/basetype.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_arg.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_lib.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_def.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_id.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_mem.h"
/*Added by guo00178934, 添加头文件,否则Win版本可能编译不过, 2011/11/8   问题单号:DTS2011110800968 */
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_util.h"
/* End of Added by guo00178934, 2011/11/10   问题单号:DTS2011110800968 */
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_ker.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_err.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/compbase.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/utldll.h"


#include "dopra/target/include/vrp_task.h"
#include "dopra/target/include/vrp_queue.h"
#include "v_sm.h"

#include "vos/vospubh/mbuf.h"  
#include "tcpip/public/tcpip_log.h"             /* 日志*/
#include "tcpip/public/tcpip_basefun.h"
#ifdef  __cplusplus
}
#endif

#endif

