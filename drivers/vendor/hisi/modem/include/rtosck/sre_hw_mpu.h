/**
 * @file sre_hw_mpu.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：SD6182 mpu模块外部头文件。 \n
 */

/**
*@defgroup  SRE_hw_mpu MPU
*@ingroup SRE_inspect
*/


#ifndef _SRE_HW_MPU_H
#define _SRE_HW_MPU_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if (OS_CPU_TYPE != OS_SD6183)
/**
 * @ingroup SRE_hw_mpu
 * 表示所有的MPU单元。
 */
#define OS_MPU_ID_ALL                    0xFFFF

/**
 * @ingroup SRE_hw_mpu
 * 表示未分配地址的MPU段编号。
 */
#define OS_MPU_UNSIGNED_RANGE_IDX        0xFFFF

/**
 * @ingroup SRE_hw_mpu
 * 表示使能，用于给指定的MPU单元配置段保护属性时，指定该段保护是否使能。
 */
#define OS_MPU_RANGE_ENABLE              1

/**
 * @ingroup SRE_hw_mpu
 * 表示去使能，用于给指定的MPU单元配置段保护属性时，指定该段保护是否使能。
 */
#define OS_MPU_RANGE_DISABLE             0

/**
 * @ingroup SRE_hw_mpu
 * 表示可读可写，用于设置指定Group针对指定MPU段的读写保护属性。
 */
#define OS_MPU_NO_PROTECTED              0

/**
 * @ingroup SRE_hw_mpu
 * 表示可读不可写，用于设置指定Group针对指定MPU段的读写保护属性。
 */
#define OS_MPU_WRITE_PROTECTED           1

/**
 * @ingroup SRE_hw_mpu
 * 表示不可读可写，用于设置指定Group针对指定MPU段的读写保护属性。
 */
#define OS_MPU_READ_PROTECTED            2

/**
 * @ingroup SRE_hw_mpu
 * 表示不可读不可写，用于设置指定Group针对指定MPU段的读写保护属性。
 */
#define OS_MPU_ALL_PROTECTED             3

/**
 * @ingroup SRE_hw_mpu
 * 表示第一次违反的保护操作是违反了读id的保护。
 */
#define OS_MPU_OFFEND_READ_ID_PROTECTED  1

/**
 * @ingroup SRE_hw_mpu
 * 表示第一次违反的保护操作是违反了写id的保护。
 */
#define OS_MPU_OFFEND_WRITE_ID_PROTECTED 2

#if (OS_CPU_TYPE == OS_SD6182)

/**
 * @ingroup SRE_hw_mpu
 * SD6182 MPU编号枚举值
 */
