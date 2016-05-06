/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdCtx.h
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2014年12月16日
  最近修改   :
  功能描述   : CnasHsdCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : g00256031
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HSD_CTX_H__
#define __CNAS_HSD_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "CnasPrlApi.h"
#include "CnasTimerMgmt.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "CnasCcb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_HSD_MAX_FSM_STACK_DEPTH                        (4)                 /* 状态机栈的深度 */

#define CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM                    (8)                 /* 最大缓存消息的个数 */

#define CNAS_HSD_MAX_MSG_BUFFER_LEN                         (1600)              /* 消息的最大长度，包括状态机保存的入口消息和CACHE消息 */

/* 存储的最大的MRU个数，CGD 130 5.2.2 The number of entries in an MRU list is implementation dependent but a typical number may be 12 */
#define CNAS_HSD_MAX_MRU_SYS_NUM                            (12)

#define CNAS_HSD_CHECK_BYTES_SUBNET_ID                      (6)                 /* 存MRU信息时需要比较的Subnet字节数 */

#define CNAS_HSD_MAX_OOC_SCHEDULE_PHASE_NUM                 (8)                 /* NV中存储搜索时间间隔的最大数目，暂定8，待确认 */
#define CNAS_HSD_TIMER_LEN_10_SEC                           (10)
#define CNAS_HSD_TIMER_LEN_5_SEC                            (5)
#define CNAS_HSD_ATTEMP_IN_DO_TRAFFIC_4_TIMES               (4)
#define CNAS_HSD_ATTEMP_UNLIMITED_TIMES                     (65535)

#define CNAS_HSD_MAX_INT_MSG_QUEUE_NUM                      (8)

/* 存储的最大的history system的个数 */
#define CNAS_HSD_HRPD_ACQED_SUCC_SYS_MAX_NUM                (20)

/* 存储的最大的avoid freq的个数 */
#define CNAS_HSD_MAX_AVOID_FREQ_NUM                         (100)

#define CNAS_HSD_MAX_SLICE_VALUE                            (0xFFFFFFFF)

#define CNAS_HSD_MAX_PREF_SUBNET_NUM                        ( 16 )          /*高优先级网络最大个数*/

#define CNAS_HSD_TIMER_LEN_20_SEC                           (20)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_HSD_FSM_ID_ENUM
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_FSM_ID_ENUM
{
    /***********************************************************************
     * HSD L1状态机标识
     ***********************************************************************/
    /* CNAS HSD L1 main状态机的标识 */
    CNAS_HSD_FSM_L1_MAIN                                    =0x00,

    /***********************************************************************
     * HSD L2状态机的标识
     ***********************************************************************/
    /* 协议栈初始化L2状态机 */
    CNAS_HSD_FSM_SWITCH_ON                                  =0x01,

    /* 协议栈关机L2状态机 */
    CNAS_HSD_FSM_POWER_OFF                                  =0x02,

    /* 协议栈SYSTEM ACQUIRE L2状态机 */
    CNAS_HSD_FSM_SYS_ACQ                                    =0x03,

    /* 协议栈POWER SAVE L2状态机 */
    CNAS_HSD_FSM_POWER_SAVE                                 =0x04,

    /* 协议栈异系统 L2状态机 */
    CNAS_HSD_FSM_INTER_SYS                                  =0x05,



    CNAS_HSD_BUTT

};
typedef VOS_UINT32 CNAS_HSD_FSM_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : CNAS_HSD_INIT_CTX_TYPE_ENUM
 结构说明  : 初始化HSD CTX类型
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新增
*****************************************************************************/
enum CNAS_HSD_INIT_CTX_TYPE_ENUM
{
    CNAS_HSD_INIT_CTX_STARTUP                    = 0,
    CNAS_HSD_INIT_CTX_POWEROFF                   = 1,
    CNAS_HSD_INIT_CTX_BUILD_FREQ                 = 2,
    CNAS_HSD_INIT_CTX_BUTT
};
typedef VOS_UINT8 CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_HSD_READ_CARD_FILES_CNF_ENUM
 结构说明  : 用于标记读取卡文件的回复消息
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
enum   CNAS_HSD_READ_CARD_FILES_CNF_ENUM
{
    CNAS_HSD_READ_CARD_FILE_FLG_NULL                        = 0x00,
    CNAS_HSD_READ_CARD_FILE_PRL_FLG                         = 0x01,
    CNAS_HSD_READ_CARD_FILE_EPRL_FLG                        = 0x02,

    CNAS_HSD_READ_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32;


/*****************************************************************************
 枚举名    : CNAS_HSD_SCAN_LIST_BUILD_SCENE_ENUM
 枚举说明  : 各种系统捕获场景的定义
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_SYS_ACQ_SCENE_ENUM
{
    CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON  = 0,                  /* 开机 */
    CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST,                     /* 出服务区 */
    CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION,                     /* 重定向 */
    CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0,                        /* OOC搜索 */

    CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK,                 /* 数据呼叫快速搜场景 */

    CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,                    /*  */

    CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY,                   /* 高优先级搜网 */

    CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER,                      /* MSCC发起的搜网，场景为OTHER，HSD统一按照SYS LOST场景处理 */

    CNAS_HSD_SYS_ACQ_SCENE_CFREQ_LOCK,                      /* 锁频搜网 */

    CNAS_HSD_SYS_ACQ_SCENE_OOC_SWITCH_ON,                   /* 开机后的ooc搜网 */

    CNAS_HSD_SYS_ACQ_SCENE_NO_RF_RESUME,                   /* NO_RF后RF AVAIL的搜网 */

    CNAS_HSD_SYS_ACQ_SCENE_BUTT
};
typedef VOS_UINT32 CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32
 枚举说明  : 系统类型
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_SYS_MODE_TYPD_ENUM
{
    CNAS_HSD_SYS_MODE_HYBRID = 0,
    CNAS_HSD_SYS_MODE_NONHYBRID,
    CNAS_HSD_SYS_MODE_BUTT,
};

typedef VOS_UINT32 CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_1X_SYSTEM_STATUS_ENUM_UINT32
 枚举说明  : 1X系统是否有效
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_1X_SYSTEM_STATUS_ENUM
{
    CNAS_HSD_1X_SYSTEM_UNAVAILABLE = 0,
    CNAS_HSD_1X_SYSTEM_AVAILABLE,
    CNAS_HSD_1X_SYSTEM_STATUS_BUTT,
};

typedef VOS_UINT32 CNAS_HSD_1X_SYSTEM_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_CAS_SESSION_NEG_STATUS_ENUM
 枚举说明  : CAS是否处于session negotiation过程
 1.日    期   : 2015年01月14日
   作    者   : x00306642
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_CAS_SESSION_NEG_STATUS_ENUM
{
    CNAS_HSD_NOT_IN_SESSION_NEG = 0,
    CNAS_HSD_IN_SESSION_NEG,
    CNAS_HSD_SESSION_NEG_STATUS_BUTT
};
typedef VOS_UINT32 CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_AT_STATUS_ENUM_UINT32
 枚举说明  : AT当前所处的状态
 1.日    期   : 2015年01月14日
   作    者   : x00306642
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_CAS_STATUS_ENUM
{
    CNAS_HSD_AT_STATUS_ENUM_NONE       = 0x0000,
    CNAS_HSD_AT_STATUS_ENUM_INIT       = 0x0001,
    CNAS_HSD_AT_STATUS_ENUM_IDLE       = 0x0002,
    CNAS_HSD_AT_STATUS_ENUM_CONN       = 0x0003,

    CNAS_HSD_AT_STATUS_ENUM_BUTT       = 0x0004
};
typedef VOS_UINT32 CNAS_HSD_AT_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_AVOID_ITEM_USED_FALG_ENUM
 枚举说明  : avoid项的使用标记
 1.日    期   : 2015年01月07日
   作    者   : x00306642
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_AVOID_ITEM_USED_FALG_ENUM
{
    CNAS_HSD_AVOID_ITEM_UNUSED = 0,
    CNAS_HSD_AVOID_ITEM_USED,

    CNAS_HSD_AVOID_ITEM_USED_FALG_BUTT
};
typedef VOS_UINT32 CNAS_HSD_AVOID_ITEM_USED_FALG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_SYS_REACQ_FALG_ENUM
 枚举说明  : avoid模块通知HSD其他模块需不需要重新搜网
 1.日    期   : 2015年01月15日
   作    者   : x00306642
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_REACQ_FALG_ENUM
{
    CNAS_HSD_NOT_NEED_REACQ = 0,
    CNAS_HSD_NEED_REACQ,

    CNAS_HSD_REACQ_FALG_BUTT
};
typedef VOS_UINT32 CNAS_HSD_REACQ_FALG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_AVOID_REASON_ENUM
 枚举说明  : avoid频点原因
 1.日    期   : 2015年01月06日
   作    者   : x00306642
   修改内容   : 新增
*****************************************************************************/
enum CNAS_HSD_AVOID_REASON_ENUM
{
    CNAS_HSD_AVOID_PROTOCAL_MISMATCH = 0,               /* protocal mismatch */
    CNAS_HSD_AVOID_REDIRECTION,                         /* redirection */
    CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT,         /* session negotiation timeout */
    CNAS_HSD_AVOID_SESSION_NEGOTIATION_FAILURE,         /* session negotiation failure */
    CNAS_HSD_AVOID_PERSISTENCE_TEST_FAILURE,            /* persistence test failure */
    CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE,           /* max access probes failure */
    CNAS_HSD_AVOID_AUTHEN_OR_BILLING_FAILURE,           /* authen or billing failure */
    CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE,             /* busy or general failure */
    CNAS_HSD_AVOID_TCA_TIMEOUT,                         /* TCA timeout */

    CNAS_HSD_AVOID_FAIL_CONTINUE_THREE_TIMES,

    CNAS_HSD_AVOID_PREFER_CH_NOT_VALID,
    CNAS_HSD_AVOID_REASON_MAX = 12,

