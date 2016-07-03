

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallSndMma.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_MMA_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8 TAF_XCALL_BuildMmaCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        return TAF_MMA_1X_EMERGENCY_VOICE_CALL;
    }

    return TAF_MMA_1X_NORMAL_VOICE_CALL;
}

/* 移到MMA中提供API实现 */


/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





