/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_basetype.h
*
*  Project Code: VISPV100R007
*   Module Name: PUBLIC
*  Date Created: 2008-4-17
*        Author: X36317
*   Description: VISP提供的用户API所依赖的基础数据类型和宏定义
*                此头文件用来替代并解决原VISP版本发布时需要附带一堆vrpvos相关的头文件的问题。
*                注:该头文件已经被tcpip_shell.h所包含，若产品已经包含了tcpip_shell.h文件就不需要再包含此头文件。
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-4-17    X36317          Create the first version.
*
*******************************************************************************/

#ifndef _TCPIP_BASETYPE_H_
#define _TCPIP_BASETYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*#include "vos_errno.h"*/

#ifdef TCPIP_DOPRA_V2    /*如用户需要使用Doprav2,则VISP与Dopra版本保持强依赖关系,需要包含Dopra头文件*/

#ifndef TCPIP_FORBALONG
#include "dopra_def.h"
#endif

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
#define INT32 int
#endif

#ifndef UINT32
#define UINT32 unsigned int
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

#endif         /*DEFINE END*/


#ifndef _DULONG
#define _DULONG
typedef struct tagUULONG
{
    ULONG hi;
    ULONG lo;
} UULONG;

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

/*与v_typdef.h定义冲突*/
/*End of Modified by l61496, u32类型定义冲突，问题单号:DTS2012121300451 ,2012/12/14 */
#ifdef TCPIP_DOPRA_VER2
#ifndef VOS_UINT32
#define VOS_UINT32 unsigned int
#endif

#ifndef VOS_INT32
#define VOS_INT32 int
#endif

#ifndef VOS_VOID
#define VOS_VOID void
#endif
#endif

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

#ifndef BOOL_TRUE
#ifndef BOOL_T
#define BOOL_T USHORT
#endif
#define BOOL_TRUE    ((BOOL_T)1)
#endif
#ifndef BOOL_FALSE
#define BOOL_FALSE    ((BOOL_T)0)
#endif


#ifdef NULL
#undef NULL
#endif

#define NULL    0
/*Some systems define NULL as (-1), in our system, NULL must be (0). */



/*产品包含此头文件时，必须定义VOS_HARDWARE_PLATFORM,因为此宏控制
XXX_api.h中的数据结构对齐方式,此处屏蔽了pc_lint告警，因为这个宏
是需要用户在makefile中显式指定值，如果不指定，编译错误*/
/*lint -save -e309*/
#ifndef VOS_HARDWARE_PLATFORM
#error "please define VOS_HARDWARE_PLATFORM in makefile"
#endif
/*lint -restore*/

#ifndef VOS_ARM
#define VOS_ARM                  8
#endif

#ifndef _SOCKADDR_S
#define _SOCKADDR_S
typedef struct tagSOCKADDR
{
    UCHAR   sa_ucLen;               /* total length */
    UCHAR   sa_ucFamily;            /* address family */
    CHAR    sa_cData[14];           /* actually longer; address value */
}SOCKADDR_S;
#define         L_SOCKADDR_S    sizeof(SOCKADDR_S)
#endif

#ifndef VOS_DBGASSERT
extern VOID VOS_Assert_X(LONG lExpression, CHAR *pcFileName, ULONG ulLine);
#define VOS_DBGASSERT(lExpression) \
{\
    LONG lExpressionTemp = (LONG)(lExpression); \
    if (!(lExpressionTemp))\
    {\
        VOS_Assert_X(lExpressionTemp,__FILE__,__LINE__);\
    }\
}
#endif


#ifdef  __cplusplus
}
#endif /*__cplusplus*/

#endif /*_TCPIP_BASETYPE_H_*/

