/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmPowerSave.c
  版 本 号   : 初稿
  作    者   : Z00316370
  生成日期   : 2015年04月08日
  功能描述   : HRPD SD L2 POWER_SAVE状态机事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月08日
    作    者   : Z00316370
    修改内容   : 创建文件
******************************************************************************/

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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerSaveReq_PowerSave_Init
 功能描述  : PowerSave状态机初始化状态收到ID_MSCC_HSD_POWER_SAVE_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月03日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasSuspendCnf_PowerOff_WaitCasSuspendCnf
 功能描述  : HSD在WaitCasSuspendCnf状态下，收到CAS的Suspend回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月03日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitCasSuspendCnfExpired_PowerSave_WaitCasSuspendCnf
 功能描述  : HSD在WaitCasSuspendCnf状态下，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月03日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsmPowerSaveCnf_PowerSave_WaitHsmPowerSaveCnf
 功能描述  : HSD在HsmPowerSaveCnf状态下，收到HSM的power save回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月09日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitHsmPowerSaveCnfExpired_PowerSave_WaitHsmPowerSaveCnf
 功能描述  : HSD在WaitHsmPowerSaveCnf状态下，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月09日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvRrmStatusInd_PowerSave
 功能描述  : HSD在PowerSave流程中接收到RF_AVAIL消息需要进行缓存操作
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年1月5日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
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



