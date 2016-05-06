/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              raw_ip_func.h
*
*  Project Code: VISP1.5
*   Module Name: RawIP
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _RAW_IP_FUNC_H_
#define _RAW_IP_FUNC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/rawip4/include/rawip_api.h"
struct tagSOCKET;
struct tagROUTE;
struct tagRIPSTAT;
struct tagRIP4_MOD_INFO;


ULONG IP4_RIP4_QueryInterface(IUnknown* This, COMP_IID iid, LPVOID *raw_ipObj);
ULONG IP4_RIP4_Init_Com(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen) ;
ULONG IP4_RIP4_Activate_Com();
ULONG IP4_RIP4_SetModuleInfo(struct  tagRIP4_MOD_INFO *pstMInfo );

VOID RIP_Input(MBUF_S *pMBuf);
LONG RIP_Output( MBUF_S *pMBuf, VOID *pSock,VOID* ,ULONG ulDst,VOID* );
LONG RIP_CtlOutput(LONG nOper, VOID *pSock, LONG nLevel, LONG nOptName, MBUF_S **pMP);
LONG IP_CtlOutput(LONG nOper, struct tagSOCKET *pSock,  LONG nLevel, LONG nOptName, MBUF_S **pMPtr );
LONG RIP_UsrReq(struct tagSOCKET *pSock, LONG nReq,MBUF_S *pMBuf,MBUF_S *pMName, MBUF_S *pMCtl);
ULONG RIP_ResetStatistics(VOID);
ULONG RIP_GetStatistics(struct tagRIPSTAT *pstRipStats);

ULONG  IP4_RIP4_FAC_QueryInterface(IUnknown * This, COMP_IID iid, VOID ** ripvObj);
ULONG IP4_RIP4_FAC_CreateInstance(IComponentFactory * This,  COMP_IID iid, VOID ** ripvObj );
ULONG RIP_LocateTargetSocket(ULONG ulIfIndex,ULONG ulDestAddr, TARGET_SOCKET_S *pstTargetSkt);

ULONG RAWIP_GetPerRawip4ConnStats(RAWIP4CONN_S *pstConnInfo, RAWIP4PERSTAT_S  *pstRetStats);
ULONG RAWIP_ResetPerRawip4ConnStats(RAWIP4CONN_S *pstConnInfo);


#ifdef __cplusplus
}
#endif

#endif  /* _RAW_IP_FUNC_H_ */


