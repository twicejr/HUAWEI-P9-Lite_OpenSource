/* vxCpu.h - VxWorks CPU definitions header */

/* Copyright 1984-2001 Wind River Systems, Inc. */

/*
 * vxCpu.h is now generated -- DO NOT EDIT
 *
 * To change the boilerplate, edit vxCpu.in
 *
 * To add CPU types or otherwise change the substance,
 * edit $WIND_BASE/host/src/target/architecturedb
 */

/*
modification history
--------------------
02i,10aug01,pch  Rename to vxCpu.in, revise for use in generating vxCpu.h
                 from host/src/target/architecturedb
02m,23jul01,scm  change XScale name to conform to coding standards...
02h,07may01,kab  Fix PPC enum clashes
02l,04may01,scm  add STRONGARM support...
02g,25oct00,s_m  renamed PPC405 cpu types
02f,14jun00,alp  Added PPC405 support
02k,11dec00,scm  replace references to ARMSA2 with XScale
02j,31aug00,scm  add sa2 support under arm
02i,20jan99,cdp  marked old ARM CPU numbers 'obsoleted'.
02h,13nov98,cdp  added ARMARCH3, ARMARCH4, ARMARCH4_T.
02n,28mar01,mem  Update SH cpu numbers.
02m,14dec00,pes  Remove more obsolete MIPS CPU designations.
02m,01dec00,???  Update ARM block
02l,06oct00,ish  fix MCF5400
02k,07jul00,dh   rationalised mcf family to 2 cpus.
02j,23nov99,yvp  adding CPU_FAMILY FRV and CPU type FR500 for Fujitsu FR-V
                 (a.k.a Venus) family processors
02i,27mar00,ish  Fixed CPU identifiers in ColdFire support
02h,15mar00,dra  Added ColdFire support.
02g,12oct99,yvp  Merge from .../tor2_0_0.coretools-baseline branch to make
                 Tor2 code work with T3 main/LATEST compiler
02f,09sep99,myz  added CW4000_16 support
02f,22jul99,jld  Regularize CPU=MCOREx tags.
02e,17dec97,ur   added MCORE support.
02f,05nov97,mem  added SPARCV9 support.
02n,18oct99,dra  added CW4000, CW4011, VR4100, VR5000 and VR5400 support.
02m,13jul99,bc   Added SH7718 <-> sh3e
02l,02jul98,st   added SH7750 support (SH4).
02k,05may98,jmc  added SH-DSP and SH3-DSP support.
02j,23apr97,hk   added SH support.
02i,17aug97,tpr  added PowerPC EC 603 support.
02h,15aug97,cym  added SIMNT support.
02g,09apr98,hdn  added support for Pentium, PentiumPro.
02f,26mar97,cdp  added Thumb (ARM7TDMI_T) support.
02e,28nov96,cdp  added ARM support.
02d,12jul96,kkk  added CW4000 & R4650 support.
02c,08feb96,tpr  added PPC505 and PPC860 support.
02b,23feb96,tpr  undefined the PPC macro defined by the PowerPC Gnu.
02a,26may94,yao  added PPC support.
01k,24jul95,ism  added SIMSOLARIS support.
01j,27dec95,myz  added I960HX stuff.
01i,20mar95,kvk  added I960JX specific stuff.
01h,31oct94,kdl  removed comment-within-comment.
01f,27sep93,cd   added R4000 support.
01g,26oct94,tmk  added new cpu type MC68LC040
01f,21jul94,tpr  added MC68060 cpu.
01f,09jun93,hdn  added support for I80X86
01g,02dec93,tpr  added definition for the AMD 29200 microcontroller
	    pad  added definitions for the AMD 29030 cpu
01g,11aug93,gae  vxsim hppa.
01f,22jun93,gae  vxsim: added SIMSPARCSUNOS.
01e,13nov92,dnw  added test for correct definition of CPU
01d,22sep92,rrr  added support for c++
01c,07sep92,smb  added documentation
01b,23jul92,jwt  restored SPARClite reference omitted in file creation.
01a,11jul92,smb  CPU definitions moved from vxWorks.h.
*/

/*
DESCRIPTION
Depending on the value of CPU passed to the system by the compiler command
line, the CPU_FAMILY is defined.  This must be the first header file
included by vxWorks.h.
*/

#ifndef __INCvxCpuh
#define __INCvxCpuh

