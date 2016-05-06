/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifib6c.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2003-07-22
*       Author: Zhang Hongyan
*  Description: Defines Component ID, and All Interface IDs for FIBContainer Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-22   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/

#include "tcpip/public/tcpip_config.h"

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IFIB6C_H
#define _IFIB6C_H 

#include "vos/vospubh/compbase.h"
#include "vos/vospubh/iunknown.h"

DECLARE_INTERFACE( IIF_IPV6_FIBCONTR_ComIntFUN ) 
{
    IUNKNOWN_METHODS  

    /* This method has to be used by IPv6 stack or FE */
    METHOD_( VOID, pfNotifyCache) (ROUTE6_S *pstRoute6);
};

DECLARE_INTERFACE( IIF_IPV6_FIBCONTR_ComIntFIBA ) 
{
    IUNKNOWN_METHODS

    /* This method is used by FIBAgent for adding/deleteing routes */
    METHOD_( ULONG, pfIP6_FIB_Request) (RTMSG6_S* pstMsg);

    /* This method is used by FIBAgent for searched a route in FIB, for fowarding */
    METHOD_( ULONG, pfIP6_AllocValid) (ROUTE6_S *pstRoute6, BOOL_T bEnableRouteBal);

    /* These three methods are used by FIBAgent for getting FIB entries for download purpose */
    METHOD_( ULONG, pfGetBulkFIBData) ( USHORT usZoneID,
                                        UINTPTR  ulWaitlistIndex,
                                        ULONG  ulNumOfEntryWanted,
                                        ULONG *pulNumOfEntryReturn,
                                        RT6_ENTRY_S **pastFIBData
                                      );
    METHOD_(ULONG, pfOpenObject_FIB) ( UINTPTR * pulWaitlLstId_DisplayMain,USHORT usZone);
    METHOD_(ULONG, pfCloseObject_FIB) ( UINTPTR ulWaitlLstId_DisplayMain);
    METHOD_(ULONG, pfGetRouteCount) ( USHORT usZoneId);
    METHOD_(ULONG, pfIP6_HostRtReserve)(UCHAR ucAddress[]);    
    METHOD_(ULONG, pfIP6_HostRtReserveI3Proc)(VOID * pData);  
    METHOD_(ULONG, pfIP6_HostRtReserveI3AddrProc)(SFIB_AM6_MSG_S *pMsg, VOID *pData);  
};

DECLARE_INTERFACE( IIF_IPV6_FIBCONTR_ComIntCFG )
{
    IUNKNOWN_METHODS

    METHOD_( ULONG , pfInit_Com )(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_( ULONG , pfActivate_Com )( );
    METHOD_( ULONG , pfSetModuleInfo )( IP6_FIBContainer_MOD_INFO_S *pstMInfo );    
    METHOD_( ULONG , pfRegShellApi )( IP6_FIBContainer_SHELL_EV_CALLBACUP_SET_S *pstCallBkSet);
    METHOD_(ULONG, pfSFIB6_RM_RtTblInit)(ULONG ulZoneId);
    METHOD_(VOID, pfSFIB6_RM_RtTblClr)(ULONG ulZoneId);
};

DECLARE_INTERFACE( IIF_IPV6_FIBCONTR_ComIntSSA )
{
    IUNKNOWN_METHODS

    /* This method is used by FIBAgent Shell for getting FIB entries for display purpose */
    METHOD_( ULONG, pfGetBulkFIBData)( USHORT usZoneID,
                                       UINTPTR pulWaitlistIndex,
                                       ULONG ulNumOfEntryWanted,
                                       ULONG *pulNumOfEntryReturn,
                                       RT6_ENTRY_S **pastFIBData
                                      );
    METHOD_(ULONG, pfOpenObject_FIB) ( UINTPTR * pulWaitlLstId_DisplayMain,USHORT usZone);
    METHOD_(ULONG, pfCloseObject_FIB) ( UINTPTR ulWaitlLstId_DisplayMain);

    METHOD_(ULONG, pfGetRouteCount) ( USHORT usZoneId);

    METHOD_(ULONG, pfRegRouteBalCTL) (ULONG ulRouteBalMode);
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    /* METHOD_(VOID ,pfSFIB6_LinkTrap)(ULONG ulIfIndex, ULONG ulCmd ); */
    METHOD_(VOID ,pfSFIB6_LinkTrap)(ULONG ulVrfIndex,  ULONG ulIfIndex, ULONG ulCmd );
    METHOD_(VOID ,pfSFIB6_LinkCfg)(ULONG ulVrfIndex,  ULONG ulIfIndex, ULONG ulCmd );
    /* End:VISP V3R2C10 VRF chandra , 2014-03-18 */
};

/* For implement of QuerfyInstance(); */
typedef struct tagINT_CONTR_OBJ_S
{
    IIF_IPV6_FIBCONTR_ComIntFUN  *pComIntFUN;
    IIF_IPV6_FIBCONTR_ComIntFIBA *pComIntFIBA;
    IIF_IPV6_FIBCONTR_ComIntCFG  *pComIntCFG;
    IIF_IPV6_FIBCONTR_ComIntSSA  *pComIntSSA;
}IPV6_FIBCONTR_INT_OBJ_S;

ULONG IP6_FIBCONTR_QueryInterface(IUnknown * This, COMP_IID iid, LPVOID *ppvObj);

#ifdef  __cplusplus
}
#endif

#endif  /* _IFIB6C_H */

