
#ifndef __MNMSGUSIMPROC_H__
#define __MNMSGUSIMPROC_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgSmCommProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/*****************************************************************************
  3 接口函数声明
*****************************************************************************/


VOS_UINT32  MN_MSG_SndUsimGetFileReq(
    VOS_UINT16                          usEfId,
    VOS_UINT8                           ucRecNum
);


VOS_UINT32 MN_MSG_SndUsimSetFileReq(
    VOS_UINT16                          usEfId,
    VOS_UINT8                           *pucEf,
    VOS_UINT8                           ucEfLen,
    VOS_UINT8                           ucRecNum
);


VOS_UINT32  MN_MSG_SndUsimGetMaxRecReq(
    VOS_UINT16                          usEfId
);



VOS_VOID MN_MSG_InitParm(VOS_VOID);



VOS_UINT8  MN_MSG_GetSmCurrRecFromUsim(VOS_VOID);



VOS_VOID  MN_MSG_SetSmCurrRecFromUsim(
    VOS_UINT8                           ucCurrRec
);


VOS_UINT32 MN_MSG_CheckFdn(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbCheckFdn
);


VOS_UINT32 MN_MSG_SendMsgAvailable(
    VOS_BOOL                                bBufferEntity,
    VOS_UINT32                              ulIndex,
    MN_MSG_MO_ENTITY_STRU                  *pstMoEntity
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

#endif /* __MNMSGUSIMPROC_H__ */

