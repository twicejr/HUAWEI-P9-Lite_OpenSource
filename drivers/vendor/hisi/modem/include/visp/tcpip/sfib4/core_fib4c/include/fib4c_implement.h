/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib4c_implement.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: This file contains the prototype declarations for the 
*               radix tree operation functions.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB4C_IMPLEMENT_H
#define _FIB4C_IMPLEMENT_H

#define  IPV4_RTWARN_LEVEL_INIT     10000


/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG SFIB_PPI_Update (ULONG ulCmd,ULONG ulVrfIndex,RT4_ENTRY_S *pstRtEntry);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

ULONG IP4_FIBImpl_RouteInit ();
ULONG IP4_FIBImpl_RouteAdd (RTMSG4_S *pstRtmsg);

/* Begin: Interface priority, chandra, 2012-12-26 */
ULONG IP4_FIBImpl_RouteRefresh(USHORT usZoneID, RT4_ENTRY_S *pstRouteEntry);
ULONG IP4_FIBImpl_Search_ByIfIndex(USHORT usZoneID, ULONG ulIfIndex);
/* End: Interface priority, chandra, 2012-12-26 */

ULONG IP4_FIBImpl_ClearZone ();
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP4_FIBImpl_ClearSpecZone(USHORT usZoneId);
ULONG IP4_FIB_GetBulkFIBData ( UINTPTR ulWaitListHandle,\
                               ULONG ulVrfIndex,\
                               ULONG ulNumOfEntryWanted,\
                               ULONG *pulNumOfEntryReturn,\
                               RT4_ENTRY_S **ppstFIBData);
ULONG IP4_FIB_OpenObject_FIB (UINTPTR *pulWaitListHandle,ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP4_FIB_CloseObject_FIB ( UINTPTR ulWaitListHandle );
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP4_FIB_GetRouteCount (ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

ULONG IP4_FIBImpl_RouteDel (RTMSG4_S *pstRtmsg);
ULONG IP4_FIBImpl_SearchBest (ROUTE4_S *pstRoute4, BOOL_T bEnableRoutBal);

ULONG IP4_FIB_RegRouteBalCTL(ULONG ulRouteBalMode);
VOID IP4_FIBImpl_RemoveDLLNode (USHORT usZoneID, RT4_ENTRY_S *pstRtDLLNode);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG SFIB4_SetRoutePolicy(ULONG ulZoneId,ULONG ulPolicy);
ULONG SFIB4_GetRoutePolicy(ULONG ulZoneId,ULONG *gulPolicy);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG SFIB4_SetHostRouteReserved(ULONG ulIfIndex, ULONG ulFlag);
ULONG SFIB4_GetHostRouteReserved(ULONG ulIfIndex, ULONG * pulFlag);


extern ULONG VOS_SYS_GetCurrentTime
(
    ULONG *pulRetDate, /*Y/M/D (31-16/15-8/7-0) */ 
    ULONG *pulRetTime, /*h/m/s (31-16/15-8/7-0) */ 
    ULONG *pulRetMillSec
);


#endif 

#ifdef  __cplusplus
}
#endif

