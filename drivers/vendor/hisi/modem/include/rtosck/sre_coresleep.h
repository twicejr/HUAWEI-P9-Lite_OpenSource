/**
 * @file sre_coresleep.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：低功耗模块的对外头文件。 \n
 */

 /**@defgroup SRE_coresleep 低功耗管理
   *@ingroup SRE_inspect
 */

#ifndef _SRE_CORESLEEP_H
#define _SRE_CORESLEEP_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_coresleep
 * 低功耗错误码：设置核的低功耗模式非法。
 *
 * 值: 0x02003a01
 *
 * 解决方案: 核的低功耗方式只能为LOW_POWER_MODE_OFF和LOW_POWER_MODE_CORE_SLEEP。
 */
#define OS_ERRNO_POWER_MODE_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_CORESLEEP,0x01)

/**@ingroup SRE_coresleep
 * 低功耗结构体定义
 */
typedef enum
{
    LOW_POWER_MODE_OFF,                 /**< 关闭低功耗状态     */
    LOW_POWER_MODE_CORE_SLEEP,          /**< 低功耗状态         */
    LOW_POWER_MODE_BUTT                 /**< 非法状态           */
}OS_POWER_MODE_E;

/**
 * @ingroup  SRE_coresleep
 * @brief 低功耗方式设置。
 *
 * @par 描述:
 * 根据enPowerMode设置核低功耗运行方式。
 *
 * @attention
 * <ul>
 * <li>支持Tensilica及SD6183平台。</li>
 * </ul>
 *
 * @param  enPowerMode   [IN] 类型#OS_POWER_MODE_E，设置核低功耗方式，详见OS_POWER_MODE_E。
 *
 * @retval #OS_ERRNO_POWER_MODE_INVALID               0x02003a01，设置低功耗方式错误，只能设置为LOW_POWER_MODE_OFF和LOW_POWER_MODE_CORE_SLEEP。
 * @retval #SRE_OK                                    0x00000000，设置低功耗方式成功。
 * @par 依赖:
 * <ul><li>sre_coresleep.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R002C00
 * @see
 **/
extern UINT32 SRE_PowerModeSet(OS_POWER_MODE_E enPowerMode);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CORESLEEP_H */



