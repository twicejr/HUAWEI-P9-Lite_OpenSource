
#ifndef _TWAMP_DEF_H_
#define _TWAMP_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define  TWAMP_MID MID_COMP_TWAMP

//#define TWAMP_OK            0
//#define TWAMP_ERR           1
#define TWAMP_TTL_255 255

#define TWAMP_ONE 1
#define TWAMP_ZERO 0

#define TWAMP_MAX_SOCK_OPTION_NUM 5

#define TWAMP_QDEPTH     512
#define TWAMP_QMODE     VOS_Q_FIFO | VOS_Q_ASYN

#define TWAMP_TASK_MODE          0       /* means default value: T_NOPREEMPT | T_NOTSLICE */


#define TWAMP_BUFF_SIZE  2*512

#define TWAMP_EVENT_READ_TIMEOUT 500


#define TWAMP_MIN_CLIENT_SESS_PER_REFL 1
#define TWAMP_MIN_CLIENT_SESS 1
#define TWAMP_MIN_TEST_SESS_PER_REFL 1
#define TWAMP_MIN_TEST_SESS 1

#define TWAMP_MIN_REFLECTORS                 1  /*Min reflectors */

#define TWAMP_NO_OF_BITS_IN_LONG 32

#define TWAMP_MAX_PORT_POOL_SIZE ((TWAMP_MAX_TEST_SESS / TWAMP_NO_OF_BITS_IN_LONG) + TWAMP_ONE)

#define TWAMP_PORT_FREE 0xFF


#define INVALID_SESSION_ID 0xFFFF


#define TWAMP_CTRL_SESSION_TABLE_SIZE 100



#define TWAMP_USE_GLOBAL_CONFIG_VALUE 0

/*TWAMP Events*/
#define TWAMP_REFLECTOR_ADD           0X00000001  /* "00000000 00000000 00000000 00000001" */
#define TWAMP_REFLECTOR_DEL            0X00000002  /* "00000000 00000000 00000000 00000010" */
#define TWAMP_REFLECTOR_LISTEN       0X00000004  /* "00000000 00000000 00000000 00000100" */
#define TWAMP_CLIENT_CONFIG              0X00000008  /* "00000000 00000000 00000000 00001000" */
#define TWAMP_CLIENT_LISTEN               0X00000010  /* "00000000 00000000 00000000 00010000" */
#define TWAMP_REFLECTOR_TIMER          0X00000020  /* "00000000 00000000 00000000 00100000" */


/*TWAMP_Client Operation*/
#define TWAMP_CLIENT_ADD           0X00000001
#define TWAMP_SENDER_ADD          0X00000002
#define TWAMP_CLIENT_DELETE      0x00000003
#define TWAMP_SENDER_DELETE     0X00000004


#define TWAMP_NON_BLOCKING 1

#define TWAMP_REFLECTOR_QUEUE_LEN 2048
#define TWAMP_REFLECTOR_QUEUE_MODE VOS_MSG_Q_FIFO

#define TWAMP_CLIENT_QUEUE_LEN 2048
#define TWAMP_CLIENT_QUEUE_MODE VOS_MSG_Q_FIFO


#define TWAMP_REFLECTOR_SELECT_TIMEOUT_SEC 1
#define TWAMP_REFLECTOR_SELECT_TIMEOUT_USEC 0

#define TWAMP_CLIENT_SELECT_TIMEOUT_SEC 1
#define TWAMP_CLIENT_SELECT_TIMEOUT_USEC 0

#define TWAMP_TEST_SESSION_TABLE_CLOSE 0xFFFFFFFF
#define TWAMP_TEST_SESSION_TABLE_OPEN 0


#define TWAMP_CONFIG_TIMER_TIMEOUT 100  /*100 mili seconds*/
#define TWAMP_CONFIG_TIMEOUT 120 /*seconds*/


#define TWAMP_EVENT_QUEUE_ENABLE 0



#define TWAMP_IS_INVALID_SOCKETFD(a) (a < TWAMP_ZERO ? TWAMP_ONE : TWAMP_ZERO)

