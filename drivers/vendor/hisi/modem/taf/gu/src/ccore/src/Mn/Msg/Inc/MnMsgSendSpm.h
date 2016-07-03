
#ifndef __MNMSGSENDSPM_H__
#define __MNMSGSENDSPM_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 接口函数声明
*****************************************************************************/
VOS_VOID TAF_MSG_SendSpmSmmaInd(VOS_VOID);

VOS_VOID TAF_MSG_SpmMsgReportInd(
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU    *pstSubmitRptEvt,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enSignallingType
);

#endif

VOS_VOID TAF_MSG_SendSpmMsgCheckResultInd(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MSG_ERROR_ENUM_UINT32           enRslt
);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __MNMSGSENDSPM_H__ */

