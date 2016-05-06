/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallMnccProc.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月20日
  最近修改   : 2007年9月20日
  功能描述   : 处理来自CC的MNCC原语
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年7月12日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2008年7月23日
    作    者   : 黎客来 130025
    修改内容   : 问题单号:AT2D04596
  4.日    期   : 2008年7月23日
    作    者   : 黎客来 130025
    修改内容   : 问题单号:AT2D04594
  5.日    期   : 2008年9月11日
    作    者   :S62952
    修改内容   : 问题单号:AT2D05594
  6.日    期   : 2008年10月20日
    作    者   : h44270
    修改内容   : 问题单号:A32D14153,来电时，用户尚未接听电话就打开了声码器,，AMR速率变换没有上报
  7.日    期   : 2009年3月2日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D09095
  8.日    期   : 2009年5月20日
    作    者   : h44270
    修改内容   : 问题单号A32D14863，在中国移动的网络下（G网），被叫单板，来电接不起来。
  9.日    期   : 2009年12月6日
    作    者   : h44270
    修改内容   : 问题单号AT2D15568，NAS处理SD晚指配有问题,没有打开声码器。

  10.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  11.日    期   : 2010年3月16日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率调整

  12.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS1
******************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallMnccProc.h"
#include "NasMncc.h"
#include "MnCallMgmt.h"
#include "MnCallApi.h"
#include "MnComm.h"
#include "NasIeUtil.h"
#include "MnCallFacilityDecode.h"
#include "MnCallFacilityEncode.h"
#include "MnErrorCode.h"
#include "NasMncc.h"
#include "MnCallSendCc.h"
#include "MnCallBcProc.h"
#include "NasOmInterface.h"
#include "VcCallInterface.h"
#include "MnCallCstProc.h"
#include "MnCall.h"
#include "MnCallTimer.h"
#include "MnCallMsgDef.h"
#include "MM_Share_inc.h"
#include "MnMsgTs.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#include "NVIM_Interface.h"

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
#include "TafSdcCtx.h"
#include "TafSdcLib.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
#include "NasUtranCtrlInterface.h"
#include "NasUsimmApi.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "SpmImsaInterface.h"
#endif
#include "MnCallImsaProc.h"
#include "MnCallMgmt.h"

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, end */

#include "MnCallReqProc.h"
#include "TafStdlib.h"
#include "MnCallSendApp.h"

#include "MnCallCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_MNCC_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/* 当前TCH信道参数 */
LOCAL  MN_CALL_CHANNEL_INFO_STRU        f_stCallTchStatus;

/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, begin */
MN_CALL_CHANNEL_INFO_STRU               g_stLastCallTchStatus;
/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, end */


/* 当前呼叫是否等待发送Alert信息 */
LOCAL  MN_CALL_WAIT_SEND_ALERT_STRU     f_stWaitSendAlert;

/*当前Channel是否打开标志*/
LOCAL  VOS_BOOL                         f_bChannelOpenFlg = VOS_FALSE;

/* 当前所有呼叫信息 */
LOCAL  MN_CALL_INFO_STRU                f_astCallInfos[MN_CALL_MAX_NUM];


/*lint -save -e958 */

/*****************************************************************************
   2 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CALL_SetChannelOpenFlg
 功能描述  : 设置信道打开标志
 输入参数  : bChannelOpenFlg - 语音信道打开标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetChannelOpenFlg(
    VOS_BOOL                            bChannelOpenFlg
)
{
    f_bChannelOpenFlg = bChannelOpenFlg;
}

/*****************************************************************************
 函 数 名  : CALL_GetChannelOpenFlg
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL MN_CALL_GetChannelOpenFlg( VOS_VOID )
{
    return f_bChannelOpenFlg;
}


/*****************************************************************************
 函 数 名  : CALL_SetWaitSendAlertStatus
 功能描述  :
 输入参数  : bWaitSendAlertStatus   - 业务信道的状态
             uccallId               - 呼叫Id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetWaitSendAlertStatus(
    VOS_BOOL                            bWaitSendAlertStatus,
    VOS_UINT8                           uccallId
)
{
    f_stWaitSendAlert.bWaitSendAlertStatus = bWaitSendAlertStatus;
    f_stWaitSendAlert.ucCallId = uccallId;
}

/*****************************************************************************
 函 数 名  : CALL_GetWaitSendAlertStatus
 功能描述  :
 输入参数  :
 输出参数  : pbWaitSendAlertStatus - 当前是否处于等待发送alerting消息状态
              puccallId             - 对应的呼叫Id
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_GetWaitSendAlertStatus(
    VOS_BOOL                            *pbWaitSendAlertStatus,
    VOS_UINT8                           *puccallId
)
{
    *pbWaitSendAlertStatus = f_stWaitSendAlert.bWaitSendAlertStatus;
    *puccallId = f_stWaitSendAlert.ucCallId;

}

/*****************************************************************************
 函 数 名  : MN_CALL_SetTchStatus
 功能描述  :
 输入参数  : bAvailable - 业务信道的状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetTchStatus(
    VOS_BOOL                            bAvailable
)
{
    f_stCallTchStatus.bChannelEnable = bAvailable;
}

/*****************************************************************************
 函 数 名  : MN_CALL_SetTchPara
 功能描述  :
 输入参数  : pstTchPara - 信道参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月16日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率调整

  3.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 支持AMR-WB

  4.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
LOCAL VOS_BOOL MN_CALL_SetTchPara(
    const NAS_CC_SYNC_IND_STRU           *pstTchPara,
    const VOS_UINT8                       ucCallId
)
{
    MN_CALL_RADIO_MODE_ENUM_U8          enMode;
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;

    switch(pstTchPara->enTchType)
    {
        case NAS_CC_TCH_TYPE_FR:
            enCodecType = MN_CALL_CODEC_TYPE_FR;
            break;

        case NAS_CC_TCH_TYPE_HR:
            enCodecType = MN_CALL_CODEC_TYPE_HR;
            break;

        case NAS_CC_TCH_TYPE_EFR:
            enCodecType = MN_CALL_CODEC_TYPE_EFR;
            break;

        case NAS_CC_TCH_TYPE_AMR:
            enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

        case NAS_CC_TCH_TYPE_AMR2:
            enCodecType = MN_CALL_CODEC_TYPE_AMR2;
            break;

        case NAS_CC_TCH_TYPE_AMRWB:
            enCodecType = MN_CALL_CODEC_TYPE_AMRWB;
            break;

        case NAS_CC_TCH_TYPE_AHR:
            enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

        case NAS_CC_TCH_SINGAL_MOD:
            /* singal mode, ignore */
            return VOS_FALSE;

        case NAS_CC_TCH_CSD_9600:
        case NAS_CC_TCH_CSD_4800:
        case NAS_CC_TCH_CSD_2400:
        case NAS_CC_TCH_CSD_14400:
            /* data mode, ignore */
            return VOS_FALSE;

        default:
            MN_WARN_LOG1("MN_CALL_SetTchPara enTchType is error: ", (VOS_INT32)(pstTchPara->enTchType));
            return VOS_FALSE;
    }

    switch(pstTchPara->enRaMode)
    {
        case NAS_CC_RA_MODE_GSM:
            enMode = MN_CALL_RADIO_MODE_GSM;
            break;

        case NAS_CC_RA_MODE_WCDMA:
            enMode = MN_CALL_RADIO_MODE_WCDMA;
            break;

        default:
            MN_WARN_LOG1("MN_CALL_SetTchPara enRaMode is error: ", (VOS_INT32)(pstTchPara->enRaMode));
            return VOS_FALSE;
    }

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ECALL);
    }
    else
#endif
    {
        TAF_CALL_SetTchCallType(TAF_CALL_TYPE_NORMAL_CALL);
    }
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

    f_stCallTchStatus.stChannelParam.enCodecType = enCodecType;
    f_stCallTchStatus.stChannelParam.enMode = enMode;


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MN_CALL_GetTchStatus
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年6月20日
    作    者   : z00161729
    修改内容   : 问题单DTS2010061100528
*****************************************************************************/
VOS_BOOL MN_CALL_GetTchStatus( VOS_VOID )
{
    return f_stCallTchStatus.bChannelEnable;
}

/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_SetLastCallTchStatus
 功能描述  : 设置TCH信道参数全局变量
 输入参数  : pstCallTchStatus: TCH信道参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月05日
    作    者   : l00171473
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetLastCallTchStatus(
    MN_CALL_CHANNEL_INFO_STRU          *pstCallTchStatus
)
{
    PS_MEM_CPY(&g_stLastCallTchStatus,
               pstCallTchStatus,
               sizeof(MN_CALL_CHANNEL_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : MN_CALL_GetLastCodecType
 功能描述  : 获取保存的上次的CODEC TYPE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CODEC TYPE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月05日
    作    者   : l00171473
    修改内容   : 新生成函数
*****************************************************************************/
MN_CALL_CODEC_TYPE_ENUM_U8 MN_CALL_GetLastCodecType(VOS_VOID)
{
    return g_stLastCallTchStatus.stChannelParam.enCodecType;
}
/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* MN_CALL_JudgeMtCallType调整到MnComm.c中 */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_SetTchCallType
 功能描述  : 更新当前TCH中的呼叫类型
 输入参数  : enCallType －呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ENUM_UINT16 enCallType)
{
    f_stCallTchStatus.stChannelParam.enCallType = enCallType;
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

/*****************************************************************************
 函 数 名  : CALL_JudgeMtCallMode
 功能描述  : 判定来电的呼叫模式
 输入参数  : pstBCRepeatInd - IE Repeat indicator
              pstBC1         - IE BC1
              pstBC2         - IE BC2
 输出参数  : penCallMode    - 呼叫模式
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32  MN_CALL_JudgeMtCallMode(
    const NAS_CC_IE_REPEAT_INDICATOR_STRU       *pstBCRepeatInd,
    const NAS_CC_IE_BC_STRU                     *pstBC1,
    const NAS_CC_IE_BC_STRU                     *pstBC2,
    MN_CALL_MODE_ENUM_U8                        *penCallMode
)
{
    MN_CALL_TYPE_ENUM_U8                enCallType1;
    MN_CALL_TYPE_ENUM_U8                enCallType2;

    /* AVF 模式下，必须两个BC都存在 */
    if ((VOS_TRUE == NAS_IE_IS_PRESENT(pstBC1))
      &&(VOS_TRUE == NAS_IE_IS_PRESENT(pstBC2)))
    {
        if (VOS_OK != MN_CALL_JudgeMtCallType(&pstBC1->Octet3,
                                           &pstBC1->Octet5a,
                                           &enCallType1))
        {
            return VOS_ERR;
        }

        if (VOS_OK != MN_CALL_JudgeMtCallType(&pstBC2->Octet3,
                                           &pstBC2->Octet5a,
                                           &enCallType2))
        {
            return VOS_ERR;
        }

        /* 目前这里只写了支持语音和传真，其他情况下，暂时认为是不兼容 */
        if ((MN_CALL_TYPE_VOICE == enCallType1)
         && (MN_CALL_TYPE_FAX == enCallType2))
        {
            switch(pstBCRepeatInd->RepeatIndication)
            {
            case MN_CALL_REP_IND_ALTER:
            case MN_CALL_REP_IND_ALTER_1_PRFER:
                *penCallMode = MN_CALL_MODE_AVF;
                return VOS_OK;

            case MN_CALL_REP_IND_FALLBACK:
                *penCallMode = MN_CALL_MODE_SINGLE;
                return VOS_OK;

            default:
                MN_WARN_LOG("MN_CALL_JudgeMtCallMode: Repeat Indication err");
                return VOS_ERR;
            }
        }

        MN_WARN_LOG("MN_CALL_JudgeMtCallMode: not support call mode");
        return VOS_ERR;
    }

    /* 其他情况下，属于single模式 */
    *penCallMode = MN_CALL_MODE_SINGLE;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcNotifyForwardSsCode
 功能描述  : 当补充业务是呼叫前转时,Component中的Operation Code为NotifySs时，调用该函数
             进行处理
 输入参数  : ucCallId    - 呼叫ID
             pstNotifySs - notifySs内容
 输出参数  : pstSsInfo   - 记录上报信息
 返 回 值  : VOS_OK      - 成功
             VOS_ERR     - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_ProcNotifyForwardSsCode(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo
)
{
    /*根据 24.082中的描述，收到ssStatus的时候，表示该业务被激活*/
    if (pstNotifySs->OP_SsStatus)
    {
        if (TAF_CFU_SS_CODE == pstNotifySs->SsCode)
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_UNCOND_FWD_ACTIVE;
        }
        else
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_COND_FWD_ACTIVE;
        }
    }

    /*根据 24.082中的描述，收到SsNotification的时候，表示号码被前转*/
    if (pstNotifySs->OP_SsNotification)
    {
        /*根据24.080中对于SsNotification的值的定义来确定值, 24.080 4.4.2*/
        switch(pstNotifySs->SsNotification)
        {
            case TAF_FWDIND_FORWARDED_CALL_INCOM:
            case TAF_FWDIND_INCALL_FORWARDED:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_FORWORDED_CALL;
                break;

            case TAF_FWDIND_OUTCALL_FORWARDED:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_BE_FORWORDED;
                break;

            default:
                MN_WARN_LOG("MN_CALL_ProcNotifySs: Notification value is wrong");
                return VOS_ERR;

        }
    }
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : MN_CALL_NotifyNtfyOnHoldOrRetrieved
 功能描述  : 当补充业务是告知呼叫被保持或者恢复,Component中的Operation Code为
             NotifySs时，调用该函数进行处理
 输入参数  :ucCallId     - 呼叫ID
            pstNotifySs  - notifySs内容
 输出参数  : pstSsInfo   - 记录上报信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_NotifyNtfyOnHoldOrRetrieved(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo
)
{
    if (MN_CALL_ON_HOLD_IND_RETRIEVED == pstNotifySs->CallOnHoldIndicator)
    {
        pstSsInfo->enCode = MN_CALL_SS_NTFY_RETRIEVED;
    }
    else
    {
        pstSsInfo->enCode = MN_CALL_SS_NTFY_ON_HOLD;
    }
    MN_CALL_UpdateSsNotify(ucCallId, pstSsInfo);

    /* 广播来电(INCOMING)事件 */
    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcNotifyCcbsSscode
 功能描述  : 当补充业务是CCBS时,Component中的Operation Code为NotifySs时，调用该函数
             进行处理
 输入参数  : pstNotifySs    - notifySs内容
 输出参数  : pstSsInfo      - 记录上报相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月20日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_ProcNotifyCcbsSscode(
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo
)
{

    if (TAF_CCBS_A_SS_CODE == pstNotifySs->SsCode)
    {
        /*通过MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY)上报CCBS回呼事件*/
         pstSsInfo->enCode = MN_CALL_SS_NTFY_CCBS_RECALL;
    }
    else if (TAF_CCBS_B_SS_CODE == pstNotifySs->SsCode)
    {
        pstSsInfo->enCode = MN_CALL_SS_NTFY_CCBS_BE_RECALLED;
    }
    else
    {
        ;
    }
}

/*****************************************************************************
 函 数 名  : CALL_SsRegCcEntryProc
 功能描述  : 更新补充业务Ect操作的进展
 输入参数  : callId      - 呼叫Id
             unComponent - 网络回复的component
             enErrcode   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsRegCcEntryProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{

    /*更新补充业务操作的进展*/
    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                                       enErrcode);
    }

}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcNotifySsCode
 功能描述  : 当补充业务Component中的Operation Code为NotifySs时，调用该函数
             进行处理
 输入参数  : ucCallId    - 呼叫ID
             pstNotifySs - notifySs内容
 输出参数  : pstSsInfo   - 记录上报信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2013年3月29日
    作    者   : 傅映君 62575
    修改内容   : DTS2013033004557,参考新的特性控制原则: CD业务信息上报不受业务控制NV项限制
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_ProcNotifySsCode(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo

)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /*呼叫禁止相关信息*/
    if (TAF_ALL_BARRING_SS_CODE == (pstNotifySs->SsCode & 0xf0))
    {
        switch(pstNotifySs->SsCode)
        {
            case TAF_BAOC_SS_CODE:
            case TAF_BOIC_SS_CODE:
            case TAF_BOICEXHC_SS_CODE:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_OUTGOING_BARRED;
                break;

            case TAF_BAIC_SS_CODE:
            case TAF_BICROAM_SS_CODE:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_INCOMING_BARRED;
                break;

            default:
                MN_WARN_LOG("MN_CALL_ProcNotifySs: Ss Code Error");
                return;
        }
    }

    /*呼叫前转相关信息*/
    if (TAF_ALL_FORWARDING_SS_CODE == (pstNotifySs->SsCode & 0xf0))
    {
        if (TAF_CD_SS_CODE != pstNotifySs->SsCode)
        {
            if (VOS_ERR == MN_CALL_ProcNotifyForwardSsCode(ucCallId, pstNotifySs, pstSsInfo))
            {
                return;
            }
        }

    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        MN_CALL_ProcNotifyCcbsSscode(pstNotifySs, pstSsInfo);
    }

    /* 参考新的特性控制原则: CD业务信息上报不受业务控制NV项限制 */
    if (TAF_CD_SS_CODE == pstNotifySs->SsCode)
    {
        if (TAF_FWDIND_OUTCALL_FORWARDED == pstNotifySs->SsNotification)
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_BE_DEFLECTED;
        }
        else
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_DEFLECTED_CALL;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end*/

    MN_CALL_UpdateSsNotify(ucCallId, pstSsInfo);

    /* 上报事件*/
    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    return;
}



/*****************************************************************************
 函 数 名  : MN_CALL_ProcNotifySsEct
 功能描述  : 当补充业务是ECT时,Component中的Operation Code为NotifySs时，调用该函数
             进行处理
 输入参数  : ucCallId    - 呼叫ID
             pstNotifySs - notifySs内容
 输出参数  : pstSsInfo   - 记录上报信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2012年11月08日
    作    者   : l65478
    修改内容   : DTS2012110702322,MT没有显示新的号码,同时CUSS上报也是旧的信息
  4.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
  5.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_ProcNotifySsEct(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo

)
{
    VOS_UINT8                           ucBcdLen;


    ucBcdLen = 0;

    pstSsInfo->enCode = MN_CALL_SS_NTFY_EXPLICIT_CALL_TRANSFER;
    pstSsInfo->stEctIndicator.enEctCallState = pstNotifySs->EctIndicator.EctCallState;

    if (1 == pstNotifySs->EctIndicator.OP_PresentationAllowedAddr)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_PRESENTATION_ALLOWED_ADDR;
        pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.enNumType
                    = pstNotifySs->EctIndicator.PresentationAllowedAddr.NumType;
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)pstNotifySs->EctIndicator.PresentationAllowedAddr.aucPartyNumber,
                            pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.aucBcdNum,
                            &ucBcdLen))
        {
            MN_INFO_LOG("MN_CALL_ProcNotifySsEct: TAF_STD_ConvertAsciiNumberToBcd fail");
        }
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.ucNumLen = ucBcdLen;

        /* 参考22.091 8.1,8.3 */
        MN_CALL_UpdateCallNumber(ucCallId, &(pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr));
    }

    if (1 == pstNotifySs->EctIndicator.OP_PresentationRestricted)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_PRESENTATION_RESTRICTED;
    }

    if (1 == pstNotifySs->EctIndicator.OP_NumNotAvailableDueToInterworking)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_NUM_NOT_AVAILABLE;
    }

    if (1 == pstNotifySs->EctIndicator.OP_PresentationRestrictedAddr)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_PRESENTATION_RESTRICTED_ADDR;
        pstSsInfo->stEctIndicator.rdn.stPresentationRestrictedAddr.enNumType
                    = pstNotifySs->EctIndicator.PresentationRestrictedAddr.NumType;
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)pstNotifySs->EctIndicator.PresentationRestrictedAddr.aucPartyNumber,
                            pstSsInfo->stEctIndicator.rdn.stPresentationRestrictedAddr.aucBcdNum,
                            &ucBcdLen))
        {
            MN_INFO_LOG("MN_CALL_ProcNotifySsEct: TAF_STD_ConvertAsciiNumberToBcd fail");
        }
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.ucNumLen = ucBcdLen;
    }

    MN_CALL_UpdateSsNotify(ucCallId, pstSsInfo);

    /* 广播来电(INCOMING)事件 */
    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);

}


/*****************************************************************************
 函 数 名  : CALL_ProcNotifySs
 功能描述  : 当补充业务Component中的Operation Code为NotifySs时，调用该函数
             进行处理。该函数将向应用层上报相应的补充业务通知事件。
 输入参数  : pstSsCompo     - 来自网络的Facility IE中的SS component
             ucCallId       - 呼叫Id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年1月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  3.日    期   : 2012年10月20日
    作    者   : l65478
    修改内容   : DTS2012101901424,没有更新ECT后的新的号码
*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_ProcNotifySs(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs
)
{
    MN_CALL_SS_NOTIFY_STRU              stSsInfo;


    PS_MEM_SET(&stSsInfo, 0, sizeof(stSsInfo));

    MN_INFO_LOG1("MN_CALL_ProcNotifySs: callId,", ucCallId);

    /* 告知呼叫等待 */
    if (pstNotifySs->OP_CallWaitingInd)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_IS_WAITING;

        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);

        /* 广播来电(INCOMING)事件 */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    /* 告知呼叫被保持或者恢复 */
    if (pstNotifySs->OP_CallOnHoldInd)
    {
        MN_CALL_NotifyNtfyOnHoldOrRetrieved(ucCallId, pstNotifySs, &stSsInfo);
    }

    /* 告知进入MPTY状态 */
    if (pstNotifySs->OP_MptyIndicator)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_ENTER_MPTY;
        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    /* 告知cug相关信息 */
    if (pstNotifySs->OP_CugIndex)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_MO_CUG_INFO;
        stSsInfo.ulCugIndex = (VOS_UINT32)pstNotifySs->CugIndex;
        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);

        /* 广播来电(INCOMING)事件 */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    /* 告知clir相关信息 */
    if(pstNotifySs->OP_ClirSuppressionRej)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_CLIR_SUPPRESS_REJ;
        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);

        /* 广播来电(INCOMING)事件 */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    if (pstNotifySs->OP_SsCode)
    {
        MN_CALL_ProcNotifySsCode(ucCallId, pstNotifySs, &stSsInfo);
    }
    /*ECT相关信息*/
    if (pstNotifySs->OP_EctIndicator)
    {
        MN_CALL_ProcNotifySsEct(ucCallId, pstNotifySs, &stSsInfo);
    }

}

/*****************************************************************************
 函 数 名  : MN_CALL_Bc1Bc2CompChk
 功能描述  : 对call confirm消息中的BC进行检查。
 输入参数  : callId -呼叫标识
 输出参数  : pstBc1Setup            - 检查后BC1值
              pstBc2Setup           - 检查后BC2值
              pstRepeatIndSetup     - repeat indicator的值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理

  3.日    期   : 2012年10月16日
    作    者   : z40661
    修改内容   : DTS2012071007225
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_Bc1Bc2CompChk(
    MN_CALL_ID_T                        callId,
    NAS_CC_IE_BC_STRU                   *pstBc1Setup,
    NAS_CC_IE_BC_STRU                   *pstBc2Setup,
    NAS_CC_IE_REPEAT_INDICATOR_STRU     *pstRepeatIndSetup
)
{
    VOS_UINT32                          ulBc1ChkRslt;
    VOS_UINT32                          ulBc2ChkRslt;

    /* BC1和BC2的兼容性检查 */
    ulBc1ChkRslt = MN_CALL_BcCompChk(pstBc1Setup);
    ulBc2ChkRslt = MN_CALL_BcCompChk(pstBc2Setup);


    /* 此处需要在CC的定义增加对应的枚举定义，暂时以1代替alternate */
    if ( MN_CALL_REP_IND_ALTER == pstRepeatIndSetup->RepeatIndication )
    {
        MN_INFO_LOG1("MN_CALL_ProcMnccSetupInd ", pstRepeatIndSetup->RepeatIndication );
        /*如果有一个BC检查都没有通过*/
        if ((VOS_OK != ulBc1ChkRslt) || (VOS_OK != ulBc2ChkRslt))
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: alter mode one bc check no ok" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
    }
    else if ( ( MN_CALL_REP_IND_FALLBACK == pstRepeatIndSetup->RepeatIndication)
           || ( MN_CALL_REP_IND_ALTER_1_PRFER == pstRepeatIndSetup->RepeatIndication ))
    {
        /* 两个BC检查没有通过 */
        if ( (VOS_OK != ulBc1ChkRslt) && (VOS_OK != ulBc2ChkRslt) )
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: fallback mode two bc check no ok" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
        /*其中一个BC检查没有通过*/
        else if (VOS_OK != ulBc1ChkRslt)
        {
            /*保留检查通过的BC, 丢弃检查失败的BC(将不携带在Call Confirm中)*/
            /* 此处将检查失败的BC设置为不存在 */
            /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
            PS_MEM_CPY(pstBc1Setup,
                       pstBc2Setup,
                       sizeof(NAS_CC_IE_BC_STRU));
            /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
            NAS_IE_SET_ABSENT(pstBc2Setup);
        }
        else if (VOS_OK != ulBc2ChkRslt)
        {
            NAS_IE_SET_ABSENT(pstBc2Setup);
        }
        else
        {
            MN_NORM_LOG("MN_CALL_ProcMnccSetupInd: fallback mode BC check pass" );
        }
    }
    else
    {
        MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
        MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: other mode BC check pass" );
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CALL_BcChkForCallCnf
 功能描述  : 对call confirm或cc establishment消息中的BC进行检查
 输入参数  : pMsg - MT的setup消息或MO的setup消息
             callId - 呼叫Id
             enCallDir -呼叫方向
             pstDataCfgInfo     - cs data 业务配置数据
 输出参数  : pstBc1CallCnf      - 回复的call confirm或cc establishment confirm消息中的Bc1
              pstBc2CallCnf     - 回复的call confirm或cc establishment confirm消息中的Bc2
              penRepeatInd      - repeat indicator的值
 返 回 值  : VOS_OK:成功
             VOS_ERR:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加CCBS支持
  3.日    期   : 2010年12月3日
    作    者   : z00161729
    修改内容  : DTS2010120301487:GCF 11.1.1用例要求对不支持的业务类型回复原因值为88的release complete消息
  4.日    期   : 2012年05月21日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012052100994,拨打可视电话，发给网侧的承载类型不对

*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_BcChkForCallCnf(
    VOS_VOID                            *pMsg,
    NAS_CC_IE_BC_STRU                   *pstBc1CallCnf,
    NAS_CC_IE_BC_STRU                   *pstBc2CallCnf,
    MN_CALL_REP_IND_ENUM_U8             *penRepeatInd,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{
    VOS_UINT32                          ulCnt;
    NAS_CC_MSG_SETUP_MO_STRU            *pstMoSetup;
    NAS_CC_MSG_SETUP_MT_STRU            *pstMtSetup;
    NAS_CC_IE_BC_STRU                   *pstBc1Setup;
    NAS_CC_IE_BC_STRU                   *pstBc2Setup;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     *pstRepeatIndSetup;
    VOS_UINT8                           ucRatType;


    if (MN_CALL_DIR_CCBS == enCallDir)
    {
        /*CCBS中cc establishment中setup container中带的setup结构同NAS_CC_MSG_SETUP_MO_STRU*/
        pstMoSetup = (NAS_CC_MSG_SETUP_MO_STRU *)pMsg;
        pstBc1Setup = &pstMoSetup->stBC1;
        pstBc2Setup = &pstMoSetup->stBC2;
        pstRepeatIndSetup = &pstMoSetup->stBCRepeatInd;
    }
    else
    {
        pstMtSetup = (NAS_CC_MSG_SETUP_MT_STRU *)pMsg;
        pstBc1Setup =  &pstMtSetup->stBC1;
        pstBc2Setup = &pstMtSetup->stBC2;
        pstRepeatIndSetup = &pstMtSetup->stBCRepeatInd;
    }

    MMC_ComGetRatType(&ucRatType);
    if (MN_CALL_NET_TYPE_GSM == ucRatType)
    {
        /* 当前驻留G下*/
        if ((VOS_TRUE == NAS_IE_IS_PRESENT(pstBc1Setup))
         && (MN_CALL_BC_VAL_ITC_SPEECH != pstBc1Setup->Octet3.InfoTransCap)
         && (MN_CALL_BC_VAL_ITC_AUX_SPEECH != pstBc1Setup->Octet3.InfoTransCap))
        {
            /* 不支持的业务类型直接回复release complete消息 */
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;

        }


        if ((VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2Setup))
         && (MN_CALL_BC_VAL_ITC_SPEECH != pstBc2Setup->Octet3.InfoTransCap)
         && (MN_CALL_BC_VAL_ITC_AUX_SPEECH != pstBc2Setup->Octet3.InfoTransCap))
        {
            /* 不支持的业务类型直接回复release complete消息 */
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;

        }
    }
    /* 以下是对BC的检查 */
    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1Setup))
    {
        /*单号码方案, 现在的处理认为是voice。
           为了规避编译告警，在MN_CALL_BuildBcForSns函数调用的时候所传入的第二个参数
           pstDataCfgInfo进行了强制转换，实际上是有问题的，因为MN_CALL_CS_DATA_CFG_INFO_STRU结构
           和MN_CALL_CS_DATA_CFG_STRU结构的元素enSpeed是不一样的。后续修改CSD的时候请特别关注。*/
        ulCnt = MN_CALL_BuildBcForSns(MN_CALL_SNS_MODE_VOICE,
                                      pstDataCfgInfo,
                                      pstBc1CallCnf,
                                      pstBc2CallCnf,
                                      penRepeatInd);
        if ( 0 == ulCnt )
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: no bc1 not support" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
        MN_CALL_UpdateCallMode(callId, MN_CALL_MODE_SINGLE);
        MN_CALL_UpdateCallType(callId, MN_CALL_TYPE_VOICE);
    }
    else if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc2Setup))
    {
        /* BC1的兼容性检查，如果不能通过检查，发送Release Complete消息 */
        if (VOS_OK != MN_CALL_BcCompChk(pstBc1Setup) )
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: bc1 check no ok" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
    }
    else
    {
        /* BC1和BC2的兼容性检查 */
        if (VOS_ERR == MN_CALL_Bc1Bc2CompChk(callId, pstBc1Setup, pstBc2Setup, pstRepeatIndSetup))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : CALL_UpdateCallStateForCallCnf
 功能描述  : 对call confirm消息处理时，刷新呼叫状态。
 输入参数  : callId - 呼叫ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_UpdateCallStateForCallCnf(
    MN_CALL_ID_T                        callId
)
{
    /* 根据当前是否有其它呼叫，设置对应的呼叫状态 */
    if ( VOS_TRUE == MN_CALL_CheckNotIdleStateExist() )
    {
        MN_CALL_UpdateCallState(callId, MN_CALL_S_WAITING);
    }
    else
    {
        MN_CALL_UpdateCallState(callId, MN_CALL_S_INCOMING);
    }

}

/*****************************************************************************
 函 数 名  : CALL_GetDataCfgInfoForCallCnf
 功能描述  : 获取数据业务的配置信息。
 输入参数  : pstBc1CallCnf      - call confirm消息中的Bc1
              pstBc2CallCnf     - call confirm消息中的Bc2
              enCallType        - 呼叫类型
              enCallMode        - 呼叫模式
 输出参数  : pstDataCfgInfo     - 数据业务的配置信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_GetDataCfgInfoForCallCnf(
    NAS_CC_IE_BC_STRU                   *pstBc1CallCnf,
    NAS_CC_IE_BC_STRU                   *pstBc2CallCnf,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{
    /* 获取数据业务的配置信息 */
    if ((MN_CALL_TYPE_CS_DATA == enCallType) || (MN_CALL_TYPE_FAX == enCallType))
    {
        MN_CALL_GetDataCfgInfoFromBc(pstBc1CallCnf, pstDataCfgInfo);
    }
    /* 传真和语音交替，则从BC2中获取 */
    else
    {
        if (( MN_CALL_MODE_AVF == enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2CallCnf)))
        {
            MN_CALL_GetDataCfgInfoFromBc(pstBc2CallCnf, pstDataCfgInfo);
        }
    }

}

/*****************************************************************************
 函 数 名  : CALL_JudgeAllowToSendAlertReq
 功能描述  : 判定是否需要发送Alerting消息
 输入参数  : callId   - 呼叫Id
              pstSetup - MT的setup消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_JudgeAllowToSendAlertReq(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
)
{
    /*
    if 业务信道已建立 或 Setup消息中有signal IE
            发送MNCC_ALERTING_REQ原语
            if 原语发送失败
                输出调试信息, 返回
        else
            设置一个标志表明该呼叫正等待时机发送Alerting消息
    */
    if ((VOS_TRUE == MN_CALL_GetTchStatus()) || (VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stSignal)))
    {
        MN_NORM_LOG("MN_CALL_JudgeAllowToSendAlertReq: ready send alerting.");
        if (VOS_OK != MN_CALL_SendCcAlertReq(callId))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToSendAlertReq: Failed to send Message Alert.");
            MN_CALL_DeleteCallEntity(callId);
            MN_CALL_FreeCallId(callId);
            return VOS_ERR;
        }
        else
        {
            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_ALERTING, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
        }
    }
    else
    {
        MN_NORM_LOG("MN_CALL_JudgeAllowToSendAlertReq: Not ready send alerting.");
        MN_CALL_SetWaitSendAlertStatus(VOS_TRUE, callId);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CALL_SsCdOperationProc
 功能描述  : 更新补充业务CD操作的进展
 输入参数  : callId      - 呼叫Id
             unComponent - 网络回复的component
             enErrcode   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsCdOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_DEFLECT_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                                       enErrcode);
    }
}

/*****************************************************************************
 函 数 名  : CALL_SsSplitMptyOperationProc
 功能描述  : 更新补充业务Split Mpty操作的进展
 输入参数  : callId         - 呼叫Id
              unComponent   - 网络回复的component
              enErrcode     - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月23日
    作    者   : 黎客来 130025
    修改内容   : 问题单号:AT2D04596
  3.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
  4.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsSplitMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT16                          i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /*更新该呼叫的MPTY状态为不在MPTY中*/
        MN_CALL_UpdateMptyState(callId, MN_CALL_NOT_IN_MPTY);
        MN_CALL_UpdateCallState(callId, MN_CALL_S_ACTIVE);

        MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfCalls, aCallIds);
        /*将当前MPTY中的呼叫状态置为hold状态*/
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_HELD);
        }
        /* 给AT模块上报MN_CALL_EVT_HOLD事件 */
        MN_CALL_ReportHoldEvent(MN_CLIENT_ALL, (VOS_UINT8)ulNumOfCalls, aCallIds);

        /*更新补充业务操作的进展*/
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,
                                       enErrcode);
    }
    else
    {
        /*更新补充业务操作的进展*/
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                                       enErrcode);
    }

}

/*****************************************************************************
 函 数 名  : CALL_SsHoldMptyOperationProc
 功能描述  : 更新补充业务Hold Mpty操作的进展
 输入参数  : callId      - 呼叫Id
             unComponent - 网络回复的component
             enErrcode   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
  3.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  4.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目，多方通话被保持，释放DTMF缓存
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsHoldMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT16                          i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /*更新当前所有在MPTY中的呼叫的呼叫状态为HELD*/
        MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfCalls, aCallIds);
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_HELD);
        }

        /* 给AT模块上报MN_CALL_EVT_HOLD事件 */
        MN_CALL_ReportHoldEvent(MN_CLIENT_ALL, (VOS_UINT8)ulNumOfCalls, aCallIds);

        /* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_ON_HOLD);
        /* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_HOLD_REJ,
                                       enErrcode);
    }

}

/*****************************************************************************
 函 数 名  : CALL_SsHoldMptyOperationProc
 功能描述  : 更新补充业务Retrieve Mpty操作的进展
 输入参数  : callId      - 呼叫Id
             unComponent - 网络回复的component
             enErrcode   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
  3.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsRetrieveMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT16                          i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /* 更新当前所有在MPTY中的呼叫的呼叫状态为ACTIVE */
        MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfCalls, aCallIds);
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_ACTIVE);
        }

        /* 给AT模块上报MN_CALL_EVT_RETRIEVE事件 */
        MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, (VOS_UINT8)ulNumOfCalls, aCallIds);

        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                       enErrcode);
    }
}

/*****************************************************************************
 函 数 名  : CALL_SsBuildMptyOperationProc
 功能描述  : 更新补充业务Build Mpty操作的进展
 输入参数  : callId      - 呼叫Id
             unComponent - 网络回复的component
             enErrcode   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
  3.日    期   : 2012年11月09日
    作    者   : Y00213812
    修改内容   : DTS2012110809089, 发起多方通话，MN_CALL_S_HELD态的呼叫在恢复时
                 未上报^CCALLSTATE的RETRIEVE
  4.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsBuildMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    VOS_UINT16                          i;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;


    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /* 更新当前所有在MPTY中的呼叫的呼叫状态为MPTY */
        MN_CALL_GetCallInfoList((VOS_UINT8*)&ulNumOfCalls, f_astCallInfos);

        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_GetCallState(f_astCallInfos[i].callId,&enCallState,&enMptyState);

            if (MN_CALL_S_HELD == enCallState)
            {
                /* 给AT模块上报MN_CALL_EVT_RETRIEVE事件 */
                MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, 1, &f_astCallInfos[i].callId);
            }

            if ((MN_CALL_S_INCOMING != enCallState) && (MN_CALL_S_WAITING != enCallState))
            {
               MN_CALL_UpdateMptyState(f_astCallInfos[i].callId, MN_CALL_IN_MPTY);
               MN_CALL_UpdateCallState(f_astCallInfos[i].callId, MN_CALL_S_ACTIVE);
            }
        }
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                                       enErrcode);
    }
}

/*****************************************************************************
 函 数 名  : CALL_SsEctOperationProc
 功能描述  : 更新补充业务Ect操作的进展
 输入参数  : callId      - 呼叫Id
             unComponent - 网络回复的component
             enErrcode   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsEctOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{

    /*更新补充业务操作的进展*/
    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ECT_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ECT_REJ,
                                       enErrcode);
    }
}


/*****************************************************************************
 函 数 名  : CALL_SsGetInvokeId
 功能描述  : 更新补充业务Ect操作的进展
 输入参数  : unComponent - 网络回复的component
 输出参数  : pucInvokeId - Invoke id
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年06月27日
    作    者   : l00171473
    修改内容   : DTS2012082204471, TEQ告警清理, 参数修改为指针
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SsGetInvokeId(
    MN_CALL_SS_COMPONENT_UNION          *punComponent,
    VOS_UINT8                           *pucInvokeId
)
{

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        *pucInvokeId = punComponent->resultComp.ucInvokeId;
    }
    else if (MN_CALL_SS_RETURN_ERROR_TYPE_TAG == punComponent->ucCompType)
    {
        *pucInvokeId = punComponent->errorComp.ucInvokeId;
    }
    else
    {
        *pucInvokeId = punComponent->rejectComp.ucInvokeId;
    }
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcSsFacility
 功能描述  : 处理来自网络的Facility IE
 输入参数  : pstFacIe - 来自网络的Facility IE
             callId   - 呼叫Id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2012年10月22日
    作    者   : l65478
    修改内容   : DTS2012101901424,OPTIONAL项不存在时不能认为解码失败
*****************************************************************************/
VOS_VOID  MN_CALL_ProcSsFacility(
    MN_CALL_ID_T                        callId,
    const NAS_CC_IE_FACILITY_STRU       *pstFacIe
)
{
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT8                           ucOpCode;
    VOS_UINT8                           ucInvokeId;
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    PS_MEM_SET(&unComponent, 0, sizeof(MN_CALL_SS_COMPONENT_UNION));


    enErrcode = MN_CALL_ERR_SS_UNSPECIFIC;

    /* 先对facility的内容进行解码 */
    if (VOS_OK != MN_CALL_FacilityDecode(pstFacIe, &unComponent))
    {
        MN_WARN_LOG("MN_CALL_ProcSsFacility: Facility Decode failed!" );
        return;
    }

    if ((MN_CALL_SS_RETURN_RESULT_TYPE_TAG == unComponent.ucCompType)
      ||(MN_CALL_SS_RETURN_ERROR_TYPE_TAG == unComponent.ucCompType)
      ||(MN_CALL_SS_REJECT_TYPE_TAG == unComponent.ucCompType))
    {
        MN_CALL_SsGetInvokeId(&unComponent, &ucInvokeId);

        if (VOS_TRUE == g_stCallInvokeIdTable[ucInvokeId].bUsed)
        {
            ucOpCode = g_stCallInvokeIdTable[ucInvokeId].ucOperateCode;
            MN_CALL_InvokeId_Free(ucInvokeId);
        }
        else
        {
            MN_ERR_LOG("MN_CALL_ProcSsFacility: Can not find invoke ID.");
            return;
        }
    }
    else
    {
        /*这种情况是invoke这种type，不用考虑异常，如果类型异常，那么
          在调用函数MN_CALL_FacilityDecode的时候已经返回异常了*/
        ucOpCode = unComponent.invokeComp.ucOperateCode;
    }

    /* 如果是return error，那么有对应的error code，使用网络的error code上报*/
    if (MN_CALL_SS_RETURN_ERROR_TYPE_TAG == unComponent.ucCompType)
    {
        enErrcode = unComponent.errorComp.ucErrorCode;
    }

    /* 如果是return reject，那么使用未定义的非特定error code*/
    if (MN_CALL_SS_REJECT_TYPE_TAG == unComponent.ucCompType)
    {
        enErrcode = MN_CALL_ERR_SS_UNSPECIFIC;
    }

    MN_INFO_LOG1("MN_CALL_ProcSsFacility: Operation Code.", ucOpCode);


    switch (ucOpCode)
    {
        case MN_CALL_SS_NOTIFYSS_OPERATION:
            MN_CALL_ProcNotifySs(callId, &unComponent.invokeComp.unArg.notifySsArg);
            break;

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        case MN_CALL_SS_CD_OPERATION:
           if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg )
           {
               /*更新补充业务操作的进展*/
               MN_CALL_SsCdOperationProc(callId, &unComponent, enErrcode);
           }
           break;

        case MN_CALL_SS_REG_CC_ENTRY_OPERATION:
            /*更新补充业务操作的进展*/
            if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                MN_CALL_SsRegCcEntryProc(callId, &unComponent, enErrcode);
            }
            break;
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


        case MN_CALL_SS_SPLITMPTY_OPERATION:
            MN_CALL_SsSplitMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_RETRIEVEMPTY_OPERATION:
            MN_CALL_SsRetrieveMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_HOLDMPTY_OPERATION:
            MN_CALL_SsHoldMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_BUILDMPTY_OPERATION:
            MN_CALL_SsBuildMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_AOC_OPERATION:
            /*AOC的处理，后续再加入*/
            break;

        case MN_CALL_SS_ECT_OPERATION:
            /*更新补充业务操作的进展*/
            MN_CALL_SsEctOperationProc(callId, &unComponent, enErrcode);
            break;

        default:
            MN_WARN_LOG("MN_CALL_ProcSsFacility: Operation Code Error!" );
            break;

    }


}

/*****************************************************************************
 函 数 名  : MN_CALL_NegotBc
 功能描述  : 对cc establishment或setup_ind消息中的BC进行协商
 输入参数  : pMsg           - 消息内容
             ucCallId       - 呼叫ID
             enCallDir      - 呼叫方向
 输出参数  : pstBc1CallCnf  - 回复消息中的BC1
             pstBc2CallCnf  - 回复消息中的BC2
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010-5-24
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_NegotBc(
    VOS_VOID                            *pMsg,
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_IE_BC_STRU                   *pstBc1CallCnf,
    NAS_CC_IE_BC_STRU                   *pstBc2CallCnf,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    MNCC_MSG_EST_STRU                   *pstCcEstInd;
    NAS_CC_MSG_SETUP_MT_STRU            *pstMtSetup;
    NAS_CC_IE_BC_STRU                   *pstBc1;
    NAS_CC_IE_BC_STRU                   *pstBc2;

    /* CCBS和普通呼叫，数据结构定义不同，所以取的BC来自不同的数据结构定义 */
    if (MN_CALL_DIR_CCBS == enCallDir)
    {
        pstCcEstInd = (MNCC_MSG_EST_STRU *)pMsg;
        pstBc1 = &pstCcEstInd->stSetupContainer.stSetup.stBC1;
        pstBc2 = &pstCcEstInd->stSetupContainer.stSetup.stBC2;
    }
    else
    {
        pstMtSetup = (NAS_CC_MSG_SETUP_MT_STRU *)pMsg;
        pstBc1 = &pstMtSetup->stBC1;
        pstBc2 = &pstMtSetup->stBC2;
    }

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1))
    {
        if (VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2))
        {
            /* BC1不存在的时候，BC2的协商结果作为call confirm中的BC1*/
            if ( VOS_FALSE == MN_CALL_NegotBcForCallConf(pstBc2,pstBc1CallCnf))
            {
                NAS_IE_SET_ABSENT(pstBc1CallCnf);
                NAS_IE_SET_ABSENT(pstBc2CallCnf);
            }
            else
            {
                NAS_IE_SET_PRESENT(pstBc1CallCnf);
            }
        }
    }
    else
    {
        /* 进行BC1协商 */
        if (VOS_FALSE == MN_CALL_NegotBcForCallConf(pstBc1,pstBc1CallCnf))
        {
            NAS_IE_SET_ABSENT(pstBc1CallCnf);
        }

        /* 进行BC2协商 */
        if (VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2))
        {
            if (VOS_FALSE == MN_CALL_NegotBcForCallConf(pstBc2,pstBc2CallCnf))
            {
                NAS_IE_SET_ABSENT(pstBc2CallCnf);
                if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1CallCnf))
                {
                    /*BC1和BC2协商都不成功的话，回复release complete*/
                    MN_CALL_SendCcRejReq(ucCallId, MN_CALL_INCOMPATIBLE_DESTINATION);
                    MN_WARN_LOG("MN_CALL_NegotBc: negotiation BC fail" );
                    MN_CALL_FreeCallId(ucCallId);
                    MN_CALL_DeleteCallEntity(ucCallId);
                    return VOS_ERR;
                }
            }
            else
            {
                /* BC1不存在的时候，将协商出的BC2当作BC1来使用 */
                if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1CallCnf))
                {

                    PS_MEM_CPY(pstBc1CallCnf, pstBc2CallCnf, sizeof(NAS_CC_IE_BC_STRU));

                    NAS_IE_SET_PRESENT(pstBc1CallCnf);
                }
            }
        }
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccDisIndWithCcbs
 功能描述  : MNCC_DISC_IND原语中disconnect消息中带CCBS激活相关信息的处理
 输入参数  : pstDisc    - 通过MNCC_DISC_IND原语收到的disconnect消息
             ucCallId   - 呼叫ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :2009-12-24
    作    者   :z00161729
    修改内容   : 新生成函数
*****************************************************************************/

LOCAL VOS_VOID MN_CALL_ProcMnccDisIndWithCcbs(
    const NAS_CC_MSG_DISCONNECT_MT_STRU    *pstDisc,
    VOS_UINT8                               ucCallId
)
{
    if ((VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stCause))
     && (CCA_SS_DIAG_CCBS_POSSIBLE == (pstDisc->stCause.diagnostic[0] & 0x7))
     && (VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stAllowedAct))
     && (NAS_CCBS_ACTIVATION_POSSIBLE == pstDisc->stAllowedAct.Octet3.CCBSActivation))
    {
        MN_CALL_UpdateCallState(ucCallId, MN_CALL_S_CCBS_WAITING_ACTIVE);
        MN_CALL_ReportEvent(ucCallId,MN_CALL_EVT_CCBS_POSSIBLE);
    }

}

/*****************************************************************************
 函 数 名  : MN_CALL_CcbsProcMnccRelCnf
 功能描述  : 用户选择CCBS激活收到MNCC_REL_CNF原语但没有带facility时的处理
             或CCBS回呼用户没有响应超时收到MNCC_REL_CNF原语时的处理
 输入参数  : enCallState    - 呼叫状态
             ucCallId       - 呼叫ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :2009-12-24
    作    者   :z00161729
    修改内容   : 新生成函数
*****************************************************************************/

LOCAL VOS_VOID MN_CALL_CcbsProcMnccRelCnf(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT8                           ucCallId
)
{
    if (MN_CALL_S_CCBS_WAITING_ACTIVE == enCallState)
    {
        MN_CALL_UpdateCallSupsProgress(ucCallId,
                                       MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                                       MN_CALL_ERR_SS_UNSPECIFIC);
    }
    else if (MN_CALL_S_CCBS_WAITING_RECALL == enCallState)
    {
        /* 判断是否已经存在有呼叫相关补充业务 */
        if (VOS_FALSE == MN_CALL_IsCallSupsCmdInProgress())
        {
           MN_CALL_UpdateCcbsSupsProgress(ucCallId,
                                          MN_CALL_ERR_SS_UNSPECIFIC,
                                          MN_CALL_SS_RES_FAIL);
        }
    }
    else
    {
        ;
    }

}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccEstInd
 功能描述  : 处理MNCC_CC_EST_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MN_CALL_ProcMnccEstInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{

    MNCC_MSG_EST_STRU                   *pstCcEstInd;
    MN_CALL_ID_T                        callId;
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd;
    NAS_CC_IE_BC_STRU                   stBc1CcEstCnf;
    NAS_CC_IE_BC_STRU                   stBc2CcEstCnf;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    MN_CALL_BCD_NUM_STRU                stNumber;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;

    enCause = MN_CALL_INVALID_CAUSE;
    enCallType = MN_CALL_TYPE_VOICE;
    enCallMode = MN_CALL_MODE_SINGLE;
    pstCcEstInd = VOS_NULL_PTR;


    callId = 0;

    MN_CALL_ASSERT( VOS_TRUE != MN_CALL_TiUsedCheck(pstMsg->ucTi) );

    PS_MEM_SET(&stDataCfgInfo, 0, sizeof(stDataCfgInfo));
    PS_MEM_SET(&stNumber, 0, sizeof(stNumber));
    PS_MEM_SET(&stBc1CcEstCnf, 0, sizeof(stBc1CcEstCnf));
    PS_MEM_SET(&stBc2CcEstCnf, 0, sizeof(stBc2CcEstCnf));

    pstCcEstInd = (MNCC_MSG_EST_STRU*)&(pstMsg->unParam.stEstInd);
    /* 分配 Call Id */
    (VOS_VOID)MN_CALL_AllocCallId(&callId);

    /* 新建呼叫实体,填写初始的呼叫信息,有些信息属于默认值，后面再刷新 */
    MN_CALL_CreateCallEntity(callId, pstMsg->ucTi, MN_CLIENT_ALL,
                             enCallType, enCallMode,
                             MN_CALL_DIR_CCBS, &stDataCfgInfo,
                             &stNumber);

    MN_NORM_LOG1("MN_CALL_ProcMnccEstInd: call id, ", callId);

    /*对cc establishment消息中的BC进行检查*/
    if (VOS_OK != MN_CALL_BcChkForCallCnf(&pstCcEstInd->stSetupContainer.stSetup,
                                          &stBc1CcEstCnf,
                                          &stBc2CcEstCnf,
                                          &enRepeatInd,
                                          MN_CALL_DIR_CCBS,
                                          callId,
                                          &stDataCfgInfo))
    {
        return;
    }

    /* 判定呼叫类型和呼叫模式 */
    if (VOS_OK != MN_CALL_JudgeMtCallType(
                        &pstCcEstInd->stSetupContainer.stSetup.stBC1.Octet3,
                        &pstCcEstInd->stSetupContainer.stSetup.stBC1.Octet5a,
                        &enCallType))
    {
        MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }

    if (VOS_OK != MN_CALL_JudgeMtCallMode(
                        &pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd,
                        &pstCcEstInd->stSetupContainer.stSetup.stBC1,
                        &pstCcEstInd->stSetupContainer.stSetup.stBC2,
                        &enCallMode))
    {
        MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }

    /*由于实体在之前创建，需要刷新呼叫模式和呼叫类型*/
    MN_CALL_UpdateCallMode(callId, enCallMode);
    MN_CALL_UpdateCallType(callId, enCallType);

    /*对通过检查的BC进行协商, 得到需要携带在CC establishment confirm消息中的BC*/
    /* 目前不支持单号码方案，在前面已经返回，因此在此处，暂不处理BC1
           不存在的情况，以后再定 */
    if (VOS_OK != MN_CALL_NegotBc(pstCcEstInd, callId, &stBc1CcEstCnf,
                                  &stBc2CcEstCnf,MN_CALL_DIR_CCBS))
    {
        return;
    }

    /* 获取数据业务的配置信息 */
    MN_CALL_GetDataCfgInfoForCallCnf(&stBc1CcEstCnf,&stBc2CcEstCnf,enCallType,
                                     enCallMode,&stDataCfgInfo);

    MN_CALL_UpdateDataCallCfgInfo(callId, &stDataCfgInfo);

    /* 当前已有其它呼叫, cause值设为 user busy*/
    if ( VOS_TRUE == MN_CALL_CheckNotIdleStateExist() )
    {
        enCause = MN_CALL_USER_BUSY;
    }

    /* 对回复的RepeatInd进行赋值 */
    /*enRepeatInd = (VOS_FALSE == NAS_IE_IS_PRESENT(&pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd))?\
                  (VOS_UINT8)MN_CALL_REP_IND_NULL:pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd.RepeatIndication;*/
    if ((VOS_TRUE == NAS_IE_IS_PRESENT(&stBc1CcEstCnf))
     && (VOS_TRUE == NAS_IE_IS_PRESENT(&stBc2CcEstCnf)))
    {
        enRepeatInd = pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd.RepeatIndication;
    }
    else
    {
        enRepeatInd = MN_CALL_REP_IND_NULL;
    }
    /*回复cc establishment confirm消息*/
    if ( VOS_OK != MN_CALL_SendCcEstCnfReq(callId, enRepeatInd,
                                           &stBc1CcEstCnf, &stBc2CcEstCnf, enCause))
    {
        MN_WARN_LOG("MN_CALL_SendCcEstCnfReq: Failed to send Message cc Establishment cnf.");
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }
    PS_MEM_CPY(&pstCcEstInd->stSetupContainer.stSetup.stBC1,
               &stBc1CcEstCnf,
               sizeof(stBc1CcEstCnf));
    PS_MEM_CPY(&pstCcEstInd->stSetupContainer.stSetup.stBC2,
               &stBc2CcEstCnf,
               sizeof(stBc2CcEstCnf));

    if (MN_CALL_REP_IND_NULL != enRepeatInd)
    {
        NAS_IE_SET_PRESENT(&pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd);
        pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd.RepeatIndication
                        = enRepeatInd;
    }
    else
    {
        NAS_IE_SET_ABSENT(&pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd);
    }
    MN_CALL_UpdateCcbsSetup(&pstCcEstInd->stSetupContainer.stSetup);


    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstCcEstInd->stSetupContainer.stSetup.stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(callId,
                               (NAS_CC_IE_FACILITY_STRU*)&pstCcEstInd->stSetupContainer.stSetup.stFacility);
    }
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRecallInd
 功能描述  : 处理MNCC_RECALL_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRecallInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{

    /*更新状态,以便用户选择接受回呼或拒绝回呼后,可以根据MN_CALL_S_CCBS_WAITING_RECALL找到相应的CallId*/
    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_CCBS_WAITING_RECALL);

    /* 处理呼叫相关补充业务 */
    MN_CALL_ProcSsFacility(pstMsg->ucCallId,
                           (NAS_CC_IE_FACILITY_STRU*)&pstMsg->unParam.stRecall.stFacility);

}
/*****************************************************************************
 函 数 名  :  MN_CALL_CheckNvAllowMtCall
 功能描述  : 检查NV配置项是否允许被叫
 输入参数  : ucCallType     - 呼叫类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月19日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE

  3.日    期   : 2013年10月24日
    作    者   : z00234330
    修改内容   : DTS2013101201412
  4.日    期   : 2013年12月09日
    作    者   : f62575
    修改内容   : DTS2013120411878，终端不支持VOICE/VIDEO CALL，回复RELEASE COMPLETE
消息原因定制值
  4.日    期   : 2014年05月12日
    作    者   : y00245242
    修改内容   : eCall feature修改
  5.日    期   : 2014年6月24日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
VOS_BOOL MN_CALL_CheckNvAllowMtCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT8                            ucTafMultiSimCallStatusControl;
    VOS_UINT8                            enVpNvCfgState;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();


    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-5-12, begin */
    /* 删除对cause值初始化操作 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-5-12, end */

    /* VSIM的MODEM且NAS的VSIM特性开关打开，则拒绝接受被叫业务 */
    if (VOS_TRUE == NAS_VSIM_IsRequireVsimCtrl())
    {
        *penCause = MN_CALL_USER_BUSY;
        return VOS_FALSE;
    }

    /*增加判断如果NV项开启存在呼叫状态为incoming且呼叫子状态为
      TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK的呼叫则返回VOS_FALSE，
      不允许新的被叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    enCallSubState = TAF_CALL_GetCallSubState(aCallIds[0]);

    if ((VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
     && (0 != ulNumOfCalls)
     && (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == enCallSubState))
    {
        return VOS_FALSE;
    }

    /* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */
    ucTafMultiSimCallStatusControl = TAF_CALL_GetMultiSimCallStatusControl();
    enVpNvCfgState                 = TAF_CALL_GetVpCfgState();
    /* Voice类型的呼叫，使用的是gucTafCallStatusControl和gucTafMultiSimCallStatusControl这两个NV项的值 */
    if (MN_CALL_TYPE_VOICE == enCallType)
    {

        if ((VOS_TRUE == TAF_CALL_GetCallStatusControl())
            ||(VOS_TRUE == ucTafMultiSimCallStatusControl))
        {
            return VOS_TRUE;
        }


        *penCause = pstCustomCfg->ucVoiceCallNotSupportedCause;

        return VOS_FALSE;
    }
    else if (MN_CALL_TYPE_VIDEO == enCallType)
    {
        /* 可视电话NV项的判断，判定双向和MT的情况返回VOS_TRUE */
        if (( MN_CALL_VP_MO_MT_BOTH == enVpNvCfgState )
         || ( MN_CALL_VP_MT_ONLY == enVpNvCfgState ))
        {
            return VOS_TRUE;
        }

        *penCause = pstCustomCfg->ucVideoCallNotSupportedCause;

        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }

    /* Modified by z00234330 for PCLINT清理, 2014-07-03, end */

}

/*****************************************************************************
 函 数 名  : TAF_CALL_IsMtCallAllowed
 功能描述  : 检查MT eCall是否允许发起
 输入参数  : pstSetup - MT setup消息
             ucCallId - 呼叫标识

 输出参数  : penCause - 返回呼叫不允许原因值
 返 回 值  : VOS_TRUE  -- 允许发起
             VOS_FALSE -- 不允许发起
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsMtCallAllowed(
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup,
    VOS_UINT8                           ucCallId,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT                            i;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_VOICE;
    MN_CALL_MODE_ENUM_U8                enCallMode = MN_CALL_MODE_SINGLE;
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8    enCcwaCtrlMode;
    VOS_UINT8                           ucCcwaiFlg;

    enCcwaCtrlMode = TAF_CALL_GetCcwaCtrlMode();
    ucCcwaiFlg     = TAF_CALL_GetCcwaiFlg();

   /*查找是否有正在通话的呼叫，如果有正在进行的可视电话，则不允许接收另一个呼叫*/
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    for (i = 0; i < ulNumOfCalls; i++)
    {
        if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(aCallIds[i]))
        {
            *penCause = MN_CALL_USER_BUSY;

            return VOS_FALSE;
        }
    }

    if ((ulNumOfCalls > 0)
     && (TAF_CALL_CCWA_CTRL_BY_IMS == enCcwaCtrlMode)
     && (VOS_FALSE == ucCcwaiFlg))
    {
        *penCause = MN_CALL_USER_BUSY;

        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsEcallRedialExist())
    {
        *penCause = MN_CALL_USER_BUSY;

        return VOS_FALSE;
    }
#endif

    /* 判定呼叫类型和呼叫模式 */
    if (VOS_OK != MN_CALL_JudgeMtCallType(&pstSetup->stBC1.Octet3,
                                          &pstSetup->stBC1.Octet5a,
                                          &enCallType))
    {
        *penCause = MN_CALL_INCOMPATIBLE_DESTINATION;

        return VOS_FALSE;
    }

    /*判断是否允许做被叫*/
    if (VOS_FALSE == MN_CALL_CheckNvAllowMtCall(enCallType, penCause))
    {
        return VOS_FALSE;
    }

    if (VOS_OK != MN_CALL_JudgeMtCallMode(&pstSetup->stBCRepeatInd,
                                          &pstSetup->stBC1,
                                          &pstSetup->stBC2,
                                          &enCallMode))
    {

        *penCause = MN_CALL_INCOMPATIBLE_DESTINATION;

        return VOS_FALSE;
    }

    /*由于实体在之前创建，需要刷新呼叫模式和呼叫类型*/
    MN_CALL_UpdateCallMode(ucCallId, enCallMode);
    MN_CALL_UpdateCallType(ucCallId, enCallType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSetupInd
 功能描述  : 处理MNCC_SETUP_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2009年5月20日
    作    者   : h44270
    修改内容   : 问题单号A32D14863，在中国移动的网络下（G网），被叫单板，来电接不起来。

  3.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 支持ALS多线路
  4.日    期   : 2010年07月20日
    作    者   : h44270
    修改内容   : 问题单号： DTS2010071902031
  5.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  6.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  7.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
  8.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  9.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
 10.日    期   : 2013年3月7日
    作    者   : w00176964
    修改内容   : DTS2013030606529:TD下,网测下发connect消息,RB未建好,此时上报RING
                 用户接听可能会失败,此处进行规避延长TD下的RING上报时机
 12.日    期   : 2013年9月4日
    作    者   : w00167002
    修改内容   : DTS2013090403562:NAS定时器清理，需要启动32K定时器。将MM/MMA/SMS/cc
                模块的循环定时器修改为非循环定时器。

 13.日    期   : 2013年10月24日
    作    者   : z00234330
    修改内容   : DTS2013101201412

 14.日    期   : 2013年12月28日
    作    者   : j00174725
    修改内容   : HSUART PHASE III
 15.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
 16.日    期   : 2014年6月11日
    作    者   : y00245242
    修改内容   : DTS2014060306029
 17.日    期   : 2015年7月7日
    作    者   : zwx247453
    修改内容   : CHR 优化项目
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    NAS_CC_MSG_SETUP_MT_STRU            *pstSetup = VOS_NULL_PTR;
    MN_CALL_ID_T                        callId;
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd;
    NAS_CC_IE_BC_STRU                   stBc1CallCnf;
    NAS_CC_IE_BC_STRU                   stBc2CallCnf;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause = MN_CALL_INVALID_CAUSE;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_VOICE;
    MN_CALL_MODE_ENUM_U8                enCallMode = MN_CALL_MODE_SINGLE;
    MN_CALL_BCD_NUM_STRU                stNumber;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_INFO_STRU                   stCallInfo;

    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    VOS_BOOL                            bWaitSendAlertStatus;
    MN_CALL_ID_T                        ucCallId;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    callId = 0;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    MN_CALL_ASSERT( VOS_TRUE != MN_CALL_TiUsedCheck(pstMsg->ucTi) );

    PS_MEM_SET(&stDataCfgInfo, 0, sizeof(stDataCfgInfo));
    PS_MEM_SET(&stNumber, 0, sizeof(stNumber));
    PS_MEM_SET(&stBc1CallCnf, 0, sizeof(stBc1CallCnf));
    PS_MEM_SET(&stBc2CallCnf, 0, sizeof(stBc2CallCnf));
    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));

    pstSetup = (NAS_CC_MSG_SETUP_MT_STRU*)&(pstMsg->unParam.stSetup);

    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
    /* 下移重拨缓存处理到MT呼叫检查完成后 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */

    /* 分配 Call Id */
    (VOS_VOID)MN_CALL_AllocCallId(&callId);

    /* 新建呼叫实体,填写初始的呼叫信息,将空口的号码结构转换成API要求的结构，有些信息属于默认值，后面再刷新 */
    MN_CALL_CreateMtCallEntity(callId, pstMsg->ucTi, pstSetup);

    MN_NORM_LOG1("MN_CALL_ProcMnccSetupInd: call id, ", callId);

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
    /*对call confirm消息中的BC进行检查*/
    if (VOS_OK != MN_CALL_BcChkForCallCnf(pstSetup,
                                      &stBc1CallCnf,
                                      &stBc2CallCnf,
                                      &enRepeatInd,
                                      MN_CALL_DIR_MT,
                                      callId,
                                      &stDataCfgInfo))
    {

#if (FEATURE_ON == FEATURE_PTM)
        /* setup消息按协议检查失败的异常记录 */
        MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_BC_CHECK_FAIL);
#endif

        return;
    }

    if (VOS_FALSE == TAF_CALL_IsMtCallAllowed(pstSetup, callId, &enCause))
    {
        MN_CALL_SendCcRejReq(callId, enCause);
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);

#if (FEATURE_ON == FEATURE_PTM)
        /* setup消息按协议检查失败的异常记录 */
        MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_MT_CALL_NOT_ALLOW);
#endif

        return;
    }

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    /* 如果呼叫重发间隔定时器在运行，且有缓存的mncc rej ind消息则上报呼叫失败，
       不再进行重发，响应被叫*/
    MN_CALL_GetCallState(pstBufferdMsg->stBufferedSetupMsg.ucCallId, &enCallState, &enMptyState);

    if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
     && (MN_CALL_S_DIALING           == enCallState))
    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
        TAF_CALL_StopAllRedialTimers(pstBufferdMsg->stBufferedSetupMsg.ucCallId);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */

        if (VOS_TRUE == pstBufferdMsg->bitOpBufferedRejIndMsg)
        {
            TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg,
                pstBufferdMsg->stBufferedRejIndMsg.unParam.enCause);
        }
        else if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
        {
            TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg,
                TAF_CS_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
        }
        else
        {
            ;
        }
    }
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */

    /*对通过检查的BC进行协商, 得到需要携带在Call Confirm消息中的BC*/
    /* 目前不支持单号码方案，在前面已经返回，因此在此处，暂不处理BC1
       不存在的情况，以后再定 */
    if (VOS_OK != MN_CALL_NegotBc(pstSetup, callId, &stBc1CallCnf,
                                  &stBc2CallCnf,MN_CALL_DIR_MT))
    {
        /*BC1和BC2协商均失败*/

#if (FEATURE_ON == FEATURE_PTM)
        /* setup消息按协议检查失败的异常记录 */
        MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_NE_GET_BC_FAIL);
#endif

        return;
    }

    /* 获取数据业务的配置信息 */
    MN_CALL_GetDataCfgInfoForCallCnf(&stBc1CallCnf,&stBc2CallCnf,enCallType,enCallMode,&stDataCfgInfo);

    MN_CALL_UpdateDataCallCfgInfo(callId, &stDataCfgInfo);

    /* 当前已有其它呼叫, cause值设为 user busy*/
    if ( VOS_TRUE == MN_CALL_CheckNotIdleStateExist() )
    {
        enCause = MN_CALL_USER_BUSY;
    }

    /* 对回复的RepeatInd进行赋值 */
    enRepeatInd = (VOS_FALSE == NAS_IE_IS_PRESENT(&pstSetup->stBCRepeatInd))?\
            (VOS_UINT8)MN_CALL_REP_IND_NULL:pstSetup->stBCRepeatInd.RepeatIndication;



    /* 回复call confirm */
    if ( VOS_OK != MN_CALL_SendCcCallConfReq(callId, enRepeatInd,
                                             &stBc1CallCnf, &stBc2CallCnf, enCause))
    {
        MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: Failed to send Message CallConf.");
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_ATTEMPT, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-6-12, begin */
    /* 此处处理下移到后面处理 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-6-12, end */

    /*刷新当前的呼叫状态*/
    MN_CALL_UpdateCallStateForCallCnf(callId);


    /* 如果Setup消息中没有对方号码，更新呼叫管理模块中保存的NoCliCause */
    if (VOS_FALSE == NAS_IE_IS_PRESENT(&pstSetup->stCallingNum))
    {
        MN_CALL_UpdateNoCliCause(callId, MN_CALL_NO_CLI_USR_REJ);
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        /* 广播来电(INCOMING)事件,需要区分是线路1的来电还是线路2的来电 */
        if ( (VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stBC1))
          && (NAS_CC_ITC_AUXILIARY_SPEECH == pstSetup->stBC1.Octet3.InfoTransCap))
        {
            MN_CALL_UpdateAlsLineNbr(callId, MN_CALL_ALS_LINE_NO_2);
        }
        else
        {
            MN_CALL_UpdateAlsLineNbr(callId, MN_CALL_ALS_LINE_NO_1);
        }

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 此处删除dts2013030606529的修改，统一在alert请求发送给网络后, 上报INCOMING
     * 事件，同时启动RING定时器
     */
    if (VOS_OK != MN_CALL_JudgeAllowToSendAlertReq(callId, pstSetup))
    {
        return;
    }

    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucCallId);

    if (VOS_FALSE == bWaitSendAlertStatus)
    {
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_INCOMING);

        MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);
    }

    MN_CALL_SndStkMtCallEvent(callId, pstMsg->ucTi);


    MN_CALL_GetCallInfoByCallId(callId, &stCallInfo);

    /* 在CALL发送Alert req后，启动RING定时器, 删除此处逻辑 */

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(callId, (NAS_CC_IE_FACILITY_STRU*)&pstSetup->stFacility);
    }

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(callId,NAS_CC_MSG_SETUP,&pstSetup->stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_UUS1_INFO);
    }

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-5-27, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
    {
        /* 如果T9定时器在运行，更新呼叫类型为PSAP回呼eCall类型 */
        MN_CALL_UpdateCallType(callId, MN_CALL_TYPE_PSAP_ECALL);
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-5-27, end */

}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSetupCnf
 功能描述  : 处理MNCC_SETUP_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年07月20日
    作    者   : h44270
    修改内容   : 问题单号： DTS2010071902031
  3.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  6.日    期   : 2014年2月19日
    作    者   : s00217060
    修改内容   : coverity清理
  7.日    期   : 2014年4月2日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  8.日    期   : 2015年8月14日
    作    者   : s00217060
    修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_CONNECT_MT_STRU    *pstConn;
    MN_CALL_BCD_NUM_STRU                stConnNumber;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    /* Added by s00217060 for coverity清理, 2014-02-17, begin */
    PS_MEM_SET(&stConnNumber, 0, sizeof(MN_CALL_BCD_NUM_STRU));
    /* Added by s00217060 for coverity清理, 2014-02-17, end */

    /* 获取当前呼叫状态*/
    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( (MN_CALL_S_DIALING == enCallState)
              || (MN_CALL_S_ALERTING == enCallState));

    pstConn = &pstMsg->unParam.stConn;

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstConn->stConnectedNum))
    {
        /* 更新呼叫信息中的Connect number */
        stConnNumber.ucNumLen =
            (VOS_UINT8)NAS_IE_GET_BLOCK_SIZE(&pstConn->stConnectedNum, BCDNum);
        PS_MEM_CPY(stConnNumber.aucBcdNum,
                   pstConn->stConnectedNum.BCDNum,
                   stConnNumber.ucNumLen);

        stConnNumber.enNumType = *((VOS_UINT8*)&pstConn->stConnectedNum.Octet3);

        MN_CALL_UpdateConnNumber(pstMsg->ucCallId, &stConnNumber);
    }

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ACTIVE);

    /* 通知call status nty */
    TAF_CALL_SendCcCallStatusNty(pstMsg->ucCallId, MNCC_CALL_STATUS_SETUP_SUCC);


    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (pstMsgBuff->stBufferedSetupMsg.ucCallId == pstMsg->ucCallId))

    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(pstMsg->ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(pstMsg->ucCallId);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
    }
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */

    /*如果是可视电话，通知CST模块建立通道*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        MN_CALL_SendCstSetupReqMsg(pstMsg->ucCallId);
        MN_CALL_StartTimer(MN_CALL_TID_WAIT_CST_SETUP, 0, 0, VOS_RELTIMER_NOLOOP);
    }

    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
            /* 发送消息通知VC打开语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
            TAF_CALL_SetSrvccLocalAlertedFlagByCallId(pstMsg->ucCallId, VOS_FALSE);
        }
    }
    MN_CALL_StartFluxCalculate(pstMsg->ucCallId);
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CONNECT);

    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MO_ANSWERED, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateTi(pstMsg->ucCallId, pstMsg->ucTi);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstConn->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstConn->stFacility);
    }

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstConn->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,NAS_CC_MSG_CONNECT,(NAS_CC_IE_USER_USER_STRU*)&pstConn->stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    MN_CALL_SndStkCallConnEvent(pstMsg->ucTi, MN_CALL_DIR_MO);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* 增加eCall处理相关*/
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        /* 启动T2定时器 */
        MN_CALL_StartTimer(TAF_CALL_TID_T2, 0, 0, VOS_RELTIMER_NOLOOP);

        /* 发送MN_CALL_EVT_CHANNEL_CONNECT通知VC，可以进行MSD传输 */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CONNECT);

        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* 设置等待MT eCall标志 */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALl_VoicePreferJudgeVoiceCallExist();
#endif
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSetupComplInd
 功能描述  : 处理MNCC_SETUP_COMPL_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2009年01月29日
    作    者   : x00115505
    修改内容   : GCF用例26.8.1.3.5.3 Fail,呼叫过程中挂不断电话
  3.日    期   : 2010年05月07日
    作    者   : z00161729
    修改内容   : 修改问题单AT2D19199,修改上报MN_CALL_EVT_CONNECT事件的限制条件
  4.日    期   : 2010年07月20日
    作    者   : h44270
    修改内容   : 问题单号： DTS2010071902031
  5.日    期   : 2012年11月09日
    作    者   : Y00213812
    修改内容   : DTS2012110501198, 发起多方通话，主叫未上报^CCALLSTATE状态
  6.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  7.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
  8.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  9.日    期   : 2014年6月24日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
VOS_VOID MN_CALL_ProcMnccSetupComplInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfCalls;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;
    VOS_UINT32                          ulLength;

    ulLength               = 0;
    enCallState            = MN_CALL_S_BUTT;
    enMptyState            = MN_CALL_MPYT_STATE_BUTT;
    ulNumOfCalls           = 0;
    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ACTIVE);

    /* 通知call status nty */
    TAF_CALL_SendCcCallStatusNty(pstMsg->ucCallId, MNCC_CALL_STATUS_SETUP_SUCC);


    /* 清除incoming状态的呼叫子状态为null */
    TAF_CALL_SetCallSubState(pstMsg->ucCallId, TAF_CALL_SUB_STATE_NULL);

    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
            /* 发送消息通知VC打开语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_ANSWERED, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* 更新补充业务操作的进展(CCA_SS_PROG_EVT_SETUP_COMPL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);
    /*获取当前存在呼叫的个数,等于1的情况下才需上报MN_CALL_EVT_CONNECT事件*/
    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (1 == ulNumOfCalls)
    {
        /*如果是可视电话，通知CST模块建立通道*/
        if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
        {
            MN_CALL_SendCstSetupReqMsg(pstMsg->ucCallId);
            MN_CALL_StartTimer(MN_CALL_TID_WAIT_CST_SETUP, 0, 0, VOS_RELTIMER_NOLOOP);
        }
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CONNECT);
    }
    /* 为了避免影响MBB产品线(不能确定是否影响)，只上报一次^CONN和^CCALLSTATE */
    else
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

        if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                             &stSysAppConfig, ulLength))
        {
            stSysAppConfig.usSysAppConfigType = SYSTEM_APP_MP;
            MN_WARN_LOG("MN_CALL_ProcMnccSetupComplInd():Read en_NV_Item_System_APP_Config Failed!");
        }

        if (SYSTEM_APP_ANDROID == stSysAppConfig.usSysAppConfigType)
        {
            MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CONNECT);
        }
    }
    MN_CALL_StartFluxCalculate(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALl_VoicePreferJudgeVoiceCallExist();
#endif

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* 增加eCall处理相关*/
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
    {
        /* 停止T9定时器 */
        MN_CALL_StopTimer(TAF_CALL_TID_T9);

        /* 启动T2定时器 */
        MN_CALL_StartTimer(TAF_CALL_TID_T2, 0, 0, VOS_RELTIMER_NOLOOP);

        /* 发送CALL_VC_CHANNEL_CONNECT通知VC，可以进行MSD传输 */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CONNECT);

        /* 更新呼叫类型为PSAP回呼 */
        MN_CALL_UpdateCallType(pstMsg->ucCallId, MN_CALL_TYPE_PSAP_ECALL);
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccCallProcInd
 功能描述  : 处理MNCC_CALL_PROC_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  3.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccCallProcInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    NAS_CC_MSG_CALL_PROC_STRU           *pstCallProc;
    MN_CALL_MODE_ENUM_U8                enCallMode = MN_CALL_MODE_SINGLE;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_VOICE;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_INFO_STRU                   stCallInfo;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);
    MN_CALL_UpdateTi(pstMsg->ucCallId, pstMsg->ucTi);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    pstCallProc = (NAS_CC_MSG_CALL_PROC_STRU*)&pstMsg->unParam.stCallProc;

    MN_CALL_GetCallInfoByCallId(pstMsg->ucCallId, &stCallInfo);
    enCallType = stCallInfo.enCallType;
    enCallMode = stCallInfo.enCallMode;

    /* 判定呼叫类型和呼叫模式，进行刷新 */
    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stBC1))
    {
        if (VOS_OK == MN_CALL_JudgeMtCallType(&pstCallProc->stBC1.Octet3,
                                           &pstCallProc->stBC1.Octet5a,
                                           &enCallType))
        {
            MN_CALL_UpdateCallType(pstMsg->ucCallId, enCallType);
        }
    }

    if (VOS_OK == MN_CALL_JudgeMtCallMode(&pstCallProc->stRepeatInd,
                                       &pstCallProc->stBC1,
                                       &pstCallProc->stBC2,
                                       &enCallMode))
    {
        MN_CALL_UpdateCallMode(pstMsg->ucCallId, enCallMode);
    }


    /*获取指定呼叫的数据呼叫配置信息*/
    MN_CALL_GetDataCallCfgInfo(pstMsg->ucCallId, &stDataCfgInfo);
    /* 数据呼叫，从BC1中取速度 */
    if (((MN_CALL_TYPE_CS_DATA == enCallType) || (MN_CALL_TYPE_FAX == enCallType))
      &&(VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stBC1)))
    {
        MN_CALL_GetDataCfgInfoFromBc(&pstCallProc->stBC1, &stDataCfgInfo);
    }
    /* 传真和语音交替，则从BC2中获取 */
    else
    {
        if (( MN_CALL_MODE_AVF == enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stBC2)))
        {
            MN_CALL_GetDataCfgInfoFromBc(&pstCallProc->stBC2, &stDataCfgInfo);
        }
    }


    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CALL_PROC);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstCallProc->stFacility);
    }

    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (pstMsgBuff->stBufferedSetupMsg.ucCallId == pstMsg->ucCallId))
    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(pstMsg->ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(pstMsg->ucCallId);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */
    }

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* 设置等待MT eCall标志 */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSyncInd
 功能描述  : 处理MNCC_SYNC_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  1.日    期   : 2010年7月21日
    作    者   : h44270
    修改内容   : 问题单号：DTS2010071302154
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年3月7日
    作    者   : w00176964
    修改内容   : DTS2013030606529:TD下,网测下发connect消息,RB未建好,此时上报RING
                 用户接听可能会失败,此处进行规避延长TD下的RING上报时机
  4.日    期   : 2013年6月13日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  5.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
  6.日    期   : 2013年12月23日
    作    者   : y00245242
    修改内容   : 增加SRVCC缓存处理
  7.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  8.日    期   : 2014年6月11日
    作    者   : y00245242
    修改内容   : DTS2014060306029
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSyncInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_BOOL                            bResult = VOS_FALSE;
    VOS_UINT8                           uccallId;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfCalls;
    /* 删除dts2013030606529的修改 */

    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    if (VOS_TRUE == pstMsg->unParam.stSyncInd.ulTchAvail)
    {
#if (FEATURE_ON == FEATURE_IMS)
        TAF_CALL_ProcSrvccSyncInfo();
#endif

        if (VOS_FALSE == MN_CALL_GetTchStatus())
        {
            /*设置业务信道建立标志*/
            MN_CALL_SetTchStatus(VOS_TRUE);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
            (VOS_VOID)MN_CALL_SetTchPara(&(pstMsg->unParam.stSyncInd), pstMsg->ucCallId);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
            MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &uccallId);
            if (VOS_TRUE == bWaitSendAlertStatus)
            {
                MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);
                if (VOS_OK != MN_CALL_SendCcAlertReq(uccallId))
                {
                    MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: Failed to send Message Alert.");
                    MN_CALL_FreeCallId(uccallId);
                    return;
                }

                MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_INCOMING);
                /* 启动RING定时器 */
                MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);
            }

            /*临时为GSM的晚指派作的修改，在信令面流程完成之后，业务信道才准备好*/
            MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

            if (MN_CALL_S_ACTIVE == enCallState)
            {
                if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
                {
                    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
                    /* 发送消息通知VC打开语音通道 */
                    MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                    /* 发送消息通知AT语音通道状态 */
                    MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
                    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

                    MN_CALL_SetChannelOpenFlg(VOS_TRUE);
                }
            }

            if (MN_CALL_S_ALERTING == enCallState)
            {
                if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
                {
                    if (VOS_FALSE == TAF_CALL_GetSrvccLocalAlertedFlagByCallId(pstMsg->ucCallId))
                    {
                        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
                        /* 发送消息通知VC打开语音通道 */
                        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                        /* 发送消息通知AT语音通道状态 */
                        MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
                        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

                        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
                    }
                }
            }

            /* 删除dts2013030606529的修改 */
        }
        else
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-21, begin */
            bResult = MN_CALL_SetTchPara(&(pstMsg->unParam.stSyncInd), pstMsg->ucCallId);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-21, end */

            if ((VOS_TRUE == MN_CALL_GetChannelOpenFlg()) && (VOS_TRUE == bResult))
            {
                /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
                /* 发送消息通知VC语音通道配置改变 */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_PARA_CHANGE);
                /* 发送消息通知AT语音通道状态 */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_PARA_CHANGE);
                /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

                return;
            }
        }
    }
    else
    {
        if (VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
            {
                /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
                /* 发送消息通知VC关闭语音通道 */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
                /* 发送消息通知AT语音通道状态 */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
                /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
                MN_CALL_SetChannelOpenFlg(VOS_FALSE);
            }

            /* 如果当前还有等待的呼叫，此时有可能需要关闭声码器，但是业务
               信道仍然存在，需要此时不要清除业务信道建立的标志 */
            MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
            if (0 == ulNumOfCalls)
            {
                /* 清除业务信道建立标志 */
                MN_CALL_SetTchStatus(VOS_FALSE);
            }

        }
    }


}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccAlertInd
 功能描述  : 处理MNCC_ALERT_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改支持本地回铃音
  5.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccAlertInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_ALERTING_MT_STRU   *pstAlert;

    MN_CALL_CHANNEL_INFO_STRU           stChannelInfo;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);
    MN_CALL_UpdateTi(pstMsg->ucCallId, pstMsg->ucTi);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    pstAlert = &pstMsg->unParam.stAlert;

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ALERTING);

    /* 如果网络发送ALERTING消息，此时不能网络放音（网络发音的要求：A progress indicator
       IE indicates user attachment if it specifies a progress description in the set {1， 2， 3}
       or in the set {6， 7， 8， ...， 20}. ），此时通过^CSCHANNELINFO:0通知AP侧进行本地振铃放音 */
    if (VOS_TRUE == TAF_CALL_IsNeedLocalAlerting(&(pstAlert->stProgInd)))
    {
        PS_MEM_SET(&stChannelInfo, 0, sizeof(stChannelInfo));
        MN_CALL_SndAtChannelInfoInd(MN_CALL_EVT_CHANNEL_LOCAL_ALERTING, &stChannelInfo, VOS_TRUE);
    }
    else
    {
        if (VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
            {
                /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
                /* 发送消息通知VC打开语音通道 */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                /* 发送消息通知AT语音通道状态 */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
                /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
            }
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }
    }


    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_ALERTING);

    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MO_ALERTING, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstAlert->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstAlert->stFacility);
    }

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstAlert->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_ALERTING,
                                  (NAS_CC_IE_USER_USER_STRU*)&pstAlert->stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (pstMsgBuff->stBufferedSetupMsg.ucCallId == pstMsg->ucCallId))
    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(pstMsg->ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(pstMsg->ucCallId);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */
    }

        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* 设置等待MT eCall标志 */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccDiscInd
 功能描述  : 处理MNCC_DISC_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
  5.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  6.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
  7.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  8.日    期   : 2014年10月09日
    作    者   : s00217060
    修改内容   : for cs_err_log
  9.日    期   : 2014年12月11日
    作    者   : s00217060
    修改内容   : DTS2014121003107:no tch不再上报，用网络disconnect带上来的原
                 因值,如果网络没带原因值用默认值#16
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccDiscInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_DISCONNECT_MT_STRU *pstDisc;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulTchStatus;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_IDLE != enCallState);

    pstDisc = &pstMsg->unParam.stDisc;

    ulTchStatus = MN_CALL_GetTchStatus();

    if ((VOS_TRUE == ulTchStatus)
     && (VOS_TRUE == pstDisc->stProgInd.IsExist)
     && ( ( (pstDisc->stProgInd.Octet4.ProgDesc >= 1)
          && (pstDisc->stProgInd.Octet4.ProgDesc <= 3))
       || ( (pstDisc->stProgInd.Octet4.ProgDesc >= 6)
          && (pstDisc->stProgInd.Octet4.ProgDesc <= 20))))
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
            /* 发送消息通知VC打开语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* 网络下发disconnect时，cc会先构造mncc_sync_ind(ulTchAvail:false), 再上报mncc_disc_ind给CALL,
       CALL在收到mncc_disc_ind,TCH一定是不可用的，并且无法判断出之前TCH是否可用过，此处删除上报原因值TAF_CS_CAUSE_CC_INTER_ERR_NO_TCH
       和周君确认:此处用网络Disconnect消息里带的原因值,如果网络没带原因值用默认值#16 */
    if (VOS_TRUE    == pstDisc->stCause.IsExist)
    {
        MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstDisc->stCause.Octet4.CauseValue );
    }
    else
    {
        MN_CALL_UpdateCcCause(pstMsg->ucCallId, TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING);
    }

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);

#if (FEATURE_ON == FEATURE_PTM)
    MN_CALL_CsCallDiscInfoRecord(pstMsg->ucCallId, MN_CALL_GetCsCause(pstMsg->ucCallId));
#endif

    /*不修改状态，暂时认为不改变状态的话，不会有影响*/

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId,
                               (NAS_CC_IE_FACILITY_STRU*)&pstDisc->stFacility);
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        MN_CALL_ProcMnccDisIndWithCcbs(pstDisc, pstMsg->ucCallId);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_DISCONNECT,
                                  (NAS_CC_IE_USER_USER_STRU *)&pstDisc->stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);

}

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcAllCallReleased
 功能描述  : 所有呼叫释放后的处理流程
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 1.日    期   : 2014年4月15日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_ProcCallAllReleased(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg
)
{
    VOS_UINT8                           ucCallId;
    VOS_BOOL                            bWaitSendAlertStatus;

    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
        {
            /* 发送消息通知VC关闭语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
        }
        MN_CALL_SetTchStatus(VOS_FALSE);
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
    }

    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucCallId);

    if ((VOS_TRUE == bWaitSendAlertStatus))
    {
        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);
    }

    /* 如果当前没有呼叫，上报所有呼叫都已RELEASED */
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_ALL_RELEASED);

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
    {
        TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
        /* client ID与op ID在SPM中不care, 填写0 */
        TAF_CALL_SendTafRelCallCnf(0, 0, TAF_CS_CAUSE_SUCCESS);
    }
#endif
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcCallCause
 功能描述  : 处理呼叫原因值
 输入参数  : ucCallId         - 呼叫标识
             ucCauseExistFlag － 原因值存在标志
             enCallCause      － cause值

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 1.日    期   : 2014年4月15日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_ProcCallCause(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCauseExistFlag,
    MN_CALL_CC_CAUSE_ENUM_U8            enCallCause
)
{
    /* 更新本地原因值 */
    if (VOS_TRUE == ucCauseExistFlag)
    {
        /* 先记录本次异常的CHR，原因值使用本次异常的原因值 */
#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        if (0 != enCallCause)
        {
            MN_CALL_CsCallErrRecord(ucCallId, enCallCause);
        }
        else
        {
            MN_CALL_CsCallErrRecord(ucCallId, TAF_CS_CAUSE_UNKNOWN);
        }
#endif

        /* 如果原来就已经有异常原因，则本次的异常不更新原因值 */
        if (MN_CALL_INVALID_CAUSE == MN_CALL_GetCsCause(ucCallId))
        {
            MN_CALL_UpdateCcCause(ucCallId, enCallCause);
        }
    }
    else
    {
#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(ucCallId, MN_CALL_GetCsCause(ucCallId));
#endif
    }

}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcCallRedialAfterCallRel
 功能描述  : 处理呼叫释放后的重拨
 输入参数  : ucCallId         － 呼叫标识

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 1.日    期   : 2014年4月15日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_ProcCallRedialAfterCallRel(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (ucCallId == pstMsgBuff->stBufferedSetupMsg.ucCallId))
    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(ucCallId);
    }
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRelInd
 功能描述  : 处理MNCC_REL_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2008年9月11日
    作    者   :S62952
    修改内容   : 问题单号:AT2D05594
  4.日    期   : 2009年3月2日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D09095

  5.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 更新支持CCBS
  6.日    期   : 2011年10月15日
    作    者   : f00179208
    修改内容   : AT移植项目
  7.日    期   : 2012年03月02日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012020206417，使用ATD117;拨打电话，一段时间后挂断电话，
                 单板主动上报的CEND中，通话时间显示为0
   8.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
   9.日    期   : 2012年10月29日
     作    者   : z00161729
     修改内容   : DTS2012083102536:支持cc呼叫重建
  6.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  7.日    期   : 2013年01月18日
    作    者   : Y00213812
    修改内容   : DTS2013011201560修改错误原因值上报
  8.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
  9.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS FDN&Call Control移动到TAF
 10.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目，呼叫释放，若未处于多方通话中则释放DTMF缓存
 11.日    期   : 2013年07月09日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目
 12.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报呼叫状态
 13.日    期   : 2013年11月06日
    作    者   : l00198894
    修改内容   : DTS2013111305567: 解决多方呼叫时DTMF上下文清理错误
 14.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
 15.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRelInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_RELEASE_MT_STRU   *pstRel;
    VOS_UINT8                           ucNumOfCalls;
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_MGMT_STRU                   stCallEntity;
#endif
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    MN_CALL_ID_T                        ucDtmfCallId;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;

    ucDtmfCallId = 0;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_IDLE != enCallState);

    pstRel = &pstMsg->unParam.stRel;

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstRel->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstRel->stFacility);
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /*CCBS激活超时，用户没有响应，网侧发release消息，cause为102:recovery on timer expiry,上报CCBS激活失败事件*/
    if ( (MN_CALL_S_CCBS_WAITING_ACTIVE == enCallState)
       &&(MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg))
    {
        MN_CALL_UpdateCcbsSupsProgress(pstMsg->ucCallId,
                                       MN_CALL_ERR_SS_UNSPECIFIC,
                                       MN_CALL_SS_RES_FAIL);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /*如果是可视电话，且CST已建立好业务信道，通知CST模块释放*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(pstMsg->ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(pstMsg->ucCallId);
        }
    }

    /* 需要先统计通话时间，再上报RELEASED事件 */
    MN_CALL_StopFluxCalculate(pstMsg->ucCallId);

    /* 一般情况下 RELEASE消息只会携带一个Cause值，只有在24.008 5.4.4.1.2.3
    章节中描述的情况，才会带两个Cause值，目前暂时不考虑这种情况，只取第一个 */
    /* 如果消息中携带了Cause，那么更新Cause值 */
    /* 更新原因值放在MN_CALL_EVT_RELEASED前面，否则release事件里带的原因值可能不对 */
    TAF_CALL_ProcCallCause(pstMsg->ucCallId,
                           NAS_IE_IS_PRESENT(&pstRel->stCause),
                           pstRel->stCause.Octet4.CauseValue);

    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_RELEASED);


    TAF_CALL_ProcCallStatusFail(pstMsg->ucCallId, enCallState);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);


    /* 电话挂断时勾出相应的事件，第三个参数不能是空指针，第四个参数不能是0，否则事件报不上去 */
    enCause = MN_CALL_GetCsCause(pstMsg->ucCallId);

    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(pstMsg->ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }

    /* 更新补充业务操作的进展(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    TAF_CALL_ProcRelCallSsKeyEvent(pstMsg->ucCallId);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    TAF_CALL_ProcCallRedialAfterCallRel(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_ECALL)
    /* 在call id释放之前，获取当前CALL ID呼叫实体信息，后续使用 */
    PS_MEM_SET(&stCallEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    (VOS_VOID)MN_CALL_GetSpecificCallInfo(pstMsg->ucCallId, &stCallEntity);
#endif

    MN_CALL_FreeCallId(pstMsg->ucCallId);

    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);

    if (0 == ucNumOfCalls)
    {
        TAF_CALL_ProcCallAllReleased(pstMsg);
    }

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstRel->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_RELEASE,
                                  (NAS_CC_IE_USER_USER_STRU *)&pstRel->stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);


    enCause = TAF_CALL_GetAllowedDtmfCallId(&ucDtmfCallId);
    if (enCause != TAF_CS_CAUSE_SUCCESS)
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_RELEASE);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_ProcEcallRel(&stCallEntity);
#endif

    return;

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRelCnf
 功能描述  : 处理MNCC_REL_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2009年3月2日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D09095

  4.日    期   : 2010年1月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  5.日    期   : 2011年10月15日
    作    者   : f00179208
    修改内容   : AT移植项目
  6.日    期   : 2012年03月02日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012020206417，使用ATD117;拨打电话，一段时间后挂断电话，
                 单板主动上报的CEND中，通话时间显示为0
  7.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  8.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
  9.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 10.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
 11.日    期   : 2013年01月18日
    作    者   : Y00213812
    修改内容   : DTS2013011201560修改错误原因值上报
 12.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
 13.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS FDN&Call Control移动到TAF
 14.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目，软关机时重置DTMF状态及缓存
 15.日    期   : 2013年07月09日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目
 16.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报呼叫状态
 17.日    期   : 2013年11月06日
    作    者   : l00198894
    修改内容   : DTS2013111305567: 解决多方呼叫时DTMF上下文清理错误
 18.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
 19.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRelCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8                                   enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    const NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU              *pstRelComp;
    VOS_UINT8                                               ucNumOfCalls;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfgAddr;

    MN_CALL_ID_T                                            ucDtmfCallId;
    TAF_CS_CAUSE_ENUM_UINT32                                enCause;
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_MGMT_STRU                                       stCallEntity;
#endif

    ucDtmfCallId = 0;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_IDLE != enCallState);

    pstRelComp = &pstMsg->unParam.stRelComp;

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstRelComp->stFacility))
    {
        /* 处理呼叫相关补充业务 */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstRelComp->stFacility);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else
    {
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            /*用户没有响应，网侧发release complete消息，cause为102:recovery on timer expiry,上报CCBS回呼失败事件*/
            MN_CALL_CcbsProcMnccRelCnf(enCallState, pstMsg->ucCallId);
        }

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    /*如果是可视电话，通知CST模块释放*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(pstMsg->ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(pstMsg->ucCallId);
        }
    }

    /* 需要先统计通话时间，再上报RELEASED事件 */
    MN_CALL_StopFluxCalculate(pstMsg->ucCallId);

    /* 更新原因值放在MN_CALL_EVT_RELEASED前面，否则release事件里带的原因值可能不对 */
    TAF_CALL_ProcCallCause(pstMsg->ucCallId,
                           NAS_IE_IS_PRESENT(&pstRelComp->stCause),
                           pstRelComp->stCause.Octet4.CauseValue);

    /*先处理呼叫相关补充业务，再上报release事件,原代码是放在处理呼叫相关补充业务前面的*/
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_RELEASED);

    TAF_CALL_ProcCallStatusFail(pstMsg->ucCallId, enCallState);

    enCause = MN_CALL_GetCsCause(pstMsg->ucCallId);

    /* 电话挂断时勾出相应的事件，第三个参数不能是空指针，第四个参数不能是0，否则事件报不上去 */
    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(pstMsg->ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }


    /* 更新补充业务操作的进展(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    TAF_CALL_ProcRelCallSsKeyEvent(pstMsg->ucCallId);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstRelComp->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_RELEASE_COMPLETE,
                                  (NAS_CC_IE_USER_USER_STRU*)&pstRelComp->stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    TAF_CALL_ProcCallRedialAfterCallRel(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_ECALL)
    /* 在call id释放之前，获取当前CALL ID呼叫实体信息，后续使用 */
    PS_MEM_SET(&stCallEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    (VOS_VOID)MN_CALL_GetSpecificCallInfo(pstMsg->ucCallId, &stCallEntity);
#endif

    MN_CALL_FreeCallId(pstMsg->ucCallId);

    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);

    if (0 == ucNumOfCalls)
    {
        TAF_CALL_ProcCallAllReleased(pstMsg);
    }

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);

    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    enCause = TAF_CALL_GetAllowedDtmfCallId(&ucDtmfCallId);
    if (enCause != TAF_CS_CAUSE_SUCCESS)
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_RELEASE);
    }
    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_ProcEcallRel(&stCallEntity);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRejInd
 功能描述  : 处理MNCC_REJ_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2008年7月23日
    作    者   : 黎客来 130025
    修改内容   : 问题单号:AT2D04594
  4.日    期   : 2009年3月2日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D09095
  5.日    期   : 2011年10月15日
    作    者   : f00179208
    修改内容   : AT移植项目
  6.日    期   : 2012年03月02日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012020206417，使用ATD117;拨打电话，一段时间后挂断电话，
                 单板主动上报的CEND中，通话时间显示为0
  7.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目下发CALL DISCONNECT EVENT到USIM模块
  8.日    期   : 2012年09月20日
    作    者   : A00165503
    修改内容   : STK&DCM 项目cs域错误码上报
  9.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 10.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
 11.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
 12.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，SS FDN&Call Control移动到TAF
 13.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目，呼叫重建指示，清空缓存
 14.日    期   : 2013年07月20日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目
 15.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报呼叫状态
 16.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
 17.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRejInd(
    MNCC_IND_PRIM_MSG_STRU             *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           ucNumOfCalls;
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-6, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_MGMT_STRU                   stCallEntity;
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-6, end */

    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    if (VOS_TRUE == MN_CALL_IsNeedCallRedial(pstMsg->ucCallId, pstMsg->unParam.enCause))
    {
        /* 缓存mncc rej ind消息，启动重建定时器 */
        pstBufferdMsg->bitOpBufferedRejIndMsg = VOS_TRUE;
        PS_MEM_CPY(&pstBufferdMsg->stBufferedRejIndMsg, pstMsg, sizeof(MNCC_IND_PRIM_MSG_STRU));

        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, 0, 0, VOS_RELTIMER_NOLOOP);

            /* 初始化MSD传输状态为BUTT */
            TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
        }
        else
