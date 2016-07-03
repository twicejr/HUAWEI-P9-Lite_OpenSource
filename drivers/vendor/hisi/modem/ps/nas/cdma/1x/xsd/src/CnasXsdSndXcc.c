

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasMain.h"
#include "CnasXsdSndXcc.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID CNAS_XSD_SndXccStartReq(VOS_VOID)
{
    XSD_XCC_START_REQ_STRU             *pstInternalMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(XSD_XCC_START_REQ_STRU);

    pstInternalMsg  = (XSD_XCC_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XSD, ulLen);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    /* 填充消息 */

    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_XCC;

    pstInternalMsg->enMsgId                     = ID_XSD_XCC_START_REQ;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(XSD_XCC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstInternalMsg);

}


VOS_VOID CNAS_XSD_SndXccPowerOffReq(
    XCC_XSD_POWER_OFF_REASON_ENUM_UINT32                    enPowerOffReason
)
{
    XSD_XCC_POWER_OFF_REQ_STRU         *pstInternalMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(XSD_XCC_POWER_OFF_REQ_STRU);

    pstInternalMsg  = (XSD_XCC_POWER_OFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XSD, ulLen);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    /* 填充消息 */

    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_XCC;

    pstInternalMsg->enMsgId                     = ID_XSD_XCC_POWER_OFF_REQ;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(XSD_XCC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enPowerOffReason            = enPowerOffReason;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstInternalMsg);

}


VOS_VOID CNAS_XSD_SndXccNdssResultInd(
    XSD_XCC_NDSS_RESULT_ENUM_UINT8      enNsddResult
)
{
    XSD_XCC_NDSS_RESULT_IND_STRU       *pstNdssResultInd  = VOS_NULL_PTR;

    pstNdssResultInd  = (XSD_XCC_NDSS_RESULT_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XSD,
                                                                              sizeof(XSD_XCC_NDSS_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstNdssResultInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstNdssResultInd, sizeof(XSD_XCC_NDSS_RESULT_IND_STRU), 0, sizeof(XSD_XCC_NDSS_RESULT_IND_STRU));

    /* 填充消息 */
    pstNdssResultInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNdssResultInd->ulReceiverPid    = UEPS_PID_XCC;
    pstNdssResultInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNdssResultInd->ulSenderPid      = UEPS_PID_XSD;
    pstNdssResultInd->ulLength         = sizeof(XSD_XCC_NDSS_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNdssResultInd->enMsgId                = ID_XSD_XCC_NDSS_RESULT_IND;
    pstNdssResultInd->enNsddResult           = enNsddResult;

    /* 发送消息 */
    CNAS_SndInternalMsg(pstNdssResultInd);
}

/*lint -restore*/
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

