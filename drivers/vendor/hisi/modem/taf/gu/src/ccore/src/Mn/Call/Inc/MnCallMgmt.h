
#ifndef  MN_CALL_MGMT_H
#define  MN_CALL_MGMT_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallCtx.h"
#include "MnCallApi.h"
#include "UsimPsApi.h"
#include "MnCallMnccProc.h"
#include "MnCallFacilityDecode.h"
#include "product_config.h"
#include "siappstk.h"
#include "hi_list.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
#define MN_CALL_DISC_EVENT_CAUSE_LEN        (3)

#define MN_CALL_IS_OPEN_CODEC(ucCallState, ucStartedHifiFlag)           \
               ( (CALL_IMSA_SRVCC_CALL_ACTIVE       == ucCallState)        \
              || (CALL_IMSA_SRVCC_CALL_HELD         == ucCallState)         \
              || ((CALL_IMSA_SRVCC_CALL_ALERTING    == ucCallState)         \
               && (VOS_TRUE                         == ucStartedHifiFlag)))

/*****************************************************************************
  3类型定义
*****************************************************************************/


enum MN_CALL_POWER_STATE_ENUM
{
    MN_CALL_POWER_STATE_OFF                 = 0, /*关机*/
    MN_CALL_POWER_STATE_ON                  = 1, /*开机*/
    MN_CALL_POWER_STATE_BUTT
};
typedef VOS_UINT8  MN_CALL_POWER_STATE_ENUM_U8;

/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define MN_CALL_SIM_ABSENT              PS_USIM_GET_STATUS_ABSENT               /* SIM不存在                                */
#define MN_CALL_SIM_PRESENT             PS_USIM_GET_STATUS_PRESENT              /* SIM存在                                  */


/* PC回放导出全局变量使用 */
#define EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* 为PC工程回放定义的消息 */

/* ASSERT */
#ifdef  _DEBUG
#define  MN_CALL_ASSERT(expr) \
        if(!(expr)) \
        { \
            MN_ERR_LOG("Assertion failed: " #expr); \
        }
#else
#define  MN_CALL_ASSERT(expr)   ((VOS_VOID)0)
#endif /* _DEBUG */

enum MN_CALL_HOOK_MSG_ID_ENUM
{
    /* STK呼叫事件 MT CALL  SI_STK_MT_CALL_EVENT_STRU */
    MN_CALL_HOOK_STK_MT_CALL_EVENT                          = 0x02aa,           /* _H2ASN_MsgChoice SI_STK_MT_CALL_EVENT_STRU        */
    /* STK呼叫事件 CALL Disconnect SI_STK_CALL_DISCONNECTED_EVENT_STRU */
    MN_CALL_HOOK_STK_CALL_DISC_EVENT                        = 0x02ab,           /* _H2ASN_MsgChoice SI_STK_CALL_DISCONNECTED_EVENT_STRU */
    /* STK呼叫事件 CALL Connect SI_STK_CALL_CONNECTED_EVENT_STRU */
    MN_CALL_HOOK_STK_CALL_CONN_EVENT                        = 0x02ac,           /* _H2ASN_MsgChoice SI_STK_CALL_CONNECTED_EVENT_STRU */

    MN_CALL_HOOK_STK_ENVELOPE                               = 0x0300,           /* _H2ASN_MsgChoice SI_STK_ENVELOPE_STRU */

    MN_CALL_HOOK_MSG_ID_BUTT
};
typedef VOS_UINT32 MN_CALL_HOOK_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER
    MN_CALL_HOOK_MSG_ID_ENUM_UINT32     enMsgId;                                /* 消息名 */
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
} MN_CALL_HOOK_MSG_STRU;


typedef struct
{
    MN_CALL_ID_T                        CallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF持续时间，0: 代表停止DTMF */

    VOS_UINT16                          usOffLength;                            /* stop dtmf req和start dtmf req时间间隔，单位ms*/
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           aucReserved1[3];
} TAF_CALL_DTMF_INFO_STRU;


typedef struct
{
    TAF_CALL_DTMF_INFO_STRU             stDtmf;
    HI_LIST_S                           stList;
} TAF_CALL_DTMF_NODE_STRU;

#define TAF_CALL_DTMF_BUF_MAX_CNT               (32)                            /* 最多缓存DTMF信息的个数 */


typedef struct
{
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT8                           ucDtmfCnt;
    VOS_UINT8                           aucReserved1[2];
    TAF_CALL_DTMF_INFO_STRU             stCurrDtmf;
    HI_LIST_S                           stList;
} TAF_CALL_DTMF_CTX_STRU;

/*****************************************************************************
  6 全局变量声明
*****************************************************************************/


/*****************************************************************************
  7 接口函数声明
*****************************************************************************/


extern VOS_VOID  MN_CALL_StartFluxCalculate( VOS_UINT8 ucCallId);


VOS_VOID  MN_CALL_StopFluxCalculate( VOS_UINT8 ucCallId);

/* 复位所有的呼叫信息 */
VOS_VOID   MN_CALL_ResetAllCalls(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);

/* 分配Call ID */
VOS_UINT32 MN_CALL_AllocCallId(MN_CALL_ID_T *pCallId);

/* 释放Call ID */
VOS_VOID   MN_CALL_FreeCallId(MN_CALL_ID_T  callId);

/* 检查是否可以发起/接听一个新的呼叫 */
VOS_BOOL   MN_CALL_IsAllowToMakeNewCall(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

/* 新建一个呼叫管理实体 */
VOS_VOID  MN_CALL_CreateCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulTi,
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo,
    const MN_CALL_BCD_NUM_STRU          *pstNumber
);

VOS_VOID  MN_CALL_CreateMoCallEntity(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT8 TAF_CALL_IsCallTypeEcall(MN_CALL_ID_T ucCallId);
#endif

VOS_VOID TAF_CALL_UpdateCallInfo(
    MN_CALL_ID_T                        ucCallId,
    MN_CALL_INFO_STRU                  *pstCallInfo
);

VOS_UINT32 MN_CALL_GetSpecificCallInfo(
    MN_CALL_ID_T                        CallId,
    MN_CALL_MGMT_STRU                  *pstCallInfo
);

VOS_VOID MN_CALL_GetCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                           *pbReleaseFlag
);

VOS_VOID TAF_CALL_FillDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf
);

VOS_UINT8 TAF_CALL_IsCallTypeEmgencyCall(MN_CALL_ID_T ucCallId);



VOS_VOID  MN_CALL_CreateMtCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
);


VOS_VOID  MN_CALL_DeleteCallEntity(
    MN_CALL_ID_T                        callId
);


VOS_UINT32 MN_CALL_GetCcTi(
    MN_CALL_ID_T                        callId
);

VOS_UINT32 MN_CALL_GetCcCallDir(
    MN_CALL_ID_T                        callId
);


VOS_VOID  MN_CALL_ReportEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_EVENT_ENUM_U32              enEventType
);


VOS_VOID  MN_CALL_UpdateClientId(
    MN_CALL_ID_T                        callId,
    MN_CLIENT_ID_T                      ucClientId
);


VOS_VOID  MN_CALL_UpdateCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               enCallState
);


VOS_VOID  MN_CALL_UpdateMptyState(
    MN_CALL_ID_T                        callId,
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState
);


VOS_VOID  MN_CALL_UpdateCallType(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID  MN_CALL_UpdateCallMode(
    MN_CALL_ID_T                        callId,
    MN_CALL_MODE_ENUM_U8                enCallMode
);


VOS_VOID  MN_CALL_UpdateDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo
);



VOS_VOID  MN_CALL_UpdateRedirNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNumber
);


VOS_VOID  MN_CALL_UpdateConnNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstConnNumber
);


VOS_VOID  MN_CALL_UpdateCallNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstCallNumber
);


VOS_VOID  MN_CALL_UpdateCalledNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CALLED_NUM_STRU      *pstCalledNumber
);


VOS_VOID  MN_CALL_UpdateSsNotify(
    MN_CALL_ID_T                        callId,
    const MN_CALL_SS_NOTIFY_STRU        *pstSsInfo
);


VOS_VOID  MN_CALL_UpdateCcCause(
    MN_CALL_ID_T                        callId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCcCause
);


VOS_VOID  MN_CALL_UpdateNoCliCause(
    MN_CALL_ID_T                        callId,
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCliCause
);


VOS_VOID  MN_CALL_UpdateRabId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucRabId
);


VOS_VOID  MN_CALL_GetCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               *penCallState,
    MN_CALL_MPTY_STATE_ENUM_U8          *penMptyState
);

TAF_CALL_SUB_STATE_ENUM_UINT8 TAF_CALL_GetCallSubState(
    MN_CALL_ID_T                        callId
);

VOS_VOID TAF_CALL_SetCallSubState(
    MN_CALL_ID_T                        callId,
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState
);



VOS_VOID  MN_CALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);



VOS_VOID  MN_CALL_RegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp
);


VOS_VOID  MN_CALL_ClearSsKeyEvent(VOS_VOID);



VOS_VOID  MN_CALL_UpdateCallSupsProgress(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    VOS_UINT32                          ulErrno
);


VOS_VOID    TAF_CALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID  MN_CALL_BeginCallSupsCmdProgress(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd
);


VOS_BOOL  MN_CALL_IsCallSupsCmdInProgress(VOS_VOID);



VOS_VOID  MN_CALL_GetCallInfoList(
    TAF_UINT8                           *pucNumOfCalls,
    MN_CALL_INFO_STRU                   *pstCallInfos
);


VOS_VOID  MN_CALL_GetCallsByMptyState(
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);


VOS_BOOL  MN_CALL_TiUsedCheck(
    VOS_UINT32                          ulTi
);



VOS_BOOL  MN_CALL_CheckNotIdleStateExist( VOS_VOID );



VOS_BOOL  MN_CALL_CheckCallEntityExist(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Alloc()
 Description    : 分配InvokeId，此函数为原来的代码进行移植
 Input          : ucTi: 呼叫标识
 Output         : *pInvokeId: 分配的InvokeId
 Return Value   : VOS_OK    分配成功
                : VOS_ERROR 分配失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_INT32 MN_CALL_InvokeIdAlloc(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           *pInvokeId,
    VOS_UINT8                           ucOperateCode
);



VOS_VOID  MN_CALL_GetDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
);


VOS_VOID  MN_CALL_UpdateTi(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
);

VOS_UINT8 TAF_CALL_GetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId
);
VOS_VOID TAF_CALL_SetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucSrvccLocalAlertedFlag
);


VOS_VOID  MN_CALL_GetNotIdleStateCalls(
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);

/*****************************************************************************
 Prototype      : MN_CALL_SsOpCodeTransToSsEvent
 Description    : 将操作码转换成对应的事件
 Input          : sSOpCode - 操作码
 Output         : penEvent - 对应的事件
 Return Value   : VOS_OK    - 转换成功
                : VOS_ERR   - 转换失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-03-26
    Author      : h44270
    Modification: Created function
*****************************************************************************/
VOS_UINT32  MN_CALL_SsOpCodeTransToSsEvent(
    MN_CALL_SS_OPERATION_CODE_T         sSOpCode,
    MN_CALL_SS_PROGRESS_EVT_ENUM        *penEvent
);


VOS_VOID  MN_CALL_GetCallInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_INFO_STRU                   *pstCallInfo
);


VOS_VOID  MN_CALL_DeRegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
);


VOS_VOID  TAF_CALL_ProcRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
);



VOS_VOID  MN_CALL_UpdateCcbsSetup(
    const NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
);


VOS_VOID  MN_CALL_UpdateCcbsSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);


VOS_VOID  MN_CALL_GetCcbsSetup(
    NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
);

VOS_VOID MN_CALL_UpdateCcCallDir(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);


VOS_VOID  MN_CALL_UpdateRecallSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);

/*****************************************************************************
 Prototype      : MN_CALL_CallCtrlProcess
 Description    : 调用USIM模块提供的call control接口，发送Envelop命令给USIM模块
 Input          : pstParam - 主叫的信息，用于填写Envelop命令中的相应参数
 Output         :
 Return Value   : VOS_OK    - 操作成功
                : VOS_ERR - 操作失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-08-19
    Author      : huwen
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_CallCtrlProcess(
    MN_CALL_ORIG_PARAM_STRU             *pstParam
);


VOS_VOID  MN_CALL_UpdateCallCtrlState(
    MN_CALL_ID_T                        callId,
    MN_CALL_CTRL_STATE_ENUM_U32         enCallCtrlState
);


MN_CALL_ALS_LINE_NO_ENUM_U8  MN_CALL_GetAlsLineInfo(VOS_VOID);


VOS_VOID  MN_CALL_UpdateAlsLineNbr(
    MN_CALL_ID_T                        callId,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLineNbr
);


VOS_UINT32 MN_CALL_UpdateAlsLineInfo(
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine,
    VOS_BOOL                            bUpdateNvim
);


extern MN_CALL_TYPE_ENUM_U8  MN_CALL_GetCallType(
    MN_CALL_ID_T                        callId
);


extern VOS_VOID  MN_CALL_UpdateRbId(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulRbId
);


extern VOS_UINT32 MN_CALL_GetRbId(MN_CALL_ID_T callId);


VOS_VOID MN_CALL_SetVideoCallChannelOpenFlg(
    VOS_BOOL                            bVideoCallChannelOpenFlg,
    MN_CALL_ID_T                        callId
);


VOS_BOOL MN_CALL_GetVideoCallChannelOpenFlg(
    MN_CALL_ID_T                        callId
);


VOS_UINT32 MN_CALL_ConCallMsgTypeToCcMsgType(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType,
    NAS_CC_MSG_TYPE_ENUM_U8             *penCcMsgType
);


VOS_UINT32 MN_CALL_ConCcMsgTypeToCallMsgType(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      *penCallMsgType
);


VOS_VOID MN_CALL_UpdateRptUus1Info(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser
);


VOS_VOID MN_CALL_ConCcUusInfoToCall(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);


VOS_UINT32  MN_CALL_ConCallUusInfoToCc(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
);

VOS_VOID NAS_CALL_SndOutsideContextData(VOS_VOID);

VOS_UINT32 NAS_CALL_RestoreContextData(struct MsgCB * pMsg);


VOS_VOID  MN_CALL_CallInfoReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);



VOS_VOID  MN_CALL_GetCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
);


VOS_VOID MN_CALL_RcvTafAgentGetCallInfo(VOS_VOID);


VOS_UINT32  MN_CALL_GetSpecificStatusCallInfo(
    MN_CALL_STATE_ENUM_U8                enCallStatus,
    MN_CALL_INFO_STRU                   *pstCallInfo
);



/* 移这部分函数到文件MnCallSendApp.c文件中 */


VOS_VOID  MN_CALL_CreateStkMoCallEntity(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkCallOrig);


VOS_VOID MN_CALL_UpdateSubAddress(
    VOS_UINT8                           ucCallId,
    MN_CALL_SUBADDR_STRU               *pstSubCallNumber
);


VOS_VOID MN_CALL_UpdateOpId(
    VOS_UINT8                           ucCallId,
    MN_OPERATION_ID_T                   opId
);


VOS_VOID MN_CALL_UpdateCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                            bReleaseFlag
);


VOS_VOID  MN_CALL_RecordCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        NAS_CC_MSG_SETUP_MT_STRU            *pstSetup);


VOS_VOID  MN_CALL_ReadCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        MN_CALL_CLPR_GET_CNF_STRU          *pstGetClprCnf);





VOS_UINT32 MN_CALL_AllowSupsOperation(VOS_VOID);



/*****************************************************************************
 函 数 名  : MN_CALL_GetNetDiscEventInfo
 功能描述  : 获取UE发起的DISCONNECT, RELEASE, RELEASE COMPLETE消息的CAUSE, CALLID和TI
 输入参数  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE消息
 输出参数  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent 呼叫释放事件结构
             VOS_UINT8                          *pucTi,     消息对应的呼叫TI
             VOS_UINT8                          *pucCallId  消息对应的CALL ID
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR     获取操作成功
                其他                获取操作失败

*****************************************************************************/
VOS_UINT32 MN_CALL_GetNetDiscEventInfo(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg,
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetUeDiscEventInfo
 功能描述  : 获取UE发起的DISCONNECT, RELEASE, RELEASE COMPLETE消息的CAUSE,CALLID和TI
 输入参数  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE消息
 输出参数  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent 呼叫释放事件结构
             VOS_UINT8                          *pucTi,     消息对应的呼叫TI
             VOS_UINT8                          *pucCallId  消息对应的CALL ID
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR     获取操作成功
                其他                获取操作失败

*****************************************************************************/
VOS_UINT32 MN_CALL_GetUeDiscEventInfo(
    const MNCC_REQ_PRIM_MSG_STRU       *pstMsg,
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
);

VOS_UINT32 MN_CALL_IsNeedCallRedial(
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);
VOS_UINT32 TAF_CALL_IsOrigNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsConfNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsConnNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsCendNeedRpt(VOS_VOID);


TAF_CS_CAUSE_ENUM_UINT32  MN_CALL_GetCsCause(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateDiscCallDir
 功能描述  : 更新CALL挂断的方向
 输入参数  : callId     - 呼叫ID
             ucIsUser   - 是否是用户发起的挂断
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_CALL_UpdateDiscCallDir(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucIsUser
);

VOS_VOID  MN_CALL_GetMgmtEntityInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_MGMT_STRU                   *pstMgmtEntity
);

VOS_UINT8 TAF_CALL_GetDisconnectFlg(
    MN_CALL_ID_T                        callId
);

VOS_VOID TAF_CALL_InitDtmfCtx(VOS_VOID);

VOS_VOID TAF_CALL_ResetDtmfCtx(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_CheckUserDtmfCallId(
    MN_CALL_ID_T                        CallId
);

TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_GetAllowedDtmfCallId(
    MN_CALL_ID_T                       *pCallId
);

TAF_CALL_DTMF_CTX_STRU* TAF_CALL_GetDtmfCtx(VOS_VOID);

TAF_CALL_DTMF_STATE_ENUM_UINT8 TAF_CALL_GetDtmfState(VOS_VOID);

VOS_VOID TAF_CALL_SetDtmfState(
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enState
);

VOS_UINT8 TAF_CALL_GetDtmfBufCnt(VOS_VOID);

HI_LIST_S* TAF_CALL_GetDtmfListHead(VOS_VOID);

TAF_CALL_DTMF_INFO_STRU* TAF_CALL_GetDtmfCurInfo(VOS_VOID);

/* 移这部分函数到文件MnCallSendApp.c文件中 */

TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_SaveDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
);

VOS_VOID TAF_CALL_DelDtmfNode(
    TAF_CALL_DTMF_NODE_STRU            *pstNode
);

VOS_VOID TAF_CALL_PreProcRelAllCall(VOS_VOID);

/* 移这部分函数到文件MnCallSendApp.c文件中 */

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_CreateCallEntitiesWithImsCallInfo(
    VOS_UINT8                           ucSrvccCallNum,
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstSrvccCallInfo,
    VOS_UINT8                           ucStartedHifiFlag
);

VOS_VOID TAF_CALL_ProcSrvccDtmfBuffInfo(TAF_CALL_DTMF_BUFF_STRU *pstDtmfBuffInfo);
#endif
MN_CALL_MGMT_STRU *TAF_CALL_GetCallEntityAddr(VOS_VOID);

VOS_UINT32 TAF_CALL_IsCallRedialCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_VOID MN_CALl_VoicePreferJudgeVoiceCallExist(VOS_VOID);
VOS_VOID MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_UINT32 ulVoiceFlag);
#endif

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

#endif /* MN_CALL_MGMT_H */

