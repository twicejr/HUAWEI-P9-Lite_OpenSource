

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "VcCtx.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define THIS_FILE_ID                    PS_FILE_ID_VC_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
APP_VC_STATE_MGMT_STRU                  g_stVcStateMgmt;

#if 0
/* VC CTX,用于保存VC上下文 */
APP_VC_STATE_MGMT_STRU                  g_stAppVcCtx;
#endif


/*****************************************************************************
   3 函数实现
*****************************************************************************/
#if 0

APP_VC_STATE_MGMT_STRU*  APP_VC_GetCtx( VOS_VOID )
{
    return &(g_stAppVcCtx);
}
#endif

APP_VC_STATE_MGMT_STRU*  APP_VC_GetVcStateMgmtAddr( VOS_VOID )
{
    return &(g_stVcStateMgmt);
}



APP_VC_MS_CFG_INFO_STRU* APP_VC_GetCustomCfgInfo( VOS_VOID )
{
    return &(APP_VC_GetVcStateMgmtAddr()->stMsCfgInfo);
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_UINT8* APP_VC_GetEcallMsdAddr( VOS_VOID )
{
    return &(APP_VC_GetVcStateMgmtAddr()->stEcallCtx.aucMsdData[0]);
}


VOS_VOID APP_VC_SetNewEcallCfg(
    VOS_UINT16                          usMode,
    VOS_UINT16                          usVocConfig
)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallMode         = usMode;
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallVocConfig    = usVocConfig;
}


VOS_VOID APP_VC_UpdateCurrEcallCfg(VOS_VOID)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallMode        = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallMode;
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallVocConfig   = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallVocConfig;
}


VOS_VOID APP_VC_GetCurrEcallCfg(
    VOS_UINT16                         *pusMode,
    VOS_UINT16                         *pusVocConfig
)
{
    *pusMode        = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallMode;
    *pusVocConfig   = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallVocConfig;
}


VOS_VOID APP_VC_SetInEcallFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enInECall = enFlag;
}


PS_BOOL_ENUM_UINT8 APP_VC_GetInEcallFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enInECall;
}


VOS_VOID APP_VC_SetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enMsdFlag = enFlag;
}


PS_BOOL_ENUM_UINT8 APP_VC_GetMsdFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enMsdFlag;
}



VOS_VOID APP_VC_SetEcallState(APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 enState)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enEcallState = enState;
}


APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 APP_VC_GetEcallState(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enEcallState;
}


VOS_VOID APP_VC_SetEcallDescription(VOS_UINT32 ulDesc)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.ulEcallDescription = ulDesc;
}


VOS_UINT32 APP_VC_GetEcallDescription(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.ulEcallDescription;
}


VOS_VOID APP_VC_SetAllowSetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enAllowSetMsdFlag = enFlag;
}


PS_BOOL_ENUM_UINT8 APP_VC_GetAllowSetMsdFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enAllowSetMsdFlag;
}


VC_AL_ACK_REPORT_INFO_STRU* APP_VC_GetAlAckInfoAddr(VOS_VOID)
{
    return &(APP_VC_GetVcStateMgmtAddr()->stEcallCtx.stVcAlAckReportInfo);
}


#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



