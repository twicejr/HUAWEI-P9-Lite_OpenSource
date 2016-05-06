/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                           ppp_sh_main_cen.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2004-07-15
 *        Author: YiAn
 *   Description: PPP shellÍ·ÎÄ¼þ
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004-07-15      YiAn            Create
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *
 *************************************************************************/

#ifndef _PPP_SH_MAIN_CEN_H
#define _PPP_SH_MAIN_CEN_H

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_basefun.h"

#define TCPIP_PPP_INIT 0

extern ULONG ulVRPTID_SOCK;
extern ULONG ulSOCKTmrQueID;

ULONG PPP_Init(VOID);
ULONG PPP_NotifyIpcpDown(ULONG ulIfIndex);
VOID PPP_Shell_AuthRequest(ULONG ulIfnetIndex, PPPAUTHMSG_S * pMsg);
ULONG PPP_EnDropQue(MBUF_S *pMBuf);
VOID PPP_ShowDebugInfo(char *szString, ULONG ulLen);
ULONG PPP_Shell_Chap_GetUserPsw(PPPAUTHMSG_S *pstMsg);
ULONG PPP_GetPeerIPAddress(ULONG ulUserID, ULONG ulIfnetIndex,  PPP_GetPeerCallBack_PF pfGetPeerCallBack);
VOID PPP_FreeAddr(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);

extern ULONG Que_AddQueLen(ULONG ulQueID,ULONG ulLen);
extern ULONG Que_GetQueLen(ULONG ulQueID);
extern ULONG VOS_Tm_Now(ULONG *pulRetTimeInMillSecHigh, ULONG *pulRetTimeInMillSecLow);
extern ULONG TCPIP_IC_SendMsg(ULONG ulMid, ULONG ulInfoId, char *pBuf);

VOID PPP_ShowIfIPHCConfig(ULONG ulIfIndex);

VOID PPP_ShowIfIPHCStat(ULONG ulIfIndex, ULONG ulPacketType);

VOID PPP_CollectIfIPHCStat(IPHC_DEBUG_RTP_TCP_COMPRESSION_S *pstNewInfo, 
                           IPHC_DEBUG_RTP_TCP_COMPRESSION_S *pstTotalInfo);

VOID PPP_OutputIfIPHCStat(CHAR* pszIfName, 
                          IPHC_DEBUG_RTP_TCP_COMPRESSION_S* pstDebugInfo, 
                          ULONG ulNonTcp);

VOID PPP_ShowIfIPHCContext(ULONG ulIfIndex, ULONG ulPacketType, ULONG ulFlag);

VOID PPP_OutputIfIPHCContext(IPHC_COMPRESSION_CONTEXT_S *pstIPHCContext, 
                             ULONG ulPacketType, 
                             ULONG ulFlag,
                             CHAR* pszIfName);

VOID PPP_OutputTcpCompressContext(IPHC_TCP_CONTEXT_TABLE_STRUCT_S* pstContext, CHAR* pszIfName);

VOID PPP_OutputNonTcpCompressContext(IPHC_NON_TCP_CONTEXT_TABLE_STRUCT_S* pstContext, CHAR* pszIfName);

VOID PPP_OutputTcpDecompressContext(IPHC_TCP_CONTEXT_ARRAY_STRUCT_S* pstContext, CHAR* pszIfName);

VOID PPP_OutputNonTcpDecompressContext(IPHC_NON_TCP_CONTEXT_ARRAY_STRUCT_S* pstContext, CHAR* pszIfName);

INT32 PPP_OutputIPHeader(IP_S* pstIP, CHAR* pszStr, INT32 i32StrLen);

INT32 PPP_OutputTCPHeader(TCPHDR_S* pstTcp, CHAR* pszStr, INT32 i32StrLen);

INT32 PPP_OutputUDPHeader(UDPHDR_S* pstUdp, CHAR* pszStr, INT32 i32StrLen);

INT32 PPP_OutputRTPHeader(rtp_hdr_t* pstRtp, CHAR* pszStr, INT32 i32StrLen);

VOID PPP_ShowPPPStateByIndex(ULONG ulIfIndex);
VOID PPP_QueryPPPStateByIndex(IFNET_S* pszIf);

VOID PPP_ShowEffectiveCfg(ULONG ulIfIndex,ULONG ulProtocol);
VOID PPP_ShowPPPNegoInfobyIfindex(ULONG ulIfIndex);

#ifdef  __cplusplus
}
#endif

#endif/*#ifndef _PPP_SH_MAIN_CEN_H*/
