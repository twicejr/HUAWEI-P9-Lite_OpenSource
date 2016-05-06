/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMtFsmMain.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service)MT短信状态机处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafXsmsMtFsmMain.h"
#include  "TafXsmsMtFsmMainTbl.h"
#include  "TafXsmsCtx.h"
#include  "TafXsmsSndXcc.h"
#include  "TafXsmsSndCas.h"
#include  "TafXsmsSndAt.h"
#include  "TafXsmsMsgProc.h"
#include  "TafXsmsTimer.h"
#include  "UsimPsInterface.h"
#include  "TafXsmsUimProc.h"
#include  "TafXsmsDecode.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "TafXsmsEncode.h"
#include  "TafSdcCtx.h"
#include  "TafXsmsSndXcall.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MT_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtFsmMainProc
 功能描述  : MT状态机对外主接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : C00299064
    修改内容   : 新生成函数

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MtFsmMainProc(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enCurState;
    VOS_UINT16                          usTemp = 0;
    TAF_ACTION_FUNC                     pActFun;
    REL_TIMER_MSG                      *pstRelTimerMsg;

    if (VOS_PID_TIMER == pstMsg->ulSenderPid)
    {
        /* 定时器消息处理 */
        pstRelTimerMsg = (REL_TIMER_MSG*)pstMsg;

        ulEventType = TAF_BuildEventType(VOS_PID_TIMER, pstRelTimerMsg->ulName);
    }
    else if (WUEPS_PID_USIM == pstMsg->ulSenderPid)
    {
        /* 卡消息处理 */
        PS_MEM_CPY(&usTemp, pstMsg->aucValue, 2);

        ulEventType = TAF_BuildEventType(WUEPS_PID_USIM, usTemp);
    }
    else
    {
        PS_MEM_CPY(&usTemp, pstMsg->aucValue, 2);

        ulEventType = TAF_BuildEventType(pstMsg->ulSenderPid, usTemp);
    }

    enCurState = TAF_XSMS_MtGetCurrFsmId();

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MT_FSM, (VOS_UINT8*)&enCurState, sizeof(TAF_XSMS_MO_FSM_ID_ENUM_UINT32));

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtFsmMainProc:Current Status is ", (VOS_INT32)enCurState);
    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtFsmMainProc:Event Type is ", (VOS_INT32)ulEventType);

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(&g_stTafXsmsMtFsmDesc, enCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun)(ulEventType, (struct MsgCB*)pstMsg);

        return ulRet;
    }

    TAF_XSMS_WARNING_LOG("TAF_XSMS_MtFsmMainProc:TAF_FSM_FindAct return null ptr ");

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtDealTlAck
 功能描述  : 处理是否发送TL ACK
 输入参数  : enCauseCode，enErrorClass
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtDealTlAck
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* 判断是否需要回TL ACK */
    if (VOS_TRUE == pstMtRec->stTLP2PMsg.unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent)
    {
        TAF_XSMS_NORMAL_LOG("TAF_XSMS_MtDealTlAck:need to send TL ACK");

        if (TAF_XSMS_CCF_AP_MEM_FULL == TAF_XSMS_GetApMemFullFlag())
        {
            TAF_XSMS_NORMAL_LOG("TAF_XSMS_MtDealTlAck: TAF_XSMS_GetApMemFullFlag is full");
            enCauseCode     = TAF_XSMS_TL_DESTINATION_RESOURCE_SHORTAGE;
            enErrorClass    = TAF_XSMS_TL_CAUSECODE_TMP;
        }

        /*  将CAUSE CODE 存入MT全局变量，启动TL_ACK发送的总定时器，1S超时,如果超过30次直接失败退出流程 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_RESEND,
                            pstMtRec->stResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND);

        if (VOS_ERR == TAF_XSMS_EncodeTlAckInMtRec(enCauseCode,  enErrorClass))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealTlAck: TAF_XSMS_EncodeTlAckInMtRec err");

            TAF_XSMS_MtIdleInit();

            return ;
        }

        if (VOS_ERR == TAF_XSMS_SndCasTlAckAccordingCurUeState())
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealTlAck: TAF_XSMS_SndCasTlAckAccordingCurUeState err");

            TAF_XSMS_MtIdleInit();

            return ;
        }

        return ;

    }
    else
    {
        if (TAF_XSMS_ACTIVE_CSCH  == pstMtRec->enActiveRevChannel)
        {
            TAF_XSMS_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
            TAF_XSMS_SndCasCschOrderMsg(0, pstMtRec->enIsCasAckFlag, pstMtRec->aucCasAckData);
        }
    }

    /* 不需要回复TL ACK，或者发送TL ACK出错 */
    if (TAF_XSMS_ACTIVE_DSCH  == pstMtRec->enActiveRevChannel)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealTlAck:no need to send TL ACK, end call");

        /* Traffic channel，拆信道 */
        TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealTlAck:no need to send TL ACK, return to IDLE");

        /* Access channel，回IDLE,初始化全局变量和状态机 */
        TAF_XSMS_MtIdleInit();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtDealPrl
 功能描述  : 处理PRL短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtDealPrl(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulEncodedResult;
    VOS_UINT8                           ucEncodedLen;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    PS_MEM_SET(aucData, 0, TAF_XSMS_RECORD_LEN_MAX);

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* 是PRL，如果卡没满,发送写卡请求 */
    if (VOS_OK == TAF_XSMS_FindFreeIndex(&ucIndex))
    {
        TAF_XSMS_INFO_LOG1("TAF_XSMS_MtDealPrl:FindFreeIndex = ", (VOS_UINT32)ucIndex);

        /* 调用编码接口将 stuct转换成TL PDU码流,bear_reply_seq写成63 */
        ulEncodedResult = TAF_XSMS_EncodeBearDataStruToSimRaw(&pstMtRec->stTLP2PMsg.stMessage,
                                                              aucData + 2,
                                                              TAF_XSMS_BEAR_REPLY_SEQ_PRL,
                                                              &ucEncodedLen,
                                                              TAF_XSMS_STATUS_REC_UNREAD,
                                                              VOS_TRUE);

        /* 内容超过卡上一条短信容量，直接返回带cause code的TL ACK给网络 */
        if (VOS_OK != ulEncodedResult)
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_MtDealPrl:encode BearDataStru to SimRawPDU error");

            TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS,
                                 TAF_XSMS_TL_CAUSECODE_TMP);
            return;
        }

        /* 标记短信为接收未读 */
        aucData[0] = TAF_XSMS_STATUS_STO_SEND;
        /* 标记短信TL PDU长度 */
        aucData[1] = ucEncodedLen;

        /* 写卡 */
        TAF_XSMS_PrlWriteReq(ucEncodedLen + 2, aucData, ucIndex);

        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF_MAX);

        /* 设置当前状态为等写卡回复 */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE);
    }
    else
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_MtDealPrl:no free index in uim, to report uim full");

        /* 调用AT接口上报卡满 */
        TAF_XSMS_MsgUimFullInd();

        /* 生成TL_ACK CAUSE CODE 为卡满 */
        TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_RESOURCE_SHORTAGE,
                             TAF_XSMS_TL_CAUSECODE_TMP);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtDealDataInd
 功能描述  : 接入层数据上报的处理函数
 输入参数  : pstDataInd:上报的数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtDealDataInd(TAF_XSMS_CAS_DATA_IND_MSG_STRU *pstDataInd)
{
    VOS_UINT32                          ulDecodedResult;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec  = VOS_NULL_PTR;

    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec  = VOS_NULL_PTR;
    TAF_XSMS_MO_FSM_ID_ENUM_UINT32      enCurMoFsmId;

    enCurMoFsmId    = TAF_XSMS_MoGetCurrFsmId();
    pstMtRec        = TAF_XSMS_MtGetRecAddr();
    pstMoRec        = TAF_XSMS_MoGetRecAddr();

    /* 收到短信，需要将MO_REC里面的发送短信过程中收到短信的标志置成TRUE */
    if (TAF_XSMS_MO_IDLE_STATE != enCurMoFsmId)
    {
        pstMoRec->ucIsRcvSmsWhenSndSms =  VOS_TRUE;
    }


    /* 保存接收短信的信道 */
    if (ID_CAS_CNAS_1X_DSCH_DATA_IND == pstDataInd->enMsgId)
    {
        pstMtRec->enActiveRevChannel = TAF_XSMS_ACTIVE_DSCH;
    }
    else
    {
        pstMtRec->enActiveRevChannel = TAF_XSMS_ACTIVE_CSCH;
    }

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtDealDataInd:ActiveRevChannel is ",
                       (VOS_UINT32)pstMtRec->enActiveRevChannel);

    /* 通过解码接口变成TL STRU */
    ulDecodedResult = TAF_XSMS_DecodeTLRawToTLStru(pstDataInd->ucLen, pstDataInd->aucMsg, &pstMtRec->stTLP2PMsg);

    TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_RCV_SMS,
                            pstMtRec->stTLP2PMsg.ucBearReplySeqNum,
                            &pstMtRec->stTLP2PMsg.stMessage);

    TAF_XSMS_INFO_LOG1(" Recieve Msg, the seq num is", pstMtRec->stTLP2PMsg.ucBearReplySeqNum);

    /* 如果解码出错，直接返回带cause code的TL ACK给网络 */
    if (VOS_OK != ulDecodedResult)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_MtDealDataInd:DecodeTLRawToTLStru error");

        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        return;
    }

    /* 判断是不是CATPT短信 */
    if ((TAF_XSMS_TELESERVICE_CATPT == pstMtRec->stTLP2PMsg.stMessage.ulTeleserviceID)
    &&  (VOS_TRUE == pstMtRec->stTLP2PMsg.unPresentFlag.stTLBitPresentFlag.bIsOpIsPPDownload))
    {
        TAF_XSMS_MtDealCatptMsgProc(pstDataInd);

        return;
    }
    /* 如果当前的收件箱满直接回复TL_ACK */

    /* 如果是AGPS NI短信需要解码然后将内容传给MTA */
    if (TAF_XSMS_TELESERVICE_AGPS_NI_SMS == pstMtRec->stTLP2PMsg.stMessage.ulTeleserviceID)
    {
        if (VOS_ERR == TAF_XSMS_MtAgpsSmsHandle(&pstMtRec->stTLP2PMsg.stMessage))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealDataInd : TAF_XSMS_MtAgpsSmsHandle ERR");
        }

        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        return;
    }

    /* 如果是KMC短信 */
    if (VOS_TRUE == TAF_XSMS_IsMtKmcSms(&pstMtRec->stTLP2PMsg.stMessage.stAddr))
    {
        if (VOS_OK != TAF_XSMS_MtXcallKmcSmsHandle(&pstMtRec->stTLP2PMsg.stMessage))
        {
             TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealDataInd : TAF_XSMS_MtXcallKmcSmsHandle ERR");
        }

        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        return;
    }

    /* 判断是不是PRL短信 */
    if (VOS_TRUE == pstMtRec->stTLP2PMsg.unPresentFlag.stTLBitPresentFlag.bIsOpIsPRL)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealDataInd: there is a PRL SMS");

        /* 是PRL,先存卡，再读取上报 */
        TAF_XSMS_MtDealPrl();

        return;
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealDataInd: there is a normal SMS");

        /* 通过接口上报 */
        TAF_XSMS_MsgDeliveryInd(&pstMtRec->stTLP2PMsg.stMessage);

        /* 不是PRL,发送 TL_ACK给网络侧 */
        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtDealSndCasDataReq
 功能描述  : 发送data req
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MtDealSndCasDataReq(VOS_VOID)
{
    VOS_UINT32                          ulRst;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    VOS_UINT8                           aucData[3];

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    PS_MEM_SET(aucData, 0, 3);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtDealSndCasDataReq:ActiveRevChannel is ",
                       (VOS_UINT32)pstMtRec->enActiveRevChannel);

    /* 给接入层发消息 */
    if (TAF_XSMS_ACTIVE_DSCH  == pstMtRec->enActiveRevChannel)
    {
        /* Traffic channel */
        ulRst = TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT, &pstMtRec->stDbm);
    }
    else
    {
        /* Access channel，需要携带鉴权信息 */
        TAF_XSMS_EncodeAuth(&pstMtRec->stTLP2PMsg.stMessage.stAddr, aucData);
        TAF_XSMS_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
        ulRst = TAF_XSMS_SndCasCschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT, aucData, &pstMtRec->stDbm);
    }

    if (VOS_ERR == ulRst)
    {
        TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtSendCasTlAck
 功能描述  : 发送TL ACK
 输入参数  : enCauseCode enErrorClass
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MtSendCasTlAck
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
)
{
    VOS_UINT32                          ulEncodedResult;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* 将causecode和errorclass存入全局变量 */
    pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode  = enCauseCode;
    pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass = enErrorClass;

    /* 给网络侧回ACK的 SEQ NUM  */
    pstMtRec->stTLP2PMsg.stCauseCode.ucReplySeq     = pstMtRec->stTLP2PMsg.ucBearReplySeqNum;

    TAF_XSMS_INFO_LOG1(" Send TL_ACK the seq num is ", pstMtRec->stTLP2PMsg.ucBearReplySeqNum);

    /* 通过编码获得TL ACK DBM结构体 */
    ulEncodedResult = TAF_XSMS_GetAckDBMStru(&pstMtRec->stTLP2PMsg.stMessage.stAddr,
                                             &pstMtRec->stTLP2PMsg.stCauseCode,
                                             &pstMtRec->stDbm);

    if (VOS_OK != ulEncodedResult)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtSendCasTlAck:GetAckDBMStru error");

        /* 编码失败 */
        return VOS_ERR;
    }

    if (VOS_OK != TAF_XSMS_MtDealSndCasDataReq())
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtSendCasTlAck:MtDealSndCasDataReq error");

        /* 发送DATAREQ出错 */
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_Resend
 功能描述  : 重发TL ACK
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MtResend
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果没有超过重试次数
    1.0 当前UE状态 IDLE 在CSCH上 发送等待CSCH_CNF
    2.0 当前的UE状态在TCH, 在DSCH上发送
    3.0 当前UE在其他状态等待切换UE状态 */
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstMtRec->ucReSendTimes++;

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_RESEND,
                        pstMtRec->stResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND);

    /* 如果小于30S判断是否需要重试，如果大于30直接失败 返回IDLE 态 */
    if (30 > pstMtRec->ucReSendTimes)
    {
        if (VOS_FALSE == pstMtRec->ulIsTlAckSndToCas)
        {
            if (VOS_OK != TAF_XSMS_SndCasTlAckAccordingCurUeState())
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_MtResend : TAF_XSMS_SndCasTlAckAccordingCurUeState ERR");

                TAF_XSMS_MtIdleInit();
            }
        }
        else
        {
            TAF_XSMS_INFO_LOG1("TAF_XSMS_MtResend:cur resendtimes is", (VOS_UINT32)pstMtRec->ucReSendTimes);
        }

    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtResend : pstMtRec->ucReSendTimes > 30");

        TAF_XSMS_MtIdleInit();
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvIncomingCall_MtIdle
 功能描述  : 在MT_IDLE状态下处理XCC发来的INCOMING_CALL_INCOMING_CALL_IND
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvIncomingCall_MtIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 强转成INCOMING CALL MSG */
    XCC_CSMS_INCOMING_CALL_IND_STRU    *pstIncomingCallIndMsg;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec =  TAF_XSMS_MtGetRecAddr();

    pstIncomingCallIndMsg = (XCC_CSMS_INCOMING_CALL_IND_STRU*)pstMsg;

    /* 将当前链路所有置成短信被叫所有 */
    pstMtRec->ucIsMtCreatLink   = VOS_TRUE;

    /* 如果当前的链路时XSMS所有设置标志位 */
    TAF_SDC_SetXsmsCallExistFlg(VOS_TRUE);

    /* 发送INCOMING CALL 的回复 */
    TAF_XSMS_SndXccIncomingCallRsp(TAF_XSMS_SEND_XCC_CALL_ID_MT, 0, XCC_CSMS_RESULT_SUCC);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvIncomingCall_MtIdle:IsAlertAnsByPass is ",
                      (VOS_UINT32)pstIncomingCallIndMsg->ucIsAlertAnsByPass);

    /* 判断是不是BY PASS */
    if (VOS_TRUE == pstIncomingCallIndMsg->ucIsAlertAnsByPass)
    {
        /* 如果是BY PASS，启动超时定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND_MAX);

        /* 设置当前MT状态机为等待CONN IND */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE);

    }
    else
    {
        /* 如果不是BY PASS，发送ANSWER CALL REQ */
        TAF_XSMS_SndXccAnswerCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MT);

        /* 启动超时定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF_MAX);

        /* 设置当前MT状态机为等待CALL CNF */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvDataInd_MtIdle
 功能描述  : 在MT_IDLE 处理CAS发送的CSCH_DATA_IND或者DSCH_DATA_IND
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvDataInd_MtIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstDataInd;

    pstDataInd = (TAF_XSMS_CAS_DATA_IND_MSG_STRU*)pstMsg;

    /* 处理DATA_IND */
    TAF_XSMS_MtDealDataInd(pstDataInd);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf
 功能描述  : WAITING_XCC_CALL_CONN_STATE状态下处理XCC的XCC_CSMS_CALL_CONN_IND
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    XCC_CSMS_CALL_CONN_IND_STRU        *pstCallConnInd;

    pstMtRec       =  TAF_XSMS_MtGetRecAddr();

    pstCallConnInd = (XCC_CSMS_CALL_CONN_IND_STRU*)pstMsg;

    /* 判断call id,如果不是MT短信的，返回ERR */
    if (TAF_XSMS_SEND_XCC_CALL_ID_MT != pstCallConnInd->ucCallId)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf:not mt CallId");
        return VOS_ERR;
    }

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND);

    /* 标识当前信道是SMS建立的 */
    pstMtRec->ucIsSmsOrigChannel = VOS_TRUE;

    /* 启动保护定时器 */
    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND,
                        TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND_MAX);

    /* 进入到等待SO_IND的状态 */
    TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE);;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvCallConnTimeout_MtWaitXccCallConnCnfs
 功能描述  : TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND定时器超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvCallConnTimeout_MtWaitXccCallConnCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 初始化MT相关的全局变量和定时器,回IDLE */
    TAF_XSMS_MtIdleInit();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvSoInd_MtWaitXccSoInd
 功能描述  : 在TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE状态处理ID_XCC_CSMS_SERVICE_CONNECT_IND
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvSoInd_MtWaitXccSoInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_CSMS_SERVICE_CONNECT_IND_STRU  *pstSoIndMsg;

    pstSoIndMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU*)pstMsg;

    /* 判断SO是否是短信的 */
    if ((TAF_CDMA_SO_6_SMS == pstSoIndMsg->enSo)
        || (TAF_CDMA_SO_14_RS2_SMS == pstSoIndMsg->enSo))
    {
        TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvSoInd_MtWaitXccSoInd:SO is ", (VOS_UINT32)pstSoIndMsg->enSo);

        /* 如果是短信SO,停掉定时器 */
        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND);

        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND_MAX);

        /* 设置当前状态为等待DATA_IND */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE);

        return VOS_OK;
    }
    else
    {
        /* 如果不是短信的SO,继续等待 */
        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvSoIndTimeout_MtWaitXccSoInd
 功能描述  : TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND定时器超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvSoIndTimeout_MtWaitXccSoInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 拆信道 */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf
 功能描述  : TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE状态下处理XCC_CSMS_ANSWER_CALL_CNF
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_CSMS_ANSWER_CALL_CNF_STRU      *pstCallCnf;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstCallCnf = (XCC_CSMS_ANSWER_CALL_CNF_STRU*)pstMsg;

    /* 判断call id,如果不是MT短信的，返回ERR */
    if (TAF_XSMS_SEND_XCC_CALL_ID_MT != pstCallCnf->ucCallId)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf:not mt CallId");

        return VOS_ERR;
    }

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF);

    /* 判断是不是创建OK */
    if (TAF_XCC_CAUSE_SUCCESS == pstCallCnf->enRslt)
    {
        /* 肯定是短信建的,存入全局变量 */
        pstMtRec->ucIsSmsOrigChannel = VOS_TRUE;

        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND_MAX);

        /* 进入到等待SO_IND的状态 */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE);
    }
    else if (TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH == pstCallCnf->enRslt)
    {
        /* 如果是已经建好链路，不需要等SO，直接等DATA IND */
        pstMtRec->ucIsSmsOrigChannel = VOS_FALSE;
        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND_MAX);

        /* 设置当前状态为等待DATA_IND */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE);
    }
    else
    {
        /* 拆链 */
        TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvAnsCallCnfTimeout_MtWaitXccAnsCallCnf
 功能描述  : TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF定时器超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvAnsCallCnfTimeout_MtWaitXccAnsCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 拆信道 */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd
 功能描述  : 在TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE状态下处理CAS发送的DSCH_DATA_IND
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstDschData;

    pstDschData = (TAF_XSMS_CAS_DATA_IND_MSG_STRU*)pstMsg;

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND);

    /* 处理DATA_IND */
    TAF_XSMS_MtDealDataInd(pstDschData);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvDschDataIndTimeout_MtWaitCasDschDataInd
 功能描述  : TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvDschDataIndTimeout_MtWaitCasDschDataInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 拆信道回到MT_IDLE状态 */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf
 功能描述  : PRL更新短信写卡结果处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_UPDATEFILE_CNF_STRU           *pstWriteUimCnf;

    pstWriteUimCnf = (USIMM_UPDATEFILE_CNF_STRU*)pstMsg;

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF);

    if (VOS_OK == pstWriteUimCnf->stCmdResult.ulResult)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf:write uim is ok");

        /* 写卡请求成功，读取该index的PRL短信 */
        if (VOS_OK == TAF_XSMS_PrlReadReq(pstWriteUimCnf->ucRecordNum))
        {
            TAF_XSMS_INFO_LOG("TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf:read uim req is ok");

            /* 起定时器，设置TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE状态 */
            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF,
                                TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF_MAX);

            TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE);

            return VOS_OK;
        }
    }

    /* 写卡失败或者读卡请求失败，给网络侧回复携带CAUSE_CODE的TL ACK */
    TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvWriteUimCnfTimeout_MtWaitWriteUimCnf
 功能描述  : PRL更新短信写卡超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvWriteUimCnfTimeout_MtWaitWriteUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 写卡失败，给网络侧回复携带CAUSE_CODE的TL ACK */
    TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf
 功能描述  : 读取PRL更新短信结果处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstReadUimCnf;
    VOS_UINT8                           aucData[TAF_XSMS_CAS_DATA_IND_MAX_LEN];
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTransportMessage;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstReadUimCnf = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* 停止定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF);

    if ( VOS_OK == pstReadUimCnf->stCmdResult.ulResult)
    {
        /* 读取出卡上短信内容 */
        PS_MEM_SET(aucData, 0, sizeof(aucData));
        PS_MEM_CPY(aucData, (pstReadUimCnf->aucEf + 2), (pstReadUimCnf->usEfLen - 2));

        PS_MEM_SET(&stTransportMessage, 0, sizeof(TAF_XSMS_TRANSPORT_MESSAGE_STRU));

        /*调用编码接口转换成上报的结构体 */
        (VOS_VOID)TAF_XSMS_DecodeTLRawToTLStru((VOS_UINT8)(pstReadUimCnf->usEfLen - 2), aucData, &stTransportMessage);

        /* 上报AP收到一条新短信 */
        TAF_XSMS_MsgDeliveryInd(&stTransportMessage.stMessage);

        /* 给网络侧回复TL ACK */
        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);

        return VOS_OK;
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf:read uim is error");

        /* 读卡失败，给网络侧回复携带CAUSE_CODE的TL ACK */
        TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

        return VOS_ERR;
    }

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvReadUimCnfTimeout_MtWaitReadUimCnf
 功能描述  : 读取PRL更新短信结果超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : l00208516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvReadUimCnfTimeout_MtWaitReadUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 读卡失败，给网络侧回复携带CAUSE_CODE的TL ACK */
    TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf
 功能描述  : traffic channel接收到CAS的L2 ACK处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDschDataCnf;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec =  TAF_XSMS_MtGetRecAddr();

    /* 停止定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF);

    pstDschDataCnf = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pstDschDataCnf->enRslt)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf: dsch cnf succ");

        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_RESEND);

        /* 初始化全局变量和状态机,回IDLE */
        TAF_XSMS_MtIdleInit();

    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf: dsch cnf failed");
    }

    /* 设置当前的SND FLAG 为FALSE 重发定时器超时之后发送 */
    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf
 功能描述  : Access channel接收到CAS的L2 ACK处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU     *pstCschDataCnf;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec =  TAF_XSMS_MtGetRecAddr();

    /* 停止定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF);

    pstCschDataCnf = (CAS_CNAS_1X_CSCH_DATA_CNF_STRU *)pstMsg;

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pstCschDataCnf->enRslt)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf: CSCH cnf succ");

        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_RESEND);

        /* 初始化全局变量和状态机,回IDLE */
        TAF_XSMS_MtIdleInit();
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf: CSCH cnf failed");
    }

    /* 设置当前的SND FLAG 为FALSE 重发定时器超时之后发送 */
    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf
 功能描述  : 等待CAS的L2 ACK超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec    = TAF_XSMS_MtGetRecAddr();

    if (TAF_XSMS_ACTIVE_CSCH == pstMtRec->enActiveRevChannel)
    {
        TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
    }

    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf : Wait cnf time out");

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvEndCallCnf_MtWaitEndCallCnf
 功能描述  : 等待拆信道的结果
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvEndCallCnf_MtWaitEndCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END);

    /* 不论成功失败，都回到MT_IDLE状,初始化全局变量和状态机 */
    TAF_XSMS_MtIdleInit();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvEndCallCnfTimeout_MtWaitEndCallCnf
 功能描述  : 等待拆信道的结果超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : l00208516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvEndCallCnfTimeout_MtWaitEndCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 超时后进入MT_IDLE状态,初始化全局变量和状态机 */
    TAF_XSMS_MtIdleInit();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtEndcallReq
 功能描述  : 拆信道
 输入参数  : enEndReason:呼叫挂断原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtEndcallReq(VOS_UINT8 enEndReason)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec      = TAF_XSMS_MtGetRecAddr();

    /* 如果是MT SMS建立的信道，给XCC发送拆信道请求 */
    if (VOS_TRUE == pstMtRec->ucIsSmsOrigChannel)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtEndcallReq:MO is IDLE, EndCall");

        TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MT, enEndReason);

        /* 起定时器，进入MT_WAITING_XCC_DISCONNECT_STATE状态 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END,
                            TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END_MAX);

        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE);
    }
    else
    {
        /* 初始化全局变量和状态机,回IDLE */
        TAF_XSMS_MtIdleInit();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvMtLinkAbort
 功能描述  : 收到接入层链路ABORT的消息的处理函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvMtLinkAbort
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 断链 */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_MtAgpsSmsHandle
 功能描述  : 收到网侧发给AGPS消息的处理函数
 输入参数  : pstMessage: 短信的结构体
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月16日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MtAgpsSmsHandle(
    TAF_XSMS_MESSAGE_STRU              *pstMessage
)
{

    VOS_UINT16                          usUserDataStartByte = 0;
    VOS_UINT16                          usUserDataLen       = 0;
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;

    PS_MEM_SET(&stUserData, 0, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    /* 解码USER DATA */
    TAF_XSMS_DecodeUserDataInBearerData(pstMessage->ulBearerDataLen,
                                        pstMessage->aucBearerData,
                                        &usUserDataStartByte,
                                        &usUserDataLen,
                                        &stUserData);

    /* 如果不是8BIT OCTET有可能需要转码 */
    if (TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET != stUserData.enMsgCodeType)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtAgpsSmsHandle : TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET != enMsgCodeType");
        return VOS_ERR;
    }

    /* 将短信内容发送給MTA */
    TAF_XSMS_SendXpdsGpsSms(&pstMessage->stAddr,
                            stUserData.ucNumFields,
                            stUserData.aucUserData);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtDealCatptMsgProc
 功能描述  : 接入层数据上报的处理函数
 输入参数  : pstDataInd:上报的数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtDealCatptMsgProc(TAF_XSMS_CAS_DATA_IND_MSG_STRU *pstDataInd)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           ucIsUimPPDownloadEnable;
    VOS_UINT8                           ucIsCsimPPDownloadEnable;
    pstMtRec = TAF_XSMS_MtGetRecAddr();

    ucIsUimPPDownloadEnable     = (VOS_UINT8)USIMM_IsServiceAvailable(UIM_SVR_SMS_PP_DOWNOLAD);
    ucIsCsimPPDownloadEnable    = (VOS_UINT8)USIMM_IsServiceAvailable(CSIM_SVR_SMSPP_DOWNLOAD);

    if ((PS_USIM_SERVICE_AVAILIABLE  == ucIsUimPPDownloadEnable)
     || (PS_USIM_SERVICE_AVAILIABLE  == ucIsCsimPPDownloadEnable))
    {
        /* 上报给STK */
        TAF_XSMS_SendStkCATPTMsg(pstDataInd->ucLen,
                                 pstDataInd->aucMsg,
                                 &pstMtRec->stTLP2PMsg.stMessage);

        /* 回复TL_ACK */
        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                         pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
    }
    else
    {
        /* 直接DOWNLOAD 到USIM卡 */
        if ((VOS_OK != TAF_XSMS_FindFreeIndex(&ucIndex))
        || ((TAF_XSMS_RECORD_LEN_MAX - 2)    < pstDataInd->ucLen))
        {
            /* 回复TL_ACK */
            TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                 TAF_XSMS_TL_CAUSECODE_TMP);
        }
        else
        {
            /* 写卡请求 */
            TAF_XSMS_CommonFileWriteReq(pstDataInd->ucLen,
                                        pstDataInd->aucMsg,
                                        ucIndex);

            /* 回复TL_ACK */
            TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                         pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        }

    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvMtLinkAbort_MtWaitCasCnf
 功能描述  : 收到接入层链路ABORT的消息的处理函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvMtLinkAbort_MtWaitCasCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 收到ABORT之后,和CAS 确认没有CNF回复，清除DATA_REQ已经发送的FLAG
    等待重发定时器超时之后，判断能否重发 */
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeTlAckInMtRec
 功能描述  : 将TL_ACK放在MT_REC中
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeTlAckInMtRec
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
)
{
    VOS_UINT32                          ulEncodedResult;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* 将causecode和errorclass存入全局变量 */
    pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode  = enCauseCode;
    pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass = enErrorClass;

    /* 给网络侧回ACK的 SEQ NUM  */
    pstMtRec->stTLP2PMsg.stCauseCode.ucReplySeq     = pstMtRec->stTLP2PMsg.ucBearReplySeqNum;

    TAF_XSMS_INFO_LOG1(" Send TL_ACK the seq num is ", pstMtRec->stTLP2PMsg.ucBearReplySeqNum);

    TAF_XSMS_HookSmsTlAck(TAF_XSMS_HOOK_MSG_TYPE_SND_TL_ACK, &pstMtRec->stTLP2PMsg.stCauseCode);

    /* 通过编码获得TL ACK DBM结构体 */
    ulEncodedResult = TAF_XSMS_GetAckDBMStru(&pstMtRec->stTLP2PMsg.stMessage.stAddr,
                                             &pstMtRec->stTLP2PMsg.stCauseCode,
                                             &pstMtRec->stDbm);

    if (VOS_OK != ulEncodedResult)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeTlAckInMtRec:TAF_XSMS_GetAckDBMStru error");

        /* 编码失败 */
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeTlAckInMtRec
 功能描述  : 将TL_ACK放在MT_REC中
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SndCasTlAckAccordingCurUeState
(
    VOS_VOID
)
{
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8     enCurUeStatus;
    TAF_XSMS_MSG_MT_REC_STRU                *pstMtRec;
    VOS_UINT8                                aucData[3] = {0};

    pstMtRec =  TAF_XSMS_MtGetRecAddr();

    enCurUeStatus = TAF_SDC_GetCdmaCurUeState();

    TAF_XSMS_INFO_LOG1("TAF_XSMS_SndCasTlAckAccordingCurUeState: enCurUeStatus",enCurUeStatus);

    PS_MEM_SET(aucData, 0, 3);

    if (CAS_CNAS_1X_CAS_IDLE_STATE == enCurUeStatus)
    {
        /* Access channel，需要携带鉴权信息 */
        TAF_XSMS_EncodeAuth(&pstMtRec->stTLP2PMsg.stMessage.stAddr, aucData);

        TAF_XSMS_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);

        if (VOS_OK != TAF_XSMS_SndCasCschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT,
                                                 aucData,
                                                 &pstMtRec->stDbm))
        {
            TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
            TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasTlAckAccordingCurUeState:TAF_XSMS_SndCasCschDataReq ERR");
            return VOS_ERR;
        }

        pstMtRec->ulIsTlAckSndToCas = VOS_TRUE;

        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_CSCH_CNF_MAX);
    }
    else if (CAS_CNAS_1X_CAS_TCH_STATE == enCurUeStatus)
    {
        /* Traffic channel */
        if(VOS_OK != TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT, &pstMtRec->stDbm))
        {

            TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasTlAckAccordingCurUeState:TAF_XSMS_SndCasDschDataReq ERR");
            return VOS_ERR;
        }

        pstMtRec->ulIsTlAckSndToCas = VOS_TRUE;

        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_DSCH_CNF_MAX);
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_SndCasTlAckAccordingCurUeState: enCurUeStatus is not idle or tch");
        pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;
    }

    /* 已经发送TL ACK，设置当前状态为等待AS CNF */
    TAF_XSMS_MtSetCurrFsmState(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtXcallKmcSmsHandle
 功能描述  : 收到网侧发给XCALL KMC消息的处理函数
 输入参数  : pstMessage: 短信的结构体
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MtXcallKmcSmsHandle(
    TAF_XSMS_MESSAGE_STRU              *pstMessage
)
{

    VOS_UINT16                          usUserDataStartByte = 0;
    VOS_UINT16                          usUserDataLen       = 0;
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;

    PS_MEM_SET(&stUserData, 0, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    /* 解码USER DATA */
    TAF_XSMS_DecodeUserDataInBearerData(pstMessage->ulBearerDataLen,
                                        pstMessage->aucBearerData,
                                        &usUserDataStartByte,
                                        &usUserDataLen,
                                        &stUserData);

    /* 如果不是8BIT OCTET有可能需要转码 */
    if (TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET != stUserData.enMsgCodeType)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtXcallKmcSmsHandle : TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET != enMsgCodeType");
        return VOS_ERR;
    }

    /* 将短信内容发送給xcall */
    TAF_XSMS_SndXcallDataInd(stUserData.ucNumFields, stUserData.aucUserData);

    return VOS_OK;

}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

