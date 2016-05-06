/**
 * @file sre_mmu.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：mmu模块的对外头文件。 \n
 */
 /**@defgroup SRE_mmu MMU
  *@ingroup SRE_kernel
 */

#ifndef _SRE_MMU_H
#define _SRE_MMU_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define MMU_VA_T VOID*
#define MMU_PA_T VOID*

/**
 * @ingroup SRE_mmu
 * 错误码：虚拟地址、物理地址或长度非page对齐。
 *
 * 值: 0x02001201
 *
 * 解决方案: 检查入参虚拟地址、物理地址、长度是否page(代码段映射需要8k, 数据段映射需要4k)对齐。
 */
#define OS_ERRNO_MMU_NOT_PAGE_ALIGNED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1)

/**
 * @ingroup SRE_mmu
 * 错误码：找到虚拟地址对应的物理地址为0，或者配置MMU段的物理地址或长度为0。
 *
 * 值: 0x02001202
 *
 * 解决方案: 请检查MMU段配置的物理地址或长度是否为0。
 */
#define OS_ERRNO_MMU_SECTION_CFG_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x2)

/**
 * @ingroup SRE_mmu
 * 错误码：未申请到一级页表内存。
 *
 * 值: 0x02001203
 *
 * 解决方案: 配置足够大的内存分区。
 */
#define OS_ERRNO_MMU_NO_LEVEL1_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3)

/**
 * @ingroup SRE_mmu
 * 错误码：映射虚拟地址空间已经映射或者部分已经映射。
 *
 * 值: 0x02001204
 *
 * 解决方案: 检查所映射的虚拟地址空间是否已经映射或部分已经映射。
 */
#define OS_ERRNO_MMU_ADDR_MAPPED                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4)

/**
 * @ingroup SRE_mmu
 * 错误码：未申请到二级页表内存。
 *
 * 值: 0x02001205
 *
 * 解决方案: 配置足够大的内存分区。
 */
#define OS_ERRNO_MMU_NO_LEVEL2_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x5)

/**
 * @ingroup SRE_mmu
 * 错误码：未申请到页表映射信息内存。
 *
 * 值: 0x02001206
 *
 * 解决方案: 配置足够大的内存分区。
 */
#define OS_ERRNO_MMU_NO_MAP_INFO_MEMORY                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x6)

/**
 * @ingroup SRE_mmu
 * 错误码：MMU模块初始化内存映射信息重复。
 *
 * 值: 0x02001207
 *
 * 解决方案: 检查MMU初始化内存映射信息是否重复。
 */
#define OS_ERRNO_MMU_INIT_ADDR_OVERLAPPED                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x7)

/**
 * @ingroup SRE_mmu
 * 错误码：(去)映射内存地址设置溢出。
 *
 * 值: 0x02001209
 *
 * 解决方案: 请检查(去)映射地址和长度配置是否合理。
 */
#define OS_ERRNO_MMU_ADDR_OVERFLOW                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x09)

/**
 * @ingroup SRE_mmu
 * 错误码：虚拟地址未映射。
 *
 * 值: 0x02001210
 *
 * 解决方案: 检查虚拟地址是否映射或MMU初始化地址是否包含内存分区所有地址。
 */
#define OS_ERRNO_MMU_ADDR_NOT_MAPPED                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x10)

/**
 * @ingroup SRE_mmu
 * 错误码：页表拆分时内存空间不足。
 *
 * 值: 0x02001211
 *
 * 解决方案: 配置空间足够的0号分区。
 */
#define OS_ERRNO_MMU_DEOPTIMIZE_FAIL                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x11)

/**
 * @ingroup SRE_mmu
 * 错误码：长度不足合并为大页表。
 *
 * 值: 0x02001212
 *
 * 解决方案: 检查入参虚拟地址和长度是否正确。
 */
#define OS_ERRNO_MMU_OPTIMIZE_NO_NEED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x12)

/**
 * @ingroup SRE_mmu
 * 错误码：0号分区映射的虚拟地址和物理地址不一致。
 *
 * 值: 0x02001214
 *
 * 解决方案: 检查初始化时内存分区地址虚拟地址和物理地址是否一致。
 */
#define OS_ERRNO_MMU_MEM_PT_NOT_FLAT                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x14)

/**
 * @ingroup SRE_mmu
 * 错误码：初始化映射信息未包含整个0号分区信息。
 *
 * 值: 0x02001215
 *
 * 解决方案: 检查初始化时内存分区地址是否均包含在映射信息中。
 */
#define OS_ERRNO_MMU_MEM_PT_NOT_INCLUDE                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x15)

/**
 * @ingroup SRE_mmu
 * 错误码：初始化映射信息0号分区内存属性不一致。
 *
 * 值: 0x02001216
 *
 * 解决方案: 检查初始化时内存分区属性是否一致。
 */
#define OS_ERRNO_MMU_MEM_PT_STATE_DIFFERENT                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x16)

/**
 * @ingroup SRE_mmu
 * 错误码：ATTRIBUTE属性配错。
 *
 * 值: 0x02001217
 *
 * 解决方案: 检查ATTRIBUTE属性是否为属性宏的一种。
 */
#define OS_ERRNO_MMU_ATTRIBUTE_ERR                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x17)

/**
 * @ingroup SRE_mmu
 * 错误码：ACCESS属性配错。
 *
 * 值: 0x02001218
 *
 * 解决方案: 检查写属性是否或上读属性，检查可执行属性是否或上读属性。
 */
#define OS_ERRNO_MMU_ACCESS_ERR                                  SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x18)

/**
 * @ingroup SRE_mmu
 * 错误码：初始化映射信息0号分区属性未配置成可cache。
 *
 * 值: 0x02001219
 *
 * 解决方案: 检查初始化时内存分区地址属性是否配成wbwa或wbnwa。
 */
#define OS_ERRNO_MMU_MEM_PT_STATE_ERR                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x19)

/**
 * @ingroup SRE_mmu
 * 错误码：初始化映射信息未配置或映射数组起始地址、元素个数配置成0。
 *
 * 值: 0x0200121a
 *
 * 解决方案: 检查config配置项中MMU初始化映射信息是否配置，检查映射数组起始地址、元素个数是否配置为0。
 */
#define OS_ERRNO_MMU_INIT_INFO_NOT_CONFIG                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1a)

/**
 * @ingroup SRE_mmu
 * 错误码：入参错误。
 *
 * 值: 0x0200121b
 *
 * 解决方案: 检查入参。
 */
#define OS_ERRNO_MMU_PARAM_INVALID                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1b)

/**
 * @ingroup SRE_mmu
 * 错误码：MMU模式配置错误。
 *
 * 值: 0x0200121c
 *
 * 解决方案: MMU模式错误，只能是BYPASS,MMU三种模式。
 */
#define OS_ERRNO_MMU_MODE_INVALID                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1c)

/**
 * @ingroup SRE_mmu
 * 错误码：TLB 内容查询时index错误。
 *
 * 值: 0x0200121d
 *
 * 解决方案: TLB查询时index有效范围是0~31。
 */
#define OS_ERRNO_MMU_TLB_INDEX_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1d)

/**
 * @ingroup SRE_mmu
 * 错误码：TLB 类型错误。
 *
 * 值: 0x0200121e
 *
 * 解决方案: TLB 类型错误，只能是ITLB,DTLB两种。
 */
#define OS_ERRNO_MMU_TLB_TYPE_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1e)

/**
 * @ingroup SRE_mmu
 * 错误码：TLB 无效策略非法。
 *
 * 值: 0x0200121f
 *
 * 解决方案: TLB 无效策略非法，只能是PAGE_INV,LINE_INV,ALL_INV三种。
 */
#define OS_ERRNO_MMU_TLB_INV_POLICY_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1f)

/**
 * @ingroup SRE_mmu
 * 错误码：TLB way number非法。
 *
 * 值: 0x02001220
 *
 * 解决方案: WAY number只能是0~7。
 */
#define OS_ERRNO_MMU_WAY_NUMBER_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x20)

/**
 * @ingroup SRE_mmu
 * 错误码：获取的对应index的L1TLB内容无效。
 *
 * 值: 0x02001221
 *
 * 解决方案: 确保该index输入正确以及对应的TLB内容未被无效或者替换。
 */
#define OS_ERRNO_MMU_TLB_DATA_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x21)

/**
 * @ingroup SRE_mmu
 * 错误码：Page Size非法。
 *
 * 值: 0x02001222
 *
 * 解决方案: 修改Page Size。
 */
#define OS_ERRNO_MMU_PAGE_SIZE_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x22)

/**
 * @ingroup SRE_mmu
 * 错误码：SYSTEM MODE非法。
 *
 * 值: 0x02001223
 *
 * 解决方案: 只能为SUPER_MODE或者USER_MODE。
 */
#define OS_ERRNO_MMU_SYS_MODE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x23)

/**
 * @ingroup SRE_mmu
 * 错误码：设置的内存属性非法。
 *
 * 值: 0x02001224
 *
 * 解决方案: 使用OS提供的属性宏设置内存的属性，属性宏具体信息查看SRE_MmuAssign或SRE_MmuMcAssign接口说明。
 */
#define OS_ERRNO_MMU_PAGEMAP_STATE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x24)

/**
 * @ingroup SRE_mmu
 * 错误码：MMU模式下，实地址转虚地址失败。
 *
 * 值: 0x02001227
 *
 * 解决方案: MMU模式下，实地址未进行映射。
 */
#define OS_ERRNO_MMU_PA2VA_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x27)

/**
 * @ingroup SRE_mmu
 * 错误码：地址转换接口，入参虚拟地址、物理地址非4字节对齐。
 *
 * 值: 0x02001228
 *
 * 解决方案: 检查入参虚拟地址、物理地址是否4字节对齐。
 */
#define OS_ERRNO_MMU_NOT_WORD_ALIGNED                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x28)

/**
 * @ingroup SRE_mmu
 * 错误码：二级页表内存不够。
 *
 * 值: 0x02001229
 *
 * 解决方案: 扩大二级页表空间
 */
#define OS_ERRNO_MMU_SIZE_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x29)

/**
 * @ingroup SRE_mmu
 * 错误码：L2TLB setindex number非法。
 *
 * 值: 0x02001230
 *
 * 解决方案: setindex只能是0~127。
 */
#define OS_ERRNO_MMU_SET_NUMBER_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x30)

/**
 * @ingroup SRE_mmu
 * 错误码：地址映射时，发现L1TLB中部分或者全部虚地址已经配置。
 *
 * 值: 0x02001231
 *
 * 解决方案: 先调用SRE_MmuUnAssign丢弃已经配置的页表描述符，取消映射后，再重新映射，或者映射在其他未映射的地址。
 */
#define OS_ERRNO_MMU_VADDR_L1TLB_OVERLAP                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x31)

/**
 * @ingroup SRE_mmu
 * 错误码：地址映射时，发现L2TLB中部分或者全部虚地址已经配置。
 *
 * 值: 0x02001232
 *
 * 解决方案: 先调用SRE_MmuUnAssign丢弃已经配置的页表描述符，取消映射后，再重新映射，或者映射在其他未映射的地址。
 */
#define OS_ERRNO_MMU_VADDR_L2TLB_OVERLAP                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x32)


/**
 * @ingroup SRE_mmu
 * 错误码：配置页表基地址未按0x4000字节(16K)大小对齐。
 *
 * 值: 0x02001233
 *
 * 解决方案: 检查配置页表基地址是否按0x4000字节大小对齐。
 */
#define OS_ERRNO_MMU_PAGE_TBL_ADDR_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x33)

/**
 * @ingroup SRE_mmu
 * 错误码：配置页表长度未按0x400字节(1k)大小对齐。
 *
 * 值: 0x02001234
 *
 * 解决方案: 检查配置页表长度是否按0x400字节大小对齐。
 */
#define OS_ERRNO_MMU_PAGE_TBL_LEN_NOT_ALIGN                     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x34)

/**
 * @ingroup SRE_mmu
 * 错误码：传入的页表地址或长度非法。
 *
 * 值: 0x02001235
 *
 * 解决方案: 请确保传入的页表参数的正确性(包括页表地址不能为0，页表长度不能为0，
   若OS进行MMU页表映射MAP的建立，则保证页表大于等于0x4000（16K）;
   若采用工具(如SDK) 进行MMU页表映射MAP的建立，则页表大小配置必须保证能完成所有段的映射,建议增加页表长度。
 */
#define OS_ERRNO_MMU_PAGE_TBL_CFG_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x35)

/**
 * @ingroup SRE_mmu
 * 错误码： L2 TLB查找顺序错误。
 *
 * 值: 0x02001236
 *
 * 解决方案: L2 TLB寄存器里面必须包含8种类型的页表大小，且8种类型仅出现一次。
 */
#define OS_ERRNO_MMU_L2TLB_ORDER_ERR                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x36)

/**
 * @ingroup SRE_mmu
 * 错误码：核号错误。
 *
 * 值: 0x02001237
 *
 * 解决方案: 核号不能大于33。
 */
#define OS_ERRNO_MMU_COREID_ERR                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x37)


/**
 * @ingroup SRE_mmu
 * 错误码：MMU模式下，虚地址转实地址失败。
 *
 * 值: 0x02001239
 *
 * 解决方案: MMU模式下，虚地址未进行映射。
 */
