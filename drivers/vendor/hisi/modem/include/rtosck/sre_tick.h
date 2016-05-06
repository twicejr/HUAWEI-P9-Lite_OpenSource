/**
 * @file sre_tick.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：Tick中断的对外头文件。 \n
 */

 /** @defgroup SRE_tick Tick中断
 *@ingroup SRE_interrupt
 */

#ifndef _SRE_TICK_H
#define _SRE_TICK_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_tick
 * Tick中断模块配置信息的结构体定义。
 *
 * 保存Tick中断模块的配置项信息。
 */
typedef struct tagTickModInfo
{
    UINT32 uwTickPerSecond;                                 /**< 每秒产生的TICK中断数       */
} TICK_MOD_INFO_S;

/**
 * @ingroup SRE_tick
 * Tick中断错误码：tick在申请硬件定时器物理资源时资源不足，申请不到。
 *
 * 值: 0x02000b02
 *
 * 解决方案:确保有足够的定时器物理资源
 */
#define OS_ERRNO_TICK_NO_HWTIMER                            SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x02)

/**
 * @ingroup SRE_tick
 * Tick中断错误码：Cortex-AX平台在调整Tick计数值时，输入的补偿值总大小为负值且绝对值大于正常的Tick计数值。
 *
 * 值: 0x02000b03
 *
 * 解决方案:确保调整Tick计数值时，输入的补偿值总大小为负值时且它的绝对值不能大于正常的Tick计数值
 */
#define OS_ERRNO_TICK_ADJUST_VALUE_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x03)

/**
 * @ingroup SRE_tick
 * Tick中断错误码：Cortex-MX tick的周期错误
 *
 * 值: 0x02000b04
 *
 * 解决方案:确认经过转换后的tick周期(多少cycle/tick)是否区间(0,0x00FFFFFF]内。
 */
#define OS_ERRNO_TICK_PERIOD                                SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x04)

/**
 * @ingroup SRE_tick
 * Tick中断错误码：每秒的Tick中断计数配置不合法。
 *
 * 值: 0x02000b05
 *
 * 解决方案:确保配置的每秒Tick中断计数小于系统时钟数，并且不等于0。
 */
#define OS_ERRNO_TICK_PER_SECOND_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x05)

/**
 * @ingroup  SRE_tick
 * @brief Tick中断处理函数。
 *
 * @par 描述:
 * Tick中断处理函数。
 *
 * @attention
 * <ul>
 * <li>当前仅Cortex-AX平台有效。</li>
 * <li>只有在Tick中断源由用户提供，并在Tick中断处理中调用有效。若在非tick中断处理函数中调用，可能引发tick时钟不准确</li>
 * <li>Tick模块裁剪开关未打开，调用此接口无效。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>sre_tick.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern VOID SRE_TickISR(VOID);

/**
 * @ingroup  SRE_tick
 * @brief 获取每秒钟对应的Tick数。
 *
 * @par 描述:
 * 获取每秒钟时间内触发的Tick中断次数。
 *
 * @attention 无
 *
 * @param  无
 *
 * @retval #[0,0xFFFFFFFF]  每秒钟对应的Tick数。
 * @par 依赖:
 * <ul><li>sre_tick.h：该接口声明所在的头文件。</li></ul>
 * @since UniDSP V100R001C01
 * @see SRE_TickCountGet
 */
extern UINT32 SRE_TickPerSecondGet(VOID);

/**
 * @ingroup  SRE_tick
 * @brief 调整Tick计数值。
 *
 * @par 描述:
 * 调整Tick计数值。
 *
 * @attention
 * 该功能接口仅作统计使用（只影响SRE_TickCountGet返回值），不做调度行为控制（即不影响Task Delay，软件定时器，信号量/消息/时间延时等待）。
 *
 * @param  swTick [IN] 类型#INT32，Tick计数补偿值，取值范围[-2^31,2^31 - 1]。
 *
 * @retval #OS_ERRNO_TICK_ADJUST_VALUE_INVALID  0x02000b03    Tick计数总补偿值为负数，并且绝对值大于实际的Tick计数值。
 * @retval #SRE_OK                              0x00000000    调整Tick计数值成功。
 * @par 依赖:
 * <ul><li>sre_tick.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_TickCountGet
 */
extern UINT32 SRE_TickCountAdjust(INT32 swTick);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_TICK_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

