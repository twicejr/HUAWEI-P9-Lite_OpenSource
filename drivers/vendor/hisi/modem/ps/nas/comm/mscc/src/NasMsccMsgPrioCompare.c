
/*****************************************************************************
  1. Including header files
*****************************************************************************/
#include  "NasComm.h"
#include  "NasMsccSndInternalMsg.h"
#include  "NasMsccMsgPrioCompare.h"
#include  "NasMsccCtx.h"
#include  "MmaMsccInterface.h"
#include  "NasMsccFsmSysAcqTbl.h"
#include  "NasMsccFsmSysAcq.h"

#include "NasMsccFsmBsrTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 Global Variable Define
*****************************************************************************/




NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithSystemAcquireTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MSCC_SCAN_TIMER),
                             NAS_MSCC_CompareTiScanTimerExpiredPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithSystemAcquire),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF),
                              NAS_MSCC_CompareMoCallSuccessNtfPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_XSD, ID_XSD_MSCC_EMC_CALLBACK_IND),
                              NAS_MSCC_CompareEmcCallBackIndPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_CompareHsdRfAvailableIndPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER),
                              NAS_MSCC_CompareTi1xSrvClSysAcqPhaseOneTotalTimerExpiredPrioWithSystemAcquire),
#endif

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF),
                             NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSystemAcquire),
};



NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithBSRTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF),
                              NAS_MSCC_CompareMoCallSuccessNtfPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_XSD, ID_XSD_MSCC_EMC_CALLBACK_IND),
                              NAS_MSCC_CompareEmcCallBackIndPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF),
                             NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithBSR),

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_INTERSYS_START_IND),
                              NAS_MSCC_CompareHsdInterSysStartIndPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND),
                              NAS_MSCC_CompareMmcInterSysStartIndPrioWithBSR),
    #endif
};



NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithPowerOffTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_PLMN_USER_RESEL_REQ),
                              NAS_MSCC_CompareMmaUserReselReqPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_XSD, ID_XSD_MSCC_EMC_CALLBACK_IND),
                              NAS_MSCC_CompareEmcCallBackIndPrioWithPowerOff),
};



NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithCLInterSysTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithCLInterSys),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MSCC_SCAN_TIMER),
                             NAS_MSCC_CompareTiScanTimerExpiredPrioWithCLInterSys),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF),
                             NAS_MSCC_CompareTiWaitMmcPlmnSearchCnfTimerExpiredPrioWithCLInterSys),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithCLInterSys),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF),
                              NAS_MSCC_CompareMoCallSuccessNtfPrioWithCLInterSys),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_XSD, ID_XSD_MSCC_EMC_CALLBACK_IND),
                              NAS_MSCC_CompareEmcCallBackIndPrioWithCLInterSys),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF),
                             NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithCLInterSys),
};

/* Added by w00176964 for CL数传切换优化, 2015-12-11, begin */


NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithSysCfgTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF),
                             NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSysCfg),
};

/* Added by w00176964 for CL数传切换优化, 2015-12-11, end */


NAS_MSCC_FSM_MSG_COMPARE_STRU g_astMsccMsgCompareTbl[] =
{
    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_SYS_ACQ,
                                  g_astMsccMsgPrioCompareWithSystemAcquireTbl),

    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION,
                                  g_astMsccMsgPrioCompareWithBSRTbl),

    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_CL_INTERSYS,
                                  g_astMsccMsgPrioCompareWithCLInterSysTbl),
    /* Added by w00176964 for CL数传切换优化, 2015-12-11, begin */
    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_SYSTEM_CONFIG,
                                  g_astMsccMsgPrioCompareWithSysCfgTbl),
    /* Added by w00176964 for CL数传切换优化, 2015-12-11, end */

    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_POWER_OFF,
                                  g_astMsccMsgPrioCompareWithPowerOffTbl)

};


/*****************************************************************************
  3 Function Implement
*****************************************************************************/

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiScanTimerExpiredPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTi1xSrvClSysAcqPhaseOneTotalTimerExpiredPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareHsdRfAvailableIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 对于RF触发搜搜网的场景,LTE在进行全频点搜的时候可以打断L，先搜DO，
        对于在搜DO的状态可以丢弃；
        对于其他状态可以缓存；*/
    VOS_UINT32                                              ulState;
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    enSysAcqScene = NAS_MSCC_GetCLSysAcqScene_SysAcq();

    if (NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE == enSysAcqScene)
    {
        ulState     = NAS_MSCC_GetFsmTopState();

        if (NAS_MSCC_PIF_PLMN_SEARCH_SPEC == NAS_MSCC_GetSysAcqLteSrchType_SysAcq())
        {
            if ((NAS_MSCC_SYSACQ_STA_WAIT_MMC_PLMN_SEARCH_CNF == ulState)
             || (NAS_MSCC_SYSACQ_STA_WAIT_HSD_POWER_SAVE_CNF  == ulState))
            {
                return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
            }
        }

        if (ulState == NAS_MSCC_SYSACQ_STA_WAIT_HSD_ACQUIRE_CNF)
        {
            return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
        }
    }

    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}
