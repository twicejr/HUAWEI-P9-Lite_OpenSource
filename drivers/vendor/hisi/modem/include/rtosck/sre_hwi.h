/**
 * @file sre_hwi.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：硬中断模块的对外头文件。 \n
 */

 /**@defgroup SRE_interrupt 中断
   *@ingroup SRE_kernel
 */
 /** @defgroup SRE_hwi 硬中断
  *@ingroup SRE_interrupt
 */

#ifndef _SRE_HWI_H
#define _SRE_HWI_H

#include "sre_base.h"
#include "sre_hook.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_hwi
 * 可用的硬中断优先级的宏定义。
 *
 * SD6108和SD6181的优先级为1-6，SD6182/SD6157的优先级为1-5，数值越大优先级越高，Tensilica平台下优先级由硬件固定；
 * 而Cortex-AX的优先级为0-31，SD6183的优先级为1-7。
 *
 *
 * N: Invalid Priority
 * Y: Valid Priority
 * NMI: Non-Maskable Interrupt
 */
 /*************************************************<SD6108/6181>*****<SD6182/SD6157>*****<SD6183>*****<Cortex-AX>***/
#define SRE_HWI_PRIORITY0             0    /*       N                 N                   Y            Y           */
#define SRE_HWI_PRIORITY1             1    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY2             2    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY3             3    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY4             4    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY5             5    /*       Y                 NMI                 Y            Y           */
#define SRE_HWI_PRIORITY6             6    /*       NMI               N                   Y            Y           */
#define SRE_HWI_PRIORITY7             7    /*       N                 N                   Y            Y           */
#define SRE_HWI_PRIORITY8             8    /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY9             9    /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY10            10   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY11            11   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY12            12   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY13            13   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY14            14   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY15            15   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY16            16   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY17            17   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY18            18   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY19            19   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY20            20   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY21            21   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY22            22   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY23            23   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY24            24   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY25            25   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY26            26   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY27            27   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY28            28   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY29            29   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY30            30   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY31            31   /*       N                 N                   N            Y           */

/**
 * 硬中断模式的宏定义。
 */

/**
 * @ingroup SRE_hwi
 * 组合型硬中断。
 */
#define OS_HWI_MODE_COMBINE                                 0x8000

/**
 * @ingroup SRE_hwi
 * 独立型硬中断。
 */
#define OS_HWI_MODE_ENGROSS                                 0x4000

/**
 * @ingroup SRE_hwi
 * 缺省硬中断模式。
 */
#define OS_HWI_MODE_DEFAULT                                 OS_HWI_MODE_ENGROSS

/**
 * @ingroup SRE_hwi
 * 作为使能或屏蔽所有硬中断函数的入参，仅Tensilica平台有效。
 */
#define OS_HWI_ALL                                          0x7fff

/*
 * 硬中断模块的错误码定义。
 */

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：中断号非法。
 *
 * 值: 0x02001400
 *
 * 解决方案：确保中断号合法，Tensilica:[0,31]，Cortex-AX平台Balong产品:[0,255]，Cortex-AX平台ISP产品:[0,511]，SD6183:[34,51],[55,58],[64,103],[124,127]。
 */
#define OS_ERRNO_HWI_NUM_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x00)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：优先级非法。
 *
 * 值: 0x02001401
 *
 * 解决方案：确保优先级合法，Tensilica:优先级忽略，Cortex-AX:[0,31]，SD6183:[1,7]。
 */
#define OS_ERRNO_HWI_PRI_ERROR                              SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x01)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：硬中断已被创建或相应中断向量号已被其它中断占用。
 *
 * 值: 0x02001402
 *
 * 解决方案：更换中断号
 */
#define OS_ERRNO_HWI_ALREADY_CREATED                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x02)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：硬中断处理函数为空。
 *
 * 值: 0x02001403
 *
 * 解决方案：传入非空的有效处理函数
 */
