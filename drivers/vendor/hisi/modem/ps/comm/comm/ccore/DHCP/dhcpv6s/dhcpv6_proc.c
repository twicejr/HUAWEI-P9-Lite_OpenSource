/*************************************************************************************
*
*                       dhcpv6_proc.c
*
*  项目代码：           UGW9811 V900R010C00
*  创建日期：           2012-07-31
*  作者：               y00170683
*  修改历史列表：
*  参考文档：
*  功能：               DHCPV6S模块消息处理
*  其他：
*
*-----------------------------------------------------------------------------------
*
*  Copyright  Beijing Institute HuaWei Tech, Inc.
*                     ALL RIGHTS RESERVED
*
*************************************************************************************/

/********************************************************************************/
/******************                  头文件引用               *******************/
/********************************************************************************/
#include "dhcp_inc.h"

#include "dhcpc_def.h"

#if 0
#include "ipv6_api.h"
#include "ipv6.h"
#endif

#include "dhcpv6_def.h"
#include "dhcpv6_proc.h"
#include "dhcpv6s_comp.h"
#include "dhcpv6s_dbg.h"
#if 0
#include "gtp.h"
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6_PROC_C
/*lint +e767*/



/********************************************************************************/
/******************                  宏定义                 *******************/
/********************************************************************************/


/********************************************************************************/
/******************                  全局变量                 *******************/
/********************************************************************************/
extern ULONG g_ulGreProType;
extern in6_addr in6addr_ggsn;
DHCPV6_STAT_S  g_stDhcpv6Statistics = {0};         /*  IPv6报文统计 */

UCHAR* g_pucDhcpv6sSendBuff = VOS_NULL;        /*发送消息缓存*/
UCHAR* g_pucDhcpv6sRevBuff = VOS_NULL;        /*接收消息缓存*/


/********************************************************************************/
/******************                  内部接口                 *******************/
/********************************************************************************/
#define __MSG_TRC__
/*****************************************************************************
 *  函数名称:       DHCPV6_ProMsgInterfaceTrc
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       上报接口跟踪
 *  输入参数:       UCHAR *pucMsg,USHORT usMsgLen,UCHAR ucMsgType,
                    ULONG ulDirection,RM_SOCKET_PATH_S *pstPath
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_MsgInterfaceTrc(UCHAR *pucMsg, USHORT usMsgLen, ULONG ulMsgType,
                                       ULONG ulDirection, RM_SOCKET_PATH_S *pstPath)
{
    ULONG ulMsgClass = 0;
    E_TRACE_TYPE enTraceType = TRC_TYPE_BUTT;
    E_TRACE_TYPE enExtTraceType = TRC_TYPE_BUTT;
    UGW_EXTERN_INTF_TRACE_S stTraceInfo = {0};

    if((NULL == pucMsg) || (NULL == pstPath))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_TRC_NULL);
        return;
    }

    /* 确定跟踪类型 */
    DHCPV6S_GET_TRCTYPE_BY_DIR(ulDirection, enTraceType, enExtTraceType, ulMsgClass);
    if ((TRC_TYPE_BUTT == enTraceType) && (TRC_TYPE_BUTT == enExtTraceType))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_TRC_TYPE_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulDirection = %u", ulDirection);
        return;
    }

    /* 内部跟踪 */
    UGW_OmAccessMsgTrc(pucMsg,
                        enTraceType,
                        ulMsgClass,
                        (ulMsgType + ulDirection),
                        pstPath->ulPeerAddr,
                        usMsgLen);

    /* 外部跟踪 */
    stTraceInfo.ulMsgClass      = ulMsgClass;
    stTraceInfo.ulGtpMsgType    = ulMsgType + ulDirection;
    stTraceInfo.ulLocalIpAddr   = pstPath->ulLocalAddr;
    stTraceInfo.ulVpnIndex      = pstPath->ulVrfIndex;
    stTraceInfo.ulPeerIpAddr    = pstPath->ulPeerAddr;
    stTraceInfo.usApnIndex      = pstPath->usApnIndex;
    stTraceInfo.ucAliaApnFlag   = pstPath->ucAliaApnFlag;
    stTraceInfo.ulMsgLen        = (ULONG)usMsgLen;
    GTPC_OmExternInterfaceTrcProcess(pucMsg, enExtTraceType, stTraceInfo);

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_MsgTraceProc
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       上报消息跟踪
 *  输入参数:       DHCPV6_MSG_S *pDhcpv6Msg,
                    ULONG ulMsgLen,
                    SDB_GSPU_CONTEXT_S *pstContext,
                    UDPHDR_S * pstUdp,
                    ULONG ulTrcDir
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_MsgTraceProc(DHCPV6_MSG_S *pDhcpv6Msg,
                                     ULONG ulMsgLen,
                                     SDB_GSPU_CONTEXT_S *pstContext,
                                     UDPHDR_S *pstUdp,
                                     ULONG ulEmsTrcDir)
{
    RM_SOCKET_PATH_S stPath = {0};
    S_OM_EMS_TRC_PARA stTrcPara = {0};
    UCHAR ucMsgType = pDhcpv6Msg->ucMsgType;
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_PGW;

    /* 确定消息跟踪的方向 */
    DHCPV6S_GET_TRCDIR_BY_ROLE(pstContext->ucUgwRole, ulEmsTrcDir, ulDirection);

    /* 确定源目的地址,端口号 */
    stPath.ulLocalAddr = pstContext->ulS5_Gn_LocDataIP;
    stPath.ulPeerAddr  = pstContext->ulS5_Gn_PeerDataIP;
    if ((E_NET_ELEMENT_ROLE_PGW != pstContext->ucUgwRole)
        && (E_NET_ELEMENT_ROLE_GGSN != pstContext->ucUgwRole))
    {
        stPath.ulLocalAddr = pstContext->ulSgwLeftLocDataIP;
        stPath.ulPeerAddr  = pstContext->ulSgwLeftPeerDataIP;
    }
    /* 获取VPN-id */
    Path_GetVpn(pstContext, &(stPath.ulVrfIndex));

    stPath.usLocalPort = VOS_NTOHS(pstUdp->uh_usSPort);
    stPath.usPeerPort  = VOS_NTOHS(pstUdp->uh_usDPort);

    AM_CtxApiGetReqApnIndexByPdpContext(pstContext, &(stPath.usApnIndex), &(stPath.ucAliaApnFlag));

    if (M_EMS_TRC_RECV_MSG == ulEmsTrcDir)
    {
        stPath.usLocalPort = VOS_NTOHS(pstUdp->uh_usDPort);
        stPath.usPeerPort  = VOS_NTOHS(pstUdp->uh_usSPort);
    }

    /* 接口跟踪 */
    DHCPV6_MsgInterfaceTrc((UCHAR*)pDhcpv6Msg, (USHORT)ulMsgLen, (ULONG)ucMsgType, ulDirection, &stPath);

    /* 用户跟踪 DTS2012091903437 y00170683 */
    UGW_OmUsrMsgTrace((UCHAR *)pDhcpv6Msg,
                        GUSER_MSGTYPE_DHCPV6,
                        (ULONG)ucMsgType + ulDirection,
                        (USHORT)(ulMsgLen),
                        (UCHAR *)&(pstContext->stImsi),
                        (UCHAR *)&(pstContext->stIMEI),
                        pstContext->szMsisdn,
                        pstContext->ucRandomNo);

    /* 全网跟踪 */
    stTrcPara.pucTrcMsg = (UCHAR *)pDhcpv6Msg;
    stTrcPara.ucMsgType = ucMsgType;
    stTrcPara.ucUgwRole = pstContext->ucUgwRole;
    stTrcPara.usMsgLen = (USHORT)ulMsgLen;
    stTrcPara.ulEmsTrcDir = ulEmsTrcDir;
    stTrcPara.ulUsrTrcDir = ulDirection;
    stTrcPara.usTraceId = pstContext->usTraceId;
    stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
    stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
    stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
    stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
    stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV6;
    stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
    stTrcPara.ucMsgSndFlg = 0;
    if((1 == stTrcPara.ucSgwTrcFlg) || (1 == stTrcPara.ucPgwTrcFlg))
    {
        UGW_OmEmsTrcMsgTrc(&stTrcPara, &stPath);
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_MsgTraceProcForRelay
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       需要透传的消息进行消息跟踪上报
 *  输入参数:       UCHAR *pucDateMsg,
                    ULONG ulMsgLen,
                    SDB_GSPU_CONTEXT_S *pstContext,
                    ULONG ulEmsTrcDir
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_MsgTraceProcForRelay(UCHAR *pucDateMsg,
                                                 ULONG ulMsgLen,
                                                 UCHAR ucMsgType,
                                                 SDB_GSPU_CONTEXT_S *pstContext,
                                                 ULONG ulEmsTrcDir)
{
    /*此处只考虑合一场景和PGW上的消息跟踪和接口跟踪*/
    UDPHDR_S *pstUdp = NULL;
    RM_SOCKET_PATH_S stPath = {0};
    DHCPV6_MSG_S *pDhcpv6Msg = NULL;
    S_OM_EMS_TRC_PARA stTrcPara = {0};
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_PGW;

    pstUdp = (UDPHDR_S*)(pucDateMsg  + IPV6_HEADER_LEN);
    pDhcpv6Msg = (DHCPV6_MSG_S*)(pucDateMsg + IPV6_HEADER_LEN + UDP_HEADER_LENGTH);

    /* 根据消息方向确定消息跟踪的参数 */
    if (M_EMS_TRC_RECV_MSG == ulEmsTrcDir)
    {
        DHCPV6S_GET_TRCPARA_FOR_RELAY_REV(ucMsgType, ulDirection, stPath, pstUdp, pstContext);
    }
    else
    {
        DHCPV6S_GET_TRCPARA_FOR_RELAY_SEND(ucMsgType, ulDirection, stPath, pstContext);
    }

    AM_CtxApiGetReqApnIndexByPdpContext(pstContext, &(stPath.usApnIndex), &(stPath.ucAliaApnFlag));

    /* 接口跟踪 */
    DHCPV6_MsgInterfaceTrc((UCHAR*)pDhcpv6Msg, (USHORT)ulMsgLen, (ULONG)ucMsgType, ulDirection, &stPath);

    /* 用户跟踪 DTS2012091903437 y00170683 */
    UGW_OmUsrMsgTrace((UCHAR *)pDhcpv6Msg,
                 GUSER_MSGTYPE_DHCPV6,
                 (ULONG)ucMsgType + ulDirection,
                 (USHORT)(ulMsgLen),
                 (UCHAR *)&(pstContext->stImsi),
                 (UCHAR *)&(pstContext->stIMEI),
                 pstContext->szMsisdn,
                 pstContext->ucRandomNo);

    /* 全网跟踪 */
    stTrcPara.pucTrcMsg = (UCHAR *)pDhcpv6Msg;
    stTrcPara.ucMsgType = ucMsgType;
    stTrcPara.ucUgwRole = pstContext->ucUgwRole;
    stTrcPara.usMsgLen = (USHORT)ulMsgLen;
    stTrcPara.ulEmsTrcDir = ulEmsTrcDir;
    /* 透传info-request消息时,都是接收类型 */
    if (DHCPV6_MSG_TYPE_INFORMATION_REQUEST == ucMsgType)
    {
        stTrcPara.ulEmsTrcDir = M_EMS_TRC_RECV_MSG;
    }
    stTrcPara.ulUsrTrcDir = ulDirection;
    stTrcPara.usTraceId = pstContext->usTraceId;
    stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
    stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
    stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
    stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
    stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV6;
    stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
    stTrcPara.ucMsgSndFlg = 0;
    if((1 == stTrcPara.ucSgwTrcFlg) || (1 == stTrcPara.ucPgwTrcFlg))
    {
        UGW_OmEmsTrcMsgTrc(&stTrcPara, &stPath);
    }

    return;
}

#define __MSG_CHECK__

/*****************************************************************************
 *  函数名称:       DHCPV6_CheckForRequestDns
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       检查info-request消息，是否请求DNS
 *  输入参数:       DHCPV6S_OPTION_INFO_S *pstOptionInfo
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_CheckForReqDns(DHCPV6S_OPTION_INFO_S *pstOptionInfo)
{
    ULONG ulOROFlag = pstOptionInfo->ulOROFlag;
    ULONG ulOptionFlag = pstOptionInfo->ulOptionFlag;

    /* 没有请求DNS */
    if(0 == (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_ORO)) &&
       0 == (ulOROFlag & (1 << DHCPV6_MSG_OPTION_DNS_SERVERS)))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_DNS);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_CheckForReqIaPd
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       检查solicit, request消息，是否请求IA_PD,PD_EXCLUDE
 *  输入参数:       DHCPV6S_OPTION_INFO_S *pstOptionInfo
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_CheckForReqIaPd(DHCPV6S_OPTION_INFO_S *pstOptionInfo)
{
    ULONG ulOptionFlag = pstOptionInfo->ulOptionFlag;
    ULONG ulPdExcludeFlg = pstOptionInfo->ulPdExcludeFlg;

    /* 没有请求IA_PD,丢弃消息 */
    if(0 == (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_IAPD)))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_IAPD);
        return VOS_ERR;
    }

    /* 没有请求PD_EXCLUDE,正常分配pd_exclude */
    if((0 == (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_ORO))) ||
       (VOS_FALSE == ulPdExcludeFlg))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_PDEXCLUDE);
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_CheckIpUdp
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       检查IP头和UDP头
 *  输入参数:       UCHAR *pucSrcMsg, ULONG ulMsgLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_CheckIpUdp(UCHAR *pucSrcMsg, ULONG ulMsgLen)
{
    ULONG ulFwdHdrLen = 0;
    //USHORT usCheckSumOri = 0;
    //USHORT usCheckSumFresh = 0;
    IPV6HDR_S *pIpv6Hdr = NULL;
    UDPHDR_S  *pUdpv6Hdr = NULL;
    //UCHAR *pucMsgCheckSum = NULL;

    if(NULL == pucSrcMsg)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NULL_MSG);
        return  VOS_ERR;
    }

    /* 转发上送的报文包括UDP头和IP头，还包括了一个转发头 */
    pIpv6Hdr = (IPV6HDR_S*)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR));
    ulFwdHdrLen = sizeof(FWD_TO_CTRL_HDR);

    /* 检查源地址 */
    if (VOS_OK != IPV6_SrcAddrValidationCheck(pIpv6Hdr))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SRC_ADDR_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "stAddr = %08x;%08x;%08x;%08x",
        pIpv6Hdr->saddr.s6_addr32[0], pIpv6Hdr->saddr.s6_addr32[1],
        pIpv6Hdr->saddr.s6_addr32[2], pIpv6Hdr->saddr.s6_addr32[3]);
        return VOS_ERR;
    }

    if ((VOS_NTOHS(pIpv6Hdr->payload_len) + IPV6_HEADER_LEN + ulFwdHdrLen) != ulMsgLen)
    {
        g_stDhcpv6Statistics.ulLenErr++;
        return VOS_ERR;
    }

    if (pIpv6Hdr->hop_limit < 1)
    {
        g_stDhcpv6Statistics.ulHopLimitErr++;
        return VOS_ERR;
    }

    if (pIpv6Hdr->nexthdr != IPV6_UDP_PRO)
    {
        g_stDhcpv6Statistics.ulNextHeadErr++;
        return VOS_ERR;
    }

    pUdpv6Hdr = (UDPHDR_S *)((UCHAR*)pIpv6Hdr + IPV6_HEADER_LEN);
    if(DHCPV6_SERVER_UDP_PORT != VOS_NTOHS(pUdpv6Hdr->uh_usDPort))
    {
        g_stDhcpv6Statistics.ulDestPortErr++;
        return VOS_ERR;
    }


    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_CheckMsgLen
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       检查消息长度
 *  输入参数:       UCHAR *pucSrcMsg, ULONG ulMsgLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_CheckMsgLen(UCHAR *pucSrcMsg, ULONG ulMsgLen)
{
    ULONG ulDhcpMsgLen = 0;
    ULONG ulTotalMsgLen = 0;
    UCHAR *pucDhcpv6Msg = NULL;
    DHCPV6_OPT_S *pDhcpv6Opt = NULL;
    ULONG ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    /* 消息长度检查 */
    if(ulMsgLen < ulMsgHeadLen + DHCPV6_HEADER_LEN)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MSGLEN_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulMsgLen = %u", ulMsgLen);
        g_stDhcpv6Statistics.ulLenErr++;
        return VOS_ERR;
    }

    /* 检查消息长度与各个选项的长度和是否匹配 */
    ulDhcpMsgLen = ulMsgLen - ulMsgHeadLen;
    pucDhcpv6Msg = pucSrcMsg + ulMsgHeadLen;
    ulTotalMsgLen = ulMsgHeadLen + DHCPV6_HEADER_LEN;
    pDhcpv6Opt = (DHCPV6_OPT_S *) (pucDhcpv6Msg + DHCPV6_HEADER_LEN);/*指向第一个OPTION*/

    while((ULONG)( (UCHAR *)pDhcpv6Opt - pucDhcpv6Msg )< ulDhcpMsgLen)
    {
        ulTotalMsgLen += VOS_NTOHS(pDhcpv6Opt->usOptLen) + DHCPV6_OPT_HEADER_LEN;
        pDhcpv6Opt = (DHCPV6_OPT_S *) ((UCHAR*)pDhcpv6Opt + DHCPV6_OPT_HEADER_LEN + VOS_NTOHS(pDhcpv6Opt->usOptLen));
    }

    if(ulTotalMsgLen != ulMsgLen)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MSGLEN_ERR);
        g_stDhcpv6Statistics.ulOptionLenErr++;
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulTotalMsgLen = %u, ulMsgLen = %u", ulTotalMsgLen, ulMsgLen);
        return VOS_ERR;
    }

    return VOS_OK;
}

#define __MSG_DECODE__
/*****************************************************************************
 *  函数名称:       DHCPV6_GetPdpIdxAndContext
 *  初稿完成:       2012-08-16
 *  作    者:       y00170683
 *  函数功能:       获取pdpindex和上下文
 *  输入参数:       UCHAR *pucSrcMsg
 *  输出参数:       ULONG *pulPdpIndex,
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_GetPdpIdxAndContext(FWD_TO_CTRL_HDR* pstCtrlHdr, ULONG *pulPdpIndex,
                                                SDB_GSPU_CONTEXT_S **ppstContext)
{
    ULONG ulRet = VOS_OK;
    ULONG ulPdpIndex = 0;
    ULONG ulTempIndex = 0;

    if (NULL == ppstContext)
    {
        return VOS_ERR;
    }

    ulTempIndex = (ULONG)fwd_get_ctrlhdr_pdpindex(pstCtrlHdr);
    ulPdpIndex = ulTempIndex - SDB_MAX_CONTEXT_NUM * DHCPV6S_SELF_CMPIDX_INSG;

    /* PDP INDEX检查 */
    if ((ulPdpIndex > SDB_MAX_CONTEXT_NUM) || (0 == ulPdpIndex))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_PDP_INDEX_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulPdpIndex = %u", ulPdpIndex);
        return VOS_ERR;
    }

    /*根据PDP INDEX, 获取上下文*/
    ulRet = (ULONG)SDB_GetContextByIndex(ulPdpIndex, (UCHAR**)ppstContext);
    if ((ulRet != VOS_OK) || (NULL == *ppstContext))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GET_CONTXT_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "no-context");
        return VOS_ERR;
    }

    *pulPdpIndex = ulPdpIndex;

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_OrOptionDecode
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       消息解码
 *  输入参数:       DHCPV6_OPT_S *pDhcpv6Opt
 *  输出参数:       DHCPV6S_OPTION_INFO_S *pstOptionInfo
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_OrOptionDecode(DHCPV6S_OPTION_INFO_S *pstOptionInfo,
                                       DHCPV6_OPT_S *pDhcpv6Opt)
{
    ULONG ulOROFlag = 0;
    USHORT usOROptLen = 0;
    USHORT *pusOptType = (USHORT *)pDhcpv6Opt->opt;

    usOROptLen = VOS_NTOHS(pDhcpv6Opt->usOptLen);
    while(usOROptLen > 0)
    {
        if (DHCPV6_MSG_OPTION_PDEXCLUDE == VOS_HTONS(*pusOptType))
        {
            pstOptionInfo->ulPdExcludeFlg = VOS_TRUE;
        }

        /*lint -e504*/
        ulOROFlag |= (ULONG)1 << (VOS_HTONS(*pusOptType));
        /*lint +e504*/
        pusOptType++;
        usOROptLen -= 2;
    }
    pstOptionInfo->ulOROFlag = ulOROFlag;

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_MsgDecode
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       消息解码
 *  输入参数:       DHCPV6S_MSG_INFO_S *pstMsgInfo
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_MsgDecode(DHCPV6S_MSG_INFO_S *pstMsgInfo)
{
    ULONG ulOptionFlag = 0;
    DHCPV6_OPT_S *pDhcpv6Opt = NULL;
    pDhcpv6Opt = (DHCPV6_OPT_S *)(pstMsgInfo->pucMsg + DHCPV6_HEADER_LEN);/*指向第一个OPTION*/

    /*lint -e574*/
    while((UCHAR *)pDhcpv6Opt - pstMsgInfo->pucMsg < pstMsgInfo->ulMsgLen)
    {
        switch (VOS_NTOHS(pDhcpv6Opt->usOptType))
        {
            case DHCPV6_MSG_OPTION_ORO:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_ORO;
                if(VOS_NTOHS(pDhcpv6Opt->usOptLen) % 2 != 0)
                {
                    g_stDhcpv6Statistics.ulOptionLenOddErr++;
                    break;
                }

                /* 解析Option-Request Option */
                DHCPV6_OrOptionDecode(&(pstMsgInfo->stDhcpOptionInfo), pDhcpv6Opt);
                break;

            case DHCPV6_MSG_OPTION_CLIENTID:
                pstMsgInfo->stDhcpOptionInfo.pstCiOption = pDhcpv6Opt;
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_CLIENTID;
                break;

            case DHCPV6_MSG_OPTION_SERVERID:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_SERVERID;
                break;

            case DHCPV6_MSG_OPTION_IA_NA:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IA_NA;
                break;

            case DHCPV6_MSG_OPTION_IA_TA:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IA_TA;
                break;

            case DHCPV6_MSG_OPTION_IAADDR:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IAADDR;
                break;

            case DHCPV6_MSG_OPTION_PREFERENCE:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_PREFERENCE;
                break;

            case DHCPV6_MSG_OPTION_ELAPSED_TIME:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_ELAPSED_TIME;
                break;

            case DHCPV6_MSG_OPTION_RELAY_MSG:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RELAY_MSG;
                break;

            case DHCPV6_MSG_OPTION_AUTH:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_AUTH;
                break;

            case DHCPV6_MSG_OPTION_UNICAST:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_UNICAST;
                break;

            case DHCPV6_MSG_OPTION_STATUS_CODE:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_STATUS_CODE;
                break;

            case DHCPV6_MSG_OPTION_RAPID_COMMIT:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RAPID_COMMIT;
                break;

            case DHCPV6_MSG_OPTION_USER_CLASS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_USER_CLASS;
                break;

            case DHCPV6_MSG_OPTION_VENDOR_CLASS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_VENDOR_CLASS;
                break;

            case DHCPV6_MSG_OPTION_VENDOR_OPTS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_VENDOR_OPTS;
                break;

            case DHCPV6_MSG_OPTION_INTERFACE_ID:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_INTERFACE_ID;
                break;

            case DHCPV6_MSG_OPTION_RECONF_MSG:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RECONF_MSG;
                break;

            case DHCPV6_MSG_OPTION_RECONF_ACCEPT:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RECONF_ACCEPT;
                break;

            case DHCPV6_MSG_OPTION_DNS_SERVERS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_DNS_SERVERS;
                break;

            case DHCPV6_MSG_OPTION_DOMAIN_LIST:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_DOMAIN_LIST;
                break;

            /* ipv6-pd特性 2012.8.1 y00170683*/
            case DHCPV6_MSG_OPTION_IAPD:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IAPD;
                break;

            default:
                g_stDhcpv6Statistics.ulUnknownOptErr++;
                break;
        }

        pDhcpv6Opt = (DHCPV6_OPT_S *) ((UCHAR*)pDhcpv6Opt + DHCPV6_OPT_HEADER_LEN + VOS_NTOHS(pDhcpv6Opt->usOptLen));
    }
    pstMsgInfo->stDhcpOptionInfo.ulOptionFlag = ulOptionFlag;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulOptionFlag = 0x%x, ulOROFlag = 0x%x, ulPdExcludeFlg = 0x%x",
                        pstMsgInfo->stDhcpOptionInfo.ulOptionFlag,
                        pstMsgInfo->stDhcpOptionInfo.ulOROFlag,
                        pstMsgInfo->stDhcpOptionInfo.ulPdExcludeFlg);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_MsgUnpacket
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       消息解封装
 *  输入参数:       UCHAR *pucSrcMsg, ULONG ulMsgLen
 *  输出参数:       DHCPV6S_MSG_INFO_S *pstMsgInfo
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_MsgUnpacket(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                    UCHAR *pucSrcMsg, ULONG ulMsgLen)
{
    ULONG ulMsgHeadLen = 0;
    UDPHDR_S *pstUdpv6Hdr = NULL;
    IPV6HDR_S *pstIpv6Hdr = NULL;

    pstIpv6Hdr = (IPV6HDR_S *)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR));
    pstUdpv6Hdr = (UDPHDR_S *)((UCHAR *)pstIpv6Hdr + IPV6_HEADER_LEN);
    ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    /* 确定消息长度和消息内容 */
    pstMsgInfo->pucMsg = pucSrcMsg + ulMsgHeadLen;
    pstMsgInfo->ulMsgLen = ulMsgLen - ulMsgHeadLen;
    pstMsgInfo->ucMsgType = ((DHCPV6_MSG_S*)pstMsgInfo->pucMsg)->ucMsgType;
    VOS_MemCpy(&(pstMsgInfo->stSrcAddr), &(pstIpv6Hdr->saddr), sizeof(in6_addr));
    VOS_MemCpy(&(pstMsgInfo->stDstAddr), &(pstIpv6Hdr->daddr), sizeof(in6_addr));
    /* 后面发送消息时直接使用,因此不进行字节序转换 */
    pstMsgInfo->usSrcPort = pstUdpv6Hdr->uh_usSPort;
    pstMsgInfo->usDstPort = pstUdpv6Hdr->uh_usDPort;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG,
            "srcPort = %u, srcAddr = 0x%x:%x:%x:%x, dstPort = %u, dstAddr = 0x%x:%x:%x:%x",
            VOS_NTOHS(pstMsgInfo->usSrcPort),
            pstMsgInfo->stSrcAddr.s6_addr32[0], pstMsgInfo->stSrcAddr.s6_addr32[1],
            pstMsgInfo->stSrcAddr.s6_addr32[2], pstMsgInfo->stSrcAddr.s6_addr32[3],
            VOS_NTOHS(pstMsgInfo->usDstPort),
            pstMsgInfo->stDstAddr.s6_addr32[0], pstMsgInfo->stDstAddr.s6_addr32[1],
            pstMsgInfo->stDstAddr.s6_addr32[2], pstMsgInfo->stDstAddr.s6_addr32[3]);

    return;
}

