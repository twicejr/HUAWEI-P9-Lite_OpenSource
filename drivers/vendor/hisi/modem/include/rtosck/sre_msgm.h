/**
 * @file sre_msgm.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：MSGM模块的对外头文件。 \n
 */

/**
*@defgroup  SRE_msgm  MSGM消息管理
*@ingroup SRE_comm
*/
#ifndef _SRE_MSGM_H
#define _SRE_MSGM_H

#include "sre_base.h"
#include "sre_msg.h"
#include "sre_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP) )

/**
 * @ingroup SRE_msgm
 * MSGQ的第一个QPORT。
 */
#define SRE_QPORT_ID_0        0

/**
 * @ingroup SRE_msgm
 * MSGQ的第二个QPORT。
 */
#define SRE_QPORT_ID_1        1

/**
 * @ingroup SRE_msgm
 * MSGQ的第三个QPORT，仅HACCC核有该QPORT。
 */
#define SRE_QPORT_ID_2        2

/**
 * @ingroup SRE_msgm
 * 全局MSGM标识。
 */
#define SRE_GLOBAL_MSGM       0

/**
 * @ingroup SRE_msgm
 * 局部MSGM标识。
 */
#define SRE_LOCAL_MSGM        1

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：多核消息驱动初始化过程中，MSGM通道无响应，或者核接收状态为完成，需判断下是否是总线挂死。
 *
 * 值: 0x02002b01
 *
 * 解决方案: 需要硬件确认一下MSGQ_RESP_STATUS寄存器状态长时间不为0，或者MSGM_NOR_CORE_STATE长时间不为1的问题。
 *
 */
#define OS_ERRNO_MSGM_INIT_MSGQ_NORESP                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x01)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置QPORT的队列深度时，输入的PORT ID非法。
 *
 * 值: 0x02002b02
 *
 * 解决方案: QPORT ID取值范围: dsp:0-1;cpu:0-1;haccc:0-2。
 *
 */
#define OS_ERRNO_MSGM_QDEP_QORTID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x02)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置QPORT的队列深度时，输入的QUEUE ID非法。
 *
 * 值: 0x02002b03
 *
 * 解决方案: QUEUE ID取值范围: 0-1。
 *
 */
#define OS_ERRNO_MSGM_QDEP_QUEID_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x03)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置QPORT的队列深度时，输入的队列深度非法。
 *
 * 值: 0x02002b04
 *
 * 解决方案: 队列深度必须是非0值，且GLBAL MSGM不能超过SD6182/SD6157:2048，SD6183:8192，LOCAL MSGM不能超过SD6182/SD6157:1024，SD6183:2048。
 *
 */
#define OS_ERRNO_MSGM_QDEP_QDEPTH_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x04)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置QPORT的队列深度时，队列处于使能状态。
 *
 * 值: 0x02002b05
 *
 * 解决方案: QPORT只支持在队列处于去使能的状态下进行配置。
 *
 */
#define OS_ERRNO_MSGM_QDEP_QUEEN_WRONG                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x05)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：发送Qport消息时，消息地址非法。
 *
 * 值: 0x02002b07
 *
 * 解决方案: 为了避免与ECC混淆，QPort消息不能使用全F数据。
 *
 */
#define OS_ERROR_MSGM_QPORT_SEND_DATA_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x07)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：注册qport消息钩子时，传入的tag值非法。
 *
 * 值: 0x02002b08
 *
 * 解决方案: tag值有效取值范围：1~7，对应于128bit消息中第4个WORD的低3bit。
 *
 */
#define OS_ERRNO_MSGM_QHOOK_TAG_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x08)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：发送Qport普通消息时，输入地址指针为空。
 *
 * 值: 0x02002b09
 *
 * 解决方案: 地址指针不能为空。
 *
 */
#define OS_ERRNO_MSGM_SEND_ADDR_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x09)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：发送Qport消息时，消息地址为空
 *
 * 值: 0x02002b0a
 *
 * 解决方案: 需要合法的消息体地址，以便进行消息发送。
 *
 */
#define OS_ERROR_MSGM_QPORT_SEND_DATA_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0a)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：从QPort收到的数据有不可纠ECC错误。
 *
 * 值: 0x02002b0b
 *
 * 解决方案: 无。
 *
 */
#define OS_ERROR_MSGM_QPORT_RECV_SER                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0b)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：接收Qport消息时，消息体地址无效。
 *
 * 值: 0x02002b0c
 *
 * 解决方案: 需要合法的消息体地址，以便保存接收消息。
 *
 */
#define OS_ERROR_MSGM_QPORT_RECV_DATA_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0c)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：该MSGQ上无消息。
 *
 * 值: 0x02002b0d
 *
 * 解决方案: 检查该MSGQ所对应的MSGM队列上是否有数据发送出来或者MSGQ上消息已经全部都接受完。
 *
 */
#define OS_ERRNO_MSGM_RECV_QORT_EMPTY                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0d)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：从指定的MSGQ上接收消息时，指定的QPORT ID非法。
 *
 * 值: 0x02002b0e
 *
 * 解决方案: QPORT ID取值范围: dsp:0-1;cpu:0-1;haccc:0-2。
 *
 */
#define OS_ERRNO_MSGM_RECV_QID_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0e)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：使用MSGM队列发送消息时，指定的目的核非法。
 *
 * 值: 0x02002b0f
 *
 * 解决方案: 指定的目的核必须是实际存在的核号或者目的核还没有启动完成，若设置消息白名单，则目的核需要在白名单内。
 *
 */
#define OS_ERRNO_MSGM_SEND_DSTCORE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0f)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：使用MSGM队列发送消息时，指定的QPORT ID非法。
 *
 * 值: 0x02002b10
 *
 * 解决方案: QPORT ID取值范围: dsp:0-1;cpu:0-1;haccc:0-2。
 *
 */
#define OS_ERRNO_MSGM_SEND_PORTID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x10)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：使用MSGM队列发送消息时，指定的QUEUE ID非法。
 *
 * 值: 0x02002b11
 *
 * 解决方案: QUEUE ID只能为0或1。
 *
 */
#define OS_ERRNO_MSGM_SEND_QUEUEID_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x11)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在使用组装os消息类型的消息组装接口时，指定的目的线程非法。
 *
 * 值: 0x02002b13
 *
 * 解决方案: 不允许发送给os固定占用的线程(idle任务，idle软中断，tick软中断)，且必须是已创建的有效线程号，若设置消息白名单，则目的核需要在白名单内。
 *
 */
#define OS_ERRNO_MSGM_PID_INVALID                               SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x13)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：收到未注册钩子函数的消息。
 *。
 * 值: 0x02002b14
 *
 * 解决方案: 用户在发送消息数据时，检查发送数据的合法性，保证发送过去的数据Tag值所对应的钩子函数已经注册过。
 *
 */
#define OS_ERRNO_MSGM_QHOOK_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x14)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在使用组装os消息类型的消息组装接口时，待创建消息数据的指针为空。
 *
 * 值: 0x02002b15
 *
 * 解决方案: 在使用组装os消息类型的消息组装接口时，待创建消息数据的指针不能为空。
 *
 */
#define OS_ERRNO_MSGM_MSG_POINT_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x15)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的MSGM的ID值不合法。
 *
 * 值: 0x02002b16
 *
 * 解决方案: 请确保MSGM的ID值为SRE_GLOBAL_MSGM或SRE_LOCAL_MSGM(SRE_LOCAL_MSGM对SD6182/SD6183有效)。
 *
 */
#define OS_ERRNO_MSGM_ID_ILLEGAL                                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x16)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的TRACE缓冲区起始地址未256bit对齐。
 *
 * 值: 0x02002b17
 *
 * 解决方案: 请确保传入的TRACE缓冲区起始地址按照256bit进行对齐。
 *
 */
#define OS_ERRNO_MSGM_TRACE_BUFFER_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x17)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的TRACE缓冲区大小未256bit对齐。
 *
 * 值: 0x02002b18
 *
 * 解决方案: 请确保传入的TRACE缓冲区大小按照256bit进行对齐。
 *
 */
#define OS_ERRNO_MSGM_TRACE_SIZE_NOT_ALIGN                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x18)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的TRACE缓冲区起始地址为NULL。
 *
 * 值: 0x02002b19
 *
 * 解决方案: 请确保传入的TRACE缓冲区起始地址不为NULL。
 *
 */
#define OS_ERRNO_MSGM_TRACE_BUFFER_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x19)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：MSGM的TRACE缓冲区起始地址未进行配置。
 *
 * 值: 0x02002b1a
 *
 * 解决方案: 使用TRACE使能接口前，请确认缓冲区起始地址是否已经配置过。
 *
 */
#define OS_ERRNO_MSGM_TRACE_NOT_CONFIG                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1a)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：MSGM的TRACE功能已使能，此时禁止用户进行配置。
 *
 * 值: 0x02002b1b
 *
 * 解决方案: 请确保配置时，TRACE功能处于未使能状态。
 *
 */
#define OS_ERRNO_MSGM_TRACE_ENABLE                              SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1b)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的TRACE缓冲区大小为0或缓冲区大小太大导致溢出。
 *
 * 值: 0x02002b1c
 *
 * 解决方案: 请确保配置时，TRACE缓冲区大小不为0或大小合适，不导致溢出现象。
 *
 */
#define OS_ERRNO_MSGM_TRACE_SIZE_ILLEGAL                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1c)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：MSGM的TRACE匹配码或掩码首地址为NULL。
 *
 * 值: 0x02002b1d
 *
 * 解决方案: 请确保配置时，MSGM的TRACE匹配码或掩码首地址不为NULL。
 *
 */
#define OS_ERRNO_MSGM_TRACE_FILTERBIT_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_MSG, 0x1D)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：用户传入获取当前消息的指针为NULL。
 *
 * 值: 0x02002b1e
 *
 * 解决方案: 请确保传入的获取当前消息的指针不为NULL。
 *
 */
#define OS_ERRNO_MSGM_TRACE_PTR_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1e)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：MSGM Profiling 缓冲区起始地址非空时，配置MSGM Profiling缓冲区的起始地址及长度不合法。
 *
 * 值: 0x02002b1f
 *
 * 解决方案: 检查MSGM Profiling 缓冲区起始地址向上16字节对齐以及缓冲区长度向下16字节对齐后，Profiling 缓冲区起始地址应该小于结束地址。
 *
 */
#define OS_ERRNO_MSGM_PROFILING_CONFIG_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1f)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在调用SRE_QportMsgCreate接口组装消息时，传入的消息句柄非法（错误或已删除或句柄指针为NULL），或者消息正在被使用。
 *
 * 值: 0x02002b21
 *
 * 解决方案: 检查该消息是否只发送一次或者是否正在使用中(长消息处于已组装状态)；检查传入的消息句柄是否正确(确保是采用SRE_MsgAlloc接口申请返回的消息句柄且没有被删除)。
 *
 */
#define OS_ERRNO_MSGM_MSG_CREATE_HANDLE_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x21)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：设置MSGM队列深度时，MSGM没有初始化。
 *
 * 值: 0x02002b22
 *
 * 解决方案: 当前核的MSGM初始化完成后再设置MSGM队列深度。
 *
 */
#define OS_ERRNO_MSGM_NOT_INITED                                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x22)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：进行共享消息队列收发等操作时，传入的handle非法。
 *
 * 值: 0x02002b23
 *
 * 解决方案: 确认该handle是否是在共享消息队列打开时获取，使用过程中是否被非法修改。
 *
 */
#define OS_ERROR_MSGM_SH_HANDLE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x23)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在打开共享消息队列时，传入的ID非法。
 *
 * 值: 0x02002b24
 *
 * 解决方案: 共享消息队列ID有效范围SD6182/SD6157为[0,31]，SD6183为[0,63]。
 *
 */
#define OS_ERROR_MSGM_SH_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x24)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开共享消息队列时，传入的handle指针为空。
 *
 * 值: 0x02002b25
 *
 * 解决方案: 该指针不能为空。
 *
 */
#define OS_ERROR_MSGM_SH_HANDLE_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x25)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开共享消息队列时，FIFO区间配置错误。
 *
 * 值: 0x02002b26
 *
 * 解决方案: FIFO区间SD6182/SD6157为[0,1023]，SD6183为[0,2047]范围内。
 *
 */
#define OS_ERROR_MSGM_SH_FIFO_OVERRUN                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x26)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：共享消息队列未打开。
 *
 * 值: 0x02002b27
 *
 * 解决方案: 共享消息队列在使用之前必须由本核或其它核打开。
 *
 */
#define OS_ERROR_MSGM_SH_NOT_OPENED                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x27)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在做MSGM共享队列消息数查询时，传入的消息个数指针未空。
 *
 * 值: 0x02002b28
 *
 * 解决方案: 该指针必须指向有效数据，以便查询结果写回。
 *
 */
#define OS_ERROR_MSGM_SH_MSGNUM_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x28)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：发送共享消息时，数据非法。
 *
 * 值: 0x02002b29
 *
 * 解决方案: 全0或全F的数据不允许发送。
 *
 */
#define OS_ERROR_MSGM_SH_INVALID_DATA                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x29)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：从共享消息队列接收数据时，共享消息队列为空。
 *
 * 值: 0x02002b2a
 *
 * 解决方案: 确认数据是否已经发送。
 *
 */
#define OS_ERROR_MSGM_SH_RECV_EMPTY                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2a)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：从共享消息队列接收到的数据有不可纠ECC错误。
 *
 * 值: 0x02002b2b
 *
 * 解决方案: 无。
 *
 */
#define OS_ERROR_MSGM_SH_RECV_SER                               SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2b)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，传入队列ID非法。
 *
 * 值: 0x02002b2c
 *
 * 解决方案: 同步消息队列个数有效ID范围SD6182/SD6157为[0, 15]，SD6183为[0, 255]。
 *
 */
#define OS_ERROR_MSGM_SYN_ID_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2c)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，传入的配置参数attr指针为空。
 *
 * 值: 0x02002b2d
 *
 * 解决方案: 请传入有效的配置参数。
 *
 */
#define OS_ERROR_MSGM_SYN_ATTR_NULL                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2d)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，包括返回handle的地址指针为空。
 *
 * 值: 0x02002b2e
 *
 * 解决方案: 请传入有效的地址指针。
 *
 */
#define OS_ERROR_MSGM_SYN_HANDLE_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2e)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在做同步消息队列同步发送、统计查询等操作时，传入的handle无效。
 *
 * 值: 0x02002b2f
 *
 * 解决方案: 请确认该handle是否通过共享消息队列打开时获得，在使用过程中没有非法修改。
 *
 */
#define OS_ERROR_MSGM_SYN_HANDLE_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2f)


/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：接收共享消息时，消息体地址无效。
 *
 * 值: 0x02002b30
 *
 * 解决方案: 需要合法的消息体地址，以便保存接收消息。
 *
 */
#define OS_ERROR_MSGM_SH_RECV_DATA_PTR_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x30)


/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：start同步队列时，同步消息队列未打开。
 *
 * 值: 0x02002b31
 *
 * 解决方案: 同步队列必须在打开之后，才能进行start操作。
 *
 */
#define OS_ERROR_MSGM_SYN_NOT_OPENED                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x31)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：在打开同步计数时，传入的同步计数无效。
 *
 * 值: 0x02002b32
 *
 * 解决方案: 同步计数值有效范围SD6182/SD6157:[1, 31],SD6183:[1, 127]。
 *
 */
#define OS_ERROR_MSGM_SYN_SYNNUM_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x32)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，传入的LOAD模式无效。
 *
 * 值: 0x02002b33
 *
 * 解决方案: 只允许使用SRE_MSGM_SYN_LOAD_PERIOD和SRE_MSGM_SYN_LOAD_ONCE两种模式。
 *
 */
#define OS_ERROR_MSGM_SYN_LOAD_MODE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x33)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，选择了中断通知模式，但指定的目标核无效。
 *
 * 值: 0x02002b34
 *
 * 解决方案: 确认目标核号是否正确。
 *
 */
#define OS_ERROR_MSGM_SYN_DST_CORE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x34)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，传入的超时时间档位非法。
 *
 * 值: 0x02002b35
 *
 * 解决方案: 有效超时时间档位为[0, 11]， 或者SRE_MSGM_SYN_TOT_FOREVER。
 *
 */
#define OS_ERROR_MSGM_SYN_TOT_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x35)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，配置参数同步接受模式非法。
 *
 * 值: 0x02002b36
 *
 * 解决方案: 有效值为SRE_MSGM_SYN_RECV_IRQ或SRE_MSGM_SYN_RECV_MSG。
 *
 */
#define OS_ERROR_MSGM_SYN_RECV_MODE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x36)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，选择了消息通知模式，但消息发送目标地址非法。
 *
 * 值: 0x02002b37
 *
 * 解决方案: 请确认该地址是否为有效全局地址, 并且地址16字节对齐。
 *
 */
#define OS_ERROR_MSGM_SYN_DES_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x37)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：挂接中断通知钩子时，传入的中断号或中断模式无效。
 *
 * 值: 0x02002b38
 *
 * 解决方案: 当前82和57芯片可挂接中断通知钩子有效中断号范围为[19, 26]，且每次挂接采用的中断号和中断模式必须一致。
 *
 */
#define OS_ERROR_MSGM_SYN_RECV_IRQ_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x38)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：挂接中断通知钩子时，钩子已经注册。
 *
 * 值: 0x02002b39
 *
 * 解决方案: 请确认之前是否已经成功注册。
 *
 */
#define OS_ERROR_MSGM_SYN_IRQ_RECV_DISCARD                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x39)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：查询当前同步计数时，传入的返回地址指针为空。
 *
 * 值: 0x02002b3a
 *
 * 解决方案: 请输入有效地址指针。
 *
 */
#define OS_ERROR_MSGM_SYN_MSGCNT_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3a)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：发送同步消息时，消息体地址为空。
 *
 * 值: 0x02002b3b
 *
 * 解决方案: 该消息体地址不允许为空。
 *
 */
#define OS_ERROR_MSGM_SYN_MSG_PTR_NULL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3b)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：同步消息队列不在同步进行中。
 *
 * 值: 0x02002b3c
 *
 * 解决方案: 同步队列在发送、统计等操作前，需要先start该队列。
 *
 */
#define OS_ERROR_MSGM_SYN_NOT_GOING                              SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3c)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：同步消息队列消息错误。
 *
 * 值: 0x02002b3d
 *
 * 解决方案: 同步通知消息，发往共享队列时，不允许使用全0或全f的消息。
 *
 */
#define OS_ERROR_MSGM_SYN_MSG_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3d)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：挂接中断通知钩子时，注册钩子为空。
 *
 * 值: 0x02002b3e
 *
 * 解决方案: 注册钩子不能为空。
 *
 */
#define OS_ERROR_MSGM_SYN_RECV_HOOK_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3e)

/**
 * @ingroup SRE_msgm
 * 配置实例启动参数或者重新配置MSGM普通队列缓冲区范围时传入的MSGM队列起始地址或长度非4字节对齐。
 *
 * 值: 0x02002b3f
 *
 * 解决方案: 请确保传入的MSGM队列起始地址和长度都是4字节对齐的。
 */
#define OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN                  SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3f)

/**
 * @ingroup SRE_msgm
 * 配置实例启动参数时传入的MSGM队列起始地址非法。
 *
 * 值: 0x02002b40
 *
 * 解决方案: 请确保传入的MSGM队列起始地址不超过最大支持的地址。
 */
#define OS_ERRNO_MSGM_CFG_START_ADDR_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x40)

/**
 * @ingroup SRE_msgm
 * 配置实例启动参数时传入的MSGM队列长度非法。
 *
 * 值: 0x02002b41
 *
 * 解决方案: 请确保传入的MSGM队列长度不超过最大支持的长度。
 */
#define OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x41)

/**
 * @ingroup SRE_msgm
 * 配置实例启动参数时传入的MSGM队列起始地址和长度决定的区间非法。
 *
 * 值: 0x02002b42
 *
 * 解决方案: 请确保传入的MSGM队列起始地址和长度决定的区间合法，对于Global MSGM普通队列，有效范围SD6182/SD6157为[0,2047]，SD6183为[0,8191]，对于Local MSGM普通队列，以及共享队列，有效范围SD6182/SD6157为[0,1023]，SD6183为[0,2047]。
 */
#define OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x42)

/**
 * @ingroup SRE_msgm
 * 配置本核的普通局部消息缓冲长度过长。
 *
 * 值: 0x02002b43
 *
 * 解决方案: 请确保本实例所有核上配置普通局部消息缓冲总长度不超过传入的本实例管理的普通局部消息缓冲长度。
 */
#define OS_ERRNO_MSGM_CFG_LOCAL_QUE_TOO_LONG                    SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x43)

/**
 * @ingroup SRE_msgm
 * 配置本核的普通全局消息缓冲长度过长。
 *
 * 值: 0x02002b44
 *
 * 解决方案: 请确保本实例所有核上配置普通全局消息缓冲总长度不超过传入的本实例管理的普通全局消息缓冲长度。
 */
#define OS_ERRNO_MSGM_CFG_GLOBAL_QUE_TOO_LONG                   SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x44)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：获取共享消息队列入口地址时，输入地址指针为空。
 *
 * 值: 0x02002b45
 *
 * 解决方案: 该地址指针不能为空。
 *
 */
#define OS_ERROR_MSGM_SH_ADDR_GET_NULL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x45)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：获取同步消息队列入口地址时，输入地址指针为空。
 *
 * 值: 0x02002b46
 *
 * 解决方案: 该地址指针不能为空。
 *
 */
#define OS_ERROR_MSGM_SYN_ADDR_GET_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x46)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：注册同步消息队列中断通知钩子函数时，申请内存失败。
 *
 * 值: 0x02002b47
 *
 * 解决方案: 增大OS缺省分区大小配置。
 *
 */
#define OS_ERROR_MSGM_SYN_IRQ_NO_MEMORY                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x47)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置普通消息溢出缓冲区时，传入的缓存区首地址无效。
 *
 * 值: 0x02002b48
 *
 * 解决方案: 缓存区首地址不允许为NULL，且为有效的全局地址。
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_ILLEGAL                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x48)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置普通消息溢出缓冲区时，传入的缓存区大小无效。
 *
 * 值: 0x02002b49
 *
 * 解决方案: 缓存区大小要求16字节对齐，且为有效的全局地址空间。
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_BUFFER_SIZE_ILLEGAL                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x49)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置普通消息溢出缓冲区时，缓存区地址没有地址对齐。
 *
 * 值: 0x02002b4a
 *
 * 解决方案: 缓存区首地址和长度都要求16字节对齐。
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_NOT_ALIGN              SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4a)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：配置普通消息溢出缓冲区时，传入的MSGM ID无效。
 *
 * 值: 0x02002b4b
 *
 * 解决方案: MSGM ID有效值为SRE_GLOBAL_MSGM或SRE_LOCAL_MSGM(SRE_LOCAL_MSGM只对SD6182/SD6183有效)。
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_MSGM_ID_ILLEGAL                    SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4b)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：发送共享消息时，消息体地址无效。
 *
 * 值: 0x02002b4c
 *
 * 解决方案: 需要合法的消息体地址，以便进行消息发送。
 *
 */
#define OS_ERROR_MSGM_SH_SEND_DATA_PTR_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4c)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：设置VMID时，传入的VMID值无效。
 *
 * 值: 0x02002b4e
 *
 * 解决方案: 当VMID类型为通道组VMID时，VMID值有效范围[0,7]，当为通道VMID时，有效范围低8bit有效。
 *
 */
#define OS_ERRNO_MSGM_VMID_VALUE_ILLEGAL                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4e)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的通道组编号值无效。
 *
 * 值: 0x02002b4f
 *
 * 解决方案: 通道组编号值有效范围为[0,3]。
 *
 */
#define OS_ERRNO_MSGM_CHG_IDX_ILLEGAL                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4f)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：设置普通消息队列VMID时，传入的编号值无效。
 *
 * 值: 0x02002b50
 *
 * 解决方案: 硬线程编号值有效范围[0,33]。
 *
 */
#define OS_ERRNO_MSGM_NOR_CORE_IDX_ILLEGAL                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x50)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：设置共享队列组VMID时，传入的编号值无效。
 *
 * 值: 0x02002b51
 *
 * 解决方案: 共享队列组编号值有效范围[0,7]。
 *
 */
#define OS_ERRNO_MSGM_SH_IDX_ILLEGAL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x51)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：设置同步队列组VMID时，传入的编号值无效。
 *
 * 值: 0x02002b52
 *
 * 解决方案: 共享队列组编号值有效范围[0,31]。
 *
 */
#define OS_ERRNO_MSGM_SYNC_IDX_ILLEGAL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x52)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的队列类型无效。
 *
 * 值: 0x02002b53
 *
 * 解决方案: MSGM队列类型有效值范围[0,2]。
 *
 */
#define OS_ERRNO_MSGM_QUEUE_TYPE_ILLEGAL                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x53)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的核号无效。
 *
 * 值: 0x02002b54
 *
 * 解决方案: 核号有效范围SD6182:[0-16]，SD6157:(0、1、2、12)，SD6183[0,33]。
 *
 */
#define OS_ERRNO_MSGM_COREID_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x54)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：传入的通道组映射配置表非法。
 *
 * 值: 0x02002b55
 *
 * 解决方案: 普通队列硬线程bitmap低34位有效，共享队列组bitmap低8位有效。
 *
 */
#define OS_ERRNO_MSGM_MAP_INFO_ILLEGAL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x55)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：查询同步消息队列使能状态时，返回使能状态的地址指针为空。
 *
 * 值: 0x02002b56
 *
 * 解决方案: 请传入有效的地址指针。
 *
 */
#define OS_ERROR_MSGM_SYN_EN_STATE_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x56)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，配置发送消息数据模式非法。
 *
 * 值: 0x02002b57
 *
 * 解决方案: 有效值为SRE_MSGM_SYN_DATA_DYN或SRE_MSGM_SYN_DATA_STATIC。
 *
 */
#define OS_ERROR_MSGM_SYN_DATA_MODE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x57)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：打开同步消息队列时，配置匹配word值非法。
 *
 * 值: 0x02002b58
 *
 * 解决方案: 有效范围[0,3]。
 *
 */
#define OS_ERROR_MSGM_SYN_CMP_WORD_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x58)


/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：内核进程非空中断接收Qport消息时，目的进程的局部线程ID、全局线程ID或者PID非法。
 *
 * 值: 0x02002b59
 *
 * 解决方案: 排查目的进程的用户线程是否创建过。
 *
 */
#define OS_ERROR_MSGM_INVLAID_GLTID_PID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x59)

/**
 * @ingroup SRE_msgm
 * 多核消息驱动错误码：KOS侧非空中断接收Qport消息时，目的进程的消息MSGM缓冲区溢出。
 *
 * 值: 0x02002b5a
 *
 * 解决方案: 确保用户进程的消息及时接收。
 *
 */
#define OS_ERROR_MSGM_USR_MSG_BUF_OV                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x5a)


/**
 * @ingroup SRE_msgm
 * @brief qport消息钩子类型定义。
 *
 * @par 描述:
 * 该钩子通过SRE_QportHookSet进行注册。
 * 当本核的os使用的Qport非空中断接收到该类型的消息时，会将接收到的消息通过传递给本函数交由用户进行处理。
 * @attention 无。
 *
 * @param  auwData[4] [IN] 类型#UINT32，接收到的128bit消息的首地址。
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无。
 */
typedef VOID (*SRE_QPORT_HOOK)(UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * MSGM模块配置信息的结构体定义。
 */
typedef struct tagMsgmModInfo
{
    VOID  *pProfBufAddr;        /**< 每个核的profiling缓冲区首地址 */
    UINT32 uwProfBufSize;       /**< 每个核的profiling缓冲区长度 */
}MSGM_MOD_INFO_S;

/**
 * @ingroup SRE_task
 * 同步或共享消息队列handle。
 */
typedef UINT32 QUE_HANDLE_T;

/**
 * @ingroup SRE_msgm
 * @brief: 同步消息中断通知钩子类型定义。
 *
 * @par 描述:
 * 该钩子通过SRE_MsgmSynRevHookReg进行注册。
 * 当本核收到同步消息中断通知后，会通过该接口通知用户做进一步处理。
 * @attention 无。
 *
 * @param  hQue [IN] 类型#QUE_HANDLE_T，同步消息队列handle。
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynRevHookReg
 */
typedef VOID (* SRE_MSGM_SYN_REV_HOOK)(QUE_HANDLE_T hQue);

/**
 * @ingroup SRE_msgm
 * 同步消息队列计数周期加载启动模式
 */
#define SRE_MSGM_SYN_LOAD_PERIOD    0

/**
 * @ingroup SRE_msgm
 * 同步消息队列计数单次加载启动模式
 */
#define SRE_MSGM_SYN_LOAD_ONCE      1

/**
 * @ingroup SRE_msgm
 * SD6182/SD6157 同步消息队列采用中断方式进行通知
 */
#define SRE_MSGM_SYN_RECV_IRQ       0

/**
 * @ingroup SRE_msgm
 * SD6182/SD6157 同步消息队列采用消息方式进行通知
 */
#define SRE_MSGM_SYN_RECV_MSG       1

/**
 * @ingroup SRE_msgm
 * SD6183 同步消息队列采用动态模式
 */
#define SRE_MSGM_SYN_DATA_DYN       0

/**
 * @ingroup SRE_msgm
 * SD6183 同步消息队列采用静态模式
 */
#define SRE_MSGM_SYN_DATA_STATIC    1

/**
 * @ingroup SRE_msgm
 * 同步消息队列超时时间，表示不做超时检测
 */
#define SRE_MSGM_SYN_TOT_FOREVER    0xFFFFFFFFU

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup SRE_msgm
 * SD6182/SD6157 MSGM同步消息队列配置参数的结构体定义。
 */
typedef struct tagSreSynQueAttr
{
    UINT32 uwLoadMode;       /**< 计数器同步加载方式，SRE_MSGM_SYN_LOAD_PERIOD或SRE_MSGM_SYN_LOAD_ONCE                                   */
    UINT32 uwRecvMode;       /**< 同步后的通知模式，SRE_MSGM_SYN_RECV_IRQ：中断模式, SRE_MSGM_SYN_RECV_MSG:消息通知模式                  */
    UINT32 uwSynCnt;         /**< 同步计数值，有效范围[1, 31]                                                                            */
    UINT32 uwTimeOut;        /**< 超时时间档位，取值范围N: [0~11]，对应超时时间: 2^N*8Kcycles。 SRE_MSGM_SYN_TOT_FOREVER表示不做超时检测 */
    UINT32 uwSynMatch;       /**< 消息的过滤数据，仅对消息的最后一个word进行过滤                                                         */
    UINT32 uwSynMask;        /**< 过滤消息的掩码，对应比特位配置为0，则相应位需要进行消息匹配检查。仅对消息的最后一个word进行掩码        */
    UINT32 uwIrqDstCore;     /**< 中断通知模式时，通知的目标核号。(仅中断通知模式有效)                                                   */
    VOID * pMsgDstAddr;      /**< 消息通知模式时，消息通知的目的地址。(仅消息通知模式有效, 需要配置为有效全局地址且16字节对齐)           */
    UINT32 auwMsgData[4];    /**< 消息通知模式时，消息通知的消息数据。(仅消息通知模式有效)                                               */
}SRE_SYN_QUE_ATTR_S;

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

/**
 * @ingroup SRE_msgm
 * SD6183 MSGM同步消息队列配置参数的结构体定义。
 */
typedef struct tagSreSynQueAttr
{
    UINT32 uwLoadMode;       /**< 计数器同步加载方式，SRE_MSGM_SYN_LOAD_PERIOD或SRE_MSGM_SYN_LOAD_ONCE                                   */
    UINT32 uwQueMode;        /**< 发送消息数据模式，SRE_MSGM_SYN_DATA_DYN：动态模式, SRE_MSGM_SYN_DATA_STATIC:静态模式                   */
    UINT32 uwSynCnt;         /**< 同步计数值，有效范围[1, 127]                                                                           */
    UINT32 uwTimeOut;        /**< 超时时间档位，取值范围N: [0~11]，对应超时时间: 2^N*8Kcycles。 SRE_MSGM_SYN_TOT_FOREVER表示不做超时检测 */
    UINT32 uwSynMatch;       /**< 消息的过滤数据，仅对消息的uwSynCmpWord个word进行过滤                                                   */
    UINT32 uwSynMask;        /**< 过滤消息的掩码，对应比特位配置为1，则相应位需要进行消息匹配检查。仅对消息的uwSynCmpWord个word进行掩码  */
    UINT32 uwSynCmpWord;     /**< 消息检查第几个WORD，有效范围[0, 3]                                                                     */
    VOID * pMsgDstAddr;      /**< 消息通知模式时，消息通知的目的地址。(仅消息通知模式有效, 需要配置为有效全局物理地址且16字节对齐)       */
    UINT32 auwMsgData[4];    /**< 消息通知模式时，消息通知的消息数据。(仅消息通知模式有效)                                               */
}SRE_SYN_QUE_ATTR_S;

#endif

/**
 * @ingroup SRE_msgm
 * SD6183 队列类型值
 */
typedef enum tagMsgmQueueType
{
    OS_MSGM_NOR_QUEUE     = 0,    /**< 普通消息队列             */
    OS_MSGM_SH_QUEUE      = 1,    /**< 共享消息队列             */
    OS_MSGM_SYNC_QUEUE    = 2     /**< 同步消息队列             */
}MSGM_QUEUE_TYPE_E;

/**
 * @ingroup SRE_msgm
 * SD6183 通道组映射的结构体定义。
 */
typedef struct tagMsgmChgMapInfo
{
    UINT64 ullNorChBitmap;        /**< 普通队列硬线程号bitmap，低34bit有效，每1bit代表1个硬线程号*/
    UINT32 uwShChBitmap;          /**< 共享队列组bitmap，低8bit有效，每1bit代表1个共享队列组     */
    UINT32 uwSyncChBitmap;        /**< 同步队列组bitmap，32位有效， 每1bit代表1个同步队列组      */
}MSGM_CHG_MAP_S;

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))

#if (OS_OPTION_MSGM_USR_MNG == YES)
/**
 * @ingroup SRE_msgm
 * @brief 配置指定核指定Qport指定队列的起始位置和深度。
 *
 * @par 描述:
 * 每个Qport在MSGM中存在两个缓冲队列，本接口根据队列起始位置对每个缓冲队列的深度进行配置，一个深度单元代表一条消息。
 * 在配置完队列深度之后会对指定队列进行优先级设置，默认会将0队列配置成高优先级，1队列配置低优先级，并使能队列功能。
 * @attention
 * <ul>
 * <li>适用于SD6183、SD6182/SD6157平台。</li>
 * <li>OS使用了0号QPORT的0号队列；0号QPORT为OS管理，创建为中断方式，故用户必须通过中断方式接收0号QPORT队列中消息(接收时通过用户自己注册的钩子函数实现消息接收处理)。</li>
 * <li>SD6182/SD6157 CPU和DSP使用的所有队列深度加起来不能超过2048，HACCC使用的所有队列深度加起来不能超过1024，而SD6183 DSP核使用的所有队列深度加起来不能超过8192，HACCC使用的所有队列深度加起来不能超过2048。</li>
 * <li>队列起始位置和队列深度必须配置成4的整数倍。</li>
 * <li>必须先调用SRE_MsgmQportReset接口对指定核进行软复位，才能设置对应核的队列深度。</li>
 * <li>SD6183平台由用户保证有通道组VMID权限调用该接口。</li>
 * </ul>
 *
 * @param uwCoreID       [IN] 类型#UINT32，指定的核号,取值范围SD6182:[0-16]，SD6157:(0、1、2、12)，SD6183[0,33]。
 * @param uwQportID      [IN] 类型#UINT32，指定的QPORT ID,取值范围：dsp:[0,1];haccc:[0,2]。
 * @param uwQueIdx       [IN] 类型#UINT32，指定的队列ID，取值范围：0，1。
 * @param uwQueStart     [IN] 类型#UINT32，队列起始位置，取值范围：4的正整数倍。
 * @param uwQueDepth     [IN] 类型#UINT32，队列的深度，取值范围：4的正整数倍。
 *
 * @retval #OS_ERRNO_MSGM_COREID_INVALID            0x02002b54，核号非法。
 * @retval #OS_ERRNO_MSGM_QDEP_QORTID_INVALID       0x02002b02，QPORT ID非法。
 * @retval #OS_ERRNO_MSGM_QDEP_QUEID_INVALID        0x02002b03，队列ID非法。
 * @retval #OS_ERRNO_MSGM_QDEP_QDEPTH_INVALID       0x02002b04，队列深度非法。
 * @retval #OS_ERRNO_MSGM_INIT_MSGQ_NORESP          0x02002b01，多核消息驱动初始化过程中，MSGM通道无响应，或者核接收状态为完成，需判断下是否是总线挂死。
 * @retval #SRE_OK                                  0x00000000，配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_MsgmNorQueSet(UINT32 uwCoreID, UINT32 uwQportID, UINT32 uwQueIdx, UINT32 uwQueStart, UINT32 uwQueDepth);

/**
 * @ingroup SRE_msgm
 * @brief 对指定核的MSGM队列和Qport软复位。
 *
 * @par 描述:
 * 对指定核所有的Qport以及MSGM队列软复位。
 * @attention
 * <ul>
 * <li>适用于SD6183、SD6182/SD6157平台。</li>
 * <li>必须先调用该接口对指定核进行软复位，才能设置对应核的队列深度。</li>
 * <li>调用该接口后，指定核的MSGM队列和Qport里面的所有消息都会丢失。</li>
 * <li>SD6183平台由用户保证有通道组VMID权限调用该接口。</li>
 * </ul>
 *
 * @param uwCoreID       [IN] 类型#UINT32，指定的核号,取值范围SD6182:[0-16]，SD6157:(0-2、12)，SD6183[0,33]。
 *
 * @retval #OS_ERRNO_MSGM_COREID_INVALID            0x02002b54，核号非法。
 * @retval #OS_ERRNO_MSGM_INIT_MSGQ_NORESP          0x02002b01，多核消息驱动初始化过程中，MSGM通道无响应，或者核接收状态为完成，需判断下是否是总线挂死。
 * @retval #SRE_OK                                  0x00000000，配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_MsgmQportReset(UINT32 uwCoreID);

#else
/**
 * @ingroup SRE_msgm
 * @brief MSGM队列配置函数。
 *
 * @par 描述:
 * 每个Qport在MSGM中存在两个缓冲队列，本接口对每个缓冲队列的深度进行配置，一个深度单元代表一条消息。
 * 在配置完队列深度之后会对本队列进行优先级设置，默认会将0队列配置成高优先级，1队列配置低优先级，并使能队列功能。
 * @attention
 * <ul>
 * <li>适用于SD6182 、SD6157平台。</li>
 * <li>OS使用了0号QPORT的0号队列；0号QPORT为OS管理，创建为中断方式，故用户必须通过中断方式接收0号QPORT队列中消息(接收时通过用户自己注册的钩子函数实现消息接收处理)。</li>
 * <li>CPU和DSP使用的所有队列深度加起来不能超过2048，HACCC使用的所有队列深度加起来不能超过1024。</li>
 * <li>队列的深度尽量配置成4的整数倍，如果不是，接口自动会向上适配成4的整数倍，譬如配置成7，实际生效是8。</li>
 * </ul>
 *
 * @param uwQportID      [IN] 类型#UINT32，指定的QPORT ID,取值范围：dsp:[0,1];cpu:[0,1];haccc:[0,2]。
 * @param uwQueIdx       [IN] 类型#UINT32，指定的队列ID，取值范围：0，1。
 * @param uwQueDepth     [IN] 类型#UINT32，队列的深度，取值范围：4的正整数倍。
 *
 * @retval #OS_ERRNO_MSGM_QDEP_QORTID_INVALID       0x02002b02，QPORT ID非法。
 * @retval #OS_ERRNO_MSGM_QDEP_QUEID_INVALID        0x02002b03，队列ID非法。
 * @retval #OS_ERRNO_MSGM_QDEP_QDEPTH_INVALID       0x02002b04，队列深度非法。
 * @retval #OS_ERRNO_MSGM_QDEP_QUEEN_WRONG          0x02002b05，检测出队列已被使能。
 * @retval #OS_ERRNO_MSGM_NOT_INITED                0x02002b22，设置MSGM队列深度时，MSGM没有初始化。
 * @retval #OS_ERRNO_MSGM_CFG_LOCAL_QUE_TOO_LONG    0x02002b43，配置本核的普通局部消息缓冲长度过长。
 * @retval #OS_ERRNO_MSGM_CFG_GLOBAL_QUE_TOO_LONG   0x02002b44，配置本核的普通全局消息缓冲长度过长。
 * @retval #SRE_OK                                  0x00000000，配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_QueDepthSet(UINT32 uwQportID, UINT32 uwQueIdx, UINT32 uwQueDepth);

/**
 * @ingroup SRE_msgm
 * @brief 主控核重新配置MSGM普通队列缓冲区范围函数。
 *
 * @par 描述:
 * 主控核重新配置MSGM普通队列缓冲区范围。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157平台。</li>
 * <li>用户保证实例间MSGM缓冲区没有重叠。</li>
 * <li>该接口会对本核的MSGQ和MSGM队列做重新初始化。</li>
 * <li>用户保证队列深度的重配置在本接口被调用完毕后再执行。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * </ul>
 *
 * @param uwGMsgmBufStart    [IN] 类型#UINT32，全局MSGM普通队列缓冲区起始地址。
 * @param uwGMsgmBufLen      [IN] 类型#UINT32，全局MSGM普通队列缓冲区长度。
 *
 * @retval #OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN  0x02002b3f，重新配置MSGM普通队列缓冲区范围时传入的MSGM队列起始地址或长度非4字节对齐。
 * @retval #OS_ERRNO_MSGM_CFG_START_ADDR_INVALID     0x02002b40，重新配置MSGM普通队列缓冲区范围时传入的MSGM队列起始地址非法。
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID      0x02002b41，重新配置MSGM普通队列缓冲区范围时传入的MSGM队列长度非法。
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID   0x02002b42，重新配置MSGM普通队列缓冲区范围时传入的MSGM队列起始地址和长度决定的区间非法。
 * @retval #OS_ERRNO_MSGM_INIT_MSGQ_NORESP           0x02002b01，多核消息驱动初始化过程中，MSGM通道无响应，或者核接收状态为完成，需判断下是否是总线挂死。
 * @retval #SRE_OK                                   0x00000000，配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmBufRecfg(UINT32 uwGMsgmBufStart, UINT32 uwGMsgmBufLen);

#endif

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列完成中断通知钩子注册接口。
 *
 * @par 描述:
 * 该接口由同步完成目标核进行注册，钩子在OS接收到同步中断通知后调用注册钩子通知用户。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157平台。</li>
 * <li>每个队列handle允许多次注册，以最后一次为准。</li>
 * <li>所有的队列共用一个中断号。对于同一个核，要求uwIntHum和usMode两个参数在每次调用过程中必须保持一致。</li>
 * </ul>
 *
 * @param hQueue        [IN] 类型#QUE_HANDLE_T，同步消息队列handle。
 * @param uwIntNum      [IN] UINT32，中断号, 有效范围为[19, 26]。
 * @param usMode        [IN] HWI_MODE_T，中断模式，独占或组合型。
 * @param pfnHook       [IN] SRE_MSGM_SYN_REV_HOOK，钩子函数指针，不能为空。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID       0x02002b2f，handle无效。
 * @retval #OS_ERROR_MSGM_SYN_RECV_IRQ_INVALID     0x02002b38，中断号无效。
 * @retval #OS_ERROR_MSGM_SYN_RECV_HOOK_NULL       0x02002b3e，注册钩子为空。
 * @retval #OS_ERROR_MSGM_SYN_IRQ_NO_MEMORY        0x02002b47，申请内存失败。
 * @retval #SRE_OK                                 0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmSynRevHookReg(QUE_HANDLE_T hQueue, UINT32 uwIntNum, HWI_MODE_T usMode, SRE_MSGM_SYN_REV_HOOK pfnHook);

/**
 * @ingroup SRE_msgm
 * @brief 普通消息溢出缓冲区配置接口。
 *
 * @par 描述:
 * 根据用户传入的参数，配置指定的MSGM普通消息溢出缓存区，并使能溢出缓存功能。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157平台。</li>
 * <li>如果重复配置，以最后一次为准。 之前的溢出数据，在新的配置生效后，将被清除。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM和溢出缓存区内存是否被低功耗关断不做判断，用户请自行保证。</li>
 * </ul>
 *
 * @param uwMsgmID      [IN] UINT32，MSGM ID，有效值为SRE_GLOBAL_MSGM或SRE_LOCAL_MSGM(SRE_LOCAL_MSGM只对SD6182)。
 * @param pBufAddr      [IN] VOID *，缓存区首地址，要求为GLOBAL可写地址，并且首地址16字节对齐。
 * @param uwBufSize     [IN] UINT32，以字节为单位的缓存区长度。长度要求16字节对齐。
 *
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_ILLEGAL       0x02002b48，缓存区首地址为NULL, 或者不是Global地址。
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_SIZE_ILLEGAL       0x02002b49，缓存区大小无效。
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_NOT_ALIGN     0x02002b4a，缓存区首地址或长度没有16字节对齐。
 * @retval #OS_ERRNO_MSGM_NOR_OV_MSGM_ID_ILLEGAL           0x02002b4b，MSGM ID无效。
 * @retval #SRE_OK                                         0x00000000，配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_NorQueOvBufAddrCfg(UINT32 uwMsgmID, VOID * pBufAddr, UINT32 uwBufSize);

#else
/**
 * @ingroup SRE_msgm
 * @brief MSGM通道组映射关系配置和Vmid设置接口。
 *
 * @par 描述:
 * 1、把普通消息队列、共享消息队列和同步消息队列映射到相应的通道组。
 * 2、设置通道组的VMID。
 * @attention
 * <ul>
 * <li>适用于SD6183平台。</li>
 * </ul>
 *
 * @param uwChgId       [IN] 类型#UINT32，通道组ID，取值范围[0,3]。
 * @param pstChgMapInfo [IN] 类型#MSGM_CHG_MAP_S *，通道组映射配置表。
 * @param uwChgVmid     [IN] 类型#UINT32，通道组Vmid值，取值范围[0,7]。
 *
 * @retval #OS_ERRNO_MSGM_CHG_IDX_ILLEGAL           0x02002b4f，设置通道组VMID时，传入的编号值无效。
 * @retval #OS_ERRNO_MSGM_VMID_VALUE_ILLEGAL        0x02002b4e，设置VMID时，传入的VMID值无效。
 * @retval #OS_ERRNO_MSGM_MAP_INFO_ILLEGAL          0x02002b55，传入的通道组映射配置表非法。
 * @retval #SRE_OK                                  0x00000000，返回成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_MsgmChgCfg(UINT32 uwChgId, MSGM_CHG_MAP_S *pstChgMapInfo, UINT32 uwChgVmid);

/**
 * @ingroup SRE_msgm
 * @brief MSGM通道VMID配置接口。
 *
 * @par 描述:
 * 设置普通消息队列、共享消息队列、同步消息队列的VMID。
 * @attention
 * <ul>
 * <li>适用于SD6183平台。</li>
 * </ul>
 *
 * @param enQueueType    [IN] 类型#MSGM_QUEUE_TYPE_E，队列类型，取值范围[0,2]。
 * @param uwChId         [IN] 类型#UINT32，通道编号(enQueueType为普通消息队列:硬线程编号[0,33]，共享消息队列:共享队列组编号[0,7]，同步消息队列:同步队列组编号[0,31])。
 * @param uwChVmidBitmap [IN] 类型#UINT32，Vmid值(8位bit map)。
 *
 * @retval #OS_ERRNO_MSGM_QUEUE_TYPE_ILLEGAL        0x02002b53，传入的队列类型无效。
 * @retval #OS_ERRNO_MSGM_VMID_VALUE_ILLEGAL        0x02002b4e，设置VMID时，传入的VMID值无效。
 * @retval #OS_ERRNO_MSGM_NOR_CORE_IDX_ILLEGAL      0x02002b50，设置普通消息队列VMID时，传入的编号值无效。
 * @retval #OS_ERRNO_MSGM_SH_IDX_ILLEGAL            0x02002b51，设置共享队列组VMID时，传入的编号值无效。
 * @retval #OS_ERRNO_MSGM_SYNC_IDX_ILLEGAL          0x02002b52，设置同步队列组VMID时，传入的编号值无效。
 * @retval #SRE_OK                                  0x00000000，返回成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_MsgmChVmidSet(MSGM_QUEUE_TYPE_E enQueueType, UINT32 uwChId, UINT32 uwChVmidBitmap);

/**
 * @ingroup SRE_msgm
 * @brief 普通消息溢出缓冲区配置接口。
 *
 * @par 描述:
 * 根据用户传入的参数，配置指定的MSGM普通消息溢出缓存区，并使能溢出缓存功能。
 * @attention
 * <ul>
 * <li>适用于SD6183。</li>
 * <li>如果重复配置，以最后一次为准。之前的溢出数据，在新的配置生效后，将被清除。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM和溢出缓存区内存是否被低功耗关断不做判断，用户请自行保证。</li>
 * </ul>
 *
 * @param uwMsgmID      [IN] UINT32，MSGM ID，有效值为SRE_GLOBAL_MSGM或SRE_LOCAL_MSGM。
 * @param uwChgId       [IN] UINT32，通道组ID，有效值范围为[0,3]。
 * @param pBufAddr      [IN] VOID *，缓存区首地址，要求为可写虚地址，并且首地址16字节对齐。用户保证为GLOBAL地址。
 * @param uwBufSize     [IN] UINT32，以字节为单位的缓存区长度。长度要求16字节对齐。
 *
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR                       0x02001239，虚地址转实地址失败。
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_SIZE_ILLEGAL       0x02002b49，缓存区大小无效。
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_NOT_ALIGN     0x02002b4a，缓存区首地址或长度没有16字节对齐。
 * @retval #OS_ERRNO_MSGM_NOR_OV_MSGM_ID_ILLEGAL           0x02002b4b，MSGM ID无效。
 * @retval #SRE_OK                                         0x00000000，配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern UINT32 SRE_NorQueOvBufAddrCfg(UINT32 uwMsgmID, UINT32 uwChgId, VOID * pBufAddr, UINT32 uwBufSize);
#endif
#endif

/**
 * @ingroup SRE_msgm
 * @brief Qport消息钩子的注册函数。
 *
 * @par 描述:
 * 设置本核用户使用0号QPORT通信处理的钩子函数。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>该接口只针对OS占用的0号QPORT使用，而该QPORT工作在中断模式下，该钩子在中断中进行调用，故需注意执行时间不可过长。</li>
 * <li>当传入的钩子为空时，表示取消该用户钩子，此时返回结果为成功。</li>
 * <li>多次调用以最后一次为准。</li>
 * </ul>
 *
 * @param uwTag      [IN] 类型#UINT32，Qport消息标识Tag，取值范围：1~7(业务自定义消息); OS消息使用的Tag为0。
 * @param pfnHook    [IN] 类型#SRE_QPORT_HOOK，回调函数。
 *
 * @retval #OS_ERRNO_MSGM_QHOOK_TAG_INVALID      0x02002b08，注册失败，uwTag不合法。
 * @retval #SRE_OK                               0x00000000，注册成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_QportHookSet(UINT32 uwTag, SRE_QPORT_HOOK  pfnHook);

/**
 * @ingroup SRE_msgm
 * @brief 消息入口地址获取函数接口。
 *
 * @par 描述:
 * 获取目的核指定队列的消息入口地址。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>注意OS使用了0号QPORT的0号队列；0号QPORT为OS管理，创建为中断方式，故用户可以通过中断方式接收0号QPORT队列中消息(接收时通过用户自己注册的钩子函数实现消息接收处理)。</li>
 * </ul>
 *
 * @param uwDstCoreID    [IN] 类型#UINT32，消息发送到指定的目标核。
 * @param uwQportID      [IN] 类型#UINT32，指定的qport id,取值范围：dsp:[0,1];cpu:[0,1];haccc:[0,2]。
 * @param uwQueIdx       [IN] 类型#UINT32，指定的队列，取值范围：0，1。
 * @param pQportAddr     [OUT] 类型#VOID *，返回的消息Qport队列入口地址。
 *
 * @retval #OS_ERRNO_MSGM_SEND_ADDR_NULL         0x02002b09，获取地址失败，输入Qport队列入口地址为空。
 * @retval #OS_ERRNO_MSGM_SEND_DSTCORE_INVALID   0x02002b0f，获取地址失败，目的核非法。
 * @retval #OS_ERRNO_MSGM_SEND_PORTID_INVALID    0x02002b10，获取地址失败，qport非法。
 * @retval #OS_ERRNO_MSGM_SEND_QUEUEID_INVALID   0x02002b11，获取地址失败，queue id非法。
 * @retval #SRE_OK                               0x00000000，获取地址成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_QportAddrGet(UINT32 uwDstCoreID, UINT32 uwQportID, UINT32 uwQueIdx, VOID *pQportAddr);

/**
 * @ingroup SRE_msgm
 * @brief Qport消息的发送函数。
 *
 * @par 描述:
 * 直接使用硬件的Qport发送消息。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>注意OS使用了0号QPORT的0号队列；0号QPORT为OS管理，创建为中断方式，故用户可以通过中断方式接收0号QPORT队列中消息(接收时通过用户自己注册的钩子函数实现消息接收处理)。</li>
 * <li>auwData[3]的低3bit为tag，1~7(业务自定义消息); OS消息使用的Tag为0。</li>
 * <li>用户保证发送的字节地址128bit对齐。</li>
 * <li>OS对目的核是否被低功耗关断不做判断，用户请自行保证。</li>
 * </ul>
 *
 * @param uwDstCoreID    [IN] 类型#UINT32，消息发送到指定的目标核。
 * @param uwQportID      [IN] 类型#UINT32，指定的qport id,取值范围：dsp:[0,1];cpu:[0,1];haccc:[0,2]。
 * @param uwQueIdx       [IN] 类型#UINT32，指定的队列，取值范围：0，1。
 * @param auwData        [IN] 类型#UINT32*，待发送的消息数组 ，长度为16字节。
 *
 * @retval #OS_ERRNO_MSGM_SEND_DSTCORE_INVALID      0x02002b0f，发送失败，目的核非法。
 * @retval #OS_ERRNO_MSGM_SEND_PORTID_INVALID       0x02002b10，发送失败，qport非法。
 * @retval #OS_ERRNO_MSGM_SEND_QUEUEID_INVALID      0x02002b11，发送失败，queue id非法。
 * @retval #OS_ERROR_MSGM_QPORT_SEND_DATA_NULL      0x02002b0a，发送失败，数据指针为空。
 * @retval #OS_ERROR_MSGM_QPORT_SEND_DATA_INVALID   0x02002b07，发送失败，数据内容无效。
 * @retval #SRE_OK                                  0x00000000，发送成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_QportSend(UINT32 uwDstCoreID, UINT32 uwQportID, UINT32 uwQueIdx, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief Qport消息的接收函数。
 *
 * @par 描述:
 * 接收本核指定Qport的消息。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>注意2号QPORT只能配置在HACCC核。</li>
 * <li>注意OS使用了0号QPORT的0号队列；0号QPORT为OS管理，创建为中断方式，故用户可以通过中断方式接收0号QPORT队列中消息(接收时通过用户自己注册的钩子函数实现消息接收处理)。</li>
 * <li>用户在使用PORT0 1号队列时，OS已经创建了HPQ中断并注册了处理函数，用户只需通过自己注册钩子函数(SRE_QportHookSet来实现)来接受处理消息，故这种方式不直接使用SRE_QportRecv接口以免跟OS冲突 ，若要使用查询方式必须先去使能该中断。</li>
 * <li>auwData[3]的低3bit为tag，1~7(业务自定义消息); OS消息使用的Tag为0。</li>
 * <li>由用户保证128bit对齐接收数据。</li>
 * </ul>
 *
 * @param uwQportID      [IN] 类型#UINT32，指定的qport,取值范围：dsp:[0,1];cpu:[0,1];haccc:[0,2]。
 * @param auwData        [IN] 类型#UINT32*，待接收消息buffer首地址 ，buffer长度为16字节。
 *
 * @retval #OS_ERRNO_MSGM_RECV_QID_INVALID      0x02002b0e，接收失败，qport非法。
 * @retval #OS_ERRNO_MSGM_RECV_QORT_EMPTY       0x02002b0d，接收失败，指定的qport中无消息。
 * @retval #OS_ERROR_MSGM_QPORT_RECV_SER        0x02002b0b, 接收数据有不可纠的2bit ECC错误。
 * @retval #OS_ERROR_MSGM_QPORT_RECV_DATA_NULL  0x02002b0c，接收失败，传入的数据指针为空。
 * @retval #SRE_OK                              0x00000000，接收成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_QportRecv(UINT32 uwQportID, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief 数据消息组装函数。
 *
 * @par 描述:
 * 把128bit的数据按照OS消息格式组装,主要用于在HACCC核与DSP&CPU的消息通信时，需要进行OS消息格式组装。
 * @attention:
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>对于Qport短消息，auwData[0~2]短消息内容, auwData[3]为生成的MSG header。</li>
 * <li>消息可以不包含消息体，若发送不带消息体消息，则MSG_HANDLE_T入参为OS_MSG_NO_PAYLOAD。</li>
 * <li>注意在使用该接口创建封装数据消息后，用户发送消息要符合OS消息发送规范，具体可见OS消息模块的手册。</li>
 * <li>注意创建封装数据消息的地址auwData不能为空。</li>
 * <li>通过MSGM发送的消息只支持发送到目的端线程的0号消息队列。</li>
 * </ul>
 *
 * @param uwMsgHandle    [IN]  类型#UINT32，消息体句柄，来源于消息体创建成功或接收成功的输出值。
 * @param uwMsgID        [IN]  类型#UINT32，消息ID，用以标识该消息的唯一性。
 * @param uwDstPID       [IN]  类型#UINT32，接收者的线程ID。
 * @param uwDstQID       [IN]  类型#UINT32，接收任务的指定队列，只能为0号队列，若接收者为软中断，本参数无效。
 * @param auwData        [OUT] 类型#UINT32*，待发送消息buffer首地址，buffer长度为16字节。
 *
 * @retval #OS_ERRNO_MSGM_PID_INVALID                0x02002b13，目的线程PID非法。
 * @retval #OS_ERRNO_MSGM_MSG_POINT_NULL             0x02002b15, 待创建消息数据的指针不能为空。
 * @retval #OS_ERRNO_MSGM_MSG_CREATE_HANDLE_INVALID  0x02002b21, 传入的消息体句柄非法（错误或已删除或句柄指针为NULL），或者消息体正在被使用。
 * @retval #SRE_OK                                   0x00000000，消息组装成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_QportMsgCreate(MSG_HANDLE_T uwMsgHandle, UINT32 uwMsgID, MSG_PID_T uwDstPID, UINT32 uwDstQID, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief 配置MSGM核间消息发送跟踪(TRACE)功能属性接口。
 *
 * @par 描述:
 * 根据用户传入的msgm的类型msgmID、缓冲区空间指针pTraceBufAddr、uwTraceBufSize大小的缓冲区、auwMask[4]大小的掩码、auwMatch[4]大小的匹配码 ，进行核间消息发送跟踪（TRACE)功能属性的配置。
 * 掩码、匹配码、消息值的逻辑关系为： 消息值(auwData) | 掩码值(auwMask) = 匹配码值(auwMatch)。即在auwMask对应位为1情况下，auwMatch对应位一定设置为1，auwData对应位才能过滤，在auwMask为0情况下，auwData对应位 = auwMatch对应位才能过滤。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>禁止在使能情况下进行配置。</li>
 * <li>如进行重复配置，以最后一次配置为准。</li>
 * <li>用户传入的缓冲区地址必须为共享地址。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM和缓存地址空间是否被低功耗关断不做判断，用户请自行保证。</li>
 * <li>SD6183平台由用户保证有COMM VMID权限调用该接口。</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32，0--往dsp&cpu核发送消息时使用的msgm消息队列，1--往haccc核发送消息时使用的msgm消息队列，其余值非法。
 * @param pTraceBufAddr  [IN] VOID *，TRACE BUFFER的首地址(SD6183平台为虚地址)，注：需保证为256bit对齐的GLOBAL地址。
 * @param uwTraceBufSize [IN] UINT32， TRACE BUFFER的长度，注：需保证为256bit的整数倍。
 * @param auwMask        [IN] UINT32 *，128bit的消息过滤掩码值。
 * @param auwMatch       [IN] UINT32 *，128bit的消息匹配值。
 *
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR             0x02001239，虚地址转实地址失败。
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16，指定的MSGM ID非法。
 * @retval #OS_ERRNO_MSGM_TRACE_BUFFER_NULL      0x02002b19，传入的MSGM TRACE缓冲区地址为NULL。
 * @retval #OS_ERRNO_MSGM_TRACE_BUFFER_NOT_ALIGN 0x02002b17，传入的TRACE缓冲区起始地址未256bit对齐。
 * @retval #OS_ERRNO_MSGM_TRACE_SIZE_NOT_ALIGN   0x02002b18，传入的TRACE缓冲区大小未256bit对齐。
 * @retval #OS_ERRNO_MSGM_TRACE_ENABLE           0x02002b1b，MSGM的TRACE功能已使能，此时禁止用户进行配置。
 * @retval #OS_ERRNO_MSGM_TRACE_SIZE_ILLEGAL     0x02002b1c，传入的TRACE缓冲区大小为0或缓冲区大小太大导致溢出。
 * @retval #OS_ERRNO_MSGM_TRACE_FILTERBIT_NULL   0x02002b1d，传入的MSGM的TRACE匹配码或掩码首地址为NULL。
 * @retval #SRE_OK                               0x00000000，过滤功能的属性配置成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_MsgTraceCfg(UINT32 uwMsgmID, VOID *pTraceBufAddr, UINT32 uwTraceBufSize, UINT32 auwMask[4], UINT32 auwMatch[4]);

/**
 * @ingroup SRE_msgm
 * @brief 使能MSGM核间消息发送跟踪(TRACE)功能接口。
 *
 * @par 描述:
 * 根据用户传入的msgm的类型msgmID，对MSGM核间消息发送跟踪(TRACE)功能进行使能。
 * 当使能MSGM核间消息发送跟踪(TRACE)功能时，TRACE BUFFER空间当前消息指针将进行清空，重复使能时不会进行清空。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>如进行重复使能，均返回成功。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM是否被低功耗关断不做判断，用户请自行保证。</li>
 * <li>SD6183平台由用户保证有COMM VMID权限调用该接口。</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32，0--往dsp&cpu核发送消息时使用的msgm消息队列，1--往haccc核发送消息时使用的msgm消息队列，其余值非法。
 *
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16，指定的MSGM ID非法。
 * @retval #OS_ERRNO_MSGM_TRACE_NOT_CONFIG       0x02002b1a，MSGM的TRACE缓冲区起始地址未进行配置。
 * @retval #SRE_OK                               0x00000000，使能MSGM核间消息发送跟踪(TRACE)功能成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MsgTraceDisable
 */
extern UINT32 SRE_MsgTraceEnable(UINT32 uwMsgmID);

/**
 * @ingroup SRE_msgm
 * @brief 去使能MSGM核间消息发送跟踪(TRACE)功能接口。
 *
 * @par 描述:
 * 根据用户传入的msgm的类型msgmID，对MSGM核间消息发送跟踪(TRACE)功能进行去使能。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>如进行重复去使能，均返回成功。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM是否被低功耗关断不做判断，用户请自行保证。</li>
 * <li>SD6183平台由用户保证有COMM VMID权限调用该接口。</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32，0--往dsp&cpu核发送消息时使用的msgm消息队列，1--往haccc核发送消息时使用的msgm消息队列，其余值非法。
 *
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16，指定的MSGM ID非法。
 * @retval #SRE_OK                               0x00000000，去使能MSGM核间消息发送跟踪(TRACE)功能成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MsgTraceEnable
 */
extern UINT32 SRE_MsgTraceDisable(UINT32 uwMsgmID);

/**
 * @ingroup SRE_msgm
 * @brief 获取TRACE BUFFER空间当前消息指针接口。
 *
 * @par 描述:
 * 根据用户传入的msgm的类型msgmID，获取空间当前消息指针，通过指针变量puwTracePtr进行返回，获取到的是个首地址偏移量。
 * 此接口返回的是待写入的下一条消息偏移地址，使用时：缓冲区首地址 + 当前消息指针 = 下一条待写入的消息地址。
 * 当使能MSGM核间消息发送跟踪(TRACE)功能时，TRACE BUFFER空间当前消息指针将进行清空。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>未配置缓冲区情况下，不允许调用此接口，返回指针为0XFFFFFFFF。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM是否被低功耗关断不做判断，用户请自行保证。</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32，0--往dsp&cpu核发送消息时使用的msgm消息队列，1--往haccc核发送消息时使用的msgm消息队列，其余值非法。
 * @param puwTracePtr    [OUT] UINT32 *，返回的TRACE BUFFER空间当前消息指针，函数执行失败且传入指针不为NULL时，指针返回0xFFFFFFFF。
 *
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16，指定的MSGM ID非法。
 * @retval #OS_ERRNO_MSGM_TRACE_PTR_NULL         0x02002b1e，用户传入获取当前消息的指针为NULL。
 * @retval #OS_ERRNO_MSGM_TRACE_NOT_CONFIG       0x02002b1a，MSGM的TRACE缓冲区起始地址未进行配置。
 * @retval #SRE_OK                               0x00000000，获取TRACE BUFFER空间当前消息指针成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_MsgTracePtrGet(UINT32 uwMsgmID, UINT32 *puwTracePtr);

/**
 * @ingroup SRE_msgm
 * @brief 打开共享消息队列接口。
 *
 * @par 描述:
 * 根据用户传入的队列ID及FIFO参数，初始化并打开指定队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>用户需要自行保证不同队列的FIFO区间无交叉。</li>
 * <li>如果该队列之前已经打开，该队列将被复位并重新打开。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开或关闭同一队列的情形，用户需在外层进行锁保护。</li>
 * </ul>
 *
 * @param uwQueID       [IN] UINT32，队列物理ID，有效值范围SD6182/SD6157为[0, 31],SD6183为[0, 63]。
 * @param uwFifoStart   [IN] UINT32，队列FIFO起始游标值。有效值范围SD6182/SD6157为[0, 1023],SD6183为[0, 2047]。
 * @param uwFifoDepth   [IN] UINT32，队列FIFO深度，有效范围SD6182/SD6157为[1, 1024],SD6183为[1, 2048]。且uwFifoStart + uwFifoDepthSD6182/SD6157不能超出1024,SD6183不能超出2048。
 * @param phQueue       [OUT] QUE_HANDLE_T *，若打开成功，返回队列handle。
 *
 * @retval #OS_ERROR_MSGM_SH_ID_INVALID          0x02002b24，ID非法。
 * @retval #OS_ERROR_MSGM_SH_HANDLE_NULL         0x02002b25，handle指针为空。
 * @retval #OS_ERROR_MSGM_SH_FIFO_OVERRUN        0x02002b26，FIFO区间配置错误。
 * @retval #SRE_OK                               0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueClose
 */
extern UINT32 SRE_MsgmShQueOpen(UINT32 uwQueID, UINT32 uwFifoStart, UINT32 uwFifoDepth, QUE_HANDLE_T * phQueue);

/**
 * @ingroup SRE_msgm
 * @brief 关闭共享消息队列接口。
 *
 * @par 描述:
 * 根据用户传入的handle，关闭对应的共享消息队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>队列中的残留数据将会被丢弃。</li>
 * <li>可以重复关闭共享队列，返回SRE_OK。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开或关闭同一队列的情形，用户需在外层进行锁保护。</li>
 * <li>SD6183平台由用户保证有通道组 VMID权限调用该接口。</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T，共享消息队列handle。
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23，handle非法。
 * @retval #SRE_OK                               0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueOpen
 */
extern UINT32 SRE_MsgmShQueClose(QUE_HANDLE_T hQueue);

/**
 * @ingroup SRE_msgm
 * @brief 共享消息队列消息发送接口。
 *
 * @par 描述:
 * 向handle对应的队列发送消息auwData。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>由用户保证128bit对齐发送数据。</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T，共享消息队列handle。
 * @param auwData      [IN] UINT32*，发送的消息体内容。
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID       0x02002b23，handle非法。
 * @retval #OS_ERROR_MSGM_SH_INVALID_DATA         0x02002b29，数据非法。
 * @retval #OS_ERROR_MSGM_SH_NOT_OPENED           0x02002b27，共享消息队列未打开。
 * @retval #OS_ERROR_MSGM_SH_SEND_DATA_PTR_NULL   0x02002b4c，无效的消息体地址。
 * @retval #SRE_OK                                0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueRecv
 */
extern UINT32 SRE_MsgmShQueSend(QUE_HANDLE_T hQueue, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief 共享消息队列消息接收接口。
 *
 * @par 描述:
 *  从handle对应的共享消息队列读取一条消息，并放入auwData内存中。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>由用户保证128bit对齐接收数据。</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T，共享消息队列handle。
 * @param auwData      [OUT] UINT32*，接收数据保存地址
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23，handle非法。
 * @retval #OS_ERROR_MSGM_SH_NOT_OPENED          0x02002b27，共享消息队列未打开。
 * @retval #OS_ERROR_MSGM_SH_RECV_EMPTY          0x02002b2a，共享消息队列为空。
 * @retval #OS_ERROR_MSGM_SH_RECV_SER            0x02002b2b，数据有不可纠ECC错误。
 * @retval #OS_ERROR_MSGM_SH_RECV_DATA_PTR_NULL  0x02002b30，无效的消息体地址。
 * @retval #SRE_OK                               0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueSend
 */
extern UINT32 SRE_MsgmShQueRecv(QUE_HANDLE_T hQueue, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief 共享消息队列消息缓存个数查询接口。
 *
 * @par 描述:
 * 查询handle对应的共享消息队列的缓存消息个数，并保存到puwMsgNum。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T，共享消息队列handle。
 * @param puwMsgNum    [OUT] UINT32 *，缓存消息个数
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23，handle非法。
 * @retval #OS_ERROR_MSGM_SH_MSGNUM_NULL         0x02002b28，消息个数指针为空。
 * @retval #OS_ERROR_MSGM_SH_NOT_OPENED          0x02002b27，共享消息队列未打开。
 * @retval #SRE_OK                               0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmShQueStatics(QUE_HANDLE_T hQueue, UINT32 * puwMsgNum);

/**
 * @ingroup SRE_msgm
 * @brief 共享消息队列消息入口地址获取函数接口。
 *
 * @par 描述:
 * 获取指定共享消息队列的消息入口地址。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * </ul>
 *
 * @param hQueue       [IN] 类型#QUE_HANDLE_T，共享消息队列handle。
 * @param pQueAddr     [OUT] 类型#VOID *，返回的共享消息队列入口地址。
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23，handle非法。
 * @retval #OS_ERROR_MSGM_SH_ADDR_GET_NULL       0x02002b45，地址为空。
 * @retval #SRE_OK                               0x00000000，获取地址成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmShQueAddrGet(QUE_HANDLE_T hQueue, VOID * pQueAddr);

#if (OS_OPTION_MSGM_SYN_PARA_RESET == YES)

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列参数重新配置接口。
 *
 * @par 描述:
 * 根据用户传入的队列ID及配置参数，重新配置参数并打开指定队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>如果对同一个队列多次参数重设，以最后一次为准。</li>
 * <li>如果对正在同步中的队列进行参数重设，那么同步将被停止，队列将重新复位打开。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开、关闭、启动、停止同一队列的情形，用户需在外层进行锁保护。</li>
 * <li>消息通知模式时，用户保证消息通知的目的地址为有效全局地址。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 * @param pstSynQueAttr [IN] SRE_SYN_QUE_ATTR_S *，队列配置参数。
 *
 * @retval #OS_ERROR_MSGM_SYN_ID_INVALID          0x02002b2c, 传入队列ID非法。
 * @retval #OS_ERROR_MSGM_SYN_ATTR_NULL           0x02002b2d，配置参数attr指针为空。
 * @retval #OS_ERROR_MSGM_SYN_SYNNUM_INVALID      0x02002b32，同步计数无效。
 * @retval #OS_ERROR_MSGM_SYN_LOAD_MODE_INVALID   0x02002b33，LOAD模式无效。
 * @retval #OS_ERROR_MSGM_SYN_TOT_INVALID         0x02002b35，超时时间档位非法。
 * @retval #OS_ERROR_MSGM_SYN_DST_CORE_INVALID    0x02002b34，目标核无效。
 * @retval #OS_ERROR_MSGM_SYN_RECV_MODE_INVALID   0x02002b36，同步接受模式非法。
 * @retval #OS_ERROR_MSGM_SYN_DES_ADDR_INVALID    0x02002b37，消息发送目标地址非法。
 * @retval #OS_ERROR_MSGM_SYN_MSG_INVALID         0x02002b3d，消息错误。
 * @retval #OS_ERROR_MSGM_SYN_DATA_MODE_INVALID   0x02002b57，配置发送消息数据模式非法。
 * @retval #OS_ERROR_MSGM_SYN_CMP_WORD_INVALID    0x02002b58，配置匹配word值非法。
 * @retval #SRE_OK                                0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MsgmSynQueOpen
 */
extern UINT32 SRE_MsgmSynParaReset(QUE_HANDLE_T hQueue, SRE_SYN_QUE_ATTR_S * pstSynQueAttr);

#endif

#if (OS_OPTION_MSGM_SYN_STATE_GET == YES)

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列使能状态查询接口。
 *
 * @par 描述:
 * 查询同步消息队列使能状态。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 * @param puwState      [OUT] UINT32 *，同步消息队列的使能状态，返回1代表使能状态，0代表去使能状态。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID      0x02002b2f，handle无效。
 * @retval #OS_ERROR_MSGM_SYN_EN_STATE_NULL       0x02002b56，返回使能状态的地址指针为空。
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED          0x02002b31，同步消息队列未打开。
 * @retval #SRE_OK                                0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MsgmSynQueStatics
 */
extern UINT32 SRE_MsgmSynStateGet(QUE_HANDLE_T hQueue, UINT32* puwState);

#endif

/**
 * @ingroup SRE_msgm
 * @brief 打开同步消息队列接口。
 *
 * @par 描述:
 * 根据用户传入的队列ID及配置参数，初始化并打开指定队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>同一个队列如果被多次打开，以最后一次为准。</li>
 * <li>如果打开正在同步中的队列，那么同步将被停止，队列将重新复位打开。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开、关闭、启动、停止同一队列的情形，用户需在外层进行锁保护。</li>
 * <li>消息通知模式时，用户保证消息通知的目的地址为有效全局地址。</li>
 * </ul>
 *
 * @param uwQueID       [IN] UINT32，队列物理ID，有效值范围为SD6182/SD6157:[0, 15]，SD6183:[0, 255]。
 * @param pstSynQueAttr [IN] SRE_SYN_QUE_ATTR_S *，队列配置参数。
 * @param phQueue       [OUT] QUE_HANDLE_T *，若打开成功，返回队列handle。
 *
 * @retval #OS_ERROR_MSGM_SYN_ID_INVALID          0x02002b2c, 传入队列ID非法。
 * @retval #OS_ERROR_MSGM_SYN_ATTR_NULL           0x02002b2d，配置参数attr指针为空。
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_NULL         0x02002b2e，handle的地址指针为空。
 * @retval #OS_ERROR_MSGM_SYN_SYNNUM_INVALID      0x02002b32，同步计数无效。
 * @retval #OS_ERROR_MSGM_SYN_LOAD_MODE_INVALID   0x02002b33，LOAD模式无效。
 * @retval #OS_ERROR_MSGM_SYN_TOT_INVALID         0x02002b35，超时时间档位非法。
 * @retval #OS_ERROR_MSGM_SYN_DST_CORE_INVALID    0x02002b34，目标核无效。
 * @retval #OS_ERROR_MSGM_SYN_RECV_MODE_INVALID   0x02002b36，同步接受模式非法。
 * @retval #OS_ERROR_MSGM_SYN_DES_ADDR_INVALID    0x02002b37，消息发送目标地址非法。
 * @retval #OS_ERROR_MSGM_SYN_MSG_INVALID         0x02002b3d，消息错误。
 * @retval #OS_ERROR_MSGM_SYN_DATA_MODE_INVALID   0x02002b57，配置发送消息数据模式非法。
 * @retval #OS_ERROR_MSGM_SYN_CMP_WORD_INVALID    0x02002b58，配置匹配word值非法。
 * @retval #SRE_OK                                0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueClose
 */
extern UINT32 SRE_MsgmSynQueOpen(UINT32 uwQueID, SRE_SYN_QUE_ATTR_S * pstSynQueAttr, QUE_HANDLE_T * phQueue);

/**
 * @ingroup SRE_msgm
 * @brief 关闭同步消息队列接口。
 *
 * @par 描述:
 * 关闭hQueue所对应的消息队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>重复关闭已经关闭的同步消息队列，返回SRE_OK。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开、关闭、启动、停止同一队列的情形，用户需在外层进行锁保护。</li>
 * <li>这里的关闭只是简单地进行stop操作，需要用户保证close后不再进行start等重新启动同步的操作 </li>
 * <li>SD6183平台由用户保证有通道组 VMID权限调用该接口。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID     0x02002b2f，传入的handle无效。
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED         0x02002b31，同步消息队列未打开。
 * @retval #SRE_OK                               0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueOpen
 */
#define SRE_MsgmSynQueClose(hQueue)  SRE_MsgmSynQueStop(hQueue)

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列启动接口。
 *
 * @par 描述:
 * 启动hQueue所对应的消息队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开、关闭、启动、停止同一队列的情形，用户需在外层进行锁保护。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID        0x02002b2f，传入的handle无效。
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED            0x02002b31，同步消息队列未打开。
 * @retval #SRE_OK                                  0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueStop
 */
extern UINT32 SRE_MsgmSynQueStart(QUE_HANDLE_T hQueue);

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列停止接口。
 *
 * @par 描述:
 * 停止hQueue所对应的消息队列。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>该接口内部无核间锁保护，对于可能出现多核同时打开、关闭、启动、停止同一队列的情形，用户需在外层进行锁保护。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID        0x02002b2f，传入的handle无效。
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED            0x02002b31，同步消息队列未打开。
 * @retval #SRE_OK                                  0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueStart
 */
extern UINT32 SRE_MsgmSynQueStop(QUE_HANDLE_T hQueue);

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列消息发送接口。
 *
 * @par 描述:
 * 向hQueue对应的队列发送同步消息。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 * @param auwData       [IN] UINT32*，发送消息数据。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID        0x02002b2f，handle无效。
 * @retval #OS_ERROR_MSGM_SYN_NOT_GOING             0x02002b3c，不在同步进行中。
 * @retval #OS_ERROR_MSGM_SYN_MSG_PTR_NULL          0x02002b3b，数据地址为空。
 * @retval #SRE_OK                                  0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmSynQueSend(QUE_HANDLE_T hQueue, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列统计接口。
 *
 * @par 描述:
 * 查询hQueue对应队列当前统计计数。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * <li>在没有发过同步消息，或者同步完成的情况下，SD6182/SD6157平台返回的剩余消息个数为同步计数，而SD6183平台返回的为0。</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T，同步消息队列handle。
 * @param puwSynMsgCnt  [OUT] UINT32*，剩余消息个数。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID     0x02002b2f，handle无效。
 * @retval #OS_ERROR_MSGM_SYN_MSGCNT_NULL        0x02002b3a，返回地址指针为空。
 * @retval #OS_ERROR_MSGM_SYN_NOT_GOING          0x02002b3c，不在同步进行中。
 * @retval #SRE_OK                               0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmSynQueStatics(QUE_HANDLE_T hQueue, UINT32 * puwSynMsgCnt);

/**
 * @ingroup SRE_msgm
 * @brief 同步消息队列消息入口地址获取函数接口。
 *
 * @par 描述:
 * 获取指定同步消息队列的消息入口地址。
 * @attention
 * <ul>
 * <li>适用于SD6182、SD6157、SD6183平台。</li>
 * </ul>
 *
 * @param hQueue       [IN] 类型#QUE_HANDLE_T，同步消息队列handle。
 * @param pQueAddr     [OUT] 类型#VOID *，返回的同步消息队列入口地址。
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID     0x02002b2f，handle无效。
 * @retval #OS_ERROR_MSGM_SYN_ADDR_GET_NULL      0x02002b46，地址为空。
 * @retval #SRE_OK                               0x00000000，获取地址成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmSynQueAddrGet(QUE_HANDLE_T hQueue, VOID * pQueAddr);

#if ((OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HIDSP))
/**
 * @ingroup SRE_msgm
 * @brief MSGM DFX异常接管初始化配置接口。
 *
 * @par 描述:
 * 该接口初始化MSGM错误异常相关寄存器，创建并使能错误处理硬中断。
 * @attention
 * <ul>
 * <li>GMSGM初始化负责GMSGM DFX寄存器初始化配置以及错误中断创建，LMSGM初始化只负责LMSGM DFX寄存器初始化配置。</li>
 * <li>GMSGM只能初始化配置一次，可以在SRE_AppInit或之后调用。</li>
 * <li>LMSGM可做多次初始化配置，但必须在GMSGM初始化之后进行(否则可能出现未接管中断)，请用户自行保证。</li>
 * <li>该接口不做GIC通道配置，MSGM错误异常接管功能需要在GIC配通之后才能正式生效。</li>
 * <li>该接口内部对MSGM的硬件配置没有核间锁保护，对于可能出现多核同时配置的场景，用户保证串行操作。</li>
 * <li>OS对LMSGM是否被低功耗关断不做判断，用户请自行保证。</li>
 * <li>必须主控核调用该接口。</li>
 * </ul>
 *
 * @param uwMsgmID      [IN] UINT32，待初始化复位的MSGM，有效值为SRE_GLOBAL_MSGM或SRE_LOCAL_MSGM(SRE_LOCAL_MSGM只对SD6182/SD6183有效)。
 *
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED                 0x02001402，硬中断已被创建或相应中断向量号已被其它中断占用。
 * @retval #OS_ERRNO_HWI_MEMORY_ALLOC_FAILED             0x02001408，组合型中断节点申请私有静态内存失败。
 * @retval #OS_ERRNO_HWI_COMBINEHOOK_ALREADY_CREATED     0x02001409，组合型中断已创建了相同的中断处理函数。
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL                     0x02002b16，指定的MSGM ID非法。
 * @retval #SRE_OK                                       0x00000000，获取地址成功。
 *
 * @par 依赖:
 * <ul><li>sre_msgm.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see 无
 */
extern UINT32 SRE_MsgmDfxInit(UINT32 uwMsgmID);
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_MSGM_H */




