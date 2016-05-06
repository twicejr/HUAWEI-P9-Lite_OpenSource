/**
 * @file SRE_libc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：C库函数头文件。 \n
 */

/**@defgroup SRE_libc libc
 *@ingroup SRE_inspect
*/

#ifndef __SRE_LIBC_H__
#define __SRE_LIBC_H__

#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "sre_base.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_LIBC == YES)
#ifndef _TOOL_WIN32
/**
 * @ingroup SRE_libc
 * LIBC错误码：调用C库函数时，输入的参数不合法。
 *
 * 值: 0x02003701
 *
 * 解决方案: 调用C库函数时，需保证输入的参数合法。
 */
#define OS_ERRNO_LIBC_PARA_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x01)

/**
 * @ingroup SRE_libc
 * LIBC错误码：调用vsnprintf或者snprintf函数时，格式化后的字符串长度不小于输入长度size。
 *
 * 值: 0x02003702
 *
 * 解决方案: 调用vsnprintf或者snprintf函数时，需保证格式化后的字符串长度小于输入长度size。
 */
#define OS_ERRNO_LIBC_LEN_TOO_LONG                         SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x02)

/**
 * @ingroup SRE_libc
 * LIBC错误码：注册打印前缀钩子时，传入的钩子函数为NULL。
 *
 * 值: 0x02003703
 *
 * 解决方案: 保证注册打印前缀钩子时传入的钩子函数不为NULL。
 *
 */
#define OS_ERRNO_LIBC_PRINT_PRIFIX_HOOK_NULL                                   SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x03)

/**
* @ingroup  SRE_libc
* @brief 将可变参数格式化输出到一个字符数组。
*
* @par 描述:
* 将ap按格式format输出到一个指定最大输出大小的字符数组str中功能。
*
* @attention
* <ul>
* <li>目前只有CORTEX_AX平台支持标准输出打印函数。</li>
* <li>支持c、d、i、x、s、f、%几种类型格式化转换。</li>
* <li>支持右对齐(左边补0或者空格)和左对齐(右边补空格)。</li>
* <li>当格式化后的字符串长度大于(size-1)时，返回OS_INVALID，但是会把(size-1)个字符输出到str中。</li>
* <li>str空间大小由用户保证，避免造成内存越界。</li>
* </ul>
*
* @param  str   [OUT] 类型#char *，把生成的格式化的字符串存放在这里。
* @param  size  [IN] 类型#size_t，str可接受的最大字节数,防止产生数组越界。
* @param  format[IN] 类型#const char *，输出格式化字符串指针。
* @param  ap    [IN] 类型#va_list，va_list变量。
*
* @retval  #OS_INVALID                             入参不合法，或者格式化后的字符串长度大于(size-1)。
* @retval  #[0, size)                              成功输入str中的字符数，大于等于0，但是小于size。
* @par 依赖:
* <ul><li>sre_libc.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see vsprintf
*/
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);

/**
* @ingroup  SRE_libc
* @brief 将可变参数格式化输出到一个字符数组。
*
* @par 描述:
* 将ap按格式format输出到字符数组str中功能。
*
* @attention
* <ul>
* <li>目前只有CORTEX_AX平台支持标准输出打印函数。</li>
* <li>支持c、d、i、x、s、%几种类型格式化转换。</li>
* <li>str空间大小由用户保证，避免造成内存越界。</li>
* </ul>
*
* @param  str   [OUT] 类型#char *，把生成的格式化的字符串存放在这里。
* <li>支持c、d、i、x、s、f、%几种类型格式化转换。</li>
* <li>支持右对齐(左边补0或者空格)和左对齐(右边补空格)。</li>
* @param  ap    [IN] 类型#va_list，va_list变量。
*
* @retval  #OS_INVALID                             入参不合法。
* @retval  #格式化后的字符数                       成功输入str中的字符数。
* @par 依赖:
* <ul><li>sre_libc.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see vsnprintf
*/
extern int vsprintf(char *str, const char *format, va_list ap);

/**
* @ingroup  SRE_libc
* @brief 将可变个参数按照format格式化成字符串，然后将其复制到str中。
*
* @par 描述:
* 将可变个参数按照format格式化成字符串，然后将其复制到指定最大输出大小str中。
*
* @attention
* <ul>
* <li>目前只有CORTEX_AX平台支持标准输出打印函数。</li>
* <li>支持c、d、i、x、s、f、%几种类型格式化转换。</li>
* <li>支持右对齐(左边补0或者空格)和左对齐(右边补空格)。</li>
* <li>当格式化后的字符串长度大于(size-1)时，返回OS_INVALID，但是会把(size-1)个字符输出到str中。</li>
* <li>str空间大小和可选参数的合法性由用户保证，避免造成内存越界和其它异常。</li>
* </ul>
*
* @param  str   [OUT] 类型#char *，把生成的格式化的字符串存放在这里。
* @param  size  [IN] 类型#size_t，str可接受的最大字节数,防止产生数组越界。
* @param  format[IN] 类型#const char *，输出格式化字符串指针。
* @param  ...   [IN] 可选参数。
*
* @retval  #OS_INVALID                             入参不合法，或者格式化后的字符串长度大于(size-1)。
* @retval  #[0, size)                              成功输入str中的字符数，大于等于0，但是小于size。
* @par 依赖:
* <ul><li>sre_libc.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see vsnprintf
*/
extern int snprintf(char *str, size_t size, const char *format, ...);

#if (OS_OPTION_IO_INTF == YES)

/**< 最大Show长度 */
#define SHOW_MAX_LEN 321

/**
* @ingroup  SRE_libc
* @brief 标准输出打印。
*
* @par 描述:
* 注册通道输出钩子后，调用该函数可实现输出打印。
*
* @attention
* <ul>
* <li>目前只有CORTEX_AX平台支持标准输出打印函数。</li>
* <li>支持c、d、i、x、s、f、%几种类型格式化转换。</li>
* <li>支持右对齐(左边补0或者空格)和左对齐(右边补空格)。</li>
* <li>不支持在中断线程中调用，由用户保证。</li>
* <li>对于Balong产品，支持打印前缀(线程名)，对于ISP产品，不支持打印前缀。</li>
* <li>最大支持打印字符数为SHOW_MAX_LEN(321)，包含结束符。</li>
* <li>调用此函数时，需要额外消耗当前线程所在的栈空间资源(大约为343个字节)。</li>
* <li>可选参数的合法性由用户保证，避免造成打印异常。</li>
* </ul>
*
* @param  pcFormat [IN] 类型#CHAR *，输出格式化字符串指针。
* @param  ...      [IN] 可选参数。
*
* @retval  #OS_INVALID                             入参不合法。
* @retval  #[0,SHOW_MAX_LEN)                       已经输出打印的字符数，输出打印成功。
* @par 依赖:
* <ul><li>sre_libc.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see SRE_Printf
*/
extern int printf(const CHAR *pcFormat, ...);

#endif
#endif

/**< 用户打印前缀最大长度 */
#define PRINT_PREFIX_MAX_LEN    64

/**
 *@ingroup sre_shell
 *用户打印前缀的钩子函数类型定义。
 */
typedef UINT32 (*PRINT_PREFIX_FUNC)(CHAR *pcBuff);

/**
 *@ingroup sre_shell
 *@brief 用户注册打印前缀钩子。
 *
 *@par 描述:
 *注册用户打印前缀的钩子，OS将buffer传给用户，由用户通过注册的钩子进行格式化。
 *@attention
 * <ul>
 * <li>当多次注册该钩子时，最后一次注册的钩子生效。
 * <li>注册的钩子函数不能为空，即一旦注册钩子函数，不能通过注册空函数将其取消。
 * <li>如果钩子函数的出参buffer不为空字符串，OS按buffer字符串内容作为打印前缀打印。
 * <li>如果钩子函数的出参buffer为空字符串，OS将钩子返回值按16进制打印。
 * <li>用户保证钩子函数操作buffer长度不超过64字节。
 * </ul>
 *
 *@param pfnHook [IN] 类型#PRINT_PREFIX_FUNC，钩子函数。
 *
 *@retval #OS_ERRNO_SHELL_PRINT_PRIFIX_HOOK_NULL 0x02002d3b，钩子函数为空
 *@retval #SRE_OK 0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_libc.h：该接口声明所在的头文件
 *@since RTOSck V100R005C00
 *@see 无
 */
extern UINT32 SRE_PrintPrefixRegHook(PRINT_PREFIX_FUNC pfnHook);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__SRE_LIBC_H__

