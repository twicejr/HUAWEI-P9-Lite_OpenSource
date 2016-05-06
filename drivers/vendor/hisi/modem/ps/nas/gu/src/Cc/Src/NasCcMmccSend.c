/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcMmccSend.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年10月17日
  最近修改   : 2007年10月17日
  功能描述   : 发送MMCC原语
  函数列表   :
  修改历史   :
  1.日    期   : 2007年10月17日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcInclude.h"
#include  "NasOmInterface.h"
/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
#include "NasCcEntityMgmt.h"
/* Added by n00355355 for 呼叫重建, 2015-9-17, end */


/* delete by z00234330 for PCLINT??àí, 2014-06-24, begin */
/* delete by z00234330 for PCLINT??àí, 2014-06-24, end */


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_MMCCSEND_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*NAS上行空口消息ID和上报给OM的消息ID对应表*/
NAS_CC_OTA_MSG_ID_STRU    g_astNasOtaMsgIdM2N[] = {

    {NAS_CC_MSG_CONNECT_ACK,      NAS_OTA_MSG_CC_CONNECT_ACK_UP},
    {NAS_CC_MSG_DISCONNECT,       NAS_OTA_MSG_CC_DISCONNECT_UP},
    {NAS_CC_MSG_RELEASE,          NAS_OTA_MSG_CC_RELEASE_UP},
    {NAS_CC_MSG_RELEASE_COMPLETE, NAS_OTA_MSG_CC_RELEASE_COMPLETE_UP},
    {NAS_CC_MSG_START_DTMF,       NAS_OTA_MSG_CC_START_DTMF},
    {NAS_CC_MSG_STOP_DTMF,        NAS_OTA_MSG_CC_STOP_DTMF},
    {NAS_CC_MSG_STATUS,           NAS_OTA_MSG_CC_STATUS_UP},
    {NAS_CC_MSG_CALL_CNF,         NAS_OTA_MSG_CC_CALL_CONFIRM},
    {NAS_CC_MSG_SETUP,            NAS_OTA_MSG_CC_SETUP_UP},
    {NAS_CC_MSG_EMERGENCY_SETUP,  NAS_OTA_MSG_CC_EMERGENCY_UP},
    {NAS_CC_MSG_ALERTING,         NAS_OTA_MSG_CC_ALERTING_UP},
    {NAS_CC_MSG_CONNECT,          NAS_OTA_MSG_CC_CONNECT_UP},
    {NAS_CC_MSG_FACILITY,         NAS_OTA_MSG_CC_FACILITY_UP},
    {NAS_CC_MSG_HOLD,             NAS_OTA_MSG_CC_HOLD},
    {NAS_CC_MSG_RETRIEVE,         NAS_OTA_MSG_CC_RETREIVE},
    {NAS_CC_MSG_MODIFY,           NAS_OTA_MSG_CC_MODIFY_UP},
    {NAS_CC_MSG_MODIFY_COMPLETE,  NAS_OTA_MSG_CC_MODIFY_COMPLETE_UP},
    {NAS_CC_MSG_MODIFY_REJ,       NAS_OTA_MSG_CC_MODIFY_REJ_UP},
    {NAS_CC_MSG_CC_EST_CNF,       NAS_OTA_MSG_CC_CCBS_EST_CNF},

};

/*lint -save -e958 */

