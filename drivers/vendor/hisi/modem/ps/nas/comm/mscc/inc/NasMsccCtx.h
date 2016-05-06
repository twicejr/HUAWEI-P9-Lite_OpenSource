/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccCtx.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年1月26日
  最近修改   :
  功能描述   : NasMsccCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月26日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_MSCC_CTX_H__
#define __NAS_MSCC_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccPifInterface.h"
#include "NasCommDef.h"
#include "VosPidDef.h"
#include "NasFsm.h"
#include "MsccMmcInterface.h"
#include "hsd_mscc_pif.h"
#include "MsccMmcInterface.h"
#include "NasMsccMlplMsplParse.h"

#include "ImsaMsccInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_MAX_MSG_BUFFER_LEN                         (1600)    /* Maximum number of bytes for message buffer */

#define NAS_MSCC_MAX_MODULE_NUM                             (4)       /* Maximum number of modules that can be started*/

#define NAS_MSCC_MAX_FSM_STACK_DEPTH                        (4)       /* Maximum stack depth of the MSCC module */

#define NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM                    (8)       /* Maximum number of the Cache messages */

#define NAS_MSCC_MAX_INT_MSG_QUEUE_NUM                      (8)       /* Maximum number of internal messages */

#define NAS_MSCC_PLATFORM_MAX_RAT_NUM                       (7)       /* Maximum number of RATs supported */

#define NAS_MSCC_INVALID_MCC                                (0xFFFFFFFF) /* Used in the assignment of default MCC value */

#define NAS_MSCC_INVALID_MNC                                (0xFFFFFFFF) /* Used in the assignment of default MNC value */

#define NAS_MSCC_INVALID_RAC                                (0xFF)    /* Used in the assignment of default RAC value */

#define NAS_MSCC_INVALID_CELL_ID                            (0xFFFFFFFF) /* Used in the assignment of default Cell ID value */

#define NAS_MSCC_INVALID_LAC                                (0xFFFF)  /* Used in the assignment of default LAC value */

#define NAS_MSCC_SIM_RAT_E_UTRN                             (0x4000)

#define NAS_MSCC_BYTES_IN_SUBNET                            (16)

#define NAS_MSCC_WILDCARD_SID                               (0)

#define NAS_MSCC_WILDCARD_NID                               (65535)


#define NAS_MSCC_MAX_IMSI_LENGTH                            (9)

#define NAS_MSCC_SIM_FORMAT_PLMN_LEN                        (3)     /* Sim卡格式的Plmn长度 */

#define NAS_MSCC_BYTE_MASK                                  (0xFF)
#define NAS_MSCC_MAX_DIGIT_VALUE                            (9)
#define NAS_MSCC_LOW_BYTE_INVALID                           (0x0F)
#define NAS_MSCC_OCTET_LOW_FOUR_BITS                        (0x0f)  /* 获取一个字节中的低4位 */
#define NAS_MSCC_OCTET_HIGH_FOUR_BITS                       (0xf0)  /* 获取一个字节中的高4位 */
#define NAS_MSCC_OCTET_MOVE_FOUR_BITS                       (0x04)  /* 将一个字节移动4位 */
#define NAS_MSCC_OCTET_MOVE_SIXTEEN_BITS                    (0x10)  /* 将一个字节移动16位 */
#define NAS_MSCC_OCTET_MOVE_EIGHT_BITS                      (0x08)  /* 将一个字节移动8位 */

#define NAS_MSCC_MAX_SYS_NUM_IN_ACQUIRE_LIST                (8)

#define NAS_MSCC_SYSCFG_MAX_MODULE_NUM                      (3)       /* Maximum number of mudules in system config request */


#define NAS_MSCC_INVALID_SID                                (-1)
#define NAS_MSCC_INVALID_NID                                (-1)

/* 封装OSA申请消息接口 */
#define NAS_MSCC_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC, (ulMsgLen))

/* 封装OSA消息头 */
#define NAS_MSCC_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
           { \
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = UEPS_PID_MSCC;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
           }

/* 封装OSA消息头(MSCC内部消息) */
#define NAS_MSCC_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            NAS_MSCC_CFG_MSG_HDR(pstMsg, UEPS_PID_MSCC, ulMsgId)

/* 获取OSA消息内容 */
#define NAS_MSCC_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* 获取OSA消息长度 */
#define NAS_MSCC_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* 封装OSA消息初始化消息内容接口 */
#define NAS_MSCC_CLR_MSG_ENTITY(pstMsg)\
            PS_MEM_SET(NAS_MSCC_GET_MSG_ENTITY(pstMsg), 0x0, NAS_MSCC_GET_MSG_LENGTH(pstMsg))

/* 封装OSA发送消息接口 */
#define NAS_MSCC_SEND_MSG(pstMsg)\
            PS_SEND_MSG(UEPS_PID_MSCC, pstMsg)

#define NAS_MSCC_MAX_LOG_MSG_STATE_NUM                      (150)

/* 1x有服务时CL系统捕获的最大阶段数 */
#define NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX                   (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_TWO)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8
 结构说明  : IMS voice capability
 1.日    期   : 2015年1月26日
   作    者   : y0024524
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_NW_IMS_VOICE_CAP_ENUM
{
    NAS_MSCC_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    NAS_MSCC_NW_IMS_VOICE_SUPPORTED        = 1,

    NAS_MSCC_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8
 结构说明  : network EMC BS capability
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_NW_EMC_BS_CAP_ENUM
{
    NAS_MSCC_NW_EMC_BS_NOT_SUPPORTED       = 0,
    NAS_MSCC_NW_EMC_BS_SUPPORTED           = 1,

    NAS_MSCC_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8
枚举说明  : persistent bearer是否存在状态枚举
1.日    期   : 2015年5月12日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
enum NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM
{
    NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST = 0,
    NAS_MSCC_PERSISTENT_BEARER_STATE_EXIST     = 1,
    NAS_MSCC_PERSISTENT_BEARER_STATE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8
 结构说明  : network EMC BS capability
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_LTE_CS_CAPBILITY_ENUM
{
    NAS_MSCC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    NAS_MSCC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    NAS_MSCC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    NAS_MSCC_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    NAS_MSCC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_LTE_CS_CAPBILITY_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_SYS_MODE_ENUM_UINT8
 结构说明  : 驻留网络的系统模式枚举
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_SYS_MODE_ENUM
{
    NAS_MSCC_SYS_MODE_GSM,
    NAS_MSCC_SYS_MODE_WCDMA,
    NAS_MSCC_SYS_MODE_LTE,

    NAS_MSCC_SYS_MODE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_SYS_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_SYS_SUBMODE_ENUM_UINT8
 结构说明  : 驻留网络的系统子模式枚举
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_SYS_SUBMODE_ENUM
{
    NAS_MSCC_SYS_SUBMODE_NONE                = 0,                                /* 无服务 */
    NAS_MSCC_SYS_SUBMODE_GSM                 = 1,                                /* GSM模式 */
    NAS_MSCC_SYS_SUBMODE_GPRS                = 2,                                /* GPRS模式 */
    NAS_MSCC_SYS_SUBMODE_EDGE                = 3,                                /* EDGE模式 */
    NAS_MSCC_SYS_SUBMODE_WCDMA               = 4,                                /* WCDMA模式 */
    NAS_MSCC_SYS_SUBMODE_HSDPA               = 5,                                /* HSDPA模式 */
    NAS_MSCC_SYS_SUBMODE_HSUPA               = 6,                                /* HSUPA模式 */
    NAS_MSCC_SYS_SUBMODE_HSDPA_HSUPA         = 7,                                /* HSDPA+HSUPA模式 */
    NAS_MSCC_SYS_SUBMODE_TD_SCDMA            = 8,                                /* TD_SCDMA模式 */
    NAS_MSCC_SYS_SUBMODE_HSPA_PLUS           = 9,                                /* HSPA+模式 */
    NAS_MSCC_SYS_SUBMODE_LTE                 = 10,                               /* LTE模式 */
    NAS_MSCC_SYS_SUBMODE_DC_HSPA_PLUS        = 17,                               /* DC-HSPA+模式 */
    NAS_MSCC_SYS_SUBMODE_DC_MIMO             = 18,                               /* MIMO-HSPA+模式 */

    NAS_MSCC_SYS_SUBMODE_CDMA_1X             = 23,                               /* CDMA2000 1X*/
    NAS_MSCC_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_SYS_SUBMODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_LMM_ACCESS_TYPE_ENUM
 结构说明  : LTE的接入模式EUTRAN_TDD/FDD
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_LMM_ACCESS_TYPE_ENUM
{
    NAS_MSCC_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    NAS_MSCC_LMM_ACCESS_TYPE_EUTRAN_FDD      = 1,

    NAS_MSCC_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_LMM_ACCESS_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_SERVICE_STATUS_ENUM_UINT8
 结构说明  : cs/ps域服务状态
 1.日    期: 2015年1月26日
   作    者: y00245242
   修改内容: 新增
*****************************************************************************/
enum NAS_MSCC_SERVICE_STATUS_ENUM
{
    NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* 正常服务 */
    NAS_MSCC_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* 限制服务 */
    NAS_MSCC_SERVICE_STATUS_NO_SERVICE               = 2,                        /* 无服务 */

    NAS_MSCC_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_SERVICE_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_VOICE_DOMAIN_ENUM_UINT32
 结构说明  : VOICE优选域
 1.日    期   : 2015年01月27日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_VOICE_DOMAIN_ENUM
{
    NAS_MSCC_VOICE_DOMAIN_CS_ONLY            = 0,                                /**< CS voice only */
    NAS_MSCC_VOICE_DOMAIN_IMS_PS_ONLY        = 1,                                /**< IMS PS voice only */
    NAS_MSCC_VOICE_DOMAIN_CS_PREFERRED       = 2,                                /**< CS voice preferred, IMS PS Voice as secondary */
    NAS_MSCC_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,                                /**< IMS PS voice preferred, CS Voice as secondary */

    NAS_MSCC_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_MSCC_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_SYS_ACQ_SCENE_ENUM
 枚举说明  : 各种系统捕获场景的定义
 1.日    期   : 2015年04月03日
   作    者   : m00312079
   修改内容   : 新建
 2.日    期   : 2015年12月10日
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE新增捕获场景
*****************************************************************************/
enum NAS_MSCC_SYS_ACQ_SCENE_ENUM
{
    NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON                 = 0,/* 开机 */
    NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED,      /* available定时器超时触发的OOS搜索 */
    NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST,                    /* hrpd 丢网 */
    NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST,                     /* lte  丢网 */
    NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED,          /* sleep 定时器超时 */
    NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET,                  /* system configure设置触发搜网 */
    NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE,             /* LTE RF资源可用 */
    NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE,            /* HRPD RF资源可用 */
    NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER,                   /* 主叫触发 */

    NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE,                                       /* LTE不可用,只搜HRPD */

    NAS_MSCC_SYS_ACQ_SCENE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_PRIOR_SYS_ENUM
 枚举说明  : CL模式下系统优先级
 1.日    期   : 2015年04月03日
   作    者   : m00312079
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_PRIOR_SYS_ENUM
{
    NAS_MSCC_LTE_PRIOR                      = 0,  /* LTE最优 */
    NAS_MSCC_HRPD_PRIOR                     = 1,  /* HRPD最优 */

    NAS_MSCC_PRIOR_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PRIOR_SYS_ENUM_UINT8;

/****************************************************************************
enum name  :   NAS_MSCC_FSM_ID_ENUM_UINT32
Description     :   Contains the FSM IDs of the MSCC Module
Modify History:
    1)  Date    :   2015-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-04-02
        Author  :   y00307564
        Modify content :    Modify for CDMA Iteration 10
    3)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :新增CL intersys状态机
****************************************************************************/
enum NAS_MSCC_FSM_ID_ENUM
{
    /* L1 Main FSM. This is the default FSM of the MSCC module */
    NAS_MSCC_FSM_L1_MAIN                                    =0x00,

    /* Switch ON FSM that is responsible for Start Process */
    NAS_MSCC_FSM_SWITCH_ON                                  =0x01,

    /* Power OFF FSM that is responsible for Start Process */
    NAS_MSCC_FSM_POWER_OFF                                  =0x02,

    /* system acquire state machine */
    NAS_MSCC_FSM_SYS_ACQ                                    =0x03,

    /* better system reselection(BSR) FSM that is responsible for Start Process */
    NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION                  =0x04,

    /* system config FSM which deals with system config process in MSCC */
    NAS_MSCC_FSM_SYSTEM_CONFIG                              =0X05,

    /* CL异系统状态机 */
    NAS_MSCC_FSM_CL_INTERSYS                                =0x06,

    /* Invalid FSM ID */
    NAS_MSCC_BUTT
};
typedef VOS_UINT32 NAS_MSCC_FSM_ID_ENUM_UINT32;


enum NAS_MSCC_LC_RAT_COMBINED_ENUM
{
    NAS_MSCC_LC_RAT_COMBINED_GUL,
    NAS_MSCC_LC_RAT_COMBINED_CL,

    NAS_MSCC_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 NAS_MSCC_LC_RAT_COMBINED_ENUM_UINT8;


enum NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM
{
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID,                  /* initial acquire location info is invalid */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_NO_SEARCH_MLPL,           /* initial acquire location info is valid but not used to search mlpl */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_FAIL,         /* initial acquire location info is valid but search mlpl failed */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_LTE_PRIO,     /* initial acquire location info is valid and search mlpl result is lte prio */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_HRPD_PRIO,    /* initial acquire location info is valid and search mlpl result is hrpd prio */

    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8;



enum NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM
{
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_NULL                    = 0x00,
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MLPL                    = 0x01,
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MSPL                    = 0x02,

    NAS_MSCC_WAIT_CARD_READ_CNF_FLG_BUTT
};
typedef VOS_UINT32 NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32;


enum NAS_MSCC_MLPL_MSPL_SOURCE_ENUM
{
    NAS_MSCC_MLPL_MSPL_SOURCE_NULL,
    NAS_MSCC_MLPL_MSPL_SOURCE_CARD,
    NAS_MSCC_MLPL_MSPL_SOURCE_NV,
    NAS_MSCC_MLPL_MSPL_SOURCE_DEFAULT,

    NAS_MSCC_MLPL_MSPL_SOURCE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32;





enum NAS_MSCC_SYS_ACQ_STATUS_ENUM
{
    NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED,                    /* the system is no searched */

    NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_REGISTERED,            /* the system is searched success and register succ */

    NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_NO_EXIST,              /* the system is searched fail and no coveraged in this area */

    NAS_MSCC_SYS_ACQ_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_SYS_ACQ_STATUS_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_INIT_CTX_TYPE_ENUM
 结构说明  : 初始化MSCC CTX类型
 1.日    期   : 2015年4月27日
   作    者   : y00174758
   修改内容   : 新增
*****************************************************************************/
enum NAS_MSCC_INIT_CTX_TYPE_ENUM
{
    NAS_MSCC_INIT_CTX_STARTUP                               = 0,
    NAS_MSCC_INIT_CTX_POWEROFF                              = 1,
    NAS_MSCC_INIT_CTX_BUTT
};
typedef VOS_UINT8 NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_RAT_MODE_TYPE_ENUM_UINT8
 枚举说明  : 定义RAT变化类型
 1.日    期   : 2015年08月21日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_RAT_MODE_CHG_TYPE_ENUM
{
    NAS_MSCC_RAT_MODE_CHG_GUL_TO_GUL,
    NAS_MSCC_RAT_MODE_CHG_GUL_TO_CL,
    NAS_MSCC_RAT_MODE_CHG_CL_TO_GUL,
    NAS_MSCC_RAT_MODE_CHG_CL_TO_CL,

    NAS_MSCC_RAT_MODE_CHG_BUTT
};
typedef VOS_UINT8 NAS_MSCC_RAT_MODE_CHG_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MSCC_AVAILABLE_TIMER_TYPE_ENUM_UINT32
 结构说明  : available定时器启动时类型
 1.日    期   : 2015年12月10日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_AVAILABLE_TIMER_TYPE_ENUM
{
    NAS_MSCC_AVAILABLE_TIMER_TYPE_OOS_SRCH                      = 1,                /* available定时器启动时类型为OOS场景搜网 */
    NAS_MSCC_AVAILABLE_TIMER_TYPE_1X_SERVICE_LTE_HISTORY_SRCH   = 2,                /* available定时器启动时类型为1x有服务的L的历史频点搜网 */
    NAS_MSCC_AVAILABLE_TIMER_TYPE_1X_SERVICE_LTE_FULL_BAND_SRCH = 3,                /* available定时器启动时类型为1x有服务的L的全频段搜网 */
    NAS_MSCC_AVAILABLE_TIMER_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_AVAILABLE_TIMER_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM
 枚举说明  : 1X有服务时CL的系统捕获阶段枚举定义,当前只支持两个阶段,后续可以扩展更多阶段
 1.日    期   : 2015年12月10日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM
{
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE               = 1,
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_TWO               = 2,
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM
 枚举说明  : 发起初搜的时候，当前是在等GUL的位置信息，还是在等C的位置信息
 1.日    期   : 2015年12月10日
   作    者   : j00354216
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_GUL = 0,
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X  = 1,
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32;

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
 结构名    : NAS_MSCC_IMS_RAT_SUPPORT_STRU
 结构说明  : IMS支持信息
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranImsSupportFlag;  /**< UNTRAN IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranEmsSupportFlag;  /**< UNTRAN EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           aucReserved[2];
}NAS_MSCC_IMS_RAT_SUPPORT_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_IMS_CONFIG_PARA_STRU
 结构说明  : IMS配置信息
 1.日    期   : 2015年1月27日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    NAS_MSCC_IMS_RAT_SUPPORT_STRU       stImsRatSupport;                        /* different RAT IMS support */
    NAS_MSCC_VOICE_DOMAIN_ENUM_UINT32   enVoiceDomain;
    VOS_UINT32                          ulWaitImsVoiceAvailTimerLen;            /* 等待IMS VOICE 可用的定时器时长 */
}NAS_MSCC_IMS_CONFIG_PARA_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_NETWORK_CAP_INFO_STRU
 结构说明  : 当前驻留的网络的能力信息
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8                    enNwImsVoCap;
    NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8                       enNwEmcBsCap;
    NAS_MSCC_LTE_CS_CAPBILITY_ENUM_UINT8                    enLteCsCap;
    VOS_UINT8                                               aucReserved[1];
}NAS_MSCC_NETWORK_CAP_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_3GPP_SYS_INFO_STRU
 结构说明  : 服务小区信息
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2015年4月11日
   作    者   : w00176964
   修改内容   : CDMA Iteraiton 11 Modified
 3.日    期   : 2015年9月21日
   作    者   : y00346957
   修改内容   : DTS2015070910885 Modified
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCampOnFlg;
    NAS_MSCC_SYS_MODE_ENUM_UINT8        enSysMode;
    NAS_MSCC_LMM_ACCESS_TYPE_ENUM_UINT8 enLmmAccessType;
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enPrioClass;                    /* 当前系统对应的prio class,目前只在CL模式下有效，GUL下LTE下会赋值,其他模式可以忽略 */

    VOS_UINT32                          ulCellId;
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmnId;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRoamFlag;                     /* 当前驻留网络是否漫游 VOS_TRUE:漫游网络 VOS_FALSE:非漫游网络 */
}NAS_MSCC_3GPP_SYS_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucCampOnFlg;
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   en1xPrioClass;  /* sys_type为CDMA2000_1X时的PRI class */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enAIPrioClass;  /* sys_type为CDMA2000_AI时的PRI class */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT32                          ulMcc;  /* NAS格式的MCC，例如461: 0x00010604 */
    VOS_UINT32                          ulMnc;  /* NAS格式的MNC，例如03 : 0x000f0300 */
}NAS_MSCC_1X_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucCampOnFlg;
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enHrpdPrioClass;  /* sys_type为CDMA2000_HRPD时的PRI class */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enAIPrioClass;    /* sys_type为CDMA2000_AI时的PRI class */
    VOS_UINT8                           ucSubNetMask;
    VOS_UINT32                          ulMcc;  /* NAS格式的MCC，例如461: 0x00010604 */
    VOS_UINT8                           aucSectorId[NAS_MSCC_BYTES_IN_SUBNET];
}NAS_MSCC_HRPD_SYS_INFO_STRU;


typedef struct
{
    NAS_MSCC_1X_SYS_INFO_STRU           st1xSysInfo;
    NAS_MSCC_HRPD_SYS_INFO_STRU         stHrpdSysInfo;
}NAS_MSCC_3GPP2_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_SYS_INFO_STRU
 结构说明  : 当前驻留的网络信息
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2015年4月11日
   作    者   : w00176964
   修改内容   : CDMA Iteration 10 Modified
*****************************************************************************/
typedef struct
{
    NAS_MSCC_3GPP_SYS_INFO_STRU         st3gppSysInfo;      /* 3gpp当前驻留PLMN信息 */
    NAS_MSCC_3GPP2_SYS_INFO_STRU        st3gpp2SysInfo;     /* 3gpp2当前驻留PLMN信息 */
}NAS_MSCC_SYS_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU   stEhPlmnInfo;                          /* EHPLMN列表信息 */
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU stUserPlmnInfo;                        /* UPLMN列表信息 */
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU stOperPlmnInfo;                        /* OPLMN列表信息 */
}NAS_MSCC_SIM_PLMN_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimStatus;
    VOS_UINT8                           ucSimCsRegStatus;    /* SIM卡CS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/
    VOS_UINT8                           ucSimPsRegStatus;    /* SIM卡PS域的注册结果导致的卡是否有效VOS_TRUE:PS域的卡有效,VOS_FALSE:PS域的卡无效*/
}NAS_MSCC_SIM_STATUS_STRU;


typedef struct
{
    NAS_MSCC_SIM_STATUS_STRU            stSimStatus;                            /* SIM卡状态 */
    NAS_MSCC_SIM_PLMN_INFO_STRU         stSimPlmnInfo;                          /* SIM卡中保存的PLMN信息 */
    VOS_UINT8                           ucIsCardChanged;                        /* SIM卡是否发生改变 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
}NAS_MSCC_SIM_INFO_STRU;


typedef struct
{
    VOS_UINT8                           uc1xActiveFlg;                 /* power save cnf, we consider this mode is deactived,while acquire
                                                                           system in this mode,we consider this mode is actived */
    VOS_UINT8                           ucHrpdActiveFlg;
    VOS_UINT8                           uc3gppActiveFlg;                /* in CL system acqruie flow, we only power save LTE, but for syscfg procedure,
                                                                           we maybe power save GSM or UTRAN or LTE, so this flag indicate the current
                                                                           active mode in 3GPP active or deacitve */
    VOS_UINT8                           ucPowerSaveReplyFlg;            /* VOS_TRUE:  need reply power save result to upplayer
                                                                           VOS_FALSE: need not reply power save result to upplayer */
}NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU;


typedef struct
{
    VOS_UINT16      usNum;                                                      /* Number of RATs supported */
    VOS_UINT16      usIndex;                                                    /* Current index of the Request sequence */
    VOS_UINT32      aulModuleID[NAS_MSCC_SYSCFG_MAX_MODULE_NUM];                /* List of Module IDs  */
}NAS_MSCC_PREF_ORDER_MODULE_LIST;

/*****************************************************************************
 结构名    : NAS_MSCC_NO_CARD_INIT_SEARCH_CDMA_LOC_STRU
 结构说明  : 无卡初搜C模获得的位置信息

  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_INT32                           lSid;               /* 无卡初搜，X模初搜获取到的SID */
    VOS_INT32                           lNid;               /* 无卡初搜，X模初搜获取到的NID */
    VOS_UINT32                          ulMcc;              /* 无卡初搜，X模初搜获取到的MCC，MMA通过查询表获取，通过MMA_MSCC_SYSTEM_ACQUIRE_REQ带给MSCC */
}NAS_MSCC_NO_CARD_INIT_SEARCH_CDMA_LOC_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU
 结构说明  : 无卡初搜获得的位置信息

  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stInitSearchGulLoc;            /*  无卡初搜，GUL初搜获取到的位置信息  */
    NAS_MSCC_NO_CARD_INIT_SEARCH_CDMA_LOC_STRU              stInitSearchCdmaLoc;           /*  无卡初搜，C模初搜获取到的位置信息  */
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enInitSearchWaitType;          /*  无卡初搜，当前等待的是GUL的位置信息还是C的位置信息 */
    VOS_UINT8                                               ucIsLocInfoUsed;               /*  初搜位置信息是否被使用过，位置信息只使用一次，使用后值位，TRUE:已使用过，FALSE:未使用 */
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU
Description     :   Structure definition the System Acquire CTRL context info.
Modify History:
    1)  Date    :   2015-04-28
        Author  :   t00323010
        Modify content :    Create
    2)  Date    :   2015-06-04
        Author  :   w00176964
        Modify content :CDMA Iteration 15 Modified:add data service on 1x flag
    3)  Date    :   2015-09-19
        Author  :   y00346957
        Modify content :DTS2015070910885 modify
    4)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整:增加1x有服务时系统捕获阶段
    5)  Date    :   2015-12-10
        Author  :   j00354216
        Modify content :CL_MUTIMODE_OPTIMIZE调整:增加无卡初搜位置信息
****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCurrBsrTimerLen;            /* 记录正在运行的BSR Timer长度 */
    VOS_RATMODE_ENUM_UINT32                                 enOrigBsrTimerStartRat;       /* 记录上次启动BSR Timer定时器的驻留制式 */
    VOS_UINT8                                               ucAllowSrchLteFlg;            /* 是否允许搜索lte */
    VOS_UINT8                                               ucSysAcqMoCallFlag;           /* 1X上存在呼叫标记 */
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enCur1xServiceSysAcqPhaseNum; /* 当前处于1x有服务时哪个捕获阶段 */
    VOS_UINT8                                               ucIsEmcCallExist;
    VOS_UINT32                                              ulCallBackEnableFlg;

    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                   stNoCardInitSearchLoc;
}NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU;






typedef struct
{
    NAS_MSCC_PREF_ORDER_MODULE_LIST                         stSysCfgModuleOrder;
    NAS_MSCC_PREF_ORDER_MODULE_LIST                         stPowerSaveModuleOrder;
}NAS_MSCC_FSM_SYSCFG_CTX_STRU;


typedef struct
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  en1xServiceStatus;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdServiceStatus;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  en3gppPsServiceStatus;
    VOS_UINT8                           aucRsv[1];
}NAS_MSCC_SERVICE_STATUS_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucHrpdConnExistFlg;
    VOS_UINT8                           ucLteEpsConnExistFlg;
    VOS_UINT8                           aucRsv[2];
}NAS_MSCC_CONN_STATUS_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;  /* NAS格式的MCC，例如461: 0x00010604 */
    VOS_UINT32                          ulMnc;  /* NAS格式的MNC，例如03 : 0x000f0300 */
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;

    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   en1xPrioClass;  /* sys_type为CDMA2000_1X时的PRI class */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enAIPrioClass;  /* sys_type为CDMA2000_AI时的PRI class */
    VOS_UINT8                           aucRsv[2];
}NAS_MSCC_1X_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enPrioClass;                    /* 当前系统对应的prio class,目前只在CL模式下有效，GUL下LTE下会赋值,其他模式可以忽略 */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_LTE_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucIsLocInfoUsedInSwitchOn;
    NAS_MSCC_LC_RAT_COMBINED_ENUM_UINT8 enSysAcqMode;
    VOS_UINT8                           ucCdma1xActiveFlag;
    VOS_UINT8                           ucLteActiveFlag;
    NAS_MSCC_1X_LOC_INFO_STRU           st1xLocationInfo;
    NAS_MSCC_LTE_LOC_INFO_STRU          stLteLocationInfo;
}NAS_MSCC_MMSS_LOCATION_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_IMS_DOMAIN_INFO_STRU
 结构说明  : IMS域信息
 1.日    期   : 2015年5月12日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8             enPersistentBearerState;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8                      enImsVoiceCap;
    VOS_UINT8                                               ucReserved[2];
}NAS_MSCC_IMS_DOMAIN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_SEND_TO_IMSA_INFO_STRU
 结构说明  : MSCC已经发送给IMSA的信息

  1.日    期   : 2015年11月23日
    作    者   : c00318887
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_SEND_TO_IMSA_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_NW_INFO_STRU
 结构说明  : 与网络相关信息
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新建
   修改内容   : 新建
 2.日    期   : 4/4/2015
   作    者   : w00176964
   修改内容   : CDMA Iteration 10 Modified
 3.日    期   : 2015年5月12日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
