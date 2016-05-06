/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iam4_inc.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: AM4中接口定义，为外部使用时包含此文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*  2006-11-07   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif


#ifndef _I_AM4_INC_H_
#define _I_AM4_INC_H_


struct tagIFNET;
struct tagMBuf;
struct tagIPIFNET;
struct tagRM_IM_IPMSG;
struct tagIPIFADDR;
struct tagSOCKADDRIN;
struct tagSOCKADDR;
struct tagINADDR;
struct tagIPMULTI;
struct tagIP_L3VPN_VRF;
struct tagIP_AM4_MOD_INFO;
struct tagIpAm4IfAddr;
struct tagAM4_SHELL_HA_CALLBACK_FUNC_SET;
struct tagAm4ICCallbackSet;
struct tagIpAddrNotifyMsg;

/* rm callback functions set*/
typedef struct tagAM4_SHELL_RM_FUNC_PTR
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG(*pfSFIB_Item_IsAvailable)(); 
      ULONG(*pfSFIB_RM_SearchRoute)(ULONG ulIpAddress ,ULONG ulMaskLen,ULONG ulIfIndex );*/
    ULONG(*pfSFIB_Item_IsAvailable)(ULONG ulVrfIndex); 
    ULONG(*pfSFIB_RM_SearchRoute)(ULONG ulVrfIndex,ULONG ulIpAddress ,ULONG ulMaskLen,ULONG ulIfIndex );
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}AM4_SHELL_RM_FUNC_PTR;

/* prototype of shell callback function */
typedef ULONG(*AM4_SHELL_SYS_RECOVER_CALLBACK_PTR)();
typedef ULONG(*AM4_SHELL_REPLACE_CONFIG_CALLBACK_PTR)(ULONG ulIfIndex);

/* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
typedef ULONG(*IP_AM4_ETHVLN_VLANWARNING_HOOK_FUNC)(IFNET_S *pstSubtIf, ULONG ulLocalIP, ULONG ulNeighbourIP, ULONG ulMatchMode, UCHAR ucRecoverReason);

/* prototype of vtable of am4:fun */
DECLARE_INTERFACE( IIF_IPV4_IP_AM4_ComIntFUN ) 
{
    IUNKNOWN_METHODS

    /* link layer and ifnet UP IOCtl function. */
    METHOD_(ULONG, pfIP_Addr_LLC_Notify)(struct tagIFNET *pstIfNet, ULONG ulCmd, CHAR *pcData);

    /* Attach IP to an interface */
    METHOD_(ULONG, pfIP_IF_Attach)(struct tagIFNET *pstIfNet);
    /* Detach IP to an interface */
    METHOD_(ULONG, pfIP_IF_Detach)(struct tagIFNET *pstIfNet, ULONG ulCmd);

    /* judge if a packet is multicast */
    METHOD_(ULONG, pfIP_IsMultiCastPkt)(struct tagMBuf *pstMBuf);
    /* judge if a packet is netbroadcast */
    METHOD_(ULONG, pfIP_IsNetBroadcastPkt)(struct tagMBuf *pstMBuf);
    /* judge if a packet is subnetbroadcast */
    METHOD_(ULONG, pfIP_IsSubNetBroadcastPkt)(struct tagMBuf *pstMBuf);

    /* is the net mask valid?(continuous) */
    METHOD_(ULONG, pfIP_NetmaskIsContinue)( ULONG ulMask );

    /* judge is an address is broadcast address, including all 1, all 0, broadcast on if. */
    METHOD_(ULONG, pfIP_IsBroadcast)(struct tagIFNET *pstIfNet, ULONG ulIpAddr);
    /* judge is an address is broadcast address on if */
    METHOD_(ULONG, pfIP_IF_IsBroadcast)(ULONG ulIpAddr, struct tagIFNET *pstIfNet);

    /* is the address and mask invalid on the interface? */
    METHOD_(ULONG, pfIP_IsInvalidIPAddress)(struct tagIFNET *pstIfNet,
                               ULONG ulAddr, ULONG ulMask);

    /* does the address and mask conflict with other configured address? */
    METHOD_(ULONG, pfIP_ConflictIpAddress)(struct tagIPIFNET *pstIpIf,
                               ULONG ulAddr, ULONG ulMask, ULONG ulFlag);

    /* get the current configured addres number of the interface */
    METHOD_(ULONG, pfIP_GetAddrNumOnIf)(struct tagIPIFNET *pstIpIf );
    /* get the multicast group number joined on the interface */
    METHOD_(ULONG, pfIP_GetMultiAddrNumOnIf)(struct tagIPIFNET *pstIpIf );

    /* does the interface has address? */
    METHOD_(ULONG, pfIP_IF_HaveIpAddr)(struct tagIFNET * pstIfNet);

    /* get the main address and mask of the interface */
    /* the address maybe OWN or BORROW */
    METHOD_(ULONG, pfIP_Get_Main_IpAddr)(struct tagIPIFNET *pstIpIf,
                               ULONG *pulMainAddr, ULONG *pulMainMask);
    /* get the main address of the interface */
    /* the address maybe OWN or BORROW */
    /* (same functionality with previous, ifindex used as incoming parameter) */
    METHOD_(ULONG, pfIP_GetIfIpAddrByIndex)(ULONG ulIndex, ULONG *pulIpAddr);
    /* get the main address of the interface, only OWN address */
    METHOD_(ULONG, pfIP_Get_MainIpAddr)(struct tagIPIFNET*pstIpIf);
    /* get the main address of the interface, only OWN address */
    /* (same functionality with previous, use ifnet as parameter) */
    METHOD_(ULONG, pfIP_Get_IF_MainIpAddr)(struct tagIFNET *pstIf);
    /* get the first address in the address link of interface addresses */
    METHOD_(ULONG, pfIP_Get_First_IpAddr)(struct tagIPIFNET*pstIpIf,
                             ULONG *pulFirstAddr, ULONG *pulFirstMask);

    /* get the mask for the address on interface. when failed, return 0 */
    METHOD_(ULONG, pfIP_GetMask)(struct tagIFNET *pstIfNet, ULONG ulIpAddr);

    /* search the longest match address of the interface */
    METHOD_(ULONG, pfIP_IF_MaxIpAddr)(struct tagIFNET *pstIfNet, ULONG ulIpAddr);
    /* search the longest match address on interface */
    /* (same functionality with previous, parameter diff) */
    METHOD_(struct tagIPIFADDR*, pfIP_IF_IFA_IfWithBestNet)(struct tagSOCKADDRIN *pstSockInAddr,
                                      struct tagIPIFNET*pstIpIf);

    /* search the multicast address on interface */
    METHOD_(struct tagIPMULTI*, pfIP_FindMultiOnIpIf)(struct tagINADDR *pstAddr,
                                struct tagIPIFNET*pstIpIfNet);

    /* is the address one of the interface? */
    METHOD_(ULONG, pfIP_IF_IsThisIfIpAddr)(struct tagIFNET *pstIfNet, ULONG ulIpAddr);

    /* is this address a VRF's local address? (address of one of VRF's interface) */
    METHOD_(ULONG, pfIP_IsLocalIfAddr)(ULONG ulIpAddr, ULONG ulVrfIndex);

    /* get if index by ip;对于借用地址(IP_BORROW)的接口跳过 */
    METHOD_(ULONG, pfIP_DHCP4R_FindIfByIp)(ULONG ulGiaddr, ULONG ulVrfIndex);
        
    /* Added by l57500 for 同步VISPV1R5问题单A82D13365,2007-05-09 */
    /* 查询指定的地址是否和接口上的地址处于相同网段 */
    METHOD_(ULONG, pfIP_IF_IsSameNet)(IFNET_S *pstIfNet, ULONG ulIpAddr);
    /* End of addition */

    /* search all VRF's address, find the interface which has the specified address. */
    /* (almost same with the previous one. a little more is: returns the ifindex) */
    METHOD_(ULONG, pfIP_GetIfindexbyIpAddr)(ULONG ulIpAddr,ULONG *pulIfIndex, ULONG ulVrfIndex);
    /* find the address whose neighbor is the given one, in the VRF */
    METHOD_(struct tagIPIFADDR*, pfIP_IFA_IfWithDstAddr)(struct tagSOCKADDRIN *pstSockInAddr,
                                ULONG ulVrfIndex);
    /* find the local address, which is in the same net with given one, in the VRF */
    METHOD_(struct tagIPIFADDR*, pfIP_IFA_IfWithNet)(struct tagSOCKADDRIN *pstSockInAddr,
                                ULONG ulVrfIndex);
    /* find if the address is a local address or a broadcast address of the VRF */
    METHOD_(struct tagIPIFADDR*, pfIP_IFA_IfWithAddr)(struct tagSOCKADDR *pstSockAddr, ULONG ulVrfIndex);

    /* get any valid address from all of the VRF's */
    METHOD_(struct tagIPIFADDR*, pfIP_Get_ValidIpAddr)(ULONG ulVrfIndex);
    /* get any valid address from all of the VRF's. */
    /* (same functionality with previous, only parameter diff) */
    METHOD_(BOOL_T, pfIP_GetValidAddress)(ULONG *pulValidIpAddr, ULONG ulVrfIndex);


    /* ARP to query if the address is valid input */
    METHOD_(ULONG, pfIP_Eth_IsValidIpAddr)(struct tagIFNET *pstIfNet, ULONG ulSrcIpAddr,
                               ULONG ulDstIpAddr, USHORT usOpType);

    /* get the interface state. */
    /* not a good idea use this interface. */
    /* maybe can use pstIfnet->if_pfLinkDownIOCtl with SIOCLINKSTATE cmd instead. */
    METHOD_(ULONG, pfIP_GetIfUpDownStateFromIndex)(ULONG ulIfIndex, ULONG *pUpDown);

    /* find VRF with specified name */
    METHOD_(struct tagIP_L3VPN_VRF*, pfIP_L3VPN_LocateVRFByName)(CHAR *szVrfName);
    /* find VRF with specified VRFindex */
    METHOD_(struct tagIP_L3VPN_VRF*, pfIP_L3VPN_LocateVRFByIndex)(ULONG ulVRFIndex);
    /* is the VRF index valid? */
    METHOD_(BOOL_T, pfIP_L3VPN_IsValidVRFIndex)(ULONG ulVRFIndex);

    METHOD_(struct tagIPMULTI*, pfIPIF_AddMulti)(struct tagINADDR *pstIn, struct tagIPIFNET *pstIpIf);
    METHOD_(LONG, pfIPIF_DelMulti)(struct tagINADDR *pstInAddr, struct tagIPIFNET *pstIpIf);
    METHOD_(ULONG, pfIP_AM4_DHCP4C_SetAddress)(ULONG ulNo, ULONG ulIfIndex, ULONG ulIPAddr, ULONG ulMask);
    METHOD_(ULONG, pfIP_ArpProxy_IsValidIpAddr)( IFNET_S *pstIfNet, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, ULONG ulVrfIndex); 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfIP_Addr_OpenTable)(UINTPTR *pulAddrCacheHandle,IPIFNET_S *pstIpIf,ULONG ulVrfIndex); 
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfIP_Addr_CloseTable)(UINTPTR ulAddrCacheHandle); 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfIP_AddrGet)(UINTPTR ulAddrCacheHandle,IPIFADDR_S  *pIfa,IPIFNET_S *pstIpIf,ULONG ulVrfIndex); 
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_(ULONG, pfIP_HA_BatchBackup)();
    METHOD_(ULONG, pfIP_HA_Input)(UCHAR *pBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfIP_HA_Smooth)();
    METHOD_(ULONG, pfIP_ConflictIpAddressSpecial_PT)(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);
    METHOD_(struct tagIPIFADDR*, pfIP_GetBestIpAddrByVrf)(SOCKADDRIN_S *pstSockInAddr, ULONG ulVrfIndex);

    /* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
    METHOD_(ULONG, pfIP_AM4_Ethvlan_VlanWarningHook_Register)(IP_AM4_ETHVLN_VLANWARNING_HOOK_FUNC pfHookFunc);

    /* Added by likaikun213099, 地址冲突告警处理, 2014/10/24 */
    METHOD_(ULONG, pfIP_SetIpConflictFlag)(IFNET_S* pIf, ULONG ulIpAddr);
    METHOD_(ULONG, pfIP_ClearIpConflictFlag)(IFNET_S* pIf, ULONG ulIpAddr);
    METHOD_(BOOL_T, pfIP_AM4_SupportSameSubAddr)();
};

/* prototype of vtable of am4:config */
DECLARE_INTERFACE( IIF_IPV4_IP_AM4_ComIntCFG )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_(ULONG, pfIP_AM4_Init_Com)();
    METHOD_(ULONG, pfIP_AM4_Activate_Com)();
    METHOD_(ULONG, pfIP_AM4_SetModuleInfo)(struct tagIP_AM4_MOD_INFO *pstMInfo);

    /* register shell srm notify function to core */
    METHOD_(ULONG, pfIP_AM4_RegisterShSrmCallback)(AM4_SHELL_RM_CALLBACK_FUNC_PTR pfShCallback);
    /* registers shell sys recover judge function to core */
    METHOD_(ULONG, pfIP_AM4_RegShIsSysRecoverCallback)(AM4_SHELL_SYS_RECOVER_CALLBACK_PTR pfCallback);
    METHOD_(ULONG, pfIP_AM4_RegShReplaceConfigCallback)(AM4_SHELL_REPLACE_CONFIG_CALLBACK_PTR pfCallback);

    /* set/delete interface address */
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddr)(ULONG ulNo,
                                   struct tagIFNET *pstIf,
                                   ULONG ulIpAddr,
                                   ULONG ulSubnetMask,
                                   ULONG ulSecondary);

    /* add by z62531 ,屏蔽主从概念的地址配置接口*/
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddrUniform)(ULONG ulOperate,ULONG ulIfIndex,
                                   ULONG ulIpAddr,ULONG ulSubnetMask);
    
    /* set/remove interface ip unnumber */
    METHOD_(VOID, pfDealWithOthersBorrowMyIPaddr)(IPIFNET_S *pstCurIf, ULONG ulCmd);    
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddrUnnumber)(ULONG ulNo, struct tagIFNET *pstIf,
                                   struct tagIFNET *pstIfOfLendIn);
    /* set/remove interface ip PPP negotiate */
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddrNego)(ULONG ulNo, struct tagIFNET* pstIf);
    /* set/remove interface ip DHCP */
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddrDhcp)(ULONG ulNo, struct tagIFNET* pstIf);
    /* register shell srm to Judge the free rib item */
    METHOD_(ULONG,pfIP_AM4_RegShSrmJudgeFun)(AM4_SHELL_RM_FUNC_PTR *pstShRmCallback);
    METHOD_( ULONG , pfIP_HA_GetIpDbg )  (ULONG *pulDbg);
    METHOD_( ULONG , pfTCPIP_HA_SetIpDbg ) (ULONG ulDbg);
    METHOD_( ULONG , pfIP_HA_SetIpVerboseDbg)(ULONG ulDbg);
    METHOD_( ULONG , pfIP_HA_GetIpVerboseDbg)(ULONG *pulDbg);
    METHOD_(VOID, pfIP_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddrDhcpRmt)(ULONG ulNo, struct tagIFNET* pstIf, ULONG ulOutIfIndex);
    METHOD_(ULONG, pfIP_AM4_CfgProcIpAddrUniformEx)(ULONG ulOperate, ULONG ulIfIndex,
                                   ULONG ulIpAddr, ULONG ulSubnetMask);
};    

/* prototype of vtable of am4:shell */
DECLARE_INTERFACE( IIF_IPV4_IP_AM4_ComIntSSA )
{
    IUNKNOWN_METHODS
    /* register shell IC output functions to core */
    METHOD_(ULONG, pfIP_AM4_RegisterICCallbacks)(struct tagAm4ICCallbackSet *pstICCallback);
};

#endif  /* _I_AM4_INC_H_  */

#ifdef  __cplusplus
}
#endif

