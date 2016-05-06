/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __NASNVINTERFACE_H__
#define __NASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV项激活 */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV项未激活 */

/* GPRS GEA 算法支持宏定义 */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* 支持GPRS GEA1算法 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* 支持GEA1时的网络能力值 */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* 支持GEA2时的网络能力值 */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* 支持GEA3时的网络能力值 */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* 支持GEA4时的网络能力值 */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* 支持GEA5时的网络能力值 */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* 支持GEA6时的网络能力值 */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* 支持GEA7时的网络能力值 */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* 支持GPRS GEA2算法 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* 支持GPRS GEA3算法 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* 支持GPRS GEA4算法 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* 支持GPRS GEA5算法 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* 支持GPRS GEA6算法 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* 支持GPRS GEA7算法 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV中等效plmn个数 */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn中Mcc最大长度 */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn中Mnc最大长度 */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* 用户配置的最多可支持的USIM/SIM卡的个数 */
#define NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* 用户配置的EHplmn的个数 */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* 禁止接入技术的PLMN ID的最大个数 */
#define NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM              (8)                /* 扩展的NV项的EHplmn组的最大个数*/
#define NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN               (8)               /* 用户配置的OPLMN版本号最大长度 */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* 用户配置的OPLMN最多可支持的USIM/SIM卡的个数 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_NUM                   (256)             /* 用户配置的OPLMN的最大个数 */
#define NAS_MMC_NVIM_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* 用户配置的带接入技术OPLMN基本单元长度，如6F61文件的基本长度单元为5 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN              (500)             /* 用户配置OPLMN的最大字节数,扩容前只支持500*/
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN       (1280)            /* 扩展后的用户配置OPLMN的最大字节数*/


/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
/* 扩容:由128改256; 增加预置类型信息,由6改7*/
#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN             (7*256)            /* 扩展后的用户配置DPLMN的最大字节数 */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN             (7*256)            /* 扩展后的用户配置NPLMN的最大字节数 */
/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN       (6*128)            /* 扩展后的用户配置DPLMN的最大字节数*/
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN       (6*128)            /* 扩展后的用户配置NPLMN的最大字节数*/
#define NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM                   (3*8)
#define NAS_MCC_NVIM_VERSION_LEN                         (9)                /* 版本号，固定为xx.xx.xxx */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM                   (256)            /* 扩展后的用户配置DPLMN个数 */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM                   (256)            /* 扩展后的用户配置NPLMN个数 */

#define NAS_NVIM_MAX_OPER_SHORT_NAME_LEN                36
#define NAS_NVIM_MAX_OPER_LONG_NAME_LEN                 40

#define NAS_NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* 最大的IMSI的长度 */
#define NAS_MML_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM中PSLOCI文件的长度 */
#define NAS_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM中PSLOCI文件的长度 */

#define NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM          (6)                 /* 模式自动切换中最大的可配置国家码个数 */
#define NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM       (6)                 /* 模式自动切换中最大的可配置USIM/IMSI的网络号个数 */

#define NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM              (8)                 /* 禁止接入技术的PLMN ID的最大个数 */

#define NAS_SIM_FORMAT_PLMN_LEN                     (3)                     /* Sim卡格式的Plmn长度 */

#define NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* 黑名单锁网支持的PLMN ID的最大个数 */

#define NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* 白名单锁网支持的PLMN ID的最大个数 */

#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG搜不考虑国家码的国家码最大个数 */
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /* 定制原因值最大列表 */

#define NV_ITEM_NET_CAPABILITY_MAX_SIZE                     (10)

#define NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE            (2)                 /* 当前支持的协议版本 */

#define NAS_MMC_NVIM_MAX_IMSI_LEN                           (9)                     /* 最大的IMSI的长度 */

#define NVIM_MAX_EPLMN_NUM                                  (16)
#define NVIM_MAX_MCC_SIZE                                   (3)
#define NVIM_MAX_MNC_SIZE                                   (3)

#define NVIM_MAX_FDD_FREQ_BANDS_NUM                         (12)

/*+CGMI - 获取制造商名称*/

#define NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM         (16)
#define NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM          (8)    /* 预留拓展 */
#define NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM     (2)

#define NAS_NVIM_FORBIDDEN_RAT_NUM_0                 (0)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_1                 (1)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_2                 (2)


#define NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM              (8)

#define NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM     (12)

/* 对NVID枚举的转定义(PS_NV_ID_ENUM, SYS_NV_ID_ENUM, RF_NV_ID_ENUM) */
typedef VOS_UINT16  NV_ID_ENUM_U16;
#define NV_ITEM_IMEI_SIZE                      16
#define NV_ITEM_MMA_OPERATORNAME_SIZE          84

#define NV_ITEM_OPER_NAME_LONG          (40)
#define NV_ITEM_OPER_NAME_SHORT         (36)
#define NV_ITEM_PLMN_ID_LEN             (8)

#define NV_ITEM_AT_PARA_SIZE                   100
#define NV_ITEM_HPLMN_FIRST_SEARCH_SIZE        1  /* 第一次HPLMN搜索的时间间隔 */
#define NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* 最大的IMSI的长度 */

#define CNAS_NVIM_MAX_1X_MRU_SYS_NUM                            (12)

#define NAS_MMC_NVIM_MAX_CAUSE_NUM      (10)     /* NV配置原因值最大个数 */

#define CNAS_NVIM_PRL_SIZE                                      (4096) /* PRL NV size: 4K byte */

#define CNAS_NVIM_MAX_1X_BANDCLASS_NUM                          (32)

#define CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM                       (20)
#define CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM                           (12)
#define CNAS_NVIM_HRPD_SUBNET_LEN                                (16)

#define CNAS_NVIM_MAX_STORAGE_BLOB_LEN                      ( 255 )

#define NAS_NVIM_BYTES_IN_SUBNET                            (16)
#define NAS_NVIM_MAX_RAT_NUM                                (7)                 /* 预留出1X和HRPD */

#define NAS_MSCC_NVIM_MLPL_SIZE                                      (1024) /* PRL NV size: 1K byte */
#define NAS_MSCC_NVIM_MSPL_SIZE                                      (1024) /* PRL NV size: 1K byte */

#define NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM      ( 8 )                       /*  包含全网通性特的通道配置场景数目 */

#define CNAS_NVIM_ICCID_OCTET_LEN                            (10)
#define CNAS_NVIM_MEID_OCTET_NUM                             (7)
#define CNAS_NVIM_UATI_OCTET_LENGTH                          (16)

#define CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM                     (20)

#define CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM                (10)

#define CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM              (10)

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
/* 高优先级PLMN refresh 触发背景搜默认延迟时长: 单位 秒 */
#define NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN    (5)
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */

#define NAS_NVIM_MAX_PLMN_CSG_ID_NUM             (35)
#define NAS_NVIM_MAX_CSG_REJ_CAUSE_NUM           (10)

#define NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM      (16)    /* SIM卡列表 (LTE OOS后先搜2G再搜3G) */

#define NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM        (16)        /*支持的禁止LA列表大小*/
#define CNAS_NVIM_MAX_AUTHDATA_USERNAME_LEN                      (253)   /* HRPD ppp AN鉴权用户名最长用户名，
                                                                            参考C.S0023-D section 3.4.53以及
                                                                            C.S0016-D,section 3.5.8.13,
                                                                            该长度理论最长为255-2(NAI长度以
                                                                            及鉴权算法保留字节占用的字节) */

#define CNAS_NVIM_1X_MAX_MRU_SYS_NUM                   (12)

#define CNAS_NVIM_1X_AVOID_MAX_PHASE_NUM               (8)
#define CNAS_NVIM_1X_AVOID_REASON_MAX                  (20)

#define CNAS_NVIM_MAX_HRPD_OOC_SCHEDULE_PHASE_NUM                    (8)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
枚举名    : NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
结构说明  : 单域注册被拒，MMC的动作

1.日    期   : 2012年6月11日
  作    者   : w00166186
  修改内容   : AT&T&DCM项目新增类型

2.日    期   : 2014年8月19日
  作    者   : w00167002
  修改内容   : DTS2014081905808:在配置PS注册拒绝14时候，若当前在HOME PLMN上，则可能
               触发循环乒乓，修改为增加ACTION动作:在漫游网络上触发选网，在HOME网络上
               不生效，按现有流程进行处理。

*****************************************************************************/
enum NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 0,            /* 触发搜网 */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 1,            /* 正常驻留 */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 2,            /* 触发可选搜网 */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 3,            /* 限制驻留 */

    NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 4,            /* 在漫游网络上注册发起搜网，在HOME网络上不生效 */

    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
结构说明  : 注册失败自定义原因值

1.日    期   : 2012年6月11日
  作    者   : w00166186
  修改内容   : AT&T&DCM项目新增类型

*****************************************************************************/
enum NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN = 14,
    NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT               = 301,                                 /* 等待网侧结果定时器超时 */
    NAS_MMC_NVIM_REG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT16 NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16;

/*****************************************************************************
枚举名    : NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8
结构说明  : 注册域

1.日    期   : 2012年6月11日
  作    者   : w00166186
  修改内容   : AT&T&DCM项目新增类型

*****************************************************************************/
enum NAS_MMC_NVIM_REG_DOMAIN_ENUM
{
    NAS_MMC_NVIM_REG_DOMAIN_CS = 1,
    NAS_MMC_NVIM_REG_DOMAIN_PS = 2,                                 /* 等待网侧结果定时器超时 */
    NAS_MMC_NVIM_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8;

/* Added by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, begin */
/*****************************************************************************
 枚举名    : NAS_MMC_UCS2_ENUM
 枚举说明  : UCS2 能力
 修改历史  :
 1.日    期    : 2013年03月11日
   作    者    : w00176964
   修改内容    : 新建
*****************************************************************************/

enum NAS_MMC_UCS2_ENUM
{
    NAS_MMC_UCS2_HAS_PREFER                                = 0,
    NAS_MMC_UCS2_NO_PREFER                                 = 1,

    NAS_MMC_UCS2_BUTT
};

typedef VOS_UINT16 NAS_MMC_UCS2_ENUM_UINT16;
/* Added by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, end */

/*****************************************************************************
 枚举名    : NV_MS_MODE_ENUM_UINT8
 结构说明  :  NV中记录的手机模式
  1.日    期   : 2011年8月18日
    作    者   : z00161729
    修改内容   : 新增
  2.日    期   : 2012年4月23日
    作    者   : w00166186
    修改内容   : DTS2012033104746,关机状态设置服务域为ANY不生效
*****************************************************************************/
enum NV_MS_MODE_ENUM
{
    NV_MS_MODE_CS_ONLY,                                                 /* 仅支持CS域 */
    NV_MS_MODE_PS_ONLY,                                                 /* 仅支持PS域 */
    NV_MS_MODE_CS_PS,                                                   /* CS和PS都支持 */

    NV_MS_MODE_ANY,                                                     /* ANY,相当于仅支持CS域 */

    NV_MS_MODE_BUTT
};
typedef VOS_UINT8 NV_MS_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
 结构说明  : 修改拒绝原因值，按照服务域进行区分
  1.日    期   : 2013年11月19日
    作    者   : l00208543
    修改内容   : 新增
*****************************************************************************/
enum NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_INACTIVE     = 0,        /* 功能不生效 */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_PS,                   /* 修改CS+PS的拒绝原因值 */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_ONLY,                 /* 仅修改CS域的拒绝原因值 */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_PS_ONLY,                 /* 仅修改PS域的拒绝原因值 */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8
 结构说明  : 频点重复搜索策略枚举
 1.日    期   : 2015年01月08日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
enum NAS_NVIM_CHAN_REPEAT_SCAN
{
    NAS_NVIM_CHAN_SCAN_NORMAL,
    NAS_NVIM_CHAN_REPEAT_SCAN_REACQ_0_1_2_3_4S,
    NAS_NVIM_CHAN_REPEAT_SCAN_PING_5,
    NAS_NVIM_CHAN_REPEAT_SCAN_2_7,

    NAS_NVIM_CHAN_REPEAT_SCAN_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8
 结构说明  : EPDSZID支持类型
 1.日    期   : 2015年01月10日
   作    者   : g00261581
   修改内容   : 新增
*****************************************************************************/
enum NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID,

    NAS_NVIM_EPDSZID_SUPPORT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8;


enum NAS_NVIM_LC_RAT_COMBINED_ENUM
{
    NAS_NVIM_LC_RAT_COMBINED_GUL,
    NAS_NVIM_LC_RAT_COMBINED_CL,

    NAS_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_ENUM_UINT8
 结构说明  : neg系统和 perf系统比较控制
 1.日    期   : 2015年6月9日
   作    者   : c00299063
   修改内容   : 新增
*****************************************************************************/
enum CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH,                /* Band Channel 模糊匹配 */
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_ACCURATE_MATCH,                 /* Band Channel 精确匹配*/
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU
 结构说明  : NV SrchHplmnFlg_ManualMode的结构

 1.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usManualSearchHplmnFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU;
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
 结构说明  : NV SrchHplmnFlg_ManualMode的结构结构

 1.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : 新建
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usAutoSearchHplmnFlg; /*Range:[0,3]*/
}NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU
 结构说明  : NV en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG 的结构结构

  1.日    期   : 2015年9月30日
    作    者   : c00318887
    修改内容   : 新建函数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;       /* ucActiveFlag 是否激活，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
 结构说明  : NV SrchHplmnFlg_AutoMode的结构结构

 1.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : 新建
 2.日    期   : 2015年3月2日
   作    者   : w00316404
   修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEHPlmnSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg的结构

 1.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : 新建
 2.日    期   : 2015年3月2日
   作    者   : w00316404
   修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStkSteeringOfRoamingSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NVIM_SCAN_CTRL_STRU
 结构说明  : 记录en_NV_Item_Scan_Ctrl_Para (9080)NV项内容，标识搜索控制功能是否使能
  1.日    期   : 2012年06月11日
    作    者   : l60609
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Scan_Ctrl_Para NV项是否激活，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           ucReserved1;                            /* 保留 */
    VOS_UINT8                           ucReserved2;                            /* 保留 */
    VOS_UINT8                           ucReserved3;                            /* 保留 */
}NVIM_SCAN_CTRL_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_PLMN_ID_STRU
 结构说明  : PLMN的结构

 1.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_NVIM_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_PLMN_ID_STRU
 结构说明  : en_NV_Item_Network_Name_From_MM_Info的结构

