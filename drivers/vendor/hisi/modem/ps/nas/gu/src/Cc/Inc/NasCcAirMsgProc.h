
#ifndef  NAS_CC_AIRMSG_RPOC_H
#define  NAS_CC_AIRMSG_RPOC_H

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

VOS_VOID  NAS_CC_ProcAirMsg(
    const VOS_UINT8                     *pucData,
    VOS_UINT32                          ulDataLen
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

#endif /* NAS_CC_AIRMSG_RPOC_H */