#define __MSG_ENCODE__
/*****************************************************************************
 *  函数名称:       DHCPV6_FillServerIdOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充Client Identifier Option
 *  输入参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_FillServerIdOption(UCHAR *pucMsgBuff,
                                         ULONG *pulOffset,
                                         SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulServerIP = 0;
    USHORT usOptionLen = 0;
    UCHAR ucUgwRole = pstContext->ucUgwRole;
    DHCPV6_OPT_S *pstServerIdOption = (DHCPV6_OPT_S *)pucMsgBuff;
    DHCPV6_DUID_EN_OPTION_S *pstDuidEn = (DHCPV6_DUID_EN_OPTION_S *)pstServerIdOption->opt;

    /* 确定本端信令IP */
    if (E_NET_ELEMENT_ROLE_PGW_AND_SGW == ucUgwRole)
    {
        ulServerIP = pstContext->ulSgwLeftLocSigIP;
    }
    else
    {
        ulServerIP = pstContext->ulS5_Gn_LocSigIP;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucUgwRole = %u, ulServerIP = 0x%x",
                        ucUgwRole, ulServerIP);

    pstServerIdOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_SERVERID);
    pstDuidEn->usType = VOS_HTONS(DHCPV6_MSG_OPTION_DUID_EN);
    pstDuidEn->ulEnterpriseNum = VOS_HTONL(DHCPV6_HUAWEI_ENTERPRISENUM);
    usOptionLen += sizeof(DHCPV6_DUID_EN_OPTION_S);
    *(ULONG*)pstDuidEn->ucData = ulServerIP;
    usOptionLen += sizeof(ULONG);
    pstServerIdOption->usOptLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "usOptionLen = %u", usOptionLen);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillDnsOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充Client Identifier Option
 *  输入参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_FillDnsOption(UCHAR *pucMsgBuff,
                                     ULONG *pulOffset,
                                     SDB_GSPU_CONTEXT_S *pstContext)
{
    in6_addr stMainDnsIp;
    in6_addr stSecdDnsIp;
    USHORT usOptionLen = 0;
    DHCPV6_OPT_S *pstDnsOption = (DHCPV6_OPT_S *)pucMsgBuff;

    VOS_MemCpy(&stMainDnsIp, &(pstContext->stMainDnsIp), sizeof(in6_addr));
    VOS_MemCpy(&stSecdDnsIp, &(pstContext->stBackupDnsIp), sizeof(in6_addr));

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "stMainDnsIp = 0x%x:%x:%x:%x, stSecdDnsIp = 0x%x:%x:%x:%x",
            stMainDnsIp.s6_addr32[0], stMainDnsIp.s6_addr32[1],
            stMainDnsIp.s6_addr32[2], stMainDnsIp.s6_addr32[3],
            stSecdDnsIp.s6_addr32[0], stSecdDnsIp.s6_addr32[1],
            stSecdDnsIp.s6_addr32[2], stSecdDnsIp.s6_addr32[3]);

    if(VOS_FALSE == DHCPV6S_IPV6_ADDR_INVALID(&stMainDnsIp))
    {
        pstDnsOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_DNS_SERVERS);
