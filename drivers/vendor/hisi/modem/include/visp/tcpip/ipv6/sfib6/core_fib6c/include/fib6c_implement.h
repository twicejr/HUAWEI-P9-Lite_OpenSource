/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib6c_implement.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2004-07-08
*       Author: Zhang Hongyan
*  Description: This file contains the prototype declarations for the 
*               fib6c operation functions.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB6C_IMPLEMENT_H
#define _FIB6C_IMPLEMENT_H

extern ULONG VOS_time(ULONG *pulSecond);

ULONG SFIB6_PPI_Update (ULONG ulCmd,RT6_ENTRY_S *pstRt6Entry);

ULONG IP6_FIBImpl_RouteInit ();
ULONG IP6_FIBImpl_RouteAdd (RTMSG6_S *pstRtmsg);
ULONG IP6_FIBImpl_ClearZone (USHORT usZoneId);
ULONG IP6_FIB_GetBulkFIBData (USHORT usZoneID,\
                              UINTPTR ulWaitListHandle,\
                              ULONG ulNumOfEntryWanted,\
                              ULONG *pulNumOfEntryReturn,\
                              RT6_ENTRY_S **ppstFIBData);

ULONG IP6_FIB_OpenObject_FIB (UINTPTR *pulWaitListHandle, USHORT usZoneID);
ULONG IP6_FIB_CloseObject_FIB ( UINTPTR ulWaitListHandle );
ULONG IP6_FIB_GetRouteCount (USHORT usZoneId);

ULONG IP6_FIB_RegRouteBalCTL(ULONG ulRouteBalMode);
VOID  IP6_FIBImpl_RemoveDLLNode (USHORT usZoneID, RT6_ENTRY_S *pstRtDLLNode);

ULONG IP6_FIBImpl_RouteDel (RTMSG6_S *pstRtmsg);
ULONG IP6_FIBImpl_SearchBest (ROUTE6_S *pstRoute6, BOOL_T bEnableRouteBal);

ULONG SFIB6_SetHostRouteReserved(ULONG ulIfIndex, ULONG ulFlag);
ULONG SFIB6_GetHostRouteReserved(ULONG ulIfIndex, ULONG * pulFlag);
ULONG SFIB6_HostRouteReservedCheck(ULONG ulIfIndex, ULONG ulFlag);
ULONG DclRtm6_SetHostRouteReserved(ULONG ulIfIndex, ULONG ulFlag);
ULONG SFIB6_HostRtShouldReserve(UCHAR ucAddress[]);
ULONG SFIB6_HostRtReserveI3Proc(VOID * pData);
ULONG SFIB6_HostRtReserveI3AddrProc(SFIB_AM6_MSG_S *pMsg, VOID *pData);

extern ULONG  g_ulFib6MaxZoneNum;

#endif 

#ifdef  __cplusplus
}
#endif

