

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasMain.h"
#include  "CnasHsdSndEhsm.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_EHSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID CNAS_HSD_SndEhsmStartReq(
    MSCC_HSD_START_REQ_STRU            *pstMsg
)
{
    HSD_EHSM_START_REQ_STRU            *pstStartMsg;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    i                                   = 0;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen        = sizeof(HSD_EHSM_START_REQ_STRU);

    pstStartMsg  = (HSD_EHSM_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstStartMsg)
    {
        return;
    }

    /* 填充消息 */
    pstStartMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstStartMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstStartMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstStartMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstStartMsg->enMsgId                     = ID_HSD_EHSM_START_REQ;
    pstStartMsg->usOpId                      = 0;
    pstStartMsg->ulLength                    = sizeof(HSD_EHSM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstStartMsg->enModemId                   = pstMsg->enModemId;

    /* 初始化RatMode = BUTT */
    for (i = NAS_MSCC_PIF_MAX_RAT_NUM; i < VOS_RATMODE_BUTT; i++)
    {
        pstStartMsg->aenRatMode[i]  = VOS_RATMODE_BUTT;
    }

    PS_MEM_CPY(pstStartMsg->aenRatMode,
               pstMsg->aenRatMode,
               NAS_MSCC_PIF_MAX_RAT_NUM * sizeof(VOS_RATMODE_ENUM_UINT32));

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstStartMsg);

    return;
}


VOS_VOID CNAS_HSD_SndEhsmPowerOffReq(
    EHSM_HSD_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
)
{
    HSD_EHSM_POWER_OFF_REQ_STRU        *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_EHSM_POWER_OFF_REQ_STRU);

    pstMsg  = (HSD_EHSM_POWER_OFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;

    pstMsg->enMsgId                     = ID_HSD_EHSM_POWER_OFF_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_EHSM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enCause                     = enCause;

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
