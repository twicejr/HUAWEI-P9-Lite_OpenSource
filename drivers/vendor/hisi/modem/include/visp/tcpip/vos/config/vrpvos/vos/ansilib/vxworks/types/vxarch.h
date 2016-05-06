/* vxArch.h - architecture header */

/* Copyright 1984-1996 Wind River Systems, Inc. */

/*
modification history
--------------------
02a,26may94,yao  added PPC support.
01n,30oct95,ism  added SIMSOLARIS support.
01m,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
01l,02dec93,pme  added Am29K family support.
01k,11aug93,gae  vxsim hppa.
01j,12jun93,rrr  vxsim.
01i,09jun93,hdn  added support for I80X86
01h,22sep92,rrr  added support for c++
01g,07sep92,smb  added documentation
01f,07jul92,rrr  added defines for BIG & LITTLE ENDIAN and STACK direction
01e,07jul92,ajm  added _ARCH_MULTIPLE_CACHELIB for cache init
01d,03jul92,smb  changed name from arch.h.
01c,06jun92,ajm  corrected definition of mips CPU_FAMILY
01b,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01a,22apr92,yao	 written.
*/

/*
DESCRIPTION
This header file includes a architecture specific header file depending
on the value of CPU_FAMILY defined in vxCpu.h. The header file contains
definitions specific to this CPU family. This header file must be
preceded by an include of vxCpu.h
*/

#ifndef __INCvxArchh
#define __INCvxArchh

#ifdef __cplusplus
extern "C" {
#endif

#define _BIG_ENDIAN		1234
#define _LITTLE_ENDIAN		4321
#define _STACK_GROWS_DOWN	(-1)
#define _STACK_GROWS_UP		1

#if (CPU_FAMILY==MC680X0)
#include "arch/mc68k/archMc68k.h"
#endif /* (CPU_FAMILY== MC680X0) */

#if (CPU_FAMILY==SPARC)
#include "arch/sparc/archSparc.h"
#endif /* (CPU_FAMILY== SPARC) */

#if (CPU_FAMILY==SIMSPARCSUNOS)
#include "arch/simsparc/archSimsparc.h"
#endif /* (CPU_FAMILY== SIMSPARCSUNOS) */

#if (CPU_FAMILY==SIMSPARCSOLARIS)
#include "arch/simsolaris/archSimsolaris.h"
#endif /* (CPU_FAMILY== SIMSPARCSOLARIS) */

#if (CPU_FAMILY==SIMHPPA)
#include "arch/simhppa/archSimhppa.h"
#endif /* (CPU_FAMILY== SIMHPPA) */

#if (CPU_FAMILY==I960)
#include "arch/i960/archI960.h"
#endif /* (CPU_FAMILY== I960) */

#if (CPU_FAMILY==MIPS)
#include "arch/mips/archMips.h"
#endif /* (CPU_FAMILY==MIPS) */

#if (CPU_FAMILY==PPC)
#include "arch/ppc/archPpc.h"
#endif /* (CPU_FAMILY==PPC) */

#if (CPU_FAMILY==I80X86)
#include "arch/i86/archI86.h"
#endif /* (CPU_FAMILY==I80X86) */

#if (CPU_FAMILY==AM29XXX)
#include "arch/am29k/archAm29k.h"
#endif /* (CPU_FAMILY==AM29XXX) */

#ifndef _BYTE_ORDER
#define	_BYTE_ORDER		_BIG_ENDIAN
#endif /* _BYTE_ORDER */

#ifndef	_STACK_DIR
#define	_STACK_DIR		_STACK_GROWS_DOWN
#endif	/* _STACK_DIR */

#ifndef	_ALLOC_ALIGN_SIZE
#define	_ALLOC_ALIGN_SIZE	4	/* 4 byte boundary */
#endif	/* _ALLOC_ALIGN_SIZE */

/* Note: for architectures not reguiring stack alignment, enforcing 4 byte
 * alignment is recommended for better efficiency.
 */

#ifndef	_STACK_ALIGN_SIZE
#define	_STACK_ALIGN_SIZE	4	/* 4 byte boundary */
#endif	/* _STACK_ALIGN_SIZE */

#ifndef _ARCH_MULTIPLE_CACHELIB
#define _ARCH_MULTIPLE_CACHELIB	FALSE
#endif	/* _ARCH_MULTIPLE_CACHELIB */

#ifndef _CACHE_ALIGN_SIZE
#define _CACHE_ALIGN_SIZE	16
#endif	/* _CACHE_ALIGN_SIZE */

/* alignment requirement when accessing bus */

#ifndef	_DYNAMIC_BUS_SIZING
#define _DYNAMIC_BUS_SIZING	TRUE	/* dynamic bus sizing */
#endif	/* _DYNAMIC_BUS_SIZING */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxArchh */
