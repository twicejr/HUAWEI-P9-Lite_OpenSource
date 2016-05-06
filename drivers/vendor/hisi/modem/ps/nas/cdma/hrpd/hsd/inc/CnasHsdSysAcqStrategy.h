/******************************************************************************

                  版权所有 (C), 2014-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSysAcqStrategy.h
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2014年12月15日
  最近修改   :
  功能描述   : CnasHsdSysAcqStrategy.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月15日
    作    者   : C00299064
    修改内容   : CDMA 1X IT&1 added

******************************************************************************/
#ifndef _CNAS_HSD_SYS_ACQ_STRATEGY_H_
#define _CNAS_HSD_SYS_ACQ_STRATEGY_H_

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
#define CNAS_HSD_MRU0_NUM_4_IN_SCAN_LIST                      (4)

#define CNAS_HSD_MRU0_NUM_1_IN_SCAN_LIST                      (1)

#define CNAS_HSD_CFREQLOCK_FREQ_NUM                           (1)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : CNAS_HSD_ASSN_RLST_ENUM_UINT32
 结构说明  :
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : CNAS XSD模块发送给OM的可维可测消息
*****************************************************************************/
enum CNAS_HSD_ASSN_RLST_ENUM
{
    CNAS_HSD_ASSN_SUCC      = 0,
    CNAS_HSD_NO_ASSN_FREQ,
    CNAS_HSD_NO_ASSN_SYS,
    CNAS_HSD_NO_ASSN_WITH_HRPD,

    CNAS_HSD_ASSN_RLST_BUTT
};
typedef VOS_UINT32 CNAS_HSD_ASSN_RLST_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern VOS_UINT8                                            g_aucCnasHsdSystemLostMru0Pos[CNAS_HSD_MRU0_NUM_4_IN_SCAN_LIST];

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
 结构名    : NA
 结构说明  : 扫描频点列表初始化函数指针
 1.日    期   : 2014年8月05日
   作    者   : C00299064
   修改内容   : 新增
*****************************************************************************/
typedef VOS_VOID  (*pCNasHsdScanChanListBuildFunc)(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

/*****************************************************************************
 结构名    : CNAS_HSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU
 结构说明  : 保存不同搜网场景下频点扫描列表构造函数
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;            /* 系统捕获场景 */
    pCNasHsdScanChanListBuildFunc                           pfunScanChanListBuild;    /* 对应场景的扫描频点列表构造函数指针 */
}CNAS_HSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU;

/*****************************************************************************
 结构名    : NA
 结构说明  : 获取扫描频点列表初始化函数指针
 1.日    期   : 2015年1月22日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32  (*pCNasHsdGetScanChanListFunc)(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
);

/*****************************************************************************
 结构名    : CNAS_HSD_GET_SCAN_CHANNEL_LIST_TBL_STRU
 结构说明  : 获取不同搜网场景下扫描频点列表构造函数
 1.日    期   : 2015年1月22日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;            /* 系统捕获场景 */
    pCNasHsdGetScanChanListFunc                             pfunGetScanChanList;      /* 对应场景的扫描频点列表构造函数指针 */
}CNAS_HSD_GET_SCAN_CHANNEL_LIST_TBL_STRU;

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
extern VOS_UINT32 CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs
(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstEvdoSys,
    VOS_UINT8                          *pucPrio,
    VOS_UINT16                         *pusEvdoSysListMatchIndex
);

extern VOS_UINT32 CNAS_HSD_RefreshScanListByMatchLvl
(
VOS_UINT16                          usScanListPos,
VOS_UINT8                           ucPrio
);

extern VOS_UINT32 CNAS_HSD_IsCurrFreqStay
(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstEvdoSys
);

extern VOS_VOID CNAS_HSD_RefreshScanListIndex(VOS_UINT16 usFreqNumUsed);

extern VOS_VOID CNAS_HSD_BuildHrpdScanList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32              enSysAcqScene
);

extern VOS_VOID CNAS_HSD_BuildScanChanList_SwitchOn
(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_VOID CNAS_HSD_BuildScanChanList_PilotSearch(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_UINT16 CNAS_HSD_CalcFreqNumForScanList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysList
);
extern VOS_UINT32 CNAS_HSD_MallocMemForScanList(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU   *pstScanList,
    VOS_UINT16                           usFreqNum
);

extern VOS_UINT32 CNAS_HSD_Create1xMatchedHrpdSysRecs(
    CNAS_PRL_1X_SYSTEM_STRU                                *pst1xSys,
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstGeoListInfo
);

extern VOS_UINT32 CNAS_HSD_CreateAllHrpdSysRecs(
    CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16          enCheckAssnIncl,
    CNAS_PRL_SORT_ENUM_UINT16                     enIsSortNeeded,
    CNAS_HSD_HRPD_SYS_LIST_STRU                  *pstSysList
);

extern VOS_UINT32 CNAS_HSD_CreateHrpdSysList(
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType,
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo,
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList
);

extern VOS_UINT32 CNAS_HSD_CreateScanFreqList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enModeType,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList,
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList
);

extern VOS_UINT32 CNAS_HSD_MallocMemForSysRec(
    VOS_UINT16                   usSysRecNum,
    CNAS_HSD_HRPD_SYS_LIST_STRU *pstSysList
);

extern VOS_VOID CNAS_HSD_BuildScanChanList_SystemLost(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_VOID CNAS_HSD_BuildScanChanList_Redirection(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_VOID CNAS_HSD_BuildScanChanList_DataCallQuick(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_VOID CNAS_HSD_AddMruToScanList_SwitchOn
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                       *pstHrpdScanFreqList
);

extern VOS_VOID CNAS_HSD_AddMruToScanList_SystemLost
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                       *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_SwitchOn(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_SystemLost
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_Redirection
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_DataCallQuick
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_AddMatchedGeoFreqToScanFreqList_Redirection
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
);

extern VOS_UINT32 CNAS_HSD_FreqIsMru0Pos
(
    VOS_UINT16                          usPos
);

extern VOS_UINT32 CNAS_HSD_FreqIsSupport
(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

VOS_VOID CNAS_HSD_SortHrpdSystem
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdList
);

VOS_UINT16 CNAS_HSD_CalcMatchHrpdSystemFreqNum(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo
);

VOS_UINT32 CNAS_HSD_IsRepeatFreqInSpecPrio
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    VOS_UINT8                                               usPrio
);

VOS_UINT32 CNAS_HSD_IsRepeatFreq
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);


VOS_UINT32 CNAS_HSD_GetScanListSameLevelFreq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

VOS_UINT16 CNAS_HSD_GetNonHybridHrpdSysRecNum(
    CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16    enCheckAssnIncl
);

VOS_UINT16 CNAS_HSD_GetNonHybridHrpdSysRecList(
    CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16    enCheckAssnIncl,
    CNAS_HSD_HRPD_SYS_LIST_STRU            *pstSysRecIList
);

VOS_UINT16 CNAS_HSD_GetHybridHrpdSysRecNum(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU     *pstGeoInfoList
);
VOS_UINT16 CNAS_HSD_GetHybridHrpdSysRecList(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU    *pstGeoList,
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU         *pstHrpdSysItem,
    VOS_UINT16                               usAviHrpdSysNum,
    VOS_UINT16                               usPivotDeltLevel
);


extern VOS_VOID CNAS_HSD_BuildScanChanList_OocMru0(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_UINT32 CNAS_HSD_GetScanChanListFromMru0_Ooc(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
);

extern CNAS_HSD_ASSN_RLST_ENUM_UINT32 CNAS_HSD_CheckHrpdFreqAssnWith1X(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
);

extern VOS_VOID CNAS_HSD_BuildScanChanList_HighPriority(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_HighPriority(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
);

extern VOS_UINT8 CNAS_HSD_IsCurHrpdSysNeedInHighPriScene(
    VOS_UINT16                          usSysIndex,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

extern VOS_UINT8 CNAS_HSD_IsCurHrpdSysInHighPriList(
    VOS_UINT16                                              usSysIndex
);

extern VOS_UINT8 CNAS_HSD_IsCurSysSubnetWildCard(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

extern CNAS_HSD_ASSN_RLST_ENUM_UINT32 CNAS_HSD_CheckHrpdSysAssnWith1X(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
);


VOS_VOID CNAS_HSD_GetMostMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
);
extern VOS_VOID CNAS_HSD_BuildScanChanList_CFreqLock(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

extern VOS_VOID CNAS_HSD_ProcMru0Relate(
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstFreqInfo
);
VOS_VOID CNAS_HSD_SortHrpdSystem_NoHybrid
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdList
);

VOS_VOID CNAS_PRL_SortHrpdSystem_Hybrid
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdList
);

VOS_UINT32 CNAS_HSD_GetPivot1xSysPriosInGeos
(
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstGeoList,
    VOS_UINT8                                              *pucPivotDeltPrio
);

VOS_UINT32 CNAS_HSD_Is1xSysStillMatchHrpdSearchList
(
    CNAS_PRL_1X_SYSTEM_STRU            *pstHrpdSrcSys, /*  生成HRPD列表的1x系统 */
    CNAS_PRL_1X_SYSTEM_STRU            *pstDstSys
);

VOS_UINT32 CNAS_HSD_Get1XMostMatchedGeoList
(
    CNAS_PRL_1X_SYSTEM_STRU                                *pst1xSrcSys,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMostMatchedGeoList
);

VOS_UINT32 CNAS_HSD_IsTheHrpdSysAsso1xSys
(
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSrcHrpdSys,
    CNAS_PRL_EXT_SYS_RECORD_STRU                          **ppst1xSys,
    VOS_UINT8                                               uc1xSysNum
);

extern VOS_VOID CNAS_HSD_GetAcqedHrpdSysMatchIndexList(
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys
);

extern VOS_UINT32 CNAS_HSD_IsAcqedHrpdSysInMatchIndexList(
    VOS_UINT16                                              usSysIndex
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

#endif /* end of CNasHsdSysAcqStrategy.h */


