/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmPowerOff.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : CnasXsdFsmPowerOff.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月3日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_FSM_POWER_OFF_H__
#define __CNAS_XSD_FSM_POWER_OFF_H__

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

VOS_UINT32  CNAS_XSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf(
     VOS_UINT32                          ulEventType,
     struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvMsccPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvXccPowerOffCnf_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitCasSysDeterminInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvInterXsdSystemAcquiredReq_PowerOff_WaitXsdSystemAcquireRsltCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  CNAS_XSD_RcvXsdSystemAcquiredRsltCnf_PowerOff_WaitXsdSystemAcquireRsltCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvXccDeregisterInd_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasSuspendCnf_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiWaitCasSuspendCnfExpired_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_PowerOff_WaitCasSuspendCnf(
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

#endif /* end of CnasXsdFsmPowerOff.h */
