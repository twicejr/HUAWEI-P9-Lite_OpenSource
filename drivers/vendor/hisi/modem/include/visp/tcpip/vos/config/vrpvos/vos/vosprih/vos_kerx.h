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


#ifndef _VOS_KERX_H_
#define _VOS_KERX_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagHouseKeeper{
	CHAR hk_cName[4];
	ULONG hk_ulEvent;
}HOUSEKEEPER_S;



#if (VRP_VERSION_DEBUG == VRP_YES)
#define VOS_DBGOUTPRINTF VOS_OutPrintf
#else
#define VOS_DBGOUTPRINTF (1)?(VOID)0:VOS_OutPrintf
#endif

#if (VRP_VERSION_DEBUG == VRP_YES)
#define VOS_REGCALLSTACK(pcFileName,ulLine,pFuncAddr)
#else
#define VOS_REGCALLSTACK(pcFileName,ulLine,pFuncAddr)
#endif



#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of _VOS_KERX_H_ */


