

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "CnasPrlMntn.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_PRL_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958 */


VOS_VOID CNAS_PRL_MntnConvertAcqRecInfo(
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord,
    CNAS_PRL_MNTN_ACQ_RECORD_STRU      *pstMntnAcqRec
)
{
    VOS_UINT8                           i;

    pstMntnAcqRec->enAcqType  = pstAcqRecord->enAcqType;
    pstMntnAcqRec->ucAcqValid = pstAcqRecord->ucAcqValid;

    switch (pstAcqRecord->enAcqType)
    {
        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS:
            {
                NAS_MEM_CPY_S(&(pstMntnAcqRec->u.stCellularStandardSys),
                              sizeof(CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU),
                              &(pstAcqRecord->u.stCellularStandardSys),
                              sizeof(CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU));
            }
            break;

        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS:
            {
                pstMntnAcqRec->u.stCelluarCustomSys.ucNumOfChans = pstAcqRecord->u.stCelluarCustomSys.ucNumOfChans;

                for (i = 0; i < pstAcqRecord->u.stCelluarCustomSys.ucNumOfChans; i++)
                {
                    pstMntnAcqRec->u.stCelluarCustomSys.ausChan[i] = pstAcqRecord->u.stCelluarCustomSys.ausChan[i];
                }
            }
            break;

        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED:
            {
                pstMntnAcqRec->u.stCellularPreSys.enSysSelType = pstAcqRecord->u.stCellularPreSys.enSysSelType;
            }
            break;

        case CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS:
            {
                pstMntnAcqRec->u.stPcsBlocksSys.ucNumOfBlocks = pstAcqRecord->u.stPcsBlocksSys.ucNumOfBlocks;

                for (i = 0; i < pstAcqRecord->u.stPcsBlocksSys.ucNumOfBlocks; i++)
                {
                    pstMntnAcqRec->u.stPcsBlocksSys.aenBlock[i] = pstAcqRecord->u.stPcsBlocksSys.aenBlock[i];
                }
            }
            break;

        case CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS:
            {
                pstMntnAcqRec->u.stPcsChannelsSys.ucNumOfChans = pstAcqRecord->u.stPcsChannelsSys.ucNumOfChans;

                for (i = 0; i < pstAcqRecord->u.stPcsChannelsSys.ucNumOfChans; i++)
                {
                    pstMntnAcqRec->u.stPcsChannelsSys.ausChan[i] = pstAcqRecord->u.stPcsChannelsSys.ausChan[i];
                }
            }
            break;

        case CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95:
            {
                pstMntnAcqRec->u.st1xAndIs95Sys.ucNumOfChans = pstAcqRecord->u.st1xAndIs95Sys.ucNumOfChans;

                for (i = 0; i < pstAcqRecord->u.st1xAndIs95Sys.ucNumOfChans; i++)
                {

                    pstMntnAcqRec->u.st1xAndIs95Sys.astFreq[i].enBandClass = pstAcqRecord->u.st1xAndIs95Sys.astFreq[i].enBandClass;
                    pstMntnAcqRec->u.st1xAndIs95Sys.astFreq[i].usChannel   = pstAcqRecord->u.st1xAndIs95Sys.astFreq[i].usChannel;
                }
            }
            break;
        /* 1、copy时乘上sizeof */
        case CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD:
            {
                pstMntnAcqRec->u.stHrpdSys.ucNumOfChans = pstAcqRecord->u.stHrpdSys.ucNumOfChans;
                NAS_MEM_CPY_S(&pstMntnAcqRec->u.stHrpdSys.astFreq[0],
                              CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                              &pstAcqRecord->u.stHrpdSys.astFreq[0],
                              pstAcqRecord->u.stHrpdSys.ucNumOfChans * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
            }
            break;

        case CNAS_PRL_ACQ_TYPE_COMMON_ACQ_TABLE_RECORD_FOR_UMB:
        case CNAS_PRL_ACQ_TYPE_COMMON_ACQ_RECORD_FOR_UMB:
        case CNAS_PRL_ACQ_TYPE_CELLULAR_ANALOG:
        /* 1、JTACS和2G记录不支持，不做处理*/
        case CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS:
        case CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS:
        case CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS:
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_TraceAcqRecInfo: invalid acquisiton record type!");
            break;
    }
}


VOS_VOID CNAS_PRL_LogHeaderInfo(CNAS_PRL_HEADER_INFO_STRU *pstPrlHeader)
{
    CNAS_PRL_MNTN_HEADER_INFO_IND_STRU                     *pstHeaderInfo = VOS_NULL_PTR;

    pstHeaderInfo = (CNAS_PRL_MNTN_HEADER_INFO_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                      sizeof(CNAS_PRL_MNTN_HEADER_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstHeaderInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstHeaderInfo, sizeof(CNAS_PRL_MNTN_HEADER_INFO_IND_STRU), 0, sizeof(CNAS_PRL_MNTN_HEADER_INFO_IND_STRU));

    pstHeaderInfo->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstHeaderInfo->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstHeaderInfo->ulSenderPid          = UEPS_PID_XSD;
    pstHeaderInfo->ulReceiverPid        = UEPS_PID_XSD;
    pstHeaderInfo->ulLength             = sizeof(CNAS_PRL_MNTN_HEADER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstHeaderInfo->enMsgId              = ID_CNAS_PRL_MNTN_HEADER_INFO_IND;

    NAS_MEM_CPY_S(&(pstHeaderInfo->stHeaderInfo), sizeof(CNAS_PRL_HEADER_INFO_STRU), pstPrlHeader, sizeof(CNAS_PRL_HEADER_INFO_STRU));

    DIAG_TraceReport(pstHeaderInfo);

    PS_MEM_FREE(UEPS_PID_XSD, pstHeaderInfo);
}


VOS_VOID CNAS_PRL_LogAcqRecInfo(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecordInfo
)
{
    CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU                    *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_PRL_MNTN_ACQ_RECORD_STRU                           stMntnAcqRec;
    VOS_UINT16                                              i;
    VOS_UINT8                                               j;

    pstAcqRecInfo = (CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                       sizeof(CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstAcqRecInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstAcqRecInfo, sizeof(CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU), 0, sizeof(CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU));

    pstAcqRecInfo->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstAcqRecInfo->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstAcqRecInfo->ulSenderPid          = UEPS_PID_XSD;
    pstAcqRecInfo->ulReceiverPid        = UEPS_PID_XSD;
    pstAcqRecInfo->ulLength             = sizeof(CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAcqRecInfo->enMsgId              = ID_CNAS_PRL_MNTN_ACQ_RECORD_INFO_IND;

    j = 0;

    for (i = 0; i < pstAcqRecordInfo->usAcqRecordNum; i++)
    {
        NAS_MEM_SET_S(&stMntnAcqRec, sizeof(CNAS_PRL_MNTN_ACQ_RECORD_STRU), 0, sizeof(CNAS_PRL_MNTN_ACQ_RECORD_STRU));

        CNAS_PRL_MntnConvertAcqRecInfo(pstAcqRecordInfo->pastPrlAcqRecord[i], &stMntnAcqRec);

        NAS_MEM_CPY_S(&(pstAcqRecInfo->astAcqRec[j]), sizeof(CNAS_PRL_MNTN_ACQ_RECORD_STRU), &stMntnAcqRec, sizeof(CNAS_PRL_MNTN_ACQ_RECORD_STRU));
        j++;

        /* 捕获记录每10个记录输出一次 */
        if (0 == (j%CNAS_PRL_MNTN_MAX_ACQ_REC_NUM))
        {
            pstAcqRecInfo->ucRecNum = CNAS_PRL_MNTN_MAX_ACQ_REC_NUM;
            DIAG_TraceReport(pstAcqRecInfo);

            j = 0;

            NAS_MEM_SET_S(&(pstAcqRecInfo->astAcqRec[0]),
                          sizeof(CNAS_PRL_MNTN_ACQ_RECORD_STRU) * CNAS_PRL_MNTN_MAX_ACQ_REC_NUM,
                          0,
                          sizeof(CNAS_PRL_MNTN_ACQ_RECORD_STRU) * CNAS_PRL_MNTN_MAX_ACQ_REC_NUM);
        }
    }

    /* 捕获记录不够10个，此处输出 */
    if (0 != j)
    {
        pstAcqRecInfo->ucRecNum = j;

        DIAG_TraceReport(pstAcqRecInfo);
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstAcqRecInfo);
}


VOS_VOID CNAS_PRL_LogSysRecInfo(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecordInfo
)
{
    CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU                    *pstSysRecInfo = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    VOS_UINT8                                               j;

    pstSysRecInfo = (CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                       sizeof(CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSysRecInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSysRecInfo, sizeof(CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU), 0, sizeof(CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU));

    pstSysRecInfo->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSysRecInfo->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSysRecInfo->ulSenderPid          = UEPS_PID_XSD;
    pstSysRecInfo->ulReceiverPid        = UEPS_PID_XSD;
    pstSysRecInfo->ulLength             = sizeof(CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSysRecInfo->enMsgId              = ID_CNAS_PRL_MNTN_SYS_RECORD_INFO_IND;

    j = 0;
    for (i = 0; i < pstSysRecordInfo->usSysRecordNum; i++)
    {
        NAS_MEM_CPY_S(&(pstSysRecInfo->astSysRec[j]),
                      sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU),
                      &(pstSysRecordInfo->pstSysRecord[i]),
                      sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        j++;

        /* 系统记录每10个记录输出一次 */
        if (0 == (j%CNAS_PRL_MNTN_MAX_ACQ_REC_NUM))
        {
            pstSysRecInfo->ucRecNum = CNAS_PRL_MNTN_MAX_SYS_REC_NUM;

            DIAG_TraceReport(pstSysRecInfo);

            /* 初始化系统记录表信息 */
            j = 0;
            NAS_MEM_SET_S(&(pstSysRecInfo->astSysRec[0]),
                          sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * CNAS_PRL_MNTN_MAX_SYS_REC_NUM,
                          0,
                          sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * CNAS_PRL_MNTN_MAX_SYS_REC_NUM);
        }
    }

    /* 系统记录不够10个，此处输出 */
    if (0 != j)
    {
        pstSysRecInfo->ucRecNum = j;

        DIAG_TraceReport(pstSysRecInfo);
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecInfo);
}


VOS_VOID CNAS_PRL_LogMultiMatchedGeoInfo(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                   *pstMultiMatchedGeoInfo
)
{
    CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU          *pstGeoInfo = VOS_NULL_PTR;

    pstGeoInfo = (CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                       sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU));
    if (VOS_NULL_PTR == pstGeoInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstGeoInfo, sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU), 0, sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU));

    pstGeoInfo->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstGeoInfo->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstGeoInfo->ulSenderPid          = UEPS_PID_XSD;
    pstGeoInfo->ulReceiverPid        = UEPS_PID_XSD;
    pstGeoInfo->ulLength             = sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstGeoInfo->enMsgId              = ID_CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_IND;

    NAS_MEM_CPY_S(&pstGeoInfo->stMultiMatchedGeoInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU), pstMultiMatchedGeoInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU));

    DIAG_TraceReport(pstGeoInfo);

    PS_MEM_FREE(UEPS_PID_XSD, pstGeoInfo);
}


VOS_VOID CNAS_PRL_LogMultiMatchedGeoListInfo(
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMultiMatchedGeoListInfo
)
{
    CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU         *pstGeoListInfo = VOS_NULL_PTR;

    pstGeoListInfo = (CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                       sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstGeoListInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstGeoListInfo, sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU));

    pstGeoListInfo->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstGeoListInfo->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstGeoListInfo->ulSenderPid          = UEPS_PID_XSD;
    pstGeoListInfo->ulReceiverPid        = UEPS_PID_XSD;
    pstGeoListInfo->ulLength             = sizeof(CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstGeoListInfo->enMsgId              = ID_CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_IND;

    NAS_MEM_CPY_S(&pstGeoListInfo->stMultiMatchedGeoListInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU), pstMultiMatchedGeoListInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

    DIAG_TraceReport(pstGeoListInfo);

    PS_MEM_FREE(UEPS_PID_XSD, pstGeoListInfo);
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



