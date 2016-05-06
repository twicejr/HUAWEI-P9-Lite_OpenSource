/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndMscc.c
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2013年3月26日
  最近修改   :
  功能描述   : mma给mscc发送消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月26日
    作    者   : z00161729
    修改内容   : 创建文件

****************************************************************************/

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
/*****************************************************************************
 函 数 名  : TAF_MMA_MapMmaRatToMsccRat
 功能描述  : MMA格式的接入模式转换为VOS格式的RAT
 输入参数  : ulCause: 原因值
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccStartReq
 功能描述  : 向mscc发送开机请求
 输入参数  : enCardStatus   - 卡状态
             pstPlmnRatPrio - 接入技术优先级
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2014年1月27日
   作    者   : s00261364
   修改内容   : L-C互操作项目,开机请求新增支持CDMA技术接口

*****************************************************************************/
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

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->enCallMode                 = (NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8)(TAF_SDC_GetCurCallMode());
#endif
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    /* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */

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
    /* Added by s00261364 for L-C互操作项目, 2014-1-27, end */


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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccSignalReportReq
 功能描述  : 向mscc发送信号上报配置消息
 输入参数  : ucActionType    - action type
             ucRrcMsgType    - msg type
             ucSignThreshold - 信号质量改变门限
             ucMinRptTimerInterval -时间间隔
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccModeChangeReq
 功能描述  : 向mscc发送模式变更消息
 输入参数  : enMsMode - ms模式
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccAttachReq
 功能描述  : 向mscc发送attach请求消息
 输入参数  : ulOpID       - operation id
             enAttachType - attach 类型
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2014年2月17日
   作    者   : b00269685
   修改内容   : L-C互操作项目:增加获取和注册请求的处理

*****************************************************************************/
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
    /* Added by b00269685 for L-C互操作项目, 2014-2-17, begin */
    pstMsg->enEpsAttachReason          = enAttachReason;
    /* Added by b00269685 for L-C互操作项目, 2014-2-17, end */

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccDetachReq
 功能描述  : 向mscc发送detach请求消息
 输入参数  : ulOpID       - operation id
             enDetachType - detach 类型
 输出参数  : 无
 返 回 值  : VOS_TRUE : 消息发送成功
             VOS_FALSE: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 3.日    期   : 2015年4月13日
   作    者   : h00313353
   修改内容   : SysCfg重构
*****************************************************************************/
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

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    pstMsg->enDetachReason             = enDetachCause;
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCsgListSearchReq
 功能描述  : 向mscc发送csg list搜网请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月30日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCsgListAbortReq
 功能描述  : 向mscc发送csg list abort消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月30日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPlmnListReq
 功能描述  : 向mscc发送list搜网请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPlmnListAbortReq
 功能描述  : 向mscc发送list搜网中止请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPlmnUserReselReq
 功能描述  : 向mscc发送重选请求消息
 输入参数  : enPlmnSelMode - 选网模式
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPlmnSpecialReq
 功能描述  : 向mscc发送指定搜网请求
 输入参数  : pstPlmnId    - 指定搜plmn id
             enAccessMode - 接入技术
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPowerOffReq
 功能描述  : 向mscc发送关机请求消息
 输入参数  : enCause - 关机原因值
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccSysCfgReq
 功能描述  : 发送syscfg请求消息
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pSysCfgReq,
             VOS_UINT8                           ucOnlyRoamParaChanged,
             VOS_UINT8                           ucIsNeedAttachPs
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
   1.日    期   : 2008年4月15日
     作    者   : luojian id:107747
     修改内容   : 新生成函数
   2.日    期   : 2009年4月9日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D10825/AT2D10887,Efust的定制需求，Efust禁掉GSM/SMS后相关服务被禁止
   3.日    期   : 2010年11月24日
     作    者   : z00161729
     修改内容   : 问题单号DTS2010112204212:syscfg设置双模但只支持W频段或只支持G频段,MMA应给MSCC报接入模式为W或G单模
   4.日    期   : 2011年6月29日
     作    者   : z00161729
     修改内容   : V7R1 phase II支持syscfgex命令修改
   5.日    期   : 2011年11月15日
     作    者   : zhoujun /40661
     修改内容   : GSM被禁止时syscfg设置需要删除G模相关信息
   6.日    期   : 2013年3月26日
     作    者   : z00161729
     修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
   7.日    期   : 2013年07月222日
     作    者   : j00177245
     修改内容   : 清理Coverity
   8.日    期   : 2014年2月13日
     作    者   : w00167002
     修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
  9.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/

/* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
VOS_VOID  TAF_MMA_SndMsccSysCfgReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pSysCfgReq,
    VOS_UINT8                           ucOnlyRoamParaChanged,
    VOS_UINT8                           ucIsNeedAttachPs
)
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
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

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
    return;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccNetScanMsgReq
 功能描述  : MMA模块通知MSCC模块NetScanReq消息
 输入参数  : TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanReq
 输出参数  : 无
 返 回 值  : 发送成功返回VOS_OK
             发送失败返回VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccAbortNetScanMsgReq
 功能描述  : MMA模块通知MSCC模块打断NetScanReq消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 发送成功返回VOS_OK
             发送失败返回VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccSystemAcquireReq
 功能描述  : 向mscc发送开机搜网请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccSpecPlmnSearchAbortReq
 功能描述  : 向mscc发送指定搜网中止请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccOmMaintainInfoInd
 功能描述  : 处理OAM发来的TRACE 配置请求
 输入参数  : ucOmConnectFlg       - om连接标识
             ucOmPcRecurEnableFlg - 回放使能标识
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月16日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccUpdateUplmnNtf
 功能描述  : mma给mscc发送UPLMN更新通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
              VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月31日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccOtherModemInfoNotify
 功能描述  : 向mscc发送ID_MMA_MSCC_OTHER_MODEM_INFO_NOTIFY请求消息
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccOtherModemDplmnNplmnInfoNotify
 功能描述  : 向mscc发送dplmn和nplmn信息
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改

 2.日    期   : 2015年10月22日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccNcellInfoInd
 功能描述  : 向mscc发送ID_MMA_MSCC_TDS_LTE_NCELL_INFO_IND请求消息
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPsTransferInd
 功能描述  : 向mscc发送ID_MMA_MSCC_PS_TRANSFER_IND请求消息
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccEOPlmnSetReq
 功能描述  : MMA模块通知MSCC模块ID_MMA_MSCC_EOPLMN_SET_REQ消息
 输入参数  : TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnSetPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 新生成函数
  2.日    期   : 2013年11月26日
    作    者   : s00190137
    修改内容   : 添加分组机制，单组允许最大设置50个OPLMN
*****************************************************************************/
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


/* Added by b00269685 for L-C互操作项目, 2014-2-13, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccAcqReq
 功能描述  : 向MSCC发送开机搜网请求消息
 输入参数  : stMmaAcqPara
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月13日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccRegReq
 功能描述  : 向MSCC发送开机注册请求消息
 输入参数  : stMmaRegPara
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月14日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPowerSaveReq
 功能描述  : 向MSCC发送开机搜网请求消息
 输入参数  : stMmaPowerSavePara
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月13日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
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

/* Added by b00269685 for L-C互操作项目, 2014-2-14, end */


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccSrvAcqReq
 功能描述  : 向MSCC发送因服务触发的搜网指示请求消息
 输入参数  : enSrvType:服务类型
            pstRatList:需要触发搜网的网络模式列表
 输出参数  : 无
 返 回 值  : VOS_OK:发送成功
             VOS_ERR:发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月17日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccBeginSessionNotify
 功能描述  : 向MSCC发送申请资源消息
 输入参数  : enSessionType:Session类型
            pstRatList: Rat列表
 输出参数  : 无
 返 回 值  : VOS_OK:发送成功
             VOS_ERR:发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月17日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccEndSessionNotify
 功能描述  : 向MSCC发送释放资源消息
 输入参数  : stMmaAcqPara
 输出参数  : 无
 返 回 值  : VOS_OK:发送成功
             VOS_ERR:发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月17日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccImsSrvInfoNotify
 功能描述  : 向mscc发送ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY
 输入参数  : ucImsCallFlg---IMS call是否存在
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_MapMmaCallTypeToMsccFormat
 功能描述  : MMA格式的呼叫类型转换为MSCC格式的
 输入参数  : TAF_MMA_1X_CALL_TYPE_ENUM_UINT8   enMmaCallType
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : TAF_MMA_MapCsCauseToMsccFormat
 功能描述  : MMA格式的呼叫原因值转换为MSCC格式的(CS)
 输入参数  : ulCause: 原因值
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_MapPsCauseToMsccFormat
 功能描述  : MMA格式的PS原因类型转换为MSCC格式的(PS)
 输入参数  : ulCause : 原因值
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCdmaMoCallStartNtf
 功能描述  : 向MSCC发送呼叫开始指示
 输入参数  : enCallType --  呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月27日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccQuitCallBackNtf
 功能描述  : 向MSCC发送退出CallBack指示
 输入参数  : enCallType --  呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月21日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCdmaMoCallEndNtf
 功能描述  : 向MSCC发送呼叫结束指示
 输入参数  : enCallType --  呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月27日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCdmaMoCallSuccessNtf
 功能描述  : 向MSCC发送呼叫成功指示
 输入参数  : enCallType --  呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月27日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCdmaMoCallRedialSysAcqNtf
 功能描述  : 向MSCC发送呼叫重拨指示
 输入参数  : enCallType --  呼叫类型
             enCause --- 呼叫失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月27日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCFreqLockNtf
 功能描述  : MMA发送锁频信息给MSCC
 输入参数  : TAF_MMA_CFREQ_LOCK_SET_PARA_STRU *pstCFreqLockSetReq
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCdmaCsqSetReq
 功能描述  : 向MSCC发送设置CDMACSQ上报参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月25日
   作    者   : m00312079
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccHandsetInfoQryReq
 功能描述  : 向MSCC发送获取手机信息请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月25日
   作    者   : m00312079
   修改内容   : 新生成函数

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccHdrCsqSetReq
 功能描述  : 向MSCC发送设置HDRCSQ上报参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月20日
   作    者   : c00299064
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCFPlmnReq
 功能描述  : 向mscc发送指定或所有plmn请求
 输入参数  : pstPlmnId    - plmn id

 输出参数  : 无
 返 回 值  : VOS_OK : 消息发送成功
             VOS_ERR: 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccCFPlmnQueryReq
 功能描述  : 向mscc发送查询请求
 输入参数  :

 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccDplmnSetReq
 功能描述  : mma给mscc发送ID_MMA_MSCC_DPLMN_SET_REQ 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新生成函数
  2.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : 在消息中新增更新Dplmn的场景
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPrefPlmnSetReq
 功能描述  : MMA发送设置prefplmn信息给MSCC
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl,
             TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月06日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPrefPlmnQueryReq
 功能描述  : MMA发送查询prefplmn信息给MSCC
 输入参数  : TAF_MMA_PREF_PLMN_QUERY_REQ_STRU    *pstRcvMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月06日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPrefPlmnTestReq
 功能描述  : MMA发送查询prefplmn信息给MSCC
 输入参数  : TAF_MMA_PREF_PLMN_TEST_REQ_STRU    *pstRcvMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月06日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccPsRatTypeNtf
 功能描述  : MMA发送查询prefplmn信息给MSCC
 输入参数  : TAF_MMA_PREF_PLMN_TEST_REQ_STRU    *pstRcvMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccVoiceDomainChangeInd
 功能描述  : MMA发送voice domain变化消息给MSCC
 输入参数  : voice domain:E-UTRAN的语音优先域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月15日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccImsStartReq
 功能描述  : 给MSCC发送IMS开启请求消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月15日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccImsStopReq
 功能描述  : 给MSCC发送IMS关闭请求消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月15日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccAutoReselSetReq
 功能描述  : 给MSCC发送auto resel
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月3日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccGetGeoReq
 功能描述  : 获取地理位置信息请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_MMA_SndMsccStopGetGeoReq
 功能描述  : 停止获取地理位置信息请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
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

