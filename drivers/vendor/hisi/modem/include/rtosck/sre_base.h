/**
 * @file sre_base.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：RTOSck的基础头文件。 \n
 */

/** @defgroup SRE_memory  内存接口 */
/** @defgroup SRE_kernel  内核接口 */
/** @defgroup SRE_comm    通信接口 */
/** @defgroup SRE_inspect 调试接口 */
/** @defgroup v_Patch     补丁接口 */

#ifndef _SRE_BASE_H
#define _SRE_BASE_H

#include "sre_buildef.h"
#include "sre_typedef.h"
#include "sre_module.h"
#include "sre_errno.h"
#if (OS_OPTION_USR_PROCESS == YES) 
#include "sre_syscall.h"
#endif

#if (OS_OPTION_KERNEL_PROCESS == YES) 
#include "sre_k_copy.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define OS_ASSERT
#define OS_ASSERT_COND(expression)

#define ALIGN(uwAddr, uwBoundary)       (((uwAddr) + (uwBoundary) - 1) & ~((uwBoundary) - 1))
#define TRUNCATE(uwAddr, uwSize)        ((uwAddr) & ~((uwSize) - 1))

#define READ_UINT8(ucValue, ucArg)                          ucValue = (UINT8)(ucArg)
#define READ_UINT16(usValue, usArg)                         usValue = (UINT16)(usArg)
#define READ_UINT32(uwValue, uwArg)                         uwValue = (UINT32)(uwArg)
#define READ_UINT64(ullValue, ullArg)                       ullValue = (UINT64)(ullArg)
#define GET_UINT8(ucArg)                                    (UINT8)(ucArg)
#define GET_UINT16(usArg)                                   (UINT16)(usArg)
#define GET_UINT32(uwArg)                                   (UINT32)(uwArg)
#define GET_UINT64(ullArg)                                  (UINT64)(ullArg)
#define WRITE_UINT8(ucArg, ucValue)                         ucArg = (UINT8)(ucValue)
#define WRITE_UINT16(usArg, usValue)                        usArg = (UINT16)(usValue)
#define WRITE_UINT32(uwArg, uwValue)                        uwArg = (UINT32)(uwValue)
#define WRITE_UINT64(ullArg, ullValue)                      ullArg = (UINT64)(ullValue)

/**
 * @ingroup  SRE_sys
 * 从线程PID获取核内线程handle号
 */
#define GET_HANDLE(pid)               ((pid)&0x000000FF)

/**
 * @ingroup  SRE_sys
 * 硬中断核内线程handle号
 */
#define OS_HWI_HANDLE                 0X000000FF

/**
 * @ingroup  SRE_sys
 * 从线程PID获取核号
 */
#define GET_COREID(pid)               ((UINT8)(((pid)&0x0000FF00) >> 8))
/**
 * @ingroup  SRE_sys
 * 将coreid与handle组成PID
 */
#define COMPOSE_PID(coreid, handle)   ((((UINT32)(coreid))<<8) + ((UINT8)(handle))) /* 将coreid与handle组成PID,UIPC不使用该接口 */
/**
 * @ingroup  SRE_sys
 * 核间功能模块的未初始化标志位
 */
#define OS_MC_PHASE_UNINIT                                  0
/**
 * @ingroup  SRE_sys
 * 核间功能模块的正在初始化标志位
 */
#define OS_MC_PHASE_HANDLE                                  0xae1234ea
/**
 * @ingroup  SRE_sys
 * 核间功能模块的初始化完成标志位
 */
#define OS_MC_PHASE_INITED                                  0xad5678da

/**
 * @ingroup  SRE_sys
 *核间信号量、信号量、消息等待时间设定：表示不等待。
 */
#define OS_NO_WAIT            0

/**
 * @ingroup  SRE_sys
 * CpuTick结构体类型。
 *
 * 用于记录64位的cycle计数值。
 */
typedef struct tagCpuTick
{
    UINT32 uwCntHi;         /**<  cycle计数高32位 */
    UINT32 uwCntLo;         /**<  cycle计数低32位 */
} CPU_TICK;

/**
 * @ingroup SRE_sys
 * 矢量寄存器保护区域结构体。
 *
 */
typedef struct tagCpSaveCfgParam
{
    VOID *pSaveAreaA;            /**< coprocessor上下文保存区域的大小 */
    VOID *pSaveAreaB;            /**< coprocessor上下文保存区域的大小 */
} CP_SAVE_CFG_PARAM_S;

/**
 * @ingroup  SRE_sys
 * @brief 开中断。
 *
 * @par 描述:
 * 开启全局可屏蔽中断。
 *
 * @attention 中断服务函数里慎用该接口，会引起中断优先级反转
 *
 * @param 无
 *
 * @retval 开启全局中断前的中断状态值。
 * @par 依赖:
 * <ul><li>sre_base.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_IntLock | SRE_IntRestore
 */
#ifndef _WIN32

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

OS_SEC_ALW_INLINE INLINE UINTPTR SRE_IntUnLock(VOID)
{
    UINTPTR uvIntSave;
    __asm__ __volatile("mrs %0, cpsr"
            :"=r"(uvIntSave));
    __asm__ __volatile("cpsie i");
    return uvIntSave;
}
#else
extern UINTPTR SRE_IntUnLock(VOID);
#endif

/**
 * @ingroup  SRE_sys
 * @brief 关中断。
 *
 * @par 描述:
 * 关闭全局可屏蔽中断。
 *
 * @attention 在关全局中断后，禁止调用引起内核调度的相关接口，如SRE_TaskDelay接口
 *
 * @param 无
 *
 * @retval 关闭全局中断前的中断状态值。
 * @par 依赖:
 * <ul><li>sre_base.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_IntUnLock | SRE_IntRestore
 */
 
