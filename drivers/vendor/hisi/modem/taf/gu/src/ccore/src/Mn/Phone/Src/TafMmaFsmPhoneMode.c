/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmPhoneMode.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月8日
  最近修改   :
  功能描述   : TafMmaFsmPhoneMode.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月7日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafTypeDef.h"
#include "MmaMsccInterface.h"
#include "TafMmaFsmPhoneMode.h"
#include "TafMmaCtx.h"
#include "TafSdcCtx.h"
#include "TafOamInterface.h"
#include "Taf_Status.h"
#include "MmaAppLocal.h"
#include "rfa.h"
#include "NasUsimmApi.h"
#include "msp_nvim.h"
#include "TTFMemInterface.h"
#include "TafMmaMain.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafMmaSndInternalMsg.h"
#include "TafLog.h"
#include "TafMmaTimerMgmt.h"
#include "TafAppMma.h"
#include "TafMmaSndTaf.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2014-1-3, begin */
#include "TafMmaProcNvim.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2014-1-3, end */
#include "MmaUphyInterface.h"
/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
#include "TafMmaSndApp.h"
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */
#include "TafMmaSndMscc.h"
#include "NasMntn.h"
#include "NasComm.h"
#include "TafMmaComFunc.h"

#include "TafMmaSndUphy.h"

#include "TafMmaSndMtc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
extern VOS_UINT8                                g_ucMmaOmConnectFlg;

extern VOS_UINT8                                g_ucMmaOmPcRecurEnableFlg;

extern MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8   g_ucMmaDeactSimWhenPoweroff;

extern MMA_ME_PERSONALISATION_STATUS_STRU       g_stMmaMePersonalisationStatus;

extern STATUS_CONTEXT_STRU                      g_StatusContext;

extern TAF_MMA_GLOBAL_VALUE_ST                  gstMmaValue;


extern MMA_TIMER_ST                             g_stPowerDownDelayTimer;

extern MN_PH_REG_TIME_INFO_STRU                 g_stRegTimeInfo;

/*lint -save -e958 */

/*****************************************************************************
  6 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaInterPowerInit_PhoneMode_Init
 功能描述  : 收到MMA的内部上电开机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年4月1日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:修改状态名称和定时器名称
 3.日    期   : 2014年7月11日
   作    者   : y00213812
   修改内容   : 增加开机顺序设置的有效性判断
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 保存的入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    if (VOS_TRUE == TAF_MMA_IsExternalModuleInitCompeleted())
    {
        if (MMA_UPHY_INIT_STATUS_FAIL == TAF_MMA_GetPhyInitStatus())
        {
            NAS_TRACE_HIGH("MMA UPHY INIT FAIL!!!!!!!!");

            /* 上报当前的RAT模式 */
            TAF_MMA_SndRatModInd_PhoneMode();

            /* 回复开机失败处理 */
            TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_FAIL);

            /* 记录错误类型，发送开机失败给OM or AT */
            TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
            TAF_MMA_ReportPhoneModeCnf_PhoneMode();

            /* 发送状态机退出消息 */
            TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

            /* 退出状态机 */
            TAF_MMA_FSM_QuitSubFsm();

            return VOS_TRUE;
        }

        /* 上电第一次收到卡状态变化,自动开机场景需要投票禁止睡眠 */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
        TAF_MMA_ProcStartReq_PhoneMode();

        return VOS_TRUE;
    }

    /* 迁移状态到等待初始化完成状态上报 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT);

    /* 启动保护定时器,需要新增定时器启动和停止函数 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                       TAF_MMA_GetWaitExtTimerLen() * NAS_SDC_ONE_THOUSAND_MILLISECOND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init
 功能描述  : 收到MMA的内部USIM卡状态改变消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;

    ucIsCLWork          = TAF_MMA_IsPowerOnCLInterWork();
    ucIsUsimSrvAvail    = TAF_MMA_IsUsimServiceAvailable();
#endif

    /* 保存的入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_PTM)
    /* 非CL的模式且卡有效的情况下，才给AP上报关机 */
    if ((VOS_TRUE != ucIsCLWork)
     && (VOS_TRUE == ucIsUsimSrvAvail))
    {
        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_CS);

        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_PS);

        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_TRUE);
    }
#endif

    TAF_MMA_ProcPowerOffReq_PhoneMode();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init
 功能描述  : 收到OM的模式设置消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年3月22日
   作    者   : y00176023
   修改内容   : DSDS II wait the DSP init when start req
 3.日    期   : 2014年7月11日
   作    者   : y00213812
   修改内容   : 增加开机顺序设置的有效性判断
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;

    ucIsCLWork          = TAF_MMA_IsPowerOnCLInterWork();
    ucIsUsimSrvAvail    = TAF_MMA_IsUsimServiceAvailable();
#endif


    pstRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstPhModeSet        = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;
    enPhyInitStatus     = TAF_MMA_GetPhyInitStatus();

    /* 保存的入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 设置为FULL模式进行开机 */
    if (TAF_PH_MODE_FULL == pstPhModeSet->PhMode)
    {
         /* PC回放时不判断USIM的卡状态 */
#if defined(__PC_TRACE_RECUR__)
#else
        if (VOS_FALSE  == TAF_MMA_IsExternalModuleInitCompeleted())
        {
            /* 迁移状态到等待初始化完成状态上报 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT);


            /* 启动外部模块初始化保护定时器 */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT, TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT_LEN);


            return VOS_TRUE;
        }
#endif

        if (MMA_UPHY_INIT_STATUS_SUCCESS == enPhyInitStatus)
        {

            /* 进行开机流程 */
            TAF_MMA_ProcStartReq_PhoneMode();
        }
        else
        {
            /* 记录错误类型，发送开机失败给OM or AT */
            TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
            TAF_MMA_ReportPhoneModeCnf_PhoneMode();

            /* 发送开机失败结果消息 */
            TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

            /* 退出状态机 */
            TAF_MMA_FSM_QuitSubFsm();
        }

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_PTM)
    /* 非CL的模式且卡有效的情况下，才给AP上报关机 */
    if ((VOS_TRUE != ucIsCLWork)
     && (VOS_TRUE == ucIsUsimSrvAvail))
    {
        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_CS);

        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_PS);

        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_TRUE);
    }
#endif

    /* 否则走关机流程 */
    TAF_MMA_ProcPowerOffReq_PhoneMode();

    return VOS_TRUE;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTafPhoneModeSet_PhoneMode_Init
 功能描述  : 收到TAF的模式设置消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月14日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2014年3月22日
   作    者   : y00176023
   修改内容   : DSDS II wait the DSP init when start req
 3.日    期   : 2014年7月11日
   作    者   : y00213812
   修改内容   : 增加开机顺序设置的有效性判断

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafPhoneModeSet_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhModeSet    = VOS_NULL_PTR;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;

    ucIsCLWork          = TAF_MMA_IsPowerOnCLInterWork();
    ucIsUsimSrvAvail    = TAF_MMA_IsUsimServiceAvailable();
#endif


    pstPhModeSet        = (TAF_MMA_PHONE_MODE_SET_REQ_STRU*)pstMsg;
    enPhyInitStatus     = TAF_MMA_GetPhyInitStatus();

    /* 保存的入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 设置为FULL模式进行开机 */
    if (TAF_PH_MODE_FULL == pstPhModeSet->stPhoneModePara.PhMode)
    {
         /* PC回放时不判断USIM的卡状态 */
#if defined(__PC_TRACE_RECUR__)
#else
        if (VOS_FALSE  == TAF_MMA_IsExternalModuleInitCompeleted())
        {
            /* 迁移状态到等待初始化完成状态上报 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT);


            /* 启动外部模块初始化保护定时器 */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT, TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT_LEN);


            return VOS_TRUE;
        }
#endif
        if (MMA_UPHY_INIT_STATUS_SUCCESS == enPhyInitStatus)
        {
            /* 进行开机流程 */
            TAF_MMA_ProcStartReq_PhoneMode();
        }
        else
        {
            /* 记录错误类型，发送开机失败给OM or AT */
            TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
            TAF_MMA_ReportPhoneModeCnf_PhoneMode();

            /* 发送开机失败结果消息 */
            TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

            /* 退出状态机 */
            TAF_MMA_FSM_QuitSubFsm();
        }

        return VOS_TRUE;
    }


#if (FEATURE_ON == FEATURE_PTM)
    /* 非CL的模式且卡有效的情况下，才给AP上报关机 */
    if ((VOS_TRUE != ucIsCLWork)
     && (VOS_TRUE == ucIsUsimSrvAvail))
    {
        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_CS);

        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_PS);

        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_TRUE);
    }
#endif

    /* 否则走关机流程 */
    TAF_MMA_ProcPowerOffReq_PhoneMode();

    return VOS_TRUE;
}
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitExternalModuleInit
 功能描述  : 收到PIH模块上报的卡状态指示消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
2. 日    期   : 2014年3月21日
   作    者   : y00176023
   修改内容   : 增加物理层初始化判断启动协议栈
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;

    enPhyInitStatus                     = TAF_MMA_GetPhyInitStatus();

    /* 如果物理层已经报初始化结果，停止保护定时器，否则直接返回 */
    if (MMA_UPHY_INIT_STATUS_BUTT == enPhyInitStatus)
    {
        return VOS_TRUE;
    }
    else
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);
    }



#ifndef __PS_WIN32_RECUR__
    if ( (VOS_TRUE == g_ucMmaOmConnectFlg)
      && (VOS_TRUE == g_ucMmaOmPcRecurEnableFlg) )
    {
        NAS_MMA_SndOutsideFixedContextData();
    }
#endif

    /* 上电第一次收到卡状态变化,自动开机场景需要投票禁止睡眠 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
    TAF_MMA_ProcStartReq_PhoneMode();

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit
 功能描述  : 收到等待PIH模块上报的卡状态指示消息超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数

  2.日    期   : 2014年1月24日
    作    者   : z00234330
    修改内容   : dts2013112601036
  3.日    期   : 2014年3月21日
   作    者   : y00176023
   修改内容   : DSDS II 等待物理层初始化后启动协议栈
  4.日    期   : 2014年2月27日
   作    者   : z00234330
   修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
                at^cpin命令查询的会不正确。
  5.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
  6.日    期   : 2015年5月30日
    作    者   : f00179208
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* warning 打印 */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit:time expired!");

    /* 更新卡状态为卡无效 */
    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);



    /*物理层未初始化函数返回*/
    if (MMA_UPHY_INIT_STATUS_SUCCESS != TAF_MMA_GetPhyInitStatus())
    {
        /* 上报当前的RAT模式 */
        TAF_MMA_SndRatModInd_PhoneMode();

        NAS_TRACE_HIGH("MMA UPHY INIT TIMEOUT!!!!!!!!");

        /* 报给ril上报物理层初始化超时的结果 */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_TIMEOUT);

        /* 记录错误类型，发送开机失败给OM or AT */
        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* 发送状态机退出消息 */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

        return VOS_TRUE;
    }

    /* 上电第一次收到卡状态变化,自动开机场景需要投票禁止睡眠 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
    TAF_MMA_ProcStartReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvUphyInitStatusInd_PhoneMode_WaitExternalModuleInit
 功能描述  : 收到等待物理层上报初始化状态指示消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期    : 2014年3月21日
    作    者   : y00176023
    修改内容   : 新增
  2.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvUphyInitStatusInd_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    UPHY_MMA_INIT_STATUS_IND_STRU      *pstRcvMsg              = VOS_NULL;

    pstRcvMsg                       = (UPHY_MMA_INIT_STATUS_IND_STRU*)pstMsg;

    /*设置物理层初始化状态*/
    if (MMA_UPHY_INIT_STATUS_BUTT > pstRcvMsg->enInitStatus)
    {
        TAF_MMA_SetPhyInitStatus(pstRcvMsg->enInitStatus);
    }

    if (MMA_UPHY_INIT_STATUS_SUCCESS != pstRcvMsg->enInitStatus)
    {
        NAS_TRACE_HIGH("MMA UPHY INIT FAIL!!!!!!!!");

        /* 停止定时器 */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

        /* 上报当前的RAT模式 */
        TAF_MMA_SndRatModInd_PhoneMode();

        /* 报给ril结果 */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_FAIL);

        /* 记录错误类型，发送开机失败给OM or AT */
        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* 发送状态机退出消息 */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

        return VOS_TRUE;
    }


    /* 如果卡状态已经上报，则停止等待定时器 */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {
        /* 停止定时器 */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);
    }

    /* 上电开机获取国家码功能打开，且不是C核单独复位导致的上电，需要无卡开机，获取国家码 */
    if (VOS_TRUE  == TAF_MMA_IsNeedGetGeoNoSimStart())
    {
        /* 上电第一次收到物理层初始化消息,自动开机场景需要投票禁止睡眠 */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

        /* 此处不关心卡状态，不管有卡还是无卡都进行无卡开机 */
        TAF_MMA_ProcGetGeoNoSimStartReq_PhoneMode();

        return VOS_TRUE;
    }

    /* 如果USIM标志和物理层标志都为TRUE则启动协议栈 */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {

        /* 上电第一次收到物理层初始化消息,自动开机场景需要投票禁止睡眠 */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
        TAF_MMA_ProcStartReq_PhoneMode();
    }

    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : TAF_MMA_SndMmaStartReq_PhoneMode
 功能描述  : 向MSCC或IMSA发送开机请求,迁移状态,启动保护定时器
 输入参数  : ulReceivePid---接收PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月19日
    作    者   : s00217060
    修改内容   : coverity清理
  3.日    期   : 2014年07月08日
    作    者   : y00245242
    修改内容   : 为1X feature开发增加
  4.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : TSTS
  5.日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID TAF_MMA_SndStartReq_PhoneMode(
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8         enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8         enCsimCardStatus;
    TAF_MMA_RAT_ORDER_STRU                      stSndRatPrioList;
    TAF_SDC_USIM_STATUS_ENUM_UINT8              enUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8              enCsimStatus;
    TAF_MMA_RAT_ORDER_STRU                     *pstRatPrioList  = VOS_NULL_PTR;
    VOS_UINT32                                  ulEventType;
    VOS_UINT8                                   ucIsCardRefresh;
    TAF_SDC_SIM_TYPE_ENUM_UINT8                 enCsimType;
    TAF_SDC_SIM_TYPE_ENUM_UINT8                 enUsimType;

    enCsimType                                  = TAF_SDC_GetCsimType();
    enUsimType                                  = TAF_SDC_GetUsimType();

    ulEventType = TAF_MMA_GetCurrFsmMsgAddr()->ulEventType;
    ucIsCardRefresh                             = VOS_FALSE;

    enUsimStatus = TAF_SDC_GetUsimStatus();
    enCsimStatus = TAF_SDC_GetCsimStatus();

    /* 消除coverity告警 */
    if (TAF_SDC_USIM_STATUS_BUTT == enUsimStatus)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_SndStartReq_PhoneMode: Usim Status is BUTT!");
    }

    /* 消除coverity告警 */
    if (TAF_SDC_USIM_STATUS_BUTT == enCsimStatus)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_SndStartReq_PhoneMode: Csim Status is BUTT!");
    }

    /* 消除coverity告警 */
    if (TAF_SDC_SIM_TYPE_BUTT == enCsimType)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_SndStartReq_PhoneMode: Usim Type is BUTT!");
    }

    /* 消除coverity告警 */
    if (TAF_SDC_SIM_TYPE_BUTT == enUsimType)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_SndStartReq_PhoneMode: Csim Type is BUTT!");
    }

    /* 获取卡状态 */
    enUsimCardStatus = TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(enUsimStatus, enUsimType);
    enCsimCardStatus = TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(enCsimStatus, enCsimType);

    /* 获取接入技术信息 */
    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* Modified by s00217060 for coverity清理, 2014-02-19, begin */
    PS_MEM_SET(&stSndRatPrioList, 0, sizeof(TAF_MMA_RAT_ORDER_STRU));
    /* Modified by s00217060 for coverity清理, 2014-02-19, end */

    stSndRatPrioList.ucRatOrderNum = pstRatPrioList->ucRatOrderNum;
    PS_MEM_CPY(stSndRatPrioList.aenRatOrder,
               pstRatPrioList->aenRatOrder,
               pstRatPrioList->ucRatOrderNum);

    TAF_MMA_GetAvailablePlmnRatPrio(&stSndRatPrioList);

    /* 发送开机请求给UPHY */
    TAF_MMA_SndUphyPowerOnReq();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND) == ulEventType)
    {
        ucIsCardRefresh = VOS_TRUE;
    }

    /* 发送开机请求给MSCC */
    (VOS_VOID)TAF_MMA_SndMsccStartReq(&stSndRatPrioList, enUsimCardStatus, enCsimCardStatus, ucIsCardRefresh);

    /* 迁移状态到等待MSCC的开机回复 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF);

    /* 启动保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF, TI_TAF_MMA_WAIT_MSCC_START_CNF_LEN);

}

/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode
 功能描述  : 将当前SDC的卡状态转换成MSCC格式的
 输入参数  : ucSdcSimStatus:当前SDC中的SIM卡状态
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 返回当前卡状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月18日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2014年1月24日
    作    者   : z00234330
    修改内容   : dts2013112601036

  3.日    期   : 2014年2月27日
    作    者   : z00234330
    修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
                at^cpin命令查询的会不正确
  4.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整(传入卡类型，分别进行替换)
*****************************************************************************/
NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(
    VOS_UINT8                           ucSdcSimStatus,
    VOS_UINT8                           ucSimType
)
{
    /* 在没有收到卡状态消息时或卡不在位或有PIN码时,作为无卡开机 */
    if ((TAF_SDC_USIM_STATUS_BUTT       == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_NO_PRESENT == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PIN    == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK    == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID    == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT    == ucSdcSimStatus))
    {
        return NAS_MSCC_PIF_CARD_STATUS_ABSENT;
    }

    if (TAF_PH_ME_SIM_LOCK == MMA_GetMeLockStatus())
    {
        return NAS_MSCC_PIF_CARD_STATUS_ABSENT;
    }

    if (TAF_SDC_SIM_TYPE_USIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_ROM_SIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_SIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_UIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_CSIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT;
    }
    else
    {
        return NAS_MSCC_PIF_CARD_STATUS_ABSENT;
    }
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndPowerOffReq_PhoneMode
 功能描述  : 向MSCC或IMSA发送关机请求,迁移状态,启动保护定时器
 输入参数  : ulReceivePid---接收PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年7月08日
   作    者   : y00245242
   修改内容   : 为1X feature开发增加
*****************************************************************************/
VOS_VOID TAF_MMA_SndPowerOffReq_PhoneMode(
    VOS_UINT32                          ulReceivePid
)
{
    TAF_MMA_SndMsccPowerOffReq(TAF_MMA_GetMsccPowerOffCause_PhoneMode());

    /* 迁移状态到等待MSCC的关机回复 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF);

    /* 启动保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF, TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF_LEN);

    return;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode
 功能描述  : MMA模块对于非上电开机成功的结果处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2014年2月19日
   作    者   : w00167002
   修改内容   : L-C互操作项目修改，不发送搜网
 3.日    期   : 2014年08月13日
   作    者   : s00217060
   修改内容   : DTS2014073007533:开机完成后，释放投票的操作延后，否则中间C核可能睡下去
*****************************************************************************/
VOS_VOID TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode(VOS_VOID)
{
    VOS_UINT8                                               ucNeedPinFlg;
    VOS_UINT8                                               ucSdcSimStatus;
    VOS_UINT16                                              usAppCfgSupportType;



    usAppCfgSupportType     = TAF_SDC_GetAppCfgSupportType();
    ucSdcSimStatus          = TAF_SDC_GetSimStatus();
    ucNeedPinFlg            = VOS_FALSE;

    /* 更新当前的模式为FULL模式 */
    TAF_SDC_SetCurPhoneMode(TAF_PH_MODE_FULL);

    if ((TAF_SDC_USIM_STATUS_SIM_PIN == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == ucSdcSimStatus))
    {
       ucNeedPinFlg = VOS_TRUE;
    }

    if (VOS_FALSE == ucNeedPinFlg)
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
        {
            (VOS_VOID)MMA_GetCsimMeLockStatus();
        }
        else
#endif
        {
            (VOS_VOID)MMA_GetMeLockStatus();
        }
    }

    TTF_MemCcpuCheckPoolLeak();

    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    if (SYSTEM_APP_WEBUI == usAppCfgSupportType)
    {
        if ((VOS_FALSE == ucNeedPinFlg)
         && (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus))
        {
            MN_PH_SimLockedRpt();
        }
    }

    /* Added by j00174725 for V9R1 干扰控制, 2013/08/12, begin */
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_ON);
#endif
    /* Added by j00174725 for V9R1 干扰控制, 2013/08/12, end */

    /* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */
    /* 读全局变量进行模式判断，如果不为C+L互操作模式，则发搜网注册请求 */
    if (VOS_TRUE != TAF_MMA_IsPowerOnCLInterWork())
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == TAF_SDC_IsPlatformSupport3Gpp2())
        {
            TAF_MMA_SndMsccCFreqLockNtf(TAF_MMA_GetCFreqLockSetPara());
        }
