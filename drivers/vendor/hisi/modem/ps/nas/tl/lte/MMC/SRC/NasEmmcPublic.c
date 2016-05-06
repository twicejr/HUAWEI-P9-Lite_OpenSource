/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmcPublic.c
  Description     : EMMC模块的公共操作
  History         :
     1.lining 00141619       2008-10-9   Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmcPublic.h"
#include  "NasEmmcSendMsg.h"
#include  "NasLmmPubMOm.h"
#include  "NasLmmPubMTimer.h"
/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMCPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMCPUBLIC_C
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
/* 全局变量g_stEmmcGlobalCtrl的定义 */
NAS_EMMC_GLOBAL_STRU                    g_stEmmcGlobalCtrl;

NAS_EMMC_GU_SYS_INFO_STRU               g_stEmmcGuSysInfo;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMMC_FillRrcNasForbTaList
 Description     : 按照NAS_RRC接口结构填充禁止TA列表
 Input           : RRC_NAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
 Output          : RRC_NAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_FillRrcNasForbTaList
(
    LRRC_LNAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
)
{
    VOS_UINT32                          i = 0;
    NAS_MM_TA_LIST_STRU                *pstForbTaListForRoaming = NAS_EMMC_NULL_PTR;

    /*get ForbTaListForRoaming and ForbTaListForRpos*/
    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);

    /* Fill ForbTaListForRoaming */
    /* 新增Del Forb定时器判断, 当定时器运行的时才把Roaming列表填给RRC, 防止定时器被误停止导致通知RRC后
        由于无定时器保护导致TA无法解禁, 该情况可能在给LRRC发搜网消息填充Forb列表时出现 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID))
    {
        for ( i=0; i < pstForbTaListForRoaming->ulTaNum; i++)
        {
            pstRrcNasForbTaList->astForbTa[i].stTac.ucTac
                = pstForbTaListForRoaming->astTa[i].stTac.ucTac;
            pstRrcNasForbTaList->astForbTa[i].stTac.ucTacCont
                = pstForbTaListForRoaming->astTa[i].stTac.ucTacCnt;
            pstRrcNasForbTaList->astForbTa[i].stPlmnId.aucPlmnId[0]
                = pstForbTaListForRoaming->astTa[i].stPlmnId.aucPlmnId[0];
            pstRrcNasForbTaList->astForbTa[i].stPlmnId.aucPlmnId[1]
                = pstForbTaListForRoaming->astTa[i].stPlmnId.aucPlmnId[1];
            pstRrcNasForbTaList->astForbTa[i].stPlmnId.aucPlmnId[2]
                = pstForbTaListForRoaming->astTa[i].stPlmnId.aucPlmnId[2];
        }

        /*caculate forbidden TA num*/
        pstRrcNasForbTaList->ulTaNum  = pstForbTaListForRoaming->ulTaNum ;
    }
    else
    {
        if (0 < pstForbTaListForRoaming->ulTaNum)
        {
            NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_FillRrcNasForbTaList TI_NAS_EMM_STATE_DEL_FORB_TA_PROID Not Running");
        }
    }

    /* 把临时列表中惩罚定时器运行中的TA填入列表中 */
    NAS_LMM_FillTempTaInRrcNasForbTaList(pstRrcNasForbTaList);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_FillUserSpecRrcNasForbTaList
 Description     : 用户指定搜网时填充下发给RRC的禁止TA列表
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-15  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMMC_FillUserSpecRrcNasForbTaList
(
    const NAS_MM_PLMN_ID_STRU  *pstPlmnId,
    NAS_MM_TA_LIST_STRU  *pstTaList
)
{

    NAS_MM_TA_LIST_STRU                *pstForbTaListForRoaming = NAS_EMMC_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU           *pstNetInfo = NAS_EMMC_NULL_PTR;
    VOS_UINT32                          i = 0;
    VOS_UINT32                          j = 0;

    if ((NAS_EMMC_NULL_PTR == pstPlmnId) ||
        (NAS_EMMC_NULL_PTR == pstTaList))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMMC_FillUserSpecRrcNasForbTaList: Input is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_FillUserSpecRrcNasForbTaList_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /*get ForbTaListForRoaming and ForbTaListForRpos*/
    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstNetInfo = (VOS_VOID*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);
    for (i = 0; i < pstForbTaListForRoaming->ulTaNum; i++)
    {
        if (NAS_LMM_MATCH_SUCCESS != NAS_LMM_PlmnMatch(pstPlmnId,&pstForbTaListForRoaming->astTa[i].stPlmnId))
        {
            NAS_LMM_MEM_CPY_S(  &pstTaList->astTa[j],
                                sizeof(NAS_MM_TA_STRU),
                                &pstForbTaListForRoaming->astTa[i],
                                sizeof(NAS_MM_TA_STRU));
            j++;

        }

    }
    pstTaList->ulTaNum = j;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMMC_FillUserSpecRrcNasForbTaList:Rej15 TA NUM =, ",
                                   pstNetInfo->stForbTaForRej15.ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_FillUserSpecRrcNasForbTaList_ENUM
,LNAS_FUNCTION_LABEL1,
                                   pstNetInfo->stForbTaForRej15.ulTaNum);

    for(i = 0; i < pstNetInfo->stForbTaForRej15.ulTaNum; i++ )
    {

       NAS_LMM_AddTaInTaList(   &pstNetInfo->stForbTaForRej15.astTa[i],
                                pstTaList,
                                NAS_LMM_MAX_FORBTA_NUM);
    }

    NAS_LMM_FillUserSpecRrcNasForbTaListWithTempTa(pstPlmnId, pstTaList);

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMMC_FillUserSpecRrcNasForbTaList:RRC FORB TA NUM =, ",
                                       pstTaList->ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_FillUserSpecRrcNasForbTaList_ENUM
