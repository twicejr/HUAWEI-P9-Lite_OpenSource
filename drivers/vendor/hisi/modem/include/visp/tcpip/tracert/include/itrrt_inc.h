/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Itrrt_inc.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module
*  Date Created: 2003-07-14
*        Author: Suraj( )
*   Description: Declare interface of trrt
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-14  Suraj( )         Creat the first version.
*
*******************************************************************************/

#ifndef _TRRT_INC_H_
#define _TRRT_INC_H_

#ifdef    __cplusplus
extern "C" {
#endif

DECLARE_INTERFACE(IIF_TRRT_ComIntFUN)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG,pfTRRT_DoTrace)(ULONG ulUserID, TCPIP_TRRT_DETECTMTU_S *pstTrrtParam);
    METHOD_(ULONG,pfTRRT_RegShellApi)(TRRT_SH_CALLBACK_S  *pstTrrtCallBackFun);
    METHOD_(ULONG,pfTRRT_SetPortRange)(USHORT usTrrtMinPort, USHORT usTrrtMaxPort, USHORT usTrrtDefaultPort);
    METHOD_(ULONG,pfTRRT_GetPortRange)(USHORT *pusTrrtMinPort, USHORT *pusTrrtMaxPort, USHORT *pusTrrtDefaultPort);
};

DECLARE_INTERFACE(IIF_TRRT_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG,pfTRRT_InitCom)(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
    METHOD_(ULONG,pfTRRT_ActiveCom)();
    METHOD_(ULONG,pfTRRT_SetModuleInfo)(TRRT_MOD_INFO_S *pstMInfo);
};

#ifdef __cplusplus
}
#endif
#endif
