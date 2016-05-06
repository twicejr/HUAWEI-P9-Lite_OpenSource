
/**
 * @file sre_mcsem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：核间信号量模块的对外头文件。 \n
 */

#ifndef _SRE_MCSEM_H
#define _SRE_MCSEM_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**@defgroup SRE_mcsem 核间信号量
  *@ingroup SRE_comm
  */
/**
 * @ingroup SRE_mcsem
 * 核间信号量等待时间设定：表示永久等待。
 */
#define OS_WAIT_FOREVER       0xFFFFFFFF

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：初始化核间信号量内存不足。
 *
 * 值: 0x02001300
 *
 * 解决方案: 增加共享静态内存分区的大小。
 */
#define OS_ERRNO_MCSEM_NO_MEMORY              SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x00)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：核间信号量句柄非法（错误、本核未创建或已删除）。
 *
 * 值: 0x02001301
 *
 * 解决方案: 请检查输入的信号量句柄的是否错误，本核是否已创建。
 */
#define OS_ERRNO_MCSEM_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x01)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：输入指针为空。
 *
 * 值: 0x02001302
 *
 * 解决方案: 请检查输入指针是否为空。
 */
#define OS_ERRNO_MCSEM_PTR_NULL               SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x02)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：没有空闲核间信号量。
 *
 * 值: 0x02001303
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_MCSEM_ALL_BUSY               SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x03)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：核间信号量获取失败。
 *
 * 值: 0x02001304
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_MCSEM_UNAVAILABLE            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x04)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：禁止中断处理函数阻塞于核间信号量。
 *
 * 值: 0x02001305
 *
 * 解决方案: 查看是否在中断中使用了核间信号量，该系统不支持中断中使用核间信号量。
 */
#define OS_ERRNO_MCSEM_PEND_INTERR            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x05)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：任务切换锁定时，禁止任务阻塞于核间信号量。
 *
 * 值: 0x02001306
 *
 * 解决方案: 查看是否在任务锁定时使用了核间信号量，该系统不支持任务锁定时使用核间信号量。
 */
#define OS_ERRNO_MCSEM_PEND_IN_LOCK           SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x06)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：核间信号量等待超时。
 *
 * 值: 0x02001307
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_MCSEM_TIMEOUT                SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x07)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：核间信号量计数超出最大范围。
 *
 * 值: 0x02001308
 *
 * 解决方案: 查看输入的信号量计数值是否有效。
 */
#define OS_ERRNO_MCSEM_OVERFLOW               SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x08)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：有阻塞于核间信号量的任务。
 *
 * 值: 0x02001309
 *
 * 解决方案: 请检查是否有任务阻塞于该核间信号量。
 */
#define OS_ERRNO_MCSEM_PENDED                 SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x09)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：核间信号量阻塞链表非空时资源回收失败。
 *
 * 值: 0x0200130A
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_MCSEM_PENDED_NULL            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0A)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：最大支持核间信号量数为零。
 *
 * 值: 0x0200130B
 *
 * 解决方案: 检查核间信号量配置选项中核间信号量配置是否为零。
 */
#define OS_ERRNO_MCSEM_MAXNUM_NULL            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0B)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：调用#SRE_McSemPendListGet时，空指针或uwBufLen小于4。
 *
 * 值: 0x0200130C
 *
 * 解决方案: 无。
 */
#define OS_ERRNO_MCSEM_INPUT_ERROR            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0C)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：调用#SRE_McSemPendListGet时，指定的内存空间不足，无法存入全部的阻塞任务PID。
 *
 * 值: 0x0200130D
 *
 * 解决方案: 建议uwBufLen配置为(#OS_TSK_MAX_SUPPORT_NUM + 1) * #OS_MAX_CORE_NUM * 4bytes。
 */
#define OS_ERRNO_MCSEM_INPUT_BUF_NOT_ENOUGH   SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0D)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：不同镜像上的核间信号量个数不一样，核间信号量注册失败。
 *
 * 值: 0x0200130E
 *
 * 解决方案: 建议每个核的最大核间信号量个数配置一样多。
 */
#define OS_ERRNO_MCSEM_NUM_NOT_SAME           SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0E)

/**
 * @ingroup SRE_mcsem
 * 核间信号量错误码：核间信号量被某个核重复创建。
 *
 * 值: 0x0200130F
 *
 * 解决方案: 建议检查信号量是否被创建过。
 */
#define OS_ERRNO_MCSEM_CREATED                SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0F)


/**
 * @ingroup SRE_mcsem
 * 核间信号量句柄类型定义。
 */
typedef UINT32 MCSEM_HANDLE_T;

/**
 * @ingroup SRE_mcsem
 * 核间信号量模块配置信息的结构体定义。
 */
typedef struct tagMcsemModInfo
{
    UINT16 usMaxNum;                /**< 最大支持的核间信号量数  */
}MCSEM_MOD_INFO_S;


/**
 *@ingroup SRE_mcsem
 *@brief 创建一个核间信号量。
 *
 *@par 描述:
 *根据用户指定的名字和计数值，创建一个核间信号量。
 *@attention
 *@li 创建是否成功会受到"核间信号量裁剪开关"和"最大支持核间信号量"配置项的限制。
 *@li 创建时需要指定名称（编号），多个核上创建的相同名称的核间信号量看作同一个，计数器初值以第一次创建时为准。
 *@li RTOSck的核间信号量属于计数型信号量，创建次数与删除次数需要相同。
 *@li 核间信号量的创建与删除与核绑定，本核使用必须本核创建，且不能够重复创建。
 *@li wCount大于等于0时表示互斥模式，设定计数初值，一次pend对应一次post操作；当wCount小于0是表示同步模式，-wCount表示同步的次数，一次pend需要对应-wCount次post操作
 *
 *@param wCount [IN] 类型为#INT32，计数器初始值，取值范围为[-254, 254]。
 *@param uwMcSemName [IN] 类型#UINT32，核间信号量名称，用于标识多核创建的是否为同一个核间信号量。
 *@param puwSemHandle [OUT] 类型为#MCSEM_HANDLE_T *，输出核间信号量句柄。
 *
 *@retval #OS_ERRNO_MCSEM_OVERFLOW 0x02001308，计数器初始值超出最大范围。
 *@retval #OS_ERRNO_MCSEM_ALL_BUSY 0x02001303，没有空闲核间信号量，建议增加"最大支持核间信号量"配置。
 *@retval #OS_ERRNO_MCSEM_PTR_NULL 0x02001302，入参指针为空。
 *@retval #OS_ERRNO_MCSEM_CREATED  0x0200130F，重复创建。
 *@retval #SRE_OK                  0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see SRE_McSemDelete
*/
extern UINT32 SRE_McSemCreate(INT32 wCount, UINT32 uwMcSemName,
                              MCSEM_HANDLE_T *puwSemHandle);

/**
 *@ingroup SRE_mcsem
 *@brief 删除一个核间信号量。
 *
 *@par 描述:
 *根据用户指定的核间信号量句柄，删除核间信号量。
 *@attention
 *@li RTOSck的核间信号量属于计数型信号量，创建次数与删除次数需要相同。
 *@li RTOSck的核间信号量绑定了核号，本核创建只能本核删除，且不能重复删除。
 *@li 删除操作仅当信号量创建计数变成0时才会真正删除该核间信号量。
 *@li 如果有任务阻塞于该核间信号量，则删除失败。
 *
 *@param uwSemHandle [IN] 类型为#MCSEM_HANDLE_T，核间信号量句柄，来源于核间信号量创建成功的输出值。
 *
 *@retval #OS_ERRNO_MCSEM_INVALID 0x02001301，核间信号量句柄为非法值，或已被删除。
 *@retval #OS_ERRNO_MCSEM_PENDED  0x02001309，有任务阻塞于该核间信号量，禁止删除。
 *@retval #SRE_OK                 0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see SRE_McSemCreate
*/
extern UINT32 SRE_McSemDelete(MCSEM_HANDLE_T uwSemHandle);

/**
 *@ingroup SRE_mcsem
 *@brief 重设核间信号量计数器数值函数。
 *
 *@par 描述:
 *根据用户指定的核间信号量句柄，重设核间信号量计数器数值。
 *@attention
 *@li 如果有任务阻塞于该核间信号量，则重设失败。
 *
 *@param uwSemHandle [IN] 类型为#MCSEM_HANDLE_T，核间信号量句柄，来源于核间信号量创建成功的输出值。
 *@param wCount [IN] 类型为#INT32，计数器设定值，取值范围为[-254, 254]。
 *
 *@retval #OS_ERRNO_MCSEM_INVALID  0x02001301，核间信号量句柄为非法值，或已被删除。
 *@retval #OS_ERRNO_MCSEM_OVERFLOW 0x02001308，计数器设定值超出最大范围。
 *@retval #OS_ERRNO_MCSEM_PENDED   0x02001309，有任务阻塞于该核间信号量，禁止重设。
 *@retval #SRE_OK                  0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see SRE_McSemCreate | SRE_McSemCountGet
*/
extern UINT32 SRE_McSemReset(MCSEM_HANDLE_T uwSemHandle, INT32 wCount);

/**
 *@ingroup SRE_mcsem
 *@brief 获取核间信号量计数器数值。
 *
 *@par 描述:
 *根据用户指定的核间信号量句柄，获取核间信号量计数器数值。
 *@attention
 *
 *@param uwSemHandle [IN] 类型为#MCSEM_HANDLE_T，核间信号量句柄，来源于核间信号量创建成功的输出值。
 *@param pwCount     [OUT] 类型为#INT32 * ，返回给用户的当前信号量计数值，范围[-254, 254]。
 *
 *@retval #OS_ERRNO_MCSEM_INVALID      0x02001301，获取失败，核间信号量句柄错误或已被删除。
 *@retval #OS_ERRNO_MCSEM_INPUT_ERROR  0x0200130C，指针为空
 *@retval #SRE_OK                      0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see SRE_McSemCreate | SRE_McSemReset
*/
extern UINT32 SRE_McSemCountGet(MCSEM_HANDLE_T uwSemHandle, INT32 * pwCount);

/**
 *@ingroup SRE_mcsem
 *@brief 申请一个核间信号量。
 *
 *@par 描述:
 *根据用户指定的句柄和等待时间，申请核间信号量，若其计数器值大于0，则返回成功。
 *@attention
 *@li 在osStart之前不能调用该接口。
 *@li 等待时间可以选择零等待、等待特定时间、永久等待。
 *@li 当没有信号量资源时，非零等待该函数只能被任务调用。
 *@li 当有可用资源时，系统允许中断和锁任务pend信号量成功。
 *@li 当没有可用资源，禁止中断处理函数和锁任务阻塞该核间信号量。
 *@li 如果系统没有打开TICK开关，将会以#OS_WAIT_FOREVER模式进行等待。
 *
 *@param uwSemHandle [IN] 类型为#MCSEM_HANDLE_T，核间信号量句柄，来源于核间信号量创建成功的输出值。
 *@param uwTimeout   [IN] 类型为#UINT32，等待时间限制，单位为tick，取值范围为[0, 0xffffffff]。
 *#OS_NO_WAIT或0表示不等待，#OS_WAIT_FOREVER或0xffffffff表示永久等待。
 *
 *@retval #OS_ERRNO_MCSEM_INVALID      0x02001301，核间信号量句柄为非法值，或已被删除。
 *@retval #OS_ERRNO_MCSEM_UNAVAILABLE  0x02001304，核间信号量零等待时获取失败。
 *@retval #OS_ERRNO_MCSEM_PEND_INTERR  0x02001305，中断处理函数禁止发生阻塞。
 *@retval #OS_ERRNO_MCSEM_PEND_IN_LOCK 0x02001306，系统可用资源为0任务切换锁定时，禁止任务发生阻塞。
 *@retval #OS_ERRNO_MCSEM_TIMEOUT      0x02001307，任务等待核间信号量超时。
 *@retval #SRE_OK                      0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see SRE_McSemPost
*/
extern UINT32 SRE_McSemPend(MCSEM_HANDLE_T uwSemHandle, UINT32 uwTimeout);

/**
 *@ingroup SRE_mcsem
 *@brief 释放指定的核间信号量。
 *
 *@par 描述:
 *根据用户指定的句柄，释放核间信号量。
 *互斥模式:
 *若没有任务等待该核间信号量，则直接将计数器加1返回。
 *否则唤醒为此核间信号量阻塞的任务列表中的第一个任务（最早阻塞的）。
 *同步模式:
 *若没有任务等待该核间信号量或者释放的次数小于设定的同步次数，则直接将计数器加1返回。
 *否则唤醒为此核间信号量阻塞的任务列表中的第一个任务（最早阻塞的）。
 *@attention
 *@li 在osStart之前不能调用该接口
 *@li 如果唤醒的任务非本核，则会触发核间中断，发送唤醒任务的操作。
 *@li 在未锁任务的情况下，如果唤醒的任务优先级高于当前任务，则会立刻发生任务切换。
 *
 *@param uwSemHandle [IN] 类型为#MCSEM_HANDLE_T，核间信号量句柄，来源于核间信号量创建成功的输出值。
 *
 *@retval #OS_ERRNO_MCSEM_INVALID  0x02001301，核间信号量句柄为非法值，或已被删除。
 *@retval #OS_ERRNO_MCSEM_OVERFLOW 0x02001308，核间信号量计数超出最大范围。
 *@retval #OS_ERRNO_IPC_SHQ_FULL   0x02001486，6181和6108平台下，发送核间中断，共享队列已满。
 *@retval #SRE_OK                  0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see SRE_McSemPend
*/
extern UINT32 SRE_McSemPost(MCSEM_HANDLE_T uwSemHandle);

/**
 *@ingroup SRE_mcsem
 *@brief 获取核间信号量上的阻塞任务信息。
 *
 *@par 描述:
 *根据用户指定的核间信号量句柄，获取阻塞于该核间信号量上的任务个数以及相应的任务PID。
 *@attention
 *@li 若有任务阻塞于该核间信号量，则返回阻塞于该核间信号量的任务数目，以及相应任务的PID。
 *@li 若没有任务阻塞于该核间信号量，则返回阻塞于该核间信号量的任务数目为0。
 *@li 若指定的内存长度小于实际所需长度，则返回错误码，但指定的内存中的任务PID依然有效。
 *@li 用户应保证存储任务PID的内存空间足够大，建议将uwBufLen配置为(#OS_TSK_MAX_SUPPORT_NUM + 1) * #OS_MAX_CORE_NUM * 4bytes。
 *
 *@param uwSemHandle [IN]  类型为#MCSEM_HANDLE_T，核间信号量句柄，来源于核间信号量创建成功的输出值。
 *@param puwTskCnt   [OUT] 类型为#UINT32 *，返回给用户的阻塞于该核间信号量的任务数目。
 *@param puwPidBuf   [OUT] 类型为#UINT32 *，由用户指定的内存区域首地址，用于存储阻塞于指定核间信号量的任务PID。
 *@param uwBufLen    [IN]  类型为#UINT32，用户指定的内存区域的长度（单位：字节）。
 *
 *@retval #OS_ERRNO_MCSEM_INVALID               0x02001301，核间信号量句柄为非法值，或已被删除。
 *@retval #OS_ERRNO_MCSEM_INPUT_ERROR           0x0200130C，指针为空或者uwBufLen小于4。
 *@retval #OS_ERRNO_MCSEM_INPUT_BUF_NOT_ENOUGH  0x0200130D，指定的内存空间不足，但内存中的任务PID依然有效。
 *@retval #SRE_OK                               0x00000000，操作成功。
 *@par 依赖:
 *@li sre_mcsem.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C01
 *@see 无
*/
extern UINT32 SRE_McSemPendListGet( MCSEM_HANDLE_T uwSemHandle,
                                    UINT32 *puwTskCnt,
                                    UINT32 *puwPidBuf,
                                    UINT32  uwBufLen );

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MCSEM_H */