#define OS_ERRNO_HWI_PROC_FUNC_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x03)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：未创建的硬中断被响应。
 *
 * 值: 0x03001404
 *
 * 解决方案：先创建硬中断，然后使能并触发该中断使其得到响应
 */
#define OS_ERRNO_HWI_UNCREATED                              SRE_ERRNO_OS_FATAL(OS_MID_HWI, 0x04)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：删除TICK中断。
 *
 * 值: 0x02001405
 *
 * 解决方案：不允许删除tick中断
 */
#define OS_ERRNO_HWI_DELETE_TICK_INT                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x05)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：设置硬中断属性时，属性设置与之前设置值不一致
 *
 * 值: 0x02001406
 *
 * 解决方案：确认当前设置属性值与之前是否一致。如果确需修改属性，请先删除该硬中断。
 */
#define OS_ERRNO_HWI_ATTR_CONFLICTED                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x06)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：组合型中断创建失败，为组合型中断节点申请系统默认私有FSC内存失败。
 *
 * 值: 0x02001408
 *
 * 解决方案: 增大系统默认私有FSC分区大小
 */
#define OS_ERRNO_HWI_MEMORY_ALLOC_FAILED                    SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x08)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：组合型中断函数注册失败，该组合型中断已创建了相同的中断处理函数。
 *
 * 值: 0x02001409
 *
 * 解决方案: 更换中断处理函数
 */
#define OS_ERRNO_HWI_COMBINEHOOK_ALREADY_CREATED            SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x09)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：创建的中断函数即不是独立型，也不是组合型，或者SD6183平台配置的中断模式既不是边沿型也不是电平型。
 *
 * 值: 0x0200140a
 *
 * 解决方案: 硬中断模式只能设置为独立型或组合型，另外SD6183平台配置的中断模式必须是边沿型或者电平型
 */
#define OS_ERRNO_HWI_MODE_ERROR                             SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0a)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：删除未创建或者已经被删除的硬中断。
 *
 * 值: 0x0200140b
 *
 * 解决方案: 删除已创建并且未被删除的硬中断
 */
#define OS_ERRNO_HWI_DELETED                                SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0b)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：未进行硬中断模式设置。
 *
 * 值: 0x0200140c
 *
 * 解决方案: 调用中断创建函数前，需要先调用中断模式设置函数，进行模式参数设置
 */
#define OS_ERRNO_HWI_MODE_UNSET                             SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0c)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：硬中断触发接口入参错误，输入无效的核号。
 *
 * 值: 0x0200140d
 *
 * 解决方案: 输入本核核号
 */
#define OS_ERRNO_HWI_CORE_ID_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0d)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：硬中断软件不可触发。
 *
 * 值: 0x0200140e
 *
 * 解决方案: SD6182的CPU,DSP,HAC CC核，SD6157的CPU,DSP核及SD6181/SD6108的CPU核只有7号可以软件触发，SD6181/SD6108的DSP核7号与11号可以软件触发，SD6183平台124~127号可以软件触发
 */
#define OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD                  SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0e)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：删除SD6182/SD6157/SD6183 MSGM中的HPQ中断。
 *
 * 值: 0x0200140f
 *
 * 解决方案：SD6182/SD6157/SD6183 MSGM中的HPQ中断为OS内部使用，不能删除。
 */
#define OS_ERRNO_HWI_DELETE_MSGM_HPQ_INT                    SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0f)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：Cortex-AX硬件上报错误中断，上报的中断号大于0x1FF。
 *
 * 值: 0x02001410
 *
 * 解决方案：无。
 */
#define OS_ERRNO_HWI_HW_REPORT_HWINO_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x10)

/**
 * @ingroup SRE_hwi
 * 硬中断错误码：入参为空
 *
 * 值: 0x02001411
 *
 * 解决方案：无。
 */
#define OS_ERRNO_HWI_PARAM_NULL                             SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x11)

/**
 * @ingroup SRE_hwi
 * 硬中断号的类型定义。
 */
typedef UINT32                                              HWI_HANDLE_T;

/**
 * @ingroup SRE_hwi
 * 硬中断优先级的类型定义。
 */
typedef UINT16                                              HWI_PRIOR_T;

/**
 * @ingroup SRE_hwi
 * 硬中断模式配置信息的类型定义。
 */
typedef UINT16                                              HWI_MODE_T;

/**
 * @ingroup SRE_hwi
 * 硬中断处理函数的参数类型定义。
 */
typedef UINT32                                              HWI_ARG_T;

/**
* @ingroup  SRE_hwi
* @brief 硬中断处理函数的类型定义。
*
* @par 描述:
* 通过硬中断处理函数的类型定义硬中断处理函数，在硬中断触发时调用该中断处理函数。
*
* @attention 无。
*
* @param  uwParam1 [IN] 类型#HWI_ARG_T，硬中断处理函数的参数。
*
* @retval 无。
* @par 依赖:
* <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see 无。
*/
typedef VOID (* HWI_PROC_FUNC)(HWI_ARG_T);


/**
* @ingroup  SRE_hwi
* @brief 硬中断调用处理函数钩子函数类型定义。
*
* @par 描述:
* 用户通过硬中断调用钩子处理函数类型定义硬中断调用处理函数钩子，在硬中断调用处理函数时，调用该钩子。
* @attention 无。
*
* @param  uwHwiNum [IN] 类型#UINT32，硬中断号。
*
* @retval 无。
* @par 依赖:
* <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R002C00
* @see SRE_HwiEntryHookAdd | SRE_HwiEntryHookDel | SRE_HookAdd | SRE_HookDel
*/
typedef VOID (* HWI_ENTRY_HOOK)(UINT32 uwHwiNum);

/**
* @ingroup  SRE_hwi
* @brief 硬中断退出处理函数钩子函数类型定义。
*
* @par 描述:
* 用户通过硬中断退出钩子处理函数类型定义硬中断退出处理函数钩子，在硬中断退出处理函数时，调用该钩子。
* @attention 无。
*
* @param  uwHwiNum [IN] 类型#UINT32，硬中断号。
*
* @retval 无。
* @par 依赖:
* <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R002C00
* @see SRE_HwiExitHookAdd | SRE_HwiExitHookDel | SRE_HookAdd | SRE_HookDel
*/
typedef VOID (* HWI_EXIT_HOOK)(UINT32 uwHwiNum);

/**
 * @ingroup  SRE_hwi
 * @brief 设置硬中断属性接口。
 *
 * @par 描述:
 * 在创建硬中断前，必须要配置好硬中断的优先级和模式，包括独立型（#OS_HWI_MODE_ENGROSS）和组合型（#OS_HWI_MODE_COMBINE）两种配置模式。
 *
 * @attention
 * <ul>
 * <li>Tensilica下的SD6181, SD6108, SD6182, SD6157芯片，可用硬中断号为0-31，OS已经占用的不能被使用(对于SD6182平台，1号中断用于错误中断，9号中断用于WriteError，28号中断用于MSGM，若打开Tick模块，6号中断用于Tick;对于SD6183平台，48、50号中断用于CACHE，51号中断用于MMU，64号中断用于错误中断，72、73号中断用于硬件信号量)。</li>
 * <li>对于Tensilica平台，硬中断优先级由硬件固定，优先级配置参数#usHwiPrio无效。</li>
 * <li>Cortex-AX平台下Balong产品可用硬中断号为0-255,ISP产品可用硬中断号为0-511，优先级都为0-31。</li>
 * <li>SD6183平台下可用硬中断号为34-51,55-58,64-103,124-127，优先级1-7，数字越大优先级越高。</li>
 * </ul>
 *
 * @param  uwHwiNum  [IN] 类型#HWI_HANDLE_T，硬中断号。
 * @param  usHwiPrio [IN] 类型#HWI_PRIOR_T，硬中断优先级。
 * @param  usMode    [IN] 类型#HWI_MODE_T，设置的中断模式，为独立型(#OS_HWI_MODE_ENGROSS)或者组合型(#OS_HWI_MODE_COMBINE)。
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID                     0x02001400，中断号非法。
 * @retval #OS_ERRNO_HWI_PRI_ERROR                       0x02001401，优先级非法。
 * @retval #OS_ERRNO_HWI_MODE_ERROR                      0x0200140a，创建的中断函数即不是独立型，也不是组合型。
 * @retval #OS_ERRNO_HWI_ATTR_CONFLICTED                 0x02001406，属性重复设置冲突。
 * @retval #SRE_OK                                       0x00000000，硬中断创建成功。
 * @par 依赖:
 * <ul><li>SRE_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiCreate
 **/
