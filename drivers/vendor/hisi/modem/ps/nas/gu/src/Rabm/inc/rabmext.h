/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmExt.h
  Description : 函数声明
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.  l47619   2005.10.21   Modify for V200R001
*******************************************************************************/
#ifndef _RABM_EXT_H_
#define _RABM_EXT_H_


#include "NasRlcInterface.h"
#include "NasPdcpInterface.h"
#include "Rabm2GStru.h"
#include "CdsRabmInterface.h"
#include "QosFcCommon.h"
#include "AtRabmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

/* common */
extern VOS_VOID RABM_SaveData( RABM_DATA_SAVE_STRU    *pSaveDataPtr, VOS_VOID *pMsg, VOS_UINT8 ucMsgType );
extern VOS_VOID RABM_ComSaveRabPara( RRRABM_RAB_IND_STRU *pMsg );
extern VOS_VOID RABM_ComRlsRabReource( RRRABM_RAB_IND_STRU *pMsg );
extern VOS_VOID RABM_RelSaveData( RABM_DATA_SAVE_STRU *pLink, VOS_UINT8 ucMsgType);

/* main */
extern VOS_VOID Rabm_3GTaskEntry( struct MsgCB* pMsg );
extern VOS_VOID Rabm_TimerProcess( REL_TIMER_MSG *pTimer );
extern VOS_VOID Rabm_Init( VOS_VOID );
extern VOS_VOID RABM_TimerStart(VOS_UINT8 ucTimerId, VOS_UINT32 ulTimerLen);
extern VOS_VOID RABM_TimerStop(VOS_UINT8);

/* Rcv msg */
extern VOS_VOID RABM_RcvGmmReestCnf( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvSmActInd( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvSmDeactInd( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvSmModInd( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvRrcStatusInd( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvPsTcDataInd( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvRrcRabInd( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvRrcRelAllReq(VOS_VOID);
extern VOS_VOID RABM_RcvPsDataReq( VOS_VOID *pMsg );
extern VOS_VOID RABM_RcvCsDataReq( VOS_VOID *pMsg );
extern VOS_VOID RABM_SaveDataProcess( VOS_UINT8 ucEntId,VOS_UINT8 ucUlFlg );
extern VOS_VOID RABM_RcvRlcDataInd( RLC_RABM_CS_DATA_IND_STRU  *pRcvData );

/* Snd msg */
extern VOS_VOID RABM_SndRabReestReq( VOS_VOID );
extern VOS_VOID RABM_SndPdcpDataReq( VOS_UINT8 ucEntId, TAFRABM_PS_DATA_REQ_STRU *pData );
extern VOS_VOID RABM_SndRrcQosUpdReq(  VOS_UINT8           ucEntId );
extern VOS_VOID RABM_SndTafPsDataInd( VOS_UINT8  ucEntId,  PDCP_RABM_DATA_BUF_STRU  *pRcvMsg );
extern VOS_VOID RABM_SndTafInActNsapiInd( VOS_UINT8 ucNsapi );
extern VOS_VOID RABM_SndTafInActSiInd( VOS_UINT8 ucSi );
extern VOS_VOID RABM_SndGmmRabRelInd( VOS_VOID );

extern VOS_VOID NAS_RABM_SndGmmRbSetupInd(VOS_VOID);

extern VOS_VOID RABM_SndTafStatusInd( VOS_UINT8 ucNsapiOrSi,VOS_UINT8 ucStatusFlg,VOS_UINT8 ucCause );
extern VOS_VOID RABM_SndRrcRabRsp( VOS_UINT8 ucRabNum, RRRABM_RAB_IND_STRU *pMsg );
extern VOS_VOID RABM_SndSmDeactReq(VOS_UINT8   ucNsapi);
extern VOS_VOID RABM_SndCcSyncInd(VOS_UINT8 ucResult, VOS_UINT32 ulSi);
extern VOS_VOID RABM_SndCallSyncInd(VOS_UINT32 ulResult, RAB_INFO_STRU *pRabInfo);
extern VOS_VOID RABM_SndTafCsDataInd(RLC_RABM_CS_DATA_IND_STRU *pRcvMsg, VOS_UINT8 ucEntId);
extern VOS_VOID RABM_RcvTcTestReq(TCRABM_TEST_REQ_STRU *pRcvMsg);
extern VOS_VOID RABM_RcvTcTestLoopReq(TCRABM_TEST_LOOP_REQ_STRU *pRcvMsg);
extern VOS_VOID RABM_SndTcTestCnf(TCRABM_TEST_CNF_STRU *pSndMsg);
extern VOS_VOID RABM_SndTcTestLoopCnf(VOS_VOID);
extern VOS_VOID Rabm_TcInfSave(RRRABM_RAB_IND_STRU *pMsg, VOS_UINT8 ucRabId);
extern VOS_VOID RABM_TcInfRls(RRRABM_RAB_IND_STRU *pMsg,VOS_UINT8  ucRabId);
extern VOS_VOID RABM_SndTcPsData(VOS_UINT8 ucEntId, PDCP_RABM_TC_DATA_STRU *pData);
extern VOS_VOID RABM_SndTcCsData(VOS_UINT8 ucEntId, RLC_RABM_CS_DATA_IND_STRU *pData);
extern VOS_VOID RABM_SndTcRabInd(VOS_UINT8 ucEndId, VOS_UINT8 ucSetUpFlg);
extern VOS_VOID RABM_TcRbStatus(RRRABM_STATUS_IND_STRU *pMsg, VOS_UINT8 ucRabId, VOS_UINT8 ucRelFlg);
extern VOS_VOID API_CcSyncInd(VOS_UINT8  ucActType, VOS_UINT32 ucRabId);

/*****************************************************************************
 函 数 名  : NAS_RABM_SendApsSysChgInd
 功能描述  : 向APS发送SYS切换指示
 输入参数  : ulMsgId                    - 消息ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 消息发送成功
             VOS_ERR                    - 消息发送失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_SendApsSysChgInd(
    VOS_UINT32                          ulMsgId
);


VOS_VOID  NAS_RABM_SndCdsFreeBuffDataInd(VOS_UINT8 ucRabId);

VOS_VOID  NAS_RABM_SndCdsSendBuffDataInd(
    VOS_UINT8                                               ucRabId,
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32        enSndBuffDataAllowedType
);

VOS_UINT32 NAS_RABM_DL_DataInd(
    VOS_UINT8                           ucRabId,
    TTF_MEM_ST                         *pstData
);

VOS_VOID  NAS_RABM_SndCdsQosFcRabCreateInd(
    VOS_UINT8                           ucRabId,
    QCI_TYPE_ENUM_UINT8                 enQci
);

VOS_VOID  NAS_RABM_SndCdsQosFcRabReleaseInd(
    VOS_UINT8                           ucRabId
);

QCI_TYPE_ENUM_UINT8 NAS_RABM_QosParaTransferToQci(
    VOS_UINT8                           ucTrafficClass,
    VOS_UINT8                           ucTransDelay,
    VOS_UINT8                           ucTraffHandlPrior,
    VOS_UINT8                           ucSrcStatisticsDescriptor,
    VOS_UINT8                           ucSignallingIndication
);

QCI_TYPE_ENUM_UINT8 NAS_RABM_GetQciFromQos(
    VOS_UINT32                      ulQosLength,
    VOS_UINT8                      *pQosValue
);



/*****************************************************************************
 函 数 名  : NAS_RABM_IsRabIndPsDonmain
 功能描述  : 判断RRRABM_RAB_IND消息中是否包含PS域的RAB信息
 输入参数  : pstRrcRabInd - RRRABM_RAB_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE     - 包含PS域RAB信息
             VOS_FALSE    - 不包含PS域RAB信息
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 NAS_RABM_IsRabIndPsDonmain(
    RRRABM_RAB_IND_STRU                *pstRrcRabInd
);

VOS_VOID NAS_RABM_StartReestRabPendingTmr(VOS_UINT8 ucRabId);
VOS_VOID NAS_RABM_StopReestRabPendingTmr(VOS_UINT8 ucRabId);
VOS_VOID NAS_RABM_ProcTiRabReestRequestExpired(VOS_VOID);
VOS_VOID NAS_RABM_ProcTiRabReestPendingExpired(VOS_UINT8 ucRabId);

extern VOS_VOID NAS_RABM_SndAtReleaseRrcCnf(
    VOS_UINT16                          usClientId,                             /* AT发消息给RABM所带的ClientId */
    VOS_UINT8                           ucOpId,                                 /* AT发消息给RABM所带的OpId */
    VOS_UINT32                          ulRslt
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_VOID NAS_RABM_SndAtSetVoicePreferParaCnf(
    MN_CLIENT_ID_T                      usClientId,                             /* AT发消息给RABM所带的ClientId */
    MN_OPERATION_ID_T                   ucOpId,                                 /* AT发消息给RABM所带的OpId */
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
);

VOS_VOID NAS_RABM_SndAtQryVoicePreferParaCnf(
    MN_CLIENT_ID_T                      usClientId,                             /* AT发消息给RABM所带的ClientId */
    MN_OPERATION_ID_T                   ucOpId,                                 /* AT发消息给RABM所带的OpId */
    VOS_UINT32                          ulRslt
);
VOS_VOID NAS_RABM_SndAtVoicePreferActStatus(VOS_UINT32 ulVpStatus);
VOS_VOID  NAS_RABM_SndCdsVoicePreferActInd(VOS_UINT32 ulVpInd);
VOS_VOID NAS_RABM_SndWasVoicePreferStartReq(VOS_VOID);
VOS_VOID NAS_RABM_SndWasVoicePreferStopReq(VOS_VOID);
VOS_VOID NAS_RABM_SendVpActIndToOtherModule(VOS_UINT32 ulVpActInd);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
