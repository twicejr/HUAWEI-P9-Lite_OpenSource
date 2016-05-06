/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluSndAs.c
  版 本 号   : 初稿
  作    者   : h00313353
  生成日期   : 2015年5月22日
  最近修改   :
  功能描述   : HLU发送给接入层的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月22日
    作    者   : h0031335
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CnasHluSndAs.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "Nas_Mem.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_SND_AS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CNAS_HLU_SndCasBeginSessionNotify
 功能描述  : HLU向CAS申请Session保护
 输入参数  : enSessionType : HLU申请保护的session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00133353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HLU_SndCasBeginSessionNotify(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
)
{
    CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU                   *pstBeginSessionNotify   = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HLU, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_HLU;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_HALMP;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_HRPD_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->usOpId           = 0x00;
    pstBeginSessionNotify->enSessionType    = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBeginSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HLU, pstBeginSessionNotify);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HLU_SndCasEndSessionNotify
 功能描述  : HLU向CAS申请Session释放
 输入参数  : enSessionType : HLU申请释放的session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00133353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HLU_SndCasEndSessionNotify(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
)
{
    CNAS_CAS_HRPD_SESSION_END_NTF_STRU                     *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_HRPD_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_HRPD_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HLU, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstEndSessionNotify->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid       = UEPS_PID_HLU;
    pstEndSessionNotify->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid     = UEPS_PID_HALMP;
    pstEndSessionNotify->ulLength          = ulMsgLength;
    pstEndSessionNotify->enMsgId           = ID_CNAS_CAS_HRPD_SESSION_END_NTF;
    pstEndSessionNotify->usOpId            = 0x00;
    pstEndSessionNotify->enSessionType     = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEndSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HLU, pstEndSessionNotify);

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



