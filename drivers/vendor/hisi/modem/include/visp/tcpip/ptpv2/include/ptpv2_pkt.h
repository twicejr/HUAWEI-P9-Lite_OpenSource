/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_pkt.h
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

#ifndef _PTPV2_PKT_H_
#define _PTPV2_PKT_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTPV2_PktWithCastModeMatch(PTPV2_PORT_S *pstPortInfo, TCPIP_PTP_ADDRINFO_S *pstAddrInfo);

/*******************************************************************************
*    Func Name: PTPV2_GeneralPktProc
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UCHAR* pBuffer:
*               ULONG ulPacketLen:
*               TCPIP_PTP_ADDRINFO_S *pstAddrInfo:
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
ULONG PTPV2_GeneralPktProc(UCHAR* pBuffer, ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S *pstAddrInfo);

/*******************************************************************************
*    Func Name: PTPV2_PktAnnSequenceIdCheck
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
 *  Description: announce报文序列号检查
*        Input: PTPV2_PORT_S *pstPtpPort:
*               PTPV2_MSGHEADER_S* pstMsgHeader:
*               TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo:
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
ULONG PTPV2_PktAnnSequenceIdCheck(PTPV2_PORT_S *pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                        TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo);

ULONG PTPV2_PktFlagfieldCheck(PTPV2_PORT_S *pstPtpPort, CHAR *pcFlagfield, ULONG ulMsgType);

/******************************************************************************
*Func Name   : PTPV2_PktGeneralHeaderCheck
*Description : PTP消息头通用项合法性检测，由PTP_PKT_HeaderCheck调用
*Input       : PTP_PORT_S       *pstPtpPort   时钟端口控制块指针
*              PTP_MSGHEADER_S  *pstMsgHeader 消息头
*              ULONG            ulPtpMsgType  消息类型
*              ULONG            ulPacketLen   报文长度
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-5             wangchengyang  Create
*******************************************************************************/
ULONG PTPV2_PktGeneralHeaderCheck(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                            ULONG ulPtpMsgType, ULONG ulPacketLen);

ULONG PTPV2_BCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                    ULONG ulPtpMsgType);

ULONG PTPV2_OCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                    ULONG ulPtpMsgType);

/******************************************************************************
*Func Name   : PTPV2_PKT_HeaderCheck
*Description : PTP消息头合法性检测总入口，所有需要检查头的均调用该接口
*Input       : PTP_PORT_S       *pstPtpPort   时钟端口控制块指针
*              PTP_MSGHEADER_S  *pBuffer      报文
*              ULONG            ulPtpMsgType  报文类型(详见PTP_MSG_TYPE_E)
*              ULONG            ulPacketLen   接收的报文长度
*              PTP_ADDRINFO_S   *pstAddrInfo  接收到报文的地址以及UDP信息

*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-5             wangchengyang  Create
*  2009-4-28  wangchengyang-xujun62830-57575         VISPV1R8C01.消除Vc三级告警
*  2010-12-21  wangchengyang62830         DTS2010122100198 .
*******************************************************************************/
/*
   Bits                                  Octets  Offset
   7     6     5     4   3   2   1   0
   |transportSpecific|  messageType  |     1       0
   |    reserved     |  versionPTP   |     1       1
   |           messageLength         |     2       2
   |           domainNumber          |     1       4
   |           reserved              |     1       5
   |           flagField             |     2       6
   |           correctionField       |     8       8
   |           reserved              |     4       16
   |           sourcePortIdentity    |     10      20
   |           sequenceId            |     2       30
   |           controlField          |     1       32
   |           logMessageInterval    |     1       33
*/
ULONG PTPV2_PktHeaderCheck(PTPV2_PORT_S* pstPtpPort, UCHAR *pucBuffer, ULONG ulPtpMsgType,
                          ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S* pstAddrInfo);

ULONG PTPV2_BuildAnnPktHeader(PTPV2_PORT_S* pstPtpPort,  PTPV2_MSGHEADER_S* pstMsgHeader);

ULONG PTPV2_ComputeSeqId(VOID *pThis, MBUF_S *pstMbuf);

ULONG PTPV2_OverMacSndAnnPkt(VOID *pThis, VOID *pData, VOID *pAddr);

VOID PTPV2_PrintHeader(PTPV2_MSGHEADER_S *pstMsgHeader, TCPIP_PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTPV2_GrandMasterIDCheck(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg);

ULONG PTPV2_BuildAnnPktClockQa(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_CLOCK_QA_S* pstClockQa);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_FUNC_h_   */

