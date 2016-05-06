/**
 * @file sre_hw.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：硬件相关模块的对外头文件。 \n
 */

 /**@defgroup SRE_hw 硬件支持
   *@ingroup SRE_kernel
 */

#ifndef _SRE_HW_H
#define _SRE_HW_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：配置实例启动参数时传入的参数为NULL
 *
 * 值: 0x02002000
 *
 * 解决方案: 请确保传入的参数不为NULL
 */
#define OS_ERRNO_HW_START_PARAM_CFG_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x00)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：配置实例启动参数时，实例内各个核配置不一致
 *
 * 值: 0x02002001
 *
 * 解决方案: 请确保实例内所有核配置的启动参数一致
 */
#define OS_ERRNO_HW_START_PARAM_INCONSISTENT                    SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x01)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：核启动时，未在#SRE_HardBootInit中调用#SRE_StartParamCfg接口进行启动参数配置
 *
 * 值: 0x02002002
 *
 * 解决方案: 请确保有在#SRE_HardBootInit中调用#SRE_StartParamCfg接口进行启动参数配置
 */
#define OS_ERRNO_HW_START_PARAM_NOT_CFG                         SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x02)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：设备ID错误
 *
 * 值: 0x02002003
 *
 * 解决方案: 设备ID的取值[0 ,2]
 */
#define OS_ERRNO_HW_DEVICE_ID_ERR                               SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x03)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：uwCommVmid参数传入错误
 *
 * 值: 0x02002004
 *
 * 解决方案: COMM VMID的取值范围[0 ,7]
 */
#define OS_ERRNO_HW_VMID_ID_ERR                                 SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x04)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码: Cored ID错误
 *
 * 值: 0x02002005
 *
 * 解决方案: 确保Cored ID不能大于等于芯片支持的最大核数[OS_MAX_CORE_NUM]，同时主核设置从核启动参数或唤醒从核时入参核ID不能是主核ID
 */
#define OS_ERRNO_HW_CORE_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x05)


/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：启动结构指针参数为NULL
 *
 * 值: 0x02002006
 *
 * 解决方案: SD6183平台请确保传入的启动参数结构指针不为NULL
 */
#define OS_ERRNO_HW_SLAVE_CORE_BOOTPARA_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x06)


/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：启动参数中段数目配置为0
 *
 * 值: 0x02002007
 *
 * 解决方案: SD6183平台请确保当采用用户模式配置MMU MAP时，加载的段数不能为0
 */
#define OS_ERRNO_HW_SLAVE_CORE_BOOTSECNUM_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x07)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：唤醒中断优先级非法
 *
 * 值: 0x02002008
 *
 * 解决方案: SD6183平台请确保主核唤醒从核的唤醒中断优先级范围为[1, 7]
 */
#define OS_ERRNO_HW_CORE_WAKE_UP_PRI_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x08)

/**
 * @ingroup SRE_hw
 *  硬件相关信息错误码：启动参数段配置中虚拟地址配置重叠
 *
 * 值: 0x02002009
 *
 * 解决方案: SD6183平台请确保启动参数各段配置中虚拟地址是否配置重叠
 */
#define OS_ERRNO_HW_SEC_AREA_OVERLAY_IN_VIR_ADDR                SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x09)

/**
 * @ingroup SRE_hw
 * 错误码：启动参数中设置的启动向量基地址vecbase不合法。
 *
 * 值: 0x0200200a
 *
 * 解决方案: 检查SD6183平台硬线程启动向量基地址vecbase(配置的虚地址或对应的实地址)，保证4K字节对齐且对应的实地址不能为零。
 */
#define OS_ERRNO_HW_VECBASE_ADDR_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x0a)

/**
 * @ingroup SRE_hw
 * 错误码：启动参数中设置的系统栈地址不合法。
 *
 * 值: 0x0200200b
 *
 * 解决方案: 检查SD6183平台硬线程启动系统栈地址，需要保证16字节对齐且不能为零；同时排查该栈地址经过映射后是否存在溢出为零或不对齐的情况。
 */
#define OS_ERRNO_HW_SYS_STACK_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x0b)

/**
 * @ingroup SRE_hw
 * 错误码：启动参数中设置的堆地址不对齐。
 *
 * 值: 0x0200200c
 *
 * 解决方案: 检查SD6183平台硬线程启动系统堆地址（注意配置为虚地址），保证16字节对齐。
 */
#define OS_ERRNO_HW_HEAP_ADDR_NOT_ALIGNED                       SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x0c)


/**
 * @ingroup SRE_hw
 * 错误码：传入的参数非法，目前只支持BALONG和ISP类型
 *
 * 值: 0x02002012
 *
 * 解决方案: 请保证传入的参数合法。
 */
#define OS_ERRNO_HW_PLATFORM_INFO_PTR_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x12)

/**
 * @ingroup SRE_Hw
 * 硬件相关信息。
 *
 */
typedef struct tagHwModInfo
{
    UINT32 uwGiccCtrlOffset;      /**< 芯片GIC CPU Interface地址偏移，Cortex_AX系列芯片有效 */
} HW_MOD_INFO_S;

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**@ingroup SRE_Hw
 * 启动参数结构体定义
 */

typedef struct tagStartParam
{
    UINT16 usInstID;              /**< 实例ID，保留这个配置项用于扩展             */
    UINT16 usReserved;            /**< 保留 */
    UINT16 usGHwSemStartID;       /**< 本实例管理的Global Hwsem起始物理ID */
    UINT16 usGHwSemNum;           /**< 本实例管理的Global Hwsem个数*/
    UINT16 usCpuLHwSemStartID;    /**< 本实例管理的CPU(SD6183 DSP2) cluster Local Hwsem起始物理ID */
    UINT16 usCpuLHwSemNum;        /**< 本实例管理的CPU(SD6183 DSP2) cluster Local Hwsem个数*/
    UINT16 usHacLHwSemStartID;    /**< 本实例管理的HACCC cluster Local Hwsem起始物理ID */
    UINT16 usHacLHwSemNum;        /**< 本实例管理的HACCC cluster Local Hwsem个数*/
    UINT16 usDsp0LHwSemStartID;   /**< 本实例管理的DSP0 cluster Local Hwsem起始物理ID */
    UINT16 usDsp0LHwSemNum;       /**< 本实例管理的DSP0 cluster Local Hwsem个数*/
    UINT16 usDsp1LHwSemStartID;   /**< 本实例管理的DSP1 cluster Local Hwsem起始物理ID */
    UINT16 usDsp1LHwSemNum;       /**< 本实例管理的DSP1 cluster Local hwsem个数*/
    UINT16 usNorGMsgmBufStart;    /**< 本实例管理的Global MSGM普通消息缓冲起始地址(MSGM资源由用户管理时无效)*/
    UINT16 usNorGMsgmBufLen;      /**< 本实例管理的Global MSGM普通消息缓冲长度(MSGM资源由用户管理时无效)*/
    UINT16 usNorLMsgmBufStart;    /**< 本实例管理的Local MSGM普通消息缓冲起始地址(MSGM资源由用户管理时无效)*/
    UINT16 usNorLMsgmBufLen;      /**< 本实例管理的Local MSGM普通消息缓冲长度(MSGM资源由用户管理时无效)*/
 } START_PARAM_S;
#elif ((OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup SRE_hw
 * 从核启动的映射段定义。
 */
typedef  struct tagSecAttr{
    UINT32 uwSecVA;
    UINT32 uwSecPA;
    UINT32 uwSecSize;
    UINT32 uwSecAttr;
}SEC_ATTR_S;

/**
 * @ingroup SRE_hw
 * 从核启动参数结构体，适用于设置从核启动参数，通过osSlavePreBoot接口入参传入
 */
typedef  struct tagSlaveCoreBootPara
{
    UINT32  uwCoreId;           /**<取值范围0~33*/
    UINT32  uwVmid;             /**<系统模式context ID, 由OS组装context ID： VMID（bit5~7）|THDID（bit4）*/
    UINT32  uwPageTblAddr;      /**<MMU页表入口基地址，保证0x4000(16K)对齐*/
    UINT32  uwPageTblLen;       /**<MMU页表占用的内存长度（一级及二级页表总长度），保证大于等于一级页表长度0x4000（16K）,且保证0x400(1K)对齐。页表大小配置必须保证能完成所有段的映射，建议预留页表长度空间，若页表长度配置为0x4000，则需要保证映射的所有段（包括工具方式映射或OS映射）不需要二级页表空间。
                                  1、二级页表的起始地址为(uwPageTblAddr + 0x4000)，二级页表空间供给OS启动过程中的段映射及用户调用SRE_MmuAssign接口映射使用;
                                  2、启动阶段过程中使用的二级页表空间计算: 从启动参数配置的段(stSecInfo)或工具加载映射的段(目前从mmu_config中获取)中找出映射段起始地址中bit[31,30]不相同的段，且映射段的长度小于1M，这样条件下的映射段数为N, 二级页表占用大小为(N * 1K)Bytes.
                                  3、调用MMU接口SRE_MmuAssign使用的二级页表空间: 根据入参pVStart地址及映射长度uwLen，划出1K空间给二级页表，原理同启动加载映射关系一致。
                                */
    BOOL    bMmuMapFlag;        /**<TRUE:表示OS进行MMU页表映射MAP的建立; False:通过工具进行MMU页表映射MAP的建立*/
    UINT32  uwVecbase;          /**<硬线程启动向量基地址（注意配置为虚地址），指定vecbase，保证4K字节对齐*/
    UINT32  uwSysHeap;          /**<硬线程启动系统堆地址（注意配置为虚地址），保证16字节对齐，需与LSP中配置的堆地址保持一致*/
    UINT32  uwSysStack;         /**<硬线程启动系统栈地址（系统栈的栈底，注意配置为虚地址），保证16字节对齐，且不能为零，需与LSP配置的栈地址保持一致*/
    UINT32  uwSecNum;           /**<配置的映射段个数*/
    SEC_ATTR_S  stSecInfo[0];   /**<该处开始顺序存放映射的段结构参数*/
}SLAVE_CORE_BOOTPARA_S;


/**@ingroup SRE_Hw
 * 启动参数结构体定义
 */
typedef struct tagStartParam
{
    UINT16 usInstID;             /**< 实例ID，保留这个配置项用于扩展     */
    UINT16 usReserved;           /**< 保留 */
    UINT16 usGHwSemStartID;      /**< 本实例管理的Global Hwsem起始物理ID */
    UINT16 usGHwSemNum;          /**< 本实例管理的Global Hwsem个数*/
    UINT16 usDsp0LHwSemStartID;  /**< 本实例管理的DSP cluster0 Local Hwsem起始物理ID */
    UINT16 usDsp0LHwSemNum;      /**< 本实例管理的DSP cluster0 Local Hwsem个数*/
    UINT16 usDsp1LHwSemStartID;  /**< 本实例管理的DSP cluster1 Local Hwsem起始物理ID */
    UINT16 usDsp1LHwSemNum;      /**< 本实例管理的DSP cluster1 Local Hwsem个数*/
    UINT16 usDsp2LHwSemStartID;  /**< 本实例管理的DSP cluster2 Local Hwsem起始物理ID */
    UINT16 usDsp2LHwSemNum;      /**< 本实例管理的DSP cluster2 Local Hwsem个数*/
    UINT16 usHacLHwSemStartID;   /**< 本实例管理的HACCC cluster Local Hwsem起始物理ID */
    UINT16 usHacLHwSemNum;       /**< 本实例管理的HACCC cluster Local Hwsem个数*/
 } START_PARAM_S;

#elif (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_Hw
 * Cortex-AX平台产品类型编号。
 */
typedef enum
{
    PLATFORM_BALONG = 0,      /**< Balong产品 */
    PLATFORM_ISP,             /**< ISP产品    */
    PLATFORM_BUIT
}OS_PLATFORM_TYPE_S;
#endif

#if ((OS_HARDWARE_PLATFORM == OS_HIDSP) || (OS_HARDWARE_PLATFORM == OS_DSP220) \
|| (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup  SRE_hw
 * @brief 配置实例启动参数。
 *
 * @par 描述:
 * 根据pstStartParam的内容配置实例启动参数，OS根据该配置将Hwsem和MSGM队列资源按实例进行分段管理。
 *
 * @attention
 * <ul>
 * <li>只支持SD6182/SD6157/SD6183平台。</li>
 * <li>用户必须在#SRE_HardBootInit中且在DDR代码加载后调用该函数，否则初始化失败。</li>
 * <li>实例间配置的资源分段不能重叠，该合法性由用户保证。</li>
 * <li>OS固定使用0号硬件信号量作为实例间互斥，用户无需通过该API将0号硬件信号量配置给OS。</li>
 * </ul>
 *
 * @param  pstStartParam   [IN] 类型#START_PARAM_S，启动参数。
 *
 * @retval #OS_ERRNO_HW_START_PARAM_CFG_NULL          0x02002000，配置实例启动参数时传入的参数为NULL。
 * @retval #OS_ERRNO_HW_START_PARAM_INCONSISTENT      0x02002001，配置实例启动参数时，实例内各个核配置不一致。
 * @retval #OS_ERRNO_HW_START_PARAM_NOT_CFG           0x02002002，核启动时，未在#SRE_HardBootInit中调用#SRE_StartParamCfg接口进行启动参数配置。
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_START_ID_INVALID   0x02002425，配置实例启动参数时传入的全局硬件信号量起始ID非法。
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_NUM_INVALID        0x02002426，配置实例启动参数时传入的全局硬件信号量个数非法
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_REGION_INVALID     0x02002427，配置实例启动参数时配置的全局硬件信号量区间非法。
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_START_ID_INVALID 0x02002428，配置实例启动参数时传入的局部硬件信号量起始ID过大。
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_NUM_INVALID      0x02002429，配置实例启动参数时传入的局部硬件信号量个数非法。
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_REGION_INVALID   0x0200242a，配置实例启动参数时配置的局部硬件信号量区间非法。
 * @retval #OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN   0x02002b3f，配置实例启动参数时传入的MSGM队列起始地址或长度非4字节对齐。
 * @retval #OS_ERRNO_MSGM_CFG_START_ADDR_INVALID      0x02002b40，配置实例启动参数时传入的MSGM队列起始地址非法。
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID       0x02002b41，配置实例启动参数时传入的MSGM队列长度非法。
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID    0x02002b42，配置实例启动参数时传入的MSGM队列起始地址和长度决定的区间非法。
 * @retval #SRE_OK                                    0x00000000，启动参数配置成功。
 * @par 依赖:
 * <ul><li>sre_hw.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see
 **/
extern UINT32 SRE_StartParamCfg(START_PARAM_S  *pstStartParam);
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup SRE_hw
 * 设备编号
 */
typedef enum _tagOsDevice
{
    OS_DEVICE_HWSEM_ID = 0,/**< 硬件信号量ID*/
    OS_DEVICE_MSGM_ID = 1, /**< MSGM ID     */
    OS_DEVICE_TIMER_ID = 2 /**< 全局定时器ID*/
} OS_DEVICE_TYPE_E;

/**
 * @ingroup SRE_hw
 * @brief Comm VMID配置接口。
 *
 * @par 描述:
 * 设置COMM VMID并使能VMID检查。
 * @attention
 * <ul>
 * <li>适用于SD6183平台。</li>
 * <li>main函数之后，调用硬件信号量的VMID设置，否则可能出现硬件信号量VMID保护不使能的情况。</li>
 * </ul>
 *
 * @param uwDeviceID    [IN] 类型#UINT32，设备ID，取值范围[0,2],含义参考#OS_DEVICE_TYPE_E。
 * @param uwCommVmid    [IN] 类型#UINT32，Comm Vmid值，取值范围[0,7]。
 *
 * @retval #OS_ERRNO_HW_VMID_ID_ERR      0x02002004，uwCommVmid参数传入错误。
 * @retval #OS_ERRNO_HW_DEVICE_ID_ERR    0x02002003，设备ID错误。
 * @retval #SRE_OK                       0x00000000，返回成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_CommVmidSet(UINT32 uwDeviceID, UINT32 uwCommVmid);

typedef enum
{
    OS_SUPER_MODE,
    OS_USER_MODE,
    OS_ERR_MODE
}OS_SYS_MODE;

/**
 * @ingroup SRE_hw
 * @brief VMID切换接口。
 *
 * @par 描述:
 * 重设本核的VMID。
 * @attention
 * <ul>
 * <li>适用于SD6183平台。</li>
 * </ul>
 *
 * @param enMode        [IN] 类型#OS_SYS_MODE，切换VMID的模式，超级模式或者用户模式。
 * @param ucCntxID      [IN] 类型#UINT8，切换的contextID值。
 *
 * @retval #OS_ERRNO_SYS_MODE_INVALID      0x0200000f，传入的模式错误。
 * @retval #SRE_OK                         0x00000000，返回成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see 无
 */
extern  UINT32 SRE_CntxIdSwitch(OS_SYS_MODE enMode, UINT8 ucCntxID);

#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_hw
 * @brief 注册用于区分Cortex-AX平台Balong和ISP产品标志
 *
 * @par 描述:
 * 注册用于区分Cortex-AX平台Balong和ISP产品的标志。
 *
 * @attention
 * <ul>
 * <li>只支持Cortex-AX平台，并且须在SRE_HardBootInit中最先调用。</li>
 * <li>。</li>
 * </ul>
 *
 * @param enPlatFormFlag    [IN] 类型#OS_PLATFORM_TYPE_S，Cortex-AX平台产品类型。
 *
 * @retval #OS_ERRNO_HW_PLATFORM_INFO_PTR_INVALID    0x02002012，enPlatFormFlag参数传入错误。
 * @retval #SRE_OK                                   0x00000000，返回成功。
 *
 * @par 依赖:
 * <ul><li>sre_hw.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see NONE
 **/
extern UINT32 SRE_PlatFormReg(OS_PLATFORM_TYPE_S enPlatFormFlag);

/**
 * @ingroup  SRE_hw
 * @brief ARM的DSB功能
 *
 * @par 描述:
 * ARM的DSB功能，等待内存操作完毕，内存操作未结束之前，CPU不会继续操作内存和寄存器。
 *
 * @attention
 * <ul>
 * <li>只支持Cortex-AX平台。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_hw.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_DMB
 **/
#ifndef _WIN32
#define SRE_DSB() OS_EMBED_ASM("dsb")
#else
#define SRE_DSB()
#endif

/**
 * @ingroup  SRE_hw
 * @brief ARM的DMB功能
 *
 * @par 描述:
 * ARM的DMB功能，等待内存操作完毕，内存操作未结束之前，CPU不会继续操作内存。
 *
 * @attention
 * <ul>
 * <li>只支持Cortex-AX平台。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_hw.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_DSB
 **/
#ifndef _WIN32
#define SRE_DMB() OS_EMBED_ASM("dmb")
#else
#define SRE_DMB()
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */



