/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              diagnose_sh.h
*
*  Project Code: VISPV100R007C02
*   Module Name: i3agent
*  Date Created: 2008-07-30
*        Author: L00105073
*   Description: ’Ô∂œ–≈œ¢≈‰÷√API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-29   L00105073               Create
*
*******************************************************************************/

#ifndef DIAGNOSE_SH_H
#define DIAGNOSE_SH_H

#ifdef  __cplusplus
    extern "C"{
#endif

typedef struct tagTCPIP_DiagnosticsInfo_S
{
    ULONG ulTraceLevel;
    ULONG ulTraceLevelVerify;
    CHAR* pszTraceFilterInFile;
    CHAR* pszTraceFilterOutFile;
    CHAR* pszTraceFilterInFunc;
    CHAR* pszTraceFilterOutFunc;
    ULONG ulIpsInfo;
    ULONG ulEventInfo;
    ULONG ulTimerInfo;
    CHAR* pszIpsFilterInProc;
    CHAR* pszIpsFilterOutProc;
    CHAR* pszIpsFilterInType;
    CHAR* pszIpsFilterOutType;
    ULONG ulVerifyMem;
    ULONG ulVerifyMemPerNSchedules;
    ULONG ulCheckMemory;
    ULONG ulAssertBehave;
    ULONG ulDumpOnAssert;
    ULONG ulPdLogLevel;
    ULONG ulPdLogDetail;
    ULONG ulPdLogDev;
    ULONG ulPdLogVerbose;
    CHAR* pszLogFilterInProc;
    CHAR* pszLogFilterOutProc;
    CHAR* pszLogFilterInMsgid;
    CHAR* pszLogFilterOutMsgid;
    CHAR* pszStopLogs;
    ULONG ulStopOnAssert;
}TCPIP_DIAGNOSTICS_INFO_S;

extern TCPIP_PROT_DIAGNOSTICS_HOOK_FUNC g_diagnostics_output;

extern ULONG Diag_CheckStopLogs(CHAR* pszStopLogs);
extern ULONG TCPIP_GetI3stubStatus (ULONG ulIndex, ULONG* pulOperStatus);
extern ULONG TCPIP_GetDiagnosticsPara(TCPIP_DIAGNOSTICS_INFO_S* pstDiagnosticsInfo);
extern ULONG Diag_CheckCommonFilterStr(CHAR* pszIpsFilterStr);

#ifdef  __cplusplus
}
#endif

#endif
