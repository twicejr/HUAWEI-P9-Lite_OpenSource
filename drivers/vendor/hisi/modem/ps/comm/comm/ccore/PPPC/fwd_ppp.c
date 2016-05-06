/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : fwd_ppp.c
  版 本 号   : 初稿
  作    者   : zhangnan 68158
  生成日期   : 2007年07月19日
  最近修改   :
  功能描述   : PPP模块处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2007年07月14日
    作    者   : zhangnan 68158
    修改内容   : 创建文件

 2.日    期  : 2007-07-23
    作    者  :zhangna 68158
    内    容  :添加协议报文上送的封装

 3.日    期  : 2007-07-30
    作    者  :zhangna 68158
    内    容  修改宏的名称

 4.日    期  : 2007-08-02
    作    者  :zhangnan 68158
    内    容  封装上送信息头时,使用了新定义的 ENCAP_TOCP_INFO_S结构来表示封装的长度,用于更新MBUF
                新定义了临时变量 ENCAP_TOCP_INFO_S *pstEncapHd 用于指向封装信息头,方便 " 封装信息头宏 " 中的计算
                封装装的信息头采用主机序格式
 5.日    期  : 2008-01-29
    作    者  :zhangnan 68158
    内    容  :函数处理只返回结果不丢包，在外面调用处统一处理；增加一个返回值表示同步报文，在外面决定是否丢弃
 6.日    期  : 2008-02-15
    作    者  :zhangnan 68158
    内    容  :修改获取GTPU表字段的宏，优化为只有一个参数，减少计算

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "PppInterface.h"
#include "fwd_ppp_private.h"
#include "pppc_ctrl.h"
#include "fwd_ppp.h"
#include "TTFMem.h"
#include "TTFLink.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_FWD_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
PPP_REBUILD_INCOMPLETE_SLICE_STRU   g_stPppRebuildIncompleteSliceStat = {0};
VOS_UINT8                           g_aucPppRebuildSynSliceBuffer[3600];
VOS_UINT16                          g_usPppSynSliceBufUsedLen = 0;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : FWD_PppFillDataInfo
 功能描述  : 填写需要勾取的数据
 输入参数  : pstIP: 原始数据的ip信息指针
             pstUlDataInfo: 勾取的数据的指针
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-23
    作    者   : d00314740
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID FWD_PppFillDataInfo
(
    VOS_UINT8                          *pucPppData,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
)
{
    IP4_S                              *pstIp;
    VOS_UINT8                           ucIpHdLen;
    VOS_UINT32                          ulProtocol;
    VOS_UINT8                           ucIcmpType;
    VOS_UINT32                          ulIcmpOtherHd;

    if ((VOS_NULL_PTR == pucPppData) || (VOS_NULL_PTR == pstUlDataInfo))
    {
        PPPC_WARNING_LOG("null ptr when fill high layer data info");
        return;
    }

    pstIp       = (IP4_S *)pucPppData;
    ucIpHdLen   = pstIp->ip_chHLen * 4;
    ulProtocol  = pstIp->ip_chPr;

    PS_MEM_SET(pstUlDataInfo, 0x0, sizeof(PS_DATA_EXT_INFO_STRU));

    /* 性能优化，勾取trace.
        ucPri, ulBirthTime 暂未使用
        R方向 usStartSN, usEndSN 在rrlp 填写
        F方向 usStartSN, usEndSN 在ppp 填写*/
    pstUlDataInfo->enDataType   = (IPV4_VERSION == pstIp->ip_chVer) ?
        (PS_DATA_FLOW_TYPE_IPV4_PACKET) : (PS_DATA_FLOW_TYPE_IPV6_PACKET);

    if ((PS_DATA_HIGH_LAYER_TCP_TYPE != ulProtocol)
        && (PS_DATA_HIGH_LAYER_UDP_TYPE != ulProtocol)
        && (PS_DATA_HIGH_LAYER_ICMP_TYPE != ulProtocol)
        && (PS_DATA_HIGH_LAYER_ICMPV6_TYPE) != ulProtocol)
    {
        ulProtocol  = (IPV4_VERSION == pstIp->ip_chVer) ?
            (PS_DATA_HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE) : (PS_DATA_HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE);
    }

    pstUlDataInfo->stHighLayerInfo.ulChoice = ulProtocol;

    switch (ulProtocol)
    {
        case PS_DATA_HIGH_LAYER_TCP_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usIpId           = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usDataLen        = VOS_NTOHS(pstIp->ip_usLen);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usSrcPort
                = VOS_NTOHS(((PPP_TRACE_TCP4_STRU *)(pucPppData + ucIpHdLen))->usSrcPort);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usDstPort
                = VOS_NTOHS(((PPP_TRACE_TCP4_STRU *)(pucPppData + ucIpHdLen))->usDstPort);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.ulAckSeq
                = VOS_NTOHL(((PPP_TRACE_TCP4_STRU *)(pucPppData + ucIpHdLen))->ulAck);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.enIncludeHttp    = PS_FALSE;
            break;
        case PS_DATA_HIGH_LAYER_UDP_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usIpId           = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usDataLen        = VOS_NTOHS(pstIp->ip_usLen);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usSrcPort
                = VOS_NTOHS(((PPP_TRACE_UDP4_STRU *)(pucPppData + ucIpHdLen))->usSrcPort);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usDstPort
                = VOS_NTOHS(((PPP_TRACE_UDP4_STRU *)(pucPppData + ucIpHdLen))->usDstPort);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.enIncludeDns     = PS_FALSE;
            break;
        case PS_DATA_HIGH_LAYER_ICMP_TYPE:
            ucIcmpType    = ((PPP_TRACE_ICMP_STRU *)(pucPppData + ucIpHdLen))->ucType;
            ulIcmpOtherHd = VOS_NTOHL(((PPP_TRACE_ICMP_STRU *)(pucPppData + ucIpHdLen))->ulOtherHd);

            pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usIpId        = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usDataLen     = VOS_NTOHS(pstIp->ip_usLen);
            pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.ucType        = ucIcmpType;
            if ((ICMP_TYPE_ECHO_REPLY == (ICMP_TYPE_ENUM_UINT8)ucIcmpType)
                || (ICMP_TYPE_ECHO_REQUEST == (ICMP_TYPE_ENUM_UINT8)ucIcmpType))
            {
                pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usIcmpId  = PPPC_GET_HIGH_16_BITS(ulIcmpOtherHd);
                pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usIcmpSn  = PPPC_GET_LOW_16_BITS(ulIcmpOtherHd);
            }
            break;
        case PS_DATA_HIGH_LAYER_ICMPV6_TYPE:
            ucIcmpType    = ((PPP_TRACE_ICMP_STRU *)(pucPppData + ucIpHdLen))->ucType;

            pstUlDataInfo->stHighLayerInfo.u.stIcmpv6Info.ucType        = ucIcmpType;
            pstUlDataInfo->stHighLayerInfo.u.stIcmpv6Info.usDataLen     = VOS_NTOHS(pstIp->ip_usLen);
            break;
        case PS_DATA_HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stIpv4OtherTypeInfo.usIpId     = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stIpv4OtherTypeInfo.usDataLen  = VOS_NTOHS(pstIp->ip_usLen);
            break;
        case PS_DATA_HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stIpv4OtherTypeInfo.usDataLen  = VOS_NTOHS(pstIp->ip_usLen);
            break;
        default:
            PPPC_WARNING_LOG1("wrong protocol for ppp ul trace", ulProtocol);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : FWD_PppParse
 功能描述  : 更新参数，返回PPP头的长度
 输入参数  : VOS_UINT8 *pcuPppHead   PPP头
 输出参数  : VOS_UINT32 *pulHdLen    PPP头的长度
 返 回 值  : PPP_IS_DATA    :    数据报文
             PPP_IS_LCP_ECHO:    ECHO报文
             PPP_IS_LCP_SIG :    协商报文
             PPP_IS_ASYN    :    异步报文
             PPP_IS_OTHER_SIG  :   其他信令报文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppParse
(
    VOS_UINT8                          *pcuPppHead,
    VOS_UINT32                         *pulHdLen,
    FWD_PKT_TYPE_ENUM_UINT8            *penIpVersion
)
{
    VOS_UINT16 usPppHdFlg=0;
    VOS_UINT32 ulPPPHLen = 0;
    VOS_UINT32 ret = 0;
    *pulHdLen=0;
    /* 同异步检查 */
    if (PPP_H_ASYN == (*pcuPppHead))
    {
        return (PPP_PARSE_R_ASYN);
    }

    /*地址控制域判断,采用一字节对齐方式读,*/
    usPppHdFlg = pcuPppHead[0];
    usPppHdFlg = (PF_USHORT)((usPppHdFlg << 8)|(PF_USHORT)pcuPppHead[1]);
    if ( PPP_H_ACF ==  usPppHdFlg)
    {
        ulPPPHLen +=2;
        usPppHdFlg = pcuPppHead[ulPPPHLen+0];
        usPppHdFlg = (PF_USHORT)((usPppHdFlg << 8)|(PF_USHORT)pcuPppHead[ulPPPHLen+1]);
    }

    /*协议域判断*/
    /*Modified Start by lijun 00129916 2010-03-02 for AX4D13910 修改PPP解析流程*/
    /*数据报文，协议域无压缩*/
    if ((PPP_H_PF_IPV4 == usPppHdFlg) ||(PPP_H_PF_IPV6 == usPppHdFlg))
    {
        *penIpVersion = (PPP_H_PF_IPV4 == usPppHdFlg) ? FWD_PKT_TYPE_IPV4 : FWD_PKT_TYPE_IPV6;
        ulPPPHLen +=2;
        ret = PPP_PARSE_R_DATA;
    }
    /*数据报文、协议域压缩*/
    else if ((PPP_H_PFC_IPV4 == (PF_UCHAR)(usPppHdFlg >> 8)) ||(PPP_H_PFC_IPV6 == (PF_UCHAR)(usPppHdFlg >> 8)))
    {
        *penIpVersion = (PPP_H_PFC_IPV4 == (PF_UCHAR)(usPppHdFlg >> 8)) ? FWD_PKT_TYPE_IPV4 : FWD_PKT_TYPE_IPV6;
        ulPPPHLen +=1;
        ret = PPP_PARSE_R_DATA;
    }
    /*LCP报文*/
    else if (PPP_H_PF_LCP == usPppHdFlg)
    {
        PF_UCHAR *pucLcpData = VOS_NULL_PTR;
        PF_UCHAR ucLcpCode=0;
        ulPPPHLen +=2;
        pucLcpData = pcuPppHead + ulPPPHLen;
        ucLcpCode =  GET_CODE_FROM_LCP_PKT(pucLcpData);

        if (PPP_H_LCP_ECHOREQ == ucLcpCode)
        {
            ret = PPP_PARSE_R_LCP_ECHO_REQ;
        }
        /* begin: add by zhangnan 68158 at 2012-02-21 for PPP Echo 报文无法跟踪 */
        else if (PPP_H_LCP_ECHOREP == ucLcpCode)
        {
            ret = PPP_PARSE_R_LCP_ECHO_REPLY;
        }
        /* end  :add by zhangnan 68158 at 2012-02-21 for PPP Echo 报文无法跟踪 */
        else /*ucCode !=0X09 */
        {
            ret = PPP_PARSE_R_LCP_SIG;
        }
    }
    /*Added start by wangyixing 00167384 at 2013-2-4 for HSGW开发*/
    else if (PPP_H_PF_VSNP == usPppHdFlg)
    {
        /*偏移掉协议,协议域无压缩*/
        ulPPPHLen +=2;
        ret = PPP_PARSE_R_VSCP_DATA;
    }
    else if(PPP_H_PF_VSNP == (PF_UCHAR)(usPppHdFlg >> 8))
    {
        /*偏移掉协议,协议域压缩*/
        ulPPPHLen +=1;
        ret = PPP_PARSE_R_VSCP_DATA;
    }
    /*Added end by wangyixing 00167384 at 2013-2-4 for HSGW开发*/
    else
    {
        /*Modified by t00127644 for DTS2010073002901
        协议域后判断第一个字节高4bit是否>=8,如果>=,则认为是信令报文,上送PPP,否则认为报文非法,丢弃*/
        if(((usPppHdFlg>>12)&0xf)>= 8)
        {
            ret = PPP_PARSE_R_OTHER_SIG;
        }
        else
        {
            ret = PPP_PARSE_R_ERR_SIG;
        }
    }
    *pulHdLen = ulPPPHLen;
    return ret;
}

/*****************************************************************************
 函 数 名  : FWD_PppGetLcpMagicNum
 功能描述  : 获取本端魔术字
 输入参数  : 无

 输出参数  : pulPppMagicNum    魔术字
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppGetLcpMagicNum(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppMagicNum)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* 内部调用，保证入参非空 */
    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_908);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG("LCP is Null!");
        PPP_DBG_ERR_CNT(PPP_PHERR_857);
        return VOS_ERR;
    }

    *pulPppMagicNum = pstLcpInfo->stGotOptions.magicnumber;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FWD_PppDecap
 功能描述  : PPP报文解封装
 输入参数  : pstMBuf        PPP报文
             enPktType      报文类型
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID FWD_PppDecap
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
)
{
    VOS_UINT8                          *pucPppData;
    VOS_UINT8                          *pucLcpData ;
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulLcpMagicNum = 0;
    VOS_UINT32                          ulPPPType;
    VOS_UINT32                          lHdLen = 0;
    VOS_UINT32                          ulMagicNum;
    VOS_UINT32                          ulRet;
    PMBUF_S                            *pstSynMBuf = VOS_NULL_PTR;
    PMBUF_S                            *pstMBuf = VOS_NULL_PTR;
    FWD_PKT_TYPE_ENUM_UINT8             enIpVersion;
    PPPINFO_S                          *pstPppInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucMinBody = 8;  /* LCP报文最小长度为8 */
    VOS_UINT16                          usLcpLen = 0;

    /* 对解封装的PPP 包 计数 */
    PPP_DBG_OK_CNT(PPP_PHOK_1478);

    pucPppData  = pstData->pData;

    ulPPPType = FWD_PppParse( pucPppData, &lHdLen, &enIpVersion);

    PPPC_INFO_LOG3("FWD_PppDecap : lHdLen:0x%x, ulPPPType:0x%x\n", lHdLen, ulPPPType,ucPppId);

    switch (ulPPPType)
    {
        case PPP_PARSE_R_ASYN:

            PPP_DBG_ERR_CNT(PPP_PHERR_839);

            break;

        case PPP_PARSE_R_DATA:
            TTF_MEM_REMOVE_FROM_HDR(pstData, (VOS_UINT16)lHdLen);

            ulRet = PPPC_1XHrpdGetPdnId((VOS_UINT16)ucPppId, &ucPdnId);
            if (VOS_OK == ulRet)
            {
                PPP_SendRlpDlDatatoCds(usStartSeq, usEndSeq, ucPdnId, pstData, ucRatMode);
            }
            else
            {
                TTF_MemFree(MSPS_PID_PPPC,pstData);
                pstData = VOS_NULL_PTR;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1479);
            break;

        case PPP_PARSE_R_VSCP_DATA:


            /* 获取PDN ID */
            ucPdnId = pucPppData[lHdLen];
            lHdLen++;
            TTF_MEM_REMOVE_FROM_HDR(pstData, (VOS_UINT16)lHdLen);

            PPP_SendRlpDlDatatoCds(usStartSeq, usEndSeq, ucPdnId, pstData, ucRatMode);
            break;

        case PPP_PARSE_R_LCP_ECHO_REQ:

            pucLcpData = pucPppData + lHdLen;

            GET_LENGTH_FROM_LCP_PKT(pucLcpData, usLcpLen);
            if (usLcpLen < ucMinBody)
            {
                PPPC_WARNING_LOG1("Lcp Echo Req Len Error", usLcpLen);
                return;
            }

            /*下面的宏在读取MagicNumber时已经进行网络序到主机序的转换 */
            GET_MAGICNUM_FROM_LCP_PKT(pucLcpData,ulLcpMagicNum);
            ulRet   = FWD_PppGetLcpMagicNum(ucPppId, &ulMagicNum);
            if (VOS_OK != ulRet)
            {
                TTF_MemFree(MSPS_PID_PPPC,pstData);
                pstData = VOS_NULL_PTR;
                PPP_DBG_ERR_CNT(PPP_PHERR_840);
                (VOS_VOID)pstData;
                return;
            }

            /*修改原报文为ECHO_REPLY 报文*/
            pucLcpData[LCP_MAGICNUM_OFFSET+3] = (PF_UCHAR)(ulMagicNum & 0X000000FFL);
            pucLcpData[LCP_MAGICNUM_OFFSET+2] = (PF_UCHAR)((ulMagicNum & 0X0000FF00L)>>8);
            pucLcpData[LCP_MAGICNUM_OFFSET+1] = (PF_UCHAR)((ulMagicNum & 0X00FF0000L)>>16);
            pucLcpData[LCP_MAGICNUM_OFFSET+0] = (PF_UCHAR)((ulMagicNum & 0XFF000000L)>>24);
            pucLcpData[LCP_CODE_OFFSET] = PPP_H_LCP_ECHOREP;

            /* 获取PPPC控制块指针*/
            GETPPPINFOPTRBYRP(pstPppInfo, ucPppId);
            /* for pclint */
            if(VOS_NULL_PTR == pstPppInfo)
            {
                TTF_MemFree(MSPS_PID_PPPC, pstData);
                return ;
            }
            pstMBuf = PPPC_AdapterTtfMemorytoMBuf(pstData);
            /* 同/异步转换 */
            if (pstPppInfo->bSynAsyConvert)
            {
                pstMBuf = PPP_SynToAsy(pstMBuf, 0xffffffff);
                if (pstMBuf == VOS_NULL_PTR)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_836);
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Echo Reply Syn To Asy Error!!");
                    return;
                }
            }
            /* 发送报文 */
            ulRet = PPPC_ULSendNegoFrame(pstMBuf, pstPppInfo->ulRPIndex);
            if (VOS_ERR == ulRet)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_837);
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Send Echo Reply Fail!!");
                return;
            }
            (VOS_VOID)ulLcpMagicNum;
            return;

        case PPP_PARSE_R_LCP_ECHO_REPLY:
        case PPP_PARSE_R_LCP_SIG:
        case PPP_PARSE_R_OTHER_SIG:
            pstSynMBuf = PPPC_AdapterTtfMemorytoMBuf(pstData);
            PPP_Shell_ReceiveNegoPacket(pstSynMBuf, ucPppId);
            PMBUF_Destroy(pstSynMBuf);
            pstSynMBuf = VOS_NULL_PTR;
            break;

        default:

            PPP_DBG_ERR_CNT(PPP_PHERR_858);
            break;
    }
    (VOS_VOID)pstData;
    (VOS_VOID)pstSynMBuf;
    return;
}

