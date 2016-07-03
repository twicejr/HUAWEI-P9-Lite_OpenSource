

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


    NAS_TIMER_EventReport((VOS_UINT32)enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_START);

    return VOS_TRUE;

}



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



    if (0!=ulTimerRemainLen)
    {
        NAS_TIMER_EventReport(enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_STOP);
    }


    /* 定时器状态勾包出来 */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, enTimerId, ulTimerRemainLen * 10);




}



VOS_VOID  NAS_MMC_StopAllTimer( VOS_VOID )
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
        {
            if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
            {
                ulTimerRemainLen = 0;
            }

            /* 停止VOS定时器 */
            (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));

            NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, pstMmcTimerCtx[i].enTimerId, ulTimerRemainLen * 10);

            pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
            pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
        }
    }
}



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

