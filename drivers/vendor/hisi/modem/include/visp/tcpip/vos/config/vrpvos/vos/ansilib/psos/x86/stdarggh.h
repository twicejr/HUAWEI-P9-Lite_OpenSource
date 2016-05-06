/* @(#) pSOSystem x86/V2.2.6: include/stdarg.h.ghs 1.2 94/08/04 09:12:10 */
/*
		   ANSI C/C++ Runtime Library

    Copyright 1983,1984,1985,1986,1987,1988,1989,1990,1991,1992,1993,1994
		    Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

#ifndef _STDARG_H
# define _STDARG_H
# ifdef __c_plusplus
   extern "C" {
# endif

# if defined(ghs_c_out) || defined(__ghs_c_out)
    /* THIS MUST COME FIRST BECAUSE THE TRANSLATOR WILL DEFINE THE OTHER */
    /*	SYMBOLS AS APPROPRIATE */
    /* Hack to pass stdarg stuff through to the underlying c compiler */
    #define va_list __va_list
    #define va_start(list,lstprm) __va_start(list,lstprm)
    #define va_end(list) __va_end(list)
    #define va_arg(list,mode) __va_arg(list,mode)
# elif defined(__acp)

    typedef struct {
	 char *va_adr[9];  /* potential addresses of input args*/
	 int	  va_narg;  /* position index in parameter-list */
    } va_list[1];	    /* to do v?printf this must be an array */
				     /* so we can get an implicit pointer */

#    define va_start(ap,va_alist) \
       ( \
	 (ap)[0].va_adr[0] = (char *)&__va_ansiarg, \
	 (ap)[0].va_adr[1] = (char *)&__va_intreg0, \
	 (ap)[0].va_adr[2] = (char *)&__va_dblreg0, \
	 (ap)[0].va_adr[3] = (char *)&__va_intreg1, \
	 (ap)[0].va_adr[4] = (char *)&__va_dblreg1, \
	 (ap)[0].va_adr[5] = (char *)&__va_intreg2, \
	 (ap)[0].va_adr[6] = (char *)&__va_dblreg2, \
	 (ap)[0].va_adr[7] = (char *)&__va_intreg3, \
	 (ap)[0].va_adr[8] = (char *)&__va_dblreg3, \
	 (ap)[0].va_narg = __va_argnum(va_alist)+1 \
    )

#    define va_arg(ap,type) \
       ((ap)[0].va_narg++ < 4 && __va_regtyp(type) ? \
      ((type *)((ap)[0].va_adr[2*(ap)[0].va_narg+__va_align(type)/4-2]))[0]: \
      ( (type *)((ap)[0].va_adr[0]=(char *)(((int)(ap)[0].va_adr[0]+__va_align(type)-1 \
			     & -__va_align(type)) + sizeof(type))))[-1] \
    )

#     define va_end(list)

# elif defined(m88k)||defined(__m88k)
    /* This structure must be the same as the structure in varargs.h */
    typedef struct _va_struct {
	    int next_arg;
	    int *mem_ptr;
	    int *reg_ptr;
    } va_list;

#     define va_start(ap,va_alist) ( \
	   (ap).next_arg= (int *)&__va_ansiarg-__va_stkarg,\
	   (ap).mem_ptr=(int*)(((char*)&__va_ansiarg)-(ap).next_arg*4),\
	   (ap).reg_ptr = (int *)__va_intreg)

#     if defined(__LittleEndian)
char *_gh_va_arg(struct _va_struct *, int, int, int);
#    define va_arg(ap,type) \
       (*(type*)_gh_va_arg(&ap,__va_align(type),__va_regtyp(type),sizeof(type)))
#    else
/* [JY] Mon Feb 28 09:49:33 PST 1994.
   The new version should work for small structs and also for char and short
OLD CODE:
#      define va_arg(ap,type)( \
       (ap).next_arg+=((ap).next_arg&(__va_align(type)==8))+(sizeof(type)+3)/4,\
	   ((type *)((__va_regtyp(type)&&(ap).next_arg<=8? \
		      (ap).reg_ptr:(ap).mem_ptr)+(ap).next_arg))[-1])
NEW CODE: */
#      define va_arg(p,typ)(*(typ*) \
      ((char*)((((p).next_arg+=((p).next_arg&(__va_align(typ)==8))), \
	       (((p).next_arg+=(sizeof(typ)+3)/4)-(sizeof(typ)+3)/4)+ \
	       ((__va_regtyp(typ)&&(p).next_arg<8)?(p).reg_ptr:(p).mem_ptr)))+\
	       (__va_regtyp(typ)?((sizeof(typ)==1)?3:(sizeof(typ)==2)?2:0):0)))
#    endif

#     define va_end(list)
# elif defined(i860) | defined(__i860)
    /*
    Stdarg for the Intel i*860 processor
    */
    typedef struct {
	int va_iarg;
	int va_darg;
	char *va_stkaddr;
	int *va_iregs;
	double *va_dregs;
    } va_list[1];		    /* to do v?printf this must be an array */
				    /* so we can get an implicit pointer */

#     define va_start(ap,va_alist)  ( (ap)[0].va_iarg=__va_iargnum(va_alist), \
				  (ap)[0].va_darg=__va_dargnum(va_alist), \
				    (ap)[0].va_stkaddr= (char*)&__va_ansiarg, \
				    (ap)[0].va_iregs = __va_intreg-1, \
				    (ap)[0].va_dregs = __va_dblreg-1 )

#    define va_arg(ap,type)\
    ( ((__va_regtyp(type)&&sizeof(type)==sizeof(int)&&(ap)[0].va_iarg<12)? \
	(++(ap)[0].va_iarg,*((type*) ((ap)[0].va_iregs+(ap)[0].va_iarg))): \
	(__va_regtyp(type)&&sizeof(type)==sizeof(double)&&(ap)[0].va_darg<4)? \
		    (++(ap)[0].va_darg,*((type*) ((ap)[0].va_dregs+(ap)[0].va_darg))): \
	    (((type *) ((ap)[0].va_stkaddr= \
		((char*) (((int)(ap)[0].va_stkaddr+__va_align(type)-1)&-__va_align(type))) \
		+ sizeof(type)))[-1]) \
    ))
#     define va_end(list)
# elif defined(__clipper) | defined(clipper)

    typedef struct {
	 char *va_adr[5];  /* potential addresses of input args*/
	 int	  va_narg;  /* position index in parameter-list */
    } va_list[1];	    /* to do v?printf this must be an array */
				     /* so we can get an implicit pointer */

#    define va_start(ap,va_alist) \
       ( (ap)[0].va_adr[0] = (char *)&__va_ansiarg, \
	 (ap)[0].va_adr[1] = (char *)&__va_intreg0, \
	 (ap)[0].va_adr[2] = (char *)&__va_dblreg0, \
	 (ap)[0].va_adr[3] = (char *)&__va_intreg1, \
	 (ap)[0].va_adr[4] = (char *)&__va_dblreg1, \
	 (ap)[0].va_narg = __va_argnum(va_alist)+1)

#    define va_arg(ap,type) \
       ((ap)[0].va_narg++ < 2 && __va_regtyp(type) ? \
      ((type *)((ap)[0].va_adr[2*(ap)[0].va_narg+__va_align(type)/4-2]))[0]: \
      ( (type *)((ap)[0].va_adr[0]=(char *)(((int)(ap)[0].va_adr[0]+__va_align(type)-1 \
			     & -__va_align(type)) + sizeof(type))))[-1])
#     define va_end(list)

# elif defined(ns32000) | defined(__ns32000)
    /*
    Stdarg for the National 32000 processor
    */
    typedef struct {
	    char *va_adr[5];
	    int va_narg;
    } va_list[1];		/* to do v?printf this must be an array */
				/* so we can get an implicit pointer */

#    define va_start(ap,va_alist) \
    (	    (ap)[0].va_adr[0] = (char *)&__va_ansiarg, \
	    (ap)[0].va_adr[1] = (char *)&__va_intreg0, \
	    (ap)[0].va_adr[2] = (char *)&__va_dblreg0, \
	    (ap)[0].va_adr[3] = (char *)&__va_intreg1, \
	    (ap)[0].va_adr[4] = (char *)&__va_dblreg1, \
	    (ap)[0].va_narg = __va_argnum(va_alist)+1)

#    define va_arg(p,typ) \
    ((p)[0].va_narg++ < 2 && __va_regtyp(typ) ? \
      ((typ*)((p)[0].va_adr[2*(p)[0].va_narg+(sizeof(typ))/8-1]))[0]: \
      ((typ*)((p)[0].va_adr[0]=(char*)(((int)(p)[0].va_adr[0]+__va_align(typ)-1\
				& -__va_align(typ)) + sizeof(typ))))[-1])
#     define va_end(list)

# elif defined(ppc)  || defined(__ppc)
#  if !defined(__EABI10)
     typedef struct {int *oflo_ptr,*reg_ptr,int_cnt,FP_cnt,mem_cnt;} va_list;
#    define va_start(p,va_alist) \
	((p).oflo_ptr=(int *)(&__va_ansiarg), \
	 (p).reg_ptr=(int *)__va_intreg, \
	 (p).int_cnt= __va_iargnum(va_alist), \
	 (p).FP_cnt=  __va_dargnum(va_alist), \
	 (p).mem_cnt=0)
#    define va_end(list)
#    define va_arg(list,mode) \
	(*(mode *)__gh_va_arg(&list, __va_regtyp(mode), __va_float(mode), sizeof(mode)))
     char *__gh_va_arg(va_list *, int, int, int);
#  else
    /* Like standard case except for va_arg 4 byte stack alignment */
    typedef char *va_list;
#    define va_start(list,lstprm) list = (char *) (&__va_ansiarg)
#    define va_end(list)
#    define va_arg(list,mode) ((mode *)(list =\
	    (char *) ((((int)list + 3) & -4)+ sizeof(mode))))[-1]
#  endif /* __EABI10 */

# elif  defined(i960) || defined(__i960)
    /* Like standard case except for va_arg 16 byte stack alignment */

    typedef char *va_list;
#    define va_start(list,lstprm) list = (char *) (&__va_ansiarg)
#    define va_end(list)
#    define va_arg(list,mode) ((mode *)(list =\
	    (char *) ((((int)list + (__va_align(mode)<=4?3:\
		(__va_align(mode)<=8?7:15))) & (__va_align(mode)<=4?-4:\
		(__va_align(mode)<=8?-8:-16)))+sizeof(mode))))[-1]

# elif  defined(mips) || defined(__mips) || \
	defined(V810) || defined(__V810) || defined(TBD1) || defined(__TBD1)
    /* Like standard case except for va_arg 8 byte stack alignment */
    typedef char *va_list;
#    define va_start(list,lstprm) list = (char *) (&__va_ansiarg)
#    define va_end(list)
#ifndef __Reg_Is_64
#    define va_arg(list,mode) ((mode *)(list =\
	    (char *) ((((int)list + (__va_align(mode)<=4?3:7)) &\
	    (__va_align(mode)<=4?-4:-8))+sizeof(mode))))[-1]
#else /* 64 bit regs means 8 bytes for all args here */
#ifdef __BigEndian
#    define va_arg(list,mode) ((mode *)(list =\
	    (char *) (((int)list + 7 + (int)sizeof(mode)) & -8)))[-1]
#else /* __LittleEndian */
#    define va_arg(list,mode) ((mode *)(list =\
	    (char *) ((((int)list + 7) & -8)+(int)sizeof(mode))))[-1]
#endif /* Endian */
#endif /* __Reg_Is_64 */

# elif defined(alpha) || defined(__alpha)

    typedef struct{char *__va_stkaddr;int __va_pos;}va_list;
    #define va_start(ap,dummy) __va_start(ap)
    #define va_end(ap)
    #define va_arg(ap,mode) (*(((ap).__va_pos+=(sizeof(mode)+7)&~7),(mode *)((ap).__va_stkaddr+(ap).__va_pos-((__va_float(mode)&&(ap).__va_pos<=48)?56:(sizeof(mode)+7)&~7))))

/* DAVEK Sun Nov 21 22:30:56 PST 1993 add SH here */
# elif	defined(m68k) || defined(__m68k) || \
	defined(i386) || defined(__i386)  || \
	defined(gmicro) || defined(__gmicro) || \
	defined(vax) || defined(__vax) || \
	defined(sparc) || defined(__sparc) || \
	defined(am29000) || defined(__am29000) || \
	defined(SH7000) || defined(__SH7000)

    /*
    Trivial stdarg, assuming no register parameters.  4 byte align the stack 
    */
    typedef char *va_list;
#    define va_start(list,lstprm) list = (char *) (&__va_ansiarg)
#    define va_end(list)

#if (defined(sparc) || defined(__sparc)) && defined(__BUILTIN_VA_ARG_INCR)
#    define va_arg(list,mode) ((mode *)__builtin_va_arg_incr((mode *)list))[0]
/* [JY] Tue Apr 19 10:13:14 PDT 1994.  68k defaults to 2-byte alignment */
#elif (defined(m68k) || defined(__m68k)) && (__ghs_alignment < 4)
/* [JY] Mon Apr 25 09:33:10 PDT 1994.  this generates much better code:	*/
/* #    define va_arg(list,mode) ((mode *)(list =\			*/
/* 	    (char *) ((((int)list + 1) & -2)+ sizeof(mode))))[-1]	*/
#    define va_arg(list,mode) \
	(*(mode *)((list += ((sizeof(mode)+1) & -2))-((sizeof(mode)+1) & -2)))
/* end of better code */
#else
/* [JY] Mon Feb 28 15:48:00 PST 1994.  4 byte align stack. VAL:vatest/ansi4.c*/
/* old: #    define va_arg(list,mode) ((mode *)(list += sizeof(mode)))[-1] */
/* new: */
#    define va_arg(list,mode) ((mode *)(list =\
	    (char *) ((((int)list + 3) & -4)+ sizeof(mode))))[-1]
/* [JY] experimental version for bigendian char and short, not enabled
* #  define va_arg(list,typ) (*(typ *)((char*)\
*	    (((list)=(((list)+3) & -4)),((((list)+=sizeof(typ))-sizeof(typ))+\
*	      (__va_regtyp(typ)?((sizeof(typ)==1)?3:(sizeof(typ)==2)?2:0):0)))))
*/
#endif

# else
   #error	  Unknown processor, please add a stdargs entry
# endif

#ifdef __c_plusplus
    }
#endif
#endif	/* _STDARG_H */
