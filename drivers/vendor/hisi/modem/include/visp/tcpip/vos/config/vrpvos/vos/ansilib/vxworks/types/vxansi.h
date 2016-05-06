/* vxANSI.h - ANSI header file */

/* Copyright 1992 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,13nov92,dnw  added define for _EXTENSION_POSIX_1003
01c,22sep92,rrr  added support for c++
01b,07sep92,smb  added documentation.
01a,03jul92,smb  written.
*/

/*
DESCRIPTION
This header file includes the minimum configuration necessary for
an ANSI compatible file.

vxCpu.h       contains CPU_FAMILY definition
vxArch.h      contains architecture specific definitions
vxParams.h    contains system parameters specified by ANSI or POSIX standards
vxTypesBase.h contains type definitions for ALL types specified by ANSI or
	      POSIX not already defined in vxArch.h
*/

#ifndef __INCvxANSIh
#define __INCvxANSIh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The following defines enable various extensions to strict ANSI definitions.
 * To achieve strict ANSI compliance without extensions, define these
 * to be 0.
 */

#define _EXTENSION_POSIX_1003		1    /* include POSIX extensions */
#define _EXTENSION_POSIX_REENTRANT	1    /* include POSIX reentrant ext. */
#define _EXTENSION_WRS			1    /* include WRS extensions */


#include "types/vxcpu.h"		/* CPU family definition */
#include "types/vxarch.h"		/* architecture definitions */
#include "types/vxparams.h"		/* system defaults */
#include "types/vxtypesbase.h"	 	/* defaults for machine dependant */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxANSIh */
