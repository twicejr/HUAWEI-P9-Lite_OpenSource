/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMoFsmMain.c
  版 本 号   : 初稿
  作    者   : c00299064
  生成日期   : 2014年11月07日
  功能描述   : 1X SMS(Short Message Service)MO状态机主入口,
               每个消息的函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月07日
    作    者   : C00299064
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsLogdef.h"
#include  "TafXsmsSndAt.h"
#include  "TafXsmsTimer.h"
#include  "TafXsmsDecode.h"
#include  "TafXsmsEncode.h"
#include  "TafXsmsSndXcc.h"
#include  "TafXsmsSndCas.h"
#include  "TafXsmsMsgProc.h"
#include  "TafXsmsUimProc.h"
#include  "TafXsmsMoFsmMain.h"
#include  "TafXsmsMoFsmMainTbl.h"
#include  "MmaXsmsInterface.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "TafXpdsXsmsInterface.h"
#include  "TafSdcCtx.h"
#include  "taf_xcall_xsms_pif.h"





#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MO_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/


/*****************************************************************************
 函 数 名  : TAF_XSMS_MoFsmMainProc
 功能描述  : MO状态机对外主接口
 输入参数  : pstMsg 外部消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoFsmMainProc(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet           = VOS_ERR;
    TAF_XSMS_MO_FSM_ID_ENUM_UINT32      enCurState;
    VOS_UINT16                          usTemp = 0;
    TAF_ACTION_FUNC                     pActFun;
    REL_TIMER_MSG                      *pstRelTimerMsg;

    enCurState = TAF_XSMS_MoGetCurrFsmId();

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MO_FSM, (VOS_UINT8*)&enCurState, sizeof(TAF_XSMS_MO_FSM_ID_ENUM_UINT32));

    if (VOS_PID_TIMER == pstMsg->ulSenderPid)
    {
        pstRelTimerMsg = (REL_TIMER_MSG*)pstMsg;
        /* 判断是不是 非MO_IDLE状态 超时 */
        if ((TI_TAF_XSMS_TIMER_MO_IDLE == pstRelTimerMsg->ulName)
            && (TAF_XSMS_MO_IDLE_STATE != enCurState))
        {
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);

            TAF_XSMS_MoIdleInit();

            TAF_XSMS_ERROR_LOG("TAF_XSMS_MoFsmMainProc: MO_IDLE timeOut");

            return VOS_ERR;
        }
        else
        {
            ulEventType = TAF_BuildEventType(VOS_PID_TIMER, pstRelTimerMsg->ulName);
        }
    }
    else
    {
        /* 需要判断大小端 */
        PS_MEM_CPY(&usTemp, pstMsg->aucValue, 2);

        ulEventType = TAF_BuildEventType(pstMsg->ulSenderPid, usTemp);
    }

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MoFsmMainProc:Current Status is ", (VOS_INT32)enCurState);
    TAF_XSMS_INFO_LOG1("TAF_XSMS_MoFsmMainProc:Event Type is ", (VOS_INT32)ulEventType);

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(&g_stTafXsmsMoFsmDesc, enCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet = (*pActFun)(ulEventType, (struct MsgCB*)pstMsg);

        return ulRet;
    }

    TAF_XSMS_WARNING_LOG("TAF_XSMS_MoFsmMainProc:TAF_FSM_FindAct return null ptr ");

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoIdleRcvAtSendReqOnDschProc
 功能描述  : NV项为DSCH_ONLY发送流程(先建链)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK -- 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnDschProc(VOS_VOID)
{
    TAF_XSMS_INFO_LOG("TAF_XSMS_MoIdleRcvAtSendReqOnDschProc: first time to link");

    TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoIdleRcvAtSendReqOnCschProc
 功能描述  : NV项为CSCH_ONLY 发送的处理流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnCschProc(VOS_VOID)
{
    TAF_XSMS_SndCasCschReq_MoWaitCasCnf();

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CAS_XSMS_MoIdleRcvAtSendReqOnDschOrCschProc
 功能描述  : NV 项为CSCH OR DSCH发送的处理流程
 输入参数  : pstRecAddr:MO的状态全局变量的地址
 输出参数  : 无
 返 回 值  : VOS_OK -- 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnDschOrCschProc(TAF_XSMS_MSG_MO_REC_STRU *pstRecAddr)
{
#if 0
    if (/* 当前状态是IDLE状态 */)
    {
        pstRecAddr->enActiveSndChannel = TAF_XSMS_ACTIVE_CSCH;
        TAF_XSMS_MoIdleRcvAtSendReqOnCschProc();
    }
    else
    {
        pstRecAddr->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;
        TAF_XSMS_MoIdleRcvAtSendReqOnDschProc();
    }
#endif
    pstRecAddr->enActiveSndChannel = TAF_XSMS_ACTIVE_CSCH;

    TAF_XSMS_MoIdleRcvAtSendReqOnCschProc();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoIdleRcvAtSendReqDispatchProc
 功能描述  : 根据NV项信道选择,选择发送信道
 输入参数  : pstRecAddr:MO的状态全局变量的地址
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec)
{
    VOS_UINT32                          ulRslt;

    /* 当前配置是走专用信道 */
    if (TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN == pstMoRec->stNvResend.enXsmsChannelOption)
    {
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnDschProc();
    }
    /* 当前配置是走公共信道 */
    else if (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN == pstMoRec->stNvResend.enXsmsChannelOption)
    {
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_CSCH;
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnCschProc();
    }
    /* 当前配置是走两个信道都可以 */
    else if (TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH == pstMoRec->stNvResend.enXsmsChannelOption)
    {
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnDschOrCschProc(pstMoRec);
    }
    else
    {
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnDschProc();
    }

    /* 判断如果当前状态改变 直接启动非MO_IDLE状态持续定时器 */
    if (VOS_OK == ulRslt)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_IDLE,
                            TI_TAF_XSMS_TIMER_MO_IDLE_MAX);
    }
    return ulRslt;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoIncreaseMessageId
 功能描述  : 将全局变量里面的MSG_ID加1 写回卡里
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MoIncreaseMessageId(VOS_VOID)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           aucMsgId[sizeof(VOS_UINT16)];
    VOS_UINT16                          usMsgId;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 将MSG加1后写入UIM卡内，不等待UIM的CNF消息，即使失败也不影响后面的短信发送 */
    pstInitCtrlInfoAddr->usMessageId++;

    usMsgId = pstInitCtrlInfoAddr->usMessageId;

    aucMsgId[0] = (usMsgId >> 8) & 0xFF;
    aucMsgId[1] = usMsgId & 0xFF;

    TAF_XSMS_MsgIdUpdataReq(aucMsgId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvAtSendReqProc_MoIdle
 功能描述  : MO Idle状态下收到AT下发的AT命令发送短信的处理流程
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:AT的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvAtSendReqProc_MoIdle(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{

    VOS_UINT32                          ulUsimState;
    VOS_UINT32                          ulCsimState;
    TAF_XSMS_SEND_MSG_REQ_STRU         *pstAtMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    USIMM_FdnQuery(&ulUsimState, &ulCsimState);

    if (USIMM_FDNSTATUS_OFF == ulCsimState)
    {
        pstAtMsg    = (TAF_XSMS_SEND_MSG_REQ_STRU *)pstMsg;

        /* MO 记录全局变量 */
        pstMoRec    = TAF_XSMS_MoGetRecAddr();
        pstDbm      = &(pstMoRec->stDbm);

        /* INIT CTRL 记录全局变量 */
        pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

        /* 将AT下发的STRU保存到全局变量中(FDN,CC可能会用) */
        PS_MEM_CPY(&pstMoRec->st1xSms, &pstAtMsg->st1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

        pstMoRec->enOrigPid         = TAF_XSMS_SMS_ORIGPID_AT;
        pstMoRec->usIsTlAckNeed     = VOS_TRUE;

        /* 将现在的MSG_ID写到MO_REC全局变量中 */
        pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;
        ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);

        /* 将AT下发的数据转换成DBM存在全局变量中 */
        if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstAtMsg->st1XSms,
                                               pstMoRec->usMessageId,
                                               ucReqSeq,
                                               TAF_XSMS_STATUS_STO_UNSEND,
                                               pstDbm,
                                               VOS_TRUE))
        {
            /* 保持MO_IDLE */
            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

            return VOS_ERR;
        }

        TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &pstAtMsg->st1XSms);

        /* 将MSG_ID写回卡中 (需要决定是这时候写还是等到TL_ACK再写) */
        TAF_XSMS_MoIncreaseMessageId();

        return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);
    }
    else
    {
        /* 做FDN的处理 */
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvStkSendReqProc_MoIdle
 功能描述  : MO Idle状态下收到STK下发的AT命令发送短信的处理流程
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:STK的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvStkSendReqProc_MoIdle(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{

    VOS_UINT32                          ulUsimState;
    VOS_UINT32                          ulCsimState;
    STK_XSMS_SEND_SMS_REQ_STRU         *pstStkSendMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    USIMM_FdnQuery(&ulUsimState, &ulCsimState);

    if (USIMM_FDNSTATUS_OFF == ulCsimState)
    {
        pstStkSendMsg    = (STK_XSMS_SEND_SMS_REQ_STRU *)pstMsg;

        /* MO 记录全局变量 */
        pstMoRec    = TAF_XSMS_MoGetRecAddr();
        pstDbm      = &(pstMoRec->stDbm);

        /* INIT CTRL 记录全局变量 */
        pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

        /* 将STK下发的STRU保存到全局变量中(FDN,CC可能会用) */
        PS_MEM_CPY(&pstMoRec->st1xSms, &pstStkSendMsg->st1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

        pstMoRec->enOrigPid         = TAF_XSMS_SMS_ORIGPID_STK;

        if (VOS_TRUE == pstStkSendMsg->ulIsUserAck)
        {
            pstMoRec->usIsTlAckNeed     = VOS_FALSE;
        }
        else
        {
            pstMoRec->usIsTlAckNeed     = VOS_TRUE;
        }

        /* 将现在的MSG_ID写到MO_REC全局变量中 */
        pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;

        /* 将STK下发的数据转换成DBM存在全局变量中 */
        if (VOS_TRUE == pstMoRec->usIsTlAckNeed)
        {
            ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);
            if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstStkSendMsg->st1XSms,
                                                   pstMoRec->usMessageId,
                                                   ucReqSeq,
                                                   TAF_XSMS_STATUS_STO_UNSEND,
                                                   pstDbm,
                                                   VOS_TRUE))
            {
                /* 保持MO_IDLE */
                TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

                return VOS_ERR;
            }
        }
        else
        {
            if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstStkSendMsg->st1XSms,
                                                   pstMoRec->usMessageId,
                                                   0,
                                                   TAF_XSMS_STATUS_STO_UNSEND,
                                                   pstDbm,
                                                   VOS_FALSE))
            {
                /* 保持MO_IDLE */
                TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

                return VOS_ERR;
            }

        }
        TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &pstStkSendMsg->st1XSms);

        /* 将MSG_ID写回卡中 (需要决定是这时候写还是等到TL_ACK再写) */
        TAF_XSMS_MoIncreaseMessageId();

        return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);
    }
    else
    {
        /* 做FDN的处理 */
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_EncodeXsmsMsgBearDataByContext
 功能描述  : MO Idle状态下收到MTA下发的命令发送短信的处理流程
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:MTA的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeXsmsMsgBearDataByContext
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;
    VOS_UINT8                           aucEncodedData[256] = {0};
    VOS_UINT8                           ucEncodeDataLen     = 0;
    TAF_XSMS_MSG_ID_STRU                stMsgId;

    /* 标准的MSG_ID 结构体 */
    stMsgId.enMsgType           = TAF_XSMS_BD_MSG_TYPE_SUBMIT;
    stMsgId.ucIsHeadIndExist    = VOS_FALSE;
    stMsgId.usMsgID             = 0;

    /* 组成标准USER DATA 结构 */
    PS_MEM_SET(&stUserData, 0, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    stUserData.enMsgCodeType = TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET;

    if (TAF_XSMS_BD_PURE_CONTEXT_MAX_LEN_8 < usDataLen)
    {
        return VOS_ERR;
    }

    stUserData.ucNumFields  = (VOS_UINT8)usDataLen;

    PS_MEM_CPY(stUserData.aucUserData, pucData, usDataLen);

    /* 生成BEAR DATA */
    /* 生成MSG ID */
    TAF_XSMS_EncodeMsgID(&stMsgId,
                         &ucEncodeDataLen,
                         aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* 生成USER DATA */
    TAF_XSMS_EncodeUserData(&stUserData,
                            &ucEncodeDataLen,
                            aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* 生成LANGUAGE INDICATOR */
    aucEncodedData[0] = TAF_XSMS_BD_LANGUAGE_INDICATOR;
    aucEncodedData[1] = 1;
    aucEncodedData[2] = TAF_XSMS_BD_LANGUAGE_INDICATOR_ENGLISH;

    ucEncodeDataLen   = 3;

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXpdsSendReqProc_MoIdle
 功能描述  : MO Idle状态下收到MTA下发的命令发送短信的处理流程
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:MTA的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXpdsSendReqProc_MoIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XSMS_SEND_REQ_STRU        *pstSendReq;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    pstSendReq  = (TAF_XPDS_XSMS_SEND_REQ_STRU*)pstMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(stXsmsMsg));

    /* MO 记录全局变量 */
    pstMoRec    = TAF_XSMS_MoGetRecAddr();
    pstDbm      = &(pstMoRec->stDbm);

    /* INIT CTRL 记录全局变量 */
    pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 将MTA消息转换成标准的短信结构体 */
    PS_MEM_CPY(&stXsmsMsg.stAddr,
               &pstSendReq->stXsmsAddr,
               sizeof(TAF_XSMS_ADDR_STRU));

    if (VOS_ERR == TAF_XSMS_EncodeXsmsMsgBearDataByContext(pstSendReq->aucData,
                                                           pstSendReq->usDataLen,
                                                          &stXsmsMsg))
    {
        return VOS_ERR;
    }

    stXsmsMsg.ulTeleserviceID   = TAF_XSMS_TELESERVICE_AGPS_NI_SMS;

    /* 将STK下发的STRU保存到全局变量中(FDN,CC可能会用) */
    PS_MEM_CPY(&pstMoRec->st1xSms, &stXsmsMsg, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstMoRec->enOrigPid         = TAF_XSMS_SMS_ORIGPID_XPDS;
    pstMoRec->usIsTlAckNeed     = VOS_TRUE;

    /* 将现在的MSG_ID写到MO_REC全局变量中 */
    pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;

    ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);
    /* 将MTA下发的数据转换成DBM存在全局变量中 */
    if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&stXsmsMsg,
                                           pstMoRec->usMessageId,
                                           ucReqSeq,
                                           TAF_XSMS_STATUS_STO_UNSEND,
                                           pstDbm,
                                           VOS_TRUE))
    {
        /* 保持MO_IDLE */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

        return VOS_ERR;
    }

    TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &stXsmsMsg);

    /* 将MSG_ID写回卡中 (需要决定是这时候写还是等到TL_ACK再写) */
    TAF_XSMS_MoIncreaseMessageId();

    return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);


}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXccOrgiCallCnfRedialCheck
 功能描述  : 根据XCC上报的原因值判断是否需要重拔
 输入参数  : enRslt:XCC上报的原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : H00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXccOrgiCallCnfRedialCheck(TAF_XCC_CAUSE_ENUM_UINT32 enRslt)
{
    switch (enRslt)
    {
        /* 需要重拔的原因值 */
        case TAF_XCC_CAUSE_NO_SERVICE:
        case TAF_XCC_CAUSE_MAX_ACCESS_PROBES:
        case TAF_XCC_CAUSE_REORDER:
        case TAF_XCC_CAUSE_ACCESS_DENYIED:
        case TAF_XCC_CAUSE_ACCT_BLOCK:
        case TAF_XCC_CAUSE_NDSS:
        case TAF_XCC_CAUSE_REDIRECTION:
        case TAF_XCC_CAUSE_ACCESS_IN_PROGRESS:
        case TAF_XCC_CAUSE_ACCESS_FAIL:
        case TAF_XCC_CAUSE_ABORT:
        case TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH:
        case TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH:
        case TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT:
        case TAF_XCC_CAUSE_CCS_NOT_SUPPORT:
        case TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL:
        case TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL:
        case TAF_XCC_CAUSE_SO_REJ:

            return VOS_TRUE;
        default:

        /* no matter what reason just try to relink */
            return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXccOrigCallCnfRedialProc
 功能描述  : 根据XCC上报的原因值判断是否需要重拔的处理
 输入参数  : pstMoRec:MO的上下文信息
             pstXccSmsOrigCallCnf:XCC上报的信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : H00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XSMS_RcvXccOrigCallCnfRedialProc(
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec,
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU    *pstXccSmsOrigCallCnf)
{
    if (VOS_TRUE == TAF_XSMS_RcvXccOrgiCallCnfRedialCheck(pstXccSmsOrigCallCnf->enRslt))
    {
        if (pstMoRec->stNvResend.ucResendMax > pstMoRec->ucResendTimes)
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnfRedialProc:Remain times left, retry");

            /* 设置层2错误标识
            1.0 如果此次是L2错误 上次也是L2 直接加1
            2.0 如果此次是L2错误 上次不是L2 错误次数变成1
            3.0 如果此次不是L2错误 上次不是L2 错误次数加1
            4.0 如果此次不是L2错误 上次是L2 错误次数变成1*/
            if (TAF_XCC_FAIL_LAYER_L2 == pstXccSmsOrigCallCnf->enIsL2Err)
            {
                pstMoRec->ucIsL2ErrReOrig   = VOS_TRUE;
                pstMoRec->enLastErrType     = TAF_XCC_FAIL_LAYER_L2;
                if (TAF_XCC_FAIL_LAYER_L3 != pstMoRec->enLastErrType)
                {
                    pstMoRec->ucL2ErrReOrigCount++;
                }
                else
                {
                    pstMoRec->ucL2ErrReOrigCount = 1;
                }
            }
            else
            {
                pstMoRec->ucIsL2ErrReOrig   = VOS_FALSE;
                pstMoRec->enLastErrType     = TAF_XCC_FAIL_LAYER_L3;
                if (TAF_XCC_FAIL_LAYER_L2 != pstMoRec->enLastErrType)
                {
                    pstMoRec->ucL2ErrReOrigCount++;
                }
                else
                {
                    pstMoRec->ucL2ErrReOrigCount = 1;
                }

            }
            /* 不管因为什么原因失败，都在等待OHM之后重新建链，或者5秒定时器超时之后建链 */
            pstMoRec->ucWaitRedirCompleteFlag = VOS_TRUE;

            /* 启动重连定时器，不改变当前状态(等待XCC_CNF) */
            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                                pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND);

        }
        /* 重试次数超限不再尝试，进入IDLE状态 */
        else
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnfRedialProc:No times left,return MO Idle");

            /* 上报AT发送失败 */
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

            /* 拆链,初始化全局变量 */
            TAF_XSMS_MoIdleInit();
        }
    }
    else
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnfRedialProc:No need retry");

        /* 上报AT发送失败 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        /* 拆链初始化全局变量 */
        TAF_XSMS_MoIdleInit();
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf
 功能描述  : 收到XCC_CALL_CNF消息的处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:XCC的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU    *pstXccSmsOrigCallCnf;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec    = VOS_NULL_PTR;
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enCurMtState;

    enCurMtState            = TAF_XSMS_MtGetCurrFsmId();

    pstXccSmsOrigCallCnf    = (XCC_CSMS_ORIG_SMS_CALL_CNF_STRU *)pstMsg;

    if (TAF_XSMS_SEND_XCC_CALL_ID_MO != pstXccSmsOrigCallCnf->ucCallId)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf:Call Id error");

        return VOS_ERR;
    }

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    pstMoRec->ucIsOrigReqSendFlag       = VOS_FALSE;

    /* 如果当前的链路是MT所有，而且当前的原因值是已经在TCH，认为当期的原因值是失败的 */
    if ((TAF_XSMS_MT_IDLE_STATE                 != enCurMtState)
     && (TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH     == pstXccSmsOrigCallCnf->enRslt ))
    {
         TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf: already in tch but rcving sms.");

        pstXccSmsOrigCallCnf->enRslt = TAF_XCC_CAUSE_NO_SERVICE;
    }

    /* 停止定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF);

    switch (pstXccSmsOrigCallCnf->enRslt)
    {
        /* 呼叫发起成功等待SO协商 */
        case TAF_XCC_CAUSE_SUCCESS:
            /* 是XSMS建的 */
            pstMoRec->ucIsSmsOrigChannel = VOS_TRUE;

            pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;

            /* 设置状态机为等待SO协商完成 */
            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_SO_IND);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND,
                                TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND_MAX);

            break;

        /* 已经存在TCH信道，不需要再等待SO协商 */
        case TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH:

            /* 不是XSMS建的 */
            pstMoRec->ucIsSmsOrigChannel = VOS_FALSE;

            /* 将AT请求编码之后在专用信道上发送 */
            if (VOS_OK != TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, &pstMoRec->stDbm))
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf:TAF_XSMS_SndCasDschDataReq fail.");

                TAF_XSMS_MoIdleInit();

                return VOS_ERR;
            }

            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                                TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX);

            break;

        default:
            TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf:Redial Proc");

            /* 重拔处理 */
            TAF_XSMS_RcvXccOrigCallCnfRedialProc(pstMoRec, pstXccSmsOrigCallCnf);

            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXccCallCnfTimeOut_MoWaitXccCallCnf
 功能描述  : 收到定时器(等待XCC_CALL_CNF)超时消息的处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:XCC的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXccCallCnfTimeOut_MoWaitXccCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    pstMoRec->ucIsOrigReqSendFlag       = VOS_FALSE;

    if (pstMoRec->stNvResend.ucResendMax > pstMoRec->ucResendTimes)
    {

        /* 发送断链请求 */
        TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);

        /* 启动重连定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                            pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND);
    }
    /* 重试次数超限不再尝试，进入IDLE状态 */
    else
    {
        /* 上报AT发送失败 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        /* 拆链,初始化全局变量 */
        TAF_XSMS_MoIdleInit();
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf
 功能描述  : 收到定时器(等待重新建链)超时消息的处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:定时器的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec = VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 重连次数加1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf: cur resend time is", pstMoRec->ucResendTimes);

    if (VOS_FALSE == pstMoRec->ucIsOrigReqSendFlag)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf: orig_req has not send");

        /* 设置当前信道选择为专用信道 */
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;

        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd
 功能描述  : 收到CAS链路被释放的处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:定时器的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 建链重试次数加1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd: cur relink time is", pstMoRec->ucResendTimes);

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND);

    /* 超过重试次数 */
    if ((pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
     || (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN ==  pstMoRec->stNvResend.enXsmsChannelOption))
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd: no relink time left");

        /* 直接上报失败 返回IDLE态 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        TAF_XSMS_MoIdleInit();
    }
    else
    {
        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd
 功能描述  : 收到定时器(等待SO_IND)超时处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 建链重试次数加1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd: cur relink time is", pstMoRec->ucResendTimes);

    /* 超过重试次数 */
    if ((pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
     || (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN ==  pstMoRec->stNvResend.enXsmsChannelOption))
    {
        /* 直接上报失败 返回IDLE态 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        TAF_XSMS_MoIdleInit();
    }
    else
    {
        /* 如果当前是DSCH发送短信 */
        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND);

        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd
 功能描述  : 收到XCC SO_IND消息的处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:SERVICE_CONNECT_IND消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{

    XCC_CSMS_SERVICE_CONNECT_IND_STRU  *pstSoIndMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec    =  TAF_XSMS_MoGetRecAddr();
    pstSoIndMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU*)pstMsg;

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND);

    if ((TAF_CDMA_SO_6_SMS == pstSoIndMsg->enSo)
     || (TAF_CDMA_SO_14_RS2_SMS == pstSoIndMsg->enSo))

    {
        /* 发送短信 设置当前状态为等待AS_CNF */
        if (VOS_ERR == TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, &pstMoRec->stDbm))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd:TAF_XSMS_SndCasDschDataReq fail");

            TAF_XSMS_MoPrepareReturnToMoIdle();

            return VOS_ERR;
        }

        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

        /* 启动保护定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX);

    }
    else
    {
        /* 上报AT发送失败 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
        {
            /* 拆信道 */
            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
        }

        TAF_XSMS_MoIdleInit();

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvDschDataCnf_MoWaitAsCnf
 功能描述  : MO过程中在TAF_XSMS_MO_WAITING_AS_CNF状态下收到DSCH CNF消息的处理函数
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:接入层的CNF消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvDschDataCnf_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8                    enRslt;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU                         *pstCnfMsg;
    TAF_XSMS_MSG_MO_REC_STRU                               *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();
    pstCnfMsg = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;

    enRslt = pstCnfMsg->enRslt;

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* 数据发送成功 */
    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == enRslt)
    {
        if ((VOS_FALSE == pstMoRec->usIsTlAckNeed)
         && (TAF_XSMS_SMS_ORIGPID_STK == pstMoRec->enOrigPid))
        {
            /* 直接结束发送流程 ,不需要上报 */
            if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
            {
                /* 拆信道 */
                TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
            }

            /* 初始化回MO_IDLE状态 */
            TAF_XSMS_MoIdleInit();

        }
        else
        {
            /* 设置为等待TL_ACK的状态,启动18秒保护定时器 */
            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_TL_ACK);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK,
                                TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK_MAX);
        }
    }
    else
    {
        /* 根据错误原因值 (1.0 重新建立信道,重新发送 2.0 重新发送 3.0 还是直接放弃 回到MO_IDLE) */
        if (VOS_OK != TAF_XSMS_MoAsDataCnfErrProc(enRslt))
        {
            /* 上报AT发送失败 */
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

            if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
            {
                TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
            }

            TAF_XSMS_MoIdleInit();
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoAccessChanResendProc
 功能描述  : 在只使用公共信道下的MO过程中在TAF_XSMS_MO_WAITING_AS_CNF状态下收到CNF消息中结果为错误的处理
 输入参数  : enRslt:接入层返回的错误原因值
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoAccessChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 接入层返回公共信道数据太大，无法发送，不再尝试，返回IDLE状态 */
    if (CAS_CNAS_1X_DATA_CNF_RSLT_DBM_TOO_LARGE == enRslt)
    {
        TAF_XSMS_MoIdleInit();

        return VOS_ERR;
    }
    else
    {
        /* 延时重发 */
        pstMoRec->ucResendTimes++;

        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (4 * pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoTrafficChanResendProc
 功能描述  : 在只使用专用信道下的MO过程中在TAF_XSMS_MO_WAITING_AS_CNF状态下收到CNF消息中结果为错误的处理
 输入参数  : enRslt:接入层返回的错误原因值
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoTrafficChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 延时重发 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                        (pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoBothChanResendProc
 功能描述  : 在使用专用信道或公共信道下的MO过程中在TAF_XSMS_MO_WAITING_AS_CNF状态下收到CNF消息中结果为错误的处理
 输入参数  : enRslt:接入层返回的错误原因值
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoBothChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 当前是在公共信道上发送，不管何原因发起呼叫建立信道 */
    if (TAF_XSMS_ACTIVE_CSCH == pstMoRec->enActiveSndChannel)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                            TAF_XSMS_HUNDRED_MILLISECS);

        /* 设置状态机为等待XCC的CNF消息 */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF);
    }
    /* 当前已经在专用信道上不再发起呼叫，重发数据 */
    else
    {
        /* 延时重发 */
        pstMoRec->ucResendTimes++;

        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoAsDataCnfErrProc
 功能描述  : MO过程中在TAF_XSMS_MO_WAITING_AS_CNF状态下收到DSCH CNF消息中结果为错误的处理
 输入参数  : enRslt:接入层返回的错误原因值
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoAsDataCnfErrProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT32                          ulRslt;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 重试最大次数已到最大值，拆链,初始化,直接回到MO_IDLE */
    if (pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MoAsDataCnfErrProc: ucResendTimes >= stNvResend.ucResendMax");

        return VOS_ERR;
    }

    /* 根据错误原因值 判断是重建,是重发 还是直接放弃回到MO_IDLE (拆链) */
    switch (pstMoRec->stNvResend.enXsmsChannelOption)
    {
        case TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN:
            ulRslt = TAF_XSMS_MoTrafficChanResendProc(enRslt);
            break;

        case TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN:
            ulRslt = TAF_XSMS_MoAccessChanResendProc(enRslt);
            break;

        case TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH:
            ulRslt =TAF_XSMS_MoBothChanResendProc(enRslt);
            break;

        /* 不可能走到的流程 */
        default:
            return VOS_ERR;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvAsCnfTimeout_MoWaitAsCnf
 功能描述  : MO过程中等待接入层回复定时器超时处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:等待接入层的CNF的超时消息
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvAsCnfTimeout_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    if (TAF_XSMS_ACTIVE_CSCH == pstMoRec->enActiveSndChannel)
    {
        TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
    }

    /* 如果没有超过最大重试次数 */
    if (pstMoRec->stNvResend.ucResendMax > pstMoRec->ucResendTimes)
    {
        /* 延时重发 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));

        pstMoRec->ucResendTimes++;

        /* 保持当前状态不变 */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);
    }
    else
    {
        /* 上报AT发送失败 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
        {
            /* 拆信道 */
            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
        }

        /* 返回MO_IDLE */
        TAF_XSMS_MoIdleInit();
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf
 功能描述  : MO过程中给接入层重发数据定时器超时的处理函数
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:延时发送的超时消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT8                           aucData[3];

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    PS_MEM_SET(aucData, 0, sizeof(aucData));


    /* 选择重发信道信道，重新发送DATA_REQ */
    if (TAF_XSMS_ACTIVE_DSCH == pstMoRec->enActiveSndChannel)
    {
        if (VOS_ERR == TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, &pstMoRec->stDbm))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf: TAF_XSMS_SndCasDschDataReq fail");

            TAF_XSMS_MoIdleInit();

            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf: TAF_XSMS_SndCasDschDataReq fails");

            return VOS_ERR;
        }

        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX);

        /* 设置当前状态为TAF_XSMS_MO_WAITING_AS_CNF */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);
    }
    else
    {
        TAF_XSMS_SndCasCschReq_MoWaitCasCnf();

        /* 需要返回OK ,不管CSCH REQ 发送成功还是失败 */
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvCschDataCnf_MoWaitAsCnf
 功能描述  : 收到CSCH_DATA_CNF消息的处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:CSCH_DATA_CNF 消息
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvCschDataCnf_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8                    enRslt;
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU                         *pstCnfMsg;
    TAF_XSMS_MSG_MO_REC_STRU                               *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    pstCnfMsg = (CAS_CNAS_1X_CSCH_DATA_CNF_STRU *)pstMsg;

    enRslt = pstCnfMsg->enRslt;

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* 数据发送成功 */
    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == enRslt)
    {
        if ((VOS_FALSE == pstMoRec->usIsTlAckNeed)
         && (TAF_XSMS_SMS_ORIGPID_STK == pstMoRec->enOrigPid))
        {
            /* 直接结束发送流程 ,不需要上报 */
            /* 初始化回MO_IDLE状态 */
            TAF_XSMS_MoIdleInit();

        }
        else
        {
            /* 设置为等待TL_ACK的状态,启动保护定时器 */
            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_TL_ACK);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK,
                                TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK_MAX);
        }

    }
    else
    {
        /* 根据错误原因值 (1.0 重新建立信道,重新发送 2.0 重新发送 3.0 还是直接放弃 回到MO_IDLE) */
        if (VOS_OK != TAF_XSMS_MoAsDataCnfErrProc(enRslt))
        {
            /* 上报AT发送失败 */
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

            TAF_XSMS_MoIdleInit();
        }
    }

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvDschTlACK_MoWaitTlACK
 功能描述  : 收到DSCH的TL ACK处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:DATA_IND消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvDschTlACK_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstDschDataInd;
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTlAck;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstDschDataInd = (TAF_XSMS_CAS_DATA_IND_MSG_STRU *)pstMsg;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    PS_MEM_SET(&stTlAck, 0, sizeof(TAF_XSMS_TRANSPORT_MESSAGE_STRU));

    /* 通过解码接口将TL ACK变成TL STRU */
    if (VOS_ERR == TAF_XSMS_DecodeTLRawToTLStru(pstDschDataInd->ucLen, pstDschDataInd->aucMsg, &stTlAck))
    {
        /* 解码错误 */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvDschTlACK_MoWaitTlACK:TAF_XSMS_DecodeTLRawToTLStru fail");

        return VOS_ERR;
    }


    TAF_XSMS_INFO_LOG1(" In MO TL_ACK the seq num is", stTlAck.stCauseCode.ucReplySeq);

    TAF_XSMS_HookSmsTlAck(TAF_XSMS_HOOK_MSG_TYPE_RCV_TL_ACK, &stTlAck.stCauseCode);

    if (stTlAck.stCauseCode.ucReplySeq != (pstMoRec->ucReplySeq - 1))
    {
        /* 不是对应的TL_ACK */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvDschTlACK_MoWaitTlACK:Reply Seq not match");

        return VOS_ERR;
    }

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* 如果不是短信建链，直接上报成功或者失败
    如果是短信建链，等待链路释放之后才能直接上报短信发送结果 */
    if (VOS_FALSE == pstMoRec->ucIsSmsOrigChannel)
    {
        if ( TAF_XSMS_TL_CAUSECODE_NONE == stTlAck.stCauseCode.enErrorClass)
        {
            /* 如果成功，上报发送成功 */
            TAF_XSMS_MsgSubmitSuccInd((VOS_UINT32)(pstMoRec->usMessageId));
        }
        else
        {
            /* 如果失败，上报短信发送失败*/
            TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)(stTlAck.stCauseCode.enCauseCode));

        }
    }
    else
    {
        /* 存储CAUSE CODE */
        PS_MEM_CPY(&pstMoRec->stCauseCode, &stTlAck.stCauseCode, sizeof(TAF_XSMS_CAUSE_CODE_STRU));
    }

    /* 判断是否是SMS建立的信道，如果是，拆信道 */
    TAF_XSMS_MoPrepareReturnToMoIdle();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvCschTlACK_MoWaitTlACK
 功能描述  : 收到CSCH的TL ACK处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:DATA_IND消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvCschTlACK_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstCschDataInd;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTlAck;

    pstCschDataInd = (TAF_XSMS_CAS_DATA_IND_MSG_STRU *)pstMsg;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    PS_MEM_SET(&stTlAck, 0, sizeof(stTlAck));

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* 通过解码接口将TL ACK变成TL STRU */
    (VOS_VOID)TAF_XSMS_DecodeTLRawToTLStru(pstCschDataInd->ucLen, pstCschDataInd->aucMsg, &stTlAck);

    TAF_XSMS_INFO_LOG1(" In MO TL_ACK the seq num is", stTlAck.stCauseCode.ucReplySeq);

    TAF_XSMS_HookSmsTlAck(TAF_XSMS_HOOK_MSG_TYPE_RCV_TL_ACK, &stTlAck.stCauseCode);

    if (stTlAck.stCauseCode.ucReplySeq != (pstMoRec->ucReplySeq - 1))
    {
        /* log 打印TL_ACK SEQ NUM 不匹配 */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvCschTlACK_MoWaitTlACK: SEQ_NUM mot match");

        return VOS_ERR;
    }

    if (TAF_XSMS_TL_CAUSECODE_NONE == stTlAck.stCauseCode.enErrorClass)
    {
        /* 如果成功，上报发送成功 */
        TAF_XSMS_MsgSubmitSuccInd((VOS_UINT32)(pstMoRec->usMessageId));
    }
    else
    {
        /* 如果失败，上报短信发送失败 */
        TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)(stTlAck.stCauseCode.enCauseCode));
    }

    /* 返回MO_IDLE */
    TAF_XSMS_MoIdleInit();

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK
 功能描述  : 等待CAS的TL ACK超时处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg: 等待TL_ACK超时的消息
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU stXsmsMoTlAckTimeOutCfg;
    VOS_UINT8                           ucIsTlAckNeed;

    PS_MEM_SET(&stXsmsMoTlAckTimeOutCfg, 0, sizeof(TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU));

    pstMoRec        = TAF_XSMS_MoGetRecAddr();
    ucIsTlAckNeed   = VOS_TRUE;

    TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK: wait tl_ack timeout,ap should resend");

    /* 读取配置的NV */
    if (VOS_OK != NV_Read(en_NV_Item_1X_SMS_MO_TL_ACK_TIME_OUT_CFG, &stXsmsMoTlAckTimeOutCfg, sizeof(TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU)))
    {
        /* CS0015要求 TL_ACK */
        stXsmsMoTlAckTimeOutCfg.ucIsCfgEnable       =  VOS_FALSE;
        stXsmsMoTlAckTimeOutCfg.enTlAckNeedLevel    =  TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NEEDED;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK: NV_Read error ");
    }

    /* NV使能 且 不需要TL_ACK
       NV使能 且 当收发对冲时不需要TL_ACK 且收发对冲时 TL_ACK 超时的时候，直接上报成功*/
    if ((VOS_TRUE == stXsmsMoTlAckTimeOutCfg.ucIsCfgEnable)
    &&  (TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NOT_NEEDED == stXsmsMoTlAckTimeOutCfg.enTlAckNeedLevel))
    {
        ucIsTlAckNeed   = VOS_FALSE;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK: wait tl_ack timeout, but not need,so succ");
    }

    if ((VOS_TRUE == stXsmsMoTlAckTimeOutCfg.ucIsCfgEnable)
    &&  (TAF_XSMS_TL_ACK_NEED_LEVEL_NOT_NEEDED_WHEN_RCV_SMS == stXsmsMoTlAckTimeOutCfg.enTlAckNeedLevel)
    &&  (VOS_TRUE == pstMoRec->ucIsRcvSmsWhenSndSms))
    {
        ucIsTlAckNeed                   = VOS_FALSE;
        pstMoRec->ucIsRcvSmsWhenSndSms  = VOS_FALSE;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK: wait tl_ack timeout, rcving sms,so succ");
    }

    /* 上报AT 等待TLACK 超时 */
    if ((TAF_XSMS_ACTIVE_CSCH == pstMoRec->enActiveSndChannel)
     ||((TAF_XSMS_ACTIVE_DSCH == pstMoRec->enActiveSndChannel)
     && (VOS_FALSE == pstMoRec->ucIsSmsOrigChannel)))
    {
        if (VOS_TRUE == ucIsTlAckNeed)
        {
            TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)TAF_XSMS_TL_NO_ACK);
        }
        else
        {
            TAF_XSMS_MsgSubmitSuccInd(pstMoRec->usMessageId);
        }
    }
    else
    {
        if (VOS_TRUE == ucIsTlAckNeed)
        {
            pstMoRec->stCauseCode.enCauseCode   = TAF_XSMS_TL_NO_ACK;
            pstMoRec->stCauseCode.enErrorClass  = TAF_XSMS_TL_CAUSECODE_TMP;
        }
        else
        {
            pstMoRec->stCauseCode.enCauseCode   = TAF_XSMS_TL_CAUSECODE_NONE;
        }
    }

    /* 拆链回到MO_IDLE */
    TAF_XSMS_MoPrepareReturnToMoIdle();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvEndCallCnf_MoWaitEndCallCnf
 功能描述  : 等待拆信道的结果处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:拆信道结果
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvEndCallCnf_MoWaitEndCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL);

    /* 设置当前状态为等待LINK ABORT */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND);

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT,
                        TI_TAF_XSMS_TIMER_MO_WAIT_LINK_ABORT_MAX);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort
 功能描述  : 等待链路断开处理
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:拆信道结果
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec  = TAF_XSMS_MoGetRecAddr();

    /* 停掉定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL);

    /* 上报成功或者失败 */
    if ( TAF_XSMS_TL_CAUSECODE_NONE == pstMoRec->stCauseCode.enErrorClass)
    {
        /* 如果成功，上报发送成功 */
        TAF_XSMS_MsgSubmitSuccInd((VOS_UINT32)(pstMoRec->usMessageId));
    }
    else
    {
        /* 如果失败，上报短信发送失败*/
        TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)(pstMoRec->stCauseCode.enCauseCode));

    }

    /* 不论成功失败，都回到MT_IDLE状态 */
    TAF_XSMS_MoIdleInit();

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvEndCallCnfTimeout_MoWaitEndCallCnf
 功能描述  : 等待拆信道的结果定时器超时处理函数
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:等待XCC断链的确认的超时消息
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvEndCallCnfTimeout_MoWaitEndCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    /* 设置当前状态为等待LINK ABORT */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND);

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT,
                        TI_TAF_XSMS_TIMER_MO_WAIT_LINK_ABORT_MAX);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MoPrepareReturnToMoIdle
 功能描述  : 返回MO IDLE状态的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MoPrepareReturnToMoIdle(VOS_VOID)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec        = TAF_XSMS_MoGetRecAddr();

    /* 判断是否是SMS建立的信道，如果是，拆信道 */
    if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
    {
        /* 拆信道 */
        TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);

        /* 设置定时器为等待XCC挂断呼叫的CNF */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF);

        /* 起定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL,
                            TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL_MAX);
    }
    else
    {
        /*不拆信道，初始化回MO_IDLE状态 */
        TAF_XSMS_MoIdleInit();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvMmaServiceStatus_MoWaitXccOrigCallCnf
 功能描述  : 收到OHM完成的处理机制
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvMmaServiceStatus_MoWaitXccOrigCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MMA_XSMS_SERVICE_STATUS_IND_STRU   *pMmaXsmsStatusInd;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec            =   TAF_XSMS_MoGetRecAddr();
    pMmaXsmsStatusInd   =  (MMA_XSMS_SERVICE_STATUS_IND_STRU*)pstMsg;

    /* 如果正在等待重定向完成而且重定向之后的介入技术为1X或者混合模式 */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == pMmaXsmsStatusInd->enRatType)
    &&  (VOS_TRUE == pstMoRec->ucWaitRedirCompleteFlag)
    &&  (VOS_FALSE == pstMoRec->ucIsOrigReqSendFlag))
    {
        pstMoRec->ucWaitRedirCompleteFlag   = VOS_FALSE;

        /* 直接发起建链流程 */
        TAF_XSMS_SndXccSmsOrgiCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO,
                                      pstMoRec->ucIsL2ErrReOrig,
                                      pstMoRec->ucL2ErrReOrigCount);

        /* 启动定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF_MAX);

        /* 设置状态机为等待XCC的CNF消息 */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF);
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf
 功能描述  : 等待接入层CNF的时候收到断链的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec    =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* 链路断了需要停掉等待CNF的定时器，和重发的定时器 */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_RESEND);

    /* 建链重试次数加1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf: cur relink time is", pstMoRec->ucResendTimes);

    /* 超过重试次数 */
    if (pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
    {
        /* 直接上报失败 返回IDLE态 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        TAF_XSMS_MoIdleInit();
    }
    else if (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN ==  pstMoRec->stNvResend.enXsmsChannelOption)
    {
        TAF_XSMS_SndCasCschReq_MoWaitCasCnf();
    }
    else
    {
        /* 如果当前是DSCH发送短信 */
        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SendXccOrigReq_MoWaitOrigCnf
 功能描述  : MO 发送ORIG_REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf
(
    VOS_VOID
)
{
    TAF_XSMS_MSG_MO_REC_STRU                *pstMoRec;
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8     enCasState;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8        enCsServiceStatus;
    VOS_UINT8                                ucCsCallExistFlg;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /*判断当前起定时器次数是否达到最大次数*/
    if (pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
    {
        /* 上报AT发送失败 */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        /* 拆链,初始化全局变量 */
        TAF_XSMS_MoIdleInit();

        return;
    }

    enCsServiceStatus  = TAF_SDC_GetCsServiceStatus();
    enCasState         = TAF_SDC_GetCdmaCurUeState();
    ucCsCallExistFlg   = TAF_SDC_GetCsCallExistFlg();

    if ( (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
       && ((VOS_TRUE !=  ucCsCallExistFlg) || (TAF_SDC_1X_UE_MAIN_STATUS_TCH_STATE == enCasState)))
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf: normal service snd xcc orig_req");

        /* 给XCC发起呼叫 */
        TAF_XSMS_SndXccSmsOrgiCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO,
                                      pstMoRec->ucIsL2ErrReOrig,
                                      pstMoRec->ucL2ErrReOrigCount);

        /* 启动定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF_MAX);

    }
    else
    {
        /* 启动重新链接定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                            pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND);

        TAF_XSMS_ERROR_LOG("TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf: TAF_SDC_GetCsServiceStatus not normal service");
        TAF_XSMS_ERROR_LOG("TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf: Start XSMS relink timer");

    }

    /* 设置状态机为等待 */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SndCasCschReq_MoWaitCasCnf
 功能描述  : MO 发送 CSCH_DATA_REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : C00299064
    修改内容   : 新生成函数
  2.日    期   : 2016年01月19日
    作    者   : C00299064
    修改内容   : 正在收短信的时候 不发送短信
*****************************************************************************/
VOS_VOID TAF_XSMS_SndCasCschReq_MoWaitCasCnf
(
    VOS_VOID
)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT8                           aucData[3];
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCurService;
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enCurMtState;

    enCurMtState        = TAF_XSMS_MtGetCurrFsmId();

    pstMoRec            = TAF_XSMS_MoGetRecAddr();
    enCurService        =  TAF_SDC_GetCsServiceStatus();

    PS_MEM_SET(aucData, 0, 3);
    TAF_XSMS_EncodeAuth(&pstMoRec->st1xSms.stAddr, aucData);

    if ((TAF_XSMS_MT_IDLE_STATE                 == enCurMtState)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE  == enCurService))
    {
        /* 将数据发给CAS */
        TAF_XSMS_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
        if (VOS_ERR == TAF_XSMS_SndCasCschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, aucData, &(pstMoRec->stDbm)))
        {
            TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
            TAF_XSMS_MoIdleInit();

            TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasCschReq_MoWaitCasCnf: TAF_XSMS_SndCasCschDataReq fail");

            return ;
        }

        /* 启动定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_CSCH_CNF_MAX);

    }
    else
    {
        /* 启动4S定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (4 * pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));

        TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasCschReq_MoWaitCasCnf:  unnormal service or rcving sms");
    }

    /* 设置状态机为等待接入层回复 */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck
 功能描述  : 等待TL_ACK的时候收到断链的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月29日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck: do nothing,should wait for 18s and AP resend");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvXcallDataReq_MoIdle
 功能描述  : MO Idle状态下收到XCALL下发的命令发送短信的处理流程
 输入参数  : ulEventType:事件类型(由Sendpid和msg type组成)
             pstMsg:MTA的消息内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXcallDataReq_MoIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XSMS_KMC_MSG_SEND_REQ_STRU   *pstSendReq;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    pstSendReq  = (XCALL_XSMS_KMC_MSG_SEND_REQ_STRU*)pstMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(stXsmsMsg));

    /* MO 记录全局变量 */
    pstMoRec    = TAF_XSMS_MoGetRecAddr();
    pstDbm      = &(pstMoRec->stDbm);

    /* INIT CTRL 记录全局变量 */
    pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 将XCALL消息转换成标准的短信结构体 */
    TAF_XSMS_GetKmcDefaultAddress(&stXsmsMsg.stAddr);

    if (VOS_ERR == TAF_XSMS_EncodeXcallMsgBearDataByContext(pstSendReq->aucData,
                                                            pstSendReq->usDataLen,
                                                            &stXsmsMsg))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXcallDataReq_MoIdle: encode msg fail");
        return VOS_ERR;
    }

    stXsmsMsg.ulTeleserviceID = TAF_XSMS_TELESERVICE_CDMACMT;

    /* 将XCALL下发的STRU保存到全局变量中(FDN,CC可能会用) */
    PS_MEM_CPY(&pstMoRec->st1xSms, &stXsmsMsg, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstMoRec->enOrigPid         = TAF_XSMS_SMS_ORIGPID_XCALL;
    pstMoRec->usOpId            = pstSendReq->usOpId;
    pstMoRec->usIsTlAckNeed     = VOS_TRUE;

    /* 将现在的MSG_ID写到MO_REC全局变量中 */
    pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;

    ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);
    /* 将xcall下发的数据转换成DBM存在全局变量中 */
    if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&stXsmsMsg,
                                           pstMoRec->usMessageId,
                                           ucReqSeq,
                                           TAF_XSMS_STATUS_STO_UNSEND,
                                           pstDbm,
                                           VOS_TRUE))
    {
        /* 保持MO_IDLE */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXcallDataReq_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

        return VOS_ERR;
    }

    TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &stXsmsMsg);

    /* 将MSG_ID写回卡中 (需要决定是这时候写还是等到TL_ACK再写) */
    TAF_XSMS_MoIncreaseMessageId();

    return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);


}

