
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

/*****************************************************************************
 函 数 名  : ADS_MNTN_TraceTimerOperation
 功能描述  : 发送消息给OM模块，ADS定时器运行状态
 输入参数  : ulPid         - PID
             enTimerId     - 定时器ID
             ulTimerLen    - 定时器时长
             enTimerStatus - 定时器状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月22日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  ADS_MNTN_TraceTimerOperation(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulTimerLen,
    ADS_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
)
{
    ADS_TIMER_INFO_STRU                 stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(ADS_TIMER_INFO_STRU));

    stMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid       = ulPid;
    stMsg.ulReceiverPid     = VOS_PID_TIMER;
    stMsg.ulLength          = sizeof(ADS_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stMsg.enTimerId         = enTimerId;
    stMsg.ulTimerLen        = ulTimerLen;
    stMsg.enTimerAction     = enTimerAction;
    stMsg.enTimerStopCause  = enStopCause;

    DIAG_TraceReport(&stMsg);

    return;
}


/*****************************************************************************
 函 数 名  : ADS_StartTimer
 功能描述  : ADS启动定时器
 输入参数  : VOS_UINT32                          ulPid
             ADS_TIMER_ID_ENUM_UINT32            enTimerId
             VOS_UINT32                          ulLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化

  3.日    期   : 2016年01月25日
    作    者   : w00316404
    修改内容   : DTS2016010709647: 定时器使用句柄判断并优化
*****************************************************************************/
VOS_VOID  ADS_StartTimer(
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulLen
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx;
    ADS_TIMER_OPERATE_STRU              stTmrOperate;
    VOS_UINT32                          ulRet;

    stTmrOperate = g_astAdsTmrOperateTbl[enTimerId];

    /* 不在使用的定时器范围内 */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_UL, "ADS_StartTimer: timer id is invalid.", enTimerId);
        return;
    }

    /* 定时器长度检查 */
    if (0 == ulLen)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_StartTimer: timer len is 0,");
        return;
    }

    pstTiCtx = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        return;
    }

    if (VOS_NULL_PTR == stTmrOperate.pfnTimerStartCallBack)
    {
        ulRet = VOS_StartRelTimer(&(pstTiCtx->hTimer),
                                  stTmrOperate.ulPid,
                                  ulLen,
                                  enTimerId,
                                  0,
                                  VOS_RELTIMER_NOLOOP,
                                  stTmrOperate.enPrecision);
    }
    else
    {
        ulRet = VOS_StartCallBackRelTimer(&(pstTiCtx->hTimer),
                                           stTmrOperate.ulPid,
                                           ulLen,
                                           enTimerId,
                                           0,
                                           VOS_RELTIMER_NOLOOP,
                                           stTmrOperate.pfnTimerStartCallBack,
                                           stTmrOperate.enPrecision);
    }

    if (VOS_OK != ulRet)
    {
        ADS_ERROR_LOG(stTmrOperate.ulPid, "ADS_StartTimer:timer is fail start!");
        return;
    }

    pstTiCtx->enTimerStatus = ADS_TIMER_STATUS_RUNNING;

    /*勾包ADS_TIMER_INFO_STRU*/
    ADS_MNTN_TraceTimerOperation(stTmrOperate.ulPid, enTimerId, ulLen, ADS_TIMER_OPERATION_START, ADS_TIMER_STOP_CAUSE_ENUM_BUTT);

    return;
}

/*****************************************************************************
 函 数 名  : ADS_StopTimer
 功能描述  : ADS停止定时器
 输入参数  : VOS_UINT32                          ulPid
             ADS_TIMER_ID_ENUM_UINT32            enTimerId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_StopTimer(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx;

    pstTiCtx = ADS_GetTiCtx();

    /* 不在使用的定时器范围内 */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstTiCtx[enTimerId].hTimer)
    {
        VOS_StopRelTimer(&(pstTiCtx[enTimerId].hTimer));
    }

    pstTiCtx[enTimerId].hTimer        = VOS_NULL_PTR;
    pstTiCtx[enTimerId].enTimerStatus = ADS_TIMER_STATUS_STOP;

    /*勾包ADS_TIMER_INFO_STRU*/
    ADS_MNTN_TraceTimerOperation(ulPid, enTimerId, 0, ADS_TIMER_OPERATION_STOP, enStopCause);

    return;
}

/*****************************************************************************
 函 数 名  : ADS_GetTimerStatus
 功能描述  : 获取ADS定时器的状态
 输入参数  : VOS_UINT32                          ulPid
             ADS_TIMER_ID_ENUM_UINT32            enTimerId
 输出参数  : 无
 返 回 值  : ADS_TIMER_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2013年9月22日
    作    者   : A00165503
    修改内容   : DTS2013092200927: 定时器使用优化
*****************************************************************************/
ADS_TIMER_STATUS_ENUM_UINT8 ADS_GetTimerStatus(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pstTiCtx  = ADS_GetTiCtx();

    enTimerStatus = ADS_TIMER_STATUS_STOP;

    if (enTimerId < ADS_MAX_TIMER_NUM)
    {
        enTimerStatus = pstTiCtx[enTimerId].enTimerStatus;
    }

    return enTimerStatus;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
