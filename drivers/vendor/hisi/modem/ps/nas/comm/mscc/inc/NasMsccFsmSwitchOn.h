
#ifndef __NAS_MSCC_FSM_SWITCH_ON_H__
#define __NAS_MSCC_FSM_SWITCH_ON_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasMsccPifInterface.h"
#include  "NasMsccSndMmc.h"
#include  "NasMsccCtx.h"
#include  "NasMsccTimerMgmt.h"
#include  "NasMsccSndImsa.h"
#include  "NasMsccFsmSwitchOnTbl.h"
#include  "NasMsccSndXsd.h"
#include  "NasMsccSndHsd.h"
#include  "NasMsccSndInternalMsg.h"


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
#ifdef DMT
extern NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8 genCardReadStubTypeForDmt;
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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 NAS_MSCC_RcvMmaStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_SndUsimmReadFileReq_SwitchOn(VOS_VOID);
#endif

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 NAS_MSCC_RcvImsaStartCnf_SwitchOn_WaitImsaStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaStartCnfExpired_SwitchOn_WaitImsaStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_MSCC_RcvMmcStartCnf_SwitchOn_WaitMmcStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcStartCnfExpired_SwitchOn_WaitMmcStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvXsdStartCnf_SwitchOn_WaitXsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvTiWaitXsdStartCnfExpired_SwitchOn_WaitXsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvHsdStartCnf_SwitchOn_WaitHsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvTiWaitHsdStartCnfExpired_SwitchOn_WaitHsdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvUsimmReadFileCnf_SwitchOn_WaitCardReadCnf(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitCardReadTimerExpire_SwitchOn_WaitCardReadCnf(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
);
#endif


NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetCsimStatus_SwitchOn();

NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetUsimStatus_SwitchOn();

NAS_MSCC_PIF_RAT_PRIO_STRU* NAS_MSCC_GetRatPrio_SwitchOn(VOS_VOID);
VOS_VOID NAS_MSCC_SndStartReq_SwitchOn(
    VOS_UINT32                          ulReceivePid
);

VOS_VOID NAS_MSCC_ProcTimerExpired_SwitchOn(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_ProcMlplMsplReadRslt_SwitchOn(VOS_VOID);

VOS_VOID NAS_MSCC_ClearWaitCardReadCnfFlg_SwitchOn(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
);
#endif




#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif
#endif

