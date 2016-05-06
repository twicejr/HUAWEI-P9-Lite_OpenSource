
#ifndef _IP6_PMTU_VAR_H
#define _IP6_PMTU_VAR_H

#ifdef  __cplusplus
extern "C"{
#endif

/* Global Aging Timer initialized to ten. Only CLI can modify this value.
   Range : 10 to 100.*/
extern USHORT g_usPmtuAgingTimer;

/* When we start aging timer this variable is initialized to 1.*/
extern ULONG g_ulPmtuStartAgeTimer;

/* This will get incremented by one when add a new PMTU entry and it will get
   decremented by one when a PMTU entry deleted.*/
extern ULONG g_ulPmtuTotalPmtuEntries;

/* Total number of CLI configured PMTU entries. This will get incremented
   by one whenever a CLI adds or modifies a PMTU entry and it will get
   decremented by one when CLI deletes a PMTU entry.*/
extern ULONG  g_ulPmtuTotalCliEntries;

/* Value will range from zero to nine. This is used to maintain last ten-minute
   access count. So that while caching we can delete least used entry in last
   ten minutes.*/
extern ULONG g_ulPmtuCachingIndex;

/* For creating and deleting aging timer.*/
extern ULONG g_ulAgingTimerId;

/* For creating and deleting caching timer.*/
extern ULONG g_ulCachingTimerId;

/* The HA status Enable/Disable.*/
extern ULONG g_ulHACoreState;

/* The CLI status.*/
extern ULONG g_ulPMTUCliState;

/* IPC will use this groupID to obtain members of multicast group.*/
extern ULONG g_ulPMTUMipcGroupId;

/* To identify groupnode.*/
extern ULONG g_ulPMTUMipcGroupNode;

/* The structure to store Debug callbacks from shell.*/
extern PMTU_SHELL_DEBUG_CALLBACK_SET_S  g_stShellDebugCallBackup;

/* Destination bucket for traversing all pmtu entries.*/
extern MULTIPLE_INDEX_NODE_S *g_stDABucket[MAX_BUCKET];

/* Socket bucket for all sockets..*/
extern SOCKET_IDENTITY_NODE_S *g_stSocketBucket[MAX_BUCKET];

/* Useful for IP6_PMTU_RegSocketCallBack().*/
extern PMTU_CALLBACKUP_SET_S    g_stPmtuSockCallBack;

/* Useful for IP6_PMTU_RegShellCallbackFunc().*/
extern IP6_PMTU_SH_CALLBACK_FUNC_S g_stShellCallBack;

/* Shell registers timeout functions to PMTU component.*/
extern PMTU_SHELL_TIMEOUT_CALLBACUP_SET_S g_stShellTimeoutCallBack;

/* To get shell's HA function pointers.*/
extern PMTU_SHELL_HA_BACUP_SET_S g_stPMTUHACallBack;

/* GADS's handle initialised in pmtu init function.*/
extern GADS_HANDLE g_hGADS;

/* get all resource specific information from PAF.*/
extern SPECS_RES_VALUE_S g_stIP6_PMTU_TotalResSpecVal;

/*  IAS changes Start :
    Maximum static PMTU entries is changed from macro to PAF.
*/
/* get static resource specific information from PAF.*/
extern SPECS_RES_VALUE_S g_stIP6_PMTU_StaticResSpecVal;

/* All module related information from shell.*/
extern PMTU_MOD_INFO_S g_stModuleInfo;

/* From address management.*/
extern struct IIF_IP6_ADDR_GENERIC_IR_FUNVtbl *g_pstPMTU_ADDR_IR_FUNVtbl;
extern struct IIF_IP6_ADDR_GENERIC_FUNVtbl *g_pstPMTU_ADDR_FUNVtbl;

extern ULONG g_ulMaxPMtu;


/*ND fun Vtable*/
extern struct IIF_IP6_ND_GENERIC_FUNVtbl        *g_pstPMTU_ND_FUNVtbl;
extern struct IIF_IP6_ND_GENERIC_IR_FUNVtbl     *g_pstPMTU_ND_IR_FUNVtbl;

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
extern ULONG (*g_pfIP6_PMTU_PPIOperation)(ULONG ulOperType, VOID * pData);
extern UCHAR  g_ucPMTUFlag;
#endif


extern TCPIP_IP6_PTU_USER_HOOK_S g_stPmtuUserHook;

#ifdef  __cplusplus
}
#endif

#endif