 1.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_NVIM_MAX_OPER_SHORT_NAME_LEN];/* 当前驻留网络运营商的短名称 */
    VOS_UINT8                           aucOperatorNameLong[NAS_NVIM_MAX_OPER_LONG_NAME_LEN];  /* 当前驻留网络运营商的长名称 */
}NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU
 结构说明  : en_NV_Item_OPERLOCK_PLMN_INFO NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBlackPlmnLockNum;                     /* 支持黑名单的个数,个数为0时表示不支持黑名单 */
    NAS_NVIM_PLMN_ID_STRU               astBlackPlmnId[NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU;
/*****************************************************************************
 结构名    : NAS_MMC_AIS_ROAMING_CFG_STRU
 结构说明  : 记录en_NV_Item_AIS_ROAMING_Config NV项内容
 1.日    期   : 2012年5月17日
   作    者   : z40661
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 该特性是否打开 */
    VOS_UINT8                           ucHighPrioRatType;                              /* 漫游支持的接入技术 */
    VOS_UINT8                           aucReserve[2];
    NAS_NVIM_PLMN_ID_STRU               stHighPrioPlmnId;                       /* 漫游支持的高优先级的PLMN ID ,即使驻留在HPLMN上,此PLMNID的优先级也较高*/
    NAS_NVIM_PLMN_ID_STRU               stSimHPlmnId;                           /* SIM卡的HPLMN ID */
}NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MML_USER_AUTO_RESEL_CFG_STRU
 结构说明  : 记录en_NV_Item_User_Auto_Resel_Switch NV项内容,UserResecl功能是否使能
 1.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAutoReselActiveFlg;                   /* 是否允许LTE国际漫游标记:VOS_TRUE 表示允许LTE国际漫游 VOS_FALSE 表示禁止LTE国际漫游 */
    VOS_UINT8                           ucReserve;
}NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU
 结构说明  :  en_NV_Item_PRIO_HPLMNACT_CFG NV项结构
 1.日    期   : 2012年6月9日
   作    者   : l00130025
   修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；目前USim卡中HPLMNACT很多不支持L
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;        /* NV有效标志, 1: 有效，0：无效 */
	VOS_UINT8                            ucReserved;      /* 四字节对齐 */
    VOS_UINT16                           usPrioHplmnAct;      /*定制的优先接入技术*/
}NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MML_NVIM_AVAIL_TIMER_CFG_STRU
 结构说明  : en_NV_Item_SEARCH_TIMER_INFO NV项结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer定时器第一次的时长 */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer定时器第一次的次数 */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer定时器深睡的时长 */
    VOS_UINT32                          ulDeepSearchTimeCount;
}NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_T3212_TIMER_CFG_STRU
 结构说明  : en_NV_Item_SEARCH_TIMER_INFO NV项结构
  1.日    期   : 2015年3月14日
    作    者   : w00167002
    修改内容   : 新建

    BIT0控制: LAUU建联时候失败启动T3212场景
    ulT3212StartSceanCtrlBitMask1 BIT0:             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL
    BIT1控制: LAU建联时候被REL启动T3212场景
    ulT3212StartSceanCtrlBitMask1 BIT1:             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNvActiveFlg;                          /* 控制当前NV是否使能 */
    VOS_UINT32                          ulT3212StartSceneCtrlBitMask;           /* BIT0~BIT31,用于控制链路失败后启动T3212时，是否使用当前NV配置的时长 */
    VOS_UINT32                          ulT3212Phase1TimeLen;                   /* t3212定时器第1阶段的时长,单位为s */
    VOS_UINT32                          ulT3212Phase1Count;                     /* t3212定时器第1阶段的次数 */
    VOS_UINT32                          ulT3212Phase2TimeLen;                   /* t3212定时器第2阶段的时长,单位为s  */
    VOS_UINT32                          ulT3212Phase2Count;                     /* t3212定时器第2阶段的次数 */
}NAS_MMC_NVIM_T3212_TIMER_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU
 结构说明  : en_NV_Item_OPERLOCK_PLMN_INFO_WHITE NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWhitePlmnLockNum;                     /* 支持白名单的个数,个数为0时表示不支持白名单 */
    NAS_NVIM_PLMN_ID_STRU               astWhitePlmnId[NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_SUPPORT_CPHS_FLAG NV项结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_PREVENT_TEST_IMSI_REG_STRU
 结构说明  : en_NV_Item_PREVENT_TEST_IMSI_REG结构
  1.日    期   : 2012年2月22日
    作    者   : w00199382
    修改内容   : 移植
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /*是否激活，0不激活，1激活 */
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_PREVENT_TEST_IMSI_REG_STRU;
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 结构名    : NAS_PREVENT_TEST_IMSI_REG_STRU
 结构说明  : en_NV_Item_PREVENT_TEST_IMSI_REG结构
  1.日    期   : 2012年2月22日
    作    者   : w00199382
    修改内容   : 移植
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnSearchPowerOn;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU;


/*****************************************************************************
 结构名    : NAS_PREVENT_TEST_IMSI_REG_STRU
 结构说明  : NAS_PREVENT_TEST_IMSI_REG_STRU结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 移植
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTinType;                              /* TIN类型 */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_NVIM_ITEM_MAX_IMSI_LEN];        /* 上次保存的IMSI的内容 */
}NAS_NVIM_TIN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_PREVENT_TEST_IMSI_REG_STRU
 结构说明  : NAS_PREVENT_TEST_IMSI_REG_STRU结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 移植
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulAutoStart;
}NAS_MMA_NVIM_AUTO_START_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU
 结构说明  : en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT NV项结构
  1.日    期   : 2011年8月5日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSingleDomainFailPlmnSrchFlag;         /* DT定制需求，单域注册被拒后，需要出发搜网 */
    VOS_UINT8                           ucReserved;                             /* 保留*/
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU;

/*****************************************************************************
 结构名    : NAS_PREVENT_TEST_IMSI_REG_STRU
 结构说明  : NAS_PREVENT_TEST_IMSI_REG_STRU结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 移植
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPsLocInfo[NAS_NVIM_PS_LOCI_SIM_FILE_LEN];
}NAS_NVIM_PS_LOCI_SIM_FILES_STRU;

/*****************************************************************************
 结构名    : NAS_MML_NVIM_GPRS_GEA_ALG_CTRL_STRU
 结构说明  : en_NV_Item_GEA_SUPPORT_CTRL NV项结构
 1.日    期   : 2011年7月14日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucStatus;                                /* NV是否激活标志, 0: 不激活，1: 激活 */
    VOS_UINT8                          ucGeaSupportCtrl;                        /* 终端配置:GPRS GEA算法支持控制 */
}NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_LTE_CS_SERVICE_CFG_STRU
 结构说明  : 记录en_NV_Item_Lte_Cs_Service_Config NV项内容，LTE支持的cs业务能力
  1.日    期   : 2011年10月28日
    作    者   : z00161729
    修改内容   : 新建
  2.日    期   : 2013年09月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目，修改结构体名称
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;    /* en_NV_Item_Lte_Cs_Service_Config NV项是否激活，VOS_TRUE:激活；VOS_FALSE:未激活 */
    VOS_UINT8                           ucLteCsServiceCfg;  /* LTE支持的 cs域业务能力*/
}NAS_NVIM_LTE_CS_SERVICE_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU
 结构说明  : NVIM项中的配置CSFB HO流程等系统消息时长，NV项未激活则不等系统消息直接注册
 1.日    期   : 2012年2月14日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucWaitSysinfoTimeLen;
}NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU;



/*****************************************************************************
 结构名    : NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU
 结构说明  : en_NV_Item_Lte_Internation_Roam_Config NV项结构
 1.日    期   : 2012年3月14日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2012年4月25日
   作    者   : w00176964
   修改内容   : DTS2012042403564:修改NV读取的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           aucRoamEnabledMccList[20];/* 允许漫游的国家码列表 */
}NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ROAM_RPLMN_SEARCH_CFG_STRU
 结构说明  : en_NV_Item_Roam_Search_Rplmn_Config NV项结构
 1.日    期   : 2014年2月24日
   作    者   : t00173447
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamRplmnflg;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                         aucRoamEnabledMccList[5];/* 允许漫游的国家码列表 */
}NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU;

/* Modified by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, begin */
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU
 结构说明  : en_NV_Item_Close_SMS_Capability_Config NV项结构
 1.日    期   : 2013年3月11日
   作    者   : w00176964
   修改内容   : close sms capability NV结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU;
/* Modified by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, end */

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_STRU
 结构说明  : en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG NV项结构
  1.日    期   : 2012年03月03日
    作    者   : S62952
    修改内容   : 新建
  2.日    期   : 2013年12月13日
    作    者   : z00161729
    修改内容   : DTS2013121206933:非高优先级可用高低质量的网络按syscfg设置接入技术优先级排序，9055 nv项控制
  3.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWcdmaPriorityGsmFlg;                  /* H3G定制需求，W网络优先于G*/

    VOS_UINT8                           ucSortAvailalePlmnListRatPrioFlg;    /* 是否按syscfg设置接入技术优先级排序高低质量搜网列表标识，1:是; 0:不是高质量网络按随机排序低质量网络不排序*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG NV项结构
  1.日    期   : 2012年03月03日
    作    者   : S62952
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPsOnlyCsServiceSupportFlg;            /* 服务域设置为PS ONLY时，是否支持CS域短信和呼叫业务(紧急呼叫除外)*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_NVIM_CCBS_SUPPORT_FLG NV项结构
  1.日    期   : 2012年03月03日
    作    者   : S62952
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /* CCBS(遇忙呼叫完成)业务*/
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}NAS_NVIM_CCBS_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU
 结构说明  : en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT NV项结构
 1.日    期   : 2012年6月11日
   作    者   : W00166186
   修改内容   : AT&T&t&DCM新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          aulCustommMccList[10];                   /* 允许漫游的国家码列表 */
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU;


/*****************************************************************************
 结构名    : NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU
 结构说明  : en_NV_Item_ACTING_PLMN_SUPPORT_FLAG NV项结构
  1.日    期   : 2011年06月11日
    作    者   : W00166186
    修改内容   : AT&T&DCM新建结构
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU
 结构说明  : en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG NV项结构
  1.日    期   : 2011年06月11日
    作    者   : W00166186
    修改内容   : AT&T&DCM新建结构
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;                            /* 保留*/
    VOS_UINT8                           ucReserved2;                            /* 保留*/
    VOS_UINT8                           ucReserved3;                            /* 保留*/
}NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU;



/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
 结构说明  : 单域注册被拒定制动作结构
 1.日    期   : 2012年6月11日
   作    者   : W00166186
   修改内容   : AT&T&t&DCM新建
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enRegCause;
    NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8                      enDomain;
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enAction;
}NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
 结构说明  : 单域注册被拒定制en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST结构
 1.日    期   : 2012年6月11日
   作    者   : W00166186
   修改内容   : AT&T&t&DCM新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               auReserv[2];
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU         astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_SIM_FORMAT_PLMN_ID
 结构说明  : Sim PLMN ID的存储结构
 1.日    期   : 2011年5月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_SIM_FORMAT_PLMN_ID;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_NVIM_CURRENT_UTRAN_MODE_STRU
 结构说明  : 记录en_NV_Item_Utran_Mode NV项内容
 1.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseI:新加
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranMode;                            /* 当前支持的UTRAN模式 */
    VOS_UINT8                           ucReserve;
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU
 结构说明  : 记录en_NV_Item_Utran_Mode_Auto_Switch NV项内容
 1.日    期   : 2012年8月7日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0：UTRAN模式为FDD 1：UTRAN模式为TDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* 支持TD网络的国家号个数 */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* 根据IMS PLMN决定UTRAN模式是否AUTO SWITCH时，当前IMSI的PLMN在此列表中的都支持自动切换，否则固定为W模 */
    VOS_UINT8                           aucReserve[1];

    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU;




/*****************************************************************************
 结构名    : NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU
 结构说明  : en_NV_Item_UTRAN_TDD_SMC_FLAG NV项结构
 1.日    期   : 2013年7月25日
   作    者   : w00167002
   修改内容   : 控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                TD下不发起SMC流程。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;                /* 控制在3G TDD模式下是否需要开启CS SMC验证标记:0-不需要；1-需要 */
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;                /* 控制在3G TDD模式下是否需要开启PS SMC验证标记:0-不需要；1-需要 */
    VOS_UINT8                           aucReserved[2];                         /* 保留 */
}NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU
 结构说明  : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU结构，控制非HPLMN/RPLMN
             网络接入禁止后是否发起PLMN搜网 en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG
 1.日    期   : 2013年10月15日
   作    者   : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   aucReserve[3];
}NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU
 结构说明  : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU NVIM项中的用户设置的OPLMN
 1.日    期   : 2013年10月15日
   作    者   : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* 定制项使能标志 */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* 是否有IMSI列表的白名单，0:不需要 1:需要 */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* 本地配置的版本号 */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* 定制的IMSI列表个数 */
    VOS_UINT8                           ucOplmnListNum;                                       /* 本地配置的Oplmn的个数 */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN];/* OPLMN的PDU数据，和EFOplmn文件一致 */
}NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU
 结构说明  : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU NVIM项中的用户设置的OPLMN
 1.日    期   : 2013年11月26日
   修改内容   : 将NV支持的最大OPLMN个数扩展到256个
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* 定制项使能标志 */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* 是否有IMSI列表的白名单，0:不需要 1:需要 */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* 本地配置的版本号 */
    VOS_UINT16                          usOplmnListNum;                                       /* 本地配置的Oplmn的个数 */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* 定制的IMSI列表个数 */
    VOS_UINT8                           aucReserve[3];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN];/* OPLMN的PDU数据，和EFOplmn文件一致 */
}NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU;


/* Added by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-28, begin */
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 结构说明  : en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg NVIM
            en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg
            en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg
            中的DPLMN NPLMN功能信息
 1.日    期   : 2015年5月28日
   作    者   : c00318887
   修改内容   : 漫游优化搜网DPlmn扩容和优先接入HPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* 本地配置的Dplmn的个数 */
    VOS_UINT16                         usNplmnListNum;                                       /* 本地配置的Nplmn的个数 */

    /* DPLMN数据,每7个字节代表一个dplmn信息，第1-3个字节为sim卡格式plmn id，
       第4-5字节为支持的接入技术(0x8000为支持w，0x4000为支持lte，0x0080为支持gsm)，
       第6字节为域信息:1(cs域注册成功)；2(ps域注册成功)；3(cs ps均注册成功)
       第7直接为预置标示信息: 1(预置Dplmn), 0(自学习到的DPLMN) */
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN];

    /* NPLMN数据,每7个字节代表一个nplmn信息，第1-3个字节为sim卡格式plmn id，
       第4-5字节为支持的接入技术(0x8000为支持w，0x4000为支持lte，0x0080为支持gsm)，
       第6字节为域信息:1(cs域注册成功)；2(ps域注册成功)；3(cs ps均注册成功)
       第7直接为预置标示信息: 1(预置nplmn), 0(自学习到的nplmn) */
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN];/* NPLMN数据*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 结构说明  : en_NV_Item_CMCC_Cfg_Dplmn_Nplmn NVIM
            en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn
            en_NV_Item_CT_Cfg_Dplmn_Nplmn
            中的DPLMN NPLMN功能信息
 1.日    期   : 2014年7月14日
   作    者   : c00188733
   修改内容   : 漫游优化搜网方案新增DPLMN NPLMN
 2.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* 本地配置的Dplmn的个数 */
    VOS_UINT16                         usNplmnListNum;                                       /* 本地配置的Nplmn的个数 */

    /* DPLMN数据,每6个字节代表一个dplmn信息，第1-3个字节为sim卡格式plmn id，
       第4-5字节为支持的接入技术(0x8000为支持w，0x4000为支持lte，0x0080为支持gsm)，第6字节为域信息:1(cs域注册成功)；2(ps域注册成功)；3(cs ps均注册成功)*/
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN];

    /* NPLMN数据,每6个字节代表一个nplmn信息，第1-3个字节为sim卡格式plmn id，
       第4-5字节为支持的接入技术(0x8000为支持w，0x4000为支持lte，0x0080为支持gsm)，第6字节为域信息:1(cs域注册成功)；2(ps域注册成功)；3(cs ps均注册成功)*/
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN];/* NPLMN数据*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_OLD_STRU;
/* Added by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-28, end */

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU
 结构说明  : en_NV_Item_Cfg_Dplmn_Nplmn_Flag NVIM
 1.日    期   : 2014年7月14日
   作    者   : c00188733
   修改内容   : 漫游优化搜网方案新增DPLMN NPLMN使能标志
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usCfgDplmnNplmnFlag;
    VOS_UINT8                          ucCMCCHplmnNum;
    VOS_UINT8                          aucCMCCHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucUNICOMHplmnNum;
    VOS_UINT8                          aucUNICOMHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucCTHplmnNum;
    VOS_UINT8                          aucCTHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          aucReserve[3];
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU
 结构说明  : en_NV_Item_Cfg_Dplmn_Nplmn_Flag NVIM
 1.日    期   : 2015年10月20日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEHplmnNum;
    VOS_UINT8                           aucEHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                           aucVersionId[NAS_MCC_NVIM_VERSION_LEN];
    VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU;



/*****************************************************************************
 结构名    : NAS_MML_USER_CFG_EHPLMN_INFO_STRU
 结构说明  : en_NV_Item_User_Cfg_Ehplmn NVIM项中的用户配置的Ehplmn List
 1.日    期   : 2012年8月9日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:CMCC内置EHPLMN功能
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* 定制的IMSI列表个数 */
    VOS_UINT8                           ucEhplmnListNum;                        /* 用户配置的EHplmn的个数 */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astEhPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU
 结构说明  : en_NV_Item_User_Cfg_Ehplmn NVIM项中的用户配置的扩充的Ehplmn List组
 1.日    期   : 2014年12月19日
   作    者   : wx270776
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulNvimEhplmnNum;
    NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU    astNvimEhplmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_PLMN_WITH_RAT_STRU
 结构说明  : NAS MML PLMN和接入技术结构
 1.日    期   : 2012年8月9日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_NVIM_PLMN_WITH_RAT_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU
 结构说明  : en_NV_Item_DISABLED_RAT_PLMN_INFO NV项结构
  1.日    期   : 2012年8月15日
    作    者   : w00176964
    修改内容   : 新建
  2.日    期   : 2015年4月18日
    作    者   : w00167002
    修改内容   : DTS2015032709270:NV中最大禁止网络的个数为8个。
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDisabledRatPlmnNum;                   /* 支持禁止接入技术的PLMN个数,个数为0表示不支持该特性 */

    NAS_MMC_NVIM_PLMN_WITH_RAT_STRU     astDisabledRatPlmnId[NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM];/* 禁止接入技术的PLMN和RAT信息 */

}NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU;

/*****************************************************************************
 枚举名    : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
 结构说明  :
 1.日    期: 2013年11月01日
   作    者: l00208543
   修改内容: 新增
*****************************************************************************/
enum NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /* 功能未激活 */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /* 开启黑名单功能 */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /* 开启白名单功能 */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
 结构说明  :
 1.日    期: 2013年11月01日
   作    者: l00208543
   修改内容: 新增
*****************************************************************************/
enum NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRAN包括WCDMA/TDS-CDMA */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8;


enum NAS_MSCC_NVIM_SYS_PRIORITY_CLASS_ENUM
{
    NAS_MSCC_NVIM_SYS_PRI_CLASS_HOME             = 0,    /* home or ehome plmn */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_PREF             = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ANY              = 2,    /* Acceptable PLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU
 结构说明  : en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config NV项结构
  1.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 新建

    ucSwitchFlag        功能类型：0不激活；
                                  1: astImsiPlmnList 名单内的卡启用禁止RAT功能；
                                  2：对不在astImsiPlmnList 名单中的卡启用禁止RAT功能
    ucImsiPlmnListNum   SIM卡数目；最大支持16；
    ucForbidRatListNum  禁止RAT的数目，最大值支持 8；（目前仅支持NV中配置禁止LTE或者禁止LTE+UTRAN，
                                                       NV中配置其他禁止网络制式的组合认为是非法参数）
    astImsiPlmnList     SIM卡列表，最大支持16组
    aucForbidRatList    禁止的RAT，最大值支持 2；（目前仅支持NV中配置禁止LTE或者禁止LTE+UTRAN，
                                                   NV中配置其他禁止网络制式的组合认为是非法参数）
                        0: GSM
                        1: UTRAN
                        2: E-UTRAN
                        其他值为无效值
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8  enSwitchFlag;                                         /*功能是否有效及功能的类型  */
    VOS_UINT8                                               ucImsiListNum;                                        /*功能起效的SIM卡数目(黑名单/白名单)  */
    VOS_UINT8                                               ucForbidRatNum;                                       /*禁止RAT的数目  */
    VOS_UINT8                                               aucReserve[1];
    NAS_SIM_FORMAT_PLMN_ID                                  astImsiList[NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM];        /* SIM卡列表 (黑名单/白名单) */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            aenForbidRatList[NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM];    /*禁止的接入技术  */
}NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU
 结构说明  : NVIM项中的配置csfb 紧急呼到gu后lai改变，mm先进行lau还是先进行呼叫
 1.日    期   : 2012年8月14日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT8                           aucRserved[1];
}NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU;
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
 结构说明  : en_NV_Item_PLMN_EXACTLY_COMPARE_FLG NV项结构
  1.日    期   : 2012年08月16日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题,新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;
    VOS_UINT8                           aucRsv[3];                         /* 保留*/
}NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU
 结构说明  : en_NV_Item_Hplmn_Register_Ctrl_Flg NV项结构
 1.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : HPLMN注册被拒后是否允许注册标记
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMN注册控制标记 */
    VOS_UINT8                           aucRsv[3];                              /* 保留 */
}NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU;
/*****************************************************************************
结构名    : NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU
结构说明  : 信号质量主动上报相关配置信息
1.日    期  : 2012年11月21日
  作    者  : z00161729
  修改内容  : 支持^cerssi新增结构
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSignThreshold;    /* 信号变化门限,当RSSI变化超过该值，
                                                                                  接入层需要主动上报信号质量，取值0表示接入层按默认值处理 */
    VOS_UINT8                                               ucMinRptTimerInterval;     /* 间隔上报的时间   */
    VOS_UINT8                                               ucRserved1;
    VOS_UINT8                                               ucRserved2;
} NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU
 结构说明  : en_NV_Item_H3g_Ctrl_Flg NV项结构
 1.日    期   : 2013年4月10日
   作    者   : w00176964
   修改内容   : H3G定制场景控制标记
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucH3gCtrlFlg;                           /* H3G定制标记 */
    VOS_UINT8                           aucRsv[3];                              /* 保留 */
}NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU
 结构说明  : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 移植
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUcs2Customization;
    VOS_UINT8                           ucRserved1;
    VOS_UINT8                           ucRserved2;
}NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU;

/*****************************************************************************
 结构名    : SMS_TIMER_LENGTH_STRU
 结构说明  : 短信协议定时器时长结构

1. 日    期   : 2012年12月28日
   作    者   : l00167671
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_NVIM_TIMER_LENGTH_STRU;


/*****************************************************************************
 结构名    : NVIM_PRIVATE_CMD_STATUS_RPT_STRU
 结构说明  : 是否主动上报信息
 1.日    期   : 2013年5月10日
   作    者   : s00217060
   修改内容   : 主动上报AT命令控制下移至C核项目主动上报NV结构体定义
 2.日    期   : 2015年3月2日
   作    者   : w00316404
   修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志, 0: 不激活，1: 激活 */
    VOS_UINT8                           ucStatusRptGeneralControl;        /* 私有命令是否允许状态上报 0:不上报，1:上报 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NVIM_PRIVATE_CMD_STATUS_RPT_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SPECIAL_ROAM_STRU
 结构说明  : en_NV_Item_Special_Roam_Flag NV项结构
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志, 0: 不激活，1: 激活  */
    VOS_UINT8                           ucSpecialRoamFlg;                         /* Vplmn与Hplmn不同国家码时,是否允许回到Hplmn,1:允许，0:不允许 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SPECIAL_ROAM_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU
 结构说明  : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnhancedHplmnSrchFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_CC_NVIM_TIMER_LEN_STRU
 结构说明  : NAS_CC_NVIM_TIMER_LEN_STRU结构en_NV_Item_CC_TimerLen
  1.日    期   : 2013年8月30日
    作    者   : l00208543
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucT305Len;
    VOS_UINT8   ucT308Len;
    VOS_UINT8   aucReserve[2];
}NAS_CC_NVIM_TIMER_LEN_STRU;

/*****************************************************************************
 结构名    : NAS_CC_NVIM_T303_LEN_CFG_STRU
 结构说明  : NAS_CC_NVIM_T303_LEN_CFG_STRU结构en_NV_Item_CC_T303_Len_Cfg
  1.日    期   : 2015年3月20日
    作    者   : wx270776
    修改内容   : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT303ActiveFlag;                       /* 是否开启T303定时器。0:关闭，1:开启。*/
    VOS_UINT8                           ucT303Len;                              /* T303定时器时长 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_CC_NVIM_T303_LEN_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU
 结构说明  : 结构
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucCmSrvExistTrigPlmnSearch;                                                     /* 业务存在时是否触发搜网 */
    VOS_UINT8   ucCmSrvTrigPlmnSearchCauseNum;                                                  /* 配置业务存在时触发搜网的被拒原因值个数 */
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucCmSrvTrigPlmnSearchCause[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];   /* 配置业务存在时触发搜网的被拒原因值 */
    VOS_UINT8   aucReserve[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];                    /* 预留给注册被拒触发搜网使用 */
}NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU
 结构说明  : 结构
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucLauRejCauseNum;
    VOS_UINT8   ucLauRejTimes;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucLauRejCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
}NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU
 结构说明  : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU结构en_NV_Item_ChangeRejectCause_Flg
  1.日    期   : 2013年10月09日
    作    者   : l00208543
    修改内容   : 新建
  2.日    期   : 2013年11月19日
    作    者   : l00208543
    修改内容   : 修改，将控制位改为枚举，增加单域控制
*****************************************************************************/
typedef struct
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8           enChangeRegRejCauCfg;
    VOS_UINT8   ucPreferredRegRejCau_HPLMN_EHPLMN;             /* HPLMN/EHPLMN时使用的拒绝原因值 */
    VOS_UINT8   ucPreferredRegRejCau_NOT_HPLMN_EHPLMN;         /* 非HPLMN/EHPLMN时使用的拒绝原因值 */
    VOS_UINT8   aucReserve[1];
}NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU
 结构说明  : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU结构en_NV_Item_ROAMING_REJECT_NORETRY_CFG
  1.日    期   : 2014年4月29日
    作    者   : l00208543
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucNoRetryRejectCauseNum;
    VOS_UINT8   aucNoRetryRejectCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
    VOS_UINT8   aucReserve[3];
}NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU
 结构说明  : en_NV_Item_Remove_Auth_Rej_CFG NV项结构


 1.日    期   : 2014年2月18日
   作    者   : l00215384
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
   VOS_UINT8                           ucIgnoreAuthRejFlg;
   VOS_UINT8                           ucMaxAuthRejNo;
   VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NV_GWMAC_ADDR_STRU
 结构说明  : NV_GWMAC_ADDR(39026)结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved1;
    VOS_UINT8 aucE5GwMacAddr[18];
}NAS_NV_GWMAC_ADDR_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU
 结构说明  : E5_RoamingWhiteList_Support_Flg(39330)结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucE5_RoamingWhiteList_Support_Flg[2];
}NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU
 结构说明  : NDIS_DIALUP_ADDRESS(39330)结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNDIS_DIALUP_ADDRESS;
}NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_NV_BREATH_LED_STR_STRU
 结构说明  : NV_BREATH_LED_STR(9051)结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucBreOnTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreOffTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreRiseTime; /*Range:[0,5]*/
    VOS_UINT8 ucBreFallTime; /*Range:[0,5]*/
}NAS_NVIM_NV_BREATH_LED_STR_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_NV_WIFI_Key_STRU
 结构说明  : NV_WIFI_Key(50012)结构(废弃)
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
VOS_UINT8  aucwlAuthMode[16];
VOS_UINT8  aucBasicEncryptionModes[5];
VOS_UINT8  aucWPAEncryptionModes[5];
VOS_UINT8  aucwlKeys1[27];
VOS_UINT8  aucwlKeys2[27];
VOS_UINT8  aucwlKeys3[27];
VOS_UINT8  aucwlKeys4[27];
VOS_UINT32 ulwlKeyIndex;
VOS_UINT8  aucwlWpaPsk[65];
VOS_UINT8  ucwlWpsEnbl;
VOS_UINT8  ucwlWpsCfg;
VOS_UINT8  ucReserved;
}NAS_NVIM_NV_WIFI_KEY_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_NV_PRI_VERSION_STRU
 结构说明  : NV_PRI_VERSION(50023)结构
  1.日    期   : 2013年5月22日
    作    者   : l00167671
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
VOS_UINT8 aucPRIVersion[32];
VOS_UINT8 aucReserve[32];
}NAS_NVIM_NV_PRI_VERSION_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_SYSTEM_APP_CONFIG_STRU
结构说明  : en_NV_Item_System_APP_Config(121)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSysAppConfigType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SYSTEM_APP_CONFIG_STRU;

/*****************************************************************************
结构名    : NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU
结构说明  : en_NV_Item_NetworkCapability(8197)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNetworkCapability[NV_ITEM_NET_CAPABILITY_MAX_SIZE];
}NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_AUTOATTACH_STRU
结构说明  : en_NV_Item_Autoattach(8202)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAutoattachFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_AUTOATTACH_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_SELPLMN_MODE_STRU
结构说明  : en_NV_Item_SelPlmn_Mode(8214)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSelPlmnMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SELPLMN_MODE_STRU;

/*****************************************************************************
结构名    : NAS_MMA_NVIM_ACCESS_MODE_STRU
结构说明  : en_NV_Item_MMA_AccessMode(8232)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAccessMode[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_ACCESS_MODE_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_MS_CLASS_STRU
结构说明  : en_NV_Item_MMA_MsClass(8233)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsClass;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_MS_CLASS_STRU;

/*****************************************************************************
结构名    : NAS_MMA_NVIM_RF_Auto_Test_Flag_STRU
结构说明  : en_NV_Item_RF_Auto_Test_Flag(8262)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRfAutoTestFlg;
}NAS_MMA_NVIM_RF_AUTO_TEST_FLAG_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_HPLMN_FIRST_TIMER_STRU
结构说明  : en_NV_Item_HPlmnFirstTimer(8276)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnTimerLen;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}NAS_NVIM_HPLMN_FIRST_TIMER_STRU;

/*****************************************************************************
结构名    : NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU
结构说明  : en_NV_Item_NAS_Supported_3GPP_Release(8288)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSupported3GppRelease[NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE];
}NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU;

/*****************************************************************************
结构名    : NAS_MMC_NVIM_LAST_IMSI_STRU
结构说明  : en_NV_Item_Last_Imsi(8325)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucValid;
    VOS_UINT8   aucImsi[NAS_MMC_NVIM_MAX_IMSI_LEN];
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_LAST_IMSI_STRU;

/*****************************************************************************
结构名    : NAS_MMA_NVIM_ROAMING_BROKER_STRU
结构说明  : en_NV_Item_Roaming_Broker(8328)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucRoamingBroker[2];
}NAS_MMA_NVIM_ROAMING_BROKER_STRU;

/*****************************************************************************
结构名    : NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU
结构说明  : en_NV_Item_Use_Single_Rplmn_When_Area_Lost(8343)结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usUseSingleRplmnFlag;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU;

/* en_NV_Item_EquivalentPlmn 8215 */
/*****************************************************************************
结构名    : NVIM_PLMN_VALUE_STRU
结构说明  : en_NV_Item_EquivalentPlmn(8215)结构引用#
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_VALUE_STRU;

/*****************************************************************************
结构名    : NVIM_EQUIVALENT_PLMN_LIST_STRU
结构说明  : en_NV_Item_EquivalentPlmn(8215)结构#
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8             ucCount;
    NVIM_PLMN_VALUE_STRU  struPlmnList[NVIM_MAX_EPLMN_NUM];
    VOS_UINT8             aucReserve[3];   /*NV项相关的结构体，在4字节方式下，需手动补齐空洞*/
}NVIM_EQUIVALENT_PLMN_LIST_STRU;

/*en_NV_Item_Support_Freqbands 8229*/
/*
NVIM_UE_SUPPORT_FREQ_BAND_STRU结构说明:
usWcdmaBand和usGsmBand用Bit位表示用户设置的频段，bit1代表频段I,bit2代表频段II,
依次类推,比特位为1,表示支持该频段.下表是比特位和频段对应关系:
-------------------------------------------------------------------------------
        bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
-------------------------------------------------------------------------------
WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
        spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
-------------------------------------------------------------------------------
GSM频段 1900(VIII) 1800(VII) E900(VI) R900(V) P900(IV) 850(III)  480(II)  450(I)  oct3
        spare      spare     spare    spare   spare    spare     spare    700(IX) oct4
-------------------------------------------------------------------------------
aucUeSupportWcdmaBand和aucUeSupportGsmBand用数组表示UE支持的频段,并以存储顺序的
先后表示频段优先顺序,用0xff表示无效.

例如:
oct1-oct4分别是：0x03,0x00,0x7B,0x00
   则代表用户设置频段为：W：WCDMA-I-2100, WCDMA-II-1900
                         G：850(III),P900(IV),R900(V),E900(VI),1800(VII)
oct5-oct16分别是:2,5,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
   则代表UE支持W频段I,II,V,优先顺序是:II,V,I.
oct17-oct28分别是:4,5,8,7,6,3,0xff,0xff,0xff,0xff,0xff,0xff
   则代表UE支持G频段III,IV,V,VI,VII,VIII,优先顺序是:IV,V,VIII,VII,VI,III.
*/
/*****************************************************************************
结构名    : NAS_NVIM_UE_SUPPORT_FREQ_BAND_STRU
结构说明  : en_NV_Item_Support_Freqbands(8229)结构#
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2014年8月1日
  作    者   : b00269685
  修改内容   : NV拆分
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT32                  ulGsmBand;
    VOS_UINT8                   aucReserved1[12];
    VOS_UINT8                   aucReserved2[12];
    VOS_UINT8                   aucReserved[24];        /* 为保证nv长度一致保留 */
}NVIM_UE_SUPPORT_FREQ_BAND_STRU;

/*en_NV_Item_Roam_Capa 8266*/
/*****************************************************************************
 结构名    : NAS_NVIM_ROAM_CFG_INFO_STRU
 结构说明  : en_NV_Item_Roam_Capa(8266) NV项结构#
  1.日    期   : 2011年8月18日
    作    者   : z00161729
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*记录漫游特性是否激活,VOS_FALSE:不激活,VOS_TRUE:激活*/
    VOS_UINT8                               ucRoamCapability;                   /*记录用户设置的漫游属性*/
    VOS_UINT8                               ucReserve1;
    VOS_UINT8                               ucReserve2;
}NAS_NVIM_ROAM_CFG_INFO_STRU;

/*en_NV_Item_CustomizeService 8271*/
/*****************************************************************************
结构名    : NAS_NVIM_CUSTOMIZE_SERVICE_STRU
结构说明  : en_NV_Item_CustomizeService(8271)结构#
            用于保存运营商定制要求业务配置
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;           /*是否激活，0不激活，1激活 */
    VOS_UINT32                          ulCustomizeService; /*终端说明书是1个byte，为了没有空洞，扩充成4byte，高3byte保留*/
}NAS_NVIM_CUSTOMIZE_SERVICE_STRU;

/*en_NV_Item_RPlmnWithRat 8275*/
/*****************************************************************************
 结构名    : NAS_MM_NVIM_RPLMN_WITH_RAT_STRU
 结构说明  : en_NV_Item_RPlmnWithRat(8275) NV项结构
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stGRplmn;                               /* G RPLMN信息 */
    NAS_NVIM_PLMN_ID_STRU               stWRplmn;                               /* W RPLMN信息*/
    VOS_UINT8                           ucLastRplmnRat;                         /* 上次关机时驻留网络的接入技术0:GSM;1:WCDMA;0xFF:无效值 */
    VOS_UINT8                           ucLastRplmnRatEnableFlg;                /* 0:NV 未激活; 1:NV激活 */
    VOS_UINT8                           aucReserved[2];                          /* 保留 */
}NAS_NVIM_RPLMN_WITH_RAT_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU
 结构说明  : en_NV_Item_SearchHplmnTtimerValue NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;                              /* 0:NV 未激活; 1:NV 激活 */
    VOS_UINT8                            ucReserve;                             /* 保留未用 */
    VOS_UINT16                           usSrchHplmnTimerValue;                 /* VPLMN下非首次搜HPLMN时间,单位:分钟 */

}NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU;

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
/*****************************************************************************
 结构名    : NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU
 结构说明  : en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG NV项结构
 1.日    期   : 2015年4月28日
   作    者   : c00318887
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTriggerBGSearchFlag;  /* 0: mmc收到高优先级PLMN更新时不启动BG SEARCH; 1:mmc收到高优先级PLMN更新时启动BG SEARCH */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usSearchDelayLen;             /* BG SEARCH Delay 时长, 单位: 秒  */
}NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU;

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */


/*en_NV_Item_EFust_Service_Cfg 8285*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU
 结构说明  : en_NV_Item_EFust_Service_Cfg(8285) NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV项是否激活0：未激活；1：激活 */
    VOS_UINT8                           ucForbidReg2GNetWork;                   /* 0：EFust GSM接入标志定制项去使能。定制项不激活，不检查EFust 27、38。允许GSM接入。
                                                                                   定制项激活，该定制项激活后，UE根据SIM卡中的EFust 27、38位，确定是否允许GSM接入，
                                                                                   如果EFUST文件禁止这两位（同时设置为0），则禁止GSM接入注册，否则GSM可以接入。
                                                                                   注意：SIM卡中不存在EFust 27、38位，因此该功能仅针对USIM卡有效。1：EFust GSM接入标志定制项使能 */
    VOS_UINT8                           ucForbidSndMsg;                         /* 0：EFust短信发送标志定制项去使能。定制项不激活，不检查EFust 10、12。允许SMS发送。
                                                                                   1：EFust短信发送标志定制项使能。NV项激活，该定制项激活后，UE根据SIM卡中EFUST的10、12位，
                                                                                   确定是否禁止短信发送,如果禁止这两位（同时设置为0），则禁止发送SMS；否则，短信可以发送。*/
    VOS_UINT8                           ucReserved[13];
}NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU;

/*en_NV_Item_UE_MSCR_VERSION 8289*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_MSCR_VERSION_STRU
 结构说明  : en_NV_Item_UE_MSCR_VERSION(8289) NV项结构
 1.日    期   : 2011年7月14日
   作    者   : z00161729
   修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志, 0: 不激活，1: 激活 */
    VOS_UINT8                           ucUeMscrVersion;                        /* 终端上报的SGSN版本 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MSCR_VERSION_STRU;

/*en_NV_Item_UE_SGSNR_VERSION 8290*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SGSNR_VERSION_STRU
 结构说明  : en_NV_Item_UE_SGSNR_VERSION(8290) NV项结构
 1.日    期   : 2011年7月14日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2015年3月2日
   作    者   : w00316404
   修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志, 0: 不激活，1: 激活 */
    VOS_UINT8                           ucUeSgsnrVersion;                       /* 终端上报的SGSN版本 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SGSNR_VERSION_STRU;

/*en_NV_Item_SteeringofRoaming_SUPPORT_CTRL 8292*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU
 结构说明  : en_NV_Item_SteeringofRoaming_SUPPORT_CTRL(8292) NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志, 0: 不激活，1: 激活 */
    VOS_UINT8                           ucCsRejSearchSupportFlg;                /* vodafone的搜网定制需求,CS域失败四次后下发搜网请求,VOS_FALSE:不支持,VOS_TRUE:支持 */
}NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU;

/*en_NV_Item_Max_Forb_Roam_La 8320*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU
 结构说明  : en_NV_Item_Max_Forb_Roam_La(8320) NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxForbRoamLaFlg;                     /* NV中设置的最大禁止LA个数是否有效: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucMaxForbRoamLaNum;                     /* NV中设置的最大禁止LA个数 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU;

/*en_NV_Item_Default_Max_Hplmn_Srch_Peri 8321*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU
 结构说明  : en_NV_Item_Default_Hplmn_Srch_Peri(8321) NV项结构
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDefaultMaxHplmnPeriFlg;               /* 默认最大的HPLMN搜索周期是否有效标志,VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucDefaultMaxHplmnTim;                   /* 用户可以定义默认的最大的HPLMN搜索周期 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU;

/*en_NV_Item_USSD_Apha_To_Ascii 8327*/
/*控制USSD转换字符表*/
/*****************************************************************************
 结构名    : NAS_SSA_NVIM_ALPHA_to_ASCII_STRU
 结构说明  : en_NV_Item_USSD_Apha_To_Ascii(8327) NV项结构
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucStatus;            /*是否激活，0不激活，1激活 */
    VOS_UINT8                       ucAlphaTransMode;    /* 字符表转换*/
}NAS_SSA_NVIM_ALPHA_to_ASCII_STRU;

/*en_NV_Item_Register_Fail_Cnt 8338*/
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_REG_FAIL_CNT_STRU
 结构说明  : en_NV_Item_Register_Fail_Cnt(8338) NV项结构
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新建
  2.日    期   : 2015年3月2日
    作    者   : w00316404
    修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvActiveFlag;                         /* 当前NV项是否激活 */
    VOS_UINT8                           ucRegFailCnt;                           /* NV中设置的注册失败的次数，默认值为2，即注册失败两次后发起搜网。 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_REG_FAIL_CNT_STRU;

/*en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt 8345*/
/* VDF需求: CREG/CGREG命令<CI>域是否以4字节上报的NV项控制结构体 */
/*****************************************************************************
结构名    : NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU
结构说明  : en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt(8345)结构#
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                        /* 1: NV有效标志位，0：无效 */
    VOS_UINT8                           ucCiBytesRpt;                    /* <CI>域上报字节数标志，0：2字节上报, 1：4字节上报 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU
 结构说明  : 记录en_NV_Item__Dell_Reject_Config NV项内容，拨号被拒11,12,13,15,other cause,建链失败,网络没响应等原因定制NV
 1.日    期   : 2012年3月6日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2015年3月2日
   作    者   : w00316404
   修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 拨号被拒是否使能 VOS-TRUE:拨号被拒支持 VOS_FALSE:拨号被拒不支持 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU;

/* en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME 8344 */
typedef struct
{
    VOS_UINT32                          ulDhcpLeaseHour;    /*Range:[0x1,0x2250]*/
}NDIS_NV_DHCP_LEASE_HOUR_STRU;

typedef struct
{
    VOS_UINT32                          ulIpv6Mtu;          /*Range:[1280,65535]*/
}NDIS_NV_IPV6_MTU_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU
结构说明  : en_NV_Item_CCallState_Rpt_Status nvid 9116(已废弃)
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
2.日    期   : 2015年3月2日
  作    者   : w00316404
  修改内容   : 四字节对齐，增加reserve位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU;

/*****************************************************************************
 结构名    : NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
 结构说明  : PLMN比较是否进行精确比较的方式的标记
 修改历史  :
 1.日    期    : 2012年08月7日
   作    者    : l00128652
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucPlmnExactlyCompareFlag;               /* PLMN比较是否进行精确比较的方式的标记 */
   VOS_UINT8                            aucRsv[3];                              /* 保留位 */
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
结构名    : PLATFORM_RAT_TYPE_ENUM
结构说明  : 接入技术

  1.日    期   : 2012年12月25日
    作    者   : z00220246
    修改内容   : 创建
