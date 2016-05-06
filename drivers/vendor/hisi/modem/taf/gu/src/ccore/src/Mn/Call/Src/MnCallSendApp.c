/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallSendApp.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年4月18日
  最近修改   : 2014年4月18日
  功能描述   : CALL模块发送消息给APP，即AT或STK
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月18日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallSendApp.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "TafSdcCtx.h"
#include "NasUsimmApi.h"
#include "TafInternalInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_SEND_APP_C
/*****************************************************************************
   2 函数实现
*****************************************************************************/

/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_CALL_SendCallOrigCnf
 功能描述  : MN_CALL_EVT_CALL_ORIG_CNF事件发送给AT
 输入参数  : usClientId     - 发起该请求的Client的ID或广播客户ID
             opId           - Operation ID, 标识本次操作
             callId         - 呼叫ID
             enCause        - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月09日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年01月23日
    作    者   : f62575
    修改内容   : DTS2014012106603: 临时响应MN_CALL_EVT_CALL_ORIG_CNF，
                 MN_CALL_EVT_SUPS_CMD_CNF
                 CLIENT id从广播ID修改为业务发起方 。
  3.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID TAF_CALL_SendCallOrigCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */   
    MN_CALL_MGMT_STRU                   stCallMgmt;                             /* 呼叫信息 */
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;    

    PS_MEM_SET(&stCallMgmt, 0, sizeof(MN_CALL_MGMT_STRU));

    if (VOS_ERR == MN_CALL_GetSpecificCallInfo(callId, &stCallMgmt))
    {
        /* 可能会存在还没分配callid就发现错误，需要给AT回复,
           此时需要构造stCallInfo,不能取实体中的stCallInfo */
        stCallMgmt.stCallInfo.clientId   = clientId;
        stCallMgmt.stCallInfo.opId       = opId;
        stCallMgmt.stCallInfo.enCause    = enCause;
    }
    else
    {
        /* 如果已经分配callid就取实体中的stCallInfo */        
        
        stCallMgmt.stCallInfo.clientId = clientId;
        stCallMgmt.stCallInfo.opId     = opId;
        stCallMgmt.stCallInfo.callId   = callId;
        stCallMgmt.stCallInfo.enCause  = enCause;

        /* 增加主动上报相关全局变量的值 */
        pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();        
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucCurcRptCfg,
                   pstCurcRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);

        pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucUnsolicitedRptCfg,
                   pstUnsolicitedRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);

        TAF_CALL_UpdateCallInfo(callId, &(stCallMgmt.stCallInfo));
    }
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

    /* 对所有注册了CS域呼叫事件回调函数的Client调用回调函数 */
    MN_SendClientEvent(clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CALL_ORIG_CNF,
                       &(stCallMgmt.stCallInfo));
}

/*****************************************************************************
 函 数 名  : TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf
 功能描述  : 当TAF给AT发送MN_CALL_EVT_SUPS_CMD_CNF事件时，更新呼叫实体的CallInfo
 输入参数  : usClientId     - 发起该请求的Client的ID或广播客户ID
             opId           - Operation ID, 标识本次操作
             callId         - 呼叫ID
             ulErrorCode    - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月16日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_MGMT_STRU                   stCallMgmt;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallMgmt, 0, sizeof(MN_CALL_MGMT_STRU));

    if (VOS_OK == MN_CALL_GetSpecificCallInfo(callId, &stCallMgmt))
    {
        stCallMgmt.stCallInfo.clientId = clientId;
        stCallMgmt.stCallInfo.opId     = opId;
        stCallMgmt.stCallInfo.callId   = callId;
        /* 1. 只有enCause值不是TAF_CS_CAUSE_SUCCESS，才更新CALL实体的原因值。*/
        if (enCause != TAF_CS_CAUSE_SUCCESS)
        {
            stCallMgmt.stCallInfo.enCause  = enCause;
        }

        /* 增加主动上报相关全局变量的值 */
        pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucCurcRptCfg,
                   pstCurcRptCtrl->aucRptCfg,
                        MN_CALL_RPT_CFG_MAX_SIZE);

        pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucUnsolicitedRptCfg,
                   pstUnsolicitedRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);

        TAF_CALL_UpdateCallInfo(callId, &(stCallMgmt.stCallInfo));
    }
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SendSupsCmdCnf
 功能描述  : MN_CALL_EVT_SUPS_CMD_CNF事件发送给AT
 输入参数  : usClientId     - 发起该请求的Client的ID或广播客户ID
             opId           - Operation ID, 标识本次操作
             callId         - 呼叫ID
             ulErrorCode    - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月09日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年01月23日
    作    者   : f62575
    修改内容   : DTS2014012106603: 临时响应MN_CALL_EVT_CALL_ORIG_CNF，
                 MN_CALL_EVT_SUPS_CMD_CNF
                 CLIENT id从广播ID修改为业务发起方
  3.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  4.日    期   : 2014年6月24日
    作    者   : z00161729
    修改内容   : DSDS III新增
  5.日    期   : 2015年03月03日
    作    者   : n00269697
    修改内容   : DTS2015021501043
