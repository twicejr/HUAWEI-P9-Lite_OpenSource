/**
 * @file sre_sem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：信号量模块对外头文件。 \n
 */

#ifndef _SRE_SEM_H
#define _SRE_SEM_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**@defgroup SRE_sem 信号量
  *@ingroup SRE_comm
  */

/**
 * @ingroup SRE_sem
 * 信号量等待时间设定：表示永久等待。
 */
#define OS_WAIT_FOREVER     0xFFFFFFFF

/**
 * 二进制信号量空闲状态，互斥型信号量初始计数值。
 */
#define OS_SEM_FULL         1

/**
 * 二进制信号量占用状态，同步型信号量初始计数值。
 */
#define OS_SEM_EMPTY        0

/**
 * @ingroup SRE_sem
 * 信号量错误码：初始化信号量内存不足。
 *
 * 值: 0x02000f00
 *
 * 解决方案: 可以将私有的静态内存空间配大。
 */
#define OS_ERRNO_SEM_NO_MEMORY                      SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x00)

/**
 * @ingroup SRE_sem
 * 信号量错误码：信号量句柄非法（错误或已删除）。
 *
 * 值: 0x02000f01
 *
 * 解决方案: 查看输入的信号量句柄值是否有效。
 */
#define OS_ERRNO_SEM_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x01)

/**
 * @ingroup SRE_sem
 * 信号量错误码：输入指针为空。
 *
 * 值: 0x02000f02
 *
 * 解决方案: 查看指针是否输入为空。
 */
#define OS_ERRNO_SEM_PTR_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x02)

/**
 * @ingroup SRE_sem
 * 信号量错误码：没有空闲信号量。
 *
 * 值: 0x02000f03
 *
 * 解决方案: 查看信号量模块是否打开，或配置更多信号量。
 */
#define OS_ERRNO_SEM_ALL_BUSY                       SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x03)

/**
 * @ingroup SRE_sem
 * 信号量错误码：信号量没有可用资源且Pend时设为不等待(等待时间为0)时获取信号量失败。
 *
 * 值: 0x02000f04
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SEM_UNAVAILABLE                    SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x04)

/**
 * @ingroup SRE_sem
 * 信号量错误码：禁止中断处理函数阻塞于信号量。
 *
 * 值: 0x02000f05
 *
 * 解决方案: 查看是否在中断中Pend信号量。
 */
#define OS_ERRNO_SEM_PEND_INTERR                    SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x05)

/**
 * @ingroup SRE_sem
 * 信号量错误码：任务切换锁定时，禁止任务阻塞于信号量。
 *
 * 值: 0x02000f06
 *
 * 解决方案: 不要在锁任务时pend没有资源可用的信号量。
 */
#define OS_ERRNO_SEM_PEND_IN_LOCK                   SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x06)

/**
 * @ingroup SRE_sem
 * 信号量错误码：信号量等待超时。
 *
 * 值: 0x02000f07
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_SEM_TIMEOUT                        SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x07)

/**
 * @ingroup SRE_sem
 * 信号量错误码：信号量发生溢出。
 *
 * 值: 0x02000f08
 *
 * 解决方案: 查看输入的信号量计数值是否有效。
 */
#define OS_ERRNO_SEM_OVERFLOW                       SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x08)

/**
 * @ingroup SRE_sem
 * 信号量错误码：信号量删除和重设当前值时有阻塞于信号量的任务。
 *
 * 值: 0x02000f09
 *
 * 解决方案: 如果当前信号量有任务阻塞，不能进行删除和重设计数值操作。
 */
#define OS_ERRNO_SEM_PENDED                         SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x09)

/**
 * @ingroup SRE_sem
 * 信号量错误码：在中断中释放互斥型信号量。
 *
 * 值: 0x02000f0a
 *
 * 解决方案: 只能在任务中对互斥型信号量进行PV操作。
 */
#define OS_ERRNO_SEM_MUTEX_POST_INTERR              SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x0A)

/**
 * @ingroup SRE_sem
 * 信号量错误码：非当前互斥信号量的持有者释放该信号量。
 *
 * 值: 0x02000f0b
 *
 * 解决方案: 互斥信号量只能由其持有者释放，即互斥信号量的PV操作必须配对使用。
 */
#define OS_ERRNO_SEM_MUTEX_NOT_OWNER_POST           SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x0B)

/**
 * @ingroup SRE_sem
 * 信号量错误码：注册核内信号量个数为0导致注册失败。
 *
 * 值: 0x02000f10
 *
 * 解决方案: 查看信号量模块配置的最大个数是否为0。
 */
#define OS_ERRNO_SEM_REG_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x10)

/**
 * @ingroup SRE_sem
 * 信号量错误码：调用#SRE_SemPendListGet时，指定的内存空间不足，无法存入全部的阻塞任务PID。
 *
 * 值: 0x02000f11
 *
 * 解决方案: 建议将数组长度配置为(#OS_TSK_MAX_SUPPORT_NUM + 1) * 4。
 */
#define OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH           SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x11)

/**
 * @ingroup SRE_sem
 * 信号量错误码：调用#SRE_SemPendListGet时，输入指针为空或者uwBufLen小于4。
 *
 * 值: 0x02000f12
 *
 * 解决方案: 出参不能为NULL，指定的缓存长度不能小于4。
 */
#define OS_ERRNO_SEM_INPUT_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_SEM, 0x12)

/*
 * @ingroup SRE_sem
 * 信号量错误码：信号量创建时指定的唤醒方式非法。
 *
 * 值: 0x02000f13
 *
 * 解决方案: 唤醒方式只能为SEM_MODE_FIFO,SEM_MODE_PRIOR。
 */
#define OS_ERRNO_SEM_MODE_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x13)

/*
 * @ingroup SRE_sem
 * 信号量错误码：创建二进制信号量的初始值只能为OS_SEM_FULL或者OS_SEM_EMPTY。
 *
 * 值: 0x02000f14
 *
 * 解决方案: 二进制信号量初始值只能为OS_SEM_FULL(1)或者OS_SEM_EMPTY(0)。
 */
#define OS_ERRNO_SEM_BIN_VALUE_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x14)

/*
 * @ingroup SRE_sem
 * 信号量错误码：信号量设置计数最大值时指定的最大值非法。
 *
 * 值: 0x02000f15
 *
 * 解决方案: 指定的信号量最大计数值不能大于0xFFFF FFFE。
 */
#define OS_ERRNO_SEM_MAXCOUNT_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x15)

/*
 * @ingroup SRE_sem
 * 信号量错误码：信号量设置计数最大值时指定的最大值小于当前计数值。
 *
 * 值: 0x02000f16
 *
 * 解决方案: 指定的信号量最大计数值不能小于当前计数值。
 */
#define OS_ERRNO_SEM_MAXCOUNT_GREATER_THAN_CURRENT  SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x16)

/*
 * @ingroup SRE_sem
 * 信号量错误码：对二进制型信号量设置最大值。
 *
 * 值: 0x02000f17
 *
 * 解决方案: 不要对二进制型信号量设置最大值。
 */
#define OS_ERRNO_SEM_BIN_NO_MAXCOUNT                SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x17)

/*
 * @ingroup SRE_sem
 * 信号量错误码：重设信号量的当前计数值超过了设置的最大值。
 *
 * 值: 0x02000f18
 *
 * 解决方案: 设置的当前计数值不能大于设置的最大值。
 */
#define OS_ERRNO_SEM_OVER_MAXCOUNT                  SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x18)

/*
 * @ingroup SRE_sem
 * 信号量错误码：获取信号量详细信息时出参结构体指针为NULL。
 *
 * 值: 0x02000f19
 *
 * 解决方案: 用来保存信号量详细信息的结构体指针不能为NULL。
 */
#define OS_ERRNO_SEM_INFO_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x19)

/*
 * @ingroup SRE_sem
 * 信号量错误码：对二进制型信号量重设当前计数值。
 *
 * 值: 0x02000f1a
 *
 * 解决方案: 不要对二进制型信号量重设当前计数值。
 */
#define OS_ERRNO_SEM_BIN_CANNOT_RESET               SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x1A)

/*
 * @ingroup SRE_sem
 * 信号量错误码：互斥型信号量的唤醒方式不为优先级方式。
 *
 * 值: 0x02000f1c
 *
 * 解决方案: 互斥型信号量的唤醒方式不能为FIFO。
 */
