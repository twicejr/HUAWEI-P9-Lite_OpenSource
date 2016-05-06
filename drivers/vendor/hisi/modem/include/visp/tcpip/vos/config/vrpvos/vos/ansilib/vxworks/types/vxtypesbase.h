/* vxTypesBase.h - default types (when undefined) header file */

/* Copyright 1984-1992 Wind River Systems, Inc. */

/*
modification history
--------------------
01i,08nov94,dvs  cleaned values for _ARCH_FLT_EPSILON and _ARCH_FLT_MIN
		 that got munged in clear case conversion
01h,18oct93,cd   added __STDC__ definitions for unsigned maximum values.
01g,13nov92,dnw  pruned some non-POSIX stuff
01f,22sep92,rrr  added support for c++
01e,07sep92,smb  added __STDC__ conditional and documentation.
01d,30jul92,jwt  made safe for assembly language files.
01c,30jul92,gae  added timer_t; fixed clock_t, fpos_t.
01b,29jul92,smb  added type define for fpos_t.
01a,03jul92,smb  written
*/

/*
DESCRIPTION
Types not defined by the architecture specific header file will be
defined here so that a complete set of definitions are achieved.
For this reason this file, vxTypesBase.h  must be included after vxArch.h
in which the architecture definitions are located.
*/

#ifndef __INCvxTypesBaseh
#define __INCvxTypesBaseh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* global typedefs */

#ifdef __GNUC_TYPEOF_FEATURE_BROKEN_USE_DEFAULT_UNTIL_FIXED__
#undef _TYPE_size_t
#define _TYPE_size_t		typedef __typeof(sizeof(0)) size_t
#else
#ifndef _TYPE_size_t
#define _TYPE_size_t		typedef unsigned int size_t
#endif
#endif

#ifdef __GNUC_TYPEOF_FEATURE_BROKEN_USE_DEFAULT_UNTIL_FIXED__
#undef _TYPE_ptrdiff_t
#define _TYPE_ptrdiff_t		typedef __typeof((char *)1-(char *)0) ptrdiff_t
#else
#ifndef _TYPE_ptrdiff_t
#define _TYPE_ptrdiff_t		typedef long ptrdiff_t
#endif
#endif

#ifdef __GNUC_TYPEOF_FEATURE_BROKEN_USE_DEFAULT_UNTIL_FIXED__
#undef _TYPE_wchar_t
#define _TYPE_wchar_t		typedef __typeof(L'X') wchar_t
#else
#ifndef _TYPE_wchar_t
#define _TYPE_wchar_t		typedef char wchar_t
#endif
#endif

#ifndef _TYPE_sig_atomic_t
#define _TYPE_sig_atomic_t      typedef unsigned int sig_atomic_t
#endif

#ifndef _TYPE_timer_t
struct __timer;
#define _TYPE_timer_t           typedef struct __timer *timer_t
#endif

#ifndef _TYPE_clock_t
#define _TYPE_clock_t           typedef unsigned int clock_t
#endif

#ifndef _TYPE_time_t
#define _TYPE_time_t            typedef unsigned long time_t
#endif

#ifndef _TYPE_fpos_t
#define _TYPE_fpos_t            typedef long fpos_t
#endif

#ifndef _TYPE_int8_t
#if defined(__STDC__) || defined(__cplusplus)
#define _TYPE_int8_t		typedef signed char int8_t
#else
#define _TYPE_int8_t		typedef char int8_t
#endif
#endif

#ifndef _TYPE_uint8_t
#define _TYPE_uint8_t		typedef unsigned char uint8_t
#endif

#ifndef _TYPE_int16_t
#define _TYPE_int16_t		typedef short int16_t
#endif

#ifndef _TYPE_uint16_t
#define _TYPE_uint16_t		typedef unsigned short uint16_t
#endif

#ifndef _TYPE_int32_t
#define _TYPE_int32_t		typedef long int32_t
#endif

#ifndef _TYPE_uint32_t
#define _TYPE_uint32_t		typedef unsigned long uint32_t
#endif

#ifndef _TYPE_div_t
#define _TYPE_div_t		typedef struct { int quot; int rem; } div_t
#endif

#ifndef _TYPE_ldiv_t
#define _TYPE_ldiv_t		typedef struct { long quot; long rem; } ldiv_t
#endif

#ifndef _TYPE_ssize_t
#define _TYPE_ssize_t		typedef int ssize_t
#endif

/*
 * stuff for setjmp.h
 */
#ifndef _ARCH_jmp_buf_len
#define _ARCH_jmp_buf_len		8
#endif

/*
 * stuff for stdarg.h
 */
#ifndef _ARCH_va_arg
#define _ARCH_va_arg(list, type)	((type *)(list += sizeof(type)))[-1]
#endif

#ifndef _ARCH_va_end
#define _ARCH_va_end(list)
#endif

#ifndef _ARCH_va_start
#define _ARCH_va_start(list, last_arg)	(list = (va_list)(&last_arg + 1))
#endif

#ifndef _ARCH_va_list
#define _ARCH_va_list			typedef char *va_list
#endif

#endif	/* _ASMLANGUAGE */

/*
 * stuff for limits.h
 */
#ifndef _ARCH_MB_LEN_MAX
#define _ARCH_MB_LEN_MAX		1
#endif

#ifndef _ARCH_CHAR_BIT
#define _ARCH_CHAR_BIT			8
#endif

#ifndef _ARCH_CHAR_MAX
#define _ARCH_CHAR_MAX			127
#endif

#ifndef _ARCH_CHAR_MIN
#define _ARCH_CHAR_MIN			(-128)
#endif

#ifndef _ARCH_SHRT_MAX
#define _ARCH_SHRT_MAX			32767
#endif

#ifndef _ARCH_SHRT_MIN
#define _ARCH_SHRT_MIN			(-32768)
#endif

#ifndef _ARCH_INT_MAX
#define _ARCH_INT_MAX			2147483647
#endif

#ifndef _ARCH_INT_MIN
#define _ARCH_INT_MIN			(-2147483648)
#endif

#ifndef _ARCH_LONG_MAX
#define _ARCH_LONG_MAX			2147483647
#endif

#ifndef _ARCH_LONG_MIN
#define _ARCH_LONG_MIN			(-2147483648)
#endif

#ifndef _ARCH_SCHAR_MAX
#define _ARCH_SCHAR_MAX			127
#endif

#ifndef _ARCH_SCHAR_MIN
#define _ARCH_SCHAR_MIN			(-128)
#endif

#ifndef _ARCH_UCHAR_MAX
#define _ARCH_UCHAR_MAX			255
#endif

#ifndef _ARCH_USHRT_MAX
#define _ARCH_USHRT_MAX			65535
#endif

#ifndef _ARCH_UINT_MAX
#ifdef __STDC__
#define _ARCH_UINT_MAX			4294967295u
#else
#define _ARCH_UINT_MAX			4294967295
#endif
#endif

#ifndef _ARCH_ULONG_MAX
#ifdef __STDC__
#define _ARCH_ULONG_MAX			4294967295u
#else
#define _ARCH_ULONG_MAX			4294967295
#endif
#endif

/*
 * stuff for float.h
 */
#ifndef _ARCH_FLT_RADIX
#define _ARCH_FLT_RADIX			2
#endif

#ifndef _ARCH_FLT_MANT_DIG
#define _ARCH_FLT_MANT_DIG		24
#endif

#ifndef _ARCH_FLT_DIG
#define _ARCH_FLT_DIG			7	/* not correct in ANSI spec.s */
#endif

#ifndef _ARCH_FLT_ROUNDS
#define _ARCH_FLT_ROUNDS		1
#endif

#ifndef _ARCH_FLT_EPSILON
#define _ARCH_FLT_EPSILON		1.19209290e-07F
#endif

#ifndef _ARCH_FLT_MIN_EXP
#define _ARCH_FLT_MIN_EXP		(-125)
#endif

#ifndef _ARCH_FLT_MIN
#define _ARCH_FLT_MIN			1.17549435e-38F
#endif

#ifndef _ARCH_FLT_MIN_10_EXP
#define _ARCH_FLT_MIN_10_EXP		(-37)
#endif

#ifndef _ARCH_FLT_MAX_EXP
#define _ARCH_FLT_MAX_EXP		128
#endif

#ifndef _ARCH_FLT_MAX
#define _ARCH_FLT_MAX			3.40282347e+38F
#endif

#ifndef _ARCH_FLT_MAX_10_EXP
#define _ARCH_FLT_MAX_10_EXP		38
#endif

#ifndef _ARCH_DBL_MANT_DIG
#define _ARCH_DBL_MANT_DIG		53
#endif

#ifndef _ARCH_DBL_DIG
#define _ARCH_DBL_DIG			15
#endif

#ifndef _ARCH_DBL_EPSILON
#define _ARCH_DBL_EPSILON		2.2204460492503131e-16
#endif

#ifndef _ARCH_DBL_MIN_EXP
#define _ARCH_DBL_MIN_EXP		(-1021)
#endif

#ifndef _ARCH_DBL_MIN
#define _ARCH_DBL_MIN			2.2250738585072014e-308
#endif

#ifndef _ARCH_DBL_MIN_10_EXP
#define _ARCH_DBL_MIN_10_EXP		(-307)
#endif

#ifndef _ARCH_DBL_MAX_EXP
#define _ARCH_DBL_MAX_EXP		1024
#endif

#ifndef _ARCH_DBL_MAX
#define _ARCH_DBL_MAX			1.7976931348623157e+308
#endif

#ifndef _ARCH_DBL_MAX_10_EXP
#define _ARCH_DBL_MAX_10_EXP		308
#endif

#ifndef _ARCH_LDBL_MANT_DIG
#define _ARCH_LDBL_MANT_DIG		53
#endif

#ifndef _ARCH_LDBL_DIG
#define _ARCH_LDBL_DIG			15
#endif

#ifndef _ARCH_LDBL_EPSILON
#define _ARCH_LDBL_EPSILON		2.2204460492503131e-16L
#endif

#ifndef _ARCH_LDBL_MIN_EXP
#define _ARCH_LDBL_MIN_EXP		(-1021)
#endif

#ifndef _ARCH_LDBL_MIN
#define _ARCH_LDBL_MIN			2.2250738585072014e-308L
#endif

#ifndef _ARCH_LDBL_MIN_10_EXP
#define _ARCH_LDBL_MIN_10_EXP		(-307)
#endif

#ifndef _ARCH_LDBL_MAX_EXP
#define _ARCH_LDBL_MAX_EXP		1024
#endif

#ifndef _ARCH_LDBL_MAX
#define _ARCH_LDBL_MAX			1.7976931348623157e+308L
#endif

#ifndef _ARCH_LDBL_MAX_10_EXP
#define _ARCH_LDBL_MAX_10_EXP		308
#endif

/*
 * stuff for math.h
 */
#ifndef _ARCH_HUGH_VAL
#define _ARCH_HUGH_VAL			_ARCH_DBL_MAX
#endif

/*
 * stuff for the kernel
 */
#ifndef _ARCH_BYTE_ORDER
#define _ARCH_BYTE_ORDER		_PARM_BIG_ENDIAN
#endif

#ifndef _ARCH_STACK_DIR
#define _ARCH_STACK_DIR			_PARM_STACK_GROWS_DOWN
#endif

#ifndef _ARCH_ALIGN_STACK
#define _ARCH_ALIGN_STACK		4
#endif

#ifndef _ARCH_ALIGN_MEMORY
#define _ARCH_ALIGN_MEMORY		4
#endif

#ifndef _ARCH_ALIGN_REGS
#define _ARCH_ALIGN_REGS		4
#endif

#ifndef _ARCH_MOVE_SIZE
#define _ARCH_MOVE_SIZE			4
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxTypesBaseh */
