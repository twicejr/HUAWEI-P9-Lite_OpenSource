/**
 * @file sre_task.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：任务模块的对外头文件。 \n
 */

 /**@defgroup SRE_task 任务基本功能
  *@ingroup SRE_kernel
 */

#ifndef _SRE_TASK_H
#define _SRE_TASK_H

#include "sre_base.h"
#include "sre_hook.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_task
 * 任务名的最大长度。
 *
 * 任务名的最大长度，包括结尾符'\0'。
 */
#define OS_TSK_NAME_LEN                                     16

/**
 * @ingroup SRE_task
 * 任务的消息队列最大的个数。
 *
 */
#define OS_TSK_MSGQ_MAX                                     8


/**
 * @ingroup SRE_task
 * 空任务ID。
 *
 * 调用SRE_TaskYield时，使用OS_TSK_NULL_ID，由OS选择就绪队列中的第一个任务。
 */
#define OS_TSK_NULL_ID                                      0xFFFFFFFF


/**
 * @ingroup SRE_task
 * Balong AX支持的优先级为(0~63)，其他平台芯片支持的优先级(0~31)，OS系统IDLE线程使用最低优先级(63或31)，用户不能使用。
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_00                                  0

/**
* @ingroup SRE_task
* 可用的任务优先级宏定义。
*
*/

#define OS_TSK_PRIORITY_01                                  1

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_02                                  2

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_03                                  3

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_04                                  4

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_05                                  5

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_06                                  6

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_07                                  7

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_08                                  8

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_09                                  9

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_10                                  10

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_11                                  11

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_12                                  12

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_13                                  13

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_14                                  14

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_15                                  15

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_16                                  16

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_17                                  17

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_18                                  18

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_19                                  19

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_20                                  20

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_21                                  21

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_22                                  22

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_23                                  23

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_24                                  24

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_25                                  25

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_26                                  26

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_27                                  27

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_28                                  28

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_29                                  29

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_30                                  30

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_31                                  31

/**
 * @ingroup SRE_task
 * Cortex-AX支持的优先级为(0~63),下面优先级是32~63。
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_32                                  32

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_33                                  33

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_34                                  34

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_35                                  35

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_36                                  36

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_37                                  37

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_38                                  38

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_39                                  39

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_40                                  40

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_41                                  41

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_42                                  42

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_43                                  43

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_44                                  44

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_45                                  45

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_46                                  46

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_47                                  47

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_48                                  48

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_49                                  49

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_50                                  50

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_51                                  51

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_52                                  52

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_53                                  53

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_54                                  54

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_55                                  55

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_56                                  56

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_57                                  57

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_58                                  58

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_59                                  59

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_60                                  60

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_61                                  61

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_62                                  62

/**
 * @ingroup SRE_task
 * 可用的任务优先级宏定义。
 *
 */
#define OS_TSK_PRIORITY_63                                  63


/**
 * @ingroup SRE_task
 * 最小任务栈大小。
 *
 * 若指定的任务栈大小低于此值（任务上下文大小向上16字节对齐），任务将创建失败。
 * 该项只是包含任务上下文预留的栈空间，任务调度时额外的任务开销需要由用户自行保证足够的任务栈空间配置, 不确定情况下建议使用默认任务栈大小配置。
 */
#define OS_TSK_MIN_STACK_SIZE                               (ALIGN(0x1D0, 16))


/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务控制块未被使用。
 */
#define OS_TSK_UNUSED                                       0x0001

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务被挂起。
 */
#define OS_TSK_SUSPEND                                      0x0004

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务被阻塞（等待信号量）。
 */
#define OS_TSK_PEND                                         0x0008

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务在等待信号量或者事件的标志。
 */
#define OS_TSK_TIMEOUT                                      0x0010

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务被延时。
 */
#define OS_TSK_DELAY                                        0x0020

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务已就绪，已加入就绪队列。
 */
#define OS_TSK_READY                                        0x0040

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务正运行，仍在就绪队列。
 */
#define OS_TSK_RUNNING                                      0x0080

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务被阻塞（等待快速信号量）。
 */
#define OS_TSK_FSEM_PEND                                    0x0100
/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务被阻塞（等待消息）。
 */

#define OS_TSK_MSG_PEND                                     0x0200
/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务被阻塞（等待核间信号量）。
 */
#define OS_TSK_MCSEM_PEND                                   0x0400

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * OS_TSK_EVENT_PEND      --- 任务阻塞于等待读事件。
 */
#define OS_TSK_EVENT_PEND                                   0x0800

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * OS_TSK_EVENT_TYPE    --- 任务读事件类型，0:ANY; 1:ALL。
 */
#define OS_TSK_EVENT_TYPE                                   0x1000


/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * OS_TSK_QUEUE_PEND      --- 任务阻塞与等待队列。
 */
#define OS_TSK_QUEUE_PEND                                   0x2000

/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * OS_TSK_QUEUE_BUSY      --- 队列正在读写数据。
 */
#define OS_TSK_QUEUE_BUSY                                   0x4000

#if (OS_OPTION_KERNEL_PROCESS == YES) 
/**
 * @ingroup SRE_task
 * 任务进程控制块状态标志。
 *
 * OS_TSK_SLEEP           --- 任务进程处于休眠状态
 */
#define OS_TSK_SLEEP                                        0x8000

#endif

#if  (OS_OPTION_COPROCESSOR == YES)
/**
 * @ingroup SRE_task
 * 任务或任务控制块状态标志。
 *
 * 任务使用coprocessor的矢量寄存器现场已保存。
 */
#define OS_TSK_CP_CONTEXT_SAVED                             0x0002
#endif

/**
 * @ingroup SRE_task
 * 任务切换类型。
 *
 * 任务快速切换。
 */
#define OS_TSK_FAST_TRAP                                    0x1

/**
 * @ingroup SRE_task
 * 任务切换类型。
 *
 * 任务普通切换。
 */
#define OS_TSK_NORMAL_TRAP                                  0x0


/*
 * 任务模块的错误码定义。
 */
/**
 * @ingroup SRE_task
 * 任务错误码：申请内存失败。
 *
 * 值: 0x02000800
 *
 * 解决方案: 分配更大的私有FSC内存分区
 *
 */
#define OS_ERRNO_TSK_NO_MEMORY                              SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x00)

/**
 * @ingroup SRE_task
 * 任务错误码：指针参数为空。
 *
 * 值: 0x02000801
 *
 * 解决方案: 检查参数指针是否为NUL。
 */
#define OS_ERRNO_TSK_PTR_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x01)

/**
 * @ingroup SRE_task
 * 任务错误码：任务栈大小未按16字节大小对齐。
 *
 * 值: 0x02000802
 *
 * 解决方案: 检查入参任务栈大小是否按16字节对齐。
 */
#define OS_ERRNO_TSK_STKSZ_NOT_ALIGN                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x02)

/**
 * @ingroup SRE_task
 * 任务错误码：任务优先级非法。
 *
 * 值: 0x02000803
 *
 * 解决方案: 检查入参任务优先级Balong平台不能大于63，其他平台不能大于31。
 */
#define OS_ERRNO_TSK_PRIOR_ERROR                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x03)

/**
 * @ingroup SRE_task
 * 任务错误码：任务入口函数为空。
 *
 * 值: 0x02000804
 *
 * 解决方案: 检查入参任务入口函数是否为NULL。
 */
#define OS_ERRNO_TSK_ENTRY_NULL                             SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x04)

/**
 * @ingroup SRE_task
 * 任务错误码：任务名的指针为空或任务名为空字符串。
 *
 * 值: 0x02000805
 *
 * 解决方案: 检查任务名指针和任务名。
 */
#define OS_ERRNO_TSK_NAME_EMPTY                             SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x05)

/**
 * @ingroup SRE_task
 * 任务错误码：指定的任务栈空间太小。
 *
 * 值: 0x02000806
 *
 * 解决方案: 检查任务栈是否小于OS_TSK_MIN_STACK_SIZE。
 */
#define OS_ERRNO_TSK_STKSZ_TOO_SMALL                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x06)

/**
 * @ingroup SRE_task
 * 任务错误码：任务ID非法。
 *
 * 值: 0x02000807
 *
 * 解决方案: 检查当前运行任务的PID是否超过任务最大数或检查用户入参任务PID是否合法。
 */
#define OS_ERRNO_TSK_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x07)

/**
 * @ingroup SRE_task
 * 任务错误码：任务已被挂起。
 *
 * 值: 0x02000808
 *
 * 解决方案: 检查所挂起任务是否为已挂起任务。
 */
#define OS_ERRNO_TSK_ALREADY_SUSPENDED                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x08)

/**
 * @ingroup SRE_task
 * 任务错误码：任务未被挂起。
 *
 * 值: 0x02000809
 *
 * 解决方案: 检查所恢复任务是否未挂起。
 */
#define OS_ERRNO_TSK_NOT_SUSPENDED                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x09)

/**
 * @ingroup SRE_task
 * 任务错误码：任务未创建。
 *
 * 值: 0x0200080a
 *
 * 解决方案: 检查任务是否创建。
 */
#define OS_ERRNO_TSK_NOT_CREATED                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0a)

/**
 * @ingroup SRE_task
 * 任务错误码：在锁任务的状态下删除当前任务。
 *
 * 值: 0x0300080b
 *
 *解决方案: 用户确保删除任务时，将任务解锁。
 *
 */
#define OS_ERRNO_TSK_DELETE_LOCKED                          SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x0b)

/**
 * @ingroup SRE_task
 * 任务错误码：任务待处理的消息数非零。
 *
 * 值: 0x0200080c
 *
 * 解决方案: 检查所删除任务是否尚有未处理的消息。
 */
#define OS_ERRNO_TSK_MSG_NONZERO                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0c)

/**
 * @ingroup SRE_task
 * 任务错误码：在硬中断或软中断的处理中进行延时操作。
 *
 * 值: 0x0300080d
 *
 *解决方案: 此操作禁止在中断中进行调度。
 *
 */
#define OS_ERRNO_TSK_DELAY_IN_INT                           SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x0d)

/**
 * @ingroup SRE_task
 * 任务错误码：在锁任务的状态下进行延时操作。
 *
 * 值: 0x0200080e
 *
 * 解决方案: 检查是否锁任务。
 */
#define OS_ERRNO_TSK_DELAY_IN_LOCK                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0e)

/**
 * @ingroup SRE_task
 * 任务错误码：任务ID不在Yield操作指定的优先级队列中。
 *
 * 值: 0x0200080f
 *
 * 解决方案: 检查操作的任务的优先级。
 */
#define OS_ERRNO_TSK_YIELD_INVALID_TASK                     SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0f)

/**
 * @ingroup SRE_task
 * 任务错误码：Yield操作指定的优先级队列中，就绪任务数小于2。
 *
 * 值: 0x02000810
 *
 * 解决方案: 检查指定优先级就绪任务，确保就绪任务数大于1。
 */
#define OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK                  SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x10)

/**
 * @ingroup SRE_task
 * 任务错误码：没有可用的任务控制块资源或配置项中任务裁剪关闭。
 *
 * 值: 0x02000811
 *
 * 解决方案: 打开配置项中任务裁剪开关，并配置足够大的任务资源数。
 */
#define OS_ERRNO_TSK_TCB_UNAVAILABLE                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x11)

/**
 * @ingroup SRE_task
 * 任务错误码：任务钩子不匹配，即要删除的钩子未注册或已取消。
 *
 * 值: 0x02000812
 *
 * 解决方案: 检查钩子是否已注册。
 */
#define OS_ERRNO_TSK_HOOK_NOT_MATCH                         SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x12)


/**
 * @ingroup SRE_task
 * 任务错误码：操作IDLE任务。
 *
 * 值: 0x02000814
 *
 * 解决方案: 检查是否操作IDLE任务。
 */
#define OS_ERRNO_TSK_OPERATE_IDLE                           SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x14)

/**
 * @ingroup SRE_task
 * 任务错误码：在锁任务的状态下挂起当前任务。
 *
 * 值: 0x03000815
 *
 *解决方案: 确保任务挂起的时候，任务已经解锁。
 *
 */
#define OS_ERRNO_TSK_SUSPEND_LOCKED                         SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x15)

/**
 * @ingroup SRE_task
 * 任务错误码：释放任务栈失败。
 *
 * 值: 0x02000817
 *
 * 解决方案: 检查是否踩内存导致内存块不能释放。
 */
#define OS_ERRNO_TSK_FREE_STACK_FAILED                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x17)

/**
 * @ingroup SRE_task
 * 任务错误码：任务栈区间配置太小。
 *
 * 值: 0x02000818
 *
 * 解决方案: 在sre_config.h中配置任务栈大小超过OS_TSK_MIN_STACK_SIZE 。
 */
#define OS_ERRNO_TSK_STKAREA_TOO_SMALL                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x18)

/**
 * @ingroup SRE_task
 * 任务错误码：系统初始化任务激活失败。
 *
 * 值: 0x02000819
 *
 * 解决方案: 查看任务栈是否配置错误。
 *
 */
#define OS_ERRNO_TSK_ACTIVE_FAILED                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x19)

/**
 * @ingroup SRE_task
 * 任务错误码：配置的任务数量太多，配置的最大任务个数不能大于254减去配置的软中断个数，总任务个数不包括Idle任务且不能为0。
 *
 * 值: 0x0200081a
 *
 * 解决方案: 在任务配置项中将最大任务数改为小于等于254减去配置的软中断个数且大于0。
 */
#define OS_ERRNO_TSK_MAX_NUM_NOT_SUITED                     SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1a)

/**
 * @ingroup SRE_task
 * 任务错误码：任务的coprocessor上下文保存区域未按16字节对齐。
 *
 * 值: 0x0200081b
 *
 * 解决方案: 检查保存区起始地址是否16字节对齐。
 */
#define OS_ERRNO_TSK_CP_SAVE_AREA_NOT_ALIGN                 SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1b)

/**
 * @ingroup SRE_task
 * 任务错误码：任务的MSG队列个数超过8。
 *
 * 值: 0x0200081d
 *
 * 解决方案: 确认任务创建的消息队列数不超过8。
 */
#define OS_ERRNO_TSK_MSG_Q_TOO_MANY                         SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1d)

/**
 * @ingroup SRE_task
 * 任务错误码：任务的coprocessor上下文保存区域的地址为空指针。
 *
 * 值: 0x0200081e
 *
 * 解决方案: 检查保存区起始地址是否为NULL。
 */
#define OS_ERRNO_TSK_CP_SAVE_AREA_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1e)

/**
 * @ingroup SRE_task
 * 任务错误码：任务自删除时释放未接收消息的内存失败。
 *
 * 值: 0x0200081f
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_TSK_SELF_DELETE_ERR                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1f)

/**
 * @ingroup SRE_task
 * 任务错误码：获取任务信息时，用户实际欲获取任务数为0。
 *
 * 值: 0x02000821
 *
 * 解决方案: 获取任务信息时，用户实际输入的欲获取任务数不为0。
 */
#define OS_ERRNO_TSK_INPUT_NUM_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x21)


/**
 * @ingroup SRE_task
 * 任务错误码：用户配置的任务栈首地址未16字节对齐。
 *
 * 值: 0x02000822
 *
 * 解决方案: 配置进来任务栈首地址需16字节对齐。
 */
#define OS_ERRNO_TSK_STACKADDR_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x22)

/**
 * @ingroup SRE_task
 * 任务错误码：任务正在操作队列。
 *
 * 值: 0x02000823
 *
 * 解决方案: 让被删除的任务得到调度读取完队列数据，即可删除。
 */
#define OS_ERRNO_TSK_QUEUE_DOING                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x23)

/**
 * @ingroup SRE_task
 * 任务错误码：任务发生优先级继承。
 *
 * 值: 0x02000824
 *
 * 解决方案: 等待任务恢复优先级后再尝试设置任务的优先级。
 */
#define OS_ERRNO_TSK_PRIORITY_INHERIT                       SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x24)

/**
 * @ingroup SRE_task
 * 任务错误码：任务阻塞在互斥信号量上。
 *
 * 值: 0x02000825
 *
 * 解决方案: 等待任务恢复调度后再尝试设置任务的优先级。
 */
#define OS_ERRNO_TSK_PEND_ON_MUTEX                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x25)

/**
 * @ingroup SRE_task
 * 任务错误码：任务删除时持有互斥信号量。
 *
 * 值: 0x02000826
 *
 * 解决方案: 删除任务时必须将其持有的互斥信号量释放。
 */
#define OS_ERRNO_TSK_HAVE_MUTEX_SEM                         SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x26)

/**
 * @ingroup SRE_task
 * 任务错误码：任务退出时没有完全释放资源。
 *
 * 值: 0x03000827
 *
 *解决方案: 任务退出前确保完全释放其占有的资源(如消息，互斥信号量等)。
 *
 */
#define OS_ERRNO_TSK_EXIT_WITH_RESOURCE                     SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x27)

/**
 * @ingroup SRE_task
 * 任务错误码：任务设置优先级时低于阻塞在它持有的互斥信号量的最高优先级任务的优先级。
 *
 * 值: 0x02000828
 *
 *解决方案: 重设优先级时不能低于阻塞在目标任务持有的互斥信号量的最高优先级任务的优先级。
 *
 */
#define OS_ERRNO_TSK_PRIOR_LOW_THAN_PENDTSK                 SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x28)

/**
 * @ingroup SRE_task
 * 任务错误码：不能在当前正在运行的任务中获取当前任务的上下文信息。
 *
 * 值: 0x02000829
 *
 *解决方案: 需要在中断中获取任务的上下文信息或者当前运行任务中获取其他任务的任务上下文信息。
 *
 */
#define OS_ERRNO_TSK_CONTEXT_NOT_GETED                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x29)

/**
 * @ingroup SRE_task
 * 任务错误码：创建线程时没有可使用的GTID资源分配。
 *
 * 值: 0x0200082a
 *
 * 解决方案: 检查当前创建的线程过多，分配资源数不够。
 */
#define OS_ERRNO_TSK_NO_GTID_ALLOC_RESOURCE                 SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x2a)


/**
 * @ingroup SRE_process
 * 任务错误码：进程中删除线程时线程TID对应的GTID资源不存在。
 *
 * 值: 0x0200082b
 *
 * 解决方案: 检查当前进程中的删除的线程TID是否存在。
 */
#define OS_ERRNO_TSK_NO_GTID_RESOURCE_DEL                   SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x2b)

/**
 * @ingroup SRE_process
 * 任务错误码：没有任务调度请求
 *
 * 值: 0x0200082c
 *
 * 解决方案: 检查进程任务idle下是否存在其他用户进程切换。
 */
#define OS_ERRNO_TSK_NO_SCHEDULE_REQ                       SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x2c)


/**
 * @ingroup SRE_task
 * 任务ID的类型定义。
 */
typedef UINT32                                              TSK_HANDLE_T;

/**
 * @ingroup SRE_task
 * 任务优先级的类型定义。
 */
typedef UINT16                                              TSK_PRIOR_T;

/**
 * @ingroup SRE_task
 * 任务状态的类型定义。
 */
typedef UINT16                                              TSK_STATUS_T;

/**
 * @ingroup SRE_task
 * 任务栈信息的结构体定义。
 *
 * 保存任务栈的信息。
 */
typedef struct tagStackInfo
{
    UINT32 uwTop;                                           /**< 栈顶                       */
    UINT32 uwBottom;                                        /**< 栈底                       */
    UINT32 uwSP;                                            /**< 栈当前SP指针值             */
    UINT32 uwCurrUsed;                                      /**< 栈当前使用的大小           */
    UINT32 uwPeakUsed;                                      /**< 栈使用的历史峰值           */
    BOOL   bOvf;                                            /**< 栈是否溢出                 */
} STACK_INFO_S;

/**
* @ingroup  SRE_task
* @brief 任务入口函数类型定义。
*
* @par 描述:
* 用户通过任务入口函数类型定义任务入口函数，在任务创建触发之后调用该函数进行任务执行。
* @attention 无。
*
* @param  uwParam1 [IN] 类型#UINT32，传递给任务处理函数的第一个参数。
* @param  uwParam2 [IN] 类型#UINT32，传递给任务处理函数的第二个参数。
* @param  uwParam3 [IN] 类型#UINT32，传递给任务处理函数的第三个参数。
* @param  uwParam4 [IN] 类型#UINT32，传递给任务处理函数的第四个参数。
*
* @retval 无。
* @par 依赖:
* <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see 无。
*/
typedef VOID (* TSK_ENTRY_FUNC)( UINT32 uwParam1,
                                 UINT32 uwParam2,
                                 UINT32 uwParam3,
                                 UINT32 uwParam4 );
/**
 * @ingroup  SRE_task
 * @brief 任务创建钩子函数类型定义。
 *
 * @par 描述:
 * 用户通过任务创建钩子函数类型定义任务创建钩子，在系统创建任务时，调用该钩子。
 * @attention 无。
 *
 * @param  puwTaskPID [IN] 类型#UINT32，新创建任务的PID。
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无。
 */
typedef UINT32 (* TSK_CREATE_HOOK)(UINT32 uwTaskPID);

/**
* @ingroup  SRE_task
* @brief 任务删除钩子函数类型定义。
*
* @par 描述:
* 用户通过任务删除钩子函数类型定义任务删除钩子，在系统对任务进行删除时，调用该钩子。
* @attention 无。
*
* @param  puwTaskPID [IN] 类型#UINT32，删除任务的PID。
*
* @retval 无。
* @par 依赖:
* <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see 无。
*/
typedef UINT32 (* TSK_DELETE_HOOK)(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_task
 * @brief 任务切换钩子函数类型定义。
 *
 * @par 描述:
 * 用户通过任务切换钩子函数类型定义任务切换钩子，在系统对任务进行切换时，调用该钩子。
 * @attention 无。
 *
 * @param  uwLastTaskPID [IN] 类型#UINT32，上一个任务的PID。
 * @param  uwNextTaskPID [IN] 类型#UINT32，下一个任务的PID。
 *
 * @retval 无。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无。
 */
typedef UINT32 (* TSK_SWITCH_HOOK)(UINT32 uwLastTaskPID, UINT32 uwNextTaskPID);

/**
 * @ingroup SRE_task
 * 任务模块配置信息的结构体定义。
 *
 * 保存任务模块的配置项信息。
 */
typedef struct tagTskModInfo
{
    UINT32 uwMaxNum;                /**< 最大支持的任务数           */
    UINT32 uwDefaultSize;           /**< 缺省的任务栈大小           */
    UINT32 uwIdleStackSize;         /**< Idle任务的任务栈大小       */
    UINT32 uwStackAreaAddr;         /**< 任务栈区间的起始地址       */
    UINT32 uwStackAreaSize;         /**< 任务栈区间的大小           */
    UINT32 uwMagicWord;             /**< 任务栈初始化魔术           */
} TSK_MOD_INFO_S;

/**
 * @ingroup SRE_task
 * 任务创建参数的结构体定义。
 *
 * 传递任务创建时指定的参数信息。
 */
typedef struct tagTskInitParam
{
   TSK_ENTRY_FUNC pfnTaskEntry;     /**< 任务入口函数               */
   TSK_PRIOR_T    usTaskPrio;       /**< 任务优先级                 */
   UINT16 usQNum;                   /**< 消息队列数                 */
   UINT32 auwArgs[4];               /**< 任务参数，最多4个          */
   UINT32 uwStackSize;              /**< 任务栈的大小               */
   CHAR  *pcName;                   /**< 任务名                     */
   UINT32 uwStackAddr;              /**< 本任务的任务栈独立配置起始地址，用户必须对该成员进行初始化，若配置为0表示从系统内部空间分配，否则用户指定栈起始地址 */
   UINT32 uwPrivateData;            /**< 专属于本任务的私有数据     */
} TSK_INIT_PARAM_S;

/**
 * @ingroup SRE_task
 * 任务信息的结构体定义。
 *
 * 用户可以查询的任务信息。
 */

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_task
 * CORTEX_AX平台任务上下文的结构体定义。
 */
typedef struct tagTskContext
{
    UINT32 auwR[13];               /**< 当前物理寄存器R0-R12 */
    UINT32 uwPC;                   /**< 程序计数器           */
    UINT32 uwLR;                   /**< 即R14链接寄存器      */
    UINT32 uwCPSR;                 /**< 当前程序状态寄存器   */
} TSK_CONTEXT_S;

#endif


#if ( (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup SRE_task
 * Xtensa 平台任务上下文的结构体定义。
 */
typedef struct tagTskContext
{
    UINT32 auwA[16];                /**< 当前窗口的a0-a15               */
    UINT32 uwPC;                    /**< 程序计数器                     */
    UINT32 uwPS;                    /**< 程序状态寄存器                 */
    UINT32 uwLBEG;                  /**< Loop Begin寄存器               */
    UINT32 uwLEND;                  /**< Loop End寄存器                 */
    UINT32 uwLCOUNT;                /**< Loop Count寄存器               */
    UINT32 uwSAR;                   /**< 移位数寄存器                   */
} TSK_CONTEXT_S;
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup SRE_task
 * OS_HIDSP平台任务上下文的结构体定义。
 */
typedef struct tagTskContext
{
    UINT32 uwTrapType;                 /**< OS_TSK_NORMAL_TRAP:正常切换; OS_TSK_FAST_TRAP: 快速切换   */
    UINT32 uwLBEG0;                    /**< Loop Begin0寄存器               */
    UINT32 uwLEND0;                    /**< Loop End0寄存器                 */
    UINT32 uwLCOUNT0;                  /**< Loop Count0寄存器               */
    UINT32 uwReserve0;                 /**< 保留                            */
    UINT32 uwLBEG1;                    /**< Loop Begin1寄存器               */
    UINT32 uwLEND1;                    /**< Loop End1寄存器                 */
    UINT32 uwLCOUNT1;                  /**< Loop Count1寄存器               */
    UINT32 uwReserve1;                 /**< 保留                            */
    UINT32 auwA[32];                   /**< a0-a31寄存器                    */
    UINT32 uwPC;                       /**< 程序计数器                      */
    UINT32 uwSR;                       /**< 程序状态寄存器                  */
} TSK_CONTEXT_S;

#endif

/**@ingroup SRE_task
 * 任务信息结构体
 */
typedef struct tagTskInfo
{
   UINT32 uwSP;                     /**< 任务切换时的SP             */
   UINT32 uwPC;                     /**< 任务切换时的PC             */
   TSK_STATUS_T usTaskStatus;       /**< 任务状态                   */
   TSK_PRIOR_T  usTaskPrio;         /**< 任务优先级                 */
   UINT32 uwStackSize;              /**< 任务栈的大小               */
   UINT32 uwTopOfStack;             /**< 任务栈的栈顶               */
   UINT32 uwNumOfMsg;               /**< 任务接收到的消息数         */
   CHAR   acName[OS_TSK_NAME_LEN];  /**< 任务名                     */
} TSK_INFO_S;

/**@ingroup SRE_task
 * 任务栈查询结构体
 */
typedef struct tagStackTask
{
    UINT32 uwID;             /**< 任务ID                                          */
    UINT32 uwSize;           /**< 该任务使用的栈峰值，如果栈越界则用0xFFFFFFFF表示*/
} OS_STACK_TASK_S;

/**@ingroup SRE_task
 * 任务TCB首地址信息结构体。
 */
typedef struct tagTcbAddr
{
    UINT32 uwTskID;         /**< 任务ID                  */
    VOID* pTcbAddr;         /**< 任务TCB首地址           */
} TSK_TCB_ADDR_S;

///@cond
/**@ingroup SRE_task
* 对外任务控制块的结构体
* pStackPointer、usTaskStatus、usPriority的位置不能变动，汇编中已写死。
*
typedef struct tagMsgQHead
{
    UINT32 uwMsgNum;
    LIST_OBJECT_S stMsgList;
} MSG_QHead_S;

typedef struct tagListObject
{
    struct tagListObject *pstPrev;
    struct tagListObject *pstNext;
} LIST_OBJECT_S;

typedef struct tagPublicTskCB
{
    VOID               *pStackPointer;              // 当前任务的SP
    TSK_STATUS_T        usTaskStatus;               // 任务状态
    TSK_PRIOR_T         usPriority;                 // 任务的运行优先级
    UINT32              uwStackSize;                // 任务栈大小
    UINT32              uwTopOfStack;               // 任务栈顶
    TSK_HANDLE_T        uwTaskPID;                  // 任务PID
    TSK_ENTRY_FUNC      pfnTaskEntry;               // 任务入口函数
    VOID               *pTaskSem;                   // 任务Pend的信号量指针
    INT32               swFsemCount;                // 快速信号量计数
    UINT32              auwArgs[4];                 // 任务的参数
#if (OS_OPTION_COPROCESSOR == YES)                  // 只有SD6108/SD6181/SD6182平台才有该功能
    VOID               *pCpSaveAreaA;               // 矢量寄存器缓存地址A
    VOID               *pCpSaveAreaB;               // 矢量寄存器缓存地址B
#endif
    TSK_PRIOR_T         usOrigPriority;             // 任务的原始优先级
    UINT16              usStackCfgFlg;              // 任务栈配置标记
    UINT16              usQNum;                     // 消息队列数
    UINT16              usRecvQID;                  // 期望接收消息的QID
    UINT32              uwPrivateData;              // 私有数据
    MSG_QHead_S        *pstMsgQ;                    // 指向消息队列数组
    LIST_OBJECT_S       stPendList;                 // 信号量链表指针
    LIST_OBJECT_S       stTimerList;                // 任务延时链表指针
    LIST_OBJECT_S       stSemBList;                 // 持有互斥信号量链表
    UINT64              ullExpirationTick;          // 任务恢复的时间点(单位Tick)
    UINT32              uwEvent;                    // 任务事件
    UINT32              uwEventMask;                // 任务事件掩码
    UINT32              uwLastErr;                  // 任务记录的最后一个错误码
    UINT32              uwReserved;                 // 增加一个PAD，保证TCB 8字节对齐
} TSK_CB_S;

*/
///@endcond

/**
 * @ingroup  SRE_task
 * @brief 创建任务。
 *
 * @par 描述:
 * 创建一个任务。在系统OS初始化前创建的任务只是简单地加入就绪队列。
 * 系统初始化后创建的任务，如果优先级高于当前任务且未锁任务，则立即发生任务调度并被运行，否则加入就绪队列。
 *
 * @attention
 * <ul>
 * <li>若指定的任务栈独立配置起始地址不为0，则采用用户配置的独立任务栈进行栈空间分配，并且系统会占用(消息队列个数乘以12字节)的空间用于消息队列头。</li>
 * <li>任务创建时，会对之前自删除任务的任务控制块和任务栈进行回收，用户独立配置的任务栈除外。</li>
 * <li>任务名的最大长度为16字节，含结束符。</li>
 * <li>创建任务时需要配置消息队列数。</li>
 * <li>同一核内任务名不允许重复，且不允许和软中断重名。</li>
 * <li>若指定的任务栈大小为0，则使用配置项#OS_TSK_DEFAULT_STACK_SIZE指定的默认的任务栈大小。</li>
 * <li>任务栈的大小必须按16字节大小对齐。确定任务栈大小的原则是，够用就行：多了浪费，少了任务栈溢出。具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>用户配置的任务栈首地址需16字节对齐，且配置的任务栈空间中，os会使用消息队列数乘以消息队列控制块的内存大小。</li>
 * <li>用户配置的任务栈空间需由用户保证其合法性，即对可cache空间的地址用户需要保证其任务栈首地址及栈大小cache line对齐，系统不做对齐处理，并在使用后需由用户进行释放。</li>
 * <li>任务创建时，任务创建参数中的任务栈大小配置建议不要使用最小任务栈大小OS_TSK_MIN_STACK_SIZE(大小为0x130)，该项只是包含任务上下文预留的栈空间，任务调度时额外的任务开销需要由用户自行保证足够的任务栈空间配置。</li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] 类型#UINT32 *，保存任务PID。
 * @param  pstInitParam [IN] 类型#TSK_INIT_PARAM_S *，任务创建参数，其结构体中的成员参数uwStackAddr传入时必须进行初始化，若不采用用户配置的独立任务栈进行栈空间分配，该成员必须初始化为0。
 *
 * @retval #OS_ERRNO_TSK_NO_MEMORY              0x02000800，申请内存失败。
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_STKSZ_NOT_ALIGN        0x02000802，任务栈大小未按16字节大小对齐。
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803，任务优先级非法。
 * @retval #OS_ERRNO_TSK_ENTRY_NULL             0x02000804，任务入口函数为空。
 * @retval #OS_ERRNO_TSK_NAME_EMPTY             0x02000805，任务名的指针为空或任务名为空字符串。
 * @retval #OS_ERRNO_TSK_STKSZ_TOO_SMALL        0x02000806，指定的任务栈空间太小。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_SUSPENDED          0x02000809，任务未被挂起。
 * @retval #OS_ERRNO_TSK_FREE_STACK_FAILED      0x02000817，释放任务栈失败。
 * @retval #OS_ERRNO_TSK_TCB_UNAVAILABLE        0x02000811，没有可用的任务控制块资源。
 * @retval #OS_ERRNO_TSK_MSG_Q_TOO_MANY         0x0200081d，任务的MSG队列个数超过8。
 * @retval #OS_ERRNO_HUNT_THREAD_NAME_REPEAT    0x02001f01，创建任务时，线程名重名。
 * @retval #OS_ERRNO_TSK_STACKADDR_NOT_ALIGN    0x02000822，创建任务时，用户配置任务栈地址未16字节对齐。
 * @retval #SRE_OK                              0x00000000，任务创建成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDelete | SRE_TaskCreateHookAdd | SRE_TaskCreateOnly
 */
extern UINT32 SRE_TaskCreate(UINT32 *puwTaskPID, TSK_INIT_PARAM_S *pstInitParam);


/**
 * @ingroup  SRE_task
 * @brief 创建任务，但不激活任务。
 *
 * @par 描述:
 * 创建一个任务。该任务不加入就绪队列，只处于挂起状态，用户需要激活该任务需要通过调用SRE_TaskResume函数将其激活。
 *
 * @attention
 * <ul>
 * <li>若指定的任务栈独立配置起始地址不为0，则采用用户配置的独立任务栈进行栈空间分配，并且系统会占用(usQNum * 12字节)的空间用于消息队列头。</li>
 * <li>任务创建时，会对之前自删除任务的任务控制块和任务栈进行回收，用户独立配置的任务栈除外。</li>
 * <li>任务名的最大长度为16字节，含结束符。</li>
 * <li>创建任务时需要配置消息队列数。</li>
 * <li>同一核内任务名不允许重复，且不允许和软中断重名。</li>
 * <li>若指定的任务栈大小为0，则使用配置项#OS_TSK_DEFAULT_STACK_SIZE指定的默认的任务栈大小。</li>
 * <li>任务栈的大小必须按16字节大小对齐。确定任务栈大小的原则是，够用就行：多了浪费，少了任务栈溢出。具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>用户配置的任务栈首地址需16字节对齐，且配置的任务栈空间中，os会使用消息队列数*消息队列控制块的内存大小。</li>
 * <li>用户配置的任务栈空间需由用户保证其合法性，即对可cache空间的地址用户需要保证其任务栈首地址及栈大小cache line对齐，系统不做对齐处理，并在使用后需由用户进行释放。</li>
 * <li>任务创建时，任务创建参数中的任务栈大小配置建议不要使用最小任务栈大小OS_TSK_MIN_STACK_SIZE(大小为0x130)，该项只是包含任务上下文预留的栈空间，任务调度时额外的任务开销需要由用户自行保证足够的任务栈空间配置。</li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] 类型#UINT32 *，保存任务PID。
 * @param  pstInitParam [IN] 类型#TSK_INIT_PARAM_S *，任务创建参数，其结构体中的成员参数uwStackAddr传入时必须进行初始化，若不采用用户配置的独立任务栈进行栈空间分配，该成员必须初始化为0。
 *
 * @retval #OS_ERRNO_TSK_NO_MEMORY              0x02000800，申请内存失败。
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_STKSZ_NOT_ALIGN        0x02000802，任务栈大小未按16字节大小对齐。
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803，任务优先级非法。
 * @retval #OS_ERRNO_TSK_ENTRY_NULL             0x02000804，任务入口函数为空。
 * @retval #OS_ERRNO_TSK_NAME_EMPTY             0x02000805，任务名的指针为空或任务名为空字符串。
 * @retval #OS_ERRNO_TSK_STKSZ_TOO_SMALL        0x02000806，指定的任务栈空间太小。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_TCB_UNAVAILABLE        0x02000811，没有可用的任务控制块资源。
 * @retval #OS_ERRNO_TSK_MSG_Q_TOO_MANY         0x0200081d，任务的MSG队列个数超过8。
 * @retval #OS_ERRNO_HUNT_THREAD_NAME_REPEAT    0x02001f01，创建任务时，线程名重名.
 * @retval #OS_ERRNO_TSK_STACKADDR_NOT_ALIGN    0x02000822，创建任务时，用户配置任务栈地址未16字节对齐.
 * @retval #SRE_OK                              0x00000000，任务创建成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDelete | SRE_TaskCreateHookAdd | SRE_TaskCreate
 */
extern UINT32 SRE_TaskCreateOnly(UINT32 *puwTaskPID, TSK_INIT_PARAM_S *pstInitParam);


/**
 * @ingroup  SRE_task
 * @brief 恢复任务。
 *
 * @par 描述:
 * 恢复挂起的任务。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>若任务仍处于延时、阻塞态，则只是取消挂起态，并不加入就绪队列。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 *
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #OS_ERRNO_TSK_NOT_SUSPENDED          0x02000809，任务未被挂起。
 * @retval #SRE_OK                              0x00000000，恢复任务成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSuspend
 */
extern UINT32 SRE_TaskResume(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief 挂起任务。
 *
 * @par 描述:
 * 挂起指定的任务，任务将从就绪队列中被删除。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>若为当前任务且已锁任务，则不能被挂起。</li>
 * <li>IDLE任务不能被挂起。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 *
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_ALREADY_SUSPENDED      0x02000808，任务已被挂起。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，操作IDLE任务。
 * @retval #OS_ERRNO_TSK_SUSPEND_LOCKED         0x03000815，在锁任务的状态下挂起当前任务。
 * @retval #SRE_OK                              0x00000000，挂起任务成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since  RTOSck V100R001C01
 * @see SRE_TaskResume | SRE_TaskLock
 */
extern UINT32 SRE_TaskSuspend(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief 删除任务。
 *
 * @par 描述:
 * 删除指定的任务，释放任务栈和任务控制块资源。
 *
 * @attention
 * <ul>
 * <li>若为自删除，则任务控制块和任务栈在下一次创建任务时才回收。</li>
 * <li>对于任务自删除，RTOSck处理该任务相关的信号量和接收到的消息会强制删除。</li>
 * <li>任务自删除时，删除钩子不允许进行pend信号量、挂起等操作。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 *
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #OS_ERRNO_TSK_DELETE_LOCKED          0x0300080b，在锁任务的状态下删除当前任务。
 * @retval #OS_ERRNO_TSK_MSG_NONZERO            0x0200080c，任务待处理的消息数非零。
 * @retval #OS_ERRNO_TSK_HAVE_MUTEX_SEM         0x02000826，任务持有互斥型信号量时删除该任务。
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，操作IDLE任务。
 * @retval #OS_ERRNO_TSK_QUEUE_DOING            0x02000823，任务正在操作队列。
 * @retval #SRE_OK                              0x00000000，删除任务成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCreate | SRE_TaskDeleteHookAdd
 */
extern UINT32 SRE_TaskDelete(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief 延迟正在运行的任务。
 *
 * @par 描述:
 * 延迟当前运行任务的执行。任务延时等待指定的Tick数后，重新参与调度。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>硬中断或软中断处理中，或已锁任务，则延时操作失败。</li>
 * <li>若传入参数0，且未锁任务调度，则顺取同优先级队列中的下一个任务执行。如没有同级的就绪任务，则不发生任务调度，继续执行原任务。</li>
 * </ul>
 *
 * @param  uwTick [IN] 类型#UINT32，延迟的Tick数。
 *
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803，任务优先级非法。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_YIELD_INVALID_TASK     0x0200080f，任务ID不在Yield操作指定的优先级队列中。
 * @retval #OS_ERRNO_TSK_DELAY_IN_INT           0x0300080d，在硬中断或软中断的处理中进行延时操作。
 * @retval #OS_ERRNO_TSK_DELAY_IN_LOCK          0x0200080e，在锁任务的状态下进行延时操作。
 * @retval #OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK  0x02000810，Yield操作指定的优先级队列中，就绪任务数小于2。
 * @retval #SRE_OK                              0x00000000，任务延时成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskYield
 */
extern UINT32 SRE_TaskDelay(UINT32 uwTick);


/**
 * @ingroup  SRE_task
 * @brief 锁任务调度。
 *
 * @par 描述:
 * 锁任务调度。若任务调度被锁，则不发生任务切换。
 *
 * @attention
 * <ul>
 * <li>只是锁任务调度，并不关中断，因此任务仍可被中断打断。</li>
 * <li>执行此函数则锁计数值加1，解锁则锁计数值减1。因此，必须与#SRE_TaskUnlock配对使用。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskUnlock
 */
extern VOID SRE_TaskLock(VOID);


/**
 * @ingroup  SRE_task
 * @brief 解锁任务调度。
 *
 * @par 描述:
 * 任务锁计数值减1。若嵌套加锁，则只有锁计数值减为0才真正的解锁了任务调度。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>执行此函数则锁计数值加1，解锁则锁计数值减1。因此，必须与#SRE_TaskLock配对使用。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskLock
 */
extern VOID SRE_TaskUnlock(VOID);


/**
 * @ingroup  SRE_task
 * @brief 获取当前任务PID。
 *
 * @par 描述:
 * 获取处于运行态的任务PID。
 *
 * @attention
 * <ul>
 * <li>硬中断或软中断处理中，也可获取当前任务PID，即被中断打断的任务。</li>
 * <li>在任务切换钩子处理中调用时，获取的是切入任务的ID。</li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] 类型#UINT32，保存任务PID。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务ID非法。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskStatusGet | SRE_TaskInfoGet
 */
extern UINT32 SRE_TaskSelf(UINT32 *puwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief 检查任务PID。
 *
 * @par 描述:
 * 检查任务PID是否合法。
 *
 * @attention
 * <ul>
 * <li>任务ID并不是从0开始编号的。</li>
 * <li>该接口只支持本核任务PID的检测。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 *
 * @retval #TRUE        1， 任务PID输入合法。
 * @retval #FALSE       0， 任务PID输入不合法。

 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSelf
 */
extern BOOL SRE_TaskIDCheck(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief 获取任务状态。
 *
 * @par 描述:
 * 获取指定任务的状态。
 *
 * @attention 无
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 *
 * @retval #(TSK_STATUS_T)OS_INVALID    返回失败。
 * @retval #任务状态 返回成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskInfoGet | SRE_TaskContextGet | SRE_TaskPrivateDataGet
 */
extern TSK_STATUS_T SRE_TaskStatusGet(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief 获取任务信息。
 *
 * @par 描述:
 * 获取指定任务的信息。
 *
 * @attention
 * <ul>
 * <li>若获取当前任务的信息，则只在硬中断、软中断、异常的处理中才有意义，否则获取的SP值和PC值是不准的。(在Xtensa平台下不允许在自身任务中获取上下文信息)</li>
 * <li>由于任务切换时，上下文信息也保存在任务栈中，因此任务信息中的SP是保存上下文之后的实际的SP值。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 * @param  pstTaskInfo [OUT] 类型#TSK_INFO_S *，保存任务信息。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskStatusGet | SRE_TaskContextGet | SRE_TaskPrivateDataGet
 */
extern UINT32 SRE_TaskInfoGet(UINT32 uwTaskPID, TSK_INFO_S *pstTaskInfo);

#if ( (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_CORTEX_AX) \
    || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup  SRE_task
 * @brief 获取任务上下文。
 *
 * @par 描述:
 * 获取指定任务的上下文。
 *
 * @attention
 * <ul>
 * <li>若获取当前任务的上下文信息，则只在硬中断、软中断、异常的处理中才有意义，否则获取的PC值是不准的。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 * @param  pstContext [OUT] 类型#TSK_CONTEXT_S *，保存任务上下文信息。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #OS_ERRNO_TSK_CONTEXT_NOT_GETED      0x02000829, 获取当前正在运行任务的任务上下文信息失败。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskStatusGet | SRE_TaskInfoGet | SRE_TaskPrivateDataGet
 */
 extern UINT32 SRE_TaskContextGet(UINT32 uwTaskPID, TSK_CONTEXT_S *pstContext);
#endif

/**
 * @ingroup  SRE_task
 * @brief 获取私有数据。
 *
 * @par 描述:
 * 获取当前任务的私有数据。
 *
 * @attention
 * <ul>
 * <li>当当前任务正在运行时，调用该接口能获取当前任务的私有数据。</li>
 * <li>当任务被中断打断时，中断里调用该接口能获取被中断打断的任务的私有数据。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #当前任务的私有数据 任意值，如未设置，则返回的值不确定。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPrivateDataSet
 */
extern UINT32 SRE_TaskPrivateDataGet(VOID);


/**
 * @ingroup  SRE_task
 * @brief 设置私有数据值。
 *
 * @par 描述:
 * 设置当前任务的私有数据值。
 *
 * @attention
 * <ul>
 * <li>只能在任务处理中调用。若在中断中设置，则操作的是刚被打断的任务。</li>
 * </ul>
 *
 * @param  uwPrivateData [IN] 类型#UINT32，数据值。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPrivateDataGet
 */
extern VOID SRE_TaskPrivateDataSet(UINT32 uwPrivateData);


/**
 * @ingroup  SRE_task
 * @brief 获取优先级。
 *
 * @par 描述:
 * 获取指定任务的优先级。
 *
 * @attention 无
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 * @param  uwTaskPID [OUT] 类型#TSK_PRIOR_T *，保存任务优先级指针。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPrioritySet
 */
extern UINT32 SRE_TaskPriorityGet(UINT32 uwTaskPID, TSK_PRIOR_T * pusTaskPrio);

/**
 * @ingroup  SRE_task
 * @brief 设置优先级。
 *
 * @par 描述:
 * 设置指定任务的优先级。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>若设置的优先级高于当前运行的任务，则可能引发任务调度。</li>
 * <li>若调整当前运行任务的优先级，同样可能引发任务调度。</li>
 * <li>若任务发生优先级继承或者任务阻塞在互斥信号量上，不可以设置任务的优先级。</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 * @param  usTaskPrio [IN] 类型#TSK_PRIOR_T，任务优先级。
 *
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803，任务优先级非法。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814，操作IDLE任务。
 * @retval #OS_ERRNO_TSK_PRIORITY_INHERIT       0x02000824，任务发生优先级继承。
 * @retval #OS_ERRNO_TSK_PEND_ON_MUTEX          0x02000825，任务阻塞在互斥信号量上。
 * @retval #OS_ERRNO_TSK_PRIOR_LOW_THAN_PENDTSK 0x02000828，设置优先级低于阻塞于它持有的互斥信号量的最高优先级任务的优先级
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPriorityGet
 */
extern UINT32 SRE_TaskPrioritySet(UINT32 uwTaskPID, TSK_PRIOR_T usTaskPrio);


/**
 * @ingroup  SRE_task
 * @brief 调整指定优先级的任务调度顺序。
 *
 * @par 描述:
 * 若uwNextTask为#OS_TSK_NULL_ID，则优先级队列中的第一个就绪任务调整至队尾,
 * 否则，将uwNextTask指定的任务调整至优先级队列的队首。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>前提是指定优先级的就绪队列至少要有两个就绪任务，否则报错返回。</li>
 * </ul>
 *
 * @param  usTaskPrio [IN] 类型#TSK_PRIOR_T，任务usTaskPrio，指定任务优先级队列。
 * @param  uwNextTask [IN] 类型#UINT32，任务ID或OS_TSK_NULL_ID。
 * @param  puwYeildTo [OUT] 类型#UINT32 *，保存被调整到队首的任务PID，可为NULL(不需要保存队首任务PID)。
 *
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803，任务优先级非法。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_YIELD_INVALID_TASK     0x0200080f，任务PID不在Yield操作指定的优先级队列中。
 * @retval #OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK  0x02000810，Yield操作指定的优先级队列中，就绪任务数小于2。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSuspend
 */
extern UINT32 SRE_TaskYield( TSK_PRIOR_T  usTaskPrio,
                             UINT32 uwNextTask,
                             UINT32 *puwYeildTo );



/**
 * @ingroup  SRE_task
 * @brief 查询本核指定任务正在PEND的信号量。
 *
 * @par 描述:
 * 根据任务状态和任务控制块，判断任务是否在PEND信号量，以及PEND的信号量ID。
 *
 * @attention
 * <ul>
 * <li>用户应先判断PEND状态，状态为0表明任务没有被信号量阻塞。</li>
 * <li>快速信号量没有信号量ID，若任务阻塞于快速信号量，则返回的信号量ID为#OS_INVALID。</li>
 * </ul>
 *
 * @param  uwTaskID     [IN]  类型#UINT32，任务PID。
 * @param  pusSemID     [OUT] 类型#UINT16 *，任务PEND的信号量ID或者#OS_INVALID。
 * @param  pusPendState [OUT] 类型#UINT16 *，任务的PEND状态：0，#OS_TSK_FSEM_PEND，#OS_TSK_PEND，#OS_TSK_MCSEM_PEND。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL       0x02000801，指针参数为空。
 * @retval #OS_ERRNO_TSK_ID_INVALID     0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED    0x0200080a，任务未创建。
 * @retval #SRE_OK                      0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemPendListGet | SRE_McSemPendListGet
 */
extern UINT32 SRE_TaskPendSemGet(TSK_HANDLE_T uwTaskID, UINT16 *pusSemID, UINT16 *pusPendState);

/**
 * @ingroup  SRE_task
 * @brief 查询当前运行任务指定队列的消息待接收个数。
 *
 * @par 描述:
 *查询当前运行任务消息队列uwQid上待接收消息个数。
 *
 * @attention
 * <ul>
 * <li>6181/6108/6182平台上表示任务上的指定的消息队列的消息数，其他平台不支持多消息队列，该接口表示消息队列上的消息数，入参uwQid无效。</li>
 * <li>入参uwQid有效性需由用户保证。</li>
 * </ul>
 *
 * @param  uwQid [IN] 类型#UINT32，6181/6108/6182平台上表示任务上的消息队列，其他平台无效入参。
 *
 * @retval  当前运行任务指定队列的消息待接收个数。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_TaskMsgNumGet(UINT32 uwQid);

/**
 * @ingroup  SRE_task
 * @brief 获取指定任务的堆栈信息。
 *
 * @par 描述:
 * 获取指定任务的堆栈信息。
 *
 * @attention 无
 *
 * @param  uwTaskPID [IN] 类型#UINT32，任务PID。
 * @param  pstStackInfo [OUT] 类型#STACK_INFO_S，任务栈信息。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL      0x02000801，入参指针为空。
 * @retval #OS_ERRNO_TSK_ID_INVALID    0x02000807，入参任务ID不合法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED   0x0200080a，任务未创建。
 * @retval #SRE_OK                     0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_TaskStackInfoGet(TSK_HANDLE_T uwTaskPID, STACK_INFO_S *pstStackInfo);


#if  (OS_OPTION_COPROCESSOR == YES)

/**
 * @ingroup  SRE_task
 * @brief 给任务分配矢量操作上下文数据保存区
 *
 * @par 描述:
 * 给指定任务分配矢量操作上下文数据保存区
 *
 * @attention
 * <ul>
 * <li>该操作适用于SD6108/SD6181平台的DSP核，SD6182/SD6157平台。</li>
 * <li>保存矢量操作上下文用到核的双LoadStore指令，建议配置的SaveAreaA/SaveAreaB在不同的Memory Bank中。</li>
 * <li>矢量上下文数据保存区大小需由用户根据芯片实际存在的矢量寄存器总大小确定。</li>
 * </ul>
 *
 * @param  uwTaskID [IN] 类型为#TSK_HANDLE_T，任务ID号
 * @param  pstParam [IN] 类型#CP_SAVE_CFG_PARAM_S *，参数结构指针
 *
 * @retval #OS_ERRNO_TSK_CP_SAVE_AREA_NULL      0x0200081e，任务的coprocessor上下文保存区域的地址为空指针。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，输入任务ID非法。
 * @retval #OS_ERRNO_TSK_CP_SAVE_AREA_NOT_ALIGN 0x0200801b，保存区域未按16字节对齐。
 * @retval #SRE_OK                              0x00000000，成功。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCpEntry | SRE_TaskCpExit
 */
extern UINT32 SRE_TaskCpSaveCfg(TSK_HANDLE_T uwTaskID, CP_SAVE_CFG_PARAM_S *pstParam);

/**
 * @ingroup  SRE_task
 * @brief 任务中执行矢量操作的入口
 *
 * @par 描述:
 * 任务中执行矢量操作的入口, 矢量操作开始之前需调用此接口。
 *
 * @attention
 * <ul>
 * <li>该操作适用于SD6108/SD6181平台的DSP核，SD6182/SD6157/SD6183平台。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCpExit
 */
extern VOID SRE_TaskCpEntry(VOID);

/**
 * @ingroup  SRE_task
 * @brief 任务中执行矢量操作的出口
 *
 * @par 描述:
 * 任务中执行矢量操作的出口，矢量操作完成之后需调用此接口。
 *
 * @attention
 * <ul>
 * <li>该操作适用于SD6108/SD6181平台的DSP核，SD6182/SD6157/SD6183平台。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCpEntry
 */
extern VOID SRE_TaskCpExit(VOID);

#else
#define SRE_TaskCpSaveCfg(uwTaskID, pstParam)   SRE_OK
#define SRE_TaskCpEntry(VOID)
#define SRE_TaskCpExit(VOID)
#endif

/**
 * @ingroup  SRE_task
 * @brief 获取指定PID的任务TCB首地址。
 *
 * @par 描述:
 * 获取指定PID的任务TCB首地址。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>不能获取ID不合法的任务TCB地址。</li>
 * <li>若获取ID的任务没有创建，返回失败。</li>
 * </ul>
 *
 * @param  uwTaskPID  [IN] 类型#UINT32，任务PID。
 * @param  puwTcbAddr [OUT] 类型#UINT32* ，保存任务TCB地址。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，pTskTcbAddr为NULL。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，任务PID非法。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，任务未创建。
 * @retval #SRE_OK                              0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskIDList
 */
extern UINT32 SRE_TaskTcbAddrGet(TSK_HANDLE_T uwTaskPID, UINT32* puwTcbAddr);

/**
 * @ingroup  SRE_task
 * @brief 获取所有已创建的任务PID信息。
 *
 * @par 描述:
 * 获取所有已创建的任务PID信息，按照任务ID从小到大的排序。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * </ul>
 *
 * @param  pusMaxNum  [IN/OUT] 类型#UINT16 *，元素个数，输入/输出参数，输入：缓冲区pstTaskPID可容纳的元素个数；输出：填写在缓冲区pstTaskPID中有效的元素个数。
 * @param  pstTaskPID [OUT]    类型#UINT32 *，缓冲区，输出参数，用于保存所有任务的PID。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL           0x02000801，获取所有任务的PID信息时，输入入参为NULL。
 * @retval #OS_ERRNO_TSK_INPUT_NUM_ERROR    0x02000821，获取所有任务的PID信息时，任务数为0个。
 * @retval #SRE_OK                          0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see 无
 */
extern UINT32 SRE_TaskIDList(UINT16 *pusMaxNum, UINT32 *pstTaskPID);

/**
 * @ingroup  SRE_task
 * @brief 查询任务名。
 *
 * @par 描述:
 * 根据任务PID，查询任务名。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>不能查询ID不合法的任务名。</li>
 * <li>若查询没有创建的任务名，查询失败。</li>
 * </ul>
 *
 * @param  uwTaskID [IN] 类型#UINT32，任务ID。
 * @param  ppcName  [OUT] 类型#CHAR **，保存任务名字符串的首地址。
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801，  保存任务名指针为NULL。
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a，  任务未创建。
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807，  任务ID非法。
 * @retval #SRE_OK                              0x00000000，  查询成功。
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see  SRE_TaskIDList
 */
extern UINT32 SRE_TaskNameGet(TSK_HANDLE_T uwTaskID,CHAR **ppcName);

/**
 * @ingroup  SRE_task
 * @brief 注册任务切换钩子。
 *
 * @par 描述:
 * 注册任务切换钩子函数。钩子函数在切入新任务前被调用。
 *
 * @attention
 * <ul>
 * <li>不同钩子函数间执行的先后顺序，不应当存在依赖关系。</li>
 * <li>不应在任务切换钩子里进行可能引起任务调度的处理，如：任务延时、P信号量等。</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#TSK_SWITCH_HOOK，任务切换钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSwitchHookDelete | SRE_TaskDeleteHookAdd | SRE_TaskCreateHookAdd
 */
#define SRE_TaskSwitchHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_TSK_SWITCH, (OS_VOID_FUNC)(TSK_SWITCH_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief 取消任务切换钩子。
 *
 * @par 描述:
 * 取消指定的任务切换钩子。钩子函数在切入新任务前被调用。
 *
 * @attention  无
 *
 * @param  pfnHook [IN] 类型#TSK_SWITCH_HOOK，任务切换钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSwitchHookAdd
 */
#define SRE_TaskSwitchHookDelete(pfnHook) SRE_HookDel(OS_HOOK_TSK_SWITCH, (OS_VOID_FUNC)(TSK_SWITCH_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief 注册任务创建钩子。
 *
 * @par 描述:
 * 注册任务创建钩子函数,钩子函数在任务创建成功后被调用。
 *
 * @attention
 * <ul>
 * <li>不应在任务创建钩子里创建任务。</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#TSK_CREATE_HOOK，任务创建钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCreateHookDelete | SRE_TaskDeleteHookAdd | SRE_TaskSwitchHookAdd
 */
#define SRE_TaskCreateHookAdd(pfnHook)  SRE_HookAdd(OS_HOOK_TSK_CREATE, (OS_VOID_FUNC)(TSK_CREATE_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief 取消任务创建钩子。
 *
 * @par 描述:
 * 取消指定的任务创建钩子函数,钩子函数在任务创建成功后被调用。
 *
 * @attention 无
 *
 * @param  pfnHook [IN] 类型#TSK_CREATE_HOOK，任务创建钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCreateHookAdd
 */
#define SRE_TaskCreateHookDelete(pfnHook) SRE_HookDel(OS_HOOK_TSK_CREATE, (OS_VOID_FUNC)(TSK_CREATE_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief 注册任务删除钩子。
 *
 * @par 描述:
 * 注册任务删除钩子函数,钩子函数在资源回收前被调用。
 *
 * @attention
 * <ul>
 * <li>任务删除钩子中不允许进行pend信号量操作。</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#TSK_DELETE_HOOK，任务删除钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDeleteHookDelete | SRE_TaskCreateHookAdd | SRE_TaskSwitchHookAdd
 */
#define SRE_TaskDeleteHookAdd(pfnHook)  SRE_HookAdd(OS_HOOK_TSK_DELETE,(OS_VOID_FUNC)(TSK_DELETE_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief 取消任务删除钩子。
 *
 * @par 描述:
 * 取消指定的任务删除钩子,钩子函数在资源回收前被调用。
 *
 * @attention
 * <ul>
 * <li>不应在任务删除钩子里删除任务。</li>
 * </ul>
 *
 * @param  pfnHook [IN] 类型#TSK_DELETE_HOOK，任务删除钩子函数。
 *
 * @par 依赖:
 * <ul><li>sre_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDeleteHookAdd
 */
#define SRE_TaskDeleteHookDelete(pfnHook) SRE_HookDel(OS_HOOK_TSK_DELETE, (OS_VOID_FUNC)(TSK_DELETE_HOOK)pfnHook)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BASE_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

