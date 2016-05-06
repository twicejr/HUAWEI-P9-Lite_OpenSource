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

#ifndef _VOS_INTR_H_
#define _VOS_INTR_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef  __cplusplus
extern "C" {
#endif


ULONG VOS_SplImp(LONG *plRetSpl);
ULONG VOS_SplX(LONG lSpl);


#ifdef  __cplusplus
}
#endif

#endif


