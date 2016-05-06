/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcAirMsgProc.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月5日
  最近修改   : 2007年9月5日
  功能描述   : 接收和处理来自空口的信令消息
  函数列表   : NAS_CC_SendNextStartDtmf
               NAS_CC_ProcProtocolError
               NAS_CC_ProcAlertingMsg
               NAS_CC_ProcCallProceedingMsg
               NAS_CC_ProcCcEstablishment
               NAS_CC_ProcConnectAckMsg
               NAS_CC_ProcConnectMsg
               NAS_CC_ProcDisconnectMsg
               NAS_CC_ProcFacilityMsg
               NAS_CC_ProcHoldAckMsg
               NAS_CC_ProcHoldRejMsg
               NAS_CC_ProcModifyCompleteMsg
               NAS_CC_ProcModifyMsg
               NAS_CC_ProcModifyRejMsg
               NAS_CC_ProcNotify
               NAS_CC_ProcProgressMsg
               NAS_CC_ProcRecall
               NAS_CC_ProcReleaseCompleteMsg
               NAS_CC_ProcReleaseMsg
               NAS_CC_ProcRetrieveAckMsg
               NAS_CC_ProcRetrieveRejMsg
               NAS_CC_ProcSetupMsg
               NAS_CC_ProcStartDtmfAck
               NAS_CC_ProcStartDtmfRej
               NAS_CC_ProcStatus
               NAS_CC_ProcStatusEnquiry
               NAS_CC_ProcStopDtmfAck
               NAS_CC_ProcAirMsg
  修改历史   :
  1.日    期   : 2007年9月5日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2008年10月20日
    作    者   : h44270
    修改内容   : 问题单号:A32D14153,来电时，用户尚未接听电话就打开了声码器,，AMR速率变换没有上报
  4.日    期   : 2008年10月25日
    作    者   : s62952
    修改内容   : 问题单号:A32D14142,在通话117时，拨打1，2等DTMF字符时，会中断117通话
  5.日    期   : 2010年01月28日
    作    者   : f62575
    修改内容   : 问题单号AT2D16557, GCF测试26.5.5.3.1.2；
                 CC接收到网络过来的STATUS消息缺失必选IE，应回复STATUS消息，
                 错误原因值96

  6.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  7.日    期   : 2010年8月4日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS
******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasCcInclude.h"
#include  "MnCall.h"
#include "NasCcCtx.h"
#include "NasCcProcNvim.h"

#include "NasUsimmApi.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_AIRMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/* 最小空口消息长度 */
#define  NAS_CC_MIN_AIR_MSG_LEN             2

/* PD/TI字段在消息中的所在位置 */
#define  NAS_CC_MSG_PD_TI_POS               0

/* Message Type字段在消息中的所在位置 */
#define  NAS_CC_MSG_TYPE_POS                1

extern VOS_UINT32 AT_CheckModemDataMode(VOS_VOID);


/*****************************************************************************
  3 变量定义
*****************************************************************************/
/* 解码缓存，用于缓存解码后的空口消息 */
LOCAL  NAS_CC_AIR_MSG_UNION             f_unCcDecodeBuf;

LOCAL VOS_VOID  NAS_CC_ProcProtocolError(
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_PROTOCOL_ERR_ENUM_U8            enErrno
);

/*lint -save -e958 */

/*****************************************************************************
  4 函数实现
*****************************************************************************/
LOCAL  VOS_VOID NAS_CC_ProcProgressIndicator(
    NAS_CC_ENTITY_ID_T                      entityId,
    const NAS_CC_IE_PROGRESS_INDICATOR_STRU *pstProgInd
)
{
    /*
    [5.5.1 In-band tones and announcements]
    A progress indicator IE indicates user attachment if it specifies a progress
    description in the set {1, 2, 3} or in the set {6, 7, 8, ..., 20}.
    ......
    attach the user connection for speech as soon as an appropriate channel in
    speech mode is available.
    */
    if (((pstProgInd->Octet4.ProgDesc >= 1)
      && (pstProgInd->Octet4.ProgDesc <= 3))
     || ((pstProgInd->Octet4.ProgDesc >= 6)
      && (pstProgInd->Octet4.ProgDesc <= 20)))
    {
        NAS_CC_AttachUserConn(entityId, NAS_CC_ITC_SPEECH);
    }
}

/*****************************************************************************
 函 数 名  : NAS_CC_CheckMtSetupCondIe
 功能描述  : 检查Mt Setup中的条件ie项
 输入参数  : pstMsg   - 解码后的SETUP消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理

*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckMtSetupCondIe(
     const NAS_CC_MSG_SETUP_MT_STRU     *pstMsg
)
{
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
    if ( (VOS_TRUE == pstMsg->stBC1.IsExist)
      && (VOS_TRUE == pstMsg->stBC2.IsExist)
      && ( VOS_FALSE == pstMsg->stBCRepeatInd.IsExist))
    {
        return VOS_ERR;
    }

    if ( (VOS_TRUE == pstMsg->stLLC1.IsExist)
      && (VOS_TRUE == pstMsg->stLLC2.IsExist)
      && (VOS_FALSE == pstMsg->stLLCRepeatInd.IsExist))
    {
        return VOS_ERR;
    }

    if ( ( VOS_TRUE == pstMsg->stHLC1.IsExist)
      && (VOS_TRUE == pstMsg->stHLC2.IsExist)
      && (VOS_FALSE == pstMsg->stHLCRepeatInd.IsExist))
    {
        return VOS_ERR;
    }
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_CC_CheckCallProceedingCondIe
 功能描述  : 检查Mt call proceeding中的条件ie项
 输入参数  : pstMsg   - 解码后的SETUP消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckCallProceedingCondIe(
     const NAS_CC_MSG_CALL_PROC_STRU    *pstMsg
)
{
    if ( (VOS_TRUE == pstMsg->stBC1.IsExist)
      && (VOS_TRUE == pstMsg->stBC2.IsExist)
      && (VOS_FALSE == pstMsg->stRepeatInd.IsExist))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcFacIE
 功能描述  : 处理facility IE
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的DISCONNECT消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID NAS_CC_ProcFacIE(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_IE_FACILITY_STRU             *pstFacIE
    )
{
    NAS_SS_OPERATION_ENUM_U8  enOperation;
    NAS_CC_FACILITY_INFO_STRU stFacInfo;

    (VOS_VOID)NAS_CC_GetFacilityInfo(pstFacIE->aucFacility, &stFacInfo);

    /* 取得facility中的ss operation code */
    if (stFacInfo.bOpCodePresent)
    {
        enOperation = stFacInfo.enOpCode;
    }
    else
    {
        if (NAS_CC_RestoreSsOperation(entityId,
                                      stFacInfo.ucInvokeID,
                                      &enOperation) != VOS_OK)
        {
            NAS_CC_ERR_LOG("NAS_CC_ProcFacilityMsg: Unknown invoke ID.");
            return;
        }
    }

    switch (enOperation)
    {
    case NAS_SS_OPERATION_BUILD_MPTY:
    case NAS_SS_OPERATION_HOLD_MPTY:
    case NAS_SS_OPERATION_RETRIEVE_MPTY:
    case NAS_SS_OPERATION_SPLIT_MPTY:
        NAS_CC_StopTimer(entityId, TI_NAS_CC_MPTY);

        if (NAS_SS_COMPONENT_TYPE_TAG_RTN_RSLT == stFacInfo.ucCompType)
        {
            NAS_CC_HandleMptyEvent(entityId,
                                   NAS_CC_MPTY_EVT_SUCCESS,
                                   enOperation);
        }
        else
        {
            NAS_CC_HandleMptyEvent(entityId,
                                   NAS_CC_MPTY_EVT_FAIL,
                                   enOperation);
        }
        break;
    case NAS_SS_OPERATION_EXPLICIT_CT:
        NAS_CC_StopTimer(entityId, TI_NAS_CC_ECT);
        break;
    default:
        break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcSetupMsg
 功能描述  : 处理来自网络的SETUP消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的SETUP消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年8月21日
    作    者   : h44270
    修改内容   : 问题单号DTS2010081802507
  3.日    期   : 2010年11月18日
    作    者   : h44270
    修改内容   : 问题单号DTS2010111601486/DTS2010111804800
  4.日    期   : 2013年7月18日
    作    者   : z60575
    修改内容   : 问题单号DTS2013071804506,VP,PS并发，删除限制
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcSetupMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_SETUP_MT_STRU      *pstMsg
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;
    /*VOS_UINT32                          ulCheckModemDataState;*/

    /* 判定当前是否能够接受MT呼叫,不能接受的话，清除所有的呼叫状态 */
    if (VOS_FALSE == NAS_CC_IsAllowNewMtCall())
    {
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
        NAS_CC_WARN_LOG("NAS_CC_ProcSetupMsg: INCOMPATIBLE STATE");

#if (FEATURE_ON == FEATURE_PTM)
        /* setup消息按协议检查失败的异常记录 */
        NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_NEW_CALL_NOT_ALLOW);
#endif

        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
    if (VOS_OK != NAS_CC_CheckMtSetupCondIe(pstMsg))
    {
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
        NAS_CC_WARN_LOG("NAS_CC_ProcSetupMsg: Conditional Ie should exist");

#if (FEATURE_ON == FEATURE_PTM)
        /* setup消息按协议检查失败的异常记录 */
        NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_OPTIONAL_IE_ERR);
#endif

        return NAS_PROT_ERR_OPTIONAL_IE_ERR;
    }

    /* 记录呼叫的承载能力参数 */
    if (pstMsg->stBC1.IsExist)
    {
        stBcParams.enItc = pstMsg->stBC1.Octet3.InfoTransCap;
        NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
        if (pstMsg->stBC2.IsExist)
        {
            stBcParams.enItc = pstMsg->stBC2.Octet3.InfoTransCap;
            NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
        }

    }

    NAS_CC_SendMnccMsg(entityId,
                       MNCC_SETUP_IND,
                       pstMsg,
                       sizeof(NAS_CC_MSG_SETUP_MT_STRU));

    NAS_CC_INFO_LOG("NAS_CC_ProcSetupMsg: call state to U6");

    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U6);


    /* 如果消息中存在Progress Indicator，需要进行处理 */
    if (pstMsg->stProgInd.IsExist)
    {
        NAS_CC_ProcProgressIndicator(entityId, &pstMsg->stProgInd);
    }

    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcReleaseMsg
 功能描述  : 处理来自网络的RELEASE消息
 输入参数  : entityId - CC实体ID
             pstMsg   - 解码后的RELEASE消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcReleaseMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_RELEASE_MT_STRU    *pstMsg
)
{
    /*
        3GPP 24.008 5.4.3.3
        The call control entity of the mobile station in any state except the "null"
        state and the "release request" state, shall, upon receipt of a RELEASE
        message: stop all running call control timers; send a RELEASE COMPLETE
        message; release the MM connection; and return to the "null" state.
    */
    NAS_CC_CALL_STATE_ENUM_U8           enCallState = NAS_CC_GetCallState(entityId);
    VOS_UINT8                           ucTi;

    if (NAS_CC_CALL_STATE_U0 == enCallState)
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcReleaseMsg: Incompatible state.", enCallState);

        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
    else
    {
        ucTi = NAS_CC_GetEntityTi(entityId);

        NAS_CC_StopAllTimer(entityId);
        NAS_CC_DetachUserConn(entityId);
        NAS_CC_StopLocalAlertInd();
        if(NAS_CC_CALL_STATE_U19 != enCallState)
        {
            NAS_CC_SendReleaseComplete(ucTi, VOS_FALSE, 0);
        }
        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        /* 通知MN DTMF操作的结果,并清空缓存的DTMF消息 */
        NAS_CC_LocalAbortDtmf(entityId);
        NAS_CC_FlushDTMFBuff(entityId);

        NAS_CC_SendMnccMsg(entityId,
                           MNCC_REL_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_RELEASE_MT_STRU));

        /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
        NAS_CC_ProcSsSwitchCallRelease(entityId);
        /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

        NAS_CC_INFO_LOG("NAS_CC_ProcReleaseMsg: call state to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);

    }

    if(VOS_TRUE == pstMsg->stFacility.IsExist)
    {
        NAS_CC_ProcFacIE(entityId, (NAS_CC_IE_FACILITY_STRU *)&(pstMsg->stFacility));
    }
    return NAS_PROT_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcReleaseCompleteMsg
 功能描述  : 处理来自网络的RELEASE COMPLETE消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的RELEASE COMPLETE消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcReleaseCompleteMsg(
    NAS_CC_ENTITY_ID_T                        entityId,
    const NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU *pstMsg
)
{
/*
    3GPP 24.008 5.4.4.2.5 :
    A call control entity of the mobile station in any call control state shall,
    upon receipt of a RELEASE COMPLETE message from its peer entity in the network:
    stop all running call control timers; release the MM connection; and return
    to the "null" state.
*/
    VOS_UINT8 ucTi = NAS_CC_GetEntityTi(entityId);

    NAS_CC_StopAllTimer(entityId);
    NAS_CC_DetachUserConn(entityId);
    NAS_CC_StopLocalAlertInd();
    NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

    /* 通知MN DTMF操作的结果,并清空缓存的DTMF消息 */
    NAS_CC_LocalAbortDtmf(entityId);
    NAS_CC_FlushDTMFBuff(entityId);

    NAS_CC_SendMnccMsg(entityId,
                       MNCC_REL_CNF,
                       pstMsg,
                       sizeof(NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU));

    /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
    NAS_CC_ProcSsSwitchCallRelease(entityId);
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

    NAS_CC_INFO_LOG("NAS_CC_ProcReleaseCompleteMsg: call state to U0");

    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);


    if(VOS_TRUE == pstMsg->stFacility.IsExist)
    {
        NAS_CC_ProcFacIE(entityId, (NAS_CC_IE_FACILITY_STRU *)(&(pstMsg->stFacility)));
    }

    return NAS_PROT_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcProgressIe
 功能描述  : 处理Progress IE
 输入参数  : entityId - CC实体ID
              ucPi     - Progress indicator
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2015年7月6日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcProgressIe(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_PROGRESS_DESCRIPTION_ENUM_U8 ucPi
)
{
    VOS_UINT8                           ucIstartT310AccordWith3GPP;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard                = NAS_USIMMAPI_IsTestCard();
    ucIstartT310AccordWith3GPP  = NAS_CC_GetProceedingStartT310Flag();

    /* 测试卡严格按照协议做 */
    if ( (VOS_TRUE == ulIsTestCard)
      && ( (ucPi == NAS_CC_PROGRESS_NOT_END_TO_END)
       || (ucPi == NAS_CC_PROGRESS_DEST_IN_NON)
       || (ucPi == NAS_CC_PROGRESS_QUEUEING) ) )
    {
        NAS_CC_SetStartT310Flag(entityId, VOS_FALSE);

        return;
    }
    /*
    5.2.1.3 Receipt of a CALL PROCEEDING message
    Having entered the "call initiated" state, when the call control entity of the mobile station receives a CALL PROCEEDING message, it shall stop timer T303; start timer T310 unless
        - the CALL PROCEEDING message contains a progress indicator IE specifying progress description #1, #2, or #64; or
        - it has received a PROGRESS message containing a progress indicator IE specifying progress description #1, #2, or #64 prior to the CALL PROCEEDING message
    and enter the "mobile originating call proceeding" state.
    Abnormal case:
        If timer T310 elapses before any of the ALERTING, CONNECT or DISCONNECT messages has been received, the mobile station shall perform the clearing procedure described in subclause 5.4.
    */
    if( (VOS_TRUE == ucIstartT310AccordWith3GPP)
     && ( (ucPi == NAS_CC_PROGRESS_NOT_END_TO_END)
       || (ucPi == NAS_CC_PROGRESS_DEST_IN_NON)
       || (ucPi == NAS_CC_PROGRESS_QUEUEING) ) )
    {
        NAS_CC_SetStartT310Flag(entityId, VOS_FALSE);
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_CC_ProcCallProceedingMsg
 功能描述  : 处理来自网络的CALL PROCEEDING消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的CALL PROCEEDING消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcCallProceedingMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_CALL_PROC_STRU     *pstMsg
)
{
/*
    3GPP 24.008 5.2.1.3 :
    Having entered the "call initiated" state, when the call control entity of
    the mobile station receives a CALL PROCEEDING message, it shall stop timer
    T303; start timer T310 unless
    - the CALL PROCEEDING message contains a progress indicator IE specifying
      progress description #1, #2, or #64; or
    - it has received a PROGRESS message containing a progress indicator IE
      specifying progress description #1, #2, or #64 prior to the CALL PROCEEDING
      message
    and enter the "mobile originating call proceeding" state.
*/
    NAS_CC_CALL_STATE_ENUM_U8  enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_BC_PARAMS_STRU      stBcParams;

    if (NAS_CC_CALL_STATE_U1 == enCallState)
    {
        if (VOS_OK != NAS_CC_CheckCallProceedingCondIe(pstMsg))
        {
            NAS_CC_WARN_LOG("NAS_CC_ProcCallProceedingMsg: Conditional Ie should exist");
            return NAS_PROT_ERR_CONDITIONAL_IE_ERR;
        }
        if(pstMsg->stProgInd.IsExist)
        {
            NAS_CC_ProcProgressIe(entityId, pstMsg->stProgInd.Octet4.ProgDesc);
        }
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T303);

        if (NAS_CC_GetStartT310Flag(entityId) == VOS_TRUE)
        {
            NAS_CC_StartTimer(entityId, TI_NAS_CC_T310, 0);
        }

        NAS_CC_SendMnccMsg(entityId,
                           MNCC_CALL_PROC_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_CALL_PROC_STRU));

        NAS_CC_INFO_LOG("NAS_CC_ProcCallProceedingMsg: call state to U3");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U3);

        /* 如果BC改变，需要更新已保存的承载能力参数 */
        if (pstMsg->stBC1.IsExist)
        {
            stBcParams.enItc = pstMsg->stBC1.Octet3.InfoTransCap;
            NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
            if (pstMsg->stBC2.IsExist)
            {
                stBcParams.enItc = pstMsg->stBC2.Octet3.InfoTransCap;
                NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
            }
        }

        /* 如果消息中存在Progress Indicator，需要进行处理 */
        if (pstMsg->stProgInd.IsExist)
        {
            NAS_CC_ProcProgressIndicator(entityId, &pstMsg->stProgInd);
        }

        /* 信道已经接入的情况,需要设置当前使用此信道的每一个呼叫实体.
           避免多个呼叫存在时,原来的呼叫被释放后,就断开信道
           CC在呼叫结束的时候,会清除此标志*/
        if (VOS_TRUE == NAS_CC_IsAttachUserConn())
        {
            NAS_CC_SetUserConnEntity(entityId);
        }

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcCallProceedingMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcAlertingMsg
 功能描述  : 处理来自网络的ALERTING消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的ALERTING消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加ALS功能支持

  3.日    期   : 2010年3月17日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率调整时,本地振铃暂不由MODEM侧实现
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcAlertingMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_ALERTING_MT_STRU   *pstMsg
)
{
/*
    3GPP 24.008 5.2.1.5 :
    When the call control entity of the mobile station in the "call initiated"
    state or "mobile originating call proceeding" state receives an ALERTING
    message then, the call control entity of the mobile station shall stop
    timer T303 and T310 (if running) and shall enter the "call delivered" state.

    In this state, for speech calls:
    - an alerting indication should be given to the user. If the mobile station
      has not attached the user connection then the mobile station shall internally
      generate an alerting indication. If the mobile station has attached the
      user connection then the network is responsible for generating the alerting
      indication and the mobile station need not generate one.
*/
    NAS_CC_CALL_STATE_ENUM_U8  enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_BC_PARAMS_STRU      stBcParams;

    if ((NAS_CC_CALL_STATE_U1 == enCallState)
    || (NAS_CC_CALL_STATE_U3 == enCallState))
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T303);
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T310);

        NAS_CC_SendMnccMsg(entityId,
                           MNCC_ALERT_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_ALERTING_MT_STRU));

        NAS_CC_INFO_LOG("NAS_CC_ProcAlertingMsg: call state to U4");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U4);

        NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);
        if ( (NAS_CC_ITC_SPEECH == stBcParams.enItc)
          || (NAS_CC_ITC_AUXILIARY_SPEECH == stBcParams.enItc) )
        {
            #if 0
            if (NAS_CC_AttachUserConn(entityId, NAS_CC_ITC_SPEECH) != VOS_TRUE)
            {
                NAS_CC_GenarateLocalAlertInd();
            }
            #endif
        }

        /* 信道已经接入的情况,需要设置当前使用此信道的每一个呼叫实体.
           避免多个呼叫存在时,原来的呼叫被释放后,就断开信道
           CC在呼叫结束的时候,会清除此标志*/
        if (VOS_TRUE == NAS_CC_IsAttachUserConn())
        {
            NAS_CC_SetUserConnEntity(entityId);
        }

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcAlertingMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcConnectMsg
 功能描述  : 处理来自网络的CONNECT消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的CONNECT消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加ALS多线路的支持

  3.日    期   : 2012年8月22日
    作    者   : z40661
    修改内容   : DTS20120713601654，多上报了sync_ind消息
  4.日    期   : 2012年10月20日
    作    者   : l65478
    修改内容   : DTS2012101706755，在早指派时没有设置用户连接存在标志
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcConnectMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_CONNECT_MT_STRU    *pstMsg
)
{
/*
    3GPP 24.008 5.2.1.6 :
    The call control entity of the mobile station in the "call initiated" state,
    in the "mobile originating call proceeding" state or in the "call delivered"
    state, shall, upon receipt of a CONNECT message:
    - attach the user connection;
    - return a CONNECT ACKNOWLEDGE message;
    - stop any locally generated alerting indication (if applied);
    - stop timer T303 and T310 (if running);
    - enter the "active" state.
*/
    NAS_CC_CALL_STATE_ENUM_U8  enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_BC_PARAMS_STRU      stBcParams;

    if ((NAS_CC_CALL_STATE_U1 == enCallState)
        || (NAS_CC_CALL_STATE_U3 == enCallState)
        || (NAS_CC_CALL_STATE_U4 == enCallState))
    {
        NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);
        /* 此种场景用于晚指派,当前sync ind消息已经上报了,除非此处未上报 */
        if ( VOS_FALSE == NAS_CC_IsAttachUserConn() )
        {
            if ( (NAS_CC_ITC_SPEECH == stBcParams.enItc)
               ||(NAS_CC_ITC_AUXILIARY_SPEECH == stBcParams.enItc))
            {
                NAS_CC_AttachUserConn(entityId, NAS_CC_ITC_SPEECH);
            }
            else
            {
                NAS_CC_AttachUserConn(entityId, stBcParams.enItc);
            }
        }
        else
        {
            /* 设置用户连接存在标志.用于在早指派时,标志f_bSpeechConnAttached可能已经设置,
               但是用户连接标志还没有设置的情况 */
            NAS_CC_SetUserConnEntity(entityId);
        }
        NAS_CC_SendConnectAck(NAS_CC_GetEntityTi(entityId));
        NAS_CC_StopLocalAlertInd();
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T303);
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T310);
        NAS_CC_SendMnccMsg(entityId,
                           MNCC_SETUP_CNF,
                           pstMsg,
                           sizeof(NAS_CC_MSG_CONNECT_MT_STRU));

        NAS_CC_INFO_LOG("NAS_CC_ProcConnectMsg: call state to U10");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U10);

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcConnectMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcConnectAckMsg
 功能描述  : 处理来自网络的CONNECT ACK消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的CONNECT ACK消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加ALS多线路的支持

  3.日    期   : 2012年8月22日
    作    者   : z40661
    修改内容   : DTS20120713601654，多上报了sync_ind消息
  4.日    期   : 2012年10月20日
    作    者   : l65478
    修改内容   : DTS2012101706755，在早指派时没有设置用户连接存在标志
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8 NAS_CC_ProcConnectAckMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_CONNECT_ACK_STRU   *pstMsg
)
{
/*
    3GPP 24.008 5.2.2.6 :
    In the "connect request" state, the call control entity of the mobile station
    shall, upon receipt of a CONNECT ACKNOWLEDGE message: stop timer T313 and
    enter the "active" state.
*/
    NAS_CC_CALL_STATE_ENUM_U8  enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_BC_PARAMS_STRU      stBcParams;

    if (NAS_CC_CALL_STATE_U8 == enCallState)
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T313);

        NAS_CC_SendMnccMsg(entityId,
                           MNCC_SETUP_COMPL_IND,
                           VOS_NULL_PTR,
                           0);

        NAS_CC_INFO_LOG("NAS_CC_ProcConnectAckMsg: call state to U10");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U10);

        /*
        5.2.2.9 User connection attachment during a mobile terminating call
        For data calls:
        The mobile station shall attach the user connection when receiving the
        CONNECT ACKNOWLEDGE message from the network.
        */
        NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);
        if ( (stBcParams.enItc != NAS_CC_ITC_SPEECH)
           &&(stBcParams.enItc != NAS_CC_ITC_AUXILIARY_SPEECH))
        {

            /* 此种场景用于晚指派,当前sync ind消息已经上报了,除非此处未上报 */
            if ( VOS_FALSE == NAS_CC_IsAttachUserConn() )
            {
                NAS_CC_AttachUserConn(entityId, stBcParams.enItc);
            }
            else
            {
                /* 设置用户连接存在标志.用于在早指派时,标志f_bSpeechConnAttached可能已经设置,
                   但是用户连接标志还没有设置的情况 */
                NAS_CC_SetUserConnEntity(entityId);
            }
        }

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcConnectAckMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcDisconnectMsg
 功能描述  : 处理来自网络的DISCONNECT消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的DISCONNECT消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
 2.日    期   : 2009年7月18日
    作    者   : s62952
    修改内容: 根据问题单AT2D12925修改

  3.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 测试ECT时，未能上报Disconnect消息
  4.日    期   : 2010年11月27日
    作    者   : w00166186
    修改内容   : DTS2010111800201 电话挂断后有一段电流声
  5.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcDisconnectMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MSG_DISCONNECT_MT_STRU       *pstMsg
)
{
/*
    5.4.4.2.1.1 Receipt of a DISCONNECT message
    The call control entity of the MS in any state except the "null" state, the
    "disconnect indication" state, and the "release request" state, shall, upon
    receipt of a DISCONNECT message with progress indicator #8 and, either not
    containing an Allowed Actions IE or containing an Allowed Actions IE
    indicating "CCBS activation is not possible":
    i) if an appropriate speech traffic channel is not connected,
    - stop all running call control timers;
    - send a RELEASE message;
    - start timer T308;
    - enter the "release request" state; and
    - not connect to the in-band tone/announcement.
    ii) if an appropriate speech traffic channel is connected, attach the user
    connection for speech if it is not yet attached and enter the "disconnect
    indication" state.
*/
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;

    enCallState = NAS_CC_GetCallState(entityId);

    if ((enCallState != NAS_CC_CALL_STATE_U0)
        && (enCallState != NAS_CC_CALL_STATE_U12)
        && (enCallState != NAS_CC_CALL_STATE_U19))
    {
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
        if (( VOS_TRUE == NAS_CC_IsTchAvailable(NAS_CC_ITC_SPEECH))
        && ( VOS_TRUE == pstMsg->stProgInd.IsExist)
        && (NAS_CC_PROGRESS_IN_BAND == pstMsg->stProgInd.Octet4.ProgDesc)
        )
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
        {
            /* 建立用户面连接 */
            NAS_CC_AttachUserConn(entityId, NAS_CC_ITC_SPEECH);
            NAS_CC_StopTimer(entityId, TI_NAS_CC_T310);
            /* 向TAF发送MNCC_DISC_IND原语 */
            NAS_CC_SendMnccMsg(entityId,
                               MNCC_DISC_IND,
                               pstMsg,
                               sizeof(NAS_CC_MSG_DISCONNECT_MT_STRU));

            NAS_CC_ProcProgressIndicator(entityId, &pstMsg->stProgInd);

            NAS_CC_INFO_LOG("NAS_CC_ProcDisconnectMsg: call state to U12");
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U12);
        }
        else
        {
            VOS_UINT8 ucTi = NAS_CC_GetEntityTi(entityId);

            NAS_CC_StopLocalAlertInd();

            NAS_CC_StopAllTimer(entityId);
            NAS_CC_SendRelease(ucTi, VOS_FALSE, 0, VOS_FALSE, 0);
            NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_FIRST);
            NAS_CC_INFO_LOG("NAS_CC_ProcDisconnectMsg: call state to U19");
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U19);
            NAS_CC_DetachUserConn(entityId);

            /* 向TAF发送MNCC_DISC_IND原语 */
            NAS_CC_SendMnccMsg(entityId,
                               MNCC_DISC_IND,
                               pstMsg,
                               sizeof(NAS_CC_MSG_DISCONNECT_MT_STRU));
        }

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcDisconnectMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcCcEstablishmentMsg
 功能描述  : 处理来自网络的cc establishment消息
 输入参数  : entityId - CC实体ID
             pstMsg   - 解码后的cc establishment消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/

LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcCcEstablishmentMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_CC_EST_STRU        *pstMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           aucSetupContainer[NAS_CC_MAX_SETUP_MSG_LEN + 2];
    MNCC_MSG_EST_STRU                   *pstCcEst;

    enCallState = NAS_CC_GetCallState(entityId);
    ucTi = NAS_CC_GetEntityTi(entityId);

    pstCcEst = VOS_NULL_PTR;
    if (NAS_CC_CALL_STATE_U0_3 == enCallState)
    {
        pstCcEst = (MNCC_MSG_EST_STRU *)PS_MEM_ALLOC(WUEPS_PID_CC,sizeof(MNCC_MSG_EST_STRU));
        if (VOS_NULL_PTR == pstCcEst)
        {
            NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_88);
            NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
            NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0);   /* 状态迁移到NULL */
            return NAS_PROT_ERR_INCOMPATIBLE_STATE;
        }

        NAS_CC_StopTimer(entityId, TI_NAS_CC_T332);
        PS_MEM_CPY(&pstCcEst->stHeader,&(pstMsg->stHeader),sizeof(pstCcEst->stHeader));
        pstCcEst->stSetupContainer.IsExist = pstMsg->stSetupContainer.IsExist;
        pstCcEst->stSetupContainer.LastOctOffset
                        = pstMsg->stSetupContainer.LastOctOffset;

        if (NAS_IE_IS_PRESENT(&pstMsg->stSetupContainer))
        {
            aucSetupContainer[0] = pstMsg->stHeader.bit4PD | pstMsg->stHeader.bit4TI;
            aucSetupContainer[1] = NAS_CC_MSG_EST_SETUP;
            PS_MEM_CPY(aucSetupContainer + 2,  pstMsg->stSetupContainer.SetupMessage,pstMsg->stSetupContainer.LastOctOffset);

            (VOS_VOID)NAS_CC_DecodeMsg(aucSetupContainer, 2+ pstMsg->stSetupContainer.LastOctOffset,&f_unCcDecodeBuf);
            PS_MEM_CPY(&pstCcEst->stSetupContainer.stSetup, &f_unCcDecodeBuf.stSetupMo, sizeof(f_unCcDecodeBuf.stSetupMo));
        }
        else
        {
            NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_88);
            NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
            NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0);   /* 状态迁移到NULL */

            PS_MEM_FREE(WUEPS_PID_CC,pstCcEst);

            return NAS_PROT_ERR_MANDATORY_IE_ERR;
        }

        /* 向TAF发送原语 CC_establish_ind*/
        NAS_CC_SendMnccMsg(entityId,
                           MNCC_CC_EST_IND,
                           pstCcEst,
                           sizeof(MNCC_MSG_EST_STRU));

        NAS_CC_NORM_LOG( "  CC State: CC_S_WAIT_FOR_NW_INFO ==> CC_S_EST_PRESENT  " );
        NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0_4);   /* 状态迁移到CC_S_EST_PRESENT */

        PS_MEM_FREE(WUEPS_PID_CC,pstCcEst);

        return NAS_PROT_ERR_NO_ERROR;

    }
    else
    {
        NAS_CC_WARN_LOG( " [Error]State error! " );   /* 出错报警  */
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }

}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcRecallMsg
 功能描述  : 处理来自网络的recall消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的recall消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcRecallMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_RECALL_STRU        *pstMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCallState = NAS_CC_GetCallState(entityId);

    VOS_UINT8 ucTi = NAS_CC_GetEntityTi(entityId);
    if (enCallState == NAS_CC_CALL_STATE_U0_5)
    {
        /* Recall消息Facility消息必须存在 */
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T335);
        if (VOS_FALSE == NAS_IE_IS_PRESENT(&pstMsg->stFacility))
        {
            NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_88);
            NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
            NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0);   /* 状态迁移到CC_S_EST_PRESENT */
            return NAS_PROT_ERR_MANDATORY_IE_ERR;
        }

        /* 向TAF发送原语 recall_ind*/
        NAS_CC_SendMnccMsg(entityId,
                           MNCC_RECALL_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_RECALL_STRU));
        NAS_CC_NORM_LOG( "  CC State:  RECALL PRESENT  " );
        NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0_6);   /* 状态迁移到CC_S_EST_PRESENT */

    }
    else
    {
        NAS_CC_WARN_LOG( " [Error]State error! " );   /* 出错报警  */
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
    return NAS_PROT_ERR_NO_ERROR;
}

LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcNotifyMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_NOTIFY_STRU        *pstMsg
)
{
    /* User notification procedure, 暂不支持 */
    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcHoldAckMsg
 功能描述  : 处理来自网络的HOLD ACK消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的HOLD ACK消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
  3.日    期   : 2013年07月29日
    作    者   : z00161729
    修改内容   : V9R1 STK升级项目如果在start dtmf req状态发起了hold，收到hold ack后需要清除dtmf状态
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcHoldAckMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_HOLD_ACK_STRU      *pstMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8     enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_HOLD_AUX_STATE_ENUM_U8 enHoldState = NAS_CC_GetHoldAuxState(entityId);

    if ((enCallState != NAS_CC_CALL_STATE_U10)
        && (enCallState != NAS_CC_CALL_STATE_U26))
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcHoldAckMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }

    if (NAS_CC_HOLD_AUX_S_HOLD_REQ == enHoldState)
    {
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
        NAS_CC_StopTimer(entityId, TI_NAS_CC_HOLD);

        /* 记录补充业务切换状态，调用统一补充业务切换状态处理函数 */
        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_SUCCESS, NAS_CC_CAUSE_NULL);

        NAS_CC_ProcSsSwitchMain();
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

        /* Modified by z00161729 for V9R1 STK升级, 2013-07-29, begin */
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T336);
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T337);
        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_IDLE);
        NAS_CC_FlushDTMFBuff(entityId);
        /* Modified by z00161729 for V9R1 STK升级, 2013-07-29, end */

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcHoldAckMsg: Incompatible hold state.", enHoldState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcHoldRejMsg
 功能描述  : 处理来自网络的HOLD REJECT消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的HOLD REJECT消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcHoldRejMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_HOLD_REJ_STRU      *pstMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8      enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_HOLD_AUX_STATE_ENUM_U8  enHoldState = NAS_CC_GetHoldAuxState(entityId);

    if ((enCallState != NAS_CC_CALL_STATE_U10)
        && (enCallState != NAS_CC_CALL_STATE_U26))
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcHoldRejMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }

    if (NAS_CC_HOLD_AUX_S_HOLD_REQ == enHoldState)
    {
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
        NAS_CC_StopTimer(entityId, TI_NAS_CC_HOLD);

        /* 记录补充业务切换状态，调用统一补充业务切换状态处理函数 */
        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_FAILED, pstMsg->stCause.Octet4.CauseValue);

        NAS_CC_ProcSsSwitchMain();
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcHoldRejMsg: Incompatible hold state.", enHoldState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcRetrieveAckMsg
 功能描述  : 处理来自网络的RETRIEVE ACK消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的RETRIEVE ACK消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年02月03日
    作    者   : Y00213812
    修改内容   : DTS2013020203946,如果还存在一个ACTIVE状态的呼叫，不处理本次
                 retrieve消息
  3.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcRetrieveAckMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_RETRIEVE_ACK_STRU  *pstMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8           enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState = NAS_CC_GetHoldAuxState(entityId);

    if ((enCallState != NAS_CC_CALL_STATE_U10)
        && (enCallState != NAS_CC_CALL_STATE_U26))
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcRetrieveAckMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }

    if (NAS_CC_HOLD_AUX_S_RETRIEVE_REQ == enHoldState)
    {
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
        NAS_CC_StopTimer(entityId, TI_NAS_CC_HOLD);

        /* 记录补充业务切换状态，调用统一补充业务切换状态处理函数 */
        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_SUCCESS, NAS_CC_CAUSE_NULL);

        NAS_CC_ProcSsSwitchMain();
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcRetrieveAckMsg: Incompatible hold state.", enHoldState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcRetrieveRejMsg
 功能描述  : 处理来自网络的RETRIEVE REJECT消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的RETRIEVE REJECT消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年02月03日
    作    者   : Y00213812
    修改内容   : DTS2013020203946,如果还存在一个HELD状态的呼叫，则恢复另外一个呼叫为ACTIVE
  3.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcRetrieveRejMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_RETRIEVE_REJ_STRU  *pstMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8      enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_HOLD_AUX_STATE_ENUM_U8  enHoldState = NAS_CC_GetHoldAuxState(entityId);

    if ((enCallState != NAS_CC_CALL_STATE_U10)
        && (enCallState != NAS_CC_CALL_STATE_U26))
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcRetrieveRejMsg: Incompatible state.", enCallState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }

    if (NAS_CC_HOLD_AUX_S_RETRIEVE_REQ == enHoldState)
    {
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
        NAS_CC_StopTimer(entityId, TI_NAS_CC_HOLD);

        /* 记录补充业务切换状态，调用统一补充业务切换状态处理函数 */
        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_FAILED, pstMsg->stCause.Octet4.CauseValue);

        NAS_CC_ProcSsSwitchMain();
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcRetrieveRejMsg: Incompatible hold state.", enHoldState);
        return NAS_PROT_ERR_INCOMPATIBLE_STATE;
    }
}


LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcModifyMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_MODIFY_STRU        *pstMsg
)
{
    /* in-call modification, 暂不支持 */
    return NAS_PROT_ERR_NO_ERROR;
}


LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcModifyCompleteMsg(
    NAS_CC_ENTITY_ID_T                    entityId,
    const NAS_CC_MSG_MODIFY_COMPLETE_STRU *pstMsg
)
{
    /* in-call modification, 暂不支持 */
    return NAS_PROT_ERR_NO_ERROR;
}


LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcModifyRejMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_MODIFY_REJ_STRU    *pstMsg

)
{
    /* in-call modification, 暂不支持 */
    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcProgressMsg
 功能描述  : 处理来自网络的PROGRESS消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的PROGRESS消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcProgressMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_PROGRESS_STRU      *pstMsg
)
{
/*
    3GPP 24.008 5.5.6
    On receipt of a PROGRESS message during the establishment or release of a
    call the mobile station shall stop all call control timers related to that call.

    If the PROGRESS has been received before the receipt of a CALL PROCEEDING
    message, the mobile station will not start timer T310 on receipt of a
    CALL PROCEEDING message.
*/
    NAS_CC_StopAllTimer(entityId);

    if (NAS_CC_GetCallState(entityId) == NAS_CC_CALL_STATE_U1)
    {
        /* 设置一个标志，表示在收到CALL PROCEEDING消息时将不启动T310定时器 */
        NAS_CC_ProcProgressIe(entityId, pstMsg->stProgInd.Octet4.ProgDesc);
    }

    /* 处理Progress Indicatore */
    NAS_CC_ProcProgressIndicator(entityId, &pstMsg->stProgInd);

    NAS_CC_SendMnccMsg(entityId,
                       MNCC_PROGRESS_IND,
                       pstMsg,
                       sizeof(NAS_CC_MSG_PROGRESS_STRU));

    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcFacilityMsg
 功能描述  : 处理来自网络的FACILITY消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的FACILITY消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcFacilityMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg
)
{
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    NAS_CC_ENTITY_ID_T                  ulHoldEntityID;
    NAS_CC_ENTITY_ID_T                  ulRetrieveEntityID;

    NAS_CC_ProcFacIE(entityId, &(pstMsg->stFacility));

    /* 如果entityId记录到了补充业务切换信息中，则缓存此消息，否则发出 */
    ulHoldEntityID      = NAS_CC_GetSsSwitchHoldEntityID();
    ulRetrieveEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();

    if ( (entityId == ulHoldEntityID)
      || (entityId == ulRetrieveEntityID) )
    {

        /* 缓存网络发来的Facility消息 */
        NAS_CC_SetSsSwitchOpFacility(VOS_TRUE, pstMsg);

        NAS_CC_ProcSsSwitchMain();
    }
    else
    {
        NAS_CC_SendMnccMsg(entityId,
                           MNCC_FACILITY_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_FACILITY_MT_STRU));
    }
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcStartDtmfAckMsg
 功能描述  : 处理来自网络的START DTMF ACK消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的START DTMF ACK消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcStartDtmfAckMsg(
    NAS_CC_ENTITY_ID_T                   entityId,
    const NAS_CC_MSG_START_DTMF_ACK_STRU *pstMsg
)
{
    NAS_CC_DTMF_STATE_ENUM  enDtmfState = NAS_CC_GetDtmfState(entityId);

    if (NAS_CC_DTMF_S_START_REQ == enDtmfState)
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T336);

        NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_CNF, VOS_NULL_PTR, 0);

        NAS_CC_INFO_LOG("NAS_CC_ProcStartDtmfAckMsg: ChangeDtmfState to IDLE");

        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_IDLE);

        NAS_CC_SendBufferedDtmfReq(entityId);

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcStartDtmfAck: Incompatible DTMF state.", enDtmfState);
        return NAS_PROT_ERR_NO_ERROR;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcStartDtmfRejMsg
 功能描述  : 处理来自网络的START DTMF REJ消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的START DTMF REJ消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年2月18日
    作    者   : z00161729
    修改内容   : DTS2013021803962:start dtmf rej后如果收到stop dtmf请求无需跟网络交互直接回复stop dtmf cnf

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcStartDtmfRejMsg(
    NAS_CC_ENTITY_ID_T                   entityId,
    const NAS_CC_MSG_START_DTMF_REJ_STRU *pstMsg
)
{
    NAS_CC_DTMF_STATE_ENUM      enDtmfState = NAS_CC_GetDtmfState(entityId);
    NAS_CC_CAUSE_VALUE_ENUM_U32 enCause;

    if (NAS_CC_DTMF_S_START_REQ == enDtmfState)
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T336);

        enCause = pstMsg->stCause.Octet4.CauseValue;
        NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &enCause, sizeof(enCause));

        NAS_CC_INFO_LOG("NAS_CC_ProcStartDtmfRejMsg: ChangeDtmfState to IDLE");

        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_START_REJ);

        NAS_CC_SendBufferedDtmfReq(entityId);

        return NAS_PROT_ERR_NO_ERROR;
    }
    else if (NAS_CC_DTMF_S_STOP_REQ == enDtmfState)
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcStartDtmfRejMsg: Incompatible DTMF state.", enDtmfState);
        NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcStartDtmfRejMsg: Incompatible DTMF state.", enDtmfState);
        return NAS_PROT_ERR_NO_ERROR;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcStopDtmfAckMsg
 功能描述  : 处理来自网络的STOP DTMF ACK消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的STOP DTMF ACK消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcStopDtmfAckMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_STOP_DTMF_ACK_STRU *pstMsg
)
{
    NAS_CC_DTMF_STATE_ENUM  enDtmfState = NAS_CC_GetDtmfState(entityId);

    if (NAS_CC_DTMF_S_STOP_REQ == enDtmfState)
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T337);

        NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);

        NAS_CC_INFO_LOG("NAS_CC_ProcStopDtmfAckMsg: ChangeDtmfState to IDLE");
        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_IDLE);

        NAS_CC_SendBufferedDtmfReq(entityId);

        return NAS_PROT_ERR_NO_ERROR;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_ProcStopDtmfAckMsg: Incompatible DTMF state.", enDtmfState);
        return NAS_PROT_ERR_NO_ERROR;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcStatusEnquiryMsg
 功能描述  : 处理来自网络的STATUS ENQUIRY消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的STATUS ENQUIRY消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcStatusEnquiryMsg(
    NAS_CC_ENTITY_ID_T                   entityId,
    const NAS_CC_MSG_STATUS_ENQUIRY_STRU *pstMsg
)
{
/*
    3GPP 5.5.3.1 :
    Upon receipt of a STATUS ENQUIRY message, the receiver shall respond with
    a STATUS message, reporting the current call state and cause value #30
    "response to STATUS ENQUIRY".
*/
    NAS_CC_SendStatus(NAS_CC_GetEntityTi(entityId), NAS_CC_CAUSE_30);

    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcStatusMsg
 功能描述  : 处理来自网络的STATUS消息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的STATUS消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月5日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcStatusMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_STATUS_STRU        *pstMsg
)
{
    VOS_UINT8 ucTi = NAS_CC_GetEntityTi(entityId);

    if ((VOS_TRUE == pstMsg->stCause.IsExist)
      &&(NAS_CC_CAUSE_101 == pstMsg->stCause.Octet4.CauseValue))
    {
        NAS_CC_StopAllTimer(entityId);
        NAS_CC_DetachUserConn(entityId);
        NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_101);
        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        NAS_CC_SendMnccMsg(entityId,
                           MNCC_REL_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_RELEASE_MT_STRU));

        NAS_CC_INFO_LOG("NAS_CC_ProcStopDtmfAckMsg: ChangeCallState to U0");

        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
        return NAS_PROT_ERR_NO_ERROR;
    }
    /* 暂不支持 */
    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcUserInfoMsg
 功能描述  : 处理来自网络的User Information信息
 输入参数  : entityId - CC实体ID
              pstMsg   - 解码后的STATUS消息
 输出参数  : 无
 返 回 值  : 处理中是否发生协议错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月4日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL NAS_PROTOCOL_ERR_ENUM_U8  NAS_CC_ProcUserInfoMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    const NAS_CC_MSG_USER_INFO_STRU     *pstMsg
)
{
    NAS_CC_UUS_INFO_IND_STRU            stUserInfo;

    /* 如果Disconnect中携带Uus需要上报给Call模块 */
    if ( VOS_TRUE == pstMsg->stUserUser.IsExist )
    {
        PS_MEM_SET(&stUserInfo,0x00,sizeof(stUserInfo));
        stUserInfo.enCcMsgtype = NAS_CC_MSG_USER_INFO;
        PS_MEM_CPY(&stUserInfo.stUserInfo.stUserUser,
                   &(pstMsg->stUserUser),
                   sizeof(stUserInfo.stUserInfo.stUserUser));

        NAS_CC_SendMnccMsg(entityId,
                           MNCC_UUSINFO_IND,
                           &stUserInfo,
                           sizeof(stUserInfo));
    }

    return NAS_PROT_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcProtocolError
 功能描述  : 处理协议相关的错误，参见3GPP 24.008第8章
 输入参数  : ucTi      - Transcation ID
              enMsgType - 消息类型
              enErrno   - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月13日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年01月15日
    作    者   : l65478
    修改内容   : 问题单号:AT2D14565，收到不期望的"comprehension required"的IE，
                 需要向网络发送status消息
  3.日    期   : 2010年01月28日
    作    者   : f62575
    修改内容   : 问题单号AT2D16557, GCF测试26.5.5.3.1.2；
                 CC接收到网络过来的STATUS消息缺失必选IE，应回复STATUS消息，
                 错误原因值96
  4.日    期   : 2008年8月21日
    作    者   : h44270
    修改内容   : 问题单号DTS2010081802507
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcProtocolError(
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_PROTOCOL_ERR_ENUM_U8            enErrno
)
{
    NAS_CC_NORM_LOG1("CC_ProcProtocolError: There is a protocol error.", enErrno);

    switch (enErrno)
    {
    case NAS_PROT_ERR_MSG_TOO_SHORT:
        /* Ignore, do nothing */
        break;

    case NAS_PROT_ERR_MSG_TYPE_UNKNOWN:
        /* Send STATUS to nw, cause value #97 */
        NAS_CC_SendStatus(ucTi, NAS_CC_CAUSE_97);
        break;

    case NAS_PROT_ERR_INCOMPATIBLE_STATE:
        /* Send STATUS to nw, cause value #98 */
        NAS_CC_SendStatus(ucTi, NAS_CC_CAUSE_98);
        break;

    case NAS_PROT_ERR_MANDATORY_IE_ERR:
        switch(enMsgType)
        {
        case NAS_CC_MSG_DISCONNECT:
            /* Send RELEASE to nw, cause value #96 */
            NAS_CC_SendRelease(ucTi, VOS_TRUE, NAS_CC_CAUSE_96, VOS_FALSE, 0);
            break;

        case NAS_CC_MSG_SETUP:
            NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_96);
            NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0);
            break;
        case NAS_CC_MSG_RELEASE:
            NAS_CC_StopAllTimer(NAS_CC_GetEntityByTi(ucTi));
            NAS_CC_DetachUserConn(NAS_CC_GetEntityByTi(ucTi));
            NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_96);
            NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
            NAS_CC_FillCauseIe(NAS_CC_CAUSE_127, &f_unCcDecodeBuf.stReleaseMT.stCause);
            NAS_CC_SendMnccMsg(NAS_CC_GetEntityByTi(ucTi),
                               MNCC_REL_IND,
                               &f_unCcDecodeBuf,
                               sizeof(NAS_CC_MSG_RELEASE_MT_STRU));
            NAS_CC_ChangeCallState(NAS_CC_GetEntityByTi(ucTi), NAS_CC_CALL_STATE_U0);
            break;
        case NAS_CC_MSG_STATUS:
            NAS_CC_SendStatus(ucTi, NAS_CC_CAUSE_96);
            break;

        case NAS_CC_MSG_RELEASE_COMPLETE:
            /* 3GPP 24.008 8.5.3 Call control
            If the message is a RELEASE COMPLETE message, it shall be treated
            as a normal RELEASE COMPLETE message.
            */
            NAS_CC_FillCauseIe(NAS_CC_CAUSE_127, &f_unCcDecodeBuf.stReleaseCompleteMT.stCause);
            (VOS_VOID)NAS_CC_ProcReleaseCompleteMsg(NAS_CC_GetEntityByTi(ucTi), (NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU *)&f_unCcDecodeBuf);
            break;
        case NAS_CC_MSG_HOLD_REJ:
            /* 3GPP 24.008 8.5.3 Call control
             If the message is a HOLD REJECT or RETRIEVE REJECT message,
            it shall be treated as a normal HOLD REJECT or RETRIEVE REJECT message.
            */
            NAS_CC_FillCauseIe(NAS_CC_CAUSE_127, &f_unCcDecodeBuf.stHoldRej.stCause);
            (VOS_VOID)NAS_CC_ProcHoldRejMsg(NAS_CC_GetEntityByTi(ucTi), (NAS_CC_MSG_HOLD_REJ_STRU *)&f_unCcDecodeBuf);
            break;
        case NAS_CC_MSG_RETRIEVE_REJ:
            NAS_CC_FillCauseIe(NAS_CC_CAUSE_127, &f_unCcDecodeBuf.stRetrieveRej.stCause);
            (VOS_VOID)NAS_CC_ProcRetrieveRejMsg(NAS_CC_GetEntityByTi(ucTi), (NAS_CC_MSG_RETRIEVE_REJ_STRU *)&f_unCcDecodeBuf);
            break;

        default:
            /* according to 24.008 8.5,
             if an RR connection exists, it shall return a status message */
            NAS_CC_SendStatus(ucTi, NAS_CC_CAUSE_96);
            NAS_CC_WARN_LOG("NAS_CC_ProcProtocolError: Mandatory IE error.");
            break;
        }
        break;

    case NAS_PROT_ERR_CONDITIONAL_IE_ERR:
        /* Send STATUS to nw, cause value #100 */
        NAS_CC_SendStatus(ucTi, NAS_CC_CAUSE_100);
        break;

    case NAS_PROT_ERR_INCOMPATIBLE_DESTINATION:
        NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_88);
        break;

    default:
        /* do noting */
        break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_CheckAirMsgValidity
 功能描述  : 对CC空口消息进行协议检查
 输入参数  : pucData     - CC消息的数据流
             ulDataLen   - 数据流的长度
 输出参数  : pulEntityId - 实体ID
             pucMsgType  - 解析出来的消息类型
             pucMsTi     - 解析出来的TI值
 返 回 值  : VOS_OK      - 消息合法
             VOS_ERR     - 消息非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月28日
    作    者   : z00161729
    修改内容   : 降NAS_CC_ProcAirMsg新生成函数
  1.日    期   : 2010年12月03日
    作    者   : w00166186
    修改内容   : DTS2010111900302 上海外场接听第三方通话失败，CALL ID填写错误
  3.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*****************************************************************************/
VOS_UINT32 NAS_CC_CheckAirMsgValidity(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulDataLen,
    NAS_CC_ENTITY_ID_T                 *pulEntityId,
    VOS_UINT8                          *pucMsgType,
    VOS_UINT8                          *pucMsTi
)
{
    VOS_UINT8                           ucNwTi;  /* Ti in network to MS message */

    if (ulDataLen < NAS_CC_MIN_AIR_MSG_LEN)
    {
        /* 3GPP 24.008 8.2 Message too short
           When a message is received that is too short to contain a complete
           message type information element, that message shall be ignored
        */
        NAS_CC_WARN_LOG("NAS_CC_CheckAirMsgValidity: Message too short.");
        return VOS_ERR;
    }

    ucNwTi      = ((pucData[NAS_CC_MSG_PD_TI_POS] >> 4) & 0xf);
    *pucMsTi    = ucNwTi ^ 0x8;
    *pucMsgType = pucData[NAS_CC_MSG_TYPE_POS] & 0x3f;

    /* Check TI according to 3GPP 24.008 8.3.1 */
    if (0x7 == (ucNwTi & 0x7))
    {
        NAS_CC_WARN_LOG("NAS_CC_CheckAirMsgValidity: TI coded as 111.");

        if (NAS_CC_MSG_SETUP == *pucMsgType)
        {
            NAS_CC_SendReleaseComplete(*pucMsTi, VOS_TRUE, 81);
            NAS_CC_SendMmccRelReq(*pucMsTi, MMCC_RELEASE_SPECIFIC);

#if (FEATURE_ON == FEATURE_PTM)
            /* setup消息按协议检查失败的异常记录 */
            NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_CODED_AS_111);
#endif

        }
        return VOS_ERR;
    }

    *pulEntityId = NAS_CC_GetEntityByTi(*pucMsTi);

    if (NAS_CC_INVALID_ENTITY_ID == *pulEntityId)
    {
       if (NAS_CC_MSG_SETUP == *pucMsgType)
       {
            if (1 == ((ucNwTi >> 3) & 0x1))
            {
                /* When an EMERGENCY SETUP, a START CC or, a SETUP message is
                  received specifying a TI which is not recognised as relating
                  to an active call or to a call in progress, and with a TI flag
                  incorrectly set to "1", this message shall be ignored.
                */
                NAS_CC_WARN_LOG("NAS_CC_CheckAirMsgValidity: TI flag in SETUP etc. set to 1.");
                NAS_CC_SendMmccRelReq(*pucMsTi, MMCC_RELEASE_SPECIFIC);

#if (FEATURE_ON == FEATURE_PTM)
                /* setup消息按协议检查失败的异常记录 */
                NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_INC_SET_TO_1);
#endif

                return VOS_ERR;
            }
            else
            {
                if (NAS_CC_CreateEntity(NAS_CC_CALL_TYPE_MT_NORMAL_CALL, (*pucMsTi + 1), *pucMsTi, pulEntityId) != VOS_OK)
                {
                    NAS_CC_ERR_LOG("NAS_CC_CheckAirMsgValidity: Fail to create entity.");

#if (FEATURE_ON == FEATURE_PTM)
                    /* setup消息按协议检查失败的异常记录 */
                    NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_CC_CREATE_ENTYTY_FAIL);
#endif

                    return VOS_ERR;
                }
            }
        }
       else if (NAS_CC_MSG_RELEASE_COMPLETE == *pucMsgType)
       {
           NAS_CC_WARN_LOG1("NAS_CC_CheckAirMsgValidity: unrecognized TI", ucNwTi);
           NAS_CC_SendMmccRelReq(*pucMsTi, MMCC_RELEASE_SPECIFIC);
           return VOS_ERR;
       }
       else
       {
           NAS_CC_WARN_LOG1("NAS_CC_CheckAirMsgValidity: unrecognized TI", ucNwTi);
           NAS_CC_SendReleaseComplete(*pucMsTi, VOS_TRUE, NAS_CC_CAUSE_81);
           NAS_CC_SendMmccRelReq(*pucMsTi, MMCC_RELEASE_SPECIFIC);
           return VOS_ERR;
       }
    }
    else /* TI is recognized */
    {
       if (NAS_CC_MSG_SETUP == *pucMsgType)
       {
            /* When a SETUP message is received by the mobile station specifying
              a TI which is recognized as relating to an active call or to a call
              in progress, this SETUP message shall be ignored.
            */
            NAS_CC_WARN_LOG1("NAS_CC_CheckAirMsgValidity: TI in a SETUP is in use.", ucNwTi);

#if (FEATURE_ON == FEATURE_PTM)
            /* setup消息按协议检查失败的异常记录 */
            NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_IS_USED);
#endif

            return VOS_ERR;
       }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcAirMsg
 功能描述  : 对CC空口消息进行协议检查，解码，然后根据消息类型分发到各种消息的
             处理函数去处理。
 输入参数  : pucData   - CC消息的数据流
             ulDataLen - 数据流的长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月13日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年6月28日
    作    者   : z00161729
    修改内容   : 降NAS_CC_ProcAirMsg新生成函数
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2014年12月22日
    作    者   : b00269685
    修改内容   : ultra flash新增缓存机制

*****************************************************************************/
VOS_VOID  NAS_CC_ProcAirMsg(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                           ucMsgType;
    NAS_PROTOCOL_ERR_ENUM_U8            enProtErr;
    NAS_CC_ENTITY_ID_T                  ulEntityId;
    VOS_UINT8                           ucMsTi;      /* Ti in MS to network message */
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    enProtErr = NAS_PROT_ERR_NO_ERROR;

    /* 判断消息的合法性,不合法直接返回不做处理 */
    if (VOS_OK != NAS_CC_CheckAirMsgValidity(pucData, ulDataLen, &ulEntityId,
                                             &ucMsgType, &ucMsTi))
    {
        return;
    }

    /* 消息解码 */
    PS_MEM_SET(&f_unCcDecodeBuf, 0, sizeof(f_unCcDecodeBuf));
    enProtErr = NAS_CC_DecodeMsg(pucData, (VOS_UINT8)ulDataLen, &f_unCcDecodeBuf);

    if (enProtErr != NAS_PROT_ERR_NO_ERROR)
    {
        NAS_CC_ProcProtocolError(ucMsTi, ucMsgType, enProtErr);
        NAS_CC_WARN_LOG1("NAS_CC_ProcAirMsg: decode msg err, msgtype:", ucMsgType);

        /* setup消息按协议检查失败的异常记录 */
#if (FEATURE_ON == FEATURE_PTM)
        if (NAS_CC_MSG_SETUP == ucMsgType)
        {
            NAS_CC_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_DECODE_FAIL);
        }
#endif

        return;
    }

    NAS_CC_INFO_LOG1("NAS_CC_ProcAirMsg: process normal msgtype:", ucMsgType);

    /* process the message */
    switch (ucMsgType)
    {
        case NAS_CC_MSG_SETUP:
           enProtErr = NAS_CC_ProcSetupMsg(ulEntityId, &f_unCcDecodeBuf.stSetupMT);

           if (NAS_PROT_ERR_NO_ERROR == enProtErr)
           {
               NAS_CC_ProcessSpecTypeBufferMsg(NAS_BuildEventType(WUEPS_PID_MM, MMCC_SYNC_IND));
           }
           else
           {
               NAS_CC_ClearSpecEventTypeCacheMsg(NAS_BuildEventType(WUEPS_PID_MM, MMCC_SYNC_IND));
           }

           break;

        case NAS_CC_MSG_RELEASE:
           enProtErr = NAS_CC_ProcReleaseMsg(ulEntityId, &f_unCcDecodeBuf.stReleaseMT);
           break;

        case NAS_CC_MSG_RELEASE_COMPLETE:
           enProtErr = NAS_CC_ProcReleaseCompleteMsg(ulEntityId, &f_unCcDecodeBuf.stReleaseCompleteMT);
           break;

        case NAS_CC_MSG_CALL_PROC:
           enProtErr = NAS_CC_ProcCallProceedingMsg(ulEntityId, &f_unCcDecodeBuf.stCallProc);
           break;

        case NAS_CC_MSG_ALERTING:
           enProtErr = NAS_CC_ProcAlertingMsg(ulEntityId, &f_unCcDecodeBuf.stAlertingMT);
           break;

        case NAS_CC_MSG_CONNECT:
           enProtErr = NAS_CC_ProcConnectMsg(ulEntityId, &f_unCcDecodeBuf.stConnectMT);
           break;

        case NAS_CC_MSG_CONNECT_ACK:
           enProtErr = NAS_CC_ProcConnectAckMsg(ulEntityId, &f_unCcDecodeBuf.stConnectAck);
           break;

        case NAS_CC_MSG_DISCONNECT:
           enProtErr = NAS_CC_ProcDisconnectMsg(ulEntityId, &f_unCcDecodeBuf.stDisconnectMT);
           break;

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        case NAS_CC_MSG_CC_EST:
            if (VOS_TRUE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                enProtErr = NAS_CC_ProcCcEstablishmentMsg(ulEntityId, &f_unCcDecodeBuf.stCCEst);
            }
            break;

        case NAS_CC_MSG_RECALL:
            if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                enProtErr = NAS_CC_ProcRecallMsg(ulEntityId, &f_unCcDecodeBuf.stRecall);
            }

            break;
       /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        case NAS_CC_MSG_NOTIFY:
           enProtErr = NAS_CC_ProcNotifyMsg(ulEntityId, &f_unCcDecodeBuf.stNotify);
           break;

        case NAS_CC_MSG_HOLD_ACK:
           enProtErr = NAS_CC_ProcHoldAckMsg(ulEntityId, &f_unCcDecodeBuf.stHoldAck);
           break;

        case NAS_CC_MSG_HOLD_REJ:
           enProtErr = NAS_CC_ProcHoldRejMsg(ulEntityId, &f_unCcDecodeBuf.stHoldRej);
           break;

        case NAS_CC_MSG_RETRIEVE_ACK:
           enProtErr = NAS_CC_ProcRetrieveAckMsg(ulEntityId, &f_unCcDecodeBuf.stRetrieveAck);
           break;

        case NAS_CC_MSG_RETRIEVE_REJ:
           enProtErr = NAS_CC_ProcRetrieveRejMsg(ulEntityId, &f_unCcDecodeBuf.stRetrieveRej);
           break;

        case NAS_CC_MSG_MODIFY:
           enProtErr = NAS_CC_ProcModifyMsg(ulEntityId, &f_unCcDecodeBuf.stModify);
           break;

        case NAS_CC_MSG_MODIFY_COMPLETE:
           enProtErr = NAS_CC_ProcModifyCompleteMsg(ulEntityId, &f_unCcDecodeBuf.stModifyComplete);
           break;

        case NAS_CC_MSG_MODIFY_REJ:
           enProtErr = NAS_CC_ProcModifyRejMsg(ulEntityId, &f_unCcDecodeBuf.stModifyRej);
           break;

        case NAS_CC_MSG_PROGRESS:
           enProtErr = NAS_CC_ProcProgressMsg(ulEntityId, &f_unCcDecodeBuf.stProgress);
           break;

        case NAS_CC_MSG_FACILITY:
           enProtErr = NAS_CC_ProcFacilityMsg(ulEntityId, &f_unCcDecodeBuf.stFacilityMT);
           break;

        case NAS_CC_MSG_START_DTMF_ACK:
           enProtErr = NAS_CC_ProcStartDtmfAckMsg(ulEntityId, &f_unCcDecodeBuf.stStartDTMFAck);
           break;

        case NAS_CC_MSG_START_DTMF_REJ:
           enProtErr = NAS_CC_ProcStartDtmfRejMsg(ulEntityId, &f_unCcDecodeBuf.stStartDTMFRej);
           break;

        case NAS_CC_MSG_STOP_DTMF_ACK:
           enProtErr = NAS_CC_ProcStopDtmfAckMsg(ulEntityId, &f_unCcDecodeBuf.stStopDTMFAck);
           break;

        case NAS_CC_MSG_STATUS_ENQUIRY:
           enProtErr = NAS_CC_ProcStatusEnquiryMsg(ulEntityId, &f_unCcDecodeBuf.stStatusEnquiry);
           break;

       case NAS_CC_MSG_USER_INFO:
           enProtErr = NAS_CC_ProcUserInfoMsg(ulEntityId, &f_unCcDecodeBuf.stUserInfo);
           break;

        case NAS_CC_MSG_STATUS:
           enProtErr = NAS_CC_ProcStatusMsg(ulEntityId, &f_unCcDecodeBuf.stStatus);
           break;

        default:
           NAS_CC_WARN_LOG1("NAS_CC_ProcAirMsg: msgtype default, msgtype:", ucMsgType);
           enProtErr = NAS_PROT_ERR_MSG_TYPE_UNKNOWN;
           break;

    }

    if (enProtErr != NAS_PROT_ERR_NO_ERROR)
    {
       NAS_CC_INFO_LOG1("NAS_CC_ProcAirMsg: proc protocol error:", enProtErr);
       NAS_CC_ProcProtocolError(ucMsTi, ucMsgType, enProtErr);
    }

}


/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
