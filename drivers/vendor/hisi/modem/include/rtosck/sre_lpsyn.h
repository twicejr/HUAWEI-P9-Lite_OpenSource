/**
 * @file sre_lpsyn.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：多核同步单元模块h文件。 \n
 */

/**
 * @defgroup SRE_lpsyn LP同步单元
 * @ingroup v_Patch
 */

#ifndef _SRE_LPSYN_H
#define _SRE_LPSYN_H
#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**
 * @ingroup SRE_lpsyn
 *
 * 组内同步单元ID
 */
#define LP_INNER_GROUP_SYNC_UNIT_ID                         0

/**
 * @ingroup SRE_lpsyn
 *
 * LP同步默认超时时间
 */
#define DEFAULT_SYN_OVERTIME                                15000

/**
 * @ingroup SRE_lpsyn
 *
 * LP同步阶段枚举
 */
typedef enum tagLPSyncType
{
    LP_SYNC_TYPE_FETCH     = 0,           /**< 加载阶段            */
    LP_SYNC_TYPE_ACTIVE    = 1,           /**< 激活阶段            */
    LP_SYNC_TYPE_DEACTIVE  = 2,           /**< 去激活阶段          */
} LP_SYNC_TYPE;

/**
 * @ingroup SRE_lpsyn
 *
 * LP同步阶段枚举
 */
typedef enum tagLPsynRegType
{
    LP_SYNC_TYPE_SP    = 1,               /**< 静态补丁类型            */
    LP_SYNC_TYPE_DL    = 2,               /**< 动态加载类型            */
    LP_SYNC_TYPE_DP    = 4                /**< 动态补丁类型            */
} LP_SYNC_UINT_TYPE;

/**
 * @ingroup SRE_lpsyn
 *
 * LP同步信息结构体
 */
typedef struct taglpsyninfo
{   
    UINT32 uwPatchNo;                     /**< 操作的外部单元号           */
    LP_SYNC_UINT_TYPE enUnitType;         /**< 单元类型 DL DP SP          */
    LP_SYNC_TYPE enPhaseType;             /**< 加载阶段 激活 去激活 加载  */
}LP_SYN_INFO_S;

/**
* @ingroup  SRE_lpsyn
* @brief 定义同步消息发送函数类型。
*
* @par 描述:
* 用户通过同步消息发送函数类型定义消息发送钩子函数，LP同步模块调用该类型的钩子函数发送消息进行同步。
*
* @attention 无。
*
* @param  uwCpuMask  [IN] 类型#UINT32，本次同步CPU的bitMap表。
* @param  uwGroupID  [IN] 类型#UINT32，哪个组发起的同步，该信息需要由主核传递给从核。
* @param  enSyncType [IN] 类型#LP_SYNC_TYPE，发送消息的阶段，用于接收消息时针对不同阶段做不同处理。
*
* @retval #SRE_OK  0，消息发送成功。
* @retval 其他，消息发送失败。
* @par 依赖:
* <ul><li>sre_lpsyn.h：该接口声明所在的头文件。</li></ul>
* @since UniDSP V100R001C02
* @see 无。
*/
typedef UINT32 (* SRE_MCSYNMSGHOOK_FUNCPTR)(UINT32 uwCpuMask, UINT32 uwGroupID, LP_SYNC_TYPE enSyncType);

/**
 * @ingroup SRE_lpsyn
 *
 * 同步单元阶段处理函数结构定义。
 */
typedef struct tagMCSynProFunc
{
    OS_VOID_FUNC               pfnNormalHook;          /**< 同步阶段的处理函数     */
    SRE_MCSYNMSGHOOK_FUNCPTR   pfnSendSynMsgHook;      /**< 发送同步消息的钩子函数 */
} MC_SYN_PROFUNC;

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：其它同步单元正在被使用。
 *
 * 值: 0x02002c01
 *
 * 解决方案:在进行同步操作前，确认所有的LP同步都已经退出。
 */
#define OS_ERRNO_LPSYN_STARTSYN_USINGOTHERUNIT             SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x01)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：发送同步消息失败。
 *
 * 值: 0x02002c02
 *
 * 解决方案:请参考用户注册的消息发送接口失败原因的解决方法。
 */
#define OS_ERRNO_LPSYN_STARTSYN_SENDMSGFAIL                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x02)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：输入同步CPU掩码表为NULL。
 *
 * 值: 0x02002c03
 *
 * 解决方案:同步时CPU掩码不能为空。
 */
#define OS_ERRNO_LPSYN_STARTSYN_MASKPTRISNULL              SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x03)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码定义: 当前LP组中没有有效的可以同步的核
 *
 * 值: 0x02002c04
 *
 *解决方案:确保该LP组中配置的有效核是否已经在线，或者查看需要同步的LP组中的生效核范围是否配置为0。
 */
#define OS_ERROR_LPSYN_NO_CORE_IN_THIS_IMAGE               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x04)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：开始同步时超时。
 *
 * 值: 0x02002c05
 *
 * 解决方案:尝试增加同步操作时间。
 */
#define OS_ERRNO_LPSYN_STARTSYN_TIMEOUT                    SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x05)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：没有注册同步消息发送函数。
 *
 * 值: 0x02002c06
 *
 * 解决方案:请注册同步消息发送函数。
 */
#define OS_ERRNO_LPSYN_STARTSYN_SENDFUNCISNULL             SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x06)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：管理组的同步单元没有进入同步状态。
 *
 * 值: 0x02002c08
 *
 * 解决方案:同步失败，重新发起同步或者检查同步消息处理时用户传入的管理组ID是否为需要同步的有效管理组ID。
 */
#define OS_ERRNO_LPSYN_PROCSYN_STATUSINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x08)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：执行同步单元超时。
 *
 * 值: 0x02002c09
 *
 * 解决方案:增加同步超时时间。
 */
#define OS_ERRNO_LPSYN_PROCSYN_TIMEOUT                     SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x09)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：调用该函数的核不是开始同步的核。
 *
 * 值: 0x02002c0a
 *
 * 解决方案:调用该函数和发起该函数必须是同一个核。
 */
#define OS_ERRNO_LPSYN_PROCSYN_VCPUIDINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0a)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步单元没有进入同步状态。
 *
 * 值: 0x02002c0c
 *
 * 解决方案:重新发起同步。
 */
#define OS_ERRNO_LPSYN_ENDSYN_STATUSINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0c)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：结束同步过程超时。
 *
 * 值: 0x02002c0d
 *
 * 解决方案:增加同步超时时间。
 */
#define OS_ERRNO_LPSYN_ENDSYN_TIMEOUT                      SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0d)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：结束同步过程的核不是开始同步的核。
 *
 * 值: 0x02002c0e
 *
 * 解决方案:开始和结束同步必须是同一个核。
 */
#define OS_ERRNO_LPSYN_ENDSYN_VCPUIDINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0e)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：输入同步消息发送函数为NULL。
 *
 * 值: 0x02002c0f
 *
 * 解决方案:同步消息的函数的地址不能为NULL。
 */
#define OS_ERRNO_LPSYN_REGSENDHOOK_HOOKISNULL              SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x0f)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：输入同步单元的ID大于等于同步单元的最大数目。
 *
 * 值: 0x02002c10
 *
 * 解决方案:确认同步单元的ID必须为0。
 */
#define OS_ERRNO_LPSYN_SETARGS_SYNIDINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x10)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步单元没有被注册。
 *
 * 值: 0x02002c11
 *
 * 解决方案:请初始化同步单元。
 */
#define OS_ERRNO_LPSYN_SETARGS_STATUSINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x11)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：输入同步单元的ID大于等于同步单元的最大数目。
 *
 * 值: 0x02002c12
 *
 * 解决方案:同步单元ID必须为0。
 */
#define OS_ERRNO_LPSYN_GETARGS_SYNIDINVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x12)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步单元没有被注册。
 *
 * 值: 0x02002c13
 *
 * 解决方案:请初始化同步单元。
 */
#define OS_ERRNO_LPSYN_GETARGS_STATUSINVALID               SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x13)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：输入的获取参数地址的指针为NULL。
 *
 * 值: 0x02002c14
 *
 * 解决方案:确保输入的指针不能NULL。
 */
#define OS_ERRNO_LPSYN_GETARGS_INPUTADDRISNULL             SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x14)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步模块的ID非法。
 *
 * 值: 0x02002c15
 *
 * 解决方案:排查同步模块管理信息是否被踩。
 */
#define OS_ERRNO_LPSYN_UNIT_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x15)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：主核还没有发起同步。
 *
 * 值: 0x02002c16
 *
 * 解决方案:查看主核是否发起同步。
 */
#define OS_ERRNO_LPSYN_UNIT_RUNNING                        SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x16)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：当前核不在同步器同步的范围。
 *
 * 值: 0x02002c17
 *
 * 解决方案:查看LP组初始化是否成功或者检查当前核处理同步消息时传入的同步管理组ID是否合法。
 */
#define OS_ERRNO_LPSYN_NOT_IN_SYNLIST                      SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x17)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：主核和从核的同步机不匹配，不在同一个同步中。
 *
 * 值: 0x02002c18
 *
 * 解决方案:查看主核和从核同步是否匹配。
 */
#define OS_ERRNO_LPSYN_ALREADY_RESTART                     SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x18)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步器中有错误。
 *
 * 值: 0x02002c19
 *
 * 解决方案:查看整个同步过程是否已经超时。
 */
#define OS_ERRNO_LPSYN_HAS_ERROR                           SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x19)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步信息获取失败。
 *
 * 值: 0x02002c1a
 *
 * 解决方案:查看当前是否在同步过程中，只有同步过程才能获取同步信息。
 */
