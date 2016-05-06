/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmModeChange.h
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2012年8月8日
  最近修改   :
  功能描述   : NasUtranCtrlFsmModeChange.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月8日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_UTRANCTRL_FSM_MODE_CHANGE_H_
#define _NAS_UTRANCTRL_FSM_MODE_CHANGE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"


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

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
);

VOS_VOID NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
);

NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  NAS_UTRANCTRL_GetMasterMode_ModeChange(VOS_VOID);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
VOS_UINT32 NAS_UTRANCTRL_RcvGasMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_UTRANCTRL_RcvLmmMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitMasterModeRelCnfExpired_ModeChange_WaitMasterModeRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif


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

#endif /* end of NasUtranCtrlFsmModeChange.h */


