/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_pkt.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP PKT
*  Date Created: 2008-06-02
*        Author: Wangchengyang
*   Description: PTP PKT模块函数头文件声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _PTP_PKT_H_
#define _PTP_PKT_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTP_PKT_ProcHandshakeReq(PTP_HANDSHAKE_REQ_S *pstHandshakeReq, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_PKT_RcvEventMsg(UCHAR *pucBuffer, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);

/*qinyun&luogaowei 0地址方案 2011-12-12 start*/
/*ULONG PTP_PKT_RcvGeneralMsg(UCHAR *pBuffer, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo,UCHAR *pucMacAddr,ULONG 
ulifindex);*/
ULONG PTP_PKT_RcvGeneralMsg(UCHAR *pBuffer, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo,UCHAR *pucMacAddr);
/*qinyun&luogaowei 0地址方案 2011-12-12 end*/

ULONG PTP_PKT_GeneralHeaderCheck(PTP_PORT_S *pstPtpPort, PTP_MSGHEADER_S *pstMsgHeader, ULONG ulPacketLen);


ULONG PTP_PKT_HeaderCheck(PTP_PORT_S *pstPtpPort, PTP_MSGHEADER_S *pBuffer, ULONG ulPtpMsgType, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_PKT_MasterHeaderBuild(PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S*pstSlave, PTP_MSGHEADER_S *pstMsgHeader, ULONG ulPtpMsgType);

ULONG PTP_PKT_NonMasterHeaderBuild(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S *pstUnicastMaster, PTP_MSGHEADER_S *pstMsgHeader, ULONG ulPtpMsgType);

ULONG PTP_PKT_HeaderBuild(PTP_PORT_S * pstPtpPort, VOID * pData, UCHAR * pBuffer, ULONG ulPtpMsgType);

ULONG PTP_PKT_AnnSequenceIdCheck(PTP_PORT_S *pstPtpPort, USHORT usSequenceId, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

ULONG PTP_PKT_SigSequenceIdCheck(PTP_PORT_S *pstPtpPort, PTP_SIGNALING_HEARDER_S *pstHeader, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

VOID PTP_PKT_PrintEventMsg(CHAR *pcBuffer, PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag);

VOID PTP_PKT_PrintHeader(PTP_MSGHEADER_S *pstMsgHeader, PTP_ADDRINFO_S *pstAddrInfo);

LONG PTP_PKT_CircularSpaceCmp(USHORT a, USHORT b, USHORT usHalfSpace);

ULONG PTP_PKT_FlagfieldCheck(PTP_PORT_S *pstPtpPort, CHAR *pcFlagfield);

ULONG PTP_PKT_FlagfieldBuild(PTP_PORT_S * pstPtpPort, PTP_MSGHEADER_S * pstMsgHeader, ULONG ulPtpMsgType);

ULONG PTP_PKT_SndLiveMsg(PTP_PORT_S *pstPtpPort, PTP_PORT_ADDR_S *pstDstPortAddr);

ULONG PTP_PKT_RcvLiveMsg(UCHAR *pucBuffer, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_PKT_StateCheck(PTP_PORT_S *pstPtpPort);


#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTP_PKT_H_    */ 

