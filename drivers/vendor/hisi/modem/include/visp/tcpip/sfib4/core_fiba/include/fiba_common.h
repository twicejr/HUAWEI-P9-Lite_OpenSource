/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fiba_common.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-10
*       Author: Zhang Hongyan
*  Description: Contains the macros for address manipulation
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-10   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859
*  2006-07-12   j51916                  Adjust for D03373
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB6_COMMON_H_
#define _FIB6_COMMON_H_


/* pDest and pSrc must be a array that have 4 ULONG element */
#define FIB6_ADDRESS_COPY( pDest, pSrc )    \
{\
    (pDest)[0] = (pSrc)[0];\
    (pDest)[1] = (pSrc)[1];\
    (pDest)[2] = (pSrc)[2];\
    (pDest)[3] = (pSrc)[3];\
}

/* x must be a array that have 4 ULONG element */
#define FIB6_ADDRESS_NTOH(x) \
{\
   (x)[0] = VOS_NTOHL((x)[0]);\
   (x)[1] = VOS_NTOHL((x)[1]);\
   (x)[2] = VOS_NTOHL((x)[2]);\
   (x)[3] = VOS_NTOHL((x)[3]);\
}

/* x must be a array that have 4 ULONG element */
#define FIB6_ADDRESS_HTON(x) \
{\
   (x)[0] = VOS_HTONL((x)[0]);\
   (x)[1] = VOS_HTONL((x)[1]);\
   (x)[2] = VOS_HTONL((x)[2]);\
   (x)[3] = VOS_HTONL((x)[3]);\
}

/*
 * pDest and pSrc must be a array that have 4 ULONG element
 * return value:
 *      1 -- pDest and pSrc is equal
 *      0 -- pDest and pSrc isn't equal
 */
#define FIB6_IS_ADDRESS_EQUAL( pDest, pSrc )      \
    ( ((pDest)[0] == (pSrc)[0]) \
     && ((pDest)[1] == (pSrc)[1]) \
     && ((pDest)[2] == (pSrc)[2]) \
     && ((pDest)[3] == (pSrc)[3]) )


/*
 * pAddress must be a array that have 4 ULONG element
 * return value:
 *      1 -- pAddress is a NULL address
 *      0 -- pAddress isn't a NULL address
 */

#define FIB6_IS_ADDRESS_NULL( pAddress )         \
    ( (0 == (pAddress)[0]) \
     && (0 == (pAddress)[1]) \
     && (0 == (pAddress)[2]) \
     && (0 == (pAddress)[3]) )


/*
 * pAddress must be a array that have 4 ULONG element
 * return value:
 *      1 -- pAddress is a link-local address
 *      0 -- pAddress isn't a link-local address
 */
#define FIB6_IS_ADDRESS_LINKLOCAL( pAddress )    \
    ( 0xFE800000 == (0xFFC00000&((pAddress)[0])) )

/*
 * pAddress must be a array that have 4 ULONG element
 * return value:
 *      1 -- pAddress is a site-local address
 *      0 -- pAddress isn't a site-local address
 */
#define FIB6_IS_ADDRESS_SITELOCAL( pAddress )    \
    ( 0xFEC00000 == (0xFFC00000&((pAddress)[0])) )

/*
 * pAddress must be a array that have 4 ULONG element
 * return value:
 *      1 -- pAddress is a loopback address
 *      0 -- pAddress isn't a loopback address
 */
#define FIB6_IS_ADDRESS_LOOPBACK( pAddress )     \
    ( (0 == (pAddress)[0]) \
     && (0 == (pAddress)[1]) \
     && (0 == (pAddress)[2]) \
     && (1 == (pAddress)[3]) )


/*
 * pAddress must be a array that have 4 ULONG element
 * return value:
 *      1 -- pAddress is a multicast address
 *      0 -- pAddress isn't a multicast address
 */
#define FIB6_IS_ADDRESS_MULTICAST( pAddress )    \
    ( 0xFF000000 == (0xFF000000&((pAddress)[0])) )


/*
 * pAddress must be a array that have 4 ULONG element
 * return value:
 *      1 -- pAddress is a global address
 *      0 -- pAddress isn't a global address
 */
