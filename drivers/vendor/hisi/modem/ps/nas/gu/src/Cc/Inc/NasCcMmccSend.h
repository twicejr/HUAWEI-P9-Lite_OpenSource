
#ifndef  NAS_CC_MMCC_SEND_H
#define  NAS_CC_MMCC_SEND_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MmCcInterface.h"

/*****************************************************************************
  2 函数声明
*****************************************************************************/

VOS_VOID  NAS_CC_SendMmccAbortReq(
    VOS_UINT8                           ucTi
);



VOS_VOID  NAS_CC_SendMmccRelReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulRelType
);



VOS_VOID  NAS_CC_SendMmccEstReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulCallType,
    VOS_UINT32                          ulCallMode,
    VOS_UINT32                          ulPriority,
    VOS_UINT8                           ucRedialFlg
);



VOS_VOID  NAS_CC_SendMmccDataReq(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
);



VOS_VOID  NAS_CC_SendMmccPromptRej(
    VOS_UINT32                          ulCause
);



VOS_VOID  NAS_CC_SendMmccReestReq(
    VOS_UINT8                           ucTi
);


VOS_VOID  NAS_CC_SendMmccStartCc(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
);
VOS_VOID  NAS_CC_SendMmccCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
);

//VOS_VOID NAS_CC_SendMmccCallInfoCnf(VOS_VOID);
VOS_VOID NAS_CC_SendMmccCallInfoCnf(
    MMCC_CALL_INFO_STRU                *pstCallInfo
);



#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  NAS_CC_SendMmccSrvccCallInfoNtf(
    VOS_UINT8                           ucSyncTiNum,
    VOS_UINT8                          *pucSyncTi
);
#endif

#if(FEATURE_ON == FEATURE_DSDS)
VOS_VOID  NAS_CC_SendMmccBeginSessionNotify(
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType
);

VOS_VOID  NAS_CC_SendMmccEndSessionNotify(
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType
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
#endif
#endif

#endif /* NAS_CC_MMCC_SEND_H */

