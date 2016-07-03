
#ifndef  NAS_CC_AIRMSG_SEND_H
#define  NAS_CC_AIRMSG_SEND_H

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
#include "NasCcCommon.h"
#include "NasCcIe.h"


/*****************************************************************************
  2 函数声明
*****************************************************************************/

VOS_VOID  NAS_CC_SendConnectAck(
    VOS_UINT8                           ucTi
);



VOS_VOID  NAS_CC_SendDisconnect(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
);



VOS_VOID  NAS_CC_SendRelease(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal,
    VOS_BOOL                            bCause2Present,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause2Val
);



VOS_VOID  NAS_CC_SendReleaseComplete(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
);



VOS_VOID  NAS_CC_SendStartDtmf(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucKey
);



VOS_VOID  NAS_CC_SendStopDtmf(
    VOS_UINT8                           ucTi
);



VOS_VOID  NAS_CC_SendStatus(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
);


VOS_VOID  NAS_CC_FillCauseIe(
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCauseVal,
    NAS_CC_IE_CAUSE_STRU                *pstCauseIe
);


VOS_VOID NAS_CC_SendMmccStartCcReq(
      VOS_UINT8                           ucTi
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

#endif /* NAS_CC_AIRMSG_SEND_H */