#define FIB6_IS_ADDRESS_GLOBAL( pAddress )    \
    ( !((FIB6_IS_ADDRESS_MULTICAST(pAddress))\
     ||(FIB6_IS_ADDRESS_LOOPBACK(pAddress))\
     ||(FIB6_IS_ADDRESS_LINKLOCAL(pAddress))\
     ||(FIB6_IS_ADDRESS_NULL(pAddress))) )

#define FIB6_IS_ADDRESS_6To4( pAddress )    \
    ( 0x20020000 == (0xFFFF0000&((pAddress)[0])) ) /* updated for defect 5784, by Guru, 18-12-03 */

/* x must be a array that have 4 ULONG element */
#define RT6_ADDRESS_HTON(x) FIB6_ADDRESS_NTOH(x)

#define RT6_SET_ADDRESS_LOOPBACK( pAddress )     \
{\
    (pAddress)[0] = 0;\
    (pAddress)[1] = 0;\
    (pAddress)[2] = 0;\
    (pAddress)[3] = 1;\
}

#define RT6_SET_ADDRESS_LINKLOCAL( pAddress )    \
{\
    (pAddress)[0] = 0xfe800000;\
    (pAddress)[1] = 0;\
    (pAddress)[2] = 0;\
    (pAddress)[3] = 0;\
}
#define FIB6_SET_ADDRESS_NULL( pAddress )    \
{\
    (pAddress)[0] = 0;\
    (pAddress)[1] = 0;\
    (pAddress)[2] = 0;\
    (pAddress)[3] = 0;\
}


#define FIB6_ALLOC( ulInfo, ulSize)     TCPIP_Malloc ( ulInfo, ulSize)
#define FIB4_ALLOC( ulInfo, ulSize)     TCPIP_Malloc ( ulInfo, ulSize)

#if (VRP_YES == VRP_MODULE_VRF6)
#define FIB6_IS_ZONEID_VALID(usZoneId) \
   ((0 <= (SHORT)(usZoneId)) && \
   ((SHORT)g_ulFib6MaxZoneNum >= (SHORT)(usZoneId)))
#else
#define FIB6_IS_ZONEID_VALID(usZoneId) \
   ((0 <= (SHORT)(usZoneId)) && \
   (FIB6_MAX_NUM_OF_ZONES >= (SHORT)(usZoneId)))
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB4_IS_ZONEID_VALID(usZoneId) \
   ((0 <= (SHORT)(usZoneId)) && \
    (g_ulFib4MaxZoneNum >= (SHORT)(usZoneId)))
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define FIB6_IS_SLOTID_VALID(ulSlotId) \
   ((0 <= (LONG)(ulSlotId)) && \
   (VRP_MAX_BOARD_NUM >= (LONG)(ulSlotId)))

#define FIB6_IS_RTMSG6_VALID(pstRtMsg)  \
    ( (NULL != pstRtMsg) && \
        FIB6_IS_ZONEID_VALID ((pstRtMsg)->usZoneID) && \
        FIB6_IS_SLOTID_VALID ((pstRtMsg)->ulSlot))

#define FIB4_IS_RTMSG6_VALID(pstRtMsg)  \
    (NULL != pstRtMsg)

#define FIB6_IS_ROUTE6_VALID(pstRoute6)  \
    ( (NULL != pstRoute6) && \
        FIB6_IS_ZONEID_VALID ((pstRoute6)->usZoneID) && \
        ! (FIB6_IS_ADDRESS_NULL ((pstRoute6)->aulDestination)) )

#define RT6_ENTRY_HTON(pRTEntry)  \
{\
    FIB6_ADDRESS_HTON ((pRTEntry)->aulRt_Dest)   \
    FIB6_ADDRESS_HTON ((pRTEntry)->aulRt_Nexthop)   \
    (pRTEntry)->ulRt_Dest_PrefLen = VOS_HTONL ((pRTEntry)->ulRt_Dest_PrefLen); \
    (pRTEntry)->ulRt_Flags = VOS_HTONL ((pRTEntry)->ulRt_Flags); \
    (pRTEntry)->ulRt_IfIndex = VOS_HTONL ((pRTEntry)->ulRt_IfIndex); \
    (pRTEntry)->ulRt_ATIndex = VOS_HTONL ((pRTEntry)->ulRt_ATIndex); \
    (pRTEntry)->ulRt_Slot = VOS_HTONL ((pRTEntry)->ulRt_Slot); \
    (pRTEntry)->ulCacheEntryIndex = VOS_HTONL ((pRTEntry)->ulCacheEntryIndex); \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (pRTEntry)->ulLabel = VOS_HTONL ((pRTEntry)->ulLabel); \
    (pRTEntry)->ulToken = VOS_HTONL ((pRTEntry)->ulToken); \
}

#define RT6_ENTRY_NTOH(pRTEntry)  \
{\
    FIB6_ADDRESS_NTOH ((pRTEntry)->aulRt_Dest)   \
    FIB6_ADDRESS_NTOH ((pRTEntry)->aulRt_Nexthop)   \
    (pRTEntry)->ulRt_Dest_PrefLen = VOS_NTOHL ((pRTEntry)->ulRt_Dest_PrefLen); \
    (pRTEntry)->ulRt_Flags = VOS_NTOHL ((pRTEntry)->ulRt_Flags); \
    (pRTEntry)->ulRt_IfIndex = VOS_NTOHL ((pRTEntry)->ulRt_IfIndex); \
    (pRTEntry)->ulRt_ATIndex = VOS_NTOHL ((pRTEntry)->ulRt_ATIndex); \
    (pRTEntry)->ulRt_Slot = VOS_NTOHL ((pRTEntry)->ulRt_Slot); \
    (pRTEntry)->ulCacheEntryIndex = VOS_NTOHL ((pRTEntry)->ulCacheEntryIndex); \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (pRTEntry)->ulLabel = VOS_NTOHL ((pRTEntry)->ulLabel); \
    (pRTEntry)->ulToken = VOS_NTOHL ((pRTEntry)->ulToken); \
}

#define RT_MSG6_NTOH(stRtMsg) \
{\
    FIB6_ADDRESS_NTOH ((stRtMsg).aulDestination)   \
    FIB6_ADDRESS_NTOH ((stRtMsg).aulNexthop)   \
    FIB6_ADDRESS_NTOH ((stRtMsg).aulNexthop_Relay)  \
    (stRtMsg).usType = (USHORT)VOS_NTOHS ((stRtMsg).usType); \
    (stRtMsg).usZoneID = (USHORT)VOS_NTOHS ((stRtMsg).usZoneID); \
    (stRtMsg).ulIfIndex = VOS_NTOHL ((stRtMsg).ulIfIndex); \
    (stRtMsg).ulATIndex= VOS_NTOHL ((stRtMsg).ulATIndex); \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (stRtMsg).ulLabel = VOS_NTOHL ((stRtMsg).ulLabel); \
    (stRtMsg).ulToken= VOS_NTOHL ((stRtMsg).ulToken); \
    FIB6_ADDRESS_NTOH ((stRtMsg).aulOldNexthop)   \
    FIB6_ADDRESS_NTOH ((stRtMsg).aulOldNexthop_Relay)  \
    (stRtMsg).ulOldIfIndex = VOS_NTOHL ((stRtMsg).ulOldIfIndex); \
    (stRtMsg).ulOldATIndex= VOS_NTOHL ((stRtMsg).ulOldATIndex); \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (stRtMsg).ulOldLabel = VOS_NTOHL ((stRtMsg).ulOldLabel); \
    (stRtMsg).ulOldToken= VOS_NTOHL ((stRtMsg).ulOldToken); \
}

#define RT_MSG4_NTOH(stRtMsg) \
{\
    (stRtMsg).ulDestination = VOS_NTOHL((stRtMsg).ulDestination);  \
    (stRtMsg).ulNexthop = VOS_NTOHL((stRtMsg).ulNexthop);   \
    (stRtMsg).usType = (USHORT)VOS_NTOHS ((stRtMsg).usType); \
    (stRtMsg).usZoneID = (USHORT)VOS_NTOHS ((stRtMsg).usZoneID); \
    (stRtMsg).ulIfIndex = VOS_NTOHL ((stRtMsg).ulIfIndex); \
    (stRtMsg).ulATIndex= VOS_NTOHL ((stRtMsg).ulATIndex); \
}

#define FIB_IPV4_MSG 0
#define FIB_IPV6_MSG 1

#define RT6_CMD_NTOH(stRtCmd) \
{\
    (stRtCmd).ulRtcmd_Group = VOS_NTOHL ((stRtCmd).ulRtcmd_Group); \
    if(FIB_IPV6_MSG == (stRtCmd).ulVer)\
    {\
        RT_MSG6_NTOH ((stRtCmd).stRtcmd.stRtcmd_RtMsg); \
    }\
    else\
    {\
        RT_MSG4_NTOH ((stRtCmd).stRtcmd.stRtcmd4_RtMsg); \
    }\
}

#define RT_MSG6_HTON(stRtMsg) \
{\
    FIB6_ADDRESS_HTON ((stRtMsg).aulDestination)   \
    FIB6_ADDRESS_HTON ((stRtMsg).aulNexthop)   \
    FIB6_ADDRESS_HTON ((stRtMsg).aulNexthop_Relay)   \
    (stRtMsg).usType = (USHORT)VOS_HTONS ((stRtMsg).usType); \
    (stRtMsg).usZoneID = (USHORT)VOS_HTONS ((stRtMsg).usZoneID); \
    (stRtMsg).ulIfIndex = VOS_HTONL ((stRtMsg).ulIfIndex); \
    (stRtMsg).ulATIndex= VOS_HTONL ((stRtMsg).ulATIndex); \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (stRtMsg).ulLabel = VOS_HTONL ((stRtMsg).ulLabel); \
    (stRtMsg).ulToken= VOS_HTONL ((stRtMsg).ulToken); \
    FIB6_ADDRESS_HTON ((stRtMsg).aulOldNexthop)   \
    FIB6_ADDRESS_HTON ((stRtMsg).aulOldNexthop_Relay)  \
    (stRtMsg).ulOldIfIndex = VOS_HTONL ((stRtMsg).ulOldIfIndex); \
    (stRtMsg).ulOldATIndex= VOS_HTONL ((stRtMsg).ulOldATIndex); \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (stRtMsg).ulOldLabel = VOS_HTONL ((stRtMsg).ulOldLabel); \
    (stRtMsg).ulOldToken= VOS_HTONL ((stRtMsg).ulOldToken); \
}

#define RT_MSG4_HTON(stRtMsg) \
{\
    (stRtMsg).ulDestination = VOS_HTONL((stRtMsg).ulDestination);  \
    (stRtMsg).ulNexthop = VOS_HTONL((stRtMsg).ulNexthop);   \
    (stRtMsg).usType = (USHORT)VOS_HTONS ((stRtMsg).usType); \
    (stRtMsg).usZoneID = (USHORT)VOS_HTONS ((stRtMsg).usZoneID); \
    (stRtMsg).ulIfIndex = VOS_HTONL ((stRtMsg).ulIfIndex); \
    (stRtMsg).ulATIndex= VOS_HTONL ((stRtMsg).ulATIndex); \
}


#define RT6_CMD_HTON(stRtCmd) \
{\
    (stRtCmd).ulRtcmd_Group = VOS_HTONL ((stRtCmd).ulRtcmd_Group); \
    if(FIB_IPV6_MSG == (stRtCmd).ulVer)\
    {\
        RT_MSG6_HTON ((stRtCmd).stRtcmd.stRtcmd_RtMsg); \
    }\
    else\
    {\
        RT_MSG4_HTON ((stRtCmd).stRtcmd.stRtcmd4_RtMsg); \
    }\
}

/* Defect 5784 Guru 22nd Dec 2003 - removed Nexthop relay copy for 6to4;
Defect 8715 Guru 26 Feb 2004 - modified to check port type only in main board,
and overwrite the relay nexthop  so that IO board gets correct next hop,
updated for defect 7034; Guru, 1-03-04,
updated for defect 8844; Guru, 2-03-04, added NULL check for for ifnet */
#define FIB6_COPY_RTMSG_TO_RTENTRY(pstRtEntry, pstRtMsg) \
{ \
    FIB6_ADDRESS_COPY( (pstRtEntry)->aulRt_Dest, (pstRtMsg)->aulDestination ); \
    (pstRtEntry)->ulRt_Dest_PrefLen = (ULONG) ((pstRtMsg)->ucDestPrefixLength); \
    (pstRtEntry)->ulRt_Flags = (pstRtMsg)->ulFlags; \
    (pstRtEntry)->ulRt_Slot = (pstRtMsg)->ulSlot; \
    \
\
    { \
        if ( FIB6_IS_ADDRESS_6To4((pstRtMsg)->aulNexthop) && \
             (getSelfBoardId () == getMainboardId ()) && \
             (NULL != IF_GetIfByIndex ( (pstRtMsg)->ulIfIndex)) && \
             (PORT_TUNNEL == IF_GETLINKTYPE ((pstRtMsg)->ulIfIndex)))  \
        { \
            FIB6_ADDRESS_COPY(  (pstRtEntry)->aulRt_Nexthop, (pstRtMsg)->aulNexthop); \
            FIB6_ADDRESS_COPY((pstRtMsg)->aulNexthop_Relay, (pstRtEntry)->aulRt_Nexthop); \
        } \
        else \
        { \
            if (FIB6_IS_ADDRESS_NULL((pstRtMsg)->aulNexthop_Relay)) \
            { \
                FIB6_ADDRESS_COPY(  (pstRtEntry)->aulRt_Nexthop, (pstRtMsg)->aulNexthop) ;\
            } \
            else \
            { \
                FIB6_ADDRESS_COPY(  (pstRtEntry)->aulRt_Nexthop, (pstRtMsg)->aulNexthop_Relay) ;\
                /* below assignment added for BYAD09878; by Guru; 03-05-2004 */ \
                (pstRtEntry)->ulRt_Flags |= FIB6_RTF_RELAY; \
            } \
        } \
        (pstRtEntry)->ulRt_IfIndex = (pstRtMsg)->ulIfIndex; \
        (pstRtEntry)->ulRt_ATIndex = (pstRtMsg)->ulATIndex; \
        /* Guru: Added for 6PE implementation 26th Mar'04 */\
        (pstRtEntry)->ulLabel = (pstRtMsg)->ulLabel; \
        (pstRtEntry)->ulToken = (pstRtMsg)->ulToken; \
        (pstRtEntry)->ulProto = (pstRtMsg)->ulProto; \
        /*Add by h55555 for defect BC3D00951 interface name*/\
        (VOID)TCPIP_Mem_Copy((pstRtEntry)->ucIfName,MAX_IF_NAME_LENGTH + 1,(pstRtMsg)->ucIfName,MAX_IF_NAME_LENGTH + 1);\
\
\
        (pstRtEntry)->ulRtPri = (pstRtMsg)->usRtPri;\
\
\
        (pstRtEntry)->ulVrfIndex = (pstRtMsg)->usZoneID;\
\
    }\
}

#define FIB4_COPY_RTMSG_TO_RTENTRY(  pstRtEntry, pstRtMsg) \
{ \
    (pstRtEntry)->ulRt_Dest = (pstRtMsg)->ulDestination ; \
    (pstRtEntry)->ulRt_Nexthop = (pstRtMsg)->ulNexthop ;\
    (pstRtEntry)->ulRt_Dest_PrefLen = (ULONG) ((pstRtMsg)->ucDestPrefixLength); \
    (pstRtEntry)->ulRt_Flags = (pstRtMsg)->ulFlags; \
    (pstRtEntry)->ulRt_IfIndex = (pstRtMsg)->ulIfIndex; \
    (pstRtEntry)->ulRt_ATIndex = (pstRtMsg)->ulATIndex; \
    (pstRtEntry)->ulRt_Slot = (pstRtMsg)->ulSlot; \
\
    (pstRtEntry)->ulRt_Loc = (pstRtMsg)->ulLocalAddress;\
    (pstRtEntry)->ulRt_Loc_PrefLen = (ULONG)((pstRtMsg)->ucLocalPrefixLength);\
    (pstRtEntry)->ulRTPri = (pstRtMsg)->usRTPri;\
    (pstRtEntry)->ulRt_Proto = (pstRtMsg)->ulProto;\
    /*Add by h55555 for defect BC3D00951 interface name*/\
    (VOID)TCPIP_Mem_Copy((pstRtEntry)->ucIfName,MAX_IF_NAME_LENGTH + 1,(pstRtMsg)->ucIfName,MAX_IF_NAME_LENGTH + 1);\
\
\
    (pstRtEntry)->ulPmtu = (pstRtMsg)->ulPmtu;\
\
    /*Add by q62011 for 大规格地址查询速度慢*/\
    (pstRtEntry)->ulRt_Loc_If = (pstRtMsg)->ulLocalIfIndex;\
\
}

/* Begin: Interface priority, chandra, 2012-12-26 */
#define FIB4_COPY_ROUTE4_TO_RTMSG(pstRtEntry, stRtMsg) \
{ \
    stRtMsg.ulDestination = (pstRtEntry)->ulRt_Dest; \
    stRtMsg.ulNexthop      = (pstRtEntry)->ulRt_Nexthop;\
    stRtMsg.ucDestPrefixLength = (UCHAR)((pstRtEntry)->ulRt_Dest_PrefLen); \
    stRtMsg.ulFlags   = (pstRtEntry)->ulRt_Flags; \
    stRtMsg.ulIfIndex = (pstRtEntry)->ulRt_IfIndex; \
    stRtMsg.ulATIndex = (pstRtEntry)->ulRt_ATIndex; \
    stRtMsg.ulSlot    = (pstRtEntry)->ulRt_Slot; \
    stRtMsg.ulLocalAddress = (pstRtEntry)->ulRt_Loc; \
    stRtMsg.ucLocalPrefixLength = (UCHAR)((pstRtEntry)->ulRt_Loc_PrefLen);\
    stRtMsg.usRTPri = (USHORT)((pstRtEntry)->ulRTPri);\
    stRtMsg.ulProto = (pstRtEntry)->ulRt_Proto;\
   (VOID)TCPIP_Mem_Copy((stRtMsg.ucIfName),MAX_IF_NAME_LENGTH + 1,(pstRtEntry)->ucIfName,MAX_IF_NAME_LENGTH + 1);\
}
/* End: Interface priority, chandra, 2012-12-26 */

/* Defect 5784 Guru 22nd Dec 2003 - removed Nexthop relay copy for 6to4;
Defect 8715 Guru 26 Feb 2004 - modified to check port type only in main board,
and overwrite the relay nexthop  so that IO board gets correct next hop,
updated for defect 8844; Guru, 2-03-04, added NULL check for for ifnet */
#define FIB6_COPY_RTMSG_TO_ROUTE6(pstRoute6, pstRtMsg)\
{\
    (pstRoute6)->usZoneID = (pstRtMsg)->usZoneID; \
    FIB6_ADDRESS_COPY(   (pstRoute6)->aulDestination, (pstRtMsg)->aulDestination); \
    FIB6_ADDRESS_COPY(   (pstRoute6)->aulLocalAddress, (pstRtMsg)->aulLocalAddress); \
    if ( FIB6_IS_ADDRESS_6To4((pstRtMsg)->aulNexthop) && \
        (getSelfBoardId () == getMainboardId ()) && \
        (NULL != IF_GetIfByIndex ( (pstRtMsg)->ulIfIndex)) && \
        (PORT_TUNNEL == IF_GETLINKTYPE ((pstRtMsg)->ulIfIndex))) \
    { \
        FIB6_ADDRESS_COPY(  (pstRoute6)->aulNexthop, (pstRtMsg)->aulNexthop) ; \
        FIB6_ADDRESS_COPY((pstRtMsg)->aulNexthop_Relay, (pstRoute6)->aulNexthop); \
    } \
    else \
    { \
        if (FIB6_IS_ADDRESS_NULL((pstRtMsg)->aulNexthop_Relay)) \
        { \
            FIB6_ADDRESS_COPY(  (pstRoute6)->aulNexthop, (pstRtMsg)->aulNexthop) ;\
        } \
        else \
        { \
            FIB6_ADDRESS_COPY(  (pstRoute6)->aulNexthop, (pstRtMsg)->aulNexthop_Relay) ;\
        } \
    } \
    (pstRoute6)->ucDestPrefixLength = (pstRtMsg)->ucDestPrefixLength; \
    (pstRoute6)->ucLocalPrefixLength = (pstRtMsg)->ucLocalPrefixLength; \
    (pstRoute6)->ulFlags = (pstRtMsg)->ulFlags; \
    (pstRoute6)->ulIfIndex = (pstRtMsg)->ulIfIndex; \
    (pstRoute6)->ulATIndex = (pstRtMsg)->ulATIndex; \
    (pstRoute6)->ulSlot = (pstRtMsg)->ulSlot; \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (pstRoute6)->ulLabel = (pstRtMsg)->ulLabel; \
    (pstRoute6)->ulToken = (pstRtMsg)->ulToken; \
}

#define FIB6_COPY_ROUTE6_TO_RTMSG(pstRtMsg, pstRoute6) \
{\
    (pstRtMsg)->usZoneID = (USHORT)((pstRoute6)->ulVrfIndex); \
    FIB6_ADDRESS_COPY( (pstRtMsg)->aulDestination, (pstRoute6)->aulRt_Dest); \
    FIB6_ADDRESS_COPY(  (pstRtMsg)->aulNexthop, (pstRoute6)->aulRt_Nexthop); \
    FIB6_ADDRESS_COPY(  (pstRtMsg)->aulNexthop_Relay, (pstRoute6)->aulRt_Nexthop); \
    (pstRtMsg)->ucDestPrefixLength = (pstRoute6)->ulRt_Dest_PrefLen; \
    (pstRtMsg)->ulFlags = (pstRoute6)->ulRt_Flags; \
    (pstRtMsg)->ulIfIndex = (pstRoute6)->ulRt_IfIndex; \
    (pstRtMsg)->ulATIndex= (pstRoute6)->ulRt_ATIndex; \
    (pstRtMsg)->ulSlot = (pstRoute6)->ulRt_Slot; \
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (pstRtMsg)->ulLabel= (pstRoute6)->ulLabel; \
    (pstRtMsg)->ulToken = (pstRoute6)->ulToken; \
    (pstRtMsg)->ulProto = (pstRoute6)->ulProto; \
    (pstRtMsg)->usRtPri = (USHORT)((pstRoute6)->ulRtPri); \
    (VOID)TCPIP_Mem_Copy((pstRtMsg)->ucIfName,MAX_IF_NAME_LENGTH + 1,(pstRoute6)->ucIfName,MAX_IF_NAME_LENGTH + 1); \
}

#define FIB6_COPY_RTENTRY_TO_ROUTE6(  pstRoute6, pstRtEntry)\
{\
    FIB6_ADDRESS_COPY((pstRoute6)->aulDestination, (pstRtEntry)->aulRt_Dest);\
    FIB6_ADDRESS_COPY((pstRoute6)->aulNexthop, (pstRtEntry)->aulRt_Nexthop);\
    (pstRoute6)->ulIfIndex =  (pstRtEntry)->ulRt_IfIndex;\
    (pstRoute6)->ulATIndex = (pstRtEntry)->ulRt_ATIndex;\
    (pstRoute6)->ulSlot =       (pstRtEntry)->ulRt_Slot;\
    (pstRoute6)->ucDestPrefixLength = (UCHAR)(pstRtEntry->ulRt_Dest_PrefLen);\
    (pstRoute6)->ulFlags = (pstRtEntry)->ulRt_Flags;\
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (pstRoute6)->ulLabel =  (pstRtEntry)->ulLabel;\
    (pstRoute6)->ulToken = (pstRtEntry)->ulToken;\
    (pstRoute6)->usZoneID = FIB6_DEF_ZONEID;\
\
    (pstRoute6)->ulRtPri = (pstRtEntry)->ulRtPri;\
\
}

#define FIB4_COPY_RTENTRY_TO_ROUTE4(  pstRoute4, pstRtEntry)\
{\
    (pstRoute4)->ulDestination = (pstRtEntry)->ulRt_Dest;\
    (pstRoute4)->ulNexthop = (pstRtEntry)->ulRt_Nexthop;\
    (pstRoute4)->ulIfIndex =  (pstRtEntry)->ulRt_IfIndex;\
    (pstRoute4)->ulATIndex = (pstRtEntry)->ulRt_ATIndex;\
    (pstRoute4)->ulSlot =       (pstRtEntry)->ulRt_Slot;\
    (pstRoute4)->ucDestPrefixLength = (UCHAR)(pstRtEntry->ulRt_Dest_PrefLen);\
    (pstRoute4)->ulFlags = (pstRtEntry)->ulRt_Flags;\
\
    (pstRoute4)->ulLocalAddress = (pstRtEntry)->ulRt_Loc;\
    (pstRoute4)->ucLocalPrefixLength = (UCHAR)(pstRtEntry)->ulRt_Loc_PrefLen;\
    (pstRoute4)->usRTPri = (USHORT)((pstRtEntry)->ulRTPri);\
\
    (pstRoute4)->ulPmtu = (pstRtEntry)->ulPmtu;\
\
}


#define FIB6_COPY_RTENTRY_TO_RTMSG( pstBalRtMsg, pstRtEntry)\
{\
    FIB6_ADDRESS_COPY( (pstBalRtMsg)->aulDestination, (pstRtEntry)->aulRt_Dest );\
    FIB6_ADDRESS_COPY( (pstBalRtMsg)->aulNexthop, (pstRtEntry)->aulRt_Nexthop);\
    FIB6_ADDRESS_COPY( (pstBalRtMsg)->aulNexthop_Relay, (pstRtEntry)->aulRt_Nexthop);\
    (pstBalRtMsg)->ulIfIndex = (pstRtEntry)->ulRt_IfIndex;\
    (pstBalRtMsg)->ulATIndex = (pstRtEntry)->ulRt_ATIndex;\
    (pstBalRtMsg)->ulSlot = (pstRtEntry)->ulRt_Slot;\
    (pstBalRtMsg)->ucDestPrefixLength = (UCHAR) ((pstRtEntry)->ulRt_Dest_PrefLen);\
    (pstBalRtMsg)->ulFlags = ((pstRtEntry)->ulRt_Flags);\
    /* Guru: Added for 6PE implementation 26th Mar'04 */\
    (pstBalRtMsg)->ulLabel = (pstRtEntry)->ulLabel;\
    (pstBalRtMsg)->ulToken = (pstRtEntry)->ulToken;\
    (pstBalRtMsg)->usZoneID = (USHORT)((pstRtEntry)->ulVrf6Index);\
\
    (pstBalRtMsg)->usRtPri = (USHORT)(pstRtEntry)->ulRtPri;\
\
    (VOID)TCPIP_Mem_Copy((pstBalRtMsg)->ucIfName,MAX_IF_NAME_LENGTH + 1,(pstRtEntry)->szRt_OutIfName,MAX_IF_NAME_LENGTH + 1);\
 }

#define FIB4_COPY_RTENTRY_TO_RTMSG( pstBalRtMsg, pstRtEntry)\
{\
    (pstBalRtMsg)->ulDestination = (pstRtEntry)->ulRt_Dest ;\
    (pstBalRtMsg)->ulNexthop = (pstRtEntry)->ulRt_Nexthop;\
    (pstBalRtMsg)->ulIfIndex = (pstRtEntry)->ulRt_IfIndex;\
    (pstBalRtMsg)->ulATIndex = (pstRtEntry)->ulRt_ATIndex;\
    (pstBalRtMsg)->ulSlot = (pstRtEntry)->ulRt_Slot;\
    (pstBalRtMsg)->ucDestPrefixLength = (UCHAR) ((pstRtEntry)->ulRt_Dest_PrefLen);\
    (pstBalRtMsg)->ulFlags = ((pstRtEntry)->ulRt_Flags);\
    (pstBalRtMsg)->ulLocalAddress = (pstRtEntry)->ulRt_Loc ;\
    (pstBalRtMsg)->ucLocalPrefixLength = (UCHAR) ((pstRtEntry)->ulRt_Loc_PrefLen);\
    (pstBalRtMsg)->usRTPri = (pstRtEntry)->usRTPri;\
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */\
    (pstBalRtMsg)->usZoneID = (USHORT)(pstRtEntry)->ulVrfIndex;\
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */\
\
    (pstBalRtMsg)->ulPmtu = (pstRtEntry)->ulPmtu;\
\
    (VOID)TCPIP_Mem_Copy((pstBalRtMsg)->ucIfName,MAX_IF_NAME_LENGTH + 1,(pstRtEntry)->szRt_OutIfName,MAX_IF_NAME_LENGTH + 1);\
}


#endif

#ifdef  __cplusplus
}
#endif

