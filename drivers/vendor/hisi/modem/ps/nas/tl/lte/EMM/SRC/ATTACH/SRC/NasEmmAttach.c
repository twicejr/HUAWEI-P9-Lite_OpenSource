


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasMmlCtx.h"
#include "ImsaLmmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACH_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACH_C
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
NAS_EMM_ATTACH_CTRL_STRU                g_stEmmAttCtrl;

/*****************************************************************************
  3 Function
*****************************************************************************/


/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_AttachInit()
{
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AttachInit                START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AttachInit_ENUM,LNAS_BEGIN);

    /* 初始化ATTACH全局变量 */
    NAS_LMM_MEM_SET_S(&g_stEmmAttCtrl, sizeof(g_stEmmAttCtrl), 0, sizeof(g_stEmmAttCtrl));
    /*NAS_EMM_GLO_AD_GetAttRst()          = EMM_ATTACH_RST_PS;*/
    /*NAS_EMM_GLO_AD_GetAttType()         = MMC_LMM_ATT_TYPE_EPS_ONLY;*/

    return;
}


VOS_VOID  NAS_EMM_FreeAttDyn( VOS_VOID )
{
    /*暂时无操作*/

    return;
}


VOS_VOID     NAS_EMM_Attach_ClearResourse(VOS_VOID)
{

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_Attach_ClearResourse is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_Attach_ClearResourse_ENUM,LNAS_ENTRY);

    /*动态内存释放*/
    /*lint -e522*/
    NAS_EMM_FreeAttDyn();
    /*lint +e522*/

    /* 停止ATTACH定时器 */
    NAS_LMM_Stop3402Timer();
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*赋初值*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GLO_AD_GetAttCtrlAddr(),
                        sizeof(NAS_EMM_ATTACH_CTRL_STRU),
                        0,
                        sizeof(NAS_EMM_ATTACH_CTRL_STRU));

    /*NAS_EMM_GLO_AD_GetAttRst()          = EMM_ATTACH_RST_PS;*/

    /*NAS_EMM_GLO_AD_GetAttType()         = MMC_LMM_ATT_TYPE_EPS_ONLY;*/
    NAS_EMM_SetAttType();

    return;
}

/*****************************************************************************
 Function Name   :  NAS_EMM_Attach_SuspendInitClearResourse
 Description     :  在挂起时清理ATTACH资源
 Input           :

 Return          :

 History         :
    1.FTY         2012-02-21  Draft Enact

*****************************************************************************/
VOS_VOID     NAS_EMM_Attach_SuspendInitClearResourse(VOS_VOID)
{

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_Attach_SuspendInitClearResourse is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_Attach_SuspendInitClearResourse_ENUM,LNAS_ENTRY);

    /*动态内存释放*/
    /*lint -e522*/
    NAS_EMM_FreeAttDyn();
    /*lint +e522*/

    /* 停止ATTACH定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_Attach_SuspendInitClearResourse is entered: send mmc attach fail");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Attach_SuspendInitClearResourse_ENUM,LNAS_FAIL);

        NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
    }

    /*赋初值*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GLO_AD_GetAttCtrlAddr(),
                        sizeof(NAS_EMM_ATTACH_CTRL_STRU),
                        0,
                        sizeof(NAS_EMM_ATTACH_CTRL_STRU));

    /*NAS_EMM_GLO_AD_GetAttRst()          = EMM_ATTACH_RST_PS;*/

    /*NAS_EMM_GLO_AD_GetAttType()         = MMC_LMM_ATT_TYPE_EPS_ONLY;*/
    NAS_EMM_SetAttType();

    return;
}


/*****************************************************************************
 Function Name   :  NAS_EMM_SendrrcLmmCleBuffNotifyInd
 Description     :  在REG_INIT+WAIT_DATA_CNF状态下TA发生变化，通知RRC清缓存
 Input           :

 Return          :

 History         :
    1.wangchen 00209181         2012-05-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendRrcClearBuffNotify(VOS_VOID )
{
    LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU           *pstCleBuffNotifyIndMsg;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM(            "NAS_EMM_SendRrcClearBuffNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendRrcClearBuffNotify_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pstCleBuffNotifyIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU));
    if (NAS_LMM_NULL_PTR == pstCleBuffNotifyIndMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstCleBuffNotifyIndMsg,
                        sizeof(LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU),
                        0,
                        sizeof(LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstCleBuffNotifyIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU));

    /* 填充消息ID */
    pstCleBuffNotifyIndMsg->enMsgId        = ID_LRRC_LMM_CLEAR_BUFF_NOTIFY;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstCleBuffNotifyIndMsg);

    return;
}





VOS_VOID  NAS_EMM_AdStateConvert(NAS_EMM_MAIN_STATE_ENUM_UINT16 ucMs,
                                   NAS_EMM_SUB_STATE_ENUM_UINT16 ucSs,
                                   NAS_EMM_STATE_TI_ENUM_UINT16 ucStaTId)
{
    NAS_EMM_FSM_STATE_STRU              stDestState;

    stDestState.enFsmId                 = NAS_LMM_PARALLEL_FSM_EMM;
    stDestState.enMainState             = ucMs;
    stDestState.enSubState              = ucSs;
    stDestState.enStaTId                = ucStaTId;
    NAS_LMM_StaTransProc(stDestState);

}


VOS_VOID    NAS_EMM_EsmSendRelInd()
{
    EMM_ESM_REL_IND_STRU                 *pEmmEsmRelIndMsg;


    /*申请消息内存*/
    pEmmEsmRelIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_REL_IND_STRU));

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmRelIndMsg)
    {
        return;
    }

    /*构造ID_EMM_ESM_REL_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(      pEmmEsmRelIndMsg,
                                        (sizeof(EMM_ESM_REL_IND_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pEmmEsmRelIndMsg->ulMsgId            = ID_EMM_ESM_REL_IND;

    /*向ESM发送ID_EMM_ESM_REL_IND消息*/
    NAS_LMM_SEND_MSG(                   pEmmEsmRelIndMsg);

    return;


}


VOS_UINT32  NAS_EMM_IntraAttReqChk(const NAS_LMM_INTRA_ATTACH_REQ_STRU* pMsgMsg)
{
    /*消息内容检查*/
    if (ID_NAS_LMM_INTRA_ATTACH_REQ == pMsgMsg->ulMsgId)
    {
        return  NAS_EMM_PARA_VALID;

    }
    else
    {
        return  NAS_EMM_PARA_INVALID;

    }
}





VOS_VOID    NAS_EMM_AtmpCntLess5Proc()
{
    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_AtmpCntLess5Proc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AtmpCntLess5Proc_ENUM,LNAS_ENTRY);

    /*启动定时器T3411*/
    NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

}


VOS_VOID    NAS_EMM_AtmpCntEqual5Proc()
{

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_AtmpCntEqual5Proc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AtmpCntEqual5Proc_ENUM,LNAS_ENTRY);

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置update status为EU2*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /*删除GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
    /*启动定时器T3402*/
    NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

    /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                        TI_NAS_EMM_STATE_NO_TIMER);


}


