

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdFsmPowerSave.h"
#include  "CnasHsdFsmPowerSaveTbl.h"
#include  "CnasHsdProcCard.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasTimerMgmt.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasHsdFsmSysAcq.h"
#include  "NasMntn.h"
#include  "CnasHsdSndHsm.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_POWER_SAVE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_UINT32  CNAS_HSD_RcvMsccPowerSaveReq_PowerSave_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存入口消息 */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 通知HSM进入power save状态 */
    CNAS_HSD_SndHsmPowerSaveReq();

    /* 迁移到 CNAS_HSD_POWER_SAVE_STA_WAIT_HSM_POWERSAVE_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_SAVE_STA_WAIT_HSM_POWERSAVE_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF, TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvCasSuspendCnf_PowerSave_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移，并给MMA回复关机消息 */
    CNAS_HSD_SndPowerSaveRslt();

    /* 关机完成，退出层二状态机*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvTiWaitCasSuspendCnfExpired_PowerSave_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo;

    /* 复位底层 */
    PS_MEM_SET(&stCnasRebootInfo, 0x0, sizeof(CNAS_REBOOT_INFO_STRU));
    stCnasRebootInfo.enRebootScene = CNAS_REBOOT_SCENE_TI_HSD_WAIT_CAS_SUSPEND_CNF_EXPIRED;
    stCnasRebootInfo.ulPid         = UEPS_PID_HSD;
    stCnasRebootInfo.ulFsmId       = CNAS_HSD_GetCurrFsmId();
    stCnasRebootInfo.ulFsmState    = CNAS_HSD_GetFsmTopState();

    /* 复位后直接退出 */
    CNAS_SoftReboot(stCnasRebootInfo);

    /* 关机完成，退出层二状态机*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvHsmPowerSaveCnf_PowerSave_WaitHsmPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF);

    /* 通知CAS进入Suspend状态 */
    CNAS_HSD_SndCasSuspendReq();

    /* 迁移到 CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_SUSPEND_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_SUSPEND_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF, TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvTiWaitHsmPowerSaveCnfExpired_PowerSave_WaitHsmPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 通知CAS进入Suspend状态 */
    CNAS_HSD_SndCasSuspendReq();

    /* 迁移到 CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_SUSPEND_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_SUSPEND_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF, TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_HSD_RcvRrmStatusInd_PowerSave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 缓存 */
    CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



