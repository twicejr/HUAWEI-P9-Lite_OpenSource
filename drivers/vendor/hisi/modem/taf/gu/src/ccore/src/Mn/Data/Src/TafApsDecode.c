


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsDecode.h"
#include "MnComm.h"
#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_DECODE_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/
/*AT AGENT模块消息处理函数对应表*/
const TAF_APS_DECODE_IPCP_PROC_STRU g_astTafApsDecIpcpProcTab[]=
{
    /* 操作ID */                            /* 解码处理函数 */
    {APS_PPP_IP_ADDR_ID,                    TAF_APS_DecodeIpcpIpAddr},
    {APS_PPP_PRI_DNS_ID,                    TAF_APS_DecodeIpcpPriDns},
    {APS_PPP_PRI_NBNS_ID,                   TAF_APS_DecodeIpcpPriNbns},
    {APS_PPP_SEC_DNS_ID,                    TAF_APS_DecodeIpcpSecDns},
    {APS_PPP_SEC_NBNS_ID,                   TAF_APS_DecodeIpcpSecNbns}
 };


/******************************************************************************
   5 函数实现
******************************************************************************/


VOS_UINT32 TAF_APS_DecodeIpcpIpAddr(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Peer IP地址长度必须等于6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_IP_ADDR_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpIpAddr: Invalid IPCP ADDRESS Option. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpIpAddr = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucIpAddr, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpPriDns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Primary DNS地址长度必须等于6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_PRI_DNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpPriDns: Invalid Pri DNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpPrimDns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucPrimDns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpPriNbns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Primary NBNS地址长度必须等于6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_PRI_NBNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpPriNbns: Invalid Pri NBNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpPrimNbns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucPrimNbns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpSecDns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Secondary DNS地址长度必须等于6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_SEC_DNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpSecDns: Invalid Sec DNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpSecDns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucSecDns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpSecNbns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
     Secondary NBNS地址长度必须等于6
     OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_SEC_NBNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpSecNbns: Invalid Sec NBNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpSecNbns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucSecNbns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


TAF_APS_DECODE_IPCP_PROC_FUNC TAF_APS_GetIpcpDecFuncByOptType(VOS_UINT8 ucOptType)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulTableSize;

    /* 从g_astTafApsDecIpcpProcTab中获取操作个数 */
    ulTableSize = sizeof(g_astTafApsDecIpcpProcTab)/sizeof(TAF_APS_DECODE_IPCP_PROC_STRU);

    /* g_astTafApsDecIpcpProcTab查表，进行解码分发 */
    for (i = 0; i < ulTableSize; i++)
    {
        if (g_astTafApsDecIpcpProcTab[i].ucOptType == ucOptType)
        {
            return g_astTafApsDecIpcpProcTab[i].pDecIpcpProcFunc;
        }
    }

    return VOS_NULL_PTR;
}


VOS_UINT32 TAF_APS_DecodeIpcpConfigReqPkt(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
)
{
    VOS_UINT8                           ucOptType;
    VOS_UINT8                           ucOptLen;
    VOS_UINT32                          ulResult;
    TAF_APS_DECODE_IPCP_PROC_FUNC       pDecIpcpFunc;

    ulResult     = VOS_OK;
    pDecIpcpFunc = VOS_NULL_PTR;

    /*-------------------------------------------------------------------
       处理 Peer IP/PRI DNS/SEC DNS/PRI NBNS/SEC NBNS
    -------------------------------------------------------------------*/
    while (usPktLen)
    {
        /*--------------------------------------------------------------
           OPTION长度必须等于6
           OPTION TYPE(1 byte) + OPTION LEN(1 btye) + VALUE(4 bytes)
        --------------------------------------------------------------*/
        /*lint -e961*/
        /* 获取IPCP Option类型 */
        ucOptType   = *pucProtocolPacket++;

        /* 获取IPCP Option长度 */
        ucOptLen    = *pucProtocolPacket++;
        /*lint +e961*/
        /* 如果剩余的IPCP Packet的长度比该IPCP Option的长度小, 则直接丢弃 */
        if (usPktLen < ucOptLen)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpConfigReqPkt: Invalid IPCP packet Len.");

            return VOS_ERR;
        }

        /* 如果IPCP Option的长度为0, 则直接丢弃 */
        if (0 == ucOptLen)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpConfigReqPkt: IPCP option length is zero.");

            return VOS_ERR;
        }

        /* 查找解码表中解码的操作 */
        pDecIpcpFunc = TAF_APS_GetIpcpDecFuncByOptType(ucOptType);
        if (VOS_NULL_PTR != pDecIpcpFunc)
        {
            ulResult = pDecIpcpFunc(pstIpcpInfo, pucProtocolPacket, ucOptLen);
            if (VOS_ERR == ulResult)
            {
                TAF_ERROR_LOG(WUEPS_PID_TAF,
                              "TAF_APS_DecodeIpcpConfigReqPkt: IPCP option decode error.");

                return VOS_ERR;
            }
        }
        else
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF,
                             "TAF_APS_DecodeIpcpConfigReqPkt: Option type not supported %d", ucOptType);
        }

        /* 前面解码时已经跳过了OPTION的头 */
        pucProtocolPacket += (ucOptLen - TAF_APS_PPP_IPCP_OPTION_HEAD_LEN);

        usPktLen -= ucOptLen;

    }

    return VOS_OK;
}



VOS_UINT32 TAF_APS_DecodeIpcpPkt(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucIpcpPkt,
    VOS_UINT16                          usIpcpPktLen
)
{
    VOS_UINT8                           ucConfigType;
    VOS_UINT8                           ucIdentifier;
    VOS_UINT16                          usLength;

    while (usIpcpPktLen > 0)
    {
        /*lint -e961*/
        /* 获取Config type */
        ucConfigType  = *pucIpcpPkt++;

        /* 获取Identifier */
        ucIdentifier  = *pucIpcpPkt++;
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
                         "TAF_APS_DecodeIpcpPkt: Identifier:", ucIdentifier);

        /* 获取Packet length */
        usLength  = (*pucIpcpPkt++) << 8;
        usLength |= *pucIpcpPkt++;
        /*lint +e961*/
        if (usIpcpPktLen < usLength)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpPkt: Invalid packet length.");

            return VOS_ERR;
        }

        usIpcpPktLen -= usLength;

        if (usLength < APS_PCO_CONFIG_HDR_LEN)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpPkt: Invalid IPCP packet length.");

            return VOS_ERR;
        }

        /* 从包长度中减去CONFIG_HDR_LEN */
        usLength -= APS_PCO_CONFIG_HDR_LEN;

        /* 只处理CONFIG_REQ, 其它的跳过 */
        switch (ucConfigType)
        {
            case APS_PPP_CODE_REQ:
                TAF_NORMAL_LOG(WUEPS_PID_TAF,
                               "TAF_APS_DecodeIpcpPkt: CONFIG_REQ IPCP pkt.");
                if (VOS_OK != TAF_APS_DecodeIpcpConfigReqPkt(pstIpcpInfo,
                                                             pucIpcpPkt,
                                                             usLength))
                {
                    return VOS_ERR;
                }

                pucIpcpPkt += usLength;

                break;

            default:

                TAF_WARNING_LOG1(WUEPS_PID_TAF,
                                 "TAF_APS_DecodeIpcpPkt: Invalid IPCP code, Ignore. Type:", ucConfigType);
                pucIpcpPkt += usLength;

                break;
        }
    }

    return VOS_OK;
}



