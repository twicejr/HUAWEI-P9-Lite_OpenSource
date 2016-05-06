
#ifndef _TWAMP_CLIENT_H_
#define _TWAMP_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif



extern VOID TWAMP_Client_TaskMain(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);




extern ULONG TWAMP_Del_Client(TWAMP_CLIENT_S *pstClient,ULONG ulEvent);


extern ULONG TWAMP_Core_AddClient(ULONG ulClientId, TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstClientConf);

extern ULONG TWAMP_Core_DelClient(ULONG ulClientId);


extern VOID TWAMP_ProcClientConfig(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData);


extern ULONG TWAMP_Add_Sender(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData);



extern TWAMP_SENDER_S * TWAMP_Get_Sender(TWAMP_CLIENT_S *pstClient,ULONG ulSenderId);





extern VOID TWAMP_Del_Sender(TWAMP_SENDER_S *pstSender);



extern ULONG TWAMP_Delete_Sender(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData);



extern  ULONG TWAMP_Core_AddSender(ULONG ulClientId,  ULONG ulSenderId,
    TCPIP_TWAMP_SENDER_CONF_S *pstSenderConf);


extern ULONG TWAMP_Core_Delete_Sender(ULONG ulClientId, ULONG ulSenderId);


#ifdef __cplusplus
}
#endif

#endif

