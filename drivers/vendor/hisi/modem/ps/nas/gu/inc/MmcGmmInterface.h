/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmcGmmInterface.h
  Description : MMC与GMM接口头文件
  History     :
      1. 张志勇  2003.12.05  文件头作成
      2. 日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
      3.日    期   : 2008年08月08日
        作    者   : luojian id:00107747
        修改内容   : 根据问题单AT2D04880/AT2D05000,等效PLMN列表清除排查
      4.日    期   : 2009年01月15日
        作    者   : l00130025
        修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
      5.日    期   : 2012年01月11日
        作    者   : w00176964
        修改内容   : asn 解析统一调整接口头文件
      6.日    期   : 2012年02月02日
        作    者   : w00176964
        修改内容   : V7R1 PhaseIV 合入
*******************************************************************************/
#ifndef _MMC_GMM_INTERFACE_H_
#define _MMC_GMM_INTERFACE_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafTypeDef.h"
#include "NasCommDef.h"
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)
    /*_H2ASN_Include wuepsosa_msg.h*/


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 在所有结构体中的ulServiceSts使用如下的定义 */
#define     MMC_GMM_NORMAL_SERVICE                      MM_COM_SRVST_NORMAL_SERVICE
#define     MMC_GMM_LIMITED_SERVICE                     MM_COM_SRVST_LIMITED_SERVICE
#define     MMC_GMM_NO_IMSI                             MM_COM_SRVST_NO_IMSI
#define     MMC_GMM_NO_SERVICE                          MM_COM_SRVST_NO_SERVICE

#define     MMC_GMM_SYS_MSK_PLMN                        RRC_NAS_SYS_MSK_PLMN
#define     MMC_GMM_SYS_MSK_PS_DRX                      RRC_NAS_SYS_MSK_PS_DRX
#define     MMC_GMM_SYS_MSK_CSPS_INFO                   RRC_NAS_SYS_MSK_CSPS_INFO

#define     MMC_GMM_NO_FORBIDDEN                        0x0000                  /* 不在任何禁止列表中                         */
#define     MMC_GMM_FORBIDDEN_PLMN                      0x0001                  /* 在forbidden PLMN list上                  */
#define     MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS             0x0002                  /* 在forbidden PLMN for GPRS list上         */
#define     MMC_GMM_FORBIDDEN_LA_FOR_ROAM               0x0004                  /* 在forbidden LA for roaming上             */
#define     MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS       0x0008                  /* 在forbidden LA for regional provision of service上 */
#define     MMC_GMM_MS_ID_TYPE_NULL                     0
#define     MMC_GMM_MS_ID_TYPE_IMSI                     1
#define     MMC_GMM_MS_ID_TYPE_TMSI                     2

#define     MMC_GMM_ATTACH_RESLUT_PS_ONLY               0                       /* GPRS only attached                       */
#define     MMC_GMM_ATTACH_RESLUT_COMBINED              1                       /* Combined attached                        */

#define     MMC_GMM_MAX_EQUPLMN_NUM                     15                      /* 等效PLMN的最大个数                        */

#define     MMC_GMM_REAL_PROCEDURE                      0                       /* 真正发起流程                             */
#define     MMC_GMM_UNREAL_PROCEDURE                    1                       /* 没有真正发起流程                         */

/* 原语MMCGMM_PDP_STATUS_IND的结构体 */
#define     MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST        0                       /* 不存在已激活的PDP context                */
#define     MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST            1                       /* 存在已激活的PDP context                  */

#define     MMC_GMM_NO_TIMER_EXPIRED                    0
#define     MMC_GMM_T3312_EXPIRED                       1
#define     MMC_GMM_T3311_EXPIRED                       2
#define     MMC_GMM_T3302_EXPIRED                       3
#define     MMC_GMM_T3330_EXPIRED                       4

#define     MMC_GMM_SIGNALING_STATUS_ABSENT             0                       /* 不存在PS域信令连接                        */
#define     MMC_GMM_SIGNALING_STATUS_PRESENT            1                       /* 存在PS域信令连接                          */
#define     MMC_GMM_SIGNALING_STATUS_ESTING             2                       /* 正在建立PS域信令连接                       */

#define     MMCGMM_GSM_NO_FORBIDDEN                     0x0000                    /* 不在任何禁止列表中                         */
#define     MMCGMM_GSM_FORBIDDEN_PLMN                   0x0001                    /* 在forbidden PLMN list上                  */
#define     MMCGMM_GSM_FORBIDDEN_PLMN_FOR_GPRS          0x0002                    /* 在forbidden PLMN for GPRS list上         */
#define     MMCGMM_GSM_FORBIDDEN_LA_FOR_ROAM            0x0004                    /* 在forbidden LA for roaming上             */
#define     MMCGMM_GSM_FORBIDDEN_LA_FOR_REG_PRVS_SVS    0x0008                    /* 在forbidden LA for regional provision of service上 */

#define     MMC_GMM_EMERGENCY_NUM_MAX_LEN               LMM_MMC_EMERGENCY_NUM_MAX_LEN
#define     MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS      LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS /* 紧急呼最大值 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MMC_GMM_MSG_TYPE_ENUM
 结构说明  : MMC和GMM之间的原语ulMsgName
 1.日    期   : 2012年1月11日
   作    者   : w00176964
   修改内容   : ASN解析统一调整
