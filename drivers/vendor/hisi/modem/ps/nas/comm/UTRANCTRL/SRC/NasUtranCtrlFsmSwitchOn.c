

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"
#include "PsTypeDef.h"
#include "NasUtranCtrlFsmSwitchOn.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SWITCHON_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

VOS_UINT32 NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到W下开机回复后，通知TD模开机 */
    NAS_UTRANCTRL_SndGuAsStartReq(TPS_PID_RRC);

    /* 迁移状态到等到TD模的开机回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_TD_START_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF, TI_NAS_UTRANCTRL_WAIT_TD_START_CNF_LEN);

    /* 不进入后续状态机处理 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 收到TD下开机回复后，通知W模块开机 */
    NAS_UTRANCTRL_SndGuAsStartReq(WUEPS_PID_WRR);

    /* 迁移状态到等到W模的开机回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_WAS_START_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF_LEN);

    /* 不进入后续状态机处理 */
    return VOS_TRUE;
}



VOS_UINT32  NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL停止等待WAS回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF);

    /* 适配模块状态机回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 进入后续开机状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrMmStartCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg        = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstRrMmStartCnfMsg = (RRMM_START_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf: ENTERED");

    /* 认为当前开机失败 */
    pstRrMmStartCnfMsg->ulResult = MMC_START_FAILURE;

    /* 将当前开机失败消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* 设置需要替换入口消息标记，这样MMC模块就会处理开机回复失败消息 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* UTRANCTRL状态机回到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息未被处理完成需MMC继续处理 */
    return VOS_FALSE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL停止等待TD回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF);

    /* 适配模块状态机回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 进入后续开机状态机处理 */
    return VOS_FALSE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}



VOS_UINT32  NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrMmStartCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg        = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstRrMmStartCnfMsg = (RRMM_START_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf: ENTERED");

    /* 认为当前开机失败 */
    pstRrMmStartCnfMsg->ulResult = MMC_START_FAILURE;

    /* 将当前开机失败消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* 设置需要替换入口消息标记，这样MMC模块就会处理开机回复失败消息 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* UTRANCTRL状态机回到main状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息未被处理完成需MMC继续处理 */
    return VOS_FALSE;
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