#define TWAMP_IS_INVALID_REFLECTORADDR(a) (a == 0x7F000001 ? TWAMP_ONE : TWAMP_ZERO)


#define TWAMP_IS_INVALID_DSCP(a) ((a) != (a & 0x0000003F))


#define TWAMP_MODE_MASK 0x00000007
#define TWAMP_DSCP_MASK  0xC0000000

#define TWAMP_IPV4_SESSION 4

#define TWAMP_START_SESSION_DELAY 2

#define TWAMP_CMDID_REQUEST_SESSION 5
#define TWAMP_CMDID_START_SESSION 2
#define TWAMP_CMDID_STOP_SESSION 3


#define TWAMP_REFLECTOR_TIME_OUT 1000 /* Reflector Timer Interval*/

#define TWAMP_MILLISEC_PER_SEC 1000 /* No of millisecond in a second*/


#define TWAMP_TIMER_TABLE_SIZE 256 /*Timer Table Size */


#define TWAMP_RENEGOTIATION_DELAY 125


/**first six bits will be used as DSCP value*/
#define TWAMP_TOS_DSCP_SHIFT_VAL  2



/*Begin:: twamp reflectore packet debug types*/
#define TWAMP_REF_DEBUG_INVALID_PKT                     1
#define TWAMP_REF_DEBUG_REQUEST_SESSION_PKT    2
#define TWAMP_REF_DEBUG_START_SESSION_PKT        3
#define TWAMP_REF_DEBUG_STOP_SESSION_PKT          4
#define TWAMP_REF_DEBUG_SETUP_RESPONSE_PKT      6
#define TWAMP_REF_DEBUG_SERVER_GREETING_PKT     7
#define TWAMP_REF_DEBUG_SERVER_START_PKT           8
#define TWAMP_REF_DEBUG_SESSION_ACCEPT_PKT       9
#define TWAMP_REF_DEBUG_SESSION_START_ACK_PKT 10


#define TWAMP_CLI_DEBUG_INVALID_PKT                     1
#define TWAMP_CLI_DEBUG_SERV_GREETING_PKT         2
#define TWAMP_CLI_DEBUG_SERV_SERVER_START_PKT 3
#define TWAMP_CLI_DEBUG_SESSION_ACCEPT_PKT       4
#define TWAMP_CLI_DEBUG_SESSION_START_ACK_PKT  5
#define TWAMP_CLI_DEBUG_SETUP_RESPONSE_PKT        6
#define TWAMP_CLI_DEBUG_REQUEST_SESSION_PKT      7
#define TWAMP_CLI_DEBUG_SENDER_SESSION_START_PKT         8
#define TWAMP_CLI_DEBUG_STOP_SESSION_PKT         9



#define TWAMP_SENDER_RENEGOTIATION_DELAY 1


#define TWAMP_RECV_BUFFER_LEN LEN_512


#define TWAMP_REFLECTOR_START_LISTEN(a)\
{\
    if (a > g_lTwampMAXReflectorFD)\
    {\
        g_lTwampMAXReflectorFD = a + TWAMP_ONE;\
    }\
    FD_SET(a, &g_stTWAMPReflectorFDSet);\
}

#define TWAMP_CLIENT_START_LISTEN(a)\
{\
    if (a > g_lTwampMAXClientFD)\
    {\
        g_lTwampMAXClientFD = a + TWAMP_ONE;\
    }\
    FD_SET(a, &g_stTWAMPClientFDSet);\
}

#define TWAMP_CLIENT_STOP_LISTEN(a)\
{\
       FD_CLR(a, &g_stTWAMPClientFDSet);\
       (VOID)close(a);\
}

#define TWAMP_STOP_SESSION_TIMEOUT_START_SCAN(a)\
{\
    /*if (a > g_lTwampMAXStopSessionFD)\
    {\
        g_lTwampMAXStopSessionFD = a + TWAMP_ONE;\
    }*/\
    FD_SET(a, &g_stTWAMPStopSessionFDSet);\
}

#define TWAMP_STOP_SESSION_TIMEOUT_STOP_SCAN(a)\
{\
       FD_CLR(a, &g_stTWAMPStopSessionFDSet);\
}


#if (TCPIP_MODULE_HA == VRP_YES)
#define TWAMP_REFLECTOR_STOP_LISTEN(a)\
{\
       FD_CLR(a, &g_stTWAMPReflectorFDSet);\
       if((TCPIP_HA_AMB == TCPIP_HA_GetBoardType()) && (!g_ulHAManualOrSmooth) && (!g_ulHABeforeSmooth))\
       {\
            (VOID)close(a);\
       }\
}

#else
#define TWAMP_REFLECTOR_STOP_LISTEN(a)\
{\
       FD_CLR(a, &g_stTWAMPReflectorFDSet);\
       (VOID)close(a);\
}
#endif


/*#define TWAMP_REFLECTOR_STOP_LISTEN(a)\
{\
       FD_CLR(a, &g_stTWAMPReflectorFDSet);\
       (VOID)close(a);\
}*/





#define TWAMP_NOTIFY_ROSA_SHELL(ulRefid,Sessinfo,ulState)\
{\
    if (NULL != g_pfnReflHook)\
    {\
        (VOID)(*g_pfnReflHook)(ulRefid,Sessinfo,ulState);\
    }\
}


#define TWAMP_SENDER_NOTIFY_ROSA_SHELL(ulClientid,ulSenderId,ulState)\
{\
    if (NULL != g_pfnSessCoreHook)\
    {\
        (VOID)(*g_pfnSessCoreHook)(ulClientid,ulSenderId,ulState);\
    }\
}

#define TWAMP_CLIENT_NOTIFY_ROSA_SHELL(uClientId, ulState)\
{\
    if(g_pfnCtrlCoreHook)\
    {\
        (VOID)(*g_pfnCtrlCoreHook)(uClientId, ulState);\
    }\
}\





#define TWAMP_RELEASE_PORT(n, p)        ((p)->aulPortPool[(n)/TWAMP_NO_OF_BITS_IN_LONG] |= \
            (((ULONG) 0x00000001) << ((n) % TWAMP_NO_OF_BITS_IN_LONG)))


#define TWAMP_AQUIRE_PORT(n, p)    ((p)->aulPortPool[(n)/TWAMP_NO_OF_BITS_IN_LONG] &= \
                       ~(((ULONG) 0x00000001) << ((n) % TWAMP_NO_OF_BITS_IN_LONG)))
#define TWAMP_ISPORTFREE(n, p)  ((p)->aulPortPool[(n)/TWAMP_NO_OF_BITS_IN_LONG] & \
                        (((ULONG) 0x00000001) << ((n) % TWAMP_NO_OF_BITS_IN_LONG)))


#define TWAMP_BIT64_ADD(argAHi, argALo, argBHi, argBLo) \
    do \
    { \
        if ((argALo) > 0xFFFFFFFF - (argBLo)) \
        { \
            (argAHi) += ((argBHi) + 1); \
        } \
        else \
        { \
            (argAHi) += (argBHi); \
        } \
        (argALo) += (argBLo); \
    } while (0)

#define TWAMP_BIT64_COMPARE(argAHi, argALo, argBHi, argBLo, result) \
    do \
    { \
        if ((argAHi) > (argBHi)) \
        { \
            result = TWAMP_BIT64_GREAT; \
        } \
        else if (((argAHi) == (argBHi)) && ((argALo) > (argBLo))) \
        { \
            result = TWAMP_BIT64_GREAT; \
        } \
        else if (((argAHi) == (argBHi)) && ((argALo) == (argBLo))) \
        { \
            result = TWAMP_BIT64_EQUAL; \
        } \
        else \
        { \
            result = TWAMP_BIT64_LESS; \
        } \
    } while (0)


#define TWAMP_BIT64_SUB(argAHi, argALo, argBHi, argBLo) \
    do \
    { \
        if ((argALo) < (argBLo)) \
        { \
            (argAHi) -= ((argBHi) + 1); \
        } \
        else \
        { \
            (argAHi) -= (argBHi); \
        } \
        (argALo) -= (argBLo); \
    } while (0)

#define TWAMP_MAX_SHIFT_NUM 32

#define TWAMP_MASK_BIT_32      0x80000000

typedef enum tagTwampbit64CompareResult
{
    TWAMP_BIT64_GREAT,
    TWAMP_BIT64_EQUAL,
    TWAMP_BIT64_LESS
} Twampbit64CompareResult;


/* Callback function to compute key. */
typedef ULONG (*TCPIP_KEY_GET)
(
    VOID  *pInput,
    ULONG *ulKey
);

/* Callback function to compare key. */
typedef ULONG (*TCPIP_KEY_COMP)
(
    VOID *pTO,
    VOID *pFrom
);

/*Callback function to notify the client status*/
typedef ULONG (*TWAMP_CORE_HOOK_CLIENT_CTRL_FUNC)
(
    ULONG  ulClientId,
    ULONG  ulState
);


/*Callback function to notify the client status*/
typedef ULONG (*TWAMP_CORE_HOOK_CLIENT_CTRL_TIMEOUTFUNC)
(
    ULONG  ulClientId
);


/*Callback function to notify the client test session status*/
typedef ULONG (*TWAMP_CORE_HOOK_SENDER_SESS_FUNC)
(
    ULONG  ulClientId,
    ULONG  ulSenderId,
    ULONG  ulState
);



typedef struct tagTcpipTwampClientSockTbl
{
    /* Info. */
    VOID *pHashInst;
}TCPIP_TWAMP_CLIENT_SOCK_TBL_S;

typedef struct tagTcpipTwampClientSessionTbl
{
    /* Info. */
    VOID *pHashInst;
}TCPIP_TWAMP_CLIENT_SESSION_TBL_S;





VOID TWAMP_Begin_PT(VOID);



VOID TWAMP_End_PT(VOID);



VOID TWAMP_ShowAllClients(ULONG ulStartClientId, ULONG ulEndClientId);



/*******************************************************************************
*    Func Name: TWAMP_ShowClientInfo
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  TWAMP_ShowClientInfo shows the client info based on client ID.
*  Following fields will be displayed
*	src_ip
*	 peer_ip
*	src_port
*	dst_port
*	mode
*	vrfIndex
*	ulConfigState
*	ulCoreState
*	ulCurFsmState
*	ulNumSenders
*	ulNumSendersInCore
*        Input:
*                  ULONG ulClientId: Cleinet ID
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowClientInfo(ULONG ulClientId);


/*******************************************************************************
*    Func Name: TWAMP_ShowAllSenders
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  TWAMP_ShowAllSenders shows all sender info based on client ID.
*  Following fields will be displayed
*  sender_id
*  src_port
*  dst_port
*        Input:
*                  ULONG ulClientId: Cleinet ID
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowAllSenders(ULONG ulClientId);

/*******************************************************************************
*    Func Name: TWAMP_ShowSenderInfo
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  TWAMP_ShowSenderInfo shows the sender info based on client ID & sender ID.
*  Following fields will be displayed
*  sender_id
*  src_port
*  dst_port
*  ucDscp
*  ulWaitTime
*  ulTimeOut
*  ulConfigState
*  ulCoreState
*  ulCurFsmState
*  ulIsDownloadToNP
*        Input:
*                  ULONG ulClientId: Cleinet ID
*                  ULONG ulSenderId: Sender ID
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowSenderInfo(ULONG ulClientId, ULONG ulSenderId);


/*******************************************************************************
*    Func Name: TWAMP_ShowAllGloablVars
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  TWAMP_ShowAllGloablVars shows all global variable related to TWAMP.
*  Following fields will be displayed
*  g_ulTwampCliTaskId
*  g_ulClientCount
*  g_ulShellClientCount
*  g_ulShellSenderCount
*  g_ulSenderCount
*  g_ulSIDCount
*  g_ulReflectorCount
*  g_ulTwampRefTaskId
*  g_ulTwampInitFlag
*  g_ulTWAMPSysTestSessionCount
*  g_ulTWAMPSysClientCount
*        Input: 
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowAllGloablVars();

/*******************************************************************************
*    Func Name: TWAMP_ShowAllReflector
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  Displays the Reflector ID, IP, Port, VRF, No of Control Session and No of Test Session.
*        Input: 
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowAllReflector();


/*******************************************************************************
*    Func Name: TWAMP_ShowReflectorInfo
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  Displays all information for the reflector other than Stats ,Test Session,
*  Control Session, IP Port Pool and Session ID queue.
*        Input: ULONG ulReflectorID
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowReflectorInfo(ULONG ulReflectorID);


/*******************************************************************************
*    Func Name: TWAMP_ShowReflectorStat
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  Displays Statistics provided by TCPIP_TWAMP_GetReflStats.
*        Input: ULONG ulReflectorID
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowReflectorStat(ULONG ulReflectorID);


/*******************************************************************************
*    Func Name: TWAMP_ShowSessionIdQueue
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  Displays Session Id Information.
* print TWAMP_REFLECTOR_S->stSessionIDQueue.
*        Input: ULONG ulReflectorID
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowSessionIdQueue(ULONG ulReflectorID);

/*******************************************************************************
*    Func Name: TWAMP_ShowIPPortPool
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  Displays multiple Pools based on Index value.
*        Input: ULONG ulReflectorID
*			ULONG ulStartIndex
*			ULONG ulEndIndex
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowIPPortPool(ULONG ulReflectorID,ULONG ulStartIndex , ULONG ulEndIndex);


/*******************************************************************************
*    Func Name: TWAMP_ShowIPPortPoolBYIP
* Date Created: 2013-06-24
*       Author: s72256
*  Description:
*  Displays Pool for a Specific IP.
*        Input: ULONG ulReflectorID
*			ULONG ulClientIpaddr
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowIPPortPoolBYIP(ULONG ulReflectorID,ULONG ulClientIpaddr);

/*******************************************************************************
*    Func Name: TWAMP_ShowReflectorCtrlSess
* Date Created: 2013-06-24
*       Author: s72256
*  Description: Displays multiple ctrl Session based on Index value.
*       Input: ULONG ulReflectorID
*			ULONG ulStartIndex
*			ULONG ulEndIndex
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowReflectorCtrlSess(ULONG ulReflectorID,ULONG ulStartIndex , ULONG ulEndIndex);


/*******************************************************************************
*    Func Name: TWAMP_ShowReflectorCtrlSessByIP
* Date Created: 2013-06-24
*       Author: s72256
* Description: Displays Ctrl Session for a Specific IP.
*        Input: ULONG ulReflectorID
*			ULONG ulIpaddr
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowReflectorCtrlSessByIP(ULONG ulReflectorID,ULONG ulIpaddr);


/*******************************************************************************
*    Func Name: TWAMP_ShowTestSession
* Date Created: 2013-06-24
*       Author: s72256
* Description: Displays Test Session based on Index value.
*        Input: ULONG ulReflectorID
*			ULONG ulStartIndex
*			ULONG ulEndIndex
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowTestSession(ULONG ulReflectorID,ULONG ulStartIndex , ULONG ulEndIndex);

/*******************************************************************************
*    Func Name: TWAMP_ShowTestSessionByIP
* Date Created: 2013-06-24
*       Author: s72256
* Description: Displays Test Session a Specific IP and Port.
*        Input: ULONG ulReflectorID
*			ULONG ulIpaddr
*			USHORT usPort
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-24     s72256       Create first version
*******************************************************************************/
VOID TWAMP_ShowTestSessionByIP(ULONG ulReflectorID, ULONG ulIpaddr, USHORT usPort);






#ifdef __cplusplus
}
#endif

#endif

