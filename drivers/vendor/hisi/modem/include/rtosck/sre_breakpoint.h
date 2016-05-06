/**
 * @file sre_breakpoint.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：断点管理模块的对外头文件。 \n
 */

/** @defgroup SRE_breakpoint 断点管理
 *@ingroup SRE_inspect
 */

#ifndef _SRE_BREAK_POINT_H
#define _SRE_BREAK_POINT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**
 * @ingroup SRE_breakpoint
 * 断点句柄类型定义
 */
typedef UINT32  BP_HANDLE_T;

/**
 * @ingroup SRE_breakpoint
 * 断点类型
 */
typedef enum
{
    BP_TYPE_INSTRCTION       = 0,  /**< 指令断点     */
    BP_TYPE_DATA_READ        = 1,  /**< 数据读断点   */
    BP_TYPE_DATA_WRITE       = 2,  /**< 数据写断点   */
    BP_TYPE_DATA_READ_WRITE  = 3,  /**< 数据读写断点，SD6183无效 */
    BP_TYPE_INVALID
}OS_BP_TYPE_E;

/**
 * @ingroup SRE_breakpoint
 * 断点监控区间大小定义
 */
typedef enum
{
    BP_MON_SIZE_001 = 0,   /**<监控区间大小为1字节    */
    BP_MON_SIZE_002 = 1,   /**<监控区间大小为2字节    */
    BP_MON_SIZE_004 = 2,   /**<监控区间大小为4字节    */
    BP_MON_SIZE_008 = 3,   /**<监控区间大小为8字节    */
    BP_MON_SIZE_016 = 4,   /**<监控区间大小为16字节   */
    BP_MON_SIZE_032 = 5,   /**<监控区间大小为32字节，SD6183无效   */
    BP_MON_SIZE_064 = 6,   /**<监控区间大小为64字节，SD6183无效   */
    BP_MON_SIZE_INVALID    /**<监控区间大小非法       */
}OS_BP_MON_SIZE_E;

/**@ingroup SRE_breakpoint
 * 断点管理错误码:添加断点时传入的句柄指针为空。
 *
 * 值: 0x02002201
 *
 * 解决方案:添加断点时，请确保传入的句柄指针合法。
 */
#define OS_ERRNO_BP_ADD_PTR_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_BP,0x01)

/**@ingroup SRE_breakpoint
 * 断点管理错误码:添加断点时传入的断点类型非法。
 *
 * 值: 0x02002202
 *
 * 解决方案:请确保传入的断点类型为BP_TYPE_INSTRCTION，BP_TYPE_DATA_READ，BP_TYPE_DATA_WRITE，BP_TYPE_DATA_READ_WRITE其中一种(SD6183仅支持前三种)。
 */
#define OS_ERRNO_BP_TYPE_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_BP,0x02)

/**@ingroup SRE_breakpoint
 * 断点管理错误码:添加断点时传入的监控区间大小非法。
 *
 * 值: 0x02002203
 *
 * 解决方案:请确保传入的监控区间大小合法:对于数据断点，合法范围见OS_BP_MON_SIZE_E定义，对于指令断点，合法值只能为BP_MON_SIZE_001。
 */
#define OS_ERRNO_BP_MON_SIZE_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_BP,0x03)

/**@ingroup SRE_breakpoint
 * 断点管理错误码:添加断点时传入的监控区间起始地址不满足按监控区间大小对齐的要求。
 *
 * 值: 0x02002204
 *
 * 解决方案:请确保传入的监控区间起始地址按监控区间大小对齐。
 */
#define OS_ERRNO_BP_MON_ADDR_NOT_ALIGN                      SRE_ERRNO_OS_ERROR(OS_MID_BP,0x04)

/**@ingroup SRE_breakpoint
 * 断点管理错误码:断点资源耗尽。
 *
 * 值: 0x02002205
 *
 * 解决方案:请先删除不再使用的断点。
 */
#define OS_ERRNO_BP_RES_NOT_AVALIABLE                       SRE_ERRNO_OS_ERROR(OS_MID_BP,0x05)

/**@ingroup SRE_breakpoint
 * 断点管理错误码:删除断点时传入的断点句柄非法。
 *
 * 值: 0x02002206
 *
 * 解决方案:请确保传入的断点句柄是通过SRE_BreakPointAdd得到的，且该断点未被删除过。
 */
#define OS_ERRNO_BP_REMOVE_INVALID_HANDLE                   SRE_ERRNO_OS_ERROR(OS_MID_BP,0x06)

/**@ingroup SRE_breakpoint
 * 断点管理错误码:删除栈越界检测模块使用的断点资源。
 *
 * 值: 0x02002207
 *
 * 解决方案:请确保传入的断点句柄是通过SRE_BreakPointAdd得到的，而非OS的栈越界模块使用的断点资源。
 */
#define OS_ERRNO_BP_REMOVE_STKMON_HANDLE                    SRE_ERRNO_OS_ERROR(OS_MID_BP,0x07)

/**
*@ingroup SRE_breakpoint
*@brief 添加断点。
*
*@par 描述:
*对uwBpAddr和enSize指定的地址区间，设置enBpType类型的断点，返回断点句柄puwBpHdl。
*
*@attention
* <ul>
* <li>仅支持SD6108/SD6181/SD6182/SD6157/SD6183平台。</li>
* <li>SD6108/SD6181/SD6182/SD6157支持2个指令断点和2个数据断点，数据断点的监控范围为1字节~64字节。</li>
* <li>SD6183支持8个断点(不区分指令/数据断点)，监控数据时监控范围为1字节~16字节。</li>
* <li>当栈越界模块打开时，可使用的数据断点减少1个。</li>
* <li>断点是核内功能，监控的是本核的行为，其他核或外设的行为不会被监控。</li>
* <li>对于指令断点，断点的触发时机是核即将执行被监控指令时，所以用户观察到的断点现场中被监控指令还未被执行。</li>
* <li>对于数据断点，断点的触发时机是核即将读/写被被监控数据时，所以用户观察到的断点现场中被监控数据还未被读/写。</li>
* </ul>
*
*@param enBpType  [IN]  类型OS_BP_TYPE_E，添加的断点类型。
*@param uwBpAddr  [IN]  类型UINT32，断点监控区间的起始地址，必须按enSize对齐。
*@param enSize    [IN]  类型OS_BP_MON_SIZE_E，断点监控区间的大小。
*@param puwBpHdl  [OUT] 类型BP_HANDLE_T*，用于存放断点句柄的地址。
*
*@retval #OS_ERRNO_BP_ADD_PTR_NULL            0x02002201，添加断点时传入的句柄指针为空。
*@retval #OS_ERRNO_BP_TYPE_INVALID            0x02002202，添加断点时传入的断点类型非法。
*@retval #OS_ERRNO_BP_MON_SIZE_INVALID        0x02002203，添加断点时传入的监控区间大小非法。
*@retval #OS_ERRNO_BP_MON_ADDR_NOT_ALIGN      0x02002204，添加断点时传入的监控区间起始地址不满足按监控区间大小对齐的要求。
*@retval #OS_ERRNO_BP_RES_NOT_AVALIABLE       0x02002205，断点资源耗尽。
*@retval #SRE_OK                              0x00000000，添加断点成功。
*@par 依赖:
*<li>sre_breakpoint.h：该接口声明所在的头文件。</li>
*@since RTOSck V100R003C00
*@see SRE_BreakPointRemove
*/
extern UINT32 SRE_BreakPointAdd(OS_BP_TYPE_E enBpType, UINT32 uwBpAddr,  OS_BP_MON_SIZE_E enSize, BP_HANDLE_T* puwBpHdl);

/**
*@ingroup SRE_breakpoint
*@brief 删除断点。
*
*@par 描述:
*删除uwBpHdl指定的断点。
*
*@attention
* <ul>
* <li>仅支持SD6108/SD6181/SD6182/SD6157/SD6183平台。</li>
* </ul>
*
*@param uwBpHdl  [IN]  类型BP_HANDLE_T，断点句柄。
*
*@retval #OS_ERRNO_BP_REMOVE_INVALID_HANDLE   0x02002206，删除断点时传入的断点句柄非法。
*@retval #OS_ERRNO_BP_REMOVE_STKMON_HANDLE    0x02002207，删除栈越界检测模块使用的断点资源。
*@retval #SRE_OK                              0x00000000，删除断点成功。
*@par 依赖:
*<li>sre_breakpoint.h：该接口声明所在的头文件。</li>
*@since RTOSck V100R003C00
*@see SRE_BreakPointAdd
*/
extern UINT32 SRE_BreakPointRemove(BP_HANDLE_T uwBpHdl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _SRE_BREAK_POINT_H */

