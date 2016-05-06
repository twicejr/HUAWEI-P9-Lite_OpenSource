/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              idhcp6r.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R 
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: DHCP6R 组件定义
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)     Create the first version.
*
*******************************************************************************/

#ifndef _IDHCP6R_H_
#define _IDHCP6R_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* Component ID declaration for DHCP6R */
#define CID_COMP_DHCP6R            ( CID_IPV4V6_BASE + 26)

/*interface IDs declaration*/
#define IID_COMP_DHCP6R_INTF_FUN    ( IID_IPV4V6_BASE + 261 )
#define IID_COMP_DHCP6R_INTF_CFG    ( IID_IPV4V6_BASE + 262 )
#define IID_COMP_DHCP6R_INTF_SSA    ( IID_IPV4V6_BASE + 263 )

typedef struct tagDHCP6RModInfo
{    
    ULONG   ulModID;        /* DHCP6R模块ID */
    ULONG   ulCfgMode;      /* DHCP6R使能和配置模式 */
    ULONG   ulTaskId;       /* DHCP6R任务ID */
    ULONG   ulSocketQId;    /* DHCP6R异步socket消息ID */
    ULONG   ulCntrlQId;     /* DHCP6R控制命令消息队列ID */
}DHCP6R_MOD_INFO_S;

DECLARE_INTERFACE (IIF_COMP_DHCP6R_ComIntFUN)
{
    IUNKNOWN_METHODS
    METHOD_(VOID,  pfDHCP6R_SetTaskId)(ULONG ulTask);
    METHOD_(ULONG, pfDHCP6R_Notify_CreateSocket)(VOID);
};

DECLARE_INTERFACE (IIF_COMP_DHCP6R_ComIntCFG)
{
    IUNKNOWN_METHODS      
    /* 组件相关 */
    METHOD_(ULONG, pfDHCP6R_Init_Com)(VOID);
    METHOD_(ULONG, pfDHCP6R_Active_Com)(VOID);
    METHOD_(ULONG, pfDHCP6R_RegShellApi)(DHCP6R_SHELL_CALLBACK_SET_S* pstShellApi);
  
    /* 配置相关 */
    METHOD_(ULONG, pfDHCP6R_Enable)(ULONG ulIfIndex);
    METHOD_(ULONG, pfDHCP6R_Disable)(ULONG ulIfIndex);
    METHOD_(ULONG, pfDHCP6R_AddServerList)(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);
    METHOD_(ULONG, pfDHCP6R_DelServerList)(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);
    METHOD_(ULONG, pfDHCP6R_DelAllServerList)(ULONG ulInIfIndex);
    METHOD_(ULONG, pfDHCP6R_GetServerList)(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstDhcp6rServerList);
    METHOD_(ULONG, pfDHCP6R_ShowServerList)(ULONG ulInIfIndex);
    METHOD_(ULONG, pfDHCP6R_SetDebugSwitch)(ULONG ulIfIndex, ULONG ulDebugLevel);
    METHOD_(ULONG, pfDHCP6R_GetDebugSwitch)(ULONG ulIfIndex, ULONG *pulDebugSwitch);
    METHOD_(ULONG, pfDHCP6R_SetDbgPktLen)(USHORT usPacketLen);
    METHOD_(ULONG, pfDHCP6R_ShowDebugSwitch)(ULONG ulIfIndex);
    METHOD_(ULONG, pfDHCP6R_ShowCfgInfo)(ULONG ulIfIndex);
    METHOD_(ULONG, pfDHCP6R_SetFwdMode)(ULONG ulMode);
    METHOD_(ULONG, pfDHCP6R_GetFwdMode)(ULONG *pulMode);
    METHOD_(VOID,  pfDHCP6R_ShowFwdMode)(VOID);
    METHOD_(ULONG, pfDHCP6R_SetMaxHops)(ULONG ulHops);
    METHOD_(ULONG, pfDHCP6R_GetMaxHops)(ULONG *pulHops);
    METHOD_(VOID,  pfDHCP6R_ShowMaxHops)(VOID);
    METHOD_(ULONG, pfDHCP6R_GetStatInfo)(DHCP6R_STATINFO_S *pstDhcp6rStat);
    METHOD_(VOID,  pfDHCP6R_ClrStatInfo)(VOID);
    METHOD_(VOID,  pfDHCP6R_ShowStatInfo)(VOID);

};

typedef struct tagDHCP6R_IntObj
{
    struct IIF_COMP_DHCP6R_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_DHCP6R_ComIntCFG    *pCompIntCFG;
}DHCP6R_INT_OBJ_S;

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif      /* end of _IDHCP6R_H_   */

