/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcTimer.c
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年5月30日
  最近修改   : 2011年5月30日
  功能描述   : 管理MMC定时器，以及进行超时处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月30日
    作    者   : zhoujun 40661
    修改内容   : 创建文件
  2.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer,
                  删除NAS_MMC_GetTimerRemainLen/NAS_MMC_SetTimerStopStatus

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "vos.h"
#include "Ps.h"
#include "NasComm.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcCtx.h"
#include "NasMmcSndOm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASMMC_TIMERMGMT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/* 这个表添加无精度定时器信息，默认32k */
NAS_TIMER_PRECISION_STRU g_stNasMmcTimerPrcision[]=
{
   {WUEPS_PID_MMC,  TI_NAS_MMC_TIMER_BUTT,       VOS_TIMER_NO_PRECISION},
};

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_MMC_InitAllTimers
 功能描述  : 初始化所有定时器，应在MMC初始化及Reset时被调用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月30日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_InitAllTimers(
    NAS_MMC_TIMER_CTX_STRU              *pstMmcTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
        pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_StartTimer
 功能描述  : 启动指定的MMC定时器
 输入参数  : enTimerId - 需要启动的定时器ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年5月30日
   作    者   : w00167002
   修改内容   : 增加定时器的时长打印

 3.日    期   : 2012年11月7日
   作    者   : l00167671
   修改内容   : 增加返回值，以便于调用者知道是否启动定时器成功。
                DTS2012110607212
 4.日    期   : 2013年6月14日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
5. 日    期   : 2013年06月28日
   作    者   : l00167671
   修改内容   : DCM LOGGER项目定时器事件上报
*****************************************************************************/
VOS_UINT32  NAS_MMC_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    if (0 == ulLen)
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return VOS_FALSE;
    }

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstMmcTimerCtx[i].enTimerId))
        {
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartTimer:timer is running", enTimerId);

            return VOS_FALSE;
        }
    }

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_STOP == pstMmcTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartTimer:too many timer", enTimerId);

        return VOS_FALSE;
    }

    if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_MMC_GetTimerPrecision(enTimerId);

    ulRet = VOS_StartRelTimer(&(pstMmcTimerCtx[i].hTimer),
                              WUEPS_PID_MMC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");

        return VOS_FALSE;
    }

    pstMmcTimerCtx[i].enTimerId     = enTimerId;
    pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_RUNING;


    /* 定时器状态勾包出来 */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_RUNING, enTimerId, ulLen);


    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    NAS_TIMER_EventReport((VOS_UINT32)enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_START);
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_StopTimer
 功能描述  : 停止指定的MMC定时器
 输入参数  : enTimerId - 需要停止的定时器ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月30日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年10月06日
    作    者   : z49106
    修改内容   : 定时器指针不为空的时候, 才停止定时器
  3.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印

  4.日    期   : 2012年8月21日
    作    者   : z40661
    修改内容   : DTS2012080208200,VOS_GetRelTmRemainTimehTimer时，未将tick转为ms。
  5.日    期   : 2013年06月28日
    作    者   : l00167671
    修改内容   : DCM LOGGER项目定时器事件上报
*****************************************************************************/
VOS_VOID  NAS_MMC_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;


    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMmcTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_StopTimer:Timer not running", enTimerId);

        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstMmcTimerCtx[i].hTimer)
    {


        /* 获取当前定时器的剩余时间 */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }



        (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));
    }

    pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
    pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;



    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    if (0!=ulTimerRemainLen)
    {
        NAS_TIMER_EventReport(enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_STOP);
    }
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */


    /* 定时器状态勾包出来 */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, enTimerId, ulTimerRemainLen * 10);




}


/*****************************************************************************
 函 数 名  : NAS_MMC_StopAllTimer
 功能描述  : 停止MMC的所有定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月30日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2014年3月12日
    作    者   : s00246516
    修改内容   : L-C互操作项目，增加可维可测信息
*****************************************************************************/
VOS_VOID  NAS_MMC_StopAllTimer( VOS_VOID )
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
        {
            /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
            if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
            {
                ulTimerRemainLen = 0;
            }

            /* 停止VOS定时器 */
            (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));

            NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, pstMmcTimerCtx[i].enTimerId, ulTimerRemainLen * 10);
            /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

            pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
            pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
        }
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetTimerStatus
 功能描述  : 查询指定的MMC定时器的状态
 输入参数  : enTimerId  - 需要查询的定时器ID
 输出参数  : 无
 返 回 值  : NAS_MMC_TIMER_STATUS_ENUM_U8:定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
*****************************************************************************/
NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_MMC_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    pstMmcTimerCtx = NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMmcTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        return NAS_MMC_TIMER_STATUS_STOP;
    }

    return NAS_MMC_TIMER_STATUS_RUNING;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetTimerPrecision
 功能描述  : 获取MMC模块定时器精度范围
 输入参数  : Pid       -- 启动定时器的PID
             ulName    -- 定时器名
 输出参数  : 无
 返 回 值  : VOS_TIMER_PRECISION_ENUM_UINT32 -- 定时器精度范围
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

 2.日    期   : 2013年9月4日
   作    者   : w00167002
   修改内容   : DTS2013090403562:NAS定时器清理，需要启动32K定时器。将MM/MMA/SMS
                模块的循环定时器修改为非循环定时器。
*****************************************************************************/
VOS_TIMER_PRECISION_ENUM_UINT32 NAS_MMC_GetTimerPrecision(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
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

    VOS_UINT32                          i;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;



    /* 默认为有精度要求，挂在32K时钟上 */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for ( i = 0; i < ( sizeof(g_stNasMmcTimerPrcision)/sizeof(NAS_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_stNasMmcTimerPrcision[i].ulTimerName)
        {
            ulPrecision = g_stNasMmcTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

