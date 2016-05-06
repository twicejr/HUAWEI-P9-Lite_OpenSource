/**
 * @file SRE_io_intf.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：IO接口头文件。 \n
 */

/**@defgroup sre_io_intf IO打印
 *@ingroup SRE_kernel
*/

#ifndef __SRE_IO_INTF_H__
#define __SRE_IO_INTF_H__

#include "sre_base.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_IO_INTF == YES)

/**
 *@ingroup sre_io_intf
 *IO端口打印输出结束符。
 */
#define OS_IO_INTF_END_SIGN        0

/**
* @ingroup  sre_io_intf
*
* 定义用户注册的通道字符输出钩子函数类型。
*/
typedef UINT32 (*OS_SENDCHR2CHL_HOOK_FUNC)(UINT8 ucChar);

/**
 * @ingroup sre_io_intf
 * IO接口错误码：SRE_SendChrToChlHookReg函数入参为空。
 *
 * 值: 0x02003431
 *
 * 解决方案: SRE_SendChrToChlHookReg函数的入参否为空指针。
 *
 */
#define OS_ERRNO_IO_INTF_SENDCHR2SHELL_PARA_NULL                                  SRE_ERRNO_OS_ERROR(OS_MID_IO_INTF, 0x31)

/**
 * @ingroup sre_io_intf
 * IO接口错误码：串口输出钩子函数为空。
 *
 * 值: 0x02003432
 *
 * 解决方案: 串口输出钩子函数是否为空。
 *
 */
#define OS_ERRNO_IO_INTF_SENDCHR2CHL_HOOK_NULL                                    SRE_ERRNO_OS_ERROR(OS_MID_IO_INTF, 0x32)

/**
 * @ingroup sre_shell
 * HShell错误码：串口发送的字符串为空。
 *
 * 值: 0x02003433
 *
 * 解决方案: 串口发送的字符串为空
 *
 */
#define OS_ERRNO_IO_INTF_SENDSTR_NULL                                             SRE_ERRNO_OS_ERROR(OS_MID_IO_INTF, 0x33)

/**
* @ingroup  sre_io_intf
* @brief 向IO端口输出字符的钩子注册函数
*
* @par 描述:
* 注册IO端口输出字符函数。
*
* @attention
* <ul>无</ul>
*
* @param  pfnSendChr2ChlHook  [IN] 类型#OS_SENDCHR2CHL_HOOK_FUNC，注册的钩子函数。
*
* @retval  #OS_ERRNO_IO_INTF_SENDCHR2SHELL_PARA_NULL 0x02003431，用户注册的钩子函数参数为空。
* @retval  #SRE_OK                                 0x00000000，成功。
* @par 依赖:
* <ul><li>sre_io_intf.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C00
* @see 无
*/
extern UINT32 SRE_SendChrToChlHookReg(OS_SENDCHR2CHL_HOOK_FUNC pfnSendChr2ChlHook);


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__SRE_IO_INTF_H__