,LNAS_FUNCTION_LABEL2,
                                   pstTaList->ulTaNum);
    return;
}



/*****************************************************************************
 Function Name   : NAS_EMMC_GetCurrentTa
 Description     : 获取当前TAs
 Input           : NAS_MM_TA_STRU pstTa
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_GetCurrentTa( NAS_MM_TA_STRU *pstTa )
{
    NAS_MM_NETWORK_ID_STRU              *pstAreaInfo;

    if (NAS_EMMC_NULL_PTR == pstTa)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_GetCurrentTa:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_GetCurrentTa_ENUM
,LNAS_NULL_PTR);
        return;
    }
    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    NAS_LMM_PlmnCpy(&(pstTa->stPlmnId), &pstAreaInfo->stPlmnId);

    pstTa->stTac.ucTac                  = pstAreaInfo->stTac.ucTac;

    pstTa->stTac.ucTacCnt               = pstAreaInfo->stTac.ucTacCnt;

    return;
}



VOS_VOID  NAS_EMMC_GetForbPlmnInfo
(
    NAS_MM_PLMN_LIST_STRU               *pstFPlmn,
    NAS_MM_PLMN_LIST_STRU               *pstFPlmnForGprs
)
{
    MMC_LMM_PUB_INFO_STRU               stFPlmnInfo;
    MMC_LMM_PUB_INFO_STRU               stFPlmnForGprsInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulErrInd;

    if ((NAS_EMMC_NULL_PTR == pstFPlmn) ||
        (NAS_EMMC_NULL_PTR == pstFPlmnForGprs))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_GetForbPlmnInfo:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_GetForbPlmnInfo_ENUM
,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(&stFPlmnInfo,sizeof(MMC_LMM_PUB_INFO_STRU),0,sizeof(MMC_LMM_PUB_INFO_STRU));
    NAS_LMM_MEM_SET_S(&stFPlmnForGprsInfo,sizeof(MMC_LMM_PUB_INFO_STRU),0,sizeof(MMC_LMM_PUB_INFO_STRU));

    /*获取禁止PLMN*/
    ulErrInd = NAS_EMM_GetGulPubInfo(MMC_LMM_FPLMN,&stFPlmnInfo);

    if (MMC_LMM_SUCC != ulErrInd)
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_GetCurrentForbInfo: FPLMN Invalid");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_GetForbPlmnInfo_ENUM
,LNAS_FUNCTION_LABEL1);
    }

    /*获取禁止PLMN for GPRS*/
    ulErrInd = NAS_EMM_GetGulPubInfo(MMC_LMM_FPLMN_FOR_GPRS,&stFPlmnForGprsInfo);

    if (MMC_LMM_SUCC != ulErrInd)
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_GetCurrentForbInfo: FPLMN FOR GRPS Invalid");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_GetForbPlmnInfo_ENUM
,LNAS_FUNCTION_LABEL2);
    }
    NAS_LMM_PlmnListCpy(pstFPlmn, (NAS_MM_PLMN_LIST_STRU *)&(stFPlmnInfo.u.stForbiddenPlmnList));
    NAS_LMM_PlmnListCpy(pstFPlmnForGprs, (NAS_MM_PLMN_LIST_STRU *)&(stFPlmnForGprsInfo.u.stForbiddenPlmnListForGPRS));

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMMC_GetCurrentForbInfo
 Description     : 获取当前区域禁止信息
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-10-16  Draft Enact
    2.leili   00132387      2011-02-25  Modify EMMC适配

*****************************************************************************/
VOS_VOID NAS_EMMC_GetCurrentForbInfo
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  *pulForbdInfo
)
{
    NAS_MM_NETWORK_ID_STRU              *pstAreaInfo;
    NAS_MM_PLMN_LIST_STRU               stForbPlmn;
    NAS_MM_PLMN_LIST_STRU               stForbPlmnForGprs;
    NAS_MMC_TA_LIST_STRU                *pstForbTaForRoming;
    NAS_MMC_TA_LIST_STRU                *pstForbTaForRegional;
    NAS_MMC_TA_STRU                     stTa;

    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbdInfo;

    if (NAS_EMMC_NULL_PTR == pulForbdInfo)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_GetCurrentForbInfo:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_GetCurrentForbInfo_ENUM
,LNAS_NULL_PTR);
        return;
    }

    ulForbdInfo                         = EMMC_EMM_NO_FORBIDDEN;
    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    NAS_LMM_MEM_SET_S(&stForbPlmn,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_SET_S(&stForbPlmnForGprs,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));

    NAS_EMMC_GetForbPlmnInfo(&stForbPlmn,&stForbPlmnForGprs);

    pstForbTaForRoming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaForRegional = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);

    NAS_EMMC_GetCurrentTa(&stTa);

    if (NAS_LMM_MATCH_SUCCESS ==
           NAS_LMM_PlmnIDMatchPlmnList(&pstAreaInfo->stPlmnId, &stForbPlmn))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_PLMN;
    }
    else if (NAS_LMM_MATCH_SUCCESS ==
            NAS_LMM_PlmnIDMatchPlmnList(&pstAreaInfo->stPlmnId,&stForbPlmnForGprs))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS;
    }
    else if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&stTa, pstForbTaForRoming))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING;
    }
    else if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&stTa, pstForbTaForRegional))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_TA_FOR_RPOS;
    }
    else if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTempTaListWithForbTimerRunning(&stTa))
    {
        /* 当TA在Gradul Forb临时列表中, 且惩罚定时器在运行, 则被禁 */
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING;
    }
    else
    {
    }

    *pulForbdInfo                       = ulForbdInfo;

    return;


}


