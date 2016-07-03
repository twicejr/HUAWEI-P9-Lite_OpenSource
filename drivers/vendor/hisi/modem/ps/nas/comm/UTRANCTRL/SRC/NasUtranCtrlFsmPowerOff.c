



/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"
#include "PsTypeDef.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlCtx.h"
#include "NasMmlCtx.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasUtranCtrlCommFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_POWEROFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 全局变量
*****************************************************************************/


/*****************************************************************************
  3 宏定义
*****************************************************************************/


VOS_UINT32 NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到W下关机回复后，通知TD模块关机 */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(TPS_PID_RRC);

    /* 迁移状态到等到TD模的关机回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN);

    /* 不进入后续MMC状态机处理 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到W下关机回复后，通知TD模块关机 */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(TPS_PID_RRC);

    /* 迁移状态到等到TD模的关机回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN);

    /* 不进入后续MMC状态机处理 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到TD下关机回复后，通知W模块关机 */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(WUEPS_PID_WRR);

    /* 迁移状态到等到W模的关机回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN);

    /* 不进入后续MMC状态机处理 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将构造的关机成功消息作为状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到TD下关机回复后，通知W模块关机 */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(WUEPS_PID_WRR);

    /* 迁移状态到等到W模的关机回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN);

    /* 不进入后续MMC状态机处理 */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitWasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL停止等待WAS回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF);

    /* UTRANCTRL状态机回到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 进入后续MMC状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitWasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitWasPowerOffCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_WaitWasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_POWER_OFF_CNF_STRU             stNasPowerOffCnf;
    VOS_UINT32                          ulPowerOffEventType;


    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_WaitWasPowerOffCnf: ENTERED");

    /* 构造关机回复消息 */
    NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(WUEPS_PID_WRR,
                                          WUEPS_PID_MMC,
                                          &stNasPowerOffCnf);

    ulPowerOffEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)&stNasPowerOffCnf );

    /* 将构建的关机回复消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulPowerOffEventType,
                                           (struct MsgCB *)&stNasPowerOffCnf);

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* UTRANCTRL状态机回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息未被处理完成需MMC继续处理 */
    return VOS_FALSE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitTdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL停止等待TD回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF);

    /* 回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitTdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitTdPowerOffCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_WaitTdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_POWER_OFF_CNF_STRU             stNasPowerOffCnf;
    VOS_UINT32                          ulPowerOffEventType;


    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_WaitTdPowerOffCnf: ENTERED");

    /* 构造关机回复消息 */
    NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(WUEPS_PID_WRR,
                                          WUEPS_PID_MMC,
                                          &stNasPowerOffCnf);

    ulPowerOffEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)&stNasPowerOffCnf );

    /* 将更改过的超时消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulPowerOffEventType,
                                           (struct MsgCB *)&stNasPowerOffCnf);

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

