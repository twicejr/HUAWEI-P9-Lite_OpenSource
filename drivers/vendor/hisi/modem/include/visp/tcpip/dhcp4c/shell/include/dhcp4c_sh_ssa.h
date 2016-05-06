/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_sh_ssa.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module 
*  Date Created: 2004-05-27
*        Author: Tang Congfeng(36956)
*   Description: Shell SSA implement header file for DHCP4C4 module 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-05-27  Tang Congfeng(36956)         Creat the first version.
*
*******************************************************************************/

#ifndef _DHCP4C_SH_SSA_H_
#define _DHCP4C_SH_SSA_H_

#ifdef  __cplusplus
extern "C"{
#endif

ULONG DHCP4C_AsynWriteQueue (ULONG ulTastId, ULONG ulQueueId, UINTPTR ulMsg[4], ULONG ulEvent);
ULONG DHCP4C_CreateTimer(
                                    ULONG ulTastId,
                                    ULONG ulMsgQueId,
                                    ULONG ulMillSec,
                                    VOID  (*pfTimerFunc)(ULONG),
                                    ULONG ulIfIndex,
                                    ULONG *pulTimerId,
                                    ULONG ulFlag
                                                );
VOID DHCP4C_AddLeaseNode(DHCP4C_LEASE_S *pstLease);
VOID DHCP4C_LeaseRead();
ULONG DHCP4C_LeaseWrite(ULONG ulDelFlag, VOID * pBuf);
ULONG DHCP4CTimer_Delete( ULONG * ulTimerId );
VOID DHCP4CTimer_Resize(ULONG ultimerID, ULONG ulNewMillSec);

ULONG DHCP4C_AddDefaultRouteToSfib(ULONG ulIfIndex, ULONG ulGateway);
ULONG DHCP4C_DelDefaultRouteToSfib(ULONG ulIfIndex, ULONG ulGateWay);

#ifdef  __cplusplus
}
#endif

#endif

