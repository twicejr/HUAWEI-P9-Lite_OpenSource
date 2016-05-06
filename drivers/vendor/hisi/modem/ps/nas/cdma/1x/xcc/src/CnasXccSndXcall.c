/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndXcall.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年09月15日
  功能描述   : 1X CC发给XCAll的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXccSndXcall.h"
#include  "CnasMain.h"
#include  "CnasXccCtx.h"
#include  "xcc_xcall_pif.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_XCALL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallCallConnectInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_CALL_CONNECT_IND消息
 输入参数  : pstCallInfo -- 呼叫信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XCALL_CALL_CONNECT_IND_STRU    *pstCallConnectInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstCallConnectInd = (XCC_XCALL_CALL_CONNECT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_CALL_CONNECT_IND_STRU));

    if (VOS_NULL_PTR == pstCallConnectInd)
    {
        return;
    }

    /* 填充消息 */
    pstCallConnectInd->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstCallConnectInd->enMsgId          = ID_XCC_XCALL_CALL_CONNECT_IND;
    pstCallConnectInd->usOpId           = 0;
    pstCallConnectInd->ucCallId         = pstCallInfo->ucCallId;
    pstCallConnectInd->ucConRef         = pstCallInfo->ucConRef;
    pstCallConnectInd->enSo             = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCallConnectInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstCallConnectInd);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallHangUpCallCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF消息
 输入参数  : ucCallId -- 呼叫标识
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallHangUpCallCnf(
    VOS_UINT8                           ucCallId
)
{
    XCC_XCALL_HANGUP_CALL_CNF_STRU     *pstHangUpCallCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstHangUpCallCnf = (XCC_XCALL_HANGUP_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_HANGUP_CALL_CNF_STRU));
    if (VOS_NULL_PTR == pstHangUpCallCnf)
    {
        return;
    }

    /* 填充消息 */
    pstHangUpCallCnf->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstHangUpCallCnf->enMsgId          = ID_XCC_XCALL_HANGUP_CALL_CNF;
    pstHangUpCallCnf->usOpId           = 0;
    pstHangUpCallCnf->ucCallId         = ucCallId;

    NAS_MEM_SET_S(pstHangUpCallCnf->aucReserved, sizeof(pstHangUpCallCnf->aucReserved), 0, sizeof(pstHangUpCallCnf->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHangUpCallCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstHangUpCallCnf);

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallIncomingCallInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_INCOMING_CALL_IND消息
 输入参数  : pstCallInfo -- 呼叫信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XCALL_INCOMING_CALL_IND_STRU           *pstIncomingInd = VOS_NULL_PTR;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU    *pInfoRecoBuff;
    CNAS_XCC_INFO_RECS_CALLING_NUM_STRU        *pstCallingNum;
    CNAS_XCC_CALL_NVIM_CFG_STRU                *pstCallNvimCfg       = VOS_NULL_PTR;
    /* 分配消息 */
    pstIncomingInd = (XCC_XCALL_INCOMING_CALL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_INCOMING_CALL_IND_STRU));
    if (VOS_NULL_PTR == pstIncomingInd)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstIncomingInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstIncomingInd->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstIncomingInd->enMsgId             = ID_XCC_XCALL_INCOMING_CALL_IND;
    pstIncomingInd->usOpId              = 0;
    pstIncomingInd->ucCallId            = pstCallInfo->ucCallId;
    pstIncomingInd->ucConnectId         = pstCallInfo->ucConnectId;
    pstIncomingInd->ucIsAlertAnsByPass  = pstCallInfo->ucIsByPassAlertAns;
    pstIncomingInd->ucConRef            = pstCallInfo->ucConRef;
    pstIncomingInd->enSo                = pstCallInfo->enCurrentSo;

    pstCallNvimCfg                       = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);
    pstIncomingInd->enPrivacyModeSetting = pstCallNvimCfg->ucPrivacyMode;
    pstIncomingInd->enPrivacyMode        = pstCallInfo->enNegPrivacyMode;

    /* 获取calling party number */
    pInfoRecoBuff = &(pstCallInfo->stAWIorEAWIInfoRecoBuffer);
    if (VOS_TRUE == pInfoRecoBuff->ucIsBufferValid)
    {
        if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pInfoRecoBuff->enMsgType)
        {
            ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_NUMBER,
                                        pInfoRecoBuff->u.stAWIM.ucNumInfoRecs,
                                        pInfoRecoBuff->u.stAWIM.astInfoRecsData,
                                        &ucIndex);
        }
        else
        {
            ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_NUMBER,
                                        pInfoRecoBuff->u.stEAWIM.ucNumInfoRecs,
                                        pInfoRecoBuff->u.stEAWIM.astInfoRecsData,
                                        &ucIndex);
        }

        if (VOS_TRUE == ulResult)
        {
            if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pInfoRecoBuff->enMsgType)
            {
                pstCallingNum = &(pInfoRecoBuff->u.stAWIM.astInfoRecsData[ucIndex].stInfoRecs.u.stCallingNum);
            }
            else
            {
                pstCallingNum = &(pInfoRecoBuff->u.stEAWIM.astInfoRecsData[ucIndex].stInfoRecs.u.stCallingNum);
            }

            pstIncomingInd->stCallingPartyNum.enNumType  = (XCC_XCALL_NUMBER_TYPE_ENUM_UINT8)pstCallingNum->ucNumberType;
            pstIncomingInd->stCallingPartyNum.enNumPlan  = (XCC_XCALL_NUMBER_PLAN_ENUM_UINT8)pstCallingNum->ucNumberPlan;
            pstIncomingInd->stCallingPartyNum.ucPi       = pstCallingNum->ucPi;
            pstIncomingInd->stCallingPartyNum.ucSi       = pstCallingNum->ucSi;
            pstIncomingInd->stCallingPartyNum.ucDigitNum = pstCallingNum->ucDigitNum;
            NAS_MEM_CPY_S(pstIncomingInd->stCallingPartyNum.aucDigit,
                          sizeof(pstIncomingInd->stCallingPartyNum.aucDigit),
                          pstCallingNum->aucDigit,
                          pstCallingNum->ucDigitNum);
        }
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstIncomingInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstIncomingInd);

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallOrigCallCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_ORIG_CALL_CNF消息
 输入参数  : ucCallId -- 呼叫标识
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallOrigCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT8                           ucOrigCallId,
    VOS_INT16                           sRssi
)
{
    XCC_XCALL_ORIG_CALL_CNF_STRU       *pstOrigCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstOrigCnf = (XCC_XCALL_ORIG_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_ORIG_CALL_CNF_STRU));
    if (VOS_NULL_PTR == pstOrigCnf)
    {
        return;
    }

    NAS_MEM_SET_S(pstOrigCnf, sizeof(XCC_XCALL_ORIG_CALL_CNF_STRU), 0, sizeof(XCC_XCALL_ORIG_CALL_CNF_STRU));

    /* 填充消息 */
    pstOrigCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstOrigCnf->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstOrigCnf->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstOrigCnf->ulSenderPid         = UEPS_PID_XCC;
    pstOrigCnf->ulLength            = sizeof(XCC_XCALL_ORIG_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstOrigCnf->enMsgId             = ID_XCC_XCALL_ORIG_CALL_CNF;
    pstOrigCnf->usOpId              = 0;
    pstOrigCnf->enCause             = enCause;
    pstOrigCnf->enFailLayer         = enFailLayer;
    pstOrigCnf->ucCallId            = ucCallId;
    pstOrigCnf->ucOrigCallId        = ucOrigCallId;
    pstOrigCnf->sRssi               = sRssi;


    NAS_MEM_SET_S(pstOrigCnf->aucReserved, sizeof(pstOrigCnf->aucReserved), 0, sizeof(pstOrigCnf->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstOrigCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstOrigCnf);

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallCallDiscInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_CALL_DISC_IND消息
 输入参数  : pstCallInfo -- 呼叫信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年12月1日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallCallDiscInd(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XCALL_CALL_DISC_IND_STRU       *pstDiscInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstDiscInd = (XCC_XCALL_CALL_DISC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_CALL_DISC_IND_STRU));
    if (VOS_NULL_PTR == pstDiscInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstDiscInd, sizeof(XCC_XCALL_CALL_DISC_IND_STRU), 0, sizeof(XCC_XCALL_CALL_DISC_IND_STRU));

    /* 填充消息 */
    pstDiscInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDiscInd->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstDiscInd->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstDiscInd->ulSenderPid         = UEPS_PID_XCC;
    pstDiscInd->ulLength            = sizeof(XCC_XCALL_CALL_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDiscInd->enMsgId             = ID_XCC_XCALL_CALL_DISC_IND;
    pstDiscInd->usOpId              = 0;
    pstDiscInd->ucCallId            = ucCallId;
    pstDiscInd->ucConnectId         = ucConnectId;
    pstDiscInd->enCause             = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDiscInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstDiscInd);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallAnswerCallCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_ANSWER_CALL_CNF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallAnswerCallCnf(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef,
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enCurrentSo,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XCALL_ANSWER_CALL_CNF_STRU     *pstAnswerCallCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstAnswerCallCnf = (XCC_XCALL_ANSWER_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_ANSWER_CALL_CNF_STRU));
    if (VOS_NULL_PTR == pstAnswerCallCnf)
    {
        return;
    }

    /* 填充消息 */
    pstAnswerCallCnf->ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstAnswerCallCnf->enMsgId           = ID_XCC_XCALL_ANSWER_CALL_CNF;
    pstAnswerCallCnf->usOpId            = 0;
    pstAnswerCallCnf->ucCallId          = ucCallId;
    pstAnswerCallCnf->ucConRef          = ucConRef;
    pstAnswerCallCnf->enSo              = enCurrentSo;
    pstAnswerCallCnf->enCause           = enCause;
    pstAnswerCallCnf->enFailLayer       = enFailLayer;

    NAS_MEM_SET_S(pstAnswerCallCnf->aucReserved, sizeof(pstAnswerCallCnf->aucReserved), 0, sizeof(pstAnswerCallCnf->aucReserved));


    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstAnswerCallCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstAnswerCallCnf);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallCodecCloseInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_CODEC_CLOSE_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallCodecCloseInd( VOS_VOID )
{
    XCC_XCALL_CODEC_CLOSE_IND_STRU     *pstCodecCloseInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstCodecCloseInd = (XCC_XCALL_CODEC_CLOSE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_CODEC_CLOSE_IND_STRU));
    if (VOS_NULL_PTR == pstCodecCloseInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstCodecCloseInd, sizeof(XCC_XCALL_CODEC_CLOSE_IND_STRU), 0, sizeof(XCC_XCALL_CODEC_CLOSE_IND_STRU));
    /* 填充消息 */
    pstCodecCloseInd->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstCodecCloseInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCodecCloseInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCodecCloseInd->ulSenderPid     = UEPS_PID_XCC;
    pstCodecCloseInd->ulLength        = sizeof(XCC_XCALL_CODEC_CLOSE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCodecCloseInd->enMsgId         = ID_XCC_XCALL_CODEC_CLOSE_IND;
    pstCodecCloseInd->usOpId          = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCodecCloseInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstCodecCloseInd);

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallCodecOpenInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_CODEC_OPEN_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallCodecOpenInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XCALL_CODEC_OPEN_IND_STRU     *pstCodecOpenInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstCodecOpenInd = (XCC_XCALL_CODEC_OPEN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_CODEC_OPEN_IND_STRU));
    if (VOS_NULL_PTR == pstCodecOpenInd)
    {
        return;
    }

    /* 填充消息 */
    pstCodecOpenInd->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstCodecOpenInd->enMsgId            = ID_XCC_XCALL_CODEC_OPEN_IND;
    pstCodecOpenInd->usOpId             = 0;
    pstCodecOpenInd->enSo               = pstCallInfo->enCurrentSo;

    NAS_MEM_SET_S(pstCodecOpenInd->aucReserved, sizeof(pstCodecOpenInd->aucReserved), 0, sizeof(pstCodecOpenInd->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCodecOpenInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstCodecOpenInd);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallCodecChangedInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_CODEC_CHANGED_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallCodecChangedInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XCALL_CODEC_CHANGED_IND_STRU   *pstCodecChangedInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstCodecChangedInd = (XCC_XCALL_CODEC_CHANGED_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_CODEC_CHANGED_IND_STRU));
    if (VOS_NULL_PTR == pstCodecChangedInd)
    {
        return;
    }

    /* 填充消息 */
    pstCodecChangedInd->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstCodecChangedInd->enMsgId            = ID_XCC_XCALL_CODEC_CHANGED_IND;
    pstCodecChangedInd->usOpId             = 0;
    pstCodecChangedInd->enSo               = pstCallInfo->enCurrentSo;

    NAS_MEM_SET_S(pstCodecChangedInd->aucReserved, sizeof(pstCodecChangedInd->aucReserved), 0, sizeof(pstCodecChangedInd->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCodecChangedInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstCodecChangedInd);

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallSoCtrlMsgInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_SO_CTRL_MSG_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallSoCtrlMsgInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    VOS_UINT8                          *pucSoCtrlData,
    VOS_UINT8                           ucDataLen,
    VOS_UINT8                           ucActTime
)
{
    XCC_XCALL_SO_CTRL_MSG_IND_STRU      *pstSoCtrlMsgInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstSoCtrlMsgInd = (XCC_XCALL_SO_CTRL_MSG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_SO_CTRL_MSG_IND_STRU));
    if (VOS_NULL_PTR == pstSoCtrlMsgInd)
    {
        return;
    }

    /* 填充消息 */
    pstSoCtrlMsgInd->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstSoCtrlMsgInd->enMsgId            = ID_XCC_XCALL_SO_CTRL_MSG_IND;
    pstSoCtrlMsgInd->usOpId             = 0;
    pstSoCtrlMsgInd->enSo               = pstCallInfo->enCurrentSo;
    pstSoCtrlMsgInd->ucActTime          = ucActTime;


    /* 当前data只有一个字节，直接取bit位进行复制 */
    pstSoCtrlMsgInd->ucRateReduc        = (VOS_UINT8)(*pucSoCtrlData >> 5);
    pstSoCtrlMsgInd->ucReserved         = 0;
    pstSoCtrlMsgInd->ucMobileToMobile   = (VOS_UINT8)((*pucSoCtrlData >> 1) & 0x01);
    pstSoCtrlMsgInd->ucInitCodec        = (VOS_UINT8)(*pucSoCtrlData & 0x01);

    NAS_MEM_SET_S(pstSoCtrlMsgInd->aucReserved, sizeof(pstSoCtrlMsgInd->aucReserved), 0, sizeof(pstSoCtrlMsgInd->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSoCtrlMsgInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstSoCtrlMsgInd);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallSoCtrlOrderInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_SO_CTRL_ORDER_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallSoCtrlOrderInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    VOS_UINT8                           ucORDQ
)
{
    XCC_XCALL_SO_CTRL_ORDER_IND_STRU   *pstSoCtrlOrderInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstSoCtrlOrderInd = (XCC_XCALL_SO_CTRL_ORDER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_SO_CTRL_ORDER_IND_STRU));
    if (VOS_NULL_PTR == pstSoCtrlOrderInd)
    {
        return;
    }

    /* 填充消息 */
    pstSoCtrlOrderInd->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstSoCtrlOrderInd->enMsgId          = ID_XCC_XCALL_SO_CTRL_ORDER_IND;
    pstSoCtrlOrderInd->usOpId           = 0;
    pstSoCtrlOrderInd->enSo             = pstCallInfo->enCurrentSo;
    pstSoCtrlOrderInd->ucORDQ           = ucORDQ;

    NAS_MEM_SET_S(pstSoCtrlOrderInd->aucReserved, sizeof(pstSoCtrlOrderInd->aucReserved), 0, sizeof(pstSoCtrlOrderInd->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSoCtrlOrderInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstSoCtrlOrderInd);

}

