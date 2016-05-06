/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_func.h
  版 本 号   : 初稿
  作    者   : c57548
  生成日期   : 2007年11月3日
  最近修改   :
  功能描述   : dhcpc模块的函数声明
  函数列表   :
  修改历史   :
  1.日    期   : 2007年11月3日
    作    者   : c57548
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DHCPC_FUNC_H__
#define __DHCPC_FUNC_H__


extern ULONG g_aulGtpcSndLapDbgCnt[GTPC_SND2_LAP_CNT_COUNT];
extern UCHAR g_ucSoftParaDHCPKPN;
extern in6_addr in6addr_ggsn;

ULONG FCM_CreateFwdChannel(ULONG ulCompType, ULONG ulMsgType, ULONG ulCpuCompInstId);
VOS_UINT32 PTM_CreateMcQueue(PTM_QUEUE_INFO_S *pstQueInfo, VOS_UINT32* pulQueID);

/******************************************************************************
 Function   : VOS_MCQueueShow
 Description: 队列调试信息获取
 Input      : MCQueId - 共享队列ID，为0时显示不大于指定条数的使用态的队列信息
              pMCQueInfo - 存储调试信息的地址
              ulExpectCount - 用户期待的信息条数
 Output     : pulReadCount - 实际存储的信息条数
 Return     : 获取调试信息成功VOS_OK,失败返回错误码
 ******************************************************************************/
VOS_UINT32 VOS_MCQueueShow(MC_QUE_ID MCQueId, VOS_VOID* pMCQueInfo,
                                  VOS_UINT32 ulExpectCount, VOS_UINT32* pulReadCount);
VOS_UINT32 LAP2_McQue_IsEmpty( VOS_VOID *pvMCQueId );
VOID PGP_Ready();

ULONG FCM_ReadMCQue(ULONG ulCompType,
                    ULONG ulMsgType,
                    ULONG ulCpuCompInstId,
                    PMBUF_S **ppMBuf);

ULONG PGP_SetTaskRunConfirm();
VOS_UINT32 PGP_RTDistributeCallback(ULONG ulFlag, ULONG64 ul64DstCsi, VOID *pData, ULONG ulLen);
VOID PTM_Print_Exception_End(ULONG ulResultCode);
VOID PTM_Print_Exception_Info(UCHAR *pucStr);

VOID PTM_Print_Exception_Loop(UCHAR *pucStr, ULONG ulLoop, ULONG ulValue);
VOS_VOID  CDBRegCallBackCmd(CDB_TBLID         nTbl,       /* 表号 */
                                      CDB_CALLBACK_FUN pFun,        /* 函数指针 */
                                      ULONG64          ullCSI,      /* 那个任务注册的函数 */
                                      VOS_UINT8        ucFunType,   /* 回调函数的类型 */
                                      VOS_UINT8        ucBoardType, /* 注册在哪一种单板上 */
                                      VOS_INT8        *pcName);     /* 函数的名称 */
ULONG VOS_MCRWReadLock(MC_RWLOCK_ID RWLockID, VOS_CHAR *pFile, ULONG ulLine);
ULONG VOS_MCRWReadUnlock (MC_RWLOCK_ID RWLockID, VOS_CHAR *pFile, ULONG ulLine);

VOS_UINT32 VOS_MCRWWriteLock(MC_RWLOCK_ID RWLockID,VOS_CHAR *pFile,VOS_UINT32 ulLine);

VOS_UINT32 VOS_MCRWWriteUnlock (MC_RWLOCK_ID RWLockID, VOS_CHAR *pFile, VOS_UINT32 ulLine);

#ifndef __WIN32_PLATFORM_PTM__
void spin_lock(spinlock_t *lock);
void spin_unlock(spinlock_t *lock);
#endif

ULONG CRM_GetSelfLogicSlotID();
ULONG CRM_GetSlotPrimaryInfoOfSelfGroup(UCHAR ucSlotID);
VOID PTM_DebugBatchSRunCmdProc();
ULONG SPM_GetDwordValue(ULONG ulSoftparaNum, ULONG* ulDwordValue);
VOS_UINT32 VOS_MCRWLockCreate (VOS_CHAR* pName, MC_RWLOCK_ID *pIndex, VOS_UINT32 ulFlag );

VOS_UINT32 DBApiQueryFirst(CDB_TBLID nTableId,
                           VOS_INT32 dwCondNum,
                           S_CFG_CDB_CONDITION *pCond,
                           VOS_INT8 *pTuple,
                           VOS_UINT32 *pudwQueryId);
VOS_UINT32 DBApiQueryNext(VOS_UINT32 *pudwQueryId, VOS_INT8 *pTuple);
VOS_BOOL PSM_Inf_IsOnlySGRestarted();
VOS_UINT32 PGP_Timer_Create( VOS_UINT64 CSI, VOS_UINT32 ulTimerMsgType, VOS_UINT32 ulInterval, VOID (*cbFunc)(VOID *), VOS_VOID *pArg, RELTMR_T *pTimerID, VOS_UINT32 ulTimerMode);
VOS_UINT32 PGP_RTCreate(VOS_UINT64 ulSelfCSI, VOS_UINT32 uiFlag, VOS_UINT32 uiQueueID, IPC_RTNOTIFY_FUNC pfNotify);

VOS_INT32 VOS_atoul( const VOS_CHAR * pcStr, VOS_UINT32 * pulVal );
VOS_INT32 VOS_StrToUint32(const VOS_CHAR *szStr, VOS_UINT32 *pulVal);
VOID PTM_SetPrintLevel(PTM_DBG_PRINT_MODULE_E emModuleType, ULONG ulPrintLevel);

ULONG PTM_DbgLogRecordReg(PTM_DBG_PRINT_MODULE_E emModuleType, CHAR szSystemName[],
                          CHAR szModuleName[], CHAR szSubmoduleName[]);
VOS_UINT32 CommandsRegister (struct Command_Group_S *  pCommand_Group, VOS_CHAR *cpCommand, VOS_CHAR *cpHelp);
ULONG DebugPrintf(ULONG ulModId,  ULONG ulCtrlLevel, CHAR * pcFileName, USHORT ulLineNo, CHAR * cDbgInfo, ...);
VOID PTM_Print_String_With_Arguments(UCHAR *pszFormat, ...);
VOS_INT VOS_StrNCmp( VOS_CHAR * pscStr1, VOS_CHAR * pscStr2, SIZE_T ulCount );
VOS_INTPTR VOS_StrICmp(VOS_CHAR *pscStr1, VOS_CHAR *pscStr2);
VOS_UINT32 VOS_TmGet( DATE_T * pDate, TIME_T * pTime, VOS_UINT32 * pulMillSecs );
ULONG PTM_WriteDiagLog(ULONG ulDBGLogRegID, DBG_LOG_LEVEL_E enLogType,
    CHAR *szFileName, ULONG ulLineNumber, CHAR *pcFormat, ...);
ULONG LAP_IPv4AddrToStr( ULONG ulIpAddr, CHAR *szStr );
CHAR *LAP_Ipv6AddrToStr( ULONG* pulAddr, CHAR *szStr );
VOID PTM_StrNCpy(CHAR *pucDestStr, CHAR *pucSrcStr, ULONG ulMaxLength);
ULONG PTM_LogCnt_RecordReg(PTM_LogCnt_RecRegInfo_S *pstRegInfo);
VOS_VOID PTM_Dbg_RegMemoryPrint(VOS_UINT64 ullCsi );
VOS_UINT32 VOS_Tm_NowInSec( VOS_UINT32 *pulRetTimeInSec );

VOID OutString ( char * szString );
VOS_UINT32 DBApiQueryDirect(CDB_TBLID nTableId,
                            VOS_INT32 dwTupleNo,
                            VOS_INT8 *pTuple);
VOS_UINT32 CdbGetApnIndexByApnName(VOS_UINT8 *pucAPNName,  VOS_UINT16 *pusAPNIndex );
VOS_UINT32 PGP_Timer_Delete(RELTMR_T TimerID);
ULONG UDPS_PickUpExt( UDPS_PACKET_INFO_S * pstUdp, PMBUF_S *pstMbuf );
ULONG SPM_GetBitValue(ULONG ulSoftparaNum, UCHAR* ucByteValue);
ULONG AM_IsNeedChecksum(ULONG ulMsgCode);
ULONG UDPS_ConvertToSockAddr(SOCKADDRIN_S * pAddress, ULONG ulAddressLen);
LONG UDPS_DataHandle(UDPS_PACKET_INFO_S *pstPktInfo, PMBUF_S *pstMBuf);
ULONG CRM_GetSpuWorkModeOfSelfGroup(VOID);
ULONG  AM_USM_NotifyBackupByIndex (ULONG ulIndex, UCHAR ucType);
ULONG SDB_GTPC_GetRelatedContextsByTeidc(ULONG ulTeidc,  ULONG *pulNum, UCHAR *pucContextDim[]);
ULONG SDB_GetContextByIndex(ULONG ulSdbIndex, UCHAR **ppucContext);
VOS_UINT32 DHCPC_SendAddrMsgToLAP(VOS_VOID *pMsg, VOS_UINT32 ulMsgLegth, ULONG ulUserIpAddr, VOS_UINT8 ucLapNo);
VOS_BOOL PSM_Inf_GetStatByCSI(VOS_UINT64 CSI);

VOS_UINT32 PGP_URTDistributeSend(VOS_UINT64 ul64SrcCSI,
                                           VOS_UINT64 ul64DstCSI,
                                           PMBUF_S* pstMsgBuff,
                                           VOS_UINT32 ulMode,
                                           VOS_UINT32 ulMsgType,
                                           VOS_UINT32 ulGene);
ULONG GTPC_RadiusHlrIPValidCheck(ULONG ulAddr);
VOS_BOOL TrcGetTraceFlag(ULONG ulTrcType);
VOID UGW_OmUsrMsgTrace(UCHAR *pMsg,
                          ULONG    ulMsgClass,
                          ULONG    ulGtpMsgType,
                          USHORT   usMsgLen,
                          UCHAR*   pucImsi,
                          UCHAR*   pucImei,
                          MSISDN   aucMsisdn,
                          UCHAR   ucRandomNo);
ULONG ipv6_addr_any(in6_addr *a);
ULONG ipv6_addr_all_one(in6_addr *a);
void ipv6_addr_copy(in6_addr *a1, in6_addr *a2);
PF_VOID fwd_set_ctrlhdr_vcpuid(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulVcpuId);

PF_VOID fwd_set_ctrlhdr_vrfindex(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulVrfIndex);

PF_VOID fwd_set_ctrlhdr_msgcode(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulMsgCode);

PF_VOID fwd_set_ctrlhdr_moduleid(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulModuleId);
void ipv6_addr_set(in6_addr *addr, ULONG w1, ULONG w2,ULONG w3, ULONG w4);
void ipv6_addr_all_nodes(in6_addr *addr);
VOID UGW_OmEmsTrcMsgTrc(S_OM_EMS_TRC_PARA *pstTrcPara, RM_SOCKET_PATH_S* pstPath);
ULONG DVM_GetSelfLpid();
ULONG64 PGP_getTimeByTicksInMisc(void);
VOS_VOID FamTrcSendTrcMsgWithTime(UCHAR  ucTrcType,         /* 接口类型 */
                                            UCHAR* pFilter,           /* 过滤参数 */
                                            ULONG  ulReportMsgType,   /* 消息类型 */
                                            USHORT usLen,             /* 消息长度 */
                                            UCHAR* pMsg,              /*消息内容*/
                                            S_FAM_BAM_TRC_TIME_DATA stTime); /*时间信息*/
VOID EMS_DebugTrace(ULONG ulPdpIndex,USHORT usModule, USHORT usCode, UCHAR* szReason, UCHAR* szSuggestion );
USHORT LAP_IPv6GetAddrType( in6_addr *addr );
VOS_SIZE_T PerfGetFamPerfCounterAddress(    VOS_UINT32 enMeasureUnit,     VOS_UINT32 enMeasureEntity,     VOS_UINT8 *pucObjectData);
VOS_VOID * IPC_RPC_AllocMsg(VOS_UINT32 ulSize, VOS_UINT32 ulUserInfo);
ULONG DHCPS_DPEDhcpMsgProc( UCHAR * pucMsg, ULONG ulMsgLen);
VOS_UINT64 PSM_Inf_GetCSIBySGIDCmpTypeAndCmpInstId(VOS_UINT64 SGID,VOS_UINT32 CmpType,VOS_UINT32 CmpInsId);
ULONG IPC_RPC_Register(ULONG ulModuleID, IPC_RPC_RECEIVE_NOTIFY pfReceiveNotify);
VOS_VOID VOS_T_Delay(VOS_UINT32 ulMillisecond);
VOS_UINT32 VOS_Ev_Read( VOS_UINT32 ulEvents, VOS_UINT32 *pulEvents, VOS_UINT32 ulFlags, VOS_UINT32 ulTimerOut );

ULONG DVM_GetSelfLogicSlotID();
ULONG DVM_GetSelfVcpuID(VOID);



VOID DHCPC_RenewTimeOut(VOID);
VOID DHCPC_RetransTimeOut(VOID);
VOID DHCPC_TimerOut(VOID* pvArg);
ULONG DHCPC_ReceiveLAP2Msg(VOID* pMsgBuf);
VOID DHCPC_ReceiveLap2MbufMsg(PMBUF_S *pstMBuf);
VOID DHCPC_ReceiveServerMsg(UCHAR *pucMsg);
VOID DHCPC_DelNode(ULONG ulTimerIndex, DHCPC_CTRLBLK_NODE* pstCurrNode);
VOID DHCPC_InSertNodeAfterSecs(ULONG ulSeconds,DHCPC_CTRLBLK_NODE* pstCurrNode);
DHCPC_CTRLBLK_NODE* DHCPC_GetDhcpTmpNode(VOID);
VOID DHCPC_FreeDhcpTmpNode(DHCPC_CTRLBLK_NODE* pNode);
ULONG DHCPC_RenewIpAddr( DHCPC_CTRLBLK *pstDhcpcCtlBlk );
ULONG DHCPC_SaveTmpDhcpCtrlBlkPtr(ULONG ulDHCPCtlIdx, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNodePtr);
DHCPC_CTRLBLK_NODE* DHCPC_GetTmpDhcpCtrlBlkPtr(DHCPC_CTRLBLK *pstDhcpCtrBlk);
ULONG DHCPC_ResendMSG(DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode);
LONG DHCPC_OutPut( UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, PMBUF_S* pMBuf, LONG* plSecondReturnCode);
VOID DHCPC_MsgProc_Apply(LAP2_DHCPC_MSG_S *pstReqMsg );
VOID DHCPC_MsgProc_Lease(LAP2_DHCPC_MSG_S *pstReqMsg , ULONG ulDHCPCtlIdx);
VOID DHCPC_MsgProc_Release(LAP2_DHCPC_MSG_S*pstReqMsg);
ULONG  DHCPC_Pkt_ProcDHCP( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen,ULONG ulSrvIpAddr );
ULONG DHCPC_Pkt_ProcDHCPOFFER (DHCP_S *pstDHCPPkt, DHCP_OPTION_S *pstDhcpOption, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode);
ULONG DHCPC_Pkt_ProcDHCPACK (DHCP_S  *pstDHCPPkt, DHCP_OPTION_S *pstDhcpOption, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode);
ULONG DHCPC_Pkt_ProcDHCPNACK (DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode);
ULONG DHCPC_SendMsgToLAP2 ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode, UCHAR MsgType );
ULONG DHCPC_Pkt_Send( UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pItemInfo );
VOID DHCPC_Pkt_EncapDiscovry ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo );
VOID DHCPC_Pkt_EncapRequest ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo);
VOID DHCPC_Pkt_EncapDecline( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo);
VOID DHCPC_Pkt_EncapRelease ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo);
ULONG  DHCPC_Pkt_GetTransId(DHCPC_TEMPCTRLBLK* pItemInfo);
ULONG  DHCPR_RecordAllOption( DHCP_OPTION_S *pstDhcpOpt, DHCP_S *pstDhcp, ULONG ulOptionLen);
ULONG DHCPC_InitGlobalVar(VOID);
ULONG DHCPC_Init(VOID);
ULONG DHCPC_Tmr_Init(VOID);
VOID DHCPC_DBG_strcat(CHAR *dest, CHAR *src);
VOID DHCPC_Dbg_Printf(USHORT usIC_flag,CHAR *pucStr);
VOID DHCPC_Dbg_PacketPrint( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen,USHORT s1);
VOID DHCPC_Dbg_PacketPrintReceive( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen);
VOID DHCPC_Dbg_PacketPrintSend(PMBUF_S  *pMBuf);
VOID DHCPC_ConstructPhyAddr(DHCPC_TEMPCTRLBLK* pstTempCtrlBlk, UCHAR* szChaddr);
VOID DHCPC_OutString(CHAR *fmt,...);
VOID DHCPC_DFT_Init(VOID);
VOID DHCPC_RegisterDFTInfo(VOID);

/* z00175135 DTS2012012003193 全文件pclint 2012-02-09 start */
extern SDB_GSPU_CONTEXT_S *DHCPC_GetOneContextByteidc(ULONG ulTeidc);
extern VOID OutString( CHAR * szString );
extern ULONG PGP_SetTaskRunConfirm(VOID);
extern ULONG DHCPC_ReleaseDhcpCtrlBlock(DHCPC_CTRLBLK *pstDhcpcCtlBlk);
extern ULONG DHCPC_NotifyBKUpdate(ULONG ulTeidc);
extern VOS_UINT32 DHCPC_SendAddrMsgToLAP(VOS_VOID *pMsg, VOS_UINT32 ulMsgLegth, ULONG ulUserIpAddr, VOS_UINT8 ucLapNo);
/* z00175135 DTS2012012003193 全文件pclint 2012-02-09 end   */
/* z00175135 DTS2011120504839 全pclint修改 2012-02-18 start */
extern VOID DHCPC_OmVIfMsgTrc(ULONG  ulDhcpMsgType,
                                    ULONG ulDirection,
                                    UCHAR  *pMsg,
                                    USHORT usMsgLen,
                                    UCHAR  ucIpType,
                                    ULONG  *pulPeerIp);
extern VOID DHCPCv6_OmMsgTrc(UCHAR *pucDhcpv6Msg,DHCPC_CTRLBLK *pstDhcpcContext, UCHAR ucMsgType,ULONG ulMsgLen, UCHAR MsgDirection);
extern ULONG INST_GetSelfInstanceId(VOID);
/* z00175135 DTS2011120504839 全pclint修改 2012-02-18 end   */

/* BEGIN: Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/9 */
extern ULONG DHCPC_CreateDhcpcContext(DHCPC_CTRLBLK **ppstDhcpcContext);
extern ULONG DHCPC_QueryDhcpcContext(UCHAR ucIpType, ULONG ulTeidc, DHCPC_CTRLBLK **ppstDhcpcContext);
extern ULONG DHCPC_AddDhcpcContextToPool(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPC_FreeDhcpcContext(UCHAR ucIpType, ULONG ulTeidc);
extern VOID DHCPC_InsertIdleTable(DHCPC_CTRLBLK *pstDhcpcContext);
extern VOID DHCPC_InsertWaitFreeTable(DHCPC_MANAGEBLK *pstDhcpcContext);
extern VOID DHCPC_FreeDhcpcCtrlBlkMem(VOID);
extern ULONG DHCPC_BlkMemCanbeFree(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPC_DelWholeBlkFromIdleTable(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPC_DelSingleBlkFromTable(DHCPC_CTRLBLK *pstDhcpcContext, DHCPC_CTRLBLK **ppstDhcpcContextHead);
extern DHCPC_CTRLBLK *DHCPC_GetDhcpcBlockfromIdleTable(VOID);
extern ULONG DHCPC_CreateNewDhcpcBlock(VOID);
extern VOID DHCPC_MangeNewBlock(DHCPC_MANAGEBLK *pstDchpcContext);
extern ULONG DHCPC_DelNodeFromWaitFreeTable(DHCPC_MANAGEBLK **pstPreWaitFreeBlk, DHCPC_MANAGEBLK *pstWaitDelBlk);
extern ULONG DHCPC_GetCtlBlkUsedNum(VOID);
extern ULONG DHCPC_GetIdelBlkNum(VOID);
extern ULONG DHCPC_GetManageMemNum(VOID);
extern VOID DHCPC_CheckCtrBlkforIpv4(ULONG ulSelftSlotState, ULONG ulHashValue);
extern VOID DHCPC_CheckCtrBlkforIpv6(ULONG ulSelftSlotState, ULONG ulHashValue);
extern VOID DHCPC_CheckPdpProcForIpv6(SDB_GSPU_CONTEXT_S *pstContext);
extern VOID DHCPC_CheckPdpProcForIpv4(SDB_GSPU_CONTEXT_S *pstContext);
extern ULONG DHCPC_GetTedicByUgwRole(UCHAR ucUgwRole, ULONG ulSgwLeftLocTeidc, ULONG ulS5_Gn_LocTeidc);
extern VOID DHCPC_CheckPdpByCrtBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpcCtlBlk, SDB_GSPU_CONTEXT_S *pstContext);
extern ULONG DHCPC_BkRestoreProcforV6( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC );
extern ULONG DHCPC_BkRestoreProcforV4( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC );
extern ULONG DHCPV6C_TimerRestoreProc(DHCPC_CTRLBLK *pstDhcpcCtlBlk);
extern ULONG DHCPV6C_T1TimerRestoreProc(ULONG ulT1, ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk);
extern ULONG DHCPV6C_T2TimerRestoreProc(ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk);
extern ULONG DHCPV6C_LeaseExpireTimerRestoreProc(ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk);
extern ULONG DHCPC_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent);
extern VOID DHCPC_StateOfBoardChgCallback( CRM_SPUSTATE_CHG_ENUM enEvent, UCHAR ucGroupID, UCHAR ucSlotID, UCHAR ucCpuID, UCHAR ucSGIndex);
/* END:   Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/9 */

/* zhangjinquan 00175135 DHCPv6特性 2012-07-23 start */
ULONG DHCPC_StartTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, ULONG ulTimerInterval, DHCPC_TIMER_CALLBACK pCallBackFun);
ULONG DHCPC_StopTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent);
VOID DHCPC_HourListTimerOut(VOID *pvArg);
VOID DHCPC_SecondListTimerOut(VOID *pvArg);
ULONG DHCPC_getCurTimerSecondPos(VOID);
ULONG DHCPC_getCurTimerHourPos(VOID);
ULONG DHCPC_getCurTimerHourSec(VOID);
/* zhangjinquan 00175135 DHCPv6特性 2012-07-23 end   */

/* DS.UGWV9R10C0.DHCPv6.DHCP.0024支持TID使用情况的维护 ---SEQNUM老化处理 */
extern VOID DHCPV6C_AgeingSeqNum(VOID);

/*m00221573 全文件pclint 2012-10-15 start*/
extern ULONG CRM_GetSelfLogicSlotID(VOID);
extern ULONG DHCPC_SendRtMsg(VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen );
extern ULONG DHCPC_SendURTMsg(VOS_UINT64 ullSrcCsi, VOS_UINT64 ullDstCsi, ULONG ulMsgType,
                      ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen );
extern ULONG DHCPC_MallocDhcpcContext(UCHAR ucIpType, ULONG ulTeidc, DHCPC_CTRLBLK **ppstDhcpcContext);
extern ULONG DHCPC_IsTimNodeExist(UCHAR ucIpType, ULONG ulTeidc);
extern ULONG DHCPV6C_QuryTeidcBySeqNum(USHORT usSeqNum, ULONG *pulTeidc, UCHAR *pucIpAddrType);
extern ULONG DHCPC_InitTimerList(VOID);
extern ULONG DHCPM_RegDhcpServer(VOID);
extern VOID DHCPC_SelfMsgProc(UCHAR *pucMsg);
extern VOID DHCPC_SendSelfPdpCheckMsg(ULONG ulPdpIndex);
extern VOID DHCPV6C_FSM_Register(VOID);
extern VOS_UINT32 DHCPC_AttachLapQueue(VOID);
extern ULONG DHCPC_CommInit1(VOID);
extern VOID DHCPV6C_ProcSDMsg(UCHAR *pucMsg);
extern ULONG DHCPC_CommInit3(VOID);
extern ULONG DHCPC_StartWorkProc(VOID);
extern VOID DHCPV6C_TimerRestoreForSpud(DHCPC_INNER_MSG_S *pstInnerMsg);
extern ULONG DHCPCv6_Get_MsgDirection(UCHAR MsgDirection, UCHAR ucUgwRole);
extern VOID DHCPC_UpdateServerGroupStatusNormal(ULONG ulSvrGrpIndex, UCHAR ucCurrentSrv);
extern ULONG DHCPV6C_QueryDhcpBlockBySeq(USHORT usSeqNo, DHCPC_CTRLBLK **ppstDhcpcContext);
extern ULONG DHCPC_SendMsgToLAP2ByContext(DHCPC_CTRLBLK *pstDhcpcContext, UCHAR MsgType);
extern VOID DHCPC_EmsReportAndCleanCause(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPC_NotifyLapFail(DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPC_RegLogCnt(VOID);
/*m00221573 全文件pclint 2012-10-15 start*/
#endif
