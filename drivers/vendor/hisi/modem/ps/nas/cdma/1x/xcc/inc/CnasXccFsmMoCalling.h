/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccFsmMoCalling.h
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月4日
  功能描述   : CnasXccFsmMoCalling.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月4日
    作    者   : w00242748
    修改内容   : 创建文件
******************************************************************************/
#ifndef _CNAS_XCC_FSM_MO_CALLING_H_
#define _CNAS_XCC_FSM_MO_CALLING_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"

#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccCtx.h"
#include "xcc_taf_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
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
VOS_UINT32 CNAS_XCC_RcvXcallOrigReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvOrigDataCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvOrigSmsCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvOrigAgpsCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvApsSuspendRsp_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsEstCnf_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallInitInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallHandupReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID   CNAS_XCC_SndOrigCallCnf_MoCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    VOS_BOOL                            isNeedToResumeAps,
    VOS_INT16                           sRssi
);





#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif


