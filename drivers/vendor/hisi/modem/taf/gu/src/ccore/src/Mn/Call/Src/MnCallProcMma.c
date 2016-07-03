


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallProcMma.h"
#include "MnCallMnccProc.h"
#include "MnCall.h"

#include "TafSdcLib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_MMA_C

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TAF_CALL_ClearCallInfo(VOS_VOID)
{
    /*如果声码器打开则需关闭声码器*/
    if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
    {
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
        /* 发送消息通知VC关闭语音通道 */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
        /* 发送消息通知AT语音通道状态 */
        MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
    }

    MN_CALL_Init(MN_CALL_POWER_STATE_OFF);
}

VOS_VOID TAF_CALL_RcvMmaPowerOffInd(
    TAF_MMA_POWER_OFF_IND_STRU         *pstMsg
)
{
    TAF_CALL_ClearCallInfo();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_CALL_RcvMmaSyscfgInfoInd(
    MMA_TAF_SYS_CFG_INFO_IND_STRU       *pstMsg
)
{
    VOS_UINT32                          ulIsSupportGsm;

    ulIsSupportGsm = TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_GSM, &(pstMsg->stNewRatOrder));

    if ( (VOS_TRUE == TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_WCDMA, &(pstMsg->stNewRatOrder)))
      || (VOS_TRUE == ulIsSupportGsm) )
    {
        return;
    }

    TAF_CALL_ClearCallInfo();
}
#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



