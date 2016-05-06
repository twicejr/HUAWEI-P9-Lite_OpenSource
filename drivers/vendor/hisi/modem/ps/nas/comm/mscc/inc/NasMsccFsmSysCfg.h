
#ifndef __NAS_MSCC_FSM_SYS_CFG_H__
#define __NAS_MSCC_FSM_SYS_CFG_H__

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
#include  "NasMsccFsmSysCfgTbl.h"
#include  "NasMsccSndXsd.h"
#include  "NasMsccSndHsd.h"
#include  "NasMsccSndInternalMsg.h"
#include  "NasMsccComFunc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_GSM_SUPPORT            0x0001
#define NAS_MSCC_UMTS_SUPPORT           0x0002
#define NAS_MSCC_LTE_SUPPORT            0x0004
#define NAS_MSCC_1X_SUPPORT             0x0008
#define NAS_MSCC_HRPD_SUPPORT           0x0010

#define NAS_MSCC_GU_SUPPORT             0x0003
#define NAS_MSCC_GL_SUPPORT             0x0005
#define NAS_MSCC_UL_SUPPORT             0x0006
#define NAS_MSCC_GUL_SUPPORT            0x0007
#define NAS_MSCC_1X_LTE_SUPPORT         0x000C
#define NAS_MSCC_HRPD_LTE_SUPPORT       0x0014
#define NAS_MSCC_1X_HRPD_SUPPORT        0x0018
#define NAS_MSCC_1X_HRPD_LTE_SUPPORT    0x001C


#define NAS_MSCC_GET_SYS_CFG_RAT_TYPE_MAP_TBL_PTR()  (g_astNasMsccSysCfgRatTypeMapTbl)
#define NAS_MSCC_GET_SYS_CFG_RAT_TYPE_MAP_TBL_SIZE() (sizeof(g_astNasMsccSysCfgRatTypeMapTbl)/sizeof(NAS_MSCC_SYS_CFG_RAT_TYPE_MAP_STRU))






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


enum NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE
{
    NAS_MSCC_SYSCFG_SUPPORT_GSM                 = 0x0000,
    NAS_MSCC_SYSCFG_SUPPORT_UMTS                = 0x0001,
    NAS_MSCC_SYSCFG_SUPPORT_LTE                 = 0x0002,
    NAS_MSCC_SYSCFG_SUPPORT_GU                  = 0x0003,
    NAS_MSCC_SYSCFG_SUPPORT_GL                  = 0x0004,
    NAS_MSCC_SYSCFG_SUPPORT_UL                  = 0x0005,
    NAS_MSCC_SYSCFG_SUPPORT_GUL                 = 0x0006,
    NAS_MSCC_SYSCFG_SUPPORT_1X                  = 0x0007,
    NAS_MSCC_SYSCFG_SUPPORT_HRPD                = 0x0008,
    NAS_MSCC_SYSCFG_SUPPORT_1X_HRPD             = 0x0009,
    NAS_MSCC_SYSCFG_SUPPORT_1X_LTE              = 0x000A,
    NAS_MSCC_SYSCFG_SUPPORT_HRPD_LTE            = 0x000B,
    NAS_MSCC_SYSCFG_SUPPORT_1X_HRPD_LTE         = 0x000C,

    NAS_MSCC_SYSCFG_SUPPORT_BUTT
};

typedef VOS_UINT16 NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16;





typedef struct
{
    VOS_UINT16                                              ulRatTypeFlg;
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16            enRatType;
} NAS_MSCC_SYS_CFG_RAT_TYPE_MAP_STRU;

#ifdef DMT

typedef struct
{
    VOS_UINT8 ulXsdPowerSaveCnfFailureFlag;
    VOS_UINT8 ulHsdPowerSaveCnfFailureFlag;
    VOS_UINT8 ulMmcPowerSaveCnfFailureFlag;
    VOS_UINT8 ulXsdSysCfgCnfFailureFlag;
    VOS_UINT8 ulHsdSysCfgCnfFailureFlag;
    VOS_UINT8 ulMmcSysCfgCnfFailureFlag;
}TEST_NAS_MSCC_POWER_SAVE_SYS_CFG_CNF_FAILURE_STRU;
#endif


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



VOS_UINT32 NAS_MSCC_IsUserPlatformSupportCdmaEvdo(VOS_VOID);

NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16 NAS_MSCC_MapSysCfgRatType(
    VOS_UINT16                          usRatPrioFlg
);

NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16 NAS_MSCC_GetSysCfgSupportedRatType(
    NAS_MSCC_PIF_RAT_PRIO_STRU          *pstRatPrio
);

NAS_MSCC_POWER_SAVE_OPERATION_STRU *NAS_MSCC_GetPowerSaveOperTypeFromTbl(
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16    ulLastRatType,
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16    ulCurrRatType
);

VOS_VOID NAS_MSCC_MapPowerSaveOperTypeToPowerSaveModuleOrder(
    NAS_MSCC_POWER_SAVE_OPERATION_STRU       *pstPowerSaveOperType
);

VOS_VOID NAS_MSCC_SetPowerSaveModuleOrder_SysCfg(VOS_VOID);

VOS_VOID NAS_MSCC_SetSysCfgModuleOrder_SysCfg(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_SysCfg(VOS_VOID);


NAS_MSCC_PIF_RAT_PRIO_STRU * NAS_MSCC_GetRatPrioListFromEntryMsg_SysCfg(VOS_VOID);
VOS_UINT32 NAS_MSCC_GetNextPowerSaveModuleId_SysCfg(
    VOS_UINT32                          *pulNextModuleId
);

VOS_UINT32 NAS_MSCC_GetNextSysCfgModuleId_SysCfg(
    VOS_UINT32                          *pulNextModuleId
);

VOS_VOID NAS_MSCC_SndSysCfgReq_SysCfg(
    VOS_UINT32                          ulReceivePid
);

VOS_VOID NAS_MSCC_SndPowerSaveReq_SysCfg(
    VOS_UINT32                          ulReceivePid
);

VOS_UINT32 NAS_MSCC_RcvMmaSysCfgReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvXsdPowerSaveCnf_SysCfg_WaitXsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitXsdPowerSaveCnfExpired_SysCfg_WaitXsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_SysCfg_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysCfg_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_SysCfg_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysCfg_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvXsdSysCfgCnf_SysCfg_WaitXsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitXsdSysCfgCnfExpired_SysCfg_WaitXsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdSysCfgCnf_SysCfg_WaitHsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitHsdSysCfgCnfExpired_SysCfg_WaitHsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_MSCC_RcvMmcSysCfgCnf_SysCfg_WaitMmcSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcSysCfgCnfExpired_SysCfg_WaitMmcSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#ifdef DMT
    extern TEST_NAS_MSCC_POWER_SAVE_SYS_CFG_CNF_FAILURE_STRU g_stTestMsccPowerSaveSysCfgCnfFailure;
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
#endif