#define OS_ERRNO_MMU_VA2PA_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x39)

/**
 * @ingroup SRE_mmu
 * 错误码：MMU无效的时候ContextID错误。
 *
 * 值: 0x0200123a
 *
 * 解决方案: 检查当前输入的ContextID是否无效。
 */
#define OS_ERRNO_MMU_TLB_INV_CONTEXT_ID_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3a)

/**
 * @ingroup SRE_mmu
 * 错误码：MMU页表去映射(配置属性)时，传入的参数未按照配置的页表大小对齐。
 *
 * 值: 0x0200123b
 *
 * 解决方案: 先把要地址范围传入SRE_MmuPageSpaceGet获得页表对齐后的地址范围。
 */
#define OS_ERRNO_MMU_PAGE_NOT_ALIGNED                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3b)

/**
 * @ingroup SRE_mmu
 * 错误码：获取MMU内存属性时，入参指针参数为空。
 *
 * 值: 0x0200123c
 *
 * 解决方案: 确保存储内存属性输出值的指针不能为空。
 */
#define OS_ERRNO_MMU_ATTR_OUTPUT_POINT_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3c)

/**
 * @ingroup SRE_mmu
 * 错误码：获取MMU内存属性时，输入指定的内存属性类型非法。
 *
 * 值: 0x0200123d
 *
 * 解决方案: 请确保输入的属性类型值为[OS_MMU_PERMISSION, OS_MMU_CACHE]
 */
#define OS_ERRNO_MMU_ATTR_TYPE_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3d)

/**
 * @ingroup SRE_mmu
 * 错误码：实虚地址转换空间不足
 *
 * 值: 0x0200123f
 *
 * 解决方案: 增大OS_MMU_PHYTOVIR_SIZE配置，确保内存空间够用。
 */
#define OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL                       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3f)

/**
 * @ingroup SRE_mmu
 * 错误码：实虚地址转换去映射失败
 *
 * 值: 0x02001240
 *
 * 解决方案: 确定是否已经完成虚实地址映射。
 */
#define OS_ERRNO_MMU_PA_VA_REMOVE_FAIL                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x40)

/**
 * @ingroup SRE_mmu
 * 错误码：实虚地址转换空间及大小未对齐
 *
 * 值: 0x02001241
 *
 * 解决方案: 检查OS_MMU_PHYTOVIR_ADDR，OS_MMU_PHYTOVIR_SIZE配置是否8字节对齐。
 */
#define OS_ERRNO_MMU_PA_VA_UN_ALIGN                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x41)

/**
 * @ingroup SRE_mmu
 * 错误码：实虚地址转换空间未配置，不能使用SRE_MmuPA2VA
 *
 * 值: 0x02001242
 *
 * 解决方案: 检查OS_MMU_PHYTOVIR_SIZE配置是否配置为0。
 */
#define OS_ERRNO_MMU_PA_VA_UNCONFIG                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x42)

/**
 * @ingroup SRE_mmu
 * 错误码：mmu模块申请名字空间失败
 *
 * 值: 0x02001243
 *
 * 解决方案: 增大实例间名字空间大小。
 */
#define OS_ERRNO_MMU_NAME_ALLOC_FAILED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x43)

/**
 * @ingroup SRE_mmu
 * 错误码：配置指定核的MMU时，未完成MMU消息队列初始化
 *
 * 值: 0x02001244
 *
 * 解决方案: 主核未进行OS初始化流程，就给指定核配置消息内存。
 */
#define OS_ERRNO_MMU_MSG_UNINIT                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x44)

/**
 * @ingroup SRE_mmu
 * 错误码：配置指定核的MMU时，给指定核发送消息失败
 *
 * 值: 0x02001245
 *
 * 解决方案: 若链接未被踩，那么原因就是未完成指定核MMU消息队列初始化，需要先调用SRE_MemCfg接口配置，申请并初始化指定核MMU消息队列。
 */
#define OS_ERRNO_MMU_MSG_SEND_FAIL                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x45)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：实例ID超过最大值
 *
 * 值: 0x02001246
 *
 * 解决方案:实例ID不合法
 */
#define OS_ERRNO_MMU_INST_ID_TOO_MAX           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x46)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：硬件线程ID超过最大值
 *
 * 值: 0x02001247
 *
 * 解决方案:硬件线程ID不合法
 */
#define OS_ERRNO_MMU_CORE_ID_TOO_MAX           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x47)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：实例未准备好
 *
 * 值: 0x02001248
 *
 * 解决方案:实例创建并完成资源配置后，才能调用
 */
#define OS_ERRNO_MMU_INST_NOT_READY            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x48)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：coreID错误
 *
 * 值: 0x02001249
 *
 * 解决方案:用户的coreID不在实例的bitMap内
 */
#define OS_ERRNO_MMU_COREID_NOT_EXIST          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x49)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：从实例未创建的情况下，给从核配置MMU
 *
 * 值: 0x0200124a
 *
 * 解决方案:创建从实例后再给从核配置MMU
 */
#define OS_ERRNO_MMU_SLAVE_INST_UNCREATE       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4a)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：主核初始化MMU消息队列时，申请内存失败
 *
 * 值: 0x0200124b
 *
 * 解决方案:确认有名空间是否已经配置
 */
#define OS_ERRNO_MMU_MSG_ALLOC_FAILED          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4b)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：使用非优化接口映射MMU时，不允许跨越不同的内存区间
 *
 * 值: 0x0200124c
 *
 * 解决方案:使用非优化接口映射MMU时，不允许跨越不同的内存区间
 */
#define OS_ERROR_MEM_REGION_OVERLAY          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4c)


/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：使用非优化接口映射MMU时，对齐方式不正确
 *
 * 值: 0x0200124d
 *
 * 解决方案:使用非优化接口映射MMU时，DDR需要按照1M对齐，其他的内存要按照4K(数据段)或8K(代码段)对齐
 */
#define OS_ERRNO_MMU_NOT_CORRECT_ALIGNED     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4d)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：MMU消息发送时，申请消息节点失败
 *
 * 值: 0x0200124e
 *
 * 解决方案:无
 */
#define OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4e)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：MMU修改属性时不允许修改寄存器空间属性
 *
 * 值: 0x0200124f
 *
 * 解决方案:无
 */
#define OS_ERRNO_MMU_REG_REGION_PROTECT        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4f)

/**
 * @ingroup SRE_MNG
 * SRE MNG错误码：MMU修改属性时内存段包含了受保护的寄存器空间
 *
 * 值: 0x02001250
 *
 * 解决方案:无
 */
#define OS_ERRNO_MMU_SETATTR_PROTECT_REGION_COVERRED       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x50)

