/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NASUTRANCTRLFSMMODECHANGE.c
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2012年8月7日
  最近修改   :
  功能描述   : ModeChange状态机处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月7日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#include "NasUtranCtrlFsmModeChange.h"
#include "NasMmlLib.h"
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#endif

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoad.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_MODE_CHANGE_C

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
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init
 功能描述  : 模式变更初始化状态收到WAS系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年1月6日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台支持G/L时，才给G/L发送Utran_Mode_Req
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  保持当前入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W为主模时，将当前UtranMode通知L/G/TD */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
    }

    /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
       不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*迁到等待从模回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*启等待从模回复定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init
 功能描述  : 模式变更初始化状态收到TDRRC系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年1月6日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台支持G/L时，才给G/L发送Utran_Mode_Req
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  保持当前入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* TD为主模时，将当前UtranMode通知L/G/W */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
    }

    /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
       不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    /*迁到等待从模回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*启等待从模回复定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init
 功能描述  : 模式变更初始化状态收到GAS系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年1月6日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台支持G/L时，才给G/L发送Utran_Mode_Req
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  保持当前入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, NAS_UTRANCTRL_UTRAN_MODE_NULL);

        /*迁到等待主模回复状态 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_REL_CNF);

        /*启等待主模回复定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF, TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF_LEN);

        return VOS_TRUE;
    }
    else
#endif
    {
        /* G为主模时，将当前UtranMode通知L/W/TD */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
        {
            NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
            NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
        }
#endif

        /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
           不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
        NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

        NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

        /*迁到等待从模回复状态 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

        /*启等待从模回复定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

        return VOS_TRUE;
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init
 功能描述  : 模式变更初始化状态收到LMM系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年1月6日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台支持G/L时，才给G/L发送Utran_Mode_Req
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  保持当前入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(NAS_UTRANCTRL_UTRAN_MODE_NULL);

        /*迁到等待从模回复状态 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_REL_CNF);

        /*启等待从模回复定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF, TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF_LEN);

        return VOS_TRUE;
    }
    else
#endif
    {
        /* L为主模时，将当前UtranMode通知G/W/TD */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
        {
            NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
            NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
        }

        /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
           不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
        NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

        NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

        /*迁到等待从模回复状态 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

        /*启等待从模回复定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf
 功能描述  : 模式变更等待从模回复状态收到WAS的模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* 如果W为主模，不处理，直接返回 */
    if (NAS_UTRANCTRL_MASTER_MODE_WCDMA == enMasterMode)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* 收到WAS的UTRAN MODE CNF消息，清除等待标志 */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    /* 收到从模的回复后，调用处理从模回复的函数 */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf
 功能描述  : 模式变更等待从模回复状态收到TDRRC的模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* 如果TD为主模，不处理，直接返回 */
    if (NAS_UTRANCTRL_MASTER_MODE_TDSCDMA == enMasterMode)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* 收到TDRRC的UTRAN MODE CNF消息，清除等待标志 */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /* 收到从模的回复后，调用处理从模回复的函数 */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf
 功能描述  : 模式变更等待从模回复状态收到GAS的模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* 如果G为主模，不处理，直接返回 */
    if (NAS_UTRANCTRL_MASTER_MODE_GSM == enMasterMode)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* 收到GAS的UTRAN MODE CNF消息，清除等待标志 */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);

    /* 收到从模的回复后，调用处理从模回复的函数 */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf
 功能描述  : 模式变更等待从模回复状态收到LMM的模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* 如果L为主模，不处理，直接返回 */
    if (NAS_UTRANCTRL_MASTER_MODE_LTE == enMasterMode)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* 收到TDRRC的UTRAN MODE CNF消息，清除等待标志 */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);

    /* 收到从模的回复后，调用处理从模回复的函数 */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTotalUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf
 功能描述  : 模式变更等待从模回复状态收到等待从模回复的定时器超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf: ENTERED");

    /* 向主模发模式通知 */
    NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(NAS_UTRANCTRL_GetMasterMode_ModeChange());

    /* 启等待主模回复定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF_LEN);

    /* 迁到等待主模回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf
 功能描述  : 模式变更等待主模回复状态收到WAS的模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU                           *pstEntryMsg;

    /* 停等待主模回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF);

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg( pstEntryMsg->ulEventType,
                                     (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* 设置缓存消息有效标志 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 退出MODE CHANGE状态机，切换到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf
 功能描述  : 模式变更等待主模回复状态收到WAS的模式变更回复定时器超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf: ENTERED");

    /* 清除所有等待模式变更回复的标志 */
    NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange();

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg( pstEntryMsg->ulEventType,
                                     (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* 设置缓存消息有效标志 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 退出MODE CHANGE状态机，切换到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange
 功能描述  : 模式变更状态机收到从模回复状态后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
)
{
    VOS_UINT8                           ucWaitSlaveModeUtranModeCnfFlg;

    ucWaitSlaveModeUtranModeCnfFlg = NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange();

    if (NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_NULL != ucWaitSlaveModeUtranModeCnfFlg)
    {
        return;
    }

    /* 如果已经收齐三个从模的回复，停等待从模回复定时器,给主模发模式变更请求，
       启等待主模回复定时器，迁到等待主模回复状态 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(enMasterMode);

    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF);

    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange
 功能描述  : 根据不同的主模给相应的主模发送模式变更请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
)
{

    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                      enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    switch (enMasterMode)
    {
        case NAS_UTRANCTRL_MASTER_MODE_WCDMA:
            NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
            break;

        case NAS_UTRANCTRL_MASTER_MODE_TDSCDMA:
            NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
            break;

        case NAS_UTRANCTRL_MASTER_MODE_GSM:
            NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_UTRANCTRL_MASTER_MODE_LTE:
            NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
            break;
#endif

        default:
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange: unexpected master mode.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetMasterMode_ModeChange
 功能描述  : 获取当前主模
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8：主模类型
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-8-8
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  NAS_UTRANCTRL_GetMasterMode_ModeChange(VOS_VOID)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU                           *pstEntryMsg;
    MSG_HEADER_STRU                                        *pstHead;
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode;

    /*  取保存的入口消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstHead     = (MSG_HEADER_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    switch (pstHead->ulSenderPid)
    {
        case WUEPS_PID_WRR:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_WCDMA;
            break;

        case TPS_PID_RRC:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_TDSCDMA;
            break;

        case UEPS_PID_GAS:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_GSM;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_MM:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_LTE;
            break;
#endif

        default:
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf: ENTERED");
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_BUTT;
            break;
    }

    return enMasterMode;
}

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvLmmMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf
 功能描述  : 模式变更等待G主模释放回复状态收到主模模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月25日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvGasMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    /* 停等待主模回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF);

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
    enRatMode       = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enCurrUtranMode);

    (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
    }
#endif

    /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
       不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*迁到等待从模回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*启等待从模回复定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvLmmMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf
 功能描述  : 模式变更等待L主模释放回复状态收到主模模式变更回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月25日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvLmmMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    /* 停等待主模回复定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF);

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
    enRatMode       = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enCurrUtranMode);

    (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);

    /* L为主模时，将当前UtranMode通知G/W/TD */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
    }

    /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
       不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*迁到等待从模回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*启等待从模回复定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitMasterModeRelCnfExpired_ModeChange_WaitMasterModeRelCnf
 功能描述  : 模式变更等待G/L主模释放回复状态收到定时器超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月25日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitMasterModeRelCnfExpired_ModeChange_WaitMasterModeRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg = VOS_NULL_PTR;

    NAS_TRACE_HIGH("NAS_UTRANCTRL_RcvTiWaitMasterModeRelCnfExpired_ModeChange_WaitMasterModeRelCnf\r\n");

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
    enRatMode       = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enCurrUtranMode);

    (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);

    if (NAS_UTRANCTRL_BuildEventType(PS_PID_MM, ID_LMM_MMC_SYS_INFO_IND) == pstEntryMsg->ulEventType)
    {
        /* L为主模时，将当前UtranMode通知G/W/TD */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
        {
            NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
            NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
        }
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
        {
            NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
            NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
        }
#endif
    }

    /* 如果平台只支持W/TD中的一个，或者两者都不支持，会在NAS_UTRANCTRL_MsgProc或NAS_UTRANCTRL_ProcessMmcMsg返回VOS_FALSE
       不会进到Utran的状态机里，所以此处不需要判断平台是否支持W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*迁到等待从模回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*启等待从模回复定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}


#endif


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

