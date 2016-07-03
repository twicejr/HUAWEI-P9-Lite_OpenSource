

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "UsimmApi.h"
#include "usimmbase.h"
#include "siapppb.h"
#include "siappstk.h"
#include "siapppih.h"
#include "siappstk.h"
#include "NasNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e767 修改人:胡骏 59254;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_INSTANCE_API_C
/*lint +e767 修改人:胡骏 59254;*/


#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
extern VOS_UINT32 I1_USIMM_IsServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_BOOL I1_USIMM_IsTestCard(VOS_VOID);

extern VOS_BOOL I1_USIMM_IsCdmaTestCard(VOS_VOID);

extern VOS_UINT32 I1_USIMM_GetPinStatus(VOS_UINT8 *pucType,VOS_UINT8 * pucBeEnable,VOS_UINT8 * pucBeNeed,VOS_UINT8 * pucNum);

extern VOS_UINT32 I1_USIMM_GetCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *pulCardStatus);

extern VOS_UINT32 I1_USIMM_GetCardIMSI(VOS_UINT8 *pucImsi);

extern VOS_UINT32 I1_USIMM_GetPinRemainTime(USIMM_PIN_REMAIN_STRU *pstRemainTime);

extern VOS_VOID I1_USIMM_BdnQuery(VOS_UINT32 *pulState);

extern VOS_VOID I1_USIMM_FdnQuery(VOS_UINT32 *pulUsimFdnState, VOS_UINT32 *pulCsimFdnState);

extern VOS_UINT32 I1_USIMM_GetCardTypeByAppType(
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 I1_USIMM_GetCachedFile(VOS_CHAR *pusFileStr, VOS_UINT32 *pulDataLen, VOS_UINT8 **ppucData, USIMM_CARDAPP_ENUM_UINT32 enAppType);

extern VOS_UINT32 I1_PIH_RegUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 I1_PIH_DeregUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 I1_PIH_RegCardRefreshIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 I1_PIH_DeregCardRefreshIndMsg(VOS_UINT32 ulRegPID);

extern SI_UINT32 I1_SI_PB_GetEccNumber(SI_PB_ECC_DATA_STRU *pstEccData);

extern VOS_UINT32 I1_SI_STK_EnvelopeRsp_Decode(SI_STK_ENVELOPE_TYPE_UINT32 enDataType,VOS_UINT32 ulDataLen,VOS_UINT8 *pucCmdData,SI_STK_ENVELOPE_RSP_STRU *pstRspData);

extern VOS_VOID I1_SI_STK_EnvelopeRspDataFree(SI_STK_ENVELOPE_RSP_STRU *pstData);

extern SI_UINT32 I1_SI_STK_EnvelopeDownload(VOS_UINT32 ulSenderPid, VOS_UINT32 ulSendPara, SI_STK_ENVELOPE_STRU* pstENStru);

extern VOS_VOID I1_SI_STK_CCResultInd(SI_STK_ENVELOPE_RSP_STRU    *pstRspData);

extern VOS_VOID I1_SI_STK_SMSCtrlResultInd(SI_STK_ENVELOPE_RSP_STRU *pstRspData);

extern VOS_UINT32 I1_USIMM_VsimIsActive(VOS_VOID);

extern VOS_UINT32 I2_USIMM_IsServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_BOOL I2_USIMM_IsTestCard(VOS_VOID);

extern VOS_BOOL I2_USIMM_IsCdmaTestCard(VOS_VOID);

extern VOS_UINT32 I2_USIMM_GetPinStatus(VOS_UINT8 *pucType,VOS_UINT8 * pucBeEnable,VOS_UINT8 * pucBeNeed,VOS_UINT8 * pucNum);

extern VOS_UINT32 I2_USIMM_GetCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *pulCardStatus);

extern VOS_UINT32 I2_USIMM_GetCachedFile(VOS_CHAR *pusFileStr, VOS_UINT32 *pulDataLen, VOS_UINT8 **ppucData, USIMM_CARDAPP_ENUM_UINT32 enAppType);

extern VOS_UINT32 I2_USIMM_GetCardIMSI(VOS_UINT8 *pucImsi);

extern VOS_UINT32 I2_USIMM_GetPinRemainTime(USIMM_PIN_REMAIN_STRU *pstRemainTime);

extern VOS_VOID I2_USIMM_BdnQuery(VOS_UINT32 *pulState);

extern VOS_VOID I2_USIMM_FdnQuery(VOS_UINT32 *pulUsimFdnState, VOS_UINT32 *pulCsimFdnState);

extern VOS_UINT32 I2_USIMM_GetCardTypeByAppType(
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 I2_PIH_RegUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 I2_PIH_DeregUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 I2_PIH_RegCardRefreshIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 I2_PIH_DeregCardRefreshIndMsg(VOS_UINT32 ulRegPID);

extern SI_UINT32 I2_SI_PB_GetEccNumber(SI_PB_ECC_DATA_STRU *pstEccData);

extern VOS_UINT32 I2_SI_STK_EnvelopeRsp_Decode(SI_STK_ENVELOPE_TYPE_UINT32 enDataType,VOS_UINT32 ulDataLen,VOS_UINT8 *pucCmdData,SI_STK_ENVELOPE_RSP_STRU *pstRspData);

extern VOS_VOID I2_SI_STK_EnvelopeRspDataFree(SI_STK_ENVELOPE_RSP_STRU *pstData);

extern VOS_VOID I2_SI_STK_CCResultInd(SI_STK_ENVELOPE_RSP_STRU    *pstRspData);

extern VOS_VOID I2_SI_STK_SMSCtrlResultInd(SI_STK_ENVELOPE_RSP_STRU *pstRspData);

extern VOS_UINT32 I2_USIMM_VsimIsActive(VOS_VOID);

#endif



VOS_UINT32 USIMM_IsSvlte(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    SVLTE_SUPPORT_FLAG_STRU             stSvlteFlag;

    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_SVLTE_FLAG, &stSvlteFlag, sizeof(SVLTE_SUPPORT_FLAG_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_IsSvlte: Read NV en_NV_Item_SVLTE_FLAG Fail");

        return VOS_FALSE;
    }

    return (VOS_UINT32)stSvlteFlag.ucSvlteSupportFlag;

#else

    return VOS_FALSE;

#endif
}


VOS_UINT32 USIMM_VsimIsActive_Instance(MODEM_ID_ENUM_UINT16 enModemID)
{
#if (FEATURE_VSIM == FEATURE_ON)
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_VsimIsActive_Instance: call USIMM_VsimIsActive");

        return USIMM_VsimIsActive();
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_VsimIsActive_Instance: call I1_USIMM_VsimIsActive");

        return I1_USIMM_VsimIsActive();
    }

#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_VsimIsActive_Instance: call I2_USIMM_VsimIsActive");

        return I2_USIMM_VsimIsActive();
    }
#endif /* MULTI_MODEM_NUMBER == 3 */
#endif /* FEATURE_MULTI_MODEM == FEATURE_ON */
#endif /* FEATURE_VSIM == FEATURE_ON */
    USIMM_ERROR_LOG("USIMM_VsimIsActive_Instance: Para is Error");

    return VOS_FALSE;
}


VOS_UINT32 USIMM_IsServiceAvailable_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    UICC_SERVICES_TYPE_ENUM_UINT32      enService)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsServiceAvailable_Instance: call USIMM_IsServiceAvailable");

        return USIMM_IsServiceAvailable(enService);
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsServiceAvailable_Instance: call I1_USIMM_IsServiceAvailable");

        return I1_USIMM_IsServiceAvailable(enService);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsServiceAvailable_Instance: call I2_USIMM_IsServiceAvailable");

        return I2_USIMM_IsServiceAvailable(enService);
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_IsServiceAvailable_Instance: Para Is Error");

    return PS_USIM_SERVICE_NOT_AVAILIABLE;
}


VOS_BOOL USIMM_IsTestCard_Instance(MODEM_ID_ENUM_UINT16 enModemID)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsTestCard_Instance: call USIMM_IsTestCard");

        return USIMM_IsTestCard();
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsTestCard_Instance: call I1_USIMM_IsTestCard");

        return I1_USIMM_IsTestCard();
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsTestCard_Instance: call I2_USIMM_IsTestCard");

        return I2_USIMM_IsTestCard();
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_IsTestCard_Instance: Para Is Error");

    return VOS_FALSE;
}


VOS_BOOL USIMM_IsCdmaTestCard_Instance(MODEM_ID_ENUM_UINT16 enModemID)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsCdmaTestCard_Instance: call USIMM_IsCdmaTestCard");

        return USIMM_IsCdmaTestCard();
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsTestCard_Instance: call I1_USIMM_IsCdmaTestCard");

        return I1_USIMM_IsCdmaTestCard();
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_IsTestCard_Instance: call I2_USIMM_IsCdmaTestCard");

        return I2_USIMM_IsCdmaTestCard();
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_IsCdmaTestCard_Instance: enModemID Is Error");

    return VOS_FALSE;
}


VOS_UINT32 USIMM_GetPinStatus_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT8                          *pucType,
    VOS_UINT8                          *pucBeEnable,
    VOS_UINT8                          *pucBeNeed,
    VOS_UINT8                          *pucNum)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetPinStatus_Instance: call USIMM_GetPinStatus");

        return USIMM_GetPinStatus(pucType, pucBeEnable, pucBeNeed, pucNum);
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetPinStatus_Instance: call I1_USIMM_GetPinStatus");

        return I1_USIMM_GetPinStatus(pucType, pucBeEnable, pucBeNeed, pucNum);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetPinStatus_Instance: call I2_USIMM_GetPinStatus");

        return I2_USIMM_GetPinStatus(pucType, pucBeEnable, pucBeNeed, pucNum);
    }
#endif

#endif

    USIMM_ERROR_LOG("USIMM_GetPinStatus_Instance: Para Is Error");

    return USIMM_API_WRONG_PARA;
}


VOS_UINT32 USIMM_GetCardType_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *pulCardStatus)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardType_Instance: call USIMM_GetCardType");

        return USIMM_GetCardType(enCardType, pulCardStatus);
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardType_Instance: call I1_USIMM_GetCardType");

        return I1_USIMM_GetCardType(enCardType, pulCardStatus);
    }

#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardType_Instance: call I2_USIMM_GetCardType");

        return I2_USIMM_GetCardType(enCardType, pulCardStatus);
    }
#endif

#endif

    USIMM_ERROR_LOG("USIMM_GetCardType_Instance: Para Is Error");

    return USIMM_API_WRONG_PARA;
}


VOS_UINT32 USIMM_GetCachedFile_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_CHAR                           *pucFilePath,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCachedFile_Instance: call USIMM_GetCachedFile");

        return USIMM_GetCachedFile(pucFilePath, pulDataLen, ppucData, enAppType);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCachedFile_Instance: call I1_USIMM_GetCachedFile");

        return I1_USIMM_GetCachedFile(pucFilePath, pulDataLen, ppucData, enAppType);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCachedFile_Instance: call I2_USIMM_GetCachedFile");

        return I2_USIMM_GetCachedFile(pucFilePath, pulDataLen, ppucData, enAppType);
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_GetCachedFile_Instance: Para Is Error");

    return USIMM_API_WRONG_PARA;
}


VOS_UINT32 USIMM_GetCardIMSI_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT8                          *pucImsi)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardIMSI_Instance: call USIMM_GetCardIMSI");

        return USIMM_GetCardIMSI(pucImsi);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardIMSI_Instance: call I1_USIMM_GetCardIMSI");

        return I1_USIMM_GetCardIMSI(pucImsi);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardIMSI_Instance: call I2_USIMM_GetCardIMSI");

        return I2_USIMM_GetCardIMSI(pucImsi);
    }
#endif

#endif

    USIMM_ERROR_LOG("USIMM_GetCardIMSI_Instance: Para Is Error");

    return USIMM_API_WRONG_PARA;
}


VOS_UINT32 USIMM_GetPinRemainTime_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    USIMM_PIN_REMAIN_STRU              *pstRemainTime)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetPinRemainTime_Instance: call USIMM_GetPinRemainTime");

        return USIMM_GetPinRemainTime(pstRemainTime);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetPinRemainTime_Instance: call I1_USIMM_GetPinRemainTime");

        return I1_USIMM_GetPinRemainTime(pstRemainTime);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetPinRemainTime_Instance: call I2_USIMM_GetPinRemainTime");

        return I2_USIMM_GetPinRemainTime(pstRemainTime);
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_GetPinRemainTime_Instance: Para Is Error");

    return USIMM_API_WRONG_PARA;
}


VOS_VOID USIMM_BdnQuery_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                         *pulState)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_BdnQuery_Instance: call USIMM_BdnQuery");

        USIMM_BdnQuery(pulState);

        return;
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_BdnQuery_Instance: call I1_USIMM_BdnQuery");

        I1_USIMM_BdnQuery(pulState);

        return;
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_BdnQuery_Instance: call I2_USIMM_BdnQuery");

        I2_USIMM_BdnQuery(pulState);

        return;
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_BdnQuery_Instance: Para Is Error");

    *pulState = USIMM_BDNSTATUS_BUTT;

    return;
}


VOS_VOID USIMM_FdnQuery_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                         *pulUsimFdnState,
    VOS_UINT32                         *pulCsimFdnState)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_FdnQuery_Instance: call USIMM_FdnQuery");

        USIMM_FdnQuery(pulUsimFdnState, pulCsimFdnState);

        return;
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_FdnQuery_Instance: call I1_USIMM_FdnQuery");

        I1_USIMM_FdnQuery(pulUsimFdnState, pulCsimFdnState);

        return;
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_FdnQuery_Instance: call I2_USIMM_FdnQuery");

        I2_USIMM_FdnQuery(pulUsimFdnState, pulCsimFdnState);

        return;
    }
#endif
#endif

    USIMM_ERROR_LOG("USIMM_FdnQuery_Instance: Para Is Error");

    if (VOS_NULL_PTR != pulUsimFdnState)
    {
        *pulUsimFdnState = USIMM_FDNSTATUS_BUTT;
    }

    if (VOS_NULL_PTR != pulCsimFdnState)
    {
        *pulCsimFdnState = USIMM_FDNSTATUS_BUTT;
    }

    return;
}


VOS_UINT32 USIMM_GetCardTypeByAppType_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardTypeByAppType_Instance: call USIMM_GetCardTypeByAppType");

        /*lint -e534*/
        USIMM_GetCardTypeByAppType(pucCardStatus, pucCardType, enAppType);
        /*lint +e534*/

        return VOS_OK;
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardTypeByAppType_Instance: call I1_USIMM_GetCardTypeByAppType");

        /*lint -e534*/
        I1_USIMM_GetCardTypeByAppType(pucCardStatus, pucCardType, enAppType);

        return VOS_OK;
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("USIMM_GetCardTypeByAppType_Instance: call I2_USIMM_GetCardTypeByAppType");

        I2_USIMM_GetCardTypeByAppType(pucCardStatus, pucCardType, enAppType);

        return VOS_OK;
    }
#endif
#endif

    return VOS_ERR;
}


