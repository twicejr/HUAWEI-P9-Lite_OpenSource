/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : AppMmInterface.h
  Description     : AppMmInterface.h header file
  History           :
     1 zhyiqiang:00138739      2008-08-30  Draft Enact
     2.sunbing 49683           2008-09-20  Modify
     3.sunbing 49683           2008-09-27  Modify
     4.lining 00141619         2008-10-29  合并MM
     5.sunbing 49683           2008-10-30  设置SM消息ID值和规范SM命名
     6.leili 00132387          2008-12-03  完善APP与MM的接口
     7.hanlufeng 41410         2009-03-11  BA8D01164 增加和APP的接口
     8.hanlufeng 41410         2009-05-12  BJ9D00722 增加和APP的接口
     9.xiaojun 58160           2009-05-19  BJ9D00828  AppMmInterface.h中关于路测
                               的公共定义移植到OmCommon.h中，利于各个模块公共使
                               用、维护
******************************************************************************/

#ifndef __APPMMINTERFACE_H__
#define __APPMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "AppNasComm.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define APP_MAX_PLMN_NUM                37
#define APP_MAX_UEID_BUF_SIZE           10
#define APP_MS_NET_CAP_MAX_SIZE         9
#define APP_MM_MAX_EQU_PLMN_NUM         16  /* 协议规定EPlmn最大个数*/
#define APP_MM_MAX_PLMN_NUM             64  /* PLMN列表最大个数 */
#define APP_MM_MAX_TA_NUM               64  /* TA 列表最大个数 */

#define APP_MM_CN_NAME_MAX_LEN         255          /* 网络名字的最大长度 */

/*niuxiufan DT begin */
#define APP_EMM_IMSI_MAX_LEN           15

/*niuxiufan DT end */


/*APP->MM 普通命令消息前3个字节宏定义 APP->MM*/
#define APP_MM_COMM_MSG_ID_HEADER                           PS_MSG_ID_APP_TO_EMM_BASE

/*MM->APP 普通命令消息前3个字节宏定义 MM->APP*/
#define MM_APP_COMM_MSG_ID_HEADER                           PS_MSG_ID_EMM_TO_APP_BASE


/*MM->APP 关键事件消息前3个字节宏定义 MM->APP*/
#define MM_APP_KEY_EVT_MSG_ID_HEADER                        PS_OMT_KEY_EVT_REPORT_IND

/*APP->MM 透明命令消息前3个字节宏定义 APP->MM*/
#define APP_MM_TP_MSG_ID_HEADER                             OM_PS_TRANSPARENT_CMD_REQ

/*MM->APP 透明命令消息前3个字节宏定义 MM->APP*/
#define MM_APP_TP_MSG_ID_HEADER                             OM_PS_TRANSPARENT_CMD_CNF

/*MM->APP 空口上报消息前3个字节宏定义 MM->APP*/
#define MM_APP_AIR_MSG_ID_HEADER                            PS_OMT_AIR_MSG_REPORT_IND
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4. Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : APP_MM_MSG_TYPE_ENUM
 枚举说明  : APP与MM消息取值
*****************************************************************************/
enum    APP_MM_MSG_TYPE_ENUM
{
    /* 普通命令 参数查询类消息  0x30 ~ 0x4F*/
    ID_APP_MM_CMD_INQ_START             = 0x30+APP_MM_COMM_MSG_ID_HEADER,

    ID_APP_MM_INQ_UE_MODE_REQ           = 0x44 + APP_MM_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_UE_MODE_REQ_STRU */
    ID_APP_MM_INQ_UE_MODE_CNF           = 0x44 + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_UE_MODE_CNF_STRU */
    ID_APP_MM_INQ_LTE_CS_REQ            = 0x45 + APP_MM_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_LTE_CS_REQ_STRU */
    ID_APP_MM_INQ_LTE_CS_CNF            = 0x45 + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_LTE_CS_CNF_STRU */



    ID_APP_MM_CMD_INQ_END               = 0x4F+APP_MM_COMM_MSG_ID_HEADER,

    /* niuxiufan DT begin */
    ID_APP_MM_INQ_LTE_GUTI_REQ          = 0x46 + APP_MM_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_LTE_GUTI_REQ_STRU */
    ID_APP_MM_INQ_LTE_GUTI_CNF          = 0x46 + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_LTE_GUTI_CNF_STRU */
    ID_APP_MM_INQ_LTE_GUTI_IND          = 0x47 + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_LTE_GUTI_IND_STRU */

    ID_APP_MM_INQ_IMSI_REQ              = 0x47 + APP_MM_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_IMSI_REQ_STRU */
    ID_APP_MM_INQ_IMSI_CNF              = 0x48 + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_IMSI_CNF_STRU */
    ID_APP_MM_INQ_IMSI_IND              = 0x49 + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_IMSI_IND_STRU */

    ID_APP_MM_INQ_EMM_STATE_REQ         = 0x48 + APP_MM_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_EMM_STATE_REQ_STRU */
    ID_APP_MM_INQ_EMM_STATE_CNF         = 0x4a + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_EMM_STATE_CNF_STRU */
    ID_APP_MM_INQ_EMM_STATE_IND         = 0x4b + MM_APP_COMM_MSG_ID_HEADER,    /* _H2ASN_MsgChoice APP_MM_INQ_EMM_STATE_IND_STRU */

    /* niuxiufan DT end */

    /* 普通命令 流程类消息  0x50 ~ 0x8F*/

    ID_APP_MM_REG_STAT_IND              = 0x5D+MM_APP_COMM_MSG_ID_HEADER,   /* _H2ASN_MsgChoice APP_MM_REG_STAT_IND_STRU */

    ID_APP_MM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : APP_EMM_MAIN_STATE_ENUM
 枚举说明  : EMM主状态
*****************************************************************************/
enum    APP_EMM_MAIN_STATE_ENUM
{
    /*=================== EMM的主状态 ===================*/
    APP_EMM_MS_NULL                     = 0x0000,   /* 空状态           */
    APP_EMM_MS_DEREG                    = 0x0001,   /* DETACH状态       */
    APP_EMM_MS_REG_INIT                 = 0x0002,   /* ATTACH过程中状态 */
    APP_EMM_MS_REG                      = 0x0003,   /* ATTACH状态       */
    APP_EMM_MS_DEREG_INIT               = 0x0004,   /* DETACH过程中状态 */
    APP_EMM_MS_TAU_INIT                 = 0x0005,   /* TAU过程中状态    */
    APP_EMM_MS_SER_INIT                 = 0x0006,   /* SERVICE过程中状态*/
    APP_EMM_MS_STATE_BUTT
};
typedef VOS_UINT16 APP_EMM_MAIN_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : APP_EMM_SUB_STATE_ENUM
 枚举说明  : EMM子状态
*****************************************************************************/
enum    APP_EMM_SUB_STATE_ENUM
{

    /*=================== EMM的子状态 ===================*/
    APP_EMM_SS_NULL                       = 0x0000,  /* 空子状态 */
    /*========== APP_EMM_MS_DEREG下的子状态 ==============*/
    APP_EMM_SS_DEREG_NORMAL_SERVICE       = 0x0001,  /* 未注册正常服务状态 */
    APP_EMM_SS_DEREG_LIMITED_SERVICE      = 0x0002,  /* 未注册限制服务状态 */
    APP_EMM_SS_DEREG_ATTEMPT_TO_ATTACH    = 0x0003,  /* 未注册等待尝试ATTCH状态*/
    APP_EMM_SS_DEREG_PLMN_SEARCH          = 0x0004,  /* 未注册搜网状态 */
    APP_EMM_SS_DEREG_NO_IMSI              = 0x0005,  /* 未注册卡无效状态 */
    APP_EMM_SS_DEREG_ATTACH_NEEDED        = 0x0006,  /* 未注册需要尽快ATTACH状态 */
    APP_EMM_SS_DEREG_NO_CELL_AVAILABLE    = 0x0007,  /* 未注册没有可用小区状态 */

    /*========== APP_EMM_MS_REG下的子状态 ================*/
    APP_EMM_SS_REG_NORMAL_SERVICE         = 0x0011,  /* 注册正常服务状态 */
    APP_EMM_SS_REG_ATTEMPTING_TO_UPDATE   = 0x0012,  /* 注册等待尝试TA更新状态 */
    APP_EMM_SS_REG_LIMITED_SERVICE        = 0x0013,  /* 注册限制服务状态 */
    APP_EMM_SS_REG_PLMN_SEARCH            = 0x0014,  /* 注册搜网状态 */
    APP_EMM_SS_REG_WAIT_ACCESS_GRANT_IND         = 0x0015,  /* 注册需要TA更新状态 */
    APP_EMM_SS_REG_NO_CELL_AVAILABLE      = 0x0016,  /* 注册没有可用小区状态 */
    APP_EMM_SS_REG_ATTEMPT_TO_UPDATE_MM   = 0x0017,  /* 联合注册只注册成功EPS服务的状态 */
    APP_EMM_SS_REG_IMSI_DETACH_WAIT_CN_DETACH_CNF   = 0x0018,  /* IMSI DETACH等待网络回复状态 */
    APP_EMM_SS_REG_IMSI_DETACH_WAIT_RRC_REL_IND     = 0x0019,  /* IMSI DETACH等待链路释放状态 */
    APP_EMM_SS_BUTT
};
typedef VOS_UINT16  APP_EMM_SUB_STATE_ENUM_UINT16;
/*****************************************************************************
 枚举名    : APP_EMM_UPDATE_STAT_ENUM
 枚举说明  : EMM UPDATE状态
*****************************************************************************/
enum    APP_EMM_UPDATE_STATE_ENUM
{
    APP_EMM_US_EU1_UPDATED                  = 0x00,   /* 更新状态       */
    APP_EMM_US_EU2_NOT_UPDATED              = 0x01,   /* 未更新状态     */
    APP_EMM_US_EU3_ROAMING_NOT_ALLOWED      = 0x02,   /* 漫游不允许状态 */

    APP_EMM_US_BUTT
};
typedef VOS_UINT32  APP_EMM_UPDATE_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_EMM_REG_STATE_ENUM
 枚举说明  : EMM注册状态
*****************************************************************************/
enum APP_EMM_REG_STATE_ENUM
{
    APP_EMM_RS_NULL                          = 0x00,   /* 空状态 */
    APP_EMM_RS_L1_UPDATED                    = 0x01,   /* 更新状态 */
    APP_EMM_RS_L2_IDLE_NO_IMSI               = 0x02,   /* 卡无效状态 */
    APP_EMM_RS_L3_ROMING_NOT_ALLOW           = 0x03,   /* 漫游不允许状态 */
    APP_EMM_RS_L4_NOT_UPDATED                = 0x04,   /* 未更新状态 */
    APP_EMM_RS_BUTT
};
typedef VOS_UINT32 APP_EMM_REG_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_EMM_SEL_MODE_ENUM
 枚举说明  : 选网模式
*****************************************************************************/
enum    APP_EMM_SEL_MODE_ENUM
{
    APP_EMM_PLMN_SEL_AUTO               = 0x00,    /* 自动网络选择模式 */
    APP_EMM_PLMN_SEL_MANUAL             = 0x01,    /* 手动网络选择模式 */
    APP_EMM_PLMN_SEL_BUTT
};
typedef VOS_UINT32 APP_EMM_SEL_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_MM_LOCK_PLMN_TYPE_ENUM
 枚举说明  : PLMN lock类型
*****************************************************************************/
enum    APP_MM_LOCK_PLMN_TYPE_ENUM
{
    APP_MM_LOCK_PLMN_TYPE_LOCK          = 0x00,
    APP_MM_LOCK_PLMN_TYPE_UNLOCK        = 0x01,
    APP_MM_LOCK_PLMN_TYPE_BUTT
};
typedef VOS_UINT32   APP_MM_LOCK_PLMN_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_EMM_SRV_STATE_ENUM
 枚举说明  : 服务状态
*****************************************************************************/
enum APP_EMM_SRV_STATE_ENUM
{
    APP_EMM_SRV_STATUS_NO_SRV           = 0x00,    /* 无服务状态 */
    APP_EMM_SRV_STATUS_LIMITED          = 0x01,    /* 限制服务状态 */
    APP_EMM_SRV_STATUS_SRV              = 0x02,    /* 服务状态 */
    APP_EMM_SRV_STATUS_LIMITED_REGIONAL = 0x03,    /* 区域限制服务状态 */
    APP_EMM_SRV_STATUS_BUTT
};
typedef VOS_UINT32 APP_EMM_SRV_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_MM_REPORT_MODE_ENUM
 枚举说明  : 上报模式
*****************************************************************************/
enum APP_MM_REPORT_MODE_ENUM
{
    APP_MM_RM_ONE_TIME                  = 0x00,    /* 上报一次 */
    APP_MM_RM_AUTO                      = 0x01,    /* 主动上报 */
    APP_MM_RM_PERIOD                    = 0x02,    /*周期上报 */
    APP_MM_RM_BUTT
};
typedef VOS_UINT32 APP_MM_REPORT_MODE_ENUM_UINT32;

/* niuxiufan DT begin */
/*****************************************************************************
 枚举名    : NAS_DT_RPT_STATUS_ENUM_UINT32
 枚举说明  : NAS为路测软件上报的状态
*****************************************************************************/

enum NAS_DT_PRT_STAUTS_ENUM
{
    NAS_DT_RPT_STOP,        /*停止*/
    NAS_DT_RPT_START,       /*启动*/
    NAS_DT_RPT_BUTT
};
typedef VOS_UINT32 NAS_DT_RPT_STATUS_ENUM_UINT32;
/*****************************************************************************
 枚举名    : NAS_DT_REPORT_ITEM_ENUM_UINT32
 枚举说明  : NAS为路测软件上报的类型枚举
*****************************************************************************/
enum NAS_DT_REPORT_ITEM_ENUM
{
    NAS_DT_REPORT_TYPE_GUTI,
    NAS_DT_REPORT_TYPE_IMSI,
    NAS_DT_REPORT_TYPE_EMM_STATE,
    NAS_DT_REPORT_TYPE_BUTT
};
typedef VOS_UINT32 NAS_DT_REPORT_ITEM_ENUM_UINT32;

/*****************************************************************************
 结构名    : NAS_OM_RPT_TIMER_STRU
 结构说明  : NAS给路测软件周期性上报时的定时器信息
*****************************************************************************/
typedef struct
{
    HTIMER                            pRptTimer; /*周期上报定时器 */
    VOS_UINT32                        ulRptPeriod;/*上报周期 */
}NAS_DT_RPT_TIMER_STRU;
/*****************************************************************************
 结构名    : APP_MM_DT_REPORT_CTRL_STRU
 结构说明  : NAS给路测软件上报的控制结构
*****************************************************************************/

typedef struct
{
    NAS_DT_REPORT_ITEM_ENUM_UINT32    enDtRptItem;/*所要上报的项目 */
    NAS_DT_RPT_STATUS_ENUM_UINT32     enRptStatus; /*是否允许上报 */
    APP_MM_REPORT_MODE_ENUM_UINT32    enRptType;  /*上报类型 */
    NAS_DT_RPT_TIMER_STRU             stRptTimer;/*上报周期定时器信息 */
}APP_MM_DT_REPORT_CTRL_STRU;
/* niuxiufan DT end */

/* OM和MM间的维护类命令执行结果类型 */
/*
enum    APP_MM_MAINTAIN_RST_ENUM
{
    APP_MM_MAINTAIN_RST_SUCC       = 0x01,
    APP_MM_MAINTAIN_RST_FAIL       = 0x02,

    APP_MM_MAINTAIN_RST_BUTT
};
typedef VOS_UINT8   APP_MM_MAINTAIN_RST_ENUM_UINT8;
*/

/* OM和MM间的透明类命令类型 */
/*
enum    APP_MM_TRANSPARENT_MSG_TYPE_ENUM
{
    APP_MM_TP_SET_NET_CAP_REQ          = 0x01,
    APP_MM_TP_INQ_NET_CAP_REQ          = 0x02,

    APP_MM_TRANSPARENT_BUTT
};
typedef VOS_UINT8   APP_MM_TRANSPARENT_MSG_TYPE_ENUM_UINT8;

enum    APP_MM_TRANSPARENT_CAUSE_ENUM
{
    APP_MM_TP_CAUSE_TP_MSG_TYPE_UNKNOWN= 0x01,
    APP_MM_TP_CAUSE_PARA_RANGE_ERR     = 0x02,
    APP_MM_TP_CAUSE_BUTT               = 0xFF
};
typedef VOS_UINT8   APP_MM_TRANSPARENT_CAUSE_ENUM_UINT8;

*/
/*****************************************************************************
 枚举名    : APP_PH_RA_MODE_ENUM
 枚举说明  : 接入模式
*****************************************************************************/

enum APP_PH_RA_MODE_ENUM
{
    APP_PH_RAT_WCDMA                   = 0x00,
    APP_PH_RAT_GSM_GPRS                = 0x01,
    APP_PH_RAT_LTE_FDD                 = 0x02,
    APP_PH_RAT_LTE_TDD                 = 0x03,

    APP_PH_RAT_TYPE_BUTT
};
typedef VOS_UINT32  APP_PH_RA_MODE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : APP_PLMN_RESEL_MODE_TYPE_ENUM
 枚举说明  : PLMN重选类型
*****************************************************************************/
enum APP_PLMN_RESEL_MODE_TYPE_ENUM
{
    APP_PLMN_RESELECTION_AUTO           = 0x00,             /* 自动重选 */
    APP_PLMN_RESELECTION_MANUAL         = 0x01,             /* 手动重选 */

    APP_PLMN_RESEL_MODE_TYPE_BUTT
};
typedef VOS_UINT32 APP_PLMN_RESEL_MODE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_PLMN_STATUS_FLAG_ENUM
 枚举说明  : PLMN状态
*****************************************************************************/
enum APP_PLMN_STATUS_FLAG_ENUM
{
    APP_PLMN_STATUS_UNKNOWN             = 0x00,
    APP_PLMN_STATUS_AVAILABLE           = 0x01,
    APP_PLMN_STATUS_CURRENT             = 0x02,
    APP_PLMN_STATUS_FORBIDDEN           = 0x03,

    APP_PLMN_STATUS_FLAG_BUTT
};
typedef VOS_UINT32 APP_PLMN_STATUS_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_PHONE_SERVICE_STATUS_ENUM
 枚举说明  : 服务状态
*****************************************************************************/
enum APP_PHONE_SERVICE_STATUS_ENUM
{
    APP_NORMAL_SERVICE                  = 0x00,             /* 正常工作状态   */
    APP_LIMITED_SERVICE                 = 0x01,             /* 限制服务状态   */
    APP_ATTEMPTING_TO_UPDATE            = 0x02,             /* 更新状态中     */
    APP_NO_IMSI                         = 0x03,             /* 不存在IMSI状态 */
    APP_NO_SERVICE                      = 0x04,             /* 无服务状态     */
    APP_DETACHED                        = 0x05,             /* 去附着状态     */
    APP_DISABLE                         = 0x06,             /* 服务不可用状态 */
    APP_DETACH_FAIL                     = 0x07,             /* 执行去注册失败*/

    APP_PHONE_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 APP_PHONE_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_MM_ATTACH_TYPE_ENUM
 枚举说明  : ATTACH TYPE
*****************************************************************************/
enum APP_MM_ATTACH_TYPE_ENUM
{
    APP_MM_ATTACH_TYPE_PS               = 0x01,
    APP_MM_ATTACH_TYPE_PS_CS            = 0x02,

    APP_MM_ATTACH_RST_BUTT
};
typedef VOS_UINT32   APP_MM_ATTACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : APP_MM_DETACH_TYPE_ENUM
 枚举说明  : DETACH TYPE
*****************************************************************************/
enum    APP_MM_DETACH_TYPE_ENUM
{
    APP_MM_DETACH_TYPE_PS               = 0x01,
    APP_MM_DETACH_TYPE_CS               = 0x02,
    APP_MM_DETACH_TYPE_PS_CS            = 0x03,
    APP_MM_DETACH_TYPE_BUTT
};
typedef VOS_UINT32   APP_MM_DETACH_TYPE_ENUM_UINT32;


enum APP_EMM_SMC_CTRL_ENUM
{
    APP_EMM_SMC_OPEN                    = 0,
    APP_EMM_SMC_CLOSE                   = 1,

