/**
* @file sre_cpup.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：CPU占用率模块对外头文件。 \n
*/

/** @defgroup SRE_cpup CPU占用率
   *@ingroup SRE_kernel
*/

#ifndef _SRE_CPUP_H
#define _SRE_CPUP_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP模式配置不正确。
 *
 * 值: 0x02000c00
 *
 * 解决方案: CPUP模式必须配置为OS_CPUP_MODE_SYS或者OS_CPUP_MODE_THREAD。
 */
#define OS_ERRNO_CPUP_MODE_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x00)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：参数(CPUP告警阈值)设定不在规定范围(0,10000]。
 *
 * 值: 0x02000c01
 *
 * 解决方案: CPUP告警阈值设定在规定范围(0,10000]内。
 */
#define OS_ERRNO_CPUP_INTERVAL_NOT_SUITED       SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x01)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：指针参数为NULL。
 *
 * 值: 0x02000c02
 *
 * 解决方案: 传入非0的有效地址。
 */
#define OS_ERRNO_CPUP_PTR_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x02)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：恢复阈值设定不小于告警阈值。
 *
 * 值: 0x02000c03
 *
 * 解决方案: 恢复阈值小于告警阈值。
 */
#define OS_ERRNO_CPUP_RESUME_NOT_SUITED         SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x03)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP初始化申请内存失败。
 *
 * 值: 0x02000c04
 *
 * 解决方案: 确认缺省静态内存是否足够，以及采样个数(参见配置宏OS_CPUP_SAMPLE_RECORD_NUM)是否过大。
 */
#define OS_ERRNO_CPUP_NO_MEMORY                 SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x04)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：在osStart之前调用CPUP模块相关功能接口。
 *
 * 值: 0x02000c05
 *
 * 解决方案: 调用CPUP模块功能接口时，请查看是否在osStart之后。
 */
#define OS_ERRNO_CPUP_OS_NOT_STARTED            SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x05)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP配置模式不正确。
 *
 * 值: 0x02000c06
 *
 * 解决方案: CPUP模块配置模式必须配置正确的模式，才能调用相对应的接口。
 */
#define OS_ERRNO_CPUP_MODE_NOT_CORRECT          SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x06)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP采样时间间隔为0。
 *
 * 值: 0x02000c07
 *
 * 解决方案: 系统级CPUP设置采样时间间隔必须大于0，当CPUP告警功能打开时，线程级CPUP采样时间间隔也必须大于0。
 */
#define OS_ERRNO_CPUP_SAMPLE_TIME_ZERO          SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x07)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：指定核号非法。
 *
 * 值: 0x02000c08
 *
 * 解决方案: 指定核小于最大核数。
 */
#define OS_ERRNO_CPUP_COREID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x08)

/**
 * @ingroup SRE_cpup
 * 事件错误码：获取CPUP时入参任务ID非法。
 *
 * 值: 0x02000c09
 *
 * 解决方案: 请输入合法任务ID。
 */
#define OS_ERRNO_CPUP_TASKID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_CPUP, 0x09)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP采样个数为零。
 *
 * 值: 0x02000c0a
 *
 * 解决方案: 设置采样地个数在(0,30]之间。
 */
#define OS_ERRNO_CPUP_SAMPLE_NUM_ZERO           SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0A)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP功能开关未打开或者未初始化时，获取CPUP、设置告警阈值或者补偿IDLE钩子执行时间。
 *
 * 值: 0x02000c0b
 *
 * 解决方案: 需保证在打开功能开关,在osStart之后才能获取CPUP、设置告警阈值或者补偿IDLE钩子执行时间。
 */
#define OS_ERRNO_CPUP_NOT_INITED                SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0B)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：使用获取线程级所有线程的CPUP接口时，输入的线程数为0。
 *
 * 值: 0x02000c0c
 *
 * 解决方案: 使用获取线程级所有线程的CPUP接口时，输入的线程数必须大于0
 */
#define OS_ERRNO_CPUP_THREAD_INNUM_INVALID      SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0C)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：获取指定任务CPU占用率时，该任务还未创建或已删除。
 *
 * 值: 0x02000c0d
 *
 * 解决方案: 需保证获取指定任务CPU占用率时，该任务已经创建且未被删除。
 */