    CNAS_HSD_AVOID_REASON_BUTT
};
typedef VOS_UINT8 CNAS_HSD_AVOID_REASON_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_HSD_ABORT_REASON_ENUM
 枚举说明  : ABORT频点原因
 1.日    期   : 2015年04月16日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
enum CNAS_HSD_ABORT_REASON_ENUM
{
    CNAS_HSD_ABORT_REASON_POWER_OFF     = 0,                /* POWER_OFF*/
    CNAS_HSD_ABORT_REASON_POWER_SAVE,                        /* POWER_SAVE */
    CNAS_HSD_ABORT_REASON_DATA_CALL,                         /* DATA_CALL */

    CNAS_HSD_ABORT_REASON_BUTT
};
typedef VOS_UINT8 CNAS_HSD_ABORT_REASON_ENUM_UINT8;

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
 结构名    : CNAS_HSD_MSG_STRU
 结构说明  : HSD消息结构，状态机保存的入口消息和CACHE消息都使用此结构
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[CNAS_HSD_MAX_MSG_BUFFER_LEN];
}CNAS_HSD_MSG_STRU;

/* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
/*****************************************************************************
 结构名    : CNAS_HSD_CACHE_MSG_INFO_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastCacheMsg[CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM]; /* XSD的消息队列数组，存储的是带通用消息头的消息 */
}CNAS_HSD_CACHE_MSG_QUEUE_STRU;
 /* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

/*****************************************************************************
 结构名    : CNAS_HSD_INT_MSG_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2015年1月13日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[CNAS_HSD_MAX_INT_MSG_QUEUE_NUM]; /* HSD的消息队列数组，存放消息指针 */
}CNAS_HSD_INT_MSG_QUEUE_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_FSM_L1_MAIN_CTX_STRU
 结构说明  : 存放开机状态机的上下文信息
  1.日    期   : 2015年1月21日
    作    者   : g00256031
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurAvailableTimerCount;               /* 当前Available Timer启动次数 */
}CNAS_HSD_FSM_L1_MAIN_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_FSM_SWITCH_ON_CTX_STRU
 结构说明  : 存放开机状态机的上下文信息
  1.日    期   : 2015年1月21日
    作    者   : g00256031
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHsdReadCardFileFlg;                   /* 标记卡文件是否读取完成 */
    VOS_UINT8                           aucReserved[4];
}CNAS_HSD_FSM_SWITCH_ON_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_FSM_SYS_ACQ_CTX_STRU
 结构说明  : 存放SYS ACQ状态机的上下文信息
  1.日    期   : 2015年1月21日
    作    者   : g00256031
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucAbortFlg;         /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    CNAS_HSD_ABORT_REASON_ENUM_UINT8                        enAbortReason;      /* 当前abort场景 */
    VOS_UINT8                                               aucRsved[2];
}CNAS_HSD_FSM_SYS_ACQ_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_FSM_Inter_Sys_CTX_STRU
 结构说明  : 存放Inter Sys状态机的上下文信息
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucAbortFlg;         /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    CNAS_HSD_ABORT_REASON_ENUM_UINT8                        enAbortReason;      /* 当前abort场景 */
    VOS_UINT8                                               aucRsved[2];
}CNAS_HSD_FSM_INTER_SYS_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建
 2.日    期   : 2015年06月03日
   作    者   : z00316370
   修改内容   : 增加异系统上下文信息
*****************************************************************************/
typedef union
{
    CNAS_HSD_FSM_L1_MAIN_CTX_STRU       stL1MainCtx;
    CNAS_HSD_FSM_SWITCH_ON_CTX_STRU     stSwitchOnCtx;
    CNAS_HSD_FSM_SYS_ACQ_CTX_STRU       stSysAcqCtx;
    CNAS_HSD_FSM_INTER_SYS_CTX_STRU     stInterSysCtx;
}CNAS_HSD_FSM_EXTRA_CTX_UNION;

/*****************************************************************************
 结构名    : CNAS_HSD_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId;

    /* 上层状态机标识 */
    CNAS_HSD_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* 上层状态机入口消息类型 */
    VOS_UINT32                          ulParentEventType;

    /* 当前状态 */
    VOS_UINT32                          ulState;

    /* 入口消息MSGID和内容  */
    CNAS_HSD_MSG_STRU                   stEntryMsg;

    /* 状态机数据 */
    CNAS_HSD_FSM_EXTRA_CTX_UNION        unFsmCtx;
}CNAS_HSD_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_FSM_STACK_STRU
 结构说明  : 状态机栈描述结构
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT16                          usStackPopFlg;                          /* 当前栈pop标志 */
    CNAS_HSD_FSM_CTX_STRU               astFsmStack[CNAS_HSD_MAX_FSM_STACK_DEPTH];  /* 状态机栈的深度 */
}CNAS_HSD_FSM_STACK_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_1X_SYSTEM_INFO_STRU
 结构说明  : 1X系统信息
  1.日    期   : 2014年12月16日
    作    者   : g00256031
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_HSD_1X_SYSTEM_STATUS_ENUM_UINT32       enStatus;                       /* 指示当前1X系统是否有效 */
    CNAS_PRL_1X_SYSTEM_STRU                     st1xSys;                        /* 存放当前1X系统信息 */
}CNAS_HSD_1X_SYSTEM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_EVDO_MRU_LIST_STRU
 结构说明  : hrpd系统MRU结构体
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCurrMruNum;                           /* 指示当前MRU个数 */
    VOS_UINT8                           aucRcv[3];
    CNAS_PRL_HRPD_SYSTEM_STRU           astHrpdSys[CNAS_HSD_MAX_MRU_SYS_NUM];   /* 存放MRU信息 */
}CNAS_HSD_HRPD_MRU_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_AVOID_FREQ_INFO_STRU
 结构说明  : hrpd系统avoid表项信息
 1.日    期   : 2015年01月06日
   作    者   : x00306642
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_HSD_AVOID_ITEM_USED_FALG_ENUM_UINT32               enUsedFlag;                 /* 使用标志 */
    VOS_UINT32                                              ulStartSlice;               /* 起始slice */
    VOS_UINT32                                              ulExpiredSliceNum;          /* 到期的slice个数 */
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stAvoidFreq;
}CNAS_HSD_AVOID_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_AVOID_FREQ_LIST_STRU
 结构说明  : hrpd系统avoid表信息
 1.日    期   : 2015年01月06日
   作    者   : x00306642
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAvoidItemUsedNum;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucCounter[CNAS_HSD_AVOID_REASON_MAX];
    CNAS_HSD_AVOID_FREQ_INFO_STRU       astAvoidFreqInfo[CNAS_HSD_MAX_AVOID_FREQ_NUM];
}CNAS_HSD_AVOID_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_SUBNET_STRU
 结构说明  : 只存放subnet的结构体
 1.日    期   : 2015年01月06日
   作    者   : x00306642
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSubnet[CNAS_PRL_BYTES_IN_SUBNET];
}CNAS_HSD_SUBNET_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HRPD_SYS_REC_ITEM_STRU
 结构说明  : 系统表中HRPD项信息
 1.日    期   : 2014年12月10日
   作    者   : g00256031
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usAcqIndex;         /* 此系统记录指向的ACQ表的Index */
    VOS_UINT16                                              usSysIndex;         /* 此HRPD系统记录在系统表中的Index */
    VOS_UINT8                                               ucPrioLevel;        /* 指示HRPD的优先级，取值从1开始 */
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enPrefNegSys;       /* 此系统是否为negative或preferred */
    VOS_UINT8                                               aucRcv[2];
}CNAS_HSD_HRPD_SYS_REC_ITEM_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HRPD_SYS_LIST_STRU
 结构说明  : 系统表中HRPD项表的信息
 1.日    期   : 2014年12月10日
   作    者   : c00299064
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHrpdSysNum;                           /* 有效的HRPD系统信息个数 */
    VOS_UINT8                           aucRcv[2];
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU    *pstHrpdSysItem;                         /* 指向存放HRPD系统记录内存的指针 */
}CNAS_HSD_HRPD_SYS_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU
 结构说明  : HRPD搜网表项信息
 1.日    期   : 2014年12月10日
   作    者   : g00256031
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPrioLevel;        /* 此频点的优先级，从0开始优先级逐渐降低 */
    CNAS_HSD_FREQ_TYPE_INDICATION_ENUM_UINT8                enFreqType;         /* 频点类型，目前用于区分是否为MRU频点 */
    VOS_UINT8                                               aucRsv[2];
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;             /* 频点信息 */
}CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU
 结构说明  : HRPD搜网表信息
 1.日    期   : 2014年12月10日
   作    者   : g00256031
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalFreqNum;                         /* 全部频点个数，对于整个申请空间大小 */
    VOS_UINT16                          usAvailFreqNum;                         /* 有效的频点个数 */
    VOS_UINT16                          usCurrIndex;                            /* 指向当前频点的索引 */
    VOS_UINT8                           ucLowPrioLevel;                         /* 整个频点列表的最低优先级值 */
    VOS_UINT8                           ucRsv;
    CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU  *pstScanFreqItem;                        /* 指向存放HRPD频点信息内存的指针 */
}CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_CTX_STRU
 结构说明  : CNAS HSD 模块运行上下文
 1.日    期   : 2015年1月12日
   作    者   : d00212987
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucChanNum;
    VOS_UINT8                                               aucReseve[3];
    CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU                    aulChannel[CAS_CNAS_HRPD_MAX_REDIRECT_CH_NUM]; /**< Number of frequencies included in list */
} CNAS_HSD_REDIRECTION_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_SYSTEM_ACQUIRE_FREQ_INFO_STRU
 结构说明  : 高优先级搜网频点信息
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU              astFreq;             /* 存放HRPD的频点信息 */
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU             stHrpdSysItem;       /* 高优先级网对应的HRPD系统信息 */
} CNAS_HSD_SYSTEM_ACQUIRE_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HIGHPRIORITY_STRU
 结构说明  : 高优先级搜网频点信息列表
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucFreqNum;                                      /* 频点个数 */
    VOS_UINT8                                   aucReserved[3];
    CNAS_HSD_SYSTEM_ACQUIRE_FREQ_INFO_STRU      astFreqInfo[CNAS_HSD_MAX_PREF_SUBNET_NUM];     /* 频点信息列表 */
} CNAS_HSD_HIGHPRIORITY_STRU;


/*****************************************************************************

 结构名    : CNAS_HSD_OOC_CTX_INFO_STRU
 结构说明  : OOC上下文信息
 1.日    期   : 2015年1月13日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucWaitSearchFlag;           /* OOC等待搜索标志，即在MRU0搜索时，OOC定时器到期 */
    VOS_UINT8                                               ucCurrentPhase;             /* 记录当前搜索阶段 */
    VOS_UINT16                                              usCurrentTimes;             /* 记录在当前阶段已经搜索次数 */
    VOS_UINT8                                               ucSceneSetFlag;
    VOS_UINT8                                               aucReseve[3];
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enOocSearchScene;
}CNAS_HSD_OOC_CTX_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_OOC_TIMER_INFO_STRU
 结构说明  : OOC搜网定时器信息
 1.日    期   : 2015年1月13日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}CNAS_HSD_OOC_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_OOC_CONFIG_INFO_STRU
 结构说明  : OOC搜网调度信息, 所有信息源与NV配置
 1.日    期   : 2015年1月13日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucMru0SearchTimerLen;       /* 搜索MRU0时长 */
    VOS_UINT8                                               ucPhaseNum;                 /* 搜索步长数目 */
    VOS_UINT8                                               ucRsv[2];
    CNAS_HSD_OOC_TIMER_INFO_STRU                            astOocTimerInfo[CNAS_HSD_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_HSD_OOC_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_OOC_SCHEDULE_INFO_STRU
 结构说明  : out of cell相关信息
 1.日    期   : 2015年1月13日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_HSD_OOC_CTX_INFO_STRU                              stOocCtxInfo;
    CNAS_HSD_OOC_CONFIG_INFO_STRU                           stConfigInfo;               /* 保存OOC场景下，搜网配置信息 */
}CNAS_HSD_OOC_SCHEDULE_INFO_STRU;

/*****************************************************************************

 枚举名    : CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM
 枚举说明  : HRPD系统是否有效
 1.日    期   : 2015年1月12日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
enum CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM
{
    CNAS_HSD_HRPD_SYSTEM_UNAVAILABLE = 0,
    CNAS_HSD_HRPD_SYSTEM_AVAILABLE,
    CNAS_HSD_HRPD_SYSTEM_STATUS_BUTT,
};

typedef VOS_UINT32 CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32;

/*****************************************************************************
 结构名    : CNAS_HSD_CAMPED_SYS_INFO_STRU
 结构说明  : 驻留成功的系统信息
 1.日    期   : 2015年1月12日
   作    者   : d00212987
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32                 enStatus;
    CNAS_PRL_HRPD_SYSTEM_STRU                               stCampedHrpdSysInfo;
}CNAS_HSD_HRPD_SYSTEM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HISTORY_SYS_LIST_STRU
 结构说明  : 开机后 驻留成功的系统信息
 1.日    期   : 2015年1月12日
   作    者   : x00306642
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalNum;
    CNAS_PRL_HRPD_SYSTEM_STRU           stCampedHrpdSysInfo[CNAS_HSD_HRPD_ACQED_SUCC_SYS_MAX_NUM];
}CNAS_HSD_HISTORY_SYS_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU
 结构说明  : 系统连续丢网记录
 1.日    期   : 2015年06月04日
   作    者   : z00316370
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    CNAS_PRL_HRPD_SYSTEM_STRU           stHrpdSys;
    VOS_UINT32                          ulLastRecSlice;
    VOS_UINT8                           ucNetwkLostCnt;
    VOS_UINT8                           aucResv[3];
}CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU
 结构说明  : CNAS HSD 锁频信息
 1.日    期   : 2015年07月14日
   作    者   : x00306642
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucFreqLockMode;
    VOS_UINT8                                       aucReserve[1];
    VOS_UINT16                                      usHrpdBandClass;
    VOS_UINT16                                      usHrpdFreq;
    VOS_UINT16                                      usHrpdPn;
}CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU;


/*****************************************************************************
 结构名    : CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU
 结构说明  : 最匹配的HRPD系统的系统表索引值
 1.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIndexNum;
    VOS_UINT8                           aucResv[2];
    VOS_UINT16                          ausMatchedHrpdSysIndexList[CNAS_PRL_MAX_MATCHED_HRPD_SYSTEM_NUM];                         /* 和搜到的HRPD系统最匹配的sys record index */
}CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU;


/*****************************************************************************
 结构名    : CNAS_HSD_SYSTEM_ACQUIRE_CTRL_STRU
 结构说明  : hrpd搜网控制结构体
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;         /* 区分混合和非混合模式 */
    CNAS_HSD_1X_SYSTEM_INFO_STRU                            st1xSysInfo;        /* 保存1X系统信息 */
    CNAS_HSD_HRPD_MRU_LIST_STRU                             stMruList;          /* 存放MRU内容 */
    CNAS_HSD_AVOID_FREQ_LIST_STRU                           stAvoidFreqList;    /* avoid表 */
    CNAS_HSD_HRPD_SYS_LIST_STRU                             stSysRecList;       /* HRPD系统记录表 */
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                       stScanFreqList;     /* HRPD频点表 */
    CNAS_HSD_REDIRECTION_STRU                               stRedirection;      /* 重定向频点信息 */
    CNAS_HSD_HIGHPRIORITY_STRU                              stHighPriority;     /* 高优先级频点信息 */
    CNAS_HSD_HISTORY_SYS_LIST_STRU                          stHistorySysList;
    CNAS_HSD_HRPD_SYSTEM_INFO_STRU                          stHrpdSysInfo;      /* Hrpd系统驻留状态信息 */
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                         stOocScheduleInfo;  /* OOC调度信息 */
    CNAS_PRL_HRPD_SYSTEM_STRU                               stCasOhmHrpdSys;    /* overhead上报的频点信息 */
    CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU                   stNetwkLostSysRec;  /* 连续丢网的系统记录 */
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU                       stFreqLockPara;     /* 锁频的参数信息 */
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stSyncFreq;         /* sync到的系统频点 */
    CNAS_HSD_1X_SYSTEM_INFO_STRU                            stHrpdMatched1xSysInfo;        /* 保存1X系统信息 */
    CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU               stMatchedHrpdSysIndexList;      /* 匹配的HRPD系统索引集 */

}CNAS_HSD_SYSTEM_ACQUIRE_CTRL_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_SYSTEM_ASSIST_INFO_STRU
 结构说明  : 系统辅助信息记录
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enNoRfScene;
    CNAS_HSD_AT_STATUS_ENUM_UINT32                          enATStatus;         /* AT当前状态 */
    CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32                 enSessionNegStatus; /* 当前session neg状态 */
    VOS_UINT8                                               ucHrpdRfAvailFlg;
    VOS_UINT8                                               ucMru0RelateFlg;
    VOS_UINT8                                               ucSysCfgFlg;
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8                        enNoRf1XUeStatus;
    VOS_UINT32                                              ulUeSupportedBand;
    VOS_UINT8                                               ucIsAbnormalLostFLg;   /* 指示当前是否为IDLE态收到CAS的abnormal lost */
    VOS_UINT8                                               aucResv[3];
}CNAS_HSD_SYSTEM_ASSIST_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_TEST_CONFIG_STRU
 结构说明  : CNAS HSD 测试控制
 1.日    期   : 2015年10月20日
   作    者   : z00316370
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReadNvPrlDirectly;
    VOS_UINT8                           ucReadDefaultPrl;        /* 读取Default Prl */
    VOS_UINT8                           ucNoCardModeCfgFlg;
    VOS_UINT8                           ucReserve;
}CNAS_HSD_TEST_CONFIG_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_CTX_STRU
 结构说明  : CNAS HSD 模块运行上下文
 1.日    期   : 2014年12月16日
   作    者   : g00256031
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        CNAS HSD状态机状态及其状态栈
    **************************************************************************/
    CNAS_HSD_FSM_CTX_STRU               stCurFsm;                               /* 状态机当前的状态机数组 */
    CNAS_HSD_FSM_STACK_STRU             stFsmStack;                             /* 状态机的状态机栈数组   */

    CNAS_HSD_CACHE_MSG_QUEUE_STRU       stCacheMsgQueue;                        /* CNAS HSD缓存消息队列 */

    CNAS_HSD_INT_MSG_QUEUE_STRU         stIntMsgQueue;                          /* CNAS 内部消息队列 */

    CNAS_HSD_SYSTEM_ACQUIRE_CTRL_STRU   stSysAcqCtrl;                           /* 搜网控制信息 */

    CNAS_HSD_SYSTEM_ASSIST_INFO_STRU    stSysAssistInfo;                        /* 系统辅助信息 */

    CNAS_HSD_TEST_CONFIG_STRU           stTestConfig;                           /* 读默认PRL控制 */

}CNAS_HSD_CTX_STRU;


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

extern VOS_VOID CNAS_HSD_InitCurrFsmCtx(
    CNAS_HSD_FSM_CTX_STRU              *pstCurrFsmCtx
);

extern VOS_VOID CNAS_HSD_InitFsmStackCtx(
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack
);

/* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, begin */
extern VOS_VOID CNAS_HSD_InitCacheMsgQueue(
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue,
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
);
/* Modified by d00212987 for CNAS内存裁剪, 2015-09-18, end */

extern VOS_VOID CNAS_HSD_InitSysRecList(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysRecList
);

