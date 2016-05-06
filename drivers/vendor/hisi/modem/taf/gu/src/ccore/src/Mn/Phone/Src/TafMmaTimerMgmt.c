/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaTimerMgmt.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月23日
  最近修改   :
  功能描述   : 管理mma定时器，以及进行超时处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月13日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafMmaCtx.h"
#include  "PsCommonDef.h"
#include  "TafLog.h"
#include  "TafMmaTimerMgmt.h"
#include  "NasComm.h"
#include  "Taf_Status.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_TAF_MMA_TIMERMGMT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern STATUS_CONTEXT_STRU              g_StatusContext;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MMA_SndOmTimerStatus
 功能描述  : 发送消息给OM模块，MMA定时器运行状态
 输入参数  : enTimerStatus - 定时器状态
             enTimerId     - 定时器ID
             ulLen         - 定时器时长
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_SndOmTimerStatus(
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
)
{
    TAF_MMA_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_MMA_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}


/*****************************************************************************
 函 数 名  : TAF_MMA_StartTimer
 功能描述  : 启动指定的MMA定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen     - 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_StartTimer(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
)
{
    TAF_MMA_TIMER_CTX_STRU             *pstMmaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (0 == ulLen)
    {
        TAF_WARNING_LOG1(WUEPS_PID_MMA,"TAF_MMA_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
       ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    pstMmaTimerCtx   =  TAF_MMA_GetTimerCtxAddr();

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for (i = 0 ; i < TAF_MMA_MAX_TIMER_NUM ; i++)
    {
        if ((TAF_MMA_TIMER_STATUS_RUNING == pstMmaTimerCtx[i].enTimerStatus)
         && (enTimerId                   == pstMmaTimerCtx[i].enTimerId))
        {
            TAF_WARNING_LOG1(WUEPS_PID_MMA,"TAF_MMA_StartTimer:timer is running!", (VOS_INT32)enTimerId);
            return;
        }
    }

    for (i = 0 ; i < TAF_MMA_MAX_TIMER_NUM ; i++)
    {
        if (TAF_MMA_TIMER_STATUS_STOP == pstMmaTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= TAF_MMA_MAX_TIMER_NUM)
    {
       TAF_WARNING_LOG1(WUEPS_PID_MMA, "TAF_MMA_StartTimer:too many timer", (VOS_INT32)enTimerId);

       return;
    }

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstMmaTimerCtx[i].hTimer),
                              WUEPS_PID_MMA,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
    /* Modified by w00176964 for APS服务状态通知清理, 2014-4-7, begin */
                              VOS_TIMER_PRECISION_5);
    /* Modified by w00176964 for APS服务状态通知清理, 2014-4-7, end */

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,"TAF_MMA_StartTimer:VOS_StartRelTimer failed");
        return;
    }

    pstMmaTimerCtx[i].enTimerId             = enTimerId;
    pstMmaTimerCtx[i].enTimerStatus         = TAF_MMA_TIMER_STATUS_RUNING;

    TAF_MMA_SndOmTimerStatus(TAF_MMA_TIMER_STATUS_RUNING, enTimerId, ulLen);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_StopTimer
 功能描述  : 停止指定的MMA定时器
 输入参数  : enTimerId - 需要停止的定时器ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_StopTimer(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    TAF_MMA_TIMER_CTX_STRU             *pstMmaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMmaTimerCtx   =  TAF_MMA_GetTimerCtxAddr();

    for (i = 0 ; i < TAF_MMA_MAX_TIMER_NUM ; i++)
    {
        if ((TAF_MMA_TIMER_STATUS_RUNING  == pstMmaTimerCtx[i].enTimerStatus)
         && (enTimerId                    == pstMmaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= TAF_MMA_MAX_TIMER_NUM)
    {
        TAF_WARNING_LOG1(WUEPS_PID_MMA,"TAF_MMA_StopTimer:timer already stoped", (VOS_INT32)enTimerId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstMmaTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstMmaTimerCtx[i].hTimer));
    }

    pstMmaTimerCtx[i].hTimer            = VOS_NULL_PTR;
    pstMmaTimerCtx[i].enTimerId         = TI_TAF_MMA_TIMER_BUTT;
    pstMmaTimerCtx[i].enTimerStatus     = TAF_MMA_TIMER_STATUS_STOP;

    TAF_MMA_SndOmTimerStatus(TAF_MMA_TIMER_STATUS_STOP, enTimerId, 0);
}




/*****************************************************************************
 函 数 名  : TAF_MMA_GetTimerStatus
 功能描述  : 获取指定的MMA定时器运行状态
 输入参数  : enTimerId - 需要停止的定时器ID
 输出参数  : 无
 返 回 值  : TAF_MMA_TIMER_STATUS_ENUM_UINT8 - 定时器运行状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MMA_TIMER_STATUS_ENUM_UINT8  TAF_MMA_GetTimerStatus(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    TAF_MMA_TIMER_CTX_STRU             *pstMmaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;

    pstMmaTimerCtx = TAF_MMA_GetTimerCtxAddr();

    enTimerStatus  = TAF_MMA_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for (i = 0 ; i < TAF_MMA_MAX_TIMER_NUM; i++)
    {
        if (enTimerId    == pstMmaTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstMmaTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_GetPlmnListAbortTimerLen
 功能描述  : 获取指定的abort plmn list定时器时长
 输入参数  :
 输出参数  : 无
 返 回 值  : 定时器的时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_MMA_GetPlmnListAbortTimerLen(VOS_VOID)
{
    VOS_UINT32                          ulTimerLen;
#if(FEATURE_ON == FEATURE_LTE)
    /* 平台支持LTE */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        ulTimerLen = STA_TIMER_GUL_PLMN_LIST_ABORT_LEN;
    }
    else
#endif
    {
        ulTimerLen = STA_TIMER_GU_PLMN_LIST_ABORT_LEN;
    }

    return ulTimerLen;
}
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


