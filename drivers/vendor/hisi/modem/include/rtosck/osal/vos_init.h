/**
 * @file vos_init.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL系统基本功能头文件。 \n
 */

/**@defgroup vos_init OSAL初始化
 *@ingroup OSAL
 */

#ifndef __VOS_INIT_H__
#define __VOS_INIT_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
#include "sre_typedef.h"
#include "vos_redef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup  vos_init
 * @brief RTOSck OSAL初始化。
 *
 * @par 描述:
 * RTOSck OSAL初始化。用户在需要使用RTOSck OSAL接口前调用必须此接口。
 *
 * @attention 无
 *
 * @param
 *
 * @retval #VOS_ERRNO_OSAL_INIT_FAILED          0x00000080，请检查任务、队列、定时器模块是否开启并完成初始化。
 * @retval #VOS_ERRNO_NOMEM                     0x0000000C，释放其他未使用的内存空间或者分配更大的私有FSC内存分区。
 * @retval #VOS_ERROR                           0xFFFFFFFF，添加任务运行计时钩子失败。
 * @retval #VOS_OK                              0x00000000，OSAL初始化成功。
 * @par 依赖:
 * <ul><li>vos_init.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 VOS_AdapterInit(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_INIT_H__

