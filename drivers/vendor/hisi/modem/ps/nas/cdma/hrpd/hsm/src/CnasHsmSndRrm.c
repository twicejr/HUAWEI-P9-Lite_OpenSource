/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsmSndRrm.c
  版 本 号   : 初稿
  作    者   : t00323010
  生成日期   : 2015年5月29日
  最近修改   :
  功能描述   : HSM发送给RRM的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月29日
    作    者   : t00323010
    修改内容   : 新生成函数

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasMntn.h"
#include "CnasHsmSndRrm.h"
#include "CnasMntn.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_RRM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSM_SndRrmRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_REGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
             enRatType          :接入模式类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月29日
    作    者   : t00323010
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSM_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType,
    VOS_RATMODE_ENUM_UINT32             enRatType
)
{
    /* 定义调用VOS发送函数的返回值  */
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    /* 定义原语类型指针 */
    PS_RRM_REGISTER_IND_STRU           *pstMsg    = VOS_NULL_PTR;

    enModemId   = VOS_GetModemIDFromPid(UEPS_PID_HSM);

    pstMsg      = (PS_RRM_REGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSM,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SndRrmRegisterInd():Alloc memory failed.");

        /* 返回失败 */
        return;
    }

    NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = enModemId;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = enRatType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSM, pstMsg);

    /* 发送失败 */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SndRrmRegisterInd():Send Msg failed.");
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSM_SndRrmDeRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_DEREGISTER_IND消息
 输入参数  : enTaskType         :去注册任务类型
             enRatType          :接入模式类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月29日
    作    者   : t00323010
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSM_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType,
    VOS_RATMODE_ENUM_UINT32             enRatType
)
{
    /* 定义调用VOS发送函数的返回值  */
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    /* 定义原语类型指针 */
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    enModemId   = VOS_GetModemIDFromPid(UEPS_PID_HSM);

    pstMsg      = (PS_RRM_DEREGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSM,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SndRrmDeRegisterInd():Alloc memory failed.");

        /* 返回失败 */
        return;
    }

    NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = enModemId;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = enRatType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSM, pstMsg);

    /* 发送失败 */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrmDeRegisterInd():Send Msg failed.");
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
