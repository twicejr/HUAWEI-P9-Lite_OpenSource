/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmRabmMsgProc.c
    Description : 处理RABM发给SM的消息
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.杨茜惠 00135146    2008-12-18  Modify BA8D00749
     3.杨茜惠 00135146    2009-03-06  Modify BA8D01127
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMRABMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMRABMMSGPROC_C
/*lint +e767*/


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



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_ESM_RabmMsgDistr()
 Description    : SM模块RABM消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RabmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pRabmMsg = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RabmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RabmMsgDistr_ENUM, LNAS_ENTRY);

    pRabmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pRabmMsg->ulMsgName)
    {
        /*如果收到的是ID_ESM_ERABM_REL_REQ消息*/
        case ID_ESM_ERABM_REL_REQ:

            /* 如果ESM处于非注册态，则直接返回 */
            if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
            {
                NAS_ESM_WARN_LOG("NAS_ESM_RabmMsgDistr:WARNING:Msg is discard cause ESM state is detached!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_RabmMsgDistr_ENUM, 1);
                return ;
            }


            /*清资源*/
            NAS_ESM_ClearEsmResource();
            break;

        /*RB未建立，本地去激活相应承载上下文*/
        case ID_ESM_ERABM_BEARER_STATUS_REQ:

            /*本地去激活承载上下文*/
            NAS_ESM_RcvEsmRabmBearerStatusReq((ESM_ERABM_BEARER_STATUS_REQ_STRU *) pRcvMsg);
            break;

        default:
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_RabmMsgDistr:WARNING:RABM->SM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_RabmMsgDistr_ENUM, 2);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetPdnAddr
 Description     : 获取某承载的PDN信息
 Input           : NAS_ESM_CONTEXT_IP_ADDR_STRU *pstPdnAddr,
                   VOS_UINT32 ulEpsbId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-7-8  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_GetPdnAddr
(
    NAS_ESM_CONTEXT_IP_ADDR_STRU       *pstPdnAddr,
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulEhrpdBearerId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex            = 0;
#endif

    if(VOS_NULL_PTR == pstPdnAddr)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetPdnAddr:Error:Input parameter is null!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetPdnAddr_ENUM, LNAS_PARAM_INVALID);
        return;
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 如果修改的是EHRPD承载，目前CL互操作只支持缺省承载，不支持专有承载 */
    if (ESM_ERABM_BEARER_RAT_EHRPD == enBearerCntxtRat)
    {
        /* 根据EHRPD承载ID查找到ESM对应的EHRPD承载实体索引 */
        if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(ulEhrpdBearerId, &ulIndex))
        {

            pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
            NAS_ESM_MEM_CPY_S(  pstPdnAddr,
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                &pstPdnEntity->stEhPdnContextInfo.stPdnAddr,
                                sizeof(EHSM_ESM_PDN_ADDR_STRU));

        }
        return;
    }
#endif
    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 若是专有承载，则获取关联缺省承载的EpsbCntxtTbl表地址 */
    if(NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(ulEpsbId))
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEpsbCntxtInfo->ulLinkedEpsbId);
    }

    /* 获取PDN信息 */
    if(NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPdnAddr)
    {
        NAS_ESM_MEM_CPY_S(  pstPdnAddr,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                            &pstEpsbCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetPdnAddr:Error:No Pdn Address!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetPdnAddr_ENUM, ESM_PDN_TYPE_ERROR);
    }
    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmActIndMsg
 Description    : SM模块发送ID_ESM_ERABM_ACT_IND消息函数
 Input          : VOS_UINT32                          LTE的承载ID
                  ESM_ERABM_BEARER_RAT_ENUM_UINT8     承载接入技术类型
                  VOS_UINT8                           EHRPD承载恢复标识
                  VOS_UINT32                          EHRPD承载ID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.wangchen 00209181  2014-09-20  Modify:视频通话，视频承载建立后，本地去激活问题修改
        RABM            ESM             EMM             RRC
        |               |               |               |
        |               |               |               |
        |               |LRRC_LRABM_RAB_IND(BEARID=7)   |
        |<----------------------------------------------|
        |               |               |               |
        |               |               |               |
        |               |               |               |
        |               |LMM_ESM_DATA_IND(bearid=7)     |
        |               |<--------------|               |
        |               |(ACT_DEDICT_EPS_BEAR_REQ)      |
        |               |               |               |
        |               |ACT_BEAR_ACP   |               |
        |               |-------------->|               |
        | ESM_LRABM_ACT_IND(bearid=7)   |               |
        |<--------------|               |               |
        |               |               |               |
        |BEAR_STATUS_REQ(bearid=5,6,7)  |               |
        |---->          |               |               |
        |               |               |               |
        |               |LRRC_LRABM_RAB_IND(BEARID=8)   |
        |<----------------------------------------------|
        |               |               |               |
        |               |               |               |
        |               |               |               |
        |               |LMM_ESM_DATA_IND(bearid=8)     |
        |               |<--------------|               |
        |               |(ACT_DEDICT_EPS_BEAR_REQ)      |
        |               |               |               |
        |               |ACT_BEAR_ACP   |               |
        |               |-------------->|               |
        | ESM_LRABM_ACT_IND(bearid=8)   |               |
        |<--------------|               |               |
        |               |               |               |
        | BEAR_STATUS_REQ(bearid=5,6,7) |               |
        |       ------->|               |               |
        |               ESM收到后，将承载8本地去激活
        |
     3.sunjitan 00193151  2016-01-14  Modify:CL多模互操作二阶段增加入参2和3和4
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmRabmActIndMsg(
    VOS_UINT32                          ulEpsbId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat,
    VOS_UINT8                           ucHandoverFlag,
    VOS_UINT32                          ulEhrpdBearerId
)
{
    VOS_UINT32                          ulTftPfNum         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt              = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpCid           = NAS_ESM_NULL;
    ESM_ERABM_ACT_IND_STRU             *pEsmRabmActIndMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pEsmRabmActIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_ACT_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pEsmRabmActIndMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmActIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmActIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmActIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmActIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmActIndMsg));

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    NAS_ESM_AssignErabmSessionId(&(pEsmRabmActIndMsg->ucSessionId));

    /* 拷贝承载的所有PF信息 */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            /*拷贝SDF的PF信息*/
            NAS_ESM_CopyRabmTftInfo(pEsmRabmActIndMsg->astTftPf + ulTftPfNum,\
                               pstSdfCntxtInfo->astSdfPfInfo,\
                               pstSdfCntxtInfo->ulSdfPfNum);

            ulTftPfNum += pstSdfCntxtInfo->ulSdfPfNum;
        }
    }

    /*填写消息内容*/
    pEsmRabmActIndMsg->ulEpsId = ulEpsbId;
    pEsmRabmActIndMsg->ulTftPfNum = ulTftPfNum;

    /* 填写PDN信息 */
    NAS_ESM_GetPdnAddr(&pEsmRabmActIndMsg->stPdnAddr,ulEpsbId, ulEhrpdBearerId,enBearerCntxtRat);

    pEsmRabmActIndMsg->enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
    pEsmRabmActIndMsg->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;
    pEsmRabmActIndMsg->ucQCI = pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

    /* 填写承载的接入技术类型，是否是handover的承载，以及EHRPD承载ID */
    pEsmRabmActIndMsg->enBearerCntxtRat = enBearerCntxtRat;
    pEsmRabmActIndMsg->ucHandoverFlag   = ucHandoverFlag;
    pEsmRabmActIndMsg->ulEhrpdBearerId  = ulEhrpdBearerId;

    /*填写消息头*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmActIndMsg,ID_ESM_ERABM_ACT_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pEsmRabmActIndMsg);

}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmMdfIndMsg()
 Description    : SM模块发送ID_ESM_ERABM_MDF_IND消息函数
 Input          : VOS_UINT32                          承载ID
                  ESM_ERABM_BEARER_RAT_ENUM_UINT8     承载类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunjitan 00193151  2016-01-14  Mofify for CL多模互操作
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmRabmMdfIndMsg(
    VOS_UINT32                          ulEpsbId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat
)
{
    VOS_UINT32                          ulTftPfNum         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt              = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpCid           = NAS_ESM_NULL;
    ESM_ERABM_MDF_IND_STRU             *pEsmRabmMdfIndMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex            = 0;
#endif

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pEsmRabmMdfIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_MDF_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pEsmRabmMdfIndMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmMdfIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmMdfIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmMdfIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmMdfIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmMdfIndMsg));

    /* 赋值承载接入技术类型 */
    pEsmRabmMdfIndMsg->enBearerCntxtRat  = enBearerCntxtRat;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 如果修改的是EHRPD承载，目前CL互操作只支持缺省承载，不支持专有承载 */
    if (ESM_ERABM_BEARER_RAT_EHRPD == enBearerCntxtRat)
    {
        /* 根据EHRPD承载ID查找到ESM对应的EHRPD承载实体索引 */
        if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(ulEpsbId, &ulIndex))
        {
            /* 取出实体 */
            pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

            pEsmRabmMdfIndMsg->enBearerCntxtType = ESM_ERABM_BEARER_TYPE_DEFAULT;
            pEsmRabmMdfIndMsg->ucHandoverFlag    = PS_FALSE;
            pEsmRabmMdfIndMsg->ulEhrpdBearerId   = ulEpsbId;
            pEsmRabmMdfIndMsg->ulEpsId           = ESM_ERABM_INVALID_BEARER_ID;

            /* 这个地方数据结构不一致，但枚举一致，1为IPV4，2为IPV6，3为IPV4V6 */
            pEsmRabmMdfIndMsg->stPdnAddr.ucIpType = pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType;

            /* 取出IPV4地址 */
            NAS_ESM_MEM_CPY_S(pEsmRabmMdfIndMsg->stPdnAddr.aucIpV4Addr,
                              APP_MAX_IPV4_ADDR_LEN,
                              pstPdnEntity->stEhPdnContextInfo.stPdnAddr.aucIpv4Addr,
                              EHSM_ESM_IPV4_ADDR_LEN);

            /* 取出IPV6地址 */
            NAS_ESM_MEM_CPY_S(pEsmRabmMdfIndMsg->stPdnAddr.aucIpV6Addr,
                              APP_MAX_IPV6_ADDR_LEN,
                              pstPdnEntity->stEhPdnContextInfo.stPdnAddr.aucIpv6Addr,
                              EHSM_ESM_IPV6_ADDR_LEN);
        }

        /*填写消息头*/
        NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmMdfIndMsg,ID_ESM_ERABM_MDF_IND);

        /* 调用消息发送函数 */
        NAS_ESM_SND_MSG(pEsmRabmMdfIndMsg);
        return;
    }
    #endif

    /* 如果修改的是LTE承载 */

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    /* 拷贝承载的所有PF信息 */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            /*拷贝SDF的PF信息*/
            NAS_ESM_CopyRabmTftInfo(pEsmRabmMdfIndMsg->astTftPf + ulTftPfNum,\
                               pstSdfCntxtInfo->astSdfPfInfo,\
                               pstSdfCntxtInfo->ulSdfPfNum);

            ulTftPfNum += pstSdfCntxtInfo->ulSdfPfNum;
        }
    }

    /*填写消息内容*/
    pEsmRabmMdfIndMsg->ulEpsId = ulEpsbId;
    pEsmRabmMdfIndMsg->ulTftPfNum = ulTftPfNum;

    /* 填写PDN信息 */
    NAS_ESM_GetPdnAddr(&pEsmRabmMdfIndMsg->stPdnAddr, ulEpsbId,ESM_ERABM_INVALID_BEARER_ID,enBearerCntxtRat);

    pEsmRabmMdfIndMsg->enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
    pEsmRabmMdfIndMsg->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;
    pEsmRabmMdfIndMsg->ucQCI= pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

    /*填写消息头*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmMdfIndMsg,ID_ESM_ERABM_MDF_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pEsmRabmMdfIndMsg);

}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmDeactIndMsg()
 Description    : SM模块发送ID_ESM_ERABM_DEACT_IND消息函数
 Input          : VOS_UINT32                         承载数目
                  VOS_UINT32                         承载ID列表
                  ESM_ERABM_BEARER_RAT_ENUM_UINT8    承载接入技术类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunjitan 00193151  2016-01-14  Mofify for CL多模互操作
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmDeactIndMsg(
    VOS_UINT32                          ulEpsbIdNum,
    const VOS_UINT32                   *pulEpsbId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat
)
{
    ESM_ERABM_DEACT_IND_STRU       *pEsmRabmDeactIndMsg   = VOS_NULL_PTR;

    /*检查入口参数*/
    if( (ulEpsbIdNum == 0) || (ulEpsbIdNum > NAS_ESM_MAX_EPSB_NUM) \
            || (VOS_NULL_PTR == pulEpsbId) )
    {
        /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmRabmDeactIndMsg:WARNING:Input Para error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndEsmRabmDeactIndMsg_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*分配空间并检验分配是否成功*/
    pEsmRabmDeactIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_DEACT_IND_STRU));

    if ( VOS_NULL_PTR == pEsmRabmDeactIndMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmDeactIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmDeactIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmDeactIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmDeactIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmDeactIndMsg));

    /*将ulEpsbIdNum、pulEpsbId填入pEsmRabmDeactIndMsg*/
    pEsmRabmDeactIndMsg->ulEpsIdNum = ulEpsbIdNum;

    pEsmRabmDeactIndMsg->enBearerCntxtRat = enBearerCntxtRat;

    NAS_ESM_MEM_CPY_S(  (VOS_UINT8*)pEsmRabmDeactIndMsg->aulEpsId,
                        sizeof(pEsmRabmDeactIndMsg->aulEpsId),
                        (VOS_UINT8*)pulEpsbId,
                        (pEsmRabmDeactIndMsg->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*填写消息头*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmDeactIndMsg,ID_ESM_ERABM_DEACT_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pEsmRabmDeactIndMsg);
}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmRelIndMsg()
 Description    : SM模块发送ID_ESM_ERABM_REL_IND消息函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmRelIndMsg( VOS_VOID )
{
    ESM_ERABM_REL_IND_STRU       *pEsmRabmRelIndMsg   = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pEsmRabmRelIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_REL_IND_STRU));

    if ( VOS_NULL_PTR == pEsmRabmRelIndMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmRelIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmRelIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmRelIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmRelIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmRelIndMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmRelIndMsg,ID_ESM_ERABM_REL_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pEsmRabmRelIndMsg);

}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmDeactAllMsg()
 Description    : SM模块针对所有已激活承载发送ID_ESM_ERABM_DEACT_IND消息函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmDeactAllMsg( VOS_VOID )
{
    VOS_UINT32                  ulEpsbId                    = NAS_ESM_NULL;
    VOS_UINT32                  ulActiveFlg                 = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmRabmDeactAllMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmRabmDeactAllMsg_ENUM, LNAS_ENTRY);

    /*找出已激活承载，并记录其ID*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*此承载已激活*/
        if( NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId) )
        {
            /*保存已激活承载ID,准备发送给RABM*/
            aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

            /*设置标识位*/
            ulActiveFlg = NAS_ESM_SUCCESS;
        }
    }

    /*如果所有的承载均未激活*/
    if( NAS_ESM_FAILURE == ulActiveFlg )
    {
        /*打印信息*/
        NAS_ESM_NORM_LOG("NAS_ESM_SndEsmRabmDeactAllMsg:NORMAL:no bearer active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmRabmDeactAllMsg_ENUM, 1);
        return ;
    }

    /*通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND*/
    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId, ESM_ERABM_BEARER_RAT_LTE);

}

/*****************************************************************************
 Function Name  : NAS_ESM_CopyRabmTftInfo()
 Description    : 拷贝TFT信息给RABM
 Input          : ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo
                  NAS_ESM_CONTEXT_TFT_STRU* pstCntxtTftInfo
 Output         : ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_CopyRabmTftInfo( ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo,
                                         const NAS_ESM_CONTEXT_TFT_STRU* pstCntxtTftInfo,
                                            VOS_UINT32 ulSdfPfNum)
{
    VOS_UINT32                          ulPfNum = NAS_ESM_NULL;

    ulPfNum = ulSdfPfNum;

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)pstRabmTftInfo,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU),
                        0,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU));

    /* 拷贝*/
    NAS_ESM_MEM_CPY_S(  pstRabmTftInfo,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU),
                        pstCntxtTftInfo,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU));
}


/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmRabmBearerStatusReq
 Description     : RB未建立，RABM发送当前承载上下文信息，
                    ESM去激活对应RB未建立承载上下文
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2009-3-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_RcvEsmRabmBearerStatusReq(const ESM_ERABM_BEARER_STATUS_REQ_STRU *pRcvMsg )
{
    VOS_UINT32                  ulCnt                           = NAS_ESM_NULL;
    VOS_UINT32                  ulQueryRslt                     = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbId                        = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                     = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                  ulStateTblIndex                 =  NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo              = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_ENTRY);

    /* 如果ESM处于非注册态，则直接返回 */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_FAIL);
        return ;
    }

    /* 连续激活两条承载时，避免ERABM发送的BEAR_STATUS_REQ消息时序错乱时，错误的本地去激活承载，因此增加
    OPID进行匹配；如果是RABM主动发送的消息不进行匹配；RABM针对ESM的ACT_IND消息回复BEAR_STATUS_REQ消息时，
    进行OPID匹配，如果匹配不成功，直接丢弃 */
    if ((pRcvMsg->ucSessionId != 0) && (pRcvMsg->ucSessionId != NAS_ESM_GetErabmSessionIdValue()))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq:WARNING:Msg is discard cause OPID is not match!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_ERROR);
        return;
    }

    /*取出消息中的EPSID信息*/
    ulEpsbIdNum = pRcvMsg->ulEpsIdNum;

    NAS_ESM_MEM_CPY_S(  aulEpsbId,
                        sizeof(aulEpsbId),
                        pRcvMsg->aulEpsId,
                        ulEpsbIdNum*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*轮询每一个承载信息*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*取出承载信息*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*如果此承载未激活*/
        if( NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState )
        {
            continue;
        }

        ulQueryRslt = NAS_ESM_FAILURE;

        /*查询ID_ESM_ERABM_BEARER_STATUS_IND消息的EPSID信息中是否包含此承载ID*/
        for( ulCnt = 0; ulCnt < ulEpsbIdNum; ulCnt++ )
        {
            if( ulEpsbId == aulEpsbId[ulCnt] )
            {
                ulQueryRslt = NAS_ESM_SUCCESS;
                break;
            }
        }

        /*如果不包含*/
        if( NAS_ESM_FAILURE == ulQueryRslt )
        {
            /*通知APP释放承载，并释放相关承载和资源*/
            NAS_ESM_DeactBearerAndInformApp(ulEpsbId);
            /*清除和中止与ulEpsbId关联的流程信息*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId, &ulStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }
        }
    }

    /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmClearClBearerNotifyMsg
 Description    : SM模块发送ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY消息函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151         2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmClearClBearerNotifyMsg(VOS_VOID)
{
    ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU        *pEsmRabmClearBearerMsg = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pEsmRabmClearBearerMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pEsmRabmClearBearerMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmClearClBearerNotifyMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmClearClBearerNotifyMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(NAS_ESM_GET_MSG_ENTITY(pEsmRabmClearBearerMsg),
                      NAS_ESM_GET_MSG_LENGTH(pEsmRabmClearBearerMsg),
                      0,
                      NAS_ESM_GET_MSG_LENGTH(pEsmRabmClearBearerMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmClearBearerMsg, ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pEsmRabmClearBearerMsg);
    return;
}
#endif


/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmRabmMsgProc.c */
