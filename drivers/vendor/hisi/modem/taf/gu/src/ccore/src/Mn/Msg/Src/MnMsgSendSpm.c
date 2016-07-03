

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnMsgInclude.h"
#include "MnMsgSendSpm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_SENDSPM_C

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 函数实现
*****************************************************************************/

VOS_VOID TAF_MSG_SendSpmSmmaInd(VOS_VOID)
{
    TAF_SPM_SMMA_IND_STRU              *pstSmaMsg = VOS_NULL_PTR;

    pstSmaMsg = (TAF_SPM_SMMA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(TAF_SPM_SMMA_IND_STRU));

    if (VOS_NULL_PTR == pstSmaMsg)
    {
        MN_WARN_LOG("TAF_MSG_SendSpmSmmaInd:ERROR: VOS_AllocMsg fails");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSmaMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(TAF_SPM_SMMA_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    
    pstSmaMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSmaMsg->ulSenderPid          = WUEPS_PID_TAF;
    pstSmaMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSmaMsg->ulReceiverPid        = WUEPS_PID_TAF;
    pstSmaMsg->ulMsgId              = ID_TAF_SPM_SMMA_IND;
    pstSmaMsg->clientId             = INTERNAL_CLIENT_ID_SMMA;    

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmaMsg ) )
    {
        MN_WARN_LOG( "TAF_MSG_SendSpmSmmaInd:WARNING:SEND ID_TAF_SPM_SMMA_IND msg FAIL!" );
    }

    return;
}


VOS_VOID TAF_MSG_SpmMsgReportInd(
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU    *pstSubmitRptEvt,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,  
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enSignallingType
)
{
    TAF_SPM_MSG_REPORT_IND_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_MSG_REPORT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                         sizeof(TAF_SPM_MSG_REPORT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_WARN_LOG("TAF_MSG_SpmMsgReportInd:ERROR: message alloctiaon fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 
               0, 
               sizeof(TAF_SPM_MSG_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid          = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid        = WUEPS_PID_TAF;
    pstMsg->ulMsgId              = ID_TAF_SPM_MSG_REPORT_IND;

    pstMsg->usClientId           = pstMoEntity->clientId;
    pstMsg->ucOpId               = pstMoEntity->opId;

    pstMsg->enSignallingType     = enSignallingType;
    pstMsg->ucReportFlag         = (VOS_UINT8)(pstMoEntity->bReportFlag);
    pstMsg->enSmsMoType          = pstMoEntity->enSmsMoType;
    pstMsg->ucBcOpId             = MN_MSG_GetBCopId();
    
    PS_MEM_CPY(&(pstMsg->stRptEvtInfo), pstSubmitRptEvt, sizeof(MN_MSG_SUBMIT_RPT_EVT_INFO_STRU));
    
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_WARN_LOG( "TAF_MSG_SpmMsgReportInd:WARNING:SEND ID_TAF_SPM_MSG_REPORT_IND msg FAIL!" );
    }

    return;
}
#endif


VOS_VOID TAF_MSG_SendSpmMsgCheckResultInd(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MSG_ERROR_ENUM_UINT32           enRslt
)
{
    TAF_SPM_MSG_CHECK_RESULT_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_MSG_CHECK_RESULT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                         sizeof(TAF_SPM_MSG_CHECK_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_WARN_LOG("TAF_MSG_SendSpmMsgCheckResultInd:ERROR: message alloctiaon fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_SPM_MSG_CHECK_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid          = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid        = WUEPS_PID_TAF;
    pstMsg->ulMsgId              = ID_TAF_SPM_MSG_CHECK_RESULT_IND;

    pstMsg->usClientId           = usClientId;
    pstMsg->ucOpId               = ucOpId;
    pstMsg->enRslt               = enRslt;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_WARN_LOG( "TAF_MSG_SpmMsgReportInd:WARNING:SEND ID_TAF_SPM_MSG_REPORT_IND msg FAIL!" );
    }

    return;
}







#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

