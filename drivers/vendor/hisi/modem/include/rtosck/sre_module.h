/**
* @file sre_module.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：模块ID编号。 \n
*/

#ifndef _SRE_MODULE_H
#define _SRE_MODULE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/* 预留处可加新增模块的模块号，注意请同步刷新CDA 工具端文件sre_kernelinfo.inc中osModuleID结构体,以及init_trace中的acModuleName数组*/

enum OS_MOUDLE_ID
{
    OS_MID_SYS                  = 0x0,     /*系统模块*/
    OS_MID_MEM                  = 0x1,     /*内存模块*/
    OS_MID_FSCMEM               = 0x2,
    OS_MID_DYNFSCMEM            = 0x3,
    OS_MID_MCPOOLMEM            = 0x4,
    OS_MID_POOLMEM              = 0x5,
    OS_MID_SYNC                 = 0x6,
    OS_MID_MCSWI                = 0x7,
    OS_MID_TSK                  = 0x8,
    OS_MID_SWI                  = 0x9,
    OS_MID_SWTMR                = 0xa,
    OS_MID_TICK                 = 0xb,
    OS_MID_CPUP                 = 0xc,
    OS_MID_MSG                  = 0xd,
    OS_MID_STAFSCMEM            = 0xe,
    OS_MID_SEM                  = 0xf,
    OS_MID_FSEM                 = 0x10,
    OS_MID_CACHE                = 0x11,
    OS_MID_MMU                  = 0x12,
    OS_MID_MCSEM                = 0x13,
    OS_MID_HWI                  = 0x14,
    OS_MID_MSGMEM               = 0x15,
    OS_MID_HOOK                 = 0x16,
    OS_MID_HWTMR                = 0x17,
    OS_MID_BSS                  = 0x18,
    OS_MID_INSTSHMEM            = 0x19,
    OS_MID_SIG                  = 0x1a,
    OS_MID_NSM                  = 0x1b,
    OS_MID_EXC                  = 0x1c,
    OS_MID_MCHWTMR              = 0x1d,
    OS_MID_LP                   = 0x1e,
    OS_MID_HUNT                 = 0x1f,
    OS_MID_HW                   = 0x20,
    OS_MID_MPU                  = 0x21,
    OS_MID_BP                   = 0x22,
    OS_MID_MCCOM                = 0x23,
    OS_MID_HWSEM                = 0x24,
    OS_MID_TRACE                = 0x25,
    OS_MID_EVENT                = 0x26,
    OS_MID_QUEUE                = 0x27,
    OS_MID_OSAL                 = 0x28,
    OS_MID_SYMBOL               = 0x29,
    OS_MID_STKMON               = 0x2a,
    OS_MID_MSGM                 = 0x2b,
    OS_MID_LP_SYNC              = 0x2c,
    OS_MID_SHELL                = 0x2d,
    OS_MID_TIMER                = 0x2e,
    OS_MID_SREMNG               = 0x2f,
    OS_MID_PROCESS              = 0x30,
    OS_MID_TSKMON               = 0x31,
    OS_MID_SHELLSVR             = 0x32,
    OS_MID_SHELLAGT             = 0x33,
    OS_MID_IO_INTF              = 0x34,
    OS_MID_CALLSTACK            = 0x35,
    OS_MID_K_COPY               = 0x36,
    OS_MID_LIBC                 = 0x37,
    OS_MID_SHELLCMDPROC         = 0x38,
    OS_MID_CPUPWARN             = 0x39,
    OS_MID_CORESLEEP            = 0x3a,
    OS_MID_MCFSEM               = 0x3b,
    OS_MID_MCMSG                = 0x3c,
    OS_MID_HARDDRV              = 0x3d,
    OS_MID_DEVICE               = 0x3e,
    OS_MID_APP                  = 0x3f,
    OS_MID_LOWPOWER             = 0x40,
    OS_MID_BUTT
};

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_MODULE_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

