/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmGetGeo.h
  版 本 号   : 初稿
  作    者   : sunjitan 00193151
  生成日期   : 2015年05月08日
  最近修改   :
  功能描述   : NasMmcFsmGetGeo.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月08日
    作    者   : sunjitan 00193151
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __NASMMCFSMGETGEO_H__
#define __NASMMCFSMGETGEO_H__

#include "vos.h"
#include "NasMmlCtx.h"
#include "CssInterface.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcSndCss.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

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

VOS_UINT32 NAS_MMC_RcvMsccGetGeoReq_GetGeo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitCssBandScanCnfExp_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvCssStopBandScanCnf_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvTiWaitCssStopBandScanCnfExp_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasGetGeoCnfExp_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasGetGeoExp_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasStopGetGeoExp_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasStopGetGeoExp_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExp_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExp_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmGetGeoCnfExp_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmStopPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopGetGeoCnfExp_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExp_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_VOID NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo(VOS_VOID);
VOS_VOID NAS_MMC_LogSndCssBandScanReq_GetGeo(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU         *pstCssScanInfo
);
VOS_VOID NAS_MMC_LOG_PrioRatList_GetGeo(VOS_VOID);
VOS_VOID NAS_MMC_BuildCommBandScanInfo_GetGeo(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU        *pstCssScanInfo
);
VOS_VOID NAS_MMC_InitFsmGetGeoRatPrioListCtx_GetGeo(VOS_VOID);
VOS_VOID NAS_MMC_ConvertNasRatTypeToCssRatType_GetGeo(
    CSS_RAT_LIST                       *pstCssBandScanRatList
);

NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_ConvertCoverageType_GetGeo(
    CSS_COVERAGE_TYPE_ENUM_UINT8        enSrcCoverageType
);
VOS_VOID NAS_MMC_PerformBandScan_GetGeo(VOS_VOID);

VOS_VOID NAS_MMC_UpdateGetGeoRatCoverageType_GetGeo(
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf,
    NAS_MMC_GET_GEO_RAT_INFO_STRU      *pstDestRatInfo
);
VOS_VOID NAS_MMC_UpdateGetGeoRatPrioListCtx_GetGeo(
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf
);


VOS_UINT32 NAS_MMC_GetNextGetGeoRat_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penDestRat
);

VOS_VOID NAS_MMC_SetRatIsSearchedInGetGeoRatPrioList_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
);

VOS_VOID NAS_MMC_SuspendCurrentRat_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
);

VOS_VOID NAS_MMC_SndAsGetGeoReq_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
);
VOS_VOID NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
);
VOS_VOID NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    struct MsgCB                       *pstMsg,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32  NAS_MMC_IsMsccGetGeo_GetGeo(VOS_VOID);

VOS_VOID NAS_MMC_ProcGetGeoRslt_GetGeo(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGeoPlmn
);

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

#endif
