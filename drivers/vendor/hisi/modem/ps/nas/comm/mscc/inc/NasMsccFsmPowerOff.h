/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmPowerOff.h
Author          :   k902809
Version         :
Date            :   2015-01-31
Description     :   Contains Event handlers of MSCC Power-off FSM.
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/

#ifndef _NAS_MSCC_FSM_POWER_OFF_H_
#define _NAS_MSCC_FSM_POWER_OFF_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasMsccCtx.h"
#if (FEATURE_IMS == FEATURE_ON)
#include  "NasMsccSndImsa.h"
#endif
#include  "NasMsccSndMmc.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include  "NasMsccSndXsd.h"
#include  "NasMsccSndHsd.h"
#endif


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
VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 NAS_MSCC_RcvImsaPowerOffCnf_PowerOff_WaitImsaPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PowerOff_WaitImsaPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_UINT32 NAS_MSCC_RcvMmcPowerOffCnf_PowerOff_WaitMmcPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerOffCnfExpired_PowerOff_WaitMmcPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvXsdPowerOffCnf_PowerOff_WaitXsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitXsdPowerOffCnfExpired_PowerOff_WaitXsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerOffCnf_PowerOff_WaitHsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerOffCnfExpired_PowerOff_WaitHsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvXsdPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitCLPowerSaveCnfExpired_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MSCC_ProcPowerSaveComplete(VOS_VOID);

VOS_UINT32 NAS_MSCC_RcvTiScanTimerExpired_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_PowerOff_WaitHrpdLtePowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_PowerOff_WaitHrpdLtePowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallSuccessNtf_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_VOID NAS_MSCC_SndPowerOffReq(
    VOS_UINT32                                      ulReceivePid
);

NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 NAS_MSCC_GetPowerOffCause(VOS_VOID);

VOS_VOID NAS_MSCC_ProcPowerOffComplete(VOS_VOID);

VOS_VOID NAS_MSCC_ProcPowerOffExpired(VOS_VOID);


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

#endif /* end of NasMsccFsmPowerOff.h */


