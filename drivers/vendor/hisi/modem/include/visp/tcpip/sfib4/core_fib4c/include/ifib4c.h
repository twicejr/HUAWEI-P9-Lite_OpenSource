/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifib4c.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-22
*       Author: Zhang Hongyan
*  Description: Defines Component ID, and All Interface IDs for FIBContainer Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-22   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IFIB4C_H
#define _IFIB4C_H 


#include "tcpip/public/tcpip_id.h"

DECLARE_INTERFACE( IIF_IPV4_FIBCONTR_ComIntFUN ) 
{
    IUNKNOWN_METHODS  
};

DECLARE_INTERFACE( IIF_IPV4_FIBCONTR_ComIntFIBA ) 
{
    IUNKNOWN_METHODS

    /* This method is used by FIBAgent for adding/deleteing routes */
    METHOD_( ULONG, pfIP4_FIB_Request) (RTMSG4_S* pstMsg);

    /* This method is used by FIBAgent for searched a route in 
    FIB, for fwding */
    METHOD_( ULONG, pfIP4_AllocValid) (ROUTE4_S *pstRoute4);

    /* These three methods are used by FIBAgent for getting FIB entries for download purpose */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG, pfGetBulkFIBData) (
                                       UINTPTR  ulWaitlistIndex,
                                       ULONG ulVrfIndex,
                                       ULONG  ulNumOfEntryWanted,
                                       ULONG *pulNumOfEntryReturn,
                                       RT4_ENTRY_S **pastFIBData
                                      );
    METHOD_(ULONG, pfOpenObject_FIB) ( UINTPTR * pulWaitlLstId_DisplayMain,ULONG ulVrfIndex);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfCloseObject_FIB) ( UINTPTR ulWaitlLstId_DisplayMain);
    
};

DECLARE_INTERFACE( IIF_IPV4_FIBCONTR_ComIntCFG )
{
    IUNKNOWN_METHODS

    METHOD_( ULONG , pfInit_Com )(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_( ULONG , pfActivate_Com )( );
    METHOD_( ULONG , pfSetModuleInfo )( IP4_FIBContainer_MOD_INFO_S *pstMInfo );    
    METHOD_( ULONG , pfRegShellApi )( IP4_FIBContainer_SHELL_EV_CALLBACUP_SET_S *pstCallBkSet);
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG , pfFIB4C_SetRoutePolicy )(ULONG ulZoneId,ULONG ulPolicy);
    METHOD_( ULONG , pfSFIB4_GetRoutePolicy )(ULONG ulZoneId,ULONG *gulPolicy);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG , pfSFIB4_SetHostRouteReserved)(ULONG ulIfIndex, ULONG ulFlag);
    METHOD_( ULONG , pfSFIB4_GetHostRouteReserved)(ULONG ulIfIndex, ULONG *pulFlag);
};

DECLARE_INTERFACE( IIF_IPV4_FIBCONTR_ComIntSSA )
{
    IUNKNOWN_METHODS

    /* This method is used by FIBAgent Shell for getting FIB entries for
    display purpose */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG, pfGetBulkFIBData)(
                                      UINTPTR pulWaitlistIndex,
                                      ULONG ulVrfIndex,
                                      ULONG ulNumOfEntryWanted,
                                      ULONG *pulNumOfEntryReturn,
                                      RT4_ENTRY_S **pastFIBData
                                      );
    METHOD_(ULONG, pfOpenObject_FIB) ( UINTPTR * pulWaitlLstId_DisplayMain,ULONG ulVrfIndex);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfCloseObject_FIB) ( UINTPTR ulWaitlLstId_DisplayMain);

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfGetRouteCount) (ULONG ulVrfIndex);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    METHOD_(ULONG, pfRegRouteBalCTL) (ULONG ulRouteBalMode);
};


/* For implement of QuerfyInstance(); */
typedef struct tagFIB4_INT_CONTR_OBJ_S
{
    IIF_IPV4_FIBCONTR_ComIntFUN    *pComIntFUN;
    IIF_IPV4_FIBCONTR_ComIntFIBA   *pComIntFIBA;
    IIF_IPV4_FIBCONTR_ComIntCFG    *pComIntCFG;
    IIF_IPV4_FIBCONTR_ComIntSSA    *pComIntSSA;
}IPV4_FIBCONTR_INT_OBJ_S;

ULONG IP4_FIBCONTR_QueryInterface (IUnknown * This, COMP_IID iid, LPVOID *ppvObj);



#ifdef  __cplusplus
}
#endif

#endif  /* _IFIB4C_H */

