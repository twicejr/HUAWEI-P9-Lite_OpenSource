/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_pkt.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP Common
*  Date Created: 2008-06-02
*        Author: lishenchuan
*   Description: PTP 公用函数申明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-11      lishenchuan       Create
*
*******************************************************************************/
#ifndef __ptp__common__h__
#define __ptp__common__h__

#ifdef __cplusplus
extern "C" {
#endif

/* 以下部分为对内接口 */

/* 出入指针不需要分配内存,返回NULL表示获取失败 */
ULONG PTP_GetUnicastMaster(PTP_PORT_ADDR_S* pstPortAddr, PTP_UNI_MASTER_NODE_S **ppstUnincastMaster);

/* 根据master地址查询ptp_port_s下挂的slave table 节点的序号 */
ULONG PTP_GetUniSlaveTbl(PTP_PORT_S * pstPtpPort, PTP_PORT_ADDR_S * pstPortAddr, PTP_UNI_SLAVE_TBL_S **ppstUniSlaveTbl);

/* 增加ptp_port_s下挂的slave table 节点 */
ULONG PTP_AddUniSlaveTbl(PTP_PORT_S * pstPtpPort, PTP_PORT_ADDR_S * pstPortAddr);

/* 删除ptp_port_s下挂的slave table 节点 */
ULONG PTP_DelUniSlaveTbl(PTP_PORT_S * pstPtpPort, PTP_PORT_ADDR_S *pstPortAddr);

/* 添加表项,内部分配和释放内存 */
ULONG PTP_AddUnicastSlave(USHORT usPtpPortNumber, PTP_ADDRINFO_S *pstAddrInfo, PTP_UNI_SLAVE_NODE_S **ppstUnicastSlave);

/* 删除表项, 内部需要释放内存 */
ULONG PTP_DelUnicastSlave(USHORT usPtpPortNumber, PTP_UNI_SLAVE_NODE_S *pstSlave);

/* 获取某一表项, 不需要分配内存, NULL为获取失败 */
ULONG PTP_GetUnicastSlave(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, PTP_UNI_SLAVE_NODE_S **ppstUnicastSlave);

/* 获取某一表项, 不需要分配内存, NULL为获取失败  */
ULONG PTP_GetAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_ACCEPT_MASTER_S **ppstAcceptMaster);

ULONG PTP_GetAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_ACCEPT_MASTER_S **ppstAcceptMaster);

VOID PTP_Begin_PT(VOID);

VOID PTP_End_PT(VOID);

ULONG PTP_IsHuaweiDev(UCHAR* pucOrganizationId);

ULONG PTP_GetPtpPortByAddr(PTP_PORT_ADDR_S *pstPortAddr, PTP_PORT_S **ppstPtpPort);

ULONG PTP_AddForeignMaster(PTP_PORT_S *pstPtpPort,PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, PTP_FOREIGN_MASTER_S **ppstForeMaster);

ULONG PTP_DelForeignMaster(PTP_PORT_S *pstPtpPort,PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

ULONG PTP_GetForeignMaster(PTP_PORT_S *pstPtpPort,PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, PTP_FOREIGN_MASTER_S **ppstForeMaster);

VOID PTP_ClearUnicastMasterRunInfo(PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

VOID PTP_ClearUnicastMasterCfgInfo(PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/* Add for BC3D03003 */
ULONG PTP_SetMIpInfo(USHORT usPtpPortNumber, PTP_MIPINFO_S *pstMIpInfo);

ULONG PTP_GetMIpInfo(USHORT usPtpPortNumber, PTP_MIPINFO_S *pstMIpInfo);

ULONG PTP_GetUnicastSlaveByID(USHORT usPtpPortNumber,
                              PTP_CLOCK_ID_SZ szClockId,
                              PTP_UNI_SLAVE_NODE_S **ppstUnicastSlave);
ULONG PTP_Str2Mac(UCHAR *pStrMac,UCHAR szMac[]);

ULONG PTP_Addr_Cmp(PTP_PORT_ADDR_S *pstDstAddr,PTP_PORT_ADDR_S *pstSrcAddr,LONG *plRetResult);

ULONG PTP_Check_MAC_Zero_Addr(UCHAR *ucpPortMac);

/*Begin Add by heyijun KF62476 for DTS2011122700669, 调试打印增加基于地址过滤功能 */
ULONG PTP_CheckPacketFilter(PTP_ADDRINFO_S *pstAddrInfo);
/*End   Add by heyijun KF62476 for DTS2011122700669, 调试打印增加基于地址过滤功能 */

ULONG PTP_GetUnicastMasterByPortId(PTP_PORT_ID_S *pstPortId, PTP_UNI_MASTER_NODE_S **ppstUnicastMaster);

ULONG PTP_GetForeignMasterByPortId(PTP_PORT_ID_S *pstPortId, PTP_FOREIGN_MASTER_S **ppstForeMaster);
/* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
ULONG PTP_GetSlaveStatByNum(PTP_SLAVE_STAT_LIST_S *pstStatList, ULONG ulListSize);
/* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */

ULONG PTP_AddPortAddrVrf(USHORT usPortNum, PTP_PORT_ADDR_S *pstPortAddr, 
                            ULONG ulVrfIndex, ULONG ulIfIndex);

ULONG PTP_DelPortAddrVrf(USHORT usPortNum, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

ULONG PTP_GetPortAddrVrf(USHORT usPortNum, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, PTP_PORT_ADDR_VRF_NODE_S **ppstPortAddrVrf);

ULONG PTP_GetPortAddrVrfByVrf(USHORT usPortNum, ULONG ulVrfIndex, PTP_ALL_PORT_ADDR_VRF_NODE_S *pstAllPortAddrVrf);

ULONG PTP_GetAllPortAddrVrf(USHORT usPortNum, PTP_ALL_PORT_ADDR_VRF_NODE_S *pstAllPortAddrVrf);

ULONG PTP_ShowPortAddrVrf(USHORT usPortNum);

ULONG PTP_AddVrfSocket(ULONG ulVrfIndex);

ULONG PTP_DelVrfSocket(ULONG ulVrfIndex);

ULONG PTP_GetVrfSocket(ULONG ulVrfIndex, PTP_VRF_NODE_S **ppstVrfNode);

ULONG PTP_GetVrfSocketByFd(LONG lSocketFd, PTP_VRF_NODE_S **ppstVrfNode);

ULONG PTP_GetAllVrfSocket(PTP_ALL_VRF_NODE_S *pstAllVrfNode);

ULONG PTP_ShowVrfSocket(VOID);

ULONG PTP_SetPtpPortAddrCommon(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

ULONG PTP_AddUnicastMasterCommon(PTP_PORT_ADDR_S * pstPortAddr,PTP_PORT_ADDR_S * pstExtPortAddr,ULONG ulVrfIndex);

ULONG PTP_DelUnicastMasterCommon(PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

ULONG PTP_GetUnicastMasterCommon(PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, PTP_UNI_MASTER_NODE_S **ppstUnicastMaster);

ULONG PTP_StartNegoCommon(PTP_PORT_ADDR_S *pstMasterPortAddr, ULONG ulVrfIndex);

ULONG PTP_EndNegoCommon(PTP_PORT_ADDR_S * pstMasterPortAddr,ULONG ulVrfIndex);

ULONG PTP_QueryLinkStatusCommon(USHORT usPortNumber, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, BOOL_T* pbLink);

ULONG PTP_GetLinkPacketStatCommon(PTP_PORT_ADDR_S *pstMasterPortAddress, ULONG ulVrfIndex, PTP_PACKET_STAT_S *pLinkPacketStat);

ULONG PTP_ClearLinkPacketStatCommon(PTP_PORT_ADDR_S *pstMasterPortAddress, ULONG ulVrfIndex);

ULONG PTP_SetBMCSelectModeCommon(ULONG ulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

ULONG PTP_SetBMCSelectModeManual(PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, ULONG *pulCmpResult);

ULONG PTP_GetBMCSelectModeCommon(ULONG *pulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, ULONG *pulVrfIndex);

ULONG PTP_SetMasterWeightCommon(PTP_PORT_ADDR_S *pstMaster, ULONG ulVrfIndex, ULONG ulWeight);

ULONG PTP_GetMasterWeightCommon(PTP_PORT_ADDR_S *pstMaster, ULONG ulVrfIndex, ULONG *pulWeight);

ULONG PTP_SetPTSFByTypeCommon(PTP_PORT_ADDR_S *pstMaster, ULONG ulVrfIndex, ULONG ulType, ULONG ulPTSFValue);

ULONG PTP_GetPTSFByTypeCommon(PTP_PORT_ADDR_S *pstMaster, ULONG ulVrfIndex, ULONG ulType, ULONG *pulPTSFValue);

ULONG PTP_ReqCancelCommon(USHORT usPtpPortNumber,ULONG ulMessageType,PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

ULONG PTP_GetCurrentParentCommon(PTP_PORT_ADDR_S *pstParentPortAddr, ULONG *pulVrfIndex);

VOID PTP_ShowLinkPacketStatisticCommon(USHORT usNetworkProtocol, USHORT usAddressLength, UCHAR *pszIPOrMacAddr, ULONG ulVrfIndex);

ULONG PTP_QueryUnicastMasterCommon(PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, PTP_UNICAST_MASTER_S *pstUnicastMaster);

ULONG PTP_CheckMultiVrfStat(VOID);

ULONG PTP_SndMsgFsmDecision(ULONG ulPortNumber);

ULONG PTP_PreDoDecisionGrant(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S* pstUniMaster);

ULONG PTP_PreDoDecisionReject(PTP_PORT_S *pstPtpPort, PTP_UNI_MASTER_NODE_S* pstUniMaster);

VOID PTP_BMC_AddUnicastLinkPpi(PTP_PORT_S *pstPtpPort, 
                         PTP_UNI_MASTER_NODE_S* pstUniMaster, PTP_FOREIGN_MASTER_S *pstBmcParent);

VOID PTP_BMC_SetUnicastLinkPpi(PTP_PORT_S *pstPtpPort, 
                         PTP_UNI_MASTER_NODE_S* pstUniMaster, PTP_FOREIGN_MASTER_S *pstBmcParent);

VOID PTP_BMC_DelUnicastLinkPpi(PTP_PORT_S *pstPtpPort, 
                         PTP_UNI_MASTER_NODE_S* pstUniMaster, PTP_FOREIGN_MASTER_S *pstBmcParent);

VOID PTP_BMC_UnsetUnicastLinkPpi(PTP_PORT_S *pstPtpPort, 
                         PTP_UNI_MASTER_NODE_S* pstUniMaster, PTP_FOREIGN_MASTER_S *pstBmcParent);

ULONG PTP_AddMultiPortAddrNoLog(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr);

ULONG PTP_DelMultiPortAddrNoLog(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr);

ULONG PTP_SetPortAddrMaxCfgNumNoLog(USHORT usNetworkProtocol, USHORT usMaxNum);

ULONG PTP_AddPortAddrWithVrfNoLog(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

ULONG PTP_DelPortAddrWithVrfNoLog(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

ULONG PTP_StartNegoWithVrfNoLog(PTP_PORT_ADDR_S *pstMasterPortAddr, CHAR *pcVrfName);

ULONG PTP_EndNegoWithVrfNoLog(PTP_PORT_ADDR_S *pstMasterPortAddr, CHAR *pcVrfName);

ULONG PTP_AddUnicastMasterWithVrfNoLog(PTP_PORT_ADDR_S *pstPortAddr,PTP_PORT_ADDR_S *pstExtPortAddr, CHAR *pcVrfName);

ULONG PTP_DelUnicastMasterWithVrfNoLog(PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

ULONG PTP_ClearLinkPacketStatWithVrfNoLog(PTP_PORT_ADDR_S *pstMasterPortAddress, CHAR *pcVrfName);

ULONG PTP_SetBMCSelectModeWithVrfNoLog(ULONG ulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

ULONG PTP_SetMasterWeightWithVrfNoLog(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulWeight);

ULONG PTP_SetPTSFByTypeWithVrfNoLog(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulType, ULONG ulPTSFValue);

ULONG PTP_SetSlaveMultiSelectModeNoLog(ULONG ulMultiSelMode);

ULONG PTP_AddUnicastMasterNoLog(PTP_PORT_ADDR_S *pstPortAddr, PTP_PORT_ADDR_S *pstExtPortAddr);

ULONG PTP_DelUnicastMasterNoLog(PTP_PORT_ADDR_S *pstPortAddr);

ULONG PTP_ExternNotifyPTPWithClassNoLog(USHORT usPtpPortNumber, USHORT usCmd, UCHAR ucClass);

/*******************************************************************************
*    Func Name: PTP_GetCurrentPortNumber
* Date Created: 2012-01-06
*       Author: guo00178934
*  Description: 获取当前PTP端口号
*        Input: USHORT *pusPtpPortNumber:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-06   guo00178934             Create
*
*******************************************************************************/
ULONG PTP_GetCurrentPortNumber(USHORT *pusPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_GetWayMode
* Date Created: 2012-01-06
*       Author: guo00178934
*  Description: 获取当前接口为1-Way Or 2-Way模式
*        Input: USHORT usPtpPortNumber:
*               ULONG *pulMode:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-06   guo00178934             Create
*
*******************************************************************************/
ULONG PTP_GetWayMode(USHORT usPtpPortNumber, ULONG *pulMode);

/*******************************************************************************
*    Func Name: PTP_IsValidParentPortAddr
* Date Created: 2012-01-06
*       Author: guo00178934
*  Description: 判断ParentPortAddr是否有效
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-06   guo00178934             Create
*
*******************************************************************************/
BOOL_T PTP_IsValidParentPortAddr(PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex, UCHAR ucCastMode);

/*******************************************************************************
*    Func Name: PTP_IsOneWayMode
* Date Created: 2012-01-07
*       Author: guo00178934
*  Description: 判断当前的PTP端口是否为1-Way模式
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-07   guo00178934             Create
*
*******************************************************************************/
BOOL_T PTP_IsOneWayMode(VOID);

/*******************************************************************************
*    Func Name: PTP_IsTwoWayMode
* Date Created: 2012-01-07
*       Author: guo00178934
*  Description: 判断当前的PTP端口是否为2-Way模式
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-07   guo00178934             Create
*
*******************************************************************************/
BOOL_T PTP_IsTwoWayMode(VOID);

/*******************************************************************************
*    Func Name: PTP_CalcDurationTimeout
* Date Created: 2012-01-07
*       Author: guo00178934
*  Description: 计算Duration重协商时间
*        Input: PTP_PORT_S *pstPtpPort:
*               ULONG ulDurationType:
*               ULONG ulDuration:
*       Output: 
*       Return: 
*      Caution: 内部代码调用，不对参数做有效性判断
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-07   guo00178934             Create
*
*******************************************************************************/
ULONG PTP_CalcDurationTimeout(PTP_PORT_S *pstPtpPort, ULONG ulDurationType, ULONG ulDuration);

/*Added by guo00178934, PTP 告警需求, 2012/1/13   问题单号:20120112_1 */
/*******************************************************************************
*    Func Name: PTP_WarningLinkUpDown
* Date Created: 2012-01-13
*       Author: guo00178934
*  Description: UniMaster链路Up Down告警
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*               PTP_PORT_S *pstPtpPort:
*               ULONG ulWarnID:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-13   guo00178934             Create
*
*******************************************************************************/
VOID PTP_WarningLinkUpDown(PTP_UNI_MASTER_NODE_S *pstUniMaster, PTP_PORT_S *pstPtpPort, ULONG ulWarnID);

/*******************************************************************************
*    Func Name: PTP_WarningSyncUpDown
* Date Created: 2012-01-13
*       Author: guo00178934
*  Description: UniMaster Sync Up和Down告警
                注意:Sync Up和Down告警依赖于ADD PPI下发,需在PPI下发前调用
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*               PTP_PORT_S *pstPtpPort:
*               ULONG ulWarnID:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-13   guo00178934             Create
*
*******************************************************************************/
VOID PTP_WarningSyncUpDown(PTP_UNI_MASTER_NODE_S *pstUniMaster, PTP_PORT_S *pstPtpPort, ULONG ulWarnID);

/*******************************************************************************
*    Func Name: PTP_WarningDelayUpDown
* Date Created: 2012-01-13
*       Author: guo00178934
*  Description: UniMaster Delay Up和Down告警
                注意:Delay Up和Down告警依赖于SET PPI下发,需在PPI下发前调用
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*               PTP_PORT_S *pstPtpPort:
*               ULONG ulWarnID:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-13   guo00178934             Create
*
*******************************************************************************/
VOID PTP_WarningDelayUpDown(PTP_UNI_MASTER_NODE_S *pstUniMaster, PTP_PORT_S *pstPtpPort, ULONG ulWarnID);

/*******************************************************************************
*    Func Name: PTP_WarningRefuse
* Date Created: 2012-01-13
*       Author: guo00178934
*  Description: 协商(Annc, Sync, Delay)拒绝告警
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*               PTP_PORT_S *pstPtpPort:
*               ULONG ulMsgType:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-13   guo00178934             Create
*
*******************************************************************************/
VOID PTP_WarningRefuse(PTP_UNI_MASTER_NODE_S *pstUniMaster, PTP_PORT_S *pstPtpPort, ULONG ulMsgType);

/*******************************************************************************
*    Func Name: PTP_WarningTimeout
* Date Created: 2012-01-13
*       Author: guo00178934
*  Description: 协商(Annc, Sync, Delay)超时告警
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*               PTP_PORT_S *pstPtpPort:
*               ULONG ulMsgType:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-13   guo00178934             Create
*
*******************************************************************************/
VOID PTP_WarningTimeout(PTP_UNI_MASTER_NODE_S *pstUniMaster, PTP_PORT_S *pstPtpPort, ULONG ulMsgType);
/* End of Added by guo00178934, 2012/1/13   问题单号:20120112_1 */



BOOL_T PTP_BMC_PpiParaCmpCommon(PTP_PORT_S *pstPtpPort,
    PTP_FOREIGN_MASTER_S *pstBmcParent, PTP_UNI_MASTER_NODE_S *pstUniMaster);

BOOL_T PTP_BMC_AddPpiParaCmp(PTP_PORT_S *pstPtpPort,
    PTP_FOREIGN_MASTER_S *pstBmcParent, PTP_UNI_MASTER_NODE_S *pstUniMaster);


BOOL_T PTP_BMC_SetPpiParaCmp(PTP_PORT_S *pstPtpPort,
    PTP_FOREIGN_MASTER_S *pstBmcParent, PTP_UNI_MASTER_NODE_S *pstUniMaster);


ULONG PTP_BMC_PpiParaCopy(PTP_PORT_S *pstPtpPort,
    PTP_FOREIGN_MASTER_S *pstBmcParent, PTP_UNI_MASTER_NODE_S *pstUniMaster);

extern ULONG PTP_SetKeepAliveMode_Common(UCHAR ucMode);

/******************************************************************************
*Func Name   : PTP_MasterAutoNotifyProc
*Description : 根据不同状态命令字，通知协议栈
*Input       : USHORT usPtpPortNumber:    PTP端口号
               USHORT usCmd:              notify命令字，0:master锁定基准时钟源、1:master失锁
*Output      :
*Return      : PTP_OK:     成功
               other:      失败
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-11           dutianyi       Create
*******************************************************************************/
ULONG PTP_MasterAutoNotifyProc(USHORT usPtpPortNumber, USHORT usCmd);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of __ptp__common__h__    */

