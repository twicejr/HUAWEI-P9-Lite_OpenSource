/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TlPsDrv.h
  版 本 号   : 初稿
  作    者   : 翟鹏 00282933
  生成日期   : 2014年9月1日
  最近修改   :
  功能描述   : 协议栈封装底软API接口
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月1日
    作    者   : 翟鹏 00282933
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TLPS_DRV_H__
#define __TLPS_DRV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#include "mdrv.h"
#include "msp.h"
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*z00282933, 多模OM融合添加 - BEGIN*/
#define LPS_OM_ID(pid, log_type)    DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_LTE, log_type)

#define TPS_OM_ID(pid, log_type)    DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_TDS, log_type)

#define COMM_OM_ID(pid, log_type)   DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, log_type)
/*z00282933, 多模OM融合添加 - END*/

#define LDRV_OM_SYSTEM_ERROR                    mdrv_om_system_error

#define LDRV_OM_REGISTER_CALLBACK               mdrv_om_register_callback

#define LDRV_TIMER_GET_ACC_TS                   mdrv_timer_get_accuracy_timestamp

#define LDRV_TIMER_GET_NORMAL_TIMESTAMP         mdrv_timer_get_normal_timestamp

#define LDRV_VER_GET_INFO                       mdrv_ver_get_info

#define LDRV_BBP_REG_DLTB_INTR_CB               mdrv_bbp_register_dltb_intr_cb

#define LDRV_BBP_GET_SYSFRM                     mdrv_bbp_get_lte_sysfrm

#define LDRV_BBP_GET_SUBFRM                     mdrv_bbp_get_lte_subfrm

#define LDRV_BBP_INIT_INTR                      mdrv_bbp_init_intr

#define LDRV_BBP_GET_TA                         mdrv_bbp_get_lte_ta

#define LDRV_DSP_LOAD_BBE                       mdrv_dsp_load_bbe

#define LDRV_DSP_RUN_BBE                        mdrv_dsp_run_bbe

#define LDRV_PM_PWRUP                           mdrv_pm_pwrup

#define LDRV_PM_WAKE_LOCK                       mdrv_pm_wake_lock

#define LDRV_PM_WAKE_UNLOCK                     mdrv_pm_wake_unlock

#define LDRV_PM_GET_DFS_PROFILE_LIMIT           mdrv_pm_get_dfs_profile_limit

#define LDRV_PM_GET_DFS_PROFILE                 mdrv_pm_get_dfs_profile

#define LDRV_PM_SET_DFS_PROFILE                 mdrv_pm_set_dfs_profile

#define LDRV_PM_REG_CCPULOAD_CB                 mdrv_pm_register_ccpuload_cb

#define LDRV_IPF_INIT                           mdrv_ipf_init

#define LDRV_IPF_CONFIG_ULCHAN                  mdrv_ipf_config_ulchan

#define LDRV_IPF_CONFIG_DLCHAN                  mdrv_ipf_config_dlchan

#define LDRV_IPF_ENABLE_CHAN                    mdrv_ipf_enable_chan

#define LDRV_IPF_GET_DLBD_NUM                   mdrv_ipf_get_dlbd_num

#define LDRV_IPF_GET_DLBD_MAX_NUM               mdrv_ipf_get_dlbd_max_num

#define LDRV_IPF_GET_FILTER                     mdrv_ipf_get_filter

#define LDRV_IPF_REG_OPS                        mdrv_ipf_register_ops

#define LDRV_IPF_GET_ULRD                       mdrv_ipf_get_ulrd

#define LDRV_IPF_CONFIG_ULAD                    mdrv_ipf_config_ulad

#define LDRV_IPF_GET_ULAD_NUM                   mdrv_ipf_get_ulad_num

#define LDRV_IPF_SET_FILTER                     mdrv_ipf_set_filter

#define LDRV_IPF_CONFIG_DLBD                    mdrv_ipf_config_dlbd

#define LDRV_IPF_CONFIG_TIMEOUT                 mdrv_ipf_config_timeout

#define LDRV_IPF_CONFIG_ADTHRED                 mdrv_ipf_config_adthred

#define LDRV_IPF_SET_DBUF_PARA                  mdrv_ipf_set_dbuf_para

#define LDRV_MEM_MEMCPY                         mdrv_memcpy

#define LDRV_MEM_GETMEMINFO                     mdrv_getmeminfo

#define LDRV_DIAG_TRACEREPORT                   DIAG_ReportLayerMessageLog

#define LDRV_DIAG_GTRRCVCALLBACKREG             DIAG_GtrRcvCallBackReg

#define LDRV_DIAG_SOCPPOWERON                   DIAG_SocpPowerOn

#define LDRV_DIAG_DSPINITFINISHED               DIAG_DspInitFinished

/*z00282933, 多模OM融合添加 - BEGIN*/
#define LDRV_DIAG_LOGREPORT                     DIAG_LogReport

#define LDRV_DIAG_EVENTREPORT                   DIAG_EventReport

#define LDRV_DIAG_AIRMSGREPORT                  DIAG_AirMsgReport

#define LDRV_DIAG_USERPLANEREPORT               DIAG_UserPlaneReport

#define LDRV_DIAG_COMMONREPORT                  DIAG_TransReport
/*z00282933, 多模OM融合添加 - END*/

#define LDRV_TLSLEEP_ACTIVATEHW                 TLSLEEP_ActivateHw

#define LDRV_FTM_GETMODE                        FTM_GetMode

#define LDRV_ACC_DMA                            mdrv_acc_dma

#define LDRV_ACC_CIPHER                         mdrv_acc_cipher

#define LDRV_ACC_GET_BDQ_ADDR                   mdrv_acc_get_bdq_addr

#define LDRV_ACC_GET_STATUS                     mdrv_acc_get_status

#define LDRV_ACC_ENABLE                         mdrv_acc_enable

#define LDRV_CIPHER_REG_MEMFREE_CB              mdrv_cipher_register_memfree_cb

#define LDRV_CIPHER_REG_NOTIFY_CB               mdrv_cipher_register_notify_cb

#define LDRV_CIPHER_PURGE_CHAN                  mdrv_cipher_purge_chan

#define LDRV_CIPHER_SINGLE_SUBMIT_TASK          mdrv_cipher_single_submit_task

#define LDRV_CIPHER_RELA_SUBMIT_TASK            mdrv_cipher_rela_submit_task

#define LDRV_CIPHER_SET_KEY                     mdrv_cipher_set_key

#define LDRV_CIPHER_GET_KEY                     mdrv_cipher_get_key

#define LDRV_CIPHER_SET_DBUF_PARA               mdrv_cipher_set_dbuf_para

#define LDRV_CIPHER_GET_CMPLT_DATA              mdrv_cipher_get_cmplt_data

#define LDRV_CIPHER_DISABLE                     mdrv_cipher_disable

#define LDRV_CIPHER_GEN_KEY                     mdrv_cipher_gen_key

#define LDRV_CIPHER_GET_RDINFO                  mdrv_cipher_get_rdinfo

#define LDRV_CIPHER_GET_CHN_STATUS              mdrv_cipher_get_chn_status


/**/
#define LDRV_CIPHER_GET_BD_NUM              mdrv_cipher_get_bd_num

/**/
#define LDRV_CIPHER_SET_BD_INFO             mdrv_cipher_set_bdinfo
#define LDRV_OM_REGISTER_FIELD                  mdrv_om_register_field

#define LDRV_SYSBOOT_STAMPADD                   mdrv_sysboot_stampadd


#define LDRV_PMU_DISABLE_APT                    mdrv_pmu_disable_apt

#define LDRV_PMU_ENABLE_APT                     mdrv_pmu_enable_apt

#define TDRV_TIMER_GET_ACC_TS                   mdrv_timer_get_accuracy_timestamp

#define TDRV_TIMER_GET_NORMAL_TS                mdrv_timer_get_normal_timestamp

#define TDRV_BBP_REG_TDSTF_INTR_CB              mdrv_bbp_register_tdstf_intr_cb

#define TDRV_BBP_ENABLE_TDSTF_INTR              mdrv_bbp_enable_tdstf_intr

#define TDRV_BBP_DISABLE_TDSTF_INTR             mdrv_bbp_disable_tdstf_intr

#define TDRV_BBP_SET_SUBFRM_OFFSET              mdrv_bbp_set_tds_subfrm_offset

#define TDRV_PM_PWRUP                           mdrv_pm_pwrup

#define TDRV_MEM_MEMCPY                         mdrv_memcpy

#define TDRV_NV_READ                            NV_Read

#define TDRV_DIAG_TRACEREPORT                   DIAG_ReportLayerMessageLog

/*z00282933，多模OM融合添加 - BEGIN*/
#define TDRV_DIAG_LOGREPORT                     DIAG_LogReport

#define TDRV_DIAG_EVENTREPORT                   DIAG_EventReport

#define TDRV_DIAG_COMMONREPORT                  DIAG_TransReport
/*z00282933, 多模OM融合添加 - END*/

#define TDRV_MISC_GET_IP_BASEADDR               mdrv_misc_get_ip_baseaddr


#define TDRV_PMU_DISABLE_APT                    mdrv_pmu_disable_apt

/*z00282933, 多模OM融合添加 - BEGIN*/
#define COMMDRV_DIAG_COMMONREPORT               DIAG_TransReport
/*z00282933, 多模OM融合添加 - END*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

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
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
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

#endif

