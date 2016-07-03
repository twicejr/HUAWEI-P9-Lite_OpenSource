

#ifndef _TAF_MMA_FSM_MAIN_H
#define _TAF_MMA_FSM_MAIN_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafLog.h"


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
VOS_UINT32 TAF_MMA_RcvAppPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTafPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_MMA_RcvMmaPlmnListReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 TAF_MMA_RcvTafCsgListSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_MMA_RcvMsccCsgListSearchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccCsgListAbortCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMsccCsgListRej_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_MMA_RcvTafCsgListAbortReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvUsimRefreshIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvDetachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaPhoneModeRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaSysCfgRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaSimlockStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ProcPlmnAutoReselReq_Main(
    VOS_UINT32                          ulOpID
);

extern VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_Main (
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_MMA_RcvTafImsSwitchSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaImsSwitchRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif


VOS_UINT32 TAF_MMA_RcvAttachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);






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

#endif /* end of Taf_MMA_FSM_MAIN.h */