/*****************************************************************************
 函 数 名  : FWD_PppGetWantLcpFcFlag
 功能描述  : 获取协商的协议压缩域
 输入参数  : 无

 输出参数  : pulPppFcFlag    协议压缩域
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppGetWantLcpFcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppFcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;

    /* 内部调用，保证入参非空 */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_905);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Fc Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_859);
        return VOS_ERR;
    }

    *pulPppFcFlag = pstLcpInfo->stWantOptions.neg_pcompression;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FWD_PppGetWantLcpAcfcFlag
 功能描述  : 获取协商的地址压缩域
 输入参数  : 无

 输出参数  : pulPppAcfcFlag   地址压缩域
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppGetWantLcpAcfcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppAcfcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* 内部调用，保证入参非空 */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_906);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Ac Fc Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_860);
        return VOS_ERR;
    }

    *pulPppAcfcFlag = pstLcpInfo->stWantOptions.neg_accompression;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FWD_PppGetHisLcpFcFlag
 功能描述  : 获取协商的协议压缩域
 输入参数  : 无

 输出参数  : pulPppFcFlag    协议压缩域
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppGetHisLcpFcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppFcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;

    /* 内部调用，保证入参非空 */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_905);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Fc Flag Fail!%d\r\n",ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_859);
        return VOS_ERR;
    }

    *pulPppFcFlag = pstLcpInfo->stHisOptions.neg_pcompression;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FWD_PppGetHisLcpAcfcFlag
 功能描述  : 获取协商的地址压缩域
 输入参数  : 无

 输出参数  : pulPppAcfcFlag   地址压缩域
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppGetHisLcpAcfcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppAcfcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* 内部调用，保证入参非空 */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_906);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Ac Fc Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_860);
        return VOS_ERR;
    }

    *pulPppAcfcFlag = pstLcpInfo->stHisOptions.neg_accompression;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FWD_PppGetHisAccm
 功能描述  : 获取对端控制字符映射标记
 输入参数  : 无

 输出参数  : pulAccmFlag   地址压缩域
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月29日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FWD_PppGetHisAccm(VOS_UINT8 ucPppId, VOS_UINT32  *pulAccmFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* 内部调用，保证入参非空 */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_910);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp ACCM Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_911);
        return VOS_ERR;
    }

    *pulAccmFlag = pstLcpInfo->stHisOptions.asyncmap;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FWD_PppEncap
 功能描述  : 封装PPP报文头
 输入参数  : ucPdnId        承载号
             pstMBuf        PPP报文
             enPktType      报文类型
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 FWD_PppEncap
(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucCdsData,
    VOS_UINT16                          usDataLen,
    VOS_UINT32                          ulAccmValue,
    VOS_UINT32                         *pulAsynLen
)
{
    VOS_UINT8                          *pucPppData;
    IP4_S                              *pstIP;
    VOS_UINT8                           ucPppId;
    VOS_UINT8                           ucIpVer;
    VOS_UINT8                           ucPppProto;
    VOS_UINT32                          ulPppFcFlag;
    VOS_UINT32                          ulPppAcfcFlag;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSduLen = 0;
    VOS_UINT8                          *pucHeadPtr;

    /* 1X和HRPD头部长度最大为4个字节ff030021,eHRPD头部最长5个字节ff03005bxx(pdn id) */
    VOS_UINT8                           aucHeadData[8];
    /* 记录头部长度 */
    VOS_UINT16                          usFrameLen = 0;


    /* 数据指针为空或者数据长度为0直接退出,外面释放内存 */
    if ((VOS_NULL_PTR == pucCdsData) || (0 == usDataLen) || (usDataLen > PPPC_MAX_FRAME_LEN))
    {
        PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", usDataLen);
        return VOS_ERR;
    }

    PS_MEM_SET(aucHeadData, 0, sizeof(aucHeadData));
    pucHeadPtr = &(aucHeadData[0]);

    pucPppData = pucCdsData;

    /*
    加PPP封装出现以下两种情况 :
    1.解完GTP或L2TP之后,此时空间够用
    2.普通下行报文，加PPP封装，(下行PPP终结),若此时加ppp封装,封装头会进入预留的512字节内
     考虑到效率,这里不做检查,进一步封装GTP时会做检查
    */

    ulRet = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_907);
        return VOS_ERR;
    }

    ulRet   = FWD_PppGetHisLcpAcfcFlag(ucPppId, &ulPppAcfcFlag);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_861);
        return VOS_ERR;
    }

    ulRet   = FWD_PppGetHisLcpFcFlag(ucPppId, &ulPppFcFlag);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_862);
        return VOS_ERR;
    }

    /*填充地址控制域*/
    if (PPP_ACFC_0 == ulPppAcfcFlag)
    {
        *pucHeadPtr     = 0xff;
        pucHeadPtr++;
        *pucHeadPtr     = 0x03;
        pucHeadPtr++;
        usFrameLen     += 2;
    }

    /* 先判断协议域是否压缩,如果不压缩,协议域第一个字节填0,第二个字节在后面填充,
       之所以将协议域拆开填写是因为eHRPD场景下协议域不是IPv4或IPv6而是VSNP,且后面
       还要多一个字节的PDN ID */
    if(PPP_PFC_1 != ulPppFcFlag)
    {
        *pucHeadPtr     = 0;
        pucHeadPtr++;
        usFrameLen     += 1;
    }

    /*填充协议域*/
    if (PPPC_RAT_MODE_EHRPD == PPPC_GetRatMode())
    {
        ucPppProto      = PPP_H_PFC_VSNP;
        *pucHeadPtr     = ucPppProto;
        pucHeadPtr++;
        *pucHeadPtr     = ucPdnId;
        pucHeadPtr++;
        usFrameLen += 2;
    }
    else
    {
        pstIP = (IP4_S *)pucPppData;
        ucIpVer = pstIP->ip_chVer;
        (IPV4_VERSION == ucIpVer)?(ucPppProto = PPP_H_PFC_IPV4):(ucPppProto = PPP_H_PFC_IPV6);
        *pucHeadPtr = ucPppProto;
        pucHeadPtr++;
        usFrameLen += 1;
    }

    /* 同步转异步 */
    ulSduLen = PPP_UlDataSynToAsy(aucHeadData, usFrameLen, pucCdsData, usDataLen, ulAccmValue);
    *pulAsynLen = ulSduLen;

    (VOS_VOID)pucHeadPtr;
    return VOS_OK;
}

