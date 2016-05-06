/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmMain.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月12日
  功能描述   : HRPD L1主状态机下收到各事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdFsmMain.h"
#include  "CnasHsdFsmMainTbl.h"
#include  "CnasHsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasPrlApi.h"
#include  "CnasCcb.h"
#include  "CnasHsdFsmSysAcq.h"
#include  "CnasTimerMgmt.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "CnasHsdAvoidStrategy.h"
#include  "cas_hrpd_overheadmsg_nas_pif.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdSndInternalMsg.h"

#include  "CnasHsdSndRrm.h"

#include  "NasOmInterface.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                        PS_FILE_ID_CNAS_HSD_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvStartReq_Null
 功能描述  : 处理在null状态收到开机请求事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月03日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动L2开机状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSwitchOnRsltCnf_Null
 功能描述  : 收到开机结果后，若成功迁移到CNAS_HSD_L1_STA_INACTIVE状态，
             失败保持CNAS_HSD_L1_STA_NULL状态
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSwitchOnRsltCnf_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU                    *pstSwitchOnMsg;

    pstSwitchOnMsg = (CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU *)pstMsg;

    /* 收到开机结果后，若成功迁移到CNAS_HSD_L1_STA_INACTIVE状态 */
    if (CNAS_HSD_SWITCH_ON_RESULT_SUCCESS == pstSwitchOnMsg->enRslt)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        /* 通知MSCC开机成功 */
        CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_SUCC);
    }
    /* 失败保持CNAS_HSD_L1_STA_NULL状态，收到关机请求时仍然要给HSM/HLU/CAS发关机 */
    else
    {
        /* 通知MSCC开机失败 */
        CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_FAIL);

        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvSwitchOnRsltCnf_Deactive:switch on fail");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPowerOffReq_Null
 功能描述  : 处理在null状态收到关机请求事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : h00300778
   修改内容   : 新生成函数
 2.日    期   : 2015年06月23日
   作    者   : z00316370
   修改内容   : 开机顺便变更后，在NULL状态也需要起关机状态机

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动L2关机状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_POWER_OFF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPowerOffReq_L1Main
 功能描述  : 收到ID_MMA_HSD_POWER_OFF_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动L2关机状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_POWER_OFF);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPowerOffReq_Initial
 功能描述  : 处理在IDLE或OCC状态收到L2 power off关机确认事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2014年12月03日
     作    者   : h00300778
     修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerOffRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD所有定时器 */
    CNAS_StopAllTimerWithSpecifiedPid(UEPS_PID_HSD);

    /* 开机时判断是否需初始化PRL */

    /* 通知MSCC关机结果 */
    CNAS_HSD_SndMsccPowerOffCnf();

    /* 初始化HSD模块CTX */
    CNAS_HSD_InitCtx(CNAS_HSD_INIT_CTX_POWEROFF);

    /* 状态迁移到CNAS_HSD_L1_STA_NULL */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_NULL);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqReq_Inactive
 功能描述  : INACTIVE状态收到ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 增加搜网场景判断

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSysAcqReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU   *pstSysAcqReq;
    CNAS_HSD_HIGHPRIORITY_STRU         *pstHighPri;

    /* 无卡并且无卡模式关闭下直接返回搜网失败 */
    if (CNAS_CCB_CARD_STATUS_ABSENT == CNAS_CCB_GetCsimCardStatus())
    {
        if (VOS_FALSE == (CNAS_HSD_GetTestConfig()->ucNoCardModeCfgFlg))
        {
            CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

            return VOS_TRUE;
        }
    }

    pstSysAcqReq    = (MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU *)pstMsg;

    if (MSCC_HSD_ACQUIRE_REASON_POWER_UP == pstSysAcqReq->enReason)
    {
        CNAS_HSD_StartSysAcq_Inactive(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON);
    }
    else if (MSCC_HSD_ACQUIRE_REASON_HIGH_PRIORITY == pstSysAcqReq->enReason)
    {
        pstHighPri = CNAS_HSD_GetHighPriorityFreqAddr();

        /* 初始化高优先级网络频点信息 */
        CNAS_HSD_InitHighPriorityFreq(pstHighPri);

        /* 将高优先级频点信息保存到上下文中 */
        pstHighPri->ucFreqNum = CNAS_MIN(pstSysAcqReq->ucFreqNum, CNAS_HSD_MAX_PREF_SUBNET_NUM);

        PS_MEM_CPY(pstHighPri->astFreqInfo,
                   pstSysAcqReq->astFreqInfo,
                   pstHighPri->ucFreqNum * sizeof(CNAS_HSD_SYSTEM_ACQUIRE_FREQ_INFO_STRU));

        /* 开始高优先级搜网 */
        CNAS_HSD_StartSysAcq_Inactive(CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY);
    }
    else if (MSCC_HSD_ACQUIRE_REASON_OTHER == pstSysAcqReq->enReason)
    {
        /* MSCC发起的OTHER，HSD按照LOST处理 */
        CNAS_HSD_StartSysAcq_Inactive(CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER);
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvInternalSysAcqReq_Initial
 功能描述  : INACTIVE状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvInternalSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndCasBeginSessionNotify();

    /* 启动L2 System Acquire状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ
 功能描述  : initial状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF消息的处理
 输入参数  : pstSysAcqRslt

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* 如果是pilot search场景，将结果通知给CAS,重新切回inactive态后返回 */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchSuccNtf();

        /* 状态迁移到CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    /* 状态迁移到CNAS_HSD_L1_STA_IDLE */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_IDLE);

    /* 开机场景搜网成功 */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);
    }

    /* 如果是DATA CALL快速搜网场景，给MSCC回复快速搜网成功消息 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);
    }

    /* 上报搜网成功 */
    CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    /* 初始化OOC上下文信息 */
    CNAS_HSD_InitOocCtxInfo();

    /* 停止所有OOC下定时器,需要停止吗?*/
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted
 功能描述  : initial状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF消息的处理
 输入参数  : pstSysAcqRslt

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* 开机搜网场景 */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 如果是pilot search场景，将结果通知给CAS,重新切回inactive态后返回 */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchFailNtf();

        CNAS_HSD_SndHsmPilotSearchFailNtf();

        /* 状态迁移到CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    /* 如果是DATA CALL快速搜网场景，给MSCC回复消息 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 状态迁移到CNAS_HSD_L1_STA_OOC */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

    /* 假如需要立即启动搜网则不上报给MSCC无服务 */
    if (CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE != pstSysAcqRslt->enImmediateSysAcq)
    {
        /* 上报搜网结果 */
        CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF
 功能描述  : initial状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF消息的处理
 输入参数  : pstSysAcqRslt

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enCur1xState;
    /* 保存NORF的场景 */
    CNAS_HSD_SetNoRfScene(pstSysAcqRslt->enCurAcqScene);

    /* 向RRM发起注册,RF可用后RRM会通知XSD */
    /* 需要判断重入情况 如果正在等待RRM的status ind 不需要发送消息和启动定时器 */
    CNAS_HSD_SndRrmRegisterInd(RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH);

    /* 开启保护定时器 */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND, TI_CNAS_HSD_WAIT_RRM_STATUS_IND_LEN);

    /* 状态迁移到CNAS_HSD_L1_STA_OOC */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

    /* 如果当时在INIT 态 说明1X正在搜网，RF available之后按照开机搜网 */
    enCur1xState = CNAS_CCB_GetCasState();

    CNAS_HSD_SetNoRf1XUeStatus(enCur1xState);


    if (VOS_TRUE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_HSD_SndMsccRfAvailInd(VOS_FALSE);

        /* 设置当前RF可用标记为:RF不可用 */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_FALSE);
    }

    /* 开机场景搜网失败 */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* 如果是pilot search场景，将结果通知给CAS,重新切回inactive态后返回 */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchFailNtf();

        CNAS_HSD_SndHsmPilotSearchFailNtf();

        /* 状态迁移到CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    /* 如果是重定向场景，添加当前驻留频点到Avoid频点中 */
    if (CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION == pstSysAcqRslt->enCurAcqScene)
    {
        /* 该场景NORF按照丢网处理 */
        CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);
    }

    /* 如果是DATA CALL快速搜网场景，给MSCC回复失败消息 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        /* 该场景NORF按照丢网处理 */
        CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);

        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);
    }

    /* 上报搜网失败 */
    CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail
 功能描述  : initial状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF消息的处理
 输入参数  : pstSysAcqRslt

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* 开机场景搜网失败 */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* 如果是重定向场景，添加当前驻留频点到Avoid频点中 */
    if (CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_ProcAvoidEventInRedirection(&(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSyncFreq));

        /* 重定向失败，立即搜网 */
        pstSysAcqRslt->enImmediateSysAcq = CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE;
    }

    /* 如果是DATA CALL 快速搜网场景，给MSCC回复失败消息 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* 如果是pilot search场景，将结果通知给CAS,重新切回inactive态后返回 */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchFailNtf();

        CNAS_HSD_SndHsmPilotSearchFailNtf();

        /* 状态迁移到CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    if (CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE == pstSysAcqRslt->enImmediateSysAcq)
    {
        /* 状态迁移到CNAS_HSD_L1_STA_INITIAL */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
    }
    else
    {
        /* 上报搜网失败 */
        CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

        /* 如果当前场景是恢复搜网下的丢网，修成场景为丢网场景 */
        if (CNAS_HSD_SYS_ACQ_SCENE_NO_RF_RESUME == pstSysAcqRslt->enCurAcqScene)
        {
            pstSysAcqRslt->enCurAcqScene = CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST;
        }
        /* 状态迁移到CNAS_HSD_L1_STA_OOC */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

        CNAS_HSD_SetOocSearchScene(pstSysAcqRslt->enCurAcqScene);
        CNAS_HSD_ProcOocSchedule(pstSysAcqRslt->enCurAcqScene);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqRsltCnfProc_Initial
 功能描述  : initial状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSysAcqRsltCnfProc_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt;

    pstSysAcqRslt = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU *)pstMsg;

    CNAS_HSD_SndCasEndSessionNotify();

    /* 清除abnormal标志 */
    CNAS_HSD_SetAbnormalLostFlag(VOS_FALSE);

    switch(pstSysAcqRslt->enRslt)
    {
        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_SUCCESS:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_ACQUIRE_SUCCESS, UEPS_PID_HSD);
            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);

            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);
            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);
            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_REDIRECTION:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);

            break;
        }

        default:
            CNAS_ERROR_LOG(UEPS_PID_HSD, "Acq Scene error.");

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiAvailTimerExpired_Ooc
 功能描述  : OOC状态下available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiAvailTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_GetOocSearchScene(),
                                  0,
                                  VOS_NULL_PTR);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPilotSearch_Inactive
 功能描述  : INACTIVE状态下收到接入层导频搜索消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPilotSearch_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置L1状态机进入搜网状态 */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvStartReq_Inactive
 功能描述  : INACTIVE状态下收到开机消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvStartReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 这里属于异常的场景，MSCC不应该在INACTIVE态发开机，但如果收到了还是回复开机结果给MSCC,通知MSCC开机成功 */
    CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_Rcv1xSysAcqInd_Inactive
 功能描述  : L1状态机下收到XSD在1X下搜网成功消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年04月13日
    作    者   : Z00316370
    修改内容   : 修改1x系统的接口
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;

    enSysAcqStatus = CNAS_HSD_GetSysAcqStatus();

    if ((enSysAcqStatus & CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV) == CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV)
    {
        return VOS_TRUE;
    }

    enSysAcqScene = CNAS_HSD_GetAcqSceneBySysAcqStatus();

    /* MSCC的搜网和1X搜网都收齐了就开始搜网 */
    if (CNAS_HSD_SYS_ACQ_SCENE_BUTT != enSysAcqScene)
    {
        /* 设置L1状态机进入INITIAL状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(enSysAcqScene, 0, VOS_NULL_PTR);
    }

    CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_SYS_ACQ_1X_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_Rcv1xSysAcqInd_Idle
 功能描述  : L1状态机下收到XSD在1X下搜网成功消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年04月11日
    作    者   : z00316370
    修改内容   : 1x信息改由MSCC发送，修改相应消息接口
  3.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 判断和1x关联性接口修改

*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU    *pst1xSysIndMsg;
    CNAS_HSD_ASSN_RLST_ENUM_UINT32      enAssnRlst;
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys;

    pst1xSysIndMsg = (MSCC_HSD_1X_SYS_CHANGE_IND_STRU *)pstMsg;

    /* 1X搜网结果为失败则不用进行判断 */
    if (VOS_TRUE != pst1xSysIndMsg->ucIs1xAvail)
    {
        return VOS_TRUE;
    }

    /* 需要到空闲态下进行相关联判断 */
    if (CNAS_HSD_AT_STATUS_ENUM_IDLE != CNAS_HSD_GetATStatus())
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetATStatus: Current state isn't idle.");

        return VOS_TRUE;
    }

    if (CNAS_HSD_HRPD_SYSTEM_AVAILABLE != CNAS_HSD_GetHrpdSysStatus())
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_Rcv1xSysChgInd_Idle: Current state is incorrect.");

        /* 异常保护，返回CNAS_HSD_ASSN_SUCC代表关联不进行重新搜网操作 */
        return VOS_TRUE;
    }

    /* 假如为锁频下就不用判断 */
    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        return VOS_TRUE;
    }

    pstHrpdSys = CNAS_HSD_GetCampedHrpdSystemInfo();

    /*  获取当前1X和HRPD的关联关系 */
    enAssnRlst = CNAS_HSD_CheckHrpdFreqAssnWith1X(pstHrpdSys);

    /* 当前没有相关联的频点 */
    if (CNAS_HSD_NO_ASSN_FREQ == enAssnRlst)
    {
        CNAS_HSD_ClearHrpdSysInfo();

        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

        CNAS_HSD_SndCasOocNtf();

        /* 上报搜网失败,通知MSCC切换到LTE */
        CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

        return VOS_TRUE;
    }

    /* 有关联频点，但和当前的HRPD系统不相关联 */
    if (CNAS_HSD_NO_ASSN_WITH_HRPD == enAssnRlst)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_Rcv1xSysAcqInd_Ooc
 功能描述  : L1状态机下收到XSD在1X下搜网成功消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月22日
    作    者   : g00256031
    修改内容   : 新生成函数
  2.日    期   : 2015年04月11日
    作    者   : z00316370
    修改内容   : 1x信息改由MSCC发送，修改相应消息接口
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU    *pst1xSysIndMsg;

    pst1xSysIndMsg = (MSCC_HSD_1X_SYS_CHANGE_IND_STRU *)pstMsg;

    /* 1X搜网结果为失败则不用进行判断 */
    if (VOS_TRUE != pst1xSysIndMsg->ucIs1xAvail)
    {
        return VOS_TRUE;
    }

    /* 停止available定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER);

    /* 如果当前是NO_RF状态，不应当发起重新搜网 */
    if (VOS_FALSE != CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* 设置L1状态机进入INITIAL状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasOhmInd_Idle
 功能描述  : idle状态收到ID_CAS_CNAS_1X_OHM_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年2月11日
    作    者   : w00208541
    修改内容   : CDMA Iteration 8 增加Ohm上报到mscc
  3.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 判断和1x关联性接口修改
  4.日    期   : 2015年07月37日
    作    者   : x00306642
    修改内容   : MCC白皮书判断
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasOhmInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU    *pstOhmMsg;
    CNAS_PRL_HRPD_SYSTEM_STRU               stHrpdSys;
    CNAS_HSD_ASSN_RLST_ENUM_UINT32          enAssnRlst;
    VOS_UINT32                              ulMccFlg;

    pstOhmMsg = (CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU*)pstMsg;

    stHrpdSys.stFreq.enBandClass = pstOhmMsg->usBandClass;
    stHrpdSys.stFreq.usChannel   = pstOhmMsg->usFreq;
    stHrpdSys.ucSubnetMask       = pstOhmMsg->ucSubNetMask;

    PS_MEM_CPY(stHrpdSys.aucSubnet, pstOhmMsg->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    /* avoid模块处理 */
    CNAS_HSD_ProcAvoidEventInSubnetIdChange(&stHrpdSys);

    /* 更新history list */
    CNAS_HSD_UpdateHistorySysList(&stHrpdSys);

    /* 更新Hrpd驻留信息 */
    CNAS_HSD_UpdateHrpdSysInfo(&stHrpdSys);

    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        /* Idle切换成功的处理，要和下面保持一致 */
        /* HSD收到CAS的overhead消息时，要给HSM以及MSCC转发overhead消息 */
        CNAS_HSD_SndHsmOverheadMsgInd(pstOhmMsg);
        CNAS_HSD_SndMsccOverheadMsgInd(pstOhmMsg,&stHrpdSys);

        /* 将驻留的网络保存到MRU */
        CNAS_HSD_UpdateMru0(&stHrpdSys);

        return VOS_TRUE;
    }

    enAssnRlst = CNAS_HSD_CheckHrpdFreqAssnWith1X(&stHrpdSys);

    ulMccFlg = CNAS_HSD_IsMccInOperLockWhiteSidList(pstOhmMsg->usCountryCode);

    /* 当前系统不相关联 */
    if ((CNAS_HSD_NO_ASSN_WITH_HRPD == enAssnRlst)
     || (VOS_FALSE == ulMccFlg))
    {
        /* IDLE态下才进行搜网操作 */
        if (CNAS_HSD_AT_STATUS_ENUM_IDLE == CNAS_HSD_GetATStatus())
        {
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

            CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
        }
    }
    else if (CNAS_HSD_ASSN_SUCC == enAssnRlst)
    {
        /* Idle切换成功的处理，要和上面保持一致 */
        /* HSD收到CAS的overhead消息时，要给HSM以及MSCC转发overhead消息 */
        CNAS_HSD_SndHsmOverheadMsgInd(pstOhmMsg);
        CNAS_HSD_SndMsccOverheadMsgInd(pstOhmMsg,&stHrpdSys);

        /* 将驻留的网络保存到MRU */
        CNAS_HSD_UpdateMru0(&stHrpdSys);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCasOhmInd_Idle: enAssnRlst is incorrect.");;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNetworkLostIndProc_Idle
 功能描述  : IDLE状态下收到接入层上报丢网消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLostIndProc_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;
    VOS_UINT32                                              ulResult;

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        /* 重定向消息指示 */
        ulResult = CNAS_HSD_RcvCasRedirectionInd_Idle(ulEventType, pstMsg);
    }
    else if (CAS_CNAS_HRPD_NETWORK_LOST_NO_RF == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        ulResult = CNAS_HSD_RcvCasNoRFInd_Idle(ulEventType, pstMsg);
    }
    else
    {
        ulResult = CNAS_HSD_RcvCasNetworkLostInd_Idle(ulEventType, pstMsg);
    }

    CNAS_HSD_SndMsccHrpdNoSrvInd();

    return ulResult;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasRedirectionInd_Idle
 功能描述  : idle状态收到ID_CAS_CNAS_HRPD_REDIRECTION_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasRedirMsg;
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;

    pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

    pstCasRedirMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (0 == pstCasRedirMsg->ucChanNum)
    {
        /* 不携带频点信息的重定向消息按照普通丢网来处理 */
        /* 设置L1状态机进入搜网状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* 发起搜网 */
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* 收到的频点加入全局变量中用于构造搜网列 */
    pstRedirection->ucChanNum = pstCasRedirMsg->ucChanNum;

    PS_MEM_CPY(pstRedirection->aulChannel,
               pstCasRedirMsg->aulChannel,
               sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstCasRedirMsg->ucChanNum);

    /* 打印收到的频点信息 */
    CNAS_HSD_LogRedirectionFreqList(pstRedirection);

    /* 设置L1状态机进入搜网状态 */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    /* 发起搜网 */
    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNetworkLostInd_Idle
 功能描述  : IDLE状态下收到接入层上报丢网消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLostInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstLostMsg;

    pstLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU *)pstMsg;

    /* 设置L1状态机进入INITIAL状态 */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    if (CAS_CNAS_HRPD_NETWORK_LOST_ABNORMAL == pstLostMsg->enNetworkLostReason)
    {
        CNAS_HSD_SetAbnormalLostFlag(VOS_TRUE);
    }

    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, VOS_NULL, VOS_NULL_PTR);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle
 功能描述  : IDLE状态下收到接ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : d00212987
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 已经驻留完成直接回复成功 */
    CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc
 功能描述  : OOC状态下available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2015年1月14日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    /* 搜索MRU0 */
    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes
 功能描述  : 更新调度上下文信息
 输入参数  : CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    VOS_UINT8                           ucOocSchPhaseNum;
    VOS_UINT16                          usOocSchPhaseTimes;

    /* 根据当前OOC阶段获取下次启动OOC捕获时间 */
    ucOocSchPhaseNum    = pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase;
    usOocSchPhaseTimes  = pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[ucOocSchPhaseNum].usTimes;

    /* 刷新当前所处的阶段和次数 */
    if ((pstOocScheduleInfo->stConfigInfo.ucPhaseNum - 1) == ucOocSchPhaseNum)
    {
        /* 如果当前已经在最末尾的阶段，次数已经没有意义，这里始终设置成255 */
        pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes = CNAS_HSD_ATTEMP_UNLIMITED_TIMES;
    }
    else
    {
        /* 不在最末位的阶段，则次数累加，如果当前的次数已经到了该阶段的最大次数，则阶段增加，
             并把次数清0 */
        pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes++;
        if (pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes >= usOocSchPhaseTimes)
        {
            pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase++;
            pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes = 0;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNextOocScheduleTimerLen
 功能描述  : 获取下一次调度时长
 输入参数  : CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : Z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetNextOocScheduleTimerLen(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    VOS_UINT16                          usNextTimerLen;
    VOS_UINT8                           ucOocSchPhaseNum;

    usNextTimerLen = 0;

    /* 根据当前OOC阶段获取下次启动OOC捕获时间 */
    ucOocSchPhaseNum    = pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase;
    usNextTimerLen      = pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[ucOocSchPhaseNum].usTimerLen;

    return usNextTimerLen;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcOocSchedule
 功能描述  : 处理OOC调度
 输入参数  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcOocSchedule(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;
    VOS_UINT16                          usNextAcqTimerLen;
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT32                          ulRemainTimerLen;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    ucMru0SearchTimerLen = pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen;

    /* 有等待OOC的请求,在MRU0搜索时如果OOC定时器超时则设置OOC搜索请求,
       待MRU0搜索失败会返回到此时，直接启动OOC搜网*/
    if (VOS_TRUE == CNAS_HSD_GetOocWaitSearchFlag())
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene, 0, VOS_NULL_PTR);

        /* 清除标记 */
        CNAS_HSD_SetOocWaitSearchFlag(VOS_FALSE);

        return;
    }

    /* 搜索MRU0失败，再次check MRU0定时器是否可以启动 */
    if (CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0 == enAcqScene)
    {
        /* MRU0搜索步长不为0时，可以尝试MRU0 */
        if (ucMru0SearchTimerLen != 0)
        {
            /* 获取available剩余时长 */
            ulRemainTimerLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_HSD, TI_CNAS_HSD_AVAILABLE_TIMER, 0);

            /* 如果剩余时长仍然大于2倍MRU0时长，可以尝试MRU0, 启动MRU0定时器 */
            if ((VOS_UINT32)(ucMru0SearchTimerLen * 2000) < ulRemainTimerLen)
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER, (ucMru0SearchTimerLen * TI_CNAS_HSD_AVAILABLE_RATIO));
            }
        }

        return;
    }

    /* 更新前 LOG OOC调度信息 */
    CNAS_HSD_LogOocCtxInfo(&(pstOocScheduleInfo->stOocCtxInfo));

    usNextAcqTimerLen = CNAS_HSD_GetNextOocScheduleTimerLen(pstOocScheduleInfo);

    /* 如果OOC调度时间为0，立即启动搜网 */
    if (0 == usNextAcqTimerLen)
    {
        /* 设置L1 main状态为initial状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* 发起OOC场景下系统捕获 */
        CNAS_HSD_SndInternalSysAcqReq(pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene, 0, VOS_NULL_PTR);
    }
    else
    {
        /* 启动OOC available定时器 */
        CNAS_HSD_StartTimer(TI_CNAS_HSD_AVAILABLE_TIMER, (usNextAcqTimerLen * TI_CNAS_HSD_AVAILABLE_RATIO));

        /* 如果是OOC丢网场景，且MRU0的定时长度不为0，检查是否需要启动MRU0搜索 */
        if ((CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST == pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene)
         && (ucMru0SearchTimerLen != 0))
        {
            /* 2倍MRU0搜索时长是否小于当前OOC sleep时长，如果是，启动MRU0 available定时器 */
            if ((VOS_UINT32)(ucMru0SearchTimerLen * 2000) < usNextAcqTimerLen)
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER, (ucMru0SearchTimerLen * TI_CNAS_HSD_AVAILABLE_RATIO));
            }
        }
    }

    /* 更新OOC搜索阶段及当前阶段搜索次数 */
    CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes(pstOocScheduleInfo);

    /* 更新后 LOG OOC调度信息 */
    CNAS_HSD_LogOocCtxInfo(&(pstOocScheduleInfo->stOocCtxInfo));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetOocSearchScene
 功能描述  : 设置OOC搜索场景
 输入参数  : enAcqScene -- 搜索场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月13日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetOocSearchScene(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    /* 设置搜网场景 */
    if (VOS_FALSE == pstOocScheduleInfo->stOocCtxInfo.ucSceneSetFlag)
    {
        if (CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON != enAcqScene)
        {
            /* 如果不是开机搜网失败，则统一设置为OOC搜网 */
            pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene = CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST;
        }
        else
        {
            pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene = CNAS_HSD_SYS_ACQ_SCENE_OOC_SWITCH_ON;
        }

        pstOocScheduleInfo->stOocCtxInfo.ucSceneSetFlag       = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetOocSearchScene
 功能描述  : 获取OOC搜索场景
 输入参数  : enAcqScene -- 搜索场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年09月04日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetOocSearchScene(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    return (pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc
 功能描述  : OOC状态下收到接ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : d00212987
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU  *pstDataCallRedialReq;

    pstDataCallRedialReq = (MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU*)pstMsg;

    if (NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE == pstDataCallRedialReq->enCause)
    {
        /* 设置L1状态机进入搜网状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* 快速搜网 */
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPowerSaveReq_L1Main
 功能描述  : 收到ID_MSCC_HSD_POWER_SAVE_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动L2 POWER_SAVE状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_POWER_SAVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPowerSaveReq_Inactive
 功能描述  : inactive状态下收到ID_MSCC_HSD_POWER_SAVE_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数
  2.日    期   : 2015年06月30日
    作    者   : z00316370
    修改内容   : INACTIVE状态下也起POWER SAVE 状态机
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerSaveReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除HRPD搜网状态 */
    CNAS_HSD_ClearHrpdSysAcqStatusBits();

    /* inactive状态下，直接回复MSCC POWER SAVE结果 */
    CNAS_HSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvPowerSaveRsltCnf_L1Main
 功能描述  : 处理在IDLE或OCC状态收到L2 power save确认事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年04月03日
     作    者   : z00316370
     修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerSaveRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 停止HSD所有定时器 */
    //CNAS_StopAllTimerWithSpecifiedPid(UEPS_PID_HSD);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND);

    /* 通知MSCC POWER SAVE结果 */
    CNAS_HSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* 清除HRPD搜网状态 */
    CNAS_HSD_ClearHrpdSysAcqStatusBits();

    /* 状态迁移到CNAS_HSD_L1_STA_INACTIVE */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

    CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_POWER_SAVE, UEPS_PID_HSD);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_StartSysAcq_Inactive
 功能描述  : 在INACTIVE状态收到sys acq后发起搜网请求
 输入参数  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年04月07日
     作    者   : z00316370
     修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_StartSysAcq_Inactive(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;

    /* 非混合模式下收到MSCC的搜网请求之后就开始搜网 */
    if (CNAS_HSD_SYS_MODE_NONHYBRID == CNAS_HSD_GetModeType())
    {
        /* 设置L1状态机进入INITIAL状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(enSysAcqScene, 0, VOS_NULL_PTR);
    }
    else
    {
        CNAS_HSD_SetSysAcqStatusByAcqScene(enSysAcqScene);

        enSysAcqStatus = CNAS_HSD_GetSysAcqStatus();

        /* 1X搜网已收到就开始搜网 */
        if ((enSysAcqStatus & CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV) == CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV)
        {
            /* 设置L1状态机进入INITIAL状态 */
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

            CNAS_HSD_SndInternalSysAcqReq(enSysAcqScene, 0, VOS_NULL_PTR);
        }
    }
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasSubnetIdChkReq_Inactive
 功能描述  : 处理ID_CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ请求消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年06月02日
     作    者   : z00316370
     修改内容   : 新生成函数
   2.日    期   : 2015年08月10日
     作    者   : x00306642
     修改内容   : 增加白皮书的判断
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSubnetIdChkReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ_STRU                 *pstSubnetChk;
    CNAS_PRL_HRPD_SYSTEM_STRU                               stHrpdSys;
    VOS_UINT32                                              ulRslt;
    VOS_UINT32                                              ulMccFlg;

    pstSubnetChk = (CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ_STRU *)pstMsg;

    stHrpdSys.stFreq.enBandClass    = pstSubnetChk->usBandClass;
    stHrpdSys.stFreq.usChannel      = pstSubnetChk->usFreq;
    stHrpdSys.ucSubnetMask          = pstSubnetChk->ucSubNetMask;
    PS_MEM_CPY(stHrpdSys.aucSubnet, pstSubnetChk->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    /* 检查HRPD系统的有效性 */
    ulRslt = CNAS_HSD_HrpdSubnetIdChkProc(&stHrpdSys);

    ulMccFlg = CNAS_HSD_IsMccInOperLockWhiteSidList(pstSubnetChk->usCountryCode);

    if ((VOS_TRUE == ulRslt) && (VOS_TRUE == ulMccFlg))
    {
        /* 回复有效 */
        CNAS_HSD_SndCasSubnetIdChkCnf(PS_TRUE);
    }
    else
    {
        /* 回复无效 */
        CNAS_HSD_SndCasSubnetIdChkCnf(PS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasIratFromLteNtf_Inactive
 功能描述  : 处理ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF请求消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年06月02日
     作    者   : z00316370
     修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasIratFromLteNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndHsmIratFromLteInd();

    /* 按约定此处填BUTT，MSCC可以区分是从LTE重选还是回退HRPD */
    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_BUTT);

    /* 状态迁移到CNAS_HSD_L1_STA_IDLE */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_IDLE);
    /* Inactive下启动L2 异系统子状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_INTER_SYS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc
 功能描述  : CL切换到HRPD制式下的结果处理
 输入参数  : ucRslt                     -- C-L结果
             enNetworkLostReason        -- lost原因值
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年09月18日
     作    者   : z00316370
     修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
)
{
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;

    pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

    if (VOS_TRUE == ucRslt)
    {
        /* 状态迁移到CNAS_HSD_L1_STA_IDLE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_IDLE);

        /* 初始化OOC上下文信息 */
        CNAS_HSD_InitOocCtxInfo();

        /* 停止OOC下搜网定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);
    }
    else
    {
        switch (enNetworkLostReason)
        {
            case CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT:
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);
                if (0 == pstRedirection->ucChanNum)
                {
                    /* 发起搜网 */
                    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
                }
                else
                {
                    /* 发起搜网 */
                    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION, 0, VOS_NULL_PTR);
                }
                break;
            case CAS_CNAS_HRPD_NETWORK_LOST_NORMAL_ACS:
            case CAS_CNAS_HRPD_NETWORK_LOST_NORMAL_OTHER:
            case CAS_CNAS_HRPD_NETWORK_LOST_ABNORMAL:
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);
                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
                break;
            /* NO RF 处理 */
            case CAS_CNAS_HRPD_NETWORK_LOST_NO_RF:
                CNAS_HSD_RcvCasNoRFInd_Proc();
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);
                break;
            default:
                /* 状态迁移到CNAS_HSD_L1_STA_OOC */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

                CNAS_HSD_SetOocSearchScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);
                CNAS_HSD_ProcOocSchedule(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);
                break;
        }
    }

}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvInterSysRsltCnf_Inactive
 功能描述  : 处理ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF请求消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年06月02日
     作    者   : z00316370
     修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvInterSysRsltCnf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU                   *pstRsltMsg;

    pstRsltMsg  = (CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU *)pstMsg;

    if (VOS_RATMODE_HRPD == pstRsltMsg->enCampedRatMode)
    {
        CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(pstRsltMsg->ucRslt,
                                            pstRsltMsg->enNetworkLostReason);

    }
    /* LTE主模，HRPD为INACTIVE态 */
    else
    {}

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvInterSysRsltCnf_Idle
 功能描述  : IDLE态处理ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF请求消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年07月01日
     作    者   : z00316370
     修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvInterSysRsltCnf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU                   *pstRsltMsg;

    pstRsltMsg  = (CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU *)pstMsg;

    if (VOS_RATMODE_HRPD == pstRsltMsg->enCampedRatMode)
    {
        CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(pstRsltMsg->ucRslt,
                                            pstRsltMsg->enNetworkLostReason);
    }
    /* LTE主模，HRPD为INACTIVE态 */
    else
    {
        /* 清除HRPD搜网状态 */
        CNAS_HSD_ClearHrpdSysAcqStatusBits();

        /* 状态迁移到CNAS_HSD_L1_STA_IDLE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasSuspendInd_Idle
 功能描述  : 处理ID_CAS_CNAS_HRPD_SUSPEND_IND请求消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年06月02日
     作    者   : z00316370
     修改内容   : 新生成函数
   1.日    期   : 2015年11月13日
     作    者   : y00346957
     修改内容   : DTS2015070910837修改，intersys cause 枚举统一用mscc pif中的
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSuspendInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndHsmSuspendInd();

    CNAS_HSD_SndMsccInterSysStartInd(VOS_RATMODE_HRPD,
                                     VOS_RATMODE_LTE,
                                     NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT);

    /* Inactive下启动L2 异系统子状态机 */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_INTER_SYS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SubnetIdChkProc
 功能描述  : 异系统切换到HRPD时的有效性判断
 输入参数  : pstHrpdSys         HRPD系统信息
 输出参数  : VOS_VOID

 返 回 值  : VOS_TRUE           - 相关联
             VOS_FALSE          - 不相关联
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月08日
    作    者   : z00316370
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_HrpdSubnetIdChkProc(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    CNAS_HSD_ASSN_RLST_ENUM_UINT32      enAssnRlst;

    /* 有关联的HRPD系统，但是在HRPD系统中没有频点，此判断逻辑是返回CNAS_HSD_NO_ASSN_FREQ
        而重定向到HRPD系统时，这样的判断逻辑是否合理???
        即重定向的频点属于的HRPD系统是关联的，但是不在PRL表中，现在的判断逻辑是失败，是否合理??? */
    enAssnRlst = CNAS_HSD_CheckHrpdSysAssnWith1X(pstHrpdSys);

    if (CNAS_HSD_ASSN_SUCC != enAssnRlst)
    {
        return VOS_FALSE;
    }

    /* 若关联，还需判断是否avoid的频点 */
    CNAS_HSD_CheckExpiredFreqFromAvoidList();

    if (VOS_TRUE == CNAS_HSD_IsCurFreqAvoided(&(pstHrpdSys->stFreq)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive
 功能描述  : 处理ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ请求消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
   1.日    期   : 2015年06月25日
     作    者   : z00316370
     修改内容   : 新生成函数
   2.日    期   : 2015年12月18日
     作    者   : z00316370
     修改内容   : INACTIVE下也支持快搜
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU  *pstDataCallRedialReq;

    pstDataCallRedialReq = (MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU*)pstMsg;

    if (NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE == pstDataCallRedialReq->enCause)
    {
        /* 设置L1状态机进入搜网状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* 快速搜网 */
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNoRF_Idle
 功能描述  : 收到RRM NO RF状态指示的时候，如果当前处于NO RF,则向MSCC透传Status Ind消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNoRFInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理NO RF */
    CNAS_HSD_RcvCasNoRFInd_Proc();

    /* 在IDLE 状态时收到NO_RF，不再进行恢复搜网，而是重新建表，所以将场景重置成BUTT */
    CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_BUTT);

    /* 状态迁移到CNAS_HSD_L1_STA_OOC */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNoRFInd_Proc
 功能描述  : IDLE态收到RRM NO RF状态指示的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvCasNoRFInd_Proc(VOS_VOID)
{
    /* 保存NORF的场景 */
    CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);

    /* 向RRM发起注册,RF可用后RRM会通知HSD */
    CNAS_HSD_SndRrmRegisterInd(RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH);

    /* 开启保护定时器 */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND, TI_CNAS_HSD_WAIT_RRM_STATUS_IND_LEN);

    if (VOS_TRUE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_HSD_SndMsccRfAvailInd(VOS_FALSE);

        /* 设置当前RF可用标记为:RF不可用 */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_FALSE);
    }

    /* 給MSCC 发送END 消息告诉MSCC 去搜LTE WENXIAO 要求增加这条消息*/
    CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvRrmStatusInd_Deactive
 功能描述  : 收到RRM NO RF状态指示的时候，如果当前处于NO RF,则向MSCC透传Status Ind消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvRrmStatusInd_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 判断RF可用标记 */
    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* 当前处于NO RF 向MSCC透传消息,不触发搜网 */
        CNAS_HSD_SndMsccRfAvailInd(VOS_TRUE);

        /* 设置当前RF可用标记为:RF可用 */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvRrmStatusInd_Ooc
 功能描述  : 收到RRM NO RF状态指示的时候，发起搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvRrmStatusInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enScene;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pstNew1xSystem;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pstScanList1xSystem;
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enNoRfUeStatus;
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enCur1xUeStatus;
    VOS_UINT32                          ulIs1XSysMatched    = VOS_FALSE;
    VOS_UINT32                          ulIs1XNoChanged     = VOS_FALSE;

    pstNew1xSystem      = CNAS_HSD_Get1xSystemInfo();
    pstScanList1xSystem = CNAS_HSD_GetScanListMatched1xSystemInfo();
    enCur1xUeStatus     = CNAS_CCB_GetCasState();

    /* 如果当前处于NO RF状态，则触发搜网 */
    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        enScene = CNAS_HSD_GetNoRfScene();

        if (CNAS_HSD_SYS_ACQ_SCENE_BUTT >= enScene)
        {

            CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_BUTT);
            enNoRfUeStatus      = CNAS_HSD_GetNoRf1XUeStatus();

            ulIs1XSysMatched    = CNAS_HSD_Is1xSysStillMatchHrpdSearchList(&pstScanList1xSystem->st1xSys,&pstNew1xSystem->st1xSys);

            /* NO_RF前后都是丢网认为没有变化 */
            if (((CNAS_CCB_1X_CAS_INIT_STATE == enNoRfUeStatus) || (CNAS_CCB_1X_CAS_NO_SERVICE_STATE == enNoRfUeStatus))
            && ((CNAS_CCB_1X_CAS_INIT_STATE == enCur1xUeStatus) || (CNAS_CCB_1X_CAS_NO_SERVICE_STATE == enCur1xUeStatus)))
            {
                ulIs1XNoChanged = VOS_TRUE;
            }
            else if (((CNAS_CCB_1X_CAS_INIT_STATE != enNoRfUeStatus) && (CNAS_CCB_1X_CAS_NO_SERVICE_STATE != enNoRfUeStatus))
                   &&((CNAS_CCB_1X_CAS_INIT_STATE != enCur1xUeStatus) && (CNAS_CCB_1X_CAS_NO_SERVICE_STATE != enCur1xUeStatus))
                   &&( VOS_TRUE == ulIs1XSysMatched ))
            {
                /* 如果NO_RF前后都是在网，而且1x没有变化，则不需要重新建表 */
                ulIs1XNoChanged = VOS_TRUE;
            }
            else
            {

                ulIs1XNoChanged = VOS_FALSE;
            }

            /* 如果 1X没有变更(NO_RF前后都是不存在，或者都存在还是匹配)，不是快速搜 不是IDLE态下NO_RF,才进行恢复搜网 */
            if ((VOS_TRUE == ulIs1XNoChanged)
            &&  (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK != enScene)
            &&  (CNAS_HSD_SYS_ACQ_SCENE_BUTT            != enScene))
            {
                /* 设置L1状态机进入INITIAL状态 */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_NO_RF_RESUME, 0, VOS_NULL_PTR);

            }
            else
            {
                /* 1x 变更 需要开机搜网 */
                /* 设置L1状态机进入INITIAL状态 */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
            }


        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir
 功能描述  : initial状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF消息的处理
 输入参数  : pstSysAcqRslt

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* 设置L1状态机进入搜网状态 */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    /* 发起搜网 */
    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION, 0, VOS_NULL_PTR);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_CovertSessionType_PreProc
 功能描述  : 将HSM_HSD之间的session type转换为HSD_MSCC之间的session type
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : m00312079
    修改内容   : 新生成函数
