/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : AgpsParaDef.h
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2012年06月14日
  最近修改   :
  功能描述   : AGPS相关参数的定义头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年06月14日
    作    者   : h44270
    修改内容   : 创建文件

******************************************************************************/
#ifndef __AGPSPARADEF_H__
#define __AGPSPARADEF_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AGPS_MSR_ELEMENT_MAX_NUM                (16)                            /* GPS芯片回复的最大的测量成员个数 */
#define AGPS_MAX_SAT_NUM                        (16)                            /* 最大卫星个数 */
#define AGPS_MAX_MEAS_EVENT                     (8)                             /* 事件上报最大事件个数 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : AGPS_POSITION_ACTION_TYPE_ENUM
 结构说明  : 定位测量取消或者启动类型
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_POSITION_ACTION_TYPE_ENUM
{
    AGPS_POSITION_ACTION_TYPE_RRLP_MEAS = 0,
    AGPS_POSITION_ACTION_TYPE_RRC_MEAS     ,
    AGPS_POSITION_ACTION_TYPE_ABORT        ,

    AGPS_POSITION_ACTION_TYPE_BUTT
};
typedef VOS_UINT8 AGPS_POSITION_ACTION_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_RRLP_METHOD_TYPE_ENUM
 结构说明  : RRLP定位方式
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_RRLP_METHOD_TYPE_ENUM
{
    AGPS_RRLP_METHOD_TYPE_UE_ASSISTED                = 0,
    AGPS_RRLP_METHOD_TYPE_UE_ASSISTED_NO_ACCURACY,
    AGPS_RRLP_METHOD_TYPE_UE_BASED,
    AGPS_RRLP_METHOD_TYPE_UE_ASSISTED_PREFER,
    AGPS_RRLP_METHOD_TYPE_UE_BASED_PREFER,

    AGPS_RRLP_METHOD_TYPE_BUTT
};
typedef VOS_UINT8 AGPS_RRLP_METHOD_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_POSITION_RESULT_TYPE_ENUM
 结构说明  : 定位测量结果类型
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_POSITION_RESULT_TYPE_ENUM
{
    AGPS_POSITION_RESULT_TYPE_LOCATION  = 0,
    AGPS_POSITION_RESULT_TYPE_MEAS,
    AGPS_POSITION_RESULT_TYPE_ASSIST_REQ,
    AGPS_POSITION_RESULT_TYPE_ERROR,

    AGPS_POSITION_RESULT_TYPE_BUTT
};
typedef VOS_UINT8 AGPS_POSITION_RESULT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_POSITION_ESTIMAT_ENUM
 结构说明  : 定位结果位置估计类型
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_POSITION_ESTIMAT_ENUM
{
    AGPS_POSITION_ESTIMAT_ELLIP_POINT                    = 0,                   /* ellipsoid_point */
    AGPS_POSITION_ESTIMAT_ELLIP_POINT_UNCERT_CIRCLE,                            /* ellipsoid_point_uncert_circle */
    AGPS_POSITION_ESTIMAT_ELLIP_POINT_UNCERT_ELLIP,                             /* ellipsoid_point_uncert_ellipse */
    AGPS_POSITION_ESTIMAT_ELLIP_POINT_ALTI,                                     /* ellipsoid_point_alt */
    AGPS_POSITION_ESTIMAT_ELLIP_POINT_ALTI_ELLIP,                               /* ellipsoid_point_alt_uncertellipse */
    AGPS_POSITION_ESTIMAT_ELLIP_ARC,                                            /* ellips_arc */

    AGPS_POSITION_ESTIMAT_BUTT
};
typedef VOS_UINT8 AGPS_POSITION_ESTIMAT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_LATITUDE_SIGN_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_LATITUDE_SIGN_ENUM
{
    AGPS_ELLIP_POINT_LATITUDE_SIGN_NORTH = 0,
    AGPS_ELLIP_POINT_LATITUDE_SIGN_SOUTH,
    AGPS_ELLIP_POINT_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_LATITUDE_SIGN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_ENUM
{
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_NORTH = 0,
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_SOUTH,
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_UNCERT_CIRCLE_LATITUDE_SIGN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_ENUM
{
    AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_NORTH = 0,
    AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_SOUTH,
    AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_UNCERT_ELLIP_LATITUDE_SIGN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_ENUM
{
    AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_NORTH = 0,
    AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_SOUTH,
    AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_ALTI_LATITUDE_SIGN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_ALTI_DIRECT_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_ALTI_DIRECT_ENUM
{
    AGPS_ELLIP_POINT_ALTI_DIRECT_HEIGHT = 0,
    AGPS_ELLIP_POINT_ALTI_DIRECT_DEPTH,
    AGPS_ELLIP_POINT_ALTI_DIRECT_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_ALTI_DIRECT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_ENUM
{
    AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_NORTH = 0,
    AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_SOUTH,
    AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_ALTI_ELLIP_LATITUDE_SIGN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_ENUM
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_ENUM
{
    AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_HEIGHT = 0,
    AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_DEPTH,
    AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_BUTT
};
typedef VOS_UINT8 AGPS_ELLIP_POINT_ALTI_ELLIP_ALTI_DIRECT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_MULTI_PATH_INDIC_ENUM
 结构说明  : 定位结果多路径指示
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_MULTI_PATH_INDIC_ENUM
{
    AGPS_MULTI_PATH_INDIC_NOT_MEAS  = 0,
    AGPS_MULTI_PATH_INDIC_LOW,
    AGPS_MULTI_PATH_INDIC_MEDIUM,
    AGPS_MULTI_PATH_INDIC_HIGH,

    AGPS_MULTI_PATH_INDIC_BUTT
};
typedef VOS_UINT8 AGPS_MULTI_PATH_INDIC_ENUM_UINT8;

/*****************************************************************************
 枚举名    : AGPS_POSITION_ERROR_REASON_ENUM
 结构说明  : 定位结果错误原因
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum AGPS_POSITION_ERROR_REASON_ENUM
{
    AGPS_POSITION_ERROR_REASON_UNDEFINED                 = 0,                   /* undefined_error */
    AGPS_POSITION_ERROR_REASON_NOT_ENOUGH_GPS_SATS,                             /* not_enough_gps_satellites */
    AGPS_POSITION_ERROR_REASON_GPS_ASS_DATA_MISSING ,                           /* gps_assist_data_missing */

    AGPS_POSITION_ERROR_REASON_BUTT
};
typedef VOS_UINT8 AGPS_POSITION_ERROR_REASON_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_POS_UDRE_ENUM
 枚举说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_POS_UDRE_ENUM
{
    AGPS_POS_UDRE_LESS_THAN1         = 0,
    AGPS_POS_UDRE_BETWEEN1_AND4,
    AGPS_POS_UDRE_BETWEEN4_AND8,
    AGPS_POS_UDRE_OVER8,

    AGPS_POS_UDRE_BUTT
};
typedef VOS_UINT8 AGPS_POS_UDRE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_POS_SAT_STA_ENUM
 枚举说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_POS_SAT_STA_ENUM
{
    AGPS_POS_SAT_STA_NS_NN_U         = 0,                                       /* New satellite, new Navigation Model */
    AGPS_POS_SAT_STA_ES_SN,                                                     /* Existing satellite, same Navigation Model */
    AGPS_POS_SAT_STA_ES_NN_U,                                                   /* Existing satellite, new Navigation Model */
    AGPS_POS_SAT_STA_REV2,                                                      /* Reserved */
    AGPS_POS_SAT_STA_REV,                                                       /* Reserved */

    AGPS_POS_SAT_STA_BUTT
};
typedef VOS_UINT8 AGPS_POS_SAT_STA_ENUM_UINT8;

enum AGPS_POSITION_TYPE_ENUM
{
    AGPS_UE_POS_METHOD_TYPE_UE_ASSIST          = 0,
    AGPS_UE_POS_METHOD_TYPE_UE_BASED              ,
    AGPS_UE_POS_METHOD_TYPE_UE_BASED_PREF         ,
    AGPS_UE_POS_METHOD_TYPE_UE_ASSIST_PREF        ,

    AGPS_UE_POS_METHOD_TYPE_BUTT
};
typedef VOS_UINT8 AGPS_POSITION_TYPE_ENUM_UINT8;

enum AGPS_POS_METHOD_ENUM
{
    AGPS_POS_METHOD_OTDOA                                 = 0,
    AGPS_POS_METHOD_GPS                                      ,
    AGPS_POS_METHOD_OTDOA_OR_GPS                             ,
    AGPS_POS_METHOD_CELL_ID                                  ,

    AGPS_POS_METHOD_BUTT
};
typedef VOS_UINT8 AGPS_POS_METHOD_ENUM_UINT8;

enum AGPS_REP_CRIT_TYPE_ENUM
{
    AGPS_REP_CRIT_TYPE_POS_EVT_REP                        = 0,                  /* event_rep_crit */
    AGPS_REP_CRIT_TYPE_PERIOD_REP                            ,                  /* period_rep_crit */
    AGPS_REP_CRIT_TYPE_NO_REP                                ,                  /* no_rep */

    AGPS_REP_CRIT_TYPE_BUTT
};
typedef VOS_UINT8 AGPS_REP_CRIT_TYPE_ENUM_UINT8;

enum AGPS_UE_POS_EVT_ENUM
{
    AGPS_UE_POS_EVT_7A                                 = 0,
    AGPS_UE_POS_EVT_7B                                    ,
    AGPS_UE_POS_EVT_7C                                    ,
    AGPS_UE_POS_EVT_BUTT
};
typedef VOS_UINT8 AGPS_UE_POS_EVT_ENUM_UINT8;
enum AGPS_UDRE_GROWTH_RATE_ENUM
{
    AGPS_UDRE_GROWTH_RATE_GROWTH15 = 0,
    AGPS_UDRE_GROWTH_RATE_GROWTH2,
    AGPS_UDRE_GROWTH_RATE_GROWTH4,
    AGPS_UDRE_GROWTH_RATE_GROWTH6,
    AGPS_UDRE_GROWTH_RATE_GROWTH8,
    AGPS_UDRE_GROWTH_RATE_GROWTH10,
    AGPS_UDRE_GROWTH_RATE_GROWTH12,
    AGPS_UDRE_GROWTH_RATE_GROWTH16,
    AGPS_UDRE_GROWTH_RATE_BUTT
};
typedef VOS_UINT8 AGPS_UDRE_GROWTH_RATE_ENUM_UINT8;

enum AGPS_UDRE_VALID_TIME_ENUM
{
    AGPS_UDRE_VALID_TIME_VAL20SEC = 0,
    AGPS_UDRE_VALID_TIME_VAL40SEC,
    AGPS_UDRE_VALID_TIME_VAL80SEC,
    AGPS_UDRE_VALID_TIME_VAL160SEC,
    AGPS_UDRE_VALID_TIME_VAL320SEC,
    AGPS_UDRE_VALID_TIME_VAL640SEC,
    AGPS_UDRE_VALID_TIME_VAL1280SEC,
    AGPS_UDRE_VALID_TIME_VAL2560SEC,
    AGPS_UDRE_VALID_TIME_BUTT
};
typedef VOS_UINT8 AGPS_UDRE_VALID_TIME_ENUM_UINT8;

enum AGPS_DIFF_CORRECT_STA_ENUM
{
    AGPS_DIFF_CORRECT_STA_UDRE10 = 0,
    AGPS_DIFF_CORRECT_STA_UDRE075,
    AGPS_DIFF_CORRECT_STA_UDRE05,
    AGPS_DIFF_CORRECT_STA_UDRE03,
    AGPS_DIFF_CORRECT_STA_UDRE02,
    AGPS_DIFF_CORRECT_STA_UDRE01,
    AGPS_DIFF_CORRECT_STA_NO_DATA,
    AGPS_DIFF_CORRECT_STA_INVALID_DATA,
    AGPS_DIFF_CORRECT_STA_BUTT
};
typedef VOS_UINT8 AGPS_DIFF_CORRECT_STA_ENUM_UINT8;

enum AGPS_DOPPLER_UNCERTN_ENUM
{
    AGPS_DOPPLER_UNCERTN_HZ125 = 0,
    AGPS_DOPPLER_UNCERTN_HZ25,
    AGPS_DOPPLER_UNCERTN_HZ50,
    AGPS_DOPPLER_UNCERTN_HZ100,
    AGPS_DOPPLER_UNCERTN_HZ200,
    AGPS_DOPPLER_UNCERTN_SPARE3,
    AGPS_DOPPLER_UNCERTN_SPARE2,
    AGPS_DOPPLER_UNCERTN_SPARE1,
    AGPS_DOPPLER_UNCERTN_BUTT
};
typedef VOS_UINT8 AGPS_DOPPLER_UNCERTN_ENUM_UINT8;

enum AGPS_CODE_PHASE_SEARCH_WIN_ENUM
{
    AGPS_CODE_PHASE_SEARCH_WIN_W1023 = 0,
    AGPS_CODE_PHASE_SEARCH_WIN_W1,
    AGPS_CODE_PHASE_SEARCH_WIN_W2,
    AGPS_CODE_PHASE_SEARCH_WIN_W3,
    AGPS_CODE_PHASE_SEARCH_WIN_W4,
    AGPS_CODE_PHASE_SEARCH_WIN_W6,
    AGPS_CODE_PHASE_SEARCH_WIN_W8,
    AGPS_CODE_PHASE_SEARCH_WIN_W12,
    AGPS_CODE_PHASE_SEARCH_WIN_W16,
    AGPS_CODE_PHASE_SEARCH_WIN_W24,
    AGPS_CODE_PHASE_SEARCH_WIN_W32,
    AGPS_CODE_PHASE_SEARCH_WIN_W48,
    AGPS_CODE_PHASE_SEARCH_WIN_W64,
    AGPS_CODE_PHASE_SEARCH_WIN_W96,
    AGPS_CODE_PHASE_SEARCH_WIN_W128,
    AGPS_CODE_PHASE_SEARCH_WIN_W192,
    AGPS_CODE_PHASE_SEARCH_WIN_BUTT
};
typedef VOS_UINT8 AGPS_CODE_PHASE_SEARCH_WIN_ENUM_UINT8;


enum AGPS_UE_POS_EVT_INTERVAL_ENUM
{
    AGPS_UE_POS_EVT_INTERVAL_E5 = 0,
    AGPS_UE_POS_EVT_INTERVAL_E15   ,
    AGPS_UE_POS_EVT_INTERVAL_E60   ,
    AGPS_UE_POS_EVT_INTERVAL_E300  ,
    AGPS_UE_POS_EVT_INTERVAL_E900  ,
    AGPS_UE_POS_EVT_INTERVAL_E1800 ,
    AGPS_UE_POS_EVT_INTERVAL_E3600 ,
    AGPS_UE_POS_EVT_INTERVAL_E7200 ,
    AGPS_UE_POS_EVT_INTERVAL_BUTT
};
typedef VOS_UINT8 AGPS_UE_POS_EVT_INTERVAL_ENUM_UINT8;

enum AGPS_UE_POS_PERI_INTERVAL_ENUM
{
   AGPS_UE_POS_PERI_INTERVAL_RIL0 = 0,
   AGPS_UE_POS_PERI_INTERVAL_RIL0_25    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL0_5   ,
   AGPS_UE_POS_PERI_INTERVAL_RIL1    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL2    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL3    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL4    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL6    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL8    ,
   AGPS_UE_POS_PERI_INTERVAL_RIL12  ,
   AGPS_UE_POS_PERI_INTERVAL_RIL16,
   AGPS_UE_POS_PERI_INTERVAL_RIL20,
   AGPS_UE_POS_PERI_INTERVAL_RIL24,
   AGPS_UE_POS_PERI_INTERVAL_RIL28,
   AGPS_UE_POS_PERI_INTERVAL_RIL32,
   AGPS_UE_POS_PERI_INTERVAL_RIL64 ,
   AGPS_UE_POS_PERI_INTERVAL_BUTT
};
typedef VOS_UINT8  AGPS_UE_POS_PERI_INTERVAL_ENUM_UINT8;

enum AGPS_UE_POS_RPT_MOUNT_ENUM
{
    AGPS_UE_POS_RPT_MOUNT_RA1 = 0    ,
    AGPS_UE_POS_RPT_MOUNT_RA2        ,
    AGPS_UE_POS_RPT_MOUNT_RA4        ,
    AGPS_UE_POS_RPT_MOUNT_RA8        ,
    AGPS_UE_POS_RPT_MOUNT_RA16       ,
    AGPS_UE_POS_RPT_MOUNT_RA32       ,
    AGPS_UE_POS_RPT_MOUNT_RA64       ,
    AGPS_UE_POS_RPT_MOUNT_RA_INFINITY,
    AGPS_UE_POS_RPT_MOUNT_BUTT
};
typedef VOS_UINT8 AGPS_UE_POS_RPT_MOUNT_ENUM_UINT8;

enum AGPS_THRESHOLD_POSITION_ENUM
{
   AGPS_THRESHOLD_POSITION_PC10 = 0,
   AGPS_THRESHOLD_POSITION_PC20    ,
   AGPS_THRESHOLD_POSITION_PC30    ,
   AGPS_THRESHOLD_POSITION_PC40    ,
   AGPS_THRESHOLD_POSITION_PC50    ,
   AGPS_THRESHOLD_POSITION_PC100    ,
   AGPS_THRESHOLD_POSITION_PC200    ,
   AGPS_THRESHOLD_POSITION_PC300    ,
   AGPS_THRESHOLD_POSITION_PC500    ,
   AGPS_THRESHOLD_POSITION_PC1000    ,
   AGPS_THRESHOLD_POSITION_PC2000    ,
   AGPS_THRESHOLD_POSITION_PC5000    ,
   AGPS_THRESHOLD_POSITION_PC10000    ,
   AGPS_THRESHOLD_POSITION_PC20000    ,
   AGPS_THRESHOLD_POSITION_PC50000    ,
   AGPS_THRESHOLD_POSITION_PC100000    ,
   AGPS_THRESHOLD_POSITION_BUTT
};
typedef VOS_UINT8  AGPS_THRESHOLD_POSITION_ENUM_UINT8;

enum AGPS_THRESHOLD_SFN_SFN_ENUM
{
   AGPS_THRESHOLD_SFN_SFN_C0_25 = 0,
   AGPS_THRESHOLD_SFN_SFN_C0_5    ,
   AGPS_THRESHOLD_SFN_SFN_C1    ,
   AGPS_THRESHOLD_SFN_SFN_C2    ,
   AGPS_THRESHOLD_SFN_SFN_C3    ,
   AGPS_THRESHOLD_SFN_SFN_C4    ,
   AGPS_THRESHOLD_SFN_SFN_C5    ,
   AGPS_THRESHOLD_SFN_SFN_C10    ,
   AGPS_THRESHOLD_SFN_SFN_C20    ,
   AGPS_THRESHOLD_SFN_SFN_C50    ,
   AGPS_THRESHOLD_SFN_SFN_C100    ,
   AGPS_THRESHOLD_SFN_SFN_C200    ,
   AGPS_THRESHOLD_SFN_SFN_C500    ,
   AGPS_THRESHOLD_SFN_SFN_C1000    ,
   AGPS_THRESHOLD_SFN_SFN_C2000    ,
   AGPS_THRESHOLD_SFN_SFN_C5000    ,
   AGPS_THRESHOLD_SFN_SFN_BUTT
};
typedef VOS_UINT8  AGPS_THRESHOLD_SFN_SFN_ENUM_UINT8;

enum AGPS_THRESHOLD_SFN_GPS_TOW_ENUM
{
   AGPS_THRESHOLD_SFN_GPS_TOW_US1 = 0,
   AGPS_THRESHOLD_SFN_GPS_TOW_US2    ,
   AGPS_THRESHOLD_SFN_GPS_TOW_US3   ,
   AGPS_THRESHOLD_SFN_GPS_TOW_US5    ,
   AGPS_THRESHOLD_SFN_GPS_TOW_US10    ,
   AGPS_THRESHOLD_SFN_GPS_TOW_US20   ,
   AGPS_THRESHOLD_SFN_GPS_TOW_US50    ,
   AGPS_THRESHOLD_SFN_GPS_TOW_US100    ,
   AGPS_THRESHOLD_SFN_GPS_TOW_BUTT
};
typedef VOS_UINT8  AGPS_THRESHOLD_SFN_GPS_TOW_ENUM_UINT8;


/*******************************************************************************
 枚举名    : AGPS_EPHEM_CLOCK_TYPE_ENUM
 枚举说明  : 需要指示ELEMENT ephem_and_clock是哪个接入层提供的
 1.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_EPHEM_CLOCK_TYPE_ENUM
{
   AGPS_EPHEM_CLOCK_TYPE_RRLP = 0,
   AGPS_EPHEM_CLOCK_TYPE_RRC     ,
   AGPS_EPHEM_CLOCK_TYPE_BUTT
};
typedef VOS_UINT8  AGPS_EPHEM_CLOCK_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_IONOSPHERIC_MODEL_TYPE_ENUM_UINT8
 枚举说明  : 需要指示ELEMENT ionospheric_model是哪个接入层提供的
 1.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_IONOSPHERIC_MODEL_TYPE_ENUM
{
   AGPS_IONOSPHERIC_MODEL_TYPE_RRLP = 0,
   AGPS_IONOSPHERIC_MODEL_TYPE_RRC    ,
   AGPS_IONOSPHERIC_MODEL_TYPE_BUTT
};
typedef VOS_UINT8  AGPS_IONOSPHERIC_MODEL_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_UTC_MODEL_TYPE_ENUM_UINT8
 枚举说明  : 需要指示ELEMENT UTC_model是哪个接入层提供的
 1.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_UTC_MODEL_TYPE_ENUM
{
   AGPS_UTC_MODEL_TYPE_RRLP = 0,
   AGPS_UTC_MODEL_TYPE_RRC     ,
   AGPS_UTC_MODEL_TYPE_BUTT
};
typedef VOS_UINT8  AGPS_UTC_MODEL_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_ALMANAC_SAT_INFO_TYPE_ENUM
 枚举说明  : 需要指示ELEMENT almanac是哪个接入层提供的
 1.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_ALMANAC_SAT_INFO_TYPE_ENUM
{
   AGPS_ALMANAC_SAT_INFO_TYPE_RRLP = 0,
   AGPS_ALMANAC_SAT_INFO_TYPE_RRC     ,
   AGPS_ALMANAC_SAT_INFO_TYPE_BUTT
};
typedef VOS_UINT8  AGPS_ALMANAC_SAT_INFO_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : AGPS_MULT_SETS_ENUM
 枚举说明  : mult set的取值
 1.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
enum AGPS_MULT_SETS_ENUM
{
   AGPS_MULT_SETS_MULTIPLE = 0,
   AGPS_MULT_SETS_ONE     ,

   AGPS_MULT_SETS_BUTT
};
typedef VOS_UINT8  AGPS_MULT_SETS_ENUM_UINT8;



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
 结构名    : AGPS_RRLP_METHOD_TYPE_STRU
 结构说明  : GAS的定位测量请求指示的具体参数，通过MTA发送给GPS芯片
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_RRLP_METHOD_TYPE_ENUM_UINT8            enRrlpMethodType;               /*ELEMENT  RRLP_method_type,定位类型 */
    VOS_UINT8                                   ucAccuracy;                     /*ELEMENT  method_accuracy,测量精度，取值范围:0-127, 无效值;0xFF */
    VOS_UINT8                                   aucReserved1[2];                /* 保留位 */
}AGPS_RRLP_METHOD_TYPE_STRU;

/*******************************************************************************
 结构名    : AGPS_POSITION_INSTRUCT_STRU
 结构说明  : GAS的定位测量请求指示的具体参数，通过MTA发送给GPS芯片
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_RRLP_METHOD_TYPE_STRU                  stRrlpMethodType;               /* ELEMENT RRLP_pos_instruct */
    VOS_UINT8                                   ucMeasureRspTime;               /* ELEMENT  resp_time_seconds,测量反应时间，取值范围:1,2,4,8,16,32,64,128, 单位:秒 */
    AGPS_MULT_SETS_ENUM_UINT8                   enUseMultipleSets;              /* ELEMENT  mult_sets,是否发送多个信息集合，0:MultipleSets; 1:OneSet */
    VOS_UINT8                                   aucReserved1[2];                /* 保留位 */
}AGPS_POSITION_INSTRUCT_STRU;

/*******************************************************************************
 结构名    : AGPS_REP_QUANT_STRU
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpHoriAccur         : 1;
    VOS_UINT32                                  bitOpVerticalAccur     : 1;
    VOS_UINT32                                  bitOpSpare             : 30;

    PS_BOOL_ENUM_UINT8                          enGpsTimOfCellWant;             /* gps_timing_of_cell_wanted, BOOLEAN */
    PS_BOOL_ENUM_UINT8                          enAddAssistDataReq;             /* addl_assist_data_req, BOOLEAN */
    AGPS_POSITION_TYPE_ENUM_UINT8               enMethodType;                   /* ATTLIST RRC_method_type literal, ENUMERATED */
    AGPS_POS_METHOD_ENUM_UINT8                  enPosMethod;                    /* ATTLIST RRC_method literal, ENUMERATED */
    VOS_UINT8                                   ucHoriAccur;                    /* ELEMENT hor_acc, BIT STRING(SIZE(7))  OPTIONAL */
    VOS_UINT8                                   ucVerticalAccur;                /* ELEMENT vert_acc, BIT STRING(SIZE(7))  OPTIONAL */
    VOS_UINT8                                   aucRsv[2];                      /* 保留位 */
}AGPS_REP_QUANT_STRU;

/*******************************************************************************
 结构名    : AGPS_UE_POS_EVT_SPEC_INFO_STRU
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_UE_POS_EVT_ENUM_UINT8                  enChoice;

    union
    {
        AGPS_THRESHOLD_POSITION_ENUM_UINT8      enE7a;                          /* ENUMERATED */
        AGPS_THRESHOLD_SFN_SFN_ENUM_UINT8       enE7b;                          /* ENUMERATED */
        AGPS_THRESHOLD_SFN_GPS_TOW_ENUM_UINT8   enE7c;                          /* ENUMERATED */
    } u;

    VOS_UINT8                                   aucReserved[2];                 /* 保留位 */
}AGPS_UE_POS_EVT_SPEC_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_UE_POS_EVT_PARAM_STRU
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpEvtSpecInfo       : 1;
    VOS_UINT32                                  bitOpSpare             : 31;

    PS_BOOL_ENUM_UINT8                          enRptFirstFix;                  /* report_first_fix, BOOLEAN */
    AGPS_UE_POS_RPT_MOUNT_ENUM_UINT8            enReportAmount;                 /* ATTLIST rep_amount literal, ENUMERATED */
    AGPS_UE_POS_EVT_INTERVAL_ENUM_UINT8         enMeasInterval;                 /* ATTLIST meas_interval literal, ENUMERATED */
    VOS_UINT8                                   aucReserved[1];                 /* 保留位 */

    AGPS_UE_POS_EVT_SPEC_INFO_STRU              stEvtSpecInfo;                  /* event_specific_info */
}AGPS_UE_POS_EVT_PARAM_STRU;

/*******************************************************************************
 结构名    : AGPS_UE_POS_EVT_PARAM_LIST_STRU
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulCnt;
    AGPS_UE_POS_EVT_PARAM_STRU                  astUePosEvtParam[AGPS_MAX_MEAS_EVENT];
}AGPS_UE_POS_EVT_PARAM_LIST_STRU;


/*******************************************************************************
 结构名    : AGPS_PERIOD_RPTNG_CRTR_STRU
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_UE_POS_RPT_MOUNT_ENUM_UINT8         enRptngAmount;
    AGPS_UE_POS_PERI_INTERVAL_ENUM_UINT8     enMeasInterval;
    VOS_UINT8                                   aucRsv[2];                      /* 保留位 */
}AGPS_PERIOD_RPTNG_CRTR_STRU;

/*******************************************************************************
 结构名    : AGPS_REP_CRIT_STRU
 结构说明  :
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */

    AGPS_REP_CRIT_TYPE_ENUM_UINT8               enChoice;
    union
    {
        AGPS_UE_POS_EVT_PARAM_LIST_STRU         stUePosRptngCrtr;               /* ELEMENT event_par */
        AGPS_PERIOD_RPTNG_CRTR_STRU             stPeriodRptngCrtr;              /* ELEMENT period_rep_crit */
        VOS_UINT32                              ulNoRptng;                      /* NULL */
    } u;
}AGPS_REP_CRIT_STRU;

/*******************************************************************************
 结构名    : AGPS_RRLP_MEAS_REQ_STRU
 结构说明  : GAS的定位测量请求指示，通过MEA发送给GPS芯片
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_POSITION_INSTRUCT_STRU                 stPosInstruct;                  /* ELEMENT RRLP_pos_instruct,定位指示 */
    VOS_UINT8                                   aucReserved[108];               /* UNION结构RRC比RRLP多，增加填充为生成ASN */
}AGPS_RRLP_MEAS_REQ_STRU;

/*******************************************************************************
 结构名    : AGPS_RRC_MEAS_REQ_STRU
 结构说明  : WAS发给MMC的定位测量请求，通过MTA发送给GPS芯片
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_REP_QUANT_STRU                         stRepQuant;                     /* ELEMENT rep_quant */
    AGPS_REP_CRIT_STRU                          stRepCrit;                      /* ELEMENT rep_crit */
}AGPS_RRC_MEAS_REQ_STRU;

/*******************************************************************************
 结构名    : AGPS_MEASURE_REQ_STRU
 结构说明  : pos_meas,RR发给MMC的定位测量请求
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */

    AGPS_POSITION_ACTION_TYPE_ENUM_UINT8        enActionTypeChoice;             /* 测量请求类型 */
    union
    {
        AGPS_RRLP_MEAS_REQ_STRU                 stRrlpMeasReq;                  /* ELEMENT  RRLP_meas, G模RRLP的测量请求 */
        AGPS_RRC_MEAS_REQ_STRU                  stRrcMeasReq;                   /* ELEMENT RRC_meas, W模RRC的测量请求 */
    }u;
}AGPS_MEASURE_REQ_STRU;

/*******************************************************************************
 结构名    : AGPS_LATITUDE_STRU
 结构说明  : 纬度
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_ELLIP_POINT_LATITUDE_SIGN_ENUM_UINT8    enNorth;                       /* ENUMERATED */
    VOS_UINT8                                    aucRsv[3];                     /* 保留位 */
    VOS_UINT32                                   ulDegrees;                     /* INTEGER(0..8388607) */
} AGPS_LATITUDE_STRU;

/*******************************************************************************
 结构名    : AGPS_COORDINATE_STRU
 结构说明  : 坐标值:经度和纬度
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_LATITUDE_STRU                          stLatitude;
    VOS_INT32                                   lLongitude;                     /* INTEGER(-8388608..8388607) */
} AGPS_COORDINATE_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_POINT_STRU
 结构说明  : 定位数据:ellipsoid_point
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_COORDINATE_STRU                        stCoordinate;
} AGPS_ELLIP_POINT_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU
 结构说明  : 定位数据:ellipsoid_point_uncert_circle
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_COORDINATE_STRU                        stCoordinate;                   /* 坐标值*/
    VOS_UINT8                                   ucUncertnCode;                  /* INTEGER(0..127) */
    VOS_UINT8                                   aucRsv[3];                     /* 保留位 */
} AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU
 结构说明  : 定位数据:uncert_ellipse
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucUncertnSemiMajor;             /* INTEGER(0..127) */
    VOS_UINT8                                   ucUncertnSemiMin;               /* INTEGER(0..127) */
    VOS_UINT8                                   ucOrientMajorAxis;              /* INTEGER(0..89) */
    VOS_UINT8                                   ucConfidence;                   /* INTEGER(0..100) */
} AGPS_UNCERT_ELLIPSE_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU
 结构说明  : 定位数据:ellipsoid_point_uncert_ellipse
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_COORDINATE_STRU                        stCoordinate;                   /* 坐标值*/
    AGPS_UNCERT_ELLIPSE_STRU                    stUncertEllipse;                /* uncert_ellipse */
} AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU;

typedef struct
{
    AGPS_ELLIP_POINT_ALTI_DIRECT_ENUM_UINT8             enAltiDirect;           /* ENUMERATED,表示海平面以上还是以下 */
    VOS_UINT8                                           aucReserved[1];         /* 保留位 */
    VOS_UINT16                                          usHeight;               /* INTEGER(0..32767)，绝对值 */
} AGPS_ALTITUDE_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_POINT_ALTI_STRU
 结构说明  : 定位数据:ellipsoid_point_alt
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_COORDINATE_STRU                        stCoordinate;                   /* 坐标 */
    AGPS_ALTITUDE_STRU                          stAltitude;                     /* 海拔 */
} AGPS_ELLIP_POINT_ALTI_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_POINT_ALTI_ELLIP_STRU
 结构说明  : 定位数据:ellipsoid_point_alt_uncertellipse
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_COORDINATE_STRU                        stCoordinate;                   /* 坐标 */
    AGPS_ALTITUDE_STRU                          stAltitude;                     /* 海拔 */
    VOS_UINT8                                   ucUncertnSemiMajor;             /* INTEGER(0..127) */
    VOS_UINT8                                   ucUncertnSemiMin;               /* INTEGER(0..127) */
    VOS_UINT8                                   ucOrientMajorAxis;              /* INTEGER(0..89) */
    VOS_UINT8                                   ucUncertnAlti;                  /* INTEGER(0..127) */
    VOS_UINT8                                   ucConfidence;                   /* INTEGER(0..100) */
    VOS_UINT8                                   aucReserved[3];
} AGPS_ELLIP_POINT_ALTI_ELLIP_STRU;

/*******************************************************************************
 结构名    : AGPS_ELLIP_ARC_STRU
 结构说明  : 定位数据:ellips_arc
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_COORDINATE_STRU                        stCoordinate;                   /* coordinate,坐标 */
    VOS_UINT16                                  usInnerRad;                     /* inner_rad,2 octets */
    VOS_UINT8                                   ucUncertRad;                    /* uncert_rad,1 octets */
    VOS_UINT8                                   ucOffsetAngle;                  /* offset_angle,1 octets */
    VOS_UINT8                                   ucIncludedAngle;                /* included_angle,1 octets */
    VOS_UINT8                                   ucConfidence;                   /* confidence,INTEGER(0..100) */
    VOS_UINT8                                   aucReserved[2];
} AGPS_ELLIP_ARC_STRU;

/*******************************************************************************
 结构名    : AGPS_SHAPE_DATA_STRU
 结构说明  : 定位数据
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */

    AGPS_POSITION_ESTIMAT_ENUM_UINT8            enEstimatTypeChoice;            /* 位置估计使用的方法 */
    union
    {
        AGPS_ELLIP_POINT_STRU                   stEllipPoint;                   /* ellipsoid_point */
        AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU     stEllipPointUncertCircle;       /* ellipsoid_point_uncert_circle */
        AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU      stEllipPointUncertEllip;        /* ellipsoid_point_uncert_ellipse */
        AGPS_ELLIP_POINT_ALTI_STRU              stEllipPointAlti;               /* ellipsoid_point_alt */
        AGPS_ELLIP_POINT_ALTI_ELLIP_STRU        stEllipPointAltiEllip;          /* ellipsoid_point_alt_uncertellipse */
        AGPS_ELLIP_ARC_STRU                     stEllipArc;                     /* ellips_arc */
    } u;
} AGPS_SHAPE_DATA_STRU;

/*******************************************************************************
 结构名    : AGPS_LOCATION_PARA_STRU
 结构说明  : 定位位置参数
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpTime              : 1;
    VOS_UINT32                                  bitOpDirection         : 1;
    VOS_UINT32                                  bitOpSpare             : 30;

    VOS_UINT32                                  ulTime;                         /* time, 和GPS TOW含义相同, INTEGER(0..14399999) */
    VOS_UINT8                                   ucDirection;                    /* direction, 映射到水平方向的速率, INTEGER(0..359) */
    VOS_UINT8                                   aucReserved[3];
    AGPS_SHAPE_DATA_STRU                        stShapeData;                    /* shape_data */
} AGPS_LOCATION_PARA_STRU;

/*******************************************************************************
 结构名    : AGPS_LOCATION_INFO_STRU
 结构说明  : 定位位置信息
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpTimeOfFix         : 1;
    VOS_UINT32                                  bitOpSpare             : 31;

    AGPS_LOCATION_PARA_STRU                     stLocationPara;                 /* location_parameters,位置信息 */
    VOS_UINT32                                  ulTimeOfFix;                    /* time_of_fix, 当前接入层不使用 */
} AGPS_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_GPS_MEASURE_ELEMENT_STRU
 结构说明  : 定位GPS测量信息成员
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucSatId;                        /* INTEGER(0..63) */
    VOS_UINT8                                   ucCarr2Noise;                   /* ELEMENT ucCNo, INTEGER(0..63) */
    VOS_UINT8                                   aucReserved1[2];
    VOS_INT32                                   lDoppler;                       /* RRLP:INTEGER(-32768..32767),RRC:INTEGER(-32768..32768) */
    VOS_UINT16                                  usWholeChips;                   /* INTEGER(0..1022) */
    VOS_UINT16                                  usFracChips;                    /* INTEGER(0..1024) */
    AGPS_MULTI_PATH_INDIC_ENUM_UINT8            enMultipathIndic;               /* ENUMERATED */
    VOS_UINT8                                   ucPseuRangeRmsErr;              /* INTEGER(0..63) */
    VOS_UINT8                                   aucReserved2[2];
} AGPS_GPS_MEASURE_PARA_STRU;


/*******************************************************************************
 结构名    : AGPS_REF_TIME_ONLY_STRU
 结构说明  : 参考时间信息
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulTow;                          /* ELEMENT GPS TOW, INTEGER(0..14399999) */
} AGPS_REF_TIME_ONLY_STRU;

/*******************************************************************************
 结构名    : AGPS_GPS_MEASURE_INFO_STRU
 结构说明  : 定位测量信息
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    AGPS_REF_TIME_ONLY_STRU                     stRefTimeOnly;                  /* ELEMENT ref_time_only */

    VOS_UINT32                                  ulGpsMeasNum;                   /* GPS测量成员个数 */
    AGPS_GPS_MEASURE_PARA_STRU                  astGpsMeasParaList[AGPS_MSR_ELEMENT_MAX_NUM];
} AGPS_GPS_MEASURE_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_ADDITION_REQ_SAT_STRU
 结构说明  : 需要向网络侧请求的辅助数据信息
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucSatId;
    VOS_UINT8                                   ucIode;                         /* INTEGER(0..255) */
    VOS_UINT8                                   aucReserved[2];
}AGPS_ADDITION_REQ_SAT_STRU;

/*******************************************************************************
 结构名    : AGPS_NAV_ADD_DATA_STRU
 结构说明  : 需要向网络侧请求的辅助数据信息
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                  usGpsWeek;                      /* ELEMENT GPS_week */
    VOS_UINT8                                   ucGpsToe;                       /* ELEMENT GPS_toe */
    VOS_UINT8                                   ucTtoeLimit;                    /* ELEMENT ttoe_limit */
    VOS_UINT16                                  usAddlReqSatNum;
    VOS_UINT8                                   aucReserved[2];
    AGPS_ADDITION_REQ_SAT_STRU                  astAddlReqSat[AGPS_MAX_SAT_NUM];/* ELEMENT addl_req_sat */
}AGPS_NAV_ADD_DATA_STRU;

/*******************************************************************************
 结构名    : AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU
 结构说明  : 需要向网络侧请求的辅助数据信息
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpNavAddData        : 1;
    VOS_UINT32                                  bitOpSpare             : 31;

    VOS_UINT8                                   ucAlmReq;                       /* ELEMENT alm_req */
    VOS_UINT8                                   ucUtcModelReq;                  /* ELEMENT UTC_model_req */
    VOS_UINT8                                   ucIonReq;                       /* ELEMENT ion_req */
    VOS_UINT8                                   ucNavModelReq;                  /* ELEMENT nav_model_req */
    VOS_UINT8                                   ucDgpsCorrReq;                  /* ELEMENT DGPS_corr_req */
    VOS_UINT8                                   ucRefLocReq;                    /* ELEMENT ref_loc_req */
    VOS_UINT8                                   ucRefTimeReq;                   /* ELEMENT ref_time_req */
    VOS_UINT8                                   ucAquAssistReq;                 /* ELEMENT aqu_assist_req */
    VOS_UINT8                                   ucRtIntegrReq;                  /* ELEMENT rt_integr_req */
    VOS_UINT8                                   aucReserved[3];
    AGPS_NAV_ADD_DATA_STRU                      stNavAddData;                   /* ELEMENT nav_addl_data */
}AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU;

/*******************************************************************************
 结构名    : AGPS_POSITION_LOCATION_ERR_STRU
 结构说明  : 定位测量错误回复
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpAssistDataReq     : 1;
    VOS_UINT32                                  bitOpSpare             : 31;

    AGPS_POSITION_ERROR_REASON_ENUM_UINT8       enLocErrReason;                 /* ELEMENT err_reason,定位错误原因 */
    VOS_UINT8                                   aucRsv[3];                      /* 保留位 */

    AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU  stAssistDataReq;                /* ELEMENT GPS_assist_req,辅助数据请求 */
} AGPS_POSITION_ERR_STRU;

/*******************************************************************************
 结构名    : AGPS_GPS_TIME_STRU
 结构说明  : UE positioning GPS reference time中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulGpsTowMsec;                   /* ELEMENT GPS_TOW_msec */
    VOS_UINT16                                  usGpsWeek;                      /* ELEMENT GPS_week */
    VOS_UINT8                                   aucReserved[2];                 /* 保留  */
}AGPS_GPS_TIME_STRU;

/*******************************************************************************
 结构名    : AGPS_GSM_TIME_STRU
 结构说明  : ReferenceTime中的GSMTime
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpBcchCarrier    : 1;
    VOS_UINT32                                  bitOpBsic           : 1;
    VOS_UINT32                                  bitOpSpare          : 30;

    VOS_UINT32                                  ulFrameNum;                     /* ELEMENT frame_number, INTEGER(0..2097151) */
    VOS_UINT8                                   ucTimeSlotNum;                  /* ELEMENT time_slot_number, INTEGER(0..7) */
    VOS_UINT8                                   ucBitNum;                       /* ELEMENT bit_number, INTEGER(0..156) */
    VOS_UINT16                                  usBcchCarrier;                  /* ELEMENT BCCH_carrier, INTEGER(0..1023) */
    VOS_UINT8                                   ucBsic;                         /* ELEMENT BSIC, INTEGER(0..63) */
    VOS_UINT8                                   aucReserved[3];                 /* 保留位 */
} AGPS_GSM_TIME_STRU;

/*******************************************************************************
 结构名    : AGPS_GPS_TOW_ASSIST_STRU
 结构说明  : UE positioning GPS reference time中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucSatId;                        /* ELEMENT sat_id */
    VOS_UINT8                                   aucReserved1[1];
    VOS_UINT16                                  usTlmWord;                      /* ELEMENT tlm_word */
    PS_BOOL_ENUM_UINT8                          enAntiSp;                       /* ELEMENT anti_sp */
    PS_BOOL_ENUM_UINT8                          enAlert;                        /* ELEMENT alert */
    VOS_UINT8                                   ucTlmRes;                       /* ELEMENT ucTlmReserv,  tlm_res*/
    VOS_UINT8                                   aucReserved2[1];
}AGPS_GPS_TOW_ASSIST_STRU;

/*******************************************************************************
 结构名    : AGPS_GPS_TOW_ASSIST_LIST_STRU
 结构说明  : UE positioning GPS reference time中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulGpsTowAssistNum;
    AGPS_GPS_TOW_ASSIST_STRU                    astGpsTowAssist[AGPS_MAX_SAT_NUM];
}AGPS_GPS_TOW_ASSIST_LIST_STRU;

/*******************************************************************************
 结构名    : AGPS_REFERENCE_TIME_STRU
 结构说明  : UE positioning GPS reference time
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpGsmTime            : 1;
    VOS_UINT32                                  bitOpGpsTowAssistList   : 1;
    VOS_UINT32                                  bitSpare                : 30;

    AGPS_GPS_TIME_STRU                          stGpsTime;                      /* ELEMENT GPS_time */
    AGPS_GSM_TIME_STRU                          stGsmTime;                      /* ELEMENT GSM_time */
    AGPS_GPS_TOW_ASSIST_LIST_STRU               stGpsTowAssistList;             /* ELEMENT GPS_TOW_assist */
}AGPS_REFERENCE_TIME_STRU;

/*******************************************************************************
 结构名    : AGPS_UP_DGPS_CORRECTION_STRU
 结构说明  : UE positioning GPS DGPS corrections
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpDeltaPrc2:1;
    VOS_UINT32                                  bitOpDeltaRrc2:1;
    VOS_UINT32                                  bitOpSpare:30;

    VOS_UINT8                                   ucSatId;                        /* ELEMENT sat_id, INTEGER(0..63) */
    VOS_UINT8                                   ucIode;                         /* ELEMENT IODE, INTEGER(0..255) */
    AGPS_POS_UDRE_ENUM_UINT8                    enUdre;                         /* ELEMENT UDRE, ENUMERATED */
    VOS_UINT8                                   aucReserved1[1];
    VOS_INT16                                   sPrc;                           /* ELEMENT PRC, INTEGER(-2047..2047) */
    VOS_INT8                                    cRrc;                           /* ELEMENT RRC, INTEGER(-127..127) */
    VOS_INT8                                    cDeltaPrc2;                     /* ELEMENT delta_PRC2, INTEGER(-127..127) */
    VOS_INT8                                    cDeltaRrc2;                     /* ELEMENT delta_RRC2, INTEGER(-7..7) */
    VOS_UINT8                                   aucReserved2[3];

}AGPS_UP_DGPS_CORRECTION_STRU;

/*******************************************************************************
 结构名    : AGPS_DGPS_CORRECTION_STRU
 结构说明  : UE positioning GPS DGPS corrections
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulDgpsCorrectionNum;
    AGPS_UP_DGPS_CORRECTION_STRU                astUpDgpsCorrection[AGPS_MAX_SAT_NUM];
}AGPS_DGPS_CORRECTION_STRU;

/*******************************************************************************
 结构名    : AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU
 结构说明  : UE positioning GPS Ephemeris and Clock Correction parameters
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体命名，该结构体部分参数为有符号类型，目前GAS专用
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucCodeOnL2;                     /* ELEMENT l2_code, INTEGER (0..3),BIT STRING(SIZE(2)) */
    VOS_UINT8                                   ucUraIndex;                     /* ELEMENT ura, INTEGER (0..15),BIT STRING(SIZE(4)) */
    VOS_UINT8                                   ucSatHealth;                    /* ELEMENT sv_health, INTEGER (0..63),BIT STRING(SIZE(6)) */
    VOS_UINT8                                   aucReserved1[1];
    VOS_UINT16                                  usIodc;                         /* ELEMENT iodc, INTEGER (0..1023),BIT STRING(SIZE(10)) */
    VOS_UINT8                                   ucL2PFlag;                      /* ELEMENT l2p_flag, INTEGER (0..1),BIT STRING(SIZE(1)) */
    VOS_UINT8                                   aucReserved2[1];
    VOS_UINT32                                  ulReserved1;                    /* ELEMENT esr1 INTEGER (0..8388607), -- 23-bit field */
    VOS_UINT32                                  ulReserved2;                    /* ELEMENT esr2 INTEGER (0..16777215), -- 24-bit field */
    VOS_UINT32                                  ulReserved3;                    /* ELEMENT esr3 INTEGER (0..16777215), -- 24-bit field */
    VOS_UINT16                                  usReserved4;                    /* ELEMENT esr4 INTEGER (0..65535), -- 16-bit field*/
    VOS_INT8                                    cTGd;                           /* ELEMENT tgd, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved3[1];
    VOS_UINT16                                  usTOc;                          /* ELEMENT toc, INTEGER (0..37799),BIT STRING(SIZE(16)) */
    VOS_INT8                                    cAf2;                           /* ELEMENT af2, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved4[1];
    VOS_INT16                                   sAf1;                           /* ELEMENT af1, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved5[2];
    VOS_INT32                                   lAf0;                           /* ELEMENT af0, INTEGER (-2097152..2097151),BIT STRING(SIZE(22)) */
    VOS_INT16                                   sCRs;                           /* ELEMENT crs, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_INT16                                   sDeltaN;                        /* ELEMENT delta_n, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_INT32                                   lM0;                            /* ELEMENT m0, INTEGER (-2147483648..2147483647),BIT STRING(SIZE(32)) */
    VOS_INT16                                   sCUc;                           /* ELEMENT cuc, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved6[2];
    VOS_UINT32                                  ulEcc;                          /* ELEMENT ecc, INTEGER (0..4294967295),BIT STRING(SIZE(32)) */
    VOS_INT16                                   sCUs;                           /* ELEMENT cus, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved7[2];
    VOS_UINT32                                  ulPowerHalf;                    /* ELEMENT power_half, BIT STRING(SIZE(32)) */
    VOS_UINT16                                  usTOe;                          /* ELEMENT toe, INTEGER (0..37799),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   ucFitFlag;                      /* ELEMENT fit_flag, INTEGER (0..1),BIT STRING(SIZE(1)) */
    VOS_UINT8                                   ucAodo;                         /* ELEMENT aoda, INTEGER (0..31),BIT STRING(SIZE(5)) */
    VOS_INT16                                   sCIc;                           /* ELEMENT cic, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved8[2];
    VOS_INT32                                   lOmega0;                        /* ELEMENT omega0, INTEGER (-2147483648..2147483647),BIT STRING(SIZE(32)) */
    VOS_INT16                                   sCIs;                           /* ELEMENT cis, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved9[2];
    VOS_INT32                                   lI0;                            /* ELEMENT i0, INTEGER (-2147483648..2147483647),BIT STRING(SIZE(32)) */
    VOS_INT16                                   sCRc;                           /* ELEMENT crc, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved10[2];
    VOS_INT32                                   lOmega;                         /* ELEMENT omega, INTEGER (-2147483648..2147483647),BIT STRING(SIZE(32)) */
    VOS_INT32                                   lOmegaDot;                      /* ELEMENT omega_dot, INTEGER (-8388608..8388607),BIT STRING(SIZE(24)) */
    VOS_INT16                                   sIDot;                          /* ELEMENT idot, INTEGER (-8192..8191), BIT STRING(SIZE(14)) */
    VOS_UINT8                                   aucReserved11[2];
}AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU;

/*******************************************************************************
 结构名    : AGPS_RRC_EPHEM_CLOCK_PARAM_STRU
 结构说明  : UE positioning GPS Ephemeris and Clock Correction parameters
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体命名，该结构体参数为无符号类型，目前WAS专用
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucCodeOnL2;                     /* ELEMENT l2_code, BIT STRING(SIZE(2)) */
    VOS_UINT8                                   ucUraIndex;                     /* ELEMENT ura, BIT STRING(SIZE(4)) */
    VOS_UINT8                                   ucSatHealth;                    /* ELEMENT sv_health, BIT STRING(SIZE(6)) */
    VOS_UINT8                                   aucReserved1[1];
    VOS_UINT16                                  usIodc;                         /* ELEMENT iodc, BIT STRING(SIZE(10)) */
    VOS_UINT8                                   ucL2PFlag;                      /* ELEMENT l2p_flag, BIT STRING(SIZE(1)) */
    VOS_UINT8                                   aucReserved2[1];
    VOS_UINT32                                  ulReserved1;                    /* ELEMENT esr1 */
    VOS_UINT32                                  ulReserved2;                    /* ELEMENT esr2 */
    VOS_UINT32                                  ulReserved3;                    /* ELEMENT esr3 */
    VOS_UINT16                                  usReserved4;                    /* ELEMENT esr4 */
    VOS_UINT8                                   ucTGd;                          /* ELEMENT tgd, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved3[1];
    VOS_UINT16                                  usTOc;                          /* ELEMENT toc, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   ucAf2;                          /* ELEMENT af2, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved4[1];
    VOS_UINT16                                  usAf1;                          /* ELEMENT af1, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved5[2];
    VOS_UINT32                                  ulAf0;                          /* ELEMENT af0, BIT STRING(SIZE(22)) */
    VOS_UINT16                                  usCRs;                          /* ELEMENT crs, BIT STRING(SIZE(16)) */
    VOS_UINT16                                  usDeltaN;                       /* ELEMENT delta_n, BIT STRING(SIZE(16)) */
    VOS_UINT32                                  ulM0;                           /* ELEMENT m0, BIT STRING(SIZE(32)) */
    VOS_UINT16                                  usCUc;                          /* ELEMENT cuc, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved6[2];
    VOS_UINT32                                  ulEcc;                          /* ELEMENT ecc, BIT STRING(SIZE(32)) */
    VOS_UINT16                                  usCUs;                          /* ELEMENT cus, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved7[2];
    VOS_UINT32                                  ulPowerHalf;                    /* ELEMENT power_half, BIT STRING(SIZE(32)) */
    VOS_UINT16                                  usTOe;                          /* ELEMENT toe, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   ucFitFlag;                      /* ELEMENT fit_flag, BIT STRING(SIZE(1)) */
    VOS_UINT8                                   ucAodo;                         /* ELEMENT aoda, BIT STRING(SIZE(5)) */
    VOS_UINT16                                  usCIc;                          /* ELEMENT cic, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved8[2];
    VOS_UINT32                                  ulOmega0;                       /* ELEMENT omega0, BIT STRING(SIZE(32)) */
    VOS_UINT16                                  usCIs;                          /* ELEMENT cis, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved9[2];
    VOS_UINT32                                  ulI0;                           /* ELEMENT i0, BIT STRING(SIZE(32)) */
    VOS_UINT16                                  usCRc;                          /* ELEMENT crc, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved10[2];
    VOS_UINT32                                  ulOmega;                        /* ELEMENT omega, BIT STRING(SIZE(32)) */
    VOS_UINT32                                  ulOmegaDot;                     /* ELEMENT omega_dot, BIT STRING(SIZE(24)) */
    VOS_UINT16                                  usIDot;                         /* ELEMENT idot, BIT STRING(SIZE(14)) */
    VOS_UINT8                                   aucReserved11[2];
}AGPS_RRC_EPHEM_CLOCK_PARAM_STRU;


/*******************************************************************************
 结构名    : AGPS_NAV_MODEL_ELEM_STRU
 结构说明  : UE positioning GPS navigation model
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，需要区分哪个接入层给的数据
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitEphemClock:1;
    VOS_UINT32                                  bitOpSpare:31;

    VOS_UINT8                                   ucSatId;                        /* ELEMENT sat_id, INTEGER(0..63) */
    AGPS_POS_SAT_STA_ENUM_UINT8                 enSatSta;                       /* ATTLIST sat_status, ENUMERATED */

    VOS_UINT8                                   aucReserved[1];

    AGPS_EPHEM_CLOCK_TYPE_ENUM_UINT8            enChoice;
    union
    {
        AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU        stRrlpEphemClock;               /* ELEMENT ephem_and_clock */
        AGPS_RRC_EPHEM_CLOCK_PARAM_STRU         stRrcEphemClock;                /* ELEMENT ephem_and_clock */
    } u;
}AGPS_NAV_MODEL_ELEM_STRU;

/*******************************************************************************
 结构名    : AGPS_NAV_MODEL_ELEM_LIST_STRU
 结构说明  : UE positioning GPS navigation model
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulNavModelElemNum;
    AGPS_NAV_MODEL_ELEM_STRU                    astNavModelElem[AGPS_MAX_SAT_NUM];
}AGPS_NAV_MODEL_ELEM_LIST_STRU;

/*******************************************************************************
 结构名    : AGPS_RRLP_IONOSPHERIC_MODEL_STRU
 结构说明  : UE positioning GPS ionospheric model中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，GAS提供的数据是有符号数
*******************************************************************************/
typedef struct
{
    VOS_INT8                                    cAlpha0;                        /* ELEMENT alfa0, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cAlpha1;                        /* ELEMENT alfa1, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cAlpha2;                        /* ELEMENT alfa2, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cAlpha3;                        /* ELEMENT alfa3, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cBeta0;                         /* ELEMENT beta0, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cBeta1;                         /* ELEMENT beta1, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cBeta2;                         /* ELEMENT beta2, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cBeta3;                         /* ELEMENT beta3, INTEGER (-128..127),BIT STRING(SIZE(8)) */
}AGPS_RRLP_IONOSPHERIC_MODEL_STRU;

/*******************************************************************************
 结构名    : AGPS_RRC_IONOSPHERIC_MODEL_STRU
 结构说明  : UE positioning GPS ionospheric model中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，WAS提供的数据是无符号数
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucAlpha0;                       /* ELEMENT alfa0, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucAlpha1;                       /* ELEMENT alfa1, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucAlpha2;                       /* ELEMENT alfa2, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucAlpha3;                       /* ELEMENT alfa3, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucBeta0;                        /* ELEMENT beta0, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucBeta1;                        /* ELEMENT beta1, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucBeta2;                        /* ELEMENT beta2, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucBeta3;                        /* ELEMENT beta3, BIT STRING(SIZE(8)) */
}AGPS_RRC_IONOSPHERIC_MODEL_STRU;

/*******************************************************************************
 结构名    : AGPS_RRLP_UTC_MODEL_STRU
 结构说明  : UE positioning GPS UTC model中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，GAS提供的数据是有符号数
*******************************************************************************/
typedef struct
{
    VOS_INT32                                   lA1;                            /* ELEMENT a1, INTEGER (-8388608..8388607),BIT STRING(SIZE(24)) */
    VOS_INT32                                   lA0;                            /* ELEMENT a0, INTEGER (-2147483648..2147483647),BIT STRING(SIZE(32)) */
    VOS_UINT8                                   ucTOt;                          /* ELEMENT tot, INTEGER (0..255),BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucWnT;                          /* ELEMENT wnt, INTEGER (0..255),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cDeltaTLs;                      /* ELEMENT dtls, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucWnLsf;                        /* ELEMENT wnlsf, INTEGER (0..255),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cDn;                            /* ELEMENT dn, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_INT8                                    cDeltaTLsf;                     /* ELEMENT dtlsf, INTEGER (-128..127),BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved[2];                 /* 保留位 */
}AGPS_RRLP_UTC_MODEL_STRU;

/*******************************************************************************
 结构名    : AGPS_RRC_UTC_MODEL_STRU
 结构说明  : UE positioning GPS UTC model中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，WAS提供的数据是无符号数
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulA1;                           /* ELEMENT a1, BIT STRING(SIZE(24)) */
    VOS_UINT32                                  ulA0;                           /* ELEMENT a0, BIT STRING(SIZE(32)) */
    VOS_UINT8                                   ucTOt;                          /* ELEMENT tot, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucWnT;                          /* ELEMENT wnt, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucDeltaTLs;                     /* ELEMENT dtls, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucWnLsf;                        /* ELEMENT wnlsf, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucDn;                           /* ELEMENT dn, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   ucDeltaTLsf;                    /* ELEMENT dtlsf, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved[2];                 /* 保留位 */
}AGPS_RRC_UTC_MODEL_STRU;

/*******************************************************************************
 结构名    : AGPS_RRLP_ALMANAC_SAT_INFO_STRU
 结构说明  : UE positioning GPS almanac中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，GAS提供的数据是有符号数
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpDataId  :1;
    VOS_UINT32                                  bitOpSpare   :31;

    VOS_UINT8                                   ucDataId;                       /* ELEMENT data_id, INTEGER(0..3) */
    VOS_UINT8                                   ucSatId;                        /* ELEMENT sat_id, INTEGER(0..63) */
    VOS_UINT16                                  usAlmEcc;                       /* ELEMENT alm_ecc, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved1[1];
    VOS_UINT8                                   ucAlmToa;                       /* ELEMENT alm_toa, BIT STRING(SIZE(8)) */
    VOS_INT16                                   sAlmKsii;                       /* ELEMENT alm_ksii, INTEGER (-32768..32767),usDeltaI, BIT STRING(SIZE(16)) */
    VOS_INT16                                   sAlmOmegaDot;                   /* ELEMENT alm_omega_dot, INTEGER (-32768..32767),BIT STRING(SIZE(16)) */
    VOS_UINT8                                   ucAlmSvHealth;                  /* ELEMENT alm_sv_health, INTEGER (0..255),ucSatHealth, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved2[1];
    VOS_UINT32                                  ulAlmPowerHalf;                 /* ELEMENT alm_power_half, INTEGER (0..16777215),ulASqrt, BIT STRING(SIZE(24)) */
    VOS_INT32                                   lAlmOmega0;                     /* ELEMENT alm_omega0, INTEGER (-8388608..8388607),BIT STRING(SIZE(24)) */
    VOS_INT32                                   lAlmOmega;                      /* ELEMENT alm_omega, INTEGER (-8388608..8388607),BIT STRING(SIZE(24)) */
    VOS_INT32                                   lAlmM0;                         /* ELEMENT alm_m0, INTEGER (-8388608..8388607),BIT STRING(SIZE(24)) */
    VOS_INT16                                   sAlmAf0;                        /* ELEMENT valm_af0, INTEGER (-1024..1023),BIT STRING(SIZE(11)) */
    VOS_INT16                                   sAlmAf1;                        /* ELEMENT alm_af1, INTEGER (-1024..1023),BIT STRING(SIZE(11)) */
}AGPS_RRLP_ALMANAC_SAT_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_RRC_ALMANAC_SAT_INFO_STRU
 结构说明  : UE positioning GPS almanac中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，WAS提供的数据是无符号数
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpDataId  :1;
    VOS_UINT32                                  bitSpare    :31;

    VOS_UINT8                                   ucDataId;                       /* ELEMENT data_id, INTEGER(0..3) */
    VOS_UINT8                                   ucSatId;                        /* ELEMENT sat_id, INTEGER(0..63) */
    VOS_UINT16                                  usAlmEcc;                       /* ELEMENT alm_ecc, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   aucReserved1[1];
    VOS_UINT8                                   ucAlmToa;                       /* ELEMENT alm_toa, BIT STRING(SIZE(8)) */
    VOS_UINT16                                  usAlmKsii;                      /* ELEMENT alm_ksii, usDeltaI, BIT STRING(SIZE(16)) */
    VOS_UINT16                                  usAlmOmegaDot;                  /* ELEMENT alm_omega_dot, BIT STRING(SIZE(16)) */
    VOS_UINT8                                   ucAlmSvHealth;                  /* ELEMENT alm_sv_health?, ucSatHealth, BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved2[1];
    VOS_UINT32                                  ulAlmPowerHalf;                 /* ELEMENT alm_power_half, ulASqrt, BIT STRING(SIZE(24)) */
    VOS_UINT32                                  ulAlmOmega0;                    /* ELEMENT alm_omega0, BIT STRING(SIZE(24)) */
    VOS_UINT32                                  ulAlmOmega;                     /* ELEMENT alm_omega, BIT STRING(SIZE(24)) */
    VOS_UINT32                                  ulAlmM0;                        /* ELEMENT alm_m0, BIT STRING(SIZE(24)) */
    VOS_UINT16                                  usAlmAf0;                       /* ELEMENT valm_af0, BIT STRING(SIZE(11)) */
    VOS_UINT16                                  usAlmAf1;                       /* ELEMENT alm_af1, BIT STRING(SIZE(11)) */
}AGPS_RRC_ALMANAC_SAT_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_ALMANAC_SAT_INFO_LIST_STRU
 结构说明  : UE positioning GPS almanac中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，需要区分哪个接入层给的数据
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulAlmancSatNum;
    VOS_UINT8                                   aucReserved[3];

    AGPS_ALMANAC_SAT_INFO_TYPE_ENUM_UINT8       enAlmanacSatInfoChoice;
    union
    {
        AGPS_RRLP_ALMANAC_SAT_INFO_STRU         astRrlpAlmanacSatInfo[AGPS_MAX_SAT_NUM];    /* ELEMENT almanac */
        AGPS_RRC_ALMANAC_SAT_INFO_STRU          astRrcAlmanacSatInfo[AGPS_MAX_SAT_NUM];     /* ELEMENT almanac */
    } u;

}AGPS_ALMANAC_SAT_INFO_LIST_STRU;

/*******************************************************************************
 结构名    : AGPS_ALMANAC_STRU
 结构说明  : UE positioning GPS almanac中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，命名修正
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucWnA;                          /* ELEMENT wna, INTEGER (0..255),BIT STRING(SIZE(8)) */
    VOS_UINT8                                   aucReserved1[3];                /* 保留位 */
    AGPS_ALMANAC_SAT_INFO_LIST_STRU             stAlmanacSatInfoList;
}AGPS_ALMANAC_STRU;

/*******************************************************************************
 结构名    : AGPS_EXTRA_DOPPLER_INFO_STRU
 结构说明  : UE positioning GPS acquisition assistance中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucDoppler1stOrder;              /* INTEGER(0..63) */
    VOS_UINT8                                   aucReserved[2];
    AGPS_DOPPLER_UNCERTN_ENUM_UINT8             enDopplerUncertn;
}AGPS_EXTRA_DOPPLER_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_AZIMUTH_AND_ELEVA_STRU
 结构说明  : UE positioning GPS acquisition assistance中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucAzimuth;                      /* ELEMENT az, INTEGER(0..31) */
    VOS_UINT8                                   ucEleva;                        /* ELEMENT elev, INTEGER(0..7) */
    VOS_UINT8                                   aucReserved[2];
}AGPS_AZIMUTH_AND_ELEVA_STRU;

/*******************************************************************************
 结构名    : AGPS_ACQU_SAT_INFO_STRU
 结构说明  : UE positioning GPS acquisition assistance中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpExtraDopplerInfo  :1;
    VOS_UINT32                                  bitOpAzimuthAndEleva   :1;
    VOS_UINT32                                  bitSpare               :30;

    VOS_UINT8                                   ucSatId;                        /* ELEMENT sat_id, INTEGER(0..63) */
    VOS_UINT8                                   aucReserved1[1];
    VOS_INT16                                   sDopl0;                         /* ELEMENT dopl0, INTEGER (-2048..2047) */
    AGPS_EXTRA_DOPPLER_INFO_STRU                stExtraDopplerInfo;             /* ELEMENT dopl_extra, OPTIONAL */
    VOS_UINT16                                  usCodePhase;                    /* INTEGER(0..1022) */
    VOS_UINT8                                   ucIntCodePhase;                 /* INTEGER(0..19) */
    VOS_UINT8                                   ucGpsBitNum;                    /* INTEGER(0..3) */
    AGPS_CODE_PHASE_SEARCH_WIN_ENUM_UINT8       enCodePhaseSearchWin;           /* ENUMERATED */
    VOS_UINT8                                   aucReserved2[3];
    AGPS_AZIMUTH_AND_ELEVA_STRU                 stAzimuthAndEleva;              /* OPTIONAL */
}AGPS_ACQU_SAT_INFO_STRU;

/*******************************************************************************
 结构名    : AGPS_ACQU_SAT_INFO_LIST_STRU
 结构说明  : UE positioning GPS acquisition assistance中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulSatInfoNum;
    AGPS_ACQU_SAT_INFO_STRU                     astSatInfo[AGPS_MAX_SAT_NUM];
}AGPS_ACQU_SAT_INFO_LIST_STRU;

/*******************************************************************************
 结构名    : AGPS_ACQU_ASSIST_STRU
 结构说明  : UE positioning GPS acquisition assistance中的信元
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulTowMsec;                      /* ELEMENT tow_msec?, ulGpsRefTime, INTEGER(0..604799999) */
    AGPS_ACQU_SAT_INFO_LIST_STRU                stSatInfoList;
}AGPS_ACQU_ASSIST_STRU;

/*******************************************************************************
 结构名    : AGPS_BAD_SAT_LIST_STRU
 结构说明  : describe the real-time status of the GPS constellation
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulBadSatListBadSatListNum;
    VOS_UINT8                                   ausBadSatListBadSatList[AGPS_MAX_SAT_NUM];
}AGPS_BAD_SAT_LIST_STRU;

/*******************************************************************************
 结构名    : AGPS_GPS_ASSIST_STRU
 结构说明  : GPS辅助数据的内容
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
 2.日    期   : 2012年07月07日
   作    者   : h44270
   修改内容   : 修改结构体，需要区分哪个接入层给的数据
*******************************************************************************/
typedef struct
{
    VOS_UINT32                               bitOpStatusHealth         : 1;
    VOS_UINT32                               bitOpBtsClockDrift        : 1;
    VOS_UINT32                               bitOpRefTime              : 1;
    VOS_UINT32                               bitOpLocationPara         : 1;
    VOS_UINT32                               bitOpDgpsCorrection       : 1;
    VOS_UINT32                               bitOpNavModelElem         : 1;
    VOS_UINT32                               bitOpIonosphericModel     : 1;
    VOS_UINT32                               bitOpUtcModel             : 1;
    VOS_UINT32                               bitOpAlmanac              : 1;
    VOS_UINT32                               bitOpAcquAssist           : 1;
    VOS_UINT32                               bitOpGpsRealTimeIntegrity : 1;
    VOS_UINT32                               bitSpare                  : 21;

    AGPS_DIFF_CORRECT_STA_ENUM_UINT8         enStatusHealth;                    /* ELEMENT status_health */
    VOS_UINT8                                aucReserved1[1];
    VOS_UINT16                               usBtsClockDrift;                   /* ELEMENT BTS_clock_drift,BTS时钟偏移 */
    AGPS_REFERENCE_TIME_STRU                 stRefTime;                         /* ELEMENT ref_time */
    AGPS_LOCATION_PARA_STRU                  stLocationPara;
    AGPS_DGPS_CORRECTION_STRU                stDgpsCorrection;
    AGPS_NAV_MODEL_ELEM_LIST_STRU            stNavModelElem;

    VOS_UINT8                                aucReserved2[3];
    AGPS_IONOSPHERIC_MODEL_TYPE_ENUM_UINT8   enIonosphericModelChoice;
    union
    {
        AGPS_RRLP_IONOSPHERIC_MODEL_STRU     stRrlpIonosphericModel;            /* ELEMENT ionospheric_model */
        AGPS_RRC_IONOSPHERIC_MODEL_STRU      stRrcIonosphericModel;             /* ELEMENT ionospheric_model */
    } u1;

    VOS_UINT8                                aucReserved3[3];
    AGPS_UTC_MODEL_TYPE_ENUM_UINT8           enUtcModelChoice;
    union
    {
        AGPS_RRLP_UTC_MODEL_STRU             stRrlpUtcModel;                    /* ELEMENT UTC_model */
        AGPS_RRC_UTC_MODEL_STRU              stRrcUtcModel;                     /* ELEMENT UTC_model */
    } u2;

    AGPS_ALMANAC_STRU                        stAlmanac;
    AGPS_ACQU_ASSIST_STRU                    stAcquAssist;
    AGPS_BAD_SAT_LIST_STRU                   stGpsRealTimeIntegrity;
}AGPS_GPS_ASSIST_STRU;


/*******************************************************************************
 结构名    : AGPS_ASSIST_DATA_STRU
 结构说明  : 辅助数据的内容
 1.日    期   : 2012年06月01日
   作    者   : y00142674,l00128652,h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGpsAssist      : 1;
    VOS_UINT32                          bitSpare            : 31;

    AGPS_GPS_ASSIST_STRU                stGpsAssist;                            /* ELEMENT GPS_assist */
}AGPS_ASSIST_DATA_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of AgpsParaDef.h */