*****************************************************************************/
enum MMC_GMM_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/  /* 备注 */
/* MMC发给GMM的原语 */
    MMCGMM_SYS_INFO_IND                         = 0,    /* _H2ASN_MsgChoice MMCGMM_SYS_INFO_IND_STRU */
    MMCGMM_COVERAGE_LOST_IND                    = 2,    /* _H2ASN_MsgChoice MMCGMM_COVERAGE_LOST_IND_STRU */
    MMCGMM_POWER_OFF_REQ                        = 4,    /* _H2ASN_MsgChoice MMCGMM_POWER_OFF_REQ_STRU */
    MMCGMM_PLMN_SEARCH_INITIATED                = 6,    /* _H2ASN_MsgChoice MMCGMM_PLMN_SEARCH_INITIATED_STRU */
    MMCGMM_START_REQ                            = 8,    /* _H2ASN_MsgChoice MMCGMM_START_REQ_STRU */
    MMCGMM_PLMN_USER_SEL_REQ                    = 10,   /* _H2ASN_MsgChoice MMCGMM_PLMN_USER_SEL_REQ_STRU */
    MMCGMM_DETACH_REQ                           = 12,   /* _H2ASN_MsgChoice MMCGMM_DETACH_REQ_STRU */

    MMCGMM_REGISTER_INITIATION                  = 14,   /* _H2ASN_MsgChoice MMCGMM_REGISTER_INITIATION_STRU */
    MMCGMM_ATTACH_REQ                           = 16,   /* _H2ASN_MsgChoice MMCGMM_ATTACH_REQ_STRU */
    MMCGMM_MODE_CHANGE_REQ                      = 18,   /* _H2ASN_MsgChoice MMCGMM_MODE_CHANGE_REQ_STRU */

    MMCGMM_EMERGENCY_NUM_LIST_IND               = 20,   /* _H2ASN_MsgChoice MMCGMM_EMERGENCY_NUM_LIST_IND */

    MMCGMM_SUSPEND_IND                          = 22,   /* _H2ASN_MsgChoice MMCGMM_SUSPEND_IND_ST */
    MMCGMM_RESUME_IND                           = 24,   /* _H2ASN_MsgChoice MMCGMM_RESUME_IND_ST */
    MMCGMM_GSM_SYS_INFO_IND                     = 26,   /* _H2ASN_MsgChoice MMCGMM_GSM_SYS_INFO_IND_ST */
    MMCGMM_REL_REQ                              = 28,   /* _H2ASN_MsgChoice MMCGMM_REL_REQ_STRU */

    MMCGMM_LTE_SYS_INFO_IND                     = 30,   /* _H2ASN_MsgChoice MMC_GMM_LTE_SYS_INFO_IND_STRU */

    /* MMC发给MM LMM的注册结果 */
    MMCGMM_LMM_ATTACH_IND                       = 32,   /* _H2ASN_MsgChoice MMCGMM_LMM_ATTACH_IND_STRU */
    MMCGMM_LMM_TAU_RESULT_IND                   = 34,   /* _H2ASN_MsgChoice MMCGMM_LMM_TAU_RESULT_IND_STRU */
    MMCGMM_LMM_MT_DETACH_IND                    = 36,   /* _H2ASN_MsgChoice MMCGMM_LMM_MT_DETACH_IND_STRU */
    MMCGMM_LMM_SERVICE_RESULT_IND               = 38,   /* _H2ASN_MsgChoice MMCGMM_LMM_SERVICE_RESULT_IND_STRU */

    MMCGMM_LMM_MO_DETACH_IND                    = 40,   /* _H2ASN_MsgChoice MMCGMM_LMM_MO_DETACH_IND_STRU */
    MMCGMM_LMM_LOCAL_DETACH_IND                 = 42,   /* _H2ASN_MsgChoice MMMCGMM_LMM_LOCAL_DETACH_IND_STRU */

    MMCGMM_LMM_STATUS_IND                       = 44,   /* _H2ASN_MsgChoice MMCGMM_LMM_STATUS_IND_STRU */
    MMCGMM_W_AC_INFO_CHANGE_IND                 = 46,   /* _H2ASN_MsgChoice MMCGMM_W_AC_INFO_CHANGE_IND_STRU */

    MMCGMM_LMM_TIMER_STATE_NOTIFY               = 48, /* _H2ASN_MsgChoice MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU */

    MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY           = 50,   /* _H2ASN_MsgChoice MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU */

    /* MMC发给GMM的消息ID用偶数 */

    /* GMM发送给MMC的原语 */
    MMCGMM_INFO_IND                             = 1,    /* _H2ASN_MsgChoice MMCGMM_INFO_IND_STRU */
    MMCGMM_PDP_STATUS_IND                       = 3,    /* _H2ASN_MsgChoice MMCGMM_PDP_STATUS_IND_STRU */
    MMCGMM_POWER_OFF_CNF                        = 5,    /* _H2ASN_MsgChoice MMCGMM_POWER_OFF_CNF_STRU */
    MMCGMM_NETWORK_DETACH_IND                   = 7,    /* _H2ASN_MsgChoice MMCGMM_NETWORK_DETACH_IND_STRU */
    MMCGMM_DETACH_CNF                           = 9,    /* _H2ASN_MsgChoice MMCGMM_DETACH_CNF_STRU */
    MMCGMM_START_CNF                            = 11,   /* _H2ASN_MsgChoice MMCGMM_START_CNF_STRU */
    MMCGMM_LOCAL_DETACH_IND                     = 13,   /* _H2ASN_MsgChoice MMCGMM_LOCAL_DETACH_IND_STRU */
    MMCGMM_GPRS_SERVICE_IND                     = 15,   /* _H2ASN_MsgChoice MMCGMM_GPRS_SERVICE_IND_STRU */
    MMCGMM_SIGNALING_STATUS_IND                 = 17,   /* _H2ASN_MsgChoice MMCGMM_SIGNALING_STATUS_IND_STRU */
    MMCGMM_SUSPEND_RSP                          = 19,   /* _H2ASN_MsgChoice MMCGMM_SUSPEND_RSP_ST */
    MMCGMM_RESUME_RSP                           = 21,   /* _H2ASN_MsgChoice MMCGMM_RESUME_RSP_ST */
    MMCGMM_REGISTER_STATE_CHANGE_IND            = 23,   /* _H2ASN_MsgChoice MMCGMM_REGISTER_STATE_CHANGE_IND_ST */
    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-15, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-15, end */
    MMCGMM_TBF_REL_IND                          = 27,   /* _H2ASN_MsgChoice MMCGMM_TBF_REL_IND_STRU */

    MMCGMM_TIN_TYPE_IND                         = 29,   /* _H2ASN_MsgChoice MMCGMM_TIN_TYPE_IND_STRU */

    MMCGMM_ATTACH_CNF                           = 33,   /* _H2ASN_MsgChoice MMCGMM_ATTACH_CNF_STRU */
    GMMMMC_PS_REG_RESULT_IND                    = 35,   /* _H2ASN_MsgChoice GMMMMC_PS_REG_RESULT_IND_STRU */
    GMMMMC_SERVICE_REQUEST_RESULT_IND           = 37,   /* _H2ASN_MsgChoice GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU */

    GMMMMC_CIPHER_INFO_IND                      = 39,   /* _H2ASN_MsgChoice MMC_GMM_CIPHER_INFO_IND_STRU */
    MMCGMM_SIM_AUTH_FAIL_IND                    = 41,  /* _H2ASN_MsgChoice MMCGMM_SIM_AUTH_FAIL_IND_STRU */

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
    GMMMMC_NETWORK_CAPABILITY_INFO_IND          = 43,   /* _H2ASN_MsgChoice GMMMMC_NETWORK_CAPABILITY_INFO_IND */
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */

    /* GMM发给MMC的消息ID用奇数 */

    MMCGMM_MSG_TYPE_BUTT
};
typedef VOS_UINT16 MMC_GMM_MSG_TYPE_ENUM_UINT16;


