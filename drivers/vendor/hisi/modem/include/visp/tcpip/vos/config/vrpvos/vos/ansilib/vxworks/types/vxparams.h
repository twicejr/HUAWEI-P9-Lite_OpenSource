/* vxParams.h - system parameters header file */

/* Copyright 1984-1992 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,22sep92,rrr  added support for c++
01d,07sep92,smb  added documentation
01c,22jul92,kdl  reduced _PARM_PATH_MAX from 511 to 255.
01b,03jul92,smb  corrected comment after #endif
		 modified values for _PARM_PATH_MAX and _PARM_NAME_MAX
01a,29jul91,rrr  written.
*/

/*
DESCRIPTION
This file defines system parameters specified by the ANSI or POSIX
specifications. The actual value are sometimes suggested by the standards
but can be changed to tune the system.
*/

#ifndef __INCvxParamsh
#define __INCvxParamsh

#ifdef __cplusplus
extern "C" {
#endif

#define _PARM_BUFSIZ		1024
#define _PARM_EXIT_FAILURE	1
#define _PARM_EXIT_SUCCESS	0
#define _PARM_FILENAME_MAX	20
#define _PARM_FOPEN_MAX		20
#define _PARM_L_ctermid		64
#define _PARM_L_cuserid		64
#define _PARM_L_tmpnam		64
#define _PARM_MB_CUR_MAX	1	/* must not be greater than MB_LEN_MAX*/
#define _PARM_NAME_MAX		99
#define _PARM_PATH_MAX		255	/* max path length, not including EOS */
#define _PARM_RAND_MAX		32767 	/* as defined by the ANSI spec. */
#define _PARM_TMP_MAX		64

#define _PARM_UTS_MACHINE_MAX	64
#define _PARM_UTS_NODENAME_MAX	64
#define _PARM_UTS_RELEASE_MAX	64
#define _PARM_UTS_SYSNAME_MAX	64
#define _PARM_UTS_VERSION_MAX	64

#define _PARM_BIG_ENDIAN	1234
#define _PARM_LITTLE_ENDIAN	4321
#define _PARM_STACK_GROWS_UP    1
#define _PARM_STACK_GROWS_DOWN  (-1)


#ifdef __cplusplus
}
#endif

#endif /* __INCvxParamsh */
