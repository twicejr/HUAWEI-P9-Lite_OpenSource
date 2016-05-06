/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdComFunc.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : CnasXsdComFunc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月3日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_COM_FUNC_H__
#define __CNAS_XSD_COM_FUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdTimer.h"

#include  "xsd_xreg_pif.h"
#include  "xsd_mscc_pif.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include "CnasXsdCtx.h"

#include "PsRrmInterface.h"

#include "cas_1x_idlectrl_proc_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XSD_MAX_MCC                           (999)
#define CNAS_XSD_MAX_IMSI11_12                     (99)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef DMT
extern VOS_UINT32                       g_ulCurSlice;
#endif

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
 结构名    : CNAS_XSD_AVOID_TIMER_CTRL_STRU
 结构说明  : avoid timer ctrl info structure
 1.日    期   : 29/12/2014
   作    者   : W00176964
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason;                              /* avoid reason */
    VOS_UINT8                           ucReserved;    
    VOS_UINT16                          usAvoidTimerLen;                            /* avoid timer length */
}CNAS_XSD_AVOID_TIMER_CTRL_STRU;

/*****************************************************************************
 结构名    : NA
 结构说明  : 每个频段所支持的频点函数指针
 1.日    期   : 2015年8月07日
   作    者   : c00299063
   修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT8 (*pCNasXsdBandSupportChanBuildFunc)(
    VOS_UINT16                          usChannel
);

/*****************************************************************************
 结构名    : CNAS_XSD_CHANNEL_SUPPORTED_IN_BANDCLASS_TBL_STRU
 结构说明  : 每个频段所支持的频点
 1.日    期   : 7/8/2015
   作    者   : c00299063
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandClass;
    pCNasXsdBandSupportChanBuildFunc    pfunBandSupportChanBuild;                            /* avoid timer length */
}CNAS_XSD_CHANNEL_SUPPORTED_IN_BANDCLASS_TBL_STRU;



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

VOS_VOID CNAS_XSD_StartTimer(
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
);

VOS_VOID CNAS_XSD_StopTimer(
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId
);

VOS_UINT16 CNAS_XSD_GetAvoidTimerLen(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enReason,
    VOS_UINT16                          usAvoidTimes
);

VOS_VOID CNAS_XSD_UpdataAvoidListInfo(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

VOS_VOID CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq
);

VOS_UINT32 CNAS_XSD_GetSystemSlice(VOS_VOID);

VOS_UINT32 CNAS_XSD_GetSystemSliceNumOfOneSecond(VOS_VOID);

CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 CNAS_XSD_TransferMsccCallTypeToXsdFormat(
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8          enMsccCallType
);

VOS_UINT8 CNAS_XSD_IsUeSupportedFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreqChan
);

VOS_VOID CNAS_XSD_SaveRedirectionInfo(
    CNAS_CAS_1X_REDIRECTION_INFO_STRU  *pstCasRedirInfo
);

VOS_VOID CNAS_XSD_RemoveNegativeFreqs(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstSysId,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstSrcFreqInfo,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstDstFreqInfo
);

VOS_VOID CNAS_XSD_ProcCasOhmInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstMsg,
    VOS_UINT32                          ulIsNegSys
);

VOS_VOID CNAS_XSD_UpdateReturnCauseValue(
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList
);
CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 CNAS_XSD_GetCurrentSystemRoamingInd(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
);

NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 CNAS_XSD_GetCurrentSystemPriClass(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    MSCC_XSD_SYS_TYPE_ENUM_UINT8        enSysType
);

VOS_VOID CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                  *penMatchPrio
);

VOS_VOID CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                  *penMatchPrio
);




VOS_UINT32 CNAS_XSD_TransformMccToBcd(
    VOS_UINT16                          usMcc
);

VOS_UINT16 CNAS_XSD_TransformImsiToBcd(
    VOS_UINT8                           ucImsi
);

VOS_VOID CNAS_XSD_StopAllTimerExceptSpecifiedTimerId(
    VOS_UINT32                          ulTimerId
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_0(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_1(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_2(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_3(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_4(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_5(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_6(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_7(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_8(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_9(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_10(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_11(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_12(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_13(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_14(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_15(
    VOS_UINT16                          usChannel
);

VOS_UINT8 CNAS_XSD_IsAddInAvoidList(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8                        enReason
);


VOS_VOID CNAS_XSD_DeleteUsableFreqFormAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
);

VOS_VOID CNAS_XSD_RegisterRrmResourceNtf(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
);

VOS_VOID CNAS_XSD_DeRegisterRrmResourceNtf(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
);

CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16 CNAS_XSD_ConvertSrvTypeToSessionType(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType
);

VOS_UINT32 CNAS_XSD_IsSidInOperLockSysWhiteList(
    VOS_UINT16                          usSid
);

VOS_UINT32 CNAS_XSD_IsMccInOperLockSysWhiteList(
    VOS_UINT32                          ulMcc
);

VOS_VOID CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMatchedGeoList,
    VOS_UINT16                                             *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecordList,
    VOS_UINT16                                             *pusMorePrefSysNum
);

VOS_VOID CNAS_XSD_GetGeoListFromPrlSysRecordInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoList
);

VOS_UINT16 CNAS_XSD_CalcPrlSysRecListTotalFreqNum(
    VOS_UINT16                          usSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

VOS_UINT32 CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
);

VOS_UINT32 CNAS_XSD_IsCurSystemInAvailSysList(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
);

VOS_VOID CNAS_XSD_QuitCallBackMode( VOS_VOID );

VOS_UINT32 CNAS_XSD_IsCurSysNotSuitableSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
);

VOS_UINT32 CNAS_XSD_Is1xSysNegative(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
);

VOS_UINT32 CNAS_XSD_IsCurSysInSysWhiteList
(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
);

VOS_VOID CNAS_XSD_BuildSysRecordListBasedOnGeo(
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

VOS_VOID CNAS_XSD_ReducePriLvlInSysRecordList(
    VOS_UINT16                          usTmpSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord,
    VOS_UINT16                          usReducePriLvl
);

VOS_UINT32 CNAS_XSD_AddGeoIntoCompsiteGeo(
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeo,
    VOS_UINT16                         *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecordList,
    VOS_UINT16                         *pusPriLvl
);

VOS_UINT8 CNAS_XSD_GetAvoidTimesOfAvoidFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

VOS_UINT8 CNAS_XSD_IsAddSyncFailFreqInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSyncFailFreq,
    VOS_UINT32                          ulSyncFailSlice,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason 
);

VOS_VOID CNAS_XSD_ClearAccessSuccessFreqFormAvoidList(VOS_VOID);

VOS_VOID CNAS_XSD_ClearAvoidCountFromAvoidList(
    VOS_UINT8                           ucAvoidListIndex, 
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason    
);

VOS_UINT8 CNAS_XSD_IsClearFreqInfoOfAvoidList(
    VOS_UINT8                           ucAvoidListIndex    
);

VOS_VOID CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(
    VOS_UINT8                           ucAvoidListIndex
);

VOS_UINT8 CNAS_XSD_IsExistAvoidFlagInAvoidlist(VOS_VOID);

VOS_VOID CNAS_XSD_DeleteAcqSuccFreqOfAvoidList(    
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
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

#endif /* end of __CNAS_XSD_COM_FUNC_H__ */
