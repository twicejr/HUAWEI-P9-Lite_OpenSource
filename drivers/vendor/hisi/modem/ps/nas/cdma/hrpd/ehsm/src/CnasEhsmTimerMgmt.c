

#include "PsCommonDef.h"
#include "CnasEhsmCtx.h"
#include "CnasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_TIMER_MGMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID  CNAS_EHSM_SndOmTimerStatus(
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen
)
{
    CNAS_EHSM_TIMER_INFO_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_EHSM_TIMER_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_EHSM,
                sizeof(CNAS_EHSM_TIMER_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_EHSM;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_EHSM_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_EHSM, pstMsg);
}


VOS_VOID  CNAS_EHSM_StartTimer(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen
)
{
    CNAS_EHSM_TIMER_CTX_STRU            *pstEhsmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                           i;
    VOS_UINT32                           ulRet;

    if (0 == ulLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
       ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    pstEhsmTimerCtx   =  CNAS_EHSM_GetTimerCtxAddr();

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for (i = 0 ; i < TI_CNAS_EHSM_TIMER_BUTT ; i++)
    {
        if ((CNAS_EHSM_TIMER_STATUS_RUNING == pstEhsmTimerCtx[i].enTimerStatus)
         && (enTimerId                     == pstEhsmTimerCtx[i].enTimerId))
        {
            CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_StartTimer:timer is running!", (VOS_INT32)enTimerId);

            return;
        }
    }

    for (i = 0 ; i < TI_CNAS_EHSM_TIMER_BUTT ; i++)
    {
        if (CNAS_EHSM_TIMER_STATUS_STOP == pstEhsmTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= TI_CNAS_EHSM_TIMER_BUTT)
    {
       CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_StartTimer: timer resource is not enough", (VOS_INT32)enTimerId);

       return;
    }

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstEhsmTimerCtx[i].hTimer),
                              UEPS_PID_EHSM,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if (VOS_OK != ulRet)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM,"CNAS_EHSM_StartTimer:VOS_StartRelTimer failed");

        return;
    }

    pstEhsmTimerCtx[i].enTimerId     = enTimerId;
    pstEhsmTimerCtx[i].enTimerStatus = CNAS_EHSM_TIMER_STATUS_RUNING;

    CNAS_EHSM_SndOmTimerStatus(CNAS_EHSM_TIMER_STATUS_RUNING, enTimerId, ulLen);

    return;
}



VOS_VOID  CNAS_EHSM_StopTimer(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId
)
{
    CNAS_EHSM_TIMER_CTX_STRU           *pstEhsmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEhsmTimerCtx   =  CNAS_EHSM_GetTimerCtxAddr();

    for (i = 0; i < TI_CNAS_EHSM_TIMER_BUTT; i++)
    {
        if ((CNAS_EHSM_TIMER_STATUS_RUNING == pstEhsmTimerCtx[i].enTimerStatus)
         && (enTimerId                     == pstEhsmTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= TI_CNAS_EHSM_TIMER_BUTT)
    {
        CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_StopTimer:timer already stopped", (VOS_INT32)enTimerId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstEhsmTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstEhsmTimerCtx[i].hTimer));
    }

    pstEhsmTimerCtx[i].hTimer            = VOS_NULL_PTR;
    pstEhsmTimerCtx[i].enTimerId         = TI_CNAS_EHSM_TIMER_BUTT;
    pstEhsmTimerCtx[i].enTimerStatus     = CNAS_EHSM_TIMER_STATUS_STOP;

    CNAS_EHSM_SndOmTimerStatus(CNAS_EHSM_TIMER_STATUS_STOP, enTimerId, 0);
}



CNAS_EHSM_TIMER_STATUS_ENUM_UINT8  CNAS_EHSM_GetTimerStatus(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId
)
{
    CNAS_EHSM_TIMER_CTX_STRU           *pstEhsmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus;

    pstEhsmTimerCtx = CNAS_EHSM_GetTimerCtxAddr();

    enTimerStatus  = CNAS_EHSM_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for (i = 0 ; i < TI_CNAS_EHSM_TIMER_BUTT; i++)
    {
        if (enTimerId    == pstEhsmTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstEhsmTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


