



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "IpComm.h"
#include  "IpIpmGlobal.h"
#include  "msp_at.h"
#if (FEATURE_ON == FEATURE_LTE)
#include  "msp_diag.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IPCOMM_C    /*待修改*/
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

VOS_UINT8 g_aucNdAllNodesMulticaseAddr[IP_IPV6_ADDR_LEN] = {0xff, 0x02, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x01};
VOS_UINT8 g_aucNdAllRoutersMulticaseAddr[IP_IPV6_ADDR_LEN] = {0xff, 0x02, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x02};

VOS_UINT8 g_aucNdAllNodesMacAddr[IP_MAC_ADDR_LEN] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x01};
VOS_UINT8 g_aucNdAllRoutersMacAddr[IP_MAC_ADDR_LEN] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x02};


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 函 数 名  : ND_CheckEpsIdValid
 功能描述  : 构造link-local地址
 输入参数  : VOS_UINT8 *pucLinkLocalAddr
             VOS_UINT8 *pucIfId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

  2.日    期   : 2013年1月10日
    作    者   : y00151394
    修改内容   : DSDA输入参数修改。EpsId为高2bit为ModemID，低6bit为EpsbId。

*****************************************************************************/
VOS_UINT32 ND_CheckEpsIdValid(VOS_UINT8 ucExEpsId)
{
    VOS_UINT8       ucEpsId;
    VOS_UINT16      usModemId;

    usModemId = ND_GET_MODEMID_FROM_EXEPSID(ucExEpsId);
    if (usModemId >= MODEM_ID_BUTT)
    {
        return PS_FAIL;
    }

    ucEpsId = ND_GET_EPSID_FROM_EXEPSID(ucExEpsId);
    if ((ucEpsId < ND_MIN_EPSB_ID)
                || (ucEpsId > ND_MAX_EPSB_ID))
    {
        return IP_FAIL;
    }

    return IP_SUCC;
}

/*****************************************************************************
 函 数 名  : IP_BuildLinkLocalAddr
 功能描述  : 构造link-local地址
 输入参数  : VOS_UINT8 *pucLinkLocalAddr
             VOS_UINT8 *pucIfId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IP_BuildLinkLocalAddr
(
    VOS_UINT8 *pucLinkLocalAddr,
    const VOS_UINT8 *pucIfId
)
{
    /* 构造link-local address */
    IP_SetUint16Data(pucLinkLocalAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    IP_MEM_CPY(&pucLinkLocalAddr[ND_IPV6_IF_OFFSET], pucIfId, ND_IPV6_IF_LEN);
}

/*****************************************************************************
 函 数 名  : IP_BuildIPv6Header
 功能描述  : 为ICMPv6消息构造IP header，不支持扩展头
 输入参数  :
             VOS_UINT8                  *pucIpv6
             IPV6_PSEDUOHEADER_STRU     *pstPseduoHeader
             VOS_UINT8                  *pucInterfaceId
             VOS_UINT32                 ulUpperLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IP_BuildIPv6Header
(
    VOS_UINT8               *pucIpv6,
    IPV6_PSEDUOHEADER_STRU  *pstPseduoHeader,
    const VOS_UINT8         *pucInterfaceId,
    VOS_UINT32               ulUpperLength
)
{
    VOS_UINT8    aucLinkLocalAddr[IP_IPV6_ADDR_LEN] = {0};

    /* 构造link-local address */
    IP_BuildLinkLocalAddr(aucLinkLocalAddr, pucInterfaceId);

    /* 设置IP版本号 */
    *pucIpv6 = IP_VERSION_6 << 4;

    /* 设置Payload，没有扩展头 */
    IP_SetUint16Data(pucIpv6 + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET, ulUpperLength);

    /* 设置next header */
    *(pucIpv6 + IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET) = IP_HEAD_PROTOCOL_ICMPV6;

    /* Hop Limit 255 */
    *(pucIpv6 + IP_IPV6_BASIC_HOP_LIMIT_OFFSET) = IP_IPV6_ND_HOP_LIMIT;

    IP_MEM_CPY(pucIpv6 + IP_IPV6_SRC_ADDR_OFFSET, aucLinkLocalAddr, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pucIpv6 + IP_IPV6_DST_ADDR_OFFSET, g_aucNdAllRoutersMulticaseAddr, IP_IPV6_ADDR_LEN);

    /* 为计算checksum构造pseudo-header */
    PS_MEM_CPY(pstPseduoHeader->aucIPSrc, aucLinkLocalAddr, IP_IPV6_ADDR_LEN);
    PS_MEM_CPY(pstPseduoHeader->aucIPDes, g_aucNdAllRoutersMulticaseAddr, IP_IPV6_ADDR_LEN);
    IP_SetUint32Data((VOS_UINT8*)&pstPseduoHeader->ulUpperLength, ulUpperLength);
    pstPseduoHeader->ucNextHead = IP_HEAD_PROTOCOL_ICMPV6;

}