//        DHCPV6_HTONL_IPV6_ADDR(stMainDnsIp);
        VOS_MemCpy(pstDnsOption->opt, &stMainDnsIp, sizeof(in6_addr));
        usOptionLen += sizeof(in6_addr);
        if(VOS_FALSE == DHCPV6S_IPV6_ADDR_INVALID(&stSecdDnsIp))
        {
//            DHCPV6_HTONL_IPV6_ADDR(stSecdDnsIp);
            VOS_MemCpy(pstDnsOption->opt + sizeof(in6_addr), &stSecdDnsIp, sizeof(in6_addr));
            usOptionLen += sizeof(in6_addr);
        }
        pstDnsOption->usOptLen = VOS_HTONS(usOptionLen);
        *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "usOptionLen = %u", usOptionLen);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillStatusCodeOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充Status-Code Option
 *  输入参数:       无
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_FillStatusCodeOption(UCHAR *pucMsgBuff,
                                              ULONG *pulOffset,
                                              USHORT usStatusCode)
{
    DHCPV6_OPT_S *pstStatusCodeOption = (DHCPV6_OPT_S *)pucMsgBuff;

    pstStatusCodeOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_STATUS_CODE);
    *(USHORT*)pstStatusCodeOption->opt = VOS_HTONS(usStatusCode);
    pstStatusCodeOption->usOptLen = VOS_HTONS(sizeof(USHORT));

    *pulOffset += (DHCPV6_OPT_HEADER_LEN + sizeof(USHORT));
    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulOffset = %u", *pulOffset);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_GetSubnetByPrefixAddr
 *  初稿完成:       2012-08-07
 *  作    者:       z00175135
 *  函数功能:       根据前缀地址获取pd-exclude的subnetId
 *  输入参数:       无
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_GetSubnetByPrefixAddr(ULONG aulPrefixAddr[],
                                                UCHAR ucPrefixLength,
                                                ULONG *pulSubnetId,
                                                UCHAR *pucByteNum)
{
    UCHAR ucMoveBitNum = 0;
    ULONG ulTempIp= 0;
	ULONG ulTmpAddr[4] = {0};

    if ((NULL == pulSubnetId) || (NULL == pucByteNum))
    {
        VOS_Assert(NULL != pulSubnetId);
        VOS_Assert(NULL != pucByteNum);
        return;
    }

	/*将传入的ip地址转换成主机序之后进运算*/
	ulTmpAddr[0] = VOS_NTOHL(aulPrefixAddr[0]);
	ulTmpAddr[1] = VOS_NTOHL(aulPrefixAddr[1]);
	ulTmpAddr[2] = VOS_NTOHL(aulPrefixAddr[2]);
	ulTmpAddr[3] = VOS_NTOHL(aulPrefixAddr[3]);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "PrefixAddr = 0x%x:%x:%x:%x, PrefixLength = %u",
            ulTmpAddr[0], ulTmpAddr[1],
            ulTmpAddr[2], ulTmpAddr[3], ucPrefixLength);

    /* 最可能的情况放到最前面，目前只会进入第一个if */
    if ((ucPrefixLength > 32) && (ucPrefixLength <= 64))
    {
        ucMoveBitNum = (64 - ucPrefixLength);
        ulTempIp = ulTmpAddr[1] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }
    else if ((ucPrefixLength > 0) && (ucPrefixLength <= 32))
    {
        ucMoveBitNum = (32 - ucPrefixLength);
        ulTempIp = ulTmpAddr[0] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }
    else if ((ucPrefixLength > 64) && (ucPrefixLength <= 96))
    {
        ucMoveBitNum = (96 - ucPrefixLength);
        ulTempIp = ulTmpAddr[2] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }
    else if ((ucPrefixLength > 96) && (ucPrefixLength <= 128))
    {
        ucMoveBitNum = (128 - ucPrefixLength);
        ulTempIp = ulTmpAddr[3] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }

    *pulSubnetId = ulTempIp << (LAP_ULONG_BIT_NUM - ucMoveBitNum);
    *pucByteNum = (ucMoveBitNum / 8) + (0 == (ucMoveBitNum % 8) ? 0: 1);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulSubnetId = 0x%x, ucByteNum = %u",
                        *pulSubnetId, *pucByteNum);

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillPdExcludeOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充Pd-exclude Option
 *  输入参数:       in6_addr *pstIPv6Prefix, UCHAR ucMaskLen
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_FillPdExcludeOption(UCHAR *pucMsgBuff,
                                            ULONG *pulOffset,
                                            in6_addr *pstIPv6Prefix,
                                            UCHAR ucIpv6PrefixLength)
{
    UCHAR ucByteNum = 0;
    ULONG ulSubnetId = 0;
    USHORT usOptionLen = 0;
    DHCPV6_PDEXCLUDE_OPTION_S *pstPdExcludeOption = (DHCPV6_PDEXCLUDE_OPTION_S *)pucMsgBuff;

    pstPdExcludeOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_PDEXCLUDE);
    pstPdExcludeOption->ucPrefixLen = DHCPV6S_PREFIX_LEN;
    usOptionLen += sizeof(UCHAR);

    /* 获取subnetId */
    DHCPV6_GetSubnetByPrefixAddr((ULONG *)pstIPv6Prefix, ucIpv6PrefixLength, &ulSubnetId, &ucByteNum);
    /* ulSubnetId本来是大字节序,但在windows和x86场景,需要进行字节序转换才能正确取值 */
    ulSubnetId = VOS_HTONL(ulSubnetId);
    VOS_MemCpy(pstPdExcludeOption->ucData, (UCHAR*)&ulSubnetId, ucByteNum);
    usOptionLen += ucByteNum;
    pstPdExcludeOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucByteNum = %u, usOptionLen = %u", ucByteNum, usOptionLen);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillIaPrefixOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充ia-prefix Option
 *  输入参数:       in6_addr *pstIPv6Prefix, UCHAR ucIpv6PrefixLength
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_FillIaPrefixOption(UCHAR *pucMsgBuff,
                                        ULONG *pulOffset,
                                        in6_addr *pstIPv6Prefix,
                                        UCHAR ucIpv6PrefixLength)
{
    in6_addr stIpv6Addr;
    UCHAR ucPos = 0;
    UCHAR ucMoveBitNum = 0;
    USHORT usOptionLen = 0;
    ULONG ulPdExcludeLen = 0;
    DHCPV6_IAPREFIX_OPTION_S *pstIaPrefixOption = (DHCPV6_IAPREFIX_OPTION_S *)pucMsgBuff;

    /* 前缀长度不合法 */
    if ((ucIpv6PrefixLength > DHCPV6S_PD_PREFIX_MAX_LEN)
        || (ucIpv6PrefixLength < DHCPV6S_PD_PREFIX_MIN_LEN))
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ucIpv6PrefixLength = %u", ucIpv6PrefixLength);
        return VOS_ERR;
    }

    /* 前缀不合法 */
    if (VOS_TRUE == DHCPV6S_IPV6_ADDR_INVALID(pstIPv6Prefix))
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "IPv6Prefix = 0x%x:%x:%x:%x",
            pstIPv6Prefix->s6_addr32[0], pstIPv6Prefix->s6_addr32[1],
            pstIPv6Prefix->s6_addr32[2], pstIPv6Prefix->s6_addr32[3]);
        return VOS_ERR;
    }

    VOS_MemCpy(&(stIpv6Addr), pstIPv6Prefix, sizeof(in6_addr));
    DHCPV6_NTOHL_IPV6_ADDR(stIpv6Addr);
    pstIaPrefixOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_IAPREFIX);
    pstIaPrefixOption->ulPreTime = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);
    pstIaPrefixOption->ulValidTime = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);
    pstIaPrefixOption->ucPrefixLen = ucIpv6PrefixLength;
    usOptionLen += sizeof(UCHAR);

    /* 确定PD前缀 */
    LAP_SetPrefixLengthIp((ULONG *)&stIpv6Addr, ucIpv6PrefixLength, (ULONG *)&stIpv6Addr, &ucPos, &ucMoveBitNum);
    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "PdPrefix = 0x%x:%x:%x:%x, ucPos = %u, ucMoveBitNum = %u",
            stIpv6Addr.s6_addr32[0], stIpv6Addr.s6_addr32[1],
            stIpv6Addr.s6_addr32[2], stIpv6Addr.s6_addr32[3],
            ucPos, ucMoveBitNum);
    DHCPV6_HTONL_IPV6_ADDR(stIpv6Addr);
    VOS_MemCpy(&(pstIaPrefixOption->stIpv6Prefix), &stIpv6Addr, sizeof(in6_addr));
    usOptionLen += sizeof(in6_addr);

    /* 填充pd-exclude-option */
    DHCPV6_FillPdExcludeOption(pstIaPrefixOption->ucData, &ulPdExcludeLen, pstIPv6Prefix, ucIpv6PrefixLength);
    usOptionLen += (USHORT)ulPdExcludeLen;
    pstIaPrefixOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "OptionLen = %u", usOptionLen);
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillIaPdOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充IA_PD option
 *  输入参数:       SDB_GSPU_CONTEXT_S *pstContext
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_FillIaPdOption(UCHAR *pucMsgBuff,
                                      ULONG *pulOffset,
                                      DHCPV6_OPT_S *pstDhcpv6Opt,
                                      SDB_GSPU_CONTEXT_S *pstContext,
                                      UCHAR ucIsFirstFlg)
{
    ULONG ulRet = VOS_OK;
    USHORT usOptionLen = 0;
    ULONG ulIaPrefixOptionLen = 0;
    ULONG ulStatusCodeOptionLen = 0;
    DHCPV6_IAPD_OPTION_S *pstIaPdOption = (DHCPV6_IAPD_OPTION_S *)pucMsgBuff;
    DHCPV6_IAPD_OPTION_S *pstSrcIaPdOption = (DHCPV6_IAPD_OPTION_S *)pstDhcpv6Opt;

    pstIaPdOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_IAPD);
    VOS_MemCpy(&(pstIaPdOption->ulId), &(pstSrcIaPdOption->ulId), sizeof(ULONG));
    usOptionLen += sizeof(ULONG);
    pstIaPdOption->ulT1 = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);
    pstIaPdOption->ulT2 = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucIpv6PrefixLength = %u, ucIsFirstFlg = %u",
                         pstContext->ucIpv6PrefixLength, ucIsFirstFlg);

    /* 首先前缀长度不在49~63之间,或者不是第一个ia-pd-option时,填充code=6的status-code-option */
    if (((pstContext->ucIpv6PrefixLength > DHCPV6S_PD_PREFIX_MAX_LEN)
        || (pstContext->ucIpv6PrefixLength < DHCPV6S_PD_PREFIX_MIN_LEN))
        || (VOS_FALSE == ucIsFirstFlg))
    {
        /* 填充status-code-option */
        DHCPV6_FillStatusCodeOption(pstIaPdOption->ucData, &ulStatusCodeOptionLen, DHCPV6C_STATUS_CODE_NOPREFIX);
        usOptionLen += (USHORT)ulStatusCodeOptionLen;
    }
    /* 前缀长度在49~63之间，且是第一个ia-pd-option时,填充ia-prefix-option */
    else
    {
        /* 填充ia-prefix-option */
        ulRet = DHCPV6_FillIaPrefixOption(pstIaPdOption->ucData, &ulIaPrefixOptionLen,
                            &(pstContext->stIPv6Addr), pstContext->ucIpv6PrefixLength);
        if (VOS_OK != ulRet)
        {
            /* 填充失败时,填充code=6的status-code-option */
            DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6_FillIaPrefixOption fail");
            DHCPV6_FillStatusCodeOption(pstIaPdOption->ucData, &ulStatusCodeOptionLen, DHCPV6C_STATUS_CODE_NOPREFIX);
            usOptionLen += (USHORT)ulStatusCodeOptionLen;
        }
        else
        {
            usOptionLen += (USHORT)ulIaPrefixOptionLen;
        }
    }
    pstIaPdOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "OptionLen = %u", usOptionLen);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillIaPdOptionForMsg
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充IA_PD option
 *  输入参数:       SDB_GSPU_CONTEXT_S *pstContext
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_FillIaPdOptionForMsg(UCHAR *pucMsgBuff,
                                               ULONG *pulOffset,
                                               DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                               SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulIaPdNum = 0;
    ULONG ulOptionLen = 0;
    USHORT usIaPdMinLen = 0;
    UCHAR ucIsFirstFlg = VOS_TRUE; /* 必须初始化为VOS_TRUE */
    DHCPV6_OPT_S *pstDhcpv6Opt = NULL;

    /* IA-PD的最小长度,小于该长度时会导致固定部分取值错误 */
    usIaPdMinLen = sizeof(DHCPV6_IAPD_OPTION_S) - sizeof(DHCPV6_OPT_S);

    /*指向第一个OPTION*/
    pstDhcpv6Opt = (DHCPV6_OPT_S *)(pstMsgInfo->pucMsg + DHCPV6_HEADER_LEN);

    /* 为每一个有效的ia-pd填充响应信息 */
    while((UCHAR *)pstDhcpv6Opt - pstMsgInfo->pucMsg < pstMsgInfo->ulMsgLen)
    {
        if ((DHCPV6_MSG_OPTION_IAPD == VOS_NTOHS(pstDhcpv6Opt->usOptType))
            && (VOS_NTOHS(pstDhcpv6Opt->usOptLen) >= usIaPdMinLen))
        {
            if (VOS_TRUE == ucIsFirstFlg)
            {
                DHCPV6_FillIaPdOption(&(pucMsgBuff[*pulOffset]), pulOffset,
                    pstDhcpv6Opt, pstContext, VOS_TRUE);
                ucIsFirstFlg = VOS_FALSE;
            }
            else
            {
                DHCPV6_FillIaPdOption(&(pucMsgBuff[*pulOffset]), pulOffset,
                    pstDhcpv6Opt, pstContext, VOS_FALSE);
            }
            ulIaPdNum ++;
        }

        ulOptionLen = DHCPV6_OPT_HEADER_LEN + VOS_NTOHS(pstDhcpv6Opt->usOptLen);
        pstDhcpv6Opt = (DHCPV6_OPT_S *)((UCHAR*)pstDhcpv6Opt + ulOptionLen);
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "IaPdNum = %u", ulIaPdNum);

    /* 不存在有效的ia-pd则返回VOS_ERR,丢弃消息 */
    if (0 == ulIaPdNum)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_VALID_IAPD);
        return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillRapidComOption
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       填充rapid-commit-option
 *  输入参数:       无
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_FillRapidComOption(UCHAR *pucMsgBuff, ULONG *pulOffset)
{
    DHCPV6_OPT_S *pstRapidComOption = (DHCPV6_OPT_S *)pucMsgBuff;

    pstRapidComOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_RAPID_COMMIT);
    pstRapidComOption->usOptLen = 0;
    *pulOffset += DHCPV6_OPT_HEADER_LEN ;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_FillMsg
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       为申请DNS构造响应消息
 *  输入参数:       UCHAR *pSrcMbuf,
                    PMBUF_S *pstDstMbuf,
                    ULONG ulDhcpMsgLen,
                    in6_addr *pstMainDnsIp,
                    in6_addr *pstBackupDnsIp
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_FillMsg(UCHAR *pucMsgBuff,
                           ULONG *pulMsgLen,
                           DHCPV6S_MSG_INFO_S *pstMsgInfo,
                           SDB_GSPU_CONTEXT_S *pstContext,
                           UCHAR ucMsgType)
{
    ULONG ulRet = VOS_OK;
    ULONG ulCiOptionLen = 0;
    DHCPV6_OPT_S *pstCiOption = NULL;
    DHCPV6_MSG_S *pstDhcpv6Msg = NULL;

    /* 填充消息头 */
    pstDhcpv6Msg = (DHCPV6_MSG_S *)pucMsgBuff;
    VOS_MemCpy((UCHAR*)pstDhcpv6Msg, pstMsgInfo->pucMsg, sizeof(ULONG));
    pstDhcpv6Msg->ucMsgType = ucMsgType;
    *pulMsgLen += sizeof(ULONG);

    /* 如果携带CI,则copy */
    pstCiOption = pstMsgInfo->stDhcpOptionInfo.pstCiOption;
    if (NULL != pstCiOption)
    {
        ulCiOptionLen = DHCPV6_HEADER_LEN + VOS_NTOHS(pstCiOption->usOptLen);
        VOS_MemCpy(&pucMsgBuff[*pulMsgLen], pstCiOption, ulCiOptionLen);
        *pulMsgLen += ulCiOptionLen;
    }

    /* 填充SI */
    DHCPV6_FillServerIdOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstContext);

    /* 填充DNS */
    if (VOS_TRUE == pstMsgInfo->ucReqDnsFlg)
    {
        DHCPV6_FillDnsOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstContext);
    }

    /* 填充IaPd */
    if (VOS_TRUE == pstMsgInfo->ucReqPdFlg)
    {
        ulRet = DHCPV6_FillIaPdOptionForMsg(pucMsgBuff, pulMsgLen, pstMsgInfo, pstContext);
        if (VOS_OK != ulRet)
        {
            return VOS_ERR;
        }
    }

    /* 填充Rapid-commit */
    if (VOS_TRUE == pstMsgInfo->ucReqRapidFlg)
    {
        DHCPV6_FillRapidComOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen);
    }

    return VOS_OK;
}

