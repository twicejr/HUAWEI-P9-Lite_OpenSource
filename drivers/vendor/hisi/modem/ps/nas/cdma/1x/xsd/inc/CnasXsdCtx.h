/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdCtx.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月4日
  最近修改   :
  功能描述   : CnasXsdCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月4日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_CTX_H__
#define __CNAS_XSD_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "CnasPrlApi.h"
#include "xsd_mscc_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XSD_MAX_FSM_STACK_DEPTH                        (4)                 /* 状态机栈的深度 */

#define CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM                    (8)                 /* 最大缓存消息的个数 */

#define CNAS_XSD_MAX_MSG_BUFFER_LEN                         (1600)              /* 消息的最大长度，包括状态机保存的入口消息和CACHE消息 */

/* 存储的最大的MRU个数，CGD 130 5.2.2 The number of entries in an MRU list is implementation dependent but a typical number may be 12 */
#define CNAS_XSD_MAX_MRU_SYS_NUM                            (12)

#define CNAS_XSD_MAX_AVOID_FREQ_NUM                         (100)

#define CNAS_XSD_MAX_REDIR_CHANNEL_NUM                      (16)

#define CNAS_XSD_MAX_PREFERRED_SYSTEM_NUM                   (50)

#define CNAS_XSD_BAND0_BAND10_PREFERRED_SYSTEM_NUM          (21)

#define CNAS_XSD_MAX_AVAILABLE_SYS_NUM                      (50)

#define CNAS_XSD_MAX_REDIAL_SYSTEM_NUM                      (600)

#define CNAS_XSD_MAX_NEG_SYS_NUM                            (50)

/* 与CNAS_CAS_1X_MAX_SAME_PRIO_SYS_NUM相同 */
#define CNAS_XSD_1X_MAX_SAME_PRIO_SYS_NUM                   (8)

/* 与CNAS_CAS_1X_MAX_SYSTEM_NUM相同 */
#define CNAS_XSD_1X_SND_CAS_MAX_SYSTEM_NUM                  (16)

#define CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM                  (128)

#define CNAS_XSD_MAX_INT_MSG_QUEUE_NUM                      (8)

#define CNAS_XSD_MAX_SLICE_VALUE                            (0xFFFFFFFF)

#define CNAS_XSD_WILDCARD_CDMAPN_VALUE                      (0xFFFF)

/* XSD内部系统捕获请求中带的频点最大个数 */
#define CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM       (40)

#define CNAS_XSD_MAX_OOC_SCHEDULE_PHASE_NUM                 (8)

#define CNAS_XSD_ATTEMP_IN_DO_TRAFFIC_4_TIMES               (4)
#define CNAS_XSD_ATTEMP_UNLIMITED_TIMES                     (65535)

#define CNAS_XSD_EF_HOME_SID_NID_REC_LEN                    (5)
#define CNAS_XSD_EF_HOME_SID_OCTET_LEN                      (2)
#define CNAS_XSD_EF_HOME_NID_OCTET_LEN                      (2)
#define CNAS_XSD_EF_HOME_BAND_OCTET_LEN                     (1)

#define CNAS_XSD_BIT_LEN_8_BIT                              (8)
#define CNAS_XSD_BIT_LEN_16_BIT                             (16)
#define CNAS_XSD_HOME_SID_NID_LEN                           (5)
#define CNAS_XSD_HOME_SID_NID_1_OFFSET                      (1)
#define CNAS_XSD_HOME_SID_NID_2_OFFSET                      (2)
#define CNAS_XSD_HOME_SID_NID_3_OFFSET                      (3)
#define CNAS_XSD_HOME_SID_NID_4_OFFSET                      (4)

#define CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM                 (2)

#define CNAS_XSD_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM       (10)

#define CNAS_XSD_AVOID_MAX_PHASE_NUM                        (8)
#define CNAS_XSD_MAX_CANDIDATE_FREQ_NUM                     (3)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_XSD_FSM_ID_ENUM
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_FSM_ID_ENUM
{
    /***********************************************************************
     * XSD L1状态机标识
     ***********************************************************************/
    /* CNAS XSD L1 main状态机的标识 */
    CNAS_XSD_FSM_L1_MAIN                                    =0x00,

    /***********************************************************************
     * XSD L2状态机的标识
     ***********************************************************************/
    /* 协议栈初始化L2状态机 */
    CNAS_XSD_FSM_SWITCH_ON                                  =0x01,

    /* 协议栈关机L2状态机 */
    CNAS_XSD_FSM_POWER_OFF                                  =0x02,

    /* 协议栈SYSTEM ACQUIRE L2状态机 */
    CNAS_XSD_FSM_SYS_ACQ                                    =0x03,

    CNAS_XSD_FSM_REDIRECTION                                =0X04,
    CNAS_XSD_BUTT

};
typedef VOS_UINT32 CNAS_XSD_FSM_ID_ENUM_UINT32;


/** ****************************************************************************
 * Name        : CNAS_XSD_ACQUIRED_CAUSE_ENUM
 * Description :
 *******************************************************************************/
enum CNAS_XSD_ACQUIRED_CAUSE_ENUM
{
    CNAS_XSD_ACQ_FAIL_CAUSE_ACQUISITION_FAIL                = 0x00,
    CNAS_XSD_ACQ_FAIL_CAUSE_PROTO_MISMATCH                  = 0x01,
    CNAS_XSD_ACQ_FAIL_CAUSE_PAGE_CH_FAIL                    = 0x02,
    CNAS_XSD_ACQ_FAIL_CAUSE_FREQ_SRCH_FAIL                  = 0x03,
    CNAS_XSD_ACQ_FAIL_CAUSE_BUTT                            = 0x04
};
typedef VOS_UINT8 CNAS_XSD_ACQUIRED_CAUSE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_INIT_CTX_TYPE_ENUM
 结构说明  : 初始化XSD CTX类型
 1.日    期   : 2014年7月11日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_INIT_CTX_TYPE_ENUM
{
    CNAS_XSD_INIT_CTX_STARTUP                    = 0,
    CNAS_XSD_INIT_CTX_POWEROFF                   = 1,
    CNAS_XSD_INIT_CTX_BUTT
};
typedef VOS_UINT8 CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_READ_CARD_FILES_CNF_ENUM
 结构说明  : 用于标记读取卡文件的回复消息
 1.日    期   : 2014年7月11日
   作    者   : h00246512
   修改内容   : 新增

*****************************************************************************/
enum   CNAS_XSD_READ_CARD_FILES_CNF_ENUM
{
    CNAS_XSD_READ_CARD_FILE_FLG_NULL                        = 0x00,

    CNAS_XSD_READ_CARD_FILE_PRL_FLG                         = 0x01,

    CNAS_XSD_READ_CARD_FILE_EPRL_FLG                        = 0x02,

    CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG                = 0x04,

    CNAS_XSD_READ_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XSD_SYS_ACQ_SCENE_ENUM
 枚举说明  : 各种系统捕获场景的定义
 1.日    期   : 2014年8月5日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2014年12月29日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 6 Modified
 3.日    期   : 2015年1月3日
   作    者   : y00245242
   修改内容   : 增加OOC系统捕获调度机制

*****************************************************************************/
enum CNAS_XSD_SYS_ACQ_SCENE_ENUM
{
    CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON,                       /* 开机 */
    CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST,                     /* 出服务区 */
    CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED,                   /* 呼叫释放触发搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED,         /* Available Timer超时触发搜网 */

    CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL,              /* 正常呼叫重拨触发搜网*/
    CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL,                  /* 紧急呼触发搜网*/

    CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR,        /* call released while redirction flag is true */
    CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_FAIL,                /* redirection fail we must trigger system acquire */
    CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM,  /* redirection with invalid GSRDM */
    CNAS_XSD_SYS_ACQ_SCENE_RESCAN,                          /* SD ind with rescan reason */
    CNAS_XSD_SYS_ACQ_SCENE_PROTO_MISMATCH,                  /* SD ind with proto mismatch reason with redirection flag is false */
    CNAS_XSD_SYS_ACQ_SCENE_ACCESS_DENINED,                  /* SD ind with access denied reason */
    CNAS_XSD_SYS_ACQ_SCENE_ACCT_BLOCKED,                    /* SD ind with acct blocked reason */
    CNAS_XSD_SYS_ACQ_SCENE_NDSS_OFF,                        /* SD ind with ndss off reason */
    CNAS_XSD_SYS_ACQ_SCENE_ERR,                             /* SD ind with error ind reason */
    CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF,    /* SD ind with register reject reason with redirection flag is ture and return_if_fail is true */
    CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ,                       /* SD ind with regis rej reason */
    CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF,       /* SD ind with system resel reason while the current system is in PRL and is prefered system */
    CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG,     /* SD ind with system resel reason while the current system is not in PRL or negative in PRL */
    CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL,       /* SD ind with max access failure reason while the current system is in PRL */
    CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL,   /* SD ind with max access failure reason while the current system is not in PRL */
    CNAS_XSD_SYS_ACQ_SCENE_ABNORMAL,                        /* SD ind with abnormal ind reason */
    CNAS_XSD_SYS_ACQ_SCENE_CFREQ_LOCK,                      /* 锁频场景触发搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0,                       /* MRU0搜索 */

    CNAS_XSD_SYS_ACQ_SCENE_NO_RF,                           /* 无射频资源可用 */

    CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,        /* CallBack模式中15s搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED,               /* 紧急呼释放场景 */

    CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0,            /* 同system lost，只是搜网时不搜MRU0  */
    CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC,    /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC,       /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC,     /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC,           /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC,  /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC,       /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC,   /* 紧急呼场景的CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL搜网 */
    CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASE_SYSTEM_LOST,

    CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH,

