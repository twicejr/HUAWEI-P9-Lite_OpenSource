


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsCommonDef.h"
#include "stdlib.h"
#include "CnasHsdSysAcqStrategy.h"
#include "CnasHsdMntn.h"
#include "CnasCcb.h"
#include "CnasPrlApi.h"
#include "CnasHsdAvoidStrategy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CNAS_HSD_AVOID_STRATEGY_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT随counter值变化的avoid time */
VOS_UINT8                               g_aucAvoidSETTimeLen[CNAS_HSD_AVOID_SESSION_COUNTER_MAX] =
{
    0, 1, 2, 4, 8, 8, 8
};

/* CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE随counter值变化的avoid time */
VOS_UINT8                               g_aucAvoidMAPFTimeLen[CNAS_HSD_AVOID_PROBE_COUNTER_MAX] =
{
    0, 1, 1, 2, 2, 2
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/

VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_Without_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT32                          ulAvoidTimeLen;

    switch (enAvoidReason)
    {
        /* 协议CDG130中10.3.5:未明确定义，这里使用60sec */
        case CNAS_HSD_AVOID_PROTOCAL_MISMATCH:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* 协议CDG143中5.6.2:屏蔽30sec */
        case CNAS_HSD_AVOID_REDIRECTION:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_30_SEC;
            break;

        /* 协议CDG143中5.8.2:屏蔽10min */
        case CNAS_HSD_AVOID_SESSION_NEGOTIATION_FAILURE:
            ulAvoidTimeLen = 10 * CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* 协议CDG143中5.7.1:屏蔽7min */
        case CNAS_HSD_AVOID_PERSISTENCE_TEST_FAILURE:
            ulAvoidTimeLen = 7 * CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* 协议CDG143中5.7.4:屏蔽10min */
        case CNAS_HSD_AVOID_AUTHEN_OR_BILLING_FAILURE:
            ulAvoidTimeLen = 10 * CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* 协议CDG143中5.5.2:屏蔽1min */
        case CNAS_HSD_AVOID_FAIL_CONTINUE_THREE_TIMES:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_60_SEC;
            break;

         case CNAS_HSD_AVOID_PREFER_CH_NOT_VALID:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_60_SEC;
            break;
        default:
            ulAvoidTimeLen = 0;
            break;
    }

    return ulAvoidTimeLen;
}


VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_With_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT32                          ulAvoidTimeLen;
    VOS_UINT8                           ucCounter;

    ucCounter = CNAS_HSD_GetCounterValue(enAvoidReason);

    switch (enAvoidReason)
    {
        /* 协议CDG143中5.8.1:随着counter增加，屏蔽时间为1, 2, 4, 8, 8, 8, 16, 16(min)... */
        case CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT:
            if (ucCounter < CNAS_HSD_AVOID_SESSION_COUNTER_MAX)
            {
                ulAvoidTimeLen = g_aucAvoidSETTimeLen[ucCounter] * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            else
            {
                ulAvoidTimeLen = 16 * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            break;

        /* 协议CDG143中5.7.2b:随着counter增加，屏蔽时间为2, 4, 8, 8, 8, 16, 16(min)... */
        case CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE:
            if (ucCounter < CNAS_HSD_AVOID_PROBE_COUNTER_MAX)
            {
                ulAvoidTimeLen = g_aucAvoidMAPFTimeLen[ucCounter] * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            else
            {
                ulAvoidTimeLen = 4 * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            break;

        /* 协议CDG143中5.7.5b:连续发生三次屏蔽1min */
        case CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE:
            if (ucCounter < CNAS_HSD_AVOID_BUSY_COUNTER_MAX)
            {
                ulAvoidTimeLen = 0;
            }
            else
            {
                ulAvoidTimeLen = 1 * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            break;

        default:
            ulAvoidTimeLen = 0;
    }

    return ulAvoidTimeLen;
}


VOS_VOID CNAS_HSD_IncreaseAvoidFreqUsedNum(VOS_VOID)
{
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList;

    pstAvoidFreqList = CNAS_HSD_GetAvoidFreqListAddr();
    pstAvoidFreqList->ucAvoidItemUsedNum++;

    return;
}


VOS_VOID CNAS_HSD_DecreaseAvoidFreqUsedNum(VOS_VOID)
{
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList;

    pstAvoidFreqList = CNAS_HSD_GetAvoidFreqListAddr();
    pstAvoidFreqList->ucAvoidItemUsedNum--;

    return;
}


VOS_VOID CNAS_HSD_IncreaseCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    UINT8                               ucMaxCounter
)
{
    VOS_UINT8                          *pucCounter;

    pucCounter = CNAS_HSD_GetAvoidFreqListAddr()->aucCounter;

    if (pucCounter[enAvoidReason] < ucMaxCounter)
    {
        pucCounter[enAvoidReason]++;
    }
    else
    {
        pucCounter[enAvoidReason] = ucMaxCounter;
    }

    return;
}


VOS_VOID CNAS_HSD_ClearCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT8                          *pucCounter;

    if (enAvoidReason < CNAS_HSD_AVOID_REASON_MAX)
    {
        pucCounter                = CNAS_HSD_GetAvoidFreqListAddr()->aucCounter;
        pucCounter[enAvoidReason] = 0;
    }

    return;
}


VOS_UINT8 CNAS_HSD_GetCounterValue(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    return (CNAS_HSD_GetAvoidFreqListAddr()->aucCounter[enAvoidReason]);
}


VOS_VOID CNAS_HSD_CheckExpiredFreqFromAvoidList(VOS_VOID)
{
    VOS_UINT32                          ulCurSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           ucIndex;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* 获取当前系统的slice */
    ulCurSlice = CNAS_HSD_GetSystemSlice();

    /* 遍历avoid列表中所有的频点的到期slice */
    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* 考虑反转问题 */
            ulRunSliceNum = CNAS_HSD_MAX_SLICE_VALUE - pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* 如果已经运行的slice数目大于等于到期的slice数目，要将该item从avoid list中删掉 */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_HSD_DeleteItemFromAvoidList(ucIndex);
            CNAS_HSD_DecreaseAvoidFreqUsedNum();
        }
    }

    /* 如果avoid list为空，停止avoid定时器 */
    if (0 == CNAS_HSD_GetAvoidFreqListUsedNum())
    {
        CNAS_HSD_StopTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER);
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}


VOS_UINT32 CNAS_HSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT8                           ucIndex;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* 遍历avoid列表中所有的频点，判断当前频点是否在avoid列表中 */
    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&(pstAvoidFreqInfo->stAvoidFreq), pstFreq))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSD_DeleteItemFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

    PS_MEM_SET(pstAvoidFreqInfo, 0, sizeof(CNAS_HSD_AVOID_FREQ_INFO_STRU));

    pstAvoidFreqInfo->enUsedFlag = CNAS_HSD_AVOID_ITEM_UNUSED;

    return;
}


CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetAvoidItemFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* 返回指定索引的avoid频点信息 */
    pstAvoidFreqInfo = &(CNAS_HSD_GetAvoidFreqListAddr()->astAvoidFreqInfo[ucIndex]);

    return pstAvoidFreqInfo;
}


CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetEmptyItemFormAvoidList(VOS_VOID)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulFlag;

    ulFlag = VOS_FALSE;

    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        /* 查找一个未被使用的项 */
        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            ulFlag = VOS_TRUE;

            break;
        }
    }

    if (VOS_TRUE == ulFlag)
    {
        CNAS_HSD_IncreaseAvoidFreqUsedNum();

        return pstAvoidFreqInfo;
    }

    return VOS_NULL_PTR;
}


VOS_UINT32 CNAS_HSD_IsCurrFreqExistInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT8                          *ucIndex
)
{
    VOS_UINT8                           i;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* 遍历avoid列表中所有的频点，当前频点在avoid列表中, 返回VOS_TRUE */
    for (i = 0; i < CNAS_HSD_MAX_AVOID_FREQ_NUM; i++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(i);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&(pstAvoidFreqInfo->stAvoidFreq), pstFreq))
        {
            *ucIndex = i;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSD_AddAvoidInfoToAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulExpiredSliceNum
)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 如果当前freq已经处于avoid状态，将该项的avoid信息更新成最新的avoid信息，
       否则找到一个空的记录填写最新的avoid信息 */
    if (VOS_TRUE == CNAS_HSD_IsCurrFreqExistInAvoidList(pstFreq, &ucIndex))
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);
    }
    else
    {
        pstAvoidFreqInfo = CNAS_HSD_GetEmptyItemFormAvoidList();
    }

    if (VOS_NULL_PTR == pstAvoidFreqInfo)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddAvoidInfoToAvoidList: get avoid item fail!");

        return;
    }

    pstAvoidFreqInfo->enUsedFlag                = CNAS_HSD_AVOID_ITEM_USED;
    pstAvoidFreqInfo->ulStartSlice              = ulStartSlice;
    pstAvoidFreqInfo->ulExpiredSliceNum         = ulExpiredSliceNum;
    pstAvoidFreqInfo->stAvoidFreq.enBandClass   = pstFreq->enBandClass;
    pstAvoidFreqInfo->stAvoidFreq.usChannel     = pstFreq->usChannel;

    return;
}


VOS_VOID CNAS_HSD_IncreaseCounterInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
)
{
    switch (enFailReason)
    {
        case HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE:
            CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE, CNAS_HSD_AVOID_PROBE_COUNTER_MAX);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_BS_BUSY_OR_GENERAL :
            CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE, CNAS_HSD_AVOID_BUSY_COUNTER_MAX);
            break;

        default:
            break;
    }

    return;
}


VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
)
{
    VOS_UINT32                          ulAvoidTime;

    switch (enFailReason)
    {
        case HSM_HSD_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_PERSISTENCE_TEST_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_With_Counter(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_AUTH_BILLING_FAIL:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_AUTHEN_OR_BILLING_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_BS_BUSY_OR_GENERAL:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_With_Counter(CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_PREFER_CH_NOT_VALID);
            break;

        default:
            ulAvoidTime = 0;
            break;
    }

    return ulAvoidTime;
}


VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8 enNegResult
)
{
    VOS_UINT32                          ulAvoidTime;

    if (HSM_HSD_SESSION_NEG_RSLT_TIMEOUT == enNegResult)
    {
        ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_With_Counter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT);
    }
    else if (HSM_HSD_SESSION_NEG_RSLT_FAIL == enNegResult)
    {
        ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_FAILURE);
    }
    else
    {
        ulAvoidTime = 0;
    }

    return ulAvoidTime;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInAccessRlstInd(
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulAvoidTime;

    ulExpiredSliceNum = 0;
    ulAvoidTime       = 0;

    if (HSM_HSD_HRPD_CONN_OPEN_RSLT_SUCC == pstOpenInd->enRslt)
    {
        /* access成功，清除协议5.7.5b中的计数器 */
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE);

        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_TCA_TIMEOUT);
    }
    else
    {
        if (HSM_HSD_HRPD_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT == pstOpenInd->enRslt)
        {
            CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(penReAcqFlag);

            return;
        }

        /*  CDG143 6.4 非混合模式下此场景不需要avoid */
        if (HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE == pstOpenInd->enRslt)
        {
            if (VOS_FALSE == CNAS_HSD_IsNeedAvoidedInNonHbrid(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE))
            {
                return;
            }
        }

        /* 根据错误值处理协议CDG143里面5.7.2b和5.7.5b中描述的计数器*/
        CNAS_HSD_IncreaseCounterInAccessRlstInd(pstOpenInd->enRslt);

        /* 获取avoid time */
        ulAvoidTime = CNAS_HSD_GetAvoidTimeLenInAccessRlstInd(pstOpenInd->enRslt);

        if (0 != ulAvoidTime)
        {
            ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

            CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                             CNAS_HSD_GetSystemSlice(),
                                             ulExpiredSliceNum);

            /* 如果avoid timer未启动，启动avoid timer定时器 */
            if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                          TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                          0))
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                    TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
            }

            *penReAcqFlag = CNAS_HSD_NEED_REACQ;
        }

    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
)
{
    VOS_UINT8                           ucCounter;

    /*  CDG143 6.4 非混合模式下此场景不需要avoid */
    if (VOS_FALSE == CNAS_HSD_IsNeedAvoidedInNonHbrid(CNAS_HSD_AVOID_TCA_TIMEOUT))
    {
        return;
    }

    /* 根据协议CDG143的5.7.7，TCA Timeout时要增加计数器的计数 */
    CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_TCA_TIMEOUT, CNAS_HSD_AVOID_TCA_COUNTER_MAX);

    ucCounter = CNAS_HSD_GetCounterValue(CNAS_HSD_AVOID_TCA_TIMEOUT);

    /* 根据协议CDG143的5.7.7，TCA Timeout连续三次后重新搜网 */
    if (ucCounter >= CNAS_HSD_AVOID_TCA_COUNTER_MAX)
    {
        *penReAcqFlag = CNAS_HSD_NEED_REACQ;
    }

    return;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInCasStatusInd(
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enHsdATStatus
)
{
    /* 状态发生IDLE->TCH切换时，表示一次max access probes成功，要处理协议CDG143的5.7.2中的计数器 */
    if ((CNAS_HSD_AT_STATUS_ENUM_IDLE == CNAS_HSD_GetATStatus())
     && (CNAS_HSD_AT_STATUS_ENUM_CONN  == enHsdATStatus))
    {
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE);
    }

    return;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                        *penReAcqFlag
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulAvoidTime;

    ulExpiredSliceNum = 0;
    ulAvoidTime       = 0;

    /* 根据协议CDG143的5.8,session neg成功后，要清除5.8.1中的计数器 */
    if (HSM_HSD_SESSION_NEG_RSLT_SUCCESS == pstSessionNegRlstInd->enNegResult)
    {
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT);
    }
    else
    {
        /* 根据协议CDG143的5.8,session neg timeout or fail时，要屏蔽当前freq并且重新搜网，
           如果是session neg timeout，还要增加5.8.1中描述的计数器 */
        if (HSM_HSD_SESSION_NEG_RSLT_TIMEOUT == pstSessionNegRlstInd->enNegResult)
        {
            CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT, CNAS_HSD_AVOID_SESSION_COUNTER_MAX);
        }

        ulAvoidTime = CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd(pstSessionNegRlstInd->enNegResult);

        if (0 != ulAvoidTime)
        {
            ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

            CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                             CNAS_HSD_GetSystemSlice(),
                                             ulExpiredSliceNum);

            /* 如果avoid timer未启动，启动avoid timer定时器 */
            if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                          TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                          0))
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                    TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
            }

            *penReAcqFlag = CNAS_HSD_NEED_REACQ;
        }
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInCasSysSyncCnf(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT32                          ulCurrSlice;
    VOS_UINT32                          ulAvoidTime;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    VOS_UINT8                           i;

    ulAvoidTime      = 0;
    ulCurrSlice      = CNAS_HSD_GetSystemSlice();

    /* 协议CDG130的10.3.5规定，如果freq同步失败的原因是protocol mismatch，则将该freq添加到avoid list中 */
    for (i = 0; i < pstSyncCnf->ulSyncFailFreqNum; i++)
    {
        if (CNAS_CAS_HRPD_SYS_SRCH_SYNC_FAIL_PROTO_MISMATCH == pstSyncCnf->astSyncRsltList[i].enFailReason)
        {
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_PROTOCAL_MISMATCH);
        }

        if (0 != ulAvoidTime)
        {
            /* 如果从同步失败到现在所经过的时间已经超过需要屏蔽的时间，则不进行屏蔽操作 */
            ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

            ulRunSliceNum     = ulCurrSlice - pstSyncCnf->astSyncRsltList[i].ulSlice;
            ulRunSliceNum     = ulRunSliceNum % CNAS_HSD_MAX_SLICE_VALUE;

            if (ulRunSliceNum < ulExpiredSliceNum)
            {
                stFreq.enBandClass  = pstSyncCnf->astSyncRsltList[i].stFreq.usBandClass;
                stFreq.usChannel    = pstSyncCnf->astSyncRsltList[i].stFreq.usChannel;

                CNAS_HSD_AddAvoidInfoToAvoidList(&stFreq, ulCurrSlice, ulExpiredSliceNum);
            }

            ulAvoidTime = 0;
        }
    }

    if (0 != CNAS_HSD_GetAvoidFreqListUsedNum())
    {
        /* 如果avoid timer未启动，启动avoid timer定时器 */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                      TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInRedirection(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulAvoidTime;

    /* 协议CDG143的5.6.2规定在redirection失败后，需要将原来的freq屏蔽30sec */
    ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_REDIRECTION);

    if (0 != ulAvoidTime)
    {
        ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

        CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                         CNAS_HSD_GetSystemSlice(),
                                         ulExpiredSliceNum);

        /* 如果avoid timer未启动，启动avoid timer定时器 */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                      TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}



VOS_UINT32 CNAS_HSD_IsSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys,
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys
)
{
    VOS_UINT8                           ucCurrSubnetid;
    VOS_UINT8                           ucLastSubnetid;
    VOS_UINT8                           ucSubnetTempLen;
    VOS_UINT8                           ucSubnetBitTempLen;   /* 存放Subne剩余bit长度 */

    if (pstCurrHrpdSys->ucSubnetMask != pstLastHrpdSys->ucSubnetMask)
    {
        return VOS_TRUE;
    }

    ucSubnetTempLen = (pstCurrHrpdSys->ucSubnetMask / CNAS_PRL_BIT_LEN_8_BIT);

    /* 先比较整字节 */
    if (VOS_TRUE != CNAS_PRL_CmpSubnetValue(pstCurrHrpdSys->aucSubnet, pstLastHrpdSys->aucSubnet, ucSubnetTempLen))
    {
        return VOS_TRUE;
    }

    /* 再比较剩余bit */
    ucSubnetBitTempLen = (pstCurrHrpdSys->ucSubnetMask % CNAS_PRL_BIT_LEN_8_BIT);
    if (0 < ucSubnetBitTempLen)
    {
        ucCurrSubnetid = CNAS_PRL_ExtractBitStringToOctet(&(pstCurrHrpdSys->aucSubnet[ucSubnetTempLen]), 0, ucSubnetBitTempLen);
        ucLastSubnetid = CNAS_PRL_ExtractBitStringToOctet(&(pstLastHrpdSys->aucSubnet[ucSubnetTempLen]), 0, ucSubnetBitTempLen);

        if (ucCurrSubnetid != ucLastSubnetid)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys
)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys;

    pstLastHrpdSys = &(CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0]);

    /* subnet-id change时，要清除协议CDG143里面5.7.7和5.8.1中描述的两个计数器 */
    if (VOS_TRUE == CNAS_HSD_IsSubnetIdChange(pstCurrHrpdSys, pstLastHrpdSys))
    {
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT);
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_TCA_TIMEOUT);
    }

    return;
}


VOS_VOID CNAS_HSD_ProcAvoidEventInNetwkLostInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT32                                              ulAvoidTime;
    VOS_UINT32                                              ulExpiredSliceNum;

    ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_FAIL_CONTINUE_THREE_TIMES);

    ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

    CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                     CNAS_HSD_GetSystemSlice(),
                                     ulExpiredSliceNum);

    /* 如果avoid timer未启动，启动avoid timer定时器 */
    if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                  TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                  0))
    {
        CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                            TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
    }

    return;
}


VOS_UINT32 CNAS_HSD_IsNeedAvoidedInNonHbrid(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enSysMode;

    enSysMode = CNAS_HSD_GetModeType();

    /* CDG143 6.4,非混合模式下，一下两种场景不需要进行avoid处理 */
    if (((CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE == enAvoidReason)
      || (CNAS_HSD_AVOID_TCA_TIMEOUT == enAvoidReason))
     && (CNAS_HSD_SYS_MODE_NONHYBRID == enSysMode))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


#endif

/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



