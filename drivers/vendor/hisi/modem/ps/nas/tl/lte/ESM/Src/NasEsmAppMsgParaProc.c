/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmAppMsgParaProc.c
    Description : 处理APP发给SM的参数设置查询类消息
    History     :
     1.丁丽 00128736        2008-09-01  Draft Enact
     2.祝义强 00138739      2008-09-11
     3.sunbing 49683        2008-10-12  Modify
     4.杨茜惠 00135146      2008-12-18  Modify BA8D00749
     5.杨茜惠 00135146      2008-12-18  Modify BA8D00752
     6.杨茜惠 00135146      2009-03-06  Modify BA8D01127
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMAPPMSGPARAPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMAPPMSGPARAPROC_C
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
 Function Name   : NAS_ESM_AppParaSetMsgProc
 Description     : 处理参数设置消息
 Input           :VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-11  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AppParaSetMsgProc( VOS_VOID *pRcvMsg )
{
    APP_PS_MSG_HEADER_STRU   *pAppMsg    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息类型，调用相应的参数设置函数*/
    switch (pAppMsg->ulMsgId)
    {
        case ID_APP_ESM_SET_TFT_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetTft(pRcvMsg);
            break;

        case ID_APP_ESM_SET_EPS_QOS_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetSdfQos(pRcvMsg);
            break;

        case ID_APP_ESM_SET_APN_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetApn(pRcvMsg);
            break;

        case ID_APP_ESM_SET_PCO_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetPco(pRcvMsg);
            break;

        case ID_APP_ESM_SET_PDN_TYPE_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetPdnType(pRcvMsg);
            break;

        case ID_APP_ESM_SET_BEARER_TYPE_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetBearType(pRcvMsg);
            break;

        case ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetPdpManagType(pRcvMsg);
            break;
        case ID_APP_ESM_SET_GW_AUTH_REQ:

            /*调用参数设置函数*/
            NAS_ESM_AppParaSetGwAuthInfo(pRcvMsg);
            break;
        case ID_APP_ESM_SET_CGDCONT_REQ:

            NAS_ESM_AppSetCgdcont(pRcvMsg);
            break;
        default:
            /*打印收到异常消息*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetMsgProc:WARNING:APP->SM ,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetMsgProc_ENUM, LNAS_MSG_INVALID);
            break;
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_AppParaSetCnf
 Description     : SM->APP返回参数设置结果
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-11  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_AppParaSetCnf( const NAS_ESM_APP_PARA_SET_RESLT_STRU *pstParaInfo)
{
    APP_ESM_PARA_SET_CNF_STRU   *pSmAppSetRslt   =VOS_NULL_PTR;
    VOS_UINT32                  ulCid           =0;


    /*获取传递参数中的ulCid参数*/
    ulCid = pstParaInfo->ulCid;

    /*分配空间并检验分配是否成功*/
    pSmAppSetRslt = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PARA_SET_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppSetRslt)
    {
         /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaSetCnf:ERROR:SM->APP Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaSetCnf_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppSetRslt),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppSetRslt),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppSetRslt));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppSetRslt,pstParaInfo->ulMsgId,\
                              pstParaInfo->usOriginalId,pstParaInfo->usTerminalId,\
                              pstParaInfo->ulSn);

    /*封装消息内容*/
    pSmAppSetRslt->ulOpId = pstParaInfo->ulOpId;
    pSmAppSetRslt->ulCid = ulCid;
    pSmAppSetRslt->ulSetRslt = pstParaInfo->ulSetRslt;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppSetRslt);

}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppTftOperation
 Description     : 检查App设置的TFT信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppTftOperation
(
    const APP_ESM_SET_TFT_REQ_STRU     *pAppTftMsg
)
{
    VOS_UINT32                          ulIsSdfActive       = NAS_ESM_FAILURE;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulPfIdx             = NAS_ESM_NULL;
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulCnt1              = NAS_ESM_NULL;
    VOS_UINT32                          ulPfId              = NAS_ESM_NULL;
    VOS_UINT8                           ucSdfPrecedence     = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    /*检验CID参数是否合法*/
    if(pAppTftMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppTftOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* 操作过程中，不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppTftMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppTftOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppTftOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* 判定SDF是否已激活 */
    ulIsSdfActive = NAS_ESM_QueryEpsbCntxtTblByCid(pAppTftMsg->ulCid, &ulEpsbId);

    /* 设置类型为删除的情况 */
    if (pAppTftMsg->enSetType != APP_ESM_PARA_SETTING)
    {
        /* 若此SDF已激活，则不允许删除QOS信息 */
        if (NAS_ESM_SUCCESS == ulIsSdfActive)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:Tft can not be deleted cause the sdf is active!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckAppTftOperation_ENUM, ESM_SDF_IS_ACTIVE, 1);
            return NAS_ESM_FAILURE;
        }

        return NAS_ESM_SUCCESS;
    }

    /* 判断TFT参数本身的有效性*/
    if (NAS_ESM_FAILURE == NAS_ESM_IsTftInfoValid(&pAppTftMsg->stAppTftInfo))
    {
        return NAS_ESM_FAILURE;
    }

    /* 判断本次TFT操作的有效性 */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(pAppTftMsg->ulCid);

    /* 同一个Cid下,优先级不能相同*/
    for (ulCnt1 = NAS_ESM_NULL; ulCnt1 < pstSdfPara->ulPfNum; ulCnt1++)
    {
        ucSdfPrecedence = pstSdfPara->astCntxtTftInfo[ulCnt1].ucPrecedence;
        ulPfId          = pstSdfPara->astCntxtTftInfo[ulCnt1].ucPacketFilterId;

        /* 允许对同一个Packetfilter设置相同的优先级*/
        if ((ucSdfPrecedence == pAppTftMsg->stAppTftInfo.ucPrecedence)
         && (ulPfId != pAppTftMsg->stAppTftInfo.ucPacketFilterId))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:Pf precedence error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppTftOperation_ENUM, 1);
            return NAS_ESM_FAILURE;
        }
    }

    /* 查找指定PF ID */
    if (NAS_ESM_FAILURE == NAS_ESM_QueryPfInTft(pAppTftMsg->stAppTftInfo.ucPacketFilterId,
                                                pstSdfPara->astCntxtTftInfo,
                                                pstSdfPara->ulPfNum,
                                               &ulPfIdx))
    {
        /* 若指定PF不存在，且此SDF已激活或者PF数已满，则返回设置错误 */
        if ((NAS_ESM_SUCCESS == ulIsSdfActive)
         || (pstSdfPara->ulPfNum >= NAS_ESM_MAX_SDF_PF_NUM))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:Pf can not be added cause the sdf is active!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckAppTftOperation_ENUM, ESM_SDF_IS_ACTIVE, 2);

            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppQosOperation
 Description     : 检查App设置的Qos信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppQosOperation
(
    const APP_ESM_SET_QOS_REQ_STRU           *pAppQosMsg
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*检验CID参数是否合法*/
    if(pAppQosMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppQosOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppQosOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* 操作过程中，不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppQosMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppQosOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppQosOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* 已经激活不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(pAppQosMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppQosOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppQosOperation_ENUM, ESM_CID_IS_ACTIVE);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppSdfQosOperation
 Description     : 检查App设置的SDF Qos信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppSdfQosOperation
(
    const APP_ESM_SET_EPS_QOS_REQ_STRU       *pAppSdfQosMsg
)
{
    VOS_UINT32                          ulEpsbId        = NAS_ESM_NULL;
    VOS_UINT32                          ulIsSdfActive   = NAS_ESM_FAILURE;
    VOS_UINT32                          ulStateId       = NAS_ESM_ILL_STATETAL_INDEX;

    /*检验CID参数是否合法*/
    if(pAppSdfQosMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppSdfQosOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppSdfQosOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* 操作过程中，不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppSdfQosMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppSdfQosOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppSdfQosOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* 判定SDF是否已激活 */
    ulIsSdfActive = NAS_ESM_QueryEpsbCntxtTblByCid(pAppSdfQosMsg->ulCid, &ulEpsbId);

    /* 设置类型为删除的情况 */
    if (pAppSdfQosMsg->enSetType != APP_ESM_PARA_SETTING)
    {
        /* 若此SDF已激活，则不允许删除QOS信息 */
        if (NAS_ESM_SUCCESS == ulIsSdfActive)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppSdfQosOperation:Qos can not be deleted cause the sdf is active!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppSdfQosOperation_ENUM, ESM_SDF_IS_ACTIVE);

            return NAS_ESM_FAILURE;
        }

        return NAS_ESM_SUCCESS;
    }

    /* 设置类型为设置的情况 */
    /* 判断SDF Qos参数本身的有效性*/
    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQosValid(&pAppSdfQosMsg->stSdfQosInfo))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppApnOperation
 Description     : 检查App设置的APN信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppApnOperation
(
    VOS_UINT32                          ulCid
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*检验CID参数是否合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppApnOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppApnOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }

    /* 操作过程中，不允许修改 */
    /* 协议中没有要求对操作过程中或者已经激活的SDF不能修改其静态属性，所以取消了原来不允许修改的限制 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppApnOperation:APP->SM ,change is allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppApnOperation_ENUM, ESM_CID_IS_OPERATING);
    }

    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppApnOperation:APP->SM ,change is allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppApnOperation_ENUM, ESM_CID_IS_ACTIVE);
    }

    return APP_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppPcoOperation
 Description     : 检查App设置的PCO信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppPcoOperation
(
    const APP_ESM_SET_PCO_REQ_STRU           *pAppPcoMsg
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*检验CID参数是否合法*/
    if(pAppPcoMsg->ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPcoOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* 操作过程中，不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppPcoMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPcoOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* 已经激活不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(pAppPcoMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPcoOperation_ENUM, ESM_CID_IS_ACTIVE);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppPdnTypeOperation
 Description     : 检查App设置的PDN 类型信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppPdnTypeOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          bitOpIpv4AddrAllocType,
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*检验CID参数是否合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }

    /* 操作过程中，不允许修改 */
    /* 协议中没有要求对操作过程中或者已经激活的SDF不能修改其静态属性，所以取消了原来不允许修改的限制 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_CID_IS_OPERATING);
    }

    /* 已经激活允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_CID_IS_ACTIVE);
    }

    /* 设置类型为删除的情况 */
    if (enSetType != APP_ESM_PARA_SETTING)
    {
        return APP_SUCCESS;
    }

    if ((enPdnType >= APP_ESM_PDN_TYPE_BUTT)
      ||(enPdnType == NAS_ESM_NULL))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,Pdn type error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_PDN_TYPE_ERROR);
        return APP_ERR_SM_PDN_TYPE_ILLEGAL;
    }

    if (NAS_ESM_OP_TRUE == bitOpIpv4AddrAllocType)
    {
        if (enIpv4AddrAllocType >= APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,IP address allocate type error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdnTypeOperation_ENUM, 1);
            return APP_ERR_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL;
        }
    }
    return APP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsTheOnlyOneDefltBearTypeSdf
 Description     : 在CID0-CID10之间，判断指定CID是否是唯一的承载类型为缺省的
                   SDF
 Input           : ulCid-------------------------CID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsTheOnlyOneDefltBearTypeSdf
(
     VOS_UINT32                         ulCid
)
{
    VOS_UINT32                          ulCnt                   = NAS_ESM_NULL;
    VOS_UINT32                          ulDefltBearTypeSdfNum   = NAS_ESM_NULL;
    VOS_UINT32                          ulFindCid               = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara              = VOS_NULL_PTR;

    /* 如果入参ulCid不位于[0,10]，则直接返回 */
    if (ulCid >= NAS_ESM_MAX_EPSB_NUM)
    {
        return PS_FALSE;
    }

    /* 遍历CID0-CID10，记录承载类型为缺省的SDF个数，以及最后一个承载类型为缺省的
       SDF对应的CID号 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_EPSB_NUM; ulCnt++)
    {
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCnt);

        if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
        {
            ulDefltBearTypeSdfNum++;
            ulFindCid = ulCnt;
        }
    }

    if (ulDefltBearTypeSdfNum == NAS_ESM_NULL)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTheOnlyOneDefltBearTypeSdf:Default Bearer Type sdf number is 0");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_IsTheOnlyOneDefltBearTypeSdf_ENUM, 1);
    }

    /* 在CID0-CID10中，入参ulCid指定SDF是否是唯一的承载类型为缺省的SDF，若是则
       返回PS_TRUE；若不是，则返回PS_FALSE */
    if ((ulDefltBearTypeSdfNum == NAS_ESM_DEFAULT_BEARER_TYPE_SDF_NUM_ONE)
         && (ulCid == ulFindCid))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppBearTypeOperation
 Description     : 检查App设置的承载类型信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppBearTypeOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType,
    VOS_UINT32                          bitOpLinkdCid,
    VOS_UINT32                          ulLinkdCid
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    /*检验CID参数是否合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }


    /* 如果本次操作要修改的内容与本地已经存储的内容相同，即如果是缺省类型，本次操作要修改成的承载类型与
       本地存储的相同，或者如果是专有承载类型，本次操作要修改成的承载类型和关联CID信息与本地存储的都相同，
       则直接反馈成功，允许修改；如果本次操作要修改成的内容与本地已存储的内容不同，且正在操作过程中或者已激活，
       则不允许修改*/

    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);
    /*承载属性没有变化*/
    if(pstSdfPara->enBearerCntxtType == enBearCidType)
    {
        /*缺省承载*/
        if(pstSdfPara->enBearerCntxtType != APP_ESM_CID_TYPE_DEDICATED)
        {
            return APP_SUCCESS;
        }

        if ((NAS_ESM_OP_TRUE== bitOpLinkdCid)
             &&(pstSdfPara->ulLinkdCId == ulLinkdCid))
        {
            return APP_SUCCESS;
        }
    }


    /*  操作过程中 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_IS_OPERATING);
        return APP_ERR_SM_CALL_CID_IN_OPERATION;
    }

    /* 已经激活不允许修改 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_IS_ACTIVE);
        return APP_ERR_SM_CALL_CID_ACTIVE;
    }

    /* 设置类型为删除的情况 */
    if (enSetType != APP_ESM_PARA_SETTING)
    {
        return APP_SUCCESS;
    }

    if (enBearCidType >= APP_ESM_CID_TYPE_BUTT)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,bearer type error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_TYPE_ERROR);
        return APP_ERR_SM_BEARER_TYPE_ILLEGAL;
    }

    if(APP_ESM_CID_TYPE_DEDICATED == enBearCidType)
    {
        /* 如果没有设置LinkCid，则返回设置失败 */
        if ((NAS_ESM_OP_FALSE == bitOpLinkdCid)
         || (ulLinkdCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,required LinkCid or LinkeCid error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_ERROR);
            return APP_ERR_SM_LINK_CID_INVALID;
        }

        /* 如果用户的这次设置会造成CID0-CID10中没有缺省承载类型的SDF，则返回设置错误 */
        if (PS_TRUE == NAS_ESM_IsTheOnlyOneDefltBearTypeSdf(ulCid))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,this sdf is the only one which is default bearer type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_SDF_ERROR);
            return APP_ERR_SM_MUST_EXIST_DEFAULT_TYPE_CID;
        }

        /* 如果此专有承载对应的linked承载类型为紧急类型，则返回设置失败 */
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulLinkdCid);
        if (APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,not allow dedicated bearer type for emergency bearer");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, 1);
            return APP_ERR_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED;
        }
    }

    return APP_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppPdpManagTypeOperation
 Description     : 检查App设置的承载管理类型信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppPdpManagTypeOperation
(
    const APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU *pAppBearManagTypeMsg
)
{
    if (pAppBearManagTypeMsg->enSetType != APP_ESM_PARA_SETTING)
    {
        /*打印异常消息*/
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdpManagTypeOperation:APP->SM ,Pdp manage type can not be del!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdpManagTypeOperation_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    if ((pAppBearManagTypeMsg->enAnsMode >= APP_ESM_ANSWER_MODE_BUTT)
      ||(pAppBearManagTypeMsg->enAnsType >= APP_ESM_ANSWER_RESULT_BUTT))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdpManagTypeOperation:APP->SM ,Pdp Manage Type Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdpManagTypeOperation_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_CheckAppGwAuthInfoOperation
 Description     : 检查App设置的网关鉴权信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 检查失败
                   NAS_ESM_SUCCESS -- 检查成功
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact
    2.niuxiufan 00181501     2012-6-11  modify 专有承载允许设置鉴权信息

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckAppGwAuthInfoOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_GW_AUTH_INFO_STRU           *pstGwAuthInfo
)
{
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*检验CID参数是否合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }

    /* 操作过程中，不允许修改 */
    /* 协议中没有要求对操作过程中或者已经激活的SDF不能修改其静态属性，所以取消了原来不允许修改的限制 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_CID_IS_OPERATING);
    }

    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_CID_IS_ACTIVE);
    }

    /* 设置类型为删除的情况 */
    if (enSetType != APP_ESM_PARA_SETTING)
    {
        return APP_SUCCESS;
    }


    /* 设置鉴权信息前，用户必须先设置APN信息；若没有,则提示没有设置APN*/
    if (pstSdfPara->bitOpApn == NAS_ESM_OP_FALSE)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->ESM ,no apn info!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_APN_ERROR);
    }
    return NAS_ESM_IsGwAuthInfoValid(pstGwAuthInfo);
}
/*****************************************************************************
 Function Name   : NAS_ESM_AppParaSetTft
 Description     : 设置TFT参数
 Input           :VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-11  Draft Enact
    2.sunbing 49683            2008-10-12 Modify
    3.liuwenyu 00143951        2010-09-07 Modify
*****************************************************************************/
VOS_VOID NAS_ESM_AppParaSetTft( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid            =0;
    VOS_UINT32                          ulTftIdx         = NAS_ESM_NULL;
    VOS_UINT8                           ucPacketFilterID = NAS_ESM_NULL;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType        =0;
    APP_ESM_SET_TFT_REQ_STRU           *pAppTftMsg       =VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara       =VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetTft is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetTft_ENUM, LNAS_ENTRY);

    pAppTftMsg = (APP_ESM_SET_TFT_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid*/
    ulCid = pAppTftMsg->ulCid;

    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_TFT_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*得到参数设置类型*/
    enSetType = pAppTftMsg->enSetType;

    /* 检查App设置的TFT信息 */
    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppTftOperation(pAppTftMsg))
    {
        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = APP_FAILURE;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING != enSetType)
    {
        /*根据ulCid，删除本地相应结构中的TFT信息*/
        pstSdfPara->ulPfNum = NAS_ESM_NULL;

        NAS_ESM_MEM_SET_S(  (VOS_VOID *)(pstSdfPara->astCntxtTftInfo),
                            sizeof(APP_ESM_TFT_INFO_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                            VOS_NULL,
                            sizeof(APP_ESM_TFT_INFO_STRU) * NAS_ESM_MAX_SDF_PF_NUM);

        /*向APP返回设置确认*/
        stParaInfo.ulSetRslt = APP_SUCCESS;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    ucPacketFilterID = pAppTftMsg->stAppTftInfo.ucPacketFilterId;

    /* 查找预添加的packet filter id是否已存在，若存在，则用预添加的packet
       filter 信息替换查找到的packet filter */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryPfInTft(ucPacketFilterID,
                                                pstSdfPara->astCntxtTftInfo,
                                                pstSdfPara->ulPfNum,
                                               &ulTftIdx))
    {
        NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&(pstSdfPara->astCntxtTftInfo[ulTftIdx]),
                            sizeof(APP_ESM_TFT_INFO_STRU),
                            (const VOS_VOID *)&(pAppTftMsg->stAppTftInfo),
                            sizeof(APP_ESM_TFT_INFO_STRU));

        /*向APP返回设置确认*/
        stParaInfo.ulSetRslt = APP_SUCCESS;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }


    /* 若预添加的packet filter id不存在，且当前此SDF的静态信息中的packet filter数
       未达到最大数，则将此packet filter添加到SDF的静态信息中*/
    ulTftIdx = pstSdfPara->ulPfNum;
    pstSdfPara->ulPfNum++;

    NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&(pstSdfPara->astCntxtTftInfo[ulTftIdx]),
                        sizeof(APP_ESM_TFT_INFO_STRU),
                        (const VOS_VOID *)&(pAppTftMsg->stAppTftInfo),
                        sizeof(APP_ESM_TFT_INFO_STRU));

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppParaSetSdfQos
 Description     : 设置SDFQOS参数
 Input           :VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-12  Draft Enact
    2.sunbing 49683            2008-10-12 Modify
