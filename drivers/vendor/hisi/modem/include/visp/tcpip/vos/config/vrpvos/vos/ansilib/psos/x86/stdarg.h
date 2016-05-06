/* @(#) pSOSystem x86/V2.2.6: include/stdarg.h.ppc (386) 1.3 96/07/05 13:03:27 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  include/stdarg.h                                         */
/*   DATE:    96/07/05                                                 */
/*   PURPOSE: This header file is being used to differentiate the      */
/*            CAD-UL compiler and GREEN HILLS Compiler.                */
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
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#ifndef _STDARG_H_386
#define _STDARG_H_386
# ifdef __c_plusplus
   extern "C" {
# endif

#if __ghs__
#include "vos/ansilib/psos/stdarggh.h"
#elif __CADUL__
#include "vos/ansilib/psos/stdargcu.h"
#endif

#ifdef __c_plusplus
    }
#endif
#endif	/* _STDARG_H_XXX */
