
#ifndef _TWAMP_TYPE_H_
#define _TWAMP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTwampReflectorQueueData
{
    TCPIP_TWAMP_REFL_CONFIG_S stReflectorConfig;
    LONG lServSock;
    ULONG ulReflectorID;
    USHORT usUdpPortStart;   /*Start of the UDP Port range */
    USHORT usUdpPortEnd;     /*End of the UDP Port range */
    ULONG  ulKeepAliveFlag;
    USHORT usKeepintvl;          /* second */
    USHORT usKeepcount;       /* keepintvl's count */
}TWAMP_REFLECTOR_QUEUE_DATA_S;


typedef struct tagTwampClientQueueData
{
    TCPIP_TWAMP_CTRLCLIENT_CONFIG_S stClientConfig;
    TCPIP_TWAMP_SENDER_CONF_S stSenderConfig;
    LONG lClientSockFd;
    ULONG ulClientID;
    ULONG ulSenderID;
    ULONG ulOperType;
}TWAMP_CLIENT_QUEUE_DATA_S;


typedef struct tagTwampRecvBuffer
{
    CHAR acBuff[TWAMP_RECV_BUFFER_LEN];
    ULONG ulWriteIndex;
}TWAMP_RECV_BUFFER_S;


typedef struct tagTwampClient TWAMP_CLIENT_S;

typedef struct tagTwampSender TWAMP_SENDER_S;

struct tagTwampClient
{
    ULONG ulClientID;
    TCPIP_TWAMP_CTRLCLIENT_CONFIG_S stClientConfig;
    LONG lClientSockFd;
    ULONG ulConnectTime;
    ULONG ulSenderCount;
    ULONG ulStartSessionCount;
    ULONG ulState;
    ULONG ulServStartTimeHigh;
    ULONG ulServStartTimeLow;
    TWAMP_RECV_BUFFER_S stRecvBuffer;
    TWAMP_SENDER_S *pstSenderList;
    USHORT usSrcPort;
    USHORT usPad;
};

struct tagTwampSender
{
    ULONG ulSenderID;
    TCPIP_TWAMP_SENDER_CONF_S stSenderConfig;
    ULONG ulState;
    ULONG aulSID[4];
    USHORT usServUDPPort;
    TWAMP_CLIENT_S *pstClient;
    TWAMP_SENDER_S *pstNext;
    TWAMP_SENDER_S *pstPrev;
    ULONG ulPpiDownloadFlag;
};


typedef struct tagTwampSessionNode
{
    TCPIP_TWAMP_CTRLCLIENT_SESS_S *pstCntrlClientSession;
    LONG lClientSockFd;
    ULONG ulClientID;
}TWAMP_SESSION_NODE_S;


typedef struct tagTwampSessionIdQueue
{
    ULONG ulUseIndex;
    ULONG ulReleaseIndex;
    ULONG ulUsedNum;
    USHORT usSessionIdStart;   /*Start of the UDP Port range */
    USHORT usSessionIdEnd;     /*End of the UDP Port range */
    USHORT *pQueue;
} TWAMP_SESSIONID_QUEUE_S;

typedef struct tagTwampIpPortPool
{
    ULONG ulPoolIP;
    USHORT usUdpPortStart;   /*Start of the UDP Port range */
    USHORT usUdpPortEnd;     /*End of the UDP Port range */
    ULONG aulPortPool[TWAMP_MAX_PORT_POOL_SIZE];
    ULONG ulPortUsedNum;    
    ULONG ulClientCount;    
    struct tagTwampIpPortPool *pstPoolNext;
    struct tagTwampIpPortPool *pstPoolPrev;

} TWAMP_IP_PORT_POOL_S;


typedef struct tagTwampReflector TWAMP_REFLECTOR_S;

typedef struct tagTwampReflectorCtrlSession TWAMP_REFLECTOR_CTRL_SESSION_S;
typedef struct tagTwampReflectorTestSession TWAMP_REFLECTOR_TEST_SESSION_S;

struct tagTwampReflectorTestSession
{
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
    ULONG ulTestSessStartTimeLow;   /* Lower 32 bit Value. Represents the time when the test session is changed to current state, seconds. It is the time since 1970 */
    ULONG ulTestSessStartTimeHigh;  /* Higher 32 bit value. Represents the time when the test session is changed to current state, seconds. It is the time since 1970  */
    ULONG ulStopSessionTime;
    TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession;
    TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSessionListNext;
    TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSessionListPrev;

};

