

#ifndef _ADDR_DEF_H_
#define _ADDR_DEF_H_


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/* To output information for testing  */
#define ADDRMNG_TEST 0

#define IN6MASK0  {{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}}
#define IN6MASK32 {{{ 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, \
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6MASK64 {{{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, \
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6MASK96 {{{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, \
                       0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6MASK128 {{{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, \
                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }}}

#define IN6MASK_LINKLOCAL {{{ 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}

#define IN6PREFIXLEN_LINKLOCAL 10

/*w39533 2004-11-08 sync D24*/
/* Begin : Defect ID: D01006,     Modifier:Rajesh,   Date:2004/9/13
         Reason   : Get negotiated Mtu from I/O Board*/
#define  IP6_ADDR_GET_NEGMTU  10

#define  IP6_OWN                 1
#define  IP6_NEGOTIATE           2
#define  IP6_BORROW              4
#define  IP6_LEND                8

#define  IP6_ADDRLIST_INTERFACE      0
#define  IP6_ADDRLIST_GLOBAL         1

#define  IP6_DOCONFLICT_WITHPREFIX       1
#define  IP6_DOCONFLICT_WITHOUTPREFIX    0

#define  IP6_NOLINKLOCAL              0
#define  IP6_LINKLOCAL_TENTATIVE      1
#define  IP6_LINKLOCAL_NOTENTATIVE    2

#define V6_LIST_EMPTY(m_pstPtr)  ((m_pstPtr)->ia6_v_pNext == (m_pstPtr))
#define V6_LIST_LAST(m_pstPtr)   ((m_pstPtr)->ia6_v_pPrev)
#define V6_LIST_SCAN(m_pstHead, m_pstNode) \
    for ((m_pstNode) = V6_LIST_FIRST((m_pstHead)); (m_pstNode) != (m_pstHead);\
        (m_pstNode) = V6_LIST_NEXT((m_pstNode)))

#define H6_LIST_EMPTY(m_pstPtr)  ((m_pstPtr)->ia6_h_pNext == (m_pstPtr))
#define H6_LIST_FIRST(m_pstPtr)  ((m_pstPtr)->ia6_h_pNext)
#define H6_LIST_NEXT(m_pstPtr)   ((m_pstPtr)->ia6_h_pNext)
#define H6_LIST_LAST(m_pstPtr)   ((m_pstPtr)->ia6_h_pPrev)
#define H6_LIST_SCAN(m_pstHead, m_pstNode) \
    for ((m_pstNode) = H6_LIST_FIRST((m_pstHead)); (m_pstNode) != (m_pstHead);\
        (m_pstNode) = H6_LIST_NEXT((m_pstNode)))

/* Macros defined for systrace implementation. Each macro defines a file ID */
#define IP6_ADDR_MGT_C    ((SYSTRC_IPV6_ADDR_BASE << 8) + 010)
#define IP6_ADDR_INIT_C    ((SYSTRC_IPV6_ADDR_BASE << 8) + 011)
#define IP6_ADDR_MAIN_CORE_C    ((SYSTRC_IPV6_ADDR_BASE << 8) + 012)
#define IP6_ADDR_CFG_C    ((SYSTRC_IPV6_ADDR_BASE << 8) + 013)

#define IP6_ADDR_LINK_LOCAL            8000
#define IP6_ADDR_GLOBAL                8001
#define IP6_ADDR_RPC_CALL              9000
#define IP6_ADDR_ADD_ADDR              5000
#define IP6_ADDR_DEL_ADDR              5001
#define IP6_ADDR_RM_ADD_ADDR           5002
#define IP6_ADDR_RM_DEL_ADDR           5003
#define IP6_ADDR_RM_CREATE_INT         5004
#define IP6_ADDR_RM_DEL_INT            5005
#define IP6_ADDR_ND_START_DAD          5006
#define IP6_ADDR_ND_STOP_DAD           5007
#define IP6_ADDR_ND_ADD_ADDR           5008
#define IP6_ADDR_ND_DEL_ADDR           5009
#define IP6_ADDR_ND_ADD_PFX            5010
#define IP6_ADDR_ND_DEL_PFX            5011
#define IP6_ADDR_AUTO_CFG_LLA          5012
#define IP6_ADDR_DEL_LLA               5013
#define IP6_ADDR_IF_STATUS_UP          5014
#define IP6_ADDR_IF_STATUS_DOWN        5015
#define IP6_ADDR_PHY_NOTIFY            5016
#define IP6_ADDR_LLC_NOTIFY            5017
#define IP6_ADDR_ND_DAD2MAIN           5018

/* Sachin :- As earlier it was always compared to VOS_OK, which was very
  ambiguous */
#define IP6_ADDR_NOT_TUNNEL    0x0
#define IP6_ADDR_CONFIG_NO     0x0
#define IP6_ADDR_CONFIG_ONE    0x1
#define IP6_ADDR_ADD           0x0
#define IP6_ADDR_DEL           0x1

/*Tunnel Interface defination*/
#define IP6_TUNNEL_MODE_GRE               TUNNEL_MODE_GRE
#define IP6_TUNNEL_MODE_IPV6IP_CONFIG     TUNNEL_MODE_IPV6IP_CONFIG
#define IP6_TUNNEL_MODE_IPV6IP_AUTO       TUNNEL_MODE_IPV6IP_AUTO

/* Delay during address configuration 1000 ms */
#define IP6_ADDR_PPPDELAY             1000 /*Time increased to 1 sec as still
                      this time out was less for EUI address add , BYAD09001*/
#define IP6_ADDR_REFCOUNTDELAY        5000

#define IP6_ADDR_DISPLAY    IP6_ADDR6_Core_Log_Text


/* Macro to LOG Error Codes of IP6 Module*/
/*Check the flags in core itself. so that shell need not call core for getting
  the flags*/
#define IP6_ADDR_DISPLAY_0(m_ulLevel, m_str) \
{\
    if ((VOS_TRUE == g_ulIP6LoggerSwitch) \
        && ((IP6_LEVEL_ALL == g_ulIP6LogLevel) \
        || (m_ulLevel == g_ulIP6LogLevel))) \
    {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "m_str"\n",\
                                              IPB_IR_IF_GETSELFBOARDID());\
    }\
}

#define IP6_ADDR_DISPLAY_1(m_ulLevel, m_str, m_arg1) \
{\
    if ((VOS_TRUE == g_ulIP6LoggerSwitch) \
        && ((IP6_LEVEL_ALL == g_ulIP6LogLevel) \
        || (m_ulLevel == g_ulIP6LogLevel))) \
    {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "m_str"\n",\
                                        IPB_IR_IF_GETSELFBOARDID(), m_arg1);\
    }\
}

#define IP6_ADDR_DISPLAY_2(m_ulLevel, m_str, m_arg1, m_arg2) \
{\
    if ((VOS_TRUE == g_ulIP6LoggerSwitch) \
        && ((IP6_LEVEL_ALL == g_ulIP6LogLevel) \
        || (m_ulLevel == g_ulIP6LogLevel))) \
    {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "m_str"\n",\
                                 IPB_IR_IF_GETSELFBOARDID(), m_arg1, m_arg2);\
    }\
}

#define IP6_ADDR_DISPLAY_3(m_ulLevel, m_str, m_arg1, m_arg2, m_arg3) \
{\
    if ((VOS_TRUE == g_ulIP6LoggerSwitch) \
        && ((IP6_LEVEL_ALL == g_ulIP6LogLevel) \
        || (m_ulLevel == g_ulIP6LogLevel))) \
    {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "m_str"\n",\
                         IPB_IR_IF_GETSELFBOARDID(),  m_arg1, m_arg2, m_arg3);\
    }\
}

#define IP6_ADDR_DISPLAY_4(m_ulLevel, m_str, m_arg1, m_arg2, m_arg3, m_arg4) \
{\
    if ((VOS_TRUE == g_ulIP6LoggerSwitch) \
        && ((IP6_LEVEL_ALL == g_ulIP6LogLevel) \
        || (m_ulLevel == g_ulIP6LogLevel))) \
    {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "m_str"\n",\
                   IPB_IR_IF_GETSELFBOARDID(), m_arg1, m_arg2, m_arg3, m_arg4);\
    }\
}

#define IP6_ADDR_DISPLAY_5(m_ulLevel, m_str, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5) \
{\
    if ((VOS_TRUE == g_ulIP6LoggerSwitch) \
        && ((IP6_LEVEL_ALL == g_ulIP6LogLevel) \
        || (m_ulLevel == g_ulIP6LogLevel))) \
    {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "m_str"\n",\
            IPB_IR_IF_GETSELFBOARDID(), m_arg1, m_arg2, m_arg3, m_arg4, m_arg5);\
    }\
}



#define IP6_ADDR_DEFAULT_PUBLIC_INSTANCE    0     /* Used to fill the instance
                                     id while sending the IP6 message to RM */

/*For PPP interface to send the configuration flag*/
#define IP6_ADDR_MANUAL_CONFIG   0x02
#define IP6_ADDR_AUTO_CONFIG     0x01

#define IP6_ADDR_NO_CONFIG       0x00

#define IP6_ADDR_PRELEN_LLA    10
#define IP6_ADDR_PRELEN_SLA    10
#define IP6_ADDR_PRELEN_MAX    128
#define IP6_ADDR_PRELEN_MIN    1
#define IP6_ADDR_PRELEN_EUI    64

#define IP6_ADDR_NOTIFY_RM(m_pstIp6IfAddr) ((m_pstIp6IfAddr)->ucNotifyRM)

/*Anycast now is not supported therfore always fault*/
/*Address status is relevent only for host*/

#define IP6_ADDR_FILLADDRENTRY(m_pstInOutMIBAddrTbl, m_pstIp6IfAddr, m_pIp6IfNet)\
{\
    (VOID)TCPIP_Mem_Copy((VOID *)&((m_pstInOutMIBAddrTbl)->stIPv6Addr), sizeof(IN6ADDR_S),\
                 (VOID *)&((m_pstIp6IfAddr)->ia6_stAddr), sizeof(IN6ADDR_S));\
    (m_pstInOutMIBAddrTbl)->ulAnyCastFlag   =   IPv6_ANYCAST_FALSE;\
    (m_pstInOutMIBAddrTbl)->ulAddrStatus    =   IPv6_STATUS_PREFERRED;\
    if (((m_pIp6IfNet)->ip6if_ulAddrFlag & IP6_MANUAL_LINKLOCAL) \
                 || ((m_pIp6IfNet)->ip6if_ulAddrFlag & IP6_OWN))\
    {\
        (m_pstInOutMIBAddrTbl)->ulAddrType = IPv6_ADDR_STATEFUL;\
    }\
    else\
    {\
        (m_pstInOutMIBAddrTbl)->ulAddrType = IPv6_ADDR_STATEUNKNOWN;\
    }\
}

/*IOS = Interface Operation Status*/
#define IPv6_ADDR_IOS_UP                  1
#define IPv6_ADDR_IOS_DOWN                2
#define IPv6_ADDR_IOS_NOIDENTIFIER        3
#define IPv6_ADDR_IOS_UNKNOWN             4
#define IPv6_ADDR_IOS_NOTPRESENT          5

#define IP6_FWDING                        1
#define IP6_NOFWDING                      2

#define REASM_MAXSIZE 65535

#define     IP6_SHIFT_BITS              16
#define     IP6_ADDR_PREFIX_LENGTH      128
#define     IP6_MAC_ADDR_LEN            6
#define     IP6_TIME_TO_MILLI           1000
#define     IP6_TIME_TICK_100           100
#define     IP6_TIME_TICK_10            10
#define     IP6_ADDR_BYTE_LENGTH        8
#define     IP6_ADDR_MAC_BYTE_LEN       6

/*  Reason: Used in VISP to check leftover space in Routing Table*/
#define MIN_TBL_SPACE 2
#define LINK_SCOPE 0x80
#define SITE_SCOPE 0xc0


#define IP6_ADDR_SITELINK_LOCAL_MASK 0xfe

#define IP6_ADDR_MULTI_BYTE_MASK 0xff

#define IP6_ADDR_LOWER_NIBLE_MASK 0x0f

#define IP6_ADDR_BYTE_MASK 0xff

#define IP6_ADDR_BIT_MASK 0x80

#define IP6_ADDR_MASK 0xff

#define IP6_ADDR_CORE_LOG  (VOID)g_stIP6ADDR_SH_CallBack.pfIP6_Addr_SH_LogToIPOSIC
#define IP6_ADDR_CHAR_BUF_50    50


#define IP6_IF_NOTEXIST_RETURN_ERR(m_ulIfIndex)  \
{\
    VOID *pIfTemp;\
    IP6IFNET_S *pstIp6IfTemp;\
    pIfTemp = IPB_IR_IF_GETIFBYINDEX(m_ulIfIndex); \
    if (NULL == pIfTemp) \
    {\
        return VOS_ERR; \
    }\
    pstIp6IfTemp = (IP6IFNET_S *)IPB_IR_IF_GETIPV6CTLBLK(pIfTemp);\
    if (NULL == pstIp6IfTemp) \
    {\
        return VOS_ERR; \
    }\
}

#define IP6_IF_NOTEXIST_SEMUNLOCK_RETURN_ERR(m_ulIfIndex)  \
{\
    VOID *pIfTemp;\
    IP6IFNET_S *pstIp6IfTemp;\
    pIfTemp = IPB_IR_IF_GETIFBYINDEX(m_ulIfIndex); \
    if (NULL == pIfTemp) \
    {\
        TCPIP_END_PT(g_ulSemForTightMods);\
        return VOS_ERR; \
    }\
    pstIp6IfTemp = (IP6IFNET_S *)IPB_IR_IF_GETIPV6CTLBLK(pIfTemp);\
    if (NULL == pstIp6IfTemp) \
    {\
        TCPIP_END_PT(g_ulSemForTightMods);\
        return VOS_ERR; \
    }\
}

#define IP6_IF_NOTEXIST_RETURN(m_ulIfIndex)  \
{\
    VOID *pIfTemp;\
    IP6IFNET_S *pstIp6IfTemp;\
    pIfTemp = IPB_IR_IF_GETIFBYINDEX( m_ulIfIndex); \
    if (NULL == pIfTemp) \
    {\
        return; \
    }\
    pstIp6IfTemp = (IP6IFNET_S *)IPB_IR_IF_GETIPV6CTLBLK(pIfTemp);\
    if (NULL == pstIp6IfTemp) \
    {\
        return; \
    }\
}

#define IP6_ADDR_MAX_MTU_LOWER 1500
#define IP6_ADDR_MAX_MTU_UPPER 10000

/* IP6_ADDR_MALLOC will be used in ADDR module, only when this
 * allocated memory will be used and freed inside ADDR module.
 * Similarly, IP6_ADDR_FREE will be used in ADDR module, only
 * when the corresponding memory is allocated by ADDR module.
 * If the pointer 'ptr' is NULL, then print an assert for
 * debugging the bad pointer.
 */

#define IP6_ADDR_MALLOC(m_ulInfo, m_ulSize)  TCPIP_Malloc((m_ulInfo), (m_ulSize))
#define IP6_ADDR_FREE(m_ptr)\
{\
    if (NULL != (m_ptr))\
    {\
        (VOID)TCPIP_Free((VOID *)m_ptr);\
        (m_ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}

/* Added by Anand - V1R7 Workspace Integration */
#define ADDR_MEM_SET(m_pBufPtr, m_cBufVal, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), (m_cBufVal), (m_ulBufLen))

/* Added by Anand - V1R7 Workspace Integration */
#define ADDR_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* PAF value for POS MTU */
#define IP6_ADDR_PAF_POS_MTU_MAX     g_stIP6ADDR_PAF_MtuPosVal.ulMax_Value
#define IP6_ADDR_PAF_POS_MTU_MIN     g_stIP6ADDR_PAF_MtuPosVal.ulMin_Value
#define IP6_ADDR_PAF_POS_MTU_AVAIL   g_stIP6ADDR_PAF_MtuPosVal.ulAvail_Value

/* PAF value for GE MTU */
#define IP6_ADDR_PAF_GE_MTU_MAX      g_stIP6ADDR_PAF_MtuGEVal.ulMax_Value
#define IP6_ADDR_PAF_GE_MTU_MIN      g_stIP6ADDR_PAF_MtuGEVal.ulMin_Value
#define IP6_ADDR_PAF_GE_MTU_AVAIL    g_stIP6ADDR_PAF_MtuGEVal.ulAvail_Value

/* PAF value for Address number */
#define IP6_ADDR_PAF_ADDR_NUM_MAX    g_stIP6ADDR_PAF_AddrNum.ulMax_Value
#define IP6_ADDR_PAF_ADDR_NUM_MIN    g_stIP6ADDR_PAF_AddrNum.ulMin_Value
#define IP6_ADDR_PAF_ADDR_NUM_AVAIL  g_stIP6ADDR_PAF_AddrNum.ulAvail_Value


/* Macro for NULL parameter  */
#define IP6_NULL_PARA  0
#define IP6_NULL_LOGID 0

/* Macro for unused variables */
#define ADDR_NOUSE(m_vVar)    (VOID)(m_vVar)


/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* DAD State Msg Data Structure */
typedef struct tagIP6Addr_DADSTATEMSG
{
    ULONG          ulIfIndex;
    ULONG          ulRequestType;
    ULONG          ulDADState;
    IN6ADDR_S      stAddr;
}IP6ADDR_DADSTATEMSG_S;

/* Data structure to maintain information for sync. of Multicast addresses
   between Main Board and IO board*/
typedef struct tagIP6Addr_RefCountMsg
{
    ULONG          ulIfIndex;
    ULONG          ulRequestType;
    ULONG          ulRefCount;
    IN6ADDR_S      stAddr;
}IP6ADDR_REFCOUNTMSG_S;

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

extern VOID IP6_ADDR6_Core_Log_Text(CHAR *pMessage, ...);

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

extern IP6_ADDR_SH_CALLBACK_FUNC_S  g_stIP6ADDR_SH_CallBack;
extern IP6_ADDR_SGSN_CALLBACK_FUNC_S g_stIP6ADDR_SGSN_CallBack;

/* Claim of some costant IP6 addresses and prefix */
extern const IN6ADDR_S g_stIn6Addr_any;
extern const IN6ADDR_S g_stIn6Addr_loopback;
extern const IN6ADDR_S g_stIn6Addr_linklocal_allnodes;
extern const IN6ADDR_S g_stIn6Addr_linklocal_allrouters;

extern const IN6ADDR_S g_stIn6Mask128;

extern const IN6ADDR_S g_stIn6Mask_LinkLocal;



/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

#define IP6_ADDR_PREFIXLEN_STATELESS       64

/* Data structure Specific Malloc/Free Macros */
#define IP6_ADDR_GLOBAL_AUTOCFGINFO_MALLOC(m_pstAddrAutoCfgInfo)               \
    (m_pstAddrAutoCfgInfo) = (IP6_ADDR_GLOBAL_AUTOCFGINFO_S *)IP6_ADDR_MALLOC( \
                (IP6_ADDR_MODULEID) | (SID_IP6_AUTOCFG_ADDRINFO),              \
                sizeof(IP6_ADDR_GLOBAL_AUTOCFGINFO_S));

#define IP6_ADDR_GLOBAL_AUTOCFGINFO_FREE(m_pstAddrAutoCfgInfo)                 \
    IP6_ADDR_FREE((m_pstAddrAutoCfgInfo))


#define IP6_ADDR_STATEFUL_TIMER_MALLOC(m_pstStatefulAddrTimerMsg)              \
    (m_pstStatefulAddrTimerMsg) = (IP6_ADDR_STATEFUL_TIMER_S *)IP6_ADDR_MALLOC(\
                (IP6_ADDR_MODULEID) | (SID_IP6_STATEFUL_ADDRTIMER),            \
                sizeof(IP6_ADDR_STATEFUL_TIMER_S));

#define IP6_ADDR_STATEFUL_TIMER_FREE(m_pstStatefulAddrTimerMsg)                \
    IP6_ADDR_FREE((m_pstStatefulAddrTimerMsg))

#define IP6_ADDR_STATELESS_TIMER_MALLOC(m_pstStatelessAddrTimerMsg)            \
    (m_pstStatelessAddrTimerMsg) = (IP6_ADDR_STATELESS_TIMER_S *)IP6_ADDR_MALLOC(\
                (IP6_ADDR_MODULEID) | (SID_IP6_STATELESS_ADDRTIMER),           \
                sizeof(IP6_ADDR_STATELESS_TIMER_S));

#define IP6_ADDR_STATELESS_TIMER_FREE(m_pstStatelessAddrTimerMsg)              \
    IP6_ADDR_FREE((m_pstStatelessAddrTimerMsg))


#define IP6_ADDR_INITIALDELAY_TIMER_MALLOC(m_pstInitDelayTimer)                \
    (m_pstInitDelayTimer) = (IP6_ADDR_INITIALDELAY_TIMER_S *)IP6_ADDR_MALLOC(  \
                (IP6_ADDR_MODULEID) | (SID_IP6_INITDELAY_TIMER),               \
                sizeof(IP6_ADDR_INITIALDELAY_TIMER_S));

#define IP6_ADDR_INITIALDELAY_TIMER_FREE(m_pstInitDelayTimer)                  \
    IP6_ADDR_FREE((m_pstInitDelayTimer))

/* Represents the Number of Applications that can be registered to get
   Ipv6 Enable/Disable Notification on an interface */
#define IP6_ADDR_MAX_APPLICATION_REGISTER 10

/* Gets Interface Physical state */
#define IP6_ADDR_GETINTERFACEPHYSTATE(m_pstIf, m_ulPhyStatusisUp) \
{\
    ULONG  ulLinkStatus;\
    ULONG  ulSpoofing = 0;\
    if (IPB_IR_IF_ISSPOOFINGSET((m_pstIf)))\
    {\
        ulSpoofing = 1 ;\
    }\
    if (IPB_IR_PORT_TEMPLATE == IPB_IR_IF_GETPORTTYPE((m_pstIf)))\
    {\
        ulLinkStatus = IPB_IR_IF_STATUS_PROT_UP;\
    }\
    else\
    {\
        ulLinkStatus = IPB_IR_IF_PFLINKDOWNIOCtl((m_pstIf), \
                                               (ULONG)IPB_IR_SIOCLINKSTATE\
                                                    , NULL );\
    }\
    switch (ulLinkStatus)\
    {\
        case IPB_IR_IF_STATUS_LOW_DOWN :   \
            (m_ulPhyStatusisUp) = 0; \
            break;\
        case IPB_IR_IF_STATUS_PROT_DOWN :   \
            if (IPB_IR_IF_ISSHUTDOWN((m_pstIf)))\
            {\
                (m_ulPhyStatusisUp) = 0;\
            }\
            else\
            {\
                (m_ulPhyStatusisUp) = 1;\
            }\
            break;\
        case IPB_IR_IF_STATUS_PROT_UP :  \
            (m_ulPhyStatusisUp) = 1;\
            break;\
        default :\
            if (ulSpoofing)\
            {\
                if (IPB_IR_IF_ISSHUTDOWN((m_pstIf)))\
                {\
                    (m_ulPhyStatusisUp) = 0; \
                }\
                else\
                {\
                    (m_ulPhyStatusisUp) = 1; \
                }\
            }\
            else\
            {\
                (m_ulPhyStatusisUp) = 1;\
            }\
            break ;\
    }\
}

/* Gets Lifetime state */
#define IP6_ADDR_NDHOST_GETLIFETIME_STATE(m_pstIp6IfAddr, m_ulIP6AddrLifetimeState) \
{\
    IP6_ADDR_GLOBAL_AUTOCFGINFO_S *pstAddrAutoCfgInfo; \
    if (((m_pstIp6IfAddr)->ia6_ulAddrFlag & IP6_NDHOST_ADDR_STATELESS)\
        || ((m_pstIp6IfAddr)->ia6_ulAddrFlag & IP6_NDHOST_ADDR_STATEFUL))\
    {\
        /* Get Lifetime State for Stateless Address */ \
        pstAddrAutoCfgInfo \
                = (IP6_ADDR_GLOBAL_AUTOCFGINFO_S *)m_pstIp6IfAddr->pvAddrInfo; \
        (m_ulIP6AddrLifetimeState) = pstAddrAutoCfgInfo->ulAddrLifetimeState;\
    }\
    else\
    {\
        /* Address Lifetime state for Manual Address is always Preferred */\
        (m_ulIP6AddrLifetimeState) = IP6_ADDR_LIFETIME_PREFERRED;\
    }\
}

/* Modifies selected address */
#define IP6_ADDR_MODIFYSELECTEDSRCADDRESS(m_pstIp6CurIfAddrSel, m_pstIp6NewIfAddr, \
                                    m_ulAddrSrcAddrState, m_ulAddrNewSrcAddrState)\
{\
    (m_pstIp6CurIfAddrSel) = (m_pstIp6NewIfAddr); \
    (m_ulAddrSrcAddrState) = (m_ulAddrNewSrcAddrState); \
}

/* XOR two addresses */
#define IP6_ADDR_XOR_ADDRESSES(m_pstIP6Addr1, m_pstIP6Addr2, m_stIP6AddrRes)\
{\
    m_stIP6AddrRes.s6_addr32[0] = m_pstIP6Addr1->s6_addr32[0]\
                                                ^ m_pstIP6Addr2->s6_addr32[0];\
    m_stIP6AddrRes.s6_addr32[1] = m_pstIP6Addr1->s6_addr32[1]\
                                                ^ m_pstIP6Addr2->s6_addr32[1];\
    m_stIP6AddrRes.s6_addr32[2] = m_pstIP6Addr1->s6_addr32[2]\
                                                ^ m_pstIP6Addr2->s6_addr32[2];\
    m_stIP6AddrRes.s6_addr32[3] = m_pstIP6Addr1->s6_addr32[3]\
                                               ^ m_pstIP6Addr2->s6_addr32[3];\
}

#define IP6_ADDR_ADDRESS_TO_STRING(m_pstIP6Addr, m_szAddr) \
    IP6_Addr_ConvertIp6AddressToString(m_pstIP6Addr, m_szAddr)

/* Gets the Time after Boot. If this system call fails we log and continue
   as system call are not expected to fail */
#define IP6_ADDR_GET_TIME_BOOTINSEC(m_pulBootInSeconds, m_pulUSeconds)\
{\
    if (VOS_OK != g_stIP6ADDR_SH_CallBack.pfIP6_Addr_SH_Tm_BootInSec(\
                                    m_pulBootInSeconds, m_pulUSeconds))\
    {\
        IP6_ADDR_CORE_LOG(ADDR6_LOGID_GETBOOTTIME_FAILED);\
    }\
}

#define IP6_ADDR_IF_RETVAL(pstIfNet)\
    ((!(IPB_IR_IF_ISNULL(pstIfNet))) && (!(IPB_IR_IF_IS_INLOOPBACK(pstIfNet)))) ? VOS_ERR : VOS_OK\


#define IP6_ADDR_MODULEID g_stADDRModInfo.ulModID

#define IP6_ADDR_CREATE_NONPERIODIC_TIMER  \
    g_stIP6ADDR_Timer_CallBack.pfIP6_Addr_SH_CreateNonPeriodicTimer

#define IP6_ADDR_DELETE_TIMER \
    g_stIP6ADDR_Timer_CallBack.pfIP6_Addr_SH_DeleteTimer

#define IP6_ADDR_GET_TIMERINFO \
    g_stIP6ADDR_Timer_CallBack.pfIP6_Addr_SH_GetTimerInfo

#define IP6_ADDR_GET_LEFTOVER_TIME \
    g_stIP6ADDR_Timer_CallBack.pfIP6_Addr_SH_GetLeftoverTime

#define IP6_ADDR_REFRESH_TIMER \
    g_stIP6ADDR_Timer_CallBack.pfIP6_Addr_SH_RefreshTimer


#define IP6_ADDR_FINDOUTINTF_FOR_DESTADDR \
    g_pstADDRNDIRVtbl->pfIP6_ND_FindNHAndOGIntf_ForDestAddr


#define IP6_ADDR_NOTIFY_ND_ADDRNOTUSABLE \
    g_pstADDRNDIRVtbl->pfIP6_ND_NotifyDHCP6CAdaptAddrNotUse

/* Invalid Timer-Id for TWL is 0xFFFFFFFF */
#define IP6_ADDR_INVALID_TIMER_ID                 0xFFFFFFFF

#define IP6_ADDR_INFINITE_DURATION                0xFFFFFFFF

/* Max Tx Timer value
    Possible Max value is 0xFFFFFFFF, But when it is converted into millisec,
    this will exceed the max ULONG. Hence we have chosen - 49 days (4233600)

    i.e 49 days * 24 Hrs * 60 Min * 60 sec = 4233600 Seconds

    4233600 Seconds * 1000 = 4233600000 MilliSec = FC579C00 < FFFFFF */
#define IP6_ADDR_MAX_TIMER_VAL          (49 * 24 * 60 * 60) /* 49 Days */

#define IP6_ADDR_TWOHOURS_TIMER_VAL     (2 * 60 * 60)       /* 2 Hours */

#define IP6_ADDR_TIMER_VAL_ZERO           0

#define IP6_ADDR_SECONDS_TO_MILLISECONDS  1000

#define IP6_ADDR_MAX_INITDELAY_TIME       1000

#define IP6_ADDR_INVALID_MODULE_ID         0

#define IP6_ADDR_INIT_DELAY_REQD           1

#define IP6_ADDR_BITSNUM_IN_ULONG          32

#define IP6_ADDR_BITSNUM_IN_USHORT         16

#define IP6_ADDR_BYTESNUM_IN_ULONG         4

#define IP6_ADDR_BITSNUM_IN_BYTE           8

#define IP6_ADDR_FIRSTBIT_SET              0x80

#define IP6_ADDR_HIGHBYTE_SET_IN_ULONG    0xFFFF0000

#define IP6_ADDR_LOWBYTE_SET_IN_ULONG     0x0000FFFF

#define IP6_ADDR_LOWBYTE_SET_IN_USHORT     0x00FF

/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* AutoConfigured Address Relate Information */
/* WARNING-> The numbers of structure elements shall be moderate i.e <= 5 */
/* The Above HCC Warning is obvious - Will not be addressed */
typedef struct tagIP6AddrGlobalAutoCfgInfo
{
    ULONG ulAddrLifetimeState;    /* Preferred/Valid State */
    ULONG ulPreferredLifeTime;    /* Preferred Lifetime */
    ULONG ulValidLifeTime;        /* Valid Lifetime */
    ULONG ulLastChangePrefTime;   /* Time When Address is created
                                    or Lifetime Updated */
    ULONG ulLastChangeValidTime;  /* Time When Address is created
                                    or Lifetime Updated */
    ULONG ulTimerId;              /* Timer Id of the associated Timer */
    IP6_ND_IATYPE_E    enIAType;   /* IA Type */
    ULONG              ulIAID;    /* IA-ID */
}IP6_ADDR_GLOBAL_AUTOCFGINFO_S;


/* Timer Related Information for Stateless Addresses */
typedef struct tagIP6AddrStatelessTimerInfo
{
    ULONG ulIfnetIndex;         /* Interface Index */
    IN6ADDR_S stIP6AddrPrefix;  /* IP6 Address Prefix */
    IN6ADDR_S stIP6AddrMask;    /* IP6 Address Mask */
}IP6_ADDR_STATELESSADDRESSINFO_S;


/* Timer Related Information for Stateful Addresses */
typedef struct tagIP6AddrStatefulAddressInfo
{
    ULONG ulIfnetIndex;         /* Interface Index */
    IN6ADDR_S stIP6Addr;        /* IP6 Address */
}IP6_ADDR_STATEFULADDRESSINFO_S;

/* Lifetime and State related Information for autoconfigured Addresses */
typedef struct tagIP6_ADDR_LIFETIMEANDSTATE_S
{
    ULONG  ulAddrLifetimeState;   /* Address LifetimeState */
    ULONG  ulRemainValidTime;     /* Valid Lifetime */
    ULONG  ulRemainPrefTime;      /* Preferred Lifetime */
    ULONG  ulCfgValidTime;        /* Configured Valid Time */
    ULONG  ulCfgPrefTime;         /* Configured Preferred Time */
}IP6_ADDR_LIFETIMEANDSTATE_S;


/* Stores Information related to Ipv6 Applications which registers to get
   Interface Level IPv6 Functionality Status */
typedef struct tagIP6AddrRegAppInfo
{
    ULONG ulStatusNotifyCount;
    IP6_ADDR_APPLICATION_CALLBACK_FUNC_S stIpv6StatusNotifyList[IP6_ADDR_MAX_APPLICATION_REGISTER];
}IP6_ADDR_REGISTERED_APP_INFO_S;





#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
#define IP6_ADDR_NOTIFY_NP(ulOper, pvAddrInfo) \
    ((g_pfIP6_ADDR_PPIOperation)?IP6_Addr_Notify_PPI(ulOper, pvAddrInfo) : VOS_OK)

#else
#define IP6_ADDR_NOTIFY_NP(ulOper, pvAddrInfo) VOS_OK
#endif

#define IP6_ADDR_IP6CB_FLAG_ISSET(pstIPv6CtlBlk, flag) \
                        ((pstIPv6CtlBlk)->ucFlag & (flag))

#define IP6_ADDR_IP6CB_FLAG_SET(pstIPv6CtlBlk, flag) \
                        ((pstIPv6CtlBlk)->ucFlag |= (flag))

#define IP6_ADDR_IP6CB_FLAG_RESET(pstIPv6CtlBlk, flag) \
                        ((pstIPv6CtlBlk)->ucFlag &= (~(flag)))

#define IP6_ADDR_NOTIFY_STATEINFO(ulOperation, pvAddrInfo) \
    ((g_pstDADNotifyCallback)?\
        IP6_Addr_Notify_StateInfo(ulOperation, pvAddrInfo) : VOS_OK)

#define IP6_ADDR_NOTIFY_STATEINFO_UPONCONDITION(m_ulOperation, m_pvAddrInfo, m_Condition) \
    ((m_Condition)?((g_pstDADNotifyCallback)?\
        IP6_Addr_Notify_StateInfo(m_ulOperation, m_pvAddrInfo) : VOS_OK):VOS_OK)


#define IP6_ADDR_ADDRESS_TO_NETWORK(dst, src)\
{\
    dst[0] = VOS_HTONL(src[0]);\
    dst[1] = VOS_HTONL(src[1]);\
    dst[2] = VOS_HTONL(src[2]);\
    dst[3] = VOS_HTONL(src[3]);\
}

typedef struct tagIP6AddrIfVpn
{
    ULONG  ulIfindex;   
    struct tagIP6AddrIfVpn *next;
    struct tagIP6AddrIfVpn *prev;                                
} IP6_Addr_IfVpn;

typedef struct tagIP6AddrVpn
{
    struct tagIP6AddrIfVpn *Head;
    VOID *pvVpnRootNode;  /* Root node for the address list head */
} IP6_Addr_VPN;

#define IP6_ADDR_ADDRESS_ARRAY_COPY(dst, src)\
{\
    dst[0] = src[0];\
    dst[1] = src[1];\
    dst[2] = src[2];\
    dst[3] = src[3];\
}

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _ADDR_DEF_H_ */