VOS_UINT32 PIH_RegUsimCardStatusIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_RegUsimCardStatusIndMsg_Instance: call PIH_RegUsimCardStatusIndMsg");

        return PIH_RegUsimCardStatusIndMsg(ulRegPID);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_RegUsimCardStatusIndMsg_Instance: call I1_PIH_RegUsimCardStatusIndMsg");

        return I1_PIH_RegUsimCardStatusIndMsg(ulRegPID);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_RegUsimCardStatusIndMsg_Instance: call I2_PIH_RegUsimCardStatusIndMsg");

        return I2_PIH_RegUsimCardStatusIndMsg(ulRegPID);
    }
#endif
#endif

    USIMM_ERROR_LOG("PIH_RegUsimCardStatusIndMsg_Instance: Para Is Error");

    return VOS_ERR;
}


VOS_UINT32 PIH_DeregUsimCardStatusIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_DeregUsimCardStatusIndMsg_Instance: call PIH_DeregUsimCardStatusIndMsg");

        return PIH_DeregUsimCardStatusIndMsg(ulRegPID);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_DeregUsimCardStatusIndMsg_Instance: call I1_PIH_DeregUsimCardStatusIndMsg");

        return I1_PIH_DeregUsimCardStatusIndMsg(ulRegPID);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_DeregUsimCardStatusIndMsg_Instance: call I2_PIH_DeregUsimCardStatusIndMsg");

        return I2_PIH_DeregUsimCardStatusIndMsg(ulRegPID);
    }
#endif
#endif

    USIMM_ERROR_LOG("PIH_DeregUsimCardStatusIndMsg_Instance: Para Is Error");

    return VOS_ERR;
}


VOS_UINT32 PIH_RegCardRefreshIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_RegCardRefreshIndMsg_Instance: call PIH_RegCardRefreshIndMsg");

        return PIH_RegCardRefreshIndMsg(ulRegPID);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_RegCardRefreshIndMsg_Instance: call I1_PIH_RegCardRefreshIndMsg");

        return I1_PIH_RegCardRefreshIndMsg(ulRegPID);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_RegCardRefreshIndMsg_Instance: call I2_PIH_RegCardRefreshIndMsg");

        return I2_PIH_RegCardRefreshIndMsg(ulRegPID);
    }
#endif
#endif

    USIMM_ERROR_LOG("PIH_RegCardRefreshIndMsg_Instance: Para Is Error");

    return VOS_ERR;
}


VOS_UINT32 PIH_DeregCardRefreshIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_DeregCardRefreshIndMsg_Instance: call PIH_RegCardRefreshIndMsg");

        return PIH_DeregCardRefreshIndMsg(ulRegPID);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_DeregCardRefreshIndMsg_Instance: call PIH_RegCardRefreshIndMsg");

        return I1_PIH_DeregCardRefreshIndMsg(ulRegPID);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("PIH_DeregCardRefreshIndMsg_Instance: call I2_PIH_DeregCardRefreshIndMsg");

        return I2_PIH_DeregCardRefreshIndMsg(ulRegPID);
    }
#endif
#endif

    USIMM_ERROR_LOG("PIH_DeregCardRefreshIndMsg_Instance: Para Is Error");

    return VOS_ERR;
}


VOS_UINT32 SI_PB_GetEccNumber_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_PB_ECC_DATA_STRU                *pstEccData)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_PB_GetEccNumber_Instance: call SI_PB_GetEccNumber");

        return SI_PB_GetEccNumber(pstEccData);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_PB_GetEccNumber_Instance: call I1_SI_PB_GetEccNumber");

        return I1_SI_PB_GetEccNumber(pstEccData);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_PB_GetEccNumber_Instance: call I2_SI_PB_GetEccNumber");

        return I2_SI_PB_GetEccNumber(pstEccData);
    }
#endif
#endif

    USIMM_ERROR_LOG("SI_PB_GetEccNumber_Instance: Para Is Error");

    return VOS_ERR;
}


VOS_UINT32 SI_STK_EnvelopeRsp_Decode_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_STK_ENVELOPE_TYPE_UINT32         enDataType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_EnvelopeRsp_Decode_Instance: call SI_STK_EnvelopeRsp_Decode");

        return SI_STK_EnvelopeRsp_Decode(enDataType, ulDataLen, pucCmdData, pstRspData);
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_EnvelopeRsp_Decode_Instance: call I1_SI_STK_EnvelopeRsp_Decode");

        return I1_SI_STK_EnvelopeRsp_Decode(enDataType, ulDataLen, pucCmdData, pstRspData);
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_EnvelopeRsp_Decode_Instance: call I2_SI_STK_EnvelopeRsp_Decode");

        return I2_SI_STK_EnvelopeRsp_Decode(enDataType, ulDataLen, pucCmdData, pstRspData);
    }
#endif
#endif

    USIMM_ERROR_LOG("SI_STK_EnvelopeRsp_Decode_Instance: Para Is Error");

    return VOS_ERR;
}


VOS_VOID SI_STK_EnvelopeRspDataFree_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_STK_ENVELOPE_RSP_STRU           *pstData)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_EnvelopeRspDataFree_Instance: call SI_STK_EnvelopeRspDataFree");

        SI_STK_EnvelopeRspDataFree(pstData);

        return;
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_EnvelopeRspDataFree_Instance: call I1_SI_STK_EnvelopeRspDataFree");

        I1_SI_STK_EnvelopeRspDataFree(pstData);

        return;
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_EnvelopeRspDataFree_Instance: call I2_SI_STK_EnvelopeRspDataFree");

        I2_SI_STK_EnvelopeRspDataFree(pstData);

        return;
    }
#endif
#endif

    USIMM_ERROR_LOG("SI_STK_EnvelopeRsp_Decode_Instance: Para Is Error");

    return;
}


VOS_VOID SI_STK_CCResultInd_Instance(
    MODEM_ID_ENUM_UINT16                                    enModemID,
    SI_STK_ENVELOPE_RSP_STRU                                *pstRspData)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_CCResultInd_Instance: call SI_STK_CCResultInd");

        SI_STK_CCResultInd(pstRspData);

        return;
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_CCResultInd_Instance: call I1_SI_STK_CCResultInd");

        I1_SI_STK_CCResultInd(pstRspData);

        return;
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_CCResultInd_Instance: call I2_SI_STK_CCResultInd");

        I2_SI_STK_CCResultInd(pstRspData);

        return;
    }
#endif
#endif

    USIMM_ERROR_LOG("SI_STK_CCResultInd_Instance: Para Is Error");

    return;
}


VOS_VOID SI_STK_SMSCtrlResultInd_Instance(
    MODEM_ID_ENUM_UINT16                                    enModemID,
    SI_STK_ENVELOPE_RSP_STRU                                *pstRspData)
{
    if (MODEM_ID_0 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_SMSCtrlResultInd_Instance: call SI_STK_SMSCtrlResultInd");

        SI_STK_SMSCtrlResultInd(pstRspData);

        return;
    }
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if (MODEM_ID_1 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_SMSCtrlResultInd_Instance: call I1_SI_STK_SMSCtrlResultInd");

        I1_SI_STK_SMSCtrlResultInd(pstRspData);

        return;
    }
#if (MULTI_MODEM_NUMBER == 3)
    if (MODEM_ID_2 == enModemID)
    {
        USIMM_NORMAL_LOG("SI_STK_SMSCtrlResultInd_Instance: call I2_SI_STK_SMSCtrlResultInd");

        I2_SI_STK_SMSCtrlResultInd(pstRspData);

        return;
    }
#endif
#endif

    USIMM_ERROR_LOG("SI_STK_SMSCtrlResultInd_Instance: Para Is Error");

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




