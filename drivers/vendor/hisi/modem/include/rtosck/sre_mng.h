/**
 * @file sre_mng.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：SRE MNG的对外头文件。 \n
 */

/** @defgroup SRE_mng SRE MNG
  * @ingroup SRE_kernel
  */

#ifndef _SRE_MNG_H
#define _SRE_MNG_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_mng
 * SRE MNG使用的核掩码结构体
 * SD6183 共34个硬线程，64bit即能满足
 */

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
typedef unsigned long long SRE_COREMASK;
#else
typedef unsigned int SRE_COREMASK;
#endif

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG传入的VMID非法。
 *
 * 值: 0x02002f01
 *
 * 解决方案: VMID的取值范围[0,7]。
 */
#define OS_ERRNO_SREMNG_VMID_VALUE_ERR               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x01)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG创建实例传入的虚实地址memmap入参为空。
 *
 * 值: 0x02002f02
 *
 * 解决方案: 检查实例创建接口传入的memmap并传入正确的结构体指针。
 */
#define OS_ERRNO_SREMNG_MEMMAP_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x02)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG传入的核bitmap入参为空。
 *
 * 值: 0x02002f03
 *
 * 解决方案: 检查SREMNG接口传入的核bitmap并传入正确的结构体指针。
 */
#define OS_ERRNO_SREMNG_CORE_BITMAP_NULL             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x03)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：创建实例时传入的用户存放实例ID的地址为空。
 *
 * 值: 0x02002f04
 *
 * 解决方案: 创建实例时请确保传入的用户存放实例ID的地址不为空。
 */
#define OS_ERRNO_SREMNG_INST_ID_ADDR_NULL            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x04)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG创建实例传入的核bitmap不合法，都为0。
 *
 * 值: 0x02002f05
 *
 * 解决方案: 检查实例创建接口传入的核bitmap并传入正确的参数。
 */
#define OS_ERRNO_SREMNG_CORE_BITMAP_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x05)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG申请内存失败。
 *
 * 值: 0x02002f06
 *
 * 解决方案: 扩大SRE MNG管理的系统使用的内存空间。
 */
#define OS_ERRNO_SREMNG_NO_MEMORY                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x06)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG实例创建个数过多，无可用的实例资源。
 *
 * 值: 0x02002f07
 *
 * 解决方案: 请确保创建的最大实例个数不超过8。
 */
#define OS_ERRNO_SREMNG_INST_ID_EXHAUST             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x07)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG进程组创建指定的进程组类型非法。
 *
 * 值: 0x02002f08
 *
 * 解决方案: 创建进程组的类型只能为PG_TYPE_PROCESS或者PG_TYPE_BMCORE。
 */
#define OS_ERRNO_SREMNG_PG_TYPE_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x08)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG进程组创建指定的基础bin入参结构体为NULL。
 *
 * 值: 0x02002f09
 *
 * 解决方案: 检查创建进程组的基础bin入参指针并传入正确的参数。
 */
#define OS_ERRNO_SREMNG_BIN_PARA_NULL                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x09)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG基础bin加载的elf文件头里段的大小校验错误 。
 *
 * 值: 0x02002f0a
 *
 * 解决方案: 确保传入的基础bin文件正确性。
 */
#define OS_ERRNO_MNG_BIN_ELF_SEC_HEAD_ERROR          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0a)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG传入的实例ID非法。
 *
 * 值: 0x02002f0b
 *
 * 解决方案: 确保传入的实例ID不超过实例支持的最大值。
 */
#define OS_ERRNO_SREMNG_INSTID_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0b)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG传入的实例ID为未创建实例。
 *
 * 值: 0x02002f0c
 *
 * 解决方案: 确保传入的实例ID为已创建的实例。
 */
#define OS_ERRNO_SREMNG_INSTID_UNCREATE              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0c)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG创建进程组传入的核bitmap超过了所属实例的核bitmap。
 *
 * 值: 0x02002f0d
 *
 * 解决方案: 确保进程组的核bitmap为其所属实例的子集。
 */
#define OS_ERRNO_SREMNG_PG_COREBITMAP_OVERINST       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0d)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG创建进程组加载从核段时找不到可用的未映射的连续虚拟地址空间。
 *
 * 值: 0x02002f0e
 *
 * 解决方案: 确保进程组加载时主核的连续未映射空间不小于10M。
 */
#define OS_ERRNO_MNG_BIN_LOAD_NO_VALID_VA            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0e)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载基础bin给的文件长度不正确。
 *
 * 值: 0x02002f0f
 *
 * 解决方案: 确保传入的基础bin二进制文件的长度的正确性。
 */
#define OS_ERRNO_MNG_BIN_LEN_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0f)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载基础bin申请段内存失败。
 *
 * 值: 0x02002f10
 *
 * 解决方案: 调整分配给实例的内存资源。
 */
#define OS_ERRNO_MNG_BIN_MEMALLOC_FAILED             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x10)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG基础bin加载的elf文件头校验错误。
 *
 * 值: 0x02002f11
 *
 * 解决方案: 确保传入的基础bin文件正确性。
 */
#define OS_ERRNO_MNG_BIN_ELF_HEAD_ERROR              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x11)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG基础bin加载的elf文件类型错误。
 *
 * 值: 0x02002f12
 *
 * 解决方案: 确保传入的基础bin文件正确性。
 */
#define OS_ERRNO_MNG_BIN_ELF_FILETYPE_ERROR          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x12)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG基础bin加载的elf的段个数不正确。
 *
 * 值: 0x02002f13
 *
 * 解决方案: 确保传入的基础bin文件正确性。
 */
#define OS_ERRNO_MNG_BIN_ELF_SEC_NUM_ERROR           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x13)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG基础bin管理申请内存失败。
 *
 * 值: 0x02002f14
 *
 * 解决方案: 确保SRE MNG基础bin管理的内存足够。
 */
#define OS_ERRNO_MNG_BIN_MANAGE_NO_MEMORY            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x14)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG基础bin加载参数的基础bin文件信息不正确。
 *
 * 值: 0x02002f15
 *
 * 解决方案: 确保SRE MNG基础bin加载时传入的基础bin文件信息的正确性,二进制buffer首地址需要4字节对齐。
 */
#define OS_ERRNO_SREMNG_BIN_PARA_INVALID             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x15)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态库加载的动态库信息指针为空。
 *
 * 值: 0x02002f16
 *
 * 解决方案: 确保SRE MNG动态库加载时传入的动态库信息指针的正确性。
 */
#define OS_ERRNO_SREMNG_DLIB_PARA_NULL               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x16)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态库加载的动态库信息不正确。
 *
 * 值: 0x02002f17
 *
 * 解决方案: 确保SRE MNG动态库加载时传入的动态库信息指针的正确性,二进制buffer首地址需要4字节对齐。
 */
#define OS_ERRNO_SREMNG_DLIB_PARA_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x17)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态库加载指定的进程组非法。
 *
 * 值: 0x02002f18
 *
 * 解决方案: 确保SRE MNG动态库加载时指定的进程组号的正确性。
 */
#define OS_ERRNO_SREMNG_DLIBLOAD_PG_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x18)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG指定的进程组尚未创建。
 *
 * 值: 0x02002f19
 *
 * 解决方案: 确保给SRE MNG传入的进程组ID为已创建的进程组。
 */
#define OS_ERRNO_SREMNG_PG_UNCREATED                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x19)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG启动的进程组已被启动。
 *
 * 值: 0x02002f19
 *
 * 解决方案: 一个进程组不能被重复启动，可以停止后再启动。
 */
#define OS_ERRNO_SREMNG_PG_ALREADY_STARTED           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1a)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG停止的进程组尚未启动。
 *
 * 值: 0x02002f1b
 *
 * 解决方案: 不能停止不在运行状态的进程组。
 */
#define OS_ERRNO_SREMNG_PG_NOT_START                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1b)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载动态库指定的核bitmap超过了进程组的核bitmap。
 *
 * 值: 0x02002f1c
 *
 * 解决方案: 确认库的加载核范围。
 */
#define OS_ERRNO_SREMNG_DLIB_COREBITMAP_OVERINST     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1c)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载动态库分配段内存失败。
 *
 * 值: 0x02002f1d
 *
 * 解决方案: 调整分配给实例的内存资源。
 */
#define OS_ERRNO_MNG_DLIB_MEMALLOC_FAILED            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1d)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：加载动态库时发现所属的进程组未启动。
 *
 * 值: 0x02002f1e
 *
 * 解决方案: 先启动进程组再加载动态库。
 */
#define OS_ERRNO_SREMNG_DLIBLOAD_PG_NOT_RUNNING      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1e)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG卸载动态库的入参结构体指针为空。
 *
 * 值: 0x02002f1f
 *
 * 解决方案: 确认卸载动态库的入参结构体指针的正确性。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_NULL        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1f)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载的基础bin里未找到OS的vecbase段。
 *
 * 值: 0x02002f20
 *
 * 解决方案: 确认加载的基础bin的正确性。
 */
#define OS_ERRNO_MNG_BIN_NO_VECBASE_SECTION           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x20)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载的基础bin里未找到从核的启动参数段。
 *
 * 值: 0x02002f21
 *
 * 解决方案: 确认从核也定义了OS_SEC_DATA_RESET_VECTOR的数据段。
 */
#define OS_ERRNO_MNG_BIN_NO_CORE_RESET_DATA_SECTION   SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x21)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG启动从核时查找名字空间里的启动参数失败。
 *
 * 值: 0x02002f22
 *
 * 解决方案: 启动从核时确保名字空间已初始化。
 */
#define OS_ERRNO_MNG_START_PARA_FIND_FAILED           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x22)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG创建实例指定的实例ID为0。
 *
 * 值: 0x02002f23
 *
 * 解决方案: SRE MNG创建实例指定的实例ID范围[1, 7]。
 */
#define OS_ERRNO_SREMNG_INST_ID_CONFLICTED            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x23)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 核号没有对应的进程组
 *
 * 值: 0x02002f24
 *
 * 解决方案: 核号错误，或进程组未创建。
 */
#define OS_ERRNO_SREMNG_PG_UNEXIST                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x24)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 给主核指定的核掩码错误
 *
 * 值: 0x02002f25
 *
 * 解决方案: 确定主核的核ID再进行SRE MNG的操作。
 */
#define OS_ERRNO_SREMNG_MASTER_CORE_BITMAP_ERR        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x25)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 申请有名空间失败
 *
 * 值: 0x02002f26
 *
 * 解决方案: 扩大有名空间。
 */
#define OS_ERRNO_MNG_NSM_MEM_ALLOC_FAILED             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x26)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG加载操作，等待从核结果超时
 *
 * 值: 0x02002f27
 *
 * 解决方案: 检查从核加载处理的结果。
 */
#define OS_ERRNO_MNG_LOAD_WAIT_SLAVE_CORE_OVERTIME         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x27)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态库加载的elf文件头校验错误。
 *
 * 值: 0x02002f28
 *
 * 解决方案: 确保传入的动态库文件正确性。
 */
#define OS_ERRNO_MNG_LIB_ELF_HEAD_ERROR               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x28)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：0号实例不允许删除。
 *
 * 值: 0x02002f29
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SREMNG_MCPU_INSTID_DELETE_FORBIDDEN  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x29)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：0号实例的核bitmap传入错误。
 *
 * 值: 0x02002f2a
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SREMNG_MASTER_COREMASK_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2a)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG对主实例创建进程组。
 *
 * 值: 0x02002f2b
 *
 * 解决方案: 确认创建进程组传入的实例号的正确性。
 */
#define OS_ERRNO_SREMNG_MCPU_PG_CREATE_ERR            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2b)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG卸载操作，等待从核结果超时
 *
 * 值: 0x02002f2c
 *
 * 解决方案: 检查从核卸载处理的结果。
 */
#define OS_ERRNO_MNG_UNLOAD_WAIT_SLAVE_CORE_OVERTIME  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2c)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态库卸载的动态库信息不正确。
 *
 * 值: 0x02002f2d
 *
 * 解决方案: 确保SRE MNG动态库卸载时传入的动态库信息，卸载库名字指针不为空和指定的卸载核掩码指针不为空。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_INVALID      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2d)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG卸载操作，传入的实例ID非法。
 *
 * 值: 0x02002f2e
 *
 * 解决方案: 卸载操作，确保传入的实例ID不超过实例支持的最大值。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_INSTID_INVALID    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2e)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载操作的实例还未Ready。
 *
 * 值: 0x02002f2f
 *
 * 解决方案: 请确保当前卸载操作对应的实例创建完成且实例资源已配置完成。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_INST_NOT_READY    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2f)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态库卸载时指定的进程组非法。
 *
 * 值: 0x02002f30
 *
 * 解决方案: 确保SRE MNG动态库卸载时指定的进程组号的正确性。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_INVALID        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x30)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态库时发现所属的进程组未启动。
 *
 * 值: 0x02002f31
 *
 * 解决方案: 先启动进程组并完成加载动态库后，才能进行卸载动作。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_NOT_RUNNING    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x31)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态库时未找到指定的库名
 *
 * 值: 0x02002f32
 *
 * 解决方案: 先启动进程组并完成该动态库的加载动作后，才能进行该动态库的卸载动作。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_NAME_NOT_FIND     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x32)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态库时未找到内部记录的管理单元序号UnitNO
 *
 * 值: 0x02002f33
 *
 * 解决方案: 若正确进行库加载后，内部一定会生成对应的管理单元序号，只有在内存被踩时，才可能返回该错误码。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_LOCAL_ID_NOT_FIND SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x33)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：实例资源配置时指定的MMU页表空间非法
 *
 * 值: 0x02002f34
 *
 * 解决方案: MMU页表首地址不能为NULL，首地址必须4K对齐，MMU页表空间大于4K。
 */
#define OS_ERRNO_SREMNG_INST_RES_CFG_MMU_TBL_ERR      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x34)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态库时传入的核bitmap不合法，都为0。
 *
 * 值: 0x02002f35
 *
 * 解决方案: 检查实例创建接口传入的核bitmap,确认其传入正确的参数。
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_CORE_BITMAP_INVALID  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x35)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态库指定的核bitmap超过了进程组的核bitmap。
 *
 * 值: 0x02002f36
 *
 * 解决方案: 确认库的卸载核范围。
 */
 #define OS_ERRNO_SREMNG_DLIB_UNLOAD_COREBITMAP_OVERINST SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x36)

 /**
 * @ingroup SRE_mng
 * SRE MNG错误码：加载动态库时，为计算内部LOCAL ID号申请临时缓存时，报内存不足。
 *
 * 值: 0x02002f37
 *
 * 解决方案: 扩大用于LOCAL ID申请的内存大小。
 */
 #define OS_ERRNO_SREMNG_DLIB_LOAD_ALLOC_NO_MEMORY       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x37)

  /**
  * @ingroup SRE_mng
  * SRE MNG错误码：主核给从核做内存配置时指定的物理层级非法。
  *
  * 值: 0x02002f38
  *
  * 解决方案: 检查内存配置接口传入的各个物理层级。
  */
 #define OS_ERRNO_SREMNG_MEMCFG_PHY_LEVEL_INVALID         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x38)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG ELF文件的buf没有4字节对齐。
 *
 * 值: 0x02002f80
 *
 * 解决方案: 用户保证buf 4字节对齐。
 */
