/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregSndXsd.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月03日
  功能描述   : 1X REG(register)发给CAS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregSndCas.h"
#include  "CnasXregProcess.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_SND_CAS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_SndCASEstReq
 功能描述  : XREG模块发送给CAS模块的EST REQ接口
 输入参数  : enRegType: 注册类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : zhuli
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndCASEstReq(CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType)
{
    CNAS_CAS_1X_EST_REQ_STRU           *pstMsg;
    VOS_UINT8                          *pucContent;

    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8             enCnas1xReturnCause;

    /*申请消息*/
    pstMsg  = (CNAS_CAS_1X_EST_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_XREG,
                        sizeof(CNAS_CAS_1X_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pucContent = (VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pucContent, 0, sizeof(CNAS_CAS_1X_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /*填写参数*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_1XCASM;
    pstMsg->enMsgId         = ID_CNAS_CAS_1X_EST_REQ;
    pstMsg->enEstType       = CAS_CNAS_1X_EST_TYPE_REGISTRATION;

    pstMsg->stRegInfo.enRegType                 = enRegType;
    pstMsg->stRegInfo.ucIsMtCallInRoamingAcc    = CNAS_CCB_GetMtCallInRoamingAccFlg();

    enCnas1xReturnCause = CNAS_CCB_Get1xReturnCause();

    pstMsg->stRegInfo.enReturnCause             = CNAS_CCB_CovertReturnCause(enCnas1xReturnCause);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndCASAbortReq
 功能描述  : XREG模块发送给CAS模块的Abort Req消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : zhuli
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndCASAbortReq(VOS_VOID)
{
    CNAS_CAS_1X_REG_ABORT_REQ_STRU          *pstMsg;

    /*申请消息*/
    pstMsg  = (CNAS_CAS_1X_REG_ABORT_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_XREG,
                    sizeof(CNAS_CAS_1X_REG_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /*填写参数*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_1XCASM;
    pstMsg->enMsgId         = ID_CNAS_CAS_1X_REG_ABORT_REQ;
    pstMsg->usOpId          = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndCASSciReq
 功能描述  : XREG模块发送给CAS模块当前的SCI值
 输入参数  : ucSciValue
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月22日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndCASSciReq(VOS_UINT8 ucSciValue)
{
    CNAS_CAS_1X_SLOT_CYCLE_INDEX_NTF_STRU                  *pstMsg;
    VOS_UINT8                                              *pucContent;

    /*申请消息*/
    pstMsg  = (CNAS_CAS_1X_SLOT_CYCLE_INDEX_NTF_STRU*)PS_ALLOC_MSG(UEPS_PID_XREG,
                    sizeof(CNAS_CAS_1X_SLOT_CYCLE_INDEX_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pucContent = (VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pucContent, 0, sizeof(CNAS_CAS_1X_SLOT_CYCLE_INDEX_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /*填写参数*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_1XCASM;
    pstMsg->enMsgId         = ID_CNAS_CAS_1X_SLOT_CYCLE_INDEX_NTF;
    pstMsg->usOpId          = 0;

    pstMsg->ucSlotCycleIndex = ucSciValue;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndRrmRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_REGISTER_IND消息
 输入参数  : enModemId          :当前的MODEM ID
             enTaskType         :注册任务类型
             enRatType          :接入模式类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月19日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    /* 定义原语类型指针 */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_XREG,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 返回失败 */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_XREG;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_1X;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_SndRrmDeRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_DEREGISTER_IND消息
 输入参数  : enModemId          :当前的MODEM ID
             enTaskType         :注册任务类型
             enRatType          :接入模式类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月19日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    /* 定义原语类型指针 */
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_XREG,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 返回失败 */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_XREG;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_1X;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndCasBeginSessionNtf
 功能描述  : XREG通知CAS开始Session通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月28日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SndCasBeginSessionNtf(VOS_VOID)
{
    CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU                     *pstBeginSessionNtf = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNtf = (CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XREG, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNtf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstBeginSessionNtf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstBeginSessionNtf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNtf->ulSenderPid      = UEPS_PID_XREG;
    pstBeginSessionNtf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNtf->ulReceiverPid    = UEPS_PID_1XCASM;
    pstBeginSessionNtf->ulLength         = ulMsgLength;
    pstBeginSessionNtf->enMsgId          = ID_CNAS_CAS_1X_SESSION_BEGIN_NTF;
    pstBeginSessionNtf->enSessionType    = CNAS_CAS_1X_SESSION_TYPE_REG;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBeginSessionNtf);

    PS_SEND_MSG(UEPS_PID_XREG, pstBeginSessionNtf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndCasEndSessionNtf
 功能描述  : XREG通知CAS结束Session通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月28日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SndCasEndSessionNtf(VOS_VOID)
{
    CNAS_CAS_1X_SESSION_END_NTF_STRU                       *pstEndSessionNtf = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_1X_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNtf = (CNAS_CAS_1X_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XREG, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNtf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstEndSessionNtf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstEndSessionNtf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNtf->ulSenderPid      = UEPS_PID_XREG;
    pstEndSessionNtf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNtf->ulReceiverPid    = UEPS_PID_1XCASM;
    pstEndSessionNtf->ulLength         = ulMsgLength;
    pstEndSessionNtf->enMsgId          = ID_CNAS_CAS_1X_SESSION_END_NTF;
    pstEndSessionNtf->enSessionType    = CNAS_CAS_1X_SESSION_TYPE_REG;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEndSessionNtf);

    PS_SEND_MSG(UEPS_PID_XREG, pstEndSessionNtf);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



