/* @(#) pSOSystem PowerPC/V2.5.0: include/stdarg.h.diab 4.2 98/07/30 09:46:09 */
/***********************************************************************/
/*                                                                     */
/*   MODULE: include/stdargdi.h                                        */
/*   DATE:    98/07/30                                                 */
/*   PURPOSE: stdarg.h file for DIAB compiler.                         */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1998, Integrated Systems, Inc.           */
/*                      ALL RIGHTS RESERVED                            */
/*                                                                     */
/*   Permission is hereby granted to licensees of Integrated Systems,  */
/*   Inc. products to use or abstract this computer program for the    */
/*   sole purpose of implementing a product based on Integrated        */
/*   Systems, Inc. products.   No other rights to reproduce, use,      */
/*   or disseminate this computer program, whether in part or in       */
/*   whole, are granted.                                               */
/*                                                                     */
/*   Integrated Systems, Inc. makes no representation or warranties    */
/*   with respect to the performance of this computer program, and     */
/*   specifically disclaims any responsibility for any damages,        */
/*   special or consequential, connected with the use of this program. */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/
#ifndef __Istdarg
#define __Istdarg

#ifdef	__cplusplus
extern "C" {
#endif

#if defined(m88k) || defined(__m88k)
typedef struct {
	int	next_arg;
	int	*mem_ptr;
	int	*reg_ptr;
} va_list;

#pragma pure_function __mem_ptr, __reg_ptr

extern int *__mem_ptr(), *__reg_ptr();

#define __gnuc_va_list va_list

#define va_start(list,parmN) {\
	(list).mem_ptr = __mem_ptr();\
	(list).reg_ptr = __reg_ptr();\
	(list).next_arg = (int *) ((char *)&parmN + sizeof(parmN)) - (list).mem_ptr;\
}
#define va_end(list)
#define va_arg(list, mode) (\
	sizeof(mode,2) <= 3 || sizeof(mode,2) == 44 ? (	/* char-short */\
		(list).next_arg < 8 ? (\
			*(mode*)((char*)(&(list).reg_ptr[++(list).next_arg])-sizeof(mode))\
		) : (\
			*(mode*)((char*)(&(list).mem_ptr[++(list).next_arg])-sizeof(mode))\
		)\
	) : sizeof(mode) == 4 && sizeof(mode,1) == 4 ? (/* 4 byte types */\
		(list).next_arg < 8 ? (\
			*(mode*)&(list).reg_ptr[(list).next_arg++]\
		) : (\
			*(mode*)&(list).mem_ptr[(list).next_arg++]\
		)\
	) : sizeof(mode,2) == 15  ? (			/* double */\
		((list).next_arg & 1) && (list).next_arg++,\
		(list).next_arg < 8 ? (\
			(list).next_arg += 2,\
			*(mode*)&(list).reg_ptr[(list).next_arg-2]\
		) : (\
			(list).next_arg += 2,\
			*(mode*)&(list).mem_ptr[(list).next_arg-2]\
		)\
	) : sizeof(mode,2) == 32 ? (			/* non-aggregates */\
		(list).next_arg < 8 ? (\
			**(mode**)&(list).reg_ptr[(list).next_arg++]\
		) : (\
			**(mode**)&(list).mem_ptr[(list).next_arg++]\
		)\
	) : (						/* structs */\
		(void)(sizeof(mode,1) == 8 && ((list).next_arg & 1) && (list).next_arg++),\
		(list).next_arg += (sizeof(mode)+3)>>2,\
		*(mode*)&(list).mem_ptr[(list).next_arg-((sizeof(mode)+3)>>2)]\
	)\
)

#elif defined(__ppc) && defined(__EABI__)

typedef struct {
	char	__gpr;
	char	__fpr;
	char	filler[2] ; /* necessary if compiled with packed */
	char	*__mem;
	char	*__reg;
} va_list[1];

#pragma pure_function __va_mem, __va_reg, __va_gpr, __va_fpr

extern int __va_gpr(void), __va_fpr(void);
extern char *__va_mem(void), *__va_reg(void);
extern void *__va_arg(va_list, int);

#ifdef __softfp
#define __va_one_gpr(mode)	(sizeof(mode,2) <= 7 || sizeof(mode,2) == 14 || sizeof(mode,2) == 19 || sizeof(mode,2) == 44)
#define __va_two_gpr(mode)	(sizeof(mode,2) <= 9 || sizeof(mode,2) == 15 || sizeof(mode,2) == 16)
#else
#define __va_one_gpr(mode)	(sizeof(mode,2) <= 7 || sizeof(mode,2) == 19 || sizeof(mode,2) == 44)
#define __va_two_gpr(mode)	(sizeof(mode,2) <= 9)
#endif

#define va_start(list,parmN) {\
	(list[0]).__mem = __va_mem();\
	(list[0]).__reg = __va_reg();\
	(list[0]).__gpr = __va_gpr();\
	(list[0]).__fpr = __va_fpr();\
}
#define va_end(list)
#define va_arg(list, mode) (\
	 __va_one_gpr(mode) ? (			/* char-ulint + ptr (float if SWFP) */\
		(*(mode *)((char *)__va_arg(list, 1)+sizeof(int)-sizeof(mode)))\
	) : __va_two_gpr(mode) ? (		/* llint-ullint (double if SWFP) */\
		(*(mode *)__va_arg(list, 2))\
	) : (sizeof(mode,2) == 14) ? (		/* float (602, -Xno-double) */\
		(*(mode *)__va_arg(list, 4))\
	) : (sizeof(mode,2) == 15 || sizeof(mode,2) == 16) ? (		/* double */\
		(*(mode *)__va_arg(list, 3))\
	) : (					/* structs and others passed as pointers */\
		(*(mode *)__va_arg(list, 0))\
	)\
)

#else

typedef char *va_list;

#define va_start(list,parmN) list = (va_list) ((char *)&parmN + sizeof(parmN))
#define va_end(list)
#define va_arg(list, mode) (\
	sizeof(mode,2) == 32 ? (			/* non-aggregates. */\
		*((mode **)(list += ((sizeof(mode *)+sizeof(int)-1) & ~(sizeof(int)-1))))[-1]\
	) : (\
		((mode *)(list += ((sizeof(mode)+sizeof(int)-1) & ~(sizeof(int)-1))))[-1]\
	)\
)
#endif

#if	defined(__Istdio)
extern int vprintf(const char *, va_list);
extern int vfprintf(FILE *, const char *, va_list);
extern int vsprintf(char *, const char *, va_list);
extern int vscanf(const char *, va_list);
extern int vfscanf(FILE *, const char *, va_list);
extern int vsscanf(const char *, const char *, va_list);
#endif

#ifdef	__cplusplus
}
#endif
#endif
