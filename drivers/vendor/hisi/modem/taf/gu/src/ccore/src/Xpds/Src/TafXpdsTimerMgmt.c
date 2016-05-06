/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsTimerMgmt.c
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年8月21日
  最近修改   :
  功能描述   : XPDS模块定时器实现和资源管理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : A-GPS项目新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define     THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_TIMER_MGMT_C

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsMntn.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数申明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndOmTimerStatus
 功能描述  : TAF 将 XPDS 定时器状态发送给 OM
 输入参数  : enTimerStatus 定时器状态,
             enTimerId     定时器ID,
             ulLen         定时器时长
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_XPDS_SndOmTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen,
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus
)
{
    TAF_XPDS_TIMER_INFO_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_TIMER_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_XPDS,
                             sizeof(TAF_XPDS_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndOmTimerStatus:ERROR:Alloc Mem Fail.");

        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_XPDS_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_InitAllTimers
 功能描述  : 初始化所有定时器，应在XPDS初始化时被调用
 输入参数  : pstXpdsTimerCtx - 定时器上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_XPDS_InitAllTimers(
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        pstXPDSTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstXPDSTimerCtx[i].enTimerId     = TI_TAF_XPDS_TIMER_BUTT;
        pstXPDSTimerCtx[i].enTimerStatus = TAF_XPDS_TIMER_STATUS_STOP;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_StartTimer
 功能描述  : 启动指定的XPDS定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen     - 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XPDS_TIMER_START_RESULT_ENUM_UINT8 TAF_XPDS_StartTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
)
{
    TAF_XPDS_TIMER_CTX_STRU            *pstXpdsTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if ( enTimerId >= TI_TAF_XPDS_TIMER_BUTT)
    {
        return TAF_XPDS_TIMER_START_FAILURE;
    }

    pstXpdsTimerCtx = TAF_XPDS_GetTimerCtxAddr();

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_XPDS_TIMER_STATUS_RUNING == pstXpdsTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstXpdsTimerCtx[i].enTimerId))
        {
            XPDS_WARNING1_LOG("TAF_XPDS_StartTimer:timer is running!", (VOS_INT32)enTimerId);

            return TAF_XPDS_TIMER_START_FAILURE;
        }
    }

    /* 查找当前列表中未用的节点 */
    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if ( TAF_XPDS_TIMER_STATUS_STOP == pstXpdsTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (TAF_XPDS_CTX_MAX_TIMER_NUM == i)
    {
        XPDS_WARNING_LOG("TAF_XPDS_StartTimer: 10 timers are running!");

        return TAF_XPDS_TIMER_START_FAILURE;
    }

    /* 检查定时器时长 */
    if ( 0 == ulLen)
    {
        return TAF_XPDS_TIMER_START_FAILURE;
    }
    else if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }
    else
    {

    }

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstXpdsTimerCtx[i].hTimer),
                              UEPS_PID_XPDS,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if ( VOS_OK != ulRet)
    {
        XPDS_WARNING_LOG("TAF_XPDS_StartTimer:VOS_StartRelTimer failed");

        return TAF_XPDS_TIMER_START_FAILURE;
    }

    pstXpdsTimerCtx[i].enTimerId     = enTimerId;
    pstXpdsTimerCtx[i].enTimerStatus = TAF_XPDS_TIMER_STATUS_RUNING;

    /* 定时器状态勾包出来 */
    TAF_XPDS_SndOmTimerStatus(enTimerId, ulLen, TAF_XPDS_TIMER_STATUS_RUNING);

    return TAF_XPDS_TIMER_START_SUCCEE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_StopTimer
 功能描述  : 停止指定的XPDS定时器
 输入参数  : enTimerId - 需要停止的定时器ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_XPDS_StopTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx;
    VOS_UINT32                          i;

    pstXPDSTimerCtx   =  TAF_XPDS_GetTimerCtxAddr();

    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_XPDS_TIMER_STATUS_RUNING  == pstXPDSTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstXPDSTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_XPDS_CTX_MAX_TIMER_NUM)
    {
        XPDS_WARNING1_LOG("TAF_XPDS_StopTimer:timer already stopped!", (VOS_INT32)enTimerId);

        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstXPDSTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstXPDSTimerCtx[i].hTimer));
    }

    pstXPDSTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstXPDSTimerCtx[i].enTimerId     = TI_TAF_XPDS_TIMER_BUTT;
    pstXPDSTimerCtx[i].enTimerStatus = TAF_XPDS_TIMER_STATUS_STOP;

    /* 定时器状态勾包出来 */
    TAF_XPDS_SndOmTimerStatus(enTimerId, 0, TAF_XPDS_TIMER_STATUS_STOP);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetTimerStatus
 功能描述  : 获取指定的XPDS定时器运行状态
 输入参数  : enTimerId - 需要获取运行状态的定时器ID
 输出参数  : 无
 返 回 值  : TAF_XPDS_TIMER_STATUS_ENUM_UINT8 - 定时器运行状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XPDS_TIMER_STATUS_ENUM_UINT8  TAF_XPDS_GetTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx;
    VOS_UINT32                          i;
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;

    pstXPDSTimerCtx = TAF_XPDS_GetTimerCtxAddr();

    enTimerStatus   = TAF_XPDS_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if (enTimerId == pstXPDSTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstXPDSTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_StopAllTimer
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_StopAllTimer(VOS_VOID)
{
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId;

    for (enTimerId = TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND;enTimerId < TI_TAF_XPDS_TIMER_BUTT;enTimerId++)
    {
        TAF_XPDS_StopTimer(enTimerId);
    }
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

