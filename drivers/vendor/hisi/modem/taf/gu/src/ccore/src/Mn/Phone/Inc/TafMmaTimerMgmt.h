
#ifndef  TAF_MMA_TIMER_MGMT_PROC_H
#define  TAF_MMA_TIMER_MGMT_PROC_H

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MMA_MAX_TIMER_NUM                       (30)

/* 等待PB的文件刷新指示定时器 */
#define TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT_LEN                 (10*1000)


/* 等待MSCC的开机回复定时器 */
#define TI_TAF_MMA_WAIT_MSCC_START_CNF_LEN                        (70*1000)

/* 等待MSCC的关机回复定时器 */
#define TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF_LEN                    (61*1000)



#define TI_TAF_MMA_WAIT_MSCC_ACQ_CNF_LEN                          (180*1000)

/* 等待MSCC的REG_CNF定时器 */
#define TI_TAF_MMA_WAIT_MSCC_REG_CNF_LEN                          (1200*1000)

/* 等待MSCC的POWER_SAVE_CNF定时器 */
#define TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF_LEN                   (23*1000)


#define TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF_LEN                      (23*1000)

#define TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF_LEN                  (1*1000)
#define TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF_LEN                (1*1000)

#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF_LEN               (6*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF_LEN             (1*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF_LEN              (1*1000)

/*收到PS_USIM_REFRESH_IND 且有CS业务，等待CS业务结束重启*/
#define TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN                   (5*1000)
#define TI_TAF_MMA_WAIT_READ_SIM_FILES_LEN                       (10*1000)


#define TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF_LEN                   (5*1000)
#define TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF_LEN                    (5*1000)
#define TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_SET_CNF_LEN         (320*1000)
#define TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_RESEL_SET_CNF_LEN      (110*1000)
#define TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF_LEN         (5*1000)

#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF_LEN               (6*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF_LEN             (1*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF_LEN              (1*1000)

#define TI_TAF_MMA_WAIT_MSCC_DETACH_CNF_LEN                       (95 * 1000)
#define TI_TAF_MMA_WAIT_MSCC_SYSCFG_DETACH_CNF_LEN                (44 * 1000)
/* 待定 */
#define TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF_LEN                       (150 * 1000)
#define TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF_LEN                       (55 * 1000)

/* 4F36文件Refresh触发内部SYSCFG，周期性尝试定时器时长 */
#define TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING_LEN                (5*1000)


#define TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF_LEN                 (6*1000)
#define TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF_LEN                  (6*1000)

#define TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF_LEN             (215*1000)
#define TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF_LEN              (10*1000)

/* 获取国家码定时器默认时长 */
#define TAF_MMA_GET_GEO_TIMER_DEFAULT_LEN                        (3*1000)

/* 等待停止获取国家码定时器默认时长 */
#define TAF_MMA_WAIT_STOP_GET_GEO_CNF_LEN                        (3*1000)



/* 国家码有效时长默认值，单位为秒 */
#define TAF_MMA_GEO_EFFECTIVE_TIME_DEFAULT_LEN                   (30*60)



#define TI_TAF_MMA_DEFAULT_FREQUENCE_OF_QRY_CDMA_SYS_INFO_LEN    (5*1000)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_MMA_TIMER_ID_ENUM
{
    /* 等待PB的文件刷新指示定时器 */
    TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT                  = MN_TIMER_CLASS_MMA ,

    /* 删除定时器处理 */

    /* 等待MSCC的开机回复定时器 */
    TI_TAF_MMA_WAIT_MSCC_START_CNF,

    /* 等待MSCC的关机回复定时器 */
    TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF,

    /* 删除定时器处理 */

    /* 等待MSCC的MSCC_ACQ_CNF定时器 */
    TI_TAF_MMA_WAIT_MSCC_ACQ_CNF,

    /* 等待MSCC的REG_CNF定时器 */
    TI_TAF_MMA_WAIT_MSCC_REG_CNF,

    /* 等待MSCC的POWER_SAVE_CNF定时器 */
    TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF,

    /* 等待mscc srv acq cnf业务触发搜网结果消息定时器 */
    TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF,

    /* 删除定时器处理 */

    /* 删除定时器处理 */

    TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF,
    TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF,

    TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF,
    TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF,
    TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF,

    /*收到PS_USIM_REFRESH_IND 且有CS业务，等待CS业务结束重启*/
    TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN                 ,
    TI_TAF_MMA_WAIT_READ_SIM_FILES,

    /* 等待MSCC的IMS开启回复定时器 */
    TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF,

    /* 等待MSCC的IMS关闭回复定时器 */
    TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF,

    TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF,
    TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF,
    TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF,
    TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF,
    TI_TAF_MMA_WAIT_MSCC_DETACH_CNF,
    TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF,
    TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF,

    /* 4F36文件Refresh触发SYSCFG，周期性尝试定时器*/
    TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING,


    TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF,
    TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF,


    TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF,
    TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF,

    TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS              ,

    TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO,

    TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
    TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,

    TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF,
    TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF,

    TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE,                             /* 延迟上报CL无服务定时器 */
    TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE,                             /* 延迟上报DO无服务定时器 */

    TI_TAF_MMA_TIMER_BUTT
};
typedef VOS_UINT32  TAF_MMA_TIMER_ID_ENUM_UINT32;


enum TAF_MMA_TIMER_STATUS_ENUM
{
    TAF_MMA_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    TAF_MMA_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    TAF_MMA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MMA_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
  3 结构声明
*****************************************************************************/


typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId;                              /* 定时器的ID */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[3];
} TAF_MMA_TIMER_CTX_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_MMA_TIMER_INFO_STRU;

/*****************************************************************************
  4 函数声明
*****************************************************************************/
VOS_VOID  TAF_MMA_StartTimer(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  TAF_MMA_StopTimer(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId
);

TAF_MMA_TIMER_STATUS_ENUM_UINT8  TAF_MMA_GetTimerStatus(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId
);

VOS_VOID  TAF_MMA_SndOmTimerStatus(
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
);

extern VOS_UINT32  TAF_MMA_GetPlmnListAbortTimerLen(VOS_VOID);

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

#endif /* TAF_MMA_TIMER_MGMT_H */


