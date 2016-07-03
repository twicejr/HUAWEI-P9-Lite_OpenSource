

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafSdcCtx.h"
#include "TafMmaSndMscc.h"
#include "MmaMsccInterface.h"
#include "MmaAppLocal.h"
#include "TafApsApi.h"
#include "TafLog.h"
#include "NasMntn.h"
#include "TafMmaCtx.h"
#include "TafMmaComFunc.h"

#include "TafAppMma.h"

#include "TafStdlib.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define THIS_FILE_ID  PS_FILE_ID_TAF_MMA_SND_MSCC_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_MMA_CS_PS_ERR_CODE_MAP_STRU         g_astTafMmaCsErrCodeMapTbl[] =
{
    {TAF_CS_CAUSE_XCALL_MAX_ACCESS_PROBES,                  NAS_MSCC_PIF_CDMA_CALL_CAUSE_MAX_ACCESS_PROBES},

    {TAF_CS_CAUSE_XCALL_REORDER,                            NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_NORMAL},

    {TAF_CS_CAUSE_XCALL_ACCESS_DENYIED,                     NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_DENYIED},

    {TAF_CS_CAUSE_XCALL_CHANNEL_ASSIGN_TIMEOUT,             NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_LOW_RSSI},

    {TAF_CS_CAUSE_XCALL_SIGNAL_FADE_IN_ACH,                 NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE},

    {TAF_CS_CAUSE_XCALL_SIGNAL_FADE_IN_TCH,                 NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE},

    {TAF_CS_CAUSE_XCALL_INTERNAL_NO_SERVICE,                NAS_MSCC_PIF_CDMA_CALL_CAUSE_INTERNAL_NO_SERVICE},

    {TAF_CS_CAUSE_XCALL_NO_SERVICE,                         NAS_MSCC_PIF_CDMA_CALL_CAUSE_INTERNAL_NO_SERVICE},
};

TAF_MMA_CS_PS_ERR_CODE_MAP_STRU         g_astTafMmaPsErrCodeMapTbl[] =
{
    {TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES,                 NAS_MSCC_PIF_CDMA_CALL_CAUSE_MAX_ACCESS_PROBES},

    {TAF_PS_CAUSE_XCC_AS_REORDER,                           NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_NORMAL},

    {TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED,                     NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_DENYIED},

    {TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT,            NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_LOW_RSSI},

    {TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH,                NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE},

    {TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH,                NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE},

    {TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES,                 NAS_MSCC_PIF_CDMA_CALL_CAUSE_MAX_ACCESS_PROBES},

    {TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE,                NAS_MSCC_PIF_CDMA_CALL_CAUSE_RTC_RTCACK_FAILURE},

    {TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY,                   NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_DENYIED},

    {TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE,                       NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE},

    {TAF_PS_CAUSE_1X_NO_SERVICE,                            NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE},

    {TAF_PS_CAUSE_HRPD_NO_SERVICE,                          NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE},
};
#endif

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 TAF_MMA_MapMmaRatToMsccRat(
    TAF_MMA_RAT_TYPE_ENUM_UINT8      enRatType
)
{
    switch (enRatType)
    {
        case TAF_MMA_RAT_GSM:
            return NAS_MSCC_PIF_NET_RAT_TYPE_GSM;

        case TAF_MMA_RAT_WCDMA:
            return NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA;

        case TAF_MMA_RAT_LTE:
            return NAS_MSCC_PIF_NET_RAT_TYPE_LTE;

        case TAF_MMA_RAT_1X:
            return NAS_MSCC_PIF_NET_RAT_TYPE_1X;

        case TAF_MMA_RAT_HRPD:
            return NAS_MSCC_PIF_NET_RAT_TYPE_HRPD;

        default:
            return VOS_RATMODE_BUTT;
    }

}



VOS_UINT32 TAF_MMA_SndMsccStartReq(
    TAF_MMA_RAT_ORDER_STRU                  *pstRatPrioList,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enUsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus,
    VOS_UINT8                                ucIsCardRefresh
)
{
    MMA_MSCC_START_REQ_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccStartReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_START_REQ;
    pstMsg->enRegDomain                = TAF_MMA_GetRegDomain();
    pstMsg->enUsimStatus               = enUsimStatus;
    pstMsg->enCsimStatus               = enCsimStatus;

    pstMsg->stRatPrio.ucRatNum         = pstRatPrioList->ucRatOrderNum;
    for (i = 0; i < TAF_SDC_MIN(pstMsg->stRatPrio.ucRatNum, NAS_MSCC_PIF_MAX_RAT_NUM); i++)
    {
        pstMsg->stRatPrio.aucRatPrio[i]   = TAF_MMA_MapMmaRatToMsccRat(pstRatPrioList->aenRatOrder[i]);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->enCallMode                 = (NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8)(TAF_SDC_GetCurCallMode());
#endif


    /* 开机请求适配新的接口，支持CDMA技术接口 */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())/* C+L模式 */
    {
        pstMsg->enRegCtrl                                        = NAS_MSCC_PIF_REG_CONTROL_BY_3GPP2_CBP;

        if (NAS_MSCC_PIF_MAX_RAT_NUM > pstMsg->stRatPrio.ucRatNum)
        {
            pstMsg->stRatPrio.aucRatPrio[pstMsg->stRatPrio.ucRatNum] = NAS_MSCC_PIF_NET_RAT_TYPE_HRPD;
            pstMsg->stRatPrio.ucRatNum++;
        }
    }
    else
    {
        pstMsg->enRegCtrl                   = NAS_MSCC_PIF_REG_CONTROL_BY_3GPP_MMC;
    }


    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT != enUsimStatus)
    {
        PS_MEM_CPY(pstMsg->aucImsi, TAF_SDC_GetSimImsi(), NAS_MAX_IMSI_LENGTH);
    }

    pstMsg->ucIsCardChanged = (VOS_UINT8)TAF_MMA_GetIccIdChangedFlg(ucIsCardRefresh, enCsimStatus);

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );


    NAS_TRACE_HIGH("Send Msg!");

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccSignalReportReq(
    VOS_UINT8                           ucActionType,
    VOS_UINT8                           ucRrcMsgType,
    VOS_UINT8                           ucSignThreshold,
    VOS_UINT8                           ucMinRptTimerInterval
)
{
    MMA_MSCC_SIGN_REPORT_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_SIGN_REPORT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccSignalReportReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_SIGN_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_SIGN_REPORT_REQ;
    pstMsg->ucActionType               = ucActionType;
    pstMsg->ucRrcMsgType               = ucRrcMsgType;
    pstMsg->ucSignThreshold            = ucSignThreshold;
    pstMsg->ucMinRptTimerInterval      = ucMinRptTimerInterval;


    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_VOID TAF_MMA_SndMsccModeChangeReq(
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32         enMsMode
)
{
    MMA_MSCC_MODE_CHANGE_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_MODE_CHANGE_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccModeChangeReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_MODE_CHANGE_REQ;
    pstMsg->enMsMode                   = enMsMode;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return;
}


VOS_UINT32 TAF_MMA_SndMsccAttachReq(
    VOS_UINT32                                              ulOpID,
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enAttachType,
    TAF_MMA_EPS_ATTACH_REASON_ENUM_UINT8                    enAttachReason
)
{
    MMA_MSCC_ATTACH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_ATTACH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccAttachReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_ATTACH_REQ;
    pstMsg->ulOpID                     = ulOpID;
    pstMsg->enAttachType               = enAttachType;
    pstMsg->enEpsAttachReason          = enAttachReason;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccDetachReq(
    VOS_UINT8                                  ucOpID,
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32       enDetachType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8            enDetachCause
)
{
    MMA_MSCC_DETACH_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_DETACH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccDetachReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_FALSE;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_DETACH_REQ;
    pstMsg->ulOpID                     = ucOpID;
    pstMsg->enDetachType               = enDetachType;

    pstMsg->enDetachReason             = enDetachCause;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_CSG)

VOS_UINT32 TAF_MMA_SndMsccCsgListSearchReq(VOS_VOID)
{
    MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccCsgListSearchReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_CSG_LIST_SEARCH_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccCsgListAbortReq(VOS_VOID)
{
    MMA_MSCC_CSG_LIST_ABORT_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CSG_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccCsgListAbortReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_CSG_LIST_ABORT_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}

#endif


VOS_UINT32 TAF_MMA_SndMsccPlmnListReq(VOS_VOID)
{
    MMA_MSCC_PLMN_LIST_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_PLMN_LIST_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPlmnListReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_PLMN_LIST_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccPlmnListAbortReq(VOS_VOID)
{
    MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPlmnListAbortReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_PLMN_LIST_ABORT_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccPlmnUserReselReq(NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32 enPlmnSelMode)
{
    MMA_MSCC_PLMN_USER_RESEL_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_PLMN_USER_RESEL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPlmnUserReselReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_PLMN_USER_RESEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_PLMN_USER_RESEL_REQ;
    pstMsg->enPlmnSelMode              = enPlmnSelMode;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccPlmnSpecialReq(
    MMA_MSCC_PLMN_ID_STRU               *pstPlmnId,
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8     enAccessMode
)
{
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMA_MSCC_PLMN_SPECIAL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPlmnSpecialReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_PLMN_SPECIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_PLMN_SPECIAL_REQ;
    pstMsg->stPlmnId                   = *pstPlmnId;
    pstMsg->enAccessMode               = enAccessMode;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_VOID TAF_MMA_SndMsccPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 enCause
)
{
    MMA_MSCC_POWER_OFF_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPowerOffReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_POWER_OFF_REQ;
    pstMsg->enCause                    = enCause;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );


    NAS_TRACE_HIGH("Send Msg!");

    return;
}



VOS_VOID  TAF_MMA_SndMsccSysCfgReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pSysCfgReq,
    VOS_UINT8                           ucOnlyRoamParaChanged,
    VOS_UINT8                           ucIsNeedAttachPs
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pMsg = VOS_NULL_PTR;
    TAF_MMA_USER_BAND_SET_UN            uUserSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeBand;   /* UE支持的用户设置的频段 */
    VOS_UINT32                          ulBand;
    VOS_UINT32                          i;


    /* 申请消息内存 */
    pMsg = (MMA_MSCC_SYS_CFG_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(MMA_MSCC_SYS_CFG_SET_REQ_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        /* 内存申请失败                             */
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccSysCfgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = WUEPS_PID_MMA;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = UEPS_PID_MSCC;
    pMsg->MsgHeader.ulMsgName           = ID_MMA_MSCC_SYS_CFG_SET_REQ;

    pMsg->ucOnlyRoamParaChanged         = VOS_FALSE;

    pMsg->ucIsNeedAttachPs = VOS_FALSE;

    /*漫游参数填写*/
    pMsg->enRoamCapability = pSysCfgReq->enRoam;

    /*接入模式pMsg->stRatPrioList参数填写*/


#if (FEATURE_ON == FEATURE_LTE)
    if (pSysCfgReq->stRatOrder.ucRatOrderNum > TAF_PH_MAX_GUL_RAT_NUM)
    {
        pSysCfgReq->stRatOrder.ucRatOrderNum = TAF_PH_MAX_GUL_RAT_NUM;
    }
#else
    if (pSysCfgReq->stRatOrder.ucRatOrderNum > TAF_PH_MAX_GU_RAT_NUM)
    {
        pSysCfgReq->stRatOrder.ucRatOrderNum = TAF_PH_MAX_GU_RAT_NUM;
    }
#endif

    /* 如果UE不支持GSM，当设置包含G模去掉G模 */
    if (VOS_TRUE == MMA_IsGsmForbidden())
    {
        pMsg->stRatPrioList.ucRatNum = 0;
        for ( i = 0 ; i < pSysCfgReq->stRatOrder.ucRatOrderNum; i++ )
        {
            if ( TAF_MMA_RAT_GSM == pSysCfgReq->stRatOrder.aenRatOrder[i])
            {
                continue;
            }
            pMsg->stRatPrioList.aucRatPrio[pMsg->stRatPrioList.ucRatNum] = pSysCfgReq->stRatOrder.aenRatOrder[i];
            pMsg->stRatPrioList.ucRatNum++;
        }
    }
    else
    {
        PS_MEM_CPY(&(pMsg->stRatPrioList), &(pSysCfgReq->stRatOrder), sizeof(TAF_MMA_RAT_ORDER_STRU));
    }

    /* GU频带设置参数填写*/
    /*将pSysCfgReq->stGuBand 从64位转换为32位*/
    MN_MMA_Convert64BitBandTo32Bit(&pSysCfgReq->stGuBand, &ulBand);
    MN_MMA_ConvertGUFrequencyBand(&ulBand);
    uUserSetBand.ulPrefBand         = ulBand;

    MMA_SwitchUserSetBand2UESupportBand(uUserSetBand, &stUeBand);
    pMsg->stBand.unGsmBand.ulBand   = stUeBand.unGsmBand.ulBand;
    pMsg->stBand.unWcdmaBand.ulBand = stUeBand.unWcdmaBand.ulBand;

    /* 目前system configure命令不支持cdma band设置，暂设置为所有band全支持 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pMsg->stBand.unCdmaBand.ulCdmaBand = 0x00000003;
#endif

    /* L频段设置参数填写 */
    pMsg->stBand.stLteBand.aulLteBand[0] = pSysCfgReq->stLBand.ulBandLow;
    pMsg->stBand.stLteBand.aulLteBand[1] = pSysCfgReq->stLBand.ulBandHigh;


    pMsg->ucOnlyRoamParaChanged = ucOnlyRoamParaChanged;

    pMsg->ucIsNeedAttachPs = ucIsNeedAttachPs;

    /*消息发送*/
    PS_SEND_MSG( WUEPS_PID_MMA, pMsg);

    return;
}




VOS_VOID TAF_MMA_SndMsccNetScanMsgReq(
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    MMA_MSCC_NET_SCAN_REQ_STRU          *pstMsg              = VOS_NULL_PTR;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU    stUeBand;                               /* UE支持的用户设置的频段 */
    VOS_UINT32                           ulBand;
    TAF_MMA_USER_BAND_SET_UN             uUserSetBand;

    /* 申请消息内存 */
    pstMsg = (MMA_MSCC_NET_SCAN_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(MMA_MSCC_NET_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndNetScanMsgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(MMA_MSCC_NET_SCAN_REQ_STRU));

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMA_MSCC_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = ID_MMA_MSCC_NET_SCAN_REQ;

    /* GU频带设置参数填写 */
    /* 将pstNetScanReq->stGuBand 从64位转换为32位 */
    MN_MMA_Convert64BitBandTo32Bit(&pstNetScanReq->stBand, &ulBand);
    MN_MMA_ConvertGUFrequencyBand(&ulBand);
    uUserSetBand.ulPrefBand             = ulBand;

    MMA_SwitchUserSetBand2UESupportBand(uUserSetBand, &stUeBand);

    pstMsg->stBand.unGsmBand.ulBand     = stUeBand.unGsmBand.ulBand;
    pstMsg->stBand.unWcdmaBand.ulBand   = stUeBand.unWcdmaBand.ulBand;
    pstMsg->sCellPow                    = pstNetScanReq->sCellPow;
    pstMsg->usCellNum                   = pstNetScanReq->usCellNum;
    pstMsg->ucRat                       = pstNetScanReq->enRat;

    /*消息发送*/
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_SndMsccAbortNetScanMsgReq(VOS_VOID)
{
    MMA_MSCC_ABORT_NET_SCAN_REQ_STRU    *pstMsg              = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstMsg = (MMA_MSCC_ABORT_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(MMA_MSCC_ABORT_NET_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccAbortNetScanMsgReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(MMA_MSCC_ABORT_NET_SCAN_REQ_STRU));

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMA_MSCC_ABORT_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = ID_MMA_MSCC_ABORT_NET_SCAN_REQ;

    /*消息发送*/
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_VOID TAF_MMA_SndMsccSystemAcquireReq(VOS_VOID)
{
    MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio = VOS_NULL_PTR;
    VOS_UINT32                          ulIsGeoValid;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsGeoCdmaValid;

    ulIsGeoCdmaValid = TAF_MMA_IsGeoCdmaLocValid();
#endif
    pstGetGeoCtx   = TAF_MMA_GetGeoCtxAddr();
    pstRatPrio     = TAF_SDC_GetMsPrioRatList();
    ulIsGeoValid   = TAF_MMA_IsGeoValid();

    /* 申请内存  */
    pstMsg = (MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccSystemAcquireReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_SYSTEM_ACQUIRE_REQ;

    pstMsg->enAcqReason                = NAS_MSCC_PIF_ACQ_REASON_POWER_UP;
    pstMsg->stInitAcqPlmnInfo.enRat    = pstRatPrio->aenRatPrio[0];

    if (VOS_TRUE == ulIsGeoValid)
    {
        pstMsg->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMcc = pstGetGeoCtx->stGeoPlmnId.ulMcc;
        pstMsg->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMnc = pstGetGeoCtx->stGeoPlmnId.ulMnc;
    }
    else
    {
        pstMsg->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
        pstMsg->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == ulIsGeoCdmaValid)
    {
        pstMsg->stCdmaInitLocInfo.ulMcc = TAF_STD_TransformDeciDigitToBcdMcc(pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc);
        pstMsg->stCdmaInitLocInfo.lSid  = pstGetGeoCtx->stGeoCdmaLocInfo.lSid;
        pstMsg->stCdmaInitLocInfo.lNid  = pstGetGeoCtx->stGeoCdmaLocInfo.lNid;
    }
    else
#endif
    {
        pstMsg->stCdmaInitLocInfo.ulMcc = TAF_SDC_INVALID_MCC;
        pstMsg->stCdmaInitLocInfo.lSid  = MMA_INVALID_SID;
        pstMsg->stCdmaInitLocInfo.lNid  = MMA_INVALID_NID;
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return;
}


VOS_UINT32 TAF_MMA_SndMsccSpecPlmnSearchAbortReq(VOS_VOID)
{
    MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU                 *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccSpecPlmnSearchAbortReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


VOS_VOID TAF_MMA_SndMsccOmMaintainInfoInd(
    VOS_UINT8                           ucOmConnectFlg,
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_OM_MAINTAIN_INFO_IND;
    pstMsg->ucOmConnectFlg             = ucOmConnectFlg;
    pstMsg->ucOmPcRecurEnableFlg       = ucOmPcRecurEnableFlg;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return;
}



VOS_UINT32 TAF_MMA_SndMsccUpdateUplmnNtf( VOS_VOID )
{
    MMA_MSCC_UPDATE_UPLMN_NTF_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_UPDATE_UPLMN_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccUpdateUplmnNtf:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulLength         = sizeof(MMA_MSCC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MMA_MSCC_UPDATE_UPLMN_NTF;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}


#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_UINT32 TAF_MMA_SndMsccOtherModemInfoNotify(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstMmaSndMsccMsg = VOS_NULL_PTR;
    MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstMtcMmaOtherModemInfo = VOS_NULL_PTR;

    pstMtcMmaOtherModemInfo = (MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU *)pstMsg;

    /* 申请内存  */
    pstMmaSndMsccMsg = (MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMmaSndMsccMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccOtherModemInfoNotify:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMmaSndMsccMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMmaSndMsccMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMmaSndMsccMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmaSndMsccMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_OTHER_MODEM_INFO_NOTIFY;
    pstMmaSndMsccMsg->bitOpCurrCampPlmnId        = pstMtcMmaOtherModemInfo->bitOpCurrCampPlmnId;
    pstMmaSndMsccMsg->stCurrCampPlmnId.ulMcc     = pstMtcMmaOtherModemInfo->stCurrCampPlmnId.ulMcc;
    pstMmaSndMsccMsg->stCurrCampPlmnId.ulMnc     = pstMtcMmaOtherModemInfo->stCurrCampPlmnId.ulMnc;

    pstMmaSndMsccMsg->bitOpEplmnInfo             = pstMtcMmaOtherModemInfo->bitOpEplmnInfo;
    pstMmaSndMsccMsg->stEplmnInfo.ucEquPlmnNum   = pstMtcMmaOtherModemInfo->stEplmnInfo.ucEquPlmnNum;
    PS_MEM_CPY(pstMmaSndMsccMsg->stEplmnInfo.astEquPlmnAddr, pstMtcMmaOtherModemInfo->stEplmnInfo.astEquPlmnAddr,
               sizeof(pstMmaSndMsccMsg->stEplmnInfo.astEquPlmnAddr));


    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMmaSndMsccMsg );

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccOtherModemDplmnNplmnInfoNotify(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       *pstMmaSndMsccMsg = VOS_NULL_PTR;
    MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       *pstMtcMmaOtherModemDplmnNplmnInfo = VOS_NULL_PTR;

    pstMtcMmaOtherModemDplmnNplmnInfo = (MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)pstMsg;

    /* 申请内存  */
    pstMmaSndMsccMsg = (MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMmaSndMsccMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccOtherModemDplmnNplmnInfoNotify:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMmaSndMsccMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMmaSndMsccMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMmaSndMsccMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmaSndMsccMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY;

    pstMmaSndMsccMsg->ucEHplmnNum = pstMtcMmaOtherModemDplmnNplmnInfo->ucEHplmnNum;

    PS_MEM_CPY(pstMmaSndMsccMsg->aucEHplmnList,
        pstMtcMmaOtherModemDplmnNplmnInfo->aucEHplmnList, NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM);

    PS_MEM_CPY(&(pstMmaSndMsccMsg->stSelfLearnDplmnNplmnInfo),
        &(pstMtcMmaOtherModemDplmnNplmnInfo->stSelfLearnDplmnNplmnInfo), sizeof(pstMmaSndMsccMsg->stSelfLearnDplmnNplmnInfo));

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMmaSndMsccMsg );

    return VOS_OK;
}



VOS_UINT32 TAF_MMA_SndMsccNcellInfoInd(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU    *pstMmaSndMsccMsg = VOS_NULL_PTR;
    MTC_MMA_NCELL_INFO_IND_STRU        *pstMtcMmaNcellInfo = VOS_NULL_PTR;

    pstMtcMmaNcellInfo = (MTC_MMA_NCELL_INFO_IND_STRU *)pstMsg;

    /* 申请内存  */
    pstMmaSndMsccMsg = (MMA_MSCC_NCELL_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMmaSndMsccMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccNcellInfoInd:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMmaSndMsccMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMmaSndMsccMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMmaSndMsccMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_NCELL_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmaSndMsccMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_NCELL_INFO_NOTIFY;

    pstMmaSndMsccMsg->stTdsNcellInfo.ucTdsArfcnNum = pstMtcMmaNcellInfo->stTdsNcellInfo.ucTdsArfcnNum;
    PS_MEM_CPY(pstMmaSndMsccMsg->stTdsNcellInfo.ausTdsArfcnList, pstMtcMmaNcellInfo->stTdsNcellInfo.ausTdsArfcnList,
               sizeof(pstMmaSndMsccMsg->stTdsNcellInfo.ausTdsArfcnList));

    pstMmaSndMsccMsg->stLteNcellInfo.ucLteArfcnNum = pstMtcMmaNcellInfo->stLteNcellInfo.ucLteArfcnNum;
    PS_MEM_CPY(pstMmaSndMsccMsg->stLteNcellInfo.aulLteArfcnList, pstMtcMmaNcellInfo->stLteNcellInfo.aulLteArfcnList,
               sizeof(pstMmaSndMsccMsg->stLteNcellInfo.aulLteArfcnList));

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMmaSndMsccMsg );

    return VOS_OK;
}

VOS_UINT32 TAF_MMA_SndMsccPsTransferNotify(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU   *pstMmaSndMsccMsg = VOS_NULL_PTR;
    MTC_MMA_PS_TRANSFER_IND_STRU       *pstMtcMmaPsTransferInd = VOS_NULL_PTR;

    pstMtcMmaPsTransferInd = (MTC_MMA_PS_TRANSFER_IND_STRU *)pstMsg;

    /* 申请内存  */
    pstMmaSndMsccMsg = (MMA_MSCC_PS_TRANSFER_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMmaSndMsccMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPsTransferInd:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMmaSndMsccMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMmaSndMsccMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMmaSndMsccMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMmaSndMsccMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_PS_TRANSFER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmaSndMsccMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_PS_TRANSFER_NOTIFY;
    pstMmaSndMsccMsg->enSolutionCfg                = pstMtcMmaPsTransferInd->enSolutionCfg;
    pstMmaSndMsccMsg->ucCause                      = pstMtcMmaPsTransferInd->ucCause;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMmaSndMsccMsg );

    return VOS_OK;
}

#endif


VOS_VOID TAF_MMA_SndMsccEOPlmnSetReq(
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnSetPara
)
{
    MMA_MSCC_EOPLMN_SET_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存 */
    pstMsg = (MMA_MSCC_EOPLMN_SET_REQ_STRU*)PS_ALLOC_MSG(
                                         WUEPS_PID_MMA,
                                         sizeof(MMA_MSCC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccEOPlmnSetReq():ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulMsgName         = ID_MMA_MSCC_EOPLMN_SET_REQ;
    pstMsg->MsgHeader.ulLength          = sizeof(MMA_MSCC_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息内容 */
    pstMsg->ucIndex      = pstEOPlmnSetPara->ucIndex;
    pstMsg->ucOPlmnCount = pstEOPlmnSetPara->ucOPlmnCount;

    PS_MEM_CPY((VOS_INT8*)pstMsg->aucVersion,
                    pstEOPlmnSetPara->aucVersion,
                    TAF_MAX_USER_CFG_OPLMN_VERSION_LEN * sizeof(TAF_UINT8));

    PS_MEM_CPY((VOS_INT8*)pstMsg->aucOPlmnWithRat,
                    pstEOPlmnSetPara->aucOPlmnWithRat,
                    TAF_MAX_GROUP_CFG_OPLMN_DATA_LEN * sizeof(TAF_UINT8));

    /*消息发送*/
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_UINT32 TAF_MMA_SndMsccAcqReq(
    TAF_MMA_ACQ_PARA_STRU              *pstMmaAcqPara
)
{
    MMA_MSCC_ACQ_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_ACQ_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccAcqReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_ACQ_REQ;

    if (TAF_MMA_ACQ_REASON_POWER_UP == pstMmaAcqPara->enAcqReason)
    {
        pstMsg->enAcqReason = NAS_MSCC_PIF_ACQ_REASON_POWER_UP;
    }
    else if (TAF_MMA_ACQ_REASON_HIGH_PRIO == pstMmaAcqPara->enAcqReason)
    {
        pstMsg->enAcqReason = NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY;
    }
    else
    {
        pstMsg->enAcqReason = NAS_MSCC_PIF_ACQ_REASON_OTHER;
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccRegReq(
    TAF_MMA_REG_PARA_STRU              *pstMmaRegPara
)
{
    VOS_UINT32                          i;
    MMA_MSCC_REG_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_REG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccRegReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_REG_REQ;
    pstMsg->bitOpPrioClass               = pstMmaRegPara->bitOpPrioClass;
    pstMsg->bitOpCellInfo                = pstMmaRegPara->bitOpCellInfo;
    pstMsg->bitSpare                     = pstMmaRegPara->bitSpare;
    pstMsg->enPrioClass                  = pstMmaRegPara->enPrioClass;

    if (VOS_TRUE == pstMmaRegPara->bitOpCellInfo)
    {
        /* 目前只支持到CDMA到LTE的重选，接入技术固定填写为LTE */
        pstMsg->stCellInfo.ucRat   = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;
        pstMsg->stCellInfo.ulArfcn = pstMmaRegPara->stCellInfo.ulArfcn;

        pstMsg->stCellInfo.ucCellNum = TAF_SDC_MIN(pstMmaRegPara->stCellInfo.ucCellNum, NAS_MSCC_PIF_REG_MAX_CELL_NUM);
        PS_MEM_CPY(pstMsg->stCellInfo.ausCellId, pstMmaRegPara->stCellInfo.ausCellId,
                   pstMsg->stCellInfo.ucCellNum*sizeof(VOS_UINT16));

        pstMsg->stCellInfo.ucPlmnNum = TAF_SDC_MIN(pstMmaRegPara->stCellInfo.ucPlmnNum, NAS_MSCC_PIF_REG_MAX_PLMN_NUM);
        for (i = 0; i < pstMsg->stCellInfo.ucPlmnNum; i++)
        {
            pstMsg->stCellInfo.astPlmnId[i].ulMcc = pstMmaRegPara->stCellInfo.astPlmnId[i].Mcc;
            pstMsg->stCellInfo.astPlmnId[i].ulMnc = pstMmaRegPara->stCellInfo.astPlmnId[i].Mnc;
        }
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_SndMsccPowerSaveReq(
    TAF_MMA_POWER_SAVE_PARA_STRU       *pstMmaPowerSavePara
)
{
    MMA_MSCC_POWER_SAVE_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_POWER_SAVE_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPowerSaveReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_POWER_SAVE_REQ;

    pstMsg->enPowerSaveReason            = NAS_MSCC_PIF_POWER_SAVE_TYPE_UNKNOWN;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return VOS_OK;
}




VOS_VOID TAF_MMA_SndMsccSrvAcqReq(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType,
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList
)
{
    MMA_MSCC_SRV_ACQ_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_SRV_ACQ_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccSrvAcqReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_SRV_ACQ_REQ;
    pstMsg->enSrvType                    = enSrvType;

    PS_MEM_CPY(&(pstMsg->stRatList), pstRatList, sizeof(NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_SndMsccBeginSessionNotify(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8         enSrvType,
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU      *pstRatList
)
{
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccBeginSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_BEGIN_SESSION_NOTIFY;

    pstMsg->enSrvType                    = enSrvType;

    PS_MEM_CPY(&(pstMsg->stRatList), pstRatList, sizeof(NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_SndMsccEndSessionNotify(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8         enSrvType,
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU      *pstRatList
)
{
    MMA_MSCC_END_SESSION_NOTIFY_STRU                       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccEndSessionNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_END_SESSION_NOTIFY;

    pstMsg->enSrvType                    = enSrvType;

    PS_MEM_CPY(&(pstMsg->stRatList), pstRatList, sizeof(NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}




VOS_VOID TAF_MMA_SndMsccImsSrvInfoNotify(
    VOS_UINT8                           ucImsCallFlg
)
{
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccImsSrvInfoNotify:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY;
    pstMsg->ucImsCallFlg                 = ucImsCallFlg;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return;
}



NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8 TAF_MMA_MapMmaCallTypeToMsccFormat(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enMmaCallType
)
{
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8        enMsccCallType;

    switch (enMmaCallType)
    {
        case TAF_MMA_1X_EMERGENCY_VOICE_CALL:
            enMsccCallType = NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL;
            break;

        case TAF_MMA_1X_NORMAL_VOICE_CALL:
            enMsccCallType = NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL;
            break;

        case TAF_MMA_1X_NORMAL_DATA_CALL:
            enMsccCallType = NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL;
            break;

        case TAF_MMA_DO_NORMAL_DATA_CALL:
            enMsccCallType = NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL;
            break;

        default:
            enMsccCallType = NAS_MSCC_PIF_CDMA_CALL_TYPE_BUTT;
            break;
    }

    return enMsccCallType;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8 TAF_MMA_MapCsCauseToMsccFormat(
    VOS_UINT32                          ulCause
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astTafMmaCsErrCodeMapTbl)/sizeof(TAF_MMA_CS_PS_ERR_CODE_MAP_STRU)); ulCnt++)
    {
        if (g_astTafMmaCsErrCodeMapTbl[ulCnt].ulCsPsCause == ulCause)
        {
            return g_astTafMmaCsErrCodeMapTbl[ulCnt].enMsccCause;
        }
    }

    return NAS_MSCC_PIF_CDMA_CALL_CAUSE_BUTT;
}


NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8 TAF_MMA_MapPsCauseToMsccFormat(
    VOS_UINT32                          ulCause
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astTafMmaPsErrCodeMapTbl)/sizeof(TAF_MMA_CS_PS_ERR_CODE_MAP_STRU)); ulCnt++)
    {
        if (g_astTafMmaPsErrCodeMapTbl[ulCnt].ulCsPsCause == ulCause)
        {
            return g_astTafMmaPsErrCodeMapTbl[ulCnt].enMsccCause;
        }
    }

    return NAS_MSCC_PIF_CDMA_CALL_CAUSE_BUTT;
}


VOS_VOID TAF_MMA_SndMsccCdmaMoCallStartNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
)
{
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CDMA_MO_CALL_START_NTF;
    pstMsg->enCallType                   = TAF_MMA_MapMmaCallTypeToMsccFormat(enCallType);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_SndMsccQuitCallBackNtf( VOS_VOID )
{
    MMA_MSCC_QUIT_CALL_BACK_NTF_STRU   *pstSndMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstSndMsg = (MMA_MSCC_QUIT_CALL_BACK_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_QUIT_CALL_BACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH);


    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvQuitCallBackReq_PreProc:ERROR: Memory Alloc Error for pMsg");

        return;
    }
    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_QUIT_CALL_BACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstSndMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_QUIT_CALL_BACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_QUIT_CALL_BACK_NTF;

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstSndMsg );

    return;
}


VOS_VOID TAF_MMA_SndMsccCdmaMoCallEndNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
)
{
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CDMA_MO_CALL_END_NTF;
    pstMsg->enCallType                   = TAF_MMA_MapMmaCallTypeToMsccFormat(enCallType);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_VOID TAF_MMA_SndMsccCdmaMoCallSuccessNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
)
{
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU     *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF;
    pstMsg->enCallType                   = TAF_MMA_MapMmaCallTypeToMsccFormat(enCallType);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}




VOS_VOID TAF_MMA_SndMsccCdmaMoCallRedialSysAcqNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType,
    VOS_UINT32                          ulCause
)
{
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU        *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF;
    pstMsg->enCallType                   = TAF_MMA_MapMmaCallTypeToMsccFormat(enCallType);

    if  ((NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstMsg->enCallType)
      || (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL == pstMsg->enCallType))
    {
        pstMsg->enCause          = TAF_MMA_MapPsCauseToMsccFormat(ulCause);
    }
    else
    {
        pstMsg->enCause          = TAF_MMA_MapCsCauseToMsccFormat(ulCause);
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_VOID TAF_MMA_SndMsccCFreqLockNtf(
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU *pstCFreqLockSetPara
)
{
    MMA_MSCC_CFREQ_LOCK_NTF_STRU        *pstMmaMscCFreqLockNtf = VOS_NULL_PTR;

    pstMmaMscCFreqLockNtf =
            (MMA_MSCC_CFREQ_LOCK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(MMA_MSCC_CFREQ_LOCK_NTF_STRU));

    if (VOS_NULL_PTR == pstMmaMscCFreqLockNtf)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMmaMscCFreqLockNtf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MSCC_CFREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstMmaMscCFreqLockNtf->stMsgHeader.ulReceiverPid = UEPS_PID_MSCC;
    pstMmaMscCFreqLockNtf->stMsgHeader.ulMsgName     = ID_MMA_MSCC_CFREQ_LOCK_NTF;

    /* 填写消息信息 */
    pstMmaMscCFreqLockNtf->enFreqLockMode            = pstCFreqLockSetPara->enFreqLockMode;
    if (TAF_MMA_CFREQ_LOCK_MODE_ON == pstMmaMscCFreqLockNtf->enFreqLockMode)
    {
        pstMmaMscCFreqLockNtf->usSid           = pstCFreqLockSetPara->usSid;
        pstMmaMscCFreqLockNtf->usNid           = pstCFreqLockSetPara->usNid;
        pstMmaMscCFreqLockNtf->usCdmaBandClass = pstCFreqLockSetPara->usCdmaBandClass;
        pstMmaMscCFreqLockNtf->usCdmaFreq      = pstCFreqLockSetPara->usCdmaFreq;
        pstMmaMscCFreqLockNtf->usCdmaPn        = pstCFreqLockSetPara->usCdmaPn;
        pstMmaMscCFreqLockNtf->usHrpdBandClass = pstCFreqLockSetPara->usEvdoBandClass;
        pstMmaMscCFreqLockNtf->usHrpdFreq      = pstCFreqLockSetPara->usEvdoFreq;
        pstMmaMscCFreqLockNtf->usHrpdPn        = pstCFreqLockSetPara->usEvdoPn;
    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMmaMscCFreqLockNtf);

    return;
}


VOS_UINT32 TAF_MMA_SndMsccCdmaCsqSetReq(
    NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU     stCdmaCsqSetPara
)
{
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_CDMACSQ_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_CDMACSQ_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccCdmaCsqSetReq:ERROR: Memory Alloc Error for pMsg");

        return VOS_FALSE;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CDMACSQ_SET_REQ;
    PS_MEM_CPY(&pstMsg->stCdmaCsq, &stCdmaCsqSetPara, sizeof(NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return VOS_TRUE;

}


VOS_UINT32 TAF_MMA_SndMsccHandsetInfoQryReq(
     MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32  enInfoType
)
{
    MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU *pstMsg = VOS_NULL_PTR;


    /* 申请内存  */
    pstMsg = (MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccHandsetInfoQryReq:ERROR: Memory Alloc Error for pMsg");

        return VOS_FALSE;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_HANDSET_INFO_QRY_REQ;
    pstMsg->enInfoType                   = enInfoType;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return VOS_TRUE;

}




VOS_UINT32 TAF_MMA_SndMsccHdrCsqSetReq(
    NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU     stHdrCsqSetPara
)
{
    MMA_MSCC_HDR_CSQ_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_HDR_CSQ_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_HDR_CSQ_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccCdmaCsqSetReq:ERROR: Memory Alloc Error for pMsg");

        return VOS_FALSE;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_HDR_CSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_HDR_CSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_HDR_CSQ_SET_REQ;
    PS_MEM_CPY(&pstMsg->stHdrCsq, &stHdrCsqSetPara, sizeof(NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return VOS_TRUE;

}


#endif


VOS_VOID TAF_MMA_SndMsccCFPlmnSetReq(
    TAF_PH_FPLMN_OPERATE_STRU          *pstFPlmnOperInfo
)
{
    MMA_MSCC_CFPLMN_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMA_MSCC_CFPLMN_SET_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                                             sizeof(MMA_MSCC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccCFPlmnSetReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MMA_MSCC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CFPLMN_SET_REQ;

    if (TAF_PH_FPLMN_DEL_ALL == pstFPlmnOperInfo->ulCmdType)
    {
        pstMsg->enCmdType = NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ALL;
    }
    else if (TAF_PH_FPLMN_DEL_ONE == pstFPlmnOperInfo->ulCmdType)
    {
        pstMsg->enCmdType = NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ONE;
    }
    else if (TAF_PH_FPLMN_ADD_ONE == pstFPlmnOperInfo->ulCmdType)
    {
        pstMsg->enCmdType = NAS_MSCC_PIF_CFPLMN_TYPE_ADD_ONE;
    }
    else
    {
        pstMsg->enCmdType = NAS_MSCC_PIF_CFPLMN_TYPE_BUTT;
    }

    if ((TAF_PH_FPLMN_DEL_ONE == pstFPlmnOperInfo->ulCmdType)
     || (TAF_PH_FPLMN_ADD_ONE == pstFPlmnOperInfo->ulCmdType))
    {
        pstMsg->stPlmnInfo.ulMcc = pstFPlmnOperInfo->stPlmn.Mcc;
        pstMsg->stPlmnInfo.ulMnc = pstFPlmnOperInfo->stPlmn.Mnc;
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    return;
}


VOS_VOID TAF_MMA_SndMsccCFPlmnQueryReq(VOS_VOID)
{
    MMA_MSCC_CFPLMN_QUERY_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMA_MSCC_CFPLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                                               sizeof(MMA_MSCC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccCFPlmnQueryReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MMA_MSCC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_CFPLMN_QUERY_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    return;
}


VOS_VOID TAF_MMA_SndMsccDplmnSetReq(
    TAF_MMA_DPLMN_SET_REQ_STRU         *pstMsg
)
{
    MMA_MSCC_DPLMN_SET_REQ_STRU        *pstSndMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstSndMsg = (MMA_MSCC_DPLMN_SET_REQ_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(MMA_MSCC_DPLMN_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
       TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccDplmnSetReq:ERROR: Memory Alloc Error for pMsg");
       return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstSndMsg);

    /* 填写消息头 */
    TAF_MMA_CFG_MSG_HDR(pstSndMsg, UEPS_PID_MSCC, ID_MMA_MSCC_DPLMN_SET_REQ);

    /* 填写消息内容 */
    pstSndMsg->ucSeq                    = pstMsg->ucSeq;

    pstSndMsg->enApPresetDplmnScene     = TAF_MMA_GetDplmnUpdateScene();

    PS_MEM_CPY(pstSndMsg->aucVersionId, pstMsg->aucVersionId, TAF_MMA_VERSION_INFO_LEN);
    PS_MEM_CPY(&(pstSndMsg->stCtrl), &(pstMsg->stCtrl), sizeof(pstMsg->stCtrl));
    pstSndMsg->stDplmnInfo.ucEhPlmnNum  = pstMsg->stDplmnInfo.ucEhPlmnNum;
    pstSndMsg->stDplmnInfo.usDplmnNum   = pstMsg->stDplmnInfo.usDplmnNum;
    PS_MEM_CPY(pstSndMsg->stDplmnInfo.astEhPlmnInfo,
               pstMsg->stDplmnInfo.astEhPlmnInfo,
               pstMsg->stDplmnInfo.ucEhPlmnNum * sizeof(TAF_PLMN_ID_STRU));
    PS_MEM_CPY(pstSndMsg->stDplmnInfo.astDplmnList,
               pstMsg->stDplmnInfo.astDplmnList,
               pstMsg->stDplmnInfo.usDplmnNum * sizeof(TAF_MMA_SIM_PLMN_WITH_RAT_STRU));

    /* 发送消息 */
    TAF_MMA_SEND_MSG(pstSndMsg);

    return;
}



VOS_VOID TAF_MMA_SndMsccPrefPlmnSetReq(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt
)
{
    MMA_MSCC_PREF_PLMN_SET_REQ_STRU    *pstMmaMsccPrefPlmnSetReq = VOS_NULL_PTR;

    pstMmaMsccPrefPlmnSetReq = (MMA_MSCC_PREF_PLMN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                  sizeof(MMA_MSCC_PREF_PLMN_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMmaMsccPrefPlmnSetReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPrefPlmnSetReq ERROR: Memory Alloc Error for pstMmaMsccPrefPlmnSetReq");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMmaMsccPrefPlmnSetReq + VOS_MSG_HEAD_LENGTH),
                0x00,
               (sizeof(MMA_MSCC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstMmaMsccPrefPlmnSetReq->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMmaMsccPrefPlmnSetReq->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMmaMsccPrefPlmnSetReq->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMmaMsccPrefPlmnSetReq->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMmaMsccPrefPlmnSetReq->stMsgHeader.ulLength         = sizeof(MMA_MSCC_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmaMsccPrefPlmnSetReq->stMsgHeader.ulMsgName        = ID_MMA_MSCC_PREF_PLMN_SET_REQ;

    /* 填写消息信息 */
    pstMmaMsccPrefPlmnSetReq->enPrefPlmnParaType           = (NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8)TAF_MMA_GetPrefPlmnParaType(pstPrefPlmnOpt->enPrefPLMNType);

    PS_MEM_CPY(&(pstMmaMsccPrefPlmnSetReq->stCtrl),
               pstCtrl,
               sizeof(TAF_MMA_CTRL_STRU));

    PS_MEM_CPY(&(pstMmaMsccPrefPlmnSetReq->stPrefPlmnOpt),
               pstPrefPlmnOpt,
               sizeof(TAF_PH_PREF_PLMN_OPERATE_STRU));


    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMmaMsccPrefPlmnSetReq);

    return;
}


VOS_VOID TAF_MMA_SndMsccPrefPlmnQueryReq(
    TAF_MMA_PREF_PLMN_QUERY_REQ_STRU   *pstRcvMsg
)
{
    MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstPrefPlmnQueryReq    = VOS_NULL_PTR;

    pstPrefPlmnQueryReq = (MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU));
    if (VOS_NULL_PTR == pstPrefPlmnQueryReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvMmaPrefPlmnQueryReq_PreProc: ERROR:ALLOC MEMORY FAIL.");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPrefPlmnQueryReq + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstPrefPlmnQueryReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryReq->stMsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstPrefPlmnQueryReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryReq->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPrefPlmnQueryReq->stMsgHeader.ulLength          = sizeof(MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnQueryReq->stMsgHeader.ulMsgName         = ID_MMA_MSCC_PREF_PLMN_QUERY_REQ;

    /* 填写消息内容 */
    pstPrefPlmnQueryReq->enCmdType                     = NAS_MSCC_PIF_PREF_PLMN_QUERY;
    pstPrefPlmnQueryReq->bPlmnSelFlg                   = MN_PH_IsUsingPlmnSel();

    /*  填写cpol info */
    pstPrefPlmnQueryReq->stCpolInfo.enPrefPLMNType     =
                    (NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8)TAF_MMA_GetPrefPlmnParaType(pstRcvMsg->stCpolInfo.enPrefPLMNType);
    pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex        = pstRcvMsg->stCpolInfo.ulFromIndex;
    pstPrefPlmnQueryReq->stCpolInfo.ulPlmnNum          = pstRcvMsg->stCpolInfo.ulPlmnNum;
    pstPrefPlmnQueryReq->stCpolInfo.ulValidPlmnNum     = pstRcvMsg->stCpolInfo.ulValidPlmnNum;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnQueryReq);

    return;
}


VOS_VOID TAF_MMA_SndMsccPrefPlmnTestReq(
    TAF_MMA_PREF_PLMN_TEST_REQ_STRU    *pstRcvMsg
)
{
    MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstPrefPlmnTestReq     = VOS_NULL_PTR;

    pstPrefPlmnTestReq = (MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU));
    if (VOS_NULL_PTR == pstPrefPlmnTestReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccPrefPlmnTestReq: ERROR:ALLOC MEMORY FAIL.");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPrefPlmnTestReq + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstPrefPlmnTestReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnTestReq->stMsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstPrefPlmnTestReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnTestReq->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPrefPlmnTestReq->stMsgHeader.ulLength          = sizeof(MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnTestReq->stMsgHeader.ulMsgName         = ID_MMA_MSCC_PREF_PLMN_QUERY_REQ;

    /* 填写消息内容 */
    pstPrefPlmnTestReq->enCmdType                     = NAS_MSCC_PIF_PREF_PLMN_TEST;
    pstPrefPlmnTestReq->bPlmnSelFlg                   = MN_PH_IsUsingPlmnSel();
    pstPrefPlmnTestReq->stCpolInfo.enPrefPLMNType     = (NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8)TAF_MMA_GetPrefPlmnParaType(pstRcvMsg->enPrefPlmnType);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnTestReq);

    return;
}



VOS_VOID TAF_MMA_SndMsccPsRatTypeNtf(
    TAF_MMA_PS_RAT_TYPE_ENUM_UINT32     enCurrCdataServiceMode
)
{
    MMA_MSCC_PS_RAT_TYPE_NTF_STRU                          *pstPsRatTypeNtf = VOS_NULL_PTR;
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32                    enRatType;

    switch (enCurrCdataServiceMode)
    {
        case TAF_MMA_PS_RAT_TYPE_NULL:
            enRatType = NAS_MSCC_PIF_PS_RATTYPE_NULL;
            break;
        case TAF_MMA_PS_RAT_TYPE_1X:
            enRatType = NAS_MSCC_PIF_PS_RATTYPE_1X;
            break;
        case TAF_MMA_PS_RAT_TYPE_HRPD:
            enRatType = NAS_MSCC_PIF_PS_RATTYPE_HRPD;
            break;
        case TAF_MMA_PS_RAT_TYPE_EHRPD:
            enRatType = NAS_MSCC_PIF_PS_RATTYPE_EHRPD;
            break;
        case TAF_MMA_PS_RAT_TYPE_LTE:
            enRatType = NAS_MSCC_PIF_PS_RATTYPE_LTE;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_MMA_SndMsccPsRatTypeNtf: enRatType Error");
            return;
    }


    pstPsRatTypeNtf = (MMA_MSCC_PS_RAT_TYPE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                        sizeof(MMA_MSCC_PS_RAT_TYPE_NTF_STRU));
    if (VOS_NULL_PTR == pstPsRatTypeNtf)
    {
        MMA_ERRORLOG("TAF_MMA_SndMsccPsRatTypeNtf: ERROR:ALLOC MEMORY FAIL.");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPsRatTypeNtf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MSCC_PS_RAT_TYPE_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstPsRatTypeNtf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPsRatTypeNtf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstPsRatTypeNtf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPsRatTypeNtf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPsRatTypeNtf->stMsgHeader.ulLength          = sizeof(MMA_MSCC_PS_RAT_TYPE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPsRatTypeNtf->stMsgHeader.ulMsgName         = ID_MMA_MSCC_PS_RAT_TYPE_NTF;

    /* 填写消息内容 */
    pstPsRatTypeNtf->enPsRatType                   = enRatType;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPsRatTypeNtf);

    return;
}


#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_MMA_SndMsccVoiceDomainChangeInd(
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32                   enVoiceDomain
)
{
    NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU              *pstMsg = VOS_NULL_PTR;

    /* 申请内存 */
    pstMsg = (NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccVoiceDomainChangeInd:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->enVoiceDomain                = enVoiceDomain;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_SndMsccImsStartReq(VOS_VOID)
{
    MMA_MSCC_IMS_START_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_IMS_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_IMS_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccImsStartReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_IMS_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_IMS_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_IMS_START_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}


VOS_VOID TAF_MMA_SndMsccImsStopReq(VOS_VOID)
{
    MMA_MSCC_IMS_STOP_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_IMS_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_IMS_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccImsSwitchStopReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_IMS_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_IMS_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_IMS_STOP_REQ;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}
#endif


VOS_VOID TAF_MMA_SndMsccAutoReselSetReq(VOS_UINT8 ucActiveFlg)
{
    MMA_MSCC_AUTO_RESEL_SET_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMA_MSCC_AUTO_RESEL_SET_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSCC_AUTO_RESEL_SET_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccAutoReselSetReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSCC_AUTO_RESEL_SET_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_AUTO_RESEL_SET_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_AUTO_RESEL_SET_REQ;
    pstMsg->ucActiveFlg                  = ucActiveFlg;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}



VOS_VOID TAF_MMA_SndMsccGetGeoReq(VOS_VOID)
{
    MMA_MSCC_GET_GEO_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (MMA_MSCC_GET_GEO_REQ_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(MMA_MSCC_GET_GEO_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccGetGeoReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    TAF_MMA_CFG_MSG_HDR(pstMsg, UEPS_PID_MSCC, ID_MMA_MSCC_GET_GEO_REQ);

    /* 填写消息内容 */

    /* 发送消息 */
    TAF_MMA_SEND_MSG(pstMsg);

    NAS_TRACE_HIGH("MMA Get Geo Begin!!!");

    return;
}


VOS_VOID TAF_MMA_SndMsccStopGetGeoReq(VOS_VOID)
{
    MMA_MSCC_STOP_GET_GEO_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (MMA_MSCC_STOP_GET_GEO_REQ_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(MMA_MSCC_STOP_GET_GEO_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsccStopGetGeoReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    TAF_MMA_CFG_MSG_HDR(pstMsg, UEPS_PID_MSCC, ID_MMA_MSCC_STOP_GET_GEO_REQ);

    /* 填写消息内容 */

    /* 发送消息 */
    TAF_MMA_SEND_MSG(pstMsg);

    return;
}
/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

