/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              idhcp4c.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module   
*  Date Created: 2004-05-19 
*        Author: tangcongfeng(36956)
*   Description: Defines Component ID, and All Interface IDs for DHCP4C Component 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                   DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-05-19 tangcongfeng(36956)     Creat the first version.
*
*******************************************************************************/

#ifndef _IDHCP4C_H_
#define _IDHCP4C_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/dhcp4c/include/idhcp4c_inc.h"

struct tagDHCP4C_DISPLAYINFO;

typedef struct  tagTCPIP_DHCP4C_MOD_INFO
{
    
    ULONG ulModID; /* Module id */
    ULONG ulDHCP4CTaskId;

    ULONG ulDHCP4CTimerQId;
    ULONG ulDHCP4CCmdQId;
    ULONG ulDHCP4CCntrlQId;
    ULONG ulDHCP4CSocketQId;
}DHCP4C_MOD_INFO_S;



/* shell function */
typedef struct tagDHCP4C_SH_CALLBACUP_SET_S
{
    ULONG (*pfDHCP4C_CreateTimer)(ULONG ulTaskId, 
                                  ULONG ulMsgQueId, 
                                  ULONG ulMillSec, 
                                  VOID ( *pfTimerFunc)(ULONG), 
                                  ULONG ulIfIndex, 
                                  ULONG *pulTimerId, 
                                  ULONG ulFlag);
    ULONG (*pfDHCP4C_AsynWriteQueue)(ULONG ulTaskId, ULONG ulQueueId, UINTPTR ulMsg [ 4 ], ULONG ulEvent);
    ULONG (*pfDHCP4CTimer_Delete)(ULONG * ulTimerId);
    VOID (*pfDHCP4CTimer_Resize)(ULONG ultimerID, ULONG ulNewMillSec);
    ULONG (*pfDHCP4C_LeaseWrite)(ULONG ulDelFlag, VOID * pBuf);

    ULONG (*pfDHCP4C_AddDefaultRouteToSfib)(ULONG ulIfIndex,ULONG ulGateway);
    ULONG (*pfDHCP4C_DelDefaultRouteToSfib)(ULONG ulIfIndex,ULONG ulGateway);
    
    VOID (*pfDHCP4C_SendDebugInfoToIC)(ULONG ulInfo, CHAR *szString);
}DHCP4C_SH_CALLBACUP_SET_S; 


DECLARE_INTERFACE(IIF_IPV4_DHCP4C_ComIntSSA)
{
    IUNKNOWN_METHODS
    METHOD_( ULONG , pfDHCP4C_RegShellApi ) ( DHCP4C_SH_CALLBACUP_SET_S * pstCallBkSet);

};

DECLARE_INTERFACE(IIF_IPV4_DHCP4C_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfDHCP4C_Init_Com)(VOID);
    METHOD_(ULONG, pfDHCP4C_DeInit_Com)(VOID);
    METHOD_(ULONG, pfDHCP4C_Activate_Com)();
    METHOD_(ULONG, pfDHCP4C_SetModuleInfo)(DHCP4C_MOD_INFO_S * pstMInfo);
    
    METHOD_(ULONG, pfDHCP4C_GetDhcpShowInfo)(struct tagDHCP4C_DISPLAYINFO *pstDhcp4cInfo, ULONG ulIfIndex);
    METHOD_(ULONG, pfDHCP4C_ProDbugFilter)(
                                    ULONG ulIfIndex,
                                    ULONG ulDHCP4CDebugNo,
                                    ULONG ulDHCP4CDebugType);
    METHOD_(ULONG, pfTCPIP_HA_SetDhcpDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfDHCP4C_HA_GetDhcpDbg)(ULONG *pulDbg);
    METHOD_(ULONG, pfDHCP4C_HA_SetDhcp4cVerboseDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfDHCP4C_HA_GetDhcp4cVerboseDbg)(ULONG *pulDbg);
    METHOD_(VOID,pfDHCP4C_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);

    METHOD_(ULONG, pfDHCP4C_SetTos)(UCHAR ucTos);
    METHOD_(ULONG, pfDHCP4C_GetTos)(UCHAR *pucTos);
    METHOD_(ULONG, pfDHCP4C_SetIgnoreOption)(ULONG ulSetYes);
    METHOD_(ULONG, pfDHCP4C_GetIgnoreOption)(ULONG *pulSetYes);
    
};


typedef struct tagDHCP4C_INT_OBJ_S
{
    IIF_IPV4_DHCP4C_ComIntSSA   * pComIntSSA;
    IIF_IPV4_DHCP4C_ComIntFun   * pComIntFun;  
    IIF_IPV4_DHCP4C_ComIntCFG   * pComIntCFG;

}DHCP4C_INT_OBJ_S;



#ifdef  __cplusplus
}
#endif

#endif

