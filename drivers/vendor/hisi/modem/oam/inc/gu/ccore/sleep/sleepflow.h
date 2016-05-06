/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SleepFlow.h
  版 本 号   : 初稿
  作    者   : zuowen
  生成日期   : 2005年3月7日
  最近修改   :
  功能描述   : SleepFlow.c 的头文件
  函数列表   :
  修改历史   :

  1.日    期   : 2005年3月7日
    作    者   : zuowen
    修改内容   : 创建文件

  2.日    期   : 2006年4月13日
    作    者   : w45442
    修改内容   : 修改问题单A32D03034

******************************************************************************/
#ifndef __SLEEPFLOW_H__
#define __SLEEPFLOW_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"
#include "sleepsleep.h"
#include "phyoaminterface.h"
#include "OmApi.h"
#include "oam_cphy_interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BBP_AWAKE_BIT                           0x01

#define WSLEEP_32K_TO_64M_TYPE_BIT              0       /*DRX唤醒后时钟切换到61.44M中断*/
#define WSLEEP_64M_TO_32K_TYPE_BIT              1       /*sleep*/

#define BBP_DRX_INT_SLICE_COUNT                 800       /*BBP DRX INT SLICE DELAY COUNT*/

#define SLEEP_SLOT_LEN                          15      /*W每帧包含15个SLOT*/
#define SLEEP_SFN_CYCLE_LEN                     (4096*SLEEP_SLOT_LEN) /*SFN范围为12bit，每次轮回4096*/

#define SLEEP_WAKE_DELAY                        2       /*增加延迟防止函数执行中正常唤醒已经来到*/
#define SLEEP_WAKE_INTERVAL                     30      /*强制唤醒时刻与正常唤醒时刻间隔的最小值*/
#define SLEEP_WAKE_BASE_FRM_PROTECT_CHIP        (38200) /* 在绝对计时器先后判断时避开帧头前的CHIP */
#define SLEEP_WAKE_BASE_FRM_PROTECT_VALUE       (500)
#define SLEEP_WAKE_BBP_POS_PROTECT_SLICE        (330)   /* BBP保护流程超时门限,10ms */

/* GU下支持模式的BUTT值 */
#define SLEEP_GU_MODE_TYPE_BUTT                 (VOS_RATMODE_BUTT)

/* C下支持模式的BUTT值 */
#define SLEEP_C_MODE_TYPE_BUTT                  (VOS_RATMODE_BUTT)

#define BBP_SLEEP_32K_CLOCK_SWITCH_IND          (4)
#define BBP_SLEEP_WAKE_IND                      (5)
#define BBP_SLEEP_NORMAL_CLOCK_SWITCH_IND       (6)
#define SLEEP_WAKE_MASTER_GU_IND                (7)
#define SLEEP_WAKE_SLAVE_GU_IND                 (8)
#define BBE16_SLEEP_SLEEP_IND                   (0x1001)
#define BBE16_SLEEP_AWAKE_IND                   (0x1002)
#define BBE16_SLEEP_RESUME_IND                  (0x1003)
#define BBE16_SLEEP_MASTER_WAKE_IND             (0x1004)
#define BBE16_SLEEP_SLAVE_WAKE_IND              (0x1005)
#define BBE16_SLEEP_TRACE_STACK_IND             (0x1011)

#define BBP_ERROR_VALUE                         (0xDEADBEEF)

#define SLEEP_TRACK_RECORD_NUM                  (100)

#define SLEEP_INFO_RESET_ENABLE                 (0x5A5A5A5A)

#define SLEEP_BBP_ERROR_TIMEOUT                 (30000)

#define SLEEP_IPC_TIMEOUT                       (2)   /* 20ms超时 */

#define SLEEP_SLAVE_MSG_TRACK_NUM               (20)

#define SLEEP_NOTIFY_MSG_TRACK_NUM              (20)

#define SLEEP_IPC_INT_DELAY_SLICE               (7)

#define SLEEP_DEVICE_POWUP(enModemId, enMode, enCommMode, enChannel) \
    { \
        mdrv_pm_pwrup((PWC_COMM_MODE_E)enMode, enCommMode, (PWC_COMM_MODEM_E)enModemId, (PWC_COMM_CHANNEL_E)enChannel); \
        if ( VOS_NULL_PTR != g_pstSleepDeviceState ) \
        { \
            g_pstSleepDeviceState->aulDevicePwState[enModemId][enMode][enCommMode][enChannel]  = PWRCTRL_COMM_ON; \
            g_pstSleepDeviceState->aulDeviceUpSlice[enModemId][enMode][enCommMode][enChannel]  = OM_GetSlice(); \
        } \
        \
    } \

#define SLEEP_DEVICE_POWDOWN(enModemId, enMode, enCommMode, enChannel) \
    { \
        mdrv_pm_pwrdown((PWC_COMM_MODE_E)enMode, enCommMode, (PWC_COMM_MODEM_E)enModemId, (PWC_COMM_CHANNEL_E)enChannel); \
        if ( VOS_NULL_PTR != g_pstSleepDeviceState ) \
        { \
            g_pstSleepDeviceState->aulDevicePwState[enModemId][enMode][enCommMode][enChannel]   = PWRCTRL_COMM_OFF; \
            g_pstSleepDeviceState->aulDeviceDownSlice[enModemId][enMode][enCommMode][enChannel] = OM_GetSlice(); \
        } \
        \
    } \

#define SLEEP_DEVICEPLL_POWUP(enModemId, enMode, enCommMode, enChannel) \
    { \
        mdrv_pm_enable_pllclk((PWC_COMM_MODE_E)enMode, enCommMode, (PWC_COMM_MODEM_E)enModemId, (PWC_COMM_CHANNEL_E)enChannel); \
        if ( VOS_NULL_PTR != g_pstSleepDeviceState ) \
        { \
            g_pstSleepDeviceState->aulPllPwState[enModemId][enMode][enCommMode][enChannel]  = PWRCTRL_COMM_ON; \
            g_pstSleepDeviceState->aulPLLUpSlice[enModemId][enMode][enCommMode][enChannel]  = OM_GetSlice(); \
        } \
        \
    } \


#define SLEEP_DEVICEPLL_POWDOWN(enModemId, enMode, enCommMode, enChannel) \
    { \
        mdrv_pm_disable_pllclk((PWC_COMM_MODE_E)enMode, enCommMode, (PWC_COMM_MODEM_E)enModemId, (PWC_COMM_CHANNEL_E)enChannel); \
        if ( VOS_NULL_PTR != g_pstSleepDeviceState ) \
        { \
            g_pstSleepDeviceState->aulPllPwState[enModemId][enMode][enCommMode][enChannel]     = PWRCTRL_COMM_OFF; \
            g_pstSleepDeviceState->aulPLLDownSlice[enModemId][enMode][enCommMode][enChannel]   = OM_GetSlice(); \
        } \
        \
    } \

/* 通道参数 */
#define SLEEP_ABB_CHAN(enMode)          (g_stChannelModeProfile.astPara[g_stChannelModeProfileId.uwProfileId].stModeBasicPara[enMode].uhwABBSwitch)
#define SLEEP_RF_CHAN(enMode)           (g_stChannelModeProfile.astPara[g_stChannelModeProfileId.uwProfileId].stModeBasicPara[enMode].uhwRFSwitch)
#define SLEEP_TCXO_CHAN(enMode)         (g_stChannelModeProfile.astPara[g_stChannelModeProfileId.uwProfileId].stModeBasicPara[enMode].uhwTCXOSwitch)
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
#define SLEEP_RFCLK_CHAN(enMode)        (g_stChannelModeProfile.astPara[g_stChannelModeProfileId.uwProfileId].stModeBasicPara[enMode].uhwRfClk)
#endif

#define SLEEP_DEBUG

#ifdef SLEEP_DEBUG

#define SLEEP_ISR_RECORD(ulMsgId, enMode) \
    if (VOS_NULL_PTR != g_pstSleepTrackRecord) \
    { \
        g_pstSleepTrackRecord->astIsrRecord[g_pstSleepTrackRecord->ulIsrIndex].usMsgId    = (VOS_UINT16)ulMsgId; \
        g_pstSleepTrackRecord->astIsrRecord[g_pstSleepTrackRecord->ulIsrIndex].usModeType = (VOS_UINT16)enMode; \
        g_pstSleepTrackRecord->astIsrRecord[g_pstSleepTrackRecord->ulIsrIndex].ulSlice    = OM_GetSlice(); \
        \
        g_pstSleepTrackRecord->ulIsrIndex++; \
        /* 达到末尾需要翻转*/ \
        if (SLEEP_TRACK_RECORD_NUM == g_pstSleepTrackRecord->ulIsrIndex) \
        { \
            g_pstSleepTrackRecord->ulIsrIndex = 0; \
        } \
    } \

