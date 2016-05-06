/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallSndXcc.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年09月03日
  功能描述   : TAF X CALL发送给XCC的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallSndXcc.h"
#include "TafStdlib.h"
#include "Taf_Aps.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccOrigCallReq
 功能描述  : 发送ID_XCALL_XCC_ORIG_CALL_REQ消息
 输入参数  : pstOrigPara    - 呼叫信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_SndXccOrigCallReq(
    VOS_UINT8                           ucCallId
)
{
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq = VOS_NULL_PTR;

    /* 分配消息 */
    pstOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstOrigReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstOrigReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstOrigReq->ulReceiverPid           = UEPS_PID_XCC;
    pstOrigReq->enMsgId                 = ID_XCALL_XCC_ORIG_CALL_REQ;

    /* 填写消息内容 */
    TAF_XCALL_BuildOrigCallPara(pstOrigReq, ucCallId);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstOrigReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccAnswerCallReq
 功能描述  : 发送ID_XCALL_XCC_ANSWER_CALL_REQ消息
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_SndXccAnswerCallReq(
    VOS_UINT8                           ucCallId
)
{
    XCALL_XCC_ANSWER_CALL_REQ_STRU     *pstAnswerCallReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstAnswerCallReq = (XCALL_XCC_ANSWER_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_ANSWER_CALL_REQ_STRU));
    if (VOS_NULL_PTR == pstAnswerCallReq)
    {
        return;
    }

    /* 填充消息 */
    pstAnswerCallReq->ulReceiverPid          = UEPS_PID_XCC;

    PS_MEM_SET((VOS_UINT8 *)pstAnswerCallReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_ANSWER_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAnswerCallReq->enMsgId                = ID_XCALL_XCC_ANSWER_CALL_REQ;
    pstAnswerCallReq->usOpId                 = 0;
    pstAnswerCallReq->ucCallId               = ucCallId;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstAnswerCallReq);

}


/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccHangUpCallReq
 功能描述  : 发送ID_XCALL_XCC_HANGUP_CALL_REQ消息
 输入参数  : VOS_UINT8                           ucCallId
             TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_SndXccHangUpCallReq(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangUpCallReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstHangUpCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_HANGUP_CALL_REQ_STRU));
    if (VOS_NULL_PTR == pstHangUpCallReq)
    {
        return;
    }

    /* 填充消息 */
    pstHangUpCallReq->ulReceiverPid          = UEPS_PID_XCC;

    PS_MEM_SET((VOS_UINT8 *)pstHangUpCallReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_HANGUP_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstHangUpCallReq->enMsgId                = ID_XCALL_XCC_HANGUP_CALL_REQ;
    pstHangUpCallReq->usOpId                 = 0;
    pstHangUpCallReq->ucCallId               = ucCallId;
    pstHangUpCallReq->enEndReason            = enEndReason;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstHangUpCallReq);

}