    APP_EMM_SMC_CTRL_BUTT
};
typedef VOS_UINT8 APP_EMM_SMC_CTRL_ENUM_UINT8;

enum APP_REG_STAT_ENUM
{
    APP_REG_STAT_NOT_REG_AND_NOT_SRCH_OPERATOR         = 0x00,
    APP_REG_STAT_REG_HPLMN                             ,
    APP_REG_STAT_NOT_REG_AND_SRCH_OPERATOR             ,
    APP_REG_STAT_REG_DENIED                            ,
    APP_REG_STAT_UNKNOWN                               ,
    APP_REG_STAT_REG_ROAMING                           ,
    APP_REG_STAT_BUTT
};
typedef VOS_UINT32 APP_REG_STAT_ENUM_UINT32;

enum APP_MM_SERVICE_DOMAIN_ENUM
{
    APP_MM_SERVICE_DOMAIN_NULL          = 0x00,
    APP_MM_SERVICE_DOMAIN_PS            ,
    APP_MM_SERVICE_DOMAIN_CS            ,
    APP_MM_SERVICE_DOMAIN_PS_CS         ,
    APP_MM_SERVICE_DOMAIN_BUTT
};
typedef VOS_UINT32 APP_MM_SERVICE_DOMAIN_ENUM_UINT32;


enum APP_MM_DETACH_ENTITY_ENUM
{
    APP_MM_DETACH_ENTITY_ME             = 0x01,
    APP_MM_DETACH_ENTITY_NW             = 0x02,
    APP_MM_DETACH_ENTITY_BUTT
};
typedef VOS_UINT32 APP_MM_DETACH_ENTITY_ENUM_UINT32;

enum APP_MM_PLMN_TYPE_ENUM
{
    APP_MM_PLMN_TYPE_RPLMN              = 0x01,
    APP_MM_PLMN_TYPE_EPLMN              ,
    APP_MM_PLMN_TYPE_FPLMN              ,
    APP_MM_PLMN_TYPE_UPLMN              ,
    APP_MM_PLMN_TYPE_OPLMN              ,
    APP_MM_PLMN_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_PLMN_TYPE_ENUM_UINT32;

enum APP_MM_SET_TYPE_ENUM
{
    APP_MM_SET_TYPE_SETTING             = 0x00,
    APP_MM_SET_TYPE_DELETE              ,
    APP_MM_SET_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_SET_TYPE_ENUM_UINT32;

enum APP_MM_DAYLIGHT_SAVE_TIME_ENUM
{
    APP_MM_DAYLIGHT_NO_ADJUST                         = 0,
    APP_MM_DAYLIGHT_1_HOUR_ADJUST                        ,
    APP_MM_DAYLIGHT_2_HOUR_ADJUST                        ,
    APP_MM_DAYLIGHT_BUTT
};
typedef VOS_UINT32  APP_MM_DAYLIGHT_SAVE_TIME_ENUM_UINT32;

enum APP_MM_TIMEZONE_ENUM
{
    APP_MM_TIMEZONE_POSITIVE                        = 0,
    APP_MM_TIMEZONE_NAGETIVE                           ,
    APP_MM_TIMEZONE_BUTT
};
typedef VOS_UINT8  APP_MM_TIMEZONE_ENUM_UINT8;


/*****************************************************************************
  5. STRUCT
*****************************************************************************/


/* APP_MM_MSG_ID_UINT32包括4部分:

-----------------------------------------------------------
  字节高位                                      字节低位
-----------------------------------------------------------
| BYTE1高4位 + 0000 |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------
0000：协议模块间消息|  源模块号 |  目的模块号| 消息号0-255
-----------------------------------------------------------
0001：L2 LOG        |           |            |
-----------------------------------------------------------
0010：空口消息      |           |            |
-----------------------------------------------------------
0011：普通命令      |           |            |
-----------------------------------------------------------
0100：实时监控命令  |           |            |
-----------------------------------------------------------
0101：关键事件      |           |            | 保留不用
-----------------------------------------------------------
*/
typedef VOS_UINT32  APP_MM_MSG_ID_UINT32;


/*****************************************************************************
 结构名    : APP_PLMN_ID_STRU
 结构说明  :
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

    AT命令：
    at+cops=1,2,"mcc digit 1, mcc digit 2, mcc digit 3, mnc digit 1, mnc digit 2, mnc

digit 3",2 :

    e.g.
    at+cops=1,2,"789456",2 :
    --------------------------------------------------------------------------------
    (mcc digit 1)|(mcc digit 2)|(mcc digit 3)|(mnc digit 1)|(mnc digit 2)|(mnc digit 3)
    --------------------------------------------------------------------------------
       7         |     8       |      9      |     4       |      5      |     6
    --------------------------------------------------------------------------------

    在aucPlmnId[3]中的存放格式:
    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2 = 8        |           MCC digit 1 = 7
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3 = 6        |           MCC digit 3 = 9
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2 = 5        |           MNC digit 1 = 4
    ---------------------------------------------------------------------------

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
} APP_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : APP_PLMN_INFO_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    APP_PLMN_ID_STRU                    stPlmnId;           /* PLMN ID  */
    APP_PLMN_STATUS_FLAG_ENUM_UINT32    ulPlmnStatus;       /* PLMN状态 */
    APP_PH_RA_MODE_ENUM_UINT32          ulAccessMode;       /* 接入方式 */
} APP_PLMN_INFO_STRU;

/*****************************************************************************
 结构名    : APP_PLMN_LIST_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    APP_PLMN_INFO_STRU                  stPlmnInfo[APP_MAX_PLMN_NUM];
} APP_PLMN_INFO_LIST_STRU;

/*****************************************************************************
结构名称    :APP_GUTI_HEAD_STRU
使用说明    :APP_GUTI_HEAD_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}APP_GUTI_HEAD_STRU;

/*****************************************************************************
结构名称    :APP_MME_GROUPID_STRU
使用说明    :APP_MME_GROUPID_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}APP_MME_GROUPID_STRU;

/*****************************************************************************
结构名称    :APP_MME_CODE_STRU
使用说明    :APP_MME_CODE_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}APP_MME_CODE_STRU;

/*****************************************************************************
结构名称    :APP_MTMSI_STRU
使用说明    :APP_MTMSI_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}APP_MTMSI_STRU;


/*****************************************************************************
结构名称    :APP_GUTI_STRU
使用说明    :APP_GUTI_STRU的相关参数
*****************************************************************************/
typedef struct
{
    APP_GUTI_HEAD_STRU                  stGutiHead;
    APP_PLMN_ID_STRU                    stPlmn;
    APP_MME_GROUPID_STRU                stMmeGroupId;
    APP_MME_CODE_STRU                   stMmeCode;
    APP_MTMSI_STRU                      stMTmsi;
}APP_GUTI_STRU;


/*****************************************************************************
结构名称    : APP_MBMSSER_ID_STRU
使用说明    : 24.008 10.5.6.13
              MBMS Service ID (octet 3, 4 and 5)
              In the MBMS Service ID field bit 8 of octet 3 is the most
              significant bit and bit 1 of octet 5 the least significant bit.
              The coding of the MBMS Service ID is the responsibility of each
              administration. Coding using full hexadecimal representation may
              be used. The MBMS Service ID consists of 3 octets.
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMbmsSerId;
}APP_MBMSSER_ID_STRU;
/*****************************************************************************
结构名称    :APP_TMGI_STRU
使用说明    :APP_TMGI_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPlmn         :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitSpare          :31;

    APP_MBMSSER_ID_STRU                 stMbmsSer;
    APP_PLMN_ID_STRU                    stPlmnId;
}APP_TMGI_STRU;

/*****************************************************************************
结构名称    :APP_TMGI_MBMS_HEAD_STRU
使用说明    :APP_TMGI_MBMS_HEAD_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeTi;
    VOS_UINT8                           aucRsv[2];
}APP_TMGI_MBMS_HEAD_STRU;
/*****************************************************************************
结构名称    :APP_TMGI_MBMS_STRU
使用说明    :APP_TMGI_MBMS_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpMbmsSesId  :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitSpare        :31;

    APP_TMGI_MBMS_HEAD_STRU             stMsidHead;
    APP_TMGI_STRU                       stTmgi;
    VOS_UINT8                           ucMbmsSesId;
    VOS_UINT8                           aucRsv[3];
}APP_TMGI_MBMS_STRU;

/*****************************************************************************
结构名称    :APP_UEID_STRU
使用说明    :APP_UEID_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpImsi     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpImeisv   :1;
    VOS_UINT32                          bitOpTmsi     :1;
    VOS_UINT32                          bitOpPtmsi    :1;
    VOS_UINT32                          bitOpGuti     :1;
    VOS_UINT32                          bitOpTmgiMbms :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :25;


    VOS_UINT8                           aucImsi[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           aucImei[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved2[2];
    VOS_UINT8                           aucImeisv[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved3[2];
    VOS_UINT8                           aucTmsi[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved4[2];
    VOS_UINT8                           aucPtmsi[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved5[2];

    APP_GUTI_STRU                       stGuti;
    APP_TMGI_MBMS_STRU                  stTmgiMbms;
}APP_UEID_STRU;

/*****************************************************************************
结构名称    :APP_LAC_STRU
使用说明    :APP_LAC_STRU的相关参数
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucLac;
    VOS_UINT8                           ucLacCnt;
    VOS_UINT8                           aucRsv[2];
} APP_LAC_STRU;

/*****************************************************************************
结构名称    :APP_RAC_STRU
使用说明    :APP_RAC_STRU的相关参数
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucRsv[3];
} APP_RAC_STRU;

/*****************************************************************************
结构名称    :APP_TAC_STRU
使用说明    :APP_TAC_STRU的相关参数
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
} APP_TAC_STRU;

/*****************************************************************************
结构名称    :APP_NETWORK_ID_STRU
使用说明    :APP_NETWORK_ID_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPlmnId   : 1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpLac      : 1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRac      : 1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpTac      : 1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpCellId   : 1;
    VOS_UINT32                          bitOpRsv      : 27;

    APP_PLMN_ID_STRU                    stPlmnId;
    APP_LAC_STRU                        stLac;
    APP_RAC_STRU                        stRac;
    APP_TAC_STRU                        stTac;
    VOS_UINT32                          ulCellId;                           /* Cell Identity */
} APP_NETWORK_ID_STRU;


/*****************************************************************************
结构名称    :APP_MS_CLASSMARK_1_STRU
使用说明    :24.008 840 10.5.1.5
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucValue;
    VOS_UINT8                           aucRsv[3];

}APP_MS_CLASSMARK_1_STRU;

/*****************************************************************************
结构名称    :APP_MS_CLASSMARK_2_STRU
使用说明    :24.008 840 10.5.1.6
              考虑大小端和BIT序，进行修改；
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenLvLen;
    VOS_UINT8                           aucClassMark[3];
}APP_MS_CLASSMARK_2_STRU;

/*****************************************************************************
结构名称    :APP_MS_CLASSMARK_3_STRU
使用说明    :24.008 840 10.5.1.7
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenLvLen;
    VOS_UINT8                           aucValue[35];

}APP_MS_CLASSMARK_3_STRU;

/*****************************************************************************
结构名称    :APP_MS_CLASSMARK_STRU
使用说明    :24.008 840 10.5.1.6
            0   EPS encryption algorithm *** not supported
            1   EPS encryption algorithm *** supported

            #define NAS_MM_ALGORITHM_NOT_SUPPORT    0
            #define NAS_MM_ALGORITHM_SUPPORT        1
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpClassMark1     :1;
    VOS_UINT32                          bitOpClassMark2     :1;
    VOS_UINT32                          bitOpClassMark3     :1;

    VOS_UINT32                          bitOpRsv            :29;

    APP_MS_CLASSMARK_1_STRU             stClassMark1;
    APP_MS_CLASSMARK_2_STRU             stClassMark2;
    APP_MS_CLASSMARK_3_STRU             stClassMark3;

}APP_MS_CLASSMARK_STRU;

/*****************************************************************************
结构名称    :APP_UE_NET_CAP_STRU
使用说明    :23.401-800 9.9.3.34
            0   EPS encryption algorithm *** not supported
            1   EPS encryption algorithm *** supported

            #define NAS_MM_ALGORITHM_NOT_SUPPORT    0
            #define NAS_MM_ALGORITHM_SUPPORT        1
            考虑大小端和BIT序，进行修改；
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeNetCapLen;
    VOS_UINT8                           aucUeNetCap[NAS_MM_MAX_UE_NET_CAP_LEN];
    VOS_UINT8                           aucRsv[2];
}APP_UE_NET_CAP_STRU;

/*****************************************************************************
结构名称    :APP_MS_NET_CAP_STRU
使用说明    :24.008 10.5.5.12

    aucMsNetCap数组中与协议描述的字节/位的关系如下:
    --------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    --------------------------------------------------------------
        Length of MS network capability contents, UNIT is byte      octet 0
    --------------------------------------------------------------
        MS network capability value                                 octet 1-8
    --------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsNetCapLen;
    /* 由于编码时是直接拷贝，因此aucMsNetCap[0]的逻辑最高位是GEA1 bits，与空口传输一致 */
    VOS_UINT8                           aucMsNetCap[NAS_MM_MAX_MS_NET_CAP_LEN];
    VOS_UINT8                           aucRsv[3];
}APP_MS_NET_CAP_STRU;

typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    APP_PLMN_ID_STRU                    astPlmnId[APP_MM_MAX_PLMN_NUM];
}APP_MM_PLMN_LIST_STRU;

typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    APP_PLMN_ID_STRU                    astPlmnId[APP_MM_MAX_EQU_PLMN_NUM];
} APP_EMM_EPLMN_LIST_STRU;

typedef struct
{
    APP_PLMN_ID_STRU                    stPlmnId;
    APP_TAC_STRU                        stTac;
}APP_TA_STRU;

typedef struct
{
    VOS_UINT32                          ulTaNum;            /* TA的个数    */
    APP_TA_STRU                         astTa[APP_MM_MAX_TA_NUM];
}APP_TA_LIST_STRU;

typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    APP_PLMN_ID_STRU                    astPlmnId[APP_MM_MAX_PLMN_NUM];
}APP_EMM_PLMN_LIST_STRU;

typedef struct
{
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulMainState;        /*MM主状态*/
    APP_EMM_SUB_STATE_ENUM_UINT16       ulSubState;         /*MM子状态*/
    APP_EMM_UPDATE_STATE_ENUM_UINT32    ulEmmUpState;       /*EMM update状态*/
    APP_EMM_REG_STATE_ENUM_UINT32       ulRegState;         /*注册状态*/
    APP_EMM_SRV_STATE_ENUM_UINT32       ulMmcSrvStat;       /*EMM服务状态*/
    APP_EMM_SEL_MODE_ENUM_UINT32        ulPlmnSelMode;      /*搜网模式*/
    APP_EMM_EPLMN_LIST_STRU             stEPlmnList;        /*EPLMN List*/
    APP_PLMN_ID_STRU                    stRplmn;            /*RPlmn*/
    APP_TA_LIST_STRU                    stTaiList;          /*TaiList*/
    APP_TA_STRU                         stLastTa;           /*Last Ta*/
    APP_EMM_PLMN_LIST_STRU              stFplmnList;        /*Forbiden Plmn*/
    APP_TA_LIST_STRU                    stForbTaList;       /*Forbiden Ta*/
    APP_GUTI_STRU                       stGuti;             /*GUTI */
}APP_EMM_INFO_STRU;