#define OS_ERRNO_SEM_MUTEX_SHOULD_PRIO              SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x1C)

/*
 * @ingroup SRE_sem
 * 信号量错误码：获取当前信号量计数时传入的出参为NULL。
 *
 * 值: 0x02000f1d
 *
 * 解决方案: 互斥型信号量的唤醒方式不能为FIFO。
 */
#define OS_ERRNO_SEM_COUNT_GET_PTR_NULL             SRE_ERRNO_OS_ERROR(OS_MID_SEM,0x1D)

/*
 * @ingroup SRE_sem
 * 信号量不被任何任务持有，处于空闲状态。
 */
#define OS_INVALID_OWNER_ID                         (0xFFFFFFFE)

/**
 * @ingroup SRE_sem
 * 信号量句柄类型定义。
 */
typedef UINT16 SEM_HANDLE_T;

/**
 * @ingroup SRE_sem
 * 信号量模块配置信息的结构体定义。
 */
typedef struct tagSemModInfo
{
    UINT16 usMaxNum;                            /**< 最大支持的信号量数  */
    UINT16 usReserved;                          /**< 保留                */
}SEM_MOD_INFO_S;

/*
 * @ingroup SRE_sem
 * 信号量类型。
 */
typedef enum
{
    SEM_TYPE_COUNT,                             /**< 计数型信号量    */
    SEM_TYPE_BIN                                /**< 二进制信号量    */
}OS_SEM_TYPE_E;

/*
 * @ingroup SRE_sem
 * 信号量模块被阻塞线程唤醒方式。
 */
typedef enum
{
    SEM_MODE_FIFO,                              /**< 信号量FIFO唤醒模式    */
    SEM_MODE_PRIOR,                             /**< 信号量优先级唤醒模式  */
    SEM_MODE_BUTT                               /**< 信号量非法唤醒方式  */
}OS_SEM_MODE_E;

/**
 * @ingroup SRE_sem
 * 信号量模块获取信号量详细信息时的信息结构体。
 */
typedef struct tagSemInfo
{
    UINT32 uwCount;                             /**< 信号量计数 */
    UINT32 uwOwner;                             /**< 信号量占用者，对于计数型信号量，记录的是最后一次信号量获得者；如果没有被任务获得，则为OS_THREAD_ID_INVALID */
    OS_SEM_MODE_E enMode;                       /**< 信号量唤醒方式，为SEM_MODE_FIFO或SEM_MODE_PRIOR */
    OS_SEM_TYPE_E enType;                       /**< 信号量类型，为SEM_TYPE_COUNT（计数型）或SEM_TYPE_BIN（二进制）*/
}SEM_INFO_S;

/**
 * @ingroup SRE_sem
 * @brief 创建一个计数型信号量。
 *
 * @par 描述:
 * 根据用户指定的计数值，创建一个计数型信号量，设定初始计数器数值，唤醒方式为FIFO。
 * @attention
 * <ul><li>创建是否成功会受到"核内信号量裁剪开关"和"最大支持信号量"配置项的限制。</li></ul>
 *
 * @param uwCount [IN] 类型为#UINT32，计数器初始值，取值范围为[0, 0xFFFFFFFE]。
 * @param pusSemHandle [OUT] 类型为#SEM_HANDLE_T *，输出信号量句柄。
 *
 * @retval #OS_ERRNO_SEM_OVERFLOW 0x02000f08，计数器初始值超出范围。
 * @retval #OS_ERRNO_SEM_ALL_BUSY 0x02000f03，没有空闲信号量，建议增加"最大支持信号量"配置。
 * @retval #OS_ERRNO_SEM_PTR_NULL 0x02000f02，入参指针为空。
 * @retval #SRE_OK                0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemDelete | SRE_SemCCreate | SRE_SemBCreate
 */
extern  UINT32 SRE_SemCreate(UINT32 uwCount,  SEM_HANDLE_T *pusSemHandle);

/**
 * @ingroup SRE_sem
 * @brief 创建一个计数型信号量。
 *
 * @par 描述:
 * 创建一个计数信号量，设定初始计数器数值。
 * @attention
 * <ul><li>创建是否成功会受到"最大支持信号量"配置项的限制。</li></ul>
 *
 * @param uwCount [IN]       类型#UINT32，计数器初始值，取值范围为[0, 0xFFFFFFFE]。
 * @param enMode  [IN]       类型#OS_SEM_MODE_E，信号量模式，取值范围为SEM_MODE_FIFO或者SEM_MODE_PRIOR。
 * @param pusSemHandle [OUT] 类型#SEM_HANDLE_T *，输出信号量句柄。
 *
 * @retval #OS_ERRNO_SEM_OVERFLOW     0x02000f08，计数器初始值超出范围。
 * @retval #OS_ERRNO_SEM_ALL_BUSY     0x02000f03，没有空闲信号量，建议增加"最大支持信号量"配置。
 * @retval #OS_ERRNO_SEM_PTR_NULL     0x02000f02，入参指针为空。
 * @retval #OS_ERRNO_SEM_MODE_INVALID 0x02000f13，指定的唤醒模式非法。
 * @retval #SRE_OK                    0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>SRE_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemDelete | SRE_SemCreate | SRE_SemBCreate
 */
extern UINT32 SRE_SemCCreate(UINT32 uwCount, SEM_HANDLE_T *pusSemHandle, OS_SEM_MODE_E enMode);

/**
 * @ingroup SRE_sem
 * @brief 创建一个二进制信号量。
 *
 * @par 描述:
 * 创建一个二进制信号量，设定初始计数器数值。
 * @attention
 * <ul><li>创建是否成功会受到"最大支持信号量"配置项的限制。</li></ul>
 *
 * @param uwCount [IN]       类型#UINT32，计数器初始值，取值范围为OS_SEM_FULL或OS_SEM_EMPTY。
 * @param enMode  [IN]       类型#OS_SEM_MODE_E，信号量模式，取值范围为SEM_MODE_FIFO或者SEM_MODE_PRIOR。
 * @param pusSemHandle [OUT] 类型#SEM_HANDLE_T *，输出信号量句柄。
 *
 * @retval #OS_ERRNO_SEM_BIN_VALUE_ERR     0x02000f14，计数器初始值错误。
 * @retval #OS_ERRNO_SEM_ALL_BUSY          0x02000f03，没有空闲信号量，建议增加"最大支持信号量"配置。
 * @retval #OS_ERRNO_SEM_PTR_NULL          0x02000f02，入参指针为空。
 * @retval #OS_ERRNO_SEM_MODE_INVALID      0x02000f13，指定的唤醒模式非法。
 * @retval #OS_ERRNO_SEM_MUTEX_SHOULD_PRIO 0x02000f1c，互斥型信号量的唤醒方式只能为优先级方式。
 * @retval #SRE_OK                         0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>SRE_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemDelete
 */
extern UINT32 SRE_SemBCreate(UINT32 uwCount, SEM_HANDLE_T *pusSemHandle, OS_SEM_MODE_E enMode);

/**
 * @ingroup SRE_sem
 * @brief 删除一个信号量。
 *
 * @par 描述:
 * 删除用户传入的信号量句柄指定的信号量，如果有任务阻塞于该信号量，则删除失败。
 * @attention  无
 *
 * @param usSemHandle [IN] 类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 *
 * @retval #OS_ERRNO_SEM_INVALID 0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_PENDED  0x02000f09，有任务阻塞于该信号量，禁止删除。
 * @retval #SRE_OK               0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemCreate
 */
extern UINT32 SRE_SemDelete(SEM_HANDLE_T usSemHandle);

/**
 * @ingroup SRE_sem
 * @brief 设置一个信号量的最大值。
 *
 * @par 描述:
 * 设置一个信号量计数的最大值。
 * @attention  无
 *
 * @param usSemHandle [IN] 类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 * @param uwMaxCount  [IN] 类型为#UINT32，待设置的最大计数值，不能小于当前计数值，且不能大于0xFFFFFFFE。
 *
 * @retval #OS_ERRNO_SEM_INVALID           0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_MAXCOUNT_INVALID  0x02000f15，设置的最大值非法。
 * @retval #OS_ERRNO_SEM_BIN_NO_MAXCOUNT   0x02000f17，对二进制信号量设置最大值。
 * @retval #OS_ERRNO_SEM_MAXCOUNT_GREATER_THAN_CURRENT 0x02000f16，信号量设置计数最大值时指定的最大值小于当前计数值。
 * @retval #SRE_OK                         0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemCreate | SRE_SemReset
 */
extern UINT32 SRE_SemCMaxCountSet(SEM_HANDLE_T usSemHandle, UINT32 uwMaxCount);

/**
 * @ingroup SRE_sem
 * @brief 重设信号量计数器数值函数。
 *
 * @par 描述:
 * 根据用户输入信号量句柄和计数值，重设信号量计数器数值。
 * @attention
 * <ul><li>如果有任务阻塞于该信号量，则重设失败。</li></ul>
 *
 * @param usSemHandle [IN] 类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 * @param uwCount [IN] 类型为#UINT32，计数器设定值，取值范围为[0, 0xFFFFFFFE]。
 *
 * @retval #OS_ERRNO_SEM_INVALID       0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_OVERFLOW      0x02000f08，计数器设定值超过OS_SEM_COUNT_MAX。
 * @retval #OS_ERRNO_SEM_BIN_CANNOT_RESET    0x02000f1a，对二进制型信号量重设当前计数值。
 * @retval #OS_ERRNO_SEM_PENDED        0x02000f09，有任务阻塞于该信号量，禁止重设。
 * @retval #OS_ERRNO_SEM_OVER_MAXCOUNT 0x02000f18，计数器设定值超过设置的最大值。
 * @retval #SRE_OK                     0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemCreate | SRE_SemCountGet | SRE_SemCMaxCountSet
 */
extern UINT32 SRE_SemReset(SEM_HANDLE_T usSemHandle, UINT32 uwCount);

/**
 * @ingroup SRE_sem
 * @brief 获取信号量计数器数值。
 *
 * @par 描述:
 * 根据用户输入信号量句柄和计数值，获取信号量计数器数值。
 * @attention 无
 *
 * @param usSemHandle [IN]  类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 * @param puwSemCnt   [OUT] 类型为#UINT32 *，保存信号量计数值指针。
 *
 * @retval #OS_ERRNO_SEM_INVALID         0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_COUNT_GET_PTR_NULL      0x02000f1d，获取当前信号量计数时传入的出参为NULL。
 * @retval #SRE_OK                       0x00000000，获取信号量计数器值成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemCreate | SRE_SemReset | SRE_SemInfoGet
 */
extern UINT32 SRE_SemCountGet(SEM_HANDLE_T usSemHandle, UINT32 *puwSemCnt);

/**
 * @ingroup SRE_sem
 * @brief 等待一个信号量。
 *
 * @par 描述:
 * 等待用户传入信号量句柄指定的信号量，若其计数器值大于0，则直接减1返回成功。否则任务阻塞，
 * 等待其他线程发布该信号量，等待超时时间可设定。
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>等待时间可以选择零等待、等待特定时间、永久等待。</li>
 * <li>该接口只能被任务调用。</li>
 * <li>在锁任务情况下，用户要PEND信号量，要保证当前有可用信号量资源。</li>
 * </ul>
 *
 * @param usSemHandle [IN] 类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 * @param uwTimeout [IN] 类型为#UINT32，等待时间限制，单位为tick，取值范围为[0, 0xffffffff]。
 * #OS_NO_WAIT或0表示不等待，#OS_WAIT_FOREVER或0xffffffff表示永久等待。
 *
 * @retval #OS_ERRNO_SEM_INVALID      0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_UNAVAILABLE  0x02000f04，信号量零等待时获取失败。
 * @retval #OS_ERRNO_SEM_PEND_INTERR  0x02000f05，中断处理函数禁止发生阻塞。
 * @retval #OS_ERRNO_SEM_PEND_IN_LOCK 0x02000f06，系统可用资源为0且任务切换锁定时，禁止任务发生阻塞。
 * @retval #OS_ERRNO_SEM_TIMEOUT      0x02000f07，信号量等待超时。
 * @retval #SRE_OK                    0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemPost
 */
extern UINT32 SRE_SemPend(SEM_HANDLE_T usSemHandle, UINT32 uwTimeout);

/**
 * @ingroup SRE_sem
 * @brief 发布指定的信号量。
 *
 * @par 描述:
 * 发布指定的信号量，若没有任务等待该信号量，则直接将计数器加1返回。
 * 否则根据唤醒方式唤醒相应的阻塞任务，FIFO方式唤醒最早阻塞的任务，优先级方式唤醒阻塞在此信号量的最高优先级任务。
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>在未锁任务的情况下，如果唤醒的任务优先级高于当前任务，则会立刻发生任务切换。</li>
 * <li>发生任务切换时，如果支持优先级唤醒方式，且创建信号量时指定唤醒方式为优先级，则唤醒阻塞在该信号量上的最高优先级任务。</li>
 * </ul>
 * @param usSemHandle [IN] 类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 *
 * @retval #OS_ERRNO_SEM_INVALID              0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_OVERFLOW             0x02000f08，信号量加操作后溢出。
 * @retval #OS_ERRNO_SEM_MUTEX_POST_INTERR    0x02000f0a，中断中释放互斥型信号量。
 * @retval #OS_ERRNO_SEM_MUTEX_NOT_OWNER_POST 0x02000f0b，非互斥信号量的持有者在释放此互斥信号量。
 * @retval #SRE_OK                            0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemPend
 */
extern UINT32 SRE_SemPost(SEM_HANDLE_T usSemHandle);

/**
 * @ingroup SRE_sem
 * @brief 获取阻塞在指定核内信号量上的任务PID清单。
 *
 * @par 描述:
 * 根据用户指定的核内信号量句柄，获取阻塞在指定核内信号量上的任务PID清单。若有任务阻塞于该核内信号量，则返回阻塞于该核内信号量的任务数目，以及相应任务的PID。
 * 若没有任务阻塞于该核内信号量，则返回阻塞于该核内信号量的任务数目为0。
 * @attention
 * <ul><li>用户应保证存储任务PID清单的内存空间足够大，建议将uwBufLen配置为(#OS_TSK_MAX_SUPPORT_NUM + 1) * 4bytes。</li></ul>
 *
 * @param usSemHandle   [IN]  类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 * @param puwTskCnt [OUT] 类型为#UINT32 *，阻塞于该核内信号量的任务数。
 * @param puwPidBuf [OUT] 类型为#UINT32 *，由用户指定的内存区域首地址，用于存储阻塞于指定核内信号量的任务PID。
 * @param uwBufLen  [IN]  类型为#UINT32，用户指定的内存区域的长度（单位：字节）。
 *
 * @retval #OS_ERRNO_SEM_INVALID              0x02000f01，信号量句柄为非法值，或已被删除。
 * @retval #OS_ERRNO_SEM_INPUT_ERROR          0x02000f12，指针为空或者uwBufLen小于4。
 * @retval #OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH 0x02000f11，指定的内存空间不足，但内存中的任务PID有效。
 * @retval #SRE_OK                            0x00000000，操作成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPendSemGet | SRE_McSemPendListGet | SRE_SemInfoGet
 */
extern UINT32 SRE_SemPendListGet( SEM_HANDLE_T usSemHandle,
                                 UINT32 *puwTskCnt,
                                 UINT32 *puwPidBuf,
                                 UINT32  uwBufLen );

/**
 * @ingroup SRE_sem
 * @brief 获取信号量详细信息:信号量当前计数值，信号量持有者(最后一次pend成功的线程ID)，信号量唤醒方式，信号量类型。
 *
 * @par 描述:
 * 根据用户输入信号量句柄获取信号量详细信息。
 * @attention 无
 *
 * @param usSemHandle [IN]  类型为#SEM_HANDLE_T，信号量句柄，来源于信号量创建成功的输出值。
 * @param pstSemInfo  [OUT] 类型为#SEM_INFO_S*，信号量详细信息:uwCount--信号量计数，uwOwner--信号量占用者，enMode--信号量唤醒方式，enType--信号量类型。
 *
 * @retval #OS_ERRNO_SEM_INFO_NULL       0x02000f19，传入的出参结构体指针为NULL。
 * @retval #OS_ERRNO_SEM_INVALID         0x02000f01，信号量句柄非法或已被删除。
 * @retval #SRE_OK                       0x00000000，获取信号量计数器值成功。
 * @par 依赖:
 * <ul><li>sre_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_SemCountGet | SRE_SemPendListGet
 */
extern UINT32 SRE_SemInfoGet(SEM_HANDLE_T usSemHandle, SEM_INFO_S *pstSemInfo);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _SRE_SEM_H */


