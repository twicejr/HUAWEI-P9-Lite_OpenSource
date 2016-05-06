/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifiba.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: Defines Component ID, and All Interface IDs for FIBAgent Component
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


#ifndef _IFIBA_H
#define _IFIBA_H


DECLARE_INTERFACE( IIF_COMP_FIBAGENT_ComIntFUN ) 
{
    IUNKNOWN_METHODS
        
    /* This method has to be used by RM for sending route message to FIB */
    METHOD_( ULONG, pfIP6_FIB_KRTMsgSend) (RTMSG6_S *pstRtMsg);
    METHOD_( ULONG, pfIP_FIB_KRTMsgSend) (RTMSG4_S *pstRtMsg);

    /* This method has to be used by FE for registering it's FIB download function with FIBAgent */
    METHOD_( ULONG, pfIP6_FIB_RegFENotify)(FE_DOWNLOAD_FUNC_SET_S *pfDownloadFIB6toFE);

    /* This method has to be used by IPV6 Stack to search for a route for forwarding */
    METHOD_( ULONG, pfIP6_FIB_AllocValid) (ROUTE6_S *pstRoute6, BOOL_T bEnableRouteBal);    
    METHOD_( ULONG, pfIP4_FIB_AllocValid) (ROUTE4_S *pstRoute4); 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG, pfIP4_GetIfIndexByDstIP)(ULONG ulDstIp,ULONG * pulOutIfIndex, ULONG ulVrfIndex);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG, pfIP_Search_VispFIB) (ROUTE4_S *pstRoute4);     
    METHOD_( ULONG, pfIP4_GetPMtuByFIB)(ULONG ulDstIp,ULONG *pulPMtu, ULONG ulVrfIndex);
};

DECLARE_INTERFACE( IIF_COMP_FIBAGENT_ComIntCFG )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_( ULONG , pfInit_Com ) (COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_( ULONG , pfActivate_Com ) ();
    METHOD_( ULONG , pfSetModuleInfo ) ( IP6_FIBAgent_MOD_INFO_S *pstMInfo );

};    

DECLARE_INTERFACE( IIF_COMP_FIBAGENT_ComIntSSA )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for functionality purpose */   
    METHOD_( ULONG , pfRegShellApi ) ( IP6_FIBAgent_SHELL_EV_CALLBACUP_SET_S *pstCallBkSet);
    
    METHOD_( VOID , pfRTMSG_Receive ) ();

    METHOD_( VOID , pfSetMemShortageFlag ) ();
};

/* For implement of QuerfyInstance() */
typedef struct tagFIBAINT_OBJ_S
{
    IIF_COMP_FIBAGENT_ComIntFUN  *pComIntFUN;
    IIF_COMP_FIBAGENT_ComIntCFG  *pComIntCFG;
    IIF_COMP_FIBAGENT_ComIntSSA  *pComIntSSA;
}IP_FIBAGENT_INT_OBJ_S;

#endif

#ifdef  __cplusplus
}
#endif

