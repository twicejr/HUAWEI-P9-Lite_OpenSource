

#ifdef __cplusplus
extern "C" {
#endif




typedef struct tagTcpipTwampClientQueueData
{
TCPIP_TWAMP_CTRLCLIENT_CONFIG_S stClientConfig;
LONG lServSock;
ULONG ulReflectorID;
ULONG ulTaskID;
}TCPIP_TWAMP_CLIENT_QUEUE_DATA_S;



typedef struct tagTcpipTwampReflectorQueueData
{
TCPIP_TWAMP_REFL_CONFIG_S stReflectorConfig;
LONG ServSock;
ULONG ulReflectorID;
ULONG ulTaskID;
}TCPIP_TWAMP_REFLECTOR_QUEUE_DATA_S;



extern ULONG TWAMP_Init(ULONG ulTWAMPTaskPri, ULONG ulTwampTaskStackSize);


extern ULONG TWAMP_ClientInit(ULONG ulTWAMPTaskPri, ULONG ulTwampTaskStackSize);

extern ULONG TWAMP_ReflectorInit(ULONG ulTWAMPTaskPri, ULONG ulTwampTaskStackSize);

extern ULONG TWAMP_ClientDeInit(VOID);


extern VOID TWAMP_CLI_TaskMain(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
extern ULONG TWAMP_ClientAlloc(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData, TWAMP_SESSION_NODE_S **ppOutput);
extern ULONG TWAMP_ClientConnect(TWAMP_SESSION_NODE_S *pSessionNode);
extern VOID TWAMP_RunClientCTRLSessionFSM(TWAMP_SESSION_NODE_S *pstCtrlSession,VOID *pvPkt);
extern VOID TWAMP_ProcessClientReConnectFDSet(ULONG ulCount,fd_set * pstReconnectFDset);
extern VOID TWAMP_ProcessClientControlData(ULONG ulCount, fd_set * pstReconnectFDset);

extern ULONG TWAMP_ClientClose(ULONG ulClientID);
extern ULONG TWAMP_RegClientCtrlCoreHook(TWAMP_CORE_HOOK_CLIENT_CTRL_FUNC pfnCtrlCoreHook);
extern ULONG TWAMP_RegSenderSessCoreHook(TWAMP_CORE_HOOK_SENDER_SESS_FUNC pfnSessCoreHook);

extern ULONG TWAMP_CreateMonitorTime(VOID);

#ifdef __cplusplus
}
#endif