    CNAS_XSD_SYS_ACQ_SCENE_BUTT
};
typedef VOS_UINT32 CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XSD_SCAN_CHAN_STATUS_ENUM
 枚举说明  : 频点的扫描状态取值定义
 1.日    期   : 2014年8月5日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_SCAN_CHAN_STATUS_ENUM
{
    CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED,                        /* 未搜索，当前环境中是否存在该频点还不确定 */
    CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,                     /* 已搜索，当前环境中存在对应频点 */
    CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,                  /* 已搜索，当前环境中不存在对应频点，但还未尝试捕获 */

    CNAS_XSD_SCAN_CHAN_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_AVAIL_SYS_STATUS_ENUM
 枚举说明  : available system 状态取值定义
 1.日    期   : 2014年8月14日
   作    者   : l60609
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_AVAIL_SYS_STATUS_ENUM
{
    CNAS_XSD_AVAIL_SYS_STATUS_NO_ACQUIRED,                  /* 未捕获*/
    CNAS_XSD_AVAIL_SYS_STATUS_ACQUIRED_SUCC,                /* 已捕获成功 */
    CNAS_XSD_AVAIL_SYS_STATUS_ACQUIRED_FAIL,                /* 已捕获失败 */
    CNAS_XSD_AVAIL_SYS_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_XSD_AVAIL_SYS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_SYS_TYPE_ENUM
 枚举说明  : 系统类型定义
 1.日    期   : 2014年8月21日
   作    者   : l60609
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_SYS_TYPE_ENUM
{
    CNAS_XSD_SYS_TYPE_PREFERRED,
    CNAS_XSD_SYS_TYPE_AVAILABLE,
    CNAS_XSD_SYS_TYPE_NEGATIVE,
    CNAS_XSD_SYS_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XSD_SYS_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_XSD_ACQ_SYS_REGION_IND_ENUM
 枚举说明  : 捕获系统列表中的记录相对下一条是否为新的系统表记录
 1.日    期   : 2014年8月21日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_ACQ_SYS_REGION_IND_ENUM
{
    CNAS_XSD_ACQ_SYS_REGION_IND_NEW = 0,  /* 捕获系统列表中的第一条系统记录,设置为0,后续如果相对下条记录时新的系统表记录也设置为0 */
    CNAS_XSD_ACQ_SYS_REGION_IND_SAME,

    CNAS_XSD_ACQ_SYS_REGION_IND_BUTT
};
typedef VOS_UINT8 CNAS_XSD_ACQ_SYS_REGION_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_CALL_EXIST_FLAG_ENUM
 结构说明  : 呼叫存在标记枚举
 1.日    期   : 2014年12月2日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_CALL_EXIST_FLAG_ENUM
{
    CNAS_XSD_CALL_EXIST_NULL_FLAG                    = 0x00,
    CNAS_XSD_NORMAL_VOICE_CALL_EXIST_FLAG            = 0x01,
    CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG               = 0x02,
    CNAS_XSD_NORMAL_DATA_CALL_EXIST_FLAG             = 0x04,
};
typedef VOS_UINT8 CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM
 结构说明  : system acquire mode
 1.日    期   : 5/1/2014
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
enum CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM
{
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY                    = 0,   /* try to acquire any system without regard to
                                                                  PRL designation(event if the negative system in PRL or
                                                                  a available system when pref_only is true) */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ALLOWED                = 1,   /* try to acquire any system that is allowed by PRL
                                                                  (should ignore negative system and avaiable system when
                                                                  pref_only is true)*/

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC               = 2,   /* try to acquire only a system for which the
                                                                  SID/NID is known(for example frequency lock) without regard to
                                                                  PRL designation(event if the negative system in PRL or
                                                                  a available system when pref_only is true) */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC_PREFEREED     = 3,   /* try to acquire only a system for which the
                                                                  SID/NID is known and the system must be allowed by the PRL
                                                                  (should ignore negative system) */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED               = 4,   /* try to acquire only a prefered PRL system */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF              = 5,   /* try to acquire only a system which is the most prefered in the PRL */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_MORE_PREF              = 6,   /* try to acquire only a system that is more
                                                                   prefered than the idle system */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF          = 7,   /* try to acquire only a system that is not less
                                                                   prefered than the idle system(for example silent redial) */

    CNAS_XSD_SYSTEM_ACQUIRE_MODE_BUTT
};
typedef VOS_UINT8 CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_XSD_OOC_SCAN_STRATEGY_ENUM
 结构说明  : 频点重复搜索策略枚举
 1.日    期   : 2015年1月4日
   作    者   : c00299063
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_OOC_SCAN_STRATEGY_ENUM
{
    CNAS_XSD_OOC_SCAN_NORMAL,                           /* OOC后，scan list列表按正常方式构建 */
    CNAS_XSD_OOC_SCAN_REACQ_0_1_2_3_4S,                 /* OOC后，scan list列表构建按每0，1，2，3，4个其他频点后插入一个MRU0频点，以次类推 */
    CNAS_XSD_OOC_SCAN_PING_5,                           /* OOC后，scan list列表构建按每5个其他频点后插入1个MRU0频点，以次类推 */
    CNAS_XSD_OOC_SCAN_2_7,                              /* OOC后，scan list列表构建按每5个其他频点后插入2个MRU0频点，以次类推 */

    CNAS_XSD_OOC_SCAN_BUTT
};
typedef VOS_UINT8 CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_NEG_PREF_SYS_CMP_CTRL_ENUM
 结构说明  : neg系统和 perf系统比较控制
 1.日    期   : 2015年6月9日
   作    者   : c00299063
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_NEG_PREF_SYS_CMP_CTRL_ENUM
{
    CNAS_XSD_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH,                /* Band Channel 模糊匹配 */
    CNAS_XSD_NEG_PREF_SYS_CMP_BAND_CHAN_ACCURATE_MATCH,                 /* Band Channel 精确匹配*/
    CNAS_XSD_NEG_PREF_SYS_CMP_BUTT
};
typedef VOS_UINT8 CNAS_XSD_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_EMC_STATE_ENUM
 结构说明  : XSD紧急呼流程标识
 1.日    期   : 2015年7月2日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XSD_EMC_STATE_ENUM
{
    CNAS_XSD_EMC_STATE_NULL             = 0x00,             /* 清空紧急呼所有状态 */
    CNAS_XSD_EMC_STATE_CALLBACK         = 0x01,             /* 紧急呼CALLBACK模式状态 */

    CNAS_XSD_EMC_STATE_BUTT
};
typedef VOS_UINT8 CNAS_XSD_EMC_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_SERVICE_STATUS_ENUM_UINT32
 结构说明  : 服务状态
 1.日    期: 2015年7月10日
   作    者: y00245242
   修改内容: 新增
*****************************************************************************/
enum CNAS_XSD_SERVICE_STATUS_ENUM
{
    CNAS_XSD_SERVICE_STATUS_NO_SERVICE                      = 0,        /* 无服务   */
    CNAS_XSD_SERVICE_STATUS_LIMITED_SERVICE                 = 1,        /* 限制服务 */
    CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE                  = 2,        /* 正常服务 */
    CNAS_XSD_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 CNAS_XSD_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XSD_AVOID_REASON_ENUM
 枚举说明  : avoid频点原因
 1.日    期   : 2014年10月17日
   作    者   : y00245242
   修改内容   : 新增
 2.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 6 Modified
*****************************************************************************/
enum CNAS_XSD_AVOID_REASON_ENUM
{
    CNAS_XSD_AVOID_P_REV_MISMATCH,                  /* P_REV mismatch */
    CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL,           /* System's SID/NID is rejected by PRL */
    CNAS_XSD_AVOID_SYNC_CH_ACQUIRED_PAGE_CH_FAIL,   /* Sync channel is acquired but not the paging channel */
    CNAS_XSD_AVOID_BAD_OVERHEAD_MESSAGES,           /* Bad overhead messages */
    CNAS_XSD_AVOID_REG_REJECTED,                    /* Registeration is rejected */
    CNAS_XSD_AVOID_MAX_ACCESS_PROBES,               /* Max access probes */
    CNAS_XSD_AVOID_ACCT_BLOCKED_IND,                /* ACCT blocked indication */
    CNAS_XSD_AVOID_ERROR_IND,                       /* ERROR indication */
    CNAS_XSD_AVOID_REDIRECTION_FAIL,                                    /* redirection fail with return_if_fail is false */
    CNAS_XSD_AVOID_REDIRECTION_WITH_INVALID_GSRDM,                      /* redirection with invalid GSRDM and return_if_fail is false */
    CNAS_XSD_AVOID_ACCESS_DENIED,                                       /* access denied */
    CNAS_XSD_AVOID_SYSTEM_RESELECTION,                                  /* system reselection */
    CNAS_XSD_AVOID_REASON_MAX,

    CNAS_XSD_AVOID_REASON_BUTT
};
typedef VOS_UINT8 CNAS_XSD_AVOID_REASON_ENUM_UINT8;

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
 结构名    : CNAS_XSD_MSG_STRU
 结构说明  : XSD消息结构，状态机保存的入口消息和CACHE消息都使用此结构
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[CNAS_XSD_MAX_MSG_BUFFER_LEN];
}CNAS_XSD_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_CACH_MSG_INFO_STRU
 结构说明  : 缓存的消息内容
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_XSD_MSG_STRU                   stCacheMsg;         /* 缓存的具体内容 */
}CNAS_XSD_CACHE_MSG_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_CACHE_MSG_INFO_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2015年09月07日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastCacheMsg[CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM]; /* XSD的缓存消息指针数组 */
}CNAS_XSD_CACHE_MSG_QUEUE_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_MRU_LIST_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_PRL_1X_SYSTEM_STRU             astSystem[CNAS_XSD_MAX_MRU_SYS_NUM];
}CNAS_XSD_MRU_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_TEST_CONFIG_STRU
 结构说明  : CNAS XSD 测试控制
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReadNvPrlDirectly;
    VOS_UINT8                           ucReadDefaultPrl;        /* 读取Default Prl */
    VOS_UINT8                           ucNoCardModeCfgFlg;
    VOS_UINT8                           ucIsMod1xAvailTimerLen;
}CNAS_XSD_TEST_CONFIG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_CALLBACK_CFG_STRU
 结构说明  : 紧急呼CALLBACK模式设置
 1.日    期   : 2015年7月2日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;        /* 是否支持CallBack模式 */
    VOS_UINT32                          ulCallBackModeTimerLen;     /* CallBack定时器时长 */
} CNAS_XSD_CALLBACK_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_FREQENCY_CHANNEL_STRU
 结构说明  : 频点结构
  1.日    期   : 2015年7月3日
    作    者   : h00313353
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    CNAS_PRL_BAND_CLASS_ENUM_UINT16     enBandClass;
} CNAS_XSD_FREQUENCY_CHANNEL_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_CDMA_1X_PREF_CHANNELS_STRU
 结构说明  : 中国电信1X优选频点结构
  1.日    期   : 2015年7月3日
    作    者   : h00313353
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_XSD_FREQUENCY_CHANNEL_STRU     astFreqList[CNAS_XSD_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM];
} CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_ADD_AVOID_FREQ_CFG_STRU
 结构说明  : CNAS XSD 添加avoid频点控制
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsNegSysAdd;
    VOS_UINT8                           aucReserve[15];
}CNAS_XSD_ADD_AVOID_LIST_CFG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_NEG_PREF_SYS_CMP_CTRL_STRU
 结构说明  : CNAS XSD negitave syetem 判断控制
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_XSD_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8               enNegPrefSysCmpType;
    VOS_UINT8                                               aucReserve[15];
}CNAS_XSD_NEG_PREF_SYS_CMP_CTRL_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU
 结构说明  : CNAS XSD 系统捕获NV控制
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_XSD_ADD_AVOID_LIST_CFG_STRU                        stAddAvoidListCfg;
    CNAS_XSD_NEG_PREF_SYS_CMP_CTRL_STRU                     stNegPrefSysCmpCtrl;
}CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU
 结构说明  : CNAS XSD 锁频信息
 1.日    期   : 2014年12月29日
   作    者   : y00307564
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                                   ucFreqLockMode;
    VOS_UINT8                                                   aucReserve[1];
    VOS_UINT16                                                  usCdmaBandClass;
    VOS_UINT16                                                  usSid;
    VOS_UINT16                                                  usNid;
    VOS_UINT16                                                  usCdmaFreq;
    VOS_UINT16                                                  usCdmaPn;
}CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU;


typedef struct
{
    VOS_UINT32                          BandCDMA_0            :1;/* 800 MHz cellular band */

    VOS_UINT32                          BandCDMA_1            :1;/* 1.8 to 2.0 GHz PCS band */

    VOS_UINT32                          BandCDMA_2            :1;/* 872 to 960 MHz TACS band */

    VOS_UINT32                          BandCDMA_3            :1;/* 832 to 925 MHz JTACS band */

    VOS_UINT32                          BandCDMA_4            :1;/* 1.75 to 1.87 GHz Korean PCS band */

    VOS_UINT32                          BandCDMA_5            :1;/* 450 MHz NMT band */

    VOS_UINT32                          BandCDMA_6            :1;/* 2 GHz IMT-2000 band */

    VOS_UINT32                          BandCDMA_7            :1;/* 700 MHz band */

    VOS_UINT32                          BandCDMA_8            :1;/* 1800 MHz band */

    VOS_UINT32                          BandCDMA_9            :1;/* 900 MHz band */

    VOS_UINT32                          BandCDMA_10           :1;/* Secondary 800 MHz band */

    VOS_UINT32                          BandCDMA_11           :1;/* 400 MHz European PAMR band */

    VOS_UINT32                          BandCDMA_12           :1;/* 800 MHz PAMR band */

    VOS_UINT32                          BandCDMA_13           :1;/* 2.5 GHz IMT-2000 Extension Band */

    VOS_UINT32                          BandCDMA_14           :1;/* US PCS 1.9GHz Band */

    VOS_UINT32                          BandCDMA_15           :1;/* AWS Band */

    VOS_UINT32                          BandCDMA_16           :1;/* US 2.5GHz Band */

    VOS_UINT32                          BandCDMA_17           :1;/* US 2.5GHz Forward Link Only Band */

    VOS_UINT32                          BandCDMA_18           :1;/* 700 MHz Public Safety Band */

    VOS_UINT32                          BandCDMA_19           :1;/* Lower 700 MHz Band */

    VOS_UINT32                          BandCDMA_20           :1;/* L-Band */

    VOS_UINT32                          BandCDMA_21           :1;/* S-Band */

    VOS_UINT32                          BandCDMA_22           :1;

    VOS_UINT32                          BandCDMA_23           :1;

    VOS_UINT32                          BandCDMA_24           :1;

    VOS_UINT32                          BandCDMA_25           :1;

    VOS_UINT32                          BandCDMA_26           :1;

    VOS_UINT32                          BandCDMA_27           :1;

    VOS_UINT32                          BandCDMA_28           :1;

    VOS_UINT32                          BandCDMA_29           :1;

    VOS_UINT32                          BandCDMA_30           :1;

    VOS_UINT32                          BandCDMA_31           :1;/* Wildcard Band Class */
}CNAS_XSD_1X_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulBand;

    CNAS_XSD_1X_BAND_STRU               stBitBand;
}CNAS_XSD_1X_BAND_UN;

/** ****************************************************************************
 * Name        : CNAS_XSD_ACQUIRED_SYS_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    CNAS_PRL_1X_SYSTEM_STRU             stSystem;
    CNAS_XSD_ACQUIRED_CAUSE_ENUM_UINT8  enCause;
    VOS_UINT8                           ucAcqCounter;
    VOS_UINT8                           aucReserve[2];
}CNAS_XSD_ACQUIRED_SYS_STRU;


/** ****************************************************************************
 * Name        : CNAS_XSD_AVOID_SYSTEM_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAvoidFlag;                 /* 使用标志 */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulStartSlice;               /* 起始slice */
    VOS_UINT32                          ulExpiredSliceNum;          /* 到期的slice个数 */
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stAvoidFreq;
    VOS_UINT8                           aucAvoidTimes[CNAS_XSD_AVOID_REASON_MAX];  /* CNAS_XSD_AVOID_REASON_MAX = 12*/
}CNAS_XSD_AVOID_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_SCAN_CHANNEL_INFO_STRU
 结构说明  : 保存扫描的频点信息
 1.日    期   : 2014年8月05日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU          stFreqChan;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8    enChanStatus;                       /* 频点的搜索状态 */
    VOS_UINT8                               aucRsv[3];
}CNAS_XSD_SCAN_CHANNEL_INFO_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_REDIRECTION_INFO_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRedirection;
    VOS_UINT8                           ucReturnIfFail;
    VOS_UINT16                          usExpectSid;
    VOS_UINT16                          usExpectNid;

    VOS_UINT8                           ucNdssInd;
    VOS_UINT8                           ucChanNum;       /**<  record the number of frequency channels in astFreqChanList */
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     astChanInfo[CNAS_XSD_MAX_REDIR_CHANNEL_NUM];
    CNAS_PRL_1X_SYSTEM_STRU             stOriginalSystem;
    VOS_UINT16                          usCurScanIndex;
    VOS_UINT8                           ucIsEmcRedir;    /* 重定向过程中紧急呼标识 */
    VOS_UINT8                           ucReserved;
}CNAS_XSD_REDIRECTION_INFO_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_AVAIL_SYSTEM_INFO_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;
}CNAS_XSD_AVAIL_SYSTEM_INFO_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_AVAILABLE_LIST_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucAvailSysNum;
    VOS_UINT8                                               ucNextSrchIndex;    /* 下次的搜索索引，初始为0 */
    VOS_UINT8                                               aucRsved[2];
    CNAS_XSD_AVAIL_SYSTEM_INFO_STRU                         astAvailSystem[CNAS_XSD_MAX_AVAILABLE_SYS_NUM];
}CNAS_XSD_AVAILABLE_LIST_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_BSR_INFO_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsPrlAcqTable;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT16                          usIndex;            /**<  record last acquired preferred system index */
    CNAS_PRL_1X_SYSTEM_STRU             astPreferredSystem[CNAS_XSD_MAX_PREFERRED_SYSTEM_NUM];
}CNAS_XSD_BSR_INFO_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_AVOID_FREQ_LIST_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAvoidFreqNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_XSD_AVOID_FREQ_INFO_STRU       astAvoidFreqInfo[CNAS_XSD_MAX_AVOID_FREQ_NUM];
}CNAS_XSD_AVOID_FREQ_LIST_STRU;

/** ****************************************************************************
 * Name        : CNAS_XSD_CALL_REDIAL_SYS_LIST_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSysNum;
    VOS_UINT16                          usIndex;         /**<  record last acquired preferred system index */
    CNAS_PRL_1X_SYSTEM_STRU             astRedialSystem[CNAS_XSD_MAX_REDIAL_SYSTEM_NUM];
}CNAS_XSD_CALL_REDIAL_SYS_LIST_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU
 结构说明  : 保存需要捕获的系统记录信息
 1.日    期   : 2014年8月05日
   作    者   : W00176964
   修改内容   : 新增

 2.日    期   : 2015年7月3日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
typedef struct
{
    CNAS_PRL_1X_SYSTEM_STRU                                 stAcqSys;                           /* 需要捕获的系统ID */
    VOS_UINT16                                              usLevel;                            /* 系统在GEO中Level, level0为最高优先级 */
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enPrefNegSys;                       /* 在频点扫描列表中的索引,方便对应的频点状态刷新 */
}CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_SCAN_CHANNEL_LIST_STRU
 结构说明  : 频点扫描列表结构体
 1.日    期   : 2014年8月05日
   作    者   : W00176964
   修改内容   : 新增
 2.日    期   : 2015年1月09日
   作    者   : W00176964
   修改内容   : CDMA 1X Iteration 6 Modidifed:Add Max List Size Item
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalNum;                             /* 列表中保存的chan个数 */
    VOS_UINT16                          usCurScanIndex;                         /* 当前需要扫描的频点索引,默认为0,同步完成一组记录后指向下个索引
                                                                                   ,由于系统捕获流程也会刷新频点扫描状态,因此当前的扫描索引不精确到
                                                                                    具体同步到的频点,只表示大致位置,提高列表访问效率 */

    VOS_UINT16                          usMaxScanChanSize;                      /* 最大扫描频点个数 */
    VOS_UINT8                           aucReserve[2];
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU    *pstScanChanInfo;                        /* 需要扫描的频点列表首地址:根据总个数分配内存 */

}CNAS_XSD_SCAN_CHANNEL_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU
 结构说明  : 紧急呼重拨搜网控制
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRedialCount;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT8                                               aucRedialTimes[CNAS_XSD_MAX_MRU_SYS_NUM];  /* 紧急呼叫失败时当前驻留的频点在mru的重拨次数，超过次数起搜网*/
    CNAS_PRL_1X_SYSTEM_STRU                                 stLastCampedSys;
    CNAS_XSD_MRU_LIST_STRU                                  stEmcRedialMruList;
}CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU
 结构说明  : 紧急呼回呼模式异频临区信息
  1.日    期   : 2016年01月28日
    作    者   : h00313353
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCfChannelNum;
    VOS_UINT8                           aucReserved[2];
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astChannelList[CNAS_XSD_MAX_CANDIDATE_FREQ_NUM];    /* 异频临区频点信息 */
}CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_CUR_SYNC_GEO_LIST_INFO
 结构说明  : 记录当前正在同步的GEO list首个索引
 1.日    期   : 2015年7月8日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usGeoNum;
    VOS_UINT16                                              usReserved;
    VOS_UINT16                                              ausGeoFirstIndex[CNAS_PRL_MAX_MATCHING_GEO_NUM];
}CNAS_XSD_CUR_SYNC_GEO_LIST_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU
 结构说明  : 系统捕获列表信息-用于系统捕获时使用
 1.日    期   : 2014年8月05日
   作    者   : W00176964
   修改内容   : 新增

 2.日    期   : 2015年1月09日
   作    者   : W00176964
   修改内容   : CDMA 1X Iteration 6 Modidifed:Add Max List Size Item

 3.日    期   : 2015年7月3日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usTotalNum;                             /* 列表中保存的sys总个数 */
    VOS_UINT16                                              usMaxAcqSysSize;                        /* 最大捕获系统个数 */
    VOS_UINT16                                              usCurSrchLevel;                         /* 当前搜索索引 */
    VOS_UINT16                                              usReserved;
    CNAS_XSD_CUR_SYNC_GEO_LIST_INFO_STRU                    stCurSyncGeoInfo;                       /* 当前同步的GEO list信息 */
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU                      *pstAcqSysInfo;                         /* 需要捕获的系统记录列表指针:根据总个数分配内存 */
}CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU;


