
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MmcApsInterface.h"
#include "NasMmlCtx.h"
#include "NasMmcSndAps.h"
#include "PsCommonDef.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_APS_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

MMC_APS_RAT_TYPE_ENUM_UINT32 NAS_MMC_ConverMmlRatTypeToAps(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            return MMC_APS_RAT_TYPE_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            return MMC_APS_RAT_TYPE_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
            return MMC_APS_RAT_TYPE_LTE;

        default:
            return MMC_APS_RAT_TYPE_NULL;

    }
}


VOS_VOID  NAS_MMC_SndApsServiceStatusInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType,
    VOS_UINT8                                   ucSimPsRegStatus
)
{
    MMC_APS_SERVICE_STATUS_IND_STRU            *pstMsg = VOS_NULL_PTR;


    pstMsg = (MMC_APS_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMC,
                        sizeof(MMC_APS_SERVICE_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: memery alloc failed.");

        return;
    }

    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMC_APS_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMC_APS_SERVICE_STATUS_IND;

    pstMsg->enRatType                   = NAS_MMC_ConverMmlRatTypeToAps(enRatType);

    pstMsg->ulPsSimRegStatus            = ucSimPsRegStatus;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: send message failed.");
    }

    return;
}
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