*****************************************************************************/
VOS_VOID TAF_CALL_SendSupsCmdCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
    MN_CALL_MGMT_STRU                   stCallMgmt;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallMgmt, 0, sizeof(MN_CALL_MGMT_STRU));

    /* 1. 可能会存在还没分配callid就发现错误，需要给AT回复,
        此时需要构造stCallInfo,不能取实体中的stCallInfo
       2. 如果已经分配callid就取实体中的stCallInfo
    */
    if (VOS_OK == MN_CALL_GetSpecificCallInfo(callId, &stCallMgmt))
    {
        stCallMgmt.stCallInfo.callId   = callId;

        /* 增加主动上报相关全局变量的值 */
        pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucCurcRptCfg,
                   pstCurcRptCtrl->aucRptCfg,
                        MN_CALL_RPT_CFG_MAX_SIZE);

        pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
        PS_MEM_CPY(stCallMgmt.stCallInfo.aucUnsolicitedRptCfg,
                   pstUnsolicitedRptCtrl->aucRptCfg,
                   MN_CALL_RPT_CFG_MAX_SIZE);
    }

    stCallMgmt.stCallInfo.clientId   = clientId;
    stCallMgmt.stCallInfo.opId       = opId;
    stCallMgmt.stCallInfo.enCause    = enCause;

    if (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == TAF_CALL_GetCallSubState(callId))
    {
        stCallMgmt.stCallInfo.ucAtaReportOkAsyncFlag = TAF_CALL_GetAtaReportOkAsyncFlag();
    }

    /* 对所有注册了CS域呼叫事件回调函数的Client调用回调函数 */
    MN_SendClientEvent(clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SUPS_CMD_CNF,
                       &(stCallMgmt.stCallInfo));
}

