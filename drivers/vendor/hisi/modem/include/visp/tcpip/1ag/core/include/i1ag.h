/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              i1ag.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG组件头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_I1AG_H
#define _1AG_I1AG_H

#ifdef  __cplusplus
    extern "C"{
#endif

DECLARE_INTERFACE (IIF_COMP_OAM1AG_ComIntFUN)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfOAM_1AG_RcvPkt)(MBUF_S *pstMbuf);
    METHOD_(ULONG, pfOAM_1AG_IfDel)(ULONG ulIfIndex);
    METHOD_(ULONG, pfOAM_1AG_IsEnable1ag)(ULONG ulIfIndex, ULONG* pulIsEnable);
    METHOD_(ULONG, pfOAM_1AG_NpNotify)(UINTPTR aulMsg[4]);
    METHOD_(ULONG, pfOAM_1AG_HA_BatchBackup)(VOID);
    METHOD_(ULONG, pfOAM_1AG_HA_Input)(UCHAR * pucData, ULONG ulDataLen);
    METHOD_(ULONG, pfOAM_1AG_HA_Smooth)(VOID);
    METHOD_(ULONG, pfOAM_1AG_HA_Clean)(VOID);
    METHOD_(ULONG, pfOAM_1AG_GetHaStat)(HA1AGSTAT_S *pstHa1agStat);
    METHOD_(ULONG, pfOAM_1AG_ClearHaStat)(VOID);
    METHOD_(ULONG, pfOAM_1AG_SetHaDebug)(ULONG ulFlag);
    METHOD_(ULONG, pfOAM_1AG_GetHaDebug)(ULONG *pulValue);
    METHOD_(ULONG, pfOAM_1AG_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
    
    METHOD_(ULONG, pfOAM_1AG_SetHaVerboseDebug)(ULONG ulFlag);
    METHOD_(ULONG, pfOAM_1AG_GetHaVerboseDebug)(ULONG *pulFlag);

    METHOD_(ULONG, pfOAM_1AG_JudgeNameValue)(UCHAR* pszMdName, UCHAR* pszMaName);
    METHOD_(ULONG, pfOAM_1AG_GetRmepStatus)(UCHAR* pszMdName,UCHAR* pszMaName, USHORT usRmepId, ULONG* pulStatus);
    METHOD_(ULONG, pfOAM_1AG_IfStatus)(ULONG ulIfIndex,ULONG ulCmd);
};

DECLARE_INTERFACE (IIF_COMP_OAM1AG_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfOAM_1AG_Init_Com)(VOID);
    METHOD_(ULONG, pfOAM_1AG_Active_Com)(VOID);
    METHOD_(ULONG, pfOAM_1AG_SetModuleInfo)(OAM_1AG_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfOAM_1AG_RegShellApi)(OAM_1AG_SHELL_CALLBACK_S* pstShellApi);

    METHOD_(ULONG, pfOAM_1AG_SetPktType)(USHORT usPktType,UCHAR ucPriority);
    METHOD_(ULONG, pfOAM_1AG_GetPktType)(USHORT *pusEthType,UCHAR *pucPriority);
    METHOD_(ULONG, pfOAM_1AG_GlobalDisable)(VOID);
    METHOD_(ULONG, pfOAM_1AG_CreateMd)(UCHAR * pszMdName, UCHAR ucMdLevel);
    METHOD_(ULONG, pfOAM_1AG_DeleteMd)(UCHAR * pszMdName);
    METHOD_(ULONG, pfOAM_1AG_GetMdInfo)(UCHAR *pszMdName, DISP_MD_INFO_S *pstDispMdInfo);
    METHOD_(ULONG, pfOAM_1AG_CreateMa)(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulVlanId, VOID *pPrara, VOID *pstTlvData);
    METHOD_(ULONG, pfOAM_1AG_DeleteMa)(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulIsBackUp);
    METHOD_(ULONG, pfOAM_1AG_GetMaInfo)(UCHAR *pszMdName,UCHAR *pszMaName, DISP_MA_INFO_S *pstDispMaInfo);
    METHOD_(ULONG, pfOAM_1AG_CreateMep)(ULONG ulIfIndex, UCHAR * pszMdName, 
                                        UCHAR * pszMaName, USHORT usMepId, VOID *pPrara, VOID *pstTlvData);
    METHOD_(ULONG, pfOAM_1AG_DeleteMep)(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, ULONG ulIsBackUp);
    METHOD_(ULONG, pfOAM_1AG_CreateRmep)(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName,
                                         UCHAR * pszMaName, USHORT usRmepId, VOID *pPrara, VOID *pstTlvData);
    METHOD_(ULONG, pfOAM_1AG_DeleteRmep)(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usRmepId, ULONG ulIsBackUp);
    METHOD_(ULONG, pfOAM_1AG_GetMepInfo)(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                                         DISP_MEP_INFO_S * pstDispMepInfo);
    METHOD_(ULONG, pfOAM_1AG_EnableCcmSend)(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, UCHAR ucSendFlag);
    METHOD_(ULONG, pfOAM_1AG_SetCcmInterval)(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulInterval);

    METHOD_(ULONG, pfOAM_1AG_Ping)(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                                   USHORT usRmepId, ULONG ulCount,USHORT usPacketSize, USHORT usTimeOut,
                                   ULONG ulSendInterval, ULONG ulID, UCHAR ucVlanPri);

    METHOD_(ULONG, pfOAM_1AG_UserPing)(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName,
                                       UCHAR * pszMaName, USHORT usRmepId, UCHAR *pBuffer,
                                       ULONG ulLen, UCHAR ucVlanPri);

    METHOD_(ULONG, pfOAM_1AG_Trace)(ULONG ulIfIndex, UCHAR *pcMacAddr, UCHAR * pszMdName, UCHAR * pszMaName, 
                                    USHORT usRmepId, UCHAR ucTtl,USHORT  usTimeOut, ULONG ulID);
    METHOD_(ULONG, pfOAM_1AG_GetMepStat)(UCHAR *pszMdName,UCHAR * pszMaName, USHORT usMepId, 
                                         OAM_1AG_STAT_S *pstOam1agStat); 
    METHOD_(ULONG, pfOAM_1AG_ClearMepStat)(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId); 
    METHOD_(ULONG, pfOAM_1AG_SetDebug)(ULONG ulType,ULONG ulFlag, ULONG ulPacketNum,ULONG ulPacketOctets);
    METHOD_(ULONG, pfOAM_1AG_GetDebug)(ULONG *pul1AgPktDebug,ULONG *pulError1AgPktDebug,ULONG 
                        *pul1AgVerbosePktDebug,ULONG *pulPacketNum,ULONG *pulPacketOctets); 
    METHOD_(ULONG, pfOAM_1AG_SetCompatible)(UCHAR * pszMdName, UCHAR *pszMaName, ULONG ulValue);
    METHOD_(ULONG, pfOAM_1AG_GetCompatible)(UCHAR * pszMdName, UCHAR *pszMaName, ULONG *pulValue); 
    METHOD_(ULONG, pfOAM_1AG_SetMaVlanPri)(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucPriority);
    METHOD_(ULONG, pfOAM_1AG_GetAllMepInfoById)(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                                                DISP_MEP_INFO_LIST_S ** ppstDispMepInfoList);
    METHOD_(ULONG, pfOAM_1AG_FreeMepInfoList)(DISP_MEP_INFO_LIST_S * pstDispMepInfoList);
    METHOD_(ULONG, pfOAM_1AG_SetVersion)(ULONG ulIfIndex, ULONG ulVersion, ULONG ulIsTrunkPort);
    METHOD_(ULONG, pfOAM_1AG_GetVersion)(ULONG ulIfIndex, ULONG *pulVersion);
    METHOD_(ULONG, pfOAM_1AG_SetRcvDefaultVlan)(ULONG ulIfIndex, ULONG ulDefaultVlan);
    METHOD_(ULONG, pfOAM_1AG_GetRcvDefaultVlan)(ULONG ulIfIndex, ULONG *pulDefaultVlan);
    METHOD_(ULONG, pfOAM_1AG_SetRmepCheck)(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulSetYes, ULONG ulPPICCMode);
    METHOD_(ULONG, pfOAM_1AG_GetRmepCheck)(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG *pulSetYes);

    METHOD_(ULONG, pfOAM_1AG_DeleteAllMepOnIfIndex)(ULONG ulIfIndex);
    METHOD_(ULONG, pfOAM_1AG_SetLossDetectInterval)(UCHAR * pszMdName, UCHAR * pszMaName, 
                                                    USHORT usMepId, USHORT usInterval);
    METHOD_(ULONG, pfOAM_1AG_GetLossDetectInterval)(UCHAR * pszMdName, UCHAR * pszMaName, 
                                                    USHORT usMepId, USHORT *pusInterval);
    
    METHOD_(ULONG, pfOAM_1AG_GetRmepWarnState)(UCHAR * pszMdName, UCHAR * pszMaName, 
                                               USHORT usRmepId, OAM1AG_WARN_STATE_S * pst1agWarnState);
    
    /* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. 修改原因: 支持EOAM协议版本全局设置 */
    METHOD_(ULONG, pfOAM_1AG_SetGlobalVersion)(ULONG ulVersion);           
    METHOD_(ULONG, pfOAM_1AG_GetGlobalVersion)(ULONG *pulVersion);  

    /* Add for V2R3C06, by z00187940/s00176784, at 2011-10-13. 修改原因: 支持EOAM AIS使能设置 */
    METHOD_(ULONG, pfOAM_Y1731_EnableAIS)(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucEnable);  

    /* Add for V2R3C06, by  z00171897/p00193127, at 2011-10-12. 修改原因: 支持Y1731使能/去使双端帧丢失检测、
          单端帧丢失检测SLM功能、双向延时检测DM功能*/
    METHOD_(ULONG, pfOAM_Y1731_EnablePMCheck)(UCHAR * pszMdName, UCHAR * pszMaName,
                                                    USHORT usMepId, USHORT usRmepId,UCHAR ucPMType,UCHAR ucCheckFlag,
                                                    ULONG ulSendInterval, ULONG ulTimeOut); 
};

DECLARE_INTERFACE (IIF_COMP_OAM1AG_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagOAM1AG_IntObj
{
    struct IIF_COMP_OAM1AG_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_OAM1AG_ComIntCFG    *pCompIntCFG;
    struct IIF_COMP_OAM1AG_ComIntSSA    *pCompIntSSA;
}OAM1AG_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif

#endif
