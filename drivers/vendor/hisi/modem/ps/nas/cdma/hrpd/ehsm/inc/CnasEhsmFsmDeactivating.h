

#ifndef __CNAS_EHSM_FSM_DEACTIVATING_H__
#define __CNAS_EHSM_FSM_DEACTIVATING_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "CnasEhsmSndAps.h"
#include "CnasEhsmSndEsm.h"
#include "CnasEhsmSndHsd.h"
#include "CnasEhsmSndHsm.h"
#include "CnasEhsmSndPpp.h"
#include "CnasEhsmComFunc.h"
#include "ehsm_hsd_pif.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmFsmDeactivatingTbl.h"

    /* To Do: Need to add interface file */

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/


/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Deactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivate_Deactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscCnf_Deactivating_WaitPdnDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdDetachCnf_Deactivating_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Deactivating_WaitPdnDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmConnEstCnf_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitConnRetryEst_Deativating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Deativating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitHsmConnEstCnf_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_EHSM_RcvTiWaitCttfPdnDiscCnf_Deactivating_WaitPdnDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvTiCttfEhrpdDetachCnf_Deactivating_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvTiProtectingPowerOff_Deactivating_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Deactivating_WaitPdnDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Deactivating_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitPdnDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvTiProtectingPowerOff_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_ProcConnEstFail_Deactivating(
    EHSM_HSM_RSLT_ENUM_UINT32           enHsmEhsmRslt,
    VOS_UINT32                          ulIsTimeOutReason
);

VOS_VOID CNAS_EHSM_IncreConntRetryTimes_Deactivating(VOS_VOID);

VOS_VOID CNAS_EHSM_ResetConntRetryTimes_Deactivating(VOS_VOID);

VOS_VOID CNAS_EHSM_ProcAbortMsg_Deactivating(
    VOS_UINT32                enCause
);

VOS_UINT32 CNAS_EHSM_RcvApsDiscNotify_Deactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmDiscCnf_Deactivating_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitHsmDiscCnf_Deactivating_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Deactivating_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscCnf_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnDiscCnfExpired_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdDetachCnf_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiCttfEhrpdDetachCnf_Deactivating_WaitHsmConnEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdReconnInd_Deactivating_WaitPdnDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdReconnInd_Deactivating_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscCnf_Deactivating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Deactivating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnDiscCnfExpired_Deactivating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasEhsmDeactivating.h */


