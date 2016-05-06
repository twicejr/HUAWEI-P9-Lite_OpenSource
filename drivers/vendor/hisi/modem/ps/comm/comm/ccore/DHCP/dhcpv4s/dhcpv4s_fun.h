
#ifndef _DHCPV4S_FUN_H_
#define _DHCPV4S_FUN_H_


/*****************************************************************************
 函 数 名  :Dhcp4vs_Debug_OnOff 
 功能描述  : LAP模块的调试开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 
 被调函数  : 

 修改历史      : 
  1.日    期   : 2010-08-10
    作    者   : jiahuidong 00142544
    修改内容   : 新生成函数

*****************************************************************************/
extern VOID Dhcp4vs_Debug_OnOff( ULONG argc, CHAR * argv [ ] );

/*本模块定义的函数*/

VOID DHCPS_FSM_Run(DHCPS_PRE_RESULT_S *pstPreResult);

VOID DHCPS_FSM_Register(VOID);

ULONG DHCPS_FSM_IDLE_ReceiveDiscover(
                                                                         DHCPS_PRE_RESULT_S *pstPreResult,
                                                                         DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_IDEL_ReceiveRequest(
                                                                         DHCPS_PRE_RESULT_S *pstPreResult,
                                                                         DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_IDLE_ReceiveRelease(
                                                                         DHCPS_PRE_RESULT_S *pstPreResult,
                                                                         DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_REQUESTIP_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_REQUESTIP_AddressAllocateSuccess(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_REQUESTIP_AddressAllocateFailed(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_REQUESTIP_Deactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_REQUESTIP_USMTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_OFFERED_ReceiveDiscover(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_OFFERED_ReceiveRequest(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);


ULONG DHCPS_FSM_OFFERED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);


ULONG DHCPS_FSM_OFFERED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_OFFERED_Deactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_OFFERED_ClientTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_ReceiveDiscover(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_ReceiveRequest(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_ReceiveInform(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_ReceiveDeactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

ULONG DHCPS_FSM_COMMITED_LeaseTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);

/* Added start by ZhangYang  z00142225 at 2008-12-29 UGWV900R001C001 for 地址分配功能 */
ULONG DHCPS_FSM_RELAY_ReceiveDiscover(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_RELAY_ReceiveRequest(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_RELAY_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_RELAY_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_RELAY_ReceiveInform(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);
ULONG DHCPS_FSM_RELAY_ReceiveDeactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet);
/* Added end by ZhangYang  z00142225 at 2008-12-29 UGWV900R001C001 for 地址分配功能 */
ULONG   DHCPS_FSM_ReleaseResource(DHCPS_LEASE_S *pstLease);

ULONG   DHCPS_FSM_InitLease(DHCPS_LEASE_S *pstLease);

ULONG DHCPS_ENC_SendMsg(DHCPS_LEASE_S *pstLease, ULONG ulMsgType);
/* Added start by ZhangYang  z00142225 at 2008-12-30 UGWV900R001C001 for 地址分配功能 */
ULONG DHCPS_RELAY_SendMsg(DHCPS_LEASE_S *pstLease, UCHAR ucMsgType, UCHAR *pucDateMsg,ULONG ulIpPacketLen);
/* Added end by ZhangYang  z00142225 at 2008-12-30 UGWV900R001C001 for 地址分配功能 */

ULONG DHCPS_TIMER_StartTimer(DHCPS_LEASE_S *pstLease, DHCPS_TIMER_TYPE_E enTimerType, ULONG ulTimerLen);

ULONG DHCPS_TIMER_StopTimer(DHCPS_LEASE_S *pstLease, DHCPS_TIMER_TYPE_E enTimerType);
VOID DHCPS_ChangeTimerNode(ULONG ulOldIndex, ULONG ulNewIndex);


VOID DHCPS_DelHeadNode(DHCPS_TIMER_LINKLIST_S** ppstHead);
VOID DHCPS_DelLinkNode(DHCPS_TIMER_LINKLIST_S** ppstHead, DHCPS_TIMER_LINKLIST_S* pstNode);

VOID DHCPS_FSM_PreMsgFromUSM(UCHAR *pstRspMsg);

ULONG   DHCPS_FSM_SendMSG2USM(DHCPS_USM_MSG_S     *pstMsg);

extern ULONG DHCPS_GetLeaseTime(ULONG ulPdpIndex, ULONG *pulTimerLen);

extern ULONG DHCPS_Tmr_Init(VOID);

/*本模块使用的外部函数*/


/* Added start by dongmingzhou 42828 at 2009-03-17 UGWV9R1C1 for 备份 */
ULONG DHCPS_HA_BackupProc( char **ppbuff,  ULONG ulIndex );
ULONG DHCPS_HA_SLAVE_CreateProc( char **ppbuff,  ULONG ulIndex );
ULONG DHCPS_HA_SLAVE_UpdateProc( char **ppbuff,  ULONG ulIndex );
ULONG DHCPS_HA_SLAVE_DeleteProc( ULONG ulIndex );
/* Added end by dongmingzhou 42828 at 2009-03-17 UGWV9R1C1 for 备份 */

VOID  DHCPS_TimerOut(VOID);
VOID DHCPS_StateTimerMsgProc(VOID);
VOID DHCPS_LeaseTimerMsgProc(VOID);
ULONG DHCPS_DPEDhcpMsgProc( UCHAR * pucMsg, ULONG ulMsgLen);
VOID DHCPS_GetConfig(VOID);
VOS_VOID DHCPV4S_DebugCmdInit(UINT64 ul64Csi);
ULONG DhcpEncapSendRequestMsg(DHCPS_LEASE_S *pstLease);
ULONG DHCP_ENC_SEND_DISCOVER_MSG(DHCPS_LEASE_S *pstLease);
extern VOS_VOID  DHCPv6_RecvMsgHandle(VOID);
/*m00221573 ¨¨????tpclint 2012-10-16 start*/
extern VOS_VOID DHCPS_V4_CallBackReg(VOID);
extern ULONG DHCPS_CommInit1(VOID);
extern VOID DHCPS_ProcSelfMsg(VOID* pMsg);
extern ULONG DHCPS_CommInit3(VOID);
extern ULONG DHCPS_StartWorkProc(VOID);
extern VOID DHCPS_SendLeaseTimeOutInnerMsg(VOID);
extern VOID DHCPS_SendStateTimeOutInnerMsg(VOID);
extern ULONG DHCPS_RegLogCnt(VOID);
/*m00221573 ¨¨????tpclint 2012-10-16 end*/


extern USHORT DHCPS_IpCkSum(USHORT* pusIpMsg,ULONG ulWordNum);

/*其他模块函数声明*/
extern VOID OutString ( char * szString );

extern ULONG PGP_GetTrcStartID(CHAR* szTaskName);
extern ULONG  AM_USM_NotifyBackupByIndex (ULONG ulIndex, UCHAR ucType);
extern ULONG DHCPS_DEC_Decode (UCHAR *pucUdpBuf, USHORT usUdpBufLen ,DHCPS_ANALYZEDPACKET_S *pstAnalyzedPacket);
extern ULONG DHCPS_IsTimerOn(ULONG ulIndex, ULONG ulTimerType);
extern ULONG DHCPS_FSM_LeaseStateIsValid(ULONG ulIndex);

USHORT ICMPv6_CheckSum(UCHAR *ptr, const in6_addr src, const in6_addr des, const UCHAR *msg,
                                                    USHORT usLen, USHORT *pusCheckSum, UCHAR ucPro);
ULONG UGW_GtpEncap( PMBUF_S *pMbuf, ULONG ulPdpIndex );
ULONG UGW_GRE_Encap(PMBUF_S *pMbuf, ULONG ulPdpIndex );
ULONG AM_CtxApiGetApnInfo( ULONG ulPdnIndex, AM_CTX_APN_INFO_S *pstApnInfo);
VOID UGW_OmAccessMsgTrc(UCHAR *pMsg,
                      E_TRACE_TYPE enTraceType,
                      ULONG  ulMsgClass,
                      ULONG  ulGtpMsgType,
                      ULONG  ulPeerIpAddr,
                      USHORT usMsgLen);
VOID GTPC_OmExternInterfaceTrcProcess(UCHAR *pMsg, E_TRACE_TYPE enTraceType, UGW_EXTERN_INTF_TRACE_S stTraceInfo);
VOID AM_CtxApiGetReqApnIndexByPdpContext(SDB_GSPU_CONTEXT_S *pstContext,USHORT *pusRequestIndex,UCHAR *pucAliaApnFlag);
ULONG IPV6_SrcAddrValidationCheck(IPV6HDR_S *pstIpv6Hdr);
PF_ULONG fwd_get_ctrlhdr_pdpindex(FWD_TO_CTRL_HDR* pstCtrlHdr);
VOID LAP_SetPrefixLengthIp(ULONG aulOldIp[], UCHAR ucPrefixLength, ULONG aulNewIp[],
                            UCHAR *pucPos, UCHAR *pucMoveBitNum);
ULONG PTM_DebugBatchSProcDebugCmdRspMsg(UCHAR *pucMsg);
VOS_UINT32 CLAP_TaskInit(VOS_UINT64 ullCsi, ULONG ulHandle);
ULONG CLAP_TaskConfirm(ULONG ulTaskID);
VOID CLAP_TaskProcess();
VOID Path_GetVpn(SDB_GSPU_CONTEXT_S *pstContext, ULONG *pulVpnId);




#endif
