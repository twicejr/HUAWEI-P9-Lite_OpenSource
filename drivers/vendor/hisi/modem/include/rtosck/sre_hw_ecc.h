/**
 * @file sre_hw_ecc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：ECC模块外部头文件。 \n
 */

 /**@defgroup SRE_ecc ECC
   *@ingroup SRE_inspect
 */

#ifndef _SRE_HW_ECC_H
#define _SRE_HW_ECC_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170))

/**
 *@ingroup SRE_ecc
 * 寄存器信息结构
 *
 * 描述:异常触发时保存的寄存器信息
 *
 * 注意:以下寄存器名称去掉类型前缀‘uw’，即对应芯片手册中的寄存器名称
 */
typedef struct tagTensilicaEccRegInfo
{
    UINT32 uwMESR;          /**< ECC状态寄存器                          */
    UINT32 uwMECR;          /**< ECC校验寄存器                          */
    UINT32 uwMEVADDR;       /**< ECC地址寄存器                          */
    UINT32 uwMEPC;          /**< ECC异常时PC                            */
    UINT32 uwMEPS;          /**< ECC异常时PS                            */
    UINT32 uwMESAVE;        /**< ECC异常处理数据缓冲寄存器              */
}ECC_REGS_S;

/**
 *@ingroup SRE_ecc
 *@brief ECC使能函数。
 *
 *@par 描述:
 *使能ECC模块功能。
 *@attention
 * <ul>
 * <li>适用于SD6108、SD6181、SD6182、SD6157平台。</li>
 * </ul>
 *
 *@param 无
 *
 *@retval #SRE_OK 0x00000000，成功。
 *
 *@par 依赖:
 * <ul><li>sre_hw_ecc.h：该接口声明所在的头文件。</li></ul>
 *@since UniDSP V100R001C02
 *@see SRE_EccDisable
 */
extern UINT32 SRE_EccEnable(VOID);

/**
 *@ingroup SRE_ecc
 *@brief ECC禁止函数。
 *
 *@par 描述:
 *禁止ECC模块功能。
 *@attention
 * <ul>
 * <li>适用于SD6108、SD6181、SD6182、SD6157平台。</li>
 * </ul>
 *
 *@param 无
 *
 *@retval #SRE_OK 0x00000000，成功。
 *@par 依赖:
 * <ul><li>sre_hw_ecc.h：该接口声明所在的头文件。</li></ul>
 *@since UniDSP V100R001C02
 *@see SRE_EccEnable
 */
 extern UINT32 SRE_EccDisable(VOID);

#elif(OS_HARDWARE_PLATFORM == OS_HIDSP)

/**
 *@ingroup SRE_ecc
 * 寄存器信息结构
 *
 * 描述:为方便定位，OS对于ECC软失效问题记录的有用信息
 *
 * 注意:无
 */
typedef struct tagHidspEccRegInfo
{
    UINT32 uwEccExcCause;    /**< ECC异常原因                            */
    UINT32 uwEccEmAddr;      /**< ECC地址寄存器                          */
    UINT32 uwEccPC;          /**< ECC异常时PC                            */
}ECC_REGS_S;

#endif

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC)  \
  || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170) \
  || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
*@ingroup SRE_ecc
*@brief 用户ECC可纠正错误的处理函数原型定义。
*
*@par 描述: 无。
*@attention
* <ul>
* <li>适用于SD6108、SD6181、SD6182、SD6157、SD6183平台。</li>
* </ul>
*
*@param  pstRegs [IN] 类型#ECC_REGS_S *，指向ECC异常接管后保存的ECC寄存器信息结构体。
*
*@retval 无。
*@par 依赖:
*<li>sre_hw_ecc.h：该接口声明所在的头文件。</li></ul>
*@since UniDSP V200R003C06
*@see 无。
*/
typedef VOID (* OS_ECC_CORRECTED_HOOK)(ECC_REGS_S *pstRegs);

/**
 *@ingroup SRE_ecc
 *@brief 注册用户ECC可纠正错误的处理钩子。
 *
 *@par 描述:
 *注册用户ECC可纠正错误的处理钩子。
 *@attention
 * <ul>
 * <li>支持钩子重复注册。</li>
 * <li>输入参数为NULL可删除已注册钩子。</li>
 * <li>适用于SD6108、SD6181、SD6182、SD6157、SD6183平台。</li>
 * </ul>
 *
 *@param pfnHook [IN] 类型#OS_ECC_CORRECTED_HOOK，用户ECC可纠正错误的处理钩子函数原型。
 *
 *@retval #SRE_OK 0x00000000，成功。
 *
 *@par 依赖:
 *<ul><li>sre_hw_ecc.h：该接口声明所在的头文件。</li></ul>
 *@since UniDSP V200R003C06
 *@see 无
 */
extern UINT32 SRE_EccCorrectedHookAdd(OS_ECC_CORRECTED_HOOK pfnHook);

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* _SRE_HW_ECC_H */

