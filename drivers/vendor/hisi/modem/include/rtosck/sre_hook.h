/**
 * @file sre_hook.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：内核钩子头文件。 \n
 */

 /**
 *@defgroup  SRE_hook  钩子管理
 *@ingroup SRE_kernel
*/

#ifndef _SRE_HOOK_H
#define _SRE_HOOK_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_hook
 * HOOK错误码：HOOK类型错误。
 *
 * 值: 0x02001600
 *
 * 解决方案：确认输入钩子是否为有效的OS_HOOK_TYPE_E类型。
 */
#define OS_ERRNO_HOOK_TYPE_INVALID   SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x00)

/**
 * @ingroup SRE_hook
 * HOOK错误码：内存不足。
 *
 * 值: 0x02001601
 *
 * 解决方案：增加缺省分区大小。
 */
#define OS_ERRNO_HOOK_NO_MEMORY     SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x01)

/**
 * @ingroup SRE_hook
 * HOOK错误码：HOOK指针空。
 *
 * 值: 0x02001602
 *
 * 解决方案：检查入参的钩子，NULL指针不允许进行添加或删除。
 */
#define OS_ERRNO_HOOK_PTR_NULL      SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x02)

/**
 * @ingroup SRE_hook
 * HOOK错误码：HOOK已存在。
 *
 * 值: 0x02001603
 *
 * 解决方案：确认该钩子之前是否已经成功注册，所以再次注册失败。
 */
#define OS_ERRNO_HOOK_EXISTED       SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x03)

/**
 * @ingroup SRE_hook
 * HOOK错误码：HOOK已满。
 *
 * 值: 0x02001604
 *
 * 解决方案：该类型钩子已经注册满，可以增大配置，或删掉一部分钩子。
 */
#define OS_ERRNO_HOOK_FULL          SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x04)

/**
 * @ingroup SRE_hook
 * HOOK错误码：HOOK不存在。
 *
 * 值: 0x02001605
 *
 * 解决方案：确认该钩子之前是否已经成功注册。
 */
#define OS_ERRNO_HOOK_NOT_EXISTED   SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x05)

/**
 * @ingroup SRE_hook
 * HOOK错误码：HOOK配置个数为0。
 *
 * 值: 0x02001606
 *
 * 解决方案：该类型钩子个数配置为0，添加或者删除某类型钩子前，需要先对其个数进行正确配置。
 */
#define OS_ERRNO_HOOK_NOT_CFG       SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x06)


/**
 * @ingroup SRE_hook
 * 用户可使用钩子类型枚举。
 */
typedef enum
{
    OS_HOOK_HWI_ENTRY = 0,       /**< 硬中断进入钩子  */
    OS_HOOK_HWI_EXIT,            /**< 硬中断退出钩子  */

    OS_HOOK_SWI_ENTRY,           /**< 软中断进入钩子  */
    OS_HOOK_SWI_EXIT,            /**< 软中断退出钩子  */

    OS_HOOK_TSK_CREATE,          /**< 任务创建钩子    */
    OS_HOOK_TSK_DELETE,          /**< 任务删除钩子    */
    OS_HOOK_TSK_SWITCH,          /**< 任务切换钩子    */

    OS_HOOK_IDLE_PERIOD,         /**< IDLE钩子        */
    OS_HOOK_LAST_WORDS,          /**< 临终遗言钩子    */

    OS_HOOK_TYPE_NUM             /**< 钩子总数        */
}OS_HOOK_TYPE_E;


/**
 * @ingroup SRE_hook
 * 钩子模块配置信息的结构体定义。
 */
typedef struct tagOSHookModInfo
{
    UINT8 aucMaxNum[OS_HOOK_TYPE_NUM];
}HOOK_MOD_INFO_S;


/**
*@ingroup SRE_hook
*
*@brief 添加内核钩子。
*
*@par 描述:
* 添加指定类型的内核钩子，内核在相应的处理点进行钩子回调。
*@attention 添加钩子数目不能大于对应类型静态配置(OS_HOOK_XXX_NUM)的最大值。如果没有静态配置项，默认支持1个。
*
*@param enHookType [IN] 类型#OS_HOOK_TYPE_E，添加钩子类型。
*@param pfnHook [IN] 类型#OS_VOID_FUNC，添加钩子指针。
*
*@retval #OS_ERRNO_HOOK_TYPE_INVALID   0x02001600，钩子类型无效。
*@retval #OS_ERRNO_HOOK_PTR_NULL       0x02001602，钩子指针为空。
*@retval #OS_ERRNO_HOOK_EXISTED        0x02001603，钩子已经存在。
*@retval #OS_ERRNO_HOOK_FULL           0x02001604，钩子已满。
*@retval #OS_ERRNO_HOOK_NOT_CFG        0x02001606，钩子个数配置为0。
*@retval #SRE_OK                       0x00000000，添加钩子成功。
*@par 依赖:
*<li>sre_hook.h：该接口声明所在的头文件。</li>
*@since RTOSck V100R002C00
*@see SRE_HookDel
*/
extern UINT32 SRE_HookAdd(OS_HOOK_TYPE_E enHookType, OS_VOID_FUNC pfnHook);


/**
*@ingroup SRE_hook
*
*@brief 删除内核钩子。
*
*@par 描述:
* 删除指定类型的内核钩子。
*@attention
*
*@param enHookType [IN] 类型#OS_HOOK_TYPE_E，待删除钩子类型。
*@param pfnHook [IN] 类型#OS_VOID_FUNC，待删除钩子指针。
*
*@retval #OS_ERRNO_HOOK_TYPE_INVALID   0x02001600，钩子类型无效。
*@retval #OS_ERRNO_HOOK_PTR_NULL       0x02001602，钩子指针为空。
*@retval #OS_ERRNO_HOOK_NOT_EXISTED    0x02001605，钩子不存在。
*@retval #OS_ERRNO_HOOK_NOT_CFG        0x02001606，钩子个数配置为0。
*@retval #SRE_OK                       0x00000000，删除钩子成功。
*@par 依赖:
*<li>sre_hook.h：该接口声明所在的头文件。</li>
*@since RTOSck V100R002C00
*@see SRE_HookAdd
*/
extern UINT32 SRE_HookDel(OS_HOOK_TYPE_E enHookType, OS_VOID_FUNC pfnHook);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HOOK_H */

/*
 * History: \n
 * 2013-3-22, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

