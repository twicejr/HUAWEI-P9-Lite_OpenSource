/*******************************************************************************
*                          icmp6_api.h
*  Project Code    : VRP3.0
*  Author          : Mayun  / Mahaveer Jain
*  Create Date     : 2002-8-20
*  Version         :
*  Description     : 本文件是icmp6.h文件
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
#ifndef _ICMP6_API_H_
#define _ICMP6_API_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern ULONG IP6_ICMP6_QueryInterface(IUnknown * This, COMP_IID iid,
                                                       LPVOID *icmp6vObj);

extern ULONG IP6_ICMP6_Init_Com(const COM_ID_INFO_S *pstComInfo,
                                                       ULONG ulComLen);

extern ULONG IP6_ICMP6_Activate_Com();

extern ULONG IP6_ICMP6_SetModuleInfo(IP6_ICMP6_MOD_INFO_S *pstMInfo);

extern ULONG IP6_ICMP6_RegShellCallBackFunc(
                               IP6_ICMP6_SH_CALLBACK_FUNC_S *pstCallbackFunc);

extern ULONG IP6_ICMP6_IncrementStatistics(ULONG ulIfIndex,
                                           ICMP6STATFIELD efield,
                                           UCHAR ucType);

ULONG IP6_ICMP6_ErrorRateLimitTimeout(VOID *pTemp);

ULONG IP6_ICMP6_TooBigErrorRateLimitTimeout(VOID *pTemp);

extern ULONG IP6_ICMP6_Input(MBUF_S **ppstMBuf,  ULONG *puLOff,
                                    ULONG ulProto);

extern VOID IP6_ICMP6_Error(MBUF_S *pstMBuf, UCHAR ucType, UCHAR ucCode,
                                                           LONG lParam);

extern ULONG IP6_ICMP6_NotifyError(MBUF_S *pstMBuf, ULONG ulOff,
                                              ULONG ulIcmp6Len, UCHAR ucCode);

extern VOID IP6_ICMP6_RedirectOutput(MBUF_S *pstMBuf,
                                         const ICMP6_ROUTE_S *pstRt);

extern LONG IP6_ICMP6_CtlOutput(LONG lOper, UINTPTR ulSockId, LONG lLevel,
                                           LONG lOptName, MBUF_S **ppMPtr);

extern ULONG IP6_ICMP6_ResetStatisticsByType(ICMP6STATFIELD efield,
                                             UCHAR ucType);

extern ULONG IP6_ICMP6_GetStatisticsByType(ICMP6STATFIELD efield,
                                                UCHAR ucType, ULONG *ulVal);

extern ULONG IP6_ICMP6_ErrorRateLimitGetValue(ULONG *pulInterval,
                                              ULONG *pulTockens);

extern ULONG IP6_ICMP6_ErrorRateLimitUpdate(const ICMP6_ERRRATE_MSG_S *pstBuf);

/* Start: RFC4443 compliance changes */
extern ULONG IP6_ICMP6_EnableDisableIntfDestUnReachError(ULONG ulIfindex, 
                                                        ULONG ulOperation);

/* End: RFC4443 compliance changes */

extern ULONG IP6_ICMP6_SOSB6_Socket_RegisterCallBack(
                                       SOSB6_CALLBACUP_SET_S *pstCallbackFunc);

extern ULONG IP6_ICMP6_IN6PCB_Socket_RegisterCallBack(
                                      IN6PCB_CALLBACUP_SET_S *pstCallbackFunc);

extern IN6ADDR_S* IP6_ICMP6_SelectSrcAddr(const IN6ADDR_S *pstDstAddr,
                                             IN6ADDR_S *pstSrcAddr,
                                             USHORT usVrfIndex);

extern ULONG IP6_ICMP6_GetAllStatistics(ICMP6STAT_S *pstIcmp6Stat);

extern ULONG IP6_ICMP6_ResetAllStatistics();

extern ULONG IP6_ICMP6_SetTooBigErrorRateLimit (ULONG ulRateStatus);

extern ULONG IP6_ICMP6_TooBigErrorRateLimit ();

/* SSA Interface */
IIF_IP6_ICMP6_ComIntSSA       g_IComInt_ICMP6_SSA;

/* CFG Interface */
IIF_IP6_ICMP6_ComIntCFG       g_IComInt_ICMP6_CFG;

/* Functional Interface */
IIF_IP6_ICMP6_ComIntFun       g_IComInt_ICMP6_FUN;

/* INIT Interface */
IIF_IP6_ICMP6_ComIntINIT      g_IComInt_ICMP6_INIT;

/* TEST Interface */
IIF_IP6_ICMP6_ComIntTEST      g_IComInt_ICMP6_TEST;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ICMP6_API_H_ */

