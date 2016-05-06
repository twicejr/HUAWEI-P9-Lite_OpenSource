#ifndef _BASETYPE_H_
#define _BASETYPE_H_

//#include "v_typdef.h"
//#include "v_modNum.h"

#ifdef  __cplusplus
extern "C" {
#endif


#ifndef VOID
#define VOID void
#endif

#ifndef CHAR
#define CHAR char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef SHORT
#define SHORT short
#endif

#ifndef USHORT
#define USHORT  unsigned short
#endif

/* Modified start by jiangyongliang 50758 at 2012-02-16 PGPV2R6 for 工程适配 */
#ifdef __X86_PLATFORM__ 
#ifndef LONG
#define LONG int
#endif

#ifndef ULONG
#define ULONG unsigned int
#endif

#ifndef ULONG64
#define ULONG64 unsigned long
#endif

#else
#ifndef LONG
#define LONG long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef ULONG64
#ifdef __WIN32_PLATFORM__
#define ULONG64 unsigned __int64
#else
#define ULONG64 unsigned long long
#endif
#endif
#endif
/* Modified end by jiangyongliang 50758 at 2012-02-16 PGPV2R6 for 工程适配 */

/* Added start by majun 52643 at 2013-06-19 PGP V2R6C01 for Source 整理*/
#ifndef VOS_USHORT
#define VOS_USHORT  unsigned short
#endif

#ifdef __X86_PLATFORM__
#ifndef VOS_UINT64
#define VOS_UINT64 unsigned long
#endif

#else

#ifndef VOS_UINT64
#ifdef __WIN32_PLATFORM__
#define VOS_UINT64 unsigned __int64
#else
#define VOS_UINT64 unsigned long long
#endif
#endif

#endif

/* 表字段定义数据结构 */
#ifndef VOS_PACKED
#ifdef __WIN32_PLATFORM__
#define VOS_PACKED
#else
#define VOS_PACKED  __attribute__ ((__packed__))
#endif
#endif
/* Added end by majun 52643 at 2013-06-19 PGP V2R6C01 for Source 整理*/

typedef struct tagUULONG 
{
        ULONG hi;
        ULONG lo;
} UULONG;

/* xhz-8031 changed for 8031 2005-04-19: for compatibility with MIPS system */ 
#define VOS_IntegerShiftLeft( A, B ) \
    ( ( (ULONG) (A) ) << (B) )

#define VOS_NewCopyVar( A, B) \
{\
    (VOID)VOS_Mem_Copy( (VOID*)&(A), (VOID*)&(B), sizeof(A) ); \
}

#if	(CPU_FAMILY == MIPS)
#define VOS_CopyConst( A, B ) \
{ \
        if( 4 == sizeof( A ) ) \
        { \
                unsigned long _vos_long_x_b_; \
                 \
                _vos_long_x_b_ = (unsigned long) (B); \
                 \
                (VOID)VOS_Mem_Copy( (VOID*)&(A), (VOID*)&_vos_long_x_b_, 4); \
        } \
        else if( 2 == sizeof( A ) ) \
        { \
                unsigned short _vos_short_x_; \
                 \
                _vos_short_x_ = (unsigned short) (B); \
                 \
                (VOID)VOS_Mem_Copy( (VOID*)&(A), (VOID*)&_vos_short_x_, 2); \
        } \
        else \
        { \
            VOS_DBGASSERT(0); \
        } \
}
#define VOS_CopyVar( A, B ) \
{ \
    (VOID)VOS_Mem_Copy( (VOID*)&(A), (VOID*)&(B), sizeof(A) ); \
}
#define VOS_CopyVarByPointer(pA, pB) \
{ \
    (VOID)VOS_Mem_Copy( (VOID*)(pA), (VOID*)(pB), sizeof(*(pA)) ); \
}
#define VOS_CopyConstByPointer(pA, B) \
{ \
    if( sizeof( B ) == 4 ) \
    { \
        unsigned long _vos_long_x_; \
         \
        _vos_long_x_ = (ULONG)(B); \
        (VOID)VOS_Mem_Copy( (VOID*)(pA), (VOID*)(&_vos_long_x_), 4); \
    } \
    else if( sizeof( B ) == 2 ) \
    { \
        unsigned short _vos_short_x_; \
         \
        _vos_short_x_ = (USHORT)(B); \
        (VOID)VOS_Mem_Copy( (VOID*)(pA), (VOID*)(&_vos_short_x_), 2); \
    } \
    else \
    { \
            VOS_DBGASSERT(0); \
    } \
}
#define VOS_AddVar( SUM, A, B ) \
{ \
        if( 4 == sizeof( A ) ) \
        { \
                unsigned long _vos_long_x_a_; \
                unsigned long _vos_long_x_b_; \
                 \
                VOS_CopyVar( _vos_long_x_a_, (A) ); \
                VOS_CopyVar( _vos_long_x_b_, (B) ); \
                _vos_long_x_a_ += _vos_long_x_b_; \
                VOS_CopyVar( (SUM), _vos_long_x_a_ ); \
        } \
        else if( 2 == sizeof( A ) ) \
        { \
                unsigned short _vos_short_x_a_; \
                unsigned short _vos_short_x_b_; \
                 \
                VOS_CopyVar( _vos_short_x_a_, (A) ); \
                VOS_CopyVar( _vos_short_x_b_, (B) ); \
                _vos_short_x_a_ += _vos_short_x_b_; \
                VOS_CopyVar( (SUM), _vos_short_x_a_ ); \
        } \
        else \
        { \
            VOS_DBGASSERT(0); \
        } \
} 
#define VOS_AddConst( SUM, A, B ) \
{ \
        if( 4 == sizeof( A ) ) \
        { \
                unsigned long _vos_long_x_a_; \
                unsigned long _vos_long_x_b_; \
                 \
                VOS_CopyVar( _vos_long_x_a_, (A) ); \
                _vos_long_x_b_ = (unsigned long)(B); \
                _vos_long_x_a_ += _vos_long_x_b_; \
                VOS_CopyVar( (SUM), _vos_long_x_a_ ); \
        } \
        else if( 2 == sizeof( A ) ) \
        { \
                unsigned short _vos_short_x_a_; \
                unsigned short _vos_short_x_b_; \
                 \
                VOS_CopyVar( _vos_short_x_a_, (A) ); \
                _vos_short_x_b_ = (unsigned short)(B); \
                _vos_short_x_a_ += _vos_short_x_b_; \
                VOS_CopyVar( (SUM), _vos_short_x_a_ ); \
        } \
        else \
        { \
            VOS_DBGASSERT(0); \
        } \
} 
#if ( VRP_BIG_ENDIAN ==  VRP_YES )
#define VOS_EqConst( A, B )     ( *( (char*)&(A) + 0 ) == (char)((B)>>24) && \
                                  *( (char*)&(A) + 1 ) == (char)((B)>>16) && \
                                  *( (char*)&(A) + 2 ) == (char)((B)>>8) && \
                                  *( (char*)&(A) + 3 ) == (char)((B)>>0) )
