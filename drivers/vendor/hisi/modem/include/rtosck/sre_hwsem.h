/**
 * @file sre_hwsem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：硬件信号量的对外头文件。 \n
 */

/** @defgroup SRE_hwsem 硬件信号量
  * @ingroup SRE_comm
  */

#ifndef _SRE_HWSEM_H
#define _SRE_HWSEM_H

#include "sre_base.h"
#include "sre_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_hwsem
 * 硬件信号量资源类型:全局硬件信号量资源。
 */
#define SRE_HWSEM_SHARE_GLOBAL    0

/**
 * @ingroup SRE_hwsem
 * 硬件信号量资源类型:cluster内部硬件信号量资源。
 */
#define SRE_HWSEM_SHARE_CLUSTER   1

/**
 * @ingroup SRE_hwsem
 * 硬件信号量工作模式:互斥型硬件信号量资源。
 */
#define SRE_HWSEM_MODE_MUTEX      0

/**
 * @ingroup SRE_hwsem
 * 硬件信号量工作模式:计数型硬件信号量资源访问。
 * 当前只有6181支持该工作模式
 */
#define SRE_HWSEM_MODE_CNT        1

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：创建硬件信号量资源时传入的名字非法。
 *
 * 值: 0x02002401
 *
 * 解决方案: 硬件信号量名不可为0xFFFFFFFF，不可与os预留的0xFFFFFFFE冲突。
 */
#define OS_ERRNO_HWSEM_NAME_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x01)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：创建硬件信号量资源时，传入的模式非法。
 *
 * 值: 0x02002402
 *
 * 解决方案: uwMode入参必须是 SRE_HWSEM_MODE_MUTEX。
 */
#define OS_ERRNO_HWSEM_MODE_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x02)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：创建硬件信号量资源时，传入的硬件信号量ID指针为空。
 *
 * 值: 0x02002403
 *
 * 解决方案: 确保传入的指针非空。
 */
#define OS_ERRNO_HWSEM_ID_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x03)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：删除硬件信号量资源时，被检测出硬件信号量ID高4位即不是全局也不是局部资源类型。
 *
 * 值: 0x02002404
 *
 * 解决方案: 硬件信号量ID需是通过SRE_HwSemCreate接口所得。
 */
#define OS_ERRNO_HWSEM_NOT_ANY_TYPE               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x04)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：SD6108/SD6181平台: 删除硬件信号量资源时，被检测出局部硬件信号量ID的低16位超过了最大资源个数。
 *
 * 值: 0x02002405
 *
 * 解决方案: 硬件信号量ID需是通过SRE_HwSemCreate接口所得。
 */
#define OS_ERRNO_HWSEM_LHWSEM_EXCEED_MAX          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x05)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：SD6108/SD6181平台: 删除硬件信号量资源时，被检测出全局硬件信号量ID的低20位超过了最大资源个数。
 *
 * 值: 0x02002406
 *
 * 解决方案: 硬件信号量ID需是通过SRE_HwSemCreate接口所得。
 */
#define OS_ERRNO_HWSEM_GHWSEM_EXCEED_MAX          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x06)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：SD6108/SD6181平台:删除硬件信号量资源时，被检测出硬件信号量ID的24至27位的工作模式与管理信息不匹配。
 *
 * 值: 0x02002407
 *
 * 解决方案: 硬件信号量ID需是通过SRE_HwSemCreate或者SRE_HwSemCreateById接口所得。
 */
#define OS_ERRNO_HWSEM_MODE_NOT_MATCH             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x07)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：创建硬件信号量资源时，被检测出无可用的硬件信号量资源。
 *
 * 值: 0x02002408
 *
 * 解决方案: 硬件信号量资源有限，若资源耗尽时，需先释放部分资源，再行使用。
 */
#define OS_ERRNO_HWSEM_EXHAUST                    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x08)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：创建硬件信号量资源时，被检测出重复创建。
 *
 * 值: 0x02002409
 *
 * 解决方案: 同一硬件信号量资源不可进行重复创建。
 */
#define OS_ERRNO_HWSEM_CREATED                     SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x09)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：使用硬件信号量资源时，被检测出该硬件信号量已被删除或者未创建。
 *
 * 值: 0x0200240a
 *
 * 解决方案: 检查该硬件信号量是否已经被删除或者未创建。
 */
#define OS_ERRNO_HWSEM_DELETED                    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x0a)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：SD6183平台:VMID的bit位表的值不正确
 *
 * 值: 0x0200240b
 *
 * 解决方案: VMID的bit位表的值范围[0,0xFF]
 */
#define OS_ERRNO_HWSEM_VMID_BIT_MAP_ERR          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x0b)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：获取硬件信号量管理信息句柄失败。
 *
 * 值: 0x02002410
 *
 * 解决方案: 查看输入的输入的硬件信号量ID是否正确。
 */
#define OS_ERRNO_HWSEM_INT_POINT_NULL             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x10)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码：SD6108/SD6181/SD6182/SD6157平台: 硬件信号量初始化时创建错误处理中断失败
 *
 * 值: 0x02002411
 *
 * 解决方案：无
 */
#define OS_ERRNO_HWSEM_INIT_FAILED                SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x11)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: SD6181平台: 硬件信号量模式3创建或者删除时，输入的中断号非法
 *
 * 值: 0x02002412
 *
 * 解决方案：输入合法中断号，DSP中断号范围[15,22]，CPU中断号范围[15,21]
 */
#define OS_ERRNO_HWSEM_HWINUM_INVALID             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x12)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: SD6181平台: 硬件信号量模式3创建时，对应的硬件信号量ID已经绑定中断。
 *
 * 值: 0x02002413
 *
 * 解决方案：输入未绑定的硬件信号量ID。
 */
