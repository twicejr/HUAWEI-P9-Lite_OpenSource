

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VosTaskPrioDef.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2013年10月28日
  最近修改   :
  功能描述   : 公共头文件, 定义VOS全系统的任务优先级
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月28日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef _VOS_TASK_PRIO_DEF_H
#define _VOS_TASK_PRIO_DEF_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#if (VOS_VXWORKS == VOS_OS_VER)
#define GUPHY_APM_TASK_PRIO             (0)
#define GUPHY_RCM_TASK_PRIO             (0)
#define GUPHY_GPHY_TASK_PRIO            (1)
#define COMM_BBPDBG_SELFTASK_PRIO       (1)
#define GUPHY_UPA_TASK_PRIO             (2)
#define GUPHY_WPHY_TASK_PRIO            (3)
#define COMM_HPA_SELFTASK_PRIO          (3)
#define GUPHY_DRX_TASK_PRIO             (4)
#define GUPHY_WMEAS_TASK_PRIO           (4)
#define TTF_FLOW_CTRL_TASK_PRIO         (4)
#define COMM_SLEEP_TASK_PRIO            (4)
#define COMM_AWAKE_TASK_PRIO            (4)
#define CPROC_HRPD_TASK_PRIO            (4)
#define CPROC_1X_TASK_PRIO              (4)
#define CPROC_RM_TASK_PRIO              (4)
#define PHY_COM_TASK_PRIO               (5)
#define COMM_TIMER_TASK_PRIO            (74)
#define COMM_RTC_TIMER_TASK_PRIO        (74)
#define COMM_NOSIG_TASK_PRIO            (75)
#define GTTF_GRM_TASK_PRIO              (76)
#define COMM_SPY_TASK_PRIO              (78)
#define CTTF_1X_REV_TASK_PRI            (123)
#define WTTF_MAC_RLC_UL_TASK_PRIO       (125)
#define CTTF_HRPD_REV_TASK_PRI          (125)
#define SOCP_ENCSRC_SELFTASK_PRIO       (126)
#define SOCP_DECSRC_SELFTASK_PRIO       (126)
#define SOCP_ENCDST_SELFTASK_PRIO       (130)
#define SOCP_DECDST_SELFTASK_PRIO       (130)
#define COMM_HPA_TASK_PRIO              (130)
#define WTTF_MAC_RLC_DL_TASK_PRIO       (131)
#define CTTF_1X_FWD_TASK_PRI            (131)
#define CTTF_HRPD_FWD_TASK_PRI          (131)
#define CTTF_HRPD_SIG_TASK_PRI          (132)
#define PPPC_TASK_PRI                   (133)
#define RRM_TASK_PRIO                   (135)
#define NAS_MM_TASK_PRIO                (137)
#define NAS_MSCC_TASK_PRIO              (137)
#define CNAS_TASK_PRIO                  (137)
#define TTF_MEM_RB_FREE_TASK_PRIO       (151)
#define GUPHY_IDLE_TASK_PRIO            (250)
#define COMM_LOG_SELFTASK_PRIO          (253)
#define COMM_WD_SELFTASK_PRIO           (254)

/* Just for pclint.*/
#define COMM_SOCK_SELFTASK_PRIO         (101)
#define SCM_DATA_RCV_SELFTASK_PRIO      (101)
#define COMM_PRINTF_SELFTASK_PRIO       (253)
#endif

#if (VOS_LINUX == VOS_OS_VER)
#define COMM_WD_SELFTASK_PRIO           (4)
#define CPROC_HRPD_TASK_PRIO            (4)
#define CPROC_1X_TASK_PRIO              (4)
#define CPROC_RM_TASK_PRIO              (4)
#define COMM_LOG_SELFTASK_PRIO          (5)
#define COMM_PRINTF_SELFTASK_PRIO       (6)
#define SOCP_ENCDST_SELFTASK_PRIO       (69)
#define SOCP_DECDST_SELFTASK_PRIO       (69)
#define SOCP_ENCSRC_SELFTASK_PRIO       (73)
#define SOCP_DECSRC_SELFTASK_PRIO       (73)
#define COMM_SOCK_SELFTASK_PRIO         (76)
#define SCM_DATA_RCV_SELFTASK_PRIO      (76)
#define TTF_FLOW_CTRL_TASK_PRIO         (88)
#define TTF_ACPULOAD_TASK_PRIO          (89)
#define COMM_TIMER_TASK_PRIO            (90)
#define COMM_RTC_TIMER_TASK_PRIO        (90)
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
#define GUPHY_APM_TASK_PRIO             (0)
#define GUPHY_RCM_TASK_PRIO             (0)
#define GUPHY_GPHY_TASK_PRIO            (1)
#define COMM_BBPDBG_SELFTASK_PRIO       (1)
#define GUPHY_UPA_TASK_PRIO             (2)
#define GUPHY_WPHY_TASK_PRIO            (3)
#define COMM_HPA_SELFTASK_PRIO          (3)
#define GUPHY_DRX_TASK_PRIO             (4)
#define GUPHY_WMEAS_TASK_PRIO           (4)
#define TTF_FLOW_CTRL_TASK_PRIO         (4)
#define COMM_SLEEP_TASK_PRIO            (4)
#define COMM_AWAKE_TASK_PRIO            (4)
#define CPROC_HRPD_TASK_PRIO            (4)
#define CPROC_1X_TASK_PRIO              (4)
#define CPROC_RM_TASK_PRIO              (4)
#define PHY_COM_TASK_PRIO               (5)
#define COMM_TIMER_TASK_PRIO            (16)
#define COMM_RTC_TIMER_TASK_PRIO        (16)
#define COMM_NOSIG_TASK_PRIO            (17)
#define GTTF_GRM_TASK_PRIO              (18)
#define COMM_SPY_TASK_PRIO              (20)
#define CTTF_1X_REV_TASK_PRI            (29)
#define WTTF_MAC_RLC_UL_TASK_PRIO       (31)
#define CTTF_HRPD_REV_TASK_PRI          (31)
#define SOCP_ENCSRC_SELFTASK_PRIO       (32)
#define SOCP_DECSRC_SELFTASK_PRIO       (32)
#define SOCP_ENCDST_SELFTASK_PRIO       (34)
#define SOCP_DECDST_SELFTASK_PRIO       (34)
#define COMM_HPA_TASK_PRIO              (34)
#define WTTF_MAC_RLC_DL_TASK_PRIO       (35)
#define CTTF_1X_FWD_TASK_PRI            (35)
#define CTTF_HRPD_FWD_TASK_PRI          (35)
#define CTTF_HRPD_SIG_TASK_PRI          (36)
#define PPPC_TASK_PRI                   (37)
#define RRM_TASK_PRIO                   (39)
#define NAS_MM_TASK_PRIO                (41)
#define NAS_MSCC_TASK_PRIO              (41)
#define CNAS_TASK_PRIO                  (41)
#define TTF_MEM_RB_FREE_TASK_PRIO       (49)
#define GUPHY_IDLE_TASK_PRIO            (58)
#define COMM_LOG_SELFTASK_PRIO          (61)
#define COMM_WD_SELFTASK_PRIO           (62)
#endif

#if (VOS_WIN32 == VOS_OS_VER)
#define GUPHY_APM_TASK_PRIO             (0)
#define GUPHY_RCM_TASK_PRIO             (0)
#define GUPHY_GPHY_TASK_PRIO            (1)
#define GUPHY_UPA_TASK_PRIO             (2)
#define GUPHY_WPHY_TASK_PRIO            (3)
#define GUPHY_DRX_TASK_PRIO             (4)
#define GUPHY_WMEAS_TASK_PRIO           (4)
#define CPROC_HRPD_TASK_PRIO            (4)
#define CPROC_1X_TASK_PRIO              (4)
#define CPROC_RM_TASK_PRIO              (4)
#define SOCP_ENCDST_SELFTASK_PRIO       (69)
#define SOCP_DECDST_SELFTASK_PRIO       (69)
#define SOCP_ENCSRC_SELFTASK_PRIO       (73)
#define SOCP_DECSRC_SELFTASK_PRIO       (73)
#define COMM_NOSIG_TASK_PRIO            (75)
#define COMM_SOCK_SELFTASK_PRIO         (101)
#define SCM_DATA_RCV_SELFTASK_PRIO      (101)
#define TTF_MEM_RB_FREE_TASK_PRIO       (151)
#define COMM_HPA_TASK_PRIO              (192)
#define TTF_FLOW_CTRL_TASK_PRIO         (192)
#define TTF_ACPULOAD_TASK_PRIO          (193)
#define GTTF_GRM_TASK_PRIO              (193)
#define WTTF_MAC_RLC_UL_TASK_PRIO       (193)
#define WTTF_MAC_RLC_DL_TASK_PRIO       (193)
#define COMM_SPY_TASK_PRIO              (193)
#define COMM_BBPDBG_SELFTASK_PRIO       (193)
#define COMM_HPA_SELFTASK_PRIO          (193)
#define CTTF_1X_REV_TASK_PRI            (200)
#define CTTF_1X_FWD_TASK_PRI            (201)
#define CTTF_HRPD_REV_TASK_PRI          (200)
#define CTTF_HRPD_FWD_TASK_PRI          (201)
#define CTTF_HRPD_SIG_TASK_PRI          (201)
#define COMM_SLEEP_TASK_PRIO            (225)
#define COMM_AWAKE_TASK_PRIO            (225)
#define COMM_TIMER_TASK_PRIO            (225)
#define COMM_RTC_TIMER_TASK_PRIO        (225)
#define GUPHY_IDLE_TASK_PRIO            (250)
#define COMM_PRINTF_SELFTASK_PRIO       (253)
#define COMM_LOG_SELFTASK_PRIO          (253)
#define COMM_WD_SELFTASK_PRIO           (254)
#define PPPC_TASK_PRI                   (254)
#define NAS_MM_TASK_PRIO                (137)
#define NAS_MSCC_TASK_PRIO              (137)
#define CNAS_TASK_PRIO                  (137)
#define RRM_TASK_PRIO                   (196)

#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_PID_DEF_H */
