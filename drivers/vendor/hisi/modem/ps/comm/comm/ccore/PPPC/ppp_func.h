/************************************************************************
 *                                                                      *
 *                             ppp_func.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/27                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP模块私有函数说明                             *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件包含了PPP模块所有私有函数的申明                            *
 *                                                                      *
 ************************************************************************/

#ifndef      _PPP_FUNC_H_
#define      _PPP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif    /* end of __cplusplus */

/****************外部函数声明******************/

/********** 初始化函数 ************/
VOS_UINT32 PPP_CreateCB(VOS_UINT32, PPP_LUPPARA_S*) ;
VOS_UINT32 PPP_DeleteCB(PPPINFO_S *, PS_BOOL_ENUM_UINT8) ;
VOS_UINT32 PPP_InitCB(PPPINFO_S *) ;
VOS_UINT32 PPP_InitConfigInfo(PPPINFO_S *) ;
VOS_UINT32 PPP_ClearCB(PPPINFO_S *) ;
VOID PPP_ClearConfigInfo(PPPINFO_S *) ;
VOS_UINT32 Ppp_UsmIoCtl(VOS_UINT32 ulRPIndex, VOS_UINT32 ulCmd, CHAR *pPara);
VOS_VOID PPPC_MsgTimerProc( struct MsgCB * pMsg );
VOS_VOID FWD_PppClearFreelist(VOS_UINT8 ucPppId);

VOID PPPGetPPPConfig(VOID);
#ifdef    __PRODUCT_TYPE_PDSN80
VOID PPPGetCompressConfig(VOID);
#endif
VOID PPP_L2tpUserNumAlarm(VOS_UINT32 ulOldNum, VOS_UINT32 ulNewNum);

extern VOID PPP_VSNCP_SetRenegoFlagForAllPDN(PPPINFO_S *pstPppInfo);
extern VOID A11_ReqNumSubProc(PPPINFO_S *pstPppInfo);
extern VOID PPP_ClearCB_IPCP(PPPIPCPINFO_S *pstIpcpInfo);
extern VOID PPP_ClearCB_IPV6CP(PPPIPV6CPINFO_S *pstPppIpv6cpInfo);
extern VOS_UINT32 PPP_CompSelectDmpuDpe(UCHAR *pucDmpuId, UCHAR* pucDpeId);
extern VOS_VOID IPV6_PerfStatistic(VOS_UINT32 ulMsgType);




extern UCHAR PPP_IPCP_IsSip(UCHAR *pPacket, VOS_UINT32 *pulLen);
extern UCHAR PPP_IPV6CP_IsSip(UCHAR *pPacket, VOS_UINT32 *pulLen);

extern VOS_UINT32 PPP_CheckCcpLimit(VOID );
extern VOID PPP_Ipv4cp_Proc( PPPINFO_S *pstPppInfo );
extern VOID PPP_Ipv6cp_Proc(PPPINFO_S *pstPppInfo);
extern VOS_UINT32 PPP_GetConfigUserName
(
    VOS_UINT8                          *pucUserName,
    VOS_UINT32                          ulPppId
);

extern VOS_UINT32 PPP_GetConfigPassWord
(
    VOS_UINT8                          *pucPassWd
);
extern VOS_VOID *PPP_GetActPppHeadNode(VOS_VOID);
extern VOS_VOID PPPC_AccessAuthSuccProc(VOS_VOID);
extern PS_BOOL_ENUM_UINT8 PPPC_IsDoingAccessAuth(VOS_UINT8 ucPppId);

/********** 初始化函数 ************/

VOS_UINT32 PPP_OmInitial(VOID);
VOID  PPP_OmMsgTrc(VOS_UINT32 ulIndex, VOS_UINT16 usProtocol, UCHAR* pMsg, VOS_UINT32 ulLen, UCHAR ucflag, VOS_UINT32 ulLnsIp, IMSI_S *pstImsi,  UCHAR ucEhrpdMode);

/********** 同异步转换 ************/
PMBUF_S *PPP_SynToAsy(PMBUF_S *pstSynMBuf, VOS_UINT32 ulAsynAccm) ;
VOS_UINT32 PPP_AsyToSyn
(
    VOS_UINT8                           ucAsynByte
);
VOS_UINT32 PPP_UlDataSynToAsy
(
    VOS_UINT8                          *pucDstData,
    VOS_UINT16                          usDstDataLen,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT16                          usSrcDataLen,
    VOS_UINT32                          ulAccmValue
);

VOS_VOID FWD_PppRebuildIncompleteSliceStatInit();

/********** 同异步转换 ************/

/****************** 内核 *******************/
/* 与各部分接口函数 */
VOID PPP_Core_ReceiveEventFromProtocol (PPPINFO_S *, VOS_UINT32 , CHAR *) ;
VOID PPP_Core_ReceiveEventFromShell(PPPINFO_S *, VOS_UINT32 , CHAR *) ;
VOID PPP_Core_ReceivePacketFromShell(PPPINFO_S *, UCHAR *, UCHAR *, VOS_UINT32 ) ;
VOID PPP_Core_RejectProtocol(VOID *, VOS_UINT16 ) ;
VOID PPP_Core_ReceiveUnknownProtocol (PPPINFO_S *, UCHAR *, UCHAR *, VOS_UINT32, VOS_UINT16, UCHAR) ;
PPPFSM_S *PPP_Core_GetFsmByProtocol(VOID *, VOS_UINT16 ) ;
VOS_UINT32 PPP_SendUserInfo(PPPINFO_S* pstPppInfo, VOS_UINT32 ulType);

/* 内部处理函数 */
VOID PPP_Core_Reset(VOID *) ;
VOS_UINT32 PPP_Core_GetProtocol(PPPINFO_S *, UCHAR *, VOS_UINT16 *) ;
VOID PPP_Core_NotifyUperLcpDown(PPPINFO_S *) ;
VOID PPP_Core_NotifyNcpDown(PPPINFO_S *pstPppInfo);
VOID PPP_Core_AuthUp(PPPINFO_S *pstPppInfo, UCHAR* pMsg) ;
LONG PPP_Core_NCPExist(VOS_UINT32  ulOriginIfindex,
                       VOS_UINT16 usProtocol,
                       VOS_UINT32  ulIfIndex);
extern VOID ImsiToString( A11_IMSI_S stImsi ,UCHAR*szTemp);

/* 阶段转换函数 */
VOID PPP_Core_AuthenticatePhase(PPPINFO_S *) ;
VOID PPP_Core_DeadPhase(PPPINFO_S *) ;
VOID PPP_Core_EstablishPhase(PPPINFO_S *) ;
VOID PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo,UCHAR* pMsg) ;
VOID _PPP_Core_NetworkPhase(PPPINFO_S *) ;
VOID PPP_Core_TerminatePhase(PPPINFO_S *) ;
VOID ppp_Core_CcpInitiativeNego(PPPINFO_S *pstPppInfo);

/* 其他 */
VOS_UINT32 PPP_GetMagicNumber(VOID) ;
VOS_UINT32 PPP_SlaveBoardDiscardMsMsg(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR ucSlaveReleaseFlg);
VOID PPP_CheckIsLcpTerminateMsg(PPPINFO_S *pstPppInfo, UCHAR *pucPacket, VOS_UINT32 ulLen, UCHAR *pucLcpTerminateFlg);
VOS_VOID ShowCode(VOS_UINT8 *pucMsg, VOS_UINT16 usLen);
PS_BOOL_ENUM_UINT8 PPP_VSNCP_IsPDNOpened(UCHAR ucPDNId);

/* 与L2TP接口函数 */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)
VOID PPP_Core_L2tpPreNeg(PPPINFO_S *, CHAR *) ;
VOID PPP_Core_L2tpNeg(PPPINFO_S *pstPppInfo, CHAR *pOptionalPara);
LONG PPP_Core_L2tpPreNegLcp(UCHAR *, VOS_UINT32 , UCHAR *, UCHAR *) ;
LONG PPP_Core_L2tpPreNegAuth(PPPINFO_S *, UCHAR *) ;
VOS_UINT32 PPP_Shell_NotifyL2tpUp(VOS_UINT32 ulIndex, L2TP_PPPPARA_S *pstPPPPara );
VOID PPP_L2tpUpPreProc(L2TP_PPPPARA_S * pstPPPPara, SDB_PDSN_RP_CONTEXT_S *pstContext,VOS_UINT32 ulIndex);
VOS_UINT32 PPP_SendMsgToL2tp( UCHAR ucMsgCode, UCHAR* pucMsg, VOS_UINT32 ulMsgLen );

#endif

extern VOS_UINT32 PDN_PDNGlobalIndexToPDNScIndex(VOS_UINT32 ulPDNGlobalIndex);


/****************** 内核 *******************/

/***************** 状态机 ******************/
/* 对外接口 */
VOS_VOID PPP_FSM_ReceiveEvent (PPPFSM_S* pstFsm, VOS_UINT32 ulCmd, CHAR *pPara) ;
VOID PPP_FSM_ReceivePacket (PPPFSM_S* pstFsm, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen,VOS_UINT32 ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
VOID PPP_FSM_Init(PPPFSM_S *pstFsm) ;

/* 外部事件处理 */
VOID PPP_FSM_Close(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_LowerDown(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_LowerUp(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_Open(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_TimeOut(VOID *pstFsm) ;
VOID PPP_FSM_VSTimeOut( VOID * );

/* 其他事件处理 */
VOID PPP_FSM_RXJ_Plus(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_RXJ_Sub(PPPFSM_S *pstFsm) ;

/* 报文处理 */
VOID PPP_FSM_ReceiveCodeRej(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_ReceiveConfAck(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_ReceiveConfNakRej(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR ucCode, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_ReceiveConfReq(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_ReceiveProtocolRej(PPPFSM_S *pstFsm, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_ReceiveTermAck(PPPFSM_S *pstFsm, UCHAR ucId) ;
VOID PPP_FSM_ReceiveTermReq(PPPFSM_S *pstFsm, UCHAR ucId) ;
VOID PPP_FSM_ReceiveUnknownCode(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_ReceiveVendorSpecific(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR * pHead,UCHAR * pPacket,VOS_UINT32 ulLen);

/* 报文发送 */
VOID PPP_FSM_SendConfigReq(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_SendPacket(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulLen) ;
VOID PPP_FSM_SendPacketByCode(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId) ;
VOID PPP_FSM_SendVendorSpecific(PPPFSM_S *pstFsm , UCHAR ucid,VOS_UINT32 ulMagic, UCHAR ucKind);
/***************** 状态机 ******************/


/****************** 外壳 *******************/
/* 与内核接口函数 */
VOS_UINT32 PPP_Shell_ReceiveEventFromCore(PPPINFO_S *, VOS_UINT32 , CHAR *) ;
VOS_UINT32 PPP_Shell_GetPacketFromCore(CHAR *, UCHAR *, UCHAR *, VOS_UINT32 , VOS_UINT16 ) ;
VOS_UINT32 PPP_Shell_ReceiveNegoPacket(PMBUF_S *pMbuf, VOS_UINT8 ucPppId) ;
VOS_UINT32 PPP_Shell_ReceiveStacPacket(PMBUF_S *pMbuf) ;
VOID PPP_Shell_ReceiveCompressPacket(PMBUF_S * pMbuf);
VOID PPP_Shell_ReceiveDecompressPacket(PMBUF_S * pMbuf);
VOS_UINT32 PPP_Shell_SendDecompressPacket(PMBUF_S * pMbuf, VOS_UINT16 usProtocol, VOS_UINT32 ulIndex);
VOS_VOID PPP_CCP_Timeout(VOS_UINT32 ulPppId);

/* 与AAA接口 */
VOID PPP_Shell_ReceiveAAAResult(AAA_AUTHRSP_S *) ;

VOID PPP_Shell_GetPeerAddrTimeOut(VOID *pIfIndex);


/* 与上、下层的接口函数 */
VOS_UINT32 PPP_Shell_ISLIoCtl(VOS_UINT32 ulRPIndex, VOS_UINT32 ulCmd, char *pPara);/* 提供给底层的控制函数接口 */


/* 内部处理函数 */
VOS_UINT32 PPP_Shell_SendPacketToISL(PPPINFO_S *, PMBUF_S *, VOS_UINT16 ) ;

/* 下发协商信息函数 */
VOID PPP_SendIpcpInfoProc(PPPINFO_S* pstPppInfo);


/***************** build run *******************/

/***************** Debug函数 ******************/
VOID PPP_Debug_FsmPacket(PPPINFO_S* , UCHAR * , VOS_UINT32 , VOS_UINT16 , UCHAR ) ;
VOID PPP_Debug_FsmEvent(PPPFSM_S*, VOS_UINT32 ) ;
VOID PPP_Debug_FsmIllegalEvent(PPPFSM_S* , VOS_UINT32 ) ;
VOID PPP_Debug_Error(PPPFSM_S *, VOS_UINT16 , CHAR *) ;
VOID PPP_Debug_FsmStateChange(PPPFSM_S *, UCHAR ) ;
VOID PPP_Debug_CoreEvent(PPPINFO_S *pstPppInfo, VOS_UINT16 usLogLevel,CHAR *pString) ;

CHAR *PPP_Debug_GetInterfaceName(PPPINFO_S *) ;
CHAR *PPP_Debug_GetTypeName(VOS_UINT16 , UCHAR ) ;
CHAR *PPP_Debug_GetProtocolName(VOS_UINT16 ) ;
CHAR *PPP_Debug_GetValueStr(UCHAR * , UCHAR ) ;
CHAR *PPP_Debug_GetProtoState(PPPINFO_S *, VOS_UINT16) ;
CHAR *PPP_Debug_GetCode(UCHAR ucCode) ;
CHAR *PPP_Debug_GetLcpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetIpcpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetCcpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetOsicpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetString(UCHAR *, UCHAR ) ;

VOID PPP_Debug_SetAllOptions( PPPDEBUGINFO_S *pstPppDebugInfo, UCHAR ucSet );
VOID PPP_Debug_SetOneOption( PPPDEBUGINFO_S *pstPppDebugInfo,
                             UCHAR ucSet,
                             VOS_UINT32 ulType,
                             VOS_UINT16 usProtocol) ;
UCHAR PPP_Debug_GetOption( PPPDEBUGINFO_S *pstPppDebugInfo,
                           VOS_UINT32 ulType,
                           VOS_UINT16 usProtocol) ;
/***************** Debug函数 ******************/

/***************** Mib 函数 ******************/
/*
#if(VRP_MODULE_SNMP == VRP_YES )
*/
VOS_UINT32 PPP_MIB_LcpStatus( VOID * pMsgRcv, VOID **ppMsgSnd );
VOS_UINT32 PPP_MIB_LcpConfig( VOID * pMsgRcv, VOID **ppMsgSnd );
VOS_UINT32 PPP_MIB_IpcpStatus( VOID * pMsgRcv, VOID **ppMsgSnd );
VOS_UINT32 PPP_MIB_IpcpConfig( VOID * pMsgRcv, VOID **ppMsgSnd );
VOS_UINT32 PPP_MIB_Unsupport( VOID * pMsgRcv, VOID **ppMsgSnd );


/***************** Mib 函数 ******************/
VOS_UINT32 PPP_NodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPDNIndex, UCHAR ucNodeType);
VOS_UINT32 PPP_NodeDelete(VOS_UINT32 ulRpIndex);
VOID PPP_NegoListProc(VOID* pPara);
VOS_UINT32 PPP_PDNNodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPDNIndex, UCHAR ucNodeType);
VOS_UINT32 PPP_PDNNodeDelete(VOS_UINT32 ulPDNIndex);




extern VOS_VOID PPP_SubBoardDown(VOS_VOID);

extern VOS_UINT32 PPP_CheckVjLimit(VOID);


extern VOS_UINT32 PPP_CheckStacLimit(VOID );


extern VOS_VOID PPP_CompUserClear( VOID );
extern VOID PPP_CompUserNumAdd(PPPINFO_S *pstPppInfo, VOS_UINT32 ulCompType);
extern VOID PPP_CompUserNumDel(PPPINFO_S *pstPppInfo, VOS_UINT32 ulCompType);

extern VOS_VOID PPP_BkpCompUserSmooth( VOID );

extern LONG PPP_CompBinSelectDpe(LONG llow, LONG lhigh, VOS_UINT32 ulSearchData);

//extern VOS_UINT32 PPP_Shell_GetVpnIdByVpnName(UCHAR *pucVpnName, VOS_UINT32 *pulVpnId);

VOID PPP_Core_IpcpV4FinProc( PPPINFO_S *pstPppInfo );
VOID PPP_Core_IpcpV6FinProc( PPPINFO_S *pstPppInfo );
VOS_UINT32 PPP_GetUserTypeByIpv4cpReq(PPPINFO_S *pstPppInfo, UCHAR* pPacket,VOS_UINT32 ulLen, VOS_UINT32* pulMsgType);
VOS_UINT32 PPP_CopyIpv4cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulMsgLen);
VOS_UINT32 PPP_CopyIpv6cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, VOS_UINT32 ulMsgLen);
VOID PPP_L2tpMsgProc(VOID *pstMsg, VOS_UINT32 ulMsgCode);
extern VOS_UINT32 Diam_AuthPPPRenegoRelCB(VOS_UINT32 ulRPIndex);


extern VOID              SRPppCfgCompress( VOS_UINT32 argc, CHAR * argv []   );
/* extern VOID              SRPppShowDebug( VOS_UINT32 argc, CHAR * argv []   ); */
/* extern VOID              SRPppShowCBDetailInfo( VOS_UINT32 argc, CHAR * argv []   ); */
/* extern VOID              SRPppShowCBInfo( VOS_UINT32 argc, CHAR * argv []   ); */
/* extern VOID              SRPppShowInfo( VOS_UINT32 argc, CHAR * argv []   ); */
extern VOID              StartPPPRego( VOS_UINT32 argc, CHAR * argv []   );
extern VOID              PPP_PrintPerfVar( VOS_UINT32 argc, CHAR * argv [] );
extern VOID              PPP_SetStubValue(VOS_UINT32 argc, CHAR *argv[]);

extern VOID              PPP_ShowEcho( VOS_UINT32 argc, CHAR * argv [] );
extern VOID              PPP_SetDebugInfo( VOS_UINT32 argc, CHAR * argv [] );



extern VOS_UINT32 PPP_VSNCP_FSM_DelRetransmitTimer(PPPFSM_S *pstFsm);
extern VOID PPP_VSNCP_FSM_SetRetransmitTimer(PPPFSM_S *pstFsm);

extern VOID PPP_EAP_NotifyDiamAuthReleaseForRenego(PPPINFO_S *pstPppInfo);


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_FUNC_H_ */