#define __MSG_SEND__
/*****************************************************************************
 *  函数名称:       DHCPV6_CalcSuccSendPacketNum
 *  初稿完成:       2012-08-08
 *  作    者:       y00170683
 *  函数功能:       统计发消息成功计数
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_CalcSuccSendPacketNum(UCHAR ucMsgType)
{
    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_ADVERTISE :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_ADVERTISE_SUCC);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_REPLY_SUCC);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_OTHER_SUCC);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_CalcFailSendPacketNum
 *  初稿完成:       2012-08-08
 *  作    者:       y00170683
 *  函数功能:       统计发消息失败计数
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_CalcFailSendPacketNum(UCHAR ucMsgType)
{
    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_ADVERTISE :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_ADVERTISE_FAIL);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_REPLY_FAIL);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_OTHER_FAIL);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_SendMsg
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       给MS回复消息
 *  输入参数:       UCHAR *pMbuf, ULONG ulPdpIndex, UCHAR ucLeftEncapType
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_SendMsgOut(UCHAR *pMbuf, ULONG ulPdpIndex,
                               UCHAR ucLeftEncapType)
{
    /* 调用通用封装GTP头的函数，封装GTP头并发送报文 */
    if(DHCP_ENCAP_PMIP_GRE == ucLeftEncapType)
    {
        g_ulGreProType = 1;
        DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "gre-encape");
        if (VOS_OK != UGW_GRE_Encap((PMBUF_S *)pMbuf, ulPdpIndex))
        {
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GRE_SEND_ERR);
            return VOS_ERR;
        }
    }
    else
    {
        DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "gtp-encape");
        if (VOS_OK != UGW_GtpEncap((PMBUF_S *)pMbuf, ulPdpIndex))
        {
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GTP_SEND_ERR);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_SendMsgToClient
 *  初稿完成:       2012-08-02
 *  作    者:       y00170683
 *  函数功能:       为info-request回复reply消息
 *  输入参数:       DHCPV6S_MSG_INFO_S *pstMsgInfo,
                    SDB_GSPU_CONTEXT_S *pstContext,
                    UCHAR ucMsgType
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_SendMsgToClient(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                          SDB_GSPU_CONTEXT_S *pstContext,
                                          UCHAR ucMsgType)
{
    in6_addr stDstAddr;    /* 目的地址 */
    ULONG ulMsgLen = 0;    /* dhcp消息总长度 */
    ULONG ulRet = VOS_OK;
    USHORT usUdpMsgLen = 0;
    PMBUF_S *pstMbuf = NULL;
    ULONG ulDhcpMsgLen = 0;    /* dhcp消息体长度 */
    USHORT usCheckSumFresh = 0;
    IPV6HDR_S *pstIpv6Hdr = NULL;
    UDPHDR_S *pstUdpv6Hdr = NULL;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucMsgType = %u", ucMsgType);
    DHCP_MemZero(g_pucDhcpv6sSendBuff, DHCPV6S_SEND_MSG_MAXLEN);

    /* 填充消息 预留出ip头和udp头 */
    pstIpv6Hdr = (IPV6HDR_S *)g_pucDhcpv6sSendBuff;
    pstUdpv6Hdr = (UDPHDR_S *)&g_pucDhcpv6sSendBuff[IPV6_HEADER_LEN];
    ulRet = DHCPV6_FillMsg(&g_pucDhcpv6sSendBuff[IPV6_HEADER_LEN + UDPV6_HEADER_LEN],
                            &ulDhcpMsgLen, pstMsgInfo, pstContext, ucMsgType);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* 填写UDP头内容 DTS2012092403013 y00170683 UDP头中长度应该是UDP头长度+消息长度 */
    usUdpMsgLen= (USHORT)(ulDhcpMsgLen + UDPV6_HEADER_LEN);
    pstUdpv6Hdr->uh_sULen = (SHORT)VOS_HTONS(usUdpMsgLen);
    pstUdpv6Hdr->uh_usDPort = pstMsgInfo->usSrcPort;
    pstUdpv6Hdr->uh_usSPort = pstMsgInfo->usDstPort;

    if(ipv6_addr_any(&pstMsgInfo->stSrcAddr))
    {
        ipv6_addr_all_nodes(&stDstAddr);
    }
    else
    {
        ipv6_addr_copy(&stDstAddr, &pstMsgInfo->stSrcAddr);
    }

    if (VOS_OK != ICMPv6_CheckSum((UCHAR *)pstIpv6Hdr, in6addr_ggsn, stDstAddr, (UCHAR *)pstUdpv6Hdr,
                                    usUdpMsgLen, &usCheckSumFresh, IPV6_UDP_PRO))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_CHECKSUM_ERR);
        return VOS_ERR;
    }
    pstUdpv6Hdr->uh_usSum = usCheckSumFresh;

    /* 填写IP头内容 */
    *(ULONG*)pstIpv6Hdr = VOS_HTONL(0x60000000); /* version and etc */
    pstIpv6Hdr->payload_len = VOS_HTONS(usUdpMsgLen);
    pstIpv6Hdr->nexthdr = IPV6_UDP_PRO;
    pstIpv6Hdr->hop_limit = 255;
    ipv6_addr_copy(&(pstIpv6Hdr->saddr), &in6addr_ggsn);
    ipv6_addr_copy(&(pstIpv6Hdr->daddr), &stDstAddr);

    /* 消息总长度 */
    ulMsgLen = IPV6_HEADER_LEN + usUdpMsgLen;

    /* 申请MBUF */
#if 0
    pstMbuf = PMBUF_CreateByCopyBuffer(0, ulMsgLen, g_pucDhcpv6sSendBuff,
                                          MBUF_TYPE_DATA, MID_DHCPSV6);
#endif
    pstMbuf = PMBUF_GetPMbuf(MID_DHCPC, ulMsgLen);

    if (NULL == pstMbuf)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MALLOC_BUFF_FAIL);
        return VOS_ERR;
    }

    ulRet = DHCPV6_SendMsgOut((UCHAR *)pstMbuf, pstMsgInfo->ulPdpIndex, pstContext->ucLeftEncapType);
    if (VOS_OK != ulRet)
    {
        /* 发送失败释放buf */
        (VOID)PMBUF_Destroy(pstMbuf);

        /* 发送消息失败计数 */
        DHCPV6_CalcFailSendPacketNum(ucMsgType);
        return VOS_ERR;
    }

    /* 发送消息成功计数 */
    DHCPV6_CalcSuccSendPacketNum(ucMsgType);

    /* 只有information-reques才进行性能统计 */
    if (DHCPV6_MSG_TYPE_INFORMATION_REQUEST == pstMsgInfo->ucMsgType)
    {
        if (VOS_NULL_PTR != g_PGWtoUE_ulDHCPV6AckNumAddr)
        {
            (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoUE_ulDHCPV6AckNumAddr, E_PERF_OBJECT_ADD, 1);
        }
    }

    /* 消息跟踪 */
    DHCPV6_MsgTraceProc((DHCPV6_MSG_S*)(&g_pucDhcpv6sSendBuff[IPV6_HEADER_LEN + UDPV6_HEADER_LEN]),
                        ulDhcpMsgLen, pstContext, pstUdpv6Hdr, M_EMS_TRC_SEND_MSG);

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_CalcSuccRelayPacketNum
 *  初稿完成:       2012-08-08
 *  作    者:       y00170683
 *  函数功能:       统计发消息成功计数
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_CalcSuccRelayPacketNum(UCHAR ucMsgType)
{
    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_INFO_SUCC);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_REPLY_SUCC);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_OTHER_SUCC);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_CalcFailRelayPacketNum
 *  初稿完成:       2012-08-08
 *  作    者:       y00170683
 *  函数功能:       统计发消息失败计数
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6_CalcFailRelayPacketNum(UCHAR ucMsgType)
{
    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_INFO_FAIL);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_REPLY_FAIL);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_OTHER_FAIL);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPv6_RelaySendMsg
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       发送透传消息
 *  输入参数:       PMBUF_S *pMbuf, UCHAR *pucDateMsg, ULONG ulPdpIndex,
                    SDB_GSPU_CONTEXT_S *pstContext, ULONG ulDhcpMsgLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPv6_RelaySendMsg(PMBUF_S *pMbuf, UCHAR ucMsgType, ULONG ulPdpIndex)
{
    /*填充IP地址和UDP端口号，并且用GTP或者GRE的方式发送出去 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST :
            DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "info-request");
            g_ulGreProType = 1;
            if (VOS_OK != UGW_GRE_Encap(pMbuf, ulPdpIndex))
            {
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GRE_RELAY_ERR);
                return VOS_ERR;
            }
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "reply");
            if (VOS_OK != UGW_GtpEncap(pMbuf, ulPdpIndex))
            {
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GTP_RELAY_ERR);
                return VOS_ERR;
            }
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPv6_RelayMsg
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       透传消息
 *  输入参数:       UCHAR *pucDateMsg,ULONG ulPdpIndex,ULONG ulIpPacketLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPv6_RelayMsg(UCHAR *pucDateMsg, ULONG ulIpPacketLen,
                               ULONG ulPdpIndex, SDB_GSPU_CONTEXT_S *pstContext)
{
    UCHAR ucMsgType = 0;
    ULONG ulRet = VOS_OK;
    PMBUF_S *pMbuf = NULL;
    DHCPV6_MSG_S *pstDhcpPacket = NULL;
    ULONG ulMsgHeadLen = IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    ULONG ulDhcpMsgLen = ulIpPacketLen - ulMsgHeadLen;

    /*入参判断*/
    if((NULL == pucDateMsg) || (NULL == pstContext))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NULL_MSG);
        return VOS_ERR;
    }

    pstDhcpPacket = (DHCPV6_MSG_S*)(pucDateMsg + IPV6_HEADER_LEN + UDP_HEADER_LENGTH);
    ucMsgType = pstDhcpPacket->ucMsgType;

    /* 收到消息, 上报消息跟踪 */
    DHCPV6_MsgTraceProcForRelay(pucDateMsg, ulDhcpMsgLen, ucMsgType, pstContext,
                                   M_EMS_TRC_RECV_MSG);

    /* 判断消息类型 */
    if ((DHCPV6_MSG_TYPE_INFORMATION_REQUEST != ucMsgType)
        && (DHCPV6_MSG_TYPE_REPLY != ucMsgType))
    {
        return VOS_ERR;
    }

    /*创建MBUF*/
#if 0
    pMbuf = PMBUF_CreateByCopyBuffer (0, ulIpPacketLen, pucDateMsg,
                                         MBUF_TYPE_DATA, MID_DHCPSV6);
#endif
    pMbuf = PMBUF_GetPMbuf(MID_DHCPC, ulIpPacketLen);

    if (NULL == pMbuf)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MALLOC_BUFF_FAIL);
        return VOS_ERR;
    }

    /* relay 发送消息 */
    ulRet = DHCPv6_RelaySendMsg(pMbuf, ucMsgType, ulPdpIndex);
    if (ulRet != VOS_OK)
    {
        /* 发消息失败计数 */
        DHCPV6_CalcFailRelayPacketNum(ucMsgType);
        (VOID)PMBUF_Destroy(pMbuf);
        return VOS_ERR;
    }

    /* 发消息成功计数 */
    DHCPV6_CalcSuccRelayPacketNum(ucMsgType);

    /* 上报消息跟踪 */
    DHCPV6_MsgTraceProcForRelay(pucDateMsg, ulDhcpMsgLen, ucMsgType, pstContext,
                                   M_EMS_TRC_SEND_MSG);

    return VOS_OK;
}


#define __MSG_PROCESS__
/*****************************************************************************
 *  函数名称:       DHCPV6_MsgPreProcForNotRelay
 *  初稿完成:       2012-08-03
 *  作    者:       y00170683
 *  函数功能:       对于非透传消息的预处理(消息检查,解封装,解码)
 *  输入参数:       UCHAR *pMbuf, ULONG ulMsgLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_MsgPreProcForNotRelay(UCHAR *pucSrcMsg, ULONG ulMsgLen,
                                                   SDB_GSPU_CONTEXT_S *pstContext,
                                                   DHCPV6S_MSG_INFO_S *pstMsgInfo)
{
    /* 检查IP-UDP头, 内层有计数不需要添加 */
    if(VOS_OK != DHCPV6_CheckIpUdp(pucSrcMsg, ulMsgLen))
    {
        return VOS_ERR;
    }

    /* 消息长度检查 */
    if (VOS_OK != DHCPV6_CheckMsgLen(pucSrcMsg, ulMsgLen))
    {
        return VOS_ERR;
    }

    /* 消息解封装 */
    DHCPV6_MsgUnpacket(pstMsgInfo, pucSrcMsg, ulMsgLen);

    /* 消息解码 */
    DHCPV6_MsgDecode(pstMsgInfo);

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_InfoReqProc
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       处理info-request消息
 *  输入参数:       UCHAR *pMbuf, ULONG ulMsgLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_InfoReqProc(UCHAR *pucSrcMsg, ULONG ulMsgLen,
                                    ULONG ulPdpIndex,
                                    SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    ULONG ulOptionFlag = 0;
    UDPHDR_S *pstUdp = NULL;
    ULONG ulMsgHeadLen = 0;
    DHCPV6S_MSG_INFO_S stMsgInfo = {0};

    /* 消息跟踪 */
    ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    pstUdp = (UDPHDR_S *)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN);
    DHCPV6_MsgTraceProc((DHCPV6_MSG_S*)(pucSrcMsg + ulMsgHeadLen),
            ulMsgLen - ulMsgHeadLen, pstContext, pstUdp, M_EMS_TRC_RECV_MSG);

    /* 消息预处理----消息检查,解封装,解码 */
    ulRet = DHCPV6_MsgPreProcForNotRelay(pucSrcMsg, ulMsgLen, pstContext, &stMsgInfo);
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /*  RFC3315
    15.12. Information-request Message

       Clients MUST discard any received Information-request messages.

       Servers MUST discard any received Information-request message that
       meets any of the following conditions:

       -  The message includes a Server Identifier option and the DUID in
          the option does not match the server's DUID.

       -  The message includes an IA option.
    */
    ulOptionFlag = stMsgInfo.stDhcpOptionInfo.ulOptionFlag ;
    if(0 != (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_IA_NA)) ||
        0 != (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_IA_TA)))
    {
        g_stDhcpv6Statistics.ulInfoReqWithIAErr++;
        return VOS_ERR;
    }

    /* 消息检查是否请求DNS */
    ulRet = DHCPV6_CheckForReqDns(&(stMsgInfo.stDhcpOptionInfo));
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }
    stMsgInfo.ucReqDnsFlg = VOS_TRUE;
    stMsgInfo.ulPdpIndex = ulPdpIndex;

    /* 回复reply消息 */
    ulRet = DHCPV6_SendMsgToClient(&stMsgInfo, pstContext, DHCPV6_MSG_TYPE_REPLY);
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 *  函数名称:       DHCPV6_InfoMsgProc
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       处理info-request消息
 *  输入参数:       UCHAR *pMbuf, ULONG ulMsgLen, ULONG ulPdpIndex,
                    SDB_GSPU_CONTEXT_S *pstContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_InfoMsgProc(UCHAR *pucSrcMsg, ULONG ulMsgLen, ULONG ulPdpIndex,
                                    SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    ULONG ulIpPacketLen = ulMsgLen - sizeof(FWD_TO_CTRL_HDR);
    UCHAR *pucDateMsg = pucSrcMsg + sizeof(FWD_TO_CTRL_HDR);

    if((E_NET_ELEMENT_ROLE_SGW == pstContext->ucUgwRole)
        && (DHCP_ENCAP_PMIP_GRE == pstContext->ucRightEncapType))
    {
        if (VOS_NULL_PTR != g_UEtoSGW_ulDHCPV6InformRequestNumAddr)
        {
            (VOID)PerfSetFamPerfCounterByAddress(g_UEtoSGW_ulDHCPV6InformRequestNumAddr, E_PERF_OBJECT_ADD, 1);
        }

        /*处理透传给PGW*/
        if (VOS_OK != DHCPv6_RelayMsg(pucDateMsg, ulIpPacketLen, ulPdpIndex, pstContext))
        {
            g_stDhcpv6Statistics.ulRelayStateInfoNum++;
            return VOS_ERR;
        }
        return VOS_OK;
    }

     /* 目前只处理这一个消息 */
    if (VOS_NULL_PTR != g_UEtoPGW_ulDHCPV6InformRequestNumAddr)
    {
        (VOID)PerfSetFamPerfCounterByAddress(g_UEtoPGW_ulDHCPV6InformRequestNumAddr, E_PERF_OBJECT_ADD, 1);
    }

    /* 处理info-request消息 */
    ulRet = DHCPV6_InfoReqProc(pucSrcMsg, ulMsgLen, ulPdpIndex, pstContext);
    return ulRet;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_ReplyMsgProc
 *  初稿完成:       2012-07-31
 *  作    者:       y00170683
 *  函数功能:       处理reply消息
 *  输入参数:       UCHAR *pMbuf, ULONG ulMsgLen
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_ReplyMsgProc(UCHAR *pucSrcMsg, ULONG ulMsgLen, ULONG ulPdpIndex,
                                      SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulIpPacketLen = ulMsgLen - sizeof(FWD_TO_CTRL_HDR);
    UCHAR *pucDateMsg = pucSrcMsg + sizeof(FWD_TO_CTRL_HDR);

    if((E_NET_ELEMENT_ROLE_SGW == pstContext->ucUgwRole)
        && (DHCP_ENCAP_PMIP_GRE == pstContext->ucRightEncapType))
    {
        if (VOS_NULL_PTR != g_SGWtoUE_ulDHCPV6AckNumAddr)
        {
            (VOID)PerfSetFamPerfCounterByAddress(g_SGWtoUE_ulDHCPV6AckNumAddr, E_PERF_OBJECT_ADD, 1);
        }

        /*处理透传给手机*/
        if (VOS_OK != DHCPv6_RelayMsg(pucDateMsg, ulIpPacketLen, ulPdpIndex, pstContext))
        {
            g_stDhcpv6Statistics.ulRelayStateReplyNum++;
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_SolicitMsgProc
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       处理solicit消息
 *  输入参数:       DHCPV6S_MSG_INFO_S *pstMsgInfo, SDB_GSPU_CONTEXT_S *pstContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_SolicitMsgProc(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                       SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;

    /* 检查是否携带rapid-commit*/
    if (0 != (pstMsgInfo->stDhcpOptionInfo.ulOptionFlag & (1 << DHCPV6_MSG_OPTION_RAPID_COMMIT)))
    {
        pstMsgInfo->ucReqRapidFlg = VOS_TRUE;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucReqRapidFlg = %u", pstMsgInfo->ucReqRapidFlg);

    /* 回复reply消息 */
    if (VOS_TRUE == pstMsgInfo->ucReqRapidFlg)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_2_STEP);
        ulRet = DHCPV6_SendMsgToClient(pstMsgInfo, pstContext, DHCPV6_MSG_TYPE_REPLY);
    }
    else    /* 回复advertise消息 */
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_4_STEP);
        ulRet = DHCPV6_SendMsgToClient(pstMsgInfo, pstContext, DHCPV6_MSG_TYPE_ADVERTISE);
    }

    return ulRet;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_RequstMsgProc
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       处理request消息
 *  输入参数:       DHCPV6S_MSG_INFO_S *pstMsgInfo, SDB_GSPU_CONTEXT_S *pstContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_RequstMsgProc(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                       SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;

    /* 回复reply消息 */
    ulRet = DHCPV6_SendMsgToClient(pstMsgInfo, pstContext, DHCPV6_MSG_TYPE_REPLY);

    return ulRet;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_SolicitReqMsgProc
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       处理solicit消息
 *  输入参数:       UCHAR *pucSrcMsg, ULONG ulMsgLen, ULONG ulPdpIndex, SDB_GSPU_CONTEXT_S *pstContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_SolicitReqMsgProc(UCHAR *pucSrcMsg, ULONG ulMsgLen,
                                            UCHAR ucMsgType, ULONG ulPdpIndex,
                                            SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    UDPHDR_S *pstUdp = NULL;
    ULONG ulMsgHeadLen = 0;
    DHCPV6S_MSG_INFO_S stMsgInfo = {0};

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucMsgType = %u", ucMsgType);

    /* 消息跟踪 */
    ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    pstUdp = (UDPHDR_S *)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN);
    DHCPV6_MsgTraceProc((DHCPV6_MSG_S*)(pucSrcMsg + ulMsgHeadLen),
            ulMsgLen - ulMsgHeadLen, pstContext, pstUdp, M_EMS_TRC_RECV_MSG);

    /* 角色与封装方式判断 */
    if ((E_NET_ELEMENT_ROLE_SGW == pstContext->ucUgwRole)
        || (DHCP_ENCAP_PMIP_GRE == pstContext->ucRightEncapType))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_ROLE_ENCAPE_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ucUgwRole = %u, ucRightEncapType = %u",
                             pstContext->ucUgwRole, pstContext->ucRightEncapType);
        return VOS_ERR;
    }

    /* 消息预处理----消息检查,解封装,解码 */
    ulRet = DHCPV6_MsgPreProcForNotRelay(pucSrcMsg, ulMsgLen, pstContext, &stMsgInfo);
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* 检查是否请求IA_PD,PD_EXCLUDE */
    ulRet = DHCPV6_CheckForReqIaPd(&(stMsgInfo.stDhcpOptionInfo));
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }
    stMsgInfo.ucReqPdFlg = VOS_TRUE;
    stMsgInfo.ulPdpIndex = ulPdpIndex;

    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_SOLICIT :
            ulRet = DHCPV6_SolicitMsgProc(&stMsgInfo, pstContext);
            break;

        case DHCPV6_MSG_TYPE_REQUEST :
            ulRet = DHCPV6_RequstMsgProc(&stMsgInfo, pstContext);
            break;

        default:
            ulRet = VOS_ERR;
            break;
    }
    return ulRet;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_GetMbufData
 *  初稿完成:       2012-08-04
 *  作    者:       y00170683
 *  函数功能:       从buf中取出消息
 *  输入参数:       VOID *pMsg
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_GetMbufData(PMBUF_S* pstMsgBuf, UCHAR **ppMsg, ULONG *pulMsgLen)
{
    ULONG ulMsgLen = 0;

    if (NULL == pstMsgBuf)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "pstMBuf = NULL!");
        return VOS_ERR;
    }

    /*获取报文长度和地址*/
    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (DHCPV6S_REV_MSG_MAXLEN < ulMsgLen)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "length(%u) > 4096!", ulMsgLen);
        return VOS_ERR;
    }

    *pulMsgLen = ulMsgLen;
    DHCP_MemZero(g_pucDhcpv6sRevBuff, DHCPV6S_REV_MSG_MAXLEN);

    /* 没有分片 BLOCK_NUMBER为 1 */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        *ppMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        /* 有分片，需要复制到连续内存 , 将MBUF内容复制到本地连续内存中 */
        if (VOS_OK != PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf, 0, ulMsgLen, g_pucDhcpv6sRevBuff))
        {
            DHCPV6S_DebugPrint(PTM_LOG_ERR, "copy buf from mbuf fail!");
            return VOS_ERR;
        }
        *ppMsg = g_pucDhcpv6sRevBuff;
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6_MsgProc
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       处理从DHCPV6的队列中读取出来的报文
 *  输入参数:       VOID *pMsg
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6_MsgProc(PMBUF_S *pstMsgBuf)
{
    ULONG ulMsgLen = 0;
    ULONG ulRet = VOS_OK;
    ULONG ulPdpIndex = 0;
    UCHAR *pucSrcMsg = NULL;
    DHCPV6_MSG_S *pDhcpv6Msg = NULL;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    ULONG ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    if (ulDhcpv6sPerfInitFinish != VOS_TRUE)
    {
        (VOID)DHCPV6S_OmInitial();
    }

    /* 从buff中取出消息和长度 */
    (VOID)DHCPV6_GetMbufData(pstMsgBuf, &pucSrcMsg, &ulMsgLen);
    if (NULL == pucSrcMsg)
    {
        return VOS_ERR;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulMsgLen = %u", ulMsgLen);

    g_stDhcpv6Statistics.ulTotal++;

    /* 因为外层ipv4头已经被转发剥掉,因此不能立即进行接口跟踪,必须借助上下文 */
    /* 获取PDP-index和上下文 */
    (VOID)DHCPV6_GetPdpIdxAndContext((FWD_TO_CTRL_HDR*)pucSrcMsg, &ulPdpIndex, &pstContext);
    if (NULL == pstContext)
    {
        return VOS_ERR;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulPdpIndex = %u, ucUgwRole = %u", ulPdpIndex, pstContext->ucUgwRole);

    /* 转发上送的报文包括UDP头和IP头，还包括了一个转发头 */
    pDhcpv6Msg = (DHCPV6_MSG_S*)(pucSrcMsg + ulMsgHeadLen);
    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucMsgType = %u", pDhcpv6Msg->ucMsgType);

    switch(pDhcpv6Msg->ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_INFO);
                ulRet = DHCPV6_InfoMsgProc(pucSrcMsg, ulMsgLen, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_REPLY:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_REPLY);
                ulRet = DHCPV6_ReplyMsgProc(pucSrcMsg, ulMsgLen, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_SOLICIT:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_SOLICIT);
                ulRet = DHCPV6_SolicitReqMsgProc(pucSrcMsg, ulMsgLen, pDhcpv6Msg->ucMsgType, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_REQUEST:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_REQUEST);
                ulRet = DHCPV6_SolicitReqMsgProc(pucSrcMsg, ulMsgLen, pDhcpv6Msg->ucMsgType, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_ADVERTISE:
        case DHCPV6_MSG_TYPE_CONFIRM:
        case DHCPV6_MSG_TYPE_RENEW:
        case DHCPV6_MSG_TYPE_REBIND:
        case DHCPV6_MSG_TYPE_RELEASE:
        case DHCPV6_MSG_TYPE_DECLINE:
        case DHCPV6_MSG_TYPE_RECONFIGURE:
        case DHCPV6_MSG_TYPE_RELAY_FORW:
        case DHCPV6_MSG_TYPE_RELAY_REPL:
                g_stDhcpv6Statistics.ulUnsupportMsgErr++;
                return VOS_ERR;
        default:
                g_stDhcpv6Statistics.ulUnknownMsgErr++;
                return VOS_ERR;
    }

    return ulRet;
}