extern UINT32 SRE_HwiSetAttr(HWI_HANDLE_T uwHwiNum,
                             HWI_PRIOR_T usHwiPrio,
                             HWI_MODE_T usMode);

/**
 * @ingroup  SRE_hwi
 * @brief 创建硬中断函数。
 *
 * @par 描述:
 * 注册硬中断的处理函数。
 *
 * @attention
 * <ul>
 * <li>在调用该函数之前，请先确保已经设置了中断属性。</li>
 * <li>Tensilica平台下的SD6181, SD6108, SD6182, SD6157芯片，可用硬中断号为0-31。</li>
 * <li>Cortex-AX平台下Balong产品可用硬中断号为0-255,ISP产品可用硬中断号为0-511，优先级都为0-31。</li>
 * <li>SD6183平台下可用硬中断号为34-51,55-58,64-103,124-127,优先级1-7。</li>
 * <li>硬中断创建成功后，并不使能相应向量的中断，需要显式调用#SRE_HwiEnable单独使能。</li>
 * </ul>
 *
 * @param  uwHwiNum   [IN] 类型#HWI_HANDLE_T，硬中断号。
 * @param  pfnHandler [IN] 类型#HWI_PROC_FUNC，硬中断触发时的处理函数。
 * @param  uwArg      [IN] 类型#HWI_ARG_T，调用硬中断处理函数时传递的参数。
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID                     0x02001400，中断号非法。
 * @retval #OS_ERRNO_HWI_PROC_FUNC_NULL                  0x02001403，硬中断处理函数为空。
 * @retval #OS_ERRNO_HWI_MODE_UNSET                      0x0200140c，未进行硬中断模式设置。
 * @retval #OS_ERRNO_HWI_MEMORY_ALLOC_FAILED             0x02001408，组合型中断节点申请私有静态内存失败
 * @retval #OS_ERRNO_HWI_COMBINEHOOK_ALREADY_CREATED     0x02001409，组合型中断已创建了相同的中断处理函数。
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED                 0x02001402，硬中断已被创建或相应中断向量号已被其它中断占用。
 * @retval #SRE_OK                                       0x00000000，硬中断创建成功。
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiDelete
 **/
extern UINT32 SRE_HwiCreate(HWI_HANDLE_T  uwHwiNum,
                            HWI_PROC_FUNC pfnHandler,
                            HWI_ARG_T     uwArg);

/**
 * @ingroup  SRE_hwi
 * @brief 删除硬中断函数。
 *
 * @par 描述:
 * 屏蔽相应硬中断或事件，取消硬中断处理函数的注册。
 *
 * @attention
 * <ul>
 * <li>Tensilica下的SD6181, SD6108, SD6182, SD6157芯片，可用硬中断号为0-31。</li>
 * <li>不能删除OS占用的中断号。</li>
 * <li>Cortex-AX平台下Balong产品可用硬中断号为0-255,ISP产品可用硬中断号为0-511。</li>
 * <li>SD6183下可用硬中断号为34-51,55-58,64-103,124-127。</li>
 * </ul>
 *
 * @param  uwHwiNum [IN] 类型#HWI_HANDLE_T，硬中断号。
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID            0x02001400，中断号非法。
 * @retval #OS_ERRNO_HWI_DELETE_TICK_INT        0x02001405，删除TICK中断。
 * @retval #OS_ERRNO_HWI_DELETE_MSGM_HPQ_INT    0x0200140f，删除SD6182/SD6157/SD6183 MSGM中的HPQ中断。
 * @retval #OS_ERRNO_HWI_DELETED                0x0200140b，删除未创建的硬中断。
 * @retval #SRE_OK                              0x00000000，硬中断删除成功。
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiCreate
 */