enum NAS_MMC_GMM_NT_DETACH_ENUM
{
    NAS_MMC_GMM_NT_DETACH_REATTACH      = 1,
    NAS_MMC_GMM_NT_DETACH_NOATTACH      = 2,
    NAS_MMC_GMM_NT_DETACH_IMSI          = 3,
    NAS_MMC_GMM_NT_DETACH_BUTT
};
typedef VOS_UINT32 NAS_MMC_GMM_NT_DETACH_ENUM_U32;

/*****************************************************************************
 枚举名    : GMM_MMC_ACTION_TYPE_ENUM
 结构说明  : GMMMMC_REG_RESULT_IND消息中GMM操作类型
 1.日    期   : 2011年7月11日
   作    者   : w00166186
   修改内容   : 新建
 2.日    期   : 2012年3月1日
   作    者   : w00176964
   修改内容   : DTS2012022407450:增加联合RAU/ATTACH的类型通知给MMC
 3.日    期   : 2013年3月30日
   作    者   : w00176964
   修改内容   : DTS2013030802929,周期性RAU需要通知LMM
*****************************************************************************/
enum GMM_MMC_ACTION_TYPE_ENUM
{
    GMM_MMC_ACTION_RAU                  = 0,
    GMM_MMC_ACTION_ATTACH               = 1,
    GMM_MMC_ACTION_COMBINED_RAU         = 2,
    GMM_MMC_ACTION_COMBINED_ATTACH      = 3,
    GMM_MMC_ACTION_PERIODC_RAU          = 4,
    GMM_MMC_ACTION_BUTT
};
typedef VOS_UINT32 GMM_MMC_ACTION_TYPE_ENUM_U32;

/*****************************************************************************
 枚举名    : GMM_MMC_ACTION_RESULT_ENUM
 结构说明  : GMMMMC_REG_RESULT_IND_STRU消息中操作的结果
 1.日    期   : 2011年7月11日
   作    者   : w00166186
   修改内容   : 新建
*****************************************************************************/
enum GMM_MMC_ACTION_RESULT_ENUM
{
    GMM_MMC_ACTION_RESULT_SUCCESS    = 0,    /*ACTION成功*/
    GMM_MMC_ACTION_RESULT_FAILURE    = 1,    /*ACTION失败*/
    GMM_MMC_ACTION_RESULT_BUTT
};
typedef VOS_UINT32 GMM_MMC_ACTION_RESULT_ENUM_U32;

/*****************************************************************************
 枚举名    : GMM_MMC_REG_DOMAIN_ENUM_UINT32
 枚举说明  : 注册的域信息
 1.日    期   : 2012年3月30日
   作    者   : l00130025
   修改内容   : 问题单
*****************************************************************************/
enum GMM_MMC_REG_DOMAIN_ENUM
{
    GMM_MMC_REG_DOMAIN_PS    = 0x00,                                            /* 注册结果域为PS域 */
    GMM_MMC_REG_DOMAIN_PS_CS = 0x01,                                            /* 注册结果域为CS+PS域 */
    GMM_MMC_REG_DOMAIN_BUTT
};
typedef VOS_UINT32 GMM_MMC_REG_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMM_MMC_ACTION_PROC_ENUM
 结构说明  : GMMMMC_REG_RESULT_IND_STRU消息中操作过程类型
 1.日    期   : 2011年7月11日
   作    者   : w00166186
   修改内容   : 新建
*****************************************************************************/
enum GMM_MMC_ACTION_PROC_ENUM
{
    GMM_MMC_ACTION_PROC_TRUE     = 0,    /*真正发起流程*/
    GMM_MMC_ACTION_PROC_FALSE    = 1,    /*没有真正发起流程*/
    GMM_MMC_ACTION_PROC_BUTT
};
typedef VOS_UINT32 GMM_MMC_ACTION_PROC_ENUM_U32;

/*****************************************************************************
 枚举名: MMC_GMM_ATTACH_TYPE_ENUM
 枚举说明:ATTACH类型
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 新建
*****************************************************************************/
enum MMC_GMM_DETACH_TYPE_ENUM
{
    MMC_GMM_PS_DETACH        = 1,
    MMC_GMM_CS_DETACH        = 2,
    MMC_GMM_PS_CS_DETACH     = 3,
    MMC_GMM_DETACH_BUTT
};
typedef VOS_UINT32 MMC_GMM_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMC_GMM_DETACH_REASON_ENUM
 结构说明  : detach原因
 1.日    期   : 2015年4月11日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
enum MMC_GMM_DETACH_REASON_ENUM
{
    MMC_GMM_DETACH_CAUSE_USER_DETACH          = 0,/* 用户触发的detach操作 */
    MMC_GMM_DETACH_CAUSE_RAT_OR_BAND_DETACH   = 1,/* system configure的RAT或Band设置触发的detach */
    MMC_GMM_DETACH_CAUSE_SRV_DOMAIN_CHANGE    = 2,/* 服务变化引起的detach */

    MMC_GMM_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 MMC_GMM_DETACH_REASON_ENUM_UINT32;

/*****************************************************************************
 枚举名: MMC_GMM_ATTACH_TYPE_ENUM
 枚举说明:
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 新建
*****************************************************************************/
enum MMC_GMM_ATTACH_TYPE_ENUM
{
    MMC_GMM_ATTACH_TYPE_NULL          = 0,
    MMC_GMM_ATTACH_TYPE_GPRS          = 1,
    MMC_GMM_ATTACH_TYPE_IMSI          = 2,
    MMC_GMM_ATTACH_TYPE_GPRS_IMSI     = 3,
    MMC_GMM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_GMM_ATTACH_TYPE_ENUM_UINT32;

enum MMCGMM_SGSN_REL_VER_ENUM
{
    MMCGMM_SGSN_RELEASE98_OR_OLDER        = 0,
    MMCGMM_SGSN_RELEASE99_ONWARDS         = 1,
    MMCGMM_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   MMCGMM_SGSN_REL_VER_ENUM_U8;

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
/*****************************************************************************
 枚举名: NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM
 枚举说明: GMM指示给MMC的服务类型
 1.日    期   : 2012年8月04日
   作    者   : s46746
   修改内容   : 新建
*****************************************************************************/
enum NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM
{
    NAS_MMC_GMM_GPRS_SERVICE_ATTACH               = 0,
    NAS_MMC_GMM_GPRS_SERVICE_PAGING               = 1,
    NAS_MMC_GMM_GPRS_SERVICE_PDPACT               = 2,
    NAS_MMC_GMM_GPRS_SERVICE_DATA                 = 3,
    NAS_MMC_GMM_GPRS_SERVICE_BUTT
};
typedef VOS_UINT32   NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32;
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-24, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-24, end */

/*****************************************************************************
 枚举名: GMM_MMC_NW_EMC_BS_CAP_ENUM
 枚举说明: 网络的EMC BS支持能力
 1.日    期   : 2013年7月9日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum GMM_MMC_NW_EMC_BS_CAP_ENUM
{
    GMM_MMC_NW_EMC_BS_NOT_SUPPORTED       = 0,
    GMM_MMC_NW_EMC_BS_SUPPORTED           = 1,

    GMM_MMC_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8;

/*****************************************************************************
 枚举名: GMM_MMC_LTE_CS_CAPBILITY_ENUM
 枚举说明: LTE CS能力
 1.日    期   : 2013年7月9日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum GMM_MMC_LTE_CS_CAPBILITY_ENUM
{
    GMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    GMM_MMC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    GMM_MMC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    GMM_MMC_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    GMM_MMC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */

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
/* 原语MMCGMM_SYS_INFO_IND的结构体 */
typedef struct
{
    /* 约定：按照从ULONG的最低字节开始到次高字节为止的顺序依次存储MCC和MNC的digit1、digit2、digit3 */
    VOS_UINT32             ulMcc;                                                    /* MCC,3 bytes                              */
    VOS_UINT32             ulMnc;                                                    /* MNC,2 or 3 bytes                         */
}MMCGMM_PLMN_ID_STRU;


typedef struct
{

    MSG_HEADER_STRU             MsgHeader;                                      /* 消息头                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                  ulCellId;
    VOS_UINT32                  ulCnCommonSize;                                 /* CN Common信息的字节长度                    *
                                                                                 * 0：不包含CN Common NAS System Infomation  */
    VOS_UINT8                   aucCnCommonInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];     /* aulCnCommonInfo[0] b0 - b7：第一字节；    *
                                                                                 * aulCnCommonInfo[0] b8 - b15：第二字节；   *
                                                                                 * ...                                      *
                                                                                 * aulCnCommonInfo[1] b0 - b7：第五字节；    *
                                                                                 * ...                                      */
    VOS_UINT32                  ulPsInfoSize;                                        /* PS域相关信息的字节长度* * 0：CS域信息不存在 */
    VOS_UINT32                  aulPsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP/4];           /* aulPsInfo[0] b0 - b7：第一字节；          *
                                                                                 * aulPsInfo[0] b8 - b15：第二字节；         *
                                                                                 * ...                                      *
                                                                                 * aulPsInfo[1] b0 - b7：第五字节；          *
                                                                                 * ...                                      */

