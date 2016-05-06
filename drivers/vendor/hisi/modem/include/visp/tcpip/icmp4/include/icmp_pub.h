/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_pub.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: ìá1????￡?éía2?ê1ó?μ?oê?¨ò?￡??á11ì?oíoˉêyéù?÷
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _ICMP_PUB_H_
#define _ICMP_PUB_H_

#include "tcpip/icmp4/include/icmp_api.h"

/*
 * Definition of type and code field values.
 */


#define ICMP_INFOTYPE(type) \
    (ICMP_ECHOREPLY == (type) || ICMP_ECHO == (type) || \
    ICMP_ROUTERADVERT == (type) || ICMP_ROUTERSOLICIT == (type) || \
    ICMP_TSTAMP == (type) || ICMP_TSTAMPREPLY == (type) || \
    ICMP_IREQ == (type) || ICMP_IREQREPLY == (type) || \
    ICMP_MASKREQ == (type) || ICMP_MASKREPLY == (type))

/*
 * Names for ICMP sysctl objects
 */
#define ICMPCTL_MASKREPL    1   /* allow replies to netmask requests */
#define ICMPCTL_MAXID       2

/*Added by wangbin,增加组播广播ping防攻击类型值, 2015/10/21   DTS:DTS2015102607862 */
#define     ICMP_SRCADDR_ANY          20    /* ICMP源地址 0.0.0.0 */
#define     ICMP_DSTADDR_BCASTORMCAST    21    /* ICMP报文目的广播地址或子网广播地址 */

/*
 * Interface Control Message Protocol Definitions.
 * Per RFC 792, September 1981.
 */
typedef ULONG   NTIME;  /* ms since 00:00 GMT, byte rev */

#define ICMP_STAT_IN        0       /* Indicate an incoming icmp packet */
#define ICMP_STAT_OUT       1       /* Indicate an outgoing icmp packet */

#define ICMP_NO_SEND_ERR    0       /* Indicates no error in sending icmp packet */
#define ICMP_SEND_ERR       1       /* Indicates error in sending icmp packet */

#define ICMP_STAT_ENABLE    1       /* Used for enable g_ulIcmpStatsFlag */

/*
 * Structure of an icmp header.
 */
typedef struct tagICMP
{
    UCHAR   icmp_chType;        /* type of message, see below */
    UCHAR   icmp_chCode;        /* type sub code */
    USHORT  icmp_usCksum;       /* ones complement cksum of struct */
    union
    {
        UCHAR   ih_chPPtr;              /* ICMP_PARAMPROB */
        struct tagINADDR ih_stGwAddr;   /* ICMP_REDIRECT */
        struct tagIHIDSEQ
        {
            USHORT  icd_nsId;
            USHORT  icd_nsSeq;
        } ih_stIdSeq;
                LONG     ih_nVoid;

        /* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
        struct tagIHPMTU
        {
            USHORT ipm_nsVoid;
            USHORT ipm_nsNextMtu;
        } ih_stPMtu;
    }icmp_unHun;
#define icmp_chPPtr     icmp_unHun.ih_chPPtr
#define icmp_stGwAddr   icmp_unHun.ih_stGwAddr
#define icmp_nsId       icmp_unHun.ih_stIdSeq.icd_nsId
#define icmp_nsSeq      icmp_unHun.ih_stIdSeq.icd_nsSeq
#define icmp_nVoid      icmp_unHun.ih_nVoid
#define icmp_nsPmVoid   icmp_unHun.ih_stPMtu.ipm_nsVoid
#define icmp_nsNextMtu  icmp_unHun.ih_stPMtu.ipm_nsNextMtu
    union
    {
        struct tagIDTS
        {
            NTIME  its_ntOTime;
            NTIME  its_ntRTime;
            NTIME  its_ntTTime;
        } id_stTS;
        struct tagIDIP
        {
            struct tagIP idi_stIp;
            /* options and then 64 bits of data */
        } id_stIp;
        ULONG   id_ulMask;
        char    id_chData_a[9];
    } icmp_unDun;
#define icmp_ntOTime    icmp_unDun.id_stTS.its_ntOTime
#define icmp_ntRTime    icmp_unDun.id_stTS.its_ntRTime
#define icmp_ntTTime    icmp_unDun.id_stTS.its_ntTTime
#define icmp_stIp       icmp_unDun.id_stIp.idi_stIp
#define icmp_ulMask     icmp_unDun.id_ulMask
#define icmp_chData_a   icmp_unDun.id_chData_a
}ICMP_S;

#endif  /*  _ICMP_PUB_H_  */

#ifdef  __cplusplus
}
#endif