/**
 * @ingroup  SRE_mmu
 * @brief 虚地址转实地址。
 *
 * @par 描述:
 * 虚地址转实地址。
 *
 * @attention
 * <ul>
 * <li>AX平台若入参为未映射地址，会返回错误码，查询到的物理地址为虚拟地址本身。</li>
 * <li>AX平台只允许MMU模块初始化完成后调用。</li>
 * <li>该操作仅在SD6183和Cortex-AX平台下支持。</li>
 * </ul>
 *
 * @param  pVAddr  [IN] 类型#MMU_VA_T，虚拟地址。
 * @param  ppPAddr  [OUT] 类型#MMU_PA_T，转换后的物理地址。
 *
 * @retval #OS_ERRNO_MMU_PARAM_INVALID       0x0200121b，入参为空。
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED     0x02001210，地址未映射。
 * @retval #SRE_OK                           0x00000000，转换成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 SRE_MmuVA2PA(MMU_VA_T pVAddr, MMU_PA_T *ppPAddr);

/**
 * @ingroup  SRE_mmu
 * @brief 实地址转虚地址。
 *
 * @par 描述:
 * 实地址转虚地址。
 *
 * @attention
 * <ul>
 * <li>AX平台只允许MMU模块初始化完成后MMU模式下调用。</li>
 * <li>AX平台若入参为未映射地址，会返回错误码，查询到的虚拟地址为物理地址本身。</li>
 * <li>该操作仅在SD6183和Cortex-AX平台下支持。</li>
 * </ul>
 *
 * @param  pPAddr  [IN] 类型#MMU_PA_T，物理地址。
 * @param  ppVAddr [OUT] 类型#MMU_VA_T，转换后的虚拟地址。
 *
 * @retval #OS_ERRNO_MMU_PARAM_INVALID       0x0200121b，入参为空。
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED     0x02001210，AX平台实地址未映射。
 * @retval #OS_ERRNO_MMU_PA_VA_UNCONFIG      0x02001242，实虚地址空间未配置。
 * @retval #OS_ERRNO_MMU_PA2VA_ERROR         0x02001227，SD6183平台MMU模式下实地址未映射。
 * @retval #SRE_OK                           0x00000000，转换成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 SRE_MmuPA2VA(MMU_PA_T pPAddr, MMU_VA_T *ppVAddr);

/**
 * @ingroup  SRE_mmu
 * @brief 映射虚拟地址到物理地址。
 *
 * @par 描述:
 * 根据传入参数pVStart、pPStart、uwLen进行虚拟、物理地址映射，并按照uwAttr设置内存属性。
 *
 * @attention
 * <ul>
 * <li>uwLen为0时不进行地址映射，直接返回成功。</li>
 * <li>AX平台只允许MMU模块初始化完成后调用。</li>
 * <li>AX平台代码段和分配给OS使用的内存区映射方式必须虚拟地址和物理地址一致。</li>
 * <li>AX平台地址映射时，从uwVirtAddr开始对page逐个进行映射。某一页映射不成功时，已经映射成功的地址保持映射关系。</li>
 * <li>SD6183平台地址映射时，优先映射成大页。</li>
 * <li>SD6183平台MMU去映射及映射的内存区域cache一致性由用户保证。</li>
 * <li>SD6183平台MMU配置的虚实地址，长度都必须按照4K对齐，如果是可执行的代码段，必须按照8K对齐</li>
 * </ul>
 *
 * @param  pVStart       [IN] 类型#MMU_VA_T，映射虚拟地址起始地址。
 * @param  pPStart       [IN] 类型#MMU_PA_T，映射物理地址起始地址。
 * @param  uwLen         [IN] 类型#UINT32，映射的内存大小。
 * @param  uwAttr        [IN] 类型#UINT32，内存属性，SD6183平台uwAttr有效bit位为(bit7-0)，bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201，传入参数虚拟地址、物理地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203，未申请到一级页表内存。
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204，传入虚拟地址已经映射过。
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205，未申请到二级页表内存。
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206，未申请到页表映射信息内存。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，地址溢出。
 * @retval #OS_ERRNO_MEM_FREE_SH_DAMAGED        0x02000311，内存释放时要释放的内存块的头被破坏，或已释放。
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217，入参uwState的ATTRIBUTE属性配置不正确。
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218，入参uwState的ACCESS属性配置不正确。
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL   0x0200123f，新的实虚映射节点申请内存失败。
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED  0x0200124e，MMU消息发送时，申请消息节点失败。
 * @retval #SRE_OK                              0x00000000，虚拟、物理地址映射成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern UINT32 SRE_MmuAssign(MMU_VA_T pVStart, MMU_PA_T pPStart,
                                  UINT32 uwLen, UINT32 uwAttr);


#if(OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_mmu
 * MMU内存属性-可读。
 */
#define OS_MMU_STATE_READ                                      0x1

/**
 * @ingroup SRE_mmu
 * MMU内存属性-可写。
 *
 * 该属性宏配置时需要或上OS_MMU_STATE_READ属性
 */
#define OS_MMU_STATE_WRITE                                     0x2

/**
 * @ingroup SRE_mmu
 * MMU内存属性-可执行。
 *
 * 该属性宏配置时需要或上OS_MMU_STATE_READ属性
 */
#define OS_MMU_STATE_EXE                                       0x4

/**
 * @ingroup SRE_mmu
 * MMU内存属性-strong ordered。
 */
#define OS_MMU_STATE_STRONGLY_ORDERED                          0x8

/**
 * @ingroup SRE_mmu
 * MMU内存属性-shared device。
 */
#define OS_MMU_STATE_SHARED_DEVICE                             0x10

/**
 * @ingroup SRE_mmu
 * MMU内存属性-device。
 */
#define OS_MMU_STATE_DEVICE                                    0x20

/**
 * @ingroup SRE_mmu
 * MMU内存属性-不可cache。
 */
#define OS_MMU_STATE_CACHE_OFF                                 0x40

/**
 * @ingroup SRE_mmu
 * MMU内存属性-cache wbwa。
 */
#define OS_MMU_STATE_CACHE_WBWA                                0x80

/**
 * @ingroup SRE_mmu
 * MMU内存属性-cache wbnwa。
 */
#define OS_MMU_STATE_CACHE_WBNWA                               0x100

/**
 * @ingroup SRE_mmu
 * MMU内存属性-cache wtnwa。
 */
#define OS_MMU_STATE_CACHE_WTNWA                               0x200

/**
 * @ingroup SRE_mmu
 * MMU内存属性-shareable。
 */
#define OS_MMU_STATE_SHARE                                     0x400

/**
 * @ingroup SRE_mmu
 * MMU内存属性掩码-ACCESS。
 */
#define OS_MMU_STATEMASK_ACCESS                                (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU内存属性掩码-Normal。
 */
#define OS_MMU_STATEMASK_NORMAL                                (OS_MMU_STATE_CACHE_OFF | OS_MMU_STATE_CACHE_WBWA | OS_MMU_STATE_CACHE_WBNWA | OS_MMU_STATE_CACHE_WTNWA)

/**
 * @ingroup SRE_mmu
 * MMU内存属性掩码-ATTRIBUTES。
 */
#define OS_MMU_STATEMASK_ATTRIBUTES                            (OS_MMU_STATEMASK_NORMAL | OS_MMU_STATE_STRONGLY_ORDERED | OS_MMU_STATE_SHARED_DEVICE | OS_MMU_STATE_DEVICE)

/**
 * @ingroup SRE_mmu
 * MMU内存属性掩码-SHARE。
 */
#define OS_MMU_STATEMASK_SHARE                                 OS_MMU_STATE_SHARE

/**
 * @ingroup SRE_mmu
 * mmu用户配置信息的结构体定义。
 *
 * mmu用户配置信息。
 */
typedef struct tagVirtPhysMem
{
    UINT32 uwVirtualAddr;                                   /**< 虚拟地址 */
    UINT32 uwPhysicalAddr;                                  /**< 物理地址 */
    UINT32 uwLen;                                           /**< 长度     */
    UINT32 uwInitialStateMask;                              /**< 状态掩码 */
    UINT32 uwInitialState;                                  /**< 状态     */
} VIRT_PHYS_MEM_S;

/**
 * @ingroup SRE_mmu
 * MMU模块配置信息的结构体定义。
 *
 * 保存MMU模块的配置项信息。
 */
typedef struct tagMmuModInfo
{
    UINT32 uwMmuInitAddr;                                   /**< MMU初始化结构体数组首地址       */
    UINT32 uwMmuInitNum ;                                   /**< MMU初始化结构体数组元素个数     */
} MMU_MOD_INFO_S;
/**
 * @ingroup  SRE_mmu
 * @brief 内存属性设置。
 *
 * @par 描述:
 * 设置虚拟地址uwVirtAddr，长度uwLen的内存属性为uwState。
 *
 * @attention
 * <ul>
 * <li>该操作仅在Cortex-AX平台下支持。</li>
 * <li>只允许MMU模块初始化完成后调用。</li>
 * <li>不允许设置0号分区内存属性。</li>
 * <li>uwLen为0时不进行内存属性设置。</li>
 * <li>内存属性设置时，从uwVirtAddr开始对section、page逐个进行设置。某一页内存属性设置不成功时，已经设置成功的保持设置属性。</li>
 * </ul>
 *
 * @param  uwVirtAddr  [IN] 类型#UINT32，虚拟地址起始地址。
 * @param  uwLen       [IN] 类型#UINT32，设置内存属性长度。
 * @param  uwStateMask [IN] 类型#UINT32，内存属性掩码，区分平台属性用，当前为无效参数，可忽略。
 * @param  uwState     [IN] 类型#UINT32，内存属性。
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201，传入参数虚拟地址、物理地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210，传入虚拟地址未映射过。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，地址溢出。
 * @retval #OS_ERRNO_MMU_DEOPTIMIZE_FAIL        0x02001211，页表拆分时内存不足。
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217，入参uwState的ATTRIBUTE属性配置不正确。
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218，入参uwState的ACCESS属性配置不正确。
 * @retval #SRE_OK                              0x00000000，内存属性设置成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuStateSet(UINT32 uwVirtAddr, UINT32 uwLen, UINT32 uwStateMask, UINT32 uwState);

/**
 * @ingroup  SRE_mmu
 * @brief 使能MMU。
 *
 * @par 描述:
 * 使能MMU。
 *
 * @attention
 * <ul>
 * <li>该操作仅在Cortex-AX平台下支持。</li>
 * <li>只允许MMU模块初始化完成后调用。</li>
 * <li>请勿在低功耗时使用此接口。</li>
 * </ul>
 *
 * @param 无
 *
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210，虚拟地址未映射。
 * @retval #SRE_OK                              0x00000000，MMU使能成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MmuDisable
 */
extern UINT32 SRE_MmuEnable(VOID);

/**
 * @ingroup  SRE_mmu
 * @brief 除能MMU。
 *
 * @par 描述:
 * 除能MMU。
 *
 * @attention
 * <ul>
 * <li>该操作仅在Cortex-AX平台下支持。</li>
 * <li>只允许MMU模块初始化完成后调用。</li>
 * <li>请勿在低功耗时使用此接口。</li>
 * </ul>
 *
 * @param 无
 *
 * @retval #SRE_OK                              0x00000000，MMU除能成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MmuEnable
 */
extern UINT32 SRE_MmuDisable(VOID);

/**
 * @ingroup  SRE_mmu
 * @brief 页表合并。
 *
 * @par 描述:
 * 合并uwVirtAddr开始，长度为uwLen的内存空间页表。
 *
 * @attention
 * <ul>
 * <li>该操作仅在Cortex-AX平台下支持。</li>
 * <li>只允许MMU模块初始化完成后调用。</li>
 * <li>该接口遍历入参地址空间，对物理地址连续、内存属性一致的内存进行合并。</li>
 * </ul>
 *
 * @param  uwVirtAddr  [IN] 类型#UINT32，合并起始地址。
 * @param  uwLen       [IN] 类型#UINT32，合并长度。
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201，起始地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，地址溢出。
 * @retval #OS_ERRNO_MMU_OPTIMIZE_NO_NEED       0x02001212，长度不足合并为大页表。
 * @retval #SRE_OK                              0x00000000，合并成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuOptimize(UINT32 uwVirtAddr, UINT32 uwLen);


/************************************************HIDSP interface*************************************************/
#elif(OS_HARDWARE_PLATFORM == OS_HIDSP)
/************************* Permission 属性(以下宏只能选择一个) *********************/
/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可读。
 */
#define OS_MMU_STATE_READ                                      0x4

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可写。
 */
#define OS_MMU_STATE_WRITE                                     0x2

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可执行。
 */
#define OS_MMU_STATE_EXE                                       0x1

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-不可读、不可写、不可执行。
 */
#define OS_MMU_STATE_NO_WRITE_READ_EXE                         0x0

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可读可执行。
 */
#define OS_MMU_STATE_READ_EXE                                  (OS_MMU_STATE_READ | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可读可写。
 */
#define OS_MMU_STATE_READ_WRITE                                (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE)

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可写可执行。
 */
#define OS_MMU_STATE_WRITE_EXE                                  (OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU内存permission属性-可读可写执行。
 */
#define OS_MMU_STATE_READ_WRITE_EXE                            (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)


/**************************** Share属性(以下宏只能选择一个) *********************/
/**
 * @ingroup SRE_mmu
 * MMU内存共享属性-可共享。
 */
#define OS_MMU_STATE_SHARED                                    0x1

/**
 * @ingroup SRE_mmu
 * MMU内存共享属性-不可共享。
 */
#define OS_MMU_STATE_NOT_SHARED                                0x0

/*************************** Speculative 属性 (以下宏只能选择一个)***************/
/**
 * @ingroup SRE_mmu
 * MMU内存投机属性-可投机。
 */
#define OS_MMU_STATE_SPEC                                      0x1

/**
 * @ingroup SRE_mmu
 * MMU内存共享属性-不可投机。
 */
#define OS_MMU_STATE_NOT_SPEC                                  0x0


/***************************** Cache   属性 (以下宏只能选择一个)**************/
/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-不可cache不可buffer。
 */
#define OS_MMU_STATE_NONCACHE_NONBUFFER                        0x0

/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-不可cache可buffer。
 */
#define OS_MMU_STATE_NONCACHE_BUFFERABLE                       0x1

/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-DTLB: writeback,no allocate。
 */
#define OS_MMU_STATE_WRITEBACK_NOALLOC                         0x3

/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-DTLB: writeback, writeallocate。
 */
#define OS_MMU_STATE_WRITEBACK_ALLOC                           0x7

/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-DTLB:writethrough。
 */
#define OS_MMU_STATE_WRITETHROUGH                              0x2

/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-ITLB:Cacheable, Read Allocate for write through cache。
 */
#define OS_MMU_STATE_READ_ALLOC_FOR_WRITETHROUGH               0x2

/**
 * @ingroup SRE_mmu
 * MMU内存cache属性-ITLB: cacheable, read allocate。
 */
#define OS_MMU_STATE_READ_ALLOC                                0x3

/**
 * @ingroup SRE_mmu
 * MMU内存属性组装宏(共8bit)。
 */
#define OS_MMU_ATTR(CacheAttr, Speculative, Share, permission) (((CacheAttr) << 5) | ((Speculative) << 4) | ((Share) << 3) | (permission))

/**
 * @ingroup SRE_mmu
 * TLB无效操作时指定的无效方式:页无效、context无效、无效ALL.
 *
 * TLB无效方式。
 */
typedef enum
{
    NON_INV     = 0,              /**< none opreation     */
    PAGE_INV    = 1,              /**< page invalidate    */
    CONTEXT_INV = 2,              /**< context invalidate */
    ALL_INV     = 3,              /**< all invalidate     */
    RESERVED    = 4
}OS_TLB_INV_POLICY;

/**
 * @ingroup SRE_mmu
 * TLB的三种类型:ITLB、DTLB.
 *
 * TLB类型。
 */
typedef enum
{
    ITLB,            /**< ITLB*/
    DTLB             /**< DTLB*/
}OS_TLB_TYPE;

/**
 * @ingroup SRE_mmu
 * MMU的四种内存属性类型.
 *
 * TLB类型。
 */
typedef enum
{
    OS_MMU_PERMISSION,       /**<Permission: W(可写), R(可读), E(可执行)属性类型*/
    OS_MMU_SHARED,           /**<Shared: 内存共享属性类型*/
    OS_MMU_SPEC,             /**<Destructive: 内存投机属性类型*/
    OS_MMU_CACHE,            /**<Cache: 内存cache属性类型*/
    OS_MMU_BUTT              /**<无效MMU内存属性类型*/
}OS_MMU_ATTR_TYPE;

/**
 * @ingroup SRE_mmu
 * MMU模块配置信息的结构体定义。
 *
 * 保存MMU模块的配置项信息。
 */
typedef struct tagMmuModInfo
{
    UINT32 uwMmuPhyToVirAddr;                                   /**< MMU初始化结构体数组首地址   */
    UINT32 uwMmuPhyToVirSize ;                                  /**< MMU初始化结构体数组大小     */
} MMU_MOD_INFO_S;



/**
 * @ingroup  SRE_mmu
 * @brief 按照固定大小映射虚拟地址到物理地址。
 *
 * @par 描述:
 * 根据传入参数pVStart、pPStart、uwLen进行虚拟、物理地址映射，并按照uwAttr设置内存属性。
 *
 * @attention
 * <ul>
 * <li>uwLen为0时不进行地址映射，直接返回成功。</li>
 * <li>SD6183平台地址映射时，优先映射成大页。</li>
 * <li>SD6183平台MMU去映射及映射的内存区域cache一致性由用户保证。</li>
 * <li>SD6183平台MMU配置的虚实地址，如果是DDR空间，需要按照1M对齐，否则代码段8K对齐，数据段4K对齐</li>
 * </ul>
 *
 * @param  pVStart       [IN] 类型#MMU_VA_T，映射虚拟地址起始地址。
 * @param  pPStart       [IN] 类型#MMU_PA_T，映射物理地址起始地址。
 * @param  uwLen         [IN] 类型#UINT32，映射的内存大小。
 * @param  uwAttr        [IN] 类型#UINT32，内存属性，SD6183平台uwAttr有效bit位为(bit7-0)，bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201，传入参数虚拟地址、物理地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203，未申请到一级页表内存。
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204，传入虚拟地址已经映射过。
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205，未申请到二级页表内存。
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206，未申请到页表映射信息内存。
 * @retval #OS_ERRNO_MEM_FREE_SH_DAMAGED        0x02000311，内存释放时要释放的内存块的头被破坏，或已释放。
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217，入参uwState的ATTRIBUTE属性配置不正确。
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218，入参uwState的ACCESS属性配置不正确。
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL   0x0200123f，新的实虚映射节点申请内存失败。
 * @retval #OS_ERRNO_MMU_PAGEMAP_STATE_INVALID  0x02001224，设置的内存属性非法。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，映射内存地址设置溢出。
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED  0x0200124e，MMU消息发送时，申请消息节点失败。
 * @retval #OS_ERRNO_MMU_NOT_CORRECT_ALIGNED    0x0200124d，使用非优化接口映射MMU时，对齐方式不正确。
 * @retval #SRE_OK                              0x00000000，虚拟、物理地址映射成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern  UINT32 SRE_MmuAssignNoOpt(MMU_VA_T pVStart, MMU_PA_T pPStart,
                                  UINT32 uwLen, UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief 得到页表对齐后的虚地址空间。
 *
 * @par 描述:
 * 根据传入参数pVStart、uwLen输出根据页表对齐后的虚地址和长度。
 *
 * @attention
 * <ul>
 * <li>uwLen为0时容错处理，返回用户传入的起始地址ppVStartOut和大小puwLenOut。</li>
 * </ul>
 *
 * @param  pVStart       [IN] 类型#MMU_VA_T，去映射虚拟地址起始地址。
 * @param  uwLen         [IN] 类型#UINT32，去映射的内存大小。
 * @param  ppVStartOut   [OUT] 类型#MMU_VA_T*，根据页表对齐后去映射虚拟地址起始地址。
 * @param  puwLenOut     [OUT] 类型#UINT32*，根据页表对齐后去映射的内存大小。
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201，传入参数虚拟地址、物理地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，(去)映射内存地址设置溢出。
 * @retval #SRE_OK                              0x00000000，虚拟、物理地址映射成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuUnMap
 */
extern UINT32 SRE_MmuPageSpaceGet(MMU_VA_T pVStart, UINT32 uwLen, MMU_VA_T * ppVStartOut, UINT32 * puwLenOut);

/**
 * @ingroup  SRE_mmu
 * @brief 去映射已经配置好的虚拟地址。
 *
 * @par 描述:
 * 根据传入参数pVStart、uwLen进行MMU配置页表的去映射。
 *
 * @attention
 * <ul>
 * <li>uwLen为0时不进行页表清除。做容错操作。</li>
 * <li>pVStart和uwLen建议用SRE_MmuAlignSpace对齐后的地址。</li>
 * <li>MMU去映射及映射的内存区域cache一致性由用户保证。</li>
 * <li>该操作仅在SD6183平台下支持。</li>
 * </ul>
 *
 * @param  pVStart       [IN] 类型#MMU_VA_T，映射虚拟地址起始地址。
 * @param  uwLen         [IN] 类型#UINT32，映射的内存大小。
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201，传入参数虚拟地址、物理地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，(去)映射内存地址设置溢出。
 * @retval #OS_ERRNO_MMU_PAGE_NOT_ALIGNED       0x0200123b，MMU页表去映射时，传入的参数未按照配置的页表大小对齐。
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED  0x0200124e，MMU消息发送时，申请消息节点失败。
 * @retval #SRE_OK                              0x00000000，虚拟、物理地址映射成功。

 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuAlignSpace
 */
extern UINT32 SRE_MmuUnAssign(MMU_VA_T pVStart, UINT32 uwLen);

/**
 * @ingroup  SRE_mmu
 * @brief 无效TLB。
 *
 * @par 描述:
 * 无效 TLB。
 *
 * @attention
 * <ul>
 * <li>因为硬件特性，TLB无效的时候，会把已经加锁的TLB无效掉且解锁。需要用户重新上锁。</li>
 * </ul>
 *
 * @param  enTlbType    [IN] 类型#OS_TLB_TYPE，ITLB或者DTLB
 * @param  enInvPolicy  [IN] 类型#OS_TLB_INV_POLICY，page inv,context inv,all inv
 * @param  pVirAddr     [IN] 类型#MMU_VA_T，虚拟地址,针对page inv方式有效
 * @param  uwContextID  [IN] 类型#UINT32，context ID，针对page inv和context inv有效
 *
 * @retval #OS_ERRNO_MMU_TLB_INV_POLICY_INVALID             0x0200121f，TLB 无效策略非法。
 * @retval #OS_ERRNO_MMU_TLB_INV_CONTEXT_ID_INVALID         0x0200123a，无效TLB输入的ContextID非法。
 * @retval #OS_ERRNO_MMU_TLB_TYPE_INVALID                   0x0200121e，TLB类型错误。
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL               0x0200123f，拆分产生新的实虚映射节点申请内存失败。
 * @retval #SRE_OK                                          0x00000000，成功。
 * @retval SRE_OK 成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuL2TlbOrdSet
 */
extern UINT32 SRE_MmuTlbInv(OS_TLB_TYPE enTlbType , OS_TLB_INV_POLICY enInvPolicy,
                           MMU_VA_T pVirAddr, UINT32 uwContextID);

/**
 * @ingroup  SRE_mmu

 * @brief 配置L2 TLB查找的顺序。
 *
 * @par 描述:
 * 配置L2 TLB查找的顺序。
 *
 * @attention
 * <ul>
 * <li>主核要在从核启动之前为自己设置搜索顺序，否则可能有异常。</li>
 * <li>主核在从核启动前为从核设置搜索顺序，否则可能产生异常。</li>
 * <li>uwOrdValue表示8个页表的查找顺序，每4bit表示一种类型，且4bit中仅低3bit有效。</li>
 * <li>8个类型在顺序中都要有且仅一次。</li>
 * <li>页表类型0:4K 1:8K 2:16K 3:64K 4:256K 5:1M 6:4M 7:16M</li>
 * <li>若uwOrdValue=0x76543210，表示按4K、8K、16K、64K、256K、1M、4M、16M顺序查找。</li>
 * <li>硬件默认的搜索顺序是0x76543210。</li>
 * </ul>
 *
 * @param  uwCoreID             [IN] 类型#UINT32，核号范围[0,33]。
 * @param  uwOrdValue           [IN] 类型#UINT32，L2页表的查找顺序。
 *
 * @retval #OS_ERRNO_MMU_L2TLB_ORDER_ERR    0x02001236，L2 TLB查找顺序错误。
 * @retval #OS_ERRNO_MMU_COREID_ERR         0x02001237，核号错误。
 * @retval #SRE_OK                          0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbInv
 */
extern UINT32 SRE_MmuL2TlbOrdSet(UINT32 uwCoreID ,UINT32 uwOrdValue);


/**
 * @ingroup  SRE_mmu

 * @brief 查询MMU页表属性值。
 *
 * @par 描述:
 * 查询当前内存的MMU页表属性值。
 *
 * @attention
 * <ul>
 * <li>保证查询的地址已经做过MMU映射。</li>
 * </ul>
 *
 * @param  pVirAddr     [IN] 类型#MMU_VA_T，虚拟地址。
 * @param  puwMemAttr   [OUT]类型#UINT32 *，实际输出的MMU页表属性值。
 *
 * @retval #OS_ERRNO_MMU_ATTR_OUTPUT_POINT_NULL 0x0200123c，获取MMU内存属性时，入参指针参数为空。
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210，虚拟地址未映射。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbInv
 */
extern UINT32 SRE_MmuMemAttrGet(MMU_VA_T pVirAddr, UINT32 *puwMemAttr);

