/******************************************************************************

                  版权所有 (C), 2014-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdAvoidStrategy.h
  版 本 号   : 初稿
  作    者   : x00306642
  生成日期   : 2015年01月15日
  最近修改   :
  功能描述   : CnasHsdAvoidStrategy.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月15日
    作    者   : x00306642
    修改内容   : Added for HRPD

******************************************************************************/
#ifndef _CNAS_HSD_AVOID_STRATEGY_H_
#define _CNAS_HSD_AVOID_STRATEGY_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "hsm_hsd_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 连续8次SESSION NEGOTIATION TIMEOUT后，avoid time的值不随counter值变化 */
#define CNAS_HSD_AVOID_SESSION_COUNTER_MAX      (7)

/* 连续7次MAX ACCESS PROBES FAILURE后，avoid time的值不随counter值变化 */
#define CNAS_HSD_AVOID_PROBE_COUNTER_MAX        (6)

/* 连续三次BUSY_OR_GENERAL_FAILURE时要重新搜网 */
#define CNAS_HSD_AVOID_BUSY_COUNTER_MAX         (3)

/* 连续三次TCA timeout时要重新搜网 */
#define CNAS_HSD_AVOID_TCA_COUNTER_MAX          (3)

/* avoid time中的30sec和60sec */
#define CNAS_HSD_AVOID_TIME_30_SEC              (30)

#define CNAS_HSD_AVOID_TIME_60_SEC              (60)

#define CNAS_HSD_AVOID_NETWORK_LOST_MAX_CNT     (3)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_Without_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_With_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_VOID CNAS_HSD_IncreaseAvoidFreqUsedNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_DecreaseAvoidFreqUsedNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_IncreaseCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    UINT8                               ucMaxCounter
);

extern VOS_VOID CNAS_HSD_ClearCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_UINT8 CNAS_HSD_GetCounterValue(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_VOID CNAS_HSD_CheckExpiredFreqFromAvoidList(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern  VOS_VOID CNAS_HSD_DeleteItemFromAvoidList(
    VOS_UINT8                           ucIndex
);

extern CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetAvoidItemFromAvoidList(
    VOS_UINT8                           ucIndex
);

extern CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetEmptyItemFormAvoidList(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_IsCurrFreqExistedInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT8                          *ucIndex
);

extern VOS_VOID CNAS_HSD_AddAvoidInfoToAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulExpiredSliceNum
);

extern VOS_VOID CNAS_HSD_IncreaseCounterInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
);

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
);

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8 enNegResult
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInAccessRlstInd(
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenFailInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInCasStatusInd(
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enHsdATStatus
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                        *penReAcqFlag
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInCasSysSyncCnf(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInRedirection(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern VOS_UINT32 CNAS_HSD_IsSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys,
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrSysId
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInNetwkLostInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern VOS_UINT32 CNAS_HSD_IsNeedAvoidedInNonHbrid(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);


#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CNasHsdAvoidStrategy.h */