/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccIncomingCallRsp
 功能描述  : 发送ID_XCALL_XCC_INCOMING_CALL_RSP消息
 输入参数  : XCC_XCALL_RESULT_ENUM_UINT32        enRslt,
             VOS_UINT8                           ucCallId,
             VOS_UINT8                           ucConnectId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_SndXccIncomingCallRsp(
    XCC_XCALL_RESULT_ENUM_UINT32        enRslt,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
)
{
    XCALL_XCC_INCOMING_CALL_RSP_STRU   *pstIncomingCallRsp  = VOS_NULL_PTR;

    /* 分配消息 */
    pstIncomingCallRsp = (XCALL_XCC_INCOMING_CALL_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_INCOMING_CALL_RSP_STRU));
    if (VOS_NULL_PTR == pstIncomingCallRsp)
    {
        return;
    }

    /* 填充消息 */
    pstIncomingCallRsp->ulReceiverPid          = UEPS_PID_XCC;

    PS_MEM_SET((VOS_UINT8 *)pstIncomingCallRsp + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_INCOMING_CALL_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    pstIncomingCallRsp->enMsgId                = ID_XCALL_XCC_INCOMING_CALL_RSP;
    pstIncomingCallRsp->usOpId                 = 0;
    pstIncomingCallRsp->ucCallId               = ucCallId;
    pstIncomingCallRsp->ucConnectId            = ucConnectId;
    pstIncomingCallRsp->enRslt                 = enRslt;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstIncomingCallRsp);

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccFlashReq
 功能描述  : 发送ID_XCALL_XCC_SEND_FLASH_REQ消息
 输入参数  : XCC_XCALL_RESULT_ENUM_UINT32        enRslt,
             VOS_UINT8                           ucDigitNum,
             VOS_UINT8                          *pucDigits;
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 TAF_XCALL_SndXccFlashReq(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigits,
    VOS_UINT8                           ucIsEmcCall
)
{
    XCALL_XCC_SEND_FLASH_REQ_STRU   *pstFlashReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstFlashReq = (XCALL_XCC_SEND_FLASH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_SEND_FLASH_REQ_STRU));
    if (VOS_NULL_PTR == pstFlashReq)
    {
        return VOS_ERR;
    }

    /* 填写VOS消息头 */
    pstFlashReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstFlashReq->ulSenderPid     = WUEPS_PID_TAF;
    pstFlashReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstFlashReq->ulReceiverPid   = UEPS_PID_XCC;

    /* 填写消息内容 */
    PS_MEM_SET((VOS_UINT8 *)pstFlashReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_SEND_FLASH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstFlashReq->enMsgId        = ID_XCALL_XCC_SEND_FLASH_REQ;
    pstFlashReq->usOpId         = 0;
    pstFlashReq->ucCallId       = ucCallId;
    pstFlashReq->ucDigitNum     = ucDigitNum;
    pstFlashReq->ucIsEmcCall    = ucIsEmcCall;
    PS_MEM_CPY(pstFlashReq->aucDigit, pucDigits, ucDigitNum);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstFlashReq);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_BuildOrigCallPara
 功能描述  : 发送ID_XCALL_XCC_ORIG_CALL_REQ消息中的参数
 输入参数  : pstOrigPara    - 呼叫信息
             ucCallId       - call ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数
  2.日    期   : 2015年08月27日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear pc-lint warning

