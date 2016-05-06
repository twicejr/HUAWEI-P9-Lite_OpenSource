/**
 * @file sre_coprocessor.h
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：矢量寄存器模块的对外头文件。 \n
 */
 /**@defgroup SRE_coprocessor 矢量寄存器
   *@ingroup SRE_kernel
 */


#include "sre_base.h"
#ifndef _SRE_COPROCESSOR_H
#define _SRE_COPROCESSOR_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if  (OS_OPTION_COPROCESSOR == YES)

/**
 * @ingroup SRE_coprocessor
 * coprocessor_a和coprocessor_b上下文保存区域的大小。
 *
 */

#if (OS_HARDWARE_PLATFORM == OS_DSP170)

#define OS_CP_CONTEXT_A_SIZE                                0x18C
#define OS_CP_CONTEXT_B_SIZE                                0x18C

#elif (OS_HARDWARE_PLATFORM == OS_DSP220)

#define OS_CP_CONTEXT_A_SIZE                                0xD8
#define OS_CP_CONTEXT_B_SIZE                                0xD8

#elif ((OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))

#define OS_CP_CONTEXT_A_SIZE                                0x44
#define OS_CP_CONTEXT_B_SIZE                                0x44

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

#define OS_CP_CONTEXT_A_SIZE                                0x88
#define OS_CP_CONTEXT_B_SIZE                                0x88

#endif

#endif // (OS_OPTION_COPROCESSOR == YES)

/**
 *@ingroup SRE_coprocessor
 *@brief 为指定的内存空间设置指定值。
 *
 *@par 描述:
 *通过矢量操作，将指定首地址和长度的内存空间设置为固定值，功能等同于memset。
 *@attention
 * <ul>
 * <li>该操作适用于SD6108/SD6181平台的DSP核，SD6182、SD6157、SD6183平台。</li>
 * <li>非SD6183平台建议用户使用矢量赋值操作前调用#SRE_TaskCpEntry或#SRE_SwiCpEntry，使用矢量赋值操作后，调用#SRE_TaskCpExit或#SRE_SwiCpExit, 以提高矢量操作性能。</li>
 * <li>参数uwValue只有低8bit有效，高位会被忽略。</li>
 * <li>非SD6183平台在任务或软中断中进行矢量赋值操作前一定要设置矢量缓存区。</li>
 * <li>非SD6183平台硬中断中不支持矢量操作</li>
 * </ul>
 *@param pDst         [IN]  类型#VOID *，内存空间首地址。
 *@param uwValue      [IN]   类型#UINT32，需设置的指定值，低8BIT有效。
 *@param uwSize       [IN]   类型#UINT32，内存空间的长度。
 *
 *@retval #VOID *    内存空间首地址。
 *@par 依赖:
 *sre_coprocessor.h：该接口声明所在的头文件。
 *@since UniDSP V200R003C05
 *@see SRE_SwiCpEntry|SRE_TaskCpEntry
*/
extern VOID * SRE_VecMemSet(VOID *pDst, UINT32 uwValue, UINT32 uwSize);


/**
 *@ingroup SRE_coprocessor
 *@brief 将一段指定长度的内存从源地址拷贝至目的地址。
 *
 *@par 描述:
 * 通过矢量操作，将pSrc起始大小为uwSize的内存的内容拷贝至pDst起始的内存空间。
 *@attention
 * <ul>
 * <li>该操作适用于SD6108/SD6181平台的DSP核，SD6182、SD6157、SD6183平台。</li>
 * <li>建议用户使用矢量拷贝操作前调用#SRE_TaskCpEntry或#SRE_SwiCpEntry，使用矢量拷贝操作后，调用#SRE_TaskCpExit或#SRE_SwiCpExit, 以提高矢量操作性能。</li>
 * <li>调用前，需要保证参数之间不满足以下关系pSrc < pDst < (pSrc + uwSize)</li>
 * <li>在任务或软中断中进行矢量拷贝操作前一定要设置矢量缓存区。</li>
 * <li>硬中断中不支持矢量操作</li>
 * </ul>
 *@param pDst         [IN] 类型#VOID *，待拷贝的目的内存首地址。
 *@param pSrc         [IN]  类型#VOID *，需拷贝的源内存首地址。
 *@param uwSize       [IN]  类型#UINT32，进行拷贝的长度。
 *
 *@retval #VOID*    待拷贝的目的内存首地址。
 *@par 依赖:
 *sre_coprocessor.h：该接口声明所在的头文件。
 *@since UniDSP V200R003C05
 *@see SRE_SwiCpEntry|SRE_TaskCpEntry
*/
extern VOID * SRE_VecMemCpy(VOID *pDst, VOID *pSrc, UINT32 uwSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_COPROCESSOR_H */

/**
 * History:
 * 2011-03-30 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
