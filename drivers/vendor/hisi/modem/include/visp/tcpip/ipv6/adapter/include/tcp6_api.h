/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for TCP6
*    Version        : Initial Draft
*    File Name      : tcp6_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for TCP6
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _TCP6_API_H_
#define      _TCP6_API_H_

#ifdef      __cplusplus
extern "C"{
#endif

#define TCP6ADP_SHOWERRORINFO     VRP_YES
#define TCP6ADP_AUTOINIT          VRP_YES


#define TCP6ADP_OK                VOS_OK
#define TCP6ADP_ERR               VOS_ERR
#define TCP6ADP_DISPLAY(m_string) TCPIP_InfoOutput(m_string)
#define TCP6ADP_ERROR_STARTVALUE  0x100
#define TCP6ADP_ERROR_MAXVALUE    0xffffffff

/* Return Values */
typedef enum tagTCP6_ADP_ERRORNUM_E
{
    TCP6ADP_ERR_MEMBERFN_UNAVAILABLE = TCP6ADP_ERROR_STARTVALUE,
    TCP6ADP_ERR_INIT_NOTDONE,
    TCP6ADP_ERR_OPFAIL,
    TCP6ADP_ERR_INPUTINVALID,
    TCP6ADP_ERRORNUM_ULONG_PAD = TCP6ADP_ERROR_MAXVALUE
}TCP6_ADP_ERRORNUM_E;


/* Initialize TCP Component */
extern ULONG TCP6_InitAdapt();

/* Display TCP Statistics */
extern ULONG TCP6_DisplayStatistics();

/* Display TCP Connection Info */
extern ULONG TCP6_DisplayConnectionInfo();

/* Set / Reset TCP SYN Timeout Value */
extern ULONG TCP6_SetSynTimeOut(ULONG ulTCP6KeepIntvl, ULONG ulFlag);

/* Set / Reset FIN Timeout Value */
extern ULONG TCP6_SetFinTimeOut(ULONG ulTCP6KeepIntvl, ULONG ulFlag);

/* Set / Reset TCP Window Size */
extern ULONG TCP6_SetWindow(ULONG ulWindowSize, ULONG ulFlag);

/* Enable / Disable TCP6 debugs */
extern ULONG TCP6_DebugSwitch(ULONG ulFlag);

/* Set / Reset TCP6 Statistics */
extern ULONG TCP6_ResetStatistics();

/*Reset of TCP6 statistics per connection based on the connection info */
extern ULONG TCP6_ResetConnectionStatistics(TCP6CONNINFO_S *pstTCP6Conn);

/* Get TCP6 Connection statistics */
extern ULONG TCP6_GetConnectionStatistics(TCP6CONNINFO_S *pstTCP6ConnInfo,
                                                         TCP6PERCONNSTAT_S *pstPerTCP6Stats);

/*Display  of TCP6 statistics per connection based on the four tuple information */
extern ULONG TCP6_DisplayConnectionStatistics(CHAR *szLAddr, ULONG ulLPort,
                                                                       CHAR *szFAddr, ULONG ulFPort);

/* Display Per Connection based TCP6 statistics on Socket id and Task id */
extern ULONG TCP6_DisplayConnectionStatistics_Socket(ULONG ulSockId, ULONG ulTaskId);

/* Get First / Next Connection Object */
extern ULONG TCP6_Get_Object_Next(UINTPTR ulHandle, TCP6CONNPARAM_S * pstTcp6CB);

/* Close TCP6 Connection Object */
extern ULONG TCP6_CloseObject(UINTPTR ulHandle);

/* Open TCP6 Connection Object */
extern ULONG TCP6_OpenObject(ULONG ulMainType, UINTPTR *pulHandle);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _TCP6_API_H_ */

