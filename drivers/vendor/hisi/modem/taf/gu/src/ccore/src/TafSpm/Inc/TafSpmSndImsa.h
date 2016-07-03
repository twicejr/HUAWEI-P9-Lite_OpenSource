
#ifndef _TAF_SPM_SND_IMSA_H_
#define _TAF_SPM_SND_IMSA_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafSpmCtx.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_IMS == FEATURE_ON)
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
VOS_VOID TAF_SPM_SendImsaCallOrigReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaSupsCmdReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaGetCallInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg,
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8 enReqType
);

VOS_VOID TAF_SPM_SendImsaGetClprReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaStartDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaStopDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaGetCdurReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaRegisterSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaEraseSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaActivateSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaDeactivateSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaInterrogateSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaProcessUssSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaReleaseSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaCallInviteNewPtptReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaCallModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaCallAnswerRemoteModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaEconfAddUsersReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaEconfDialReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaGetEconfInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_FillImsaEconfCallList(
    TAF_CALL_ECONF_CALL_LIST_STRU      *pstCallList
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

#endif


