

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_private.h                                                        */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _V_PRIVATE_H
#define _V_PRIVATE_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

extern void mdrv_om_system_error(int modId, int arg1, int arg2, char * arg3, int arg3Length);

#define VOS_FLOW_REBOOT     0xffffffff

/* C 核 有 64K 空间, 将最后的16 K 空间拿出来给 任务定位用，每个任务最多 4K */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define VOS_DUMP_MEM_TOTAL_SIZE         (48*1024)
#define VOS_TASK_DUMP_INFO_SIZE         (4*1024)
#else
#define VOS_DUMP_MEM_TOTAL_SIZE         (16*1024)
#define VOS_TASK_DUMP_INFO_SIZE         (4*1024)
#endif

#define VOS_DUMP_MEM_INFO_NUM           (4)
#define VOS_DUMP_MEM_ALL_SIZE           (VOS_DUMP_MEM_TOTAL_SIZE + (VOS_DUMP_MEM_INFO_NUM*VOS_TASK_DUMP_INFO_SIZE))

#define VOS_MEM_RECORD_BLOCK_SIZE       20

enum
{
    RTC_CHECK_TIMER_ID = 0x10000000,
    RTC_CHECK_TIMER_RANG,
    RTC_CHECK_TIMER_NOT_EQUAL,
    START_32K_CALLBACK_RELTIMER_FAIL_TO_STOP,
    START_32K_CALLBACK_RELTIMER_FAIL_TO_ALLOCATE,
    START_32K_RELTIMER_FAIL_TO_STOP,
    START_32K_RELTIMER_FAIL_TO_ALLOCATE,
    RESTART_32K_RELTIMER_NULL,
    RESTART_32K_RELTIMER_FAIL_TO_CHECK,
    VOS_CHECK_TIMER_ID,
    VOS_CHECK_TIMER_RANG,
    VOS_CHECK_TIMER_NOT_EQUAL,
    START_RELTIMER_FLASE_MODE,
    START_RELTIMER_NULL,
    START_RELTIMER_TOO_BIG,
    START_26M_RELTIMER_FAIL_TO_STOP,
    START_26M_RELTIMER_FAIL_TO_ALLOCATE,
    RESTART_RELTIMER_NULL,
    RESTART_RELTIMER_NOT_RUNNING,
    RESTART_RELTIMER_FAIL_TO_CHECK,
    START_CALLBACK_RELTIMER_FALSE_MODE,
    START_CALLBACK_RELTIMER_NULL,
    START_CALLBACK_RELTIMER_TOO_BIG,
    START_CALLBACK_RELTIMER_FAIL_TO_STOP,
    START_CALLBACK_RELTIMER_FAIL_TO_ALLOCATE,
    FAIL_TO_ALLOCATE_TIMER_MSG,
    FAIL_TO_ALLOCATE_MSG,
    FAIL_TO_ALLOCATE_MEM,
    DSP_REPORT_ERROR,
    INQUIRE_DSP_ERROR,
    WD_CHECK_ERROR,
    OSA_EXPIRE_ERROR,
    OSA_INIT_ERROR,
    OSA_SEND_MSG_NULL,
    OSA_SEND_MSG_PP_NULL,
    OSA_SEND_MSG_FAIL_TO_CHECK,
    OSA_SEND_MSG_PID_BIG,
    OSA_SEND_MSG_FAIL_TO_WRITE,
    OSA_SEND_URG_MSG_NULL,
    OSA_SEND_URG_MSG_PP_NULL,
    OSA_SEND_URG_MSG_FAIL_TO_CHECK,
    OSA_SEND_URG_MSG_PID_BIG,
    OSA_SEND_URG_MSG_FAIL_TO_WRITE,
    START_CALLBACK_RELTIMER_FUN_NULL,
    START_RELTIMER_PRECISION_TOO_BIG,
    START_CALLBACK_RELTIMER_PRECISION_TOO_BIG,
    VOS_FAIL_TO_ALLOC_STATIC_MEM,
    HIFI_REPORT_ERROR,
    RTC_FLOAT_MUL_32_DOT_768,
    RTC_FLOAT_MUL_DOT_32768,
    RTC_FLOAT_DIV_32_DOT_768,
    OM_APP_ICC_INIT_ERROR,
    OSA_CHECK_MEM_ERROR,
    OSA_ALLOC_TASK_CONTROL_ERROR,
    OSA_CREATE_TASK_ERROR,
    OSA_FIND_TASK_ERROR,
    OSA_FIND_TASK_PARA_ERROR,
    OSA_SET_TASK_PRI_ERROR,
    RTC_TIMER_EXPIRED_TOO_SHORT,
    CBPCA_VIAMSG_INDEX_ERROR,

    VOS_GET_DRV_VER_INFO_ERROR,

    OSA_REBOOT_MODULE_ID_BUTT = 0x1fffffff
};

/*****************************************************************************
 枚举名    : VOS_GET_DRV_VER_INFO_ENUM
 结构说明  : 获取单板类型信息枚举

  1.日    期   : 2014年11月07日
    作    者   : d00212987
    修改内容   :
*****************************************************************************/
enum VOS_GET_DRV_VER_INFO_ENUM
{
    VOS_GET_DRV_BOARD_PRODUCT_ID      = 0x00,
    VOS_GET_DRV_PROTOCOL_TYPE         = 0x01,
    VOS_GET_DRV_BOARD_TYPE            = 0x02,

    VOS_GET_DRV_VER_INFO_BUTT
};
typedef VOS_UINT32 VOS_GET_DRV_VER_INFO_ENUM_UINT32;

/*****************************************************************************
 枚举名    : PM_LOG_COSA_PAM_ENUM
 枚举说明  : PM COSA PAM主要类型

  1.日    期   : 2015年03月21日
    作    者   : s00207770
    修改内容   : PM LOG特性新增
*****************************************************************************/
enum PM_LOG_COSA_PAM_ENUM
{
    PM_LOG_COSA_PAM_TIMER   = 0x00000001,
    PM_LOG_COSA_PAM_ICC     = 0x00000002,
    PM_LOG_COSA_PAM_BUTT,
};
typedef VOS_UINT32 PM_LOG_COSA_PAM_ENUM_UINT32;

VOS_INT VOS_GetDrvVerInfo(VOS_GET_DRV_VER_INFO_ENUM_UINT32 enVerInfo);

#define VOS_SIMPLE_FATAL_ERROR(ulModel)\
    mdrv_om_system_error(ulModel, (VOS_INT)ulFileID, usLineNo, VOS_NULL_PTR, 0)

#define VOS_ProtectionReboot(modId, arg1, arg2, arg3, arg3Length)\
    mdrv_om_system_error(modId, arg1, arg2, arg3, arg3Length)

#define VOS_GetBoardProductId()\
    VOS_GetDrvVerInfo(VOS_GET_DRV_BOARD_PRODUCT_ID)

#define VOS_GetBoardType()\
    VOS_GetDrvVerInfo(VOS_GET_DRV_BOARD_TYPE)

#define VOS_SAVE_STACK(modId) (modId | (0x1 << 24))

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define DUMP_SAVE_MOD_OSA_MEM OM_AP_OSA
#else
#define DUMP_SAVE_MOD_OSA_MEM OM_CP_OSA
#endif

#define VOS_EXCH_MEM_MALLOC(length)\
    mdrv_om_register_field(DUMP_SAVE_MOD_OSA_MEM, "OAM", VOS_NULL_PTR, VOS_NULL_PTR, VOS_DUMP_MEM_ALL_SIZE, 0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _V_PRIVATE_H */