typedef enum tagMpuNum
{
    OS_MPU_DSP_CLUST0_CORE0_LL2  = 0,    /**< DSP0 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_CORE1_LL2  = 1,    /**< DSP1 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_CORE2_LL2  = 2,    /**< DSP2 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_CORE3_LL2  = 3,    /**< DSP3 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_CORE4_LL2  = 4,    /**< DSP4 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST1_CORE0_LL2  = 5,    /**< DSP5 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST1_CORE1_LL2  = 6,    /**< DSP6 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST1_CORE2_LL2  = 7,    /**< DSP7 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST1_CORE3_LL2  = 8,    /**< DSP8 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST1_CORE4_LL2  = 9,    /**< DSP9 核的Local L2 MPU编号               */
    OS_MPU_HACCC_CLUST_CORE0_LL2 = 10,   /**< HACCC0 核的Local L2 MPU编号             */
    OS_MPU_HACCC_CLUST_CORE1_LL2 = 11,   /**< HACCC1 核的Local L2 MPU编号             */
    OS_MPU_CPU_CLUST_CORE0_LL2   = 12,   /**< CPU0 核的Local L2 MPU编号               */
    OS_MPU_CPU_CLUST_CORE1_LL2   = 13,   /**< CPU1 核的Local L2 MPU编号               */
    OS_MPU_CPU_CLUST_CORE2_LL2   = 14,   /**< CPU2 核的Local L2 MPU编号               */
    OS_MPU_CPU_CLUST_CORE3_LL2   = 15,   /**< CPU3 核的Local L2 MPU编号               */
    OS_MPU_CPU_CLUST_CORE4_LL2   = 16,   /**< CPU4 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_L2M0       = 17,   /**< DSP Cluster0 的第0块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M1       = 18,   /**< DSP Cluster0 的第1块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M2       = 19,   /**< DSP Cluster0 的第2块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M3       = 20,   /**< DSP Cluster0 的第3块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M4       = 21,   /**< DSP Cluster0 的第4块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST1_L2M0       = 22,   /**< DSP Cluster1 的第0块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST1_L2M1       = 23,   /**< DSP Cluster1 的第1块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST1_L2M2       = 24,   /**< DSP Cluster1 的第2块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST1_L2M3       = 25,   /**< DSP Cluster1 的第3块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST1_L2M4       = 26,   /**< DSP Cluster1 的第4块Shared L2 MPU编号   */
    OS_MPU_HACCC_CLUST_L2M0      = 27,   /**< HACC Cluster 的第0块Shared L2 MPU编号   */
    OS_MPU_HACCC_CLUST_L2M1      = 28,   /**< HACC Cluster 的第1块Shared L2 MPU编号   */
    OS_MPU_HACCC_CLUST_L2M2      = 29,   /**< HACC Cluster 的第2块Shared L2 MPU编号   */
    OS_MPU_HACCC_CLUST_L2M3      = 30,   /**< HACC Cluster 的第3块Shared L2 MPU编号   */
    OS_MPU_CPU_CLUST_L2M0        = 31,   /**< CPU Cluster 的第0块Shared L2 MPU编号    */
    OS_MPU_CPU_CLUST_L2M1        = 32,   /**< CPU Cluster 的第1块Shared L2 MPU编号    */
    OS_MPU_CPU_CLUST_L2M2        = 33,   /**< CPU Cluster 的第2块Shared L2 MPU编号    */
    OS_MPU_L3_CMI0               = 34,   /**< L3M0 MPU编号                            */
    OS_MPU_L3_CMI1               = 35,   /**< L3M1 MPU编号                            */
    OS_MPU_DDR                   = 36,   /**< DDR MPU编号                             */
    OS_MPU_HACCC_CLUST_LSIP      = 37,   /**< HACC Cluster Lsip MPU编号               */
    OS_MPU_MAIN_CLUST_LSIP       = 38,   /**< Main Cluster Lsip MPU编号               */
    OS_MPU_SRIO                  = 39    /**< sRIO Register MPU编号                   */
}OS_MPU_ID_E;

#elif (OS_CPU_TYPE == OS_SD6157)

/**
 * @ingroup SRE_hw_mpu
 * SD6157 MPU编号枚举值
 */
typedef enum tagMpuNum
{
    OS_MPU_DSP_CLUST0_CORE0_LL2  = 0,    /**< DSP0 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_CORE1_LL2  = 1,    /**< DSP1 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_CORE2_LL2  = 2,    /**< DSP2 核的Local L2 MPU编号               */
    OS_MPU_CPU_CLUST_CORE0_LL2   = 3,    /**< CPU0 核的Local L2 MPU编号               */
    OS_MPU_DSP_CLUST0_L2M0       = 4,    /**< DSP Cluster0 的第0块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M1       = 5,    /**< DSP Cluster0 的第1块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M2       = 6,    /**< DSP Cluster0 的第2块Shared L2 MPU编号   */
    OS_MPU_DSP_CLUST0_L2M3       = 7,    /**< DSP Cluster0 的第3块Shared L2 MPU编号   */
    OS_MPU_CPU_CLUST_L2M0        = 8,    /**< CPU Cluster 的第0块Shared L2 MPU编号    */
    OS_MPU_DDR                   = 9,    /**< DDR MPU编号                             */
    OS_MPU_MAIN_CLUST_LSIP       = 10    /**< Main Cluster Lsip MPU编号               */
}OS_MPU_ID_E;

#endif

/**
 * @ingroup SRE_hw_mpu
 * MPU段配置信息结构体定义。
 *
 * 配置指定的MPU属性时指定的参数信息。
 */
typedef struct tagMpuCfgInfo
{
    UINT16 usRangeId;     /**< 段ID，不同的MPU能配置的段数目不一样，取值范围也不一样(0 ~ N-1，N为最大段数目)。OS_MPU_UNSIGNED_RANGE_IDX代表未分配的地址段*/
    UINT16 usEnable;      /**< 是否使能：OS_MPU_RANGE_ENABLE：使能MPU保护，OS_MPU_RANGE_DISABLE：禁止MPU保护 */
    UINT32 uwStartAddr;   /**< 段的起始地址，不同MPU有不同的对齐要求 */
    UINT32 uwEndAddr;     /**< 段的结束地址，不同MPU有不同的对齐要求  */
    UINT32 uwWriteProt;   /**< 写保护，每个bit代表一个group，1--不允许对应的group写这段地址，0--允许对应的group写这段地址 */
    UINT32 uwReadProt;    /**< 读保护，每个bit代表一个group，1--不允许对应的group读这段地址，0--允许对应的group读这段地址 */
}MPU_SLV_CFG_INFO_S;

/**
 * @ingroup SRE_hw_mpu
 * MPU异常时，记录的异常信息。
 *
 * MPU异常时，记录的异常信息结构体。
 */
typedef struct tagMpuExcInfo
{
     UINT32  uwFaultAddr;   /**< 异常时访问的地址                                 */
     UINT16  usTranId;      /**< 传输ID，当前无效                                 */
     UINT8   ucGroupId;     /**< 发起访问的master对应的Group ID                   */
     UINT8   ucFaultType;   /**< 异常的类型: 01-违反读访问保护，02-违反写访问保护 */
} MPU_EXC_INFO_S;


/**
 * @ingroup SRE_hw_mpu
 * 表示异常信息。
 */
typedef VOID (*MPU_EXC_HOOK_FUNC) (UINT16 usMpuId, MPU_EXC_INFO_S *pstMpuExcInfo);

/*
 * MPU模块错误码定义。
 */

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：输入的Group Id非法。
 *
 * 值: 0x02002101
 *
 * 解决方案: 请确保传入正确的Group Id，范围为[0,31]。
 */
#define OS_ERRNO_MPU_GROUP_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x01)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：输入的MPU Id非法。
 *
 * 值: 0x02002102
 *
 * 解决方案: 请确保传入正确的MPU Id，范围为SD6182:[0,39],SD6157:[0,10]。
 */
#define OS_ERRNO_MPU_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x02)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：用户为指定的MPU单元配置保护属性时，传入的段个数非法
 *
 * 值: 0x02002103
 *
 * 解决方案: 请确保传入的段个数合法(不为0且不超过指定MPU单元硬件支持的最大可划分的MPU段数(包括未划分的段)，其中DDR为33，sRIO为2，其他为5)。
 */
#define OS_ERRNO_MPU_RANGE_NUM_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x03)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：用户输入的段Id非法
 *
 * 值: 0x02002104
 *
 * 解决方案: 请确保传入的段个数合法(为#OS_MPU_ID_ALL或不超过指定MPU单元支持的最大编号(其中DDR为31，sRIO为0，其他为3))。
 */
#define OS_ERRNO_MPU_RANGE_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x04)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：用户为指定的MPU单元配置保护属性时，传入的段属性信息缓冲区首地址为NULL
 *
 * 值: 0x02002105
 *
 * 解决方案: 请确保传入有效的缓冲区地址
 */
#define OS_ERRNO_MPU_RANGE_BUFF_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x05)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：用户输入的保存MPU属性的地址为NULL
 *
 * 值: 0x02002106
 *
 * 解决方案: 请确保传入的保存MPU属性的地址非NULL。
 */
#define OS_ERRNO_MPU_QUERY_PTR_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x06)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：用户给指定的MPU单元配置段保护属性时，指定的段使能状态非法
 *
 * 值: 0x02002107
 *
 * 解决方案: 请确保传入的段使能状态为#OS_MPU_RANGE_ENABLE或#OS_MPU_RANGE_DISABLE。
 */
#define OS_ERRNO_MPU_RANGE_ENA_STATUS_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x07)

/**
 * @ingroup SRE_hw_mpu
 * MPU错误码：注册MPU异常钩子函数时，已经注册。
 *
 * 值: 0x02002108
 *
 * 解决方案: 请确保注册MPU异常钩子函数时，异常钩子函数未被注册，当前仅支持注册一个MPU异常钩子函数。
 */
#define OS_ERRNO_MPU_EXC_INFO_HOOK_IS_FULL                  SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x08)

/**
 * @ingroup  SRE_hw_mpu
 * @brief 给指定的MPU单元配置保护属性。
 *
 * @par 描述:
 * 给usMpuId指定的MPU单元配置保护属性，MPU段信息缓冲区地址为pastRangeInfo，配置的段个数为usRangeNum。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证对应的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>该操作在配置各个MPU段属性的同时会打开该MPU单元的全局MPU使能开关，即若配置段使能，则进行该操作后该MPU段保护就会生效。</li>
 * <li>由于#SRE_MpuDisable，#SRE_MpuRestore以及该接口都会操作MPU使能开关，所以不建议在#SRE_MpuDisable和#SRE_MpuRestore之间调用该接口，否则可能会造成使能状态混乱。</li>
 * <li>MPU保护功能不区分Global/Local和Cacheable/Uncacheable访问，即保护的是实际的物理空间，对各种不同的逻辑地址访问均可做到保护。</li>
 * <li>硬件会根据各个MPU单元的保护粒度自动忽略用户配置的段起始地址和段结束地址的相应低位(保护粒度为4K时，忽略低12bit，保护粒度为1M时，忽略低20bit)，然后将用户输入的起始地址
       相应低位赋0后组成保护的起始地址，将用户输入的结束地址相应低位赋1后组成保护的结束地址。</li>
 * <li>对于#OS_MPU_HACCC_CLUST_LSIP和#OS_MPU_MAIN_CLUST_LSIP这两个MPU单元，硬件设计的目的只用于保护HACCC寄存器，若用户配置成其他地址段，可能会引发硬件逻辑错误。</li>
 * <li>当传入的usRangeId为#OS_MPU_UNSIGNED_RANGE_IDX时，表示对该MPU的未划分地址段(即该MPU所有保护区间中除了已划分段外的其他所有地址空间)进行段属性配置，并且该MPU作用范围由用户保证。</li>
 * </ul>
 * @param  usMpuId       [IN] 类型为#UINT16，MPU ID号，取值范围为SD6182:[0,39],SD6157:[0,10]。
 * @param  usRangeNum    [IN] 类型为#UINT16，MPU段信息缓冲区单元个数。对于DDR和SRIO MPU，取值范围分别为(0,33]和(0,2],对于其它MPU，取值范围为(0,5]。
 * @param  pastRangeInfo [IN] 类型为#MPU_SLV_CFG_INFO_S，MPU段信息缓冲区首地址。
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID                 0x02002102，输入的MPU Id非法。
 * @retval #OS_ERRNO_MPU_RANGE_NUM_INVALID          0x02002103，用户为指定的MPU单元配置保护属性时，传入的段个数非法。
 * @retval #OS_ERRNO_MPU_RANGE_ID_INVALID           0x02002104，用户输入的段Id非法。
 * @retval #OS_ERRNO_MPU_RANGE_BUFF_NULL            0x02002105，用户为指定的MPU单元配置保护属性时，传入的段属性信息缓冲区首地址为NULL。
 * @retval #OS_ERRNO_MPU_RANGE_ENA_STATUS_INVALID   0x02002107, 用户给指定的MPU单元配置段保护属性时，指定的段使能状态非法。
 * @retval #SRE_OK                                  0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable | SRE_MpuRestore
 */
extern UINT32 SRE_MpuCfg(UINT16 usMpuId,UINT16 usRangeNum, const MPU_SLV_CFG_INFO_S *pastRangeInfo);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 设置指定的Group针对指定的MPU段的读写属性。
 *
 * @par 描述:
 * 设置指定Group针对由usMpuId和usRangeId指定的MPU段的读写属性。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证对应的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>若输入的usRangeId为OS_MPU_UNSIGNED_RANGE_IDX，表示设置的未分配地址的MPU段读写属性。</li>
 * <li>若指定的MPU段未被调用SRE_MpuCfg接口设置过，则设置的读写属性不生效。</li>
 * </ul>
 * @param  usGroupId     [IN] 类型为#UINT16，Group ID号，范围[0,31]。
 * @param  usMpuId       [IN] 类型为#UINT16，MPU ID号，范围SD6182:[0,39],SD6157:[0,10]。
 * @param  usRangeId     [IN] 类型为#UINT16，MPU段的ID号，范围请参照对应MPU单元的硬件规格。
 * @param  usWrProt      [IN] 类型为#UINT16，欲设置的读写属性，bit0代表写保护，值1--不允许写，值0--允许写；bit1代表读保护，值1--不允许读，值0--允许读。
 *
 * @retval #OS_ERRNO_MPU_GROUP_ID_INVALID      0x02002101，输入的Group Id非法。
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102，输入的MPU Id非法。
 * @retval #OS_ERRNO_MPU_RANGE_ID_INVALID      0x02002104，用户输入的段Id非法。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable | SRE_MpuRestore
 */
extern UINT32 SRE_MpuMasterCfg(UINT16 usGroupId, UINT16 usMpuId, UINT16 usRangeId, UINT16 usWrProt);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 设置指定的Group针对指定的MPU段的读写属性。
 *
 * @par 描述:
 * 查询指定Group针对由usMpuId和usRangeId指定的MPU段的读写属性，结果保存在pusWrProt。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证对应的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>若输入的usRangeId为OS_MPU_RANGE_ID_ALL，表示查询的未分配地址的MPU段读写属性。</li>
 * </ul>
 * @param  usGroupId     [IN] 类型为#UINT16，Group ID号，范围[0,31]。
 * @param  usMpuId       [IN] 类型为#UINT16，MPU ID号，范围SD6182:[0,39],SD6157:[0,10]。
 * @param  usRangeId     [IN] 类型为#UINT16，MPU段的ID号，范围请参照对应MPU单元的硬件规格。
 * @param  pusWrProt     [OUT] 类型为#UINT16 *，查询出来的读写属性，bit0代表写保护，值1--不允许写，值0--允许写；bit1代表读保护，值1--不允许读，值0--允许读。
 *
 * @retval #OS_ERRNO_MPU_GROUP_ID_INVALID      0x02002101，输入的Group Id非法。
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102，输入的MPU Id非法。
 * @retval #OS_ERRNO_MPU_RANGE_ID_INVALID      0x02002104，用户输入的段Id非法。
 * @retval #OS_ERRNO_MPU_QUERY_PTR_NULL        0x02002106，输入的保存查询结果的地址为NULL。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable | SRE_MpuRestore
 */
extern UINT32 SRE_MpuMasterQuery(UINT16 usGroupId, UINT16 usMpuId, UINT16 usRangeId, UINT16 *pusWrProt);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 禁止指定MPU单元的保护功能。
 *
 * @par 描述:
 * 禁止usMpuId指定的MPU单元的保护功能。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证对应的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>若输入的usMpuId为#OS_MPU_ID_ALL，表示禁止所有MPU单元的保护功能。</li>
 * <li>去使能后，恢复使能前，不能进行mpu的配置操作，否则下次去使能不成功。</li>
 * </ul>
 * @param  usMpuId     [IN] 类型为#UINT16，MPU ID号，范围SD6182:[0,39],SD6157:[0,10]或者等于OS_MPU_ID_ALL。
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102，输入的MPU Id非法。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuRestore
 */
extern UINT32 SRE_MpuDisable(UINT16 usMpuId);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 恢复指定MPU单元的保护功能。
 *
 * @par 描述:
 * 恢复usMpuId指定的MPU单元的保护功能。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证对应的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>若输入的usMpuId为#OS_MPU_ID_ALL，表示恢复所有MPU单元的保护功能。</li>
 * </ul>
 * @param  usMpuId     [IN] 类型为#UINT16，MPU ID号，范围SD6182:[0,39],SD6157:[0,10]或者等于OS_MPU_ID_ALL。
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102，输入的MPU Id非法。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable
 */
extern UINT32 SRE_MpuRestore(UINT16 usMpuId);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 查询MPU错误中断。
 *
 * @par 描述:
 * 查询usMpuId指定的MPU错误中断。若存在MPU中断，查询之后，会清除相对应的中断。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证对应的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>若查询的是DDR MPU，并且已经注册MPU异常钩子函数时，若存在多个AXI口的MPU中断时，会多次调用异常钩子函数。</li>
 * <li>若查询的是DDR MPU，当违反MPU保护属性时，返回给用户的异常地址是实际异常地址的低30Bit。</li>
 * <li>若查询的是LL2 MPU，当存在违反MPU保护属性时，返回给用户的异常地址是全局Uncache地址。</li>
 * <li>调用初始化MPU Dfx功能接口后，才能调用此接口，否则会返回相关错误码。</li>
 * </ul>
 * @param  usMpuId     [IN] 类型为#UINT16，MPU ID号，范围SD6182:[0,39],SD6157:[0,10]。
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102，输入的MPU Id非法。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see None
 */
extern UINT32 SRE_MpuIntQuery(UINT16 usMpuId);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 注册MPU异常钩子函数。
 *
 * @par 描述:
 * 注册MPU异常钩子函数。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>输入参数pfnHook为NULL时，表示取消MPU异常钩子函数。</li>
 * <li>当用户使用#SRE_MpuIntQuery查询MPU错误中断信息时，若存在错误中断，则该接口注册的MPU异常钩子函数会被调用。</li>
 * </ul>
 * @param  pfnHook     [IN] 类型为#MPU_EXC_HOOK_FUNC，MPU异常钩子函数。
 *
 * @retval #OS_ERRNO_MPU_EXC_INFO_HOOK_IS_FULL 0x02002108，注册MPU异常钩子函数时，已经注册。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see None
 */
extern UINT32 SRE_MpuExcHookReg(MPU_EXC_HOOK_FUNC pfnHook);

/**
 * @ingroup  SRE_hw_mpu
 * @brief 初始化MPU Dfx功能。
 *
 * @par 描述:
 * 初始化MPU Dfx功能, 使能MPU错误中断。
 *
 * @attention
 * <ul>
 * <li>该操作仅支持SD6182和SD6157平台。</li>
 * <li>该操作不支持ESL平台。</li>
 * <li>用户调用该接口时，需要保证待初始化DFX功能的MPU资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * <li>若输入的usMpuId为#OS_MPU_ID_ALL，表示初始化所有MPU DFX功能。</li>
 * <li>如果多个核调用此接口，核间互斥由用户保证。</li>
 * </ul>
 * @param  usMpuId     [IN] 类型为#UINT16，MPU ID号，范围SD6182:[0,39],SD6157:[0,10]或者等于OS_MPU_ID_ALL。
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102，输入的MPU Id非法。
 * @retval #SRE_OK                             0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw_mpu.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see None
 */
extern UINT32 SRE_MpuDfxInit(UINT16 usMpuId);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* _SRE_HW_MPU_H */

