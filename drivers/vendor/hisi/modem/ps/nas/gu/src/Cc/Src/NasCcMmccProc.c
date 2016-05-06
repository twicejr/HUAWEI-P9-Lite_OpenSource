/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcMmccProc.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月31日
  最近修改   : 2007年8月31日
  功能描述   : 接收和处理来自MM的MMCC原语
  函数列表   : NAS_CC_ProcMmccDataInd
                NAS_CC_ProcMmccErrInd
                NAS_CC_ProcMmccEstCnf
                NAS_CC_ProcMmccEstInd
                NAS_CC_ProcMmccPrimitive
                NAS_CC_ProcMmccPromptInd
                NAS_CC_ProcMmccReestCnf
                NAS_CC_ProcMmccRelInd
                NAS_CC_ProcMmccSyncInd
  修改历史   :
  1.日    期   : 2007年8月31日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年6月25日
    作    者   :  l00130025
    修改内容   : 问题单号：AT2D03940
  3.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
  4.日    期   : 2008年9月10日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D05028,启动呼叫重建定时器T303
  5.日    期   : 2008年10月20日
    作    者   : h44270
    修改内容   : 问题单号:A32D14153,来电时，用户尚未接听电话就打开了声码器,，AMR速率变换没有上报
  6.日    期   : 2010年1月26日
    作    者   : s46746
    修改内容   : 问题单号:AT2D16340被叫未接听，可以听到对方语音，原因是传送到
                 NAS_CC_SetTchStatus第二个参数填写不正确

  7.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcInclude.h"

#include "MnCall.h"
#include "NasCcCtx.h"
#include "NasCcProcNvim.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_MMCC_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
#define NAS_CC_AIRMSG_TYPE_MASK         0X3f

/*NAS下行空口消息ID和上报给OM的消息ID对应表*/
NAS_CC_OTA_MSG_ID_STRU    g_astNasOtaMsgIdN2M[] = {

    {NAS_CC_MSG_ALERTING,         NAS_OTA_MSG_CC_ALERTING_DOWN},
    {NAS_CC_MSG_CALL_PROC,        NAS_OTA_MSG_CC_CALL_PROCEEDING},
    {NAS_CC_MSG_PROGRESS,         NAS_OTA_MSG_CC_PROGRESS},
    {NAS_CC_MSG_SETUP,            NAS_OTA_MSG_CC_SETUP_DOWN},
    {NAS_CC_MSG_RELEASE,          NAS_OTA_MSG_CC_RELEASE_DOWN},
    {NAS_CC_MSG_RELEASE_COMPLETE, NAS_OTA_MSG_CC_RELEASE_COMPLETE_DOWN},
    {NAS_CC_MSG_CONNECT,          NAS_OTA_MSG_CC_CONNECT_DOWN},
    {NAS_CC_MSG_CONNECT_ACK,      NAS_OTA_MSG_CC_CONNECT_ACK_DOWN},
    {NAS_CC_MSG_DISCONNECT,       NAS_OTA_MSG_CC_DISCONNECT_DOWN},
    {NAS_CC_MSG_NOTIFY,           NAS_OTA_MSG_CC_NOTIFY},
    {NAS_CC_MSG_HOLD_ACK,         NAS_OTA_MSG_CC_HOLD_ACK},
    {NAS_CC_MSG_HOLD_REJ,         NAS_OTA_MSG_CC_HOLD_REJ},
    {NAS_CC_MSG_RETRIEVE_ACK,     NAS_OTA_MSG_CC_RETREIVE_ACK},
    {NAS_CC_MSG_RETRIEVE_REJ,     NAS_OTA_MSG_CC_RETREIVE_REJ},
    {NAS_CC_MSG_MODIFY,           NAS_OTA_MSG_CC_MODIFY_DOWN},
    {NAS_CC_MSG_MODIFY_COMPLETE,  NAS_OTA_MSG_CC_MODIFY_COMPLETE_DOWN},
    {NAS_CC_MSG_MODIFY_REJ,       NAS_OTA_MSG_CC_MODIFY_REJ_DOWN},
    {NAS_CC_MSG_FACILITY,         NAS_OTA_MSG_CC_FACILITY_DOWN},
    {NAS_CC_MSG_START_DTMF_ACK,   NAS_OTA_MSG_CC_START_DTMF_ACK},
    {NAS_CC_MSG_START_DTMF_REJ,   NAS_OTA_MSG_CC_START_DTMF_REJ},
    {NAS_CC_MSG_STOP_DTMF_ACK,    NAS_OTA_MSG_CC_STOP_DTMF_ACK},
    {NAS_CC_MSG_STATUS_ENQUIRY,   NAS_OTA_MSG_CC_STATUS_ENQUIRY},
    {NAS_CC_MSG_STATUS,           NAS_OTA_MSG_CC_STATUS_DOWN},
    {NAS_CC_MSG_CC_EST,           NAS_OTA_MSG_CC_CCBS_ESTABLISHMENT},
    {NAS_CC_MSG_RECALL,           NAS_OTA_MSG_CC_CCBS_RECALL},

};

/*lint -save -e958 */

/*****************************************************************************
  2 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CC_ReportN2MOtaMsg
 功能描述  : 勾取CC的空口消息发给OM
 输入参数  : pNasMsg   - CC空口消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月13日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_ReportN2MOtaMsg(
    CC_MSG_STRU                         *pNasMsg
)
{

    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          i;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    /* Message Type字段在消息中的所在位置 */
    ucMsgType = pNasMsg->aucCcMsg[1] & NAS_CC_AIRMSG_TYPE_MASK;

    NAS_CC_NORM_LOG1("NAS_CC_ReportN2MOtaMsg:NORMAL: msg type is ",pNasMsg->aucCcMsg[1]);

    /*在NAS下行空口消息ID和上报给OM的消息ID对应表中查找该消息是否需要通过OM进行勾取显示*/
    for (i = 0; i < (sizeof(g_astNasOtaMsgIdN2M)/sizeof(NAS_CC_OTA_MSG_ID_STRU)); i++)
    {
        if (g_astNasOtaMsgIdN2M[i].enCcMsgId == ucMsgType)
        {
            enNasOtaMsyId = g_astNasOtaMsgIdN2M[i].enOtaMsgId;
            break;
        }
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
          NAS_CC_WARN_LOG1("NAS_CC_ReportN2MOtaMsg:WARNING: invalid msg type!",enNasOtaMsyId);
          /*不属于CC模块的空口消息，不在trace中显示*/
          return;
    }

    /*上报空口消息给OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_CC, enNasOtaMsyId,
                       NAS_OTA_DIRECTION_DOWN, pNasMsg->ulCcMsgSize + 4, (VOS_UINT8 *)pNasMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccEstCnf
 功能描述  : 处理MMCC_EST_CNF原语
             注意: 需要MM同步修改，只发一次MMCC_EST_CNF
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccEstCnf(
    const VOS_VOID                      *pMsg
)
{
    NAS_CC_CALL_STATE_ENUM_U8 enCallState;
    NAS_CC_ENTITY_ID_T entityId;
    MMCC_EST_CNF_STRU * pstEstCnf = (MMCC_EST_CNF_STRU *)pMsg;
    VOS_UINT8  ucTi = (VOS_UINT8)pstEstCnf->ulTransactionId;

    ucTi ^= 0x08;
    entityId = NAS_CC_GetEntityByTi(ucTi);
    NAS_CC_ASSERT(entityId != NAS_CC_INVALID_ENTITY_ID);

    enCallState = NAS_CC_GetCallState(entityId);

    if (NAS_CC_CALL_STATE_U0_1 == enCallState)
    {
        NAS_CC_SendMmccDataReq(ucTi,
                               g_stNasCcBufferedSetupMsg.aucBuf,
                               g_stNasCcBufferedSetupMsg.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMmccEstCnf: ChangeCallState to U1.");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U1);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMmccEstCnf: Bad state.", enCallState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccEstInd
 功能描述  : 处理MMCC_EST_IND原语
             注意: 需要MM同步修改，只发一次MMCC_EST_CNF
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2009年9月126日
    作    者   : s62952
    修改内容  : AT2D14145
  3.日    期   : 2013年03月13日
    作    者   : z00214637
    修改内容   : Delete M2
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccEstInd(
    const VOS_VOID                      *pMsg
)
{
    MMCC_EST_IND_STRU * pstEstInd = (MMCC_EST_IND_STRU *)pMsg;


    NAS_CC_ProcAirMsg(pstEstInd->FisrtCcMsg.aucCcMsg,
                      pstEstInd->FisrtCcMsg.ulCcMsgSize);

    /*通过om钩取CC空口消息*/
    NAS_CC_ReportN2MOtaMsg(&pstEstInd->FisrtCcMsg);

}



