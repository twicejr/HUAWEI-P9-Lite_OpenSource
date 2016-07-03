

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallProcCttf.h"
#include "TafXCallCtx.h"
#include "TafXCallSndApp.h"
#include "MnComm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_CTTF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID TAF_XCALL_RcvCttfDecryptVoiceDataReportInd(VOS_VOID *pMsg)
{
    VOS_UINT8                                               i;
    CTTF_CNAS_1X_DECRYPT_VOICE_DATA_REPORT_IND_STRU        *pstDataReportInd = VOS_NULL_PTR;

    pstDataReportInd = (CTTF_CNAS_1X_DECRYPT_VOICE_DATA_REPORT_IND_STRU *)pMsg;

    for (i = 0; i < TAF_XCALL_MIN(pstDataReportInd->ucValidNum, CTTF_1X_VOICE_DECRYPT_DATA_STRING_REPORT_MAX_GROUP_PER_TIME); i++)
    {
        TAF_XCALL_SndEncryptedVoiceDataInd((VOS_INT8 *)pstDataReportInd->astVoiceStrData[i].acVoiceDataStr,
                                           (VOS_UINT32)TAF_XCALL_MIN(CTTF_1X_VOICE_DECRYPT_DATA_STRING_MAX_BYTE_LENGTH,
                                                                     VOS_StrLen(pstDataReportInd->astVoiceStrData[i].acVoiceDataStr)));
    }

    return;
}


VOS_VOID TAF_XCALL_RcvCttfDecryptVoiceStatReportInd(VOS_VOID *pMsg)
{
    CTTF_CNAS_1X_DECRYPT_VOICE_STATISTICS_REPORT_IND_STRU  *pstStatReportInd = VOS_NULL_PTR;

    pstStatReportInd = (CTTF_CNAS_1X_DECRYPT_VOICE_STATISTICS_REPORT_IND_STRU *)pMsg;

    TAF_XCALL_SndEncryptedVoiceDataInd((VOS_INT8 *)pstStatReportInd->acCalcTimeStr,
                                       (VOS_UINT32)TAF_XCALL_MIN(CTTF_1X_VOICE_DECRYPT_STATISTICS_STRING_MAX_BYTE_LENGTH,
                                                                 VOS_StrLen(pstStatReportInd->acCalcTimeStr)));
    return;
}

VOS_VOID TAF_XCALL_RcvCttfEncryptVoiceDataReportInd(VOS_VOID *pMsg)
{
    VOS_UINT8                                               i;
    CTTF_CNAS_1X_ENCRYPT_VOICE_DATA_REPORT_IND_STRU        *pstDataReportInd = VOS_NULL_PTR;

    pstDataReportInd = (CTTF_CNAS_1X_ENCRYPT_VOICE_DATA_REPORT_IND_STRU *)pMsg;

    for (i = 0; i < TAF_XCALL_MIN(pstDataReportInd->ucValidNum, CTTF_1X_VOICE_ENCRYPT_DATA_STRING_REPORT_MAX_GROUP_PER_TIME); i++)
    {
        TAF_XCALL_SndEncryptedVoiceDataInd((VOS_INT8 *)pstDataReportInd->astVoiceStrData[i].acVoiceDataStr,
                                           (VOS_UINT32)TAF_XCALL_MIN(CTTF_1X_VOICE_ENCRYPT_DATA_STRING_MAX_BYTE_LENGTH,
                                                                     VOS_StrLen(pstDataReportInd->astVoiceStrData[i].acVoiceDataStr)));
    }

    return;
}


VOS_VOID TAF_XCALL_RcvCttfEncryptVoiceStatReportInd(VOS_VOID *pMsg)
{
    CTTF_CNAS_1X_ENCRYPT_VOICE_STATISTICS_REPORT_IND_STRU  *pstStatReportInd = VOS_NULL_PTR;

    pstStatReportInd = (CTTF_CNAS_1X_ENCRYPT_VOICE_STATISTICS_REPORT_IND_STRU *)pMsg;

    TAF_XCALL_SndEncryptedVoiceDataInd((VOS_INT8 *)pstStatReportInd->acCalcTimeStr,
                                       (VOS_UINT32)TAF_XCALL_MIN(CTTF_1X_VOICE_ENCRYPT_STATISTICS_STRING_MAX_BYTE_LENGTH,
                                                                 VOS_StrLen(pstStatReportInd->acCalcTimeStr)));
    return;
}

#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE*/
#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT*/
#endif /*FEATURE_UE_MODE_CDMA*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
