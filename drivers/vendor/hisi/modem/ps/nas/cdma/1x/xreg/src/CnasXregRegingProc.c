/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregRegingProc.c
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2014年06月27日
  功能描述   : 1X REG模块正在注册流程
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : Y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "CnasXregCtx.h"
#include  "CnasXregProcess.h"
#include  "CnasXregSndCas.h"
#include  "CnasXregSndInternalMsg.h"
#include  "CnasXregTimer.h"
#include  "CnasXregRegingProcTbl.h"
#include  "CnasTimerMgmt.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "CnasXregSndAps.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_REGING_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
//extern VOS_VOID CNAS_XREG_SndApsRegBeginInd(VOS_VOID);
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvRegReq_Reging_Init
 功能描述  : 发送注册请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvRegReq_Reging_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstRegReq;

    pstRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)pstMsg;

    /* 保存入口消息 */
    CNAS_XREG_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 发送注册消息 */
    CNAS_XREG_SndCASEstReq(pstRegReq->enRegType);

    if (VOS_TRUE == CNAS_XREG_IsNeedNotifyApsRegBegin(pstRegReq->enRegType))
    {
        CNAS_XREG_SndApsRegBeginInd();
    }

    /* 启动EstReq保护定时器 */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ESTCNF_PT, TI_CNAS_XREG_TIMER_ESTCNF_PT_LEN);


    CNAS_XREG_SetCurrFsmState(CNAS_XREG_REGING_WAIT_EST_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf
 功能描述  : 在等待中止状态机消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvRegReq_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    /* 根据当前的注册类型停止EstCnf保护定时器 */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);

    /* 发送ABORT消息给CAS */
    CNAS_XREG_SndCASAbortReq();

    /* 启动保护定时器并切换状态机状态 */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ABORTCNF_PT, TI_CNAS_XREG_TIMER_ABORTCNF_PT_LEN);

    CNAS_XREG_SetCurrFsmState(CNAS_XREG_REGING_WAIT_ABORT_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf
 功能描述  : 接收到EstCnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_EST_CNF_STRU           *pstEstCnf;
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEstCnf   = (CAS_CNAS_1X_EST_CNF_STRU*)pstMsg;

    /* 类型不正确直接返回 */
    if (CAS_CNAS_1X_EST_TYPE_REGISTRATION != pstEstCnf->enEstType)
    {
        return VOS_TRUE;
    }

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* 停止EstCnf保护定时器 */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);

    /* 记录注册结果 */
    CNAS_XREG_RecordRegRslt(pstCurrRegReq->enRegType, pstEstCnf->enEstRslt);

    /* 注册失败处理流程 */
    if (CAS_CNAS_1X_EST_RSLT_NO_RF == pstEstCnf->enEstRslt)
    {
        CNAS_XREG_RegFailProc();

        CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_NORF, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

        /* 退出层二状态机*/
        CNAS_XREG_QuitFsmL2();

        return VOS_TRUE;
    }

    if (CAS_CNAS_1X_EST_RSLT_SUCCESS != pstEstCnf->enEstRslt)
    {
        CNAS_XREG_RegFailProc();

        CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

        /* 退出层二状态机*/
        CNAS_XREG_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 注册成功 */
    CNAS_XREG_RegSuccProc();

    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_SUCCESS, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

    /* 退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf
 功能描述  : 等待EstCnf时接收到AbortInd消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* 根据当前的注册类型停止EstCnf保护定时器 */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);


    /* 记录当前是接收到接入层上报的ABORT消息 */
    CNAS_XREG_RecordRegRslt(pstCurrRegReq->enRegType, CAS_CNAS_1X_EST_RSLT_BUTT);

    /* 发送内部消息通知退出层二状态机后的状态 */
    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

    /* 退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf
 功能描述  : 接收EstCnf超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* EST请求超时记录 */
    CNAS_XREG_RecordRegRslt(pstCurrRegReq->enRegType, CAS_CNAS_1X_EST_RSLT_BUTT + 1);

    /* 发送ABORT消息给CAS */
    CNAS_XREG_SndCASAbortReq();

    /* 启动保护定时器并切换状态机状态 */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ABORTCNF_PT, TI_CNAS_XREG_TIMER_ABORTCNF_PT_LEN);

    CNAS_XREG_SetCurrFsmState(CNAS_XREG_REGING_WAIT_ABORT_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd
 功能描述  : 接收到AbortInd消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* 停止ABortInd保护定时器 */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ABORTCNF_PT, 0);

    /* 发送内部消息通知退出层二状态机后的状态 */
    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_ABORT_IND, pstCurrRegReq->enRegType);

    /* 退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd
 功能描述  : 等待AbortInd消息的超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* 发送内部消息通知退出层二状态机后的状态 */
    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_ABORT_IND, pstCurrRegReq->enRegType);

    /* 退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_PostProcessMsg_Reging
 功能描述  : 处理层二状态机的后处理消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : g00256031
    修改内容   : 新生成函数

 2.日    期   : 2015年09月18日
   作    者   : d00212987
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_UINT32  CNAS_XREG_PostProcessMsg_Reging(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstRegReq;

    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) == ulEventType)
    {
        pstRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)pstMsg;

        /* 接收到非POWERDOWN的注册则直接丢弃 */
        if (CAS_CNAS_1X_POWER_DOWN_REGISTRATION != pstRegReq->enRegType)
        {
            return VOS_TRUE;
        }

        /* 发送内部消息终止当前流程 */
        CNAS_XREG_SndAbortFsmMsg();

        /* 缓存消息 */
        /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
        CNAS_XREG_SaveMsgToCache(ulEventType, (VOS_UINT8*)pstMsg);
        /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_IsNeedNotifyApsRegBegin
 功能描述  : 判断是否需要通知APS触发了注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要通知APS； VOS_FALSE:不需要通知APS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_IsNeedNotifyApsRegBegin(
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8                enRegType
)
{
   /*
    If the mobile station enters the Registration Access Substate (see [16]) due to timer-
    based registration, distance-based registration, zone-based registration, parameter
    change registration, or user zone registration, and if the packet zone list contains an
    entry with an active hysteresis timer for the current packet zone, the mobile station
    shall cancel the entrys packet zone hysteresis timer and shall remove the entry from
    the packet zone list.4
    */

    switch (enRegType)
    {
        case CAS_CNAS_1X_TIMER_BASED_REGISTRATION:
        case CAS_CNAS_1X_ZONE_BASED_REGISTRATION:
        case CAS_CNAS_1X_PARAMETER_CHANGED_REGISTRATION:
        case CAS_CNAS_1X_DISTANCE_BASED_REGISTRATION:
        case CAS_CNAS_1X_USER_ZONE_BASED_REGISTRATION:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf
 功能描述  : 接收Poweroff超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* 判断消息内容是否正确 */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_PWROFF, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

    /* 退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


