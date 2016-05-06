
#ifndef _TWAMP_SH_H_
#define _TWAMP_SH_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
ULONG TWAMP_Shell_Init(ULONG ulTWAMPTaskPri);
*/

/****************************************************/
/*structures used in shell config*/


typedef struct tagTwampConfiglist
{
    ULONG ulClientId;
    TCPIP_TWAMP_CTRLCLIENT_CONFIG_S* pstClientConfigdata;
    struct tagTwampConfiglist *pNext;
    struct tagTwampSenderconfiglist *pSenderConfigList;
    ULONG ulReqTimestamp;
    ULONG ulStateTimestamp;
    ULONG ulStateTimestampHigh;
    ULONG ulConfigState;
    ULONG ulCoreState;
    ULONG ulSenderCount;
    ULONG ulSendToCoreFlag;
    ULONG ulSenderSuccessCount;
    ULONG ulTotalSockOptionsSizeforHA;
    ULONG ulDelSenderTimestamp;
} TWAMP_CONFIG_CLI_LIST_S;


typedef struct tagTwampSenderconfiglist
{
    ULONG ulClientId;
    ULONG ulSenderId;
    TCPIP_TWAMP_SENDER_CONF_S * pstsenderConfigdata;
    struct tagTwampSenderconfiglist *pNextSender;
    ULONG ulReqTimestamp;
    ULONG ulSessTimeStampHigh;
    ULONG ulSessTimeStampLow;
    ULONG ulConfigState;
    ULONG ulCoreState;
    UCHAR ucIsUsrTimeOut;
    UCHAR ucReserved[3];
}TWAMP_CONFIG_SENDER_LIST_S;



/*****************************************************/
/*Macros used in shell config*/

/*TWAMP configuration manager commands types to be issued*/
#define TWAMP_CONFIG_CLIENT_ADD   0
#define TWAMP_CONFIG_CLIENT_DEL   1
#define TWAMP_CONFIG_SENDER_ADD   2
#define TWAMP_CONFIG_SENDER_DEL   3



#define TWAMP_BUFF_SIZE  2*512

#define TWAMP_UPDATE_LAST_CLIENT(pstCurrConfigClientData) g_pstTwampConfigMnglistHead = pstCurrConfigClientData->pNext;

#define TWAMP_UPDATE_LAST_SENDER(Client, Sender) Client->pSenderConfigList = Sender;


/******************************************************/




/*Callback function to notify the client test session status*/
typedef ULONG (*TWAMP_SHELL_HOOK_SESS_FUNC)
(
    ULONG  ulClientId,
    ULONG  ulSenderId,
    ULONG  ulState
);


/*Callback function to notify the client test session status*/
typedef ULONG (*TWAMP_SHELL_HOOK_CTRL_FUNC)
(
    ULONG  ulClientId,
    ULONG  ulState
);

//extern VOID TWAMP_Begin_Config_PT();
//extern VOID TWAMP_End_Config_PT();

extern ULONG TWAMP_ShellConfigInit(VOID);

extern ULONG TWAMP_ShellConfigDeInit(VOID);

extern VOID TWAMP_MngConfigTimer(VOID *);
extern TWAMP_CONFIG_CLI_LIST_S * TWAMP_GetClientConfigData(VOID);
extern ULONG TWAMP_SendCommandToCore(VOID * pstConfigData, ULONG ulCommandType);
extern ULONG TWAMP_AddCommandToMngList(TWAMP_CONFIG_CLI_LIST_S * pstClientConfigCommadData);
extern ULONG TWAMP_AddSenderToConfigMngList(TWAMP_CONFIG_SENDER_LIST_S * pstSenderConfigCommadData);
extern ULONG TWAMP_DelCommandFromMngList(TWAMP_CONFIG_CLI_LIST_S * pstClientConfigCommadData);
extern ULONG TWAMP_DelSenderFromConfigMngList(TWAMP_CONFIG_SENDER_LIST_S * pstSenderConfigCommadData);
extern VOID TWAMP_ProcInProgressSenderConfigData(TWAMP_CONFIG_CLI_LIST_S* pstClientConfigdata);
extern TWAMP_CONFIG_SENDER_LIST_S* TWAMP_GetNextSenderConfigData(TWAMP_CONFIG_CLI_LIST_S* pstClientConfigdata);
extern ULONG TWAMP_DelSenderConfig(ULONG ulClientId, ULONG ulSenderId);
extern ULONG TWAMP_CallUsrClientNotifyHook(ULONG ulClientId, ULONG ulState);
extern ULONG TWAMP_CallUsrSenderNotifyHook(ULONG ulClientId, ULONG ulSenderId, ULONG ulState);
extern TWAMP_CONFIG_SENDER_LIST_S* TWAMP_GetSenderConfigDataFromSenderId(TWAMP_CONFIG_SENDER_LIST_S* pstSenderConfigdata, ULONG ulSenderId);
extern ULONG TWAMP_ShellCtrlStatusNotify(ULONG  ulClientId, ULONG  ulState);
extern ULONG TWAMP_ShellSenderStatusNotify(ULONG  ulClientId, ULONG ulSenderId, ULONG  ulState);

extern ULONG TWAMP_DelClientCtrlConfig(ULONG ulClientId);

extern ULONG TWAMP_GetClientShellState(ULONG ulClientId, TCPIP_TWAMP_CTRLCLIENT_SESS_S *pstCtrlSessInfo);
extern TWAMP_CONFIG_CLI_LIST_S * TWAMP_GetPrevClientConfigNode(TWAMP_CONFIG_CLI_LIST_S * pstClientConfigCommadDataCurr);

extern TWAMP_CONFIG_SENDER_LIST_S * TWAMP_GetPrevSenderConfigNode(TWAMP_CONFIG_SENDER_LIST_S * pstSenderConfigCommadDataCurr);

extern ULONG TWAMP_ShowTwampTestSessInfo(ULONG ulClientId, ULONG ulSenderId);

extern ULONG TWAMP_GetTwampTestSessInfo(ULONG ulClientId, ULONG ulSenderId,
                                                      TCPIP_TWAMP_TEST_SESS_INFO_S *pstTestSessionInfo);

extern TWAMP_CONFIG_CLI_LIST_S * TWAMP_GetClientConfigDataFromClientId(ULONG ulClientId);


extern VOID TWAMP_SenderNotifyTimeOutEvent(TWAMP_CONFIG_CLI_LIST_S * pstClientConfigCommadData);


extern ULONG TWAMP_HA_CopyOneClientConfigData(UCHAR **pucData, UCHAR **pucEnd, TWAMP_CONFIG_CLI_LIST_S *pstCurrConfigClientData);

extern ULONG TWAMP_HA_SenderConfigBack(TWAMP_CONFIG_SENDER_LIST_S *pSenderConfigList);

extern ULONG TWAMP_HA_CopyOneSenderConfigData(UCHAR **pucData, UCHAR** pucEnd, TWAMP_CONFIG_SENDER_LIST_S *pstSenderConfig);

extern ULONG TWAMP_HA_CopyOneClientSessionData(UCHAR **pucData, UCHAR **pucEnd, TWAMP_CLIENT_S *pstClient);

extern ULONG TWAMP_HA_CopyOneSenderSessionData(UCHAR** pucData, UCHAR **pucEnd,  TWAMP_SENDER_S *pstSenderSess);

extern ULONG TWAMP_ShellCtrlTimerHookUpdate(ULONG  ulClientId);

extern ULONG TWAMP_RegClientCtrlCoreTimeoutHook(TWAMP_CORE_HOOK_CLIENT_CTRL_TIMEOUTFUNC pfnCtrlCoreTimeoutHook);





extern TCPIP_TWAMP_CTRLCLIENT_CONFIG_S * TWAMP_AllocateClientConfigData(TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstClientConf, ULONG *pulTotalSockOptionsSizeforHA);



extern VOID TWAMP_FreeClientConfigData(TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstClientConfigData);



#ifdef __cplusplus
}
#endif

#endif


