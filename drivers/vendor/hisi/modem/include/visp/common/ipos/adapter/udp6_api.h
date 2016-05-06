/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for UDP6
*    Version        : Initial Draft
*    File Name      : udp6_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for UDP6
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj_R (72063)   Create
**************************************************************************
*/

#ifndef      _UDP6_API_H_
#define      _UDP6_API_H_

#ifdef      __cplusplus
extern "C"{
#endif

#define UDP6ADP_SHOWERRORINFO     VRP_YES
#define UDP6ADP_AUTOINIT          VRP_YES


#define UDP6ADP_OK                VOS_OK
#define UDP6ADP_ERR               VOS_ERR


#define UDP6ADP_ERROR_STARTVALUE   0x200
#define UDP6ADP_ERROR_MAXVALUE     0xffffffff

/* UDP6 ErrorNum */
typedef enum tagUDP6_ADP_ERRORNUM_E
{
    UDP6ADP_ERR_MEMBERFN_UNAVAILABLE = UDP6ADP_ERROR_STARTVALUE,
    UDP6ADP_ERR_INIT_NOTDONE,
    UDP6ADP_ERR_OPFAIL,
    UDP6ADP_ERR_INPUTINVALID,
    UDP6ADP_ERRORNUM_ULONG_PAD = UDP6ADP_ERROR_MAXVALUE
}UDP6_ADP_ERRORNUM_E;

/* Intermediate did not process packet, VISP will continue to process it */
#define UDP6_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define UDP6_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define UDP6_PROCESSED_BY_INTERMEDIATE                  2

typedef ULONG (*UDP6INPUT_HOOK_FUNC)( MBUF_S* pMbuf );

/* Initialize UDP6 Component */
extern ULONG UDP6_InitAdapt();

/* Display UDP6 Statistics */
extern ULONG UDP6_DisplayStatistics();

/* Enable / Disable UDP6 Debugging */
extern ULONG UDP6_DebugSwitch(ULONG ulFlag);

/* Reset UDP6 Statistics */
extern ULONG UDP6_ResetStatistics();

extern ULONG TCPIP_RegFuncUDP6InputHook(UDP6INPUT_HOOK_FUNC pfFuncHook);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _UDP6_API_H_ */
