


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallCtx.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "MnCallMgmt.h"
#include "MnCallTimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MMC CTX,用于保存MMC状态机,描述表 */
MN_CALL_CONTEXT_STRU                    g_stMnCallCtx;


/*****************************************************************************
   3 函数实现
*****************************************************************************/


MN_CALL_CONTEXT_STRU*  MN_CALL_GetCtx( VOS_VOID )
{
    return &(g_stMnCallCtx);
}


MN_CALL_CUSTOM_CFG_INFO_STRU* MN_CALL_GetCustomCfgInfo( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg);
}


TAF_CALL_REDIAL_CFG_STRU *MN_CALL_GetCallRedialCfg(VOS_VOID)
{
    return &(MN_CALL_GetCustomCfgInfo()->stCallRedialCfgInfo.stCallRedialCfg);
}


TAF_CALL_CCWA_CTRL_MODE_ENUM_U8 TAF_CALL_GetCcwaCtrlMode(VOS_VOID)
{
    return MN_CALL_GetCustomCfgInfo()->enCcwaCtrlMode;
}


VOS_VOID TAF_CALL_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
)
{
    MN_CALL_GetCustomCfgInfo()->enCcwaCtrlMode = enCcwaCtrlMode;

    return;
}


TAF_CALL_APP_CFG_INFO_STRU* MN_CALL_GetAppCfgInfo(VOS_VOID)
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stAppCfg);
}


VOS_VOID TAF_CALL_SetCcwaiMode(
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode
)
{
    MN_CALL_GetAppCfgInfo()->enCcwaiMode = enCcwaiMode;
}


TAF_CALL_CCWAI_MODE_ENUM_UINT8 TAF_CALL_GetCcwaiMode(VOS_VOID)
{
    return MN_CALL_GetAppCfgInfo()->enCcwaiMode;
}


TAF_CALL_CCWAI_MODE_ENUM_UINT8 TAF_GetCcwaiMode(VOS_VOID)
{
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;

    enCcwaiMode = TAF_CALL_GetCcwaiMode();

    TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_GetCcwaiMode ", enCcwaiMode);

    return enCcwaiMode;
}


VOS_VOID TAF_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
)
{
    TAF_CALL_SetCcwaCtrlMode(enCcwaCtrlMode);

    return;
}


VOS_UINT8 TAF_CALL_GetAtaReportOkAsyncFlag(VOS_VOID)
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag;
}


VOS_VOID TAF_CALL_SetAtaReportOkAsyncFlag(
    VOS_UINT8                           ucAtaReportOkAsyncFlag
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag
                           = ucAtaReportOkAsyncFlag;
    return;
}




VOS_UINT32 MN_CALL_GetCallRedialSupportFlg(VOS_VOID)
{
    return (MN_CALL_GetCallRedialCfg()->ucCallRedialSupportFlg);
}

#if (FEATURE_ON == FEATURE_ECALL)

MN_CALL_REDIAL_CFG_STRU *TAF_CALL_GetEcallRedialCfg(VOS_VOID)
{
    return &(MN_CALL_GetCustomCfgInfo()->stCallRedialCfgInfo.stEcallRedialCfg);
}


VOS_UINT8 TAF_CALL_GetEcallRedialSupportFlg(VOS_VOID)
{
    return (TAF_CALL_GetEcallRedialCfg()->ucCallRedialSupportFlg);
}


VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 TAF_CALL_GetEcallMsdTransStatus(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.enEcallTransStatus);
}


VOS_VOID TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 enEcallTransStatus)
{
    MN_CALL_GetCtx()->stEcallCtx.enEcallTransStatus = enEcallTransStatus;
}


VOS_UINT8 TAF_CALL_GetWaitingMtEcallFlag(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ucWaitMtEcallFlag);
}


VOS_VOID TAF_CALL_SetWaitingMtEcallFlag(VOS_UINT8 ucWaitMtEcallFlag)
{
    MN_CALL_GetCtx()->stEcallCtx.ucWaitMtEcallFlag = ucWaitMtEcallFlag;
}


VOS_VOID TAF_CALL_SetInternalHangUpFlag(VOS_UINT8 ucInternalHangUpFlag)
{
    MN_CALL_GetCtx()->stEcallCtx.ucInternalHangUpFlag = ucInternalHangUpFlag;
}


VOS_UINT8 TAF_CALL_GetInternalHangUpFlag(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ucInternalHangUpFlag);
}


VOS_VOID TAF_CALL_ResetEcallPeriodRemainTimerLen(VOS_VOID)
{
    MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen = \
        TAF_CALL_GetTimerLen(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
}


VOS_VOID TAF_CALL_UpdateEcallPeriodRemainTimerLen(VOS_UINT32 ulEcallPeriodTimerLen)
{
    MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen = ulEcallPeriodTimerLen;
}


VOS_UINT32 TAF_CALL_GetEcallPeriodRemainTimerLen(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen);
}
#endif

/*lint -save -e958 */

VOS_UINT32 TAF_CALL_GetRedialSupportFlg(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulRedialSupportFlg;

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        ulRedialSupportFlg = (VOS_UINT32)TAF_CALL_GetEcallRedialSupportFlg();
    }
    else
#endif
    {
        ulRedialSupportFlg = (VOS_UINT32)MN_CALL_GetCallRedialSupportFlg();
    }

    return ulRedialSupportFlg;
}
/*lint -restore */


MN_CALL_MSG_BUFF_STRU*  MN_CALL_GetBufferedMsg( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMnCallBufferedMsg);
}


VOS_VOID MN_CALL_ClearBufferedMsg(VOS_VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    PS_MEM_SET(pstMsgBuff, 0x0, sizeof(MN_CALL_MSG_BUFF_STRU));
    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_ENUM_UINT8 enSrvccState)
{
    MN_CALL_GetCtx()->enSrvccState = enSrvccState;
}


MN_CALL_SRVCC_STATE_ENUM_UINT8 TAF_CALL_GetSrvccState(VOS_VOID)
{
    return (MN_CALL_GetCtx()->enSrvccState);
}
#endif


VOS_VOID MN_CALL_InitCtx(VOS_VOID)
{
    PS_MEM_SET(MN_CALL_GetCtx(), 0x0, sizeof(g_stMnCallCtx));

    #if (FEATURE_ON == FEATURE_IMS)
    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_BUTT);

    TAF_CALL_SetCcwaiMode(VOS_TRUE);
    TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_NW);
    TAF_WARNING_LOG2(WUEPS_PID_TAF, "MN_CALL_InitCtx ", TAF_CALL_CCWA_CTRL_BY_NW, VOS_TRUE);
#endif

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
#endif
}




VOS_VOID TAF_CALL_SetCallStatusControl(
    VOS_UINT8                           ucCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl = ucCallStatus;
}


VOS_UINT8 TAF_CALL_GetCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl;
}


VOS_VOID TAF_CALL_SetMultiSimCallStatusControl(
    VOS_UINT8                           ucMultiSimCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl = ucMultiSimCallStatus;
}


VOS_UINT8 TAF_CALL_GetMultiSimCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl;
}



VOS_VOID TAF_CALL_SetVpCfgState(
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpStateStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState = enVpStateStatus;
}


MN_CALL_VP_NV_CFG_STATE_ENUM_U8 TAF_CALL_GetVpCfgState( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