    VOS_UINT32                  ulMask;                                              /* 以下各IE的有效标志                         */

    MMCGMM_PLMN_ID_STRU         PlmnId;                                              /* 本小区所在PLMN的ID                        */
    VOS_UINT32                  ulPsDrxLength;                                       /* PS域DRX长度系数                           */


    VOS_UINT32                  ulForbiddenMask;                                     /* 是否在禁止列表中                           */
    VOS_UINT32                  ulUserSrchFlg;          /* 是否是用户指定搜网 */


    VOS_UINT8                   ucCsChanged2UnBarFlg;             /* 是否CS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8                   ucPsChanged2UnBarFlg;             /* 是否PS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8                   aucReserve[2];

}MMCGMM_SYS_INFO_IND_STRU;

/* MMCGMM_SUSPEND_IND的消息结构 */
/* 参数宏值请参见RRMM_SUSPEND_IND_ST中的说明 */
/*****************************************************************************
 结构名    : MMCGMM_SUSPEND_IND_ST
 结构说明  : MMCGMM_SUSPEND_IND的数据结构
 1.日    期: 2011年10月27日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增挂起目的方
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSuspendCause;                         /* 挂起原因 */
    VOS_UINT8                           ucSuspendOrigen;                        /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA*/
    MMC_SUSPEND_DESTINATION_UINT8       ucSuspendDestination;                   /* 挂起的目的方 */
    VOS_UINT8                           aucReserve1[1];                         /* 保留 */
}MMCGMM_SUSPEND_IND_ST;

/* MMCGMM_RESUME_IND的消息结构 */
/* 参数宏值请参见RRMM_RESUME_IND_ST中的说明 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT8               ucCsResumeResult;                                   /* CS域切换结果 */
    VOS_UINT8               ucPsResumeResult;                                   /* PS域切换结果 */
    VOS_UINT8               ucResumeOrigen;                                     /* 消息发起方，RRMM_ORIGEN_GSM:GSM，RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8               ucPsSigExistFlg;                                    /* CS信令连接存在标记 */
}MMCGMM_RESUME_IND_ST;

/* MMCGMM_SUSPEND_RSP的消息结构 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT8               ucResult;                                           /*WRRC/RR需要处理挂起失败的情况，NAS在有些情况下挂起会失败*/
    VOS_UINT8               aucReserve1[3];                                     /* 保留 */
}MMCGMM_SUSPEND_RSP_ST;

/* MMCGMM_RESUME_RSP的消息结构 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                                         /* 保留*/
}MMCGMM_RESUME_RSP_ST;

/* MMCGMM_REGISTER_STATE_CHANGE_IND的消息结构 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT8               GmmRegState;

    VOS_UINT8               aucReservel[3];
}MMCGMM_REGISTER_STATE_CHANGE_IND_ST;

/* 原语MMCGMM_COVERAGE_LOST_IND的结构体 */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
}MMCGMM_COVERAGE_LOST_IND_STRU;

/* 原语MMCGMM_COMBINED_ATTACH_ACCEPTED的结构体 */
typedef struct
{
    VOS_UINT32            ulIdType;

    VOS_UINT8            aucTmsi[4];
} MMC_GMM_MS_IDENTITY_STRU;


/* 原语MMCGMM_NETWORK_DETACH_IND的结构体 */
typedef struct
{

    MSG_HEADER_STRU             MsgHeader;                                      /* 消息头                                   */ /*_H2ASN_Skip*/


    VOS_UINT32                   ulDetachType;                                       /* Detach类型                               */

    VOS_UINT32                   ulDetachCause;                                      /* Detach原因                               */


    VOS_UINT32                  ulServiceSts;                                        /* 服务状态                                 */


}MMCGMM_NETWORK_DETACH_IND_STRU;


/*******************************************************************************
 结构名    : GMMMMC_PS_REG_RESULT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMM向MMC发送Attach/RAU结果消息的结构体
 1.日    期   : 2011年7月11日
   作    者   : w00166186
   修改内容   : 新建
 2.日    期   : 2011年10月8日
   作    者   : s46746
   修改内容   : V7R1 phase II,将EPLMN、RPLMN移到MM/GMM维护

 3.日    期   : 2012年2月9日
   作    者   : w00167002
   修改内容   : 删除真假流程的判断字段

 4.日    期   : 2012年03月30日
   作    者   : l00130025
   修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                           MsgHeader;                        /* 消息头    */ /*_H2ASN_Skip*/
    GMM_MMC_ACTION_TYPE_ENUM_U32              enGmmActionType;
    GMM_MMC_ACTION_RESULT_ENUM_U32            enActionResult;


	GMM_MMC_REG_DOMAIN_ENUM_UINT32        	  enReqDomain;                     /* 当前注册的结果域，Ps Only或CS_PS */
	GMM_MMC_REG_DOMAIN_ENUM_UINT32        	  enRsltDomain;                     /* 当前注册的结果域，Ps Only或CS_PS */


    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16        enRegFailCause;                   /* 操作失败原因                             */
	NAS_MML_NET_RAT_TYPE_ENUM_UINT8           enNetType;                        /* 当前注册的网络类型 */
    VOS_UINT8                                 ucReserved;
    VOS_UINT32                                ulRegCounter;                     /* Attach attempt counter                   */
    VOS_UINT32                                ulServiceStatus;                  /* 服务状态                                 */
}GMMMMC_PS_REG_RESULT_IND_STRU;

/*******************************************************************************
 结构名    : GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMM向MMC发送SR结果消息的结构体
 1.日    期   : 2011年7月11日
   作    者   : w00166186
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                           MsgHeader;                        /* 消息头    */ /*_H2ASN_Skip*/
    GMM_MMC_ACTION_RESULT_ENUM_U32            enActionResult;                   /* 操作的结果 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16        enRegFailCause;                   /* 操作失败原因 */
    VOS_UINT32                                ulServiceSts;                     /* 服务状态 */
}GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU;


/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
/*******************************************************************************
 结构名    : GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMM向MMC发送网络能力信息提示
 1.日    期   : 2013年7月9日
   作    者   : y00245242
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                        MsgHeader;          /* _H2ASN_Skip */
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8    enNwImsVoCap;
    GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8       enNwEmcBsCap;
    GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8    enLteCsCap;
    VOS_UINT8                              aucReserve[1];
}GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */

/*****************************************************************************
 结构名    : MMCGMM_DETACH_REQ_STRU
 结构说明  : MMCGMM_DETACH_REQ消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 增加Opid
 2.日    期   : 2015年4月11日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;                           /* detach原因                               */

    MMC_GMM_DETACH_REASON_ENUM_UINT32   enDetachReason;
} MMCGMM_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : MMCGMM_DETACH_CNF_STRU
 结构说明  : MMCGMM_DETACH_CNF消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 增加Opid
 2.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : phaseIV调整:增加detach类型IE项，disable场景需要判断
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    VOS_UINT32                          ulServiceSts;                           /* PS服务状态                                 */

    VOS_UINT32                          ulDetachType;                           /* detach 类型 */
}MMCGMM_DETACH_CNF_STRU;

/* 原语MMCGMM_POWER_OFF_REQ的结构体 */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMCGMM_POWER_OFF_REQ_STRU;

/* 原语MMCGMM_POWER_OFF_CNF的结构体 */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMCGMM_POWER_OFF_CNF_STRU;

/* 消息MMCGMM_INFO_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                                      /*_H2ASN_Skip*/

    NAS_MM_INFO_IND_STRU        stMmInfo;
}MMCGMM_INFO_IND_STRU;

typedef struct
{

    MSG_HEADER_STRU            MsgHeader;                                       /* 消息头    */ /*_H2ASN_Skip*/

    VOS_UINT32                  ulPdpStatusFlg;                                 /* 存在已激活的PDP context标志              */
}MMCGMM_PDP_STATUS_IND_STRU;

/* 消息MMCGMM_PLMN_SEARCH_INITIATED的结构体 */
typedef struct
{

    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                  ulReserve;                                      /* 保留                                     */
} MMCGMM_PLMN_SEARCH_INITIATED_STRU;

/* 消息MMCGMM_ABORT_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMCGMM_REL_REQ_STRU;

/* 消息MMCGMM_START_REQ的结构体 */
typedef struct
{

    MSG_HEADER_STRU             MsgHeader;                                       /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                  ulReserved;                     /* 保留*/
}MMCGMM_START_REQ_STRU;

/* 消息MMCGMM_START_CNF的结构体 */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
}MMCGMM_START_CNF_STRU;

/* 消息MMCGMM_PLMN_USER_SEL_REQ的结构体 */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
}MMCGMM_PLMN_USER_SEL_REQ_STRU;

/* 消息MMCGMM_LOCAL_DETACH_IND的结构体 */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/

    VOS_UINT32               ulDetachCause ;                                         /* detach原因                               */


    VOS_UINT32                  ulServiceSts;                                        /* 服务状态                                 */

} MMCGMM_LOCAL_DETACH_IND_STRU;

typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMCGMM_REGISTER_INITIATION_STRU;

typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* 保留*/
} MMCGMM_TBF_REL_IND_STRU;

typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                   ulSignalingSts;                                     /* PS域信令连接状态                          */
} MMCGMM_SIGNALING_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_ATTACH_REQ_STRU
 结构说明  : MMCGMM_ATTACH_REQ消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   : 增加Opid
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    MMC_GMM_ATTACH_TYPE_ENUM_UINT32     enAttachType;                           /* 注册请求类型                                */
} MMCGMM_ATTACH_REQ_STRU;

/*****************************************************************************
 结构名    : MMCGMM_ATTACH_CNF_STRU
 结构说明  : MMCGMM_ATTACH_CNF消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : w00166186
   修改内容   :增加Opid
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA定义使用，记录ATTACH编号 */
    VOS_UINT32                          ulServiceStatus ;                       /* PS域服务状态 */
}MMCGMM_ATTACH_CNF_STRU;

 /*****************************************************************************
 结构名    : MMCGMM_W_AC_INFO_CHANGE_IND_STRU
 结构说明  : MMCGMM_W_AC_INFO_CHANGE_IND消息的数据结构
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                              /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enCsRestrictRegisterChange;         /* CS注册受限改变情况 */
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enPsRestrictRegisterChange;         /* PS注册受限改变情况 */
}MMCGMM_W_AC_INFO_CHANGE_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_MODE_CHANGE_REQ_STRU
 结构说明  : MMCGMM_MODE_CHANGE_REQ_STRU消息的数据结构
 1.日    期   : 2011年7月01日
   作    者   : zhoujun \40661
   修改内容   : 手机模式修改
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* 消息头                                    */ /*_H2ASN_Skip*/
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;                                           /* 用户模式                                 */
    VOS_UINT8                           aucReservel[3];
} MMCGMM_MODE_CHANGE_REQ_STRU;


/*****************************************************************************
 结构名    : MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU
 结构说明  : MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY消息的数据结构
  2.日    期   : 2015年2月2日
    作    者   : s00217060
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                      /* 消息头                                    */ /*_H2ASN_Skip*/
} MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU;


/* 消息 MMCGMM_GSM_SYS_INFO_IND 结构体 */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* 消息头    */ /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU    stPlmnId;                     /* 本小区PLMN ID */
    VOS_UINT32          ulForbiddenFlg;               /* 与本小区相关的禁止信息                     */
    VOS_UINT16          usCellId;                     /* 本小区 ID  */
    VOS_UINT16          usLac;                        /* [0x0001－0xFFFE] 位置区码  */
    VOS_UINT8           ucAttachDetach;               /* [0-1] 用于通知MS，在本小区内是否允许进行IMSI结合和分离允许过程:
                                                         0表示不允许手机启动IMSI附着和分离过程，
                                                         1则表示手机必须启动附着和分离过程，message origin:SI3,PSI2 */
    VOS_UINT8           ucLRTimerT3212;               /* [0-255] 周期位置更新定时器,确定了手机进行周期位置更新的频度,
                                                         每1个单位表示6分钟的时间，为0则表示不进行位置更新，message origin:SI3,PSI2 */
    VOS_UINT8           ucGprsSupportInd;             /* [0-1] GPRS支持指示:0-不支持;1-支持*/
    VOS_UINT8           ucRac;                        /* 路由区域码*/

    VOS_UINT8           ucNetworkOperationMode;       /*   网络运行模式:
                                                           0-无效;
                                                           1-网络运行模式I;
                                                           2-网络运行模式II;
                                                           3-网络运行模式III; */
    VOS_UINT8           ucDrxTimerMax;                /* [0,1,2,4,8,16,32,64]s   */

    MMCGMM_SGSN_REL_VER_ENUM_U8    ucSgsnRelease;       /* [0-1] 0 SGSN is Release '98 or older
                                                              1 SGSN is Release '99 onwards */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    RRC_NAS_RESTRICTION_UN              unAcInfo;
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    VOS_UINT32                      ulUserSrchFlg;


    VOS_UINT8                   ucCsChanged2UnBarFlg;             /* 是否CS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8                   ucPsChanged2UnBarFlg;             /* 是否PS域从bar转为不bar: 0 无，1 有 */
    VOS_UINT8                   aucReserve[2];

}MMCGMM_GSM_SYS_INFO_IND_ST;

/* 消息MMCGMM_SERVICE_STATUS_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/

    VOS_UINT32               ulServiceStatus ;
} MMCGMM_SERVICE_STATUS_IND_STRU;


/* 消息MMCGMM_GPRS_SERVICE_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
	NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32     enGprsServiceType;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */
}MMCGMM_GPRS_SERVICE_IND_STRU;


/*****************************************************************************
 结构名称: MMCGMM_TIN_TYPE_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:

 1.日    期   : 2011年10月28日
   作    者   : w00167002
   修改内容   : 字节对齐
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头    */ /*_H2ASN_Skip*/
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    VOS_UINT8                           aucReservel[3];
} MMCGMM_TIN_TYPE_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_SIM_AUTH_FAIL_IND_STRU
 结构说明  : MMCGMM_SIM_AUTH_FAIL_IND_STRU的数据结构
 1.日    期: 2013年11月16日
   作    者: m00217266
   修改内容:
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                              /* 消息头  */ /*_H2ASN_Skip*/
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16       enSimAuthFailValue;
    VOS_UINT8                               ucReservel;
    NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain;
}MMCGMM_SIM_AUTH_FAIL_IND_STRU;


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 结构名    : MMCGMM_LMM_ATTACH_IND_STRU
 结构说明  : MMCGMM_LMM_ATTACH_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知GMM关于LMM的attach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_ATTACH_IND_STRU MMCGMM_LMM_ATTACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_LMM_TAU_RESULT_IND_STRU
 结构说明  : MMCGMM_LMM_TAU_RESULT_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知GMM关于LMM的TAU结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_TAU_RESULT_IND_STRU MMCGMM_LMM_TAU_RESULT_IND_STRU;


/*****************************************************************************
 结构名    : MMCGMM_LMM_MT_DETACH_IND_STRU
 结构说明  : MMCGMM_LMM_MT_DETACH_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知GMM关于LMM的detach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_DETACH_IND_STRU MMCGMM_LMM_MT_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_LMM_SERVICE_RESULT_IND_STRU
 结构说明  : MMCGMM_LMM_SERVICE_RESULT_IND的数据结构
 1.日    期: 2011年10月26日
   作    者: w00176964
   修改内容: V7R1 PhaseIII阶段调整:新增MMC通知GMM关于LMM的service结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_SERVICE_RESULT_IND_STRU MMCGMM_LMM_SERVICE_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_LMM_MO_DETACH_IND_STRU
 结构说明  : MMCGMM_LMM_MO_DETACH_IND的数据结构
 1.日    期: 2011年11月28日
   作    者: w00176964
   修改内容: V7R1 PhaseIV阶段调整:新增MMC通知GMM关于LMM的UE detach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_DETACH_CNF_STRU MMCGMM_LMM_MO_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_LMM_LOCAL_DETACH_IND_STRU
 结构说明  : MMCGMM_LMM_LOCAL_DETACH_IND_STRU的数据结构
 1.日    期: 2011年12月6日
   作    者: w00176964
   修改内容: V7R1 PhaseIV阶段调整:新增MMC通知GMM关于LMM的LOCAL detach结果的数据结构
*****************************************************************************/
typedef  LMM_MMC_DETACH_IND_STRU MMCGMM_LMM_LOCAL_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_LMM_STATUS_IND_STRU
 结构说明  : MMCGMM_LMM_STATUS_IND的数据结构
 1.日    期: 2012年03月02日
   作    者: l00130025
   修改内容: DTS2012022102014:新增MMC通知GMM关于LMM的STATUS_IND的数据结构
*****************************************************************************/
typedef  LMM_MMC_STATUS_IND_STRU MMCGMM_LMM_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : MMC_GMM_LTE_SYS_INFO_IND_STRU
 结构说明  : MMC_GMM_LTE_SYS_INFO_IND的数据结构
 1.日    期: 2012年04月26日
   作    者: w00166186
   修改内容: 新增结构
*****************************************************************************/
typedef  LMM_MMC_SYS_INFO_IND_STRU MMC_GMM_LTE_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU
 结构说明  : MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU的数据结构
 1.日    期: 2012年2月27日
   作    者: z00161729
   修改内容: V7R1 C50 支持ISR功能调整:新增MMC通知GMM关于LMM定时器状态的数据结构
*****************************************************************************/
typedef  LMM_MMC_TIMER_STATE_NOTIFY_STRU MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_GMM_EMERGENCY_NUM_STRU
 结构说明  : 用于发送的MMCGMM_EMERGENCY_NUM_LIST_IND数据结构
 1.日    期: 2014年5月21日
   作    者: b00269685
   修改内容: DTS2014050604659新增
*****************************************************************************/
typedef  LMM_MMC_EMERGENCY_NUM_STRU MMC_GMM_EMERGENCY_NUM_STRU;

/*****************************************************************************
 结构名    : MMCGMM_EMERGENCY_NUM_LIST_IND_STRU
 结构说明  : MMCGMM_EMERGENCY_NUM_LIST_IND的数据结构
 1.日    期: 2014年5月22日
   作    者: B00269685
   修改内容: DTS2014050604659新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;

    VOS_UINT8                               ucOpEmcNumList;

    VOS_UINT8                               ucEmergencyNumAmount;

    VOS_UINT8                               aucReserved[2];

    MMC_GMM_EMERGENCY_NUM_STRU              astEmergencyNumList[MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS];
} MMCGMM_EMERGENCY_NUM_LIST_IND_STRU;
#endif


/*****************************************************************************
 结构名    : MMC_GMM_CIPHER_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GMM主动上报MMC，加密算法更新
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头  _H2ASN_Skip*/
    VOS_UINT8                           ucGprsCipherAlg;                        /* GPRS加密算法 */
    VOS_UINT8                           ucGprsCipher;                           /* VOS_TRUE:加密启动,VOS_FALSE:加密不启动。*/
    VOS_UINT8                           aucRsv[2];                              /* 预留位 */
}MMC_GMM_CIPHER_INFO_IND_STRU;
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
    MMC_GMM_MSG_TYPE_ENUM_UINT16         enMsgID;    /*_H2ASN_MsgChoice_Export MMC_GMM_MSG_TYPE_ENUM_UINT32*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用MMC_GMM_MSG_TYPE_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMC_GMM_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MMC_GMM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMC_GMM_MSG_DATA                    stMsgData;
}MmcGmmInterface_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif

