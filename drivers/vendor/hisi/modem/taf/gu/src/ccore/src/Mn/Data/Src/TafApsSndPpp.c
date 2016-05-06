/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndPpp.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年10月21日
  最近修改   :
  功能描述   : TAF APS模块发送消息给PPP的函数实现文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsApi.h"
#include  "MnApsComm.h"
#include  "Taf_Aps.h"
#include  "TafLog.h"
#include  "TafApsCtx.h"
#include  "TafApsComFunc.h"
#include  "TafApsDecode.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include  "taf_aps_ppp_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_PPP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_APS_FillPppActReqInfoWithCardSipContent
 功能描述  : PPP act req使用卡中的鉴权参数
 输入参数  :
 输出参数  : VOS_UINT8                          *pucUserName,
             VOS_UINT8                          *pucPswd,
             VOS_UINT8                          *pucAuthType
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_FillPppActReqInfoWithCardSipContent(
    VOS_UINT8                          *pucUserName,
    VOS_UINT8                          *pucPswd,
    VOS_UINT8                          *pucAuthType
)
{
    TAF_APS_3GPD_SIP_INFO_STRU          st3GpdSipInfo;
    VOS_UINT32                          ulReadUserProfileRslt;
    VOS_UINT32                          ulReadPppPapSsRslt;

    PS_MEM_SET(&st3GpdSipInfo, 0, sizeof(TAF_APS_3GPD_SIP_INFO_STRU));
    ulReadUserProfileRslt = TAF_APS_Get3GpdPppSipNaiInfoFromCard(&st3GpdSipInfo);
    ulReadPppPapSsRslt    = TAF_APS_Get3GpdPppSipPapSsInfoFromCard(&st3GpdSipInfo);

    if (VOS_TRUE == ulReadUserProfileRslt)
    {
        VOS_StrNCpy((VOS_CHAR*)pucUserName,
                    (VOS_CHAR*)st3GpdSipInfo.aucNaiStr,
                    TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);


    }
    if ((VOS_TRUE == ulReadPppPapSsRslt) && (TAF_PDP_AUTH_TYPE_PAP == st3GpdSipInfo.enPppAuthType))
    {
        VOS_StrNCpy((VOS_CHAR*)pucPswd,
                    (VOS_CHAR*)st3GpdSipInfo.aucPapSsStr,
                    TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);
    }
    *pucAuthType = TAF_APS_MapApsAuthTypeToPpp(st3GpdSipInfo.enPppAuthType);

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPppActReq
 功能描述  : 通知PPP模块PPP协商激活
 输入参数  : ucPdpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年4月27日
    作    者   : Y00213812
    修改内容   : 使用NDISDUP或者AUTHDATA中设置的用户名和密码作为鉴权参数
*****************************************************************************/
VOS_VOID  TAF_APS_SndPppActReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_ACT_REQ_STRU               *pstPppActReq;

    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    VOS_UINT32                          ulResult;

    /* 获取消息内容 */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg       = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    pstPppActReq    = (APS_PPP_ACT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_ACT_REQ_STRU));

    if (VOS_NULL_PTR == pstPppActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppActReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppActReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_ACT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppActReq->ulReceiverPid = MSPS_PID_PPPC;
    pstPppActReq->enMsgId       = ID_APS_PPP_ACT_REQ;
    pstPppActReq->usOpId        = 0;
    pstPppActReq->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    pstPppActReq->enPdnType     = TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 目前只有1X和HRPD模式下需要APS通知PPP模块，当前的接入模式 */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppActReq->enMode            = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppActReq->enMode            = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    switch(pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):

            if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
            {
                pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_MODEM;

                TAF_APS_FillPppActReqInfoWithCardSipContent(pstPppActReq->aucUserName,
                                                            pstPppActReq->aucPassword,
                                                           &pstPppActReq->enAuthType);
            }
            else
            {
                pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_AP;

                VOS_StrNCpy((VOS_CHAR*)pstPppActReq->aucUserName,
                            (VOS_CHAR*)pstCallOrigReq->stDialParaInfo.aucUserName,
                            TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);

                VOS_StrNCpy((VOS_CHAR*)pstPppActReq->aucPassword,
                            (VOS_CHAR*)pstCallOrigReq->stDialParaInfo.aucPassWord,
                            TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);

                pstPppActReq->enAuthType = TAF_APS_MapApsAuthTypeToPpp(pstCallOrigReq->stDialParaInfo.enAuthType);
            }


            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
            PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));

            if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
            {
                pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_MODEM;

                TAF_APS_FillPppActReqInfoWithCardSipContent(pstPppActReq->aucUserName,
                                                            pstPppActReq->aucPassword,
                                                           &pstPppActReq->enAuthType);

                /* 卡中无chap鉴权密码 */
                if (TAF_APS_PPP_AUTH_TYPE_PAP != pstPppActReq->enAuthType)
                {
                    PS_MEM_SET(pstPppActReq->aucUserName, 0, TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN + 1);
                    PS_MEM_SET(pstPppActReq->aucPassword, 0, TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN + 1);
                    pstPppActReq->enAuthType = TAF_APS_PPP_AUTH_TYPE_NONE;
                }
            }
            else
            {
                /* MODEM拨号时，只支持PAP类型的鉴权 */
                if ((VOS_TRUE == pstPppDialOrigReq->stPppDialParaInfo.bitOpPppConfigInfo)
                 && (TAF_PDP_AUTH_TYPE_PAP == pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthType))
                {
                    ulResult = TAF_APS_DecodePapInfo(&stAuthInfo,
                                                     pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.aucPapReqBuf,
                                                     pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.usPapReqLen);

                    if (VOS_OK == ulResult)
                    {
                        pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_AP;
                        PS_MEM_CPY(pstPppActReq->aucUserName,
                                   stAuthInfo.unAuthParam.stPapParam.aucUsername,
                                   stAuthInfo.unAuthParam.stPapParam.ucUsernameLen);

                        PS_MEM_CPY(pstPppActReq->aucPassword,
                                   stAuthInfo.unAuthParam.stPapParam.aucPassword,
                                   stAuthInfo.unAuthParam.stPapParam.ucPasswordLen);

                        pstPppActReq->enAuthType = TAF_APS_PPP_AUTH_TYPE_PAP;
                    }
                }
            }
            break;

        default:
            break;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppActReq);

}


/*****************************************************************************
 函 数 名  : TAF_APS_SndPppDeactReq
 功能描述  : 通知PPP模块PPP协商去激活
 输入参数  : ucPdpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDeactReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_DEACT_REQ_STRU             *pstPppDeactReq;

    pstPppDeactReq = (APS_PPP_DEACT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DEACT_REQ_STRU));

    if (VOS_NULL_PTR == pstPppDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDeactReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppDeactReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DEACT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppDeactReq->ulReceiverPid = MSPS_PID_PPPC;
    pstPppDeactReq->enMsgId       = ID_APS_PPP_DEACT_REQ;

    pstPppDeactReq->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);


    /* 目前只有1X和HRPD模式下需要APS通知PPP模块，当前的接入模式 */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppDeactReq->enMode          = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppDeactReq->enMode          = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppDeactReq);

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPppDeactInd
 功能描述  : 通知PPP模块PPP直接去激活
 输入参数  : ucPdpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDeactInd(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_DEACT_IND_STRU             *pstPppDeactInd;

    pstPppDeactInd = (APS_PPP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DEACT_IND_STRU));

    if (VOS_NULL_PTR == pstPppDeactInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDeactInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppDeactInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppDeactInd->ulReceiverPid = MSPS_PID_PPPC;
    pstPppDeactInd->enMsgId       = ID_APS_PPP_DEACT_IND;

    pstPppDeactInd->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    /* 目前只有1X和HRPD模式下需要APS通知PPP模块，当前的接入模式 */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppDeactInd->enMode          = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppDeactInd->enMode          = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppDeactInd);

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPppModeChangeNotify
 功能描述  : 通知PPP模块PPP模式改变通知
 输入参数  : ucPdpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月27日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppModeChangeNotify(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_MODE_CHANGE_NTF_STRU       *pstPppModeChangeNty;

    pstPppModeChangeNty = (APS_PPP_MODE_CHANGE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_MODE_CHANGE_NTF_STRU));

    if (VOS_NULL_PTR == pstPppModeChangeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppModeChangeNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppModeChangeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_MODE_CHANGE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppModeChangeNty->ulReceiverPid = MSPS_PID_PPPC;
    pstPppModeChangeNty->enMsgId       = ID_APS_PPP_MODE_CHANGE_NTF;
    pstPppModeChangeNty->usOpId        = 0;
    pstPppModeChangeNty->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    /* 目前只有1X和HRPD模式下需要APS通知PPP模块，当前的接入模式 */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppModeChangeNty->enMode = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppModeChangeNty->enMode = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppModeChangeNty);

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPppModeChangeNotify
 功能描述  : 通知PPP模块AT设置的拨号模式
 输入参数  : ucPdpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDialModeNotify(
    VOS_UINT16                          usClientId
)
{
    APS_PPP_DIAL_MODE_NTF_STRU         *pstDialModeNty;

    pstDialModeNty = (APS_PPP_DIAL_MODE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DIAL_MODE_NTF_STRU));

    if (VOS_NULL_PTR == pstDialModeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDialModeNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDialModeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DIAL_MODE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDialModeNty->ulReceiverPid        = MSPS_PID_PPPC;
    pstDialModeNty->enMsgId              = ID_APS_PPP_DIAL_MODE_NTF;
    pstDialModeNty->usOpId               = 0;
    pstDialModeNty->usClientId           = usClientId;
    pstDialModeNty->enDialMode           = (VOS_UINT8)TAF_APS_GetFsmCtxCdataDialMode();

    PS_SEND_MSG(WUEPS_PID_TAF, pstDialModeNty);

}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPppLinkStatusNotify
 功能描述  : APS Notify current link status to PPP module
 输入参数  : VOS_UINT8                           ucPdpId
             TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  enLinkStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndPppLinkStatusNotify(
    VOS_UINT8                           ucPdpId,
    TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  enLinkStatus
)
{
    APS_PPP_LINK_STATUS_NTF_STRU       *pstLinkStatusNtf;

    pstLinkStatusNtf = (APS_PPP_LINK_STATUS_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_LINK_STATUS_NTF_STRU));

    if (VOS_NULL_PTR == pstLinkStatusNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppLinkStatusNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstLinkStatusNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_LINK_STATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstLinkStatusNtf->ulReceiverPid = MSPS_PID_PPPC;
    pstLinkStatusNtf->enMsgId       = ID_APS_PPP_LINK_STATUS_NTF;
    pstLinkStatusNtf->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstLinkStatusNtf->enLinkStatus  = enLinkStatus;

    PS_SEND_MSG(WUEPS_PID_TAF, pstLinkStatusNtf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPppLinkStatus
 功能描述  : 提供给L2查询空口链路的接口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 TAF_APS_GetPppLinkStatus(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  ucLinkStatus;

    ucLinkStatus = TAF_APS_PPP_LINK_NOT_EXISTED;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        switch (TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            case TAF_APS_CDATA_AIR_LINK_NO_LINK:
                ucLinkStatus = TAF_APS_PPP_LINK_NOT_EXISTED;
                break;

            case TAF_APS_CDATA_AIR_LINK_CONNECTING:
                ucLinkStatus = TAF_APS_PPP_LINK_CONNING;
                break;

            case TAF_APS_CDATA_AIR_LINK_DISCONNECTING:
                ucLinkStatus = TAF_APS_PPP_LINK_DISCING;
                break;

            case TAF_APS_CDATA_AIR_LINK_CONNECTED:
                ucLinkStatus = TAF_APS_PPP_LINK_CONNECTED;
                break;

            default:
                break;
        }
    }

    return ucLinkStatus;
}


#endif






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
