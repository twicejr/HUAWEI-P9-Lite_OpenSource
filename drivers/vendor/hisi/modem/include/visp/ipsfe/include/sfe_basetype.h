/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_basetype.h
*
*  Project Code: V1.1.0
*   Module Name: 
*  Date Created: 2009-7-27
*        Author: w60786
*   Description: SFE提供的用户API及内部使用所依赖的基础数据类型和宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-7-27  w60786         Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_BASETYPE_H_
#define _SFE_BASETYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif


#ifndef SFE_OK
#define SFE_OK      0
#endif
#ifndef SFE_ERR
#define SFE_ERR     1
#endif

#ifndef SFE_YES
#define SFE_YES     1
#endif

#ifndef SFE_NO
#define SFE_NO      0
#endif

#ifndef SFE_TRUE
#define SFE_TRUE    1
#endif

#ifndef SFE_FALSE
#define SFE_FALSE   0
#endif

/*Some systems define NULL as (-1), in our system, NULL must be (0). */
#ifdef NULL
#undef NULL
#endif

#define NULL    0 

#if (SFE_NOVRP_VXWORKS == SFE_YES)
#define SFE_OS_WINDOWS           SFE_NO
#define SFE_OS_VXWORKS           SFE_YES
#define SFE_OS_LINUX             SFE_NO
#elif (SFE_NOVRP_LINUX == SFE_YES)
#define SFE_OS_WINDOWS           SFE_NO
#define SFE_OS_VXWORKS           SFE_NO
#define SFE_OS_LINUX             SFE_YES
#else
#undef SFE_OS_WINDOWS
#define SFE_OS_WINDOWS           SFE_YES
#define SFE_OS_VXWORKS           SFE_NO
#define SFE_OS_LINUX             SFE_NO
#endif

/*缺省为小头序*/
#ifndef SFE_ORDER_BIG_ENDIAN
#define SFE_LITTLE_ENDIAN        SFE_YES
#define SFE_BIG_ENDIAN           SFE_NO
#else
#define SFE_LITTLE_ENDIAN        SFE_NO
#define SFE_BIG_ENDIAN           SFE_YES
#endif

#if (SFE_LITTLE_ENDIAN == SFE_YES)
#define SFE_NTOHL(x)                   ((((x) & 0x000000ff) << 24) | \
                                        (((x) & 0x0000ff00) <<  8) | \
                                        (((x) & 0x00ff0000) >>  8) | \
                                        (((x) & 0xff000000) >> 24))

#define SFE_HTONL(x)                   ((((x) & 0x000000ff) << 24) | \
                                        (((x) & 0x0000ff00) <<  8) | \
                                        (((x) & 0x00ff0000) >>  8) | \
                                        (((x) & 0xff000000) >> 24))

#define SFE_NTOHS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))

#define SFE_HTONS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))

#else
#ifndef SFE_NTOHL
#define SFE_NTOHL(x) (x)
#endif
#ifndef SFE_NTOHS
#define SFE_NTOHS(x) (x)
#endif
#ifndef SFE_HTONL
#define SFE_HTONL(x) (x)
#endif
#ifndef SFE_HTONS
#define SFE_HTONS(x) (x)
#endif
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

#ifndef UINT64
#if (SFE_OS_WINDOWS == SFE_YES)
    #define UINT64 unsigned __int64
#else
    #define UINT64 unsigned long long
#endif
#endif

#ifndef INT64
#if (SFE_OS_WINDOWS == SFE_YES)
    #define INT64 __int64
#else
    #define INT64 long long
#endif
#endif

#ifndef VOID
#define VOID void
#endif

#ifndef LEN_8
#define LEN_8    8
#endif

#ifndef LEN_16
#define LEN_16   16
#endif

#ifndef LEN_32
#define LEN_32   32
#endif

#ifndef LEN_64
#define LEN_64   64
#endif

#ifndef LEN_128
#define LEN_128  128
#endif

#ifndef LEN_256
#define LEN_256  256
#endif

#ifndef LEN_512
#define LEN_512  512
#endif

#ifndef LEN_1024
#define LEN_1024 1024
#endif

#ifndef LEN_2048
#define LEN_2048 2048
#endif


/* 数据面地址信息结构定义 */
typedef union unSFE_IPADDR
{
    UINT32 u32IPv4;       /* IPv4地址 */
    UINT32 u32IPv6[4];    /* IPv6地址 */
}SFE_IPADDR_UN;


#define SFE_IN_CLASSA(i)        (0 == ((INT32)(i) & 0x80000000L))

#define SFE_IN_CLASSB(i)        (0x80000000L == ((INT32)(i) & 0xc0000000L))

#define SFE_IN_CLASSC(i)        (0xc0000000L == ((INT32)(i) & 0xe0000000L))

#define SFE_IN_CLASSD(i)        (0xe0000000L == ((INT32)(i) & 0xf0000000L))
#define SFE_IN_MULTICAST(i)     SFE_IN_CLASSD(i)

#ifdef  __cplusplus
}
#endif /*__cplusplus*/

#endif /*_SFE_BASETYPE_H_*/

