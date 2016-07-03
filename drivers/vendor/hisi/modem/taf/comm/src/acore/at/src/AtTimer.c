

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "AtTimer.h"
#include  "ATCmdProc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_TIMER_C
/*lint +e960*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/



VOS_UINT32 AT_StartRelTimer(
    HTIMER                             *phTm,
    VOS_UINT32                          ulLength,
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulParam,
    VOS_UINT8                           ucMode
)
{
    VOS_UINT32                          ulRet;
    AT_TIMER_OPERATION_STRU             stTimer;

    if (0 == ulLength)
    {
        AT_ERR_LOG("AT_StartRelTimer: Start Rel Timer Length is 0!");
        return VOS_ERR;
    }

    if ( ulLength >= VOS_TIMER_MAX_LENGTH )
    {
        ulLength = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulRet = VOS_StartRelTimer(phTm, WUEPS_PID_AT, ulLength, ulName, ulParam, ucMode, VOS_TIMER_PRECISION_5);

    if (VOS_ERR == ulRet)
    {
        AT_ERR_LOG("AT_StartRelTimer: Start Rel Timer Fail!");
    }

    stTimer.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stTimer.ulSenderPid     = WUEPS_PID_AT;
    stTimer.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stTimer.ulReceiverPid   = VOS_PID_TIMER;
    stTimer.ulLength        = sizeof(AT_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;
    stTimer.ulMsgName       = ulName;
    stTimer.enTimeAction    = AT_TIMER_OPERATION_START;
    stTimer.ulTimeLen       = ulLength;

    DIAG_TraceReport(&stTimer);

    return ulRet;
}


VOS_UINT32 AT_StopRelTimer(
    VOS_UINT32                          ulName,
    HTIMER                             *phTm
)
{
    VOS_UINT32                          ulRet;
    AT_TIMER_OPERATION_STRU             stTimer;

    ulRet = VOS_StopRelTimer(phTm);

    if (VOS_ERR == ulRet)
    {
        AT_ERR_LOG("AT_StopRelTimer: Stop Rel Timer Fail!");
    }

    stTimer.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stTimer.ulSenderPid     = WUEPS_PID_AT;
    stTimer.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stTimer.ulReceiverPid   = VOS_PID_TIMER;
    stTimer.ulLength        = sizeof(AT_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;
    stTimer.ulMsgName       = ulName;
    stTimer.enTimeAction    = AT_TIMER_OPERATION_STOP;
    stTimer.ulTimeLen       = 0x0;

    DIAG_TraceReport(&stTimer);

    return ulRet;
}


VOS_UINT32 At_StartTimer(
    VOS_UINT32                          usLength,
    VOS_UINT8                           ucIndex
)
{
    VOS_StopRelTimer(&gastAtClientTab[ucIndex].hTimer);
    if(VOS_OK != AT_StartRelTimer(&gastAtClientTab[ucIndex].hTimer,usLength,ucIndex,0,VOS_RELTIMER_NOLOOP))
    {
        AT_ERR_LOG("At_StartTimer:ERROR:Start Timer");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
