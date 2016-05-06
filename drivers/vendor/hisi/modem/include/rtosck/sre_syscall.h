#ifndef _SRE_SYS_CALL_H
#define _SRE_SYS_CALL_H

#include "sre_typedef.h"
#include "sre_module.h"
#include "sre_errno.h"
#include "sre_syscall_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_syscall
 * syscall入参函数名错误。
 *
 * 值: 0x02002f00
 *
 * 解决方案:确保入参正确。
 *
 */
#define OS_ERRNO_SYSCALL_NAME_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_SYSCALL, OS_ERR_FUN_NAME)

/**
 * @ingroup SRE_syscall
 * syscall函数入参个数错误。
 *
 * 值: 0x02002f01
 *
 * 解决方案:确保入参正确。
 *
 */
 
#define OS_ERRNO_SYSCALL_PARA_NUM_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_SYSCALL, OS_ERR_FUN_PARA_NUM)

#define SRE_SYSCALL(pcname,uwParaNum,...)  osSysCallInner(OS_N_##pcname, uwParaNum, __VA_ARGS__)
extern UINT64 osSysCallInner(UINT32 uwsyscallNo, UINT32 uwParaNum,...);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BUILDEF_H */


