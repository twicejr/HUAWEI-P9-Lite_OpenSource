


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#include "NasMsccMntn.h"
#include "PsCommonDef.h"

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_MNTN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/



VOS_VOID NAS_MSCC_MNTN_LogFsmInfo(
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState
)
{
    NAS_MSCC_MNTN_LOG_FSM_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MSCC_MNTN_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                             sizeof(NAS_MSCC_MNTN_LOG_FSM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_FSM_INFO_IND;
    pstMsg->ulCurFsmId      = ulFsmId;
    pstMsg->ulCurFsmState   = ulFsmState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}




VOS_VOID  NAS_MSCC_MNTN_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU  *pstBufferMsg = VOS_NULL_PTR;
    NAS_MSCC_CACHE_MSG_QUEUE_STRU           *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                             sizeof(NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogBufferQueueMsg: Alloc Memory Failed!");
        return;
    }

    PS_MEM_SET(pstBufferMsg, 0, sizeof(NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU));

    pstMsgQueue                       = NAS_MSCC_GetCacheMsgAddr();
    pstBufferMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid         = UEPS_PID_MSCC;
    pstBufferMsg->ulReceiverPid       = UEPS_PID_MSCC;
    pstBufferMsg->ulLength            = sizeof(NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId             = ID_NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg           = ulFullFlg;
    PS_MEM_CPY(&(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstBufferMsg);

    return;

}




VOS_VOID  NAS_MSCC_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;

    pucData = (VOS_UINT8 *)PS_MEM_ALLOC(ulModuleId, ulLength);

    if (VOS_NULL_PTR == pucData)
    {
        NAS_ERROR_LOG(ulModuleId, "NAS_MSCC_MNTN_TraceIntMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    /* Copy the input message to the temp pucData */
    PS_MEM_CPY(pucData, pMsg, ulLength);

    /* Trace the message */
    DIAG_TraceReport(pucData);

    PS_MEM_FREE(ulModuleId, pucData);

    return;

}



VOS_VOID NAS_MSCC_MNTN_LogMlplParseRslt(
    NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32                   enSource,
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                    enRslt
)
{
    NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                        sizeof(NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_IND;
    pstMsg->enSource        = enSource;
    pstMsg->enRslt          = enRslt;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);
}



VOS_VOID NAS_MSCC_MNTN_LogMsplParseRslt(
    NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32                   enSource,
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                    enRslt
)
{
    NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                        sizeof(NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_IND;
    pstMsg->enSource        = enSource;
    pstMsg->enRslt          = enRslt;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);
}



VOS_VOID NAS_MSCC_MNTN_LogMlplMsplMatchRslt(
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU      *pstLogMatchRsltInput
)
{
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                        sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_IND;

    pstMsg->enMatchPurpose  = pstLogMatchRsltInput->enMatchPurpose;
    pstMsg->enSysRat        = pstLogMatchRsltInput->enSysRat;

    switch (pstMsg->enSysRat)
    {
        case NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP:
            PS_MEM_CPY(&(pstMsg->unInputSysInfo.st3gppInfo), pstLogMatchRsltInput->pvSysInfo,
                       sizeof(NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU));
            break;

        case NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X:
            PS_MEM_CPY(&(pstMsg->unInputSysInfo.st1xInfo), pstLogMatchRsltInput->pvSysInfo,
                       sizeof(NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU));
            break;

        case NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD:
            PS_MEM_CPY(&(pstMsg->unInputSysInfo.stHrpdInfo), pstLogMatchRsltInput->pvSysInfo,
                       sizeof(NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU));
            break;

        default:
            break;
    }

    pstMsg->ucMlplMatchRslt    = pstLogMatchRsltInput->ucMlplMatchRslt;
    pstMsg->enMlplMatchLvl     = pstLogMatchRsltInput->enMlplMatchLvl;
    pstMsg->ucIsUseDfltMlpLRec = pstLogMatchRsltInput->ucIsUseDfltMlpLRec;
    pstMsg->ucMatchedMsplIndex = pstLogMatchRsltInput->ucMatchedMsplIndex;
    pstMsg->ucMsplMatchRslt    = pstLogMatchRsltInput->ucMsplMatchRslt;
    pstMsg->ucMatchedMsplRecId = pstLogMatchRsltInput->ucMatchedMsplRecId;

    pstMsg->ucCurSysTypeNotExistInMspl = pstLogMatchRsltInput->ucCurSysTypeNotExistInMspl;

    if (VOS_NULL_PTR != pstLogMatchRsltInput->pstMsplSysList)
    {
        PS_MEM_CPY(&(pstMsg->stMsplSysList), pstLogMatchRsltInput->pstMsplSysList,
                   sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));
    }

    pstMsg->ulBsrTimerLen = pstLogMatchRsltInput->ulBsrTimerLen;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);
}




VOS_VOID NAS_MSCC_MNTN_LogMsplHeaderInfo(
    NAS_MSCC_MSPL_HEADER_STRU          *pstMsplHeaderInfo
)
{
    NAS_MSCC_MNTN_MSPL_HEADER_STRU     *pstMsplHdr;
    pstMsplHdr = (NAS_MSCC_MNTN_MSPL_HEADER_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_MSPL_HEADER_STRU));
    if (VOS_NULL_PTR == pstMsplHdr)
    {
        return;
    }

    PS_MEM_SET(pstMsplHdr, 0, sizeof(NAS_MSCC_MNTN_MSPL_HEADER_STRU));

    pstMsplHdr->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMsplHdr->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMsplHdr->ulSenderPid          = UEPS_PID_MSCC;
    pstMsplHdr->ulReceiverPid        = UEPS_PID_MSCC;
    pstMsplHdr->ulLength             = sizeof(NAS_MSCC_MNTN_MSPL_HEADER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsplHdr->enMsgId              = ID_NAS_MSCC_MNTN_LOG_MSPL_MSPL_HDR_INFO_IND;

    PS_MEM_CPY(&(pstMsplHdr->stMsplHdrInfo), pstMsplHeaderInfo, sizeof(NAS_MSCC_MSPL_HEADER_STRU));

    DIAG_TraceReport(pstMsplHdr);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsplHdr);
}