extern UINT32 SRE_HwiDelete(HWI_HANDLE_T uwHwiNum);

/**
* @ingroup  SRE_hwi
* @brief 还原指定中断号的中断使能寄存器的值。
*
* @par 描述:
* 将之前调用#SRE_HwiDisable、#SRE_HwiEnable的返回值，重新填入中断使能寄存器。
*
* @attention
* <ul>
* <li>该函数需要与#SRE_HwiDisable或#SRE_HwiEnable配对使用。</li>
* <li>对于Tensilica，可用硬中断号为0-31。</li>
* <li>Cortex-AX平台下Balong产品可用硬中断号为0-255,ISP产品可用硬中断号为0-511。</li>
* <li>对于SD6183，可用硬中断号为34-51,55-58,64-103,124-127。</li>
* <li>Tensilica特有功能:当入参为OS_HWI_ALL时，可还原所有硬中断。</li>
* </ul>
*
* @param  uwHwiNum  [IN] 类型#HWI_HANDLE_T，硬中断号。
* @param  uvHwiSave [IN] 类型#UINTPTR，中断使能寄存器的保存值。
*
* @retval 无
* @par 依赖:
* <ul><li>SRE_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HwiEnable | SRE_HwiDisable
*/
extern VOID SRE_HwiRestore(HWI_HANDLE_T  uwHwiNum, UINTPTR  uvHwiSave);

/**
* @ingroup  SRE_hwi
* @brief 激活指定核号内的硬中断。
*
* @par 描述:
* 激活指定核号内的软件可触发的硬中断
*
* @attention
* <ul>
* <li>针对Tensilica和SD6183平台有效。</li>
* <li>针对Cortex-AX，不支持该接口。</li>
* </ul>
*
* @param  uwDstCore [IN] 类型#UINT32， 目标核号。 目前只支持指定为本核。
* @param  uwHwiNum  [IN] 类型#HWI_HANDLE_T，硬中断号，只支持软件可触发的中断号（SD6182平台为7和11号中断，SD6183平台为124、125、126和127号中断）。
*
* @retval #OS_ERRNO_HWI_NUM_INVALID                0x02001400，中断号非法。
* @retval #OS_ERRNO_HWI_CORE_ID_INVALID            0x0200140d，输入无效的核号。
* @retval #OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD      0x0200140e，输入无效的中断号，软件不可触发。
* @retval #SRE_OK                                  0x00000000，硬中断请求位清除成功。
* @par 依赖:
* <ul><li>SRE_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
*/
extern UINT32 SRE_HwiTrigger (UINT32 uwDstCore , HWI_HANDLE_T uwHwiNum);

/**
 * @ingroup  SRE_hwi
 * @brief 清空中断请求位。
 *
 * @par 描述:
 * 清除所有的中断请求位。即放弃当前已触发中断的的响应。
 *
 * @attention
 * <ul>
 * <li>针对Tensilica和SD6183平台，清除所有的中断请求位(对于NMI中断无效)。</li>
 * <li>针对Cortex-AX，不支持该接口。</li>
 * </ul>
 *
 * @param  无。
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>SRE_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiClearPendingBit
 */
extern VOID SRE_ClearAllPending(VOID);

/**
 * @ingroup  SRE_hwi
 * @brief 清除硬中断的Pending位。
 *
 * @par 描述:
 * 显式清除硬中断或事件的请求位，因为有的硬件响应中断后不会自动清Pending位。
 *
 * @attention
 * <ul>
 * <li>对于Tensilica，此参数为中断向量号0-31。</li>
 * <li>针对Cortex-AX，不支持该接口。</li>
 * <li>针对SD6183平台，此参数为中断向量号34-51,55-58,64-103,124-127，另外此接口对NMI中断无效。</li>
 * </ul>
 *
 * @param  uwHwiNum [IN] 类型#HWI_HANDLE_T，硬中断号。
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID            0x02001400，中断号非法。
 * @retval #SRE_OK                              0x00000000，硬中断请求位清除成功。
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiCreate
 */
extern UINT32 SRE_HwiClearPendingBit(HWI_HANDLE_T uwHwiNum);


/**
* @ingroup  SRE_hwi
* @brief 屏蔽指定的硬中断。
*
* @par 描述:
* 禁止核响应指定硬中断的请求。
*
* @attention
* <ul>
* <li>对于Tensilica，此参数为中断向量号0-31。</li>
* <li>对于Cortex-AX，Balong产品可用硬中断向量号为0-255,ISP产品可用硬中断向量号为0-511。</li>
* <li>对于SD6183，此参数为中断向量号34-51,55-58,64-103,124-127，另外此接口对NMI中断无效。</li>
* <li>Tensilica特有功能:当入参为OS_HWI_ALL时，可屏蔽所有硬中断。</li>
* </ul>
*
* @param  uwHwiNum [IN] 类型#HWI_HANDLE_T，依据不同的芯片，硬中断号或中断向量号，见注意事项。
*
* @retval #OS_ERRNO_HWI_NUM_INVALID           0x02001400，中断号非法。(针对Cortex-AX、SD6183)
* @retval #0                                  屏蔽前的中断禁止状态值。(针对Cortex-AX、SD6183)
* @retval #1                                  屏蔽前的中断使能状态值。(针对Cortex-AX、SD6183)
* @retval #任意值                             屏蔽前的中断使能寄存器的值。(针对Tensilica)
* @par 依赖:
* <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HwiEnable
*/
extern UINTPTR SRE_HwiDisable(HWI_HANDLE_T uwHwiNum);



/**
* @ingroup  SRE_hwi
* @brief 查询中断状态。
*
* @par 描述:
* 查询中断状态。
*
* @attention
* <ul>
* <li>只支持6183。</li>
* <li>读出的是当前中断的中断状态。</li>
* </ul>
*
* @param  uwHwiNum [IN] 类型#HWI_HANDLE_T，依据不同的芯片，硬中断号或中断向量号，见注意事项
* @param  puwHwiPendingReg [OUT] 类型#UINT32*，对应的中断状态1:有中断，0无中断
*
* @retval #OS_ERRNO_HWI_NUM_INVALID           0x02001400，中断号非法。(针对SD6183)
* @retval #OS_ERRNO_HWI_PARAM_NULL            0x02001411，入参非法。
* @retval #SRE_OK                             0x00000000，查询成功。
* @par 依赖:
* <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see
*/
extern  UINT32 SRE_HwiPendingQuery(HWI_HANDLE_T uwHwiNum, UINT32 *puwHwiPendingReg);

/**
* @ingroup  SRE_hwi
* @brief 使能指定的硬中断。
*
* @par 描述:
* 允许核响应指定硬中断的请求。
*
* @attention
* <ul>
* <li>对于Tensilica，此参数为中断向量号0-31。</li>
* <li>对于Cortex-AX，Balong产品可用硬中断向量号为0-255,ISP产品可用硬中断向量号为0-511。</li>
* <li>对于SD6183，此参数为中断向量号34-51,55-58,64-103,124-127，另外此接口对NMI中断无效。</li>
* <li>Tensilica特有功能:当入参为OS_HWI_ALL时，可使能所有硬中断。</li>
* <li>对于不同芯片，此返回值代表的意义有所差异，差异细节见下面返回值说明</li>
* </ul>
*
* @param  uwHwiNum [IN] 类型#HWI_HANDLE_T，依据不同的芯片，硬中断号或中断向量号，见注意事项。
*
* @retval #OS_ERRNO_HWI_NUM_INVALID           0x02001400，中断号非法(针对Cortex-AX、SD6183)。
* @retval #0                                  屏蔽前的中断禁止状态值(针对Cortex-AX、SD6183)。
* @retval #1                                  屏蔽前的中断使能状态值(针对Cortex-AX、SD6183)。
* @retval #任意值                             屏蔽前的中断使能寄存器的值(针对Tensilica)。
* @par 依赖:
* <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HwiDisable
*/
extern UINTPTR SRE_HwiEnable(HWI_HANDLE_T uwHwiNum);

/**
 * @ingroup  SRE_hwi
 * @brief 添加硬中断进入钩子
 *
 * @par 描述:
 * 添加硬中断进入钩子。该钩子函数在进入硬中断ISR前被调用。
 *
 * @attention
 * <ul>
 * <li>不同钩子函数间执行的先后顺序，不应当存在依赖关系。</li>
 * <li>不应在钩子函数里调用可能引起线程调度或阻塞的OS接口。</li>
 * <li>最大支持钩子数需静态配置</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#HWI_ENTRY_HOOK，中断进入钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiEntryHookDel | SRE_HookAdd | SRE_HwiExitHookAdd
 */
#define SRE_HwiEntryHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_HWI_ENTRY, (OS_VOID_FUNC)(HWI_ENTRY_HOOK)pfnHook)

/**
 * @ingroup  SRE_hwi
 * @brief 删除硬中断进入钩子
 *
 * @par 描述:
 * 删除硬中断进入钩子。该钩子函数将停止在进入硬中断ISR前的调用。
 *
 * @attention
 * <ul>
 * <li>不同钩子函数间执行的先后顺序，不应当存在依赖关系。</li>
 * <li>不应在钩子函数里调用可能引起线程调度或阻塞的OS接口。</li>
 * <li>最大支持钩子数需静态配置</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#HWI_ENTRY_HOOK，中断进入钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiEntryHookAdd | SRE_HookDel
 */
#define SRE_HwiEntryHookDel(pfnHook) SRE_HookDel(OS_HOOK_HWI_ENTRY, (OS_VOID_FUNC)(HWI_ENTRY_HOOK)pfnHook)

/**
 * @ingroup  SRE_hwi
 * @brief 添加硬中断退出钩子
 *
 * @par 描述:
 * 添加硬中断退出钩子。该钩子函数在退出硬中断ISR后被调用。
 *
 * @attention
 * <ul>
 * <li>不同钩子函数间执行的先后顺序，不应当存在依赖关系。</li>
 * <li>不应在钩子函数里调用可能引起线程调度或阻塞的OS接口。</li>
 * <li>最大支持钩子数需静态配置</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#HWI_EXIT_HOOK，中断退出钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiExitHookDel | SRE_HookAdd | SRE_HwiEntryHookAdd
 */
#define SRE_HwiExitHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_HWI_EXIT, (OS_VOID_FUNC)(HWI_EXIT_HOOK)pfnHook)

/**
 * @ingroup  SRE_hwi
 * @brief 删除硬中断退出钩子
 *
 * @par 描述:
 * 删除硬中断退出钩子。该钩子函数将停止在退出硬中断ISR后的调用。
 *
 * @attention
 * <ul>
 * <li>不同钩子函数间执行的先后顺序，不应当存在依赖关系。</li>
 * <li>不应在钩子函数里调用可能引起线程调度或阻塞的OS接口。</li>
 * <li>最大支持钩子数需静态配置</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#HWI_EXIT_HOOK，中断退出钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_hwi.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiExitHookAdd | SRE_HookDel
 */
#define SRE_HwiExitHookDel(pfnHook) SRE_HookDel(OS_HOOK_HWI_EXIT, (OS_VOID_FUNC)(HWI_EXIT_HOOK)pfnHook)


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HWI_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

