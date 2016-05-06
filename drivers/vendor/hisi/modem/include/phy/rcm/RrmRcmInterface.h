/******************************************************************************

                  版权所有 (C), 2013-2023, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RrmRcmInterface.h
  版 本 号   : 初稿
  作    者   : h00163499
  生成日期   : 2014年6月25日
  最近修改   :
  功能描述   : RrmRcmInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年6月25日
    作    者   : h00163499
    修改内容   : 创建文件

******************************************************************************/

#ifndef __RRMRCMINTERFACE_H__
#define __RRMRCMINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "vos_Id.h"



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

/*******************************************************************************
 枚举名    : RRM_RCM_MSG_TYPE_ENUM_UINT32
 结构说明  : 消息枚举
 1.日    期   : 2014年6月25日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
enum RRM_RCM_MSG_TYPE_ENUM
{
    ID_RRM_RCM_PROTECT_RF_IND           = 0x0001,       /* _H2ASN_MsgChoice RRM_RCM_PROTECT_RF_IND_STRU */

    ID_RRM_RCM_DEPROTECT_RF_IND         = 0x0002,       /* _H2ASN_MsgChoice RRM_RCM_DEPROTECT_RF_IND_STRU */

    ID_RRM_RCM_ACTIVE_ID_NTF            = 0x0003,       /* _H2ASN_MsgChoice RRM_RCM_ACTIVE_ID_NTF_STRU */

    ID_RRM_RCM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 RRM_RCM_MSG_TYPE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : RRM_RCM_ACTIVE_ID_ENUM
 结构说明  : RRM RCM Active Id标识定义
*******************************************************************************/
enum RRM_RCM_ACTIVE_ID_ENUM
{
    RRM_RCM_ACTIVE_ID_0               = 0,   /* Active Id 0 标识 */
    RRM_RCM_ACTIVE_ID_1               = 1,   /* Active Id 1 标识 */
    RRM_RCM_ACTIVE_ID_2               = 2,   /* Active Id 2 标识 */
    RRM_RCM_ACTIVE_ID_1X              = 3,   /* Active Id 1x 标识 */
    RRM_RCM_ACTIVE_ID_BUTT
};
typedef VOS_UINT16 RRM_RCM_ACTIVE_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRM_RCM_MODE_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层模式标示 排列次序和校准次序一致
*****************************************************************************/
enum RRM_RCM_MODE_ID_ENUM
{
    RRM_RCM_LTE                         = 0,                                    /* LTE */
    RRM_RCM_WCDMA                       = 1,                                    /* WCDMA */
    RRM_RCM_1X                          = 2,                                    /* 1X */
    RRM_RCM_HRPD                        = 3,                                    /* HRPD */
    RRM_RCM_TD                          = 4,                                    /* TD */
    RRM_RCM_G0                          = 5,                                    /* G0 */
    RRM_RCM_G1                          = 6,                                    /* G1 */
    RRM_RCM_G2                          = 7,                                    /* G2 */
    RRM_RCM_MODE_ID_BUTT
};
typedef VOS_UINT16  RRM_RCM_MODE_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RRM_RCM_RESOURCE_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : resoure ID
*****************************************************************************/
enum RRM_RCM_RESOURCE_ID_ENUM
{
    RRM_RCM_RESOURCE_0                            = 0,                          /* RESOURCE 0 */
    RRM_RCM_RESOURCE_1                            = 1,                          /* RESOURCE 1 */
    RRM_RCM_RESOURCE_ID_BUTT
};
typedef VOS_UINT16  RRM_RCM_RESOURCE_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    : RRM_RCM_DSDS_FLG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRM_RCM_DSDS_FLG_ENUM
*****************************************************************************/
enum RRM_RCM_DSDS_FLG_ENUM
{
    RRM_RCM_DSDS_CLOSE                            = 0,                          /* DSDS CLOSE */
    RRM_RCM_DSDS_OPEN                             = 1,                          /* DSDS OPEN  */
    RRM_RCM_DSDS_BUTT
};
typedef VOS_UINT16  RRM_RCM_DSDS_FLG_ENUM_UINT16;

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

