/**
 * @file sre_cache.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：CACHE模块的对外头文件。 \n
 */
/** @defgroup sre_cache Cache
   *@ingroup SRE_kernel
*/

#ifndef _SRE_CACHE_H
#define _SRE_CACHE_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
* @ingroup sre_cache
* cache类型为指令cache。
*/
#define OS_ICACHE_TYPE                                      1

/**
* @ingroup sre_cache
* cache类型为数据cache。
*/
#define OS_DCACHE_TYPE                                      2

/**
* @ingroup sre_cache
* cache大小参数设置不合法。
*/
#define SRE_CACHE_SIZE_INVALID                              0x00000001

/**
* @ingroup sre_cache
*cache地址参数类型设置不合法 。
*/
#define SRE_CACHE_ADDR_INVALID                              0x00000002

/**
* @ingroup sre_cache
*cache类型参数设置不合法 。
*/
#define SRE_CACHE_TYPE_INVALID                              0x00000003

/**
* @ingroup sre_cache
* cache加锁余量不足。
*/
#define SRE_CACHE_NOAREA_LOCK                               0x00000006

/**
* @ingroup sre_cache
* cache TAG获取接口入参地址为空。
*/
#define SRE_CACHE_TAG_PTR_NULL                              0x00000007

/**
* @ingroup sre_cache
*cache操作地址被加锁。
*/
#define SRE_CACHE_ADDR_LOCKED                               0x00000008

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)

typedef enum
{
    CACHE_UNIFY     = 0,                    /**< Unify模式          */
    CACHE_SPLIT     = 1                     /**< Split模式          */
} OS_CACHE_MODE_E;

typedef enum
{
    ONE_LINE_PF         = 0,                /**< 1个cacheline       */
    TWO_LINES_PF        = 1,                /**< 2个cacheline       */
    ILLEGAL_ONE_LINE_PF = 2,                /**< 无效               */
    THREE_LINES_PF      = 3,                /**< 3个cacheline       */
    INVALID_DCC_HWPF    = 4                 /**< 无效               */
} OS_DCC_HWPF_POLICY_E;

typedef enum
{
    ZERO_LINE_OFFSET    = 0,                /**< 预取0个cacheline   */
    QUATER_LINE_OFFSET  = 1,                /**< 预取1/4个cacheline */
    HALF_LINE_OFFSET    = 2,                /**< 预取1/2个cacheline */
    THREE_QUARTERS_LINE_OFFSET = 3,         /**< 预取3/4个cacheline */
    INVALID_PCC_HWPF = 4                    /**< 无效               */
} OS_PCC_HWPF_POLICY_E;

#endif

/**
* @ingroup sre_cache
* cache错误码: 使用cache接口，操作cache区域大小为0，或者加锁解锁预取接口操作的实际大小超出最大可操作范围，则返回该值。
*
* 值: 0x02001101
*
* 解决方案: 请调整操作空间大小。
*/
#define OS_ERRNO_CACHE_SIZE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_SIZE_INVALID)

/**
 * @ingroup sre_cache
 * cache错误码: 使用加锁解锁以及获取tag接口时，操作地址超出可cache的范围。
 *
 * 值: 0x02001102
 *
 * 解决方案: 请查看操作地址空间是否可cache。
 */
#define OS_ERRNO_CACHE_ADDR_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_ADDR_INVALID)

/**
 * @ingroup sre_cache
 * cache错误码: 调用cache加解锁、获取tag接口以及SD6183设置Icache模式时，输入的cache类型不正确，目前只支持ICACHE进行加解锁，输入其它值报错误码，获取cache tag接口支持指令cache和数据cache类型，只能是PCC或者DCC。SD6183设置ICache模式时只能是Split或者UNIFY模式。
 *
 * 值: 0x02001103
 *
 * 解决方案: 请查看输入的cache类型是否支持。
 */
#define OS_ERRNO_CACHE_TYPE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_TYPE_INVALID)

/**
 * @ingroup sre_cache
 * cache错误码: cache加锁过程中，出现某一组加锁余量不足。
 *
 * 值: 0x02001106
 *
 * 解决方案: 加锁解锁接口需要配对使用，加锁空间范围有限，请查看是否进行多次加锁。
 */
#define OS_ERRNO_CACHE_NOAREA_LOCK                          SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_NOAREA_LOCK)

/**
 * @ingroup sre_cache
 * cache错误码: cache tag获取接口，输入的tag结构体指针为空。
 *
 * 值: 0x02001107
 *
 * 解决方案: 请输入有效的结构体指针。
 */
#define OS_ERRNO_CACHE_TAG_PTR_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_TAG_PTR_NULL)

/**
 * @ingroup sre_cache
 * cache错误码: 调用指令cache无效接口时，由于该无效空间存在加锁情况，无效不成功。
 *
 * 值: 0x02001108
 *
 * 解决方案: 无效前请检查该地址是否加锁。
 */
#define OS_ERRNO_CACHE_ADDR_LOCKED                          SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_ADDR_LOCKED)

/**
 * @ingroup sre_cache
 * cache错误码: 核号错误，HiDSP只能为0-33。
 *
 * 值: 0x02001109
 *
 * 解决方案: 请输入正确的核号。
 */
#define OS_ERRNO_CACHE_CORE_ID_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x09)

/**
 * @ingroup sre_cache
 * cache错误码: PCC硬件预取策略错误。
 *
 * 值: 0x0200110a
 *
 * 解决方案: 请修改PCC硬件预取策略。
 */
#define OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0a)

/**
 * @ingroup sre_cache
 * cache错误码: 获取指定地址的cache tag信息时，输入的CACHE Tag结构体指针为空。
 *
 * 值: 0x0200110c
 *
 * 解决方案: 请输入的有效的结构体指针。
 */
#define OS_ERRNO_CACHE_INFO_PTR_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0c)

/**
 * @ingroup sre_cache
 * cache错误码: DCC硬件预取策略错误。
 *
 * 值: 0x0200110d
 *
 * 解决方案: 请修改DCC硬件预取策略。
 */
#define OS_ERRNO_CACHE_DCC_HWPF_POLICY_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0d)

/**
 * @ingroup sre_cache
 * CACHE错误码: PCC 锁余量不足。
 *
 * 值: 0x0200110e
 *
 * 解决方案 :4块可加锁地址区域已经使用完，需解锁才能继续加锁。
 */
#define OS_ERRNO_CACHE_PCC_LOCK_BLOCK_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0e)

/**
 * @ingroup sre_cache
 * 消息错误码：cache锁操作的地址范围发生了反转。
 *
 * 值: 0x0200110f
 *
 * 解决方案: 请保证传入的锁虚拟地址对应的物理地址是连续的且没有发生反转。
 *
 */
#define OS_ERRNO_CACHE_REGION_REVERSE                       SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0f)

/**
 * @ingroup sre_cache
 * 消息错误码：cache锁操作的地址范围已经被锁。
 *
 * 值: 0x02001110
 *
 * 解决方案: 确认当前锁操作的地址范围是否已被锁操作。
 *
 */
#define OS_ERRNO_CACHE_REGION_ALREARY_LOCK                  SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x10)

/**
 * @ingroup sre_cache
 * 消息错误码：异步方式操作cache后发送的消息内容为空。
 *
 * 值: 0x02001111
 *
 * 解决方案: 请保证传入的消息内容不为空。
 *
 */
#define OS_ERRNO_CACHE_ASYNC_MSG_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x11)

/**
 * @ingroup sre_cache
 * 消息错误码：解锁操作对应的地址区域未加锁。
 *
 * 值: 0x02001112
 *
 * 解决方案: 请检查传入解锁地址范围是否正确。
 *
 */
#define OS_ERRNO_CACHE_PCC_LOCK_REGION_UNLOCK               SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x12)

/**
 * @ingroup sre_cache
 * 消息错误码：L2 Cache控制基地址为0。
 *
 * 值: 0x02001113
 *
 * 解决方案: L2 Cache控制基地址不能为0。
 *
 */
#define OS_ERRNO_L2_CACHE_CTRL_BASE_ADDR_ZERO               SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x13)

/**
 * @ingroup sre_cache
 * 消息错误码：调用L2 Cache低功耗Suspend和Resume操作函数时，L2 Cache未初始化。
 *
 * 值: 0x02001114
 *
 * 解决方案: 调用L2 Cache低功耗Suspend和Resume操作函数前，需要对Cache进行初始化。
 *
 */
#define OS_ERRNO_L2_CACHE_NOT_INIT                          SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x14)

/**
 * @ingroup sre_cache
 * 消息错误码：重复或者覆盖注册已经注册的L2 Cache优化钩子。
 *
 * 值: 0x02001115
 *
 * 解决方案: 注册L2 Cache优化钩子时在取消前只能注册一次。
 *
 */
#define OS_ERRNO_L2_CACHE_HOOK_EXIST                        SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x15)

/**
 * @ingroup sre_cache
 * 消息错误码：重复Suspend L2 Cache。
 *
 * 值: 0x02001116
 *
 * 解决方案: Suspend L2 Cache后，必须Resume L2 Cache，才能再次Suspend L2 Cache。
 *
 */
#define OS_ERRNO_L2_CACHE_ALREADY_SUSPENDED                 SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x16)

/**
 * @ingroup sre_cache
 * 消息错误码：未Suspend L2 Cache前Resume L2 Cache。
 *
 * 值: 0x02001117
 *
 * 解决方案: 必须在Suspend L2 Cache后，才能Resume L2 Cache。
 *
 */
#define OS_ERRNO_L2_CACHE_NOT_SUSPENDED                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x17)

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 * @ingroup sre_cache
 * CACHE Tag 结构体信息。
 */
typedef struct tagCacheCb
{
    UINT32  uwCacheTag; /**< cache tag的完整信息                        */
    BOOL    bDirty;     /**< dcache中的数据是否被修改，仅对Dache有效    */
    BOOL    bLock;      /**< cache中的数据是否被加锁，仅对SD6182和SD6157平台有效 */
    BOOL    bValid;     /**< cache中的数据是否有效                      */
} CACHE_LINE_INFO_S;

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

/**
 * @ingroup sre_cache
 * CACHE Tag 结构体信息。
 */
typedef struct tagCacheCb
{
    UINT32 uwCacheTag;  /**< cache tag的完整信息                        */
    UINT32 uwCacheData; /**< cache data的完整信息                       */
} CACHE_LINE_INFO_S;

#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

typedef VOID  (* CACHE_INIT_HOOK)(VOID);
typedef VOID  (* CACHE_SUSPEND_HOOK)(VOID);
typedef VOID  (* CACHE_RESUME_HOOK)(VOID);

#endif
#if (OS_OPTION_DCACHE == NO)

/**
 * @ingroup sre_cache
 * 将数据Cache的内容回写到内存。
 */
#define  SRE_DCacheFlush(pAddr, uwSize, bWait)          SRE_OK

/**
 * @ingroup sre_cache
 * 将数据Cache中的内容无效。
 */
#define  SRE_DCacheInv(pAddr, uwSize, bWait)            SRE_OK

/**
 * @ingroup sre_cache
 * 将数据Cache里的内容回写到内存并无效该数据cache。
 */
#define  SRE_DCacheFlushInv(pAddr, uwSize, bWait)       SRE_OK

/**
 * @ingroup sre_cache
 * 等待DCache操作完成。
 */
#define  SRE_DCacheWait(VOID)

#else

/**
 * @ingroup  sre_cache
 * @brief 回写所有DCACHE
 *
 * @par 描述:
 * 刷新所有DCACHE, 将其中所有数据回写到内存
 *
 * @attention
 * <ul>
 * <li>只有SD6182、SD6157、CORTEX_AX平台和SD6181/SD6108 CPU核、SD6183支持刷新所有DCACHE功能</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，在关中断条件下进行该操作，关中断时间长短与整个Dcache大小成正比。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #SRE_OK                        0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlushAll(VOID);

/**
 * @ingroup  sre_cache
 * @brief 将数据Cache里的内容回写到内存。
 *
 * @par 描述:
 * 将指定地址区域的数据Cache内容回写到内存中。
 *
 * @attention
 * <ul>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>只有SD6182、SD6157、SD6108和SD6181的CPU核、SD6183、Cortex-AX支持该功能。</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，输入的参数#bWait必须为TRUE</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，在关中断条件下进行该操作，关中断时间长短与Dcache回写内存大小成正比。</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr    [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize   [IN] 类型#UINT32，内存块的大小。
 * @param  bWait    [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlush(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief 数据Cache回写并无效。
 *
 * @par 描述:
 * 将指定地址区域的数据Cache内容回写至内存并无效掉。
 *
 * @attention
 * <ul>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>只有SD6182、SD6157、SD6108和SD6181的CPU核、SD6183、Cortex-AX支持该功能。</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，输入的参数#bWait必须为TRUE</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，在关中断条件下进行该操作，关中断时间长短与Dcache回写并无效内存大小成正比。</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr   [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize  [IN] 类型#UINT32，内存块的大小。
 * @param  bWait   [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_ICacheInv
 */
extern UINT32 SRE_DCacheFlushInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief 数据Cache无效。
 *
 * @par 描述:
 * 将指定地址区域的数据Cache内容无效掉。
 *
 * @attention
 * <ul>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>只有SD6182、SD6157、SD6108和SD6181的CPU核、SD6183、Cortex-AX支持该功能。</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr   [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize  [IN] 类型#UINT32，内存块的大小。
 * @param  bWait   [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_ICacheInv | SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

#if ( (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup  sre_cache
 * @brief 预取数据CACHE
 *
 * @par 描述:
 * 将地址为pVirtAddr，大小为uwSize的内存数据预取到数据cache中，可根据参数bWait选择是否等待。
 *
 * @attention
 * <ul>
 * <li>只有SD6182、SD6157、SD6183平台支持预取DCACHE功能</li>
 * <li>用户传入的地址空间做cache line对齐后不能超过dcache大小</li>
 * </ul>
 *
 * @param  pVirtAddr  [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize     [IN] 类型#UINT32，内存块的大小。
 * @param  bWait      [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_DCachePrefetch(VOID * pVirtAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief 加锁指令cache
 *
 * @par 描述:
 * 对类型为uwCacheType，地址为pVirtAddr，大小为uwSize的指令cache进行加锁操作。
 *
 * @attention
 * <ul>
 * <li>只有SD6182、SD6157、SD6183平台支持加锁指令CACHE功能</li>
 * <li>不支持数据cache加锁</li>
 * <li>对于SD6182平台，cache加锁首地址和大小cache line对齐时，每组4-WAY至多能加锁3-WAY，因此最大加锁大小为cache大小的四分之三</li>
 * <li>对于SD6182平台，cache最小操作单位为一个cache line，考虑到首尾地址对齐情况，可能会浪费掉两个cache line，即最大可加锁大小可能为四分之三的cache大小减去两个cache line</li>
 * <li>对于SD6183平台，可以指定4个地址范围进行锁操作。cache空间可以全部被锁，某一Set全部被锁后，该Set对应其他数据不会再进cache。</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] 类型#UINT32，cache类型，OS_ICACHE_TYPE表示指令cache,目前只支持指令cache。
 * @param  pVirtAddr    [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize       [IN] 类型#UINT32，内存块的大小。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102，操作cache空间范围不合理。
 * @retval #OS_ERRNO_CACHE_NOAREA_LOCK    0x02001106，加锁余量不足。
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103，加锁类型不正确，目前只支持ICACHE。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_CacheUnLock
 */
extern UINT32 SRE_CacheLock(UINT32 uwCacheType, VOID *pVirtAddr,UINT32 uwSize);

/**
 * @ingroup  sre_cache
 * @brief 解锁指令cache
 *
 * @par 描述:
 * 对类型为uwCacheType，地址为pVirtAddr，大小为uwSize的指令cache进行解锁操作。
 *
 * @attention
 * <ul>
 * <li>只有SD6182、SD6157、SD6183平台支持解锁指令CACHE功能</li>
 * <li>不支持数据cache解锁</li>
 * <li>对于SD6182、SD6157平台，与加锁接口保持一致，最大解锁大小为四分之三的cache大小减去首尾地址cache line对齐带来的损耗</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] 类型#UINT32，cache类型，OS_ICACHE_TYPE表示指令cache,目前只支持指令cache。
 * @param  pVirtAddr    [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize       [IN] 类型#UINT32，内存块的大小。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102，操作cache空间范围不合理。
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103，解锁类型不正确，目前只支持ICACHE。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_CacheLock
 */
extern UINT32 SRE_CacheUnLock(UINT32 uwCacheType, VOID *pVirtAddr,UINT32 uwSize);
#endif

/**
 * @ingroup  sre_cache
 * @brief 等待数据Cache操作完成。
 *
 * @par 描述:
 * 等待DCache操作完成。
 *
 * @attention
 * <ul>
 * <li>Cortex-AX平台不支持此功能。</li>
 * <li>如果以不等待的方式使用数据cache的接口，建议使用这个接口保证安全性。</li>
 * </ul>
 *
 *@param 无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))
#ifndef _TOOL_WIN32
OS_SEC_ALW_INLINE INLINE VOID SRE_DCacheWait(VOID)
{
    OS_EMBED_ASM("memw");
}
#else
OS_SEC_ALW_INLINE INLINE VOID SRE_DCacheWait(VOID)
{
    ;
}

#endif
#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)
extern VOID SRE_DCacheWait(VOID);
#endif

#endif /* (OS_OPTION_DCACHE == NO) */

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup  sre_cache
 * @brief 无效所有指令Cache
 *
 * @par 描述:
 * 将所有指令Cache无效。
 *
 * @attention
 * <ul>
 * <li>只有SD6182,SD6157,SD6181,SD6108,SD6183平台支持无效所有指令Cache功能。</li>
 * <li>SD6182和SD6157平台指令Cache如果有锁，则该接口有解锁功能。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_ICacheInv
 */
extern VOID SRE_ICacheInvAll(VOID);

/**
 * @ingroup  sre_cache
 * @brief 获取指定地址的cache tag信息
 *
 * @par 描述:
 * 将类型为uwCacheType，地址为pVirtAddr的cache Tag信息获取并存储到pstCacheInfo结构体中。
 *
 * @attention
 * <ul>
 * <li>只有SD6182/SD6157/SD6181/SD6108/SD6183平台支持获取cache tag信息功能</li>
 * <li>SD6181/SD6108平台DSP核不支持获取dcache tag信息功能</li>
 * <li>如果获取的指定地址的Cache Tag信息为0，说明该地址不在Cache内</li>
 * </ul>
 *
 * @param  uwCacheType  [IN]  类型#UINT32，OS_ICACHE_TYPE表示指令cache，OS_DCACHE_TYPE表示数据cache。
 * @param  pVirtAddr    [IN]  类型#VOID *，内存块的起始地址，对于SD6182/SD6157平台，可Cache地址范围为[0x08000000, 0x60000000)，对于SD6181/SD08平台，可Cache地址范围为[0x10000000, 0x60000000)
 * @param  pstCacheInfo [OUT] 类型#CACHE_LINE_INFO_S *，获取的tag信息结构体。
 *
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103，cache类型输入不合理。
 * @retval #OS_ERRNO_CACHE_TAG_PTR_NULL   0x02001107，输入的存放Tag信息的指针为NULL。
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102，输入的地址不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_CacheLineInfoGet(UINT32 uwCacheType, VOID *pVirtAddr, CACHE_LINE_INFO_S *pstCacheInfo);

#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup  sre_cache
 * @brief 配置PCC模式
 *
 * @par 描述:
 * PCC 模式配置: UNIFY/SPLIT
 *
 * @attention
 * <ul>
 * <li>只有SD6183平台支持配置ICache模式</li>
 * </ul>
 *
 * @param  uwCoreID      [IN] 类型#UINT32，指定的核号。
 * @param  enMode        [IN] 类型#OS_CACHE_MODE，SPLIT/UNIFY模式。
 *
 * @retval #OS_ERRNO_CACHE_CORE_ID_INVALID   0x02001109，指定的核号非法。
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID      0x02001103，指定的cache类型非法。
 * @retval #SRE_OK                           0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_ICacheModeSet(UINT32 uwCoreID, OS_CACHE_MODE_E enMode);

/**
 * @ingroup  sre_cache
 * @brief 配置PCC硬件预取
 *
 * @par 描述:
 * PCC 的硬件预取的使能去使能，以及预取的策略设置
 *
 * @attention
 * <ul>
 * <li>只有SD6183平台支持配置ICache硬件预取策略</li>
 * </ul>
 *
 * @param  uwCoreID      [IN] 类型#UINT32，指定的核号。
 * @param  bEnable       [IN] 类型#BOOL，1:使能，0:去使能。
 * @param  enHwPfPolicy  [IN] 类型#OS_PCC_HWPF_POLICY_E，4种策略。
 *
 * @retval #OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID 0x0200110a，指定的硬件预取策略非法。
 * @retval #OS_ERRNO_CACHE_CORE_ID_INVALID         0x02001109，指定的核号非法。
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheHwPfCfg
 */
extern UINT32 SRE_ICacheHwPfCfg(UINT32 uwCoreID, BOOL bEnable, OS_PCC_HWPF_POLICY_E enHwPfPolicy);

/**
 * @ingroup  sre_cache
 * @brief 配置DCC硬件预取
 *
 * @par 描述:
 * DCC 的硬件预取的使能去使能，以及预取的策略设置
 *
 * @attention
 * <ul>
 * <li>只有SD6183平台支持配置DCache硬件预取策略</li>
 * </ul>
 *
 * @param  uwCoreID      [IN] 类型#UINT32，指定的核号。
 * @param  bEnable       [IN] 类型#BOOL，1:使能，0:去使能。
 * @param  enHwPfPolicy  [IN] 类型#OS_DCC_HWPF_POLICY_E，3种策略。
 *
 * @retval #OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID 0x0200110a，指定的硬件预取策略非法。
 * @retval #OS_ERRNO_CACHE_CORE_ID_INVALID         0x02001109，指定的核号非法。
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ICacheHwPfCfg
 */
extern UINT32 SRE_DCacheHwPfCfg(UINT32 uwCoreID, BOOL bEnable,  OS_DCC_HWPF_POLICY_E enHwPfPolicy);

/**
 * @ingroup  sre_cache
 * @brief 异步方式将数据Cache里的内容回写到内存并发送消息。
 *
 * @par 描述:
 * 将指定地址区域的数据Cache内容回写到内存中，当操作完成时向目标地址发送消息通知。
 *
 * @attention
 * <ul>
 * <li>只有SD6183平台支持异步方式回写数据cache，只能向MSGM的地址空间发送消息</li>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>当uwSize为0xffffffff时，相当于回写全部的数据cache</li>
 * <li>通过MSGM的SRE_QportAddrGet接口可以得到目标核指定队列的地址，详见sre_msgm.h</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr     [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize    [IN] 类型#UINT32，内存块的大小。
 * @param  bWait     [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 * @param  uwDstAddr [IN] 类型#UINT32，目标MSGM队列的首地址。
 * @param  auwData   [IN] 类型#UINT32*，待发送的消息内容首地址，消息内容长度须为16字节。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #OS_ERRNO_CACHE_ASYNC_MSG_NULL 0x02001111，发送的消息内容为空。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheFlush
 */
extern UINT32 SRE_DCacheFlushAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

/**
 * @ingroup sre_cache
 * @brief 异步方式数据Cache无效并发送消息。
 *
 * @par 描述:
 * 异步方式将指定地址区域的数据Cache内容无效,当操作完成时向目标地址发送消息通知。
 *
 * @attention
 * <ul>
 * <li>只有SD6183平台支持异步方式无效数据cache，只能向MSGM的地址空间发送消息</li>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>当uwSize为0xffffffff时，相当于无效全部的数据cache</li>
 * <li>通过MSGM的接口可以得到目标核指定队列的地址，详见sre_msgm.h</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr     [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize    [IN] 类型#UINT32，内存块的大小。
 * @param  bWait     [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 * @param  uwDstAddr [IN] 类型#UINT32，目标MSGM队列的首地址。
 * @param  auwData   [IN] 类型#UINT32，待发送的消息内容。

 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #OS_ERRNO_CACHE_ASYNC_MSG_NULL 0x02001111，发送的消息内容为空。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheInv
 */
extern UINT32 SRE_DCacheInvAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

/**
 * @ingroup  sre_cache
 * @brief 异步方式将数据Cache回写并无效后发送消息。
 *
 * @par 描述:
 * 异步方式将指定地址区域的数据Cache内容回写至内存并无效,当操作完成时向目标地址发送消息通知。
 *
 * @attention
 * <ul>
 * <li>只有SD6183平台支持异步方式回写并无效数据cache，只能向MSGM的地址空间发送消息</li>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>当uwSize为0xffffffff时，相当于回写无效全部的数据cache。</li>
 * <li>通过MSGM的接口可以得到目标核指定队列的地址，详见sre_msgm.h</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr     [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize    [IN] 类型#UINT32，内存块的大小。
 * @param  bWait     [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 * @param  uwDstAddr [IN] 类型#UINT32，目标MSGM队列的首地址。
 * @param  auwData   [IN] 类型#UINT32 *，待发送的消息内容。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #OS_ERRNO_CACHE_ASYNC_MSG_NULL 0x02001111，发送的消息内容为空。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlushInvAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  sre_cache
 * @brief Cache初始化
 *
 * @par 描述:
 * 对L1/L2进行Cache初始化，以使能L1/L2 Cache功能。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户需要使用L2 Cache功能时，才需要调用此接口。</li>
 * <li>此接口必须要在#SRE_HardBootInit中调用。</li>
 * </ul>
 *
 * @param  uwL2CtrBase   [IN] 类型#UINT32，L2 Cache控制基地址，需要配置成实际的L2 Cache控制基地址。
 *
 * @retval #OS_ERRNO_L2_CACHE_CTRL_BASE_ADDR_ZERO  0x02001113，传入的L2 Cache控制基地址为0。
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheInitHookReg
 */
extern UINT32 SRE_CacheInit(UINT32 uwL2CtrBase);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Suspend操作
 *
 * @par 描述:
 * 进入低功耗前，L2 Cache Suspend操作。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户使用L2 Cache功能时，才需要调用此接口。</li>
 * <li>需要在进入低功耗前调用此接口。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT             0x02001114，必须在L2 Cache初始化后调用此接口。
 * @retval #OS_ERRNO_L2_CACHE_ALREADY_SUSPENDED    0x02001116，L2 Cache已经被Suspend。
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheResume
 */
extern UINT32 SRE_CacheSuspend(VOID);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Resume操作
 *
 * @par 描述:
 * 进入低功耗前，L2 Cache Resume操作。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户使用L2 Cache功能时，才需要调用此接口。</li>
 * <li>需要在唤醒低功耗后调用此接口。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT             0x02001114，必须在L2 Cache初始化后调用此接口。
 * @retval #OS_ERRNO_L2_CACHE_NOT_SUSPENDED        0x02001117，L2 Cache未Suspend。
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheSuspend
 */
extern UINT32 SRE_CacheResume(VOID);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache 初始化阶段优化钩子函数注册
 *
 * @par 描述:
 * L2 Cache 初始化阶段优化钩子函数注册。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户使用L2 Cache功能时，才需要调用此接口。</li>
 * <li>必须要在Cache初始化前调用此接口。</li>
 * <li>通过该接口注册的钩子在初始化阶段L2 Cache去使能状态下调用。</li>
 * <li>该钩子不允许重复或者覆盖注册，否则注册失败；当传入NULL时，表示去除该优化钩子函数。</li>
 * </ul>
 *
 * @param  pfnCacheInitHook   [IN] 类型#CACHE_INIT_HOOK，L2 Cache初始化阶段优化钩子函数。
 *
 * @retval #OS_ERRNO_L2_CACHE_HOOK_EXIST           0x02001115，注册钩子已经存在
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheInit
 */
extern UINT32 SRE_CacheInitHookReg(CACHE_INIT_HOOK pfnCacheInitHook);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Suspend阶段优化钩子函数注册
 *
 * @par 描述:
 * L2 Cache Suspend阶段优化钩子函数注册。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户使用L2 Cache功能时，才需要调用此接口。</li>
 * <li>必须要在L2 Cache Suspend前调用此接口。</li>
 * <li>通过该接口注册的钩子在Suspend阶段L2 Cache使能状态下调用。</li>
 * <li>该钩子不允许重复或者覆盖注册，否则注册失败；当传入NULL时，表示去除该优化钩子函数。</li>
 * </ul>
 *
 * @param  pfnCacheSuspendHook   [IN] 类型#CACHE_SUSPEND_HOOK，L2 Cache Suspend阶段优化钩子函数。
 *
 * @retval #OS_ERRNO_L2_CACHE_HOOK_EXIST           0x02001115，注册钩子已经存在
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheResumeHookReg
 */
extern UINT32 SRE_CacheSuspendHookReg(CACHE_SUSPEND_HOOK pfnCacheSuspendHook);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Resume阶段优化钩子函数注册
 *
 * @par 描述:
 * L2 Cache Resume阶段优化钩子函数注册。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户使用L2 Cache功能时，才需要调用此接口。</li>
 * <li>必须要在L2 Cache Resume前调用此接口。</li>
 * <li>通过该接口注册的钩子在Resume阶段L2 Cache去使能状态下调用。</li>
 * <li>该钩子不允许重复或者覆盖注册，否则注册失败；当传入NULL时，表示去除该优化钩子函数。</li>
 * </ul>
 *
 * @param  pfnCacheResumeHook   [IN] 类型#CACHE_RESUME_HOOK，L2 Cache Resume阶段优化钩子函数。
 *
 * @retval #OS_ERRNO_L2_CACHE_HOOK_EXIST           0x02001115，注册钩子已经存在
 * @retval #SRE_OK                                 0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheSuspendHookReg
 */
extern UINT32 SRE_CacheResumeHookReg(CACHE_RESUME_HOOK pfnCacheResumeHook);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache同步
 *
 * @par 描述:
 * L2 Cache同步功能。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能，并且只有当用户使用L2 Cache功能时，才需要调用此接口。</li>
 * </ul>
 *
 * @param  NONE
 *
 * @retval NONE
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_CacheInit
 */
extern VOID SRE_L2CacheWait(VOID);

#endif



/**
 * @ingroup  sre_cache
 * @brief 无效指令Cache
 *
 * @par 描述:
 * 将指定地址区域的指令Cache置为无效。
 *
 * @attention
 * <ul>
 * <li>只有SD6182,SD6157,SD6181,SD6108,Cortex-AX,SD6183平台支持无效指令功能。</li>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>为保证指令cache操作的安全性，Icache操作都是以等待方式操作，bWait参数无效。</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，输入的参数#bWait必须为TRUE</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，在关中断条件下进行该操作，关中断时间长短与Icache无效内存大小成正比。</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr   [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize  [IN] 类型#UINT32，内存块的大小。
 * @param  bWait   [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 *
 * @retval #OS_ERRNO_CACHE_ADDR_LOCKED    0x02001108，对SD6182和SD6157平台，请检查无效地址是否已经加锁。
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_ICacheInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief 更新指令及数据Cache
 *
 * @par 描述:
 * 将指定地址区域回写并无效数据Cache，然后再无效指令cache。
 *
 * @attention
 * <ul>
 * <li>只有SD6182,SD6157,SD6181,SD6108,Cortex-AX,SD6183平台支持更新指令及数据Cache功能。</li>
 * <li>Cache操作的最小单位为Cache line。因此，操作范围为指定地址区域所跨的所有Cache line。</li>
 * <li>无DCACHE情况下，此接口等同SRE_ICacheInv。</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，输入的参数#bWait必须为TRUE</li>
 * <li>对于Cortex-A9平台，当L2 Cache功能打开时，在关中断条件下进行该操作，关中断时间长短与Icache无效内存大小成正比。</li>
 * <li>对于SD6183平台，用户传入的虚拟地址空间对应的物理地址空间必须连续且没有翻转</li>
 * </ul>
 *
 * @param  pAddr   [IN] 类型#VOID *，内存块的起始地址。
 * @param  uwSize  [IN] 类型#UINT32，内存块的大小。
 * @param  bWait   [IN] 类型#BOOL，TRUE为等Cache操作完成后才返回，FALSE为执行操作指令后立即返回。
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101，操作cache区域大小不合法。
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239，SD6183平台输入的虚地址未映射。
 * @retval #SRE_OK                        0x00000000，操作成功。
 *
 * @par 依赖:
 * <ul><li>sre_cache.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv | SRE_ICacheInv
 */
extern UINT32 SRE_CacheUpdate(VOID *pAddr, UINT32 uwSize, BOOL bWait);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_CACHE_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

