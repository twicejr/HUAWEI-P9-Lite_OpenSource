/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_ext.h
*
*  Project Code: 
*   Module Name: PTPV2 type
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi 
*   Description: 主要提供给产品以及CBB自己调用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_EXT_h_
#define _PTPV2_EXT_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"
//#include "tcpip/public/tcpip_basefun.h"

#include "vos/vospubh/basetype.h"
#include "public/arith_cbb/include/mbuf.h"
#include "vos/vospubh/utldll.h"
#include "tcpip/public/arith_cbb/include/avltree.h"
#include "vos/vospubh/vos_ker.h"

#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_log.h"
#include "tcpip/public/tcpip_basefun.h"

#include "dopra/target/include/vrp_queue.h"
#include "dopra/target/include/vrp_timer.h"
#include "dopra/target/include/vrp_task.h"
#include "dopra/target/include/vrp_event.h"
#include "dopra/target/include/vrp_systime.h"

#include "tcpip/ptpv2/include/tcpip_ptpv2_api.h"
#include "tcpip/ptpv2/include/ptpv2_def.h"
#include "tcpip/ptpv2/include/ptpv2_type.h"
#include "tcpip/ptpv2/include/ptpv2_var.h"

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _PTPV2_EXT_h_ */



