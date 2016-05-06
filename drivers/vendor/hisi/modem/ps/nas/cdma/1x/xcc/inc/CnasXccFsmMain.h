/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccFsmMain.h
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年06月27日
  功能描述   : CnasXccFsmMain.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00213812
    修改内容   : 创建文件
******************************************************************************/
#ifndef _CNAS_XCC_FSM_MAIN_H_
#define _CNAS_XCC_FSM_MAIN_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "xcc_taf_pif.h"
#include "CnasXccCtx.h"
#include "cas_1x_control_main_nas_pif.h"


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

VOS_UINT32 CNAS_XCC_RcvOrigCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvPagingInd_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_NotifyTafCallDisc_L1Main(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_BOOL                            isNeedToResumeAps
);

VOS_VOID CNAS_XCC_ProcOrderMsg_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_RcvAWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
);

extern VOS_UINT32 CNAS_XCC_RcvEAWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
);

extern VOS_UINT32 CNAS_XCC_RcvFWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
);

extern VOS_UINT32 CNAS_XCC_RcvEFWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
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


