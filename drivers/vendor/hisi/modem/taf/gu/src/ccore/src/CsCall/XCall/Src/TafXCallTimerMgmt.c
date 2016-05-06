/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXcallTimerMgmt.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2014年11月17日S
  最近修改   :
  功能描述   : 管理XCALL定时器，以及进行超时处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "TafLog.h"
#include  "TafXCallTimerMgmt.h"
#include  "NasComm.h"
#include  "TafXCallCtx.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_TAF_X_CALL_TIMERMGMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XCALL_SndOmTimerStatus
 功能描述  : 发送消息给OM模块，XCALL定时器运行状态
 输入参数  : enTimerStatus - 定时器状态
             enTimerId     - 定时器ID
             ulLen         - 定时器时长
             ucCallId      - 定时器关联CALL Id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_XCALL_SndOmTimerStatus(
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_TIMER_INFO_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_XCALL_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                             sizeof(TAF_XCALL_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_XCALL_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_XCALL_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ucCallId                    = ucCallId;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_StartTimer
 功能描述  : 启动指定的XCALL定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen     - 定时器时长
             ucCallId   - 定时器关联的call ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_XCALL_StartTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_TIMER_CTX_STRU           *pstXCallTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    pstXCallTimerCtx   =  TAF_XCALL_GetTimerCtxAddr();

    if (0 == ulLen)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_XCALL_StartTimer:timer len is zero!", (VOS_INT32)enTimerId, ucCallId);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
       ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for (i = 0 ; i < TAF_XCALL_MAX_TIMER_ID_NUM; i++)
    {
        if ((TAF_XCALL_TIMER_STATUS_RUNING == pstXCallTimerCtx[i].enTimerStatus)
         && (enTimerId                     == pstXCallTimerCtx[i].enTimerId)
         && (ucCallId                      == pstXCallTimerCtx[i].ucCallId))
        {
            TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_XCALL_StartTimer:timer is running!", (VOS_INT32)enTimerId, ucCallId);
            return;
        }
    }

    for (i = 0 ; i < TAF_XCALL_MAX_TIMER_ID_NUM ; i++)
    {
        if (TAF_XCALL_TIMER_STATUS_STOP == pstXCallTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= TAF_XCALL_MAX_TIMER_ID_NUM)
    {
       TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_XCALL_StartTimer:too many timer", (VOS_INT32)enTimerId, ucCallId);

       return;
    }

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstXCallTimerCtx[i].hTimer),
                              WUEPS_PID_TAF,
                              ulLen,
                              enTimerId,
                              ucCallId,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_XCALL_StartTimer:VOS_StartRelTimer failed");
        return;
    }

    pstXCallTimerCtx[i].enTimerId             = enTimerId;
    pstXCallTimerCtx[i].enTimerStatus         = TAF_XCALL_TIMER_STATUS_RUNING;
    pstXCallTimerCtx[i].ucCallId              = ucCallId;

    TAF_XCALL_SndOmTimerStatus(TAF_XCALL_TIMER_STATUS_RUNING, enTimerId, ulLen, ucCallId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_StopTimer
 功能描述  : 停止指定的XCALL定时器
 输入参数  : enTimerId - 需要停止的定时器ID
             ucCallId   - 定时器关联的CALL ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_XCALL_StopTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_TIMER_CTX_STRU           *pstXcallTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstXcallTimerCtx   =  TAF_XCALL_GetTimerCtxAddr();

    for (i = 0 ; i < TAF_XCALL_MAX_TIMER_ID_NUM ; i++)
    {
        if ((TAF_XCALL_TIMER_STATUS_RUNING  == pstXcallTimerCtx[i].enTimerStatus)
         && (enTimerId                      == pstXcallTimerCtx[i].enTimerId)
         && (ucCallId                       == pstXcallTimerCtx[i].ucCallId))
        {
            break;
        }
    }

    if (i >= TAF_XCALL_MAX_TIMER_ID_NUM)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_XCALL_StopTimer:timer already stoppe", (VOS_INT32)enTimerId, ucCallId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstXcallTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstXcallTimerCtx[i].hTimer));
    }

    pstXcallTimerCtx[i].hTimer            = VOS_NULL_PTR;
    pstXcallTimerCtx[i].enTimerId         = TI_TAF_XCALL_TIMER_BUTT;
    pstXcallTimerCtx[i].enTimerStatus     = TAF_XCALL_TIMER_STATUS_STOP;
    pstXcallTimerCtx[i].ucCallId          = TAF_XCALL_INVAILD_CALL_ID;

    TAF_XCALL_SndOmTimerStatus(TAF_XCALL_TIMER_STATUS_STOP, enTimerId, 0, ucCallId);

    return;
}




/*****************************************************************************
 函 数 名  : TAF_XCALL_GetTimerStatus
 功能描述  : 获取指定的XCALL定时器运行状态
 输入参数  : enTimerId - 需要停止的定时器ID
             ucCallId  - 定时器关联的call Id
 输出参数  : 无
 返 回 值  : TAF_XCALL_TIMER_STATUS_ENUM_UINT8 - 定时器运行状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_TIMER_STATUS_ENUM_UINT8  TAF_XCALL_GetTimerStatus(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_TIMER_CTX_STRU           *pstXcallTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;

    pstXcallTimerCtx = TAF_XCALL_GetTimerCtxAddr();

    enTimerStatus  = TAF_XCALL_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for (i = 0 ; i < TAF_XCALL_MAX_TIMER_ID_NUM; i++)
    {
        if ((enTimerId    == pstXcallTimerCtx[i].enTimerId)
         && (ucCallId     == pstXcallTimerCtx[i].ucCallId))
        {
            enTimerStatus = pstXcallTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitAllTimers
 功能描述  : 初始化所有定时器，应在Xcall初始化时被调用
 输入参数  : pstXcallTimerCtx - 定时器上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_XCALL_InitAllTimers(
    TAF_XCALL_TIMER_CTX_STRU              *pstXcallTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0 ; i < TAF_XCALL_MAX_TIMER_ID_NUM ; i++)
    {
        pstXcallTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstXcallTimerCtx[i].enTimerId     = TI_TAF_XCALL_TIMER_BUTT;
        pstXcallTimerCtx[i].enTimerStatus = TAF_XCALL_TIMER_STATUS_STOP;
        pstXcallTimerCtx[i].ucCallId      = TAF_XCALL_INVAILD_CALL_ID;

        PS_MEM_SET(&(pstXcallTimerCtx[i].aucReserve[0]), 0x0, sizeof(VOS_UINT8) * 2);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetRemainTimerLen
 功能描述  : 获取定时器剩余时长
 输入参数  : enTimerId        --- 定时器ID
             ucCallId           --- 定时器参数
 输出参数  : pulRemainTimeLen --- 剩余时长(单位: 毫秒)
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_GetRemainTimerLen(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId,
    VOS_UINT32                         *pulRemainTimeLen
)
{
    TAF_XCALL_TIMER_CTX_STRU           *pstXcallTimerCtx;
    VOS_UINT32                          ulRemainTick;
    VOS_UINT32                          i;

    pstXcallTimerCtx = TAF_XCALL_GetTimerCtxAddr();
    ulRemainTick   = 0;

    for (i = 0 ; i < TAF_XCALL_MAX_TIMER_ID_NUM ; i++)
    {
        if ( (TAF_XCALL_TIMER_STATUS_RUNING == pstXcallTimerCtx[i].enTimerStatus)
          && (enTimerId                     == pstXcallTimerCtx[i].enTimerId)
          && (ucCallId                      == pstXcallTimerCtx[i].ucCallId) )
        {
            break;
        }
    }

    if (i >= TAF_XCALL_MAX_TIMER_ID_NUM)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_XCALL_GetRemainTimerLen: Timer already stopped!", (VOS_INT32)enTimerId, ucCallId);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_NULL_PTR == pstXcallTimerCtx[i].hTimer)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_XCALL_GetRemainTimerLen: Timer handle is null!", (VOS_INT32)enTimerId, ucCallId);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstXcallTimerCtx[i].hTimer), &ulRemainTick))
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_XCALL_GetRemainTimerLen: Get remain time fail!", (VOS_INT32)enTimerId, ucCallId);
        *pulRemainTimeLen = 0;
        return;
    }

    *pulRemainTimeLen = ulRemainTick * TAF_XCALL_TIMER_TICK;

    return;
}

/*lint -restore */
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


