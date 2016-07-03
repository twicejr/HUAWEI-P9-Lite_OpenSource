

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsCtx.h"
#include  "TafApsTimerMgmt.h"
#include  "PsCommonDef.h"
#include  "TafLog.h"
#include  "TafApsMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_TAF_APS_TIMERMGMT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_APS_TIMER_PRECISION_STRU g_astTafApsTimerPrcisionTab[]=
{
   {TI_TAF_APS_DSFLOW_REPORT,      VOS_TIMER_NO_PRECISION}
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32  TAF_APS_BuildTmrParaByCtrlHdr(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulClientId
)
{
    /*
        由于PID扩展，ModuleId在组装定时器参数时需要同时考虑影响
        约束: ModuleId结构 Bit0~Bit11: 模块ID  Bit12~Bit15: 保留 Bit16~Bit19: CPU ID Bit20~Bit31: 保留
        例: ModuleID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
            ClientID: 0x0000abcd
            CtrlHdr : 0xABCDabcd
    */
    return (((((ulModuleId) & 0xF0000) | (((ulModuleId) & 0xFFF) << 4)) << 12) | (ulClientId));
}


VOS_TIMER_PRECISION_ENUM_UINT32 TAF_APS_GetTimerPrecision(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId
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

    for(i=0; i<( sizeof(g_astTafApsTimerPrcisionTab)/sizeof(TAF_APS_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_astTafApsTimerPrcisionTab[i].enTimerId)
        {
            ulPrecision = g_astTafApsTimerPrcisionTab[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}



VOS_VOID  TAF_APS_InitAllTimers(
    TAF_APS_TIMER_CTX_STRU              *pstApsTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
        pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
        pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;
        pstApsTimerCtx[i].aucReserve[0] = 0;
        pstApsTimerCtx[i].aucReserve[1] = 0;
        pstApsTimerCtx[i].aucReserve[2] = 0;

    }
}



VOS_VOID  TAF_APS_StartTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;
    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_APS_TIMER_STATUS_RUNING == pstApsTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstApsTimerCtx[i].enTimerId)
          && ( ulPara                      == pstApsTimerCtx[i].ulPara))
        {
            TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_StartTimer:timer is running!", (VOS_INT32)enTimerId, ulPara);
            return;
        }
    }

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_APS_TIMER_STATUS_STOP == pstApsTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= TAF_APS_MAX_TIMER_NUM)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_APS_StartTimer:too many timer!", (VOS_INT32)enTimerId, ulPara);
        return;
    }

    /* 检查定时器时长 */
    if ( 0 == ulLen)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_APS_StartTimer:timer len is zero!", (VOS_INT32)enTimerId, ulPara);
        return;
    }
    else if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }
    else
    {

    }
    ulPrecision = TAF_APS_GetTimerPrecision(enTimerId);

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstApsTimerCtx[i].hTimer),
                              WUEPS_PID_TAF,
                              ulLen,
                              enTimerId,
                              ulPara,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);
    if ( VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_StartTimer:VOS_StartRelTimer failed");
        return;
    }

    pstApsTimerCtx[i].enTimerId     = enTimerId;
    pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_RUNING;
    pstApsTimerCtx[i].ulPara        = ulPara;

    /* 定时器状态勾包出来 */
    TAF_APS_TraceTimer(TAF_APS_TIMER_STATUS_RUNING, enTimerId, ulLen, ulPara);

    return;
}


VOS_VOID  TAF_APS_StopTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;

    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_APS_TIMER_STATUS_RUNING  == pstApsTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstApsTimerCtx[i].enTimerId)
          && ( ulPara                       == pstApsTimerCtx[i].ulPara))
        {
            break;
        }
    }

    if ( i >= TAF_APS_MAX_TIMER_NUM)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_StopTimer:timer already stopped!", (VOS_INT32)enTimerId, ulPara);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstApsTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstApsTimerCtx[i].hTimer));
    }

    pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
    pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
    pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;

    /* 定时器状态勾包出来 */
    TAF_APS_TraceTimer(TAF_APS_TIMER_STATUS_STOP, enTimerId, 0, ulPara);

}



VOS_VOID  TAF_APS_StopAllTimer( VOS_VOID )
{

    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;

    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_APS_TIMER_STATUS_RUNING  == pstApsTimerCtx[i].enTimerStatus )
        {
            /* 停止VOS定时器 */
            if (VOS_NULL_PTR != pstApsTimerCtx[i].hTimer)
            {
                (VOS_VOID)VOS_StopRelTimer(&(pstApsTimerCtx[i].hTimer));
            }

            pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
            pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
            pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;
        }
    }

    return;
}



VOS_VOID  TAF_APS_StopPdpAllTimer(
    VOS_UINT32                          ulPara
)
{

    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;

    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_APS_TIMER_STATUS_RUNING  == pstApsTimerCtx[i].enTimerStatus )
          && ( ulPara  == pstApsTimerCtx[i].ulPara ))
        {
            /* 停止VOS定时器 */
            if (VOS_NULL_PTR != pstApsTimerCtx[i].hTimer)
            {
                (VOS_VOID)VOS_StopRelTimer(&(pstApsTimerCtx[i].hTimer));
            }

            pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
            pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
            pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;
        }
    }

    return;
}



TAF_APS_TIMER_STATUS_ENUM_U8  TAF_APS_GetTimerStatus(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    pstApsTimerCtx = TAF_APS_GetTimerCtxAddr();

    enTimerStatus  = TAF_APS_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( enTimerId == pstApsTimerCtx[i].enTimerId)
          && ( ulPara    == pstApsTimerCtx[i].ulPara))
        {
            enTimerStatus = pstApsTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}


VOS_VOID TAF_APS_GetRemainTimerLen(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulRemainTimeLen
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          ulRemainTick;
    VOS_UINT32                          i;

    pstApsTimerCtx = TAF_APS_GetTimerCtxAddr();
    ulRemainTick   = 0;

    for (i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++)
    {
        if ( (TAF_APS_TIMER_STATUS_RUNING == pstApsTimerCtx[i].enTimerStatus)
          && (enTimerId                   == pstApsTimerCtx[i].enTimerId)
          && (ulPara                      == pstApsTimerCtx[i].ulPara) )
        {
            break;
        }
    }

    if (i >= TAF_APS_MAX_TIMER_NUM)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_GetRemainTimerLen: Timer already stopped!", (VOS_INT32)enTimerId, ulPara);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_NULL_PTR == pstApsTimerCtx[i].hTimer)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_GetRemainTimerLen: Timer handle is null!", (VOS_INT32)enTimerId, ulPara);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstApsTimerCtx[i].hTimer), &ulRemainTick))
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_GetRemainTimerLen: Get remain time fail!", (VOS_INT32)enTimerId, ulPara);
        *pulRemainTimeLen = 0;
        return;
    }

    *pulRemainTimeLen = ulRemainTick * TI_TAF_APS_1_TICK_10_MS;
    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
