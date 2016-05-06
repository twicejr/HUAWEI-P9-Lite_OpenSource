#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv6_def.h"
#include "dhcpc_comp.h"
#include "dhcpc.h"
#include "dhcpc_dbg.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6C_C
/*lint +e767*/

DHCPC_EMS_INFO_S g_stDhcpcEmsInfo[DHCPV6C_CAUSE_BUFF] =
{
    /* NULL */
    {
        0,
        "N/A.",
        "N/A."
    },

    /* 租约到期 */
    {
        EMS_CODE_DHCPV6C_LEASE_EXPIRE,
        "Lease of DHCPv6 server-assigned IP addresses expired.",
        "Check the DHCPv6 server status and the status of the link between the UGW9811 and the DHCPv6 server."
    },

    /* DHCPv6服务器无响应 */
    {
        EMS_CODE_DHCPV6C_SERVER_NO_RSP,
        "No response from the DHCP server.",
        "Check the DHCPv6 server status and the status of the link between the UGW9811 and the DHCPv6 server."
    },

    /* DHCPv6服务器消息异常 */
    {
        EMS_CODE_DHCPV6C_SERVER_MSG_EXCEPTION,
        "Abnormal messages sent by the DHCPv6 server.",
        "Check whether the DHCPv6 server is functioning properly and whether the messages sent by the DHCPv6 server are correct."
    },

    /* DHCPv6服务器无地址可用 */
    {
        EMS_CODE_DHCPV6C_SERVER_NO_AVAILABLE_ADDR,
        "No available IP addresses for the DHCPv6 server.",
        "Check whether the DHCPv6 server has sufficient available IP addresses."
    },

    /* DHCPV6C Transaction Id耗尽 */
    {
        EMS_CODE_DHCPV6C_TID_EXHAUST,
        "DHCPv6 transaction IDs exhausted.",
        "Check whether the subscriber activation rate is at a peak and whether the link between the UGW9811 and the DHCPv6 server is functioning properly."
    }
};

ULONG DHCPC_PickUpDhcp(UDPS_PACKET_INFO_S * pstUdp, PMBUF_S *pstMbuf)
{
    UCHAR ucIpUdpHeadLen = IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    if (pstMbuf->stDataBlockDescriptor.ulDataLength <= ucIpUdpHeadLen)
    {
        return VOS_ERR;
    }

    pstMbuf->stDataBlockDescriptor.pucData      += ucIpUdpHeadLen;
    pstMbuf->stDataBlockDescriptor.ulDataLength -= ucIpUdpHeadLen;
    pstMbuf->ulTotalDataLength                  -= ucIpUdpHeadLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPC_UnpackDhcpMsgFromMbuf
 功能描述  : 从SD分发的Mbuf中解封装Dhcp信令消息
 输入参数  : PMBUF_S *pstMsgBuf
             UCHAR ucDhcpMsgType
             UCHAR **ppucDhcpMsg
             ULONG *pulMsgLen
             ULONG *pulServerIp
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月11日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_UnpackDhcpMsgFromMbuf(PMBUF_S *pstMsgBuf, UDPS_PACKET_INFO_S *pstPtkInf,
                                    UCHAR **ppucDhcpMsg, ULONG *pulMsgLen)
{
    ULONG ulRet = VOS_ERR;
    ULONG ulMsgLen = 0;

#if 0

    ulRet = (ULONG)UDPS_PickUpExt( pstPtkInf, pstMsgBuf );
    if ( VOS_OK != ulRet )
    {
        DHCPC_DebugPrint(PTM_LOG_WARNING, "call UDPS_PickUpExt fail! ulRet=%u", ulRet);
        return ulRet;
    }
#endif

    ulRet = DHCPC_PickUpDhcp(pstPtkInf, pstMsgBuf);
    if ( VOS_OK != ulRet )
    {
        DHCPC_DebugPrint(PTM_LOG_WARNING, "call DHCPC_PickUpDhcp fail! ulRet=%u", ulRet);
        return ulRet;
    }

    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (ulMsgLen > DHCP_PKT_ASSUME_MAX_LEN)
    {
        DHCPC_DebugPrint(PTM_LOG_WARNING, "receive malformed Packet. length=%u", ulMsgLen);
        return VOS_ERR;
    }

    /* 检查Mbuf是否对消息进行了分片 */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        /* 没有分片 */
        *ppucDhcpMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        PGP_MemZero(g_pucDhcpPktBuf, sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN);
        ulRet = PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf,
                                            0,
                                            ulMsgLen,
                                            g_pucDhcpPktBuf);
        if (VOS_OK != ulRet)
        {
            DHCPC_DebugPrint(PTM_LOG_WARNING,
                "call PMBUF_CopyDataFromPMBufToBuffer fail. ulRet=%u", ulRet);
            return VOS_ERR;
        }

        *ppucDhcpMsg = g_pucDhcpPktBuf;
    }

    *pulMsgLen = ulMsgLen;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_ProcDhcpMsg
 功能描述  : 处理dhcpv6 server发送的dhcp消息
 输入参数  : UCHAR *pucDhcpv6Msg
             ULONG ulMsgLen
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月12日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPV6C_ProcDhcpMsg(UCHAR *pucDhcpv6Msg, UCHAR ucMsgType, ULONG ulMsgLen , ULONG *pulSrvIpAddr)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_MSG_INFO_S stMsgInfo = {0};
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPC_FUNC_ENTRY();

    stMsgInfo.pucMsg = pucDhcpv6Msg;
    stMsgInfo.ulMsgLen = ulMsgLen;

    /* 根据消息获取teidc,SequnceNum */
    DHCPV6C_GetSeqNumByMsg(&(stMsgInfo.usSeqNum), stMsgInfo.pucMsg);

    /* 查找dhcp控制块 */
    ulReturn = DHCPV6C_QueryDhcpBlockBySeq(stMsgInfo.usSeqNum, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {
            DHCPC_OmVIfMsgTrc((ULONG)(ucMsgType),
                                TRC_DIRECTION_DHCPV6_IN_GGSN,
                                pucDhcpv6Msg,
                                (USHORT)ulMsgLen,
                                LAP_IPV6,
                                pulSrvIpAddr);
        }
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "Dhcpcontext not exist!");
        return ulReturn;
    }

    /* 消息跟踪 */
    DHCPCv6_OmMsgTrc(pucDhcpv6Msg, pstDhcpcContext, ucMsgType, ulMsgLen, DHCPV6_MSG_DIRECTION_RECEIVE);

    ulReturn = DHCPV6C_MsgDecode(&stMsgInfo);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6C_MsgDecode fail!");
        return ulReturn;
    }

    DHCPC_UpdateServerGroupStatusNormal(pstDhcpcContext->usServerGrpIndex, pstDhcpcContext->ucCurrentServer);

    /* 设置原因值为缺省 */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.pMsg = &(stMsgInfo.stDhcpv6cOptionInfo);
    stPreResult.ucDhcpServerMsg = ucMsgType;

    ulReturn = DHCPV6C_CheckOption(&(stMsgInfo.stDhcpv6cOptionInfo), pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n call DHCPV6C_CheckOption fail!");
        if (DHCPC_RET_DROP_MSG == ulReturn)
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n [dhcpv6c err:]drop msg!");
            return ulReturn;
        }
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
        stPreResult.enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    }
    else
    {
        ulReturn = DHCPV6C_FSM_PreProc_ServerMsg(&(stPreResult));
        if (DHCPC_RET_DROP_MSG == ulReturn)
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n [dhcpv6c err:]drop msg!");
            return ulReturn;
        }
    }

    /* 认为收到了配对的消息,将该控制块累计发送单条消息数清0 */
    pstDhcpcContext->ucCurSvrSendCount = 0;
    pstDhcpcContext->ucTotalSendCount = 0;

    DHCPV6C_RunFsm(&stPreResult);
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckServerMsgType
 *  初稿完成:       2012-07-19
 *  作    者:       y00170683
 *  函数功能:       检查收到的消息类型
 *  输入参数:       ucMsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckServerMsgType(UCHAR ucMsgType)
{
    ULONG ulRet = VOS_OK;

    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_ADVERTISE :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_ADVERTISE_MSG);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_REPLY_MSG);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_SERVER_OTHER_MSG);
            ulRet = VOS_ERR;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_ProcMbufMsg
 功能描述  : 处理以Mbuf封装的dhcpv6信令消息
 输入参数  : PMBUF_S *pstMsgBuf
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月11日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV6C_ProcMbufMsg(PMBUF_S *pstMsgBuf)
{
    UCHAR   ucMsgType = 0;
    ULONG   ulReturn = VOS_ERR;
    UCHAR   ucLogicSlot = 0;
    UCHAR   *pucDhcpv6Msg = NULL;
    ULONG   ulMsgLen = 0;
    ULONG   aulSrvIp[4] = {0};
    UDPS_PACKET_INFO_S stPtkInf = {0};

    DHCPC_FUNC_ENTRY();

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "not active board!");
        return;
    }

    ulReturn = DHCPC_UnpackDhcpMsgFromMbuf(pstMsgBuf, &stPtkInf, &pucDhcpv6Msg, &ulMsgLen);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_UNPACKET_FAIL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPC_UnpackDhcpMsgFromMbuf fail!");
        return;
    }

    /* 统计收V6-SERVER消息计数 只处理advertise和reply消息 */
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_SERVER_MSG);
    ucMsgType = DHCPV6C_GET_MSG_TYPE(pucDhcpv6Msg);
    ulReturn = DHCPV6C_CheckServerMsgType(ucMsgType);
    if (VOS_OK != ulReturn)
    {
        return;
    }

    VOS_MemCpy(&(stPtkInf.uaddrSrc.stAddr6Src.stSin6_addr), aulSrvIp, 4*sizeof(ULONG));
    ulReturn = DHCPV6C_ProcDhcpMsg(pucDhcpv6Msg, ucMsgType, ulMsgLen, aulSrvIp);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n call DHCPV6C_ProcDhcpMsg fail!");
    }
    return;
}

/*****************************************************************************
 函 数 名  : DHCPV6C_ProcSDMsg
 功能描述  : 处理SD分发的dhcpv6消息
 输入参数  : UCHAR *pucMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月11日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV6C_ProcSDMsg(UCHAR *pucMsg)
{
    PMBUF_S *pstMsgBuf = NULL;

    pstMsgBuf = *((PMBUF_S **)pucMsg);
    if ( NULL == pstMsgBuf )
    {
        VOS_Assert(0);
        return;
    }

    DHCPV6C_ProcMbufMsg(pstMsgBuf);

    (VOS_VOID)PMBUF_Destroy(pstMsgBuf);
    *((PMBUF_S **)pucMsg) = NULL;

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPC_CalcSuccSendLapNum
 *  初稿完成:       2012-07-19
 *  作    者:       y00170683
 *  函数功能:       统计通知LAP成功计数
 *  输入参数:       ucMsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPC_CalcSuccSendLapNum(UCHAR ucMsgType)
{
    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SUCCESS_OK);
            break;

        case DHCPC_SND2_LAP2_ADDR_FAILED_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_FAIL_OK);
            break;

        case DHCPC_SND2_LAP2_ADDR_REL_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_REL_OK);
            break;

        case DHCPC_SND2_LAP2_NO_RSP_MSG:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SVR_NO_RSP_OK);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_OTHER_OK);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPC_CalcFailSendLapNum
 *  初稿完成:       2012-07-19
 *  作    者:       y00170683
 *  函数功能:       统计通知LAP失败计数
 *  输入参数:       ucMsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPC_CalcFailSendLapNum(UCHAR ucMsgType)
{
    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SUCCESS_ERR);
            break;

        case DHCPC_SND2_LAP2_ADDR_FAILED_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_FAIL_ERR);
            break;

        case DHCPC_SND2_LAP2_ADDR_REL_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_REL_ERR);
            break;

        case DHCPC_SND2_LAP2_NO_RSP_MSG:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SVR_NO_RSP_ERR);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_OTHER_ERR);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_SendMsgToLAP2ByContext
 功能描述  : 根据控制块内容向LAP2发送消息
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
             UCHAR MsgType
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月12日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_SendMsgToLAP2ByContext(DHCPC_CTRLBLK *pstDhcpcContext, UCHAR MsgType)
{
    ULONG ulReturn = VOS_ERR;
    LAP2_DHCPC_MSG_S stLapDhcpcMsg = {0};

    DHCPC_FUNC_ENTRY();

    /* 填充消息内容 */
    stLapDhcpcMsg.usVpnId = pstDhcpcContext->usVPNIndex;
    VOS_MemCpy(stLapDhcpcMsg.aulPdpAddr, pstDhcpcContext->aulUserIpAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    stLapDhcpcMsg.ucAddressType = pstDhcpcContext->ucIpType;
    stLapDhcpcMsg.usPoolIndex = pstDhcpcContext->usPoolIndex;
    stLapDhcpcMsg.ucSCID = PSM_Inf_GetCmpSameTIndexInSGByCSI(DHCPC_SELF_CSI);
    VOS_MemCpy(stLapDhcpcMsg.aulAgentIP, pstDhcpcContext->aulAgentIpAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    stLapDhcpcMsg.ulIndex = pstDhcpcContext->ulPDPIndex;
    stLapDhcpcMsg.usDhcpGroupIndex = pstDhcpcContext->usServerGrpIndex;
    stLapDhcpcMsg.ucMsgType = MsgType;
    stLapDhcpcMsg.usApnIndex = pstDhcpcContext->usApnIndex;
    VOS_MemCpy(stLapDhcpcMsg.aulPrimaryDNS, pstDhcpcContext->aulMainDnsAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    VOS_MemCpy(stLapDhcpcMsg.aulSecondaryDNS, pstDhcpcContext->aulSecdDnsAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    stLapDhcpcMsg.ucUserType = pstDhcpcContext->ucUserType;
    stLapDhcpcMsg.ucGtpVer = pstDhcpcContext->ucUser;
    stLapDhcpcMsg.ulTeidc = pstDhcpcContext->ulTEIDC;
    stLapDhcpcMsg.ucStaticIpRouteType = 0;
    stLapDhcpcMsg.aulMSISDN[0] = pstDhcpcContext->aulMSISDN[0];
    stLapDhcpcMsg.aulMSISDN[1] = pstDhcpcContext->aulMSISDN[1];
    stLapDhcpcMsg.ucLAPNo = pstDhcpcContext->ucLAPNo;

    DHCPC_PRINT_LAP_MSG(&stLapDhcpcMsg);

    ulReturn = DHCPC_SendAddrMsgToLAP(&stLapDhcpcMsg,
                                           sizeof(LAP2_DHCPC_MSG_S),
                                           pstDhcpcContext->aulUserIpAddr[2],    // TODO:临时处理
                                           pstDhcpcContext->ucLAPNo);
    /* 统计发消息计数 */
    if (VOS_OK == ulReturn)
    {
        DHCPC_CalcSuccSendLapNum(MsgType);
    }
    else
    {
        DHCPC_CalcFailSendLapNum(MsgType);
    }
    return ulReturn;
}

/*****************************************************************************
 函 数 名  : DHCPC_EmsReportAndCleanCause
 功能描述  : 上报EMS消息,并清除原因值字段
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_EmsReportAndCleanCause(DHCPC_CTRLBLK *pstDhcpcContext)
{
    UCHAR ucCause = 0;
    DHCPC_EMS_INFO_S *pstEmsInfo = NULL;
    SDB_GSPU_CONTEXT_S * pstContext = NULL;

    if (NULL == pstDhcpcContext)
    {
        VOS_Assert(0);
        return;
    }
    ucCause = pstDhcpcContext->ucCause;

    if ((ucCause > DHCPV6C_CAUSE_DEFAULT) && (ucCause < DHCPV6C_CAUSE_BUFF))
    {
        pstContext = DHCPC_GetOneContextByteidc(pstDhcpcContext->ulTEIDC);
        if (NULL == pstContext)
        {
            return;
        }

        pstEmsInfo = &g_stDhcpcEmsInfo[ucCause];

        EMS_DebugTrace(pstContext->ulGspuBdIndex, EMS_MODULE_TYPE_AM_DHCP,
                        pstEmsInfo->usMsgCode,pstEmsInfo->aucReason, pstEmsInfo->aucsuggestion);
    }

    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;
    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_NotifyLapFail
 功能描述  : 通知LAP分配地址失败
 输入参数  : DHCPC_CTRLBLK *pstDhcpcContext
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_NotifyLapFail(DHCPC_CTRLBLK *pstDhcpcContext)
{
    UCHAR ucMsgType = 0;
    ULONG ulReturn = 0;

    DHCPC_FUNC_ENTRY();

    if (NULL == pstDhcpcContext)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n Cause=%u", pstDhcpcContext->ucCause);

    if (DHCPV6C_CAUSE_SERVER_NOT_RSP == pstDhcpcContext->ucCause)
    {
        ucMsgType = DHCPC_SND2_LAP2_NO_RSP_MSG;
    }
    else
    {
        ucMsgType = DHCPC_SND2_LAP2_ADDR_FAILED_MSG;
    }

    DHCPC_EmsReportAndCleanCause(pstDhcpcContext);

    ulReturn = DHCPC_SendMsgToLAP2ByContext(pstDhcpcContext, ucMsgType);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}

/*****************************************************************************
 函 数 名  : DHCPCv6_Get_MsgDirection
 功能描述  : dhcpv6消息收或者发送
 输入参数  : UCHAR MsgDirection

 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : linyufeng 00176669
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPCv6_Get_MsgDirection(UCHAR MsgDirection,UCHAR ucUgwRole)
{
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_SGW;

    if ( DHCPV6_MSG_DIRECTION_RECEIVE ==  MsgDirection )
    {
        if ( E_NET_ELEMENT_ROLE_PGW == ucUgwRole )
        {
            ulDirection = TRC_DIRECTION_DHCPV6_IN_PGW;
        }
        else if(E_NET_ELEMENT_ROLE_GGSN == ucUgwRole)
        {
            ulDirection = TRC_DIRECTION_DHCPV6_IN_GGSN;
        }
        else
        {
            ulDirection = TRC_DIRECTION_DHCPV6_IN_SGW;
        }
    }
    else
    {
        if ( E_NET_ELEMENT_ROLE_PGW == ucUgwRole )
        {
            ulDirection = TRC_DIRECTION_DHCPV6_OUT_PGW;
        }
        else if(E_NET_ELEMENT_ROLE_GGSN == ucUgwRole)
        {
            ulDirection = TRC_DIRECTION_DHCPV6_OUT_GGSN;
        }
        else
        {
            ulDirection = TRC_DIRECTION_DHCPV6_OUT_SGW;
        }
    }

    return ulDirection;

}