*******************************************************************************/
enum PLATFORM_RAT_TYPE_ENUM
{
    PLATFORM_RAT_GSM,                                                       /*GSM接入技术 */
    PLATFORM_RAT_WCDMA,                                                     /* WCDMA接入技术 */
    PLATFORM_RAT_LTE,                                                       /* LTE接入技术 */
    PLATFORM_RAT_TDS,                                                       /* TDS接入技术 */
    PLATFORM_RAT_1X,                                                        /* CDMA-1X接入技术 */
    PLATFORM_RAT_HRPD,                                                      /* CDMA-EV_DO接入技术 */

    PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 PLATFORM_RAT_TYPE_ENUM_UINT16;

#define PLATFORM_MAX_RAT_NUM            (7)                                    /* 接入技术最大值 */

/*****************************************************************************
结构名    : PLATAFORM_RAT_CAPABILITY_STRU
结构说明  : 平台支持的接入技术

  1.日    期   : 2012年12月25日
    作    者   : z00220246
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                              /* 接入技术的数目*/
    PLATFORM_RAT_TYPE_ENUM_UINT16        aenRatList[PLATFORM_MAX_RAT_NUM];  /* 接入技术 */
}PLATAFORM_RAT_CAPABILITY_STRU;

/*en_NV_Item_Rplmn 8216*/
/*****************************************************************************
 结构名    : NAS_NVIM_RPLMN_INFO_STRU
 结构说明  : en_NV_Item_Rplmn(8216) NV项结构(已废弃)
1.日    期   : 2013年5月22日
  作    者   : m00217266
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRplmnInfo[56];
}NAS_NVIM_RPLMN_INFO_STRU;

/*****************************************************************************
 结构名    : SVLTE_SUPPORT_FLAG_STRU
 结构说明  : en_NV_Item_SVLTE_FLAG NV项结构
 1.日    期   : 2013年6月20日
   作    者   : z00161729
   修改内容   : SVLTE功能是否支持:0-不支持；1-支持
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvlteSupportFlag;                     /* SVLTE功能是否支持:0-不支持；1-支持 */
    VOS_UINT8                           aucReserved[3];                         /* 保留 */
}SVLTE_SUPPORT_FLAG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU
 结构说明  : en_NV_Item_Enable_Lte_Timer_Len NV项结构
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : enable lte定时器时长
 2.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv项未激活；1:nv项激活 */
    VOS_UINT8                           ucCsPsMode1EnableLteTimerLen;           /* 1)cs ps mode1 L联合注册eps only成功cs被拒#16/#17/#22达最大次数场景disable lte时启动enable lte定时器时长
                                                                                   2)cs ps mode1 L联合注册cs eps均失败原因值other cause 达最大次数场景disable lte启动enable lte定时器时长,单位:分钟， nv项激活时如果为0默认54分钟 */
    VOS_UINT8                           ucCsfbEmgCallEnableLteTimerLen;         /* L下紧急呼叫无法正常csfb到gu，通过搜网到gu场景disable lte启动enable lte定时器时长，单位:分钟， nv项激活时如果为0默认5分钟 */

    /* 被拒原因值为#16、#17或#18或联合注册成功，Additional Update Result IE消息中
    指示SMS Only或CSFB Not Preferred需要disable lte时，如果协议版本大于等于R11，
    配置被拒绝的PLMN和RAT记录在禁止接入技术网络列表中的惩罚时间，如果为0xFF表示永久惩罚
    单位:分钟 */
    VOS_UINT8                           ucLteVoiceNotAvailPlmnForbiddenPeriod;
}NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU;


/* Added by c00318887 for 移植T3402 , 2015-6-17, begin */
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU
 结构说明  : en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG NV项结构
             ucT3402Flag 用来控制Disable LTE 后到再次把LTE 恢复所需的定时器时长:
             如果ucT3402Flag 是0，则Disable LTE 后到再次把LTE 恢复所需的定时器时长由NV_Item_Enable_Lte_Timer_Len  0x2404（9220）设置值决定
             如果 ucT3402Flag 配置为 1，在以下场景将使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度
            1) EPS ONLY成功,CS被拒18,CS被拒16,17,22,other cause,EPS尝试次数达到5次
            2) 联合EPS注册被拒 #19, 次数达到最大值
            3) 联合EPS注册被拒 #301, 次数达到最大值 
            4) 联合EPS注册被拒 #other cause, 次数达到最大值
            5) 联合EPS注册被拒 #401, 次数达到最大值
 1.日    期   : 2015年4月28日
   作    者   : c00318887
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT3402Flag;                           /* 0: 不使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度; 1:使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度 */
    VOS_UINT8                           ucHighPrioRatTimerNotEnableLteFlag;    /* 1:高优先级RAT HPLMN TIMER 超时不重新ENABLE lte；0: 高优先级RAT HPLMN TIMER 超时重新ENABLE lte */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU;

/* Added by c00318887 for 移植T3402 , 2015-6-17, end */


/*****************************************************************************
结构名    : NAS_MMC_NVIM_ISR_CFG_STRU
结构说明  : ISR相关配置信息
1.日    期  : 2013年05月23日
  作    者  : z00234330
  修改内容  : ISR通过NVIM判断是否支持
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsrSupport;       /* ISR ???? */
    VOS_UINT8                                               ucReserve1;
} NAS_NVIM_ISR_CFG_STRU;


/*****************************************************************************
 结构名    : CSFB_MT_FOLLOW_ON_SUPPORT_FLAG_STRU
 结构说明  : en_NV_Item_CSFB_MT_RAU_FOLLOW_ON_FLAG NV项结构
 1.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : Csfb mt流程中，RAU是否需要带follow on标记:0-不需要；1-需要
 2.日    期   : 2014年6月10日
   作    者   : w00242748
   修改内容   : Csfb mo流程中，RAU是否需要带follow on标记:0-不需要；1-需要
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg;           /* Csfb mt流程中，RAU是否需要带follow on标记:0-不需要；1-需要 */
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg;           /* Csfb mo流程中，RAU是否需要带follow on标记:0-不需要；1-需要 */
    VOS_UINT8                           aucReserved[2];                         /* 保留 */
}NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU;

/*****************************************************************************
 结构名    : NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU
 结构说明  : en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG NV项结构
  功能说明: 控制通过两个Modem的信息交互的增强型的搜索策略；当前支持的策略为：
  1)  通过另一Modem的PLMN信息,控制FDD搜网是否跳过的策略。比如GUTL+G的版本，当副卡已经驻留在国内G网的时候，主卡搜网可以跳过FDD的搜索（中移动国内只需要支持TDD模式）。
  2)  通过Modem1的GSM上报的L、TDS邻区信息, Modem0不支持GSM的情况下，T/L丢网后，能够根据传递的邻区频点快速搜索到TDS/LTE。
 1.日    期   : 2013年11月18日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usSolutionMask;/*控制通过两个Modem的信息交互的增强型的搜索策略；Bit位控制各个搜网策略；bitn=0：第n个策略关闭；bitn=1：第n个策略开启；
                                                         目前只有bit0、bit1 有效；
                                                         BIT0：控制双Modem下通过另一Modem的PLMN信息控制FDD搜网是否跳过的策略是否启动。
                                                         BIT1：通过Modem1的GSM上报的L、TDS邻区信息, Modem0不支持GSM的情况下，T/L丢网后，能够根据传递的邻区频点快速搜索到TDS/LTE；
                                                               如果Modem1传递过来的邻区信息不存在的情况下，也能通过历史频点支持NCELL搜索邻区快速搜索的频率由ucSolution2NcellSearchTimer决定。
                                                         BIT2~BIT15:预留*/
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer;       /*邻区频点快速搜索策略的一阶段时间间隔（单位秒）。*/

   VOS_UINT8                            ucSolution2NcellQuickSearchTimer2;      /* 邻区频点快速搜索策略的二阶段时间间隔（单位秒）。*/
   VOS_UINT8                            aucAdditonCfg[4];
}NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;


/*****************************************************************************
结构名    : NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU
结构说明  : en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT(9140)结构
1.日    期   : 2014年01月13日
  作    者   : l65478
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucRelFlg;
    VOS_UINT8   ucReserve;
}NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_WG_RF_MAIN_BAND_STRU
结构说明  : en_NV_Item_WG_RF_MAIN_BAND结构
  1.日    期   : 2014年02月10日
    作    者   : f62575
    修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND数据修改为从内存中获取
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWband;                                /* 支持的WCDMA主集通路 */
    VOS_UINT32                          ulWbandExt;                             /* 支持的WCDMA主集通路扩展字段 */
    VOS_UINT32                          ulGband;                                /* 支持的GSM主集通路 */
}NAS_NVIM_WG_RF_MAIN_BAND_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT
 结构说明  : en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT NV项结构
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : ISR激活状态下，从L异系统到GU，如果LAI或RAI未发生变化，是否需要
                进行LAU或是RAU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;           /* ISR激活后，异系统从L变换到GU，LAI未改变，是否需要强制LAU */
    VOS_UINT8                           ucImsVoiceMMEnable;         /* IMS移动性管理 NV */
    VOS_UINT8                           aucReserved[2];             /* 保留 */
}NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT;

/*****************************************************************************
结构名    : NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU
结构说明  : en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG结构
  1.日    期   : 2014年02月25日
    作    者   : z00161729
    修改内容   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1失败disable lte时rau需要从L获取安全上下文

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;             /* l disabled后rau是否需要从l获取安全上下文或guti映射信息，vos_true:需要获取；vos_false:无需获取*/
    VOS_UINT8                           ucReserved[3];
}NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU;


/*****************************************************************************
结构名    : NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU
结构说明  : en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG结构
  1.日    期   : 2014年02月13日
    作    者   : f62575
    修改内容   : DTS2014012902032:
                 NV项en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* 是否激活功能 */
    VOS_UINT8                           ucCsOnlyDataServiceSupportFlg;          /* PS注册被禁止情况下，是否允许数据业务触发注册的标志 */
}NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU;
/*****************************************************************************
 结构名    : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU
 结构说明  : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_INFO NV项结构
 1.日    期   : 2014年2月19日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2014年10月25日
   作    者   : b00269685
   修改内容   : 此NV已废弃，放在这里只是为了编译通过
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /* 该定时器是否使能 */                       /* TD开始背景搜的次数 */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer定时器第一次的时长 单位:秒 */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer定时器第一次时长的限制搜索次数 */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer定时器非首次的时长 单位:秒 */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat 搜被中止或不能立即发起重试的时长 单位:秒*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU
 结构说明  : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG NV项结构
 1.日    期   : 2014年10月25日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                            /* 该定时器是否使能 */
    VOS_UINT8                           ucTdThreshold;                          /* TD开始背景搜的次数 */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer定时器第一次的时长 单位:秒 */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer定时器第一次时长的限制搜索次数 */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer定时器非首次的时长 单位:秒 */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat 搜被中止或不能立即发起重试的时长 单位:秒*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_Ultra_Flash_Csfb_Support_Flg NV项结构
 1.日    期   : 2014年5月30日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUltraFlashCsfbSupportFLg;                 /* 是否支持ultra flash csfb */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_3GPP2_Uplmn_Not_Pref_STRU
 结构说明  : en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg NV项结构
 1.日    期   : 2014年6月13日
   作    者   : B00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc3GPP2UplmnNotPrefFlg;                    /* 是否开启3GPP2 pref plmn */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU
 结构说明  : en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg NV项结构
 1.日    期   : 2014年7月14日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHighPrioRatPlmnSrchFlg;                  /* 是否开启高优先级接入技术搜网 */
    VOS_UINT8                           aucReserved1[3];
}NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU
 结构说明  : en_NV_Item_DSDS_END_SESSION_DELAY NV项结构
 1.日    期   : 2014年7月17日
   作    者   : B00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;              /* Lau延迟时长，单位:毫秒 */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;              /* Rau延迟时长，单位:毫秒 */
    VOS_UINT32                           ulReserve1;
    VOS_UINT32                           ulReserve2;
} NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_SYSTEM_STRU
 结构说明  : 1x system结构
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usChannel;
}CNAS_NVIM_1X_SYSTEM_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_NVIM_1X_MRU_LIST_STRU
 结构说明  : en_NV_Item_1X_MRU_LIST NV项结构
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_SYSTEM_STRU            astSystem[CNAS_NVIM_MAX_1X_MRU_SYS_NUM];
}CNAS_NVIM_1X_MRU_LIST_STRU;


/*****************************************************************************
 结构名    : CNAS_NVIM_1X_TEST_CONFIG_STRU
 结构说明  : en_NV_Item_1X_TEST_CONFIG NV项结构
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReadNvPrlDirectly;
    VOS_UINT8                           ucReadDefaultPrl;        /* 读取Default Prl */
    VOS_UINT8                           ucIsMod1xAvailTimerLen;
    VOS_UINT8                           aucReserve[13];
    
}CNAS_NVIM_TEST_CONFIG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_CALLBACK_CFG_STRU
 结构说明  : en_Nv_Item_CNAS_XSD_CALLBACK_CFG NV项结构
 1.日    期   : 2015年7月2日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} CNAS_NVIM_1X_CALLBACK_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_ADD_AVOID_FREQ_CFG_STRU
 结构说明  : en_NV_Item_1X_ADD_AVOID_CHAN_CFG NV项结构
 1.日    期   : 2015年6月5日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsNegSysAdd;
    VOS_UINT8                           aucReserve[15];
}CNAS_NVIM_1X_ADD_AVOID_LIST_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU
 结构说明  : en_NV_Item_1X_NEG_PREF_SYS_CMP_CTRL NV项结构
 1.日    期   : 2015年6月5日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8           enNegPrefSysCmpType;
    VOS_UINT8                                               aucReserve[15];
}CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_CALL_NVIM_CFG_STRU
 结构说明  : en_NV_Item_1X_CALL_NVIM_CFG_CTRL NV项结构
 1.日    期   : 2015年6月15日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsL3ErrReOrigCount;
    VOS_UINT8                                               ucPrivacyMode;      /* privacy mode flag: 0 - disable 1 - enable */

    VOS_UINT8                                               aucReserve[14];
}CNAS_NVIM_1X_CALL_NVIM_CFG_STRU;


/*****************************************************************************
 结构名    : CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 终端支持的频段能力掩码  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* 终端支持的频段能力掩码，每bit表示是否支持对应的频段能力，比如0x00000001表示只支持频段0 */
}CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 终端支持的频段能力掩码  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* 终端支持的频段能力掩码，每bit表示是否支持对应的频段能力，比如0x00000001表示只支持频段0 */
}CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
结构名称    :NAS_MMC_NVIM_ADAPTION_CAUSE_STRU
使用说明    :用户配置网侧原因的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnCause;     /* 网侧原因值 */
    VOS_UINT8                           ucHplmnCause;  /* 用户配置匹配HPLMN的原因值 */
    VOS_UINT8                           ucVplmnCause;  /* 用户配置匹配VPLMN的原因值 */
    VOS_UINT8                           aucReserved[1];
}NAS_MMC_NVIM_ADAPTION_CAUSE_STRU;

