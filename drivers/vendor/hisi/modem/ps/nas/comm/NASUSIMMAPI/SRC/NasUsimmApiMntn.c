

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "NasUsimmApiMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_USIMM_API_MNTN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID  NAS_LogUsimmApiSetFileReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_USIMM_MNTN_SETFILE_INFO_STRU   *pstSetFileInfo
)
{
    NAS_LOG_USIMM_API_SET_FILE_REQ_STRU                    *pstMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR != pstSetFileInfo)
    {
        /*lint -e961*/
        pstMsg = (NAS_LOG_USIMM_API_SET_FILE_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                            (sizeof(NAS_LOG_USIMM_API_SET_FILE_REQ_STRU) + pstSetFileInfo->ulEfLen - 3));
        /*lint +e961*/
        if (VOS_NULL_PTR == pstMsg)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiSetFileReq:ERROR:Alloc Mem Fail.");
            return;
        }
        /*lint -e961*/
        PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(NAS_LOG_USIMM_API_SET_FILE_REQ_STRU) + pstSetFileInfo->ulEfLen - 3 - VOS_MSG_HEAD_LENGTH);
        /*lint +e961*/
        pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
        pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
        /*lint -e961*/
        pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_SET_FILE_REQ_STRU) + pstSetFileInfo->ulEfLen - 3 - VOS_MSG_HEAD_LENGTH;
        /*lint +e961*/
        pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_SET_FILE_REQ;
        pstMsg->ulRslt                      = ulRslt;
        pstMsg->enApiType                   = enApiType;

        pstMsg->usFileID                    = pstSetFileInfo->usEfId;
        pstMsg->usDataLen                   = (VOS_UINT16)pstSetFileInfo->ulEfLen;
        pstMsg->ucRecordNum                 = pstSetFileInfo->ucRecordNum;
        pstMsg->enAppType                   = pstSetFileInfo->enAppType;

        if( VOS_NULL_PTR != pstSetFileInfo->pucEfContent)
        {
            PS_MEM_CPY(pstMsg->aucContent, pstSetFileInfo->pucEfContent, pstSetFileInfo->ulEfLen);
        }

        DIAG_TraceReport(pstMsg);

        PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
    }

    return;
}


VOS_VOID  NAS_LogUsimmApiGetFileReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_USIMM_MNTN_GETFILE_INFO_STRU   *pstGetFileInfo

)
{
    NAS_LOG_USIMM_API_GET_FILE_REQ_STRU                    *pstMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR != pstGetFileInfo)
    {
        pstMsg = (NAS_LOG_USIMM_API_GET_FILE_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                              sizeof(NAS_LOG_USIMM_API_GET_FILE_REQ_STRU));

        if (VOS_NULL_PTR == pstMsg)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetFileReq:ERROR:Alloc Mem Fail.");
            return;
        }

        PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(NAS_LOG_USIMM_API_GET_FILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
        pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
        pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_GET_FILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
        pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_GET_FILE_REQ;

        pstMsg->ulRslt                      = ulRslt;
        pstMsg->enApiType                   = enApiType;
        pstMsg->usFileID                    = pstGetFileInfo->usEfId;
        pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
        pstMsg->enAppType                   = pstGetFileInfo->enAppType;

        DIAG_TraceReport(pstMsg);

        PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
    }
    return;
}



VOS_VOID  NAS_LogUsimmApiAuthReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                           ucChallengeType,
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn
)
{
    NAS_LOG_USIMM_API_AUTH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_AUTH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_AUTH_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiAuthReq:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_LOG_USIMM_API_AUTH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_AUTH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_AUTH_REQ;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->enChallengeType             = ucChallengeType;

    if (VOS_NULL_PTR != pucRand)
    {
        /* Rand值不带长度信息，固定为16 */
        PS_MEM_CPY(&pstMsg->aucRand[1], pucRand, NAS_USIMM_AUTH_RAND_LENGTH);
    }

    pstMsg->aucRand[0] = NAS_USIMM_AUTH_RAND_LENGTH;

    if(VOS_NULL_PTR != pucAutn)
    {
        PS_MEM_CPY(pstMsg->aucAUTN, pucAutn, pucAutn[0]+1);
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiPinReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_LOG_USIMM_PIN_INFO_STRU        *pstPinInfo
)
{
    NAS_LOG_USIMM_API_PIN_REQ_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_PIN_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_PIN_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiPinReq:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_LOG_USIMM_API_PIN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_PIN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_PIN_REQ;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    if (VOS_NULL_PTR != pstPinInfo)
    {
        pstMsg->stPinInfo.enPINType  = pstPinInfo->enPINType;
        pstMsg->stPinInfo.enCmdType  = pstPinInfo->enCmdType;

        PS_MEM_CPY(pstMsg->stPinInfo.aucOldPIN, pstPinInfo->aucOldPIN, USIMM_PINNUMBER_LEN);
        PS_MEM_CPY(pstMsg->stPinInfo.aucNewPIN, pstPinInfo->aucNewPIN, USIMM_PINNUMBER_LEN);
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiMaxEFRecordNumReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
)
{
    NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiMaxEFRecordNumReq:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->enAppType                   = enAppType;
    pstMsg->usEfId                      = usEFid;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiIsTestCard(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
)
{
    NAS_LOG_USIMM_API_IS_TEST_CARD_STRU                    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_IS_TEST_CARD_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_IS_TEST_CARD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiIsTestCard:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_LOG_USIMM_API_IS_TEST_CARD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_IS_TEST_CARD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_IS_TEST_CARD;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiGetPinStatus(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_PIN_STATUS_STRU                *pstPinStatus
)
{
    NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetPinStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_GET_PIN_STATUS;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if ( VOS_NULL_PTR != pstPinStatus)
    {
        PS_MEM_CPY(&(pstMsg->stPinStatus), pstPinStatus, sizeof(NAS_PIN_STATUS_STRU));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiGetCardType(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                           ucCardStatus,
    VOS_UINT16                          usCardType
)
{
    NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetCardType:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_GET_CARD_TYPE;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->ucCardStatus                = ucCardStatus;
    pstMsg->usCardType                  = usCardType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiIsServiceAvailable(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    UICC_SERVICES_TYPE_ENUM_UINT32      enService
)
{
    NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                              sizeof(NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetCardType:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->enService                   = enService;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}



VOS_VOID  NAS_LogUsimmApiGetCachedFile(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                         **ppucData
)
{


    NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU                 *pstMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR != *ppucData)
    {
        /*lint -e961*/
        pstMsg = (NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                       (VOS_UINT32)(sizeof(NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU) + ulDataLen - 4));
        /*lint +e961*/
        if (VOS_NULL_PTR == pstMsg)
        {
           TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetCachedFile:ERROR:Alloc Mem Fail.");
           return;
        }
        /*lint -e961*/
        PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                    (VOS_UINT32)(sizeof(NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU) - VOS_MSG_HEAD_LENGTH + ulDataLen - 4));
        /*lint +e961*/
        pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
        pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
        /*lint -e961*/
        pstMsg->stMsgHeader.ulLength        = (VOS_UINT32)(sizeof(NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU) - VOS_MSG_HEAD_LENGTH + ulDataLen - 4);
        /*lint +e961*/
        pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_GET_CACHED_FILE;

        pstMsg->ulRslt                      = ulRslt;
        pstMsg->enApiType                   = enApiType;
        pstMsg->usDataLen                   = (VOS_UINT16)ulDataLen;

        PS_MEM_CPY(pstMsg->aucContent, *ppucData, ulDataLen);

        DIAG_TraceReport(pstMsg);

        PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
    }

    return;

}


VOS_VOID  NAS_LogUsimmApiGetCardIMSI(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetCardIMSI:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_GET_CARD_IMSI;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pucImsi)
    {
        PS_MEM_CPY(pstMsg->aucImsi, pucImsi, sizeof(pstMsg->aucImsi));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiBdnQuery(
    VOS_UINT32                          ulState,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
)
{
    NAS_LOG_USIMM_API_BDN_QUERY_STRU                       *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_BDN_QUERY_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_BDN_QUERY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiBdnQuery:ERROR:Alloc Mem Fail.");
        return;
    }


    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(NAS_LOG_USIMM_API_BDN_QUERY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_BDN_QUERY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_BDN_QUERY;

    pstMsg->ulUsimState                 = ulState;
    pstMsg->enApiType                   = enApiType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiFdnQuery(
    VOS_UINT32                          ulUsimState,
    VOS_UINT32                          ulCsimState,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
)
{
    NAS_LOG_USIMM_API_FDN_QUERY_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_FDN_QUERY_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_FDN_QUERY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiFdnQuery:ERROR:Alloc Mem Fail.");
        return;
    }


   PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
               sizeof(NAS_LOG_USIMM_API_FDN_QUERY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_FDN_QUERY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_FDN_QUERY;

    pstMsg->enApiType                   = enApiType;
    pstMsg->ulUsimState                 = ulUsimState;
    pstMsg->ulCsimState                 = ulCsimState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogUsimmApiGetPinRemainTime(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    USIMM_PIN_REMAIN_STRU              *pstRemainTime
)
{
    NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiGetPinRemainTime:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pstRemainTime)
    {
        PS_MEM_CPY(&(pstMsg->stRemainTime), pstRemainTime, sizeof(USIMM_PIN_REMAIN_STRU));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogPihApiRegUsimCardStatusInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulRegPid
)
{
    NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPihApiRegUsimCardStatusInd:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRegPID                    = ulRegPid;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogPihApiDeregUsimCardStatusInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDeregId
)
{
    NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPihApiDeregUsimCardStatusInd:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PIH_API_DEREG_USIM_CARD_STATUS_IND;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRegPID                    = ulDeregId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogPihApiRegCardRefreshInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulRegId
)
{
    NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU              *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPihApiRegCardRefreshInd:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PIH_API_REG_CARD_REFRESH_IND;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRegPID                    = ulRegId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogPihApiDeregCardRefreshInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDeregPID
)
{
    NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPihApiDeregCardRefreshInd:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PIH_API_DEREG_CARD_REFRESH_IND;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;
    pstMsg->ulDeregPID                  = ulDeregPID;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogPbApiGetEccNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_ECC_DATA_STRU                *pstEccData
)
{
    NAS_LOG_PB_API_GET_ECC_NUMBER_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_PB_API_GET_ECC_NUMBER_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PB_API_GET_ECC_NUMBER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPbApiGetEccNumber:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_PB_API_GET_ECC_NUMBER_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PB_API_GET_ECC_NUMBER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PB_API_GET_ECC_NUM;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pstEccData)
    {
        PS_MEM_CPY(&(pstMsg->stEccData), pstEccData, sizeof(SI_PB_ECC_DATA_STRU));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogPbApiGetXeccNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_ECC_DATA_STRU                *pstEccData
)
{
    NAS_LOG_PB_API_GET_XECC_NUMBER_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_PB_API_GET_XECC_NUMBER_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PB_API_GET_XECC_NUMBER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPbApiGetEccNumber:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                 sizeof(NAS_LOG_PB_API_GET_XECC_NUMBER_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PB_API_GET_XECC_NUMBER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PB_API_GET_XECC_NUM;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pstEccData)
    {
        PS_MEM_CPY(&(pstMsg->stEccData), pstEccData, sizeof(SI_PB_ECC_DATA_STRU));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}





VOS_VOID  NAS_LogPbApiFdnNumCheck(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_FDN_NUM_STRU                 *pstFdnNum
)
{
    NAS_LOG_PB_API_FDN_NUM_CHECK_STRU *pstMsg = VOS_NULL_PTR;


    pstMsg = (NAS_LOG_PB_API_FDN_NUM_CHECK_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PB_API_FDN_NUM_CHECK_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPbApiFdnNumCheck:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_PB_API_FDN_NUM_CHECK_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PB_API_FDN_NUM_CHECK_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PB_API_FDN_NUM_CHECK;

    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRslt                      = ulRslt;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pstFdnNum)
    {
        PS_MEM_CPY(&(pstMsg->stFdnNum), pstFdnNum, sizeof(pstMsg->stFdnNum));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}




VOS_VOID  NAS_LogStkApiEnvelopRspDecode(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogStkApiEnvelopRspDecode:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_STK_API_ENVELOP_RSP_DECODE;

    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRslt                      = ulRslt;

    if (VOS_NULL_PTR != pstRspData)
    {
        pstMsg->enEnvelopeType                  = pstRspData->EnvelopeType;
        pstMsg->stCallCtrlRslt.OP_SepcialData   = pstRspData->uResp.CallCtrlRsp.OP_SepcialData;
        pstMsg->stCallCtrlRslt.OP_Alaph         = pstRspData->uResp.CallCtrlRsp.OP_Alaph;
        pstMsg->stCallCtrlRslt.OP_BCRepInd      = pstRspData->uResp.CallCtrlRsp.OP_BCRepInd;
        pstMsg->stCallCtrlRslt.OP_CCP1          = pstRspData->uResp.CallCtrlRsp.OP_CCP1;
        pstMsg->stCallCtrlRslt.OP_CCP2          = pstRspData->uResp.CallCtrlRsp.OP_CCP2;
        pstMsg->stCallCtrlRslt.OP_SubAddr       = pstRspData->uResp.CallCtrlRsp.OP_SubAddr;

        if ((VOS_NULL_PTR != pstRspData->uResp.CallCtrlRsp.SpecialData.pValue)
         && (VOS_TRUE == pstRspData->uResp.CallCtrlRsp.OP_SepcialData))
        {
            pstMsg->stCallCtrlRslt.stSpecialData.ucTag  = pstRspData->uResp.CallCtrlRsp.SpecialData.ucTag;
            pstMsg->stCallCtrlRslt.stSpecialData.ucLen  = pstRspData->uResp.CallCtrlRsp.SpecialData.ucLen;

            PS_MEM_CPY(pstMsg->stCallCtrlRslt.stSpecialData.aucSpecialData, pstRspData->uResp.CallCtrlRsp.SpecialData.pValue, pstRspData->uResp.CallCtrlRsp.SpecialData.ucLen);
        }
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogStkApiEnvelopReqCode(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                          *pucEvent,
    VOS_UINT32                          ulDataLen,
    VOS_UINT32                          ulOffSet
)
{
    NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogStkApiEnvelopRspDecode:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_STK_API_ENVELOP_DOWN_CODE;
    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRslt                      = ulRslt;
    pstMsg->ulDataLen                   = ulDataLen;
    pstMsg->ulOffSet                    = ulOffSet;
    PS_MEM_CPY(pstMsg->aucEvent, pucEvent, 256);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}



VOS_VOID  NAS_LogStkApiEnvelopRspDataFree(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstEnvelopeRsp
)
{
    NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogStkApiEnvelopRspDataFree:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE;

    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if ( VOS_NULL_PTR != pstEnvelopeRsp)
    {
        PS_MEM_CPY(&pstMsg->stEvelopRsp, pstEnvelopeRsp, sizeof(pstMsg->stEvelopRsp));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}



VOS_VOID  NAS_LogStkApiEnvelopDownload(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
)
{
    NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogStkApiEnvelopRspDataFree:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_STK_API_ENVELOP_DOWNLOAD;

    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRslt                      = ulRslt;
    pstMsg->ulSendPara                  = ulSendPara;

    if (VOS_NULL_PTR != pstENStru)
    {
        pstMsg->enEnvelopeType              = pstENStru->enEnvelopeType;

        PS_MEM_CPY(&(pstMsg->stDeviceId), &(pstENStru->DeviceId), sizeof(SI_STK_DEVICE_IDENTITIES_STRU));
        PS_MEM_CPY(pstMsg->aucData, pstENStru->aucData, SI_STK_DATA_MAX_LEN);

        pstMsg->stCallCtrl.OP_BCRepInd      = pstENStru->uEnvelope.CallCtrl.OP_BCRepInd;
        pstMsg->stCallCtrl.OP_Capability1   = pstENStru->uEnvelope.CallCtrl.OP_Capability1;
        pstMsg->stCallCtrl.OP_LocInfo       = pstENStru->uEnvelope.CallCtrl.OP_LocInfo;
        pstMsg->stCallCtrl.OP_Subaddr       = pstENStru->uEnvelope.CallCtrl.OP_Subaddr;
        pstMsg->stCallCtrl.OP_Capability2   = pstENStru->uEnvelope.CallCtrl.OP_Capability2;
        pstMsg->stCallCtrl.OP_SepcialData   = pstENStru->uEnvelope.CallCtrl.OP_SepcialData;

        if ((VOS_NULL_PTR != pstENStru->uEnvelope.CallCtrl.SpecialData.pValue)
         && (VOS_TRUE == pstENStru->uEnvelope.CallCtrl.OP_SepcialData))
        {
            pstMsg->stCallCtrl.stSpecialData.ucTag  = pstENStru->uEnvelope.CallCtrl.SpecialData.ucTag;
            pstMsg->stCallCtrl.stSpecialData.ucLen  = pstENStru->uEnvelope.CallCtrl.SpecialData.ucLen;
            PS_MEM_CPY(pstMsg->stCallCtrl.stSpecialData.aucSpecialData, pstENStru->uEnvelope.CallCtrl.SpecialData.pValue, pstENStru->uEnvelope.CallCtrl.SpecialData.ucLen);
        }

        if ((VOS_NULL_PTR != pstENStru->uEnvelope.CallCtrl.LocInfo.pucATSLI)
         && (VOS_TRUE == pstENStru->uEnvelope.CallCtrl.OP_LocInfo)
         && (pstENStru->uEnvelope.CallCtrl.LocInfo.ulLen <= NAS_MO_CTRL_LAI_LEN))
        {
            pstMsg->stCallCtrl.stLocInfo.ulLen  = pstENStru->uEnvelope.CallCtrl.LocInfo.ulLen;
            PS_MEM_CPY(pstMsg->stCallCtrl.stLocInfo.aucATSLI, pstENStru->uEnvelope.CallCtrl.LocInfo.pucATSLI, pstENStru->uEnvelope.CallCtrl.LocInfo.ulLen);
        }
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}



VOS_VOID  NAS_LogUsimmApiDeactiveCardReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
)
{
    NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                sizeof(NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogUsimmApiDeactiveCardReq:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ;

    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRslt                      = ulRslt;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogSTKApiCCResultInd(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    NAS_LOG_STK_API_CC_RESULT_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_STK_API_CC_RESULT_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                sizeof(NAS_LOG_STK_API_CC_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogSTKApiCCResultInd:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_STK_API_CC_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_STK_API_CC_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_STK_API_CC_RESULT_IND;

    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pstRspData)
    {
        PS_MEM_CPY(&(pstMsg->stRspData), pstRspData, sizeof(pstMsg->stRspData));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID  NAS_LogSTKApiSMSCtrlResultInd(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                sizeof(NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogSTKApiSMSCtrlResultInd:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_STK_API_SMS_CTRL_RESULT_IND;

    pstMsg->enApiType                   = enApiType;

    /* 空指针保护 */
    if (VOS_NULL_PTR != pstRspData)
    {
        PS_MEM_CPY(&(pstMsg->stRspData), pstRspData, sizeof(pstMsg->stRspData));
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


VOS_VOID NAS_LogVsimIsRequireVsimCtrl(
    VOS_UINT32                          ulVsimModem,
    VOS_UINT8                           ucVsimCtrlFlg
)
{
    NAS_LOG_VSIM_CTRL_INFO_STRU         stVsimCtrl;

    PS_MEM_SET(&stVsimCtrl, 0, sizeof(stVsimCtrl));

    stVsimCtrl.MsgHeader.ulMsgName          = NAS_LOG_VSIM_CTRL_INFO;
    stVsimCtrl.MsgHeader.ulSenderCpuId      = VOS_LOCAL_CPUID;
    stVsimCtrl.MsgHeader.ulSenderPid        = WUEPS_PID_TAF;
    stVsimCtrl.MsgHeader.ulReceiverCpuId    = VOS_LOCAL_CPUID;
    stVsimCtrl.MsgHeader.ulReceiverPid      = WUEPS_PID_USIM;
    stVsimCtrl.MsgHeader.ulLength           = sizeof(stVsimCtrl) - VOS_MSG_HEAD_LENGTH;

    stVsimCtrl.ulVsimModem                  = ulVsimModem;
    stVsimCtrl.ucVsimCtrlFlg                = ucVsimCtrlFlg;

    DIAG_TraceReport(&stVsimCtrl);

    return;
}



VOS_VOID  NAS_LogPbApiQryEcallNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_STORATE_TYPE                  enPbType,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
)
{
    NAS_LOG_PB_API_QRY_ECALL_NUM_STRU *pstMsg = VOS_NULL_PTR;


    pstMsg = (NAS_LOG_PB_API_QRY_ECALL_NUM_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(NAS_LOG_PB_API_QRY_ECALL_NUM_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "NAS_LogPbApiQryEcallNumber:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                   sizeof(NAS_LOG_PB_API_QRY_ECALL_NUM_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = MAPS_PB_PID;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LOG_PB_API_QRY_ECALL_NUM_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = NAS_LOG_PB_API_QRY_ECALL_NUM;

    pstMsg->enApiType                   = enApiType;
    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enPbType                    = enPbType;
    pstMsg->ucListLen                   = ucListLen;

    /* 空指针保护 */
    if ((VOS_NULL_PTR != pucList)
     && (0            != ucListLen))
    {
        PS_MEM_CPY(&(pstMsg->aucList[0]), pucList, ucListLen);
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}

/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

