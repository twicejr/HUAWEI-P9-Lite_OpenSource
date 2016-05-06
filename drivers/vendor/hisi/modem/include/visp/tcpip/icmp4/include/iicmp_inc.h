/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iicmp_inc.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 定义Icmp中的组件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_ICMP_INC_H_
#define _I_ICMP_INC_H_

struct tagMBuf;
struct tagIFNET;
struct tagIpIcmpModInfo;
struct tagICMPSTAT;
struct tagIpIcmpIcCallbackSet;

DECLARE_INTERFACE( IIF_IPV4_IP_ICMP_ComIntFUN ) 
{
    IUNKNOWN_METHODS

    METHOD_(VOID, pfICMP_Error)(struct tagMBuf*pstMBuf, LONG ltype, LONG lcode, 
                                ULONG ulnlDest, struct tagIFNET*pstIfNet);
    METHOD_(VOID, pfICMP_Input)(struct tagMBuf*pstMBuf, LONG lHLen);

    METHOD_(ULONG, pfICMP_AddIcmpFlowStat)(UCHAR ucFlowStatType, ULONG ulLocalIP,
                            ULONG ulRemoteIP, UCHAR ucIcmpType,
                            ULONG ulSendErr, ULONG ulVrfIndex);
    
    METHOD_(ULONG, pfICMP_AddIcmpStatbyVrf)(ULONG ulVrfIndex, UCHAR ucIcmpType,
                                UCHAR ucIcmpCode, UCHAR ucPacketDir);
};

DECLARE_INTERFACE( IIF_IPV4_IP_ICMP_ComIntCFG )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_(ULONG, pfIP_ICMP_Init_Com)(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_(ULONG, pfIP_ICMP_Activate_Com)();
    METHOD_(ULONG, pfIP_ICMP_SetModuleInfo)(struct tagIpIcmpModInfo*pstModInfo);

    METHOD_(ULONG, pfIP_ICMP_SetDebugFlag)(ULONG ulDebugFlag);
    METHOD_(ULONG, pfIP_ICMP_GetDebugFlag)(ULONG *pulDebugFlag);
    METHOD_(ULONG, pfIP_ICMP_GetStatics)(struct tagICMPSTAT * pstStat);
    METHOD_(ULONG, pfIP_ICMP_ClearCounters)(ULONG ulSlotNumber );
    
    METHOD_(ULONG,  pfIP_ICMP_ClearInterface)( IPIFNET_S *  pstIpIf);

    /* add by z62531 ,禁ping开关设置/获取接口 */
    METHOD_(ULONG,pfIP_ICMP_SetPingForbidFlag)(ULONG ulValue);
    METHOD_(ULONG,pfIP_ICMP_GetPingForbidFlag)(ULONG *pulValue);

    /* add by z00104207, 禁ping增强设置/显示ping allow list接口*/
    METHOD_(ULONG,pfICMP_SetPingAllowList)(ULONG ulOperation, ULONG ulIpAddr, ULONG ulMask);
    METHOD_(VOID,pfICMP_ShowPingAllowList)();

    METHOD_(ULONG, pfIP_ICMP_CreateIcmpFlowStat)(UCHAR ucFlowStatType, UCHAR ucNumber);
    METHOD_(ULONG, pfIP_ICMP_GetIcmpFlowStat)(UCHAR ucFlowStatType, ULONG ulVrfIndex, UCHAR *pucNumber, VOID *pStat);
    METHOD_(ULONG, pfIP_ICMP_ClearIcmpFlowStat)(UCHAR ucFlowStatType, ULONG ulVrfIndex);
    METHOD_(ULONG, pfIP_ICMP_GetIcmpStatbyVrf)(ULONG ulVrfIndex,ICMPSTATVRF_S *pstStat);
    METHOD_(ULONG, pfIP_ICMP_ClearIcmpStatbyVrf)(ULONG ulVrfIndex);
    METHOD_(ULONG, pfIP_ICMP_EnableIcmpStat)(ULONG ulFlag);
};


DECLARE_INTERFACE( IIF_IPV4_IP_ICMP_ComIntSSA )
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIP_ICMP_RegisterIcCallbacks)(struct tagIpIcmpIcCallbackSet*pstCallbackSet);
};

#endif  /* _I_ICMP_INC_H_  */


#ifdef  __cplusplus
}
#endif