/*****************************************************************************
结构名称    :NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU
使用说明    :en_NV_Item_ChangeNWCause_CFG NV项结构
*****************************************************************************/
typedef struct
{
    /* CS域注册流程(LU)拒绝原因值替换信息 */
    VOS_UINT8                           ucCsRegCauseNum;
    VOS_UINT8                           aucReserved1[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* PS域注册流程(ATTACH/RAU)拒绝原因值替换信息 */
    VOS_UINT8                           ucPsRegCauseNum;
    VOS_UINT8                           aucReserved2[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* 网络GPRS Detach 流程拒绝原因值替换信息 */
    VOS_UINT8                           ucDetachCauseNum;
    VOS_UINT8                           aucReserved3[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astDetachAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* GMM service request流程拒绝原因值替换信息 */
    VOS_UINT8                           ucPsSerRejCauseNum;
    VOS_UINT8                           aucReserved4[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* MM ABORT流程拒绝原因值替换信息 */
    VOS_UINT8                           ucMmAbortCauseNum;
    VOS_UINT8                           aucReserved5[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astMmAbortAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* CM Service流程拒绝原因值替换信息 */
    VOS_UINT8                           ucCmSerRejCauseNum;
    VOS_UINT8                           aucReserved6[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCmSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    VOS_UINT8                           ucHplmnPsRejCauseChangTo17MaxNum; /* HPLMN PS/EPS域拒绝原因值修改为#17的最大次数 */
    VOS_UINT8                           ucHplmnCsRejCauseChangTo17MaxNum; /* HPLMN CS域拒绝原因值修改为#17的最大次数 */
    VOS_UINT8                           ucVplmnPsRejCauseChangTo17MaxNum; /* VPLMN PS/EPS域拒绝原因值修改为#17的最大次数 */
    VOS_UINT8                           ucVplmnCsRejCauseChangTo17MaxNum; /* VPLMN CS域拒绝原因值修改为#17的最大次数 */
}NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU
 结构说明  : en_NV_Item_REL_PS_SIGNAL_CON_CFG NV项结构
 1.日    期   : 2014年11月04日
 作    者   : h00285180
 修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRelPsSignalConFlg;/* 是否开启数据域网络防呆功能 */

    VOS_UINT8                           ucPdpExistNotStartT3340Flag; /* rau或attach请求不带follow on，网络回复attach accept或rau accept也不带follow on，存在pdp上下文场景是否需要启动T3340,0:需要启动T3340; 1:不需要启动 */
    VOS_UINT8                           aucReserved[2];

    VOS_UINT32                          ulT3340Len;         /* 配置的GMM T3340的时长,单位:秒 */
}NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU
 结构说明  : en_NV_Item_WCDMA_VOICE_PREFER_CFG结构
  1.日    期   : 2014年12月26日
    作    者   : s00273135
    修改内容   : 移植
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucEnableFlag;/*使能开关 */
    VOS_UINT8   aucReserve[3];
    VOS_UINT32  ulMcc;    /*用于测试使用指定MCC*/
    VOS_UINT32  ulMnc;    /*用于测试使用指定MNC*/
}NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU;
/*****************************************************************************
 结构名    : NAS_NV_TRI_MODE_ENABLE_STRU
 结构说明  : en_NV_Item_TRI_MODE_ENABLE NV项结构
 1.日    期   : 2015年01月04日
 作    者   : z00306637
 修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEnable;                          /* 全网通特性开关 */
    VOS_UINT16                              usReserved;
}NAS_NV_TRI_MODE_ENABLE_STRU;

/*****************************************************************************
 结构名    : NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU
 结构说明  : en_NV_Item_TRI_MODE_FEM_PROFILE_ID NV项结构
 1.日    期   : 2015年01月04日
 作    者   : z00306637
 修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulProfileId;                        /* 根据使用场景，控制前端器件的上下电（ABB，TCXO，RF）以及RF通道的控制。
                                                                                   由AT命令下发配置。默认值为0。取值范围0-7。 */
    VOS_UINT32                              ulReserved[3];                     /* 保留，将来扩展使用 */
}NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU;



/*****************************************************************************
结构名    : NAS_NV_MODE_BASIC_PARA_STRU
结构说明  :
对应NVID:

  1.日    期   : 2014年12月30日
    作    者   : z00306637
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usABBSwitch;                       /* 用于ABB PLL开关的控制。0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1都打开 */
    VOS_UINT16                              usRFSwitch;                        /* 用于RFIC电源开关的控制。0:RFIC使用MIPI0控制供电方式 1：RFIC使用MIPI1控制供电方式 2：同时打开两路电源。*/
    VOS_UINT16                              usTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              usReserved;                        /* 保留，将来扩展使用 */
}NAS_NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
 结构名    : NV_TRI_MODE_CHAN_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 全网通通道参数配置参数  (不能改变)
*****************************************************************************/
typedef struct
{
    NAS_NV_MODE_BASIC_PARA_STRU            stModeBasicPara[2];                  /* 下标[0]:表示GSM模式下的前端器件的上下电控制。
                                                                                   下标[1]:表示WCDMA模式下的前端器件的上下电控制。
                                                                                    注：副卡时，不使用WCDMA模式的配置。*/
    VOS_UINT32                              ulRfSwitch;                         /* 用于控制共分集的开关 */
    VOS_UINT32                              ulGsmRficSel;                       /* 信令模式下当前使用的通道（0：RF0,1：RF1） */
    VOS_UINT32                              ulGpioCtrl;                         /* gpio */
    VOS_UINT32                              aulReserved[14];                    /* 保留，将来扩展使用 */
}NAS_NV_TRI_MODE_CHAN_PARA_STRU;

/*****************************************************************************
 结构名    : NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 8种场景的通道配置
*****************************************************************************/
typedef struct
{
    NAS_NV_TRI_MODE_CHAN_PARA_STRU          stPara[NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* 最多支持8个场景的配置 */
}NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU;





/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU
 结构说明  : en_NV_Item_CSMO_SUPPORTED_Cfg_Info NV项结构
 1.日    期   : 2015年3月03日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU
 结构说明  : en_NV_Item_Roam_Display_Cfg NV项结构
 1.日    期   : 2015年3月20日
   作    者   : B00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_MT_CSFB_PAGING_PROCEDURE_LEN_STRU
 结构说明  : en_NV_Item_Mt_Csfb_Paging_Procedure_Len NV项结构
 1.日    期   : 2015年5月4日
   作    者   : B00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMtCsfbPagingProcedureLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU
 结构说明  : en_NV_Item_Roam_Plmn_Selection_Sort_Cfg NV项结构
 1.日    期   : 2015年6月02日
   作    者   : W00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    VOS_UINT8                           ucSrchUOplmnPriorToDplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU
 结构说明  : 各阶段定时器
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新建

    NV 参数说明:
    ucHistoryNum        第几次的历史搜 会变成 PrefBand/FullBand搜
    ucPrefBandNum       第几次的PrefBand搜 会变成 FullBand搜
    ucFullBandNum       第几次FullBand搜後, 此阶段结束, 进入下一阶段

    举例：
        第一阶段参数：
        Timerlen = 2sec
        ucHistoryNum            = 2
        ucPrefBandNum           = 2
        ucFullBandNum           = 1
         -> TotalLen            = 2*2*2 = 8
        第二阶段参数：
        Timerlen = 4sec
        ucHistoryNum            = 1
        ucPrefBandNum           = 2
        ucFullBandNum           = Null (1 or 100 没差, 最後一各阶段的full band)
         -> TotalLen            = 1*2*4 = 8

        图示：
        OOC:_H_P_H_F|__P__F__P__F__P__F__P__F ...

        如果改成小於等於:
        OOC:_H_H_P_H_H_P_H_H_F|__H__P__H__P__H__F
        TotalLen = (2+1)*(2+1)*2sec = 18sec (FullBand)

        第一阶段
        CASE#1:
        ucHistoryNum            = 2
        ucPrefBandNum           = 2
        ucFullBandNum           = 0
        OOC:_H_H_P_H_H_P|
        TotalLen = (2+1)*2sec = 6 (PrefBand)

        CASE#2:
        ucHistoryNum            = 2
        ucPrefBandNum           = 0
        ucFullBandNum           = 0
        OOC:_H_H|
        TotalLen = Timerlen     = 2sec (PrefBand)

        CASE#3:
        ucFullBandNum           = 0
        ucPrefBandNum           = 0
        ucHistoryNum            = 0
        给定预设值ucFullBandNum = 1
        OOC:_F|

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimerLen;                        /* 各阶段搜网总时长,单位:s */
    VOS_UINT16                          usSleepTimerLen;                        /* 搜网间隔的睡眠时长,单位:s */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucHistoryNum;                           /* 第几次的历史搜 会变成 PrefBand/FullBand搜 */
    VOS_UINT8                           ucPrefBandNum;                          /* 第几次的PrefBand搜 会变成 FullBand搜 */
    VOS_UINT8                           ucFullBandNum;                          /* 第几次FullBand搜後, 此阶段结束, 进入下一阶段 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
}NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU
 结构说明  : en_NV_Item_Oos_Plmn_Search_Strategy_Cfg NV项结构
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseOnePatternCfg;    /* 第一阶段的搜网类型配置与睡眠时长 */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseTwoPatternCfg;    /* 第二阶段的搜网类型配置与睡眠时长 */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseThreePatternCfg;  /* 保留：第三阶段的搜网类型配置与睡眠时长 */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseFourPatternCfg;   /* 保留：第四阶段的搜网类型配置与睡眠时长 */
}NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU
 结构说明  : en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg NV项结构
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHistoryActiveFlg;                     /* NV项是否激活 */
    VOS_UINT8                           ucPrefBandActiveFlg;                    /* NV项是否激活 */
    VOS_UINT8                           ucSearchTypeAfterHistoryInAreaLostScene;/* area lost场景history搜完之后的搜网类型 0:不搜 1:pref band搜 2:spec搜 */
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulReserved4;
    VOS_UINT32                          ulReserved5;
}NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_GET_GEO_PRIO_RAT_LIST_STRU
 结构说明  : 获取地理位置信息的接入技术优先级列表信息
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* 获取地理位置信息的接入技术个数 */
    VOS_UINT8                           aucRatOrder[NAS_NVIM_MAX_RAT_NUM];      /* 获取地理位置信息的接入技术优先级 */
}NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_GET_GEO_CFG_INFO_STRU
 结构说明  : en_NV_Item_Get_Geo_Cfg_Info NVIM
 1.日    期   : 2015年05月22日
   作    者   : f00179208
   修改内容   : 漫游搜网配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;               /* NV项是否激活 */
    VOS_UINT8                                               ucGetGeoTimerlen;           /* 获取国家码定时器时长，单位是秒 */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT32                                              ulGeoEffectiveTimeLen;      /* 国家码的有效性时长，单位是分钟 */
    NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU                     stGetGeoPrioRatList;        /* 获取地理位置信息的接入技术优先级列表信息 */
}NAS_NVIM_GET_GEO_CFG_INFO_STRU;

/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
/*****************************************************************************
 结构名    : NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU
 结构说明  : en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg NV项结构
  1.日    期   : 2015年10月9日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU;
/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, end */

/*****************************************************************************
 结构名    : NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU
 结构说明  : en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG NV项结构
  1.日    期   : 2015年10月9日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDeleteRplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU
 结构说明  : en_NV_Item_Nw_Search_Chr_Record_Cfg NVIM
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 搜网CHR记录配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;       /* NV项是否激活 */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT32                                              ulRecordNum;        /* 记录的次数 */
}NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_EVDO_PRL_LIST_STRU
 结构说明  : en_NV_Item_1X_EVDO_PRL_LIST NV项结构
 1.日    期   : 2014年11月03日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrlData[CNAS_NVIM_PRL_SIZE];
}CNAS_NVIM_1X_EVDO_PRL_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_HOME_SID_NID_STRU
 结构说明  : HOME_SID_NID相关信息
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usReserved;
}CNAS_NVIM_1X_HOME_SID_NID_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU
 结构说明  : HOME_SID_NID相关列表信息
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_HOME_SID_NID_STRU      astHomeSidNid[CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM];
}CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_SEARCH_INTERVAL_STRU
 结构说明  : 扫描次数与间隔相关信息
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}CNAS_NVIM_OOC_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 结构说明  : 扫描次数与间隔相关列表信息
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           uc1xOocDoTchPhase1TimerLen;              /* Do TCH，前4次尝试 Ooc Timer 最短时长 */
    VOS_UINT8                           uc1xOocDoTchPhase2TimerLen;              /* Do TCH，4次以上尝试 Ooc Timer 最短时长 */
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU;
/*****************************************************************************
 结构名    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 结构说明  : 扫描次数与间隔相关列表信息
 1.日    期   : 2015年01月08日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucInsertOrigChanFlg;        /* 在同步请求前是否插入先前驻留频点 */
    NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8                    enChanRepeatScanStrategy;   /*频点重复搜索策略 */
    VOS_UINT8                                               aucReserved[2];
}CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU
 结构说明  : EPDSZID Feature Cfg
 1.日    期   : 2015年01月08日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8                ucEpdszidType;  /* EPDSZID支持类型 */
    VOS_UINT8                                               ucHatLen;       /* HAT时长，单位s */
    VOS_UINT8                                               ucHtLen;        /* HT时长，单位s */
    VOS_UINT8                                               aucReserved[5];
}CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_HRPD_SYSTEM_STRU
 结构说明  : NV项中HRDP保存的子网、BAND和Channel信息结构
 1.日    期   : 2014年12月11日
   作    者   : h00300778
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucSubnet[CNAS_NVIM_HRPD_SUBNET_LEN];
    VOS_UINT16                         usBandClass;
    VOS_UINT16                         usChannel;
}CNAS_NVIM_HRPD_SYSTEM_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_HRPD_MRU_LIST_STRU
 结构说明  : en_NV_Item_HRPD_MRU_LIST NV项结构
 1.日    期   : 2014年12月11日
   作    者   : h00300778
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucRsv[3];
    CNAS_NVIM_HRPD_SYSTEM_STRU          astSystem[CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM];
}CNAS_NVIM_HRPD_MRU_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_LAST_SCI_STRU
 结构说明  : en_NV_Item_1X_LAST_SCI NV项结构
 1.日    期   : 2015年2月4日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSicValue;
}CNAS_NVIM_1X_LAST_SCI_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU
 结构说明  : en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len NV项结构
 1.日    期   : 2015年1月29日
   作    者   : y00245242
   修改内容   : 等待IMS VOICE CAP的定时器时长
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv项未激活；1:nv项激活 */
    VOS_UINT8                           ucWaitImsVoiceAvailTimerLen;            /* 等待IMS VOICE的可用指示的定时器时长,单位为秒级,需要转换为毫秒 */
    VOS_UINT8                           aucRsv[2];
}NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU;

typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT8                           ucLocType;
    VOS_UINT8                           ucLocLen;
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNID;
    VOS_UINT8                           ucPacketZoneID;
    VOS_UINT8                           ucReserve;
}CNAS_NVIM_HRPD_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT16                          usStrgBLOBType;
    VOS_UINT8                           ucStrgBLOBLen;
    VOS_UINT8                           aucStorageBLOB[CNAS_NVIM_MAX_STORAGE_BLOB_LEN];
    VOS_UINT8                           aucReserve[2];
}CNAS_NVIM_HRPD_STORAGE_BLOB_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU
 结构说明  : en_NV_Item_LTE_REJ_CAUSE_14_CFG NV项结构
 1.日    期   : 2015年1月5日
   作    者   : h00285180
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRejCause14Flg;               /* 是否开启LTE #14原因拒绝优化，0: 未开启；1:开启 */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLteRejCause14EnableLteTimerLen; /* LTE #14原因拒绝时，通过搜网到gu场景disable lte启动enable lte定时器时长，单位:分钟 */
}NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU;

/*****************************************************************************
 枚举名    : NAS_SMS_PS_CONCATENATE_ENUM
 结构说明  : PS域短信连续发送枚举定义
  1.日    期   : 2015年05月18日
    作    者   : j00174725
    修改内容   : 新增
*****************************************************************************/
enum NAS_SMS_PS_CONCATENATE_ENUM
{
    NAS_SMS_PS_CONCATENATE_DISABLE      = 0,
    NAS_SMS_PS_CONCATENATE_ENABLE,

    NAS_SMS_PS_CONCATENATE_BUTT
};
typedef VOS_UINT8 NAS_SMS_PS_CONCATENATE_ENUM_UINT8;

/*****************************************************************************
 结构名称  : NAS_NV_SMS_PS_CTRL_STRU
 结构说明  : PS域短信控制

  1.日    期   : 2015年05月18日
    作    者   : j00174725
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8   enSmsConcatenateFlag;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} NAS_NV_SMS_PS_CTRL_STRU;

/*****************************************************************************
 结构名称  : NAS_NV_SMS_FILTER_CFG_STRU
 结构说明  : 短信过滤配置信息

  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsFilterEnableFlg;
    VOS_UINT8                           aucReserved[3];
} NAS_NV_SMS_FILTER_CFG_STRU;


/*****************************************************************************
 Name    : NAS_NVIM_AVAILABLE_TIMER_CFG_STRU
 Description  : Structure defintion for available timer config used in MSCC
 History     :
  1.Date     : 2015-04-14
    Author   : a00295761
    Modify   : create
  2.Date     : 2016-01-14
    Author   : W00176964
    Modify   : DTS2016011505496:增加对原始系统不在MSPL表进行BSR流程,定时器时长的NV控制
*****************************************************************************/
typedef struct
{

    VOS_UINT8                           ucBsrTimerActiveFlag; /* If the Flag is TRUE, then BSR Timer value is read from NV
                                                                  If FALSE, the BSR timer value is read from SIM */

    VOS_UINT8                           ucReserved1;

    VOS_UINT16                          usBsrTimerLenWithNoMatchedMsplRec;/* 原始系统不在MSPL表中时,bsr定时器时长 */

    VOS_UINT32                          ulFirstSearchAvailTimerLen; /* Contains the Available timer length to be used , when the
                                                                    number of successive triggers is less than ulFirstSearchAvailTimerCount */

    VOS_UINT32                          ulFirstSearchAvailTimerCount; /* For the number successive triggers of avaiable timer less
                                                                      than or equal to ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                      length value of ulFirstSearchAvailTimerLen */

    VOS_UINT32                          ulDeepSearchAvailTimerLen;  /* For the number successive triggers of avaiable timer greater
                                                                    than ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                    length value of ulDeepSearchAvailTimerLen */

    VOS_UINT32                          ulScanTimerLen; /* Contains the scan timer length */
    VOS_UINT32                          ulBsrTimerLen; /* Contains the BSR Timer length */
    VOS_UINT32                          ulSleepTimerLen; /* Contains the sleep timer length */
}NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU;


typedef struct
{
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;

    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  en1xPrioClass;
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enAIPrioClass;
    VOS_UINT8                                               aucRsv[2];  /* remain four bytes in future */
}NAS_NVIM_1X_LOC_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_3GPP_LOC_INFO_STRU
 结构说明  : 3gpp loc info

 1.日    期   : 2015年5月26日
   作    者   : w00176964
   修改内容   : 新建
 2.Date       : 2015-05-29
   Author     : w00176964
   Modify     : DTS2015052903319:add pri class
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                                              ulMnc;                                  /* MNC,2 or 3 bytes */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enPrioClass;
    VOS_UINT8                                               aucRsv[3];  /* remain four bytes in future */
}NAS_NVIM_3GPP_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucIsLocInfoUsedInSwitchOn;
    NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8 enSysAcqMode;
    VOS_UINT8                           ucIs1xLocInfoValid;
    VOS_UINT8                           ucIsLteLocInfoValid;
    NAS_NVIM_1X_LOC_INFO_STRU           st1xLocInfo;
    NAS_NVIM_3GPP_LOC_INFO_STRU         st3gppLocInfo;
}NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU;


typedef struct
{

    VOS_UINT8                                               ucReAcqLteOnHrpdSyncIndFlag; /* The NVIM Flag controls if
                                                                                                       MSCC must search  for LTE Service
                                                                                                       when HSD sends Sync Ind, if LTE
                                                                                                       is preferred */

    VOS_UINT8                                               ucIs1xLocInfoPrefThanLte;  /* The NVIM Flag controls if CDMA 1x
                                                                                                     Loc info is more preferred than LTe
                                                                                                     Loc Info */
    VOS_UINT8                                               aucReserved[2];
    NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU                    stMmssSysAcqTimerCfg;  /* Contains the Timer Configuration
                                                                                                for MMSS System Acquire */
}NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucMlplMsplActiveFlag;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usMlplBufSize;
    VOS_UINT16                          usMsplBufSize;
    VOS_UINT8                           aucMlplBuf[NAS_MSCC_NVIM_MLPL_SIZE];
    VOS_UINT8                           aucMsplBuf[NAS_MSCC_NVIM_MSPL_SIZE];
}NAS_MSCC_NVIM_MLPL_MSPL_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_MOB_TERM_STRU
 结构说明  : en_NV_Item_1X_MOB_TERM NV项结构
 1.日    期   : 2015年6月2日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermHome;
    VOS_UINT8                           ucRsv;
}CNAS_NVIM_1X_MOB_TERM_STRU;


typedef struct
{
    VOS_UINT8                           ucActiveFlag;           /* NV item is active not not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usActTimerLen;          /* Session activate timer length, unit is second */
    VOS_UINT8                           ucMaxActCountConnFail;  /* Max session activate count of reason conntion fail */
    VOS_UINT8                           ucMaxActCountOtherFail; /* Max session activate count of reason other fail */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU;

/*****************************************************************************
 Name    : CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg
 History     :
  1.Date     : 2015-09-23
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-12-17
    Author   : m00312079
    Modify   : DTS2015121410637:增加NV项控制在AMP setup和open态时当UATI req发送成功过后等网侧UATI assign的时长
  3.Date     : 2015-12-31
    Author   : m00312079
    Modify   : DTS2015123108077:增加NV项控制在open态时当UATI req发送成功后等网侧UATI assign超时后的重试次数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartUatiReqAfterSectorIdChgFlg;   /* 为了通过RF测试和CCF2.2.2.8用例，增加NV控制
                                                                                          NV打开(默认):参照标杆只要sector ID发生变化就启动UATI申请流程
                                                                                          NV关闭:      严格按照协议C.S0024 7.3.7.1.6.1处理，即只有在HO或者
                                                                                                       Conn Close后，sector ID发生变化才启动UATI申请流程 */

    VOS_UINT8                           ucWaitUatiAssignTimerLenInAmpSetup; /* 单位:秒(s),默认5s.在某些场景和设备商的网络上，为了降低UE的接入时长，
                                                                                        缩短UE等UATI assign的时长，该时长最短为5s，最长为120s(协议定时器时长) */
    VOS_UINT8                           ucWaitUatiAssignTimerLenInAmpOpen; /* 单位:秒(s),默认120s(协议定时器时长)。该时长最短5s，最长120s。*/

    VOS_UINT8                           ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;/* 增加NV项控制在open态时当UATI req发送成功后
                                                                                                             等网侧UATI assign超时后的重试次数,默认不重试，最大重试4次 */
    VOS_UINT8                           aucRsv[28];
}CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucIsKeepAliveInfoValid;    /* If TRUE, then the Keep alive paramters are valid */
    VOS_UINT8                           ucRsv1;                    /* for padding */
    VOS_UINT16                          usTsmpClose;               /* stores the TsmpClose value of the last session. Unit is minutes */
    VOS_UINT32                          ulTsmpCloseRemainTime;     /* Stores the time remaining for Tsmpclose minutes to
                                                                               expire. Unit is seconds */
    VOS_UINT32                          aulLastPowerOffSysTime[2]; /* Stores the CDMA system time at last Power Off.
                                                                              Unit is Milliseconds. */
}CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEhrpdSupportFlg;       /* EHRPD is support or not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}NAS_NVIM_EHRPD_SUPPORT_FLG_STRU;


/* Added by c00318887 for 预置频点搜网优化, 2015-8-26, begin */
/*****************************************************************************
 结构名    : NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU
 结构说明  : en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG NV项结构
  1.日    期   : 2015年8月26日
    作    者   : c00318887
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* NV项是否激活 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulTotalTimeLen;                         /* 第一阶段搜网总时长,单位:s */
}NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU;

/* Added by c00318887 for 预置频点搜网优化, 2015-8-26, end */

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU
 结构说明  : en_NV_Item_CS_REG_FAIL_CAUSE_FORB_LA_TIME_CFG NV项结构
  1.日    期   : 2015年9月23日
    作    者   : z00359541
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegFailCauseNum;                      /* 支持的注册失败原因值个数,个数为0表示不支持该特性 */
    VOS_UINT16                          usForbLaTimeLen;                        /* 禁止LA时长,单位:s */
    VOS_UINT16                          usPunishTimeLen;                        /* 放乒乓机制中需要惩罚的时长 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT16                          ausRegFailCauseList[NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM];
}NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU;

/*****************************************************************************
 结构名称  : NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU
 结构说明  : CSG自主搜网相关配置信息

  1.日    期   : 2015年9月21日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCsgAutonomousSrchFirstSrchTimeLen;                   /* CSG自主搜网定时器第一次的时长 */
    VOS_UINT8                           ucCsgAutonomousSrchFirstSrchTimeCount;                 /* CSG自主搜网定时器第一次的次数 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usCsgAutonomousSrchSecondSrchTimeLen;                  /* CSG自主搜网定时器第二次的时长 */
    VOS_UINT8                           ucCsgAutonomousSrchSecondSrchTimeCount;                /* CSG自主搜网定时器第二次的次数 */
    VOS_UINT8                           ucReserved2;
} NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_PLMN_WITH_CSG_ID_STRU
 结构说明  : PLMN带CSG ID的结构

 1.日    期   : 2015年9月21日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    NVIM_PLMN_VALUE_STRU                stPlmnId;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT32                          ulCsgId;
}NAS_NVIM_PLMN_WITH_CSG_ID_STRU;


/*****************************************************************************
 结构名    : NAS_NVIM_ALLOWED_CSG_LIST_STRU
 结构说明  : Allowed CSG List卡文件不存时nv中记录allowed CSG List信息

 1.日    期   : 2015年9月21日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnWithCsgIdNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    NAS_NVIM_PLMN_WITH_CSG_ID_STRU      astPlmnWithCsgIdList[NAS_NVIM_MAX_PLMN_CSG_ID_NUM];
}NAS_NVIM_ALLOWED_CSG_LIST_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_CSG_DUPLICATE_RPLMN_AND_EPLMN_LIST_STRU
结构说明  : 记录CSG手动搜网前的RPLMN和EPLMN信息
1.日    期   : 2015年9月21日
  作    者   : z00161729
  修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           ucRat;                                  /* 记录duplicate rplmn的接入技术*/
    VOS_UINT8                           aucReserve[2];                          /*NV项相关的结构体，在4字节方式下，需手动补齐空洞*/
    NVIM_PLMN_VALUE_STRU                astRplmnAndEplmnList[NVIM_MAX_EPLMN_NUM];
}NAS_NVIM_CSG_DUPLICATED_RPLMN_AND_EPLMN_LIST_STRU;

/*****************************************************************************
结构名    : NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU
结构说明  : csg禁止网络相关配置
1.日    期   : 2015年9月21日
  作    者   : z00161729
  修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    /* CSG禁止网络惩罚时长,单位秒 */
    VOS_UINT16                          usCsgPlmnForbiddenPeriod;

    /* 配置CSG网络被拒哪些原因值时需要将该网络加入禁止csg网络列表 */
    VOS_UINT8                           ucCauseNum;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausCause[NAS_NVIM_MAX_CSG_REJ_CAUSE_NUM];
}NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU;

/*****************************************************************************
 结构名称  : NAS_NVIM_CSG_CTRL_CFG_STRU
 结构说明  : CSG特性配置相关nv

  1.日    期   : 2015年9月21日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucBitOp1:1;
    VOS_UINT8                                               ucBitOp2:1;
    VOS_UINT8                                               ucBitOp3:1;
    VOS_UINT8                                               ucBitOp4:1;
    VOS_UINT8                                               ucBitOp5:1;
    VOS_UINT8                                               ucBitOp6:1;
    VOS_UINT8                                               ucBitOp7:1;
    VOS_UINT8                                               ucBitOp8:1;
    VOS_UINT8                                               ucReserved0;
    VOS_UINT8                                               ucIsSupportCsgFlag;             /* VOS_TRUE:UE支持CSG功能; VOS_FALSE:UE不支持CSG功能 */
    VOS_UINT8                                               ucCsgListOnlyReportOperatorCsgListFlag; /* VOS_TRUE:csg列表搜网结果只上报在operator csg list中网络; VOS_FALSE:CSG列表搜网结果所有CSG ID都上报 */
    NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU                    stCsgForbiddenPlmnCfg;       /* CSG禁止网络相关配置 */
    NAS_NVIM_ALLOWED_CSG_LIST_STRU                          stAllowedCsgList;               /* 记录Allowed CSG List信息 */
    VOS_UINT32                                              ulCsgPeriodicSearchPeriod;      /* CSG周期性搜网时长,单位分钟 */
    NAS_NVIM_CSG_DUPLICATED_RPLMN_AND_EPLMN_LIST_STRU       stDuplicatedRplmnAndEplmnList;  /* 关机时如果之前进行过CSG指定搜网，且关机时驻留CSG网络，则记录CSG指定搜网前的RPLMN和EPLMN*/
    NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU                 stCsgAutonomousSrchCfg;         /* CSG自主搜网相关配置 */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
    VOS_UINT32                                              ulReserved1;
} NAS_NVIM_CSG_CTRL_CFG_STRU;


