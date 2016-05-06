/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              raw_ip6_api.h
*
*    Project Code: VRP5.0
*    Version     : Initial Draft
*    Module Name : IP6 RawIp6
*    Create Date : 2003/06/23
*    Author      : Sunil Dutt
*    Description : To define Prototype of RawIp6 Functions  that are required
*                  by other components
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-23  Sunil Dutt       Create
*************************************************************************/
#ifndef _RAW_IP6_API_H
#define _RAW_IP6_API_H

#ifdef  __cplusplus
extern "C" {
#endif

/* CPD guideline conformance - Alok 70823 01/03/2006 */
extern ULONG IP6_RIP6_QueryInterface(IUnknown* This, COMP_IID iid,
                                    LPVOID  *ppvraw_ip6vObj);

extern ULONG IP6_RIP6_Init_Com(COM_ID_INFO_S *pstComInfo,ULONG ulComLen);

extern ULONG IP6_RIP6_Activate_Com(VOID);

extern ULONG IP6_RIP6_SetModuleInfo(IP6_RIP6_MOD_INFO_S *pstMInfo);

extern VOID IP6_RIP6_Reg_SockAPI (
                                    SOSB6_CALLBACUP_SET_S *pfSocketTL6CallBack);

extern ULONG IP6_RIP6_ResetStatistics(VOID);

extern ULONG IP6_RIP6_GetStatistics(RIP6STAT_S *pstRip6Stats);

extern ULONG IP6_RIP6_Input (MBUF_S **ppstMBuf, ULONG *pulOff,
                                  ULONG ulProto);

extern VOID IP6_RIP6_Reg_IN6PCBAPI
                            (IN6PCB_CALLBACUP_SET_S *pfIn6PCBTL6CallBack);

extern LONG IP6_RIP6_Output(MBUF_S *pstMBuf, UINTPTR  ulSock,
                                   SOCKADDR_IN6_S *pstDstAddr,MBUF_S *pstMCtl);

extern LONG IP6_RIP6_CtlOutput(LONG lOper, UINTPTR ulSock,LONG lLevel,
                                    LONG lOptName, MBUF_S **ppMBuf);

extern LONG IP6_RIP6_Usrreq(UINTPTR ulSock, LONG lReq,VOID *pstMBuf,
                                    VOID *pstMName, VOID *pstMCtl);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _RAW_IP6_API_H_ */

