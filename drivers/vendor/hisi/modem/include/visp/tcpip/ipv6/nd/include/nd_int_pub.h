/******************************************************************************
*             Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              nd_int_pub.h
*
*    Project Code:  IPB IR V1R2
*    Version     :  IPBIRV100R003.IPv6.E001
*    Module Name :  ND
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define the strcutures and macro's used by core
*                    and shell of component
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik      Created for including all component
*                           public definitions in this file,
*                           for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/

#ifndef _ND_COM_PUBLIC_H
#define _ND_COM_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 *              Macros                          *
 *----------------------------------------------*/

#define IPB_IR_ND_MAX_INT_VAL            0xFFFFFFFF

/* ASSUMPTION : Maximum physical address length is 6 */
#define MACADDRLEN                      6

/* RA prefix related macros */
#define IP6_ND_PREFIX_LEN               96
#define IP6_ND_MAX_VALIDLIFETIME        4294967295
#define IP6_ND_MAX_PREFLIFETIME         4294967295

/* RA interval multiplication factor */
#define ND_DEF_MIN_INT_FAC              (0.33)

/* RA parameters default value */
#define DEFAULT_RA_CURHOPLIMIT          255
#define REACHABLE_TIME                  30000    /* msec */
#define RETRANS_TIMER                   1000     /* msec */

#define IP6_ND_RA_INTERVAL_EXCEEDS      23

/* RFC 2461

      MaxRtrAdvInterval
                     The maximum time allowed between sending
                     unsolicited multicast Router Advertisements from
                     the interface, in seconds.  MUST be no less than 4
                     seconds and no greater than 1800 seconds.

                     Default: 600 seconds

      AdvDefaultLifetime
                     The value to be placed in the Router Lifetime field
                     of Router Advertisements sent from the interface,
                     in seconds.  MUST be either zero or between
                     MaxRtrAdvInterval and 9000 seconds.  A value of
                     zero indicates that the router is not to be used as
                     a default router.

                     Default: 3 * MaxRtrAdvInterval

*/
#define DEFAULT_MAX_RA_INTERVAL         600
#define DEFAULT_ROUTER_LIFETIME         ((DEFAULT_MAX_RA_INTERVAL) * 3)
#define DEFAULT_DAD_NUM                 1
#define ND_RA_CANNOTSEND                0
#define ND_RA_CANSEND                   1

/* ND timer types */
#define ND_DADTIMER                     0
#define ND_RATIMER                      1
#define ND_NBTIMER                      2
#define ND_NBFORCEDELTIMER              3
/*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
#define ND_NATIMER                      4
/* End of Added by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
/*【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了N
  A我们需要启动DAD探测。*/
#define ND_DADEXTTIMER                  5
/* End of Added by guojianjun178934, 2014/2/22   问题单号:DTS2014021206259  */


#define ND_PAF_DEFAULT_VALUE            4096

#define ND_IAS_PAF_DEFAULT_VALUE        2048


#define MAX_SPECS_FOR_ND                9 /*5*/

#define MAX_SPECS_ND_SHOW               4

#define  ND_REBOOT_NOTIFY               05

/* Total memory for each entry for displaying */
#define  NBENTRY_SIZE                   128

/* MAX number of entries considered for displaying */
#define  NBENTRY_NUM                    20

#define IP6_MIB_NET2MEDIA               0xff
#define IP6_MIB_NET2MEDIAGETFIRST       0xf1
#define IP6_MIB_NET2MEDIAGET            0xf2
#define IP6_MIB_NET2MEDIAGETNEXT        0xf3

#define ND_SET_MINHOPLIMIT              1
#define ND_SET_MAXHOPLIMIT              255

/* Systrace Id */
#define  SYSTRC_IPV6_ND_BASE            03

/* Tick Proc timer - to feed Timeout event to TWL */
#define ND_TWL_TICKPROC_TIMER           10

/* Tick Proc timer timeout value - 500 Milli seconds */
#define ND_TWL_TICKPROC_INTERVAL        500