/*****************************************************************************
 Function Name   : IP_ND_FormIPv6HeaderMsg
 Description     : IPv6报头设置
 Input           : aucSrcIPAddr --- 源IP地址
                   aucDstIPAddr --- 目的IP地址
                   ulPduLen     --- 有效负载长度
 Output          : pucData --- 报文缓冲指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
/*lint -e830*/
/*lint -e438*/
VOS_VOID IP_ND_FormIPv6HeaderMsg
(
    const VOS_UINT8                    *aucSrcIPAddr,
    const VOS_UINT8                    *aucDstIPAddr,
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                          *pucData,
    VOS_UINT8                           ucType
)
{
    /* 版本 */
    *pucData = (VOS_UINT8)((IP_VERSION_6 << IP_MOVEMENT_4_BITS) & IP_IPDATA_HIGH_4_BIT_MASK);
    pucData++;

    /* 传输类型、流标签 */
    pucData += 3;

    /* 有效负载长度 */
    IP_SetUint16Data(pucData, (VOS_UINT16)ulPduLen);
    pucData += 2;

    /* 下一报头 */
    *pucData = ucType;
    pucData++;

    /* 跳限制 */
    *pucData = IP_IPV6_ND_HOP_LIMIT;
    pucData++;

    /* 源地址 */
    IP_MEM_CPY( pucData,
                aucSrcIPAddr,
                IP_IPV6_ADDR_LEN);
    pucData += IP_IPV6_ADDR_LEN;

    /* 目的地址 */
    IP_MEM_CPY( pucData,
                aucDstIPAddr,
                IP_IPV6_ADDR_LEN);
    pucData += IP_IPV6_ADDR_LEN;
}
/*lint +e830*/
/*lint +e438*/
/*****************************************************************************
 函 数 名  : IP_IsValidRAPacket
 功能描述  : RA合法性检查
 输入参数  : const VOS_UINT8                    *pucIpMsg
             VOS_UINT32                         ulTypeOffset
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
IP_BOOL_ENUM_UINT8 IP_IsValidRAPacket
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                         ulTypeOffset
)
{
    VOS_UINT32                          ulTmp;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FALSE);

    /* link-local source address */
    IP_GetUint16Data(ulTmp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET);
    if(IP_IPV6_LINK_LOCAL_PREFIX != (ulTmp & IP_IPV6_LINK_LOCAL_MASK))
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidRAPacket: Illegal source address:!", ulTmp);
        return IP_FALSE;
    }

    /* Hop Limit 255 */
    ulTmp = *(pucIpMsg + IP_IPV6_BASIC_HOP_LIMIT_OFFSET);
    if(IP_IPV6_ND_HOP_LIMIT != ulTmp)
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidRAPacket: Illegal Hop Limit:!", ulTmp);
        return IP_FALSE;
    }

    /* CODE 0 */
    ulTmp = *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CODE_OFFSET);
    if(IP_IPV6_ND_VALID_CODE != ulTmp)
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidRAPacket: Illegal ICMPv6 CODE:!", ulTmp);
        return IP_FALSE;
    }

    return IP_TRUE;
}

