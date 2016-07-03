
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsTimerMgmt.h"
#include "AdsCtx.h"
#include "AdsDownLink.h"
#include "AdsUpLink.h"
#include "AdsDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_TIMERMGMT_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

ADS_TIMER_OPERATE_STRU                  g_astAdsTmrOperateTbl[] =
{
    { ACPU_PID_ADS_UL,  TI_ADS_UL_SEND,         VOS_TIMER_PRECISION_5,  {0},    ADS_UL_RcvTiSendExpired     },
    { ACPU_PID_ADS_UL,  TI_ADS_DSFLOW_STATS,    VOS_TIMER_NO_PRECISION, {0},    VOS_NULL_PTR                },
    { ACPU_PID_ADS_DL,  TI_ADS_DL_ADQ_EMPTY,    VOS_TIMER_PRECISION_0,  {0},    ADS_DL_RcvTiAdqEmptyExpired },
    { ACPU_PID_ADS_UL,  TI_ADS_UL_DATA_STAT,    VOS_TIMER_NO_PRECISION, {0},    VOS_NULL_PTR                }

};

/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID  ADS_MNTN_TraceTimerOperation(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulTimerLen,
    ADS_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
)
{
    ADS_TIMER_INFO_STRU                 stMsg = {0};

    stMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid       = ulPid;
    stMsg.ulReceiverPid     = VOS_PID_TIMER;
    stMsg.ulLength          = sizeof(ADS_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stMsg.enTimerId         = enTimerId;
    stMsg.ulTimerLen        = ulTimerLen;
    stMsg.enTimerAction     = enTimerAction;
    stMsg.enTimerStopCause  = enStopCause;
    stMsg.aucReserved[0]    = 0;
    stMsg.aucReserved[1]    = 0;

    DIAG_TraceReport(&stMsg);

    return;
}


VOS_VOID  ADS_StartTimer(
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulLen
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx      = VOS_NULL_PTR;
    ADS_TIMER_OPERATE_STRU             *pstTmrOperate = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 不在使用的定时器范围内 */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_UL,
            "ADS_StartTimer: timer id is invalid. <enTimerId>", enTimerId);
        return;
    }


    /* 获取定时器上下文 */
    pstTmrOperate = &(g_astAdsTmrOperateTbl[enTimerId]);
    pstTiCtx      = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    /* 定时器长度检查 */
    if (0 == ulLen)
    {
        ADS_ERROR_LOG(pstTmrOperate->ulPid,
            "ADS_StartTimer: timer len is 0,");
        return;
    }

    /* 定时器已运行 */
    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        return;
    }

    /* 启动定时器 */
    if (VOS_NULL_PTR == pstTmrOperate->pfnTimerStartCallBack)
    {
        ulRet = VOS_StartRelTimer(&(pstTiCtx->hTimer),
                                  pstTmrOperate->ulPid,
                                  ulLen,
                                  enTimerId,
                                  0,
                                  VOS_RELTIMER_NOLOOP,
                                  pstTmrOperate->enPrecision);
    }
    else
    {
        ulRet = VOS_StartCallBackRelTimer(&(pstTiCtx->hTimer),
                                          pstTmrOperate->ulPid,
                                          ulLen,
                                          enTimerId,
                                          0,
                                          VOS_RELTIMER_NOLOOP,
                                          pstTmrOperate->pfnTimerStartCallBack,
                                          pstTmrOperate->enPrecision);
    }

    if (VOS_OK != ulRet)
    {
        ADS_ERROR_LOG1(pstTmrOperate->ulPid,
            "ADS_StartTimer: timer start failed! <ret>", ulRet);
        return;
    }

    /*勾包ADS_TIMER_INFO_STRU*/
    ADS_MNTN_TraceTimerOperation(pstTmrOperate->ulPid, enTimerId, ulLen, ADS_TIMER_OPERATION_START, ADS_TIMER_STOP_CAUSE_ENUM_BUTT);

    return;
}


VOS_VOID ADS_StopTimer(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx = VOS_NULL_PTR;

    /* 不在使用的定时器范围内 */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_UL,
            "ADS_StopTimer: timer id is invalid. <enTimerId>", enTimerId);
        return;
    }

    /* 获取定时器上下文 */
    pstTiCtx = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    /* 停止定时器 */
    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstTiCtx->hTimer));
    }

    /*勾包ADS_TIMER_INFO_STRU*/
    ADS_MNTN_TraceTimerOperation(ulPid, enTimerId, 0, ADS_TIMER_OPERATION_STOP, enStopCause);

    return;
}


ADS_TIMER_STATUS_ENUM_UINT8 ADS_GetTimerStatus(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx = VOS_NULL_PTR;

    /* 不在使用的定时器范围内 */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        return ASD_TIMER_STATUS_BUTT;
    }

    /* 获取定时器上下文 */
    pstTiCtx = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    /* 检查定时器句柄 */
    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        return ADS_TIMER_STATUS_RUNNING;
    }

    return ADS_TIMER_STATUS_STOP;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
