/**
 * @file sre_trace.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：系统模块的对外头文件。 \n
 */


/** @defgroup SRE_trace 系统跟踪
 *@ingroup SRE_inspect
 */

#ifndef _SRE_TRACE_H
#define _SRE_TRACE_H

#include "sre_base.h"
#include "sre_mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//支持功能宏裁剪,sre_buildef.h文件中支持的功能宏
#if (OS_OPTION_TRACE == YES) 

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：用户配置的系统跟踪区域首地址为空或16字节不对齐。
 *
 * 值: 0x02002501
 *
 * 解决方案: 系统跟踪区域首地址配置为非空且16字节对齐。
 */
#define OS_ERRNO_TRACE_INIT_PARA_ADDR_ERR                                   SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x01)

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：用户配置的系统跟踪区域大小除去控制头的大小OS_TRACE_HEAD_SIZE后，小于等于0或不为2的N次幂。
 *
 * 值: 0x02002502
 *
 * 解决方案: 系统跟踪区域大小除去控制头的大小OS_TRACE_HEAD_SIZE后应大于16且为2的N次幂。
 */
#define OS_ERRNO_TRACE_INIT_PARA_SIZE_ERR                                   SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x02)

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：非法的事件类型。
 *
 * 值: 0x02002505
 *
 * 解决方案: 配置为合法的事件类型, 如OS_TRACE_TYPE_TSK，OS_TRACE_TYPE_SEM等。
 */
#define OS_ERRNO_TRACE_TYPE_ERR                                             SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x05)

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：用户入参无效, 空指针。
 *
 * 值: 0x02002506
 *
 * 解决方案: 传入非空的指针。
 */
#define OS_ERRNO_TRACE_PARA_INVALID                                         SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x06)

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：事件ID非法。
 *
 * 值: 0x02002507
 *
 * 解决方案: 用户主动上报系统跟踪时，传入的事件ID大于等于OS_TRACE_USRERR。
 */
#define OS_ERRNO_TRACE_EVTID_INVALID                                        SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x07)

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：中断号非法。
 *
 * 值: 0x02002509
 *
 * 解决方案: 使能中断的系统跟踪时，配置合法的硬中断号或软中断PID，具体参考硬中断或软中断的介绍。
 */
#define OS_ERRNO_TRACE_INTNUM_INVALID                                       SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x09)

/**
 * @ingroup SRE_trace
 * 系统跟踪错误码：系统跟踪模块没有初始化。
 *
 * 值: 0x0200250C
 *
 * 解决方案: 打开系统跟踪模块剪裁开关，对应配置项OS_TRACE_INCLUDE。
 */
#define OS_ERRNO_TRACE_UNINITED                                             SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x0C)

/**
 * @ingroup SRE_trace
 * 系统跟踪控制头大小
 *
 */
#define OS_TRACE_HEAD_SIZE                                                  sizeof(OS_TRACE_OBJ_S)

/**
 * @ingroup SRE_trace
 * 系统跟踪控制信息结构体
 *
 */
typedef struct tagTraceObj
{
    UINT32 uwSeqID;         /**<  下一条系统跟踪记录的序列号*/
    UINT32 uwIdxMask;       /**<  序列号掩码, 值为缓冲区最大日志数-1, 因此缓冲区大小需要为2的N次幂, 且不小于16        */
    UINT32 uwRsv1;          /**<  硬件平台|cpu类型|核号|魔数字  */
    UINT32 uwRsv2;          /**<  保留位        */
} OS_TRACE_OBJ_S;

/**
 * @ingroup SRE_trace
 * 系统跟踪日志信息结构体
 *
 */
typedef struct tagTraceEvent
{
    UINT32 uwTSL32;        /**<  CPU cycle的低32位  */
    UINT32 uwEvtID;        /**<  事件ID        */
    UINT32 uwPara1;        /**<  参数1         */
    UINT32 uwPara2;        /**<  参数2         */
} OS_TRACE_EVENT_S;

/**
* @ingroup  SRE_trace
*
* 设置TRACE模块的配置信息。
*/
typedef struct tagTraceModInfo
{
    UINT32 uwTraceBufAddr;       /**<系统跟踪空间起始地址, 按16字节对齐*/
    UINT32 uwTraceBufSize;       /**<系统跟踪空间大小,含控制头,扣除控制头大小应为2的N次幂且不小于16*/
} TRACE_MOD_INFO_S;

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 硬中断开始事件，记录的信息包括：事件ID，CPU cycle的低32位，硬中断号。
 */
#define OS_TRACE_HWI_BEGIN                                        1

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 硬中断结束事件，记录的信息包括：事件ID，CPU cycle的低32位，硬中断号。
 */
#define OS_TRACE_HWI_END                                          2

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 软中断开始事件，记录的信息包括：事件ID，CPU cycle的低32位，软中断PID。
 */
#define OS_TRACE_SWI_BEGIN                                        3

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 软中断结束事件，记录的信息包括：事件ID，CPU cycle的低32位，软中断PID。
 */
#define OS_TRACE_SWI_END                                          4


/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 任务切出事件，记录的信息包括：事件ID，CPU cycle的低32位，任务PID，任务状态。
 * #OS_TRACE_TSKOUT和#OS_TRACE_TSKIN事件是合为一条
 * 信息进行记录的，在工具端解析时，会把它还原成两条信息。
 */
#define OS_TRACE_TSKOUT                                           7

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 任务切入事件，记录的信息包括：事件ID，CPU cycle的低32位，任务PID，任务状态。
 * #OS_TRACE_TSKOUT和#OS_TRACE_TSKIN事件是合为一条信息进行记录
 * 的，在工具端解析时，会把它还原成两条信息。
 */
#define OS_TRACE_TSKIN                                            8

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 信号量POST事件，记录的信息包括：事件ID，CPU cycle的低32位，信号量ID，信号量的计数值。
 */
#define OS_TRACE_SEMPOST                                          9

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 致命错误事件，记录的信息包括：事件ID，错误码。
 */
#define OS_TRACE_FATAL_ERR                                        10
/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 异常事件，记录的信息包括：事件ID，CPU cycle的低32位，异常时CPU cycle的高32位和低32位。
 */
#define OS_TRACE_EXCEPTION                                        11

/**
 * @ingroup SRE_trace
 * 系统跟踪事件ID: 用户自定义事件。ID从0x100开始， 0x100以下为OS的事件ID。记录的信息包括：事件ID，CPU cycle的低32位，用户指定的参数值。
 */
#define OS_TRACE_USRERR                                           0x100

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 硬中断，包含#OS_TRACE_HWI_BEGIN和#OS_TRACE_HWI_END事件。
 */
#define OS_TRACE_TYPE_HWI                                         0x1

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 软中断，包含#OS_TRACE_SWI_BEGIN和#OS_TRACE_SWI_END事件。
 */
#define OS_TRACE_TYPE_SWI                                         0x2

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 任务，包含#OS_TRACE_TSKOUT和#OS_TRACE_TSKIN事件。
 */
#define OS_TRACE_TYPE_TSK                                         0x4

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 信号量，包含#OS_TRACE_SEMPOST事件。
 */
#define OS_TRACE_TYPE_SEM                                         0x8

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 致命错误，包含#OS_TRACE_FATAL_ERR事件。
 */
#define OS_TRACE_TYPE_FATAL_ERR                                   0x10

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 异常，包含#OS_TRACE_EXCEPTION事件。
 */
#define OS_TRACE_TYPE_EXC                                         0x20

/**
 * @ingroup SRE_trace
 * 系统跟踪事件类型: 所有事件，不包括用户事件。
 */
#define OS_TRACE_TYPE_ALL                                         0xffffffff

/**
 * @ingroup SRE_trace
 * 系统跟踪中断号: 所有软中断或硬中断。
 */
#define OS_TRACE_INT_ALL                                          0xffffffff

/**
* @ingroup  SRE_trace
* @brief 使能系统跟踪。
*
* @par 描述:
* 使能指定事件类型的系统跟踪。
*
* @attention
* <ul>
* <li>使能系统跟踪的事件类型若为中断，如果该中断没有创建，仍可以跟踪该中断。</li>
* <li>使能系统跟踪的事件类型若为任务，如果该任务没有创建，仍可以跟踪该任务。</li>
* </ul>
*
* @param  uwEvtType      [IN]   类型#UINT32，事件类型， 取值范围:#OS_TRACE_TYPE_HWI， #OS_TRACE_TYPE_SWI，#OS_TRACE_TYPE_TSK，
                                #OS_TRACE_TYPE_SEM， #OS_TRACE_TYPE_FATAL_ERR，#OS_TRACE_TYPE_EXC，#OS_TRACE_TYPE_ALL
* @param  uwParam        [IN]   类型#UINT32，硬中断号或软中断ID， OS_TRACE_INT_ALL表示所有硬中断或软中断，
                                若uwEvtType为信号量，任务，致命错误，异常等事件类型，该参数无意义
*
* @retval #OS_ERRNO_TRACE_UNINITED             0x0200250C，系统跟踪模块没有初始化。
* @retval #OS_ERRNO_TRACE_TYPE_ERR             0x02002505，事件类型非法。
* @retval #OS_ERRNO_TRACE_INTNUM_INVALID       0x02002509，中断号非法。
* @retval #SRE_OK                              0x00000000，使能系统跟踪成功。
* @par 依赖:
* <ul><li>sre_trace.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see SRE_SysTraceDisable
*/
extern UINT32 SRE_SysTraceEnable(UINT32 uwEvtType, UINT32 uwParam);

/**
* @ingroup  SRE_trace
* @brief 取消系统跟踪。
*
* @par 描述:
* 取消指定事件类型的系统跟踪。
*
* @attention
* <ul>
* <li>若指定的中断(硬中断、软中断)并没有使能系统跟踪，仍可以取消其系统跟踪。</li>
* </ul>
*
* @param  uwEvtType      [IN]   类型#UINT32，事件类型， 取值范围:#OS_TRACE_TYPE_HWI， #OS_TRACE_TYPE_SWI，#OS_TRACE_TYPE_TSK，
                                #OS_TRACE_TYPE_SEM， #OS_TRACE_TYPE_FATAL_ERR，#OS_TRACE_TYPE_EXC，#OS_TRACE_TYPE_ALL。
* @param  uwParam        [IN]   类型#UINT32，硬中断号或软中断ID， OS_TRACE_INT_ALL表示所有硬中断或软中断，
*                               若uwEvtType为信号量，任务，致命错误，异常等事件类型， 该参数无意义。
*
* @retval #OS_ERRNO_TRACE_UNINITED             0x0200250C，系统跟踪模块没有初始化。
* @retval #OS_ERRNO_TRACE_TYPE_ERR             0x02002505，事件类型非法。
* @retval #OS_ERRNO_TRACE_INTNUM_INVALID       0x02002509，中断号非法。
* @retval #SRE_OK                              0x00000000，取消系统跟踪成功。
* @par 依赖:
* <ul><li>sre_trace.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see SRE_SysTraceEnable
*/
extern UINT32 SRE_SysTraceDisable(UINT32 uwEvtType, UINT32 uwParam);

/**
* @ingroup  SRE_trace
* @brief 上报自定义系统跟踪事件。
*
* @par 描述:
* 上报一条自定义系统跟踪事件。
*
* @attention
* <ul>
* <li>用户事件ID应大于等于#OS_TRACE_USRERR。</li>
* </ul>
*
* @param  pstTraceEvt      [IN]   类型#OS_TRACE_EVENT_S *，指向待上报的系统跟踪事件。
*                                 其中：uwTSL32忽略用户值，由OS重填， uwEvtID为用户的事件ID，uwPara1和uwPara2为用户自定义的数据信息 。
*
* @retval #OS_ERRNO_TRACE_UNINITED              0x0200250C，系统跟踪模块没有初始化。
* @retval #OS_ERRNO_TRACE_EVTID_INVALID         0x02002507，事件ID非法。
* @retval #OS_ERRNO_TRACE_PARA_INVALID          0x02002506，用户入参无效， 空指针等。
* @retval #SRE_OK                               0x00000000，上报系统跟踪事件成功。
* @par 依赖:
* <ul><li>sre_trace.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see 无
*/
extern UINT32 SRE_TraceReport(OS_TRACE_EVENT_S *pstTraceEvt);

#endif //if (OS_OPTION_TRACE == YES) 

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_TRACE_H */



