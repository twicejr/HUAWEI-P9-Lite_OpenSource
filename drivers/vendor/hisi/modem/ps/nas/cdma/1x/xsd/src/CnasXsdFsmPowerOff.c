/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmPowerOff.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD L2关机状态机事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXsdFsmPowerOff.h"
#include  "CnasXsdFsmPowerOffTbl.h"
#include  "CnasXsdProcCard.h"
#include  "CnasXsdSndXcc.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "xsd_xcc_pif.h"
#include  "xsd_xreg_pif.h"
#include  "CnasCcb.h"
#include  "NasMntn.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_POWER_OFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccPowerOffReq_PowerOff_Init
 功能描述  : POWER_OFF状态机初始化状态收到ID_MSCC_XSD_POWER_OFF_REQ消息的处理?
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : DSDS NO RF RRM去注册
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvMsccPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存入口消息 */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    /* CAS处于TCH态,需要等待CAS上报call release 指示进行驻留后做关机去注册 */
    if (CNAS_CCB_1X_CAS_TCH_STATE == CNAS_CCB_GetCasState())
    {
        CNAS_XSD_SetCampOnNeedFlg_PowerOff(VOS_TRUE);
    }

    /* 向RRM发起注册,RF可用后RRM会通知XSD */
    CNAS_XSD_DeRegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

    /* 通知XCC关机 */
    CNAS_XSD_SndXccPowerOffReq(XCC_XSD_POWER_OFF_REASON_POWER_OFF);

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF_LEN);


    return VOS_TRUE;

}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the current FSM Entry message to the FSM Context */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    CNAS_XSD_SndXccPowerOffReq(XCC_XSD_POWER_OFF_REASON_POWER_SAVE);

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXccPowerOffCnf_PowerOff_WaitXccPowerOffCnf
 功能描述  : XSD在WAIT_XCC_POWER_OFF_CNF状态下，收到XCC的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXccPowerOffCnf_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq = VOS_NULL_PTR;
    VOS_UINT8                           ucCampOnNeedFlg;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    XCC_XSD_POWER_OFF_CNF_STRU         *pstPowerOffCnf = VOS_NULL_PTR;

    /* 停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF);

    pstMsgHeader = (MSG_HEADER_STRU*)(CNAS_XSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer);

    if ((ID_MSCC_XSD_POWER_OFF_REQ == pstMsgHeader->ulMsgName)
      &&(UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        /* 此处使用NV控制(暂不添加,待后续NV目录划分清楚后添加),默认打开,关闭时按照原有流程走 */
        ucCampOnNeedFlg = CNAS_XSD_GetCampOnNeedFlg_PowerOff();
        if ((VOS_TRUE == CNAS_CCB_GetPowerOffCampOnCtrlFlg())
         && (VOS_TRUE == ucCampOnNeedFlg))
        {
            /* 如果存在缓存的呼叫释放指示,直接发送内部消息启动系统捕获状态机 */
            if (VOS_TRUE == CNAS_XSD_GetBufCallRelIndFlg_PowerOff())
            {
                pstFreq = CNAS_XSD_GetBufCallRelFreqInfo_PowerOff();

                CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, pstFreq);

                /* 这里注意需要先迁移状态;否则启动新状态机后当前状态机被压栈 */
                /* 迁移状态到等待XSD的系统捕获回复状态 */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF);

                return VOS_TRUE;
            }

            /* 迁移状态到等待CAS的SD指示CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND);

            /* 启动保护定时器TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND, TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND_LEN);
        }
        else
        {
            /* 通知XREG关机 */
            CNAS_XSD_SndXregPowerOffReq();

            /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);
        }
    }
    else if ((ID_MSCC_XSD_POWER_SAVE_REQ == pstMsgHeader->ulMsgName)
          && (UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        pstPowerOffCnf = (XCC_XSD_POWER_OFF_CNF_STRU*)pstMsg;
        if (XCC_XSD_POWER_OFF_RESULT_SUCC == pstPowerOffCnf->enRslt)
        {
            /* Send Suspend Request to CAS */
            CNAS_XSD_SndCasSuspendReq();

            /* Set Next State to Wait CAS Suspend Cnf */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SUSPEND_CNF);

            /* Start the Wait CAS Suspend Cnf protect timer */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF, TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF_LEN);
        }
        else
        {
            CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_REASON_POWER_SAVE, CNAS_XSD_POWEROFF_RSLT_FAIL);

            /* Quit the FSM */
            CNAS_XSD_QuitFsmL2();
        }
    }
    else
    {
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf
 功能描述  : 等待XCC关机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq = VOS_NULL_PTR;
    VOS_UINT8                           ucCampOnNeedFlg;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    /* 异常打印 */
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf:wait xcc power off expired");


    /* 此处使用NV控制(暂不添加,待后续NV目录划分清楚后添加),默认打开,关闭时按照原有流程走 */
    pstMsgHeader = (MSG_HEADER_STRU*)CNAS_XSD_GetCurrFsmEntryMsgAddr();

    if ((ID_MSCC_XSD_POWER_OFF_REQ == pstMsgHeader->ulMsgName)
      &&(UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        ucCampOnNeedFlg = CNAS_XSD_GetCampOnNeedFlg_PowerOff();
        if ((VOS_TRUE == CNAS_CCB_GetPowerOffCampOnCtrlFlg())
         && (VOS_TRUE == ucCampOnNeedFlg))
        {
            /* 如果存在缓存的呼叫释放指示,直接发送内部消息启动系统捕获状态机 */
            if (VOS_TRUE == CNAS_XSD_GetBufCallRelIndFlg_PowerOff())
            {
                pstFreq = CNAS_XSD_GetBufCallRelFreqInfo_PowerOff();

                CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, pstFreq);

                /* 这里注意需要先迁移状态;否则启动新状态机后当前状态机被压栈 */
                /* 迁移状态到等待XSD的系统捕获回复状态 */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF);

                return VOS_TRUE;
            }

            /* 迁移状态到等待CAS的SD指示CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND);

            /* 启动保护定时器TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND, TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND_LEN);

            return VOS_TRUE;
        }

        /* 通知XREG关机 */
        CNAS_XSD_SndXregPowerOffReq();

        /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);
    }
    else if ((ID_MSCC_XSD_POWER_SAVE_REQ == pstMsgHeader->ulMsgName)
          &&(UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        /* Send Suspend Request to CAS */
        CNAS_XSD_SndCasSuspendReq();

        /* Set Next State to Wait CAS Suspend Cnf */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SUSPEND_CNF);

        /* Start the Wait CAS Suspend Cnf protect timer */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF, TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF_LEN);
    }
    else
    {
    }


    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf
 功能描述  : XSD在WAIT_XREG_POWEROFF_CNF状态下，收到注册模块的的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF);

    /* 通知CAS关机 */
    CNAS_XSD_SndCasPowerOffReq();

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF, TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf
 功能描述  : 等待XREG模块的关机确认消息，定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  :
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf:wait xreg power off expired");

    /* 通知CAS关机 */
    CNAS_XSD_SndCasPowerOffReq();

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF, TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf
 功能描述  : XSD在WAIT_Cas_POWER_OFF_CNF状态下，收到Cas的关机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32：VOS_TRUE,VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : h00246512
    修改内容   : 新生成函数
  2. Date      : 2015-04-11
     Author    : a00295761
     Content   : Modified the send internal power off result function

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Receive Msg!");

    /* 停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF);

    /* 通知MSCC关机结果 */
    CNAS_XSD_SndMsccPowerOffCnf();

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_RSLT_SUCCESS,CNAS_XSD_POWEROFF_REASON_POWER_OFF);

    /* 关机完成，退出层二状态机*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf
 功能描述  : 等待接入层的关机确认消息时，超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
  2. Date      : 2015-04-11
     Author    : a00295761
     Content   : Modified the send internal power off result function


*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf:wait cas power off expired");

    /* 通知MSCC关机结果 */
    CNAS_XSD_SndMsccPowerOffCnf();

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_RSLT_SUCCESS,CNAS_XSD_POWEROFF_REASON_POWER_OFF);

    /* 关机完成，退出层二状态机*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitCasSysDeterminInd
 功能描述  : 等待CAS的system determin指示状态收到CAS的system determin消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  :
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitCasSysDeterminInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    /* 停止定时器 TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND);

    /* 呼叫释放 */
    if (CAS_CNAS_1X_SD_RELEASE_IND == pstSysDeterminInd->enSdReason)
    {
        /* 从determin ind消息中填充system id */
        stFreq.enBandClass = pstSysDeterminInd->stCurChannelInfo.usBandClass;
        stFreq.usChannel   = pstSysDeterminInd->stCurChannelInfo.usChannel;

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, &stFreq);

        /* 这里注意需要先迁移状态;否则启动新状态机后当前状态机被压栈 */
        /* 迁移状态到等待XSD的系统捕获回复状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF);

        return VOS_TRUE;
    }

    /* 通知XREG关机 */
    CNAS_XSD_SndXregPowerOffReq();

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd
 功能描述  : 等待CAS的system determin指示的保护定时器超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  :
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd:wait cas system determin ind expired");

    /* 通知XREG关机 */
    CNAS_XSD_SndXregPowerOffReq();

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdSystemAcquiredRsltCnf_PowerOff_WaitXsdSystemAcquireRsltCnf
 功能描述  : 等待XSD的系统捕获结果状态收到XSD的系统捕获结果的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  :
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXsdSystemAcquiredRsltCnf_PowerOff_WaitXsdSystemAcquireRsltCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER);

    /* 通知XREG关机 */
    CNAS_XSD_SndXregPowerOffReq();

    /* 迁移到 CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvInterXsdSystemAcquiredReq_PowerOff_WaitXsdSystemAcquireRsltCnf
 功能描述  : 等待XSD的系统捕获结果状态收到XSD的系统捕获请求状态机
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  :
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年01月13日
    作    者   : m00312079
    修改内容   : 只有在Call Release场景下进入状态机

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvInterXsdSystemAcquiredReq_PowerOff_WaitXsdSystemAcquireRsltCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU         *pSysAcqReq;

    pSysAcqReq = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstMsg;

    /* IDLE状态锁频会进入此函数，但是不会进CNAS_XSD_FSM_SYS_ACQ状态机，只有在Call
       Release下会进入CNAS_XSD_FSM_SYS_ACQ状态机 */
    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == pSysAcqReq->enSysAcqScene)
    {
        /* 申请射频资源 */
        CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

        CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SYS_ACQ);

        /* 停止保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                            TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXccDeregisterInd_PowerOff_WaitXccPowerOffCnf
 功能描述  : 等待XCC的关机回复状态收到XCC的关机去注册指示的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXccDeregisterInd_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_XSD_DEREGISTER_IND_STRU        *pstDeregInd = VOS_NULL_PTR;

    pstDeregInd = (XCC_XSD_DEREGISTER_IND_STRU *)pstMsg;

    if (XSD_XCC_DEREGISTER_REASON_POWEROFF == pstDeregInd->enCause)
    {
        /* 收到XCC的关机去注册指示后,XSD不需要在关机时驻留,清除标记 */
        CNAS_XSD_SetCampOnNeedFlg_PowerOff(VOS_FALSE);

        CNAS_XSD_SndXregDeregisterInd(XSD_XREG_DEREGISTER_REASON_POWEROFF);
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitXccPowerOffCnf
 功能描述  : 等待XCC的关机回复状态收到CAS的system determine ind的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 为不依赖于CAS上报呼叫终止指示和system determine的时序,此处也增加
       收到该消息的处理,可以存到上下文中
    */
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDetermin = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;

    pstSysDetermin = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    if (CAS_CNAS_1X_SD_RELEASE_IND != pstSysDetermin->enSdReason)
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetBufCallRelIndFlg_PowerOff(VOS_TRUE);

    stFreq.enBandClass = pstSysDetermin->stCurChannelInfo.usBandClass;
    stFreq.usChannel   = pstSysDetermin->stCurChannelInfo.usChannel;

    CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff(&stFreq);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvCasSuspendCnf_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Stop the Wait CAS Suspend Cnf protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF);

    /* Send Internal Power Sav CNf message */
    CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_RSLT_SUCCESS, CNAS_XSD_POWEROFF_REASON_POWER_SAVE);

    /* Quit the FSM */
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvTiWaitCasSuspendCnfExpired_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo;

    /* Construct the Soft Reboot Info */
    NAS_MEM_SET_S(&stCnasRebootInfo, sizeof(stCnasRebootInfo), 0x0, sizeof(CNAS_REBOOT_INFO_STRU));
    stCnasRebootInfo.enRebootScene = CNAS_REBOOT_SCENE_TI_XSD_WAIT_CAS_SUSPEND_CNF_EXPIRED;
    stCnasRebootInfo.ulPid         = UEPS_PID_XSD;
    stCnasRebootInfo.ulFsmId       = CNAS_XSD_GetCurrFsmId();
    stCnasRebootInfo.ulFsmState    = CNAS_XSD_GetFsmTopState();

    /* XSD performs soft reboot */
    CNAS_SoftReboot(stCnasRebootInfo);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvRpmStatusInd_PowerOff_WaitCasSuspendCnf
 功能描述  : 收到ID_RRM_PS_STATUS_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月10日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将消息缓存在缓存内存池中 */
    CNAS_XSD_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;

}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