/*****************************************************************************
 结构名    : NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU
 结构说明  : 配置收到PS注册成功消息是否保留禁止信息

 1.日    期   : 2015年12月11日
   作    者   : z00359541
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKeepCsForbInfoFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_CLEAR_CKSN_STRU
 结构说明  : 当网络对鉴权失败结果没有响应，释放链路时是否清楚CKSN的配置
 1.日    期   : 2015年1月5日
   作    者   : z00359541
   修改内容   : 新建
  2.日    期   : 2016年1月19日
    作    者   : c00318887
    修改内容   : 扩充nv
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNwIgnoreAuthFailFlg;                  /* 当网络对鉴权失败结果没有响应，释放链路时是否清楚CKSN的配置 */
    VOS_UINT8                           ucUsimGsmAuthCfg;                       /* USIM卡在GSM下做2G cs/ps 鉴权，在3G下是否需要清除CS/ps CKSN值 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_NVIM_CLEAR_CKSN_STRU;


enum CNAS_NVIM_HRPD_SESSION_STATUS_ENUM
{
    CNAS_NVIM_HRPD_SESSION_STATUS_CLOSE,
    CNAS_NVIM_HRPD_SESSION_STATUS_OPEN,
    CNAS_NVIM_HRPD_SESSION_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8;


enum CNAS_NVIM_HRPD_SESSION_TYPE_ENUM
{
    CNAS_NVIM_HRPD_SESSION_TYPE_HRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_EHRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8;


enum CNAS_NVIM_HARDWARE_ID_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_TYPE_MEID                    = 0x0000FFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_ESN                     = 0x00010000,
    CNAS_NVIM_HARDWARE_ID_TYPE_NULL                    = 0x00FFFFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32;


enum CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_NVIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_RAND,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_UIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32;

/*****************************************************************************
 Structure Name    : CNAS_NVIM_HRPD_UATI_INFO_STRU
 Description       : hrpd uati info structure
 History     :
  1.Date     : 2015-06-03
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-06-18
    Author   : m00312079
    Modify   : DTS2015091604029:nv中保存有效uati assigngment的sequence number
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           aucCurUATI[CNAS_NVIM_UATI_OCTET_LENGTH];
    VOS_UINT8                           ucUATIColorCode;
    VOS_UINT8                           ucUATISubnetMask;
    VOS_UINT8                           ucUATIAssignMsgSeq;
    VOS_UINT8                           ucRsv2;
}CNAS_NVIM_HRPD_UATI_INFO_STRU;


typedef struct
{
    CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32                  enHwidType;
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32              enHwidSrcType;
    VOS_UINT32                                              ulEsn;                                /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_NVIM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               ucRsv1;
}CNAS_NVIM_HARDWARE_ID_INFO_STRU;


typedef struct
{
    VOS_INT32                           lLongitude;
    VOS_INT32                           lLatitude;
}CNAS_NVIM_LOC_INFO_STRU;


typedef struct
{
    CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8                enSessionStatus;
    CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                               aucIccid[CNAS_NVIM_ICCID_OCTET_LEN];
    CNAS_NVIM_HRPD_UATI_INFO_STRU                           stUatiInfo;
    CNAS_NVIM_LOC_INFO_STRU                                 stLocInfo;
    CNAS_NVIM_HARDWARE_ID_INFO_STRU                         stHwid;
}CNAS_NVIM_HRPD_SESSION_INFO_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSuppOnlyDo0;                          /* 是否只支持DO0版本 */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithMfpa;                      /* 是否支持DOA版本，应用类型只支持MFPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithEmfpa;                     /* 是否支持DOA版本，应用类型支持MFPA和EMPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaEhrpd;                         /* 是否支持eHRPD */
}CNAS_NVIM_HRPD_UE_REV_INFO_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU
 Description  : Structure definition for en_Nv_Item_HRPD_Session_Info_Ex
 History     :
  1.Date     : 2015-09-18
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-12-21
    Author   : m00312079
    Modify   : DTS2015120208895,将session与UE的版本信息绑定
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSessionSeed;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU     stUERevInfo;
    VOS_UINT8                           aucReserve[12];
}CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU;


typedef struct
{
    VOS_UINT8                           ucAccessAuthAvailFlag;
    VOS_UINT8                           ucAccessAuthUserNameLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           aucAccessAuthUserName[CNAS_NVIM_MAX_AUTHDATA_USERNAME_LEN];
}CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU
 结构说明  : 联合Attach或者RAU，建链失败达到最大次数之后是否只触发一次LAU
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucPsRegFailMaxTimesTrigLauOnceFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU
 结构说明  : HPLMN注册被#13拒绝之后是否需要再搜索此HPLMN WITH RAT
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucKeepSrchHplmnEvenRejByCause13Flg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU
 结构说明  : VPLMN LTE注册被#14拒绝之后是否允许在2/3G PS域进行注册
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucEpsRejByCause14InVplmnAllowPsRegFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU;

/*****************************************************************************
 枚举名    : NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
 结构说明  : 搜索RPLMN时是否需要携带EPLMN
 1.日    期: 2015年8月13日
   作    者: l00289540
   修改内容: 新增
*****************************************************************************/
enum NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_OFF                     = 0,           /* 关闭此优化 */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ROAM             = 1,           /* 优化打开，但是仅在漫游时生效 */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ALL              = 2,           /* 优化打开，漫游与非漫游都生效 */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU
 结构说明  : 搜索RPLMN是否需要携带EPLMN的NV配置
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8         enSwitchFlag;
    VOS_UINT8                                               ucCarryEplmnSceneSwitchOn;
    VOS_UINT8                                               ucCarryEplmnSceneAreaLost;
    VOS_UINT8                                               ucCarryEplmnSceneAvailableTimerExpired;
    VOS_UINT8                                               ucCarryEplmnSceneSysCfgSet;
    VOS_UINT8                                               ucCarryEplmnSceneDisableLte;
    VOS_UINT8                                               ucCarryEplmnSceneEnableLte;
    VOS_UINT8                                               ucCarryEplmnSceneCSFBServiceRej;
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
}NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_HOME_SID_NID_PRI_CFG
                HOME SID/NID列表的优先级是否是最高的，如果标记为VOS_TRUE，表示home SID/NID
                的系统优先级最高，不管该系统是否在PRL表中；如果为VOS_FALSE，home SID/NID仅刷新
                PRL表中的NEG和roaming标记
 History     :
  1.Date     : 2015-07-02
    Author   : w00242748
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeSidNidDependOnPrlFlg;
    VOS_UINT8                           aucReserved[3];
}CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_SYS_INFO_STRU
 结构说明  : 保存的SID和MCC信息，定制白名单中的MCC、起始SID以及结束SID

 1.日    期   : 2015年7月2日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}CNAS_NVIM_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_OPER_LOCK_WHITE_SID_STRU
 结构说明  : en_NV_Item_OPER_LOCK_WHITE_SID_INFO NV项结构
  1.日    期   : 2015年7月2日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* 白名单是否使能 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* 支持白名单的个数,个数为0时表示不支持白名单 */
    CNAS_NVIM_SYS_INFO_STRU             astSysInfo[CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_FREQENCY_CHANNEL_STRU
 结构说明  : 频点结构
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT8                           aucReserved[2];
}CNAS_NVIM_FREQENCY_CHANNEL_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU
 结构说明  : 中国电信定制频点结构
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_NVIM_FREQENCY_CHANNEL_STRU     astFreqList[CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM];
}CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU
 结构说明  : CDAM standard channels信息
  1.日    期   : 2015年7月14日
    作    者   : y00245242
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryA;
    VOS_UINT16                          usPrimaryB;
    VOS_UINT16                          usSecondaryA;
    VOS_UINT16                          usSecondaryB;
}CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU;


typedef struct
{
    VOS_UINT32                                              ulEnableFlag;
}CNAS_NVIM_NO_CARD_MODE_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_EMC_REDIAL_SYS_ACQ_CFG_STRU
 结构说明  : en_NV_Item_EMC_REDIAL_SYS_ACQ_CFG NV项结构
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucRedialTimes[CNAS_NVIM_1X_MAX_MRU_SYS_NUM];  /* 紧急呼叫失败时当前驻留的频点在mru list的重拨次数，超过次数起搜网*/
}CNAS_NVIM_1X_EMC_REDIAL_SYS_ACQ_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_AVOID_PHASE_NUM
 结构说明  : avoid策略信息
  1.日    期   : 2015年11月23日
    作    者   : c00299063
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAvoidTimerLen[CNAS_NVIM_1X_AVOID_MAX_PHASE_NUM];    
}CNAS_NVIM_1X_AVOID_PHASE_NUM;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU
 结构说明  : avoid策略信息
  1.日    期   : 2015年11月23日
    作    者   : c00299063
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_AVOID_PHASE_NUM        astAvoidPhaseNum[CNAS_NVIM_1X_AVOID_REASON_MAX];    
}CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU
 结构说明  : en_CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU NV项结构
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPowerOffCampOnCtrlFlg;  
    VOS_UINT8                                               aucReserved[3];
}CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRUs
 结构说明  : en_NV_Item_LTE_OOS_2G_PREF_PLMN_SEL_CFG NV项结构
  1.日    期   : 2015年07月03日
    作    者   : h00285180
    修改内容   : 新建

    ucImsiPlmnListNum   SIM卡数目；最大支持16；
    astImsiPlmnList     SIM卡列表，最大支持16组;
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucImsiListNum;                                                  /*功能起效的SIM卡数目(LTE OOS后先搜2G再搜3G)  */
    VOS_UINT8                          ucReserved1;
    VOS_UINT8                          ucReserved2;
    VOS_UINT8                          ucReserved3;
    NAS_SIM_FORMAT_PLMN_ID             astImsiList[NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM];/* SIM卡列表 (LTE OOS后先搜2G再搜3G) */
}NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU
 结构说明  : 频段和频点结构
  1.日    期   : 2015年7月3日
    作    者   : h00313353
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT16                          usBandClass;
} CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_CDMA_1X_PREF_CHANNELS_STRU
 结构说明  : 中国电信1X优选频点结构
  1.日    期   : 2015年7月3日
    作    者   : h00313353
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU astFreqList[CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_DYNLOAD_CTRL_STRU
 结构说明  : 动态加载控制信息
  1.日    期   : 2015年8月12日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableDynloadTW;
    VOS_UINT8                           ucReseverd1;
    VOS_UINT8                           ucReseverd2;
    VOS_UINT8                           ucReseverd3;
}NAS_NVIM_DYNLOAD_CTRL_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU
 结构说明  : 动态加载次数控制信息
  1.日    期   : 2015年11月12日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTWMaxAttemptCount;
    VOS_UINT8                           ucReseverd1;
    VOS_UINT8                           ucReseverd2;
    VOS_UINT8                           ucReseverd3;
}NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU
 结构说明  : en_NV_Item_1X_PAGING_RSP_SO_CFG NV项结构
 1.日    期   : 2015年11月02日
   作    者   : L00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNoDataSrvRspSo33;                     /* 没有数据业务时，Paging rsp的回复。0 - Paging Rsp中SO带0； 1 - Paging Rsp中SO带33 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU;



/*****************************************************************************
 结构名    : NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU
 结构说明  : en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO NV项结构
 1.日    期   : 2015年10月10日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsStartT310AccordWith3GPP;            /* 当proceeding或者progress中，携带progress indicator值为#1，#2，#64时，
                                                                                   是否启动T310, 0 - 不按协议做;  1 -  按照协议做 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU
 结构说明  : en_NV_Item_CDATA_DISCING_PARA_CFG NV项结构
 1.日    期   : 2015年11月11日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPppDeactTimerLen;                     /* 单位(S), PPP去激活流程时间 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU
 结构说明  : en_NV_Item_PPP_AUTH_INFO_FROM_CARD_FLAG NV项结构
 1.日    期   : 2015年11月11日
   作    者   : Y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsPppAuthGetFromCard;
}NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU
 结构说明  : en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG NV项结构
 1.日    期   : 2015年12月26日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:Auto attach功能使能；VOS_FALSE:Auto attach功能关闭 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU
 结构说明  : ECC服务能力参数信息。
             注: ECC业务状态仅在ECC业务能力支持的情况下，才有效。

 修改历史      :
  1.日    期   : 2015-11-11
    作    者   : l00359089
    修改内容   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC服务能力: TRUE -- 支持ECC服务，FALSE -- 不支持ECC服务 */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC服务状态: TRUE -- ECC服务打开，FALSE -- ECC服务关闭 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
 结构说明  : 1X有服务时CL搜网各阶段配置结构体
 修改历史      :
  1.日    期   : 2015-12-10
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimeLen;         /* 该阶段整体搜索时长,单位为秒 */
    VOS_UINT16                          usSleepTimeLen;         /* 该阶段available定时器的启动时长,单位为秒 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucLteHistorySrchNum;       /* 该阶段LTE历史频点搜索总次数 */
    VOS_UINT8                           ucLteFullBandSrchNum;      /* 该阶段LTE全频段搜索总次数 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU
 结构说明  : 1X有服务时CL搜网各阶段配置结构体
 修改历史      :
  1.日    期   : 2015-12-21
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
    VOS_UINT8                           ucReserve8;
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU;


/*****************************************************************************
 结构名    : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU
 结构说明  : 1X有服务时CL搜网策略控制NV
 修改历史      :
  1.日    期   : 2015-12-10
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
typedef struct
{
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU         stCtrlInfo;
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseOnePatternCfg;   /* 首阶段配置信息 */
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseTwoPatternCfg;   /* 二阶段配置信息 */
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseThreePatternCfg; /* 三阶段配置信息:目前未使用,预留 */
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 结构说明  : 扫描次数与间隔相关列表信息
 1.日    期   : 2016年01月12日
   作    者   : z00316370
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           ucResv[2];
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_HRPD_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU;



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

#endif /* end of NasNvInterface.h */
