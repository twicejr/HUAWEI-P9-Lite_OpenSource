

#ifndef __TAFAPSSNDEHSM_H__
#define __TAFAPSSNDEHSM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "ehsm_aps_pif.h"
#include  "Taf_Aps.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_APS_SndEhsmPdnActReq(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType
);


VOS_VOID TAF_APS_SndEhsmPdnDeactReq(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SndEhsmPsRatTypeNtf(
    APS_EHSM_PS_RATTYPE_ENUM_UINT32     enPsRatType
);

VOS_VOID TAF_APS_SndEhsmReconnReq(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SndEhsmPdnCtxInfoNotify(
    VOS_UINT8                           ucPdnId,
    EHSM_APS_PDN_OPTION_ENUM_UINT32     enOption
);

VOS_VOID TAF_APS_SndEhsmLocDetachNotify(VOS_VOID);

VOS_VOID TAF_APS_SndEhsmLocDeactNtf(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SndEhsmDiscNtf(VOS_VOID);

VOS_VOID TAF_APS_SndEhsmPdnAttachReq(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType
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

#endif /* end of TafApsSndEhsm.h */