#endif
        TAF_MMA_SndMsccSystemAcquireReq();

        /* 卡有效的情况下，才给AP上报开机 */
#if (FEATURE_ON == FEATURE_PTM)
        if (VOS_TRUE == TAF_MMA_IsUsimServiceAvailable())
        {
            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_CS);

            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_PS);

            TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_TRUE);
            TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);
        }
#endif
    }
    /* Added by s00261364 for L-C互操作项目, 2014-1-27, end */

#if defined(__PS_WIN32_RECUR__) || defined(NAS_STUB)
    if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetUsimStatus())
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_AVAILABLE);
    }
    else
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_UNAVAILABLE);
    }
#endif


    /* 发送状态机退出消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    /* 收到rrmm-start-cnf消息后，
     当前是自动开机，
        MMA需要释放投票,由AS发送plmn_serach_req时,由OAM投反对睡眠票,
     当前是非自动开机，
        MMA需要释放投票,进入睡眠*/

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
    }

    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode
 功能描述  : MMA模块对于上电开机成功的结果处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年2月19日
   作    者   : w00167002
   修改内容   : L-C互操作项目修改，不发送搜网
 3.日    期   : 2014年08月13日
   作    者   : s00217060
   修改内容   : DTS2014073007533:开机完成后，释放投票的操作延后，否则中间C核可能睡下去
*****************************************************************************/
VOS_VOID TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode(VOS_VOID)
{
    VOS_UINT32                          ulAutoSwitchOnFlg;
    VOS_UINT8                           ucSdcSimStatus;

    ulAutoSwitchOnFlg       = TAF_MMA_GetAutoSwitchOnFlg();

    /* 非E5下的充电模式或自动上电开机NV关闭时进行关机流程 */
    if ((DRV_START_MODE_CHARGING == mdrv_sysboot_get_bootmode())
     || (VOS_FALSE == ulAutoSwitchOnFlg))
    {
        /* 上电不自动开机，NAS需要关闭RF */
        MMA_TurnOffForFlightMode();

        NAS_TRACE_HIGH("mdrv_sysboot_get_bootmode = %d, ulAutoSwitchOnFlg = %d",
                        (VOS_UINT32)mdrv_sysboot_get_bootmode(),
                        ulAutoSwitchOnFlg);

        /* 走关机流程 */
        TAF_MMA_ProcPowerOffReq_PhoneMode();

        return;
    }

    /* 更新当前的模式为FULL模式 */
    TAF_SDC_SetCurPhoneMode(TAF_PH_MODE_FULL);

    /* 硬开机流程走到这里，启动底层 */
    MMA_TurnOnForFlightMode();

    TTF_MemCcpuCheckPoolLeak();

#ifndef __PS_WIN32_RECUR__
    NAS_MMA_SndOutsideContextData();
#endif

    TAF_MMA_ReportPhoneModeInd_PhoneMode();

    ucSdcSimStatus          = (VOS_UINT8)TAF_SDC_GetSimStatus();

    if (SYSTEM_APP_WEBUI == TAF_SDC_GetAppCfgSupportType())
    {
        /* 不需要PIN码但锁卡时上报SIM LOCKED事件 */
        if (((TAF_SDC_USIM_STATUS_SIM_PIN != ucSdcSimStatus)
          && (TAF_SDC_USIM_STATUS_SIM_PUK != ucSdcSimStatus))
         && (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus))
        {
            MN_PH_SimLockedRpt();
        }
    }

    /* Added by j00174725 for V9R1 干扰控制, 2013/08/12, begin */
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_ON);
#endif
    /* Added by j00174725 for V9R1 干扰控制, 2013/08/12, end */

    /* Modified by w00167002 for L-C互操作项目, 2014-2-15, begin */
    /*读全局变量进行模式判断，如果不为C+L互操作模式，则发搜网注册请求,否则等待CMMCA触发搜网注册请求 */
    if (VOS_TRUE != TAF_MMA_IsPowerOnCLInterWork())
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == TAF_SDC_IsPlatformSupport3Gpp2())
        {
            TAF_MMA_SndMsccCFreqLockNtf(TAF_MMA_GetCFreqLockSetPara());
        }
