/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DaoJKLOkHnsHop7n+e+dpNEZbcEUANAhREkDhyi9k9JiD8innzTXtzoD3G9IhJgTHUk7k
ETG2NI2nqdzZcPC3BMtcGARKklVHocpE39IMocylCJhLsvboEP3ws+F39pdOlQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_k_copy.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：硬件相关模块的对外头文件。 \n
 */

 /**@defgroup SRE_K_copy 内核拷贝
   *@ingroup SRE_kernel
 */

#ifndef _SRE_K_COPY_H
#define _SRE_K_COPY_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_KERNEL_PROCESS == YES)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元号非法，为0值或者超过了最大的配置。
 *
 * 值: 0x02003601
 *
 *解决方案:请检查LP单元号合法性
 */
#define OS_ERRNO_KCOPY_LEN_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_K_COPY, 0x01)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元号非法，为0值或者超过了最大的配置。
 *
 * 值: 0x02003602
 *
 *解决方案:请检查LP单元号合法性
 */
#define OS_ERRNO_KCOPY_PFROM_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_K_COPY, 0x02)

/**
 * @ingroup sre_lp
 * 多核LP错误码定义: LP单元号非法，为0值或者超过了最大的配置。
 *
 * 值: 0x02003603
 *
 *解决方案:请检查LP单元号合法性
 */
#define OS_ERRNO_KCOPY_PTO_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_K_COPY, 0x03)

/*****************************************************************************
 Description : 用户空间-->内核空间
 Input       : 
                pFrom:源地址（用户空间）

 Output      : 
                pTo:目标地址（内核空间）
                
 Return      : 成功返回0，失败返回错误码
 *****************************************************************************/
extern UINT32 SRE_copy_from_usr(void *pTo, const void *pFrom, UINT32 uwLen);



/*****************************************************************************
Description : 内核空间-->用户空间
Input       : 
                pFrom:源地址（内核空间）

Output      : 
                pTo:目标地址（用户空间）
            
Return      : 成功返回0，失败返回错误码
*****************************************************************************/
extern UINT32 SRE_copy_to_usr(void *pTo, const void *pFrom, UINT32 uwLen);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */



