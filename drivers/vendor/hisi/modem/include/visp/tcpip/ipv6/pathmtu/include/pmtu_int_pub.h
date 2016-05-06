/*-----------------------------------------------------------------------
*                              pmtu_com_pub.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  PMTU
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
************************************************************************/

#ifndef _PMTU_COM_PUBLIC_H
#define _PMTU_COM_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

#include "ipv6/ircommon/pathmtu/pmtu_ir_pub.h"

/* ----------------------------------------------*
 *              Macros                          *
 *---------------------------------------------- */

#define IPB_IR_PMTU_MAX_VAL                 0xFFFFFFFF

/* For systrace id calculation */
#define SYSTRC_IPV6_PMTU_BASE           07

/* HA states */
#define IP6_PMTU_SLAVE_NOT_READY        0
#define IP6_PMTU_BATCH_BACKUP_GOING     1
#define IP6_PMTU_HSB_NORMAL             2


/* SIDs for VOS_Malloc functions */
#define SID_IP6_PMTU_AddSBYIO               1
#define SID_IP6_PMTU_AddPMTUEntry           2
#define SID_IP6_PMTU_ModifyEntry            3
#define SID_IP6_PMTU_AddSockidEntry         4
#define SID_IP6_PMTU_GetFirstObj            5
#define SID_IP6_PMTU_GetNextObj             6
#define SID_IP6_PMTU_SearchObj              7
#define SID_IP6_PMTU_HotInsertProc          8
#define SID_PMTU                            9
#define SID_IP6_PMTU_HA_DataSmoothOutside   10
#define SID_IP6_PMTU_SH_HA_MemAllocate      11
#define SID_HA_INIT                         12
#define SID_IP6_PMTU_HA_SMOOTH              13
#define SID_IP6_PMTU_BUILDRUN               14
#define SID_IP6_PMTU_IfnetHotNotifyCB       15


/* HA backup event types
  possible values for ulEventType in pfIP6_PMTU_HA_SetBackupData */
#define IP6_PMTU_BATCH_DATA             3
#define IP6_PMTU_REAL_DATA              4


/* macros for filling/validating SPECS_RES_VALUE_S */
#define PMTU_PAF_DEFAULT_VALUE          64
#define PMTU_AVAIL_VALUE                1024

/* Max CLI entries supported by PMTU */
#define PMTU_PAF_STAT_MAX                 300

/* values to fill IPB_IR_PMTU_COM_ID_INFO_S */
#define IP6_PMTU_EXT_COMIF_CNT          0x4
#define IP6_PMTU_LOCAL_INTF_ID_ADDR_FUN        3001
#define IP6_PMTU_LOCAL_INTF_ID_ADDR_IR_FUN     3002
#define IP6_PMTU_LOCAL_INTF_ID_ND_FUN          3003
#define IP6_PMTU_LOCAL_INTF_ID_ND_IR_FUN       3004

#define PMTU_PAF_STR_TOTAL_ENTRIES  "PAF_LCS_IPV6_PMTU_SPECS_ENTRIES_NUM"
#define PMTU_PAF_STR_STAT_ENTRIES   \
                                "PAF_LCS_IPV6_PMTU_SPECS_STATIC_ENTRIES_NUM"


/* ----------------------------------------------*
 *              Enumerated Data Types           *
 *---------------------------------------------- */

/* IC log IDs */
typedef enum tagIP6_PMTU_IClogID
{
    PMTU_LOGID_ADD_ENTRY_NO_FREEMEM = 0,
    PMTU_LOGID_GADS_CREATE_OBJ_FAIL,
    PMTU_LOGID_GADS_VERIFY_MINDEX_FAIL,
    PMTU_LOGID_ENTRY_POPULATION_FAIL,
    PMTU_LOGID_GADS_DELETE_OBJ_FAIL,
    PMTU_LOGID_SYNCH_MAIN_IO_FAIL,
    PMTU_LOGID_HA_MEM_FAIL,
    PMTU_LOGID_REALTIME_BKP_FAIL,
    PMTU_LOGID_AGE_TMR_CRT_FAIL,
    PMTU_LOGID_AGE_TMR_DLT_FAIL,
    PMTU_LOGID_CACHE_TMR_CRT_FAIL,
    PMTU_LOGID_CACHE_TMR_DLT_FAIL,
    PMTU_LOGID_INIT_COM_FAILED,
    PMTU_LOGID_ACQUIRE_GLOBAL_SEM_FAILED,
    PMTU_LOGID_RELEASE_GLOBAL_SEM_FAILED,
    PMTU_LOGID_MAX,
    PMTU_LOGID_MAX_INT = IPB_IR_PMTU_MAX_VAL
}IP6_PMTU_IClogID_E;


/* IC Dbg IDs */
typedef enum tagIP6_PMTU_ICDbgID
{
    PMTU_DBGID_INFO_DBG = 0,

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
    PMTU_DBGID_NP_ENTRY,
    PMTU_DBGID_NP_RESET,
    PMTU_DBGID_NP_GENERIC,
#endif

    PMTU_DBGID_MAX,
    PMTU_DBGID_MAX_INT = IPB_IR_PMTU_MAX_VAL
}IP6_PMTU_ICDbgID_E;

/* Input for pfIP6_PMTU_Init_Com_NEW */
typedef struct tagIPB_IR_PMTU_COM_ID_INFO
{
    ULONG ulLocalIntfId;
    CHAR *szComName;
    ULONG ulComId;
    CHAR *szIntfName;
    ULONG ulIntfId;
}IPB_IR_PMTU_COM_ID_INFO_S;

/* To pass HA function pointers from shell to core. */
typedef struct tagPMTUShellHABackUpSet
{
    ULONG (*pfIP6_PMTU_SH_HA_RealTimeBackup_Send)(UCHAR *, ULONG);
    ULONG (*pfIP6_PMTU_SH_HA_BatchBackup_Send)(UCHAR *, ULONG);
    ULONG (*pfIP6_PMTU_SH_HA_MemFreeup)(VOID *);
    VOID * (*pfIP6_PMTU_SH_HA_MemAllocate) (ULONG);
} PMTU_SHELL_HA_BACUP_SET_S;

/* To pass timeout functions from shell to core. */
typedef struct tagPMTUShellTimeoutCallBackSet
{
    VOID (*pfIP6_PMTU_SH_Cachetimeout_handler) (VOID);/* Cache timeout */
    VOID (*pfIP6_PMTU_SH_Agetimeout_handler) (VOID); /* Age timeout */
} PMTU_SHELL_TIMEOUT_CALLBACUP_SET_S;

 /* ICMP Error - Packet Too Big Information. */
typedef struct tagTooBigInfo
{
    ULONG       ulZoneid;        /* zone index */
    ULONG       ulPPmtu;        /* Proposed PMTU from too big message */
    IN6ADDR_S   stDA;
    IN6ADDR_S   stFaddr;     /* Foreign Address from too big message */
    IN6ADDR_S   stLaddr;    /* Local Address from too big message */
    USHORT      usFport;     /* Foreign port from too big message */
    USHORT      usLport;   /* Local port from too big message */
    UCHAR       ucProtocol;    /* Protocol from too big message */
    UCHAR       ucReserved[3];
}TOO_BIG_INFO_S;

/* To pass Debug function from shell to core */
typedef struct tagPMTUShellDebugCallBackSet
{
    ULONG (*pfIP6_Pmtu_SH_DbgToIPOSIC)(ULONG ulLogID, ...);

} PMTU_SHELL_DEBUG_CALLBACK_SET_S;

/* Argument for pfIP6_PMTU_SetModuleInfo */
typedef struct tagPMTUModInfo
{
    ULONG ulModID;          /* Module ID */
    ULONG ulSubModID;       /* Sub Module ID */
    ULONG ulLocalIPC_Tid;   /* Local IPC id */
    ULONG ulPeerIPC_Tid;    /* Remote IPC id */
} PMTU_MOD_INFO_S;

/* Shell callbacks registered to core */
typedef struct tagIP6_PMTU_SH_CALLBACK_FUNC_S
{
    ULONG (*pfIP6_PMTU_SH_Timer_Create)(ULONG, VOID (*)(VOID*), VOID *,
        ULONG*, ULONG);
    ULONG (*pfIP6_PMTU_SH_Timer_Delete)(ULONG);
    ULONG (*pfIP6_PMTU_SH_Que_Write)(UINTPTR [4], ULONG, ULONG);
    ULONG (*pfIP6_PMTU_SH_Ev_Write)(ULONG);
    ULONG (*pfIP6_Pmtu_SH_LogToIPOSIC)(ULONG ulLogID, ...);
    ULONG (*pfIP6_Pmtu_SH_AddrStToStr)(const IN6ADDR_S *pstAddress,
        char *szDstAddr);
} IP6_PMTU_SH_CALLBACK_FUNC_S;


#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _PMTU_COM_PUBLIC_H */

