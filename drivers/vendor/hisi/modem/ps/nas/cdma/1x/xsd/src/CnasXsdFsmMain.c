/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmMain.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD L1主状态机下收到各事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXsdFsmMain.h"
#include  "CnasXsdFsmMainTbl.h"
#include  "CnasXsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "CnasPrlApi.h"
#include  "CnasCcb.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXsdSndXreg.h"

#include  "CnasXsdSndXcc.h"
#include  "CnasXsdMntn.h"
#include  "NasOmInterface.h"
#include "CnasXsdSysAcqStrategy.h"
#include  "CnasXsdSndMscc.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                        PS_FILE_ID_CNAS_XSD_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*****************************************************************************/
typedef VOS_VOID  (*pCNasXsdSystemDetermineIndProcFunc)(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU   *pstSdIndInfo
);

typedef struct
{
    VOS_UINT32                                  ulSdReason;
    pCNasXsdSystemDetermineIndProcFunc          pFuncSDIndProc;
}CNAS_XSD_SYSTEM_DETERMINE_IND_PROC_TBL_FUNC;

CNAS_XSD_SYSTEM_DETERMINE_IND_PROC_TBL_FUNC                 g_astCnasXsdSystemDetermineIndL1MainProcFuncTbl[] =
{
    {CAS_CNAS_1X_SD_RESCAN_IND,                         CNAS_XSD_ProcCasSystemDetermineIndWithRescanReason_Idle},
    {CAS_CNAS_1X_SD_PROTO_MISMATCH_IND,                 CNAS_XSD_ProcCasSystemDetermineIndWithProtoMismatchReason_Idle},
    {CAS_CNAS_1X_SD_SYS_LOST_IND,                       CNAS_XSD_ProcCasSystemDetermineIndWithSysLostReason_Idle},
    {CAS_CNAS_1X_SD_LOCK_IND,                           CNAS_XSD_ProcCasSystemDetermineIndWithLockReason_Idle},
    {CAS_CNAS_1X_SD_UNLOCK_IND,                         CNAS_XSD_ProcCasSystemDetermineIndWithUnlockReason_Idle},
    {CAS_CNAS_1X_SD_ACCESS_DENIED_IND,                  CNAS_XSD_ProcCasSystemDetermineIndWithAccessDeniedReason_Idle},
    {CAS_CNAS_1X_SD_ACCT_BLOCKED_IND,                   CNAS_XSD_ProcCasSystemDetermineIndWithAcctBlockReason_Idle},
    {CAS_CNAS_1X_SD_NDSS_OFF_IND,                       CNAS_XSD_ProcCasSystemDetermineIndWithNdssOffReason_Idle},
    {CAS_CNAS_1X_SD_ERR_IND,                            CNAS_XSD_ProcCasSystemDetermineIndWithErrReason_Idle},
    {CAS_CNAS_1X_SD_REDIR_IND,                          CNAS_XSD_ProcCasSystemDetermineIndWithRedirectionReason_Idle},
    {CAS_CNAS_1X_SD_REGIST_REJ_IND,                     CNAS_XSD_ProcCasSystemDetermineIndWithRegistRejReason_Idle},
    {CAS_CNAS_1X_SD_RELEASE_IND,                        CNAS_XSD_ProcCasSystemDetermineIndWithReleaseReason_Idle},
    {CAS_CNAS_1X_SD_RESELECTION_IND,                    CNAS_XSD_ProcCasSystemDetermineIndWithReselectionReason_Idle},
    {CAS_CNAS_1X_SD_SYSTEM_RESELECTION_IND,             CNAS_XSD_ProcCasSystemDetermineIndWithSystemReselectionReason_Idle},
    {CAS_CNAS_1X_SD_NEW_SYSTEM_IND,                     CNAS_XSD_ProcCasSystemDetermineIndWithNewSystemReason_Idle},
    {CAS_CNAS_1X_SD_MAX_ACCESS_FAILURE,                 CNAS_XSD_ProcCasSystemDetermineIndWithMaxAccessFailureReason_Idle},
    {CAS_CNAS_1X_SD_ABNORMAL_IND,                       CNAS_XSD_ProcCasSystemDetermineIndWithAbnormalReason_Idle},
    {CAS_CNAS_1X_SD_NO_RF,                              CNAS_XSD_ProcCasSystemDetermineIndWithNoRfReason_Idle},
    {CAS_CNAS_1X_SD_ACQUISITION_FAIL,                   CNAS_XSD_ProcCasSystemDetermineIndWithAcquisitionFail_Idle},
};



/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvStartReq_Null
 功能描述  : 处理在null状态收到开机请求事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动L2开机状态机 */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvSwitchOnRsltCnf_Null
 功能描述  : 收到开机结果后，若成功迁移到CNAS_XSD_L1_STA_INITIAL状态，
             失败保持CNAS_XSD_L1_STA_NULL状态
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvSwitchOnRsltCnf_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU                    *pstSwitchOnMsg = VOS_NULL_PTR;

    pstSwitchOnMsg = (CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU *)pstMsg;

    /* 收到开机结果后，若成功迁移到CNAS_XSD_L1_STA_INITIAL状态，
       失败保持CNAS_XSD_L1_STA_NULL状态
    */
    if (CNAS_XSD_SWITCH_ON_RESULT_SUCCESS == pstSwitchOnMsg->enRslt)
    {
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvSwitchOnRsltCnf_Null:switch on fail");
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvPowerOffReq_Null
 功能描述  : 处理在null状态收到关机请求事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月11日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接回复关机结果给MSCC */
    CNAS_XSD_SndMsccPowerOffCnf();

    return VOS_TRUE;

}


VOS_UINT32 CNAS_XSD_RcvStartReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* If XSD receives a Power On request In L1Main initial state
        then XSD sends Power On success Result to MSCC */
    CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvPowerOffReq_L1Main
 功能描述  : 收到ID_MSCC_XSD_POWER_OFF_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 启动L2关机状态机 */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_POWER_OFF);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvPowerOffReq_Initial
 功能描述  : 处理在initial状态收到L2 power off关机确认事件
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数

 2. Date      : 2015-04-11
    Author    : a00295761
    Content   : Added Result  Enum to also process Power save CNf internal message.

 3.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvPowerOffRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU                   *pstPowerOffRsltCnf = VOS_NULL_PTR;

    pstPowerOffRsltCnf = (CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    if (CNAS_XSD_POWEROFF_REASON_POWER_OFF == pstPowerOffRsltCnf->enPowerOffReason)
    {
        /* 释放保存的GEO搜索列表的buffer */
        CNAS_XSD_FreeBufferOfGeoSrchList();

        /* 停止XSD所有定时器 */
        CNAS_StopAllTimerWithSpecifiedPid(UEPS_PID_XSD);

        /* 开机时判断是否需初始化PRL */

        /* 初始化XSD模块CTX */
        CNAS_XSD_InitCtx(CNAS_XSD_INIT_CTX_POWEROFF);

        /* 状态迁移到CNAS_XSD_L1_STA_NULL */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_NULL);
    }
    else if (CNAS_XSD_POWEROFF_REASON_POWER_SAVE == pstPowerOffRsltCnf->enPowerOffReason)
    {
        /* Stop all timers except slice reverse protect timer */
        CNAS_XSD_StopAllTimerExceptSpecifiedTimerId(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);

        /* Send Power Save Cnf to MSCC */
        if (CNAS_XSD_POWEROFF_RSLT_SUCCESS == pstPowerOffRsltCnf->enRslt)
        {
            CNAS_XSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_1X_POWER_SAVE, UEPS_PID_XSD);


            /* Set Next State to Deactive State */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_DEACTIVE);
        }
        else
        {
            CNAS_XSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_FAILURE);
        }
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvPowerOffRsltCnf_L1Main: Invalid Result!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvSysAcqReq_Initial
 功能描述  : initial状态收到ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoList = VOS_NULL_PTR;

    /* 开机进入捕获状态机之前，获取PRL表GEO个数及对应的系统表中的首个索引 */
    pstGeoList = CNAS_XSD_GetGeoSrchListInfoAddr();
    CNAS_XSD_GetGeoListFromPrlSysRecordInfo(pstGeoList);

    /* log GEO list搜索状态 */
    CNAS_XSD_LogGeoListSrchStatus(pstGeoList);

    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 申请射频资源 */
    CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

    /* 启动L2 System Acquire状态机, Reference to CDG 130 Figure 5-4 Example System Selection */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvInternalSysAcqReq_Initial
 功能描述  : initial状态收到ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月7日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2015年12月21日
    作    者   : w00242748
    修改内容   : DTS2015121511023:call release申请的资源优先级需提高

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvInternalSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq         = VOS_NULL_PTR;
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    pstIntSysAcqReq = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstMsg;

    enSessionType   = CNAS_CAS_1X_SESSION_TYPE_ENUM_BUTT;

    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == pstIntSysAcqReq->enSysAcqScene)
    {
        enSessionType = CNAS_CAS_1X_SESSION_TYPE_TCH_REL_NETWORK_SEARCH;
    }
    else
    {
        enSessionType = CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH;
    }

    /* 申请射频资源 */
    CNAS_XSD_SndCasBeginSessionNotify(enSessionType);

    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 启动L2 System Acquire状态机 */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SYS_ACQ);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvSysAcqRsltCnf_Initial
 功能描述  : initial状态收到CNAS_XSD_L1_STA_IDLE消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月29日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 6 Modified
  3.日    期   : 2015年1月5日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能与OOC系统捕获调度机制
  4.日    期   : 2015年5月30日
    作    者   : h00313353
    修改内容   : 迭代15 DSDS

  5.日    期   : 2015年7月21日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvSysAcqRsltCnf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt = VOS_NULL_PTR;
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    pstSysAcqRslt = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU *)pstMsg;

    enSessionType   = CNAS_CAS_1X_SESSION_TYPE_ENUM_BUTT;

    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == pstSysAcqRslt->enCurAcqScene)
    {
        enSessionType = CNAS_CAS_1X_SESSION_TYPE_TCH_REL_NETWORK_SEARCH;
    }
    else
    {
        enSessionType = CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH;
    }

    /* 申请射频资源 */
    CNAS_XSD_SndCasEndSessionNotify(enSessionType);

    if (CNAS_XSD_SYSTEM_ACQUIRED_RESULT_SUCCESS == pstSysAcqRslt->enRslt)
    {
        CNAS_XSD_ProcSearchNetworkRslt_Succ(pstSysAcqRslt);

        CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_1X_SYS_ACQUIRE_SUCCESS, UEPS_PID_XSD);
    }
    else if (CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED == pstSysAcqRslt->enRslt)
    {
        CNAS_XSD_ProcSearchNetworkRslt_Abort(pstSysAcqRslt);

        CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_1X_SYS_LOST, UEPS_PID_XSD);
    }
    else
    {
        CNAS_XSD_ProcSearchNetworkRslt_Fail(pstSysAcqRslt);

        CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_1X_SYS_LOST, UEPS_PID_XSD);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Idle
 功能描述  : initial状态收到MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月17日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    /* 语音呼和数据呼处理 */
    if ((NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL == pstCallRedialNtfMsg->enCallType)
     || (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL  == pstCallRedialNtfMsg->enCallType))
    {
        if (VOS_NULL_PTR == CNAS_XSD_GetCallRedialScanChanListAddr()->pstScanChanInfo)
        {
            return VOS_TRUE;
        }

        /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        /*发送搜网内部请求消息 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* 对冲场景处理: 若携带的原因值为NO SERVICE，不触发搜网 */
    if (NAS_MSCC_PIF_CDMA_CALL_CAUSE_INTERNAL_NO_SERVICE == pstCallRedialNtfMsg->enCause)
    {
        return VOS_TRUE;
    }

    /* 紧急呼处理 */
    if (VOS_NULL_PTR == CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        return VOS_TRUE;
    }

    CNAS_XSD_ProcEmcRedialSysAcq_Idle();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcEmcRedialSysAcq_Idle
 功能描述  : 处理紧急呼叫重拨
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcEmcRedialSysAcq_Idle()
{

    VOS_UINT32                                              ulIndex;
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstSysCampedSysInfo   = VOS_NULL_PTR;

    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();
    pstSysCampedSysInfo   = CNAS_XSD_GetCurCampedSysInfo();

    /* 搜索到了新的系统，重新计数 */
    if ((pstSysCampedSysInfo->stSystem.usSid              != pstEmcRedialSysAcqCfg->stLastCampedSys.usSid)
     || (pstSysCampedSysInfo->stSystem.usNid              != pstEmcRedialSysAcqCfg->stLastCampedSys.usNid)
     || (pstSysCampedSysInfo->stSystem.stFreq.enBandClass != pstEmcRedialSysAcqCfg->stLastCampedSys.stFreq.enBandClass)
     || (pstSysCampedSysInfo->stSystem.stFreq.usChannel   != pstEmcRedialSysAcqCfg->stLastCampedSys.stFreq.usChannel))
    {
        pstEmcRedialSysAcqCfg->ucRedialCount = 0;

        NAS_MEM_CPY_S(&(pstEmcRedialSysAcqCfg->stLastCampedSys),
                      sizeof(CNAS_PRL_1X_SYSTEM_STRU),
                      &(pstSysCampedSysInfo->stSystem),
                      sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    }

    /* 获取当前系统在mru list中的索引 */
    ulIndex = 0;


    if ((VOS_TRUE == CNAS_XSD_GetCurSysIndexOfEmcRedialMruList(&(pstSysCampedSysInfo->stSystem), &ulIndex))
     && (pstEmcRedialSysAcqCfg->ucRedialCount < pstEmcRedialSysAcqCfg->aucRedialTimes[ulIndex]))
    {
        pstEmcRedialSysAcqCfg->ucRedialCount++;
    }
    else
    {
        /* 当前驻留频点在mru列表中，重拨次数大于该场景下的应重拨的次数，或者当前驻留频点不在mru列表，发起搜网*/

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvInternalSysAcqReq_Idle
 功能描述  : Idle状态收到ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月09日
    作    者   : m00312079
    修改内容   : 新生成函数
  2.日    期   : 2015年12月21日
    作    者   : w00242748
    修改内容   : DTS2015121511023:call release申请的资源优先级需提高
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvInternalSysAcqReq_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq         = VOS_NULL_PTR;
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    pstIntSysAcqReq = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstMsg;

    enSessionType   = CNAS_CAS_1X_SESSION_TYPE_ENUM_BUTT;

    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == pstIntSysAcqReq->enSysAcqScene)
    {
        enSessionType = CNAS_CAS_1X_SESSION_TYPE_TCH_REL_NETWORK_SEARCH;
    }
    else
    {
        enSessionType = CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH;
    }

    /* 申请射频资源 */
    CNAS_XSD_SndCasBeginSessionNotify(enSessionType);

    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 启动L2 System Acquire状态机 */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SYS_ACQ);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Ooc
 功能描述  : ooc状态收到MMA_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年01月4日
    作    者   : y00245242
    修改内容   : 增加OOC系统捕获调度机制

  3.日    期   : 2015年7月17日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    /* 语音呼和数据呼处理 */
    if ((NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL == pstCallRedialNtfMsg->enCallType)
     || (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL  == pstCallRedialNtfMsg->enCallType))
    {
        /* if scan list is null, nothing to do */
        if (VOS_NULL_PTR == CNAS_XSD_GetCallRedialScanChanListAddr()->pstScanChanInfo)
        {
            return VOS_TRUE;
        }

        /* 停止所有OOC下定时器 */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_TIMER);

        CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER);


        /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        /*发送搜网内部请求消息 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* 紧急呼流程 */
    if (VOS_NULL_PTR == CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        return VOS_TRUE;
    }

    /* 停止所有OOC下定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_TIMER);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER);


    /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /*发送搜网内部请求消息 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Initial
 功能描述  : Initial状态收到MMA_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼

  3.日    期   : 2015年7月20日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32                     enSrvStatus;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    /* 退出CallBack状态 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 停止CALLBACK保护定时器 */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER);
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

        CNAS_XSD_QuitCallBackMode();
    }

    /* 语音呼和数据呼处理 */
    if ((NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL == pstCallRedialNtfMsg->enCallType)
     || (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL  == pstCallRedialNtfMsg->enCallType))
    {
        /*******************************************************************************************
        * 注: 下面场景是处理收到呼叫语音或数据重拨时，此时XSD正在搜网状态机中等待CAS的overheader消息
        *     上报, 当XSD等待到overheader消息后，退出L2状态机处理搜网结果时，并不迁移状态。在此状态下
        *     (initial状态)，处理缓存队列中的重拨消息时，如果已经驻留成功，且是normal serice，不需要
        *     再触发搜网，直接使用当前驻留到的系统上发起呼叫就可以了
        *******************************************************************************************/
        enSrvStatus = CNAS_XSD_GetCurSrvStatus();
        if ((VOS_TRUE                               == CNAS_XSD_GetSystemCampOnFlag())
         && (CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE == enSrvStatus))
        {
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

            CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

            return VOS_TRUE;
        }

        /* if scan list is null, nothing to do */
        if (VOS_NULL_PTR == CNAS_XSD_GetCallRedialScanChanListAddr()->pstScanChanInfo)
        {
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);

            /* abornormal protect,satrt availablt timer here */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_AVAILABLE_TIMER, TI_CNAS_XSD_AVAILABLE_LEN);

            return VOS_TRUE;
        }

        /*发送搜网内部请求消息 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* 紧急呼流程处理 */
    /* 紧急呼搜网打断当前搜网，搜网成功，紧急呼可利用当前的搜网结果 */
    if (VOS_TRUE == CNAS_XSD_GetSystemCampOnFlag())
    {
        CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

        return VOS_TRUE;
    }

    /* 未构表的异常情况处理 */
    if (VOS_NULL_PTR == CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);

        CNAS_XSD_StartTimer(TI_CNAS_XSD_AVAILABLE_TIMER, TI_CNAS_XSD_AVAILABLE_LEN);

        return VOS_TRUE;
    }

    /* 启动紧急呼重拨搜网 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvSysDeterminInd_Idle
 功能描述  : idle状态收到ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified
  3.日    期   : 2015年10月10日
    作    者   : l00324781
    修改内容   : CDMA Iteration 18 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvSysDeterminInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd       = VOS_NULL_PTR;
    pCNasXsdSystemDetermineIndProcFunc                      pfunSdProc;
    VOS_UINT32                                              i;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    pfunSdProc = VOS_NULL_PTR;

    for (i = 0; i < (sizeof(g_astCnasXsdSystemDetermineIndL1MainProcFuncTbl)/sizeof(CNAS_XSD_SYSTEM_DETERMINE_IND_PROC_TBL_FUNC)); i++)
    {
        if (pstSysDeterminInd->enSdReason == g_astCnasXsdSystemDetermineIndL1MainProcFuncTbl[i].ulSdReason)
        {
            pfunSdProc = g_astCnasXsdSystemDetermineIndL1MainProcFuncTbl[i].pFuncSDIndProc;
            break;
        }
    }

    if (VOS_NULL_PTR != pfunSdProc)
    {
        pfunSdProc(pstSysDeterminInd);
    }
    else
    {
        /*如果原因值不在搜网场景列表中，默认OOC场景搜网*/
        CNAS_XSD_ProcCasSystemDetermineIndWithSysLostReason_Idle(pstSysDeterminInd);
    }

    /* 消息处理完后，如果发起搜网，向MSCC上报无服务，MSCC通知MMA，MMA启动延时上报定时器 */
    if (VOS_TRUE == CNAS_XSD_IsNeedReportNoService(pstSysDeterminInd))
    {
        CNAS_XSD_SndMscc1xNoSrvInd();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasOhmInd_Idle
 功能描述  : idle状态收到ID_CAS_CNAS_1X_OHM_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月17日
    作    者   : y00245242
    修改内容   : iteration 17开发

  3.日    期   : 2015年9月23日
    作    者   : y00245242
    修改内容   : DTS2015091901326

  4.日    期   : 2015年11月30日
    作    者   : h00313353
    修改内容   : DTS2015101200488

  5.日    期   : 2015年12月15日
    作    者   : l00324781
    修改内容   : CL_MUTIMODE_OPTIMIZE修改
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasOhmInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_OHM_IND_STRU           *pstOhmInd       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsNegSys;
    VOS_UINT32                          ulIsCallOrigSysExist;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    /* 根据XCC状态判断当前是否存在业务态，若在业务态，Negative系统，也暂不搜网 */
    VOS_UINT32                          ulIsCurCallStateIdle;

    ulIsCurCallStateIdle                = CNAS_CCB_IsCurCallStateIdle();

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0x00, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    ulIsCallOrigSysExist                = CNAS_XSD_IsEmcCallOriginalSysExist();

    pstOhmInd       = (CAS_CNAS_1X_OHM_IND_STRU *)pstMsg;

    stCurSysInfo.usSid              = pstOhmInd->usSid;
    stCurSysInfo.usNid              = pstOhmInd->usNid;
    stCurSysInfo.stFreq.enBandClass = pstOhmInd->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstOhmInd->usFreq;

    /***********************************************************************************************
     * 1. 更新当前系统频点到历史同步成功频点的频点列表中
     **********************************************************************************************/
    CNAS_XSD_UpdateHistorySyncedSysFreqList(&(stCurSysInfo.stFreq));

    CNAS_PRL_Get1xSysGeoList(&stCurSysInfo, &stGeoListInfo);

    if (VOS_FALSE == CNAS_PRL_Is1xSysNegativeInPrl(&stCurSysInfo, &stGeoListInfo))
    {
        CNAS_CCB_SetCdmaOhmFreq(&(stCurSysInfo.stFreq));
    }

    /***********************************************************************************************
     * 2. check当前系统是否是negative，如果是negative系统，且无紧急呼存在，则需要重新搜索
     **********************************************************************************************/
    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo,
                                                 pstOhmInd->enServiceInfoIncl,
                                                 pstOhmInd->stServiceInfo.usMcc);


    if ((VOS_NULL_PTR   == CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
     && (VOS_FALSE      == ulIsCallOrigSysExist)
     && (VOS_TRUE       == ulIsNegSys)
     && (VOS_TRUE       == ulIsCurCallStateIdle))
    {
        CNAS_XSD_SndMsccSidNidInd(stCurSysInfo.usSid, stCurSysInfo.usNid);

        /* 如果是neg系统发起重新搜网 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    CNAS_XSD_ProcCasOhmInd(pstOhmInd, ulIsNegSys);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiAvailTimerExpired_Ooc
 功能描述  : OOC状态下available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 增加OOC系统捕获调度机制

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_HRPD_SYSTEM_STRU           stPrlHrpdSystem;
    VOS_UINT16                          usAvailTimerLen;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;
 
    NAS_MEM_SET_S(&stPrlHrpdSystem, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU), 0x0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));  

    if (VOS_TRUE == CNAS_XSD_GetTestConfig()->ucIsMod1xAvailTimerLen)
    {
        pstOocScheduleInfo  = CNAS_XSD_GetOocScheduleInfo();
        usAvailTimerLen     = CNAS_XSD_GetNextOocScheduleTimerLen(CNAS_XSD_GetOocScheduleInfo());
    
        
        if ((0   != PS_MEM_CMP(&stPrlHrpdSystem, CNAS_HSD_GetCasOhmHrpdSysAddr(), sizeof(CNAS_PRL_HRPD_SYSTEM_STRU)))
         && (300 != usAvailTimerLen))
        {
            /*间隔设置为5分钟 */
            usAvailTimerLen = 300;

            pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen = 255;
        
            pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase                = 0;
            pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes                = 0;
            pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes    = 10;
            pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen = 300;

            /* 启动OOC available定时器 */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_AVAILABLE_TIMER, (usAvailTimerLen * 1000));
             
            return VOS_TRUE;
         
        } 
    }
   
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_GetOocSearchScene(),
                                  0,
                                  VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvInternalRedirectionInd_Initial
 功能描述  : process the internal redirection indication message in L1_initial state
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvInternalRedirectionInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 申请射频资源 */
    CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 启动L2 redireciton状态机 */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_REDIRECTION);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcRedirectionRsltCnf_Success
 功能描述  : 重定向搜网成功的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : h00313353
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcRedirectionRsltCnf_Success( VOS_VOID )
{
    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_SUCCESS);

        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);
    }

    CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    /* 状态迁移到CNAS_XSD_L1_STA_IDLE */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcRedirectionRsltCnf_Abort
 功能描述  : 重定向搜网结果为Abort的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : h00313353
    修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcRedirectionRsltCnf_Abort( VOS_VOID )
{
    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);

        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);
    }


    /* 缓存中处理状态迁移 */
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcRedirectionRsltCnf_Norf
 功能描述  : 重定向搜网结果为NO RF的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : h00313353
    修改内容   : Create

 2.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcRedirectionRsltCnf_Norf( VOS_VOID )
{
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU   stSysSrvInfo;

    /* 向RRM发起注册,RF可用后RRM会通知XSD */
    CNAS_XSD_RegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

    /* 给MSCC发送System srv Info信息 */
    NAS_MEM_SET_S(&stSysSrvInfo, sizeof(stSysSrvInfo), 0x00, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));
    stSysSrvInfo.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
    CNAS_XSD_SndMsccSysSrvInfoInd(&stSysSrvInfo);

    CNAS_XSD_SetCurSrvStatus(CNAS_XSD_SERVICE_STATUS_NO_SERVICE);

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);

        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);
    }

    if (VOS_TRUE == CNAS_CCB_Get1XRfAvailFlg())
    {
       /* 上报MSCC NO RF消息 */
       CNAS_XSD_SndMsccRfAvailInd(VOS_FALSE);

       /* 记录RF不可用 */
       CNAS_CCB_Set1XRfAvailFlg(VOS_FALSE);
    }

    /* 上报无服务 */
    CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);

    /* 状态迁移到CNAS_XSD_L1_STA_OOC */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcRedirectionRsltCnf_Fail
 功能描述  : 重定向搜网结果为失败，原因不是Abort,NORF的情况处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : h00313353
    修改内容   : Create

  2.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

  3.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcRedirectionRsltCnf_Fail( VOS_VOID )
{
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU   stSysSrvInfo;

    /* 给MSCC发送System srv Info信息 */
    NAS_MEM_SET_S(&stSysSrvInfo, sizeof(stSysSrvInfo), 0x00, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));
    stSysSrvInfo.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
    CNAS_XSD_SndMsccSysSrvInfoInd(&stSysSrvInfo);

    CNAS_XSD_SetCurSrvStatus(CNAS_XSD_SERVICE_STATUS_NO_SERVICE);

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);

        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);
    }

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 上报无服务 */
    CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);


    /* CallBack模式中收到重定向DeterminInd */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 重置计数器 */
        CNAS_XSD_SetEmcCallBackSrchCounter(0);

        /* 启动CAlLBACK模式15s搜网 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST, 0, VOS_NULL_PTR);

        /* 15s CALLBACK搜网保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);

        return;
    }

    /* 紧急呼处理 */
    if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        /* 紧急呼重拨搜网 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

        return;
    }

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_FAIL, 0, VOS_NULL_PTR);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvRedirectionRsltCnf_Initial
 功能描述  : process the result of the redirection state machine in L1_initial state
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

  2.日    期   : 5/1/2015
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能

  3.日    期   : 2015年5月29日
    作    者   : h00313353
    修改内容   : DSDS
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRedirectionRsltCnf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU                 *pstRedirRslt = VOS_NULL_PTR;

    pstRedirRslt = (CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU *)pstMsg;

    /* 释放射频资源 */
    CNAS_XSD_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

    /* 根据结果进行处理 */
    if (CNAS_XSD_REDIRECTION_RESULT_SUCCESS == pstRedirRslt->enRslt)
    {
        CNAS_XSD_ProcRedirectionRsltCnf_Success();
    }
    else if (CNAS_XSD_REDIRECTION_RESULT_ABORTED == pstRedirRslt->enRslt)
    {
        CNAS_XSD_ProcRedirectionRsltCnf_Abort();
    }
    else if (CNAS_XSD_REDIRECTION_RESULT_NORF == pstRedirRslt->enRslt)
    {
        CNAS_XSD_ProcRedirectionRsltCnf_Norf();
    }
    else
    {
        CNAS_XSD_ProcRedirectionRsltCnf_Fail();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithRedirectionReason_Idle
 功能描述  : process the redirection indication from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

  2.日    期   : 8/1/2015
    作    者   : y00245242
    修改内容   : NDSS ORIG功能增加

  3.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼

  4.日    期   : 2015年8月25日
    作    者   : w00176964
    修改内容   : DTS2015082606848:重定向流程参考标杆处理
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithRedirectionReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_CAS_1X_REDIRECTION_INFO_STRU  *pstCasRedirInfo = VOS_NULL_PTR;

    pstCasRedirInfo     = &(pstSysDeterminInd->unSysDeterminInfo.stRedirectionInfo);

    /* 参考标杆处理如下:
       1.无效频段 频点个数不为0,return_if_fail=1,按照CDG143认为是无效重定向,不发起搜网;CAS会设置无效重定向标记;
       2.无效频段 频点个数不为0,return_if_fail=0,按照CDG143发起全频搜并AVOID当前频点30S;
       3.无效频段,频点个数为0,return_if_fail=0,处理同2;
       4.无效频段,频点个数为0,return_if_fail=1,发起全频搜网;
       5.有效频断,频点个数为0,return_if_fail=0,处理同2;
       6.有效频断,频点个数为0,return_if_fail=1,处理同4;
    */

    /* If the redirection message is invalid, clear the redirection flag */
    if (VOS_TRUE == pstCasRedirInfo->ucInvalidRedir)
    {
        /* clear the rediretion falg and stay on the current system */
        CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

        /* 按业务重定向失败处理 */
        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);

        return;
    }

    /* notify CREG to delete zone_lists and sid_nid_lists */
    CNAS_XSD_SndXregRedirInd();

    /* 频段不支持或频点个数为0,作为异常情况,进行全频搜索;对应上述2/3/4/5/6几种场景 */
    if ((VOS_TRUE  == pstCasRedirInfo->ucInvalidBandClass)
     || (0         == pstCasRedirInfo->ucChannelNum))
    {
        /* return_if_fail is false,avoid the current system for 30s */
        if (VOS_FALSE == pstCasRedirInfo->ucReturnIfFail)
        {
            CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_REDIRECTION_WITH_INVALID_GSRDM, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));
        }

        CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        /* 按业务重定向失败处理 */
        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);

        /* 紧急呼未收到Succ场景,进行紧急呼搜网 */
        if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC, 0, VOS_NULL_PTR, VOS_NULL_PTR))
        {
            return;
        }

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM, 0, VOS_NULL_PTR);

        return;
    }

    CNAS_XSD_SetNdssIndFlag(VOS_TRUE);

    /* first clear the existed redirection info */
    CNAS_XSD_InitRedirectionInfo(CNAS_XSD_INIT_CTX_POWEROFF, CNAS_XSD_GetRedirectionInfoAddr());

    /* set the redirection flag to enabled */
    CNAS_XSD_SetRedirectionFlag(VOS_TRUE);

    CNAS_XSD_SetEmcRedirectionFlg();

    /* save the redirection global variables here */
    CNAS_XSD_SaveRedirectionInfo(pstCasRedirInfo);

    /* send the redirection internal message to load the redirection state machine */
    CNAS_XSD_SndInternalRedirInd(CNAS_XSD_GetRedirectionInfoAddr());

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithProtoMismatchReason_Idle
 功能描述  : process system determine indication message with protocol mismatch from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithProtoMismatchReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /* avoid the curret camped frequency fro 60s */
    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_P_REV_MISMATCH, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* check the redirection flag */
    if (VOS_TRUE == CNAS_XSD_GetRedirectionFlag())
    {
        CNAS_XSD_SetEmcRedirectionFlg();

        /* send redirection internal message to load the redirection state machine */
        CNAS_XSD_SndInternalRedirInd(CNAS_XSD_GetRedirectionInfoAddr());

        return;
    }

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    /* send system acquire request internal message with new scene to load the system acquire state machine */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_PROTO_MISMATCH, 0, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithReleaseReason_Idle
 功能描述  : process the SD with release reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

  2.日    期   : 2015年7月27日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithReleaseReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;

    NAS_MEM_SET_S(&stFreq, sizeof(stFreq), 0x00, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 从determin ind消息中填充system id */
    stFreq.enBandClass = pstSysDeterminInd->stCurChannelInfo.usBandClass;
    stFreq.usChannel   = pstSysDeterminInd->stCurChannelInfo.usChannel;

    /* CALLBACK中丢网 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 启动CAlLBACK模式15s搜网 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED, 1, &stFreq);

        return;
    }

    /* 紧急呼CallRelease当前不支持CallBack模式的处理,若支持CallBack，进行紧急呼CallRelease搜网 */
    if (VOS_TRUE == CNAS_XSD_IsEmcCallOriginalSysExist())
    {
        if (VOS_TRUE == CNAS_XSD_GetCallBackCfg()->ulCallBackEnableFlg)
        {
            CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

            CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED, 1, &stFreq);

            return;
        }

        CNAS_XSD_ClearEmcCallOriginalSys();

        /* 不支持CallBack且当前驻留的是无效系统，进行Lost搜网 */
        if (VOS_FALSE == CNAS_XSD_IsCurSystemValid())
        {
            CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

            CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

            return;
        }
    }

    if (VOS_TRUE == CNAS_XSD_GetRedirectionFlag())
    {
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR, 1, &stFreq);
    }
    else
    {
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, &stFreq);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithSysLostReason_Idle
 功能描述  : process the SD with system lost reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : L00256032
    修改内容   : Create

  2.日    期   : 4/1/2014
    作    者   : y00245242
    修改内容   : 增加OOC系统捕获调度机制

  3.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

  4.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithSysLostReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, pstSysDeterminInd))
    {
        return;
    }

    CNAS_XSD_SetOocSearchScene(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST);
    CNAS_XSD_ProcOocSchedule(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithAcquisitionFail_Idle
 功能描述  : process the SD with AcquisitionFail reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 21/12/2015
    作    者   : c00299063
    修改内容   : Create
********************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAcquisitionFail_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /*处理同system lost*/
    CNAS_XSD_ProcCasSystemDetermineIndWithSysLostReason_Idle(pstSysDeterminInd);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithRescanReason_Idle
 功能描述  : process the SD with rescan reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithRescanReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_RESCAN, 0, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithLockReason_Idle
 功能描述  : process the SD with lock reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create
  2.日    期   : 11/08/2015
    作    者   : m00312079
    修改内容   : DTS2015072202870:收到lock ind应按丢网场景触发搜网

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithLockReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /* According to discussing with CAS,we need not do system acquire flow.
       And CAS will control the access process with special fail reason */
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithUnlockReason_Idle
 功能描述  : process the SD with unlock reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithUnlockReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithAccessDeniedReason_Idle
 功能描述  : process the SD with access denied reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAccessDeniedReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /* avoid the curret camped frequency fro 60s */
    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_ACCESS_DENIED, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_ACCESS_DENINED, 0, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithAcctBlockReason_Idle
 功能描述  : process the SD with acct block reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAcctBlockReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /* avoid the curret camped frequency fro 60s */
    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_ACCT_BLOCKED_IND, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_ACCT_BLOCKED, 0, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithNdssOffReason_Idle
 功能描述  : process the SD with Ndss Off reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

  2.日    期   : 2015年7月17日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithNdssOffReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{

    /* 设置NDSS off指示值 */
    CNAS_XSD_SetNdssIndFlag(VOS_TRUE);

    /* 清除redirection标志 */
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 启动内部搜网 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_NDSS_OFF, 0, VOS_NULL_PTR);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithErrReason_Idle
 功能描述  : process the SD with err reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithErrReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /* avoid the curret camped frequency fro 60s */
     CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_ERROR_IND, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

     CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_ERR, 0, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithRegistRejReason_Idle
 功能描述  : process the SD with register reject reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create
  2.日    期   : 13/07/2015
    作    者   : m00312079
    修改内容   : DTS2015063003186 添加returnCause的维护

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithRegistRejReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_PRL_1X_SYSTEM_STRU            *pstRedirOrigSys = VOS_NULL_PTR;

    pstRedirOrigSys = CNAS_XSD_GetRedirectionOrignalSys();

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    if (VOS_TRUE == CNAS_XSD_GetRedirectionFlag())
    {
        CNAS_XSD_SetRedirectionFlag(VOS_FALSE);
        CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_REG_REJ);

        if (VOS_TRUE == CNAS_XSD_GetRedirectionReturnIfFailFlag())
        {
            /* 紧急呼场景进行Any搜网 */
            if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC, 1, &pstRedirOrigSys->stFreq, VOS_NULL_PTR))
            {
                return;
            }

            CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF, 1, &pstRedirOrigSys->stFreq);

            return;
        }

        CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_REDIRECTION_FAIL, &(pstRedirOrigSys->stFreq));
    }

    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_REG_REJECTED, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ, 0, VOS_NULL_PTR);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithReselectionReason_Idle
 功能描述  : process the SD with reselection reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithReselectionReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* XSD need not do the system acquire flow for CAS will handle the reselection process */
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithSystemReselectionReason_Idle
 功能描述  : process the SD with system reselection reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

  2.日    期   : 31/07/2015
    作    者   : m00312079
    修改内容   : DTS2015070206183修改-系统重选不Avoid当前频点

  3.日    期   : 2015/07/02
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17 modified

  4.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithSystemReselectionReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstCurCampedSys = VOS_NULL_PTR;
    CNAS_CAS_1X_SYS_RESELECTION_INFO_STRU                  *pstSysReselInfo = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astReselChanList[CNAS_CAS_1X_MAX_SYS_RESELECTION_CHAN_NUM];
    VOS_UINT16                                              i;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    NAS_MEM_SET_S(astReselChanList, sizeof(astReselChanList), 0x0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_SYS_RESELECTION_CHAN_NUM);

    pstCurCampedSys = CNAS_XSD_GetCurCampedSysInfo();
    pstSysReselInfo = &pstSysDeterminInd->unSysDeterminInfo.stSysReselInfo;



    for (i = 0; i < pstSysReselInfo->usChannelNum; i++)
    {
        astReselChanList[i].enBandClass = pstSysReselInfo->astChannelList[i].usBandClass;
        astReselChanList[i].usChannel   = pstSysReselInfo->astChannelList[i].usChannel;
    }

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);


    CNAS_PRL_Get1xSysGeoList(&pstCurCampedSys->stSystem, &stGeoListInfo);

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* check the current system is a prefered PRL system or not */
    if (0 != stGeoListInfo.ucGeoNum)
    {
        if (VOS_FALSE == CNAS_XSD_IsCurSysNotSuitableSys(&pstCurCampedSys->stSystem, VOS_FALSE, 0))
        {
            if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC, pstSysReselInfo->usChannelNum, astReselChanList, VOS_NULL_PTR))
            {
                return;
            }

            CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF, pstSysReselInfo->usChannelNum, astReselChanList);

            return;
        }
    }

    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC, pstSysReselInfo->usChannelNum, astReselChanList, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG, pstSysReselInfo->usChannelNum, astReselChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithNewSystemReason_Idle
 功能描述  : process the SD with new system reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create
  2.日    期   : 21/08/2015
    作    者   : m00312079
    修改内容   : bug fixed for DTS2015070400587

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithNewSystemReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_CAS_1X_NEW_SYSTEM_INFO_STRU                           *pstNewSysInfo;

    pstNewSysInfo = &pstSysDeterminInd->unSysDeterminInfo.stNewSysInfo;

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    if (PS_TRUE == pstNewSysInfo->enIsRelease)
    {
        /* 紧急呼流程中收到SD的处理 */
        if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC, 0, VOS_NULL_PTR, VOS_NULL_PTR))
        {
            return;
        }

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0, 0, VOS_NULL_PTR);
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithMaxAccessFailureReason_Idle
 功能描述  : process the SD with max access failure reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : L00256032
    修改内容   : Create
  2.日    期   : 27/1/2016
    作    者   : w00176964
    修改内容   : DTS2015120204031:SD指示max access failure,balong回原始频点时间比较慢
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithMaxAccessFailureReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSys = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astCurMapChannel[1];

    astCurMapChannel[0].enBandClass = pstSysDeterminInd->stCurChannelInfo.usBandClass;
    astCurMapChannel[0].usChannel   = pstSysDeterminInd->stCurChannelInfo.usChannel;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    pstCurCampedSys = CNAS_XSD_GetCurCampedSysInfo();

    /* 这里CDG对1x下最大接入尝试失败的处理，对于接入频点需要avoid,但是时长未确定，给的
       是一个建议值,此处参考标杆进行优化,接入频点放在构造列表的最后面,等待其他频点都尝试
       完成后再尝试该接入失败的频点 */


    CNAS_PRL_Get1xSysGeoList(&pstCurCampedSys->stSystem, &stGeoListInfo);

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* check the current system is a PRL system or not */
    if (0 != stGeoListInfo.ucGeoNum)
    {
        /* 紧急呼流程中收到SD的处理 */
        if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC, 1, astCurMapChannel, VOS_NULL_PTR))
        {
            return;
        }

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL, 1, astCurMapChannel);

        return;
    }

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC, 1, astCurMapChannel, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL, 1, astCurMapChannel);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithAbnormalReason_Idle
 功能描述  : process the SD with abnormal reason from CAS in L1_Idle state
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 12/1/2015
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAbnormalReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* 紧急呼流程中收到SD的处理 */
    if (VOS_TRUE == CNAS_XSD_ProcEmcSysAcqFlow_Idle(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR, VOS_NULL_PTR))
    {
        return;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_ABNORMAL, 0, VOS_NULL_PTR);

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiAvailMru0TimerExpired_Ooc
 功能描述  : OOC状态下available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailMru0TimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 搜索MRU0 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvPowerOffReq_Ooc
 功能描述  : 收到ID_MSCC_XSD_POWER_OFF_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvPowerOffReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止所有OOC下定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_TIMER);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER);

    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 启动L2关机状态机 */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_POWER_OFF);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateOocSearchPhaseAndCurrentTimes
 功能描述  : 获取下一次调度时长
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateOocSearchPhaseAndCurrentTimes(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    VOS_UINT8                           ucCurrentPhase;
    VOS_UINT16                          usOocSchPhaseTimes;

    /* 根据当前OOC阶段获取下次启动OOC捕获时间, 注: 当前阶段是从0开始的 */
    ucCurrentPhase    = pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase;
    usOocSchPhaseTimes  = pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[ucCurrentPhase].usTimes;

    /* 刷新当前所处的阶段和次数 */
    if (pstOocScheduleInfo->stConfigInfo.ucPhaseNum == ucCurrentPhase + 1)
    {
        /* 记录当前次数，方便未来打印查看 */
        pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes++;
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
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextOocScheduleTimerLen
 功能描述  : 获取下一次调度时长
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetNextOocScheduleTimerLen(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    VOS_UINT16                          usNextTimerLen;
    VOS_UINT8                           ucOocSchPhaseNum;

    usNextTimerLen = 0;

    /* 根据当前OOC阶段获取下次启动OOC捕获时间 */
    ucOocSchPhaseNum    = pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase;
    usNextTimerLen      = pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[ucOocSchPhaseNum].usTimerLen;

    /* Cdg143 5.11.1b (DO Traffic Operation):
       No more than one acquisition attempt every 5 sec for the first four acquisition attempts
       No more than one acquisition attempt every 10 sec thereafter
       当前使用NV控制
     */
    /* HRPD 数据业务是否在运行 */
    if (VOS_TRUE == pstOocScheduleInfo->stOocCtxInfo.ucDoTrafficFlag)
    {
        /* check 在DO traffic下，系统捕获是否已经达到四次 */
        if (VOS_TRUE == pstOocScheduleInfo->stOocCtxInfo.ucFirstFourAcqArrivedFlag)
        {
            /* 如果下次启动OOC时间小于10s，使用10s时长, 否则使用当前时长 */
            if  (usNextTimerLen < pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase2TimerLen)
            {
                usNextTimerLen = pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase2TimerLen;
            }
        }
        else
        {
            /* 如果下次启动OOC时间小于5s，使用5s时长, 否则使用当前时长 */
            if  (usNextTimerLen < pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase1TimerLen)
            {
                usNextTimerLen = pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase1TimerLen;
            }

            /* 否则使用当前的时长 */
            /* 刷新DO traffic下1X系统搜索次数 */
            pstOocScheduleInfo->stOocCtxInfo.ucAttemptTimesInDoTraffic++;

            /* 如果系统搜索次数达到4次，设置ucFirstFourAcqArrivedFlag变量为TRUE, 清除搜索次数为0 */
            if ((CNAS_XSD_ATTEMP_IN_DO_TRAFFIC_4_TIMES == pstOocScheduleInfo->stOocCtxInfo.ucAttemptTimesInDoTraffic)
             && (VOS_FALSE                             == pstOocScheduleInfo->stOocCtxInfo.ucFirstFourAcqArrivedFlag))
            {
                pstOocScheduleInfo->stOocCtxInfo.ucFirstFourAcqArrivedFlag = VOS_TRUE;
            }
        }
    }

    return usNextTimerLen;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcOocSchedule
 功能描述  : 处理OOC调度
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新增搜网结果NORF直接进入OOC状态

  3.日    期   : 2015年7月21日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
  4.日    期   : 2015年12月21日
    作    者   : w00242748
    修改内容   : DTS2015121511023:call release申请的资源优先级需提高
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcOocSchedule(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;
    VOS_UINT16                          usNextAcqTimerLen;
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT32                          ulRemainTimerLen;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enInSysAcqScene;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    ucMru0SearchTimerLen = pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen;

    if (CNAS_XSD_SYS_ACQ_SCENE_NO_RF == enAcqScene)
    {
        /* 向RRM发起注册,RF可用后RRM会通知XSD */
        CNAS_XSD_RegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

        if (VOS_TRUE == CNAS_CCB_Get1XRfAvailFlg())
        {
            /* 上报MSCC NO RF消息 */
            CNAS_XSD_SndMsccRfAvailInd(VOS_FALSE);

            /* 设置当前RF可用标记为:RF不可用 */
            CNAS_CCB_Set1XRfAvailFlg(VOS_FALSE);
        }

        if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
        {
            /* 15s CALLBACK搜网保护定时器 */
            if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_XSD, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, 0))
            {
                CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);
            }
        }

        return;
    }

    /* 有等待OOC的请求 */
    if (VOS_TRUE == CNAS_XSD_GetOocWaitSearchFlag())
    {
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_SndInternalSysAcqReq(pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene, 0, VOS_NULL_PTR);

        /* 清除标记 */
        CNAS_XSD_SetOocWaitSearchFlag(VOS_FALSE);

        return;
    }

    /* 搜索MRU0失败，再次check MRU0定时器是否可以启动 */
    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0 == enAcqScene)
    {
        /* 获取available剩余时长 */
        ulRemainTimerLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_XSD, TI_CNAS_XSD_AVAILABLE_TIMER, 0);

        /* 如果剩余时长仍然大于2倍MRU0时长，可以尝试MRU0, 启动MRU0定时器 */
        if (((VOS_UINT32)ucMru0SearchTimerLen * 2 * 1000) < ulRemainTimerLen)
        {
            CNAS_XSD_StartTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER, (ucMru0SearchTimerLen * 1000));
        }

        return;
    }

    /* LOG OOC调度信息 */
    CNAS_XSD_LogOocCtxInfo(&(pstOocScheduleInfo->stOocCtxInfo));

    usNextAcqTimerLen = CNAS_XSD_GetNextOocScheduleTimerLen(pstOocScheduleInfo);

    /* 如果OOC调度时间为0，立即启动搜网 */
    if (0 == usNextAcqTimerLen)
    {
        /* 设置L1 main状态为initial状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == enAcqScene)
        {
            enInSysAcqScene = CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASE_SYSTEM_LOST;
        }
        else
        {
            enInSysAcqScene = pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene;
        }

        /* 发起OOC场景下系统捕获 */
        CNAS_XSD_SndInternalSysAcqReq(enInSysAcqScene, 0, VOS_NULL_PTR);
    }
    else
    {
        /* 设置L1 main状态为OOC状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);

        /* 启动OOC available定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_AVAILABLE_TIMER, (usNextAcqTimerLen * 1000));

        /* 如果是OOC丢网场景，检查是否需要启动MRU0搜索 */
        if (CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST == pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene)
        {
            /* 2倍MRU0搜索时长是否小于当前OOC sleep时长，如果是，启动MRU0 available定时起 */
            if ((VOS_UINT16)ucMru0SearchTimerLen*2 < usNextAcqTimerLen)
            {
                CNAS_XSD_StartTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER, (ucMru0SearchTimerLen * 1000));
            }
        }
    }

    /* 更新OOC搜索阶段及当前阶段搜索次数 */
    CNAS_XSD_UpdateOocSearchPhaseAndCurrentTimes(pstOocScheduleInfo);

    /* LOG OOC更新后的调度信息 */
    CNAS_XSD_LogOocCtxInfo(&(pstOocScheduleInfo->stOocCtxInfo));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SetOocSearchScene
 功能描述  : 设置OOC搜索场景
 输入参数  : enAcqScene -- 搜索场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_SetOocSearchScene(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    if (VOS_FALSE == pstOocScheduleInfo->stOocCtxInfo.ucSceneSetFlag)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON != enAcqScene)
        {
            /* 如果不是开机搜网失败，则统一设置为OOC搜网 */
            pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene = CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST;
        }
        else
        {
            pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene = enAcqScene;
        }

        pstOocScheduleInfo->stOocCtxInfo.ucSceneSetFlag       = VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetOocSearchScene
 功能描述  : 获取OOC搜索场景
 输入参数  : enAcqScene -- 搜索场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_XSD_GetOocSearchScene(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    return (pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcNormalCallRedialSysAcqFailScene
 功能描述  : 处理普通呼叫重拨搜网失败的场景
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月17日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcNormalCallRedialSysAcqFailScene()
{
    /*存在语音呼叫重拨，循环发起搜网 */
    VOS_UINT8                           ucCallExistFlg;

    ucCallExistFlg = CNAS_XSD_GetCallExistFlg();

    if (0 != (ucCallExistFlg & CNAS_XSD_NORMAL_VOICE_CALL_EXIST_FLAG))
    {
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL, 0, VOS_NULL_PTR);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    }
    else
    {
         CNAS_XSD_SetOocSearchScene(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST);
         CNAS_XSD_ProcOocSchedule(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcEmergencyCallSysAcqFailScene
 功能描述  : 处理紧急呼搜网失败的场景
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月17日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcEmergencyCallSysAcqFailScene()
{
    /* 紧急呼重拨搜网失败启动循环搜网 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcEmcCallReleaseSysAcqFailScene
 功能描述  : 处理紧急呼释放搜网失败的场景
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月17日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcEmcCallReleaseSysAcqFailScene()
{
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 重置计数器 */
        CNAS_XSD_SetEmcCallBackSrchCounter(0);

        /* 发起新一轮CallBack搜网 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST, 0, VOS_NULL_PTR);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);

    }

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcEmcCallBackSystemLostSysAcqFailScene
 功能描述  : 处理CallBack搜网失败的场景
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月17日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcEmcCallBackSystemLostSysAcqFailScene()
{
    VOS_UINT8                                       ucCallBackSrchCounter;
    CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU *pstEmcCallBackCfInfo = VOS_NULL_PTR;

    pstEmcCallBackCfInfo    = CNAS_XSD_GetEmcCallBackCandidateFreqInfo();

    ucCallBackSrchCounter = CNAS_XSD_GetEmcCallBackSrchCounter();

    ucCallBackSrchCounter++;

    /* 发起新一轮CallBack搜网 */
    if (ucCallBackSrchCounter < CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_MAX_TRY_TIMES)
    {
        CNAS_XSD_SetEmcCallBackSrchCounter(ucCallBackSrchCounter);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        /* 如果保存了异频临区频点，则加入异频临区频点信息 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,
                                      pstEmcCallBackCfInfo->usCfChannelNum,
                                      pstEmcCallBackCfInfo->astChannelList);

        return;
    }

    /* 启动保护定时器 */
    /* 重置计数器 */
    CNAS_XSD_SetEmcCallBackSrchCounter(0);

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 达到10次，起定时器保护 */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER_LEN);

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCallReleaseWithRedirSysAcqFailScene
 功能描述  : 处理重定向呼叫释放搜网失败场景
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月17日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCallReleaseWithRedirSysAcqFailScene(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
)
{
    if (VOS_TRUE == pstSysAcqRslt->ucImmediateSysAcq)
    {
        CNAS_XSD_SetEmcRedirectionFlg();

        CNAS_XSD_SndInternalRedirInd(CNAS_XSD_GetRedirectionInfoAddr());

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    }

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcSearchNetworkFailure
 功能描述  : 设置OOC搜索场景
 输入参数  : pstSysAcqRslt -- 系统捕获结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

 2.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发

  3.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcSearchNetworkRslt_Fail(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
)
{
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU               stSysSrvInfo;


    /* 状态迁移到CNAS_XSD_L1_STA_OOC */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);

    /* 给MSCC发送System srv Info信息 */
    NAS_MEM_SET_S(&stSysSrvInfo, sizeof(stSysSrvInfo), 0x0, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));
    stSysSrvInfo.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
    CNAS_XSD_SndMsccSysSrvInfoInd(&stSysSrvInfo);

    if (VOS_TRUE == CNAS_XSD_GetSrvAcqFlg())
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);

        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);
    }

    CNAS_XSD_SetCurSrvStatus(CNAS_XSD_SERVICE_STATUS_NO_SERVICE);

    if (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_XSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* 上报无服务 */
    CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);

    /* normaly we have to clear the redirection flag while enter system lost expect trigger
       redirection flow at once */
    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR != pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_XSD_SetRedirectionFlag(VOS_FALSE);
    }


    switch(pstSysAcqRslt->enCurAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL:
             CNAS_XSD_ProcNormalCallRedialSysAcqFailScene();
             break;

        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
             CNAS_XSD_ProcEmergencyCallSysAcqFailScene();
             break;

        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED:
             CNAS_XSD_ProcEmcCallReleaseSysAcqFailScene();
             break;

        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST:
             CNAS_XSD_ProcEmcCallBackSystemLostSysAcqFailScene();
             break;

        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR:
             CNAS_XSD_ProcCallReleaseWithRedirSysAcqFailScene(pstSysAcqRslt);
             break;

        default:

            if (VOS_TRUE == pstSysAcqRslt->ucImmediateSysAcq)
            {
                CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

                /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);
            }
            else
            {
                CNAS_XSD_SetOocSearchScene(pstSysAcqRslt->enCurAcqScene);
                CNAS_XSD_ProcOocSchedule(pstSysAcqRslt->enCurAcqScene);
            }

    }


}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcSearchNetworkRslt_Abort
 功能描述  : 设置搜网打断场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月21日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcSearchNetworkRslt_Abort(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
)
{
    if (VOS_TRUE == CNAS_XSD_GetSrvAcqFlg())
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    if (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_XSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }


    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);

        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);
    }

    if (CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST == pstSysAcqRslt->enCurAcqScene)
    {
        /* 停止15s CALLBACK搜网保护定时器 */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

        /* 清除异频临区频点信息 */
        CNAS_XSD_ClearEmcCallBackCandidateFreq();
    }


    /* 停止所有OOC下定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_TIMER);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcSearchNetworkRslt_Succ
 功能描述  : 处理搜网成功的场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月21日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcSearchNetworkRslt_Succ(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
)
{
    /* 状态迁移到CNAS_XSD_L1_STA_IDLE */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

    /* 如果当前处于业务触发搜网状态，回复结果 */
    if (VOS_TRUE == CNAS_XSD_GetSrvAcqFlg())
    {
        if ((VOS_FALSE == CNAS_XSD_IsCurSystemValid())
         && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != pstSysAcqRslt->enCurAcqScene))
        {
            /* 当前搜网结果非有效系统，进行业务触发搜网 */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

            CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

            return;
        }

        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    if (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_XSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);
    }

    /* 搜网成功，停止15s CALLBACK搜网保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);

        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_SUCCESS);
    }

    /* 初始化OOC上下文信息 */
    CNAS_XSD_InitOocCtxInfo();

    /* 停止所有OOC下定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_TIMER);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER);

    if (CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST == pstSysAcqRslt->enCurAcqScene)
    {
        /* 清除异频临区频点信息 */
        CNAS_XSD_ClearEmcCallBackCandidateFreq();
    }

    return;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Deactive
Description     :   The function receives the System Acquire Request from MSCC and
                    Starts the System Acquire FSM
Input parameters:   ulEventType   - Event type of the System Acquire Request from MSCC.
                    pstMsg        - POinter to the System Acquire Request from MSCC.
Outout parameters:  None
Return Value    :   VOS_TRUE
Modify History:
    1)  Date    :   2015-04-04
        Author  :   a00295761
        Modify content :    Create

  2.日    期   : 2015年7月25日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 收到MSCC激活请求前收到紧急呼Start请求，启动紧急呼搜网，否则做开机搜网 */
    if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        /* 启动紧急呼重拨搜网 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* 申请射频资源 */
    CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

    /* Init the System acquire FSM */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SYS_ACQ);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* XSD Sends power save CNf to MSCC */
    CNAS_XSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除ohm频点信息 */
    CNAS_CCB_ClearCdmaOhmFreq();

    /* 退出CallBack状态 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 停止CALLBACK保护定时器 */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER);
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

        CNAS_XSD_QuitCallBackMode();
    }

    /* Init the Power Off FSM */
    CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_POWER_OFF);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvRrmStatusInd_Deactive
 功能描述  : 收到RRM NO RF状态指示的时候，如果当前处于NO RF,则向MSCC透传Status Ind消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 判断RF可用标记 */
    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* 当前处于NO RF 向MSCC透传消息,不触发搜网 */
        CNAS_XSD_SndMsccRfAvailInd(VOS_TRUE);

        /* 设置当前RF可用标记为:RF可用 */
        CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);
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
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前处于NO RF状态，则触发搜网 */
    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
        {
            /* 重置计数器 */
            CNAS_XSD_SetEmcCallBackSrchCounter(0);

            /*发送搜网内部请求消息 */
            CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST, 0, VOS_NULL_PTR);

            return VOS_TRUE;
        }

        /*发送搜网内部请求消息 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_Ooc
 功能描述  : OOC状态收到业务触发的搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 业务触发搜网 */
    /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /*发送搜网内部请求消息 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        /* 如果业务类型是紧急呼，构建紧急呼搜网列表 */
        CNAS_XSD_BuildEmcCallRedialScanChanList();

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);
    }
    else
    {
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_Deactive
 功能描述  : Deactive状态收到业务触发的搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年7月25日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 业务触发搜网 */
    /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /*发送搜网内部请求消息 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        /* 如果业务类型是紧急呼，构建紧急呼搜网列表 */
        CNAS_XSD_BuildEmcCallRedialScanChanList();

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);
    }
    else
    {
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithNoRfReason_Idle
 功能描述  : Idle态收到原因为Determine Ind的处理
 输入参数  : CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU pstSysDeterminInd : DeterminInd消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithNoRfReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
)
{
    /* 向RRM发起注册,RF可用后RRM会通知XSD */
    CNAS_XSD_RegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

    if (VOS_TRUE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_XSD_SndMsccRfAvailInd(VOS_FALSE);

        /* 设置当前RF可用标记为:RF不可用 */
        CNAS_CCB_Set1XRfAvailFlg(VOS_FALSE);
    }

    /* CALLBACK中NO RF丢网 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 15s CALLBACK搜网保护定时器，进入OOC等待RF可用消息 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);
    }


    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);

    CNAS_XSD_SetOocSearchScene(CNAS_XSD_SYS_ACQ_SCENE_NO_RF);

    /* 状态迁移到CNAS_XSD_L1_STA_OOC */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_Initial
 功能描述  : 紧急呼业务触发搜网打断后的缓存处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 退出CallBack状态 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 停止CALLBACK保护定时器 */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER);
        CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

        CNAS_XSD_QuitCallBackMode();
    }

    /* 当前驻留且系统有效,普通呼在搜网结果中处理 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

        return VOS_TRUE;
    }

    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallEndNtf_Initial
 功能描述  : 收到Mscc呼叫挂断呼的缓存处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前驻留且系统有效 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

        return VOS_TRUE;
    }

    /*发送Lost搜网请求 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Initial
 功能描述  : 收到CallBack 15s定时器超时打断后的缓存处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止CALLBACK保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    /* 当前驻留且系统有效 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

        return VOS_TRUE;
    }

    /* 发送Lost搜网请求 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Initial
 功能描述  : 收到CallBack模式定时器超时打断后的缓存处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    /* 当前驻留且系统有效 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

        return VOS_TRUE;
    }

    /* 发送Lost搜网请求 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Initial
 功能描述  : 收到MSCC退出CallBack请求打断后的缓存处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackNtf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止CALLBACK保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER);
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    /* 当前驻留且系统有效 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        CNAS_XSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_IDLE);

        return VOS_TRUE;
    }

    /* 发送Lost搜网请求 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Idle
 功能描述  : IDLE收到CallBack模式定时器超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    /* 呼叫存在不触发搜网 */
    if (0 != CNAS_CCB_Get1XCallExistCount())
    {
        return VOS_TRUE;
    }

    /* 如果驻留，判断当前系统是否有效(进Idle)，否则LOST搜网 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /*发送搜网内部请求消息 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackSrchBreakTimerExpired_Idle
 功能描述  : IDLE收到CallBack搜网500毫秒间隔定时器超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackSrchBreakTimerExpired_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU *pstEmcCallBackCfInfo = VOS_NULL_PTR;

    pstEmcCallBackCfInfo    = CNAS_XSD_GetEmcCallBackCandidateFreqInfo();

    /* 启动CAlLBACK模式15s搜网，CallBack模式加入异频临区频点 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,
                                  pstEmcCallBackCfInfo->usCfChannelNum,
                                  pstEmcCallBackCfInfo->astChannelList);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndEmcCallBackNtf_Idle
 功能描述  : IDLE收到MSCC退出CallBack请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackNtf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止CALLBACK保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    /* 呼叫存在不触发搜网 */
    if (0 != CNAS_CCB_Get1XCallExistCount())
    {
        return VOS_TRUE;
    }

    /* 退出时对当前网络进行判断进行LOST搜网 */
    /* 如果驻留，判断当前系统是否有效(进Idle)，否则LOST搜网 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /*发送搜网内部请求消息 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccMoCallEndNtf_Initial
 功能描述  : 收到MsccCallEnd处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* CALLBACK状态处理 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    /* 启动判断LOST搜网 */
    /* 如果驻留，判断当前系统是否有效，否则启动LOST搜网 */
    if (VOS_TRUE == CNAS_XSD_IsCurSystemValid())
    {
        return VOS_TRUE;
    }

    /* 迁移到INITIAL */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /*发送搜网内部请求消息 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccMoCallEndNtf_Ooc
 功能描述  : OOC收到MsccCallEnd的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 重置计数器 */
        CNAS_XSD_SetEmcCallBackSrchCounter(0);

        /* 启动CAlLBACK模式15s搜网 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST, 0, VOS_NULL_PTR);

        /* 15s CALLBACK搜网保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Ooc
 功能描述  : 收到CallBack 15s定时器超时打断后的缓存处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* CallBack No Rf场景处理 停止CALLBACK保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Ooc
 功能描述  : Ooc收到CallBack 定时器超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndEmcCallBackNtf_Ooc
 功能描述  : Ooc收到退出CallBack指示
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE(处理成功)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackNtf_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);
    CNAS_XSD_StopTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    /* 退出CALLBACK */
    CNAS_XSD_QuitCallBackMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSystemValid
 功能描述  : 判断当前是否驻留，系统是否在PRL表中且非Negative系统
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSystemValid( VOS_VOID )
{
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo   = VOS_NULL_PTR;
    VOS_UINT32                          ulIsNegSys;

    ulIsNegSys                          = VOS_TRUE;
    pstCurSysInfo                       = &(CNAS_XSD_GetCurCampedSysInfo()->stSystem);

    if (VOS_FALSE == CNAS_XSD_GetSystemCampOnFlag())
    {
        return VOS_FALSE;
    }

    /* 紧急呼流程中，若当前驻留，则认为是有效系统 */
    if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        return VOS_TRUE;
    }

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(pstCurSysInfo, VOS_FALSE, 0);

    return (!ulIsNegSys);
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_IsNeedReportNoService
 功能描述  : 消息CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU处理完后，如果发起搜网，
                向MSCC上报无服务，MSCC通知MMA，MMA启动延时上报定时器
 输入参数  :  CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU          *pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要上报无服务；VOS_TRUE:需要上报无服务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : l00324781
    修改内容   : 新生成函数

  2.日    期   : 2016年01月14日
    作    者   : l00324781
    修改内容   : DTS2016011107914修改
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsNeedReportNoService(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *pstSysDeterminInd
)
{
    /* 先剔除不需要上报无服务的原因
    */
    if ((CAS_CNAS_1X_SD_UNLOCK_IND == pstSysDeterminInd->enSdReason)
     || (CAS_CNAS_1X_SD_RESELECTION_IND == pstSysDeterminInd->enSdReason))
    {
        return VOS_FALSE;
    }

    /* 该情况下，不发起搜网，只是清除redirection 标记位 */
    if ((CAS_CNAS_1X_SD_REDIR_IND == pstSysDeterminInd->enSdReason)
     && (VOS_TRUE == pstSysDeterminInd->unSysDeterminInfo.stRedirectionInfo.ucInvalidRedir))
    {
        return VOS_FALSE;
    }

    /* 该情况下，不发起搜网 */
    if ((CAS_CNAS_1X_SD_NEW_SYSTEM_IND == pstSysDeterminInd->enSdReason)
     && (PS_TRUE != pstSysDeterminInd->unSysDeterminInfo.stNewSysInfo.enIsRelease))
    {
        return VOS_FALSE;
    }

    /* 电话挂断，发起搜网，分两个阶段，第1阶段只搜3个特定频点(MRU0 MRU1 和SD携带的频点)，
       一般能搜网成功，时间比较短，不再上报无服务 */
    if (CAS_CNAS_1X_SD_RELEASE_IND == pstSysDeterminInd->enSdReason)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcEmcSysAcqFlow_Idle
 功能描述  : 处理紧急呼流程中在Idle态收到的SD消息
             1.紧急呼发起，未收到SUCC,进行紧急呼搜网
             2.紧急呼收到SUCC,未挂断,若开启回呼模式，进入OOC，等待CallEnd;若未开启回呼模式，进行对应SD场景搜网
             3.紧急呼回呼模式，进行15s CallBack模式的搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE :不在紧急呼场景，不进行处理
             VOS_TRUE  :已进行处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月09日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_ProcEmcSysAcqFlow_Idle(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32      enEmcAcqScene,
    VOS_UINT32                              ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU         *pstFreq,
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU   *pstSysDeterminInd
)
{
    CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU         *pstEmcCallBackCfInfo    = VOS_NULL_PTR;

    pstEmcCallBackCfInfo    = CNAS_XSD_GetEmcCallBackCandidateFreqInfo();

    /* 紧急呼未收到Succ场景,进行紧急呼搜网 */
    if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        CNAS_XSD_SndInternalSysAcqReq(enEmcAcqScene, ulFreqNum, pstFreq);

        return VOS_TRUE;
    }

    /* CALLBACK回呼模式中，发起15s搜网 */
    if (CNAS_XSD_EMC_STATE_CALLBACK == CNAS_XSD_GetEmcState())
    {
        /* 启动CAlLBACK模式15s搜网 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

        /* 重置计数器 */
        CNAS_XSD_SetEmcCallBackSrchCounter(0);

        if (VOS_NULL_PTR    != pstSysDeterminInd)
        {
            /* SysLost场景搜索异频临区频点 */
            if (CAS_CNAS_1X_SD_SYS_LOST_IND == pstSysDeterminInd->enSdReason)
            {
                CNAS_XSD_SetEmcCallBackCandidateFreq(pstSysDeterminInd->stCurCfChannelInfo.usCfChannelNum,
                                                    (CNAS_PRL_FREQENCY_CHANNEL_STRU *)pstSysDeterminInd->stCurCfChannelInfo.astChannelList);

                CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,
                                              pstEmcCallBackCfInfo->usCfChannelNum,
                                              pstEmcCallBackCfInfo->astChannelList);

                CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);

                return VOS_TRUE;
            }
        }

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,
                                      0,
                                      VOS_NULL_PTR);

        /* 15s CALLBACK搜网保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN);

        return VOS_TRUE;
    }

    /* 紧急呼Succ后收到SD,进入OOC等待CallEnd */
    if (VOS_TRUE == CNAS_XSD_IsEmcCallOriginalSysExist())
    {
        if (VOS_TRUE == CNAS_XSD_GetCallBackCfg()->ulCallBackEnableFlg)
        {
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_OOC);

            return VOS_TRUE;
        }

        CNAS_XSD_ClearEmcCallOriginalSys();
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccXsdSysAcq_Ooc
 功能描述  : 在OOC状态下，处理用户触发的亮屏搜网请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月29日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccXsdSysAcq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止available定时器，避免在搜网过程中，available定时器超时 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_MRU0_TIMER);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_AVAILABLE_TIMER);

    /* 状态迁移到CNAS_XSD_L1_STA_INITIAL */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_L1_STA_INITIAL);

    /* 申请射频资源 */
    CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

    /*发送搜网内部请求消息 */
    CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}
/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



