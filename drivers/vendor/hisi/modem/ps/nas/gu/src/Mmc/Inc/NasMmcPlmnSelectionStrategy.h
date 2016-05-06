/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcPlmnSelectionStrategy.h
  版 本 号   : 初稿
  作    者   : sunxibo /46746
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NasMmcPLmnSelectionStrategy.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 phase II

******************************************************************************/
#ifndef _NAS_MMC_PLMN_SELECTION_STRATEGY_H_
#define _NAS_MMC_PLMN_SELECTION_STRATEGY_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasFsm.h"
#include  "NasMmcSndInternalMsg.h"
#include  "NasMmcCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_PLMN_SELECTION_MAX_RAND              (0x7fff)

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
typedef VOS_INT (* NAS_COMP_PLMN_PRIO_FUNC)(const VOS_VOID*, const VOS_VOID*);

typedef VOS_VOID  (*pNasMmcPlmnSelectionListInitFunc)(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

/*****************************************************************************
 结构名    : NAS_MMC_PLMN_SELECTION_LIST_INIT_TBL_STRU
 结构说明  : 保存不同搜网场景搜网列表初始化函数
 1.日    期   : 2011年7月04日
   作    者   : s46746
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32  enPlmnSearchScene;  /*搜网场景*/
    pNasMmcPlmnSelectionListInitFunc       pfunPlmnSearchInit; /*对应场景的搜网列表初始化函数指针*/
}NAS_MMC_PLMN_SELECTION_LIST_INIT_TBL_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enSearchScene
);
VOS_UINT32 *NAS_MMC_GetNeedHistorySearchSceneTblAddr(VOS_VOID);
VOS_UINT16 NAS_MMC_GetNeedHistorySearchSceneTblSize(VOS_VOID);


VOS_UINT16 NAS_MMC_GetNeedPrefBandSearchSceneTblSize(VOS_VOID);
VOS_UINT32 *NAS_MMC_GetNeedPrefBandSearchSceneTblAddr(VOS_VOID);
VOS_UINT32 NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enSearchScene
);

VOS_INT32  NAS_MMC_CompareRoamPlmnPrio(
    const VOS_VOID                  *pPlmn1Info,
    const VOS_VOID                  *pPlmn2Info,
    NAS_MML_PLMN_RAT_PRIO_STRU      *pstPrioRatList
);


VOS_VOID NAS_MMC_InitPlmnSelectionList(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);


VOS_VOID NAS_MMC_InitPlmnSelectionList_SwitchOn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_AreaLost(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_InterSysOos(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_UserAutoResel(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);


VOS_VOID NAS_MMC_InitPlmnSelectionList_SyscfgSet(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);


VOS_VOID NAS_MMC_InitPlmnSelectionList_AvailTimerExpire(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);
VOS_VOID NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_UserList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_DisableLte(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  					*pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU  *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionListCsfbServiceRej(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU   *pstSearchedPlmnListInfo
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_InitPlmnSelectionList_EnableLte(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_CsfbAbort(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);
#endif




VOS_VOID NAS_MMC_InitPlmnSelectionList_CsfbEnd(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionListRfEnable(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

/* Added by s00246516 for L-C互操作项目, 2014-02-11, Begin */
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegNCell(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_RegHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_RegPrefPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);
/* Added by s00246516 for L-C互操作项目, 2014-02-11, End */

VOS_VOID NAS_MMC_BuildNcellPlmnSelectionPlmnList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    VOS_UINT8                                              ucChangePrioRatOrder,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_BuildPlmnSelectionPlmnInfo(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    VOS_UINT16                                              usSimRat,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
);

VOS_VOID NAS_MMC_AddEHPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_AddEHPlmnInDestPlmnList(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo
);

VOS_VOID NAS_MMC_AddEPlmnInDestPlmnList(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList
);

VOS_VOID NAS_MMC_AddDplmnInDestPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     *pstDestPlmnList
);

VOS_VOID NAS_MMC_AddUOPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_AddOPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);
VOS_VOID NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);
VOS_VOID NAS_MMC_AddRPlmnInPlmnSelectionList(
    NAS_MML_PLMN_RAT_PRIO_STRU            *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_AddSpecPlmnInPlmnSelectionList(
    NAS_MML_PLMN_ID_STRU                  *pstPlmn,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8           enPlmnType,
    NAS_MML_PLMN_RAT_PRIO_STRU            *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_AppendPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_UINT32 NAS_MMC_InsertPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo,
    VOS_UINT32                             ulPos
);

VOS_VOID NAS_MMC_InsertPlmnToPlmnSelectionListHead(
    NAS_MML_PLMN_ID_STRU                  *pstPlmn,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8           enPlmnType,
    NAS_MML_PLMN_RAT_PRIO_STRU            *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstDstPlmn
);

VOS_VOID NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmn,
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_UINT32 NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(
    VOS_UINT32                                              ulAvailPlmnListNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstAvailPlmnList,
    NAS_MMC_NET_QUALITY_ENUM_UINT8                          enPlmnQuality,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);



VOS_VOID NAS_MMC_SortRatPrioSpecRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enPrioRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU            *pstPrioRatList
);

VOS_VOID NAS_MMC_SortPlmnListRandom(
    VOS_UINT32                             ulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmnList
);

VOS_VOID NAS_MMC_SortPlmnListPrioRat(
    VOS_UINT32                                             *pulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
);

VOS_VOID NAS_MMC_SortPlmnListSignalDecrease(
    VOS_UINT32                             ulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmnList
);

VOS_VOID NAS_MMC_SortAvailPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8           enPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(
    NAS_MMC_NET_QUALITY_ENUM_UINT8                          enNetQuality,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList(
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8           enSrcPlmnType,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8           enDestPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstPlmnSelectionListInfo
);

VOS_UINT32 NAS_MMC_GetNextSearchPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    VOS_UINT32                                              ulUserSpecPlmnSearch,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_UINT32 NAS_MMC_UpdatePlmnRatInfoInSearchList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    VOS_UINT8                                                ucIsAllBandSearch

);

VOS_VOID NAS_MMC_DelPlmnInSearchList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo
);


VOS_VOID NAS_MMC_UpdatePlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulAppendFlg,
    VOS_UINT8                                                ucIsAllBandSearch

);

NAS_MMC_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnTypeInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_LogAsPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
);

VOS_VOID NAS_MMC_LogDplmnNplmnList(VOS_VOID);

VOS_VOID NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_NET_STATUS_ENUM_UINT8                          *paucNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_UINT32 NAS_MMC_GetRPlmn_PlmnSelectionStrategy(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus,
    VOS_UINT32                          ulUserSpecPlmnSearch
);

VOS_VOID NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(
    VOS_UINT32                                              ulAvailPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstAvailPlmnList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_SavePlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_InitNetStatusInRatSearchInfo(
    NAS_MMC_NET_STATUS_ENUM_UINT8      *paucNetStatus,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList,
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo
);
#endif

VOS_VOID NAS_MMC_RefreshEPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList
);

VOS_VOID NAS_MMC_RefreshCurPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType
);

VOS_VOID NAS_MMC_LogPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList
);

VOS_UINT32 NAS_MMC_IsHPlmnPrioSearch( VOS_VOID );

VOS_UINT32 NAS_MMC_IsRPlmnFirstSearchWithHPlmn(VOS_VOID);


VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_UINT32 NAS_MMC_GetNextSearchHighPrioPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU  *pstHighPrioPlmnInfo,
    NAS_MML_PLMN_WITH_RAT_STRU             *pstVPlmn,
    NAS_MML_EQUPLMN_INFO_STRU              *pstEplmnList
);

VOS_UINT32 NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(
    NAS_MML_PLMN_ID_STRU                                   *pstVPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo
);

VOS_UINT32 NAS_MMC_GetHighestPrioPlmnInHighPrioPlmnList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo
);

VOS_VOID  NAS_MMC_DelSpecPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_DelSpecNetStatusRat(
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_NET_STATUS_ENUM_UINT8                          *pstNetStatus,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
);

VOS_VOID NAS_MMC_AddSearchedPlmnListInfoInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);
#endif

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
VOS_VOID NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);
/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

VOS_UINT8  NAS_MMC_IsNeedNcellSearch(VOS_VOID);

VOS_UINT8 NAS_MMC_IsNeedChangeNcellSearchRatOrder(VOS_VOID);

VOS_UINT32 NAS_MMC_IsHighPrioPlmnSameCountry(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo,
    NAS_MML_PLMN_ID_STRU                                   *pstVPlmnId
);
NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetRoamPlmnType(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstPlmnInfo
);

VOS_VOID NAS_MMC_AppendPlmnInRoamPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstPlmn,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedPlmnListInfo
);
VOS_VOID NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
);

VOS_VOID NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat,
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstPlmnInfo
);

NAS_MMC_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

NAS_MMC_NET_STATUS_ENUM_UINT8 NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnIdList,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
);

VOS_VOID NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstSearchedExistPlmnInfo
);

VOS_INT32  NAS_MMC_CompareRoamPlmnPrio(
    const VOS_VOID                  *pPlmn1Info,
    const VOS_VOID                  *pPlmn2Info,
    NAS_MML_PLMN_RAT_PRIO_STRU      *pstPrioRatList
);

VOS_VOID NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(
    VOS_UINT32                                              ulPlmnSearchNum,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnIdList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulAppendFlg,
    VOS_UINT8                                                ucIsAllBandSearch

);

VOS_UINT16 NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enSpecPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);


VOS_VOID NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList
);


VOS_UINT8 NAS_MMC_GetRoamPlmnPrio(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnInfo
);

VOS_VOID NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
);

VOS_VOID NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
);

VOS_VOID NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetPrioRat_SyscfgSet(VOS_VOID);

VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioRatHplmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);
VOS_VOID NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
);
VOS_UINT32 NAS_MMC_IsPlmnInSearchList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo
);
VOS_VOID NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
);
VOS_UINT32  NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
);
VOS_VOID NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_InitPlmnSelectionList_DplmnSet(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_UINT32 NAS_MMC_IsPlmnIdInSearchedPlmnList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);


VOS_UINT8  NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13(VOS_VOID);

VOS_VOID NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                   *pstPlmnIdWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU        *pstPlmnSelectionListInfo
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                   *penSrchType
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

#endif /* end of NasMmcPlmnSelectionStrategy.h */

