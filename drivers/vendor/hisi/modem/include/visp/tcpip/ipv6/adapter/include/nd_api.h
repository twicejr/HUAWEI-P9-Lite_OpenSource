/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for ND
*    Version        : Initial Draft
*    File Name      : nd_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for ND
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _ND_API_H_
#define      _ND_API_H_

#ifdef      __cplusplus
extern "C"{
#endif


/* ------------------------------------------*
 * ND Adapter Configuration Switches         *
 * ------------------------------------------*/

/* Enable / Disable ADAPTER Error / Info Ouput on Console */
#define NDADP_SHOWERRORINFO          VRP_YES

/* Enable / Disable Auto-Init for Adapter */
/* If VRP_YES, a call to adapter API, will auto-init the Adapter,
   if it has not been initialized previously */
#define NDADP_AUTOINIT               VRP_YES

/* ------------------------------------------*/


/* ------------------------------------------*
 * ND ADAPTER RETURN VALUES                  *
 * ------------------------------------------*/

#define NDADP_OK                       VOS_OK
#define NDADP_ERR                      VOS_ERR

#define ND_ADP_ERROR_STARTVALUE        0x400
#define ND_ADP_ERROR_MAXVALUE          0xFFFFFFFF

/* Error Codes */
typedef enum tagND_ADP_ERRORNUM_E
{
    NDADP_ERR_MEMBERFN_UNAVAILABLE = ND_ADP_ERROR_STARTVALUE,
    NDADP_ERR_INIT_NOTDONE,
    NDADP_ERR_IFNAME_INVALID,
    NDADP_ERR_INVALIDIP,
    NDADP_ERR_INVALIDMAC,
    NDADP_ERR_OPFAIL,
    NDADP_ERR_INVALIDINPUT,
    NDADP_ERR_VTBLFETCHFAIL,
    NDADP_ERR_INVALIDNEXTHOP,
    NDADP_ERR_INVALIDDESTIP,
    NDADP_ERR_INVALIDPREFIX,
    NDADP_ERR_NDINFOISNULL,
    ND_ADP_ERRORNUM_ULONG_PAD       = ND_ADP_ERROR_MAXVALUE
}ND_ADP_ERRORNUM_E;


/* Types of Neighbor Entry */
typedef enum tagND_ADP_NBENTRYTYPE_E
{
    NDADP_NBTYPE_ALL,
    NDADP_NBTYPE_STATIC,
    NDADP_NBTYPEDYNAMIC,
    NDADP_NBTYPE_ULONG_PAD = ND_ADP_ERROR_MAXVALUE
}ND_ADP_NBTYPE_E;

/* ------------------------------------------*/


/* ------------------------------------------*
 * ND Adapter Functions                      *
 * ------------------------------------------*
 */

/*------------------------------------------*
                 * Common for host & router *
                 *--------------------------*/

/* Initialize adapter */
extern ULONG ND_InitAdapt();

/* Get HopLimit */
extern ULONG ND_GetHopLimit(UCHAR *pucHopLimit);

/* Add Static Neighbor Entry */
extern ULONG ND_AddStaticNBEntry(CHAR *szIfName, CHAR *pcIp6Addr, UCHAR *pucMac);

/* Add Static Neighbor Entry With VLAN ID support */
extern ULONG ND_AddStaticNBEntry_Vlan(CHAR *szIfName, CHAR *pcIp6Addr, UCHAR *pucMac,
                                        USHORT usVlanId, ULONG ulPortIndex);

/* Delete static Neighbor entry */
extern ULONG ND_DelStaticNBEntry(CHAR *szIfName, CHAR *pcIp6Addr);

/* Reset all Neighbor entries */
extern ULONG ND_ResetAllNBEntries(ULONG ulFlag);

/* Display NB Cache on interface */
extern ULONG ND_DisplayNBCacheOnIntf(CHAR * szIfName);

/* Rset NB Statistics on interface */
extern ULONG ND_ResetNBStatisticsIntf(CHAR * szIfName);

/* Get DAD Attempts on interface */
extern ULONG ND_GetDADAttempts(CHAR *szIfName, ULONG *pulRetVal);

/* Get Debug Status */
extern ULONG ND_GetDebug(ULONG *pulRetVal);

/* Set Debug */
extern ULONG ND_SetDebug(IP6_ND_CFG_OPT_E enFlag);

/* Get the entry limit after which timer should stop
   for deleting LRU entries */
extern ULONG ND_GetNDTimerTriggerLimit(ULONG *pulRetVal);

/* Set the entry limit after which timer should stop
   for deleting LRU entries */
extern ULONG ND_SetNDTimerTriggerLimit(ULONG ulEntryToDelete);

/* Get Number of Static Entries */
extern ULONG ND_GetStaticEntryCount(CHAR *szIfName,
                                            ULONG *pulStaticEntryCount);

/* Set DAD attempts for ND */
extern ULONG ND_SetDADAttempts(CHAR *szIfName, ULONG ulValue,
                                        IP6_ND_SETFLAG_E enFlag);

/* Start Address Resolution */
extern ULONG ND_Start_AddressResolution(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr,
                                                    IN6ADDR_S *pstSrcIP6Addr);

/* Start NUD */
extern ULONG ND_Start_NUD(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr);

extern ULONG ND_ResetNBEntriesIntfbyVLAN(ULONG ulIfIndex, ULONG ulVlanId,
                                                                                    UCHAR ucType);

/* ND NB open table */
extern ULONG ND_OpenTable (UINTPTR *pulWaitListHandle);

/* ND NB Close table */
extern ULONG ND_CloseTable (UINTPTR ulNBWaitListHandle);

/* NB Get First Entry */
extern ULONG ND_GetFirstExt(ULONG ulIfIndex, ND_NBENTRY_INFO_S *pstNBEntryOut, UINTPTR ulNBWaitListHandle);

extern ULONG ND_GetFirstExtWithErrCode(ULONG ulIfIndex,                                            
                                           UINTPTR ulNBWaitListHandle,
                                           ND_NBENTRY_INFO_S *pstNBEntryOut,
                                           ULONG *pulErrCode);

/* NB Get Next Entry */
extern ULONG ND_GetNextExt(UINTPTR ulNBWaitListHandle,
                                                    ND_NBENTRY_INFO_S *pstNextNBInfo);

extern ULONG ND_GetNextExtWithErrCode(UINTPTR ulNBWaitListHandle, 
                                           ND_NBENTRY_INFO_S *pstNextNBInfo,
                                           ULONG *pulErrCode);

/* Register ND Flow Callback */
extern ULONG ND_RegisterFlowCallback(IP6_ND_FLOW_CALLBACK_SET_S *pstFlowCallback);

/*------------------------------------------*
                 * Specific to host         *
                 *--------------------------*/

/* Display APIs */
/* Display Destination Cache */
extern ULONG ND_DisplayDestCache_Host();

/* Display Prefix List on Interface */
extern ULONG ND_DisplayPrefixListIntf_Host(CHAR *szIfName);

/* Display Default Router List on Interface */
extern ULONG ND_DisplayDefRouterListIntf_Host(CHAR * szIfName);

/* Delete all prefix list entries per interface */
extern ULONG ND_DelAllPrefixListEntriesIntf_Host(CHAR *szIfName);

/* Delete all destination cache entries */
extern ULONG ND_DelAllDestCacheEntries_Host();

/* Delete all default router list entries on an interface */
extern ULONG ND_DelRouterListEntriesIntf_Host(CHAR *szIfName);

/* Get ND Host-Specific Parameters */
extern ULONG ND_GetNDParams_Host(CHAR * szIfName,
                                IP6_ND_GETHOSTPARAMS_S *pstHostParams);

/* Default router Open table */
extern ULONG ND_DefRouterOpenTable_HOST(ULONG ulIfIndex, UINTPTR *pulHandle);

/* Get First Default Router entry */
extern ULONG ND_DefRouterGetFirst_HOST(UINTPTR ulWaitListHandle,
                                IP6_ND_DEFROUTER_INFO_S  *pstDefRouterEntryOut);

/* Get Next Default Router entry */
extern ULONG ND_DefRouterGetNext_HOST(UINTPTR ulWaitListHandle,
                                IP6_ND_DEFROUTER_INFO_S  *pstDefRouterEntryOut);

/* Close Default router Waitlist */
extern ULONG ND_DefRouterCloseTable_HOST(UINTPTR ulWaitListHandle);

/* Interface Prefix List Open Table */
extern ULONG ND_PrefixListOpenTable_HOST(ULONG ulIfIndex, UINTPTR *pulHandle);

/* Get First Prefix list entry */
extern ULONG ND_PrefixListGetFirst_HOST(UINTPTR ulWaitListHandle,
                                IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);

/* Get First Prefix list entry */
extern ULONG ND_PrefixListGetNext_HOST(UINTPTR ulWaitListHandle,
                                        IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);

/* Close Interface Prefix list Waitlist */
extern ULONG ND_PrefixListCloseTable_HOST(UINTPTR ulWaitListHandle);


/* Destination Cache Open Table*/
extern ULONG ND_DestinationCacheOpenTable_HOST(UINTPTR *pulHandle);

/* Get Destination cache First entry */
extern ULONG ND_DestCacheGetFirst_HOST(UINTPTR ulWtLstHandle,
                                                    IP6_ND_DESTCACHE_INFO_S  *pstDestEntryOut);

/* Get Destination cache Next entry */
extern ULONG ND_DestCacheGetNext_HOST(UINTPTR ulWtLstHandle,
                                        IP6_ND_DESTCACHE_INFO_S *pstDestEntryOut);

/* Destination Cache close Table*/
extern ULONG ND_DestinationCacheCloseTable_HOST(UINTPTR ulWaitListHandle);

/*------------------------------------------*
                 * Specific to router       *
                 *--------------------------*/

/* Set Manage Router Flag */
extern ULONG ND_SetManageFlag_Router(CHAR *szIfName, IP6_ND_SETFLAG_E enFlag);

/* Get Manage Router Flag */
extern ULONG ND_GetManageFlag_Router(CHAR *szIfName, UCHAR *pucRetVal);

/* Set Manage Router Flag */
extern ULONG ND_SetOtherFlag_Router(CHAR * szIfName, IP6_ND_SETFLAG_E enFlag);

/* Set Others Router Flag */
extern ULONG ND_GetOtherFlag_Router(CHAR *szIfName, UCHAR *pucRetVal);

/* Get Reachable Time */
extern ULONG ND_GetReachableTime_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Get RA Interval */
extern ULONG ND_GetRAInterval_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Get Minimium interval for RA sending */
extern ULONG ND_GetRAMinInterval_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Set Default Routerliftime to be advertized in RA */
extern ULONG ND_GetDefaultRouterLifeTime_Router(CHAR *szIfName,
                                                        ULONG *pulRetVal);

/* Set HoptLimit */
extern ULONG ND_SetHopLimit_Router(UCHAR ucValue, IP6_ND_SETFLAG_E enFlag);

/* Set or Unset Suppressing or RA sent */
extern ULONG ND_SetSuppressRAFlag_Router(CHAR *szIfName,
                                                    IP6_ND_SETFLAG_E enFlag);

/* Set NS INterval */
extern ULONG ND_GetNSInterval_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Set VLink Router */
extern ULONG ND_SetVLink_Router(ULONG ulFlag);

/* Set Global Value Router */
extern ULONG ND_SetGlobalValue_Router(ULONG ulValue);

/* Reboot Router */
extern ULONG ND_Reboot_Router();

/* Set RA Interval */
extern ULONG ND_SetRAInterval_Router(CHAR *szIfName, ULONG ulValue,
                                                    IP6_ND_SETFLAG_E enFlag);

/* Set Default Lifetime */
extern ULONG ND_SetDefaultLifeTime_Router(CHAR *szIfName, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/* Set NS Interval */
extern ULONG ND_SetNSInterval_Router(CHAR *szIfName, ULONG ulValue,
                                               IP6_ND_SETFLAG_E enFlag);

/* Add / Delete prefixes */
extern ULONG ND_ProcPrefixInfo_Router(CHAR *szIfName,
                                        ULONG ulNo,
                                        ULONG ulValidTime,
                                        UCHAR ucAutoConfFlag,
                                        ULONG ulPreferredTime,
                                        ULONG ulPrefixLength,
                                        CHAR *szIp6Addr,
                                        UCHAR ucOnLinkFlag);

/* Set Reachable Time */
extern ULONG ND_SetReachableTime_Router(CHAR *szIfName, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/* Get ND Information from Core */
extern ULONG ND_GetInfoFromCore_Router(CHAR *szIfName,
                                            ND_GETFROMCORE_S *pstNDInfo);

/* Register DHCP6 Adapter Callbacks */
extern ULONG ND_DHCP6C_Adapt_RegCallbackFunc(IP6_ND_DHCP6CADAPT_CALLBACK_S
                                                    *pstDHCP6AdaptCallBackFunc);

extern ULONG ND_Get_OG_Intf_HOST(IN6ADDR_S *pstDestAddress, ULONG *pulIfIndex, 
                                                                IN6ADDR_S *pstNexthopAddr);

extern ULONG ND_SendAdvertiseNA(CHAR *szIfName, IN6ADDR_S *pstDstAddr, UCHAR *pucMac);

extern ULONG ND_DelNBDynamicEntriesByAddr(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr);

extern ULONG ND_NS_Output_Ext(ULONG ulIfIndex,
                                        ULONG  ucOptionFlag,
                                        IN6ADDR_S *pstDstAddr,
                                        IN6ADDR_S *pstSrcAddr,
                                        IN6ADDR_S *pstTgtAddr);

extern ULONG ND_RegFuncSpecialProxyHook(gpfIP6NDSpecialNDProxy pfHookFuc);
extern ULONG ND_RegFuncGetDADProxyIfIndexHook(gpfIP6GetDADProxyIfIndex pfHookFuc);
extern ULONG ND_SetNDSpecialProxyFlag(ULONG ulIfIndex, UCHAR ucFalg);
ULONG ND_FetchNBEntry(ULONG ulIfnetIndex, IN6ADDR_S *pstIPv6Addr,
                                                ND_NBENTRY_INFO_S *pstNBInfo);
ULONG ND_GetNBEntryNum(ULONG *pulTotalNum, ULONG *pulTotalStaticNum);

/*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
/*******************************************************************************
*    Func Name: ND_SetNAAttempts
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: 设定NA报文的最大发送次数[0,ND_SET_MAXNAATTEMPT](0,600)，
*               默认为MAX_NEIGHBOR_ADVERTISEMENT(3)
*        Input: CHAR *szIfName:接口名
*               ULONG ulValue:NA报文发送次数
*               IP6_ND_SETFLAG_E enFlag:Set/Unset标识
*       Output: 
*       Return: 
*      Caution: 1) 如果设定NA发送次数为0,则不发送。
*               2) 如果正在发送NA报文，设定的值不会立刻生效，待下次生效。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_SetNAAttempts(CHAR *szIfName, ULONG ulValue,
                                   IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_GetNAAttempts
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: 获取设定的NA报文的最大发送次数
*        Input: CHAR *szIfName:接口名
*       Output: ULONG *pulRetVal:返回的NA发送次数
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_GetNAAttempts(CHAR *szIfName, ULONG *pulRetVal);

/*******************************************************************************
*    Func Name: ND_SetNAInterval
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: 设定NA报文发送间隔[ND_NA_INTERVAL_MIN, ND_NA_INTERVAL_MAX]([1s,3600s]),
*               默认为RETRANS_TIMER(1s)
*        Input: CHAR *szIfName:接口名
*               ULONG ulValue:NA报文发送间隔
*               IP6_ND_SETFLAG_E enFlag:Set/Unset标识
*       Output: 
*       Return: 
*      Caution: 1) 如果正在发送NA报文，设定的值不会立刻生效，待下次生效。    
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_SetNAInterval(CHAR *szIfName, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_GetNAInterval
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: 获取设定的NA发送间隔
*        Input: CHAR *szIfName:接口名
*       Output: ULONG *pulRetVal:NA发送间隔
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_GetNAInterval(CHAR *szIfName, ULONG *pulRetVal);
/* End of Added by guojianjun178934, 2014/2/7   问题单号:S-IP-005-PUBLIC-FUNC-003 */

/*******************************************************************************
*    Func Name: TCPIP_OpenNDTable
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: Registers the wait list handle
*        Input: TCPIP_ND_FILTER_S* pstNDFilterInfo:
*       Output: UINTPTR *pulNDInfoHandle:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_OpenNDTable (UINTPTR *pulNDInfoHandle, TCPIP_ND_FILTER_S* pstNDFilterInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetNextNDInfo
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: 获取接口上的下一个ND表项，产品需要感知内部的错误码
*        Input: UINTPTR ulNDInfoHandle:
*       Output: TCPIP_ND_NBENTRY_INFO_S *pstNdInfo:
*               ULONG *pulErrCode:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_GetNextNDInfo( UINTPTR ulNDInfoHandle, TCPIP_ND_NBENTRY_INFO_S* pstNdInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseNDTable
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: Un registers the wait list handle
*        Input: UINTPTR ulNDInfoHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_CloseNDTable( UINTPTR ulNDInfoHandle);

/*******************************************************************************
*    Func Name: TCPIP_ShowNDInfo
* Date Created: 2014-03-11
*       Author: likaikun213099
*  Description: Display Nb entry
*        Input: CHAR* pIfName
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_ShowNDInfo(CHAR* pIfName);

/*******************************************************************************
*    Func Name: TCPIP_OpenIfNDHandle
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: 注册WAITLIST
*        Input: szFilter: 过滤条件
*       Output: pulIfNDInfoHandle: WAITLIST 句柄
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 接口索引填0则查询所有接口下的ND信息，否则查询指定接口下的ND信息
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_OpenIfNDHandle(UINTPTR *pulIfNDInfoHandle, TCPIP_IF_ND_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetNextIfNDInfo
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: 获取ND信息
*        Input: ulNDInfoHandle: WAITLIST句柄
*       Output: psIfNdInfo: 返回的ND信息，包含DAD尝试次数等信息
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 接口索引填0则查询所有接口下的ND信息，否则查询指定接口下的ND信息
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_GetNextIfNDInfo(UINTPTR ulNDInfoHandle , TCPIP_IF_NDINFO_S *psIfNdInfo);
/*******************************************************************************
*    Func Name: TCPIP_CloseIfNDHandle
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: 关闭WAITLIST句柄
*        Input: ulNDInfoHandle: waitlistHandle
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_CloseIfNDHandle(UINTPTR ulNDInfoHandle);
/*******************************************************************************
*    Func Name: TCPIP_GetIfNDInfo
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: 获取指定接口下面的DAD尝试次数等信息
*        Input: ulIfIndex: 接口索引
*       Output: psIfNdInfo: 返回的ND信息，包含DAD尝试次数等信息
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_GetIfNDInfo(ULONG ulIfIndex, TCPIP_IF_NDINFO_S *pstIfNDInfo);
/*******************************************************************************
*    Func Name: TCPIP_IfND_Display
* Date Created: 2014-04-08
*       Author: fengjing209023
*  Description: 显示IPV6地址信息
*        Input: CHAR *pcIfName:接口名称，为空所有地址，非空指定接口下的DAD尝试
*                              次数等信息
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-08   fengjing209023  Create
*
*******************************************************************************/
VOID TCPIP_IfND_Display(CHAR *pcIfName);

/*******************************************************************************
*    Func Name: TCPIP_NDMiss
* Date Created: 2014-04-22
*       Author: wuling 00201943
*  Description: ND MISS的时候根据目的地址触发地址解析
*源地址选择规则：
*1、如果目的地址是linklocal地址，源地址=当前接口的linklocal地址，没有linklocal地址填全0地址
*2、如果目的地址是golbal地址，源地址=1）当前接口最长匹配的gloabal地址
*                                  2）如果没有选到前缀匹配的地址，则随机选一个gloabal地址
*                                  3）如果当前接口没有gloabal地址，则选择接口的linklocal地址，没有linklocal地址，填全0地址
*
*  Input: ULONG ulIfIndex:接口索引
*         IN6ADDR_S *pstIP6Addr:ND MISS的目的地址
*  Return: 
*  Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-22   wuling 00201943         Create
*
*******************************************************************************/
ULONG TCPIP_NDMiss(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr);

/*******************************************************************************
*    Func Name: ND_SendAdvertiseNAByIf
* Date Created: 2014-05-27
*       Author: wuling 00201943
*  Description: 发送免费NA报文
*        Input: ULONG ulIfIndex:接口索引
*               IN6ADDR_S *pstDstAddr:目的地址
*               UCHAR *pucMac:physical地址
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-27   wuling 00201943         Create
*
*******************************************************************************/
ULONG ND_SendAdvertiseNAByIf(ULONG ulIfIndex, IN6ADDR_S *pstDstAddr, UCHAR *pucMac);

/*******************************************************************************
*    Func Name: ND_GetReachableTimeByIndex
* Date Created: 2014-07-23
*       Author: wuling 00201943
*  Description: 获取接口的ND reachable老化时间
*  Input:    ULONG ulIfIndex:接口索引
*  Output:  ULONG *pulRetVal:接口的ND reachable老化时间
*  Return: VOS_OK:查询成功
*             其他:查询失败
*  Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   wuling 00201943         Create
*
*******************************************************************************/
ULONG ND_GetReachableTimeByIndex(ULONG ulIfIndex, ULONG *pulRetVal);

/*******************************************************************************
*    Func Name: ND_GetDADAttemptsByIndex
* Date Created: 2014-07-23
*       Author: wuling 00201943
*  Description: 获取接口的DAD探测次数
*  Input:    ULONG ulIfIndex:接口索引
*  Output:  ULONG *pulRetVal:接口的DAD探测次数
*  Return: VOS_OK:查询成功
*             其他:查询失败
*  Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   wuling 00201943         Create
*
*******************************************************************************/
ULONG ND_GetDADAttemptsByIndex(ULONG ulIfIndex, ULONG *pulRetVal);

/*******************************************************************************
*    Func Name: ND_SetDADAttemptsByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description: 设置接口的DAD探测次数
*  Input:    ULONG ulIfIndex:接口索引
*              ULONG ulValue   :DAD探测次数
*              IP6_ND_SETFLAG_E enFlag:操作类型
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
ULONG ND_SetDADAttemptsByIndex(ULONG ulIfIndex, ULONG ulValue,
                                            IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_SetReachableTime_RouterByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description: 设置接口的ND reachable时间
*  Input:    ULONG ulIfIndex:接口索引
*              ULONG ulValue   :ND reachable时间
*              IP6_ND_SETFLAG_E enFlag:操作类型
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
ULONG ND_SetReachableTime_RouterByIndex(ULONG ulIfIndex, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_GetNSInterval_RouterByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description: 获取接口的NS探测间隔
*  Input:    ULONG ulIfIndex:接口索引
*  Output:  ULONG *pulRetVal:NS探测间隔
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
ULONG ND_GetNSInterval_RouterByIndex(ULONG ulIfIndex, ULONG *pulRetVal);

/*******************************************************************************
*    Func Name: ND_SetNSInterval_RouterByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description: 设置接口的NS探测间隔
*  Input:    ULONG ulIfIndex:接口索引
*              ULONG ulValue   :NS探测间隔
*              IP6_ND_SETFLAG_E enFlag:操作类型
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
ULONG ND_SetNSInterval_RouterByIndex(ULONG ulIfIndex, ULONG ulValue,
                                               IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_DelStaticNBEntryByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description:删除指定接口+地址的静态ND表项
*  Input:    ULONG ulIfIndex:接口索引
*              CHAR *szIp6Addr:目的IPv6地址
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
ULONG ND_DelStaticNBEntryByIndex(ULONG ulIfIndex, CHAR *szIp6Addr);

/*******************************************************************************
*    Func Name: ND_AddStaticNBEntry_VlanByIndex
* Date Created: 2014-08-01
*       Author: wuling 00201943
*  Description: 配置静态ND表项
*  Input:    ULONG ulIfIndex:接口索引
*              CHAR *pcIp6Addr:目的地址
*              UCHAR *pucMac :目的physical地址
*              USHORT usVlanId:Vlan ID
*              ULONG ulPortIndex:二层口索引
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
ULONG ND_AddStaticNBEntry_VlanByIndex(ULONG ulIfIndex, CHAR *pcIp6Addr, UCHAR *pucMac,
                                        USHORT usVlanId, ULONG ulPortIndex);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ND_API_H_ */

