/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcCttf.c
  版 本 号   : 初稿
  作    者   : c00177591
  生成日期   : 2015年10月23日
  功能描述   : TAF X CALL处理来自Cttf的消息
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月23日
    作    者   : c00177591
    修改内容   : 创建文件
******************************************************************************/

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
/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvCttfDecryptVoiceDataReportInd
 功能描述  : 收到CTTF上报的测试模式语音数据信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00177591
    修改内容   : 新生成函数
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

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvCttfDecryptVoiceStatReportInd
 功能描述  : 收到CTTF上报的测试模式语音数据信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00177591
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvCttfDecryptVoiceStatReportInd(VOS_VOID *pMsg)
{
    CTTF_CNAS_1X_DECRYPT_VOICE_STATISTICS_REPORT_IND_STRU  *pstStatReportInd = VOS_NULL_PTR;

    pstStatReportInd = (CTTF_CNAS_1X_DECRYPT_VOICE_STATISTICS_REPORT_IND_STRU *)pMsg;

    TAF_XCALL_SndEncryptedVoiceDataInd((VOS_INT8 *)pstStatReportInd->acCalcTimeStr,
                                       (VOS_UINT32)TAF_XCALL_MIN(CTTF_1X_VOICE_DECRYPT_STATISTICS_STRING_MAX_BYTE_LENGTH,
                                                                 VOS_StrLen(pstStatReportInd->acCalcTimeStr)));
    return;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvCttfEncryptVoiceDataReportInd
 功能描述  : 收到CTTF上报的测试模式语音数据信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00177591
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_XCALL_RcvCttfEncryptVoiceStatReportInd
 功能描述  : 收到CTTF上报的测试模式语音数据信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00177591
    修改内容   : 新生成函数
*****************************************************************************/
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
