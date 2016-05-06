/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_Config.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : BASTET系统参数配置
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_CONFIG_H__
#define __BST_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _WIN32
#define _WINSOCKAPI_
#endif
#define __DRV_MAILBOX_CFG_H__

#include "product_config.h"
#include "TcpIpTypeDef.h"
/*****************************************************************************
  1 Version Control
*****************************************************************************/
#define BST_FEATURE_ON                  ( 1 )
#define BST_FEATURE_OFF                 ( 0 )
#define BST_WIN32                       ( 0x01 )
#define BST_HISI_VOS                    ( 0x02 )
#define BST_QCOM_ROS                    ( 0x03 )
#define BST_OS_VER                      ( BST_HISI_VOS )

#define BST_DBG_VER                     ( 0x01 )
#define BST_UT_VER                      ( 0x02 )
#define BST_RLS_VER                     ( 0x03 )

#if (VOS_WIN32 == VOS_OS_VER)
#define BST_VER_TYPE                    ( BST_UT_VER )
#else
#define BST_VER_TYPE                    ( BST_DBG_VER )
#endif

#if ( BST_VER_TYPE == BST_UT_VER )
#define BST_PUBLIC                      public
#define BST_PROTECTED                   public
#define BST_PRIVATE                     public
#define BST_STATIC
#else
#define BST_PUBLIC                      public
#define BST_PROTECTED                   protected
#define BST_PRIVATE                     private
#define BST_STATIC                      static
#endif

#define BST_SSL_SUPPORT

/*****************************************************************************
  2 SYSTEM
*****************************************************************************/

#define BST_MAX_APP_NUMBER              ( 32U )
#define BST_DEFAULT_EVENT_NUM           ( 256U )
#define BST_MAX_CNNT_NUMBER             ( BST_MAX_APP_NUMBER*2 )

/*系统主任务线程数*/
#define BST_CFG_SYS_THRD_NUM            ( 1U )
/*IP协议栈线程数*/
#define BST_CFG_IP_THRD_NUM             ( 1U )
/*信道分级线程数*/
#define BST_CFG_CHNL_THRD_NUM           ( 1U )
/*实时处理线程数*/
#define BST_CFG_RT_THRD_NUM             ( 0U )
/*实时非处理线程数*/
#define BST_CFG_NRT_THRD_NUM            ( 2U )

#define BST_ACOMM_MAX_PKT_LEN           ( 256U )
#ifdef BST_SSL_SUPPORT
#define BST_SYS_SUPPORT_CFG             ( BST_SYS_SUPPORT_TCP_SHORT | \
                                          BST_SYS_SUPPORT_TCP_LONG  | \
                                          BST_SYS_SUPPORT_TCP_SHORT_SSL | \
                                          BST_SYS_SUPPORT_UDP )
#else
#define BST_SYS_SUPPORT_CFG             ( BST_SYS_SUPPORT_TCP_SHORT | \
                                          BST_SYS_SUPPORT_TCP_LONG  | \
                                          BST_SYS_SUPPORT_UDP )
#endif
#define BST_TASK_MAX_SYSPEND            ( 3U )
#define BST_TASK_MAX_CYCLEN             ( 20U )                      /*MAX 34分钟*/
#define BST_TASK_MIN_CYCLEN             ( 1U )                       /*MIN 2 分钟*/

#if ( BST_OS_VER == BST_WIN32 )
#define snprintf _snprintf
#endif
/*****************************************************************************
  3 OS
*****************************************************************************/
#define BST_OS_STACK_SIZE_XL            ( BST_OS_STACK_SIZE_M * 2 )
#define BST_OS_STACK_SIZE_L             ( BST_OS_STACK_SIZE_M * 2 )
#define BST_OS_STACK_SIZE_M             ( 4096U )
#define BST_OS_STACK_SIZE_S             ( 1024U  )
#define BST_OS_TICKS_MS                 ( 10U )

#define BST_OS_PRIO_HIGH                ( VOS_PRIORITY_M4 )
#define BST_OS_PRIO_MIDL                ( VOS_PRIORITY_M5 )
#define BST_OS_PRIO_LOW                 ( VOS_PRIORITY_M6 )

#define BST_L_MBOX_SIZE                 ( 128U )
#define BST_M_MBOX_SIZE                 ( 64U )
#define BST_S_MBOX_SIZE                 ( 32U )


#define BST_MAX_TIMER_NUMBER            ( 1024 ) //定时器的个数

#define BST_NONE_THERAD_FLAG            ( 0x00U )
#define BST_MAIN_THREAD_FLAG            ( 0x01U )
#define BST_TCPIP_THREAD_FLAG           ( 0x02U )
#define BST_CHNL_CTRL_THREAD_FLAG       ( 0x04U )
#define BST_APP_THREAD_FLAG             ( 0x08U )

#define BST_BASE_THREAD_FLAGS           ( BST_MAIN_THREAD_FLAG \
                                        | BST_CHNL_CTRL_THREAD_FLAG\
                                        | BST_TCPIP_THREAD_FLAG )

#define BST_MAX_INIT_WAIT_TIME          ( 3 )
#define BST_THREAD_INIT_MS              ( 300 )
/*****************************************************************************
  4 ACOMM
*****************************************************************************/
#define BST_ACOM_PACKET_SIZE            ( 2048 )
#define BST_ACOM_ESCAPE_MUL             ( 1 )
#define BST_ACOM_BUF_SIZE               ( BST_ACOM_PACKET_SIZE * BST_ACOM_ESCAPE_MUL )
#define BST_ACOM_RCV_EXPD_TIME          ( 5*BST_OS_MS_IN_S )
#define BST_ACOM_TRS_EXPD_TIME          ( 1*BST_OS_MS_IN_S )

/*****************************************************************************
  5 AS
*****************************************************************************/
#define BST_AS_REL_RRC_TIMER_LEN        ( 2*BST_OS_MS_IN_S )
#define BST_AS_REPORT_ALLOWED_TIMER_LEN ( 3*BST_OS_MS_IN_S )
#define BST_AS_RAT_SUPPORT_FLAGSET      ( BST_AS_RAT_GPRS   \
                                        | BST_AS_RAT_WCDMA  \
                                        | BST_AS_RAT_TDSCDMA\
                                        | BST_AS_RAT_LTE)

#define BST_CHNL_MODE_LPM_LIMIT_BYTE    (2048)

/*****************************************************************************
  6 NET
*****************************************************************************/
#define BST_IP_SUPPORT_PPP              ( BST_FEATURE_OFF )
#define BST_IP_MTU_SIZE                 ( 1700 )
#define BST_IP_RSV_SIZE                 ( 100 )
#define BST_IP_PPP_RAT_FLAGSET          ( BST_AS_RAT_CDMA | BST_AS_RAT_EVDO )
//#define BST_LOOPER_MODE                 1
//#define BST_MODEM_SELF                  ( 0x01U )
//#define BST_PEAK_SPEED_TEST             ( 0x01U )
//#define BST_RUBBISH_DEBUG

#ifdef BST_RUBBISH_DEBUG
#ifndef BST_MODEM_SELF
#define BST_MODEM_SELF                  ( 0x01U )
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
