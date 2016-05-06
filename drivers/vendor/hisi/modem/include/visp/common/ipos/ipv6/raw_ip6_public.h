/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              raw_ip6_public.h
*
*    Project Code: VRP5.0
*    Module Name : IP6 RawIp6
*    Create Date : 2006/04/11
*    Author      : Arun V
*    Description : To define RawIp6 structures that are required by other
     components
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-04-11  Arun V        Created for including all public definitions in
*    this file, for IPOSV1R1
************************************************************************
*/
#ifndef _RAWIP6_PUBLIC_H
#define _RAWIP6_PUBLIC_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack (1)
#endif

/*MAX_INT to arm allign the enums*/
#define IP6_RIP6_MAX_ENUM_VALUE            0xFFFFFFFF

/* Added by Saravanya for handling Semaphore lock failure condition */
#define RAWIP6_ERR_SEMOP_ACQUIRELOCK_FAIL 2

/*RIP6 statistics*/
typedef struct tagRip6stat
{
    ULONG ulRip6s_inpackets;   /* total input packets */
    ULONG ulRip6s_insum;        /* input checksum computations */
    ULONG ulRip6s_badsum;       /* of above, checksum lError */
    ULONG ulRip6s_nosock;       /* no matching socket */
    ULONG ulRip6s_nosockmcast;  /* of above, arrived as multicast */
    ULONG ulRip6s_fullsock;     /* not delivered, input socket full */
    ULONG ulRip6s_opackets;     /* total output packets */
    ULONG ulRip6s_ExtPreProc;
}RIP6STAT_S;

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack()
#endif


#ifdef  __cplusplus
}
#endif

#endif

