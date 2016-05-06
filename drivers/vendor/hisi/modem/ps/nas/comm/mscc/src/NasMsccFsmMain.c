


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMsccFsmMain.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccCtx.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccSndMma.h"
#include "PsLogdef.h"
#include "NasMsccSndXsd.h"
#include "NasMsccSndHsd.h"
#include "NasMsccSndMmc.h"
#include "NasComm.h"
#include "NasMsccComFunc.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccProcNvim.h"
#include "NasMsccFsmSysCfg.h"

#include "NasMsccSndRrm.h"
#include "NasUtranCtrlInterface.h"
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_MAIN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef DMT
    VOS_UINT32 g_ulDisableAutoSysAcq;
#endif
/*****************************************************************************
  3 函数定义
*****************************************************************************/






VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ReadNvim();

    /* Start the Switch ON FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SWITCH_ON);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccStartCnf_Main_Null
Description     :   The function receives the Internal message from Switch On FSM. IF Start result is success,
                    Success result is sent to MSCC. If start result is not success, fail result is sent to MMA.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-08-20
        Author  :   w00242748
        Modify content : 动态加载项目
*****************************************************************************/

VOS_UINT32 NAS_MSCC_RcvMsccStartCnf_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU                  *pstSwitchOnRslt;

    pstSwitchOnRslt                     = (NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU *)pstMsg;

    if (NAS_MSCC_SWITCH_ON_RESULT_SUCCESS == pstSwitchOnRslt->enRslt)
    {
        /* Send Switch On Cnf with Success result to MMA */
        NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_SUCC);

        /* Set next state to Deactive */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_DEACTIVE);

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* 主动上报当前的是CL mode还是GUL mode */
        NAS_MSCC_SndRrmRatCombModeInd();
#endif

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        /* 动态加载只有在TDD/FDD同时存在时才有意义，如果都不支持的话，动态加载就没有意义 */
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main();
        }
#endif

    }
    else
    {
        /* 开机失败后mma不会给mscc发送关机请求, mscc需要在此清除mspl/mlpl解析申请的内存 */
        NAS_MSCC_InitCtx(NAS_MSCC_INIT_CTX_POWEROFF);

        /* Send Switch On Cnf with Fail result to MMA */
        NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_FAIL);

        NAS_TRACE_HIGH("NAS_MSCC_RcvMsccStartCnf_Main_Null: Switch ON result Failed!");
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaStartReq_Main_Deactive: Directly respond with START CNF msg");
    NAS_TRACE_HIGH("NAS_MSCC_RcvMmaStartReq_Main_Deactive: Directly respond with START CNF msg");
    /* Send Switch On Cnf with Success result to MMA */
    NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_SUCC);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Start the Power Off FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive
Description     :   The function receives the System Acquire request from MMA.
                    Send system acquire request all enabled modules.
                    Change the current state to NAS_MSCC_L1_STA_ACTIVE

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-04-08
        Author  :   m00312079
        Modify content :    add the logic for CL system acquire
    3)  日    期   : 2015年6月19日
        作    者   : s00217060
        修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/

VOS_UINT32 NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#ifdef DMT
    if (VOS_TRUE == g_ulDisableAutoSysAcq)
    {
        /* For ST testing purpose: Test sys cfg handling in DEACTIVE state */
        return VOS_TRUE;
    }
#endif

    NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(pstMsg);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                      *pstPowerOffRslt;

    pstPowerOffRslt = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    NAS_MSCC_ProcPowerOffResult_Main(pstPowerOffRslt->enRslt);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Start the Power OFF FSM  */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32 NAS_MSCC_RcvHsdSysAcqInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU                   *pstHsdSysAcqInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimPsRegStatus;

    pstHsdSysAcqInd                     = (HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU *)pstMsg;






    /* only failure situation should be dealt with, success situcation will be
        left for session negotiation */
    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC != pstHsdSysAcqInd->enRslt)
    {
        ucSimPsRegStatus = NAS_MSCC_GetSimPsRegStatus();

        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            VOS_FALSE,
                                            VOS_FALSE,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);

        /* 向MMA上报无服务，和MMA保持服务状态一致，此处也设置无服务 */
        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        if ((VOS_TRUE  == NAS_MSCC_IsNeedPerformCLSysAcq())
         && (VOS_TRUE  == ucSimPsRegStatus))
        {
            NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST));

            return VOS_TRUE;
        }
    }

    /* 搜网结果成功或失败上报mma_sys_end_ind，其他打断、NO_RF不上报 */
    /* 如果不支持LTE,即为HRPD单独的捕获流程;通知捕获开始的系统模式为DO */
    if ((NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstHsdSysAcqInd->enRslt)
      || (NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL == pstHsdSysAcqInd->enRslt))
    {
        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
        {
            NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstHsdSysAcqInd->enRslt),
                                               MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                               MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
        }
        else
        {
            NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstHsdSysAcqInd->enRslt),
                                               MSCC_MMA_ACQ_SYS_TYPE_DO,
                                               MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvInternalSysAcqReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);

    /* 启动L2 System Acquire状态机 */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcRegRejPlmnSeleInd_Main_Active
Description     :   process ID_MMC_MSCC_REG_REJ_PLMN_SELE_IND message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
    2)  Date    :   2016-01-18
        Author  :   w00176964
        Modify content :DTS2016011802320调整
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcMmssLteUnavailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU                 *pstLteUnavailInd;
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;

    pstLteUnavailInd = (MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU *)pstMsg;

    /* LTE处于从模,依赖于available定时器超时搜L,丢弃该消息 */
    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        return VOS_TRUE;
    }

    /* SYSCFG触发的detach不需要立即搜DO，SYSCFG流程完成后会触发搜索 */
    if ((MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_BUTT               == pstLteUnavailInd->enReason)
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_RAT_OR_BAND_DETACH == pstLteUnavailInd->enReason))
    {
        return VOS_TRUE;
    }

    /* 不满足搜网条件直接退出 */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        return VOS_TRUE;
    }

    /* 注册被拒卡无效或detach PS域或NO RF场景,此轮搜索不尝试LTE */
    if ((VOS_FALSE                                             == NAS_MSCC_GetSimPsRegStatus())
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_USER_DETACH       == pstLteUnavailInd->enReason)
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SRV_DOMAIN_DETACH == pstLteUnavailInd->enReason)
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_NO_RF             == pstLteUnavailInd->enReason))
    {
        enSysAcqScene = NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE;
    }
    /* 注册被拒或丢网场景,此轮搜索按照LTE单模掉网场景处理,先搜索一轮DO后再尝试LTE */
    else
    {
        enSysAcqScene = NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST;
    }

    NAS_MSCC_SndInternalSysAcqReq(enSysAcqScene, NAS_MSCC_GetSysAcqLteSrchType_L1Main(enSysAcqScene));

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_ProcBsrFailureRslt_Main_Active(
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf
)
{
    VOS_UINT8                           uc3gppActiveFlg;

    if (NAS_MSCC_BSR_NEED_ACQ_SYS == pstBsrSearchRsltCnf->enIsNeedAcqSys)
    {
        uc3gppActiveFlg = NAS_MSCC_Get3gppActiveFlg();

        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            /* BG搜网中回LTE时如果注册被拒卡无效,需要通过搜网流程切到HRPD下去 */
            if (VOS_TRUE == uc3gppActiveFlg)
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST));

                return;
            }

            /* LTE下PS注册被拒卡无效但回HRPD后,后续靠HSD的选网定时器周期性搜网;这里不再搜网 */
            if ((VOS_TRUE  == NAS_MSCC_GetSimPsRegStatus())
             && (VOS_FALSE == uc3gppActiveFlg))
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST));

                return;
            }
        }
    }
    else
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
        {
            /* 虽然目前BSR失败场景不会设置启动Retry Timer标识, 仍然先保留此if分支 */
            if (NAS_MSCC_BSR_NEED_START_RETRY_TIMER == pstBsrSearchRsltCnf->enIsNeedStartRetryTimer)
            {
                (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                             TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);
            }
            else
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }

    return;
}


VOS_UINT32 NAS_MSCC_RcvInternalBsrRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf = VOS_NULL_PTR;

    pstBsrSearchRsltCnf = (NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU *)pstMsg;

    switch (pstBsrSearchRsltCnf->enRslt)
    {
        /* BSR驻留到高优先级制式成功 */
        case NAS_MSCC_BSR_RESULT_SUCCESS:
        case NAS_MSCC_BSR_RESULT_L2C:

            if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
            {
                NAS_MSCC_StartBsrTimer();
            }

            break;

        case NAS_MSCC_BSR_RESULT_FAILURE:

            NAS_MSCC_ProcBsrFailureRslt_Main_Active(pstBsrSearchRsltCnf);

            break;

        case NAS_MSCC_BSR_RESULT_ABORT:

            /* 虽然设置了需要启动BSR Retry Timer标记，但是如果不再满足启动BSR定时器条件，不启动Retry定时器 */
            if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
            {
                if (NAS_MSCC_BSR_NEED_START_RETRY_TIMER == pstBsrSearchRsltCnf->enIsNeedStartRetryTimer)
                {
                    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                                  TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);
                }
                else
                {
                    NAS_MSCC_StartBsrTimer();
                }
            }

            break;

        default:

            NAS_WARNING_LOG(UEPS_PID_MSCC, "BSR FSM return result is except");

            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiBsrTimerExpired_Main_Active
Description     :   process the BSR Timer Expiry message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   t00323010
        Modify content :    Create for Iteration 10
    2)  Date    :   2015-06-11
        Author  :   W00176964
        Modify content : CDMA Iteration 12 Modified
    3)  Date    :   2015-12-15
        Author  :   W00176964
        Modify content : CL_MUTIMODE_OPTIMIZE调整:BSR触发指定搜逻辑删除
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ProcInterSysAcqSucc_Main
 功能描述  : MAIN上处理内部系统捕获成功结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年12月10日
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcInterSysAcqSucc_Main(VOS_VOID)
{


    /* 判断是否需要启动或者重启BSR定时器 */
    if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_StartBsrTimer();
        }
        else
        {
            if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }


    NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

    NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main();

    if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_LTE_SUCC);
    }
    else
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_DO_SUCC);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ProcInterSysAcqFail_Main
 功能描述  : MAIN上处理内部系统捕获失败结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcInterSysAcqFail_Main(
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                    *pstSysAcqRslt
)
{
    VOS_UINT8                           ucSearchLteFLag  = VOS_FALSE;
    VOS_UINT8                           ucSearchHrpdFLag = VOS_FALSE;

    ucSearchLteFLag  = pstSysAcqRslt->ucSearchLteFlag;
    ucSearchHrpdFLag = pstSysAcqRslt->ucSearchHrpdFlag;

    /* Lte和Hrpd都尝试搜索后，且是失败的以后，才通知MMA sys acq end */
    if ((VOS_TRUE == ucSearchLteFLag)
     && (VOS_TRUE == ucSearchHrpdFLag))
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
    }

    /* LTE注册被拒卡无效,不再启动available timer,直接搜索HRPD */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        /* Set the Camp On flag to FALSE */
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

        return;
    }

    if (VOS_TRUE == NAS_MSCC_StartTimer(TI_NAS_MSCC_AVAILABLE_TIMER, NAS_MSCC_GetNextAvailableTimerLength_L1Main()))
    {
        if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
        {
            NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main();
        }
        else
        {
            NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main();
        }
    }

    /* if both 1x and hrpd ,lte no service,start scan timer */
    if (NAS_MSCC_SERVICE_STATUS_NO_SERVICE == NAS_MSCC_GetCurr1xServiceStatus())
    {
        /* we start the timer only in CL mode */
        if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
        {
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
        }
    }

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active
Description     :   in active state process the system acquire result indication message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-06-11
        Author  :   W00176964
        Modify content : CDMA Iteration 12 Modified
    3)  Date           : 2015-06-04
        Author         : w00176964
        Modify content : CDMA Iteration 15 Modified
    4)  Date           : 2015-08-25
        Author         : m00312079
        Modify content : DTS2015082004682:L2C过程中往MMA上报无服务
    5)  Date           : 2016-01-15
        Author         : j00354216
        Modify content : DTS2016011403391
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                    *pstSysAcqRslt = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchLteFLag  = VOS_FALSE;
    VOS_UINT8                                               ucSearchHrpdFLag = VOS_FALSE;

    pstSysAcqRslt = (NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU *)pstMsg;

    ucSearchLteFLag  = pstSysAcqRslt->ucSearchLteFlag;
    ucSearchHrpdFLag = pstSysAcqRslt->ucSearchHrpdFlag;

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_ProcInterSysAcqSucc_Main();

        return VOS_TRUE;
    }

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_ProcInterSysAcqFail_Main(pstSysAcqRslt);
    }

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
    }

    if ( NAS_MSCC_SYSTEM_ACQUIRED_RESULT_L2C == pstSysAcqRslt->enRslt )
    {
        if ((VOS_TRUE == ucSearchLteFLag)
         && (VOS_TRUE == ucSearchHrpdFLag))
        {
            NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE,
                                               MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                               MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
        }
    }
    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiSleepTimerExpired_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* here must be CL mode */
    NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ProcRfAvailableInd_Main_Deactive
 功能描述  : MSCC在deactive状态下，处理RF资源可用请求
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_ProcRfAvailableInd_Main_Deactive()
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    VOS_UINT8                           ucSimPsRegStatus;

    VOS_UINT8                           ucAllowSrchLteFlg;

    ucAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();
    enUsimCardStatus    = NAS_MSCC_GetUsimCardStatus();
    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    /* 关机进入NULL状态，只有进SLEEP模式时，才会进DEACTIVE状态 */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return;
    }

    /* current support lte, usim card status is avialable and sim ps reg status is true, start lte acquir */
    if ((VOS_TRUE                               == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT  == enUsimCardStatus)
     && (VOS_TRUE                               == ucSimPsRegStatus)
     && (VOS_TRUE                               == ucAllowSrchLteFlg))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return;
}


VOS_UINT32 NAS_MSCC_RcvMmcMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvXsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaSrvAcqReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    VOS_UINT8                           ucSimPsRegStatus;
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq = VOS_NULL_PTR;
    VOS_UINT8                           ucAllowSrchLteFlg;

    ucAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();

    pstSrvAcqReq = (MMA_MSCC_SRV_ACQ_REQ_STRU *)pstMsg;

    enUsimCardStatus    = NAS_MSCC_GetUsimCardStatus();
    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    /* 关机进入NULL状态，只有进SLEEP模式时，才会进DEACTIVE状态 */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

        NAS_MSCC_SndXsdSrvAcqReq(pstSrvAcqReq);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return VOS_TRUE;
    }

    /* current support lte, usim card status is avialable and sim ps reg status is true, start lte acquir */
    if ((VOS_TRUE                               == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT  == enUsimCardStatus)
     && (VOS_TRUE                               == ucSimPsRegStatus)
     && (VOS_TRUE                               == ucAllowSrchLteFlg))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallStartNtf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER));

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}



/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active
Description     :   proc for TI_NAS_MSCC_AVAILABLE_TIMER message
Input parameters:   ulEventType
                    pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-4-7
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2015-12-11
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
    NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

    if (VOS_TRUE == NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main())
    {
        NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
        NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main())
    {
        NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
        NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main())
    {
        NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
        NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiScanTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdSrvst;

    /* maybe here is the buffered scan timer expied message,should judge the service
       status, if one of the system is normal service, hould ignore this message */

    enHrpdSrvst = NAS_MSCC_GetCurrHrpdServiceStatus();

    if ((NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == NAS_MSCC_GetCurr3gppPsServiceStatus())
     || (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == enHrpdSrvst))
    {
        /* discard this message */
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_Get1xSysAcqMoCallFlag())
    {
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
        return VOS_TRUE;
    }

    /* Start the Power Off FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main(VOS_VOID)
{
    VOS_UINT8                           ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvHsdInterSysStartInd_Main_Active
 功能描述  : mscc收到消息HSD_MSCC_INTERSYS_START_IND,处理该消息
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2015年11月05日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_CL_INTERSYS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcInterSysStartInd_Main_Active
 功能描述  : mscc收到消息MMC_MSCC_INTERSYS_START_IND,处理该消息
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2015年11月05日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_CL_INTERSYS);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMsccCLInterSysRsltCnf_Main_Active
 功能描述  : mscc收到消息ID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF,处理该消息
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2015年11月05日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccCLInterSysRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaCdmaMoCallSusccessNtf_Main_Active
 功能描述  : mscc收到消息ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF,处理该消息
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2015年11月05日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallSusccessNtf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Start the Power OFF FSM  */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdEmcCallBackInd_Main_Active
 功能描述  : mscc收到消息ID_XSD_MSCC_EMC_CALLBACK_IND,处理该消息
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2016年1月6日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdEmcCallBackInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_SetEmcCallExistFlag(VOS_FALSE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main(VOS_VOID)
{
    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main entered.");

    if (VOS_FALSE == NAS_MSCC_Is1xNormalService())
    {
        /* 1x可能从有服务变到无服务,需要清除1x有服务时相关信息 */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

        NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

        NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

        NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum();

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_SPEC);

        return VOS_TRUE;
    }

    /* 非OOS场景,重置定时器启动次数 */
    NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main();

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main
Description     :   proc for TI_NAS_MSCC_AVAILABLE_TIMER message
Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2015-12-11
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2016-1-16
        Author  :   w00176964
        Modify content :DTS2016011505664:进行LTE的全频段搜索之前穿插NV限定次数的LTE历史频点搜索
*****************************************************************************/
VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucFullBandSrchCount;
    VOS_UINT8                           ucFullBandSrchNum;

    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main entered.");

    if (VOS_TRUE == NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main())
    {
        NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main();

        if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
        {
            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
        }
        else
        {
            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
        }

        ucFullBandSrchCount = NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main();

        /* 当前处于最大阶段,不需要进入下个阶段了 */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucFullBandSrchCount == ucFullBandSrchNum))
        {
            NAS_MSCC_AddCur1xServiceSysAcqPhaseNum();

            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

            NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);
        }

        /* 是否需要重置当前阶段 */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucFullBandSrchCount == ucFullBandSrchNum))
        {
            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();
        }

        /* 需要进行全频搜的时候,需要清除历史搜的次数,保证进行NV限定次数的历史搜后再进行一次全频搜 */
        NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_SPEC);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucHistorySrchCount;
    VOS_UINT8                           ucHistorySrchNum;
    VOS_UINT8                           ucFullBandSrchNum;

    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main entered.");

    if (VOS_TRUE == NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main())
    {
        NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main();

        if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
        {
            ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteHistorySrchNum;

            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
        }
        else
        {
            ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteHistorySrchNum;

            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
        }

        ucHistorySrchCount  = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

        /* 当前处于最大阶段,不需要进入下个阶段了 */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucHistorySrchCount == ucHistorySrchNum)
         && (0                  == ucFullBandSrchNum))
        {
            NAS_MSCC_AddCur1xServiceSysAcqPhaseNum();

            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

            NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);
        }

        /* 是否需要重置当前阶段 */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucHistorySrchCount == ucHistorySrchNum)
         && (0                  == ucFullBandSrchNum))
        {
            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();
        }

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_HISTORY);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active entered.");

    /* 注意:打断流程都在后处理进行,此处是打断后回到L1 MAIN的操作 */

    /* 显式停止下当前总阶段时长定时器,因为可能时先超时后被缓存,
       在处理缓存定时器超时之前启动的 */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active:Not In Phase One.");

        return VOS_TRUE;
    }

    /* 重置当前阶段的一些参数,进入下个阶段搜索 */
    NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();
    NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        NAS_MSCC_AddCur1xServiceSysAcqPhaseNum();
    }

    /* 如果当前available搜网在运行，则重启定时器等待其超时触发后续动作 */
    if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_AVAILABLE_TIMER))
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* 启动一个短时定时器,超时后切换到下个阶段 */
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_AVAILABLE_TIMER, TI_NAS_MSCC_DEFAULT_AVAILABLE_TIMER_SKIP_LEN);
    }

    return VOS_TRUE;
}


/* 系统捕获lte的搜索类型映射表 */
NAS_MSCC_SYS_ACQ_SCENE_MAP_LTE_SRCH_TYPE_STRU g_astSysAcqSceneMapLteSrchTypeTbl[]=
{
    {NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
};


/*****************************************************************************
Function Name   :   NAS_MSCC_GetSysAcqLteSrchType_L1Main
Description     :   获取系统捕获Lte时的搜索类型
Input parameters:   enSysAcqScene--捕获场景
Output parameters:  VOS_VOID
Return Value    :   NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32

Modify History:
    1)  Date    :   2015-12-30
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/

NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MSCC_GetSysAcqLteSrchType_L1Main(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    VOS_UINT32                          i;

    /* 先在表里查找是否有映射关系,如果没有根据当前LTE的搜索次数以及1x是否有服务进行判断 */
    for (i = 0; i < (sizeof(g_astSysAcqSceneMapLteSrchTypeTbl)/sizeof(NAS_MSCC_SYS_ACQ_SCENE_MAP_LTE_SRCH_TYPE_STRU)); i++)
    {
        if (enSysAcqScene == g_astSysAcqSceneMapLteSrchTypeTbl[i].enSysAcqScene)
        {
            return g_astSysAcqSceneMapLteSrchTypeTbl[i].enLteSrchType;
        }
    }

    if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main())
        {
            return NAS_MSCC_PIF_PLMN_SEARCH_HISTORY;
        }
    }

    return NAS_MSCC_PIF_PLMN_SEARCH_SPEC;
}


#endif


VOS_VOID NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU                       *pstMmaSysAcqReq = VOS_NULL_PTR;

    pstMmaSysAcqReq = (MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU *)pstMsg;

    /* 更新初搜位置信息 */
    NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(pstMmaSysAcqReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMcc,
                                              pstMmaSysAcqReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMnc);

    NAS_MSCC_Update1xNoCardInitSearchLocInfo(pstMmaSysAcqReq->stCdmaInitLocInfo.lSid,
                                             pstMmaSysAcqReq->stCdmaInitLocInfo.lNid);

    NAS_MSCC_Update1xNoCardInitSearchLocMcc(pstMmaSysAcqReq->stCdmaInitLocInfo.ulMcc);


    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_POWER_UP,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     &(pstMmaSysAcqReq->stInitAcqPlmnInfo),
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        /* Set the Current FSM state to Active */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

        return;
    }

    /* 下面处理CL模式下的系统捕获流程 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON));

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_POWER_UP,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     &(pstMmaSysAcqReq->stInitAcqPlmnInfo),
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        /* hrpd and lte could not both perform system acquire,here return */
        return;
    }

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* Send HSD system acquire request if CDMA EVDO is supported */
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_POWER_UP,
                                 0,
                                 VOS_NULL_PTR);

        /* Set the Camp On flag to FALSE */
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }
#endif

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_PerformSystemAcquireUponSysCfg_Main
Description     :   在SYS CFG场景下，发起系统捕获
Input parameters:   VOS_VOID
Output parameters:  VOS_VOID
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-5-29
        Author  :   y00245242
        Modify content :Create
*****************************************************************************/
VOS_VOID NAS_MSCC_PerformSystemAcquireUponSysCfg_Main(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          uc3gppNormalSrvFlg;
    VOS_UINT32                          ucHrpdNormalSrvFlg;
    VOS_UINT8                           ucSimPsRegStatus;
#endif

    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
         if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
         {
             NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                          NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                          VOS_NULL_PTR,
                                          VOS_NULL_PTR);

             NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

             NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
         }

         return;
    }

    /* 下面处理CL模式下的系统捕获流程 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    if (VOS_TRUE == NAS_MSCC_IsNeedStartScanTimerUponSyscfg())
    {
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
    }

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
        {
            NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

            NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
        }
    }

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    uc3gppNormalSrvFlg  = NAS_MSCC_Is3gppNormalService();
    ucHrpdNormalSrvFlg  = NAS_MSCC_IsHrpdNormalService();

    /* 如果3GPP或HRPD已经是normal service且驻留到最高优先级,不需要搜网;直接返回 */
    if ((VOS_TRUE  == NAS_MSCC_IsCampOnHighestPrioritySystem())
     && ((VOS_TRUE == uc3gppNormalSrvFlg)
      || (VOS_TRUE == ucHrpdNormalSrvFlg)))
    {
        return;
    }

    /* 满足CL搜网条件且PS卡有效,进CL搜网流程 */
    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET));

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
        {
            NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                         NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                         VOS_NULL_PTR,
                                         VOS_NULL_PTR);

            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        }

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
        {
            NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                     0,
                                     VOS_NULL_PTR);

            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvHsdRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSD在DEACTIVE状态收到RF AVAILABLE IND，说明之前HSD丢过RF资源
       但在预处理中判断，如果当前模不被支持，则不进状态机处理，理论上进该函数
       一定是CL模式。
       不满足CL模式搜网的条件:(1)SYSCFG设置不支持CL;(2)SYSCFG支持CL，但不满足CL搜条件 */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        /* (1)HRPD不支持后，SYSCFG会进入该分支;
           (2)不支持CL模式，搜网1X和HRPD失败，TI_NAS_MSCC_SCAN_TIMER定时器超时，HSD进入DEACTVE状态
           (3)支持CL模式，不满足HRPD+LTE混合搜网模式 */
        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
        {
            /* Send HSD system acquire request if CDMA EVDO is supported */
            NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                     0,
                                     VOS_NULL_PTR);

            /* Set the Camp On flag to FALSE */
            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        /* 停AVAILABLE定时器 */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* 以HRPD资源可用的场景搜网 */
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE));
    }
    else
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE));
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucHrpdActiveFlg;
    VOS_UINT8                           ucAllowSrchLteFlg;

    ucAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();
    ucHrpdActiveFlg = NAS_MSCC_GetHrpdActiveFlg();

    /* MMC在DEACTIVE状态收到RF AVAILABLE IND，说明之前MMC丢过RF资源
       但在预处理中判断，如果当前模不被支持，则不进状态机处理，理论上进该函数
       一定是CL模式 */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        /* (1)LTE不支持后，SYSCFG会进入该分支;
           (2)不支持CL模式，搜网1X和LTE失败，TI_NAS_MSCC_SCAN_TIMER定时器超时，MMC进入DEACTVE状态
           (3)支持CL模式，不满足HRPD+LTE混合搜网模式 */
        if ( (VOS_TRUE  == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
          && (VOS_FALSE == ucHrpdActiveFlg)
          && (VOS_TRUE  == ucAllowSrchLteFlg))
        {
            NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                         NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                         VOS_NULL_PTR,
                                         VOS_NULL_PTR);

            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    /* 如果HRPD当前HRPD未被激活的话，则发起HRPD混合模式搜网 */
    if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
    {
        /* 停AVAILABLE定时器 */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* 以lte资源可用超时搜网场景搜索CL  */
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE));
    }

    return VOS_TRUE;
}


#endif


VOS_UINT32 NAS_MSCC_RcvMmcPlmnSelectionRsltInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                  *pstMmcSysAcqCnf = VOS_NULL_PTR;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enMmaSysAcqRlst;

    pstMmcSysAcqCnf                     = (MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF == pstMmcSysAcqCnf->enResult)
    {
        if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
        {
            /* check the current mode(only CL mode) and find the prior system in mspl*/
            if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE));
            }


            return VOS_TRUE;
        }
    }
#endif

    enMmaSysAcqRlst = NAS_MSCC_ConvertMmcPlmnSelRsltToMmaSysAcqRlst(pstMmcSysAcqCnf->enResult);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE == pstMmcSysAcqCnf->enResult)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE      == pstMmcSysAcqCnf->enResult))
    {
        /* check the current mode(only CL mode) and find the prior system in mspl*/
        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST));

            return VOS_TRUE;
        }
    }
#endif

    /* GUL模式按照原有逻辑通知MMA搜网结束,模式为3GPP */
    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(enMmaSysAcqRlst,
                                           MSCC_MMA_ACQ_SYS_TYPE_3GPP,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);

        return VOS_TRUE;
    }

    /* 打断、NO_RF、L2C且不需要搜网的情况下不上报，其他情况上报mma_sys_end_ind结果 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE == enMmaSysAcqRlst)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE == enMmaSysAcqRlst)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE == enMmaSysAcqRlst))
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(enMmaSysAcqRlst,
                                          MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                          MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
    }
#endif

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                      *pstPowerOffRslt;

    pstPowerOffRslt = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    NAS_MSCC_ProcPowerOffResult_Main(pstPowerOffRslt->enRslt);

    return VOS_TRUE;
}


MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32 NAS_MSCC_GetSystemAcquireFinalResult(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32                enAcqRslt
)
{

    if(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == enAcqRslt)
    {
        return MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE;
    }
    else
    {
        return MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE;
    }

}




VOS_UINT32 NAS_MSCC_RcvMmaSysCfgReq_Main_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Start the System config FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SYSTEM_CONFIG);

    return VOS_TRUE;
}

/* 删除此函数 */


VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                          *pstSysCfgReq = VOS_NULL_PTR;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                    *pstSysCfgCnf = VOS_NULL_PTR;
    #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
    VOS_UINT8                                               ucIsCLmodeLast;
    VOS_UINT8                                               ucIsCLmodeCurr;
    #endif

    pstSysCfgCnf = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)pstMsg;

    pstSysCfgReq  = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    if (NAS_MSCC_SYS_CFG_RESULT_SUCCESS == pstSysCfgCnf->enRslt)
    {
        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        ucIsCLmodeLast = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
        ucIsCLmodeCurr = NAS_MSCC_IsCLCombinedModeWithRatPrio(&(pstSysCfgReq->stRatPrioList));
        #endif

        /* set the user rat priority */
        NAS_MSCC_SavePrioRatList(&pstSysCfgReq->stRatPrioList);

        /*send the system config success result to MMA */
        NAS_MSCC_SndMmaSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        /* Send the system acquire if Sleep timer is running */
        if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_SLEEP_TIMER))
        {
            /* 在发送系统捕获后，停止sleep timer定时器 */
            NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

            NAS_MSCC_PerformSystemAcquireUponSysCfg_Main();

            /* Set the Current FSM state to Active */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);
        }

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* 前后CL和GUL之间有变更时，上报 */
        if (ucIsCLmodeLast != ucIsCLmodeCurr)
        {
            NAS_MSCC_SndRrmRatCombModeInd();
        }
        #endif
        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSysCfgCnf(pstSysCfgCnf->enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccSysCfgCnf_Main_Active
Description     :   The function is used to Handle System config Confirm internal message from MSCC in L1 Main active state.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-04-10
        Author  :   m00270891
        Modify content :    Create

    2)  Date    :   2015-05-29
        Author  :   y00245242
        Modify content : DTS2015052903319

    3)  Date    :   2015-12-11
        Author  :   w00176964
        Modify content : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                          *pstSysCfgReq  = VOS_NULL_PTR;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                    *pstSysCfgCnf = VOS_NULL_PTR;
    #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
    VOS_UINT8                                               ucIsCLmodeLast;
    VOS_UINT8                                               ucIsCLmodeCurr;
    #endif

    pstSysCfgCnf = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)pstMsg;

    pstSysCfgReq  = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();


    if (NAS_MSCC_SYS_CFG_RESULT_SUCCESS == pstSysCfgCnf->enRslt)
    {
        /* 停止相关的定时器 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == NAS_MSCC_IsHrpdAndLteBothSupported())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main();

            NAS_MSCC_StopTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH);
        }

        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);
#endif
        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        ucIsCLmodeLast = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
        ucIsCLmodeCurr = NAS_MSCC_IsCLCombinedModeWithRatPrio(&(pstSysCfgReq->stRatPrioList));
        #endif

        /* Note: firstly, set user rat priority. And then process system acquire. */
        NAS_MSCC_SavePrioRatList(&pstSysCfgReq->stRatPrioList);

        /*send the system config success result to MMA */
        NAS_MSCC_SndMmaSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        NAS_MSCC_PerformSystemAcquireUponSysCfg_Main();

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* 前后CL和GUL之间有变更时，上报 */
        if (ucIsCLmodeLast != ucIsCLmodeCurr)
        {
            NAS_MSCC_SndRrmRatCombModeInd();
        }
        #endif
        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSysCfgCnf(pstSysCfgCnf->enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcPowerOffResult_Main
Description     :   proc power off result ind
Input parameters:   VOS_VOID
Output parameters:  VOS_VOID
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2014-4-7
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2015-8-26
        Author  :   w00242748
        Modify content :Create
      3.日    期   : 2016年1月6日
        作    者   : w00242748
        修改内容   : DTS2015072705348:进入紧急呼回呼模式后，挂起HRPD和LTE；退出紧急呼
                     回呼模式后，再进行搜网，紧急呼回呼模式下，不进行其他任何形式搜网；
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcPowerOffResult_Main(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
)
{
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    VOS_RATMODE_ENUM_UINT32             enRatType;
#endif

    if (NAS_MSCC_POWEROFF_RSLT_POWER_SAVE_HRPD_LTE == enRslt)
    {
        NAS_MSCC_StopAllTimer();

        NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main();

        return;
    }

    if (NAS_MSCC_POWEROFF_RSLT_POWER_OFF == enRslt)
    {
        NAS_MSCC_StopAllTimer();

        /* Send the Power off result cnf to MMA */
        NAS_MSCC_SndMmaPowerOffRsltCnf();

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            enRatType = NAS_DYNLOAD_GetCurRatInCached(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W);

            (VOS_VOID)NAS_DYNLOAD_UnloadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatType);
        }
#endif

        /* Reset the Context For MSCC */
        NAS_MSCC_InitCtx(NAS_MSCC_INIT_CTX_POWEROFF);

        /* set next state to NULL */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_NULL);

        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* stop all timer */
    NAS_MSCC_StopAllTimer();

    NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_DEACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SLEEP_TIMER, NAS_MSCC_GetSleepTimerLength());
#endif

    return;
}

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 函 数 名  : NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main
 功能描述  : 在开机完成后，处理动态加载的处理
 输入参数  : ucImsVoiceAvail           -IMS voice是否可用
             ucIsExistPersistentBearer -persistent eps bearer是否存在标识
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月27日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年4月25日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main(VOS_VOID)
{
    VOS_RATMODE_ENUM_UINT32                                 enRatMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enUtranMode;

    enRatMode = VOS_RATMODE_BUTT;

    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Deactive
Description     :   在deactive状态下，收到MMA的用户PLMN请求消息
Input parameters:   ulEventType -- 事件类型
                    pstMsg      -- 消息
Output parameters:  VOS_VOID
Return Value    :   VOS_TRUE  -- 消息处理完毕；
                    VOS_FALSE -- 消息需要进一步处理
Modify History:
    1)  Date    :   2015-12-30
        Author  :   y00245242
        Modify content :Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Active
Description     :   在active状态下，收到MMA的用户PLMN请求消息
Input parameters:   ulEventType -- 事件类型
                    pstMsg      -- 消息
Output parameters:  VOS_VOID
Return Value    :   VOS_TRUE  -- 消息处理完毕；
                    VOS_FALSE -- 消息需要进一步处理
Modify History:
    1)  Date    :   2015-12-30
        Author  :   y00245242
        Modify content :Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果available定时器在运行，表明DO&L都无服务，需要触发搜网 */
    if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_AVAILABLE_TIMER))
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));
    }

    return VOS_TRUE;
}
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


