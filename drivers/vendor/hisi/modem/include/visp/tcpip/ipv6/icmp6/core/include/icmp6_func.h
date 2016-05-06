/*******************************************************************************
*                          icmp6_func.h
*  Project Code    : VRP3.0
*  Author          : Mayun  / Mahaveer Jain
*  Create Date     : 2002-8-20
*  Version         : Initial Draft
*  Description     : 本文件是icmp6.c文件
*  Others          :
*  Remarks         : The following function declarations has their
*                    corresponding comments on its function definition headers.
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
* 2006-09-14   Alok             Updated for 14 Fly-Check rules adherence
*                               for IPBIRV1R2.IPv6
*-------------------------------------------------------------------------------
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.
*                      ALL RIGHTS RESERVED
*******************************************************************************/
#ifndef _ICMP6_FUNC_H_
#define _ICMP6_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif

VOID IP6_ICMP6_Error(MBUF_S *pstMBuf, UCHAR ucType, UCHAR ucCode, LONG lParam);

VOID IP6_ICMP6_Init(VOID);

ULONG IP6_ICMP6_Rip6_Input(MBUF_S **ppstMBuf, ULONG ulOff);

VOID IP6_ICMP6_Reflect(MBUF_S *pstMBuf, ULONG ulOff);

ULONG IP6_ICMP6_NotifyError(MBUF_S *pstMbuf, ULONG ulOff, ULONG ulIcmp6Len,
                                                          UCHAR ucCode);

IN6ADDR_S * IP6_ICMP6_SelectSrcAddr(const IN6ADDR_S *pstDstAddr,
                                                      IN6ADDR_S *pstSrcAddr,
                                                      USHORT usVrfIndex);

/* Start: RFC4443 compliance changes */
ULONG IP6_ICMP6_ICMP6InfoInit (VOID *pstIfCtlblk);

/* End: RFC4443 compliance changes */

VOID IP6_ICMP6_ErrCount(ICMP6_ERRSTAT_S *pstIcmp6ErrStat, UCHAR ucType,
                                                          UCHAR ucCode);

ULONG IP6_ICMP6_ErrorRateLimit(ULONG ulType);

VOID IP6_ICMP6_InterfaceStatistics (ULONG ulIfIndex,ICMP6STATFIELD efield,
                                           UCHAR ucType, UCHAR ucCode);

ULONG IP6_ICMP6_Init_Com_New(const IPB_IR_ICMP6_COM_ID_INFO_S *pstComInfo,
                             ULONG ulComLen);

ULONG IP6_ICMP6_Input(MBUF_S **ppstMBuf, ULONG *pulOff,ULONG ulProto);

ULONG IP6_ICMP6_QueryInterface(IUnknown * This, COMP_IID iid,
                                                       LPVOID *icmp6vObj);

ULONG IP6_ICMP6_Activate_Com(VOID);

ULONG IP6_ICMP6_SetModuleInfo(IP6_ICMP6_MOD_INFO_S *pstMInfo);

ULONG IP6_ICMP6_RegShellCallBackFunc(
                                IP6_ICMP6_SH_CALLBACK_FUNC_S *pstCallbackFunc);

ULONG IP6_ICMP6_SOSB6_Socket_RegisterCallBack(
                                       SOSB6_CALLBACUP_SET_S *pstCallbackFunc);

ULONG IP6_ICMP6_IN6PCB_Socket_RegisterCallBack(
                                      IN6PCB_CALLBACUP_SET_S *pstCallbackFunc);

ULONG IP6_ICMP6_ErrorRateLimitUpdate(const ICMP6_ERRRATE_MSG_S *pstBuf);

/* Start: RFC4443 compliance changes */
ULONG IP6_ICMP6_EnableDisableIntfDestUnReachError (ULONG ulIfindex,
                                                    ULONG ulOperation);

/* End: RFC4443 compliance changes */

ULONG IP6_ICMP6_ErrorRateLimitGetValue (ULONG *pulInterval,ULONG *pulTockens);

ULONG IP6_ICMP6_SetTooBigErrorRateLimit (ULONG ulRateStatus);

ULONG IP6_ICMP6_GetAllStatistics(ICMP6STAT_S *pstIcmp6Stat);

ULONG IP6_ICMP6_ResetAllStatistics(VOID);

ULONG IP6_ICMP6_IncrementStatistics(ULONG ulIfIndex,ICMP6STATFIELD efield,
                                             UCHAR ucType);

ULONG IP6_ICMP6_ResetStatisticsByType (ICMP6STATFIELD efield, UCHAR ucType);

ULONG IP6_ICMP6_GetStatisticsByType(ICMP6STATFIELD efield, UCHAR ucType,
                                                             ULONG *pulVal);

LONG IP6_ICMP6_CtlOutput(LONG lOper, UINTPTR ulSockId,LONG lLevel, LONG lOptName,
                                                           MBUF_S **ppMPtr);

VOID IP6_ICMP6_RedirectOutput(MBUF_S *pstMBuf, const ICMP6_ROUTE_S *pstRt);

VOID IP6_ICMP6_NotifyInput(MBUF_S *pstMBuf);

ULONG IP6_ICMP6_ErrorRateLimitTimeout(VOID *pTemp);

ULONG IP6_ICMP6_TooBigErrorRateLimitTimeout(VOID *pTemp);

ULONG IP6_ICMP6_TooBigErrorRateLimit ();

extern VOID IP6_ICMP6_SendInfo2IC (const ICMP6_S *pstIcmp6,
                               const IN6ADDR_S *pstSrcaddr,
                               const IN6ADDR_S *pstDstaddr,
                               ULONG ulFlag);

ULONG IP6_ICMP6_GetIntfStatistics(ULONG ulIfIndex, ICMP6STAT_S *psticmp6stat);

ULONG IP6_ICMP6_ResetIntfStatistics(ULONG ulIfIndex);
ULONG IP6_ICMP6_PacketValidation(MBUF_S  *pstMBuf,ICMP6_S  *pstIcmp6,
                                IN6ADDR_S *pstDstaddr, IN6ADDR_S *pstSrcaddr);
ULONG IP6_ICMP6_RegNPCallback(IPV6_PPI_HOOK_S *pstCallbackFunc);

#if (IPBIR_IPV6_NP_SUPPORT  == VRP_YES)
ULONG IP6_ICMP6_Notify_PPI(ULONG ulOper, VOID *pvInfo);
#endif

ULONG IP6_ICMP6_Reg_Flow_Callback(ICMP6_EXT_CALLBACK_S *pstCallBack);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ICMP6_PRIVATE_H_ */