#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
OS_SEC_ALW_INLINE INLINE UINTPTR SRE_IntLock(VOID)
{
    UINTPTR uvIntSave;
    __asm__ __volatile("mrs %0, cpsr" : "=r"(uvIntSave));
    __asm__ __volatile("cpsid i");
    return uvIntSave;
}
#else
extern UINTPTR SRE_IntLock(VOID);
#endif
/**
 * @ingroup  SRE_sys
 * @brief 恢复中断状态接口。
 *
 * @par 描述:
 * 恢复原中断状态寄存器。
 *
 * @attention
 *<ul>
 *<li>该接口必须和关闭全局中断或者是开启全局中断接口成对使用，以关全局中断或者开全局中断操作的返回值为入参</li>
 *<li>以保证中断可以恢复到关全局中断或者开全局中断操作前的状态</li>
 *</ul>
 * @param  uvIntSave [IN]类型#UINTPTR，关全局中断SRE_IntLock和开全局中断SRE_IntUnLock的返回值。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_base.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_IntUnLock | SRE_IntLock
 */
#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
OS_SEC_ALW_INLINE INLINE VOID SRE_IntRestore(UINTPTR uvIntSave)
{
    __asm__ __volatile__(
        "MSR     cpsr_c, %0"
        : :"r"(uvIntSave));

}
#else
extern VOID SRE_IntRestore(UINTPTR uvIntSave);
#endif
#else
extern UINTPTR SRE_IntLock(VOID);
extern UINTPTR SRE_IntUnLock(VOID);
extern VOID SRE_IntRestore(UINTPTR uvIntSave);
#endif


/**
 * @ingroup  SRE_sys
 * @brief 获取当前的64位cycle计数,cycle计数的高32位保存到参数puwCntHi，低32为保存到参数puwCntLo。
 *
 * @par 描述:
 * 获取当前的64位cycle计数,cycle计数的高32位保存到参数puwCntHi，低32为保存到参数puwCntLo。
 *
 * @attention
 *<ul>
 *<li>入参指针不能为NULL，由用户保证。</li>
 *<li>Cortex-AX平台不支持此功能。</li>
 *</ul>
 *
 * @param  puwCntHi [OUT]类型#UINT32 *，保存cycle计数的高32位。
 * @param  puwCntLo [OUT]类型#UINT32 *，保存cycle计数的低32位。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_base.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_CycleCountGet64()
 */
extern VOID SRE_CycleCountGet(UINT32 *puwCntHi, UINT32 *puwCntLo);

/**
 * @ingroup  SRE_sys
 * @brief 获取当前的64位time stamp计数(即系统运行的cycles)。
 *
 * @par 描述:
 * 获取当前的64位time stamp计数(即系统运行的cycles)。
 *
 * @attention
 *<ul>
 *<li>获取的是64bit cycles 数据。</li>
 *<li>Cortex-AX平台不支持此功能。</li>
 *</ul>
 *
 * @param  无
 *
 * @retval [0,0xFFFFFFFFFFFFFFFF] 系统当前的cycle数
 * @par 依赖:
 * <ul><li>sre_base.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_CycleCountGet32()
 */
extern UINT64 SRE_CycleCountGet64(VOID);

/**
 * @ingroup  SRE_sys
 * @brief 获取当前的32位time stamp计数(即系统运行的cycles)。
 *
 * @par 描述:
 * 获取当前的32位time stamp计数(即系统运行的cycles)。
 *
 * @attention
 *<ul>
 *<li>获取的是32bit cycles 数据。</li>
 *<li>若两次获取时间过长，会发生数据翻转现象，此情况下建议使用获取64bit数据接口。</li>
 *<li>Cortex-AX平台不支持此功能。</li>
 *</ul>
 *
 * @param  无
 *
 * @retval [0,0xFFFFFFFF]  系统当前的cycle数
 * @par 依赖:
 * <ul><li>sre_base.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_CycleCountGet64()
 */
#ifndef _TOOL_WIN32
#if ( (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) )

OS_SEC_ALW_INLINE INLINE UINT32 SRE_CycleCountGet32()
{
    UINT32 uwCCOUNT;
    __asm__ __volatile__( "rsr %0, ccount" : "=a" (uwCCOUNT) );

    return uwCCOUNT;
}
#elif(OS_HARDWARE_PLATFORM == OS_HIDSP)
OS_SEC_ALW_INLINE INLINE UINT32 SRE_CycleCountGet32()
{
    UINT32 uwCCOUNT;
    __asm__ __volatile__( "ccount %0" : "=r" (uwCCOUNT) );

    return uwCCOUNT;
}
#else
extern UINT32    SRE_CycleCountGet32(VOID);
#endif

/**
 * @ingroup  SRE_sys
 * @brief 等待内存操作完成。
 *
 * @par 描述:
 * 等待操作完成。
 *
 * @attention
 * <ul>
 * <li>支持Xtensa和SD6183平台。</li>
 * <li>多核之间操作内存，建议使用这个接口保证数据的一致性。</li>
 * </ul>
 *
 *@param 无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
#if ( (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) )
OS_SEC_ALW_INLINE INLINE VOID SRE_MemWait(VOID)
{
    __asm__ __volatile__( "memw");
}
#elif(OS_HARDWARE_PLATFORM == OS_HIDSP)
OS_SEC_ALW_INLINE INLINE VOID SRE_MemWait(VOID)
{
    __asm__ __volatile__("sync");
}
#endif
#else
OS_SEC_ALW_INLINE INLINE UINT32 SRE_CycleCountGet32()
{
    return SRE_OK;
}

OS_SEC_ALW_INLINE INLINE VOID SRE_MemWait(VOID)
{
    return;
}
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_BASE_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

