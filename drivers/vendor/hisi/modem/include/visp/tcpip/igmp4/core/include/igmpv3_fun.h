/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_fun.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-04-17
*        Author: zengshaoyang62531
*   Description: 此头文件放函数声明，包括igmpv3_cfg.c,igmpv3_debug.c等文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-17   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_FUN_H_
#define _IGMPV3_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
    
#define IGMP_GETMULTIADDRTYPE(MultiAddr) (0xe0000000 == (0xffffff00 & MultiAddr))

#define IGMP_ISROUTERADDR(MultiAddr) \
    (0xe0000000 == MultiAddr) || (0xe0000001 == MultiAddr) || (0xe0000002 == MultiAddr) || (0xe0000016 == MultiAddr)

extern ULONG IGMP_AddSource(IPMULTI_S *pstIPMulti, ULONG ulSourceAddr, ULONG ulFilterMode);
extern LONG IGMP_AddSourceToSocket(IPMREQ_S *pstIpMreq, ULONG ulSourceAddr);
extern LONG IGMP_Block_Unblock(MBUF_S *pstMBuf, IPMOPTIONS_S **ppstIpMop, ULONG ulOptionName);
extern ULONG IGMP_ChangeSourceTag(IPMULTI_SOURCELIST_S *pstTagList, ULONG ulOldTage, ULONG ulNewTag);
extern ULONG IGMP_Change_SourceFilter(IPMULTI_S *pstIPMulti, IPMREQ_SOURCELIST_S *pstSrcRem, 
                              ULONG ulFmode_From, IPMREQ_SOURCELIST_S *pstSrcAdd, ULONG ulFmode_To);
extern ULONG IGMP_ClearHaStat();
extern ULONG IGMP_ClearIgmpStat(IFNET_S * pstIf);
extern VOID IGMP_ClearList(IPMULTI_SOURCELIST_S *pstList);
extern IPMULTI_S *IGMP_CreateMulti(IPIFNET_S *pstIpIf, ULONG ulMultiAddr);
extern LONG IGMP_DelMulti(IPIFNET_S *pstIpIf, ULONG ulMultiAddr);
extern ULONG IGMP_FindMulti(ULONG ulMultiAddr, IFNET_S * pstIf, IPMULTI_S ** ppstIPMulti);
extern ULONG IGMP_FindSourceInSocket(IPMREQ_SOURCELIST_S *sourceList, ULONG ulSourceAddr);
extern ULONG IGMP_GetHaStat(HAIGMPSTAT_S *pstHaIgmpStat);
extern ULONG IGMP_GetIgmpDebug (ULONG *pulDbg, ULONG *pulVerboseDbg);
extern ULONG IGMP_GetIgmpHADebug(ULONG *pulDbg);
extern ULONG IGMP_GetIgmpStat(IFNET_S * pstIf, IGMPSTAT_S *pstIgmpStat);
extern ULONG IGMP_GetIgmpTimer(ULONG ulTimerType, ULONG *pulTimerVal);
extern ULONG IGMP_IsMultiIfInvalid(IFNET_S * pstIf);
extern VOID IGMP_NotifyIfUP(IFNET_S *pstIf);
extern VOID IGMP_RefreshList(IPMULTI_SOURCELIST_S **ppstSourceList);
extern ULONG IGMP_RemoveSource(IPMULTI_S *pstIPMulti, ULONG ulSourceAddr, ULONG ulFilterMode);
extern LONG IGMP_RemoveSourceFromSocket(IPMREQ_S *pstIpMreq, ULONG ulSourceAddr);
extern ULONG IGMP_SetClearTag(IPMULTI_SOURCELIST_S *sourceList, 
                                       ULONG ulCurrentMask, ULONG ulSetMask, ULONG ulClearMask);
extern ULONG IGMP_SetIgmpDebug (ULONG ulFlag, ULONG ulVerboseFlag);
extern ULONG IGMP_SetIgmpHADebug(ULONG ulDbg);
extern ULONG IGMP_SetIgmpTimer(ULONG ulTimerType, ULONG ulTimerVal);
extern ULONG IGMP_SetResultList(IPMULTI_S *pstIPMulti);
extern ULONG IGMP_StartUpTimer_ByIfUp(IFNET_S *pstIf);
extern ULONG IGMP_Tag_State(IPMULTI_S *pstIPMulti, ULONG *pstFilterMode, 
                              IPMULTI_SOURCELIST_S **ppstTagList, ULONG ulUseRec, ULONG ulTagMask, ULONG *pulTagCount);

extern VOID IGMP_DebugPacket(UCHAR *pstBuf, UCHAR ucType, ULONG ulDirection, ULONG ulDebugLength);
extern VOID IGMP_Debug_HA(UCHAR *pstBuf, ULONG ulDebugLength, ULONG ulCmd);
extern VOID IGMP_PacketDiscard_Msg(ULONG ulErrCode);

extern ULONG IGMP_RegIgmpHookToGetSrcIP (IGMP_GET_SRC_IP_HOOK pstHook);
/*HA相关*/
extern ULONG IGMP_HaBatch(VOID);
extern VOID IGMP_HARealSnd (UCHAR ucOperatorCode,ULONG ulMsgType,ULONG ulType,
                                   ULONG ulLen,VOID *pData);
extern ULONG IGMP_HA_BatchCfgPacket(UCHAR *pucData,USHORT usMsgOffset,USHORT usSubType,USHORT *pusRetLen);
extern ULONG IGMP_HA_Clean();
extern ULONG IGMP_HA_Input(UCHAR *pucBuf, ULONG ulMsgLen);
extern ULONG IGMP_HA_SendPacket(UCHAR *pucData, USHORT usDataLen);
extern ULONG IGMP_HA_Smooth();
extern ULONG IGMP_RegFuncHook(IGMP_HOOK_FOR_SEND pfHookFunc);
extern VOID IGMP_DebugOutput(CHAR *pszInfo);
extern ULONG IGMP_RegShellCallbackFunc(IGMP_SHELLCALLBACK_S *pstShellCallbackFunc);
extern MBUF_S * IGMP_CreateRouterAlertOpt();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IGMPV3_FUN_H_ */

