/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndHsm.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月10日
  最近修改   :
  功能描述   : HSD发送给HSM的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月10日
    作    者   : h00300778
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "hsm_hsd_pif.h"
#include  "CnasMain.h"
#include  "CnasHsdSndHsm.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_HSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmStartReq
 功能描述  : 向HSM发送开机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmStartReq(VOS_VOID)
{
    HSD_HSM_START_REQ_STRU             *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_HSM_START_REQ_STRU);

    pstMsg  = (HSD_HSM_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_START_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmPowerOffReq
 功能描述  : 向HSM发送关机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmPowerOffReq(VOS_VOID)
{
    HSD_HSM_POWEROFF_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_HSM_POWEROFF_REQ_STRU);

    pstMsg  = (HSD_HSM_POWEROFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_POWEROFF_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_POWEROFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmSysAcqSuccInd
 功能描述  : 向HSM发送搜网成功
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmSysAcqSuccInd(
    VOS_UINT32                                              aulSystemTime[],
    HSD_HSM_SYSTEM_ACQUIRE_TYPE_ENUM_UINT8                  enCurSysAcqType
)
{
    HSD_HSM_SYSTEM_ACQUIRED_IND_STRU   *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_HSM_SYSTEM_ACQUIRED_IND_STRU);

    pstMsg  = (HSD_HSM_SYSTEM_ACQUIRED_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_SYSTEM_ACQUIRED_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_SYSTEM_ACQUIRED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->aulSystemTime[0]            = aulSystemTime[0];
    pstMsg->aulSystemTime[1]            = aulSystemTime[1];
    pstMsg->enSysAcqType                = enCurSysAcqType;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmOverheadMsgInd
 功能描述  : 向HSM发送Overhead消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmOverheadMsgInd(
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg
)
{
    HSD_HSM_OVERHEAD_MSG_IND_STRU      *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_OVERHEAD_MSG_IND_STRU);

    pstMsg  = (HSD_HSM_OVERHEAD_MSG_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_OVERHEAD_MSG_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_OVERHEAD_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->usBandClass                 = pstCasOhmMsg->usBandClass;
    pstMsg->usFreq                      = pstCasOhmMsg->usFreq;
    pstMsg->usCountryCode               = pstCasOhmMsg->usCountryCode;

    pstMsg->ucColorCode                 = pstCasOhmMsg->ucColorCode;

    pstMsg->ucSubNetMask                = pstCasOhmMsg->ucSubNetMask;
    pstMsg->ucSecondaryColorCodeCount   = pstCasOhmMsg->ucSecondaryColorCodeCount;
    pstMsg->lLongitude                  = pstCasOhmMsg->lLongitude;
    pstMsg->lLatitude                   = pstCasOhmMsg->lLatitude;

    PS_MEM_CPY(pstMsg->aucSectorId, pstCasOhmMsg->aucSectorId, HSD_HSM_SUBNET_ID_MAX_LENGTH);
    PS_MEM_CPY(pstMsg->aucSecondaryColorCode, pstCasOhmMsg->aucSecondaryColorCode, HSD_HSM_SECOND_COLORCODE_MAX_LENGTH);

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID CNAS_HSD_SndHsmOhmNotCurrentInd(VOS_VOID)
{
    HSD_HSM_OHM_NOT_CURRENT_IND_STRU   *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_OHM_NOT_CURRENT_IND_STRU);

    pstMsg  = (HSD_HSM_OHM_NOT_CURRENT_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_OHM_NOT_CURRENT_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_OHM_NOT_CURRENT_IND_STRU) - VOS_MSG_HEAD_LENGTH;


    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmIratFromLteInd
 功能描述  : 向HSM发送ID_HSD_HSM_IRAT_FROM_LTE_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmIratFromLteInd(VOS_VOID)
{
    HSD_HSM_IRAT_FROM_LTE_IND_STRU     *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_IRAT_FROM_LTE_IND_STRU);

    pstMsg  = (HSD_HSM_IRAT_FROM_LTE_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_IRAT_FROM_LTE_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_IRAT_FROM_LTE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmIratToLteInd
 功能描述  : 向HSM发送ID_HSD_HSM_IRAT_TO_LTE_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmIratToLteInd(VOS_VOID)
{
    HSD_HSM_IRAT_TO_LTE_IND_STRU       *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_IRAT_TO_LTE_IND_STRU);

    pstMsg  = (HSD_HSM_IRAT_TO_LTE_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_IRAT_TO_LTE_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_IRAT_TO_LTE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmSuspendInd
 功能描述  : 向HSM发送ID_HSD_HSM_SUSPEND_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmSuspendInd(VOS_VOID)
{
    HSD_HSM_SUSPEND_IND_STRU           *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_SUSPEND_IND_STRU);

    pstMsg  = (HSD_HSM_SUSPEND_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_SUSPEND_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmResumeInd
 功能描述  : 向HSM发送ID_HSD_HSM_RESUME_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmResumeInd(VOS_VOID)
{
    HSD_HSM_RESUME_IND_STRU            *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_RESUME_IND_STRU);

    pstMsg  = (HSD_HSM_RESUME_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_RESUME_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmPowerSaveReq
 功能描述  : 向HSM发送ID_HSD_HSM_POWER_SAVE_REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmPowerSaveReq(VOS_VOID)
{
    HSD_HSM_POWER_SAVE_REQ_STRU         *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_POWER_SAVE_REQ_STRU);

    pstMsg  = (HSD_HSM_POWER_SAVE_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_POWER_SAVE_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmPilotSearchFailNtf
 功能描述  : 向HSM发送ID_HSD_HSM_RESUME_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月12日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmPilotSearchFailNtf(VOS_VOID)
{
    HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU);

    pstMsg  = (HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