/*****************************************************************************
 函 数 名  : NAS_CC_LocalAbortDtmf
 功能描述  : 通知MN DTMF操作结果
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年07月02日
    作    者   : 梁金广 65478
    修改内容   : 新生成函数，问题单号:AT2D04057
  2.日    期   : 2013年2月18日
    作    者   : z00161729
    修改内容   : DTS2013021803962:start dtmf rej后如果收到stop dtmf请求无需跟网络交互直接回复stop dtmf cnf
*****************************************************************************/
VOS_VOID NAS_CC_LocalAbortDtmf(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCause;
    NAS_CC_DTMF_STATE_ENUM              enDtmfState;

    /* 如果当前存在DTMF过程，需要通知MN DTMF的结果 */
    enDtmfState = NAS_CC_GetDtmfState(entityId);
    if (NAS_CC_DTMF_S_START_REQ == enDtmfState)
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T336);

        enCause = NAS_CC_CAUSE_111;
        NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &enCause, sizeof(enCause));

        NAS_CC_INFO_LOG("NAS_CC_ProcMmccRelInd: ChangeDtmfState to IDLE");

        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_START_REJ);
    }
    else if (NAS_CC_DTMF_S_STOP_REQ == enDtmfState)
    {
        NAS_CC_StopTimer(entityId, TI_NAS_CC_T337);

        /* stop dtmf操作即使出错也认为操作成功了，仅输出一个告警 */
        NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
        NAS_CC_WARN_LOG("radio link is aborted.");

        NAS_CC_INFO_LOG("NAS_CC_ProcMmccRelInd: ChangeDtmfState IDLE");
        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_IDLE);
    }
    else
    {
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ConvertMmccRelCauseToMnccCause
 功能描述  : 将NAS_MMCM_REL_CAUSE_ENUM_UINT32转换为 NAS_CC_CAUSE_VALUE_ENUM_U8中对应原因值
 输入参数  : enMmccRelCause - mmcc之间rel cause值
 输出参数  : enCcCause      - mncc之间cause值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   :2013年9月14日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
*****************************************************************************/
VOS_VOID NAS_CC_ConvertMmccRelCauseToMnccCause(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmccRelCause,
    NAS_CC_CAUSE_VALUE_ENUM_U32         *penCcCause
)
{
    /* 目前MMCC与MNCC之间的偏移完全一致，直接赋值过来，后续如果有偏移不一致的地方，需要单独转换 */

    *penCcCause = enMmccRelCause;


    return;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccRelInd
 功能描述  : 处理MMCC_REL_IND原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  5.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  6.日    期   : 2014年5月31日
    作    者   : z00161729
    修改内容   : DTS2014060402388:一路active呼叫，一路hold的mpty呼叫，at+chld=1过程中丢网所有呼叫都被释放后call状态异常挂死，hold mpty呼叫无法恢复
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccRelInd(
    const VOS_VOID                      *pMsg
)
{
    MMCC_REL_IND_STRU                  *pstRelInd;
    VOS_UINT8                           ucTi;
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;

    NAS_CC_CAUSE_VALUE_ENUM_U32         enCcCause;

    NAS_CC_ENTITY_ID_T                  entityId;

    pstRelInd   = (MMCC_REL_IND_STRU *)pMsg;
    ucTi        = (VOS_UINT8)(pstRelInd->ulTransactionId ^ 0x08);
    /* 这个地方加一个显示转换，避免以后修改代码两边错误原因值偏移不一致 */
    NAS_CC_ConvertMmccRelCauseToMnccCause((NAS_MMCM_REL_CAUSE_ENUM_UINT32)pstRelInd->ulRelCause,
                                          &enCcCause);


    entityId = NAS_CC_GetEntityByTi(ucTi);
    NAS_CC_ASSERT(entityId != NAS_CC_INVALID_ENTITY_ID);

    enCallState = NAS_CC_GetCallState(entityId);

    if (enCallState != NAS_CC_CALL_STATE_U0)
    {
        /* 通知MN DTMF操作的结果,并清空缓存的DTMF消息 */
        NAS_CC_LocalAbortDtmf(entityId);
        NAS_CC_FlushDTMFBuff(entityId);

        NAS_CC_DetachUserConn(entityId);

        NAS_CC_StopLocalAlertInd();

        /* 将NAS_MMCM_REL_CAUSE_ENUM_UINT32转换为NAS_CC_CAUSE_VALUE_ENUM_U8中对应原因值 */
        /* 删除NAS_CC_ConvertMmccRelCauseToMnccCause((NAS_MMCM_REL_CAUSE_ENUM_UINT32)pstRelInd->ulRelCause,
                                              &enCcCause);*/

        NAS_CC_StopAllTimer(entityId);

        NAS_CC_INFO_LOG("NAS_CC_ProcMmccRelInd: ChangeCallState to U0.");

        /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
        NAS_CC_ProcSsSwitchCallRelease(entityId);
        /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

        NAS_CC_SendMnccMsg(entityId, MNCC_REJ_IND, &enCcCause, sizeof(enCcCause));


        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
    else
    {
        NAS_CC_INFO_LOG("NAS_CC_ProcMmccRelInd: Bad state.");
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccDataInd
 功能描述  : 处理MMCC_DATA_IND原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年03月13日
    作    者   : z00214637
    修改内容   : Delete M2

*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccDataInd(
    const VOS_VOID                      *pMsg
)
{
    MMCC_DATA_IND_STRU * pstDataInd = (MMCC_DATA_IND_STRU *)pMsg;

    /*通过om钩取CC空口消息*/
    NAS_CC_ReportN2MOtaMsg(&pstDataInd->RcvCcMsg);


    NAS_CC_ProcAirMsg(pstDataInd->RcvCcMsg.aucCcMsg,
                      pstDataInd->RcvCcMsg.ulCcMsgSize);

}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccSyncInd
 功能描述  : 处理MMCC_SYNC_IND原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年1月26日
    作    者   : s46746
    修改内容   : 被叫未接听，可以听到对方语音，原因是传送到NAS_CC_SetTchStatus第
                 二个参数填写不正确
  3.日    期   : 2014年12月22日
    作    者   : b00269685
    修改内容   : ultra flash新增缓存机制
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccSyncInd(
    const VOS_VOID                      *pMsg
)
{
    VOS_UINT8                   i;
    VOS_UINT32                  ulResult;
    MMCC_SYNC_IND_STRU         *pstSyncInd  = VOS_NULL_PTR;

    for(i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if(NAS_CC_CALL_STATE_U0 != NAS_CC_GetCallState(i))
        {
            if(NAS_CC_CALL_STATE_U27 > NAS_CC_GetCallState(i))
            {
                break;
            }
        }
    }

    pstSyncInd  = (MMCC_SYNC_IND_STRU *)pMsg;
    if(i == NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_CC_WARN_LOG("NAS_CC_ProcMmccSyncInd no call is active");

        /* 只对不是rab release的sync ind进行缓存，否则在外场测试时发现有可能会挂断被叫 */
        if (MMCC_WCDMA_RAB_RELEASED != pstSyncInd->enSyncReason)
        {
            NAS_CC_SaveCacheMsg(NAS_BuildEventType(WUEPS_PID_MM, MMCC_SYNC_IND), (VOS_VOID *)pMsg);
        }

        return;
    }

    /* NAS_CC_SetTchStatus */
    ulResult = NAS_CC_SetTchStatus(pstSyncInd, i);
    if(VOS_ERR == ulResult)
    {
        NAS_CC_WARN_LOG("NAS_CC_ProcMmccSyncInd parameters are wrong");
        return;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccReestCnf
 功能描述  : 处理MMCC_REEST_CNF原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccReestCnf(
    const VOS_VOID                      *pMsg
)
{
    MMCC_REEST_CNF_STRU         *pReestMsg;
    VOS_UINT8                   ucTi;
    NAS_CC_ENTITY_ID_T          entityId;

    pReestMsg   = (MMCC_REEST_CNF_STRU *)pMsg;
    ucTi        = (VOS_UINT8)(pReestMsg->ulTransactionId ^ 0x08);
    entityId    = NAS_CC_GetEntityByTi(ucTi);
    if (MMCC_REEST_SUCCESS == pReestMsg->ulResult)
    {
        NAS_CC_INFO_LOG("NAS_CC_ProcMmccReestCnf: MM connect re-establishment is successful.");
        NAS_CC_SendBufferedDtmfReq(entityId);
    }
    else
    {
        /* 通知MN DTMF操作的结果,并清空缓存的DTMF消息 */
        NAS_CC_LocalAbortDtmf(entityId);
        NAS_CC_FlushDTMFBuff(entityId);

        NAS_CC_DetachUserConn(pReestMsg->ulTransactionId);

        NAS_CC_StopLocalAlertInd();

        NAS_CC_SendMnccMsg(entityId, MNCC_REJ_IND, VOS_NULL_PTR, 0);

        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        NAS_CC_StopAllTimer(entityId);
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
        NAS_CC_INFO_LOG("NAS_CC_ProcMmccReestCnf: ChangeCallState to U0.");
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccErrInd
 功能描述  : 处理MMCC_ERR_IND原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年6月25日
    作    者   :  l00130025
    修改内容   : 问题单号：AT2D03940
  3.日    期   : 2008年7月12日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D04057
  4.日    期   : 2008年9月10日
    作    者   : 黎客来 00130025
    修改内容   : 问题单号:AT2D05028,启动呼叫重建定时器T303
  5.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  6.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  7.日    期   : 2013年04月12日
    作    者   : f62575
    修改内容   : DTS2013041503184,解决3G下RADIO LINK FAILURE没有按协议要求输出近端释放事件问题
                 仅在呼叫重建失败后上报给UICC，此处删除MNCC_RADIO_LINK_FAILURE消息上报
  8.日    期   : 2014年9月24日
    作    者   : s00217060
    修改内容   : for cs_err_log
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccErrInd(
    const VOS_VOID                      *pMsg
)
{
    /*
    [3GPP 24.008 5.5.4.2 Reaction of call control]
    a) Re-establishment not required
        If the call is in the call establishment or call clearing phase, i.e.
        any state other than the "active" state or the "mobile originating modify"
        state, call control shall release the MM connection
    b) Re-establishment required
        If the call is in the "active" state or "mobile originating modify" state,
        the indication from MM that reestablishment is possible shall cause call
        control to request re-establishment from the MM connection, suspend any
        further message to be sent and await the completion of the re-establishment
        procedure.
    */
    MMCC_ERR_IND_STRU * pstErrInd = (MMCC_ERR_IND_STRU *)pMsg;
    VOS_UINT8  ucTi = (VOS_UINT8)(pstErrInd->ulTransactionId ^ 0x08);
    NAS_CC_CALL_STATE_ENUM_U8  enState;

    NAS_CC_ENTITY_ID_T entityId = NAS_CC_GetEntityByTi(ucTi);

    NAS_CC_CAUSE_VALUE_ENUM_U32          enCcCause;

    NAS_CC_ASSERT(entityId != NAS_CC_INVALID_ENTITY_ID);

    enState = NAS_CC_GetCallState(entityId);

    if ((NAS_CC_CALL_STATE_U10 == enState)
     || (NAS_CC_CALL_STATE_U26 == enState))
    {
    /* 如果当前存在DTMF过程，需要通知MN DTMF的结果，在重建结束后，需要处理
       缓存的DTMF消息 */
        NAS_CC_LocalAbortDtmf(entityId);

        NAS_CC_StopTimer(entityId, TI_NAS_CC_RABMINACT_PROTECT);

        NAS_CC_SendMmccReestReq(ucTi);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);
    }
    else
    {
        /* 通知MN DTMF操作的结果,并清空缓存的DTMF消息 */
        NAS_CC_LocalAbortDtmf(entityId);
        NAS_CC_FlushDTMFBuff(entityId);

        NAS_CC_DetachUserConn(entityId);

        NAS_CC_StopLocalAlertInd();

        NAS_CC_ConvertMmccRelCauseToMnccCause(pstErrInd->enCause, &enCcCause);
        NAS_CC_SendMnccMsg(entityId, MNCC_REJ_IND, &enCcCause, sizeof(enCcCause));

        NAS_CC_StopAllTimer(entityId);
        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
        NAS_CC_INFO_LOG("NAS_CC_ProcMmccErrInd: ChangeCallState to U0.");
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccPromptInd
 功能描述  : 处理MMCC_PROMPT_IND原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccPromptInd(
    const VOS_VOID                      *pMsg
)
{
    NAS_CC_ENTITY_ID_T                   entityId;
    VOS_UINT8                            ucTi;

    /*选择mo TI,创建实体*/
    if (NAS_CC_CreateEntity(NAS_CC_CALL_TYPE_MT_NORMAL_CALL, 0, NAS_CC_INVALID_TI_VALUE, &entityId) != VOS_OK)
    {
        NAS_CC_ERR_LOG("NAS_CC_ProcMmccPromptInd: Fail to create entity.");
        /*发送cm service prompt reject消息，cause:Service option temporarily out of order*/
        NAS_CC_SendMmccPromptRej(NAS_CC_CAUSE_34);
        return;
    }
    ucTi = NAS_CC_GetEntityTi(entityId);

    /*不发给taf，直接回start cc消息给网侧,只封装了头，没有封装cc capability*/
    NAS_CC_SendMmccStartCcReq(ucTi);
    NAS_CC_StartTimer(entityId, TI_NAS_CC_T332, 0);
    NAS_CC_NORM_LOG( "  CC State = CC_S_WAIT_FOR_NW_INFO  " );
    /* 状态迁移到CC_S_WAIT_FOR_NW_INFO             */
    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_3);

}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccEmcNumInd
 功能描述  : 处理MMCC_EMC_NUM_LST_IND原语，告知紧急呼号码
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年5月15日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年06月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  3.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccEmcNumListInd(
    const VOS_VOID                     *pMsg
)
{
    MMCC_EMERGENCY_LIST_STRU           *pstEmerNumInd = VOS_NULL_PTR;
    MNCC_EMERGENCY_LIST_IND_STRU        stMnccEmcLIstInd;
    MsgBlock                           *pstTmpMsg = VOS_NULL_PTR;
    MNCC_IND_PRIM_MSG_STRU             *pstMsg    = VOS_NULL_PTR;
    VOS_UINT32                          i;

    PS_MEM_SET(&stMnccEmcLIstInd, 0, sizeof(MNCC_EMERGENCY_LIST_IND_STRU));

    pstEmerNumInd           = (MMCC_EMERGENCY_LIST_STRU *)pMsg;

    stMnccEmcLIstInd.ulMcc  = pstEmerNumInd->ulMcc;

    if (pstEmerNumInd->ucEmergencyNumber > MNCC_EMERGENCY_MAX_LIST)
    {
        stMnccEmcLIstInd.ucEmergencyNumber = MNCC_EMERGENCY_MAX_LIST;
    }
    else
    {
        stMnccEmcLIstInd.ucEmergencyNumber = pstEmerNumInd->ucEmergencyNumber;
    }

    /* 将紧急呼号码保存在全局变量中 */
    for (i = 0; i < stMnccEmcLIstInd.ucEmergencyNumber; i++)
    {
        stMnccEmcLIstInd.astEmergencyLists[i].ucCategoryValue = pstEmerNumInd->astEmergencyLists[i].ucCategoryValue;
        stMnccEmcLIstInd.astEmergencyLists[i].ucEmcNumLen     = pstEmerNumInd->astEmergencyLists[i].ucEmcNumLen;

        (VOS_VOID)VOS_MemCpy(&stMnccEmcLIstInd.astEmergencyLists[i].aucEmergencyNum[0],
                   &pstEmerNumInd->astEmergencyLists[i].aucEmergencyList[0],
                   pstEmerNumInd->astEmergencyLists[i].ucEmcNumLen);
    }

    /* 申请VOS消息 */
    pstTmpMsg = PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_CC, (sizeof(MNCC_IND_PRIM_MSG_STRU) - sizeof(MNCC_IND_PARAM_UNION)) + sizeof(pstMsg->unParam));
    if (VOS_NULL_PTR == pstTmpMsg)
    {
        NAS_CC_ERR_LOG("NAS_CC_ProcMmccEmcNumListInd: Failed to alloc VOS message.");
        return;
    }

    /* 填写VOS消息头 */
    pstMsg                  = (MNCC_IND_PRIM_MSG_STRU*)pstTmpMsg;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_CC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;

    /* 填写原语首部 */
    pstMsg->enPrimName      = MNCC_EMERGENCY_LIST_IND;

    pstMsg->ulParamLen      = sizeof(MNCC_EMERGENCY_LIST_IND_STRU);
    PS_MEM_SET(&(pstMsg->unParam), 0, sizeof(pstMsg->unParam));

    PS_MEM_CPY(&(pstMsg->unParam.stEmcListInd), &stMnccEmcLIstInd, sizeof(MNCC_EMERGENCY_LIST_IND_STRU));

    /* 发送VOS消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_CC, "NAS_CC_ProcMmccEmcNumListInd():WARNING:SEND MSG FIAL");
    }
}

/*****************************************************************************
 函 数 名  : Nas_CC_ProcMmccGetCallInfoReq
 功能描述  : 处理MMCC_GET_CALL_INFO_REQ原语
 输入参数  : const VOS_VOID                      *pMsg;
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月17日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Nas_CC_ProcMmccGetCallInfoReq(
    const VOS_VOID                      *pMsg
)
{
    MMCC_CALL_INFO_STRU                 astCallInfo[NAS_CC_MAX_ENTITY_NUM];
    VOS_UINT32                          ucIndex;

    for (ucIndex = 0; ucIndex < NAS_CC_MAX_ENTITY_NUM; ucIndex++)
    {
        if ( VOS_TRUE == NAS_CC_IsSpecCallEntityInUse(ucIndex) )
        {
           astCallInfo[ucIndex].enCallState = NAS_CC_GetCallState(ucIndex);
           astCallInfo[ucIndex].enCallType  = NAS_CC_GetCallType(ucIndex);
           astCallInfo[ucIndex].ucCallId    = NAS_CC_GetCallId(ucIndex);
           astCallInfo[ucIndex].ucTi        = NAS_CC_GetEntityTi(ucIndex);
        }
        else
        {
           astCallInfo[ucIndex].enCallState = NAS_CC_CALL_STATE_BUTT;
           astCallInfo[ucIndex].enCallType  = NAS_CC_CALL_TYPE_BUTT;
           astCallInfo[ucIndex].ucCallId    = NAS_CC_INVALID_CALL_ID;
           astCallInfo[ucIndex].ucTi        = NAS_CC_INVALID_TI_VALUE;
        }
    }

    NAS_CC_SendMmccCallInfoCnf(astCallInfo);

    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_CC_ProcSrvccSucc
 功能描述  : SRVCC成功的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ProcSrvccSucc(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucTi;
    NAS_CC_ENTITY_ID_T                  entityId;
    NAS_CC_BC_PARAMS_STRU               stParams;

    PS_MEM_SET(&stParams, 0, sizeof(NAS_CC_BC_PARAMS_STRU));

    for (i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        ucTi = NAS_CC_GetEntityTi(i);

        entityId = NAS_CC_GetEntityByTi(ucTi);

        NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_1, &stParams);

        NAS_CC_AttachUserConn(entityId, stParams.enItc);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccSrvccStatusInd
 功能描述  : 处理MMCC_SRVCC_STATUS_IND原语，告知SRVCC的状态
 输入参数  : pstSrvccStasNtfMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccSrvccStatusInd(
    MMCC_SRVCC_STATUS_IND_STRU         *pstSrvccStasInd
)
{
    NAS_MNCC_SRVCC_STATUS_ENUM_UINT32   enSrvccSta;

    switch (pstSrvccStasInd->enSrvccStatus)
    {
        case NAS_MMCC_SRVCC_STATUS_START:

            enSrvccSta = NAS_MNCC_SRVCC_STATUS_START;
            break;

        case NAS_MMCC_SRVCC_STATUS_FAIL:

            /* 销毁IMSA同步过来的CC实体信息 */
            NAS_CC_DeleteAllEntities();

            /* 清除TCH信道信息 */
            NAS_CC_SetTchAvailValue(VOS_FALSE);

            enSrvccSta = NAS_MNCC_SRVCC_STATUS_FAIL;
            break;

        case NAS_MMCC_SRVCC_STATUS_SUCCESS:

            enSrvccSta = NAS_MNCC_SRVCC_STATUS_SUCCESS;

            NAS_CC_ProcSrvccSucc();

            break;

        default:

            NAS_CC_ERR_LOG("NAS_CC_ProcMmccSrvccStatusInd: Unexpected Srvcc status.");
            return;
    }

    /* 通知CALL模块SRVCC过程状态消息 */
    NAS_CC_SendMnccSrvccStatusIndMsg(enSrvccSta);

    return;
}
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccPrimitive
 功能描述  : 接收和处理来自MM的MMCC原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月16日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2013年09月25日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseII 项目修改:增加MM通知的SRVCC过程状态处理
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccPrimitive(
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                    *pMsgHeader = (MSG_HEADER_STRU *)pMsg;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    NAS_CC_INFO_LOG1("NAS_CC_ProcMmccPrimitive: primitive:",
                        (VOS_INT32)(pMsgHeader->ulMsgName));
    switch (pMsgHeader->ulMsgName)
    {
    case MMCC_EST_CNF:
        NAS_CC_ProcMmccEstCnf(pMsg);
        break;

    case MMCC_REEST_CNF:
        NAS_CC_ProcMmccReestCnf(pMsg);
        break;

    case MMCC_EST_IND:
    /*PC回放导出全局变量使用*/
#ifndef __PS_WIN32_RECUR__
        NAS_CC_SndOutsideContextData();
#endif
        NAS_CC_ProcMmccEstInd(pMsg);
        break;

    case MMCC_DATA_IND:
        NAS_CC_ProcMmccDataInd(pMsg);
        break;

    case MMCC_SYNC_IND:
        NAS_CC_ProcMmccSyncInd(pMsg);
        break;

    case MMCC_ERR_IND:
        NAS_CC_ProcMmccErrInd(pMsg);
        break;

    case MMCC_REL_IND:
        NAS_CC_ProcMmccRelInd(pMsg);
        break;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
     case MMCC_PROMPT_IND:
         if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
         {
             NAS_CC_ProcMmccPromptInd(pMsg);
         }
         break;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */


    case MMCC_EMC_NUM_LST_IND:
        NAS_CC_ProcMmccEmcNumListInd(pMsg);
        break;

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
    case MMCC_SRVCC_STATUS_IND:
        NAS_CC_ProcMmccSrvccStatusInd((MMCC_SRVCC_STATUS_IND_STRU *)pMsg);
        break;
#endif
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

    /* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
    case MMCC_GET_CALL_INFO_REQ:
        Nas_CC_ProcMmccGetCallInfoReq((MMCC_GET_CALL_INFO_REQ_STRU *)pMsg);
        break;

    /* Added by n00355355 for 呼叫重建, 2015-9-17, end */

    case MMCC_RRC_CONN_REL_IND:
        NAS_CC_ProcMmccRrcConnRelInd(pMsg);
        break;

    default:
        NAS_CC_ERR_LOG1("NAS_CC_ProcMmccPrimitive: Unknown primitive",
                    (VOS_INT32)(pMsgHeader->ulMsgName));
        break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcGmmccPrimitive
 功能描述  : 接收和处理来自GMM的原语
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年5月15日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ProcGmmccPrimitive(
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU * pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch(pMsgHeader->ulMsgName)
    {
        case GMMCC_EMC_NUM_LST_IND:
            NAS_CC_ProcMmccEmcNumListInd(pMsg);
            break;

        default:
            break;
    }

}
/*****************************************************************************
 函 数 名  : NAS_CC_ProcMmccRrcConnRelInd
 功能描述  : 接收和处理来自MM的MMCC_RRC_CONN_REL_IND
 输入参数  : pMsg - MM发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月12日
    作    者   : j00174725
    修改内容   : DTS2015121001913
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMmccRrcConnRelInd(
    const VOS_VOID                      *pMsg
)
{
    /* 清除所有缓存 */
    NAS_CC_ClearAllCacheMsg();
}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

