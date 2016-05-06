


#ifndef __CNAS_EHSM_FSM_MAIN_H__
#define __CNAS_EHSM_FSM_MAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasEhsmCtx.h"


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
VOS_UINT32 CNAS_EHSM_RcvHsdStartReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmAttachReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEsmSyncPdnInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPsRatTypeNotify_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnAttachReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsReconnReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivateReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvEhsmLocalDetachAllReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmActivatingRsltCnf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsLocalDeactiveNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmActivatingRsltCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmDeactivatingRsltCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivateReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEsmSyncPdnInfoInd_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsLocDetachNotify_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPsRatTypeNty_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsLocDeactivateNty_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsLocDetachNotify_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmPdnSetupReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdDetachInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvApsPsRatTypeNty_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvHsmSuspendInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvApsLocDeactivateNty_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_EHSM_RcvEhsmLocalDetachAllReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsDiscNotify_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvPppModifyInd_Active(
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

#endif /* end of CnasEhsmFsmMain.h */