#endif

        TAF_MMA_SndMsccSystemAcquireReq();

#if (FEATURE_ON == FEATURE_PTM)
        /* 卡有效的情况下，才给AP上报开机 */
        if (VOS_TRUE == TAF_MMA_IsUsimServiceAvailable())
        {
            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_CS);

            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_PS);

            TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_TRUE);
            TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);
        }
#endif

#if 0
        Sta_AttachByModeService(STA_OPID_ATTATCH);
#endif
    }
    /* Modified by w00167002 for L-C互操作项目, 2014-2-15, end */

#if defined(__PS_WIN32_RECUR__) || defined(NAS_STUB)
    if (TAF_SDC_USIM_STATUS_VALID == ucSdcSimStatus)
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_AVAILABLE);
    }
    else
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_UNAVAILABLE);
    }
#endif

    /* 收到rrmm-start-cnf消息后，
     当前是自动开机，
        MMA需要释放投票,由AS发送plmn_serach_req时,由OAM投反对睡眠票,
     当前是非自动开机，
        MMA需要释放投票,进入睡眠*/
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
    }

    /* 发送状态机退出消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf
 功能描述  : 收到MSCC模块的开机回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年4月16日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:修改了向at上报的失败类型
  3.日    期   : 2014年07月08日
    作    者   : y00245242
    修改内容   : 为1X feature开发修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_START_CNF_STRU            *pstStartCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstStartCnf                         = (MSCC_MMA_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Mscc Start Cnf!!!");

	NAS_NORMAL_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf: Rcv Mscc Start Cnf");

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF);

    /* MSCC模块开机成功，还存在需要下发开机消息的模块，下发开机消息 */
    if ( NAS_MSCC_PIF_START_RESULT_SUCC == pstStartCnf->ulResult )
    {

        /* 开机成功的处理 */
        ulRslt      = TAF_MMA_ProcStartComplete_PhoneMode(VOS_TRUE);
    }
    else
    {
        /* 开机失败的处理 */
        ulRslt      = TAF_MMA_ProcStartComplete_PhoneMode(VOS_FALSE);
    }

    return ulRslt;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf
 功能描述  : 等待MSCC模块的开机回复超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年07月08日
    作    者   : Y00213812
    修改内容   : 为1X feature开发修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* warning打印 */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf:time expired!");

    NAS_TRACE_HIGH("MMA Start Timeout!");

    /* 开机超时处理 */
    TAF_MMA_ProcStartExpired_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode
 功能描述  : MMA模块对于卡状态变化引起的关机回复处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode(VOS_VOID)
{
    /* 掉卡时，删除EPLMN信息 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetUsimStatus())
    {
        MMA_ClearEplmnFromNV();
        TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode:EPLMN is cleared:");
    }

    /* 初始化全局变量 */
    TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_POWEROFF, TAF_MMA_GetMmaCtxAddr());

    /* 走内部开机流程 */
    TAF_MMA_ProcStartReq_PhoneMode();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPowerOffCnfOnPowerOffMode_PhoneMode
 功能描述  : MMA模块在poweroffmode下收到关机回复的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年9月27日
   作    者   : w00167002
   修改内容   : DTS2013092100149:删除C核TASKDELAY处理，在V9低功耗时，会导致
                  TASKDELAY后未被唤醒，导致AT消息没有回复。
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPowerOffCnfWithPowerOffMode_PhoneMode(VOS_VOID)
{
    VOS_UINT16                          usAppCfgSupportType;
    VOS_UINT32                          ulRslt;

    usAppCfgSupportType     = TAF_SDC_GetAppCfgSupportType();

    if (SYSTEM_APP_WEBUI == usAppCfgSupportType)
    {
        /* 关闭射频 */
        MMA_TurnOffForFlightMode();




        /* 将TASKDELAY修改为启动定时器进行保护 */
        ulRslt = NAS_StartRelTimer(&g_stPowerDownDelayTimer.MmaHTimer,
                              WUEPS_PID_MMA,
                              TI_TAF_MMA_DELAY_POWER_DOWN_TIMER_LEN,
                              TAF_MMA,
                              TI_TAF_MMA_DELAY_POWER_DOWN,
                              VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRslt)
        {
            MMA_WARNINGLOG("Sta_PowerOffCnf():ERROR:Start TI_TAF_MMA_DELAY_POWER_DOWN Timer Error!");
            mdrv_sysboot_poweroff();
        }



        return;
    }

    if (SYSTEM_APP_ANDROID   == usAppCfgSupportType)
    {
        /* 去激活USIM卡 */
        (VOS_VOID)NAS_USIMMAPI_DeactiveCardReq(WUEPS_PID_MMA);

        /* 关闭射频 */
        MMA_TurnOffForFlightMode();

        /* 在上报事件前先调用COMM接口Flush NV */
#if (FEATURE_ON == FEATURE_LTE)
        (VOS_VOID)NVM_Flush();
#endif
        (VOS_VOID)NV_Flush();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPowerOffCnfOnPowerOffMode_PhoneMode
 功能描述  : MMA根据指定的手机模式对关机回复的处理
 输入参数  : ucPhoneMode--手机模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPowerOffCnfWithSpecPhoneMode_PhoneMode(
    VOS_UINT8                           ucPhoneMode
)
{
    switch (ucPhoneMode)
    {
        case TAF_PH_MODE_POWEROFF:

            TAF_MMA_ProcPowerOffCnfWithPowerOffMode_PhoneMode();
            break;

        case TAF_PH_MODE_MINI:

            MMA_TurnOffForFlightMode();

#if (FEATURE_ON == FEATURE_LTE)
            (VOS_VOID)NVM_Flush();
#endif
            (VOS_VOID)NV_Flush();

            /* 若"AT+CFUN=0命令软关机，去激活(U)SIM卡功能"的特性使能，则去激活SIM卡 */
            if (MMA_DEACT_SIM_WHEN_POWEROFF_ENABLE == g_ucMmaDeactSimWhenPoweroff)
            {
                (VOS_VOID)NAS_USIMMAPI_DeactiveCardReq(WUEPS_PID_MMA);
            }

            break;

        case TAF_PH_MODE_RFOFF:
        case TAF_PH_MODE_LOWPOWER:
        case TAF_PH_MODE_VDFMINI:

            MMA_TurnOffForFlightMode();
            break;

        default:

            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPowerOffCnfWithSpecPhoneMode_PhoneMode:No need to deal with this mode!");
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_WaitMsccPowerOffCnf
 功能描述  : 收到MSCC模块的关机回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年11月22日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 3.日    期   : 2014年04月15日
   作    者   : s00217060
   修改内容   : 关机时增加投票
 4.日    期   : 2014年07月08日
   作    者   : y00245242
   修改内容   : 为1X feature开发修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_WaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;

    NAS_TRACE_HIGH("Rcv Mscc Power Off Cnf!!!");


    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF);

    /* 关机完成的处理 */
    ulRslt = TAF_MMA_ProcPowerOffComplete_PhoneMode();

    return ulRslt;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf
 功能描述  : 等待MMC的关机回复超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年04月15日
    作    者   : s00217060
    修改内容   : 关机时增加投票
  3.日    期   : 2014年07月08日
    作    者   : y00245242
    修改内容   : 为1X feature开发修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* warning打印 */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf:time expired!");

    NAS_TRACE_HIGH("MMA PowerOff Timeout!!!");


    /* 关机超时的处理 */
    TAF_MMA_ProcPowerOffExpired_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPowerOffReq_PhoneMode
 功能描述  : MMA模块处理关机请求
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月13日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月28日
   作    者   : s00217060
   修改内容   : DTS2014011709107:清除开机到注册成功时间
 3.日    期   : 2014年04月15日
   作    者   : s00217060
   修改内容   : 关机时增加投票
 4.日    期   : 2014年07月08日
   作    者   : y00245242
   修改内容   : 为1X feature项目开发
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPowerOffReq_PhoneMode(VOS_VOID)
{
    VOS_UINT32                          ulModuleId;

    ulModuleId = 0;

    /* Added by s00217060 for 关机投票, 2014/04/15, begin */
    /* 增加投票:关机时不允许睡眠,收到MSCC的关机回复之后解除 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
    /* Added by s00217060 for 关机投票, 2014/04/15, end */

    /* 设置STOP状态标志量*/
    g_StatusContext.ulFsmState = STA_FSM_STOP;

    /* 清除开机到注册成功时间 */
    g_stRegTimeInfo.ulCostTime      = 0;

    /* 获取第一个关机请求消息的模块,不存在ulModuleId为无效值的情况 */
    /* 下发关机请求 */
    TAF_MMA_SndPowerOffReq_PhoneMode(ulModuleId);


    /* 如果TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU定时器正在运行，需要停止 */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodNetSelMenuStatus())
    {
       if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA,
                                      TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU,
                                      &(g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.MmaHTimer)))
       {
           TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPowerOffReq_PhoneMode:stop TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU failed!");
       }

       TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(MMA_TIMER_STOP);
    }

    /* 如果TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器正在运行，需要停止 */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodRatBalancingStatus())
    {
       TAF_MMA_StopTimer(TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING);

       TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_STOP);
    }

    TAF_MMA_StopTimer(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    TAF_MMA_StopTimer(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStartReq_PhoneMode
 功能描述  : MMA模块处理开机请求
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月13日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年12月26日
   作    者   : w00242748
   修改内容   : DTS2013120306986:刚开机时，当NV 8229和NV 10000设置不一致时，
                WAS读取NV 8229 RRC Connection Setup Complete给网侧上报当前UE
                支持频段时存在问题。
 3.日    期   : 2014年07月08日
   作    者   : y00245242
   修改内容   : 为1X feature开发修改
*****************************************************************************/
VOS_VOID TAF_MMA_ProcStartReq_PhoneMode(VOS_VOID)
{
    TAF_CS_SERVICE_ENUM_UINT32          enCsServCapa;

    /* 设置RESTART状态标志量 */
    g_StatusContext.ulFsmState = STA_FSM_RESTART;

    if (MMA_MMA_INTER_POWER_INIT != TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        /* 打开RF电源 */
        MMA_TurnOnForFlightMode();
    }

    TAF_MMA_UpdateUeBandNvim();

#if (FEATURE_ON == FEATURE_LTE)
    TAF_MMA_UpdateUserSetLteBands();
#endif


    /* 记录输入参数值 */
    g_StatusContext.ucModeService = gstMmaValue.stSetMsClass.MsClassType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsSysCfgRatSupportHrpdAndLte())
    {
        if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO != TAF_MMA_GetPlmnSelectionMode())
        {
            /* set PLMN selection mode auto in global variable  */
            TAF_MMA_SetPlmnSelectionMode((VOS_UINT8)NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

            /* write PLMN selection mode auto in NV */
            TAF_MMA_WritePlmnSelectionModeNvim((VOS_UINT8)NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);
        }
    }
#endif

    /* 获取第一个开机请求消息的模块,不存在ulModulePid为无效值的情况 */
    /* 下发开机请求 */
    TAF_MMA_SndStartReq_PhoneMode();


    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* 获取CS域能力 */
        if (VOS_TRUE == TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
        {
            enCsServCapa = TAF_CS_ON;
        }
        else
        {
            enCsServCapa = TAF_CS_OFF;
        }

        TAF_MMA_SndStkCsServiceChangeNotify(enCsServCapa);
        TAF_MMA_SndMsgCsServiceChangeNotify(enCsServCapa);
    }

    MN_PH_UpdateBeginRegTime();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode
 功能描述  : 获取当前状态机入口消息ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回入口消息ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月17日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulMsgId         = TAF_MMA_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType);

    return ulMsgId;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmEntryMsgOpId_PhoneMode
 功能描述  : 获取当前状态机入口消息的OP ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回入口消息的OP ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月17日
    作    者   : w00176964
    修改内容   : 新生成函数
 2.日    期   : 2014年2月14日
   作    者   : w00167002
   修改内容   : L-C互操作项目:开关机函数调整

*****************************************************************************/
VOS_UINT8  TAF_MMA_GetCurrFsmEntryMsgOpId_PhoneMode(VOS_VOID)
{
    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg           = VOS_NULL_PTR;
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg         = TAF_MMA_GetCurrFsmMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    ulEventType         = pstEntryMsg->ulEventType;

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_POWER_INIT)== ulEventType)
    {
        return STA_OPID_INSIDE;
    }

    if ((TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND) == ulEventType)
     || (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND)   == ulEventType))
    {
        return MMA_OP_ID_INTERNAL;
    }

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ) == ulEventType )
    {
        return pstPhoneModeSetReq->stCtrl.ucOpId;
    }

    return pstAppMsg->opId;

    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmEntryMsgPhoneMode_PhoneMode
 功能描述  : 获取当前状态机入口消息中设置的手机模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回入口消息设置的手机模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月17日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月14日
    作    者   : w00167002
    修改内容   : L-C互操作项目:开关机函数调整
