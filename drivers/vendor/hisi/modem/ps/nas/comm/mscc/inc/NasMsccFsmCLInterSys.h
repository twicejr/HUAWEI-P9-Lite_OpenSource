/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmCLInterSys.h
Author          :   W00176964
Version         :
Date            :   2015-11-05
Description     :   CL异系统流程的各状态的消息处理头文件
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/

#ifndef _NAS_MSCC_FSM_CL_INTERSYS_H_
#define _NAS_MSCC_FSM_CL_INTERSYS_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasMsccCtx.h"
#include  "NasComm.h"


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
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
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_CLInterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_CLInterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_CLInterSys_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdInterSysEndInd_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcInterSysEndInd_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32 NAS_MSCC_JudgeCLInterSysRslt(VOS_VOID);

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

#endif /* end of NasMsccFsmCLInterSys.h */


