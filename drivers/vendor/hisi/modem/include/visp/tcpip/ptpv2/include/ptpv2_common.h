/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_common.h
*
*  Project Code:
*   Module Name: PTPV2 func
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_COMMON_H_
#define _PTPV2_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

VOID PTPV2_Lock(VOID);

VOID PTPV2_UnLock(VOID);

/*************************************************************************
*    Func Name: PTPV2_PktCircularSpaceCmp
* Date Created: 
*       Author: 
*  Description: 比较两数是否相等，以及偏差是否超过定义的半空间大小
*        Input: USHORT a, 数值a
*               USHORT b，数值b
*               USHORT usHalfSpace, 半空间大小
*       Output:
*       Return: 0: a与b相等
*               1: a到b的距离大于序号环(由小到大的方向，如图中里环所示)空间的一半
*               -1:a到b的距离小于序号环(由小到大的方向，如图中里环所示)空间的一半
*
*                          a
*               .-n--0--1--2--3
*               |   -->-->    |
*               .  |      |   4 b
*               |   <--<--    |
*               .-.--.--.--.--5
*
*      Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   
*
*************************************************************************/
LONG PTPV2_PktCircularSpaceCmp (USHORT a, USHORT b, USHORT usHalfSpace);

LONG PTPV2_Port_Tree_Compare(void* a, void* b);

LONG PTPV2_Slave_Tree_Compare(void* a, void* b);

ULONG PTPV2_GetGlobalInfo(ULONG ulCmd, ULONG* pData);

/*******************************************************************************
*    Func Name: PTPV2_CheckIfIndex
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ulIfIndex:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CheckIfIndex(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: PTPV2_CheckPortNoUpToMax
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CheckPortNoUpToMax();

/*******************************************************************************
*    Func Name: PTPV2_CheckPortValidation
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG usPtpPortNo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CheckPortValidation(ULONG usPtpPortNo);

/*******************************************************************************
*    Func Name: PTPV2_GetPortInfoByPort
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: 根据PTP端口号获取端口数据
*        Input: ULONG usPtpPortNo:
*               PTPV2_PORT_S **ppstPortInfo:
*       Output:
*       Return:
*      Caution: 对于OC来说，只获取第一个的端口数据
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetPortInfoByPort(ULONG usPtpPortNo, PTPV2_PORT_S **ppstPortInfo);

/*******************************************************************************
*    Func Name: PTPV2_GetPortInfoByIntf
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: 根据接口索引和地址信息获取端口数据
*        Input: ULONG ulIfIndex: 接口索引
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 地址 :用于将来扩展
*
*       Output: PTPV2_PORT_S** ppstFindPortInfo: 返回的端口数据
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG   PTPV2_GetPortInfoByIntf(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr, 
                                    PTPV2_PORT_S** ppstFindPortInfo);

/*******************************************************************************
*    Func Name: PTPV2_AddPortInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ulIfIndex:
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 地址不使用，用于将来L3 单播扩展
*               PTPV2_PORT_S** ppstAddPortInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_AddPortInfo(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr, 
                            PTPV2_PORT_S** ppstAddPortInfo);

/*******************************************************************************
*    Func Name: PTPV2_InitPortSubInfo
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: PTPV2_PORT_SUB_INFO_S *pstPortSubInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_InitPortSubInfo(PTPV2_PORT_SUB_INFO_S *pstPortSubInfo, ULONG ulFsmMode);

/*******************************************************************************
*    Func Name: PTPV2_InitPortInfo
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: PTPV2_PORT_S* pstPortInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_InitPortInfo(PTPV2_PORT_S* pstPortInfo);

/*******************************************************************************
*    Func Name: PTPV2_GetForeignMasterByPortId
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description: 根据报文的port id 查找foreign master
*        Input: PTPV2_MSGHEADER_S* pstMsgHeader:
*               PTPV2_FOREIGN_MASTER_S** ppstForeMaster:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetForeignMasterByPortId(PTPV2_MSGHEADER_S* pstMsgHeader,
                           PTPV2_FOREIGN_MASTER_S** ppstForeMaster);

VOID PTPV2_UpdateParentDS(PTPV2_FOREIGN_MASTER_S *pstSelectMaster, ULONG *ulChangeField);

VOID PTPV2_PPI_LogMsg(ULONG ulRet, USHORT usPtpPortNumber, ULONG ulPtpPpiCmd, VOID *pstPpiInfo);

ULONG PTPV2_GetClockType();

ULONG PTPV2_GetInitFlag();

ULONG PTPV2_HaveParent();

VOID PTPV2_WarningRemoveProc();

ULONG PTPV2_DelOCPortInfoEntry(USHORT usPtpPortNo, ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr);

ULONG PTPV2_DelBCPortInfoEntry(USHORT usPtpPortNo);

ULONG PTPV2_DelBCPortInfo(PTPV2_PORT_S *pstDelPortInfo);

VOID PTPV2_DelAllOCPortInfo();

VOID PTPV2_DelAllBCPortInfo();

extern ULONG TCPIP_SmP_Wait(ULONG ulMutexID, ULONG time);

VOID PTPV2_Set_PortRole(PTPV2_PORT_SUB_INFO_S *pstSubPortInfo, UCHAR ucPtpPortRole);

VOID PTPV2_Set_FsmState(PTPV2_PORT_SUB_INFO_S *pstSubPortInfo, UCHAR ucPtpPortFsmState);

UCHAR PTPV2_GetPortRoleByFsmState(UCHAR ucPortFsmState);

/* 计算转换log值到毫级别的整数的宏 */
#define PTPV2_CAL_LOG_TO_MILL(cLogValue,ulMillValue)\
{\
    ULONG ulLogValueAbs = 0;\
    (ulMillValue) = 1;     \
    ulLogValueAbs = (cLogValue) >= 0 ? (cLogValue) : -(cLogValue);\
    (ulMillValue) = (ulMillValue) << ulLogValueAbs;\
    (ulMillValue) = (cLogValue) >= 0 ? (1000 * (ulMillValue)):(1000 / (ulMillValue));\
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_COMMON_h_   */
