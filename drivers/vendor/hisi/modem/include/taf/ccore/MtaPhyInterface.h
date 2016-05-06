/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtaPhyInterface.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年02月26日
  最近修改   :
  功能描述   : MTA与物理层之间的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年02月26日
    作    者   : l00198894
    修改内容   : 创建文件

 ******************************************************************************/

#ifndef __MTAPHYINTERFACE_H__
#define __MTAPHYINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafNvInterface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MTA_PHY_AFCLOCK_REPORT_DURATION     (500)

#define RCM_MTA_XO_COEF_NUM                 (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MTA_PHY_GPS_RF_CLOCK_STATE_ENUM
 结构说明  : RF芯片GPS时钟状态枚举
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*****************************************************************************/
enum MTA_PHY_GPS_RF_CLOCK_STATE_ENUM
{
    MTA_PHY_GPS_RF_CLOCK_STATE_RUNNING          = 0,
    MTA_PHY_GPS_RF_CLOCK_STATE_STOP,
    MTA_PHY_GPS_RF_CLOCK_STATE_BUTT
};
typedef VOS_UINT16 MTA_PHY_GPS_RF_CLOCK_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_BODY_SAR_STATE_ENUM
 结构说明  : Body SAR 状态枚举
 1.日    期   : 2013年02月27日
   作    者   : l00198894
   修改内容   : 新增枚举
*****************************************************************************/
enum MTA_BODY_SAR_STATE_ENUM
{
    MTA_BODY_SAR_OFF                    = 0,                                    /* Body SAR功能关闭 */
    MTA_BODY_SAR_ON,                                                            /* Body SAR功能开启 */
    MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 MTA_BODY_SAR_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_PHY_RESULT_ENUM
 结构说明  : MTA与物理层错误码枚举
 1.日    期   : 2013年02月27日
   作    者   : l00198894
   修改内容   : 新增枚举
*****************************************************************************/
enum MTA_PHY_RESULT_ENUM
{
    MTA_PHY_RESULT_NO_ERROR             = 0,
    MTA_PHY_RESULT_ERROR,
    MTA_PHY_RESULT_PARA_ERROR,
    MTA_PHY_RESULT_BUTT
};
typedef VOS_UINT16 MTA_PHY_RESULT_ENUM_UINT16;

/*****************************************************************************
 结构名    : MTA_PHY_EMERGENCY_CALL_STATUS_ENUM
 结构说明  : 紧急呼叫状态枚举
 1.日    期   : 2013年04月09日
   作    者   : z00214637
   修改内容   : 新增
*****************************************************************************/
enum MTA_PHY_EMERGENCY_CALL_STATUS_ENUM
{
    MTA_PHY_EMERGENCY_CALL_END  = 0,                                            /* 紧急呼叫结束 */
    MTA_PHY_EMERGENCY_CALL_START,                                               /* 紧急呼叫发起 */
    MTA_PHY_EMERGENCY_CALL_STATUS_BUTT
};
typedef VOS_UINT16 MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHY_MTA_REFCLOCK_STATUS_ENUM
 枚举说明  : GPS参考时钟锁定状态枚举

  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
enum PHY_MTA_REFCLOCK_STATUS_ENUM
{
    PHY_MTA_REFCLOCK_UNLOCKED           = 0,                                    /* GPS参考时钟频率非锁定状态 */
    PHY_MTA_REFCLOCK_LOCKED,                                                    /* GPS参考时钟频率锁定状态 */
    PHY_MTA_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHY_MTA_GPHY_XPASS_MODE_ENUM
 枚举说明  : G XPASS模式

  1.日    期   : 2014年12月18日
    作    者   : w00286360
    修改内容   : seattle
*****************************************************************************/
enum PHY_MTA_GPHY_XPASS_MODE_ENUM
{
    PHY_MTA_GPHY_XPASS_MODE_DISABLE     = 0,                                    /* 非XPASS模式，类似高铁 */
    PHY_MTA_GPHY_XPASS_MODE_ENABLE         ,                                    /* XPASS模式，类似高铁 */
    PHY_MTA_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 PHY_MTA_GPHY_XPASS_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHY_MTA_WPHY_HIGHWAY_MODE_ENUM
 枚举说明  : W高铁模式

