

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "PsLogFilter.h"

#ifdef  __cplusplus
    #if  __cplusplus
        extern "C" {
    #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_LOG_FILTER_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/
extern VOS_UINT32 GUNAS_OM_LayerMsgFilter(
    const VOS_VOID                     *pstMsg
);

extern VOS_UINT32 PAM_OM_LayerMsgFilter(
    const VOS_VOID                      *pMsg
);

extern VOS_UINT32 TLPS_OM_LayerMsgFilter(
    const VOS_VOID                      *pMsg
);

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/
/* C核过滤函数 */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)

VOS_UINT32 PS_OM_LayerMsgFilter_Ccpu(
    const VOS_VOID                      *pMsg
)
{
    /* GUNAS */
    if (VOS_TRUE == GUNAS_OM_LayerMsgFilter(pMsg))
    {
        return VOS_TRUE;
    }

    /* LNAS */
    if (VOS_TRUE == TLPS_OM_LayerMsgFilter(pMsg))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == PAM_OM_LayerMsgFilter(pMsg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/* A核过滤函数 */
#if (OSA_CPU_ACPU == VOS_OSA_CPU)

VOS_UINT32 PS_OM_LayerMsgFilter_Acpu(
    const VOS_VOID                      *pMsg
)
{
    /* GUNAS */
    if (VOS_TRUE == GUNAS_OM_LayerMsgFilter(pMsg))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == PAM_OM_LayerMsgFilter(pMsg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

#ifdef  __cplusplus
    #if  __cplusplus
        }
    #endif
#endif
