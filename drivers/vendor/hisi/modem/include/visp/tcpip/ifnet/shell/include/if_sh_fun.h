/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_SH_FUN.H  
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/08
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/08      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _IF_SH_FUN_H_
#define _IF_SH_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif

#define IF_IPC_QUE_LENGTH               9000    /* IPC消息队列长度 */


/********************IF_SH_INIT文件函数声明begin *********************/
ULONG IF_Sh_RegApp();
ULONG IF_Init(VOID);
ULONG IF_Sh_RegIFClass();
VOID IF_Sh_RegNotify();

extern struct IIF_IFNET_ComIntFUNVtbl* g_pstIfFunVtbl;
extern struct IIF_IFNET_ComIntCFGVtbl* g_pstIfCfgVtbl;

extern struct IIF_MP_ComIntFUNVtbl* g_pstIfMPFunVtbl;
extern struct IIF_PPPOE_CLIENT_ComIntFUNVtbl* g_pstIfPOECFunVtbl;

extern struct IIF_COMP_POES_ComIntFUNVtbl* g_pstIfPoesFunVtbl;  /* POES组件功能虚表 */
extern struct IIF_COMP_POES_ComIntCFGVtbl* g_pstIfPoesCfgVtbl;  /* POES组件配置虚表 */
extern struct IIF_COMP_PPP_ComIntFUNVtbl* g_pstIfPppFunVtbl;    /* PPP组件功能虚表 */
extern struct IIF_IPV4_DHCP4C_ComIntFunVtbl *g_pstIfnetDHCP4CFunVtable; /* DHCP4C组件功能虚表 */

/* L2IF FUN VTBL */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl  *g_pstIfnetL2ifFunVtbl;

extern struct IIF_COMP_TRUNK_ComIntFUNVtbl* g_pstIfTRUNKFunVtbl;   /* Trunk组件功能虚表 */
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl*  g_pstIfTrunkCfgVtbl ;

extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl  *g_pstIfEthFUNTable ;
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl  *g_pstIfEthCFGTable;

extern struct IIF_COMP_L2IF_ComIntFUNVtbl  *g_pstIfnetL2ifFunVtbl;/* L2IF 模块函数虚表 */

/* IFNET模块的1ag组件功能虚表指针 */
extern struct IIF_COMP_OAM1AG_ComIntFUNVtbl *g_pstIfnetOam1agFunTable ;

/********************IF_SH_INIT文件函数声明end *********************/


/********************IF_SH_FUN文件函数begin *********************/
ULONG IF_Sh_RegCallCenter();

CHAR* IF_Sh_GetMsg_Router_En(ULONG ulIndex);

ULONG IF_Sh_OutStringWait( ULONG ulExecID, CHAR * szOutString, ULONG * ulCurLine );

ULONG KRT_Link_Msg_Send (VLINKSTATUS_S *pstIFNETMsg);
ULONG KRT_Link_Msg6_Send (IFVLINKENTRY6_S *pstIFNETMsg);

ULONG IF_Sh_LinkIOCtl(ULONG ulIfIndex, ULONG ulCmd, CHAR * pData );

ULONG IF_Sh_LinkUpIOCtl(ULONG ulProtocol,ULONG ulIfIndex,ULONG ulCmd,CHAR * pData);

VOID IF_ShowInterface();
ULONG IF_ShowInterfacebyIfindex(ULONG ulIfIndex);

ULONG IF_NotifyMPDeleteIf(ULONG ulIfIndex); /*通知MP接口删除*/
ULONG IF_GetInterfacebyIfindex(ULONG ulIfIndex, ULONG ulBufLen, CHAR *szBuf, ULONG *pulLen);

ULONG IF_NotifyBfdDeleteIf(ULONG ulIfIndex);

/********************* IF_SH_FUN文件函数end *********************/


/*以下为Ifnet Shell要用到的外部函数*/
extern ULONG TCPIP_Link_Msg_Send(VLINKSTATUS_S *pstIFNETMsg); /*适配函数*/
extern ULONG TCPIP_GetATMLinkIntVTable(VOID** ppstLinkInt); /*获取ATM接口初始化接口的适配函数*/
extern ULONG TCPIP_Link_Msg6_Send(IFVLINKENTRY6_S *pstIFNETMsg6);

#ifdef __cplusplus
}
#endif

#endif /* _IF_SH_FUN_H_*/

