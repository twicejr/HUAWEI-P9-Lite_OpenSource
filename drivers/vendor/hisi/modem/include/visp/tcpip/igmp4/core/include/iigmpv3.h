/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iigmpv3.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-03-10
*        Author: zengshaoyang62531
*   Description: 定义igmp中的组件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IIGMPV3_H
#define _IIGMPV3_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "tcpip/public/tcpip_id.h" 
#include "tcpip/ip4/am4/include/am4_pub.h"

DECLARE_INTERFACE(IIF_COMP_IGMP_ComIntFUN) 
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_(ULONG, pfIP_IGMP_Init_Com)(COM_ID_INFO_S *pComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfIP_IGMP_Activate_Com)();
    METHOD_(ULONG, pfIP_IGMP_SetModuleInfo)(IpIgmpModInfo_S *pstModInfo);

    /*HA相关*/
    METHOD_(ULONG, pfIGMP_HaBatch)(VOID);
    METHOD_(VOID, pfIGMP_HARealSnd )(UCHAR ucOperatorCode,ULONG ulMsgType,ULONG ulType,ULONG ulLen,VOID *pData);
    METHOD_(ULONG, pfIGMP_HA_Clean)();
    METHOD_(ULONG, pfIGMP_HA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfIGMP_HA_Smooth)();
};

DECLARE_INTERFACE( IIF_COMP_IGMP_ComIntCFG )
{
    IUNKNOWN_METHODS       

    METHOD_(ULONG, pfIGMP_ClearIgmpStat)(IFNET_S * pstIf);
    METHOD_(ULONG, pfIGMP_GetIgmpDebug)(ULONG *pulDbg, ULONG *pulVerboseDbg);
    METHOD_(ULONG, pfIGMP_GetIgmpHADebug)(ULONG *pulDbg);
    METHOD_(ULONG, pfIGMP_GetIgmpStat)(IFNET_S * pstIf, IGMPSTAT_S *pstIgmpStat);
    METHOD_(ULONG, pfIGMP_GetIgmpTimer)(ULONG ulTimerType, ULONG *pulTimerVal);
    METHOD_(ULONG, pfIGMP_ClearHaStat)();
    METHOD_(ULONG, pfIGMP_GetHaStat)(HAIGMPSTAT_S *pstHaIgmpStat);
    METHOD_(ULONG, pfIGMP_SetIgmpDebug)(ULONG ulDbg, ULONG ulVerboseFlag);
    METHOD_(ULONG, pfIGMP_SetIgmpHADebug)(ULONG ulDbg);
    METHOD_(ULONG, pfIGMP_SetIgmpTimer)(ULONG ulTimerType, ULONG ulTimerVal);
    METHOD_(VOID,  pfIGMP_ClearList)(IPMULTI_SOURCELIST_S *pstList);
    METHOD_(ULONG, pfIGMP_AddSource)(IPMULTI_S *pstIPMulti, ULONG ulSourceAddr, ULONG ulFilterMode);
    METHOD_(ULONG, pfIGMP_RemoveSource)(IPMULTI_S *pstIPMulti, ULONG ulSourceAddr, ULONG ulFilterMode);
    METHOD_(ULONG, pfIGMP_IsMultiIfInvalid)(IFNET_S * pstIf);
    METHOD_(ULONG, pfIGMP_FindMulti)(ULONG ulMultiAddr, IFNET_S * pstIf, IPMULTI_S ** ppstIPMulti);
    METHOD_(ULONG, pfIGMP_FindSourceInSocket)(IPMREQ_SOURCELIST_S *sourceList, ULONG ulSourceAddr);
    METHOD_(LONG, pfIGMP_AddSourceToSocket)(IPMREQ_S *pstIpMreq, ULONG ulSourceAddr);
    METHOD_(LONG, pfIGMP_RemoveSourceFromSocket)(IPMREQ_S *pstIpMreq, ULONG ulSourceAddr);
    METHOD_(struct tagIPMULTI*, pfIGMP_CreateMulti)(IPIFNET_S *pstIpIf, ULONG ulMultiAddr);
    METHOD_(LONG, pfIGMP_DelMulti)(IPIFNET_S *pstIpIf, ULONG ulMultiAddr);
    METHOD_(ULONG, pfIGMP_Change_SourceFilter)(IPMULTI_S *pstIPMulti, IPMREQ_SOURCELIST_S *pstSrcRem, 
                   ULONG ulFmode_From, IPMREQ_SOURCELIST_S *pstSrcAdd, ULONG ulFmode_To);
    METHOD_(LONG, pfIGMP_Block_Unblock)(MBUF_S *pstMBuf, IPMOPTIONS_S **ppstIpMop, ULONG ulOptionName);
    METHOD_(VOID, pfIGMP_NotifyIfUP)(IFNET_S *pstIf);
    METHOD_(VOID, pfIGMP_Input)(MBUF_S *pstMBuf, LONG lHLen);
    METHOD_(ULONG, pfIGMP_Timer_Delete)(ULONG ulTimerId);
    METHOD_(ULONG, pfIGMP_RegShellCallbackFunc)(IGMP_SHELLCALLBACK_S *pstShellCallbackFunc);
    METHOD_(ULONG, pfIGMP_RegIgmpHookToGetSrcIP)(IGMP_GET_SRC_IP_HOOK pstHook);
};

DECLARE_INTERFACE( IIF_COMP_IGMP_ComIntSSA )
{
    IUNKNOWN_METHODS
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