/*****************************************************************************
 Function Name   : NAS_LMM_IsCellStatusNormal
 Description     : 判断小区状态是否为NORMAL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2014-01-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_IsCellStatusNormal
(
    MMC_LMM_PLMN_ID_STRU               *pstPlmn,
    const   NAS_MM_TA_STRU             *pstTa
)
{
    const NAS_MM_TA_LIST_STRU          *pstForbTaListForRoaming = VOS_NULL_PTR;
    const NAS_MM_TA_LIST_STRU          *pstForbTaListForRpos = VOS_NULL_PTR;
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl;
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    ucSimType = NAS_EMM_GetSimType();

    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaListForRpos = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);
    ulPlmnCtrl = Nas_PlmnIdIsForbid(pstPlmn);
    if ((NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
        &&(NAS_LMM_SIM_VALID == NAS_LMM_GetPsSimValidity())
        &&(NAS_MML_SIM_TYPE_USIM == ucSimType)
        &&(MMC_LMM_PLMN_ALLOW_REG == ulPlmnCtrl)
        &&(NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTaList(pstTa, pstForbTaListForRoaming))
        &&(NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTaList(pstTa, pstForbTaListForRpos))
        &&(NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTempTaListWithForbTimerRunning(pstTa)))
    {
        return VOS_TRUE;
    }
    NAS_LMM_SndOmAnyCellJudgingInfo(ucSimType, ulPlmnCtrl, pstTa);
    return VOS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_ProcessMmcLteSysInfoInd
 Description     : RRC系统消息上报处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-10-16  Draft Enact
    2.Date         : 2009/5/7
      Author       : lining 00141619
      Modification : 问题单BA8D01630
                     修改了MMC对RRC系统消息的处理
    3.Date         : 2009/5/20
      Author       : lining 00141619
      Modification : 问题单BN8D00126
                     增加了低质量PLMN LIST初始化
    4.Date         : 2009/7/22
      Author       : zhengjunyan 00148421
      Modification : 24301_CR97
                     比较系统消息与当前网络信息，获取信息变化情况。
    5.Date         : 2011/02/25
      Author       : leili 00132387
      Modification : EMMC适配
    6.Date         : 2012/12/17
      Author       : lihong00150010
      Modification : Emergency
    7.Date         : 2012/12/22
      Author       : lihong 00150010
      Modification : DTS2012121306127，系统消息机制变更
*****************************************************************************/
VOS_VOID  NAS_EMMC_ProcessMmcLteSysInfoInd
(
    const MMC_LMM_SYS_INFO_STRU        *pstLteInfoIndMsg,
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32   *pulChangeInfo,
    EMMC_EMM_CELL_STATUS_ENUM_UINT32   *penCellStatus,
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 *penForbdInfo
)
{
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo = EMMC_EMM_NO_CHANGE;
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;
    NAS_LMM_NETWORK_INFO_STRU           *pstNetInfo;
    NAS_MM_TA_STRU                      stTa;
    EMMC_EMM_CELL_STATUS_ENUM_UINT32    enCellStatus = EMMC_EMM_CELL_STATUS_NORMAL;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 enForbdInfo = EMMC_EMM_NO_FORBIDDEN;

    NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoInd_ENUM
,LNAS_ENTRY);

    pstNetInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);

    pstNetInfo->bitOpPresentNetId = NAS_EMMC_BIT_SLCT;

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);


    /*比较系统消息与UE维护的当前网络信息,获取信息变更类型*/
    if(NAS_LMM_MATCH_FAIL ==
            NAS_LMM_PlmnMatch(&(pstAreaInfo->stPlmnId),
                (NAS_MM_PLMN_ID_STRU *)pstLteInfoIndMsg->stSpecPlmnIdList.astSuitPlmnList))
    {
        ulChangeInfo                    = EMMC_EMM_CHANGE_PLMN;
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoInd: MMC_EMM_CHANGE_PLMN");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1);

        NAS_EMMC_SendEsmPlmnChangeInd();
    }
    else if(NAS_LMM_MATCH_FAIL ==
                NAS_LMM_TacMatch(&(pstAreaInfo->stTac),
                    (NAS_MM_TAC_STRU *)&(pstLteInfoIndMsg->stTac)))
    {
        ulChangeInfo                    = EMMC_EMM_CHANGE_TA;
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoInd: MMC_EMM_CHANGE_TA");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoInd_ENUM,LNAS_FUNCTION_LABEL2);
    }
    else if (pstAreaInfo->ulCellId != pstLteInfoIndMsg->ulCellId)
    {
        ulChangeInfo                    = EMMC_EMM_CHANGE_CELL;
    }
    else
    {
        ulChangeInfo                    = EMMC_EMM_NO_CHANGE;
    }


    NAS_LMM_PlmnCpy(&pstAreaInfo->stPlmnId,
            (NAS_MM_PLMN_ID_STRU *)&pstLteInfoIndMsg->stSpecPlmnIdList.astSuitPlmnList[0]);


    pstAreaInfo->stTac.ucTac            = pstLteInfoIndMsg->stTac.ucTac;
    pstAreaInfo->stTac.ucTacCnt         = pstLteInfoIndMsg->stTac.ucTacCnt;

    pstAreaInfo->ulCellId               = pstLteInfoIndMsg->ulCellId;
    /* 勾出Forbidden Plmn&Ta 信息 */
    NAS_EMMC_SndOmLogForbiddenInfo();
    /* 获取禁止信息 */
    if (NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag())
    {
       enForbdInfo =  EMMC_EMM_NO_FORBIDDEN;
    }
    else
    {
        NAS_EMMC_GetCurrentForbInfo(&enForbdInfo);
    }

    pstAreaInfo->ulForbiddenInfo = enForbdInfo;

/* s00193151 mod for GU NAS LAU 停止T3212定时器的问题 begin */
    pstAreaInfo->ulCellStatus = pstLteInfoIndMsg->enCellStatusInd;
    enCellStatus              = pstLteInfoIndMsg->enCellStatusInd;

    NAS_LMM_MEM_CPY_S(  pstAreaInfo->aulLteBand,
                        sizeof(LTE_BAND_STRU),
                        pstLteInfoIndMsg->stLteBand.aulLteBand,
                        sizeof(LTE_BAND_STRU));

    /*update the bitOp for AreaInfo*/
    pstAreaInfo->bitOpCellId            = NAS_EMMC_BIT_SLCT;
    pstAreaInfo->bitOpPlmnId            = NAS_EMMC_BIT_SLCT;
    pstAreaInfo->bitOpTac               = NAS_EMMC_BIT_SLCT;
    pstAreaInfo->bitOpLteBand           = NAS_EMMC_BIT_SLCT;

    /* 当前TA仍在拒绝原因12的TA内，记录标记，便于服务状态上报 */
    NAS_EMM_GetCurrentTa(&stTa);
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
/* s00193151 mod for GU NAS LAU 停止T3212定时器的问题 end */

    *pulChangeInfo                      = ulChangeInfo;
    *penForbdInfo                       = enForbdInfo;
    *penCellStatus                      = enCellStatus;

    pstAreaInfo->ulArfcn                 = pstLteInfoIndMsg->ulArfcn;
#if (FEATURE_ON == FEATURE_CSG)
    pstAreaInfo->ucCellType             = pstLteInfoIndMsg->enCellType;
    pstAreaInfo->ulCsgId                = pstLteInfoIndMsg->ulCsgId;
#endif
}

/*****************************************************************************
 Function Name   : NAS_EMMC_DeleteForbTa
 Description     : 删除一个禁止TA
 Input           : NAS_MM_PLMN_ID_STRU stPlmnId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_DeleteForbTa
(
    const NAS_MM_TA_STRU               *pstTa,
    NAS_MM_TA_LIST_STRU                *pstTaList
)
{
    NAS_LMM_DeleteTaFromTaList(pstTa, pstTaList, NAS_EMMC_MAX_FORBTA_NUM);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_UpdateForbTaList
 Description     : TAI List发生变化，根据新的TAI List刷新ForbTa for Roaming
                   和ForbTA for RPOS列表，如果ForbTA for Roaming发生变化，发消息
                   通知RRC。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-8-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_UpdateForbTaList( VOS_VOID )
{
    NAS_MM_TA_LIST_STRU                         *pstCurTaiList           = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                         *pstForbTaListForRoaming = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                         *pstForbTaListForRpos    = VOS_NULL_PTR;
    VOS_UINT32                                  ulPriForbTaNum           = 0;
    VOS_UINT32                                  i                        = 0;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enUpdateResult           = NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;
    /* 如果是紧急注册过程中或者紧急注册，则不需要将TAI LIST中的TA从被禁TA列表
       中删除 */
    if ((NAS_LMM_REG_STATUS_EMC_REGING  == NAS_LMM_GetEmmInfoRegStatus())
        || (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus()))
    {
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_UpdateForbTaList:EMC REGED OR EMC REGING!");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_UpdateForbTaList_ENUM
,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /*获取当前的TAI List,ForTA for Roaming,ForbTA for RPOS*/
    pstCurTaiList = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_TA_LIST);
    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaListForRpos = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);

    /* 更新临时Forb列表 */
    enUpdateResult = NAS_LMM_UpdateGradualForbTempTaList();

    /*更新 ForbTA for Roaming,如果变化通知RRC*/
    if(0 != pstForbTaListForRoaming->ulTaNum)
    {
        ulPriForbTaNum = pstForbTaListForRoaming->ulTaNum;
        for(i = 0; i < pstCurTaiList->ulTaNum; ++i)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&(pstCurTaiList->astTa[i]),
                                                              pstForbTaListForRoaming))
            {
                NAS_EMMC_DeleteForbTa(&(pstCurTaiList->astTa[i]),pstForbTaListForRoaming);
            }
        }
        /* Roam ForbTA或者Temp Forb个数发生变化, 通知RRC */
        if((ulPriForbTaNum != pstForbTaListForRoaming->ulTaNum)
            || (NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED == enUpdateResult))
        {
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

        }
    }
    else
    {
        /* Roam ForbTA个数没变化, 但是临时列表个数有变化, 也需要通知RRC */
        if(NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED == enUpdateResult)
        {
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        }
    }

    /*更新 ForbTA for RPOS,如果变化通知RRC*/
    if(0 != pstForbTaListForRpos->ulTaNum)
    {
        for(i = 0; i < pstCurTaiList->ulTaNum; ++i)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&(pstCurTaiList->astTa[i]),
                                                              pstForbTaListForRpos))
            {
                NAS_EMMC_DeleteForbTa(&(pstCurTaiList->astTa[i]),pstForbTaListForRpos);
            }
        }
    }
    /* 当FORB TA LIST为空时,停止Forb定时器 */
    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID))
        &&(0 == pstForbTaListForRoaming->ulTaNum)
        &&(0 == pstForbTaListForRpos->ulTaNum))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID);
    }
    NAS_LMM_EMMC_LOG1_INFO("NAS_EMMC_UpdateForbTaList:ForbTA for RPOS NUM: New :",
                           pstForbTaListForRpos->ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_UpdateForbTaList_ENUM
,LNAS_FUNCTION_LABEL2,
                           pstForbTaListForRpos->ulTaNum);

    return;
}


VOS_VOID  NAS_EMMC_DeleteCurrentAreaCellId( VOS_VOID )
{
    NAS_MM_NETWORK_ID_STRU              *pstAreaInfo;

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    /* 小区的有效取值范围为0~504 ,将小区ID设置为无效 */
    pstAreaInfo->ulCellId               = NAS_EMMC_INVALID_CELLID;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_ProcessRrcAreaLostInd
 Description     : 小区级覆盖区丢失上报处理
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-10-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_ProcessRrcAreaLostInd(VOS_VOID)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_ProcessRrcAreaLostInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessRrcAreaLostInd_ENUM
,LNAS_ENTRY);

    /*上报覆盖区丢失关键事件*/
    NAS_LMM_SendOmtKeyEvent(MM_KEY_EVENT_COVERAGE_LOST);

    /* 删除当前小区 */
    NAS_EMMC_DeleteCurrentAreaCellId();

    return;
}


VOS_VOID NAS_EMMC_ProcessRrcNotCampOnInd(VOS_VOID)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_ProcessRrcNotCampOnInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessRrcNotCampOnInd_ENUM
,LNAS_ENTRY);

    /* 设置Not Camp On标识 */
    NAS_EMMC_SetNotCampOnFlag(VOS_TRUE);

    /*上报覆盖区丢失关键事件*/
    /* NAS_LMM_SendOmtKeyEvent(MM_KEY_EVENT_COVERAGE_LOST); */

    /* 删除当前小区 */
    /* NAS_EMMC_DeleteCurrentAreaCellId(); */

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_IsBgListSearch
 Description     : 判断是否进行背景LIST搜
 Input           : ulSearchType   网侧下发的搜网类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuhua 00212067      2013-02-02  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_IsBgListSearch(MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32 ulSearchType)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_IsBgListSearch is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_IsBgListSearch_ENUM
,LNAS_ENTRY);

    /**
     * 只有当:
     *   - 下发搜索类型为LIST搜，且
     *   - 子状态不为NO_CELL，    且
     *   - 没有收到过Not Camp On消息
     * 时发起的搜索才是背景LIST搜
     */
    if ((MMC_LMM_PLMN_SRCH_LIST == ulSearchType) &&
        (EMM_SS_DEREG_NO_CELL_AVAILABLE != NAS_LMM_GetEmmCurFsmSS()) &&
        (EMM_SS_REG_NO_CELL_AVAILABLE   != NAS_LMM_GetEmmCurFsmSS()) &&
        (VOS_FALSE == NAS_EMMC_GetNotCampOnFlag()))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


/*****************************************************************************
 Function Name   : NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID
 Description     : RRC系统消息上报处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470            2011-08-01   Draft Enact
    2.lihong 00150010      2012-12-22   Modify:DTS2012121306127，系统消息机制变更

*****************************************************************************/
VOS_VOID  NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID
(
    const MMC_LMM_SYS_INFO_STRU          *pstLteInfoIndMsg,
    VOS_UINT32                           *pulChangeInfo
)
{
    VOS_UINT32                          ulChangeInfo = NAS_EMMC_NULL;
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;
    NAS_LMM_NETWORK_INFO_STRU          *pstNetInfo;

    NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_ENTRY);

    pstNetInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);

    pstNetInfo->bitOpPresentNetId = NAS_EMMC_BIT_SLCT;

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);


    /*比较系统消息与UE维护的当前网络信息,获取信息变更类型*/
    if(NAS_LMM_MATCH_FAIL ==
            NAS_LMM_PlmnMatch(&(pstAreaInfo->stPlmnId),
                (NAS_MM_PLMN_ID_STRU *)pstLteInfoIndMsg->stSpecPlmnIdList.astSuitPlmnList))
    {
        ulChangeInfo = ulChangeInfo | NAS_EMMC_BIT_SLCT;
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID: MMC_EMM_CHANGE_PLMN");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_FUNCTION_LABEL1);
    }
    if(NAS_LMM_MATCH_FAIL ==
                NAS_LMM_TacMatch(&(pstAreaInfo->stTac),
                    (NAS_MM_TAC_STRU *)&(pstLteInfoIndMsg->stTac)))
    {
        ulChangeInfo = ulChangeInfo | (NAS_EMMC_BIT_SLCT << 1);
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID: MMC_EMM_CHANGE_TA");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_FUNCTION_LABEL2);
    }
    if (pstAreaInfo->ulCellId != pstLteInfoIndMsg->ulCellId)
    {
        ulChangeInfo  = ulChangeInfo | (NAS_EMMC_BIT_SLCT << 2);
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID: MMC_EMM_CHANGE_CELLID");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_FUNCTION_LABEL3);
    }

    *pulChangeInfo                      = ulChangeInfo;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_GetUserSpecPlmnFlag
 Description     : 获取用户指定搜网标识
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-15  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_GetUserSpecPlmnFlag(VOS_VOID)
{
    NAS_EMMC_GLOBAL_STRU               *pstEmmcInfo;
    NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32  ulUserFlag;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    ulUserFlag = pstEmmcInfo->enUserSpecPlmnFlag;

    return ulUserFlag;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_SetUserSpecPlmnFlag
 Description     : 设置用户指定搜网标识
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-11-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32  ulUserFlag)
{
    NAS_EMMC_GLOBAL_STRU               *pstEmmcInfo;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstEmmcInfo->enUserSpecPlmnFlag = ulUserFlag;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_AddPlmnInRej18PlmnList
 Description     : 把当前PLMN加入到拒绝#18的PLMN列表中
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-12-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_AddPlmnInRej18PlmnList(const NAS_MM_PLMN_ID_STRU *pstPlmnId)
{
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    NAS_LMM_AddPlmnInPlmnList(  pstPlmnId,
                                &pstEmmcInfo->stRej18PlmnList,
                                NAS_MM_MAX_PLMN_NUM);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_PlmnMatchRej18PlmnList
 Description     : 判断输入的PLMN是否在拒绝#18PLMN列表中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-12-16  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_PlmnMatchRej18PlmnList
(
    NAS_MM_PLMN_ID_STRU *pstPlmnId
)
{
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulRslt = NAS_EMM_REJ_NO;
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;

    (void)pstPlmnId;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    ulRslt = NAS_LMM_PlmnIDMatchPlmnList(pstPlmnId,&pstEmmcInfo->stRej18PlmnList);

    if (NAS_LMM_MATCH_SUCCESS == ulRslt)
    {
        ulRslt = NAS_EMM_REJ_YES;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_SetRejCause18Flag
 Description     : 设置当前PLMN在拒绝#18PLMN列表中的标识
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-12-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_SetRejCause18Flag
(
    NAS_EMM_REJ_FLAG_ENUM_UINT32 ulRej18Flag
)
{
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstEmmcInfo->ulRej18Flag = ulRej18Flag;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_GetRejCause18Flag
 Description     : 获取当前PLMN在拒绝#18列表中的标识
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-12-19  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_GetRejCause18Flag(VOS_VOID)
{
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulRej18Flag;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    ulRej18Flag =  pstEmmcInfo->ulRej18Flag;

    NAS_LMM_EMMC_LOG1_INFO("NAS_EMMC_GetRejCause18Flag: ulRej18Flag = ",
                             ulRej18Flag);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_GetRejCause18Flag_ENUM
,LNAS_FUNCTION_LABEL1,
                             ulRej18Flag);
    return ulRej18Flag;
}
/*****************************************************************************
 Function Name   : NAS_EMMC_SndOmLogForbPlmnInfo
 Description     : 勾出被禁PLMN信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-03-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_SndOmLogForbiddenInfo(VOS_VOID)
{
    NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MM_PLMN_LIST_STRU                          stForbPlmn;
    NAS_MM_PLMN_LIST_STRU                          stForbPlmnForGprs;
    NAS_EMMC_GLOBAL_STRU                           *pstEmmcInfo;
    NAS_MM_FORB_TA_LIST_STRU                       *pstForbTaForRoming;
    NAS_MM_FORB_TA_LIST_STRU                       *pstForbTaForRegional;
    NAS_MM_FORB_TA_LIST_STRU                       *pstForbTaForRej15;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST         *pstGradualForbTaList;

    pstGradualForbTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();
    pstForbTaForRoming   = NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr();
    pstForbTaForRegional = NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr();
    pstForbTaForRej15    = NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr();
    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstMsg = (NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_SndOmLogForbPlmnInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_SndOmLogForbiddenInfo_ENUM
,LNAS_NULL_PTR);
        return;
    }


    NAS_LMM_MEM_SET_S(pstMsg, sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU), 0, sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU));
    NAS_LMM_MEM_SET_S(&stForbPlmn,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_SET_S(&stForbPlmnForGprs,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));

    NAS_EMMC_GetForbPlmnInfo(&stForbPlmn,&stForbPlmnForGprs);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_FORBIDDEN_INFO;
    /* 内容赋值 */
    pstMsg->enUserSpecPlmnFlag = pstEmmcInfo->enUserSpecPlmnFlag;
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbPlmn, sizeof(NAS_MM_PLMN_LIST_STRU), &stForbPlmn, sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbPlmnForGprs, sizeof(NAS_MM_PLMN_LIST_STRU), &stForbPlmnForGprs, sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbTaForRoam, sizeof(NAS_MM_FORB_TA_LIST_STRU), pstForbTaForRoming, sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbTaForRpos, sizeof(NAS_MM_FORB_TA_LIST_STRU), pstForbTaForRegional, sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbTaForRej15, sizeof(NAS_MM_FORB_TA_LIST_STRU), pstForbTaForRej15, sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  &pstMsg->stGradualForbTaList,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST),
                        pstGradualForbTaList,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*lint +e961*/
/*lint +e960*/
#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 Function Name   : NAS_EMMC_IsBgCsgListSearch
 Description     : 判断是否进行背景Csg LIST搜
 Input           : none
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272      2015-10-28  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_IsBgCsgListSearch(VOS_VOID)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_IsBgCsgListSearch is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_IsBgCsgListSearch_ENUM,LNAS_ENTRY);

    /**
     * 只有当:
     *   - 下发搜索类型为LIST搜，且
     *   - 子状态不为NO_CELL，    且
     *   - 没有收到过Not Camp On消息
     * 时发起的搜索才是背景LIST搜
     */
    if ((EMM_SS_DEREG_NO_CELL_AVAILABLE != NAS_LMM_GetEmmCurFsmSS()) &&
        (EMM_SS_REG_NO_CELL_AVAILABLE   != NAS_LMM_GetEmmCurFsmSS()) &&
        (VOS_FALSE == NAS_EMMC_GetNotCampOnFlag()))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