  1.日    期   : 2014年12月18日
    作    者   : w00286360
    修改内容   : seattle
*****************************************************************************/
enum PHY_MTA_WPHY_HIGHWAY_MODE_ENUM
{
    PHY_MTA_WPHY_HIGHWAY_MODE_DISABLE     = 0,                                  /* W非高铁模式 */
    PHY_MTA_WPHY_HIGHWAY_MODE_ENABLE         ,                                  /* W高铁模式 */
    PHY_MTA_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 PHY_MTA_WPHY_HIGHWAY_MODE_ENUM_UINT16;

#if 0
#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 枚举名    : MTA_LPHY_COEX_BW_TYPE_ENUM
 枚举说明  : LTE&WIFI宽带类型枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MTA_LPHY_COEX_BW_TYPE_ENUM
{
    MTA_LPHY_COEX_BAND_WIDTH_6RB        = 0,                                    /* 宽带1.4M */
    MTA_LPHY_COEX_BAND_WIDTH_15RB       = 1,                                    /* 宽带3M */
    MTA_LPHY_COEX_BAND_WIDTH_25RB       = 2,                                    /* 宽带5M */
    MTA_LPHY_COEX_BAND_WIDTH_50RB       = 3,                                    /* 宽带10M */
    MTA_LPHY_COEX_BAND_WIDTH_75RB       = 4,                                    /* 宽带15M */
    MTA_LPHY_COEX_BAND_WIDTH_100RB      = 5,                                    /* 宽带20M */
    MTA_LPHY_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 MTA_LPHY_COEX_BW_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_LPHY_COEX_CFG_ENUM
 枚举说明  : LTE&WIFI共存方案配置枚举

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
enum MTA_LPHY_COEX_CFG_ENUM
{
    MTA_LPHY_COEX_CFG_DISABLE           = 0,
    MTA_LPHY_COEX_CFG_ENABLE            = 1,
    MTA_LPHY_COEX_CFG_BUTT
};
typedef VOS_UINT16 MTA_LPHY_COEX_CFG_ENUM_UINT16;
#endif
#endif

/*****************************************************************************
 枚举名    : PHY_MTA_AFC_CLK_STATUS_ENUM
 枚举说明  : AFC时钟锁定状态枚举

  1.日    期   : 2015年9月7日
    作    者   : l00198894
    修改内容   : 新增枚举
*****************************************************************************/
enum PHY_MTA_AFC_CLK_STATUS_ENUM
{
    PHY_MTA_AFC_CLK_UNLOCKED           = 0,                                     /* AFC时钟频率非锁定状态 */
    PHY_MTA_AFC_CLK_LOCKED,                                                     /* AFC时钟频率锁定状态 */

    PHY_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT16 PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/
#define MTA_PHY_MSG_HEADER      VOS_MSG_HEADER \
                                VOS_UINT16  usMsgID; \
                                VOS_UINT16  usReserved0;

/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MTA_PHY_MSG_TYPE_ENUM
 结构说明  : 原语的usMsgID
 1.日    期   : 2013年02月27日
   作    者   : l00198894
   修改内容   : 新增枚举
*****************************************************************************/
enum MTA_PHY_MSG_TYPE_ENUM
{
    /* 消息名称 */                              /* 消息ID */                    /* 备注 */
    /* 与物理层APM间的消息 */
    ID_MTA_APM_BODY_SAR_SET_REQ                 = 0xD202,                       /* _H2ASN_MsgChoice MTA_APM_BODY_SAR_SET_REQ_STRU */
    ID_MTA_APM_EMERGENCY_CALL_STATUS_NOTIFY     = 0xD203,                       /* _H2ASN_MsgChoice MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU */
    ID_APM_MTA_BODY_SAR_SET_CNF                 = 0xD220,                       /* _H2ASN_MsgChoice APM_MTA_BODY_SAR_SET_CNF_STRU */
    ID_APM_MTA_REFCLOCK_STATUS_IND              = 0xD221,                       /* _H2ASN_MsgChoice APM_MTA_REFCLOCK_STATUS_IND_STRU */

    ID_MTA_APM_HANDLE_DETECT_SET_REQ            = 0xD222,                       /* _H2ASN_MsgChoice MTA_APM_HANDLE_DETECT_SET_REQ_STRU */
    ID_APM_MTA_HANDLE_DETECT_SET_CNF            = 0xD223,                       /* _H2ASN_MsgChoice APM_MTA_HANDLE_DETECT_SET_CNF_STRU */
    ID_MTA_APM_HANDLE_DETECT_QRY_REQ            = 0xD224,                       /* _H2ASN_MsgChoice MTA_APM_HANDLE_DETECT_QRY_REQ_STRU */
    ID_APM_MTA_HANDLE_DETECT_QRY_CNF            = 0xD225,                       /* _H2ASN_MsgChoice APM_MTA_HANDLE_DETECT_QRY_CNF_STRU */

    /* 与G, W物理层APM间的消息 */
    ID_MTA_APM_GET_PHY_CHR_INFO_REQ             = 0xD226,                       /* _H2ASN_MsgChoice MTA_APM_GET_PHY_CHR_INFO_REQ_STRU */
    ID_APM_MTA_GET_PHY_CHR_INFO_CNF             = 0xD227,                       /* _H2ASN_MsgChoice APM_MTA_GET_PHY_CHR_INFO_CNF_STRU */

    /* 与T, L物理层间的消息 */
    ID_MTA_TLPHY_GET_PHY_CHR_INFO_REQ           = 0xD228,                       /* _H2ASN_MsgChoice MTA_TLPHY_GET_PHY_CHR_INFO_REQ_STRU */
    ID_TLPHY_MTA_GET_PHY_CHR_INFO_CNF           = 0xD229,                       /* _H2ASN_MsgChoice TLPHY_MTA_GET_PHY_CHR_INFO_CNF_STRU */
    ID_AGENT_MTA_RFIC_SSI_RD_IND                = 0xD22A,                       /* _H2ASN_MsgChoice APM_MTA_RFICSSIRD_IND_STRU */

    /* 与G物理层间的消息 */
    ID_MTA_GPHY_SET_GPS_RF_CLOCK_REQ            = 0x3401,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU */
    ID_MTA_GPHY_GET_TX_PWR_REQ                  = 0x3402,                       /* _H2ASN_MsgChoice MTA_GPHY_GET_TX_PWR_REQ_STRU */

    ID_GPHY_MTA_SET_GPS_RF_CLOCK_CNF            = 0x4301,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU */
    ID_GPHY_MTA_GET_TX_PWR_CNF                  = 0x4302,                       /* _H2ASN_MsgChoice GPHY_MTA_GET_TX_PWR_CNF_STRU */

    /* 与W物理层间的消息 */
    ID_MTA_WPHY_SET_GPS_RF_CLOCK_REQ            = 0x5401,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU */

    /* 与UPHY间的消息 */
    ID_MTA_UPHY_START_UPHY_REQ                  = 0x6501,                       /* _H2ASN_MsgChoice MTA_UPHY_START_UPHY_REQ_STRU */
    ID_UPHY_MTA_START_UPHY_CNF                  = 0x5601,                       /* _H2ASN_MsgChoice UPHY_MTA_START_UPHY_CNF_STRU */


    /* 与G、W物理层间的消息 */
    ID_MTA_GUPHY_SET_DPDTTEST_FLAG_NTF          = 0x5402,                       /* _H2ASN_MsgChoice MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU */
    ID_MTA_GUPHY_SET_DPDT_VALUE_NTF             = 0x5403,                       /* _H2ASN_MsgChoice MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU */
    ID_MTA_GUPHY_QRY_DPDT_VALUE_REQ             = 0x5404,                       /* _H2ASN_MsgChoice MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU */
    ID_MTA_WPHY_GET_TX_PWR_REQ                  = 0x5405,                       /* _H2ASN_MsgChoice MTA_WPHY_GET_TX_PWR_REQ_STRU */
    ID_WPHY_MTA_SET_GPS_RF_CLOCK_CNF            = 0x4501,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU */
    ID_GUPHY_MTA_QRY_DPDT_VALUE_CNF             = 0x4502,                       /* _H2ASN_MsgChoice GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU */
    ID_WPHY_MTA_GET_TX_PWR_CNF                  = 0x4503,                       /* _H2ASN_MsgChoice WPHY_MTA_GET_TX_PWR_CNF_STRU */

    /* G\W的主动上报ID，ID从0x6500开始递增 */
    ID_GPHY_MTA_XPASS_INFO_IND                  = 0x7501,                       /* _H2ASN_MsgChoice GPHY_MTA_XPASS_INFO_IND_STRU */
    ID_WPHY_MTA_XPASS_INFO_IND                  = 0x7502,                       /* _H2ASN_MsgChoice WPHY_MTA_XPASS_INFO_IND_STRU */


#if 0
#if(FEATURE_ON == FEATURE_LTE)
    ID_MTA_LPHY_LTE_WIFI_COEX_SET_REQ           = 0x7503,                       /* _H2ASN_MsgChoice MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU */
    ID_LPHY_MTA_LTE_WIFI_COEX_SET_CNF           = 0x7504,                       /* _H2ASN_MsgChoice LPHY_MTA_LTE_WIFI_COEX_SET_REQ_STRU */
#endif
#endif

    /* 与TLPHY间的消息 */
    ID_MTA_AGENT_AFCLOCK_STATUS_RPT_NTF         = 0x7503,                       /* _H2ASN_MsgChoice MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU */

    /* 与TLPHY间的消息 */
    ID_MTA_AGENT_RFIC_SSI_RD_NTF                = 0x7505,                       /* _H2ASN_MsgChoice MTA_AGENT_RFICSSIRD_REQ_STRU */
	
    /* CDMA与物理层的消息 */
    ID_MTA_CTAS_SET_DPDTTEST_FLAG_NTF           = 0x8400,                       /* _H2ASN_MsgChoice MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU */
    ID_MTA_CTAS_SET_DPDT_VALUE_NTF              = 0x8401,                       /* _H2ASN_MsgChoice MTA_CTAS_SET_DPDT_VALUE_NTF_STRU */
    ID_MTA_CTAS_QRY_DPDT_VALUE_REQ              = 0x8402,                       /* _H2ASN_MsgChoice MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU */
    ID_CTAS_MTA_QRY_DPDT_VALUE_CNF              = 0x8500,                       /* _H2ASN_MsgChoice CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU */

    ID_MTA_RCM_AFC_CLK_INFO_QRY_REQ             = 0x7D01,                       /* _H2ASN_MsgChoice MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU */
    ID_RCM_MTA_AFC_CLK_INFO_QRY_CNF             = 0x7D02,                       /* _H2ASN_MsgChoice RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU */

    ID_MTA_PHY_MSG_TYPE_BUTT
};
typedef VOS_UINT16 MTA_PHY_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
枚举名    : MTA_UPHY_INIT_STATUS_ENUM
结构说明  : UPHY初始化状态的枚举

  1.日    期   : 2014年02月14日
    作    者   : h00246512
    修改内容   : DSDS项目新增接口
*****************************************************************************/
enum MTA_UPHY_INIT_STATUS_ENUM
{
    MTA_UPHY_INIT_STATUS_SUCCESS,
    MTA_UPHY_INIT_STATUS_FAIL,
    MTA_UPHY_INIT_STATUS_BUTT
};
typedef VOS_UINT16  MTA_UPHY_INIT_STATUS_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*******************************************************************************
 结构名    : MTA_PHY_MSG_HEADER_STRU
 结构说明  : 消息头
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
}MTA_PHY_MSG_HEADER_STRU;



/*******************************************************************************
 结构名    : NAS_PHY_COM_INIT_REQ_STRU
 结构说明  : 请求物理层开启上电初始化
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/

    VOS_UINT32                                  ulSlice;            /* 请求的时间点 */
}NAS_PHY_COM_INIT_REQ_STRU;


/*******************************************************************************
 结构名    : PHY_NAS_COM_INIT_CNF_STRU
 结构说明  : 物理层上电初始化成功
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulSlice;            /* 请求的时间点 */
}PHY_NAS_COM_INIT_CNF_STRU;


/*******************************************************************************
 结构名    : MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU
 结构说明  : 请求物理层开启或关闭RF芯片上的GPS时钟
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/

    MTA_PHY_GPS_RF_CLOCK_STATE_ENUM_UINT16      enGpsClockState;    /* RF芯片GPS时钟状态 */
    VOS_UINT16                                  ausReserved1[1];    /* 保留位 */
}MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU;

/*******************************************************************************
 结构名    : MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU
 结构说明  : 物理层开启或关闭RF芯片上的GPS时钟结果回复
 1.日    期   : 2012年06月25日
   作    者   : h44270
   修改内容   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/

    MTA_PHY_RESULT_ENUM_UINT16                  enResultType;       /* 结果信息类型 */
    VOS_UINT16                                  ausReserved1[1];    /* 保留位 */

}MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU;

/*******************************************************************************
 结构名    : MTA_GPHY_GET_TX_PWR_REQ_STRU
 结构说明  : 查询G物理层发射功率请求
 1.日    期   : 2015年07月2日
   作    者   : w00286360
   修改内容   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
}MTA_GPHY_GET_TX_PWR_REQ_STRU;

/*******************************************************************************
 结构名    : GPHY_MTA_GET_TX_PWR_CNF_STRU
 结构说明  : 查询G物理层发射功率CNF
 1.日    期   : 2015年07月2日
   作    者   : w00286360
   修改内容   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16                  enResult;           /* 操作结果 */
    VOS_INT16                                   sTxPwr;             /* 发射功率，0.1dBm精度 */
}GPHY_MTA_GET_TX_PWR_CNF_STRU;

