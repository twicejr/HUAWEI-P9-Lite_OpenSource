/**
 * @file vos_typdef.h
 *
 * Copyright(C), 2012-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：定义OSAL基本数据类型和数据结构。 \n
 */

#ifndef _VOS_TYPDEF_H
#define _VOS_TYPDEF_H

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "sre_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

typedef char                    VOS_CHAR;
typedef char                    VOS_INT8;
typedef unsigned char           VOS_UINT8;
typedef signed short            VOS_INT16;
typedef unsigned short          VOS_UINT16;
typedef signed long             VOS_INT32;
typedef unsigned long           VOS_UINT32;
typedef long long               VOS_INT64;
typedef unsigned long long      VOS_UINT64;
typedef unsigned char           VOS_UCHAR;
typedef signed   short          VOS_WCHAR;
typedef int                     VOS_INT;
typedef unsigned int            VOS_UINT;
typedef float                   VOS_FLOAT;
typedef double                  VOS_DOUBLE;
typedef VOS_UINT32              VOS_BOOL;
typedef VOS_UINT32              VOS_HANDLE_T;

enum VOS_BOOL_DEFINE
{
    VOS_FALSE = 0,              /**< BOOL 型的逻辑假 */
    VOS_TRUE  = 1               /**< BOOL 型的逻辑真 */
};

#define VOS_INTPTR              VOS_INT32
#define VOS_UINTPTR             VOS_UINT32
#define VOS_VOID                void
#define VOS_SIZE_T              VOS_UINT32

typedef VOS_SIZE_T              SIZE_T;

#define VOS_NULL                (0)
#define VOS_NULL_BYTE           (0xFF)
#define VOS_NULL_WORD           (0xFFFF)
#define VOS_NULL_DWORD          (0xFFFFFFFF)
#define VOS_NULL_LONG           (VOS_NULL_DWORD)
#define VOS_NULL_SIZE_T         (~(VOS_SIZE_T)0)
#define VOS_NULL_PTR            (0L)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif /* _VOS_TYPEDEF_H */