*****************************************************************************/
HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32 CNAS_HSD_CovertSessionType_Proc(
    HSM_HSD_SESSION_RELEASE_TYPE_ENUM_UINT8                 enSessionRelType
)
{
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32               enCurrSessionRelType;

    enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_BUTT;

    if (HSM_HSD_SESSION_RELEASE_TYPE_0 == enSessionRelType)
    {
        enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_0;
    }
    else if (HSM_HSD_SESSION_RELEASE_TYPE_A == enSessionRelType)
    {
        enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_A;
    }
    else
    {
        enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_BUTT;
    }

    return enCurrSessionRelType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsmSessionNegResultInd_PreProc
 功能描述  : idle状态收到ID_HSM_HSD_SESSION_NEG_RESULT_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : x00306642
    修改内容   : 新生成函数
  2.日    期   : 2015年2月11日
    作    者   : w00208541
    修改内容   : CDMA Iteration 8 增加协商结果上报到MSCC
  3.日    期   : 2015年04月06日
    作    者   : z00316370
    修改内容   : CDMA Iteration 10 增加当前状态判断
  4.日    期   : 2015年06月03日
    作    者   : l00324781
    修改内容   : CDMA Iteration 12 CNAS_HSD_SndMsccSessionNegRsltInd 增加参数
  5.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsmSessionNegResultInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                         enReAcqFlag;
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32               enCurrSessionRelType;

    pstSessionNegRlstInd = (HSM_HSD_SESSION_NEG_RESULT_IND_STRU*)pstMsg;
    stFreq.enBandClass   = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.enBandClass;
    stFreq.usChannel     = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.usChannel;
    enReAcqFlag          = CNAS_HSD_NOT_NEED_REACQ;

    /* avoid模块处理 */
    CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(pstSessionNegRlstInd, &stFreq, &enReAcqFlag);

    /* 是否需要重新搜网 */
    if (CNAS_HSD_NEED_REACQ == enReAcqFlag)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);

        CNAS_HSD_SndMsccHrpdNoSrvInd();

    }
    /* 成功给MSCC上班session结果 */
    else if (HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE != pstSessionNegRlstInd->enNegResult)
    {
        enCurrSessionRelType = CNAS_HSD_CovertSessionType_Proc(pstSessionNegRlstInd->enSessionRelType);

        CNAS_HSD_SndMsccSessionNegRsltInd(pstSessionNegRlstInd->enNegResult,
                                          pstSessionNegRlstInd->ucIsNewSession,
                                          enCurrSessionRelType,
                                          pstSessionNegRlstInd->ucIsEhrpdSupport);
    }
    else
    {}

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysAcqStatusByAcqScene
 功能描述  : 根据搜网场景返回当前搜网控制位状态
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月09日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetAcqSceneBySysAcqStatus(VOS_VOID)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;

    enSysAcqStatus = CNAS_HSD_GetSysAcqStatus();

    if ( CNAS_HSD_SYS_ACQ_POWER_ON_RCV == enSysAcqStatus)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON;
    }
    else if(CNAS_HSD_SYS_ACQ_HIGH_PRI_RCV == enSysAcqStatus)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY;
    }
    else if ( CNAS_HSD_SYS_ACQ_OTHER_RCV == enSysAcqStatus)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER;
    }
    else
    {
        return CNAS_HSD_SYS_ACQ_SCENE_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SetSysAcqStatusByAcqScene
 功能描述  : 根据搜网场景设置当前搜网控制位状态
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月09日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysAcqStatusByAcqScene(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    if (CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON == enSysAcqScene)
    {
        CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_POWER_ON_SYS_ACQ);
    }
    else if(CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == enSysAcqScene)
    {
        CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_HIGH_PRI_SYS_ACQ);
    }
    else
    {
        CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_OTHER_SYS_ACQ);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsmConnOpenInd_Idle
 功能描述  : 收到CAS_CNAS_HRPD_ACCESS_RLST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月06日
    作    者   : z00316370
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsmConnOpenInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenInd;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    CNAS_HSD_REACQ_FALG_ENUM_UINT32     enReAcqFlag;

    pstOpenInd              = (HSM_HSD_CONN_OPEN_IND_STRU *)pstMsg;
    stFreq.enBandClass      = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.enBandClass;
    stFreq.usChannel        = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.usChannel;
    enReAcqFlag             = CNAS_HSD_NOT_NEED_REACQ;

    /* avoid模块处理 */
    CNAS_HSD_ProcAvoidEventInAccessRlstInd(pstOpenInd, &stFreq, &enReAcqFlag);

    /* 是否需要重新搜网 */
    if (CNAS_HSD_NEED_REACQ == enReAcqFlag)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}
/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



