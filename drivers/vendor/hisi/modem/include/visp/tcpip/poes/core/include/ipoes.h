/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoes.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-19
*       Author: lijing(52889)
*  Description: POES组件虚表声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-19   lijing(52889)           Create
*
*******************************************************************************/

#ifndef _IPOES_H_
#define _IPOES_H_

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_INTERFACE (IIF_COMP_POES_ComIntFUN)
{
    IUNKNOWN_METHODS
        
    METHOD_(ULONG, pfPOES_VTIsBinded)(IFNET_S *pstIf, ULONG *pulEthIfIndex);
    METHOD_(ULONG, pfPOES_OpenList)(UINTPTR *pulPOESWaitListHandle);
    METHOD_(ULONG, pfPOES_GetPoesCB)(UINTPTR ulPOESWaitListHandle, POES_CB_S *pstPoesCb);
    METHOD_(ULONG, pfPOES_CloseList)(UINTPTR ulPOESWaitListHandle);
    METHOD_(ULONG, pfPOES_HA_BatchBackup)();
    METHOD_(ULONG, pfPOES_HA_RealTimeBackup)(UCHAR ucBkMsgType, UCHAR *pucInfo);
    METHOD_(ULONG, pfPOES_HA_Input)(UCHAR *pucBkMsg, ULONG ulMsgLen);
    METHOD_(ULONG, pfPOES_HA_Smooth)();
    METHOD_(ULONG, pfPOES_HA_Clean)();
};

DECLARE_INTERFACE (IIF_COMP_POES_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfPOES_Init_Com)(const COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfPOES_Active_Com)(VOID);
    METHOD_(ULONG, pfPOES_SetModuleInfo)(POES_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfPOES_RegShellApi)(POES_SHELL_CALLBACK_SET_S* pstShellApi);
    METHOD_(ULONG, pfPOES_Enable)(ULONG ulEthIfIndex, ULONG ulVTIfIndex);
    METHOD_(ULONG, pfPOES_Disable)(ULONG ulEthIfIndex);
    METHOD_(ULONG, pfPOES_SetSesLimit)(ULONG ulSesLimit);
    METHOD_(ULONG, pfPOES_SetOurSesLimit)(ULONG ulSesLimit);
    METHOD_(ULONG, pfPOES_SetHisSesLimit)(ULONG ulSesLimit);
    METHOD_(ULONG, pfPOES_SetServiceName)(ULONG ulEthIfIndex, CHAR *pszName);
    METHOD_(ULONG, pfPOES_GetSysCfgInfo)(POES_SYS_CFG_INFO_S *pstSysCfgInfo);
    METHOD_(ULONG, pfPOES_GetIfCfgInfo)(ULONG ulEthIfIndex, POES_IF_CFG_INFO_S *pstIfCfgInfo);
    METHOD_(ULONG, pfPOES_GetHisMacSessions)(UCHAR *pucHisMac, USHORT *pusSesNum);
    METHOD_(ULONG, pfPOES_GetSesStatInfo)(ULONG ulEthIfIndex, POES_SESSION_STAT_INFO_S *pstSesStatInfo);
    METHOD_(ULONG, pfPOES_GetSesInfo)(ULONG ulEthIfIndex, USHORT *pusSessionID, POES_SESSION_INFO_S *pstSesInfo);
    METHOD_(ULONG, pfPOES_GetSesPktStatInfo)(ULONG ulEthIfIndex, USHORT *pusSessionID, POES_SES_PKT_STAT_INFO_S *pstPktStatInfo);
    METHOD_(ULONG, pfPOES_SetWarningSwitch)(ULONG ulWarnSw);
    METHOD_(ULONG, pfPOES_GetWarningSwitch)(ULONG *pulSwitch);
    METHOD_(ULONG, pfPOES_ClearStatInfo)(ULONG ulEthIfIndex,ULONG ulType);
    METHOD_(ULONG, pfPOES_SetDbgSwitch)(ULONG ulEthIfIndex, ULONG ulType, ULONG ulValue);
    METHOD_(ULONG, pfPOES_GetDbgSwitch)(ULONG ulEthIfIndex, POES_DEBUG_INFO_S *pstDbgInfo);
    METHOD_(VOID, pfPOES_HA_DebugOutput)(UCHAR *pucBkMsg, ULONG ulMsgLen, ULONG ulCmd);
    METHOD_(ULONG, pfTCPIP_HA_SetPoesDbg)(ULONG ulValue);
    METHOD_(ULONG, pfPOES_HA_GetPoesDbg)(ULONG *pulValue);
    METHOD_(ULONG, pfPOES_HA_SetPoesVerboseDbg)(ULONG ulValue);
    METHOD_(ULONG, pfPOES_HA_GetPoesVerboseDbg)(ULONG *pulValue);
    METHOD_(ULONG, pfPOES_DelAllSess)(ULONG ulEthIfIndex);/*Add by Q62011 for BC3D01354*/
};
 

DECLARE_INTERFACE (IIF_COMP_POES_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagPOES_IntObj
{
    struct IIF_COMP_POES_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_POES_ComIntCFG    *pCompIntCFG;
    struct IIF_COMP_POES_ComIntSSA    *pCompIntSSA;
}POES_INT_OBJ_S;

#ifdef __cplusplus
}
#endif

#endif /*_IPOES_H_*/