typedef struct
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU                          stLteNwCapInfo;
    NAS_MSCC_NETWORK_CAP_INFO_STRU                          stGuNwCapInfo;
    NAS_MSCC_SYS_INFO_STRU                                  stSysInfo;
    NAS_MSCC_SERVICE_STATUS_INFO_STRU                       stServiceStatusInfo;
    NAS_MSCC_CONN_STATUS_INFO_STRU                          stConnStatusInfo;
    NAS_MSCC_IMS_DOMAIN_INFO_STRU                           stImsDomainInfo;
    NAS_MSCC_SEND_TO_IMSA_INFO_STRU                         stSendToImsaInfo;
}NAS_MSCC_NW_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[NAS_MSCC_MAX_MSG_BUFFER_LEN];
}NAS_MSCC_MSG_STRU;


typedef struct
{
    VOS_UINT32                                              ulWaitCardReadFlag;
}NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU;


typedef struct
{
    VOS_UINT16                                              usNum;  /* Number of RATs supported */
    VOS_UINT16                                              usIndex;    /* Current index of the Request sequence */
    VOS_UINT32                                              aulModuleID[NAS_MSCC_MAX_MODULE_NUM];   /* List of Module IDs  */

    NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU              stCardReadInfo;
}NAS_MSCC_FSM_SWITCH_ON_CTX_STRU;


