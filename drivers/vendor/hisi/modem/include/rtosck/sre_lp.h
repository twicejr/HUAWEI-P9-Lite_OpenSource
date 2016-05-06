/**
 * @file sre_lp.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：多核LP的h文件。 \n
 */
#ifndef _SRE_LP_H
#define _SRE_LP_H
#include "sre_base.h"
#include "sre_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**@defgroup sre_lp 动态加载和补丁模块
 * @ingroup sre_lp
 */

/**
 * @ingroup sre_lp
 * 基础bin组名定义
 */
#define OS_LP_BASE_BIN_GROUP_NAME                       0x0

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元号非法，为0值或者超过了最大的配置。
 *
 * 值: 0x02001e01
 *
 *解决方案:请检查LP单元号合法性
 */
#define OS_ERRNO_LP_NO_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_LP, 0x01)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元crc校验失败。
 *
 * 值: 0x02001e02
 *
 *解决方案:请检查LP文件的正确性
 */
#define OS_ERRNO_LP_CRC_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x02)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁文件中的标示头不正确。
 *
 * 值: 0x02001e03
 *
 *解决方案:静态补丁文件的增量标示不是"SP"，重新制作增量补丁文件
 */
#define OS_ERRNO_LP_SP_FLAG_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x03)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁文件的文件名不正确。
 *
 * 值: 0x02001e04
 *
 *解决方案:静态补丁文件文件名不正确，重新制作补丁
 */
#define OS_ERRNO_LP_SP_NAME_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x04)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP文件结构变更升级版本号错误。
 *
 * 值: 0x02001e05
 *
 *解决方案:请检查制作LP文件工具端的LP文件结构协议版本号与SRE_LPGetVersion获取的版本号是否一致,检查工具端协议版本是否正确
 */
#define OS_ERRNO_LP_PROTOCOL_VER_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x05)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP文件重复加载。
 *
 * 值: 0x02001e06
 *
 *解决方案:检查代码中是否有LP文件重复加载，并修改
 */
#define OS_ERRNO_LP_LOADED                              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x06)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁文件中代码段与配置中的代码段不一致。
 *
 * 值: 0x02001e07
 *
 *解决方案:请检查makepatch.ini文件中的静态补丁代码段配置与SRE_LPGroupInfoReg接口中的配置是否相同
 */
#define OS_ERRNO_LP_CODE_ADDR_NOT_SUIT                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x07)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁文件中数据段与配置中的共享数据段或私有数据段不一致。
 *
 * 值: 0x02001e08
 *
 *解决方案:请检查makepatch.ini文件中的静态补丁共享数据段和私有数据段配置与SRE_LPGroupInfoReg接口中的配置是否相同
 */
#define OS_ERRNO_LP_DATA_ADDR_NOT_SUIT                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x08)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP操作中，LP单元未加载.
 *
 * 值: 0x02001e09
 *
 *解决方案:请确认LP单元已加载.
 */
#define OS_ERRNO_LP_NOT_LOADED                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x09)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 该LP单元已经处于激活状态。
 *
 * 值: 0x02001e0a
 *
 *解决方案:无
 */
#define OS_ERRNO_LP_IS_ACTIVE                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 该LP单元已经处于去激活状态。
 *
 * 值: 0x02001e0c
 *
 *解决方案:无
 */
#define OS_ERRNO_LP_IS_DEACTIVE                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 入参为空。
 *
 * 值: 0x02001e0d
 *
 *解决方案:查看输入的指针变量是否为空
 */
#define OS_ERRNO_LP_INPUT_IS_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 缓冲区长度不够，或者缓冲区长度为0，请检查入参是否正确。
 *
 * 值: 0x02001e0e
 *
 *解决方案:查看输入的缓冲区长度
 */
#define OS_ERRNO_LP_BUF_NOT_ENOUGH                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 内存申请失败，LP操作过程中需要动态申请内存。
 *
 * 值: 0x02001e0f
 *
 *解决方案:请将内存空间适当配大
 */
#define OS_ERRNO_LP_MEM_NOT_ENOUGH                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 6108/6181只支持静态补丁(SP)。
 *
 * 值: 0x02001e10
 *
 *解决方案:检查6108、6181平台是否配置为动态补丁或者动态加载(DP/DL/DL_DP)。
 */
#define OS_ERRNO_LP_6108_6181_DLDP_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x10)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁(SP)查询加载的代码或数据长度时指定的LP类型不合法。
 *
 * 值: 0x02001e11
 *
 *解决方案:确保查询静态补丁代码或数据长度信息时指定LP组中的LP类型必须为SP。
 */
#define OS_ERRNO_LP_SP_TYPE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x11)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁单元代码段开始地址小于补丁区代码段首地址，或者静态补丁单元代码段超出补丁区代码段范围。
 *
 * 值: 0x02001e12
 *
 *解决方案:请检查静态补丁单元代码段开始地址或适当增加补丁区代码段大小
 */
#define OS_ERRNO_LP_CODE_OVER_FLOW                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x12)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁单元数据段开始地址小于补丁区数据段首地址，或者静态补丁单元数据段超出补丁区数据段范围。
 *
 * 值: 0x02001e13
 *
 *解决方案:请检查静态补丁单元数据段开始地址或适当增加补丁区数据段大小
 */
#define OS_ERRNO_LP_DATA_OVER_FLOW                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x13)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁或者动态补丁删除过程中，原函数指令被破坏，不能回退补丁状态。
 *
 * 值: 0x02001e14
 *
 *解决方案:静态补丁或者动态补丁删除过程中，原函数指令被破坏，不能回退补丁状态
 */
#define OS_ERRNO_LP_INSTRUCTION_DESTROYED               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x14)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁或者动态补丁加载的补丁函数个数超过了最大的限制。
 *
 * 值: 0x02001e15
 *
 *解决方案:请检查配置接口中最大函数个数是否正确
 */
#define OS_ERRNO_LP_FUNC_OVERFLOW                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x15)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 入参中的LP文件长度不是正确的LP文件长度
 *
 * 值: 0x02001e16
 *
 *解决方案:检查LP文件正确性，或者重新制作LP文件
 */
#define OS_ERRNO_LP_FILE_IS_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x16)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 重复注册的LP组信息不一致。
 *
 * 值: 0x02001e17
 *
 *解决方案:确保LP组信息重复注册时注册的组信息参数必须跟前一次相同(包括镜像ID，补丁区或段区配置参数等)
 */
#define OS_ERRNO_LP_INFO_REPEAT_DIFFER                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x17)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 指定镜像的组信息未被初始化。
 *
 * 值: 0x02001e18
 *
 *解决方案:检查对应镜像中是否有核没有调用SRE_LPGroupInfoReg初始化或者初始化失败或者镜像DSSNUM配置错误。
 */
#define OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x18)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载，动态补丁段名配置相同
 *
 * 值: 0x02001e19
 *
 *解决方案:修改相同的段名为不同段名。
 */
#define OS_ERRNO_LP_SEC_NAME_SAME                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x19)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP启动同步过程失败，超时。
 *
 * 值: 0x02001e1a
 *
 *解决方案:无
 */
#define OS_ERRNO_LP_START_SYN_FAIL                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载或动态补丁调用非补丁替换函数CALL重定位错误。
 *
 * 值: 0x02001e1b
 *
 *解决方案:确认符号是否4字节对齐或超过call调用范围。
 */
#define OS_ERRNO_LP_CALL_OFFECT_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP去激活时LP操作同步过程失败。
 *
 * 值: 0x02001e1c
 *
 *解决方案:无
 */
#define OS_ERRNO_LP_DEACTIVE_SYN_PHASE_FAIL              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 同步过程中需要申请共享内存，共享内存申请失败。
 *
 * 值: 0x02001e1d
 *
 *解决方案:请配置合理的共享内存空间。
 */
#define OS_ERRNO_LP_ALLOC_COMM_MEM_FAIL                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 设置同步参数失败。
 *
 * 值: 0x02001e1e
 *
 *解决方案:无
 */
#define OS_ERRNO_LP_SET_PARA_FAIL                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁加载中，已经加载的补丁单元与再次加载的补丁单元不一致。crc校验不通过。
 *
 * 值: 0x02001e1f
 *
 *解决方案:请确认已经加载的静态补丁单元与再次加载的静态补丁单元一致性
 */
#define OS_ERRNO_LP_INCLUDE_OLDFILE_FUNC_UNCOVERED        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP包的FLAG不正确，不等于"SP"、"DL"、"DP"。Cortex-A7、Cortex-A9平台必须为"DP"。
 *
 * 值: 0x02001e20
 *
 *解决方案:检查版本是否制作正确，第一个LP标志是否是"SP"、"DL"、"DP"之一，Cortex-A7、Cortex-A9平台必须为"DP"。
 */
#define OS_ERRNO_LP_IDENT_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x20)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP文件的crc校验失败。
 *
 * 值: 0x02001e21
 *
 *解决方案:请确认是否正确操作
 */
#define OS_ERRNO_LP_PACKET_CRC_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x21)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP加载操作或获取LP文件中的最大LP单元号时传入的缓冲区地址(pucBuf)非4字节对齐。
 *
 * 值: 0x02001e22
 *
 *解决方案:保证入参缓冲区地址(pucBuf)4字节对齐。
 */
#define OS_ERRNO_LP_BUF_ADDR_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x22)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 配置的补丁区或段区(起始地址及长度)未按照cache line对齐(SD6181/SD6108为64字节，SD6182为128字节)，或者私有补丁区未按照4字节对齐。
 *
 * 值: 0x02001e23
 *
 *解决方案:重新配置补丁区或段区的起始地址及长度。
 */
#define OS_ERRNO_LP_REG_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x23)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元最大函数个数配置为0。
 *
 * 值: 0x02001e24
 *
 *解决方案:检查配置的LP单元最大函数个数
 */
#define OS_ERRNO_LP_REG_FUNC_NUM_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x24)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 查询动态加载或动态补丁的段信息时指定LP组的LP类型错误。
 *
 * 值: 0x02001e25
 *
 *解决方案:使用SRE_LPSectionInfoGet接口查询指定LP组段信息时对应LP类型不能为静态补丁类型(LP_TYPE_SP)。
 */
#define OS_ERRNO_LP_SEC_INFO_QUERY_LP_TYPE_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x25)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁ELF段对齐错误。
 *
 * 值: 0x02001e26
 *
 *解决方案:查看动态加载或动态补丁ELF文件是否有问题。
 */
#define OS_ERRNO_LP_SEC_ALIGN_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x26)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁中有LP单元没有被加载。
 *
 * 值: 0x02001e27
 *
 *解决方案:由于静态补丁是增量补丁，请查看静态补丁中加载的ELF文件是否有问题。
 */
#define OS_ERRNO_LP_SP_NOT_LOADED                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x27)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁符号表段头中每个符号节点的大小错误
 *
 * 值: 0x02001e28
 *
 *解决方案:查看动态加载或动态补丁ELF文件是否有问题。
 */
#define OS_ERRNO_LP_ITEM_SIZE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x28)

/**
  * @ingroup sre_lp
  * 多核LP错误码定义: 注册保存LP单元状态的钩子函数为空。
  *
  * 值: 0x02001e29
  *
  *解决方案:排查注册保存LP单元状态的钩子函数是否为空。
  */
#define OS_ERRNO_LP_REG_STATESAVEHOOK_NULL                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x29)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 镜像ID错误
 *
 * 值: 0x02001e2a
 *
 *解决方案:检查配置的镜像ID是否小于镜像数或者配置的镜像ID是否与其他镜像ID冲突。
 */
#define OS_ERRNO_LP_IMAGE_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP配置不一致
 *
 * 值: 0x02001e2b
 *
 *解决方案:请确保补丁的最大LP管理信息组个数、分区号、分区地址、分区长度、芯片类型配置一致
 */
#define OS_ERRNO_LP_CONFIG_NOT_SAME                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 最大补丁和动态加载库的总单元个数配置无效
 *
 * 值: 0x02001e2c
 *
 *解决方案:请确保LP总单元数在config文件中配置范围为[1,9999]
 */