/*******************************************************************************
 结构名    : MTA_WPHY_GET_TX_PWR_REQ_STRU
 结构说明  : 查询W物理层发射功率请求
 1.日    期   : 2015年07月2日
   作    者   : w00286360
   修改内容   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
}MTA_WPHY_GET_TX_PWR_REQ_STRU;

/*******************************************************************************
 结构名    : WPHY_MTA_GET_TX_PWR_CNF_STRU
 结构说明  : 查询W物理层发射功率CNF
 1.日    期   : 2015年07月2日
   作    者   : w00286360
   修改内容   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16                  enResult;           /* 操作结果 */
    VOS_INT16                                   sTxPwr;             /* 发射功率，0.1dBm精度 */
}WPHY_MTA_GET_TX_PWR_CNF_STRU;


/*******************************************************************************
 结构名    : MTA_APM_BODY_SAR_SET_REQ_STRU
 结构说明  : 设置Body SAR开启关闭状态及功率门限参数结构体
 1.日    期   : 2013年02月27日
   作    者   : l00198894
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_BODY_SAR_STATE_ENUM_UINT16      enState;                    /* Body SAR状态 */
    VOS_UINT16                          ausReserved1[1];            /* 保留位 */
    MTA_BODY_SAR_PARA_STRU              stBodySARPara;              /* Body SAR功率门限参数 */
}MTA_APM_BODY_SAR_SET_REQ_STRU;

/*******************************************************************************
 结构名    : APM_MTA_BODY_SAR_SET_CNF_STRU
 结构说明  : 回复Body SAR设置操作结果结构体
 1.日    期   : 2013年02月27日
   作    者   : l00198894
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16          enResult;                   /* 操作结果 */
    VOS_UINT16                          ausReserved1[1];            /* 保留位 */
}APM_MTA_BODY_SAR_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_PHY_EMERGENCY_CALL_STATUS_NTF
 结构说明  : 通知PHY紧急呼叫状态结构
 1.日    期  : 2013年03月28日
   作    者  : z00214637
   修改内容  : 新建结构体
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                              /*_H2ASN_Skip*/
    MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16           enEmergencyCallStatus;      /* 紧急呼状态 */
    VOS_UINT16                                          ausReserved1[1];            /* 保留位 */
}MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU;

/*******************************************************************************
 结构名    : APM_MTA_REFCLOCK_STATUS_IND_STRU
 结构说明  : 物理层APM主动上报GPS参考时钟锁定状态结构体
 1.日    期   : 2013年02月27日
   作    者   : l00198894
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16 enStatus;                               /* 时钟频率锁定状态 */
    VOS_UINT16                          ausReserved1[1];                        /* 保留位 */
} APM_MTA_REFCLOCK_STATUS_IND_STRU;

/*******************************************************************************
 结构名    : APM_MTA_RFICSSIRD_IND_STRU
 结构说明  : 物理层APM上报rfic寄存器值结构体
 1.日    期   : 2015年10月30日
   作    者   : x00316382
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulRegValue;                             /* 寄存器的值 */
} APM_MTA_RFICSSIRD_IND_STRU;

/*******************************************************************************
 结构名    : MTA_APM_HANDLE_DETECT_SET_REQ_STRU
 结构说明  : 设置左右手操作的结构体
 1.日    期   : 2013年08月06日
   作    者   : f00179208
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          usHandle;                               /* 左右手类型 */
    VOS_UINT16                          ausReserved1[1];                        /* 保留位 */
}MTA_APM_HANDLE_DETECT_SET_REQ_STRU;

/*******************************************************************************
 结构名    : APM_MTA_HANDLE_DETECT_SET_CNF_STRU
 结构说明  : 回复左右手设置操作结果结构体
 1.日    期   : 2013年08月06日
   作    者   : f00179208
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16          enResult;                               /* 操作结果 */
    VOS_UINT16                          ausReserved1[1];                        /* 保留位 */
}APM_MTA_HANDLE_DETECT_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_APM_HANDLE_DETECT_QRY_REQ_STRU
 结构说明  : 左右手操作查询消息结构
 1.日    期   : 2013年08月06日
   作    者   : f00179208
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved1[2];                        /* 保留位 */
} MTA_APM_HANDLE_DETECT_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : APM_MTA_HANDLE_DETECT_QRY_CNF_STRU
 结构说明  : 左右手操作查询回复消息结构
 1.日    期   : 2013年08月06日
   作    者   : f00179208
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          usHandle;                               /* 左右手类型 */
    MTA_PHY_RESULT_ENUM_UINT16          enResult;                               /* 操作结果 */
} APM_MTA_HANDLE_DETECT_QRY_CNF_STRU;


/*******************************************************************************
结构名    : MTA_UPHY_START_UPHY_REQ_STRU
结构说明  : ID_MTA_UPHY_START_UPHY_REQ_的消息结构
1.日    期   : 2014年1月5日
  作    者   : z00161729
  修改内容   : 新建
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved1[2];                         /*保留位*/
} MTA_UPHY_START_UPHY_REQ_STRU;

/*******************************************************************************
结构名    : MTA_UPHY_INIT_STATUS_IND_STRU
结构说明  : ID_MTA_UPHY_INIT_STATUS_IND的消息结构
1.日    期   : 2014年1月5日
  作    者   : z00161729
  修改内容   : 新建
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_UPHY_INIT_STATUS_ENUM_UINT16     enInitStatus;                          /* 物理层初始化状态 */
    VOS_UINT16                           ausReserved1[1];                       /*保留位*/
} UPHY_MTA_START_UPHY_CNF_STRU;


/*****************************************************************************
结构名    : MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU
结构说明  : 设置天线算法打开、关闭消息结构

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          usDpdtTest;
    VOS_UINT16                          ausReserved1[1];
} MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU;

/*****************************************************************************
结构名    : MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU
结构说明  : 设置天线当前DPDT Value值的消息结构

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU;

/*****************************************************************************
结构名    : MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU
结构说明  : 查询当前天线状态消息结构

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved1[2];
} MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
结构名    : GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU
结构说明  : 查询响应结果，显示当前天线DPDT值

  1.日    期  : 2014年04月01日
    作    者  : g00261581
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
结构名    : GPHY_MTA_XPASS_INFO_IND_STRU
结构说明  : GPHY上报XPASS相关的信息

  1.日    期  : 2014年12月19日
    作    者  : w00286360
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    PHY_MTA_GPHY_XPASS_MODE_ENUM_UINT16 enXpassMode;                            /* G xpass模式 */
    VOS_UINT16                          usReserved;
} GPHY_MTA_XPASS_INFO_IND_STRU;

