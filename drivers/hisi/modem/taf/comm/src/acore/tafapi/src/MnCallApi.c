

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "MnCallApi.h"
#include  "product_config.h"
#include "MnErrorCode.h"
#include "AtParse.h"
#include "ATCmdProc.h"

#include "TafAppCall.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_API_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_CALL_SendAppRequest
 功能描述  : 将APP的异步请求发送到CCA所在任务处理
 输入参数  : enReq    - 请求的类型
              clientId - Client ID
              opId     - 本次操作的标识
              callId   - 呼叫的ID
              punParam - 请求中携带的参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2011年11月07日
    作    者   : f00179208
    修改内容   : AT Project, 修改AT虚拟的WUEPS_PID_VC为WUEPS_PID_AT
  3.日    期   : 2012年9月27日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
  4.日    期   : 2012年12月22日
    作    者   : l00227485
    修改内容   : DSDA phaseII

*****************************************************************************/
VOS_UINT32  MN_CALL_SendAppRequest(
    MN_CALL_APP_REQ_ENUM_UINT32         enReq,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_APP_REQ_PARM_UNION   *punParam
)
{
    MN_CALL_APP_REQ_MSG_STRU *pstMsg =
        (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("MN_CALL_SendAppRequest: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(MN_CALL_APP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* 填写原语首部 */
    pstMsg->enReq = enReq;
    pstMsg->clientId = clientId;
    pstMsg->opId = opId;
    pstMsg->callId = callId;

    if (TAF_NULL_PTR != punParam)
    {
        PS_MEM_CPY(&pstMsg->unParm, punParam, sizeof(pstMsg->unParm));
    }

    /* 发送VOS消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG1("MN_CALL_SendAppRequest: Send Message Fail. reqtype:", (VOS_INT32)enReq);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : MN_CALL_Orig
 功能描述  : 发起一个主叫
 输入参数  : clientId   - Client ID
             opId       - 本次操作的标识
             pstOrigParam - 主叫操作需要的参数
 输出参数  : pCallId    - 本次呼叫的ID, 用来唯一的标识这个呼叫
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目, 分配CALLId放到C核
  3.日    期   : 2012年9月25日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
*****************************************************************************/
VOS_UINT32  MN_CALL_Orig(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                       *pCallId,
    const MN_CALL_ORIG_PARAM_STRU      *pstOrigParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_ID_T                        callId;

    /* 在该处不在分配CallId，直接将callId赋值为0
       CallId的分配放到MN CALL模块处理该情况的函数中 */
    callId = 0;

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ORIG_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstOrigParam);

    *pCallId = callId;

    return ulResult;

}


/*****************************************************************************
 函 数 名  : MN_CALL_End
 功能描述  : 挂断一个呼叫
 输入参数  : clientId   - Client ID
             opId       - 本次操作的标识
             callId     - 需要挂断的呼叫的ID
             pstEndParam  - 挂断操作需要的参数, 该参数可选, NULL表示使用默认参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目CS域错误码上报，上报网侧定义的错误码

*****************************************************************************/
VOS_UINT32  MN_CALL_End(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParam
)
{
    MN_CALL_END_PARAM_STRU              stEndParam;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stEndParam, 0x00, sizeof(MN_CALL_END_PARAM_STRU));

    if ( TAF_NULL_PTR == pstEndParam)
    {
        /* 本地构造一个MN_CALL_END_REQ_PARAM_STRU结构, 填写原因值为255 */
        stEndParam.enEndCause = MN_CALL_INTERWORKING_UNSPECIFIED;
        pstEndParam = &stEndParam;
    }

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_END_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstEndParam);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_CALL_QryCdur
 功能描述  : 查询通话时长
 输入参数  : MN_CLIENT_ID_T                      clientId  Client ID
             MN_OPERATION_ID_T                   opId      本次操作的标识
             MN_CALL_ID_T                        callId    呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MN_CALL_QryCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_CDUR_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_CALL_Answer
 功能描述  : 接听一个来电
 输入参数  : clientId   - Client ID
             opId       - 本次操作的标识
             callId     - 需要接听的呼叫的ID
             pstAnsParam  - 接听操作需要的参数, 该参数可选, NULL表示使用默认参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_Answer(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
)
{
    MN_CALL_ANS_PARAM_STRU              stAnsParam;
    VOS_UINT32                          ulResult;

    if ( TAF_NULL_PTR == pstAnsParam)
    {
        /* 本地构造一个MN_CALL_ANS_REQ_PARAM_STRU结构 */
        pstAnsParam = &stAnsParam;
    }

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ANSWER_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstAnsParam);
    return ulResult;

}


