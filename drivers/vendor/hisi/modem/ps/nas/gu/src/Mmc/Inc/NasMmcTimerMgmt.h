
#ifndef  NAS_MMC_TIMER_MGMT_PROC_H
#define  NAS_MMC_TIMER_MGMT_PROC_H

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* MMC中同时运行的定时器的最大数目,默认为30个 */
#define NAS_MMC_MAX_TIMER_NUM                       (30)

/* MMC中定时器的时长 */
#define TI_NAS_MMC_WAIT_MM_START_CNF_LEN            (30*1000)


#define TI_NAS_MMC_WAIT_GAS_START_CNF_LEN           (7*1000)                    /* GAS开机保护时间为5S */

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_WAS_START_CNF_LEN           (40*1000)                   /* MMC等待WAS和TD模的开机回复定时器时长 */
#else
#define TI_NAS_MMC_WAIT_WAS_START_CNF_LEN           (8 * 1000)                  /* WAS的保护定时器为5S,NAS增加保护到7S */
#endif

#define TI_NAS_MMC_WAIT_LMM_START_CNF_LEN           (30*1000)
#define TI_NAS_MMC_WAIT_READ_SIM_FILES_LEN          (10*1000)
#define TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF_LEN          (10*1000)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF_LEN           (21 * 1000)                /* MMC等待WAS和TD模的SYSCFG设置回复定时器 */
#else
#define TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF_LEN           (10 * 1000)
#endif

#define TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF_LEN          (10*1000)
#define TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN        (10*1000)
#define TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN            (15*1000)
#define TI_NAS_MMC_FORBID_LA_TIMER_LEN              (12*60*60*1000)
#define TI_NAS_MMC_AVAILABLE_TIMER_LEN              (5*1000)
#define TI_NAS_MMC_HPLMN_TIMER_FIRST_LEN            (2*60*1000)
#define TI_NAS_MMC_HPLMN_TIMER_DEFAULT_LEN          (60 * 60 * 1000)
#define TI_NAS_MMC_DEFAULT_MAX_SEARCH_HPLMN_LEN     (18*60*1000)                /* 默认的最大HPLMN搜索周期18分钟 */

#define TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_LEN              (2 * 60)
#define TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER_NON_FIRST_LEN          (30 * 60)
#define TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_SEARCH_COUNT     (1)

#define TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN          (8*1000)

#define TI_NAS_MMC_WAIT_AS_RESUME_IND_LEN           (90*1000)

#define TI_NAS_MMC_DSDS_WAIT_AS_RESUME_IND_LEN                          (160 * 1000)
#define TI_NAS_MMC_DSDS_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN       (160*1000)
#define TI_NAS_MMC_DSDS_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN            (160*1000)

#define TI_NAS_MMC_WAIT_CMMCA_RESUME_IND_LEN        (180*1000)

#define TI_NAS_MMC_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN          (90*1000)
#define TI_NAS_MMC_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN     (90*1000)
#define TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN     (200*1000)
#define TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN     (6*1000)
#define TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF_LEN     (10*1000)
#define TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN     (8*1000)
#define TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN           (5*1000)

#define TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER_LEN (60 * 1000)  /* 定时器时长为1分钟*/

/* 等接入层的SYSINFO的定时器不再使用 */

#define TI_NAS_MMC_WAIT_EST_IND_LEN                 (20*1000)
#define TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN          (20*1000)
#define TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF_LEN     (5*1000)
#define TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN         (10*1000)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/* 等接入层关机回复的定时器不再使用 */
#define TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN        (21 * 1000)         /* 通知关闭主模时的保护定时器时长 */
#define TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN         (21 * 1000)         /* 通知关闭从模时的保护定时器时长 */
#else
/* 等接入层关机回复的定时器不再使用 */
#define TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN        (10 * 1000)         /* 通知关闭主模时的保护定时器时长 */
#define TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN         (10 * 1000)         /* 通知关闭从模时的保护定时器时长 */
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_UTRAN_PLMN_SEARCH_CNF_LEN   (301 * 1000)                /* 平台同时支持W/TD时，等搜网回复的保护定时器时长 */
#endif
#define TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN     (150 * 1000)

#define TI_NAS_MMC_WAIT_WAS_FAST_PLMN_SEARCH_CNF_LEN        (150 * 1000)        /* 在W下快速指定搜时候的定时器时长 */

#define TI_NAS_MMC_DSDS_SCEAN_WAIT_GAS_PLMN_SEARCH_CNF_LEN     (17000*1000)     /* 当前约为4小时，注意OSA的最大时长为18小时 */

#define TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN     (90*1000)
#define TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN     (120*1000)

#define TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN         (10 * 1000)

#define TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN         (10*1000)
#define TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN         (10*1000)
#define TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN       (7*1000)
#define TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN       (7*1000)
#define TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN       (7*1000)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN                                (23 * 1000)

/* 回退流程中，WAS上报系统消息时间较长，此处调整为20S */
#define TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN            (33 * 1000)
#define TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN                                (23 * 1000)
#define TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN                                (23 * 1000)
#else
#define TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN                                (10*1000)

/* 回退流程中，WAS上报系统消息时间较长，此处调整为20S */
#define TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN            (20 * 1000)
#define TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN                                (10 * 1000)
#define TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN                                (10 * 1000)
#endif

/* 修改GU下等待CSPS的注册结果时长从375变为495S */
/* 修改GU下等待CSPS的注册结果时长从495变为675S */
#define TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN            (675*1000)
#define TI_NAS_MMC_WAIT_TBF_REL_LEN                 (10*1000)
#define TI_NAS_MMC_WAIT_EPS_REG_IND_LEN             (180*1000)
#define TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN     (5*1000)
#define TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN    (5*1000)
#define TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN   (5*1000)
#define TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF_LEN         (210*1000)
#define TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF_LEN         (210*1000)
#define TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF_LEN         (210*1000)

#define TI_NAS_MMC_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN       (320*1000)          /* 驻留态下MMC等待WAS列表搜的时长(三模) */
#define TI_NAS_MMC_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN       (320*1000)          /* 驻留态下MMC等待GAS列表搜的时长(三模) */
#define TI_NAS_MMC_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN       (320*1000)          /* 驻留态下MMC等待L列表搜的时长(三模) */

#define TI_NAS_MMC_NOT_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN   (180*1000)          /* 非驻留态下MMC等待WAS列表搜的时长(单模) */
#define TI_NAS_MMC_NOT_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN   (180*1000)          /* 非驻留态下MMC等待GAS列表搜的时长(单模) */
#define TI_NAS_MMC_NOT_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN   (190*1000)          /* 非驻留态下MMC等待L列表搜的时长(单模) */

#define TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF_LEN      (180*1000)
#define TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF_LEN      (180*1000)
#define TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF_LEN        (10*1000)
#define TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF_LEN        (10*1000)
#define TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN  (10*1000)
#define TI_NAS_MMC_STK_STEERING_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN  (1*1000)

#define TI_NAS_MMC_ACTING_HPLMN_REFRESH_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN  (1*1000)

#define TI_NAS_MMC_WAIT_WAS_OOS_SYS_INFO_LEN                      (155*1000)

/* 关机时RECAMP VPLMN的定时器时长 */
#define TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_WAS_PLMN_SEARCH_CNF_LEN     (5 * 1000)
#define TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_GAS_PLMN_SEARCH_CNF_LEN     (5 * 1000)
#define TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_LMM_PLMN_SEARCH_CNF_LEN     (5 * 1000)

#define TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF_LEN            (10*1000)
#define TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF_LEN          (180*1000)


/* 删除TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER_LEN从nv项中获取 */

#define TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER_LEN              (10 * 1000)

#define TI_NAS_MMC_NCELL_PLMN_SEARCH_AVAILABLE_TIMER_LEN    (1 * 1000)          /* 1s定时器 */

/*********************************UTRANCTRL模块相关定时器时长*********************************/
/* UTRANCTRL模块PLMN SELECTION状态机相关定时器 */
#define TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN            (10*1000)
#define TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN        (150*1000)          /* TD下的DSP搜网时间为150S, */
#define TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN          (7*1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN           (10 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN       (150 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN         (7 * 1000)

/* UTRANCTRL模块MODE CHANGE状态机相关定时器 */
#define TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN  (5*1000)
#define TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF_LEN (3*1000)

#define TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF_LEN  (5*1000)

/* UTRANCTRL: POWER OFF状态相关定时器 */
#define TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN          (12 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN         (12 * 1000)         /* WAS关机保护时间为10S */

/* UTRANCTRL: SWITCH ON状态相关定时器 */
#define TI_NAS_UTRANCTRL_WAIT_TD_START_CNF_LEN              (32 * 1000)         /* TD的开机保护时间为30S */
#define TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF_LEN             (7 * 1000)          /* WAS的开机保护时间为5S */

/* UTRANCTRL: syscfg状态相关定时器 */
#define TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF_LEN             (10 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF_LEN            (10 * 1000)
/******************************************************************************************************************************/

#define TI_NAS_MMC_WAIT_MSCC_REG_REQ_LEN                     (60 * 1000)

#define TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF_LEN                (5 * 1000)

#define   TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF_LEN          (100*1000)
#define TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF_LEN                (2 * 1000)
#define TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN           (2 * 1000)

/* CL模式下，LTE2HRPD定时器时长， 重选为35s，
因为重定向需要全频道搜网，不确定多少组，一组加上一个频点需要150s
具体多次要看多少组,现在暂定为180S
*/
#define   TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_REDIR_LEN      (180*1000)
#define   TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_RESELCT_LEN    (35*1000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum NAS_MMC_TIMER_ID_ENUM
{
    /* 起始定时器的值为8192，跟ASN保持一致 */
    TI_NAS_MMC_FORBID_LA_TIMER                     = 8192,
    TI_NAS_MMC_AVAILABLE_TIMER                     = 8193,
    TI_NAS_MMC_HPLMN_TIMER                         = 8194,

    /* 开机相关定时器*/
    TI_NAS_MMC_WAIT_MM_START_CNF                   = 8195,
    TI_NAS_MMC_WAIT_LMM_START_CNF                  = 8197,
    TI_NAS_MMC_WAIT_READ_SIM_FILES                 = 8198,

    /* plmn srch 搜网处理相关定时器 */
    TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF            = 8199,
    TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF            = 8200,
    TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF            = 8201,
    TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF                = 8202,
    TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF                = 8203,
    TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF                = 8204,
    TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF              = 8205,
    TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF              = 8206,
    TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF              = 8207,

    /* 注册处理相关定时器 */
    TI_NAS_MMC_WAIT_WAS_SYS_INFO                   = 8208,
    TI_NAS_MMC_WAIT_GAS_SYS_INFO                   = 8209,
    TI_NAS_MMC_WAIT_LMM_SYS_INFO                   = 8210,
    TI_NAS_MMC_WAIT_CSPS_REG_IND                   = 8211,
    TI_NAS_MMC_WAIT_RRC_CONN_REL                   = 8212,
    TI_NAS_MMC_WAIT_TBF_REL                        = 8213,

    /* POWER OFF 状态相关定时器 */
    TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF            = 8214,
    TI_NAS_MMC_WAIT_MM_POWEROFF_CNF                = 8215,

    /* 等接入层关机回复的定时器不再使用 */

    /* suspend状态相关定时器 */
    TI_NAS_MMC_WAIT_MM_SUSPEND_RSP                 = 8217,                      /* 等待MM/GMM模块挂起回复的保护定时器 */
    TI_NAS_MMC_WAIT_AS_RESUME_IND                  = 8218,                      /* 等待接入层上报恢复指示的保护定时器 */
    TI_NAS_MMC_WAIT_MM_RESUME_RSP                  = 8219,                      /* 等待MM/GMM模块恢复回复的保护定时器 */
    TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF            = 8220,                      /* 等待WAS的挂起释放回复的保护定时器 */
    TI_NAS_MMC_WAIT_EST_IND                        = 8221,                      /* 等待CS/PS/EPS的建链结果指示的保护定时器 */
    TI_NAS_MMC_WAIT_AS_SUSPEND_IND                 = 8222,                      /* CCO回退时等待接入层上报挂起指示的保护定时器 */

    /* 等待注册结果相关定时器 */
    TI_NAS_MMC_WAIT_EPS_REG_IND                    = 8223,
    TI_NAS_MMC_WAIT_EPS_CONN_REL_IND               = 8224,

    /* LIST搜网相关定时器*/
    TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF              = 8225,                      /* 等待WAS的PLMN LIST搜网回复的保护定时器 */
    TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF              = 8226,                      /* 等待GAS的PLMN LIST搜网回复的保护定时器 */
    TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF              = 8227,                      /* 等待LMM的PLMN LIST搜网回复的保护定时器 */
    TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST        = 8228,                      /* 周期性尝试用户LIST搜网的定时器 */
    TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST       = 8229,                      /* 周期性尝试内部LIST搜网的定时器 */

    /* syscfg状态相关定时器*/
    TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF                 = 8230,
    TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF                 = 8231,
    TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF                 = 8232,

    /* 高优先级搜网相关定时器*/
    TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF         = 8233,                      /* 等待WAS BG搜网结果保护定时器，时长180s */
    TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF         = 8234,                      /* 等待GAS BG搜网结果保护定时器，时长180s */
    TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF           = 8235,                      /* 等待WAS停止BG搜网结果保护定时器，时长30s */
    TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF           = 8236,                      /* 等待GAS停止BG搜网结果保护定时器，时长30s */
    TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH = 8237,                      /* 周期性尝试高优先级搜网的定时器，时长10s */

    TI_NAS_MMC_WAIT_WAS_OOS_SYS_INFO               = 8238,

    TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF         = 8239,                      /* 等待Lmm BG搜网结果保护定时器 */
    TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF           = 8240,                      /* 等待LMM停止BG搜网结果保护定时器 */

    /* MMC: SWITCH ON状态相关定时器 */
    TI_NAS_MMC_WAIT_GAS_START_CNF                           = 8241,
    TI_NAS_MMC_WAIT_WAS_START_CNF                           = 8242,
    TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF                = 8243,
    TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF                 = 8244,

    TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF                     = 8245,                      /* 等待GAS的挂起释放回复的保护定时器 */
    TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF                     = 8246,                      /* 等待LMM的挂起释放回复的保护定时器 */

    TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER                        = 8247,             /* 在紧急呼叫,不能执行CSFB时,需要disable LTE,目前disable时长是5MINS */

    /* MMC NETSCAN周期性扫描定时器 */
    TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER                      = 8248,

    /* 高优先级接入技术的HPLMN搜索定时器 */
    TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER                    = 8249,

    TI_NAS_MMC_WAIT_MSCC_REG_REQ                             = 8250,
    TI_NAS_MMC_WAIT_CMMCA_RESUME_IND                        = 8251,

    TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER   = 8252,

    TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF                  = 8253,

    TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF                       = 8254,
    TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF                  = 8255,

    TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF                  = 8256,

    TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF                       = 8257,

    TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER            = 8258,             /* 第一阶段搜网总时间定时器 */

    TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER                     = 8259,    
    TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH        = 8260,                /* 周期性尝试用户LIST搜网的定时器 */
    TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF              = 8261,
    TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF              = 8262,
    TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF              = 8263,
    /*********************************UTRANCTRL模块相关定时器,ID从9000开始,中间预留给MMC增加新的定时器*********************************/
    /* UTRANCTRL模块PLMN SELECTION状态机相关定时器 */
    TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF                    = 9000,             /* 等待TDRRC挂起回复定时器,时长 */
    TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF                = 9001,             /* 等待TDRRC搜网回复定时器,时长 */
    TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF                  = 9002,             /* 等待TDRRC停止搜网回复定时器,时长 */
    TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF                   = 9003,             /* 等待WAS挂起回复定时器,时长 */
    TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF               = 9004,             /* 等待WAS搜网回复定时器,时长 */
    TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF                 = 9005,             /* 等待WAS停止搜网回复定时器,时长 */

    /* UTRANCTRL模块MODE CHANGE状态机相关定时器 */
    TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF          = 9006,             /* 等待从模模式变更回复定时器,时长 */
    TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF         = 9007,             /* 等待WAS模式变更回复定时器,时长 */

    /* UTRANCTRL: POWER OFF状态相关定时器 */
    TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF                 = 9008,
    TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF                  = 9009,

    /* UTRANCTRL: SWITCH ON状态相关定时器 */
    TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF                     = 9010,
    TI_NAS_UTRANCTRL_WAIT_TD_START_CNF                      = 9011,

    /* UTRANCTRL: syscfg状态相关定时器 */
    TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF                    = 9012,
    TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF                     = 9013,
    TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF     = 9014,             /* 等待主模释放W/TD从模需要的时长 */
    /******************************************************************************************************************************/


    TI_NAS_MMC_TIMER_BUTT
};
typedef VOS_UINT16  NAS_MMC_TIMER_ID_ENUM_UINT16;


enum NAS_MMC_TIMER_STATUS_ENUM
{
    NAS_MMC_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    NAS_MMC_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    NAS_MMC_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MMC_TIMER_STATUS_ENUM_U8;

/*****************************************************************************
  3 结构声明
*****************************************************************************/


typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId;                              /* 定时器的ID */
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           ucReserve;
} NAS_MMC_TIMER_CTX_STRU;

/*****************************************************************************
  4 函数声明
*****************************************************************************/

VOS_VOID  NAS_MMC_InitAllTimers(
    NAS_MMC_TIMER_CTX_STRU              *pstMmcTimerCtx
);



VOS_UINT32  NAS_MMC_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
);


VOS_VOID  NAS_MMC_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);



VOS_VOID  NAS_MMC_StopAllTimer( VOS_VOID );

NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_MMC_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

VOS_TIMER_PRECISION_ENUM_UINT32 NAS_MMC_GetTimerPrecision(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

VOS_VOID  NAS_MMC_SetTimerStopStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

VOS_UINT32  NAS_MMC_GetTimerRemainLen(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);


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

#endif /* NAS_MMC_TIMER_MGMT_PROC_H */

