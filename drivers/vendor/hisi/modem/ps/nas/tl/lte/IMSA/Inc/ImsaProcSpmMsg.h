/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaProcSpmMsg.h
    Description : ImsaProcSpmMsg.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSAPROCSPMMSG_H__
#define __IMSAPROCSPMMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    枚举名    : IMSA_SRVCC_ABNORMAL_TYPE_ENUM
    枚举说明  : SRVCC异常类型
*****************************************************************************/
enum    IMSA_SRVCC_ABNORMAL_TYPE_ENUM
{
    IMSA_SRVCC_ABNORMAL_STOP_REQ        = 1,            /* SRVCC过程中关机 */
    IMSA_SRVCC_ABNORMAL_DEREG_REQ       = 2,            /* SRVCC过程中DETACH */
    IMSA_SRVCC_ABNORMAL_STATUS_CHANGE   = 3,            /* SRVCC过程中状态迁离CONN+REG */
    IMSA_SRVCC_ABNORMAL_BUTT
};
typedef VOS_UINT8 IMSA_SRVCC_ABNORMAL_TYPE_ENUM_UINT32;




/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef VOS_UINT32 ( * IMSA_SPM_CALL_MSG_ACTION_FUN )
(
   VOS_VOID  *  /* ???￠???? */
);

typedef struct
{
    SPM_IMSA_MSG_TYPE_ENUM_UINT32                   enMsgName;            /* 消息ID*/
    IMSA_SPM_CALL_MSG_ACTION_FUN                    pfActionFun;            /* 处理函数 */
}IMSA_SPM_CALL_MSG_ACT_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32 IMSA_CallProcSpmMsgGetClprInfo(VOS_VOID *pMsg);

extern VOS_UINT32 IMSA_CallSendSpmStartDtmfCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallSendSpmStopDtmfCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallProcSpmMsgOrig(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgSups(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgStartDtmf(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgStopDtmf(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgGetInfo(VOS_VOID *pMsg);
extern VOS_VOID   IMSA_ProcSpmCallMsg(const VOS_VOID *pRcvMsg);
extern VOS_UINT32 IMSA_CallSendSpmOrigCnfMsg(VOS_UINT16 usClientId,
                                             VOS_UINT32 ulOpId,
                                             VOS_UINT32 ulCallId,
                                             TAF_CS_CAUSE_ENUM_UINT32 ulResult);
extern VOS_UINT32 IMSA_CallSendSpmSupsCnfMsg(VOS_UINT16 usClientId,
                                             VOS_UINT32 ulOpId,
                                             VOS_UINT32 ulCallId,
                                             TAF_CS_CAUSE_ENUM_UINT32 ulResult);

extern VOS_VOID IMSA_USSD_SndImsUssdReqMsg
(
    IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8   encType,
    VOS_UINT16   usLength,
    const VOS_UINT8   *pucMessage
);
extern VOS_VOID IMSA_USSD_SndImsUssdDisconnectMsg
(
    VOS_VOID
);
extern VOS_VOID IMSA_USSD_Init(VOS_VOID);
extern VOS_VOID IMSA_SMS_ProcTimerMsgWaitNetRsp(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_SMS_ProcTimerMsgWaitAppRsp(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_SrvccFailBuffProc( VOS_VOID );
extern VOS_VOID IMSA_SrvccSuccBuffProc( VOS_VOID );
extern VOS_VOID IMSA_SrvccAbormalClearBuff
(
    IMSA_SRVCC_ABNORMAL_TYPE_ENUM_UINT32    enAbnormalType
);

extern VOS_UINT32 IMSA_CallProcSpmMsgInviteNewPtpt(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallSendSpmInviteNewPtptCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);



extern VOS_UINT32 IMSA_CallSendSpmCallTypeChangeInfoIndMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    MN_CALL_TYPE_ENUM_U8                enSrcCallType,
    MN_CALL_TYPE_ENUM_U8                enDestCallType,
    const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8    EmcSubType
);
extern VOS_UINT32 IMSA_CallSendSpmModifyCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallSendSpmAnswerRemoteModifyCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);
extern VOS_UINT32 IMSA_CallProcSpmMsgModifyReq
(
    VOS_VOID *pMsg
);
extern VOS_UINT32 IMSA_CallProcSpmMsgAnswerRemoteModifyReq
(
    VOS_VOID *pMsg
);

extern VOS_UINT32 IMSA_CallProcSpmMsgEconfDial(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgEconfAddUser(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_CallProcSpmMsgGetEconfInfo
(
    VOS_VOID *pMsg
);

extern VOS_UINT32 IMSA_CallSendSpmEconfAddUserCnfMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
);


VOS_VOID IMSA_CallSendCcwaCapInfo(VOS_UINT8 ucCcwacap);


extern VOS_VOID IMSA_CallSupsCmdReqSrvccingProc
(
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstCallSupsCmdReq
);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaProcSpmMsg.h */