#define SLEEP_MSG_RECORD(ulMsgId, enMode, StartSlice) \
    if (VOS_NULL_PTR != g_pstSleepTrackRecord) \
    { \
        g_pstSleepTrackRecord->astMsgRecord[g_pstSleepTrackRecord->ulMsgIndex].usMsgId      = (VOS_UINT16)ulMsgId; \
        g_pstSleepTrackRecord->astMsgRecord[g_pstSleepTrackRecord->ulMsgIndex].usModeType   = (VOS_UINT16)enMode; \
        g_pstSleepTrackRecord->astMsgRecord[g_pstSleepTrackRecord->ulMsgIndex].ulStartSlice = StartSlice; \
        g_pstSleepTrackRecord->astMsgRecord[g_pstSleepTrackRecord->ulMsgIndex].ulEndSlice   = OM_GetSlice(); \
        \
        g_pstSleepTrackRecord->ulMsgIndex++; \
        /* 达到末尾需要翻转*/ \
        if (SLEEP_TRACK_RECORD_NUM == g_pstSleepTrackRecord->ulMsgIndex) \
        { \
            g_pstSleepTrackRecord->ulMsgIndex = 0; \
        } \
    } \

#define SLEEP_NOR_STATE_TRACK(enMode, enType) \
    if (VOS_NULL_PTR != g_pstSleepNormalState) \
    { \
        g_pstSleepNormalState->astRecordItem[enMode][enType].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][enType].ulCount%SLEEP_RECORD_TRACK_NUM] = OM_GetSlice(); \
        g_pstSleepNormalState->astRecordItem[enMode][enType].ulCount++; \
    } \

#define SLEEP_BBP_SWITCH_INT_DELAY_RECORD(ulDeltaSlice) \
    if (VOS_NULL_PTR != g_pstSleepDeviceState) \
    { \
        g_pstSleepDeviceState->stDelayRecord.astRecord[g_pstSleepDeviceState->stDelayRecord.ulCount].ulDeltaSlice = ulDeltaSlice; \
        g_pstSleepDeviceState->stDelayRecord.astRecord[g_pstSleepDeviceState->stDelayRecord.ulCount].ulSlice      = OM_GetSlice(); \
        \
        g_pstSleepDeviceState->stDelayRecord.ulCount++; \
        /* 达到末尾需要翻转*/ \
        if (SLEEP_BBP_SWITCH_INT_DELAY_RECORD_MAX == g_pstSleepDeviceState->stDelayRecord.ulCount) \
        { \
            g_pstSleepDeviceState->stDelayRecord.ulCount = 0; \
        } \
    } \


#define SLEEP_WAKE_SLICE_RECORD(ulIndex) \
    /*lint -e774 -e506*/ \
    if ((VOS_NULL_PTR != g_pstSleepWakeSliceAddr) && (ulIndex < 8)) \
    /*lint +e774 +e506*/ \
    { \
        g_pstSleepWakeSliceAddr->auwCommSRStamp[ulIndex] = OM_GetSlice(); \
    } \

#define SLEEP_BBE16_NOR_STATE_TRACK(enMode, enType) \
    if (VOS_NULL_PTR != g_pstSleepBBE16NormalState) \
    { \
        g_pstSleepBBE16NormalState->astRecordItem[enMode][enType].aulSlice[g_pstSleepBBE16NormalState->astRecordItem[enMode][enType].ulCount % SLEEP_BBE16_RECORD_TRACK_NUM] = VOS_GetSlice(); \
        g_pstSleepBBE16NormalState->astRecordItem[enMode][enType].ulCount++; \
    } \

#else

#define SLEEP_ISR_RECORD(ulMsgId, enMode)
#define SLEEP_MSG_RECORD(ulMsgId, enMode, ulStartSlice) (ulStartSlice = ulStartSlice) /* for pclint
 */
#define SLEEP_NOR_STATE_TRACK(enMode, enType)

#define SLEEP_BBP_SWITCH_INT_DELAY_RECORD(ulDeltaSlice)

#define SLEEP_BBE16_NOR_STATE_TRACK(enMode, enType)

#endif

#define HPA_UART_PRINT(data)

/* 注册到SLEEP模块的PID最大个数 */
#define SLEEP_NOTIFY_STATE_REG_PID_MAX              (16)

/* 无效PID定义 */
#define SLEEP_INVALID_PID                           (0xFFFFFFFF)

/* 自然唤醒流程中，预定时钟切换中断后，最多等待多长时间再产生时钟切换中断，当前配为4096 */
#define SLEEP_BBP_HANDSHAKE_MAX_DELAY               (4096)

/* BBP握手寄存器(bit 0有效) */
#define BBP_HANDSHAKE_BIT                           (0x01)

/* 统计BBP唤醒中断发生延迟的可维可测数据中，最大的记录次数 */
#define SLEEP_BBP_SWITCH_INT_DELAY_RECORD_MAX       (100)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : SLEEP_NORMAL_STATE_TRACK_ENUM
 枚举说明  : 正常状态下轨迹流程

  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001 MSP拆分和可维可测项目新增
*****************************************************************************/
enum SLEEP_NORMAL_STATE_TRACK_ENUM
{
    SLEEP_MASTER_BBP_32K = 0,
    SLEEP_MASTER_PHY_HALT,
    SLEEP_MASTER_LP,
    SLEEP_MASTER_BBP_WAKE,
    SLEEP_MASTER_ACTIVATE_START,
    SLEEP_MASTER_ACTIVATE_END,
    SLEEP_MASTER_BBP_RESUME_START,
    SLEEP_MASTER_BBP_RESUME_END,
    SLEEP_MASTER_FORCE_WAKE,
    SLEEP_MASTER_BBP_NORMAL,
    SLEEP_MASTER_WAKE_PHY_PRE,
    SLEEP_MASTER_WAKE_PHY,
    SLEEP_SLAVE_PHY_HALT,
    SLEEP_SLAVE_LP,
    SLEEP_SLAVE_FORCE_WAKE,
    SLEEP_NORMAL_BUTT
};

/*****************************************************************************
 枚举名    : SLEEP_CHANNEL_ENUM
 枚举说明  : 通道枚举值

  1.日    期   : 2013年09月27日
    作    者   : g47350
    修改内容   :
*****************************************************************************/
enum SLEEP_CHANNEL_ENUM
{
    SLEEP_CHANNEL_ZERO = 0,
    SLEEP_CHANNEL_ONE,
    SLEEP_CHANNEL_BOTH,
};

/*****************************************************************************
 枚举名    : SLEEP_BBE16_NORMAL_STATE_TRACK_ENUM
 枚举说明  : X模正常状态下轨迹流程

  1.日    期   : 2015年09月23日
    作    者   : x00306642
    修改内容   : 可维可测
*****************************************************************************/
enum SLEEP_BBE16_NORMAL_STATE_TRACK_ENUM
{
    /* Main Track*/
    /* Halt */
    SLEEP_BBE16_HALT_INT_TRACE = 0,
    SLEEP_BBE16_HALT_START_TRACE,
    SLEEP_BBE16_HALT_END_TRACE,

    /* Normal Wake */
    SLEEP_BBE16_NORMAL_WAKE_INT_TRACE,
    SLEEP_BBE16_NORMAL_WAKE_START_TRACE,
    SLEEP_BBE16_NORMAL_WAKE_END_TRACE,

    /* Master Force Wake */
    SLEEP_BBE16_MASTER_FORCE_WAKE_REQ_TRACE,
    SLEEP_BBE16_MASTER_FORCE_WAKE_START_TRACE,
    SLEEP_BBE16_MASTER_FORCE_WAKE_END_TRACE,

    /* Slave Force Wake */
    SLEEP_BBE16_SLAVE_FORCE_WAKE_REQ_TRACE,
    SLEEP_BBE16_SLAVE_FORCE_WAKE_START_TRACE,
    SLEEP_BBE16_SLAVE_FORCE_WAKE_END_TRACE,

    /* Resume */
    SLEEP_BBE16_RESUME_INT_TRACE,
    SLEEP_BBE16_RESUME_START_TRACE,
    SLEEP_BBE16_RESUME_END_TRACE,

    /* ACT */
    SLEEP_BBE16_DEACTIVATE_START,
    SLEEP_BBE16_DEACTIVATE_END,
    SLEEP_BBE16_ACTIVATE_START,
    SLEEP_BBE16_ACTIVATE_END,

    /* Assist Track */
    /* Halt */
    SLEEP_BBE16_HALT_INT_TO_MSG_TRACE,
    SLEEP_BBE16_HALT_SMP_TRACE,
    SLEEP_BBE16_HALT_WAKE_START_TRACE,
    SLEEP_BBE16_HALT_WAKE_END_TRACE,
    SLEEP_BBE16_HALT_CPROC_1X_SLEEP_TRACE,
    SLEEP_BBE16_HALT_CPROC_HRPD_SLEEP_TRACE,

    /* Normal Wake */
    SLEEP_BBE16_NORMAL_WAKE_INT_TO_MSG_TRACE,
    SLEEP_BBE16_NORMAL_WAKE_SMP_TRACE,
    SLEEP_BBE16_NORMAL_WAKE_PROC_TRACE,

    /* Master Force Wake */
    SLEEP_BBE16_MASTER_FORCE_WAKE_SMP_TRACE,
    SLEEP_BBE16_MASTER_FORCE_WAKE_PROC_TRACE,

    /* Slave Force Wake */
    SLEEP_BBE16_SLAVE_FORCE_WAKE_SMP_TRACE,
    SLEEP_BBE16_SLAVE_FORCE_WAKE_PROC_TRACE,

    /* Resume */
    SLEEP_BBE16_RESUME_INT_TO_MSG_TRACE,
    SLEEP_BBE16_RESUME_SMP_TRACE,
    SLEEP_BBE16_RESUME_CPROC_1X_WAKEUP_TRACE,
    SLEEP_BBE16_RESUME_CPROC_HRPD_WAKEUP_TRACE,

    /* Abnormal Track */
    SLEEP_BBE16_HALT_INT_NOT_NORMAL_TRACE,
    SLEEP_BBE16_WAKE_INT_NOT_LP_TRACE,
    SLEEP_BBE16_RESUME_INT_NOT_TEMP_TRACE,
    SLEEP_BBE16_MASTER_FORCE_WAKE_MODE_ERR_TRACE,
    SLEEP_BBE16_MBX_OTHER_CHANNEL_TRACE,

    SLEEP_BBE16_NORMAL_BUTT
};

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
 结构名    : SLEEP_MODE_INFO_STRU
 结构说明  : GU模当前系统状态
*****************************************************************************/
typedef struct
{
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enSystemState;
    UPHY_OAM_WAKE_TYPE_ENUM_UINT32      enWakeType;
}SLEEP_MODE_INFO_STRU;

/*****************************************************************************
 结构名    : SLEEP_BBE16_MODE_INFO_STRU
 结构说明  : X模当前系统状态
*****************************************************************************/
typedef struct
{
    SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32    enSystemState;
    CPHY_SLEEP_TYPE_ENUM_UINT32             enCdmaSleepType;
}SLEEP_BBE16_MODE_INFO_STRU;

/*****************************************************************************
 结构名    : SLEEP_MSG_FUN_STRU
 结构说明  : 指示各消息的处理函数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;                /* 消息ID */
    Msg_Fun_Type                        pMsgFun;                /* 消息处理函数 */
}SLEEP_MSG_FUN_STRU;

/*****************************************************************************
 结构名    : SLEEP_INFO_STATE_STRU
 结构说明  : GU模定位信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulAwakeIsrSlice;
    VOS_UINT32                      ulAwakeStartSlice;
    VOS_UINT32                      ulAwakeEndSlice;
    VOS_UINT32                      ulSwitchIsrSlice;
    VOS_UINT32                      ulSwitchTaskSlice;
    VOS_UINT32                      ulWarnEventFlag;
    VOS_UINT32                      ulWarnEventCount;
    VOS_UINT32                      ulSwitchDelayType1Count;
    VOS_UINT32                      ulSwitchDelayType2Count;
    VOS_UINT32                      ulSwitchDelayType3Count;
    VOS_UINT32                      ulSwitchDelayType4Count;
    VOS_UINT32                      ulSwitchDelayType5Count;
    VOS_UINT32                      ulEndFlag;
}SLEEP_INFO_STATE_STRU;

/*****************************************************************************
 结构名    : SLEEP_ISR_MSG_STRU
 结构说明  : 中断消息体
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER
   VOS_UINT16                           usMsgId;                /* 消息ID */
   VOS_UINT16                           usReserved;             /* 保留 */
   SLEEP_MODE_ENUM_UINT32               enRatMode;              /* 上报模式 */
   VOS_UINT32                           ulSlice;                /* 中断接收时间 */
}SLEEP_ISR_MSG_STRU;

/*****************************************************************************
 结构名    : SLEEP_RECORD_ITEM_STRU
 结构说明  : 流程记录单元
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgId;                /* 消息ID */
    VOS_UINT16                          usModeType;             /* 模式类型 */
    VOS_UINT32                          ulSlice;                /* Slice值 */
}SLEEP_RECORD_ITEM_STRU;

/*****************************************************************************
 结构名    : SLEEP_RECORD_ITEM_EX_STRU
 结构说明  : 流程记录扩展单元
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgId;                /* 消息ID */
    VOS_UINT16                          usModeType;             /* 模式类型 */
    VOS_UINT32                          ulStartSlice;           /* 开始Slice值 */
    VOS_UINT32                          ulEndSlice;             /* 结束Slice值 */
}SLEEP_RECORD_ITEM_EX_STRU;

/*****************************************************************************
 结构名    : SLEEP_TRACK_RECORD_STRU
 结构说明  : 保存SLEEP中断和消息流程记录
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsrIndex;             /* 中断记录索引 */
    VOS_UINT32                          ulMsgIndex;             /* 消息记录索引 */
    SLEEP_RECORD_ITEM_STRU              astIsrRecord[SLEEP_TRACK_RECORD_NUM]; /* 中断流程记录 */
    SLEEP_RECORD_ITEM_EX_STRU           astMsgRecord[SLEEP_TRACK_RECORD_NUM]; /* 消息流程记录 */
}SLEEP_TRACK_RECORD_STRU;

/*****************************************************************************
 结构名    : SLEEP_NORMAL_STATE_RECORD_STRU
 结构说明  : 保存SLEEP正常状态切换流程
*****************************************************************************/
typedef struct
{
    SLEEP_RECORD_TRACK_STRU   astRecordItem[SLEEP_GU_MODE_TYPE_BUTT][SLEEP_NORMAL_BUTT];
}SLEEP_NORMAL_STATE_RECORD_STRU;

/*****************************************************************************
 结构名    : SLEEP_NOTIFY_STATE_REG_PID_STRU
 结构说明  : GU模式下，底层(GAS/GPHY)注册PID到SLEEP，SLEEP在从模低功耗状态通知到注册PID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      aulRegPidTbl[SLEEP_NOTIFY_STATE_REG_PID_MAX];
}SLEEP_NOTIFY_STATE_REG_PID_STRU;

/*****************************************************************************
 结构名    : SLEEP_BBP_SWITCH_INT_DELAY_RECORD_STRU
 结构说明  : BBP唤醒中断发生延迟，记录slice，及延迟计数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulDeltaSlice;         /* 记录延迟的时钟计数(单位为32K时钟节拍) */
    VOS_UINT32                      ulSlice;              /* 记录发生的Slice值 */
}SLEEP_BBP_SWITCH_INT_DELAY_RECORD_STRU;

/*****************************************************************************
 结构名    : SLEEP_BBP_SWITCH_INT_DELAY_STATISTIC_STRU
 结构说明  : BBP唤醒中断发生延迟，则记录相应统计信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCount;        /* 统计到的异常次数 */
    SLEEP_BBP_SWITCH_INT_DELAY_RECORD_STRU                  astRecord[SLEEP_BBP_SWITCH_INT_DELAY_RECORD_MAX];    /* 统计信息 */
}SLEEP_BBP_SWITCH_INT_DELAY_STATISTIC_STRU;


/*****************************************************************************
 结构名    : SLEEP_DEVICE_STATE
 结构说明  : GU模当前器件状态
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulDeviceFlag;
    VOS_UINT32                                  aulDevicePwState[MODEM_ID_BUTT][SLEEP_GU_MODE_TYPE_BUTT][PWC_COMM_MODULE_BUTT][PWC_COMM_CHANNEL_BUTT];
    VOS_UINT32                                  aulDeviceUpSlice[MODEM_ID_BUTT][SLEEP_GU_MODE_TYPE_BUTT][PWC_COMM_MODULE_BUTT][PWC_COMM_CHANNEL_BUTT];
    VOS_UINT32                                  aulDeviceDownSlice[MODEM_ID_BUTT][SLEEP_GU_MODE_TYPE_BUTT][PWC_COMM_MODULE_BUTT][PWC_COMM_CHANNEL_BUTT];
    VOS_UINT32                                  aulPllPwState[MODEM_ID_BUTT][SLEEP_GU_MODE_TYPE_BUTT][PWC_COMM_MODULE_BUTT][PWC_COMM_CHANNEL_BUTT];
    VOS_UINT32                                  aulPLLUpSlice[MODEM_ID_BUTT][SLEEP_GU_MODE_TYPE_BUTT][PWC_COMM_MODULE_BUTT][PWC_COMM_CHANNEL_BUTT];
    VOS_UINT32                                  aulPLLDownSlice[MODEM_ID_BUTT][SLEEP_GU_MODE_TYPE_BUTT][PWC_COMM_MODULE_BUTT][PWC_COMM_CHANNEL_BUTT];
    SLEEP_RECORD_STRU                           astDevicePowerError[SLEEP_GU_MODE_TYPE_BUTT];
    SLEEP_RECORD_STRU                           stDeviceTcxoError;
    SLEEP_BBP_SWITCH_INT_DELAY_STATISTIC_STRU   stDelayRecord;
    SLEEP_RECORD_STRU                           stHandShakeRecord;    /* 记录配置握手寄存器的次数及Slice */
    VOS_UINT32                                  aulABBState[64];
    VOS_UINT32                                  ulBBPResumeTimeout;
    SLEEP_RECORD_STRU                           stDMACapError;
    VOS_UINT32                                  ulSlaveSEMTakeTimes;
    VOS_UINT32                                  ulSlaveSEMTakeStartSlice;
    VOS_UINT32                                  ulSlaveSEMTakeEndSlice;
    VOS_UINT32                                  ulSlaveSEMGiveTimes;
    VOS_UINT32                                  ulSlaveSEMGiveStartSlice;
    VOS_UINT32                                  ulSlaveSEMGiveEndSlice;
}SLEEP_DEVICE_STATE_STRU;

/*****************************************************************************
 结构名    : SLEEP_CDMA_STATE_STRU
 结构说明  : CDMA模式信息记录
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulInfoHeadFlag;
    VOS_UINT32                                  ulBBE16PowerState;
}SLEEP_CDMA_STATE_STRU;

/*****************************************************************************
 结构名    : SLEEP_SLAVE_MSG_TRACK_STRU
 结构说明  : 从模唤醒消息队列信息记录
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulMode;
    VOS_UINT32              ulSenderPid;
    VOS_UINT32              ulMsgName;
    VOS_UINT32              ulSlice;
}SLEEP_SLAVE_MSG_TRACK_STRU;

/*****************************************************************************
 结构名    : SLEEP_NOTIFY_MSG_TRACK_STRU
 结构说明  : 从模唤醒消息队列信息记录
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRegPid;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState;
    SLEEP_LOWPOWER_STATE_ENUM_UINT32    enLPState;
    VOS_UINT32                          ulSlice;
}SLEEP_NOTIFY_MSG_TRACK_STRU;

/*****************************************************************************
 结构名    : SLEEP_NORMAL_STATE_RECORD_STRU
 结构说明  : 保存SLEEP正常状态切换流程
*****************************************************************************/
typedef struct
{
    SLEEP_BBE16_RECORD_TRACK_STRU   astRecordItem[SLEEP_C_MODE_TYPE_BUTT][SLEEP_BBE16_NORMAL_BUTT];
}SLEEP_BBE16_NORMAL_STATE_RECORD_STRU;

/*****************************************************************************
 结构名    : SLEEP_BBE16_CPROC_CTRL_STRU
 结构说明  : CPROC注册消息体
*****************************************************************************/
typedef struct
{
    SLEEP_BBE16_CPROC_WAKEUP_FUNC   pfnCprocWakeupProc;
    VOS_VOID                       *pulCprocWakeupPara;
    SLEEP_BBE16_CPROC_SLEEP_FUNC    pfnCprocSleepProc;
    VOS_VOID                       *pulCprocSleepPara;
}SLEEP_BBE16_CPROC_CTRL_STRU;

/*****************************************************************************
 结构名    : SLEEP_BBE16_STATE_TRACK_MSG_STRU
 结构说明  : C模状态轨迹消息体
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER
   VOS_UINT16                           usMsgId;                /* 消息ID */
   VOS_UINT16                           usReserved;             /* 保留 */
   SLEEP_MODE_ENUM_UINT32               enRatMode;              /* 上报模式 */
   VOS_UINT32                           ulSlice;                /* 中断接收时间 */
   VOS_UINT32                           aulRecordInfo[0];
}SLEEP_BBE16_STATE_TRACK_MSG_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern SLEEP_NORMAL_STATE_RECORD_STRU         *g_pstSleepNormalState;

extern SLEEP_TRACK_RECORD_STRU                *g_pstSleepTrackRecord;

extern SLEEP_BBE16_NORMAL_STATE_RECORD_STRU   *g_pstSleepBBE16NormalState;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
MODEM_ID_ENUM_UINT16 SLEEP_GetModemId(VOS_VOID);
VOS_VOID SLEEP_EnableDspPll(VOS_VOID);
VOS_VOID SLEEP_ExitLowPower(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_BOOL SLEEP_IsSleep(VOS_VOID);
VOS_VOID Sleep_ActiveDspPll(VOS_VOID);
VOS_VOID SLEEP_NotifySndMsg(VOS_VOID);
VOS_VOID GUSLEEP_MasterAwakeSlave(VOS_VOID);
VOS_VOID SLEEP_32KIsr(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_NormalClockIsr(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_AwakeIsr(SLEEP_MODE_ENUM_UINT32 enMode);

VOS_VOID SLEEP_VoteLock(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_VoteUnlock(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_TimeCal(VOS_VOID);
VOS_VOID SLEEP_ResumeReg(VOS_VOID);
VOS_VOID SLEEP_PowerUp(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_DeactivateHw(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_InfoInd( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_UINT32  SLEEP_ForceWakeProtected(VOS_VOID);
VOS_UINT32  SLEEP_WakePhy(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode, UPHY_OAM_WAKE_TYPE_ENUM_UINT32 enWakeType);
VOS_VOID    SLEEP_AwakeIsrProc(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    SLEEP_SleepIsrProc(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    SLEEP_MasterSleepMsgProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_32KClkMsgProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_WakeMasterMsgProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_NormalClkMsgProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_SlaveSleepMsgProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_WakeSlaveGUProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_WakeMasterGUProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_MasterForceWake(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    SLEEP_SlaveForceWake(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    SLEEP_HookMsgProc(MsgBlock *pstMsg);
VOS_VOID    SLEEP_AwakeMsgProc(MsgBlock* pstMsg);
VOS_VOID    SLEEP_SleepMsgProc(MsgBlock* pstMsg);
VOS_VOID    SLEEP_Init(VOS_VOID);
VOS_UINT32  WuepsAwakePidInit(enum VOS_INIT_PHASE_DEFINE ip);
VOS_UINT32  WuepsAwakeFidInit(enum VOS_INIT_PHASE_DEFINE ip);
VOS_UINT32  WuepsSleepPidInit(enum VOS_INIT_PHASE_DEFINE ip);
VOS_UINT32  WuepsSleepFidInit(enum VOS_INIT_PHASE_DEFINE ip);
VOS_UINT32  SLEEP_ReadBaseCntChip( VOS_VOID );

VOS_VOID    I1_SLEEP_VoteLock(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    I1_SLEEP_PowerUp(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    I2_SLEEP_VoteLock(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID    I2_SLEEP_PowerUp(SLEEP_MODE_ENUM_UINT32 enMode);

VOS_BOOL    SLEEP_IsAwake(SLEEP_MODE_ENUM_UINT32 enMode);

VOS_UINT32  SLEEP_InfoFileName( VOS_CHAR * cFileName );
VOS_UINT32  SLEEP_InfoWriteLog( VOS_UINT32 *pstInfo, VOS_UINT32 uLen );
VOS_VOID    SLEEP_ActivateHWMsgProc(MsgBlock *pstMsg);
VOS_UINT32  SLEEP_GetLogPath(VOS_CHAR *pucBuf, VOS_CHAR *pucOldPath, VOS_CHAR *pucUnitaryPath);

VOS_VOID SLEEP_NotifyStateToRegPid(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID SLEEP_BBE16HaltIsr( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16AwakeIsr( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16ResumeIsr( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_TaskDelay( VOS_UINT32 ulSliceDelay );
VOS_VOID SLEEP_BBE16DeactivateHw(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_VOID SLEEP_BBE16ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_UINT32  SLEEP_BBE16GetLowPowerState( SLEEP_MODE_ENUM_UINT32 enMode );
SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32 SLEEP_BBE16GetTwinState( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16PowerUp( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16ForceWakeProc( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16MasterForceWakeProc(MsgBlock *pstMsg);
VOS_VOID SLEEP_BBE16SlaveForceWakeProc(MsgBlock *pstMsg);
VOS_VOID SLEEP_BBE16MasterForceWake( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16SlaveForceWake( SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16HaltMsgProc( MsgBlock* pstMsg );
VOS_VOID SLEEP_BBE16AwakeMsgProc( MsgBlock* pstMsg );
VOS_VOID SLEEP_BBE16ResumeMsgProc( MsgBlock* pstMsg );
VOS_VOID SLEEP_BBE16HaltIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16AwakeIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16ResumeIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16HaltIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16AwakeIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode );
VOS_VOID SLEEP_BBE16ResumeIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode );

VOS_VOID SLEEP_BBE16MailBoxResumeProc(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_UINT32 SLEEP_BBE16IsMailBoxAllowCBBE16Sleep(SLEEP_MODE_ENUM_UINT32 enMode);
VOS_UINT32 SLEEP_BBE16MailBoxGetDspState(XMBX_RATMODE_ENUM_U32 enMode);
VOS_VOID SLEEP_BBE16MailBoxForceWakeDsp(XMBX_RATMODE_ENUM_U32 enMode);

VOS_VOID SLEEP_ReportEvent(VOS_UINT16 usEventId, SLEEP_MODE_ENUM_UINT32 enMode);

VOS_VOID SLEEP_BBE16DbgInit(VOS_VOID);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLEEPFLOW_H__ */
