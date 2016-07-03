

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

CNAS_TIMER_CTX_STRU* CNAS_GetTimerCtxAddr(VOS_VOID)
{
    return (&g_astCnasTimerCtx[0]);
}


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



