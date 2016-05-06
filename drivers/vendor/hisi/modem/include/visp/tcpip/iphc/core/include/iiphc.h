/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         iiphc.h
 *
 *  Project Code: VISP
 *   Module Name: IPHC
 *  Date Created: 2005-09-20
 *        Author: Sun Mo 44939
 *   Description: Defines Component ID, and All Interface IDs for 
 *                IPHC Component
 *
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-20      Sun Mo               Create
 *  2006-03-30      xiehuaguo       Adjust for D00647
 *
 ************************************************************************/
#ifndef _IIPHC_H
#define _IIPHC_H
 
 
#ifdef  __cplusplus
extern  "C"{
#endif

DECLARE_INTERFACE( IIF_COMP_IPHC_ComIntFUN ) 
{
    IUNKNOWN_METHODS
  
    /* These methods have to be used by link layer for initiating or releasing the IPHC data table */
    METHOD_(IPHC_COMPRESSION_CONTEXT_S*, pfIPHC_Initiate)(ULONG ulIfIndex, 
                                                          ULONG CCOMPANY,
                                                          ULONG DELETE_UDP_CHECKSUM,
                                                          PPP_IPCP_OPTION_S *pstGotOption, 
                                                          PPP_IPCP_OPTION_S *pstHisOption);
            
    METHOD_(IPHC_COMPRESSION_CONTEXT_S*, pfIPHC_Release)(IPHC_COMPRESSION_CONTEXT_S *pIphcContext);

    /* These methods have to be used by link layer for compressing or decompressing the packet's headers */
    METHOD_(USHORT, pfIPHC_Compression)(MBUF_S **ppMbuf, IPHC_COMPRESSION_CONTEXT_S *pIphcContext, USHORT usIphcType);
    METHOD_(USHORT, pfIPHC_Decompression)(MBUF_S **ppMbuf, IPHC_COMPRESSION_CONTEXT_S *pIphcContext, USHORT usIphcType);
};

DECLARE_INTERFACE( IIF_COMP_IPHC_ComIntCFG )
{
    IUNKNOWN_METHODS

    /* These methods provided to shell for com init, activate, and module info registration */
    METHOD_(ULONG, pfIPHC_Init_Com)(VOID);
    METHOD_(ULONG, pfIPHC_Activate_Com)(VOID);
    METHOD_(ULONG, pfIPHC_SetModuleInfo)(IPHC_MOD_INFO_S *pstMInfo);

    /* These methods provided to shell for command processing */
    /* Set the debug switch of the debug info type */
    METHOD_( LONG, pfIPHC_DebugAll)(VOID);
    METHOD_( LONG, pfIPHC_NoDebug)(VOID);
    METHOD_( ULONG, pfIPHC_ProcessTcpDebug)(ULONG ulSetYes);
    METHOD_( ULONG, pfIPHC_ProcessNonTcpDebug)(ULONG ulSetYes);

    /* Release context structure */
    METHOD_(VOID, pfIPHC_TcpContextRelease)(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
    METHOD_(VOID, pfIPHC_NonTCPContextRelease)(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);

    METHOD_(VOID, pfIPHC_TcpStatClear)(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
    METHOD_(VOID, pfIPHC_NonTcpStatClear)(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
    /* End of addition */

    METHOD_(ULONG, pfIPHC_GetIfIPHCStatistics)(ULONG ulIfIndex,TCPIP_IPHC_STATISTICS_S *pstIPHCStatistics);
};    

DECLARE_INTERFACE( IIF_COMP_IPHC_ComIntSSA )
{
    IUNKNOWN_METHODS

    /* The method provided to shell for functionality purpose */ 
    METHOD_(ULONG, pfIPHC_RegShellApi)(IPHC_SHELL_CALLBACK_SET_S *pstCallBkSet);
};

/* For implement of QuerfyInstance() */
typedef struct tagIPHCINT_OBJ_S
{
    IIF_COMP_IPHC_ComIntFUN  *pComIntFUN;
    IIF_COMP_IPHC_ComIntCFG  *pComIntCFG;
    IIF_COMP_IPHC_ComIntSSA  *pComIntSSA;
}IPHC_INT_OBJ_S;


#ifdef  __cplusplus
}
#endif

#endif