#endif
        {
            MN_CALL_StartTimer(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL, 0, 0, VOS_RELTIMER_NOLOOP);
        }
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */
        return;
    }

    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_RELEASE);
    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */


    MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstMsg->unParam.enCause);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);

    /*如果是可视电话，通知CST模块释放*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(pstMsg->ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(pstMsg->ucCallId);
        }
    }

    /* 需要先统计通话时间，再上报RELEASED事件 */
    MN_CALL_StopFluxCalculate(pstMsg->ucCallId);

    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_RELEASED);

    TAF_CALL_ProcCallStatusFail(pstMsg->ucCallId, enCallState);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(pstMsg->ucCallId, pstMsg->unParam.enCause);
#endif

    /* 电话挂断时勾出相应的事件，第三个参数不能是空指针，第四个参数不能是0，否则事件报不上去 */
    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(pstMsg->ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &(pstMsg->unParam.enCause),
                        sizeof(MN_CALL_INFO_STRU));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &(pstMsg->unParam.enCause),
                        sizeof(MN_CALL_INFO_STRU));
    }

    /* 更新补充业务操作的进展(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    TAF_CALL_ProcRelCallSsKeyEvent(pstMsg->ucCallId);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-9, begin */
    TAF_CALL_ProcCallRedialAfterCallRel(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_ECALL)
    /* 在call id释放之前，获取当前CALL ID呼叫实体信息，后续使用 */
    PS_MEM_SET(&stCallEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    (VOS_VOID)MN_CALL_GetSpecificCallInfo(pstMsg->ucCallId, &stCallEntity);
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-9, end */

    MN_CALL_FreeCallId(pstMsg->ucCallId);

    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
    if (0 == ucNumOfCalls)
    {
        TAF_CALL_ProcCallAllReleased(pstMsg);
    }
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-6, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (MN_CALL_S_DIALING != enCallState)
    {
        TAF_CALL_ProcEcallRel(&stCallEntity);
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-6, end */
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccFacilityInd
 功能描述  : 处理MNCC_FACILITYS_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    /* 处理呼叫相关补充业务 */
    MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstMsg->unParam.stFac.stFacility);

}

/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccHoldCnf
 功能描述  : 处理MNCC_HOLD_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目，呼叫保持时清空DTMF缓存
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccHoldCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_ACTIVE == enCallState);

    /* 给AT模块上报MN_CALL_EVT_HOLD事件 */
    MN_CALL_ReportHoldEvent(MN_CLIENT_ALL, 1, &(pstMsg->ucCallId));

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_HELD);

    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_ON_HOLD);
    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

    /* 更新补充业务操作的进展(HOLD_CNF) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccHoldRej
 功能描述  : 处理MNCC_HOLD_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2015年08月17日
    作    者   : f00179208
    修改内容   : DTS2015080300502:在电话挂断过程中，保持该路电话被拒后，不需要更新错误原因值
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccHoldRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_ACTIVE == enCallState);

    enCause = MN_CALL_GetCsCause(pstMsg->ucCallId);

    MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstMsg->unParam.enCause);

    /* 更新补充业务操作的进展(HOLD_REJ) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_HOLD_REJ,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    /* 如果是在DISC(MO/MT)状态下的HOLD REJ，则不更新原因值 */
    if (NAS_CC_CAUSE_CC_INTER_ERR_HOLD_REJ_IN_DISC_STATE == pstMsg->unParam.enCause)
    {
        MN_CALL_UpdateCcCause(pstMsg->ucCallId, enCause);
    }

}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRetrieveCnf
 功能描述  : 处理MNCC_RETRIEVE_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年02月03日
    作    者   : Y00213812
    修改内容   : DTS2013020203946,前一个呼叫未置为HLED，本消息不处理Retrieved结果
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRetrieveCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfActCalls;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_HELD == enCallState);

    /* 如果当前已经有了一个激活状态的呼叫，则不处理Retrieve结果 */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfActCalls, aCallIds);
    if (0 == ulNumOfActCalls)
    {
        /* 给AT模块上报MN_CALL_EVT_RETRIEVE事件 */
        MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, 1, &(pstMsg->ucCallId));

        MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ACTIVE);

        /* 更新补充业务操作的进展(RETRIEVE_CNF) */
        MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                       MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                       MN_CALL_ERR_SS_UNSPECIFIC);
    }
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRetrieveRej
 功能描述  : 处理MNCC_RETRIEVE_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年02月03日
    作    者   : Y00213812
    修改内容   : DTS2013020203946,retrieve操作失败，增加处理，如果此时有两个hold状态的呼叫，
				   此时应该要把另外一个处于hold状态的呼叫回退
  4.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRetrieveRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfHoldCalls;
    VOS_UINT32                          i;

    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_HELD == enCallState);

    MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstMsg->unParam.enCause);

    /* retrieve操作失败，增加处理，如果此时有两个hold状态的呼叫，此时应该
       要把另外一个处于hold状态的呼叫回退 */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfHoldCalls, aCallIds);
    if (2 == ulNumOfHoldCalls)
    {
        for (i = 0; i < ulNumOfHoldCalls; i++)
        {
            if (pstMsg->ucCallId != aCallIds[i])
            {
                MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, 1, &aCallIds[i]);
                MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_ACTIVE);
                break;
            }
        }
    }

    /* 更新补充业务操作的进展(RETRIEVE_REJ) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccFacilityLocalRej
 功能描述  : 处理MNCC_RETRIEVE_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityLocalRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucOpCode;
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvent;

    /*检查Invoke Id及其对应的Operation Code*/
    ucInvokeId = pstMsg->unParam.ucInvokeId;
    if (VOS_FALSE == g_stCallInvokeIdTable[ucInvokeId].bUsed)
    {
        MN_WARN_LOG("MN_CALL_ProcMnccFacilityLocalRej: invalid InvokeId");
        return;
    }
    ucOpCode = g_stCallInvokeIdTable[ucInvokeId].ucOperateCode;
    if (VOS_OK != MN_CALL_SsOpCodeTransToSsEvent(ucOpCode, &enEvent))
    {
        MN_WARN_LOG("MN_CALL_ProcMnccFacilityLocalRej: invalid Operation Code");
        return;
    }

    MN_CALL_InvokeId_Free(ucInvokeId);
    MN_CALL_UpdateCcCause(pstMsg->ucCallId, MN_CALL_INTERWORKING_UNSPECIFIED);

    /* 更新补充业务操作的进展(RETRIEVE_REJ) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   enEvent,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

}

/*****************************************************************************
 函 数 名  : MN_CALL_SendVcMsg
 功能描述  : 上报声码器控制事件
 输入参数  : enEventType - 事件类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID  MN_CALL_SendVcMsg(
    CALL_VC_MSG_ID_ENUM_U16             enEventType
)
{
    CALL_VC_CHANNEL_INFO_MSG_STRU       *pstChannelInfoMsg;

    /* 申请消息 */
    pstChannelInfoMsg = (CALL_VC_CHANNEL_INFO_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                           sizeof(CALL_VC_CHANNEL_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstChannelInfoMsg)
    {
        MN_ERR_LOG("MN_CALL_SendVcMsg: ALLOC MSG FAIL.");
        return;
    }

    pstChannelInfoMsg->ulReceiverPid = WUEPS_PID_VC;
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
    pstChannelInfoMsg->enMsgName     = enEventType;
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
    (VOS_VOID)VOS_MemCpy(&pstChannelInfoMsg->stChannelInfo,
               &f_stCallTchStatus,
               sizeof(MN_CALL_CHANNEL_INFO_STRU));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstChannelInfoMsg))
    {
        MN_ERR_LOG("MN_CALL_SendVcMsg: MSG SEND FAIL.");
    }
}

/*****************************************************************************
 函 数 名  : MN_CALL_ReportChannelEvent
 功能描述  : 上报声码器控制事件
 输入参数  : callId - 需要上报事件的呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:cs宏打开
  3.日    期   : 2013年01月05日
    作    者   : l00171473
    修改内容   : DTS2013010800120 语音带宽信息上报
  4.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID  MN_CALL_ReportChannelEvent(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enEventType
)
{

    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo = VOS_NULL_PTR;

    pstChannelInfo = &f_stCallTchStatus;

    /* 信道开启时向AT上报 CHANNEL 信息, 并在全局变量中记录此时的信道信息 */
    if ((MN_CALL_EVT_CHANNEL_OPEN        == enEventType)
     || (MN_CALL_EVT_CHANNEL_PARA_CHANGE == enEventType))
    {
        MN_CALL_SndAtChannelInfoInd(enEventType, pstChannelInfo, VOS_FALSE);

        /* 记录此时信道信息到全局变量中 */
        MN_CALL_SetLastCallTchStatus(pstChannelInfo);
    }
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccProgressInd
 功能描述  : 处理MNCC_PROGRESS_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年6月21日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  3.日    期   : 2013年10月6日
    作    者   : z00161729
    修改内容  : DTS2013100800595:IOT主叫过程网络先下发progress ind指示不支持网络放音接着下发alerting
	              ind指示支持网络放音，call模块未打开声码器导致听不见声音
  4.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccProgressInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    VOS_UINT32                          ulLocalAlertingFlg;

    ulLocalAlertingFlg = TAF_CALL_IsNeedLocalAlerting(&pstMsg->unParam.stProgressInd.stProgInd);

    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if ((VOS_FALSE == MN_CALL_GetChannelOpenFlg())
         && (VOS_FALSE == ulLocalAlertingFlg))
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
            /* 发送消息通知VC打开语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }

    }

    /* UUS1存在,需上报UUS1信息 */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstMsg->unParam.stProgressInd.stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_PROGRESS,
                                  (NAS_CC_IE_USER_USER_STRU*)&pstMsg->unParam.stProgressInd.stUserUser);
        /* UUS1信息上报 */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* 设置等待MT eCall标志 */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */
}

/*****************************************************************************
 函 数 名  : MN_CALL_GetTchStatus
 功能描述  : 当前信道打开时获取当前TCH信道类型等参数
 输入参数  : 无
 输出参数  : pstChannInfo  -  当前信道参数
 返 回 值  : VOS_UINT32 VOS_ERR:当前信道未打开
                        VOS_OK :当前信道打开
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月9日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2014年04月08日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT32 MN_CALL_GetTchParm(
    MN_CALL_CHANNEL_PARAM_STRU          *pstChannParm
)
{
    if ( VOS_FALSE == f_stCallTchStatus.bChannelEnable )
    {
        return VOS_ERR;
    }

    pstChannParm->enCodecType = f_stCallTchStatus.stChannelParam.enCodecType;
    pstChannParm->enMode      = f_stCallTchStatus.stChannelParam.enMode;
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-5-9, begin */
    pstChannParm->enCallType  = f_stCallTchStatus.stChannelParam.enCallType;
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-5-9, end */

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCcUus1Info
 功能描述  : 调用CC模块中函数更新UUS1信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_UpdateCcUus1Info(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType;
    VOS_UINT32                          ulRet;
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType;
    NAS_CC_IE_USER_USER_STRU            stUuieInfo;

    /* 先进行消息类型转换,用户设置ANY时,则默认为Setup消息 */
    enMsgType = pstUus1Info->enMsgType;
    if ( MN_CALL_UUS1_MSG_ANY == enMsgType )
    {
        enMsgType = MN_CALL_UUS1_MSG_SETUP;
    }

    /* 将CALL定义的消息类型转换为CC定义的消息类型 */
    ulRet = MN_CALL_ConCallMsgTypeToCcMsgType(enMsgType,&enCcMsgType);
    if ( VOS_OK != ulRet )
    {
        return MN_ERR_INVALIDPARM;
    }

    /* 此处通过API直接更新CC模块中相关全局变量,不经过CALL模块,目的是因为CALL发送
    Disconnect请求时,不能区分发送的消息是Disconnect还是Release还是
    Release complete, 只有CC知道相关信息*/

    if ( MN_CALL_SET_UUS1_ACT == enSetType )
    {
        ulRet = MN_CALL_ConCallUusInfoToCc(enMsgType,pstUus1Info,&stUuieInfo);
        if ( VOS_OK != ulRet )
        {
            return MN_ERR_INVALIDPARM;
        }

        ulRet = NAS_CC_ActUus1Info(enCcMsgType, &stUuieInfo);
    }
    else
    {
        ulRet = NAS_CC_DeactUus1Info(enCcMsgType);
    }

    if ( VOS_OK != ulRet)
    {
        return MN_ERR_INVALIDPARM;
    }


    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : MN_CALL_GetCcUus1Info
 功能描述  : 获取CC保存的UUS1相关信息
 输入参数  : 无
 输出参数  : pulActNum      :CC总共激活个数
             pstUus1Info    :激活UUS1的信息
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcUus1Info(
    VOS_UINT32                          *pulActNum,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    VOS_UINT32                          ulActNum;
    NAS_CC_UUS1_INFO_STRU               astUus1Info[NAS_CC_MAX_UUIE_MSG_NUM];
    VOS_UINT32                          i;

    NAS_CC_GetAllUus1Info(&ulActNum,astUus1Info);

    *pulActNum = ulActNum;

    /* 将CC定义的消息格式转换为CALL的消息格式 */
    for ( i = 0 ; i < ulActNum ; i++ )
    {
        MN_CALL_ConCcUusInfoToCall(astUus1Info[i].enMsgType,
                                   &astUus1Info[i].stUuieInfo,
                                   pstUus1Info);
        pstUus1Info++;

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcUusInfoInd
 功能描述  : 处理空口User to User Info信息，包括其他消息中携带该信息
 输入参数  : pstMsg :消息中User to User内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月2日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_CALL_ProcUusInfoInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    const NAS_CC_UUS_INFO_IND_STRU            *pstUusInfo;

    pstUusInfo = (NAS_CC_UUS_INFO_IND_STRU *)&(pstMsg->unParam.stUusInfo);

    MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                              pstUusInfo->enCcMsgtype,
                              (NAS_CC_IE_USER_USER_STRU*)&pstUusInfo->stUserInfo.stUserUser);
    /* UUS1信息上报 */
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);

}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcEmergencyListInd
 功能描述  : 处理MM上报的紧急呼号码
 输入参数  : pstMsg :消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月11日
    作    者   : w00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_CALL_ProcEmergencyListInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MNCC_EMERGENCY_LIST_IND_STRU        *pstMnccEmcListInd  = VOS_NULL_PTR;

    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfg       = VOS_NULL_PTR;

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    pstMnccEmcListInd = (MNCC_EMERGENCY_LIST_IND_STRU *)&(pstMsg->unParam.stEmcListInd);

    MN_CALL_SetMmEmerNumList(pstMnccEmcListInd);

    /* 紧急呼上报控制NV开关打开，上报紧急呼号码 */
    if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
    {
        MN_CALL_ReportEccNumList();
    }
}

