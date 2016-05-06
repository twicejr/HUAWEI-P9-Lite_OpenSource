/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_mac.c
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

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: PTPV2_OverMacRcvPktHookEntry
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: overmac报文接收入口，挂接在ETHARP
*        Input: MBUF_S* pstMBuf:
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
ULONG PTPV2_OverMacRcvPktHookEntry (MBUF_S* pstMBuf)
{
    ULONG ulPktLen = 0;
    ULONG ulRet = 0;
    UINTPTR ulMsg[4] = {0};
    USHORT usEthType = 0;
    USHORT usTPID = 0;
    ULONG ulIfIndex = 0;
    ULONG ulPtpPkt = PTPV2_NO;

    TCPIP_PTPV2_IEEE8023VLAN_HEAD_S* pstEthVlanHeader = NULL;

    VOS_DBGASSERT(NULL != pstMBuf);

    ulPktLen = MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf);/*获取报文长度*/

    /*保证前连续性(宏MBUF_MAKE_MEMORY_CONTINUOUS);*/
    MBUF_MAKE_MEMORY_CONTINUOUS(pstMBuf, ulPktLen, PTPV2_MID, ulRet);
    if (TCPIP_PTP_OK != ulRet || NULL == pstMBuf)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280A, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTP LOG:Make Mbuf continue failed!\n", 0, 0, 0, 0);
        ulRet = TCPIP_PTP_ERR;
        
        goto EXIT_LABEL;
    }

    ulIfIndex = MBUF_GET_RECEIVE_IFNET_INDEX(pstMBuf);/*入接口索引*/
    /* 获取带VLAN的Eth头(MBUF_MTOD);*/
    pstEthVlanHeader = MBUF_MTOD(pstMBuf, TCPIP_PTPV2_IEEE8023VLAN_HEAD_S*);
    if (NULL == pstEthVlanHeader)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280B, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: mbuf head is NULL(If Index: %#x)!\n", ulIfIndex, 0, 0, 0);
        ulRet = TCPIP_PTP_ERR;
        
        goto EXIT_LABEL;
    }

    usTPID = VOS_NTOHS(pstEthVlanHeader->usTPID);
    usEthType = VOS_NTOHS(pstEthVlanHeader->usPTPType);/* 获取ETH头 */

    /* 如果usTPID == 0x8100  && usEthType == 0x88F7 则是携带VLAN 的1588
       如果usTPID == 0x88F7 则是不携带vlan的1588报文
       其他则肯定不是1588报文，继续原有流程处理
    */
    if ((usTPID == PTPV2_IEEE8023_ETHTYPE)
        || (usTPID == VLANTYPE_DOT1Q && PTPV2_IEEE8023_ETHTYPE == usEthType))
    {
        ulPtpPkt  = PTPV2_YES;
    }

    /*非PTP报文则返回给ETHARP 模块处理*/
    if (PTPV2_NO == ulPtpPkt)
    {
        ulRet = TCPIP_PTP_ERR;
        goto EXIT_LABEL;
    }

    /*将消息写入到PTP任务*/
    ulMsg[0] = PTPV2_IEEE8023_MSG_TYPE;     /*消息类型*/
    ulMsg[1] = (UINTPTR)pstMBuf;             /*消息类容地址*/
    ulMsg[2] = (UINTPTR)ulPktLen;                   /*消息长度*/
    ulMsg[3] = (UINTPTR)ulIfIndex;                  /*入接口索引*/

    if (TCPIP_PTP_OK != VOS_Que_Write(g_ulPtpV2PktQId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0))
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280C, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTP LOG: Writer message que failed! \n", 0, 0, 0, 0);
        ulRet = TCPIP_PTP_ERR_WRITE_QUE_FAIL;
        goto EXIT_LABEL;
    }

    /*事件失败 消息已经写入 不能释放内存*/
    if (TCPIP_PTP_OK != VOS_Ev_Write(g_ulPtpV2TaskId, PTPV2_IEEE8023MSG_EVENT_ID))
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280D, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTP LOG: Writer event que failed\n", 0, 0, 0, 0);
    }

    ulRet = TCPIP_PTP_OK;

EXIT_LABEL:
    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPv2_OverMacPktRcvProc
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: MBUF_S* pstMBuf:
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
ULONG PTPV2_OverMacPktRcvProc(MBUF_S* pstMBuf)
{
    TCPIP_PTP_ADDRINFO_S stAddrInfo;
    ULONG ulRet = TCPIP_PTP_OK;
    TCPIP_PTPV2_IEEE8023VLAN_HEAD_S* pstEthVlanHeader = NULL;
    UCHAR* pBuffer = NULL;
    ULONG ulPktLen = 0;
    ULONG ulIfRcvIndex = 0;
    USHORT usTPID = 0;
    PTPV2_MSGHEADER_S *pstMsgHeader = NULL;
    ULONG ulPtpExactLen = 0;

    /* Modified by wuling201943, 消除fortify告警, 2014/9/9   问题单号:DTS2014090901965 */
    if (NULL == pstMBuf)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }
    /*End of Modified by wuling201943, 2014/9/9   问题单号:DTS2014090901965 */

    ulPktLen = MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf);    /*获取报文长度*/
    ulIfRcvIndex = MBUF_GET_RECEIVE_IFNET_INDEX(pstMBuf);/*获取入接口索引*/
    pstEthVlanHeader = MBUF_MTOD(pstMBuf, TCPIP_PTPV2_IEEE8023VLAN_HEAD_S *);

    /*长度大于最大长度的报文直接丢弃*/
    if (ulPktLen > PTPV2_MAXIMUM_PKT_SIZE)
    {
        ulRet = TCPIP_PTP_ERR_PACKET_LEN;

        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorTotalLenPackets ++;
        
        goto EXIT_LABEL;
    }

    usTPID = VOS_NTOHS(pstEthVlanHeader->usTPID);
    /*暂时不比较VLAN，待定*/
    if (VLANTYPE_DOT1Q == usTPID)
    {
        /*删除二层头中的VLAN字段 */
        TCPIP_Mem_Move((CHAR*)pstEthVlanHeader + DOT1Q_TAG_SIZE, sizeof(*pstEthVlanHeader) - DOT1Q_TAG_SIZE, pstEthVlanHeader, PTPV2_MACADDRLEN * 2);
        MBUF_CUT_HEAD(pstMBuf, DOT1Q_TAG_SIZE);
        ulPktLen -= DOT1Q_TAG_SIZE;
        MBUF_MAKE_MEMORY_CONTINUOUS(pstMBuf, ulPktLen, PTPV2_MID, ulRet);
        if (ulRet != MBUF_OK || pstMBuf == NULL)
        {
            ulRet = TCPIP_PTP_ERR_INVALID_MBUF;

            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2F90, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTP LOG:Make Mbuf continue failed!\n", 0, 0, 0, 0);
            
            goto EXIT_LABEL;
        }
    }

    pBuffer = MBUF_MTOD(pstMBuf, UCHAR*);
    VOS_DBGASSERT(NULL != pBuffer);

    (VOID)TCPIP_Mem_Set((CHAR*)&stAddrInfo, 0, sizeof(TCPIP_PTP_ADDRINFO_S));

    /*获取MAC相关信息*/
    /* 目的信息 */
    stAddrInfo.stDstPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stDstPortAddr.usAddressLength   = PTPV2_MACADDRLEN;
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stDstPortAddr.unAddr.ucMacAddr,8, (VOID*)pBuffer, PTPV2_MACADDRLEN);
    /* 源信息 */
    stAddrInfo.stSrcPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stSrcPortAddr.usAddressLength   = PTPV2_MACADDRLEN;
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stSrcPortAddr.unAddr.ucMacAddr, 8,(VOID*)((ULONG)pBuffer + PTPV2_MACADDRLEN), PTPV2_MACADDRLEN);
    stAddrInfo.ulIfIndex = ulIfRcvIndex;

    /*去掉2层报文头并重新指向PTP数据位置*/
    MBUF_CUT_HEAD(pstMBuf, sizeof(TCPIP_PTPV2_IEEE8023_HEAD_S));

    pBuffer = MBUF_MTOD(pstMBuf, UCHAR*);
    ulPktLen = MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf);    /*重新获取报文长度*/
    /* 如果数据比实际长，则去掉多余的;
       如果数据比实际短，则丢弃报文
    */
    pstMsgHeader = (PTPV2_MSGHEADER_S*)pBuffer;

    /*域不相同，则丢弃报文*/
    if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber != pstMsgHeader->ucdomainNumber )
    {
       ulRet = TCPIP_PTP_ERR_INVALID_DOMAIN;

       /*报文统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorDomainNoPackets ++;
       
       goto EXIT_LABEL;
    }

    ulPtpExactLen = VOS_NTOHS(pstMsgHeader->usmessageLength);
    /*实际数据过短，则丢弃*/
    if (ulPtpExactLen > ulPktLen) 
    {
        ulRet = TCPIP_PTP_ERR_PACKET_LEN;

        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorPtpLenPackets ++;
        
        goto EXIT_LABEL;
    }
    /* 检查MBUF的数据长度是否大于PTP报文的总长，如果是，要截去多余的部分*/
    else if (ulPtpExactLen < ulPktLen)
    {
        if (MBUF_OK != MBUF_CutTail(pstMBuf,  ulPktLen - ulPtpExactLen))
        {
            ulRet = TCPIP_PTP_ERR_PACKET_LEN;

            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2F92, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTP LOG:Cut Mbuf tail failed!\n", 0, 0, 0, 0);
            
            goto EXIT_LABEL;
        }
    }

    ulRet = PTPV2_GeneralPktProc(pBuffer, ulPktLen, &stAddrInfo);

EXIT_LABEL:
    
    MBUF_Destroy(pstMBuf);
    
    return ulRet;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