VOS_VOID    NAS_EMM_AttSendEsmResult( EMM_ESM_ATTACH_STATUS_ENUM_UINT32 attStatus )
{
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_AttSendEsmResult is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AttSendEsmResult_ENUM,LNAS_ENTRY);

    /*判断触发原因*/
    if (EMM_ATTACH_CAUSE_ESM == NAS_EMM_GLO_AD_GetAttCau())
    {
        /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
        NAS_EMM_EsmSendEstCnf(          attStatus);

        if (EMM_ESM_ATTACH_STATUS_DETACHED == attStatus)
        {
            /*clear global:EpsContextStatusChange*/
            NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
        }
    }
    else
    {
        /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
        NAS_EMM_EsmSendStatResult(      attStatus);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateCnAttTypeOfUserReq
 Description     : 根据用户请求类型设置触发的ATTACH类型
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-5-8      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_UpdateCnAttTypeOfUserReq( VOS_VOID )
{
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_UpdateCnAttTypeOfUserReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateCnAttTypeOfUserReq_ENUM,LNAS_ENTRY);

    /* 判断是否被原因值2拒绝过 */
    if (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
        return ;
    }

    /* 判断是否被原因值18拒绝过 */
    if (NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag())
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
        return ;
    }

    /*用户下发CS_ONLY,但UE模式为PS1,PS2或CS/PS1,CS/PS2,在收到用户请求消息时会回复，
    此处不考虑*/
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == NAS_EMM_GLO_GetAttReqType())
        {
            NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
            return;
        }
        if ((MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType()) &&
            (NAS_EMM_YES== NAS_EMM_IsCsPsUeMode()))
        {

            NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI);
        }
        else
        {
            NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
        }
    }
    else
    {
        /*L单模下,操作模式CS+PS，用户下发PS_ONLY或CS+PS且CS允许注册,触发联合ATTACH,
        其他情况触发PS ATTACH*/
        if((NAS_EMM_YES== NAS_EMM_IsCsPsUeMode()) &&
            (NAS_EMM_AUTO_ATTACH_ALLOW == NAS_EMM_GetCsAttachAllowFlg()))
        {
            NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI);

        }
        else
        {
            NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);

        }
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateCnAttTypeOfNotUserReq
 Description     : 设置自动触发的ATTACH类型
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-5-8      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_UpdateCnAttTypeOfNotUserReq( VOS_VOID )
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_UpdateCnAttTypeOfNotUserReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateCnAttTypeOfNotUserReq_ENUM,LNAS_ENTRY);

    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();

    /* 判断是否被原因值2拒绝过 */
    if (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
        return ;
    }

    /* 判断是否被原因值18拒绝过 */
    if (NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag())
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
        return ;
    }
     /* 判断是否允许CS域注册 */
    if (NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetCsAttachAllowFlg())
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
        return ;
    }
    if ((NAS_LMM_UE_CS_PS_MODE_1 == ulLteUeMode) ||
        (NAS_LMM_UE_CS_PS_MODE_2 == ulLteUeMode))
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI);
    }
    else
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_ONLY);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SetAttType
 Description     : 设置触发的ATTACH类型
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-5      Draft Enact
    2.lihong 00150010     2011-09-28    Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_SetAttType( VOS_VOID )
{
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_SetAttType is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetAttType_ENUM,LNAS_ENTRY);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_GLO_SetCnAttReqType(MMC_LMM_ATT_TYPE_EPS_EMERGENCY);
        return ;
    }

    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        NAS_EMM_UpdateCnAttTypeOfUserReq();
    }
    else
    {
        NAS_EMM_UpdateCnAttTypeOfNotUserReq();
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SetUeUsageSetting
 Description     : 设置UE的usage setting
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SetUeUsageSetting (VOS_VOID )
{
    NAS_EMM_ATTACH_LOG1_INFO("NAS_EMM_SetUeUsageSetting: ",
                             NAS_EMM_GLO_AD_GetUsgSetting());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetUeUsageSetting_ENUM,LNAS_EMM_UE_USG_SETTING,NAS_EMM_GLO_AD_GetUsgSetting());

    /* 第一阶段，只支持数据中心，开机时已经赋初值，此处不再变化 */

    /* H41410 FOR UE MODE  */
    /*
    if ((NAS_LMM_UE_CS_PS_MODE_1 == NAS_LMM_GetEmmInfoUeOperationMode()) ||
        (NAS_LMM_UE_PS_MODE_1 == NAS_LMM_GetEmmInfoUeOperationMode()))
    {
        NAS_EMM_GLO_AD_SetUsgSetting(EMM_SETTING_VOICE_CENTRIC);
    }
    else
    {
        NAS_EMM_GLO_AD_SetUsgSetting(EMM_SETTING_DATA_CENTRIC);
    }
    */
    /* H41410 FOR UE MODE  */
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetCsService
 Description     : 获取UE的CS域服务类型
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-6      Draft Enact
    2.lihong 00150010     2012-02-27    Modify : CSFB

*****************************************************************************/
VOS_UINT32  NAS_EMM_GetCsService (VOS_VOID )
{
    NAS_EMM_PUB_INFO_STRU                  *pstPubInfo      = VOS_NULL_PTR;
    NAS_LMM_CS_SERVICE_ENUM_UINT32          ulCsService     = NAS_LMM_CS_SERVICE_BUTT;

    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8   enCsServiceCfg  = NAS_MML_LTE_SUPPORT_BUTT;
    enCsServiceCfg  = NAS_EMM_GetLteCsServiceCfg();
    NAS_EMM_ATTACH_LOG1_INFO("MML CS SERVICE: ", enCsServiceCfg);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GetCsService_ENUM,LNAS_EMM_CSSERVICECFG,enCsServiceCfg);

    pstPubInfo      = NAS_LMM_GetEmmInfoAddr();

    if (NAS_MML_LTE_SUPPORT_BUTT != enCsServiceCfg)
    {
        pstPubInfo->bitOpCsService  = NAS_EMM_BIT_SLCT;

        pstPubInfo->ulCsService     = enCsServiceCfg;
        /*pstPubInfo->ulCsService = NAS_LMM_ChangeCsServiceMmlToLmm(enCsServiceCfg);*/
    }
    else
    {
        pstPubInfo->bitOpCsService = NAS_EMM_BIT_NO_SLCT;
    }

    if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpCsService)
    {

        ulCsService = pstPubInfo->ulCsService;
    }

    return ulCsService;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetVoiceDomain
 Description     : 获取UE的VOICE DOMAIN
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_GetVoiceDomain(VOS_VOID )
{
    NAS_EMM_PUB_INFO_STRU               *pstPubInfo;
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32    ulVoiceDomain = NAS_LMM_VOICE_DOMAIN_BUTT;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
    {

        ulVoiceDomain = pstPubInfo->ulVoiceDomain;
    }

    return ulVoiceDomain;
}


/*****************************************************************************
 Function Name   : NAS_EMM_GetSuppSrvccToGU
 Description     : 获取支持SRVCC to GU
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_GetSuppSrvccToGU(VOS_VOID )
{
    NAS_EMM_PUB_INFO_STRU               *pstPubInfo;
    NAS_EMM_MS_NET_CAP_STRU             *pstMsNetCap;
    VOS_UINT32                          ulRslt = NAS_EMM_BIT_NO_SLCT;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pstMsNetCap = NAS_LMM_GetEmmInfoMsNetCapAddr();
    if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpMsNetCap)
    {
        if (NAS_EMM_BIT_SLCT == ((pstMsNetCap->aucMsNetCap[2] >> NAS_EMM_AD_MOVEMENT_3_BITS)
                                    & NAS_EMM_LOW_1_BITS_F))
        {
            ulRslt = NAS_EMM_BIT_SLCT;
        }

    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcCause161722TauAttemptCont
 Description     : ATTACH成功，EPS ONLY，原因值为16,17,22时，或者
                   TAU成功，TA UPDATED ONLY，原因值为16,17,22时，
                   根据TAU ATTEMPTIMG UPDATE COUNTER值进行处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcCause161722TauAttemptCont(VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU                               *pstEsmMsg = NAS_EMM_NULL_PTR;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_ProcCause161722TauAttemptCont is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcCause161722TauAttemptCont_ENUM,LNAS_ENTRY);

    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();

    if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        /*启动定时器TI_NAS_EMM_PTL_T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

        /*修改状态：进入主状态REG子状态ATTACH_WAIT_ESM_BEARER_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*ATTACH完成向MMC发送ATTACH成功*/
        NAS_EMM_AppSendAttSucc();

        pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
        if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            && (NAS_EMM_NULL_PTR != pstEsmMsg))
        {
            /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
            NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_OTHER;
            NAS_EMM_ClearEmcEsmMsg();
        }
    }
    else
    {
        if (NAS_LMM_UE_CS_PS_MODE_1 == ulLteUeMode)
        {
            NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_TRUE);
        }
        else if (NAS_LMM_UE_CS_PS_MODE_2 == ulLteUeMode)
        {
            NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);
        }
        else
        {
        }

        /*修改状态：进入主状态REG子状态EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                    TI_NAS_EMM_PTL_T3402);

        /*ATTACH完成向MMC发送ATTACH成功*/
        NAS_EMM_AppSendAttSucc();
        /* 识别EPS ONLY,原因值为16,17,22 disable L模的场景,释放链路 */
        /*NAS_EMM_RecogAndProc161722Disable(NAS_EMM_GLO_AD_GetEmmCau());*/
        /*NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);*/
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SetAttachRegDomain
 Description     : ATTACH成功时设置注册域
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SetAttachRegDomain( VOS_VOID )
{
    if (EMM_ATTACH_RST_PS == NAS_EMM_GLO_AD_GetAttRslt())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    else
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRrcDataCnfEpsSuccOnly
 Description     : 收到RRC_MM_DATA_CNF后且结果为EPS ONLY成功的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-09-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRrcDataCnfEpsSuccOnly( VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    if (NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS == NAS_EMM_GLO_AD_GetEmmCau())
    {
        /* 记录UE被原因值2拒绝过，之后不再发起联合ATTACH和联合TAU，直到关机或者拔卡 */
        NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

        /*修改状态：进入主状态REG子状态REG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*ATTACH完成向MMC发送ATTACH成功*/
        NAS_EMM_AppSendAttSucc();

        pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
        if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            && (NAS_EMM_NULL_PTR != pstEsmMsg))
        {
            /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
            NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_OTHER;
            NAS_EMM_ClearEmcEsmMsg();
        }

        return ;
    }


    if (NAS_LMM_CAUSE_CS_NOT_AVAIL == NAS_EMM_GLO_AD_GetEmmCau())
    {
        /*把当前PLMN加入到拒绝#18列表中*/
        NAS_EMMC_AddPlmnInRej18PlmnList(NAS_LMM_GetEmmInfoPresentPlmnAddr());

        /*设置拒绝18标识*/
        NAS_EMMC_SetRejCause18Flag(NAS_EMM_REJ_YES);

        /*修改状态：进入主状态REG子状态REG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*ATTACH完成向MMC发送ATTACH成功*/
        NAS_EMM_AppSendAttSucc();

        pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
        if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            && (NAS_EMM_NULL_PTR != pstEsmMsg))
        {
            /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
            NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_OTHER;
            NAS_EMM_ClearEmcEsmMsg();
        }

        /* 识别EPS ONLY,原因值为18 disable L模的场景,释放链路 */
        /*NAS_EMM_RecogAndProc18Disable(NAS_EMM_GLO_AD_GetAttRejCau());*/
        return;

    }

    NAS_EMM_ProcCause161722TauAttemptCont();

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_AttProcT3410Exp
 Description     : 连接释放T3410超时后的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470      2011-12-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_AttProcT3410Exp( VOS_VOID )
{
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        NAS_EMM_AtmpCntLess5Proc();
        NAS_EMM_AppSendAttTimerExp();
    }
    else
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
        /*启动定时器T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);



        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /* 注意必须先上报结果再清除attach attempt counter */
        NAS_EMM_AppSendAttTimerExp();
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_AttProcEpsOnlyRejValueOther
 Description     : EPS_only其它原因值的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470      2011-12-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_AttProcEpsOnlyRejValueOther( VOS_VOID )
{
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        NAS_EMM_AtmpCntLess5Proc();
        NAS_EMM_AppSendAttRejEpsOnly();
    }
    else
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
        /*启动定时器T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);



        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /* 注意必须先上报结果再清除attach attempt counter */
        NAS_EMM_AppSendAttRejEpsOnly();

        /*重设attach attempt counter*/
        /*NAS_EMM_GLO_AD_GetAttAtmpCnt()      = 0;*/
    }

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq( NAS_LMM_NOT_BARRED);
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauOtherAbnormal
 Description     : EPS_only其它原因值非#95 #96...的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470      2011-12-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRejCauOtherAbnormal( VOS_VOID )
{
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        NAS_EMM_AtmpCntLess5Proc();
        /* 参照标杆实现，在ATTACH被其他原因值拒绝，尝试次数小于5时，将有效安全上下文写卡 */
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
        NAS_EMM_AppSendAttRej();
    }
    else
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
        /*启动定时器T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);



        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /* 注意必须先上报结果再清除attach attempt counter */
        NAS_EMM_AppSendAttRej();

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_AD_Reattach
 Description     : 重新发起ATTACH流程
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-12-16  Draft Enact
    2.X00148705                 2010-01-26  不需要相APP上报

*****************************************************************************/
VOS_VOID  NAS_EMM_AD_Reattach(VOS_VOID )
{
    NAS_EMM_ATTACH_LOG_INFO(            "NAS_EMM_AD_Reattach entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AD_Reattach_ENUM,LNAS_ENTRY);

    /*通知ESM*/
    NAS_EMM_AttSendEsmResult(           EMM_ESM_ATTACH_STATUS_DETACHED);

    /*重新ATTACH*/
    /*NAS_EMM_EsmSendPdnConnInd(          NAS_EMM_GLO_AD_GetDefBeaId());*/
    NAS_EMM_EsmSendPdnConnInd(          0);
    NAS_LMM_StartStateTimer(             TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
   return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_Attach_IsTimerRunning
 Description     : 判断3411和3402定时器是否在运行
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY         2012-02-24  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_Attach_IsTimerRunning(VOS_VOID )
{
    /* T3411在运行，不向MMC发ATTACH结果*/
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_Attach_IsTimerRunning: T3411 is running.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_Attach_IsTimerRunning_ENUM,LNAS_EMM_T3411_RUNNING);

        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        return NAS_EMM_YES;
    }

    /* T3402运行，向MMC发ATTACH结果，触发MMC搜下一个网络*/
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
    {
         NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_Attach_IsTimerRunning: T3402 is running.");
         TLPS_PRINT2LAYER_WARNING(NAS_EMM_Attach_IsTimerRunning_ENUM,LNAS_EMM_T3402_RUNNING);

        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_T3402_RUNNING);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcAttachConnFailOtherCause
 Description     : 底层失败为其它原因值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470      2011-12-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcAttachConnFailOtherCause( VOS_VOID )
{
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        /*启动定时器T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        NAS_EMM_AppSendAttFailWithPara();

    }

    else
    {
        /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
        /*设置update status为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
        /*启动定时器T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

        /* 必须先转状态，再上报ATTACH结果，最后清除 attach attempt counter,
            顺序不能变 */

        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_AppSendAttFailWithPara();

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailBarredProc
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   收到 Intra_Connect_Fail_Ind,被BAR处理
 Input           : None
 Return          : VOS_VOID
 History         :
    1.lihong 00150010 2012.11.01 New Draft
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailBarredProc( VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;


    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailBarredProc: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailBarredProc_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_ACCESS_BAR);

        /*重设attach attempt counter，顺序必须在上报ATTACH结果之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return ;
    }

    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_ATTACH_NEEDED,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*向MMC发送ATTACH接入被bar*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_ACCESS_BAR);

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailCellSrchProc
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   收到 Intra_Connect_Fail_Ind,CELL SEARCH处理
 Input           : None
 Return          : VOS_VOID
 History         :
    1.lihong 00150010 2012.11.01 New Draft
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailCellSrchProc( VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailOthersProc: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailCellSrchProc_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在上报ATTACH结果之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* 状态迁移Dereg.Plmn_Search*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_PLMN_SEARCH,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        return ;
    }

    /* 通知ESM,APP注册失败*/
    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 状态迁移Dereg.Plmn_Search*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_PLMN_SEARCH,
                                TI_NAS_EMM_STATE_NO_TIMER);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
    #endif

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return ;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailOthersProc
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   收到 Intra_Connect_Fail_Ind,其他原因值处理
 Input           : None
 Return          : VOS_VOID
 History         :
    1.lihong 00150010 2012.11.01 New Draft
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailOthersProc( VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailOthersProc: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailOthersProc_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在上报ATTACH结果之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return ;
    }

    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_ProcAttachConnFailOtherCause();

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   收到 Intra_Connect_Fail_Ind

 Input           :
 Return          :
 History         :
    1.zhengjunyan 00148421 2009.03.17 New Draft
    2.zhengjunyan 00148421 2010-12-22 DTS2010111701490:添加建链失败原因值
                                      CELL_SEATCHING的处理
    3.zhengjunyan 00148421 2010-12-23 Mod:接入被Bar给App回复结果
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU         *pMrrcConnectFailInd = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd_ENUM,LNAS_ENTRY);

    /*check the current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

     /*check the input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd: NULL PTR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*stop T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

    /*get the msg*/
    pMrrcConnectFailInd = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)pMsgStru;

    /*process different with the est result*/
    switch(pMrrcConnectFailInd->enEstResult)
    {
        case LRRC_EST_ACCESS_BARRED_MO_SIGNAL:
        case LRRC_EST_ACCESS_BARRED_ALL:
            /* 大数据: 更新attach被bar次数 */
            NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_BAR);
            NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailBarredProc();
            break;

        /* 建链失败，RRC正在进行小区搜索*/
        case LRRC_EST_CELL_SEARCHING:
            /* 大数据: 更新attach EST Fail次数 */
            NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
            NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailCellSrchProc();
            break;

        default:
            /* 大数据: 更新attach EST Fail次数 */
            NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
            NAS_EMM_MsRegInitSsWtCnAttCnfIntraConnFailOthersProc();
            break;
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   收到 AUTH REJ,作为卡无效处理
 Input           :
 Return          :
 History         :
    1.zhengjunyan 00148421    2008-05-19  Draft Enact
    2.X00148705               2009-09-30  重构
    3.lihong00150010          2012-11-01  Modify:emgergency
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej(
                                                    VOS_UINT32  ulCause)
{
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulCause;

    /*停止定时器T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    NAS_EMM_AttDataUpdate(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
        NAS_EMM_SndEsmClearAllClBearerNotify();
    }

    /*修改状态：进入主状态DEREG子状态DEREG_NO_IMSI*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*向MMC发送LMM_MMC_ATTCH_CNF或LMM_MMC_ATTCH_IND消息*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_AUTH_REJ);

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return;
}


VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(VOS_UINT32 ulCause)
{
    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulCause);

    /*停止定时器T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在ATTACH结果上报之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        NAS_EMM_AdStateConvert(          EMM_MS_DEREG,
                                         EMM_SS_DEREG_PLMN_SEARCH,
                                         TI_NAS_EMM_STATE_NO_TIMER);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        return ;
    }

    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        /*启动定时器T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(          EMM_MS_DEREG,
                                         EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                         TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_AppSendAttFailWithPara();
    }

    else
    {
        /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
        /*设置update status为EU2*/
        /* leixiantiao 00258641v 2015-03-15 begin */
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
        /*启动定时器T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

        /* 必须先转状态，再上报结果，再清除 attach attempt counter */

        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_AppSendAttFailWithPara();
    }

    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthRej
 Description     : RegInit.WtAttCnf状态下收到AUTH REJ消息
 Input           :

 Return          :

 History         :
    1.zhengjunyan 00148421         2009-10-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthRej entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthRej_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 鉴权拒绝优化处理 */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);


    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgRrcRelInd
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   处理RRC_REL_IND
 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.X00148705              2009-09-25  对NAS_EMM_GLO_AD_GetAttAtmpCnt>5的情况做处理
    3.X00148705              2009-10-09  添加对AUTH REJ的处理或对REL_IND的处理

*****************************************************************************/

VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgRrcRelInd(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    LRRC_LMM_REL_IND_STRU     *pRrcRelInd =         (LRRC_LMM_REL_IND_STRU*)(pMsgStru);
    VOS_UINT32               ulCause;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgRrcRelInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgRrcRelInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;

    /*获得原因值*/
    ulCause                             =         pRrcRelInd->enRelCause;
    /* 大数据: 更新attach被Rel次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_AttachErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_LRRC_REL);
    #endif

    NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(ulCause);
    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmPdnRspMsgRrcRelInd
 Description     : RegInit.WtPdnRsp状态下收到RRC_REL_IND消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421    2010-11-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgRrcRelInd(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    LRRC_LMM_REL_IND_STRU                *pRrcRelInd = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    /*RRC_REL_IND消息预处理中判断了如果是IDLE态，则直接丢弃，所以这里一定是CONN*/

    /*CONN态,释放连接*/
    pRrcRelInd = (LRRC_LMM_REL_IND_STRU*)(pMsgStru);
    NAS_EMM_ATTACH_LOG1_INFO("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgRrcRelInd Cause:", pRrcRelInd->enMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgRrcRelInd_ENUM,LNAS_EMM_REL_CAUSE,pRrcRelInd->enMsgId);
    NAS_EMM_CommProcConn2Ilde();

    return  NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下，
                   收到T3410定时器超时

 Input           :
 Return          :
 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.X00148705              2009-09-19  去掉内部REL REQ消息，直接发RRC REL REQ

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp(VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru )
{

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_AttachErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_TIMEOUT);
    #endif

    /* 大数据: 更新attach 超时次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EXP);

    /*ATTACH尝试计数器加1*/
    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

    /* 收到定时器超时，将注册状态设置为T3410_EXP */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_T3410_EXP);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttTimerExp();

        /*重设attach attempt counter，顺序必须在上报ATTACH结果之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(       EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ATTACH结果*/
    NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_AttProcT3410Exp();

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAtmpToAttMsgT3411Exp
 Description     : 主状态DEREG+子状态DEREG_ATTEMPTING_TO_ATTACH下收到
                   T3411定时器超时

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.X00148705              2010-01-30  修改向ESM重新发PDN_REQ

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }


    #if 1
    /*重新ATTATCH*/
    NAS_EMM_AD_Reattach();

    #else
    /*保存触发ATTACH的原因*/
    /*NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_TIMER_EXP;*/

    /*向MRRC发送ATTACH REQUEST消息*/
    NAS_EMM_MrrcSendAttReq(             NAS_EMM_GLO_AD_GetEsmMsgLen());

    /*启动定时器T3410*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3410);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_CN_ATTACH_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                                        TI_NAS_EMM_T3410);
    #endif

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp
 Description     : 主状态DEREG+子状态ATTEMPTING_TO_ATTACH下收到T3402定时器超时
                   发起attach
 Input           :

 Return          :

 History         :
    1.leili         00132387    2008-09-09  Draft Enact
    2.hanlufeng     41410       2009-04-30  ATTEMPTING TO ATTACH状态下，发起
                                ATTACH，直接使用ATTACH模块缓存的PDN消息，不再
                                向SM模块请求;
                                ATTACH 尝试计数器在启动3402时被清空，此处不再清

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_PDN_CON_IND消息*/
    /*NAS_EMM_EsmSendPdnConnInd(          NAS_EMM_GLO_AD_GetDefBeaId());*/
    NAS_EMM_EsmSendPdnConnInd(          0);

    /*启动定时器TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_PDN_RSP*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);


    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd
 Description     : Dereg.Attach-Needed状态下收到 RRC_EMM_ACCESS_GRANT_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhengjunyan 00148421 2009.03.17 New Draft
    2.yangfan     00159566 2010.02.08 Modefy
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    LRRC_LMM_ACCESS_GRANT_IND_STRU           *pRrcMmGrantInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                              ulRst;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;

    /*check the input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {

        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd: NULL PTR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*check the current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*get the grant msg*/
    pRrcMmGrantInd = (LRRC_LMM_ACCESS_GRANT_IND_STRU *)pMsgStru;
    if ((LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL == pRrcMmGrantInd->enAccessGrantType) ||
        (LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MT == pRrcMmGrantInd->enAccessGrantType) ||
        (LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL == pRrcMmGrantInd->enAccessGrantType)||
        (LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MT == pRrcMmGrantInd->enAccessGrantType)||
        (LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MO_CSFB == pRrcMmGrantInd->enAccessGrantType)||
        (LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB == pRrcMmGrantInd->enAccessGrantType)||
        (LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB_AND_MT == pRrcMmGrantInd->enAccessGrantType)||
        (LRRC_LNAS_ACCESS_GRANT_ALL == pRrcMmGrantInd->enAccessGrantType))
    {
        /*保存触发ATTACH的原因*/
        /*NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_OTHER;*/

        /*发送EMM_ESM_STATUS_IND(去注册)*/
        NAS_EMM_AttSendEsmResult(       EMM_ESM_ATTACH_STATUS_DETACHED);

        /*转换EMM状态机MS_DEREG+SS_DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*发送ATTACH REQ内部消息给ATTACH模块*/
        ulRst = NAS_EMM_SendIntraAttachReq();
        if(NAS_EMM_SUCC != ulRst)
        {
            NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd: send INTRA ATTACH REQ ERR !");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd_ENUM,LNAS_EMM_SEND_ATT_REQ_ERR);
        }
    }
    else
    {
        return NAS_LMM_MSG_DISCARD;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd
 Description     : Dereg.Attach_Needed状态下收到SYS_INFO_IND，处理禁止信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-12-14  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    EMMC_EMM_SYS_INFO_IND_STRU          *pstsysinfo = NAS_EMM_NULL_PTR;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;

    /* 入参检查*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd: NULL PTR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* EMM状态检查*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果系统消息被禁，则迁移到 Dereg.Limite_Service*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;

    if((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
        ||(EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
    {
        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SetAttType();

        NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_PDN_RSP下收到定时器超时

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2. zhuyiqiang 00138739   2009-08-12  MODIFY BJ9D01687
    3.zhengjunyan 001148421 2010-11-09 MOD:考虑RegInit.WtPdnRsp可能是CONN态的情况
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp(VOS_UINT32 ulMsgId,
                                                            VOS_VOID * pMsgStru)

{
     /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*向ESM发送ID_EMM_ESM_REL_IND*/
    NAS_EMM_EsmSendRelInd();

    /*修改状态：进入主状态DEREG子状态DEREG_PLMN_SEARCH*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    /*向MMC发送消息*/
    /*NAS_EMM_AttSendAppResult(APP_ERR_MM_ATTACH_FAIL_UNSPECIFIED_ABNORMAL);*/
    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ESM_FAILURE);
    /*ATTACH清除资源*/
    NAS_EMM_Attach_ClearResourse();

    /* 如果处于CONN态,释放连接*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);
    }

   return   NAS_LMM_MSG_HANDLED;


}



/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_PDN_RSP下收到定时器超时

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  添加通知APP缺省承载激活失败
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp(VOS_UINT32 ulMsgId,
                                                            VOS_VOID * pMsgStru)

{
     /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }
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

    /*去注册*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcAttCompleteSendFail
 Description     : ATTACH COMPLETE消息发送失败
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470      2011-12-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcAttCompleteSendFail( VOS_VOID )
{
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        /*启动定时器T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        NAS_EMM_AppSendAttFailWithAllPara();
    }

    else
    {
        /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
        /*设置update status为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        /*必须先删除TAI List再启动T3402,顺序不能颠倒*/
        /*启动定时器T3402*/
        NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

        /* 必须先转状态再上报结果，再清除 attach attempt counter*/

        /*修改状态：进入主状态DEREG子状态DEREG_ATTEMPTING_TO_ATTACH*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_AppSendAttFailWithAllPara();
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_BEARER_CNF下收到系统消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.lihong00150010         2012-10-31  Modify:emgergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  )
{
    EMMC_EMM_SYS_INFO_IND_STRU           *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*判断是否是TA变化了*/
    if ((EMMC_EMM_CHANGE_PLMN           != pRcvEmmMsg->ulChangeInfo)
        && (EMMC_EMM_CHANGE_TA          != pRcvEmmMsg->ulChangeInfo))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo:no change");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo_ENUM,LNAS_EMM_TA_NO_CHANGE);
        return  NAS_LMM_MSG_HANDLED;
    }

    if ((EMMC_EMM_NO_FORBIDDEN == pRcvEmmMsg->ulForbiddenInfo)
        && (EMMC_EMM_CELL_STATUS_ANYCELL != pRcvEmmMsg->ulCellStatus))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo:no forbidden and not any cell");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo_ENUM,LNAS_EMM_NOFORB_NOTANYCELL);

        /*停止定时器*/
        NAS_LMM_StopStateTimer(     TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

        /* 如果是紧急注册，则重新发起紧急注册 */
        if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

            /* 发送ATTACH CMP消息失败的处理 */
            NAS_EMM_ProcAttCompleteSendFail();

            /* 通知IMSA再尝试CS域 */

            NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

            return  NAS_LMM_MSG_HANDLED;
        }

        /*重新发起普通ATTACH*/
        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        NAS_EMM_EsmSendPdnConnInd(          0);
        NAS_LMM_StartStateTimer(            TI_NAS_EMM_WAIT_ESM_PDN_RSP);
        NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                            EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                            TI_NAS_EMM_WAIT_ESM_PDN_RSP);

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo:forbidden or any cell");
    TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo_ENUM,LNAS_EMM_FORB_ANYCELL);

    /*停止定时器*/
    NAS_LMM_StopStateTimer(     TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /*状态迁移:Dereg.Limite_Service*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pRcvEmmMsg->ulForbiddenInfo);

        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        /* 通知IMSA再尝试CS域 */
    }
    else
    {
        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_AttResetAttAttempCounter();

            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /*状态迁移:Dereg.Limite_Service*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb( pRcvEmmMsg->ulForbiddenInfo);

        NAS_EMM_RelReq(             NAS_LMM_NOT_BARRED);
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下收到系统消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.yangfan 00159566       2009-08-25  Modify
    3.zhengjunyan 00148421   2010-10-25  MOD:添加被禁的判断
    4.lihong00150010         2012-11-01  Modify:emgergency
    5.lifuxin 00253982       2014-11-06  重构建链流程
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru)
{
    EMMC_EMM_SYS_INFO_IND_STRU           *pstSysInfoInd = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    pstSysInfoInd                          = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsgStru;

     NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo is entered");
     TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*当当前状态是NAS_EMM_CONN_ESTING，收到了系统消息，在这种情况，直接丢弃
      该消息，等待RRC建链回复即可。
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        if((EMMC_EMM_NO_FORBIDDEN != pstSysInfoInd->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstSysInfoInd->ulCellStatus))
        {
            return  NAS_LMM_STORE_HIGH_PRIO_MSG;
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /*如果系统消息被禁，则释放连接，进入Dereg.Limite_Service*/
    if ((EMMC_EMM_NO_FORBIDDEN != pstSysInfoInd->ulForbiddenInfo)
        ||(EMMC_EMM_CELL_STATUS_ANYCELL == pstSysInfoInd->ulCellStatus))
    {
        /* 终止ATTACH流程*/
        NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo: Cell Forb.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo_ENUM,LNAS_EMM_FORBIDDEN);
        if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_StartEmergencyAttach();

            return  NAS_LMM_MSG_HANDLED;
        }

        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_AttResetAttAttempCounter();

            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /*状态迁移:Dereg.Limite_Service*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstSysInfoInd->ulForbiddenInfo);


        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*zhengjunyan注:正常情况下不会执行下面的分支，暂时保留目前实现*/
    /*判断是否是TA变化了*/
    if ((EMMC_EMM_CHANGE_PLMN == pstSysInfoInd->ulChangeInfo)
         || (EMMC_EMM_CHANGE_TA == pstSysInfoInd->ulChangeInfo))
    {
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo: Enter New TA.!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo_ENUM,LNAS_EMM_NEW_TA);

        /*停止,启动定时器T3410*/
        NAS_LMM_StartStateTimer(     TI_NAS_EMM_T3410);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_ATTACH);
        #endif
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
 Function Name   : NAS_EMM_MsDrgSsNmlSrvMsgIntraMsgAttReq
 Description     : 主状态DEREG+子状态DEREG_NORMAL_SERVICE下收到EMM内部模块发送的
                   内部消息ATTACH REQUEST

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq( VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_ATTACH_REQ_STRU                     *pRcvEmmMsg;
    pRcvEmmMsg = (NAS_LMM_INTRA_ATTACH_REQ_STRU*)      pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_IntraAttReqChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq: MMC_MM_SYS_INFO_IND_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*保存触发ATTACH的原因*/
    if(EMM_ATTACH_CAUSE_ESM== NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_GLO_AD_GetAttCau()          = EMM_ATTACH_CAUSE_OTHER;
    }
    /*检查如果UE不能自动发起ATTACH,则不发起注册流程*/
    if(NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetPsAttachAllowFlg())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq:AUTO ATTACH NOT ALLOW!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq_ENUM,LNAS_EMM_AUTO_ATT_NOTALLOW);

        /* 向MMC上报ATTACH结果 */
        NAS_EMM_AppSendAttPsNotAllow();

        return NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ID_EMM_ESM_PDN_CON_IND消息*/
    /*NAS_EMM_EsmSendPdnConnInd(          NAS_EMM_GLO_AD_GetDefBeaId());*/
    NAS_EMM_EsmSendPdnConnInd(0);

    /*启动定时器TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_PDN_RSP*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name  : NAS_EMM_MsRegSsNmlSrvMsgAuthRej
 Discription    : Reg.Normal_Service状态下收到AUTH_REJ消息
 Input          : None
 Output         : None
 Return         :
 History:
      1.  z00148421  2009-10-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgAuthRej(
                                        VOS_UINT32 ulMsgId,
                                        VOS_VOID *pMsgStru)
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsNmlSrvMsgAuthRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 鉴权拒绝优化处理 */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name  : NAS_EMM_MsRegSsLimitedSrvMsgAuthRej
 Discription    : Reg.Limit_Service状态下收到AUTH_REJ消息
 Input          : None
 Output         : None
 Return         :
 History:
      1.lihong00150010      2012-12-29      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAuthRej
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
)
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgAuthRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 鉴权拒绝优化处理 */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthRej
 Description     : Reg.RegAttemptingToUpdateMM状态下收到AUTH_REJ消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthRej
(
    VOS_UINT32 ulMsgId,
    VOS_VOID *pMsgStru
)
{

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 鉴权拒绝优化处理 */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);

    return NAS_LMM_MSG_HANDLED;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej
 Description     : CONN模式,Reg.AnyState状态下收到AUTH REJ消息，作为卡无效处
                   理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-5-20  Draft Enact
    2.X00148705                 2009-09-30 重构

*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej( VOS_UINT32  ulCause)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej_ENUM,LNAS_ENTRY);

    (VOS_VOID)(                           ulCause);

    /*停止定时器*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /*删除GUTI,L.V.R TAI,TAI LIST,KSIasme,设置Update Status*/
     /*设置update status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);
    /*删除GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*向MMC发送LMM_MMC_DETACH_CNF消息*/
    ulTauRslt = MMC_LMM_TAU_RSLT_AUTH_REJ;
    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*等待RRC_REL_IND*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AttResetAttAttempCounter
 Description     : 清除ATTACH相关计数，本次仅添加AT&T定制需求和函数头
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151         2015-01-04      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_AttResetAttAttempCounter(VOS_VOID)
{
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_AttResetAttAttempCounter is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AttResetAttAttempCounter_ENUM,LNAS_ENTRY);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()      = 0;
    NAS_EMM_GLO_AD_GetAttRej19AtmpCnt() = 0;
    return;
}



VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru  )
{
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd_ENUM,LNAS_ENTRY);
    (VOS_VOID)(                         ulMsgId);
    (VOS_VOID)(                         pMsgStru);

    /*停止定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(             TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* 大数据: 更新attach被REL次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在ATTACH结果上报之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        NAS_EMM_AdStateConvert(          EMM_MS_DEREG,
                                         EMM_SS_DEREG_PLMN_SEARCH,
                                         TI_NAS_EMM_STATE_NO_TIMER);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        return  NAS_LMM_MSG_HANDLED;
    }

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

        /* 发送ATTACH CMP消息失败的处理 */
        NAS_EMM_ProcAttCompleteSendFail();

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        /* 通知IMSA再尝试CS域紧急呼 */

        return  NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*与ESM交互，重新发起ATTACH*/
    /*向ESM发送ID_EMM_ESM_PDN_CON_IND消息*/
    NAS_EMM_EsmSendPdnConnInd(0);

    /*启动定时器TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_PDN_RSP*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);


    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_VOID  NAS_EMM_AttNrmFailProc( VOS_VOID )
{
    /*判断ATTACH尝试计数器，根据计数器分小于5和等于5处理*/
    if (NAS_EMM_GLO_AD_GetAttAtmpCnt()  < 5)
    {
        NAS_EMM_AtmpCntLess5Proc();
    }
    else
    {
        NAS_EMM_AtmpCntEqual5Proc();
    }
    return;
}


VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru  )
{
    NAS_EMM_ATTACH_LOG_NORM(            "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp_ENUM,LNAS_ENTRY);
    (VOS_VOID)(                         ulMsgId);
    (VOS_VOID)(                         pMsgStru);


    /* 大数据: 更新attach DATA REQ发送失败次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在ATTACH结果上报之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(       EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

    NAS_EMM_ProcAttCompleteSendFail();

    if(NAS_EMM_CONN_IDLE           != NAS_EMM_GetConnState())
    {
        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(              NAS_LMM_NOT_BARRED);
    }

    /* ATTACH触发原因值在紧急承载激活成功清动态表时已通知EMM清除 */
    if (NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo(
                                                    VOS_UINT32      ulMsgId,
                                                    VOS_VOID        *pMsgStru  )
{
    EMMC_EMM_SYS_INFO_IND_STRU           *pstRcvEmmMsg;

    (VOS_VOID)(ulMsgId);
    pstRcvEmmMsg                        = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM( "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo_ENUM,LNAS_ENTRY);

    /* 为了规避RRC修改重配置流程不等网侧相应导致问题DTS2016012002189:
       UE在注册过程中，SS调整服务小区至-115dB（打开同频邻区-85dB） 并且故意不响应ATTACH COMPLETE，
       此时期望UE重建立到同频邻区并且重新发起注册流程，但是并没有达到预期，而是释放链路后重新搜网注册。与GCF协议9.2.1.1.24不一致。
       规避方案为:如果测试卡收到ATTCH CMP失败，则什么也不做。这时EMM处于REG_INIT+WAIT_RRC_DATA_CNF状态。
       这样后面可能会有两种情况:1. RRC重建立成功，EMM收到LRRC系统消息，此时EMM重新发ATTACH，符合GCF协议
       2. RRC重建立失败，RRC释放链路，后续UE会重新搜网收到系统消息发ATTACH，行为也正常。
       因此将此处改为:当测试场景下，REG_INIT+WAIT_RRC_DATA_CNF收到系统消息，不管TA有没有改变，都后续发ATTACH。 */
    /*判断是否是TA变化了*/
    if (((EMMC_EMM_CHANGE_PLMN           != pstRcvEmmMsg->ulChangeInfo)
          && (EMMC_EMM_CHANGE_TA          != pstRcvEmmMsg->ulChangeInfo))
         && (PS_SUCC != LPS_OM_IsTestMode()))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo:no change");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo_ENUM,LNAS_EMM_TA_NO_CHANGE);
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);
    if((EMMC_EMM_NO_FORBIDDEN         == pstRcvEmmMsg->ulForbiddenInfo)
        && (EMMC_EMM_CELL_STATUS_ANYCELL != pstRcvEmmMsg->ulCellStatus))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo:no forbidden and not any cell");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo_ENUM,LNAS_EMM_NOFORB_NOTANYCELL);



        NAS_EMM_SendRrcClearBuffNotify();

        /* ATTACH触发原因值在紧急承载激活成功清动态表时已通知EMM清除 */
        if (NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

            /* 发送ATTACH CMP消息失败的处理 */
            NAS_EMM_ProcAttCompleteSendFail();

            /* 通知IMSA再尝试CS域 */

            NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

            return  NAS_LMM_MSG_HANDLED;
        }

        /*重新普通ATTACH*/
        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        NAS_EMM_EsmSendPdnConnInd(      0);
        NAS_LMM_StartStateTimer(        TI_NAS_EMM_WAIT_ESM_PDN_RSP);
        NAS_EMM_AdStateConvert(         EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                                        TI_NAS_EMM_WAIT_ESM_PDN_RSP);

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo:forbidden or any cell");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo_ENUM,LNAS_EMM_FORB_ANYCELL);


    /* ATTACH触发原因值在紧急承载激活成功清动态表时已通知EMM清除 */
    if (NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
    {
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /*状态迁移:Dereg.Limite_Service*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstRcvEmmMsg->ulForbiddenInfo);

        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        /* 通知IMSA再尝试CS域 */
    }
    else
    {
        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_AttResetAttAttempCounter();

            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /*状态迁移:Dereg.Limite_Service*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstRcvEmmMsg->ulForbiddenInfo);

        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);
    }

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)(                         pMsgStru);
    (VOS_VOID)(                         ulMsgId);
    NAS_EMM_ATTACH_LOG_NORM(            "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd_ENUM,LNAS_ENTRY);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在ATTACH结果上报之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(       EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    /* 发送ATTACH CMP消息失败的处理 */
    NAS_EMM_ProcAttCompleteSendFail();

    /* ATTACH触发原因值在紧急承载激活成功清动态表时已通知EMM清除 */
    if (NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return  NAS_LMM_MSG_HANDLED;

}


/*****************************************************************************
 Function Name   : NAS_EMM_AttGuAttachRst
 Description     : 挂起状态下，处理GU发来的ATTACH结果
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Hanlufeng 41410      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_AttGuAttachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_AttGuAttachRst: ulActRst =.",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_AttGuAttachRst_ENUM,LNAS_ACT_RESULT,pMmcActResult->ulActRst);

    if(MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /* 通知ESM状态改变 */
        NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);
    }
    else
    {
        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /* 通知ESM状态改变 */
        NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    return;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_SndAttachCmpSuccProc
 Description     : ATTACH COMPLETE发送成功时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen 00209181    2013-03-30      Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndAttachCmpSuccProc(VOS_VOID* pMsg)
{
    NAS_EMM_ESM_MSG_BUFF_STRU           *pstEsmMsg = NAS_EMM_NULL_PTR;

    (VOS_VOID)pMsg;

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_SndAttachCmpSuccProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachCmpSuccProc_ENUM,LNAS_ENTRY);

    /*根据触发原因向ESM发送结果*/
    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_ATTACHED);
    /* 大数据: 更新attach成功次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_SUCC);

    /*发送UE指定的 Drx_Cycle给RRC*/

    if(NAS_EMM_DRX_CYCLE_LEN_CHANGED == NAS_EMM_GetDrxCycleLenChangeFlag())
    {
        NAS_EMM_SendUeSpecDrxCycleLenToRrc();
        NAS_EMM_SetDrxCycleLenChangeFlag(NAS_EMM_DRX_CYCLE_LEN_NOT_CHANGED);
    }

    NAS_MML_SetPsRegContainDrx(NAS_MML_LTE_PS_REG_CONTAIN_DRX_PARA);

    NAS_EMM_AttResetAttAttempCounter();

    /* 发送ATTACH CMP成功，将注册状态设置为CMP_SEND */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_CMP_SEND);

    /*发送 LMM_MMC_TIN_TYPE_IND*/
    NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);
    /*更新所有承载的ISR标识为ISR激活前*/
    NAS_EMM_UpdateBearISRFlag(NAS_MML_GetPsBearerCtx());
    NAS_LMM_LogPsBearerCtxInfo(NAS_MML_GetPsBearerCtx());
    NAS_EMM_SetAttachRegDomain();

    if ((MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType()) &&
        (EMM_ATTACH_RST_PS == NAS_EMM_GLO_AD_GetAttRslt()))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcRrcDataCnfSucc Eps Only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachCmpSuccProc_ENUM,LNAS_EMM_EPS_ONLY);

        NAS_EMM_ProcRrcDataCnfEpsSuccOnly();
    }
    else
    {
        /*修改状态：进入主状态REG子状态REG_NORMAL_SERVICE*/
        if (NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                            EMM_SS_REG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

            NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_EMC_REGED);
        }
        else
        {
            NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

            NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED);
        }

        pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)NAS_LMM_GetEmmInfoEsmBuffAddr();
        if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            && (NAS_EMM_NULL_PTR != pstEsmMsg))
        {
            /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
            NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);

            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_OTHER;
            NAS_EMM_ClearEmcEsmMsg();
        }

        /*ATTACH完成向MMC发送ATTACH成功*/
        NAS_EMM_AppSendAttSucc();
    }
    /* ATTACH 成功，如果之前发生了异系统变换，需清除触发和类型记录信息 */
    NAS_EMM_ClearResumeInfo();
    /* ATTACH 成功，清除之前保存的原因值 */
    NAS_LMM_ClearEmmInfoMmcAttachReason();

    /* 大数据: 记录ATTACH 流程结束时间 */
    NAS_LMM_SaveAttachEndTimeStamp();

    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndAttachCmpFailProc
 Description     : ATTACH COMPLETE发送失败时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen 00209181    2013-03-30      Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndAttachCmpFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    (VOS_VOID)pMsg;
    *pulIsDelBuff = VOS_TRUE;

    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_SndAttachCmpFailProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachCmpFailProc_ENUM,LNAS_ENTRY);

    /* 为了规避RRC修改重配置流程不等网侧相应导致问题DTS2016012002189:
       UE在注册过程中，SS调整服务小区至-115dB（打开同频邻区-85dB） 并且故意不响应ATTACH COMPLETE，
       此时期望UE重建立到同频邻区并且重新发起注册流程，但是并没有达到预期，而是释放链路后重新搜网注册。与GCF协议9.2.1.1.24不一致。
       规避方案为:如果测试卡收到ATTCH CMP失败，则什么也不做。这时EMM处于REG_INIT+WAIT_RRC_DATA_CNF状态。
       这样后面可能会有两种情况:1. RRC重建立成功，EMM收到LRRC系统消息，此时EMM重新发ATTACH，符合GCF协议
       2. RRC重建立失败，RRC释放链路，后续UE会重新搜网收到系统消息发ATTACH，行为也正常。*/
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachCmpFailProc_ENUM,LNAS_TEST_CARD);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 大数据: 更新attach cmp DATA REQ发送失败次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        NAS_EMM_ATTACH_LOG_INFO(" NAS_EMM_SndAttachCmpFailProc: CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAttachCmpFailProc_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        NAS_EMM_AppSendAttFailWithPara();

        /*重设attach attempt counter，顺序必须在ATTACH结果上报之后*/
        NAS_EMM_AttResetAttAttempCounter();

        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(       EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AttSendEsmResult(   EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_GLO_AD_GetAttAtmpCnt()++;

    NAS_EMM_ProcAttCompleteSendFail();

    /*发送RRC_MM_REL_REQ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    /* ATTACH触发原因值在紧急承载激活成功清动态表时已通知EMM清除 */
    if (NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_EMM_ATTAttachRej19CountProc
 Description     :美国AT&T定制需求，对于ATTACH被#19拒绝，要单独维护计数，
                  原则为，如果收到#19次数累计达3次，就设置ATTACH尝试次数为5，
                  否则仍按照原计数进行处理。
 Input           :None
 Return          :None

 History         :
    1.sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_DamAttachRej19CountProc(VOS_VOID)
{
    NAS_EMM_GLO_AD_GetAttRej19AtmpCnt()++;

    if(NAS_EMM_DAM_ATTACH_REJ19_MAX_CNT <= NAS_EMM_GLO_AD_GetAttRej19AtmpCnt())
    {
        NAS_EMM_GLO_AD_GetAttAtmpCnt() = 5;
    }
    else
    {
        NAS_EMM_GLO_AD_GetAttAtmpCnt() ++;
    }

    /* 输出ATTACH被拒#19累计次数到OM */
    NAS_LMM_SndOmRej19Cnt();

    return;
}

/*****************************************************************************
 Function Name   :NSA_EMM_SndImsaAttachBeginInd
 Description     :给IMSA发送Attach Begin指示
 Input           :None
 Return          :None

 History         :
    1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID NSA_EMM_SndImsaAttachBeginInd(VOS_VOID)
{
    LMM_IMSA_ATTACH_BEGIN_IND           *pstAttachBeginInd;


    /*申请消息内存*/
    pstAttachBeginInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_IMSA_ATTACH_BEGIN_IND));

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pstAttachBeginInd)
    {
        return;
    }

    /*构造LMM_IMSA_ATTACH_BEGIN_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_IMSA_MSG_HEADER(    pstAttachBeginInd,
                                        (sizeof(LMM_IMSA_ATTACH_BEGIN_IND)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pstAttachBeginInd->ulMsgName = ID_LMM_IMSA_ATTACH_BEGIN_IND;

    /*向IMSA发送ID_LMM_IMSA_ATTACH_BEGIN_IND消息*/
    NAS_LMM_SEND_MSG(pstAttachBeginInd);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