/*****************************************************************************
 结构名    : CNAX_XSD_CAMPED_SYS_INFO_STRU
 结构说明  : 驻留成功的系统信息
 1.日    期   : 2014年8月21日
   作    者   : l60609
   修改内容   : 新增

 2.日    期   : 3/12/2014
   作    者   : y00245242
   修改内容   : add camp on flag

 3.日    期   : 2015年7月10日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
typedef struct
{
    CNAS_PRL_1X_SYSTEM_STRU             stSystem;
    VOS_UINT32                          ulMcc;
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32 enSrvStatus;
    VOS_UINT16                          usImsi11_12;
    VOS_UINT8                           ucRoamingInd;
    CNAS_XSD_SYS_TYPE_ENUM_UINT8        enSysType;
    VOS_UINT8                           ucCampOnFlag;
    VOS_UINT8                           aucRsved[3];
}CNAX_XSD_CAMPED_SYS_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU
 结构说明  : 呼叫重拨的控制信息
 1.日    期   : 2014年11月21日
   作    者   : c00299063
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallExistFlg;              /* call exist flag */
    VOS_UINT8                           ucOrigSysExistFlg;           /* 呼叫发起系统是否存在 */
    VOS_UINT8                           aucReserved[2];              /* reserved bytes */
    CNAS_PRL_1X_SYSTEM_STRU             stCallOrignalSys;            /* 呼叫开始时的驻留系统 */
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU     stCallRedialChanScanList;    /* 呼叫重拨场景下的频点列表 */
}CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_EMC_CALL_CTRL_INFO_STRU
 结构说明  : 紧急呼流程控制信息
 1.日    期   : 2015年07月04日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_XSD_EMC_STATE_ENUM_UINT8                           enEmcState;                  /* 紧急呼流程状态 */
    VOS_UINT8                                               ucCallBackSrchCounter;       /* CallBack 15s搜网计数器 */
    VOS_UINT8                                               aucReserved[2];              /* reserved bytes */
    CNAS_XSD_CALLBACK_CFG_STRU                              stCallBackCfg;               /* 紧急呼CALLBACK模式配置 */
    CNAS_PRL_1X_SYSTEM_STRU                                 stCallOrignalSys;            /* 紧急呼接通时的驻留系统 */
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                         stEmcCallRedialChanScanList; /* 紧急呼重拨场景下的频点列表 */
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                    stEmcRedialSysAcqCfg;        /* 紧急呼重新搜网控制 */
    CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU          stEmcCallBackCfInfo;         /* 紧急呼回呼模式异频临区频点信息 */
} CNAS_XSD_EMC_CALL_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_OOC_CTX_INFO_STRU
 结构说明  : OOC上下文信息
 1.日    期   : 2015年1月4日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucWaitSearchFlag;           /* OOC等待搜索标志，即在MRU0搜索时，OOC定时器到期 */
    VOS_UINT8                                               ucCurrentPhase;             /* 记录当前搜索阶段 */
    VOS_UINT16                                              usCurrentTimes;             /* 记录在当前阶段已经搜索次数 */
    VOS_UINT8                                               ucDoTrafficFlag;            /* 记录DO是否在业务态标志 */
    VOS_UINT8                                               ucFirstFourAcqArrivedFlag;  /* 记录DO在Traffic下，1X前4次捕获是否达到 */
    VOS_UINT8                                               ucAttemptTimesInDoTraffic;  /* 记录DO在traffic下，1X已经尝试的次数，超过四次，不在维护该变量，
                                                                                           通过ucFirstFourAcqFlag维护 */
    VOS_UINT8                                               ucSceneSetFlag;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enOocSearchScene;
}CNAS_XSD_OOC_CTX_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_OOC_TIMER_INFO_STRU
 结构说明  : OOC搜网定时器信息
 1.日    期   : 2015年1月4日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}CNAS_XSD_OOC_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_OOC_CONFIG_INFO_STRU
 结构说明  : OOC搜网调度信息, 所有信息源与NV配置
 1.日    期   : 2015年1月4日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucMru0SearchTimerLen;       /* 搜索MRU0时长 */
    VOS_UINT8                                               ucPhaseNum;                 /* 搜索步长数目 */
    VOS_UINT8                                               ucInsertOrigChanFlg;        /* 在同步请求前是否插入先前驻留频点 */
    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;          /* 频点重复搜索策略 */
    VOS_UINT8                                               uc1xOocDoTchPhase1TimerLen; /* Do TCH，前4次尝试 Ooc Timer 最短时长 */
    VOS_UINT8                                               uc1xOocDoTchPhase2TimerLen; /* Do TCH，4次以上尝试 Ooc Timer 最短时长 */
    VOS_UINT8                                               aucReserved[2];
    CNAS_XSD_OOC_TIMER_INFO_STRU                            astOocTimerInfo[CNAS_XSD_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_XSD_OOC_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_1X_OOC_INFO_STRU
 结构说明  : out of cell相关信息
 1.日    期   : 2015年1月4日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_XSD_OOC_CTX_INFO_STRU                              stOocCtxInfo;
    CNAS_XSD_OOC_CONFIG_INFO_STRU                           stConfigInfo;               /* 保存OOC场景下，搜网配置信息 */
}CNAS_XSD_OOC_SCHEDULE_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU
 结构说明  : GEO list搜索信息，记录PRL表中GEO的起始索引以及搜索状态
 1.日    期   : 2015年7月3日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usGeoBeginIndex;
    VOS_UINT16                                              usGeoSrchStatus;
}CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_GEO_LIST_SRCH_INFO_STRU
 结构说明  : GEO list搜索信息, 记录某个GEO是否已经搜索过
 1.日    期   : 2015年7月3日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usGeoNum;                   /* GEO数目 */
    VOS_UINT16                                              usReserved;
    CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU                     *pstGeoSrchInfo;             /* 指向GEO搜索信息首地址 */
}CNAS_XSD_GEO_LIST_SRCH_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU
 结构说明  : 同步成功的系统频点列表信息
 1.日    期   : 2015年7月7日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalNum;                                     /* 所能保存频点的最大个数 */
    VOS_UINT32                          ulCurNum;                                       /* 当前同步到的频点数目 */
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreq[CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM];    /* 保存同步到系统的频点 */
}CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_AVOID_SCHEDULE_STRU
 结构说明  : avoid策略信息
  1.日    期   : 2015年11月23日
    作    者   : c00299063
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAvoidTimerLen[CNAS_XSD_AVOID_REASON_MAX][CNAS_XSD_AVOID_MAX_PHASE_NUM];
}CNAS_XSD_AVOID_SCHEDULE_INFO_STRU;


/** ****************************************************************************
 * Name        : CNAS_XSD_SYSTEM_ACQUIRE_CTRL_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    CNAS_XSD_REDIRECTION_INFO_STRU                          stRedirInfo;
    CNAS_XSD_BSR_INFO_STRU                                  stBsrInfo;
    CNAS_XSD_AVOID_FREQ_LIST_STRU                           stAvoidFreqList;
    CNAS_XSD_MRU_LIST_STRU                                  stMruList;
    CNAS_XSD_CALL_REDIAL_SYS_LIST_STRU                      stCallList;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                         stChanScanList;     /* 系统同步时使用到的频点列表,全局维护,可能不同场景
                                                                                   构造的频点列表不一致:初始化时分配堆空间,关机时需要释放 */

    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU              stHisSyncedSysFreqList;     /* 同步到的历史系统频点列表 */
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU                        stGeoListSrchInfo;          /* GEO list搜索信息，记录GEO搜索的状态 */
    CNAX_XSD_CAMPED_SYS_INFO_STRU                           stCurCampedSysInfo;
    CNAS_XSD_1X_BAND_UN                                     unUeSupportedBand;

    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU                     stCallRedialInfo;

    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU                       stFreqLockPara;

    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                         stOocScheduleInfo;

    CNAS_XSD_EMC_CALL_CTRL_INFO_STRU                        stEmcCallInfo;      /* 紧急呼信息 */

    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU              stCdma1XCustomPrefChan; /* 电信常用频点和频点信息 */

    CNAS_XSD_AVOID_SCHEDULE_INFO_STRU                       stAvoidScheduInfo;

    VOS_UINT8                                               ucSrvAcqFlg;        /* 记录当前是否处于业务触发搜网的标识 */

    VOS_UINT8                                               aucReserved[3];     /* 保留位 */

}CNAS_XSD_SYSTEM_ACQUIRE_CTRL_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_CALL_INFO_STRU
 结构说明  : CNAS XSD 模块保存的呼叫相关的信息
 1.日    期   : 2014年08月01日
   作    者   : l60609
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucExistNorVoiceCall;
    VOS_UINT8                           ucExistEmcVoiceCall;
    VOS_UINT8                           ucExistEmcDataCall;
    VOS_UINT8                           ucRsved;
}CNAS_XSD_CALL_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_FSM_SWITCH_ON_CTX_STRU
 结构说明  : 存放开机状态机的上下文信息
  1.日    期   : 2014年07月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulXsdReadCardFileFlg;                   /* 标记卡文件是否读取完成 */
    VOS_UINT8                           aucReserved[4];
}CNAS_XSD_FSM_SWITCH_ON_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_FSM_POWER_OFF_CTX_STRU
 结构说明  : 存放关机状态机的上下文信息
  1.日    期   : 2014年10月20日
    作    者   : w00176964
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCampOnNeedFlg;                    /* 是否需要驻留标记 */
    VOS_UINT8                           ucBufCallRelIndFlg;                 /* 缓存的呼叫释放指示标记 */
    VOS_UINT8                           aucReserved[2];
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stBuffCallRelFreq;                  /* 缓存的呼叫释放指示的频点信息 */
}CNAS_XSD_FSM_POWER_OFF_CTX_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_SYSTEM_WITH_SAME_CHANNEL_STRU
 结构说明  : 保存相同频点捕获的系统记录信息
 1.日    期   : 2014年8月05日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    VOS_UINT16                          usSysNum;
    VOS_UINT8                           aucRsv[2];
    CNAS_PRL_1X_SYSTEM_ID_STRU          astSysId[CNAS_XSD_1X_MAX_SAME_PRIO_SYS_NUM];            /* 需要捕获的系统ID */
}CNAS_XSD_SYSTEM_WITH_SAME_CHANNEL_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LAST_1X_ACQ_SYSTEM_INFO
 结构说明  : 存放最近一次发给CAS发送的捕获系统信息
  1.日    期   : 2014年08月18日
    作    者   : l60609
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usSndSysNum;                        /* 保存上次发给CAS的需要捕获系统的个数 */
    VOS_UINT8                               aucRsved[2];
    CNAS_XSD_SYSTEM_WITH_SAME_CHANNEL_STRU  astSndSys[CNAS_XSD_1X_SND_CAS_MAX_SYSTEM_NUM];  /* 保存上次发给CAS的需要捕获的系统 */
}CNAS_XSD_LATEST_SND_CAS_ACQ_SYSTEM_INFO;

/*****************************************************************************
 结构名    : CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU
 结构说明  : 呼叫释放信息, 存放呼叫释放后，任何系统直接驻留的频点
             如下:
             Upon call release MS shall first try to acquire the last channel
             being used in Traffic state. If MS fails to acquire the last channel
             being used in Traffic state, it shall try to acquire the channel
             that is listed in MRU[0].
 1.日    期   : 2015年7月27日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChanNum;       /* 呼叫释放同步的频点个数 */
    VOS_UINT8                           aucReserved[2];
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreq[CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM];   /* 保存呼叫释放后，首次需要搜索的频点 */
}CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_FSM_SYS_ACQ_CTX_STRU
 结构说明  : 存放SYS ACQ状态机的上下文信息
  1.日    期   : 2014年08月08日
    作    者   : l60609
    修改内容   : 新建
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables
  3.日    期   : 2015年7月4日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsAvailSysAcqList;/* 标记当前捕获列表是否为available system list，默认为VOS_FALSE */
    VOS_UINT8                                               ucAbortFlg;         /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    VOS_UINT8                                               aucRsved[2];
    CNAS_PRL_1X_SYSTEM_ID_STRU                              stLastSyncedSys;    /* 用于记录最后一次同步到的系统，目的为SID变更上报SID信息 */
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                  stGeoSysSrchList;
    /* 移available list到状态机上下文 */
    CNAS_XSD_AVAILABLE_LIST_STRU                            stAvailSysList;
    CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU                 stCallRelFirstSyncFreq;
}CNAS_XSD_FSM_SYS_ACQ_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_FSM_L1_MAIN_CTX_STRU
 结构说明  : 存放开机状态机的上下文信息
  1.日    期   : 2014年07月04日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurAvailableTimerCount;               /* 当前Available Timer启动次数 */
}CNAS_XSD_FSM_L1_MAIN_CTX_STRU;




typedef struct
{
    VOS_UINT8                               ucAbortFlag ;
    VOS_UINT8                               aucReserve[3];
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU         stRedireScanList;
}CNAS_XSD_FSM_REDIR_CTX_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef union
{
    CNAS_XSD_FSM_SWITCH_ON_CTX_STRU     stSwitchOnCtx;
    CNAS_XSD_FSM_POWER_OFF_CTX_STRU     stPowerOffCtx;
    CNAS_XSD_FSM_SYS_ACQ_CTX_STRU       stSysAcqCtx;
    CNAS_XSD_FSM_L1_MAIN_CTX_STRU       stL1MainCtx;
    CNAS_XSD_FSM_REDIR_CTX_STRU         stRedirCtx;
}CNAS_XSD_FSM_EXTRA_CTX_UNION;