/*****************************************************************************
 函 数 名  : TAF_XSMS_RcvSendPoolMsgReq_MoIdle
 功能描述  : MO Idle状态下收到等待发送文件池内发送短信的处理流程
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvSendPoolMsgReq_MoIdle(VOS_VOID)
{

    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    VOS_UINT8                           ucReqSeq = 0;

    /* MO 记录全局变量 */
    pstMoRec    = TAF_XSMS_MoGetRecAddr();
    pstDbm      = &(pstMoRec->stDbm);

    /* INIT CTRL 记录全局变量 */
    pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

    TAF_XSMS_GetRecFromMoSendPool(&pstMoRec->enOrigPid,
                                  &pstMoRec->usIsTlAckNeed,
                                  &pstMoRec->usOpId,
                                  &pstMoRec->st1xSms);

    /* 将现在的MSG_ID写到MO_REC全局变量中 */
    pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;
    ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);

    /* 将AT下发的数据转换成DBM存在全局变量中 */
    if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstMoRec->st1xSms,
                                           pstMoRec->usMessageId,
                                           ucReqSeq,
                                           TAF_XSMS_STATUS_STO_UNSEND,
                                           pstDbm,
                                           pstMoRec->usIsTlAckNeed))
    {
        /* 保持MO_IDLE */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvSendPoolMsgTimerOut_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

        return VOS_ERR;
    }

    TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &pstMoRec->st1xSms);

    /* 将MSG_ID写回卡中 (需要决定是这时候写还是等到TL_ACK再写) */
    TAF_XSMS_MoIncreaseMessageId();

    return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);

}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



