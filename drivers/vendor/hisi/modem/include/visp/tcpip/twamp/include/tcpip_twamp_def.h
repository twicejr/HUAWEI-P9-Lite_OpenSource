/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                            tcpip_twamp_def.h
*
*  Project Code:
*   Module Name: TWAMP DEF
*  Date Created: 2013-03-13
*        Author:
*   Description: Contains the TWAMP Client and the Reflector macros/enums/Structures
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE                            NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-03-13                                             Create
*
*******************************************************************************/
#ifndef __TCPIP_TWAMP_DEF_H__
#define __TCPIP_TWAMP_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define TWAMP_MAX_REFLECTORS                  32              /*Maximum reflectors */
#define TWAMP_MAX_CLIENT_SESS_PER_REFL       160              /*Maximum client Sessions per reflector*/
#define TWAMP_MAX_TEST_SESS_PER_REFL         160              /*Maximum Test sessions per Reflector*/
#define TWAMP_MAX_CTRL_SESSIONS              160              /*Maximum Control sessions*/
#define TWAMP_MAX_CTRL_TEST_SESSIONS         160              /*Maximum Control test sessions*/
#define TWAMP_MAX_SENDER_PER_CLIENT           16              /*Maximum Control test sessions per client */
#define TWAMP_MAX_TEST_SESS         160              /*Maximum Test sessions for the System*/
#define TWAMP_MAX_CLIENT_SESS      160              /*Maximum client Sessions for the system */


#define TWAMP_MIN_UDP_PORT  1024
#define TWAMP_MAX_UDP_PORT 65535

#define TWAMP_MIN_SERVWAIT_TIMEOUT  10 /*Time in Sec*/
#define TWAMP_MIN_REFWAIT_TIMEOUT   10 /*Time in Sec*/
#define TWAMP_MIN_PPIWAIT_TIMEOUT   10 /*Time in Sec*/

#define TWAMP_MAX_SERVWAIT_TIMEOUT  1800 /*Time in Sec*/
#define TWAMP_MAX_REFWAIT_TIMEOUT   1800 /*Time in Sec*/
#define TWAMP_MAX_PPIWAIT_TIMEOUT   1800 /*Time in Sec*/



/*     0                                     1                                      2                                       3
        0  1  2  3  4   5  6  7  8   9  0  1  2   3  4  5  6   7  8  9  0  1   2  3  4   5  6  7  8  9   0  1
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                        Sequence Number                                                                            |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                          Timestamp                                                                                     |
     |                                                                                                                               |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |        Error Estimate                                  |                                                               |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                                                               |
     |                                                                                                                               |
     .                                                                                                                                .
     .                         Packet Padding                                                                                 .
     .                                                                                                                                .
     |                                                                                                                               |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

*/

#define TWAMP_MIN_PACKET_SIZE_UNAUTH 42 /*Minimum TWAMP Test Packet Size (IP+UDP+TWAMP UNAUTHENTICATED HEADER) (20 + 8 + 14)*/




#define TWAMP_DEFAULT_SERVER_PORT 862                      /* Default server port to be used. */
#define TWAMP_DEFAULT_MAX_REFLCTR_COUNT        1       /* Default max count for Reflector. */
#define TWAMP_DEFAULT_MAX_CLIENT_COUNT         8       /* Default max client count.        */
#define TWAMP_DEFAULT_MAX_TESTSESSION_COUNT   16  /* Default max test-session count.  */
#define TWAMP_DEFAULT_UDP_START_PORT        5000     /* Default UDP start port.          */
#define TWAMP_DEFAULT_UDP_END_PORT          5500      /* Default UDP end port.            */
#define TWAMP_DEFAULT_SERVWAIT_TIMEOUT       900   /* Time in Sec. */
#define TWAMP_DEFAULT_REFWAIT_TIMEOUT        900   /* Time in Sec. */



#define TWAMP_UNAUTH_MODE       0x0001   /* Currently only this mode is supported, Unauthenticated. */
#define TWAMP_AUTH_MODE         0x0002    /* TWAMP Authentication mode. */
#define TWAMP_ENCRYPT_MODE      0x0004  /* TWAMP Enc mode.    */

/******************************************************************************
* Input/Output Parameter : UINT32 ulArg0,
*                          UINT32 ulArg1,
*                          UINT32 ulArg2,
*                          UINT32 ulArg3
* Parameter Description    Arguments to be passed when creating the task.
* Return Values            
* Error Codes              
* Note                     Points to function to be used when creating the task.
* Related Topic            
*******************************************************************************/


/*Function pointer to be given as arguement while creating the Task*/
typedef VOID (*TWAMP_TaskStartAddress_PF)( ULONG ulArg0,
                                            ULONG ulArg1,
                                            ULONG ulArg2,
                                            ULONG ulArg3 );


/* Structure to set up socket option. */
  typedef struct tagTcpipTWAMP_SockOption
  {
    ULONG ulLevel;                                                       /* Socket level to be used.*/
    ULONG iOptName;                                                    /* Socket option to be set. */
    CHAR *pOptVal;                                                      /* Socket option value to set to be set. */
    ULONG ulOptLen;                                                   /* Socket option length. */
  }TCPIP_TWAMP_SOCK_OPTIONS_S;

typedef struct tagTcpipTwampReflGConf
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
}TCPIP_TWAMP_REFL_GCONFIG_S;


