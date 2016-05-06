/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsTimerMgmt.c
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月13日
  最近修改   :
  功能描述   : 管理APS定时器，以及进行超时处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月13日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

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
/*****************************************************************************
 函 数 名  : TAF_APS_BuildTmrParaByCtrlHdr
 功能描述  : 组装定时器的参数
 输入参数  : pstCtrl        - 消息头
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseIII 项目新增

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
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

/*****************************************************************************
 函 数 名  : TAF_APS_GetTimerPrecision
 功能描述  : 获取定时器精度范围
 输入参数  : enTimerId    -- 定时器名
 输出参数  : 无
 返 回 值  : VOS_TIMER_PRECISION_ENUM_UINT32 -- 定时器精度范围
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_APS_InitAllTimers
 功能描述  : 初始化所有定时器，应在APS初始化时被调用
 输入参数  : pstApsTimerCtx - 定时器上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_APS_StartTimer
 功能描述  : 启动指定的APS定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen     - 定时器时长
             ulPara    - 定时器参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月13日
   作    者   : 欧阳飞 00132663
   修改内容   : 新生成函数
 2.日    期   : 2013年12月18日
   作    者   : Y00213812
   修改内容   : VoLTE_PhaseIII，修改参数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_APS_StopTimer
 功能描述  : 停止指定的APS定时器
 输入参数  : enTimerId - 需要停止的定时器ID
             ulPara    - 定时器参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2013年12月18日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseIII，修改参数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_APS_StopAllTimer
 功能描述  : 停止APS的所有定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2013年12月18日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseIII，修改参数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_APS_StopPdpAllTimer
 功能描述  : 停止所有该PDPID相关联的定时器
 输入参数  : ucPdpId   -  指定PDPID值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_APS_GetTimerStatus
 功能描述  : 获取指定的APS定时器运行状态
 输入参数  : enTimerId - 需要停止的定时器ID
             ucPdpId   - 定时器关联的PDPID
 输出参数  : 无
 返 回 值  : TAF_APS_TIMER_STATUS_ENUM_U8 - 定时器运行状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2013年12月18日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseIII，修改参数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_APS_GetRemainTimerLen
 功能描述  : 获取定时器剩余时长
 输入参数  : enTimerId        --- 定时器ID
             ulPara           --- 定时器参数
 输出参数  : pulRemainTimeLen --- 剩余时长(单位: 毫秒)
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
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