#define OS_ERRNO_MNG_ELF_BUF_NOT_ALIGN                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x80)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 全实例共享空间不足
 *
 * 值: 0x02002f81
 *
 * 解决方案: 增加全实例共享的空间
 */
#define OS_ERRNO_MNG_CHIP_MEM_NOT_ENOUGH              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x81)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 芯片内共享段在pl2或sl2
 *
 * 值: 0x02002f82
 *
 * 解决方案: 芯片内共享段不能放pl2和sl2
 */
#define OS_ERRNO_MNG_CHIP_SH_PHY_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x82)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 实例内共享段不能在pl2
 *
 * 值: 0x02002f83
 *
 * 解决方案: 实例共享段在pl2不能达到共享，需要更换其他内存
 */
#define OS_ERRNO_MNG_INST_SH_PL2_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x83)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 实例内共享段不能在sl2
 *
 * 值: 0x02002f84
 *
 * 解决方案: 实例共享段在sl2不能达到共享，需要更换其他内存
 */
#define OS_ERRNO_MNG_INST_SH_SL2_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x84)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG bss段属性不对
 *
 * 值: 0x02002f85
 *
 * 解决方案:ELF文件受破坏，建议更新版本文件
 */
#define OS_ERRNO_MNG_ELF_BSS_ATTRI_ERR                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x85)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 段类型不对
 *
 * 值: 0x02002f86
 *
 * 解决方案:ELF文件受破坏，建议更新版本文件
 */
#define OS_ERRNO_MNG_ELF_SEC_TYPE_ERR                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x86)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 芯片内共享内存释放失败
 *
 * 值: 0x02002f87
 *
 * 解决方案:共享内存被破坏，建议重启芯片
 */
#define OS_ERRNO_MNG_CHIP_MEM_FREE_ERR                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x87)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 找不到合适大小的物理内存
 *
 * 值: 0x02002f88
 *
 * 解决方案:物理内存不够，建议配置对应层级的物理内存
 */
#define OS_ERRNO_MNG_PHY_MEM_ERR                      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x88)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 实例的corebit MAP全零
 *
 * 值: 0x02002f89
 *
 * 解决方案:实例的corebit MAP不对，建议排除代码。
 */
#define OS_ERRNO_MNG_INST_CORE_MAP_ZERO               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x89)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG  Va申请失败
 *
 * 值: 0x02002f8a
 *
 * 解决方案:增大Va资源
 */
#define OS_ERRNO_MNG_VA_ALLOC_ERR                     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8a)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG  动态不支持芯片内共享
 *
 * 值: 0x02002f8B
 *
 * 解决方案:不允许动态库有芯片内共享内存，建议修改
 */
#define OS_ERRNO_MNG_DL_CHIP_MEM_UNSUPORT             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8b)
/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG  动态不支持芯片内共享
 *
 * 值: 0x02002f8c
 *
 * 解决方案:不允许动态库有实例内共享内存，建议修改
 */
#define OS_ERRNO_MNG_DL_INST_MEM_UNSUPORT             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8c)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG  找不到系统栈
 *
 * 值: 0x02002f8d
 *
 * 解决方案:找不到系统栈
 */
#define OS_ERRNO_MNG_SYS_STACK_UNEXIST                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8d)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG data段属性不对
 *
 * 值: 0x02002f8e
 *
 * 解决方案:ELF文件受破坏，建议更新版本文件
 */
#define OS_ERRNO_MNG_ELF_DATA_ATTRI_ERR               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8e)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 基础bin段属性错误
 *
 * 值: 0x02002f8f
 *
 * 解决方案:基础bin段的lsp配置错误
 */
#define OS_ERRNO_MNG_SEC_ATTRI_ERR                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8f)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG 基础bin段属性错误
 *
 * 值: 0x02002f90
 *
 * 解决方案:基础bin段的lsp配置错误
 */
#define OS_ERRNO_MNG_HOLE_ALLOC_ERR                   SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x90)


/**
 * @ingroup SRE_mng
 * SRE MNG错误码：创建的进程组个数过多
 *
 * 值: 0x02002f91
 *
 * 解决方案: 对于每个实例，请确保创建的最大进程组个数不超过32。
 */
#define OS_ERRNO_SREMNG_PG_EXHAUST                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x91)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：加载动态库时检查到动态库重复(传入的动态库名及动态库ID与该进程组中已有的动态库相同)。
 *
 * 值: 0x02002f92
 *
 * 解决方案: 请确保对于同一个进程组不会重复加载动态库。
 */
#define OS_ERRNO_SREMNG_DLIB_LOAD_REPEAT              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x92)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：创建进程组时传入的存放进程组ID的地址为空。
 *
 * 值: 0x02002f93
 *
 * 解决方案: 创建进程组时请确保传入的存放进程组ID的地址不为空。
 */
#define OS_ERRNO_SREMNG_PG_ID_ADDR_NULL               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x93)

/**
 * @ingroup SRE_mng
 * 错误码：内存配置入参为空
 *
 * 值: 0x02002f94
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SREMNG_MEM_CFG_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x94)

/**
 * @ingroup SRE_mng
 * 错误码：内存配置在共享名字空间中没有找到
 *
 * 值: 0x02002f95
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_HW_MEM_CFG_NAME_FIND_FAILED          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x95)

/**
 * @ingroup SRE_mng
 * 错误码：共享名字空间中申请内存失败，典型场景是有名空间耗尽，另外，也有可能是有名空间管理块被踩，导致的误报
 *
 * 值: 0x02002f96
 *
 * 解决方案: 确认有名空间剩余内存，若是正常申请耗尽，则需重新规划有名空间的使用。
 */
#define OS_ERRNO_SREMNG_MEM_CFG_NAME_ALLOC_FAILED     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x96)

/**
 * @ingroup SRE_mng
 * 错误码：指定的core ID非法
 *
 * 值: 0x02002f97
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SREMNG_MEM_CFG_CORE_ID_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x97)

/**
 * @ingroup SRE_mng
 * 错误码：指定的实例ID非法,传入的uwInstId实例号参数为0(OS保留)，或者是大于等于最大支持的实例号8
 *
 * 值: 0x02002f98
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SREMNG_MEM_CFG_INST_ID_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x98)

/**
 * @ingroup SRE_mng
 * 错误码：指定的进程组ID非法
 *
 * 值: 0x02002f99
 *
 * 解决方案: 请确保传入的进程组ID为创建进程组时返回的ID。
 */
#define OS_ERRNO_SREMNG_PG_ID_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x99)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：操作的实例还未Ready。
 *
 * 值: 0x02002f9a
 *
 * 解决方案: 请确保当前操作对应的实例创建完成且实例资源已配置完成。
 */
#define OS_ERRNO_SREMNG_INST_NOT_READY                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9a)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：尝试对已经完成资源配置的实例进行资源配置。
 *
 * 值: 0x02002f9b
 *
 * 解决方案: 配置实例资源时请确保该实例未完成资源配置。
 */
#define OS_ERRNO_SREMNG_INST_RES_CONFIG_REPEAT        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9b)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：申请物理内存时，发现物理内存值为0
 *
 * 值: 0x02002f9c
 *
 * 解决方案: 确认给指定核加载BIN或者是动作库时，物理内存是否已经分配，若已分配，则可能在之前的内存申请时耗尽，需要扩大物理内存SIZE。
 */
#define OS_ERRNO_MNG_PHY_SIZE_IS_ZERO                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9c)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：LP模块初始化未完成。
 *
 * 值: 0x02002f9d
 *
 * 解决方案:主核配置自身的反汇编内存空间时，需保证LP模块初始化完成。
 */
#define OS_ERRNO_MNG_DIS_ASM_LP_INITED              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9d)


/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态补丁加载的动态补丁信息不正确。
 *
 * 值: 0x02002f9e
 *
 * 解决方案: 确保SRE MNG动态补丁加载时传入的动态补丁信息指针的正确性,二进制buffer首地址需要4字节对齐。
 */
#define OS_ERRNO_SREMNG_DPAT_PARA_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9e)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态补丁加载或者卸载指定的进程组非法。
 *
 * 值: 0x02002f9f
 *
 * 解决方案: 确保SRE MNG动态补丁加载或者卸载时指定的进程组号的正确性。
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_PG_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9f)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：加载或者卸载动态补丁时发现所属的进程组未启动。
 *
 * 值: 0x02002fa0
 *
 * 解决方案: 先启动进程组再加载或者卸载动态补丁。
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_PG_NOT_RUNNING      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa0)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：加载动态补丁时未找到指定的动态库名或者进程组名
 *
 * 值: 0x02002fa1
 *
 * 解决方案: 先启动进程组(给动态库打补丁，还需要完成该动态库的加载动作)后，才能进行动态补丁的加载动作。
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_NAME_NOT_FIND         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa1)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：SRE MNG动态补丁加载或卸载的动态补丁信息指针为空。
 *
 * 值: 0x02002fa2
 *
 * 解决方案: 确保SRE MNG动态补丁加载或卸载时传入的动态补丁信息指针的正确性。
 */
#define OS_ERRNO_SREMNG_DPAT_PARA_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa2)

 /**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态补丁时，指定的动态库名或者进程组未加载动态补丁。
 *
 * 值: 0x02002fa6
 *
 * 解决方案: 先加载动态补丁，才能进行动态补丁的卸载动作。
 */
#define OS_ERRNO_SREMNG_DPAT_UNLOAD_NOT_FIND_IN_LIB     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa6)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态补丁时未找到内部记录的管理单元序号UnitNO
 *
 * 值: 0x02002fa7
 *
 * 解决方案: 若正确进行补丁加载后，内部一定会生成对应的管理单元序号，只有在内存被踩时，才可能返回该错误码。
 */
#define OS_ERRNO_SREMNG_DPAT_UNLOAD_LOCAL_ID_NOT_FIND   SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa7)

 /**
 * @ingroup SRE_mng
 * SRE MNG错误码：卸载动态补丁时未找到指定的动态库名或者进程组名
 *
 * 值: 0x02002fa8
 *
 * 解决方案: 先启动进程组(给动态库打补丁，还需要完成该动态库的加载动作)后，才能进行动态补丁的卸载动作。
 */
#define OS_ERRNO_SREMNG_DPAT_UNLOAD_NAME_NOT_FIND       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa8)

/**
 * @ingroup SRE_mng
 * SRE MNG错误码：非主核加载或卸载动态补丁时，动态库或者进程组bin名字为空。
 *
 * 值: 0x02002fa9
 *
 * 解决方案: 除了主核基础bin，其他动态补丁加载或者卸载时，传入的动态库名或者进程组名不为空。
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_DLIBNAME_NULL         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa9)


/**
 * @ingroup SRE_mng
 *
 * 支持的最大实例个数。
 */
#define  OS_MAX_SUPPORT_INST      0x8

/**
* @ingroup SRE_mng
* 主控核实例缺省为0
*/
#define OS_MNG_MCPU_INST_ID       0

/**
* @ingroup SRE_mng
* 主控核实例内的进程组缺省为0
*/
#define OS_MNG_MCPU_PG_ID         0

/**
 * @ingroup SRE_mng
 *
 * 分层级的memmap的结构定义。
 */
#define  OS_MNG_HW_CORE_NUM       17
#define  OS_MNG_HW_THREAD_NUM     34
#define  OS_MNG_CLUSTER_NUM       4

typedef struct tagMemAddrLen
{
    UINT32 uwAddr;
    UINT32 uwLen;
}SRE_MEM_ADDR_LEN;

typedef struct tagMemMapPL2
{
    SRE_MEM_ADDR_LEN stVaInfoPL2;                     /**< PL2虚拟地址 */
    SRE_MEM_ADDR_LEN stPaInfoPL2[OS_MNG_HW_CORE_NUM]; /**< PL2物理地址 */
}SRE_MEMMAP_PL2;
typedef struct tagMemMapSL2
{
    SRE_MEM_ADDR_LEN stVaInfoSL2;                      /**< SL2虚拟地址 */
    SRE_MEM_ADDR_LEN stPaInfoSL2[OS_MNG_CLUSTER_NUM];  /**< SL2物理地址 */
}SRE_MEMMAP_SL2;
typedef struct tagMemMapL3
{
    SRE_MEM_ADDR_LEN stVaInfoL3;      /**< L3虚拟地址 */
    SRE_MEM_ADDR_LEN stPaInfoL3;      /**< L3物理地址 */
}SRE_MEMMAP_L3;
typedef struct tagMemMapDDR32
{
    SRE_MEM_ADDR_LEN stVaInfoDDR32;   /**< DDR32虚拟地址 */
    SRE_MEM_ADDR_LEN stPaInfoDDR32;   /**< DDR32物理地址 */
}SRE_MEMMAP_DDR32;
typedef struct tagMemMapDDR64
{
    SRE_MEM_ADDR_LEN stVaInfoDDR64;   /**< DDR64虚拟地址 */
    SRE_MEM_ADDR_LEN stPaInfoDDR64;   /**< DDR64物理地址 */
}SRE_MEMMAP_DDR64;

typedef struct tagInstMMUPageInfo
{
    UINT32 uwPageTbl;                 /**< 硬线程的1级页表基址  */
    UINT32 uwSize;                    /**< 硬线程的页表空间大小 */
}SRE_INST_MMU_PAGE_INFO;

/**
 * @ingroup SRE_mng
 *
 * 版本空间及其补丁空间结构定义。
 * 需要使用某种物理层级的空间时，对应物理层级的虚拟地址空间需配置一份，物理地址空间根据物理层级类型配置，例如PL2空间需要给实例内每个核进行物理空间配置。
 */
typedef struct tagInstMem
{
    SRE_MEMMAP_PL2   stMemMapPL2;      /**< 版本空间PL2内存资源   */
    SRE_MEMMAP_SL2   stMemMapSL2;      /**< 版本空间SL2内存资源   */
    SRE_MEMMAP_L3    stMemMapL3;       /**< 版本空间L3内存资源    */
    SRE_MEMMAP_DDR32 stMemMapDDR32;    /**< 版本空间DDR32内存资源 */
    SRE_MEMMAP_DDR64 stMemMapDDR64;    /**< 版本空间DDR64内存资源 */
    SRE_MEMMAP_PL2   stPatMemMapPL2;   /**< 补丁空间PL2内存资源   */
    SRE_MEMMAP_SL2   stPatMemMapSL2;   /**< 补丁空间SL2内存资源   */
    SRE_MEMMAP_L3    stPatMemMapL3;    /**< 补丁空间L3内存资源    */
    SRE_MEMMAP_DDR32 stPatMemMapDDR32; /**< 补丁空间DDR32内存资源 */
    SRE_MEMMAP_DDR64 stPatMemMapDDR64; /**< 补丁空间DDR64内存资源 */
    SRE_INST_MMU_PAGE_INFO stMmuPageInfo[OS_MNG_HW_THREAD_NUM];   /**< 实例内各个硬线程的MMU页表信息 */
}SRE_INST_MEM_S;

/**
 * @ingroup SRE_mng
 *
 * 进程组类型的枚举定义。
 */
typedef enum
{
    PG_TYPE_PROCESS = 0,               /**< 进程组类型为进程    */
    PG_TYPE_BMCORE,                    /**< 进程组类型为裸核    */
    PG_TYPE_INVALID
}PG_TYPE_E;

/**
 * @ingroup SRE_mng
 *
 * 物理内存的类型定义。
 */
typedef enum
{
    MEM_TYPE_PL2 = 0,
    MEM_TYPE_SL2,
    MEM_TYPE_L3,
    MEM_TYPE_DDR32,
    MEM_TYPE_DDR64,
    MEM_TYPE_INVALID
}MEM_TYPE_E;

/**
 * @ingroup SRE_mng
 *
 * SRE_mng当前运行状态的枚举定义。
 */
typedef enum
{
    /*SRE_InsCreate*/
    INS_CREATE_BEGIN              = 0x101,  /**< 开始创建实例    */
    INS_CREATE_END                = 0x102,  /**< 实例创建结束    */
    /*SRE_InstResCfg*/
    INS_RES_CFG_BEGIN             = 0x103,  /**< 开始配置实例资源    */
    INS_RES_CFG_MEM_REG           = 0x104,  /**< 把配置给给实例的资源注册到内存管理模块    */
    INS_RES_CFG_END               = 0x105,  /**< 结束配置实例资源    */
    /*SRE_InsDelete*/
    INS_DELETE_BEGIN              = 0x106,  /**< 开始删除实例    */
    INS_DELETE_NSM_OBJ_DELETE     = 0x107,  /**< 实例删除时删除有名对象    */
    INS_DELETE_SSC_MEM_DELETE     = 0x108,  /**< 实例删除时SSC内存释放    */
    INS_DELETE_MEM_FREE           = 0x109,  /**< 实例删除时调用内存管理模块释放实例所有内存    */
    INS_DELETE_END                = 0x10A,  /**< 结束删除实例    */
    /*SRE_PgCreate*/
    PG_CREATE_BEGIN               = 0x10B,  /**< 开始进程组创建    */
    PG_CREATE_START_BIN_LOAD      = 0x10C,  /**< 进程组创建时开始BIN加载    */
    PG_CREATE_MEM_GROUP_ADD       = 0x10D,  /**< 进程组创建时开始MemGroup的添加   */
    PG_CREATE_UINT_MEM_ALLOC      = 0x10E,  /**< 进程组创建时开始为基础bin申请版本空间  */
    PG_CREATE_START_BM_BIN_COPY   = 0x10F,  /**< 进程组创建时开始把基础bin拷贝到申请版本空间    */
    PG_CREATE_END                 = 0x110,  /**< 结束进程组创建    */
    /*SRE_MemCfg*/
    MEM_CONFIG_START              = 0x111,  /**< 开始从核内存配置    */
    MEM_CONFIG_SYS_STACK          = 0x112,  /**< 从核配置系统栈内存    */
    MEM_CONFIG_TASK_STACK         = 0x113,  /**< 从核配置任务栈内存     */
    MEM_CONFIG_FSC_PT_MEM         = 0x114,  /**< 从核配置私有FSC内存     */
    MEM_CONFIG_TRACE_MEM          = 0x115,  /**< 从核配置trace内存     */
    MEM_CONFIG_MMU_PA2VA_MEM      = 0x116,  /**< 从核配置MMU的PA2VA内存  */
    MEM_CONFIG_MC_FSC_PT_MEM      = 0x117,  /**< 从核配置共享FSC内存   */
    MEM_CONFIG_LP_SHARE_MEM       = 0x118,  /**< 从核配置LP共享内存   */
    MEM_CONFIG_SYMBOL_TBL_MEM     = 0x119,  /**< 从核配置符号表内存  */
    MEM_CONFIG_END                = 0x11A,  /**< 结束从核内存配置   */
    /*SRE_PgStart*/
    PG_START_BEGIN                = 0x11B,  /**< 开始启动进程组    */
    PG_START_NSM_MMU_ASSGIN       = 0x11C,  /**< 启动进程组时映射基础bin有名空间    */
    PG_START_STACK_ASSGIN         = 0x11D,  /**< 启动进程组时映射基础bin的系统栈    */
    PG_START_MMU_TLB_ASSGIN       = 0x11E,  /**< 启动进程组时映射基础bin的页表空间   */
    PG_START_SLAVE_BOOT_SET       = 0x11F,  /**< 启动进程组时设置基础bin启动参数   */
    PG_START_SLAVE_WAKEUP         = 0x120,  /**< 启动进程组时唤醒从核    */
    PG_START_END                  = 0x121,  /**< 结束启动进程组    */
    /*SRE_DlibLoadFromFile*/
    DLIB_LOAD_START               = 0x122,  /**< 开始加载动态库    */
    DLIB_LOAD_CTRL_MEM_ALLOC      = 0x123,  /**< 加载动态库时申请动态库控制块 */
    DLIB_LOAD_UNIT_MEM_ALLOC      = 0x124,  /**< 加载动态库时申请动态库所需要的内存空间  */
    DLIB_LOAD_MCPU_FETCH_ACTIVE   = 0x125,  /**< 加载动态库时进行主核的加载激活操作   */
    DLIB_LOAD_FETCH_MSG_SEND      = 0x126,  /**< 加载动态库时从核加载动态库消息发送 */
    DLIB_LOAD_FETCH_MSG_RECIVE    = 0x127,  /**< 加载动态库时从核加载动态库消息接收 */
    DLIB_LOAD_END                 = 0x128,  /**< 结束加载动态库    */
    /*SRE_DlibUnload*/
    DLIB_UNLOAD_START             = 0x129,  /**< 开始动态库卸载 */
    DLIB_UNLOAD_MCPU_REMOVE       = 0x12A,  /**< 动态库卸载时主核移除动态库 */
    DLIB_UNLOAD_MCPU_UINT_MEM_FREE= 0x12B,  /**< 动态库卸载时主核动态库内存释放  */
    DLIB_UNLOAD_REMOVE_MSG_SEND   = 0x12C,  /**< 动态库卸载时从核核移除动态库消息发送 */
    DLIB_UNLOAD_REMOVE_MSG_RECIVE = 0x12D,  /**< 动态库卸载时从核核移除动态库消息接收 */
    DLIB_UNLOAD_BM_CORE_UINT_FREE = 0x12E,  /**< 动态库卸载时从核释放动态库占用的版本空间  */
    DLIB_UNLOAD_END               = 0x12F,  /**< 结束动态库卸载 */
    /*SRE_DpatLoadFromFile*/
    DPAT_LOAD_START               = 0x130,  /**< 开始加载动态补丁    */
    DPAT_LOAD_CTRL_MEM_ALLOC      = 0x131,  /**< 加载动态补丁时申请动态补丁控制块 */
    DPAT_LOAD_UNIT_MEM_ALLOC      = 0x132,  /**< 加载动态补丁时申请动态补丁所需要的内存空间  */
    DPAT_LOAD_MCPU_FETCH_ACTIVE   = 0x133,  /**< 加载动态补丁时进行主核的加载激活操作   */
    DPAT_LOAD_FETCH_MSG_SEND      = 0x134,  /**< 加载动态补丁时从核加载动态补丁消息发送 */
    DPAT_LOAD_FETCH_MSG_RECIVE    = 0x135,  /**< 加载动态补丁时从核加载动态补丁消息接收 */
    DPAT_LOAD_END                 = 0x136,  /**< 结束加载动态补丁    */

    DPAT_UNLOAD_START             = 0x137,  /**< 开始动态补丁卸载 */
    DPAT_UNLOAD_MCPU_REMOVE       = 0x138,  /**< 动态补丁卸载时主核移除动态补丁 */
    DPAT_UNLOAD_MCPU_UINT_MEM_FREE= 0x139,  /**< 动态补丁卸载时主核动态补丁内存释放  */
    DPAT_UNLOAD_REMOVE_MSG_SEND   = 0x13A,  /**< 动态补丁卸载时从核核移除动态补丁消息发送 */
    DPAT_UNLOAD_REMOVE_MSG_RECIVE = 0x13B,  /**< 动态补丁卸载时从核核移除动态补丁消息接收 */
    DPAT_UNLOAD_BM_CORE_UINT_FREE = 0x13C,  /**< 动态补丁卸载时从核释放动态补丁占用的补丁空间  */
    DPAT_UNLOAD_END               = 0x13D,  /**< 结束动态补丁卸载 */
}SRE_MNG_STATUS_E;

/**
 * @ingroup SRE_mng
 *
 * 逻辑内存与物理层级的映射关系结构定义。
 */
typedef struct tagMemToLevel
{
    CHAR *pcMemString;
    MEM_TYPE_E eMemLevel;
}SRE_MEM_TO_LEVEL;

/**
 * @ingroup SRE_mng
 *
 * 进程组创建时指定的基础bin的信息结构定义。
 */
typedef struct tagBinLoadInfo
{
    UINT8  *pcBinName;                /**< 基础bin的名字字符串                 */
    UINT8  *pucBinBuf;                /**< 基础bin的二进制buffer               */
    UINT32  uwFileLen;                /**< 基础bin的二进制buffer长度           */
    PG_TYPE_E ePgType;                /**<进程组类型，裸核或用户进程           */
}SRE_BIN_LOAD_PARA_STRU;

/**
 * @ingroup SRE_mng
 *
 * 动态库加载时指定的动态库信息结构定义。
 */
typedef struct tagDlibLoadInfo
{
    UINT32  uwInstID;                 /**< 实例ID                               */
    UINT32  uwPgID;                   /**< 进程组ID                             */
    UINT32  uwDlibID;                 /**< 动态库ID                             */
    UINT8  *pucDlibName;              /**< 动态库名                             */
    SRE_COREMASK *pCoreBitMap;        /**< 动态库加载的核掩码                   */
    UINT8  *pucDlibBuf;               /**< 动态库的二进制buffer                 */
    UINT32  uwFileLen;                /**< 动态库的buffer的长度                 */
    UINT32  uwLogicMemNum;            /**< 动态库的段名与物理层级关系结构体个数 */
    SRE_MEM_TO_LEVEL *pstLogicMemStr; /**< 动态库的段名与物理层级关系结构体     */
}SRE_DLIB_LOAD_PARA_STRU;

/**
 * @ingroup SRE_mng
 *
 * 动态库卸载时指定的动态库信息结构定义。
 */
typedef struct tagDlibUnloadInfo
{
    UINT32  uwInstID;                 /**< 实例ID             */
    UINT32  uwPgID;                   /**< 进程组ID           */
    UINT32  uwDlibID;                 /**< 动态库ID           */
    UINT8   *pucDlibName;             /**< 动态库名           */
    SRE_COREMASK *pCoreBitMap;        /**< 动态库加载的核掩码 */
}SRE_DLIB_UNLOAD_PARA_STRU;

/**
 * @ingroup SRE_mng
 *
 * 打补丁时指定的补丁信息结构定义。
 */
typedef struct tagBinInfo
{
    UINT32  uwInstID;          /**< 实例ID                                              */
    UINT32  uwPgID;            /**< 进程组ID                                            */
    UINT8  *pucPatFileName;    /**< 补丁文件名                                          */
    UINT8  *pucDPatBuf;        /**< 补丁文件二进制buffer                                */
    UINT32  uwFileLen;         /**< 补丁文件buffer长度                                  */
    UINT32  uwDlibID;          /**< 被打补丁的动态库ID                                  */
    UINT8  *pucDlibName;       /**< 被打补丁的补丁名或者进程组名，主核进程组名默认为NULL*/
}SRE_DPAT_LOAD_PARA_STRU;


/**
 * @ingroup SRE_mng
 *
 * MemCfg内存结构定义。
 */
typedef struct tagMemCfg
{
    //以下各配置项按核配置，每个核可以配置不同
    UINT32 uwSysStackAreaSize;       //系统栈大小
    UINT32 uwSysStackAreaMemLevel;   //系统栈所处的内存层级
    UINT32 uwTskStackAreaSize;       //独立任务栈大小(无效,必须填0)
    UINT32 uwTskStackAreaMemLevel;   //任务栈所处的内存层级(无效)
    UINT32 uwFscPtSize;             //私有FSC分区大小
    UINT32 uwFscPtMemLevel;         //私有FSC分区内存层级
    UINT32 uwTraceAreaSize;         //Trace内存大小
    UINT32 uwTraceAreaMemLevel;      //Trace内存类型
    UINT32 uwMmuPhy2VirAreaSize;            //MMU物理地址到虚拟地址转换映射表大小
    UINT32 uwMmuPhy2VirAreaMemLevel;        //MMU物理地址到虚拟地址转换映射表内存层级

    //以下各配置项按实例配置，实例内每个核配置相同
    UINT32 uwMcFscPtSize;           //共享静态FSC分区大小
    UINT32 uwMcFscPtMemLevel;       //共享静态FSC分区内存层级
    UINT32 uwLPShareNcPtSize;       //补丁分区大小，
    UINT32 uwLPShareNcPtMemLevel;   //补丁分区内存类型

    //以下各配置项按进程组(image)配置，进程组内每个核配置相同
    UINT32 uwSymTblNcPtSize;        //符号表内存分区大小，进程组内各个核配置相同
    UINT32 uwSymTblNcPtMemLevel;    //符号表内存分区内存层级
} OS_MEM_CFG_S;

/**
 * @ingroup  SRE_mng
 * @brief 配置从核的内存
 *
 * @par 描述:
 * 配置从核的内存配置项，并从版本空间为从核申请所需的内存。
 *
 *
 * @attention
 *
 * @param  uwCoreId    [IN] 类型#UINT32，核号，取值范围为[0,OS_MAX_CORE_NUM)。
 * @param  uwInstId    [IN] 类型#UINT32，实例ID，取值范围为[0,OS_MAX_SUPPORT_INST)。
 * @param  pstMemCfg   [IN] 类型#OS_MEM_CFG_S，内存配置参数。

 * @retval #OS_ERRNO_SREMNG_MEM_CFG_NULL                     0x02002f94，内存配置入参为空。
 * @retval #OS_ERRNO_SREMNG_MEM_CFG_CORE_ID_INVALID          0x02002f97，指定的core ID非法。
 * @retval #OS_ERRNO_SREMNG_MEM_CFG_INST_ID_INVALID          0x02002f98，指定的实例 ID非法。
 * @retval #OS_ERRNO_SREMNG_INST_NOT_READY                   0x02002f9a，操作的实例还未Ready。
 * @retval #OS_ERRNO_SREMNG_PG_UNEXIST                       0x02002f24，核号没有对应的进程组。
 * @retval #OS_ERRNO_SREMNG_MEM_CFG_NAME_ALLOC_FAILED        0x02002f96，共享名字空间中申请内存失败。
 * @retval #OS_ERRNO_SREMNG_MEMCFG_PHY_LEVEL_INVALID         0x02002f38，配置的物理层级非法。
 * @retval #SRE_OK                                           0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li></li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_MemCfg(UINT32 uwCoreId, UINT32 uwInstId, OS_MEM_CFG_S* pstMemCfg);

/**
 * @ingroup  SRE_mng
 * @brief 创建实例。
 *
 * @par 描述:
 * 创建一个实例。
 *
 * @attention
 * <ul>
 * <li>对于主控核或主控进程，系统会默认为其创建实例，无需用户显示调用该接口进行实例创建。</li>
 * <li>调用该接口完成实例创建后，需要调用SRE_InstResCfg接口进行实例资源配置。</li>
 * </ul>
 *
 * @param  uwVMID        [IN] 类型#UINT32，实例的VMID，范围[0,7]。
 * @param  uwAppVaBase   [IN] 类型#UINT32，当前无效。
 * @param  puwInstId     [OUT] 类型#UINT32 *，用于存储实例ID的地址。
 *
 * @retval #OS_ERRNO_SREMNG_VMID_VALUE_ERR      0x02002f01，SRE MNG传入的VMID非法
 * @retval #OS_ERRNO_SREMNG_INST_ID_ADDR_NULL   0x02002f04，创建实例时传入的用户存放实例ID的地址为空
 * @retval #OS_ERRNO_SREMNG_INST_ID_EXHAUST     0x02002f07，SRE MNG实例创建个数过多，无可用的实例资源
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY           0x02002f06，SREMNG管理的内存不够
 * @retval #SRE_OK                              0x00000000，实例创建成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_InstDelete
 */
extern UINT32 SRE_InstCreate(UINT32 uwVMID, UINT32 uwAppVaBase, UINT32 *puwInstId);

/**
 * @ingroup  SRE_mng
 * @brief 配置实例资源。
 *
 * @par 描述:
 * 为实例uwInstID配置pstMemMap和pCoreBitMap指定的资源。
 *
 * @attention 无
 *
 * @param  uwInstId      [IN] 类型#UINT32，实例ID。
 * @param  pstMemMap     [IN] 类型#SRE_INST_MEM_S*，实例内存资源。
 * @param  pCoreBitMap   [IN] 类型#SRE_COREMASK*，实例的核Bitmap指针。
 *
 * @retval #OS_ERRNO_SREMNG_MEMMAP_NULL             0x02002f02，虚实地址memmap入参为空
 * @retval #OS_ERRNO_SREMNG_CORE_BITMAP_NULL        0x02002f03，核bitmap指针入参为空
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID          0x02002f0b，传入的实例ID非法
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE         0x02002f0c，传入的实例ID为未创建实例
 * @retval #OS_ERRNO_SREMNG_CORE_BITMAP_INVALID     0x02002f05，核bitmap为全0
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY               0x02002f06，SREMNG管理的内存不够
 * @retval #OS_ERRNO_SREMNG_INST_RES_CONFIG_REPEAT  0x02002f9b，尝试对已经完成资源配置的实例进行资源配置
 * @retval #SRE_OK                                  0x00000000，实例创建成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_InstDelete
 */
extern UINT32 SRE_InstResCfg(UINT32 uwInstID, SRE_INST_MEM_S *pstMemMap, SRE_COREMASK *pCoreBitMap);

/**
 * @ingroup  SRE_mng
 * @brief 删除实例。
 *
 * @par 描述:
 * 删除一个实例。
 *
 * @attention 无
 *
 * @param  uwInstId    [IN] 类型#UINT32，待删除的实例ID。
 *
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID      0x02002f0b，实例ID非法
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE     0x02002f0c，指定的实例尚未创建
 * @retval #SRE_OK                              0x00000000，实例删除成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_InstCreate
 */
extern UINT32 SRE_InstDelete(UINT32 uwInstId);

/**
 * @ingroup  SRE_mng
 * @brief 创建进程组。
 *
 * @par 描述:
 * 创建一个进程组。
 *
 * @attention 无
 *
 * @param  uwInstId     [IN] 类型#UINT32，进程组所属的实例。
 * @param  pCoreBitMap  [IN] 类型#SRE_COREMASK*，实例的核Bitmap指针，SD6183按硬线程共34个核给定。
 * @param  pPgAttr      [IN] 类型#VOID*，进程组的基础bin信息结构, 成员信息需通过结构体类型SRE_BIN_LOAD_PARA_STRU输入。
 * @param  puwPgId      [OUT] 类型#UINT32*, 用于存储进程组ID。
 *
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID         0x02002f0b，实例ID非法
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE        0x02002f0c，指定的实例尚未创建
 * @retval #OS_ERRNO_SREMNG_CORE_BITMAP_NULL       0x02002f03，核bitmap指针入参为空
 * @retval #OS_ERRNO_SREMNG_PG_TYPE_INVALID        0x02002f08，进程组类型非法
 * @retval #OS_ERRNO_SREMNG_BIN_PARA_NULL          0x02002f09，基础bin入参结构体指针为NULL
 * @retval #OS_ERRNO_SREMNG_BIN_PARA_INVALID       0x02002f15，基础bin文件信息不正确
 * @retval #OS_ERRNO_SREMNG_PG_COREBITMAP_OVERINST 0x02002f0d，进程组的核bitmap超过所属实例的核bitmap
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY              0x02002f06，SREMNG管理的内存不够
 * @retval #OS_ERRNO_MNG_BIN_LOAD_NO_VALID_VA      0x02002f0e，主核未预留连续的不小于10M的虚拟地址空间
 * @retval #OS_ERRNO_MNG_BIN_LEN_INVALID           0x02002f0f，基础bin信息中指定的文件长度不正确
 * @retval #OS_ERRNO_MNG_BIN_MEMALLOC_FAILED       0x02002f10，加载基础bin申请段内存失败
 * @retval #OS_ERRNO_MNG_BIN_ELF_HEAD_ERROR        0x02002f11，基础bin加载的elf文件头校验错误
 * @retval #OS_ERRNO_MNG_BIN_ELF_FILETYPE_ERROR    0x02002f12，基础bin加载的elf文件类型错误
 * @retval #OS_ERRNO_MNG_BIN_ELF_SEC_HEAD_ERROR    0x02002f0a，ELF文件头里段大小的校验错误
 * @retval #OS_ERRNO_MNG_BIN_ELF_SEC_NUM_ERROR     0x02002f13，elf的段个数不正确
 * @retval #SRE_OK                                 0x00000000，进程组创建成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_PgStart
 */
extern UINT32 SRE_PgCreate(UINT32 uwInstId, SRE_COREMASK * pCoreBitMap, VOID* pPgAttr, UINT32 *puwPgId);

/**
 * @ingroup  SRE_mng
 * @brief 启动进程组。
 *
 * @par 描述:
 * 启动一个进程组。
 *
 * @attention 无
 *
 * @param  uwPgId      [IN] 类型#UINT32，待启动的进程组ID。
 *
 * @retval #OS_ERRNO_SREMNG_PG_ID_INVALID       0x02002f99，指定的进程组ID非法
 * @retval #OS_ERRNO_SREMNG_PG_UNCREATED        0x02002f19，指定的进程组尚未创建
 * @retval #OS_ERRNO_SREMNG_PG_ALREADY_STARTED  0x02002f1a，进程组已被启动
 * @retval #OS_ERRNO_MNG_START_PARA_FIND_FAILED 0x02002f22，启动从核时查找名字空间里的启动参数失败
 * @retval #SRE_OK                              0x00000000，进程组启动成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_PgCreate
 */
extern UINT32 SRE_PgStart(UINT32 uwPgId);

/**
 * @ingroup  SRE_mng
 * @brief 动态库加载。
 *
 * @par 描述:
 * 加载动态库。
 *
 * @attention 无
 *
 * @param  pstPara    [IN] 类型#SRE_DLIB_LOAD_PARA_STRU*，待加载的动态库结构信息。
 * @param  pcFileName [IN] 类型#CHAR *，当前可不输入，或输入Lib名。
 *
 * @retval #OS_ERRNO_SREMNG_DLIB_PARA_NULL            0x02002f16，动态库信息指针为空
 * @retval #OS_ERRNO_SREMNG_DLIB_PARA_INVALID         0x02002f17，动态库信息不正确
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID            0x02002f0b，实例ID非法
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE           0x02002f0c，指定的实例尚未创建
 * @retval #OS_ERRNO_SREMNG_DLIBLOAD_PG_INVALID       0x02002f18，指定的进程组非法
 * @retval #OS_ERRNO_SREMNG_DLIB_COREBITMAP_OVERINST  0x02002f1c，进程组的核bitmap超过所属实例的核bitmap
 * @retval #OS_ERRNO_SREMNG_DLIBLOAD_PG_NOT_RUNNING   0x02002f1e，加载动态库时发现所属的进程组未启动
 * @retval #OS_ERRNO_SREMNG_DLIB_LOAD_REPEAT          0x02002f92，加载动态库时检查到动态库重复
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY                 0x02002f06，SREMNG管理的内存不够
 * @retval #SRE_OK                                    0x00000000，动态库加载成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_DlibUnload
 */
extern UINT32 SRE_DlibLoadFromFile(SRE_DLIB_LOAD_PARA_STRU *pstPara, CHAR *pcFileName);

/**
 * @ingroup  SRE_mng
 * @brief 卸载动态库。
 *
 * @par 描述:
 * 卸载动态库。
 *
 * @attention 无
 *
 * @param  pstPara    [IN] 类型#SRE_DLIB_UNLOAD_PARA_STRU*，待卸载的动态库结构信息。
 *
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_NULL           0x02002f1f，卸载动态库的入参结构体指针为空
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_INVALID        0x02002f2d，动态库卸载的动态库信息不正确
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_INSTID_INVALID      0x02002f2e，卸载操作，传入的实例ID非法
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_INST_NOT_READY      0x02002f2f，卸载操作的实例还未Ready
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_INVALID          0x02002f30，动态库卸载时指定的进程组非法
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_NOT_RUNNING      0x02002f31，卸载动态库时发现所属的进程组未启动
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_CORE_BITMAP_INVALID 0x02002f35，卸载动态库时传入的核bitmap不合法，都为0
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_COREBITMAP_OVERINST 0x02002f36，卸载动态库指定的核bitmap超过了进程组的核bitmap
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_NAME_NOT_FIND       0x02002f32，卸载动态库时未找到指定的库名
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_LOCAL_ID_NOT_FIND   0x02002f33，卸载动态库时未找到内部记录的管理单元序号UnitNO
 * @retval #OS_ERRNO_MNG_UNLOAD_WAIT_SLAVE_CORE_OVERTIME    0x02002f2c，卸载操作，等待从核结果超时
 * @retval #OS_ERRNO_LP_NOT_LOADED                          0x02001e09，LP操作中，LP单元未加载.
 * @retval #OS_ERRNO_LP_HANDLE_CORE_BUSY                    0x02001e9f，需要操作的目的核忙，不能进行动态加载或者卸载操作
 * @retval #SRE_OK                                          0x00000000，卸载动态库成功。
 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_DlibLoadFromFile
 */
extern UINT32 SRE_DlibUnload(SRE_DLIB_UNLOAD_PARA_STRU *pstPara);

/**
 * @ingroup  SRE_mng
 * @brief 加载动态补丁。
 *
 * @par 描述:
 * 加载动态补丁。
 *
 * @attention 无
 *
 * @param  pstPara    [IN] 类型#SRE_DPAT_LOAD_PARA_STRU*，待加载的动态补丁结构信息。pucPatFileName为NULL时，表示卸载对应动态补丁。
 * @param  pcFileName [IN] 类型#CHAR *，当前可不输入，或输入Pat名。
 *
 * @retval #OS_ERRNO_SREMNG_DPAT_PARA_NULL                  0x02002fa2，动态补丁信息指针为空
 * @retval #OS_ERRNO_SREMNG_DPAT_PARA_INVALID               0x02002f9e，动态补丁加载或卸载入参信息不正确
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID                  0x02002f0b，实例ID非法
 * @retval #OS_ERRNO_SREMNG_INST_NOT_READY                  0x02002f9a，操作的实例还未Ready
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_PG_INVALID            0x02002f9f，指定的进程组非法
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_PG_NOT_RUNNING        0x02002fa0，加载或卸载动态补丁时发现所属的进程组未启动
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_DLIBNAME_NULL         0x02002fa9，加载或卸载补丁(非主核基础BIN)的进程组或者动态库名为空。
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_NAME_NOT_FIND         0x02002fa1，加载或卸载补丁的进程组或者动态库名未找到。
 * @retval #OS_ERRNO_SREMNG_DPAT_UNLOAD_NAME_NOT_FIND       0x02002fa8，未找到对应的动态补丁名。
 * @retval #OS_ERRNO_SREMNG_DPAT_UNLOAD_LOCAL_ID_NOT_FIND   0x02002fa7，卸载动态补丁时未找到内部记录的管理单元序号UnitNO
 * @retval #OS_ERRNO_SREMNG_DPAT_UNLOAD_NOT_FIND_IN_LIB     0x02002fa6，SRE MNG错误码：卸载动态补丁时，指定的动态库名或者进程组未加载动态补丁。
 * @retval #OS_ERRNO_MNG_UNLOAD_WAIT_SLAVE_CORE_OVERTIME    0x02002f2c，卸载操作，等待从核结果超时
 * @retval #OS_ERRNO_LP_NOT_LOADED                          0x02001e09，LP操作中，LP单元未加载.
 * @retval #OS_ERRNO_LP_HANDLE_CORE_BUSY                    0x02001e9f，需要操作的目的核忙，不能进行动态加载或者卸载操作
 * @retval #SRE_OK                                          0x00000000，动态补丁加载成功。

 * @par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_DpatLoadFromFile(SRE_DPAT_LOAD_PARA_STRU *pstPara, CHAR *pcFileName);

/**
 *@ingroup sre_lp
 *@brief 设置反汇编内存空间。
 *
 *@par 描述:用户设置反汇编内存空间的起始地址和大小，用来存储反汇编工具解析时需要导出的信息。
 *
 *@attention
 * <ul>
 * <li>地址和空间大小需4k对齐（MMU页表映射需要）。
 * <li>该地址空间按照虚实地址一致进行映射，且该空间不能做其它用途。
 * <li>该空间若不配置，反汇编无法解析。
 * <li>该空间配置了，若出现不够使用情况，则反汇编也不支持解析。
 * <li>该空间使用需在实例创建并配置资源之后，且在进程组启动之前(主核自身配置需在动态库加载之前)，仅主核调用，每个实例需配置一次，否则不能保证所有的动态库都能正确解析。
 * </ul>
 *
 *@param  uwInstId [IN] 类型#UINT32，实例ID。
 *@param uwBufAddr  [IN] 类型#UINT32，用户设定内存空间的起始地址。
 *@param uwBufSize  [IN] 类型#UINT32，设定空间大小。
 *
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID      0x02002f0b，实例ID非法
 * @retval #OS_ERRNO_SREMNG_INST_NOT_READY      0x02002f9a，操作的实例还未Ready。
 * @retval #OS_ERRNO_MNG_DIS_ASM_LP_INITED      0x02002f9d，主核未完成LP模块初始化。
 * @retval #SRE_OK                              0x00000000，成功返回。
 *
 *@par 依赖:
 * <ul><li>sre_mng.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_DisasmAreaSet(UINT32 uwInstID, UINT32 uwBufAddr, UINT32 uwBufSize);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MNG_H */

/**
 * History:
 * 2015-02-06.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

