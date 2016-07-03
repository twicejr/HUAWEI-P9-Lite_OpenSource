
#ifndef _SMC_EXT_H_
#define _SMC_EXT_H_


#include "NasSms.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)


/* SmsMain.c */
extern VOS_VOID  SMS_InitEntity(VOS_VOID);
extern VOS_VOID  SMS_SmrRcvTafMsgDistr(VOS_VOID *pRcvMsg);
extern VOS_VOID  SMC_RcvLlcMsgDistr(VOS_VOID *pRcvMsg);
extern VOS_VOID NAS_SMS_ProcMnMsg(
    const VOS_VOID                      *pRcvMsg
);

extern VOS_VOID  SMC_RcvGmmMsgDistr(VOS_VOID *pRcvMsg);
extern VOS_VOID  SMC_RcvMmMsgDistr(VOS_VOID *pRcvMsg);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_SMS_RcvLmmMsgDistr(VOS_VOID *pRcvMsg);

extern VOS_VOID NAS_SMS_ProcLmmEstCnf(VOS_VOID  *pRcvMsg);
extern VOS_VOID NAS_SMS_ProcLmmDataInd(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_SMS_ProcLmmErrInd(
    VOS_VOID                           *pRcvMsg
);


extern VOS_VOID NAS_SMS_SndLmmDataReq(
    VOS_UINT8                           ucType,
    VOS_UINT8                           ucCause,
    VOS_UINT8                           ucTi
);

extern VOS_UINT32 NAS_SMS_SndLmmCpDataReq(
    VOS_UINT8                          *pucSndMsg,
    VOS_UINT32                          ulMsgLen
);

extern VOS_VOID NAS_SMS_SndLmmEstReq(
    VOS_UINT32                          ulEstCause
);

#endif

#if (FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID NAS_SMS_SndMmBeginSessionNotify(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enSessionType
);
extern VOS_VOID NAS_SMS_SndMmEndSessionNotify(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enSessionType
);
#endif
extern VOS_VOID NAS_SMS_SndGmmBeginSessionNotify(
    GMMSMS_SESSION_TYPE_ENUM_UINT8      enSessionType
);
extern VOS_VOID NAS_SMS_SndGmmEndSessionNotify(
        GMMSMS_SESSION_TYPE_ENUM_UINT8      enSessionType
);

/* extern VOS_UINT8 SMS_TimerStop(HTIMER *, VOS_UINT8 ); */
VOS_UINT8 SMS_TimerStop(
                        VOS_UINT8       ucTimerId
                        );
/* extern VOS_UINT8 SMS_TimerStart(HTIMER * TimerId); */
VOS_UINT8 SMS_TimerStart(
                    VOS_UINT8               ucTimerId
                    );
extern VOS_VOID  SMS_TimerMsgDistr(VOS_UINT32 ulTimerId);
extern VOS_VOID  SMC_GetTimerInfo( VOS_UINT8    ucTimerId,
                                    HTIMER**     ppTimer,
                                    VOS_UINT32*  pulTimerLength,
                                    VOS_UINT8**  ppucTimerSta );
extern VOS_VOID  SMS_PrintInfo(VOS_VOID);

/* SmsPsSmProcess.c */
extern VOS_VOID SMC_RcvPsMtData( VOS_UINT8* pucCpdu, VOS_UINT32  ulCpduLen );
extern VOS_VOID SMC_RcvPsMoData( VOS_UINT8* pucCpdu, VOS_UINT32  ulCpduLen );
extern VOS_VOID SMC_RcvGmmEstCnf(VOS_VOID);

extern VOS_VOID SMC_ComPsMtErr(SMR_SMT_ERROR_ENUM_UINT32           enErrorCode);
extern VOS_VOID SMC_ComPsMoErr(SMR_SMT_ERROR_ENUM_UINT32           enCause);
extern VOS_VOID SMS_ReportN2MOtaMsg(NAS_MSG_STRU *pNasMsg);

extern VOS_VOID SMC_ComPsWaitAckSta( VOS_UINT8 ucMtFlg );
extern VOS_VOID SMC_RcvGmmServStatusInd(
                      GMMSMS_SERVICE_STATUS_IND_STRU  *pRcvMsg                       /* 收到的消息首地址                         */
                      );

extern VOS_VOID SMC_RcvGmmErrInd( PMMSMS_ERROR_IND_STRU  *pRcvMsg);
extern VOS_VOID SMC_SndGmmDataReq( VOS_UINT8  ucType,VOS_UINT8 ucCause,VOS_UINT8 ucTi);
extern VOS_VOID SMC_SndGmmMsg(VOS_UINT8 *pucMsg,VOS_UINT8 ucType,VOS_UINT16 usLen);

/* SmsCsSmProcess.c */
extern VOS_VOID SMC_RcvNwCsMtData( VOS_UINT8* pucCpdu, VOS_UINT32 ulCpduLen );
extern VOS_VOID SMC_RcvMmEstInd( VOS_UINT8* pucCpdu, VOS_UINT32 ulCpduLen );
extern VOS_VOID SMC_RcvNwCsMoData( VOS_UINT8* pucCpdu, VOS_UINT32  ulCpduLen );
extern VOS_VOID SMC_RcvMmEstCnf( MMSMS_EST_CNF_STRU * pRcvMsg );

extern VOS_VOID SMC_ComCsMtErr(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucTi
);
extern VOS_VOID SMC_ComCsMoErr(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucTi
);


extern VOS_VOID NAS_SMS_ChangeCsMoEntityState(VOS_UINT8  ucState);
extern VOS_VOID NAS_SMS_ChangeCsMtEntityState(VOS_UINT8  ucState);
extern VOS_VOID NAS_SMS_ChangePsMoEntityState(VOS_UINT8  ucState);
extern  VOS_VOID NAS_SMS_ChangePsMtEntityState(VOS_UINT8  ucState);

extern VOS_VOID SMC_ComCsWaitAckSta( VOS_UINT8 ucMtFlg );
extern VOS_VOID SMC_RcvMmRelInd( MMSMS_REL_IND_STRU  *pRcvMsg );
extern VOS_VOID SMC_SndMmDataReq( VOS_UINT8 ucType, VOS_UINT8 ucCause, VOS_UINT8 ucTi );
extern VOS_VOID SMC_SndRelReq( VOS_UINT8 ucTi );
extern VOS_VOID SMC_SndMmMsg( VOS_UINT8 *pucMsg, VOS_UINT8 ucType, VOS_UINT16 usLen );
extern VOS_VOID SMC_SndMmCpAckMsg(VOS_UINT8 ucTi);
extern VOS_VOID SMC_ComCsInitEnt( VOS_UINT8   ucMtFlg );
extern VOS_VOID SMC_RcvMmRegStaInd( MMSMS_REG_STATE_IND_STRU *pRcvMsg );
extern VOS_VOID SMC_MoBufferCpAckSend(VOS_VOID);

/* SmcCom.c */
extern VOS_VOID SMC_TimerTc1mExp( VOS_UINT8 ucTimerId );
extern VOS_UINT8 SMC_ComNwMsgChk( VOS_UINT8* pucCpdu, VOS_UINT32  ulCpduLen );

/* SmcSmrApi.c */
extern VOS_VOID SMC_SmrApiDataReq(VOS_UINT8 *pucData,VOS_UINT16 usLen);
extern VOS_VOID SMC_SmrApiEstReq(VOS_UINT8 ucCurSendDomain,VOS_UINT8 *pucData,VOS_UINT32 ulLen);
extern VOS_VOID SMC_SmrApiAbortReq(VOS_UINT8     ucCause);
extern VOS_VOID SMC_SmrApiRelReq(VOS_UINT8     ucRelCause,VOS_UINT8     ucMtFlg);
extern VOS_UINT32 SMR_SmcApiDataInd(VOS_UINT8 *pucData,VOS_UINT32 ulLen);
/* 参数改变:增加接收域 */
extern VOS_UINT32 SMR_SmcApiEstInd(VOS_UINT8 *pucData,VOS_UINT32 ulLen, VOS_UINT8 ucRcvDomain);

