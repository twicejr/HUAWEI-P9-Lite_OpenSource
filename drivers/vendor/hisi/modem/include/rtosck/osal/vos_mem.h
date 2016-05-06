/**
 * @file vos_mem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL内存头文件。 \n
 */
/**@defgroup OSAL OSAL */
/**@defgroup vos_mem 内存
 *@ingroup OSAL
*/

#ifndef __VOS_MEM_H__
#define __VOS_MEM_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup  vos_mem
 * @brief 申请指定大小的内存空间。
 *
 * @par 描述:
 * 申请指定大小的内存空间。
 *
 * @attention 无
 *
 * @param  ulInfo [IN] 类型#VOS_UINT32，分区号PID，该参数忽略，取值范围为任意值。
 * @param  uvSize [IN] 类型#VOS_SIZE_T，申请内存的大小，取值范围为正整数。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，申请内存失败，可能的原因为uvSize为0或者内存不足。
 * @retval #任意值                              申请的内存块首地址。
 * @par 依赖:
 * <ul><li>vos_mem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Free | VOS_MemReAlloc | VOS_Mem_Calloc
 */
extern VOS_VOID * VOS_Malloc(VOS_UINT32 ulInfo, VOS_SIZE_T uvSize);

/**
 * @ingroup  vos_mem
 * @brief 释放内存空间。
 *
 * @par 描述:
 * 释放给定的地址空间pBuf。
 *
 * @attention 无
 *
 * @param  pBuf [IN] 类型#VOS_VOID *，需要释放的内存首地址，取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，释放地址pBuf为空。
 * @retval #VOS_ERROR                           0xFFFFFFFF，释放内存失败，可能的原因为内存块的头被破坏，或内存块已释放。
 * @retval #VOS_OK                              0x00000000，释放内存成功。
 * @par 依赖:
 * <ul><li>vos_mem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Malloc
 */
extern VOS_UINT32 VOS_Free(VOS_VOID *pBuf);

/**
 * @ingroup  vos_mem
 * @brief 获取指定地址的引用计数。
 *
 * @par 描述:
 * 获取指定地址pBuf的引用计数。
 *
 * @attention 无
 *
 * @param  pBuf [IN] 类型#VOS_VOID *，需要获取引用的计数的内存首地址，取值范围为非空。
 * @param  pulRetRef [OUT] 类型#VOS_UINT32 *，用于存储获取到的引用计数，取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pBuf或pulRetRef为空。
 * @retval #VOS_OK                              0x00000000，获取指定地址的引用计数成功。
 * @par 依赖:
 * <ul><li>vos_mem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Mem_GetRef(VOS_VOID *pBuf, VOS_UINT32 *pulRetRef);

/**
 * @ingroup  vos_mem
 * @brief 增加指定地址的引用计数。
 *
 * @par 描述:
 * 增加指定地址pBuf的引用计数。
 *
 * @attention 无
 *
 * @param  pBuf [IN] 类型#VOS_VOID *，需要增加引用的计数的内存首地址，取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pBuf为空。
 * @retval #VOS_OK                              0x00000000，增加指定地址pBuf的引用计数成功。
 * @par 依赖:
 * <ul><li>vos_mem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Mem_IncRef(VOS_VOID *pBuf);

/**
 * @ingroup  vos_mem
 * @brief 申请指定大小的内存空间，并对内存空间内容进行清零。
 *
 * @par 描述:
 * 申请uvSize字节的内存，并对内存空间内容进行清零。
 *
 * @attention 无
 *
 * @param  ulInfo [IN] 类型#VOS_UINT32，该参数忽略，取值范围为任意值。
 * @param  chTaskName[4] [IN] 类型#VOS_CHAR，该参数忽略，传入VOS_NULL_PTR即可。
 * @param  uvSize [IN] 类型#VOS_SIZE_T，申请内存的大小，取值范围为正整数。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，申请内存失败，可能的原因为uvSize为0或者内存不足。
 * @retval #任意值                              申请的内存块首地址。
 * @par 依赖:
 * <ul><li>vos_mem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Malloc | VOS_MemReAlloc
 */
extern VOS_VOID * VOS_Mem_Calloc(VOS_UINT32 ulInfo, VOS_CHAR chTaskName[4], VOS_SIZE_T uvSize);

/**
 * @ingroup  vos_mem
 * @brief 重新设置内存块的大小。
 *
 * @par 描述:
 * 现有的内存块不够使用时，重新申请一块大小为ulNewSize的内存，新内存块分配成功后，会将原内存块(地址为pOldMemPtr)中的数据拷贝到新内存块，让原内存块信息保持不变的情况下，得到扩展。最大拷贝长度为新内存块的大小ulNewSize，并释放原内存块。
 *
 * @attention
 * <ul>
 * <li>如果输入的原内存地址为VOS_NULL_PTR，那么这个函数相当于 VOS_MemAlloc，即分配一个新内存块。</li>
 * <li>如果输入的原内存地址不为空，而输入的新内存块大小为0，那么这个函数相当于 VOS_MemFree，即释放原内存。</li>
 * <li>如果新内存块分配失败，原内存块不会被释放。</li>
 * <li>如果原来内存块的大小小于新的大小，则只复制原来内存大小的内容，否则复制新大小的内容。</li>
 * </ul>
 *
 * @param  ulPid [IN] 类型#VOS_UINT32，该参数忽略，取值范围为任意值。
 * @param  ucPtNo [IN] 类型#VOS_UINT8，该参数忽略，取值范围为任意值。
 * @param  pOldMemPtr [IN] 类型#VOS_VOID *，原来内存块的地址，取值范围为非空。
 * @param  uwNewSize [IN] 类型#VOS_UINT32，新的内存块大小，取值范围为正整数。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，申请内存失败，可能的原因为uvSize为0或者内存不足。
 * @retval #任意值                              重新分配的内存块首地址。
 * @par 依赖:
 * <ul><li>vos_mem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Malloc | VOS_Mem_Calloc
 */
extern VOID * VOS_MemReAlloc(VOS_UINT32 ulPid, VOS_UINT8 ucPtNo, VOS_VOID *pOldMemPtr, VOS_UINT32 uwNewSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_MEM_H__