#endif


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareMoCallSuccessNtfPrioWithSystemAcquire
 功能描述  : 主叫紧急呼的时候，与搜网状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMoCallSuccessNtfPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareEmcCallBackIndPrioWithSystemAcquire
 功能描述  : 收到退出回呼模式的时候，与关机状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == NAS_MSCC_GetEmcCallExistFlag())
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }
    else
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareHsdInterSysStartIndPrioWithBSR
 功能描述  : 收到hsd异系统开始指示时，与bsr状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE消息缓存

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : y00346957
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareHsdInterSysStartIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulState;

    ulState     = NAS_MSCC_GetFsmTopState();

    if ((NAS_MSCC_BSR_STA_WAIT_HSD_BG_SEARCH_CNF      == ulState)
     || (NAS_MSCC_BSR_STA_WAIT_HSD_STOP_BG_SEARCH_CNF == ulState))
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareHsdInterSysStartIndPrioWithBSR
 功能描述  : 收到mmc异系统开始指示时，与bsr状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE消息缓存

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : y00346957
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMmcInterSysStartIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulState;

    ulState     = NAS_MSCC_GetFsmTopState();

    if ((NAS_MSCC_BSR_STA_WAIT_MMC_BG_SEARCH_CNF      == ulState)
     || (NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF == ulState))
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSystemAcquire
 功能描述  : 收到快搜请求时，与搜网状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE消息缓存

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月13日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;
    VOS_UINT32                          ulState;

    enFsmId = NAS_MSCC_GetCurrFsmId();
    ulState = NAS_MSCC_GetFsmTopState();

    if ( (NAS_MSCC_FSM_SYS_ACQ== enFsmId)
      && ( (NAS_MSCC_SYSACQ_STA_WAIT_HSD_ACQUIRE_CNF == ulState)
        || (NAS_MSCC_SYSACQ_STA_WAIT_MMC_POWER_SAVE_CNF == ulState) ) )
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareMoCallSuccessNtfPrioWithBSR
 功能描述  : 主叫紧急呼的时候，与搜网状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMoCallSuccessNtfPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareEmcCallBackIndPrioWithBSR
 功能描述  : 收到退出回呼模式的时候，与关机状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == NAS_MSCC_GetEmcCallExistFlag())
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }
    else
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSystemAcquire
 功能描述  : 收到快搜请求时，与背景搜状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE消息缓存

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}




NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareEmcCallBackIndPrioWithPowerOff
 功能描述  : 收到退出回呼模式的时候，与关机状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == NAS_MSCC_GetEmcCallExistFlag())
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }
    else
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMmaUserReselReqPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}
/*****************************************************************************
Function Name   :   NAS_MSCC_CompareSysCfgSetPrioWithCLInterSys
Description     :   在CL异系统流程状态机比较SYSCFG请求的优先级
Input parameters:   VOS_VOID
Outout parameters:  NONE
Return Value    :   the compare result enum
Modify History  :
1)  Date           : 5/11/2015
    Author         : w00176964
    Modify content : Create
*****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_CompareTiScanTimerExpiredPrioWithCLInterSys
Description     :   在CL异系统流程状态机比较SCAN TIMER超时消息的优先级
Input parameters:   VOS_VOID
Outout parameters:  NONE
Return Value    :   the compare result enum
Modify History  :
1)  Date           : 5/11/2015
    Author         : w00176964
    Modify content : Create
*****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiScanTimerExpiredPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_CompareTiWaitMmcPlmnSearchCnfTimerExpiredPrioWithCLInterSys
Description     :   在CL异系统流程状态机比较等待MMC的搜网回复定时超时消息的优先级
Input parameters:   VOS_VOID
Outout parameters:  NONE
Return Value    :   the compare result enum
Modify History  :
1)  Date           : 5/11/2015
    Author         : w00176964
    Modify content : Create
*****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiWaitMmcPlmnSearchCnfTimerExpiredPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ComparePowerOffReqPrioWithCLInterSys
Description     :   在CL异系统流程状态机比较关机请求的优先级
Input parameters:   VOS_VOID
Outout parameters:  NONE
Return Value    :   the compare result enum
Modify History  :
1)  Date           : 5/11/2015
    Author         : w00176964
    Modify content : Create
*****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareMoCallSuccessNtfPrioWithBSR
 功能描述  : 主叫紧急呼的时候，与搜网状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMoCallSuccessNtfPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareEmcCallBackIndPrioWithCLInterSys
 功能描述  : 收到退出回呼模式的时候，与关机状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == NAS_MSCC_GetEmcCallExistFlag())
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }
    else
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithCLInterSys
 功能描述  : 收到快搜请求时，与CL异系统状态机比较优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE消息缓存

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/* Added by w00176964 for CL数传切换优化, 2015-12-11, begin */

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf = VOS_NULL_PTR;

    pstCdmaMoCallRedialSysAcqNtf = (MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU*)pstMsg;

    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallRedialSysAcqNtf->enCallType)
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_BUTT;
}

/* Added by w00176964 for CL数传切换优化, 2015-12-11, end */





NAS_MSCC_MSG_COMPARE_FUNC  NAS_MSCC_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
)
{
    NAS_MSCC_FSM_MSG_COMPARE_STRU      *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;

    for (i = 0 ; i < (sizeof(g_astMsccMsgCompareTbl)/sizeof(NAS_MSCC_FSM_MSG_COMPARE_STRU)) ; i++ )
    {
        if ( enFsmId == g_astMsccMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMsccMsgCompareTbl[i];
            break;
        }
    }

    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        #if 0
        if (NAS_MSCC_WILDCARD_MSG_ID == pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType )
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
        #endif

        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    return VOS_NULL_PTR;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_COMPARE_FUNC                               pfCompareFunc;
    NAS_MSCC_FSM_ID_ENUM_UINT32                             enCurrFsmId;
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8               enRslt;

    enCurrFsmId         = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetMsgComparePrioRslt: NAS_MSCC_GetCurrFsmId return NAS_MSCC_BUTT");
    }

    pfCompareFunc       = NAS_MSCC_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    if (VOS_NULL_PTR == pfCompareFunc )
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    enRslt = pfCompareFunc(ulEventType, pstMsg);

    return enRslt;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