/*****************************************************************************
 Function Name   : IP_GetIpv6UpLayerProtocol
 Description     : 获取IPv6上层协议
 Input           : pucIpMsg---------------------IPv6数据包首地址
                   usPayLoad--------------------IPv6数据包payload长度
 Output          : pucNextHeader----------------下一头类型指针
                   pulDecodedLen----------------已译码长度指针
 Return          : IP_ERR_ENUM_UINT32

 History         :
    1.lihong00150010      2011-03-25  Draft Enact

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_GetIpv6UpLayerProtocol
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT16                          usPayLoad,
    VOS_UINT8                          *pucNextHeader,
    VOS_UINT32                         *pulDecodedLen
)
{
    const VOS_UINT8                    *pucIpMsgTemp    = pucIpMsg;
    VOS_UINT8                           ucNextHeader    = IP_NULL;
    VOS_UINT8                           ucExtHeaderLen  = IP_NULL;
    VOS_UINT16                          usDecodeLen     = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FAIL);
    IP_ASSERT_RTN(VOS_NULL_PTR != pucNextHeader, IP_FAIL);
    IP_ASSERT_RTN(VOS_NULL_PTR != pulDecodedLen, IP_FAIL);

    /* 获取nextheader */
    ucNextHeader = *(pucIpMsgTemp + IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET);

    pucIpMsgTemp = pucIpMsgTemp + IP_IPV6_HEAD_LEN;

    /* 已跳过的数据包长度小于ulIpMsgLen */
    while (usDecodeLen <= usPayLoad)
    {
        switch (ucNextHeader)
        {
            case IP_EXTENSION_HEADER_TYPE_FRAGMENT/* 分段头 */:
            case IP_EXTENSION_HEADER_TYPE_AH/* AH头 */:
            case IP_EXTENSION_HEADER_TYPE_ESP/* ESP头 */:
                *pucNextHeader = ucNextHeader;
                *pulDecodedLen = usDecodeLen + IP_IPV6_HEAD_LEN;
                return IP_SUCC;
            case IP_EXTENSION_HEADER_TYPE_HOPBYHOP/* 逐跳选项头 */:
            case IP_EXTENSION_HEADER_TYPE_DESTINATION/* 目的地选项头 */:
            case IP_EXTENSION_HEADER_TYPE_ROUTING/* 选路头 */:

                /* 当前扩展头中的下一跳 */
                ucNextHeader =  *(pucIpMsgTemp + IP_IPV6_EXT_HEAD_NEXT_HEAD_OFFSET);

                /* 读取扩展头中的长度信息，跳过此扩展头 */
                ucExtHeaderLen = *(pucIpMsgTemp + IP_IPV6_EXT_HEAD_LEN_OFFSET);

                pucIpMsgTemp = pucIpMsgTemp + IP_GetExtensionLen(ucExtHeaderLen);
                usDecodeLen = usDecodeLen + IP_GetExtensionLen(ucExtHeaderLen);

                if (usPayLoad < usDecodeLen)
                {
                    IPND_WARNING_LOG(ND_TASK_PID, "IP_GetIpv6UpLayerProtocol: Lenth Error!");
                    return IP_FAIL;
                }

                break;
            default:
                *pucNextHeader = ucNextHeader;
                *pulDecodedLen = usDecodeLen + IP_IPV6_HEAD_LEN;
                return IP_SUCC;
        }
    }

    return IP_FAIL;
}

/*****************************************************************************
 Function Name   : IP_AffirmNdParam
 Description     : 确认ND报文参数的有效性
 Input           : pucIpMsg ----------------  报文数据区指针
                   ulTypeOffset ------------  ICMPv6报头偏移量
 Output          : None
 Return          : IP_ERR_ENUM_UINT32

 History         :
    1.sunli 00180715      2011-04-12  Draft Enact

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_AffirmNdParam
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulTypeOffset
)
{
    VOS_UINT32                          ulTmp           = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, PS_FALSE);

    /* Hop Limit 255 */
    ulTmp = *(pucIpMsg + IP_IPV6_BASIC_HOP_LIMIT_OFFSET);
    if(IP_IPV6_ND_HOP_LIMIT != ulTmp)
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_AffirmNdParam: Illegal Hop Limit:!", ulTmp);
        return IP_FAIL;
    }

    /* CODE 0 */
    ulTmp = *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CODE_OFFSET);
    if(IP_IPV6_ND_VALID_CODE != ulTmp)
    {
        IPND_INFO_LOG1(ND_TASK_PID, "IP_AffirmNdParam: Illegal ICMPv6 CODE:!", ulTmp);
        return IP_FAIL;
    }

    return IP_SUCC;
}


/*****************************************************************************
 Function Name   : IP_IsIcmpv6Packet
 Description     : 判定是否为ICMPv6包
 Input           : pucIpMsg---------------------IP数据包首地址
                   ulIpMsgLen-------------------IP数据包长度
 Output          : pulDecodedLen----------------已译码长度指针
 Return          : IP_BOOL_ENUM_UINT8

 History         :
    1.lihong00150010      2011-03-25  Draft Enact

*****************************************************************************/
VOS_UINT32                          g_ulCnNd = 0;

IP_BOOL_ENUM_UINT8 IP_IsIcmpv6Packet
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen,
    VOS_UINT32                         *pulDecodedLen
)
{
    VOS_UINT8                           ucProtocol      = IP_NULL;
    VOS_UINT8                           ucIpVersion     = IP_NULL;
    IP_ERR_ENUM_UINT32                  ulRslt          = IP_FAIL;
    VOS_UINT32                          ulDecodedLen    = IP_NULL;
    VOS_UINT16                          usPayLoad       = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FALSE);
    IP_ASSERT_RTN(VOS_NULL_PTR != pulDecodedLen, IP_FALSE);

    /* 获取IP版本号 */
    ucIpVersion = IP_GetIpVersion(pucIpMsg);

    /* 如果版本号不是IPV6，则不是ICMPv6包 */
    if (IP_VERSION_6 != ucIpVersion)
    {
        IPND_INFO_LOG1(ND_TASK_PID, "IP_IsIcmpv6Packet: IpVersion:", ucIpVersion);
        return IP_FALSE;
    }

    /* 获取PAYLOAD */
    IP_GetUint16Data(usPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    /* 长度合法检查 */
    if ((VOS_UINT32)(usPayLoad + IP_IPV6_HEAD_LEN) > ulIpMsgLen)
    {
        if(1 == g_ulCnNd)
        {
            VOS_UINT32 i=0;
            PS_PRINTF("\n***********IP_IsIcmpv6Packet: %d %d***********\n", usPayLoad + IP_IPV6_HEAD_LEN, ulIpMsgLen);
            for(i=0; (i + 8) <= 1500; i = i+8)
            {
                PS_PRINTF(" %02x %02x %02x %02x %02x %02x %02x %02x\n ",
                            pucIpMsg[i], pucIpMsg[i+1],
                            pucIpMsg[i+2], pucIpMsg[i+3],
                            pucIpMsg[i+4], pucIpMsg[i+5],
                            pucIpMsg[i+6], pucIpMsg[i+7]);
            }
            while(i < 1500)
            {
                PS_PRINTF(" %02x", pucIpMsg[i++]);
            }
            PS_PRINTF("\n**********************\n\n");

        }
        IPND_WARNING_LOG2(ND_TASK_PID, "IP_IsIcmpv6Packet: PayLoad beyond the msg::!", (usPayLoad + IP_IPV6_HEAD_LEN), ulIpMsgLen);
        return IP_FALSE;
    }

    /* 获取上层协议号 */
    ulRslt = IP_GetIpv6UpLayerProtocol(pucIpMsg, usPayLoad, &ucProtocol, &ulDecodedLen);
    if (IP_SUCC != ulRslt)
    {
        if(1 == g_ulCnNd)
        {
            VOS_UINT32 i=0;
            PS_PRINTF("\n***********IP_IsIcmpv6Packet: %d %d***********\n", usPayLoad + IP_IPV6_HEAD_LEN, ulIpMsgLen);
            for(i=0; (i + 8) <= 1500; i = i+8)
            {
                PS_PRINTF(" %02x %02x %02x %02x %02x %02x %02x %02x\n ",
                            pucIpMsg[i], pucIpMsg[i+1],
                            pucIpMsg[i+2], pucIpMsg[i+3],
                            pucIpMsg[i+4], pucIpMsg[i+5],
                            pucIpMsg[i+6], pucIpMsg[i+7]);
            }
            while(i < 1500)
            {
                PS_PRINTF(" %02x", pucIpMsg[i++]);
            }
            PS_PRINTF("\n**********************\n\n");

        }
        IPND_WARNING_LOG(ND_TASK_PID, "IP_IsIcmpv6Packet: Fail to get upper-layer protocol!");
        return IP_FALSE;
    }

    /* 判断上层协议号是否为Icmpv6 */
    if (IP_HEAD_PROTOCOL_ICMPV6 != ucProtocol)
    {
        IPND_INFO_LOG1(ND_TASK_PID, "IP_IsIcmpv6Packet: Protocol:", ucProtocol);
        return IP_FALSE;
    }

    *pulDecodedLen = ulDecodedLen;
    return IP_TRUE;
}