/**
 * @ingroup  SRE_mmu

 * @brief 配置指定段的MMU页表属性
 *
 * @par 描述:
 * 配置指定段的MMU页表属性。
 *
 * @attention
 * <ul>
 * <li>保证查询的地址已经做过MMU映射。</li>
 * <li>寄存器空间[0x10000000,0x1fffffff]和[0x90000000,0x9fffffff]的页表属性不允许修改。</li>
 * </ul>
 *
 * @param  pVirAddr     [IN] 类型#MMU_VA_T，虚拟地址。
 * @param  uwSize       [IN] 类型#UINT32，虚拟地址长度。
 * @param  uwMemAttr    [IN] 类型#UINT32，配置的内存属性值。
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED                 0x02001201，物理地址或长度非page对齐。
 * @retval #OS_ERRNO_MMU_PAGEMAP_STATE_INVALID            0x02001224，设置的内存属性非法。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW                    0x02001209，内存地址设置溢出。
 * @retval #OS_ERRNO_MMU_PAGE_NOT_ALIGNED                 0x0200123b，MMU页表去映射(配置属性)时，传入的参数未按照配置的页表大小对齐。
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED                  0x02001210，虚拟地址未映射。
 * @retval #OS_ERRNO_MMU_SETATTR_PROTECT_REGION_COVERRED  0x02001250，MMU修改属性时内存段包含了受保护的寄存器空间。
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED            0x0200124e，MMU消息发送时，申请消息节点失败。
 * @retval #OS_ERRNO_MMU_REG_REGION_PROTECT               0x0200124f，MMU修改属性时不允许修改寄存器空间属性。
 * @retval #SRE_OK                                        0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_MmuTlbInv
 */
extern UINT32 SRE_MmuMemAttrSet(MMU_VA_T pVirAddr, UINT32 uwSize, UINT32 uwMemAttr);

/**
 * @ingroup  SRE_mmu
 * @brief Tlb预取
 *
 * @par 描述:
 * 通过虚拟地址把MMU页表软件预取到L2 TLB,如果特定页表项已经在L2 TLB中，本次预取不起作用。
 *
 * @attention
 * <ul>
 * <li>对于重复预取，第二次相当于无效操作。</li>
 * </ul>
 *
 * @param  pVirAddr           [IN] 类型#MMU_VA_T，虚拟地址
 *
 * @retval #SRE_OK  成功
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbLock
 */
OS_SEC_ALW_INLINE INLINE  UINT32 SRE_MmuTlbPreload(MMU_VA_T pVirAddr)
{
    __asm__ __volatile__("mmupf %0 " :: "r"((UINT32)pVirAddr));
    return SRE_OK;
}

/**
 * @ingroup  SRE_mmu
 * @brief Tlb预取并加锁
 *
 * @par 描述:
 * 通过虚拟地址把MMU页表软件预取到L2 TLB并加锁,如果特定页表项已经在L2 TLB中且加锁，本次预取加锁不起作用。
 *
 * @attention
 * <ul>
 * <li>对于重复上锁，第二次相当于无效操作。</li>
 * </ul>
 *
 * @param  pVirAddr           [IN] 类型#MMU_VA_T，虚拟地址
 *
 * @retval #SRE_OK  成功
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbPreload
 */
OS_SEC_ALW_INLINE INLINE UINT32 SRE_MmuTlbLock(MMU_VA_T pVirAddr)
{
    __asm__ __volatile__("mmupflck %0 "  :: "r"((UINT32)pVirAddr));
    return SRE_OK;
}

/**
 * @ingroup  SRE_mmu
 * @brief Tlb解锁
 *
 * @par 描述:
 * 通过虚拟地址把把锁在L2 Tlb中的页表项解锁，如果对应的页表项不在L2 Tlb中，本次解锁不起作用。
 *
 * @attention
 * <ul>
 * <li>对于重复解锁，第二次相当于无效操作。</li>
 * </ul>
 *
 * @param  pVirAddr           [IN] 类型#MMU_VA_T，虚拟地址
 *
 * @retval #SRE_OK  成功
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbPreload
 */
OS_SEC_ALW_INLINE INLINE UINT32 SRE_MmuTlbUnlock(MMU_VA_T pVirAddr)
{
    __asm__ __volatile__("mmuulck %0 "  :: "r"((UINT32)pVirAddr));
    return SRE_OK;
}

#if (OS_OPTION_BM_SRE == NO)
/**
 * @ingroup  SRE_mng
 * @brief 映射虚拟地址到物理地址。
 *
 * @par 描述:
 * 根据传入参数pVStart、pPStart、uwLen进行虚拟、物理地址映射，并按照uwAttr设置内存属性。
 * 该接口仅支持主控核给本核或者是给指定从核进行MMU映射
 * @attention
 * <ul>
 * <li>uwLen为0时不进行地址映射，直接返回成功。</li>
 * <li>SD6183平台地址映射时，优先映射成大页。</li>
 * <li>SD6183平台MMU去映射及映射的内存区域cache一致性由用户保证。</li>
 * <li>SD6183平台MMU配置的虚实地址，长度都必须按照4K对齐，如果是可执行的代码段，必须按照8K对齐</li>
 * <li>仅支持主控核调用</li>
 * </ul>
 *
 * @param  uwInstID       [IN] 类型#UINT32，实例ID。
 * @param  uwCoreID       [IN] 类型#UINT32，硬线程ID。
 * @param  pVStart        [IN] 类型#MMU_VA_T，映射虚拟地址起始地址。
 * @param  pPStart        [IN] 类型#MMU_PA_T，映射物理地址起始地址。
 * @param  uwLen          [IN] 类型#UINT32，映射的内存大小。
 * @param  uwAttr         [IN] 类型#UINT32，内存属性，SD6183平台uwAttr有效bit位为(bit7-0)，bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_INST_ID_TOO_MAX        0x02001246，实例ID超过最大值。
 * @retval #OS_ERRNO_MMU_CORE_ID_TOO_MAX        0x02001247，硬件线程ID超过最大值
 * @retval #OS_ERRNO_MMU_INST_NOT_READY         0x02001248，实例未准备好
 * @retval #OS_ERRNO_MMU_COREID_NOT_EXIST       0x02001249，coreID错误
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203，未申请到一级页表内存。
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204，传入虚拟地址已经映射过。
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205，未申请到二级页表内存。
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206，未申请到页表映射信息内存。
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209，地址溢出。
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217，入参uwState的ATTRIBUTE属性配置不正确。
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218，入参uwState的ACCESS属性配置不正确。
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL   0x0200123f，新的实虚映射节点申请内存失败。
 * @retval #OS_ERRNO_MMU_MSG_UNINIT             0x02001244，配置指定核的MMU时，未完成MMU消息队列初始化。
 * @retval #OS_ERRNO_MMU_MSG_SEND_FAIL          0x02001245，配置指定核的MMU时，给指定核发送消息失败。
 * @retval #OS_ERRNO_MMU_INST_NOT_READY         0x02001248，实例未准备好。
 * @retval #SRE_OK                              0x00000000，虚拟、物理地址映射成功。
 * @par 依赖:
 * <ul><li>sre_mmu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see NA
 */
extern UINT32 SRE_MmuMcAssign(UINT32 uwInstID,UINT32 uwCoreID, MMU_VA_T pVStart, MMU_PA_T pPStart, UINT32 uwLen, UINT32 uwAttr);
#endif

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MMU_H */



