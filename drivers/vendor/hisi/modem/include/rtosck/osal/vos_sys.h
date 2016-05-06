/**
 * @file vos_sys.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL系统基本功能头文件。 \n
 */

/**@defgroup vos_sys 系统基本功能
 *@ingroup OSAL
*/

#ifndef __VOS_SYS_H__
#define __VOS_SYS_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup vos_sys
 * OSAL两个系统时间比较，第一个时间比第二个时间小。
 */
#define COMP_TIME_LT    1

/**
 * @ingroup vos_sys
 * OSAL两个系统时间比较，第一个时间与第二个时间相等。
 */
#define COMP_TIME_EQ    2

/**
 * @ingroup vos_sys
 * OSAL两个系统时间比较，第一个时间比第二个时间大。
 */
#define COMP_TIME_GT    3

/**
 * @ingroup vos_sys
 * OSAL日期数据结构类型。
 */
typedef struct tagDateS
{
    VOS_UINT32 d_usDate: 8;     /**< 日，取值1-31 */
    VOS_UINT32 d_usMonth: 8;    /**< 月，取值1-12 */
    VOS_UINT32 d_usYear: 16;    /**< 年，从1970开始 */
} DATE_S;

/**
 * @ingroup vos_sys
 * OSAL时间数据结构类型。
 */
typedef struct tagTimeS
{
    VOS_UINT32 t_usSecond: 8;   /**< 秒，取值0-59 */
    VOS_UINT32 t_usMinute: 8;   /**< 分，取值0-59 */
    VOS_UINT32 t_usHour:  16;   /**< 时，取值0-23 */
} TIME_S;

/**
 * @ingroup vos_sys
 * OSAL日期时间数据结构类型。
 */
typedef struct _tagDateTime
{
    DATE_S stDate;              /**< 日期，年月日 */
    TIME_S stTime;              /**< 事件，时分秒 */
} DATE_TIME_S;

/**
 * @ingroup  vos_sys
 * @brief 关中断。
 *
 * @par 描述:
 * 关闭全局可屏蔽中断。当操作可重入函数或全局变量时，为了防止其他任务改写资源而对其进行保护，需调用本接口。
 *
 * @attention 在关全局中断后，禁止调用引起内核调度的相关接口，如VOS_T_Delay接口。
 *
 * @param plRetSpl [OUT] 类型#VOS_INT32 *，保存关闭全局中断前的中断状态值。取值范围为非空。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，关中断成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_SplX
 */
extern VOS_UINT32 VOS_SplImp(VOS_INT32 *plRetSpl);

/**
 * @ingroup  vos_sys
 * @brief 开中断。
 *
 * @par 描述:
 * 恢复原中断状态寄存器。当结束对可重入函数或变量的操作后，需调用本接口。
 *
 * @attention
 *<ul>
 *<li>该接口必须和关闭全局中断或者是开启全局中断接口成对使用，以关全局中断或者开全局中断操作的返回值为入参。</li>
 *<li>以保证中断可以恢复到关全局中断或者开全局中断操作前的状态。</li>
 *</ul>
 *
 * @param lSpl [IN] 类型#VOS_INT32，关中断VOS_SplImp获取状态。取值范围为32位有符号整数。
 *
 * @retval #VOS_OK                              0x00000000，开中断成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_SplImp
 */
extern VOS_UINT32 VOS_SplX(VOS_INT32 lSpl);

/**
 * @ingroup  vos_sys
 * @brief 获取自系统启动到当前的累计运行时间。
 *
 * @par 描述:
 * 获取自系统启动到当前的64位绝对时间，存放在pulSecond和pulUSecond中。
 *
 * @attention 无
 *
 * @param pulSecond [OUT] 类型#VOS_UINT32 *，累计运行的秒数。取值范围为非空。
 * @param pulUSecond [OUT] 类型#VOS_UINT32 *，累计运行的不足一秒的微秒数。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pulSecond或pulUSecond为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取时间成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_Tm_BootInSec(VOS_UINT32 *pulSecond, VOS_UINT32 *pulUSecond);

/**
 * @ingroup  vos_sys
 * @brief 获取自系统启动到当前的累计运行时间。
 *
 * @par 描述:
 * 获取自系统启动到当前的64位绝对毫秒数，存放在pulRetTimeInMillSecHigh和pulRetTimeInMillSecLow中。
 *
 * @attention 无
 *
 * @param pulRetTimeInMillSecHigh [OUT] 类型#VOS_UINT32 *，累计运行时间用毫秒表示的高位。取值范围为非空。
 * @param pulRetTimeInMillSecLow [OUT] 类型#VOS_UINT32 *，累计运行时间用毫秒表示的低位。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pulRetTimeInMillSecHigh或pulRetTimeInMillSecLow为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取时间成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_BootInSec
 */
extern VOS_UINT32 VOS_Tm_Now(VOS_UINT32 *pulRetTimeInMillSecHigh, VOS_UINT32 *pulRetTimeInMillSecLow);

/**
 * @ingroup  vos_sys
 * @brief 获取系统当前的cputick数。
 *
 * @par 描述:
 * 通过读取系统的时基寄存器，得到系统当前的cputick数。
 *
 * @attention 无
 *
 * @param pLow [OUT] 类型#VOS_UINT32 *，系统cputick的低32位。取值范围为非空。
 * @param pHigh [OUT] 类型#VOS_UINT32 *，系统cputick的高32位。取值范围为非空。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_TickGet
 */
extern VOS_VOID VOS_GetCpuTick(VOS_UINT32 *pLow, VOS_UINT32 *pHigh);

/**
 * @ingroup  vos_sys
 * @brief 获取系统当前的Tick数。
 *
 * @par 描述:
 * 获取系统当前的Tick数。
 *
 * @attention 无
 *
 * @param puiHigh [OUT] 类型#VOS_UINT32 *，系统Tick的高32位。取值范围为非空。
 * @param puiLow [OUT] 类型#VOS_UINT32 *，系统Tick的低32位。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，puiHigh或puiLow为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取Tick数成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetCpuTick
 */
extern VOS_UINT32 VOS_TickGet(VOS_UINT32 *puiHigh, VOS_UINT32 *puiLow);

/**
 * @ingroup  vos_sys
 * @brief 获取cpuTick与Tick转换的基值。
 *
 * @par 描述:
 * 通过全局变量，获取cpuTick与Tick转换的基值，即获取多少个cpuTick相当于一个Tick。
 *
 * @attention 无
 *
 * @param puiCpuTickBase [OUT] 类型#VOS_UINT32 *，存放cpuTick基值的指针。cpuTick基值单位为cpuTick/Tick。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，puiCpuTickBase为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取cpuTick与Tick转换的基值成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_UINT32 VOS_GetCpuTickBase(VOS_UINT32 *puiCpuTickBase);

/**
 * @ingroup  vos_sys
 * @brief 将给定的秒数换算为Tick数。
 *
 * @par 描述:
 * 将给定的秒数换算为Tick数。通过含义为每秒所包含的Tick数的全局变量，把给定的秒数换算为Tick数。
 *
 * @attention 无
 *
 * @param ulSecs [IN] 类型#VOS_UINT32，需要转换为Tick数的秒数。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval #VOS_NULL_DWORD                      0xFFFFFFFF，计算溢出。
 * @retval #正整数                              转换后的Tick数。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_UINT32 VOS_TmSecToTick(VOS_UINT32 ulSecs);

/**
 * @ingroup  vos_sys
 * @brief 获取当前系统时间(格式为LocalTime)。
 *
 * @par 描述:
 * 获取当前系统时间(格式为LocalTime)，包含毫秒。
 *
 * @attention
 * <ul><li>该接口获取的时间只能精确到秒，第三个参数的返回值总为零。</li></ul>
 *
 * @param pRetDate [OUT] 类型#DATE_S *，获取的日期。取值范围为非空。
 * @param pRetTime [OUT] 类型#TIME_S *，获取的时间。取值范围为非空。
 * @param pulMillSec [OUT] 类型#VOS_UINT32 *，获取的毫秒，该参数的返回值总为零。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pRetDate、pRetTime或pulMillSec为空，用户需要检查自己的输入参数。
 * @retval #VOS_ERROR                           0xFFFFFFFF，函数执行失败。
 * @retval #VOS_OK                              0x00000000，获取时间成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_Tm_Get(DATE_S *pRetDate, TIME_S *pRetTime, VOS_UINT32 *pulMillSec);

/**
 * @ingroup  vos_sys
 * @brief 获取自1970年1月1日0时0分0秒至当前时间的所过秒数。
 *
 * @par 描述:
 * 获取自1970年1月1日0时0分0秒至当前时间的所过的秒数，存放在pulRetTimeInMillSecHigh和pulRetTimeInMillSecLow中。
 *
 * @attention 无
 *
 * @param pulSecHigh [OUT] 类型#VOS_UINT32 *，所过秒数的高位。取值范围为非空。
 * @param pulSecLow [OUT] 类型#VOS_UINT32 *，所过秒数的低位。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pulRetTimeInMillSecHigh或pulRetTimeInMillSecLow为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取秒数成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now | VOS_Tm_Get | VOS_Tm_NowInSec
 */
extern VOS_UINT32 VOS_Tm_Since1970(VOS_UINT32 *pulSecHigh, VOS_UINT32 *pulSecLow);

/**
 * @ingroup  vos_sys
 * @brief 获取自1970年1月1日0时0分0秒到当前的秒数。
 *
 * @par 描述:
 * 获取自1970年1月1日0时0分0秒到当前时间的32位绝对秒数，存放在pulRetTimeInSec中。
 *
 * @attention 无
 *
 * @param pulRetTimeInSec [OUT] 类型#VOS_UINT32 *，自1970年1月1日0时0分0秒到当前的秒数。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pulRetTimeInSec为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取时间成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now | VOS_Tm_Get | VOS_Tm_Since1970
 */
extern VOS_UINT32 VOS_Tm_NowInSec(VOS_UINT32 *pulRetTimeInSec);

/**
 * @ingroup  vos_sys
 * @brief 获取当前时间(格式LocalTime)。
 *
 * @par 描述:
 * 获取当前时间(格式LocalTime)，时间信息压缩存储在整数中。
 * 年月日时分秒毫秒的信息表示如下: 年月日信息存储在一个32位数据中，格式为 Y/M/D (对应位数 31-16/15-8/7-0) 时分秒信息存储在一个32位数据中，格式为 h/m/s (对应位数 31-16/15-8/7-0) 毫秒用一个32位数表示，值总为零。
 *
 * @attention
 * <ul><li>该接口获取的时间只能精确到秒，第三个差数的返回值总为零。</li></ul>
 *
 * @param pulRetDate [OUT] 类型#VOS_UINT32 *，当前时间的年月日信息。取值范围为非空。
 * @param pulRetTime [OUT] 类型#VOS_UINT32 *，当前时间的时分秒信息。取值范围为非空。
 * @param pulRetMillSec [OUT] 类型#VOS_UINT32 *，当前时间的毫秒信息，该参数的返回值总为零。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pulRetDate、pulRetTime或pulRetMillSec为空。
 * @retval #VOS_ERROR                           0xFFFFFFFF，函数执行失败。
 * @retval #VOS_OK                              0x00000000，获取时间成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_SYS_GetCurrentTime(VOS_UINT32 *pulRetDate, VOS_UINT32 *pulRetTime, VOS_UINT32 *pulRetMillSec);

/**
 * @ingroup  vos_sys
 * @brief 获取自系统启动到当前的累计运行时间。
 *
 * @par 描述:
 * 获取自系统启动到当前的64位绝对毫秒数，存放在pulMillSecHigh和pulMillSecLow中。
 *
 * @attention 无
 *
 * @param pulMillSecHigh [OUT] 类型#VOS_UINT32 *，累计运行时间用毫秒表示的高位。取值范围为非空。
 * @param pulMillSecLow [OUT] 类型#VOS_UINT32 *，累计运行时间用毫秒表示的低位。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pulMillSecHigh或pulMillSecLow为空，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取时间成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_TmNow(VOS_UINT32 *pulMillSecHigh, VOS_UINT32 *pulMillSecLow);

/**
 * @ingroup  vos_sys
 * @brief 比较两个合法的系统时间，返回比较的结果。
 *
 * @par 描述:
 * 比较两个合法的系统时间，返回比较的结果。当时间pFirst小于时间pSecond时，返回1。当时间pFirst等于时间pSecond时，返回2。当时间pFirst大于时间pSecond时，返回3。返回其它值为错误码。
 *
 * @attention 无
 *
 * @param pFirst [IN] 类型#DATE_TIME_S *，第一个系统时间。取值范围为非空。
 * @param pSecond [IN] 类型#DATE_TIME_S *，第二个系统时间。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pFirst或pSecond为空，用户需要检查自己的输入参数。
 * @retval #VOS_ERROR                           0xFFFFFFFF，函数执行失败。
 * @retval #COMP_TIME_LT                        0x00000001，时间pFirst小于时间pSecond。
 * @retval #COMP_TIME_EQ                        0x00000002，时间pFirst等于时间pSecond。
 * @retval #COMP_TIME_GT                        0x00000003，时间pFirst大于时间pSecond。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_DateTime_DeltaSec
 */
extern VOS_UINT32 VOS_DateTime_Cmp(DATE_TIME_S *pFirst, DATE_TIME_S *pSecond);

/**
 * @ingroup  vos_sys
 * @brief 比较两个合法的系统时间，返回比较的结果。
 *
 * @par 描述:
 * 比较两个合法的系统时间，返回日期pFirst比日期pSecond大的秒数。当时间pFirst小于等于时间pSecond时，比较失败，返回0xFFFFFFFF。当时间pFirst大于时间pSecond时，返回成功，pDeltaSec中保存pFirst比pSecond大的秒数。
 *
 * @attention 无
 *
 * @param pFirst [IN] 类型#DATE_TIME_S *，第一个系统时间。取值范围为非空。
 * @param pSecond [IN] 类型#DATE_TIME_S *，第二个系统时间。取值范围为非空。
 * @param pDeltaSec [OUT] 类型#VOS_UINT32 *，比较成功时保存日期pFirst比日期pSecond大的秒数。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，pFirst、pSecond或pDeltaSec为空，用户需要检查自己的输入参数。
 * @retval #VOS_ERROR                           0xFFFFFFFF，日期pFirst小于等于日期pSecond。
 * @retval #VOS_OK                              0x00000000，时间比较成功。
 * @par 依赖:
 * <ul><li>vos_sys.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_DateTime_Cmp
 */
extern VOS_UINT32 VOS_DateTime_DeltaSec(DATE_TIME_S *pFirst, DATE_TIME_S *pSecond, VOS_UINT32 *pDeltaSec);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_SYS_H__

