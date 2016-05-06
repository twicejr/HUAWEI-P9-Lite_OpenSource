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
#ifndef _VOS_ERR_H_
#define _VOS_ERR_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef __cplusplus
extern "C"{
#endif

#include "v_typdef.h"
#include "v_modNum.h"
#include "v_queue.h"

#define VOS_ERR_NULLPTR                 20

#define VOS_SYS_ERR_PARA_ILLEGAL        24
#define VOS_QUE_ERR_NO_SPACE            0x00000002

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _VOS_ERR_H_ */
