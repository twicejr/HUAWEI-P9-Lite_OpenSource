/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_sig.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP PKT
*  Date Created: 2008-06-02
*        Author: lishenchuan
*   Description: PTP PKT模块函数头文件声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02      Lishenchuan       Create
*
*******************************************************************************/

#ifndef _PTP_SIG_H_
#define _PTP_SIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Mod By t00110672 For BC3D01422,2009.5.7,增加最后一个参数lTmpLenth*/
ULONG PTP_SIG_ProcRequestUnicast(PTP_PORT_S *pstPtpPort, CHAR *pcTlv, PTP_MSGHEADER_S*pstHeader, PTP_ADDRINFO_S *pstAddrInfo,LONG lTmpLenth);
/*End*/

ULONG PTP_SIG_ProcGrantUnicast(PTP_PORT_S *pstPtpPort, CHAR *pcTlv, PTP_MSGHEADER_S*pstHeader, PTP_ADDRINFO_S *pstAddrInfo);


ULONG PTP_SIG_ProcCancelUnicast(PTP_PORT_S *pstPtpPort, CHAR *pcTlv, PTP_MSGHEADER_S*pstHeader, PTP_ADDRINFO_S *pstAddrInfo);


/* lishch added */
ULONG PTP_SIG_ProcMasterAnnAckCancel(PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcMasterSyncAckCancel(PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcMasterDelayAckCancel(PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcSlaveAnnAckCancel(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S *pstUniMasterNode, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcSlaveSyncAckCancel(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S *pstUniMasterNode, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcSlaveDelayAckCancel(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S *pstUniMasterNode, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcMasterAckCancel(USHORT usMsgType, PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);
ULONG PTP_SIG_ProcSlaveAckCancel(USHORT usMsgType, PTP_PORT_S *pstPtpPort, PTP_PPI_S *pstPtpPpi, PTP_ADDRINFO_S *pstAddrInfo);
ULONG PTP_SIG_ProcAckCancelUnicast(PTP_PORT_S *pstPtpPort, CHAR *pcTlv, PTP_MSGHEADER_S* pstHeader, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_SIG_ProcExtensionTlv(PTP_PORT_S *pstPtpPort, CHAR *pcTlv, PTP_MSGHEADER_S*pstHeader, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_SIG_RcvSigMsg(UCHAR *pucBuffer, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_SIG_SndSigMsg(PTP_PORT_S * pstPtpPort, VOID * pData, ULONG ulPtpTlvTpye, ULONG ulMsgTpye, BOOL_T bGrantR);

ULONG PTP_SIG_BuildOneSigMsg(PTP_PORT_S * pstPtpPort, VOID * pData, CHAR * pcBuffer, ULONG ulPtpTlvTpye, 
    ULONG ulMsgType, BOOL_T bGrantR,BOOL_T bTwoTlv);

VOID PTP_SIG_PrintSig(PTP_SIGNALING_HEARDER_S *pstSigMsgHeader, PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag);

ULONG PTP_SIG_BuildReqTlv(PTP_PORT_S *pstPtpPort,CHAR *pcTlv,CHAR *pcExtenTlv,ULONG ulMsgType,BOOL_T bTwoTlv);

/*Mod By t00110672/z00146309  10-1-11,支持路由器关于实现最新草案的需求 */
/*增加pstDstPortAddr参数*/
ULONG PTP_SIG_BuildGrantTlv(PTP_PORT_S * pstPtpPort, PTP_UNI_SLAVE_NODE_S * pstUnicastSlave, CHAR * pcTlv, ULONG ulMsgType, BOOL_T bR);
/*Mod End*/

ULONG PTP_SIG_BuildCancelTlv(PTP_PORT_S *pstPtpPort,CHAR *pcTlv,ULONG ulMsgType);

ULONG PTP_SIG_BuildAckTlv(PTP_PORT_S *pstPtpPort,CHAR *pcTlv,ULONG ulMsgType);

/*ST问题: 增加DELAY的多播处理 20080715 l00128792*/
ULONG PTP_SIG_ProcMDelayAckCancel(USHORT usMsgType, PTP_PORT_S *pstPtpPort, PTP_PPI_S *pstPtpPpi);
/*ST问题: END*/
VOID PTP_SIG_ProcRequestOtherMsg(PTP_PORT_S * pstPtpPort, PTP_REQUEST_UNICAST_TLV_S * pstReqUniTranTLV, PTP_MSGHEADER_S * pstHeader, PTP_ADDRINFO_S * pstAddrInfo, PTP_UNI_SLAVE_NODE_S * pstUnicastSlave);
VOID PTP_SIG_AddUnicastLinkPpi(PTP_PORT_S *pstPtpPort, 
	                     PTP_UNI_MASTER_NODE_S* pstUniMaster,PTP_ADDRINFO_S *pstAddrInfo);
VOID PTP_SIG_SetUnicastLinkPpi(PTP_PORT_S *pstPtpPort, 
	                     PTP_UNI_MASTER_NODE_S* pstUniMaster, PTP_ADDRINFO_S *pstAddrInfo);
ULONG PTP_SIG_CreateDelayDurTimer(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S* pstUniMaster);
ULONG PTP_SIG_CreateSyncDurTimer(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S* pstUniMaster);
ULONG PTP_SIG_CalcPeriod(ULONG ulDuration);
ULONG PTP_PRINTOUT_PrintTimer(CHAR szActName [],PTP_UNI_MASTER_NODE_S * pstUniMaster);


#ifdef __cplusplus
}
#endif

#endif

