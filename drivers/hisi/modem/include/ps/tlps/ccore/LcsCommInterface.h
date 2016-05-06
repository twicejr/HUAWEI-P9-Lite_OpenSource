/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : LcsCommInterface.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2015年9月14日
  最近修改   :
  功能描述   : LCS特性公共数据结构定义的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月14日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

#ifndef __LCCOMMINTERFACE_H__
#define __LCCOMMINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define LCS_CLIENT_EXID_MAX_LEN         (20)
#define LCS_CLIENT_NAME_MAX_LEN         (160)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*******************************************************************************
 枚举名    : LCS_PLANE_ENUM
 结构说明  : LCS特性MO-LR流程PLANE枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_PLANE_ENUM
{
    LCS_PLANE_CONTROL                   = 0,
    LCS_PLANE_SECURE_USER,

    LCS_PLANE_BUTT
};
typedef VOS_UINT8 LCS_PLANE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_MOLR_METHOD_ENUM
 结构说明  : LCS特性MO-LR流程定位方法枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_MOLR_METHOD_ENUM
{
    LCS_MOLR_METHOD_GPS                 = 0,                                    /* Unassisted GPS */
    LCS_MOLR_METHOD_AGPS,                                                       /* Assisted GPS */
    LCS_MOLR_METHOD_AGNSS,                                                      /* Assisted GANSS */
    LCS_MOLR_METHOD_AGPS_AGNSS,                                                 /* Assisted GPS and GANSS */
    LCS_MOLR_METHOD_BASIC_SELF,                                                 /* Basic self location */
    LCS_MOLR_METHOD_TRANSFER_TP_ADDR,                                           /* Transfer to third party */
    LCS_MOLR_METHOD_RETRIEVAL_TP_ADDR,                                          /* Retrieval from third party */

    LCS_MOLR_METHOD_BUTT
};
typedef VOS_UINT8 LCS_MOLR_METHOD_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_HOR_ACC_SET_ENUM
 结构说明  : LCS特性MO-LR流程水平精度设置标志枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_HOR_ACC_SET_ENUM
{
    LCS_HOR_ACC_NOT_SET                 = 0,
    LCS_HOR_ACC_SET_PARAM,

    LCS_HOR_ACC_SET_BUTT
};
typedef VOS_UINT8 LCS_HOR_ACC_SET_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_VER_REQ_ENUM
 结构说明  : LCS特性MO-LR流程垂直坐标请求枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_VER_REQ_ENUM
{
    LCS_VER_NOT_REQUESTED               = 0,
    LCS_VER_REQUESTED,

    LCS_VER_REQ_BUTT
};
typedef VOS_UINT8 LCS_VER_REQ_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_VER_ACC_SET_ENUM
 结构说明  : LCS特性MO-LR流程垂直精度设置标志枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_VER_ACC_SET_ENUM
{
    LCS_VER_ACC_NOT_SET                 = 0,
    LCS_VER_ACC_SET_PARAM,

    LCS_VER_ACC_SET_BUTT
};
typedef VOS_UINT8 LCS_VER_ACC_SET_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_VEL_REQ_ENUM
 结构说明  : LCS特性MO-LR流程速度请求枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_VEL_REQ_ENUM
{
    LCS_VEL_NOT_REQUESTED               = 0,                                    /* Velocity not requested */
    LCS_VEL_REQ_HOR,                                                            /* Horizontal velocity requested */
    LCS_VEL_REQ_HOR_VER,                                                        /* Horizontal velocity and vertical velocity requested */
    LCS_VEL_REQ_HOR_ACC,                                                        /* Horizontal velocity with uncertainty requested */
    LCS_VEL_REQ_HOR_ACC_VER_ACC,                                                /* Horizontal velocity with uncertainty and vertical velocity with uncertainty requested */

    LCS_VEL_REQ_BUTT
};
typedef VOS_UINT8 LCS_VEL_REQ_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_REP_MODE_ENUM
 结构说明  : LCS特性MO-LR流程上报模式枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_REP_MODE_ENUM
{
    LCS_REP_MODE_SINGLE_RPT             = 0,
    LCS_REP_MODE_PERIODIC_RPT,

    LCS_REP_MODE_BUTT
};
typedef VOS_UINT8 LCS_REP_MODE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_MTLRA_OP_ENUM
 结构说明  : LCS特性MT-LR用户响应网络定位请求操作枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_MTLRA_OP_ENUM
{
    LCS_MTLRA_ALLOW                     = 0,
    LCS_MTLRA_NOT_ALLOW,

    LCS_MTLRA_OP_BUTT
};
typedef VOS_UINT8 LCS_MTLRA_OP_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_NOTIFICATION_TYPE_ENUM
 结构说明  : LCS特性MT-LR网络定位请求中的用户隐私信息操作枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_NOTIFICATION_TYPE_ENUM
{
    LCS_NOTIFICATION_ALLOW_THIRD_PARTY          = 0,
    LCS_NOTIFICATION_PERMIT_IF_USER_IGNORE,
    LCS_NOTIFICATION_FORBIDDEN_IF_USER_IGNORE,

    LCS_NOTIFICATION_TYPE_BUTT
};
typedef VOS_UINT8 LCS_NOTIFICATION_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LCS_LOCATION_TYPE_ENUM
 结构说明  : LCS特性MT-LR网络定位请求中的用户隐私信息操作枚举
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增枚举
*******************************************************************************/
enum LCS_LOCATION_TYPE_ENUM
{
    LCS_LOCATION_CURRENT                = 0,
    LCS_LOCATION_CURR_OR_LAST,
    LCS_LOCATION_INITIAL,

