/**
 * @file sre_tskmon.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：任务监控模块的对外头文件。 \n
 */

/**
 *@defgroup SRE_tskmon 任务监控
 *@ingroup SRE_kernel
 */

#ifndef _SRE_TSKMON_H
#define _SRE_TSKMON_H

#include "sre_base.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

//支持功能宏裁剪,sre_buildef.h文件中支持的功能宏
#if (OS_OPTION_TASK_MON == YES) 

/* =================================任务监控模块常量定义============================== */
/**
 *@ingroup SRE_tskmon
 *代表所有任务ID
 */
#define  OS_TSK_ALL                  0xFFFFFFFF

/**
 *@ingroup SRE_tskmon
 *撑死处理模式：上报致命错误
 */
#define  OS_TSKMON_MODE_REPORT_ERROR 0x01

/**
 *@ingroup SRE_tskmon
 *撑死处理模式：挂起任务
 */
#define  OS_TSKMON_MODE_REAVE        0x02

/**
 *@ingroup SRE_tskmon
 *信息类型:任务撑死
 */
#define TSKMON_INFO_TYPE_OVERRUN     0x01

/**
 *@ingroup SRE_tskmon
 *信息类型:任务饿死
 */
#define TSKMON_INFO_TYPE_STRVATION   0x02

/**
 *@ingroup SRE_tskmon
 *无效指针
 */
#define OS_INVALID_HOOK              NULL

/* =================================任务监控模块错误码定义============================== */
/**
 *@ingroup SRE_tskmon
 *初始化时申请内存失败
 *
 * 值: 0x02000830
 *
 *解决方案:请打开任务监控模块相应开关
 */
#define OS_ERRNO_TSKMON_NO_MEMORY        SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x30)

/**
 *@ingroup SRE_tskmon
 *撑死检测功能未启用
 *
 * 值: 0x02000831
 *
 *解决方案:请打开任务监控模块相应开关
 */
#define OS_ERRNO_TSK_OVERRUN_UNINSTALL   SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x31)

/**
 *@ingroup SRE_tskmon
 *饿死检测功能未启用
 *
 * 值: 0x02000832
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_STRVATION_UNINSTALL SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x32)

/**@ingroup SRE_tskmon
 *已经加入了撑死检测队列
 *
 * 值: 0x02000833
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_OVERRUNCK_EXIST     SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x33)

/**@ingroup SRE_tskmon
 *未加入撑死检测
 *
 * 值: 0x02000834
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_OVERRUNCK_UNEXIST   SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x34)

/**@ingroup SRE_tskmon
 *已经加入了饿死检测队列
 *
 * 值: 0x02000835
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_STRVATIONCK_EXIST   SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x35)

/**@ingroup SRE_tskmon
 *未加入饿死检测
 *
 * 值: 0x02000836
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_STRVATIONCK_UNEXIST SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x36)

/**@ingroup SRE_tskmon
 *任务撑死挂起，不允许取消检测
 *
 * 值: 0x02000837
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_OVERRUN_SUPPEND     SRE_ERRNO_OS_ERROR(OS_MID_TSK,0x37)

/**@ingroup SRE_tskmon
 *任务撑死后，用户配置处理方式为上报致命错误
 *
 * 值: 0x03000838
 *
 *解决方案:无
 */
#define OS_ERRNO_TSK_OVERRUN             SRE_ERRNO_OS_FATAL(OS_MID_TSK,0x38)


/* =================================任务监控模块数据结构类型定义============================== */
/**@ingroup SRE_tskmon
 *任务死循环检测配置信息数据结构类型定义
 */
typedef struct tagTskMonModInfo
{
    UINT32 uwThresHold;                                    /**< 阀值，以tick为单位。 */
    UINT32 uwProcType;                                     /**< 处理模式 */
} TSKMON_MOD_INFO_S;

/**@ingroup SRE_tskmon
 * 任务死循环监控信息数据结构定义
 */
typedef struct tagTskMonInfo
{
    UINT32 uwTaskPID;                                      /**< 任务PID*/
    UINT16 usSize;                                         /**< 信息长度*/
    UINT16 usType;                                         /**< 信息类型*/
    UINT32 uwTickCnt;                                      /**< 任务运行时长*/
}TSKMON_INFO_S;

/**
 * @ingroup  SRE_tskmon
 * @brief 任务监控回调函数类型定义
 *
 * @par 描述:
 * 通过任务监控回调函数类型定义任务监控回调函数，任务在撑死和饿死时调用该钩子进行处理
 *
 * @attention
 * 无
 *
 * @param  para   [IN] 类型#TSKMON_INFO_S*，任务死循环监控信息。
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>sre_tskmon.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C02
 * @see 无。
 */
typedef VOID (*TSKMON_HOOK_FUNC)(TSKMON_INFO_S*);

/* =================================任务监控模块接口类型定义============================== */

/**
 * @ingroup  SRE_tskmon
 * @brief 任务加入撑死检测
 *
 * @par 描述:
 * 设定指定任务的监控控制块撑死标志，把该任务加入撑死检测。如果参数为OS_TSK_ALL表示所有任务都加入撑死检测。
 *
 * @attention  无
 *
 * @param  uwTaskPID   [IN] 类型#UINT32，任务PID。
 *
 * @retval #SRE_OK                              0x00000000，注册成功
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，传入的PID为IDLE任务PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务ID无效
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A，任务未创建
 * @retval #OS_ERRNO_TSK_OVERRUNCK_EXIST        0x02000833，任务已经加入撑死检测，不允许重复加入
 * @retval #OS_ERRNO_TSK_OVERRUN_UNINSTALL      0x02000831，撑死检测裁剪开关未打开,撑死检测未启用
 * @par 依赖:
 * <ul><li>sre_tskmon.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonOverrunExclude
 */
extern UINT32 SRE_TskMonOverrunInclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief 取消任务撑死检测
 *
 * @par 描述:
 * 清除任务监控控制块的撑死标志，取消对该任务撑死检测。如果参数为OS_TSK_ALL表示取消所有任务的撑死检测。
 *
 * @attention  无
 *
 * @param  uwTaskPID   [IN] 类型#UINT32，任务PID。
 *
 * @retval #SRE_OK                              0x00000000，注册成功
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，传入的PID为IDLE任务PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务ID无效
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A，任务未创建
 * @retval #OS_ERRNO_TSK_OVERRUNCK_UNEXIST      0x02000834，任务未入撑死检测，不运行取消操作
 * @retval #OS_ERRNO_TSK_OVERRUN_UNINSTALL      0x02000831，撑死检测裁剪开关未打开，撑死检测未启用
 * @retval #OS_ERRNO_TSK_OVERRUN_SUPPEND        0x02000837, 任务撑死挂起不允许取消检测
 * @par 依赖:
 * <ul><li>sre_tskmon.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonOverrunInclude
 */
extern UINT32 SRE_TskMonOverrunExclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief 任务加入饿死检测
 *
 * @par 描述:
 * 设定指定任务的监控控制块饿死标志，把该任务加入饿死检测。如果参数为OS_TSK_ALL表示所有任务都加入饿死检测。
 *
 * @attention  无
 *
 * @param  uwTaskPID   [IN] 类型#UINT32，任务PID。
 *
 * @retval #SRE_OK                              0x00000000，注册成功
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，传入的PID为IDLE任务PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID无效
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A，任务未创建
 * @retval #OS_ERRNO_TSK_STRVATIONCK_EXIST      0x02000835，任务已经加入饿死检测
 * @retval #OS_ERRNO_TSK_STRVATION_UNINSTALL    0x02000832，饿死检测裁剪开关未打开，饿死检测未启用
 * @par 依赖:
 * <ul><li>sre_tskmon.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonStrvationExclude
 */
extern UINT32 SRE_TskMonStrvationInclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief 任务取消饿死检测
 *
 * @par 描述:
 * 清除任务监控控制块的饿死标志，取消对该任务饿死检测。如果参数为OS_TSK_ALL表示取消所有任务的饿死检测。
 *
 * @attention  无
 *
 * @param  uwTaskPID   [IN] 类型#UINT32，任务PID。
 *
 * @retval #SRE_OK                              0x00000000，注册成功
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，传入的PID为IDLE任务PID
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID无效
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080A，任务未创建
 * @retval #OS_ERRNO_TSK_STRVATIONCK_UNEXIST    0x02000836，任务未加入饿死检测
 * @retval #OS_ERRNO_TSK_STRVATION_UNINSTALL    0x02000832，饿死检测裁剪开关未打开，饿死死检测未启用
 * @par 依赖:
 * <ul><li>sre_tskmon.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C02
 * @see SRE_TskMonStrvationInclude
 */
extern UINT32 SRE_TskMonStrvationExclude(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_tskmon
 * @brief 注册任务监控的检测信息回调函数。
 *
 * @par 描述:
 * 注册任务检测信息回调函数，当检测到任务撑死或饿死时，系统通过回调函数告知用户。<br/>
 * @attention
 * <ul>
 * <li>在注册的回调函数中，不要进行锁任务操作，否则会影响到系统的正常任务调度。</li>
 * </ul>
 *
 * @param  pfnHook         [IN] 类型#TSKMON_HOOK_FUNC，任务检测回调函数，若为NULL，表示清除回调钩子。
 *
 * @retval #SRE_OK                          0x00000000，注册成功
 * @par 依赖:
 * <ul><li>sre_tskmon.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C02
 * @see 无
 */
extern UINT32 SRE_TskMonHookReg(TSKMON_HOOK_FUNC  pfnHook);

#endif //if (OS_OPTION_TASK_MON == YES) 

#ifdef __cplusplus
 #if __cplusplus
}
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_TSKMON_H */

