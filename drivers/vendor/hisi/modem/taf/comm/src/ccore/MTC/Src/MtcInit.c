
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcInit.h"
#include "MtcCtx.h"
#include "MtcMain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MTC_INIT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

VOS_UINT32 MTC_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 初始化上下文 */
            MTC_InitCtx();
            break;

        default:
            break;
    }

    return VOS_OK;
}
#endif

VOS_UINT32 MTC_FidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_MTC,
                                         (Init_Fun_Type)MTC_PidInit,
                                         (Msg_Fun_Type)MTC_ProcMsg);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(UEPS_FID_MTC, VOS_PRIORITY_M5);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            break;

        default:
            break;
    }
#endif

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

