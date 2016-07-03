
#ifndef  NAS_CC_MMCC_PROC_H
#define  NAS_CC_MMCC_PROC_H

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
#include  "NasOmInterface.h"
#include "NasOmTrans.h"

/*****************************************************************************
  3 类型定义
*****************************************************************************/
typedef struct
{
    NAS_CC_MSG_TYPE_ENUM_U8       enCcMsgId;
    NAS_OTA_MSG_ID_ENUM_UINT16    enOtaMsgId;
} NAS_CC_OTA_MSG_ID_STRU;

/*****************************************************************************
  4 函数声明
*****************************************************************************/

VOS_VOID  NAS_CC_ProcMmccPrimitive(
    const VOS_VOID                      *pMsg
);


VOS_VOID NAS_CC_LocalAbortDtmf(
    NAS_CC_ENTITY_ID_T                  entityId
);


VOS_VOID  NAS_CC_ProcMmccRrcConnRelInd(
    const VOS_VOID                      *pMsg
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

#endif /* NAS_CC_MMCC_PROC_H */

