

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdFsmPowerOff.h"
#include  "CnasHsdFsmPowerOffTbl.h"
#include  "CnasHsdProcCard.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasTimerMgmt.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdSndHlu.h"
#include  "CnasHsdFsmSysAcq.h"
#include  "NasMntn.h"
#include  "CnasHsdSndEhsm.h"
#include  "CnasHsdSndRrm.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_POWER_OFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_UINT32  CNAS_HSD_RcvMsccPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存入口消息 */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 停止HSD所有定时器 */
    CNAS_StopAllTimerWithSpecifiedPid(UEPS_PID_HSD);

    /* 向RRM发送去注册消息 */
    CNAS_HSD_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH);

    /* 通知EHSM关机 */
    CNAS_HSD_SndEhsmPowerOffReq(EHSM_HSD_POWER_OFF_CAUSE_NORMAL);

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_EHSM_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_EHSM_POWEROFF_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF, TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvHsmPowerOffCnf_PowerOff_WaitHsmPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF);

    /* 通知HLU关机 */
    CNAS_HSD_SndHluPowerOffReq();

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF, TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvTiWaitHsmPowerOffCnfExpired_PowerOff_WaitHsmPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitHsmPowerOffCnfExpired_PowerOff_WaitHsmPowerOffCnf:wait hsm power off expired");

    /* 通知HLU关机 */
    CNAS_HSD_SndHluPowerOffReq();

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF, TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}


VOS_UINT32 CNAS_HSD_RcvHluPowerOffCnf_PowerOff_WaitHluPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF);

    /* 通知CAS关机 */
    CNAS_HSD_SndCasPowerOffReq();

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF, TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvTiWaitHluPowerOffCnfExpired_PowerOff_WaitHluPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitHluPowerOffCnfExpired_PowerOff_WaitHluPowerOffCnf:wait hlu power off expired");

    /* 通知CAS关机 */
    CNAS_HSD_SndCasPowerOffReq();

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF, TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Receive Msg!");

    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF);

    /* 把混合搜网状态清除 */
    CNAS_HSD_CleanSysAcqStatus();

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移，并给MMA回复关机消息 */
    CNAS_HSD_SndPowerOffRslt();

    /* 关机完成，退出层二状态机*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_HSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf:wait cas power off expired");

    /* 把混合搜网状态清除 */
    CNAS_HSD_CleanSysAcqStatus();

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移，并给MMA回复关机消息 */
    CNAS_HSD_SndPowerOffRslt();

    /* 关机完成，退出层二状态机*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;

}


VOS_UINT32  CNAS_HSD_RcvEhsmPowerOffCnf_PowerOff_WaitEhsmPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF);

    /* 通知HSM关机 */
    CNAS_HSD_SndHsmPowerOffReq();

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF, TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvTiWaitEhsmPowerOffCnfExpired_PowerOff_WaitEhsmPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitEhsmPowerOffCnfExpired_PowerOff_WaitEhsmPowerOffCnf:wait hsm power off expired");

    /* 通知HSM关机 */
    CNAS_HSD_SndHsmPowerOffReq();

    /* 迁移到 CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF, TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