*****************************************************************************/
VOS_VOID TAF_XCALL_BuildOrigCallPara(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigPara,
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CONFIG_STRU              *pstCallConfig = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    /* 消除 PCLINT429 告警 */
    pstOrigPara = pstOrigPara;

    pstCallConfig = TAF_XCALL_GetConfigInfo();
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* 填写ORIG_CALL_REQ参数 */
    pstOrigPara->ucCallId               = ucCallId;

    if (MN_CALL_TYPE_EMERGENCY == pstCallEntity->enCallType)
    {
        pstOrigPara->ucIsEmergencyCall  = VOS_TRUE;
    }
    else
    {
        pstOrigPara->ucIsEmergencyCall  = VOS_FALSE;
    }

    pstOrigPara->ucIsL2ErrReOrig        = pstCallEntity->ucIsL2ErrReOrig;
    pstOrigPara->ucReOrigCount          = pstCallEntity->ucReOrigCount;
    pstOrigPara->enDigitMode            = pstCallConfig->enDigitMode;

    /* so info */
    pstOrigPara->stSoInfo.enSo          = pstCallEntity->enSo;

    /* calling num */
    if (0 != pstCallEntity->stCallNumber.ucNumLen)
    {
        pstOrigPara->bitOpCallingPartyNum = VOS_TRUE;
        TAF_XCALL_BuildCallingNum(&pstOrigPara->stCallingPartyNum,
                                  pstCallEntity,
                                  pstOrigPara->enDigitMode);
    }

    /* calling num subaddress */
    if (VOS_TRUE == pstCallEntity->stCallSubNumber.IsExist)
    {
        pstOrigPara->bitOpCallingPartySubAddr = VOS_TRUE;
        TAF_XCALL_BuildCallingSubAddr(&pstOrigPara->stCallingPartySubAddr, pstCallEntity);
    }

    /* called num */
    TAF_XCALL_BuildCalledNum(&pstOrigPara->stCalledPartyNum,
                             pstCallEntity,
                             pstOrigPara->enDigitMode);

    /* called num subaddress */
    if (VOS_TRUE == pstCallEntity->stCalledSubAddr.IsExist)
    {
        pstOrigPara->bitOpCalledPartySubAddr = VOS_TRUE;
        TAF_XCALL_BuildCalledSubAddr(&pstOrigPara->stCalledPartySubAddr, pstCallEntity);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_BuildCallingNum
 功能描述  : 填写发送给XCC消息中的主叫号码
 输入参数  : XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU  *pstCallingNum
             VOS_UINT8                               ucCallId
             XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_BuildCallingNum(
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU  *pstCallingNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
)
{
    VOS_CHAR                                acDigit[XCC_XCALL_MAX_NUM_DIGIT_LEN + 1];

    PS_MEM_SET(acDigit, 0, (XCC_XCALL_MAX_NUM_DIGIT_LEN + 1));

    pstCallingNum->enNumType    = (XCC_XCALL_NUMBER_TYPE_ENUM_UINT8)((pstCallEntity->stCallNumber.enNumType & TAF_XCALL_CALL_NUM_TYPE_VALID_BIT) >> 4);
    pstCallingNum->enNumPlan    = pstCallEntity->stCallNumber.enNumType & TAF_XCALL_CALL_PLAN_TYPE_VALID_BIT;
    pstCallingNum->ucPi         = pstCallEntity->ucPi;
    pstCallingNum->ucSi         = pstCallEntity->ucSi;

    /*判断pstCallEntity->stCallNumber.aucBcdNum所指向的字符串的最后一个字节的高位是否为1111，
    如果是，说明号码位数为奇数，否则为偶数*/
    if ((pstCallEntity->stCallNumber.aucBcdNum[pstCallEntity->stCallNumber.ucNumLen - 1] & 0xF0) == 0xF0)
    {
        pstCallingNum->ucDigitNum = (VOS_UINT8)((pstCallEntity->stCallNumber.ucNumLen * 2) - 1);
    }
    else
    {
        pstCallingNum->ucDigitNum = (VOS_UINT8)(pstCallEntity->stCallNumber.ucNumLen * 2);
    }

    /* 被叫号码个数 */
    pstCallingNum->ucDigitNum = TAF_XCALL_MIN(pstCallingNum->ucDigitNum, XCC_XCALL_MAX_NUM_DIGIT_LEN);

    if (XCC_XCALL_DIGIT_MODE_ASCII == enDigitMode)
    {
        /* BCD->ASCII */
        if (MN_ERR_NO_ERROR == TAF_STD_ConvertBcdNumberToAscii(pstCallEntity->stCallNumber.aucBcdNum,
                                                               pstCallEntity->stCallNumber.ucNumLen,
                                                               acDigit))
        {
            PS_MEM_CPY((VOS_CHAR *)pstCallingNum->aucDigit,
                        acDigit,
                        pstCallingNum->ucDigitNum);
        }
    }
    else
    {
        /* BCD->DTMF */
        TAF_STD_ConvertBcdNumberToDtmf(pstCallEntity->stCallNumber.aucBcdNum,
                                       pstCallEntity->stCallNumber.ucNumLen,
                                       pstCallingNum->aucDigit);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_BuildCallingSubAddr
 功能描述  : 填写发送给XCC消息中的主叫号码的子地址
 输入参数  : XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr
             VOS_UINT8                               ucCallId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_BuildCallingSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
)
{
    /*TO DO:*/

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_BuildCalledNum
 功能描述  : 填写发送给XCC消息中的被叫号码
 输入参数  : XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU   *pstCalledNum
             VOS_UINT8                               ucCallId
             XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_BuildCalledNum(
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU   *pstCalledNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
)
{
    VOS_CHAR                                acDigit[XCC_XCALL_MAX_NUM_DIGIT_LEN + 1];

    PS_MEM_SET(acDigit, 0, (XCC_XCALL_MAX_NUM_DIGIT_LEN + 1));

    pstCalledNum->enNumType = (XCC_XCALL_NUMBER_TYPE_ENUM_UINT8)((pstCallEntity->stCalledNumber.enNumType & TAF_XCALL_CALL_NUM_TYPE_VALID_BIT) >> 4);
    pstCalledNum->enNumPlan = pstCallEntity->stCalledNumber.enNumType & TAF_XCALL_CALL_PLAN_TYPE_VALID_BIT;

    /*判断pstCallEntity->stCallNumber.aucBcdNum所指向的字符串的最后一个字节的高位是否为1111，
    如果是，说明号码位数为奇数，否则为偶数*/
    if ((pstCallEntity->stCalledNumber.aucBcdNum[pstCallEntity->stCalledNumber.ucNumLen - 1] & 0xF0) == 0xF0)
    {
        pstCalledNum->ucDigitNum = (VOS_UINT8)((pstCallEntity->stCalledNumber.ucNumLen * 2) - 1);
    }
    else
    {
        pstCalledNum->ucDigitNum = (VOS_UINT8)(pstCallEntity->stCalledNumber.ucNumLen * 2);
    }

    /* 被叫号码个数 */
    pstCalledNum->ucDigitNum = TAF_XCALL_MIN(pstCalledNum->ucDigitNum, XCC_XCALL_MAX_NUM_DIGIT_LEN);

    if (XCC_XCALL_DIGIT_MODE_ASCII == enDigitMode)
    {
        /* BCD->ASCII */
        if (MN_ERR_NO_ERROR == TAF_STD_ConvertBcdNumberToAscii(pstCallEntity->stCalledNumber.aucBcdNum,
                                                               pstCallEntity->stCalledNumber.ucNumLen,
                                                               acDigit))
        {
            PS_MEM_CPY((VOS_CHAR *)pstCalledNum->aucDigit,
                       acDigit,
                       pstCalledNum->ucDigitNum);
        }
    }
    else
    {
        /* BCD->DTMF */
        TAF_STD_ConvertBcdNumberToDtmf(pstCallEntity->stCalledNumber.aucBcdNum,
                                       pstCallEntity->stCalledNumber.ucNumLen,
                                       pstCalledNum->aucDigit);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_BuildCalledSubAddr
 功能描述  : 填写发送给XCC消息中的被叫号码子地址
 输入参数  : XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr
             VOS_UINT8                               ucCallId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_BuildCalledSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
)
{
    /*TO DO:*/
    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccBurstDTMFReq
 功能描述  : 发送给XCC消息ID_XCALL_XCC_BURST_DTMF_REQ
 输入参数  : pstBurstDtmfInfo
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccBurstDTMFReq(
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstBurstDtmfInfo
)
{
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstBurstDTMFReq = VOS_NULL_PTR;

    /* 分配消息  */
    pstBurstDTMFReq = (XCALL_XCC_BURST_DTMF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_BURST_DTMF_REQ_STRU));
    if (VOS_NULL_PTR == pstBurstDTMFReq)
    {
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ALLOC_MSG_FAIL;
    }

    /* 填写VOS消息头 */
    pstBurstDTMFReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBurstDTMFReq->ulSenderPid     = WUEPS_PID_TAF;
    pstBurstDTMFReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBurstDTMFReq->ulReceiverPid   = UEPS_PID_XCC;

    /* 填写消息内容 */
    PS_MEM_SET((VOS_UINT8 *)pstBurstDTMFReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_BURST_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBurstDTMFReq->enMsgId     = ID_XCALL_XCC_SEND_BURST_DTMF_REQ;
    pstBurstDTMFReq->usOpId      = 0;
    pstBurstDTMFReq->ucCallId    = pstBurstDtmfInfo->ucCallId;
    pstBurstDTMFReq->ucDigitNum  = pstBurstDtmfInfo->ucDigitNum;
    pstBurstDTMFReq->ulOnLength  = pstBurstDtmfInfo->ulOnLength;
    pstBurstDTMFReq->ulOffLength = pstBurstDtmfInfo->ulOffLength;

    PS_MEM_CPY(pstBurstDTMFReq->aucDigit, pstBurstDtmfInfo->aucDigit, pstBurstDTMFReq->ucDigitNum);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstBurstDTMFReq);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SndXccContDTMFReq
 功能描述  : 发送给XCC消息ID_XCALL_XCC_CONT_DTMF_REQ
 输入参数  : pstContDtmfInfo
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : 新生成函数
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccContDTMFReq(
    TAF_CALL_CONT_DTMF_PARA_STRU      *pstContDtmfInfo
)
{
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstContDTMFReq = VOS_NULL_PTR;

    /* 分配消息  */
    pstContDTMFReq = (XCALL_XCC_SEND_CONT_DTMF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                      sizeof(XCALL_XCC_SEND_CONT_DTMF_REQ_STRU));
    if (VOS_NULL_PTR == pstContDTMFReq)
    {
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ALLOC_MSG_FAIL;
    }

    /* 填写VOS消息头 */
    pstContDTMFReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstContDTMFReq->ulSenderPid     = WUEPS_PID_TAF;
    pstContDTMFReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstContDTMFReq->ulReceiverPid   = UEPS_PID_XCC;
    pstContDTMFReq->ulLength        = sizeof(XCALL_XCC_SEND_CONT_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    PS_MEM_SET((VOS_UINT8 *)pstContDTMFReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_SEND_CONT_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstContDTMFReq->enMsgId     = ID_XCALL_XCC_SEND_CONT_DTMF_REQ;
    pstContDTMFReq->usOpId      = 0;
    pstContDTMFReq->ucCallId    = pstContDtmfInfo->ucCallId;
    pstContDTMFReq->enSwitch    = pstContDtmfInfo->enSwitch;
    pstContDTMFReq->ucDigit     = pstContDtmfInfo->ucDigit;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstContDTMFReq);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : TAF_XCALL_SendEccServiceReq
 功能描述  : 发送密话SO协商请求消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_SendEccServiceReq(VOS_VOID)
{
    XCALL_XCC_ECC_SERVICE_REQ_STRU     *pstEccSrvReq = VOS_NULL_PTR;

    /* 分配消息 */
    pstEccSrvReq = (XCALL_XCC_ECC_SERVICE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                  sizeof(XCALL_XCC_ECC_SERVICE_REQ_STRU));
    if (VOS_NULL_PTR == pstEccSrvReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstEccSrvReq,
               0,
               sizeof(XCALL_XCC_ECC_SERVICE_REQ_STRU));

    /* 填写VOS消息头 */
    pstEccSrvReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstEccSrvReq->ulSenderPid     = WUEPS_PID_TAF;
    pstEccSrvReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstEccSrvReq->ulReceiverPid   = UEPS_PID_XCC;
    pstEccSrvReq->ulLength        = sizeof(XCALL_XCC_ECC_SERVICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstEccSrvReq->enMsgId         = ID_XCALL_XCC_ECC_SERVICE_REQ;
    pstEccSrvReq->usOpId          = 0;

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstEccSrvReq);
}
#endif

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendPrivacyModeSetReq
 功能描述  : 发送privacy mode设置请求
 输入参数  : enPrivacyMode -- privacy mode
             ulModuleId    -- 用于记录设置privacy mode的module标识；
             usClientId    -- 用于记录设置privacy mode的client标识；
             ucOpId        -- 用于记录操作标识
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_SendPrivacyModeSetReq(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enPrivacyMode,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU                    *pstPmSetReq = VOS_NULL_PTR;

    /* 分配消息 */
    pstPmSetReq = (XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                      sizeof(XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstPmSetReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPmSetReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPmSetReq->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPmSetReq->ulSenderPid            = WUEPS_PID_TAF;
    pstPmSetReq->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPmSetReq->ulReceiverPid          = UEPS_PID_XCC;
    pstPmSetReq->ulLength               = sizeof(XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstPmSetReq->enMsgId                = ID_XCALL_XCC_PRIVACY_MODE_SET_REQ;
    pstPmSetReq->usOpId                 = (VOS_UINT16)ucOpId;
    pstPmSetReq->ulModuleId             = ulModuleId;
    pstPmSetReq->usClientId             = usClientId;
    pstPmSetReq->enPrivacyMode          = enPrivacyMode;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstPmSetReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendPrivacyModeQryReq
 功能描述  : 发送privacy mode设置请求
 输入参数  : ulModuleId    -- 用于记录设置privacy mode的module标识；
             usClientId    -- 用于记录设置privacy mode的client标识；
             ucOpId        -- 用于记录操作标识
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_SendPrivacyModeQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU                    *pstPmQryReq = VOS_NULL_PTR;

    /* 分配消息 */
    pstPmQryReq = (XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                      sizeof(XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstPmQryReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPmQryReq + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPmQryReq->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPmQryReq->ulSenderPid            = WUEPS_PID_TAF;
    pstPmQryReq->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPmQryReq->ulReceiverPid          = UEPS_PID_XCC;
    pstPmQryReq->ulLength               = sizeof(XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstPmQryReq->enMsgId                = ID_XCALL_XCC_PRIVACY_MODE_QRY_REQ;
    pstPmQryReq->usOpId                 = (VOS_UINT16)ucOpId;
    pstPmQryReq->ulModuleId             = ulModuleId;
    pstPmQryReq->usClientId             = usClientId;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstPmQryReq);

    return;
}
/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */






