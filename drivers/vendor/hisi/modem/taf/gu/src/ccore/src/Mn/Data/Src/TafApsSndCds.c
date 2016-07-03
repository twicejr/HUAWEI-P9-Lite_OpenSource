

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "ApsCdsInterface.h"
#include "TafApsComFunc.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsCtx.h"
#include "ehsm_aps_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_CDS_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_VOID TAF_APS_SndCdsSndBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *pstSndBuffData = VOS_NULL_PTR;

    pstSndBuffData = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstSndBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsSndBuffDataInd: Memory alloc failed");
        return;
    }

    pstSndBuffData->ulReceiverPid       = UEPS_PID_CDS;
    pstSndBuffData->enMsgId             = ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND;
    pstSndBuffData->usOpId              = 0;
    pstSndBuffData->ucRabId             = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndBuffData);

    return;
}


VOS_VOID TAF_APS_SndCdsFreeBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *pstFreeBuffData = VOS_NULL_PTR;

    pstFreeBuffData = (APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstFreeBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsFreeBuffDataInd: Memory alloc failed");
        return;
    }

    pstFreeBuffData->ulReceiverPid      = UEPS_PID_CDS;
    pstFreeBuffData->enMsgId            = ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND;
    pstFreeBuffData->usOpId             = 0;
    pstFreeBuffData->ucRabId            = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstFreeBuffData);

    return;
}



VOS_VOID TAF_APS_SndCdsModeChangeInd(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{
    APS_CDS_MODE_CHANGE_IND_STRU       *pstSndMsg = VOS_NULL_PTR;
    APS_CDS_MODE_ENUM_UINT32            enMode;

    switch (enCurrCdataServiceMode)
    {
        case TAF_APS_RAT_TYPE_1X:
            enMode = APS_CDS_MODE_1X;
            break;
        case TAF_APS_RAT_TYPE_HRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            enMode = APS_CDS_MODE_GU;
            break;
        case TAF_APS_RAT_TYPE_LTE:
            enMode = APS_CDS_MODE_LTE;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Mode Error");
            return;
    }

    pstSndMsg = (APS_CDS_MODE_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_MODE_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Memory alloc failed");
        return;
    }

    pstSndMsg->ulReceiverPid    = UEPS_PID_CDS;
    pstSndMsg->enMsgId          = ID_APS_CDS_MODE_CHANGE_IND;
    pstSndMsg->usOpId           = 0;
    pstSndMsg->enMode           = enMode;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    return;

}



APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatus(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                                               ucPdpId;
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8                    enBearStatus;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_CDATA_BEAR_STATUS_INACTIVE;
    }

    enBearStatus = AT_APS_ConvertPsCdataStatusToCsdCdataStatus(TAF_PS_GetCdataBearStatus(ucPdpId));

    return enBearStatus;
}



VOS_UINT8 TAF_APS_MapRabIdToPdnId(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_PDN_ID;
    }

    return TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
}


VOS_UINT8 TAF_APS_MapPdnIdToRabId(
    VOS_UINT8                           ucPdnId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByPndId(ucPdnId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_RAB_ID;
    }

    return TAF_APS_GetPdpEntNsapi(ucPdpId);
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