/*****************************************************************************
 函 数 名  : IP_ConstructICMPv6PseudoHeader
 功能描述  : 为计算checksum构造pseudo-header
 输入参数  : const NAS_IP_MSG_STRU              *pstIpMsg
             VOS_UINT32                         ulTypeOffset
             IPV6_PSEDUOHEADER_STRU             *pstPseduoHeader
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IP_ConstructICMPv6PseudoHeader
(
    const VOS_UINT8                   *pucMsgData,
    VOS_UINT32                  ulTypeOffset,
    IPV6_PSEDUOHEADER_STRU      *pstPseduoHeader
)
{
    VOS_UINT32                          ulLength        = IP_NULL;
    VOS_UINT32                          ulLengthTmp     = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucMsgData, 0);
    IP_ASSERT_RTN(VOS_NULL_PTR != pstPseduoHeader, 0);

    PS_MEM_CPY(pstPseduoHeader->aucIPSrc, pucMsgData+IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    PS_MEM_CPY(pstPseduoHeader->aucIPDes, pucMsgData+IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    pstPseduoHeader->ucNextHead = IP_HEAD_PROTOCOL_ICMPV6;

    /* 获取PAYLOAD */
    IP_GetUint16Data(ulLength, pucMsgData + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    ulLengthTmp = (ulTypeOffset - IP_IPV6_HEAD_LEN);
    if (ulLength > ulLengthTmp)
    {
        ulLength -= ulLengthTmp;
        IP_SetUint32Data((VOS_UINT8*)&pstPseduoHeader->ulUpperLength, ulLength);
    }
    else
    {
        ulLength = 0;
    }

    return ulLength;
}

/*****************************************************************************
 函 数 名  : IP_Unit16Sum
 功能描述  : 计算16bit SUM
 输入参数  : VOS_UINT8 *pucData
             VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  IP_Unit16Sum(const VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT32    ulCheckSum  = 0;
    VOS_UINT16   *pBuffer;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucData, 0);
    IP_ASSERT_RTN(0 != ulLen, 0);

    pBuffer = (VOS_UINT16 *)(VOS_VOID*)pucData;

    while(ulLen > 1)
    {
        ulCheckSum += *(pBuffer ++);
        ulLen      -= 2;
    }

    if (0 != ulLen)
    {
        ulCheckSum += *(VOS_UINT8*)pBuffer;
    }

    return ulCheckSum;
}

/*****************************************************************************
 函 数 名  : IPv6_Checksum
 功能描述  : 基于pseduo-header和upper-layer protocal计算checksum
 输入参数  : VOS_VOID                *pucPseduoHeader
             VOS_UINT8               *pucData
             VOS_UINT32              ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 IPv6_Checksum
(
    const VOS_VOID          *pucPseduoHeader,
    const VOS_UINT8         *pucData,
    VOS_UINT32              ulLen
)
{
    VOS_UINT32      ulCheckSum  = 0;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucPseduoHeader, 0);
    IP_ASSERT_RTN(VOS_NULL_PTR != pucData, 0);
    IP_ASSERT_RTN(0 != ulLen, 0);

    /* pseduo-header求和 */
    ulCheckSum += IP_Unit16Sum(pucPseduoHeader, sizeof(IPV6_PSEDUOHEADER_STRU));

    /* IPV6 Upper-layer package求和 */
    ulCheckSum += IP_Unit16Sum(pucData, ulLen);

    while(ulCheckSum >> 16)
    {
        ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    }

    return (VOS_UINT16)(~ulCheckSum);

}

/*****************************************************************************
 函 数 名  : IP_VerifyICMPv6
 功能描述  : 校验checksum
 输入参数  : const NAS_IP_MSG_STRU              *pstIpMsg
             VOS_UINT32                         ulTypeOffset
 输出参数  : 无
 返 回 值  : IP_ERR_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_VerifyICMPv6
(
    const VOS_UINT8        *pucIpMsg,
    VOS_UINT32             ulTypeOffset
)
{
    IPV6_PSEDUOHEADER_STRU  stPseduoHeader  = {{IP_NULL}};
    VOS_UINT32              ulLen;

    if ((VOS_NULL_PTR == pucIpMsg)
        || (IP_IPV6_HEAD_LEN > ulTypeOffset))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_VerifyICMPv6: Illegal parameter!");
        return IP_FAIL;
    }

    /* 判断是否需要检验，若没有携带checksum，作为非法包处理 */
    if ((0 == *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET))
        && (0 == *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET + 1)))
    {
        IPND_WARNING_LOG(ND_TASK_PID, "IP_VerifyICMPv6: NONE CHECKSUM!");
        return IP_FAIL;
    }

    /* 构造pseduo-header */
    if (0 == (ulLen = IP_ConstructICMPv6PseudoHeader(pucIpMsg, ulTypeOffset, &stPseduoHeader)))
    {
        return IP_FAIL;
    }

    /* 校验ICMPv6包 */
    if(0 != IPv6_Checksum(&stPseduoHeader, pucIpMsg + ulTypeOffset, ulLen))
    {
        IPND_WARNING_LOG(ND_TASK_PID, "IP_VerifyICMPv6: CHECKSUM Error!");
        return IP_FAIL;
    }

    return IP_SUCC;
}

