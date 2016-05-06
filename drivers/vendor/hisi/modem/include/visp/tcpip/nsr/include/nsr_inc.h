/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_inc.h
*
*  Project Code: Dopra V3R2
*   Module Name: 该头文件主要包含了Dopra和TCPIP相关的基础头文件  
*  Date Created: 2013-09-25
*        Author: guojianjun178934
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-09-25   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_INC_INCLUDED
#define NSR_INC_INCLUDED

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_config.h"

#include "dopra/vos/config/vrpvos/vos/vospubh/basetype.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_lib.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_def.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_id.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_mem.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_ker.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/vos_err.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/compbase.h"
#include "dopra/vos/config/vrpvos/vos/vospubh/utldll.h"

#include "vos/vospubh/vos_tmr.h"

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