#else
#define VOS_EqConst( A, B )     ( *( (char*)&(A) + 3 ) == (char)((B)>>24) && \
                                  *( (char*)&(A) + 2 ) == (char)((B)>>16) && \
                                  *( (char*)&(A) + 1 ) == (char)((B)>>8) && \
                                  *( (char*)&(A) + 0 ) == (char)((B)>>0) )
#endif

#if ( VRP_BIG_ENDIAN ==  VRP_YES )
#define VOS_GetIntegerValue( A ) \
( \
    ( sizeof( A ) == 4 ) ? \
    ( VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) ), 24 ) | VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) + 1 ), 16 ) | \
        VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) + 2 ), 8 ) | *( (UCHAR*)(&(A)) + 3 ) ) : \
    ( VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) ), 8 ) | *( (UCHAR*)(&(A)) + 1 ) ) \
)
#else
#define VOS_GetIntegerValue( A ) \
( \
    ( sizeof( A ) == 4 ) ? \
    ( VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) + 3), 24 ) | VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) + 2 ), 16 ) | \
        VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) + 1 ), 8 ) | *( (UCHAR*)(&(A)) ) ) : \
    ( VOS_IntegerShiftLeft( *( (UCHAR*)(&(A)) + 1), 8 ) | *( (UCHAR*)(&(A)) ) ) \
)
#endif

