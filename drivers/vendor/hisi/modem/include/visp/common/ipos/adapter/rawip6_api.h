/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for RAWIP6
*    Version        : Initial Draft
*    File Name      : rawip6_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for RAWIP6
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _RAWIP6_API_H_
#define      _RAWIP6_API_H_

#ifdef      __cplusplus
extern "C"{
#endif

#define RAWIP6ADP_SHOWERRORINFO     VRP_YES
#define RAWIP6ADP_AUTOINIT          VRP_YES


#define RAWIP6ADP_OK                VOS_OK
#define RAWIP6ADP_ERR               VOS_ERR

#define RAWIP6ADP_DISPLAY(m_string) TCPIP_InfoOutput(m_string)


#define RAWIP6ADP_ERROR_STARTVALUE 0x300
#define RAWIP6ADP_ERROR_MAXVALUE 0xffffffff

/* Error Return Values */
typedef enum tagRAWIP6_ADP_ERRORNUM_E
{
    RAWIP6ADP_ERR_MEMBERFN_UNAVAILABLE = RAWIP6ADP_ERROR_STARTVALUE,
    RAWIP6ADP_ERR_INIT_NOTDONE,
    RAWIP6ADP_ERR_OPFAIL,
    RAWIP6ADP_ERRORNUM_ULONG_PAD = RAWIP6ADP_ERROR_MAXVALUE
}RAWIP6_ADP_ERRORNUM_E;


/* Initialize RAWIP6 Component */
extern ULONG RAWIP6_InitAdapt();

/* Get RAWIP6 Statistics */
extern ULONG RAWIP6_GetStatistics(RIP6STAT_S *pstRip6Stats);

/* Reset RAWIP6 Statistics */
extern ULONG RAWIP6_ResetStatistics();

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _RAWIP6_API_H_ */