#define OS_ERRNO_LP_NUM_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 供LP使用的分区起始地址非法
 *
 * 值: 0x02001e2d
 *
 *解决方案:确保分区起始地址(#OS_LP_SHARE_NC_PT_ADDR)非0
 */
#define OS_ERRNO_LP_MEMPT_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 供LP使用的分区大小为0
 *
 * 值: 0x02001e2e
 *
 *解决方案:确保分区大小(#OS_PATCH_SHARE_NC_PT_SIZE)非0
 */
#define OS_ERRNO_LP_MEMPT_SIZE_IS_ZERO                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP的代码区超过了0x40000000
 *
 * 值: 0x02001e2f
 *
 *解决方案:SD6181/SD6108/SD6182的代码均放在了0x4000000以下的地址空间，由于XTENSA核只支持1G空间内的函数调用，
 *若将LP的代码区放置在大于等于0x40000000的空间，LP激活后，被打补丁函数将无法返回其父函数。因此，
 *LP的代码区应该配置在0x40000000以下的空间。
 */
#define OS_ERRNO_LP_CODE_PUT_IN_ANOTHER_1G                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 补丁区或段区个数错误
 *
 * 值: 0x02001e30
 *
 *解决方案:补丁区或段区个数不能小于1
 */
#define OS_ERRNO_LP_AREA_NUM_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x30)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁补丁区的代码段配置错误
 *
 * 值: 0x02001e31
 *
 *解决方案:静态补丁补丁区的代码段起始地址、长度均不能为0
 */
#define OS_ERRNO_LP_CFG_CODE_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x31)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁补丁区的共享数据段配置错误
 *
 * 值: 0x02001e32
 *
 *解决方案:静态补丁补丁区的共享数据段起始地址、长度均不能为0，数据段总长度不能小于共享数据段的长度
 */
#define OS_ERRNO_LP_CFG_SDATA_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x32)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁补丁区的私有数据段配置错误
 *
 * 值: 0x02001e33
 *
 *解决方案:1）静态补丁补丁区的私有数据段起始地址不能为0，如果没有私有数据，私有数据段的长度可配置为0，但起始地址不能为0
 *         2）若静态补丁补丁区的共享属性为假（意味着补丁区放置于私有内存，例如SD6181/SD6108的L1空间），则只允许出现私有数据。
 *            由于私有数据段已经通过结构体#LP_SP_AREA_INFO的uwDataShareAreaAddr和uwDataShareAreaSize成员进行配置，
 *            因此结构体的uwDataAreaSize不能大于uwDataShareAreaSize。
 */
#define OS_ERRNO_LP_CFG_PDATA_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x33)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁补丁区的数据段配置错误
 *
 * 值: 0x02001e34
 *
 *解决方案:1）若静态补丁补丁区的共享属性为真，则SD6181/SD6108/SD6182的共享/私有数据段只能放置在共享内存（SD6181/SD6182：L2/L3/DDR，SD6108：L2/DDR）。
 *         2）若静态补丁补丁区的共享属性为假，则SD6181/SD6108/SD6182的私有数据段只能放置在私有内存（SD6181/SD6108：L1，SD6182：LL2）。
 */
#define OS_ERRNO_LP_CFG_DATA_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x34)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁补丁区号错误
 *
 * 值: 0x02001e35
 *
 *解决方案:静态补丁补丁区号不能大于等于SRE_LPGroupInfoReg注册的最大补丁区个数uwAreaNum
 */
#define OS_ERRNO_LP_AREA_NO_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x35)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁L1地址不允许配置为全局地址
 *
 * 值: 0x02001e36
 *
 *解决方案:SD6181/SD6108，将静态补丁补丁区配置在L1时，请使用私有地址（(0, 0x10000000)），而不是全局地址（[0x80000000, 0x8FFFFFFF]）。
 */
#define OS_ERRNO_LP_GLB_L1_ADDR                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x36)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁代码段不允许放在DRAM，数据段不允许放在IRAM
 *
 * 值: 0x02001e37
 *
 *解决方案:由于XTENSA的硬件限制，代码段不允许放在DRAM（RISC170：0x01000000~0x0101FFFF，DSP170：0x01000000~0x0107FFFF），
 *         数据段不允许放在IRAM（RISC170：0x01020000~0x0103FFFF，DSP170：0x01080000~0x0109FFFF），而且代码段或者数据段的起
 *始地址加上代码段或者数据段的长度不能超过所配置的IRAM或者DRAM内存空间，请排查；
 */
#define OS_ERRNO_LP_L1_ADDR_ERR                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x37)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 芯片类型错误
 *
 * 值: 0x02001e38
 *
 *解决方案:芯片类型既非SD6181，也非SD6108，也非SD6182。
 */
#define OS_ERRNO_LP_CHIP_TYPE_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x38)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 输入的LP单元状态不正确,其中空闲状态也为非法。
 *
 * 值: 0x02001e39
 *
 *解决方案:请填写正确的LP单元状态
 */
#define OS_ERRNO_LP_STATE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x39)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 配置的核的数目与之前配置的不同或配置的核数小于本Image实际运行的核数。
 *
 * 值: 0x02001e3a
 *
 *解决方案:检查DSS数目的正确性，或者检查imageID是否配置错误。
 */
#define OS_ERRNO_LP_DSS_NUM_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载、动态补丁段属性错误。
 *
 * 值: 0x02001e3b
 *
 *解决方案:检查ELF文件是否有问题。
 */
#define OS_ERRNO_LP_SECTION_FLAG_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载或动态补丁时申请内存失败。
 *
 * 值: 0x02001e3c
 *
 *解决方案:增大LP的内存分区大小。
 */
#define OS_ERRNO_LP_MEM_ALLOC_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载重定位段，段头大小错误。
 *
 * 值: 0x02001e3d
 *
 *解决方案:检查ELF文件是否有问题。
 */
#define OS_ERRNO_LP_REL_ENTSIZE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载或动态补丁时ELF文件头错误。
 *
 * 值: 0x02001e3e
 *
 *解决方案:检查ELF文件是否有问题。
 */
#define OS_ERRNO_LP_ELF_HEAD_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载或动态补丁时ELF段表头错误。
 *
 * 值: 0x02001e3f
 *
 *解决方案:检查ELF文件是否有问题。
 */
#define OS_ERRNO_LP_ELF_SEC_HEAD_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载或动态补丁时ELF段信息校验错误。
 *
 * 值: 0x02001e40
 *
 *解决方案:检查ELF文件是否有问题。
 */
#define OS_ERRNO_LP_ELF_SEC_NUM_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x40)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载或动态补丁加载时获取段信息错误。
 *
 * 值: 0x02001e41
 *
 *解决方案:检查动态加载动态补丁的所属的段是否已经注册。
 */
#define OS_ERRNO_LP_SEC_INFO_GET_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x41)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP组信息注册，入参指针为空。
 *
 * 值: 0x02001e42
 *
 *解决方案:检查LP组信息注册时入参指针是否为空。
 */
#define OS_ERRNO_LP_PARA_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x42)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP加载时，LP包的类型和核支持的类型不符。
 *
 * 值: 0x02001e43
 *
 *解决方案:检查核注册的类型和LP包的类型是否一致。
 */
#define OS_ERRNO_LP_FETCH_TYPE_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x43)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态补丁替换的函数个数大于用户配置的补丁单元最大函数替换个数。
 *
 * 值: 0x02001e44
 *
 *解决方案:增大LP单元最大补丁替换函数的配置，或者减少动态补丁函数替换的个数。
 */
#define OS_ERRNO_LP_FETCH_REPLACE_FUNC_OVERFLOW             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x44)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载符号和运行版本的符号重复定义或者动态补丁全局变量出现重复定义。
 *
 * 值: 0x02001e45
 *
 *解决方案:检查动态加载文件里面符号和运行版本的符号是否重复或者检查动态补丁文件里面定义的变量是否重复，重复将其删除。
 */
#define OS_ERRNO_LP_FETCH_DL_FUNC_REDEFINE                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x45)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 重定位符号对应的指令类型不支持
 *
 * 值: 0x02001e46
 *
 *解决方案:查看该目标文件编译的核是否跟OS支持的核匹配，包括指令架构、编译选项等。
 */
#define OS_ERRNO_LP_INST_TYPE_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x46)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 注册的LP类型错误。
 *
 * 值: 0x02001e47
 *
 *解决方案:排查注册的LP类型是否是#LP_TYPE枚举的类型之一,对于CORTEX-AX平台，类型必须为LP_TYPE_DP。
 */
#define OS_ERRNO_LP_REG_LP_TYPE_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x47)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP模块未初始化，注册LP组信息的镜像没有经过初始化。
 *
 * 值: 0x02001e48
 *
 *解决方案:检查是否OS中LP模块裁剪开关没打开，或者初始化没有完成。
 */
#define OS_ERRNO_LP_NOT_INITED                              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x48)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 静态补丁配置补丁区为空。
 *
 * 值: 0x02001e49
 *
 *解决方案:检查是否未配置静态补丁补丁区或者LP类型错误。
 */
#define OS_ERRNO_LP_HPAREAINFO_IS_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x49)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态补丁动态加载配置段区为空。
 *
 * 值: 0x02001e4a
 *
 *解决方案:检查是否未配置动态补丁动态加载段区或者LP类型错误。
 */
#define OS_ERRNO_LP_DLDPAREAINFO_IS_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁的段区的起始地址或者长度配置错误
 *
 * 值: 0x02001e4b
 *
 *解决方案:动态加载动态补丁的段区的起始地址、长度均不能为0
 */
#define OS_ERRNO_LP_CFG_SEC_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁的段区名字为空
 *
 * 值: 0x02001e4c
 *
 *解决方案:动态加载动态补丁的段区名字不能为空
 */
#define OS_ERRNO_LP_CFG_SEC_NAME_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 节区表内存申请错误。
 *
 * 值: 0x02001e4d
 *
 *解决方案:配大LP内存管理分区的大小。
 */
#define OS_ERRNO_LP_SECTAB_MEM_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 读节区表错误。
 *
 * 值: 0x02001e4e
 *
 *解决方案:ELF文件的格式与要求的不符合。
 */
#define OS_ERRNO_LP_SECTAB_READ_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载和动态补丁加载时，RO_DATA段溢出
 *
 * 值: 0x02001e4f
 *
 *解决方案:增大RO_DATA段的空间。
 */
#define OS_ERRNO_LP_RO_DATA_OVERFLOW                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 符号重定位时L32R指令重定位错误，可能是偏移量大于0x3FFFF，或者偏移量非4字节对齐
 *
 * 值: 0x02001e50
 *
 *解决方案:查看段配置是否有问题。
 */
#define OS_ERRNO_LP_L32R_OFFECT_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x50)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 节区个数错误。
 *
 * 值: 0x02001e51
 *
 *解决方案:ELF的段个数不能为0，请确认补丁或动态加载文件的正确性。
 */
#define OS_ERRNO_LP_SEC_NUM_ADDR_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x51)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 临时符号表生成错误。
 *
 * 值: 0x02001e52
 *
 *解决方案:SD6182平台,尝试配大LP管理分区大小，请确认补丁或动态加载文件的正确性。
 */
#define OS_ERRNO_LP_SYM_BUILD_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x52)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LOCAL L2地址不允许配置为全局地址(Cluster Local L2 Global Address)。
 *
 * 值: 0x02001e53
 *
 *解决方案:SD6181/SD6108/SD6182，使用SP将私有补丁区配置在核Local L2地址时，请使用私有地址（(0, 0x0807FFFF)），而不是全局地址（[0x90000000, 0x9A47FFFF]）。
 */
#define OS_ERRNO_LP_GLB_L2_ADDR                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x53)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP激活时对应LP单元的LP类型错误。
 *
 * 值: 0x02001e54
 *
 *解决方案:LP加载时LP类型是否正确。
 */
#define OS_ERRNO_LP_SYN_SET_TYPE_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x54)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载，动态补丁需要依赖符号表模块。
 *
 * 值: 0x02001e55
 *
 *解决方案:使用动态加载动态补丁需要打开符号表模块。
 */
#define OS_ERRNO_LP_DEPEND_SYMBOL_INITED                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x55)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载包和动态补丁包加载之后，代码段溢出
 *
 * 值: 0x02001e56
 *
 *解决方案:增大代码段的空间。
 */
#define OS_ERRNO_LP_CODE_OVERFLOW                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x56)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载包和动态补丁包加载之后，DATA段溢出
 *
 * 值: 0x02001e57
 *
 *解决方案:增大DATA段的空间。
 */
#define OS_ERRNO_LP_DATA_OVERFLOW                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x57)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载包和动态补丁包加载之后，BSS段溢出
 *
 * 值: 0x02001e58
 *
 *解决方案:增大BSS段的空间。
 */
#define OS_ERRNO_LP_BSS_OVERFLOW                            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x58)

/**
  * @ingroup sre_lp
  * 多核LP错误码定义: LP管理组ID在使用中，不能去注册该LP信息管理组。
  *
  * 值: 0x02001e59
  *
  *解决方案:排查LP管理组信息去注册时动态加载及LP管理信息组ID管理的所有LP单元是否没有处于空闲状态。
  */
#define OS_ERRNO_LP_GROUP_ID_IN_USE                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x59)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 申请LP单元控制块失败
 *
 * 值: 0x02001e5b
 *
 *解决方案:检查加载的LP单元个数是否已经大于配置的最大LP单元数。
 */
#define OS_ERRNO_LP_PATCH_INDEX_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 被打补丁函数大小小于16字节
 *
 * 值: 0x02001e5c
 *
 *解决方案:检查被打补丁的函数是否小于16字节。
 */
#define OS_ERRNO_LP_PATCH_FUNC_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 段内存管理初始化失败
 *
 * 值: 0x02001e5d
 *
 *解决方案:检查配置的段是否太小，或者地址配置错误。
 */
#define OS_ERRNO_LP_MEM_INIT_FAILD                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5d)


/**
  * @ingroup sre_lp
  * 多核LP错误码定义: ARM MOVW/MOVT指令重定位错误。
  *
  * 值: 0x02001e5e
  *
  *解决方案:检查ELF文件是否正确。
  */
#define OS_ERRNO_LP_ARM_MOVE_RELOC_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5e)

/**
  * @ingroup sre_lp
  * 多核LP错误码定义: THUMB MOVW/MOVT指令重定位错误。
  *
  * 值: 0x02001e5f
  *
  *解决方案:检查ELF文件是否正确。
  */
#define OS_ERRNO_LP_THUMB_MOVE_RELOC_ERROR                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义:非Global符号内存申请失败。
 *
 * 值: 0x02001e60
 *
 *解决方案:适当配大LP分区的大小。
 */
#define OS_ERRNO_LP_MEM_ERROR                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x60)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元个数配置的太小
 *
 * 值: 0x02001e61
 *
 *解决方案:增加LP单元的配置个数
 */
#define OS_ERRNO_LP_NUM_TOO_SMALL                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x61)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 6108、6181、6182平台LP使用的内存分区号不能是0,1
 *
 * 值: 0x02001e62
 *
 *解决方案:配置LP使用的内存分区号大于1，小于最大LP分区号
 */
#define OS_ERRNO_LP_MEM_PT_NO_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x62)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态补丁递归调用补丁替换函数call重定位失败。
 *
 * 值: 0x02001e63
 *
 *解决方案:确认LP文件中该符号是否4字节对齐或超过call调用范围。
 */
#define OS_ERRNO_LP_RECUR_CALL_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x63)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP文件类型错误
 *
 * 值: 0x02001e64
 *
 *解决方案:检查TENSILICA平台是否使用了ARM源文件做的补丁或者ARM平台使用了TENSILICA源文件做的补丁
 */
#define OS_ERRNO_LP_ELF_FILETYPE_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x64)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态补丁非递归补丁替换函数call重定位失败。
 *
 * 值: 0x02001e65
 *
 *解决方案:确认基础版本里的该符号是否4字节对齐或超过call调用范围或汇编中的递归调用。
 */
#define OS_ERRNO_LP_NONRECUR_CALL_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x65)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用24位立即数重定位错误。
 *
 * 值: 0x02001e66
 *
 *解决方案:确认ARM指令是否4字节对齐或超过24位立即数调用范围[-32M,32M]。
 */
#define OS_ERRNO_LP_ARM_PC24_OFFECT_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x66)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用22位立即数指令重定位错误。
 *
 * 值: 0x02001e67
 *
 *解决方案:确认Thumb指令是否2字节对齐或超过22位立即数指令调用范围[-16M,16M]。
 */
#define OS_ERRNO_LP_THUMB_CALL_OFFECT_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x67)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用9位立即数指令重定位错误。
 *
 * 值: 0x02001e68
 *
 *解决方案:确认Thumb指令是否2字节对齐或超过8位立即数指令调用范围[-256B,254B]。
 */
#define OS_ERRNO_LP_THUMB_JUMP8_OFFECT_ERROR                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x68)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用11位立即数类指令重定位错误。
 *
 * 值: 0x02001e69
 *
 *解决方案:确认Thumb指令是否2字节对齐或超过11位立即数指令调用范围[-2M,2M]。
 */
#define OS_ERRNO_LP_THUMB_JUMP11_OFFECT_ERROR               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x69)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 符号重定位时并行指令slot0上的L32R指令重定位错误，可能是偏移量大于0x3FFFF，或者偏移量非4字节对齐
 *
 * 值: 0x02001e6a
 *
 *解决方案:查看段配置是否有问题。
 */
#define OS_ERRNO_LP_L32R_64_S0_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 符号重定位时并行指令slot2上的L32R指令重定位错误，可能是偏移量大于0x3FFFF，或者偏移量非4字节对齐
 *
 * 值: 0x02001e6b
 *
 *解决方案:查看段配置是否有问题。
 */
#define OS_ERRNO_LP_L32R_64_S2_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用16位ABS类指令重定位错误。
 *
 * 值: 0x02001e6c
 *
 *解决方案:确认ARM指令是否2字节对齐或超过16位立即数指令调用范围[-16M,16M]。
 */
#define OS_ERRNO_LP_ARM_ABS16_OFFECT_ERROR                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用12位ABS类指令重定位错误。
 *
 * 值: 0x02001e6d
 *
 *解决方案:确认ARM指令是否2字节对齐或超过12位立即数指令调用范围[-2M,2M]。
 */
#define OS_ERRNO_LP_ARM_ABS12_OFFECT_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用8位ABS类指令重定位错误。
 *
 * 值: 0x02001e6e
 *
 *解决方案:确认ARM指令是否2字节对齐或超过8位立即数指令调用范围[-256B,256B]。
 */
#define OS_ERRNO_LP_ARM_ABS8_OFFECT_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 动态加载动态补丁调用5位ABS数类指令重定位错误。
 *
 * 值: 0x02001e6f
 *
 *解决方案:确认Thumb指令是否2字节对齐或超过5位立即数指令调用范围[-32B,32B]。
 */
#define OS_ERRNO_LP_THUMB_ABS5_OFFECT_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6f)


/**
 * @ingroup sre_lp
 * 系统基本功能错误码:LP管理信息组的个数配置错误。
 *
 * 值: 0x02001e70
 *
 * 解决方案: 查看实例内每个核配置的最大LP管理信息组个数是否大于0，而且配置的最大管理信息组个数不能超过254个(Xtensa平台)，CORTEX-AX平台配置为1。
 *
 */
#define OS_ERRNO_LP_MAG_INFO_GROUP_NUM_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x70)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP注册时找不到空闲的LP管理组。
 *
 * 值: 0x02001e71
 *
 *解决方案:排查注册时已经注册的LP管理信息组个数是否已超过配置的LP最大管理信息组个数。
 */
#define OS_ERRNO_LP_REG_NOT_FIND_IDLE_GROUP                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x71)

/**
  * @ingroup sre_lp
  * 多核LP错误码定义: LP管理组ID不可用。
  *
  * 值: 0x02001e72
  *
  *解决方案:查看调用LP接口时入参动态加载及LP管理信息组ID值不能大于等于配置的最大LP管理组个数。
  */
#define OS_ERRNO_LP_GROUP_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x72)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 不同Group间动态补丁或动态加载段与已配置的静态补丁的代码段，共享数据段或私有数据段有配置重叠。
 *
 * 值: 0x02001e73
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查不同Group间动态补丁或动态加载段之间与已配置的静态补丁的代码段，共享数据段或私有数据段是否有配置重叠。
 */
#define OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_SP      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x73)

/**
  * @ingroup sre_lp
  * 多核LP错误码定义: 注册段重叠错误上报钩子函数为空。
  *
  * 值: 0x02001e74
  *
  *解决方案:排查注册段重叠错误上报的钩子函数是否为空。
  */
#define OS_ERRNO_LP_REG_ERRREPORTHOOK_NULL                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x74)



/**
  * @ingroup sre_lp
  * 多核LP错误码定义: LP管理组生效核范围错误。
  *
  * 值: 0x02001e75
  *
  *解决方案:生效核范围不能为0或者与当前运行核范围没有交集。
  */
#define OS_ERRNO_LP_CORE_BIT_MAP_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x75)

/**
  * @ingroup sre_lp
  * 多核LP错误码定义: 静态LP单元号没有按1自增。
  *
  * 值: 0x02001e76
  *
  *解决方案:静态的一个LP文件中，必须按1递增，查看LP文件是否正确。
  */
#define OS_ERRNO_LP_PATNO_INCREASE_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x76)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在一个组内不允许一个共享数据段在多个单元存在。
 *
 * 值: 0x02001e79
 *
 *解决方案:请检查本组的共享数据段是否在多个单元存在。
 */
#define OS_ERRNO_LP_SHARED_SEC_IN_MULTI_UNIT               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x79)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 打补丁的LP组不为符号所在的组。
 *
 * 值: 0x02001e7a
 *
 *解决方案:检查动态补丁源码中的函数是否为其他组的补丁函数。
 */
#define OS_ERRNO_LP_FETCH_DP_GOURP_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 找不到指定镜像ID相应组名的组ID。
 *
 * 值: 0x02001e7b
 *
 *解决方案:检查指定镜像和指定组名的管理组是否完成注册。
 */
#define OS_ERRNO_LP_NOT_FIND_GROUP_ID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 找不到指定组中相应段的段信息。
 *
 * 值: 0x02001e7c
 *
 *解决方案:检查指定的组是否已经注册或者查询的段名是否存在于当前组中。
 */
#define OS_ERRNO_LP_NOT_FIND_GROUP_SECTION_INFO            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 调用SRE_LPUnitDependedLinkGet时发现输入的依赖链uwUnitNumIn的大小为0。
 *
 * 值: 0x02001e7d
 *
 *解决方案:检查输入的uwUnitNumIn是不是为0。
 */
#define OS_ERRNO_LP_DEPEND_LIST_NUM_IS_ZERO                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 调用SRE_LPUnitDependedLinkGet时发现输入的依赖链uwUnitNumIn的大小小于依赖链中的实际大小。
 *
 * 值: 0x02001e7e
 *
 *解决方案:按照用户实际的大小输入依赖链个数。
 */
#define OS_ERRNO_LP_DEPEND_LIST_NUM_IS_LITTLE              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7e)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义:不同Group间动态补丁或动态加载段之间有配置重叠。
 *
 * 值: 0x02001e7f
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查不同Group间动态补丁或动态加载段之间是否有配置重叠。
 */
#define OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7f)


/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 同一个Group内静态补丁单个分区内代码段，共享数据段，私有数据段之间有配置重叠。
 *
 * 值: 0x02001e80
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查静态补丁单个分区内的代码段，共享数据段，私有数据段之间的是否有重叠。
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_AREA          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x80)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 同一个Group内不同静态补丁分区间代码段，共享数据段，私有数据段之间有配置重叠。
 *
 * 值: 0x02001e81
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查同一个Group内不同静态补丁分区间代码段，共享数据段，私有数据段之间的是否有重叠。
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_GROUP          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x81)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 不同Group间静态补丁分区间代码段，共享数据段，私有数据段之间有配置重叠。
 *
 * 值: 0x02001e82
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查不同Group间静态补丁分区间代码段，共享数据段，私有数据段之间的是否有重叠。
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x82)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 不同Group间静态补丁分区间代码段，共享数据段，私有数据段与动态补丁动态加载段有配置重叠。
 *
 * 值: 0x02001e83
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查不同Group间静态补丁分区间代码段，共享数据段，私有数据段与动态补丁动态加载段有配置重叠。
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_DLDP     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x83)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 同一个Group内动态补丁或动态加载段之间有配置重叠。
 *
 * 值: 0x02001e84
 *
 *解决方案:通过SRE_LP_ERRREPORT_HOOK_FUNCPTR钩子查看LP_ERROR_REPORT_INFO检查同一个Group内动态补丁或动态加载段之间是否有配置重叠。
 */
#define OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_SAME_GROUP                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x84)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: DP不能引用其他组DP的符号。
 *
 * 值: 0x02001e85
 *
 *解决方案:检查当前加载的DP是否使用到了其他组DP中的变量或者函数。
 */
#define OS_ERRNO_LP_DP_DEPEND_DP_NOT_SAME_GROUP                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x85)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 共享段地址不可配置为LOCAL L2内存。
 *
 * 值: 0x02001e86
 *
 *解决方案:检查GROUP地址配置是否把共享段地址配置在LOCAL L2内存。
 */
#define OS_ERRNO_LP_SHARE_SECTION_ADDR_IN_LL2                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x86)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: DL不能引用DP的符号，不能依赖DP。
 *
 * 值: 0x02001e87
 *
 *解决方案:检查当前加载的DL是否用到了DP中的变量或者函数。
 */
#define OS_ERRNO_LP_DL_DEPEND_DP                                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x87)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 两个组的共享段配置有重叠或者共享段属性不一致。
 *
 * 值: 0x02001e88
 *
 *解决方案:通过注册SRE_LPErrReportHookAdd查看是哪两个镜像哪两个组哪个共享段配置重叠或者属性不一致。
 */
#define OS_ERRNO_LP_DLDP_SHARE_AREA_OVERLAY_IN_ANOTHER_GROUP        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x88)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 用户配置的生效核范围配置错误。
 *
 * 值: 0x02001e89
 *
 *解决方案:检查生效核bit表中是否有当前平台不存在的核配置为生效核。
 */
#define OS_ERRNO_LP_VALID_CORE_BIT_TAB_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x89)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元激活失败。
 *
 * 值: 0x02001e8a
 *
 *解决方案:检查LP单元激活时状态是否非#UNIT_STATE_DEACTIVATED或者正在激活#UNIT_STATE_ACTIVATING状态。
 */
#define OS_ERRNO_LP_ACTIVE_FAIL                                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元去激活失败。
 *
 * 值: 0x02001e8b
 *
 *解决方案:检查LP单元去激活时状态是否非#UNIT_STATE_ACTIVATED或者正在去激活#UNIT_STATE_DEACTIVATING状态。
 */
#define OS_ERRNO_LP_DEACTIVE_FAIL                                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位时加载了之前未加载过的动态库或者动态补丁。
 *
 * 值: 0x02001e8c
 *
 *解决方案:检查是否加载之前还未加载的动态库或动态补丁。
 */
#define OS_ERRNO_LP_RESET_LOAD_FAIL                                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位还未完成时，非故障核做动态补丁，动态库加载操作。
 *
 * 值: 0x02001e8e
 *
 *解决方案:LP单核复位还未完成时，非故障核不可以做动态补丁，动态库加载操作。
 */
#define OS_ERRNO_LP_RESET_NOT_FETCH                                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位还未完成时，非故障核做动态补丁，动态库激活操作。
 *
 * 值: 0x02001e8f
 *
 *解决方案:LP单核复位还未完成时，非故障核不可以做动态补丁，动态库激活操作。
 */
#define OS_ERRNO_LP_RESET_NOT_ACTIVE                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位还未完成时，有组在做动态补丁，动态库去激活操作。
 *
 * 值: 0x02001e90
 *
 *解决方案:LP单核复位还未完成时，不可以做动态补丁，动态库去激活操作。
 */
#define OS_ERRNO_LP_RESET_NOT_DEACTIVE                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x90)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位还未完成时，有组在做动态补丁，动态库移除操作。
 *
 * 值: 0x02001e91
 *
 *解决方案:LP单核复位还未完成时，不可以做动态补丁，动态库移除操作。
 */
#define OS_ERRNO_LP_RESET_NOT_REMOVE                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x91)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位还未完成时，其他组进行组的注册操作。
 *
 * 值: 0x02001e92
 *
 *解决方案:LP单核复位还未完成时，不可进行不包含故障核的组注册操作。
 */
#define OS_ERRNO_LP_RESET_NOT_GROUP_REG                            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x92)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位还未完成时，有组在做去注册操作。
 *
 * 值: 0x02001e93
 *
 *解决方案:LP单核复位还未完成时，不可进行组的去注册操作。
 */
#define OS_ERRNO_LP_RESET_NOT_GROUP_UNREG                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x93)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位操作时，用来做复位操作的核不是故障核。
 *
 * 值: 0x02001e94
 *
 *解决方案:只能用故障核来做故障核的复位操作。
 */
#define OS_ERRNO_LP_RESET_CORE_ERR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x94)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做注册操作的过程中发生了单核复位。
 *
 * 值: 0x03001e95
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_RESET_CORE_IN_REG                              SRE_ERRNO_OS_FATAL(OS_MID_LP,0x95)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做去注册操作的过程中发生了单核复位。
 *
 * 值: 0x03001e96
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_RESET_CORE_IN_UNREG                            SRE_ERRNO_OS_FATAL(OS_MID_LP,0x96)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做加载操作的过程中发生了单核复位。
 *
 * 值: 0x03001e97
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_RESET_CORE_IN_FETCH                            SRE_ERRNO_OS_FATAL(OS_MID_LP,0x97)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做激活操作的过程中发生了单核复位。
 *
 * 值: 0x03001e98
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_RESET_CORE_IN_ACTIVE                           SRE_ERRNO_OS_FATAL(OS_MID_LP,0x98)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做去激活操作的过程中发生了单核复位。
 *
 * 值: 0x03001e99
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_RESET_CORE_IN_DEACTIVE                         SRE_ERRNO_OS_FATAL(OS_MID_LP,0x99)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做移除操作的过程中发生了单核复位。
 *
 * 值: 0x03001e9a
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_RESET_CORE_IN_REMOVE                           SRE_ERRNO_OS_FATAL(OS_MID_LP,0x9a)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 在做完加载操作还没有做激活操作的过程中发生了单核复位；或者做完去激活还没有做移除的过程中发生了单核复位。
 *
 * 值: 0x03001e9b
 *
 *解决方案:致命错误，做制式复位。
 */
#define OS_ERRNO_LP_CORE_RESET_FAIL                                SRE_ERRNO_OS_FATAL(OS_MID_LP,0x9b)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位时候不能创建之前未存在的组。
 *
 * 值: 0x02001e9c
 *
 *解决方案:检查是否在LP单核复位时候创建了之前未存在的组。
 */
#define OS_ERRNO_LP_RESET_NOT_REG_NEW_GROUP                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9c)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单核复位时候不能激活之前依赖却未加载的组。
 *
 * 值: 0x02001e9d
 *
 *解决方案:检查是否在LP单核复位时候有依赖的组未加载。
 */
#define OS_ERRNO_LP_RESET_ACTIVE_NOT_LOAD_UNIT                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9d)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP加载DP的时候，HOT PATCH TABLE空间不足。
 *
 * 值: 0x02001e9e
 *
 *解决方案:删除一些不使用的补丁，重新加载。
 */
#define OS_ERRNO_LP_HP_TABLE_ALLOC_FAIL                            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9e)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: 需要操作的目的核忙，不能进行动态加载或者卸载操作。
 *
 * 值: 0x02001e9f
 *
 *解决方案:检查是否有在同一个核上有并发的动态加载或者卸载操作。
 */
#define OS_ERRNO_LP_HANDLE_CORE_BUSY                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9f)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: HIDSP指令重定位失败。
 *
 * 值: 0x02001ea0
 *
 *解决方案:检查重定位代码是否有问题。
 */
#define OS_ERRNO_LP_HIDSP_RELOC_FAIL                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa0)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: SD6183的LP模块从NSM空间申请内存失败。
 *
 * 值: 0x02001ea1
 *
 *解决方案:扩大NSM空间内存。
 */
#define OS_ERRNO_LP_NSM_MEM_ALLOC_FAILED                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa1)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: SD6183的LP模块未完成初始化。
 *
 * 值: 0x02001ea2
 *
 *解决方案:初始化未完成前，不能调用补丁接口。
 */
#define OS_ERRNO_LP_INITL_UNFINISH                                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa2)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: DP依赖的DL没有加载。
 *
 * 值: 0x02001ea3
 *
 *解决方案:检查代码中打补丁的动态库是否没有加载，并修改
 */
#define OS_ERRNO_LP_DP_DEPEND_DL_NOT_LOADED                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa3)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: SD6183的从核动态库或动态补丁加载失败。 
 *
 * 值: 0x02001ea4
 *
 *解决方案:通过注册SRE_ErrRegHook看从核返回的具体的错误码。
 */
#define OS_ERRNO_LP_CORE_LOAD_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa4)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义:主核的补丁分区MMU映射最小大小小于8K对齐。
 *
 * 值: 0x02001ea5
 *
 *解决方案:补丁表内存在补丁分区空间中申请，其中存储打补丁时的跳转指令，SD6183指令代码段需最小8K对齐，检查补丁分区对应空间映射大小是否小于8K。
 */
#define OS_ERRNO_LP_INIT_ALIGN_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa5)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义:SD6183平台，动态补丁替换的函数不为被打补丁的动态库所有。
 *
 * 值: 0x02001ea6
 *
 *解决方案:动态补丁只能替换对应的动态库中的函数，不可替换其他动态库函数
 */
#define OS_ERRNO_LP_DP_FUN_REPLACE_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa6)

/**
 * @ingroup sre_lp
 *
 * 日期的结构定义。
 */
typedef struct DATE_STRU
{
    UINT16  uwYear;                     /**< 年，范围1970~2100      */
    UINT8   ucMonth;                    /**< 月，范围1~12           */
    UINT8   ucDate;                     /**< 日，范围1~31           */
} DATE_T;

/**
 * @ingroup sre_lp
 *
 * 时间的结构定义。
 */
typedef struct TIME_STRU
{
    UINT8   ucHour;                     /**< 时，范围0~23           */
    UINT8   ucMinute;                   /**< 分，范围0~59           */
    UINT8   ucSecond;                   /**< 秒，范围0~59           */
    UINT8   ucPadding;                  /**< 保留                   */
} TIME_T;

/**
 * @ingroup sre_lp
 * LP单元状态枚举定义。
 * UNIT_STATE_ACTIVATING   : 正在激活状态。
 * UNIT_STATE_ACTIVATED    : 已经激活状态。
 * UNIT_STATE_DEACTIVATING : 正在去激活状态。
 * UNIT_STATE_DEACTIVATED  : 已经去激活状态。
 * UNIT_STATE_IDLE         : 空闲状态。
 * UNIT_STATE_BUTT         : 非法状态。
 */
typedef enum tagPatchState
{
    UNIT_STATE_ACTIVATED    = 0x01,      /**< 激活状态。       */
    UNIT_STATE_DEACTIVATED  = 0x02,      /**< 去激活状态。     */
    UNIT_STATE_IDLE         = 0x03,      /**< 空闲状态。       */
    UNIT_STATE_ACTIVATING   = 0x04,      /**< 激活过程态。     */
    UNIT_STATE_DEACTIVATING = 0x05,      /**< 去激活过程态。   */
    UNIT_STATE_BUTT                      /**< 非法状态。       */
} LP_UNIT_STATE;

/**
*@ingroup sre_lp
*@brief LP状态存储函数类型定义。
*
*@par 描述:
*LP单元状态存储函数钩子类型定义，在LP加载、去除、运行和去运行时调用该钩子进行LP单元状态的存储。
*@attention 无
*
*@param uwImageId       [IN] 类型#UINT32 ，静态配置的镜像。
*@param uwGroupName     [IN] 类型#UINT32，注册组信息时的组名。
*@param uwUnitNo        [IN] 类型#UINT32，工具端制作LP单元包时，用户指定的单元号。
*@param enUnitState     [IN] 类型#LP_UNIT_STATE，工具端制作LP单元包时，用户指定的单元号。
*
*@retval #SRE_OK 0，成功返回。
*@retval #OS_ERROR -1，成功失败。
*
*@par 依赖:
*sre_lp.h：该函数类型声明所在的头文件
*@since RTOSck V100R002C00
*@see 无。
*/
typedef UINT32 (*SRE_SAVEPATCHSTATE_FUNCPTR)(UINT32 uwImageId, UINT32 uwGroupName, UINT32 uwUnitNo, LP_UNIT_STATE enUnitState);

/**
 * @ingroup sre_lp
 * LP组注册段重叠错误信息上报结构体定义。
 */
typedef struct tagLPErrorReportInfo
{
    UINT32 uwCompImageId;       /* 比较段所属组镜像ID */
    UINT32 uwCompGroupName;     /* 比较段所属组名     */
    CHAR *pcCompLpName;         /* 比较段名，如果静态补丁段名为SP_CODE,SP_SHARED,SP_PRIVATE  */
    UINT32 uwComIndex;          /* 比较的段索引       */
    UINT32 uwCompLpAddr;        /* 比较段起始地址     */
    UINT32 uwCompLpSize;        /* 比较段长度         */
    UINT32 uwOverlayImageId;    /* 重叠段所属组镜像ID */
    UINT32 uwOverlayGroupName;  /* 重叠段所属组名     */
    CHAR  *pcOverlayLpName;     /* 重叠段名，如果静态补丁段名为SP_CODE,SP_SHARED,SP_PRIVATE  */
    UINT32 uwOverLayIndex;      /* 重叠段的段索引     */
    UINT32 uwOverLayLpAddr;     /* 重叠段起始地址     */
    UINT32 uwOverLaySize;       /* 重叠段长度         */
} LP_ERROR_REPORT_INFO;

/**
*@ingroup sre_lp
*@brief 配置段重叠错误信息存储函数类型定义。
*
*@par 描述:
*配置段重叠错误信息存储函数类型定义，方便注册时对段重叠错误的定位。
*@attention 无
*
*@param pstErrorReportInfo     [IN] 类型#LP_ERROR_REPORT_INFO，LP组注册段重叠错误信息上报结构体定义。
*
*@retval VOID。
*
*@par 依赖:
*sre_lp.h：该函数类型声明所在的头文件
*@since RTOSck V100R002C00
*@see 无。
*/
typedef VOID (*SRE_LP_ERRREPORT_HOOK_FUNCPTR)(LP_ERROR_REPORT_INFO *pstErrorReportInfo);

/*
 *@ingroup sre_lp
 *@brief 静态补丁、动态补丁、动态加载所有镜像统一配置信息
*/
typedef struct tagImagePubInfo
{
    UINT32 uwGroupNum;      /**< 用户配置的LP管理信息组的最大组数              */
    UINT32 uwMaxLPUnitNum;  /**< 用户配置的最大单元个数(静态补丁个数 + 动态补丁个数 + 动态加载库个数)    */
    UINT32 uwLPPtNo;        /**< 供LP使用的内存分区号                        */
    UINT32 uwLPPtAddr;      /**< 供LP使用的内存分区起始地址                  */
    UINT32 uwLPPtSize;      /**< 供LP使用的内存分区大小                      */
    UINT32 uwChipType;      /**< 芯片类型,仅SD6181/SD6108/SD6182需要配置该项 */
} LP_PUB_INFO;

/*
 *@ingroup sre_lp
 *@brief 多核SP补丁区信息
*/
typedef struct tagHPAreaInfo
{
    BOOL   bAreaIsShare;         /**< 补丁区是否在共享内存,08/81只有L1是私有内存，82只有Local L2是私有内存 */
    UINT32 uwCodeAreaAddr;       /**< 补丁代码区起始地址         */
    UINT32 uwCodeAreaSize;       /**< 补丁代码区大小             */
    UINT32 uwDataShareAreaAddr;  /**< 补丁共享数据区起始地址     */
    UINT32 uwDataShareAreaSize;  /**< 补丁共享数据区大小         */
    UINT32 uwDataPriAreaAddr;    /**< 补丁私有数据区起始地址     */
    UINT32 uwDataAreaSize;       /**< 补丁数据区大小             */
} LP_SP_AREA_INFO;

/*
 *@ingroup sre_lp
 *@brief 多核LP动态补丁或动态加载段区信息
*/
typedef struct tagDLDPAreaInfo
{
    CHAR  *pcSecName;            /**< 用户配置段的名字，段名字不能重复                    */
    UINT32 uwSecAreaAddr;        /**< 段起始地址，cacheLine对齐（取CPU cacheLine和DSP cacheLine的最大值），代码段的起始地址必须配置在0x40000000以下 */
    UINT32 uwSecAreaSize;        /**< 段大小，单位：byte，要求cacheLine的整数倍           */
    BOOL   bSecShared;           /**< 是否组间共享数据段                                  */
} LP_DL_DP_SEC_INFO;

/**
 * @ingroup sre_lp
 * 单元段信息定义
 */
typedef struct tagLPGroupQueryInfo
{
    UINT32 uwTotalSize;          /**< 段的总大小             */
    UINT32 uwFreeSize;           /**< 段空闲空间的总大小     */
    UINT32 uwMaxAvailableSize;   /**< 段的最大可用大小       */
} LP_SEC_QUERY_INFO;

/**
 * @ingroup sre_lp
 * Load&Patch注册类型枚举定义。
 */
typedef enum tagLPRegType
{
    LP_TYPE_NULL  = 0,           /**< 非法LP类型              */
    LP_TYPE_SP    = 1,           /**< 静态补丁类型            */
    LP_TYPE_DL    = 2,           /**< 动态加载类型            */
    LP_TYPE_DP    = 4,           /**< 动态补丁类型            */
    LP_TYPE_DP_DL = 6,           /**< 动态补丁和动态加载类型  */
} LP_TYPE;

/*
 *@ingroup sre_lp
 *@brief 依赖组信息结构体定义
*/
typedef struct tagLPDependGroupInfo
{
    UINT32 *pstDependGrpNameBuf; /**< 依赖组名字数组          */
    UINT32 DependGrpNum;         /**< 依赖组个数              */
} LP_DEPEND_GROUP_INFO_S;

/*
 *@ingroup sre_lp
 *@brief 依赖单元信息结构体定义
*/
typedef struct tagUnitDependedInfo
{
    UINT32  uwGroupID;           /**< 注册时返回的组ID                       */
    UINT32  uwUnitNo;            /**< 工具端制作LP单元包时，用户指定的单元号 */
} UNIT_DEPENDED_INFO;

/**
 * @ingroup sre_lp
 * LP组注册信息结构体定义。
 */
typedef struct tagLPGroupRegInfo
{
    LP_TYPE enLPType;                      /**< 组支持的类型                  (作用域:动态库(SP)+动态补丁(DP)、动态库(DL)、动态补丁(DP)、静态补丁(SP))               */
    UINT32 uwCoreBitTab;                   /**< 组的生效核范围，BitMap表,每个bit对应一个物理核，生效核不能跨基础bin(仅Xtensa有效)(作用域:动态库+动态补丁、动态库、动态补丁、静态补丁)*/
    UINT32 uwPatMaxFuncNum;                /**< 单元最大函数替换个数          (作用域:静态补丁和动态补丁)                                        */
    UINT32 uwOverTime;                     /**< 多核同步超时时间，单位ms      (仅Xtensa有效)(作用域:静态补丁、动态加载、动态补丁)                */
    UINT32 uwSPDssNum;                     /**< 镜像支持的核的个数，          (仅Xtensa有效)(作用域:静态补丁)                                    */
    UINT32 uwAreaNum;                      /**< 段个数（动态库/动态补丁）或者补丁区个数（静态补丁） (仅Xtensa有效)(作用域:动态库+动态补丁、动态库、动态补丁、静态补丁)*/
    LP_SP_AREA_INFO *pstSPAreaInfo;        /**< 静态补丁的补丁区信息          (仅Xtensa有效)(作用域:静态补丁)                                    */
    LP_DL_DP_SEC_INFO *pstDLDPSecInfo;     /**< 动态库动态补丁的段信息        (仅Xtensa有效)(作用域:动态库+动态补丁、动态库、动态补丁)           */
    UINT32 uwSearchNum;                    /**< 搜索组个数                    (仅Xtensa有效)(作用域:动态库+动态补丁、动态库、动态补丁)           */
    UINT32 *puwSearchLink;                 /**< 搜索链，数组形式，每个元素对应一个组名 (仅Xtensa有效)(作用域:动态库+动态补丁、动态库、动态补丁)  */
} LP_GROUP_REG_INFO;


/**
 * @ingroup sre_lp
 * Load&Patch调测Trace枚举。
 */
typedef enum tagLPLoadTrace
{
    LP_FETCH_ACTIVE_ENTRY  = 0,              /**< osLPUnitFetchActive,接收到主核消息，开始动态加载*/
    LP_MCPU_FETCH_ENTRY    = 1,              /**< osLPMcpuUnitFetchActive,开始主核动态加载*/
    LP_DL_FETCH_ENTRY      = 2,              /**< osLPDLFetch,开始动态库加载*/
    LP_DP_FETCH_ENTRY      = 3,              /**< osLPDPFetch,开始动态补丁加载*/
    LP_DYN_ELF_RELOCA      = 4,              /**< osLPElfFetchRelocate,进入ELF解析及重定位*/
    LP_ALL_CORE_CACHE_INV  = 5,              /**< osLPAllCoreCacheInv,开始所有核无效CACHE*/
    LP_DYN_TBL_TBL_BUILD   = 6,              /**< osLPDynSymTabBuild,开始添加动态符号到符号表*/
    LP_ALL_CORE_SYN_FETCH  = 7,              /**< osLPAllCoreSynFetch,所有核开始同步加载重定位*/
    LP_RELOCA_AND_RELOAD   = 8,              /**< osLPRelocAndReload,进入重定位和段加载流程*/
    LP_MMU_SEC_PROC        = 9,              /**< osLPMmuSecProc,开始段拷贝*/
    LP_INST_RELOCAL        = 10,             /**< osLPSecRelocBuild,开始指令的重定位*/
    LP_SEC_RELOAD          = 11,             /**< osLPReLoad,进行段的cache无效*/
    LP_INST_RELOC_AGAIN    = 12,             /**< osLPHidspRelocAgain,对非基础bin的符号进行再重定位，双向依赖场景*/
    LP_ACTIVE_ENTRY        = 13,             /**< osLPActive,开始动态库激活*/
    LP_DL_EXC_FUN_ENTRY    = 14,             /**< osLPExcFunc,开始动态库出入口函数执行*/
    LP_DP_REPLACE_ENTRY    = 15,             /**< osLPReplacePatch,开始动态库补丁函数替换*/
    LP_DL_EXC_FUN_PROC     = 16,             /**< osLPExcAMPPatch,同步执行出入口函数并返回消息*/
    LP_DP_ROLL_BACK_FUN    = 17,             /**< osLPRollbackFun,回退补丁函数*/
    LP_DP_REPLACE_PATCH_FUN= 18,             /**< osLPReplacePatchFun,替换补丁函数*/
    LP_EXC_USER_FUN_OVER   = 19,             /**< osLPExcPatchFun,动态库出入口函数执行结束*/
    LP_ALL_CORE_FETCH_OVER = 20,             /**< osLPUnitFetchActive,动态库加载激活完成开始发送消息给主核*/
    LP_MCPU_FETCH_OVER     = 21,             /**< osLPMcpuUnitFetchActive,主核动态加载完成*/
    LP_SLAVE_REMOVE_ENTRY  = 22,             /**< osLPSlaveRemove,接收到主核消息，开始动态库卸载*/
    LP_REMOVE_ENTRY        = 23,             /**< osLPRemove,开始动态库卸载*/
    LP_UNIT_ROLLBACK       = 24,             /**< osLPRollback,开始回退动态库或者动态补丁*/
    LP_UNIT_DEACTIVE_START = 25,             /**< osLPDeactiveProc,进入动态去激活流程*/
    LP_UNIT_DEACTIVE_END   = 26,             /**< osLPDeactiveProc,去激活流程完成*/
    LP_ALL_CORE_SYN_REMOVE = 27,             /**< osLPAllCoreSynRemove,进行所有核的动态单元同步移除*/ 
    LP_UNIT_CTRL_FREE      = 28,             /**< osLPUnitSecRollBack,进行单元控制块释放*/
    LP_SLAVE_REMOVE_OVER   = 29,             /**< osLPSlaveRemove,动态库卸载完成开始发送消息给主核*/
    LP_MCPU_REMOVE_OVER    = 30,             /**< osLPMCPURemove,主核动态库卸载完成*/
} LP_TRACE_PHASE;


/**
 *@ingroup sre_lp
 *@brief LP管理组信息注册函数。
 *
 *@par 描述:
 *注册LP组信息函数。
 *@attention
 * <ul>
 * <li>动态加载和动态补丁uwAreaNum的值和pstDLDPSecInfo 中配置的节区个数要一致。</li>
 * <li>静态补丁uwAreaNum的值和pstSPAreaInfo 中配置的补丁区个数要一致。</li>
 * <li>动态加载和动态补丁配置的节区名字不能为空和重复，节区之间也不能重合。</li>
 * <li>静态补丁的补丁区之间不能重合，且需要与工具端保持一致。</li>
 * <li>SD6182/SD6181/SD6108补丁区的代码段或代码节区配置的地址空间不能超过0x40000000地址。否则使用会出问题。</li>
 * <li>接口中镜像ID的正确性需要用户保证，必须是OS_SYS_IMAGE_ID。</li>
 * <li>如果使用动态加载，动态补丁，需要打开符号表裁剪开关。</li>
 * <li>ARM平台只能使用单核动态补丁。</li>
 * <li>动态加载及动态补丁组信息注册时地址不能重叠，而且需要128字节对齐(考虑cache line)，段名字不能重复。</li>
 * <li>注册接口通过uwImageId注册，多次注册如果参数一致返回都SRE_OK，并输出同一个动态加载及动态补丁管理信息组ID。</li>
 * <li>调用注册接口注册成功n次，需要调用清除注册接口n次，最后才真正删除注册信息。</li>
 * </ul>
 *
 *@param uwImageId          [IN] 类型#UINT32 ，镜像ID，一个镜像对应一个基础BIN， 镜像id (SD6182平台[0,16]，SD6181平台[0,19]，SD6108平台[0,12]，AX[0,0])，需要用户保证其正确性。
 *@param uwGroupName        [IN] 类型#UINT32 ，管理信息组名，镜像内唯一，组名0x0预留给基础BIN使用。
 *@param pstGroupInfo       [IN] 类型#LP_GROUP_REG_INFO *，组信息注册指针，组信息，包含段配置、搜索链、生效核等。
 *@param puwGroupID         [OUT]类型#UINT32*，组ID，由注册接口注册后分配，后续的LP加载、激活等操作都将需使用组ID。
 *
 *@retval #OS_ERRNO_LP_6108_6181_DLDP_INVALID              0x02001e10, 6108/6181只支持静态补丁。
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                    0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_INFO_REPEAT_DIFFER                  0x02001e17，重复注册的LP组信息不一致。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_IMAGE_ID_INVALID                    0x02001e2a，镜像ID错误。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                       0x02001e0d，入参为空。
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                      0x02001e0e，LP缓冲区长度不正确。
 *@retval #OS_ERRNO_LP_IDENT_INVALID                       0x02001e20，不是合法的LP文件。
 *@retval #OS_ERRNO_LP_FILE_IS_INVALID                     0x02001e16，LP文件长度不正确。
 *@retval #OS_ERRNO_LP_PACKET_CRC_INVALID                  0x02001e21，LP文件的crc校验失败。
 *@retval #OS_ERRNO_LP_PROTOCOL_VER_INVALID                0x02001e05，LP文件结构变更升级版本号错误。
 *@retval #OS_ERRNO_LP_INCLUDE_OLDFILE_FUNC_UNCOVERED      0x02001e1f，LP加载中，已经加载的补丁单元与再次加载的LP单元不一致。crc校验不通过。
 *@retval #OS_ERRNO_LP_SEC_NAME_SAME                       0x02001e19，动态加载，动态补丁段名配置相同。
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_AREA        0x02001e80，同一个Group内静态补丁单个分区内代码段，共享数据段，私有数据段之间有配置重叠。
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_GROUP       0x02001e81，同一个Group内不同静态补丁分区间代码段，共享数据段，私有数据段之间有配置重叠。
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP    0x02001e82，不同Group间静态补丁分区间代码段，共享数据段，私有数据段之间有配置重叠。
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_DLDP 0x02001e83，不同Group间静态补丁分区间代码段，共享数据段，私有数据段与动态补丁动态加载段有配置重叠。
 *@retval #OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_SAME_GROUP     0x02001e84，同一个Group内动态补丁或动态加载段之间有配置重叠。
 *@retval #OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP  0x02001e7f，不同Group间动态补丁或动态加载段之间有配置重叠。
 *@retval #OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_SP 0x02001e73，不同Group间动态补丁或动态加载段与已配置的静态补丁的代码段，共享数据段或私有数据段有配置重叠。
 *@retval #OS_ERRNO_LP_NOT_INITED                          0x02001e48，LP模块未初始化，没有经过镜像初始化。
 *@retval #OS_ERRNO_LP_HPAREAINFO_IS_NULL                  0x02001e49，静态补丁必须配置补丁区。
 *@retval #OS_ERRNO_LP_DLDPAREAINFO_IS_NULL                0x02001e4a，动态补丁动态加载必须配置段区。
 *@retval #OS_ERRNO_LP_CFG_SEC_INVALID                     0x02001e4b，动态加载动态补丁的段区的起始地址或者长度配置错误。
 *@retval #OS_ERRNO_LP_CFG_SEC_NAME_INVALID                0x02001e4c，动态加载动态补丁的段区的名字不能为空。
 *@retval #OS_ERRNO_LP_GLB_L2_ADDR                         0x02001e53，LOCAL L2地址不允许配置为全局地址。
 *@retval #OS_ERRNO_LP_DEPEND_SYMBOL_INITED                0x02001e55，动态加载，动态补丁需要依赖符号表模块。
 *@retval #OS_ERRNO_LP_REG_NOT_FIND_IDLE_GROUP             0x02001e71，LP注册时找不到补丁空闲的管理组。
 *@retval #OS_ERRNO_LP_REG_FUNC_NUM_INVALID                0x02001e24，LP单元最大函数个数配置为0。
 *@retval #OS_ERRNO_LP_CORE_BIT_MAP_INVALID                0x02001e75，LP管理组生效核范围错误。
 *@retval #OS_ERRNO_LP_CODE_PUT_IN_ANOTHER_1G              0x02001e2f，LP的代码区超过了0x40000000。
 *@retval #OS_ERRNO_LP_CFG_CODE_INVALID                    0x02001e31，静态补丁补丁区的代码段配置错误。
 *@retval #OS_ERRNO_LP_REG_NOT_ALIGN                       0x02001e23，配置的补丁区或段区(起始地址及长度)未按照cache line对齐(SD6181/SD6108为64字节，SD6182为128字节)，或者私有补丁区未按照4字节对齐。
 *@retval #OS_ERRNO_LP_SHARE_SECTION_ADDR_IN_LL2           0x02001e86，共享段地址不可配置为LOCAL L2内存。
 *@retval #OS_ERRNO_LP_DLDP_SHARE_AREA_OVERLAY_IN_ANOTHER_GROUP  0x02001e88，两个组的共享段配置有重叠或者共享段属性不一致。
 *@retval #OS_ERRNO_LP_VALID_CORE_BIT_TAB_ERROR            0x02001e89，用户配置的生效核范围配置错误。
 *@retval #OS_ERRNO_LP_RESET_NOT_GROUP_REG                 0x02001e92，LP单核复位还未完成时，其他组进行组的注册操作。
 *@retval #OS_ERRNO_LP_RESET_CORE_ERR                      0x02001e94，LP单核复位操作时，用来做复位操作的核不是故障核。
 *@retval #OS_ERRNO_LP_RESET_NOT_REG_NEW_GROUP             0x02001e9c，LP单核复位时候不能创建之前未存在的组。
 *@retval #SRE_OK                                          0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoUnReg
 */
extern UINT32 SRE_LPGroupInfoReg(UINT32 uwImageId, UINT32 uwGroupName, LP_GROUP_REG_INFO *pstGroupInfo, UINT32* puwGroupID);

/**
 *@ingroup sre_lp
 *@brief LP管理组信息去注册函数。
 *
 *@par 描述:
 *去注册指定LP管理组ID对应的LP组信息函数。
 *@attention
 * <ul>
 * <li>去注册接口中会检测该LP管理组ID管理的所有LP单元的状态，如果所有LP的都是空闲，才可以清除注册该LP管理组信息。</li>
 * </ul>
 *
 *@param uwGroupID [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                    0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_GROUP_ID_IN_USE                     0x02001e59，LP管理组ID在使用中，不能去注册该补丁信息管理组。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_RESET_NOT_GROUP_UNREG               0x02001e93，LP单核复位还未完成时，有组在做去注册操作。
 *@retval #SRE_OK                                          0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoReg
 */
extern UINT32 SRE_LPGroupInfoUnReg (UINT32 uwGroupID);

/**
 *@ingroup sre_lp
 *@brief 保存LP单元状态的钩子函数注册。
 *
 *@par 描述:
 *将保存LP单元状态的钩子注册到当前镜像中。
 *@attention
 * <ul>
 * <li>每个镜像注册一个LP单元状态保存钩子，用于记录LP操作过程中的LP单元状态。</li>
 * </ul>
 *
 *@param pfnHook [IN]类型#SRE_SAVEPATCHSTATE_FUNCPTR，保存补丁状态的钩子函数类型。
 *
 *@retval #OS_ERRNO_LP_REG_STATESAVEHOOK_NULL            0x02001e29，注册保存补丁状态的钩子函数为空。
 *@retval #OS_ERRNO_LP_NOT_INITED                        0x02001e48，补丁模块未初始化，没有经过镜像初始化。
 *@retval #SRE_OK                                        0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoReg
 */
extern UINT32 SRE_LPUnitStateSaveHookReg(SRE_SAVEPATCHSTATE_FUNCPTR pfnHook);

/**
 *@ingroup sre_lp
 *@brief 动态加载或补丁加载函数。
 *
 *@par 描述:
 *将缓冲区中的LP文件加载到指定LP管理组ID对应的补丁区或者指定的段中。
 *@attention
 * <ul>
 * <li>1、被打补丁函数大小不小于16字节。C语言编译出来的函数已经做了校验，有错误码返回，
 * elf文件不提供汇编语言编译出来的函数大小信息，故无法判断，需用户自行保证，否则系统会出现异常；</li>
 * <li>2、如果补丁单元之间出现符号重名或者有符号引用就会按照加载顺序产生依赖关系；</li>
 * <li>3、支持C递归补丁替换函数的CALL重定位,不支持汇编递归补丁替换函数的CALL重定位,因为汇编函数的符号大小为0。</li>
 * <li>4、ARM平台下补丁文件中使用的全局变量必须赋值或者指定段或者增加-fno-common编译选项，否则补丁加载失败，无法找到符号。</li>
 * </ul>
 *
 *@param uwGroupID      [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param pucBuf         [IN] 类型#UINT8 *，LP单元的加载包的起始地址，该起始地址必须4字节对齐，单元号包含在加载包中。
 *@param uwLength       [IN] 类型#UINT32 ，LP单元的加载包的大小。
 *
 *@retval #OS_ERRNO_LP_BUF_ADDR_NOT_ALIGN                  0x02001e22, 缓冲区地址(pucBuf)非4字节对齐。
 *@retval #OS_ERRNO_LP_SP_FLAG_INVALID                     0x02001e03，静态补丁加载时补丁文件中的标示头不是增量补丁标志。
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                    0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                0x02001e18，指定LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                       0x02001e0d，入参为空。
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                      0x02001e0e，动态加载或补丁缓冲区长度不正确。
 *@retval #OS_ERRNO_LP_IDENT_INVALID                       0x02001e20，不是合法的LP文件。
 *@retval #OS_ERRNO_LP_FILE_IS_INVALID                     0x02001e16，动态加载或LP文件长度不正确。
 *@retval #OS_ERRNO_LP_PACKET_CRC_INVALID                  0x02001e21，动态加载或LP文件的crc校验失败。
 *@retval #OS_ERRNO_LP_PROTOCOL_VER_INVALID                0x02001e05，LP文件结构变更升级版本号错误。
 *@retval #OS_ERRNO_LP_LOADED                              0x02001e06，动态加载或补丁文件重复加载。
 *@retval #OS_ERRNO_LP_INCLUDE_OLDFILE_FUNC_UNCOVERED      0x02001e1f，动态加载或补丁加载中，已经加载的LP单元与再次加载的LP单元不一致。crc校验不通过。
 *@retval #OS_ERRNO_LP_CALL_OFFECT_ERROR                   0x02001e1b，动态加载动态补丁调用非补丁替换函数CALL重定位错误。
 *@retval #OS_ERRNO_LP_REG_FUNC_NUM_INVALID                0x02001e24，LP单元最大函数个数配置为0。
 *@retval #OS_ERRNO_LP_SEC_ALIGN_ERROR                     0x02001e26，ELF段对齐错误。
 *@retval #OS_ERRNO_LP_ITEM_SIZE_ERROR                     0x02001e28，符号表段头中每个符号节点的大小错误。
 *@retval #OS_ERRNO_LP_INST_TYPE_ERROR                     0x02001e46，重定位符号对应的指令类型不支持。
 *@retval #OS_ERRNO_LP_RECUR_CALL_ERROR                    0x02001e63，动态补丁递归调用补丁替换函数call重定位失败。
 *@retval #OS_ERRNO_LP_NONRECUR_CALL_ERROR                 0x02001e65，动态补丁非递归补丁替换函数call重定位失败。
 *@retval #OS_ERRNO_LP_ELF_FILETYPE_ERROR                  0x02001e64，LP文件类型错误。
 *@retval #OS_ERRNO_LP_ARM_PC24_OFFECT_ERROR               0x02001e66，24位立即数跳转指令重定位错误。
 *@retval #OS_ERRNO_LP_THUMB_CALL_OFFECT_ERROR             0x02001e67，22位立即数跳转指令重定位错误。
 *@retval #OS_ERRNO_LP_THUMB_JUMP8_OFFECT_ERROR            0x02001e68，9位立即数跳转指令重定位错误。
 *@retval #OS_ERRNO_LP_THUMB_JUMP11_OFFECT_ERROR           0x02001e69，11位立即数跳转指令重定位错误。
 *@retval #OS_ERRNO_LP_ARM_ABS16_OFFECT_ERROR              0x02001e6c，16位立即数ABS指令重定位错误。
 *@retval #OS_ERRNO_LP_ARM_ABS12_OFFECT_ERROR              0x02001e6d，12位立即数ABS指令重定位错误。
 *@retval #OS_ERRNO_LP_ARM_ABS8_OFFECT_ERROR               0x02001e6e，8位立即数ABS指令重定位错误。
 *@retval #OS_ERRNO_LP_THUMB_ABS5_OFFECT_ERROR             0x02001e6f，5位立即数ABS指令重定位错误。
 *@retval #OS_ERRNO_LP_SEC_INFO_GET_ERROR                  0x02001e41，动态加载或动态补丁加载时获取段信息错误。
 *@retval #OS_ERRNO_LP_FETCH_TYPE_ERROR                    0x02001e43，LP加载时，LP包的类型和核支持的类型不符。
 *@retval #OS_ERRNO_LP_FETCH_DP_GOURP_ERROR                0x02001e7a，打补丁的LP组不为符号所在的组。
 *@retval #OS_ERRNO_LP_CODE_ADDR_NOT_SUIT                  0x02001e07，静态补丁文件中代码段与配置中的代码段不一致。
 *@retval #OS_ERRNO_LP_DATA_ADDR_NOT_SUIT                  0x02001e07，静态补丁文件中数据段与配置中的共享数据段或私有数据段不一致。
 *@retval #OS_ERRNO_LP_SP_NAME_INVALID                     0x02001e04，静态补丁文件的文件名不正确。
 *@retval #OS_ERRNO_LP_CRC_INVALID                         0x02001e02，LP单元crc校验失败。
 *@retval #OS_ERRNO_LP_CODE_PUT_IN_ANOTHER_1G              0x02001e2f，LP的代码区超过了0x40000000。
 *@retval #OS_ERRNO_LP_SP_NOT_LOADED                       0x02001e27，静态补丁中有LP单元没有被加载。
 *@retval #OS_ERRNO_LP_SECTAB_MEM_ERROR                    0x02001e4d，节区表内存申请错误。
 *@retval #OS_ERRNO_LP_SYM_BUILD_ERROR                     0x02001e52，临时符号表生成错误。
 *@retval #OS_ERRNO_LP_FUNC_OVERFLOW                       0x02001e15，静态补丁或者动态补丁加载的补丁函数个数超过了最大的限制。
 *@retval #OS_ERRNO_LP_CODE_OVER_FLOW                      0x02001e12，静态补丁单元代码段开始地址小于补丁区代码段首地址，或者静态补丁单元代码段超出补丁区代码段范围。
 *@retval #OS_ERRNO_LP_DATA_OVER_FLOW                      0x02001e13，静态补丁单元数据段开始地址小于补丁区数据段首地址，或者静态补丁单元数据段超出补丁区数据段范围。
 *@retval #OS_ERRNO_LP_DP_DEPEND_DP_NOT_SAME_GROUP         0x02001e85，DP不能引用其他组DP的符号。
 *@retval #OOS_ERRNO_LP_DL_DEPEND_DP                       0x02001e87，DL不能引用DP的符号，不能依赖DP。
 *@retval #OS_ERRNO_LP_RESET_LOAD_FAIL                     0x02001e8c，LP单核复位时加载了之前未加载过的动态库或者动态补丁。
 *@retval #OS_ERRNO_LP_RESET_NOT_FETCH                     0x02001e8e，LP单核复位还未完成时，非故障核做动态补丁，动态库加载操作。
 *@retval #OS_ERRNO_LP_RESET_CORE_ERR                      0x02001e94，LP单核复位操作时，用来做复位操作的核不是故障核。
 *@retval #SRE_OK                                          0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitRemove
 */
extern UINT32 SRE_LPUnitFetch(UINT32 uwGroupID, UINT8 *pucBuf, UINT32 uwLength);

/**
 *@ingroup sre_lp
 *@brief 动态加载包或补丁移除函数。
 *
 *@par 描述:
 *删除指定LP管理组ID对应的指定补丁或动态加载单元，同时删除依赖于该LP单元号的所有补丁或动态加载单元。
 *@attention
 * <ul>
 * <li>因为删除的(补丁或动态加载)单元没有备份，所以删除失败时已被删除的依赖的单元不会被回退。</li>
 * </ul>
 *
 *@param uwGroupID     [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwUnitNo      [IN] 类型#UINT32 ，工具端制作LP单元包时，用户指定的单元号。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09，动态加载或补丁单元未加载。
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                     0x02001e0f，内存申请失败，LP操作过程中需要动态申请内存。
 *@retval #OS_ERRNO_LP_RESET_NOT_REMOVE                   0x02001e91，LP单核复位还未完成时，有组在做动态补丁，动态库移除操作。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitFetch
 */
extern UINT32 SRE_LPUnitRemove(UINT32 uwGroupID, UINT32 uwUnitNo);

/**
 *@ingroup sre_lp
 *@brief 动态加载或补丁激活函数。
 *
 *@par 描述:
 *激活指定LP管理组ID的指定LP单元，同时激活此LP单元号依赖的所有LP单元。
 *@attention
 * <ul>
 * <li>对于补丁来说激活操作实现函数替换，对于动态加载激活则执行动态加载的入口函数 。</li>
 * </ul>
 *
 *@param uwGroupID     [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwUnitNo      [IN] 类型#UINT32 ，工具端制作LP单元包时，用户指定的单元号，其取值范围[1,9999]。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_NO_INVALID                         0x02001e01，动态加载或补丁单元号错误。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09，动态加载或补丁单元未加载。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，入参为空。
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                     0x02001e0f，内存申请失败，LP操作过程中需要动态申请内存。
 *@retval #OS_ERRNO_LP_IS_ACTIVE                          0x02001e0a，动态加载单元或补丁单元已经处于激活状态。
 *@retval #OS_ERRNO_LP_IS_RUNNING                         0x02001e0b，动态加载单元或补丁单元已经处于运行状态。
 *@retval #OS_ERRNO_LP_ALLOC_COMM_MEM_FAIL                0x02001e1d，同步过程中申请的共享内存失败。
 *@retval #OS_ERRNO_LP_SET_PARA_FAIL                      0x02001e1e，设置同步参数失败。
 *@retval #OS_ERRNO_LP_ACTIVE_FAIL                        0x02001e8a，LP单元激活失败。
 *@retval #OS_ERRNO_LP_RESET_NOT_ACTIVE                   0x02001e8f，LP单核复位还未完成时，非故障核做动态补丁，动态库激活操作。
 *@retval #OS_ERRNO_LP_RESET_CORE_ERR                     0x02001e94，LP单核复位操作时，用来做复位操作的核不是故障核。
 *@retval #OS_ERRNO_LP_RESET_ACTIVE_NOT_LOAD_UNIT         0x02001e9d，LP单核复位时候不能激活之前依赖却未加载的组。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitDeactive
 */
extern UINT32 SRE_LPUnitActive(UINT32 uwGroupID, UINT32 uwUnitNo);

/**
 *@ingroup sre_lp
 *@brief 动态加载或补丁去激活函数。
 *
 *@par 描述:
 *去激活指定LP管理组ID的指定LP单元，同时去激活依赖于该LP单元号的所有LP单元。
 *@attention
 * <ul>
 * <li>对于补丁去激活操作是进行函数替换，对于动态加载去激活则执行动态加载的退出函数。</li>
 * </ul>
 *
 *@param uwGroupID     [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwUnitNo      [IN] 类型#UINT32 ，工具端制作LP单元包时，用户指定的单元号，其取值范围[1, 9999]。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_NO_INVALID                         0x02001e01，动态加载或补丁单元号错误。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09，动态加载或补丁单元未加载。
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                     0x02001e0f，内存申请失败，LP操作过程中需要动态申请内存。
 *@retval #OS_ERRNO_LP_IS_DEACTIVE                        0x02001e0c，动态加载或补丁单元已经处于去激活状态。
 *@retval #OS_ERRNO_LP_IS_RUNNING                         0x02001e0b，动态加载或补丁单元已经处于运行状态。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，入参指针为空。
 *@retval #OS_ERRNO_LP_ALLOC_COMM_MEM_FAIL                0x02001e1d，同步过程中申请的共享内存失败。
 *@retval #OS_ERRNO_LP_SET_PARA_FAIL                      0x02001e1e，设置同步参数失败。
 *@retval #OS_ERRNO_LP_START_SYN_FAIL                     0x02001e1a，同步启动失败。
 *@retval #OS_ERRNO_LP_DEACTIVE_SYN_PHASE_FAIL            0x02001e1c，同步阶段操作失败。
 *@retval #OS_ERRNO_LP_DEACTIVE_FAIL                      0x02001e8b，LP单元去激活失败。
 *@retval #OS_ERRNO_LP_RESET_NOT_DEACTIVE                 0x02001e90，LP单核复位还未完成时，有组在做动态补丁，动态库去激活操作。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitActive
 */
extern UINT32 SRE_LPUnitDeactive(UINT32 uwGroupID, UINT32 uwUnitNo);

/**
 *@ingroup sre_lp
 *@brief 动态加载或动态补丁段信息查询
 *
 *@par 描述:
 *查询指定LP管理组ID中的动态加载或动态补丁段基本信息。
 *@attention
 * <ul>
 * <li>只支持动态加载及动态补丁(DL&DP)。</li>
 * <li>不支持CORTEX-AX平台。</li>
 * </ul>
 *@param uwGroupID      [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param pcSecName      [IN] 类型#CHAR * ，查询的段名。
 *@param pstSecInfo     [OUT] 类型#LP_SEC_QUERY_INFO *，保存段信息查询结果的指针。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_SEC_INFO_QUERY_LP_TYPE_INVALID     0x02001e25，查询动态加载或动态补丁的段信息时指定LP组的LP类型错误。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，入参指针为空。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPSectionInfoGet(UINT32 uwGroupID, CHAR *pcSecName, LP_SEC_QUERY_INFO *pstSecInfo);

/**
 *@ingroup sre_lp
 *@brief 已加载的处于某状态的动态加载包或补丁个数查询函数。
 *
 *@par 描述:
 *查询已加载的指定LP管理组ID中处于某状态动态加载包或补丁单元个数。
 *@attention 无
 *
 *@param uwGroupID     [IN] 类型#UINT32 ，动态加载及补丁管理信息组ID，需要用户保证其正确性。
 *@param enUnitState   [IN] 类型#LP_UNIT_STATE ，单元状态，支持 UNIT_STATE_ACTIVATED(激活)， UNIT_STATE_DEACTIVATED(去激活)。
 *@param puwUnitNum    [OUT] 类型#UINT32 *，查询到的单元数。
 *
 *@retval #[0, 配置的最大LP单元个数]，某LP单元状态最大单元个数，可配置的最大LP单元个数为9999。
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，入参指针为空。
 *@retval #OS_ERRNO_LP_STATE_INVALID                      0x02001e39，输入的LP单元状态不正确。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPGetNumByState(UINT32 uwGroupID, LP_UNIT_STATE enUnitState, UINT32 *puwUnitNum);

/**
 *@ingroup sre_lp
 *@brief 已加载的动态加载单元或补丁单元个数查询函数。
 *
 *@par 描述:
 *查询已加载的指定LP管理组ID中已加载的动态加载单元或补丁单元总个数。
 *@attention 无
 *
 *@param uwGroupID     [IN] 类型#UINT32 ，LP管理组ID，需要用户保证其正确性。
 *@param puwUnitNum    [OUT] 类型#UINT32 *，查询到的单元数。
 *
 *@retval #[0, 配置的最大LP单元个数]，获取补丁单元的个数，可配置的最大LP单元个数为9999。
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，入参指针为空。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPGetTotalNum(UINT32 uwGroupID, UINT32 *puwUnitNum);

/**
 *@ingroup sre_lp
 *@brief 动态加载单元或补丁单元状态查询函数。
 *
 *@par 描述:
 *查询指定LP管理组ID中指定补丁单元或动态加载单元的状态。
 *@attention 无
 *
 *@param uwGroupID     [IN]  类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwUnitNo      [IN]  类型#UINT32， 工具端制作LP单元包时，用户指定的单元号，其取值范围[1,9999]。
 *@param penUnitState  [OUT] 类型#LP_UNIT_STATE *，该单元状态保存指针。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，补丁管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，补丁管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，保存补丁状态的指针为空。
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09，该LP单元未加载。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPGetUnitState(UINT32 uwGroupID, UINT32 uwUnitNo, LP_UNIT_STATE *penUnitState);

/**
 *@ingroup sre_lp
 *@brief 动态加载或补丁的升级版本信息查询函数。
 *
 *@par 描述:
 *查询指定LP管理组ID中的LP协议升级版本信息(这个是工具端制作LP文件时将".o"文件打包成".pat"的协议格式版本，管理段加载".pat"文件时需要匹配该协议格式)。
 *@attention 无
 *
 *@param uwImageID       [IN]  类型#UINT32 ，静态配置的镜像ID，需要用户保证其正确性。
 *@param pucImageVersion [OUT] 类型#UCHAR * 保存版本信息查询结果指针。
 *@param uwLength        [IN] 类型#UINT32 ，保存版本信息大小。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，入参指针为空。
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                     0x02001e0e，缓冲区长度不够。
 *@retval #OS_ERRNO_LP_IMAGE_ID_INVALID                   0x02001e2a，镜像ID错误。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPGetVersion(UINT32 uwImageID, UCHAR *pucImageVersion, UINT32 uwLength);

/**
 *@ingroup sre_lp
 *@brief 静态补丁区代码段使用情况查询。
 *
 *@par 描述:
 *查询指定LP管理组ID中的指定补丁区的代码段使用情况。返回补丁区代码空间的使用长度。
 *@attention
 * <ul>
 * <li>只支持静态补丁(SP)。</li>
 * </ul>
 *
 *@param uwGroupID      [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwPatAreaNo    [IN] 类型#UINT32 ，工具端制作补丁包时，用户指定的补丁区编号。
 *@param puwLen         [OUT] 类型#UINT32 * 查询到的总长度指针。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，长度指针为空。
 *@retval #OS_ERRNO_LP_AREA_NO_INVALID                    0x02001e35，补丁补丁区号错误。
 *@retval #OS_ERRNO_LP_SP_TYPE_ERROR                      0x02001e11，查询加载的代码或数据长度时指定的LP类型不合法。。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGetLoadShareDataLen | SRE_LPGetLoadDataLen
 */
extern UINT32 SRE_LPGetLoadCodeLen(UINT32 uwGroupID, UINT32 uwPatAreaNo, UINT32 *puwLen);

/**
 *@ingroup sre_lp
 *@brief 静态补丁区共享数据段使用情况查询。
 *
 *@par 描述:
 *查询指定补丁管理组ID中的指定补丁区的共享数据段使用情况。返回补丁区共享数据空间的使用长度。
 *@attention
 * <ul>
 * <li>只支持静态补丁(SP)。</li>
 * </ul>
 *
 *@param uwGroupID      [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwPatAreaNo    [IN] 类型#UINT32 ，工具端制作补丁包时，用户指定的补丁区编号。
 *@param puwLen         [OUT] 类型#UINT32 * 查询到的总长度指针。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，长度指针为空。
 *@retval #OS_ERRNO_LP_AREA_NO_INVALID                    0x02001e35，补丁补丁区号错误。
 *@retval #OS_ERRNO_LP_SP_TYPE_ERROR                      0x02001e11，查询加载的代码或数据长度时指定的LP类型不合法。。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGetLoadCodeLen | SRE_LPGetLoadDataLen
 */
extern UINT32 SRE_LPGetLoadShareDataLen(UINT32 uwGroupID, UINT32 uwPatAreaNo, UINT32 *puwLen);

/**
 *@ingroup sre_lp
 *@brief 静态补丁区私有数据段使用情况查询。
 *
 *@par 描述:
 *查询指定LP管理组ID中的指定补丁区的私有数据段使用情况。返回补丁区私有数据空间的使用长度。
 *@attention
 * <ul>
 * <li>只支持静态补丁(SP)。</li>
 * </ul>
 *
 *@param uwGroupID      [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwPatAreaNo    [IN] 类型#UINT32 ，SP补丁区号。
 *@param puwLen         [OUT] 类型#UINT32 * 查询到的总长度指针。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，长度指针为空。
 *@retval #OS_ERRNO_LP_AREA_NO_INVALID                    0x02001e35，SP补丁区号错误。
 *@retval #OS_ERRNO_LP_SP_TYPE_ERROR                      0x02001e11，查询加载的代码或数据长度时指定的LP类型不合法。。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGetLoadCodeLen | SRE_LPGetLoadShareDataLen
 */
extern UINT32 SRE_LPGetLoadDataLen(UINT32 uwGroupID, UINT32 uwPatAreaNo, UINT32 *puwLen);

/**
 *@ingroup sre_lp
 *@brief 动态加载或补丁同步操作时间设置。
 *
 *@par 描述:
 *设置指定LP管理组ID中同步的超时时间（单位：ms）。
 *@attention
 * <ul>
 * <li>如果为配置超时时间为0，则将其设置为默认的超时时间15000ms。</li>
 * </ul>
 *
 *@param uwGroupID      [IN] 类型#UINT32 ，注册时返回的组ID，需要用户保证其正确性。
 *@param uwOverTime     [IN] 类型#UINT32 ，同步超时时间，单位为ms。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，LP管理信息组未被初始化。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPSetOverTime(UINT32 uwGroupID, UINT32 uwOverTime);

/**
 *@ingroup sre_lp
 *@brief 查询LP单元号。
 *
 *@par 描述:
 *获取指定LP文件缓冲区中的LP单元号。
 *
 *@attention
 * <ul>
 * <li>如果是动态加载包或者是动态补丁包，该接口获取该动态加载包或者补丁包对应的LP单元号。</li>
 * <li>如果是静态补丁包则获取该静态补丁包包含的补丁中的最大LP单元号。</li>
 * </ul>
 *
 *@param pucBuf    [IN]  类型#UINT8*，缓冲区地址。
 *@param uwLength  [IN]  类型#UINT32，缓冲区长度（LP文件长度）。
 *@param puwUnitNo [OUT] 类型#UINT32*，单元号。
 *
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d，动态加载或补丁缓冲区为空。
 *@retval #OS_ERRNO_LP_BUF_ADDR_NOT_ALIGN                 0x02001e22, 缓冲区地址(pucBuf)非4字节对齐。
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                     0x02001e0e，动态加载或补丁缓冲区长度不正确。
 *@retval #OS_ERRNO_LP_IDENT_INVALID                      0x02001e20，不是合法的LP文件。
 *@retval #OS_ERRNO_LP_FILE_IS_INVALID                    0x02001e16，动态加载或补丁LP文件长度不正确。
 *@retval #OS_ERRNO_LP_PACKET_CRC_INVALID                 0x02001e21，LP文件的crc校验失败。
 *@retval #OS_ERRNO_LP_CRC_INVALID                        0x02001e02，LP单元crc校验失败。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPGetUnitNo(UINT8* pucBuf, UINT32 uwLength, UINT32* puwUnitNo);

/**
 *@ingroup sre_lp
 *@brief 获取某个状态最近加载的单元号。
 *
 *@par 描述:
 *获取指定动态加载及补丁LP管理信息组ID的某个状态最迟加载的LP单元号。
 *
 *@attention 无
 *
 *@param uwGroupID     [IN] 类型#UINT32，动态加载及补丁LP管理信息组ID。
 *@param enUnitState   [IN] 类型#LP_UNIT_STATE，补丁某一个状态，支持 UNIT_STATE_ACTIVATED(激活)，UNIT_STATE_DEACTIVATED(去激活)。
 *@param puwUnitNo     [OUT] 类型#UINT32*，补丁单元号。
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18，指定的LP管理组未初始化。
 *@retval #OS_ERRNO_LP_STATE_INVALID                      0x02001e39，输入的LP单元状态不正确。
 *@retval #SRE_OK                                         0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPGetLastUnitNo(UINT32 uwGroupID, LP_UNIT_STATE enUnitState, UINT32* puwUnitNo);

/**
 *@ingroup sre_lp
 *@brief  根据组名查询组ID。
 *
 *@par 描述:
 *根据组名查询组ID。
 *
 *@attention 无
 *
 *@param uwImageID     [IN] 类型#UINT32，静态配置的镜像ID。
 *@param uwGroupName   [IN] 类型#UINT32，注册时的组名。
 *@param puwGroupID    [OUT] 类型#UINT32*，查询到的组ID。
 *
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                        0x02001e0d，动态加载或补丁缓冲区为空。
 *@retval #OS_ERRNO_LP_IMAGE_ID_INVALID                     0x02001e2a，镜像ID错误。
 *@retval #OS_ERRNO_LP_NOT_FIND_GROUP_ID                    0x02001e72，找不到指定镜像ID相应组名的组ID。
 *@retval #SRE_OK                                           0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */

extern UINT32 SRE_LPGroupIdGet (UINT32  uwImageID, UINT32  uwGroupName, UINT32  *puwGroupID);

/**
 *@ingroup sre_lp
 *@brief  获取单元的被依赖关系表。
 *
 *@par 描述:
 *查询指定LP组对应的LP外部单元号的被依赖关系表。
 *
 *@attention
 * <ul>
 * <li>依赖链包括自身，依赖链的顺序为从上到下，假设有依赖关系，A被B和C依赖，C被D依赖，则依赖链为DCBA。若存储空间不够，填满后将返回错误码。</li>
 * </ul>
 *
 *@param uwGroupID          [IN]  类型#UINT32 ，注册时返回的组ID。
 *@param uwUnitNo           [IN]  类型#UINT32 ，工具端制作LP单元包时，用户指定的单元号。
 *@param uwUnitNumIn        [IN]  类型#UINT32，依赖链的大小：能够存储的最大单元数。
 *@param astDependedLink[]  [OUT] 类型#UNIT_DEPENDED_INFO ，本单元的被依赖链，数组形式。
 *@param puwUnitNumOut      [OUT] 类型#UINT32* ，总的被依赖数，当依赖链空间不够时，该值将大于uwUnitNumIn。
 *
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                        0x02001e0d，动态加载或动态补丁缓冲区为空。
 *@retval #OS_ERRNO_LP_DEPEND_LIST_NUM_IS_ZERO              0x02001e7d，调用SRE_LPUnitDependedLinkGet时发现输入的依赖链uwUnitNumIn的大小为0。
 *@retval #OS_ERRNO_LP_NO_INVALID                           0x02001e01，动态加载单元号或LP单元号错误。
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                     0x02001e72，LP管理组ID不合法。
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                 0x02001e18，组信息未被初始化。
 *@retval #OS_ERRNO_LP_DEPEND_LIST_NUM_IS_LITTLE            0x02001e7e，输入的依赖链uwUnitNumIn的大小小于真实大小。
 *@retval #OS_ERRNO_LP_NOT_LOADED                           0x02001e09，该LP单元未加载。
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                       0x02001e0f，内存申请失败。
 *@retval #SRE_OK                                           0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see 无
 */
extern UINT32 SRE_LPUnitDependedLinkGet(UINT32 uwGroupID, UINT32 uwUnitNo,  UINT32 uwUnitNumIn, UNIT_DEPENDED_INFO astDependedLink[], UINT32* puwUnitNumOut);

/**
 *@ingroup sre_lp
 *@brief 组注册错误上报钩子函数注册。
 *
 *@par 描述:
 *将组注册错误信息上报给用户。
 *@attention
 * <ul>
 * </ul>
 *
 *@param pfnHook [IN]类型#SRE_LP_ERRREPORT_HOOK_FUNCPTR，保存组注册错误信息上报钩子函数类型。
 *
 *@retval #OS_ERRNO_LP_REG_ERRREPORTHOOK_NULL            0x02001e74，注册保存LP单元状态的钩子函数为空。
 *@retval #OS_ERRNO_LP_NOT_INITED                        0x02001e48，LP模块未初始化，没有经过镜像初始化。
 *@retval #SRE_OK                                        0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoReg
 */
extern UINT32 SRE_LPErrReportHookAdd(SRE_LP_ERRREPORT_HOOK_FUNCPTR pfnHook);

#if(OS_OPTION_LP_CORE_RESET == YES)

/**
 *@ingroup sre_lp
 *@brief 完成复位通知接口。
 *
 *@par 描述:
 *单核复位完成后，调用该接口表示单核复位完成。
 *@attention
 * <ul>
 *<li>调用通知接口，后续针对复位核所在的组进行Fetch/Active操作时，将要求组内所有生效核参与。</li>
 *<li>调用该接口通知OS复位核已经完成重加载（含Fetch/Active）。</li>
 *<li>故障核复位后，重启成功前，不能对故障核进行动态库/动态补丁的恢复操作。在故障核的动态库/动态补丁没有完全恢复前，调用SRE_LPCoreReloadOK，可能导致后续业务运行异常。</li>
 * </ul>
 *
 *@param  无
 *
 *@retval 无
 *
 *@par 依赖:
 *sre_lp.h：该接口声明所在的头文件
 *@since RTOSck V100R002C00
 *@see
 */
extern VOID SRE_LPCoreReloadOk(VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _SRE_LP_H */

/*
 * History: \n
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
