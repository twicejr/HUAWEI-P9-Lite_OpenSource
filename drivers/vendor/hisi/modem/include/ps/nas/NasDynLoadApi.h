

#ifndef __NAS_DYNLOAD_API_H__
#define __NAS_DYNLOAD_API_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "VosPidDef.h"

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

enum NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM
{
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W          = 0,
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT
};
typedef VOS_UINT32 NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32;


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

typedef VOS_VOID (*NAS_DYNLOAD_INIT_CB)(VOS_VOID);


typedef VOS_VOID (*NAS_DYNLOAD_UNLOAD_CB)(VOS_VOID);


typedef VOS_UINT32 (*WAS_QueryCSNR)(
    VOS_INT16                          *psCpichRscp,
    VOS_INT16                          *psCpichEcNo
);

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_RegQueryCsnrCallBack(
    WAS_QueryCSNR                      pfQueryCsnr
);

WAS_QueryCSNR TAF_GetWasQueryCsnrAddr(VOS_VOID);


#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
VOS_UINT32 NAS_DYNLOAD_RegLoadCallBack(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID,
    NAS_DYNLOAD_INIT_CB                 pfInit,
    NAS_DYNLOAD_UNLOAD_CB               pfUnload
);

VOS_UINT32 NAS_DYNLOAD_DeRegLoadCallBack(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID
);

VOS_UINT32 NAS_DYNLOAD_UnloadAS(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enVosRatType
);

VOS_UINT32 NAS_DYNLOAD_LoadAS(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enVosRatType
);

VOS_RATMODE_ENUM_UINT32 NAS_DYNLOAD_GetCurRatInCached(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
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

#endif /* end of NasDynLoadApi.h */



