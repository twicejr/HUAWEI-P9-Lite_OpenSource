/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

*******************************************************************************
*                              addr_int_pub.h
*
*    Module Name :  ADDR
*    Version     :  IPBIRV100R003.IPv6.E001
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define the structures and macro's used by core
*                    and shell of component
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik      Created for including all component
*                           public definitions in this file,
*                           for IPB IR V1R2 - COMMOM re-arrange
******************************************************************************/

#ifndef _ADDR_INT_PUB_H
#define _ADDR_INT_PUB_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/*----------------------------------------------*
 *              Macros                          *
 *----------------------------------------------*/

#define SID_IP6IFADDR_S    0X01
#define SID_IP6IFNET_S     0X02
#define SID_SCOPE_S        0X03

/* SID for RPC CMD message */
#define SID_IP6IPCMDA      0X04
#define SID_IP6INTID       0X05
#define SID_IP6MULADDR     0x06
#define SID_IP6MULADDRRC   0x07

/* SID for RPC message */
#define SID_HA_ADDR_INIT   0x07
#define SID_IP6ADDRQUERY   0x08

#define SID_IP6INTID_S     0X09
#define SID_IP6_ADDRHA     0x10


#define IP6_ADDR_SLAVE_NOT_READY    0
#define IP6_ADDR_BATCH_BACKUP_GOING 1
#define IP6_ADDR_HSB_NORMAL         2


#define IPv6_STATUS_PREFERRED             1
#define IPv6_STATUS_DEPRECATED            2
#define IPv6_STATUS_INVALID               3
#define IPv6_STATUS_INACCESSIBLE          4
#define IPv6_STATUS_UNKNOWN               5


#define AMB      0
#define SMB      1


#define IP6_ADDR_BK_RESET             0
#define IP6_ADDR_BK_IF_ADDRFLAG       1
#define IP6_ADDR_BK_ADD_ADDR          2
#define IP6_ADDR_BK_DEL_ADDR          4
#define IP6_ADDR_BK_DAD_INFO_PRESENT  8
#define IP6_ADDR_BK_BATCH             16
#define IP6_ADDR_BK_SYNC              32
#define IP6_ADDR_BK_INTIDCHANGE       64

/*ulEventtypes in HA*/
#define IP6_ADDR_BATCH_DATA  3
#define IP6_ADDR_REAL_DATA   4


#define IP6_ADDR_IPC_RPC_TIMEOUT    5000
#define IP6_ADDR_IPC_RPC_PRIORITY   4


#define     IP6_ADDR_POS_DEF_MTU            4470
#define     IP6_ADDR_POS_MAX_MTU            9660

#define     IP6_ADDR_GE_DEF_MTU            1500
#define     IP6_ADDR_GE_MAX_MTU            10000

/* Timer message types for PPP delay timer */
#define IP6_ADDR_PPPDELAY_TIMER      0
#define IP6_ADDR_REFCOUNTSYNC_TIMER  1

#define  IP6_CONFIG_ADDR         1
#define  IP6_GET_INTERFACEID     2

#define  IP6_ADDR_DEL_MULTI      3   /* Request type to send delete multicast to
                                        IO board */
#define  IP6_ADDR_ADD_MULTI      4   /* Request type to send add multicast
                                        to IO board */

#define  IP6_GET_INTERFACEMAC    5   /* Get mac addres */
#define  IP6_ADDR_GET_DADSTATE   6
#define  IP6_ADDR_GET_IFSTATE    7
#define  IP6_ADDR_ADD_CONFIG     8
#define  IP6_ADDR_SYNC_REFCOUNT  9

/* level 3 */
#define  IP6_ADDR_GET_NEGMTU            10

/* can be remove - As same exist in addr_def and is pruned */
#define  IP6_ADDR_CONFIGADDR_IO         11
#define  IP6_ADDR_AUTOADDR_IO           12

/* Start: RFC4443 compliance changes */
#define IP6_ADDR_EXT_COMIF_CNT 3

/* End: RFC4443 compliance changes */

#define IP6_ADDR_LOCAL_FUN_INTF_ID_ND      1
#define IP6_ADDR_LOCAL_FUN_IR_INTF_ID_ND   2
#define IP6_ADDR_LOCAL_FUN_INTF_ID_IND     3

/* Start: RFC4443 compliance changes */
#define IP6_ADDR_LOCAL_FUN_INTF_ID_ICMP    4

/* End: RFC4443 compliance changes */

#define  SYSTRC_IPV6_ADDR_BASE        02

/* macros for filling/validating SPECS_RES_VALUE_S */
#define ADDR_CONTROLLED_BY_PAF_LCS      1
#define ADDR_CONTROLLED_BY_PAF          0

#define SID_IP6_AUTOCFG_ADDRINFO    0x11
#define SID_IP6_STATELESS_ADDRTIMER 0x12
#define SID_IP6_INITDELAY_TIMER     0x13
#define SID_IP6_STATEFUL_ADDRTIMER  0x14

#define IP6_ADDR_MAX_TM_PARA_LEN          4

/*---------------------------------------------*
*              Enumerated Data Types           *
*----------------------------------------------*/

/* Log ID */
typedef enum tagIP6_Addr_IClogID
{
    ADDR6_LOGID_TMR_CRT_FAIL = 0,
    ADDR6_LOGID_INTF_CRT_EVENT,
    ADDR6_LOGID_INTF_DEL_EVENT,
    ADDR6_LOGID_INTF_ID_CHANGE,
    ADDR6_LOGID_LINK_UP,
    ADDR6_LOGID_LINK_DOWN,
    ADDR6_LOGID_LLC_TYPE_UNKNOWN,
    ADDR6_LOGID_INIT_COM_FAILED,
    ADDR6_LOGID_CONFIG_TO_RM_SENT,
    ADDR6_LOGID_RPC_FAIL_ADDMULTI,
    ADDR6_LOGID_RPC_FAIL_DELMULTI,
    ADDR6_LOGID_IF_NOT_EXIST,
    ADDR6_LOGID_TMR_EXP_ADDRESS_NOT_EXISTS,
    ADDR6_LOGID_LIFETIME_TMR_START_FAIL,
    ADDR6_LOGID_ACQUIRE_GLOBAL_SEM_FAILED,
    ADDR6_LOGID_RELEASE_GLOBAL_SEM_FAILED,
    ADDR6_LOGID_MANUALADDR_OVERWRITE_AUTOCONFIGADDR,
    ADDR6_LOGID_AUTOCFGADDR_DELETE_FORMANUALCFG,
    ADDR6_LOGID_GETBOOTTIME_FAILED,

    
    ADDR6_LOGID_IAS_NOTIFY_ADDR_ADD_FAIL,
    ADDR6_LOGID_IAS_NOTIFY_ADDR_DELETE_FAIL,
    ADDR6_LOGID_IAS_NOTIFY_ADDR_ADD_SUCCESS,
    ADDR6_LOGID_IAS_NOTIFY_ADDR_DELETE_SUCCESS,


    ADDR6_LOGID_MAX,
    ADDR6_LOGID_MAX_INT = IP6_ADDR_MAX_ENUM_VALUE

}IP6_Addr_IClogID_E;


/* Debug ID */
typedef enum tagIP6_Addr_ICDbgID
{
    ADDR6_DBGID_DBG = 0,
    ADDR6_DBGID_MAX,
    ADDR6_DBGID_MAX_INT = IP6_ADDR_MAX_ENUM_VALUE
}IP6_Addr_ICDbgID_E;


/* 注册命令行时的信息字符串索引(枚举类型) */
enum enum_Ip6Addr
{
    Ip6Addr_KeyWord_IP,
    Ip6Addr_KeyWor_Address,
    Ip6Addr_IPAddress,

    Ip6Addr_Prefix_1_TO_128,


    Ip6Addr_Prefix_1_TO_64,


    Ip6Addr_PrefixLen,
    Ip6Addr_Linklocal,
    Ip6Addr_Eui64,
    Ip6Addr_Auto,
    Addr_Mtu_Mtu,
    Addr_Mtu_MtuValue,

    /*Display Interface Command*/
    IP6_DISPLAYCMD_IPV6,
    IP6_DISPLAYINTF_INTERFACE,
    IP6_DISPLAYINTF_IFTYPE,
    IP6_DISPLAYINTF_IFNUM,
    IP6_DISPLAYINTF_IFNAME,
    IP6_DISPLAYCMD_BRIEF,

    /*H**e mode debug command*/
    IP6_DEBUG_ONOFF,
    IP6_DEBUG_LEVEL,
    IP6_DEBUG_CMD,
    IP6_ADDR_CMDELEMENT_SHOWCOM,
    IP6_ADDR_CMDELEMENT_SHOWCOMVER,
    IP6_ADDR_CMDELEMENT_SHOWCOMVERND,
    IP6_ADDR_CMDELEMENT_SHOWCOMTESTVER,
    IP6_ADDR_CMDELEMENT_SHOWCOMTESTVERND,
    IP6_Addr_MAX,
    Ip6Addr_PADDING = IP6_ADDR_MAX_ENUM_VALUE
};

/* Timer Types */
typedef enum tagIP6_ADDR_TimerType
{
    IP6_NDHOST_INITIALDELAY_TIMER = 1,
    IP6_NDHOST_STATEFUL_TIMER,
    IP6_NDHOST_STATELESS_TIMER,
    IP6_NDHOST_PREFERRED_LIFETIME,
    IP6_NDHOST_VALID_LIFETIME,
    IP6_NDHOST_TIMERTYPE_MAX,
    IP6_NDHOST_TIMERTYPE = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ADDR_TIMERTYPE_E;

/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* addr HA callback functions */
typedef struct tagIP6_ADDR_HA_CALLBACK_FUNC_S
{
    ULONG (*pfIP6_Addr_SH_HA_BoardType)(VOID);
    ULONG (*pfIP6_Addr_SH_HA_RealTimeBackup_Send)(UCHAR *, ULONG);
    ULONG (*pfIP6_Addr_SH_HA_BatchBackup_Send)(UCHAR *, ULONG);
    ULONG (*pfIP6_Addr_SH_HA_MemFreeup)(VOID *);
    VOID* (*pfIP6_Addr_SH_HA_MemAllocate) (ULONG);
}IP6_ADDR_HA_CALLBACK_FUNC_S;

/*addr component ID information*/
typedef struct tagIPB_IR_ADDR_COM_ID_INFO
{
    ULONG ulLocalIntfId;
    CHAR *szComName;
    ULONG ulComId;
    CHAR *szIntfName;
    ULONG ulIntfId;
}IPB_IR_ADDR_COM_ID_INFO_S;

/*module information structure*/
typedef struct tagIP6_ADDR_MOD_INFO_S
{
    ULONG ulModID;
    ULONG ulModSubId;
    ULONG ulLocalIPC_Tid;
    ULONG ulPeerIPC_Tid;
}IP6_ADDR_MOD_INFO_S;


/* Structure for AM Timer */
typedef  struct tagAM_Timer
{
    ULONG   ulTimerType;
    ULONG   ulTimerId;
    ULONG   ulIfIndex;
    ULONG   ulReserved0;
}IP6_Addr_TIMER_S;


typedef VOID (*pfAddr6TimerFunc)(VOID *);

/*addr shell callback functions*/
/* WARNING-> The numbers of structure elements shall be moderate i.e <= 5 */
/* The Above HCC Warning is obvious - Will not be addressed */
typedef struct tagIP6_ADDR_SH_CALLBACK_FUNC_S
{
    VOID  (*pfIP6_Addr_SH_ProcTimerEvents)(IP6_Addr_TIMER_S *pstTimerMsg);
    ULONG (*pfIP6_Addr_SH_BuildRun)(CHAR *pszSectionName,
                                    CHAR **pszBuildRunInfo);
    ULONG (*pfIP6_Addr_SH_TimerCreate) (ULONG ulTaskID,
                                        ULONG ulMsgQueID,
                                        ULONG ulMillSec,
                                        pfAddr6TimerFunc pfTimerFunc,
                                        VOID  *pArg,
                                        ULONG *pulRetTimerID, ULONG ulFlag);
    ULONG (*pfIP6_Addr_SH_TimerCreate_SockRun) (ULONG ulMillSec,
                                        pfAddr6TimerFunc pfTimerFunc,
                                        VOID  *pArg,
                                        ULONG *pulRetTimerID, ULONG ulFlag);
    ULONG (*pfIP6_Addr_SH_Tm_Now) (ULONG *pulRetTimeInMillSecHigh,
                                              ULONG *pulRetTimeInMillSecLow);
    VOID (*pfIP6_Addr_SH_ReplaceBuildRunInfo) (CHAR *szIfName, ULONG ulModuleId,
                                                  CHAR *szBuildRunInfo);

    ULONG (*pfIP6_Addr_SH_LogToIPOSIC)(ULONG ulLogID, ...);
    ULONG (*pfIP6_Addr_SH_DbgToIPOSIC)(ULONG ulLogID, ...);
    ULONG (*pfIP6_Addr_SH_AddrStToStr)(const IN6ADDR_S *pstAddress,
                                          char *szAddr);

    
    ULONG (*pfIP6_Addr_SH_Tm_BootInSec)(ULONG *pulSecond, ULONG *pulUSecond);

    
} IP6_ADDR_SH_CALLBACK_FUNC_S;

/*structure for RPC request */
typedef  struct  tagIp6Rpc_Request
{
    ULONG  ulIfIndex;
    ULONG  ulRequestType;
    ULONG  ulCmd;
    IN6ADDR_S stIp6Addr;
}IP6RPC_REQUEST_S;

/* structure for interface ID reply */
typedef  struct  tagIp6GetInterfaceId_Reply
{
    IP6_INTERFACEID_S  stInterfaceId;
}IP6_GETINTERFACEID_REPLY_S;

/* Timer-Related Callbacks */
typedef struct tagIP6_ADDR_TIMER_CALLBACK_FUNC_S
{
    ULONG (*pfIP6_Addr_SH_CreateNonPeriodicTimer)(VOID *pvTimerMsg, 
                                                      ULONG ulTimeMilliSec,
                                                      IP6_ADDR_TIMERTYPE_E enTimerType, 
                                                      ULONG *pulTimerId);
    ULONG (*pfIP6_Addr_SH_DeleteTimer)(ULONG ulTimerID);
    ULONG (*pfIP6_Addr_SH_GetTimerInfo)(ULONG ulTimerID, UINTPTR aulTimerMsgInfo[IP6_ADDR_MAX_TM_PARA_LEN]);
    ULONG (*pfIP6_Addr_SH_GetLeftoverTime)(ULONG ulTimerID, ULONG *pulRestTimeValue);
    ULONG (*pfIP6_Addr_SH_RefreshTimer)(ULONG ulTimerID, ULONG ulNewTimeValue);
}IP6_ADDR_TIMER_CALLBACK_FUNC_S;

/* Timer Control Message Structure */
typedef struct tagIp6_Addr_Timer_Ctrl_Msg
{
    ULONG   ulTimerType;        /* Type : Initial Delay/Stateful/Stateless*/
    UINTPTR   ulHandleToTimerMsg;      /* Handle to Timer Message */
}IP6_ADDR_TIMER_CTRL_MSG;


/* Timer Message for Stateless Address Lifetime */
typedef struct tagIP6_Addr_Stateful_TimerMsg
{
    ULONG     ulTimerType;         /* Preferred/Valid Lifetime Timer */
    ULONG     ulIfIndex;           /* IfNet Index */
    IN6ADDR_S stIp6Addr;           /* Stateless Address/Stateful Address */
}IP6_ADDR_STATEFUL_TIMER_S;

/* Timer Message for Stateful Address Lifetime */
typedef struct tagIP6_Addr_Stateless_TimerMsg
{
    ULONG     ulTimerType;               /* Preferred/Valid Lifetime Timer */
    ULONG     ulIfIndex;                 /* IfNet Index */
    IN6ADDR_S stIP6AddrPrefix;           /* Stateful Address Prefix */
    IN6ADDR_S stIP6AddrMask;             /* Mask Corresponding to Length */
}IP6_ADDR_STATELESS_TIMER_S;


/* Timer Message for Address Lifetime */
typedef struct tagIP6_Addr_InitialDelayMsg
{
    ULONG     ulIfIndex;           /* IfNet Index */
}IP6_ADDR_INITIALDELAY_TIMER_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ADDR_INT_PUB_H */

