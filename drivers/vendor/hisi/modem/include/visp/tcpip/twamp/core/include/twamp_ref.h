
#ifndef _TWAMP_REF_H_
#define _TWAMP_REF_H_

#ifdef __cplusplus
extern "C" {
#endif



extern VOID TWAMP_REF_TaskMain(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);




extern TWAMP_REFLECTOR_S * TWAMP_GetReflectorById(ULONG ulReflectorId);




extern TWAMP_REFLECTOR_S * TWAMP_GetReflectorByIPandVRF(ULONG ulIpaddr,ULONG ulVRF);




extern VOID  TWAMP_AttachReflector(TWAMP_REFLECTOR_S *pstReflector);



extern ULONG TWAMP_CreateSessionIDQueue(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflectorData,TWAMP_REFLECTOR_S *pstReflector);



extern ULONG TWAMP_Add_Reflector(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflectorData);


extern ULONG TWAMP_Del_Reflector(ULONG ulReflectorId);


extern ULONG TWAMP_ValidateReflectorConfig(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflData);



extern VOID TWAMP_ProcessReflectorListenFDSet(ULONG ulCount,fd_set * pstListenFDset);




extern VOID TWAMP_ProcessReflectorConnectionRequest(TWAMP_REFLECTOR_S *pstReflector);



extern VOID TWAMP_CTRL_SessionTableInsert(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);


extern VOID TWAMP_DestroyReflectorCtrlSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);



extern VOID TWAMP_UpdateSID(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
                                                               TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession);



extern VOID TWAMP_AttachTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
                                                               TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession);


extern USHORT TWAMP_GetSessionIdFromQueue(TWAMP_REFLECTOR_S *pstReflector);



extern VOID TWAMP_ReleaseSessionId(TWAMP_REFLECTOR_S *pstReflector,USHORT usSessionId);



extern USHORT TWAMP_GetPortFromPool(TWAMP_REFLECTOR_S *pstReflector,ULONG ulPeerIP);



extern LONG TWAMP_GetSETSockFD(fd_set * pstFDset);


extern VOID TWAMP_DelTestSession(TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession);





extern VOID TWAMP_NotifyCtrlSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession , ULONG ulState);



extern VOID TWAMP_NotifyTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
            TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession , ULONG ulState);


/*******************************************************************************
* Func Name: TWAMP_RefOnTimeOut
* Date Created: 2013-04-02
* Author: m70989
* Description: Timer will invoke this on when the particular client times out
*        Input:  ulId Identifier
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-02      m70989       Create first version
*******************************************************************************/
extern ULONG TWAMP_RefOnTimeOut(ULONG ulId);


extern VOID TWAMP_DelAllTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);



extern ULONG TWAMP_AddCTRLSession(TWAMP_REFLECTOR_S *pstReflector,LONG lChildSock,
                                                                ULONG ulPeerIP,USHORT usPeerPort);



extern TWAMP_REFLECTOR_CTRL_SESSION_S * TWAMP_CTRL_SessionTableSearch(LONG lSockfd);



extern ULONG TWAMP_Restart_Reflector(ULONG ulReflectorId);

extern VOID * TWAMP_GetNextSession( VOID *pParam,VOID **ppList);

extern VOID TWAMP_ProcessReflectorCtrlConnection(LONG lsockfd);

extern VOID TWAMP_FreeReflectorSockOpt(TCPIP_TWAMP_SOCK_OPTIONS_S *pstSockOptData,ULONG ulSockOptNum);

extern TCPIP_TWAMP_SOCK_OPTIONS_S * TWAMP_AllocateReflectorSockOpt(TCPIP_TWAMP_REFL_CONFIG_S *pstConf, ULONG *pulTotalSockOptionsSizeforHA);

extern VOID TWAMP_ProcessStopSessionFDSet(void);




#ifdef __cplusplus
}
#endif

#endif

