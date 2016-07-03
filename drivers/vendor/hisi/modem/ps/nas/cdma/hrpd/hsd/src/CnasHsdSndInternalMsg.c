


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasMain.h"
#include  "CnasHsdCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */

VOS_VOID CNAS_HSD_SndSwitchOnRlst(VOS_UINT32 ulResult)
{
    CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU);

    pstMsg  = (CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = ulResult;

    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}



VOS_VOID CNAS_HSD_SndPowerOffRslt(VOS_VOID)
{
    CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen  = sizeof(CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU);

    pstMsg = (CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


VOS_VOID CNAS_HSD_SndInternalSysAcqReq(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene,
    VOS_UINT32                                              ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstMsg;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU);

    pstMsg  = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSysAcqScene               = enSysAcqScene;
    pstMsg->ulFreqNum                   = ulFreqNum;

    PS_MEM_SET(pstMsg->astFreq, 0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM);

    if ((0 != ulFreqNum)
     && (ulFreqNum <= CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM))
    {
        PS_MEM_CPY(pstMsg->astFreq, pstFreq, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * ulFreqNum);
    }

    /* 发送内部消息 */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


VOS_VOID CNAS_HSD_SndSysAcqRslt(
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8                    enImmediateSysAcq
)
{
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstMsg         = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU);

    pstMsg  = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = enResult;
    pstMsg->enImmediateSysAcq           = enImmediateSysAcq;
    pstMsg->enCurAcqScene               = enCurAcqScene;


    /* 发送内部消息 */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


VOS_VOID CNAS_HSD_SndPowerSaveRslt(VOS_VOID)
{
    CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen  = sizeof(CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU);

    pstMsg = (CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


VOS_VOID CNAS_HSD_SndInterSysRslt(
    VOS_RATMODE_ENUM_UINT32                                 enCampedRatMode,
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
)
{
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen   = sizeof(CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU);

    pstMsg  = (CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enCampedRatMode             = enCampedRatMode;
    pstMsg->ucRslt                      = ucRslt;
    pstMsg->enNetworkLostReason         = enNetworkLostReason;

    /* 发送内部消息 */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


/*lint -restore*/

#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
