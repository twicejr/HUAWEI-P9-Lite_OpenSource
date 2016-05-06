/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmTimerMgmt.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : 管理spm定时器，以及进行超时处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月13日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafSpmCtx.h"
#include  "PsCommonDef.h"
#include  "TafLog.h"
#include "TafSpmTimerMgmt.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_TAF_SPM_TIMERMGMT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_SndOmTimerStatus
 功能描述  : 发送消息给OM模块，SPM定时器运行状态
 输入参数  : enTimerStatus - 定时器状态
             enTimerId     - 定时器ID
             ulLen         - 定时器时长
             usClientId    - 定时器关联Client Id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月21日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_SndOmTimerStatus(
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_SPM_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                             sizeof(TAF_SPM_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_SPM_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_SPM_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->usClientId                  = usClientId;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

}


/*****************************************************************************
 函 数 名  : TAF_SPM_StartTimer
 功能描述  : 启动指定的SPM定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen     - 定时器时长
             usClientId   - 定时器关联的client ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年9月4日
   作    者   : w00167002
   修改内容   : DTS2013090403562:NAS定时器清理，需要启动32K定时器。将MM/MMA/SMS
                模块的循环定时器修改为非循环定时器。
*****************************************************************************/
VOS_VOID  TAF_SPM_StartTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_CTX_STRU             *pstSpmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    pstSpmTimerCtx   =  TAF_SPM_GetTimerCtxAddr();

    if (0 == ulLen)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_SPM_StartTimer:timer len is zero!", (VOS_INT32)enTimerId, usClientId);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
       ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    /* 如果缓存队列中该定时器已经启动则直接返回 */
    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        if ((TAF_SPM_TIMER_STATUS_RUNING == pstSpmTimerCtx[i].enTimerStatus)
         && (enTimerId                   == pstSpmTimerCtx[i].enTimerId)
         && (usClientId                  == pstSpmTimerCtx[i].usClientId))
        {
            TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_SPM_StartTimer:timer is running!", (VOS_INT32)enTimerId, usClientId);
            return;
        }
    }

    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        if (TAF_SPM_TIMER_STATUS_STOP == pstSpmTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= TAF_SPM_MAX_TIMER_NUM)
    {
       TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_SPM_StartTimer:too many timer", (VOS_INT32)enTimerId, usClientId);

       return;
    }

    /* 启动定时器 */
    ulRet = VOS_StartRelTimer(&(pstSpmTimerCtx[i].hTimer),
                              WUEPS_PID_TAF,
                              ulLen,
                              enTimerId,
                              usClientId,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_SPM_StartTimer:VOS_StartRelTimer failed");
        return;
    }

    pstSpmTimerCtx[i].enTimerId             = enTimerId;
    pstSpmTimerCtx[i].enTimerStatus         = TAF_SPM_TIMER_STATUS_RUNING;
    pstSpmTimerCtx[i].usClientId            = usClientId;

    TAF_SPM_SndOmTimerStatus(TAF_SPM_TIMER_STATUS_RUNING, enTimerId, ulLen, usClientId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_StopTimer
 功能描述  : 停止指定的SPM定时器
 输入参数  : enTimerId - 需要停止的定时器ID
             usClientId   - 定时器关联的CLIENT ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_StopTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_CTX_STRU             *pstSpmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstSpmTimerCtx   =  TAF_SPM_GetTimerCtxAddr();

    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        if ((TAF_SPM_TIMER_STATUS_RUNING  == pstSpmTimerCtx[i].enTimerStatus)
         && (enTimerId                    == pstSpmTimerCtx[i].enTimerId)
         && (usClientId                   == pstSpmTimerCtx[i].usClientId))
        {
            break;
        }
    }

    if (i >= TAF_SPM_MAX_TIMER_NUM)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_SPM_StopTimer:timer already stoppe", (VOS_INT32)enTimerId, usClientId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstSpmTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstSpmTimerCtx[i].hTimer));
    }

    pstSpmTimerCtx[i].hTimer            = VOS_NULL_PTR;
    pstSpmTimerCtx[i].enTimerId         = TI_TAF_SPM_TIMER_BUTT;
    pstSpmTimerCtx[i].enTimerStatus     = TAF_SPM_TIMER_STATUS_STOP;
    pstSpmTimerCtx[i].usClientId        = TAF_SPM_INVALID_CLIENT_ID;

    TAF_SPM_SndOmTimerStatus(TAF_SPM_TIMER_STATUS_STOP, enTimerId, 0, usClientId);
}




/*****************************************************************************
 函 数 名  : TAF_SPM_GetTimerStatus
 功能描述  : 获取指定的SPM定时器运行状态
 输入参数  : enTimerId - 需要停止的定时器ID
             ucPdpId   - 定时器关联的PDPID
 输出参数  : 无
 返 回 值  : TAF_SPM_TIMER_STATUS_ENUM_UINT8 - 定时器运行状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_TIMER_STATUS_ENUM_UINT8  TAF_SPM_GetTimerStatus(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_TIMER_CTX_STRU             *pstSpmTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;

    pstSpmTimerCtx = TAF_SPM_GetTimerCtxAddr();

    enTimerStatus  = TAF_SPM_TIMER_STATUS_STOP;

    /* 查找该定时器是否正在运行 */
    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM; i++)
    {
        if ((enTimerId    == pstSpmTimerCtx[i].enTimerId)
         && (usClientId   == pstSpmTimerCtx[i].usClientId))
        {
            enTimerStatus = pstSpmTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

/*****************************************************************************
 函 数 名  : TAF_APS_InitAllTimers
 功能描述  : 初始化所有定时器，应在SPM初始化时被调用
 输入参数  : pstSpmTimerCtx - 定时器上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_InitAllTimers(
    TAF_SPM_TIMER_CTX_STRU              *pstSpmTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0 ; i < TAF_SPM_MAX_TIMER_NUM ; i++)
    {
        pstSpmTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstSpmTimerCtx[i].enTimerId     = TI_TAF_SPM_TIMER_BUTT;
        pstSpmTimerCtx[i].enTimerStatus = TAF_SPM_TIMER_STATUS_STOP;
        pstSpmTimerCtx[i].usClientId    = TAF_SPM_INVALID_CLIENT_ID;
        pstSpmTimerCtx[i].aucReserve[0] = 0;
    }
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