*****************************************************************************/
VOS_VOID NAS_ESM_AppParaSetSdfQos( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid               = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType           = 0;
    APP_ESM_SET_EPS_QOS_REQ_STRU       *pAppSdfQosMsg       = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetSdfQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetSdfQos_ENUM, LNAS_ENTRY);

    pAppSdfQosMsg=(APP_ESM_SET_EPS_QOS_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid =pAppSdfQosMsg->ulCid;

    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_EPS_QOS_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppSdfQosOperation(pAppSdfQosMsg))
    {
        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = APP_FAILURE;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*得到参数设置类型*/
    enSetType=pAppSdfQosMsg->enSetType;

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*从接收消息中获得SDFQOS信息,保存在本地*/
        pstSdfPara->bitOpSdfQos = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstSdfPara->stSdfQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                            (VOS_VOID*)&(pAppSdfQosMsg->stSdfQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    }
    else    /*设置类型为删除*/
    {
        /*根据ulCid，删除本地相应结构中的SDFQOS信息*/
        pstSdfPara->bitOpSdfQos = NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET_S(  (VOS_VOID*)&(pstSdfPara->stSdfQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                            0,
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    }

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

}


VOS_VOID NAS_ESM_AppParaSetApn( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType       = 0;
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    APP_ESM_SET_APN_REQ_STRU           *pAppApnMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo      = {NAS_ESM_NULL};
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo    = {NAS_ESM_NULL};

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetApn_ENUM, LNAS_ENTRY);

    pAppApnMsg = (APP_ESM_SET_APN_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid = pAppApnMsg->ulCid;

    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_APN_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppApnOperation(pAppApnMsg->ulCid);

    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetApn:NAS_ESM_CheckAppApnOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetApn_ENUM, LNAS_FAIL);

        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*得到参数设置类型*/
    enSetType = pAppApnMsg->enSetType;

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*从接收消息中获得APN信息*/
        /*根据ulCid，把APN信息保存在本地相应结构中*/
        ulRslt = NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                          &pAppApnMsg->stApnInfo);
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetApn:WARNING:APP->SM ,App Set Apn Invalid!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetApn_ENUM, 1);

            /*向APP返回设置设置失败消息*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }

        NAS_ESM_MEM_CPY_S(  &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pAppApnMsg->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        /*设置信元标志位*/
        pstSdfPara->bitOpApn = NAS_ESM_OP_TRUE;
    }
    else    /*设置类型为删除*/
    {
        /*根据ulCid，删除本地相应结构中的APN信息*/
        /*设置信元标志位*/
        pstSdfPara->bitOpApn= NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET_S(  (VOS_VOID*)&(pstSdfPara->stApnInfo),
                            sizeof(APP_ESM_APN_INFO_STRU),
                            0,
                            sizeof(APP_ESM_APN_INFO_STRU));
    }

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

}


VOS_VOID NAS_ESM_AppParaSetPco( VOS_VOID *pRcvMsg )
{
    APP_ESM_SET_PCO_REQ_STRU           *pAppPcoMsg      = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetPco is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetPco_ENUM, LNAS_ENTRY);

    pAppPcoMsg=(APP_ESM_SET_PCO_REQ_STRU*)pRcvMsg;

    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_PCO_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);


    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppPcoOperation(pAppPcoMsg))
    {
        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = APP_FAILURE;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }


    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

}


VOS_VOID NAS_ESM_AppParaSetPdnType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType       = 0;
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    APP_ESM_SET_PDN_TYPE_REQ_STRU      *pAppPdnTypeMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetPdnType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetPdnType_ENUM, LNAS_ENTRY);

    pAppPdnTypeMsg=(APP_ESM_SET_PDN_TYPE_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid =pAppPdnTypeMsg->ulCid;

    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_PDN_TYPE_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppPdnTypeOperation(pAppPdnTypeMsg->ulCid,
                                              pAppPdnTypeMsg->enSetType,
                                              pAppPdnTypeMsg->enPdnType,
                                              pAppPdnTypeMsg->bitOpIpv4AddrAllocType,
                                              pAppPdnTypeMsg->enIpv4AddrAllocType);
    if (APP_SUCCESS != ulRslt)
    {
        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*得到参数设置类型*/
    enSetType=pAppPdnTypeMsg->enSetType;

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*设置信元标志位*/
        pstSdfPara->bitOpPdnType = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType = pAppPdnTypeMsg->enPdnType;

        if (NAS_ESM_OP_TRUE == pAppPdnTypeMsg->bitOpIpv4AddrAllocType)
        {
            pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_TRUE;
            pstSdfPara->enIpv4AddrAllocType  = pAppPdnTypeMsg->enIpv4AddrAllocType;
        }
    }
    else
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_FALSE;
        pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_FALSE;
    }

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);
}

VOS_VOID NAS_ESM_AppParaSetBearType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid               = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType           = 0;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    APP_ESM_SET_BEARER_TYPE_REQ_STRU   *pAppBearTypeMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetBearType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetBearType_ENUM, LNAS_ENTRY);

    pAppBearTypeMsg=(APP_ESM_SET_BEARER_TYPE_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid =pAppBearTypeMsg->ulCid;

    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_BEARER_TYPE_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppBearTypeOperation(pAppBearTypeMsg->ulCid,
                                               pAppBearTypeMsg->enSetType,
                                               pAppBearTypeMsg->enBearCidType,
                                               pAppBearTypeMsg->bitOpLinkdCid,
                                               pAppBearTypeMsg->ulLinkdCid);

    if (APP_SUCCESS != ulRslt)
    {
        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*得到参数设置类型*/
    enSetType=pAppBearTypeMsg->enSetType;

    /*设置类型为删除*/
    if(APP_ESM_PARA_SETTING != enSetType)
    {
        /*根据ulCid，复位CID类型为初始化值*/
        pstSdfPara->enBearerCntxtType = APP_ESM_CID_TYPE_DEFAULT;

        /*删除关联CID*/
        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;
        pstSdfPara->ulLinkdCId = 0;

        /*向APP返回设置确认*/
        stParaInfo.ulSetRslt = APP_SUCCESS;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return ;
    }

    /*从接收消息中获得BearType信息,保存在本地结构中*/
    pstSdfPara->enBearerCntxtType = (VOS_UINT8)pAppBearTypeMsg->enBearCidType;

    /*设置类型为设置*/
    if(APP_ESM_CID_TYPE_DEDICATED == pAppBearTypeMsg->enBearCidType)
    {

        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_TRUE;
        pstSdfPara->ulLinkdCId = pAppBearTypeMsg->ulLinkdCid;
    }
    else
    {
        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;
    }

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);
}


VOS_VOID NAS_ESM_AppParaSetPdpManagType( VOS_VOID *pRcvMsg )
{
    APP_ESM_PARA_SET_ENUM_UINT32           enSetType               = 0;
    APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU *pAppBearManagTypeMsg    =VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU          *pBearMagageInfo         =VOS_NULL_PTR;
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *pAppBearManagTypeCnf    =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetPdpManagType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetPdpManagType_ENUM, LNAS_ENTRY);

    pAppBearManagTypeMsg = (APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU*)pRcvMsg;

    /*分配空间并检验分配是否成功*/
    pAppBearManagTypeCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppBearManagTypeCnf)
    {
         /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaSetPdpManagType:ERROR:SM->APP Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaSetPdpManagType_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppBearManagTypeCnf),
                        NAS_ESM_GET_MSG_LENGTH(pAppBearManagTypeCnf),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppBearManagTypeCnf));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppBearManagTypeCnf,ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF,\
                               pAppBearManagTypeMsg->usTerminalId,pAppBearManagTypeMsg->usOriginalId,\
                               pAppBearManagTypeMsg->ulSN);

    /*封装消息内容*/
    pAppBearManagTypeCnf->ulOpId = pAppBearManagTypeMsg->ulOpId;

    /*得到参数设置类型*/
    enSetType = pAppBearManagTypeMsg->enSetType;

    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppPdpManagTypeOperation(pAppBearManagTypeMsg))
    {
        /*向APP返回设置设置失败消息*/
        pAppBearManagTypeCnf->ulSetRslt = APP_FAILURE;
        NAS_ESM_SND_MSG(pAppBearManagTypeCnf);
        return;
    }

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*从接收消息中获得承载管理类型信息*/
        /*获取本地承载管理信息结构指针*/
        pBearMagageInfo=NAS_ESM_GetBearerManageInfoAddr();
        pBearMagageInfo->enMode=(VOS_UINT8)pAppBearManagTypeMsg->enAnsMode;
        pBearMagageInfo->enType=(VOS_UINT8)pAppBearManagTypeMsg->enAnsType;

        /*向APP返回设置确认*/
        pAppBearManagTypeCnf->ulSetRslt = APP_SUCCESS;
    }
    else
    {
        /*打印异常消息*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetPdpManagType:WARNING:APP->SM ,The para can not be del!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetPdpManagType_ENUM, LNAS_PARAM_INVALID);

        /*向APP返回设置设置失败消息*/
        pAppBearManagTypeCnf->ulSetRslt = APP_FAILURE;
    }


    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppBearManagTypeCnf);
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppParaSetGwAuthInfo
 Description     : 设置网关鉴权参数
 Input           : VOS_VOID *pRcvMsg---------收到的用户消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppParaSetGwAuthInfo( VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType           = NAS_ESM_NULL;
    APP_ESM_SET_GW_AUTH_REQ_STRU       *pstAppGwAuthMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo          = {NAS_ESM_NULL};

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetGwAuthInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetGwAuthInfo_ENUM, LNAS_ENTRY);

    pstAppGwAuthMsg =(APP_ESM_SET_GW_AUTH_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid = pstAppGwAuthMsg->ulCid;


    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_GW_AUTH_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppGwAuthInfoOperation(pstAppGwAuthMsg->ulCid,
                                                 pstAppGwAuthMsg->enSetType,
                                                 &(pstAppGwAuthMsg->stGwAuthInfo));

    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetGwAuthInfo:NAS_ESM_CheckAppGwAuthInfoOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetGwAuthInfo_ENUM, LNAS_FAIL);

        /*向APP返回设置设置失败消息*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*得到参数设置类型*/
    enSetType = pstAppGwAuthMsg->enSetType;

    /*根据参数设置类型，进行消息的设置与删除操作*/
    /*如果设置类型为:设置*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*设置信元标志位*/
        pstSdfPara->bitOpGwAuthInfo = NAS_ESM_OP_TRUE;

        /*从接收消息中获得GW AUTH信息*/
        /*根据ulCid，把GW AUTH信息保存在本地相应结构中*/
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&pstSdfPara->stGwAuthInfo,
                            sizeof(APP_ESM_GW_AUTH_INFO_STRU),
                            (VOS_VOID*)&pstAppGwAuthMsg->stGwAuthInfo,
                            sizeof(APP_ESM_GW_AUTH_INFO_STRU));

    }
    else    /*设置类型为删除*/
    {
        /*根据ulCid，删除本地相应结构中的PCO信息*/
        pstSdfPara->bitOpGwAuthInfo = NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET_S(  (VOS_VOID*)&(pstSdfPara->stGwAuthInfo),
                            sizeof(APP_ESM_GW_AUTH_INFO_STRU),
                            0,
                            sizeof(APP_ESM_GW_AUTH_INFO_STRU));
    }

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppSetCgdcont
 Description     : 设置PDP上下文
 Input           : VOS_VOID *pRcvMsg---------收到的用户消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-06-03  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppSetCgdcont( VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    APP_ESM_SET_CGDCONT_REQ_STRU       *pstAppCgdcontMsg    = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo          = {NAS_ESM_NULL};

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppSetCgdcont is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSetCgdcont_ENUM, LNAS_ENTRY);

    pstAppCgdcontMsg =(APP_ESM_SET_CGDCONT_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid = pstAppCgdcontMsg->ulCid;


    /*设置回复消息的部分内容*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_CGDCONT_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    if (NAS_ESM_OP_TRUE == pstAppCgdcontMsg->bitOpApn)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetApn(pstAppCgdcontMsg->ulCid,
                                                    pstAppCgdcontMsg->enSetType,
                                                    pstAppCgdcontMsg->stApnInfo);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppSetCgdcont: APN ERROR!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppSetCgdcont_ENUM, ESM_APN_ERROR, 1);

            /*向APP返回设置设置失败消息*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }
    }


    if (NAS_ESM_OP_TRUE == pstAppCgdcontMsg->bitOpPdnType)
    {
        ulRslt = NAS_ESM_AppCgdconntOrNDISconnSetPdnType(pstAppCgdcontMsg->ulCid,
                                                        pstAppCgdcontMsg->enSetType,
                                                        pstAppCgdcontMsg->enPdnType,
                                                        pstAppCgdcontMsg->bitOpIpv4AddrAllocType,
                                                        pstAppCgdcontMsg->enIpv4AddrAllocType);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppSetCgdcont: APN ERROR!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppSetCgdcont_ENUM, ESM_APN_ERROR, 2);

            /*向APP返回设置设置失败消息*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }
    }

    if (NAS_ESM_OP_TRUE == pstAppCgdcontMsg->bitOpBearType)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetBearType(pstAppCgdcontMsg->ulCid,
                                                           pstAppCgdcontMsg->enSetType,
                                                           pstAppCgdcontMsg->enBearCidType,
                                                           NAS_ESM_OP_FALSE,
                                                           0);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppSetCgdcont: APN ERROR!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppSetCgdcont_ENUM, ESM_APN_ERROR, 3);

            /*向APP返回设置设置失败消息*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }
    }

    pstSdfPara                      = NAS_ESM_GetSdfParaAddr(ulCid);
    pstSdfPara->bitOpPcscfDiscovery = pstAppCgdcontMsg->bitOpPcscfDiscovery;
    pstSdfPara->enPcscfDiscovery    = pstAppCgdcontMsg->enPcscfDiscovery;
    pstSdfPara->bitOpImsCnSignalFlag= pstAppCgdcontMsg->bitOpImsCnSignalFlag;
    pstSdfPara->enImsCnSignalFlag   = pstAppCgdcontMsg->enImsCnSignalFlag;

    /*向APP返回设置确认*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppSetCnfParaInfo
 Description     : 设置参数设置回复的部分信息
 Input           : NAS_ESM_APP_PARA_SET_HEAD_STRU* pstRcvInfo
 Output          : NAS_ESM_APP_PARA_SET_RESLT_STRU*  pstParaInfo
 Return          : VOS_VOID

 History         :
    1.sunbing      2008-10-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppSetCnfParaInfo( NAS_ESM_APP_PARA_SET_RESLT_STRU*  pstParaInfo,
                                                const NAS_ESM_APP_PARA_SET_HEAD_STRU * pstRcvInfo)
{
    /*得到消息中指示的ulOpId,ulCid*/
    pstParaInfo->ulCid = pstRcvInfo->ulCid;
    pstParaInfo->ulOpId = pstRcvInfo->ulOpId;

    /*交叉MID参数*/
    pstParaInfo->usOriginalId = pstRcvInfo->usTerminalId;
    pstParaInfo->usTerminalId = pstRcvInfo->usOriginalId;

    /*设置SN参数*/
    pstParaInfo->ulSn = pstRcvInfo->ulSN;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppNdisconnSetBearType
 Description     : 拨号过程中，设置beartype
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen  00209181        2013-05-29    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_AppCgdcontOrNdisConnSetBearType
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType,
    VOS_UINT32                          bitOpLinkdCid,
    VOS_UINT32                          ulLinkdCid
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppCgdcontOrNdisConnSetBearType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppCgdcontOrNdisConnSetBearType_ENUM, LNAS_ENTRY);

    if(APP_ESM_CID_TYPE_DEDICATED == enBearCidType)
    {

        return APP_ERR_SM_BEARER_TYPE_ILLEGAL;
    }
    /*得到消息中指示的ulCid**/

    ulRslt = NAS_ESM_CheckAppBearTypeOperation(ulCid,
                                               enSetType,
                                               enBearCidType,
                                               bitOpLinkdCid,
                                               ulLinkdCid);

    /* 已经激活不允许修改 */
    if (NAS_ESM_SUCCESS != ulRslt)
    {
        return ulRslt;
    }


    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*得到参数设置类型*/

    /*设置类型为删除*/
    if(APP_ESM_PARA_SETTING != enSetType)
    {
        /*根据ulCid，复位CID类型为初始化值*/
        pstSdfPara->enBearerCntxtType = APP_ESM_CID_TYPE_DEFAULT;

        /*删除关联CID*/
        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;
        pstSdfPara->ulLinkdCId = 0;

        return APP_SUCCESS;
    }
    /*从接收消息中获得BearType信息,保存在本地结构中*/
    pstSdfPara->enBearerCntxtType = (VOS_UINT8)enBearCidType;
    pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;

    return APP_SUCCESS;
}


VOS_UINT32 NAS_ESM_AppCgdconntOrNDISconnSetPdnType
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          bitOpIpv4AddrAllocType,
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType

)
{
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppCgdconntOrNDISconnSetPdnType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppCgdconntOrNDISconnSetPdnType_ENUM, LNAS_ENTRY);


    /*得到消息中指示的ulCid**/

    ulRslt = NAS_ESM_CheckAppPdnTypeOperation(ulCid,
                                              enSetType,
                                              enPdnType,
                                              bitOpIpv4AddrAllocType,
                                              enIpv4AddrAllocType);

    if (APP_SUCCESS != ulRslt)
    {
        /*向APP返回设置设置失败消息*/
        return ulRslt;
    }

    /*得到参数设置类型*/

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*设置信元标志位*/
        pstSdfPara->bitOpPdnType = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType = enPdnType;
        if (NAS_ESM_OP_TRUE == bitOpIpv4AddrAllocType)
        {
            pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_TRUE;
            pstSdfPara->enIpv4AddrAllocType  = enIpv4AddrAllocType;
        }

    }
    else
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_FALSE;
        pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_FALSE;
    }

    return APP_SUCCESS;
}



VOS_UINT32 NAS_ESM_AppCgdcontOrNdisConnSetApn
(
    VOS_UINT32                                  ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32                enSetType,
    APP_ESM_APN_INFO_STRU                       stApnInfo
)
{
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo    = {NAS_ESM_NULL};

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppCgdcontOrNdisConnSetApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppCgdcontOrNdisConnSetApn_ENUM, LNAS_ENTRY);


    /*得到消息中指示的ulCid**/
    ulRslt = NAS_ESM_CheckAppApnOperation(ulCid);
    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppCgdcontOrNdisConnSetApn:NAS_ESM_CheckAppApnOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppCgdcontOrNdisConnSetApn_ENUM, LNAS_FAIL);
        return ulRslt;
    }

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);


    /*根据参数设置类型，进行消息的设置与删除操作*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*从接收消息中获得APN信息*/
        /*根据ulCid，把APN信息保存在本地相应结构中*/
        ulRslt = NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                          &stApnInfo);
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppCgdcontOrNdisConnSetApn:WARNING:APP->SM ,App Set Apn Invalid!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppCgdcontOrNdisConnSetApn_ENUM, 1);

            return ulRslt;
        }

        NAS_ESM_MEM_CPY_S(  &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        /*设置信元标志位*/
        pstSdfPara->bitOpApn = NAS_ESM_OP_TRUE;
    }
    else    /*设置类型为删除*/
    {
        /*根据ulCid，删除本地相应结构中的APN信息*/
        /*设置信元标志位*/
        pstSdfPara->bitOpApn= NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET_S(  (VOS_VOID*)&(pstSdfPara->stApnInfo),
                            sizeof(APP_ESM_APN_INFO_STRU),
                            0,
                            sizeof(APP_ESM_APN_INFO_STRU));
    }

    return APP_SUCCESS;

}

/*****************************************************************************
 Function Name   : NAS_ESM_AppNdisConnSetGwAuthInfo
 Description     : 设置网关鉴权参数
 Input           : VOS_VOID *pRcvMsg---------收到的用户消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-05-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_AppNdisConnSetGwAuthInfo( VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU          *pstAppGwAuthMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppNdisConnSetGwAuthInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisConnSetGwAuthInfo_ENUM, LNAS_ENTRY);

    pstAppGwAuthMsg =(APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulCid**/
    ulCid = pstAppGwAuthMsg->ulCid;

    ulRslt = NAS_ESM_CheckAppGwAuthInfoOperation(pstAppGwAuthMsg->ulCid,
                                                 APP_ESM_PARA_SETTING,
                                                 &(pstAppGwAuthMsg->stGwAuthInfo));

    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisConnSetGwAuthInfo:NAS_ESM_CheckAppGwAuthInfoOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisConnSetGwAuthInfo_ENUM, LNAS_FAIL);

        /*向APP返回设置设置失败消息*/
        return ulRslt;
    }

    /*根据ulCid，获取本地NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*设置信元标志位*/
    pstSdfPara->bitOpGwAuthInfo = NAS_ESM_OP_TRUE;

    /*从接收消息中获得GW AUTH信息*/
    /*根据ulCid，把GW AUTH信息保存在本地相应结构中*/
    NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&pstSdfPara->stGwAuthInfo,
                        sizeof(APP_ESM_GW_AUTH_INFO_STRU),
                        (VOS_VOID*)&pstAppGwAuthMsg->stGwAuthInfo,
                        sizeof(APP_ESM_GW_AUTH_INFO_STRU));

    return APP_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppParaQueryMsgProc
 Description     : 处理参数查询消息
 Input           :VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-11  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AppParaQueryMsgProc(VOS_VOID *pRcvMsg)
{
    APP_PS_MSG_HEADER_STRU   *pAppMsg    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息类型，调用相应的参数查询函数*/
    switch (pAppMsg->ulMsgId)
    {

        case ID_APP_ESM_INQ_BEAER_QOS_REQ:

            /*调用参数查询函数*/
            NAS_ESM_AppParaQueryBearQos(pRcvMsg);

            break;

        case ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ:

             NAS_ESM_AppQueryDynamicPdpMsgProc(pRcvMsg);

             break;
        case ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ:

             NAS_ESM_AppQueryDynamicEpsQosMsgProc(pRcvMsg);

             break;
        case ID_APP_ESM_INQ_DYNAMIC_TFT_REQ:

             NAS_ESM_AppQueryDynamicTftMsgProc(pRcvMsg);

             break;
        default:

            /*打印收到异常消息*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryMsgProc:WARNING:APP->SM ,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryMsgProc_ENUM, LNAS_MSG_INVALID);

            break;
    }
}

/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppParaQueryTft( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_TFT_REQ_STRU         *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_TFT_CNF_STRU         *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryTft is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryTft_ENUM, LNAS_ENTRY);

    pAppQueryMsg =(APP_ESM_INQ_TFT_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*得到消息中指示的ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_TFT_CNF_STRU));
    /*lint +e433 +e826*/

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryTft:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryTft_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头，MID交叉*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_TFT_CNF,\
                              pAppQueryMsg->usTerminalId,pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid =ulCid;
    pAppCnfMsg->ulOpId =ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*检验CID参数是否合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryTft:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryTft_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*根据ulCid，获取NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if (NAS_ESM_NULL == pstSdfPara->ulPfNum)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {
            /*设置TFT参数*/
            pAppCnfMsg->ulPfNum = pstSdfPara->ulPfNum;

            NAS_ESM_MEM_CPY_S(  (VOS_VOID *)pAppCnfMsg->astPfInfo,
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU) * APP_ESM_TFT_MAX_PF_NUM,
                                (const VOS_VOID *)pstSdfPara->astCntxtTftInfo,
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstSdfPara->ulPfNum);
        }
    }
    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}
/*lint -specific(+e433)*/


VOS_VOID NAS_ESM_AppParaQuerySdfQos( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_EPS_QOS_REQ_STRU     *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_EPS_QOS_CNF_STRU     *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQuerySdfQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQuerySdfQos_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_EPS_QOS_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*得到消息中指示的ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*分配空间并检验分配是否成功*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_EPS_QOS_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQuerySdfQos:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQuerySdfQos_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_EPS_QOS_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId= ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*如果CID参数不合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQuerySdfQos:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQuerySdfQos_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*根据ulCid，获取NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {
            /*封装SDF QOS消息结构*/
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pAppCnfMsg->stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                (VOS_VOID*)&(pstSdfPara->stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }
    }

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}


VOS_VOID NAS_ESM_AppParaQueryApn( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                      ulOpId          = 0;
    VOS_UINT32                      ulCid           = 0;
    APP_ESM_INQ_APN_REQ_STRU       *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_APN_CNF_STRU       *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU          *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryApn_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_APN_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*得到消息中指示的ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*根据ulCid，获取NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*分配空间并检验分配是否成功*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_APN_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryApn:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryApn_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_APN_CNF,
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId= ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*如果CID参数不合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryApn:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryApn_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {

        if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpApn)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {

            NAS_ESM_MEM_CPY_S(  &pAppCnfMsg->stApnInfo,
                                sizeof(APP_ESM_APN_INFO_STRU),
                                &pstSdfPara->stApnInfo,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }
    }

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}

#if 0



/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppParaQueryPco( VOS_VOID *pRcvMsg )
{

    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_PCO_REQ_STRU         *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_PCO_CNF_STRU         *pAppCnfMsg      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryPco is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryPco_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_PCO_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*得到消息中指示的ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PCO_CNF_STRU));/* lint !e826 */
    /*lint +e433 +e826*/

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryPco:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryPco_ENUM, LNAS_NULL_PTR);
        return;
    }



    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_PCO_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;


    /*如果CID参数不合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryPco:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryPco_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }


    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);


}
#endif

/*lint -specific(+e433)*/


VOS_VOID NAS_ESM_AppParaQueryPdnType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_PDN_TYPE_REQ_STRU    *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_PDN_TYPE_CNF_STRU    *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryPdnType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryPdnType_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_PDN_TYPE_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*得到消息中指示的ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*分配空间并检验分配是否成功*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDN_TYPE_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryPdnType:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryPdnType_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_PDN_TYPE_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*如果CID参数不合法*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryPdnType:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryPdnType_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*根据ulCid，获取NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpPdnType)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {
            pAppCnfMsg->enPdnType = pstSdfPara->enPdnType;

            if (NAS_ESM_OP_TRUE == pstSdfPara->bitIpv4AddrAllocType)
            {
                pAppCnfMsg->bitOpIpv4AddrAllocType = NAS_ESM_OP_TRUE;
                pAppCnfMsg->enIpv4AddrAllocType    = pstSdfPara->enIpv4AddrAllocType;
            }
        }
    }

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}

#if 0

VOS_VOID NAS_ESM_AppParaQueryBearType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                              ulOpId          = 0;
    VOS_UINT32                              ulCid           = 0;
    APP_ESM_INQ_BEARER_TYPE_REQ_STRU     *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_BEARER_TYPE_CNF_STRU     *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU                  *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryBearType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryBearType_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_BEARER_TYPE_REQ_STRU*)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*得到消息中指示的ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*分配空间并检验分配是否成功*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_BEARER_TYPE_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryBearType:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryBearType_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_BEARER_TYPE_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryBearType:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryBearType_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*根据ulCid，获取NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpLinkdCId)
         && (APP_ESM_CID_TYPE_DEDICATED == pstSdfPara->enBearerCntxtType))
        {

            /*返回关联承载CID和承载类型*/
            pAppCnfMsg->bitOpLinkdCid = NAS_ESM_OP_TRUE;
            pAppCnfMsg->enBearCidType = pstSdfPara->enBearerCntxtType;
            pAppCnfMsg->ulLinkdCid = pstSdfPara->ulLinkdCId;
        }
        else
        {
            /*只返回承载类型*/
            pAppCnfMsg->bitOpLinkdCid = NAS_ESM_OP_FALSE;
            pAppCnfMsg->enBearCidType = pstSdfPara->enBearerCntxtType;
        }
    }

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}


VOS_VOID NAS_ESM_AppParaQueryPdpManagType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                                  ulOpId          =0;
    APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU      *pAppQueryMsg    =VOS_NULL_PTR;
    APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU      *pAppCnfMsg      =VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU               *pBearMagageInfo =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryPdpManagType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryPdpManagType_ENUM, LNAS_ENTRY);

    pAppQueryMsg = (APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU *)pRcvMsg;

    /*得到消息中指示的ulOpId*/
    ulOpId = pAppQueryMsg->ulOpId;

    /*分配空间并检验分配是否成功*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryPdpManagType:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryPdpManagType_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头，交叉ID信息*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_PDP_MANAGER_TYPE_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulOpId = ulOpId;

    /*获取NAS_ESM_PDP_MANAGE_INFO_STRU结构指针*/
    pBearMagageInfo = NAS_ESM_GetBearerManageInfoAddr();

    /*设置应答模式:0,自动；1,手动*/
    pAppCnfMsg->enAnsMode = pBearMagageInfo->enMode;

    /*若应答模式为自动*/
    if(APP_ESM_ANSWER_MODE_AUTO == pAppCnfMsg->enAnsMode)
    {
        /*设置自动应答类型*/
        pAppCnfMsg->enAnsType = pBearMagageInfo->enType;
    }

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);
}
#endif