*****************************************************************************/
VOS_UINT8  TAF_MMA_GetCurrFsmEntryMsgPhoneMode_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;

    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */

    /* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSet = VOS_NULL_PTR;
    /* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

    VOS_UINT32                          ulEventType;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();
    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    /* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
    pstPhoneModeSet = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

    ulEventType = pstEntryMsg->ulEventType;

    /* Modified by w00167002 for L-C互操作项目, 2014-2-19, begin */
    if ((TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ) == ulEventType)
      || (TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ) == ulEventType))
    {
        pstPhModeSet = (TAF_PH_OP_MODE_STRU*)pstAppMsg->aucContent;

        return pstPhModeSet->PhMode;
    }

    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */

    /* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */

    /* 关机可能是TAF发送的，也可能时CMMCA发送的 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ) == ulEventType)
    {
        return pstPhoneModeSet->stPhoneModePara.PhMode;
    }
    /* Added by w00167002 for L-C互操作项目, 2014-2-14, end */
    return TAF_SDC_GetCurPhoneMode();
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmEntryMsgClientId_PhoneMode
 功能描述  : 获取当前状态机入口消息的Client ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回入口消息的client ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月17日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月14日
    作    者   : w00167002
    修改内容   : L-C互操作项目:开关机函数调整
*****************************************************************************/
VOS_UINT16  TAF_MMA_GetCurrFsmEntryMsgClientId_PhoneMode(VOS_VOID)
{
    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg           = VOS_NULL_PTR;
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg         = TAF_MMA_GetCurrFsmMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    ulEventType = pstEntryMsg->ulEventType;

    if ((TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_POWER_INIT)             == ulEventType)
     || (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND) == ulEventType)
     || (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND)   == ulEventType))
    {
        return MMA_CLIENTID_NONE;
    }

    /* CMMCA或者AT触发的模式设置 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ) == ulEventType )
    {
        return pstPhoneModeSetReq->stCtrl.usClientId;
    }

    return pstAppMsg->clientId;

    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReportPhoneModeCnf_PhoneMode
 功能描述  : 上报模式设置结果给AT或OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2014年2月14日
   作    者   : w00167002
   修改内容   : L-C互操作项目:开关机函数调整
 3.日    期   : 2014年07月07日
   作    者   : z00234330
   修改内容   : coverity清理
*****************************************************************************/
VOS_VOID TAF_MMA_ReportPhoneModeCnf_PhoneMode(VOS_VOID)
{
    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucOpId;
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;
    VOS_UINT16                          usClientId;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));
    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulEventType = pstEntryMsg->ulEventType;
    ucOpId      = TAF_MMA_GetCurrFsmEntryMsgOpId_PhoneMode();
    usClientId  = TAF_MMA_GetCurrFsmEntryMsgClientId_PhoneMode();
    enErrorCode = TAF_MMA_GetCurPhoneErrorCode_PhoneMode();

    /* 只需要OM或AT或CMMCA触发的开机或关机进行模式设置结果上报 */
    if ( (TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ)      == ulEventType)
      || (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ)  == ulEventType)
      || (TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ)      == ulEventType))
    {
        stPhMode.CmdType = TAF_PH_CMD_SET;
        stPhMode.PhMode = TAF_SDC_GetCurPhoneMode();

        MMA_PhModeReport(usClientId, ucOpId, stPhMode, enErrorCode);

        return;
    }

    /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtPsInitRsltInd
 功能描述  : 向AT上报协议栈初始化结果指示(PSINIT)
 输入参数  : ucSimStatus---SIM卡状态
             ucSimLockStatus--SIM卡锁卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月18日
   作    者   : w00176964
   修改内容   : 新生成函数
2.日    期   : 2013年4月16日
  作    者   : y00176023
  修改内容   : DSDS GUNAS II项目:修改了向at上报的失败类型
*****************************************************************************/

VOS_VOID TAF_MMA_SndAtPsInitRsltInd_PhoneMode(
    TAF_MMA_PS_INIT_RSLT_ENUM_UINT32    enPsInitRslt
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAtPsInitRsltInd:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* 初始化电话上报事件 */
    MMA_InitEventInfoOP(pstPhoneEvent);

    pstPhoneEvent->OP_PsInitRslt          = VOS_TRUE;
    pstPhoneEvent->PhoneEvent             = TAF_MMA_EVT_PS_INIT_RESULT_IND;

    /* 填写事件客户端类型为广播事件 */
    pstPhoneEvent->ClientId               = MMA_CLIENTID_BROADCAST;
    pstPhoneEvent->OpId                   = MMA_OP_ID_INTERNAL;

    pstPhoneEvent->ulPsInitRslt           = enPsInitRslt;

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReportPhoneModeInd_PhoneMode
 功能描述  : 广播上报模式设置结果指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年8月5日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReportPhoneModeInd_PhoneMode(VOS_VOID)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent           = VOS_NULL_PTR;

    /* 广播上报当前的系统模式 */
    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReportPhoneModeInd_PhoneMode:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pstPhoneEvent->OpId = MMA_OP_ID_INTERNAL;
    pstPhoneEvent->ClientId = MMA_CLIENTID_BROADCAST;
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_IND;
    pstPhoneEvent->PhoneError = TAF_ERR_NO_ERROR;
    pstPhoneEvent->OP_OperMode = VOS_TRUE;
    pstPhoneEvent->OperMode.CmdType = TAF_PH_CMD_SET;
    pstPhoneEvent->OperMode.PhMode = TAF_SDC_GetCurPhoneMode();

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));
    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetMsccPowerOffCause_PhoneMode
 功能描述  : 通过状态机入口消息获取关机原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : Y00213812
    修改内容   : CDMA 1X Iteration 0 新增函数
*****************************************************************************/
NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 TAF_MMA_GetMsccPowerOffCause_PhoneMode(VOS_VOID)
{
    VOS_UINT32                          ulEntryMsgId;

    ulEntryMsgId = TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode();

    /* 通过状态机入口消息获取关机原因值 */
    if ((MMA_MMA_INTER_USIM_STATUS_CHANGE_IND == ulEntryMsgId)
     || (MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND   == ulEntryMsgId))
    {
        return NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE;
    }

    return NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStartExpired_PhoneMode
 功能描述  : 开机超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : Y00213812
    修改内容   : CDMA 1X Iteration 0 新增函数

  2.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID TAF_MMA_ProcStartExpired_PhoneMode(VOS_VOID)
{
    if (MMA_MMA_INTER_POWER_INIT == TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        /* 上报当前的RAT模式 */
        TAF_MMA_SndRatModInd_PhoneMode();

        /* 上报协议栈初始化失败 */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_FAIL);
    }

    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    TAF_MMA_SndUphyPowerOffReq();

    /* 上报APP当前状态事件 */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStartExpired_PhoneMode
 功能描述  : 关机超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : Y00213812
    修改内容   : CDMA 1X Iteration 0 新增函数

  2.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPowerOffExpired_PhoneMode(VOS_VOID)
{
    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    TAF_MMA_SndUphyPowerOffReq();

    /* 上报APP当前状态事件 */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_FAIL);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    /* 关机超时之后允许睡下去 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStartComplete_PhoneMode
 功能描述  : 开机完成后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : Y00213812
    修改内容   : CDMA 1X Iteration 0 新增函数
  2.日    期   : 2014年08月13日
    作    者   : s00217060
    修改内容   : DTS2014073007533:开机完成后，释放投票的操作延后，否则中间C核可能睡下去
  3.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : TSTS
  4.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcStartComplete_PhoneMode(
    VOS_UINT32                          ulRslt
)
{
    VOS_UINT8                           ucSimStatus;
    VOS_UINT8                           ucSimLockStatus;
    TAF_MMA_PS_INIT_RSLT_ENUM_UINT32    enPsInitRslt;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        ucSimStatus     = MMA_GetCsimStatus(VOS_FALSE);

        /* 获取锁卡状态 */
        if (MMA_SIM_IS_LOCK == MMA_GetCsimMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }
    else
#endif
    {
        ucSimStatus = MMA_GetUsimStatus(VOS_FALSE);

        /* 获取锁卡状态 */
        if (MMA_SIM_IS_LOCK == MMA_GetMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }

    /* 开机结束之后允许睡眠投票放在每个return分支的最后，以免中间调用底软接口对信号量操作时C核进入睡眠 */

    /* 上电开机时上报AT当前协议栈的初始化结果 */
    if (MMA_MMA_INTER_POWER_INIT == TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        if (VOS_TRUE == ulRslt)
        {
            enPsInitRslt = TAF_MMA_PS_INIT_SUCC;
        }
        else
        {
            enPsInitRslt = TAF_MMA_PS_INIT_FAIL;
        }

        /* 上报当前的RAT模式 */
        TAF_MMA_SndRatModInd_PhoneMode();

        NAS_TRACE_HIGH("enPsInitRslt=%d", enPsInitRslt);

        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(enPsInitRslt);

        /* 适配RIL逻辑,补充上报一次卡状态 */
        TAF_MMA_SndAtIccStatusInd(ucSimStatus, ucSimLockStatus);

        TAF_MMA_SetDplmnUpdateScene(TAF_MMA_AP_PRESET_DPLMN_SCENE_SWITCH_ON);
    }



    /* 开机失败 */
    if (VOS_FALSE == ulRslt)
    {
        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_UNSPECIFIED_ERROR);

        TAF_MMA_SndUphyPowerOffReq();

        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* 发送状态机退出消息 */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

        /* 收到rrmm-start-cnf消息后，
         当前是自动开机，
            MMA需要释放投票,由AS发送plmn_serach_req时,由OAM投反对睡眠票,
         当前是非自动开机，
            MMA需要释放投票,进入睡眠*/

        if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
        {
            (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartComplete_PhoneMode:result = %d\n", ulRslt);
            (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartComplete_PhoneMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
        }

        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);


        return VOS_TRUE;
    }

    /* 开机成功应该先设置此状态,因为后续的attach等动作会判断此状态 */
    g_StatusContext.ulFsmState          = STA_FSM_ENABLE;

    /* 更新SDC中的SIM卡的注册状态 */
    TAF_MMA_UpdateSimRegStatus();

    /* MMA通知TAF层开机 */
    TAF_MMA_SndPowerOnIndMsg();

    /* 通过状态机入口消息判断是否为上电开机 */
    if (MMA_MMA_INTER_POWER_INIT != TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode();

        return VOS_TRUE;
    }

    /* 上电开机成功的结果处理 */
    TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPowerOffComplete_PhoneMode
 功能描述  : 关机完成后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : Y00213812
    修改内容   : CDMA 1X Iteration 0 新增函数

  2.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcPowerOffComplete_PhoneMode(VOS_VOID)
{
    VOS_UINT8                           ucPhoneMode;
    VOS_UINT32                          ulEntryMsgId;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU    stSndMtcPlmnInfo;
#endif

    MMA_InitCm();


    /* 开机会通知MSG一次CS域能力，关机时不需要再通知MSG；STK要求关机时也通知一次 */
    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        TAF_MMA_SndStkCsServiceChangeNotify(TAF_CS_OFF);
    }

    /* 上报服务状态变化 */
    if (TAF_SDC_REPORT_SRVSTA_NO_SERVICE != TAF_SDC_GetServiceStatus())
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);
        TAF_MMA_ReportSrvStatus();
    }

    if (VOS_TRUE == TAF_SDC_IsPlatformSupport3Gpp())
    {
        /* 上报系统模式子模式变化 */
        Sta_ModeChangeEventReport(TAF_PH_INFO_NONE_RAT, TAF_SYS_SUBMODE_NONE);

        TAF_MMA_SndUphyPowerOffReq();

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
        TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_OFF);

        if (VOS_TRUE == TAF_SDC_GetUtranSkipWPlmnSearchFlag())
        {
            PS_MEM_SET(&stSndMtcPlmnInfo, 0, sizeof(stSndMtcPlmnInfo));

            stSndMtcPlmnInfo.enRatMode             = MTC_RATMODE_BUTT;
            stSndMtcPlmnInfo.ucIsForbiddenPlmnFlag = VOS_FALSE;
            stSndMtcPlmnInfo.ucPsAttachAllowFlag   = TAF_SDC_GetPsAttachAllowFlg();
            stSndMtcPlmnInfo.stPlmnId.ulMcc        = TAF_SDC_INVALID_MCC;
            stSndMtcPlmnInfo.stPlmnId.ulMnc        = TAF_SDC_INVALID_MCC;
            TAF_MMA_SndMtcCurrCampPlmnInfoInd(&stSndMtcPlmnInfo);
        }