/*****************************************************************************
 函 数 名  : MN_CALL_ReportHoldEvent
 功能描述  : 上报呼叫HOLD事件
 输入参数  : VOS_UINT8 ucCallNum        -- 呼叫总数
             VOS_UINT8 *pucCallId       -- CallId数组
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月24日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年4月17日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2013年9月20日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseII 增加呼叫域信息

*****************************************************************************/
VOS_VOID MN_CALL_ReportHoldEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId )
{
    MN_CALL_EVT_HOLD_STRU               stEvent;
    VOS_UINT8                           ucLoop;
    MN_CALL_INFO_STRU                   stCallInfo;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, end */
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_HOLD_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent     = MN_CALL_EVT_HOLD;
    stEvent.usClientId  = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum   = ucCallNum;
    PS_MEM_CPY(stEvent.aucCallId, pucCallId, ucCallNum);

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                sizeof(stEvent.aucUnsolicitedRptCfg));

    /* Added by Y00213812 for VoLTE_PhaseII 项目, 2013-9-12, begin */
    /* 语音呼叫域信息 */
    stEvent.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;
    /* Added by Y00213812 for VoLTE_PhaseII 项目, 2013-9-12, end */

    /* 将HOLD事件发送到AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_HOLD_STRU));
    }
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, end */

    /* 将HOLD事件发送到OAM */
    for (ucLoop = 0; ucLoop < ucCallNum; ucLoop++)
    {
        MN_CALL_GetCallInfoByCallId(stEvent.aucCallId[ucLoop], &stCallInfo);

        MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                           MN_CALL_EVT_HOLD,
                           MAPS_STK_PID,
                           &stCallInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ReportRetrieveEvent
 功能描述  : 上报呼叫Retrieve事件
 输入参数  : VOS_UINT8 ucCallNum        -- 呼叫总数
             VOS_UINT8 *pucCallId       -- CallId数组
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月24日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年4月17日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2013年9月20日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseII 增加呼叫域信息
*****************************************************************************/
VOS_VOID MN_CALL_ReportRetrieveEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId )
{
    MN_CALL_EVT_RETRIEVE_STRU           stEvent;
    VOS_UINT8                           ucLoop;
    MN_CALL_INFO_STRU                   stCallInfo;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, end */
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent     = MN_CALL_EVT_RETRIEVE;
    stEvent.usClientId  = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum   = ucCallNum;
    PS_MEM_CPY(stEvent.aucCallId, pucCallId, ucCallNum);

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                sizeof(stEvent.aucUnsolicitedRptCfg));

    /* Added by Y00213812 for VoLTE_PhaseII 项目, 2013-9-12, begin */
    /* 语音呼叫域信息 */
    stEvent.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;
    /* Added by Y00213812 for VoLTE_PhaseII 项目, 2013-9-12, end */

    /* 将RETRIEVE事件发送到AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    }

    /* 将RETRIEVE事件发送到OAM */
    for (ucLoop = 0; ucLoop < ucCallNum; ucLoop++)
    {
        MN_CALL_GetCallInfoByCallId(stEvent.aucCallId[ucLoop], &stCallInfo);

        MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                           MN_CALL_EVT_RETRIEVE,
                           MAPS_STK_PID,
                           &stCallInfo);
    }

    return;
}



/* 删除MN_CALL_ReportErrIndEvent */


/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_ProcBufferedCall
 功能描述  : 释放重拨缓存消息处理
 输入参数  : ucCallId - 缓存的call id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
  4.日    期   : 2013年07月20日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目
  5.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报呼叫状态
  6.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  7.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
  8.日    期   : 2015年7月7日
    作    者   : zwx247453
    修改内容   : CHR 优化项目
  9.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090607329
*****************************************************************************/
VOS_VOID  MN_CALL_ProcBufferedCall(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           ucNumOfCalls;
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_UINT8                           ucTempCallId;
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
    /* 定时器停止移到函数外面统一处理 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */

    MN_CALL_UpdateCcCause(ucCallId, enCause);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(ucCallId, VOS_FALSE);

    /*如果是可视电话，通知CST模块释放*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(ucCallId);
        }
    }

    /* 需要先统计通话时间，再上报RELEASED事件 */
    MN_CALL_StopFluxCalculate(ucCallId);

    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_RELEASED);

    TAF_CALL_ProcCallStatusFail(ucCallId, enCallState);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(ucCallId, enCause);
#endif

    /* 电话挂断时勾出相应的事件，第三个参数不能是空指针，第四个参数不能是0，否则事件报不上去 */
    enCause = MN_CALL_INVALID_CAUSE;

    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }

    /* 更新补充业务操作的进展(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    TAF_CALL_ProcRelCallSsKeyEvent(ucCallId);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    MN_CALL_FreeCallId(ucCallId);


    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);
    if ((VOS_TRUE == MN_CALL_GetTchStatus()) && (0 == ucNumOfCalls))
    {
        if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
            /* 发送消息通知VC关闭语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

        }
        MN_CALL_SetTchStatus(VOS_FALSE);
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
    }

    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucTempCallId) ;
    if ((VOS_TRUE == bWaitSendAlertStatus) && (0 == ucNumOfCalls))
    {
        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);
    }

    /* 如果当前没有呼叫，上报所有呼叫都已RELEASED */
    if (0 == ucNumOfCalls)
    {
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ALL_RELEASED);
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
        
        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */
    }

    if ((VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
     && (ucCallId == pstBufferdMsg->stBufferedSetupMsg.ucCallId))
    {
        MN_CALL_ClearBufferedMsg();
    }

    return;
}
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcBufferedRedialMessage
 功能描述  : 处理缓存的重拨消息
 输入参数  : pstBufferdMsg - 缓存的重拨消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
  2.日    期   : 2015年7月7日
    作    者   : zwx247453
    修改内容   : CHR 优化项目
*****************************************************************************/
VOS_VOID TAF_CALL_ProcBufferedRedialMessage(
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedRejIndMsg)
    {
        MN_CALL_ProcBufferedCall(pstBufferdMsg->stBufferedRejIndMsg.ucCallId, enCause);

        /* 下发CALL DISCONNECT EVENT到USIM模块 */
        MN_CALL_SndStkCallDiscEvent(&(pstBufferdMsg->stBufferedRejIndMsg),
                                    pstBufferdMsg->stBufferedRejIndMsg.enPrimName,
                                    VOS_TRUE);
    }
    else if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
        MN_CALL_ProcBufferedCall(pstBufferdMsg->stBufferedSetupMsg.ucCallId, enCause);
    }
    else
    {

    }
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */

/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_SndAtChannelInfoInd
 功能描述  : 向AT上报语音Channel信息
 输入参数  : enChannelEvent
             pstChannelInfo
             ucIsLocalAlertingFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月05日
    作    者   : l00171473
    修改内容   : 新建 for DTS2013010800120 语音带宽信息上报

  2.日    期   : 2013年04月11日
    作    者   : l00198894
    修改内容   : C50问题单同步
  3.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改
  4.日    期   : 2013年9月20日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseII 增加呼叫域信息
  5.日    期   : 2014年3月29日
    作    者   : w00176964
    修改内容   : DTS2014032901140:接口优化调整
*****************************************************************************/
VOS_VOID MN_CALL_SndAtChannelInfoInd(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enChannelEvent,
    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo,
    VOS_UINT8                           ucIsLocalAlertingFlag
)
{
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;

    PS_MEM_SET(&stChannelEvt, 0x00, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    stChannelEvt.enEvent        = MN_CALL_EVT_CHANNEL_INFO_IND;

    stChannelEvt.usClientId     = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    stChannelEvt.ucIsLocalAlertingFlag = ucIsLocalAlertingFlag;

    /* Added by Y00213812 for VoLTE_PhaseII 项目, 2013-9-12, begin */
    /* 语音呼叫域信息 */
    stChannelEvt.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;
    /* Added by Y00213812 for VoLTE_PhaseII 项目, 2013-9-12, end */

    stChannelEvt.enCodecType   = pstChannelInfo->stChannelParam.enCodecType;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
}

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
/* 删除该函数，功能实现移到函数MN_CALL_ReportChannelEvent中 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, end */

/*****************************************************************************
 函 数 名  : TAF_CALL_IsNeedLocalAlerting
 功能描述  : 是否需要本地播放回铃音
 输入参数  : pstProgInd - progress indicator IE信息
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要；VOS_TRUE:需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改支持本地回铃音
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsNeedLocalAlerting(const NAS_CC_IE_PROGRESS_INDICATOR_STRU *pstProgInd)
{
    if (VOS_TRUE == pstProgInd->IsExist)
    {
        if (((pstProgInd->Octet4.ProgDesc >= 1)
          && (pstProgInd->Octet4.ProgDesc <= 3))
         || ((pstProgInd->Octet4.ProgDesc >= 6)
          && (pstProgInd->Octet4.ProgDesc <= 20)))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_RcvCcStartDtmfCnf
 功能描述  : 处理MNCC_START_DTMF_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
  2.日    期   :2013年10月24日
    作    者   :z00161729
    修改内容   :DTS2013102403705:dtmf不支持off_length参数，SBM IOT认证需要stop dtmf req和下一个start dtmf req间隔大于70ms
*****************************************************************************/
VOS_VOID  TAF_CALL_RcvCcStartDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    MN_CALL_ID_T                        CallId;

    /* 判断状态是否异常 */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_WAIT_START_CNF)
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfCnf: Dtmf State Error!");
        return;
    }

    /* 回复DTMF正式响应事件 */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                         pstDtmfCurInfo->opId,
                         MN_CALL_EVT_START_DTMF_RSLT,
                         TAF_CS_CAUSE_SUCCESS);

    /* 如果有缓存且为STOP_DTMF请求，则直接发送 */
    if (TAF_CALL_GetDtmfBufCnt() > 0)
    {
        /* 获取可以用来发送DTMF的CallId */
        CallId = 0;
        if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
        {
            MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfCnf: Dtmf Not Allowed!");
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        pstListHead = TAF_CALL_GetDtmfListHead();
        /*lint -e961*/
        pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        if (0 == pstNode->stDtmf.usOnLength)
        {
            *pstDtmfCurInfo = pstNode->stDtmf;

            /* 从过滤表中删除节点 */
            TAF_CALL_DelDtmfNode(pstNode);

            if (VOS_OK != MN_CALL_SendCcStopDtmfReq(CallId))
            {
                TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
                MN_ERR_LOG("TAF_CALL_RcvCcStartDtmfCnf: Send Stop Dtmf Failed!");
                return;
            }

            /* 发送成功，更新DTMF状态 */
            TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);
            return;
        }
    }

    /* 没有缓存，或缓存为START_DTMF请求，则启动定时器，更改DTMF状态 */
    MN_CALL_StartTimer(TAF_CALL_TID_DTMF_ON_LENGTH, 0, pstDtmfCurInfo->usOnLength, VOS_RELTIMER_NOLOOP);

    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_RcvCcStartDtmfRej
 功能描述  : 处理MNCC_START_DTMF_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID  TAF_CALL_RcvCcStartDtmfRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    MN_CALL_ID_T                        CallId;

    /* 判断状态是否异常 */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_WAIT_START_CNF)
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfRej: Dtmf State Error!");
        return;
    }

    /* 回复DTMF正式响应事件 */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                         pstDtmfCurInfo->opId,
                         MN_CALL_EVT_START_DTMF_RSLT,
                         TAF_CS_CAUSE_DTMF_REJ);

    /* 若缓存为空，则重置缓存及DTMF状态，退出 */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* 有缓存，若为STOP_DTMF请求，则直接释放此缓存，之后若为START_DTMF请求，则发出 */
    pstListHead = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint +e961*/

    if (0 == pstNode->stDtmf.usOnLength)
    {
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* 从过滤表中删除节点 */
        TAF_CALL_DelDtmfNode(pstNode);

        /* 回复STOP_DTMF的正式响应 */
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_DTMF_REJ);

        /* 如果缓存为空，则直接重置缓存及DTMF状态，退出 */
        if (0 == TAF_CALL_GetDtmfBufCnt())
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* 缓存不为空，则为START_DTMF请求，准备发出 */
        /*lint -e961*/
        pstNode = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/
    }

    /* 获取可以用来发送DTMF的CallId，获取失败则清空缓存重置DTMF状态，退出 */
    CallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfRej: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* 从缓存中取出节点，发出START_DTMF请求 */
    *pstDtmfCurInfo = pstNode->stDtmf;

    /* 从过滤表中删除节点 */
    TAF_CALL_DelDtmfNode(pstNode);

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        MN_ERR_LOG("TAF_CALL_RcvCcStartDtmfRej: Send Stop Dtmf Failed!");
        return;
    }

    /* 发送成功，更新DTMF状态 */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_RcvCcStopDtmfCnf
 功能描述  : 处理MNCC_STOP_DTMF_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
  2.日    期   :2013年10月24日
    作    者   :z00161729
    修改内容   :DTS2013102403705:dtmf不支持off_length参数，SBM IOT认证需要stop dtmf req和下一个start dtmf req间隔大于70ms小于600ms
*****************************************************************************/
VOS_VOID  TAF_CALL_RcvCcStopDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    MN_CALL_ID_T                        CallId;
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;

    /* 判断状态是否异常 */
    enDtmfState = TAF_CALL_GetDtmfState();
    if ( (enDtmfState != TAF_CALL_DTMF_WAIT_STOP_CNF)
      && (enDtmfState != TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF) )
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStopDtmfCnf: Dtmf State Error!");
        return;
    }

    /* 如果是用户发出的STOP_DTMF需要回复正式响应事件 */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    if (enDtmfState != TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF)
    {
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_SUCCESS);
    }

    /* offlength长度不为0时需要启动定时器，定时器超时再下发下一条start dtmf req，如果offlength为0则直接处理缓存 */
    if (pstDtmfCurInfo->usOffLength != 0)
    {
       MN_CALL_StartTimer(TAF_CALL_TID_DTMF_OFF_LENGTH, 0, pstDtmfCurInfo->usOffLength, VOS_RELTIMER_NOLOOP);
       TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_OFF_LENGTH_TIME_OUT);
       return;
    }

    /* 若缓存为空，则重置缓存及DTMF状态，退出 */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* 有缓存，若为STOP_DTMF请求，则直接释放此缓存，之后若为START_DTMF请求，则发出 */
    pstListHead = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint +e961*/

    if (0 == pstNode->stDtmf.usOnLength)
    {
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* 从过滤表中删除节点 */
        TAF_CALL_DelDtmfNode(pstNode);

        /* 回复STOP_DTMF的正式响应 */
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_SUCCESS);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

        /* 如果缓存为空，则直接重置缓存及DTMF状态，退出 */
        if (TAF_CALL_GetDtmfBufCnt() == 0)
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* 缓存不为空，则为START_DTMF请求，准备发出 */
        /*lint -e961*/
        pstNode = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/
    }

    /* 获取可以用来发送DTMF的CallId，获取失败则清空缓存重置DTMF状态，退出 */
    CallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStopDtmfCnf: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* 从缓存中取出节点，发出START_DTMF请求 */
    *pstDtmfCurInfo = pstNode->stDtmf;

    /* 从过滤表中删除节点 */
    TAF_CALL_DelDtmfNode(pstNode);

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        MN_ERR_LOG("TAF_CALL_RcvCcStopDtmfCnf: Send Stop Dtmf Failed!");
        return;
    }

    /* 发送成功，更新DTMF状态 */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    return;
}
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_DeleteAllCallEntities
 功能描述  : 清除所有呼叫管理实体
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_CALL_DeleteAllCallEntities( VOS_VOID)
{
    MN_CALL_MGMT_STRU                  *pstMnEntity = VOS_NULL_PTR;
    VOS_UINT8                           i;

    /* 遍历所有实体,清除所有bused标志为VOS_TRUE的实体信息 */
    pstMnEntity = TAF_CALL_GetCallEntityAddr();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstMnEntity->bUsed)
        {
            MN_CALL_DeleteCallEntity(pstMnEntity->stCallInfo.callId);
        }

        pstMnEntity++;
    }

    return;
}




#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcDtmfBuffer
 功能描述  : 在SRVCC成功后，处理同步过来的DTMF请求消息

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_ProcDtmfBuffer(VOS_VOID)
{
    HI_LIST_S                          *pstListHead    = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode        = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo = VOS_NULL_PTR;
    MN_CALL_ID_T                        ucCallId;

    /* 如果当前有补充业务事件正在进行，暂不处理DTMF */
    if (VOS_TRUE == MN_CALL_IsCallSupsCmdInProgress())
    {
        return;
    }

    /* 检查是否有DTMF缓存 */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        return;
    }

    /* 获取可以用来发送DTMF的CallId */
    ucCallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&ucCallId))
    {
        MN_WARN_LOG("TAF_CALL_ProcDtmfBuffer: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* 获取缓存的首个DTMF请求 */
    pstListHead     = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode         = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint +e961*/

    /* 这是停止DTMF请求 */
    if (0 == pstNode->stDtmf.usOnLength)
    {
        /* 从过滤表中删除节点 */
        TAF_CALL_DelDtmfNode(pstNode);

        if (VOS_OK != MN_CALL_SendCcStopDtmfReq(ucCallId))
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            MN_ERR_LOG("TAF_CALL_ProcDtmfBuffer: Send Stop Dtmf Failed!");
            return;
        }

        /* 发送成功，更新DTMF状态 */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);
        return;
    }
    /* 这是启动DTMF请求 */
    else
    {
        pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();

        /* 从缓存中取出节点，发出START_DTMF请求 */
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* 从过滤表中删除节点 */
        TAF_CALL_DelDtmfNode(pstNode);

        if (VOS_OK != MN_CALL_SendCcStartDtmfReq(ucCallId, pstDtmfCurInfo->cKey))
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            MN_ERR_LOG("TAF_CALL_ProcDtmfBuffer: Send Start Dtmf Failed!");
            return;
        }

        /* 发送成功，更新DTMF状态 */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);
    }
}

/*****************************************************************************
 函 数 名  : TAF_CALL_MapCallStateToCcState
 功能描述  : 根据call状态生成CC状态
 输入参数  : pstCcInfo －－ CC信息指针
             enCallState －－ call呼叫状态

 输出参数  : 无

 返回值    : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_MapCallStateToCcState(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    switch (enCallState)
    {
        case MN_CALL_S_ACTIVE:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U10;
            break;

        case MN_CALL_S_HELD:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U10;
            pstCcInfo->enHoldAuxState = NAS_CC_HOLD_AUX_S_CALL_HELD;
            break;

        case MN_CALL_S_ALERTING:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U4;
            break;

        /* Added by y00245242 for VoLTE_PhaseIII 项目, 2014-1-3, begin */
        case MN_CALL_S_WAITING_ACCEPT:
        /* Added by y00245242 for VoLTE_PhaseIII 项目, 2014-1-3, end */
        case MN_CALL_S_WAITING:
        case MN_CALL_S_INCOMING:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U7;
            break;

        default:
            /* It been filtered in TAF_CALL_CreateCallEntitiesWithImsCallInfo and should not happen! */
            break;
    }
}


/*****************************************************************************
 函 数 名  : TAF_CALL_GetInfoTransCap
 功能描述  : 转换CC能力参数中的信息传输能力
 输入参数  : CallId -- call ID
             pEnInfoTransCap1 －－ 信息传输能力1指针
             pEnInfoTransCap2 －－ 信息传输能力2指针
             penBcRepeatInd －－ BC重复指示指针

 输出参数  : 无

 返回值    : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_GetInfoTransCap(
    MN_CALL_ID_T                        CallId,
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8   *pEnInfoTransCap1,
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8   *pEnInfoTransCap2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
)
{
    MN_CALL_MGMT_STRU                   stMgmtEntity;
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    pstCustomCfgAddr = VOS_NULL_PTR;

    PS_MEM_SET(&stMgmtEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    MN_CALL_GetMgmtEntityInfoByCallId(CallId, &stMgmtEntity);

    switch (stMgmtEntity.stCallInfo.enCallType)
    {
        case MN_CALL_TYPE_VOICE:
        case MN_CALL_TYPE_EMERGENCY:
            {
                /* 获取特性控制NV地址 */
                pstCustomCfgAddr = MN_CALL_GetCustomCfgInfo();

                /* 填写BC参数的Octet 3*/
                if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
                {

                    if ( ( MN_CALL_ALS_LINE_NO_2 == MN_CALL_GetAlsLineInfo() )
                      && ( MN_CALL_DIR_MT != stMgmtEntity.stCallInfo.enCallDir )
                      && ( MN_CALL_TYPE_EMERGENCY != stMgmtEntity.stCallInfo.enCallType ) )
                    {
                        /*ITC需要根据当前使用的线路号进行赋值,线路1时ITC取值speech,线路2时取
                          值Auxiliary speech*/
                        *pEnInfoTransCap1 = NAS_CC_ITC_AUXILIARY_SPEECH;
                    }
                    else
                    {
                        *pEnInfoTransCap1 = NAS_CC_ITC_SPEECH;
                    }
                }
                else
                {
                    *pEnInfoTransCap1 = NAS_CC_ITC_SPEECH;
                }
            }
            break;

       /*
        * data configure information is not reported by IMSA, it is a problem to create BC
        * parameter for CS data call !!! Don't support it now.
        */
        case MN_CALL_TYPE_VIDEO:
        case MN_CALL_TYPE_FAX:
        case MN_CALL_TYPE_CS_DATA:
        default:
            break;
    }

    *penBcRepeatInd = MN_CALL_REP_IND_NULL;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_MapCallInfoToCcInfo
 功能描述  : 根据call模块信息生成CC需要的信息，包括BC参数，call状态等
 输入参数  : pstCcInfo -- CC信息指针


 输出参数  : 无

 返回值    : pucCallNum －－ 返回call数目

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月11日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年1月7日
    作    者   : y00245242
    修改内容   : 修改SRVCC过程中呼叫实体创建
*****************************************************************************/
VOS_VOID TAF_CALL_MapCallInfoToCcInfo(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    VOS_UINT8                          *pucCallNum
)
{
    MN_CALL_MGMT_STRU                  *pstMnEntity = VOS_NULL_PTR;
    VOS_UINT8                           i;
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enInfoTransCap1;
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enInfoTransCap2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;

    enInfoTransCap1 = NAS_CC_ITC_RESERVED;
    enInfoTransCap2 = NAS_CC_ITC_RESERVED;
    pstMnEntity = TAF_CALL_GetCallEntityAddr();

    *pucCallNum = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstMnEntity->bUsed)
        {
            pstMnEntity++;
            continue;
        }

        TAF_CALL_MapCallStateToCcState(pstCcInfo, pstMnEntity->stCallInfo.enCallState);

        if (MN_CALL_IN_MPTY == pstMnEntity->stCallInfo.enMptyState)
        {
            pstCcInfo->enMptyAuxState = NAS_CC_MPTY_AUX_S_CALL_IN_MPTY;
        }
        else
        {
            pstCcInfo->enMptyAuxState = NAS_CC_MPTY_AUX_S_IDLE;
        }

        pstCcInfo->ucTi     = (VOS_UINT8)pstMnEntity->ulTi;
        pstCcInfo->ucCallId = pstMnEntity->stCallInfo.callId;

        /*
         * CC only need information Transfer capability, so convert it.
         */
        TAF_CALL_GetInfoTransCap(pstMnEntity->stCallInfo.callId, &enInfoTransCap1, &enInfoTransCap2, &enBcRepeatInd);

        /* set BC1 */
        pstCcInfo->stBC1.IsExist             = VOS_TRUE;
        pstCcInfo->stBC1.Octet3.InfoTransCap = enInfoTransCap1;

        if (MN_CALL_REP_IND_ALTER == enBcRepeatInd)
        {
            /* set BC2 */
            pstCcInfo->stBC2.IsExist             = VOS_TRUE;
            pstCcInfo->stBC2.Octet3.InfoTransCap = enInfoTransCap2;
        }

        pstMnEntity++;
        pstCcInfo++;
        (*pucCallNum)++;
    }

    return;
}

/* 删除此函数 */

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcMnccSrvccStart
 功能描述  : 处理CC指示的SRVCC启动指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013-12-10
    作    者   : w00176964
    修改内容   : 新增函数
  2.日    期   : 2013年12月23日
    作    者   : y00245242
    修改内容   : 增加SRVCC缓存处理
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcMnccSrvccStart(VOS_VOID)
{
    /* 这里临时圈掉函数调用的方式读取call信息 */
#if 0
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucRealCallNum;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulBeginSlice;
    VOS_UINT32                          ulEndSlice;
    VOS_UINT32                          ulSlice;
    MNCC_ENTITY_STATUS_STRU             astEntitySta[MNCC_MAX_ENTITY_NUM];
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstCallInfo = VOS_NULL_PTR;
#endif

    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_START);

#if 0
    /* 为解决IMSA通过异步接口通知CALL模块呼叫信息导致的时序问题(SRVCC先成功,后收到IMSA的同步呼叫信息指示) */
    /* CALL调用IMSA的API接口,IMSA调用SDK的API接口 */

    /* 先分配内存 */
    pstCallInfo = (CALL_IMSA_SRVCC_CALL_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU) * CALL_IMSA_MAX_ENTITY_NUM);

    if (VOS_NULL_PTR == pstCallInfo)
    {
        /* 异常打印 */
        MN_ERR_LOG("TAF_CALL_ProcMnccSrvccStart: alloc mem failed!");

        return;
    }

    ucCallNum = 0;

    PS_MEM_SET(pstCallInfo, 0x00, sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU) * CALL_IMSA_MAX_ENTITY_NUM);

    /* 加任务锁,防止其他高优先级任务抢占,导致API的调用过程被中断 */
    VOS_TaskLock();
    ulBeginSlice = VOS_GetSlice();

    ulRslt    = CALL_IMSA_GetSrvccCallInfo(&ucCallNum, pstCallInfo);

    ulEndSlice = VOS_GetSlice();
    VOS_TaskUnlock();

    ulSlice = ulEndSlice - ulBeginSlice;

    vos_printf("TAF_CALL_ProcMnccSrvccStart, call imsa api time length,tick = 0x%x\r\n", ulSlice);

    /* LOG出调用IMSA的API接口，用于可维可测 */
    //TAF_CALL_LogImsaApiGetSrvccCallInfo(ulRslt, ucCallNum, pstCallInfo);

    if (VOS_FALSE == ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstCallInfo);

        return;
    }

    /* 映射呼叫实体 */
    TAF_CALL_CreateCallEntitiesWithImsCallInfo(ucCallNum, pstCallInfo);

    /* 将CALL模块的呼叫信息映射成CC模块的呼叫信息 */
    PS_MEM_SET(&astEntitySta[0], 0, sizeof(MNCC_ENTITY_STATUS_STRU) * MNCC_MAX_ENTITY_NUM);

    /* get the actual number of call entity created */
    ucRealCallNum = TAF_CALL_GetCallEntityNum();

    TAF_CALL_MapCallInfoToCcInfo(&astEntitySta[0], ucRealCallNum);

    /* 通知CC模块呼叫信息MNCC_SRVCC_CALL_INFO_NOTIFY */
    TAF_CALL_SendCcSrvccCallInfoNtf(ucRealCallNum, astEntitySta);
#endif

    /* 通知IMSA模块SRVCC状态消息 */
    TAF_CALL_SendImsaSrvccStatusNtf(CALL_IMSA_SRVCC_STATUS_START);

#if 0
    /* 释放分配的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstCallInfo);

    return;
#endif
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcMnccSrvccSucc
 功能描述  : 处理CC指示的SRVCC成功指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013-12-10
    作    者   : w00176964
    修改内容   : 新增函数
  2.日    期   : 2013-12-14
    作    者   : y00245242
    修改内容   : 增加SRVCC缓存功能
  3.日    期   : 2014年03月01日
    作    者   : s00217060
    修改内容   : CS域业务状态变化时通知MTC
  4.日    期   : 2014年11月06日
    作    者   : s00217060
    修改内容   : DTS2014110608091:IMS电话时不处理cs域的paging inds
  5.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090607329
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcMnccSrvccSucc(VOS_VOID)
{
    VOS_UINT8                           i;
    MN_CALL_MGMT_STRU                  *pstMnEntity = VOS_NULL_PTR;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_BUTT;

    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_SUCCESS);
    TAF_SDC_SetImsCallExistFlg(VOS_FALSE);
    
    
    TAF_SndMmaImsSrvInfoNotify(VOS_FALSE);

    /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 给MTC模块上报当前CS域业务状态 */
    TAF_SendMtcCsSrvInfoInd();
#endif
    /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, end */

    /* 通知IMSA模块SRVCC状态消息 */
    TAF_CALL_SendImsaSrvccStatusNtf(CALL_IMSA_SRVCC_STATUS_SUCCESS);

    pstMnEntity = TAF_CALL_GetCallEntityAddr();
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* check whether or not call state is incoming when SRVCC success is received.
         * If yes, start ring timer. */
        if (VOS_TRUE == pstMnEntity[i].bUsed)
        {
            if (MN_CALL_S_INCOMING == pstMnEntity[i].stCallInfo.enCallState)
            {
                MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_LOOP);
                break;
            }

            if (MN_CALL_TYPE_EMERGENCY == pstMnEntity[i].stCallInfo.enCallType)
            {
                enCallType = MN_CALL_TYPE_EMERGENCY;
            }
            
            /*****************************************************************************
             from section 12.2.3B.3.1 in 24.237
             If the SC UE:
             1) as received a terminating call which is in the early dialog state according to
                the conditions in subclauses 12.1 and 12.2.3B.1; and
             2) as sent a SIP 200 (OK) response (i.e. user answers the call when in the PS domain)
                prior to successfully performing access transfer to the CS domain;

             then the UE sends a CC CONNECT message and transitions to Active (U10) state
             as described in 3GPP TS 24.008.
             *****************************************************************************/
            if (MN_CALL_S_WAITING_ACCEPT == pstMnEntity[i].stCallInfo.enCallState)
            {
                /* 回退呼叫状态到incoming状态，等待connect ack */
                pstMnEntity[i].stCallInfo.enCallState = MN_CALL_S_INCOMING;

                MN_CALL_CallAnswerReqProc(pstMnEntity[i].stCallInfo.clientId,
                                          pstMnEntity[i].stCallInfo.opId,
                                          pstMnEntity[i].stCallInfo.callId,
                                          VOS_NULL_PTR);

                break;
            }
        }
    }

    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, enCallType);

    /* TCH已分配，处理DTMF请求，否则在收到SYNC IND中处理该消息 */
    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        /* 检查是否有DTMF请求需要发送 */
        TAF_CALL_ProcDtmfBuffer();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcMnccSrvccFail
 功能描述  : 处理CC指示的SRVCC失败指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013-12-10
    作    者   : w00176964
    修改内容   : 新增函数
  2.日    期   : 2013-12-23
    作    者   : y00245242
    修改内容   : 增加SRVCC缓存功能
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcMnccSrvccFail(VOS_VOID)
{
    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_FAIL);

    MN_CALL_SetChannelOpenFlg(VOS_FALSE);

    /* 销毁IMSA同步过来的呼叫信息 */
    TAF_CALL_DeleteAllCallEntities();

    /* 清除业务信道建立标志 */
    MN_CALL_SetTchStatus(VOS_FALSE);

    /* 清除DTMF信息 */
    TAF_CALL_InitDtmfCtx();

    /* 通知IMSA模块SRVCC状态消息 */
    TAF_CALL_SendImsaSrvccStatusNtf(CALL_IMSA_SRVCC_STATUS_FAIL);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcMnccSrvccStatusInd
 功能描述  : 处理MNCC_SRVCC_STATUS_IND原语
 输入参数  : pstSrvccMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013-9-25
    作    者   : w00176964
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcMnccSrvccStatusInd(
    MNCC_SRVCC_STATUS_IND_STRU         *pstSrvccMsg
)
{
    switch (pstSrvccMsg->enSrvccStatus)
    {
        case NAS_MNCC_SRVCC_STATUS_START:

            TAF_CALL_ProcMnccSrvccStart();
            break;

        case NAS_MNCC_SRVCC_STATUS_SUCCESS:

            TAF_CALL_ProcMnccSrvccSucc();
            break;

        case NAS_MNCC_SRVCC_STATUS_FAIL:

            TAF_CALL_ProcMnccSrvccFail();
            break;

        default:

            MN_ERR_LOG("TAF_CALL_ProcMnccSrvccStatusInd: Unexpected srvcc status!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcSrvccSyncInfo
 功能描述  : 收到TCH分配指示时，处理SRVCC相关信息

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月15日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_ProcSrvccSyncInfo(VOS_VOID)
{
    if (MN_CALL_SRVCC_STATE_SUCCESS == TAF_CALL_GetSrvccState())
    {
        if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
        {
            TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_BUTT);

            MN_CALL_SetTchStatus(VOS_TRUE);

            TAF_CALL_ProcDtmfBuffer();
        }
    }
}
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcessEcallPeriodTimerLen
 功能描述  : 检查eCall重拨是否存在，如果存在且不在等待PSAP回呼，返回VOS_TRUE

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- eCall重拨存在
             VOS_FALSE -- eCall重拨存在

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月08日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_ProcessEcallPeriodTimerLen(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulEcallPeriodTimerLen;

    /* 如果eCall period定时器在运行，获取eCall period定时器 */
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD))
    {
        ulEcallPeriodTimerLen = MN_CALL_GetTimerRemainLen(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);

        /* 更新eCall period定时器剩余时长，为后续eCall重拨使用 */
        TAF_CALL_UpdateEcallPeriodRemainTimerLen(ulEcallPeriodTimerLen);
    }
}

/*****************************************************************************
 函 数 名  : TAF_CALL_IsEcallRedialExist
 功能描述  : 检查eCall重拨是否存在，如果存在且不在等待PSAP回呼，返回VOS_TRUE

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- eCall重拨存在
             VOS_FALSE -- eCall重拨存在

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月08日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsEcallRedialExist(VOS_VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstCallMsgBuff    = VOS_NULL_PTR;
    VOS_UINT8                           ucEcallFlag;

    pstCallMsgBuff = MN_CALL_GetBufferedMsg();

    if (VOS_TRUE == pstCallMsgBuff->bitOpBufferedSetupMsg)
    {
        ucEcallFlag = TAF_CALL_IsCallTypeEmgencyCall(pstCallMsgBuff->stBufferedSetupMsg.ucCallId);

        if ((MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
         && (VOS_TRUE                    == ucEcallFlag))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcEcallRel
 功能描述  : 收到呼叫释放后，处理eCall流程

 输入参数  : pstCallEntity -- call呼叫实体信息

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月08日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2014年07月14日
   作    者   : b00269685
   修改内容   : 添加PSAP类型
*****************************************************************************/
VOS_VOID TAF_CALL_ProcEcallRel(
    MN_CALL_MGMT_STRU                  *pstCallEntity
)
{
    MN_CALL_MGMT_STRU                  *pstCallEntityAddr = VOS_NULL_PTR;
    MN_CALL_MSG_BUFF_STRU              *pstCallMsgBuff    = VOS_NULL_PTR;
    VOS_UINT32                          ulEcallPeriodTimerLen;
    VOS_UINT32                          ulCallRedialIntervalLen;

    /* 呼叫实体无效 */
    if (VOS_FALSE == pstCallEntity->bUsed)
    {
        return;
    }

    /* 非MO eCall呼叫返回 */
    if ((MN_CALL_TYPE_MIEC         != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_AIEC         != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_TEST         != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_RECFGURATION != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_PSAP_ECALL   != pstCallEntity->stCallInfo.enCallType))
    {
        return;
    }

    /* 如果T2定时器在运行，停止T2定时器 */
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T2))
    {
        /* 停止T2定时器 */
        MN_CALL_StopTimer(TAF_CALL_TID_T2);
    }

    /* "等待MT eCall标志位"在MO eCall接通后被设置，见函数MN_CALL_ProcMnccSetupCnf，
     * 在eCall释放后，如果该标志位为TRUE, 启动等待eCall时长定时器T9，此时清除该标志
     */
    if (VOS_TRUE == TAF_CALL_GetWaitingMtEcallFlag())
    {
        /* 启动T9定时器 */
        MN_CALL_StartTimer(TAF_CALL_TID_T9, 0, 0, VOS_RELTIMER_NOLOOP);

        /* 清除"等待mt eCall呼叫标志位" */
        TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);
    }

    /* 如果呼叫为MO 挂断，清除重拨缓存 */
    if ((VOS_TRUE == pstCallEntity->stCallInfo.stDiscDir.ucDiscCallFlag)
     && (VOS_TRUE == pstCallEntity->stCallInfo.stDiscDir.ucIsUser))
    {
        MN_CALL_ClearBufferedMsg();

        return;
    }

    pstCallMsgBuff = MN_CALL_GetBufferedMsg();

    /* 获取eCall剩余重拨period时长 */
    ulEcallPeriodTimerLen   = TAF_CALL_GetEcallPeriodRemainTimerLen();
    /* 获取eCall重拨间隔时长 */
    ulCallRedialIntervalLen = MN_CALL_GetTimerLen(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);

    if ((VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS != TAF_CALL_GetEcallMsdTransStatus())
     && (VOS_TRUE                               == pstCallMsgBuff->bitOpBufferedSetupMsg)
     && (ulCallRedialIntervalLen                <= ulEcallPeriodTimerLen))
    {
        /* 修改呼叫状态dialing，重新创建呼叫实体, 并上报orig信息，告诉用于重拨开始 */
        pstCallEntity->stCallInfo.enCallState              = MN_CALL_S_DIALING;
        pstCallEntity->stCallInfo.stDiscDir.ucDiscCallFlag = VOS_FALSE;

        pstCallEntityAddr = TAF_CALL_GetCallEntityAddr();
        PS_MEM_CPY((pstCallEntityAddr+pstCallEntity->stCallInfo.callId - 1),
                   pstCallEntity,
                   sizeof(MN_CALL_MGMT_STRU));

        /* 上报ORIG事件 */
        MN_CALL_ReportEvent(pstCallEntity->stCallInfo.callId, MN_CALL_EVT_ORIG);

        /* 按剩余时长，启动重拨尝试定时器 */
        MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, 0, ulEcallPeriodTimerLen, VOS_RELTIMER_NOLOOP);

        /* 启动重拨尝试间隔定时器 */
        MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, 0, 0, VOS_RELTIMER_NOLOOP);

        /* 初始化MSD传输状态为BUTT */
        TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);

        return;
    }

    /* 清除重拨缓存 */
    MN_CALL_ClearBufferedMsg();
}
#endif
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-8, end */

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