/*****************************************************************************
  2 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_CC_AllocMmccPrim
 功能描述  : 申请MMCC原语消息
 输入参数  : ulMsgName  - 消息名称
              ulMsgLen   - 消息长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID * NAS_CC_AllocMmccPrim(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulMsgLen
)
{
    MSG_HEADER_STRU * pstMsg =
        (MSG_HEADER_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_CC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_CC_ERR_LOG("NAS_CC_AllocMmccPrim: Failed to alloc VOS message.");
        return VOS_NULL_PTR;
    }

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid = WUEPS_PID_CC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid = WUEPS_PID_MM;

    pstMsg->ulMsgName = ulMsgName;

    return pstMsg;
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccPrim
 功能描述  : 发送MMCC原语消息
 输入参数  : pMsg  - 需要发送的消息指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_SendMmccPrim(
    VOS_VOID                            *pMsg
)
{
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_CC, "NAS_CC_SendMmccPrim():WARNING:SEND MSG FIAL");
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccAbortReq
 功能描述  : 发送MMCC_ABORT_REQ原语
 输入参数  : ucTi - Transaction ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccAbortReq(
    VOS_UINT8                           ucTi
)
{
    MMCC_ABORT_REQ_STRU * pstMsg =
        (MMCC_ABORT_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_ABORT_REQ, sizeof(MMCC_ABORT_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    NAS_CC_SendMmccPrim(pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccRelReq
 功能描述  : 发送MMCC_REL_REQ原语
 输入参数  : ucTi      - Transaction ID
              ulRelType - 释放的类型(MMCC_RELEASE_ALL/MMCC_RELEASE_SPECIFIC)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccRelReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulRelType
)
{
    MMCC_REL_REQ_STRU * pstMsg =
        (MMCC_REL_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_REL_REQ, sizeof(MMCC_REL_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->ulReleaseType = ulRelType;

    NAS_CC_SendMmccPrim(pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccEstReq
 功能描述  : 发送MMCC_EST_REQ原语
 输入参数  : ucTi       - Transaction ID
              ulCallType - 呼叫的类型(紧急呼叫/普通呼叫)
              ulPriority - 呼叫的优先级
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加当前电话模式，可视电话或语音电话
  3.日    期   : 2015年8月13日
    作    者   : s00217060
    修改内容   : User_Exp_Improve修改:函数增加入参ucRedialFlg

*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccEstReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulCallType,
    VOS_UINT32                          ulCallMode,
    VOS_UINT32                          ulPriority,
    VOS_UINT8                           ucRedialFlg
)
{
    MMCC_EST_REQ_STRU * pstMsg =
        (MMCC_EST_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_EST_REQ, sizeof(MMCC_EST_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->ulCallType  = ulCallType;
    pstMsg->ulCallPri   = ulPriority;
    pstMsg->ulCallMode  = ulCallMode;
    pstMsg->ucRedialFlg = ucRedialFlg;

    NAS_CC_SendMmccPrim(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_ReportM2NOtaMsg
 功能描述  : 对trace中勾取CC的空口消息
 输入参数  : pNasMsg - 消息内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月13日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_ReportM2NOtaMsg(
    CC_MSG_STRU                         *pNasMsg
)
{
    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT32                          i;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;
    NAS_CC_NORM_LOG1("NAS_CC_ReportM2NOtaMsg:NORMAL: msg id is", pNasMsg->aucCcMsg[1]);

    /*在NAS上行空口消息ID和上报给OM的消息ID对应表查找该消息是否需要通过OM进行勾取显示*/
    for (i = 0; i < (sizeof(g_astNasOtaMsgIdM2N) / sizeof(NAS_CC_OTA_MSG_ID_STRU)); i++)
    {
        if (g_astNasOtaMsgIdM2N[i].enCcMsgId == pNasMsg->aucCcMsg[1])
        {
            enNasOtaMsyId = g_astNasOtaMsgIdM2N[i].enOtaMsgId;
            break;
        }
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
        NAS_CC_WARN_LOG1("NAS_CC_ReportM2NOtaMsg:WARNING: invalid msg id is ",enNasOtaMsyId);
        /*不属于CC模块的空口消息，不在trace中显示*/
        return;
    }

    /*上报空口消息给OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_CC, enNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulCcMsgSize + 4, (VOS_UINT8*)pNasMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccDataReq
 功能描述  : 发送MMCC_DATA_REQ原语
 输入参数  : ucTi        - Transaction ID
              pucCcMsg    - 原语中携带的CC消息
              ulCcMsgSize - CC消息的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年03月13日
    作    者   : z00214637
    修改内容   : Delete M2

*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccDataReq(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
)
{
    MMCC_DATA_REQ_STRU * pstMsg =
        (MMCC_DATA_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_DATA_REQ, (sizeof(MMCC_DATA_REQ_STRU) - 4) + ulCcMsgSize);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    if (0 == ulCcMsgSize)
    {
        NAS_CC_WARN_LOG("NAS_CC_SendMmccDataReq: NAS_CC_SendMmccDataReq is 0");
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->SendCcMsg.ulCcMsgSize = ulCcMsgSize;
    PS_MEM_CPY(pstMsg->SendCcMsg.aucCcMsg, pucCcMsg, ulCcMsgSize);

    /*通过OM钩取CC空口消息*/
    NAS_CC_ReportM2NOtaMsg(&pstMsg->SendCcMsg);


    NAS_CC_SendMmccPrim(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccPromptRej
 功能描述  : 发送MMCC_PROMPT_REJ原语
 输入参数  : ulCause - 拒绝的原因
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccPromptRej(
    VOS_UINT32                          ulCause
)
{
    MMCC_PROMPT_REJ_STRU * pstMsg =
        (MMCC_PROMPT_REJ_STRU *)NAS_CC_AllocMmccPrim(MMCC_PROMPT_REJ, sizeof(MMCC_PROMPT_REJ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulRefuseCause = ulCause;

    NAS_CC_SendMmccPrim(pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccReestReq
 功能描述  : 发送MMCC_REEST_REQ原语
 输入参数  : ucTi - Transaction ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccReestReq(
    VOS_UINT8                           ucTi
)
{
    MMCC_REEST_REQ_STRU * pstMsg =
        (MMCC_REEST_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_REEST_REQ, sizeof(MMCC_REEST_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    NAS_CC_SendMmccPrim(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccStartCc
 功能描述  : 发送MMCC_START_CC原语
 输入参数  : ucTi      - Transaction ID
             pucCcMsg  - 原语中携带的CC消息
             ulCcMsgSize - CC消息的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccStartCc(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
)
{
    MMCC_DATA_REQ_STRU* pstMsg =
        (MMCC_DATA_REQ_STRU*)NAS_CC_AllocMmccPrim(MMCC_START_CC,
                                                  sizeof(MMCC_DATA_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->SendCcMsg.ulCcMsgSize = ulCcMsgSize;
    PS_MEM_CPY(pstMsg->SendCcMsg.aucCcMsg, pucCcMsg, ulCcMsgSize);

    NAS_CC_SendMmccPrim(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccCallStatusNty
 功能描述  : 发送MMCC_CALL_STATUS_NTY原语
 输入参数  : enCallStatus: 呼叫建立状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
)
{
    MMCC_CALL_STATUS_NTF_STRU   *pstMsg =
        (MMCC_CALL_STATUS_NTF_STRU*)NAS_CC_AllocMmccPrim(MMCC_CALL_STATUS_NTY,
                                                  sizeof(MMCC_CALL_STATUS_NTF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->enCallStatus    = enCallStatus;

    NAS_CC_SendMmccPrim(pstMsg);

    return;
}


/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccCallInfoCnf
 功能描述  : 发送MMCC_GET_CALL_INFO_CNF原语
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月17日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_SendMmccCallInfoCnf(
    MMCC_CALL_INFO_STRU                *pstCallInfo
)
{
    MMCC_GET_CALL_INFO_CNF_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMCC_GET_CALL_INFO_CNF_STRU *)NAS_CC_AllocMmccPrim(MMCC_GET_CALL_INFO_CNF,
                                                                 sizeof(MMCC_GET_CALL_INFO_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_SendMmccCallInfoCnf():ERROR:Alloc Msg fail");
        return;
    }

   PS_MEM_CPY(pstMsg->astCallInfo, pstCallInfo, NAS_CC_MAX_ENTITY_NUM);

   NAS_CC_SendMmccPrim(pstMsg);

   return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetCallInfo
 功能描述  : 获取Get Call Info的API接口
 输入参数  : MMCC_CALL_INFO_STRU                *pstCallInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月18日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_GetCallInfo(
    MMCC_CALL_INFO_STRU                *pstCallInfo
)
{
    VOS_UINT32                          ucIndex;

    for (ucIndex = 0; ucIndex < NAS_CC_MAX_ENTITY_NUM; ucIndex++)
    {
        if ( VOS_TRUE == NAS_CC_IsSpecCallEntityInUse(ucIndex) )
        {
            pstCallInfo[ucIndex].enCallState  = NAS_CC_GetCallState(ucIndex);
            pstCallInfo[ucIndex].enCallType   = NAS_CC_GetCallType(ucIndex);
            pstCallInfo[ucIndex].ucCallId     = NAS_CC_GetCallId(ucIndex);
            pstCallInfo[ucIndex].ucTi         = NAS_CC_GetEntityTi(ucIndex);
        }
        else
        {
           pstCallInfo[ucIndex].enCallState   = NAS_CC_CALL_STATE_BUTT;
           pstCallInfo[ucIndex].enCallType    = NAS_CC_CALL_TYPE_BUTT;
           pstCallInfo[ucIndex].ucCallId      = NAS_CC_INVALID_CALL_ID;
           pstCallInfo[ucIndex].ucTi          = NAS_CC_INVALID_TI_VALUE;
        }
    }

    return;
}
/* Added by n00355355 for 呼叫重建, 2015-9-17, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccSrvccCallInfoNtf
 功能描述  : 发送MMCC_SRVCC_CALL_INFO_NOTIFY原语
 输入参数  : ucSyncTiNum-----同步过来的TI个数
             pucSyncTi-------同步过来的TI值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013-10-10
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccSrvccCallInfoNtf(
    VOS_UINT8                           ucSyncTiNum,
    VOS_UINT8                          *pucSyncTi
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTi;

    MMCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstMsg =
        (MMCC_SRVCC_CALL_INFO_NOTIFY_STRU*)NAS_CC_AllocMmccPrim(MMCC_SRVCC_CALL_INFO_NOTIFY,
                                                  sizeof(MMCC_SRVCC_CALL_INFO_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    for (i= 0 ; i< ucSyncTiNum; i++)
    {
        ucTi = pucSyncTi[i];

        /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
        pstMsg->aucTransactionId[i] = ucTi ^ 0x08;
    }

    pstMsg->ucTiNum = ucSyncTiNum;

    NAS_CC_SendMmccPrim(pstMsg);
}
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccBeginSessionNotify
 功能描述  : 发送MMCC_BEGIN_SESSION_NOTIFY原语
 输入参数  : enSessionType:Session类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-6-16
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccBeginSessionNotify(
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType
)
{
    MMCC_BEGIN_SESSION_NOTIFY_STRU     *pstBeginSessionNotify = VOS_NULL_PTR;

    pstBeginSessionNotify =
        (MMCC_BEGIN_SESSION_NOTIFY_STRU*)NAS_CC_AllocMmccPrim(MMCC_BEGIN_SESSION_NOTIFY,
                                                  sizeof(MMCC_BEGIN_SESSION_NOTIFY_STRU));


    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    pstBeginSessionNotify->enSessionType = enSessionType;

    NAS_CC_SendMmccPrim(pstBeginSessionNotify);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccEndSessionNotify
 功能描述  : 发送MMCC_END_SESSION_NOTIFY原语
 输入参数  : enSessionType:Session类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-6-16
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccEndSessionNotify(
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType
)
{
    MMCC_END_SESSION_NOTIFY_STRU       *pstEndSessionNotify = VOS_NULL_PTR;

    pstEndSessionNotify =
        (MMCC_END_SESSION_NOTIFY_STRU*)NAS_CC_AllocMmccPrim(MMCC_END_SESSION_NOTIFY,
                                                  sizeof(MMCC_END_SESSION_NOTIFY_STRU));


    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    pstEndSessionNotify->enSessionType = enSessionType;

    NAS_CC_SendMmccPrim(pstEndSessionNotify);

    return;
}
#endif

/*lint -restore */



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

