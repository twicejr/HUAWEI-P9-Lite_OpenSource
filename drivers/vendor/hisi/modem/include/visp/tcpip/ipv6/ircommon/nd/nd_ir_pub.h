

#ifndef __ND_IR_PUB_H__
#define __ND_IR_PUB_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "common/ipos/ipv6/basic/nd/nd_public.h"

/*----------------------------------------------*
 *              Macros                          *
 *----------------------------------------------*/

/* RA prefix related macros */
#define ND_PFX_STATUS_USABLE            0
#define ND_PFX_STATUS_NOT_USABLE        1

#define ND_LINKNOTIFYNODAD              5

/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* RFC 2461 => RS message format

      0                   1                   2                   3
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Type      |     Code      |          Checksum             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                            Reserved                           |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |   Options ...
     +-+-+-+-+-+-+-+-+-+-+-+-

*/

/* RS Packet structure */
typedef  struct tagND_RS_Packet
{
    ICMP6_S        stRSHdr;
}ND_RS_PACKET_S;

#define nd_rs_type                stRSHdr.ucIcmp6_type
#define nd_rs_code                stRSHdr.ucIcmp6_code
#define nd_rs_cksum                stRSHdr.usIcmp6_cksum
#define nd_rs_reserved            stRSHdr.unIcmp6_data.ulIcmp6_un_data32[0]

/* NA Packet structure */
typedef  struct tagND_NA_Packet
{
    ICMP6_S          stNAHdr;
    IN6ADDR_S        stNATarget;
}ND_NA_PACKET_S;

#define nd_na_type                 stNAHdr.ucIcmp6_type
#define nd_na_code                 stNAHdr.ucIcmp6_code
#define nd_na_cksum                stNAHdr.usIcmp6_cksum
#define nd_na_flags_reserved        stNAHdr.unIcmp6_data.ulIcmp6_un_data32[0]


/* RFC 2461: NS message format =>
         0                   1                   2                   3
         0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |     Type      |     Code      |          Checksum             |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |                           Reserved                            |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |                                                               |
        +                                                               +
        |                                                               |
        +                       Target Address                          +
        |                                                               |
        +                                                               +
        |                                                               |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |   Options ...
        +-+-+-+-+-+-+-+-+-+-+-+-
*/

/* NS Packet Structure */
typedef  struct tagND_NS_Packet
{
    ICMP6_S          stNSHdr;
    IN6ADDR_S        stNSTarget;
}ND_NS_PACKET_S;

#define nd_ns_type                 stNSHdr.ucIcmp6_type
#define nd_ns_code                 stNSHdr.ucIcmp6_code
#define nd_ns_cksum                stNSHdr.usIcmp6_cksum
#define nd_ns_flags_reserved       stNSHdr.unIcmp6_data.ulIcmp6_un_data32[0]


/* RFC 2461=> RA message format
      0                   1                   2                   3
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Type      |     Code      |          Checksum             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     | Cur Hop Limit |M|O|  Reserved |       Router Lifetime         |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                         Reachable Time                        |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                          Retrans Timer                        |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |   Options ...
     +-+-+-+-+-+-+-+-+-+-+-+-
*/

/* RA Packet structure */
typedef  struct tagND_RA_Packet
{
    ICMP6_S      stRAHdr;
    ULONG        ulReachableTime;
    ULONG        ulRetransTimer;
}ND_RA_PACKET_S;

#define nd_ra_type              stRAHdr.ucIcmp6_type
#define nd_ra_code              stRAHdr.ucIcmp6_code
#define nd_ra_cksum             stRAHdr.usIcmp6_cksum
#define nd_ra_curhoplimit       stRAHdr.unIcmp6_data.ucIcmp6_un_data8[0]
#define nd_ra_flags_reserved    stRAHdr.unIcmp6_data.ucIcmp6_un_data8[1]
#define nd_ra_router_lifetime   stRAHdr.unIcmp6_data.usIcmp6_un_data16[1]
#define ND_RA_FLAG_MANAGED      0x80
#define ND_RA_FLAG_OTHER        0x40
#define ND_NO_RA_FLAG           0x20

/* MIB entry message structure */
typedef struct tagIP6ND_MIBENTRYMSG_S
{
    ULONG          ulMsgType;
    ULONG          ulRequestType;
    ULONG          ulIfIndex;
    IN6ADDR_S      stipv6NetToMediaNetAdd;

    IP6_ND_Net2MediaTbl_S stpv6NetToMediaTbl;

}IP6ND_MIBENTRYMSG_S;


/* Redirect message format */
typedef  struct tagND_REDIRECT_Packet
{
    ICMP6_S          stRedirectHdr;     /* Redirect ICMP6 message header */
    IN6ADDR_S        stRedirectTarget;  /* ICMP6 Target address */
    IN6ADDR_S        stRedirectDest;    /* ICMP6 Destination Addres  */
}ND_REDIRECT_PACKET_S;

#define nd_rd_type               stRedirectHdr.ucIcmp6_type
#define nd_rd_code               stRedirectHdr.ucIcmp6_code
#define nd_rd_cksum              stRedirectHdr.usIcmp6_cksum
#define nd_rd_flags_reserved     stRedirectHdr.unIcmp6_data.ulIcmp6_un_data32[0]

/****************************************************************************
 *                  Nd_ir_pub.h Changes for ND Host Feature support         *
 ****************************************************************************/

/* Stateful address configuration information structure */
typedef struct tagIP6_ND_StatefulAddrCfgMsg
{
    /* Address with lifetime */
    IP6_ND_IN6ADDRWITHTIME_S *pstAddrWithTime;

    ULONG ulIAID;               /* IAID */
    ULONG ulAddrCnt;            /* Number of address given for configuration */

    IP6_ND_IATYPE_E enIAType;    /* IA type */

    /* Addition/Deletion/Life time updation */
    IP6_ND_STATEFULCFG_OPTTYPE_E eAddUpdateFlag;

}IP6_ND_STATEFULADDRCFGMSG_S;


/* Stateless Address Config Prefix information Provided to ADDR */
typedef struct tagIP6_ND_StatelessAddrCfgMsg
{
    IN6ADDR_S   stPrefix;       /* Prefix */

    ULONG   ulPreferredTime;    /* Preferred lifetime*/
    ULONG   ulValidTime;        /* Valid lifetime */

    UCHAR   ucPrefixLen;        /* Prefix Length */
    UCHAR   aucPad[3];          /* Padding */

}IP6_ND_STATELESSADDRCFGMSG_S;


/* Stateful address Not usable notification  Control message structure */
typedef struct tagIP6_ND_StatefulAddrNotUseMsg
{
    IP6_ND_IN6ADDRWITHTIME_S *pstAddrWithTime;      /* Address with lifetime */

    ULONG ulIAID;                                   /* IAID */

    IP6_ND_IATYPE_E enIAType;                        /* IA type */

    IP6_ND_NOTUSABLE_REASON_E enNotifyReason;       /* Not Usable Reason */

}IP6_ND_STFADDRNOTUSEMSG_S;


/* Prefix information for Stateless address configuration */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_PrefixOptList
{
    struct tagIP6_ND_PrefixOptList *pNext;        /* DLL pointers */
    struct tagIP6_ND_PrefixOptList *pPrev;    /* DLL pointers */

    IN6ADDR_S   stPrefix;   /* Prefix */

    ULONG   ulValidTime;    /* Valid lifetime */
    ULONG   ulPreferredTime;/* Preferred lifetime*/

    UCHAR ucPrefixLen;      /* Prefix Length */
    UCHAR ucFlagsReserved;  /* L and A flag */
    USHORT usPad;           /* Padding */

}IP6_ND_PREFIXOPTLIST_S;

/* Structure to hold input parameters for Next hop and outgoing interface
determination for the given Destination address When invoked by Addr,PMTU */
typedef struct tagIP6_ND_NHInputParam
{
    IN6ADDR_S stDestAddress;    /* Destination address */
    BOOL_T   bIsDataPath;       /* set to TRUE if Destination cache has to be
                                updated for this Next hop determination as
                                it is data path packet being queried for */
    UCHAR ucPad[2];             /* Padding */
    ULONG ulVrfIndex;
}IP6_ND_NHINPUTPARAM_S;

/* structure to Hold out parameters for Next hop and out going interface
determination  */
typedef struct tagIP6_ND_NHOutputParam
{
    IN6ADDR_S stNexthopAddr;    /* Next hop address */
    ULONG ulIfIndex;            /* Out Going Interface */
    ULONG ulFIBFlag;            /* Flags updated if next hop determination done
                                due to FIB lookup */
}IP6_ND_NHOUTPUTPARAM_S;

/* IO Board Exception Resolution, new structure is added
   to handle Async event between ADDR and ND*/
/* ND Event Message Strucutre */
typedef struct tagIP6_ND_EVENTMSG
{
    ULONG   ulMsgType;          /* Event message type */
    ULONG   ulIfIndex;          /* Interface Index */
    ULONG   ulEventVal;         /* Event specific value */
    ULONG   ulReserved;         /* Reserved for future use*/
}IP6_ND_EVENTMSG_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ND_IR_PUB_H__ */