#define OS_ERRNO_HWSEM_INT_ISSET                  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x13)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: SD6181平台: 为全局硬件信号量创建告警中断时失败。
 *
 * 值: 0x02002414
 *
 * 解决方案：固定使用22号中断，请确认该中断资源是否有被作为独占型资源使用。
 */
#define OS_ERRNO_HWSEM_GHWSEM_INIT_FAILED         SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x14)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: SD6181平台: 硬件信号量模式3重复删除失败
 *
 * 值: 0x02002415
 *
 * 解决方案：保证硬件信号量模式3删除时只操作一次。
 */
#define OS_ERRNO_HWSEM_REPEAT_DEL                 SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x15)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量全局个数配置不可用。
 *
 * 值: 0x02002416
 *
 * 解决方案：检查硬件信号量全局配置个数是否超过范围。6108范围[0-27]，6181范围[0-339]，SD6182/SD6157/SD6183下无效。
 */
#define OS_ERRNO_HWSEM_GLOBE_NUM_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x16)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量局部个数配置不可用。
 *
 * 值: 0x02002417
 *
 * 解决方案：检查硬件信号量局部配置个数是否超过范围。6108范围(0-32)，6181范围(0-32)，SD6182/SD6157/SD6183下无效。
 */
#define OS_ERRNO_HWSEM_LOCAL_NUM_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x17)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量创建参数为空。
 *
 * 值: 0x02002418
 *
 * 解决方案：检查硬件信号量创建参数是否为空。
 */
#define OS_ERRNO_HWSEM_CREATE_PARA_NULL           SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x18)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量类型不可用。
 *
 * 值: 0x0200241b
 *
 * 解决方案：检查输入的硬件信号量类型是否正确。入参必须是SRE_HWSEM_SHARE_GLOBAL or SRE_HWSEM_SHARE_CLUSTER。
 */
#define OS_ERRNO_HWSEM_TYPE_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x1b)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：SD6183平台: VMID的值不正确
 *
 * 值: 0x0200241c
 *
 * 解决方案: VMID值的范围[0,7]
 */
#define OS_ERRNO_HWSEM_VMID_VALUE_ERR          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x1c)


/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量初始化时，内存分配不足。
 *
 * 值: 0x0200241f
 *
 * 解决方案：分配更大的私有FSC静态分区。
 */
#define OS_ERRNO_HWSEM_NO_MEMORY                  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x1f)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量做PEND操作时，输入的ID错误。
 *
 * 值: 0x02002420
 *
 * 解决方案：输入的ID值必须是创建接口返回的信号量ID。
 */
#define OS_ERRNO_HWSEM_PEND_ID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x20)


/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量做PEND操作时，输入的获取中断开关值的指针为空。
 *
 * 值: 0x02002421
 *
 * 解决方案：保证获取中断开关制的指针为非空。
 */
#define OS_ERRNO_HWSEM_INTVALUE_NULL              SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x21)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量做POST操作时，输入的ID错误。
 *
 * 值: 0x02002422
 *
 * 解决方案：输入的ID值必须是创建接口返回的信号量ID。
 */
#define OS_ERRNO_HWSEM_POST_ID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x22)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: 硬件信号量注册配置的个数不一致错误。
 *
 * 值: 0x02002423
 *
 * 解决方案：需要所有的核配置的个数都一致。
 */
#define OS_ERRNO_HWSEM_NUM_NOT_SAME               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x23)

/**@ingroup SRE_hwsem
 * 硬件信号量错误码: SD6182、SD6157及SD6183平台上，硬件信号量还未释放，不能删除。
 *
 * 值: 0x02002424
 *
 * 解决方案：需要先释放该硬件信号量。
 */
#define OS_ERRNO_HWSEM_NOT_POST                   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x24)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 配置实例启动参数时传入的全局硬件信号量起始ID非法。
 *
 * 值: 0x02002425
 *
 * 解决方案: 请确保传入的全局硬件信号量起始ID不超过最大编号(SD6182为63，SD6157为31，SD6183为127)，且不等于0(0号硬件信号量固定被OS用作实例间互斥保护)。
 */
#define OS_ERRNO_HWSEM_CFG_GLB_START_ID_INVALID   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x25)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 配置实例启动参数时传入的全局硬件信号量个数非法。
 *
 * 值: 0x02002426
 *
 * 解决方案: 请确保传入的全局硬件信号量个数不小于3个(OS对于每个实例使用3个)，SD6182不大于64个，SD6157不大于32个，SD6183不大于128个。
 */
#define OS_ERRNO_HWSEM_CFG_GLB_NUM_INVALID        SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x26)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 配置实例启动参数时配置的全局硬件信号量区间非法。
 *
 * 值: 0x02002427
 *
 * 解决方案: 请确保传入的全局硬件信号量起始编号和个数决定的区间在合法范围内，SD6182:[1,63]，SD6157:[1,31], SD6183:[1,127]。
 */
#define OS_ERRNO_HWSEM_CFG_GLB_REGION_INVALID     SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x27)


/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 配置实例启动参数时传入的局部硬件信号量起始ID过大。
 *
 * 值: 0x02002428
 *
 * 解决方案: 请确保传入的局部硬件信号量起始ID不超过最大编号(SD6157/SD6182:15，SD6183:31)。
 */
#define OS_ERRNO_HWSEM_CFG_LOCAL_START_ID_INVALID SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x28)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: SD6182/SD6157/SD6183平台: 配置实例启动参数时传入的局部硬件信号量个数非法。
 *
 * 值: 0x02002429
 *
 * 解决方案: 请确保传入的局部硬件信号量个数不大于(SD6157/SD6182:16，SD6183:32)。
 */
#define OS_ERRNO_HWSEM_CFG_LOCAL_NUM_INVALID      SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x29)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 配置实例启动参数时配置的局部硬件信号量区间非法。
 *
 * 值: 0x0200242a
 *
 * 解决方案: 请确保传入的局部硬件信号量起始编号和个数在正常的区间范围内(SD6157/SD6182:[1,16]，SD6183:[1,32])。
 */
