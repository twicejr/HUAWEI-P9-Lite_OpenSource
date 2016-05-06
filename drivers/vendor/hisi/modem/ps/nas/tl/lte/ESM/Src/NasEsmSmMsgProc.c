/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmSmMsgProc.c
    Description : 处理SM发给ESM的消息
    History     :
     1.李洪 00150010        2011-04-28  Draft Enact

******************************************************************************/



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmSmMsgProc.h"
#include    "SmEsmInterface.h"
#include    "NasEsmNwMsgDecode.h"
#include    "NasEsmNwMsgBearerResModProc.h"
#include    "NasEsmRabmMsgProc.h"
#include    "NasEsmOmMsgProc.h"
#include    "NasEsmEmmMsgProc.h"

#include    "NasEsmEhsmMsgProc.h"

#include    "NasEsmAppMsgProc.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMSMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMSMMSGPROC_C
/*lint +e767*/


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_ESM_SmMsgDistr
 Description    : ESM模块SM消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong00150010      2011-04-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SmMsgDistr
(
    VOS_VOID                           *pRcvMsg
)
{
    PS_MSG_HEADER_STRU         *pSmMsg = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SmMsgDistr_ENUM, LNAS_ENTRY);

    pSmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pSmMsg->ulMsgName)
    {
        /*如果收到的是ID_SM_ESM_PDP_CONTEXT_INFO_IND消息*/
        case ID_SM_ESM_PDP_CONTEXT_INFO_IND:

            NAS_ESM_RcvPdpContextInfoInd( (SM_ESM_PDP_CONTEXT_INFO_IND_STRU *)pRcvMsg );
            break;

        /* PDN激活释放相关的消息, ESM与TAF交互, 不通过L4A */
        /*如果收到的是ID_APP_ESM_PDP_SETUP_REQ消息*/
        case ID_APP_ESM_PDP_SETUP_REQ:

            /*调用消息处理函数*/
            NAS_ESM_AppSdfSetupMsgProc(pRcvMsg);
            break;

        /*如果收到的是ID_APP_ESM_PDP_RELEASE_REQ消息*/
        case ID_APP_ESM_PDP_RELEASE_REQ:

            /*调用消息处理函数*/
            NAS_ESM_AppSdfReleaseMsgProc(pRcvMsg);
            break;

        /*如果收到的是ID_APP_ESM_PDP_MODIFY_REQ消息*/
        case ID_APP_ESM_PDP_MODIFY_REQ:

            /*调用消息处理函数*/
            NAS_ESM_AppSdfModifyMsgProc(pRcvMsg);
            break;

        /*如果收到的是ID_APP_ESM_PDP_MANAGER_RSP消息*/
        case ID_APP_ESM_PDP_MANAGER_RSP:

            NAS_ESM_AppPdpManageRspMsgProc(pRcvMsg);
            break;

        case ID_APP_ESM_NDISCONN_REQ:

            NAS_ESM_AppNdisconnMsgProc(pRcvMsg);
            break;

        default:
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_SmMsgDistr:WARNING:SM->ESM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SmMsgDistr_ENUM, 1);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvPdpContextInfoInd
 Description     : ESM模块收到ID_SM_ESM_PDP_CONTEXT_INFO_IND处理函数
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_RcvPdpContextInfoInd
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvPdpContextInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvPdpContextInfoInd_ENUM, LNAS_ENTRY);

    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_RcvPdpContextInfoInd:NORM: received abnormal Pdp context Ind !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvPdpContextInfoInd_ENUM, ESM_CID_ERROR);
    }

    switch (pstRcvMsg->enPdpOption)
    {
        case SM_ESM_PDP_OPT_ACTIVATE:
            NAS_ESM_ProcSmPdpActivate(pstRcvMsg);
            break;
        case SM_ESM_PDP_OPT_MODIFY:
            NAS_ESM_ProcSmPdpModify(pstRcvMsg);
            break;
        case SM_ESM_PDP_OPT_DEACTIVATE:
            NAS_ESM_ProcSmPdpDeactivate(pstRcvMsg);
            break;
        default:
            NAS_ESM_WARN_LOG("NAS_ESM_RcvPdpContextInfoInd:illegal enPdpOption!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvPdpContextInfoInd_ENUM, ESM_PDN_TYPE_ERROR);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_MapPdpQos2EpsQos
 Description     : 将PDP QOS映射为EPS QOS
 Input           : SM_ESM_PDP_QOS_STRU                *pstPdpQos
 Output          : NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstEpsQos
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact
    2.wangchen 00209181         2014-09-02      Modify:R11
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_MapPdpQos2EpsQos
(
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstEpsQos,
    const SM_ESM_PDP_QOS_STRU          *pstPdpQos
)
{
    VOS_UINT32                          ulRate = NAS_ESM_NULL;

    /* 映射QCI */
    switch (pstPdpQos->ucTrafficClass)
    {
        case NAS_ESM_TRAFFIC_CLASS_CONVENTIONAL:
            NAS_ESM_MapTraffClassConventional2EpsQci(pstEpsQos, pstPdpQos);
            break;
        case NAS_ESM_TRAFFIC_CLASS_STREAMING:
            pstEpsQos->ucNwQCI = NAS_ESM_QCI_TYPE_QCI4_GBR;
            pstEpsQos->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI4_GBR;
            break;
        case NAS_ESM_TRAFFIC_CLASS_INTERACTIVE:
            NAS_ESM_MapTraffClassInteractive2EpsQci(pstEpsQos, pstPdpQos);
            break;
        default:
            pstEpsQos->ucNwQCI = NAS_ESM_QCI_TYPE_QCI9_NONGBR;
            pstEpsQos->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI9_NONGBR;
            break;
    }

    /* 如果是NON-GBR，则无需映射速率 */
    if (PS_TRUE != NAS_ESM_IsGbrBearer(pstEpsQos->ucNwQCI))
    {
        return ;
    }

    /* 转化DL MAX RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucMaxBitRateForDown;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForDownExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForDownExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulDLMaxRate);

    /* 转化UL MAX RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucMaxBitRateForUp;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForUpExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForUpExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulULMaxRate);

    /* 转化DL GUARANTEED RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucGuarantBitRateForDown;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForDownExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForDownExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulDLGMaxRate);

    /* 转化UL GUARANTEED RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucGuarantBitRateForUp;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForUpExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForUpExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulULGMaxRate);
}

/*****************************************************************************
 Function Name   : NAS_ESM_MapPdpQos2ApnAmbr
 Description     : 将PDP QOS映射为APN-AMBR
 Input           : SM_ESM_PDP_QOS_STRU                *pstPdpQos
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_MapPdpQos2ApnAmbr
(
    NAS_ESM_CONTEXT_APN_AMBR_STRU      *pstApnAmbrInfo,
    const SM_ESM_PDP_QOS_STRU          *pstPdpQos
)
{
    pstApnAmbrInfo->ucDLApnAmbr = pstPdpQos->ucMaxBitRateForDown;
    pstApnAmbrInfo->ucULApnAmbr = pstPdpQos->ucMaxBitRateForUp;

    if (NAS_ESM_NULL != pstPdpQos->ucMaxBitRateForDownExt)
    {
        pstApnAmbrInfo->bitOpDLApnAmbrExt = NAS_ESM_OP_TRUE;
        pstApnAmbrInfo->ucDLApnAmbrExt = pstPdpQos->ucMaxBitRateForDownExt;
    }

    if (NAS_ESM_NULL != pstPdpQos->ucMaxBitRateForUpExt)
    {
        pstApnAmbrInfo->bitOpULApnAmbrExt = NAS_ESM_OP_TRUE;
        pstApnAmbrInfo->ucULApnAmbrExt = pstPdpQos->ucMaxBitRateForUpExt;
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_SavePdpTftInfo
 Description     : 保存PDP激活的TFT信息
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-29      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SavePdpTftInfo
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstRcvMsg
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;
    const SM_ESM_CID_PF_STRU           *pstCidPf        = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstContTft      = VOS_NULL_PTR;

    /* 存储SDF的承载号信息 */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
        pstSdfCntxtInfo->ulEpsbId = pstRcvMsg->ulNsapi;
        pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;
    }

    if (NAS_ESM_OP_TRUE != pstRcvMsg->bitOpTft)
    {
        return ;
    }

    /* 存储PF信息 */
    for( ulCnt = NAS_ESM_NULL; ulCnt < pstRcvMsg->stTft.ulPfNum; ulCnt++ )
    {
        pstCidPf        = &pstRcvMsg->stTft.astCidPf[ulCnt];
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstCidPf->ulCid);

        /* 存储PF信息 */
        pstContTft = &pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum];

        NAS_ESM_MEM_CPY_S(  pstContTft,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                            &pstCidPf->stPf,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU));

        pstSdfCntxtInfo->ulSdfPfNum++;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SavePdpTftInfo
 Description     : 保存PDP激活的PCO IPV4项
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-29      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SavePcoIpv4Item
(
    NAS_ESM_CONTEXT_PCO_STRU           *pstPcoInfo,
    const SM_ESM_PCO_IPV4_ITEM_STRU    *pstPcoIpv4Item
)
{
    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpPriDns)
    {
        pstPcoInfo->ucIpv4DnsSerNum = 1;

        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv4DnsServer[0].aucIpV4Addr,
                            SM_ESM_IPV4_ADDR_LEN,
                            pstPcoIpv4Item->aucPriDns,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpSecDns)
    {
        pstPcoInfo->ucIpv4DnsSerNum = 2;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv4DnsServer[1].aucIpV4Addr,
                            SM_ESM_IPV4_ADDR_LEN,
                            pstPcoIpv4Item->aucSecDns,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpPriPcscf)
    {
        pstPcoInfo->ucIpv4PcscfNum = 1;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv4Pcscf[0].aucIpV4Addr,
                            SM_ESM_IPV4_ADDR_LEN,
                            pstPcoIpv4Item->aucPriPcscf,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpSecPcscf)
    {
        pstPcoInfo->ucIpv4PcscfNum = 2;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv4Pcscf[1].aucIpV4Addr,
                            SM_ESM_IPV4_ADDR_LEN,
                            pstPcoIpv4Item->aucSecPcscf,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpPriNbns)
    {
        pstPcoInfo->ucIpv4NbnsNum = 1;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv4Nbns[0].aucIpV4Addr,
                            SM_ESM_IPV4_ADDR_LEN,
                            pstPcoIpv4Item->aucPriNbns,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpSecNbns)
    {
        pstPcoInfo->ucIpv4NbnsNum = 2;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv4Nbns[1].aucIpV4Addr,
                            SM_ESM_IPV4_ADDR_LEN,
                            pstPcoIpv4Item->aucSecPcscf,
                            SM_ESM_IPV4_ADDR_LEN);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SavePcoIpv6Item
 Description     : 保存PDP激活的PCO IPV6项
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
                   const SM_ESM_PCO_IPV4_ITEM_STRU    *pstPcoIpv6Item
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501            2011-11-30      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SavePcoIpv6Item
(
    NAS_ESM_CONTEXT_PCO_STRU           *pstPcoInfo,
    const SM_ESM_PCO_IPV6_ITEM_STRU    *pstPcoIpv6Item
)
{
    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpPriDns)
    {
        pstPcoInfo->ucIpv6DnsSerNum = 1;

        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv6DnsServer[0].aucIpV6Addr,
                            SM_ESM_IPV6_ADDR_LEN,
                            pstPcoIpv6Item->aucPriDns,
                            SM_ESM_IPV6_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpSecDns)
    {
        pstPcoInfo->ucIpv6DnsSerNum = 2;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv6DnsServer[1].aucIpV6Addr,
                            SM_ESM_IPV6_ADDR_LEN,
                            pstPcoIpv6Item->aucSecDns,
                            SM_ESM_IPV6_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpPriPcscf)
    {
        pstPcoInfo->ucIpv6PcscfNum = 1;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv6Pcscf[0].aucIpV6Addr,
                            SM_ESM_IPV6_ADDR_LEN,
                            pstPcoIpv6Item->aucPriPcscf,
                            SM_ESM_IPV6_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpSecPcscf)
    {
        pstPcoInfo->ucIpv6PcscfNum = 2;
        NAS_ESM_MEM_CPY_S(  pstPcoInfo->astIpv6Pcscf[1].aucIpV6Addr,
                            SM_ESM_IPV6_ADDR_LEN,
                            pstPcoIpv6Item->aucSecPcscf,
                            SM_ESM_IPV6_ADDR_LEN);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveSdfQos
 Description     : 保存PDP激活的SDF QOS信息
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveSdfQos
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU  *pstRcvMsg,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU      *pstEpsQos
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;

    /* 存储SDF的QOS信息 */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

        NAS_ESM_MEM_CPY_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                            pstEpsQos,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_SavePdpActivateInfo
 Description     : 保存PDP激活的上下文信息
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SavePdpActivateInfo
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;
    VOS_UINT32                          ulCurPdnNum      = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1    = {0};
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2    = {0};

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    NAS_ESM_MEM_SET_S(  pstEpsbCntxtInfo,
                        sizeof(NAS_ESM_EPSB_CNTXT_INFO_STRU),
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_EPSB_CNTXT_INFO_STRU));

    pstEpsbCntxtInfo->ulEpsbId              = ulEpsbId;
    pstEpsbCntxtInfo->bitOpCId              = NAS_ESM_OP_TRUE;
    pstEpsbCntxtInfo->ulBitCId              = pstRcvMsg->ulBitCid;
    pstEpsbCntxtInfo->bitOpTransId          = NAS_ESM_OP_TRUE;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU),
                        &pstRcvMsg->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /* 映射PDP QOS为承载QOS */
    pstEpsbCntxtInfo->bitOpEpsQos           = NAS_ESM_OP_TRUE;
    NAS_ESM_MapPdpQos2EpsQos(&pstEpsbCntxtInfo->stEpsQoSInfo, &pstRcvMsg->stPdpQos);

    /* 存储PDP QOS */
    pstEpsbCntxtInfo->bitOpNegQos = NAS_ESM_OP_TRUE;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU),
                        &pstRcvMsg->stPdpQos,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /* 存储SDF QOS */
    NAS_ESM_SaveSdfQos(pstRcvMsg, &pstEpsbCntxtInfo->stEpsQoSInfo);

    /* 存储PF信息 */
    NAS_ESM_SavePdpTftInfo(pstRcvMsg);

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* 专有承载 */
        pstEpsbCntxtInfo->ulLinkedEpsbId        = pstRcvMsg->ulLinkedNsapi;

        /*转换状态*/
        NAS_ESM_SetBearCntxtState(ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);
        NAS_ESM_SetBearCntxtType(ulEpsbId, NAS_ESM_BEARER_TYPE_DEDICATED);
    }
    else
    {
        /* 缺省承载 */
        /*存储PDN信息，设置PDN标识位*/
        pstEpsbCntxtInfo->bitOpPdnAddr = NAS_ESM_OP_TRUE;
        NAS_ESM_SavePdnAddr(&pstEpsbCntxtInfo->stPdnAddrInfo, &pstRcvMsg->stPdpAddr);

        if ((NAS_ESM_PDN_IPV4 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType)
            || (NAS_ESM_PDN_IPV4_IPV6 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType))
        {
            /* 产生子网掩码和默认网关 */
            pstEpsbCntxtInfo->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;

            pstEpsbCntxtInfo->stSubnetMask.ucIpType = NAS_ESM_PDN_IPV4;
            NAS_ESM_DHCPGetIPv4Mask(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                                    pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr);

            pstEpsbCntxtInfo->stGateWayAddrInfo.ucIpType = NAS_ESM_PDN_IPV4;
            NAS_ESM_DHCPGetIPv4GateWay( pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr);
        }

        /*设置APN标识位*/
        NAS_ESM_SaveApnAddr(&stTmpApnInfo1, &pstRcvMsg->stApn);

        /* 将APN格式从未译码转为译码 */
        ulRslt = NAS_ESM_ApnReverseTransformation(  &stTmpApnInfo2,
                                                    &stTmpApnInfo1);
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_ERR_LOG("NAS_ESM_SavePdpActivateInfo:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_SavePdpActivateInfo_ENUM, ESM_APN_ERROR);
            pstEpsbCntxtInfo->bitOpApn = NAS_ESM_OP_FALSE;
        }
        else
        {
            pstEpsbCntxtInfo->bitOpApn = NAS_ESM_OP_TRUE;

            NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stApnInfo,
                                sizeof(APP_ESM_APN_INFO_STRU),
                                &stTmpApnInfo2,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /* 存储APN-AMBR */
        pstEpsbCntxtInfo->bitOpApnAmbr = NAS_ESM_OP_TRUE;
        NAS_ESM_MapPdpQos2ApnAmbr(&pstEpsbCntxtInfo->stApnAmbrInfo, &pstRcvMsg->stPdpQos);

        /* 存储PCO IPV4项 */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv4Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv4Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv4Item);
        }

        /* 存储PCO IPV6项 */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv6Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv6Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv6Item);
        }

        /* 存储IM CN SIGNAL FLAG标识 */
        if ((NAS_ESM_OP_TRUE == pstRcvMsg->bitOpImCnSigalFlag))
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.enImsCnSignalFlag = pstRcvMsg->enImCnSignalFlag;
        }

        /*当前PDN连接数增加1条*/
        ulCurPdnNum = NAS_ESM_GetCurPdnNum()+1;

        /*保存当前PDN连接数*/
        NAS_ESM_SetCurPdnNum(ulCurPdnNum);

        /*转换状态*/
        NAS_ESM_SetBearCntxtState(ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);

        if ((NAS_ESM_OP_TRUE == pstRcvMsg->bitOpEmcInd)
            && (SM_ESM_PDP_FOR_EMC == pstRcvMsg->enEmergencyInd))
        {
            NAS_ESM_SetBearCntxtType(ulEpsbId, NAS_ESM_BEARER_TYPE_EMERGENCY);
        }
        else
        {
            NAS_ESM_SetBearCntxtType(ulEpsbId, NAS_ESM_BEARER_TYPE_DEFAULT);
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateSmSecPdpActivate
 Description     : 验证SM发来的次PDP激活消息的合法性
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-19      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateSmSecPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    const SM_ESM_CID_PF_STRU           *pstCidPf        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo= VOS_NULL_PTR;

    /* 专有承载必须具有TFT和PDP QOS */
    if ((NAS_ESM_OP_TRUE != pstRcvMsg->bitOpTft) || (NAS_ESM_OP_TRUE != pstRcvMsg->bitOpPdpQos))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmSecPdpActivate:no tft or no qos!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmSecPdpActivate_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstRcvMsg->ulLinkedNsapi);

    if ((NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
        || (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType)))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmSecPdpActivate:linkEpsbId is illegal!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmSecPdpActivate_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    /* 验证TFT信息中的CID在ulBitCid中都包含 */
    for( ulCnt = NAS_ESM_NULL; ulCnt < pstRcvMsg->stTft.ulPfNum; ulCnt++ )
    {
        pstCidPf        = &pstRcvMsg->stTft.astCidPf[ulCnt];

        if(NAS_ESM_OP_FALSE == (((pstRcvMsg->ulBitCid) >> (pstCidPf->ulCid)) & NAS_ESM_OP_TRUE))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmSecPdpActivate:TFT CID is not exist in BitCid!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmSecPdpActivate_ENUM, 3);
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidateSmPdpActivate
 Description     : 验证SM发来的PDP激活消息的合法性
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-04-29      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateSmPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
)
{
    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* 专有承载 */
        return NAS_ESM_ValidateSmSecPdpActivate(pstRcvMsg);
    }

    /* 缺省承载 */
    if ((NAS_ESM_OP_TRUE != pstRcvMsg->bitOpPdpQos) || (NAS_ESM_OP_TRUE != pstRcvMsg->bitOpApn))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmPdpActivate:no apn or no qos!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmPdpActivate_ENUM, ESM_APN_ERROR);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcSmPdpActivate
 Description     : ESM处理SM PDP激活
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcSmPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;

    if (NAS_ESM_L_MODE_STATUS_NORMAL == NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcSmPdpActivate:ESM is not suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcSmPdpActivate_ENUM, 1);
        return ;
    }
    /* 验证SM发来的PDP激活消息 */
    if (NAS_ESM_FAILURE == NAS_ESM_ValidateSmPdpActivate(pstRcvMsg))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcSmPdpActivate: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSmPdpActivate_ENUM, 2);
        return;
    }

    /* 如果承载已经激活，先本地去激活 */
    if(NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcSmPdpActivate : release already active bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcSmPdpActivate_ENUM, 3);
        NAS_ESM_ProcSmPdpDeactivate(pstRcvMsg);
    }

    /* 保存PDP激活的上下文信息 */
    NAS_ESM_SavePdpActivateInfo(pstRcvMsg);

    /*关键事件上报*/
    NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_SETUP(ulEpsbId));

    /*向EMM发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /* SM通知承载激活，肯定不会是CL的承载恢复流程，直接向RABM发送ID_ESM_ERABM_ACT_IND */
    NAS_ESM_SndEsmRabmActIndMsg(ulEpsbId, ESM_ERABM_BEARER_RAT_LTE, PS_FALSE, ESM_ERABM_INVALID_BEARER_ID);

    NAS_ESM_PrintEpsbInfo(ulEpsbId);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateSmPdpModify
 Description     : 验证SM发来的PDP激活消息的合法性
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501            2011-11-26      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateSmPdpModify
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstRcvMsg->ulNsapi);

    if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmPdpModify:pdp is not active!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmPdpModify_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* 专有承载, 删除TFT */
        if ((NAS_ESM_OP_FALSE == pstRcvMsg->bitOpTft) && (NAS_ESM_NULL == pstRcvMsg->stTft.ulPfNum))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmPdpModify:TFT of dedicated bearer cannot be delete!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmPdpModify_ENUM, 2);
            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ModifySdfQos
 Description     : 修改SDF Qos参数
 Input           : const SM_ESM_PDP_CONTEXT_INFO_IND_STRU  *pstRcvMsg,
                 : const NAS_ESM_CONTEXT_LTE_QOS_STRU      *pstEpsQos
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501            2011-11-26      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ModifySdfQos
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU  *pstRcvMsg,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU      *pstEpsQos
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stQosTemp = {{0}};
    VOS_UINT8                           ucCidNum  = 0;

    /* 获得承载关联的CID数目 */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }
        ucCidNum++;
    }

    if (0 == ucCidNum)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ModifySdfQos:Cid num cannot be zero!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ModifySdfQos_ENUM, 1);
        return;
    }

    NAS_ESM_MEM_CPY_S(  &stQosTemp,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        pstEpsQos,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /* 将承载Qos 参数平均分配至关联CID的Qos上 */
    stQosTemp.stQosInfo.ulDLGMaxRate /= ucCidNum;
    stQosTemp.stQosInfo.ulULGMaxRate /= ucCidNum;
    stQosTemp.stQosInfo.ulDLMaxRate  /= ucCidNum;
    stQosTemp.stQosInfo.ulULMaxRate  /= ucCidNum;

    /* 存储SDF的QOS信息 */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

        NAS_ESM_MEM_CPY_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                            &stQosTemp,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcSmPdpModify
 Description     : ESM处理SM PDP修改
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact
    2.niuxiufan 00181501        2011-11-26      Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcSmPdpModify
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1    = {0};
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2    = {0};
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;

    /* 验证SM发来的PDP修改消息 */
    if (NAS_ESM_FAILURE == NAS_ESM_ValidateSmPdpModify(pstRcvMsg))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcSmPdpModify: Msg is invalid and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSmPdpModify_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /* 保存stTransId、stPdnAddr、ulBitCid、ulLinkedNsapi至本地 */
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU),
                        &pstRcvMsg->stTransId,
                        sizeof(SM_ESM_TRANSACTION_ID_STRU));

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                        &pstRcvMsg->stPdpAddr,
                        sizeof(SM_ESM_PDP_ADDR_STRU));

    /* 清除承载原有关联CID的SDF动态信息 */
    for( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        /*遍历已取出的CID记录*/
        if(NAS_ESM_OP_TRUE ==((pstEpsbCntxtInfo->ulBitCId >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            /* 清空SDF上下文 */
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            NAS_ESM_MEM_SET_S(  pstSdfCntxtInfo,
                                sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                                0,
                                sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
        }
    }
    /*CID相同且承载类型是专有就给EMM发送承载修改请求消息*/
    if ((pstEpsbCntxtInfo->ulBitCId == pstRcvMsg->ulBitCid)||
        (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        NAS_ESM_SndEsmEmmBearerModifyReq(ulEpsbId);
    }
    pstEpsbCntxtInfo->ulBitCId = pstRcvMsg->ulBitCid;

    pstEpsbCntxtInfo->ulLinkedEpsbId = pstRcvMsg->ulLinkedNsapi;

    /* 修改TFT信息 */
    NAS_ESM_SavePdpTftInfo(pstRcvMsg);

    /* 映射PDP QOS为承载QOS */
    pstEpsbCntxtInfo->bitOpEpsQos = pstRcvMsg->bitOpPdpQos;
    NAS_ESM_MapPdpQos2EpsQos(&pstEpsbCntxtInfo->stEpsQoSInfo, &pstRcvMsg->stPdpQos);

    /* 存储PDP QOS */
    pstEpsbCntxtInfo->bitOpNegQos = pstRcvMsg->bitOpPdpQos;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU),
                        &pstRcvMsg->stPdpQos,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /* 修改SDF QOS */
    NAS_ESM_ModifySdfQos(pstRcvMsg, &pstEpsbCntxtInfo->stEpsQoSInfo);

    /* 缺省承载修改 */
    if (NAS_ESM_OP_FALSE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* 存储APN-AMBR */
        pstEpsbCntxtInfo->bitOpApnAmbr = pstRcvMsg->bitOpPdpQos;
        NAS_ESM_MapPdpQos2ApnAmbr(&pstEpsbCntxtInfo->stApnAmbrInfo, &pstRcvMsg->stPdpQos);

        /* 更改APN*/
        pstEpsbCntxtInfo->bitOpApn = pstRcvMsg->bitOpApn;
        NAS_ESM_SaveApnAddr(&stTmpApnInfo1, &pstRcvMsg->stApn);

        /* 将APN格式从未译码转为译码 */
        ulRslt = NAS_ESM_ApnReverseTransformation(  &stTmpApnInfo2,
                                                   &stTmpApnInfo1);
        /* APN转换不成功，仍用原有APN */
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_ERR_LOG("NAS_ESM_ProcSmPdpModify:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_ProcSmPdpModify_ENUM, ESM_APN_ERROR);
        }
        else
        {
            NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stApnInfo,
                                sizeof(APP_ESM_APN_INFO_STRU),
                                &stTmpApnInfo2,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /* 更改PCO IPv4 */
        NAS_ESM_MEM_SET_S(  &pstEpsbCntxtInfo->stPcoInfo,
                            sizeof(NAS_ESM_CONTEXT_PCO_STRU),
                            NAS_ESM_NULL,
                            sizeof(NAS_ESM_CONTEXT_PCO_STRU));

        /* 存储PCO IPV4项 */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv4Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv4Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv4Item);
        }

        /* 存储PCO IPV6项 */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv6Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv6Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv6Item);
        }

        /* 存储IM CN SIGNAL FLAG标识 */
        if ((NAS_ESM_OP_TRUE == pstRcvMsg->bitOpImCnSigalFlag))
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.enImsCnSignalFlag = pstRcvMsg->enImCnSignalFlag;
        }
    }

    /* 发送ID_ESM_ERABM_MDF_IND消息 */
    NAS_ESM_SndEsmRabmMdfIndMsg(ulEpsbId,ESM_ERABM_BEARER_RAT_LTE);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 支持EHRPD接入技术才通知EHSM */
    if (NAS_ESM_SUCCESS == NAS_EMM_IsEhrpdOr1XRatExist())
    {
        /* 拨号的场景要通知EHSM修改对应的CID信息 */
        NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(ulEpsbId);
    }
    #endif

    /* 打印承载信息 */
    NAS_ESM_PrintEpsbInfo(ulEpsbId);

    return ;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_ProcSmPdpDeactivate
 Description     : ESM处理SM PDP删除
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcSmPdpDeactivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    VOS_UINT8                           ucCnt            =  NAS_ESM_NULL;
    VOS_UINT32                          ulCurPdnNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulEpsbIdNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;
    VOS_UINT32                          aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_MEM_SET_S(  aulEpsId,
                        ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32),
                        0,
                        ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* 在EHRPD实体中根据EHRPD承载ID查找当前修改的PDN连接是否存在 */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(ulEpsbId, &ulIndex))
    {
        /* 通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND，只去激活1个EHRPD承载 */
        aulEpsId[0] = ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* 删除此PDN连接的信息 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }
#endif

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcSmPdpDeactivate:The pdp is already inactive!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcSmPdpDeactivate_ENUM, 1);
        return ;
    }

    /*如果当前承载为缺省承载*/
    if(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        /*查找当前PDN连接数*/
        ulCurPdnNum = NAS_ESM_GetCurPdnNum();

        /*PDN连接数减少1条*/
        if(ulCurPdnNum > 0)
        {
            ulCurPdnNum -= 1;
        }

        /*保存当前PDN连接数*/
        NAS_ESM_SetCurPdnNum(ulCurPdnNum);
    }

    /*更新ulEpsbIdNum、aulEpsbId，以便通知RABM*/
    aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

    /*循环承载信息，查找与此承载关联的专有承载*/
    for( ucCnt = NAS_ESM_MIN_EPSB_ID; ucCnt <= NAS_ESM_MAX_EPSB_ID; ucCnt++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucCnt);

        /*某一承载的Linked EPSB ID为当前承载ID*/
        if( (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType)
            && (NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)\
            && (pstEpsbCntxtInfo->ulLinkedEpsbId == ulEpsbId) )
        {
            /*更新ulEpsbIdNum、aulEpsbId，以便通知RABM*/
            aulEpsbId[ulEpsbIdNum++] = ucCnt;
        }
    }

    /*通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND*/
    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId, ESM_ERABM_BEARER_RAT_LTE);

    /*根据已记录的承载ID，循环释放承载资源*/
    for( ucCnt = 0; ucCnt < ulEpsbIdNum; ucCnt++ )
    {
        /*释放承载资源*/
        NAS_ESM_ClearEsmBearerResource(aulEpsbId[ucCnt]);

        /*关键事件上报*/
        NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_RELEASE(ulEpsbId));
    }

    if (NAS_ESM_L_MODE_STATUS_NORMAL == NAS_ESM_GetLModeStatus())
    {
        /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_LOCAL);
    }
    else
    {
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
    }
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/* end of NasEsmSmMsgProc.c */
