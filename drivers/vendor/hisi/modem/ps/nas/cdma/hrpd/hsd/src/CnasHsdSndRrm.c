/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndRrm.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年1月16日
  最近修改   :
  功能描述   : HSD发送给RRM的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月16日
    作    者   : g00256031
    修改内容   : 新生成函数

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasMntn.h"
#include  "PsRrmInterface.h"
#include  "CnasCcb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_RRM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_SndRrmRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_REGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : g00256031
    修改内容   : 新生成函数
  2.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 修改接口
*****************************************************************************/
VOS_VOID CNAS_HSD_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    /* 定义调用VOS发送函数的返回值  */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSD,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmRegisterInd():Alloc memory failed.");

        /* 返回失败 */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_HRPD;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSD, pstMsg);

    /* 发送失败 */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmRegisterInd():Send Msg failed.");
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_SndRrmDeRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_DEREGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : g00256031
    修改内容   : 新生成函数
  2.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 修改接口
*****************************************************************************/
VOS_VOID CNAS_HSD_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    /* 定义调用VOS发送函数的返回值  */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSD,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmDeRegisterInd():Alloc memory failed.");

        /* 返回失败 */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_HRPD;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSD, pstMsg);

    /* 发送失败 */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmDeRegisterInd():Send Msg failed.");
    }

    return;
}

#endif
/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