/*****************************************************************************
 函 数 名  : IP_IsValidNdMsg
 功能描述  : 检查是否是合法的ND package
 输入参数  : const NAS_IP_MSG_STRU              *pstIpMsg
             VOS_UINT32                         *pulTypeOffset
 输出参数  : 无
 返 回 值  : IP_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : 00145177
    修改内容   : 新生成函数

*****************************************************************************/
IP_BOOL_ENUM_UINT8 IP_IsValidNdMsg
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen,
    VOS_UINT32                         *pulTypeOffset
)
{
    VOS_UINT32                          ulDecodedLen    = IP_NULL;
    VOS_UINT8                           ucType          = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FALSE);
    IP_ASSERT_RTN(VOS_NULL_PTR != pulTypeOffset, IP_FALSE);

    /* 判断是否为ICMPv6包 */
    if (IP_TRUE != IP_IsIcmpv6Packet(pucIpMsg, ulIpMsgLen, &ulDecodedLen))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_IsValidNdMsg: Not Icmpv6 Packet");
        return IP_FALSE;
    }

    if (IP_SUCC != IP_VerifyICMPv6(pucIpMsg, ulDecodedLen))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_IsValidNdMsg: Verify Fail");
        return IP_FALSE;
    }

    /* 取ICMPV6消息中的TYPE字段 */
    ucType = *(pucIpMsg + ulDecodedLen);
    if (IP_ICMPV6_TYPE_ECHOREQUEST != ucType)
    {
        if (IP_SUCC != IP_AffirmNdParam(pucIpMsg, ulDecodedLen))
        {
            IPND_ERROR_LOG(ND_TASK_PID, "IP_IsValidNdMsg: ND Param Affirm Fail");
            return IP_FALSE;
        }
    }

    /* TYPE是否位于[128,137] */
    if ((IP_ICMPV6_TYPE_ECHOREQUEST <= ucType)
        && (IP_ICMPV6_TYPE_REDIRECT >= ucType))
    {
        *pulTypeOffset = ulDecodedLen;
        return IP_TRUE;
    }

    IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidNdMsg: Invalid ICMPv6 Msg:!", ucType);

    return IP_FALSE;
}

/*****************************************************************************
 Function Name   : IP_BuildIcmpv6Checksum
 Description     : 生成ICMPv6报头的校验和
 Input           : pucIpMsg ----------------  报文数据区指针
                   ulTypeOffset ------------  ICMPv6报头偏移量
 Output          : pucIpMsg ----------------  在数据区ICMPv6报头位置添加校验和
 Return          : IP_ERR_ENUM_UINT32

 History         :
    1.sunli 00180715      2011-04-12  Draft Enact

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_BuildIcmpv6Checksum
(
    VOS_UINT8                          *pucIpMsg,
    VOS_UINT32                          ulTypeOffset
)
{
    IPV6_PSEDUOHEADER_STRU              stPseduoHeader = {{IP_NULL}};
    VOS_UINT32                          ulLen          = IP_NULL;
    VOS_UINT16                          usCheckSum     = IP_NULL;

    if ((VOS_NULL_PTR == pucIpMsg)
        || (IP_IPV6_HEAD_LEN > ulTypeOffset))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_BuildICMPv6Checksum: Illegal parameter!\n");
        return IP_FAIL;
    }

    /* 清除ICMPv6校验和字段 */
    pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET] = 0;
    pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET + 1] = 0;

    /* 构造pseduo-header */
    if (0 == (ulLen = IP_ConstructICMPv6PseudoHeader(pucIpMsg, ulTypeOffset, &stPseduoHeader)))
    {
        return IP_FAIL;
    }

    /* 生成ICMPv6包校验和 */
    usCheckSum = IPv6_Checksum(&stPseduoHeader, pucIpMsg + ulTypeOffset, ulLen);

    /*IP_SetUint16Data(&pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET], usCheckSum);*/
    *(VOS_UINT16 *)(VOS_VOID*)(&pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET]) = usCheckSum;

    return IP_SUCC;
}


/*huibo from V3R1 begin*/
/*****************************************************************************
 函 数 名  : TTF_NDIS_IP6_Checksum_Update
 功能描述  :
 输入参数  : pbuf   -- 待计算的IP报文内容指针
             ulBytes -- 长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月19日
    作    者   : Hefeng 163499
    修改内容   :
*****************************************************************************/
VOS_UINT32  TTF_NDIS_IP6_Checksum_Update(void *pbuf, VOS_UINT32 ulBytes)
{
    VOS_UINT32    ulSum;
    VOS_UINT32    ulNwords;
    VOS_UINT16   *buf;


    buf = (VOS_UINT16 *) pbuf;
    ulSum = 0;

    for (ulNwords = (VOS_UINT32)ulBytes >> 5; ulNwords > 0; ulNwords--)
    {
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
    }
    for (ulNwords = (VOS_UINT32)(ulBytes & 0x1f) >> 1; ulNwords > 0; ulNwords--)
    {
        ulSum += *buf++;
    }

    /* Add left-over byte, if any. */
    if (ulBytes & 0x01)
    {
        /*lint -e778*/
        ulSum += *buf & VOS_HTONS(0xff00);
        /*lint +e778*/
    }

    return ulSum;
}

/*****************************************************************************
 函 数 名  : TTF_NDIS_IP6_Pseudo_Header_Checksum_Update
 功能描述  :
 输入参数  : pstIp6SrcAddr - The source address.
              pstIp6DstAddr - The destination address.
              ulProto       - The protcol ID of the upper layer protocol.
              usLen         - The number of octets in the payload for which this is
                    pseudo header.
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月19日
    作    者   : Hefeng 163499
    修改内容   :
*****************************************************************************/
VOS_UINT32  TTF_NDIS_IP6_Pseudo_Header_Checksum_Update
(
    const NDIS_IP6_ADDR_STRU                 *pstIp6SrcAddr,
    const NDIS_IP6_ADDR_STRU                 *pstIp6DstAddr,
    VOS_UINT32                          ulProto,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulSum;

    ulSum  = pstIp6SrcAddr->in6.ausAddr[0];
    ulSum += pstIp6SrcAddr->in6.ausAddr[1];
    ulSum += pstIp6SrcAddr->in6.ausAddr[2];
    ulSum += pstIp6SrcAddr->in6.ausAddr[3];
    ulSum += pstIp6SrcAddr->in6.ausAddr[4];
    ulSum += pstIp6SrcAddr->in6.ausAddr[5];
    ulSum += pstIp6SrcAddr->in6.ausAddr[6];
    ulSum += pstIp6SrcAddr->in6.ausAddr[7];

    ulSum += pstIp6DstAddr->in6.ausAddr[0];
    ulSum += pstIp6DstAddr->in6.ausAddr[1];
    ulSum += pstIp6DstAddr->in6.ausAddr[2];
    ulSum += pstIp6DstAddr->in6.ausAddr[3];
    ulSum += pstIp6DstAddr->in6.ausAddr[4];
    ulSum += pstIp6DstAddr->in6.ausAddr[5];
    ulSum += pstIp6DstAddr->in6.ausAddr[6];
    ulSum += pstIp6DstAddr->in6.ausAddr[7];

    ulSum += VOS_HTONS(usLen);
    ulSum += VOS_HTONS(ulProto);

    return ulSum;
}

/*****************************************************************************
 函 数 名  : TTF_NDIS_IP6_Checksum_Finish
 功能描述  :
 输入参数  : ulSum - The accumulated 32 bit internet sum.
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月19日
    作    者   : Hefeng 163499
    修改内容   :
*****************************************************************************/
VOS_UINT16  TTF_NDIS_IP6_Checksum_Finish(VOS_UINT32 ulSum)
{
    /* Fold 32-bit sum to 16 bits. */
    while (ulSum >> 16)
    {
        ulSum = (ulSum & 0xffff) + (ulSum >> 16);
    }

    return (VOS_UINT16)~(VOS_UINT16)ulSum;
}