/*****************************************************************************
 函 数 名  : MN_CALL_SndStkCallDiscEvent
 功能描述  : 输出事件Call disconnected event
 输入参数  : VOS_VOID                          *pMsg      DISCONNECT, RELEASE, RELEASE COMPLETE消息
             MNCC_PRIM_NAME_ENUM_U16            enMsgName 呼叫结束类型
             VOS_BOOL                           bNetMsg   是否网络过来的释放消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,TQE告警
  3.日    期   : 2013年04月12日
    作    者   : f62575
    修改内容   : DTS2013041503184,解决3G下RADIO LINK FAILURE没有按协议要求输出近端释放事件问题
                 所有RR连接释放都按RADIO LINK FAILURE处理，即只有CC直传消息会触发
                 远端释放事件
                 仅在呼叫重建失败后上报给UICC，此处删除MNCC_RADIO_LINK_FAILURE分支
  4.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  5.日    期   : 2013年7月12日
    作    者   : l00208543
    修改内容   : STK升级项目，发消息给STK
*****************************************************************************/
VOS_VOID MN_CALL_SndStkCallDiscEvent(
    const VOS_VOID                     *pMsg,
    MNCC_PRIM_NAME_ENUM_U16             enMsgName,
    VOS_BOOL                            bNetMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCallId;
    VOS_BOOL                            bReleaseFlag;

    /* Added by l00208543 for V9R1 STK升级, 2013-07-10, begin */
    VOS_UINT32                          ulMsgLength;
    NAS_STK_CALL_DISC_EVENT_STRU       *pstCallDiscEvent = VOS_NULL_PTR;

    ulMsgLength    = sizeof(NAS_STK_CALL_DISC_EVENT_STRU);

    pstCallDiscEvent = (NAS_STK_CALL_DISC_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstCallDiscEvent)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallDiscEvent: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstCallDiscEvent->stCallDiscEventInfo), 0, sizeof(NAS_STK_CALL_DISC_EVENT_INFO_STRU));

    pstCallDiscEvent->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstCallDiscEvent->ulMsgId       = ID_NAS_STK_CALL_DISC_EVENT;
    /* Added by l00208543 for V9R1 STK升级, 2013-07-10, end */


    ucTi            = 0;
    ucCallId        = 0;

    bReleaseFlag    = VOS_FALSE;

    /*
    判断是否已经发送过释放消息给(U)SIM: 是，则直接退出
    呼叫重建后释放呼叫是否允许重发DISCONNECT EVENT，待确认；
    */

    /*
        协议ETSI TS 102 223 V10.5.0 (2011-09) 7.5.3 Call disconnected event
        If the terminal initiates the disconnection, or in the case of radio
        link failure, this is considered a "near end" disconnection,
        whereas a "far end" disconnection is defined as when the network
        initiates the disconnection.
        in the case of "near end" disconnection, the terminal shall set the
        device identities to:
        - source: terminal;
        - destination: UICC.
        in the case of connecting at the far end (an MO call), the terminal
        shall set the device identities to:
        - source: network;
        - destination: UICC.
    */

    if ((VOS_TRUE != bNetMsg)
     || (MNCC_REJ_IND == enMsgName))
    {
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, begin */
        pstCallDiscEvent->stCallDiscEventInfo.ucLocalDiscFlg = VOS_TRUE;
    }
    else
    {
        pstCallDiscEvent->stCallDiscEventInfo.ucLocalDiscFlg = VOS_FALSE;
    }
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, end */



    /* 填写TransactionId，和Cause到stEvent */

    if (VOS_TRUE == bNetMsg)
    {
        ulRet = MN_CALL_GetNetDiscEventInfo((MNCC_IND_PRIM_MSG_STRU *)pMsg,
            /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, begin */
                                             &(pstCallDiscEvent->stCallDiscEventInfo.stCause),
            /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, end */
                                             &ucTi,
                                             &ucCallId);
        ucTi  = (VOS_UINT8)((ucTi ^ 0x08) << 4);
    }
    else
    {
        ulRet = MN_CALL_GetUeDiscEventInfo((MNCC_REQ_PRIM_MSG_STRU *)pMsg,
            /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, begin */
                                            &(pstCallDiscEvent->stCallDiscEventInfo.stCause),
            /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, end */
                                            &ucTi,
                                            &ucCallId);
        ucTi  = (VOS_UINT8)(ucTi << 4);
    }
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_FREE_MSG(WUEPS_PID_TAF, pstCallDiscEvent);
        return;
    }

    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, begin */
    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, end */

    /* 一个呼叫仅记录一次呼叫释放事件的原因值，bReleaseFlag为VOS_TRUE标志已经有记录，退出 */
    MN_CALL_GetCallReleaseFlag(ucCallId, &bReleaseFlag);

    if (VOS_TRUE == bReleaseFlag)
    {
        PS_FREE_MSG(WUEPS_PID_TAF, pstCallDiscEvent);
        return;
    }

    /* Modified by l00208543 for V9R1 STK升级, 2013-07-13, begin */
    pstCallDiscEvent->stCallDiscEventInfo.ucTi = ucTi;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstCallDiscEvent);
    if (VOS_OK != ulRet)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallDiscEvent: Send Msg Fail!");
        return;
    }
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-13, end */

    /* 一个呼叫仅记录一次呼叫释放事件的原因值，此处更新标志为已记录 */
    MN_CALL_UpdateCallReleaseFlag(ucCallId, VOS_TRUE);

    return;

}