/*******************************************************************************
 结构名    : RRM_RCM_PROTECT_RF_IND_STRU
 结构说明  : RRM发给RCM指示保护该ACTIVE上的RF,不偷帧
 1.日    期   : 2014年6月25日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRM_RCM_MSG_TYPE_ENUM_UINT32                enMsgId;                        /* 消息类型 */  /* _H2ASN_Skip */
    RRM_RCM_ACTIVE_ID_ENUM_UINT16               enActiveId;                     /* Active Id */
    RRM_RCM_RESOURCE_ID_ENUM_UINT16             enResourceId;                   /* Resource Id */

} RRM_RCM_PROTECT_RF_IND_STRU;


/*******************************************************************************
 结构名    : RRM_RCM_DEPROTECT_RF_IND_STRU
 结构说明  : RRM发给RCM指示去保护该ACTIVE上的RF,允许偷帧
 1.日    期   : 2014年6月25日
   作    者   : h00163499
   修改内容   : Added for DSDS
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRM_RCM_MSG_TYPE_ENUM_UINT32                enMsgId;                        /* 消息类型 */  /* _H2ASN_Skip */
    RRM_RCM_ACTIVE_ID_ENUM_UINT16               enActiveId;                     /* Active Id */
    RRM_RCM_RESOURCE_ID_ENUM_UINT16             enResourceId;                   /* Resource Id */
} RRM_RCM_DEPROTECT_RF_IND_STRU;

/*******************************************************************************
 结构名    : RRM_RCM_MODE_ID_PARA_STRU
 结构说明  : RRM通知RCM上每个ACTIVE ID上支持的接入模式列表
 1.日    期   : 2015年1月25日
   作    者   : l00128652
   修改内容   : Added for HYBRID MODE
*******************************************************************************/
typedef struct
{
    RRM_RCM_MODE_ID_ENUM_UINT16                 enModeId;
    RRM_RCM_ACTIVE_ID_ENUM_UINT16               enActiveId;                     /* Active Id */
    RRM_RCM_RESOURCE_ID_ENUM_UINT16             enResourceId;                   /* Resource Id */
    RRM_RCM_DSDS_FLG_ENUM_UINT16                enDsdsFlg;                      /* DSDS flag */
} RRM_RCM_MODE_ID_PARA_STRU;

/*******************************************************************************
 结构名    : RRM_RCM_ACTIVE_ID_NTF_STRU
 结构说明  : RRM通知RCM当前支持的MODE ID以及每个MODE ID上对应的ActiveId,RFId和DSDS 标志
 1.日    期   : 2015年1月25日
   作    者   : l00128652
   修改内容   : Added for HYBRID MODE
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRM_RCM_MSG_TYPE_ENUM_UINT32                enMsgId;                        /* 消息类型 */  /* _H2ASN_Skip */
    VOS_UINT16                                  usModeIdNum;
    VOS_UINT16                                  ausReserved[1];
    RRM_RCM_MODE_ID_PARA_STRU                   astModeIdPara[RRM_RCM_MODE_ID_BUTT];
} RRM_RCM_ACTIVE_ID_NTF_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/

/*****************************************************************************
 结构名    : RRM_RCM_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : RRM_RCM_MSG_DATA数据结构，用于生成ASN文件
*****************************************************************************/
typedef struct
{
    RRM_RCM_MSG_TYPE_ENUM_UINT32        enMsgId;    /*_H2ASN_MsgChoice_Export RRM_RCM_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRM_RCM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}RRM_RCM_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : RrmRcmInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : RrmRcmInterface_MSG数据结构,用于生成ASN文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RRM_RCM_MSG_DATA                             stMsgData;
}RrmRcmInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/





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

#endif /* end of RrmRcmInterface.h */

