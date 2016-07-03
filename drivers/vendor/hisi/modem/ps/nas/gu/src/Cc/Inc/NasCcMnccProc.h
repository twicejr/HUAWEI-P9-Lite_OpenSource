
#ifndef  NAS_CC_MNCC_PROC_H
#define  NAS_CC_MNCC_PROC_H

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


/*****************************************************************************
  2 函数声明
*****************************************************************************/

VOS_VOID  NAS_CC_ProcMnccPrimitive(
    VOS_VOID                            *pMsg
);


VOS_VOID  NAS_CC_GetMsgUus1Info(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
);


VOS_UINT32  NAS_CC_IsNeedProcDisProInd(
    NAS_CC_ENTITY_ID_T                  entityId
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

#endif /* NAS_CC_MNCC_PROC_H */