#define OS_ERRNO_LPSYN_INFO_GET_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x1a)

/**
 * @ingroup SRE_lpsyn
 * 同步单元错误码：同步信息获取接口入参为NULL。
 *
 * 值: 0x02002c1b
 *
 * 解决方案:查看传入存储同步信息的结构体指针是否为NULL。
 */
#define OS_ERRNO_LPSYN_INFO_PARA_IS_NULL                   SRE_ERRNO_OS_ERROR(OS_MID_LP_SYNC,0x1b)

/**
 * @ingroup  SRE_lpsyn
 * @brief 同步消息处理函数。
 *
 * @par 描述:
 * 调用该接口进行同步消息处理。用户接收到同步消息后调用该接口进行同步消息处理
 （同步消息的发送函数为用户提供，通过#SRE_LPRegSynMsgSendHook接口注册到系统中），该接口内部调用同步执行阶段函数。
 *
 * @attention
 * <ul>
 * <li>使用该接口需要锁任务调度 </li>
 * </ul>
 *
 * @param uwGroupID [IN] 类型#UINT32 ，动态加载及补丁管理信息组ID，需要用户保证其正确性。
 * 
 * @retval #OS_ERRNO_LPSYN_UNIT_ERROR                              0x02002c19，同步模块的ID非法。
 * @retval #OS_ERRNO_LPSYN_UNIT_RUNNING                            0x02002c1a，主核还没有发起同步。
 * @retval #OS_ERRNO_LPSYN_NOT_IN_SYNLIST                          0x02002c1b，当前核不在同步器同步的范围。
 * @retval #OS_ERRNO_LPSYN_ALREADY_RESTART                         0x02002c1c，主核和从核的同步机不匹配，不在同一个同步中。
 * @retval #OS_ERRNO_LPSYN_HAS_ERROR                               0x02002c1d，同步器中有错误。
 * @retval #OS_ERRNO_LPSYN_ALREADY_ENDSYN                          0x02002c1e，在主核发起同步时，从核已经进入结束同步的状态。
 * @retval #OS_ERRNO_LPSYN_PROCSYN_STATUSINVALID                   0x02002c0c, 管理组的同步单元没有进入同步状态。
 * @retval #SRE_OK                                                 0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_lpsyn.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_LPRegSynMsgSendHook
 */
extern UINT32 SRE_MCSynProcess(UINT32 uwGroupID);

/**
 * @ingroup  SRE_lpsyn
 * @brief 注册同步消息发送钩子函数的接口。
 *
 * @par 描述:
 * 注册同步消息发送函数的接口，同步消息发送函数由用户根据自己的业务进行定义。
 *
 * @attention
 * <ul>
 * <li>如果一个进程需要发起同步，必须先使用该接口注册同步消息发送函数。</li>
 * <li>不支持在LP操作过程中注册修改同步消息发送函数。</li>
 * <li>发送同步消息钩子镜像内唯一，镜像内各组使用同一钩子。</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#SRE_MCSYNMSGHOOK_FUNCPTR，同步消息发送函数指针。
 *
 * @retval #OS_ERRNO_LPSYN_REGSENDHOOK_HOOKISNULL                  0x02002c13，输入同步消息发送函数为NULL。
 * @retval #SRE_OK                                                 0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_lpsyn.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MCSynProcess
 */
extern UINT32 SRE_LPRegSynMsgSendHook(SRE_MCSYNMSGHOOK_FUNCPTR pfnHook);

#if (OS_OPTION_LP_SYN_INFO_GET == YES)

/**
 * @ingroup  SRE_lpsyn
 * @brief 获取同步信息接口。
 *
 * @par 描述:
 * 在用户接收到同步消息后，调用该接口获取当前同步状态。
 *
 * @attention
 * <ul>
 * <li>该接口必须在同步的时候调用，否则会返回错误码。</li>
 * <li>改接口建议在接收到同步消息后调用。</li>
 * </ul>
 *
 * @param uwGroupID  [IN] 类型#UINT32 ，动态加载及补丁管理信息组ID，需要用户保证其正确性。
 * @param pstSynInfo [OUT] 类型#LP_SYN_INFO_S ，同步块信息结构体。
 *
 * @retval #OS_ERRNO_LPSYN_INFO_GET_ERROR                          0x02002c1a，同步信息获取失败。
 * @retval #OS_ERRNO_LPSYN_INFO_PARA_IS_NULL                       0x02002c1b，同步信息获取接口入参为NULL。
 * @retval #SRE_OK                                                 0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_lpsyn.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MCSynProcess
 */
extern UINT32 SRE_LpSynInfoGet(UINT32 uwGroupID, LP_SYN_INFO_S *pstSynInfo);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_LPSYN_H */

/*
 * History: \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