/*****************************************************************************
 函 数 名  : TTF_NDIS_Ipv6_CalcCheckSum
 功能描述  : 计算IP报文CheckSum
 输入参数  : pData         -  IPv6报文
              usLen         -  IPv6报文总长度
              pstDstIP6Addr - 目的IPv6地址
              pstSrcIP6Addr - 源IPv6地址
              ulProto       - IPv6报文类型
 输出参数  : 无
 返 回 值  : VOS_UINT16 - CheckSum值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月24日
    作    者   : Hefeng 163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TTF_NDIS_Ipv6_CalcCheckSum
(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen,
    const NDIS_IP6_ADDR_STRU           *pstIp6SrcAddr,
    const NDIS_IP6_ADDR_STRU           *pstIp6DstAddr,
    VOS_UINT32                          ulProto
)
{
    VOS_UINT32                          ulCheckSum;
    VOS_UINT32                          ulPseudoHdrChksum;
    VOS_UINT32                          ulFinalChksum;
    VOS_UINT16                          usStdIntelChksum;


    ulCheckSum          = TTF_NDIS_IP6_Checksum_Update(pData, usLen);
    ulPseudoHdrChksum   = TTF_NDIS_IP6_Pseudo_Header_Checksum_Update(pstIp6SrcAddr,
                                                    pstIp6DstAddr, ulProto, usLen);
    ulFinalChksum       = ulCheckSum + ulPseudoHdrChksum;
    usStdIntelChksum    = TTF_NDIS_IP6_Checksum_Finish(ulFinalChksum);

    return usStdIntelChksum;
}

/*****************************************************************************
 函 数 名  : TTF_NDIS_Ipv6GetDhcpOption
 功能描述  : Returns a specific option.
 输入参数  : pFirstOpt - Points to the first option in the packet.
             ulTotOptLen - Length in byte of ICMPv6 header + data.
             usNdOptCode - The option Code to find.
             lNumber - The number of the option (if the same option can occure
              multiple times).
 输出参数  : pOpt - Will point to the option when the function returns,
              or to VOS_NULL_PTR if the option was not found.
 返 回 值  :PS_SUCC - 成功
             PS_FAIL - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : 黄飞 62119
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TTF_NDIS_Ipv6GetDhcpOption
(
    IPV6_PKT_DHCP_OPT_HDR_STRU             *pFirstOpt,
    VOS_UINT16                              usTotOptLen,
    VOS_UINT16                              usNdOptCode,
    IPV6_PKT_DHCP_OPT_HDR_STRU            **pOpt,
    VOS_INT32                               lNumber
)
{
    VOS_UINT16                          usOptLen;


    *pOpt = pFirstOpt;

    while ( usTotOptLen > 0 )
    {
        usOptLen = VOS_NTOHS((*pOpt)->usDhcpOptLen);
        if ( usOptLen == 0 )
        {
            return PS_FAIL;
        }

        if ( VOS_NTOHS((*pOpt)->usDhcpOptCode) == usNdOptCode )
        {
            if (  lNumber == 0  )
            {
                return PS_SUCC;
            }

            lNumber--;
        }

        usTotOptLen    -= usOptLen ;
        *pOpt           = (IPV6_PKT_DHCP_OPT_HDR_STRU *)(VOS_VOID*)(((VOS_UINT8 *) *pOpt + usOptLen) + 4 );
    }

    *pOpt = VOS_NULL_PTR;


    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : TTF_NDIS_Ipv6InputEthHead
 功能描述  : 填充IP头部
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : Hefeng 163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TTF_NDIS_InputUDPHead
(
    VOS_UINT8                          *pBuf,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort,
    VOS_UINT16                          usUdpDataLen
)
{
    UDP_HEAD_ST        *pstUdpHdr = (UDP_HEAD_ST*)(VOS_VOID*)pBuf;

    if ( usUdpDataLen < sizeof(UDP_HEAD_ST) )
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstUdpHdr, 0, sizeof(UDP_HEAD_ST));
    pstUdpHdr->usSrcPort    = VOS_HTONS(usSrcPort);
    pstUdpHdr->usDstPort    = VOS_HTONS(usDstPort);
    pstUdpHdr->usLen        = VOS_HTONS(usUdpDataLen);
    pstUdpHdr->usCheck      = 0;

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

