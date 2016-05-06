/**
* @file SRE_nsm.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：有名空间模块对外头文件。 \n
*/

/**
 * @defgroup SRE_nsm  有名空间
 * @ingroup SRE_kernel
 */

#ifndef _SRE_NSM_H
#define _SRE_NSM_H

#include "sre_base.h"
#include "sre_mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//支持功能宏裁剪,sre_buildef.h文件中支持的功能宏
#if (OS_OPTION_NSM == YES)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：入参非法，传入指针为NULL。
 *
 * 值: 0x02001b01
 *
 * 解决方案：确保指针非空。
 */
#define OS_ERRNO_NSM_PTR_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x01)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入的有名空间大小非法。
 *
 * 值: 0x02001b02
 *
 * 解决方案：有名空间配置大小SD6183需不小于1K字节，SD6157/82需不小于212字节。
 */

#define OS_ERRNO_NSM_SPACE_SIZE_ILLEG                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x02)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入有名空间虚拟空间或物理空间首地址未字节对齐。
 *
 * 值: 0x02001b03
 *
 * 解决方案：有名空间首地址需4K字节对齐(SD6183)或4字节对齐(SD6108/81/57/82)。
 */
#define OS_ERRNO_NSM_ADDR_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x03)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入有名空间大小未字节对齐。
 *
 * 值: 0x02001b04
 *
 * 解决方案：有名空间大小需4K字节对齐(SD6183)或4字节对齐(SD6108/81/57/82)。
 */
#define OS_ERRNO_NSM_SIZE_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x04)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间已满。
 *
 * 值: 0x02001b05
 *
 * 解决方案：添加记录时，确保有名空间有足够的空间存储。
 */
#define OS_ERRNO_NSM_MEM_FULL                               SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x05)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间中记录重命名。
 *
 * 值: 0x02001b06
 *
 * 解决方案：往有名空间中添加记录时，确保记录名唯一。
 */
#define OS_ERRNO_NSM_OBJ_RENAME                             SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x06)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：删除有名记录时，对应记录不存在。
 *
 * 值: 0x02001b07
 *
 * 解决方案：删除有名记录时，请确认相应记录存在。
 */
#define OS_ERRNO_NSM_DEL_NOT_FIND                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x07)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间中对应记录不存在。
 *
 * 值: 0x02001b08
 *
 * 解决方案：确保该空间已有相应记录。
 */
#define OS_ERRNO_NSM_FIND_FAILURE                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x08)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：实例内有名空间ID非法。
 *
 * 值: 0x02001b0a
 *
 * 解决方案：确认该空间ID是否正确。
 */
#define OS_ERRNO_LOCAL_NSM_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0a)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间申请对象失败。
 *
 * 值: 0x02001b0b
 *
 * 解决方案：确认有名空间内存是否足够。
 */
#define OS_ERRNO_NSM_OBJ_ALLOC_FAILED                 SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0b)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：Space ID指定错误。
 *
 * 值: 0x02001b0c
 *
 * 解决方案：Space ID在有名空间创建时取值范围(0,0xffff],在名字对象创建时取值范围[0,0xffff]。
 */
#define OS_ERRNO_NSM_SPACE_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0c)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：对齐方式指定错误。
 *
 * 值: 0x02001b0d
 *
 * 解决方案：参考枚举类型NS_MEM_ALIGN_E，0号名字空间取值范围[NS_ADDR_ALIGN_004, NS_ADDR_ALIGN_128],非0号名字空间取值范围[NS_ADDR_ALIGN_4K, NS_ADDR_ALIGN_16M]。
 */
#define OS_ERRNO_NSM_MEM_ALIGN_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0d)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：0号名字空间名字指定错误。
 *
 * 值: 0x02001b0e
 *
 * 解决方案：确保取值范围在[0 , 0xf0000000)。
 */
#define OS_ERRNO_GLOBLE_NAME_ID_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0e)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间虚拟地址注册接口仅供主核调用。
 *
 * 值: 0x02001b0f
 *
 * 解决方案：必须主核调用。
 */
#define OS_ERRNO_NSM_MCPU_ALLOW                             SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0f)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：入参有名空间虚拟地址段个数为0。
 *
 * 值: 0x02001b10
 *
 * 解决方案：配置虚拟地址段个数不能为0。
 */
#define OS_ERRNO_NSM_VIR_MEM_NUM_ZERO                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x10)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间虚拟地址或物理地址段长度为0。
 *
 * 值: 0x02001b11
 *
 * 解决方案：配置虚拟地址或物理地址段长度不能为0。
 */
#define OS_ERRNO_NSM_MEM_SEG_SIZE_ZERO                      SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x11)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入有名空间地址或长度未字节对齐。
 *
 * 值: 0x02001b12
 *
 * 解决方案：确保传入有名空间地址或长度至少4K字节对齐。
 */
#define OS_ERRNO_NSM_ADDR_LEN_NOT_ALIGN                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x12)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入有名空间地址空间翻转。
 *
 * 值: 0x02001b13
 *
 * 解决方案：确保传入有名空间地址空间不翻转。
 */
#define OS_ERRNO_NSM_ADDR_REGION_WRONG                      SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x13)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入有名空间虚拟地址空间重叠。
 *
 * 值: 0x02001b14
 *
 * 解决方案：确保传入有名空间虚拟地址空间不重叠。
 */
#define OS_ERRNO_NSM_ADDR_REGION_OVERLAP                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x14)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间申请内存失败。
 *
 * 值: 0x02001b15
 *
 * 解决方案：确认0号有名空间内存是否足够。
 */
#define OS_ERRNO_NSM_MEM_ALLOC_FAILED                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x15)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：有名空间类型参数非法。
 *
 * 值: 0x02001b16
 *
 * 解决方案：0表示实例间有名空间，1表示实例内有名空间，其余值非法。
 */
#define OS_ERRNO_NSM_TYPE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x16)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：重复创建有名空间参数不匹配。
 *
 * 值: 0x02001b17
 *
 * 解决方案：确保重复创建有名空间时入参一致。
 */
#define OS_ERRNO_NSM_SPACE_CREATE_REPEAT                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x17)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：虚拟地址未注册。
 *
 * 值: 0x02001b18
 *
 * 解决方案：确保创建有名空间前,先注册虚拟地址。
 */
#define OS_ERRNO_NSM_VIR_MEM_NOT_REG                        SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x18)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：找不到可分配的虚地址空间。
 *
 * 值: 0x02001b19
 *
 * 解决方案：确保虚地址空间够用。
 */
#define OS_ERRNO_NSM_VIR_MEM_NOT_ENOUGH                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x19)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：创建名字对象时大小为0
 *
 * 值: 0x02001b1a
 *
 * 解决方案：确保创建名字对象时大小不为0。
 */
#define OS_ERRNO_NSM_OBJ_SIZE_ZERO                          SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1a)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：创建名字对象时MMU属性设置不正确
 *
 * 值: 0x02001b1b
 *
 * 解决方案：确保创建名字对象时MMU属性设置正确。
 */
#define OS_ERRNO_NSM_OBJ_ATTR_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1b)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：名字空间未创建
 *
 * 值: 0x02001b1c
 *
 * 解决方案：确保已经创建名字空间。
 */
#define OS_ERRNO_NSM_SPACE_NOT_CREATE                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1c)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：非实例内的核创建或操作实例内名字空间
 *
 * 值: 0x02001b1d
 *
 * 解决方案：确保本实例的核创建或操作实例内名字空间。
 */
#define OS_ERRNO_NSM_SPACE_NOT_MATCH                        SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1d)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：重复释放虚地址
 *
 * 值: 0x02001b1e
 *
 * 解决方案：确保不重复释放虚地址。
 */
#define OS_ERRNO_NSM_VIR_MEM_FREE_REPEAT                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1e)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：创建同一个名字对象时，大小或对齐方式不相同
 *
 * 值: 0x02001b1f
 *
 * 解决方案：创建同一个名字对象时，确保大小和对齐方式相同。
 */
#define OS_ERRNO_NSM_OBJ_SIZE_OR_ALIGN_NOT_MATCH            SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1f)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：释放虚拟地址时虚拟地址未找到
 *
 * 值: 0x02001b20
 *
 * 解决方案：确保释放虚拟地址存在。
 */
#define OS_ERRNO_NSM_VIR_MEM_FREE_NOT_FIND                  SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x20)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：同一个核创建同一个名字对象时，属性不相同
 *
 * 值: 0x02001b21
 *
 * 解决方案：确保同一个核创建同一个名字对象时，属性相同。
 */
#define OS_ERRNO_NSM_OBJ_ATTR_NOT_MATCH                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x21)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：名字空间创建时传入的名字空间虚拟地址映射的物理地址为0
 *
 * 值: 0x02001b22
 *
 * 解决方案：确保传入的名字空间虚拟地址映射的物理地址不为0。
 */
#define OS_ERRNO_NSM_CREATE_PHY_ADDR_ZERO                   SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x22)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：重复注册虚拟地址
 *
 * 值: 0x02001b23
 *
 * 解决方案：确保不要重复注册虚拟地址。
 */
#define OS_ERRNO_NSM_VIR_ADDR_CFG_REPEAT                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x23)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：从实例未创建的情况下，从核创建名字对象
 *
 * 值: 0x02001b24
 *
 * 解决方案:创建从实例后再给从核配置MMU。
 */
#define OS_ERRNO_NSM_SLAVE_INST_UNCREATE                    SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x24)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：配置项OS_NSM_SPACE_PADDR配置的物理地址不正确
 *
 * 值: 0x02001b25
 *
 * 解决方案:确保配置项OS_NSM_SPACE_PADDR配置的物理地址与虚拟地址是对应的。
 */
#define OS_ERRNO_NSM_PADDR_CFG_WRONG                        SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x25)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：名字空间创建时传入的虚拟地址未映射
 *
 * 值: 0x02001b26
 *
 * 解决方案:确保名字空间创建时传入的虚拟地址已经映射过。
 */
#define OS_ERRNO_NSM_CREATE_VA2PA_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x26)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：名字空间创建时传入的虚地址映射的物理地址为PL2的GLOBAL地址
 *
 * 值: 0x02001b27
 *
 * 解决方案:确保名字空间创建时传入的虚地址映射的物理地址不为PL2的GLOBAL地址。
 */
#define OS_ERRNO_NSM_CREATE_PA_ILLEGAL                      SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x27)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：一个物理核使用另外一个物理核的有名空间PL2的Local内存
 *
 * 值: 0x02001b28
 *
 * 解决方案:确保有名空间PL2的Local内存只能一个物理核两个硬线程使用，其他核使用报错。
 */
#define OS_ERRNO_NSM_OBJ_CREATE_PL2_OWNER_ERROR             SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x28)

/**
 * @ingroup SRE_nsm
 * 有名空间错误码：传入有名空间虚拟地址映射的物理地址为DDR空间，地址或长度未1M对齐
 *
 * 值: 0x02001b29
 *
 * 解决方案：确保传入有名空间虚拟地址映射的物理地址为DDR空间时，地址和长度需要1M对齐。
 */
#define OS_ERRNO_NSM_ADDR_OR_LEN_NOT_DDR_ALIGN              SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x29)

/**
 * @ingroup SRE_nsm
 *
 * 有名空间注册结构体定义。
 */
#if(OS_HIDSP == OS_HARDWARE_PLATFORM)
typedef struct tagNsmModInfo
{
    UINT32 uwVA;                 /**< 有名空间虚拟起始地址                          */
    UINT32 uwPA;                 /**< 有名空间物理起始地址                          */
    UINT32 uwSize;               /**< 有名空间内存空间大小                          */
}NSM_MOD_INFO_S;
#else
typedef struct tagNsmModInfo
{
    VOID  *pStart;               /**< 有名空间起始地址                              */
    UINT32 uwSize;               /**< 有名空间内存空间大小                          */
}NSM_MOD_INFO_S;
#endif
/**
 * @ingroup SRE_nsm
 * 有名空间虚拟地址注册构体定义。
 */
typedef struct tagNsVirMemCfg
{
    UINT32 uwAddr;               /**< 有名空间虚拟内存地址，需4K字节对齐            */
    UINT32 uwLen;                /**< 有名空间虚拟内存大小，需4K字节对齐            */
}SRE_NS_VIR_MEM_CFG;

/**
 * @ingroup SRE_nsm
 * 有名空间创建结构体定义。
 */
