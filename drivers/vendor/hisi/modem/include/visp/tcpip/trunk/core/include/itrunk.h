/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              itrunk.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: 组件虚表的声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _ITRUNK_H_
#define _ITRUNK_H_

#ifdef __cplusplus
extern "C"{
#endif

DECLARE_INTERFACE (IIF_COMP_TRUNK_ComIntFUN)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfTRUNK_PhyInit)(IFNET_S *pIf);
    METHOD_(ULONG, pfTRUNK_FreeBlock)(IFNET_S *pIf);
    METHOD_(ULONG, pfTRUNK_IsHavingPort)(IFNET_S *pIf);
    METHOD_(ULONG, pfTRUNK_IsTrunkPort)(IFNET_S *pIf);
    METHOD_(ULONG, pfTRUNK_GetTrunkIfByPortIf)(ULONG ulPortIfIndex, ULONG *pulTrunkIfIndex);
    METHOD_(ULONG, pfTRUNK_PortLinkIOCtl)(IFNET_S *pIf, ULONG ulCmd, CHAR * pData);

    METHOD_(ULONG, pfTRUNK_HA_BatchBackup)(VOID);
    METHOD_(ULONG ,pfTRUNK_HA_RealTimePack)(ULONG ulMsgType, VOID *pData);
    METHOD_(ULONG, pfTRUNK_HA_Input)(UCHAR * pucData, const USHORT usDataLen);
    METHOD_(ULONG, pfTRUNK_HA_Smooth)(VOID);
    METHOD_(ULONG, pfTRUNK_HA_Clean)(VOID);
    METHOD_(VOID, pfTRUNK_Health_BatchCheckup)(VOID);
    METHOD_(ULONG, pfTRUNK_LastWord_BatchCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);
};

DECLARE_INTERFACE (IIF_COMP_TRUNK_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfTRUNK_Init_Com)(const COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfTRUNK_Active_Com)(VOID);
    METHOD_(ULONG, pfTRUNK_SetModuleInfo)(TRUNK_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfTRUNK_RegShellApi)(TRUNK_SHELL_CALLBACK_SET_S* pstShellApi);

    METHOD_(ULONG, pfTRUNK_AddPort)(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);
    METHOD_(ULONG, pfTRUNK_AddVPort)(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

    METHOD_(ULONG, pfTRUNK_RemovePort)(ULONG ulIfIndex);
    METHOD_(ULONG, pfTRUNK_GetPortStat)(ULONG ulIfIndex, PORT_STAT_INFO_S *pstPortStatInfo);
    METHOD_(ULONG, pfTRUNK_ClearPortStatInfo)(ULONG ulIfIndex);
    METHOD_(ULONG, pfTRUNK_SetDebug)(ULONG ulSwitch, ULONG ulValue);
    METHOD_(ULONG, pfTRUNK_GetDebug)(ULONG *pulLacpPktDbgSw, ULONG *pulOtherPktDbgSw, ULONG *pulFsmDbgSw);
    METHOD_(ULONG, pfTRUNK_GetTrunkInfo)(ULONG ulTrunkId, TRUNK_INFO_S * pstTrunkInfo);
    METHOD_(ULONG, pfTRUNK_GetTrunkIdByIf)(ULONG ulIfIndex, ULONG *ulTrunkId);
    METHOD_(ULONG, pfTRUNK_SetLacp)(ULONG ulIfIndex, ULONG ulValue);
    METHOD_(ULONG, pfTRUNK_LACP_SetPeriodMode)(ULONG ulIfIndex, ULONG ulValue);
    METHOD_(ULONG, pfTRUNK_LACP_GetFsmInfo)(ULONG ulIfIndex, LACP_FSM_INFO_S *pstFsmInfo);
    METHOD_(ULONG, pfTRUNK_LACP_GetNegoInfo)(ULONG ulIfIndex, LACP_NEGO_INFO_S *pstNegoInfo);
    METHOD_(USHORT, pfTRUNK_LACP_GetSysPri)(VOID);
    METHOD_(ULONG, pfTRUNK_Distribute_Hook_Register)(TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc);
    METHOD_(ULONG, pfTRUNK_JudgeIfType)(ULONG ulIfIndex);
    METHOD_(ULONG, pfTRUNK_SetBfd_Mode)(ULONG ulTrunkIfIndex, UCHAR ucValue);
    METHOD_(ULONG, pfTRUNK_GetBfd_Mode)(ULONG ulTrunkIfIndex, UCHAR *pucValue);

    METHOD_(ULONG, pfTCPIP_HA_SetTrunkDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfTRUNK_HA_GetTrunkDbg)(ULONG* pulDbg);

    METHOD_(ULONG, pfTRUNK_HA_SetTrunkVerboseDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfTRUNK_HA_GetTrunkVerboseDbg)(ULONG* pulDbg);
    METHOD_(VOID, pfTRUNK_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
    METHOD_(ULONG, pfTRUNK_SetTrunkGateValue)(ULONG ulTrunkId, ULONG ulGateValue);
    METHOD_(ULONG, pfTRUNK_GetTrunkGateValue)(ULONG ulTrunkId, ULONG *pulGateValue);
    METHOD_(ULONG, pfTRUNK_Set_NegTimeoutWaring)(ULONG ulTime);
    METHOD_(ULONG, pfTRUNK_Get_NegTimeoutWaring)(ULONG *pulTime);

    METHOD_(ULONG, pfTRUNK_VlanCheck_Hook_Register)(TRUNK_VLANCHECK_HOOK_FUNC pfTrunkHookFunc);

    METHOD_(ULONG, pfTRUNK_NotifyLacpStatus)(ULONG ulIfIndex, ULONG ulStatus);

    METHOD_(ULONG, pfTRUNK_1AG_MultiMac_Update)(ULONG ulTkIfIndex, ULONG ulCmd, UCHAR *pucMacMask);
    METHOD_(ULONG, pfTRUNK_GetPortRemoveWarningFlag)(ULONG ulIfIndex, UCHAR *pucWarning);
    METHOD_(ULONG, pfTRUNK_SetTrunkSysPri)(USHORT usSysPri);
    METHOD_(ULONG, pfTRUNK_SetTrunkPortPri)(ULONG ulIfIndex, USHORT usPri);
    METHOD_(ULONG, pfTRUNK_GetTrunkPortPri)(ULONG ulIfIndex, USHORT *pusPri);

    METHOD_(ULONG, pfTRUNK_SetTrunkBackupMode)(ULONG ulTrunkId, ULONG ulMode);
    METHOD_(ULONG, pfTRUNK_GetTrunkBackupMode)(ULONG ulTrunkId, ULONG *pulMode);
    METHOD_(ULONG, pfTRUNK_SetTrunkMasterPort)(ULONG ulTrunkId,ULONG ulIfIndex);
    METHOD_(ULONG, pfTRUNK_GetTrunkMasterPort)(ULONG ulTrunkId,ULONG *pulIfIndex);
    METHOD_(ULONG, pfTRUNK_SetTrunkActiveNum)(ULONG ulTrunkId, ULONG ulActiveNum);
    METHOD_(ULONG, pfTRUNK_GetTrunkActiveNum)(ULONG ulTrunkId, ULONG *pulActiveNum);
    METHOD_(ULONG, pfTRUNK_SetTrunkRecoverMode)(ULONG ulTrunkId, ULONG ulMode);
    METHOD_(ULONG, pfTRUNK_GetTrunkRecoverMode)(ULONG ulTrunkId, ULONG *pulMode);
    METHOD_(ULONG, pfTRUNK_GetWarningFlagWhenLacpDisable)(ULONG ulIfIndex, ULONG *pulRet);

    METHOD_(ULONG, pfTRUNK_SetTrunkSysPriById)(ULONG ulTrunkId, USHORT usSysPri);
    METHOD_(ULONG, pfTRUNK_GetTrunkSysPriById)(ULONG ulTrunkId, USHORT *pusSysPri);
    METHOD_(ULONG, pfTRUNK_1AG_MultiMac_UpdateWhenSetVersion)(ULONG ulTkIfIndex, UCHAR uc1AGNewVersion);

    METHOD_(ULONG, pfTRUNK_GetTrunkPortOriginalMac)(ULONG ulIfIndex, UCHAR *pucMac);
    METHOD_(ULONG, pfTRUNK_SetTrunkProductProcPolicy)(ULONG ulTrunkId, ULONG ulPolicy); 
    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    METHOD_(ULONG, pfTRUNK_LacpExpiredNotify)(TRUNK_LACP_NOTIFY_S *pstData);
    METHOD_(VOID,  pfTrunk_Lacp_DealMsg)(UINTPTR aulMsg[4]);
};


DECLARE_INTERFACE (IIF_COMP_TRUNK_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagTRUNK_IntObj
{
    struct IIF_COMP_TRUNK_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_TRUNK_ComIntCFG    *pCompIntCFG;
    struct IIF_COMP_TRUNK_ComIntSSA    *pCompIntSSA;
}TRUNK_INT_OBJ_S;

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ITRUNK_H_ */