typedef struct tagTcpipTwampReflConf
{
    ULONG ulServerIp;        /* Server address */
    ULONG ulVrfIndex;        /* VRF Index, RNC will not use, value set to 0xffffffff in case of RNC */
    ULONG ulMaxClient;       /* Max Client supported,  If 0 is passed then it will refer to the global Config*/
    ULONG ulMaxTestSession;  /* Max test sessions supported per Reflector,  If 0 is passed then it will refer to the global Config*/
    ULONG ulSerWaitTime;     /* Server wait time, If 0 is passed then it will refer to the global Config*/
    ULONG ulRefWaitTIme;     /* Ref wait time,  If 0 is passed then it will refer to the global Config*/
    USHORT usTcpPort;        /* Source TCP port to listen control connection per reflector */
    UCHAR ucModes;           /* Integrity/security mode */
    UCHAR  ucCtrlDscp;      /* Control DSCP Value for IP_TOS option */
    ULONG  ulNumSockOptions;    /* Specifies number of socket options to be set. */
    TCPIP_TWAMP_SOCK_OPTIONS_S *pstSockOption;   /* Pointer to socket option structure. */

}TCPIP_TWAMP_REFL_CONFIG_S;


typedef struct tagTcpipTwampReflSessInfo
{
    ULONG ulResponderId;    /* Responder ID */
    ULONG ulState;          /* Control link up/down or session up, Contains any of the value of  TWAMP_RESPONDER_CTRL_STATE_E*/
    ULONG ulSrcIp;          /* Server address */
    ULONG ulDestIp;         /* Client address */
    ULONG ulStartTimeLow;   /* Lower 32 bit Value. Represents the time when server started operating, seconds. It is the time since 1970 */
    ULONG ulStartTimeHigh;  /* Higher 32 bit value. Represents the time when server started operating, seconds. It is the time since 1970  */
    ULONG ulSessStateTimeStmpLow;   /* Lower 32 bit Value. Represents the time when the test session is changed to current state, seconds. It is the time since 1970 */
    ULONG ulSessStateTimeStmpHigh;  /* Higher 32 bit value. Represents the time when the test session is changed to current state, seconds. It is the time since 1970  */
    USHORT usSrcTCPPort;    /* Use server Socket TCP port to receive control packets */
    USHORT usDestTCPPort;   /* Use Client TCP port to send control packets */
    USHORT usSrcUDPPort;    /* Use server UDP port to receive test session packets */
    USHORT usDestUDPPort;   /* Use client UDP port to send test session packets */
    UCHAR ucModes;          /* Integrity/security mode */
    UCHAR ucReqSessionDscp;       /* Control connection DSCP, received in P-type descriptor */
    UCHAR ucSessDscp;       /* Session DSCP, received from TRAN */
    UCHAR  ucCtrlDscp;	/*Parameter for TCP Control Session DSCP*/
    ULONG ulVRFIndex ;       /*VRF Index*/
}TCPIP_TWAMP_REFL_SESS_S;


typedef struct tagTcpipTwampReflStats
{
    ULONG ulNumRecvConn;                          /*  Number of twamp connections Request received. */
    ULONG ulNumRejRecvConn;                     /* Number of twamp connections Request rejected. */
    ULONG ulNumGreetingMesg;                   /* Number of greeting messages. */
    ULONG ulNumSetUpResponse;                 /* Number of setup responses. */
    ULONG ulNumRejSetUpResponse;           /* Number of setup responses rejected. */
    ULONG ulNumServerStart;                   /* Number of server started. */
    ULONG ulNumRequestSession;             /* Number of requested session. */
    ULONG ulNumRejRequestSession;        /* Number of request session rejected. */
    ULONG ulNumAcceptSession;              /* Number of accepted session. */
    ULONG ulNumStartSession;               /* Number of start session. */
    ULONG ulNumRejStartSession;          /* Number of start session rejected. */
    ULONG ulNumStartSessionAck;         /* Number of start session acknowledged. */
    ULONG ulNumStopSession;               /* Number of stop session. */
}TCPIP_TWAMP_REFL_STATS_S;


typedef struct tagTcpipTwampCtrlClientConf
{
    ULONG ulSrcIp;        /* Client IP over which a TWAMP control connection is initiated. */
    ULONG ulPeerIp;       /* Server IP to which a TWAMP control connection is initiated. */
    ULONG ulVrfIndex;     /* VRF Index */
    USHORT usSrcPort;     /* Client TCP port over which a TWAMP control connection is initiated. */
    USHORT usDestPort;    /* Server TCP port to which a TWAMP control connection is initiated. */
    ULONG  ulNumSockOptions; /* Number of socket options. */
    TCPIP_TWAMP_SOCK_OPTIONS_S *pstSockOption;  /* Socket option structure. */
    UCHAR  ucModes;       /* Integrity/security mode */
    UCHAR  ucCtrlDscp;    /*Controle Tcp Session Dscp Value for TOS*/
    UCHAR  reserved[2];
}TCPIP_TWAMP_CTRLCLIENT_CONFIG_S;


typedef struct tagTcpipTwampClientCtrlSess
{
    ULONG ulState;         /* State of the control connection, Contains any of the state  of TWAMP_SESS_STATE_E */
    ULONG ulTimeLow;       /* Lower 32 bit Value. Represents the time when Connection is established in seconds. It is the time since 1970 */
    ULONG ulTimeHigh;      /* Higher 32 bit value. Represents the time when Connection is established in seconds. It is the time since 1970  */
    ULONG ulSrcIp;         /* Client IP */
    ULONG ulPeerIp;        /* Server IP */
    USHORT usSrcPort;      /* Client TCP port */
    USHORT usDestPort;     /* Server TCP port */
    UCHAR ucModes;         /* Integrity/security mode */
    UCHAR  ucCtrlDscp;     /* Control TCP Session DSCP value used for TOS*/
    UCHAR reserved[2];
    ULONG ulVrfIndex;     /*VRF Index*/
}TCPIP_TWAMP_CTRLCLIENT_SESS_S;


