#ifndef _VRPCFG_H_
#define _VRPCFG_H_


#if 1
#ifdef __WIN32_PLATFORM__
#include "stdio.h"
#endif

#ifndef VOS_PACKED
#ifdef __WIN32_PLATFORM__
#define     VOS_PACKED
#else
#define     VOS_PACKED      __attribute__ ((__packed__))
#endif
#endif

#define MID_PPPC        MSPS_PID_PPPC

#define VRP_MODULE_LINK_PPP 1
#define VRP_MODULE_LINK_PPP_PAP 1
#define VRP_MODULE_LINK_PPP_CHAP 1
#define VRP_MODULE_SEC_L2TP 0

#ifndef _lint
typedef unsigned long   ULONG;
typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
#endif

typedef signed long     LONG;
typedef signed short    SHORT;
#ifndef SRE_TYPE_DEF
typedef signed char     CHAR;
#ifndef _lint
typedef void            VOID;
#endif
#endif
typedef unsigned long long ULONG64;
typedef signed long long   LONG64;
#ifndef _lint
typedef unsigned long long UINT64;
#endif
typedef unsigned int    SEC_UINT32;

#ifndef SRE_TYPE_DEF
typedef VOS_SIZE_T      SIZE_T;
#endif

typedef signed int      CDB_RECID;
typedef unsigned short  DMS_IID_T;
typedef unsigned int    DMS_COMMID_T;


typedef void            PF_VOID;
typedef long            PF_LONG;
typedef unsigned long   PF_ULONG;
typedef unsigned char   PF_UCHAR;
typedef short           PF_SHORT;
typedef unsigned short  PF_USHORT;
typedef signed char     PF_CHAR;
typedef unsigned long long PF_DULONG;
typedef int                         SM_LONG;
typedef unsigned int                SM_ULONG;
typedef unsigned char               SM_UCHAR;
typedef SM_ULONG                    SM_BOOL;
typedef void                        SM_VOID;
typedef unsigned long long DULONG;

typedef signed int  CDB_DBID;
typedef signed int  CDB_TBLID;


#define VOS_NTOHS(x)  ((((x)& 0xFF00)>>8) |  (((x) & 0x00FF)<<8))
#define VOS_NTOHL(x) ((((x)&0xff)<<24)|(((x)&0xff00)<<8)|(((x)&0xff0000)>>8)|(((x)&0xff000000)>>24))
#define VOS_HTONS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))
#define VOS_HTONL(x)                   ((((VOS_UINT32)(x) & 0x000000ff) << 24) | \
                                        (((VOS_UINT32)(x) & 0x0000ff00) <<  8) | \
                                        (((VOS_UINT32)(x) & 0x00ff0000) >>  8) | \
                                        (((VOS_UINT32)(x) & 0xff000000) >> 24))


#include "balong.h"
#include "balong_stub.h"
#endif


#endif
