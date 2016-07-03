
#ifndef __NASCCUSERCONN_H__
#define __NASCCUSERCONN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasCcCommon.h"
#include  "NasCcIe.h"
#include  "MmCcInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define  NAS_CC_DEFAULT_RAB             0

/*****************************************************************************
  3 接口函数声明
*****************************************************************************/

VOS_VOID NAS_CC_InitUserConn(VOS_VOID);



VOS_VOID NAS_CC_AttachUserConn(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc
);




VOS_VOID NAS_CC_DetachUserConn(
    NAS_CC_ENTITY_ID_T                  entityId
);



VOS_UINT32 NAS_CC_SetTchStatus(
    const MMCC_SYNC_IND_STRU                  *pstSyncInd,
    NAS_CC_ENTITY_ID_T                  entityId
);



VOS_BOOL NAS_CC_IsTchAvailable(
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc
);



VOS_VOID NAS_CC_GenarateLocalAlertInd(VOS_VOID);



VOS_VOID NAS_CC_StopLocalAlertInd(VOS_VOID);


VOS_VOID NAS_CC_ProcLocalAlert(NAS_CC_ALERT_IND_ENUM_U32   enAlertInd);


VOS_VOID NAS_CC_SetTchAvailValue(
    VOS_BOOL                            bTchAvail
);


VOS_VOID NAS_CC_ClearSyncIndReady( VOS_VOID );


VOS_VOID NAS_CC_SetSyncIndReady(
    VOS_UINT32                 ulReadyFlg
);


VOS_UINT32 NAS_CC_GetSyncIndReady( VOS_VOID );


NAS_CC_INFO_TRANSFER_CAP_ENUM_U8 NAS_CC_GetCurrItc( VOS_VOID );


VOS_BOOL NAS_CC_IsGsmNet(VOS_VOID);

VOS_UINT32  NAS_CC_IsAttachUserConn( VOS_VOID );
VOS_VOID  NAS_CC_SetUserConnEntity(
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

#endif /* __NASCCUSERCONN_H__ */

