/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Ipp4_inc.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: PP4组件接口定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_PP4_INC_H_
#define _I_PP4_INC_H_


struct tagMBuf;
struct tagROUTE;
struct tagPROTOSW;
struct tagIPMOPTIONS;
struct tagPp4ModuleInfo;
struct tagIPSTAT;
struct tagPp4ICCallbackSet;
struct tagIPIFNET;
struct tagIFNET;

typedef ULONG (*IP_PP4_DELEVERUP_POSITION_HOOK_FUNC)(struct tagMBuf *pstMBuf);
typedef ULONG(*IP_PP4_ETHVLN_ICMPREDIRECT_HOOK_FUNC)(IFNET_S *pstIf);

DECLARE_INTERFACE( IIF_IPV4_IP_PP4_ComIntFUN ) 
{
    IUNKNOWN_METHODS
  
    /* method dealing with the received IPv4 packet, called by Queue dispatcher */
    METHOD_(ULONG, pfIP_Input)(struct tagMBuf * pMBuf);    
    
    
    /* method sending packet out to if in called board */
    METHOD_(ULONG, pfIP_IF_Output)( struct tagMBuf *pMBuf, ULONG ulPmtu );
    
    /* method sending out packet for external module */
    METHOD_(ULONG, pfIP_Output)( struct tagMBuf *pMBuf, struct tagMBuf *pstMOpt,
                 struct tagROUTE *pstRo, LONG lFlags, struct tagIPMOPTIONS *pstIpMo );
    
    /* method sending out packet for internal module */
    METHOD_(ULONG, pfIP_Output_ForInternal)( struct tagMBuf *pMBuf, struct tagMBuf *pstMOpt,
                 struct tagROUTE *pstRo, LONG lFlags, struct tagIPMOPTIONS *pstIpMo );

    METHOD_(MBUF_S*, pfIP_SrcRoute)();
    /* method for stripping ip optional fields in ip head */
    METHOD_(VOID, pfIP_StrIpOptions)(register struct tagMBuf *pMBuf, struct tagMBuf *pMOpt);

    /* method for registering intermediate process hook of packet. */
    /* more then one hook can be registered at the same time with the same type */
    METHOD_(ULONG, pfIP_PP4_Intermediate_Hook_Register)(ULONG ulType, ULONG ulPriority,
                   IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

    METHOD_(ULONG,pfIP_PP4_Intermediate_Hook_UnRegister)(ULONG ulType, IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

    /* method for registering a hook, which decides the board to process local packets */
    /* only one hook can be registered */
    METHOD_(ULONG, pfIP_PP4_DeliverUp_Position_Hook_Register)(IP_PP4_DELEVERUP_POSITION_HOOK_FUNC pfHookFunc);

    METHOD_(ULONG, pfIP_PP4_RegProtocolSwitch)(ULONG ulFlag, struct tagPROTOSW * pstRegPST);

    METHOD_(VOID, pfIP_FreeMOptions)(struct tagIPMOPTIONS *pstIpMo);
    /* method dealing with the UnKown IPv4 packet, called by Queue dispatcher */   /* 同步D21代码  x36530  2004-9-2  */
    
    METHOD_(VOID, pfIP_LinkDropPacket)(struct tagMBuf * pMBuf); 
    
    METHOD_(ULONG, pfIP_ICMP_SendHostUnreachIsOff)(struct tagIFNET *pstIf); 

    METHOD_(ULONG, pfIP_ICMP_SendRedirectsIsOff)(struct tagIFNET  *pstIf); 

    /*METHOD_(VOID , pfIP_PP4_GetInterfaceStatics)(ULONG ulIfIndex, IPIFSTAT_S  *pIpif_stData);*/
    METHOD_(ULONG, pfIP_PP4_GetInterfaceStatics)(ULONG ulIfIndex, IPIFSTAT_S  *pIpif_stData);
    METHOD_(ULONG , pfIP_PP4_ClearInterfaceStatics)(ULONG ulIfIndex);
    METHOD_(ULONG , pfIP_ClearRouteCache)();
    METHOD_(VOID , pfIP_PP4_Health_BatchCheckup)();
    METHOD_(ULONG , pfIP_PP4_LastWord_BatchCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);     
};

DECLARE_INTERFACE( IIF_IPV4_IP_PP4_ComIntCFG )
{
    IUNKNOWN_METHODS


    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_(ULONG, pfIP_PP4_Init_Com)(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_(ULONG, pfIP_PP4_Activate_Com)();
    METHOD_(ULONG, pfIP_PP4_SetModuleInfo)(struct tagPp4ModuleInfo*pstMInfo);


    METHOD_(ULONG, pfIP_PP4_GetStatics)(struct tagIPSTAT* pstIpStat);
    METHOD_(VOID, pfIP_PP4_ClearIpCounters)( ULONG  ulSlotNumber );
    METHOD_(ULONG, pfIP_PP4_GetDebugFlag)(ULONG *pulDebugFlag,
                          ULONG *pulDebugIpAcl,
                          ULONG *pulDebugIpIfAcl,
                          ULONG *pulDebugIpIfOpt,
                          ULONG *pulDebugIpErr,
                          ULONG *pulDebugPacketVerbose);
    METHOD_(ULONG, pfIP_PP4_SetDebugFlag)(ULONG ulIpDebugNo,
                          ULONG ulDebugAcl,
                          ULONG ulDebugIfAcl,
                          ULONG ulDebugIfOpt,
                          ULONG ulDebugIpErr,ULONG ulDebugIpVerbose);

    METHOD_(ULONG, pfIP_PP4_SetForwardFlag)(ULONG ulFlag);
    METHOD_(ULONG, pfIP_PP4_GetForwardFlag)();

    METHOD_(ULONG, pfIP_PP4_SetDefaultTTL)(ULONG ulTtl);
    METHOD_(ULONG, pfIP_PP4_GetDefaultTTL)();
    METHOD_(VOID, pfIP_PP4_ClearIpInterface)(struct tagIPIFNET * pstIpIf);  /* 同步D21代码  x36530  2004-9-16  */

    METHOD_(ULONG, pfIP_ICMP_RedirectsFunc)(IFNET_S * pIf, ULONG ulFlag);
    METHOD_(ULONG, pfIP_ICMP_HostUnreachFunc)(IFNET_S * pIf, ULONG ulFlag);
    METHOD_(USHORT, pfIP_Get_IpId)();
    METHOD_(VOID, pfIP_Set_IncreaseIpId)(VOID);

    /*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
    METHOD_(ULONG, pfIP_PP4_Ethvlan_IcmpRedirect_Hook_Register)(IP_PP4_ETHVLN_ICMPREDIRECT_HOOK_FUNC pfHookFunc);
    METHOD_(ULONG, pfIP_SetIpDebugFilter)(ULONG ulSetYes, ULONG ulIfIndex, CHAR *szSrcIp, CHAR *szDstIp,
            ULONG ulProtocol, ULONG ulSrcPort, ULONG ulDstPort);
    METHOD_(ULONG, pfIP_GetIpDebugFilter)(ULONG *pulDebugFlag, ULONG *pulDebugFilter);
};


DECLARE_INTERFACE( IIF_IPV4_IP_PP4_ComIntSSA )
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIP_PP4_RegisterICCallbacks)(struct tagPp4ICCallbackSet* pstICCallback);

};

#endif  /* _I_PP4_INC_H_  */


#ifdef  __cplusplus
}
#endif