    LCS_LOCATION_TYPE_BUTT
};
typedef VOS_UINT8 LCS_LOCATION_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/



/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/

/*******************************************************************************
 结构名    : LCS_SHAPE_REP_STRU
 结构说明  : LCS特性MO-LR流程参数shape-rep对应结构体
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           bitEllipPoint               :1;
    VOS_UINT8                           bitEllipPointUncertCircle   :1;
    VOS_UINT8                           bitEllipPointUncertEllip    :1;
    VOS_UINT8                           bitPolygon                  :1;
    VOS_UINT8                           bitEllipPointAlt            :1;
    VOS_UINT8                           bitEllipPointAltUncertEllip :1;
    VOS_UINT8                           bitEllipArc                 :1;
    VOS_UINT8                           bitSpare                    :1;
} LCS_SHAPE_REP_STRU;

/*******************************************************************************
 结构名    : LCS_CLIENT_EXTERNAL_ID_STRU
 结构说明  : LCS特性客户端扩展ID结构体
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucValue[LCS_CLIENT_EXID_MAX_LEN];
}LCS_CLIENT_EXTERNAL_ID_STRU;

/*******************************************************************************
 结构名    : LCS_CLIENT_NAME_STRU
 结构说明  : LCS特性客户端名称结构体
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucValue[LCS_CLIENT_NAME_MAX_LEN];
}LCS_CLIENT_NAME_STRU;

/*******************************************************************************
 结构名    : LCS_MOLR_PARA_STRU
 结构说明  : LCS特性MO-LR流程参数结构体
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    LCS_MOLR_METHOD_ENUM_UINT8          enMethod;
    LCS_HOR_ACC_SET_ENUM_UINT8          enHorAccSet;
    VOS_UINT8                           ucHorAcc;                               /* horizontal-accuracy */

    LCS_VER_REQ_ENUM_UINT8              enVerReq;                               /* verticalCoordinate Request */
    LCS_VER_ACC_SET_ENUM_UINT8          enVerAccSet;
    VOS_UINT8                           ucVerAcc;                               /* vertical-accuracy */
    LCS_VEL_REQ_ENUM_UINT8              enVelReq;                               /* velocityRequest */

    LCS_REP_MODE_ENUM_UINT8             enRepMode;
    VOS_UINT16                          usTimeOut;                              /* MO-LR等待网侧回复定时器时长，单位为s */
    VOS_UINT16                          usInterval;                             /* 周期上报时的上报间隔时长，单位为s */

    union
    {
        VOS_UINT8                       ucShapeRep;
        LCS_SHAPE_REP_STRU              stShapeRep;
    } u;

    VOS_UINT8                           aucReserved[3];
    LCS_CLIENT_EXTERNAL_ID_STRU         stTPAddr;                               /* Third Party Address */
}LCS_MOLR_PARA_STRU;

/*******************************************************************************
 结构名    : LCS_MTLR_PARA_STRU
 结构说明  : LCS特性MT-LR流程参数结构体
  1.日    期   : 2015年8月25日
    作    者   : l00198894
    修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpClientExId     : 1;
    VOS_UINT32                          bitOpClientName     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           ucHandleId;
    LCS_NOTIFICATION_TYPE_ENUM_UINT8    enNtfType;
    LCS_LOCATION_TYPE_ENUM_UINT8        enLocationType;
    VOS_UINT8                           ucRsv;

    LCS_CLIENT_EXTERNAL_ID_STRU         stClientExId;
    LCS_CLIENT_NAME_STRU                stClientName;
}LCS_MTLR_PARA_STRU;




/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  8 函数声明
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

#endif /* end of LcsCommInterface.h */

