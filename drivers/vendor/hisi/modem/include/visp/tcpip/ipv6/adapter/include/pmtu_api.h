/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for PMTU
*    Version        : Initial Draft
*    File Name      : pmtu_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for PMTU
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _PMTU_API_H_
#define      _PMTU_API_H_

#ifdef      __cplusplus
extern "C"{
#endif

#define PMTUADP_SHOWERRORINFO     VRP_YES
#define PMTUADP_AUTOINIT          VRP_YES


#define PMTUADP_OK                VOS_OK
#define PMTUADP_ERR               VOS_ERR

#define PMTUADP_ERROR_STARTVALUE  0x700
#define PMTUADP_ERROR_MAXVALUE    0xffffffff


/* Type of PMTU Entries */
typedef enum tagPMTUADP_ENTRYTYPE_E
{
    PMTU_DISPLAY_ALL,
    PMTU_DISPLAY_STATIC,
    PMTU_DISPLAY_DYNAMIC
}PMTUADP_ENTRYTYPE_E;


/* Error Return Values */
typedef enum tagPMTU_ADP_ERRORNUM_E
{
    PMTUADP_ERR_MEMBERFN_UNAVAILABLE = PMTUADP_ERROR_STARTVALUE,
    PMTUADP_ERR_INIT_NOTDONE,
    PMTUADP_ERR_OPFAIL,
    PMTUADP_ERR_ADDRESS_INVALID,
    PMTUADP_ERR_PARAMETERINVALID,
    PMTUADP_ERRORNUM_ULONG_PAD = PMTUADP_ERROR_MAXVALUE
}PMTU_ADP_ERRORNUM_E;

/* Initialize PMTU Adapter */
extern ULONG PMTU_InitAdapt();

/* Display All PMTU entries by type */
extern ULONG PMTU_DisplayEntries(ULONG ulFlag);

/* Add Static PMTU entry */
extern ULONG PMTU_AddStaticPMTU(CHAR *pcIp6Addr,ULONG ulValue);

/* Show PMTU entries by address */
extern ULONG PMTU_DisplayPMTUByIP6Addr(CHAR *pszIP6Addr);

/* Enable or Disable PMTU debugging */
extern ULONG PMTU_DebugSwitch(ULONG ulFlag);

/* Delete PMTU entries by type */
extern ULONG PMTU_DelPMTUEntriesbyType(ULONG ulType);

/* Delete PMTU entry by address */
extern ULONG PMTU_DelEntryByAddress(CHAR *szIP6Address);

/* Set Entry Count by type */
extern ULONG PMTU_GetEntryCountByType(ULONG ulFlag, ULONG *pulTotalEntries);

/* Set Max MTU that can be set on PMTU */
extern ULONG PMTU_SetMaxMTU(ULONG ulMaxMtu);

/* Set Default Age time */
extern ULONG PMTU_SetDefAge(USHORT usAgeTime);

/* Searth PathMTU Entry */
extern ULONG PMTU_SearchObj(IN6ADDR_S *pstDA, ULONG ulZoneid, PMTU_CLI_DISPLAY_S *pstCLIDisplay);

/* Get Next PMTU Entry */
extern ULONG PMTU_GetNext(ULONG *pulMultiIndex,
                    PMTU_CLI_DISPLAY_S *pstCLIDisplay,
                    UINTPTR ulWaitListHandle);

/* Get Next PMTU Entry */
extern ULONG PMTU_GetFirst(UINTPTR ulHandle,
                          PMTU_CLI_DISPLAY_S *pstCLIDisplay,
                          ULONG *pulMultiIndex);

/* Close PMTU Table */
extern ULONG PMTU_CloseTable(UINTPTR *pulUserHandle);

/* Open PMTU Table */
extern ULONG PMTU_OpenTable(UINTPTR *pulUserHandle);

extern ULONG TCPIP_IP6_PMTU_RegUserPolicyHook(TCPIP_IP6_PTU_USER_HOOK_S *pstPmtuHook);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PMTU_API_H_ */