/*****************************************************************************
 结构名    : CNAS_XSD_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    CNAS_XSD_FSM_ID_ENUM_UINT32         enFsmId;

    /* 上层状态机标识 */
    CNAS_XSD_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* 上层状态机入口消息类型 */
    VOS_UINT32                          ulParentEventType;

    /* 当前状态 */
    VOS_UINT32                          ulState;

    /* 入口消息MSGID和内容  */
    CNAS_XSD_MSG_STRU                   stEntryMsg;

    /* 状态机数据 */
    CNAS_XSD_FSM_EXTRA_CTX_UNION        unFsmCtx;
}CNAS_XSD_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_FSM_STACK_STRU
 结构说明  : 状态机栈描述结构
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT16                          usStackPopFlg;                          /* 当前栈pop标志 */
    CNAS_XSD_FSM_CTX_STRU               astFsmStack[CNAS_XSD_MAX_FSM_STACK_DEPTH];  /* 状态机栈的深度 */
}CNAS_XSD_FSM_STACK_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_INT_MSG_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2014年10月15日
   作    者   : c00299063
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[CNAS_XSD_MAX_INT_MSG_QUEUE_NUM]; /* XSD的消息队列数组，存放消息指针 */
}CNAS_XSD_INT_MSG_QUEUE_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_CTX_STRU
 结构说明  : CNAS XSD 模块运行上下文
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        CNAS XSD状态机状态及其状态栈
    **************************************************************************/
    CNAS_XSD_FSM_CTX_STRU               stCurFsm;                               /* 状态机当前的状态机数组 */
    CNAS_XSD_FSM_STACK_STRU             stFsmStack;                             /* 状态机的状态机栈数组   */

    /* CNAS XSD缓存消息队列 */
    CNAS_XSD_CACHE_MSG_QUEUE_STRU       stCacheMsgQueue;

    CNAS_XSD_INT_MSG_QUEUE_STRU         stIntMsgQueue;

    CNAS_XSD_SYSTEM_ACQUIRE_CTRL_STRU   stSysAcqCtrl;

    CNAS_XSD_TEST_CONFIG_STRU           stTestConfig;

    CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU      stSysAcqNvimCfg;
}CNAS_XSD_CTX_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID  CNAS_XSD_LoadSubFsm(
    CNAS_XSD_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID CNAS_XSD_InitFsmL2(
    CNAS_XSD_FSM_ID_ENUM_UINT32          enFsmId
);
VOS_VOID CNAS_XSD_PopFsm( VOS_VOID );

VOS_VOID CNAS_XSD_PushFsm(
    CNAS_XSD_FSM_STACK_STRU             *pstFsmStack,
    CNAS_XSD_FSM_CTX_STRU               *pstNewFsm
);

VOS_VOID CNAS_XSD_QuitFsmL2(VOS_VOID);

VOS_VOID  CNAS_XSD_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 CNAS_XSD_GetFsmTopState(VOS_VOID);

CNAS_XSD_CACHE_MSG_QUEUE_STRU* CNAS_XSD_GetCacheMsgAddr(VOS_VOID);

VOS_UINT32 CNAS_XSD_GetCacheMsgNum(VOS_VOID);

VOS_UINT32  CNAS_XSD_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);
VOS_UINT32 CNAS_XSD_GetNextCachedMsg(
    CNAS_XSD_MSG_STRU                  *pstEntryMsg
);

CNAS_XSD_FSM_CTX_STRU* CNAS_XSD_GetCurFsmAddr(VOS_VOID);

NAS_FSM_DESC_STRU* CNAS_XSD_GetCurFsmDesc(VOS_VOID);

CNAS_XSD_FSM_ID_ENUM_UINT32 CNAS_XSD_GetCurrFsmId(VOS_VOID);

CNAS_XSD_MSG_STRU* CNAS_XSD_GetCurrFsmEntryMsgAddr(VOS_VOID);

CNAS_XSD_FSM_STACK_STRU* CNAS_XSD_GetFsmStackAddr(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetFsmStackDepth(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetFsmStackPopFlg(VOS_VOID);

CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID);

CNAS_XSD_CTX_STRU* CNAS_XSD_GetXsdCtxAddr(VOS_VOID);

VOS_VOID CNAS_XSD_InitFsmCtx_Redirection(VOS_VOID);

VOS_VOID CNAS_XSD_InitCtx(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
);

VOS_VOID CNAS_XSD_InitAvailSysList(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_AVAILABLE_LIST_STRU        *pstAvailList
);

VOS_VOID CNAS_XSD_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);

VOS_VOID CNAS_XSD_InitFsmCtx_L1Main(VOS_VOID);

VOS_VOID CNAS_XSD_InitFsmCtx_SwitchOn(VOS_VOID);

VOS_VOID CNAS_XSD_InitFsmCtx_PowerOff(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetCampOnNeedFlg_PowerOff(VOS_VOID);

VOS_VOID CNAS_XSD_SetCampOnNeedFlg_PowerOff(
    VOS_UINT8                           ucCampOnNeedFlg
);

VOS_UINT8 CNAS_XSD_GetBufCallRelIndFlg_PowerOff(VOS_VOID);
VOS_VOID CNAS_XSD_SetBufCallRelIndFlg_PowerOff(
    VOS_UINT8                           ucBufCallRelIndFlg
);

CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetBufCallRelFreqInfo_PowerOff(VOS_VOID);
VOS_VOID CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);


VOS_VOID CNAS_XSD_InitFsmCtx_SysAcq(VOS_VOID);

VOS_VOID CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
);

VOS_VOID CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
);

CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetScanChanListAddr(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetScanChannelNum(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex(VOS_VOID);

VOS_VOID CNAS_XSD_SetCurChannelScanIndex(
    VOS_UINT16                          usCurScanIndex
);
CNAS_XSD_MRU_LIST_STRU* CNAS_XSD_GetMruList(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetMruListNum(VOS_VOID);
VOS_UINT32 CNAS_XSD_GetMru0SysId(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru0SysId
);

VOS_UINT32 CNAS_XSD_GetMru1SysId(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru1SysId
);

CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU* CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetCurSysAcqListNum_SysAcq(VOS_VOID);
VOS_VOID CNAS_XSD_SetAvailSysAcqListFlg_SysAcq(
    VOS_UINT8                           ucFlg
);
VOS_UINT8 CNAS_XSD_GetAvailSysAcqListFlg_SysAcq(VOS_VOID);

VOS_VOID CNAS_XSD_SetAbortFlg_SysAcq(
    VOS_UINT8                           ucFlg
);

VOS_UINT8 CNAS_XSD_GetAbortFlg_SysAcq(VOS_VOID);

CNAS_XSD_AVAILABLE_LIST_STRU* CNAS_XSD_GetAvailSysFreqListAddr(VOS_VOID);

VOS_VOID CNAS_XSD_AddAvailSysFreqList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

VOS_VOID CNAS_XSD_SetAvailSysFeqListNextSrchIndex(
    VOS_UINT8                           ucNextSrchIndex
);

VOS_UINT8 CNAS_XSD_GetAvailSysFreqListNextSrchIndex(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetAvailSysFreqNum(VOS_VOID);

VOS_VOID CNAS_XSD_UpdateMru0(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
);


VOS_UINT32 CNAS_XSD_GetUeSupportedBandClass(VOS_VOID);

VOS_VOID CNAS_XSD_SetUeSupportedBandClass(
    VOS_UINT32                          ulUeSupportedBand
);

VOS_VOID CNAS_XSD_UpdateCurCampedSysInfo(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
);

CNAX_XSD_CAMPED_SYS_INFO_STRU* CNAS_XSD_GetCurCampedSysInfo(VOS_VOID);


VOS_VOID CNAS_XSD_SetAbortFlag_Redir(
    VOS_UINT8                                ucAbortFlag
);

VOS_UINT8 CNAS_XSD_GetAbortFlag_Redir(VOS_VOID);

CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetScanChanListAddr_Redir(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetScanChannelNum_Redir(VOS_VOID);


CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetCallRedialScanChanListAddr(VOS_VOID);

CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetEmcCallRedialScanChanListAddr(VOS_VOID);

CNAS_XSD_SERVICE_STATUS_ENUM_UINT32 CNAS_XSD_GetCurSrvStatus(VOS_VOID);

VOS_VOID CNAS_XSD_SetCurSrvStatus(
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32                     enSrvStatus
);

CNAS_XSD_INT_MSG_QUEUE_STRU* CNAS_XSD_GetIntMsgQueueAddr(VOS_VOID);

VOS_VOID CNAS_XSD_InitInternalBuffer(
    CNAS_XSD_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_VOID CNAS_XSD_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *CNAS_XSD_GetNextIntMsg(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetIntMsgNum(VOS_VOID);


CNAS_XSD_AVOID_FREQ_LIST_STRU* CNAS_XSD_GetAvoidFreqListAddr(VOS_VOID);



VOS_UINT8 CNAS_XSD_GetAvoidFreqListNum(VOS_VOID);

VOS_VOID CNAS_XSD_DeleteAvoidFlagFromAvoidList(
    VOS_UINT8                           ucIndex
);

CNAS_XSD_AVOID_FREQ_INFO_STRU *CNAS_XSD_GetAvoidFreqFromAvoidList(
    VOS_UINT8                           ucIndex
);

VOS_VOID CNAS_XSD_ClearCacheMsg(
    VOS_UINT8                           ucIndex
);

VOS_VOID CNAS_XSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_UINT32 CNAS_XSD_ClearCacheMsgByMsgName(
    VOS_UINT32                          ulSndPid,
    VOS_UINT16                          usMsgName
);


VOS_VOID CNAS_XSD_SetCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
);

VOS_UINT8 CNAS_XSD_GetCallExistFlg(VOS_VOID);

VOS_VOID CNAS_XSD_ClearCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
);

VOS_VOID CNAS_XSD_SaveCallOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
);

CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetCallOrignalSys(VOS_VOID);

VOS_VOID CNAS_XSD_SaveEmcCallOriginalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
);

CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetEmcCallOriginalSys(VOS_VOID);

VOS_VOID CNAS_XSD_ClearEmcCallOriginalSys( VOS_VOID );

VOS_UINT32 CNAS_XSD_IsEmcCallOriginalSysExist( VOS_VOID );

/* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
VOS_VOID CNAS_XSD_InitCacheMsgQueue(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
);
/* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

VOS_VOID CNAS_XSD_SetCallOrigSysExistFlg(
    VOS_UINT8                           ucFlg
);

VOS_UINT8 CNAS_XSD_GetCallOrigSysExistFlg(VOS_VOID);

VOS_VOID CNAS_XSD_SetSystemCampOnFlag(
    VOS_UINT8                           ucCampOnFlg
);

VOS_UINT8 CNAS_XSD_GetSystemCampOnFlag(VOS_VOID);

VOS_VOID CNAS_XSD_InitCallRedialCtrlInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallRedialInfo
);


VOS_VOID CNAS_XSD_InitEmcCallCtrlInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_EMC_CALL_CTRL_INFO_STRU    *pstEmcCallInfo
);

CNAS_XSD_REDIRECTION_INFO_STRU *CNAS_XSD_GetRedirectionInfoAddr(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetRedirectionFlag(VOS_VOID);

VOS_VOID CNAS_XSD_SetRedirectionFlag(
    VOS_UINT8               ucRedirection
);

VOS_VOID CNAS_XSD_SetEmcRedirectionFlg(
    VOS_VOID
);

VOS_UINT8 CNAS_XSD_GetRedirectionReturnIfFailFlag(VOS_VOID);

VOS_VOID CNAS_XSD_SaveRedirectionOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU         *pstOriginalSystem
);

CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetRedirectionOrignalSys(VOS_VOID);

CNAS_XSD_SCAN_CHANNEL_INFO_STRU *CNAS_XSD_GetRedirectionChanList(VOS_VOID);

VOS_VOID CNAS_XSD_InitRedirectionInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_REDIRECTION_INFO_STRU      *pstRedirInfo
);

CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_XSD_GetFreqLockAddr(VOS_VOID);

VOS_VOID CNAS_XSD_InitCFreqLockValue(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetFreqLockMode(VOS_VOID);


CNAS_XSD_OOC_SCHEDULE_INFO_STRU *CNAS_XSD_GetOocScheduleInfo(VOS_VOID);

VOS_VOID CNAS_XSD_InitOocScheduleInfo(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
);

VOS_VOID CNAS_XSD_InitOocCtxInfo(VOS_VOID);

VOS_VOID CNAS_XSD_SetNdssIndFlag(
    VOS_UINT8                           ucNdssInd
);

VOS_UINT8 CNAS_XSD_GetNdssIndFlag(VOS_VOID);


VOS_VOID CNAS_XSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag);

VOS_UINT8 CNAS_XSD_GetOocWaitSearchFlag(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetOocInsertOrigChanFlg(VOS_VOID);

CNAS_XSD_OOC_CONFIG_INFO_STRU *CNAS_XSD_GetOocScheduleConfigInfo(VOS_VOID);

CNAS_XSD_TEST_CONFIG_STRU* CNAS_XSD_GetTestConfig(VOS_VOID);

CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU* CNAS_XSD_Get1xSysAcqNvimConfig(VOS_VOID);

CNAS_XSD_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8 CNAS_XSD_GetNegPrefSysCmpType(VOS_VOID);

VOS_VOID CNAS_XSD_InitTestConfig(
    CNAS_XSD_TEST_CONFIG_STRU          *pstTestConfig
);

VOS_VOID CNAS_XSD_InitSysAcqNvimCfg(
    CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU                         *pstSysAcqNvimCfg
);

VOS_UINT8 CNAS_XSD_GetSrvAcqFlg(VOS_VOID);

VOS_VOID CNAS_XSD_SetSrvAcqFlg(
    VOS_UINT8                           ucSrvAcqFlg
);

VOS_VOID CNAS_XSD_ClearEmcCallRedialScanChanList( VOS_VOID );

CNAS_XSD_EMC_STATE_ENUM_UINT8 CNAS_XSD_GetEmcState(VOS_VOID);

VOS_VOID CNAS_XSD_SetEmcState(
    CNAS_XSD_EMC_STATE_ENUM_UINT8       enEmcState
);

VOS_VOID CNAS_XSD_SetEmcCallBackSrchCounter(
    VOS_UINT8                           ucEmcCallBackCounter
);

CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU* CNAS_XSD_GetEmcCallBackCandidateFreqInfo(VOS_VOID);

VOS_VOID CNAS_XSD_ClearEmcCallBackCandidateFreq(
    VOS_VOID
);

VOS_VOID CNAS_XSD_SetEmcCallBackCandidateFreq(
    VOS_UINT16                          usCfFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstCfInfo
);

VOS_UINT8 CNAS_XSD_GetEmcCallBackSrchCounter(VOS_VOID);


CNAS_XSD_CALLBACK_CFG_STRU *CNAS_XSD_GetCallBackCfg( VOS_VOID );

VOS_VOID CNAS_XSD_InitGeoSrchListInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo
);

CNAS_XSD_GEO_LIST_SRCH_INFO_STRU *CNAS_XSD_GetGeoSrchListInfoAddr(VOS_VOID);

VOS_VOID CNAS_XSD_ClearGeoSrchListStatus(VOS_VOID);

VOS_VOID CNAS_XSD_FreeBufferOfGeoSrchList(VOS_VOID);

VOS_VOID CNAS_XSD_InitHistorySyncedSysFreqList(
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstHisSyncedSysFreqList
);

CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU *CNAS_XSD_GetHistorySyncedSysFreqList(VOS_VOID);

VOS_VOID CNAS_XSD_UpdateHistorySyncedSysFreqList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
);

CNAS_PRL_1X_SYSTEM_ID_STRU* CNAS_XSD_GetLastSyncedSys(VOS_VOID);

CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetLastSyncedFreq(VOS_VOID);

VOS_VOID CNAS_XSD_UpdateLastSyncedSys(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstCurSyncedSys
);

CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU* CNAS_XSD_GetCallRelAnyCampOnFreqListAddr(VOS_VOID);

VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex_Redir(VOS_VOID);
VOS_VOID CNAS_XSD_SetCurChannelScanIndex_Redir(VOS_UINT16 usIndex);

CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU* CNAS_XSD_GetCdma1XCustomPrefChannels(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetNoCardModeCfgFlg(VOS_VOID);

VOS_VOID CNAS_XSD_SetNoCardModeCfgFlg(
    VOS_UINT8                           ucNoCardModeCfgFlg
);

CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU* CNAS_XSD_GetEmcRedialSysAcqCfgInfo(VOS_VOID);

CNAS_XSD_AVOID_SCHEDULE_INFO_STRU* CNAS_XSD_GetAvoidScheduInfoAddr(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
    VOS_UINT8                          *pucIndex
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

#endif /* end of CnasXsdCtx.h */