#if ( VRP_BIG_ENDIAN ==  VRP_YES )
#define VOS_GetIntegerValueByPointer( pA, type ) \
( \
    ( sizeof( type ) == 4 ) ? \
    ( (type)( VOS_IntegerShiftLeft( *( (UCHAR*)(pA) ), 24 ) | VOS_IntegerShiftLeft( *( (UCHAR*)(pA) + 1 ), 16 ) | \
        VOS_IntegerShiftLeft( *( (UCHAR*)(pA) + 2 ), 8 ) | *( (UCHAR*)(pA) + 3 ) ) ) : \
    ( (type)( VOS_IntegerShiftLeft( *( (UCHAR*)(pA) ), 8 ) | *( (UCHAR*)(pA) + 1 ) ) )\
)
#else
#define VOS_GetIntegerValueByPointer( pA, type ) \
( \
    ( sizeof( type ) == 4 ) ? \
    ( (type)( VOS_IntegerShiftLeft( *( (UCHAR*)(pA) + 3), 24 ) | VOS_IntegerShiftLeft( *( (UCHAR*)(pA) + 2 ), 16 ) | \
        VOS_IntegerShiftLeft( *( (UCHAR*)(pA) + 1 ), 8 ) | *( (UCHAR*)(pA) ) ) ) : \
    ( (type)( VOS_IntegerShiftLeft( *( (UCHAR*)(pA) + 1), 8 ) | *( (UCHAR*)(pA) ) ) )\
)
#endif


#else /* (CPU_FAMILY == MIPS) */
#define VOS_CopyVarByPointer(pA, pB) { *(pA) = *(pB); }
#define VOS_CopyConstByPointer(pA, B) { *(pA) = (B); }
#define VOS_CopyConst( A, B ) { (A) = (B); }
#define VOS_CopyVar( A, B )  { (A) = (B); };
#define VOS_AddVar( SUM, A, B ) { (SUM) = (A) + (B); }
#define VOS_AddConst( SUM, A, B ) { (SUM) = (A) + (B); }
#define VOS_EqConst( A, B ) ( (A) == (B) )
#define VOS_GetIntegerValue( A ) (A)
#define VOS_GetIntegerValueByPointer( pA, type ) (*((type*)(pA)))
#endif /* (CPU_FAMILY == MIPS) */


/* 8070增加的双整型 */
typedef union tagDULONG
{
	struct tagULONG_UL
	{
		ULONG ulHi_l;
		ULONG ulLo_l;
	}x;
	struct tagULONG_US
	{
/* Deleted start by lihong 00181132 at 2012-09-07 V2R6C00 for 高端内存 */
#if 0
/*#if (VRP_BIG_ENDIAN==VRP_YES)
            USHORT usHiHi_s;
            USHORT usHiLo_s;
            USHORT usLoHi_s;
            USHORT usLoLo_s;
#else*/
#endif
/* Deleted end by lihong 00181132 at 2012-09-07 V2R6C00 for 高端内存 */
            USHORT usHiLo_s;
            USHORT usHiHi_s;
            USHORT usLoLo_s;
            USHORT usLoHi_s;
/* Deleted start by lihong 00181132 at 2012-09-07 V2R6C00 for 高端内存 */
#if 0
/*#endif*/
#endif
/* Deleted end by lihong 00181132 at 2012-09-07 V2R6C00 for 高端内存 */
	}y;
}DULONG;

#define ulHi	x.ulHi_l
#define ulLo	x.ulLo_l
#define usHiHi  y.usHiHi_s
#define usHiLo  y.usHiLo_s
#define usLoHi  y.usLoHi_s
#define usLoLo  y.usLoLo_s
typedef VOID   (*VOS_VOIDVRPFUNCPTR)(); /* ptr to function returning VOS_VOID */
typedef ULONG  (*VOS_ULONGVRPFUNCPTR)();/* ptr to function returning VOS_UING32 */
/* 	dulFirst<dulSecond:		return -1;
	dulFirst>dulSecond: 	return 1;
	dulFirst==dulSecond:	return 0;
*/
#define DULONG_COMPARE(dulFirst,dulSecond) \
	(((dulFirst).ulHi<(dulSecond).ulHi)?-1: \
		(((dulFirst).ulHi>(dulSecond).ulHi)?1: \
			(((dulFirst).ulLo<(dulSecond).ulLo)?-1: \
				(((dulFirst).ulLo>(dulSecond).ulLo)?1:0))))
				
#define DULONG_ADD(dulSum,dulFirst,dulSecond)	\
{ \
	DULONG dulSum_temp; \
	\
	(dulSum_temp).ulLo = (dulFirst).ulLo+(dulSecond).ulLo; \
	(dulSum_temp).ulHi = (dulFirst).ulHi+(dulSecond).ulHi+(ULONG)((dulSum_temp).ulLo<(dulFirst).ulLo); \
       /* dengyiou changed for 8031 2005-04-19: for compatibility with MIPS system */ \
	/* (dulSum)           =  dulSum_temp; */ \
	VOS_CopyVar((dulSum), dulSum_temp); \
}

