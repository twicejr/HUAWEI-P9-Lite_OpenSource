

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "v_typdef.h"
#include "NasComm.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmSyscfg.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasUtranCtrlCommFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SYSCFG_C


#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数实现
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到W下SYSCFG回复后，通知TD模SYSCFG设置 */
    NAS_UTRANCTRL_SndGuAsSyscfgReq(TPS_PID_RRC);

    /* 迁移状态到等到TD模的SYSCFG回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SYSCFG_STA_WAIT_TD_SYSCFG_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF_LEN);

    /* 不进入后续状态机处理 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到TD下SYSCFG回复后，通知W模SYSCFG设置 */
    NAS_UTRANCTRL_SndGuAsSyscfgReq(WUEPS_PID_WRR);

    /* 迁移状态到等到W模的SYSCFG回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF_LEN);

    /* 不进入后续状态机处理 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL停止等待WAS回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF);

    /* 适配模块状态机回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 进入后续MMC的SYSCFG状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 向接入层回复挂起失败 */
    NAS_UTRANCTRL_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

    return VOS_TRUE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}




VOS_UINT32 NAS_UTRANCTRL_RcvTiWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg     = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstSysCfgCnfMsg = (RRMM_SYS_CFG_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf: ENTERED");

    /* 认为当前SYSCFG设置失败 */
    pstSysCfgCnfMsg->ulResult = RRMM_SYS_CFG_RESULT_FAILURE;

    /* 将缓存的SYSCFG消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* 设置需要替换入口消息标记，这样MMC模块就会处理SYSCFG设置失败消息 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL停止等待WAS回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF);

    /* 适配模块状态机回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 进入后续开机状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdSuspendInd_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 向接入层回复挂起失败 */
    NAS_UTRANCTRL_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, TPS_PID_RRC);

    return VOS_TRUE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTiTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg     = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstSysCfgCnfMsg = (RRMM_SYS_CFG_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf: ENTERED");

    /* 认为当前SYSCFG设置失败 */
    pstSysCfgCnfMsg->ulResult = RRMM_SYS_CFG_RESULT_FAILURE;

    /* 将SYSCFG设置失败消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* 设置需要替换入口消息标记，这样MMC模块就会处理SYSCFG设置失败消息 */
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