extern VOS_VOID SMR_SmcApiErrorInd(
    SMR_SMT_ERROR_ENUM_UINT32           enCause,
    VOS_UINT8                           ucMtFlag
);

/* SmrTafMsg.c */
/* 函数名改变，参数改变:增加接收域 */
extern VOS_VOID SMS_SendMnEstInd( VOS_UINT8 *pucData,VOS_UINT32  ulLen, VOS_UINT8 ucRcvDomain);

extern VOS_VOID SMS_SendMnReportReq(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulSendLen
);
extern VOS_VOID SMS_SendMnMtErrInd(SMR_SMT_ERROR_ENUM_UINT32 enErrorCode);

extern VOS_VOID SMS_AttachFlag( VOS_UINT8 ucDomain,VOS_UINT8 ucRegState);
extern VOS_VOID SMS_RcvMnReportReq(const SMT_SMR_DATA_STRU  *pstData);
/* SmrCom.c*/

extern VOS_VOID SMR_MemNotifyRetrans(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulSendLen
);

extern VOS_VOID SMR_TimerTr1mExpire(VOS_VOID);
extern VOS_VOID SMR_TimerTr2mExpire(VOS_VOID);
extern VOS_VOID SMR_TimerTramExpire(VOS_VOID);
extern VOS_VOID SMR_SndRpErrorReq(VOS_UINT8 ucMr,VOS_UINT8 ucCause,VOS_UINT8 ucMtFlg);

/* Delete SMR_MkSndReportError */

extern VOS_UINT8 SMR_SmcChk(VOS_UINT8 *pucData,VOS_UINT32 ulLen);
extern VOS_VOID SMS_SendMnMoLinkCloseInd(VOS_VOID);
extern VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId);

extern VOS_VOID SMS_GetTc1mTimeOutRetryFlag(
    VOS_UINT8                           ucExpireTimes,
    VOS_BOOL                           *pbRetryFlag
);

extern VOS_VOID SMS_GetCustomizedPara(VOS_VOID);


VOS_VOID NAS_SMS_RcvNackMsg(MMSMS_NACK_DATA_IND_STRU *pstNackMsg);

VOS_UINT32 NAS_SMS_ResendCsRpData(VOS_UINT8 ucRetransFlg);

VOS_UINT32 NAS_SMS_ResendCsRpReport(VOS_VOID);

VOS_UINT32 NAS_SMS_ResendPsRpData(VOS_UINT8 ucRetransFlg);

VOS_UINT32 NAS_SMS_ResendPsRpReport(VOS_VOID);


extern VOS_VOID  NAS_SMS_LogSmsStateInfo(
    VOS_UINT8                           ucSmsState
);

extern VOS_VOID  NAS_SMS_ReSendLmmCpDataReq(
    VOS_UINT32                          ulResendMoFlg
);
extern VOS_VOID  NAS_SMS_ReSendGmmCpDataReq(
    VOS_UINT32                          ulResendMoFlg
);

VOS_VOID  SMS_GetPsConcatenateFlagFromNV(VOS_VOID);

VOS_VOID SMS_SetSmsPsConcatenateFlag(
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8 enFlag
);

NAS_SMS_PS_CONCATENATE_ENUM_UINT8 SMS_GetSmsPsConcatenateFlag(VOS_VOID);

VOS_VOID SMS_GetSmsFilterEnableFlgFromNV( VOS_VOID );

VOS_UINT32 GUNAS_GetSmsFilterFlg( VOS_VOID );


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