/*****************************************************************************
结构名    : WPHY_MTA_XPASS_INFO_IND_STRU
结构说明  : WPHY上报XPASS相关的信息

  1.日    期  : 2014年12月19日
    作    者  : w00286360
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    PHY_MTA_WPHY_HIGHWAY_MODE_ENUM_UINT16   enHighwayMode;                      /* W高铁模式 */
    VOS_UINT16                              usReserved;
} WPHY_MTA_XPASS_INFO_IND_STRU;

#if 0
#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
结构名    : MTA_LPHY_COEX_PARA_STRU
结构说明  : LTE&WIFI共存参数结构体

  1.日    期  : 2015年5月22日
    作    者  : w00316404
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_LPHY_COEX_BW_TYPE_ENUM_UINT16       enCoexBWType;
    MTA_LPHY_COEX_CFG_ENUM_UINT16           enCfg;
    VOS_UINT16                              usTxBegin;
    VOS_UINT16                              usTxEnd;
    VOS_INT16                               sTxPower;
    VOS_UINT16                              usRxBegin;
    VOS_UINT16                              usRxEnd;
    VOS_UINT16                              usReserved;                         /* 保留位 */
} MTA_LPHY_COEX_PARA_STRU;

/*****************************************************************************
结构名    : MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU
结构说明  : MTA通知LPHY设置LTE&WIFI共存配置请求结构体

  1.日    期  : 2015年5月22日
    作    者  : w00316404
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usCoexParaNum;
    VOS_UINT16                              usCoexParaSize;
    VOS_UINT8                               aucCoexPara[4];
} MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
结构名    : LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU
结构说明  : LPHY回复MTA LTE&WIFI共存配置设置结果结构体

  1.日    期  : 2015年5月22日
    作    者  : w00316404
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16              enResult;                           /* 设置结果 */
    VOS_UINT16                              usReserved;                         /* 保留位 */
} LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU;
#endif
#endif

/*****************************************************************************
结构名    : TLPHY_MTA_AFCLOCK_AFCSTATUS_IND_STRU
结构说明  : TLPHY_PID_RTTAGENT上报到UEPS_PID_MTA的锁定状态消息结构体

  1.日    期  : 2015年06月17日
    作    者  : zwx247453
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usStatus;                           /* AFC锁定状态: 0, 失锁; 1, 锁定 */
    VOS_UINT16                              ausReserved1[1];
} TLPHY_MTA_AFCLOCK_AFCSTATUS_IND_STRU;

/*****************************************************************************
结构名    : MTA_AGENT_AFCLOCK_AFCSTATUS_NIF_STRU
结构说明  : UEPS_PID_MTA发送到TLPHY_PID_RTTAGENT的AFC锁定状态NTF消息结构体

  1.日    期  : 2015年06月17日
    作    者  : zwx247453
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usReportCtrolflag;                  /* 0:停止上报，1:启动上报 */
    VOS_UINT16                              usReportCount;                      /* 上报次数，若是0xffff则无限上报 */
    VOS_UINT16                              usReportDuration;                   /* 上报间隔，以ms为单位，粒度为10ms整数倍。上报次数大于1时有效 */
    VOS_UINT16                              ausReserved1[1];
} MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU;

/*****************************************************************************
结构名    : MTA_AGENT_RFICSSIRD_REQ_STRU
结构说明  : MTA发送到TLPHY_PID_RTTAGENT的RFICRD消息结构体

  1.日    期  : 2015年10月29日
    作    者  : x0016382
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usChannelNo;                        /* rfic通道 */
    VOS_UINT16                              usRficReg;                          /* 寄存器地址 */
} MTA_AGENT_RFICSSIRD_REQ_STRU;

/*****************************************************************************
结构名    : MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU
结构说明  : 设置天线算法打开、关闭消息结构

 1.日    期  : 2015年11月18日
   作    者  : h00313353
   创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usDpdtTest;
    VOS_UINT16                          usReserved;
} MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU;

/*****************************************************************************
结构名    : MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU
结构说明  : 查询当前天线状态消息结构

  1.日    期  : 2015年11月18日
    作    者  : h00313353
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved[2];
} MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
结构名    : MTA_CTAS_SET_DPDT_VALUE_NTF_STRU
结构说明  : 设置天线当前DPDT Value值

  1.日    期  : 2015年11月18日
    作    者  : h00313353
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} MTA_CTAS_SET_DPDT_VALUE_NTF_STRU;

/*****************************************************************************
结构名    : CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU
结构说明  : 查询响应结果，显示当前天线DPDT值

  1.日    期  : 2015年11月18日
    作    者  : h00313353
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 结构名    : MTA_PHY_CHR_INFO_QRY_REQ_STRU
 结构说明  : MTA发给PHY的TX Power查询请求

  1.日    期   : 2015年10月20日
    作    者   : 张义芳 z00328328
    修改内容   : 创建, for 上行发射功率收集
  2.日    期   : 2015年12月01日
    作    者   : 高亮亮 g00322017
    修改内容   : 修改, for 物理层信息收集
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER
    VOS_UINT16                              ausReserved1[2];                    /* 保留位 */
} MTA_PHY_CHR_INFO_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_MTA_PHY_INFO_QRY_CNF_STRU
 结构说明  : PHY发给MTA的TX Power查询结果

  1.日    期   : 2015年10月20日
    作    者   : 张义芳 z00328328
    修改内容   : 创建, for 上行发射功率收集
  2.日    期   : 2015年12月01日
    作    者   : 高亮亮 g00322017
    修改内容   : 修改, for 物理层信息收集

*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER
    VOS_UINT16                          usCellid;       /* 小区id */
    VOS_UINT16                          usDlFreqInfo;   /* 下行频率 */
    VOS_UINT16                          usUlFreqInfo;   /* 上行频率 */
    VOS_UINT16                          usBandInfo;     /* BAND */
    VOS_INT16                           sRxPower;       /* Rxlev(GSM), RSCP(UMTS,TDS),Rsrp(LTE) */
    VOS_INT16                           sChanelQuality; /* Rxqual(GSM), EcN0(UMTS), Scale(TDS),RsrQ(LTE) */
    VOS_INT32                           lTxPwr;         /* 上行发射功率, 0.1dBm精度 */
    VOS_UINT32                          ulSavedSlice;   /* 当前上报时间 */
}PHY_MTA_PHY_CHR_INFO_QRY_CNF_STRU;


/*****************************************************************************
结构名    : MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU
结构说明  : MTA向RCM查询AFC时钟频偏信息及XO温补系数请求结构体

  1.日    期  : 2015年9月7日
    作    者  : l00198894
    创建内容  : 新建
*****************************************************************************/
typedef MTA_UPHY_START_UPHY_REQ_STRU    MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU;

/*****************************************************************************
结构名    : RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU
结构说明  : RCM回复MTA查询AFC时钟频偏信息及XO温补系数结构体

  1.日    期  : 2015年9月7日
    作    者  : l00198894
    创建内容  : 新建
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16          enResult;
    
    PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus;
    VOS_INT32                           lDeviation;                             /* 频偏信息 */

    /* 温度范围 */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /* 多项式系数 */
    VOS_UINT32                          aulCoeffMantissa[RCM_MTA_XO_COEF_NUM];  /* a0,a1,a2,a3的尾数 */
    VOS_UINT16                          ausCoeffExponent[RCM_MTA_XO_COEF_NUM];  /* a0,a1,a2,a3的指数 */

} RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU;



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
    MTA_PHY_MSG_TYPE_ENUM_UINT16        enMsgId;                    /*_H2ASN_MsgChoice_Export MTA_PHY_MSG_TYPE_ENUM_UINT16*/
    VOS_UINT16                          usRsv;                      /* 保留位 */
    VOS_UINT16                          ausMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTA_PHY_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MTA_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MTA_PHY_MSG_DATA                    stMsgData;
}MtaPhyInterface_MSG;

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

#endif /* end of MtaPhyInterface.h */

