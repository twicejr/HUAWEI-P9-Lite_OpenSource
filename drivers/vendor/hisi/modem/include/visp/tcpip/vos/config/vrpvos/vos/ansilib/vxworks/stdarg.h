/* stdarg.h - Ansi C standard arguments header file */

/* Copyright 1992 Wind River Systems, Inc. */

/*
modification history
--------------------
02c,22sep92,rrr  added support for c++
02b,25jul92,smb  rewritten to use arch. specific directories.
02a,04jul92,jcf  cleaned up.
01j,26may92,rrr  the tree shuffle
01i,09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
01h,06nov91,rrr  fixed a #endif warning
01g,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01f,02aug91,ajm  added mips va_arg define
01e,16may91,gae  changed "va-i960.h" include.
01d,26apr91,jdi  added ifndef for DOC.
01c,24mar91,del  added include for I960.
01b,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01a,11aug89,gae  created.
*/

#ifndef __INCstdargh
#define __INCstdargh

#ifdef __cplusplus
extern "C" {
#endif

#include "types/vxansi.h"

#ifdef _ARCH_va_list
_ARCH_va_list;
#undef _ARCH_va_list
#endif

#define va_arg(list, type)		_ARCH_va_arg(list, type)
#define va_end(list)			_ARCH_va_end(list)
#define va_start(list, last_arg)	_ARCH_va_start(list, last_arg)

#ifdef __cplusplus
}
#endif

#endif /* __INCstdargh */
