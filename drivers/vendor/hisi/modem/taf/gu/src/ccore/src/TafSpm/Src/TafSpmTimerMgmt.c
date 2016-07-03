

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafSpmCtx.h"
#include  "PsCommonDef.h"
#include  "TafLog.h"
#include "TafSpmTimerMgmt.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_TAF_SPM_TIMERMGMT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID  TAF_SPM_SndOmTimerStatus(
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                             sizeof(TAF_SPM_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_SPM_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_SPM_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->usClientId                  = usClientId;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

}



VOS_VOID  TAF_SPM_StartTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_CTX_STRU             *pstSpmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    pstSpmTimerCtx   =  TAF_SPM_GetTimerCtxAddr();

    if (0 == ulLen)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_SPM_StartTimer:timer len is zero!", (VOS_INT32)enTimerId, usClientId);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
       ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        if ((TAF_SPM_TIMER_STATUS_RUNING == pstSpmTimerCtx[i].enTimerStatus)
         && (enTimerId                   == pstSpmTimerCtx[i].enTimerId)
         && (usClientId                  == pstSpmTimerCtx[i].usClientId))
        {
            TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_SPM_StartTimer:timer is running!", (VOS_INT32)enTimerId, usClientId);
            return;
        }
    }

    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        if (TAF_SPM_TIMER_STATUS_STOP == pstSpmTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= TAF_SPM_MAX_TIMER_NUM)
    {
       TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_SPM_StartTimer:too many timer", (VOS_INT32)enTimerId, usClientId);

       return;
    }

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstSpmTimerCtx[i].hTimer),
                              WUEPS_PID_TAF,
                              ulLen,
                              enTimerId,
                              usClientId,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_SPM_StartTimer:VOS_StartRelTimer failed");
        return;
    }

    pstSpmTimerCtx[i].enTimerId             = enTimerId;
    pstSpmTimerCtx[i].enTimerStatus         = TAF_SPM_TIMER_STATUS_RUNING;
    pstSpmTimerCtx[i].usClientId            = usClientId;

    TAF_SPM_SndOmTimerStatus(TAF_SPM_TIMER_STATUS_RUNING, enTimerId, ulLen, usClientId);

    return;
}


VOS_VOID  TAF_SPM_StopTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_CTX_STRU             *pstSpmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstSpmTimerCtx   =  TAF_SPM_GetTimerCtxAddr();

    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        if ((TAF_SPM_TIMER_STATUS_RUNING  == pstSpmTimerCtx[i].enTimerStatus)
         && (enTimerId                    == pstSpmTimerCtx[i].enTimerId)
         && (usClientId                   == pstSpmTimerCtx[i].usClientId))
        {
            break;
        }
    }

    if (i >= TAF_SPM_MAX_TIMER_NUM)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_SPM_StopTimer:timer already stoppe", (VOS_INT32)enTimerId, usClientId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstSpmTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstSpmTimerCtx[i].hTimer));
    }

    pstSpmTimerCtx[i].hTimer            = VOS_NULL_PTR;
    pstSpmTimerCtx[i].enTimerId         = TI_TAF_SPM_TIMER_BUTT;
    pstSpmTimerCtx[i].enTimerStatus     = TAF_SPM_TIMER_STATUS_STOP;
    pstSpmTimerCtx[i].usClientId        = TAF_SPM_INVALID_CLIENT_ID;

    TAF_SPM_SndOmTimerStatus(TAF_SPM_TIMER_STATUS_STOP, enTimerId, 0, usClientId);
}





TAF_SPM_TIMER_STATUS_ENUM_UINT8  TAF_SPM_GetTimerStatus(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_CTX_STRU             *pstSpmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;

    pstSpmTimerCtx = TAF_SPM_GetTimerCtxAddr();

    enTimerStatus  = TAF_SPM_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM; i++)
    {
        if ((enTimerId    == pstSpmTimerCtx[i].enTimerId)
         && (usClientId   == pstSpmTimerCtx[i].usClientId))
        {
            enTimerStatus = pstSpmTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}


VOS_VOID  TAF_SPM_InitAllTimers(
    TAF_SPM_TIMER_CTX_STRU              *pstSpmTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        pstSpmTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstSpmTimerCtx[i].enTimerId     = TI_TAF_SPM_TIMER_BUTT;
        pstSpmTimerCtx[i].enTimerStatus = TAF_SPM_TIMER_STATUS_STOP;
        pstSpmTimerCtx[i].usClientId    = TAF_SPM_INVALID_CLIENT_ID;
        pstSpmTimerCtx[i].aucReserve[0] = 0;
    }
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

