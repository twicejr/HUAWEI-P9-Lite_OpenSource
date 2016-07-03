

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "TafXCallSndCttf.h"
#include "cttf_1x_mac_encrypted_voice_cfg_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_CTTF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID TAF_XCALL_SendCttf1xMacEncryptVoiceNtf(
    MACITF_1X_VOICE_ENCRYPT_TYPE_ENUM_UINT8                 enType
)
{
    CNAS_CTTF_1X_MAC_ENCRYPT_VOICE_NTF_STRU                *pstCttfEncyptVoiceNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstCttfEncyptVoiceNtf = (CNAS_CTTF_1X_MAC_ENCRYPT_VOICE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                                    sizeof(CNAS_CTTF_1X_MAC_ENCRYPT_VOICE_NTF_STRU));

    if (VOS_NULL_PTR == pstCttfEncyptVoiceNtf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstCttfEncyptVoiceNtf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(CNAS_CTTF_1X_MAC_ENCRYPT_VOICE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写VOS消息头 */
    pstCttfEncyptVoiceNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCttfEncyptVoiceNtf->ulSenderPid     = WUEPS_PID_TAF;
    pstCttfEncyptVoiceNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCttfEncyptVoiceNtf->ulReceiverPid   = MSPS_PID_1X_RMAC;
    pstCttfEncyptVoiceNtf->ulLength        = sizeof(CNAS_CTTF_1X_MAC_ENCRYPT_VOICE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstCttfEncyptVoiceNtf->enMsgId         = ID_CNAS_CTTF_1X_MAC_ENCRYPT_VOICE_NTF;
    pstCttfEncyptVoiceNtf->usOpId          = 0;
    pstCttfEncyptVoiceNtf->enType          = enType;

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstCttfEncyptVoiceNtf);
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)

VOS_VOID TAF_XCALL_SendCttf1xSetEncryptVoiceModeNtf(
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode
)
{
    CNAS_CTTF_1X_SET_ENCRYPT_VOICE_MODE_NTF_STRU           *pstCttfTestModeNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstCttfTestModeNtf = (CNAS_CTTF_1X_SET_ENCRYPT_VOICE_MODE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                                    sizeof(CNAS_CTTF_1X_SET_ENCRYPT_VOICE_MODE_NTF_STRU));

    if (VOS_NULL_PTR == pstCttfTestModeNtf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstCttfTestModeNtf + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(CNAS_CTTF_1X_SET_ENCRYPT_VOICE_MODE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写VOS消息头 */
    pstCttfTestModeNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCttfTestModeNtf->ulSenderPid     = WUEPS_PID_TAF;
    pstCttfTestModeNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCttfTestModeNtf->ulReceiverPid   = MSPS_PID_1X_RMAC;
    pstCttfTestModeNtf->ulLength        = sizeof(CNAS_CTTF_1X_SET_ENCRYPT_VOICE_MODE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息内容 */
    pstCttfTestModeNtf->enMsgId         = ID_CNAS_CTTF_1X_SET_ENCRYPT_VOICE_MODE_NTF;
    pstCttfTestModeNtf->usOpId          = 0;

    if (TAF_CALL_APP_SET_EC_TEST_MODE_ENABLE == enTestMode)
    {
        pstCttfTestModeNtf->enTestMode  = PS_TRUE;
    }
    else
    {
        pstCttfTestModeNtf->enTestMode  = PS_FALSE;
    }

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstCttfTestModeNtf);
}
#endif

#endif

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