typedef struct tagTcpipTwampSenderConf
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
}TCPIP_TWAMP_SENDER_CONF_S;


/*TWAMP PPI Interface structures, Using this structure sender test session information is downloaded to the product */
typedef struct tagPPI_TWAMP_SENDER_SESSION_PARA
{
    ULONG   ulClientId;   /* Client ID. */
    ULONG   ulSenderId;    /* Sender ID. */
    ULONG   ulPktSizeType;     /* Packt size type(fixed, random) */
    ULONG   ulPktSize;         /* Packt size */
    ULONG   ulPktIntervalType; /* Packt Interval type(fixed, random) */
    ULONG   ulPktInterval;     /* Packt Interval,seconds */
    ULONG   ulSrcIp;           /*Source IP in Network Byte Order */
    ULONG   ulDstIp;           /*Destination IP in Network Byte Order */
    USHORT usSrcPort;         /*Source port in Network Byte Order */
    USHORT usDstPort;         /*Destination port in Network Byte Order */
    ULONG   ulTimeOut;       /* Time-out value. */
    ULONG   ulVrfId;          /* VRF-Index. */
    ULONG   ulWaitTime;     /* Wait-time. */
    UCHAR   ucDscp;           /* DSCP value. */
    UCHAR   ucTtl;           /* TTL value. */
    UCHAR   ucSessDscp; /* Modified DSCP in transit during test session packets */
    UCHAR   ucReserved;
} PPI_TWAMP_SENDER_SESSION_PARA;

/*TWAMP PPI Interface structures , Using this structure Responder test session information is downloaded to the product */
typedef struct tagPPI_TWAMP_RESPONDER_SESSION_PARA
{
    ULONG   ulRefTime;      /*REFWAIT Time*/
    ULONG   ulSessionId;    /*Session Id*/
    ULONG   ulReflectorId; /*Responder Id*/
    ULONG   ulSrcIp;     /*Source IP in Network Byte Order */
    ULONG   ulDstIp;     /*Destination IP in Network Byte Order */
    ULONG   ulStartTimeIntegerSec;  /*Session start time in Sec (High)*/
    ULONG   ulStartTimeFracSec;       /*Session Start time in Sec (Low)*/
    USHORT  usSrcPort;   /*Source Port in Network Byte Order */
    USHORT  usDstPort;   /*Destination Port in Network Byte Order */
    ULONG   ulVrfId;        /* VRF-Index. */
    UCHAR   ucReqSessionDscp; /* p-Type discriptor DSCP value to be downloaded to TRAN */
    UCHAR   ucSessDscp; /* Modified DSCP in transit during test session packets */
    UCHAR   ucReserved[2];
} PPI_TWAMP_RESPONDER_SESSION_PARA;


/*Contains the Test session information which will be restrieved through the TCPIP_TWAMP_GetTwampTestSessInfo API*/
typedef struct tagTcpipTwampTestSessInfo
{
    ULONG ulState;          /* State of the session, Contains any of the state  of TWAMP_SESS_STATE_E*/
    ULONG ulSessStateTimeStampLow; /* Lower 32 bit Value. Represents the time when the test session is changed to current state, seconds. It is the time since 1970 */
    ULONG ulSessStateTimeStampHigh; /* Higher 32 bit value. Represents the time when the test session is changed to current state, seconds. It is the time since 1970*/
    USHORT usSrcPort;       /* Source UDP port */
    USHORT usDestPort;      /* Dest UDP port */
    UCHAR ucReqSessionDscp;    /* Control connection DSCP  used for p-Type discriptor*/
    UCHAR ucSessDscp;       /* Session  DSCP,received from TRAN */
    UCHAR reserve[2];
    ULONG ulVRFIndex;       /*VRF Index*/
}TCPIP_TWAMP_TEST_SESS_INFO_S;

/*Twamp PPi hook structure*/
typedef struct tagTCPIP_TWAMP_PPI_HOOK
{
    /*TWAMP PPI Hooks*/
    ULONG (*pfTCPIP_PPI_TWAMP_RESPONDER_Update)(ULONG ulOperType, PPI_TWAMP_RESPONDER_SESSION_PARA *pstRespSess);   /* PPI responder update pointer to function. */
    ULONG (*pfTCPIP_PPI_TWAMP_SENDER_Update)(ULONG ulOperType, PPI_TWAMP_SENDER_SESSION_PARA *pstSendSess);             /* PPI sender update pointer to function. */
}TCPIP_TWAMP_PPI_HOOK_S;


/* Twamp System hook function. */
typedef struct tagTcpipTwampSysHookFun
{
    ULONG (*pfTm_Since1970)(ULONG *pulRetTimeInSecHigh, ULONG *pulRetTimeInSecLow);     /* Points to function returning time in seconds. */
    ULONG (*pfTm_Now)(ULONG *pulRetTimeInMillSecHigh, ULONG *pulRetTimeInMillSecLow);      /* Points to function returning time in milli-seconds. */
    ULONG  (*pfFree)(VOID *pvMemory);                                                                                /* Points to function which frees the memory in heap. */
    VOID * (*pfMalloc)(ULONG ulInfo, ULONG  ulMemSize);                                                        /* Points to function which allocates the memory in heap. */
    ULONG (*pfT_Delete)( ULONG ulTaskID );                                                                          /* Points to function which deletes the task. */
    ULONG (*pfT_Create)(CHAR acTaskName[4],                                                                     /* Points to function which creates the task. */
                                       ULONG ulTaskPriority,
                                       ULONG ulTaskMode,
                                       ULONG ulTaskStackSize,
                                       ULONG aulTaskArg[4],
                                       TWAMP_TaskStartAddress_PF pfTaskStartAddress,
                                        ULONG *pulTaskID );
}TCPIP_TWAMP_SYS_HOOK_FUN_S;

/*TWAMP Responder Control status, These states would be provided in the TCPIP_HOOK_TWAMP_REFL_FUNC hook*/
typedef enum tagTcpipTwampRespCtrlState
{
    TWAMP_REFL_STATE_CTRL_CONN_SUCCESS = 0,                             /* 0. Control Connection Successufl.*/
    TWAMP_REFL_STATE_TEST_SESS_SUCCESS = 1,                             /* 1. Test Session is successuful.*/
    TWAMP_REFL_STATE_UNSPECIFIED_ERROR = 2,                             /* 2. Unspecified error .*/
    TWAMP_REFL_STATE_INTERNAL_ERROR = 3,                                /* 3. Internal Error */
    TWAMP_REFL_STATE_NOT_SUPPORTED = 4,                                 /* 4. Not Supported*/
    TWAMP_REFL_STATE_PERMANENT_RESOURCE_LIMITATION =  5,                /* 4. Permanent resource limitation.*/
    TWAMP_REFL_STATE_TEMPORARY_RESOUCE_LIMITATION = 6,                  /* 5. Temporary resource limitation.*/
    TWAMP_REFL_STATE_SERV_WAIT_TIME_OUT = 7,                            /* 7. Serv Wait Time Out.*/
    TWAMP_REFL_STATE_REF_WAIT_TIME_OUT = 8,                             /* 8. Ref Wait Time Out.*/
    TWAMP_REFL_STATE_IN_PROGRESS = 9,                                   /* 9. In Progress state.*/
    TWAMP_REFL_STATE_DELETE = 10,                                       /* 10. Delete*/
    TWAMP_REFL_STATE_LINK_DOWN = 11,                                    /* 11. Link Down*/
    TWAMP_REFL_STATE_MAX
} TWAMP_RESPONDER_CTRL_STATE_E ;


/*Twamp PPI operation types*/
typedef enum tagTwampPPIOprType
{
    /*Added for TWAMP*/
    PPI_TWAMP_RESPONDER_SESSION_ADD,  /*0 Adding Reponder Session*/
    PPI_TWAMP_RESPONDER_SESSION_DEL,  /*1 Deleting Reponder Session*/
    PPI_TWAMP_RESPONDER_GET_DSCP,     /*2 Get Responder test session DSCP Value*/
    PPI_TWAMP_SENDER_SESSION_ADD,     /*3 Adding Sender Session*/
    PPI_TWAMP_SENDER_SESSION_DEL,     /*4 Deleting Sender Session*/
    PPI_TWAMP_SENDER_GET_DSCP,        /*5 Get Sender test session DSCP Value*/
    PPI_TWAMP_OPR_END                       /*6 End of the operation type- this is not a valid value*/
} TWAMP_PPI_OPER_TYPE_E ;

/* Specifies state of Sender. */
typedef enum tagTcpipTwampSenderEvent
{
    TWAMP_SENDER_EVENT_TIMEOUT = 0, /* 0. Sender Time Out*/
    TWAMP_SENDER_EVENT_MAX
} TWAMP_SENDER_EVENT_E ;


/*
   Callback function to notify the  Responder Control/Test Session Status
   ulResponderId - Responder/Reflector ID
   pstSess - Control/Test Session
   ulState  - State of type TWAMP_RESPONDER_CTRL_STATE_E

   Return value: User Should Return following values from the Callback
   On Succes - VOS_TRUE
   On Failure - VOS_FALSE
*/

typedef ULONG (*TCPIP_HOOK_TWAMP_REFL_FUNC)
(
    ULONG  ulResponderId,                               /* Reflector ID. */
    TCPIP_TWAMP_REFL_SESS_S *pstSess,        /* Reflector session structure. */
    ULONG  ulState                                           /* Reflector state. */
);


/*
   Used to Notify the Control connection/Test Session Status to the user, Same State will be returned in the Get API.
*/
typedef enum tagTcpipTwampSesstate
{
    TWAMP_STATE_SUCCESS = 0,                                 /* 0.  Client succeeds a link to server.*/
    TWAMP_STATE_REFLECTOR_UNSPECIFIED_ERROR =1,                        /* 1.  Unspecified error from the server.*/
    TWAMP_STATE_REFLECTOR_INTERNAL_ERROR = 2,                          /* 2.  Server Internal Error*/
    TWAMP_STATE_REFLECTOR_NOT_SUPPORTED = 3,                           /* 3.  Option not supported from the server.*/
    TWAMP_STATE_REFLECTOR_PERMANENT_RESOURCE_LIMITATION = 4,           /* 4.  Permanent resource limitation from the server.*/
    TWAMP_STATE_REFLECTOR_TEMPORARY_RESOUCE_LIMITATION = 5,            /* 5.  Temporary resource limitation from the server.*/        
    TWAMP_STATE_CLIENT_INTERNAL_ERROR = 6,                   /* 6.  Client internal error .*/
    TWAMP_STATE_TIME_OUT = 7,                                /* 7.  Time Out.*/
    TWAMP_STATE_PENDING =  8,                                /* 8.  Pending state.*/
    TWAMP_STATE_IN_PROGRESS = 9,                             /* 9.  In Progress state.*/
    TWAMP_STATE_DELETE = 10,                                 /* 10. Delete  */
    TWAMP_STATE_LINK_DOWN = 11,                              /* 11. Link is down */
    TWAMP_STATE_BIND_ERROR = 12,                              /* 12. Socket Bind to port Failed */
    TWAMP_STATE_UNSPECIFIED_ERROR =13,                        /* 13.  Unspecified error from the Client.*/
    TWAMP_STATE_INTERNAL_ERROR = 14,                          /* 14.   Internal Error*/
    TWAMP_STATE_NOT_SUPPORTED = 15,                           /* 15.  Option not supported from.*/
    TWAMP_STATE_PERMANENT_RESOURCE_LIMITATION = 16,           /* 16.  Permanent resource limitation from client.*/
    TWAMP_STATE_TEMPORARY_RESOUCE_LIMITATION = 17,            /* 17.  Temporary resource limitation from client.*/
    TWAMP_STATE_MAX
} TWAMP_SESS_STATE_E ;
/*
   Callback function to notify the Control Connection status to the user
   ulClientId - Client Id
   ulState  - State of type TWAMP_SESS_STATE_E

   Return value: User Should Return following values from the Callback
   On Succes - VOS_TRUE
   On Failure - VOS_FALSE
*/

typedef ULONG (*TCPIP_HOOK_TWAMP_CTRL_FUNC)
(
    ULONG  ulClientId,
    ULONG  ulState
);

/*
   Callback function to notify the test session status to the user
   ulClientId - Client Id
   ulSenderId - Sender Id
   ulState  - State of type TWAMP_SESS_STATE_E

   Return value: User Should Return following values from the Callback
   On Succes - VOS_TRUE
   On Failure - VOS_FALSE
*/

typedef ULONG (*TCPIP_HOOK_TWAMP_SESS_FUNC)
(
    ULONG  ulClientId,
    ULONG  ulSenderId,
    ULONG  ulState
);



/*TWAMP Reflector Notify event*/
typedef enum tagTcpipTwampReflEvent
{
    TWAMP_REFL_EVENT_REFWAIT_TIMEOUT = 0,    /* 0. Ref WAIT Time Out*/
    TWAMP_REFL_EVENT_MAX
} TWAMP_REFL_EVENT_E ;


typedef struct tagTcpipTwampReflNotify
{
    ULONG ulEvent;           /*Event of type  TWAMP_REFL_EVENT_E */
    ULONG ulSessionId;       /*Session Id */
    ULONG ulReflectorId;     /*Responder id */
    ULONG ulVrfId;
} TCPIP_TWAMP_REFL_NOTIFY_S;


