#ifndef __TYPE_DEF_H__
#define __TYPE_DEF_H__

#include "vos.h"

#ifndef NULL
#ifdef __cplusplus
#define NULL	0
#else
#define NULL	((void *)0)
#endif
#endif

#undef PUBLIC
#undef static
#define PUBLIC    extern

#define static   static


typedef VOS_UINT8 BYTE_T;
typedef BYTE_T* PBYTE_T;

#undef
#undef
#define
#define




typedef VOS_VOID* (*PVOID_FUNC)(VOS_VOID);



#endif
