/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndEhsm.c
  版 本 号   : 初稿
  作    者   : y00314741
  生成日期   : 2015年05月08日
  最近修改   :
  功能描述   : TAF APS模块发送消息给HSM的函数实现文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月08日
    作    者   : y00314741
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafApsSndDhcp.h"
#include "TafApsCtx.h"
#include "taf_aps_dhcp_pif.h"
#include "TafApsComFunc.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_DHCP_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_APS_SndDhcpDnsIpv4Req
 功能描述  : 发送ID_APS_DHCP_GET_DNS_IPV4_REQ消息
 输入参数  : VOS_UINT8                    ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndDhcpDnsIpv4Req(
    VOS_UINT8                           ucPdpId
)
{
    APS_DHCP_DNS_IPV4_REQ_STRU         *pstDnsIpv4Req = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取消息内容 */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDnsIpv4Req   = (APS_DHCP_DNS_IPV4_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_DHCP_DNS_IPV4_REQ_STRU));

    if (VOS_NULL_PTR == pstDnsIpv4Req)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndDhcpDnsIpv4Req: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDnsIpv4Req + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_DHCP_DNS_IPV4_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstDnsIpv4Req->ulReceiverPid        = UEPS_PID_DHCP;
    pstDnsIpv4Req->enMsgId              = ID_APS_DHCP_GET_DNS_IPV4_REQ;
    pstDnsIpv4Req->usOpId               = 0;
    pstDnsIpv4Req->ucRabId              = pstPdpEntity->ucNsapi;

    PS_MEM_CPY((VOS_CHAR *)pstDnsIpv4Req->aucIpv4Addr,
                (VOS_CHAR *)pstPdpEntity->PdpAddr.aucIpAddr,
                 TAF_APS_DHCP_IPV4_ADDR_LEN);

    PS_SEND_MSG(WUEPS_PID_TAF, pstDnsIpv4Req);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndDhcpDnsIpv6Req
 功能描述  : 发送ID_APS_DHCP_GET_DNS_IPV4_REQ消息
 输入参数  : VOS_UINT8                    ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndDhcpDnsIpv6Req(
    VOS_UINT8                           ucPdpId
)
{
    APS_DHCP_DNS_IPV6_REQ_STRU         *pstDnsIpv6Req = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取消息内容 */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDnsIpv6Req   = (APS_DHCP_DNS_IPV6_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_DHCP_DNS_IPV6_REQ_STRU));

    if (VOS_NULL_PTR == pstDnsIpv6Req)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndDhcpDnsIpv6Req: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDnsIpv6Req + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_DHCP_DNS_IPV6_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstDnsIpv6Req->ulReceiverPid        = UEPS_PID_DHCP;
    pstDnsIpv6Req->enMsgId              = ID_APS_DHCP_GET_DNS_IPV6_REQ;
    pstDnsIpv6Req->usOpId               = 0;
    pstDnsIpv6Req->ucRabId              = pstPdpEntity->ucNsapi;

    PS_MEM_CPY((VOS_CHAR *)pstDnsIpv6Req->aucIdentifierId,
                (VOS_CHAR *)pstPdpEntity->PdpAddr.aucIpV6Addr + TAF_APS_DHCP_IPV6_IFID_LEN,
                 TAF_APS_DHCP_IPV6_IFID_LEN);

    PS_SEND_MSG(WUEPS_PID_TAF, pstDnsIpv6Req);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndDhcpDeactInd
 功能描述  : 发送ID_APS_DHCP_DEACT_IND消息
 输入参数  : VOS_UINT8                    ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月24日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndDhcpDeactInd(
    VOS_UINT8                           ucPdpId
)
{
    APS_DHCP_DEACT_IND_STRU            *pstDnsDeactInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;

    /* 获取消息内容 */

    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDnsDeactInd  = (APS_DHCP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_DHCP_DEACT_IND_STRU));

    if (VOS_NULL_PTR == pstDnsDeactInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndDhcpDnsReqReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDnsDeactInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_DHCP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstDnsDeactInd->ulReceiverPid       = UEPS_PID_DHCP;
    pstDnsDeactInd->enMsgId             = ID_APS_DHCP_DEACT_IND;
    pstDnsDeactInd->usOpId              = 0;
    pstDnsDeactInd->ucRabId             = pstPdpEntity->ucNsapi;
    pstDnsDeactInd->enPdnType           = TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid);

    PS_SEND_MSG(WUEPS_PID_TAF, pstDnsDeactInd);

    return;
}

#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
