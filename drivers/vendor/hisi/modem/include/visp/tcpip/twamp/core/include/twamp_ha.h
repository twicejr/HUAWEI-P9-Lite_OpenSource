

#ifdef __cplusplus
extern "C"
{
#endif

#include "twamp/core/include/twamp_ext.h"
#include "twamp/core/include/twamp_inc.h"

/* Whether TWAMP was marked by the initialization */
extern ULONG g_ulHATwampExist;

#define TWAMP_MAX_BATCHMSG_LEN LEN_2048


typedef struct tagTwampReflectorADDConfigBakMSG
{
    LONG lServSock;
    ULONG ulReflectorID;
    USHORT usUdpPortStart;   /*Start of the UDP Port range */
    USHORT usUdpPortEnd;     /*End of the UDP Port range */
    ULONG ulServerIp;        /* Server address */
    ULONG ulVrfIndex;        /* VRF Index, RNC will not use, value set to 0xffffffff in case of RNC */
    ULONG ulMaxClient;       /* Max Client supported,  If 0 is passed then it will refer to the global Config*/
    ULONG ulMaxTestSession;  /* Max test sessions supported per Reflector,  If 0 is passed then it will refer to the global Config*/
    ULONG ulSerWaitTime;     /* Server wait time, If 0 is passed then it will refer to the global Config*/
    ULONG ulRefWaitTIme;     /* Ref wait time,  If 0 is passed then it will refer to the global Config*/
    USHORT usTcpPort;        /* Source TCP port to listen control connection per reflector */
    UCHAR ucModes;           /* Integrity/security mode */
    UCHAR  ucCtrlDscp;      /* Control DSCP Value for IP_TOS option */
    ULONG ulNumSockOptions;
    ULONG ulKeepAliveFlag;
    USHORT usKeepintvl;          /* second */
    USHORT usKeepcount;       /* keepintvl's count */
}TWAMP_REFLECTOR_ADD_CONFIG_BAK_MSG_S;



typedef struct tagTwampSetupResponsePktBak
{
    ULONG ulModes;
    ULONG ulKeyID[20];
    ULONG ulToken[16];
    ULONG ulClientIV[4];

} TWAMP_SETUP_RESPONSE_PKT_BAK_S;


typedef struct tagTwampReqSessionPktBak
{
    UCHAR ucCmdid;
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucIPVN : 4;
    UCHAR ucMBZ : 4;
#else
    UCHAR ucMBZ : 4;
    UCHAR ucIPVN : 4;
#endif
    UCHAR ucConfSender;
    UCHAR ucConfReceiver;
    ULONG ulScheduleSlot;
    ULONG ulPacketNum;
    USHORT usSenderPort;
    USHORT usReceiverPort;
    ULONG aulSenderAddr[4];
    ULONG aulReceiveraddr[4];
    ULONG aulSID[4];
    ULONG ulPadLen;
    ULONG aulStartTime[2];
    ULONG aulTimeOut[2];
    ULONG ulTypeP;
    ULONG ulMBZ[2];
    ULONG ulHMAC[4];
}TWAMP_REQUEST_SESSION_PKT_BAK_S;

typedef struct tagTwampSessionStartPktBak
{
    UCHAR ucCmdid;
    UCHAR ucMBZ[15];
    ULONG ulHMAC[4];

} TWAMP_SESSION_START_PKT_BAK_S;


typedef struct tagTwampSessionStopPktBak
{
    UCHAR ucCmdid;
    UCHAR ucAccept;
    UCHAR ucMBZ[2];
    ULONG ulSessionCount;
    ULONG ulMBZ[2];
    ULONG ulHMAC[4];

} TWAMP_SESSION_STOP_PKT_BAK_S;


typedef struct tagTcpipTwampReflNotifyBak
{
    ULONG ulEvent;           /*Event of type  TWAMP_REFL_EVENT_E */
    ULONG ulSessionId;       /*Session Id */
    ULONG ulReflectorId;     /*Responder id */
    ULONG ulVrfId;
} TWAMP_REFL_NOTIFY_BAK_MSG_S;



typedef struct tagTWAMP_REFLECTOR_ADD_CTRL_SESSION_MSG
{
    ULONG ulReflectorID;
    LONG lChildSock;
    ULONG ulPeerIP;
    USHORT usPeerPort;
    USHORT usPad;
    ULONG ulState;
} TWAMP_REFLECTOR_ADD_CTRL_SESSION_MSG;

typedef struct tagTWAMP_REFLECTOR_DEL_CTRL_SESSION_MSG
{
    ULONG ulReflectorID;
    LONG lChildSock;
} TWAMP_REFLECTOR_DEL_CTRL_SESSION_MSG;

typedef struct tagTWAMP_REFLECTOR_DEL_TEST_SESSION_MSG
{
    ULONG ulReflectorID;
    ULONG ulTestSessionID;
} TWAMP_REFLECTOR_DEL_TEST_SESSION_MSG;


typedef struct tagTWAMP_REFLECTOR_PROC_SETUP_RESPONSE_MSG
{
    LONG lChildSock;
    TWAMP_SETUP_RESPONSE_PKT_BAK_S stSetupResponsePkt;
} TWAMP_REFLECTOR_PROC_SETUP_RESPONSE_MSG;

typedef struct tagTWAMP_REFLECTOR_PROC_REQ_SESSION_MSG
{
    LONG lChildSock;
    TWAMP_REQUEST_SESSION_PKT_BAK_S stReqSessionPkt;
} TWAMP_REFLECTOR_PROC_REQ_SESSION_MSG;

typedef struct tagTWAMP_REFLECTOR_PROC_START_SESSION_MSG
{
    LONG lChildSock;
    TWAMP_SESSION_START_PKT_BAK_S stSessionStartPkt;
} TWAMP_REFLECTOR_PROC_START_SESSION_MSG;

typedef struct tagTWAMP_REFLECTOR_PROC_STOP_SESSION_MSG
{
    LONG lChildSock;
    TWAMP_SESSION_STOP_PKT_BAK_S stSessionStopPkt;
} TWAMP_REFLECTOR_PROC_STOP_SESSION_MSG;


typedef struct tagTWAMP_PACKET_HEAD_BAK
{
    USHORT usType;           /*HA Message Type*/
    USHORT usLen;            /* HA Message length */
} TWAMP_PACKET_HEAD_BAK_S;

typedef struct tagTcpipTWAMP_SockOption_Bak
{
    ULONG ulLevel;
    ULONG iOptName;
    ULONG ulOptLen;
}TCPIP_TWAMP_SOCK_OPTIONS_BAK_S;


typedef struct tagTcpipTwampCtrlClientStateBak
{
    ULONG ulClientId;
    ULONG  ulState;
}TCPIP_TWAMP_CTRLCLIENT_STATE_BAK_S;

/*Sender Identifier Information*/
typedef struct tagTwampSenderInfo
{
    ULONG ulClientId;                   /*Client Id*/
    ULONG ulSenderId;                 /*SenderId*/
    ULONG ulEvent;                      /* Sender Event*/
}TWAMP_SENDER_INFO_S;


typedef struct tagTcpipTwampSenderConfBakUp
{
    ULONG ulPktSizeType;            /* Packt size type(fixed, random) */
    ULONG ulPktSize;                /* Packt size */
    ULONG ulPktIntervalType;        /* Packt Interval type(fixed, random) */
    ULONG ulPktInterval;            /* Packt Interval,seconds */
    ULONG ulTimeOut;                /* Reflector must wait after receieve a stop-session message,seconds */
    USHORT usSrcPort;               /* Source UDP port, test packets will be initiated */
    USHORT usDestPort;              /* Dest UDP port, to which test packets will be sent */
    ULONG ulWaitTime;               /* wait time for sender session timeout in PPI */
    UCHAR ucDscp;                   /* Prioritize test packets */
    UCHAR reserved[3];
}TCPIP_TWAMP_SENDER_CONF_BAKUP_S;


/*Backup structure for the Sender configuration*/
typedef struct tagTwampSenderConfBak
{
    TWAMP_SENDER_INFO_S stSenderInfo;  /*SenderInfo*/
    TCPIP_TWAMP_SENDER_CONF_BAKUP_S stTwampSenderConf; /*Sender Configuration*/
}TWAMP_SENDER_CONF_BAK_S;

typedef struct tagTwampSenderBakUp
{
    ULONG ulSenderID;
    TCPIP_TWAMP_SENDER_CONF_BAKUP_S stSenderConfig;
    ULONG ulState;
    ULONG aulSID[4];
    USHORT usServUDPPort;
}TWAMP_SENDER_BAKUP_S;


/*Backup structure for the Sender Session Information*/
typedef struct tagTwampSenderSessionBak
{
    ULONG ulClientId;     /*Client Id*/
    TWAMP_SENDER_BAKUP_S stSenderInfo; /*Sender Information*/
}TWAMP_SENDER_SESSION_BAK_S;



typedef struct tagTcpipTwampCtrlClientConfBakUp
{
    ULONG ulSrcIp;        /* Client IP over which a TWAMP control connection is initiated. */
    ULONG ulPeerIp;       /* Server IP to which a TWAMP control connection is initiated. */
    ULONG ulVrfIndex;     /* VRF Index */
    USHORT usSrcPort;     /* Client TCP port over which a TWAMP control connection is initiated. */
    USHORT usDestPort;    /* Server TCP port to which a TWAMP control connection is initiated. */
    ULONG  ulNumSockOptions;
    TCPIP_TWAMP_SOCK_OPTIONS_S *pstSockOption;
    UCHAR  ucModes;       /* Integrity/security mode */
    UCHAR  ucCtrlDscp;    /*Controle Tcp Session Dscp Value*/
    UCHAR  reserved[2];
}TCPIP_TWAMP_CTRLCLIENT_CONFIG_BAKUP_S;



typedef struct tagTcpipTwampCtrlClientConfBak
{
    ULONG ulClientId;
    ULONG ulState;
    TCPIP_TWAMP_CTRLCLIENT_CONFIG_BAKUP_S stClientCntrlConfig;
}TCPIP_TWAMP_CTRLCLIENT_CONFIG_BAK_S;



typedef struct tagTwampClientBakUp
{
    ULONG ulClientID;
    TCPIP_TWAMP_CTRLCLIENT_CONFIG_BAK_S stClientConfig;
    LONG lClientSockFd;
    ULONG ulConnectTime;
    ULONG ulSenderCount;
    ULONG ulStartSessionCount;
    ULONG ulState;
    ULONG ulServStartTimeHigh;
    ULONG ulServStartTimeLow;
    TWAMP_SENDER_S *pstSenderList;
    USHORT usSrcPort;
    USHORT usPad;
}TWAMP_CLIENT_BAKUP_S;


typedef struct tagTcpipTwampReflGConfBak
{
    ULONG ulMaxRefl;         /*Max Reflectors*/
    ULONG ulSysMaxTestSession;  /*Max test sessions supported by the System*/
    ULONG ulSysMaxClient;      /*Maximum number of Client Supported by the System*/
    ULONG ulMaxClient;       /*Max Client supported*/
    ULONG ulMaxTestSession;  /*Max test sessions supported per Reflector*/
    ULONG ulSerWaitTime;     /*Server wait time*/
    ULONG ulRefWaitTime;     /*Ref wait time*/
    USHORT usUdpPortStart;   /*Start of the UDP Port range */
    USHORT usUdpPortEnd;     /*End of the UDP Port range */
}TCPIP_TWAMP_REFL_GCONFIG_BAK_S;



typedef struct tagTwampReflectorTestSessionBak
{
    LONG lChildSock;
    ULONG ulState;
    ULONG ulDSCP;
    ULONG ulClientIP;
    ULONG ulServerIP;
    USHORT usClientPort;
    USHORT usServerPort;
    ULONG aulTimeout[2];
    ULONG aulStartTime[2];
    ULONG aulSID[4];
    ULONG ulPacketCount;
    ULONG ulTestSessionID;

}TWAMP_REFL_TEST_SESS_BAK_MSG_S;








/*Ha Message type enum for TWAMP */
typedef enum tagTWAMP_HA_MSG_TYPE
{
    TWAMP_REF_GLOBAL_CONFIG_BAK,
    TWAMP_CLIENT_CONFIG_BAK,
    TWAMP_CLIENT_CONFIG_DELETED_BAK,
    TWAMP_CLIENT_UPDT_STATE_BAK,
    TWAMP_CLIENT_CORE_SESSION_BAK,
    TWAMP_SENDER_CONF_BAK,
    TWAMP_SENDER_DEL,
    TWAMP_SENDER_NOTIFY,
    TWAMP_SENDER_UPDT_SHELL_STATE_BAK,
    TWAMP_SENDER_SESSION_BAK,
    TWAMP_REF_ADD_CONFIG_BAK,
    TWAMP_REF_DEL_CONFIG_BAK,
    TWAMP_REF_ADD_CTRL_SESSION_BAK,
    TWAMP_REF_PROC_SETUP_RESPONSE_PKT_BAK,
    TWAMP_REF_PROC_REQ_SESSION_PKT_BAK,
    TWAMP_REF_PROC_START_SESSION_PKT_BAK,
    TWAMP_REF_PROC_STOP_SESSION_PKT_BAK,
    TWAMP_REF_DEL_CTRL_SESSION_BAK,
    TWAMP_REF_DEL_TEST_SESSION_BAK,
    TWAMP_REF_NOTIFY_SESSION_BAK,
    TWAMP_REF_ADD_TEST_SESSION_BAK,
    TWAMP_REF_BATCHADD_REFCONFIG_BAK,
    TWAMP_REF_BATCHADD_REFCTRLSESSION_BAK,
    TWAMP_REF_BATCHADD_REFTESTSESSION_BAK,


    TWAMP_MSGTYPE_MAX
} TWAMP_HA_MSG_TYPE;


extern VOID TWAMP_HA_Register(VOID);


extern ULONG TWAMP_HA_Smooth(VOID);


extern ULONG TWAMP_HA_BatchBackup(VOID);



extern ULONG TWAMP_HA_Input(UCHAR *pBuf, ULONG ulMsgLen);

extern ULONG TWAMP_HA_BuildSendOnePacket(USHORT usType, VOID * pucData, USHORT usInBufLen);

extern ULONG TWAMP_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);

extern VOID TWAMP_HA_BuildOnePacket(USHORT usType, VOID * pucData, VOID *pucInBuf, USHORT usInBufLen);

extern ULONG TWAMP_HA_EncodeClientConfigData(UCHAR *pucBackupBuffer, TCPIP_TWAMP_CTRLCLIENT_CONFIG_S  *pstClientConfigData);

extern ULONG TWAMP_HA_DecodeClientConfigData(UCHAR *pucRcvBuffer, TCPIP_TWAMP_CTRLCLIENT_CONFIG_BAK_S  *pstClientConfigBakData);

extern ULONG TWAMP_Add_SenderInStandBy(TWAMP_SENDER_SESSION_BAK_S *pstSenderSess);

extern VOID TWAMP_HA_ClearClient(VOID);

extern ULONG TWAMP_HA_Clean(VOID);


extern VOID TWAMP_BuildReflectorAddConfigMSG(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflData,
                                                                                     TWAMP_REFLECTOR_ADD_CONFIG_BAK_MSG_S *pstMsg);




extern VOID TWAMP_ParseReflectorAddConfigMSG(TWAMP_REFLECTOR_ADD_CONFIG_BAK_MSG_S *pstMsg,
                                                                                    TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflData);




extern VOID TWAMP_BuildReflectorNotifyMSG(TCPIP_TWAMP_REFL_NOTIFY_S *pstData,
                                                                                     TWAMP_REFL_NOTIFY_BAK_MSG_S *pstMsg);


extern VOID TWAMP_ParseReflectorNotifyMSG(TWAMP_REFL_NOTIFY_BAK_MSG_S *pstMsg,
                                                                                    TCPIP_TWAMP_REFL_NOTIFY_S *pstData);



extern VOID TWAMP_Shell_ClearClientFromCore(VOID);

extern ULONG TWAMP_HA_ClientCfgBatchBak(VOID);
extern ULONG TWAMP_HA_SenderCfgBatchBak(VOID);
extern ULONG TWAMP_HA_ClientCoreSessionBatchBak(VOID);



#ifdef __cplusplus
}
#endif