/*****************************************************************************
 函 数 名  : MN_CALL_SndStkCallConnEvent
 功能描述  : 输出事件Call connect event
 输入参数  : ucTi           - CONNECT消息的TI
             enCallDir      - 呼叫方向
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  3.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : STK升级项目,改变与STK消息交互模式,由STK调用TAF接口改为直接发送消息通知STK
*****************************************************************************/
VOS_VOID MN_CALL_SndStkCallConnEvent(
    VOS_UINT8                           ucTi,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    /* Added by l00208543 for V9R1 STK升级, 2013-07-13, begin */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLength;
    NAS_STK_CALL_CONNECT_EVENT_STRU    *pstCallConnEvent = VOS_NULL_PTR;

    ulMsgLength         = sizeof(NAS_STK_CALL_CONNECT_EVENT_STRU);

    pstCallConnEvent    = (NAS_STK_CALL_CONNECT_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstCallConnEvent)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallConnEvent: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstCallConnEvent->stCallConnectEventInfo),
                0,
                sizeof(NAS_STK_CALL_CONNECT_EVENT_INFO_STRU));
    /* Added by l00208543 for V9R1 STK升级, 2013-07-13, end */


    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, begin */
    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, end */

    /* 协议ETSI TS 102 223 V10.5.0 (2011-09) 7.5.2.2 Structure of ENVELOPE
        (EVENT DOWNLOAD - call connected)
        Device identities:
        in the case of connecting at the near end (an MT call), the terminal
        shall set the device identities to:
        - source: terminal;
        - destination: UICC.
        in the case of connecting at the far end (an MO call), the terminal
        shall set the device identities to:
        - source: network;
        - destination: UICC.
    */
    if (MN_CALL_DIR_MO == enCallDir)
    {
        /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, begin */
        /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, end */
        ucTi  = (VOS_UINT8)((ucTi ^ 0x08) << 4);
    }
    else
    {
        /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, begin */
        /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, end */
        ucTi  = (VOS_UINT8)(ucTi << 4);
    }

    pstCallConnEvent->stCallConnectEventInfo.enCallDir = enCallDir;
    pstCallConnEvent->stCallConnectEventInfo.ucTi      = ucTi;

    pstCallConnEvent->ulReceiverPid                    = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstCallConnEvent->ulMsgId                          = ID_NAS_STK_CALL_CONNECT_EVENT;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstCallConnEvent);
    if (VOS_OK != ulRet)
    {
        MN_ERR_LOG("MN_CALL_SndStkCallConnEvent: Send Msg Fail!");
    }

    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, begin */
    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, end */

    return;

}

/*****************************************************************************
 函 数 名  : MN_CALL_SndStkMtCallEvent
 功能描述  : 输出事件MT call event
 输入参数  : callId         - 呼叫实体索引
             ucTi           - 消息的TI
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID MN_CALL_SndStkMtCallEvent(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLength;
    MN_CALL_INFO_STRU                   stCallInfo;
    NAS_STK_MT_CALL_EVENT_STRU         *pstMtCallEvent = VOS_NULL_PTR;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    ulMsgLength    = sizeof(NAS_STK_MT_CALL_EVENT_STRU);

    pstMtCallEvent = (NAS_STK_MT_CALL_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMtCallEvent)
    {
        MN_ERR_LOG("MN_CALL_SndStkMtCallEvent: Alloc Msg Fail!");
        return;
    }

    /* Added by l00208543 for V9R1 STK升级, 2013-07-18, begin */
    PS_MEM_SET(&(pstMtCallEvent->stMtCallEventInfo), 0, sizeof(NAS_STK_MT_CALL_EVENT_INFO_STRU));
    /* Added by l00208543 for V9R1 STK升级, 2013-07-18, end */

    /* 获取当前呼叫实体的呼叫信息 */
    MN_CALL_GetCallInfoByCallId(callId, &stCallInfo);

    /* MT call event包括TransactionId，Addr和Subaddr */
    /* 填写TransactionId到stEvent */
    pstMtCallEvent->stMtCallEventInfo.ucTi  = (VOS_UINT8)((ucTi ^ 0x08) << 4);


    /* 填写主叫号码到stEvent */
    PS_MEM_CPY(&pstMtCallEvent->stMtCallEventInfo.stCallerNumber,
               &stCallInfo.stCallNumber,
               sizeof(MN_CALL_BCD_NUM_STRU));

    /* 填写主叫号码子地址到stEvent */
    PS_MEM_CPY(&pstMtCallEvent->stMtCallEventInfo.stCallerSubNumber,
               &stCallInfo.stSubCallNumber,
               sizeof(MN_CALL_SUBADDR_STRU));

    pstMtCallEvent->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstMtCallEvent->ulMsgId       = ID_NAS_STK_MT_CALL_EVENT;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMtCallEvent);
    if (VOS_OK != ulRet)
    {
        MN_ERR_LOG("MN_CALL_SndStkMtCallEvent: Send Msg Fail!");
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_CALL_SendDtmfCnf
 功能描述  : 回复DTMF请求
 输入参数  : usClientId     -- ClientID
             opId           -- 操作ID
             enEventType    -- 回复的DTMF事件类型
             enCause        -- 原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID TAF_CALL_SendDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_CALL_EVT_DTMF_CNF_STRU          stDtmfCnf;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(stDtmfCnf));

    TAF_CALL_FillDtmfCnf(usClientId, opId, enCause, &stDtmfCnf);

    TAF_CALL_SendMsg(usClientId,
                     enEventType,
                     (VOS_VOID *)&stDtmfCnf,
                     sizeof(stDtmfCnf));

    return;
}

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_CALL_SendQueryEcallInfoCnf
 功能描述  : MN_CALL_EVT_QRY_ECALL_INFO_CNF事件发送给AT
 输入参数  : usClientId     - 发起该请求的Client的ID或广播客户ID
             opId           - Operation ID, 标识本次操作
             pstEcallInfo   - eCall呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_SendQueryEcallInfoCnf(
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU                    *pstEcallInfo
)
{
    MN_SendClientEvent(usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_QRY_ECALL_INFO_CNF,
                       pstEcallInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SendTafRelCallCnf
 功能描述  : TAF_CALL_TAF_REL_CALL_CNF事件发送给TAF
 输入参数  : usClientId     - 发起该请求的Client的ID或广播客户ID
             opId           - Operation ID, 标识本次操作
             enCause        - 释放结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_SendTafRelCallCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_CALL_TAF_REL_CALL_CNF_STRU      *pstCallCnf = VOS_NULL_PTR;

    pstCallCnf = (TAF_CALL_TAF_REL_CALL_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, 
                    sizeof(TAF_CALL_TAF_REL_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstCallCnf)
    {
        MN_ERR_LOG("TAF_CALL_SendTafRelCallCnf: ERROR: Memory allocation Fail.");
        return;
    }

    PS_MEM_SET(pstCallCnf, 0, sizeof(TAF_CALL_TAF_REL_CALL_CNF_STRU));
    
    pstCallCnf->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstCallCnf->ulSenderPid          = WUEPS_PID_TAF;
    pstCallCnf->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstCallCnf->ulReceiverPid        = WUEPS_PID_TAF;
    pstCallCnf->ulLength             = sizeof(TAF_CALL_TAF_REL_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCallCnf->ulMsgId              = TAF_CALL_TAF_REL_CALL_CNF;

    pstCallCnf->usClientId           = usClientId;
    pstCallCnf->ucOpId               = ucOpId;
    pstCallCnf->enCause              = enCause;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCallCnf))
    {
        MN_WARN_LOG( "TAF_CALL_SendTafRelCallCnf:WARNING:SEND TAF_CALL_TAF_REL_CALL_CNF msg FAIL!" );
    }

    return;
}

#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
