/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         iphc_fun.h
 *
 *  Project Code: VISP
 *   Module Name: IPHC
 *  Date Created: 2002/06/25
 *        Author: wangyue
 *   Description: 本头文件包含iphc模块的宏定义；   
 *
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-03-30      xiehuaguo       Adjust for D00647
 *  2006-05-13      l48923          Delete useless code
 *
 ************************************************************************/
 
#ifndef _IPHC_FUN_H_
#define _IPHC_FUN_H_


#ifdef  __cplusplus
extern "C"{
#endif

/*----------------    组件相关函数    ----------*/
ULONG IPHC_QueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

ULONG IPHC_Init_Com(VOID);
ULONG IPHC_Activate_Com(VOID);
ULONG IPHC_SetModuleInfo(struct tagIPHC_Mod_Info *pstMInfo);

ULONG IPHC_RegShellApi(struct tagIPHC_SHELL_CALLBACK_SET *pstCallBkSet);

ULONG ImplIPHCFactoryQueryInterface(IUnknown *This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplIPHCFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );

/*----------------    新增的配置函数    -------*/
ULONG IPHC_ProcessTcpDebug(ULONG ulSetYes);
ULONG IPHC_ProcessNonTcpDebug(ULONG ulSetYes);

struct tagIPHC_COMPRESSION_CONTEXT *IPHC_Initiate( ULONG ulIfIndex, 
                                                   ULONG CCOMPANY,
                                                   ULONG DELETE_UDP_CHECKSUM,
                                                   PPP_IPCP_OPTION_S *pstGotOption, 
                                                   PPP_IPCP_OPTION_S *pstHisOption);


VOID IPHC_TCPRelease(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
/* VOID IPHC_RTPRelease(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context); */
VOID IPHC_NonTCPRelease(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
struct tagIPHC_COMPRESSION_CONTEXT *IPHC_Release(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);

/* Modified by z43740: 将参数类型改为VOID*, 2007-03-28 */
VOID IPHC_TimerCall(VOID *pArg);
/* End of modification */

 /* 将函数返回值由VOID改为ULONG */
ULONG IPHC_TCPCidCheck(struct tagIPHC_COMPRESSION_CONTEXT *pContext);
UCHAR IPHC_TCPCidRequest(struct tagIPHC_COMPRESSION_CONTEXT *pContext,struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *pContest_Struct);
VOID IPHC_RTPCidCheck(struct tagIPHC_COMPRESSION_CONTEXT *pContext);
USHORT IPHC_RTPCidRequest(struct tagIPHC_COMPRESSION_CONTEXT *pContext,struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *pContest_Struct);
struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *IPHC_SearchTCPContext(struct tagIP *pIP,struct tagTCPHDR *pTCP,struct tagIPHC_COMPRESSION_CONTEXT *pContext,UCHAR *pFind);
struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *IPHC_SearchRTPContext(struct tagIP *pIP,struct tagUDPHDR *pUDP,struct tagRtp_Hdr_t *pRTP,struct tagIPHC_COMPRESSION_CONTEXT *pContext,UCHAR *pFind);
USHORT IPHC_Compression(MBUF_S **ppMbuf,struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context,USHORT usIPHC_Type);
USHORT IPHC_Decompression(MBUF_S **ppMbuf,struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context,USHORT usIPHC_Type);
LONG IPHC_DebugAll(VOID);
LONG IPHC_NoDebug(VOID);
LONG IPHC_ShowDebug(CHAR *pszStatusStr, ULONG ulMaxLen, ULONG ulIfIndex, 
                      ULONG *pulWaitListIndex, ULONG ulInterface);
VOID IPHC_DebugOutString (CHAR * szStr);
ULONG IPHC_RegToIC (VOID);
VOID IPHC_Init ( VOID );
ULONG IPHC_ProcessNonTcpContextRefreshTime(ULONG ulTime);

VOID IPHC_TcpStatClear(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
VOID IPHC_NonTcpStatClear(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
ULONG IPHC_GetIfIPHCStatistics(ULONG ulIfIndex, TCPIP_IPHC_STATISTICS_S *pstIPHCStatistics);

/* End of addition */


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


#endif
/* end of iphc_fun.h */