/*****************************************************************************
 函 数 名  : TAF_CALL_SendDtmf
 功能描述  : APP给TAF发送DTMF
 输入参数  : enMsgType      - DTMF请求消息类型
             clientId       - Client ID
             opId           - 本次操作的标识
             pstDtmfParam   - 发送DTMF操作需要的参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_UINT32  TAF_CALL_SendDtmf(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CALL_DTMF_PARAM_STRU     *pstDtmfParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_APP_REQ_PARM_UNION          stAppPara;

    /* 初始化局部变量 */
    PS_MEM_SET(&stAppPara, 0, sizeof(stAppPara));
    PS_MEM_CPY(&stAppPara.stDtmf, pstDtmfParam, sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(enMsgType, clientId, opId,
                                      pstDtmfParam->CallId,
                                      &stAppPara);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_CALL_Sups
 功能描述  : 发起一次呼叫相关补充业务
 输入参数  : clientId   - Client ID
             opId       - 本次操作的标识
             pstCallSupsParam   - 发送呼叫相关补充业务需要的参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年9月25日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
  3.日    期   : 2013年09月30日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目，里层和外层的CallId填成一致
*****************************************************************************/
VOS_UINT32  MN_CALL_Sups(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulResult;

    /* 发送异步应用请求 */
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-30, begin */
    /* 里层和外层的CallId填成一致 */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_SUPS_CMD_REQ, clientId,
                                      opId, pstCallSupsParam->callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstCallSupsParam);
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-30, end */

    return ulResult;
}


