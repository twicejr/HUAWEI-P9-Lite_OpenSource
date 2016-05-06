/* @(#) pSOSystem x86/V2.2.6: include/stdarg.h.cadul 2.1 96/05/30 13:37:05 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/stdargcu.h                                       */
/*   DATE:    96/05/30                                                 */
/*   PURPOSE: STDARG header file for CAD-UL Compiler.                  */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1996, Integrated Systems, Inc.           */
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
/***********************************************************************/
/*
 **	stdargcu.h
 */
#ifndef	__STDARG_H
#define	__STDARG_H	1

#ifdef __cplusplus
#ifndef __STDC__
#define __STDC__ 1
#endif
extern "C" {
extern int ___ansiarg;
#endif

typedef char *va_list[1];

#ifdef __STDC__

#define va_start(list,lstprm) list[0] = (char *) (&___ansiarg)
#define va_end(list)
#define _arg_size_on_stack_(type) \
   ((sizeof(type)+sizeof(int)-1) & (~(sizeof(int)-1)))
#define va_arg(ap,type) \
   *(((type *)(void*)((ap[0]+=_arg_size_on_stack_(type))-\
   _arg_size_on_stack_(type))))

#else

#define va_dcl int va_alist;
#define va_start(list) list[0] = (char *) (&va_alist)
#define va_end(list)
#define _arg_size_on_stack_(type) \
   ((sizeof(type)+sizeof(int)-1) & (~(sizeof(int)-1)))
#define va_arg(ap,type) \
   *(((type *)(char*)((ap[0]+=_arg_size_on_stack_(type))-\
   _arg_size_on_stack_(type))))

#endif

#ifdef __cplusplus
}
#endif

#endif

