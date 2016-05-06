/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for ADDR
*    Version        : Initial Draft
*    File Name      : addr_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for ADDR
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _ADDR_API_H_
#define      _ADDR_API_H_

#ifdef      __cplusplus
extern "C"{
#endif

/* ------------------------------------------*
 * ND Adapter Configuration Switches         *
 * ------------------------------------------*/

#define ADDRADP_SHOWERRORINFO VRP_YES
#define ADDRADP_AUTOINIT      VRP_YES

/* ------------------------------------------*/


/* ------------------------------------------*
 * ND ADAPTER RETURN VALUES                  *
 * ------------------------------------------*/
#define ADDRADP_OK             VOS_OK
#define ADDRADP_ERR            VOS_ERR

#define ADDRADP_ERROR_STARTVALUE     0x500
#define ADDRADP_ERROR_MAXVALUE       0xFFFFFFFF

/* Error Offset */
typedef enum tagADDR_ADP_ERRORNUM_E
{
    ADDRADP_ERR_MEMBERFN_UNAVAILABLE = ADDRADP_ERROR_STARTVALUE,
    ADDRADP_ERR_INIT_NOTDONE,
    ADDRADP_ERR_IFNAME_INVALID,
    ADDRADP_ERR_INVALIDIP,
    ADDRADP_ERR_OPFAIL,
    ADDRADP_ERR_INVALIDINPUT,
    ADDRADP_ERR_NULLINPUT,
    ADDR_ADP_ERRORNUM_ULONG_PAD = ADDRADP_ERROR_MAXVALUE
}ADDR_ADP_ERRORNUM_E;

/* Address Categories Supported */
typedef enum tagADDR_ADP_ADDRTYPE_E
{
    ADDRADP_GLOBUNI,
    ADDRADP_LINKLOCAL,
    ADDRADP_EUI64,
    ADDRADP_ADDRTYPE_ULONG_PAD = ADDRADP_ERROR_MAXVALUE
}ADDR_ADP_ADDRTYPE_E;

/* ------------------------------------------*/


/* ------------------------------------------*
 * ADDR Adapter Functions                    *
 * ------------------------------------------*/

/* ------------------- *
 *  Common to Both     *
 * ------------------- *
 */

/* Initialize ADDR Component */
extern ULONG ADDR_InitAdapt();

/* Add IPv6 Address */
/*ulFlag : 0 -Global Address, 1-LinkLocal Address , 2-Eui-64 Address*/
extern ULONG ADDR_AddIP6Address(CHAR *szIfName, CHAR *pIp6Char,
                            ULONG ulIP6PrefixLen, ULONG ulFlag);

extern ULONG ADDR_AddIP6AddressExt(CHAR *szIfName, IN6ADDR_S *pstIn6Addr,
                                    ULONG ulIP6PrefixLen, ULONG ulFlag);

/* Delete IPv6 Address */
/*ulFlag : 0 -Global Address, 1-LinkLocal Address , 2-Eui-64 Address*/
/* Return IP6_OTH on success */
extern ULONG ADDR_DelIP6Address(CHAR *szIfName, CHAR *pIp6Char,
                            ULONG ulIP6PrefixLen, ULONG ulFlag);

extern ULONG ADDR_DelIP6AddressExt(CHAR *szIfName, IN6ADDR_S *pstIn6Addr,
                            ULONG ulIP6PrefixLen, ULONG ulFlag);
/* Debug Switch */
extern ULONG ADDR_DebugSwitch(ULONG ulSwitch, ULONG ulLevel);

/* Display IPv6 Information */
extern ULONG ADDR_DisplayIPv6Info(CHAR *szIfName);

/* Get Link MTU, that has been registered to it VIA ADDR_SetLinkMTU */
extern ULONG ADDR_GetLinkMTU(CHAR * szIfName, ULONG *pulLinkMTU);

/* Set Maximum MTU */
extern ULONG ADDR_SetMaxMTU(ULONG ulMaxMTU);

/* Get Maximum MTU */
extern ULONG ADDR_GetMaxMTU(ULONG *pulMaxMTU);

/* Register Platform Hook */
extern ULONG ADDR_RegisterPlatformHook(IP6_ADDR_DADRESULT_NOTIFY_FUNC_S *pstCallback);

/* To trigger DAD restart for the interface */
extern ULONG ADDR_RestartDAD(ULONG ulIfIndex);

/* Get IP Address assigned to the interface */
extern ULONG ADDR_Find_SameIPAddr(IN6ADDR_S stIn6Addr,
                                          IP6IFNET_S *pstIp6IfNet);

/*Open Session for Address Waitlist */
extern ULONG ADDR_OpenTable(ULONG ulMainType, UINTPTR *pulWaitListHandle, UCHAR ucWaitlistType);

/*Close Session for Address Waitlist */
extern ULONG ADDR_CloseTable(UINTPTR ulWaitlistHandle);

/*Get First Address Info for Display */
extern ULONG ADDR_Display_GetFirst (UINTPTR ulSessionId, IP6_ADDR_GET_INFO_S *pstRetAddr);

/*Get Next Address Info for Display */
extern ULONG ADDR_Display_GetNext (UINTPTR ulSessionId, IP6_ADDR_GET_INFO_S *pstRetAddr);

/*Open Session for Interface waitlist */
extern ULONG ADDR_Disp_Open(UINTPTR *pulSessionId, IP6_ADDR_DISP_FILTER_S *pstDispAddrFilter);

/*Close Session for Interface waitlist */
extern ULONG ADDR_Disp_Close (UINTPTR ulSessionId);

/* To SET/GET MTU configurations */
extern ULONG ADDR_Set_Mtu(ULONG ulIfIndex, ULONG ulMtu);
extern ULONG ADDR_Get_Mtu(ULONG ulIfIndex, ULONG ulIsCmd, ULONG *pulMtu);

/* End : ADDR Waitlist table operations */

/* Get Link Local Address on Interface */
extern ULONG ADDR_GetLinkLocalAddrOnIntf(ULONG ulIfIndex, IP6IFADDR_S *pstLinkLocalAddr);
extern ULONG ADDR_GetLinkLocalAddrByIf(ULONG ulIfIndex, IN6ADDR_S *pstLinkLocalAddr);

/* --------- *
 * Only Host *
 * --------- *
 */

/* Display Unicast Addresses on interface */
extern ULONG ADDR_DisplayUniAddrOnIntf_Host(CHAR *szIfName);

/* Display Multicast Addresses on interface */
extern ULONG ADDR_DisplayMultiAddrOnIntf_Host(CHAR *szIfName);

/* Enable IPv6 On interface */
extern ULONG ADDR_IPv6EnableOnIntf_Host(CHAR *szIFName,ULONG ulFlag);

/* Check if IPv6 is Enabled / Disabled on interface */
extern ULONG ADDR_GetIPv6StatusOnIntf_Host(CHAR *szIFName,BOOL_T *pbIpv6FuncStatus);

/* Delete all manual addresses on interface */
extern ULONG ADDR_DelAllManualAddrIntf_Host(CHAR *szIFName);

/* Delete all Stateless Addresses on Interface */
extern ULONG ADDR_DelAllStatelessAddrIntf_Host(CHAR *szIFName);

/* Enable/Disable IPv6 Address autoconfiguration on interface */
extern ULONG ADDR_EnableDisableIntfAutoconfig (ULONG ulIfIndex, ULONG ulOperation);

/* Get First Multicast Address */
extern ULONG ADDR_MultiAddr_GetFirst_HOST(UINTPTR ulSessionId, ULONG ulAddrScope,
                ULONG ulIfIndex, IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

/* Get Next Multicast Address */
extern ULONG ADDR_MultiAddr_GetNext_HOST(UINTPTR ulSessionId,
                IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

/* Get First Unicast Address */
extern ULONG ADDR_UniAddr_GetFirst_HOST(UINTPTR ulSessionId, ULONG ulAddrScope,
                ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

/* Get Next Unicast Address */
extern ULONG ADDR_UniAddr_GetNext_HOST(UINTPTR ulSessionId, ULONG ulAddrScope,
                ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

/* ----------- *
 * Only Router *
 * ----------- *
 */

/* Delete All IPv6 Addresses on Interface */
ULONG ADDR_DelAllIPv6AddrIntf_Router(CHAR *szIFName);

/* AutoConfigure LinkLocal Address on interface */
extern ULONG ADDR_AutoConfigureLLAIntf_Router(CHAR *szIFName);

/* Undo autoConfigure LinkLocal Address on interface */
extern ULONG ADDR_UndoAutoConfigureLLAIntf_Router(CHAR *szIFName);

extern ULONG ADDR_Get_DADState(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulDadState);
extern ULONG ADDR_Get_IfIndexByAddr(ULONG ulVrfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulIfIndex);

extern ULONG ADDR_GetFirstUniAddrOnIntf(ULONG ulIfIndex, 
                                            UINTPTR ulWaitListHandle, 
                                            IN6ADDR_S *pstUniAddrAddr);
extern ULONG ADDR_GetNextUniAddrOnIntf(ULONG ulIfIndex, 
                                            UINTPTR ulWaitListHandle, 
                                            IN6ADDR_S *pstUniAddrAddr);
extern ULONG ADDR_GetFirstMultiAddrOnIntf(ULONG ulIfIndex, 
                                            UINTPTR ulWaitListHandle, 
                                            IN6ADDR_S *pstMultiAddrAddr);
extern ULONG ADDR_GetNextMultiAddrOnIntf(ULONG ulIfIndex, 
                                            UINTPTR ulWaitListHandle, 
                                            IN6ADDR_S *pstMultiAddrAddr);

extern ULONG  ADDR_IsLocalIfAddr(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_OpenAddr6Table
* Date Created: 2014-03-11
*       Author: fengjing209023
*  Description: 注册WAITLIST
*        Input: pstFilter: 过滤条件
*       Output: pulWaitlist: WAITLIST 句柄
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 接口索引填0则查询所有地址，否则查询指定接口下的地址
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   fengjing209023  Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenAddr6Table(UINTPTR *pulWaitlist, IPADDR6_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetAddr6Table
* Date Created: 2014-03-11
*       Author: fengjing209023
*  Description: 获取IPV6地址信息
*        Input: ulWaitlist: WAITLIST 句柄
*       Output: pIfAddr6: IPV6 地址信息
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   fengjing209023  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetAddr6Table(UINTPTR ulWaitlist, IP6_ADDR_GET_INFO_S *pIfAddr6);
/*******************************************************************************
*    Func Name: TCPIP_CloseAddr6Table
* Date Created: 2014-03-11
*       Author: fengjing209023
*  Description: 关闭WAITLIST
*        Input: ulWaitlist: WAITLIST 句柄
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   fengjing209023  Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseAddr6Table(UINTPTR ulWaitlist);
/*******************************************************************************
*    Func Name: TCPIP_GetAddr6ByIfIndex
* Date Created: 2014-03-11
*       Author: fengjing209023
*  Description: 获取指定接口下的所有IPV6地址信息
*        Input: ulIfIndex: 接口索引
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   fengjing209023  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetAddr6ByIfIndex(ULONG ulIfIndex, IP6_ADDR_GET_INFO_S *pstIfAddr6);
/*******************************************************************************
*    Func Name: TCPIP_Addr6_Display
* Date Created: 2014-03-11
*       Author: fengjing209023
*  Description: 显示IPV6地址信息
*        Input: CHAR *pcIfName:接口名称，为空所有地址，非空指定接口下的地址
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   fengjing209023  Create
*
*******************************************************************************/
extern VOID TCPIP_Addr6_Display(CHAR *pcIfName);

/*******************************************************************************
*    Func Name: ADDR_AddIP6AddressByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description:添加接口IPv6地址
*  Input:    ULONG ulIfIndex:接口索引
*              CHAR *szIP6Addr :IPv6地址
*              ULONG ulIP6PrefixLen:地址前缀长度
*              ULONG ulFlag:操作类型
*  Output:  
*  Return: VOS_OK:成功
*             其他:失败
*  Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-01   wuling 00201943         Create for DTS2014101506272
*
*******************************************************************************/
extern ULONG ADDR_AddIP6AddressByIndex(ULONG ulIfIndex, CHAR *szIP6Addr,
                                    ULONG ulIP6PrefixLen, ULONG ulFlag);

/*******************************************************************************
*    Func Name: ADDR_DelIP6AddressByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description:删除接口IPv6地址
*  Input:    ULONG ulIfIndex:接口索引
*              CHAR *szIP6Addr :IPv6地址
*              ULONG ulIP6PrefixLen:地址前缀长度
*              ULONG ulFlag:操作类型
*  Output:  
*  Return: VOS_OK:成功
*             其他:失败
*  Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-01   wuling 00201943         Create for DTS2014101506272
*
*******************************************************************************/
extern ULONG ADDR_DelIP6AddressByIndex(ULONG ulIfIndex, CHAR *szIP6Addr,
                                     ULONG ulIP6PrefixLen, ULONG ulFlag);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ADDR_API_H_ */
