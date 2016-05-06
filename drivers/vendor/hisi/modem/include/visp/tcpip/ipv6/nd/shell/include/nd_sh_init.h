/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*   Project Code    : VRP5.0
*   Module Name     : IP6 ND
*   Version         : Initial Draft
*   File Name       : ND_SH_INIT.H
*   Create Date     : 2003/06/25
*   Author          : Santosh G Kulkarni
*   Description     : contains shell init function prototypes
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef _ND_SH_INIT_H
#define _ND_SH_INIT_H

#ifdef    __cplusplus
extern "C"{
#endif


extern ULONG ulVRPTID_SOCK;
extern ULONG ulSOCKTmrQueID;


#define SID_HA_ND_INIT          0x000C
#define SID_SH_NDTIMER_S        0x000D

#define IP6_ND_ENABLE_CLI     1
#define IP6_ND_DISABLE_CLI   0

#define ND_QUEUE_TIMER_LENGTH              2500

/* New Queue Type is added, so the new Macro is defined 
   for Event Queue Length .. */
#define ND_QUEUE_EVENT_LENGTH              500


typedef VOID  (*pfConvtoVoidFunc)(VOID *);

typedef ULONG (*PAF_SHOWNDEFFECTVALUE_HOOK_FUN)(VOID);

ULONG IP6_ND_SH_Init();
ULONG IP6_ND_SH_DeInit();
ULONG IP6_ND_SH_NotifyCliChange(ULONG ulCliState);

VOID IP6_ND_IfnetHotNotifyCB (ULONG ulEvent, ULONG ulSlot,
                                      VOID *pstIfnet, ULONG ulIfIndex);
VOID ND_MainTaskEntry(UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2,
                              UINTPTR ulArg3);

ULONG IP6ND_SH_LogToIPOSIC(ULONG ulLogID, ...);
ULONG IP6ND_SH_DbgToIPOSIC(ULONG ulDbgID, ...);

#if(TCPIP_IN_VRP == VRP_NO)
extern ULONG TCPIP_Get_PAF_ResValue (SPECS_RES_VALUE_S *pstResValue);
#endif

//VOID VRP_LOCK(VOID);
//VOID VRP_UNLOCK(VOID);

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
#define IP6_ND_REG_NPCALLBACK_CORE()                                \
{                                                                     \
    IPV6_PPI_HOOK_S *pstNPCallBack = NULL;                            \
    (VOID)IP6_PPI_GetValue(&pstNPCallBack);                           \
    if (pstNPCallBack)                                                \
    {                                                                \
        (VOID)g_pstNDINTInitTable->pfIP6_ND_RegNPCallback(     \
                                                pstNPCallBack);       \
    }                                                                 \
}
#else
#define IP6_ND_REG_NPCALLBACK_CORE()
#endif

/* Added by fengjing209023 for DTS2014061301920 BALONG DAD优化需求，打开后不做DAD和initial delay */
extern ULONG g_ulNDNODADSwitch;

#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif        /* end of _ND_SH_INIT_H_ */