/******************************************************************************
函 数 名  : FWD_PppRebuildIncompleteSliceStatInit
功能描述  : 将g_stPppRebuildIncompleteSliceStat清空
输入参数  :

输出参数  : NA
全局变量  : NA
返 回 值  : NA
调用函数  : NA
被调函数  : NA

修改历史      :
1.日    期   : 星期六 2015年8月28日
作    者   : zWX297122
修改内容   : 新生成函数

******************************************************************************/
VOS_VOID FWD_PppRebuildIncompleteSliceStatInit()
{
    PS_MEM_SET(&g_stPppRebuildIncompleteSliceStat, 0, sizeof(g_stPppRebuildIncompleteSliceStat));
}

/******************************************************************************
函 数 名  : FWD_PppRebuildIgnoreContinuousSeqFlag
功能描述  : PPP分片跳过连续7E
输入参数  :
            VOS_UINT8                      *pData,
            VOS_UINT16                      usUsed,
            TTF_MEM_ST                     *pstData,
            VOS_UINT32                     *ulSeqOffsetToModify
输出参数  : NA
全局变量  : NA
返 回 值  : NA
调用函数  : NA
被调函数  : NA

修改历史      :
1.日    期   : 星期六 2015年8月13日
作    者   : zWX297122
修改内容   : 新生成函数

******************************************************************************/
VOS_VOID FWD_PppRebuildIgnoreContinuousSeqFlag
(
    VOS_UINT8                      *pData,
    VOS_UINT16                      usUsed,
    VOS_UINT32                     *ulSeqOffsetToModify
)
{
    VOS_UINT32                      ulSeqOffset = *ulSeqOffsetToModify;


    /* 跳过连续7E  调函数*/
    while ((ulSeqOffset < usUsed) && (PPP_FLAG_SEQ == pData[ulSeqOffset]))
    {
        ulSeqOffset++;
    }

    if(ulSeqOffset >= usUsed)
    {
        g_stPppRebuildIncompleteSliceStat.usLastByteSeq = 1;
    }
    else
    {
        g_stPppRebuildIncompleteSliceStat.usLastByteSeq = 0;
    }

    *ulSeqOffsetToModify = ulSeqOffset;

}

/******************************************************************************
 函 数 名  : FWD_PppRebuild
 功能描述  : PPP分片报文重组处理
             入参pstData已经偏移到了PPP头
             负责释放pstData
 输入参数  :
            VOS_UINT16                          usSeqNr,
            TTF_MEM_ST                         *pstData,
            PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
 输出参数  : NA
 全局变量  : NA
 返 回 值  :
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 星期六 2015年8月13日
    作    者   : zWX297122
    修改内容   : 新生成函数

******************************************************************************/
VOS_VOID FWD_PppRebuild
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
)
{
    VOS_UINT8                          *pData = pstData->pData;
    VOS_UINT16                          usUsed = pstData->usUsed;
    PPP_REBUILD_INCOMPLETE_SLICE_STRU  *pstPppCurRebuildStat = &g_stPppRebuildIncompleteSliceStat;
    VOS_UINT32                          ulSeqOffset = 0;
    VOS_UINT8                           ucThisByteSeq;
    VOS_UINT8                           ucHasStartSeq;
    TTF_MEM_ST                         *pstTtfMem;


    /* 逐Byte处理分片 */
    while (ulSeqOffset < usUsed)
    {
        ucThisByteSeq = (pData[ulSeqOffset] == PPP_FLAG_SEQ);
        ucHasStartSeq = (pstPppCurRebuildStat->usHasStartFlag == 1);

        if (ucThisByteSeq && !ucHasStartSeq)
        {
            pstPppCurRebuildStat->usHasStartFlag = 1;
            pstPppCurRebuildStat->usStartSeq = usSeqNr;
            ulSeqOffset++;
        }
        else if (!ucThisByteSeq && !ucHasStartSeq)
        {
            ulSeqOffset++;
        }
        else if (!ucThisByteSeq && ucHasStartSeq)
        {
            pstPppCurRebuildStat->usLastByteSeq = 0;
            PPP_AsyToSyn(pData[ulSeqOffset]);
            ulSeqOffset++;
        }
        else
        {
            if(pstPppCurRebuildStat->usLastByteSeq == 1)
            {
                FWD_PppRebuildIgnoreContinuousSeqFlag(pData, usUsed, &ulSeqOffset);
                pstPppCurRebuildStat->usStartSeq= usSeqNr;
            }
            else
            {
                pstPppCurRebuildStat->usEndSeq = usSeqNr;
                if(1 == PPP_AsyToSyn(pData[ulSeqOffset]))
                {
                    pstTtfMem = TTF_MemBlkCopyAlloc(MSPS_PID_PPPC,
                                    TTF_MEM_POOL_ID_DL_PDU, g_aucPppRebuildSynSliceBuffer, g_usPppSynSliceBufUsedLen);
                    if (VOS_NULL_PTR == pstTtfMem)
                    {
                        return;
                    }
                    FWD_PppDecap(pstPppCurRebuildStat->usStartSeq, pstPppCurRebuildStat->usEndSeq, pstTtfMem, ucRatMode, ucPppId);
                }
                g_usPppSynSliceBufUsedLen = 0;
                FWD_PppRebuildIgnoreContinuousSeqFlag(pData, usUsed, &ulSeqOffset);
            }
        }

    }
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