#define OS_ERRNO_HWSEM_CFG_LOCAL_REGION_INVALID   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2a)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 复位或者创建指定物理ID的硬件信号量时，输入的全局硬件信号量物理ID非法。
 *
 * 值: 0x0200242b
 *
 * 解决方案: 请确保传入的全局硬件信号量物理ID(SD6182:[0,63],SD6157:[0,31],SD6183:[0,127])范围内，并且不能为0(被OS使用)和本实例内已经配置过的硬件信号量资源。
 */
#define OS_ERRNO_HWSEM_GLB_PHYSICAL_ID_INVALID    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2b)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 复位或者创建指定物理ID的硬件信号量时，输入的局部硬件信号量物理ID非法。
 *
 * 值: 0x0200242c
 *
 * 解决方案: 请确保传入的局部硬件信号量物理ID正常范围内(SD6157/SD6182:[0,15]，SD6183:[0,31])，并且不能为本实例内已经配置过的局部硬件信号量资源。
 */
#define OS_ERRNO_HWSEM_LOCAL_PHYSICAL_ID_INVALID  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2c)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码: 复位指定物理ID的硬件信号量，并且类型为局部硬件信号量时，输入的Cluster ID非法。
 *
 * 值: 0x0200242d
 *
 * 解决方案: 复位指定物理ID的硬件信号量，并且类型为局部硬件信号量时，请确保传入的输入的Cluster ID在(SD6182/SD6183:[0,3],SD6157:[0,0])范围内。
 */
#define OS_ERRNO_HWSEM_CLUSTER_ID_INVALID         SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2d)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：删除硬件信号量资源时，被检测出硬件信号量ID非法。
 *
 * 值: 0x0200242e
 *
 * 解决方案: 硬件信号量ID需是通过SRE_HwSemCreate或者SRE_HwSemCreateById接口所得。
 */
#define OS_ERRNO_HWSEM_DELETE_ID_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2e)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：SD6157创建局部硬件信号量失败。
 *
 * 值: 0x0200242f
 *
 * 解决方案: SD6157的12核所在的cluster没有局部硬件信号量，不允许创建局部硬件信号量。
 */
#define OS_ERRNO_HWSEM_LOCAL_CTEATE_FAIL          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2f)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：通道号错误。
 *
 * 值: 0x02002430
 *
 * 解决方案: SD6183平台全局的通道索引号[0,15]，局部的通道索引号[0,3]。
 */
#define OS_ERRNO_HWSEM_CHNO_ERR                   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x30)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：通道组号错误。
 *
 * 值: 0x02002431
 *
 * 解决方案: SD6183平台通道组号[0,3]。
 */
#define OS_ERRNO_HWSEM_CHGNO_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x31)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：核号错误。
 *
 * 值: 0x02002432
 *
 * 解决方案: SD6183平台的核号范围[0,33]。
 */
#define OS_ERRNO_HWSEM_COREID_ERR                 SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x32)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：cluster ID错误。
 *
 * 值: 0x02002433
 *
 * 解决方案: SD6183平台cluster ID的取值是[0,4],0:dsp cluster0  1:dsp clustr1 2:dsp clustr2 3:cc clustr 4:main cluster。
 */
#define OS_ERRNO_HWSEM_CLUSTER_ID_ERR             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x33)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：全局硬件信号量单核撤销未找到与指定核VMID相符的通道组。
 *
 * 值: 0x02002434
 *
 * 解决方案: 检查目的核的VMID的配置和全局硬件信号量通道组VMID的配置。
 */
#define OS_ERRNO_HWSEM_CORE_OR_GCHG_VMID_ERR       SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x34)

/**
 *@ingroup SRE_hwsem
 *硬件信号量错误码: PEND已持有的直接模式硬件信号量。
 *
 *值：0x03002435
 *
 *解决方案：不要重复PEND已持有的直接模式硬件信号量。
 */
#define OS_ERRNO_HWSEM_PEND_REPEAT                SRE_ERRNO_OS_FATAL(OS_MID_HWSEM, 0x35)

/**
 *@ingroup SRE_hwsem
 *硬件信号量错误码: POST不持有的直接模式硬件信号量。
 *
 *值：0x03002436
 *
 *解决方案：不要POST不持有的直接模式硬件信号量，请先PEND再POST。
 */
#define OS_ERRNO_HWSEM_POST_ILLEGAL               SRE_ERRNO_OS_FATAL(OS_MID_HWSEM, 0x36)

/**
 *@ingroup SRE_hwsem
 *硬件信号量错误码: 硬件信号量PEND超时。
 *
 *值：0x02002437
 *
 *解决方案：释放硬件信号量资源。
 */
#define OS_ERRNO_HWSEM_PEND_TIMEOUT               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x37)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：局部硬件信号量单核撤销未找到与指定核VMID相符的通道组。
 *
 * 值: 0x02002438
 *
 * 解决方案: 检查目的核的VMID的配置和局部硬件信号量通道组VMID的配置。
 */
#define OS_ERRNO_HWSEM_CORE_OR_LCHG_VMID_ERR      SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x38)

/**
 * @ingroup SRE_hwsem
 * 硬件信号量错误码：硬件信号量单核撤销时全局或者局部都未找到与指定核VMID相符的通道组。
 *
 * 值: 0x02002439
 *
 * 解决方案: 查看CDA记录的错误码，检查目的核的VMID的配置和全局或局部硬件信号量通道组VMID的配置。
 */
#define OS_ERRNO_HWSEM_CORE_OR_CHG_VMID_ERR       SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x39)

#if (OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup sre_hwsem
 * 硬件信号量的cluster ID
 */
typedef enum tagHwSemCluster
{
    OS_HWSEM_LOCAL_CLUSTER0 = 0,/**< 局部DSP cluster 0 ID  */
    OS_HWSEM_LOCAL_CLUSTER1 = 1,/**< 局部DSP cluster 1 ID  */
    OS_HWSEM_LOCAL_CLUSTER2 = 2,/**< 局部DSP cluster 2 ID  */
    OS_HWSEM_LOCAL_CLUSTER3 = 3,/**< 局部CC cluster 0 ID   */
    OS_HWSEM_MAIN_CLUSTER = 4   /**< 全局硬件信号量簇ID     */
} OS_HWSEM_CLUSTER_E;
#endif

/**
 * @ingroup SRE_hwsem
 * 计数模式硬件信号量处理函数。
 */
typedef VOID (* HWSEM_PROC_FUNC)( UINT32);


/**
 * @ingroup SRE_hwsem
 * 硬件信号量模块创建参数的结构体定义。
 */
typedef struct tagHwsemCreatePara
{
    UINT32   uwName;                         /**< 硬件信号量名称，信号量资源的唯一标识  */
    UINT8    ucMode;                         /**< 硬件信号量的模式，模式当前仅支持互斥SRE_HWSEM_MODE_MUTEX*/
    UINT8    ucType;                         /**< 硬件信号量的类型，类型为全局SRE_HWSEM_SHARE_GLOBAL或局部SRE_HWSEM_SHARE_CLUSTER*/
    UINT16   usHwiNum;                       /**< 计数模式中断号，暂不使用  */
    HWSEM_PROC_FUNC    pfnHwsemHandler;      /**< 硬件信号量计数模式回调函数，暂不使用 */
    UINT32   uwArg;                          /**< 硬件信号量计数模式回调函数参数，暂不使用 */
} HWSEM_CREATE_PARA_S;

/**
 * @ingroup SRE_hwsem
 * 硬件信号量模块配置信息的结构体定义。
 */
typedef struct tagHwsemModInfo
{
    UINT32 uwGMaxNum;                /**< 最大支持的全局硬件信号量数  */
    UINT32 uwLMaxNum;                /**< 最大支持的局部硬件信号量数  */
}HWSEM_MOD_INFO_S;

/**
 * @ingroup  SRE_hwsem
 * @brief 创建硬件信号量。
 *
 * @par 描述:
 * 根据用户指定的模式及类型，创建硬件信号量资源。
 *
 * @attention
 * <ul>
 * <li>硬件信号量用于多核之间的互斥。</li>
 * <li>若多个核需要使用同一硬件信号量资源，则每个核均需进行创建，且名字一定要相同。</li>
 * <li>一个硬件信号量资源名对应一个硬件信号量资源，故不同资源需从名字上进行区别开来。</li>
 * <li>当前仅支持互斥访问模式。</li>
 * <li>适用于SD6108、SD6181、SD6182、SD6157、SD6183平台。</li>
 * <li>由于低功耗模式下，可能会关闭部分局部硬件信号量，所以使用局部硬件信号量资源时，需要用户保证局部硬件信号量资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * </ul>
 *
 * @param  pstCreatePara [IN] 类型#HWSEM_CREATE_PARA_S *，硬件信号量创建参数。
 * @param  puwHwSemId    [OUT] 类型#UINT32 *，存储返回给用户的硬件信号量逻辑ID，用户使用此ID进行后续的硬件信号量资源申请释放删除等操作。
 *
 * @retval #OS_ERRNO_HWSEM_NAME_INVALID         0x02002401，硬件信号量名非法。
 * @retval #OS_ERRNO_HWSEM_ID_NULL              0x02002403，传入的硬件信号量ID指针为空。
 * @retval #OS_ERRNO_HWSEM_CREATED              0x02002409，同一硬件信号量资源被重复创建。
 * @retval #OS_ERRNO_HWSEM_EXHAUST              0x02002408，无可用的硬件信号量资源。
 * @retval #OS_ERRNO_HWSEM_CREATE_PARA_NULL     0x02002418，硬件信号量参数结构体指针为空。
 * @retval #OS_ERRNO_HWSEM_TYPE_INVALID         0x0200241b，传入的资源类型非法。
 * @retval #OS_ERRNO_HWSEM_MODE_INVALID         0x02002402，创建硬件信号量资源时，传入的模式非法。
 * @retval #OS_ERRNO_HWSEM_LOCAL_CTEATE_FAIL    0x0200242f，12核不允许创建局部硬件信号量(只对SD6157芯片有效)。
 * @retval #SRE_OK                              0x00000000，创建硬件信号量资源成功。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemDelete
 */
extern UINT32 SRE_HwSemCreate (HWSEM_CREATE_PARA_S *pstCreatePara, UINT32 *puwHwSemId);

/**
 * @ingroup  SRE_hwsem
 * @brief 删除硬件信号量。
 *
 * @par 描述:
 * 删除指定的硬件信号量资源。
 *
 * @attention
 * <ul>
 * <li>若多个核使用了同一硬件信号量资源，每个核均需调用删除接口释放资源。</li>
 * <li>由于低功耗模式下，可能会关闭部分局部硬件信号量，所以删除局部硬件信号量资源时，需要用户保证局部硬件信号量资源可被正常访问(未被关断)，否则会导致核挂死。</li>
 * <li>适用于SD6108、SD6181、SD6182、SD6157、SD6183平台。</li>
 * </ul>
 * @param  uwHwSemId   [IN] 类型#UINT32，硬件信号量逻辑ID，通过SRE_HwSemCreate接口所得。
 *
 * @retval #OS_ERRNO_HWSEM_DELETED              0x0200240a，该硬件信号量资源已被删除。
 * @retval #OS_ERRNO_HWSEM_NOT_ANY_TYPE         0x02002404，该硬件信号量类型错误。
 * @retval #OS_ERRNO_HWSEM_GHWSEM_EXCEED_MAX    0x02002406，该硬件信号量资源全局个数非法。
 * @retval #OS_ERRNO_HWSEM_LHWSEM_EXCEED_MAX    0x02002405，该硬件信号量资源局部个数非法。
 * @retval #OS_ERRNO_HWSEM_INT_POINT_NULL       0x02002410，获取硬件信号量管理信息句柄失败。
 * @retval #OS_ERRNO_HWSEM_MODE_NOT_MATCH       0x02002407，该硬件信号量资源模式与记录不匹配。
 * @retval #OS_ERRNO_HWSEM_DELETE_ID_INVALID    0x0200242e，传入的硬件信号量逻辑ID非法。
 * @retval #OS_ERRNO_HWSEM_NOT_POST             0x02002424，该硬件信号量资源还未释放。
 * @retval #SRE_OK                              0x00000000，删除硬件信号量资源成功。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemCreate
 */
extern UINT32 SRE_HwSemDelete(UINT32 uwHwSemId);

/**
 * @ingroup  SRE_hwsem
 * @brief 关中断并获取互斥硬件信号量。
 *
 * @par 描述:
 * 间接模式下，关中断获取指定的互斥模式的硬件信号量。
 *
 * @attention
 * <ul>
 * <li>调用本接口后会关中断。如果Pend失败，系统会返回到关中断之前的状态。</li>
 * <li>Pend接口使用的入参一定是硬件信号量创建后返回的ID。</li>
 * <li>Pend接口只适用于互斥模式的硬件信号量。</li>
 * <li>Pend接口调用成功后，在POST之前不可开中断，或者做任务切换，否则有造成系统死锁的风险。</li>
 * <li>适用于SD6108、SD6181、SD6182、SD6157、SD6183平台。</li>
 * <li>由于低功耗模式下，可能会关闭部分局部硬件信号量，所以使用局部硬件信号量资源执行Pend操作时，需要用户保证局部硬件信号量资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * </ul>
 *
 * @param  uwHwSemId   [IN]  类型#UINT32，信号量ID。
 * @param  puvIntSave  [OUT] 类型#UINTPTR *，关中断前的PS状态值。
 *
 * @retval #OS_ERRNO_HWSEM_INTVALUE_NULL       0x02002421，PEND操作时，输入的获取中断开关值的指针为空。
 * @retval #OS_ERRNO_HWSEM_PEND_ID_INVALID     0x02002420，PEND操作时，输入的ID错误。
 * @retval #OS_ERRNO_HWSEM_DELETED             0x0200240a，PEND操作时，硬件信号量未创建或者已经被删除。
 * @retval #SRE_OK                             0x00000000，PEND硬件信号量资源成功。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPost
 */
extern UINT32 SRE_HwSemPend(UINT32 uwHwSemId, UINTPTR *puvIntSave);

/**
 * @ingroup  SRE_hwsem
 * @brief 恢复中断并释放互斥硬件信号量。
 *
 * @par 描述:
 * 间接模式下，恢复中断并释放指定的互斥模式的硬件信号量。
 *
 * @attention
 * <ul>
 * <li>本接口需要跟SRE_HwSemPend配套使用。调用结束之后会开中断。</li>
 * <li>本接口需要使用者保证uvIntSave值的正确性，否则会造成系统异常。</li>
 * <li>Post接口使用的入参一定是硬件信号量创建后返回的ID。</li>
 * <li>Post接口只适用于互斥模式的硬件信号量。</li>
 * <li>调用Post接口成功之前，不可开中断，或者做任务切换，否则有造成系统死锁的风险。</li>
 * <li>适用于SD6108、SD6181、SD6182、SD6157、SD6183平台。</li>
 * <li>由于低功耗模式下，可能会关闭部分局部硬件信号量，所以使用局部硬件信号量资源Post操作时，需要用户保证局部硬件信号量资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * </ul>
 *
 * @param  uwHwSemId [IN] 类型#UINT32，信号量ID。
 * @param  uvIntSave [IN] 类型#UINTPTR，关中断Pend操作时返回的值。
 *
 * @retval #OS_ERRNO_HWSEM_POST_ID_INVALID     0x02002422，POST操作时，输入的ID错误。
 * @retval #OS_ERRNO_HWSEM_DELETED             0x0200240a，POST操作时，硬件信号量未创建或者已经被删除。
 * @retval #OS_ERRNO_HWSEM_POST_ILLEGAL        0x03002436，POST不持有的直接模式硬件信号量。
 * @retval #SRE_OK                             0x00000000，POST硬件信号量资源成功。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPend
 */
extern UINT32 SRE_HwSemPost(UINT32 uwHwSemId, UINTPTR uvIntSave);

#if (OS_OPTION_HWSEM_DIRECT == YES)
/**
 * @ingroup  SRE_hwsem
 * @brief 在一段时间内，关中断并获取互斥硬件信号量。
 *
 * @par 描述:
 * 直接模式下，在一段时间内，关中断获取指定的互斥模式的硬件信号量。
 *
 * @attention
 * <ul>
 * <li>调用本接口后会关中断。如果Pend失败，系统会返回到关中断之前的状态。</li>
 * <li>Pend接口使用的入参一定是硬件信号量创建后返回的ID。</li>
 * <li>Pend接口只适用于互斥模式的硬件信号量。</li>
 * <li>Pend接口调用成功后，在POST之前不可开中断，或者做任务切换，否则有造成系统死锁的风险。</li>
 * <li>Pend超时后返回，由业务自行决定超时后处理，最大不超过100ms，超过100ms按100ms处理，全F表示永久等待。</li>
 * <li>适用于SD6182、SD6157平台。</li>
 * </ul>
 *
 * @param  uwHwSemId   [IN]  类型#UINT32，信号量ID。
 * @param  uwTimeOut   [IN]  类型#UINT32，PEND超时时间，单位：us。
 * @param  puvIntSave  [OUT] 类型#UINTPTR *，关中断前的PS状态值。
 *
 * @retval #OS_ERRNO_HWSEM_INTVALUE_NULL       0x02002421，PEND操作时，输入的获取中断开关值的指针为空。
 * @retval #OS_ERRNO_HWSEM_PEND_ID_INVALID     0x02002420，PEND操作时，输入的ID错误。
 * @retval #OS_ERRNO_HWSEM_DELETED             0x0200240a，PEND操作时，硬件信号量未创建或者已经被删除。
 * @retval #OS_ERRNO_HWSEM_PEND_REPEAT         0x03002435，PEND已持有的直接模式硬件信号量。
 * @retval #OS_ERRNO_HWSEM_PEND_TIMEOUT        0x02002437，硬件信号量PEND超时。
 * @retval #SRE_OK                             0x00000000，PEND硬件信号量资源成功。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwSemPend
 */
extern UINT32 SRE_HwSemPendInTime(UINT32 uwHwSemId, UINT32 uwTimeOut, UINTPTR *puvIntSave);
#endif

#if (OS_CPU_TYPE == OS_SD6182 || OS_CPU_TYPE == OS_SD6157 || OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup  SRE_hwsem
 * @brief 复位指定硬件信号量物理ID的硬件信号量。
 *
 * @par 描述:
 * 根据指定的硬件信号量物理ID，复位硬件信号量资源。
 *
 * @attention
 * <ul>
 * <li>仅供SD6182、SD6157、SD6183平台使用。</li>
 * <li>对于SD6183平台这个接口即操作了COMM的寄存器又操作了RAT寄存器,操作者需要COMM和RAT权限。</li>
 * <li>调用此接口前，由用户保证待复位的硬件信号量已经被删除。</li>
 * <li>待复位的硬件信号量不能为0号全局硬件信号量和通过启动参数配置的硬件信号量(所有实例)。</li>
 * <li>复位局部硬件信号量资源时，需要用户保证指定的局部硬件信号量资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * </ul>
 *
 * @param  uwType       [IN] 类型#UINT32，复位指定物理ID的硬件信号量类型，为全局(#SRE_HWSEM_SHARE_GLOBAL)或者局部(#SRE_HWSEM_SHARE_CLUSTER)硬件信号量。
 * @param  uwClusterId  [IN] 类型#UINT32，Cluster ID(簇ID)，取值范围为[0,3]。
 * @param  uwHwsemPhyId [IN] 类型#UINT32，硬件信号量物理ID，取值范围为实例内配置的硬件信号量资源。
 *
 * @retval #OS_ERRNO_HWSEM_TYPE_INVALID              0x0200241b，传入的资源类型非法。
 * @retval #OS_ERRNO_HWSEM_GLB_PHYSICAL_ID_INVALID   0x0200242b，传入的全局硬件信号量ID非法。
 * @retval #OS_ERRNO_HWSEM_CLUSTER_ID_INVALID        0x0200242d，传入的Cluster ID非法。
 * @retval #OS_ERRNO_HWSEM_LOCAL_PHYSICAL_ID_INVALID 0x0200242c，传入的局部硬件信号量ID非法。
 * @retval #SRE_OK                                   0x00000000，复位指定物理ID的硬件信号量资源成功。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwSemCreateById
 */
extern UINT32 SRE_HwSemReset(UINT32 uwType, UINT32 uwClusterId, UINT32 uwHwsemPhyId);

/**
 * @ingroup  SRE_hwsem
 * @brief 创建指定硬件信号量物理ID的硬件信号量。
 *
 * @par 描述:
 * 根据指定的硬件信号量物理ID，创建硬件信号量资源。
 *
 * @attention
 * <ul>
 * <li>仅供SD6182、SD6157、SD6183平台使用。</li>
 * <li>硬件信号量用于两个核之间的互斥（核级别的互斥）。</li>
 * <li>第一次使用此接口前，必须先调用复位接口(#SRE_HwSemReset)对相应的硬件信号量资源进行复位。</li>
 * <li>待创建的硬件信号量不能为OS占用和实例已经配置的硬件信号量资源。</li>
 * <li>使用局部硬件信号量资源时，需要用户保证指定的局部硬件信号量资源可被正常使用(未被关断)，否则会导致核挂死。</li>
 * </ul>
 *
 * @param  uwType       [IN] 类型#UINT32，创建指定物理ID的硬件信号量类型，为全局(#SRE_HWSEM_SHARE_GLOBAL)或者局部(#SRE_HWSEM_SHARE_CLUSTER)硬件信号量。
 * @param  uwHwsemPhyId [IN] 类型#UINT32，硬件信号量物理ID。
 * @param  puwHwSemId   [OUT] 类型#UINT32 *，存储返回给用户的硬件信号量逻辑ID，用户使用此ID进行后续的硬件信号量资源申请释放删除等操作。
 *
 * @retval #OS_ERRNO_HWSEM_TYPE_INVALID              0x0200241b，传入的资源类型非法。
 * @retval #OS_ERRNO_HWSEM_GLB_PHYSICAL_ID_INVALID   0x0200242b，传入的全局硬件信号量ID非法。
 * @retval #OS_ERRNO_HWSEM_LOCAL_PHYSICAL_ID_INVALID 0x0200242c，传入的局部硬件信号量ID非法。
 * @retval #OS_ERRNO_HWSEM_CREATED                   0x02002409，同一硬件信号量资源被重复创建。
 * @retval #OS_ERRNO_HWSEM_LOCAL_CTEATE_FAIL         0x0200242f，12核不允许创建局部硬件信号量(只对SD6157芯片有效)。
 * @retval #SRE_OK                                   0x00000000，创建硬件信号量资源成功。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwSemCreate | SRE_HwSemReset
 */
extern UINT32 SRE_HwSemCreateById(UINT32 uwType, UINT32 uwHwsemPhyId, UINT32 *puwHwSemId);
#endif

#if (OS_CPU_TYPE == OS_SD6183)

#if (OS_OPTION_USR_PROCESS == NO)

/**
 * @ingroup  SRE_hwsem
 * @brief 设置通道VMID。
 *
 * @par 描述:
 * 设置某个cluster的某个通道(8个硬件信号量一个通道)的VMID bit表。
 * @attention
 * <ul>
 * <li>仅供SD6183平台使用。</li>
 * <li>仅MCPU(单核)调用，否则硬件会上报错误中断。</li>
 * <li>main函数之后，调用硬件信号量的VMID设置，否则可能出现硬件信号量VMID保护不使能的情况。</li>
 * </ul>
 *
 * @param  uwClusterID [IN] 类型#UINT32，cluster ID号取值[0,4]，含义参考#OS_HWSEM_CLUSTER_E。
 * @param  uwChNo [IN] 类型#UINT32，通道号，全局硬件信号量取值[0,15]，局部硬件信号量取值[0,3]。
 * @param  uwChVmidBitMap [IN] 类型#UINT32，通道VMID（8bit）取值[0,0xFF]。
 *
 * @retval #SRE_OK                          0x00000000，设置成功。
 * @retval #OS_ERRNO_HWSEM_CLUSTER_ID_ERR   0x02002433，cluster ID错误。
 * @retval #OS_ERRNO_HWSEM_CHNO_ERR         0x02002430，通道号错误。
 * @retval #OS_ERRNO_HWSEM_VMID_BIT_MAP_ERR 0x0200240b，VMID的bit位表的值不正确。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_HwsemIntVmidSet
 */
extern UINT32 SRE_HwsemChVmidSet(UINT32 uwClusterID, UINT32 uwChNo, UINT32 uwChVmidBitMap);

/**
 * @ingroup  SRE_hwsem
 * @brief 中断VMID设置。
 *
 * @par 描述:
 * 根据物理核号设置全局硬件信号量和局部(4个cluster)硬件信号量的中断VMID。
 * @attention
 * <ul>
 * <li>仅供SD6183平台使用。</li>
 * <li>仅MCPU(主核)调用，否则硬件会上报错误中断。</li>
 * <li>main函数之后，调用硬件信号量的VMID设置，否则可能出现硬件信号量VMID保护不使能的情况。</li>
 * </ul>
 *
 * @param  uwCoreID [IN] 类型#UINT32，核号，取值[0,33]。
 * @param  uwIntVmidBitMap [IN] 类型#UINT32，通道VMID（8bit），取值[0,0xFF]。
 *
 * @retval #SRE_OK                          0x00000000，设置成功。
 * @retval #OS_ERRNO_HWSEM_COREID_ERR       0x02002432，核号错误。
 * @retval #OS_ERRNO_HWSEM_VMID_BIT_MAP_ERR 0x0200240b，VMID的bit位表的值不正确。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_HwsemChVmidSet
 */
extern UINT32 SRE_HwsemIntVmidSet(UINT32 uwCoreID, UINT32 uwIntVmidBitMap);

/**
 * @ingroup  SRE_hwsem
 * @brief 通道组VMID设置。
 *
 * @par 描述:
 * 按通道组号设置全局硬件信号量和局部(4个cluster)硬件信号量的通道组VMID。
 * @attention
 * <ul>
 * <li>仅供SD6183平台使用。</li>
 * <li>仅MCPU(主核)调用，否则硬件会上报错误中断。</li>
 * <li>main函数之后，调用硬件信号量的VMID设置，否则可能出现硬件信号量VMID保护不使能的情况。</li>
 * </ul>
 *
 * @param  uwChgNo [IN] 类型#UINT32，通道组号，取值[0,3]。
 * @param  uwChgVmid [IN] 类型#UINT32，通道VMID（3bit），取值[0,7]。
 *
 * @retval #SRE_OK                           0x00000000，设置成功。
 * @retval #OS_ERRNO_HWSEM_VMID_VALUE_ERR    0x0200241c，VMID的值不正确。
 * @retval #OS_ERRNO_HWSEM_CHGNO_ERR         0x02002431，通道组号错误。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_HwsemChVmidSet
 */
extern UINT32 SRE_HwsemChgVmidSet(UINT32 uwChgNo, UINT32 uwChgVmid);

/**
 * @ingroup  SRE_hwsem
 * @brief 单核撤销申请。
 *
 * @par 描述:
 * 释放指定核持有的硬件信号量并撤销该核的硬件信号量申请请求。
 * @attention
 * <ul>
 * <li>仅供SD6183平台使用。</li>
 * </ul>
 *
 * @param  uwCoreID [IN] 类型#UINT32，核号，取值[0,33]。
 *
 * @retval #SRE_OK                                  0x00000000，返回成功。
 * @retval #OS_ERRNO_HWSEM_COREID_ERR               0x02002432，核号错误。
 * @retval #OS_ERRNO_HWSEM_CORE_OR_GCHG_VMID_ERR    0x02002434，全局通道组VMID匹配失败。
 * @retval #OS_ERRNO_HWSEM_CORE_OR_LCHG_VMID_ERR    0x02002438，局部通道组VMID匹配失败。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_HwsemPendCancel(UINT32 uwCoreID);

#endif

#endif

#if (OS_CPU_TYPE == OS_SD6181)
/**
 * @ingroup  SRE_hwsem
 * @brief 创建模式3硬件信号量。
 *
 * @par 描述:
 * 硬件信号量模式3创建接口，配置中断号和中断处理函数。
 *
 * @attention
 * <ul>
 * <li>仅供SD6181平台使用。</li>
 * <li>硬件信号量ID号固定，取值为[414-coreID*2,415-coreID*2]两个。</li>
 * <li>配置的中断号，可选范围[15~22]。</li>
 * <li>该接口只需要Pend核调用创建。</li>
 * <li>用户需要在中断处理函数接口中调用SRE_HwiClearPendingBit清除中断标志位。</li>
 * <li>由于硬件清除中断存在时延，建议用户进入中断服务程序后先清除中断，再执行其他的操作，这样可以保证有足够的时间将中断清除。</li>
 * <li>入参的有效性需用户保证，OS内部没有对信号量ID进行判断。</li>
 * </ul>
 *
 * @param  uwHwsemID      [IN]   类型#UINT32，模式3硬件信号量ID,硬件信号量ID取值范围[414-coreID*2,415-coreID*2]。
 * @param  uwHwiNum       [IN]   类型#UINT32，VIC配置中断号，CPU平台可选范围[15~21]，DSP平台可选范围[15~22]。
 * @param  pfnHandler     [IN]   类型#VOID *，中断处理函数接口，用户需要在该接口中调用SRE_HwiClearPendingBit清楚中断标志位。
 * @param  uwArg          [IN]   类型#UINT32，调用硬中断处理函数时传递的参数。
 *
 * @retval #OS_ERRNO_HWSEM_HWINUM_INVALID       0x02002412，硬件信号量模式3创建时，输入的中断号非法。
 * @retval #OS_ERRNO_HWSEM_INT_ISSET            0x02002413，硬件信号量模式3创建时，对应的硬件信号量ID已经绑定中断。
 * @retval #OS_ERRNO_HWI_PROC_FUNC_NULL         0x02001403，输入的硬中断处理函数为空。
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED        0x02001402，输入中断号已经创建。
 * @retval #SRE_OK                              0x00000000，硬件信号量模式3创建成功。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemDeleteEx
 */
extern UINT32 SRE_HwSemCreateEx(UINT32 uwHwsemID, UINT32 uwHwiNum, HWI_PROC_FUNC pfnHandler, HWI_ARG_T uwArg);

/**
 * @ingroup  SRE_hwsem
 * @brief 删除模式3硬件信号量。
 *
 * @par 描述:
 * 硬件信号量模式3删除接口，删除创建时的中断号。
 *
 * @attention
 * <ul>
 * <li>仅供SD6181平台使用，必须由创建核来调用该删除接口进行删除。且删除时该信号量资源必须已经使用完毕。</li>
 * <li>硬件信号量ID号固定，取值为[414-coreID*2,415-coreID*2]两个。</li>
 * <li>配置的中断号，可选范围[15~22]。</li>
 * <li>入参的有效性需用户保证，OS内部没有对信号量ID进行判断。</li>
 * </ul>
 *
 * @param  uwHwsemID      [IN]   类型#UINT32，模式3硬件信号量ID,硬件信号量ID取值范围[414-coreID*2,415-coreID*2]。
 * @param  uwHwiNum       [IN]   类型#UINT32，VIC配置中断号，CPU平台可选范围[15~21]，DSP平台可选范围[15~22]。
 *
 * @retval #OS_ERRNO_HWSEM_HWINUM_INVALID       0x02002402，硬件信号量模式3删除时，输入的中断号非法。
 * @retval #OS_ERRNO_HWSEM_REPEAT_DEL           0x02002405，硬件信号量模式3删除重复删除。
 * @retval #SRE_OK                              0x00000000，硬件信号量模式3删除成功。
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemCreateEx
*/
extern UINT32 SRE_HwSemDeleteEx(UINT32 uwHwsemID, UINT32 uwHwiNum);

/**
 * @ingroup  SRE_hwsem
 * @brief 获取模式3硬件信号量。
 *
 * @par 描述:
 * 对模式3硬件信号量进行Pend操作, 设定计数初值。
 *
 * @attention
 * <ul>
 * <li>本模块仅针对SD6181有效。</li>
 * <li>设置初始计数值，新的计数器值必须大于0，并且原来的计数器必须等于0，否则会触发硬件信号量异常。</li>
 * <li>硬件信号量ID号固定，取值为[414-coreID*2,415-coreID*2]两个。</li>
 * <li>入参的有效性需用户保证，OS内部没有对信号量ID进行判断。</li>
 * </ul>
 *
 * @param    uwHwSemID     [IN]   类型#UINT32，模式3硬件信号量ID。
 * @param    uwInitCount   [IN]   类型#UINT32，模式3硬件信号量初值计数，可选范围[1~255]。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPostEx
 */
extern VOID SRE_HwSemPendEx(UINT32 uwHwSemID, UINT32 uwInitCount);

/**
 * @ingroup  SRE_hwsem
 * @brief 释放模式3硬件信号量。
 *
 * @par 描述:
 * 对模式3硬件信号量进行Post操作，信号量资源的计数值将减1，当计数值为0时，则触发pend核中断。
 *
 * @attention
 * <ul>
 * <li>本模块仅针对SD6181有效。</li>
 * <li>必须先调用#SRE_HwSemPendEx接口，才能调用该接口。</li>
 * <li>调用该接口时，必须保证信号量资源的计数值不为0，否则会触发硬件信号量异常。</li>
 * <li>硬件信号量ID号固定，取值为[414-coreID*2,415-coreID*2]两个。</li>
 * <li>入参的有效性需用户保证，OS内部没有对信号量ID进行判断。</li>
 * </ul>
 *
 * @param    uwHwSemID     [IN]   类型#UINT32，模式3硬件信号量ID。
 *
 * @par 依赖:
 * <ul><li>sre_hwsem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPendEx
 */
extern VOID SRE_HwSemPostEx(UINT32 uwHwSemID);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_HWSEM_H */



