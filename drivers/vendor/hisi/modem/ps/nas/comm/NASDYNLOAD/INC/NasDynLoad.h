/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasDynLoadApi.h
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2015年8月10日
  最近修改   :
  功能描述   : NasDynLoadApi.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月10日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_DYNLOAD_H__
#define __NAS_DYNLOAD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "VosPidDef.h"
#include "NasDynLoadApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_DYNLOAD_CB_MODULE_NUM                    (3)
#define NAS_DYNLOAD_MAX_ATTEMPT_COUNT                (2)

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
 结构名    : NAS_DYNLOAD_CTRL_STRU
 结构说明  : 动态加载控制信息
 1.日    期   : 2015年8月27日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableDynloadTW;      /* 是否激活TW动态加载 */
    VOS_UINT8                           ucTWMaxAttemptCount;      /* TW动态加载次数 */
    VOS_UINT8                           aucReserved[2];
}NAS_DYNLOAD_CTRL_STRU;

/*****************************************************************************
结构名    : NAS_DYNLOAD_CB_MODULE_INFO_STRU
结构说明  : 动态加载中提供回调函数的模块信息
1.日    期  : 2015年8月10日
  作    者  : w00242748
  修改内容  : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;
    NAS_DYNLOAD_INIT_CB                 pfInitCb;
    NAS_DYNLOAD_UNLOAD_CB               pfUnloadCb;
}NAS_DYNLOAD_CB_MODULE_INFO_STRU;

/*****************************************************************************
结构名    : NAS_DYNLOAD_CB_RAT_INFO_STRU
结构说明  : 动态加载中提供回调函数的接入技术信息
1.日    期  : 2015年8月10日
  作    者  : w00242748
  修改内容  : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNum;
    NAS_DYNLOAD_CB_MODULE_INFO_STRU     astModule[NAS_DYNLOAD_CB_MODULE_NUM];
}NAS_DYNLOAD_CB_RAT_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
VOS_VOID NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim(VOS_VOID);

VOS_VOID NAS_DYNLOAD_ReadDynloadCtrlNvim(VOS_VOID);

VOS_UINT8 NAS_DYNLOAD_GetEnableDynloadTWFlg(VOS_VOID);

VOS_VOID NAS_DYNLOAD_SetEnableDynloadTWFlg(
    VOS_UINT8                           ucEnableFlg
);

VOS_UINT8 NAS_DYNLOAD_GetTWMaxAttemptCount(VOS_VOID);

VOS_VOID NAS_DYNLOAD_SetTWMaxAttemptCount(
    VOS_UINT8                           ucTWMaxAttemptCount
);

NAS_DYNLOAD_CB_RAT_INFO_STRU* NAS_DYNLOAD_GetSpecCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode
);

VOS_VOID NAS_DYNLOAD_SetCurRatInCached(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatMode
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

#endif /* end of CnasXsdFsmSysAcqTbl.h */


