
#ifndef _IP6_PMTU_DEF_H
#define _IP6_PMTU_DEF_H

#ifdef  __cplusplus
extern "C"{
#endif


/****************************************************

                IPB IR HEADER FILES

 1. MBUF

*****************************************************/

/* Core's Systrace related stuff.*/
#define IP6_PMTU_CORE_CACHE ((SYSTRC_IPV6_PMTU_BASE << 8) + 001)
#define IP6_PMTU_CORE_FUN ((SYSTRC_IPV6_PMTU_BASE << 8) + 002)
#define IP6_PMTU_CORE_HA ((SYSTRC_IPV6_PMTU_BASE << 8) + 003)
#define IP6_PMTU_CORE_ICMP_PROCESS ((SYSTRC_IPV6_PMTU_BASE << 8) + 004)
#define IP6_PMTU_CORE_SSA ((SYSTRC_IPV6_PMTU_BASE << 8) + 005)
#define IP6_PMTU_CORE_CFG ((SYSTRC_IPV6_PMTU_BASE << 8) + 006)
#define IP6_PMTU_CORE_INIT ((SYSTRC_IPV6_PMTU_BASE << 8) + 007)


#define MAX_BUCKET 1024
#define MAX_CACHE_TIME 10

/* PN:AC4D01307 , moved to public header file.*/

/* IP6_PMTU_MALLOC will be used in PMTU module, only when this
   allocated memory will be used and freed inside PMTU module.
   Similarly, IP6_PMTU_FREE will be used in PMTU module, only
   when the corresponding memory is allocated by PMTU module.
   If the pointer 'ptr' is NULL, then print an assert for
   debugging the bad pointer.*/
#define IP6_PMTU_MALLOC(ulInfo, ulSize)  TCPIP_Malloc((ulInfo), (ulSize))
#define IP6_PMTU_FREE(ptr)\
{\
    if (NULL != (ptr))\
    {\
        (VOID)TCPIP_Free(ptr);\
        (ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}

#define USER_INFO             0
#define SID_IP6_PMTU_MAKECONT 0x10
#define MAX_IPC_MSG           100
#define PMTU_MAX_SOCKET       50
#ifndef IPPROTO_TCP
#define IPPROTO_TCP           0x6         /* TCP protocol */
#endif

#ifndef IPPROTO_UDP
#define IPPROTO_UDP           0x11        /* UDP protocol */
#endif

#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif


/* usmessage type.*/
#define TOO_BIG_INFO_MSG     0
#define INC_ACCESS_COUNT_MSG 1
#define CHANGE_MTU_MSG       2
#define ADD_PMTU_SBY_MSG     5
#define MFY_PMTU_SBY_MSG     7
#define MFY_GAGETIME_SBY_MSG 9

#define PMTU_CHANGED 1

/* ulEvents */
#define ADD 1
#define DEL 2


/* LISTS for search/ADD/Delete nodes.*/
/* In case of MINDEX_LIST it will add/delete/search a mindex node to
   dll of mindex node.*/
#define MINDEX_LIST 1

/* In case of SOCKET_LIST it will add/delete/search a socket node to dll
   of socket node corresponding to a destination address.*/
#define SOCKET_LIST 2

/* In case of SOCKET_ID_LIST it will add/delete/search a socket identity node
   to dll of socket identity.*/
#define SOCKET_ID_LIST 3

/* In case of DA_LIST it will add/delete/search a DA node to dll of DA
   node corresponding to a socket identity node.*/
#define DA_LIST 4

/* Control Flags */
/* Begin : Defect ID: BYAD011724,
   Reason : To remove unnecessary code.*/

#define CLI_Control 1

/* This is for ulflag value in IP6_PMTU_ModifyEntry ().*/
#define SOCKET_UNREG 1
#define SOCKET_REG   0
#define PMTU_SOC_EVOKING 1

/* Messages in IO board to sync the data.*/
#define BATCH_DATA_MSG   4
#define ADD_PMTU_MSG     5
#define DEL_PMTU_MSG     6
#define MFY_PMTU_MSG     7
#define DALL_PMTU_MSG    8
#define BITMAP_MSG       9

#define DALL_STATIC_PMTU  10
#define DALL_DYNAMIC_PMTU 11


#define MAX_USERINFO_BITLEN  0
#define ONE_MIN_TIMER        (1 * 60 * 1000)
#define PMTU_CHAR_BUF_50     50

#define PMTU_BITS_PER_BYTE      8
#define PMTU_SEVENTH_BIT_SET    0x80
#define PMTU_SECONDS_PER_MINUTE 60
#define PMTU_BYTES_NEEDED_TO_STORE(val)   (((val) + 7) / 8)   /* PN:AC4D01274*/

/* This is used in Search part.*/
#define IP6_PMTU_AddressHash(FAddr, ulZoneid) \
            (((((FAddr)->s6_addr32[0]) ^ ((FAddr)->s6_addr32[1]) ^ \
  ((FAddr)->s6_addr32[2]) ^ ((FAddr)->s6_addr32[3])) \
  + (ulZoneid)) % MAX_BUCKET)

/* for ICMP INPUT process.*/
#define IP6_ULHDR_GET(m, val, type, off, len, mid, ret) \
{ \
    IPB_IR_MBUF_MAKE_MEMORY_CONTINUOUS((m), (off) + (len), (mid), (ret)); \
    if (0 == (ret)) \
    { \
        (val) = (type)(IPB_IR_MBUF_MTOD((m), UCHAR*) + (off)); \
    } \
}

/* For hash formula use pstDA, ulZoneid as input and make sure hash key
   falls in range 0 to (MAX_BUCKET- 1). This hash key is used as index to
   Search Part.
   Defect id : BYAD02691
   T***et to Quidway router gives exception in T***et Server.*/

#define IP6_PMTU_SocketHash(lSockid, ulTaskid) \
    (((ULONG)(lSockid) ^ (ulTaskid)) % MAX_BUCKET)

/* For converting the address from Host to Network byte order.*/
#define PMTU_IPV6ADDRHTON(aulAddr) \
    (aulAddr).s6_addr32[0] = VOS_HTONL ((aulAddr).s6_addr32[0]); \
    (aulAddr).s6_addr32[1] = VOS_HTONL ((aulAddr).s6_addr32[1]); \
    (aulAddr).s6_addr32[2] = VOS_HTONL ((aulAddr).s6_addr32[2]); \
    (aulAddr).s6_addr32[3] = VOS_HTONL ((aulAddr).s6_addr32[3]);


/* For converting the address from Network to Host order.*/
#define PMTU_IPV6ADDRNTOH(aulAddr) \
    (aulAddr).s6_addr32[0] = VOS_NTOHL ((aulAddr).s6_addr32[0]); \
    (aulAddr).s6_addr32[1] = VOS_NTOHL ((aulAddr).s6_addr32[1]); \
    (aulAddr).s6_addr32[2] = VOS_NTOHL ((aulAddr).s6_addr32[2]); \
    (aulAddr).s6_addr32[3] = VOS_NTOHL ((aulAddr).s6_addr32[3]);

#define IP6_PMTU_CORE_LOG   (VOID) g_stShellCallBack.pfIP6_Pmtu_SH_LogToIPOSIC

#define IP6_PMTU_CORE_DEBUG \
                    (VOID)g_stShellDebugCallBackup.pfIP6_Pmtu_SH_DbgToIPOSIC

/* Range for age value.*/
#define PMTU_MIN_AGE_TIME           10
#define PMTU_MAX_AGE_TIME           100

/* PAF value for Total PMTU entries */
#define PMTU_PAF_TOTAL_ENTRIES_MAX      g_stIP6_PMTU_TotalResSpecVal.ulMax_Value
#define PMTU_PAF_TOTAL_ENTRIES_MIN      g_stIP6_PMTU_TotalResSpecVal.ulMin_Value
#define PMTU_PAF_TOTAL_ENTRIES_AVAIL    g_stIP6_PMTU_TotalResSpecVal.ulAvail_Value

/* PAF value for Static PMTU entries */
#define PMTU_PAF_STATIC_ENTRIES_MAX     g_stIP6_PMTU_StaticResSpecVal.ulMax_Value
#define PMTU_PAF_STATIC_ENTRIES_MIN     g_stIP6_PMTU_StaticResSpecVal.ulMin_Value
#define PMTU_PAF_STATIC_ENTRIES_AVAIL   g_stIP6_PMTU_StaticResSpecVal.ulAvail_Value



/* Added by nagesh for VISP Log FrameWork change */
#define IP6_NULL_LOGID 0
#define IP6_NULL_PARA  0

typedef VOID  (*pfConvFunc)(VOID *);

/* Macro for unused variables */
#define PMTU_NOUSE(m_vVar)    (VOID)(m_vVar)

/* Added by Anand - V1R7 Workspace Integration */
#define PMTU_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
#define IP6_NP_FLAG_PMTU_RESETSTATICENTRY  0x1
#define IP6_NP_FLAG_PMTU_RESETDYNAMICENTRY 0x2
#define IP6_PMTU_NOTIFY_NP(ulOper, pvPMTUInfo) \
    ((g_pfIP6_PMTU_PPIOperation)?IP6_PMTU_Notify_PPI(ulOper, pvPMTUInfo) : VOS_OK)
#define IP6_PMTU_FLAG_ISSET(flag) \
                        (g_ucPMTUFlag & (flag))
#define IP6_PMTU_FLAG_SET(flag) \
                        (g_ucPMTUFlag |= (flag))
#define IP6_PMTU_FLAG_RESET(flag) \
                        (g_ucPMTUFlag &= (~(flag)))
#else
#define IP6_PMTU_NOTIFY_NP(ulOper, pvPMTUInfo)     VOS_OK
#define IP6_PMTU_FLAG_ISSET(flag)                  0
#define IP6_PMTU_FLAG_SET(flag)                    VOS_OK
#define IP6_PMTU_FLAG_RESET(flag)                  VOS_OK
#endif


#ifdef  __cplusplus
}
#endif

#endif