VOS_VOID NAS_MSCC_MNTN_GetMsplRec(
    NAS_MSCC_MSPL_REC_STRU             *pDesMsplRecList,
    NAS_MSCC_MSPL_REC_STRU             *pSrcMsplRecList
)
{
    VOS_UINT16                          ucIndex;

    for (ucIndex = 0; ucIndex < NAS_MSCC_MNTN_MSPL_MAX_NUM_MSPL_REC; ucIndex++)
    {
        PS_MEM_CPY(&pDesMsplRecList[ucIndex],
                   &pSrcMsplRecList[ucIndex],
                   sizeof(NAS_MSCC_MSPL_REC_STRU));
    }

    return;
}



VOS_VOID NAS_MSCC_MNTN_LogMlplHeaderInfo(
    NAS_MSCC_MLPL_HEADER_STRU          *pstMlplHeaderInfo
)
{
    NAS_MSCC_MNTN_MLPL_HEADER_STRU     *pstMlplHdr;
    pstMlplHdr = (NAS_MSCC_MNTN_MLPL_HEADER_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                           sizeof(NAS_MSCC_MNTN_MLPL_HEADER_STRU));
    if (VOS_NULL_PTR == pstMlplHdr)
    {
        return;
    }

    PS_MEM_SET(pstMlplHdr, 0, sizeof(NAS_MSCC_MNTN_MLPL_HEADER_STRU));

    pstMlplHdr->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMlplHdr->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMlplHdr->ulSenderPid          = UEPS_PID_MSCC;
    pstMlplHdr->ulReceiverPid        = UEPS_PID_MSCC;
    pstMlplHdr->ulLength             = sizeof(NAS_MSCC_MNTN_MLPL_HEADER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMlplHdr->enMsgId              = ID_NAS_MSCC_MNTN_LOG_MLPL_MLPL_HDR_INFO_IND;

    PS_MEM_CPY(&(pstMlplHdr->stMlplHdrInfo), pstMlplHeaderInfo, sizeof(NAS_MSCC_MLPL_HEADER_STRU));

    DIAG_TraceReport(pstMlplHdr);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMlplHdr);

    return;
}



VOS_VOID NAS_MSCC_MNTN_GetMlplSysLocTag(
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pDesSysLocTag,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pSrcSysLocTag
)
{
    VOS_UINT16                          ucIndex;

    for (ucIndex = 0; ucIndex < NAS_MSCC_MNTN_MLPL_MAX_NUM_SYS_LOC_TAG; ucIndex++)
    {
        PS_MEM_CPY(&pDesSysLocTag[ucIndex],
                   &pSrcSysLocTag[ucIndex],
                   sizeof(NAS_MSCC_MLPL_SYS_LOC_TAG_STRU));
    }

    return;
}



VOS_VOID NAS_MSCC_MNTN_LogMsplInfo(
    NAS_MSCC_MSPL_STRU                 *pstMsplInfo
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    NAS_MSCC_MNTN_MSPL_ID_LIST_STRU    *pstMsplIdList;

    NAS_MSCC_MNTN_LogMsplHeaderInfo(&pstMsplInfo->stMsplHdr);

    pstMsplIdList = (NAS_MSCC_MNTN_MSPL_ID_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_MSPL_ID_LIST_STRU));
    if (VOS_NULL_PTR == pstMsplIdList)
    {
        return;
    }

    PS_MEM_SET(pstMsplIdList, 0, sizeof(NAS_MSCC_MNTN_MSPL_ID_LIST_STRU));

    pstMsplIdList->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMsplIdList->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMsplIdList->ulSenderPid          = UEPS_PID_MSCC;
    pstMsplIdList->ulReceiverPid        = UEPS_PID_MSCC;
    pstMsplIdList->ulLength             = sizeof(NAS_MSCC_MNTN_MSPL_ID_LIST_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsplIdList->enMsgId              = ID_NAS_MSCC_MNTN_LOG_MSPL_MSPL_ID_INFO_IND;

    j = 0;
    for (i = 0; i < pstMsplInfo->stMsplHdr.ucNumMsplId; i++)
    {
        pstMsplIdList->astMsplIdList[j].ucIsMsplIdValid = pstMsplInfo->apstMsplId[i]->ucIsMsplIdValid;
        pstMsplIdList->astMsplIdList[j].ucMsplId        = pstMsplInfo->apstMsplId[i]->ucMsplId;
        pstMsplIdList->astMsplIdList[j].ucNumMsplRec    = pstMsplInfo->apstMsplId[i]->ucNumMsplRec;

        NAS_MSCC_MNTN_GetMsplRec(pstMsplIdList->astMsplIdList[j].astMsplRec,
                                        pstMsplInfo->apstMsplId[i]->astMsplRec);

        j++;
        if (0 == (j % NAS_MSCC_MNTN_MAX_NUM_MSPL_ID))
        {
            pstMsplIdList->ulNumMsplId = NAS_MSCC_MNTN_MAX_NUM_MSPL_ID;

            DIAG_TraceReport(pstMsplIdList);

            j = 0;
            PS_MEM_SET(pstMsplIdList->astMsplIdList,
                       0,
                       sizeof(NAS_MSCC_MNTN_MSPL_ID_STRU) * NAS_MSCC_MNTN_MAX_NUM_MSPL_ID);
        }
    }

    if (0 != j)
    {
        pstMsplIdList->ulNumMsplId = j;

        DIAG_TraceReport(pstMsplIdList);
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsplIdList);

    return;

}



VOS_VOID NAS_MSCC_MNTN_LogMlplInfo(
    NAS_MSCC_MLPL_STRU                 *pstMlplInfo
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU *pstMlplRecList;


    NAS_MSCC_MNTN_LogMlplHeaderInfo(&pstMlplInfo->stMlplHdr);

    pstMlplRecList = (NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU));
    if (VOS_NULL_PTR == pstMlplRecList)
    {
        return;
    }

    PS_MEM_SET(pstMlplRecList, 0, sizeof(NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU));

    pstMlplRecList->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMlplRecList->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMlplRecList->ulSenderPid          = UEPS_PID_MSCC;
    pstMlplRecList->ulReceiverPid        = UEPS_PID_MSCC;
    pstMlplRecList->ulLength             = sizeof(NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMlplRecList->enMsgId              = ID_NAS_MSCC_MNTN_LOG_MLPL_MLPL_REC_INFO_IND;

    j = 0;
    for (i = 0; i < pstMlplInfo->stMlplHdr.ucNumMlplRec; i++)
    {
        pstMlplRecList->astMlplRecList[j].ucIsRecValid   = pstMlplInfo->apstMlplRec[i]->ucIsRecValid;
        pstMlplRecList->astMlplRecList[j].ucLocParamType = pstMlplInfo->apstMlplRec[i]->ucLocParamType;
        pstMlplRecList->astMlplRecList[j].ucMsplIndex    = pstMlplInfo->apstMlplRec[i]->ucMsplIndex;
        pstMlplRecList->astMlplRecList[j].stLocParamVal.usMcc = pstMlplInfo->apstMlplRec[i]->stLocParamVal.usMcc;
        pstMlplRecList->astMlplRecList[j].stLocParamVal.usMnc = pstMlplInfo->apstMlplRec[i]->stLocParamVal.usMnc;
        pstMlplRecList->astMlplRecList[j].stLocParamVal.ucNumSysLocTag = pstMlplInfo->apstMlplRec[i]->stLocParamVal.ucNumSysLocTag;

        NAS_MSCC_MNTN_GetMlplSysLocTag(pstMlplRecList->astMlplRecList[j].stLocParamVal.astSysLocTag,
                                        pstMlplInfo->apstMlplRec[i]->stLocParamVal.astSysLocTag);

        j++;
        if (0 == (j % NAS_MSCC_MNTN_MAX_NUM_MLPL_REC))
        {
            pstMlplRecList->ulNumMlplRec = NAS_MSCC_MNTN_MAX_NUM_MLPL_REC;

            DIAG_TraceReport(pstMlplRecList);

            j = 0;
            PS_MEM_SET(pstMlplRecList->astMlplRecList,
                       0,
                       sizeof(NAS_MSCC_MNTN_MLPL_RECORD_STRU) * NAS_MSCC_MNTN_MAX_NUM_MLPL_REC);
        }
    }

    if (0 != j)
    {
        pstMlplRecList->ulNumMlplRec = j;

        DIAG_TraceReport(pstMlplRecList);
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstMlplRecList);

    return;

}



VOS_VOID NAS_MSCC_MNTN_LogMlplMsplCrcChkRslt(
    NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32                     enCrcCause,
    NAS_MSCC_MLPL_MSPL_PARSE_TYPE_ENUM_UINT8                enType
)
{
    NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU                  *pstCrcRsltMsg;

    pstCrcRsltMsg = (NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU));
    if (VOS_NULL_PTR == pstCrcRsltMsg)
    {
        return;
    }

    pstCrcRsltMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstCrcRsltMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstCrcRsltMsg->ulSenderPid          = UEPS_PID_MSCC;
    pstCrcRsltMsg->ulReceiverPid        = UEPS_PID_MSCC;
    pstCrcRsltMsg->ulLength             = sizeof(NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCrcRsltMsg->enCrcRslt            = enCrcCause;

    if (NAS_MSCC_MLPL_MSPL_PARSE_TYPE_MLPL == enType)
    {
        pstCrcRsltMsg->enMsgId = ID_NAS_MSCC_MNTN_LOG_MLPL_CRC_CHK_RSLT_IND;
    }
    else
    {
        pstCrcRsltMsg->enMsgId = ID_NAS_MSCC_MNTN_LOG_MSPL_CRC_CHK_RSLT_IND;
    }

    DIAG_TraceReport(pstCrcRsltMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstCrcRsltMsg);

    return;

}

/*****************************************************************************
Function Name   :   NAS_MSCC_MNTN_LogDiscardServStaInfo
Description     :   勾包在BSR流程中状态上报屏蔽消息
Input parameters:
Outout parameters:
Return Value    :
Modify History:
    1)  Date    :   2014-04-16
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_MNTN_LogDiscardServStaInfo(
    NAS_MSCC_DISCARD_SERV_STA_ENUM_UINT8                    enDiscardServSta
)
{
    NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                        sizeof(NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU));

    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid         = UEPS_PID_MSCC;
    pstMsg->ulLength            = sizeof(NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_IND;
    pstMsg->enDiscardServSta    = enDiscardServSta;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}


VOS_VOID NAS_MSCC_MNTN_LogBsrCtrlInfo(
    NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU   *pstInCtrlInfo
)
{
    NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU                    *pstBsrCtrlInfo;

    pstBsrCtrlInfo = (NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU));
    if (VOS_NULL_PTR == pstBsrCtrlInfo)
    {
        return;
    }

    PS_MEM_SET(pstBsrCtrlInfo, 0, sizeof(NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU));

    pstBsrCtrlInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBsrCtrlInfo->ulReceiverPid   = UEPS_PID_MSCC;
    pstBsrCtrlInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBsrCtrlInfo->ulSenderPid     = UEPS_PID_MSCC;
    pstBsrCtrlInfo->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBsrCtrlInfo->enMsgId         = ID_NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_IND;

    PS_MEM_CPY(&(pstBsrCtrlInfo->stBsrCtrlInfo),
               pstInCtrlInfo,
               sizeof(NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU));

    DIAG_TraceReport(pstBsrCtrlInfo);

    PS_MEM_FREE(UEPS_PID_MSCC, pstBsrCtrlInfo);

    return;

}




VOS_VOID NAS_MSCC_MNTN_LogNvimMmssCfgInfo(
    NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU                  *pstMmssNvimCfgInfo
)
{
    NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU                   *pstMmssSysAcqCfg = VOS_NULL_PTR;

    pstMmssSysAcqCfg = (NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU));
    if (VOS_NULL_PTR == pstMmssSysAcqCfg)
    {
        return;
    }

    PS_MEM_SET(pstMmssSysAcqCfg, 0, sizeof(NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU));

    pstMmssSysAcqCfg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmssSysAcqCfg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMmssSysAcqCfg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmssSysAcqCfg->ulSenderPid     = UEPS_PID_MSCC;
    pstMmssSysAcqCfg->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmssSysAcqCfg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_IND;

    PS_MEM_CPY(&(pstMmssSysAcqCfg->stNvimMmssCfg),
               pstMmssNvimCfgInfo,
               sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU));

    DIAG_TraceReport(pstMmssSysAcqCfg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMmssSysAcqCfg);

    return;
}




VOS_VOID NAS_MSCC_MNTN_LogNvimMmssLastLocInfo(
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU                  *pstMmssNvimLastLocInfo
)
{
    NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU         *pstMmssLastLocInfo = VOS_NULL_PTR;

    pstMmssLastLocInfo = (NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                           sizeof(NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU));
    if (VOS_NULL_PTR == pstMmssLastLocInfo)
    {
        return;
    }

    PS_MEM_SET(pstMmssLastLocInfo, 0, sizeof(NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU));

    pstMmssLastLocInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmssLastLocInfo->ulReceiverPid   = UEPS_PID_MSCC;
    pstMmssLastLocInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmssLastLocInfo->ulSenderPid     = UEPS_PID_MSCC;
    pstMmssLastLocInfo->ulLength        = sizeof(NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmssLastLocInfo->enMsgId         = ID_NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_IND;

    PS_MEM_CPY(&(pstMmssLastLocInfo->stNvimLastLocInfo),
               pstMmssNvimLastLocInfo,
               sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU));

    DIAG_TraceReport(pstMmssLastLocInfo);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMmssLastLocInfo);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MSCC_LogReadNVInfo
 功能描述  : 勾取读取的NV信息上报 可维可测
 输入参数  : VOS_UINT16                          enNvItem,
             VOS_UINT16                          usNvDataLength,
             VOS_UINT32                          ulPid,
             VOS_UINT32                         *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
)
{
    NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU                *pstMsg;

    pstMsg = (NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                                         sizeof(NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU) + usNvDataLength - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulPid;
    pstMsg->stMsgHeader.ulReceiverPid   = ulPid;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH + usNvDataLength - 4;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND;
    pstMsg->enNvItem                    = enNvItem;
    pstMsg->usNvDataLength              = usNvDataLength;
    PS_MEM_CPY(pstMsg->aucNvInfo, pucData, usNvDataLength);


    DIAG_TraceReport((VOS_VOID *)pstMsg);


    PS_MEM_FREE(ulPid, pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo
 功能描述  : 将l1 main状态机相关信息勾包
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
VOS_VOID NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo(VOS_VOID)
{
    NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU         *pstMsg;

    pstMsg = (NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                          (sizeof(NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MMC_LogFsmL1MainCtxRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->ulLength        = sizeof(NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_FSM_L1_MAIN_CTX_RELATED_INFO;

    pstMsg->ulOosAvailableTimerCount    = NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main();
    pstMsg->ucCur1xSrvFullBandSrchCount = NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main();
    pstMsg->ucCur1xSrvHistorySrchCount  = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

    NAS_WARNING_LOG2(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo:ucCur1xSrvFullBandSrchCount= %d, ucCur1xSrvHistorySrchCount=%d",
                        pstMsg->ucCur1xSrvFullBandSrchCount, pstMsg->ucCur1xSrvHistorySrchCount);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo
 功能描述  : 增加对CL系统捕获策略相关信息勾包
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : W00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
VOS_VOID NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo(VOS_VOID)
{
    NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU                  *pstMsg = VOS_NULL_PTR;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU                     *pstPhaseOneInfo;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU                     *pstPhaseTwoInfo;

    pstMsg = (NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                          (sizeof(NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    pstPhaseOneInfo = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr();
    pstPhaseTwoInfo = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr();

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->ulLength        = sizeof(NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_NAS_MSCC_MNTN_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_IND;

    PS_MEM_CPY(&(pstMsg->stPhaseOnePatternCfg), pstPhaseOneInfo, sizeof(NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU));
    PS_MEM_CPY(&(pstMsg->stPhaseTwoPatternCfg), pstPhaseTwoInfo, sizeof(NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU));

    pstMsg->enCur1xServiceSysAcqPhaseNum  = NAS_MSCC_GetCur1xServiceSysAcqPhaseNum();

    NAS_WARNING_LOG2(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo:phase one total timer len= %d, phase one sleep timer len=%d",
                        pstMsg->stPhaseOnePatternCfg.usTotalTimeLen, pstMsg->stPhaseOnePatternCfg.usSleepTimeLen);

    NAS_WARNING_LOG2(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo:phase one history srch number= %d, phase one spec serch number=%d",
                        pstMsg->stPhaseOnePatternCfg.ucLteHistorySrchNum, pstMsg->stPhaseOnePatternCfg.ucLteFullBandSrchNum);

    NAS_WARNING_LOG2(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo:current sys acq phase number= %d, phase two sleep timer len=%d",
                        pstMsg->enCur1xServiceSysAcqPhaseNum, pstMsg->stPhaseTwoPatternCfg.usSleepTimeLen);

    NAS_WARNING_LOG2(UEPS_PID_MSCC, "NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo:phase two history srch number= %d, phase two spec serch number=%d",
                        pstMsg->stPhaseTwoPatternCfg.ucLteHistorySrchNum, pstMsg->stPhaseTwoPatternCfg.ucLteFullBandSrchNum);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}


/* 复位分析需要忽略的消息列表 */
/* MSCC收到的MMA发送的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgFromMmaTbl[]=
{
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_SIGN_REPORT_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_MODE_CHANGE_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_EOPLMN_SET_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_CDMACSQ_SET_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_CFPLMN_SET_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_CFPLMN_QUERY_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_SDT_CONNECTED_IND },
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_PREF_PLMN_SET_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_PREF_PLMN_QUERY_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_AUTO_RESEL_SET_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_HANDSET_INFO_QRY_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_PS_RAT_TYPE_NTF},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_SET_CSIDLIST_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_DPLMN_SET_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_CSG_LIST_SEARCH_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_CSG_LIST_ABORT_REQ},
    {WUEPS_PID_MMA,                     UEPS_PID_MSCC,                          ID_MMA_MSCC_HDR_CSQ_SET_REQ}
};

/* MSCC收到的XSD发送的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgFromXsdTbl[]=
{
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_CDMACSQ_SET_CNF},
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_CDMACSQ_SIGNAL_QUALITY_IND},
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_1X_SYSTEM_TIME_IND},
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_HANDSET_INFO_QRY_CNF},
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_SID_NID_IND},
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_SET_CSIDLIST_CNF},
    {UEPS_PID_XSD,                     UEPS_PID_MSCC,                          ID_XSD_MSCC_CDMA_UE_STATUS_IND}
};

/* MSCC收到的HSD发送的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgFromHsdTbl[]=
{
    {UEPS_PID_HSD,                     UEPS_PID_MSCC,                          ID_HSD_MSCC_QRY_HRPD_SYS_INFO_CNF},
    {UEPS_PID_HSD,                     UEPS_PID_MSCC,                          ID_HSD_MSCC_CAS_STATUS_IND},
    {UEPS_PID_HSD,                     UEPS_PID_MSCC,                          ID_HSD_MSCC_HDR_CSQ_SET_CNF},
    {UEPS_PID_HSD,                     UEPS_PID_MSCC,                          ID_HSD_MSCC_HDR_CSQ_IND}
};

/* MSCC收到的MMC发送的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgFromMmcTbl[]=
{
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_RSSI_IND},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_UMTS_CIPHER_INFO_IND},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_GPRS_CIPHER_INFO_IND},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_NETWORK_CAPABILITY_INFO_IND},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_CFPLMN_SET_CNF},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_CFPLMN_QUERY_CNF},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_PREF_PLMN_SET_CNF},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_PREF_PLMN_QUERY_CNF},
    {WUEPS_PID_MMC,                     UEPS_PID_MSCC,                          ID_MMC_MSCC_DPLMN_SET_CNF}
};

/* MSCC发送到MMC模块的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgToMmaTbl[]=
{
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_3GPP_SYS_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SERVICE_STATUS_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_MM_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_ATTACH_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_DETACH_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_DETACH_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PLMN_LIST_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PLMN_LIST_REJ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_RSSI_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PLMN_SPECIAL_SEL_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_DATATRAN_ATTRI_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PLMN_LIST_ABORT_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_UMTS_CIPHER_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_GPRS_CIPHER_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PLMN_SPECIAL_SEL_REJ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_AC_INFO_CHANGE_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PLMN_RESEL_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_REG_RESULT_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_EOPLMN_SET_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_USIM_AUTH_FAIL_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_NET_SCAN_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_ABORT_NET_SCAN_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_NETWORK_CAPABILITY_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CAMP_ON_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_EPLMN_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CS_SERVICE_CONN_STATUS_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SRV_REJ_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_ACQ_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_REG_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_ACQ_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PS_SERVICE_CONN_STATUS_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_RF_AVAILABLE_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SRV_ACQ_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_IMS_VOICE_CAP_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CDMACSQ_SET_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CFPLMN_SET_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CFPLMN_QUERY_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PREF_PLMN_SET_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_PREF_PLMN_QUERY_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_HRPD_OVERHEAD_MSG_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_HRPD_SYS_ACQ_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_1X_SYSTEM_TIME_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_INTERSYS_START_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_INTERSYS_END_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_HANDSET_INFO_QRY_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_1X_SID_NID_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SET_CSIDLIST_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_1X_EMC_CALL_BACK_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SYNC_SERVICE_AVAIL_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_SRCHED_PLMN_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_1X_UE_STATUS_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_HDR_CSQ_SET_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_HDR_CSQ_QUALITY_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_DPLMN_SET_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CSG_LIST_SEARCH_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CSG_LIST_ABORT_CNF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_CSG_LIST_REJ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMA,                          ID_MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND}
};

/* MSCC发送到XSD模块的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgToXsdTbl[]=
{
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_CFREQLOCK_NTF},
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_CDMACSQ_SET_REQ},
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_CAS_STATUS_IND},
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_SRV_ACQ_REQ},
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_HANDSET_INFO_QRY_REQ},
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_END_EMC_CALLBACK_NTF},
    {UEPS_PID_MSCC,                     UEPS_PID_XSD,                           ID_MSCC_XSD_SET_CSIDLIST_REQ}
};

/* MSCC发送到HSD模块的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgToHsdTbl[]=
{
    {UEPS_PID_MSCC,                     UEPS_PID_HSD,                           ID_MSCC_HSD_DISABLE_LTE_NTF},
    {UEPS_PID_MSCC,                     UEPS_PID_HSD,                           ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ},
    {UEPS_PID_MSCC,                     UEPS_PID_HSD,                           ID_MSCC_HSD_SRV_ACQ_REQ},
    {UEPS_PID_MSCC,                     UEPS_PID_HSD,                           ID_MSCC_HSD_CFREQLOCK_NTF},
    {UEPS_PID_MSCC,                     UEPS_PID_HSD,                           ID_MSCC_HSD_HDR_CSQ_SET_REQ}
};

/* MSCC发送到MMC模块的消息,黑名单 */
NAS_MSCC_MNTN_DISCARD_MSG_STRU g_stNasMsccMntnDiscardMsgToMmcTbl[]=
{
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_SIGN_REPORT_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_MODE_CHANGE_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_ATTACH_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_DETACH_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PLMN_LIST_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PLMN_LIST_ABORT_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PLMN_USER_RESEL_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PLMN_SPECIAL_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_OM_MAINTAIN_INFO_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_UPDATE_UPLMN_NTF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_EOPLMN_SET_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_NET_SCAN_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_ABORT_NET_SCAN_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_NCELL_INFO_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PS_TRANSFER_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_REG_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_BEGIN_SESSION_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_END_SESSION_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_CFPLMN_SET_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_CFPLMN_QUERY_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_SDT_CONNECTED_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PREF_PLMN_SET_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_PREF_PLMN_QUERY_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_MMSS_INFO_NTF},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_AUTO_RESEL_SET_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_GET_GEO_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_STOP_GET_GEO_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_DPLMN_SET_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_CSG_LIST_SEARCH_REQ},
    {UEPS_PID_MSCC,                     WUEPS_PID_MMC,                           ID_MSCC_MMC_CSG_LIST_ABORT_REQ}
};

/*****************************************************************************
函 数 名  : NAS_MSCC_MNTN_IsNeedDiscardForRcvMsg
功能描述  : 对MSCC模块收到的消息判断是否在忽略列表中,如果在，不勾包该消息
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE  : 消息在忽略列表中
            VOS_FALSE : 消息不在忽略列表中
调用函数  :
被调函数  :

修改历史  :
1.日    期  : 2016年01月23日
  作    者  : l00324781
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_MNTN_IsNeedDiscardForRcvMsg(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName
)
{
    VOS_UINT32                          i;

    /* 从其它模块发送到MSCC模块的消息 */
    switch (ulSenderPid)
    {
        case WUEPS_PID_MMA:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgFromMmaTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgFromMmaTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;

        case UEPS_PID_XSD:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgFromXsdTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgFromXsdTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;

         case UEPS_PID_HSD:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgFromHsdTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgFromHsdTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;

         case WUEPS_PID_MMC:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgFromMmcTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgFromMmcTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;

         default:
            break;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MSCC_MNTN_IsNeedDiscardForSndMsg
功能描述  : 对MSCC模块发送的消息判断是否在忽略列表中,如果在，不勾包该消息
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE  : 消息在忽略列表中
            VOS_FALSE : 消息不在忽略列表中
调用函数  :
被调函数  :

修改历史  :
1.日    期  : 2016年01月23日
  作    者  : l00324781
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_MNTN_IsNeedDiscardForSndMsg(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName
)
{
    VOS_UINT32                          i;

    /* 从MSCC模块发送到其它模块的消息 */
    switch (ulReceiverPid)
    {
        case WUEPS_PID_MMA:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgToMmaTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgToMmaTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;
        case UEPS_PID_XSD:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgToXsdTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgToXsdTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;
        case UEPS_PID_HSD:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgToHsdTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgToHsdTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;
        case WUEPS_PID_MMC:
            for (i = 0; i < (sizeof(g_stNasMsccMntnDiscardMsgToMmcTbl)/sizeof(NAS_MSCC_MNTN_DISCARD_MSG_STRU)); i++)
            {
                if (ulMsgName == g_stNasMsccMntnDiscardMsgToMmcTbl[i].ulMsgName)
                {
                    return VOS_TRUE;
                }
            }
            break;
        default:
            break;
    }

    return VOS_FALSE;

}



#if 0
/*****************************************************************************
 函 数 名  : NAS_MSCC_SetImsVoiceCapability
 功能描述  : IMSA发送IMS语音能力的桩函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年8月14日
   作    者   : n00269697
   修改内容   : DTS2015072803051

*****************************************************************************/
VOS_VOID NAS_MSCC_MNTN_ImsaSendImsVoiceCap(
    VOS_UINT8                           ucAvail
)
{
    IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    pstMsg = (IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(PS_PID_IMSA, sizeof(IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU));

    if (NULL == pstMsg)
    {
        return;
    }

    PS_MEM_SET(((VOS_UCHAR *)pstMsg) + VOS_MSG_HEAD_LENGTH, 0,
                                          sizeof(IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = PS_PID_IMSA;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_MSCC;
    pstMsg->ulMsgId         = ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY;
    pstMsg->ulLength        = sizeof(IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enImsVoiceCap   = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;

    if (VOS_TRUE == ucAvail)
    {
        pstMsg->enImsVoiceCap   = MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE;
    }

    pstMsg->ucIsExistPersistentBearer = VOS_TRUE;

    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;

}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



