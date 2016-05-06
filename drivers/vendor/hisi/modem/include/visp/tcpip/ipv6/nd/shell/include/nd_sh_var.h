
/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : Initial Draft
*    File Name      : ND_SH_VAR.H
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : contains shell variables related definations
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef      _ND_SH_VAR_H_
#define      _ND_SH_VAR_H_

#ifdef      __cplusplus
extern "C"{
#endif

extern ULONG g_ulNDExecIndex;

#define BUF_LEN_100 100
#define BUF_LEN_256 256
#define BUF_LEN_512 512

/* AC4D01206 - Added by Prabhu H (71185) */
#define BUFLEN_1024 1024
#define BUFFERLENGTH_2048 2048

#if (VRP_YES == IP6_NDHOST)
#define IP6_ND_TIMER_MAX_NUM                        40000
#define IP6_ND_MAX_CTRL_MSG_QUE_PROCESS_PER_TIME    2

#define IP6_ND_MAX_CTRL_MSG_QUE_LENGTH              512
#endif /* #if (VRP_YES == IP6_NDHOST) */

/* Added by Anand - V1R7 Workspace Integration */
#define ND_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Added by Anand - V1R7 Workspace Integration */
#define ND_MEM_SET(m_pBufPtr, m_cBufVal, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), (m_cBufVal), (m_ulBufLen))


/* ND cli state */
extern ULONG g_ulNDCliState;
extern ULONG g_ulQFullNumber;

/* Level 1 Interface V-table pointers */
extern struct IIF_IP6_ND_COMMONVtbl             *g_pstNDCommonTable;
extern struct IIF_IP6_ND_GENERIC_INTVtbl        *g_pstNDInitTable;
extern struct IIF_IP6_ND_GENERIC_CFGVtbl        *g_pstNDCfgTable;
extern struct IIF_IP6_ND_GENERIC_FUNVtbl        *g_pstNDFunTable;

#if (VRP_YES == IP6_NDHOST)
extern struct IIF_IP6_ND_HOST_DHCP6ADAPTVtbl   *g_pstNDDHCP6CAdaptTable;
#endif

/* Level 2 Interface V-table pointers */
extern struct IIF_IP6_ND_GENERIC_IR_FUNVtbl     *g_pstNDIRFunTable;

/* Level 3 Interface V-table pointers */
extern struct IIF_IP6_ND_GENERIC_INT_INITVtbl   *g_pstNDINTInitTable;
extern struct IIF_IP6_ND_GENERIC_INT_FUNVtbl    *g_pstNDINTFunTable;
extern struct IIF_IP6_ND_GENERIC_INT_SSAVtbl    *g_pstNDINTSSATable;

/* Level 1 ADDR Function VTable */
extern struct IIF_IP6_ADDR_GENERIC_FUNVtbl   *g_pst_SH_NDADDRVtbl;

extern void SNMP_Add_MIB_ND_tree(void);
extern const struct ComponentInfo m_CompNDInfo;
extern ULONG IP6_ND_SH_PAF_Init(void);
extern CHAR *Inf_ND_En[];
extern CHAR *Inf_ND_Ch[];
extern ULONG VRP_GetTaskFollowMe(ULONG);
extern ULONG     g_ulNDTimerQueueId;
extern IPOS_APP_INIT_INFO_S g_stNdAppInfo;

/* Added By Ahmed for Defect ID: AC4D05729 */
/* IO Board Exception Resolution, new Queue ID is added
   to handle ASYNC events between ADDR and ND*/
extern ULONG     g_ulNDEventQueueId;

extern ULONG g_ulND_Sh_IsIAS;


/* Bool value for ND shell init is success or failure */
extern BOOL_T g_bIP6_ND_SH_Init_Status;

#if (VRP_YES == IP6_NDHOST)

/* Control Message Queue Id */
extern ULONG g_ulNDCtrlMsgQueueId;

/* Twl Tick proc timer ID */
extern ULONG g_ulNDTwlTickProcTimerId;

/* TWL handle */
extern TWL_HANDLE g_stNDTWLHandleGbl;

/* String Table for Adaptor Notification Type */
extern CHAR *g_szIP6_ND_AdaptNotifyType[];

/* String Table for Adaptor Notification Address Not Usable Reasons */
extern CHAR *g_szIP6_ND_NotifyAddrNotUsableReason[];

#endif /* #if (VRP_YES == IP6_NDHOST) */

//extern void vos_printf(char *fmt, ...);
extern CHAR * inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr,
                            ULONG ulAddrLen);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ND_H_ */