#define DULONG_SUB(dulResult,dulFirst,dulSecond) \
{ \
	DULONG dulResult_temp; \
	\
	(dulResult_temp).ulLo = (dulFirst).ulLo-(dulSecond).ulLo; \
	(dulResult_temp).ulHi = (dulFirst).ulHi-(dulSecond).ulHi-(ULONG)((dulResult_temp).ulLo>(dulFirst).ulLo); \
       /* dengyiou changed for 8031 2005-04-19: for compatibility with MIPS system */ \
	/* (dulResult)           =  dulResult_temp; */ \
	VOS_CopyVar((dulResult), dulResult_temp); \
}

/* second must < 65536(0-65535) */
#define DULONG_MUL(dulResult,dulFirst,ulSecond) \
{ \
	DULONG dulResult_temp; \
	\
	dulResult_temp.ulLo=(dulFirst).usLoLo*(ulSecond); \
	dulResult_temp.ulHi=(dulFirst).usLoHi*(ulSecond)+dulResult_temp.usLoHi; \
	dulResult_temp.usLoHi=dulResult_temp.usHiLo; \
	dulResult_temp.ulHi=(dulFirst).ulHi*(ulSecond)+dulResult_temp.usHiHi; \
       /* dengyiou changed for 8031 2005-04-19: for compatibility with MIPS system */ \
	/* (dulResult)           =  dulResult_temp; */ \
	VOS_CopyVar((dulResult), dulResult_temp); \
}

/* second must <65536(0-65535) */
#define DULONG_DIV(dulResult,dulFirst,ulSecond,ulMod) \
{ \
	DULONG dulResult_temp,dulResult_temp2; \
	\
	dulResult_temp.ulHi=dulFirst.ulHi/(ulSecond); \
	dulResult_temp2.usHiHi=(USHORT)(dulFirst.ulHi%(ulSecond)); \
	dulResult_temp2.usHiLo=dulFirst.usLoHi; \
	dulResult_temp.usLoHi=(USHORT)(dulResult_temp2.ulHi/(ulSecond)); \
	dulResult_temp2.usLoHi=(USHORT)(dulResult_temp2.ulHi%(ulSecond)); \
	dulResult_temp2.usLoLo=dulFirst.usLoLo; \
	dulResult_temp.usLoLo=(USHORT)(dulResult_temp2.ulLo/(ulSecond)); \
	(ulMod)=dulResult_temp2.ulLo%(ulSecond); \
       /* dengyiou changed for 8031 2005-04-19: for compatibility with MIPS system */ \
	/* (dulResult)           =  dulResult_temp; */ \
	VOS_CopyVar((dulResult), dulResult_temp); \
}
#define DULONG_SELFADD(dulResult)\
{\
    (dulResult).ulLo++;\
    if((dulResult).ulLo == 0)\
        (dulResult).ulHi++; \
}

#define DULONG_SELFSUB(dulResult)\
{\
    (dulResult).ulLo--;\
    if((dulResult).ulLo == 0xffffffff)\
        (dulResult).ulHi --; \
}

/*
#ifndef VOID
typedef void VOID;
#endif

#ifndef CHAR
typedef char CHAR;
#endif
#ifndef UCHAR
typedef unsigned char UCHAR;
#endif

#ifndef SHORT
typedef short SHORT;
#endif
#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef LONG
typedef long LONG;
#endif
#ifndef ULONG
typedef unsigned long ULONG;
#endif
*/

#ifdef BOOL_T
#undef BOOL_T
#endif
#define BOOL_T USHORT
//typedef USHORT BOOL_T;
#define BOOL_TRUE	((BOOL_T)1)
#define BOOL_FALSE	((BOOL_T)0)


typedef struct tagSOCKADDR
{
	UCHAR   sa_ucLen;               /* total length */
	UCHAR   sa_ucFamily;            /* address family */
	CHAR    sa_cData[14];           /* actually longer; address value */
}SOCKADDR_S;
#define         L_SOCKADDR_S    sizeof(SOCKADDR_S)

#ifdef NULL
#undef NULL
#endif

#define NULL    0 
/*Some systems define NULL as (-1), in our system, NULL must be (0). */

#ifndef VOS_OutPrintf
#define VOS_OutPrintf       vos_printf
#endif

#ifndef VOS_printf
#define VOS_printf          vos_printf
#endif


#ifdef  __cplusplus
}
#endif

#endif