#if 0

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallStartDtmfCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_START_DTMF_CNF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallStartDtmfCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause

)
{
    XCC_XCALL_START_DTMF_CNF_STRU      *pstDtmfCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstDtmfCnf = (XCC_XCALL_START_DTMF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_START_DTMF_CNF_STRU));

    if (VOS_NULL_PTR == pstDtmfCnf)
    {
        return;
    }

    /* 填充消息 */
    pstDtmfCnf->ulReceiverPid       = WUEPS_PID_TAF;
    pstDtmfCnf->enMsgId             = ID_XCC_XCALL_START_DTMF_CNF;
    pstDtmfCnf->usOpId              = 0;
    pstDtmfCnf->enFailLayer         = enFailLayer;
    pstDtmfCnf->enCause             = enCause;
    pstDtmfCnf->ucCallId            = ucCallId;


    PS_MEM_SET(pstDtmfCnf->aucReserved, 0, sizeof(pstDtmfCnf->aucReserved));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDtmfCnf);

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XCC, pstDtmfCnf);

}
#endif

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallSendFlashCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_SEND_FLASH_CNF消息
 输入参数  : VOS_UINT8                           ucCallId,
             TAF_XCC_CAUSE_ENUM_UINT32           enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallSendFlashCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XCALL_SEND_FLASH_CNF_STRU      *pstSndFlashCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstSndFlashCnf = (XCC_XCALL_SEND_FLASH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_SEND_FLASH_CNF_STRU));

    if (VOS_NULL_PTR == pstSndFlashCnf)
    {
        return;
    }

    /* 填写VOS消息头 */
    pstSndFlashCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSndFlashCnf->ulSenderPid     = UEPS_PID_XCC;
    pstSndFlashCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSndFlashCnf->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);

    /* 填写消息内容 */
    NAS_MEM_SET_S((VOS_UINT8 *)pstSndFlashCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_SEND_FLASH_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_SEND_FLASH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndFlashCnf->enMsgId         = ID_XCC_XCALL_SEND_FLASH_CNF;
    pstSndFlashCnf->usOpId          = 0;
    pstSndFlashCnf->ucCallId        = ucCallId;
    pstSndFlashCnf->enCause         = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSndFlashCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstSndFlashCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallSendBurstDTMFCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_BURST_DTMF_CNF消息
 输入参数  : VOS_UINT8                           ucCallId
             TAF_XCC_CAUSE_ENUM_UINT32           enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallSendBurstDTMFCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XCALL_BURST_DTMF_CNF_STRU      *pstSndBurstDTMFCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstSndBurstDTMFCnf = (XCC_XCALL_BURST_DTMF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_BURST_DTMF_CNF_STRU));

    if (VOS_NULL_PTR == pstSndBurstDTMFCnf)
    {
        return;
    }

    /* 填写VOS消息头 */
    pstSndBurstDTMFCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSndBurstDTMFCnf->ulSenderPid     = UEPS_PID_XCC;
    pstSndBurstDTMFCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSndBurstDTMFCnf->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);

    /* 填写消息内容 */
    NAS_MEM_SET_S((VOS_UINT8 *)pstSndBurstDTMFCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_BURST_DTMF_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_BURST_DTMF_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndBurstDTMFCnf->enMsgId         = ID_XCC_XCALL_SEND_BURST_DTMF_CNF;
    pstSndBurstDTMFCnf->usOpId          = 0;
    pstSndBurstDTMFCnf->ucCallId        = ucCallId;
    pstSndBurstDTMFCnf->enCause         = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSndBurstDTMFCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstSndBurstDTMFCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallInfoRecInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : VOS_UINT8                                               ucCallId,
             CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8                  enRxTcMsgType,
             VOS_UINT8                                              *pucInfoRecData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallInfoRecInd(
    VOS_UINT8                                               ucCallId,
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8                  enRxTcMsgType,
    VOS_UINT8                                              *pucInfoRecData
)
{
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstInfoRecInd = (XCC_XCALL_INFO_REC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_INFO_REC_IND_STRU));
    if (VOS_NULL_PTR == pstInfoRecInd)
    {
        return;
    }

    /* 填充消息头 */
    pstInfoRecInd->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstInfoRecInd->ulSenderPid         = UEPS_PID_XCC;
    pstInfoRecInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstInfoRecInd->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);

    /* 清空消息内容 */
    NAS_MEM_SET_S((VOS_UINT8 *)pstInfoRecInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_INFO_REC_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_INFO_REC_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息体 */
    pstInfoRecInd->enMsgId             = ID_XCC_XCALL_INFO_REC_IND;
    pstInfoRecInd->usOpId              = 0;
    pstInfoRecInd->ucCallId            = ucCallId;
    /* TODO: pstInfoRecInd->ucCallWaitingInd */

    switch (enRxTcMsgType)
    {
        /* 根据FWI消息中information records,填充pstInfoRecInd */
        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_FillInfoRecIndWithFWIM((CNAS_XCC_FWIM_STRU *)pucInfoRecData, pstInfoRecInd);
            break;

        /* 根据EFWI消息中information records,填充pstInfoRecInd */
        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_FillInfoRecIndWithEFWIM((CNAS_XCC_EFWIM_STRU *)pucInfoRecData, pstInfoRecInd);
            break;

        /* 根据AWI消息中information records,填充pstInfoRecInd */
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_FillInfoRecIndWithAWIM((CNAS_XCC_AWIM_STRU *)pucInfoRecData, pstInfoRecInd);
            break;

        /* 根据EAWI消息中information records,填充pstInfoRecInd */
        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_FillInfoRecIndWithEAWIM((CNAS_XCC_EAWIM_STRU *)pucInfoRecData, pstInfoRecInd);
            break;

        default:
            PS_FREE_MSG(UEPS_PID_XCC, pstInfoRecInd);
            return;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstInfoRecInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstInfoRecInd);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillInfoRecIndWithFWIM
 功能描述  : 使用FWIM填充ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : CNAS_XCC_FWIM_STRU                 *pstFWIM
 输出参数  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数
  2.日    期   : 2015年08月27日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear pc-lint warning

*****************************************************************************/
VOS_VOID CNAS_XCC_FillInfoRecIndWithFWIM(
    CNAS_XCC_FWIM_STRU                 *pstFWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    VOS_UINT8                           ucLoop;

    /* 消除 PCLINT 429告警 */
    pstInfoRecInd = pstInfoRecInd;

    for (ucLoop = 0; ucLoop < pstFWIM->ucNumInfoRecs; ucLoop++)
    {
        CNAS_XCC_FillInfoRecIndInfoRecs(&(pstFWIM->astInfoRecsData[ucLoop].stInfoRecs), pstInfoRecInd);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillInfoRecIndWithEFWIM
 功能描述  : 使用EFWIM填充ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : CNAS_XCC_EFWIM_STRU                *pstEFWIM
 输出参数  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数
  2.日    期   : 2015年08月27日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear pc-lint warning

*****************************************************************************/
VOS_VOID CNAS_XCC_FillInfoRecIndWithEFWIM(
    CNAS_XCC_EFWIM_STRU                *pstEFWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    VOS_UINT8                           ucLoop;

    /* 消除 PCLINT 429告警 */
    pstInfoRecInd = pstInfoRecInd;

    for (ucLoop = 0; ucLoop < pstEFWIM->ucNumInfoRecs; ucLoop++)
    {
        CNAS_XCC_FillInfoRecIndInfoRecs(&(pstEFWIM->astInfoRecsData[ucLoop].stInfoRecs), pstInfoRecInd);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillInfoRecIndWithAWIM
 功能描述  : 使用AWIM填充ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : CNAS_XCC_AWIM_STRU                 *pstAWIM
 输出参数  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  2.日    期   : 2015年08月27日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear pc-lint warning

*****************************************************************************/
VOS_VOID CNAS_XCC_FillInfoRecIndWithAWIM(
    CNAS_XCC_AWIM_STRU                 *pstAWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    VOS_UINT8                           ucLoop;

    /* 消除 PCLINT 429告警 */
    pstInfoRecInd = pstInfoRecInd;

    for (ucLoop = 0; ucLoop < pstAWIM->ucNumInfoRecs; ucLoop++)
    {
        CNAS_XCC_FillInfoRecIndInfoRecs(&(pstAWIM->astInfoRecsData[ucLoop].stInfoRecs), pstInfoRecInd);
    }

    /* If this message does not contain a Signal information record, the mobile station
        should use standard alert as defined in 3.7.5.5
        The Standard Alert is defined as SIGNAL_TYPE = '10' ALERT_PITCH = '00' and SIGNAL = '000001'.*/
    if (VOS_FALSE == pstInfoRecInd->bitOpSignalInfo)
    {
        pstInfoRecInd->bitOpSignalInfo           = VOS_TRUE;
        pstInfoRecInd->stSignalInfo.ucSignalType = CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING;
        pstInfoRecInd->stSignalInfo.ucAlertPitch = CNAS_XCC_ALERT_PITCH_MEDIUM_PITCH;
        pstInfoRecInd->stSignalInfo.ucSignal     = CNAS_XCC_IS_54B_ALERTING_LONG;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillInfoRecIndWithEAWIM
 功能描述  : 使用EAWIM填充ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : CNAS_XCC_EAWIM_STRU                *pstEAWIM
 输出参数  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  2.日    期   : 2015年08月27日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear pc-lint warning

*****************************************************************************/
VOS_VOID CNAS_XCC_FillInfoRecIndWithEAWIM(
    CNAS_XCC_EAWIM_STRU                *pstEAWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    VOS_UINT8                           ucLoop;

    /* 消除 PCLINT 429告警 */
    pstInfoRecInd = pstInfoRecInd;

    for (ucLoop = 0; ucLoop < pstEAWIM->ucNumInfoRecs; ucLoop++)
    {
        CNAS_XCC_FillInfoRecIndInfoRecs(&(pstEAWIM->astInfoRecsData[ucLoop].stInfoRecs), pstInfoRecInd);
    }

    /* If this message does not contain a Signal information record, the mobile station
        should use standard alert as defined in 3.7.5.5
        The Standard Alert is defined as SIGNAL_TYPE = '10' ALERT_PITCH = '00' and SIGNAL = '000001'.*/
    if (VOS_FALSE == pstInfoRecInd->bitOpSignalInfo)
    {
        pstInfoRecInd->bitOpSignalInfo           = VOS_TRUE;
        pstInfoRecInd->stSignalInfo.ucSignalType = CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING;
        pstInfoRecInd->stSignalInfo.ucAlertPitch = CNAS_XCC_ALERT_PITCH_MEDIUM_PITCH;
        pstInfoRecInd->stSignalInfo.ucSignal     = CNAS_XCC_IS_54B_ALERTING_LONG;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillInfoRecIndInfoRecs
 功能描述  : 填充XCC_XCALL_INFO_REC_IND_STRU中的information records
 输入参数  : CNAS_XCC_INFO_RECS_STRU            *pstInfoRes,
 输出参数  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_FillInfoRecIndInfoRecs(
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRes,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    VOS_UINT8                           ucLoop;

    switch (pstInfoRes->enInfoRecsType)
    {
        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_DISPLAY:
            pstInfoRecInd->bitOpDisplayInfo         = VOS_TRUE;
            pstInfoRecInd->stDisplayInfo.ucDigitNum = pstInfoRes->u.stDisp.ucDigitNum;
            NAS_MEM_CPY_S(pstInfoRecInd->stDisplayInfo.aucDigit,
                          sizeof(pstInfoRecInd->stDisplayInfo.aucDigit),
                          pstInfoRes->u.stDisp.aucDigit,
                          pstInfoRes->u.stDisp.ucDigitNum);
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLED_PARTY_NUMBER:
            pstInfoRecInd->bitOpCalledNumInfo         = VOS_TRUE;
            pstInfoRecInd->stCalledNumInfo.enNumType  = pstInfoRes->u.stCalledNum.ucNumberType;
            pstInfoRecInd->stCalledNumInfo.enNumPlan  = pstInfoRes->u.stCalledNum.ucNumberPlan;
            pstInfoRecInd->stCalledNumInfo.ucDigitNum = pstInfoRes->u.stCalledNum.ucDigitNum;
            NAS_MEM_CPY_S(pstInfoRecInd->stCalledNumInfo.aucDigit,
                          sizeof(pstInfoRecInd->stCalledNumInfo.aucDigit),
                          pstInfoRes->u.stCalledNum.aucDigit,
                          pstInfoRes->u.stCalledNum.ucDigitNum);
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CALLING_PARTY_NUMBER:
            pstInfoRecInd->bitOpCallingNumInfo         = VOS_TRUE;
            pstInfoRecInd->stCallingNumInfo.enNumType  = pstInfoRes->u.stCallingNum.ucNumberType;
            pstInfoRecInd->stCallingNumInfo.enNumPlan  = pstInfoRes->u.stCallingNum.ucNumberPlan;
            pstInfoRecInd->stCallingNumInfo.ucPi       = pstInfoRes->u.stCallingNum.ucPi;
            pstInfoRecInd->stCallingNumInfo.ucSi       = pstInfoRes->u.stCallingNum.ucSi;
            pstInfoRecInd->stCallingNumInfo.ucDigitNum = pstInfoRes->u.stCallingNum.ucDigitNum;
            NAS_MEM_CPY_S(pstInfoRecInd->stCallingNumInfo.aucDigit,
                          sizeof(pstInfoRecInd->stCallingNumInfo.aucDigit),
                          pstInfoRes->u.stCallingNum.aucDigit,
                          pstInfoRes->u.stCallingNum.ucDigitNum);
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_CONNECTED_NUMBER:
            pstInfoRecInd->bitOpConnNumInfo         = VOS_TRUE;
            pstInfoRecInd->stConnNumInfo.enNumType  = pstInfoRes->u.stConNum.ucNumberType;
            pstInfoRecInd->stConnNumInfo.enNumPlan  = pstInfoRes->u.stConNum.ucNumberPlan;
            pstInfoRecInd->stConnNumInfo.ucPi       = pstInfoRes->u.stConNum.ucPi;
            pstInfoRecInd->stConnNumInfo.ucSi       = pstInfoRes->u.stConNum.ucSi;
            pstInfoRecInd->stConnNumInfo.ucDigitNum = pstInfoRes->u.stConNum.ucDigitNum;
            NAS_MEM_CPY_S(pstInfoRecInd->stConnNumInfo.aucDigit,
                          sizeof(pstInfoRecInd->stConnNumInfo.aucDigit),
                          pstInfoRes->u.stConNum.aucDigit,
                          pstInfoRes->u.stConNum.ucDigitNum);
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL:
            pstInfoRecInd->bitOpSignalInfo           = VOS_TRUE;
            pstInfoRecInd->stSignalInfo.ucSignalType = pstInfoRes->u.stSignal.ucSignalType;
            pstInfoRecInd->stSignalInfo.ucAlertPitch = pstInfoRes->u.stSignal.ucAlertPitch;
            pstInfoRecInd->stSignalInfo.ucSignal     = pstInfoRes->u.stSignal.ucSignal;
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_REDIRECTING_NUMBER:
            pstInfoRecInd->bitOpRedirNumInfo               = VOS_TRUE;
            pstInfoRecInd->stRedirNumInfo.bitOpPi          = pstInfoRes->u.stRedirNum.ucPiPresent;
            pstInfoRecInd->stRedirNumInfo.bitOpSi          = pstInfoRes->u.stRedirNum.ucSiPresent;
            pstInfoRecInd->stRedirNumInfo.bitOpRedirReason = pstInfoRes->u.stRedirNum.ucRedirectionReasonPresent;
            pstInfoRecInd->stRedirNumInfo.enNumPlan        = pstInfoRes->u.stRedirNum.ucNumberPlan;
            pstInfoRecInd->stRedirNumInfo.enNumType        = pstInfoRes->u.stRedirNum.ucNumbertype;
            pstInfoRecInd->stRedirNumInfo.enRedirReason    = pstInfoRes->u.stRedirNum.ucRedirectionReason;
            pstInfoRecInd->stRedirNumInfo.ucPi             = pstInfoRes->u.stRedirNum.ucPi;
            pstInfoRecInd->stRedirNumInfo.ucSi             = pstInfoRes->u.stRedirNum.ucSi;
            pstInfoRecInd->stRedirNumInfo.ucDigitNum       = pstInfoRes->u.stRedirNum.ucDigitNum;
            NAS_MEM_CPY_S(pstInfoRecInd->stRedirNumInfo.aucDigit,
                          sizeof(pstInfoRecInd->stRedirNumInfo.aucDigit),
                          pstInfoRes->u.stRedirNum.aucDigit,
                          pstInfoRes->u.stRedirNum.ucDigitNum);
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_LINE_CONTROL:
            pstInfoRecInd->bitOpLineCtrlInfo = VOS_TRUE;
            pstInfoRecInd->stLineCtrlInfo.ucPolarityIncluded        = pstInfoRes->u.stLineCtr.ucPolarityIncluded;
            pstInfoRecInd->stLineCtrlInfo.ucToggleModePresent       = pstInfoRes->u.stLineCtr.ucToggleModePresent;
            pstInfoRecInd->stLineCtrlInfo.ucToggleMode              = pstInfoRes->u.stLineCtr.ucToggleMode;
            pstInfoRecInd->stLineCtrlInfo.ucReversePolarityPresent  = pstInfoRes->u.stLineCtr.ucReversePolarityPresent;
            pstInfoRecInd->stLineCtrlInfo.ucReversePolarity         = pstInfoRes->u.stLineCtr.ucReversePolarity;
            pstInfoRecInd->stLineCtrlInfo.ucPowerDenialTime         = pstInfoRes->u.stLineCtr.ucPowerDenialTime;
            break;

        case CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_EXTENDED_DISPLAY:
            pstInfoRecInd->bitOpExtDisplay = VOS_TRUE;
            pstInfoRecInd->stExtDisplayInfo.enDisplayType    = pstInfoRes->u.stExtDisp.ucDispalyType;
            pstInfoRecInd->stExtDisplayInfo.ucExtDispInd     = pstInfoRes->u.stExtDisp.ucExtDisplayInd;
            pstInfoRecInd->stExtDisplayInfo.ucNumExtDispData = pstInfoRes->u.stExtDisp.ucNumExtDispData;
            for (ucLoop = 0; ucLoop < pstInfoRes->u.stExtDisp.ucNumExtDispData; ucLoop++)
            {
                pstInfoRecInd->stExtDisplayInfo.astExtDispData[ucLoop].enDisplayTag
                             = pstInfoRes->u.stExtDisp.astExtDispData[ucLoop].ucDispalyTag;
                pstInfoRecInd->stExtDisplayInfo.astExtDispData[ucLoop].ucDispalyLen
                             = pstInfoRes->u.stExtDisp.astExtDispData[ucLoop].ucDispalyLen;
                pstInfoRecInd->stExtDisplayInfo.astExtDispData[ucLoop].ucDigitNum
                             = pstInfoRes->u.stExtDisp.astExtDispData[ucLoop].ucDigitNum;
                NAS_MEM_CPY_S(pstInfoRecInd->stExtDisplayInfo.astExtDispData[ucLoop].aucDigit,
                              sizeof(pstInfoRecInd->stExtDisplayInfo.astExtDispData[ucLoop].aucDigit),
                              pstInfoRes->u.stExtDisp.astExtDispData[ucLoop].aucDigit,
                              pstInfoRes->u.stExtDisp.astExtDispData[ucLoop].ucDigitNum);
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_FillInfoRecIndWithFNM
 功能描述  : 使用FNM填充ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : CNAS_XCC_FWIM_STRU                 *pstFWIM
 输出参数  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年08月27日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear pc-lint warning

*****************************************************************************/
VOS_VOID CNAS_XCC_FillInfoRecIndWithFNM(
    CNAS_XCC_FNM_STRU                  *pstFNM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    VOS_UINT8                           ucLoop;

    /* 消除 PCLINT 429告警 */
    pstInfoRecInd = pstInfoRecInd;

    for (ucLoop = 0; ucLoop < CNAS_MIN(pstFNM->ucNumInfoRecs,CNAS_XCC_MAX_FNM_INFO_RECO_NUM); ucLoop++)
    {
        CNAS_XCC_FillInfoRecIndInfoRecs(&(pstFNM->astInfoRecsData[ucLoop].stInfoRecs), pstInfoRecInd);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallCschInfoRecInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_INFO_REC_IND消息
 输入参数  : VOS_UINT8                                               ucCallId,
             CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enRxTcMsgType,
             VOS_UINT8                                              *pucInfoRecData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallCschInfoRecInd(
    VOS_UINT8                                               ucCallId,
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enRxCommMsgType,
    VOS_UINT8                                              *pucInfoRecData
)
{
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstInfoRecInd = (XCC_XCALL_INFO_REC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_INFO_REC_IND_STRU));
    if (VOS_NULL_PTR == pstInfoRecInd)
    {
        return;
    }

    /* 填充消息头 */
    pstInfoRecInd->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstInfoRecInd->ulSenderPid         = UEPS_PID_XCC;
    pstInfoRecInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstInfoRecInd->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);

    /* 清空消息内容 */
    NAS_MEM_SET_S((VOS_UINT8 *)pstInfoRecInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_INFO_REC_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_INFO_REC_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息体 */
    pstInfoRecInd->enMsgId             = ID_XCC_XCALL_INFO_REC_IND;
    pstInfoRecInd->usOpId              = 0;
    pstInfoRecInd->ucCallId            = ucCallId;

    switch (enRxCommMsgType)
    {
        case CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG:
            CNAS_XCC_FillInfoRecIndWithFNM((CNAS_XCC_FNM_STRU *)pucInfoRecData, pstInfoRecInd);
            break;

        default:
            PS_FREE_MSG(UEPS_PID_XCC, pstInfoRecInd);
            return;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstInfoRecInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstInfoRecInd);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallNdssResultInd
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_NDSS_RESULT_IND消息
 输入参数  : enNdssResult

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallNdssResultInd(
    XCC_XCALL_NDSS_RESULT_ENUM_UINT8    enNsddResult
)
{
    XCC_XCALL_NDSS_RESULT_IND_STRU     *pstNdssResultInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pstNdssResultInd = (XCC_XCALL_NDSS_RESULT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_NDSS_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstNdssResultInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstNdssResultInd, sizeof(XCC_XCALL_NDSS_RESULT_IND_STRU), 0, sizeof(XCC_XCALL_NDSS_RESULT_IND_STRU));

    /* 填充消息 */
    pstNdssResultInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNdssResultInd->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstNdssResultInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNdssResultInd->ulSenderPid      = UEPS_PID_XCC;
    pstNdssResultInd->ulLength         = sizeof(XCC_XCALL_NDSS_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNdssResultInd->enMsgId          = ID_XCC_XCALL_NDSS_RESULT_IND;
    pstNdssResultInd->enNsddResult     = enNsddResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstNdssResultInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstNdssResultInd);
}



/*****************************************************************************
Function Name   :   CNAS_XCC_SndXcallContDTMFInd
Description     :   Sends ID_XCC_XCALL_CONT_DTMF_IND

Input parameters:   VOS_UINT8                           ucCallId
                    VOS_UINT8                           ucDigit
                    VOS_UINT8                           ucSwitch

Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-07-24
        Author  :   K00902809
        Modify content :    Create

    2)  日    期   : 2015年08月20日
        作    者   : t00323010
        修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallContDTMFInd(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucDigit,
    VOS_UINT8                           ucSwitch
)
{
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstXccXcallContDtmfInd;
    pstXccXcallContDtmfInd = (XCC_XCALL_CONT_DTMF_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_CONT_DTMF_IND_STRU));

    if (VOS_NULL_PTR == pstXccXcallContDtmfInd)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstXccXcallContDtmfInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_CONT_DTMF_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(XCC_XCALL_CONT_DTMF_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstXccXcallContDtmfInd->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstXccXcallContDtmfInd->enMsgId         = ID_XCC_XCALL_CONT_DTMF_IND;

    pstXccXcallContDtmfInd->ucDigit         = ucDigit;
    pstXccXcallContDtmfInd->enSwitch        = ucSwitch;
    pstXccXcallContDtmfInd->ucCallId        = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstXccXcallContDtmfInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstXccXcallContDtmfInd);
}


/*****************************************************************************
Function Name   :   CNAS_XCC_SndXcallBurstDtmfInd
Description     :   The function is used to Send the Burst DTMF message to XCALL
Input parameters:   ulEventType - Event type of the Receive Snd Burst DTMF Message.
                    pstMsg      - Pointer to the message.

Output parameters:  None
Return Value    :   VOS_TRUE
Modify History:
    1)  Date    :   2015-07-24
        Author  :   a00295761
        Modify content :Create

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/

VOS_VOID CNAS_XCC_SndXcallBurstDtmfInd(
    VOS_UINT8                           ucCallId,
    CNAS_XCC_SEND_BURST_DTMF_STRU      *pstBurstDtmfVal
)
{
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDtmfInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pstBurstDtmfInd = (XCC_XCALL_BURST_DTMF_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_BURST_DTMF_IND_STRU));

    if (VOS_NULL_PTR == pstBurstDtmfInd)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_SndXcallBurstDtmfInd: Malloc memory fail");
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstBurstDtmfInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_BURST_DTMF_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_BURST_DTMF_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Fill the Message header */
    pstBurstDtmfInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBurstDtmfInd->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstBurstDtmfInd->ulLength         = sizeof(XCC_XCALL_BURST_DTMF_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBurstDtmfInd->enMsgId          = ID_XCC_XCALL_BURST_DTMF_IND;
    pstBurstDtmfInd->usOpId           = 0;

    /* Store the Send Burst DTMF parameters */
    pstBurstDtmfInd->ucCallId         = ucCallId;
    pstBurstDtmfInd->ucDigitNum       = pstBurstDtmfVal->ucDigitNum;

    NAS_MEM_CPY_S(pstBurstDtmfInd->aucDigit,
                  sizeof(pstBurstDtmfInd->aucDigit),
                  pstBurstDtmfVal->aucDigit,
                  sizeof(pstBurstDtmfInd->aucDigit));

    pstBurstDtmfInd->ulOnLength       = pstBurstDtmfVal->ulOnLength;
    pstBurstDtmfInd->ulOffLength      = pstBurstDtmfVal->ulOffLength;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBurstDtmfInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstBurstDtmfInd);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallSendContDTMFCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_SEND_CONT_DTMF_CNF消息
 输入参数  : VOS_UINT8                           ucCallId
             TAF_XCC_CAUSE_ENUM_UINT32           enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月25日
    作    者   : l00324781
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallSendContDTMFCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XCALL_SEND_CONT_DTMF_CNF_STRU  *pstSndContDTMFCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstSndContDTMFCnf = (XCC_XCALL_SEND_CONT_DTMF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_SEND_CONT_DTMF_CNF_STRU));

    if (VOS_NULL_PTR == pstSndContDTMFCnf)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_SndXcallSendContDTMFCnf: Malloc memory fail");
        return;
    }

    /* 填写VOS消息头 */
    pstSndContDTMFCnf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSndContDTMFCnf->ulSenderPid     = UEPS_PID_XCC;
    pstSndContDTMFCnf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSndContDTMFCnf->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstSndContDTMFCnf->ulLength        = sizeof(XCC_XCALL_SEND_CONT_DTMF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    NAS_MEM_SET_S((VOS_UINT8 *)pstSndContDTMFCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_SEND_CONT_DTMF_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_SEND_CONT_DTMF_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndContDTMFCnf->enMsgId         = ID_XCC_XCALL_SEND_CONT_DTMF_CNF;
    pstSndContDTMFCnf->usOpId          = 0;
    pstSndContDTMFCnf->ucCallId        = ucCallId;
    pstSndContDTMFCnf->enCause         = enCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSndContDTMFCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstSndContDTMFCnf);

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallEccServiceCnf
 功能描述  : 给XCALL模块发送ID_XCC_XCALL_SEND_CONT_DTMF_CNF消息
 输入参数  : TAF_XCC_CAUSE_ENUM_UINT32           enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallEccServiceCnf(
    XCC_XCALL_ECC_SERVICE_RESULT_ENUM_UINT8           enRslt
)
{
    XCC_XCALL_ECC_SERVICE_CNF_STRU      *pstEccSrvCnf = VOS_NULL_PTR;

    /* 分配消息 */
    pstEccSrvCnf = (XCC_XCALL_ECC_SERVICE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_XCALL_ECC_SERVICE_CNF_STRU));

    if (VOS_NULL_PTR == pstEccSrvCnf)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_SndXcallEccServiceCnf: Malloc memory fail");
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstEccSrvCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_ECC_SERVICE_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_ECC_SERVICE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写VOS消息头 */
    pstEccSrvCnf->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstEccSrvCnf->ulSenderPid           = UEPS_PID_XCC;
    pstEccSrvCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstEccSrvCnf->ulReceiverPid         = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstEccSrvCnf->ulLength              = sizeof(XCC_XCALL_ECC_SERVICE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEccSrvCnf->enMsgId               = ID_XCC_XCALL_ECC_SERVICE_CNF;
    pstEccSrvCnf->usOpId                = 0;
    pstEccSrvCnf->enRslt                = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEccSrvCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstEccSrvCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallTchAssignCmplInd
 功能描述  : 给XCALL模块发送 ID_XCC_XCALL_TCH_ASSIGN_CMPL_IND 消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallTchAssignCmplInd(VOS_VOID)
{
    XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU *pstTchAssignCmplInd = VOS_NULL_PTR;

    pstTchAssignCmplInd = (XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU));

    if (VOS_NULL_PTR == pstTchAssignCmplInd)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstTchAssignCmplInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstTchAssignCmplInd->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstTchAssignCmplInd->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstTchAssignCmplInd->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstTchAssignCmplInd->ulSenderPid        = UEPS_PID_XCC;
    pstTchAssignCmplInd->ulLength           = sizeof(XCC_XCALL_TCH_ASSIGN_CMPL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstTchAssignCmplInd->enMsgId            = ID_XCC_XCALL_TCH_ASSIGN_CMPL_IND;
    pstTchAssignCmplInd->usOpId             = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstTchAssignCmplInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstTchAssignCmplInd);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallPrivacyModeSetCnf
 功能描述  : 给XCALL模块发送privacy mode设置结果
 输入参数  : enResult      -- 设置结果
             ulModuleId    -- module标识；
             usClientId    -- client标识；
             usOpId        -- 操作标识；
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallPrivacyModeSetCnf(
    XCC_XCALL_RESULT_ENUM_UINT32        enResult,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usOpId
)
{
    XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU                    *pstPrivacyModeSetCnf = VOS_NULL_PTR;

    pstPrivacyModeSetCnf = (XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU));

    if (VOS_NULL_PTR == pstPrivacyModeSetCnf)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstPrivacyModeSetCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPrivacyModeSetCnf->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPrivacyModeSetCnf->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstPrivacyModeSetCnf->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPrivacyModeSetCnf->ulSenderPid        = UEPS_PID_XCC;
    pstPrivacyModeSetCnf->ulLength           = sizeof(XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstPrivacyModeSetCnf->enMsgId            = ID_XCC_XCALL_PRIVACY_MODE_SET_CNF;
    pstPrivacyModeSetCnf->ulModuleId         = ulModuleId;
    pstPrivacyModeSetCnf->usClientId         = usClientId;
    pstPrivacyModeSetCnf->usOpId             = usOpId;
    pstPrivacyModeSetCnf->enResult           = enResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPrivacyModeSetCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstPrivacyModeSetCnf);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallPrivacyModeQryCnf
 功能描述  : 给XCALL模块发送privacy mode查询结果
 输入参数  : enPrivacyMode -- privacy mode
             ulModuleId    -- module标识；
             usClientId    -- client标识；
             usOpId        -- 操作标识；
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallPrivacyModeQryCnf(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enPrivacyMode,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usOpId
)
{
    XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU                    *pstPrivacyModeQryCnf = VOS_NULL_PTR;

    pstPrivacyModeQryCnf = (XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstPrivacyModeQryCnf)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstPrivacyModeQryCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPrivacyModeQryCnf->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPrivacyModeQryCnf->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstPrivacyModeQryCnf->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPrivacyModeQryCnf->ulSenderPid        = UEPS_PID_XCC;
    pstPrivacyModeQryCnf->ulLength           = sizeof(XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstPrivacyModeQryCnf->enMsgId            = ID_XCC_XCALL_PRIVACY_MODE_QRY_CNF;
    pstPrivacyModeQryCnf->ulModuleId         = ulModuleId;
    pstPrivacyModeQryCnf->usClientId         = usClientId;
    pstPrivacyModeQryCnf->usOpId             = usOpId;
    pstPrivacyModeQryCnf->enPrivacyMode      = enPrivacyMode;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPrivacyModeQryCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstPrivacyModeQryCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXcallPrivacyModeInd
 功能描述  : 通知XCALL privacy mode发生变更
 输入参数  : enPrivacyMode -- privacy mode
             ucCallId      -- call Id

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcallPrivacyModeInd(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enPrivacyModeSetting,
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enCallPrivacyMode,
    VOS_UINT8                           ucCallId
)
{
    XCC_XCALL_PRIVACY_MODE_IND_STRU                        *pstPrivacyModeInd = VOS_NULL_PTR;

    pstPrivacyModeInd = (XCC_XCALL_PRIVACY_MODE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                            sizeof(XCC_XCALL_PRIVACY_MODE_IND_STRU));

    if (VOS_NULL_PTR == pstPrivacyModeInd)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstPrivacyModeInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XCALL_PRIVACY_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XCALL_PRIVACY_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPrivacyModeInd->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstPrivacyModeInd->ulReceiverPid        = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstPrivacyModeInd->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstPrivacyModeInd->ulSenderPid          = UEPS_PID_XCC;
    pstPrivacyModeInd->ulLength             = sizeof(XCC_XCALL_PRIVACY_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstPrivacyModeInd->enMsgId              = ID_XCC_XCALL_PRIVACY_MODE_IND;
    pstPrivacyModeInd->enPrivacyModeSetting = enPrivacyModeSetting;
    pstPrivacyModeInd->ucCallId             = ucCallId;
    pstPrivacyModeInd->enCallPrivacyMode    = enCallPrivacyMode;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPrivacyModeInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstPrivacyModeInd);

    return;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