typedef struct tagNameSpacePara
{
    UINT32 uwNsType;             /**< 0表示实例间NS，1表示实例内NS                        */
    UINT32 uwRes;                /**< 保留，填写为0                                       */
    VOID  *pVirAddr;             /**< 名字空间虚拟地址，至少4K对齐                        */
    UINT32 uwNsSize;             /**< 名字空间大小，至少4K对齐                            */
}NAME_SPACE_PARA;

/**
 * @ingroup SRE_nsm
 * 有名空间对象创建对齐方式枚举定义。
 */
typedef enum
{
    NS_ADDR_ALIGN_004  = 2,      /**< 4字节对齐    */
    NS_ADDR_ALIGN_008  = 3,      /**< 8字节对齐    */
    NS_ADDR_ALIGN_016  = 4,      /**< 16字节对齐   */
    NS_ADDR_ALIGN_032  = 5,      /**< 32字节对齐   */
    NS_ADDR_ALIGN_064  = 6,      /**< 64字节对齐   */
    NS_ADDR_ALIGN_128  = 7,      /**< 128字节对齐  */
    NS_ADDR_ALIGN_4K   = 8,      /**< 4K字节对齐   */
    NS_ADDR_ALIGN_8K   = 9,      /**< 8K字节对齐   */
    NS_ADDR_ALIGN_16K  = 10,     /**< 16K字节对齐  */
    NS_ADDR_ALIGN_64K  = 11,     /**< 64K字节对齐  */
    NS_ADDR_ALIGN_256K = 12,     /**< 256K字节对齐 */
    NS_ADDR_ALIGN_512K = 13,     /**< 512K字节对齐 */
    NS_ADDR_ALIGN_1M   = 14,     /**< 1M字节对齐   */
    NS_ADDR_ALIGN_4M   = 15,     /**< 4M字节对齐   */
    NS_ADDR_ALIGN_16M  = 16,     /**< 256M字节对齐 */
}NS_MEM_ALIGN_E;

#if(OS_HIDSP == OS_HARDWARE_PLATFORM)

/**************************** Cache属性(以下宏只能选择一个) *********************/
/**
 * @ingroup SRE_nsm
 * 名字对象MMU内存cache属性-non-cache。
 */
#define OS_NS_OBJ_STATE_NONCACHE                                  0x1

/**
 * @ingroup SRE_nsm
 * 名字对象MMU内存cache属性-cache。
 */
#define OS_NS_OBJ_STATE_CACHE                                     0x3

/**************************** Share属性(以下宏只能选择一个) *********************/
/**
 * @ingroup SRE_nsm
 * 名字对象MMU内存共享属性-non-share。
 */
#define OS_NS_OBJ_STATE_NONSHARED                                 0x0

/**
 * @ingroup SRE_nsm
 * 名字对象MMU内存共享属性-share。
 */
#define OS_NS_OBJ_STATE_SHARED                                    0x1

/**
 * @ingroup SRE_nsm
 * 名字对象MMU内存属性组装宏，只允许设置三种组合OS_NS_OBJ_STATE_NONCACHE&OS_NS_OBJ_STATE_NONSHARED; OS_NS_OBJ_STATE_NONCACHE&OS_NS_OBJ_STATE_SHARED; OS_NS_OBJ_STATE_CACHE&OS_NS_OBJ_STATE_NONSHARED。
 */
#define OS_NS_OBJ_MMU_ATTR(CacheAttr, Share) OS_MMU_ATTR(CacheAttr, OS_MMU_STATE_SPEC, Share, OS_MMU_STATE_READ_WRITE)

/**
 * @ingroup  SRE_nsm
 * @brief  注册有名空间虚拟地址信息。
 *
 * @par 描述:
 * 通过传入有名空间虚拟地址段个数uwNum，虚拟地址起始地址和长度pstVirMemCfg，注册虚拟地址信息。
 *
 * @attention
 * <ul>
 * <li>仅SD6183平台，支持该功能。</li>
 * <li>仅允许主核调用一次。</li>
 * </ul>
 *
 * @param  uwNum         [IN]  类型#UINT32  ，虚拟地址段个数，取值范围为(0, 0xffffffff]。
 * @param  pstVirMemCfg  [IN]  类型#SRE_NS_VIR_MEM_CFG *  ，有名空间虚拟地址信息，不能重叠。
 *
 * @retval #OS_ERRNO_NSM_MCPU_ALLOW                 0x02001b0f，有名空间虚拟地址注册接口仅供主核调用。
 * @retval #OS_ERRNO_NSM_VIR_MEM_NUM_ZERO           0x02001b10，入参有名空间虚拟地址段个数为0。
 * @retval #OS_ERRNO_NSM_PTR_NULL                   0x02001b01，入参非法，传入指针为NULL。
 * @retval #OS_ERRNO_NSM_MEM_SEG_SIZE_ZERO          0x02001b11，有名空间虚拟地址或物理地址段长度为0。
 * @retval #OS_ERRNO_NSM_ADDR_LEN_NOT_ALIGN         0x02001b12，传入有名空间地址或长度未字节对齐。
 * @retval #OS_ERRNO_NSM_ADDR_REGION_WRONG          0x02001b13，传入有名空间地址空间翻转。
 * @retval #OS_ERRNO_NSM_ADDR_REGION_OVERLAP        0x02001b14，传入有名空间虚拟地址空间重叠。
 * @retval #OS_ERRNO_NSM_MEM_ALLOC_FAILED           0x02001b15，有名空间申请内存失败。
 * @retval #OS_ERRNO_NSM_VIR_ADDR_CFG_REPEAT        0x02001b23，重复注册虚拟地址。
 * @retval #SRE_OK                                  0x00000000，有名空间虚拟地址信息注册成功。
 * @par 依赖:
 * <ul><li>sre_nsm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_NSVirMemCfg(UINT32 uwNum, SRE_NS_VIR_MEM_CFG *pstVirMemCfg);

/**
 * @ingroup  SRE_nsm
 * @brief  创建有名空间。
 *
 * @par 描述:
 * 通过传入有名空间创建参数pstPara，有名空间uwSpaceId，创建有名空间。
 *
 * @attention
 * <ul>
 * <li>仅SD6183平台，支持该功能。</li>
 * <li>只需要一个核创建一次，创建完成后本实例的其他核都可以直接从这里申请。</li>
 * <li>不允许创建0号名字空间。</li>
 * <li>不支持PL2的Global地址。</li>
 * </ul>
 *
 * @param  pstPara       [IN]  类型#NAME_SPACE_PARA *  ，有名空间参数信息。
 * @param  uwSpaceId     [IN]  类型#UINT32  ，有名空间ID，取值范围(0,0xffff]。
 *
 * @retval #OS_ERRNO_NSM_PTR_NULL                   0x02001b01，入参非法，传入指针为NULL。
 * @retval #OS_ERRNO_NSM_SPACE_ID_INVALID           0x02001b0c，Space ID指定错误。
 * @retval #OS_ERRNO_NSM_TYPE_INVALID               0x02001b16，有名空间类型参数非法。
 * @retval #OS_ERRNO_NSM_MEM_SEG_SIZE_ZERO          0x02001b11，有名空间虚拟地址或物理地址段长度为0。
 * @retval #OS_ERRNO_NSM_ADDR_LEN_NOT_ALIGN         0x02001b12，传入有名空间地址或长度未字节对齐。
 * @retval #OS_ERRNO_NSM_ADDR_REGION_WRONG          0x02001b13，传入有名空间地址空间翻转。
 * @retval #OS_ERRNO_NSM_FIND_FAILURE               0x02001b08，有名空间中对应记录不存在。
 * @retval #OS_ERRNO_NSM_SPACE_CREATE_REPEAT        0x02001b17，重复创建有名空间参数不匹配。
 * @retval #OS_ERRNO_NSM_VIR_MEM_NOT_REG            0x02001b18，虚拟地址未注册。
 * @retval #OS_ERRNO_NSM_MEM_ALLOC_FAILED           0x02001b15，有名空间申请内存失败。
 * @retval #OS_ERRNO_NSM_VIR_MEM_NOT_ENOUGH         0x02001b19，找不到可分配的虚地址空间。
 * @retval #OS_ERRNO_NSM_CREATE_PHY_ADDR_ZERO       0x02001b22，名字空间创建时传入的名字空间虚拟地址映射的物理地址为0。
 * @retval #OS_ERRNO_NSM_CREATE_VA2PA_ERROR         0x02001b26，名字空间创建时传入的虚拟地址未映射。
 * @retval #OS_ERRNO_NSM_CREATE_PA_ILLEGAL          0x02001b27，名字空间创建时传入的虚地址映射的物理地址为PL2的GLOBAL地址。
 * @retval #OS_ERRNO_NSM_ADDR_OR_LEN_NOT_DDR_ALIGN  0x02001b29，传入有名空间虚拟地址映射的物理地址为DDR空间，地址或长度未1M对齐。
 * @retval #SRE_OK                                  0x00000000，有名空间创建成功。
 * @par 依赖:
 * <ul><li>sre_nsm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_NSCreate(NAME_SPACE_PARA *pstPara, UINT32 uwSpaceId);

/**
 * @ingroup  SRE_nsm
 * @brief 创建名字对象。
 *
 * @par 描述:
 * 通过传入空间号uwSpaceID，对象名uwNameId，对象大小，对象内存的对齐方式，MMU属性，返回申请到的内存地址。
 *
 * @attention
 * <ul>
 * <li>仅SD6183平台，支持该功能。</li>
 * <li>0号名字空间，uwNameId取值范围为[0,0xf0000000)，enAlign取值范围[NS_ADDR_ALIGN_004, NS_ADDR_ALIGN_128]。</li>
 * <li>非0号名字空间，enAlign取值范围[NS_ADDR_ALIGN_4K, NS_ADDR_ALIGN_16M]。</li>
 * <li>名字对象属性设置不能设置cache&share，否则报错。</li>
 * <li>从0号名字空间申请对象，uwAttr入参无效。</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  类型#UINT32  ，有名空间ID，取值范围[0,0xffff]。
 * @param  uwNameId      [IN]  类型#UINT32  ，有名共享对象名。
 * @param  uwSize        [IN]  类型#UINT32  ，有名对象大小。
 * @param  enAlign       [IN]  类型#NS_MEM_ALIGN_E ，对齐方式。
 * @param  uwAttr        [IN]  类型#UINT32  ，名字对象MMU属性，有效bit位为(bit7-0)，属性设置参考OS_NS_OBJ_MMU_ATTR。
 * @param  puwAddr       [OUT] 类型#UINT32 *，返回有名共享对象内存空间地址。
 *
 * @retval #OS_ERRNO_NSM_SPACE_ID_INVALID            0x02001b0c，Space ID指定错误。
 * @retval #OS_ERRNO_NSM_OBJ_SIZE_ZERO               0x02001b1a，创建名字对象时大小为0。
 * @retval #OS_ERRNO_NSM_MEM_ALIGN_INVALID           0x02001b0d，对齐方式指定错误。
 * @retval #OS_ERRNO_NSM_PTR_NULL                    0x02001b01，入参非法，传入指针为NULL。
 * @retval #OS_ERRNO_NSM_OBJ_ATTR_INVALID            0x02001b1b，创建名字对象时MMU属性设置不正确。
 * @retval #OS_ERRNO_NSM_SPACE_NOT_CREATE            0x02001b1c，名字空间未创建。
 * @retval #OS_ERRNO_NSM_SPACE_NOT_MATCH             0x02001b1d，非实例内的核创建或操作实例内名字空间。
 * @retval #OS_ERRNO_NSM_FIND_FAILURE                0x02001b08，有名空间中对应记录不存在。
 * @retval #OS_ERRNO_NSM_OBJ_ALLOC_FAILED            0x02001b0b，有名空间申请对象失败。
 * @retval #OS_ERRNO_GLOBLE_NAME_ID_INVALID          0x02001b0e，0号名字空间名字指定错误。
 * @retval #OS_ERRNO_NSM_MEM_ALLOC_FAILED            0x02001b15，有名空间申请内存失败。
 * @retval #OS_ERRNO_NSM_OBJ_SIZE_OR_ALIGN_NOT_MATCH 0x02001b1f，创建同一个名字对象时，大小或对齐方式不相同。
 * @retval #OS_ERRNO_NSM_OBJ_ATTR_NOT_MATCH          0x02001b21，同一个核创建同一个名字对象时，属性不相同。
 * @retval #OS_ERRNO_NSM_SLAVE_INST_UNCREATE         0x02001b24，从实例未创建的情况下，从核创建名字对象。
 * @retval #OS_ERRNO_NSM_OBJ_CREATE_PL2_OWNER_ERROR  0x02001b28，一个物理核使用另外一个物理核的有名空间PL2的Local内存。
 * @retval #SRE_OK                                   0x00000000，有名对象创建成功。
 * @par 依赖:
 * <ul><li>sre_nsm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_NSObjCreate(UINT32 uwSpaceID, UINT32 uwNameId, UINT32 uwSize, NS_MEM_ALIGN_E enAlign, UINT32 uwAttr, UINT32 *puwAddr);

#else
/**
 * @ingroup  SRE_nsm
 * @brief 查询有名共享记录。
 *
 * @par 描述:
 * 通过传入空间号uwSpaceID，对象名uwNameId，在有名空间中查找对应的记录，并通过ppAddr和puwSize指针返回其地址和大小。
 *
 * @attention
 * <ul>
 * <li>对于SD6108/SD6181/SD6182/SD6157平台，支持该功能。</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  类型#UINT32  ，有名空间号，暂为无效参数，留以后扩展使用。
 * @param  uwNameId      [IN]  类型#UINT32  ，有名共享对象名。
 * @param  ppAddr        [OUT] 类型#VOID ** ，返回有名对象首地址。
 * @param  puwSize       [OUT] 类型#UINT32 *，返回有名共享对象内存空间大小。
 *
 * @retval #OS_ERRNO_NSM_FIND_FAILURE           0x02001b08，有名空间中对应记录不存在。
 * @retval #OS_ERRNO_NSM_PTR_NULL               0x02001b01，入参非法，传入指针为NULL。
 * @retval #SRE_OK                              0x00000000，记录查找成功。
 * @par 依赖:
 * <ul><li>sre_nsm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSReg | SRE_NSUnReg
 */
extern UINT32 SRE_NSFind (UINT32 uwSpaceID,  UINT32 uwNameId, VOID **ppAddr, UINT32 *puwSize);

/**
 * @ingroup  SRE_nsm
 * @brief 添加有名共享记录。
 *
 * @par 描述:
 * 通过传入对象名uwNameId，有名对象首地址pAddr，有名对象大小uwSize，在有名空间uwSpaceID中添加一条记录。
 *
 * @attention
 * <ul>
 * <li>对于SD6108/SD6181/SD6182/SD6157平台，支持该功能。</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  类型#UINT32  ，有名空间号，暂为无效参数，留以后扩展使用。
 * @param  uwNameId      [IN]  类型#UINT32  ，有名共享对象名。
 * @param  pAddr         [IN]  类型#VOID *  ，有名对象首地址。
 * @param  uwSize        [IN]  类型#UINT32  ，有名共享对象内存空间大小。
 *
 * @retval #OS_ERRNO_NSM_MEM_FULL               0x02001b05，有名空间已满。
 * @retval #OS_ERRNO_NSM_PTR_NULL               0x02001b01，入参非法，传入指针为NULL。
 * @retval #OS_ERRNO_NSM_OBJ_RENAME             0x02001b06，有名空间中记录重命名。
 * @retval #SRE_OK                              0x00000000，记录添加成功。
 * @par 依赖:
 * <ul><li>sre_nsm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSUnReg
 */
extern UINT32 SRE_NSReg (UINT32 uwSpaceID, UINT32 uwNameId, VOID *pAddr, UINT32 uwSize);

/**
 * @ingroup  SRE_nsm
 * @brief 删除有名共享记录。
 *
 * @par 描述:
 * 通过传入对象名uwNameId，在有名空间uwSpaceID中删除对应的记录。
 *
 * @attention
 * <ul>
 * <li>对于SD6108/SD6181/SD6182/SD6157平台，支持该功能。</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  类型#UINT32  ，有名空间号，暂为无效参数，留以后扩展使用。
 * @param  uwNameId      [IN]  类型#UINT32  ，有名共享对象名。
 *
 * @retval #OS_ERRNO_NSM_DEL_NOT_FIND           0x02001b07，删除有名记录时，对应记录不存在。
 * @retval #SRE_OK                              0x00000000，记录删除成功。
 * @par 依赖:
 * <ul><li>sre_nsm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSReg
 */

extern UINT32 SRE_NSUnReg (UINT32 uwSpaceID, UINT32 uwNameId);
#endif
#endif // #if (OS_OPTION_NSM == YES)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_NSM_H */