typedef struct tagTwampReflectorCtrlSession
{
    LONG lChildSock;
    ULONG ulMode;
    ULONG ulState;
    UINTPTR ulServWaitTimerID;
    ULONG ulDSCP;
    ULONG ulTestSessionCount;
    ULONG ulStartTestSessionCount;
    ULONG ulPeerIP;
    USHORT usPeerTCPPort;
    USHORT usPad;
    TWAMP_RECV_BUFFER_S stRecvBuffer;
    TWAMP_REFLECTOR_S *pstReflector;
    TWAMP_REFLECTOR_CTRL_SESSION_S *pstReflectorCtrlSessionListNext;
    TWAMP_REFLECTOR_CTRL_SESSION_S *pstReflectorCtrlSessionListPrev;
    TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSessionTableListNext;
    TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSessionTableListPrev;
    TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSessionList;
    ULONG ulVRFIndex;
    //ULONG ulDisplayState;
} TCPIP_TWAMP_REFLECTOR_CTRL_SESSION_S;

struct tagTwampReflector
{
    ULONG ulReflectorID;
    TCPIP_TWAMP_REFL_CONFIG_S stReflectorConfig;
    LONG lServSock;
    ULONG ulStartTimeSecHigh;
    ULONG ulStartTimeSecLow;
    ULONG ulStartTimeFracSec;
    ULONG ulCtrlSessCount;
    ULONG ulTestSessTableIndex;
    TWAMP_SESSIONID_QUEUE_S stSessionIDQueue;
    TWAMP_IP_PORT_POOL_S *pstIPPortPool;
    TWAMP_REFLECTOR_TEST_SESSION_S **pstTestSessionTable;
    TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSessionList;
    TCPIP_TWAMP_REFL_STATS_S stStatistics;
    ULONG ulKeepAliveFlag;
    USHORT usKeepintvl;          /* second */
    USHORT usKeepcount;       /* keepintvl's count */
    USHORT usUdpPortStart;   /*Start of the UDP Port range */
    USHORT usUdpPortEnd;     /*End of the UDP Port range */
};

typedef enum enumTwampReflectorFSMState
{
    TWAMP_CTRL_SESS_INIT = 0,
    TWAMP_CTRL_SESS_GREETINGS_SENT,
    TWAMP_CTRL_SESS_SETUP_RESPONSE_RECEIVED,
    TWAMP_CTRL_SESS_SERVER_START_SENT,
} TWAMP_REFLECTOR_FSM_STATE;

typedef enum enumTwampReflectorTestSessionState
{
    TWAMP_TEST_SESS_INIT = 0,
    TWAMP_TEST_SESS_STARTED,
    TWAMP_TEST_SESS_STOPPED
} TWAMP_REFLECTOR_TEST_SESSION_STATE;

typedef enum enumTwampAcceptValue
{
    TWAMP_ACCEPT_OK = 0,
    TWAMP_ACCEPT_UNSPECIFIED,
    TWAMP_ACCEPT_INTERNAL_ERROR,
    TWAMP_ACCEPT_NOT_SUPPORTED,
    TWAMP_ACCEPT_PERMANENT_RESOURCE_LIMITATION,
    TWAMP_ACCEPT_TEMPORARY_RESOURCE_LIMITATION,
} TWAMP_ACCEPT_VALUE;

typedef enum enumTwampClientFSMState
{
    TWAMP_CLIENT_CONNECTING = 0,
    TWAMP_CLIENT_SERV_GREETING_WAIT,
    TWAMP_CLIENT_SETUP_RESPONSE_SENT,
    TWAMP_CLIENT_SERV_START_RECV,
    TWAMP_CLIENT_REQUEST_SESSION_SENT,
    TWAMP_CLIENT_START_SESSION_SENT,
    TWAMP_CLIENT_START_SESSION_ACK_RECV
} TWAMP_CLIENT_FSM_STATE;

/*Timer Expiry Function*/
typedef ULONG (*TWAMP_TIMER_EXPIRY_FUN)(ULONG ulId);

typedef struct tagTWAMPTimerNode TWAMP_TIMER_NODE_S;

struct tagTWAMPTimerNode
{
    ULONG ulTimeOut;
    ULONG ulId;
    ULONG ulTableIndex;
    TWAMP_TIMER_NODE_S  *pstTimerNodeNext;
    TWAMP_TIMER_NODE_S  *pstTimerNodePrev;
};

/*TWAMP Timer Structure */
typedef struct tagTwampTimerInfo
{
    ULONG ulTableSize;
    ULONG ulCurIndex;
    TWAMP_TIMER_EXPIRY_FUN pfExpiryFun;
    TWAMP_TIMER_NODE_S  **pstTimerTable;
}TWAMP_TIMER_INFO_S;


#ifdef __cplusplus
}
#endif

#endif