VOS_VOID NAS_ESM_QueryBearQos(VOS_UINT32   ulEpsbId,
                                          APP_ESM_INQ_BEAER_QOS_CNF_STRU      *pAppCnfMsg)
{
    VOS_UINT32                          ulTmpEpsbId      = ulEpsbId;
    VOS_UINT32                          ulCIdNum         = VOS_NULL;
    VOS_UINT32                          ulCnt            = VOS_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    APP_ESM_INQ_BEAER_QOS_CNF_STRU     *pTmpAppCnfMsg    = pAppCnfMsg;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_QueryBearQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_QueryBearQos_ENUM, LNAS_ENTRY);

    if(((ulTmpEpsbId < NAS_ESM_MIN_EPSB_ID) || (ulTmpEpsbId > NAS_ESM_MAX_EPSB_ID))
        && (NAS_ESM_UNASSIGNED_EPSB_ID != ulTmpEpsbId))
    {
        pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_REJ;
        return;
    }
    else if(NAS_ESM_UNASSIGNED_EPSB_ID == ulTmpEpsbId)
    {
        /*遍历所有承载信息*/
        for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
        {
            /*根据EpsId取出承载信息*/
            pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulCnt);

            /*如果此承载为指定承载类型，且已关联CID*/
            if( NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)
            {
                /*记录到pTmpAppCnfMsg*/
                pTmpAppCnfMsg->astQosInfo[ulCIdNum].ulEpsbId = ulCnt;

                NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pTmpAppCnfMsg->astQosInfo[ulCIdNum].stQos),
                                    sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                    (VOS_VOID*)&(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),
                                    sizeof(APP_ESM_EPS_QOS_INFO_STRU));

                ulCIdNum ++;
            }
        }
        if(VOS_NULL == ulCIdNum)
        {
            pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_REJ;
            return;
        }
        pTmpAppCnfMsg->ulEpsbIdNum = ulCIdNum;
        pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_ACCEPT;
        return;
    }
    else
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulTmpEpsbId);

        if(NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)
        {
            pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_REJ;
            return;
        }

        pTmpAppCnfMsg->ulEpsbIdNum = 1;
        pTmpAppCnfMsg->astQosInfo[0].ulEpsbId = ulTmpEpsbId;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pTmpAppCnfMsg->astQosInfo[0].stQos),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                            (VOS_VOID*)&(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));

        pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_ACCEPT;
        return;
    }
}


/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppParaQueryBearQos( VOS_VOID *pRcvMsg)
{
    VOS_UINT32                           ulEpsbId        = VOS_NULL;
    APP_ESM_INQ_BEAER_QOS_REQ_STRU      *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_BEAER_QOS_CNF_STRU      *pAppCnfMsg      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryBearQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryBearQos_ENUM, LNAS_ENTRY);

    pAppQueryMsg = (APP_ESM_INQ_BEAER_QOS_REQ_STRU*)pRcvMsg;

    ulEpsbId = pAppQueryMsg->ulEpsbId;
    /*lint -e433 -e826*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_BEAER_QOS_CNF_STRU));
    /*lint +e433 +e826*/
    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryBearQos:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryBearQos_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头，交叉ID信息*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_BEAER_QOS_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    NAS_ESM_QueryBearQos(ulEpsbId, pAppCnfMsg);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);
}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_AppParaQueryGwAuthInfo
 Description     : 查询网关鉴权信息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppParaQueryGwAuthInfo(VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulOpId          = NAS_ESM_NULL;
    VOS_UINT32                          ulCid           = NAS_ESM_NULL;
    APP_ESM_INQ_GW_AUTH_REQ_STRU       *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_GW_AUTH_CNF_STRU       *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryGwAuthInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, LNAS_ENTRY);

    pAppQueryMsg = (APP_ESM_INQ_GW_AUTH_REQ_STRU*)pRcvMsg;

    ulCid = pAppQueryMsg->ulCid;
    ulOpId = pAppQueryMsg->ulOpId;

    /*根据ulCid，获取NAS_ESM_BEARER_CNTXT_PARA_STRU结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_GW_AUTH_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryGwAuthInfo:ERROR:APP->ESM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*填写消息头，交叉ID信息*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_GW_AUTH_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*封装消息内容*/
    pAppCnfMsg->ulCid                   = ulCid;
    pAppCnfMsg->ulOpId                  = ulOpId;

    pAppCnfMsg->ulRslt                  = APP_SUCCESS;

    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryGwAuthInfo:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
        NAS_ESM_SND_MSG(pAppCnfMsg);
        return;
    }

    if ((NAS_ESM_OP_FALSE == pstSdfPara->bitOpGwAuthInfo)
        || (NAS_ESM_BEARER_TYPE_DEDICATED == pstSdfPara->enBearerCntxtType))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryGwAuthInfo:WARNING:APP->SM ,Gw Auth info is not exit or Bear type is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, 1);
        pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        NAS_ESM_SND_MSG(pAppCnfMsg);
        return;
    }

    NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&pAppCnfMsg->stGwAuthInfo,
                        sizeof(APP_ESM_GW_AUTH_INFO_STRU),
                        (VOS_VOID*)&pstSdfPara->stGwAuthInfo,
                        sizeof(APP_ESM_GW_AUTH_INFO_STRU));

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);
}

/*****************************************************************************
  Function Name   : NAS_ESM_SndEsmAppBearerQosIndMsg
  Description     : SM向APP返回消息:NAS_ESM_SndEsmAppBearerQosIndMsg;
  Input           : ulEpsBId
  Output          : None
  Return          : VOS_UINT32

  History         :
     1.niezhouyu 00108792      2009-3-9  Draft Enact

 ***********************************NAS_ESM_SndEsmAppBearerSetupIndMsg******************************************/
VOS_VOID  NAS_ESM_SndEsmAppBearerQosIndMsg(VOS_UINT32 ulEpsbId)
{
    VOS_UINT16                          usOriginalId        = 0;
    VOS_UINT16                          usTerminalId        = 0;
    APP_ESM_INQ_BEAER_QOS_IND_STRU     *pEsmAppQosInd      =VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       =VOS_NULL_PTR;

    /*获得本地EpsB承载上下文结构指针*/
    pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*分配空间并检验分配是否成功*/
    pEsmAppQosInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_BEAER_QOS_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pEsmAppQosInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppBearerQosIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppBearerQosIndMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmAppQosInd),
                        NAS_ESM_GET_MSG_LENGTH(pEsmAppQosInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmAppQosInd));

    /*分配本次过程APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pEsmAppQosInd,ID_APP_ESM_INQ_BEAER_QOS_IND,\
                              usOriginalId,usTerminalId,0);

    /*封装消息内容*/
    NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pEsmAppQosInd->stQosInfo),
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                        (VOS_VOID*)&(pEpsCntxtInfo->stEpsQoSInfo.stQosInfo),
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    pEsmAppQosInd->ulEpsbId = ulEpsbId;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pEsmAppQosInd);

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryDynamicPdpMsgProc
 Description     : 处理APP查询PDP动态信息的消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-09-21  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppQueryDynamicPdpMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU      *pstEsmAppPdpDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU               *pstEpsbCntxtInfo       = VOS_NULL_PTR;
    APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ_STRU      *pAppMsg                = VOS_NULL_PTR;
    VOS_UINT32                                  ulEpsbId               = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = ( APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ_STRU* )pRcvMsg;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pstEsmAppPdpDynaCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU));
    /*lint +e433 +e826*/
    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEsmAppPdpDynaCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEsmAppPdpDynaCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pstEsmAppPdpDynaCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEsmAppPdpDynaCnfMsg));

    /*填写消息头，MID交叉*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pstEsmAppPdpDynaCnfMsg,
                               ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF,
                               pAppMsg->usTerminalId,
                               pAppMsg->usOriginalId,
                               pAppMsg->ulSN);

    /*封装消息内容*/
    pstEsmAppPdpDynaCnfMsg->ulCid  = pAppMsg->ulCid;
    pstEsmAppPdpDynaCnfMsg->ulOpId = pAppMsg->ulOpId;
    pstEsmAppPdpDynaCnfMsg->ulRslt = APP_SUCCESS;

    /*检验CID参数是否合法*/
    if(pAppMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, ESM_CID_ERROR);
        pstEsmAppPdpDynaCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pstEsmAppPdpDynaCnfMsg);
        return ;
    }

    /*there is a EpsID mapped CID, get EpsID or return*/
    if (NAS_ESM_SUCCESS != NAS_ESM_QueryEpsbCntxtTblByCid(pAppMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);
        pstEsmAppPdpDynaCnfMsg->ulRslt = APP_ERR_SM_BEARER_INACTIVE;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pstEsmAppPdpDynaCnfMsg);
        return;
    }

    /*根据EpsId取出承载信息*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstEsmAppPdpDynaCnfMsg->ulEpsbId = pstEpsbCntxtInfo->ulEpsbId;

    /* set PDN address information for this msg response,if Eps bearer has */
    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPdnAddr)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpPdnAddr = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&pstEsmAppPdpDynaCnfMsg->stPDNAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                            (const VOS_VOID *)&pstEpsbCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&pstEsmAppPdpDynaCnfMsg->stSubnetMask,
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (const VOS_VOID *)&pstEpsbCntxtInfo->stSubnetMask,
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpGateWayAddrInfo)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&pstEsmAppPdpDynaCnfMsg->stGateWayAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                            (const VOS_VOID *)&pstEpsbCntxtInfo->stGateWayAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }

    /* set APN information for this msg response,if Eps bearer has */
    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpApn)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpApn = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&pstEsmAppPdpDynaCnfMsg->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            (const VOS_VOID*)&pstEpsbCntxtInfo->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));
    }

    /* set Link Cid for the msg response,if Eps bearer has */
    pstEsmAppPdpDynaCnfMsg->ulLinkCid    = NAS_ESM_GetLinkCidByActiveCid(pAppMsg->ulCid);
    if (NAS_ESM_ILL_CID != pstEsmAppPdpDynaCnfMsg->ulLinkCid)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpLinkCid = NAS_ESM_OP_TRUE;
    }
    else
    {
        pstEsmAppPdpDynaCnfMsg->bitOpLinkCid = NAS_ESM_OP_FALSE;
    }

    /*设置PCO信息*/
    if(NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPco)
    {
        NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo(pstEsmAppPdpDynaCnfMsg,pstEpsbCntxtInfo);
    }

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEsmAppPdpDynaCnfMsg);

    return;
}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryDynamicEpsQosMsgProc
 Description     : 处理APP查询动态QOS信息的消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-21  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_AppQueryDynamicEpsQosMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU     *pstEsmAppQosDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU                *pstSdfInfo       = VOS_NULL_PTR;
    APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU     *pAppMsg          = VOS_NULL_PTR;
    VOS_UINT32                                  ulEpsbId;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppQueryDynamicEpsQosMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = ( APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU* )pRcvMsg;

    /*分配空间并检验分配是否成功*/
    pstEsmAppQosDynaCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEsmAppQosDynaCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryDynamicEpsQosMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEsmAppQosDynaCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pstEsmAppQosDynaCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEsmAppQosDynaCnfMsg));

    /*填写消息头，MID交叉*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pstEsmAppQosDynaCnfMsg,
                               ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF,
                               pAppMsg->usTerminalId,
                               pAppMsg->usOriginalId,
                               pAppMsg->ulSN);

    /*封装消息内容*/
    pstEsmAppQosDynaCnfMsg->ulCid  = pAppMsg->ulCid;
    pstEsmAppQosDynaCnfMsg->ulOpId = pAppMsg->ulOpId;
    pstEsmAppQosDynaCnfMsg->ulRslt   = APP_SUCCESS;

    /*检验CID参数是否合法*/
    if(pAppMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppPDPDynamicQueryMsgProc:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, ESM_CID_ERROR);
        pstEsmAppQosDynaCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pstEsmAppQosDynaCnfMsg);
        return;
    }

    if (NAS_ESM_SUCCESS != NAS_ESM_QueryEpsbCntxtTblByCid(pAppMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicEpsQosMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);
        pstEsmAppQosDynaCnfMsg->ulRslt = APP_ERR_SM_BEARER_INACTIVE;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pstEsmAppQosDynaCnfMsg);
        return;
    }

    pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(pAppMsg->ulCid);

    /* 拷贝QOS动态信息 */
    NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&pstEsmAppQosDynaCnfMsg->stSdfQosInfo,
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                        (const VOS_VOID *)&pstSdfInfo->stSdfQosInfo.stQosInfo,
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEsmAppQosDynaCnfMsg);

}


/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryDynamicTftMsgProc
 Description     : 处理APP查询动态TFT信息的消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-21  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppQueryDynamicTftMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU         *pstEsmAppTftDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU              *pstSdfInfo       = VOS_NULL_PTR;
    APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU         *pAppMsg          = VOS_NULL_PTR;
    VOS_UINT32                                ulEpsbId;
    VOS_UINT32                                ulCnt            = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppQueryDynamicTftMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = ( APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU* )pRcvMsg;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pstEsmAppTftDynaCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU));
    /*lint +e433 +e826*/
    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEsmAppTftDynaCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryDynamicTftMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEsmAppTftDynaCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pstEsmAppTftDynaCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEsmAppTftDynaCnfMsg));

    /*填写消息头，MID交叉*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pstEsmAppTftDynaCnfMsg,
                               ID_APP_ESM_INQ_DYNAMIC_TFT_CNF,
                               pAppMsg->usTerminalId,
                               pAppMsg->usOriginalId,
                               pAppMsg->ulSN);

    /*封装消息内容*/
    pstEsmAppTftDynaCnfMsg->ulCid  = pAppMsg->ulCid;
    pstEsmAppTftDynaCnfMsg->ulOpId = pAppMsg->ulOpId;
    pstEsmAppTftDynaCnfMsg->ulRslt   = APP_SUCCESS;

    /*检验CID参数是否合法*/
    if(pAppMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicTftMsgProc:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, ESM_CID_ERROR);
        pstEsmAppTftDynaCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pstEsmAppTftDynaCnfMsg);
        return;
    }

    if (NAS_ESM_SUCCESS != NAS_ESM_QueryEpsbCntxtTblByCid(pAppMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicTftMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);
        pstEsmAppTftDynaCnfMsg->ulRslt = APP_ERR_SM_BEARER_INACTIVE;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pstEsmAppTftDynaCnfMsg);
        return;
    }

    pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(pAppMsg->ulCid);

    /* 拷贝TFT动态信息 */
    pstEsmAppTftDynaCnfMsg->ulPfNum = pstSdfInfo->ulSdfPfNum;
    NAS_ESM_MEM_CPY_S(  (VOS_VOID *)&pstEsmAppTftDynaCnfMsg->astPfInfo[0],
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * APP_ESM_TFT_MAX_PF_NUM,
                        (const VOS_VOID *)&pstSdfInfo->astSdfPfInfo[0],
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstSdfInfo->ulSdfPfNum);

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstEsmAppTftDynaCnfMsg->ulPfNum; ulCnt++)
    {
        pstEsmAppTftDynaCnfMsg->astPfInfo[ulCnt].ucNwPacketFilterId++;
    }
    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEsmAppTftDynaCnfMsg);

}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo
 Description     : 通过APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF消息上报用户网关鉴权信息
 Input           : VOS_VOID *pstRsvMsg
                   VOS_VOID *pstCntxtInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo( VOS_VOID *pstRsvMsg ,VOS_VOID *pstCntxtInfo)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU       *pstEsmAppPdpDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU                *pstEpsCntxtInfo        = VOS_NULL_PTR;
    NAS_ESM_PCO_TRANSFORM_STRU                   stTransPco             = {NAS_ESM_NULL};

    pstEpsCntxtInfo = pstCntxtInfo;
    pstEsmAppPdpDynaCnfMsg = pstRsvMsg;

    NAS_ESM_TransformPcoStru(   pstEpsCntxtInfo->stPdnAddrInfo.ucIpType,
                                    &(pstEpsCntxtInfo->stPcoInfo),
                                    &stTransPco);

    if (stTransPco.ucDnsSerNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo:Dns is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 1);
        pstEsmAppPdpDynaCnfMsg->bitOpDnsPrim    = NAS_ESM_OP_FALSE;
        pstEsmAppPdpDynaCnfMsg->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucDnsSerNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 2);
        pstEsmAppPdpDynaCnfMsg->bitOpDnsPrim    = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stDnsPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        pstEsmAppPdpDynaCnfMsg->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 3);
        pstEsmAppPdpDynaCnfMsg->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        pstEsmAppPdpDynaCnfMsg->bitOpDnsSec     = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stDnsPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stDnsSecAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[1]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (stTransPco.ucPcscfNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 4);
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfPrim  = NAS_ESM_OP_FALSE;
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucPcscfNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 5);
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stPCscfPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astPcscf[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        pstEsmAppPdpDynaCnfMsg->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 6);
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfSec   = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)(VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stPCscfPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)(VOS_VOID*)&(stTransPco.astPcscf[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stPCscfSecAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astPcscf[1]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }

    pstEsmAppPdpDynaCnfMsg->bitOpImsCnSignalFlag    = pstEpsCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag;
    pstEsmAppPdpDynaCnfMsg->enImsCnSignalFlag       = pstEpsCntxtInfo->stPcoInfo.enImsCnSignalFlag;
}

/*****************************************************************************
 Function Name   : NAS_ESM_BearerCntxtParaInit
 Description     : 参数初始化，初始化本地结构体数组:
                                astSdfPara[NAS_ESM_MAX_UE_CONTRUL_CID_NUM]
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-17    Draft Enact
    2.lihong00150010           2010-08-12   Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_BearerCntxtParaInit( VOS_VOID )
{
    NAS_ESM_SDF_PARA_STRU          *pstBearCntxtPara  = VOS_NULL_PTR;
    VOS_UINT32                      ulCur             = NAS_ESM_NULL;

    /* 初始化处CID0-CID19的承载类型为专有承载 */
    for (ulCur = 0; ulCur < NAS_ESM_MAX_UE_CONTRUL_CID; ulCur++ )
    {
        pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(ulCur);

        NAS_ESM_MEM_SET_S(  pstBearCntxtPara,
                            sizeof(NAS_ESM_SDF_PARA_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_PARA_STRU));

        pstBearCntxtPara->bitOpLinkdCId         = NAS_ESM_OP_TRUE;
        pstBearCntxtPara->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEDICATED;
        pstBearCntxtPara->ulLinkdCId            = 20;
    }

    /* 初始化处CID20的承载类型为缺省承载 */
    pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_MAX_UE_CONTRUL_CID);

    NAS_ESM_MEM_SET_S(  pstBearCntxtPara,
                        sizeof(NAS_ESM_SDF_PARA_STRU),
                        0,
                        sizeof(NAS_ESM_SDF_PARA_STRU));

    pstBearCntxtPara->bitOpPdnType          = NAS_ESM_OP_TRUE;
    pstBearCntxtPara->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstBearCntxtPara->enPdnType             = APP_ESM_PDN_TYPE_IPV4;

    for (ulCur = 0; ulCur < NAS_ESM_MAX_CID_NUM; ulCur++ )
    {
        pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(ulCur);
        pstBearCntxtPara->ulCId = ulCur;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_BearerManageInfoInit
 Description     : 初始化承载管理类型，初始化APP应答模式；
 Input           : NAS_ESM_PDP_MANAGE_INFO_STRU *pstBearerManInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_BearerManageInfoInit(NAS_ESM_PDP_MANAGE_INFO_STRU *pstBearerManInfo  )
{
    /*初始化承载管理类型为接受网络请求，初始化承载管理模式为自动应答*/
    pstBearerManInfo->enType = NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT;   /* 承载管理类型初始化 */
    pstBearerManInfo->enMode = NAS_ESM_BEARER_MANAGE_MODE_AUTO;     /* 承载管理模式初始化 */

}
/*****************************************************************************
 Function Name   : NAS_ESM_IsPrefixInfoExist
 Description     : 判断前缀信息是否存在
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-3-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsPrefixInfoExist(VOS_UINT8 ucEpsId)
{
    VOS_UINT32                          i;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsId);

    /*前缀信息不存在，前8个字节全0表示不存在，不需要发送*/

    for (i = 0; i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        if (NAS_ESM_NULL != pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr[i])
        {
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsPrefixInfoExist
 Description     : 判断前缀信息是否相同
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-3-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_MatchPrefixInfo
(
    const VOS_UINT8  *pucLocalPrefix,
    const VOS_UINT8  *pucPrefix
)
{
    VOS_UINT32                          i;

    /*前缀信息前8个字节全相同表示相同，不需要发送*/
    for (i = 0; i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        if (pucLocalPrefix[i] != pucPrefix[i])
        {
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppIpv6InfoNotifyMsgProc
 Description     : APS->ESM IPv6 前缀信息的处理
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2011-11-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AppIpv6InfoNotifyMsgProc(VOS_VOID* pRcvMsg)
{
    APP_ESM_IPV6_INFO_NOTIFY_STRU      *pstIpv6Notify = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucEpsbId = 0;

    pstIpv6Notify = (APP_ESM_IPV6_INFO_NOTIFY_STRU *)pRcvMsg;
    ucEpsbId = pstIpv6Notify->ucEpsbId;
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsbId);

    if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc:Eps bearer is not active!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 1);
        return;
    }

    /* 如果前缀个数为零，则直接返回 */
    if (NAS_ESM_NULL == pstIpv6Notify->ucIpv6PrefixNum)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc: Ipv6 prefix num is zero!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 2);
        return;
    }

    /*前缀信息不存在，前8个字节全0表示不存在，不需要发送*/
    if (NAS_ESM_SUCCESS == NAS_ESM_IsPrefixInfoExist(ucEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc:Prefix info is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 3);

        /*判断前缀是否发生变更，不变更就不发送*/
        if (NAS_ESM_FAILURE == NAS_ESM_MatchPrefixInfo(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,pstIpv6Notify->astIpv6PrefixArray[0].aucPrefix))
        {
            NAS_ESM_NORM_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc:Prefix info change!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 4);
            NAS_ESM_SndEsmEmmBearerModifyReq(ucEpsbId);
        }
    }

    NAS_ESM_MEM_SET_S(  pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,
                        APP_MAX_IPV6_ADDR_LEN,
                        NAS_ESM_NULL,
                        pstIpv6Notify->astIpv6PrefixArray[0].ucPrefixLen);

    /* 取第一个IPv6前缀保存至承载Pdn地址 IPv6地址前8个字节 */
    NAS_ESM_MEM_CPY_S(  pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,
                        APP_MAX_IPV6_ADDR_LEN,
                        pstIpv6Notify->astIpv6PrefixArray[0].aucPrefix,
                        pstIpv6Notify->astIpv6PrefixArray[0].ucPrefixLen);

    /* 发送ID_ESM_ERABM_MDF_IND消息 */
    NAS_ESM_SndEsmRabmMdfIndMsg((VOS_UINT32)ucEpsbId,ESM_ERABM_BEARER_RAT_LTE);

   /* 向SM发送承载修改消息 */
    NAS_ESM_SndSmEspBearerMdfIndMsg((VOS_UINT32)ucEpsbId);

}
/*lint +e961*/
/*lint +e960*/

/* niuxiufan DT begin */
/*****************************************************************************
 Function Name   : NAS_ESM_GetActPdpInfo
 Description     :获取已激活PDP信息,用于给OM上报
 Input           : NAS_OM_ACT_PDP_INFO_STRU   *
 Output          : NAS_OM_ACT_PDP_INFO_STRU   *
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-09-08  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_GetActPdpInfo
(
        NAS_OM_ACT_PDP_INFO_STRU   *pActPdpInfo
)
{
    VOS_UINT32          ulEpsbId = NAS_ESM_MIN_EPSB_ID;
    VOS_UINT32          ulActEpsbNum = 0;

    for (ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ESM_BEARER_STATE_ACTIVE ==
            NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->enBearerCntxtState)
        {
            pActPdpInfo->stEpsbInfo[ulActEpsbNum].ulEpsbId = ulEpsbId;
            pActPdpInfo->stEpsbInfo[ulActEpsbNum].enBearerType =
                            NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->enBearerCntxtType;

            if ( NAS_ESM_OP_TRUE == NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->bitOpApn)
            {
                NAS_ESM_MEM_CPY_S(  &(pActPdpInfo->stEpsbInfo[ulActEpsbNum].stApn),
                                    sizeof(APP_ESM_APN_INFO_STRU),
                                    &(NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->stApnInfo),
                                    sizeof(APP_ESM_APN_INFO_STRU));
            }

            if (NAS_ESM_OP_TRUE == NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->bitOpPdnAddr)
            {

                NAS_ESM_MEM_CPY_S(  &(pActPdpInfo->stEpsbInfo[ulActEpsbNum].stIpAddr),
                                    sizeof(APP_ESM_IP_ADDR_STRU),
                                    &(NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->stPdnAddrInfo),
                                    sizeof(APP_ESM_IP_ADDR_STRU));
            }

            if (NAS_ESM_OP_TRUE == NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->bitOpEpsQos)
            {

                NAS_ESM_MEM_CPY_S(  &(pActPdpInfo->stEpsbInfo[ulActEpsbNum].stSdfQosInfo),
                                    sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                    &(NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->stEpsQoSInfo.stQosInfo),
                                    sizeof(APP_ESM_EPS_QOS_INFO_STRU));
            }

            ulActEpsbNum++;

        }
    }

    pActPdpInfo->ulActEpsbNum = ulActEpsbNum;

}

/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryActPdpInfoMsgProc
 Description     : 处理APP查询动态PDP信息的消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-21  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppQueryActPdpInfoMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_PDP_INFO_REQ_STRU    *pAppQueryMsg;
    APP_ESM_INQ_PDP_INFO_CNF_STRU    *pAppCnfMsg;
    VOS_UINT32                        ulOpId;

    pAppQueryMsg=(APP_ESM_INQ_PDP_INFO_REQ_STRU*)pRcvMsg;

    if (pAppQueryMsg->enCmd == DT_CMD_STOP)
    {
        g_ulRptPdpStatus  = APP_ESM_DT_REPORT_STATUS_CLOSE;
    }
    else
    {
        g_ulRptPdpStatus  = APP_ESM_DT_REPORT_STATUS_OPEN;
    }

    /*得到消息中指示的ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;


    /*分配空间并检验分配是否成功*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDP_INFO_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryActPdpInfoMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryActPdpInfoMsgProc_ENUM, LNAS_NULL_PTR);
        return;
    }


    /*填写消息头*/
    /* OM融合，所有透传消息CNF和REQ中的usOriginalId和usTerminalId必须对应，不能颠倒 */
    NAS_ESM_WRITE_APP_DT_CNF_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_DT_INQ_PDP_INFO_CNF,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->ulSN);
    /*封装消息内容*/
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEsmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID *)pAppCnfMsg);
    }
#endif
    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppCnfMsg);

    NAS_ESM_ReportActPdpInfo();

}

/* niuxiufan DT end */
/*****************************************************************************
 Function Name   : NAS_ESM_InitLocalIpsupportInfo
 Description     : 初始化UE支持LOCAL IP ADDRESS的能力
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2014-09-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_InitLocalIpsupportInfo(VOS_VOID)
{
    LNAS_LMM_NV_NAS_LOCALIP_CAP_STRU    stNasLocalIpCap;
    VOS_UINT32                          ulRslt;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    usDataLen = sizeof(LNAS_LMM_NV_NAS_LOCALIP_CAP_STRU);

    pData                               = (VOS_VOID *)&(stNasLocalIpCap);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_PS_LOCALIP_CAP,
                                        pData,
                                        &usDataLen);

    if(ulRslt == VOS_OK)
    {
        if (VOS_TRUE == stNasLocalIpCap.bitOpLocalIpCap)
        {
            NAS_ESM_GetLocalIpSupFlag() = stNasLocalIpCap.ulLocalIpCap;
        }
    }
    else
    {
        NAS_ESM_GetLocalIpSupFlag() = NAS_ESM_FUN_CTRL_OFF;
    }
}



VOS_UINT32 NAS_ESM_SaveAppNdisConnInfo(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                          ulRslt;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU          *pAppMsg;

    pAppMsg = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG1("NAS_ESM_SaveAppNdisConnInfo is entered.", pAppMsg->ulCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, LNAS_ENTRY, pAppMsg->ulCid);

    /*取出消息中包含CID参数*/
    ulCidRecv=pAppMsg->ulCid;

    /*从消息中取出本次过程的ulOPID参数*/
    ulOpId=pAppMsg->ulOpId;

    /*从消息中取出MID参数*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*封装结构体pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId= ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpApn)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetApn(pAppMsg->ulCid,
                                                    APP_ESM_PARA_SETTING,
                                                    pAppMsg->stApnInfo);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_SaveAppNdisConnInfo: APN ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, ESM_APN_ERROR, ulRslt);

            /*封装结构体pstEsmAppCnfMsg*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = ulRslt;

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpGwAuth)
    {
        ulRslt = NAS_ESM_AppNdisConnSetGwAuthInfo(pRcvMsg);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: GwAuth ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, LNAS_ERROR, ulRslt);

            /*封装结构体pstEsmAppCnfMsg*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = ulRslt;

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpPdnType)
    {
        ulRslt = NAS_ESM_AppCgdconntOrNDISconnSetPdnType(pAppMsg->ulCid,
                                                        APP_ESM_PARA_SETTING,
                                                        pAppMsg->enPdnType,
                                                        pAppMsg->bitOpIpv4AddrAlloc,
                                                        pAppMsg->enIpv4AddrAlloc);

        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: Pdn ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, ESM_PDN_TYPE_ERROR, ulRslt);
            /*封装结构体pstEsmAppCnfMsg*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = ulRslt;

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