/*****************************************************************************
 函 数 名  : MN_CALL_GetInfoList
 功能描述  : 获取当前所有状态不为IDLE的呼叫信息
 输入参数  : pNumOfCalls - 输出缓存最多能存储的呼叫信息个数
 输出参数  : pNumOfCalls - 实际输出的(状态不为IDLE的)呼叫信息个数
              pstCallInfos  - 输出的呼叫信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 修改接口获取当前呼叫信息
  3.日    期   : 2011年10月15日
    作    者   : f00179208
    修改内容   : AT移植项目，发送异步消息到C核获取CALL Info
  4.日    期   : 2012年9月25日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
*****************************************************************************/
VOS_UINT32  MN_CALL_GetCallInfos(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_INFO_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_CALL_SetAlsLineNo
 功能描述  : 根据设置的线路号更新NV和当前使用的线路号
 输入参数  : enAlsLine : 选择的线路号
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月22日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年10月24日
    作    者   : c00173809
    修改内容   : AT融合项目，通过核间通信方式而不直接调用MN_CALL_UpdateAlsLineInfo函数。

  3.日    期   : 2011年10月24日
    作    者   : o00132663
    修改内容   : AT融合项目， CC API调用MN_CALL_UpdateAlsLineInfo改为消息交
                 互
  4.日    期   : 2012年9月25日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
*****************************************************************************/
VOS_UINT32 MN_CALL_SetAlsLineNo(
    TAF_UINT8                           ucIndex,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_SET_ALS_PARAM_STRU          stSetAls;

    stSetAls.enAlsLine = enAlsLine;

    /*1.通过TAF_MSG_ALS_LINE_NO_SET消息带参数结构MN_CALL_ALS_PARAM_STRU
        通知TAF对ALS进行设置。*/
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_SET_ALS_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   0,
                                   (MN_CALL_APP_REQ_PARM_UNION*)&stSetAls);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : MN_CALL_CheckUus1ParmValid
 功能描述  : 检查设置UUS1输入参数是否合法
 输入参数  : enSetType      :激活或去激活UUS1
             pstUus1Info    :UUS1相关信息
 输出参数  : 无
 返 回 值  : VOS_UINT32     :参数检查成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_CheckUus1ParmValid(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    if ( VOS_NULL_PTR == pstUus1Info )
    {
        return MN_ERR_INVALIDPARM;
    }

    /*  校验参数的合法性,非法直接返回 */
    if ( ( enSetType >= MN_CALL_SET_UUS1_BUTT )
      || ( pstUus1Info->enMsgType > MN_CALL_UUS1_MSG_RELEASE_COMPLETE ))
    {
        return MN_ERR_INVALIDPARM;
    }


    /* 对于UUIE的检查仅检查第一项是否是UUIE,其他的长度和PD不进行检查,
       由应用保证,该项仅在激活UUS1时需要检查,去激活不关心该项  */
    if ( ( MN_CALL_SET_UUS1_ACT == enSetType)
      && ( MN_CALL_UUS_IEI != pstUus1Info->aucUuie[MN_CALL_IEI_POS]))
    {
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendFlashReq
 功能描述  : APP给TAF发送Flash请求
 输入参数  : clientId       - Client ID
             opId           - 本次操作的标识
             pstFlashPara   - 发送Flash操作需要的参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月8日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendFlashReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_FLASH_PARA_STRU           *pstFlashPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_APP_SEND_FLASH_REQ_STRU *pstMsg =
        (TAF_CALL_APP_SEND_FLASH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendFlashReq: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* 填写消息内容 */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_FLASH_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stFlashPara), pstFlashPara, sizeof(TAF_CALL_FLASH_PARA_STRU));

    /* 发送VOS消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendFlashReq: Send TAF_CALL_APP_SEND_FLASH_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendBurstDtmf
 功能描述  : APP给TAF发送Flash请求
 输入参数  : clientId              - Client ID
             opId                  - 本次操作的标识
             pstSndBurstDTMFPara   - 发送Send Burst Dtmf操作需要的参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendBurstDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstSndBurstDTMFPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU *pstMsg =
        (TAF_CALL_BURST_DTMF_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendBurstDtmf: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* 填写消息内容 */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_BURST_DTMF_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stBurstDTMFPara), pstSndBurstDTMFPara, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));

    /* 发送VOS消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendBurstDtmf: Send TAF_CALL_APP_SEND_BURST_DTMF_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendCustomDialReq
 功能描述  : APP给TAF发送Flash请求
 输入参数  : clientId       - Client ID
             opId           - 本次操作的标识
             pstFlashPara   - 发送Flash操作需要的参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : w00242748
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCustomDialReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CUSTOM_DIAL_PARA_STRU     *pstCustomDialPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *pstMsg =
        (TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendCustomDialReq: Failed to alloc VOS message.");
        return VOS_FALSE;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* 填写消息内容 */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stCustomDialPara), pstCustomDialPara, sizeof(pstMsg->stCustomDialPara));

    /* 发送VOS消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_AT, pstMsg);

    return VOS_TRUE;
#else
    return VOS_FALSE;
#endif
}



VOS_UINT32  TAF_XCALL_SendContinuousDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CONT_DTMF_PARA_STRU       *pstSndContDTMFPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU *pstMsg = VOS_NULL_PTR;
    pstMsg = (TAF_CALL_CONT_DTMF_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendContinuousDtmf: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* fill in VOS_MSG_HEAD */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* fill in message content */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CONT_DTMF_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stContDTMFPara), pstSndContDTMFPara, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

    /* Send VOS message */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendContinuousDtmf: Send TAF_CALL_APP_SEND_CONT_DTMF_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendCclpr
 功能描述  : APP给TAF发送Clpr请求
 输入参数  : clientId              - Client ID
             opId                  - 本次操作的标识
             ucCallId               - 呼叫id
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月20日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCclpr(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT8                           ucCallId
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_SND_CCLPR_REQ_MSG_STRU *pstMsg =
        (TAF_CALL_SND_CCLPR_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendCclpr: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* 填写消息内容 */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CCLPR_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    pstMsg->ucCallId   = ucCallId;

    /* 发送VOS消息TAF_CALL_APP_SEND_CCLPR_REQ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_AT, pstMsg);

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT))
/*****************************************************************************
 函 数 名  : TAF_XCALL_SndEncryptCall
 功能描述  : xcall收到AT的密话通知请求后发送消息函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enEccVoiceType, 密话呼叫模式
             MN_CALL_CALLED_NUM_STRU                                *pstDialNumber   密话呼叫号码
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendEncryptCall(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulEccVoiceType,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstDialNumber
)
{

    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstEncryptVoiceReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid      = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEncryptVoiceReq = (TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU));
    if (VOS_NULL_PTR == pstEncryptVoiceReq)
    {
        AT_ERR_LOG("TAF_XCALL_SndEncryptCall: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstEncryptVoiceReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstEncryptVoiceReq->ulSenderCpuId                       = VOS_LOCAL_CPUID;
    pstEncryptVoiceReq->ulSenderPid                         = ulSenderPid;
    pstEncryptVoiceReq->ulReceiverCpuId                     = VOS_LOCAL_CPUID;
    pstEncryptVoiceReq->ulReceiverPid                       = ulReceiverPid;
    pstEncryptVoiceReq->ulLength                            = sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstEncryptVoiceReq->enMsgName                           = ID_TAF_CALL_APP_ENCRYPT_VOICE_REQ;
    pstEncryptVoiceReq->stCtrl.usClientId                   = usClientId;
    pstEncryptVoiceReq->stCtrl.ucOpId                       = opId;
    pstEncryptVoiceReq->stCtrl.ulModuleId                   = ulModuleId;
    pstEncryptVoiceReq->enEccVoiceType                      = ulEccVoiceType;
    PS_MEM_CPY(&pstEncryptVoiceReq->stDialNumber, pstDialNumber, sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    /* 发送VOS消息ID_TAF_CALL_APP_ENCRYPT_VOICE_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEncryptVoiceReq);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SndEccCtrl
 功能描述  : 密话远程控制命令响应
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               ulRemoteCtrlEvtType,远程控制命令类型
             TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT32             ulResult            远程控制命令响应结果
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendEccCtrl(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulRemoteCtrlEvtType,
    VOS_UINT32                                              ulResult

)
{
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU               *pstEccRemoteCtrlAnsReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid            = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEccRemoteCtrlAnsReq = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU));
    if (VOS_NULL_PTR == pstEccRemoteCtrlAnsReq)
    {
        AT_ERR_LOG("TAF_XCALL_SndEccCtrl: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstEccRemoteCtrlAnsReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstEccRemoteCtrlAnsReq->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstEccRemoteCtrlAnsReq->ulSenderPid                     = ulSenderPid;
    pstEccRemoteCtrlAnsReq->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstEccRemoteCtrlAnsReq->ulReceiverPid                   = ulReceiverPid;
    pstEccRemoteCtrlAnsReq->ulLength                        = sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstEccRemoteCtrlAnsReq->enMsgName                       = ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ;
    pstEccRemoteCtrlAnsReq->stCtrl.usClientId               = usClientId;
    pstEccRemoteCtrlAnsReq->stCtrl.ucOpId                   = opId;
    pstEccRemoteCtrlAnsReq->stCtrl.ulModuleId               = ulModuleId;
    pstEccRemoteCtrlAnsReq->enRemoteCtrlEvtType             = ulRemoteCtrlEvtType;
    pstEccRemoteCtrlAnsReq->enResult                        = ulResult;

    /* 发送VOS消息ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEccRemoteCtrlAnsReq);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SetEccCap
 功能描述  : 设置modem密话能力，消息发送接口
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    ulEccSrvCap,   密话能力(仅能消除或者保持当前密话能力)
             TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 ulEccSrvStatus 密话状态(关闭，打开)
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SetEccCap(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulEccSrvCap,
    VOS_UINT32                                              ulEccSrvStatus
)
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU                  *pstEccSrvCapReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEccSrvCapReq = (TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU));
    if (VOS_NULL_PTR == pstEccSrvCapReq)
    {
        AT_ERR_LOG("TAF_XCALL_SetEccCap: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstEccSrvCapReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstEccSrvCapReq->ulSenderCpuId                          = VOS_LOCAL_CPUID;
    pstEccSrvCapReq->ulSenderPid                            = ulSenderPid;
    pstEccSrvCapReq->ulReceiverCpuId                        = VOS_LOCAL_CPUID;
    pstEccSrvCapReq->ulReceiverPid                          = ulReceiverPid;
    pstEccSrvCapReq->ulLength                               = sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstEccSrvCapReq->enMsgName                              = ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ;
    pstEccSrvCapReq->stCtrl.usClientId                      = usClientId;
    pstEccSrvCapReq->stCtrl.ucOpId                          = opId;
    pstEccSrvCapReq->stCtrl.ulModuleId                      = ulModuleId;
    pstEccSrvCapReq->enEccSrvCap                            = ulEccSrvCap;
    pstEccSrvCapReq->enEccSrvStatus                         = ulEccSrvStatus;

    /* 发送VOS消息ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEccSrvCapReq);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_QryEncryptCallCap
 功能描述  : 查询当前modem的密话能力 消息发送函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryEncryptCallCap(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU                  *pstQryEccCapReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstQryEccCapReq = (TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstQryEccCapReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryEncryptCallCap: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstQryEccCapReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstQryEccCapReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstQryEccCapReq->ulSenderPid                          = ulSenderPid;
    pstQryEccCapReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstQryEccCapReq->ulReceiverPid                        = ulReceiverPid;
    pstQryEccCapReq->ulLength                             = sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;


    /* 填写消息内容 */
    pstQryEccCapReq->enMsgName                            = ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ;
    pstQryEccCapReq->stCtrl.usClientId                    = usClientId;
    pstQryEccCapReq->stCtrl.ucOpId                        = opId;
    pstQryEccCapReq->stCtrl.ulModuleId                    = ulModuleId;

    /* 发送VOS消息ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstQryEccCapReq);

    return VOS_OK;
}


#if  (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)

/*****************************************************************************
 函 数 名  : TAF_XCALL_SetEccKmc
 功能描述  : 设置KMC公钥 消息发送函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_APP_EC_KMC_DATA_STRU                          *pstEccKmcData 待设置的公钥数据
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SetEncryptCallKmc(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    MN_CALL_APP_EC_KMC_DATA_STRU                           *pstEccKmcData
)
{

    TAF_CALL_APP_SET_EC_KMC_REQ_STRU                       *pstEccKmcSetReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEccKmcSetReq = (TAF_CALL_APP_SET_EC_KMC_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_SET_EC_KMC_REQ_STRU));
    if (VOS_NULL_PTR == pstEccKmcSetReq)
    {
        AT_ERR_LOG("TAF_XCALL_SetEccKmc: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstEccKmcSetReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SET_EC_KMC_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstEccKmcSetReq->ulSenderCpuId                          = VOS_LOCAL_CPUID;
    pstEccKmcSetReq->ulSenderPid                            = ulSenderPid;
    pstEccKmcSetReq->ulReceiverCpuId                        = VOS_LOCAL_CPUID;
    pstEccKmcSetReq->ulReceiverPid                          = ulReceiverPid;
    pstEccKmcSetReq->ulLength                               = sizeof(TAF_CALL_APP_SET_EC_KMC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstEccKmcSetReq->enMsgName                              = ID_TAF_CALL_APP_SET_EC_KMC_REQ;
    pstEccKmcSetReq->stCtrl.usClientId                      = usClientId;
    pstEccKmcSetReq->stCtrl.ucOpId                          = opId;
    pstEccKmcSetReq->stCtrl.ulModuleId                      = ulModuleId;
    PS_MEM_CPY(&pstEccKmcSetReq->stKmcData, pstEccKmcData, sizeof(MN_CALL_APP_EC_KMC_DATA_STRU));


    /* 发送VOS消息ID_TAF_CALL_APP_SET_EC_KMC_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEccKmcSetReq);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_SetEccTestMode
 功能描述  : 密话测试模式设置 消息发送函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             VOS_UINT32                                              ulTestMode 测试模式
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SetEccTestMode(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulTestMode
)
{

    TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU                 *pstEccTestModeReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid       = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEccTestModeReq = (TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU));
    if (VOS_NULL_PTR == pstEccTestModeReq)
    {
        AT_ERR_LOG("TAF_XCALL_SetEccTestMode: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstEccTestModeReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstEccTestModeReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstEccTestModeReq->ulSenderPid                          = ulSenderPid;
    pstEccTestModeReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstEccTestModeReq->ulReceiverPid                        = ulReceiverPid;
    pstEccTestModeReq->ulLength                             = sizeof(TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;


    /* 填写消息内容 */
    pstEccTestModeReq->enMsgName                            = ID_TAF_CALL_APP_SET_EC_TEST_MODE_REQ;
    pstEccTestModeReq->stCtrl.usClientId                    = usClientId;
    pstEccTestModeReq->stCtrl.ucOpId                        = opId;
    pstEccTestModeReq->stCtrl.ulModuleId                    = ulModuleId;
    pstEccTestModeReq->enEccTestModeStatus                  = ulTestMode;


    /* 发送VOS消息ID_TAF_CALL_APP_SET_EC_TEST_MODE_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEccTestModeReq);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_QryEncryptCallRandom
 功能描述  : 随即数查询请求消息发送函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryEncryptCallRandom(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU                    *pstGetEccRandomReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid      = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstGetEccRandomReq = (TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU));
    if (VOS_NULL_PTR == pstGetEccRandomReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryEncryptCallRandom: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstGetEccRandomReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstGetEccRandomReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstGetEccRandomReq->ulSenderPid                          = ulSenderPid;
    pstGetEccRandomReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstGetEccRandomReq->ulReceiverPid                        = ulReceiverPid;
    pstGetEccRandomReq->ulLength                             = sizeof(TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstGetEccRandomReq->enMsgName                            = ID_TAF_CALL_APP_GET_EC_RANDOM_REQ;
    pstGetEccRandomReq->stCtrl.usClientId                    = usClientId;
    pstGetEccRandomReq->stCtrl.ucOpId                        = opId;
    pstGetEccRandomReq->stCtrl.ulModuleId                    = ulModuleId;

    /* 发送VOS消息ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstGetEccRandomReq);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_QryEncryptCallKmc
 功能描述  : 查看密话公钥 消息发送函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryEncryptCallKmc(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_GET_EC_KMC_REQ_STRU                       *pstGetEccKmcReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid      = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstGetEccKmcReq = (TAF_CALL_APP_GET_EC_KMC_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_GET_EC_KMC_REQ_STRU));
    if (VOS_NULL_PTR == pstGetEccKmcReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryEncryptCallKmc: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstGetEccKmcReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_GET_EC_KMC_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstGetEccKmcReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstGetEccKmcReq->ulSenderPid                          = ulSenderPid;
    pstGetEccKmcReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstGetEccKmcReq->ulReceiverPid                        = ulReceiverPid;
    pstGetEccKmcReq->ulLength                             = sizeof(TAF_CALL_APP_GET_EC_KMC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstGetEccKmcReq->enMsgName                            = ID_TAF_CALL_APP_GET_EC_KMC_REQ;
    pstGetEccKmcReq->stCtrl.usClientId                    = usClientId;
    pstGetEccKmcReq->stCtrl.ucOpId                        = opId;
    pstGetEccKmcReq->stCtrl.ulModuleId                    = ulModuleId;

    /* 发送VOS消息ID_TAF_CALL_APP_GET_EC_KMC_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstGetEccKmcReq);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_QryEncryptCallTestMode
 功能描述  : 查询当前是否未测试模式 消息发送函数
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId

 输出参数  : 无
 返 回 值  : VOS_UINT 32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryEncryptCallTestMode(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU                 *pstGetEccTestModeReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstGetEccTestModeReq = (TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU));
    if (VOS_NULL_PTR == pstGetEccTestModeReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryEncryptCallTestMode: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstGetEccTestModeReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写VOS消息头 */
    pstGetEccTestModeReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstGetEccTestModeReq->ulSenderPid                          = ulSenderPid;
    pstGetEccTestModeReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstGetEccTestModeReq->ulReceiverPid                        = ulReceiverPid;
    pstGetEccTestModeReq->ulLength                             = sizeof(TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstGetEccTestModeReq->enMsgName                            = ID_TAF_CALL_APP_GET_EC_TEST_MODE_REQ;
    pstGetEccTestModeReq->stCtrl.usClientId                    = usClientId;
    pstGetEccTestModeReq->stCtrl.ucOpId                        = opId;
    pstGetEccTestModeReq->stCtrl.ulModuleId                    = ulModuleId;

    /* 发送VOS消息ID_TAF_CALL_APP_GET_EC_TEST_MODE_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstGetEccTestModeReq);

    return VOS_OK;
}
#endif
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_XCALL_SetPrivacyModePreferred
 功能描述  : 设置Privacy mode优先模式
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             VOS_UINT32                                              ulPrivacyMode

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SetPrivacyModePreferred(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulPrivacyMode
)
{
    TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU                 *pstPrivacyModeReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);


    pstPrivacyModeReq = (TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                                               sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeReq)
    {
        AT_ERR_LOG("TAF_XCALL_SetPrivacyModePreferred: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstPrivacyModeReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));


    /* 填写VOS消息头 */
    pstPrivacyModeReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulSenderPid                          = ulSenderPid;
    pstPrivacyModeReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulReceiverPid                        = ulReceiverPid;
    pstPrivacyModeReq->ulLength                             = sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstPrivacyModeReq->enMsgName                            = ID_TAF_CALL_APP_PRIVACY_MODE_SET_REQ;
    pstPrivacyModeReq->stCtrl.usClientId                    = usClientId;
    pstPrivacyModeReq->stCtrl.ucOpId                        = opId;
    pstPrivacyModeReq->stCtrl.ulModuleId                    = ulModuleId;

    pstPrivacyModeReq->enPrivacyMode                        = (TAF_CALL_PRIVACY_MODE_ENUM_UINT8)ulPrivacyMode;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstPrivacyModeReq);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_QryPrivacyModePreferred
 功能描述  : 查询Privacy mode优先模式
 输入参数  : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryPrivacyModePreferred(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU                 *pstPrivacyModeReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);


    pstPrivacyModeReq = (TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                                               sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryPrivacyModePreferred: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstPrivacyModeReq + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));


    /* 填写VOS消息头 */
    pstPrivacyModeReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulSenderPid                          = ulSenderPid;
    pstPrivacyModeReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulReceiverPid                        = ulReceiverPid;
    pstPrivacyModeReq->ulLength                             = sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstPrivacyModeReq->enMsgName                            = ID_TAF_CALL_APP_PRIVACY_MODE_QRY_REQ;
    pstPrivacyModeReq->stCtrl.usClientId                    = usClientId;
    pstPrivacyModeReq->stCtrl.ucOpId                        = opId;
    pstPrivacyModeReq->stCtrl.ulModuleId                    = ulModuleId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstPrivacyModeReq);

    return VOS_OK;
}
#endif


#ifdef  __cplusplus
#if  __cplusplus
}
#endif
#endif
