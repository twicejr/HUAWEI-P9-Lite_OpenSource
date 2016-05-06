/**
 * @file sre_symbol_api.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：符号表模块的对外头文件 \n
 */

/**
 * @defgroup SRE_symbol 符号表
 * @ingroup SRE_inspect
*/

#ifndef _SRE_SYMBOL_API_H
#define _SRE_SYMBOL_API_H

#include "sre_typedef.h"
#include "sre_symbol.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_symbol
 * @brief 符号表。
 *
 * @par 描述:
 * 根据输入的符号名pcName，获取对应的符号地址。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能。</li>
 * </ul>
 *
 * @param  pcName   [IN] 类型#CHAR *，输入的符号名。
 * @param  puwAddr  [OUT] 类型#UINT32 *，保存符号地址。
 *
 * @retval #OS_ERRNO_SYMBOL_FIND_NAME_ERROR           0x02002904，在符号表中没有查找到符号名字匹配的符号节点。
 * @retval #OS_ERRNO_SYMBOL_GET_ADDR_PTR_NULL         0x0200290b，输入的指针参数为NULL。
 * @retval #SRE_OK                                    0x00000000，获取符号地址成功。
 * @par 依赖:
 * <ul><li>sre_symbol.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_SymFindAddrByName(CHAR *pcName, UINT32 *puwAddr);

/**
 * @ingroup  SRE_symbol
 * @brief 符号表。
 *
 * @par 描述:
 * 根据输入的符号地址，获取对应的符号名。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能。</li>
 * </ul>
 *
 * @param  pSymAddr  [IN]  类型#VOID *，输入的符号地址。
 * @param  pcName    [OUT] 类型#CHAR **，保存的输出符号名。
 *
 * @retval #OS_ERRNO_SYMBOL_FIND_ADDR_ERROR           0x02002903，在符号表中没有查找到地址匹配的符号节点。
 * @retval #OS_ERRNO_SYMBOL_PARA_POINT_NULL           0x02002900，输入的指针参数为NULL。
 * @retval #SRE_OK                                    0x00000000，获取符号地址成功。
 * @par 依赖:
 * <ul><li>sre_symbol.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_SymFindNameByAddr(VOID *pSymAddr, CHAR **ppcName);


/**
 * @ingroup  SRE_SymbolTableAdd
 * @brief 添加符号表信息给OS。
 *
 * @par 描述:
 * 添加符号表信息给OS。
 *
 * @attention
 * <ul>
 * <li>只支持Cortex-AX平台。</li>
 * <li>只支持配置一个overlay段起始和结束地址，不支配置多个。</li>
 * <li>该接口多次调用以最后一次为准。</li>
 * </ul>
 *
 * @param  pstSymbolNode    [IN]  类型# OS_SYMBOL_NODE_S*，符号表结构体数组的起始地址
 * @param  uwSymbolNum      [IN]  类型# UINT32，符号表结构体个数
 * @param  uwOverlayStart   [IN]  类型# UINT32，overlay段的起始地址
 * @param  uwOverlayEnd     [IN]  类型# UINT32，overlay段的结束地址(起始地址+大小)
 *
 * @retval #OS_ERRNO_SYMBOL_PARA_POINT_NULL     0x02002900，入参指针为空。
 * @retval #OS_ERRNO_SYMBOL_PARA_INVALID        0x0200290c，入参非法
 * @retval #SRE_OK                              0x00000000，获取调用栈信息成功。
 * @par 依赖:
 * <ul><li>sre_callstack.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R005C00
 * @see NONE
 **/
extern UINT32 SRE_SymbolTableAdd(OS_SYMBOL_NODE_S* pstSymbolNode, UINT32 uwSymbolNum, UINT32 uwOverlayStart, UINT32 uwOverlayEnd);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYMBOL_API_H */

/**
 * History:
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/

