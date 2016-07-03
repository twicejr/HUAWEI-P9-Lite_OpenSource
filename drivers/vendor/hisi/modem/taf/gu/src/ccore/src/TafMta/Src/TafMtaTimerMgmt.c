

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define     THIS_FILE_ID        PS_FILE_ID_TAF_MTA_TIMER_MGMT_C


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaComm.h"
#include "TafMtaCtx.h"
#include "TafMtaTimerMgmt.h"

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_MTA_TIMER_PRECISION_STRU g_astTafMtaTimerPrecisionTab[]=
{
   {TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,      VOS_TIMER_NO_PRECISION}
};

/*****************************************************************************
  3 函数申明
*****************************************************************************/


VOS_VOID  TAF_MTA_SndOmTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus
)
{
    /*lint -e958*/
    TAF_MTA_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    /*lint +e958*/

    pstMsg = (TAF_MTA_TIMER_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MTA,
                             sizeof(TAF_MTA_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_MTA;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MTA_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MTA, pstMsg);

    return;
}


VOS_TIMER_PRECISION_ENUM_UINT32 TAF_MTA_GetTimerPrecision(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
   /*定时器分为两种，26M定时器和32K定时器，
         26M定时器，系统开销少，推荐使用，但当DRX睡眠时，停止计数，可能计时不准。
         32K定时器，系统开销大，不推荐使用，但计时准确，
         当选择无精度要求时(VOS_TIMER_NO_PRECISION)，启动26M定时器
         其他有精度要求的，启动32K定时器。
     定时器选择依据:
       1）对IDLE态下定时器，要求定时器必须是精确定时的，包括我们异常保护定时器中
          自己设计的要求绝对定时的； 协议定时器中必须绝对定时的，比如说必须绝对
          定时才能通过GCF用例； 对这类定时器，使用32K定时器；
       2）其他IDLE定时器，不需要绝对定时的：挂到26M定时器；
       3）非IDLE态的定时器，使用26M定时器 */

    VOS_UINT32                      i;
    VOS_TIMER_PRECISION_ENUM_UINT32 ulPrecision;

    /* 默认精度为32K */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for(i=0; i<( sizeof(g_astTafMtaTimerPrecisionTab)/sizeof(TAF_MTA_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_astTafMtaTimerPrecisionTab[i].enTimerId)
        {
            ulPrecision = g_astTafMtaTimerPrecisionTab[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}


VOS_VOID  TAF_MTA_InitAllTimers(
    TAF_MTA_TIMER_CTX_STRU              *pstMtaTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        pstMtaTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstMtaTimerCtx[i].enTimerId     = TI_TAF_MTA_TIMER_BUTT;
        pstMtaTimerCtx[i].enTimerStatus = TAF_MTA_TIMER_STATUS_STOP;
    }

    return;
}



TAF_MTA_TIMER_START_RESULT_ENUM_UINT8  TAF_MTA_StartTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
)
{
    TAF_MTA_TIMER_CTX_STRU             *pstMtaTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    if ( enTimerId >= TI_TAF_MTA_TIMER_BUTT)
    {
        MTA_WARNING1_LOG("TAF_MTA_StartTimer:Error TimerId!", (VOS_INT32)enTimerId);
        return TAF_MTA_TIMER_START_FAILURE;
    }

    pstMtaTimerCtx   =  TAF_MTA_GetTimerCtxAddr();

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_MTA_TIMER_STATUS_RUNING == pstMtaTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstMtaTimerCtx[i].enTimerId))
        {
            MTA_WARNING1_LOG("TAF_MTA_StartTimer:timer is running!", (VOS_INT32)enTimerId);
            return TAF_MTA_TIMER_START_FAILURE;
        }
    }

    /* 查找当前列表中未用的节点 */
    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if ( TAF_MTA_TIMER_STATUS_STOP == pstMtaTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (TAF_MTA_CTX_MAX_TIMER_NUM == i)
    {
        MTA_WARNING_LOG("TAF_MTA_StartTimer: five timers are running!");
        return TAF_MTA_TIMER_START_FAILURE;
    }

    /* 检查定时器时长 */
    if ( 0 == ulLen)
    {
        MTA_WARNING1_LOG("TAF_MTA_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return TAF_MTA_TIMER_START_FAILURE;
    }
    else if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }
    else
    {

    }
    ulPrecision = TAF_MTA_GetTimerPrecision(enTimerId);

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstMtaTimerCtx[i].hTimer),
                              UEPS_PID_MTA,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        MTA_WARNING_LOG("TAF_MTA_StartTimer:VOS_StartRelTimer failed");
        return TAF_MTA_TIMER_START_FAILURE;
    }

    pstMtaTimerCtx[i].enTimerId     = enTimerId;
    pstMtaTimerCtx[i].enTimerStatus = TAF_MTA_TIMER_STATUS_RUNING;

    /* 定时器状态勾包出来 */
    TAF_MTA_SndOmTimerStatus(enTimerId, ulLen, TAF_MTA_TIMER_STATUS_RUNING);

    return TAF_MTA_TIMER_START_SUCCEE;
}


VOS_VOID  TAF_MTA_StopTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    TAF_MTA_TIMER_CTX_STRU             *pstMtaTimerCtx;
    VOS_UINT32                          i;

    pstMtaTimerCtx   =  TAF_MTA_GetTimerCtxAddr();

    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_MTA_TIMER_STATUS_RUNING  == pstMtaTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMtaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_MTA_CTX_MAX_TIMER_NUM)
    {
        MTA_WARNING1_LOG("TAF_MTA_StopTimer:timer already stopped!", (VOS_INT32)enTimerId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstMtaTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstMtaTimerCtx[i].hTimer));
    }

    pstMtaTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstMtaTimerCtx[i].enTimerId     = TI_TAF_MTA_TIMER_BUTT;
    pstMtaTimerCtx[i].enTimerStatus = TAF_MTA_TIMER_STATUS_STOP;

    /* 定时器状态勾包出来 */
    TAF_MTA_SndOmTimerStatus(enTimerId, 0, TAF_MTA_TIMER_STATUS_STOP);

    return;
}


TAF_MTA_TIMER_STATUS_ENUM_UINT8  TAF_MTA_GetTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    TAF_MTA_TIMER_CTX_STRU             *pstMtaTimerCtx;
    VOS_UINT32                          i;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;

    pstMtaTimerCtx = TAF_MTA_GetTimerCtxAddr();

    enTimerStatus  = TAF_MTA_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if (enTimerId == pstMtaTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstMtaTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