typedef struct
{
    VOS_UINT16      usNum;                                                      /* Number of RATs supported */
    VOS_UINT16      usIndex;                                                    /* Current index of the Request sequence */
    VOS_UINT32      aulModuleID[NAS_MSCC_MAX_MODULE_NUM];                       /* List of Module IDs  */
}NAS_MSCC_FSM_POWER_OFF_CTX_STRU;


typedef struct
{
    VOS_UINT8                                               ucAcqFinishFlg;             /* initial acq finished flag VOS_TRUE:finish;VOS_FALSE:not finish */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enLocInfoStatus;            /* initial acquire location info status */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_1X_LOC_INFO_STRU                               st1xLocInfo;
}NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU;


typedef struct
{
    VOS_UINT8                                               ucAcqFinishFlg;             /* initial acq finished flag VOS_TRUE:finish;VOS_FALSE:not finish */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enLocInfoStatus;            /* initial acquire location info status */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_LTE_LOC_INFO_STRU                              stLteLocInfo;
}NAS_MSCC_SYS_ACQ_LTE_INIT_LOC_STA_STRU;



typedef struct
{
    VOS_RATMODE_ENUM_UINT32             ulRatMode;
    NAS_MSCC_SYS_ACQ_STATUS_ENUM_UINT8  enAcqStatus;
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_SYS_ACQ_SYS_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucInitialAcqSysNum;                 /* initial acquire system num */
    VOS_UINT8                           ucNormalAcqSysNum;                  /* normal acquire system num */
    VOS_UINT8                           aucRsv[2];
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU      astInitialAcqSysList[NAS_MSCC_MAX_SYS_NUM_IN_ACQUIRE_LIST];
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU      astNormalAcqSysList[NAS_MSCC_MAX_SYS_NUM_IN_ACQUIRE_LIST];
}NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucNeedReAcqLteFlg;
    VOS_UINT8                                               ucAbortFlg;
    VOS_UINT8                                               ucSearchLteFlag;          /* 尝试搜过Lte的标志 */
    VOS_UINT8                                               ucSearchHrpdFlag;         /* 尝试搜过Hrpd的标志 */
    NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU                   st1xInitLocSta;
    NAS_MSCC_SYS_ACQ_LTE_INIT_LOC_STA_STRU                  stLteInitLocSta;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                     stSysAcqListInfo;
}NAS_MSCC_FSM_SYS_ACQ_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
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
    VOS_UINT8                           ucLteHistorySrchNum;       /* 该阶段LTE历史频点搜索总次数 */
    VOS_UINT8                           ucLteFullBandSrchNum;      /* 该阶段LTE全频段搜索总次数 */
    VOS_UINT8                           aucRsv[2];
 } NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU
 结构说明  : 1x有服务时CL系统捕获策略结构体
 1.日    期   : 2015年1月27日
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
typedef struct
{
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseOnePatternCfg;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseTwoPatternCfg;
}NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_1X_SERVICE_AVAILABLE_TIMER_CTX_STRU
 结构说明  : 1X有服务时available定时器上下文结构
 1.日    期   : 2015年12月10日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCurLteHistorySrchCount;          /* 当前历史频点已搜索的次数 */
    VOS_UINT8                           ucCurLteFullBandSrchCount;         /* 当前全频段已搜索的次数 */
    VOS_UINT8                           aucRsv[2];
}NAS_MSCC_1X_SERVICE_AVAILABLE_TIMER_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_OOS_AVAILABLE_TIMER_CTX_STRU
 结构说明  : OOS时available定时器上下文结构
 1.日    期   : 2015年12月10日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAvailableTimerCount;                  /* current Available Timer start count */
}NAS_MSCC_OOS_AVAILABLE_TIMER_CTX_STRU;


/****************************************************************************
Structure name  :   NAS_MSCC_FSM_L1_MAIN_CTX_STRU
Description     :   Structure definition L1 MAIN fsm ctx info
Modify History:
    1)  Date    :   2015-04-03
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE修改
****************************************************************************/
typedef struct
{
    NAS_MSCC_OOS_AVAILABLE_TIMER_CTX_STRU                   stOosAvailableTimerCtx;                 /* OOS场景available定时器信息 */
    NAS_MSCC_1X_SERVICE_AVAILABLE_TIMER_CTX_STRU            st1xServiceAvailableTimerCtx;           /* 1x有服务场景available定时器信息 */
}NAS_MSCC_FSM_L1_MAIN_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucHrpdSysNum;
    VOS_UINT8                           aucReserve[3];
    MSCC_MMC_HRPD_SYS_STRU              astHrpdSysList[MSCC_MMC_BG_HRPD_MAX_SYS_NUM];
}NAS_MSCC_BG_SEARCH_HRPD_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_HRPD_SYS_REC_ITEM_STRU
 结构说明  : 系统表中HRPD项信息
 1.日    期   : 2015年04月07日
   作    者   : y00307564
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usAcqIndex;         /* 此系统记录指向的ACQ表的Index */
    VOS_UINT16                                              usSysIndex;         /* 此HRPD系统记录在系统表中的Index */
    VOS_UINT8                                               ucPrioLevel;        /* 指示HRPD的优先级，取值从1开始 */
    NAS_MSCC_PIF_PREF_NEG_SYS_ENUM_UINT8                    enPrefNegSys;       /* 此系统是否为negative或preferred */
    VOS_UINT8                                               aucRcv[2];
}NAS_MSCC_HRPD_SYS_REC_ITEM_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_SYSTEM_ACQUIRE_FREQ_INFO_STRU
 结构说明  : 高优先级搜网频点信息
 1.日    期   : 2015年04月07日
   作    者   : y00307564
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU  stFreq;              /* 存放HRPD的频点信息 */
    NAS_MSCC_HRPD_SYS_REC_ITEM_STRU     stHrpdSysItem;       /* 高优先级网对应的HRPD系统信息 */
} NAS_MSCC_SYSTEM_ACQUIRE_FREQ_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucFreqNum;                          /* 频点个数 */
    VOS_UINT8                                               aucReserved[3];
    NAS_MSCC_SYSTEM_ACQUIRE_FREQ_INFO_STRU                  astFreqInfo[MSCC_HSD_MAX_PREF_SUBNET_NUM];
}NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU;


typedef struct
{
    VOS_UINT8                      uc1XPowerSaveFlg;
    VOS_UINT8                      ucHrpdPowerSaveFlg;
    VOS_UINT8                      uc3GppPowerSaveFlg;
    VOS_UINT8                      aucReserved[1];
}NAS_MSCC_POWER_SAVE_OPERATION_STRU;


typedef struct
{
    NAS_MSCC_BG_SEARCH_HRPD_INFO_STRU                       stBgSearchHrpdInfo;
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                 stHighPriSysInfo;
}NAS_MSCC_BSR_HRPD_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucAbortFlag;
    VOS_UINT8                                               ucOrigSysMsplIndex;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enDestBsrSysPriClass;      /* 需要发起BSR的系统的pri class */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType;          /* 需要发起BSR的系统的sys type */
    VOS_UINT8                                               ucOrigSysUseDefMsplRec;       /* 原始系统是否是default mspl rec */
    VOS_UINT8                                               aucRsv[3];

    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stPrefPlmnList;
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                 stHighPriSysInfo;
}NAS_MSCC_FSM_BSR_CTX_STRU;


typedef union
{
    /* context structure storing L1 main ctx */
    NAS_MSCC_FSM_L1_MAIN_CTX_STRU       stL1MainCtx;

    /* Context structure storing the Switch On Module Order */
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU     stSwitchOnCtx;

    /* Context Structure storing the Power Off Module Order. */
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU     stPowerOffCtx;

    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU       stSysAcqCtx;

    NAS_MSCC_FSM_BSR_CTX_STRU           stBsrCtx;

    NAS_MSCC_FSM_SYSCFG_CTX_STRU        stSysCfgCtx;
}NAS_MSCC_FSM_EXTRA_CTX_UNION;




typedef struct
{
    NAS_MSCC_PIF_RAT_PRIO_STRU          stRatPrio;
}NAS_MSCC_MS_SYS_CFG_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucIsBsrTimerNvimActiveFlag;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulAvailableTimerLengthFirstSearch;
    VOS_UINT32                          ulAvailableTimerCountFirstSearch;
    VOS_UINT32                          ulAvailableTimerLengthDeepSearch;
    VOS_UINT32                          ulScanTimerLen;
    VOS_UINT32                          ulBsrTimerLen;
    VOS_UINT32                          ulSleepTimerLen;
    VOS_UINT32                          ulBsrTimerLenWithNoMatchedMsplRec;/* 原始系统不在MSPL表中时,bsr定时器时长 */
}NAS_MSCC_SYSACQ_TIMER_CFG_STRU;


typedef struct
{
     VOS_UINT8                          ucReAcqLteOnHrpdSyncIndFlag;
     VOS_UINT8                          ucIs1xLocInfoPrefThanLte;
     VOS_UINT8                          aucReserved[2];
     NAS_MSCC_SYSACQ_TIMER_CFG_STRU     stSysAcqTimerCfg;

}NAS_MSCC_MMSS_SYSACQ_CFG_STRU;


typedef struct
{
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU       stMmssSysAcqCfg;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU    stMmssLastLocInfo;
}NAS_MSCC_MMSS_CFG_INFO_STRU;


typedef struct
{
    NAS_MSCC_MLPL_STRU                                      stMlplInfo;
    NAS_MSCC_MSPL_STRU                                      stMsplInfo;
    VOS_UINT8                                               ucMlplValid;
    VOS_UINT8                                               ucMsplValid;
    VOS_UINT8                                               ucRsv[2];
}NAS_MSCC_MLPL_MSPL_INFO_STRU;



typedef struct
{
    VOS_UINT8                                     ucRatNum;
    VOS_UINT8                                     aucReserved[3];
    VOS_RATMODE_ENUM_UINT32                       aenRatList[NAS_MSCC_PLATFORM_MAX_RAT_NUM];
}NAS_MSCC_PLATFORM_RAT_CAP_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_DYNLOAD_CTRL_STRU
 结构说明  : 动态加载控制信息
 1.日    期   : 2015年8月27日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableDynloadTW;      /* 是否激活TW动态加载 */
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_DYNLOAD_CTRL_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_CUSTOM_CONFIG_STRU
Description     :   Structure definition containing the Containing the NV Values
Modify History:
    1)  Date    :   2015-04-04
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-08-27
        Author  :   w00242748
        Modify content :动态加载项目，新增结构stDynloadCtrl
    3)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content: CL_MUTIMODE_OPTIMIZE调整:增加1x有服务时CL捕获策略控制NV
****************************************************************************/
typedef struct
{
    NAS_MSCC_PLATFORM_RAT_CAP_STRU                          stPlatformRatCap;
    NAS_MSCC_IMS_CONFIG_PARA_STRU                           stImsCfgInfo;
    NAS_MSCC_MMSS_CFG_INFO_STRU                             stMmssNvimCfgInfo;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU     st1xSrvClSysAcqStrategy;    /* 1x有服务时CL系统捕获策略NV信息 */
}NAS_MSCC_CUSTOM_CONFIG_STRU;




typedef struct
{
    /* FSM Descriptor containing the State table, init handle  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* Stores the ID of the current FSM */
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    /* Stores the ID of the parent FSM */
    NAS_MSCC_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* Stores the Event type of the parent FSM */
    VOS_UINT32                          ulParentEventType;

    /* Stores the current state of the FSM */
    VOS_UINT32                          ulState;

    /* Stores the current entry message  */
    NAS_MSCC_MSG_STRU                   stEntryMsg;

    /* Stores Context details specific to FSM */
    NAS_MSCC_FSM_EXTRA_CTX_UNION        unFsmCtx;

}NAS_MSCC_FSM_CTX_STRU;


typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* Stores the current Stack depth */
    VOS_UINT8                           aucReserved[2] ;                        /* Required for padding */
    NAS_MSCC_FSM_CTX_STRU               astFsmStack[NAS_MSCC_MAX_FSM_STACK_DEPTH];  /* Array of FSM contexts */
}NAS_MSCC_FSM_STACK_STRU;


typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* Stores the number of Cache messages */
    VOS_UINT8                           aucReserve[3];                          /* Required for padding */
    NAS_MSCC_MSG_STRU                   astCacheMsg[NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM]; /* Queue of cache messages */
}NAS_MSCC_CACHE_MSG_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* Number of internal messages */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[NAS_MSCC_MAX_INT_MSG_QUEUE_NUM]; /* Queue of internal messages */
}NAS_MSCC_INT_MSG_QUEUE_STRU;


typedef struct
{
    NAS_MSCC_CUSTOM_CONFIG_STRU         stCustomCfgInfo;
    NAS_MSCC_MS_SYS_CFG_INFO_STRU       stMsSysCfgInfo;                         /* syscfgex setting info */
}NAS_MSCC_MS_CFG_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_MODEM_PID_TAB_STRU
 结构说明  : DSDA 两个modem接收AT发送消息的PID映射表

  1.日    期   : 2015年5月21日
    作    者   : w00242748
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulModem0Pid;
    VOS_UINT32                           ulModem1Pid;
}NAS_MSCC_MODEM_PID_TAB_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_MSG_STATE_STRU
 结构说明  : 消息上报结构体

  1.日    期   : 2015年7月12日
    作    者   : y00322978
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReceiveTime;  /* 接收时间 */
    VOS_UINT32                          ulExitTime;     /* 结束时间 */
    VOS_UINT16                          usSendPid;      /* 发送PID */
    VOS_UINT16                          usReceivePid;   /* 接收PID */
    VOS_UINT16                          usMsgName;      /* 消息名 */
    VOS_UINT8                           ucMsccFsmId;    /* MSCC状态机ID  */
    VOS_UINT8                           ucMsccState;    /* MSCC当前状态  */
}NAS_MSCC_MSG_STATE_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_LOG_EVENT_STATUS_STRU
 结构说明  :  mscc 可维可测勾取发送接收消息

  1.日    期   : 2015年7月12日
    作    者   : y00322978
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    NAS_MSCC_MSG_STATE_STRU             stMsgState[NAS_MSCC_MAX_LOG_MSG_STATE_NUM];
    VOS_UINT8                           ucLatestIndex;
    VOS_UINT8                           ucReserve[3];
}NAS_MSCC_LOG_MSG_STATUS_STRU;
/*****************************************************************************
 结构名    : NAS_MSCC_MNTN_CTX_STRU
 结构说明  : mscc 可维可测勾取发送接收消息

  1.日    期   : 2015年7月12日
    作    者   : y00322978
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    NAS_MSCC_LOG_MSG_STATUS_STRU        stLogMsgState;
}NAS_MSCC_MNTN_CTX_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_CTX_STRU
 结构说明  : NAS MSCC 模块运行上下文
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2015年04月11日
   作    者   : y00245242
   修改内容   : CDMA Iteration 10 Modified:add mspl info

*****************************************************************************/
typedef struct
{
    NAS_MSCC_FSM_CTX_STRU                                   stCurFsm;                               /* 状态机当前的状态机数组 */
    NAS_MSCC_FSM_STACK_STRU                                 stFsmStack;                             /* 状态机的状态机栈数组   */
    NAS_MSCC_CACHE_MSG_QUEUE_STRU                           stCacheMsgQueue;
    NAS_MSCC_INT_MSG_QUEUE_STRU                             stIntMsgQueue;
    NAS_MSCC_SIM_INFO_STRU                                  stSimInfo;
    NAS_MSCC_MS_CFG_INFO_STRU                               stMsCfgInfo;
    NAS_MSCC_TIMER_CTX_STRU                                 astMsccTimerCtx[TI_NAS_MSCC_TIMER_BUTT];/* MSCC当前正在运行的定时器资源 */
    NAS_MSCC_NW_INFO_STRU                                   stNwInfo;
    NAS_MSCC_MLPL_MSPL_INFO_STRU                            stMlplMsplInfo;
    NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU                       stPowerSaveCtrl;                       /* power save控制上下文 */
    NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU                          stSysAcqCtrl;
    NAS_MSCC_MNTN_CTX_STRU                                  stMntnInfo;

}NAS_MSCC_CTX_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_SYS_ACQ_SCENE_MAP_LTE_SRCH_TYPE_STRU
Description     :   系统捕获场景映射LTE搜索类型表结构
Modify History:
    1)  Date    :   2015-12-31
        Author  :   w00176964
        Modify content :Create
****************************************************************************/

typedef struct
{
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;           /* 系统捕获场景 */
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enLteSrchType;           /* lte的搜索类型 */
}NAS_MSCC_SYS_ACQ_SCENE_MAP_LTE_SRCH_TYPE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
NAS_MSCC_CTX_STRU* NAS_MSCC_GetMsccCtxAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitCtx(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8 enInitType
);

VOS_VOID NAS_MSCC_InitNetworkInfo(
    NAS_MSCC_NW_INFO_STRU               *pstNwInfo
);

VOS_VOID NAS_MSCC_SetGuNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstGuNwCap);

NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetGuNwCapInfo(VOS_VOID);

VOS_VOID NAS_MSCC_SetLteNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstLteNwCap);

NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MSCC_GetPersistentBearerState(VOS_VOID);
VOS_VOID    NAS_MSCC_SetPersistentBearerState(
    NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8             enPersistentBearerState
);
MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  NAS_MSCC_GetImsVoiceCapability(VOS_VOID);
VOS_VOID    NAS_MSCC_SetImsVoiceCapability(
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8             enImsVoiceCap
);
NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetLteNwCapInfo(VOS_VOID);

NAS_MSCC_SYS_INFO_STRU *NAS_MSCC_GetCurrSysInfo(VOS_VOID);
NAS_MSCC_SERVICE_STATUS_INFO_STRU *NAS_MSCC_GetCurrServiceStatusInfo(VOS_VOID);

NAS_MSCC_TIMER_CTX_STRU *NAS_MSCC_GetTimerCtxAddr(VOS_VOID);

NAS_MSCC_IMS_CONFIG_PARA_STRU *NAS_MSCC_GetImsCfgInfo(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetWaitImsVoiceAvailTimerLen(VOS_VOID);

VOS_VOID  NAS_MSCC_LoadSubFsm(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId,
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID NAS_MSCC_InitFsmL2(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
);
VOS_VOID NAS_MSCC_PopFsm( VOS_VOID );

VOS_VOID NAS_MSCC_PushFsm(
    NAS_MSCC_FSM_STACK_STRU             *pstFsmStack,
    NAS_MSCC_FSM_CTX_STRU               *pstNewFsm
);

VOS_VOID NAS_MSCC_QuitFsmL2(VOS_VOID);

VOS_VOID  NAS_MSCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 NAS_MSCC_GetFsmTopState(VOS_VOID);

NAS_MSCC_CACHE_MSG_QUEUE_STRU* NAS_MSCC_GetCacheMsgAddr(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetCacheMsgNum(VOS_VOID);

VOS_UINT32  NAS_MSCC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);
VOS_UINT32 NAS_MSCC_GetNextCachedMsg(
    NAS_MSCC_MSG_STRU                  *pstEntryMsg
);

NAS_MSCC_FSM_CTX_STRU* NAS_MSCC_GetCurFsmAddr(VOS_VOID);

NAS_FSM_DESC_STRU* NAS_MSCC_GetCurFsmDesc(VOS_VOID);

NAS_MSCC_FSM_ID_ENUM_UINT32 NAS_MSCC_GetCurrFsmId(VOS_VOID);

NAS_MSCC_MSG_STRU* NAS_MSCC_GetCurrFsmEntryMsgAddr(VOS_VOID);

VOS_UINT8* NAS_MSCC_GetCurrFsmEntryMsgBufferAddr(VOS_VOID);

NAS_MSCC_FSM_STACK_STRU* NAS_MSCC_GetFsmStackAddr(VOS_VOID);

VOS_UINT16 NAS_MSCC_GetFsmStackDepth(VOS_VOID);

NAS_MSCC_INT_MSG_QUEUE_STRU* NAS_MSCC_GetIntMsgQueueAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitInternalBuffer(
    NAS_MSCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_VOID NAS_MSCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *NAS_MSCC_GetNextIntMsg(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetIntMsgNum(VOS_VOID);


VOS_VOID NAS_MSCC_ClearCacheMsg(
    VOS_UINT8                           ucIndex
);

VOS_VOID NAS_MSCC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID NAS_MSCC_InitCacheMsgQueue(
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
);


VOS_VOID NAS_MSCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_FSM_SWITCH_ON_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_SwitchOn(VOS_VOID);

VOS_VOID NAS_MSCC_SetModuleOrder_SwitchOn(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetNextModuleId_SwitchOn(
    VOS_UINT32                         *pulNextModuleId
);

VOS_UINT32 NAS_MSCC_IsModuleOrderValid_SwitchOn(VOS_VOID);

NAS_MSCC_FSM_POWER_OFF_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_PowerOff(VOS_VOID);

VOS_VOID NAS_MSCC_SetModuleOrder_PowerOff(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetNextModuleId_PowerOff(
    VOS_UINT32                         *pulNextModuleId
);

VOS_UINT32 NAS_MSCC_IsModuleOrderValid_PowerOff(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp2(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupportLte(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupportCdma1X(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupportCdmaEVDO(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetImsSupportFlag(VOS_VOID);

NAS_MSCC_PLATFORM_RAT_CAP_STRU*  NAS_MSCC_GetPlatformRatCap(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
);


VOS_VOID NAS_MSCC_InitCurrFsmCtx(
    NAS_MSCC_FSM_CTX_STRU              *pstCurrFsmCtx
);

VOS_VOID NAS_MSCC_InitFsmStackCtx(
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack
);

VOS_VOID NAS_MSCC_InitTimerCtx(
    NAS_MSCC_TIMER_CTX_STRU            *pstTimerCtx
);

NAS_MSCC_MS_CFG_INFO_STRU* NAS_MSCC_GetMsCfgInfoStruAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_SwitchOn(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_PowerOff(VOS_VOID);

NAS_MSCC_FSM_SYS_ACQ_CTX_STRU* NAS_MSCC_GetSysAcqFsmCtxAddr(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_InitFsmCtx_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_BSR(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_CLInterSys(VOS_VOID);


#endif

NAS_MSCC_SYSACQ_TIMER_CFG_STRU* NAS_MSCC_GetSysAcqTimerCfgAddr(VOS_VOID);

NAS_MSCC_MMSS_LOCATION_INFO_STRU* NAS_MSCC_GetMmssLastLocationInfoAddr(VOS_VOID);

NAS_MSCC_MMSS_CFG_INFO_STRU* NAS_MSCC_GetMmssNvimCfgInfoAddr(VOS_VOID);

NAS_MSCC_MMSS_SYSACQ_CFG_STRU* NAS_MSCC_GetMmssSysAcqCfgInfoAddr(VOS_VOID);

NAS_MSCC_3GPP_SYS_INFO_STRU* NAS_MSCC_Get3gppSysInfoAddr(VOS_VOID);

NAS_MSCC_1X_SYS_INFO_STRU* NAS_MSCC_Get1xSysInfoAddr(VOS_VOID);

NAS_MSCC_HRPD_SYS_INFO_STRU* NAS_MSCC_GetHrpdSysInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_Set1xCampOnFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_Get1xCampOnFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetHrpdCampOnFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_GetHrpdCampOnFlag(VOS_VOID);

VOS_VOID NAS_MSCC_Set3gppCampOnFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_GetLteCampOnFlag(VOS_VOID);

VOS_UINT8 NAS_MSCC_Get3gppCampOnFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurr3gppRoamingFlg(
    VOS_UINT8                               ucRoamingFlg
);
VOS_UINT8 NAS_MSCC_GetCurr3gppRoamingFlg(VOS_VOID);
VOS_VOID NAS_MSCC_UpdateRoamFlag(
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
);

VOS_VOID NAS_MSCC_SetBsrTimerNvimActiveFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_GetBsrTimerNvimActiveFlag(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetMlplMsplValidFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetMlplValidFlag(VOS_UINT8 ucValid);

VOS_VOID NAS_MSCC_SetMsplValidFlag(VOS_UINT8 ucValid);

NAS_MSCC_MLPL_MSPL_INFO_STRU* NAS_MSCC_GetMlplMsplInfoAddr(VOS_VOID);

NAS_MSCC_MLPL_STRU* NAS_MSCC_GetMlplInfoAddr(VOS_VOID);

NAS_MSCC_MSPL_STRU* NAS_MSCC_GetMsplInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
);

VOS_VOID NAS_MSCC_ClearWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
);

VOS_VOID NAS_MSCC_ResetWaitCardReadCnfFlg_SwitchOn(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetWaitCardReadCnfFlag_SwitchOn(VOS_VOID);

NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU* NAS_MSCC_GetEhPlmnInfoAddr(VOS_VOID);

NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU* NAS_MSCC_GetUserPlmnInfoAddr(VOS_VOID);

NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU* NAS_MSCC_GetOperPlmnInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitMlplMsplInfo(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8                       enInitType,
    NAS_MSCC_MLPL_MSPL_INFO_STRU                           *pstMlplMsplInfo
);

VOS_VOID NAS_MSCC_InitSimInfo(
    NAS_MSCC_SIM_INFO_STRU                                 *pstSimInfo
);

VOS_VOID NAS_MSCC_InitCardReadInfor(
    NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU             *pstCardReadInfo
);

NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU* NAS_MSCC_GetCardReadInforAddr(VOS_VOID);

VOS_VOID  NAS_MSCC_InitSimUserPlmnInfo(
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                    *pstUserPlmnInfo
);

VOS_VOID  NAS_MSCC_InitSimOperPlmnInfo(
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                    *pstOperPlmnInfo
);

VOS_UINT32 NAS_MSCC_GetAbortFlag_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SetAbortFlag_SysAcq(
    VOS_UINT8                           ucAbortFlg
);

VOS_UINT8 NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq(VOS_VOID);

VOS_UINT8 NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
);

VOS_VOID NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
);

NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq(VOS_VOID);

NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_L1Main(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetInterSysSearchLteFlag_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SetInterSysSearchLteFlag_SysAcq(
    VOS_UINT8                               ucSearchLteFLag
);

VOS_UINT8 NAS_MSCC_GetInterSysSearchHrpdFlag_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SetInterSysSearchHrpdFlag_SysAcq(
    VOS_UINT8                           ucSearchHrpdFLag
);

VOS_UINT32  NAS_MSCC_GetNextOosAvailableTimerLength_L1Main(VOS_VOID);

VOS_UINT32  NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main(VOS_VOID);

VOS_VOID  NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main(VOS_VOID);

VOS_VOID  NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetScanTimerLength(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetSleepTimerLength(VOS_VOID);

VOS_UINT8  NAS_MSCC_GetHrpdConnExistFlg(VOS_VOID);

VOS_VOID  NAS_MSCC_SetHrpdConnExistFlg(
    VOS_UINT8                           ucFlg
);

VOS_UINT8  NAS_MSCC_GetLteEpsConnExistFlg(VOS_VOID);

VOS_VOID  NAS_MSCC_SetLteEpsConnExistFlg(
    VOS_UINT8                           ucFlg
);

NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_GetLtePriClass(VOS_VOID);
NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xPriClass(VOS_VOID);
NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xAIPriClass(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetAbortFlag_BSR(VOS_VOID);

VOS_VOID NAS_MSCC_SetAbortFlag_BSR(
    VOS_UINT8                           ucAbortFlg
);

NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_GetDestBsrSysPriClass_BSR(VOS_VOID);
VOS_VOID NAS_MSCC_SetDestBsrSysPriClass_BSR(
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass
);
VOS_VOID NAS_MSCC_SetDestBsrSysType_BSR(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
);

VOS_VOID NAS_MSCC_SetOrigSysMsplIndex_BSR(
    VOS_UINT8                           ucOrigSysMsplIndex
);

VOS_UINT8 NAS_MSCC_GetOrigSysMsplIndex_BSR(VOS_VOID);

NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8 NAS_MSCC_GetDestBsrSysType_BSR(VOS_VOID);

NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU *NAS_MSCC_GetHrpdHighPrioSysInfo_BSR(VOS_VOID);

VOS_VOID NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(
    VOS_UINT8                           ucOrigSysUseDefMsplRec
);

VOS_UINT8 NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR(VOS_VOID);

NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU* NAS_MSCC_GetLtePrefPlmnListInfo_BSR(VOS_VOID);

VOS_VOID NAS_MSCC_SaveCardStatus(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimStatus
);

VOS_VOID NAS_MSCC_SaveIsCardChangedFlg(
    VOS_UINT8                           ucIsCardChanged
);

VOS_UINT8 NAS_MSCC_GetIsCardChangedFlg( VOS_VOID );

VOS_VOID  NAS_MSCC_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
);

VOS_VOID  NAS_MSCC_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
);

VOS_UINT8  NAS_MSCC_GetSimCsRegStatus(VOS_VOID);

VOS_UINT8  NAS_MSCC_GetSimPsRegStatus(VOS_VOID);

VOS_VOID NAS_MSCC_SavePrioRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio
);

NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetUsimCardStatus(VOS_VOID);

NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetCsimCardStatus(VOS_VOID);

NAS_MSCC_PIF_RAT_PRIO_STRU* NAS_MSCC_GetRatPrioList(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsSpecRatSupported(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat
);

VOS_UINT32 NAS_MSCC_IsUserSysCfgRatCapSupport3Gpp(VOS_VOID);

NAS_MSCC_SYS_MODE_ENUM_UINT8 NAS_MSCC_Get3gppCurSysMode(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurr3gppPsServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr3gppPsServiceStatus(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetLastSendToImsaRoamFlg(VOS_VOID);
VOS_VOID NAS_MSCC_SetLastSendToImsaRoamFlg(
    VOS_UINT8  ucRoamStatus
);

VOS_VOID NAS_MSCC_SetCurr1xServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr1xServiceStatus(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurrHrpdServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurrHrpdServiceStatus(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetHrpdActiveFlg(VOS_VOID);

VOS_VOID NAS_MSCC_SetHrpdActiveFlg(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_Get3gppActiveFlg(VOS_VOID);

VOS_VOID NAS_MSCC_Set3gppActiveFlg(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_Get1xActiveFlg(VOS_VOID);

VOS_VOID NAS_MSCC_Set1xActiveFlg(
    VOS_UINT8                           ucFlag
);

VOS_VOID  NAS_MSCC_SetPowerSaveReplyFlg(
    VOS_UINT8                           ucFlg
);

VOS_UINT8  NAS_MSCC_GetPowerSaveReplyFlg(VOS_VOID);


VOS_VOID NAS_MSCC_InitMsCfgInfo(
    NAS_MSCC_MS_CFG_INFO_STRU          *pstMsCfgInfo
);

VOS_VOID NAS_MSCC_InitCustomCfgInfo(
    NAS_MSCC_CUSTOM_CONFIG_STRU        *pstCustomCfgInfo
);

VOS_VOID NAS_MSCC_InitMsSysCfgInfo(
    NAS_MSCC_MS_SYS_CFG_INFO_STRU      *pstMsSysCfgInfo
);

VOS_VOID NAS_MSCC_InitPlatformRatCapInfo(
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap
);

VOS_VOID NAS_MSCC_InitImsCfgInfo(
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo
);

VOS_VOID NAS_MSCC_InitMmssCfgInfo(
    NAS_MSCC_MMSS_CFG_INFO_STRU        *pstMmssCfgInfo
);

VOS_VOID NAS_MSCC_InitMmssLastLocationInfo(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmssLastLocationInfo
);

VOS_VOID NAS_MSCC_InitSysAcqTimerCfgInfo(
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg
);

VOS_VOID NAS_MSCC_InitPowerSaveCtrlInfo(
    NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU  *pstPowerSaveCtrlInfo
);

VOS_VOID NAS_MSCC_InitSysAcqCtrlInfo(
    NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU     *pstSysAcqCtrlInfo
);

NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU* NAS_MSCC_GetSysAcqCtrlInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurrBsrTimerLen(
    VOS_UINT32                          ulBsrTimerLen
);

VOS_UINT32 NAS_MSCC_GetCurrBsrTimerLen(VOS_VOID);

VOS_VOID NAS_MSCC_SetEmcCallExistFlag(
    VOS_UINT8                           ucIsEmcCallExistFlg
);

VOS_UINT8 NAS_MSCC_GetEmcCallExistFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetEmcCallBackEnableFlag(
    VOS_UINT32                          ulCallBackEnableFlg
);

VOS_UINT32 NAS_MSCC_GetEmcCallBackEnableFlag(VOS_VOID);


VOS_VOID NAS_MSCC_SetOrigBsrTimerStartRat(VOS_VOID);

VOS_RATMODE_ENUM_UINT32 NAS_MSCC_GetOrigBsrTimerStartRat(VOS_VOID);





NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg(VOS_VOID);

NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg(VOS_VOID);

VOS_VOID NAS_MSCC_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
);
VOS_VOID NAS_MSCC_UpdateMsgExitTime( VOS_VOID );
VOS_VOID NAS_MSCC_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
);

VOS_VOID NAS_MSCC_InitMntnInfo(
    NAS_MSCC_MNTN_CTX_STRU            *pstMntnInfo
);



VOS_VOID  NAS_MSCC_Set1xSysAcqMoCallFlag(
    VOS_UINT8                           ucFlg
);

VOS_UINT8  NAS_MSCC_Get1xSysAcqMoCallFlag(VOS_VOID);

VOS_UINT8  NAS_MSCC_GetAllowSrchLteFlg(VOS_VOID);

VOS_VOID NAS_MSCC_SetAllowSrchLteFlg(
    VOS_UINT8                           ucAllowSrchLteFlg
);
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
VOS_UINT8 NAS_MSCC_IsCLCombinedModeWithRatPrio
(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstUserRatPrio
);
#endif

VOS_UINT32 NAS_MSCC_IsCLModeSupportedInRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
);


VOS_VOID NAS_MSCC_InitNoCardInitSearchLocInfo(
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo
);

NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU *NAS_MSCC_GetNoCardInitSearchLocInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_Update1xNoCardInitSearchLocInfo(
    VOS_INT32                           lSid,
    VOS_INT32                           lNid
);

VOS_VOID NAS_MSCC_Update1xNoCardInitSearchLocMcc(
    VOS_UINT32                          ulMcc
);

VOS_VOID NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
);

VOS_VOID NAS_MSCC_SetNoCardInitSearchWaitType(
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType
);

NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32 NAS_MSCC_GetNoCardInitSearchWaitType(VOS_VOID);

VOS_VOID NAS_MSCC_ResetNoCardInitSearchInfo(VOS_VOID);

VOS_VOID NAS_MSCC_Init1xServiceClSysAcqStrategyInfo(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU    *pstSysAcqStrategy
);

NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU* NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr(VOS_VOID);

NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU* NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr(VOS_VOID);

NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8 NAS_MSCC_GetCur1xServiceSysAcqPhaseNum(VOS_VOID);

VOS_VOID NAS_MSCC_SetCur1xServiceSysAcqPhaseNum(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enPhase
);

VOS_UINT8 NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID);

VOS_VOID NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID);

VOS_VOID NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID);

VOS_VOID NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID);

VOS_VOID NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID);

VOS_UINT32  NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enPhaseNum
);

VOS_UINT32  NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main(VOS_VOID);

VOS_UINT32  NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main(VOS_VOID);

VOS_UINT32  NAS_MSCC_GetNextAvailableTimerLength_L1Main(VOS_VOID);

VOS_VOID  NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main(VOS_VOID);

VOS_VOID NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum(VOS_VOID);

VOS_VOID NAS_MSCC_AddCur1xServiceSysAcqPhaseNum(VOS_VOID);

VOS_VOID  NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main(VOS_VOID);


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

#endif /* end of NasMsccCtx.h */
