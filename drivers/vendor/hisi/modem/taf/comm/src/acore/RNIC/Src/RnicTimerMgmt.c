

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "RnicTimerMgmt.h"
#include "RnicCtx.h"
#include "v_timer.h"
#include "RnicLog.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_TIMERMGMT_C
/*lint -e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : RNIC_InitAllTimers
 功能描述  : 初始化所有定时器，应在RNIC初始化及Reset时被调用
 输入参数  : pstRnicTimerCtx:定时器上下文首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月12日
   作    者   : 范晶/f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  RNIC_InitAllTimers(
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 函 数 名  : RNIC_StartTimer
 功能描述  : 启动指定的RNIC定时器
 输入参数  : enTimerId:需要启动的定时器ID
             ulLen    :定时器长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月12日
   作    者   : 范晶/f00179208
   修改内容   : 新生成函数

  2.日    期   : 2012年5月22日
    作    者   : A00165503
    修改内容   : DTS2012052202998: 系统在休眠状态下, 按需拨号最大闲置时间到
                 达后, 拨号无法自动断开, 定时器需要使用32K时钟源

  3.日    期   : 2012年6月6日
    作    者   : z60575
    修改内容   : DTS2012060508406，按需断开时长不准问题修改

  4.日    期   : 2012年11月23日
    作    者   : f00179208
    修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt     = VOS_NULL_PTR;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;
    VOS_UINT32                          ulRet;

    /* 目前按需拨号的功能只在网卡0上有 */
    pstNetCntxt      = RNIC_GET_SPEC_NET_CTX(RNIC_RMNET_ID_0);
    pstRnicTimerCtx  = RNIC_GetTimerAddr();
    enTimerPrecision = VOS_TIMER_PRECISION_5;

    /* 不在使用的定时器范围内 */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* 输入参数检查 */
    if (0 == ulLen)
    {
        RNIC_ERROR_LOG1(ACPU_PID_ADS_UL, "ADS_StartTimer:ulLen is",ulLen);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果还未设置唤醒源标志，并且是按需断开定时器，则设置该标志，并且设置32K时钟为唤醒源 */
    if ((VOS_FALSE == RNIC_GetTimer4WakeFlg())
      && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_SetTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_TRUE);
    }
#endif

     /* 如果是流量上报定时器，则挂在26M时钟上，以降低功耗 */
    if (RNIC_IS_DSFLOW_TIMER_ID(enTimerId))
    {
        enTimerPrecision = VOS_TIMER_NO_PRECISION;
    }


    /* VOS_StartRelTimer 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer),
                              ACPU_PID_RNIC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              enTimerPrecision);
    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");
        return;
    }

    if (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId)
    {
        /* 按需拨号统计清零 */
        pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum = 0;
    }

    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_RUNING;


    /* 定时器状态勾包出来 */

}


/*****************************************************************************
 函 数 名  : RNIC_StopTimer
 功能描述  : 停止指定的RNIC定时器
 输入参数  : enTimerId:需要停止的定时器ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月12日
   作    者   : 范晶/f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年6月6日
   作    者   : z60575
   修改内容   : DTS2012060508406，按需断开时长不准问题修改
*****************************************************************************/
VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    /* 不在使用的定时器范围内 */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* 没有启动则不需要停止 */
    if (RNIC_TIMER_STATUS_RUNING  != pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstRnicTimerCtx[enTimerId].hTimer)
    {
        VOS_StopRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer));
    }

    pstRnicTimerCtx[enTimerId].hTimer        = VOS_NULL_PTR;
    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_STOP;

    /* 定时器状态勾包出来 */
#if (FEATURE_ON == FEATURE_LTE)
    /* 如果已经设置了唤醒源标志，并且是按需断开定时器，则清除该标志，并且设置32K时钟为非唤醒源 */
    if ((VOS_TRUE == RNIC_GetTimer4WakeFlg())
     && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
#endif
}


/*****************************************************************************
 函 数 名  : RNIC_StopAllTimer
 功能描述  : 停止RNIC的所有定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月12日
   作    者   : 范晶/f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年6月6日
   作    者   : z60575
   修改内容   : DTS2012060508406，按需断开时长不准问题修改
*****************************************************************************/
VOS_VOID  RNIC_StopAllTimer( VOS_VOID )
{

    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if (RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus)
        {
            /* 停止VOS定时器 */
            VOS_StopRelTimer(&(pstRnicTimerCtx[i].hTimer));

            pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果已经设置了唤醒源标志，则清除该标志，并且设置32K时钟为非唤醒源 */
    if (VOS_TRUE == RNIC_GetTimer4WakeFlg())
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
#endif
}


/*****************************************************************************
 函 数 名  : RNIC_GetTimerStatus
 功能描述  : 查询指定的RNIC定时器的状态
 输入参数  : enTimerId:需要查询的定时器ID
 输出参数  : 无
 返 回 值  : RNIC_TIMER_STATUS_ENUM_UINT8:定时器状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月12日
   作    者   : 范晶/f00179208
   修改内容   : 新生成函数
*****************************************************************************/
RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          ulLeftLen;

    pstRnicTimerCtx = RNIC_GetTimerAddr();
    ulLeftLen       = 0;

    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return RNIC_TIMER_STATUS_STOP;
    }

    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        if (VOS_OK != (VOS_GetRelTmRemainTime(&(pstRnicTimerCtx[enTimerId].hTimer), &ulLeftLen)))
        {
            RNIC_StopTimer(enTimerId);
            return RNIC_TIMER_STATUS_STOP;
        }
        else
        {
            return RNIC_TIMER_STATUS_RUNING;
        }
    }

    return RNIC_TIMER_STATUS_STOP;

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

