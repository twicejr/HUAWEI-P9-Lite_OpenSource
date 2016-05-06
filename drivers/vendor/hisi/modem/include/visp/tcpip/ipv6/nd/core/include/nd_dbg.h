/******************************************************************************

             Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
                            All Rights Reserved

 ******************************************************************************
  File Name     : nd_dbg.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : Anand S
  Created       : 2007/1/22
  Last Modified :
  Description   : file contains ND Debug Wrapper functions prototypes
  Function List :

  History       :
  1.Date        : 2007/1/22
    Author      : Anand S
    Modification: Created file
******************************************************************************/


#ifndef _ND_DBG_H
#define _ND_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern ULONG VOS_strlen(const CHAR * Str); /*Changed by wan for VISPV1R7 integration*/

ULONG IP6_ND_Send_NDMsg_DbgToIC(ULONG ulDbgID,
                                const IN6ADDR_S *pstAddress,
                                ULONG ulIfIndex,ULONG ulMsgTypeIndex);

ULONG IP6_ND_Send_NBEntry_DbgToIC(ULONG ulDbgID,
                                const IN6ADDR_S *pstAddress,
                                ULONG ulIfIndex,ULONG ulOldState,
                                ULONG ulNewState);

ULONG IP6_ND_Send_Prefix_DbgToIC(ULONG ulDbgID,
                                const IN6ADDR_S *pstPrefix,
                                ULONG ulPrefixLen,ULONG ulLFlag,
                                ULONG ulAFlag);

ULONG IP6_ND_Send_Host_DbgToIC(ULONG ulDbgID, CHAR *szString1,
                                IN6ADDR_S *pstAddress, CHAR *szString2,
                                ULONG ulIfIndex);

ULONG IP6_ND_Send_Host_Timer_DbgToIC(ULONG ulDbgID,
                                CHAR *szString1, IN6ADDR_S *pstAddress,
                                ULONG ulPrefixLen, ULONG ulIfIndex,
                                ULONG ulTimerVal, ULONG ulTimerId);

ULONG IP6_ND_Send_Host_PrefixDbgToIC(ULONG ulDbgID,
                                CHAR *szString1, IN6ADDR_S *pstAddress,
                                ULONG ulPrefixLen, CHAR *szString2,
                                ULONG ulIfIndex);

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
/* Added for IPv6 Log Information */
#define IP6_ND_CORE_DEBUG   g_stNDCallBack.pfIP6ND_SH_DbgToIPOSIC

#define IP6_ND_SEND_NDMSG_DBGTOIC(m_ulDbgID, \
                                    m_pstAddress, \
                                    m_ulIfIndex, \
                                    m_ulMsgTypeIndex) \
{                                                                       \
    if (VRP_YES == g_ulNDDebugFlag)                                     \
    {                                                                   \
        (VOID)IP6_ND_Send_NDMsg_DbgToIC((m_ulDbgID), (m_pstAddress),    \
                            (m_ulIfIndex), (m_ulMsgTypeIndex));         \
    }                                                                   \
}

#define IP6_ND_SEND_NBENTRY_DBGTOIC(m_ulDbgID,    \
                                    m_pstAddress, \
                                    m_ulIfIndex,  \
                                    m_ulOldState, \
                                    m_ulNewState) \
{                                                                       \
    if (VRP_YES == g_ulNDDebugFlag)                                     \
    {                                                                   \
        (VOID)IP6_ND_Send_NBEntry_DbgToIC((m_ulDbgID), (m_pstAddress),  \
        (m_ulIfIndex), (m_ulOldState), (m_ulNewState));                 \
    }                                                                   \
}

#define IP6_ND_SEND_PREFIX_DBGTOIC(m_ulDbgID,     \
                                    m_pstPrefix,  \
                                    m_ulPrefixLen,\
                                    m_ulLFlag,    \
                                    m_ulAFlag)    \
{                                                                   \
    if (VRP_YES == g_ulNDDebugFlag)                                 \
    {                                                               \
        (VOID)IP6_ND_Send_Prefix_DbgToIC((m_ulDbgID), (m_pstPrefix),\
                    (m_ulPrefixLen), (m_ulLFlag), (m_ulAFlag));     \
    }                                                               \
}

#define IP6_ND_HOST_TIMER_DBG(m_ulDbgID,       \
                                m_szString1,   \
                                m_pstAddress,  \
                                m_ulPrefixLen, \
                                m_ulIfIndex,   \
                                m_ulTimerVal,  \
                                m_ulTimerId)   \
{                                                                   \
    if (VRP_YES == g_ulNDDebugFlag)                                 \
    {                                                               \
        (VOID)IP6_ND_Send_Host_Timer_DbgToIC((m_ulDbgID), (m_szString1),\
                (m_pstAddress), (m_ulPrefixLen), (m_ulIfIndex),           \
                (m_ulTimerVal), (m_ulTimerId));                         \
    }                                                               \
}

#define IP6_ND_HOST_GEN_DBG(m_ulDbgID,    \
                            m_szString1,  \
                            m_pstAddress, \
                            m_szString2,  \
                            m_ulIfIndex)  \
{                                                                   \
    if (VRP_YES == g_ulNDDebugFlag)                                 \
    {                                                               \
        (VOID)IP6_ND_Send_Host_DbgToIC((m_ulDbgID), (m_szString1),  \
                (m_pstAddress), (m_szString2), (m_ulIfIndex));      \
    }                                                               \
}

#define IP6_ND_HOST_PREFIX_DBG(m_ulDbgID,     \
                                m_szString1,  \
                                m_pstAddress, \
                                m_ulPrefixLen,\
                                m_szString2,  \
                                m_ulIfIndex)  \
{                                                                           \
    if (VRP_YES == g_ulNDDebugFlag)                                         \
    {                                                                       \
        (VOID)IP6_ND_Send_Host_PrefixDbgToIC((m_ulDbgID), (m_szString1),    \
        (m_pstAddress), (m_ulPrefixLen), (m_szString2), (m_ulIfIndex));     \
    }                                                                       \
}

#define IP6_ND_DbgOut_Info_P1(p1)  \
{                                                                           \
    if (VRP_YES == g_ulNDDebugFlag)                                         \
    {                                                                       \
        (VOID)IP6_ND_CORE_DEBUG(ND_DBGID_DBGINFO_LEVEL, p1);     \
    }                                                                       \
}

#define IP6_ND_DbgOut_Info_P2(p1, p2)  \
{                                                                           \
    if (VRP_YES == g_ulNDDebugFlag)                                         \
    {                                                                       \
        (VOID)IP6_ND_CORE_DEBUG(ND_DBGID_DBGINFO_LEVEL, p1, p2);     \
    }                                                                       \
}

#define IP6_ND_DbgOut_Info_P3(p1, p2, p3)  \
{                                                                           \
    if (VRP_YES == g_ulNDDebugFlag)                                         \
    {                                                                       \
        (VOID)IP6_ND_CORE_DEBUG(ND_DBGID_DBGINFO_LEVEL, p1, p2, p3);     \
    }                                                                       \
}

#define IP6_ND_HOST_FOWARD_PATH_DBG(m_ulDbgID,    \
                                    m_szString1,  \
                                    m_pstAddress, \
                                    m_szString2,  \
                                    m_ulIfIndex)

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _ND_DBG_H */
