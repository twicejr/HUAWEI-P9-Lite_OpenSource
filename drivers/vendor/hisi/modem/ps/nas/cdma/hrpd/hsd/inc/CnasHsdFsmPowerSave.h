

#ifndef __CNAS_HSD_FSM_POWER_SAVE_H__
#define __CNAS_HSD_FSM_POWER_SAVE_H__

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


extern VOS_UINT32  CNAS_HSD_RcvMsccPowerSaveReq_PowerSave_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvCasSuspendCnf_PowerSave_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiWaitCasSuspendCnfExpired_PowerSave_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvHsmPowerSaveCnf_PowerSave_WaitHsmPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvTiWaitHsmPowerSaveCnfExpired_PowerSave_WaitHsmPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvRrmStatusInd_PowerSave(
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

#endif /* end of CnasHsdFsmPowerOff.h */