#define OS_ERRNO_CPUP_TASK_NO_CREATE            SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0D)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：补偿系统级CPUP时，输入的钩子为NULL。
 *
 * 值: 0x02000c0e
 *
 * 解决方案: 补偿系统级CPUP时，需保证输入的钩子为非NULL。
 */
#define OS_ERRNO_CPUP_COMPEN_HOOK_NULL          SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0E)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：补偿系统级CPUP时，输入的补偿值为0，或者去除IDLE钩子补偿时，输入的值为0。
 *
 * 值: 0x02000c0f
 *
 * 解决方案: 当补偿系统级CPUP时，输入的补偿值大于0；当去除IDLE钩子补偿时，输入的值不能等于0。
 */
#define OS_ERRNO_CPUP_COMPEN_VALUE_ZERO         SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x0F)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：补偿系统级CPUP时，输入的钩子未注册。
 *
 * 值: 0x02000c10
 *
 * 解决方案: 补偿系统级CPUP时，输入的钩子已注册。
 */
#define OS_ERRNO_CPUP_COMPEN_HOOK_NO_REG        SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x10)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：补偿系统级CPUP IDLE钩子时，输入的补偿值大于等于采样周期；去除IDLE钩子补偿时，输入的值大于已经补偿值的总大小。
 *
 * 值: 0x02000c11
 *
 * 解决方案: 补偿系统级CPUP时，需保证输入的补偿值小于采样周期；当去除IDLE钩子补偿值时，输入的去除值不能大于已经补偿值的总大小。
 */
#define OS_ERRNO_CPUP_COMPEN_VALUE_TOO_LARGE    SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x11)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP告警恢复及CPUP告警阈值配置错误。
 *
 * 值: 0x02000c12
 *
 * 解决方案: CPUP告警阈值设定应该小于CPUP告警恢复阈值。
 */
#define OS_ERRNO_CPUP_RESUME_VALUE_ERROR        SRE_ERRNO_OS_ERROR(OS_MID_CPUP,0x12)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：g_ullBaseValue变量所在内存被踩。
 *
 * 值: 0x03000c13
 *
 * 解决方案: 定位g_ullBaseValue变量何时被踩，修正踩内存错误。
 */
#define OS_ERRNO_CPUP_MEM_DAMAGED_ERROR         SRE_ERRNO_OS_FATAL(OS_MID_CPUP,0x13)

/**
 * @ingroup SRE_cpup
 * CPUP错误码：CPUP名字申请失败。
 *
 * 值: 0x03000c14
 *
 * 解决方案: 增大共享名字空间大小。
 */
#define OS_ERRNO_CPUP_NAME_ALLOC_FAILED         SRE_ERRNO_OS_FATAL(OS_MID_CPUP,0x14)

/**
 * @ingroup SRE_cpup
 * CPU占用率告警标志。
 */
#define CPUP_INFO_TYPE_OVERLOAD                 0x01

/**
 * @ingroup SRE_cpup
 * CPU占用率恢复告警标志。
 */
#define CPUP_INFO_TYPE_RECONVERT                0x02

/**
 *@ingroup SRE_cpup
 *CPU占用率使用模式：系统级CPUP。
 */
#define  OS_CPUP_MODE_SYS                       0x01

/**
 *@ingroup SRE_cpup
 *CPU占用率使用模式：线程级CPUP。
 */
#define  OS_CPUP_MODE_THREAD                    0x02

/**
 * @ingroup  SRE_cpup
 *
 * CPUP告警信息。
 */
typedef struct tagCpupWarnInfo
{
    UINT16 usType;            /**< CPU占用率告警信息类型*/
    UINT16 usReserve;         /**< 保留                 */
}CPUP_WARNINFO_S;

/**
*@ingroup SRE_cpup
*@brief CPUP告警回调函数类型定义。
*
*@par 描述:
*通过该回调函数的类型定义回调函数钩子。
*@attention 无
*
*@param  #CPUP_WARNINFO_S*   [IN] 类型#CPUP_WARNINFO_S*，CPUP告警信息。
*
*@retval 无。
*@par 依赖:
*<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
*@since RTOSck V100R001C01
*@see 无。
*/
typedef VOID (*CPUP_HOOK_FUNC)(CPUP_WARNINFO_S*);

/**
 * @ingroup SRE_cpup
 * 线程级CPU占用率结构体。
 */
typedef struct tagCpupThread
{
    UINT32 uwID;            /**< 线程ID                  */
    UINT16 usUsage;         /**< 占用率，取值[0,10000]   */
    UINT16 usResv;          /**< 保留                    */
} OS_CPUP_THREAD_S;

/**
* @ingroup  SRE_cpup
* 设置cpu占用率的注册信息结构体。
*/
typedef struct tagCpupModInfo
{
    UINT32 uwCpupType;      /**< CPUP配置模式            */
    BOOL   bCpupWarnFlag;   /**< CPUP告警标志            */
    UINT32 uwSampleNum;     /**< 保存的采样个数          */
    UINT32 uwSampleTime;    /**< 采样间隔，单位tick      */
    UINT32 uwTickPerSec;    /**< 每秒的tick数            */
    UINT32 uwCyclePerSec;   /**< 每秒的cycle数           */
    UINT32 uwWarn;          /**< CPU占用率告警阈值       */
    UINT32 uwResume;        /**< CPU占用率告警恢复阈值   */
} CPUP_MOD_INFO_S;


/**
*@ingroup SRE_cpup
*@brief 获取当前cpu占用率。
*
*@par 描述:
*通过本接口获取当前cpu占用率。
*@attention
* <ul>
* <li>该接口必须在CPUP模块裁剪开关打开，并在osStart之后才能调用此接口，否则返回0xffffffff。</li>
* <li>精度为万分之一。</li>
* <li>为了减小CPUP统计对线程调度的性能影响，OS采用了基于IDLE计数的统计算法，统计结果会有一定误差，误差不超过百分之五。</li>
* </ul>
*
*@param 无
*
*@retval #0xffffffff      获取失败，CPUP裁剪开关未打开，或未初始化，或者在osStart之前调用。
*@retval #[0,10000]       返回当前cpu占用率。
*@par 依赖:
*<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupAvg | SRE_CpupThread
*/
extern UINT32 SRE_CpupNow(VOID);

/**
*@ingroup SRE_cpup
*@brief 获取指定核当前的CPU占用率
*
*@par 描述:
*通过用户输入的核号uwCoreId，获取指定核当前cpu占用率。
*@attention
* <ul>
* <li>osStart之前不能调用此接口。</li>
* <li>对于SD6182/SD6157/SD6183平台，支持实例间查询其他核的当前CPU占用率。</li>
* <li>在使用该接口获取指定核当前CPU占用率时，如果其使用线程级CPUP模式，并且采样周期配置为0，该获取功能需要依赖指定核计算其CPU占用率(调用#SRE_CpupNow或#SRE_CpupThread)。</li>
* <li>调用此接口时，如果指定核未打开CPU占用率裁剪开关，或者未运行，或者核号非法，返回的是0xffffffff。</li>
* </ul>
*
*@param uwCoreId [IN] 类型#UINT32，指定核ID。
*
*@retval #0xffffffff         指定核号非法、指定核CPUP裁剪开关未打开或未初始化、指定核未启动情况下，返回0xffffffff。
*@retval #[0,10000]          返回指定核当前cpu占用率。
*@par 依赖:
*<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupAvg | SRE_CpupNow
*/
extern UINT32 SRE_CpuUsageGet(UINT32 uwCoreId);


#if (OS_OPTION_CPUP_SYS == YES)
/**
*@ingroup SRE_cpup
*@brief 获取平均cpu占用率接口。
*
*@par 描述:
*通过本接口获取预先在配置项OS_CPUP_SAMPLE_RECORD_NUM中指定采样点的平均cpu占用率。
*@attention
* <ul>
* <li>该接口必须在CPUP模块裁剪开关打开，并在osStart之后才能使用。</li>
* <li>若系统CPUP模式配置为线程级，或在osStart之前调用，将返回0xffffffff，并且上报错误码。</li>
* <li>当且仅当CPUP模式配置为系统级时，该接口有效。</li>
* </ul>
*
*@param 无
*
*@retval #0xffffffff      获取失败。
*@retval #[0,10000]       返回平均cpu占用率。
*@par 依赖:
*<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupNow | SRE_CpupPeak
*/
extern UINT32 SRE_CpupAvg(VOID);

/**
*@ingroup SRE_cpup
*@brief 获取cpu占用率峰值。
*
*@par 描述:
*通过本接口获取cpu占用率峰值。
*@attention
* <ul>
* <li>在计算第一次系统CPU占用率之前，调用接口获取到的CPU占用率峰值为0。</li>
* </ul>
*
*@param 无
*
*@retval #[0,10000]          返回系统级CPU占用率峰值。
*@par 依赖:
*<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupAvg | SRE_CpupNow | SRE_CpupPeakClear
*/
extern UINT32  SRE_CpupPeak(VOID);

/**
*@ingroup SRE_cpup
*@brief 清空cpu占用率峰值。
*
*@par 描述:
*通过本接口将cpu占用率峰值置零。
*@attention 无
*
*@param 无
*
*@retval 无
*@par 依赖:
*<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
*@since RTOSck V100R001C01
*@see SRE_CpupPeak
*/
extern VOID  SRE_CpupPeakClear(VOID);

/**
 *@ingroup SRE_cpup
 *@brief 补偿IDLE钩子执行时间。
 *
 *@par 描述:
 *根据用户输入的指定IDLE钩子补偿时间，对指定的IDLE钩子执行时间进行补偿。
 *@attention
 *<ul>
 * <li>该接口必须在CPUP模块裁剪开关打开，并在其初始化之后才能使用。</li>
 * <li>当且仅当CPUP模式配置为系统级时，该接口有效。</li>
 * <li>若对指定的IDLE钩子执行时间进行补偿，则该钩子执行时间不计算在负载内。</li>
 * <li>对单个IDLE钩子进行多次补偿，以及所有IDLE钩子的补偿值会进行累加,补偿值总大小的合法性由用户保证。</li>
 * <li>用户在对IDLE钩子进行补偿时，必须保证补偿值的准确性(需要考虑IDLE钩子执行时Cache是否命中的因素)，否则会导致系统CPU占用率统计不准确。</li>
 * <li>若IDLE钩子时间补偿值错误，可能造成CPU占用率计算异常（超过10000或低于0）。此种情况，操作系统对计算值做容错处理，若CPU占用率超过10000，则将计算值更正为10000。若CPU占用率低于0，则将计算值更正为0。</li>
 *</ul>
 *
 *@param  pfnHook    [IN] 类型#OS_VOID_FUNC，输入的ILDE钩子。
 *@param  uwAddCycle [IN] 类型#UINT32，针对指定IDLE钩子补偿值大小。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED             0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT       0x02000C06，CPUP模式配置为线程级。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED         0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NULL       0x02000C0E，输入的IDLE钩子为NULL。
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_ZERO      0x02000C0F，输入的补偿值大小为0。
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NO_REG     0x02000C10，输入的的IDLE钩子未注册。
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_TOO_LARGE 0x02000C11，输入的补偿值大小太大，超过了采样周期。
 *@retval #SRE_OK                               0x00000000，补偿成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupNow
 */
extern UINT32 SRE_CpupIdleHookLoadAdd(OS_VOID_FUNC pfnHook, UINT32 uwAddCycle);

/**
 *@ingroup SRE_cpup
 *@brief 去除IDLE钩子补偿时间。
 *
 *@par 描述:
 *根据用户输入的指定IDLE钩子补偿时间，对IDLE钩子补偿时间进行去除。
 *@attention
 *<ul>
 * <li>该接口必须在CPUP模块裁剪开关打开，并在osStart之后才能使用。</li>
 * <li>当且仅当CPUP模式配置为系统级时，该接口有效。</li>
 * <li>若对指定的IDLE钩子执行时间进行补偿，则该钩子执行时间不计算在负载内。</li>
 * <li>去除ILDE钩子的补偿时间大小合法性由用户保证。</li>
 *</ul>
 *
 *@param  pfnHook    [IN] 类型#OS_VOID_FUNC，存放中断线程的CPUP信息指针。
 *@param  uwSubCycle [IN] 类型#UINT32，针对指定IDLE钩子补偿值大小。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED             0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT       0x02000C06，CPUP模式配置为线程级。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED         0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NULL       0x02000C0E，输入的IDLE钩子为NULL。
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_ZERO      0x02000C0F，输入的去除补偿值大小为0。
 *@retval #OS_ERRNO_CPUP_COMPEN_HOOK_NO_REG     0x02000C10，输入的的IDLE钩子未注册。
 *@retval #OS_ERRNO_CPUP_COMPEN_VALUE_TOO_LARGE 0x02000C11，输入的去除补偿值大小太大，超过了IDLE钩子已补偿值总大小。
 *@retval #SRE_OK                               0x00000000，去除补偿成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupNow
 */
extern UINT32 SRE_CpupIdleHookLoadSub(OS_VOID_FUNC pfnHook, UINT32 uwSubCycle);
#endif

#if (OS_OPTION_CPUP_THREAD == YES)
/**
 *@ingroup SRE_cpup
 *@brief 获取指定个数的线程的CPU占用率。
 *
 *@par 描述:
 *根据用户输入的线程个数，获取指定个数的线程CPU占用率。
 *@attention
 *<ul>
 * <li>当且仅当CPUP模式配置为线程级时，该接口有效。</li>
 * <li>当配置项中的采样周期值等于0时，线程级CPUP采样周期为两次调用该接口或者SRE_CpupNow之间
   的间隔。否则，线程级CPUP采样周期为配置项中的OS_CPUP_SAMPLE_INTERVAL大小。</li>
 * <li>输出的实际线程个数不大于系统中实际的线程个数(任务个数和一个中断线程)。</li>
 * <li>若输入的线程个数为1，则仅输出中断线程(除任务线程以外的线程统称)的CPUP信息。</li>
 * <li>若在一个采样周期内有任务被删除，则统计的任务线程和中断线程CPUP总和小于10000。</li>
 *</ul>
 *
 *@param  uwInNum   [IN]  类型#UINT32，输入的线程个数。
 *@param  pstCpup   [OUT] 类型#OS_CPUP_THREAD_S *，缓冲区，输出参数，用于填写输出个数线程的CPUP信息。
 *@param  puwOutNum [OUT] 类型#UINT32 *，保存输出的实际线程个数指针。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT     0x02000C06，CPUP模式配置为线程级。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02，参数指针为NULL。
 *@retval #OS_ERRNO_CPUP_THREAD_INNUM_INVALID 0x02000C0C，输入的线程个数为0。
 *@retval #SRE_OK                             0x00000000，获取成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupNow
 */
extern UINT32 SRE_CpupThread(UINT32 uwInNum, OS_CPUP_THREAD_S *pstCpup, UINT32 *puwOutNum);

/**
 *@ingroup SRE_cpup
 *@brief 获取指定任务的CPU占用率。
 *
 *@par 描述:
 *根据用户输入的任务ID，获取指定任务的CPU占用率。
 *@attention
 *<ul>
 * <li>当且仅当CPUP模式配置为线程级时，该接口有效。</li>
 * <li>当采样周期配置为0调用此接口时，获取到的是，上一采样周期结束到调用此接口时间内指定任务的CPU占用率。</li>
 * <li>当采样周期配置不为0时，获取到的是，上一采样周期内指定任务的CPU占用率。</li>
 *</ul>
 *
 *@param  uwTaskId    [IN]  类型#UINT32，输入的任务ID。
 *@param  puwTaskRate [OUT] 类型#UINT32 *，存放指定任务线程的CPUP信息指针。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT     0x02000C06，CPUP模式配置不为线程级。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02，参数指针为NULL。
 *@retval #OS_ERRNO_CPUP_TASKID_INVALID       0x02000C09，输入的任务ID非法。
 *@retval #OS_ERRNO_CPUP_TASK_NO_CREATE       0x02000C0D，输入的任务未创建或者已被删除。
 *@retval #SRE_OK                             0x00000000，获取成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R001C00
 *@see SRE_CpupThread
 */
extern UINT32 SRE_CpupTaskGetById(UINT32 uwTaskId, UINT32 *puwTaskRate);

/**
 *@ingroup SRE_cpup
 *@brief 获取中断线程的CPU占用率。
 *
 *@par 描述:
 *获取中断线程的CPU占用率。
 *@attention
 *<ul>
 * <li>当且仅当CPUP模式配置为线程级时，该接口有效。</li>
 * <li>当采样周期配置为0调用此接口时，获取到的是，上一采样周期结束到调用此接口时间内中断线程的CPU占用率。</li>
 * <li>当采样周期配置不为0时，获取到的是，上一采样周期内中断线程的CPU占用率。</li>
 *</ul>
 *
 *@param  puwIntRate [OUT] 类型#UINT32 *，存放中断线程的CPUP信息指针。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_MODE_NOT_CORRECT     0x02000C06，CPUP模式配置不为线程级。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02，参数指针为NULL。
 *@retval #SRE_OK                             0x00000000，获取成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_CpupTaskGetById
 */
extern UINT32 SRE_CpupIntGet(UINT32 *puwIntRate);
#endif

#if (OS_OPTION_CPUP_WARN == YES)
/**
 *@ingroup SRE_cpup
 *@brief 设置CPU占用率告警阈值。
 *
 *@par 描述:
 *根据用户配置的CPU占用率告警阈值uwWarn和告警恢复阈值uwResume，设置告警和恢复阈值。
 *@attention
 *<ul>
 * <li>osStart之前不能调用此接口。</li>
 *</ul>
 *
 *@param  uwWarn   [IN] 类型#UINT32，CPUP告警阈值。
 *@param  uwResume [IN] 类型#UINT32，CPUP恢复阈值。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED            0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED        0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_INTERVAL_NOT_SUITED   0x02000C01，阈值设定不在规定范围(0,10000]内。
 *@retval #OS_ERRNO_CPUP_RESUME_NOT_SUITED     0x02000C03, 恢复阈值设定不小于告警阈值。
 *@retval #SRE_OK                              0x00000000，阈值设定设定成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_CpupWarnValueGet
 */
extern UINT32 SRE_CpupWarnValueSet(UINT32  uwWarn, UINT32 uwResume);

/**
 *@ingroup SRE_cpup
 *@brief 查询CPUP告警阈值和告警恢复阈值
 *
 *@par 描述:
 *根据用户配置的告警阈值指针puwWarn和告警恢复阈值指针puwResume，查询告警阈值和告警恢复阈值
 *@attention
 *<ul>
 * <li>osStart之前不能调用此接口。</li>
 *</ul>
 *
 *@param  puwWarn   [OUT] 类型#UINT32 *，CPUP告警阈值。
 *@param  puwResume [OUT] 类型#UINT32 *，CPUP恢复阈值。
 *
 *@retval #OS_ERRNO_CPUP_NOT_INITED           0x02000C0B，CPUP裁剪开关未打开，或者未初始化。
 *@retval #OS_ERRNO_CPUP_OS_NOT_STARTED       0x02000C05，在osStart之前调用。
 *@retval #OS_ERRNO_CPUP_PTR_NULL             0x02000C02，参数指针为NULL。
 *@retval #SRE_OK                             0x00000000，获取成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_CpupWarnValueSet
 */
extern UINT32 SRE_CpupWarnValueGet(UINT32 * puwWarn, UINT32 * puwResume);


/**
 * @ingroup SRE_cpup
 * @brief 注册CPUP告警回调函数
 *
 * @par 描述:
 * 根据用户配置的回调函数pfnHook，注册CPUP告警回调函数
 * @attention
 *<ul>
 * <li>不允许重复或覆盖注册钩子。</li>
 * <li>pfnHook为NULL时，表示删除该钩子。</li>
 *</ul>
 *
 * @param  pfnHook  [IN] 类型#CPUP_HOOK_FUNC，CPU告警回调函数。
 *
 *@retval #OS_ERRNO_HOOK_FULL              0x02001604，重复注册CPU告警钩子。
 *@retval #SRE_OK                          0x00000000，注册成功。
 *@par 依赖:
 *<ul><li>sre_cpup.h：该接口声明所在的头文件。</li></ul>
 *@since RTOSck V100R001C01
 *@see 无。
 */
extern UINT32 SRE_CpupWarnHookReg(CPUP_HOOK_FUNC pfnHook);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CPUP_H */


