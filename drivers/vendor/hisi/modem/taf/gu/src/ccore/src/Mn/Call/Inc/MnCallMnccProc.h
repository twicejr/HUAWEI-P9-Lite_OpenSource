
#ifndef  MN_CALL_MNCC_PROC_H
#define  MN_CALL_MNCC_PROC_H



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMncc.h"
#include "product_config.h"
#include "MnCallApi.h"
#include "MnCallMgmt.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/

#define CALL_MAX_ENT_NUM  7

/* 该结构用于CCBS操作过程中
   暂时存储CCBS信息 */
#define MN_CALL_CCBS_INVALID_INDEX              (0)
#define MN_CALL_CCBS_MAX_INDEX                  (5)
#define MN_CALL_CCBS_DEFAULT_INDEX              (1)

#define CCA_SS_DIAG_CCBS_POSSIBLE               (7)
#define MN_CALL_NET_TYPE_GSM                    (0)

typedef struct
{
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_UINT8                           ucCallId;
} MN_CALL_WAIT_SEND_ALERT_STRU;


#define MN_CALL_BCD_ODD_NUMBER_END                          (0xF0)

/* MN_CALL_MM_EMERGENCY_CONTENT_STRU、MN_CALL_MM_EMERGENCY_LIST_STRU调整到SDC */


typedef enum
{
    MN_CALL_ACTIVE_SWITCH_ON = 0,
    MN_CALL_ACTIVE_SWITCH_OFF,

    RMN_CALL_ACTIVE_SWITCH_BUTT
}MN_CALL_TIMER_ACTIVE_SWITCH_ENUM;               /*标识某CALLID是否激活了*/


typedef struct
{
    VOS_UINT32                          ulStartCallTime;                        /* 当前通话开始时间 单位为秒 */
    VOS_UINT32                          ulTotalCallTime;                        /*累计通话时间*/
    VOS_UINT32                          ulPreCallTime;                          /*上次通话时间*/
    MN_CALL_TIMER_ACTIVE_SWITCH_ENUM       CallidActiveSwitch;                  /*标识该Callid是否激活*/
}MN_CALL_TIMER_CALC_ST;


typedef struct
{
    MN_CLIENT_ID_T                                          clientId;
    MN_OPERATION_ID_T                                       opId;
    VOS_UINT8                                               ucCallId;
    VOS_UINT8                                               ucTi;                      /* TI信息，保护TI FLAG和TI两项，具体格式参考上面描述 */
    MN_CALL_STATE_ENUM_UINT8                                enCallState;               /* IMSA同步过来的IMS域下的呼叫状态 */
    MN_CALL_MODE_ENUM_U8                                    enCallMode;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    MN_CALL_DIR_ENUM_U8                                     enCallDir;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    VOS_UINT8                                               ucLocalAlertedFlag;        /* IMS域是否进行过本地振铃 */
    VOS_UINT8                                               aucReserve1[1];
    MN_CALL_BCD_NUM_STRU                                    stCallNumber;
    MN_CALL_CALLED_NUM_STRU                                 stCalledNumber;
    MN_CALL_BCD_NUM_STRU                                    stRedirectNumber;
    MN_CALL_BCD_NUM_STRU                                    stConnectNumber;
}TAF_CALL_SRVCC_CALL_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucRslt;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucReserve[2];
    TAF_CALL_SRVCC_CALL_INFO_STRU       astCallInfo[CALL_MAX_ENT_NUM];
}TAF_CALL_LOG_IMSA_API_GET_SRVCC_CALL_INFO_STRU;

/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern VOS_UINT32 VOS_GetTick(VOS_VOID);

/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsMtCallAllowed(
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup,
    VOS_UINT8                           ucCallId,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
);


VOS_VOID  MN_CALL_ProcMnccSetupInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccSetupCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccSetupComplInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccCallProcInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccSyncInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccAlertInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccDiscInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccRelInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccRelCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


VOS_VOID  MN_CALL_ProcMnccRejInd(
    MNCC_IND_PRIM_MSG_STRU             *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccFacilityInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccHoldCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccHoldRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccRetrieveCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID  MN_CALL_ProcMnccRetrieveRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


VOS_VOID  MN_CALL_ProcMnccFacilityLocalRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  MN_CALL_ReportChannelEvent(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enEventType
);


VOS_VOID MN_CALL_SetChannelOpenFlg(
    VOS_BOOL                            bChannelOpenFlg
);

VOS_BOOL MN_CALL_GetChannelOpenFlg( VOS_VOID );


VOS_VOID MN_CALL_SetWaitSendAlertStatus(
    VOS_BOOL                            bWaitSendAlertStatus,
    VOS_UINT8                           uccallId
);


VOS_VOID  MN_CALL_ProcMnccProgressInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


VOS_VOID  MN_CALL_SetMmEmerNumList(
    MNCC_EMERGENCY_LIST_IND_STRU        *pstMnccEmcListInd
);

VOS_UINT32 MN_CALL_GetTchParm(
    MN_CALL_CHANNEL_PARAM_STRU          *pstChannParm
);

VOS_BOOL MN_CALL_GetTchStatus( VOS_VOID );




VOS_VOID MN_CALL_PorcMnccPromptInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


VOS_VOID MN_CALL_ProcMnccEstInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  MN_CALL_ProcMnccRecallInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID MN_CALL_GetWaitSendAlertStatus(
    VOS_BOOL                            *pbWaitSendAlertStatus,
    VOS_UINT8                           *puccallId
);


VOS_UINT32 MN_CALL_UpdateCcUus1Info(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);


VOS_UINT32 MN_CALL_GetCcUus1Info(
    VOS_UINT32                          *pulActNum,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

VOS_VOID  MN_CALL_ProcUusInfoInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  MN_CALL_ProcEmergencyListInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID MN_CALL_ReportHoldEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId );

VOS_VOID MN_CALL_ReportRetrieveEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId );


VOS_VOID  MN_CALL_ProcBufferedCall(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_CALL_ProcBufferedRedialMessage(
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);



VOS_VOID MN_CALL_SndAtChannelInfoInd(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enChannelEvent,
    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo,
    VOS_UINT8                           ucIsLocalAlertingFlag
);

/* 删除该函数，功能实现移到函数MN_CALL_ReportChannelEvent中 */

VOS_UINT32 TAF_CALL_IsNeedLocalAlerting(const NAS_CC_IE_PROGRESS_INDICATOR_STRU *pstProgInd);

VOS_VOID  TAF_CALL_RcvCcStartDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  TAF_CALL_RcvCcStartDtmfRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  TAF_CALL_RcvCcStopDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  TAF_CALL_ProcMnccSrvccStatusInd(
    MNCC_SRVCC_STATUS_IND_STRU         *pstSrvccMsg
);

VOS_VOID TAF_CALL_MapCallInfoToCcInfo(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    VOS_UINT8                          *pucCallNum
);

VOS_VOID TAF_CALL_ProcDtmfBuffer(VOS_VOID);

VOS_VOID TAF_CALL_ProcSrvccSyncInfo(VOS_VOID);
#endif

VOS_UINT8 TAF_CALL_IsEcallRedialExist(VOS_VOID);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ProcessEcallPeriodTimerLen(VOS_UINT8 ucCallId);

VOS_VOID TAF_CALL_ProcEcallRel(
    MN_CALL_MGMT_STRU                  *pstCallEntity);
#endif

VOS_VOID  MN_CALL_SendVcMsg(
    CALL_VC_MSG_ID_ENUM_U16             enEventType
);

VOS_VOID TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ENUM_UINT16 enCallType);



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_MNCC_PROC_H */

