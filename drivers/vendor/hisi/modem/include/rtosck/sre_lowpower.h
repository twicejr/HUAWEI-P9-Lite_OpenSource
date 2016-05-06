/**
 * @file sre_lowpower.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：低功耗相关模块的对外头文件。 \n
 */

 /**@defgroup SRE_lowpower 硬件支持
   *@ingroup SRE_kernel
 */

#ifndef _SRE_LOWPOWER_H
#define _SRE_LOWPOWER_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_lowpower
 *  硬件相关信息错误码：低功耗保存或者恢复输入的类型不正确。
 *
 * 值: 0x02004001
 *
 * 解决方案: 请确保传入的类型合法。
 */
#define OS_ERRNO_LOWPOWER_TYPE_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x01)

/**
 * @ingroup SRE_lowpower
 *  硬件相关信息错误码：低功耗suspend或者Resume GIC时，GIC未初始化。
 *
 * 值: 0x02004002
 *
 * 解决方案: 低功耗suspend或者Resume GIC时，请保证GIC已经初始化。
 */
#define OS_ERRNO_LOWPOWER_GIC_NOT_INIT                SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x02)

/**
 * @ingroup SRE_lowpower
 *  硬件相关信息错误码：低功耗Suspend GIC时，系统已经Suspend。
 *
 * 值: 0x02004003
 *
 * 解决方案: 低功耗Suspend GIC时，请保证系统未Suspend。
 */
#define OS_ERRNO_LOWPOWER_GIC_ALREADY_SUSPENDED       SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x03)

/**
 * @ingroup SRE_lowpower
 *  硬件相关信息错误码：低功耗Resume GIC时，系统未suspend。
 *
 * 值: 0x02004004
 *
 * 解决方案: 低功耗Resume GIC时，请保证系统已经suspend。
 */
#define OS_ERRNO_LOWPOWER_GIC_NOT_SUSPENDED           SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x04)

/**
 * @ingroup SRE_lowpower
 *  硬件相关信息错误码：低功耗Suspend GIC时，存在未处理的中断。
 *
 * 值: 0x02004005
 *
 * 解决方案: 低功耗Suspend GIC时，请保证系统所有中断已经被处理。
 */
#define OS_ERRNO_LOWPOWER_GIC_PENDING_INTERRUPT       SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x05)


/**
 * @ingroup SRE_lowpower
 * 低功耗suspend和resume模块编号。
 */
typedef  enum
{
    LOW_POWER_TYPE_L2CACHE = 0,     /**< L2 Cache模块ID */
    LOW_POWER_TYPE_GIC,             /**< GIC模块ID      */
    LOW_POWER_TYPE_BUIT
}OS_LOW_POWER_TYPE_S;


#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_lowpower
 * @brief 低功耗。
 *
 * @par 描述:
 * 根据enLPType的类型，进行低功耗Suspend，以保存相关信息。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能。</li>
 * <li>需要在进入低功耗前调用此接口。</li>
 * </ul>
 *
 * @param  enLowPowerType   [IN] 类型#OS_LOW_POWER_TYPE_S，低功耗suspend和resume模块类型。
 *
 * @retval #OS_ERRNO_LOWPOWER_TYPE_INVALID            0x02004001，传入的低功耗suspend模块类型不合法。
 * @retval #OS_ERRNO_LOWPOWER_GIC_NOT_INIT            0x02004002，低功耗Suspend GIC时，GIC未初始化。
 * @retval #OS_ERRNO_LOWPOWER_GIC_ALREADY_SUSPENDED   0x02004003，低功耗Suspend GIC时，GIC已经被Suspended。
 * @retval #OS_ERRNO_LOWPOWER_GIC_PENDING_INTERRUPT   0x02004005，低功耗Suspend GIC时，系统存在未处理的中断。
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT                0x02001114，必须在L2 Cache初始化后调用此接口。
 * @retval #OS_ERRNO_L2_CACHE_ALREADY_SUSPENDED       0x02001116，L2 Cache已经被Suspend。
 * @retval #SRE_OK                                    0x00000000，低功耗Suspend成功。
 * @par 依赖:
 * <ul><li>sre_lowpower.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_LowPowerSuspend(OS_LOW_POWER_TYPE_S enLowPowerType);

/**
 * @ingroup  SRE_lowpower
 * @brief 低功耗。
 *
 * @par 描述:
 * 根据enLPType的类型，进行低功耗Resume，以恢复相关信息。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能。</li>
 * <li>需要在唤醒低功耗后调用此接口。</li>
 * </ul>
 *
 * @param  enLowPowerType   [IN] 类型#OS_LOW_POWER_TYPE_S，低功耗suspend和resume模块类型。
 *
 * @retval #OS_ERRNO_LOWPOWER_TYPE_INVALID            0x02004001，传入的低功耗Resume模块类型不合法。
 * @retval #OS_ERRNO_LOWPOWER_GIC_NOT_INIT            0x02004002，低功耗Resume GIC时，GIC未初始化。
 * @retval #OS_ERRNO_LOWPOWER_GIC_NOT_SUSPENDED       0x02004004，低功耗Resume GIC时，GIC未Suspended。
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT                0x02001114，必须在L2 Cache初始化后调用此接口。
 * @retval #OS_ERRNO_L2_CACHE_NOT_SUSPENDED           0x02001117，L2 Cache未Suspend。
 * @retval #SRE_OK                                    0x00000000，低功耗Suspend成功。
 * @par 依赖:
 * <ul><li>sre_lowpower.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_LowPowerResume(OS_LOW_POWER_TYPE_S enLowPowerType);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */



