/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmExt.h
  Description : 函数声明
  History     :
      1.  张志勇      2003.12.11   新版作成
      2.  张志勇 2005.01.04   移植修改
      3.  L47619 2007.10.27   A32D13038
*******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


extern VOS_UINT8                  g_TiMapToNsapi[256];                              /* TI和NSAPI的映射关系                      */
extern VOS_UINT8                  g_CrMapToNsapi[256];                              /* CR和NSAPI的映射关系                      */
extern VOS_UINT8                  g_ucTiExt;                                        /* 记录ti是否有扩展位                       */
extern SM_ENTITY_STRU             g_SmEntity;
extern SM_PDP_ADDR_AND_APN_STRU   g_SmPdpAddrApn;
extern VOS_UINT8                  g_aucSapi[SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET][2];
extern GMMSM_SGSN_REL_VER_ENUM    g_SmSgsnVersion;

/* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
extern VOS_UINT8                  g_ucSmTimerFiveExpireFlag;
/* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

/* SmRcvTaf.c */
extern VOS_VOID NAS_SM_ProcTafPdpActiveReq(SMREG_PDP_ACTIVATE_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpActiveRej(SMREG_PDP_ACTIVATE_REJ_RSP_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpDeActiveReq(SMREG_PDP_DEACTIVATE_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpModifyRsp(SMREG_PDP_MODIFY_RSP_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpModifyReq(SMREG_PDP_MODIFY_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpActiveSecReq(SMREG_PDP_ACTIVATE_SEC_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpActiveSecReq_S00(SMREG_PDP_ACTIVATE_SEC_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpCnxtActReq_S00(SMREG_PDP_ACTIVATE_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpCnxtActReq_S05(SMREG_PDP_ACTIVATE_REQ_STRU*);
extern VOS_VOID NAS_SM_ProcTafPdpModifyRejRsp(SMREG_PDP_MODIFY_REJ_RSP_STRU*);

extern VOS_VOID NAS_SM_RcvTafPdpCnxtActReq(SMREG_PDP_ACTIVATE_REQ_STRU*);
extern VOS_VOID NAS_SM_RcvTafPdpCnxtActRejRsp(SMREG_PDP_ACTIVATE_REJ_RSP_STRU*);
extern VOS_VOID NAS_SM_RcvTafPdpCntxtModifyReq(SMREG_PDP_MODIFY_REQ_STRU*);
extern VOS_VOID NAS_SM_RcvTafPdpCnxtDeActReq(SMREG_PDP_DEACTIVATE_REQ_STRU*);
extern VOS_VOID NAS_SM_RcvTafPdpCnxtActSecReq(SMREG_PDP_ACTIVATE_SEC_REQ_STRU*);
extern VOS_VOID NAS_SM_RcvTafPdpModifyRsp(SMREG_PDP_MODIFY_RSP_STRU*);
extern VOS_VOID NAS_SM_RcvTafPdpModifyRejRsp(SMREG_PDP_MODIFY_REJ_RSP_STRU*);

extern VOS_UINT8 SM_PdpAddrApnComp(SMREG_PDP_ACTIVATE_REQ_STRU*);

/* send.c */
extern VOS_VOID SM_ReportM2NOtaMsg(NAS_MSG_STRU *pNasMsg);
extern VOS_VOID SM_ComGetTI(VOS_UINT8,VOS_UINT8**,VOS_UINT32*);
extern VOS_VOID SM_SndPdpActReqMsg(SMREG_PDP_ACTIVATE_REQ_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndReqPdpActRejMsg(SMREG_PDP_ACTIVATE_REJ_RSP_STRU *,VOS_UINT8);
extern VOS_VOID SM_SndPdpDeActReqMsg(SMREG_PDP_DEACTIVATE_REQ_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndPdpModAccMsg(SMREG_PDP_MODIFY_RSP_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndPdpModReqMsg(SMREG_PDP_MODIFY_REQ_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndPdpActSecReqMsg(SMREG_PDP_ACTIVATE_SEC_REQ_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndPdpDeActAccMsg(VOS_UINT8);
extern VOS_VOID NAS_SM_SndGmmEstablishReq(VOS_VOID);
extern VOS_VOID SM_SndTafSmPdpActivateRej(VOS_UINT8,SM_TAF_CAUSE_ENUM_UINT16,SM_OCT_VARY_STRU*);
extern VOS_VOID SM_SndTafSmPdpActivateInd(SM_NW_MSG_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpActivateCnf(SM_NW_MSG_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpDeActCnf(VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpDeActInd(VOS_UINT8,SM_TAF_CAUSE_ENUM_UINT16,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpModifyInd(SM_NW_MSG_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpModifyCnf(SM_NW_MSG_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_ENUM_UINT16,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpActSecCnf(SM_NW_MSG_STRU*,VOS_UINT8);
extern VOS_VOID SM_SndTafSmPdpActSecRej(VOS_UINT8,SM_TAF_CAUSE_ENUM_UINT16);
extern VOS_VOID SM_SndRabmSmActivateInd(VOS_UINT8    ucCntxtIndex,
                                    VOS_UINT8    ucActMsgType );
extern VOS_VOID SM_SndRabmSmModifyInd(VOS_UINT8);
extern VOS_VOID SM_SndRabmSmDeactivateInd(VOS_UINT8,VOS_UINT8*);

extern VOS_VOID SM_SndNwStatusMsg(VOS_UINT8,VOS_UINT8);
extern VOS_VOID SM_SndStatusMsg( VOS_UINT8 ucTi, VOS_UINT8  ucSmCause );

extern VOS_UINT8 SM_GetMostHighPri(VOS_VOID);
extern VOS_VOID SM_FillMsgData(VOS_VOID *pMsgContent,VOS_VOID *pData,VOS_UINT32 ulLen);
extern VOS_VOID SM_SndTafMsg(VOS_UINT8 *, VOS_UINT8, VOS_UINT32, VOS_UINT8, VOS_UINT8 );
extern VOS_VOID NAS_SM_SndGmmPdpDeactivatedInd(VOS_VOID);
extern VOS_VOID NAS_SM_SndPdpModRejMsg(SMREG_PDP_MODIFY_REJ_RSP_STRU *pstMsgIE, VOS_UINT8 ucSMIndex);

extern VOS_VOID NAS_SM_SndGmmPdpModifyInd(VOS_UINT8 ucNsapi);

/* main.c */
extern VOS_VOID SM_Init(VOS_VOID);
extern VOS_VOID NAS_SM_RcvTafMsg(MSG_HEADER_STRU*);
extern VOS_VOID SM_GmmMsgDistr(VOS_VOID*);
extern VOS_VOID SM_RabmMsgDistr(VOS_VOID*);
extern VOS_VOID SM_RcvTimerMsgDistr(VOS_UINT32);
extern VOS_VOID SM_T3380Expire(VOS_UINT8);
extern VOS_VOID SM_T3381Expire(VOS_UINT8);
extern VOS_VOID SM_T3390Expire(VOS_UINT8);
extern VOS_VOID SM_RegisterProtectTimerExpire(VOS_UINT8);
extern VOS_VOID SM_NwActProtectTimerExpire(VOS_UINT8);
extern VOS_VOID SM_NwModifyProtectTimerExpire(VOS_UINT8);
extern VOS_VOID SM_TimerStart(VOS_UINT8,VOS_UINT32,VOS_UINT8);
extern VOS_VOID SM_TimerStop( VOS_UINT8  ucTimerId );
extern VOS_VOID SM_RcvStatusMsg( GMMSM_DATA_IND_STRU *);
/* Modified by wx270776 for OM融合, 2015-7-24, begin */
extern VOS_VOID Sm_FillQosInfo(NAS_QOS_IND_STRUCT *pMsg);
/* Modified by wx270776 for OM融合, 2015-7-24, end */
extern VOS_VOID Sm_OmQuery(VOS_VOID *pMsg);


extern VOS_UINT8 SM_MemCmp(VOS_UINT8 *p1, VOS_UINT8 *p2, VOS_UINT32 ulLength);

extern VOS_VOID SM_AgentMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID SM_ReportN2MOtaMsg(VOS_UINT8 ucMsgType, NAS_MSG_STRU *pNasMsg);

extern VOS_UINT16 NAS_SM_CalcMaxSduSize(VOS_UINT8 *pucQos, VOS_UINT8 ucCurrOctet);
extern VOS_UINT16 NAS_SM_CalcTransDelay(VOS_UINT8 *pucQos, VOS_UINT8 ucCurrOctet);
extern VOS_UINT32 NAS_SM_CalcQosBitRate(VOS_UINT8 *pucQos, VOS_UINT8 ucCurrOctetIndex, VOS_UINT8 ucExtOctetIndex, VOS_UINT8 ucBitRateType, VOS_UINT32 ulQosLen);
/* Modified by wx270776 for OM融合, 2015-7-24, begin */
extern VOS_VOID   NAS_SM_FillQos(NAS_QOS_IND_STRUCT *pMsg, VOS_UINT8 *pucQos, VOS_UINT32 ulQosLen);
/* Modified by wx270776 for OM融合, 2015-7-24, end */
extern VOS_UINT32 NAS_SM_FindCurrPdpId(VOS_UINT8 *pucNSAPI);

/* SmRcvRabm.c */
extern VOS_VOID SM_RcvRabmDeActReq( RABMSM_DEACTIVATE_REQ_STRU *);

/* SmRcvGmm.c */
extern VOS_UINT8 SM_ComSaveTICheck(VOS_UINT8 ,VOS_UINT8**,VOS_UINT32*,SM_NW_MSG_STRU*);
extern VOS_UINT32 SM_ComOptionalCheck(VOS_UINT8*, VOS_UINT32 ,VOS_UINT32*, SM_NW_MSG_STRU *);
extern SM_NW_MSG_STRU* SM_ComActPdpCntxtAccCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComActPdpCntxtRejCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComReqPdpCntxtActMsgCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComModifyPdpCntxtAccCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComModifyPdpCntxtReqCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComActSecPdpCntxtAccCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComActSecPdpCntxtRejCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComModifyPdpCntxtRejCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComDeActPdpCntxtReqCheck(VOS_UINT8*,VOS_UINT32);
extern SM_NW_MSG_STRU* SM_ComDeActPdpCntxtAccCheck(VOS_UINT8*,VOS_UINT32);
extern VOS_VOID SM_RcvGmmSmEstabishCnf(GMMSM_ESTABLISH_CNF_STRU*);
extern VOS_VOID SM_RcvGmmSmStatusInd(GMMSM_STATUS_IND_STRU*);
extern VOS_VOID SM_RcvGmmSmServiceRej(GMMSM_SERVICE_REJ_STRU*);
extern VOS_VOID SM_RcvGmmSysInfoInd(GMMSM_SYS_INFO_IND_STRU *);
extern VOS_VOID SM_RcvGmmSmPdpStatusInd(GMMSM_PDP_STATUS_IND_STRU*);
extern VOS_VOID SM_RcvGmmRelInd(GMMSM_REL_IND_STRU *);
extern VOS_VOID SM_RcvNwReqPdpCntxtActMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwActPdpCntxtAccMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwActPdpCntxtRejMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwActSecPdpCntxtAccMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwActSecPdpCntxtRejMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwModifyPdpCntxtReqMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwModifyPdpCntxtAccMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwModifyPdpCntxtRejMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwDeActPdpCntxtReqMsg(SM_NW_MSG_STRU*);
extern VOS_VOID SM_RcvNwDeActPdpCntxtAccMsg(SM_NW_MSG_STRU*);
extern VOS_UINT8 SM_ComFindNullAddrApn(VOS_VOID);
extern VOS_VOID SM_ComClearPdpCntxt(VOS_UINT8);
extern VOS_VOID SM_ComClearPdpAddrApn(VOS_UINT8);
extern VOS_VOID SM_ComDelNsapiFromAddr(VOS_UINT8,VOS_UINT8);
extern VOS_VOID SM_RcvNwReqPdpCnxtActMsg_S00(SM_NW_MSG_STRU*,VOS_UINT8);
extern VOS_UINT8 SM_RcvNwReqPdpCnxtActMsg_S01(SM_NW_MSG_STRU*,VOS_UINT8,VOS_UINT8);
extern VOS_VOID SM_RcvNwReqPdpCnxtActMsg_S02(SM_NW_MSG_STRU*,VOS_UINT8);

extern VOS_UINT32 NAS_SM_ComMsgCheck(VOS_UINT8,VOS_UINT32,VOS_UINT8*,SM_NW_MSG_STRU**);
extern VOS_UINT32 NAS_SM_ValidNasMsg(GMMSM_DATA_IND_STRU*,VOS_UINT8*,VOS_UINT8*);
extern VOS_VOID NAS_SM_RcvGmmSmDataInd(GMMSM_DATA_IND_STRU*);
extern VOS_BOOL NAS_SM_ComparePdpAddr(SM_MSG_IE_COMMON_STRU*, SM_PDP_ADDR_STRU*);

/* SmAgent.c */
extern VOS_VOID SM_RcvAgentSmInquire( VOS_VOID    *pRcvMsg );
extern VOS_VOID SM_RcvAgentSmPdpnumInquire( VOS_VOID );
extern VOS_VOID SM_SndAgentSmAgentInfo( VOS_UINT8 ucNsapi );
extern VOS_VOID SM_SndAgentSmPdpnumInd( VOS_VOID );
extern VOS_VOID SM_SndAgentStatusInd( VOS_UINT8 ucTi, VOS_UINT8 ucSmCause, VOS_UINT8 ucDirection );

/* 外部API接口 */
extern VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId);
extern VOS_VOID Aps_GetPdpContextInfo(VOS_UINT8 ucNsapi, NAS_PDP_CONTEXT_STRU *pstPdpCntxt);


VOS_VOID NAS_SM_SndGmmAbortReq(VOS_VOID);
VOS_VOID NAS_SM_RcvTafPdpAbortReq(
    SMREG_PDP_ABORT_REQ_STRU          *pstPdpAbortReq
);
VOS_VOID NAS_SM_RcvTafPdpLocalDeactivateReq(
    SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU    *pstPdpLocalDeactivateReq
);

VOS_VOID NAS_SM_RcvGmmSigConnInd(
    GMMSM_SIG_CONN_IND_STRU            *pstSigConnInd
);

SM_TAF_CAUSE_ENUM_UINT16 NAS_SM_MapGmmCause(
    GMM_SM_CAUSE_ENUM_UINT16            enGmmCause
);

VOS_UINT8 * NAS_SM_GetTiMapToNsapi(VOS_VOID);
VOS_UINT8 * NAS_SM_GetCrMapToNsapi(VOS_VOID);
VOS_UINT8 NAS_SM_GetTiExt(VOS_VOID);
VOS_VOID NAS_SM_SetTiExt(VOS_UINT8 ucTiExt);
SM_ENTITY_STRU * NAS_SM_GetSmEntity(VOS_VOID);
SM_PDP_ADDR_AND_APN_STRU * NAS_SM_GetSmPdpAddrApn(VOS_VOID);
VOS_UINT8 * NAS_SM_GetSapi(VOS_UINT8 ucIndex);
GMMSM_SGSN_REL_VER_ENUM NAS_SM_GetSmSgsnVersion(VOS_VOID);
VOS_VOID NAS_SM_SetSmSgsnVersion(GMMSM_SGSN_REL_VER_ENUM enSmSgsnVersion);
VOS_VOID NAS_SM_SndGmmPdpStatusInd(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_SM_ProcGmmLteMoDetachInd(VOS_VOID);
#endif

VOS_UINT32 NAS_SM_IsPdpCntxtValid(NAS_SM_PDP_CONTEXT_INFO_STRU *pstPdpCntxt);
VOS_VOID NAS_SM_SndPdpCntxtHoldMsg(NAS_SM_PDP_CONTEXT_INFO_STRU *pstPdpCntxt);

VOS_VOID NAS_SM_BeginSession(VOS_VOID);
VOS_VOID NAS_SM_EndSession(VOS_VOID);
VOS_VOID NAS_SM_SndGmmBeginSessionNotify(GMMSM_SESSION_TYPE_ENUM_UINT8 enSessionType);
VOS_VOID NAS_SM_SndGmmEndSessionNotify(GMMSM_SESSION_TYPE_ENUM_UINT8 enSessionType);

SM_TAF_CAUSE_ENUM_UINT16 NAS_SM_MapSmNWCause(VOS_UINT8 ucSmCause);

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
