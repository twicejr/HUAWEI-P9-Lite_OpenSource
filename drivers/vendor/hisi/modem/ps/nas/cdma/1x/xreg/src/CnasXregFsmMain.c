/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregFsmMain.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月03日
  功能描述   : 1X reg L1主状态机下收到各事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregCtx.h"
#include  "CnasXregFsmMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasXregSndXsd.h"
#include  "CnasMntn.h"
#include  "CnasXregProcess.h"
#include  "CnasXregSndInternalMsg.h"
#include  "NVIM_Interface.h"
#include  "CnasXregListProc.h"
#include  "CnasCcb.h"
#include  "CnasXregSndCas.h"
#include  "CnasXregTimer.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXregMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvStartReq_Null
 功能描述  : 在null状态收到开机请求ID_XSD_XREG_START_REQ的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月08日
   作    者   : l60609
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_ClearGlobal();

    /* 启动L2状态机 */
    CNAS_XREG_InitFsmL2(CNAS_XREG_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvSwitchOnRslt_Null
 功能描述  : 在null状态收到开机请求ID_XSD_XREG_START_REQ的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月08日
   作    者   : l60609
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvSwitchOnRslt_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接回复Start Cnf(Succ) */
    CNAS_XREG_SndXsdStartCnf(XREG_XSD_START_RESULT_SUCC);

    /* 切到开机未注册状态 */
    CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_UNREG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvStartReq_UnReg
 功能描述  : 在UnReg状态收到关机请求ID_XSD_XREG_START_REQ的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月23日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvStartReq_UnReg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 已开机，直接回复Start Cnf(Succ) */
    CNAS_XREG_SndXsdStartCnf(XREG_XSD_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvAccessInd_L1Main
 功能描述  : CAS发送的注册结果
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 甘兰
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvAccessInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_MSG_ACCESS_RSLT_IND_STRU    *pstMsgData;

    pstMsgData = (CAS_CNAS_1X_MSG_ACCESS_RSLT_IND_STRU *)pstMsg;

    /* 记录注册结果,CAS_CNAS_1X_REGISTRATION_TYPE_BUTT已经分配给Traffic Channel Registered. */
    CNAS_XREG_RecordRegRslt((CAS_CNAS_1X_REGISTRATION_TYPE_BUTT + 1) + pstMsgData->enMsgAccessInfo, VOS_OK);

    /* 注册成功 */
    if (VOS_TRUE == pstMsgData->ucAcsSuccFlag)
    {
        if ((CAS_CNAS_1X_SUCC_ACCESS_ORIG == pstMsgData->enMsgAccessInfo)
         || (CAS_CNAS_1X_SUCC_ACCESS_PAGING_RSP == pstMsgData->enMsgAccessInfo))
        {
            CNAS_XREG_GetRegStateAddr()->enRegTypeMntn = NAS_OM_CDMA_IMPLICIT_REGISTRATION;

            CNAS_XREG_SndOmRegTypeReportInd(NAS_OM_CDMA_IMPLICIT_REGISTRATION);

            CNAS_XREG_RegSuccProc();

            /* 切到已注册状态 */
            CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_REGED);

            return VOS_TRUE;
        }

        /* 将注册成功消息发送给XSD */
        if (CAS_CNAS_1X_SUCC_ACCESS_REG == pstMsgData->enMsgAccessInfo)
        {
            CNAS_XREG_SndXsdRegSuccessInd();

            return VOS_TRUE;
        }
    }

    if ((VOS_FALSE == pstMsgData->ucAcsSuccFlag)
     || (CAS_CNAS_1X_SUCC_ACCESS_OTHER_MSG == pstMsgData->enMsgAccessInfo))
    {
        CNAS_XREG_RegFailProc();
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvRegedDataInd_L1Main
 功能描述  : CAS发送的已注册DSCH数据消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 祝锂
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvRegedDataInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschData;

    pstDschData = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    if (CAS_CNAS_1X_RX_TCH_REGISTRATION_MSG != pstDschData->enDschMsgType)
    {
        return VOS_TRUE;
    }

    if (VOS_OK != CNAS_XREG_DSCHDataTrans(pstDschData))
    {
        return VOS_TRUE;
    }

    /* 切到已注册状态 */
    CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_REGED);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvRegReq_L1Main
 功能描述  : 内部消息发送
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 甘兰
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvRegReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU                *pstRegReq;
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8    enRegType;
    VOS_UINT8                                   ucPowerOffDeregFlg;
    VOS_UINT8                                   ucNoCardMode;

    pstRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)pstMsg;

    ucPowerOffDeregFlg = CNAS_XREG_GetPowerOffDeregFlg();

    /* 判断是否满足关机注册条件 */
    if (CAS_CNAS_1X_POWER_DOWN_REGISTRATION == pstRegReq->enRegType)
    {
        if ((VOS_FALSE == CNAS_XREG_PowerDownCheck())
         || (VOS_TRUE  == ucPowerOffDeregFlg))
        {
            CNAS_XREG_ProcPowerOffReq();

            return VOS_TRUE;
        }
    }
    else if (CAS_CNAS_1X_REGISTRATION_TYPE_BUTT == pstRegReq->enRegType)
    {
        /* 判断是否满足注册条件 */
        enRegType = CNAS_XREG_IdleRegCheck();

        if (CAS_CNAS_1X_REGISTRATION_TYPE_BUTT == enRegType)
        {
            return VOS_TRUE;
        }

        /* 将注册类型保存到消息内容中 */
        pstRegReq->enRegType = enRegType;
    }
    else
    {
        /* For pclint */;
    }

    ucNoCardMode = CNAS_XREG_GetNoCardMode();

    /* 有卡插入或无卡模式开启时才注册 */
    if ((CNAS_CCB_CARD_STATUS_ABSENT != CNAS_CCB_GetCsimCardStatus())
     || (VOS_TRUE == ucNoCardMode))
    {
        /* 通知接入层会话开始 */
        CNAS_XREG_SndCasBeginSessionNtf();

        /* 启动L2 REGING状态机 */
        CNAS_XREG_InitFsmL2(CNAS_XREG_FSM_REGING);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvRegCnf_L1Main
 功能描述  : 内部消息回复
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : ganlan
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvRegCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_CNF_STRU        *pstReqCnf;
    CNAS_XREG_REGSTATE_STRU            *pstRegState;
    NAS_OM_CDMA_REG_TYPE_ENUM_UINT32    enRegTypeMntn;

    pstReqCnf = (CNAS_XREG_XREG_REG_CNF_STRU*)pstMsg;

    pstRegState = CNAS_XREG_GetRegStateAddr();

    /* 通知接入层会话结束 */
    CNAS_XREG_SndCasEndSessionNtf();

    /* 保存并上报可维可测的注册类型 */
    enRegTypeMntn = CNAS_XREG_TransferRegType(pstReqCnf->enRegType);
    pstRegState->enRegTypeMntn = enRegTypeMntn;
    CNAS_XREG_SndOmRegTypeReportInd(enRegTypeMntn);

    /* 单独对NORF进行处理 */
    if (CNAS_XREG_REG_RESULT_NORF == pstReqCnf->enRegResult)
    {
        /* 保存当前的注册类型 */
        pstRegState->enCurRegType = pstReqCnf->enRegType;

        /* 注册RF资源操作 */
        CNAS_XREG_SndRrmRegisterInd(RRM_PS_TASK_TYPE_1X_REGISTER);

        /* 切到Registered状态 */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_UNREG);

        return VOS_TRUE;
    }

    /* 关机保护定时器超时 + 当前为关机注册需要单独处理 */
    if ((CAS_CNAS_1X_POWER_DOWN_REGISTRATION == pstReqCnf->enRegType)
     || (CNAS_XREG_REG_RESULT_PWROFF == pstReqCnf->enRegResult))
    {
        CNAS_XREG_ProcPowerOffReq();

        return VOS_TRUE;
    }

    /* 去注册RF资源操作 */
    CNAS_XREG_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_1X_REGISTER);

    if (CNAS_XREG_REG_RESULT_SUCCESS == pstReqCnf->enRegResult)
    {
        /* 切到Registered状态 */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_REGED);
    }
    else
    {
        /* 切到 UN REG 状态 */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_UNREG);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_WriteNvimInfo_PowerOff
 功能描述  : 开机状态下读取NV项内容.
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月05日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_WriteNvimInfo_PowerOff(VOS_VOID)
{
    VOS_UINT32                          ulLastSci;

    ulLastSci = (VOS_UINT32)CNAS_XREG_GetLastSciValue();

    if (NV_OK != NV_Write(en_NV_Item_1X_LAST_SCI, &ulLastSci, sizeof(ulLastSci)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_WriteNvimInfo_PowerOff:NV_Write Failed");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ProcPowerOffReq
 功能描述  : 关机流程处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : ganlan
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_ProcPowerOffReq(VOS_VOID)
{
    /* 关机时关闭保护定时器 */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT, 0);
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ABORTCNF_PT, 0);

    /* 去注册操作 */
    CNAS_XREG_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_1X_REGISTER);

    /* 保存NV信息 */
    CNAS_XREG_WriteNvimInfo_PowerOff();

    /* 回复POWEROFF消息 */
    CNAS_XREG_SndXsdPowerOffCnf();

    /* 清空全局变量 */
    CNAS_XREG_ClearGlobal();

    /* 切到NULL状态 */
    CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_NULL);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvPwrOffTimeOut_L1Main
 功能描述  : 关机超时定时器处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : ganlan
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvPwrOffTimeOut_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_ProcPowerOffReq();

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



