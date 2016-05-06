/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                               dcc_func.h
*
*  Project Code: VR8C01
*   Module Name: PUBLIC
*  Date Created: 2009-03-25
*        Author: zhangchunyu(62474)
*   Description: 数据连通性检查处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-03-25   zhangchunyu(62474)      Create
*******************************************************************************/
#ifndef _DCC_FUN_H_
#define _DCC_FUN_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*******************************函数声明***************************************/

extern ULONG DCC_Init(VOID);

extern ULONG DCC_ProtoCheck(TCPIP_DCC_S *pstDcc);
extern ULONG DCC_DiagnoseInterface(CHAR *pszIntf);
extern ULONG DCC_DiagnoseLinkLayer(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);
extern ULONG DCC_CheckETH(ULONG ulIpAddr, ULONG ulIfIndex, ULONG ulVrfIndex);
extern ULONG DCC_ArpPing(ULONG ulIpAddr, ULONG ulIfIndex, ULONG ulVrfIndex);
extern ULONG DCC_GetArp(ULONG ulIPAddr, ULONG ulVrfIndex);
extern ULONG DCC_DiagnoseTransLayer(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);
extern ULONG DCC_DiagnoseTCP(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);
extern ULONG DCC_DiagnoseUDP(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);
extern ULONG DCC_DiagnoseRAWIP(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);
extern ULONG DCC_TCP_Check(INPCB_S *pstInPCB, TCPCB_S *pstTCPCB, SOCKET_S *pstSocket);
extern ULONG DCC_NonTcpSocketCheck(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);
extern ULONG DCC_SocketID_Check(TCPIP_DCC_S *pstUserDcc, SOCKET_S **ppstSocket, INPCB_S **ppstInPCB);
extern ULONG DCC_INPCB_Check(TCPIP_DCC_S *pstUserDcc,INPCB_S **ppstInPCB, ULONG ulVrfIndex);
extern ULONG DCC_TCPCB_Check(INPCB_S *pstInPCB, TCPCB_S **ppstTCPCB);
extern ULONG DCC_SOCKETCB_Check(INPCB_S *pstInPCB, SOCKET_S **ppstSocket);
extern VOID DCC_GetInpcbInfo(INPCB_S *pstInPCB);
extern VOID DCC_GetTcpcbInfo(TCPCB_S *pstTCPCB);
extern VOID DCC_GetSocketCBInfo(SOCKET_S *pstSocket);
extern VOID DCC_PrintInpcbFlag(ULONG ulInpcbFlag, CHAR *szOutBuf, ULONG ulStrLen);
extern VOID DCC_PrintTcpState(ULONG ulTcpState,CHAR *szOutBuf, ULONG ulStrLen);
extern VOID DCC_PrintSocketState(ULONG ulSocketState,CHAR *szOutBuf, ULONG ulStrLen);
extern VOID DCC_PrintSocketOption(ULONG ulSocketOption,CHAR *szOutBuf, ULONG ulStrLen);
extern ULONG DCC_DoPing(ULONG ulExecID, TCPIP_DCC_S *pstUserDcc);
extern ULONG DCC_Ping(ULONG ulExecID, ULONG ulIpAddr);
extern ULONG DCC_DiagnoseFIB(ULONG ulDIP, ULONG ulSIP, ULONG ulVrfIndex);
extern VOID DCC_DeleteTask(VOID);
extern VOID DCC_DataStatResult(VOID *pstNull);
extern VOID DCC_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);
extern ULONG DCC_Start(ULONG ulTaskPri);
extern ULONG DCC_StartDiagnose(VOID);
extern VOID DCC_Release(VOID);

extern VOID DCC_DiagnosisInfo(DCC_OUTPUT_S *pszOutput, ULONG ulExecID);
extern ULONG DCC_DiagnoseNetLayer(TCPIP_DCC_S *pstUserDcc, ULONG ulVrfIndex);

extern ULONG DCC_FlowHaveIt(MBUF_S *pstMbuf, STREAMINFO *pstPktInfo, ULONG ulSndOrRcv);
extern ULONG DCC_FlowStatCheck_Rcv(DCC_STREAMSTAT_RCV_S *pstDccRcvStat);
extern ULONG DCC_FlowStatCheck_Snd(DCC_STREAMSTAT_SND_S *pstDccSndStat);
extern VOID DCC_DiagnosePacketFlowTimerOut(VOID *pPara);
extern ULONG DCC_DiagnosePacketFlow(VOID);

extern VOID DCC_ShowDCCFlowStat(ULONG ulStramID, ULONG ulRcvOrSend, CHAR *pcOutStrBuf, ULONG ulResult, ULONG ulStrLen);
extern ULONG DCC_FlowClassifyInMBuf_PPP(MBUF_S *pMBuf, USHORT usProtocol, ULONG ulHeadOffSet);
extern ULONG DCC_FlowClassifyInMBuf_ETH(MBUF_S *pMBuf);
extern ULONG DCC_GetPppProtocol(MBUF_S *pstMbuf, USHORT *pusProtocol);
extern ULONG DCC_FlowGetSoureIP(MBUF_S *pstMbuf, ULONG ulDipAddr, ULONG *pSoureIp, ULONG ulSendFlag, ULONG ulVrfIndex);
extern VOID  DCC_OutputDiagnoseMsg(CHAR *pucMsg, ULONG ulDiagnoseID, ULONG ulExecID);

#ifdef  __cplusplus 
}
#endif
#endif /* _DCC_FUN_H_ */


