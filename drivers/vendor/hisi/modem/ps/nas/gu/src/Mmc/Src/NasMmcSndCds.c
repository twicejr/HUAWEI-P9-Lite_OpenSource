
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "CdsMmcInterface.h"
#include "NasMmlCtx.h"
#include "NasMmcSndCds.h"
#include "PsCommonDef.h"
#include "NasComm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_CDS_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

MMC_CDS_MODE_ENUM_UINT32 NAS_MMC_ConverMmlRatTypeToCds(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            return MMC_CDS_MODE_GU;


        case NAS_MML_NET_RAT_TYPE_LTE:
            return MMC_CDS_MODE_LTE;

        default:
            return MMC_CDS_MODE_NULL;

    }
}


VOS_VOID  NAS_MMC_SndCdsModeChangeInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enRatType
)
{
    MMC_CDS_MODE_CHANGE_IND_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMC_CDS_MODE_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMC,
                        sizeof(MMC_CDS_MODE_CHANGE_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: memery alloc failed.");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverPid   = UEPS_PID_CDS;
    pstMsg->ulLength        = sizeof(MMC_CDS_MODE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_MMC_CDS_MODE_CHANGE_IND;

    pstMsg->enMode          = NAS_MMC_ConverMmlRatTypeToCds(enRatType);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCdsModeChangeInd: send message failed.");
    }

    return;
}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

