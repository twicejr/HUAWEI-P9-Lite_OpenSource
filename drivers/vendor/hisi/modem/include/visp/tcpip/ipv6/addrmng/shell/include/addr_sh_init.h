/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code:  VRP5.0
*    Module Name:  IP6 ADDR SHELL
*    File Name: ADDR_SH_INIT.H
*    Version       : IPBIRV100R003.IPv6.E001
*    Create Date:  2003/07/02
*    Author:  Santosh G Kulkarni
*    Description:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-07-02  Santosh G Kulkarni     Create
  1.Problem Number: AC4D01052     Author:Sandeep71635,   Date:2006/11/11
    Description   : Set Res Specs APIs input validation not complete
  2.Problem Number: AC4D01246     Author:KLSrini,   Date:2006/12/4
    Description   :  Exception with router restart when change Controller
                    interface mode with IPv6 debug
*******************************************************************************/
#ifndef _ADDR_SH_INIT_H
#define _ADDR_SH_INIT_H

#ifdef    __cplusplus
extern "C"{
#endif




#define IP6_ADDR_ENABLE_CLI     1
#define IP6_ADDR_DISABLE_CLI    0

/* moved from addr_public.h */
#define IP6_ADDR_SUFFIX_LEN    15

/* By Guru for Memory shortage handling feature; 04-05-2004 */
#define IP6ADDR_MEM_SHORTAGE_REACH      1

/* Begin : Defect ID: D01006,     Modifier:Rajesh,   Date:2004/9/13
Reason   : Max Mtu change for Pos,GE interfaces*/

#define     MAX_SPECS_FOR_ADDR           4

#define     IP6_QUEUE_WRITE_MSG_LEN     4
#define     IP6_ADDR_CHAR_BUF_15        15
#define     IP6_ADDR_CHAR_BUF_17        17
#define     IP6_ADDR_CHAR_BUF_50        50
#define     IP6_ADDR_CHAR_BUF_64        64
#define     IP6_ADDR_CHAR_BUF_128       128
#define     IP6_ADDR_CHAR_BUF_256       256
#define     IP6_ADDR_CHAR_BUF_1024      1024
#define     IP6_ADDR_IF_EXCESS          2
#define     IP6_ADDR_IF_INFO_SIZE       100
#define     IP6_CFG_GET_ULONG_DEF_VAL   2
#define     IP6_LEN_OF_DUP_STR          12
#define     IP6_SPACE_LEFT              40
#define     IP6_BLANK_SPACES_LEN        4
#define     IP6_LEN_OF_ADDR_STR         12
#define     IP6_ONE_LENGTH_SIZE         75
#define     IP6_IF_ID_LEN_MUL           8
#define     IP6_ADDR_IF_NAME_LENGTH_28  28
#define     IP6_ADDR_CONVRT_MILLSEC   1000

/* Added for IPv6 Log Information */
#define IP6_MAX_LOG_LEN    255

#define IP6_ADDR_BUFFER 512

#define IP6_ADDR_DISPLAY  IP6_SH_Log_Text


/* Macro to LOG Error Codes of IP6 Module*/
#define IP6_ADDR_DISPLAY_0(level, str) \
    {\
        if (VOS_TRUE == IP6_SH_CheckDebug(level))\
        {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "str"\n", \
        IPB_IR_IF_GETSELFBOARDID());\
        }\
    }


#define IP6_ADDR_DISPLAY_1(level, str, arg1) \
    {\
        if (VOS_TRUE == IP6_SH_CheckDebug(level))\
        {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "str"\n", \
        IPB_IR_IF_GETSELFBOARDID(), arg1);\
        }\
    }

#define IP6_ADDR_DISPLAY_2(level, str, arg1, arg2) \
    {\
        if (VOS_TRUE == IP6_SH_CheckDebug(level))\
        {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "str"\n", \
        IPB_IR_IF_GETSELFBOARDID(), arg1, arg2);\
        }\
    }

#define IP6_ADDR_DISPLAY_3(level, str, arg1, arg2, arg3) \
    {\
        if (VOS_TRUE == IP6_SH_CheckDebug(level))\
        {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "str"\n", \
        IPB_IR_IF_GETSELFBOARDID(),  arg1, arg2, arg3);\
        }\
    }

#define IP6_ADDR_DISPLAY_4(level, str, arg1, arg2, arg3, arg4) \
    {\
        if (VOS_TRUE == IP6_SH_CheckDebug(level))\
        {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "str"\n", \
        IPB_IR_IF_GETSELFBOARDID(), arg1, arg2, arg3, arg4);\
        }\
    }

#define IP6_ADDR_DISPLAY_5(level, str, arg1, arg2, arg3, arg4, arg5) \
    {\
        if (VOS_TRUE == IP6_SH_CheckDebug(level))\
        {\
        IP6_ADDR_DISPLAY("\r\n [Board ID = %u] | "str"\n", \
        IPB_IR_IF_GETSELFBOARDID(), arg1, arg2, arg3, arg4, arg5);\
        }\
    }



#define IP6_ADDR_SH_LOG     (VOID) IP6_Addr_SH_LogToIPOSIC

#define IP6_ADDR_SH_DBG     (VOID) IP6_Addr_SH_DbgToIPOSIC

ULONG IP6_Addr_SH_Init(VOID);
ULONG IP6_Addr_SH_DeInit(VOID);

ULONG IP6_Addr_SH_LogToIPOSIC(ULONG ulLogID, ...);
ULONG IP6_Addr_SH_AddrStToStr(const IN6ADDR_S *pstAddress,
                                      char *szAddr);

ULONG IP6_Addr_SH_DbgToIPOSIC(ULONG ulDbgID, ...);

/* Macro to check the Validity of Ifnet and IPv6 Control Block Pointers */
#define IP6_IF_NOTEXIST_RETURN_OK(ulIfIndex)  \
{\
    VOID *pIfTemp;\
    IP6IFNET_S *pstIp6IfTemp;\
    pIfTemp = IPB_IR_IF_GETIFBYINDEX( ulIfIndex ); \
    if (NULL == (pIfTemp)) \
    {\
        return VOS_OK; \
    }\
    pstIp6IfTemp = (IP6IFNET_S *)IPB_IR_IF_GETIPV6CTLBLK(pIfTemp);\
    if (NULL == (pstIp6IfTemp)) \
    {\
        return VOS_OK; \
    }\
}

/* IP6_ADDR_MALLOC will be used in ADDR module, only when this
 * allocated memory will be used and freed inside ADDR module.
 * Similarly, IP6_ADDR_FREE will be used in ADDR module, only
 * when the corresponding memory is allocated by ADDR module.
 * If the pointer 'ptr' is NULL, then print an assert for
 * debugging the bad pointer.
 */

#define IP6_ADDR_MALLOC(ulInfo, ulSize)  TCPIP_Malloc((ulInfo), (ulSize))
#define IP6_ADDR_FREE(ptr)\
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

/* Macro for unused variables */
#define ADDR_NOUSE(m_vVar)    (VOID)(m_vVar)

/* Added by Anand - V1R7 Workspace Integration */
#define ADDR_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Added by Anand - V1R7 Workspace Integration */
#define ADDR_MEM_SET(m_pBufPtr, m_cBufVal, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), (m_cBufVal), (m_ulBufLen))

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)

#define IP6_ADDR_REG_NPCALLBACK_CORE()                                \
{                                                                     \
    IPV6_PPI_HOOK_S *pstNPCallBack = NULL;                            \
    (VOID)IP6_PPI_GetValue(&pstNPCallBack);                           \
    if (pstNPCallBack)                                                \
    {                                                                 \
        (VOID)g_pstADDRINTInitTable->pfIP6_Addr_RegNPCallback(        \
                                                pstNPCallBack);       \
    }                                                                 \
}

#else

#define IP6_ADDR_REG_NPCALLBACK_CORE()

#endif


#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif      /* end of _ADDR_SH_INIT_H_ */
