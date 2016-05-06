/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            pmtu_sh_def.h
 *    Project Code : VRP5.0
 *    Module Name  : IP6 PMTU
 *    Version      : Initial Draft
 *    Create Date  : 2003/06/10
 *         Author  : Surya PC
 *     Description : All the shell related definitions could be
 *                   given in this file
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE        NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2003-08-10  Surya         Create
 ******************************************************************************/
#ifndef _IP6_PMTU_SH_DEF_H
#define _IP6_PMTU_SH_DEF_H

#ifdef  __cplusplus
extern "C"{
#endif

/* Shell related systrace.*/
#define IP6_PMTU_SHELL_INIT    ((SYSTRC_IPV6_PMTU_BASE << 8) + 010)
#define IP6_PMTU_SHELL_CFG     ((SYSTRC_IPV6_PMTU_BASE << 8) + 011)
#define IP6_PMTU_SHELL_TIMEOUT ((SYSTRC_IPV6_PMTU_BASE << 8) + 012)
#define IP6_PMTU_SHELL_HA      ((SYSTRC_IPV6_PMTU_BASE << 8) + 013)
#define IP6_PMTU_SHELL_IC      ((SYSTRC_IPV6_PMTU_BASE << 8) + 014)
#define IP6_PMTU_SHELL_PAF     ((SYSTRC_IPV6_PMTU_BASE << 8) + 015)
#define MAX_BUILDRUN_ENTRY_INFO_LENGTH 160
#define MAX_BUILDRUN_AGE_INFO_LENGTH   40

/* Buffer size for age display.*/
#define PMTU_MAX_BUILDRUN_AGE_MEM      40

#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif

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
        (VOID)TCPIP_Free((VOID *)ptr);\
        (ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}

/* Added by Anand - V1R7 Workspace Integration */
#define PMTU_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Pmtu Maximum message process per time slice.*/
#define PMTU_MAX_MSG_PROCESS  10

#define PMTU_CHAR_BUF_256     256
#define PMTU_CHAR_BUF_50      50
#define PMTU_CHAR_BUF_46      46
#define PMTU_CHAR_BUF_15      15
#define PMTU_CHAR_BUF_5       5
#define PMTU_MSGHEAD_SIZE     4
#define PMTU_CHAR_BUF_200     200
#define PMTU_CHAR_BUF_100     100
#define PMTU_CHAR_BUF_512     512
#define PMTU_SUBMODULE_ID     10
#define PMTU_CHAR_BUF_64      64
#define IP6_PMTU_LOGID_DEF(LogId) IPOS_IC_INFOID_DEF(MID_PMTU, \
                                            IC_INFO_LOG, LogId)
#define IP6_PMTU_DBGID_DEF(DbgId) IPOS_IC_INFOID_DEF(MID_PMTU, \
                                            IC_INFO_DEBUG, DbgId)
#define IP6_PMTU_SH_LOG         (VOID)IP6_Pmtu_SH_LogToIPOSIC
#define IP6_PMTU_SH_DEBUG       (VOID)IP6_Pmtu_SH_DbgToIPOSIC

/* PN:AC4D01077*/
typedef struct tagPmtuDebugInfoIo
{
    USHORT usMsgtype;
    USHORT usReserved;
    ULONG  ulDbgFlag;
} PMTU_DEBUG_INFO_IO_S;

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)

#define IP6_PMTU_REG_NPCALLBACK_CORE()                                \
{                                                                     \
    IPV6_PPI_HOOK_S *pstNPCallBack = NULL;                            \
    (VOID)IP6_PPI_GetValue(&pstNPCallBack);                           \
    if (pstNPCallBack)                                                \
    {                                                                 \
        (VOID)g_pstPMTU_INT_INITVtbl->pfIP6_PMTU_RegNPCallback(       \
                                                pstNPCallBack);       \
    }                                                                 \
}

#else
#define IP6_PMTU_REG_NPCALLBACK_CORE()
#endif

#ifdef  __cplusplus
}
#endif

#endif