extern VOS_VOID CNAS_HSD_InitScanChanList(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanChanList
);

extern VOS_VOID CNAS_HSD_InitSystemAcquireCtrl(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_SYSTEM_ACQUIRE_CTRL_STRU  *pstSysAcqCtrl
);

extern VOS_VOID CNAS_HSD_InitSystemAssistInfo(
    CNAS_HSD_SYSTEM_ASSIST_INFO_STRU   *pstSysAssistInfo
);

extern VOS_VOID CNAS_HSD_InitFsmCtx_L1Main(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitFsmCtx_SwitchOn(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitFsmCtx_SysAcq(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitCtx(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
);

extern VOS_VOID  CNAS_HSD_LoadSubFsm(
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm
);

extern VOS_VOID CNAS_HSD_PushFsm(
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack,
    CNAS_HSD_FSM_CTX_STRU              *pstNewFsm
);

extern VOS_VOID CNAS_HSD_PopFsm(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitFsmL2(
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId
);

extern VOS_VOID CNAS_HSD_QuitFsmL2(VOS_VOID);

extern CNAS_HSD_CTX_STRU* CNAS_HSD_GetHsdCtxAddr(VOS_VOID);

extern CNAS_HSD_FSM_STACK_STRU* CNAS_HSD_GetFsmStackAddr(VOS_VOID);

extern CNAS_HSD_FSM_CTX_STRU* CNAS_HSD_GetCurFsmAddr(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_GetFsmTopState(VOS_VOID);

extern NAS_FSM_DESC_STRU* CNAS_HSD_GetCurFsmDesc(VOS_VOID);

extern VOS_UINT16 CNAS_HSD_GetFsmStackDepth(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);

extern VOS_UINT16 CNAS_HSD_GetFsmStackPopFlg(VOS_VOID);

extern CNAS_HSD_CACHE_MSG_QUEUE_STRU* CNAS_HSD_GetCacheMsgAddr(VOS_VOID);

extern VOS_VOID CNAS_HSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

extern VOS_UINT32  CNAS_HSD_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

extern VOS_VOID CNAS_HSD_ClearCacheMsg(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 CNAS_HSD_GetNextCachedMsg(
    CNAS_HSD_MSG_STRU                  *pstEntryMsg
);

extern VOS_UINT32 CNAS_HSD_GetCacheMsgNum(VOS_VOID);

extern VOS_VOID  CNAS_HSD_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

extern CNAS_HSD_MSG_STRU* CNAS_HSD_GetCurrFsmEntryMsgAddr(VOS_VOID);

extern VOS_VOID CNAS_HSD_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern CNAS_HSD_FSM_ID_ENUM_UINT32 CNAS_HSD_GetCurrFsmId(VOS_VOID);

extern CNAS_HSD_INT_MSG_QUEUE_STRU* CNAS_HSD_GetIntMsgQueueAddr(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitInternalBuffer(
    CNAS_HSD_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

extern VOS_VOID  CNAS_HSD_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

extern VOS_UINT8 *CNAS_HSD_GetNextIntMsg(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetIntMsgNum(VOS_VOID);

extern CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
);

extern VOS_VOID CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
);

extern CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 CNAS_HSD_GetModeType(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetSysModeType(CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 enModeType);

extern CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_Get1xSystemInfo(VOS_VOID);

extern CNAS_HSD_HRPD_MRU_LIST_STRU* CNAS_HSD_GetMruList(VOS_VOID);

extern VOS_VOID CNAS_HSD_UpdateMru0(CNAS_PRL_HRPD_SYSTEM_STRU *pstCurSysId);

extern VOS_UINT8 CNAS_HSD_GetMruListNum(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_GetMru0SysId(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstMru0SysId
);

extern CNAS_HSD_HRPD_SYS_LIST_STRU* CNAS_HSD_GetSysRecListAddr(VOS_VOID);

extern VOS_UINT16 CNAS_HSD_GetSysRecItemNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetSysRecListIndex(
    VOS_UINT16                          usHrpdSysNum
);
extern CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU* CNAS_HSD_GetScanFreqListAddr(VOS_VOID);

extern VOS_UINT16 CNAS_HSD_GetScanFreqNum(VOS_VOID);

extern VOS_UINT16 CNAS_HSD_GetCurScanFreqIndex(VOS_VOID);

extern VOS_UINT16 CNAS_HSD_GetScanListAvailFreqNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetCurScanFreqIndex(
    VOS_UINT16                          usCurScanIndex
);

extern CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_HSD_GetScanFreqByIndex(
    VOS_UINT16                          usFreqIndex
);

extern CNAS_HSD_REDIRECTION_STRU* CNAS_HSD_GetRedirectionFreqAddr(VOS_VOID);

extern VOS_UINT16 CNAS_HSD_GetRedirectionFreqNum(VOS_VOID);

extern CNAS_HSD_OOC_CONFIG_INFO_STRU *CNAS_HSD_GetOocScheduleConfigInfo(VOS_VOID);

extern CNAS_HSD_OOC_SCHEDULE_INFO_STRU *CNAS_HSD_GetOocScheduleInfo(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitOocScheduleInfo(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
);

extern VOS_VOID CNAS_HSD_InitOocCtxInfo(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetOocWaitSearchFlag(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag);

extern CNAS_HSD_AVOID_FREQ_LIST_STRU* CNAS_HSD_GetAvoidFreqListAddr(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetAvoidFreqListUsedNum(VOS_VOID);

extern CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32 CNAS_HSD_GetSessionNegStatus(VOS_VOID);

extern VOS_VOID CNAS_HSD_SaveSessionNegStatus(
    CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32                 enSessionNegStatus
);

extern CNAS_HSD_AT_STATUS_ENUM_UINT32 CNAS_HSD_GetATStatus(VOS_VOID);

extern VOS_VOID CNAS_HSD_SaveATStatus(
    CNAS_HSD_AT_STATUS_ENUM_UINT32     enCasStatus
);

extern CNAS_HSD_HISTORY_SYS_LIST_STRU* CNAS_HSD_GetHistorySysList(VOS_VOID);

extern VOS_VOID CNAS_HSD_UpdateHistorySysList(CNAS_PRL_HRPD_SYSTEM_STRU *pstCurrSystem);


extern CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 CNAS_HSD_GetHrpdSysStatus(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 enStatus);

extern CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCampedHrpdSystemInfo(VOS_VOID);

extern VOS_VOID CNAS_HSD_UpdateHrpdSysInfo(CNAS_PRL_HRPD_SYSTEM_STRU *pstSystem);

extern VOS_VOID CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 enNoRfScene);

extern CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetNoRfScene(VOS_VOID);

extern VOS_VOID CNAS_HSD_ClearHrpdSysInfo(VOS_VOID);

extern VOS_UINT8   CNAS_HSD_SetAbortFlg_SysAcq(
    VOS_UINT8                           ucFlg,
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
);

extern VOS_UINT8 CNAS_HSD_GetAbortFlg_SysAcq(VOS_VOID);

extern CNAS_HSD_ABORT_REASON_ENUM_UINT8 CNAS_HSD_GetAbortReason_SysAcq(VOS_VOID);

extern CNAS_HSD_HIGHPRIORITY_STRU* CNAS_HSD_GetHighPriorityFreqAddr(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetHighPriorityFreqNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitHighPriorityFreq(CNAS_HSD_HIGHPRIORITY_STRU* pstHighFreq);

extern CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCasOhmHrpdSysAddr(VOS_VOID);

extern VOS_VOID CNAS_HSD_SortCacheMsgInMsgQueue(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetCacheMsgPriority(
    VOS_UINT32                          ulEventType
);

extern VOS_VOID CNAS_HSD_InitFsmCtx_InterSys(VOS_VOID);

extern VOS_UINT8   CNAS_HSD_SetAbortFlg_InterSys(
    VOS_UINT8                           ucFlg,
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
);

extern VOS_UINT8 CNAS_HSD_GetAbortFlg_InterSys(VOS_VOID);

extern CNAS_HSD_ABORT_REASON_ENUM_UINT8 CNAS_HSD_GetAbortReason_InterSys(VOS_VOID);

extern CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU* CNAS_HSD_GetNetwkLostSysRec(VOS_VOID);

extern CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_HSD_GetFreqLockAddr(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetFreqLockMode(VOS_VOID);

extern VOS_UINT8 CNAS_HSD_GetHrpdRfAvailFlg(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetHrpdRfAvailFlg(VOS_UINT8 ucHrpdRfAvailFlg);

extern VOS_UINT8 CNAS_HSD_GetMru0RelateFlg(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetMru0RelateFlg(VOS_UINT8 ucMru0RelateFlg);

extern VOS_VOID CNAS_HSD_InitCFreqLockValue(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_GetUeSupportedBandClass(VOS_VOID);

extern CNAS_HSD_TEST_CONFIG_STRU* CNAS_HSD_GetTestConfig(VOS_VOID);
CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_HSD_GetNoRf1XUeStatus(VOS_VOID);

VOS_VOID CNAS_HSD_SetNoRf1XUeStatus(CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 enStatus);

extern CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_GetScanListMatched1xSystemInfo(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetSysCfgFlag(VOS_UINT8 ucIsSysCfg);

extern VOS_UINT8 CNAS_HSD_GetSysCfgFlag(VOS_VOID);

extern CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU* CNAS_HSD_GetMatchedHrpdSysIndexListAddr(VOS_VOID);

extern VOS_VOID CNAS_HSD_InitMatchedHrpdSysIndexList(VOS_VOID);

extern VOS_UINT8   CNAS_HSD_IsCurAbortFlgSet_SysAcq(
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
);

extern VOS_VOID CNAS_HSD_SetAbnormalLostFlag(VOS_UINT8 ucIsAbnormalLost);

extern VOS_UINT8 CNAS_HSD_GetAbnormalLostFlag(VOS_VOID);

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

#endif /* end of CnasHsdCtx.h */