/* Number of External component */
#define IP6_ND_EXT_COMIF_CNT            4

/*  Reason: Local INTF ID declartions */
#define IP6_ND_LOCAL_INTF_ID_ICMP           1
#define IP6_ND_LOCAL_INTF_ID_ADDR           2
#define IP6_ND_LOCAL_INTF_ID_PP             3
#define IP6_ND_LOCAL_INTF_ID_FUN_ICMP       4
#define IP6_ND_LOCAL_INTF_ID_ADDR_IR_FUNC   5

/* Control Msg Event ID (17th Bit) - till 16th it is reserved */
#define IP6_ND_BIT16                            (1<<16)
#define IP6_ND_EVENT_CTRLMSG                    IP6_ND_BIT16

/* IO Board Exception Resolution, New Message queue
   Event type is defined to handle non-timer related
   events from ADDR*/
#define IP6_ND_BIT17                            (1<<17)
#define IP6_ND_EVENT_MSG                    IP6_ND_BIT17

/* Queue Msg Length */
#define IP6_ND_MAX_QUEUE_MSG_LEN            4

/* PAF Strings */
#define IP6_ND_PAF_STR_DEFRTR_PER_INF    "PAF_IP6ND_SPECS_DEFRTR_PER_INTF"
#define IP6_ND_PAF_STR_PREFLIST_PER_INTF "PAF_IP6ND_SPECS_PREFLIST_PER_INTF"
#define IP6_ND_PAF_STR_DESTCACHE         "PAF_IP6ND_SPECS_DESTCACHE_PER_HOST"

/* HCC Error : 80 chars - It is obvious */
#define IP6_ND_PAF_STR_TOTAL_NB_ENTRY       "PAF_LCS_IPV6_ND_SPECS_ENTRIES_NUM"
#define IP6_ND_PAF_STR_TOTAL_STAT_NB_ENTRY  "PAF_LCS_IPV6_ND_SPECS_TOT_STATIC_NB_ENTRIES"
#define IP6_ND_PAF_STR_INTF_NB_ENTRY        "PAF_LCS_IPV6_ND_SPECS_INF_NB_ENTRIES"
#define IP6_ND_PAF_STR_INTF_STAT_NB_ENTRY   "PAF_LCS_IPV6_ND_SPECS_INF_STATIC_NB_ENTRIES"
#define IP6_ND_PAF_STR_INTF_ADDR            "PAF_LCS_IPV6_ADDR_ND_SPECS_INF_ADDR_PREFIX_NUM"
#define IP6_ND_PAF_STR_TOTAL_NB_ENTRY_EXACT       "PAF_LCS_IPV6_ND_SPECS_ENTRIES_NUM_EXACT"
#define IP6_ND_PAF_STR_TOTAL_STAT_NB_ENTRY_EXACT  "PAF_LCS_IPV6_ND_SPECS_TOT_STATIC_NB_ENTRIES_EXACT"
#define IP6_ND_PAF_STR_INTF_NB_ENTRY_EXACT        "PAF_LCS_IPV6_ND_SPECS_INF_NB_ENTRIES_EXACT"
#define IP6_ND_PAF_STR_INTF_STAT_NB_ENTRY_EXACT   "PAF_LCS_IPV6_ND_SPECS_INF_STATIC_NB_ENTRIES_EXACT"

#define IP6_ND_PAF_MAX_STRINGS              3
#define IP6_ND_PAF_MAX_LCS_KEY_LEN          80

#define IP6ND_CONTROLLED_BY_PAF             1 /* ND Host is PAF controlled*/

/*----------------------------------------------*
*              Enumerated Data Types           *
*----------------------------------------------*/

/* ND Log types */
typedef enum tagIP6_ND_IClogID
{
    ND_LOGID_DUPADDR_DETECTED = 0,
    ND_LOGID_CONFIG_CONFLICT,
    ND_LOGID_LINK_LAYER_ADDR_CHANGE,

    /* New Queue Type is added, so the new LOG Message ..
       if creation of this Event Queue Fails */
    ND_LOGID_EVENT_QUEUE_CREATE_FAIL,


    /* Changed by Anand, for adhering to Log check list */
    ND_LOGID_TMR_QUEUE_CREATE_FAIL,
    ND_LOGID_CTRL_MSG_QUEUE_CREATE_FAIL,
    ND_LOGID_TMR_START_FAIL,
    ND_LOGID_SND_TO_IO_FAIL,
    ND_LOGID_MEMORY_ALLOC_FAIL,
    ND_LOGID_INIT_COM_FAILED,
    ND_LOGID_INVALID_PACKET,
    ND_LOGID_ACQUIRE_GLOBAL_SEM_FAILED,
    ND_LOGID_RELEASE_GLOBAL_SEM_FAILED,

    
    ND_LOGID_IAS_NBENTRY_ADD_FAIL,
    ND_LOGID_IAS_NBENTRY_DELETE_FAIL,
    ND_LOGID_IAS_NBENTRY_MODIFY_FAIL,


    ND_LOGID_LOG_MAX_NUM,

    ND_LOGID_LOG_MAX_NUM_ULONG = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_IClogID_E;

/* ND Debug types */
typedef enum tagIP6_ND_ICDbgID
{
    ND_DBGID_DBGRCVNDMSG = 0,
    ND_DBGID_DBGSNDNDMSG,
    ND_DBGID_DBGPREFIX,
    ND_DBGID_DBGNBENTRYSTATE,
    ND_DBGID_DBGADDNBENTRY,
    ND_DBGID_DBGDELNBENTRY,
    ND_DBGID_DUPLICATE,
    ND_DBGID_OPTION,
    ND_DBGID_SAME_IP,
    ND_DBGID_SRC_SLLA,
    ND_DBGID_SRCDST,
    ND_DBGID_TGT,
    ND_DBGID_TRG_TENTATIVE,
    ND_DBGID_TUNNEL,
    ND_DBGID_DST_FLAG,
    ND_DBGID_TRG_CACHE,
    ND_DBGID_SRC_TLLA,
    ND_DBGID_RA_ZERO,
    ND_DBGID_RA_UNICAST,
    ND_DBGID_RA_TIME,
    ND_DBGID_RA_CANNOT,
    ND_DBGID_NS_SEND,
    ND_DBGID_EXTHEADER,
    ND_DBGID_HOPLIMIT,
    ND_DBGID_NS_SEND_PROB,
    ND_DBGID_NA_SEND_PROB,
    ND_DBGID_RA_SEND_PROB,
    ND_DBGID_DBGADDRRESNBENTRY,
    ND_DBGID_DBGADDRSTOPNBENTRY,
    ND_DBGID_LINKLOCAL,
    ND_DBGID_INPKTNULL,
    ND_DBGID_IFISNULL,
    ND_DBGID_GETIPV6CTLBLKFAILED,
    ND_DBGID_GETNDINFOFAILED,
    ND_DBGID_OPTHDRERR,
    ND_DBGID_SEND_RACTLBLKNULL,
    ND_DBGID_SEND_CRTPKTFLD,
    ND_DBGID_SEND_NDINFONULL,
    ND_DBGID_NDCACHEERR,
    ND_DBGID_SGSN_STUB,
    ND_DBGID_TRG_TENTATIVE_DAD_DISABLE,
    ND_DBGID_ND_HOST_GENDBG_STR,
    ND_DBGID_ND_HOST_TIMER,
    ND_DBGID_ND_HOST_PREFIXDBG_STR,
    ND_DBGID_ND_HOST_PREFIX_TIMER,
    ND_DBGID_ND_HOST_MODIFY_PARAMS,

    
    ND_DBGID_IAS_NBENTRY_ADD_SUCCESS,
    ND_DBGID_IAS_NBENTRY_DELETE_SUCCESS,
    ND_DBGID_IAS_NBENTRY_MODIFY_SUCCESS,


#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
    ND_DBGID_NP_NBENTRY_ADD,
    ND_DBGID_NP_NBENTRY_DEL,
    ND_DBGID_NP_NBENTRY_RESET_ALL,
    ND_DBGID_NP_NBENTRY_RESET_STATIC,
    ND_DBGID_NP_NBENTRY_RESET_DYNAMIC,
    ND_DBGID_NP_NBENTRY_SHOW,
    ND_DBGID_NP_PLENTRY_ADD,
    ND_DBGID_NP_PLENTRY_DEL,
    ND_DBGID_NP_PLENTRY_RESET_ALL,
    ND_DBGID_NP_PLENTRY_SHOW,
    ND_DBGID_NP_DRLENTRY_ADD,
    ND_DBGID_NP_DRLENTRY_DEL,
    ND_DBGID_NP_DRLENTRY_RESET_ALL,
    ND_DBGID_NP_DRLENTRY_SHOW,
    ND_DBGID_NP_DC_ADD,
#endif
    ND_DBGID_DBGINFO_LEVEL,

    ND_DBGID_DBG_MAX_NUM,

    ND_DBGID_DBG_MAX_NUM_INT = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_ICDbgID_E;

/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* COM ID Info structure */
typedef struct tagIPB_IR_ND_COM_ID_INFO
{
    ULONG       ulLocalIntfId;
    CHAR  *szComName;
    ULONG       ulComId;
    CHAR  *szIntfName;
    ULONG       ulIntfId;
}IPB_IR_ND_COM_ID_INFO_S;

/* ND Module Info structure */
typedef struct tagIP6_ND_MOD_INFO_S
{
    ULONG ulModID;
    ULONG ulModSubId;
    ULONG ulTimerQueId;
    ULONG ulTaskId;
} IP6_ND_MOD_INFO_S;        /* If required needs to be added more fields */

/* Neighbor Entry structure */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagND_ENTRY_S
{
    ULONG       ulIfnetIndex;
    IN6ADDR_S   stIPv6Addr;
    UCHAR       ucLLAddr[MACADDRLEN];
    UCHAR       ucState;
    UCHAR       ucIsStaticEntry;
    ULONG       ulReachableTimeElapsed;
}ND_ENTRY_S;


/* Move to internal include */
typedef struct tagIP6NDREBOOTMSG_S
{
    ULONG          ulMsgType;      /*ND_REBOOT_NOTIFY*/
    ULONG          ulReserved1;
    ULONG          ulIfnetIndex;
    ULONG          ulReserved2;

}IP6NDREBOOTMSG_S;

/* Shell HA call back function */
typedef struct tagIP6_ND_SH_HA_CALLBACK_FUNC_S
{
    ULONG (*pfIP6_ND_SH_HA_BoardType)(VOID);

} IP6_ND_SH_HA_CALLBACK_FUNC_S;

/* Shell call back functions */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_SH_CALLBACK_FUNC_S
{
    VOID  (*pfIP6_ND_SH_ProcTimerEvents)(ND_TIMER_S *pstTimerMsg);

    VOID  (*pfIP6_ND_SH_ChangeBuildRun)(VOID  *pstIfNet);

    VOID  (*pfIP6_ND_SH_ChangeBuildRunCheckHotRecover)(VOID  *pstIfNet);

    ULONG (*pfIP6_ND_SH_TimerCreate)(ULONG ulMillSec,
                                VOID  (*pfTimerFunc)(VOID *),
                                VOID  *pArgTimerMessage,
                                ULONG *pulRetTimerID, ULONG ulFlag);

    ULONG (*pfIP6_ND_SH_TimerDelete)(ULONG ulTimerID);

    ULONG (*pfIP6_ND_SH_Tm_Now)(ULONG *pulRetTimeInMillSecHigh,
                                                ULONG *pulRetTimeInMillSecLow);
    ULONG (*pfIP6_ND_SH_Timer_GetInfo)(ULONG ulTimerID,
                                                VOS_TIMERINFO_S *pRetTimerInfo);
    ULONG (*pfIP6_ND_SH_Tm_BootInSec) (ULONG *pulSecond, ULONG *pulUSecond);

    VOID (*pfIP6_ND_SH_T_Delay)(ULONG ulMillisecond);

    ULONG (*pfIP6_ND_SH_TimerCreateWin)(ULONG ulMillSec,
                                VOID  (*pfTimerFunc)(VOID *),
                                VOID  *pArgTimerMessage,
                                ULONG *pulRetTimerID, ULONG ulFlag);

    /* Modified By Ahmed for Defect ID: AC4D05729 */
    /* VOID  (*pfIP6_ND_SH_AsynEnQue)(ND_TIMER_S *pstRcvMsg);*/
    VOID  (*pfIP6_ND_SH_AsynEnQue)(IP6_ND_EVENTMSG_S *pstRcvMsg);

    ULONG (*pfIP6ND_SH_LogToIPOSIC)(ULONG eLogID, ...);

    ULONG (*pfIP6ND_SH_DbgToIPOSIC)(ULONG eDbgID, ...);

    ULONG (*pfIP6_ND_SH_Addr6ToStr)(const IN6ADDR_S *pstIp6Addr, char *szAddr);

#if (VRP_YES == IP6_NDHOST)

    ULONG (*pfIP6_ND_SH_CtrlMsgQue_Write)(UINTPTR ulMsg[4], ULONG ulFlags,
                          ULONG ulTimeOutInMillSec);
    ULONG (*pfIP6_ND_SH_Ev_Write_ToNDTask)(ULONG ulEvent);

    /* BEGIN : NDHOST SDV Defect AC4D05450, Anand */
    ULONG (*pfIP6_ND_SH_Is_CtrMsg_Queue_Full) (VOID);
#endif /* (VRP_YES == IP6_NDHOST) */

} IP6_ND_SH_CALLBACK_FUNC_S;


/* Shell call back functions for Timer wheel */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_SH_TWLCALLBACK_FUNC
{
    /* Creates Non-PeriodTime (NoLoop timer)*/
    ULONG (*pfIP6_ND_SH_StartTimer)(ULONG ulTimeValue,VOID *pvTimerMsg,
                                    ULONG *pulTimerid);

    /* Delete a  non-periodical / periodical timer. */
    ULONG (*pfIP6_ND_SH_StopTimer)(ULONG ulTimerID);

    /* For a given timer cancel old timing process and refresh it with new time
    value */
    ULONG (*pfIP6_ND_SH_RefreshTimer)(ULONG ulTimerID,ULONG ulNewTimeValue);

    /* When a TWL instance is working after each unit time passed this
    function must be called.*/
    ULONG (*pfIP6_ND_SH_TickProc)(VOID);

    /* Get the rest time value of a timer in millisecond. */
    ULONG (*pfIP6_ND_SH_GetRestTimeValue)(ULONG ulTimerID,
                                      ULONG *pulRestTimeValue);

    /* Get timer parameters. */
    ULONG (*pfIP6_ND_SH_GetTimerPara)(ULONG ulTimerID,VOID *pvTimerMsg);
}IP6_ND_SH_TWLCALLBACK_FUNC_S;

/* Global Prefix List Structure - Used in Display */
typedef struct tagND_GlobalPrefix_Info
{
    IN6ADDR_S   stPrefix;           /* Prefix */
    ULONG       ulIfnetIndex;       /* Interface Index */
}IP6_ND_GLOBALPREFIX_INFO_S;

/* Timer message structure for ND host */
typedef  struct tagIP6_ND_Host_TmrMsg
{
    ULONG ulTimerType;      /* Timer type */
    ULONG ulIfIndex;        /* Interface Index */
    UINTPTR ulDataPtr;        /* Address(Router/Prefix - Address) */
    ULONG ulReserved;       /* Reserved field */
}IP6_ND_HOST_TMRMSG_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ND_COM_PUBLIC_H*/

