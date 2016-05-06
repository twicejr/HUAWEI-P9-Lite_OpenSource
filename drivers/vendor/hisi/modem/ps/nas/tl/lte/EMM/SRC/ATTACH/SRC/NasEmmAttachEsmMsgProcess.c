




/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasMmlLib.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACHESMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACHESMMSGPROC_C
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
/*降低圈复杂度*/
EMM_ESM_DATA_CNF_MAP_STRU  g_astEmmEsmDataCnfTbl[] =
{
    {LRRC_LMM_SEND_RSLT_SUCCESS,                EMM_ESM_SEND_RSLT_SUCCESS},
    {LRRC_LMM_SEND_RSLT_FAILURE_HO,             EMM_ESM_SEND_RSLT_FAILURE_HO},
    {LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL,       EMM_ESM_SEND_RSLT_FAILURE_CONN_REL},
    {LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN,  EMM_ESM_SEND_RSLT_FAILURE_CTRL_NOT_CONN},
    {LRRC_LMM_SEND_RSLT_FAILURE_TXN,            EMM_ESM_SEND_RSLT_FAILURE_TXN},
    {LRRC_LMM_SEND_RSLT_FAILURE_RLF,            EMM_ESM_SEND_RSLT_FAILURE_RLF},
    {LRRC_LMM_SEND_RSLT_NO_RF,                  EMM_ESM_SEND_RSLT_NORF}
};
VOS_UINT32        g_ulEmmEsmDataCnfTblLen = sizeof(g_astEmmEsmDataCnfTbl)
                                               / sizeof(EMM_ESM_DATA_CNF_MAP_STRU);

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
Function Name   : NAS_EMM_EsmPdnRspMsgChk
Description     : 检查ID_EMM_ESM_PDN_CON_RSP消息内容是否正确
Input           :
Output          :
Return          :

History         :
1.leili 00132387         2008-09-09  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_EsmPdnRspMsgChk( const EMM_ESM_PDN_CON_RSP_STRU *pMsgpMsg)
{
    /*消息内容检查*/
    if ((EMM_ESM_PDN_CON_RSLT_SUCC == pMsgpMsg->ulRst) ||
         (EMM_ESM_PDN_CON_RSLT_FAIL == pMsgpMsg->ulRst))
    {
        return  NAS_EMM_PARA_VALID;

    }
    else
    {
        return  NAS_EMM_PARA_INVALID;

    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_AttRsltCommProc
 Description     : 发送ATTACH结果消息的公共处理
 Input           : None
 Output          : None
 Return          : VOS_VOID*

 History         :
    1.leili 00132387      2011-4-25  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID *NAS_EMM_AttRsltCommProc(VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pstMmcAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AttRsltCommProc:构造LMM_MMC_ATTACH_IND!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AttRsltCommProc_ENUM,LNAS_BEGIN);

    /*申请消息内存*/
    pstMmcAttMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ATTACH_IND_STRU));

    /*判断申请结果，若失败打印错误并退出*/
    if ((NAS_EMM_NULL_PTR == pstMmcAttMsg))
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AttRsltCommProc: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttRsltCommProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_NULL_PTR;

    }

    NAS_LMM_MEM_SET_S(  pstMmcAttMsg,
                        sizeof(LMM_MMC_ATTACH_IND_STRU),
                        0,
                        sizeof(LMM_MMC_ATTACH_IND_STRU));

    /*构造LMM_MMC_ATTACH_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pstMmcAttMsg,
                                        sizeof(LMM_MMC_ATTACH_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /*填充消息ID*/

    pstMmcAttMsg->ulMsgId       = ID_LMM_MMC_ATTACH_IND;

    /*填充消息内容----OPID*/
    pstMmcAttMsg->ulOpId        = NAS_EMM_OPID_TYPE_ATTACH_IND;

    /* 上报ATTACH IND时取当前注册状态全局变量上报给MMC，然后清除 */
    pstMmcAttMsg->enClAttRegStatus = NAS_EMM_GLO_AD_GetAttClRegStatus();

    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND);

    return pstMmcAttMsg;

}
/* 删除无人调用函数NAS_EMM_AppSendAttInd */

/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendAttCnf
 Description     : 向MMC发送LMM_MMC_ATTACH_CNF
 Input           :
 Return          : VOS_VOID

 History         :
    1.z00179470         2012-01-13  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_MmcSendAttCnf
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32                ulAttRslt
)
{
    LMM_MMC_ATTACH_CNF_STRU            *pstAttCnf;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MmcSendAttCnf:回复LMM_MMC_ATTACH_CNF!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendAttCnf_ENUM,LNAS_BEGIN);

    /*申请消息内存*/
    pstAttCnf = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*判断申请结果，若失败打印错误并退出*/
    if ((NAS_EMM_NULL_PTR == pstAttCnf))
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MmcSendAttCnf: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendAttCnf_ENUM,LNAS_NULL_PTR);
        return ;

    }

    NAS_LMM_MEM_SET_S(  pstAttCnf,
                        sizeof(LMM_MMC_ATTACH_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*消息头*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pstAttCnf,
                                        sizeof(LMM_MMC_ATTACH_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* 填充消息 */

    pstAttCnf->ulMsgId       = ID_LMM_MMC_ATTACH_CNF;

    /*填充消息内容----OPID*/
    pstAttCnf->ulOpId        = NAS_EMM_GetAppMsgOpId();

    pstAttCnf->ulAttachRslt  = ulAttRslt;
    pstAttCnf->ulReqType     = NAS_EMM_GLO_GetAttReqType();

    NAS_LMM_SendLmmMmcMsg(pstAttCnf);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /*清空APP_ATTACH_REQ消息*/
    NAS_EMM_ClearAppMsgPara();
}
/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttSucc
 Description     : 向MMC发送ATTACH结果成功消息
 Input           : pstRcvMsg-----网侧发送的ATTACH ACCEPT消息
 Return          : VOS_VOID

 History         :
    1.leili 00132387         2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttSucc( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pstMmcAttMsg = NAS_EMM_NULL_PTR;

     NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:ENTER!");
     TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_SUCCESS);
    }

    /* 构造 LMM_MMC_ATTACH_IND */
    pstMmcAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstMmcAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttSucc_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    pstMmcAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_SUCCESS;

    /*填充消息内容----ATTACH请求类型*/
    pstMmcAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*填充消息内容----网侧结果类型*/
    pstMmcAttMsg->bitOpCnRslt       = NAS_EMM_BIT_SLCT;

    if (EMM_ATTACH_RSLT_EPS_ONLY == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pstMmcAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_EPS_ONLY;
    }
    else if (EMM_ATTACH_RSLT_COMBINED_ATTACH == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pstMmcAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttSucc:CN RSLT is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttSucc_ENUM,LNAS_ACT_RESULT);
    }

    /*填充消息内容----EPLMN*/
    pstMmcAttMsg->bitOpEplmn    = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttSucc:EPLMN NUM =",
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_PLMN_NUMBER,
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);

        NAS_LMM_MEM_CPY_S(  &pstMmcAttMsg->stEplmnList,
                            sizeof(MMC_LMM_EPLMN_STRU),
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                            sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*填充消息内容----LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetLai())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:LAI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_LAI_NUMBER);
        pstMmcAttMsg->bitOpLai      = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  &pstMmcAttMsg->stLai,
                            sizeof(MMC_LMM_LAI_STRU),
                            NAS_EMM_GLO_AD_GetLaiAddr(),
                            sizeof(MMC_LMM_LAI_STRU));
    }
    /*填充消息内容----TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetMsId())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:TMSI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_TMSI_NUMBER);
        pstMmcAttMsg->bitOpMsIdentity     = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  pstMmcAttMsg->stMsIdentity.aucMsIdentity,
                            NAS_MAX_SIZE_MS_IDENTITY,
                            NAS_EMM_GLO_AD_GetMsIdAddr(),
                            NAS_MAX_SIZE_MS_IDENTITY);

    }
    /*填充消息内容----EMM CAUSE*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetEmmCau())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:EMM CAUSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_CAUSE_NUMBER);
        pstMmcAttMsg->bitOpCnCause      = NAS_EMM_BIT_SLCT;
        pstMmcAttMsg->ucCnCause         = NAS_EMM_GLO_AD_GetEmmCau();
    }

    /*
    if ((NAS_LMM_CAUSE_MSC_UNREACHABLE == NAS_EMM_GLO_AD_GetEmmCau())
        || (NAS_LMM_CAUSE_NETWORK_FAILURE == NAS_EMM_GLO_AD_GetEmmCau())
        || (NAS_LMM_CAUSE_PROCEDURE_CONGESTION == NAS_EMM_GLO_AD_GetEmmCau()))
    */
    if (0 != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:tau attempt couter");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttSucc_ENUM,LNAS_EMM_ATTEMPT_COUNTER);
        pstMmcAttMsg->bitOpAtmpCnt      = NAS_EMM_BIT_SLCT;
        pstMmcAttMsg->ulAttemptCount    = NAS_EMM_TAU_GetEmmTAUAttemptCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pstMmcAttMsg);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttRejEpsOnly
 Description     : 收到ATTACH ACCEPT消息，EPS ONLY，且携带原因不为协议24301 5.5.1.3.4.3章节规定时，
                   向MMC发送ATTACH的结果值为ATTACH REJ，携带ATTACH ATTEMPT COUTER,
                   如果ATTACH ACCEPT中携带原因值，则携带原因值，如果ATTACH ACCEPT
                   携带EPLMN LIST,TMSI或者LAI，则携带EPLMN LIST,TMSI或者LAI给MMC

 Input           :

 Return          : None

 History         :
    1.lihong         2011-08-09  Draft Enact
    2.sunjitan 00193151  2012-05-31 Modify  只有#2#16#17#18#22时填原因值，其它不填
*****************************************************************************/
VOS_VOID NAS_EMM_AppSendAttRejEpsOnly( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_CN_REJ);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRejEpsOnly:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    pEmmAppAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_CN_REJ;

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*填充消息内容----网侧结果类型*/
    pEmmAppAttMsg->bitOpCnRslt  = NAS_EMM_BIT_SLCT;
    pEmmAppAttMsg->ulCnRslt     = MMC_LMM_ATT_CN_RSLT_EPS_ONLY;

    /* 只有#2#16#17#18#22时填原因值，其它原因值或者无原因值的情况不填 */
    pEmmAppAttMsg->bitOpCnCause      = NAS_EMM_BIT_NO_SLCT;
    pEmmAppAttMsg->ucCnCause         = NAS_EMM_CAUSE_BUTT;

    /*填充消息内容----EPLMN*/
    pEmmAppAttMsg->bitOpEplmn    = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttRejEpsOnly:EPLMN NUM =",
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_EMM_PLMN_NUMBER,
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);

        NAS_LMM_MEM_CPY_S(  &pEmmAppAttMsg->stEplmnList,
                            sizeof(MMC_LMM_EPLMN_STRU),
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                            sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*填充消息内容----LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetLai())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRejEpsOnly:LAI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_EMM_LAI_NUMBER);
        pEmmAppAttMsg->bitOpLai      = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  &pEmmAppAttMsg->stLai,
                            sizeof(MMC_LMM_LAI_STRU),
                            NAS_EMM_GLO_AD_GetLaiAddr(),
                            sizeof(MMC_LMM_LAI_STRU));
    }

    /*填充消息内容----TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetMsId())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRejEpsOnly:TMSI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRejEpsOnly_ENUM,LNAS_EMM_TMSI_NUMBER);
        pEmmAppAttMsg->bitOpMsIdentity     = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  pEmmAppAttMsg->stMsIdentity.aucMsIdentity,
                            NAS_MAX_SIZE_MS_IDENTITY,
                            NAS_EMM_GLO_AD_GetMsIdAddr(),
                            NAS_MAX_SIZE_MS_IDENTITY);

    }

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttRej
 Description     : 向APP发送ATTACH结果消息

 Input           :

 Return          : None

 History         :
    1.leili 00132387         2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttRej( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRej:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRej_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_CN_REJ);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRej:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRej_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    pEmmAppAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_CN_REJ;

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*填充消息内容----网侧拒绝原因*/
    pEmmAppAttMsg->bitOpCnCause      = NAS_EMM_BIT_SLCT;
    pEmmAppAttMsg->ucCnCause         = NAS_EMM_GLO_AD_GetAttRejCau();

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttTimerExp
 Description     : 向APP发送ATTACH结果消息

 Input           :

 Return          : None

 History         :
    1.leili 00132387         2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttTimerExp(VOS_VOID)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttTimerExp:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttTimerExp_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_TIMER_EXP);
    }


    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttTimerExp:MSG MALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttTimerExp_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    pEmmAppAttMsg->ulAttachRslt      = MMC_LMM_ATT_RSLT_TIMER_EXP;

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /*填充消息内容----ATTACH尝试次数*/
    pEmmAppAttMsg->bitOpAtmpCnt      = NAS_EMM_BIT_SLCT;
    pEmmAppAttMsg->ulAttemptCount    = NAS_EMM_GLO_AD_GetAttAtmpCnt();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttFailWithPara
 Description     : 底层失败或连接释放时，发送给MMC的消息结果为失败，携带尝试次数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-4-25  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_AppSendAttFailWithPara( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithPara:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithPara_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttFailWithPara:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttFailWithPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    pEmmAppAttMsg->ulAttachRslt         = MMC_LMM_ATT_RSLT_FAILURE;

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttOtherType
 Description     : 向APP发送ATTACH结果消息

 Input           :

 Return          : None

 History         :
    1.leili 00132387         2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttOtherType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttOtherType:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(ulAttRslt);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttOtherType:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    if ((MMC_LMM_ATT_RSLT_ACCESS_BAR == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_AUTH_REJ == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_ESM_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_T3402_RUNNING == ulAttRslt))
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttOtherType:ulAttRslt =",
                                ulAttRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_ACT_RESULT,
                                ulAttRslt);

        pEmmAppAttMsg->ulAttachRslt  = ulAttRslt;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttOtherType:ulAttRslt is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttOtherType_ENUM,LNAS_ERROR);
    }

    /*填充消息内容----ATTACH请求类型*/
    /*NAS_EMM_SetAttType();*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttRstDefaultReqType
 Description     : 向APP发送ATTACH结果消息

 Input           :

 Return          : None

 History         :
    1.leili 00132387         2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttRstDefaultReqType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRstDefaultReqType:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(ulAttRslt);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRstDefaultReqType:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息内容----ATTACH结果*/
    if ((MMC_LMM_ATT_RSLT_ACCESS_BAR == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_AUTH_REJ == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_SUCCESS == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_ESM_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == ulAttRslt) ||
        (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == ulAttRslt)||
        (MMC_LMM_ATT_RSLT_T3402_RUNNING == ulAttRslt))
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttRstDefaultReqType:ulAttRslt =",
                                ulAttRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_ACT_RESULT,
                                ulAttRslt);

        pEmmAppAttMsg->ulAttachRslt  = ulAttRslt;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttOtherType:ulAttRslt is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttRstDefaultReqType_ENUM,LNAS_ERROR);
    }

    /*填充消息内容----ATTACH请求类型*/
    NAS_EMM_SetAttType();

    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);

    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttRstInTau
 Description     : CS或者CS_PS的ATTACH引起TAU导致TAU后向APP发送ATTACH结果消息
                    ATTACH引起联合TAU的，在ATTACH之前上报了TAU结果并进入了状态机，
                    只需要上报一条

 Input           :

 Return          : None

 History         :
    1.z00179470         2011-11-14  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst)
{
    LMM_MMC_ATTACH_CNF_STRU             *pEmmAppAttMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRstInTau:回复LMM_MMC_ATTACH_CNF!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRstInTau_ENUM,LNAS_BEGIN);

    /*申请消息内存*/
    pEmmAppAttMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*判断申请结果，若失败打印错误并退出*/
    if ((NAS_EMM_NULL_PTR == pEmmAppAttMsg))
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRstInTau: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRstInTau_ENUM,LNAS_NULL_PTR);
        return ;

    }

    NAS_LMM_MEM_SET_S(  pEmmAppAttMsg,
                        sizeof(LMM_MMC_ATTACH_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_ATTACH_CNF_STRU));

    /*消息头*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pEmmAppAttMsg,
                                        sizeof(LMM_MMC_ATTACH_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* 填充消息 */

    pEmmAppAttMsg->ulMsgId              = ID_LMM_MMC_ATTACH_CNF;

    /*填充消息内容----OPID*/
    pEmmAppAttMsg->ulOpId               = NAS_EMM_GetAppMsgOpId();

    /*填充消息内容----ATTACH结果*/
    pEmmAppAttMsg->ulAttachRslt         = ulAttRst;

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType            = NAS_EMM_GLO_GetAttReqType();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_CNF，不报LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /*清空APP_ATTACH_REQ消息*/
    NAS_EMM_ClearAppMsgPara();
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttFailWithPara
 Description     : 底层失败或连接释放时，发送给MMC的消息结果为失败，携带尝试次数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-4-25  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_AppSendAttFailWithAllPara( VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;


    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_ENTRY);

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
    }

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();

    /*判断申请结果，若失败打印错误并退出*/
    if ((NAS_EMM_NULL_PTR == pEmmAppAttMsg))
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttFailWithAllPara: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_NULL_PTR);
        return;

    }


    /*填充消息内容----ATTACH结果*/
    pEmmAppAttMsg->ulAttachRslt         = MMC_LMM_ATT_RSLT_FAILURE;

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    if (NAS_EMM_NULL != NAS_EMM_GLO_AD_GetAttAtmpCnt())
    {
       pEmmAppAttMsg->bitOpAtmpCnt   = NAS_EMM_BIT_SLCT;
       pEmmAppAttMsg->ulAttemptCount = NAS_EMM_GLO_AD_GetAttAtmpCnt();
    }

    /*填充消息内容----网侧结果类型*/
    pEmmAppAttMsg->bitOpCnRslt       = NAS_EMM_BIT_SLCT;

    /* zhangcaixia for syscfg_attach begin */
    if (EMM_ATTACH_RSLT_EPS_ONLY == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pEmmAppAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_EPS_ONLY;
    }
    else if (EMM_ATTACH_RSLT_COMBINED_ATTACH == NAS_EMM_GLO_AD_GetAttRslt())
    {
        pEmmAppAttMsg->ulCnRslt      = MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI;
    }

    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttFailWithAllPara:CN RSLT is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_ERROR);
    }

    /*填充消息内容----EPLMN*/
    pEmmAppAttMsg->bitOpEplmn    = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttFailWithAllPara:EPLMN NUM =",
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_EMM_PLMN_NUMBER,
                                NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);

        NAS_LMM_MEM_CPY_S(  &pEmmAppAttMsg->stEplmnList,
                            sizeof(MMC_LMM_EPLMN_STRU),
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                            sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*填充消息内容----LAI*/
    /* zhangcaixia for syscfg_attach begin */
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetLai())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:LAI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_EMM_LAI_NUMBER);
        pEmmAppAttMsg->bitOpLai      = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  &pEmmAppAttMsg->stLai,
                            sizeof(MMC_LMM_LAI_STRU),
                            NAS_EMM_GLO_AD_GetLaiAddr(),
                            sizeof(MMC_LMM_LAI_STRU));
    }

    /*填充消息内容----TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetMsId())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:TMSI");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_EMM_TMSI_NUMBER);
        pEmmAppAttMsg->bitOpMsIdentity     = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  pEmmAppAttMsg->stMsIdentity.aucMsIdentity,
                            NAS_MAX_SIZE_MS_IDENTITY,
                            NAS_EMM_GLO_AD_GetMsIdAddr(),
                            NAS_MAX_SIZE_MS_IDENTITY);
    }

    /*填充消息内容----EMM CAUSE*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetEmmCau())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttFailWithAllPara:EMM CAUSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttFailWithAllPara_ENUM,LNAS_CAUSE_NUMBER);
        pEmmAppAttMsg->bitOpCnCause      = NAS_EMM_BIT_SLCT;
        pEmmAppAttMsg->ucCnCause         = NAS_EMM_GLO_AD_GetEmmCau();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AppSendAttPsNotAllow
 Description     : 向APP发送ATTACH结果消息
                   用户发起的PS的ATTACH不会走到此结果上报上来，故此需要上报一条

 Input           :

 Return          : None

 History         :
    1. z00179470         2011-12-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_AppSendAttPsNotAllow(  VOS_VOID )
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttPsNotAllow:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttPsNotAllow_ENUM,LNAS_ENTRY);

    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttPsNotAllow:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttPsNotAllow_ENUM,LNAS_NULL_PTR);
        return;
    }

    pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW;


    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = MMC_LMM_ATT_TYPE_BUTT;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /*清空MMC_LMM_ATTACH_REQ消息*/
    NAS_EMM_ClearAppMsgPara();
    return;
}

/* zhangcaixia for syscfg_attach end */

VOS_VOID  NAS_EMM_AppSendAttRsltForb
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo
)
{
    LMM_MMC_ATTACH_IND_STRU             *pEmmAppAttMsg;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttRsltForb:ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_ENTRY);


    pEmmAppAttMsg = NAS_EMM_AttRsltCommProc();
    if (NAS_EMM_NULL_PTR == pEmmAppAttMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttRsltForb:MSG ALLOC FAIL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AppSendAttRsltForb:ulForbInfo =",
                                  ulForbInfo);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_EMM_FORB_INFO,
                                  ulForbInfo);
    /*填充消息内容----ATTACH结果*/
    if (EMMC_EMM_FORBIDDEN_PLMN == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_PLMN;
    }
    else if (EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_RPOS == ulForbInfo)
    {
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS;
    }
    else if (EMMC_EMM_NO_FORBIDDEN == ulForbInfo)
    {
        /* 如果系统消息未被禁且调用此函数上报ATTACH结果，则一定是ANY CELL的情况 */
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FAILURE;
    }

    else
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_AppSendAttRsltForb:ulForbInfo is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_AppSendAttRsltForb_ENUM,LNAS_ERROR);
        pEmmAppAttMsg->ulAttachRslt  = MMC_LMM_ATT_RSLT_FAILURE;
    }

    /*填充消息内容----ATTACH请求类型*/
    pEmmAppAttMsg->ulReqType         = NAS_EMM_GLO_GetCnAttReqType();

    /* 向用户发LMM_MMC_ATACH_CNF */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_MmcSendAttCnf(pEmmAppAttMsg->ulAttachRslt);
    }

   #if (FEATURE_ON == FEATURE_DSDS)
   /*发送end notify消息给RRC，通知RRC释放资源*/
   NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
   #endif

    /*向MMC发送LMM_MMC_ATTACH_IND消息*/
    NAS_LMM_SendLmmMmcMsg(pEmmAppAttMsg);
    /* 大数据: 更新attach Other Fail次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_CountMrrcDataReqLen
 Description     : 计算NAS_EMM_MRRC_DATA_REQ消息长度

 Input           :
 Output          :
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CountMrrcDataReqLen(VOS_UINT32 ulNasCnMsgLen)
{
    VOS_UINT32                          ulMsgLen;
    ulMsgLen                            = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                          (ulNasCnMsgLen-NAS_EMM_LEN_VOS_MSG_HEADER))
                                          -NAS_EMM_4BYTES_LEN;

    return ulMsgLen;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CompCnAttachReqNasMsg
 Description     : 为规避PC-LINT检查数组越界的问题，独立出来一个打包CN消息的函数
 Input           : pulIndex     : 既作输入，也作输出
 Output          : pucAttReqCn
                   pulIndex     : 既作输入，也作输出
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-1  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnAttachReqNasMsg(  VOS_UINT8      *pucAttReqCn,
                                            VOS_UINT32     *pulIndex)
{
    VOS_UINT32                          ulIndex     = NAS_LMM_NULL;
    VOS_UINT32                          ulIeLength = NAS_LMM_NULL;

    VOS_UINT8                           ucKsi;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_CompCnAttachReqNasMsg: is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompCnAttachReqNasMsg_ENUM,LNAS_ENTRY);

    ulIndex                             = *pulIndex;

    /* 填充 Protocol Discriminator + Security header type */
    pucAttReqCn[ulIndex++]              = EMM_CN_MSG_PD_EMM;

    /* 填充 Attach request message identity   */
    pucAttReqCn[ulIndex++]              = NAS_EMM_CN_MT_ATTACH_REQ;

    /*填充Attach type + NKSI*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    NAS_EMM_SetAttType();
    NAS_EMM_ATTACH_LOG1_NORM("Attach Type: ", NAS_EMM_GLO_GetCnAttReqType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_CompCnAttachReqNasMsg_ENUM,LNAS_EMM_ATTACH_TYPE,
                                        NAS_EMM_GLO_GetCnAttReqType());
    pucAttReqCn[ulIndex++]              = ((VOS_UINT8)(NAS_EMM_GLO_GetCnAttReqType())|
                                           ((VOS_UINT8)(ucKsi << NAS_LMM_MOVEMENT_4_BITS)));

    /*填充EPS mobile identity*/
    NAS_EMM_EncodeEpsMobileId(          &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* 填充UE network capability 是必选IE, LV，3~14*/
    NAS_EMM_EncodeUeNetCapa(            &(pucAttReqCn[ulIndex]),
                                        NAS_LMM_IE_FORMAT_LV,
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充ESM message container*/
    NAS_EMM_EncodeEsmContainer(         &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Old P-TMSI signature*/
    NAS_EMM_EncodePtmsiSignature(       &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Additional GUTI*/
    NAS_EMM_EncodeAdditionalGuti(       &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Last visited registered TAI*/
    NAS_EMM_EncodeLRVTai(               &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充DRX parameter*/
    NAS_EMM_EncodeDrxPara(              &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;

    /*填充MS network capability*/
    NAS_EMM_EncodeMsNetworkCapability( &(pucAttReqCn[ulIndex]),
                                       &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;


    /*填充LAI*/
    NAS_EMM_EncodeLai(                  &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;


    /*填充TMSI STATUS*/
    NAS_EMM_EncodeTmsiStatus(           &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;

    /*填充Mobile station classmark 2*/
    NAS_EMM_EncodeMsClassMark2(         &(pucAttReqCn[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_ATTACH_REQ);
    ulIndex                             += ulIeLength;

    /*填充Mobile station classmark 3*/
    NAS_EMM_EncodeMsClassMark3(         &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Supported Codecs*/
    NAS_EMM_EncodeSupportedCodecs(      &(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Additional update type*/
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_EncodeAdditionUpdateType(   &(pucAttReqCn[ulIndex]),
                                            &ulIeLength);
        ulIndex                             += ulIeLength;
    }

    /*填充Voice domain preference and UE's usage setting*/
    NAS_EMM_EncodeVoiceDomainAndUsageSetting(&(pucAttReqCn[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    if (NAS_RELEASE_CTRL)
    {
        /* 填充Old GUTI type */
        NAS_EMM_EncodeGutiType(             &(pucAttReqCn[ulIndex]),
                                            &ulIeLength);
        ulIndex                             += ulIeLength;
    }

    if (NAS_RELEASE_R11)
    {

        /* 联合ATTACH，才编码该信元 */
        if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
        {
            /* 填充TMSI based NRI container */
            NAS_EMM_EncodeTmsiBasedNriContainer(    &(pucAttReqCn[ulIndex]),
                                                    &ulIeLength);
            ulIndex                             += ulIeLength;
        }
    }

    *pulIndex = ulIndex;

}



/*****************************************************************************
 Function Name   : NAS_EMM_CompCnAttachReq
 Description     : 填充空口消息ATTACH REQUEST的内容

 Input           :
 Output          :
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化
*****************************************************************************/

VOS_VOID    NAS_EMM_CompCnAttachReq(NAS_EMM_MRRC_DATA_REQ_STRU *pAttReqMsg)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pTempAttReqMsg  =pAttReqMsg;
    VOS_UINT32                          ulIndex         = 0;
    VOS_UINT32                          ulDataReqMsgLenNoHeader;

    if (NAS_EMM_NULL_PTR == pAttReqMsg)
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompCnAttachReq: Mem Alloc Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompCnAttachReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);

    /*编码ATTACH REQ空口消息*/
    NAS_EMM_CompCnAttachReqNasMsg(pTempAttReqMsg->stNasMsg.aucNasMsg, &ulIndex);

    /*内部消息长度计算*/
    ulDataReqMsgLenNoHeader             = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_CompCnAttachReq, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompCnAttachReq_ENUM,LNAS_ERROR);
        return ;
    }

    /*填充NAS消息长度*/
    pTempAttReqMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*填充消息头*/
    NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pTempAttReqMsg, ulDataReqMsgLenNoHeader);

    /*填充消息ID*/
    pTempAttReqMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    /*填充消息内容*/
    if ((EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
        || (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau()))
    {
        pTempAttReqMsg->enEstCaue           = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
        pTempAttReqMsg->enCallType          = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
    }
    else
    {
        pTempAttReqMsg->enEstCaue           = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
        pTempAttReqMsg->enCallType          = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    }
    pTempAttReqMsg->enEmmMsgType             = NAS_EMM_MSG_ATTACH_REQ;

    pTempAttReqMsg->enDataCnf               = LRRC_LMM_DATA_CNF_NEED;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeUeNetCapa
 Description     : 填写UE NETWORK CAPABILITY
 Input           : pIeStartAddr : 从这个地址开始填写IE码流
                   ucIeFormat   : 需要在码流中填写的IE的格式:
 Output          : pulIeLength  : 此地址中存放这个IE占用的字节数。
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-1-7  Draft Enact


*****************************************************************************/
VOS_VOID    NAS_EMM_EncodeUeNetCapa(    VOS_UINT8                  *pMsg,
                                        NAS_LMM_IE_FORMAT_ENUM_UINT8 ucIeFormat,
                                        VOS_UINT32                 *pulIeLength)
{
    VOS_UINT8                          *pMsgPreAddr;
    NAS_MM_UE_NET_CAP_STRU             *pstUeNetCap;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength) ||
       (NAS_LMM_IE_FORMAT_ERR(ucIeFormat)))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeUeNetCapa ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeUeNetCapa_ENUM,LNAS_NULL_PTR);
        /*
        NAS_EMM_ATTACH_LOG2_ERR(        "NAS_EMM_EncodeUeNetCapa ERR !! pMsg = , pIeLength = ",
                                        pMsg,
                                        pulIeLength);
        */
        return;
    }

    /* 把IE放入消息的地址赋值给临时变量 */
    pMsgPreAddr     = pMsg;

    /* 输出的参数IE长度初始化为0 */
    (*pulIeLength)  = NAS_EMM_NULL;

    /* 指向 UeNetCap*/
    pstUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();

    switch(ucIeFormat)
    {
        case    NAS_LMM_IE_FORMAT_LV:
                (*pMsgPreAddr) = pstUeNetCap->ucUeNetCapLen;
                pMsgPreAddr ++;         /* 地址加1, 指向V的首地址 */
                (*pulIeLength) += 1;    /* NAS_LMM_IE_FORMAT_LV中的L,长度增加 1*/

                /* 不BREAK，继续使用下面的CASE完成V的填充 */
                /*lint -fallthrough*/
                /*lint +fallthrough*/
        case    NAS_LMM_IE_FORMAT_V:
                /* coverity[ptr_arith] */

                NAS_LMM_MEM_CPY_S(  pMsgPreAddr,
                                    (pstUeNetCap->ucUeNetCapLen),
                                    (&(pstUeNetCap->ucUeNetCapLen) + 1),
                                    (pstUeNetCap->ucUeNetCapLen));

                (*pulIeLength) += (pstUeNetCap->ucUeNetCapLen);
                break;


        default :
                NAS_EMM_ATTACH_LOG1_ERR("NAS_EMM_EncodeUeNetCapa ERR!! ucIeFormat =",
                                        ucIeFormat);
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_EncodeUeNetCapa_ENUM,LNAS_IE_FORMAT,
                                        ucIeFormat);
                break;
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_CompMappedGuti
 Description     : 组装映射的GUTI
 Input           : None
 Output          : pMsg------组装的GUTI内容
                   pulIeLength ------GUTI长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_CompMappedGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_LMM_GUTI_STRU                    stMappedGuti;

    NAS_LMM_MEM_SET_S(&stMappedGuti, sizeof(NAS_LMM_GUTI_STRU), 0, sizeof(NAS_LMM_GUTI_STRU));

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_CompMappedGuti is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompMappedGuti_ENUM,LNAS_ENTRY);

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompMappedGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompMappedGuti_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*获取Mapped*/
    NAS_EMM_DeriveMappedGuti(&stMappedGuti);

    /*填充GUTI*/
    pucReqMsg[ulIndex++]                = NAS_EMM_AD_LEN_GUTI;
    pucReqMsg[ulIndex++]                = NAS_EMM_AD_ID_GUTI;

    NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                        NAS_EMM_AD_LEN_PLMN_ID,
                        stMappedGuti.stPlmnId.aucPlmnId,
                        NAS_EMM_AD_LEN_PLMN_ID);

    ulIndex                             += NAS_EMM_AD_LEN_PLMN_ID;

    pucReqMsg[ulIndex++]                = stMappedGuti.stMmeGroupId.ucGroupId;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMmeGroupId.ucGroupIdCnt;

    pucReqMsg[ulIndex++]                = stMappedGuti.stMmeCode.ucMmeCode;

    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsi;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsiCnt1;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsiCnt2;
    pucReqMsg[ulIndex++]                = stMappedGuti.stMTmsi.ucMTmsiCnt3;

    *pulIeLength                        = ulIndex;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_CompNativeGuti
 Description     : 组装NATIVE GUTI
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_CompNativeGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_CompNativeGuti is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompNativeGuti_ENUM,LNAS_ENTRY);

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompNativeGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompNativeGuti_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*填充GUTI*/
    /*============ GUTI ============ begin */
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetLen();
    pucReqMsg[ulIndex++]                = (NAS_EMM_GLO_AD_GetOeToi()|
                                             NAS_EMM_HIGH_HALF_BYTE_F);

    NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                        NAS_EMM_AD_LEN_PLMN_ID,
                        NAS_EMM_GLO_AD_GetGutiPlmn(),
                        NAS_EMM_AD_LEN_PLMN_ID);

    ulIndex                             += NAS_EMM_AD_LEN_PLMN_ID;
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetMmeGroupId();
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetMMeGroupIdCnt();
    pucReqMsg[ulIndex++]                = NAS_EMM_GLO_AD_GetMMeCode();

    NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                        sizeof(NAS_EMM_MTMSI_STRU),
                        NAS_EMM_GLO_AD_GetMTmsiAddr(),
                        sizeof(NAS_EMM_MTMSI_STRU));

    ulIndex                             += sizeof(NAS_EMM_MTMSI_STRU);

    *pulIeLength                        = ulIndex;

    return;
}


VOS_VOID  NAS_EMM_CompImsi
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompImsi: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompImsi_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*填充IMSI*/
    /*============ IMSI ============ begin */

    NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                        NAS_EMM_AD_LEN_CN_MSG_IMSI,
                        NAS_EMM_GLO_AD_GetImsi(),
                        NAS_EMM_AD_LEN_CN_MSG_IMSI);

    ulIndex                             += NAS_EMM_AD_LEN_CN_MSG_IMSI;
    *pulIeLength                        = ulIndex;
    /*============ IMSI ============ end */

    return;
}


VOS_VOID  NAS_EMM_CompImei
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*填充IMEI*/
    /*============ IMEI ============ begin */
    NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                        NAS_EMM_AD_LEN_CN_MSG_IMEI,
                        NAS_EMM_GLO_AD_GetImei(),
                        NAS_EMM_AD_LEN_CN_MSG_IMEI);

    /* GU NV中存储的IMEI与ATTACH REQ中EPS mobile identity中的结构有所不同，
       NV IMEI中的type of identity为'010'，而ATTACH REQ中携带的IMEI中的
       type of identity为'011' */
    pucReqMsg[1]                        &= (~NAS_EMM_LOW_3_BITS_F);
    pucReqMsg[1]                        |= 0x03;

    ulIndex                             += NAS_EMM_AD_LEN_CN_MSG_IMEI;
    *pulIeLength                        = ulIndex;
    /*============ IMEI ============ end */

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId
 Description     : 多模且TIN值为P-TMSI时，EPS mobile identity IE编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.lihong 00150010     2012-11-08  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen       = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_ENTRY);
    if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId: P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_CompMappedGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId: imsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_EMM_CompImsi(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId: imei");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL3);

        NAS_EMM_CompImei(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId
 Description     : 多模且TIN值为INVALID时，EPS mobile identity IE编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.lihong 00150010     2012-11-08  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen       = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_ENTRY);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_CompNativeGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
        return;
    }

    if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_CompMappedGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
        return;
    }

    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:imsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_CompImsi(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId:imei");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_EMM_CompImei(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId
 Description     : 多模且TIN值为GUTI或者RAT RELATED TMSI时，EPS mobile identity
                   IE编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.lihong 00150010     2012-11-08  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen       = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_ENTRY);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_CompNativeGuti(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId:imsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_CompImsi(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId:imei");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_CompImei(&(pucReqMsg[0]),&ulLen);
        *pulIeLength            = ulLen;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeEpsMobileId
 Description     : EPS mobile identity IE编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-5-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeEpsMobileId
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulLen = NAS_EMM_NULL;

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    ulTinType = NAS_EMM_GetTinType();

    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if (MMC_LMM_TIN_P_TMSI == ulTinType)
        {
            NAS_EMM_MultiModeTinPtmsiEncodeEpsMobileId( &(pucReqMsg[ulIndex]),
                                                        &ulLen);
            *pulIeLength            = ulLen;
        }
        else if ((MMC_LMM_TIN_GUTI == ulTinType) ||
            (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
        {
            NAS_EMM_MultiModeTinGutiOrRatRelatedTmsiEncodeEpsMobileId(  &(pucReqMsg[ulIndex]),
                                                                        &ulLen);
            *pulIeLength            = ulLen;
        }
        else if (MMC_LMM_TIN_INVALID == ulTinType)
        {
            NAS_EMM_MultiModeTinInvalidEncodeEpsMobileId( &(pucReqMsg[ulIndex]),
                                                          &ulLen);
            *pulIeLength            = ulLen;
        }
        else
        {

        }
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeEpsMobileId:NOT SUPPOR MUTI MODE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL1);
        if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeEpsMobileId: GUTI VALID!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeEpsMobileId_ENUM,LNAS_FUNCTION_LABEL2);

            NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength                = ulLen;
        }
        else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
        {
            NAS_EMM_CompImsi(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength            = ulLen;
        }
        else
        {
            NAS_EMM_CompImei(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength            = ulLen;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeEsmContainer
 Description     : ESM message container IE编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
        8       7       6       5       4       3       2       1
    ┌───────────────────────────────┐
    │            ESM message container IEI                         │Octet 1
    ├───────────────────────────────┤
    │         Length of ESM message container contents             │Octet 2
    │                                                              │
    │                                                              │Octet 3
    ├───────────────────────────────┤
    │                                                              │
    │                                                              │Octet 4
    │              ESM message container contents                  │
    │                                                              │Octet n
    ├───────────────────────────────┤
    1.leili 00132387     2011-7-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeEsmContainer
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT16                          usEsmMsgLen = NAS_EMM_NULL;


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeEsmContainer: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeEsmContainer_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    usEsmMsgLen                         = (VOS_UINT16)NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen;
    pucReqMsg[ulIndex++]                = (usEsmMsgLen>>8)& 0xFF;

    pucReqMsg[ulIndex++]                = usEsmMsgLen & 0xFF;

    NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                        NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen,
                        (NAS_EMM_GLO_AD_GetEsmMsgAddr()->aucMsg),
                        NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen);

    ulIndex                             += NAS_EMM_GLO_AD_GetEsmMsgAddr()->ulMsgLen;

    *pulIeLength                        = ulIndex;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodePtmsiSignature
 Description     :  Old P-TMSI signature IE的编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-5-6  Draft Enact
    2.zhengjunyan 00148421 2011-11-22 DTS2011101906633:补充判断条件P-TMSI&RAI有效
*****************************************************************************/
VOS_VOID  NAS_EMM_EncodePtmsiSignature
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;
    /*Coverity 告警消除 2013-9-26 Begin */
    VOS_UINT32                          ulEmmRslt;
    VOS_UINT32                          ulTinType;
    /*Coverity 告警消除 2013-9-26 End */

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodePtmsiSignature: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodePtmsiSignature_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*初始化*/
    NAS_LMM_MEM_SET_S(&stGuInfo, sizeof(NAS_GUMM_INFO_STRU), 0, sizeof(NAS_GUMM_INFO_STRU));

    /*判断是否存在LAI*/
    ulRslt = NAS_EMM_GetGuInfo(NAS_GUMM_PTMSI_SIGNATURE,&stGuInfo);
    /*Coverity 告警消除 2013-9-26 Begin */
    ulEmmRslt = NAS_EMM_CheckMutiModeSupport();
    ulTinType = NAS_EMM_GetTinType();
    /* 携带 old P-TMSI signature IE的条件:
       (MultiMode) && (TIN = P-TMSI或者INVALID)&&(P-TMSI,P-TMSI signature和RAI有效)
    */
    if (NAS_EMM_SUCC == ulEmmRslt)
    {
        if ((MMC_LMM_TIN_P_TMSI == ulTinType) ||
            (MMC_LMM_TIN_INVALID == ulTinType))
        {
            if ((MMC_LMM_SUCC == ulRslt)
            &&(NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity()))
            {
                NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodePtmsiSignature:P-TMSI SIGNATURE VALID");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodePtmsiSignature_ENUM,LNAS_FUNCTION_LABEL1);

                /*填充Old P-TMSI signature*/
                pucReqMsg[ulIndex++]    = NAS_EMM_AD_PTMSI_SIGNATURE_IEI;

                NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                                    NAS_MAX_SIZE_PTMSI_SIGNATURE,
                                    stGuInfo.u.stPtmsiSignature.aucPtmsiSign,
                                    NAS_MAX_SIZE_PTMSI_SIGNATURE);

                ulIndex                 += NAS_MAX_SIZE_PTMSI_SIGNATURE;
                *pulIeLength            = ulIndex;
            }
        }

    }
    NAS_EMM_ATTACH_LOG2_INFO("NAS_EMM_EncodePtmsiSignature: NAS_EMM_CheckMutiModeSupport()= ,NAS_EMM_GetTinType() = ",
                            ulEmmRslt,
                            ulTinType);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodePtmsiSignature_ENUM,LNAS_EMM_MLTI_MODE_TIN,ulEmmRslt,ulTinType);
    /*Coverity 告警消除 2013-9-26 End */
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeAdditionalGuti
 Description     : Additional GUTI IE编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-5-6  Draft Enact
    2.zhengjunyan 00148421 2011-11-22 DTS2011101906633:补充判断条件P-TMSI&RAI有效
*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeAdditionalGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulLen = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeAdditionalGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeAdditionalGuti_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

     /* 携带Additional GUTI的条件:
      (MultiMode) && (TIN = P-TMSI且 P-TMSI和RAI有效) &&(GUTI有效)
    */
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if ((MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
          &&(NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity()))
        {
            if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
            {
                NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeAdditionalGuti: GUTI VALID");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeAdditionalGuti_ENUM,LNAS_FUNCTION_LABEL1);
                pucReqMsg[ulIndex++]    = NAS_EMM_AD_ADDITION_GUTI_IEI;
                NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]), &ulLen);
                *pulIeLength            = ulLen + ulIndex;
            }
        }
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeLRVTai
 Description     : Last visited registered TAI编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-7-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeLRVTai
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeLRVTai: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeLRVTai_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    /*判断是否支持Last visited registered TAI且TAC不为0XFFFE*/
    if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GetLVRTaiOpBit()) &&
        (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(NAS_LMM_GetEmmInfoLastRegPlmnAddr())) &&
        (VOS_FALSE == NAS_LMM_TacIsInvalid(NAS_LMM_GetEmmInfoLastRegTacAddr())))
    {
        /*填充Last visited registered TAI*/
        pucReqMsg[ulIndex++]            = NAS_EMM_AD_TAI_IEI;

        NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                            NAS_EMM_AD_LEN_PLMN_ID,
                            NAS_EMM_GLO_AD_GetLastRegPlmnId(),
                            NAS_EMM_AD_LEN_PLMN_ID);

        ulIndex                         += NAS_EMM_AD_LEN_PLMN_ID;
        pucReqMsg[ulIndex++]            = NAS_EMM_GLO_AD_GetLastRegTac();
        pucReqMsg[ulIndex++]            = NAS_EMM_GLO_AD_GetLastRegTacCnt();

        *pulIeLength                    = ulIndex;

    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeDrxPara
 Description     : DRX parameter编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-7-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeDrxPara
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT8                           ucDrxByte;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeDrxPara: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeDrxPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*从GU->L,且GU模携带DRX参数时，L模不携带*/
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_SUCC == NAS_EMM_IsGuContainPsRegDrx())
        && (NAS_EMM_NO == NAS_LMM_GetEmmInfoDrxNetCapChange()))
    {
        return;
    }

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_EncodeDrxPara:ucNonDrxTimer = , ucSplitOnCcch = ",
                           NAS_MML_GetNonDrxTimer(),NAS_MML_GetSplitOnCcch());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeDrxPara_ENUM,LNAS_FUNCTION_LABEL1,
                           NAS_MML_GetNonDrxTimer(),NAS_MML_GetSplitOnCcch());

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_EncodeDrxPara:ucSplitPgCode = , ucPsDrxLen = ",
                           NAS_MML_GetSplitPgCycleCode(),NAS_MML_GetUeEutranPsDrxLen());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeDrxPara_ENUM,LNAS_FUNCTION_LABEL2,
                           NAS_MML_GetSplitPgCycleCode(),NAS_MML_GetUeEutranPsDrxLen());
    if (NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
    {
        NAS_EMM_TAU_SaveEmmTauContainDrxFlag(NAS_EMM_YES);
    }

    pucReqMsg[ulIndex++]            = NAS_EMM_AD_DRX_IEI;
    pucReqMsg[ulIndex++]            = NAS_EMM_GetSplitPgCycleCode();
    ucDrxByte                       = NAS_EMM_GetNonDrxTimer();
    ucDrxByte                      |= (VOS_UINT8)(NAS_EMM_GetSplitOnCcch()
                                                    << NAS_EMM_AD_MOVEMENT_3_BITS);
    ucDrxByte                      |= (VOS_UINT8)(NAS_EMM_GetUeEutranPsDrxLen()
                                                    << NAS_EMM_AD_MOVEMENT_4_BITS);
    pucReqMsg[ulIndex++]            = ucDrxByte;

    *pulIeLength                    = ulIndex;
    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_EncodeLai
 Description     : MS network capability编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-5-6  Draft Enact
    2.zhengjunyan 00148421 2011-11-15  添加入参enCnMsgType，区分ATTACH REQ和
                                        TAU REQ消息的填充
*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeMsNetworkCapability
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_EMM_MS_NET_CAP_STRU             *pstMsNetCap;
    /* DTS2013071109627 ISR激活后，重选到U小区发起RAU问题 by wangchen 00209181 2013-07-15 */
    NAS_LMM_PUB_INFO_STRU               *pstEmmInfo;
    /* DTS2013071109627 ISR激活后，重选到U小区发起RAU问题 by wangchen 00209181 2013-07-15 */

    NAS_MML_MS_NETWORK_CAPACILITY_STRU  stMsNetCapa = {0};
    VOS_UINT8                           ucMsNetCapLen = NAS_MM_MAX_MS_NET_CAP_LEN;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeMsNetworkCapability: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    /* DTS2013071109627 ISR激活后，重选到U小区发起RAU问题 by wangchen 00209181 2013-07-15 */
    pstEmmInfo                          = NAS_LMM_GetEmmInfoAddr();
    /* DTS2013071109627 ISR激活后，重选到U小区发起RAU问题 by wangchen 00209181 2013-07-15 */
    pstMsNetCap                         = NAS_LMM_GetEmmInfoMsNetCapAddr();

    /* 检视如果是单模，则不填充MS network capability信元*/
    if(NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsNetworkCapability:Single Mode.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_FUNCTION_LABEL1);
        return;

    }

    /* 当前为多模下的TAU消息，且为Periodic TAU，则不填充MS network capability信元*/
    if((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
     &&(NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING == NAS_EMM_TAU_GetTAUtype()))
    {
        NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsNetworkCapability:Periodic TAU.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* 其他情况，填充MS network capability信元*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsNetworkCapability:Fill MsNetCap IE.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsNetworkCapability_ENUM,LNAS_FUNCTION_LABEL3);

    NAS_EMM_GetMsNetworkCapability(&stMsNetCapa);

    /* 将从GU获取的MS网络能力保存到本地 */
    /* DTS2013071109627 ISR激活后，重选到U小区发起RAU问题 by wangchen 00209181 2013-07-15 */
    if (NAS_LMM_NULL != stMsNetCapa.ucNetworkCapabilityLen)
    {
        pstEmmInfo->bitOpMsNetCap = NAS_EMM_BIT_SLCT;
        pstMsNetCap->ucMsNetCapLen = stMsNetCapa.ucNetworkCapabilityLen;

        NAS_LMM_MEM_CPY_S(  pstMsNetCap->aucMsNetCap,
                            NAS_MM_MAX_MS_NET_CAP_LEN,
                            stMsNetCapa.aucNetworkCapability,
                            NAS_MM_MAX_MS_NET_CAP_LEN);
    }
    else
    {
        pstEmmInfo->bitOpMsNetCap = NAS_EMM_BIT_NO_SLCT;

    }
    /* DTS2013071109627 ISR激活后，重选到U小区发起RAU问题 by wangchen 00209181 2013-07-15 */
    if(NAS_MM_MAX_MS_NET_CAP_LEN >= stMsNetCapa.ucNetworkCapabilityLen)
    {
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_NET_CAPA_IEI;

        pucReqMsg[ulIndex++]        = stMsNetCapa.ucNetworkCapabilityLen;

        NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                            stMsNetCapa.ucNetworkCapabilityLen,
                            stMsNetCapa.aucNetworkCapability,
                            stMsNetCapa.ucNetworkCapabilityLen);

        ulIndex                     += stMsNetCapa.ucNetworkCapabilityLen;

        *pulIeLength                = ulIndex;
        return;
    }

    if(NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_MsNetCap())
    {
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_NET_CAPA_IEI;
        pucReqMsg[ulIndex++]        = pstMsNetCap->ucMsNetCapLen;

        if (ucMsNetCapLen > pstMsNetCap->ucMsNetCapLen)
        {
            ucMsNetCapLen = pstMsNetCap->ucMsNetCapLen;
        }
        NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                            ucMsNetCapLen,
                            pstMsNetCap->aucMsNetCap,
                            ucMsNetCapLen);

        ulIndex                     += pstMsNetCap->ucMsNetCapLen;

        *pulIeLength                = ulIndex;

    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeLai
 Description     : Old location area identification编码函数
 Input           : None
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-5-6  Draft Enact
    2.lihong00150010     2011-08-27 Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeLai
(
    VOS_UINT8 *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeLai: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeLai_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG3_NORM("NAS_EMM_EncodeLai:cn msg type,attach type,tau type",
                             enCnMsgType,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeLai_ENUM,LNAS_EMM_CN_MSG_TYPE,
                             enCnMsgType);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeLai_ENUM,LNAS_FUNCTION_LABEL1,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* 如果是ATTACH REQ消息，且不是联合注册，则不携带LAI 信元 */
    if ((NAS_EMM_CN_MT_ATTACH_REQ == enCnMsgType)
        && (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI != NAS_EMM_GLO_GetCnAttReqType()))
    {
        return ;
    }

    /* 如果是TAU REQ消息，且不是联合TAU，则不携带LAI 信元 */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != NAS_EMM_TAU_GetTAUtype()))
    {
        return ;
    }

    /* 如果是IMSI CN DETACH 导致的联合TAU，则不携带LAI信息 */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_IMSI_DETACH_VALID == NAS_EMM_TAU_GetImsiDetachFlag()))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeLai:Imsi cn detach no LAI!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeLai_ENUM,LNAS_FUNCTION_LABEL2);

        return ;
    }
    /*判断是否存在LAI*/
    ulRslt = NAS_EMM_GetGuInfo(NAS_GUMM_LAI,&stGuInfo);

    if (MMC_LMM_SUCC == ulRslt)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeLai:LAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeLai_ENUM,LNAS_FUNCTION_LABEL3);

        /*填充Old location area identification*/
        pucReqMsg[ulIndex++]            = NAS_EMM_AD_LAI_IEI;

        NAS_LMM_MEM_CPY_S(  &(pucReqMsg[ulIndex]),
                            NAS_EMM_AD_LEN_PLMN_ID,
                            stGuInfo.u.stLai.stPlmnId.aucPlmnId,
                            NAS_EMM_AD_LEN_PLMN_ID);

        ulIndex                         += NAS_EMM_AD_LEN_PLMN_ID;

        pucReqMsg[ulIndex++]            = stGuInfo.u.stLai.stLac.ucLac;
        pucReqMsg[ulIndex++]            = stGuInfo.u.stLai.stLac.ucLacCnt;
        *pulIeLength                    = ulIndex;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeTmsiStatus
 Description     : TMSI status编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-5-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeTmsiStatus
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeTmsiStatus: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    NAS_EMM_ATTACH_LOG3_NORM("NAS_EMM_EncodeTmsiStatus:cn msg type,attach type,tau type",
                             enCnMsgType,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_EMM_CN_MSG_TYPE,
                             enCnMsgType);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_FUNCTION_LABEL1,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* 如果是ATTACH REQ消息，且不是联合注册，则不携带TMSI STATUS 信元 */
    if ((NAS_EMM_CN_MT_ATTACH_REQ == enCnMsgType)
        && (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI != NAS_EMM_GLO_GetCnAttReqType()))
    {
        return ;
    }

    /* 如果是TAU REQ消息，且不是联合TAU，则不携带TMSI STATUS 信元 */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != NAS_EMM_TAU_GetTAUtype()))
    {
        return ;
    }
    ulRslt = NAS_EMM_GetGuInfo(NAS_GUMM_TMSI_STATUS,&stGuInfo);

    /* 如果是IMSI CN DETACH 导致的联合TAU，或者GU模不存在TMSI信息，则编码TMSI STATUS信元 */
    if (((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
                && (NAS_EMM_IMSI_DETACH_VALID == NAS_EMM_TAU_GetImsiDetachFlag()))
        || ((MMC_LMM_SUCC == ulRslt) && (MMC_LMM_TMSI_STATUS_INVALID == stGuInfo.u.ulTmsiStatus)))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeTmsiStatus:TMSI STATUS INVALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeTmsiStatus_ENUM,LNAS_FUNCTION_LABEL2);

        /*填充TMSI IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_IEI_TMSI;

        /* 填充 TMSI的 spare */
        pucReqMsg[ulIndex]              &= NAS_EMM_IE_TMSI_SPARE;

        /* 填充 TMSI的 flag */
        pucReqMsg[ulIndex]              |= (VOS_UINT8)MMC_LMM_TMSI_STATUS_VALID;
        ulIndex ++;
        *pulIeLength                    = ulIndex;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeMsClassMark2
 Description     : Mobile station classmark 2编码函数
 Input           : enCnMsgType------消息类型
 Output          : pMsg------------编码IE内容
                   pulIeLength------IE长度

 Return          : VOS_VOID

 History         :

        8       7       6       5       4       3       2       1
    ┌───────────────────────────────┐
    │            Mobile station classmark 2 IEI                    │Octet 1
    ├───────────────────────────────┤
    │         Length of mobile station classmark 2 contents        │Octet 2
    ├───────────────────────────────┤
    │0     │   Revision   │ ES   │      │RF power              │
    │spare │   level      │ IND  │A5/1  │capability            │Octet 3
    ├───────────────────────────────┤
    │ 0    │ PS   │SS Screen     │SM ca │VBS   │VGCS  │ FC   │
    │spare │ capa │ Indicator    │pabi  │      │      │      │Octet 4
    ├───────────────────────────────┤
    │CM3   │ 0    │LCSVA │UCS2  │SoLSA │CMSP  │ A5/3 │A5/2  │
    │      │spare │CAP   │      │      │      │      │      │Octet 5
    ├───────────────────────────────┤

    1.leili 00132387     2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeMsClassMark2
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
)
{
    VOS_UINT8                          *pucReqMsg           = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                           aucMsClassMark2[NAS_MML_CLASSMARK2_LEN] = {0};
    VOS_UINT32                          ulIsSupportSrvccToGU= NAS_EMM_BIT_NO_SLCT;


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeMsClassMark2: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_NULL_PTR);

        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    ulIsSupportSrvccToGU = NAS_EMM_GetSuppSrvccToGU();

    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_EncodeMsClassMark2:cn mst type",
                             enCnMsgType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_EMM_CN_MSG_TYPE,
                             enCnMsgType);

    NAS_EMM_ATTACH_LOG3_NORM("NAS_EMM_EncodeMsClassMark2:support srvcc or not,attach type,tau type",
                             ulIsSupportSrvccToGU,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL1,
                             ulIsSupportSrvccToGU);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL2,
                             NAS_EMM_GLO_GetCnAttReqType(),
                             NAS_EMM_TAU_GetTAUtype());

    /* 如果是ATTACH REQ消息，且不是联合注册，也不支持SRVCC TO GU，则不携带CLASSMARK2信元 */
    if ((NAS_EMM_CN_MT_ATTACH_REQ == enCnMsgType)
        && (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI != NAS_EMM_GLO_GetCnAttReqType())
        && (NAS_EMM_BIT_NO_SLCT == ulIsSupportSrvccToGU))
    {
        return ;
    }

    /* 如果是TAU REQ消息，且不是联合TAU，也不支持SRVCC TO GU，则不携带CLAMARK2信元 */
    if ((NAS_EMM_CN_MT_TAU_REQ == enCnMsgType)
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI != NAS_EMM_TAU_GetTAUtype())
        && (NAS_EMM_BIT_NO_SLCT == ulIsSupportSrvccToGU))
    {
        return ;
    }
    /* 从GU获取classmark2 */
    NAS_EMM_FillIEClassMark2(aucMsClassMark2);
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsClassMark2: MsClassMark2's value is:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL3);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                        aucMsClassMark2,
                        NAS_MML_CLASSMARK2_LEN);

    if(NAS_MML_CLASSMARK2_LEN > aucMsClassMark2[0])
    {
        /*填充Mobile station classmark 2 IEI*/
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_CLASSMARK2_IEI;

        /* 信元长度 */
        pucReqMsg[ulIndex++]        = aucMsClassMark2[0];

        /* 拷贝除长度之外的剩余部分 */
        NAS_LMM_MEM_CPY_S(  &pucReqMsg[ulIndex],
                            aucMsClassMark2[0],
                            &aucMsClassMark2[1],
                            aucMsClassMark2[0]);

        ulIndex += aucMsClassMark2[0];
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_INFO("NAS_EMM_EncodeMsClassMark2: MsClassMark2's length is ERR:", aucMsClassMark2[0]);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark2_ENUM,LNAS_FUNCTION_LABEL4,aucMsClassMark2[0]);
    }

    *pulIeLength = ulIndex;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeMsClassMark3
 Description     : Mobile station classmark 3编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeMsClassMark3
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8            *pucReqMsg;
    VOS_UINT32           ulIndex = NAS_EMM_NULL;
    /*sunbing 49683 2013-10-14 VoLTE begin*/
    VOS_UINT8            aucMsClassMark3[NAS_EMM_AD_LEN_MS_CLASSMARK3+1] = {0};/*增加一个byte的Lenth的保存空间*/
    /*sunbing 49683 2013-10-14 VoLTE end*/


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeMsClassMark3: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*判断是否支持Mobile station classmark 3*/
    if (NAS_EMM_BIT_SLCT != NAS_EMM_GetSuppSrvccToGU())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeMsClassMark3:Not support SRVCC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*sunbing 49683 2013-10-14 VoLTE begin*/
    /* 从GU获取classmark3 */
    if(MMC_LMM_UTRAN_MODE_FDD == NAS_LMM_GetEmmInfoUtranMode())
    {
        NAS_MML_Fill_IE_FddClassMark3(aucMsClassMark3);
    }
    else
    {
        NAS_MML_Fill_IE_TddClassMark3(aucMsClassMark3);
    }

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_EncodeMsClassMark3: MsClassMark3's value is:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_FUNCTION_LABEL2);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                        aucMsClassMark3,
                        NAS_EMM_AD_LEN_MS_CLASSMARK3+1);

    if(NAS_EMM_AD_LEN_MS_CLASSMARK3 >= aucMsClassMark3[0])
    {
        /*填充Mobile station classmark 3 IEI*/
        pucReqMsg[ulIndex++]        = NAS_EMM_AD_MS_CLASSMARK3_IEI;

        /* 信元长度 */
        pucReqMsg[ulIndex++]        = aucMsClassMark3[0];

        /* 拷贝除长度之外的剩余部分 */
        NAS_LMM_MEM_CPY_S(  &pucReqMsg[ulIndex],
                            aucMsClassMark3[0],
                            &aucMsClassMark3[1],
                            aucMsClassMark3[0]);

        ulIndex += aucMsClassMark3[0];
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_INFO("NAS_EMM_EncodeMsClassMark3: MsClassMark3's length is ERR:", aucMsClassMark3[0]);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeMsClassMark3_ENUM,LNAS_ERROR,aucMsClassMark3[0]);
    }

    *pulIeLength = ulIndex;
    /*sunbing 49683 2013-10-14 VoLTE end*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeSupportedCodecs
 Description     : Supported Codecs编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
        8       7       6       5       4       3       2       1
    ┌───────────────────────────────┐
    │                  Supported Codec List IEI                    │Octet 1
    ├───────────────────────────────┤
    │                Length Of Supported Codec list                │Octet 2
    ├───────────────────────────────┤
    │               System Identification 1 (SysID 1)              │Octet 3
    ├───────────────────────────────┤
    │                 Length Of Bitmap for SysID 1                 │Octet 4
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 1, bits 1 to 8            │Octet 5
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 1, bits 9 to 16           │Octet 6
    ├───────────────────────────────┤
    │               System Identification 2 (SysID 2)              │Octet j
    ├───────────────────────────────┤
    │                 Length Of Bitmap for SysID 2                 │Octet j+1
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 2, bits 1 to 8            │Octet j+2
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID 2, bits 9 to 16           │Octet j+3
    ├───────────────────────────────┤
    │               System Identification x (SysID x)              │Octet m
    ├───────────────────────────────┤
    │                 Length Of Bitmap for SysID x                 │Octet m+1
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID x, bits 1 to 8            │Octet m+2
    ├───────────────────────────────┤
    │             Codec Bitmap for SysID x, bits 9 to 16           │Octet m+3
    └───────────────────────────────┘

    1.leili 00132387     2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeSupportedCodecs
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_LMM_CODEC_LIST_STRU             *pstCodecList;


    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeSupportedCodecs: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeSupportedCodecs_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    pstCodecList                        = NAS_LMM_GetEmmInfoSupCodecListAddr();

    /*判断是否支持Supported Codecs*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_GetSuppSrvccToGU())
    {
        if (NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_SupCodecList())
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeSupportedCodecs:Encode upported Codecs");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeSupportedCodecs_ENUM,LNAS_FUNCTION_LABEL1);

            /*填充Supported Codecs IEI*/
            pucReqMsg[ulIndex++]        = NAS_EMM_AD_SUPPORT_CODECS_IEI;

            /* 填充 Supported Codecs的 L */
            pucReqMsg[ulIndex++]        = pstCodecList->ucLenOfCodecList;

            /* 填充 Supported Codecs的 V */
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].ucSysId;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].ucLenOfBitmap;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].aucCodecBitmap[0];
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[0].aucCodecBitmap[1];

            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].ucSysId;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].ucLenOfBitmap;
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].aucCodecBitmap[0];
            pucReqMsg[ulIndex++]        = pstCodecList->astCodec[1].aucCodecBitmap[1];

            *pulIeLength                = ulIndex;

        }
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeAdditionUpdateType
 Description     : Additional update type编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
        8       7       6       5       4       3       2       1
    ┌───────────────────────────────┐
    │Additional update result IEI  │ 0    │ 0    │Additional    │
    │                              │      │      │  update      │
    │                              │Spare │Spare │ result value │Octet 1
    ├───────────────────────────────┤

    1.leili 00132387     2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeAdditionUpdateType
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeAdditionUpdateType: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeAdditionUpdateType_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    ulCsService = NAS_EMM_GetCsService();
    /* coverity[unchecked_value] */
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_EncodeAdditionUpdateType:cs service :",
                             ulCsService);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeAdditionUpdateType_ENUM,LNAS_EMM_CSSERVICECFG,
                             ulCsService);

    /*判断是否携带Additional update type*/
    if (NAS_LMM_CS_SERVICE_SMS_ONLY == ulCsService)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeAdditionUpdateType:SMS ONLY");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeAdditionUpdateType_ENUM,LNAS_FUNCTION_LABEL1);

        /*填充Additional update type IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_IEI_AUT;

        /* 填充 Additional update type的 spare */
        pucReqMsg[ulIndex]              &= NAS_EMM_IE_AUT_SPARE;

        /* 填充 Additional update type的 AUTV */
        pucReqMsg[ulIndex]              |= NAS_EMM_IE_AUTV;
        ulIndex ++;
        *pulIeLength                    = ulIndex;

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeAdditionUpdateType
 Description     : Voice domain preference and UE's usage setting编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
        8       7       6       5       4       3       2       1
    ┌───────────────────────────────- - ┐
    │   Voice domain preference and UE's usage setting IEI             │Octet 1
    ├───────────────────────────────- - ┤
    │Length of Voice domain preference and UE's usage setting contents │Octet 2
    ├───────────────────────────────- - ┤
    │ 0    │ 0    │0     │0     │0     │UE's    │ Voice domain   │
    │      │      │      │      │      │usage   │preference for  │
    │Spare │Spare │Spare │Spare │Spare │setting │  E-UTRAN       │Octet 3
    ├───────────────────────────────- - ┤

    1.leili 00132387     2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeVoiceDomainAndUsageSetting
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    NAS_EMM_PUB_INFO_STRU               *pstPubInfo;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulRslt;
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;
    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeVoiceDomainAndUsageSetting: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeVoiceDomainAndUsageSetting_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    ulCsService = NAS_EMM_GetCsService();
    NAS_EMM_ATTACH_LOG2_NORM("NAS_EMM_EncodeVoiceDomainAndUsageSetting:\
                            NAS_EMM_GetVoiceDomain=,NAS_EMM_GetCsService()=",
                            NAS_EMM_GetVoiceDomain(),
                            ulCsService);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_EncodeVoiceDomainAndUsageSetting_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetVoiceDomain(),
                            ulCsService);


    /*根据协议要求， 对VOIC domain preference and UE's usage setting, 协议有
    如下: The IE shall be included if the UE supports CS fallback and SMS
    over SGs, or if the UE is configured to support IMS voice, 当支持csfb的
    时候，必须是CS+PS的注册方式，所以EPS only时，则不需要携带此IE*/
    /*判断是否携带Voice domain preference and UE's usage setting*/
    if (((NAS_LMM_CS_SERVICE_CSFB_SMS == ulCsService) &&
         (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode())) ||
        (((NAS_LMM_VOICE_DOMAIN_CS_ONLY < NAS_EMM_GetVoiceDomain()) &&
          (NAS_LMM_VOICE_DOMAIN_BUTT > NAS_EMM_GetVoiceDomain())) &&
          (NAS_LMM_CS_SERVICE_1xCSFB != ulCsService)))
    {
        pstPubInfo = NAS_LMM_GetEmmInfoAddr();
        if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeVoiceDomainAndUsageSetting: Encode Voice Domain");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeVoiceDomainAndUsageSetting_ENUM,LNAS_FUNCTION_LABEL2);

            /*填充Voice domain preference and UE's usage setting IEI*/
            pucReqMsg[ulIndex++]            = NAS_EMM_AD_VOICE_DOMAIN_AND_USAGE_SETTING_IEI;

            /* 填充 Voice domain preference and UE's usage setting的 L */
            pucReqMsg[ulIndex++]            = NAS_EMM_AD_LEN_VOICE_DOMAIN;

            /* 填充 Voice domain preference and UE's usage setting的 V */
            NAS_EMM_SetUeUsageSetting();
            ulRslt = NAS_LMM_GetEmmInfoVoiceDomain();
            pucReqMsg[ulIndex]              = (VOS_UINT8)(NAS_EMM_GLO_AD_GetUsgSetting() << NAS_EMM_AD_MOVEMENT_2_BITS);
            pucReqMsg[ulIndex]              |= (VOS_UINT8)ulRslt;
            ulIndex ++;
            *pulIeLength                    = ulIndex;
        }
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_EncodeTmsiBasedNriContainer
 Description     : TMSI based NRI container编码函数
 Input           : None
 Output          : pMsg------------编码IE内容

 Return          : VOS_VOID

 History         :
    1.wangchen 00209181 2014-08-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeTmsiBasedNriContainer
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
)
{
    VOS_UINT8                          *pucTmsi             = VOS_NULL_PTR;
    VOS_UINT8                          *pucReqMsg           = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    /* 读取当前的TMSI */
    pucTmsi  = NAS_EMM_GetUeIdTmsi();

    if((VOS_NULL_PTR == pMsg) ||
       (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EncodeTmsiBasedNriContainer: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeTmsiBasedNriContainer_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_EncodeTmsiBasedNriContainer:TMSI :",
                             pucTmsi);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeTmsiBasedNriContainer_ENUM,LNAS_EMM_TMSI_NUMBER,pucTmsi);

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /* 如果TMSI无效，则不编码该信元 */
    if(VOS_FALSE  == NAS_MML_IsTmsiValid())
    {
        return;
    }

    if (VOS_NULL_PTR == pucTmsi )
    {
        return;
    }

    /*填充Mobile station classmark 2 IEI*/
    pucReqMsg[ulIndex++]        = NAS_EMM_AD_TMSI_BASED_NRI_CONTAINER_IEI;

    /* 信元长度 */
    pucReqMsg[ulIndex++]        = NAS_EMM_AD_LEN_TMSI_BASED_NRI_CONTAINER;

    /* 将TMSI中从 bit23到bit14这10bit的内容编码为TMSI based NRI container信元 */
    /* NRI container value shall start with bit 8 of octet 3, which corresponds to bit 23 of TMSI.
        Bit 7 of octet 4 corresponds to TMSI bit 14.
        Bits 6, 5, 4, 3, 2, and 1 in octet 4 are spare and shall be set to zero.*/

    pucReqMsg[ulIndex++]        = pucTmsi[2];
    pucReqMsg[ulIndex++]        = (pucTmsi[1] & NAS_EMM_HITH2_BYTE);

    *pulIeLength                = ulIndex;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MutiModeTinPtmsiEncodeGutiType
 Description     : 多模，TIN为PTMSI,Old GUTI type编码函数
 Input           : None
 Output          : pMsg ------Old GUTI type内容
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-3-25  Draft Enact

*****************************************************************************/
NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_MutiModeTinPtmsiEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinPtmsiEncodeGutiType:TIN IS P-TMSI");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinPtmsiEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL1);
    if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinPtmsiEncodeGutiType: P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinPtmsiEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL2);
        /*映射GUTI有效*/
        ucGutiType = NAS_EMM_GUTI_TYPE_MAPPED;
    }
    return ucGutiType;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType
 Description     : 多模，TIN为GUTI OR RAT RELATED TMSI,Old GUTI type编码函数
 Input           : None
 Output          : pMsg ------Old GUTI type内容
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-3-25  Draft Enact

*****************************************************************************/
NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType_ENUM,LNAS_EMM_TIN_TYPE);
        /*GUTI有效*/
        ucGutiType = NAS_EMM_GUTI_TYPE_NATIVE;
    }
    return ucGutiType;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MutiModeTinInvaidEncodeGutiType
 Description     : 多模，TIN为无效,Old GUTI type编码函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-3-25  Draft Enact

*****************************************************************************/
NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_MutiModeTinInvaidEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinInvaidEncodeGutiType:TIN INVALID");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinInvaidEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL1);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinInvaidEncodeGutiType:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinInvaidEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL2);
        /*GUTI有效*/
        ucGutiType = NAS_EMM_GUTI_TYPE_NATIVE;

    }
    else if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MutiModeTinInvaidEncodeGutiType:P-TMSI and RAI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MutiModeTinInvaidEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL3);
        /*映射GUTI有效*/
        ucGutiType = NAS_EMM_GUTI_TYPE_MAPPED;

    }
    else
    {
        ;
    }
    return ucGutiType;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SingleModeEncodeGutiType
 Description     : 单模,Old GUTI type编码函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-3-25  Draft Enact

*****************************************************************************/
NAS_EMM_GUTI_TYPE_ENUM_UINT8 NAS_EMM_SingleModeEncodeGutiType
(
    VOS_VOID
)
{
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_SingleModeEncodeGutiType:NOT SUPPOR MUTI MODE");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SingleModeEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL1);
    if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_GUTI())
    {
        /*GUTI有效*/
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_SingleModeEncodeGutiType: GUTI VALID!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SingleModeEncodeGutiType_ENUM,LNAS_FUNCTION_LABEL2);

        ucGutiType = NAS_EMM_GUTI_TYPE_NATIVE;
    }
    return ucGutiType;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeGutiType
 Description     : Old GUTI type编码函数
 Input           : None
 Output          : pMsg ------Old GUTI type内容
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeGutiType
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    NAS_EMM_GUTI_TYPE_ENUM_UINT8        ucGutiType = NAS_EMM_GUTI_TYPE_BUTT;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeGutiType: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeGutiType_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    /*支持多模*/
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if (MMC_LMM_TIN_P_TMSI == ulTinType)
        {
            ucGutiType = NAS_EMM_MutiModeTinPtmsiEncodeGutiType();
        }
        else if ((MMC_LMM_TIN_GUTI == ulTinType) ||
            (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
        {
            ucGutiType = NAS_EMM_MutiModeTinGutiOrRatRelatedTmsiEncodeGutiType();
        }
        else if (MMC_LMM_TIN_INVALID == ulTinType)
        {
            ucGutiType = NAS_EMM_MutiModeTinInvaidEncodeGutiType();

        }
        else
        {

        }
    }
    else
    {
        /*单模*/
        ucGutiType = NAS_EMM_SingleModeEncodeGutiType();

    }

    if (NAS_EMM_GUTI_TYPE_BUTT == ucGutiType)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EncodeGutiType:not encode guti type");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeGutiType_ENUM,LNAS_EMM_TIN_TYPE);
        return;
    }

    /*GUTI有效携带该IE*/
    /*填充GUTI TYPE IEI*/
    pucReqMsg[ulIndex]              = NAS_EMM_TAU_REQ_GUTI_TYPE_IEI;

    /* 填充 GUTI TYPE的 spare */
    pucReqMsg[ulIndex]              &= NAS_EMM_TAU_REQ_IE_SPARE;

    /* 填充GUTI TYPE的GUTI type */
    pucReqMsg[ulIndex]              |= ucGutiType;

    ulIndex ++;

    *pulIeLength                        = ulIndex;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CompCnAttachCmp
 Description     : 填充空口消息ATTACH COMPLETE的内容

 Input           :
 Output          :
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化
    3.lihong00150010         2012-10-31  Modify:emgergency

*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnAttachCmp
(
    LRRC_LNAS_MSG_STRU                 *pAttCmp,
    VOS_UINT32                         *pulIndex,
    const EMM_ESM_MSG_STRU             *pstEsmMsg
)
{
    VOS_UINT32                          ulIndex     = *pulIndex;
    VOS_UINT16                          usEsmMsgLen = NAS_EMM_NULL;

    /*清空填充CN消息的空间*/
    /* NAS_LMM_MEM_SET(pAttCmp->aucNasMsg, 0, pAttCmp->ulNasMsgSize); */

    /* 填充 Protocol Discriminator + Security header type */
    pAttCmp->aucNasMsg[ulIndex++]       = EMM_CN_MSG_PD_EMM;

    /* 填充 Attach request message identity   */
    pAttCmp->aucNasMsg[ulIndex++]       = NAS_EMM_CN_MT_ATTACH_CMP;

    /*填充ESM message container*/
    usEsmMsgLen                         = (VOS_UINT16)pstEsmMsg->ulEsmMsgSize;
    pAttCmp->aucNasMsg[ulIndex++]       = (usEsmMsgLen>>8)& 0xFF;
    pAttCmp->aucNasMsg[ulIndex++]       = usEsmMsgLen & 0xFF;

    NAS_LMM_MEM_CPY_S(  &(pAttCmp->aucNasMsg[ulIndex]),
                        pstEsmMsg->ulEsmMsgSize,
                        pstEsmMsg->aucEsmMsg,
                        pstEsmMsg->ulEsmMsgSize);

    *pulIndex = ulIndex + pstEsmMsg->ulEsmMsgSize;
}


/*****************************************************************************
 Function Name   :  NAS_EMM_MrrcSendAttReq
 Description     : 向MRRC发送NAS_EMM_MRRC_DATA_REQ(ATTACH REQUEST)消息

 Input           :
 Output          :
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化
    3.sunjitan 00193151      2012-07-12  Modify: Last TA维护，增加save Last TA
    4.lihong 00150010        2012-10-31  Modify:emergency
*****************************************************************************/
VOS_VOID    NAS_EMM_MrrcSendAttReq( VOS_VOID )
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg = NAS_EMM_NULL_PTR;
    NAS_MSG_STRU                        *pstNasMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_ATTACH_LOG_INFO("Enter NAS_EMM_MrrcSendAttReq,ESM MSG LEN");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcSendAttReq_ENUM,LNAS_BEGIN);

    /*申请消息内存*/
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*构造ATTACH REQUEST消息*/
    NAS_EMM_CompCnAttachReq( pIntraMsg);

    /* 如果是联合ATTACH，则通知MM进入MM LOCATION UPDATING PENDING状态 */
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_SendMmCombinedStartNotifyReq(MM_LMM_COMBINED_ATTACH);
    }

    /*向OM发送空口消息ATTACH REQUEST*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));

    NAS_LMM_SendOmtAirMsg(               NAS_EMM_OMT_AIR_MSG_UP,
                                        NAS_EMM_ATTACH_REQ,
                                        pstNasMsg);
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_ATTACH_REQ);
    /* 大数据: 更新attach发起次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL);

    /* 非紧急注册, 通知IMSA ATTACH  BEGIN */
    if (LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL != pIntraMsg->enCallType)
    {
        NSA_EMM_SndImsaAttachBeginInd();
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送begin notify消息给RRC，通知RRC申请资源*/
    NAS_LMM_SendRrcDsdsBeginNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*向MRRC发送ATTACH REQUEST消息*/
    NAS_EMM_SndUplinkNasMsg(             pIntraMsg);

    /* 发起ATTACH，将当前TA信息同步到Last尝试发起注册的TA信息中 */
    NAS_EMM_SaveLastAttemptRegTa();

    /* 发起ATTACH，将注册状态设置为ATTACH未发送 */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND);

    NAS_LMM_MEM_FREE(pIntraMsg);
    /* 大数据: 记录ATTACH REQ SND时间 */
    NAS_LMM_SaveAttachReqSndTimeStamp();
    return;

}

/*****************************************************************************
 Function Name   :  NAS_EMM_MrrcSendAttCmp
 Description     : 向MRRC发送NAS_EMM_MRRC_DATA_REQ(ATTACH COMPLETE)消息

 Input           :
 Output          :
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化
    3.lihong00150010         2012-10-31  Modify:emgergency

*****************************************************************************/
VOS_VOID    NAS_EMM_MrrcSendAttCmp
(
    const EMM_ESM_MSG_STRU             *pstEsmMsg
)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pIntraMsg;
    VOS_UINT32                          ulMrrcDataReqMsgLenNoHeader;
    NAS_MSG_STRU                       *pstNasMsg;
    VOS_UINT32                          ulIndex             =0;

    NAS_EMM_ATTACH_LOG_INFO("Enter NAS_EMM_MrrcSendAttCmp,ESM MSG LEN");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcSendAttCmp_ENUM,LNAS_BEGIN);

    /*申请消息内存*/
    pIntraMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*lint -e669*/
    NAS_LMM_MEM_SET_S(pIntraMsg, NAS_EMM_INTRA_MSG_MAX_SIZE, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);
    /*lint +e669*/

    /*构造ATTACH COMPLETE消息*/
    NAS_EMM_CompCnAttachCmp(            &(pIntraMsg->stNasMsg),&ulIndex,pstEsmMsg);

    ulMrrcDataReqMsgLenNoHeader         = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulMrrcDataReqMsgLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_MrrcSendAttCmp, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MrrcSendAttCmp_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pIntraMsg);
        return ;
    }

    /*填充消息头*/
    NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pIntraMsg, ulMrrcDataReqMsgLenNoHeader);

    /*填充消息ID*/
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填充消息内容*/
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enEmmMsgType             = NAS_EMM_MSG_ATTACH_CMP;

    /*填充消息是否需要RRC对传输结果确认*/
    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;

    /*填充消息是EMM发送的还是ESM发送的*/
    pIntraMsg->ulEsmMmOpId             = NAS_LMM_OPID;

    /*填充消息长度*/
    pIntraMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*向OM发送空口消息ATTACH COMPLETE*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_ATTACH_CMP, pstNasMsg);
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_ATTACH_CMP);

    /*向MRRC发送ATTACH COMPLETE消息*/
    NAS_EMM_SndUplinkNasMsg(             pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);
    /* 大数据: 记录ATTACH CMP Snd时间 */
    NAS_LMM_SaveAttachCmpSndTimeStamp();
    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_PDN_RSP下收到ESM发送的
                   ID_EMM_ESM_PDN_CON_RSP消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739   2009-08-12  MODIFY BJ9D01687
    3.zhengjunyan 001148421 2010-11-09 MOD:考虑RegInit.WtPdnRsp可能是CONN态的情况
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
#if (VOS_OS_VER != VOS_WIN32)
    FTM_TMODE_ENUM                      enMspFtmMode = EN_FTM_TMODE_SIGNAL ;
#endif

    EMM_ESM_PDN_CON_RSP_STRU             *pRcvEmmMsg;

    pRcvEmmMsg                          = (EMM_ESM_PDN_CON_RSP_STRU *) pMsgStru;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG1_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp: STATE ERR! ulMsgId:",ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_ERROR,ulMsgId);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_EsmPdnRspMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp: EMM_ESM_PDN_CON_RSP_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_PARAM_INVALID);
        return NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*停止定时器WAIT_ESM_PDN_CNF*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*停止定时器T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*停止定时器T3402*/
    NAS_LMM_Stop3402Timer();

    if(EMM_ESM_PDN_CON_RSLT_SUCC == pRcvEmmMsg->ulRst)
    {
        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pRcvEmmMsg->stEsmMsg),
                            (pRcvEmmMsg->stEsmMsg.ulEsmMsgSize)+4);

#if (VOS_OS_VER != VOS_WIN32)
        /*BT模式下，规避仪器问题，修改启动定时器等待网络响应*/
        if((LPS_OM_GetTmode(&enMspFtmMode)== ERR_MSP_SUCCESS)&&(EN_FTM_TMODE_SIGNAL_NOCARD == enMspFtmMode))
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp:T3410 modify 240s!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_LMM_ModifyStateTimer(TI_NAS_EMM_T3410, 240000);         /*240s*/
        }
#endif

        /*启动定时器T3410*/
        NAS_LMM_StartStateTimer(     TI_NAS_EMM_T3410);

        /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_CN_ATTACH_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                        TI_NAS_EMM_T3410);

        NAS_EMM_MrrcSendAttReq();

        /* 33401 CR457中描述UE从脱离去注册态转去注册态时，需要将SIM卡或者NV中的安全
        上下文设置为无效*/
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);


    }
    else
    {
        /*向MMC发送消息*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ESM_FAILURE);

        /*ATTACH清除资源*/
        NAS_EMM_Attach_ClearResourse();

        /*向ESM发送ID_EMM_ESM_REL_IND*/
        NAS_EMM_EsmSendRelInd();

        /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /* 如果处于CONN态,释放连接*/
        if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        }

    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_BEARER_CNF下收到ESM的
                   消息ACTIVATE DEFAULT EPS BEARER ACCEPT
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.lihong 00150010        2009-08-18  Modify
    3.X00148705              2010-01-22  增加直传消息确认
    4.lihong00150010         2012-05-22  将Last visit TAI更新从ATTACH COMPLETE发送成功
                                         移至此处

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{
    EMM_ESM_PDN_CON_SUCC_REQ_STRU      *pRcvEmmMsg = VOS_NULL_PTR;
    /*NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo = VOS_NULL_PTR;*/
#if (VOS_OS_VER != VOS_WIN32)
    static VOS_UINT32  s_ulNasSndDrvCnt = 1;
#endif

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (EMM_ESM_PDN_CON_SUCC_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*停止定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(                  TI_NAS_EMM_WAIT_ESM_BEARER_CNF);


#if (VOS_OS_VER != VOS_WIN32)
    if (1 == s_ulNasSndDrvCnt)
    {
        (VOS_VOID)LDRV_SYSBOOT_STAMPADD("Nas reg End",__LINE__);
        s_ulNasSndDrvCnt++;
    }
#endif

    /*启动定时器TI_NAS_EMM_WAIT_RRC_DATA_REQ_CNF*/
    NAS_LMM_StartStateTimer(            TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*修改状态：进入主状态REG子状态REG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_RRC_DATA_CNF,
                                        TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*向MRRC发送ATTACH COMPLETE*/
    NAS_EMM_MrrcSendAttCmp(             &pRcvEmmMsg->stEsmMsg);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_BEARER_CNF下收到ESM的
                   消息ACTIVATE DEFAULT EPS BEARER FAIL
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2009-03-16  Draft Enact
    2.lihong 00150010        2009-08-18  Modify

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru)
{
    NAS_EMM_ATTACH_LOG2_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq is entered",
                                        ulMsgId,
                                        pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq_ENUM,LNAS_ENTRY,
                                        ulMsgId,
                                        pMsgStru);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*check input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq: NULL PTR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*停止定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* 大数据: 更新attach ESM流程失败次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ESM_FAIL);
    /*通知APP缺省承载激活失败*/
    /*NAS_EMM_AttSendAppResult(APP_ERR_MM_ATTACH_FAIL_ACT_DEFAULT_BEARER_FAIL);*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_ESM_FAILURE);

    /* 根据ATTACH类型填写DETACH类型 */
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_CS_PS);
    }
    else
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_PS_ONLY);
    }

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_NORMAL_SERVICE下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.X00148705              2009-05-19  Modify stop timer t3402
    3.lihong00150010         2012-10-31  Modify:emgergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq(VOS_UINT32  ulMsgId,
                                           VOS_VOID   *pMsgStru)
{
    EMM_ESM_EST_REQ_STRU                 *pRcvEmmMsg;

    pRcvEmmMsg                          = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*停止定时器T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*停止定时器T3402*/
    NAS_LMM_Stop3402Timer();

    NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);

    if (VOS_TRUE == pRcvEmmMsg->ulIsEmcType)
    {
        /* 记录ATTACH触发原因值 */
        NAS_EMM_GLO_AD_GetAttCau()      = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

        /* 缓存紧急类型的ESM消息 */
        NAS_EMM_SaveEmcEsmMsg(          (VOS_VOID*)pRcvEmmMsg);

        /* 发起普通ATTACH流程 */
        NAS_EMM_EsmSendPdnConnInd(      0);
        NAS_LMM_StartStateTimer(        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    }
    else
    {
        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pRcvEmmMsg->stEsmMsg),
                            (pRcvEmmMsg->stEsmMsg.ulEsmMsgSize)+4);

        /*保存触发ATTACH的原因*/
        NAS_EMM_GLO_AD_GetAttCau()      = EMM_ATTACH_CAUSE_ESM;

        /*启动定时器T3410*/
        NAS_LMM_StartStateTimer(        TI_NAS_EMM_T3410);

        /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_CN_ATTACH_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                        TI_NAS_EMM_T3410);
        /* 大数据: 记录ATTACH流程Start时间 */
        NAS_LMM_SaveAttachStartTimeStamp();
        /*向MRRC发送ATTACH REQUEST消息*/
        NAS_EMM_MrrcSendAttReq();
        /* 33401 CR457中描述UE从脱离去注册态转去注册态时，需要将SIM卡或者NV中的安全
        上下文设置为无效*/
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);


    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_ATTEMPT_TO_ATTACH下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010         2012-10-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq
(
    VOS_UINT32                              ulMsgId,
    VOS_VOID                               *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pRcvEmmMsg = NAS_EMM_NULL_PTR;

    pRcvEmmMsg                          = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE != pRcvEmmMsg->ulIsEmcType)
    {
        /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*停止定时器T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*停止定时器T3402*/
    NAS_LMM_Stop3402Timer();

    NAS_MML_SetPsAttachAllowFlg(    NAS_EMM_AUTO_ATTACH_ALLOW);

    /* 记录ATTACH触发原因值 */
    NAS_EMM_GLO_AD_GetAttCau()      = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;
    NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

    /* 缓存紧急类型的ESM消息 */
    NAS_EMM_SaveEmcEsmMsg(          pMsgStru);

    /* 发起普通ATTACH流程 */
    NAS_EMM_EsmSendPdnConnInd(      0);
    NAS_LMM_StartStateTimer(        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                    EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                    TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_StartEmergencyAttach
 Description     : 发起紧急注册
 Input           : pstEsmEstReq
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010         2012-10-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_StartEmergencyAttach( VOS_VOID )
{
    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_StartEmergencyAttach is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_StartEmergencyAttach_ENUM,LNAS_ENTRY);

    /*停止定时器T3411*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*停止定时器T3402*/
    NAS_LMM_Stop3402Timer();

    /*保存触发ATTACH的原因*/
    NAS_EMM_GLO_AD_GetAttCau()    = EMM_ATTACH_CAUSE_ESM_EMC_ATTACH;
    NAS_MML_SetPsAttachAllowFlg(    NAS_EMM_AUTO_ATTACH_ALLOW);
    NAS_LMM_SetEmmInfoRegStatus(    NAS_LMM_REG_STATUS_EMC_REGING);
    NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

    /*启动定时器T3410*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3410);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_CN_ATTACH_CNF*/
    NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                    EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                    TI_NAS_EMM_T3410);
    /* 大数据: 记录ATTACH流程Start时间 */
    NAS_LMM_SaveAttachStartTimeStamp();
    /*向MRRC发送ATTACH REQUEST消息*/
    NAS_EMM_MrrcSendAttReq();
    /* 33401 CR457中描述UE从脱离去注册态转去注册态时，需要将SIM卡或者NV中的安全
    上下文设置为无效*/
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);


}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_LIMIT_SERVICE下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-10-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_LIMITED_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型则直接回复失败 */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*保存ESM消息*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                        sizeof(NAS_EMM_CN_MSGCON_STRU),
                        &(pstEsmEstReq->stEsmMsg),
                        (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_NO_IMSI下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-10-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_IMSI))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型则直接丢弃 */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*保存ESM消息*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                        sizeof(NAS_EMM_CN_MSGCON_STRU),
                        &(pstEsmEstReq->stEsmMsg),
                        (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_ATTACH_NEEDED下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-10-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型则直接丢弃 */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*保存ESM消息*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                        sizeof(NAS_EMM_CN_MSGCON_STRU),
                        &(pstEsmEstReq->stEsmMsg),
                        (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq
 Description     : 主状态REG+子状态REG_LIMIT_SERVICE下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-10-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_DATA_REQ_STRU                 *pstEsmDataReq = NAS_EMM_NULL_PTR;

    pstEsmDataReq                        = (EMM_ESM_DATA_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq_ENUM,LNAS_ENTRY,ulMsgId);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型则直接丢弃 */
    if (VOS_TRUE != pstEsmDataReq->ulIsEmcType)
    {
        if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
            (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
        {
            NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
            return NAS_LMM_MSG_HANDLED;
        }
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*//* ESM不能清除紧急动态记录 */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif

    /*保存ESM消息*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                        sizeof(NAS_EMM_CN_MSGCON_STRU),
                        &(pstEsmDataReq->stEsmMsg),
                        (pstEsmDataReq->stEsmMsg.ulEsmMsgSize)+4);

    NAS_EMM_StartEmergencyAttach();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitMsgEsmEstReq
 Description     : REG_INIT+WAIT_ESM_PDN_RSP,
                   REG_INIT+WAIT_ATTACH_CN_CNF,
                   REG_INIT+WAIT_ESM_BEARER_CNF,
                   REG_INIT+WAIT_RRC_DATA_CNF
                   状态下收到EMM_ESM_EST_REQ消息的处理
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_MsRegInitMsgEsmEstReq is entered",
                                        ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegInitMsgEsmEstReq_ENUM,LNAS_ENTRY,ulMsgId);


    /*检查状态是否匹配，若不匹配，退出*/
    if (EMM_MS_REG_INIT != NAS_EMM_AD_CUR_MAIN_STAT)
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型则直接丢弃 */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitMsgEsmEstReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 打断正在进行的ATTACH流程 */
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_T3410);
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_RRC_DATA_CNF);



    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;
    NAS_EMM_AppSendAttFailWithPara();
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt() >= 5)
    {
        /*设置update status为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
    }

    NAS_EMM_AttResetAttAttempCounter();

    /* 如果处于IDLE态,直接发起紧急注册*/
    if (NAS_EMM_CONN_IDLE               == NAS_EMM_GetConnState())
    {
        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmEstReq->stEsmMsg),
                            (pstEsmEstReq->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 记录ATTACH触发原因值 */
    NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

    NAS_LMM_SetEmmInfoIsEmerPndEsting(  VOS_TRUE);

    /* 缓存紧急类型的ESM消息 */
    NAS_EMM_SaveEmcEsmMsg(              (VOS_VOID*)pstEsmEstReq);

    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_PLMN_SEARCH下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_PLMN_SEARCH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq
 Description     : 主状态DEREG+子状态DEREG_NO_CELL_AVAILABLE下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq
 Description     : 主状态REG+子状态REG_NORMAL_SERVICE下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型，则不可能收到，如果收到，直接丢弃 */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq
 Description     : 主状态REG+子状态REG_ATTEMPT_TO_UPDATE_MM下收到ESM的消息
                   PDN CONNECTIVITY REQUEST
 Input           : ulMsgId
                   pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2012-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_EST_REQ_STRU                 *pstEsmEstReq = NAS_EMM_NULL_PTR;

    pstEsmEstReq                        = (EMM_ESM_EST_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型，则不可能收到，如果收到，直接丢弃 */
    if (VOS_TRUE != pstEsmEstReq->ulIsEmcType)
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq: not emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
    NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq
 Description     : 本地Detach 并重新 Attach
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-4-22  Draft Enact
    2.X00148705    2009-10-31 增加状态的判断,避免处理和协议不一致
    3.l00150010    2012-12-17 Modify:Emergency
    4.s00193151    2014-06-24 Modify:本地DETACH细化处理
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq( VOS_VOID )
{
    VOS_UINT32                          ulCurEmmMsStat = NAS_LMM_GetEmmCurFsmMS();
    VOS_UINT32                          ulCurEmmSsStat = NAS_LMM_GetEmmCurFsmSS();

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq:EpsNumId=0");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq_ENUM,LNAS_BEGIN);

    /* 主状态为非注册态，直接返回 */
    if ((EMM_MS_NULL == ulCurEmmMsStat)||(EMM_MS_DEREG == ulCurEmmMsStat))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* R10版本对CSFB的特殊处理 */
    if (NAS_RELEASE_CTRL)
    {
        if ((EMM_MS_SER_INIT == ulCurEmmMsStat)
            && (EMM_SS_SER_WAIT_CN_SER_CNF == ulCurEmmSsStat)
            && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq:ESR procedure");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq_ENUM,LNAS_FUNCTION_LABEL1);

            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_PLMN_SEARCH,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
            NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
            #endif

            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

            /* 本地DETACH释放资源:动态内存、赋初值 */
            NAS_LMM_DeregReleaseResource();

            /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
            NAS_EMM_RelReq(                           NAS_LMM_NOT_BARRED);

            return NAS_LMM_MSG_HANDLED;

        }
    }

    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /* 清除拔卡标识 */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;

        /* 给MMC回复LMM_MMC_USIM_STATUS_CNF */
        NAS_EMM_SendMmcUsimStatusCnf();
    }

    /* 根据当前的状态执行不同的本地DETACH处理 */
    switch(ulCurEmmMsStat)
    {
        case    EMM_MS_REG:
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:

                /* 通知ESM执行了本地DETACH */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

                /* 根据不同的子状态转到对应的未注册状态 */
                NAS_LMM_MsRegSsAnyLocalDetStateTrans();

                /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
                NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();

                /* 如果未注册状态的目标状态为正常服务，重新发起ATTACH */
                if(EMM_SS_DEREG_NORMAL_SERVICE == NAS_LMM_GetEmmCurFsmSS())
                {
                    /* 本身处于IDLE正常驻留直接发起ATTACH，否则释放链路等收到系统消息再发起 */
                    if(NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState())
                    {
                        (VOS_VOID)NAS_EMM_SendIntraAttachReq();
                        return NAS_LMM_MSG_HANDLED;
                    }

                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                    return NAS_LMM_MSG_HANDLED;
                }

                /* 其它非normal状态直接等系统消息 */
                break;

        case    EMM_MS_SUSPEND:

                /* 通知ESM执行了本地DETACH */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

                /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
                NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
                #endif

                /* 修改挂起前状态，继续挂起流程 */
                NAS_EMM_SetMsBefSuspend(EMM_MS_DEREG);

                /* 有可能是处于紧急注册的无卡状态 */
                if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
                {
                    NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NO_IMSI);
                }
                else
                {
                    NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NO_CELL_AVAILABLE);
                }

                /* 停止所有EMM协议定时器 ，不调用NAS_LMM_DeregReleaseResource为防止误停当前状态定时器 */
                NAS_LMM_StopAllEmmPtlTimer();

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_PUBM_ClearResource();
                NAS_EMM_PUBU_ClearResource();
                NAS_EMM_SECU_ClearResource();
                NAS_EMM_Attach_ClearResourse();
                NAS_EMM_Detach_ClearResourse();
                NAS_EMM_TAU_ClearResouce();
                NAS_EMM_SER_ClearResource();
                break;

        default:
                /* 其它状态，如RESUME，REG_INIT仅在前面更新承载状态 */
                break;

    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcEsmBearState
 Description     : 该承载在消息中表示承载状态激活，否则没有激活
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
NAS_EMM_BEARER_STATE_ENUM_UINT8  NAS_EMM_ProcEsmBearState
(
    VOS_UINT32      ulEpsId,
    VOS_VOID        *pstMsg
)
{
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstEsmBearerStatusReq   = VOS_NULL_PTR;
    VOS_UINT32              i = 0;

    pstEsmBearerStatusReq               =(EMM_ESM_BEARER_STATUS_REQ_STRU *)(pstMsg);

    for (i = 0; i < pstEsmBearerStatusReq->ulEpsIdNum; i++)
    {
        if (ulEpsId == pstEsmBearerStatusReq->aulEsmEpsId[i])
        {
            return NAS_EMM_BEARER_STATE_ACTIVE;
        }
    }
    return NAS_EMM_BEARER_STATE_INACTIVE;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcEsmBearState
 Description     : 承载是否激活
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen  00209181    2013-02-1  Draft Enact

*****************************************************************************/
NAS_EMM_BEARER_STATE_ENUM_UINT8  NAS_EMM_IsEpsBearStatusAct (VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstEpsBearerCxt;
    VOS_UINT32              i = 0;

    pstEpsBearerCxt = NAS_EMM_GetPsBearerCtx();
    if(VOS_NULL == pstEpsBearerCxt)
    {
        return NAS_EMM_BEARER_STATE_INACTIVE;
    }

    for(i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        if (NAS_MML_PS_BEARER_STATE_ACTIVE == pstEpsBearerCxt[i].enPsBearerState)
        {
            return NAS_EMM_BEARER_STATE_ACTIVE;
        }
    }
    return NAS_EMM_BEARER_STATE_INACTIVE;
}

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateEpsBearStatus
 Description     : 根据收到ESM的承载信息更新EMM的全局变量
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_UpdateEpsBearStatus(VOS_VOID *pstMsg)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerCtx[EMM_ESM_MAX_EPS_BEARER_NUM];
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstEsmBearerStatusReq   = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsId;
    NAS_EMM_BEARER_STATE_ENUM_UINT8     ucEsmBearerState;
    VOS_UINT32                          i = NAS_EMM_NULL;
    VOS_UINT32                          j = NAS_EMM_NULL;
    VOS_UINT16                          usBearerSate;
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx         = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus is entry:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    NAS_LMM_MEM_SET_S(  astPsBearerCtx,
                        sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU)*EMM_ESM_MAX_EPS_BEARER_NUM,
                        0,
                        sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU)*EMM_ESM_MAX_EPS_BEARER_NUM);

    pstEsmBearerStatusReq =(EMM_ESM_BEARER_STATUS_REQ_STRU *)(pstMsg);

    /*ISR不激活，根据ESM发送的承载信息更新MML全局变量*/
    if(MMC_LMM_TIN_RAT_RELATED_TMSI != NAS_EMM_GetTinType())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: ISR没有激活");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL1);
        for(i = 0; i < pstEsmBearerStatusReq->ulEpsIdNum; i++)
        {
            j = pstEsmBearerStatusReq->aulEsmEpsId[i] - NAS_EMM_MIN_EPS_ID;

            astPsBearerCtx[j].enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
        }
        NAS_LMM_MEM_CPY_S(  pstPsBearerCtx,
                            sizeof(astPsBearerCtx),
                            astPsBearerCtx,
                            sizeof(astPsBearerCtx));

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: UPDATE PS BEARER INFO");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        return;
    }

    /*ISR激活，根据ESM承载信息更新MML全局变量*/
    NAS_LMM_MEM_CPY_S(  astPsBearerCtx,
                        sizeof(astPsBearerCtx),
                        pstPsBearerCtx,
                        sizeof(astPsBearerCtx));

    for (i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        ulEpsId = i + NAS_EMM_MIN_EPS_ID;
        ucEsmBearerState = NAS_EMM_ProcEsmBearState(ulEpsId,pstEsmBearerStatusReq);

        usBearerSate = NAS_LMM_PUB_COMP_BEARERSTATE(astPsBearerCtx[i].enPsBearerState,ucEsmBearerState);
        switch(usBearerSate)
        {
            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_ACTIVE,NAS_EMM_BEARER_STATE_INACTIVE):

                /*MML中承载状态激活，ESM中承载状态不激活，根据当前ISR标识判断是否去激活ISR*/
                astPsBearerCtx[i].enPsBearerState = NAS_MML_PS_BEARER_STATE_INACTIVE;
                if (NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT == astPsBearerCtx[i].enPsBearerIsrFlg)
                {
                    /*更新TIN值为GUTI*/
                    NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);

                    /*更新所有承载的ISR标识为NONE*/
                    NAS_EMM_UpdateBearISRFlag(astPsBearerCtx);

                }
                astPsBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
                break;
            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_INACTIVE,NAS_EMM_BEARER_STATE_ACTIVE):

                /*MML中承载状态不激活，ESM中承载状态激活，更新MML中承载状态和ISR标识*/
                astPsBearerCtx[i].enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
                astPsBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT;
                break;

            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_ACTIVE,NAS_EMM_BEARER_STATE_ACTIVE):
            case NAS_LMM_PUB_COMP_BEARERSTATE(NAS_MML_PS_BEARER_STATE_INACTIVE,NAS_EMM_BEARER_STATE_INACTIVE):

                NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: MML BEARER INFO NOT CHANGE:");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL3);
                break;
            default:
                break;
        }
    }


    NAS_LMM_MEM_CPY_S(  pstPsBearerCtx,
                        sizeof(astPsBearerCtx),
                        astPsBearerCtx,
                        sizeof(astPsBearerCtx));

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateEpsBearStatus: UPDATE PS BEARER INFO");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateEpsBearStatus_ENUM,LNAS_FUNCTION_LABEL4);

    NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcEmcBearerStatusNotify
 Description     : 向MMC发送LMM_MMC_EMC_BEARER_STATUS_NOTIFY消息
 Input           : ucIsEmcPdpActive----------------EMC PDP是否激活标识
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2013-12-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendMmcEmcBearerStatusNotify
(
    VOS_UINT8                           ucIsEmcPdpActive
)
{
    LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU *pstEmcPdpStatusNotify = VOS_NULL_PTR;

    /* 申请DOPRA消息 */
    pstEmcPdpStatusNotify = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU));
    if (NAS_LMM_NULL_PTR == pstEmcPdpStatusNotify)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcEmcBearerStatusNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcEmcBearerStatusNotify_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstEmcPdpStatusNotify,
                        sizeof(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU),
                        0,
                        sizeof(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstEmcPdpStatusNotify),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU));

    /* 填充消息ID */
    pstEmcPdpStatusNotify->ulMsgId          = ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY;
    pstEmcPdpStatusNotify->ucIsEmcPdpActive = ucIsEmcPdpActive;

    /* 发送DOPRA消息 */
    NAS_LMM_SendLmmMmcMsg(pstEmcPdpStatusNotify);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq
 Description     : 收到ESM BEARER STATUS REQ消息时更新注册状态
 Input           : Pointer of EMM_ESM_BEARER_STATUS_REQ_STRU
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2012-10-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq
(
    const EMM_ESM_BEARER_STATUS_REQ_STRU *pstEsmBearerStatusReq
)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerCtx[EMM_ESM_MAX_EPS_BEARER_NUM];
    VOS_UINT32                          ulCurEmmStat = NAS_EMM_NULL;

    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;

    NAS_LMM_MEM_SET_S(  astPsBearerCtx,
                        sizeof(astPsBearerCtx),
                        0,
                        sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU)*EMM_ESM_MAX_EPS_BEARER_NUM);

    if (0 == pstEsmBearerStatusReq->ulEpsIdNum)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:DEREG");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_DEREG);
        return ;
    }

    /* 注册过程中，则不更新状态，待ATTACH COMPLETE发送成功
       后再更新，如果这里就更新，则无法在REG_INIT+WAIT_RRC_DATA_CNF状态下使用
       NAS_LMM_REG_STATUS_EMC_REGING标识来区分紧急注册还是普通注册，ATTACH触发
       原因值在紧急承载激活成功清动态表时已通知EMM清除 */
    if (EMM_MS_REG_INIT == NAS_EMM_AD_CUR_MAIN_STAT)
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:attaching.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* 如果有承载，且没有紧急承载，则更新状态为正常注册 */
    if (VOS_FALSE == pstEsmBearerStatusReq->ulExistEmcPdnFlag)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:NORM REGED");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL3);

        /* 如果状态从正常注册且有紧急承载变为正常注册，则给MMC发送
           LMM_MMC_EMC_BEARER_STATUS_NOTIFY消息，指示紧急承载释放 */
        if (NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_EMM_SendMmcEmcBearerStatusNotify(VOS_FALSE);
        }

        NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED);
        return ;
    }
    /* 如果有紧急承载，且承载数为1，则更新状态为紧急注册 */
    if (1 == pstEsmBearerStatusReq->ulEpsIdNum)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:EMC REGED");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL4);

        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                    NAS_EMM_CUR_SUB_STAT);

        if (((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
            || (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
            && (NAS_LMM_TIMER_STOPED == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
        {
            NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
            NAS_LMM_Stop3402Timer();

            /* TAU完成后，网侧通过ESM承载信息IE去激活所有非紧急承载 */
            NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }

        NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_EMC_REGED);

        if ((MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
            && (NAS_EMM_NOT_SUSPEND == NAS_EMM_IsSuspended()))
        {
            /* 去激活ISR */
            NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);
        }
        pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

        NAS_LMM_MEM_CPY_S(  astPsBearerCtx,
                            sizeof(astPsBearerCtx),
                            pstPsBearerCtx,
                            sizeof(astPsBearerCtx));

        /*更新所有承载的ISR标识为NONE*/
        NAS_EMM_UpdateBearISRFlag(astPsBearerCtx);

        NAS_LMM_MEM_CPY_S(  pstPsBearerCtx,
                            sizeof(astPsBearerCtx),
                            astPsBearerCtx,
                            sizeof(astPsBearerCtx));

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);

        return ;
    }
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:NORM REGED AND EMC BEARER");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL5);
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq:state:",NAS_LMM_GetEmmInfoRegStatus());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq_ENUM,LNAS_EMM_REG_STATE,
                                        NAS_LMM_GetEmmInfoRegStatus());

    /* 如果有紧急承载，且承载数大于1，则更新状态为正常注册且有紧急承载 */
    /* 如果状态从正常注册变为正常注册且有紧急承载，则给MMC发送
       LMM_MMC_EMC_BEARER_STATUS_NOTIFY消息，指示紧急承载建立 */
    if (NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
    {
        NAS_EMM_SendMmcEmcBearerStatusNotify(VOS_TRUE);
    }

    NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR);

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq
 Description     : 处理ESM的消息ID_EMM_ESM_BEARER_STATUS_REQ
 Input           : Pointer of EMM_ESM_BEARER_STATUS_REQ_STRU
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-4-22  Draft Enact
    2.H41410       2010-10-18  POP全部栈
    3.Z00148421    2011-1-11  DTS2010122201496
    4.S00193151    2014-06-24 Mod: 承载数目为0时本地DETACH的处理
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq( VOS_VOID *pstMsg )
{
    VOS_UINT32                          ulRes = NAS_LMM_MSG_HANDLED;
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstEsmBearerStatusReq   = VOS_NULL_PTR;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq_ENUM,LNAS_ENTRY);

    /* 参数检查*/
    if (NAS_EMM_NULL_PTR == pstMsg)
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq: NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_FAIL;
    }
    pstEsmBearerStatusReq               =(EMM_ESM_BEARER_STATUS_REQ_STRU *)(pstMsg);

    /* 挂起过程中或从模收到的，设置承载发生变更直接返回，MML公共维护的承载上下文全局变量不做修改，由主模进行维护 */
    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        /* CL:L从模，X模主模，L模更新承载状态；GUL:L从模，GU模主模，GU模更新承载状态
           LMM记录承载状态的全局变量:NAS_MML_GetPsBearerCtx() */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if((LRRC_LNAS_RAT_PRIO_NULL != NAS_LMM_GetCurCdma1xPrio())
            ||(LRRC_LNAS_RAT_PRIO_NULL != NAS_LMM_GetCurHrpdPrio()))
        {
            /* 更新EMM本地维护的承载上下文*/
            NAS_EMM_UpdateEpsBearStatus((VOS_VOID*)pstEsmBearerStatusReq);
        }
#endif
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq: LTE CUR SUSPEND");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* L主模  */

    /* 更新EMM本地维护的承载上下文*/
    NAS_EMM_UpdateEpsBearStatus((VOS_VOID*)pstEsmBearerStatusReq);

    /* 更新注册状态 */
    NAS_EMM_UpdateRegStatusWhenEsmBearStatusReq(pstEsmBearerStatusReq);

    /* 承载数为0，统一在此处理 */
    if (0 == pstEsmBearerStatusReq->ulEpsIdNum)
    {
        /*c00285307 add for DTS2015051204816 begin
         链路释放优化后，已没有链路释放过程中这个状态，因此不会压栈，此时如果处于DEREG态则说明本地已DETACH完全，需要等待RRC链路释放，
         因此不能将定时器停止，也不需要出栈处理*/
        if (EMM_MS_DEREG != NAS_LMM_GetEmmCurFsmMS())
        {
            NAS_LMM_EstingOrReleasingProcessTimerHandle();

            /* 判读状态是否需要出栈*/
            NAS_LMM_IfEmmHasBeenPushedThenPop();

            ulRes = NAS_EMM_MsAnyStateSsAnySateProcMsgEsmStatusReq();
            return ulRes;
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /* 承载数不为0，且L是主模，判断本次承载变化如果是ESM本地执行，
       则消息进入状态机继续处理，否则流程结束 */
    if (EMM_ESM_BEARER_CNTXT_MOD_LOCAL == pstEsmBearerStatusReq->enBearerCntxtMod)
    {
        return NAS_LMM_MSG_DISCARD;
    }
    else
    {
        return NAS_LMM_MSG_HANDLED;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndAttachReqFailProc
 Description     : ATTACH REQ发送失败时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndAttachReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;

    enMainState                         = NAS_LMM_GetEmmCurFsmMS();

    *pulIsDelBuff = VOS_TRUE;

    /*检查状态是否匹配，若不匹配，退出*/
    if (EMM_MS_REG_INIT != enMainState)
    {
        /*打印出错信息*/
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndAttachReqFailProc: STATE ERR!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachReqFailProc_ENUM,LNAS_ERROR);
        return  NAS_EMM_SUCC;
    }
    /* 大数据: 更新attach REQ DATA REQ发送失败次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
        #if (FEATURE_ON == FEATURE_DSDS)
        case LRRC_LMM_SEND_RSLT_NO_RF:
        #endif
            /* 重启ATTACH流程 */
            /*停止定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);

            if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
            {
                NAS_EMM_StartEmergencyAttach();

                return  NAS_EMM_SUCC;
            }

            if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            {
                /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
                NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
            }
            else
            {
                /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
            }

            /* 状态迁移Dereg.Normal_Service，发送INTRA_ATTACH_REQ消息*/
            NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            (VOS_VOID)NAS_EMM_SendIntraAttachReq();

            break;

        default:
            break;
        }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendEsmDataCnf
 Description     : 对ESM data req的回复
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         : lifuxin  00253982   2014-07-08  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_ENUM_UINT32 enDataCnfRst, VOS_UINT32 ulEsmEmmOpId)
{
    EMM_ESM_DATA_CNF_STRU               *pstEmmEsmDataCnf = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendEsmDataCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendEsmDataCnf_ENUM,LNAS_ENTRY);

    /*申请消息内存*/
    pstEmmEsmDataCnf   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_DATA_CNF_STRU));
    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pstEmmEsmDataCnf)
    {
        return;
    }

    /*构造ID_EMM_ESM_DATA_CNF消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pstEmmEsmDataCnf,
                                   (sizeof(EMM_ESM_DATA_CNF_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pstEmmEsmDataCnf->ulMsgId  = ID_EMM_ESM_DATA_CNF;

    /*填充消息OPID*/
    pstEmmEsmDataCnf->ulEsmEmmOpId = ulEsmEmmOpId;

    pstEmmEsmDataCnf->enDataCnfRst = enDataCnfRst;

    /*向ESM发送ID_EMM_ESM_DATA_CNF消息*/
    NAS_LMM_SEND_MSG(pstEmmEsmDataCnf);
}


/*****************************************************************************
 Function Name   : NAS_EMM_RcvLrrcEsmDataCnfHandle
 Description     : 对ESM data req的回复
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         : lifuxin  00253982   2014-07-02  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_RcvLrrcEsmDataCnfHandle(const LRRC_LMM_DATA_CNF_STRU  *pstRrcMmDataCnf, VOS_UINT32 ulEsmEmmOpId)
{
    EMM_ESM_SEND_RSLT_ENUM_UINT32       enEmmEsmDataCnfRst = EMM_ESM_SEND_RSLT_BUTT;
    VOS_UINT32                          ulLoop = 0;
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RcvLrrcEsmDataCnfHandle is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLrrcEsmDataCnfHandle_ENUM,LNAS_ENTRY);

    /*检查入参*/
    if(VOS_NULL == pstRrcMmDataCnf)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_RcvLrrcEsmDataCnfHandle(ERR): Input is NULL!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RcvLrrcEsmDataCnfHandle_ENUM,LNAS_NULL_PTR);
        return;
    }

    for(ulLoop = 0; ulLoop < g_ulEmmEsmDataCnfTblLen; ulLoop++)
    {
        if(g_astEmmEsmDataCnfTbl[ulLoop].enSendRslt == pstRrcMmDataCnf->enSendRslt)
        {
            enEmmEsmDataCnfRst = g_astEmmEsmDataCnfTbl[ulLoop].enEmmEsmDataCnfRst;
            break;
        }
    }

    /*给ESM发送data cnf消息*/
    if(EMM_ESM_SEND_RSLT_BUTT != enEmmEsmDataCnfRst)
    {
        NAS_EMM_SendEsmDataCnf(enEmmEsmDataCnfRst, ulEsmEmmOpId);
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndEsmMsgSuccProc
 Description     : 对ESM data req回复成功的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         : lifuxin  00253982   2014-07-03  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_SndEsmMsgSuccProc(VOS_VOID* pMsg)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = NAS_EMM_NULL_PTR;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);
    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    NAS_EMM_RcvLrrcEsmDataCnfHandle(pstRrcMmDataCnf, pEmmMrrcMgmtData->ulEsmMmOpId);
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndEsmMsgFailProc
 Description     : ESM消息发送失败时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndEsmMsgFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    VOS_UINT32                            ulRrcMmDataReqMsgLen;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    /* 从当前状态机中获取状态 */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();
    enSubState                          = NAS_LMM_GetEmmCurFsmSS();

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }
    NAS_EMM_RcvLrrcEsmDataCnfHandle(pstRrcMmDataCnf, pEmmMrrcMgmtData->ulEsmMmOpId);

    ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                           pEmmMrrcMgmtData->ulNasMsgLength) -
                           NAS_EMM_4BYTES_LEN;
    /* 申请消息内存*/
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);

    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SndEsmMsgFailProc: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndEsmMsgFailProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            if ((EMM_MS_REG_INIT == enMainState)
                || (EMM_MS_TAU_INIT == enMainState)
                || ((EMM_MS_REG == enMainState)
                    && ((EMM_SS_REG_NORMAL_SERVICE == enSubState)
                        || (EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == enSubState)
                        || (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == enSubState))))
            {
                pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

                pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_ESM;
                pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
                pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

                pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

                NAS_LMM_MEM_CPY_S(  pMrrcDataMsg->stNasMsg.aucNasMsg,
                                    pEmmMrrcMgmtData->ulNasMsgLength,
                                    pEmmMrrcMgmtData->aucNasMsgContent,
                                    pEmmMrrcMgmtData->ulNasMsgLength);

                NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);
            }
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

        default:
            break;
    }

    /*释放所申请内存 */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
    return NAS_EMM_SUCC;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_RestartAttProcedural
 Description     : 重启ATTACH流程
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_RestartAttProcedural(VOS_VOID)
{
    /* 重启ATTACH流程 */
    /* 停止定时器TI_NAS_EMM_T3410 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_StartEmergencyAttach();

        return;
    }

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /* 状态迁移Dereg.Normal_Service，发送INTRA_ATTACH_REQ消息*/
    NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                            EMM_SS_DEREG_NORMAL_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

    /*发送ATTACH REQ内部消息给ATTACH模块*/
    (VOS_VOID)NAS_EMM_SendIntraAttachReq();

    return ;
}



/*****************************************************************************
 Function Name   : NAS_EMM_EsmDataReqRetranSndUplink
 Description     : 重新发送ESM DATA空口消息的处理:直接发上行
 Input           : VOS_UINT32 - 消息的OPID
 Output          : None
 Return          : VOS_VOID

 History         : chengmin  00285307   2015-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_EsmDataReqRetranSndUplink(VOS_UINT32 ulOpid)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    /* 根据OPID获取缓存中消息 */
    pEmmMrrcMgmtData                    = NAS_EMM_FindMsgInDataReqBuffer(ulOpid);
    if(VOS_NULL_PTR == pEmmMrrcMgmtData)
    {
        return;
    }

    /* 消息长度 */
    ulRrcMmDataReqMsgLen                = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                            pEmmMrrcMgmtData->ulNasMsgLength) -
                                            NAS_EMM_4BYTES_LEN;

    /* 申请消息内存 */
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);
    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        return;
    }

    /* 对消息内存赋值 */
    pMrrcDataMsg->enDataCnf             = LRRC_LMM_DATA_CNF_NEED;
    pMrrcDataMsg->enEmmMsgType          = NAS_EMM_MSG_ESM;
    pMrrcDataMsg->ulMsgId               = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pMrrcDataMsg->ulEsmMmOpId           = pEmmMrrcMgmtData->ulEsmMmOpId;
    pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

    NAS_LMM_MEM_CPY_S(  pMrrcDataMsg->stNasMsg.aucNasMsg,
                        pEmmMrrcMgmtData->ulNasMsgLength,
                        pEmmMrrcMgmtData->aucNasMsgContent,
                        pEmmMrrcMgmtData->ulNasMsgLength);


    /* 重新发送上行直传 */
    NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);

    /* 释放所申请内存 */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
}

/*****************************************************************************
 Function Name   : NAS_EMM_EsmDataReqRetranSndService
 Description     : 重新发送ESM DATA空口消息的处理:先将消息缓存至ESMbuffer，再发serivce
 Input           : VOS_UINT32 - 消息的OPID
 Output          : None
 Return          : VOS_VOID

 History         : chengmin  00285307   2015-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_EsmDataReqRetranSndService(VOS_UINT32 ulOpid)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData;
    VOS_UINT32                          ulEmmEsmDataReqLen;
    EMM_ESM_DATA_REQ_STRU              *pstEmmEsmDataReq = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_EsmDataReqRetranSndService enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EsmDataReqRetranSndService_ENUM,LNAS_ENTRY);

    /* 根据OPID获取缓存中消息 */
    pEmmMrrcMgmtData                    = NAS_EMM_FindMsgInDataReqBuffer(ulOpid);
    if(VOS_NULL_PTR == pEmmMrrcMgmtData)
    {
        return;
    }

    ulEmmEsmDataReqLen                  = (sizeof(EMM_ESM_DATA_REQ_STRU)+
                                            pEmmMrrcMgmtData->ulNasMsgLength) -
                                            NAS_EMM_4BYTES_LEN;

    /* 申请消息内存 */
    pstEmmEsmDataReq = (EMM_ESM_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulEmmEsmDataReqLen);
    if(VOS_NULL_PTR == pstEmmEsmDataReq)
    {
        return;
    }

    /* 赋值参数 */
    pstEmmEsmDataReq->ulLength                    = ulEmmEsmDataReqLen - 20;
    pstEmmEsmDataReq->ulMsgId                     = ID_EMM_ESM_DATA_REQ;
    pstEmmEsmDataReq->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstEmmEsmDataReq->ulSenderPid                 = PS_PID_ESM;
    pstEmmEsmDataReq->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstEmmEsmDataReq->ulReceiverPid               = PS_PID_MM;
    pstEmmEsmDataReq->ulIsEmcType                 = pEmmMrrcMgmtData->ulIsEsmMsgEmcType;
    pstEmmEsmDataReq->ulOpId                      = pEmmMrrcMgmtData->ulEsmMmOpId;
    pstEmmEsmDataReq->stEsmMsg.ulEsmMsgSize       = pEmmMrrcMgmtData->ulNasMsgLength;

    NAS_LMM_MEM_CPY_S(  pstEmmEsmDataReq->stEsmMsg.aucEsmMsg,
                        pEmmMrrcMgmtData->ulNasMsgLength,
                        pEmmMrrcMgmtData->aucNasMsgContent,
                        pEmmMrrcMgmtData->ulNasMsgLength);

    NAS_EMM_PUBU_LOG2_INFO( "NAS_EMM_EsmDataReqRetranSndService isEmcType,esmmmopid:",
                            pstEmmEsmDataReq->ulIsEmcType,
                            pstEmmEsmDataReq->ulOpId);
    TLPS_PRINT2LAYER_INFO2( NAS_EMM_EsmDataReqRetranSndService_ENUM,
                            LNAS_FUNCTION_LABEL1,
                            pstEmmEsmDataReq->ulIsEmcType,
                            pstEmmEsmDataReq->ulOpId);


    /* 设置SERVICE触发原因值 */
    if (VOS_TRUE == pstEmmEsmDataReq->ulIsEmcType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC);

        /* 缓存紧急类型的ESM消息 */
        NAS_EMM_SaveEmcEsmMsg(pstEmmEsmDataReq);
    }
    else
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ);
    }

    /* 大数据:　清Mt Ser Flag */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*SER模块自行缓存ESM DATA消息*/
    NAS_EMM_SER_SaveEsmMsg(pstEmmEsmDataReq);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    /* 释放所申请内存 */
    NAS_LMM_MEM_FREE(pstEmmEsmDataReq);

}


/*****************************************************************************
 Function Name   : NAS_EMM_EsmDataReqRetranProc
 Description     : 重新发送ESM DATA空口消息
 Input           : VOS_UINT32 - 消息的OPID
 Output          : None
 Return          : VOS_VOID

 History         : chengmin  00285307   2015-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_EsmDataReqRetranProc(VOS_UINT32 ulOpid)
{
    /* 如果是信令连接态或数据连接态，直接发 */
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        /* 重新发送上行直传 */
        NAS_EMM_EsmDataReqRetranSndUplink(ulOpid);
        return;
    }

    /* IDLE态需要先发SERVICE */
    NAS_EMM_EsmDataReqRetranSndService(ulOpid);

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

