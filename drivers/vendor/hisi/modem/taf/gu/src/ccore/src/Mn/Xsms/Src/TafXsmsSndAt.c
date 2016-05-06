/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsSndAt.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service) 给AT的回复处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXsmsSndAt.h"
#include "TafXsmsUimProc.h"
#include "TafXsmsCtx.h"
#include "MnClient.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXsmsSndXcall.h"




#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_SND_AT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgInitInd
 功能描述  : 1XSMS给AT的短信初始化完成指示上报函数
 输入参数  : ulTotalNum:短信的总记录数
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgInitInd(VOS_UINT32 ulTotalNum)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* 填充消息结构，广播上报 */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    stEvent.XSmsEvent.stInitInd.ulTotalNum = ulTotalNum;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_INIT_IND, &stEvent);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgSubmitCnf
 功能描述  : 1XSMS给AT的短信发送结果回复函数
 输入参数  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:短信的发送结果
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgSubmitCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulRslt
)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* 填充消息结构 */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_SEND_CNF, &stEvent);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SetAPFullCnf
 功能描述  : at 设置当前的AP 存储满回复函数
 输入参数  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:设置结果
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SetAPFullCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_XSMS_APP_AT_EVENT_INFO_STRU));

    /* 填充消息结构 */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_UIM_MEM_FULL_CNF, &stEvent);
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgWriteCnf
 功能描述  : 1XSMS给AT的短信写入结果回复函数
 输入参数  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:写入操作的结果
             ulIndex:写入的记录索引号
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgWriteCnf(VOS_UINT16 usClientId,  VOS_UINT8 ucOpId, VOS_UINT32 ulRslt, VOS_UINT32 ulIndex)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_CTRL_INFO_STRU            *pstAddr;

    pstAddr = TAF_XSMS_GetReqCtrlInfoAddr();

    /* 解锁API接口，清空全局变量 */
    PS_MEM_SET(pstAddr, 0, sizeof(TAF_XSMS_CTRL_INFO_STRU));

    /* 填充消息结构 */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    stEvent.XSmsEvent.stWriteCnf.ulIndex = ulIndex;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_WRITE_CNF, &stEvent);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgDeleteCnf
 功能描述  : 1XSMS给AT的短信删除结果回复函数
 输入参数  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:删除操作的结果
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgDeleteCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_CTRL_INFO_STRU            *pstAddr;

    pstAddr = TAF_XSMS_GetReqCtrlInfoAddr();

    /* 解锁API接口，清空全局变量 */
    PS_MEM_SET(pstAddr, 0, sizeof(TAF_XSMS_CTRL_INFO_STRU));

    /* 填充消息结构 */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_DELETE_CNF, &stEvent);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgSubmitFailInd
 功能描述  : 1XSMS给AT的短信发送成功指示上报函数
 输入参数  : ulMr:MESSAGE ID
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgSubmitSuccInd(VOS_UINT32 ulMr)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();
    /* STK 非user ack */
    if ((TAF_XSMS_SMS_ORIGPID_STK == pstMoRec->enOrigPid)
     && (VOS_TRUE == pstMoRec->usIsTlAckNeed))
    {
        /* 給STK上报短信成功 */
        return TAF_XSMS_SendStkRsltInd(VOS_TRUE, 0);
    }

    /* STK user ack and  XPDS */
    if ((VOS_TRUE != pstMoRec->usIsTlAckNeed)
     || (TAF_XSMS_SMS_ORIGPID_XPDS == pstMoRec->enOrigPid))
    {
        /* 现在对USER ACK消息不上报 */
        return VOS_OK;
    }

    /* XCALL */
    if (TAF_XSMS_SMS_ORIGPID_XCALL == pstMoRec->enOrigPid)
    {
        return TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_SUCC, pstMoRec->usOpId);
    }

    /* 填充消息结构，广播上报AT */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    stEvent.XSmsEvent.stSndSuccInd.ulMr = ulMr;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_SEND_SUCC_IND, &stEvent);

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgSubmitFailInd
 功能描述  : 1XSMS给AT的短信发送失败指示上报函数
 输入参数  : ulCourceCode:错误原因值
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgSubmitFailInd(VOS_UINT32 ulCourceCode)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    if ((TAF_XSMS_SMS_ORIGPID_STK == pstMoRec->enOrigPid)
    &&  (VOS_TRUE == pstMoRec->usIsTlAckNeed))
    {
        /* 給STK上报短信发送失败 */
        return TAF_XSMS_SendStkRsltInd(VOS_FALSE, ulCourceCode);
    }

    if ((TAF_XSMS_SMS_ORIGPID_STK == pstMoRec->enOrigPid)
      &&(VOS_TRUE != pstMoRec->usIsTlAckNeed))
    {
        /* 现在对USER ACK消息不上报 */
        return VOS_OK;
    }

    if (TAF_XSMS_SMS_ORIGPID_XPDS == pstMoRec->enOrigPid)
    {
        /* 现在对MTA消息不上报 */
        return VOS_OK;
    }

    /* XCALL */
    if (TAF_XSMS_SMS_ORIGPID_XCALL == pstMoRec->enOrigPid)
    {
        return TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_FAIL, pstMoRec->usOpId);
    }

    /* 填充消息结构，广播上报 AT*/
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    stEvent.XSmsEvent.stSndFailInd.ulCourseCode = ulCourceCode;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_SEND_FAIL_IND, &stEvent);

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgUimFullInd
 功能描述  : 1XSMS给AT的UIM卡满指示上报函数
 输入参数  : pstDeliveryMsg:收到的短信或短信状态上报
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgDeliveryInd(TAF_XSMS_MESSAGE_STRU *pstDeliveryMsg)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* 填充消息结构，广播上报 */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    TAF_XSMS_TranslatePlusToNum(&pstDeliveryMsg->stAddr);

    PS_MEM_CPY(&stEvent.XSmsEvent.stRcvInd.stRcvMsg, pstDeliveryMsg, sizeof(TAF_XSMS_MESSAGE_STRU));

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_RCV_IND, &stEvent);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgUimFullInd
 功能描述  : 1XSMS给AT的UIM卡满指示上报函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgUimFullInd(VOS_VOID)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* 填充消息结构，广播上报 */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_UIM_FULL_IND, &stEvent);
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgEventCallBack
 功能描述  : 1XSMS给AT的消息发送函数
 输入参数  : enEventType:事件类型
 输出参数  : pstEvent:事件内容
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SmsEventCallBack(
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32   enEventType,
    TAF_XSMS_APP_AT_EVENT_INFO_STRU    *pstEvent)
{
    TAF_XSMS_APP_AT_CNF_STRU          *pstMsg;

    pstMsg = (TAF_XSMS_APP_AT_CNF_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                       sizeof(TAF_XSMS_APP_AT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstEvent->usClientId = MN_GetRealClientId(pstEvent->usClientId, UEPS_PID_XSMS);

    PS_MEM_CPY((VOS_VOID*)&pstMsg->stXsmsAtEvent, pstEvent, sizeof(TAF_XSMS_APP_AT_EVENT_INFO_STRU));

    pstMsg->enEventType   = enEventType;
    pstMsg->ulReceiverPid = WUEPS_PID_AT;

    return VOS_SendMsg(UEPS_PID_XSMS, pstMsg);
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_SendStkRsltInd
 功能描述  : 1XSMS给AT的消息发送函数
 输入参数  : ulSendRslt:
             ulCauseCode
 输出参数  :
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月15日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SendStkRsltInd(
    VOS_UINT32                          ulSendRslt,
    VOS_UINT32                          ulCauseCode
)
{
    XSMS_STK_SEND_SMS_RSLT_IND_STRU    *pstSendRslt;

    pstSendRslt = (XSMS_STK_SEND_SMS_RSLT_IND_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                                 sizeof(XSMS_STK_SEND_SMS_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSendRslt)
    {
        return VOS_ERR;
    }

    pstSendRslt->ulReceiverPid = MAPS_STK_PID;

    pstSendRslt->enMsgId       = ID_XSMS_STK_SEND_SMS_RSLT_IND;
    pstSendRslt->ulIsUserAck   = VOS_FALSE;
    pstSendRslt->ulSendSucc    = ulSendRslt;
    pstSendRslt->ulCauseCode   = ulCauseCode;

    return VOS_SendMsg(UEPS_PID_XSMS, pstSendRslt);
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_StkMsgSubmitCnf
 功能描述  : 1XSMS给AT的消息发送函数
 输入参数  : ulSendRslt:
             ulCauseCode
 输出参数  :
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月15日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_StkMsgSubmitCnf(VOS_UINT32 ulRet)
{
    XSMS_STK_SEND_SMS_CNF_STRU    *pstSendCnf;

    pstSendCnf = (XSMS_STK_SEND_SMS_CNF_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                                 sizeof(XSMS_STK_SEND_SMS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSendCnf)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_StkMsgSubmitCnf:VOS_AllocMsg ERR");
        return;
    }

    pstSendCnf->ulReceiverPid = MAPS_STK_PID;

    pstSendCnf->enMsgId       = ID_XSMS_STK_SEND_SMS_CNF;
    pstSendCnf->ulIsUserAck   = VOS_FALSE;
    pstSendCnf->ulRet         = ulRet;

    PS_SEND_MSG(UEPS_PID_XSMS, pstSendCnf);

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SendStkCATPTMsg
 功能描述  : 1XSMS给AT的消息发送函数
 输入参数  : ulSendRslt:
             ulCauseCode
 输出参数  :
 返 回 值  : VOS_OK -- 发送成功
             VOS_ERR -- 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月15日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_SendStkCATPTMsg(
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucTpdu,
    TAF_XSMS_MESSAGE_STRU              *pst1XSms
)
{
    XSMS_STK_RCV_SMS_IND_STRU          *pstCatptMsg;

    pstCatptMsg = (XSMS_STK_RCV_SMS_IND_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                                 sizeof(XSMS_STK_RCV_SMS_IND_STRU) + ulLen - 4 - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCatptMsg)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_SendStkCATPTMsg:VOS_AllocMsg ERR");
        return;
    }

    pstCatptMsg->ulReceiverPid = MAPS_STK_PID;

    pstCatptMsg->enMsgId       = ID_XSMS_STK_RCV_SMS_IND;
    pstCatptMsg->ulTpduLen     = ulLen;

    PS_MEM_CPY(pstCatptMsg->aucTpduData , pucTpdu, ulLen);
    PS_MEM_CPY(&pstCatptMsg->st1XSms, pst1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

    PS_SEND_MSG(UEPS_PID_XSMS, pstCatptMsg);

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SendXpdsGpsSms
 功能描述  : 1XSMS给xpds的消息发送函数
 输入参数  : ulLen: 数据长度
             pucData: 数据首指针
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月15日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_SendXpdsGpsSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XSMS_XPDS_REV_IND_STRU         *pstRcvInd;
    /* 4是结构体已有的长度 */
    pstRcvInd    = (TAF_XSMS_XPDS_REV_IND_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                      sizeof(TAF_XSMS_XPDS_REV_IND_STRU) + ulLen - 4 - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRcvInd)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_SendXpdsGpsSms:VOS_AllocMsg ERR");
        return;
    }

    pstRcvInd->ulReceiverPid = UEPS_PID_XPDS;

    pstRcvInd->enMsgName     = ID_XSMS_XPDS_RCV_IND;
    pstRcvInd->usDataLen     = (VOS_UINT16)ulLen;

    PS_MEM_CPY(pstRcvInd->aucData, pucData, ulLen);
    PS_MEM_CPY(&pstRcvInd->stXsmsAddr, pstXsmsAddr, sizeof(TAF_XSMS_ADDR_STRU));

    PS_SEND_MSG(UEPS_PID_XSMS, pstRcvInd);

    return;

}



/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



