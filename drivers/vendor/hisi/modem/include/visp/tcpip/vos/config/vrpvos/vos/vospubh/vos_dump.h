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

#ifndef _VOS_DUMP_H_
#define _VOS_DUMP_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif


#ifdef  __cplusplus
extern "C" {
#endif


#if (VRP_VERSION_RELEASE == VRP_YES)

VOID VOS_CallStack_Dump(VOID);
VOID VOS_Log_Dump(ULONG ulModuleID);
VOID VOS_Log_DumpAll(VOID);
VOID VOS_Exception_Dump(VOID);

#else /*For Debug version.*/

#define VOS_CallStack_Dump()\
	VOS_CallStack_Dump_X(__FILE__,__LINE__)
#define VOS_Log_Dump(ulModuleID) \
	VOS_Log_Dump_X(ulModuleID,__FILE__,__LINE__)
#define VOS_Log_DumpAll()\
	VOS_Log_DumpAll_X(__FILE__,__LINE__)
#define VOS_Exception_Dump()\
	VOS_Exception_Dump_X(__FILE__,__LINE__)

VOID VOS_CallStack_Dump_X(CHAR *pcFileName,ULONG ulLine);
VOID VOS_Log_Dump_X(ULONG ulModuleID,CHAR *pcFileName,ULONG ulLine);
VOID VOS_Log_DumpAll_X(CHAR *pcFileName,ULONG ulLine);
VOID VOS_Exception_Dump_X(CHAR *pcFileName,ULONG ulLine);

#endif


#ifdef  __cplusplus
}
#endif

#endif