VOS_UINT32 TAF_APS_DecodePapInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    VOS_UINT8                           aucPapReqBuf[],
    VOS_UINT16                          usPapReqLen
)
{
    VOS_UINT8                           ucLoc;
    TAF_APS_PAP_PARAM_STRU             *pstPapParam;

    ucLoc = 0;
    pstPapParam = &pstAuthInfo->unAuthParam.stPapParam;

    /* 鉴权的长度为0,则退出 */
    if (0 == usPapReqLen)
    {
        return VOS_OK;
    }

   /***************************************************************
   AUTH_PAP (RFC 1334)
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Code      |  Identifier   |            Length             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   | Peer-ID Length|  Peer-Id ...
   +-+-+-+-+-+-+-+-+-+-+-+-+
   | Passwd-Length |  Password ...
   +-+-+-+-+-+-+-+-+-+-+-+-+-+
   ****************************************************************/

    pstAuthInfo->ucAuthId   = aucPapReqBuf[TAF_APS_PPP_PAP_CODE_LEN];

    /* 跳过CODE1字节,Identifier1字节,长度2字节中的2个字节 */
    ucLoc += TAF_APS_PPP_PAP_HEAD_OFFSET;

    /* 处理UserName */
    if (aucPapReqBuf[ucLoc] > TAF_MAX_USERNAME_LEN)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodePapInfo: USERNAME LEN LARGER THEN MAX. Len:", aucPapReqBuf[ucLoc]);
        return  VOS_ERR;
    }
    else
    {
        /*lint -e961*/
        pstPapParam->ucUsernameLen = aucPapReqBuf[ucLoc++];
        /*lint +e961*/
        /* 有UserName */
        if (0 != pstPapParam->ucUsernameLen)
        {
            PS_MEM_CPY(pstPapParam->aucUsername,
                       &aucPapReqBuf[ucLoc],
                       pstPapParam->ucUsernameLen);
        }

        /* 跳过USERNAME */
        ucLoc += pstPapParam->ucUsernameLen;
    }

    /* 处理PassWord */
    if (aucPapReqBuf[ucLoc] > TAF_MAX_PASSCODE_LEN)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodePapInfo: PASSWORD LEN LARGER THEN MAX. Len:", aucPapReqBuf[ucLoc]);
        return  VOS_ERR;
    }
    else
    {
        /*lint -e961*/
        pstPapParam->ucPasswordLen = aucPapReqBuf[ucLoc++];
        /*lint +e961*/
        /* 有Password */
        if (0 != pstPapParam->ucPasswordLen)
        {
            PS_MEM_CPY(pstPapParam->aucPassword,
                       &aucPapReqBuf[ucLoc],
                       pstPapParam->ucPasswordLen);
        }

    }

    return  VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeChapInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    VOS_UINT8                           aucChapChallengeBuf[],
    VOS_UINT16                          usChapChallengeLen,
    VOS_UINT8                           aucChapResponseBuf[],
    VOS_UINT16                          usChapResponseLen
)
{
    TAF_APS_CHAP_PARAM_STRU            *pstChapParam;

    /******************************************************************
     AUTH_CHAP (RFC 1994)
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |    Data ...
     +-+-+-+-+

     1. challenge_info & challenge_info_len
     2. challenge_name & challenge_name_len
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Value-Size   |  Value ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Name ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     Value ---> challenge_info
     Name  ---> challenge_name

     3. response_info & response_len
     4. response_name & response_name_len
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Value-Size   |  Value ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Name ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     Value ---> response_info
     Name  ---> response_name
    ******************************************************************/

    pstChapParam = &pstAuthInfo->unAuthParam.stChapParam;

    /*目前的实现中，必然要有challenge和response报文*/
    if ( (0 == usChapChallengeLen)
      || (0 == usChapResponseLen) )
    {
        return VOS_ERR;
    }

    /*******************************************************************
     The Response Value is the one-way hash calculated over a stream of
     octets consisting of the Identifier, followed by (concatenated with)
     the "secret", followed by (concatenated with) the Challenge Value.
     The length of the Response Value depends upon the hash algorithm
     used (16 octets for MD5). Refer to RFC[1994] section 4.1.
    ******************************************************************/
    pstAuthInfo->ucAuthId   = aucChapResponseBuf[TAF_APS_PPP_CHAP_CODE_LEN];

    /* PPP 带下来的chap challenge buffer 的结构为:
       code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
    /* 拷贝challenge value,长度固定为16字节 */
    pstChapParam->ulChallengeLen = aucChapChallengeBuf[TAF_APS_PPP_CHAP_HEAD_OFFSET];

    if (TAF_APS_PPP_CHAP_CHALLNGE_LEN != pstChapParam->ulChallengeLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeChapInfo: Challenge value len error. Len:", pstChapParam->ulChallengeLen);
        return VOS_ERR;
    }

    PS_MEM_CPY(pstChapParam->aucChallenge,
               &aucChapChallengeBuf[TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET],
               pstChapParam->ulChallengeLen);

    /* 拷贝challenge name */
    pstChapParam->ulChallengeNameLen = (VOS_UINT32)((usChapChallengeLen - TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET) - pstChapParam->ulChallengeLen);

    if (pstChapParam->ulChallengeNameLen > TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN)
    {
        pstChapParam->ulChallengeNameLen = TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN;
    }

    PS_MEM_CPY(pstChapParam->aucChallengeName,
               &aucChapChallengeBuf[TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET + pstChapParam->ulChallengeLen],
               pstChapParam->ulChallengeNameLen);

    /* PPP 带下来的chap response buffer 的结构为:
       code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
    /* 拷贝response value,长度固定为16字节 */
    pstChapParam->ulResponseLen = aucChapResponseBuf[TAF_APS_PPP_CHAP_HEAD_OFFSET];

    if (TAF_APS_PPP_CHAP_RESPONSE_LEN != pstChapParam->ulResponseLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeChapInfo: Response value len error. Len:", pstChapParam->ulResponseLen);
        return VOS_ERR;
    }

    PS_MEM_CPY(pstChapParam->aucResponse,
               &aucChapResponseBuf[TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET],
               pstChapParam->ulResponseLen);

    /* 拷贝response name */
    pstChapParam->ucResponseNameLen = (VOS_UINT8)((usChapResponseLen - TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET) - pstChapParam->ulResponseLen);

    if (pstChapParam->ucResponseNameLen > TAF_MAX_USERNAME_LEN)
    {
        pstChapParam->ucResponseNameLen = TAF_MAX_USERNAME_LEN;
    }

    PS_MEM_CPY(pstChapParam->aucResponseName,
               &aucChapResponseBuf[TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET + pstChapParam->ulResponseLen],
               pstChapParam->ucResponseNameLen);

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeAuthInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU  *pstPppAuthConfig
)
{
    VOS_UINT8                           ucAuthType;
    VOS_UINT32                          ulResult;

    if (VOS_NULL_PTR == pstAuthInfo)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_APS_DecodeAuthInfo: pstPppAuthInfo NULL_PTR!");
        return VOS_ERR;
    }

    /* 目标结构初始化 */
    PS_MEM_SET(pstAuthInfo, 0x00, sizeof(TAF_APS_AUTH_INFO_STRU));

   /***************************************************************
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Code      |  Identifier   |            Length             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   Code       => AuthType
   ****************************************************************/

    ucAuthType = pstPppAuthConfig->enAuthType;

    switch(ucAuthType)
    {
        case PPP_NO_AUTH_TYPE:

            pstAuthInfo->enAuthType = TAF_PDP_AUTH_TYPE_NONE;
            ulResult = VOS_OK;

            break;

        case PPP_PAP_AUTH_TYPE:

            pstAuthInfo->enAuthType = TAF_PDP_AUTH_TYPE_PAP;
            ulResult = TAF_APS_DecodePapInfo(pstAuthInfo,
                                             pstPppAuthConfig->enAuthContent.stPapContent.aucPapReqBuf,
                                             pstPppAuthConfig->enAuthContent.stPapContent.usPapReqLen);
            break;

        case PPP_CHAP_AUTH_TYPE:

            pstAuthInfo->enAuthType = TAF_PDP_AUTH_TYPE_CHAP;
            ulResult = TAF_APS_DecodeChapInfo(pstAuthInfo,
                                              pstPppAuthConfig->enAuthContent.stChapContent.aucChapChallengeBuf,
                                              pstPppAuthConfig->enAuthContent.stChapContent.usChapChallengeLen,
                                              pstPppAuthConfig->enAuthContent.stChapContent.aucChapResponseBuf,
                                              pstPppAuthConfig->enAuthContent.stChapContent.usChapResponseLen);
            break;

        default:

            TAF_ERROR_LOG1(WUEPS_PID_TAF,
                          "TAF_APS_DecodeAuthInfo: Invalid Auth type ", ucAuthType);
            ulResult = VOS_ERR;

            break;
    }

    return ulResult;
}


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



