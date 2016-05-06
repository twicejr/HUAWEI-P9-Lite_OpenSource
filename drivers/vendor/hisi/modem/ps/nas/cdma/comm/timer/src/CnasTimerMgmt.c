/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasTimerMgmt.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月28日
  功能描述   : NAS CDMA定时器处理功能函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasTimerMgmt.h"
#include "CnasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_TIMER_MGMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_TIMER_CTX_STRU                     g_astCnasTimerCtx[CNAS_MAX_TIMER_RUNNING_NUM];

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_GetTimerCtxAddr
 功能描述  : 获取timer上下文首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回timer上下文首地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_TIMER_CTX_STRU* CNAS_GetTimerCtxAddr(VOS_VOID)
{
    return (&g_astCnasTimerCtx[0]);
}

/*****************************************************************************
 函 数 名  : CNAS_InitTimerCtx
 功能描述  : timer 上下文table初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月05日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_InitTimerCtx(VOS_VOID)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
        pstTimerCtx->ulParam       = 0;
        pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
        pstTimerCtx->ulTimerId     = 0;
        pstTimerCtx->ulPid         = 0;

        pstTimerCtx++;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_GetAFreeTimerCtx
 功能描述  : 获取一个空闲的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回timer上下文地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_TIMER_CTX_STRU* CNAS_GetAFreeTimerCtx(VOS_VOID)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((VOS_NULL_PTR           == pstTimerCtx->pTimerHandle)
         && (CNAS_TIMER_STATUS_STOP == pstTimerCtx->enTimerStatus))
        {
            /* 找到一个空闲的timer CTX, 跳出循环 */
            return pstTimerCtx;
        }

        pstTimerCtx++;
    }

    /* 没有找到，返回空指针 */
    return (VOS_NULL_PTR);
}

/*****************************************************************************
 函 数 名  : CNAS_GetSpecifiedTimerCtx
 功能描述  : 获取指定timer的CTX, 如果指定timer ID在CTX表中找到，返回当前CTX地址，
             否则返回为NULL
 输入参数  : ulPid     -- 启动timer的PID任务
             ulTimerId -- timer标识
             ulPara    -- 定时器参数标识
 输出参数  : 无
 返 回 值  : 返回指定timer上下文地址

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_TIMER_CTX_STRU* CNAS_GetSpecifiedTimerCtx(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulPara
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    /* 查找timer ID是否在timer ctx表中 */
    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((ulPid                     == pstTimerCtx->ulPid)
         && (ulTimerId                 == pstTimerCtx->ulTimerId)
         && (ulPara                    == pstTimerCtx->ulParam)
         && (CNAS_TIMER_STATUS_RUNNING == pstTimerCtx->enTimerStatus))
        {
            /* 查找成功，返回当前的ctx地址 */
            return pstTimerCtx;
        }

        pstTimerCtx++;
    }

    /* 查找失败，返回空指针 */

    return (VOS_NULL_PTR);
}

/*****************************************************************************
 函 数 名  : CNAS_StartTimer
 功能描述  : CNAS定时器启动
 输入参数  : ulPid        -- 启动timer的PID模块
             pstTimerInfo -- timer信息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数

 1.日    期   : 2015年07月25日
   作    者   : y00245242
   修改内容   : 增加时长为0的保护
*****************************************************************************/
VOS_VOID CNAS_StartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    /* 指针检查 */
    if ((VOS_NULL_PTR == pstTimerInfo)
     || (0            == pstTimerInfo->ulTimerLen))
    {
        /* 打印错误信息 */
        CNAS_ERROR_LOG(ulPid, "CNAS_StartTimer: pstTimerInfo is NULL or PARAM is invalid!");

        return;
    }

    /* 检查当前的定时器是否在CTX表中 */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, pstTimerInfo->ulTimerId, pstTimerInfo->ulParam);


    if (VOS_NULL_PTR != pstTimerCtx)
    {
        /* 打印错误信息, 当前timer在运行 */
        CNAS_ERROR_LOG1(ulPid, "CNAS_StartTimer: ulTimerId is already running!", pstTimerInfo->ulTimerId);

        return;
    }

    /* 获取一个空闲的定时器CTX */
    pstTimerCtx = CNAS_GetAFreeTimerCtx();

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        /* timer CTX表已满，打印错误信息， */
        CNAS_ERROR_LOG(ulPid, "CNAS_StartTimer: timer ctx table is full!");

        return;
    }

    if (VOS_OK != VOS_StartRelTimer(&(pstTimerCtx->pTimerHandle),
                                    ulPid,
                                    pstTimerInfo->ulTimerLen,
                                    pstTimerInfo->ulTimerId,
                                    pstTimerInfo->ulParam,
                                    VOS_RELTIMER_NOLOOP,
                                    pstTimerInfo->ulTimerPrecision))
    {
        /* 启动定时器失败，打印错误信息 */
        CNAS_ERROR_LOG1(ulPid, "CNAS_StartTimer: start timer is failure!", pstTimerInfo->ulTimerId);

        return;
    }

    /* 保存定时器的信息到该定时器CTX中 */
    pstTimerCtx->ulTimerId = pstTimerInfo->ulTimerId;
    pstTimerCtx->ulPid     = ulPid;
    pstTimerCtx->ulParam   = pstTimerInfo->ulParam;

    /* 设置定时器状态为running状态 */
    pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_RUNNING;

    /* 输出timer启动信息 */
    stMntnTimerInfo.ulParam    = pstTimerInfo->ulParam;
    stMntnTimerInfo.ulTimerId  = pstTimerInfo->ulTimerId;
    stMntnTimerInfo.ulTimerLen = pstTimerInfo->ulTimerLen;
    stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_START;
    CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_RestartTimer
 功能描述  : 重启定时器，当定时器还在运行时，先停止该定时器，再重启定时器。如果
             定时器未运行，直接启动该定时器
 输入参数  : ulPid        -- 启动timer的PID模块
             pstTimerInfo -- timer信息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_RestartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    /* 指针检查 */
    if (VOS_NULL_PTR == pstTimerInfo)
    {
        /* 打印错误信息 */
        CNAS_ERROR_LOG(ulPid, "CNAS_RestartTimer: pstTimerInfo is NULL!");

        return;
    }

    /* 检查当前的定时器是否在CTX表中 */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, pstTimerInfo->ulTimerId, pstTimerInfo->ulParam);

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        /* CTX表中无当前定时器记录，获取一个空闲的定时器CTX */
        pstTimerCtx = CNAS_GetAFreeTimerCtx();

        if (VOS_NULL_PTR == pstTimerCtx)
        {
            /* timer CTX表已满，打印错误信息， */
            CNAS_ERROR_LOG(ulPid, "CNAS_RestartTimer: timer ctx table is full!");

            return;
        }
    }

    if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
    {
        /* 当前timer还在运行，先停止它 */
        if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
        {
            /* 停止定时器失败，打印错误信息 */
            CNAS_ERROR_LOG1(ulPid, "CNAS_RestartTimer: start timer is failure!", pstTimerInfo->ulTimerId);

            return;
        }

        /* 清除timer CTX信息 */
        pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
        pstTimerCtx->ulParam       = 0;
        pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
        pstTimerCtx->ulTimerId     = 0;
        pstTimerCtx->ulPid         = 0;

        /* 输出timer停止信息 */
        stMntnTimerInfo.ulParam    = pstTimerInfo->ulParam;
        stMntnTimerInfo.ulTimerId  = pstTimerInfo->ulTimerId;
        stMntnTimerInfo.ulTimerLen = 0;
        stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
        CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
    }

    /* 启动定时器 */
    if (VOS_OK != VOS_StartRelTimer(&(pstTimerCtx->pTimerHandle),
                                    ulPid,
                                    pstTimerInfo->ulTimerLen,
                                    pstTimerInfo->ulTimerId,
                                    pstTimerInfo->ulParam,
                                    VOS_RELTIMER_NOLOOP,
                                    pstTimerInfo->ulTimerPrecision))
    {
        /* 启动定时器失败，打印错误信息 */
        CNAS_ERROR_LOG1(ulPid, "CNAS_RestartTimer: start timer is failure!", pstTimerInfo->ulTimerId);

        return;
    }

    /* 保存定时器的信息到该定时器CTX中 */
    pstTimerCtx->ulTimerId = pstTimerInfo->ulTimerId;
    pstTimerCtx->ulPid     = ulPid;
    pstTimerCtx->ulParam   = pstTimerInfo->ulParam;

    /* 设置定时器状态为running状态 */
    pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_RUNNING;

    /* 输出timer启动信息 */
    stMntnTimerInfo.ulParam    = pstTimerInfo->ulParam;
    stMntnTimerInfo.ulTimerId  = pstTimerInfo->ulTimerId;
    stMntnTimerInfo.ulTimerLen = pstTimerInfo->ulTimerLen;
    stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_START;
    CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_StopTimer
 功能描述  : CNAS停止定时器
 输入参数  : ulPid        -- 启动timer的PID模块
             pstTimerInfo -- timer信息指针
             ulPara       -- 定时器参数标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_StopTimer(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    /* 检查当前的定时器是否在CTX表中 */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, ulTimerId, ulParam);

    if (VOS_NULL_PTR != pstTimerCtx)
    {
        if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
        {
            /* 当前timer还在运行，先停止它 */
            if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
            {
                /* 停止定时器失败，打印错误信息 */
                CNAS_ERROR_LOG1(ulPid, "CNAS_StopTimer: start timer is failure!", ulTimerId);

                return;
            }


        }

        /* 输出timer停止信息 */
        stMntnTimerInfo.ulParam    = pstTimerCtx->ulParam;
        stMntnTimerInfo.ulTimerId  = pstTimerCtx->ulTimerId;
        stMntnTimerInfo.ulTimerLen = 0;
        stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
        CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);

        /* 清除timer表中的CTX信息 */
        pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
        pstTimerCtx->ulParam       = 0;
        pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
        pstTimerCtx->ulTimerId     = 0;
        pstTimerCtx->ulPid         = 0;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_StopAllTimerWithSpecifiedPid
 功能描述  : 停止指定PID的所有定时器
 输入参数  : ulPid        -- 启动timer的PID模块
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_StopAllTimerWithSpecifiedPid(
    VOS_UINT32                          ulPid
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((CNAS_TIMER_STATUS_RUNNING == pstTimerCtx->enTimerStatus)
         && (ulPid                     == pstTimerCtx->ulPid))
        {
            /* 当定时器的句柄为空的时候, 说明其已经停止或者超时 */
            if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
            {
                /* 当前timer还在运行，先停止它 */
                if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
                {
                    /* 停止定时器失败，打印错误信息 */
                    CNAS_ERROR_LOG1(ulPid, "CNAS_StopTimer: start timer is failure!", pstTimerCtx->ulTimerId);

                    pstTimerCtx++;

                    continue;
                }

                /* 输出timer停止信息 */
                stMntnTimerInfo.ulParam    = pstTimerCtx->ulParam;
                stMntnTimerInfo.ulTimerId  = pstTimerCtx->ulTimerId;
                stMntnTimerInfo.ulTimerLen = 0;
                stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
                CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
            }

            /* 清除timer表中的CTX信息 */
            pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
            pstTimerCtx->ulParam       = 0;
            pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
            pstTimerCtx->ulTimerId     = 0;
            pstTimerCtx->ulPid         = 0;
        }

        pstTimerCtx++;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_GetSpecifiedTimerStatus
 功能描述  : CNAS停止定时器
 输入参数  : ulPid     -- 启动timer的PID模块
             ucTimerId -- timer标识
 输出参数  : 无
 返 回 值  : CNAS_TIMER_STATUS_STOP    -- timer在停止状态
             CNAS_TIMER_STATUS_RUNNING -- timer在启动状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_TIMER_STATUS_ENUM_UINT8 CNAS_GetSpecifiedTimerStatus(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;

    /* 检查当前的定时器是否在CTX表中 */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, ulTimerId, ulParam);

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        return CNAS_TIMER_STATUS_STOP;
    }

    return pstTimerCtx->enTimerStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_GetSpecifiedTimerRemainLen
 功能描述  : 获取指定定时器剩余长度
 输入参数  : ulPid     -- 启动timer的PID模块
             ucTimerId -- timer标识
 输出参数  : 无
 返 回 值  : 返回剩余定时器时长

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_GetSpecifiedTimerRemainLen(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulTimerLen  = 0;

    /* 检查当前的定时器是否在CTX表中 */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, ulTimerId, ulParam);

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        /* 没有找到该定时器，返回长度为0 */
        return ulTimerLen;
    }

    /* 如果定时器句柄为空，表明定时器已停或已经到期 */
    if (VOS_NULL_PTR == pstTimerCtx->pTimerHandle)
    {
        /* 定时器已经停止或超时，返回定时器长度为0 */
        return ulTimerLen;
    }

    /* 获取定时器长度 */
    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerCtx->pTimerHandle), &ulTimerLen))
    {
        /* 获取定时器剩余时长失败，打印错误信息 */
        CNAS_ERROR_LOG1(ulPid, "CNAS_GetSpecifiedTimerRemainLen: get remained length is failure!",
                        pstTimerCtx->ulTimerId);

        /* 获取失败，返回为0 */
        return 0;
    }

    /* 转换timer时长为毫秒 */
    return (ulTimerLen * CNAS_TIMER_TICK);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