typedef struct
{
    APP_MM_TIMEZONE_ENUM_UINT8          enPosNegTimeZone;
    VOS_UINT8                           ucTimeZone;
    VOS_UINT8                           aucRsv[2];
}APP_MM_CN_TIMEZONE_STRU;

typedef struct
{
    APP_MM_CN_TIMEZONE_STRU             stTimeZone;
    VOS_UINT8                           ucYear;
    VOS_UINT8                           ucMonth;
    VOS_UINT8                           ucDay;
    VOS_UINT8                           ucHour;
    VOS_UINT8                           ucMinute;
    VOS_UINT8                           ucSecond;
    VOS_UINT8                           aucRsv[2];
}APP_MM_CN_TIMEZONE_UNITIME_STRU;


typedef struct
{
    VOS_UINT8                           ucMsgLen; /*表示数组中TextString的长度*/
    VOS_UINT8                           ucCodingScheme;
    VOS_UINT8                           ucAddCI;
    VOS_UINT8                           ucNumOfSpareInLastByte;
    VOS_UINT8                           aucMsg[APP_MM_CN_NAME_MAX_LEN];
    VOS_UINT8                           ucRsv;
}APP_MM_CN_NETWORK_NAME_STRU;

/*****************************************************************************
结构名称    :APP_DRX_STRU
使用说明    :
    ucSplitPgCode:取值范围 [0,98]
    ucPsDrxLen:只能取值(0,6,7,8,9),其中0:标志UE不指定DRX Cycle Len
    ucSplitOnCcch:只能取值0 或者 1
    ucNonDrxTimer:取值范围[0,7]
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSplitPgCode;      /* SPLIT PG CYCLE CODE*/
    VOS_UINT8                           ucPsDrxLen;         /* DRX length         */
    VOS_UINT8                           ucSplitOnCcch;      /* SPLIT on CCCH      */
    VOS_UINT8                           ucNonDrxTimer;      /* non-DRX timer      */
}APP_DRX_STRU;

/*****************************************************************************
 结构名    : APP_MM_START_REQ_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
} APP_MM_START_REQ_STRU;

/*****************************************************************************
 结构名    : APP_MM_START_CNF_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt ;
} APP_MM_START_CNF_STRU;

/*****************************************************************************
 结构名    : APP_MM_STOP_REQ_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
} APP_MM_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : APP_MM_STOP_CNF_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} APP_MM_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : APP_MM_ATTACH_REQ_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_MM_ATTACH_TYPE_ENUM_UINT32      enAttachType;        /* 附着类型 */
} APP_MM_ATTACH_REQ_STRU;

/*****************************************************************************
 结构名    : APP_MM_ATTACH_CNF_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER

    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} APP_MM_ATTACH_CNF_STRU;

/*****************************************************************************
 结构名    : APP_MM_ATTACH_IND_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
    APP_MM_ATTACH_TYPE_ENUM_UINT32      enAttachType;       /* 附着类型       */
} APP_MM_ATTACH_IND_STRU;


/*****************************************************************************
 结构名    : APP_MM_DETACH_REQ_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_MM_DETACH_TYPE_ENUM_UINT32      enDetachType;
} APP_MM_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : APP_MM_DETACH_CNF_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} APP_MM_DETACH_CNF_STRU;


/*****************************************************************************
 结构名    : APP_MM_DETACH_IND_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_MM_DETACH_ENTITY_ENUM_UINT32    enDetEntityType;
} APP_MM_DETACH_IND_STRU;



/*****************************************************************************
 结构名    : APP_MM_REG_STAT_IND
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER

    VOS_UINT32                          ulOpId;
    APP_REG_STAT_ENUM_UINT32            enRegStat;
    APP_MM_SERVICE_DOMAIN_ENUM_UINT32   enSrvDomain;
    APP_PH_RA_MODE_ENUM_UINT32          enAccessMode;  /*接入模式*/
    APP_PLMN_ID_STRU                    stPlmnId;      /* PLMN ID  */
    APP_TAC_STRU                        stTac;
    VOS_UINT32                          ulCellId;
}APP_MM_REG_STAT_IND_STRU;



/*========== 设置查询命令类  参数结构 ==========*/

typedef struct
{
    VOS_UINT8                           ucBitOpAttach;
    VOS_UINT8                           aucBitOpRsv[3];

    VOS_UINT8                           ucAttachAtmNum;
    VOS_UINT8                           aucRsv[3];
}APP_MM_OPT_ATTEMP_NUM_STRU;



/*========== 设置普通命令类  消息结构 ========================================*/

typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
}APP_MM_SET_CMD_CNF_STRU;




/*========== 查询普通命令类     消息结构 ==========*/

typedef VOS_UINT32 DT_CMD_ENUM_UINT32;

typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    DT_CMD_ENUM_UINT8                   enCmd;
    VOS_UINT8                           ucRsv[3];
    VOS_UINT32                          ulRptPeriod;
}APP_MM_INQ_CMD_REQ_STRU;


typedef APP_MM_INQ_CMD_REQ_STRU           APP_MM_INQ_UE_MODE_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    VOS_UINT32                            ulRslt;           /*0成功，1失败*/
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32 enCurrentUeMode;  /*当前UE模式*/
    VOS_UINT32                            ulSupportModeCnt; /*UE能够支持的模式的个数*/
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32 aenSupportModeList[4];	/*UE能够支持的模式*/
} APP_MM_INQ_UE_MODE_CNF_STRU;
typedef APP_MM_INQ_CMD_REQ_STRU           APP_MM_INQ_LTE_CS_REQ_STRU;
typedef struct
{
    VOS_UINT8                             ucSmsOverSGs;
    VOS_UINT8                             ucSmsOverIMS;
    VOS_UINT8                             ucCSFB;
    VOS_UINT8                             ucSrVcc;
    VOS_UINT8                             ucVoLGA;
    VOS_UINT8                          aucRsv[3];
} APP_MM_LTE_CS_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                            ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    VOS_UINT32                            ulRslt;           /*0成功，1失败*/
    APP_MM_LTE_CS_INFO_STRU               stLtecsInfo;
} APP_MM_INQ_LTE_CS_CNF_STRU;

/*niuxiufan DT begin */
typedef APP_MM_INQ_CMD_REQ_STRU           APP_MM_INQ_LTE_GUTI_REQ_STRU;

/*V7R2-DT ,l00195322,2014/4/23,CNF 不上报消息体，在IND上报, begin*/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;  /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    VOS_UINT32                            ulRslt;           /*0成功，1失败*/
} APP_MM_INQ_LTE_GUTI_CNF_STRU;
/*V7R2-DT ,l00195322,2014/4/23,CNF 不上报消息体，在IND上报, end*/

typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;  /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    APP_GUTI_STRU                         stGuti;           /*GUTI信息 */
} APP_MM_INQ_LTE_GUTI_IND_STRU;

typedef APP_MM_INQ_CMD_REQ_STRU           APP_MM_INQ_IMSI_REQ_STRU;

typedef struct
{
    VOS_UINT8               ucImsiLen;                        /*IMSI长度 */
    VOS_UINT8               ucImsi[APP_EMM_IMSI_MAX_LEN];     /*IMSI内容 */
}NAS_OM_IMSI_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER                                   /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;   /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    VOS_UINT32                            ulRslt;           /*0成功，1失败*/
} APP_MM_INQ_IMSI_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                 /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;/*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    NAS_OM_IMSI_INFO_STRU                 stImsi;           /*IMSI信息 */
} APP_MM_INQ_IMSI_IND_STRU;

typedef APP_MM_INQ_CMD_REQ_STRU           APP_MM_INQ_EMM_STATE_REQ_STRU;

typedef struct
{
    APP_EMM_MAIN_STATE_ENUM_UINT16       enMainState;        /* EMM主状态*/
    APP_EMM_SUB_STATE_ENUM_UINT16        enSubState;         /* EMM子状态 */
    VOS_UINT16                           usStaTId;           /* 定时器信息*/
    VOS_UINT8                            ucRsv[2];
}NAS_OM_EMM_STATE_STRU;


/*V7R2-DT ,l00195322,2014/4/23,CNF 不上报消息体，在IND上报, begin*/
typedef struct
{
    VOS_MSG_HEADER                                /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;/*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    VOS_UINT32                            ulRslt;           /*0成功，1失败*/
} APP_MM_INQ_EMM_STATE_CNF_STRU;
/*V7R2-DT ,l00195322,2014/4/23, CNF 不上报消息体，在IND上报,end*/

typedef struct
{
    VOS_MSG_HEADER                               /*_H2ASN_Skip*/
    VOS_UINT32                            ulMsgId;/*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                            ulOpId;
    NAS_OM_EMM_STATE_STRU                 stEmmState;        /*EMM状态信息 */
} APP_MM_INQ_EMM_STATE_IND_STRU;

/*niuxiufan DT end */



typedef struct
{
    APP_MM_MSG_TYPE_ENUM_UINT32         enMsgId;            /*_H2ASN_MsgChoice_Export APP_MM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          APP_MM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}APP_MM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    APP_MM_INTERFACE_MSG_DATA           stMsgData;
} AppMmInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/





#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AppMmInterface.h */


