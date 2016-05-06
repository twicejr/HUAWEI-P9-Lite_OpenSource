/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_pkt.c
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

#include "vos/vospubh/iunknown.h"

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_ann.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "ifnet/core/include/if_func.h"
#include "tcpip/trunk/include/trunk_inc.h"

extern struct IIF_COMP_TRUNK_ComIntFUNVtbl* g_pstIfTRUNKFunVtbl;

ULONG PTPV2_PktWithCastModeMatch(PTPV2_PORT_S *pstPortInfo, TCPIP_PTP_ADDRINFO_S *pstAddrInfo)
{
    /*报文类型和 PTP端口配置的单播/多播/overmac模式是否匹配，不匹配则丢弃*/
    /*目前只有overmac*/
    if (TCPIP_PTP_CLOCK_IEEE8023_MODE != pstPortInfo->pstSubPortInfo->ucCastMode)
    {
        return TCPIP_PTP_ERR_CAST_MODE;
    }

    return TCPIP_PTP_OK;
}

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
ULONG PTPV2_GeneralPktProc(UCHAR* pBuffer, ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S *pstAddrInfo)
{
    PTPV2_MSGHEADER_S* pstMsgHeader = NULL;
    ULONG ulRet      = TCPIP_PTP_OK;
    PTPV2_PORT_S *pstPortInfo = NULL;
    TCPIP_PTP_ADDRINFO_S stAddrInfo = { { 0 } };
    
    /* 参数合法性检查 */
    VOS_DBGASSERT(NULL != pBuffer);
    VOS_DBGASSERT(NULL != pstAddrInfo);

    (VOID)TCPIP_Mem_Copy(&stAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S), pstAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S));

    /*如果注册了获取报文功能,则进行获取报文处理，对于报文发送，不关心长度*/
    /*目前仅传入接口索引信息*/
    
    /*获取PTP端口信息 */
    ulRet = PTPV2_GetPortInfo(&stAddrInfo, &pstPortInfo);
    /*Added by wuling201943,  , 2014/11/20   问题单号:DTS2014102506925 */
    /*目前BC应用中，Hert时钟组是基于物理端口配置PTP功能的，而实际上物理
        端口是Trunk的成员端口。如果后续基于Trunk端口配置PTP，则报文入接口仍然
        是物理端口，导致根据物理端口无法匹配到PTP的配置端口信息。所以在第
        一次通过物理端口查找失败后，再次通过Trunk端口进行查找。*/
    if (TCPIP_PTP_OK != ulRet)
    {
        ULONG ulTrunkIfIndex = 0;
        
        if ((NULL != g_pstIfTRUNKFunVtbl)
            && (g_pstIfTRUNKFunVtbl->pfTRUNK_IsTrunkPort(IF_GetIfByIndex(stAddrInfo.ulIfIndex))))
        {
            if (TCPIP_PTP_OK == g_pstIfTRUNKFunVtbl->pfTRUNK_GetTrunkIfByPortIf(
                                            stAddrInfo.ulIfIndex, &ulTrunkIfIndex))
            {
                /*将接口索引改成trunk的接口索引*/
                stAddrInfo.ulIfIndex = ulTrunkIfIndex;
                ulRet =  PTPV2_GetPortInfo(&stAddrInfo, &pstPortInfo);
            }
        }        
    }
    /* End of Added by wuling201943, 2014/11/20   问题单号:DTS2014102506925 */
    
    if (TCPIP_PTP_OK != ulRet)
    {
        /*丢包并统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorAddrPackets ++;

        return ulRet;
    }

    /*获取报文回调函数*/
    if (NULL != g_pfPtpV2CapturePktFunc)
    {
        (VOID)g_pfPtpV2CapturePktFunc(TCPIP_PTP_PKT_IN, pBuffer, ulPacketLen, &stAddrInfo,
                                      pstPortInfo->pstSubPortInfo->usPortNo);
    }

    /*Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_INPUT)
    {
        PTPV2_ANN_PrintAnn((PTPV2_ANNOUNCE_MSG_S *)pBuffer, &stAddrInfo, TCPIP_PTP_PKT_IN);
    }

    pstMsgHeader = (PTPV2_MSGHEADER_S *)pBuffer;

    /* 根据不同的报文类型，交由不同的处理函数处理 */
    switch (pstMsgHeader->ucmessageType)
    {
        case TCPIP_PTP_MSG_ANNOUNCE:  /* ANNOUNCE消息 */
            ulRet = PTPV2_Ann_RcvMsg(pBuffer, ulPacketLen, &stAddrInfo, pstPortInfo);
            break;
        default:
            ulRet = TCPIP_PTP_ERR_MSGTYPE;
            break;
    }

    return ulRet;
}

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
ULONG PTPV2_PktAnnSequenceIdCheck(PTPV2_PORT_S *pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo)
{
    ULONG ulRet   = TCPIP_PTP_OK;
    USHORT usNextSequenceId = 0; /* 期望的下一个报文的序列号 */
    PTPV2_FOREIGN_MASTER_S *pstFindMaster = NULL;
    USHORT usSequenceId = 0;

    VOS_DBGASSERT(NULL != pstPortAddrInfo);
    VOS_DBGASSERT(NULL != pstPtpPort);

    ulRet = PTPV2_GetForeignMasterByPortId(pstMsgHeader, &pstFindMaster);
    if (TCPIP_PTP_OK != ulRet)
    {
        /*找不到，则是第一次收到报文，无条件通过检查*/
        return TCPIP_PTP_OK;
    }

    /*获取announce报文的序列号*/
    usSequenceId = VOS_NTOHS(pstMsgHeader->usSequenceId);

    usNextSequenceId = pstFindMaster->usRcvAnnSequenceId + 1;
    if (0 != PTPV2_PktCircularSpaceCmp(usNextSequenceId, usSequenceId, 0x8000))
    {
        if (usNextSequenceId > usSequenceId)
        {
           /*报文统计*/
           g_stGlobalPtpV2PktStat.ulRcvErrorSeqIdPackets ++;
           return TCPIP_PTP_ERR_SEQUENCEID;
        }

        /* 接收到报文的sequnce id不是预期的本机保存的下一个，说明中途链路有丢包，但允许 */
        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorUnexpectedSeqIdPackets ++;
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_PktFlagfieldCheck(PTPV2_PORT_S *pstPtpPort, CHAR *pcFlagfield, ULONG ulMsgType)
{
    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pcFlagfield);

    if((NULL == pstPtpPort) || (NULL == pcFlagfield))
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* 第一个字节正确性检查 */
    /* flag域第一个字节的第三位是单多播标记 */
    /*目前仅支持二层*/
    if (TCPIP_PTP_CLOCK_IEEE8023_MODE == pstPtpPort->pstSubPortInfo->ucCastMode)
    {
        if (0 != (((*pcFlagfield) >> 2) & 0x01))
        {
            return TCPIP_PTP_ERR_UNICASTFLAG;
        }
    }

    return TCPIP_PTP_OK;

}


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
ULONG PTPV2_PktGeneralHeaderCheck(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, ULONG ulPtpMsgType, ULONG ulPacketLen)
{
    ULONG ulRet      = TCPIP_PTP_OK;

    if (pstMsgHeader->ucversionPTP != PTPV2_VERSION)
    {
        /*log*/
        return TCPIP_PTP_ERR_VERSION;
    }

    /*Modified by dutianyi for DTS2014060505599, 2014/6/7, domainNumber已经在入口处检查过了，此处无需再次判断*/
    /*End of modifying by dutianyi for DTS2014060505599, 2014/6/7, domainNumber已经在入口处检查过了，此处无需再次判断*/

    /* flagfield域合法性检查 */
    ulRet = PTPV2_PktFlagfieldCheck(pstPtpPort, (CHAR*)(pstMsgHeader->ucflagField), ulPtpMsgType);
    if (TCPIP_PTP_OK != ulRet)
    {
        /*log*/
        return ulRet;
    }

    /*协议一致性检查优化*/
    if (PTPV2_CONTROLFIELD_ALL_OTHER != pstMsgHeader->ucControlField)
    {
        /*log*/
        return TCPIP_PTP_ERR_PACKET;
    }

    return TCPIP_PTP_OK;

}

ULONG PTPV2_BCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, ULONG ulPtpMsgType)
{
    PTPV2_FOREIGN_MASTER_S *pstBMCParent = g_pstBmcEbest;

    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pstMsgHeader);

    if ((NULL == pstPtpPort) || (NULL == pstMsgHeader) )
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* flag域第一个字节的第三位是单多播标记 */
    if (TCPIP_PTP_CLOCK_UNICAST_MODE == pstPtpPort->pstSubPortInfo->ucCastMode)
    {
        pstMsgHeader->ucflagField[0] |= 0x04;
    }
    else
    {
        pstMsgHeader->ucflagField[0] &= 0xFB;
    }

    /*该字段修改需要兼容老版本，老版本的Slave会对该字段做检查*/
    /* If the port is transmitting a unicast Announce message
    under the terms of this subclause and is in the MASTER state,
    set  the flagField.alternateMasterFlag to FALSE,
    otherwise set the flagField.alternateMasterFlag to TRUE. */
    /*根据G.8265.1中规定annouce和signing报文的alternateMasterFlag字段都应为FALSE*/
    pstMsgHeader->ucflagField[0] &= 0xFE;

    /* 第二个字节填充 */
    if (TCPIP_PTP_MSG_ANNOUNCE == ulPtpMsgType)
    {
        if (pstBMCParent != NULL)
        {
            pstMsgHeader->ucflagField[1] = pstBMCParent->ucFlagField[1];
        }
        else
        {
            /*当前没有选中源的时候，用最近的ParentDs信息填充flagField字段*/
            pstMsgHeader->ucflagField[1] = 0;
            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bLeap61)
            {
                pstMsgHeader->ucflagField[1] |= 0x01;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bLeap59)
            {
                pstMsgHeader->ucflagField[1] |= 0x02;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bCurrentUtcOffsetValid)
            {
                pstMsgHeader->ucflagField[1] |= 0x04;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bPtpTimescale)
            {
                pstMsgHeader->ucflagField[1] |= 0x08;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bTimeTraceable)
            {
                pstMsgHeader->ucflagField[1] |= 0x10;
            }

            if (BOOL_TRUE == g_pstPtpGlobalInfo->stParentDs.bFrequencyTraceable)
            {
                pstMsgHeader->ucflagField[1] |= 0x20;
            }
        }
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_OCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, ULONG ulPtpMsgType)
{
    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pstMsgHeader);

    if ((NULL == pstPtpPort) || (NULL == pstMsgHeader) )
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* flag域第一个字节的第三位是单多播标记 */
    if (TCPIP_PTP_CLOCK_UNICAST_MODE == pstPtpPort->pstSubPortInfo->ucCastMode)
    {
        pstMsgHeader->ucflagField[0] |= 0x04;
    }
    else
    {
        pstMsgHeader->ucflagField[0] &= 0xFB;
    }

    /*IEEE Std 1588 17.3
      If the port is transmitting a unicast Announce message
    under the terms of this subclause and is in the MASTER state,
    set  the flagField.alternateMasterFlag to FALSE,
    otherwise set the flagField.alternateMasterFlag to TRUE. */
    if ((TCPIP_PTP_MSG_ANNOUNCE == ulPtpMsgType)
        && (TCPIP_PTP_PORT_ROLE_MASTER == pstPtpPort->pstSubPortInfo->ucPtpPortRole)
        && (TCPIP_PTP_CLOCK_UNICAST_MODE == pstPtpPort->pstSubPortInfo->ucCastMode))
    {
        pstMsgHeader->ucflagField[0] &= 0xFE;
    }
    else
    {
        pstMsgHeader->ucflagField[0] |= 0x01;
    }

    /* 第二个字节填充 */
    if (TCPIP_PTP_MSG_ANNOUNCE == ulPtpMsgType)
    {
        pstMsgHeader->ucflagField[1] = 0;
        if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap61)
        {
            pstMsgHeader->ucflagField[1] |= 0x01;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap59)
        {
            pstMsgHeader->ucflagField[1] |= 0x02;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid)
        {
            pstMsgHeader->ucflagField[1] |= 0x04;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->bPtpTimescale)
        {
            pstMsgHeader->ucflagField[1] |= 0x08;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->bTimeTraceable)
        {
            pstMsgHeader->ucflagField[1] |= 0x10;
        }

        if (BOOL_TRUE == g_pstPtpGlobalInfo->bFrequencyTraceable)
        {
            pstMsgHeader->ucflagField[1] |= 0x20;
        }

    }

    return TCPIP_PTP_OK;
}



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
ULONG PTPV2_PktHeaderCheck(PTPV2_PORT_S* pstPtpPort,
                          UCHAR *pucBuffer,
                          ULONG ulPtpMsgType,
                          ULONG ulPacketLen,
                          TCPIP_PTP_ADDRINFO_S* pstAddrInfo)
{
    PTPV2_MSGHEADER_S* pstMsgHeader = NULL;
    ULONG  ulRet = TCPIP_PTP_OK;
    LONG lCmp = -1;

    /* 由于是内部函数，指针不可能为空 */
    VOS_DBGASSERT(NULL != pstPtpPort);
    VOS_DBGASSERT(NULL != pucBuffer);
    VOS_DBGASSERT(NULL != pstAddrInfo);

    if (NULL == g_pstPtpGlobalInfo)
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }
    pstMsgHeader = (PTPV2_MSGHEADER_S *)pucBuffer;

    /*PTP 端口号不能为0和0xffff*/
    if (0 == pstMsgHeader->stSourcePortIdentity.usPortNumber
        || 0xFFFF == pstMsgHeader->stSourcePortIdentity.usPortNumber)
    {
        return TCPIP_PTP_ERR_PORTNO;
    }

    /*对端的Clock Id 不能和本端相同*/
    (VOID)VOS_Mem_Cmp(g_pstPtpGlobalInfo->szClockId,
        pstMsgHeader->stSourcePortIdentity.szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ), &lCmp);
    if (0 == lCmp)
    {
        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorClockIdPackets ++;

        return TCPIP_PTP_ERR_CLOCKID;
    }

    ulRet =  PTPV2_PktGeneralHeaderCheck (pstPtpPort, pstMsgHeader, ulPtpMsgType, ulPacketLen);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    /* 部分需要针对消息类型进行区分，则分开检查 */
    switch (ulPtpMsgType)
    {
        case TCPIP_PTP_MSG_ANNOUNCE:
            ulRet = PTPV2_PktAnnSequenceIdCheck(pstPtpPort, pstMsgHeader, pstAddrInfo);

            break;

        default:
            ulRet = TCPIP_PTP_ERR_MSGTYPE;
            break;

    }

    return ulRet;
}

ULONG PTPV2_BuildAnnPktHeader(PTPV2_PORT_S* pstPtpPort,  PTPV2_MSGHEADER_S* pstMsgHeader)
{
    /* header里记得要将主机序转换成网络序 */
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_PORT_SUB_INFO_S *pstPortSubInfo = NULL;
    ULONG ulPtpV2ClockType = 0;

    /* 由于是内部函数，指针不可能为空 */
    VOS_DBGASSERT(NULL != pstPtpPort);

    pstPortSubInfo = pstPtpPort->pstSubPortInfo;
    VOS_DBGASSERT(NULL != pstPtpPort->pstSubPortInfo);
    if (NULL == pstPortSubInfo)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    ulPtpV2ClockType = PTPV2_GetClockType();

    pstMsgHeader->usSequenceId = VOS_HTONS(pstPortSubInfo->stPortAnnInfo.usSndAnnSequenceId);
    pstPortSubInfo->stPortAnnInfo.usSndAnnSequenceId ++;
    pstMsgHeader->cLogMessageInterval = pstPortSubInfo->stPortAnnInfo.clogAnnounceInterval;

    /* 构造其他报文普通字段 */
    pstMsgHeader->ucversionPTP = PTPV2_VERSION;
    pstMsgHeader->ucdomainNumber = g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber;
    pstMsgHeader->ucControlField = PTPV2_CONTROLFIELD_ALL_OTHER;
    pstMsgHeader->ucmessageType = (UCHAR)TCPIP_PTP_MSG_ANNOUNCE;

    pstMsgHeader->uctransportSpecific = 0;
    (VOID)TCPIP_Mem_Copy(pstMsgHeader->stSourcePortIdentity.szClockId,sizeof(TCPIP_PTP_CLOCK_ID_SZ), g_pstPtpGlobalInfo->szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ));
    pstMsgHeader->stSourcePortIdentity.usPortNumber = VOS_HTONS(pstPortSubInfo->usPortNo);
    if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        (VOID)PTPV2_OCBuildPktFlagfield(pstPtpPort, pstMsgHeader, TCPIP_PTP_MSG_ANNOUNCE);
    }
    else
    {
        (VOID)PTPV2_BCBuildPktFlagfield(pstPtpPort, pstMsgHeader, TCPIP_PTP_MSG_ANNOUNCE);
    }
    return ulRet;

}

ULONG PTPV2_ComputeSeqId(VOID *pThis, MBUF_S *pstMbuf)
{
    return TCPIP_PTP_OK;
}

ULONG PTPV2_OverMacSndAnnPkt(VOID *pThis, VOID *pData, VOID *pAddr)
{
    MBUF_S *pstMbuf = NULL;
    USHORT usEthType = 0;
    ULONG  ulRet = TCPIP_PTP_OK;
    IFNET_S *pstIfnet = NULL;
    ETHARP_ETHERHDR_S *pstEthHdr = NULL;
    PTPV2_PORT_S *pstPortInfo = NULL;
    ULONG ulLength = sizeof(ETHARP_ETHERHDR_S);
    MBUF_S *pstMultiPortMbuf = NULL;
    PTPV2_PORT_S *pstMultiPortInfo = NULL;
    IFNET_S *pstMultiPortIfnet = NULL;
    ULONG ulIter = 0;
    /*用于传入获取报文信息，目前仅传入接口索引信息*/
    TCPIP_PTP_ADDRINFO_S *pstAddrInfo;
    TCPIP_PTP_ADDRINFO_S stMultiPortAddrInfo = {{0}};

    if (NULL == pThis || NULL == pData || NULL == pAddr)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    pstPortInfo = (PTPV2_PORT_S *)pThis;
    pstMbuf = (MBUF_S *)pData;
    pstAddrInfo = (TCPIP_PTP_ADDRINFO_S *)pAddr;

    pstIfnet = IF_GetIfByIndex(pstAddrInfo->ulIfIndex);
    if (NULL == pstIfnet)
    {
        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulSndGetIfDropPackets ++;
        pstPortInfo->stPacketStat.ulSndGetIfDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281B, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OverMacSndAnnPkt fail to get Ifnet!\r\n",
                0, 0, 0, 0);
        
        MBUF_Destroy(pstMbuf);
        
        return TCPIP_PTP_ERR;
    }

    pstMbuf->stDataBlockDescriptor.pucData -= ulLength;
    pstMbuf->stDataBlockDescriptor.ulDataLength += ulLength;
    pstMbuf->ulTotalDataLength += ulLength;
    pstEthHdr = MBUF_MTOD(pstMbuf, ETHARP_ETHERHDR_S*);

    (VOID)TCPIP_Mem_Copy((UCHAR *)pstEthHdr->ucHdrDstMacAddr,PTPV2_MACADDRLEN, pstAddrInfo->stDstPortAddr.unAddr.ucMacAddr, PTPV2_MACADDRLEN);
    (VOID)TCPIP_Mem_Copy((UCHAR *)pstEthHdr->ucHdrSrcMacAddr, PTPV2_MACADDRLEN,pstAddrInfo->stSrcPortAddr.unAddr.ucMacAddr, PTPV2_MACADDRLEN);

    usEthType = PTPV2_IEEE8023_ETHTYPE;
    pstEthHdr->usHdrType = VOS_HTONS(usEthType);

    /*OC master下，对于所有的物理接口都复制一份报文进行发送*/
    if (PTPV2_CLOCK_TYPE_OC == g_ulPtpV2ClockType)
    {
        (VOID)TCPIP_Mem_Copy((VOID *)&stMultiPortAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S), 
                             (VOID *)pstAddrInfo, sizeof(TCPIP_PTP_ADDRINFO_S));
        
        for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
        {
            pstMultiPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);
            if (NULL == pstMultiPortInfo)
            {
                continue;
            }

            pstMultiPortIfnet = IF_GetIfByIndex(pstMultiPortInfo->ulIfIndex);
            /* 将报文复制并通过所有已配置的接口进行发送 */
            /* 为避免重复发送，此时需排除掉原本的发送接口 */
            if (pstIfnet != pstMultiPortIfnet && NULL != pstMultiPortIfnet)
            {
                pstMultiPortMbuf = MBUF_RawCopy(pstMbuf, 0, pstMbuf->ulTotalDataLength,
                                            0, PTPV2_MID);
                if (NULL == pstMultiPortMbuf)
                {
                    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281C, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                                     "TCPIP PTPV2 LOG:PTPV2_OverMacSndAnnPkt Create mbuf fail!\n",0,0,0,0);
                }
                else
                {
                    UCHAR ucSrcMacAddr[PTPV2_MACADDRLEN] = {0};
                    /* 将出接口索引填入MBuf的使用者数据 */
                    MBUF_ASSIGN_SEND_IFNET_INDEX(pstMultiPortMbuf, pstMultiPortInfo->ulIfIndex);

                    /*Added by wuling201943,  , 2014/11/11   问题单号:DTS2014111107372 */
                    /*根据和产品讨论新方案,针对不同的接口填写不同的源MAC
                                当本端MASTER 多个物理接口给对端slave发送报文，导致slave获取的master
                                源physical地址相同，下发给底软时钟组不能基于源MAC过滤*/
                    pstEthHdr = MBUF_MTOD(pstMultiPortMbuf, ETHARP_ETHERHDR_S*);
                    (VOID)TCPIP_GetEtharpMac(pstMultiPortInfo->ulIfIndex, ucSrcMacAddr);
                    (VOID)TCPIP_Mem_Copy((UCHAR *)pstEthHdr->ucHdrSrcMacAddr, PTPV2_MACADDRLEN, ucSrcMacAddr, PTPV2_MACADDRLEN);
                    /* End of Added by wuling201943, 2014/11/11   问题单号:DTS2014111107372 */
                    
                    /*Add by wuling 2014-10-25 for DTS2014101506144  报文追踪对应每一个物理接口*/
                    {
                        /*Begin Mod by wuing 00201943 for DTS2014101506444 on 2014-10-27, 获取报文从PTP报文开始*/
                        ULONG ulPtpPktLen = pstMultiPortMbuf->ulTotalDataLength - ulLength;
                        UCHAR *pucPtpPkt  = MBUF_MTOD(pstMultiPortMbuf, UCHAR*);
                        
                        pucPtpPkt += ulLength;
                        /*传给回调函数的源地址信息要更新成发送端口的MAC*/
                        stMultiPortAddrInfo.ulIfIndex = pstMultiPortInfo->ulIfIndex;
                        (VOID)TCPIP_Mem_Copy((VOID *)(stMultiPortAddrInfo.stSrcPortAddr.unAddr.ucMacAddr), PTPV2_MACADDRLEN,
                                             (VOID *)ucSrcMacAddr, PTPV2_MACADDRLEN);
                        if (NULL != g_pfPtpV2CapturePktFunc)
                        {
                            /*modified by wuling for DTS2014102506961 传入接口对应的ptp实际端口号 2014-11-19 --start*/
                            (VOID)g_pfPtpV2CapturePktFunc(TCPIP_PTP_PKT_OUT, pucPtpPkt, 
                                    ulPtpPktLen, &stMultiPortAddrInfo, pstMultiPortInfo->pstSubPortInfo->usPortNo);
                        }
                    }
                    /*End of adding*/

                    /* 将报文交至链路层发送 */
                    ulRet = pstMultiPortIfnet->if_pfQosTransmit(pstMultiPortIfnet, pstMultiPortIfnet->if_ulPhyLink, pstMultiPortMbuf);
                    if (TCPIP_PTP_OK != ulRet)
                    {
                        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281D, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                                "TCPIP PTPV2 LOG: PTPV2_OverMacSndAnnPkt multi port QosTransmit fail! Ret = %u!\r\n",
                                ulRet, 0, 0, 0);
                    }
                }
            }
        }
    }

    /*Add by wuling 2014-10-25 for DTS2014101506144 报文追踪对应每一个物理接*/
    {
        /*Begin Mod by wuling 00201943 for DTS2014101506444 on 2014-10-27, 获取报文从PTP报文开始*/
        ULONG ulPtpPktLen = pstMbuf->ulTotalDataLength - ulLength;
        UCHAR *pucPtpPkt  = MBUF_MTOD(pstMbuf, UCHAR*);

        pucPtpPkt += ulLength;        
        if (NULL != g_pfPtpV2CapturePktFunc)
        {
            /*modified by wuling for DTS2014102506961 传入接口对应的ptp实际端口号 2014-11-19 --start*/
            (VOID)g_pfPtpV2CapturePktFunc(TCPIP_PTP_PKT_OUT, pucPtpPkt, 
                        ulPtpPktLen, pstAddrInfo, pstPortInfo->pstSubPortInfo->usPortNo);
        }
    }
    /*End of adding*/

    ulRet = pstIfnet->if_pfQosTransmit(pstIfnet, pstIfnet->if_ulPhyLink, pstMbuf);
    if (TCPIP_PTP_OK != ulRet)
    {
        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulSndDropPackets ++;
        pstPortInfo->stPacketStat.ulSndDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281E, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OverMacSndAnnPkt QosTransmit fail! Ret = %u!\r\n",
                ulRet, 0, 0, 0);
    }

    return ulRet;
}
/******************************************************************************
*Func Name   : PTPV2_PrintHeader
*Description : 报文头打印接口
*Input       : PTP_MSGHEADER_S *pstMsgHeader 消息头
*              PTP_ADDRINFO_S  *pstAddrInfo  接收/发送报文的地址以及UDP信息
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-05-14           dutianyi       Create
*******************************************************************************/
VOID PTPV2_PrintHeader(PTPV2_MSGHEADER_S *pstMsgHeader, TCPIP_PTP_ADDRINFO_S *pstAddrInfo)
{

    CHAR szBuf[1024] = {0};  /* 缓冲区长度512个字节，存放报文信息 */
    //CHAR szDstAddr[256] = {0}; /* 缓冲区长度32个字节，缓存目的地址字符串 */
    //CHAR szSrcAddr[256] = {0}; /* 缓冲区长度32个字节，缓存源地址字符串 */
    /* 时间调试信息*/
    ULONG ulSysDate = 0; 
    ULONG ulSysTime = 0;
    ULONG ulSysMillSec = 0;
    ULONG ulHour = 0;
    ULONG ulMinute = 0;
    ULONG ulSecond = 0;
    CHAR *szMsgtype[]  = {
                          "PTPV2_MSG_SYNC",
                          "PTPV2_MSG_DELAY_REQ",
                          "PTPV2_MSG_PDELAY_REQ",
                          "PTPV2_MSG_PDELAY_RESP",
                          "",
                          "",
                          "",
                          "PTPV2_MSG_LIVE",
                          "PTPV2_MSG_FOLLOW_UP",
                          "PTPV2_MSG_DELAY_RESP",
                          "PTPV2_MSG_PDELAY_RESP_FOLLOW_UP",
                          "PTPV2_MSG_ANNOUNCE",
                          "PTPV2_MSG_SIGNALING",
                          "PTPV2_MSG_MANAGEMENT",
                          "PTPV2_MSG_HANDSHAKE_REQ",
                          "PTPV2_MSG_HANDSHAKE_RESP"
                          };
    INT32 i32Offset = 0;

    if ((NULL == pstMsgHeader)
        || (NULL == pstAddrInfo))
    {
        return ;
    }
    
    if ((pstAddrInfo->stDstPortAddr.usNetworkProtocol < TCPIP_PTP_PROTOCAL_UDP_IPV4)
        || (pstAddrInfo->stDstPortAddr.usNetworkProtocol > TCPIP_PTP_PROTOCAL_IEEE_802)
        || (pstAddrInfo->stSrcPortAddr.usNetworkProtocol < TCPIP_PTP_PROTOCAL_UDP_IPV4)
        || (pstAddrInfo->stSrcPortAddr.usNetworkProtocol > TCPIP_PTP_PROTOCAL_IEEE_802))
    {
        return;
    }
    
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

    /* 获取当前时间 */
    if (VOS_OK == VOS_SYS_GetCurrentTime(&ulSysDate, &ulSysTime, &ulSysMillSec))
    {
        /*
        -------------------------------------------------------
        |  Hours(16 bits) | Minutes(8 bits) | Seconds(8 bits) |
        -------------------------------------------------------
        */       
        ulHour   = (ulSysTime >> 16) & 0xFFFF;
        ulMinute = (ulSysTime >> 8) & 0xFF;
        ulSecond = ulSysTime & 0xFF;
    }

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_1024, P4("\r\nPTPV2 PKT DEBUG [%02u:%02u:%02u %3u]:", ulHour, ulMinute, ulSecond, ulSysMillSec));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P1("\r\nIfIndex:%u", pstAddrInfo->ulIfIndex));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P0("\r\nHEADER INFO:"));
    
    /*Flag Field needs to be printed in Hex with the nibbles getting printed properly.
    For eg 0400 should get printed as 0x0400 and not 40*/
    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P9("\r\n    transportspecific : %u\r\n    messageType : %u (%s)\r\n    version : %u\r\n    length : %u\r\n    flagfield : 0x%02x%02x\r\n    correctionfield : %x%x",
                              pstMsgHeader->uctransportSpecific,
                              pstMsgHeader->ucmessageType,
                              szMsgtype[pstMsgHeader->ucmessageType],
                              pstMsgHeader->ucversionPTP,
                              VOS_NTOHS(pstMsgHeader->usmessageLength),
                              pstMsgHeader->ucflagField[0],
                              pstMsgHeader->ucflagField[1],
                              pstMsgHeader->uulcorrectionField.hi,
                              pstMsgHeader->uulcorrectionField.lo));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P8("\r\n    source clock id : %02x%02x%02x%02x%02x%02x%02x%02x ",
                              pstMsgHeader->stSourcePortIdentity.szClockId[0],
                              pstMsgHeader->stSourcePortIdentity.szClockId[1],
                              pstMsgHeader->stSourcePortIdentity.szClockId[2],
                              pstMsgHeader->stSourcePortIdentity.szClockId[3],
                              pstMsgHeader->stSourcePortIdentity.szClockId[4],
                              pstMsgHeader->stSourcePortIdentity.szClockId[5],
                              pstMsgHeader->stSourcePortIdentity.szClockId[6],
                              pstMsgHeader->stSourcePortIdentity.szClockId[7]));
    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_1024 - i32Offset, P4("\r\n    source port number : %u\r\n    sequenceId : %u\r\n    controlfield : %u\r\n    logmessageinterval : %d",
                              VOS_NTOHS(pstMsgHeader->stSourcePortIdentity.usPortNumber),
                              VOS_NTOHS(pstMsgHeader->usSequenceId),
                              pstMsgHeader->ucControlField,
                              pstMsgHeader->cLogMessageInterval));

   
    TCPIP_InfoOutput(szBuf);

    return;

}

ULONG PTPV2_GrandMasterIDCheck(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg)
{
    LONG lCmp = -1L;

    if (NULL == pstAnnMsg)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    (VOID)VOS_Mem_Cmp((VOID*)g_pstPtpGlobalInfo->szClockId,(VOID*)pstAnnMsg->stGrandmasterIdentity,sizeof(TCPIP_PTP_CLOCK_ID_SZ),&lCmp);
    if (0 == lCmp)
    {
        return TCPIP_PTP_ERR;
    }
    
    return TCPIP_PTP_OK;
}

ULONG PTPV2_BuildAnnPktClockQa(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_CLOCK_QA_S* pstClockQA)
{
    if ((NULL == pstAnnMsg) || (NULL == pstClockQA))
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }
    
    (VOID)TCPIP_Mem_Copy((VOID *)&(pstAnnMsg->stGrandmasterClockQuality), sizeof(TCPIP_PTP_CLOCK_QA_S),
                                    (VOID *)pstClockQA, sizeof(TCPIP_PTP_CLOCK_QA_S));
     
    pstAnnMsg->stGrandmasterClockQuality.usOffsetScaledLogVariance =
         VOS_HTONS(pstClockQA->usOffsetScaledLogVariance);

    return TCPIP_PTP_OK;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
