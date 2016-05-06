


#ifndef __NAS_MSCC_FSM_BSR_H__
#define __NAS_MSCC_FSM_BSR_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_BSR_CommonProcess(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_BSR_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiRetryTimerExpired_BSR_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdBgSearchCnf_BSR_WaitHsdBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdBgSearchCnfTimeExpired_BSR_WaitHsdBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdStopBgSearchCnf_BSR_WaitHsdStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdStopBgSearchCnfTimeExpired_BSR_WaitHsdStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPlmnPriClassQueryCnf_BSR_WaitMmcPlmnPriClassQueryCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnPriClassQueryCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnPriClassQueryCnfTimeExpired_BSR_WaitMmcPlmnPriClassQueryCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfTimeExpired_BSR_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPlmnSearchCnf_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnSearchCnfTimeExpired_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPowerSaveReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveReAcqHrpdTimeExpired_BSR_WaitMmcPowerSaveReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdAcquireCnfReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdAcquireCnfReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdAcqCnfReAcqHrpdTimeExpired_BSR_WaitHsdAcquireCnfReAcqHrpd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcBgSearchCnf_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcBgSearchCnfExpired_BSR_WaitMmcBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcStopBgSearchCnf_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcStopBgSearchCnfExpired_BSR_WaitMmcStopBgSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdQryHrpdSysInfoCnf_BSR_WaitHsdQryHrpdSysInfoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitHsdQryHrpdSysInfoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdQryHrpdSysInfoCnfExpired_WaitHsdQryHrpdSysInfoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_BSR_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdSystemAcquireCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdSystemAcquireCnfExpired_BSR_WaitHsdSystemAcquireCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdSystemAcquireCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_BSR_WaitHsdPowerSaveCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPlmnSeachCnf_BSR_WaitMmcPlmnSearchCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPlmnSeachCnfExpired_BSR_WaitMmcPlmnSearchCnfReAcqLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcIntersysStartInd_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccCLInterSysRsltCnf_BSR_WaitMmcPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif /*****end of CDMA******/

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

#endif /* end of NasMsccFsmBsr.h */

