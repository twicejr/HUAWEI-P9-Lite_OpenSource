


#ifndef __CNAS_XSD_FSM_REDIR_H__
#define __CNAS_XSD_FSM_REDIR_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdCtx.h"
#include  "cas_1x_control_initialstate_nas_pif.h"


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


/* State: CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS act table */
VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


/* State: CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS act table */
VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnfOrigSys
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



/*State: CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND*/
VOS_UINT32 CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID CNAS_XSD_ProcCasSyncCnfSucc_Redir(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);
VOS_VOID CNAS_XSD_ProcCasSyncCnfFail_Redir(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);
VOS_VOID CNAS_XSD_ContinueSyncRedirScanList_Redir(
    VOS_UINT16                          usDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
);
VOS_VOID CNAS_XSD_ProcRedirScanListSyncComplete_Redir(VOS_VOID);
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID CNAS_XSD_PerformAbortProcedure_Redir(VOS_VOID);
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfTimerExpired_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID CNAS_XSD_QuitFsmRedir_Redir(VOS_VOID);

VOS_VOID CNAS_XSD_ContinueRedir_Redir(VOS_VOID);

VOS_UINT32 CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_Redir(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvXsdRedirInd_Redir_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasXsdFsmRedir.h */


