#ifndef _BASETYPE_H_
#define _BASETYPE_H_

/* 防止编译时，产品先包含了dopra或vos的头文件导致定义冲突 */
#ifndef VOS_MIPS
#define VOS_MIPS                       3
#endif

#include "v_typdef.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef TCPIP_DOPRA_V2    /*如用户需要使用Doprav2,则VISP与Dopra版本保持强依赖关系,需要包含Dopra头文件*/

#include "dopra_def.h"
#include "v_typdef.h"

#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif

/* Modified by wujie 61195 for BC3D00428 */
/*缺省为windows*/
#if (TCPIP_NOVRP_VXWORKS == VRP_YES)

#ifndef VRP_OS_WINDOWS
#define VRP_OS_WINDOWS           VRP_NO
#endif
#ifndef VRP_OS_VXWORKS
#define VRP_OS_VXWORKS           VRP_YES
#endif
#ifndef VRP_OS_LINUX
#define VRP_OS_LINUX             VRP_NO
#endif

#elif (TCPIP_NOVRP_LINUX == VRP_YES)

#ifndef VRP_OS_WINDOWS
#define VRP_OS_WINDOWS           VRP_NO
#endif
#ifndef VRP_OS_VXWORKS
#define VRP_OS_VXWORKS           VRP_NO
#endif
#ifndef VRP_OS_LINUX
#define VRP_OS_LINUX             VRP_YES
#endif

#else

#ifndef VRP_OS_WINDOWS
#define VRP_OS_WINDOWS           VRP_YES
#endif
#ifndef VRP_OS_VXWORKS
#define VRP_OS_VXWORKS           VRP_NO
#endif 
#ifndef VRP_OS_LINUX
#define VRP_OS_LINUX             VRP_NO
#endif

#endif


/*缺省为小头序*/
#ifndef TCPIP_BIG_ENDIAN

#ifndef VRP_LITTLE_ENDIAN
#define VRP_LITTLE_ENDIAN        VRP_YES
#endif
#ifndef VRP_BIG_ENDIAN
#define VRP_BIG_ENDIAN           VRP_NO
#endif

#else

#ifndef VRP_LITTLE_ENDIAN
#define VRP_LITTLE_ENDIAN        VRP_NO
#endif
#ifndef VRP_BIG_ENDIAN
#define VRP_BIG_ENDIAN           VRP_YES
#endif

#endif



#ifndef VOID
#define VOID VOS_VOID
#endif

#ifndef CHAR
#define CHAR VOS_CHAR
#endif

#ifndef UCHAR
#define UCHAR VOS_UINT8
#endif

#ifndef SHORT
#define SHORT VOS_INT16
#endif

#ifndef USHORT
#define USHORT  VOS_UINT16
#endif

#ifndef LONG
#define LONG VOS_INT32
#endif

#ifndef ULONG
#define ULONG VOS_UINT32
#endif

#ifndef INT8
#define INT8 VOS_INT8
#endif

#ifndef UINT8
#define UINT8 VOS_UINT8
#endif

#ifndef INT16
#define INT16 VOS_INT16
#endif

#ifndef UINT16
#define UINT16 VOS_UINT16
#endif

#ifndef INT32
#define INT32 VOS_INT32
#endif

#ifndef UINT32
#define UINT32 VOS_UINT32
#endif

#ifndef UINTPTR
#define UINTPTR VOS_UINTPTR
#endif

#ifndef UINT64
#if (VRP_OS_WINDOWS == VRP_YES)
    #define UINT64 unsigned __int64
#elif (VOS_HARDWARE_PLATFORM == VOS_MIPS)
    #define UINT64 VOS_UINT64
#else
    #define UINT64 unsigned long long
#endif
#endif

#ifndef SIZE_T
#ifdef TCPIP_NOVRP_64BIT
    #define SIZE_T unsigned long int
#else
    #define SIZE_T unsigned int
#endif
#endif

#else             /*如用户使用Doprav1或不使用Dopra,则VISP与Dopra保持解耦关系*/

#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif

/* Modified by wujie 61195 for BC3D00428 */
/*缺省为windows*/
#if (TCPIP_NOVRP_VXWORKS == VRP_YES)

#ifndef VRP_OS_WINDOWS
#define VRP_OS_WINDOWS           VRP_NO
#endif
#ifndef VRP_OS_VXWORKS
#define VRP_OS_VXWORKS           VRP_YES
#endif
#ifndef VRP_OS_LINUX
#define VRP_OS_LINUX             VRP_NO
#endif

#elif (TCPIP_NOVRP_LINUX == VRP_YES)

#ifndef VRP_OS_WINDOWS
#define VRP_OS_WINDOWS           VRP_NO
#endif
#ifndef VRP_OS_VXWORKS
#define VRP_OS_VXWORKS           VRP_NO
#endif
#ifndef VRP_OS_LINUX
#define VRP_OS_LINUX             VRP_YES
#endif

#else

#ifndef VRP_OS_WINDOWS
#define VRP_OS_WINDOWS           VRP_YES
#endif
#ifndef VRP_OS_VXWORKS
#define VRP_OS_VXWORKS           VRP_NO
#endif 
#ifndef VRP_OS_LINUX
#define VRP_OS_LINUX             VRP_NO
#endif

#endif


/*缺省为小头序*/
#ifndef TCPIP_BIG_ENDIAN

#ifndef VRP_LITTLE_ENDIAN
#define VRP_LITTLE_ENDIAN        VRP_YES
#endif
#ifndef VRP_BIG_ENDIAN
#define VRP_BIG_ENDIAN           VRP_NO
#endif

#else

#ifndef VRP_LITTLE_ENDIAN
#define VRP_LITTLE_ENDIAN        VRP_NO
#endif
#ifndef VRP_BIG_ENDIAN
#define VRP_BIG_ENDIAN           VRP_YES
#endif

#endif

#ifndef VOS_UINT32
#define VOS_UINT32 unsigned long
#endif

#ifndef VOS_INT32
#define VOS_INT32 long
#endif

#ifndef VOS_VOID
#define VOS_VOID void
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

#ifndef LONG
#define LONG long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef INT8
#define INT8 char
#endif

#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT16
#define INT16 short
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef INT32
#define INT32 long
#endif

#ifndef UINT32
#define UINT32 unsigned long
#endif

#ifndef UINTPTR
#ifdef TCPIP_NOVRP_64BIT
    #define UINTPTR unsigned long int
#else
    #define UINTPTR ULONG
#endif
#endif

#ifndef UINT64
#if (VRP_OS_WINDOWS == VRP_YES)
    #define UINT64 unsigned __int64
#else
    #define UINT64 unsigned long long
#endif
#endif

#ifndef SIZE_T
    #define SIZE_T VOS_UINT32
#endif

#endif         /*DEFINE END*/


#ifndef VOS_OK
#define VOS_OK                 (0)
#endif
#ifndef VOS_ERR
#define VOS_ERR                (1)    
#endif

#ifndef VRP_YES
#define VRP_YES    1
#endif

#ifndef VRP_NO
#define VRP_NO      0
#endif

#ifndef _DULONG
#define _DULONG
typedef struct tagUULONG 
{
        ULONG hi;
        ULONG lo;
} UULONG;


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
    #if (VRP_BIG_ENDIAN==VRP_YES)
        USHORT usHiHi_s;
        USHORT usHiLo_s;
        USHORT usLoHi_s;
        USHORT usLoLo_s;
    #else
        USHORT usHiLo_s;
        USHORT usHiHi_s;
        USHORT usLoLo_s;
        USHORT usLoHi_s;
    #endif
    }y;

#define ulHi    x.ulHi_l
#define ulLo    x.ulLo_l
#define usHiHi  y.usHiHi_s
#define usHiLo  y.usHiLo_s
#define usLoHi  y.usLoHi_s
#define usLoLo  y.usLoLo_s
}DULONG;

#endif

typedef VOID   (*VOS_VOIDVRPFUNCPTR)(); /* ptr to function returning VOS_VOID */
typedef ULONG  (*VOS_ULONGVRPFUNCPTR)();/* ptr to function returning VOS_UING32 */
/*     dulFirst<dulSecond:        return -1;
    dulFirst>dulSecond:     return 1;
    dulFirst==dulSecond:    return 0;
*/
#define DULONG_COMPARE(dulFirst,dulSecond) \
    (((dulFirst).ulHi<(dulSecond).ulHi)?-1: \
        (((dulFirst).ulHi>(dulSecond).ulHi)?1: \
            (((dulFirst).ulLo<(dulSecond).ulLo)?-1: \
                (((dulFirst).ulLo>(dulSecond).ulLo)?1:0))))

/* Modified by X36317, 将原来的结构体赋值改为逐个对结构成员赋值，以解决ARM CPU字节对齐问题, 2006/5/23 */
#define DULONG_ADD(dulSum,dulFirst,dulSecond)    \
{ \
    DULONG dulSum_temp; \
    \
    (dulSum_temp).ulLo = (dulFirst).ulLo+(dulSecond).ulLo; \
    (dulSum_temp).ulHi = (dulFirst).ulHi+(dulSecond).ulHi+(ULONG)((dulSum_temp).ulLo<(dulFirst).ulLo); \
    /*(dulSum)           =  dulSum_temp;*/ \
    (dulSum).ulLo = (dulSum_temp).ulLo;\
    (dulSum).ulHi = (dulSum_temp).ulHi;\
}

#define DULONG_SUB(dulResult,dulFirst,dulSecond) \
{ \
    DULONG dulResult_temp; \
    \
    (dulResult_temp).ulLo = (dulFirst).ulLo-(dulSecond).ulLo; \
    (dulResult_temp).ulHi = (dulFirst).ulHi-(dulSecond).ulHi-(ULONG)((dulResult_temp).ulLo>(dulFirst).ulLo); \
    /*(dulResult)           =  dulResult_temp; */\
    (dulResult).ulLo = (dulResult_temp).ulLo;\
    (dulResult).ulHi = (dulResult_temp).ulHi;\
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
    /*(dulResult)=dulResult_temp; */\
    (dulResult).ulLo = (dulResult_temp).ulLo;\
    (dulResult).ulHi = (dulResult_temp).ulHi;\
}

/* second must <65536(0-65535) */
#define DULONG_DIV(dulResult,dulFirst,ulSecond,ulMod) \
{ \
    DULONG dulResult_temp,dulResult_temp2; \
    \
    dulResult_temp.ulHi=dulFirst.ulHi/(ulSecond); \
    dulResult_temp2.usHiHi=dulFirst.ulHi%(ulSecond); \
    dulResult_temp2.usHiLo=dulFirst.usLoHi; \
    dulResult_temp.usLoHi=dulResult_temp2.ulHi/(ulSecond); \
    dulResult_temp2.usLoHi=dulResult_temp2.ulHi%(ulSecond); \
    dulResult_temp2.usLoLo=dulFirst.usLoLo; \
    dulResult_temp.usLoLo=dulResult_temp2.ulLo/(ulSecond); \
    (ulMod)=dulResult_temp2.ulLo%(ulSecond); \
    /*(dulResult)=dulResult_temp; */\
    (dulResult).ulLo = (dulResult_temp).ulLo;\
    (dulResult).ulHi = (dulResult_temp).ulHi;\
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

typedef USHORT BOOL_T;
#define BOOL_TRUE    ((BOOL_T)1)
#define BOOL_FALSE    ((BOOL_T)0)


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
/*#define VOS_OutPrintf       VOS_printf*/
#define VOS_OutPrintf       VOS_Printf
#endif

#ifndef VOSFatalError
extern VOS_VOID VOSFatalError_X(VOS_CHAR * szFile, VOS_UINT32 ulLine);
#define VOSFatalError() VOSFatalError_X(__FILE__,__LINE__)
#endif


#ifdef  __cplusplus
}
#endif

#endif