#endif
    }

    ulEntryMsgId = TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode();

    /* 通过入口消息判断是卡状态改变引起的关机 */
    if ((MMA_MMA_INTER_USIM_STATUS_CHANGE_IND == ulEntryMsgId)
     || (MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND   == ulEntryMsgId))
    {
        TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode();

        /* 前面已经在发内部开机流程，该处的投票睡眠不需要 */

        return VOS_TRUE;
    }

    /* 获取OM或AT设置的模式 */
    ucPhoneMode             = TAF_MMA_GetCurrFsmEntryMsgPhoneMode_PhoneMode();

    /* 更新当前的手机模式 */
    TAF_SDC_SetCurPhoneMode(ucPhoneMode);

    TAF_MMA_ProcPowerOffCnfWithSpecPhoneMode_PhoneMode(ucPhoneMode);

    /* 向APP上报应答事件*/
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_SUCC);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    /* 增加投票:收到关机回复之后允许睡下去 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_ProcGetGeoNoSimStartReq_PhoneMode
 功能描述  : MMA模块处理获取国家码的无卡开机请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : CL_MUTIMODE_OPTIMIZE修改，增加TAF_MMA_UpdateRatPrio调用
*****************************************************************************/
VOS_VOID TAF_MMA_ProcGetGeoNoSimStartReq_PhoneMode(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU              stSndRatPrioList;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    g_StatusContext.ulFsmState = STA_FSM_RESTART;

    NAS_TRACE_HIGH("MMA Get Geo No Sim Start Begin!!!");

    /* 获取接入技术信息 */
    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();

    PS_MEM_SET(&stSndRatPrioList, 0, sizeof(TAF_MMA_RAT_ORDER_STRU));

    stSndRatPrioList.ucRatOrderNum = pstRatPrioList->ucRatOrderNum;
    PS_MEM_CPY(stSndRatPrioList.aenRatOrder,
               pstRatPrioList->aenRatOrder,
               pstRatPrioList->ucRatOrderNum);

    /* 此处如果接入技术是1x+HRPD+LTE,则改为G+W+L。GUL的搜网依赖于StartReq消息中的接入技术。
       GUL的初搜，因为G网的覆盖更广，搜网顺序为G-U-L，如果当前接入技术是1x+HRPD+LTE，则MMC模块只会发起LTE的搜网，
       初搜成功率更低，改为G+W+L后，MMC发起GUL的初搜，同时和CAS确认，不影响X模的初搜
     */
    TAF_MMA_UpdateRatPrioFromClToGul(&stSndRatPrioList);

    TAF_MMA_GetAvailablePlmnRatPrio(&stSndRatPrioList);


    /* 发送开机请求给MSCC */
    (VOS_VOID)TAF_MMA_SndMsccStartReq(&stSndRatPrioList,
                            NAS_MSCC_PIF_CARD_STATUS_ABSENT,
                            NAS_MSCC_PIF_CARD_STATUS_ABSENT,
                            VOS_FALSE);

    /* 迁移状态到等待MSCC获取国家码的开机回复 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_START_CNF);

    /* 启动保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF, TI_TAF_MMA_WAIT_MSCC_START_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode
 功能描述  : MMA模块处理获取国家码的无卡关机请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode(VOS_VOID)
{
    /* 增加投票:关机时不允许睡眠,收到MSCC的关机回复之后解除 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

    NAS_TRACE_HIGH("MMA Get Geo No Sim PowerOff Begin!!!");

    /* 设置STOP状态标志量*/
    g_StatusContext.ulFsmState = STA_FSM_STOP;

    TAF_MMA_SndMsccPowerOffReq(NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL);

    /* 迁移状态到等待MSCC获取国家码的关机回复 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_POWER_OFF_CNF);

    /* 启动保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF, TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcStopGetGeoReq_PhoneMode
 功能描述  : MMA模块处理停止获取国家码的请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcStopGetGeoReq_PhoneMode(VOS_VOID)
{
    NAS_TRACE_HIGH("MMA Stop Get Geo Begin!!!");

    /* 发送停止获取国家码的请求给MSCC */
    TAF_MMA_SndMsccStopGetGeoReq();

    /* 迁移状态到等待MSCC获取国家码的开机回复 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_STOP_GET_GEO_CNF);

    /* 启动保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF, TAF_MMA_WAIT_STOP_GET_GEO_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccGetGeoCnf
 功能描述  : 等待MSCC模块的获取地理信息回复的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
 1.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : CL_MUTIMODE_OPTIMIZE 修改，增加cdma的位置信息处理
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_GET_GEO_CNF_STRU      *pstGetGeoCnf = VOS_NULL_PTR;
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCnf = (NAS_MSCC_PIF_GET_GEO_CNF_STRU *)pstMsg;

    NAS_TRACE_HIGH("Rcv Mscc Get Geo Cnf!!!");

    /* 停止定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF);

    /* 保存PLMN信息,更新时间戳 */
    /* 更新GUL初搜获取的位置信息 */
    TAF_MMA_UpdateGeoPlmnIdInfo((TAF_SDC_PLMN_ID_STRU *)(&(pstGetGeoCnf->stPlmnId)));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 更新X模出搜获取的位置信息 */
    TAF_MMA_UpdateGeoCdmaLocInfo(pstGetGeoCnf->lSid, pstGetGeoCnf->lNid);
#endif
    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();

    /* 上报AT命令INITLOCINFO，从GetGeoCtx中获取，如果get geo NV关闭，上报无效值 */
    TAF_MMA_SndAtInitLocInfoInd(pstGetGeoCtx->stGeoPlmnId.ulMcc, pstGetGeoCtx->stGeoCdmaLocInfo.lSid);

    /* 卡状态已经上报，则关机，卡状态没上报也不退出状态机，继续等待卡状态上报 */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {
        TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

        return VOS_TRUE;
    }

    /* 如果卡状态还没有上报，则将状态迁移到获取国家码完成等待卡状态上报的状态
       当前等卡状态上报的定时器还在运行中 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_GET_GEO_CMP_WAIT_USIM_STATUS_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitMsccGetGeoCnfExpired_PhoneMode_WaitMsccGetGeoCnf
 功能描述  : 等待MSCC模块的获取地理信息超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccGetGeoCnfExpired_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo Timeout!!!");

    /* 卡状态已经上报，则打断当前的获取国家码的流程 */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {
        TAF_MMA_ProcStopGetGeoReq_PhoneMode();

        return VOS_TRUE;
    }

    /* 卡状态还没有上报，不退出状态机，继续等待卡状态上报 */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccGetGeoCnf
 功能描述  : 等待MSCC模块的获取地理信息过程中收到卡状态上报
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA In Get Geo Status, Rcv PIH Usim Status Ind!!!");

    /* 停止等待卡状态上报定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

    /* 地理位置信息还未获取完毕，获取国家码的定时器如果不在运行，那么肯定是获取国家码的定时器超时停止的.
       则收到卡状态上报后，获取国家码的定时器已经超时，需要打断获取国家码流程 */
    if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF))
    {
        TAF_MMA_ProcStopGetGeoReq_PhoneMode();

        return VOS_TRUE;
    }

    /* 没有收到获取国家码的结果回复，则继续等待获取国家码的结果 */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitMsccGetGeoCnf
 功能描述  : 收到等待PIH模块上报的卡状态指示消息超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* NOTE: 该定时器超时肯定是等卡状态上报定时器超时，
             因为物理层初始化成功后才有GetGeo的流程 */

    NAS_TRACE_HIGH("MMA In Get Geo Status, PIH Usim Status Ind Timeout!!!");

    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);

    /* 如果TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF在运行就停止 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF);

    /* 获取国家码流程还未结束，需要打断处理 */
    TAF_MMA_ProcStopGetGeoReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoCmpWaitUsimStatusInd
 功能描述  : 在获取国家码完成后等待卡状态上报过程中收到卡状态上报
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoCmpWaitUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA In Get Geo Cmp Status, Rcv PIH Usim Status Ind!!!");

    /* 停止等待卡状态上报定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

    /* 收到卡状态上报后，则进行无卡关机 */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoCmpWaitUsimStatusInd
 功能描述  : 在获取国家码完成后等待卡状态上报过程中收到卡状态上报超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoCmpWaitUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA In Get Geo Cmp Status, PIH Usim Status Ind Timeout!!!");

    /* NOTE: 该定时器超时肯定是等卡状态上报定时器超时，
             因为物理层初始化成功后才有GetGeo的流程 */
    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);

    /* 卡上报超时后进行无卡关机 */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccStopGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf
 功能描述  : 收到MSCC模块的停止获取国家码的回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccStopGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Stop Get Geo Success!!!");

    /* 停止定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF);

    /* 停止完获取国家码的流程后，进行无卡关机 */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf
 功能描述  : 收到MSCC模块获取国家码的回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : CL_MUTIMODE_OPTIMIZE 增加Cdma位置信息处理
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_GET_GEO_CNF_STRU      *pstGetGeoCnf = VOS_NULL_PTR;
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCnf = (NAS_MSCC_PIF_GET_GEO_CNF_STRU *)pstMsg;

    /* 停止定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF);

    /* 保存PLMN信息,更新时间戳 */
    /* 更新GUL初搜获取的位置信息 */
    TAF_MMA_UpdateGeoPlmnIdInfo((TAF_SDC_PLMN_ID_STRU *)(&(pstGetGeoCnf->stPlmnId)));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 更新X模出搜获取的位置信息 */
    TAF_MMA_UpdateGeoCdmaLocInfo(pstGetGeoCnf->lSid, pstGetGeoCnf->lNid);
#endif

    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();

    /* 上报AT命令INITLOCINFO，从GetGeoCtx中获取，如果get geo NV关闭，上报无效值 */
    TAF_MMA_SndAtInitLocInfoInd(pstGetGeoCtx->stGeoPlmnId.ulMcc, pstGetGeoCtx->stGeoCdmaLocInfo.lSid);

    NAS_TRACE_HIGH("MMA In Stop Get Geo Status, Rcv Get Geo Cnf!!!");

    /* 无卡关机处理 */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeo_WaitMsccStopGetGeoCnf
 功能描述  : 新生成函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv PIH Usim Status Ind!!!");

    /* TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT定时器已经停止，本函数待后续扩展使用 */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitMsccStopGetGeoCnfExpired_PhoneMode_WaitMsccStopGetGeoCnf
 功能描述  : 收到MSCC模块的停止获取国家码超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccStopGetGeoCnfExpired_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Stop Get Geo Timeout!!!");

    /* 停止完获取国家码的流程超时，也进行无卡关机 */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccStartCnf_PhoneMode_GetGeoWaitMsccStartCnf
 功能描述  : 收到MSCC模块的开机回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccStartCnf_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_START_CNF_STRU            *pstStartCnf = VOS_NULL_PTR;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    pstStartCnf                         = (MSCC_MMA_START_CNF_STRU*)pstMsg;
    enSimStatus                         = TAF_SDC_GetUsimStatus();

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF);

    /* 获取国家码的无卡开机成功不需要上报PSINIT，
       开始获取国家码，状态迁移，并起等待定时器 */
    if (NAS_MSCC_PIF_START_RESULT_SUCC == pstStartCnf->ulResult)
    {
        NAS_TRACE_HIGH("MMA Get Geo No Sim Start Success!!!");

        /* 如果卡上报超时，则不获取国家码 */
        if (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSimStatus)
        {
            TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();
        }
        else
        {
            /* 发送获取地理位置信息请求给MSCC */
            TAF_MMA_SndMsccGetGeoReq();

            /* 迁移状态到等待MSCC的获取地理位置信息的回复 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_GET_GEO_CNF);

            /* 启动保护定时器 */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF, TAF_MMA_GetGeoTimerLen());
        }
    }
    else
    {
        /* 上报当前的RAT模式 */
        TAF_MMA_SndRatModInd_PhoneMode();

        /* 上报PSINIT */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_FAIL);

        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_UNSPECIFIED_ERROR);

        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* 发送状态机退出消息 */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

        NAS_TRACE_HIGH("MMA Get Geo No Sim Start Fail!!!");

        /* 收到rrmm-start-cnf消息后，
         当前是自动开机，
            MMA需要释放投票,由AS发送plmn_serach_req时,由OAM投反对睡眠票,
         当前是非自动开机，
            MMA需要释放投票,进入睡眠*/

        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccStartCnf
 功能描述  : 新生成函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv PIH Usim Status Ind!!!");

    /* 停止等待卡状态上报定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_GetGeoWaitMsccStartCnf
 功能描述  : 等待MSCC模块的开机回复超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo No Sim Start Timeout!!!");

    /* 上报当前的RAT模式 */
    TAF_MMA_SndRatModInd_PhoneMode();

    /* 上报协议栈初始化失败 */
    TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_FAIL);

    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    /* 上报APP当前状态事件 */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoWaitMsccStartCnf
 功能描述  : 等待PIH模块上报的卡状态指示消息超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo Start Timeout!!!");

    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_GetGeoWaitMsccPowerOffCnf
 功能描述  : 收到MSCC模块的关机回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo No Sim PowerOff Success!!!");

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF);

    /* 走内部开机流程 */
    TAF_MMA_ProcStartReq_PhoneMode();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccPowerOffCnf
 功能描述  : 新生成函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv PIH Usim Status Ind!!!");

    /* 定时器TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT已经停止，本函数留作后续扩展 */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_GetGeoWaitMsccPowerOffCnf
 功能描述  : 收到MSCC模块的关机回复处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月25日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo No Sim PowerOff Timeout!!!");

    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    /* 上报APP当前状态事件 */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_FAIL);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    /* 关机超时之后允许睡下去 */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndRatModInd_PhoneMode
 功能描述  : 上报接入模式
 输入参数  :

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月3日
   作    者   : f00279542
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndRatModInd_PhoneMode(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 上报当前的是否是CL模式 */
    TAF_MMA_SndCLModeInd();
#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    /* 上报MTC RatCfg */
    TAF_MMA_SndMtcRatCfgInd(TAF_MMA_GetRatPrioListAddr());
#endif
    return;
}
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