/*TWAMP Error code*/
typedef enum enumTwampErrorCode
{
    TWAMP_OK = 0,                                                      /*0 - Return code for Success*/
    TWAMP_ERR = MID_COMP_TWAMP + 1,                                    /*0x0E440001 - Return code for TWAMP Module error*/
    TWAMP_ERR_WRONG_TASKPRIO,                                          /*0x0E440002 - wrong task priority value*/
    TWAMP_ERR_MODULE_ALREADY_INIT,                                     /*0x0E440003 - Twamp Module has already initialized*/
    TWAMP_ERR_MALLOC_FAIL,                                             /*0x0E440004 - Malloc Failure in TWAMP Module*/
    TWAMP_ERR_QUEUE_CREATE_FAIL,                                       /*0x0E440005 - TWAMP Queue creation failed*/
    TWAMP_ERR_NULL_INPUT,                                              /*0x0E440006 - Input parameter pointer is NULL*/
    TWAMP_ERR_REFLECTOR_INIT_FAIL,                                     /*0x0E440007 - Error while Initialising TWAMP reflector*/
    TWAMP_ERR_CLIENT_INIT_FAIL,                                        /*0x0E440008 - Error while Initialising TWAMP Client*/
    TWAMP_ERR_WRONG_INPUT_RANGE,                                       /*0x0E440009 - Wrong Input Range to the API*/
    TWAMP_ERR_TIMER_CREATE_FAIL,                                       /*0x0E44000A - Error while creating the Timer in TWAMP Module*/
    TWAMP_ERR_TASK_CREATE_FAIL,                                        /*0x0E44000B - Error While Creating tha task in TWAMP Module*/
    TWAMP_ERR_MUTEX_CREATE_FAIL,                                       /*0x0E44000C - Error While Creating Mutex*/
    TWAMP_ERR_REFLECTOR_ALREADY_CREATED,                               /*0x0E44000D - Reflector has already been created*/
    TWAMP_ERR_MODULE_NOT_INIT,                                         /*0x0E44000E - Twamp Module is not initialised*/
    TWAMP_ERR_MAX_REFLECTOR_LIMIT_REACHED,                             /*0x0E44000F - Reached the limit of Max number of Reflectors*/
    TWAMP_ERR_REFLECTOR_INVALID_MODE,                                  /*0x0E440010 - The Mode being configured for reflector is Invalid*/
    TWAMP_ERR_REFLECTOR_INVALID_MAX_CLIENT,                            /*0x0E440011 - The MaxClient value being configured for reflector is Invalid */
    TWAMP_ERR_REFLECTOR_INVALID_MAX_TESTSESSION,                       /*0x0E440012 - The Max Test sessions value being configured for reflector is Invalid */
    TWAMP_ERR_REFLECTOR_INVALID_SERVWAIT_TIME,                         /*0x0E440013 - The Serv Wait Timer value being configured for reflector is Invalid */
    TWAMP_ERR_REFLECTOR_INVALID_REFWAIT_TIME,                          /*0x0E440014 - The REFWAIT Times value being configured for reflector is Invalid */
    TWAMP_ERR_REFLECTOR_DUPLICATE_RESPONDERID,                         /*0x0E440015 - The Responder Id is already exists */
    TWAMP_ERR_REFLECTOR_CREATE_SOCK_FAILED,                            /*0x0E440016 - Socket creation Failed */
    TWAMP_ERR_REFLECTOR_SOCK_IOCTL_FAILED,                             /*0x0E440017 - socket ioctl function fails*/
    TWAMP_ERR_REFLECTOR_SOCK_BIND_FAILED,                              /*0x0E440018 - socket bind function fails*/
    TWAMP_ERR_REFLECTOR_SOCK_LISTEN_FAILED,                            /*0x0E440019 - socket listen function fails*/
    TWAMP_ERR_REFLECTOR_QUEUE_WRITE_FAILED,                            /*0x0E44001A - writing to the queue failed*/
    TWAMP_ERR_REFLECTOR_EVENT_WRITE_FAILED,                            /*0x0E44001B - writing event for reflector Task failed*/
    TWAMP_ERR_ADD_REFLECTOR_MALLOC_FAIL,                               /*0x0E44001C - Malloc failure in Reflector*/
    TWAMP_ERR_REFLECTOR_TEST_SESSION_TABLE_MALLOC_FAIL,                /*0x0E44001D - malloc failure while allocating memory for reflector test session table*/
    TWAMP_ERR_CREATE_PORT_QUEUE_MALLOC_FAIL,                           /*0x0E44001E - Malloc failure while alocating memory for reflector port queue*/
    TWAMP_ERR_DUPLICATE_RESPONDERID,                                   /*0x0E44001F - Responder Id is Already present*/
    TWAMP_ERR_REFLECTOR_DUPLICATE_IPADDR,                              /*0x0E440020 - address is already existing*/
    TWAMP_ERR_REFLECTOR_GET_START_TIME_FAILED,                         /*0x0E440021 - fail to get the start time*/
    TWAMP_ERR_STOP_REFLECTOR_QUEUE_WRITE_FAILED,                       /*0x0E440022 - fail to write to the queue*/
    TWAMP_ERR_STOP_REFLECTOR_EVENT_WRITE_FAILED,                       /*0x0E440023 - Twamp Reflector Write Event failed*/
    TWAMP_ERR_DEL_REFLECTOR_NOT_FOUND,                                 /*0x0E440024 - reflector not found*/
    TWAMP_ERR_HASH_INVALID_PARAM,                                      /*0x0E440025 - Invalid parameter for hash table*/
    TWAMP_ERR_HASH_NOT_FOUND,                                          /*0x0E440026 - Hash table entry not found*/
    TWAMP_ERR_HASH_ERR_GET_KEY,                                        /*0x0E440027 - fail to get the key value fo the hash table*/
    TWAMP_ERR_CLIENT_CREATE_SOCK_FAILED,                               /*0x0E440028 - creation of socket failed for client*/
    TWAMP_ERR_CORE_ADD_CLIENT_INVALID_MODE,                            /*0x0E440029 - The Mode being configured for client is Invalid*/
    TWAMP_ERR_CORE_CLIENT_CREATE_SOCK_FAILED,                          /*0x0E44002A - creation of socket failed for client core*/
    TWAMP_ERR_CORE_CLIENT_SOCK_IOCTL_FAILED,                           /*0x0E44002B - socket ioctl function failed in core client*/
    TWAMP_ERR_CORE_CLIENT_SOCK_BIND_FAILED,                            /*0x0E44002C - socket bind function failed in core client*/
    TWAMP_ERR_CORE_ADD_CLIENT_QUEUE_WRITE_FAILED,                      /*0x0E44002D - queue write failed in client task for add operation*/
    TWAMP_ERR_CORE_DEL_CLIENT_QUEUE_WRITE_FAILED,                      /*0x0E44002E - queue write failed in client task for delete operation*/
    TWAMP_ERR_CORE_ADD_CLIENT_EVENT_WRITE_FAILED,                      /*0x0E44002F - writing of the event failed in client task for add operation*/
    TWAMP_ERR_CORE_DEL_CLIENT_EVENT_WRITE_FAILED,                      /*0x0E440030 - writing of the event failed in client task for delete operation*/
    TWAMP_ERR_MAX_CLIENT_LIMIT_REACHED,                                /*0x0E440031 - Max client limit reached*/
    TWAMP_ERR_ADD_CLIENT_DUPLICATE_CLIENTID,                           /*0x0E440032 - client Id is already present*/
    TWAMP_ERR_MAX_SENDER_LIMIT_REACHED,                                /*0x0E440033 - Maximum sender limit reached*/
    TWAMP_ERR_CORE_ADD_SENDER_QUEUE_WRITE_FAILED,                      /*0x0E440034 - writing to the queue failed while adding the sender*/
    TWAMP_ERR_CORE_ADD_SENDER_EVENT_WRITE_FAILED,                      /*0x0E440035 - writing event failed while adding the sender*/
    TWAMP_ERR_CORE_ADD_SENDER_INVALID_DSCP_VALUE,                      /*0x0E440036 - The DSCP value being configured for client is Invalid*/
    TWAMP_ERR_CORE_ADD_SENDER_CLIENT_NOT_FOUND,                        /*0x0E440037 - The Client is not present*/
    TWAMP_ERR_CORE_ADD_SENDER_INVALID_CLIENT_STATE,                    /*0x0E440038 - the client state is Invalid*/
    TWAMP_ERR_CORE_ADD_SENDER_DUPLICATE_SENDERID,                      /*0x0E440039 - sender Id is already present*/
    TWAMP_ERR_CORE_DEL_SENDER_QUEUE_WRITE_FAILED,                      /*0x0E44003A - writing to the queue failed while deleting the sender*/
    TWAMP_ERR_CORE_DEL_SENDER_EVENT_WRITE_FAILED,                      /*0x0E44003B - writing event failed while deleting the sender*/
    TWAMP_ERR_CORE_DEL_SENDER_CLIENT_NOT_FOUND,                        /*0x0E44003C - client Id not found while deleting the sender*/
    TWAMP_ERR_CORE_DEL_SENDER_SENDER_NOT_FOUND,                        /*0x0E44003D - Sender Id not found while deleting the sender*/
    TWAMP_ERR_SEND_SERVER_GREETING_FAIL,                               /*0x0E44003E - sending the server greeting message failed*/
    TWAMP_ERR_SEND_SERVER_START_FAIL,                                  /*0x0E44003F - sending the server start message failed*/
    TWAMP_ERR_SEND_SETUP_RESPONSE_FAIL,                                /*0x0E440040 - sending the set up response message failed*/
    TWAMP_ERR_SHELL_NULL_INPUT,                                        /*0x0E440041 - Input parameter is NULL*/
    TWAMP_ERR_SHELL_CLIENTID_ALREADY_PRESENT,                          /*0x0E440042 - client ID is already present*/
    TWAMP_ERR_SHELL_CLIENT_NOT_PRESENT,                                /*0x0E440043 - Client Id is not present*/
    TWAMP_ERR_SHELL_SENDERID_ALREADY_PRESENT,                          /*0x0E440044 - Sender Id is already present*/
    TWAMP_ERR_SHELL_SENDER_NOT_PRESENT,                                /*0x0E440045 - sender Id Not present*/
    TWAMP_ERR_MAX_SENDER_PER_CLIENT_LIMIT_REACHED,                     /*0x0E440046 - Max sender per client Limit reached*/
    TWAMP_ERR_ADD_CLIENT_MALLOC_FAIL,                                  /*0x0E440047 - malloc failure while adding the client*/
    TWAMP_ERR_ADD_SENDER_MALLOC_FAIL,                                  /*0x0E440048 - malloc failure while adding the sender*/
    TWAMP_ERR_REFLECTOR_NOT_FOUND,                                     /*0x0E440049 - reflector not found*/
    TWAMP_ERR_GET_TIME_FAILED,                                         /*0x0E44004A - failure while getting the timer*/
    TWAMP_ERR_LIST_END,                                                /*0x0E44004B - End of the list reached*/
    TWAMP_ERR_REFLECTOR_TEST_SESSION_TABLE_ALREADY_OPEN,               /*0x0E44004C - Reflector test session table already open*/
    TWAMP_ERR_REFLECTOR_TEST_SESSION_TABLE_ALREADY_CLOSED,             /*0x0E44004D - Reflector test session table already closed*/
    TWAMP_ERR_REFLECTOR_TEST_SESSION_TABLE_INVALID_INPUT,              /*0x0E44004E - Invalid input parameter*/
    TWAMP_ERR_REFLECTOR_TEST_SESSION_TABLE_CLOSED,                     /*0x0E44004F - Reflector test session table closed*/
    TWAMP_ERR_REFLECTOR_TEST_SESSION_TABLE_NO_ENTRY,                   /*0x0E440050 - there is no entry present in reflector test session table*/
    TWAMP_ERR_INVALID_REFLECTOR_IP,                                    /*0x0E440051 - Invalid reflector Address*/
    TWAMP_ERR_ADD_TIMER_FAILED,                                        /*0x0E440052 - adding the timer failed*/
    TWAMP_ERR_INVLID_REF_NOTIFY_EVENT,                                 /*0x0E440053 - Invalide REFWAIT notify event*/
    TWAMP_ERR_INVALID_TEST_SESSION_ID,                                 /*0x0E440054 - Invalid test session Id*/
    TWAMP_ERR_PPI_WRONG_OPER_TYPE,                                     /*0x0E440055 - Wrong operation as input for Twamp PPI function*/
    TWAMP_ERR_PPI_NULL_INPUT,                                          /*0x0E440056 - NULL input for Twamp PPI function*/
    TWAMP_ERR_PPI_HOOK_NOT_REGISTERED,                                 /*0x0E440057 - Twamp PPI Hook function is not registered*/
    TWAMP_ERR_PPI_TEST_SESSION_NOT_ADDED,                              /*0x0E440058 - Twamp test session is not yet added to PPI*/
    TWAMP_ERR_SHELL_SENDER_LIST_EMPTY,                                 /*0x0E440059 - Twamp Sender list is empty*/
    TWAMP_ERR_SHELL_SENDER_CONFIG_NOT_PRESENT,                         /*0x0E44005A - Sender Config Not Present*/
    TWAMP_ERR_SHELL_SENDER_NOT_PRESNET_IN_CORE,                        /*0x0E44005B - Sender not present in core*/
    TWAMP_ERR_HOOK_REG_AFTER_INIT,                                     /*0x0E44005C - PPI Hook function is called after twamp module Init*/
    TWAMP_ERR_REFLECTOR_SET_OPT_FAIL,                                  /*0x0E44005D - socket setsocketoption Tcp Keepalive function fails*/
    TWAMP_ERR_CLIENT_SET_OPT_FAIL,                                     /*0x0E44005E - socket setsocketoption Tcp Keepalive function fails*/
    TWAMP_ERR_ALLOCATE_CLIENT_CONFIG_DATA_FAIL,                        /*0x0E44005F - Failed to Allocate Client Configuration data*/
    TWAMP_ERR_REF_SOCK_READ_FAIL,                                      /*0x0E440060 - Failed to read data From Reflector Socket*/
    TWAMP_ERR_REF_SOCK_RECV_ZERO,                                      /*0x0E440061 - Connection closed by client*/
    TWAMP_ERR_CLIENT_SOCK_READ_FAIL,                                   /*0x0E440062 - Failed to read data From Client Socket*/
    TWAMP_ERR_CLIENT_SOCK_RECV_ZERO,                                   /*0x0E440063 - Connection closed by Reflector as Fin Packet is received by Client*/
    TWAMP_ERR_PDU_NOT_COMPLETE,                                        /*0x0E440064 - PDU Not Completely Received*/
    TWAMP_ERR_WRONG_INPUT_EVENT_TYPE,                                  /*0x0E440065 - Event Type is wrong*/
    TWAMP_ERR_PPIWAIT_TIMEOUT_VALUE,                                   /*0x0E440066 - PPI Timeout*/
    TWAMP_ERR_INVALID_SOCK_OPT,                                        /*0x0E440067 - Socket Option not supported.*/
    TWAMP_ERR_MAX_SYSTEM_LIMIT_REACHED,                                /*0x0E440068 - Max Syslem Limit Reached*/
    TWAMP_ERR_MAX_CLIENT_LIMIT_REACHED_PER_REFLECTOR,                  /*0x0E440069 - Max Client Limit Reached Per Reflector*/
    TWAMP_ERR_HA_BAK_FAIL,                                             /*0x0E44006A - Twamp HA BAckup Failed*/
    TWAMP_ERR_HA_IS_SMOOTHING,                                         /*0x0E44006B - Twamp Operation failed as HA smoothing is in progress*/
    TWAMP_NOT_ENOUGH_HA_BUFFER,                                        /*0x0E44006C - Allocated HA buffer is finished*/
    TWAMP_HA_WRITE_FAIL,                                               /*0x0E44006D - Twamp HA message write failed*/
    TWAMP_ERR_ADD_IP_PORT_POOL_FAIL,                                   /*0x0E44006E - Twamp Error For IP PORT POOl Failure*/
    TWAMP_ERR_OPENWAITLIST_FAIL,                                       /*0x0E44006F - Twamp Open Waitlist Failure*/
    TWAMP_ERR_WAITLIST_SET_FAILED,                                     /*0x0E440070 - Twamp SettingWaitlist Failed*/
    TWAMP_ERR_NO_CNTRL_SESSION,                                        /*0x0E440071 - No Control Session is present for the reflector*/
    TWAMP_ERR_GETWAITLIST_FAIL,                                        /*0x0E440072 - Get Wait list Failure*/
    TWAMP_ERR_WAITLISTEND,                                             /*0x0E440073 - Session List is Finished*/
    TWAMP_ERR_INVALID_HANDLE,                                          /*0x0E440074 - Input Handle is Invalid*/
    TWAMP_ERR_WAITLIST_UNREG_FAIL,                                     /*0x0E440075 - Unregister from waitlist Failed*/
    TWAMP_ERR_WRONG_RESPONDERID,                                       /*0x0E440076 - Invalid Responder Id for Given Handle*/
    TWAMP_ERR_TEST_PKT_SIZE_VALUE,                                     /*0x0E440077 - Invalid Packet Sizet*/
    TWAMP_ERR_TEST_INVALID_INDEX_RANGE,                                /*0x0E440078 - Invalid Index range*/
    TWAMP_ERR_CLIENT_SET_TOS_OPT_FAIL,                                 /*0x0E440079 - socket setsocketoption for IP TOS fails*/
    TWAMP_ERR_REFL_SET_TOS_OPT_FAIL,                                   /*0x0E44007A - socket setsocketoption for IP TOS fails*/
    TWAMP_ERR_CLIENT_CONNECT_INVALID_DSCP_VALUE,                       /*0x0E44007B - The DSCP value being configured for client is Invalid*/
    TWAMP_ERR_REFL_INVALID_DSCP_VALUE,                                 /*0x0E44007C - The DSCP value being configured for reflector is Invalid*/
    TWAMP_ERR_REFLECTOR_ALLOC_SOCK_OPT_FAIL                            /*0x0E44007D - Memory Allocation failed at reflector side socket options*/
} TWAMP_ERROR_CODE_E ; 


#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
#endif   /* end of __TCPIP_TWAMP_DEF_H__ */
