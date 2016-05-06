/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasDynLoadMntn.h
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2015年8月27日
  最近修改   :
  功能描述   : NasDynLoadMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月27日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_DYNLOAD_MNTN_H__
#define __NAS_DYNLOAD_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "NasDynLoad.h"
#include "VosPidDef.h"
#include "NasMsccMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_DYNLOAD_SoftReboot(pstNasRebootInfo) NAS_Dynload_SoftReBoot_WithLineNoAndFileID( (__LINE__), (THIS_FILE_ID), (pstNasRebootInfo))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_DYNLOAD_MNTN_MSG_ID_ENUM
 结构说明  : NAS发送给OM的可维可测消息
  1.日    期   : 2015年8月27日
    作    者   : w00242748
    修改内容   : NAS发送给OM的可维可测消息ID枚举
*****************************************************************************/
enum NAS_DYNLOAD_MNTN_MSG_ID_ENUM
{
    NAS_DYNLOAD_MNTN_MSG_REGISTER                       = ID_NAS_MSCC_MNTN_DYNLOAD_MSG_BASE, /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU */
    NAS_DYNLOAD_MNTN_MSG_DEREGISTER                             , /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU */
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT                            , /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU */
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD                          , /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU */
    NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD                         ,  /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU */
    NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD                        ,  /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU */

    NAS_DYNLOAD_MNTN_MSG_BUTT
};
typedef VOS_UINT32 NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32;




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
 结构名    : NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU
 结构说明  : 勾取动态加载模块信息

 修改记录  :
 1.日    期   : 2013年06月05日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulInit;
    VOS_UINT32                          ulUnload;
}NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU;

/*****************************************************************************
 结构名    : NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU
 结构说明  : 勾取动态加载模块信息

 修改记录  :
 1.日    期   : 2013年06月05日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
}NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU;

/*****************************************************************************
 结构名    : NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU
 结构说明  : 勾取动态加载模块信息

 修改记录  :
 1.日    期   : 2013年06月05日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    NAS_DYNLOAD_CB_RAT_INFO_STRU        astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulInit;
}NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU;

/*****************************************************************************
 结构名    : NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU
 结构说明  : 勾取动态加载模块信息

 修改记录  :
 1.日    期   : 2015年08月31日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    NAS_DYNLOAD_CB_RAT_INFO_STRU        astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulUnload;
}NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU;

/*****************************************************************************
 结构名    : NAS_DYNLOAD_MNTN_MSG_START_MRV_LOAD_STRU
 结构说明  : 勾取开始调用底软API消息

 修改记录  :
 1.日    期   : 2015年08月31日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
}NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU;

/*****************************************************************************
 结构名    : NAS_DYNLOAD_MNTN_MSG_START_MRV_LOAD_STRU
 结构说明  : 勾取结束调用底软API消息

 修改记录  :
 1.日    期   : 2015年08月31日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_INT32                           lLoadResult;
    NAS_DYNLOAD_CB_RAT_INFO_STRU        astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
}NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU;

/*****************************************************************************
 结构名    : NAS_DYNLOAD_REBOOT_INFO_STRU
 结构说明  : 动态加载复位信息

 修改记录  :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
}NAS_DYNLOAD_REBOOT_INFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32                     enMsgId;                         /* _H2ASN_MsgChoice_Export NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} NAS_DYNLOAD_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    NAS_DYNLOAD_MNTN_MSG_DATA           stMsgData;
} NasDynloadMntn_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogRegisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit,
    VOS_UINT32                          ulUnload
);

VOS_VOID  NAS_DYNLOAD_LogDeregisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid
);

VOS_VOID  NAS_DYNLOAD_LogExcuteInitInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit
);

VOS_VOID  NAS_DYNLOAD_LogExcuteUnloadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulUnload
);

VOS_VOID  NAS_DYNLOAD_LogStartDrvLoadInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType
);

VOS_VOID  NAS_DYNLOAD_LogFinishDrvLoadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_INT32                           lLoadResult
);

VOS_VOID NAS_Dynload_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_DYNLOAD_REBOOT_INFO_STRU       *pstRebootInfo
);


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

#endif /* end of TafSpmMntn.h */


