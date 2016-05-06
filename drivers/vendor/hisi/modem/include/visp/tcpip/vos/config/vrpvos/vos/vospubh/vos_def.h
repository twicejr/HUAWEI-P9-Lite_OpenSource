/************************************************************************
 *                                                                      *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/25                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/

#ifndef _VOS_DEF_H_
#define _VOS_DEF_H_

#include "dopra_def.h"

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif


#ifdef  __cplusplus
extern "C" {
#endif

#ifdef TCPIP_DOPRA_V2    /*如用户需要使用Doprav2,则VISP与Dopra版本保持强依赖关系,需要包含Dopra头文件*/

#include "vrp_systime.h"
#include "vrp_queue.h"
#include "vrp_sema4.h"
#include "vrp_event.h"
#include "vrp_timer.h"
#else /* 和旧版本保持一致 */

#include "dopra/target/include/vrp_systime.h"
#include "dopra/target/include/vrp_queue.h"
#include "dopra/target/include/vrp_sema4.h"
#include "dopra/target/include/vrp_event.h"
#include "dopra/target/include/vrp_timer.h"

#endif


/*yuqinyun added for IAS and for VRP*/
#ifndef HIWORD
#define HIWORD(x)                   ((x) >> 16)
#endif

#ifndef LOWORD
#define LOWORD(x)               ((x) & 0x0000FFFF)
#endif


#ifndef     DEBUG_TRACE
#define     DEBUG_TRACE VOS_OutPrintf /*Change later.*/
#endif
#define     TRACE VOS_OutPrintf

#ifdef  __cplusplus
}
#endif

#endif


