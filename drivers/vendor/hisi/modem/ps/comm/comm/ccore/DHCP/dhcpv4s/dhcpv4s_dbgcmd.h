#ifndef    _DHCPV4S_DBGCMD_H_
#define    _DHCPV4S_DBGCMD_H_

#define  DHCPV4S_MAX_INTSTRING_LEN 32

#ifdef __WIN32_PLATFORM__
#define DHCPS_DebugPrint DHCPS_DebugOut_Stub
#else
#define DHCPS_DebugPrint(level, fmt...) \
        /*lint -e774*/                     \
        if(g_ulDhcpsPrintLevel || (PTM_LOG_ERR >= (level))){DHCPS_DebugOut(level, __FILE__, __LINE__, __FUNCTION__, ##fmt);} \
        /*lint +e774*/                      
    
#endif

extern ULONG g_ulDhcpsPrintLevel;
extern VOID DHCPS_DebugOut_Stub(ULONG ulLevel, CHAR *pszFormat, ...);
extern VOID DHCPV4S_ShowSwtichCommand(ULONG argc,CHAR *argv[]);
extern VOID DHCPV4S_ShowExpired(ULONG argc,CHAR *argv[]);
extern VOID DHCPV4S_ShowCode( UCHAR *pucMsg, USHORT usLen );
extern VOID DHCPV4S_ShowDbgCommand( ULONG argc,CHAR *argv[] );
extern VOID DHCPS_ShowLEASE(  ULONG argc, CHAR * argv [] );
extern VOID DHCPV4S_ShowFailCounter(  ULONG argc, CHAR * argv [] );
extern VOID DHCPS_Debug_ShowDbgCnt(ULONG argc, CHAR*argv[]);
extern VOID DHCPS_CLEAN_FAIL(ULONG argc, CHAR*argv[]);
extern VOID DHCPS_CleanStateMachine();
extern VOID DHCPS_ShowStateMachine();
extern VOID DHCPS_ShowLEASETIMER(  ULONG argc, CHAR * argv [] );
extern VOID DHCPS_ShowStateTIMER(  ULONG argc, CHAR * argv [] );
extern VOID DHCPS_ShowStatisc(ULONG argc, CHAR*argv[]);
extern VOID DHCPS_CleanStatisc(ULONG argc, CHAR*argv[]);
extern VOID DHCPV4S_DebugShowMemInfo(ULONG argc, CHAR* argv[]);
extern VOID DHCPS_DebugPrintLevelSet( ULONG ulArgc, CHAR *szArgv[] );
VOID DHCPS_DebugOut(ULONG ulLevel, CHAR* pszFile, ULONG ulLineNo, CHAR *pszFuncName, CHAR *pszFormat, ...);

extern VOS_UINT32 CdbGetApnIndexByApnName(VOS_UINT8 *pucAPNName,  VOS_UINT16 *pusAPNIndex );

extern VOID DHCPV4S_OutString(CHAR *fmt,...);


#endif
