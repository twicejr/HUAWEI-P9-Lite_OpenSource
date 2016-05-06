


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmTauInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACHAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACHAPPMSGPROC_C
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
 Function Name   :  NAS_EMM_AppAttachReqMsgChk
 Description     : 检查APP发送消息内容是否正确
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  MOD:检查消息内容错误，回复APP_ATTACH_CNF
*****************************************************************************/
VOS_UINT32  NAS_EMM_AppAttachReqMsgChk(const MMC_LMM_ATTACH_REQ_STRU *pMsgpMsg)
{
    /*消息内容检查*/
    if ((MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pMsgpMsg->ulAttachType) ||
        (MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pMsgpMsg->ulAttachType) ||
        (MMC_LMM_ATT_REQ_TYPE_CS_PS == pMsgpMsg->ulAttachType))
    {
        return  NAS_EMM_PARA_VALID;
    }
    else
    {
        NAS_EMM_SaveAppMsgPara(pMsgpMsg->ulMsgId, pMsgpMsg->ulOpId);
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_EMM_PARA_INVALID;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq
 Description     : 主状态DEREG+子状态NORMAL_SERVICE下收到应用层的ATTACH
                   REQUEST消息

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru)
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq: NAS_EMM_CN_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*保存触发ATTACH的原因*/
    NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_APP;

    /* 用户请求ATTACH类型为IMSI，UE模式为PS，则直接回复FAILURE ,
       用户请求ATTACH类型为IMSI，UE模式为CS_PS，此时注册状态为NULL，则直接回复FAILURE ,
       综上，dereg.normalserive状态下CS的ATTACH都直接回复失败 */
    if (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
    {

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    }

    /*用户请求ATTACH类型为PS或者CS_PS，直接发起ATTACH，填充ATTACH消息时判断ATTACH类型*/
    else
    {

        /*向ESM发送ID_EMM_ESM_PDN_CON_IND消息*/
        NAS_EMM_EsmSendPdnConnInd(           NAS_EMM_DEFAULT_CID);

        /*启动定时器TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_PDN_RSP);

        /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_PDN_RSP*/
        NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                            EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                            TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    }


   return   NAS_LMM_MSG_HANDLED;

}




/*****************************************************************************
 Function Name   : NAS_EMM_EsmSendPdnConnInd
 Description     : 请求ESM的PDN CONNECTIVITY REQUEST消息

 Input           :
 Output          : None
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID    NAS_EMM_EsmSendPdnConnInd(VOS_UINT32 ulCid)
{
    EMM_ESM_PDN_CON_IND_STRU             *pEmmEsmPdnIndMsg;


    /*申请消息内存*/
    pEmmEsmPdnIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_IND_STRU));

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmPdnIndMsg)
    {
        return;
    }

    /*构造ID_EMM_ESM_PDN_CON_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(      pEmmEsmPdnIndMsg,
                                        (sizeof(EMM_ESM_PDN_CON_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pEmmEsmPdnIndMsg->ulMsgId            = ID_EMM_ESM_PDN_CON_IND;

    /*填充消息内容*/
    pEmmEsmPdnIndMsg->ulCId              = ulCid;

    if(MMC_LMM_ATT_REASON_HANDOVER == NAS_LMM_GetEmmInfoMmcAttachReason())
    {
        pEmmEsmPdnIndMsg->enPdnReqType = EMM_ESM_PDN_CON_REQ_TYPE_HANDOVER;
    }
    else
    {
        pEmmEsmPdnIndMsg->enPdnReqType = EMM_ESM_PDN_CON_REQ_TYPE_INITIAL;
    }
    /* 大数据: 记录ATTACH流程Start时间 */
    NAS_LMM_SaveAttachStartTimeStamp();
    /*向ESM发送ID_EMM_ESM_PDN_CON_IND消息*/
    NAS_LMM_SEND_MSG(                   pEmmEsmPdnIndMsg);

    return;


}


/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq
 Description     : 主状态DEREG+子状态DEREG_PLMN_SEARCH下收到APP发送的
                   ATTACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  MOD:修改APP_ATTACH_CNF结果值
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)

{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;
    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;

    (VOS_VOID)ulMsgId;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_PLMN_SEARCH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }


    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*向MMC发送ATTACH失败*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*返回NAS_LMM_MSG_HANDLED，不返回DISCARD，避免MMC再处理一遍*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq
 Description     : 主状态DEREG+子状态DEREG_ATTEMPT_TO_ATTACH下收到APP发送的
                   ATTACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  MOD:修改APP_ATTACH_CNF结果值
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)

{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;
    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;

    (VOS_VOID)ulMsgId;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*向MMC发送ATTACH失败*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /* ATTEMPINT TO ATTACH状态下，等3411超时后，会自动发起ATTACH，不必由APP
    的ATTACH REQ触发ATTACH流程；
    返回NAS_LMM_MSG_HANDLED，不返回DISCARD，避免MMC再处理一遍*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq
 Description     : 主状态DEREG+子状态DEREG_LIMITED_SERVICE下收到APP发送的
                   ATTACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                     VOS_VOID   *pMsgStru)

{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_LIMITED_SERVICE))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*向MMC发送ATTACH失败*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*返回NAS_LMM_MSG_HANDLED，不返回DISCARD，避免MMC再处理一遍*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq
 Description     : 主状态DEREG+子状态DEREG_NO_IMSI下收到APP发送的
                   ATTACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_IMSI))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);

        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*向MMC发送ATTACH失败*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*返回NAS_LMM_MSG_HANDLED，不返回DISCARD，避免MMC再处理一遍*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq
 Description     : 主状态DEREG+子状态DEREG_NO_CELL_AVAILABLE下收到APP发送的
                   ATTACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*向MMC发送ATTACH失败*/
    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    /*返回NAS_LMM_MSG_HANDLED，不返回DISCARD，避免MMC再处理一遍*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;



}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq
 Description     : 主状态DEREG+子状态DEREG_ATTACH_NEEDED下收到APP发送的
                   ATTACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /*向MMC发送ATTACH失败*/
    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ACCESS_BAR);

    /* ATTACH NEEDED 状态下，等3402超时后，会自动发起ATTACH，不必由APP
    的ATTACH REQ触发ATTACH流程；
    返回NAS_LMM_MSG_HANDLED，不返回DISCARD，避免MMC再处理一遍*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq: handled and discard out of NAS.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq_ENUM,LNAS_RETRUN_RST);
    return  NAS_LMM_MSG_HANDLED;


  }


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_PDN_RSP下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-09  添加:保存APP参数
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /* 用户请求ATTACH类型为IMSI，UE模式为PS，则直接回复FAILURE ,
       用户请求ATTACH类型为IMSI，UE模式为CS_PS，此时注册状态为NULL，则直接回复FAILURE ,
       综上，reginit.waitEsmPdnRsp状态下CS的ATTACH都直接回复失败 */
    if(MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH失败*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*忽略此消息*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq IS IGNORE");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq_ENUM,LNAS_END);

    return  NAS_LMM_MSG_DISCARD;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  MOD:保存APP参数
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *) pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 用户请求ATTACH类型为IMSI，UE模式为PS，则直接回复FAILURE ,
       用户请求ATTACH类型为IMSI，UE模式为CS_PS，此时注册状态为NULL，则直接回复FAILURE ,
       综上，RegInitSsWtCnAttCnf状态下CS的ATTACH都直接回复失败 */
    if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
      &&(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode()))
    {
        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

        /*向MMC发送ATTACH失败*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 低优先级缓存 */
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq  IS NAS_LMM_STORE_LOW_PRIO_MSG");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq_ENUM,LNAS_END);
    return  NAS_LMM_STORE_LOW_PRIO_MSG;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_BEARER_CNF下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /* 用户请求ATTACH类型为IMSI，UE模式为PS，则直接回复FAILURE ,
       综上，reginit.WtEsmBearerCnf状态下CS的ATTACH都直接回复失败 */
    if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
      &&(NAS_EMM_NO== NAS_EMM_IsCsPsUeMode()))
    {
        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

        /*向MMC发送ATTACH失败*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq IS NAS_LMM_STORE_LOW_PRIO_MSG");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq_ENUM,LNAS_END);
    return NAS_LMM_STORE_LOW_PRIO_MSG;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_BEARER_CNF下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_RRC_DATA_CNF))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    return NAS_LMM_STORE_LOW_PRIO_MSG;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq
 Description     : 主状态REG+子状态REG_NORMAL_SERVICE下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*UE请求类型为CS或者CS_PS,操作模式是PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }
    /*UE请求类型为CS或者CS_PS,操作模式是CS_PS,注册域为CS_PS*/

    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*注册域为PS*/
    else if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        if( (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
            ||(NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag()))
        {
            NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
            return NAS_LMM_MSG_HANDLED;
        }
        /*联合TAU*/
        NAS_EMM_SendIntraTauReq(ID_APP_MM_MSG_TYPE_BUTT,NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH);
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {
        return NAS_LMM_MSG_HANDLED;
    }

}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq
 Description     : 状态REG+REG_ATTEMPTING_TO_UPDATE_MM收到MMC的MMC_LMM_ATTACH_REQ
                    消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);


    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq
 Description     : 主状态REG+子状态REG_ATTEMPTING_TO_UPDATE下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
            &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {

        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq
 Description     : 主状态REG+子状态REG_LIMITED_SERVICE下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_LIMITED_SERVICE))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);


    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq
 Description     : 主状态REG+子状态REG_PLMN_SERVICE下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_PLMN_SEARCH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq
 Description     : 主状态REG+子状态REG_WAIT_ACCESS_GRANT_IND下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*操作模式是PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

    /*注册域为CS_PS*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*注册域为PS*/
    if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        if( (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
            ||(NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag()))
        {
            NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
            return NAS_LMM_MSG_HANDLED;
        }
        /*联合TAU*/
        /*信令被BAR不能发起，其它可以发起,内部消息处理中会判断，此处不再判断*/
        NAS_EMM_SendIntraTauReq(ID_APP_MM_MSG_TYPE_BUTT,NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH);
        return NAS_LMM_MSG_HANDLED;
    }

    return  NAS_LMM_MSG_HANDLED;
}
/*lint +e960*/

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq
 Description     : 主状态REG+子状态REG_NO_CELL_AVAILABLE下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU             *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NO_CELL_AVAILABLE))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq: APP_MM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {

        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }
    if ( (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())
        &&(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq
 Description     : 主状态REG+子状态ImsiDetachWtCnDetCnf下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.zhangcaixia 00179470   2011-11-24  经分析，该状态下AT通道阻塞，不可能收到用户的ATTACH请求消息，
                                         该状态下收到ID_MMC_LMM_ATTACH_REQ,加打印，统计出现概率。
                                         如果后续该状态下收到ID_MMC_LMM_ATTACH_REQ增加处理
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* 打印,*/
    NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq: Receive Message APP ATTACH.");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_RCV_MSG);


    return NAS_LMM_STORE_LOW_PRIO_MSG;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq
 Description     : 主状态DEREG_INIT+子状态DETACH_WAIT_CN_DETACH_CNF下收到APP发送
                   的ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-16  添加回复APP FAIL
    3.zhangcaixia 00179470   2011-11-24  经分析，该状态下AT通道阻塞，不可能收到用户的ATTACH请求消息，
                                         该状态下收到ID_MMC_LMM_ATTACH_REQ,加打印，统计出现概率。
                                         如果后续该状态下收到ID_MMC_LMM_ATTACH_REQ增加处理
    4.niuxiufan 00181501     2012-12-03  为解决SYSCFG过程中设置为L单模后,本地detach之后不发起attach的问题
                                         以及Detach过程中网侧无回复导致MMA侧Syscfg的20s等待detach结果定时器超时
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)(ulMsgId);


    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *) pMsgStru;

    /* 打印,*/
    NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq: Receive Message APP ATTACH.");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_RCV_MSG);

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq: NAS_EMM_CN_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*停止定时器T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /*给MMC回复Detach Cnf */
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq: No USIM");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq_ENUM,LNAS_EMM_NO_USIM);

        NAS_EMM_ProcLocalNoUsim();
    }
    else
    {
        /* 本地DETACH释放资源:动态内存、赋初值 */
        NAS_LMM_DeregReleaseResource();

        NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    }
    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);


    /*重新保存用户发起ATTACH的请求类型*/
    NAS_EMM_GLO_SetAttReqType(pRcvEmmMsg->ulAttachType);

    /*CS域的attach请求直接返回失败 */
    if (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pRcvEmmMsg->ulAttachType)
    {

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);

    }

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);


    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq
 Description     : 主状态TAU_INIT+子状态TAU_WAIT_CN_TAU_CNF下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }


    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*操作模式是PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }
    /*操作模式是CS_PS*/
    /*注册域为CS_PS*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*注册域为PS*/
    if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        return NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq
 Description     : 主状态SER_INIT+子状态SER_WAIT_CN_SER_CNF下收到APP发送的
                   ATTACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru )
{
    MMC_LMM_ATTACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_ATTACH_REQ_STRU *)pMsgStru;


    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*打印出错信息*/
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq: STATE ERR!");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppAttachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq: MMC_LMM_ATTACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pRcvEmmMsg->ulAttachType)
    {
        /*向MMC发送ATTACH成功*/
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /*请求类型是IMSI或者CS_ps,操作模式是PS*/
    if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

    /*请求类型是IMSI或者CS_ps操作模式是CS_PS,注册域为CS_PS*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }
    /*请求类型是IMSI或者CS_ps操作模式是CS_PS,注册域为PS*/
    if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        /* 发起TAU，打断SERVICE */
        /*停止T3417定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

        /*Inform RABM that SER fail*/
        NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

        /*结束SER流程*/
        /* NAS_EMM_SER_AbnormalOver();*/

        /*设置流程冲突标志位*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_IMSI_ATTACH);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /*启动TAU Procedure*/
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);

        return NAS_LMM_MSG_HANDLED;
    }

    return  NAS_LMM_MSG_HANDLED;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

