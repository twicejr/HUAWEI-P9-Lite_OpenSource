/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmPowerOff.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : HRPD SD L2关机状态机事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerOffReq_PowerOff_Init
 功能描述  : POWER_OFF状态机初始化状态收到ID_MMA_HSD_POWER_OFF_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数
 2.日    期   : 2015年06月07日
   作    者   : z00316370
   修改内容   : 先给EHSM发送关机

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsmPowerOffCnf_PowerOff_WaitXccPowerOffCnf
 功能描述  : HSD在WAIT_HSM_POWER_OFF_CNF状态下，收到HSM的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf
 功能描述  : 等待HSM关机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf
 功能描述  : HSD在WAIT_HLU_POWEROFF_CNF状态下，收到HLU的的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitHluPowerOffCnfExpired_PowerOff_WaitHluPowerOffCnf
 功能描述  : 等待HLU模块的关机确认消息，定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  :
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf
 功能描述  : HSD在WAIT_CAS_POWER_OFF_CNF状态下，收到CAS的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf
 功能描述  : 等待接入层的关机确认消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月9日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvEhsmPowerOffCnf_PowerOff_WaitEhsmPowerOffCnf
 功能描述  : HSD在WAIT_EHSM_POWER_OFF_CNF状态下，收到EHSM的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月05日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitEhsmPowerOffCnfExpired_PowerOff_WaitEhsmPowerOffCnf
 功能描述  : 等待EHSM关机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月05日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
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



