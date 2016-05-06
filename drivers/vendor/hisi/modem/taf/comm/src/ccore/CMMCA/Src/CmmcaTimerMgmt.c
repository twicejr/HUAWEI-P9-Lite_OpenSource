/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaTimerMgmt.c
  版 本 号   : 初稿
  作    者   : 鲁琳/l60609
  生成日期   : 2014年01月21日
  最近修改   :
  功能描述   : CMMCA的定时器文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月21日
    作    者   : 鲁琳/l60609
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaTimerMgmt.h"
#include "CmmcaCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_CMMCA_TIMER_MGMT_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/* 这个表添加定时器的精度信息 */
CMMCA_TIMER_PRECISION_STRU              g_stCmmcaTimerPrcision[]=
{
   {WUEPS_PID_CMMCA,  TI_CMMCA_WAIT_IPV6_RA_INFO,       VOS_TIMER_PRECISION_0},
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CMMCA_MNTN_TraceTimerOperation
 功能描述  : SDT中勾定时器消息
 输入参数  : VOS_UINT32                            ulPid
             CMMCA_TIMER_ID_ENUM_UINT32            enTimerId
             VOS_UINT32                            ulTimerLen
             CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CMMCA_MNTN_TraceTimerOperation(
    VOS_UINT32                            ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                            ulTimerLen,
    CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction
)
{
    CMMCA_TIMER_INFO_STRU                 stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(CMMCA_TIMER_INFO_STRU));

    stMsg.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid     = ulPid;
    stMsg.ulReceiverPid   = VOS_PID_TIMER;
    stMsg.ulLength        = sizeof(CMMCA_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stMsg.enTimerId       = enTimerId;
    stMsg.ulTimerLen      = ulTimerLen;
    stMsg.enTimerAction   = enTimerAction;

    DIAG_TraceReport(&stMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_GetTimerPrecision
 功能描述  : 获取定时器精度
 输入参数  : CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
 输出参数  : 无
 返 回 值  : VOS_TIMER_PRECISION_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_TIMER_PRECISION_ENUM_UINT32 CMMCA_GetTimerPrecision(
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
)
{
   /*定时器分为两种，26M定时器和32K定时器，
         26M定时器，系统开销少，推荐使用，但当DRX睡眠时，停止计数，可能计时不准。
         32K定时器，系统开销大，不推荐使用，但计时准确，
         当选择无精度要求时(VOS_TIMER_NO_PRECISION)，启动26M定时器
         其他有精度要求的，启动32K定时器。
    */

    VOS_UINT32                          i;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    /* 默认为有精度要求，挂在32K时钟上 */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for ( i = 0; i < (sizeof(g_stCmmcaTimerPrcision)/sizeof(CMMCA_TIMER_PRECISION_STRU)); i++)
    {
        if (enTimerId == g_stCmmcaTimerPrcision[i].ulTimerName)
        {
            ulPrecision = g_stCmmcaTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*****************************************************************************
 函 数 名  : CMMCA_StartTimer
 功能描述  : CMMCA启动定时器
 输入参数  : VOS_UINT32                          ulPid
             CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
             VOS_UINT32                          ulLen
             VOS_UINT32                          ulParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CMMCA_StartTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    CMMCA_TIMER_CTX_STRU               *pstTiCtx;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTmrPrecision;

    /* 输入参数检查 */
    if (0 == ulLen)
    {
        CMMCA_ERROR1_LOG("CMMCA_StartTimer:ulLen is", ulLen);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    pstTiCtx = CMMCA_GetTiCtx();

    /* 如果该定时器已经启动则直接返回 */
    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if ((CMMCA_TIMER_STATUS_RUNNING == pstTiCtx[i].enTimerStatus)
         && (enTimerId               == pstTiCtx[i].enTimerId))
        {
            return;
        }
    }

    /* 找到一个空闲位置 */
    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if (CMMCA_TIMER_STATUS_STOP == pstTiCtx[i].enTimerStatus )
        {
            break;
        }
    }

    /* 未找到空闲位置，无法保存该定时器信息，直接返回 */
    if (i >= CMMCA_MAX_TIMER_NUM)
    {
        CMMCA_ERROR1_LOG("CMMCA_StartTimer:i is",i);
        return;
    }

    enTmrPrecision = CMMCA_GetTimerPrecision(enTimerId);

    ulRet = VOS_StartRelTimer(&(pstTiCtx[i].hTimer),
                              ulPid,
                              ulLen,
                              enTimerId,
                              ulParam,
                              VOS_RELTIMER_NOLOOP,
                              enTmrPrecision);

    if (VOS_OK != ulRet)
    {
        CMMCA_ERROR_LOG("CMMCA_StartTimer:timer is fail start!");
        return;
    }

    pstTiCtx[i].enTimerId     = enTimerId;
    pstTiCtx[i].enTimerStatus = CMMCA_TIMER_STATUS_RUNNING;

    /* 勾包CMMCA_TIMER_INFO_STRU */
    CMMCA_MNTN_TraceTimerOperation(ulPid, enTimerId, ulLen, CMMCA_TIMER_OPERATION_START);

    return;
}


/*****************************************************************************
 函 数 名  : CMMCA_StopTimer
 功能描述  : CMMCA停止定时器
 输入参数  : VOS_UINT32                          ulPid
             CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_StopTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
)
{
    VOS_UINT32                          i;
    CMMCA_TIMER_CTX_STRU               *pstTiCtx;

    pstTiCtx = CMMCA_GetTiCtx();

    /* 如果该定时器已经启动则直接返回 */
    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if ((CMMCA_TIMER_STATUS_RUNNING == pstTiCtx[i].enTimerStatus)
         && (enTimerId               == pstTiCtx[i].enTimerId))
        {
            break;
        }
    }

    /* 未找到该定时器 */
    if ( i >= CMMCA_MAX_TIMER_NUM)
    {
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstTiCtx[i].hTimer)
    {
        VOS_StopRelTimer(&(pstTiCtx[i].hTimer));
    }

    pstTiCtx[i].hTimer        = VOS_NULL_PTR;
    pstTiCtx[i].enTimerId     = TI_CMMCA_TIMER_BUTT;
    pstTiCtx[i].enTimerStatus = CMMCA_TIMER_STATUS_STOP;

    /* 勾包CMMCA_TIMER_INFO_STRU */
    CMMCA_MNTN_TraceTimerOperation(ulPid, enTimerId, 0, CMMCA_TIMER_OPERATION_STOP);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_GetTimerStatus
 功能描述  : 获取定时器状态
 输入参数  : VOS_UINT32                          ulPid
             CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
 输出参数  : 无
 返 回 值  : CMMCA_TIMER_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_TIMER_STATUS_ENUM_UINT8 CMMCA_GetTimerStatus(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
)
{
    CMMCA_TIMER_CTX_STRU               *pstTiCtx;
    CMMCA_TIMER_STATUS_ENUM_UINT8       enTimerStatus;
    VOS_UINT32                          i;

    pstTiCtx  = CMMCA_GetTiCtx();

    enTimerStatus = CMMCA_TIMER_STATUS_STOP;

    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if (enTimerId == pstTiCtx[i].enTimerId)
        {
            enTimerStatus = pstTiCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

