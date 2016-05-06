/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsmSndEhsm.c
  版 本 号   : 初稿
  作    者   : t00323010
  生成日期   : 2015年05月30日
  最近修改   :
  功能描述   : HSM发送给EHSM的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月30日
    作    者   : t00323010
    修改内容   : creat

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasHsmSndEhsm.h"
#include "ehsm_hsm_pif.h"
#include "hsm_aps_pif.h"
#include "hsm_hsd_pif.h"
#include "PsCommonDef.h"
#include "CnasHsmComFunc.h"
#include "CnasMntn.h"
#include "CnasMain.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_EHSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CNAS_HSM_SndEhsmSessionInfoInd
 功能描述  : 向EHSM发送ID_HSM_EHSM_SESSION_INFO_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_SndEhsmSessionInfoInd(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                       enSessionType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstMsg;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(HSM_EHSM_SESSION_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstMsg = (HSM_EHSM_SESSION_INFO_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstMsg = (HSM_EHSM_SESSION_INFO_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_EHSM_SESSION_INFO_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (CNAS_HSM_IS_NULL_PTR(pstMsg))
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);
#endif

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;

    pstMsg->enMsgId                     = ID_HSM_EHSM_SESSION_INFO_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = ulLen;

    pstMsg->enSessionType               = CNAS_HSM_ConvertHsmSessionToEhsmSessionType(enSessionType);

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstMsg);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);
#endif

    return;
}



VOS_VOID CNAS_HSM_SndEhsmSuspendInd(VOS_VOID)
{
    HSM_EHSM_SUSPEND_IND_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(HSM_EHSM_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstMsg  = (HSM_EHSM_SUSPEND_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstMsg  = (HSM_EHSM_SUSPEND_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_EHSM_SUSPEND_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (CNAS_HSM_IS_NULL_PTR(pstMsg))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndEhsmSuspendInd: memory alloc fail");
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);
#endif

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_EHSM,
                     ID_HSM_EHSM_SUSPEND_IND,
                     ulLen);

    pstMsg->usOpId  = 0;

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstMsg);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID CNAS_HSM_SndEhsmConnEstCnf(
    EHSM_HSM_RSLT_ENUM_UINT32           enResult
)
{
    HSM_EHSM_CONN_EST_CNF_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(HSM_EHSM_CONN_EST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstMsg  = (HSM_EHSM_CONN_EST_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstMsg  = (HSM_EHSM_CONN_EST_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_EHSM_CONN_EST_CNF_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (CNAS_HSM_IS_NULL_PTR(pstMsg))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndEhsmConnEstCnf: memory alloc fail");
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);
#endif

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_EHSM,
                     ID_HSM_EHSM_CONN_EST_CNF,
                     ulLen);

    pstMsg->usOpId      = 0;
    pstMsg->enResult    = enResult;

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstMsg);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID CNAS_HSM_SndEhsmDiscCnf(VOS_VOID)
{
    HSM_EHSM_DISC_CNF_STRU             *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen   = sizeof(HSM_EHSM_DISC_CNF_STRU) - VOS_MSG_HEAD_LENGTH;


#if defined(DMT)
    pstMsg  = (HSM_EHSM_DISC_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstMsg  = (HSM_EHSM_DISC_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_EHSM_DISC_CNF_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (CNAS_HSM_IS_NULL_PTR(pstMsg))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndEhsmDiscCnf: memory alloc fail");
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);
#endif

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_EHSM,
                     ID_HSM_EHSM_DISC_CNF,
                     ulLen);

    pstMsg->usOpId  = 0;

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstMsg);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID CNAS_HSM_SndEhsmDiscInd(VOS_VOID)
{
    HSM_EHSM_DISC_IND_STRU             *pstEhsmDiscInd;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_EHSM_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstEhsmDiscInd = (HSM_EHSM_DISC_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstEhsmDiscInd = (HSM_EHSM_DISC_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_EHSM_DISC_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (CNAS_HSM_IS_NULL_PTR(pstEhsmDiscInd))
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstEhsmDiscInd + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);
#endif

    CNAS_CFG_MSG_HDR(pstEhsmDiscInd,
                     UEPS_PID_HSM,
                     UEPS_PID_EHSM,
                     ID_HSM_EHSM_DISC_IND,
                     ulLen);

#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstEhsmDiscInd);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstEhsmDiscInd);
#endif

    return;
}


VOS_VOID CNAS_HSM_SndEhsmConnInd(VOS_VOID)
{
    HSM_EHSM_CONNECT_IND_STRU          *pstEhsmConnInd;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(HSM_EHSM_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

#if defined(DMT)
    pstEhsmConnInd = (HSM_EHSM_CONNECT_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);
#else
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, begin */
    pstEhsmConnInd = (HSM_EHSM_CONNECT_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSM, sizeof(HSM_EHSM_CONNECT_IND_STRU));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-15, end */
#endif

    if (CNAS_HSM_IS_NULL_PTR(pstEhsmConnInd))
    {
        return;
    }

#if defined(DMT)
    NAS_MEM_SET_S(((VOS_UINT8 *)pstEhsmConnInd + VOS_MSG_HEAD_LENGTH),
                  ulLen,
                  0,
                  ulLen);
#endif

    CNAS_CFG_MSG_HDR(pstEhsmConnInd,
                     UEPS_PID_HSM,
                     UEPS_PID_EHSM,
                     ID_HSM_EHSM_CONNECT_IND,
                     ulLen);
#if defined(DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstEhsmConnInd);
#else
    (VOS_VOID)CNAS_SndInternalMsg(pstEhsmConnInd);
#endif

    return;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
