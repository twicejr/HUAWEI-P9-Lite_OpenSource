


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#include "CnasEhsmMntn.h"
#include "Nas_Mem.h"

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/



VOS_VOID CNAS_EHSM_MNTN_LogFsmInfo(
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState
)
{
    CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_EHSM,
                             sizeof(CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_MNTN_LogFsmInfo: Alloc Memory Failed!");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_EHSM;
    pstMsg->ulLength        = sizeof(CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_EHSM_MNTN_LOG_FSM_INFO_IND;
    pstMsg->ulCurFsmId      = ulFsmId;
    pstMsg->ulCurFsmState   = ulFsmState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_EHSM, pstMsg);

    return;
}




VOS_VOID  CNAS_EHSM_MNTN_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU                 *pstBufferMsg = VOS_NULL_PTR;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU                          *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_EHSM,
                             sizeof(CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_MNTN_LogBufferQueueMsg: Alloc Memory Failed!");
        return;
    }

    NAS_MEM_SET_S(pstBufferMsg, sizeof(CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU), 0, sizeof(CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU));

    pstMsgQueue                               = CNAS_EHSM_GetCacheMsgAddr();
    pstBufferMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid     = UEPS_PID_EHSM;
    pstBufferMsg->ulReceiverPid   = UEPS_PID_EHSM;
    pstBufferMsg->ulLength        = sizeof(CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId         = ID_CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg       = ulFullFlg;
    NAS_MEM_CPY_S(&(pstBufferMsg->stMsgQueue), sizeof(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(UEPS_PID_EHSM, pstBufferMsg);

    return;

}




VOS_VOID CNAS_EHSM_MNTN_LogCtxInfo(VOS_VOID)
{
    CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU   *pstMsg      = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx    = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();

    pstMsg = (CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_EHSM,
                             sizeof(CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_MNTN_LogCtxInfo: Alloc Memory Failed!");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_EHSM;
    pstMsg->ulLength        = sizeof(CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_EHSM_MNTN_LOG_CTX_INFO_IND;

    pstMsg->enEhrpdState    = pstEhsmCtx->enEhrpdState;
    pstMsg->enSessionType   = pstEhsmCtx->enSessionType;
    pstMsg->ulAirLinkExist  = pstEhsmCtx->ulAirLinkExist;

    pstMsg->stRetryConnEstInfo.ulExpireTimerLen  = pstEhsmCtx->stRetryCtrlInfo.stRetryConnEstInfo.ulExpireTimerLen;
    pstMsg->stRetryConnEstInfo.usMaxNoOfRetry    = pstEhsmCtx->stRetryCtrlInfo.stRetryConnEstInfo.usMaxNoOfRetry;
    pstMsg->stRetryPdnSetupInfo.ulExpireTimerLen = pstEhsmCtx->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen;
    pstMsg->stRetryPdnSetupInfo.usMaxNoOfRetry   = pstEhsmCtx->stRetryCtrlInfo.stRetryPdnSetupInfo.usMaxNoOfRetry;

    for (i = 0; i < CNAS_EHSM_MAX_PDN_NUM; i++)
    {
        /* fill Local and LTE PDN details from context */
        pstMsg->astLocalPdnBearInfo[i].enAttachType  = pstEhsmCtx->astLocalPdnBearInfo[i].enAttachType;
        pstMsg->astLocalPdnBearInfo[i].enPdnType     = pstEhsmCtx->astLocalPdnBearInfo[i].enPdnType;
        pstMsg->astLocalPdnBearInfo[i].ucCid         = pstEhsmCtx->astLocalPdnBearInfo[i].ucCid;
        pstMsg->astLocalPdnBearInfo[i].ucInUsed      = pstEhsmCtx->astLocalPdnBearInfo[i].ucInUsed;
        pstMsg->astLocalPdnBearInfo[i].ucIsPdnActive = pstEhsmCtx->astLocalPdnBearInfo[i].ucIsPdnActive;
        pstMsg->astLocalPdnBearInfo[i].ucPdnId       = pstEhsmCtx->astLocalPdnBearInfo[i].ucPdnId;
        pstMsg->astLocalPdnBearInfo[i].ulEpsbId      = pstEhsmCtx->astLocalPdnBearInfo[i].ulEpsbId;

        pstMsg->astLtePdnBearInfo[i].enPdnType       = pstEhsmCtx->astLtePdnBearInfo[i].enPdnType;
        pstMsg->astLtePdnBearInfo[i].ucCid           = pstEhsmCtx->astLtePdnBearInfo[i].ucCid;
        pstMsg->astLtePdnBearInfo[i].ucInUsed        = pstEhsmCtx->astLtePdnBearInfo[i].ucInUsed;
        pstMsg->astLtePdnBearInfo[i].ulEpsbId        = pstEhsmCtx->astLtePdnBearInfo[i].ulEpsbId;
    }


    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_EHSM, pstMsg);

    return;
}



#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