#ifdef __cplusplus
extern "C" {
#endif

/* CPU types */

/* Turn off stuff that some compilers pre-define ... */
#ifdef MC68000
#undef MC68000
#endif
#ifdef I960
#undef I960
#endif
#ifdef PPC
#undef PPC
#endif

/* Ensure CPU_FAMILY undefined initially */
#ifdef CPU_FAMILY
#undef CPU_FAMILY
#endif

#define MC68000	1	/* CPU */
#define MC68010	2	/* CPU */
#define MC68020	3	/* CPU */
#define MC68030	4	/* CPU */
#define MC68040	5	/* CPU */
#define MC68LC040	6	/* CPU */
#define MC68060	7	/* CPU */
#define CPU32	8	/* CPU */
#define MC680X0	9	/* CPU_FAMILY */
#define SPARC	10	/* CPU & CPU_FAMILY */
#define SPARClite	11	/* CPU */
#define I960	20	/* CPU_FAMILY */
#define I960CA	21	/* CPU */
#define I960KA	22	/* CPU */
#define I960KB	23	/* CPU */
#define I960JX	24	/* CPU */
#define I960HX	25	/* CPU */
#define TRON	30	/* CPU_FAMILY */
#define G100	31	/* CPU */
#define G200	32	/* CPU */
#define MIPS	40	/* CPU_FAMILY */
#define MIPS32	41	/* CPU */
#define MIPS64	42	/* CPU */
#define AM29XXX	50	/* CPU_FAMILY */
#define AM29030	51	/* CPU */
#define AM29200	52	/* CPU */
#define AM29035	53	/* CPU */
#define SIMSPARCSUNOS	60	/* CPU & CPU_FAMILY */
#define SIMSPARCSOLARIS	61	/* CPU & CPU_FAMILY */
#define SIMHPPA	70	/* CPU & CPU_FAMILY */
#define I80X86	80	/* CPU_FAMILY */
#define I80386	81	/* CPU */
#define I80486	82	/* CPU */
#define PENTIUM	83	/* CPU */
#define PENTIUM2	84	/* CPU */
#define PENTIUM3	85	/* CPU */
#define PENTIUM4	86	/* CPU */
#define PPC	90	/* CPU_FAMILY */
#define PPC601	91	/* CPU */
#define PPC602	92	/* CPU */
#define PPC603	93	/* CPU */
#define PPC604	94	/* CPU */
#define PPC403	95	/* CPU */
#define PPC505	96	/* CPU */
#define PPC860	97	/* CPU */
#define PPCEC603	98	/* CPU */
#define PPC555	99	/* CPU */
#define SIMNT	100	/* CPU & CPU_FAMILY */
#define SPARCV9	110	/* CPU_FAMILY */
#define ULTRASPARC	111	/* CPU */
#define ARM	120	/* CPU_FAMILY */
#define ARM710A	121	/* CPU */
#define ARM7TDMI	122	/* CPU */
#define ARM810	123	/* CPU */
#define ARMSA110	124	/* CPU */
#define ARM7TDMI_T	125	/* CPU */
#define ARMARCH3	126	/* CPU */
#define ARMARCH4	127	/* CPU */
#define ARMARCH4_T	128	/* CPU */
#define STRONGARM	129	/* CPU */
#define SH	130	/* CPU_FAMILY */
#define SH7000	131	/* CPU */
#define SH7600	132	/* CPU */
#define SH7040	133	/* CPU */
#define SH7700	134	/* CPU */
#define SH7410	135	/* CPU */
#define SH7729	136	/* CPU */
#define SH7750	137	/* CPU */
#define MCORE	150	/* CPU_FAMILY */
#define MCORE10	151	/* CPU */
#define MCORE15	152	/* CPU */
#define MCORE200	153	/* CPU */
#define MCORE300	154	/* CPU */
#define COLDFIRE	160	/* CPU_FAMILY */
#define MCF5200	161	/* CPU */
#define MCF5400	162	/* CPU */
#define FRV	170	/* CPU_FAMILY */
#define FR500	171	/* CPU */
#define MAP1000	180	/* CPU & CPU_FAMILY */
#define MAP1000A	181	/* CPU */
#define MAPCA	182	/* CPU */
#define XSCALE	1120	/* CPU */
#define ARMARCH5	1121	/* CPU */
#define ARMARCH5_T	1122	/* CPU */
#define PPC509	2000	/* CPU */
#define PPC405	2001	/* CPU */
#define PPC405F	2002	/* CPU */
#define PPC440	2003	/* CPU */
#define PPC85XX	2004	/* CPU */

#if	(CPU==MC68000 || \
	 CPU==MC68010 || \
	 CPU==MC68020 || \
	 CPU==MC68030 || \
	 CPU==MC68040 || \
	 CPU==MC68LC040 || \
	 CPU==MC68060 || \
	 CPU==CPU32)
#define	CPU_FAMILY	MC680X0
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==MC680X0 */

#if	(CPU==SPARC || \
	 CPU==SPARClite)
#define	CPU_FAMILY	SPARC
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==SPARC */

#if	(CPU==I960CA || \
	 CPU==I960KA || \
	 CPU==I960KB || \
	 CPU==I960JX || \
	 CPU==I960HX)
#define	CPU_FAMILY	I960
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==I960 */

#if	(CPU==G100 || \
	 CPU==G200)
#define	CPU_FAMILY	TRON
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==TRON */

#if	(CPU==MIPS32 || \
	 CPU==MIPS64)
#define	CPU_FAMILY	MIPS
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==MIPS */

#if	(CPU==AM29030 || \
	 CPU==AM29200 || \
	 CPU==AM29035)
#define	CPU_FAMILY	AM29XXX
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==AM29XXX */

#if	(CPU==SIMSPARCSUNOS)
#define	CPU_FAMILY	SIMSPARCSUNOS
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==SIMSPARCSUNOS */

#if	(CPU==SIMSPARCSOLARIS)
#define	CPU_FAMILY	SIMSPARCSOLARIS
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==SIMSPARCSOLARIS */

#if	(CPU==SIMHPPA)
#define	CPU_FAMILY	SIMHPPA
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==SIMHPPA */

#if	(CPU==I80386 || \
	 CPU==I80486 || \
	 CPU==PENTIUM || \
	 CPU==PENTIUM2 || \
	 CPU==PENTIUM3 || \
	 CPU==PENTIUM4)
#define	CPU_FAMILY	I80X86
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==I80X86 */

#if	(CPU==PPC601 || \
	 CPU==PPC602 || \
	 CPU==PPC603 || \
	 CPU==PPC604 || \
	 CPU==PPC403 || \
	 CPU==PPC505 || \
	 CPU==PPC860 || \
	 CPU==PPCEC603 || \
	 CPU==PPC555 || \
	 CPU==PPC509 || \
	 CPU==PPC405 || \
	 CPU==PPC405F || \
	 CPU==PPC440 || \
	 CPU==PPC85XX)
#define	CPU_FAMILY	PPC
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==PPC */

#if	(CPU==SIMNT)
#define	CPU_FAMILY	SIMNT
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==SIMNT */

#if	(CPU==ULTRASPARC)
#define	CPU_FAMILY	SPARCV9
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==SPARCV9 */

#if	(CPU==ARM710A || \
	 CPU==ARM7TDMI || \
	 CPU==ARM810 || \
	 CPU==ARMSA110 || \
	 CPU==ARM7TDMI_T || \
	 CPU==ARMARCH3 || \
	 CPU==ARMARCH4 || \
	 CPU==ARMARCH4_T || \
	 CPU==STRONGARM || \
	 CPU==XSCALE || \
	 CPU==ARMARCH5 || \
	 CPU==ARMARCH5_T)
#define	CPU_FAMILY	ARM
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==ARM */

#if	(CPU==SH7000 || \
	 CPU==SH7600 || \
	 CPU==SH7040 || \
	 CPU==SH7700 || \
	 CPU==SH7410 || \
	 CPU==SH7729 || \
	 CPU==SH7750)
#define	CPU_FAMILY	SH
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==SH */

#if	(CPU==MCORE10 || \
	 CPU==MCORE15 || \
	 CPU==MCORE200 || \
	 CPU==MCORE300)
#define	CPU_FAMILY	MCORE
#define CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* CPU_FAMILY==MCORE */

#if	(CPU==MCF5200 || \
	 CPU==MCF5400)
#define	CPU_FAMILY	COLDFIRE
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==COLDFIRE */

#if	(CPU==FR500)
#define	CPU_FAMILY	FRV
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==FRV */

#if	(CPU==MAP1000 || \
	 CPU==MAP1000A || \
	 CPU==MAPCA)
#define	CPU_FAMILY	MAP
#define CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#endif	/* CPU_FAMILY==MAP */

/*
 * Check that CPU and CPU_FAMILY are now defined correctly.
 * If CPU is defined to be one of the above valid values then
 * the CPU_FAMILY will have been properly selected.
 * This is required in order to select the right headers
 * and definitions for that CPU in subsequent headers.
 * If CPU or CPU_FAMILY is not defined at this point,
 * we generate an error and abort the compilation.
 */

#if !defined(CPU) || !defined(CPU_FAMILY)
#error CPU is not defined correctly
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuh */
