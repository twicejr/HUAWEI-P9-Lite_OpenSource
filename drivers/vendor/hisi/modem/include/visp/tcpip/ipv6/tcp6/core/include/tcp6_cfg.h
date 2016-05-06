/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              Tcp6_cfg.h
*
*    Project Code:  VRP5.0
*    Module Name:  IP6 TCP6
*    Create Date:  2003/06/27
*    Author:       Naina Gupta
*    Description:  Initialize the shell and main loop process funtion apis
*    Version     : Initial Draft
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-27  Naina Gupta    Create
*  2006-06-06  Alok           Updated for 14 Fly-Check rules adherence
*                             for IPOSIR-V1R1-IPv6
*  2006-08-29  Prabhu H       Updated for RFC 4022 MIB implmentation
******************************************************************
*/

#ifndef _TCP6_CFG_H
#define _TCP6_CFG_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define TCP6_FILT_PERMIT   0
#define TCP6_FILT_DENY     1

#ifndef NO_USE
#define NO_USE(var)     ((VOID)(var))
#endif

/* TCP6 MIB Connection Table structure of RFC 2452 */
typedef struct tagTCP6MIBCONNTABLE
{
    LONG    lLength;
    CHAR    *pBuffer;
} TCP6MIBCONNTABLE_S;

#define TCP6_TCP6CB_FOUND 1

USHORT TCP6_TCP6CBFound (TCP6CB_S * pstTCP6CB);
VOID TCP6_StateChangeOutput(TCP6CB_S *pstTCP6CB, SHORT sNewState);

VOID TCP6_TransaOutput(TCP6CB_S *pstTCP6CB,
                               const CHAR *szInfo,
                               ULONG ulFlag);
UINTPTR TCP6_GetNextTCP6CB(IN6ADDR_S stLAddr, ULONG ulLPort,
                    IN6ADDR_S stFAddr, ULONG ulFPort, ULONG ulIfIndx,
                    UINTPTR ulPcbHead);

TCP6MIBCONN_S * TCP6_MibConnItem(UINTPTR ulIn6Pcb);

TCP6MIBCONN_S *TCP6_ConnTableMatch(IN6ADDR_S stLAddr,
                                  ULONG ulLPort,
                                  IN6ADDR_S stFAddr,
                                  ULONG ulFPort, ULONG ulIfIndx);

TCP6MIBCONN_S * TCP6_ConnTableGetNext(IN6ADDR_S stLAddr,
                                    ULONG ulLPort,
                                    IN6ADDR_S stFAddr,
                                    ULONG ulFPort, ULONG ulIfIndx);

TCP6MIBCONN_S * TCP6_ConnTableGetFirst(VOID);
VOID TCP6_GetIn6PCBFromConnections (UINTPTR *pulIn6PCB);
ULONG TCP6_OpenObject_TCP6Conn (ULONG ulMainType,
                                              UINTPTR *pulHandle);

ULONG TCP6_CloseObject_TCP6Conn (UINTPTR  ulHandle);


ULONG TCP6_Get_Object_NextTCP6Conn (UINTPTR ulHandle,
                                                  TCP6CONNPARAM_S *pstTcp6CB);
ULONG TCP6_GetMatchTCP6CB (
      IN6ADDR_S stLAddr, ULONG ulLPort, IN6ADDR_S stFAddr, ULONG ulFPort,
      TCP6CB_S *pstTCP6CB,  TCP6CONNPARAM_S *pstTcp6CBConn);

VOID TCP6_Get_Param (ULONG ulType, ULONG *pulValue);

/*  Reason: TCP6 MIB RFC 4022 implementation  */

/* AC4D01786 - Added by Prabhu H (71185) for proper TCP MIB state display */
#define TCP6S_MIB_CLOSED        1
#define TCP6S_MIB_LISTEN        2
#define TCP6S_MIB_SYNSENT       3
#define TCP6S_MIB_SYNRECV       4
#define TCP6S_MIB_ESTABLISH     5
#define TCP6S_MIB_FINWAIT1      6
#define TCP6S_MIB_FINWAIT2      7
#define TCP6S_MIB_CLOSEWAIT     8
#define TCP6S_MIB_LASTACK       9
#define TCP6S_MIB_CLOSING       10
#define TCP6S_MIB_TIMEWAIT      11
#define TCP6S_MIB_DELTCB        12

ULONG TCP6_Set_Syn_TimeOut(ULONG ulTCP6KeepIntvl,ULONG ulFlag);
ULONG TCP6_Set_Fin_TimeOut(ULONG ulTCP6KeepIntvl, ULONG ulFlag);
ULONG TCP6_Set_Window(ULONG ulValue, ULONG ulFlag);
ULONG TCP6_Get_TCPCBParam(IN6ADDR_S stLAddr,
                                      ULONG ulLPort,
                                      IN6ADDR_S stFAddr,
                                      ULONG ulFPort,
                                      ULONG ulUserVrfIndex,
                                      TCP6CBPARAM_S *pstMatchNode);

ULONG IP6_TCP6_GetDebugFilter(ULONG *pulDebugFlag,
                                       TCP6DBUGFILTRD_S *pstSockDbgPktFilter,
                                       TCP6DBUGFILTRD_S *pstSockDbgTransFilter);

ULONG  TCP6_ProDbugFilter(ULONG ulFlag, ULONG ulDbgFilterId,
                           ULONG ulTaskId, ULONG ulSockId);

VOID TCP6_SetFilterZero (VOID);

ULONG  TCP6_ClassifyDbugFilt(TCP6DBUGFILTRD_S *pstDbugFiltRd,
    ULONG ulTaskId, ULONG ulSockId);

VOID TCP6_Get_ulCurrEstablished (ULONG *pulCurrentEstablished);


VOID TCP6_GetStatistics(TCP6STAT_S *pstTCP6Stat);

VOID TCP6_SetStatisticsZero (VOID);

CHAR * TCP6_SprintSockPair(UINTPTR ulIN6PCB, CHAR *pszRet,INT32 i32BufLen);
VOID TCP6_PrintPort(USHORT usPort,CHAR *pszBuf,INT32 i32BufLen);
VOID TCP6_PrintState(SHORT sState,CHAR *szBuf,INT32 i32BufLen);

LONG  TCP6_SetDebugAll(VOID);

VOID TCP6_ClearDebugFlag(VOID);

/* Added by KLSRINI */
BOOL_T TCP6_IsSocketBoundToVPN(UINTPTR ulSocket);

/* Added by karthik for TCP6 connection statistics */
ULONG TCP6_ResetConnectionStats (TCP6CONNINFO_S *pstTCP6ConnInfo);

/* Added by Srinivas for TCP6 connection statistics */
ULONG TCP6_GetConnectionStats(TCP6CONNINFO_S *pstTCP6ConnInfo,
                                           TCP6PERCONNSTAT_S *pstPerTCP6Stat);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
