

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasMmlCtx.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcSndLmm.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif
#include "GmmExt.h"
#include "MM_Ext.h"

#include "NasUsimmApi.h"

#include "NasUtranCtrlCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASMML_CTX_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* 保存三个模块共用的CTX */
NAS_MML_CTX_STRU                        g_stNasMmlCtx;

extern NAS_MNTN_MM_INFO_STRU            g_stNasMntnErrorLogMm;

/*****************************************************************************
  6 函数定义
*****************************************************************************/

/*lint -save -e958 */


NAS_MML_CTX_STRU*  NAS_MML_GetMmlCtx( VOS_VOID )
{
    return &(g_stNasMmlCtx);
}


VOS_VOID  NAS_MML_InitCallModeInfoCtx(
    NAS_MML_CALL_MODE_ENUM_UINT8        *penCallMode
)
{
    *penCallMode = NAS_MML_CALL_MODE_BUTT;
}




VOS_VOID  NAS_MML_InitSimStatusInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_SIM_STATUS_STRU             *pstSimStatusInfo
)
{
    if (NAS_MML_INIT_CTX_STARTUP == enInitType)
    {
        pstSimStatusInfo->ucSimPresentStatus  = VOS_FALSE;
        pstSimStatusInfo->enSimType           = NAS_MML_SIM_TYPE_BUTT;
    }

    pstSimStatusInfo->ucSimCsRegStatus    = VOS_FALSE;
    pstSimStatusInfo->ucSimPsRegStatus    = VOS_FALSE;
    pstSimStatusInfo->enCsUpdateStatus    = NAS_MML_LOCATION_UPDATE_STATUS_BUTT;
    pstSimStatusInfo->enPsUpdateStatus    = NAS_MML_ROUTING_UPDATE_STATUS_BUTT;
    /* IMSI REFRESH状态在开关机时都会清除 */
    pstSimStatusInfo->ucImsiRefreshStatus = VOS_FALSE;
}


VOS_VOID  NAS_MML_InitSimMsIdentityInfoCtx(
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity
)
{
    VOS_UINT32                          i;

    /* IMSI内容 */
    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pstMsIdentity->aucImsi[i]           = NAS_MML_IMSI_INVALID;
    }

    /* PTMSI内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
    {
        pstMsIdentity->aucPtmsi[i]          = NAS_MML_PTMSI_INVALID;
    }

    /* PTMSI Signature内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN ; i++ )
    {
        pstMsIdentity->aucPtmsiSignature[i] = NAS_MML_PTMSI_SIGNATURE_INVALID;
    }

    /* Tmsi内容 */
    for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
    {
        pstMsIdentity->aucTmsi[i] = NAS_MML_TMSI_INVALID;
    }

    pstMsIdentity->enUeOperMode     = NAS_MML_SIM_UE_OPER_MODE_BUTT;
}


VOS_VOID  NAS_MML_InitUeIdPtmisInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* PTMSI内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsi[i] = NAS_MML_PTMSI_INVALID;
    }

}


VOS_VOID  NAS_MML_InitUeIdPtmsiSignatureInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* PTMSI SIGNATURE内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsiSignature[i] = NAS_MML_PTMSI_SIGNATURE_INVALID;
    }

}


VOS_VOID  NAS_MML_InitUeIdTmsiInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* PTMSI SIGNATURE内容 */
    for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucTmsi[i] = NAS_MML_TMSI_INVALID;
    }

}


VOS_VOID  NAS_MML_InitSimPsSecurityCtx(
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   *pstPsSecurity
)
{
    VOS_UINT32                          i;

    /* CKSN */
    pstPsSecurity->ucCKSN               = NAS_MML_CKSN_INVALID;

    /* GSM KC */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        pstPsSecurity->aucGsmKc[i]      = NAS_MML_GSMKC_INVALID;
    }

    /* UMTS CK */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        pstPsSecurity->aucUmtsCk[i]      = NAS_MML_CK_INVALID;
    }

    /* UMTS IK */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        pstPsSecurity->aucUmtsIk[i]      = NAS_MML_IK_INVALID;
    }
}



VOS_VOID  NAS_MML_InitPsSecurityGsmKcInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* GSM KC内容无效 */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucGsmKc[i] = NAS_MML_GSMKC_INVALID;
    }

}


VOS_VOID  NAS_MML_InitPsSecurityUmtsCkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsCk[i] = NAS_MML_CK_INVALID;
    }

}


VOS_VOID  NAS_MML_InitPsSecurityUmtsIkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsIk[i] = NAS_MML_IK_INVALID;
    }

}



VOS_VOID  NAS_MML_InitCsSecurityGsmKcInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* GSM KC内容无效 */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucGsmKc[i] = NAS_MML_GSMKC_INVALID;
    }

}


VOS_VOID  NAS_MML_InitCsSecurityUmtsCkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsCk[i] = NAS_MML_CK_INVALID;
    }

}


VOS_VOID  NAS_MML_InitCsSecurityUmtsIkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsIk[i] = NAS_MML_IK_INVALID;
    }

}


VOS_VOID  NAS_MML_InitSimCsSecurityCtx(
    NAS_MML_SIM_CS_SECURITY_INFO_STRU   *pstCsSecurity
)
{
    VOS_UINT32                          i;

    /* CKSN */
    pstCsSecurity->ucCKSN               = NAS_MML_CKSN_INVALID;

    /* GSM KC */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        pstCsSecurity->aucGsmKc[i]      = NAS_MML_GSMKC_INVALID;
    }

    /* UMTS CK */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        pstCsSecurity->aucUmtsCk[i]      = NAS_MML_CK_INVALID;
    }

    /* UMTS IK */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        pstCsSecurity->aucUmtsIk[i]      = NAS_MML_IK_INVALID;
    }
}


VOS_VOID  NAS_MML_InitSimEhPlmnInfo(
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEhPlmnInfo
)
{
    VOS_UINT32                          i;

    pstEhPlmnInfo->ucEhPlmnNum          = 0;
    pstEhPlmnInfo->enPLMNSelInd         = NAS_MML_LAST_RPLMN_SEL_IND_RPLMN;
    pstEhPlmnInfo->enEHplmnPresentInd   = NAS_MML_EHPLMN_PRESENT_IND_NO_PREF;

    pstEhPlmnInfo->enHplmnType          = NAS_MML_HPLMN_TYPE_BUTT;

    for ( i = 0 ; i < NAS_MML_MAX_EHPLMN_NUM ; i++ )
    {
        pstEhPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        pstEhPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
#if (FEATURE_ON == FEATURE_LTE)
        pstEhPlmnInfo->astEhPlmnInfo[i].usSimRat        = NAS_MML_SIM_ALL_RAT_SUPPORT_LTE;
#else
        pstEhPlmnInfo->astEhPlmnInfo[i].usSimRat        = NAS_MML_SIM_ALL_RAT;
#endif

        PS_MEM_SET(pstEhPlmnInfo->astEhPlmnInfo[i].aucReserve,
                   0X00,
                   sizeof(pstEhPlmnInfo->astEhPlmnInfo[i].aucReserve));

    }
}


VOS_VOID  NAS_MML_InitSimHPlmnWithRatInfo(
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU *pstHplmnWithRatInfo
)
{
    VOS_UINT32                          i;

    pstHplmnWithRatInfo->ucHPlmnWithRatNum  = 0;

    for ( i = 0 ; i < NAS_MML_MAX_HPLMN_WITH_RAT_NUM ; i++ )
    {
        pstHplmnWithRatInfo->astHPlmnWithRatInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstHplmnWithRatInfo->astHPlmnWithRatInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstHplmnWithRatInfo->astHPlmnWithRatInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
    }
}

VOS_VOID  NAS_MML_InitSimUserPlmnInfo(
    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnInfo
)
{
    VOS_UINT32                          i;

    pstUserPlmnInfo->ucUserPlmnNum      = 0;

    for ( i = 0 ; i < NAS_MML_MAX_USERPLMN_NUM ; i++ )
    {
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstUserPlmnInfo->astUserPlmnInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
    }
}


VOS_VOID  NAS_MML_InitSimOperPlmnInfo(
    NAS_MML_SIM_OPERPLMN_INFO_STRU      *pstOperPlmnInfo
)
{
    VOS_UINT32                          i;

    pstOperPlmnInfo->usOperPlmnNum = 0;

    for ( i = 0 ; i < NAS_MML_MAX_OPERPLMN_NUM ; i++ )
    {
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstOperPlmnInfo->astOperPlmnInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
    }
}


VOS_VOID  NAS_MML_InitSimSelPlmnInfo(
    NAS_MML_SIM_SELPLMN_INFO_STRU        *pstSelPlmnInfo
)
{
    VOS_UINT32                          i;

    pstSelPlmnInfo->ucSelPlmnNum        = 0;

    for ( i = 0 ; i < NAS_MML_MAX_SELPLMN_NUM ; i++ )
    {
        pstSelPlmnInfo->astPlmnId[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstSelPlmnInfo->astPlmnId[i].ulMnc   = NAS_MML_INVALID_MNC;
    }
}


VOS_VOID  NAS_MML_InitSimForbidPlmnInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo
)
{
    VOS_UINT32                          i;

    pstForbidPlmnInfo->ucForbGprsPlmnNum    = 0;
    pstForbidPlmnInfo->ucForbRegLaNum       = 0;
    pstForbidPlmnInfo->ucForbRoamLaNum      = 0;

    for ( i = 0 ; i < NAS_MML_MAX_FORBGPRSPLMN_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbGprsPlmnList[i].ulMcc = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbGprsPlmnList[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    for ( i = 0 ; i < NAS_MML_MAX_FORBLA_FOR_ROAM_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstForbidPlmnInfo->astForbRomLaList[i].aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstForbidPlmnInfo->astForbRomLaList[i].aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    for ( i = 0 ; i < NAS_MML_MAX_FORBLA_FOR_REG_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbRegLaList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbRegLaList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstForbidPlmnInfo->astForbRegLaList[i].aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstForbidPlmnInfo->astForbRegLaList[i].aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    NAS_MML_InitForbLaWithValidPeriodList(&pstForbidPlmnInfo->stForbLaWithValidPeriod);

    /* 关机情况下不能清理forbid plmn信息 */
    if ( NAS_MML_INIT_CTX_POWEROFF == enInitType )
    {
        return;
    }

    pstForbidPlmnInfo->ucUsimForbPlmnNum    = 0;
    pstForbidPlmnInfo->ucForbPlmnNum        = 0;
    for ( i = 0 ; i < NAS_MML_MAX_FORBPLMN_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }


}


VOS_VOID NAS_MML_InitForbLaWithValidPeriodCfg(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
)
{
    VOS_UINT32                          i;

    pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum = 0;

    for ( i = 0 ; i < NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM ; i++ )
    {
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause              = NAS_MML_REG_FAIL_CAUSE_BUTT;
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen      = 0;
    }
    return;
}


VOS_VOID  NAS_MML_InitForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod

)
{
    VOS_UINT32                          i;

    pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum = 0;
    for ( i = 0 ; i < NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM ; i++ )
    {
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.stPlmnId.ulMcc             = NAS_MML_INVALID_MCC;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.stPlmnId.ulMnc             = NAS_MML_INVALID_MNC;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.aucLac[0]                  = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.aucLac[1]                  = NAS_MML_LAC_HIGH_BYTE_INVALID;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodBeginTick                      = 0;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodTick                           = NAS_MML_MAX_TIME_TICK;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].enCsRegFailCause                                      = NAS_MML_REG_FAIL_CAUSE_BUTT;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodPunishBeginTick                = 0;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodPunishDurationTick             = NAS_MML_MAX_TIME_TICK;
    }
    return;
}


NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU* NAS_MML_GetForbLaWithValidPeriodCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stForbLaWithValidPeriodCfg);
}


NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU* NAS_MML_GetForbLaWithValidPeriodList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stForbidPlmnInfo.stForbLaWithValidPeriod);
}



VOS_VOID NAS_MML_SetKeepCsForbInfoCfg(
    VOS_UINT8                           ucKeepCsForbInfoFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepCsForbInfoFlg = ucKeepCsForbInfoFlg;
}


VOS_UINT8 NAS_MML_GetKeepCsForbInfoCfg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepCsForbInfoFlg);
}



VOS_VOID NAS_MML_SetNwIgnoreAuthFailCfg(
    VOS_UINT8                           ucNwIgnoreAuthFailFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucNwIgnoreAuthFailFlg = ucNwIgnoreAuthFailFlg;
}


VOS_UINT8 NAS_MML_GetNwIgnoreAuthFailCfg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucNwIgnoreAuthFailFlg);
}


VOS_VOID NAS_MML_InitAuthInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_AUTH_INFO_STRU *pstAuthInfo
)
{
    PS_MEM_SET(pstAuthInfo->aucReserved, 0x00, sizeof(pstAuthInfo->aucReserved));

    /* 以下全局变量只有在上电时需要初始化，关机时不需要初始化 */
    if (NAS_MML_INIT_CTX_STARTUP == enInitType)
    {
        pstAuthInfo->ucUsimDoneGsmCsAuthFlg           = VOS_FALSE;
        pstAuthInfo->ucUsimDoneGsmPsAuthFlg           = VOS_FALSE;
    }

    return;
}



VOS_VOID NAS_MML_InitUsimGsmAuthCfgInfo(
    NAS_MML_CLEAR_CKSN_CFG_STRU *pstUsimGsmAuthCfg
)
{
    PS_MEM_SET(pstUsimGsmAuthCfg, 0x00, sizeof(NAS_MML_CLEAR_CKSN_CFG_STRU));

    pstUsimGsmAuthCfg->ucNwIgnoreAuthFailFlg      = VOS_FALSE;

    pstUsimGsmAuthCfg->ucUsimGsmAuthNvCfg         = VOS_FALSE;
    
    return;
}



VOS_UINT32 NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth(VOS_VOID)
{
    VOS_UINT8                           ucUsimDoneGsmCsAuthFlg;
    
    ucUsimDoneGsmCsAuthFlg              = NAS_MML_GetUsimDoneGsmCsAuthFlg();

    /* 非测试卡USIM卡，USIM卡在GSM下做过2G鉴权标记，在进行3G鉴权时，需要清除 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA     == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE                       == ucUsimDoneGsmCsAuthFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;    
}



VOS_UINT32 NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth(VOS_VOID)
{
    VOS_UINT8                           ucUsimDoneGsmPsAuthFlg;
    
    ucUsimDoneGsmPsAuthFlg              = NAS_MML_GetUsimDoneGsmPsAuthFlg();

    /* 非测试卡USIM卡，USIM卡在GSM下做过2G鉴权标记，在进行3G鉴权时，需要清除 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA     == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE                       == ucUsimDoneGsmPsAuthFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;  
}



VOS_UINT32 NAS_MML_IsNeedSetUsimDoneGsmAuthFlg(VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    VOS_UINT8                           ucUsimGsmAuthCfg;
    
    ucSimType                           = NAS_MML_GetSimType();
    ucUsimGsmAuthCfg                    = NAS_MML_GetUsimGsmAuthNvCfg();

    /* 非测试卡USIM卡，USIM卡在GSM下做2G鉴权标记，以便在进行3G鉴权时清除CKSN */
    if ((NAS_MML_NET_RAT_TYPE_GSM       == NAS_MML_GetCurrNetRatType())
     && (NAS_MML_SIM_TYPE_USIM          == ucSimType)
     && (VOS_TRUE                       == ucUsimGsmAuthCfg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;    
}


VOS_VOID NAS_MML_SetUsimGsmAuthNvCfg(
    VOS_UINT8                           ucUsimGsmCsAuthNvCfg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucUsimGsmAuthNvCfg = ucUsimGsmCsAuthNvCfg;
}


VOS_UINT8 NAS_MML_GetUsimGsmAuthNvCfg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucUsimGsmAuthNvCfg);
}


VOS_VOID NAS_MML_SetUsimDoneGsmCsAuthFlg(
    VOS_UINT8                           ucUsimDoneGsmCsAuthFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmCsAuthFlg = ucUsimDoneGsmCsAuthFlg;
}


VOS_UINT8 NAS_MML_GetUsimDoneGsmCsAuthFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmCsAuthFlg);
}



VOS_VOID NAS_MML_SetUsimDoneGsmPsAuthFlg(
    VOS_UINT8                           ucUsimDoneGsmPsAuthFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmPsAuthFlg = ucUsimDoneGsmPsAuthFlg;
}


VOS_UINT8 NAS_MML_GetUsimDoneGsmPsAuthFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmPsAuthFlg);
}



VOS_VOID  NAS_MML_InitSimPlmnInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_PLMN_INFO_STRU         *pstSimStatusInfo
)
{
    /* 关机情况下不需要清空内存中SIM相关变量 */
    if (NAS_MML_INIT_CTX_STARTUP  == enInitType )
    {
        NAS_MML_InitSimEhPlmnInfo(&(pstSimStatusInfo->stEhPlmnInfo));

        NAS_MML_InitSimHPlmnWithRatInfo(&(pstSimStatusInfo->stHplmnWithRatInfo));

        NAS_MML_InitSimUserPlmnInfo(&(pstSimStatusInfo->stUserPlmnInfo));

        NAS_MML_InitSimOperPlmnInfo(&(pstSimStatusInfo->stOperPlmnInfo));

        NAS_MML_InitSimSelPlmnInfo(&(pstSimStatusInfo->stSelPlmnInfo));

        NAS_MML_SetUsimMncLen(NAS_MML_MNC_LENGTH_THREE_BYTES_IN_IMSI);

        NAS_MML_SetCsgDisplayCtrlFlag(VOS_FALSE);

    }

    NAS_MML_InitSimForbidPlmnInfo(enInitType, &(pstSimStatusInfo->stForbidPlmnInfo));

}


VOS_VOID  NAS_MML_InitSimInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_INFO_STRU              *pstSimInfo
)
{
    NAS_MML_InitSimStatusInfoCtx(enInitType, &(pstSimInfo->stSimStatus));

    NAS_MML_InitSimMsIdentityInfoCtx(&(pstSimInfo->stMsIdentity));

    NAS_MML_InitSimPsSecurityCtx(&(pstSimInfo->stPsSecurity));

    NAS_MML_InitSimCsSecurityCtx(&(pstSimInfo->stCsSecurity));

    NAS_MML_InitSimPlmnInfoCtx(enInitType, &(pstSimInfo->stSimPlmnInfo));
    NAS_MML_InitCallModeInfoCtx(&(pstSimInfo->enCallMode));

    NAS_MML_InitSimCsgInfo(&pstSimInfo->stSimCsgInfo);
}


VOS_VOID  NAS_MML_InitMs3GppRel(
    NAS_MML_MS_3GPP_REL_STRU               *pstMs3GppRel
)
{
    pstMs3GppRel->enMsGsmRel    =   NAS_MML_3GPP_REL_R4;
    pstMs3GppRel->enMsWcdmaRel  =   NAS_MML_3GPP_REL_R6;
    pstMs3GppRel->enMsMscRel    =   NAS_MML_MSC_REL_R99;
    pstMs3GppRel->enMsSgsnRel   =   NAS_MML_SGSN_REL_R99;
    pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R9;
}


VOS_VOID  NAS_MML_InitPlatformBandCap(
    NAS_MML_PLATFORM_BAND_CAP_STRU     *pstPlatformBandCapability
)
{
    PS_MEM_SET(pstPlatformBandCapability, 0, sizeof(NAS_MML_PLATFORM_BAND_CAP_STRU));
}


VOS_VOID  NAS_MML_InitMsCapability(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability
)
{
    VOS_UINT8                          i;

    pstMsCapability->ucClassmark1               =   NAS_MML_DEFAULT_CLASSMARK1_VALUE;

    pstMsCapability->aucClassmark2[0]           =   NAS_MML_DEFAULT_CLASSMARK2_FIRST_VALUE;
    pstMsCapability->aucClassmark2[1]           =   NAS_MML_DEFAULT_CLASSMARK2_SECOND_VALUE;
    pstMsCapability->aucClassmark2[2]           =   NAS_MML_DEFAULT_CLASSMARK2_THIRD_VALUE;
    pstMsCapability->aucClassmark2[3]           =   NAS_MML_DEFAULT_CLASSMARK2_FOURTH_VALUE;

    PS_MEM_SET(pstMsCapability->aucFddClassmark3, 0x0, NAS_MML_CLASSMARK3_LEN);
    PS_MEM_SET(pstMsCapability->aucTddClassmark3, 0x0, NAS_MML_CLASSMARK3_LEN);

    pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen     =   NAS_MML_DEFAULT_NETWORKCAPABILITY_LEN;

    PS_MEM_SET(pstMsCapability->stMsNetworkCapability.aucNetworkCapability, 0, NAS_MML_MAX_NETWORK_CAPABILITY_LEN);

    pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0]    =   NAS_MML_DEFAULT_NETWORKCAPABILITY_FIRST_VALUE;
    pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1]    =   NAS_MML_DEFAULT_NETWORKCAPABILITY_SECOND_VALUE;

    for ( i = 0 ; i < NAS_MML_MAX_IMEISV_LEN ; i++ )
    {
        pstMsCapability->aucImeisv[i]           =   i;

        /* 后面的字段填写默认值 */
        if ( i >= 10 )
        {
            pstMsCapability->aucImeisv[i]       = NAS_MML_DEFAULT_IMEI_VALUE;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    PS_MEM_SET(pstMsCapability->stUeNetworkCapbility.aucUeNetCap, 0, NAS_MML_MAX_UE_NETWORK_CAPABILITY_LEN);
    pstMsCapability->stUeNetworkCapbility.ucUeNetCapLen  = NAS_MML_DEFAULT_UE_NETWORK_CAPABILITY_LEN;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[0] = NAS_MML_DEFAULT_UE_NET_CAP_FIRST_VALUE;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[1] = NAS_MML_DEFAULT_UE_NET_CAP_FIRST_VALUE;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[2] = NAS_MML_DEFAULT_UE_NET_CAP_THIRD_VALUE;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[3] = NAS_MML_DEFAULT_UE_NET_CAP_THIRD_VALUE;
#endif

    /* 初始化为GSM only */
    for (i = 0; i < NAS_MML_MAX_PLATFORM_RAT_NUM; i++)
    {
        pstMsCapability->stPlatformRatCap.aenRatPrio[i] = NAS_MML_PLATFORM_RAT_TYPE_BUTT;
    }
    pstMsCapability->stPlatformRatCap.ucRatNum      = NAS_MML_MIN_PLATFORM_RAT_NUM;
    pstMsCapability->stPlatformRatCap.aenRatPrio[0] = NAS_MML_PLATFORM_RAT_TYPE_GSM;


    NAS_MML_InitPlatformBandCap(&(pstMsCapability->stPlatformBandCap));
}


VOS_VOID  NAS_MML_InitMsSysCfgInfo(
    NAS_MML_MS_SYS_CFG_INFO_STRU        *pstMsSysCfgInfo
)
{
    pstMsSysCfgInfo->enMsMode                   = NAS_MML_MS_MODE_PS_CS;
    pstMsSysCfgInfo->ucPsAutoAttachFlg          = VOS_TRUE;
#if   (FEATURE_ON == FEATURE_LTE)
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = NAS_MML_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_LTE;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[2]= NAS_MML_NET_RAT_TYPE_GSM;
#else
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = NAS_MML_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_GSM;
#endif

    pstMsSysCfgInfo->st3Gpp2RatList.ucRatNum      = 0x0;
    pstMsSysCfgInfo->st3Gpp2RatList.aucRatPrio[0] = NAS_MML_3GPP2_RAT_TYPE_BUTT;
    pstMsSysCfgInfo->st3Gpp2RatList.aucRatPrio[1] = NAS_MML_3GPP2_RAT_TYPE_BUTT;

    /* GSM的支持的Band */
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm1800= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm1900= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm450 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm480 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm700 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm850 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsmE900= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsmP900= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsmR900= VOS_FALSE;

    /* WCDMA的支持的Band */
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_III_1800 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_II_1900  = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_IV_1700  = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_IX_J1700 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_I_2100   = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_VIII_900 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_VII_2600 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_VI_800   = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_V_850    = VOS_TRUE;

    /* LTE的支持的Band */
    pstMsSysCfgInfo->stMsBand.stLteBand.aulLteBand[0] = NAS_MML_LTE_ALL_BAND_SUPPORTED;
    pstMsSysCfgInfo->stMsBand.stLteBand.aulLteBand[1] = NAS_MML_LTE_ALL_BAND_SUPPORTED;

#if   (FEATURE_ON == FEATURE_LTE)
    /* 设置LTE的能力默认为ENABLE状态 */
    NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_BUTT);

    /* 设置LTE的CS业务配置能力默认为不激活 */
    NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_BUTT);

    /* 初始化UE USAGE为无效值   */
    NAS_MML_SetLteUeUsageSetting(NAS_MML_LTE_UE_USAGE_SETTIN_BUTT);

    /* 初始化VOICE DOMAIN PREFERENCE为无效值 */
     NAS_MML_SetVoiceDomainPreference(NAS_MML_VOICE_DOMAIN_PREFER_BUTT);

    /* 初始化IMS不支持 */
    NAS_MML_SetLteImsSupportFlg(VOS_FALSE);
    NAS_MML_SetVoiceCallOnImsSupportFlag(VOS_FALSE);
    NAS_MML_SetSmsOnImsSupportFlag(VOS_FALSE);
    NAS_MML_SetVideoCallOnImsSupportFlag(VOS_FALSE);
    NAS_MML_SetUssdOnImsSupportFlag(VOS_FALSE);

    NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);

#endif

    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_TRUE);
}


VOS_VOID  NAS_MML_InitRplmnCfgInfo(
    NAS_MML_RPLMN_CFG_INFO_STRU         *pstRplmnCfg
)
{
    VOS_UINT32                          i;

    pstRplmnCfg->enTinType              = NAS_MML_TIN_TYPE_INVALID;
    pstRplmnCfg->ucMultiRATRplmnFlg     = VOS_FALSE;
    pstRplmnCfg->ucLastRplmnRatFlg      = VOS_FALSE;
    pstRplmnCfg->enLastRplmnRat         = NAS_MML_NET_RAT_TYPE_BUTT;
    pstRplmnCfg->stGRplmnInNV.ulMcc     = NAS_MML_INVALID_MCC;
    pstRplmnCfg->stGRplmnInNV.ulMnc     = NAS_MML_INVALID_MNC;
    pstRplmnCfg->stWRplmnInNV.ulMcc     = NAS_MML_INVALID_MCC;
    pstRplmnCfg->stWRplmnInNV.ulMnc     = NAS_MML_INVALID_MNC;

    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pstRplmnCfg->aucLastImsi[i]    = NAS_MML_IMSI_INVALID;
    }
}



VOS_VOID  NAS_MML_InitHplmnCfgInfo(
    NAS_MML_HPLMN_CFG_INFO_STRU         *pstHplmnCfg
)
{
    pstHplmnCfg->enAutoSearchHplmnFlg   = NAS_MML_AUTO_SRCH_FLG_TYPE_HPLMN_FIRST;
    pstHplmnCfg->ucEhplmnSupportFlg     = VOS_TRUE;
    pstHplmnCfg->ucHplmnSearchPowerOn   = VOS_FALSE;
    pstHplmnCfg->ucManualSearchHplmnFlg = VOS_TRUE;

    pstHplmnCfg->stPrioHplmnActCfg.ucActiveFlg              = VOS_FALSE;
    pstHplmnCfg->stPrioHplmnActCfg.usPrioHplmnAct           = NAS_MML_SIM_NO_RAT;

    pstHplmnCfg->ucActingHPlmnSupportFlg                    = VOS_FALSE;

    pstHplmnCfg->ucAddEhplmnWhenSrchHplmnFlg                = VOS_FALSE;

    NAS_MML_InitUserCfgExtEHplmnInfo( &(pstHplmnCfg->stUserCfgExtEhplmnInfo) );
}


VOS_VOID  NAS_MML_InitAisRoamingCfg(
    NAS_MML_AIS_ROAMING_CFG_STRU        *pstAisRoamingCfg
)
{
    pstAisRoamingCfg->ucEnableFlg               = VOS_FALSE;
    pstAisRoamingCfg->enHighPrioRatType         = NAS_MML_NET_RAT_TYPE_BUTT;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMcc    = NAS_MML_INVALID_MCC;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMnc    = NAS_MML_INVALID_MNC;
    pstAisRoamingCfg->stSimHPlmnId.ulMcc        = NAS_MML_INVALID_MCC;
    pstAisRoamingCfg->stSimHPlmnId.ulMnc        = NAS_MML_INVALID_MNC;
}


VOS_VOID  NAS_MML_InitRoamCfgInfo(
    NAS_MML_ROAM_CFG_INFO_STRU          *pstRoamCfg
)
{
    pstRoamCfg->enRoamCapability            = NAS_MML_ROAM_NATION_OFF_INTERNATION_OFF;
    pstRoamCfg->ucRoamFeatureFlg            = VOS_FALSE;
    pstRoamCfg->ucNationalRoamNum           = NAS_MML_DFAULT_NATIONAL_ROAM_PLMN_NUM;
    pstRoamCfg->ucNotRoamNum                = NAS_MML_DFAULT_NOT_ROAM_PLMN_NUM;
    pstRoamCfg->astRoamPlmnIdList[0].ulMcc  = NAS_MML_DFAULT_NATIONAL_ROAM_MCC;
    pstRoamCfg->astRoamPlmnIdList[0].ulMnc  = NAS_MML_DFAULT_NATIONAL_ROAM_MNC;


    NAS_MML_InitAisRoamingCfg(&(pstRoamCfg->stAisRoamingCfg));
}


VOS_VOID  NAS_MML_InitBgSearchCfgInfo(
    NAS_MML_BG_SEARCH_CFG_INFO_STRU     *pstBgSearchCfg
)
{
    pstBgSearchCfg->ucEnhancedHplmnSrchFlg                             = VOS_FALSE;
    pstBgSearchCfg->ucSpecialRoamFlg                                   = VOS_FALSE;
    pstBgSearchCfg->ulFirstStartHplmnTimerLen                          = TI_NAS_MMC_HPLMN_TIMER_FIRST_LEN;                                /* 默认为2分钟 */
    pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ucNvimActiveFlg       = VOS_FALSE;
    pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ulDefaultMaxHplmnLen  = TI_NAS_MMC_DEFAULT_MAX_SEARCH_HPLMN_LEN;
    pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg         = VOS_FALSE;
    pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen = TI_NAS_MMC_HPLMN_TIMER_FIRST_LEN;
    pstBgSearchCfg->ucScanCtrlFlg                                      = VOS_FALSE;

    pstBgSearchCfg->stBgSearchRegardlessMcc.ucCustomMccNum             = 0;

    NAS_MML_InitHighPrioRatHplmnTimerCfgInfo(&(pstBgSearchCfg->stHighRatHplmnTimerCfg));

    NAS_MML_InitHighPrioPlmnRefreshTriggerBGSearchCfgInfo(&pstBgSearchCfg->stHighPrioPlmnRefreshTriggerBGSearchCfg);
}



VOS_VOID  NAS_MML_InitRoamingRejectNoRetryInfo(
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU           *pstRetryInfo
)
{
    pstRetryInfo->aucReserve[0]                    = 0;
    pstRetryInfo->aucReserve[1]                    = 0;
    pstRetryInfo->aucReserve[2]                    = 0;
    pstRetryInfo->ucNoRetryRejectCauseNum          = 0;
    pstRetryInfo->aucNoRetryRejectCause[0]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[1]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[2]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[3]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[4]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[5]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[6]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[7]         = 0;

    return;
}


VOS_VOID  NAS_MML_InitPlmnLockCfgInfo(
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU     *pstPlmnLockCfg
)
{
    VOS_UINT32                          i;

    /* 初始化锁网黑名单信息 */
    pstPlmnLockCfg->ucBlackPlmnLockNum  = 0;
    for ( i = 0 ; i < NAS_MML_MAX_BLACK_LOCK_PLMN_NUM; i++ )
    {
        pstPlmnLockCfg->astBlackPlmnId[i].ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnLockCfg->astBlackPlmnId[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    /* 初始化锁网白名单信息 */
    pstPlmnLockCfg->ucWhitePlmnLockNum  = 0;
    for ( i = 0 ; i < NAS_MML_MAX_WHITE_LOCK_PLMN_NUM; i++ )
    {
        pstPlmnLockCfg->astWhitePlmnId[i].ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnLockCfg->astWhitePlmnId[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    NAS_MML_InitDisabledRatPlmnCfgInfo(&(pstPlmnLockCfg->stDisabledRatPlmnInfo));
}


VOS_VOID  NAS_MML_InitRatForbiddenList(
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList
)
{
    VOS_UINT32                          i;

    pstRatBlackList->enSwitchFlag       = NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE;
    pstRatBlackList->ucImsiListNum      = 0;
    pstRatBlackList->ucForbidRatNum     = 0;

    for (i = 0; i < NAS_MML_MAX_IMSI_FORBIDDEN_LIST_NUM; i++)
    {
        pstRatBlackList->astImsiList[i].ulMcc = NAS_MML_INVALID_MCC;
        pstRatBlackList->astImsiList[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    for (i = 0; i < NAS_MML_MAX_RAT_FORBIDDEN_LIST_NUM; i++)
    {
        pstRatBlackList->aenForbidRatList[i] = NAS_MML_NET_RAT_TYPE_BUTT;
    }

}


VOS_VOID  NAS_MML_InitRatForbiddenStatusCfg(
    NAS_MML_RAT_FORBIDDEN_STATUS_STRU  *pstRatCapaStatus
)
{
   pstRatCapaStatus->ucIsImsiInForbiddenListFlg = VOS_FALSE;
   pstRatCapaStatus->ucGsmCapaStatus            = NAS_MML_RAT_CAPABILITY_STATUS_BUTT;
   pstRatCapaStatus->ucLteCapaStatus            = NAS_MML_RAT_CAPABILITY_STATUS_BUTT;
   pstRatCapaStatus->ucUtranCapaStatus          = NAS_MML_RAT_CAPABILITY_STATUS_BUTT;
}



VOS_VOID  NAS_MML_InitDisabledRatPlmnCfgInfo(
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg
)
{
    /* 初始化带禁止接入技术的PLMN信息 */
    VOS_UINT32                          i;

    /* 初始化禁止接入技术的PLMN信息 */
    pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum = 0;

    for ( i = 0 ; i < NAS_MML_MAX_DISABLED_RAT_PLMN_NUM; i++ )
    {
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].stPlmnWithRat.enRat = NAS_MML_NET_RAT_TYPE_BUTT;

        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].ulPlmnDisabledForbiddenSlice   = NAS_MML_MAX_TIME_SLICE;
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].ulPlmnDisabledBeginSlice = 0;

        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].enDisableLteReason = MMC_LMM_DISABLE_LTE_REASON_BUTT;
    }
}




VOS_VOID  NAS_MML_InitUserCfgExtEHplmnInfo(
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU  *pstUserCfgExtEhplmnInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM; i++)
    {

        /* 初始化IMSI的PLMN LIST信息个数为0  */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].ucImsiPlmnListNum = 0;
        PS_MEM_SET( pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astImsiPlmnList,
                    (VOS_UINT8)0X00,
                    sizeof(pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astImsiPlmnList));

        /* 初始化EHPLMN信息个数为0  */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].ucEhplmnListNum = 0;
        PS_MEM_SET( pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astEhPlmnList,
                    (VOS_UINT8)0X00,
                    sizeof(pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astEhPlmnList));

        /* 初始化保留字段为0 */
        PS_MEM_SET( pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].aucResv,
                    (VOS_UINT8)0X00,
                    sizeof(pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].aucResv));
    }
    return;

}



VOS_VOID  NAS_MML_InitMiscellaneousCfgInfo(
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfg
)
{
    pstMiscellaneousCfg->ucCsRejSearchSupportFlg            = VOS_FALSE;
    pstMiscellaneousCfg->ucStkSteeringOfRoamingSupportFlg   = VOS_TRUE;
    pstMiscellaneousCfg->ucMaxForbRoamLaFlg                 = VOS_FALSE;
    pstMiscellaneousCfg->ucMaxForbRoamLaNum                 = NAS_MML_DEFAULT_MAX_FORB_ROAM_LA_NUM;
    pstMiscellaneousCfg->ucNvGsmForbidFlg                   = VOS_FALSE;
    pstMiscellaneousCfg->ucRoamBrokerActiveFlag             = VOS_FALSE;
    pstMiscellaneousCfg->ucRoamBrokerRegisterFailCnt        = NAS_MML_MAX_CS_REG_FAIL_CNT;
    pstMiscellaneousCfg->ucSingleDomainFailPlmnSrchFlag     = VOS_FALSE;

    pstMiscellaneousCfg->stSingleDomainFailActionCtx.ucActiveFlag  = VOS_FALSE;
    pstMiscellaneousCfg->stSingleDomainFailActionCtx.ucCount       = 0;

    pstMiscellaneousCfg->ucRegFailNetWorkFailureCustomFlg          = VOS_FALSE;

    pstMiscellaneousCfg->ucCsOnlyDataServiceSupportFlg        = VOS_TRUE;

    NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_FALSE);

    NAS_MML_InitSorAdditionalLauCtx();
}


VOS_VOID  NAS_MML_InitCustomCfgInfo(
    NAS_MML_CUSTOM_CFG_INFO_STRU        *pstCustomCfg
)
{
    NAS_MML_InitRplmnCfgInfo(&(pstCustomCfg->stRplmnCfg));

    NAS_MML_InitHplmnCfgInfo(&(pstCustomCfg->stHplmnCfg));

    NAS_MML_InitRoamCfgInfo(&(pstCustomCfg->stRoamCfg));

    NAS_MML_InitBgSearchCfgInfo(&(pstCustomCfg->stBgSearchCfg));

    NAS_MML_InitPlmnLockCfgInfo(&(pstCustomCfg->stPlmnLockCfg));
    NAS_MML_SetHoWaitSysinfoTimerLen(NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE);

    NAS_MML_InitMiscellaneousCfgInfo(&(pstCustomCfg->stMiscellaneousCfg));

#if (FEATURE_ON == FEATURE_LTE)
    /* 默认允许LTE国际漫游 */
    NAS_MML_SetLteRoamAllowedFlg(VOS_TRUE);
#endif

    NAS_MML_SetDailRejectCfg(VOS_FALSE);


    NAS_MML_InitChangeNWCauseInfo(&(pstCustomCfg->stChangeNWCauseInfo));
    NAS_MML_InitRoamingRejectNoRetryInfo(&(pstCustomCfg->stRoamingRejectNoRetryInfo));

    NAS_MML_SetUserAutoReselActiveFlg(VOS_FALSE);

    NAS_MML_InitHplmnAuthRejCounter(&(pstCustomCfg->stIgnoreAuthRejInfo));


    NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(VOS_FALSE);

    NAS_MML_SetPlmnExactlyComparaFlg(VOS_FALSE);

    /* 默认支持cs语音业务 */
    NAS_MML_SetSupportCsServiceFLg(VOS_TRUE);

    NAS_MML_SetHplmnRegisterCtrlFlg(VOS_FALSE);

    /* 默认支持H3G定制特性 */
    NAS_MML_SetH3gCtrlFlg(VOS_TRUE);

#if (FEATURE_ON == FEATURE_LTE)
    /* 默认enable lte定时器时长为0分钟 */
    NAS_MML_SetCsfbEmgCallEnableLteTimerLen(0);

    NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(0);

    NAS_MML_SetDisableLteStartT3402EnableLteFlag(VOS_FALSE);
    NAS_MML_SetHighPrioRatBgEnableLteFlag(NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_ENABLE_LTE);


    NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(0);

    /* 默认支持ISR */
    NAS_MML_SetIsrSupportFlg(VOS_TRUE);
    NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(VOS_FALSE);

    NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(VOS_FALSE);

    NAS_MML_SetIsDelFddBandSwitchOnFlg(VOS_FALSE);
#endif

    NAS_MML_SetCsgSupportFlag(VOS_FALSE);
    NAS_MML_SetOnlyReportOperatorCsgListFlag(VOS_FALSE);

    /* 默认不支持SVLTE特性 */
    NAS_MML_SetSvlteSupportFlag(VOS_FALSE);

    NAS_MML_SetPsTransferOffAreaModeFlag(VOS_FALSE);

    NAS_MML_SetDsdsRfShareFlg(VOS_FALSE);

    /* 默认不支持接入禁止发起PLMN搜网特性 */
    NAS_MML_SetSupportAccBarPlmnSearchFlg(VOS_FALSE);

    NAS_MML_InitUserCfgOPlmnInfo(&(pstCustomCfg->stUserCfgOPlmnInfo));

    NAS_MML_InitRatForbiddenList(&(pstCustomCfg->stRatForbiddenListInfo));
    NAS_MML_InitRatForbiddenStatusCfg(&(pstCustomCfg->stRatFirbiddenStatusCfg));
    NAS_MML_SetImsVoiceInterSysLauEnableFlg(VOS_FALSE);
    NAS_MML_SetImsVoiceMMEnableFlg(VOS_FALSE);

    NAS_MML_SetLcEnableFlg(VOS_FALSE);

    /* ultra flash csfb不支持，FR NV打开时，MO电话CSFB，CS域HO到GU,mm在connective active不处理系统消息，
       等链接释放之后再重新驻留才能处理。而如果FR打开，链接释放之后不会驻留，而是FR回LTE，导致电话失败 */
    NAS_MML_SetUltraFlashCsfbSupportFlg(VOS_TRUE);

    NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_TRUE);

    NAS_MML_InitDsdsSessionEndDelay(&(pstCustomCfg->stDsdsEndSesssionDelay));

    NAS_MML_SetSupportSrvccFlg(VOS_FALSE);

    NAS_MML_SetRelPsSigConFlg(VOS_FALSE);
    NAS_MML_SetRelPsSigConCfg_T3340TimerLen(0);

    NAS_MML_SetPdpExistNotStartT3340Flag(VOS_TRUE);


    /* 默认当前不是DSDS多卡 */
    NAS_MML_SetDsdsMultiModemModeFlg(VOS_FALSE);

    NAS_MML_InitDamPlmnInfoCfg(&pstCustomCfg->stDamPlmnInfoCfg);

    /* 设置enable lte触发搜网标识为VOS_FALSE */
    NAS_MML_SetEnableLteTrigPlmnSearchFlag(VOS_FALSE);
    NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_FALSE);
    NAS_MML_SetCsmoSupportedFlg(VOS_FALSE);

    NAS_MML_InitT3212TimerCfgInfo(&(pstCustomCfg->stT3212Info));

    NAS_MML_SetHplmnInEplmnDisplayHomeFlg(VOS_FALSE);

    NAS_MML_SetProtectMtCsfbPagingProcedureLen(NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_DEFAULT_LEN);

    NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(VOS_TRUE);

    NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_FALSE);
    NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_FALSE);
    NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_FALSE);
    NAS_MML_InitCarryEplmnWhenSrchRplmnCfg(&(pstCustomCfg->stCarryEplmnWhenSrchRplmnCfg));
    NAS_MML_InitLauRejNoRetryWhenCmSrvExistCfg(&(pstCustomCfg->stLauRejNoRetryWhenCmSrvExistCfgInfo));
    NAS_MML_InitLauRejTrigPlmnSearchCfg(&(pstCustomCfg->stLauRejTrigPlmnSearchCfg));

    NAS_MML_InitGetGeoPrioRatList(&(pstCustomCfg->stGetGeoPrioRatList));

    NAS_MML_InitLteOos2GPrefPlmnSelCfg(&(pstCustomCfg->stLteOos2GPrefPlmnSelCfg));

    NAS_MML_InitForbLaWithValidPeriodCfg(&(pstCustomCfg->stForbLaWithValidPeriodCfg));

    NAS_MML_SetKeepCsForbInfoCfg(VOS_FALSE);

    NAS_MML_InitUsimGsmAuthCfgInfo(&(pstCustomCfg->stCleanCksnCfg));
    
    return;
}



VOS_VOID  NAS_MML_InitMsCfgCtx(
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfgInfo
)
{
    NAS_MML_InitMs3GppRel(&(pstMsCfgInfo->stMs3GppRel));

    NAS_MML_InitMsCapability(&(pstMsCfgInfo->stMsCapability));

    NAS_MML_InitMsSysCfgInfo(&(pstMsCfgInfo->stMsSysCfgInfo));

    NAS_MML_InitCustomCfgInfo(&(pstMsCfgInfo->stCustomCfg));
}

VOS_VOID NAS_MML_InitCampRai(
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo
)
{
    /* 将当前驻留PLMN，LAI,RAC更新为无效值 */
    pstCampPlmnInfo->stLai.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstCampPlmnInfo->stLai.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstCampPlmnInfo->stLai.aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCampPlmnInfo->stLai.aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstCampPlmnInfo->ucRac                = NAS_MML_RAC_INVALID;

    return;
}

VOS_VOID NAS_MML_InitRssiValue(
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo
)
{
    VOS_UINT8                           i;
    pstCampCellInfo->ucRssiNum = 1;

    for ( i = 0; i < RRC_NAS_AT_CELL_MAX_NUM; i++ )
    {
        pstCampCellInfo->astRssiInfo[i].sRscpValue      = NAS_MML_UTRA_RSCP_UNVALID;
        pstCampCellInfo->astRssiInfo[i].sRssiValue      = NAS_MML_RSSI_UNVALID;

        pstCampCellInfo->astRssiInfo[i].ucChannalQual   = NAS_MML_UTRA_BLER_INVALID;
        pstCampCellInfo->astRssiInfo[i].ucRssiLevel     = NAS_MML_LOWER_RSSI_LEVEL;
    }

    pstCampCellInfo->ucCellNum    = 0;
    pstCampCellInfo->sUeRfPower   = NAS_MML_UE_RFPOWER_INVALID;
    pstCampCellInfo->usCellDlFreq = NAS_MML_UE_FREQ_INVALID;
    pstCampCellInfo->usCellUlFreq = NAS_MML_UE_FREQ_INVALID;

    for ( i = 0; i < RRC_NAS_AT_CELL_MAX_NUM; i++ )
    {
        pstCampCellInfo->astCellInfo[i].sCellRSCP = NAS_MML_UTRA_RSCP_UNVALID;

        pstCampCellInfo->astCellInfo[i].sCellRssi = NAS_MML_RSSI_UNVALID;

        pstCampCellInfo->astCellInfo[i].ulCellId  = NAS_MML_CELLID_INVALID;
    }

    pstCampCellInfo->ulArfcn                      = 0x0;
}



VOS_VOID  NAS_MML_InitRrcNcellInfo(
    NAS_MML_RRC_NCELL_INFO_STRU         *pstRrcNcellInfo
)
{
    PS_MEM_SET(pstRrcNcellInfo,0x00,sizeof(NAS_MML_RRC_NCELL_INFO_STRU));
    pstRrcNcellInfo->ucLteNcellExist     = VOS_FALSE;
    pstRrcNcellInfo->ucUtranNcellExist   = VOS_FALSE;
}



VOS_VOID  NAS_MML_InitCampPlmnInfo(
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo
)
{
    pstCampPlmnInfo->enNetRatType                              = NAS_MML_NET_RAT_TYPE_BUTT;
    pstCampPlmnInfo->enNetworkMode                             = NAS_MML_NET_MODE_BUTT;
    pstCampPlmnInfo->enSysSubMode                              = RRC_NAS_SYS_SUBMODE_BUTT;

    NAS_MML_InitCampRai(pstCampPlmnInfo);

    NAS_MML_InitOldCampLai(&pstCampPlmnInfo->stOldLai);

    pstCampPlmnInfo->stOperatorNameInfo.stOperatorPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstCampPlmnInfo->stOperatorNameInfo.stOperatorPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    PS_MEM_SET(pstCampPlmnInfo->stOperatorNameInfo.aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
    PS_MEM_SET(pstCampPlmnInfo->stOperatorNameInfo.aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);

    NAS_MML_InitRrcNcellInfo(&(pstCampPlmnInfo->stRrcNcellInfo));

    NAS_MML_InitRssiValue(&(pstCampPlmnInfo->stCampCellInfo));

    pstCampPlmnInfo->enLmmAccessType    = NAS_MML_LMM_ACCESS_TYPE_BUTT;
}


VOS_VOID NAS_MML_InitOldCampLai(
    NAS_MML_LAI_STRU                   *pstLaiInfo
)
{
    /* 将上次驻留PLMN，LAI,RAC更新为无效值 */
    pstLaiInfo->stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstLaiInfo->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstLaiInfo->aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstLaiInfo->aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;

    return;
}




VOS_VOID  NAS_MML_InitCsDomainInfo(
    NAS_MML_CS_DOMAIN_INFO_STRU         *pstCsDomainInfo
)
{
    pstCsDomainInfo->ucAttFlg                               = VOS_TRUE;
    pstCsDomainInfo->ucCsAttachAllow                        = VOS_TRUE;

    pstCsDomainInfo->enCsRegStatus                          = NAS_MML_REG_STATUS_BUTT;

    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp  = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister   = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictNormalService      = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictEmergencyService   = VOS_FALSE;

    pstCsDomainInfo->ucCsSupportFlg                         = VOS_FALSE;
    pstCsDomainInfo->ulCsDrxLen                             = NAS_MML_CS_INVALID_DRX_LEN;
    pstCsDomainInfo->ulCsRegisterBarToUnBarFlag             = VOS_FALSE;
    pstCsDomainInfo->ulT3212Len                     = NAS_MML_T3212_INFINITE_TIMEOUT_VALUE;
    pstCsDomainInfo->stLastSuccLai.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
    pstCsDomainInfo->stLastSuccLai.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
    pstCsDomainInfo->stLastSuccLai.aucLac[0]        = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCsDomainInfo->stLastSuccLai.aucLac[1]        = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstCsDomainInfo->stLastSuccLai.ucRac = NAS_MML_RAC_INVALID;

    pstCsDomainInfo->stCmSrvStatus.enMoCallStatus   = NAS_MML_CALL_STATUS_BUTT;
    pstCsDomainInfo->stCmSrvStatus.enMoSsStatus     = NAS_MML_SS_STATUS_BUTT;

    pstCsDomainInfo->stCmSrvStatus.enMtCsfbPagingTimerStatus = NAS_MML_MT_CSFB_PAGING_TIMER_STOP;

    pstCsDomainInfo->stCmSrvStatus.ucCellNotSupportCsmoFlg   =   VOS_FALSE;
}



VOS_VOID  NAS_MML_InitPsDomainInfo(
    NAS_MML_PS_DOMAIN_INFO_STRU         *pstPsDomainInfo
)
{
    pstPsDomainInfo->ucPsAttachAllow                    = VOS_FALSE;

    pstPsDomainInfo->enPsRegStatus                      = NAS_MML_REG_STATUS_BUTT;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp  = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister   = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictNormalService      = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictEmergencyService   = VOS_FALSE;
    pstPsDomainInfo->ucPsSupportFlg                     = VOS_FALSE;
    pstPsDomainInfo->ulPsRegisterBarToUnBarFlag         = VOS_FALSE;
    pstPsDomainInfo->stLastSuccRai.stLai.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPsDomainInfo->stLastSuccRai.stLai.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;

    pstPsDomainInfo->stPsDomainDrxPara.enPsRegisterContainDrx = NAS_MML_PS_REG_CONTAIN_BUTT;
    pstPsDomainInfo->stPsDomainDrxPara.ucNonDrxTimer          = NAS_MML_PS_DEFAULT_NON_DRX_TIMER;
    pstPsDomainInfo->stPsDomainDrxPara.ucUeUtranPsDrxLen      = NAS_MML_PS_UE_UTRAN_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucWSysInfoDrxLen       = NAS_MML_PS_UE_UTRAN_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucUeEutranPsDrxLen     = NAS_MML_PS_UE_LTE_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucLSysInfoDrxLen       = NAS_MML_PS_UE_LTE_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucSplitOnCcch          = NAS_MML_PS_DEFAULT_DRX_SPLIT_ON_CCCH;
    pstPsDomainInfo->stPsDomainDrxPara.ucSplitPgCycleCode     = NAS_MML_PS_DEFAULT_DRX_SPLIT_PG_CYCLE_CODE;

    NAS_MML_SetPsLocalDetachFlag(VOS_FALSE);

    NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_INVALID);
    NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_INVALID);
    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_INVALID);

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MML_SetGUNwImsVoiceSupportFlg(NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED);
#endif

}


VOS_VOID  NAS_MML_InitMsCurrBandInfoInfo(
    NAS_MML_MS_BAND_INFO_STRU         *pstMsBandInfo
)
{
    /* GSM的当前驻留的Band */
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm1800          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm1900          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm450           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm480           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm700           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm850           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsmE900          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsmP900          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsmR900          = VOS_FALSE;

    /* WCDMA的当前驻留的Band */
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_III_1800 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_II_1900  = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_IV_1700  = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_IX_J1700 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_I_2100   = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_VIII_900 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_VII_2600 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_VI_800   = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_V_850    = VOS_FALSE;

    /* LTE的当前驻留的的Band */
    pstMsBandInfo->stLteBand.aulLteBand[0]                  = NAS_MML_LTE_ALL_BAND_INVALID;
    pstMsBandInfo->stLteBand.aulLteBand[1]                  = NAS_MML_LTE_ALL_BAND_INVALID;
}


VOS_VOID  NAS_MML_InitNetwork3GppRel(
    NAS_MML_NETWORK_3GPP_REL_STRU      *pstNetwork3GppRel
)
{
    pstNetwork3GppRel->enNetMscRel      = NAS_MML_NETWORK_MSG_REL_VER_BUTT;
    pstNetwork3GppRel->enNetSgsnRel     = NAS_MML_NETWORK_SGSN_REL_VER_BUTT;
}



VOS_VOID  NAS_MML_InitEquPlmnInfo(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;

    pstEquPlmnInfo->ucEquPlmnNum    = 0;
    for ( i = 0 ; i < NAS_MML_MAX_EQUPLMN_NUM ; i++ )
    {
        pstEquPlmnInfo->astEquPlmnAddr[i].ulMcc = NAS_MML_INVALID_MCC;
        pstEquPlmnInfo->astEquPlmnAddr[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    pstEquPlmnInfo->ucValidFlg = VOS_FALSE;
}


VOS_VOID  NAS_MML_InitConnStatusInfo(
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus
)
{
    pstConnStatus->ucCsSigConnStatusFlg         =   VOS_FALSE;
    pstConnStatus->ucPsSigConnStatusFlg         =   VOS_FALSE;
    pstConnStatus->ucPsTbfStatusFlg             =   VOS_FALSE;
    pstConnStatus->ucRrcStatusFlg               =   VOS_FALSE;
    pstConnStatus->ucCsServiceConnStatusFlg     =   VOS_FALSE;
    pstConnStatus->ucCsServiceBufferFlg         =   VOS_FALSE;
    pstConnStatus->ucPsServiceBufferFlg         =   VOS_FALSE;
    pstConnStatus->ucPdpStatusFlg               =   VOS_FALSE;
    pstConnStatus->ucEpsSigConnStatusFlg        =   VOS_FALSE;
    pstConnStatus->ucEpsServiceConnStatusFlg    =   VOS_FALSE;
    pstConnStatus->ucEmergencyServiceFlg        =   VOS_FALSE;
    pstConnStatus->ucPsTcServiceFlg             =   VOS_FALSE;
    pstConnStatus->ucEmcPdpStatusFlg            =   VOS_FALSE;


    pstConnStatus->enCsfbServiceStatus          =   NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;

    PS_MEM_SET(pstConnStatus->aucReserved, 0x0, sizeof(pstConnStatus->aucReserved));
}


VOS_VOID NAS_MML_InitEpsDomainInfo(
    NAS_MML_EPS_DOMAIN_INFO_STRU       *pstEpsDomainInfo
)
{
   pstEpsDomainInfo->enT3412Status            = NAS_MML_TIMER_STOP;
   pstEpsDomainInfo->enT3423Status            = NAS_MML_TIMER_STOP;
   pstEpsDomainInfo->enT3402Status            = NAS_MML_TIMER_STOP;
   pstEpsDomainInfo->enAdditionUpdateRsltInfo = NAS_MML_ADDITION_UPDATE_RSLT_BUTT;
   pstEpsDomainInfo->enEpsRegStatus           = NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH;
   pstEpsDomainInfo->enNwImsVoCap             = NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED;

   /* 设置T3402定时器时长默认12分钟 */
   NAS_MML_SetT3402Len(NAS_MML_DEFAULT_T3402_LEN);

   return;
}


VOS_VOID NAS_MML_InitImsDomainInfo(
    NAS_MML_IMS_DOMAIN_INFO_STRU        *pstImsDomainInfo
)
{
    pstImsDomainInfo->ucImsVoiceAvail   = VOS_FALSE;
    pstImsDomainInfo->enImsNormalRegSta = NAS_MML_IMS_NORMAL_REG_STATUS_DEREG;
    pstImsDomainInfo->ucImsCallFlg      = VOS_FALSE;

    NAS_MML_SetPersistentBearerState(NAS_MML_PERSISTENT_BEARER_STATE_NOT_EXIST);
}


VOS_VOID NAS_MML_InitPsBearerContext(
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx
)
{
    VOS_UINT8                           i;

    for(i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        pstPsBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
        pstPsBearerCtx[i].enPsBearerState  = NAS_MML_PS_BEARER_STATE_INACTIVE;
        pstPsBearerCtx[i].ucPsActPending   = VOS_FALSE;
        pstPsBearerCtx[i].ucPsDeactPending = VOS_FALSE;
    }

    return;
}


VOS_VOID NAS_MML_InitEmergencyNumList(
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList
)
{
    pstEmergencyNumList->ucEmergencyNumber = 0;
    PS_MEM_SET(pstEmergencyNumList->aucEmergencyList, (VOS_CHAR)0xFF,
               sizeof(pstEmergencyNumList->aucEmergencyList));
    return;
}



VOS_VOID  NAS_MML_InitNetworkCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_NETWORK_INFO_STRU           *pstNetworkInfo
)
{
    NAS_MML_InitCampPlmnInfo(&(pstNetworkInfo->stCampPlmnInfo));

    NAS_MML_InitEquPlmnInfo(&(pstNetworkInfo->stEquPlmnInfo));

    NAS_MML_InitNetwork3GppRel(&(pstNetworkInfo->stNetwork3GppRel));

    NAS_MML_InitMsCurrBandInfoInfo(&(pstNetworkInfo->stBandInfo));

    NAS_MML_InitPsDomainInfo(&(pstNetworkInfo->stPsDomainInfo));

    NAS_MML_InitCsDomainInfo(&(pstNetworkInfo->stCsDomainInfo));

    NAS_MML_InitEpsDomainInfo(&(pstNetworkInfo->stEpsDomainInfo));

    NAS_MML_InitImsDomainInfo(&(pstNetworkInfo->stImsDomainInfo));

    NAS_MML_InitConnStatusInfo(&(pstNetworkInfo->stConnStatus));
    NAS_MML_InitPsBearerContext(pstNetworkInfo->astPsBearerContext);
    NAS_MML_InitEmergencyNumList(&pstNetworkInfo->stEmergencyNumList);

    pstNetworkInfo->stNoRfInfo.ucRfAvailFlg   = VOS_TRUE;
    pstNetworkInfo->stNoRfInfo.enRatType      = NAS_MML_NET_RAT_TYPE_BUTT;
    pstNetworkInfo->stNoRfInfo.aucReserved[0] = 0;
    pstNetworkInfo->stNoRfInfo.aucReserved[1] = 0;

    NAS_MML_InitSuitPlmnListInfo(&(pstNetworkInfo->stSuitPlmnListInfo));

    NAS_MML_InitOriginalRejectCause(&(pstNetworkInfo->stOriginalRejectCause));

    NAS_MML_InitAuthInfo(enInitType, &(pstNetworkInfo->stAuthInfo));
}


VOS_VOID  NAS_MML_InitInternalMsgQueue(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MM子层的内部消息队列 */
)
{
    VOS_UINT32                          i;

    pstInternalMsgQueue->ucHeader   = 0;
    pstInternalMsgQueue->ucTail     = 0;

    for ( i = 0 ; i < NAS_MML_MAX_MSG_QUEUE_SIZE; i++ )
    {
        pstInternalMsgQueue->astNasMmMsgQueue[i].usMsgID    = NAS_MML_INVALID_INTERNAL_MSG_ID;
        PS_MEM_SET(pstInternalMsgQueue->astNasMmMsgQueue[i].aucBuf,
                   0x00,
                   NAS_MML_MAX_INTERNAL_MSG_LEN);
    }

}



VOS_VOID  NAS_MML_InitMaintainInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_MAINTAIN_CTX_STRU          *pstMaintainInfo
)
{
    PS_MEM_SET(&g_stNasMntnErrorLogMm, 0, sizeof(g_stNasMntnErrorLogMm));

    /* 上电开机时才需要初始化如下变量 */
    if (NAS_MML_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始默认不发送PC回放消息 */
    pstMaintainInfo->stUeMaintainInfo.ucUeSndPcRecurFlg    = VOS_FALSE;

    /* 初始默认PC工具未连接 */
    pstMaintainInfo->stOmMaintainInfo.ucOmConnectFlg       = VOS_FALSE;

    /* 初始默认PC工具未使能NAS的PC回放消息发送 */
    pstMaintainInfo->stOmMaintainInfo.ucOmPcRecurEnableFlg = VOS_FALSE;

    NAS_MML_InitErrLogMntnInfo(&pstMaintainInfo->stErrLogMntnInfo);
#if (FEATURE_ON == FEATURE_PTM)
    pstMaintainInfo->stFtmMntnInfo.ucFtmCtrlFlag           = VOS_FALSE;
#endif

    NAS_MML_InitLogEventState(&(pstMaintainInfo->stLogEventState));
}


VOS_VOID  NAS_MML_InitCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_CTX_STRU                    *pstMmlCtx
)
{
    /* 初始化SIM卡信息 */
    NAS_MML_InitSimInfoCtx(enInitType, &(pstMmlCtx->stSimInfo));

    /* 初始化MS配置信息 */
    NAS_MML_InitMsCfgCtx(&(pstMmlCtx->stMsCfgInfo));

    /* 初始化当前网络信息 */
    NAS_MML_InitNetworkCtx(enInitType, &(pstMmlCtx->stNetworkInfo));

    /* 初始化内部消息队列 */
    NAS_MML_InitInternalMsgQueue(&(pstMmlCtx->stInternalMsgQueue));

    /* 初始化可谓可测信息 */
    NAS_MML_InitMaintainInfo(enInitType, &(pstMmlCtx->stMaintainInfo));

    PS_MEM_SET(&pstMmlCtx->stCsMoSessionManager, 0x0, sizeof(NAS_MML_CS_MO_SESSION_MANAGER_STRU));

}


NAS_MML_SIM_INFO_STRU*  NAS_MML_GetSimInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo);
}


NAS_MML_MS_CFG_INFO_STRU* NAS_MML_GetMsCfgInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo);
}


NAS_MML_NETWORK_INFO_STRU* NAS_MML_GetNetworkInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo);
}


NAS_MML_SIM_STATUS_STRU* NAS_MML_GetSimStatus(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus);
}


VOS_UINT8 NAS_MML_GetSimPresentStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPresentStatus);
}


NAS_MML_SIM_TYPE_ENUM_UINT8 NAS_MML_GetSimType(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enSimType);
}


VOS_VOID NAS_MML_SetSimType(
    NAS_MML_SIM_TYPE_ENUM_UINT8                 enSimType
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enSimType = enSimType;
}



VOS_UINT8 NAS_MML_GetSimCsRegStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimCsRegStatus);
}



VOS_UINT8 NAS_MML_GetSimPsRegStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPsRegStatus);
}


VOS_VOID NAS_MML_SetSimPresentStatus(
    VOS_UINT8                           ucSimPresentStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPresentStatus = ucSimPresentStatus;
}


VOS_VOID NAS_MML_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimCsRegStatus = ucSimCsRegStatus;
}


VOS_VOID NAS_MML_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPsRegStatus = ucSimPsRegStatus;
}


VOS_VOID NAS_MML_SetPsUpdateStatus(
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enPsUpdateStatus = enPsUpdateStatus;
}


NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8 NAS_MML_GetPsUpdateStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enPsUpdateStatus;
}


VOS_VOID NAS_MML_SetCsUpdateStatus(
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enCsUpdateStatus = enCsUpdateStatus;
}


NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8 NAS_MML_GetCsUpdateStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enCsUpdateStatus;
}


VOS_UINT8 NAS_MML_GetImsiRefreshStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucImsiRefreshStatus;
}


VOS_VOID NAS_MML_SetImsiRefreshStatus(
    VOS_UINT8                           ucImsiRefreshStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucImsiRefreshStatus = ucImsiRefreshStatus;
}


NAS_MML_SIM_MS_IDENTITY_STRU* NAS_MML_GetSimMsIdentity(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity);
}



VOS_VOID NAS_MML_SetSimMsIdentity(
    NAS_MML_SIM_MS_IDENTITY_STRU        *pstSimMsIdentity
)
{
    PS_MEM_CPY(&((NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity)),
               pstSimMsIdentity,
               sizeof(NAS_MML_SIM_MS_IDENTITY_STRU));
}


VOS_UINT8* NAS_MML_GetSimImsi(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucImsi;
}


VOS_UINT8* NAS_MML_GetUeIdPtmsi(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsi;
}


VOS_VOID NAS_MML_SetUeIdPtmsi(
    VOS_UINT8                          *pucPtmsi
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsi,
               pucPtmsi,
               (sizeof(VOS_UINT8) * NAS_MML_MAX_PTMSI_LEN));
}


VOS_UINT8* NAS_MML_GetUeIdPtmsiSignature(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsiSignature;
}


VOS_VOID NAS_MML_SetUeIdPtmsiSignature(
    VOS_UINT8                          *pucPtmsiSignature
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsiSignature,
               pucPtmsiSignature,
               (sizeof(VOS_UINT8) * NAS_MML_MAX_PTMSI_SIGNATURE_LEN));
}



VOS_UINT8* NAS_MML_GetUeIdTmsi(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucTmsi;
}


VOS_VOID NAS_MML_SetUeIdTmsi(
    VOS_UINT8                          *pucTmsi
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucTmsi,
               pucTmsi,
               NAS_MML_MAX_TMSI_LEN);
}


VOS_VOID NAS_MML_SetUeOperMode(
    NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 enUeOperMode
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.enUeOperMode = enUeOperMode;
}

NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 NAS_MML_GetUeOperMode(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.enUeOperMode;
}



NAS_MML_SIM_PS_SECURITY_INFO_STRU* NAS_MML_GetSimPsSecurity(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity);
}



VOS_VOID NAS_MML_SetSimPsSecurity(
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   *pstSimPsSecruity

)
{
    PS_MEM_CPY(&((NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity)),
               pstSimPsSecruity,
               sizeof(NAS_MML_SIM_PS_SECURITY_INFO_STRU));
}



VOS_UINT8 NAS_MML_GetSimPsSecurityCksn(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.ucCKSN;
}


VOS_VOID NAS_MML_SetSimPsSecurityCksn(
    VOS_UINT8                           ucCksn
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.ucCKSN = ucCksn;
}


VOS_UINT8* NAS_MML_GetSimPsSecurityUmtsCk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsCk;
}


VOS_VOID NAS_MML_SetSimPsSecurityUmtsCk(
    VOS_UINT8                           *pucUmtsCk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsCk,
               pucUmtsCk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_CK_LEN));
}



VOS_UINT8* NAS_MML_GetSimPsSecurityUmtsIk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsIk;
}


VOS_VOID NAS_MML_SetSimPsSecurityUmtsIk(
    VOS_UINT8                           *pucUmtsIk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsIk,
               pucUmtsIk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_IK_LEN));
}


VOS_UINT8* NAS_MML_GetSimPsSecurityGsmKc(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucGsmKc;
}


VOS_VOID NAS_MML_SetSimPsSecurityGsmKc(
    VOS_UINT8                           *pucGsmKc
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucGsmKc,
               pucGsmKc,
               (sizeof(VOS_UINT8) * NAS_MML_GSM_KC_LEN));
}



NAS_MML_SIM_CS_SECURITY_INFO_STRU* NAS_MML_GetSimCsSecurity(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity);
}



VOS_VOID NAS_MML_SetSimCsSecurity(
    NAS_MML_SIM_CS_SECURITY_INFO_STRU  *pstSimCsSecruity
)
{
    PS_MEM_CPY(&((NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity)),
               pstSimCsSecruity,
               sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));
}



VOS_UINT8 NAS_MML_GetSimCsSecurityCksn(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.ucCKSN;
}


VOS_VOID NAS_MML_SetSimCsSecurityCksn(
    VOS_UINT8                           ucCksn
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.ucCKSN = ucCksn;
}


VOS_UINT8* NAS_MML_GetSimCsSecurityUmtsCk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsCk;
}


VOS_VOID NAS_MML_SetSimCsSecurityUmtsCk(
    VOS_UINT8                           *pucUmtsCk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsCk,
               pucUmtsCk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_CK_LEN));
}



VOS_UINT8* NAS_MML_GetSimCsSecurityUmtsIk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsIk;
}


VOS_VOID NAS_MML_SetSimCsSecurityUmtsIk(
    VOS_UINT8                           *pucUmtsIk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsIk,
               pucUmtsIk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_IK_LEN));
}


VOS_UINT8* NAS_MML_GetSimCsSecurityGsmKc(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucGsmKc;
}


VOS_VOID NAS_MML_SetSimCsSecurityGsmKc(
    VOS_UINT8                           *pucGsmKc
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucGsmKc,
               pucGsmKc,
               (sizeof(VOS_UINT8) * NAS_MML_GSM_KC_LEN));
}




NAS_MML_SIM_EHPLMN_INFO_STRU* NAS_MML_GetSimEhplmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo);
}


VOS_VOID NAS_MML_SetSimEhplmnList(
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEhplmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo),
               pstEhplmnList,
               sizeof(NAS_MML_SIM_EHPLMN_INFO_STRU));
}



NAS_MML_SIM_PLMN_INFO_STRU* NAS_MML_GetSimPlmnInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo);
}



NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU* NAS_MML_GetSimHplmnWithRatList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stHplmnWithRatInfo);
}



VOS_VOID NAS_MML_SetSimHplmnWithRatList(
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU    *pstHplmnWithRatList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stHplmnWithRatInfo),
               pstHplmnWithRatList,
               sizeof(NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU));
}


NAS_MML_SIM_USERPLMN_INFO_STRU* NAS_MML_GetSimUserPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stUserPlmnInfo);
}


VOS_VOID NAS_MML_SetSimUserPlmnList(
    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stUserPlmnInfo),
               pstUserPlmnList,
               sizeof(NAS_MML_SIM_USERPLMN_INFO_STRU));
}


NAS_MML_SIM_OPERPLMN_INFO_STRU* NAS_MML_GetSimOperPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stOperPlmnInfo);
}


VOS_VOID NAS_MML_SetSimOperPlmnList(
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stOperPlmnInfo),
               pstOperPlmnList,
               sizeof(NAS_MML_SIM_OPERPLMN_INFO_STRU));
}


NAS_MML_SIM_SELPLMN_INFO_STRU* NAS_MML_GetSimSelPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stSelPlmnInfo);
}


VOS_VOID NAS_MML_SetSimSelPlmnList(
    NAS_MML_SIM_SELPLMN_INFO_STRU       *pstSelPlmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stSelPlmnInfo),
               pstSelPlmnList,
               sizeof(NAS_MML_SIM_SELPLMN_INFO_STRU));
}


NAS_MML_SIM_FORBIDPLMN_INFO_STRU* NAS_MML_GetForbidPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stForbidPlmnInfo);
}


VOS_VOID NAS_MML_SetSimForbidPlmnList(
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU    *pstForbidPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stForbidPlmnInfo),
               pstForbidPlmnInfo,
               sizeof(NAS_MML_SIM_FORBIDPLMN_INFO_STRU));
}


VOS_VOID NAS_MML_SetSimHplmnTimerLen(
    VOS_UINT32                          ulSimHplmnTimerLen
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ulSimHplmnTimerLen = ulSimHplmnTimerLen;
}



VOS_UINT32 NAS_MML_GetSimHplmnTimerLen(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ulSimHplmnTimerLen;
}


NAS_MML_MS_3GPP_REL_STRU* NAS_MML_GetMs3GppRel(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel);
}


VOS_VOID NAS_MML_SetMs3GppRel(
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel),
               pstMs3GppRel,
               sizeof(NAS_MML_MS_3GPP_REL_STRU));
}



NAS_MML_MS_CAPACILITY_INFO_STRU* NAS_MML_GetMsCapability(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability);
}




VOS_UINT8* NAS_MML_GetImeisv( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.aucImeisv);
}


NAS_MML_MS_MODE_ENUM_UINT8 NAS_MML_GetMsMode( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enMsMode);
}


NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8 NAS_MML_GetLteCsServiceCfg( VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCsServiceCfg;
}






NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32 NAS_MML_GetLteCapabilityStatus( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCapabilityStatus);
}


MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32 NAS_MML_GetDisableLteReason( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enDisableLteReason);
}



VOS_UINT8 NAS_MML_GetLteDisabledRauUseLteInfoFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucLteDisabledRauUseLteInfoFlag);
}


VOS_VOID NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_UINT8 ucLteDisabledRauUseLteInfoFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucLteDisabledRauUseLteInfoFlag = ucLteDisabledRauUseLteInfoFlag;
    return;
}



VOS_UINT8   NAS_MML_GetLteRoamAllowedFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.ucLteRoamAllowedFlg);
}


VOS_UINT32 NAS_MML_GetDisableLteRoamFlg( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ulDisableLteRoamFlg);
}


VOS_VOID NAS_MML_GetRoamEnabledMccList(VOS_UINT32 *pulMcc)
{
    VOS_UINT32      i;

    for (i=0; i<NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER; i++)
    {
        pulMcc[i] = NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.aulRoamEnabledMccList[i];
    }
}



NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetEpsRegStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enEpsRegStatus);
}



VOS_UINT8 NAS_MML_GetDailRejectCfg( VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDailRejectCfg.ucEnableFlg;
}



NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 NAS_MML_GetCsfbServiceStatus( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.enCsfbServiceStatus;
}


NAS_MML_PS_BEARER_CONTEXT_STRU* NAS_MML_GetPsBearerCtx( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.astPsBearerContext;
}


NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3412Status(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3412Status;
}


NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3423Status(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3423Status;
}


NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3402Status(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3402Status;
}



NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8 NAS_MML_GetAdditionUpdateRslt(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enAdditionUpdateRsltInfo;
}


NAS_MML_EMERGENCY_NUM_LIST_STRU* NAS_MML_GetEmergencyNumList (VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stEmergencyNumList);
}



NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8 NAS_MML_GetLteUeUsageSetting( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteUeUsageSetting;
}


NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8 NAS_MML_GetVoiceDomainPreference( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enVoiceDomainPreference;
}



VOS_UINT8 NAS_MML_GetLteImsSupportFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsRatSupport.ucLteImsSupportFlag;
}


VOS_UINT8 NAS_MML_GetVoiceCallOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVoiceCallOnImsSupportFlag;
}


VOS_UINT8 NAS_MML_GetSmsOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucSmsOnImsSupportFlag;
}



VOS_UINT8 NAS_MML_GetVideoCallOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVideoCallOnImsSupportFlag;
}


VOS_UINT8 NAS_MML_GetUssdOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucUssdOnImsSupportFlag;
}


VOS_UINT32 NAS_MML_GetHoWaitSysinfoTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulHoWaitSysinfoTimeLen);
}



VOS_UINT8 NAS_MML_GetPsAutoAttachFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucPsAutoAttachFlg);
}




NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU* NAS_MML_GetRoamingRejectNoRetryCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamingRejectNoRetryInfo);
}


NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU* NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLauRejNoRetryWhenCmSrvExistCfgInfo);
}




NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU* NAS_MML_GetRejCauseChangedCounter(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stChangeNWCauseInfo.stRejCauseChangedCounter);
}



VOS_UINT8 NAS_MML_GetUserAutoReselActiveFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucUserAutoReselActiveFlg);
}

VOS_VOID NAS_MML_SetUserAutoReselActiveFlg(VOS_UINT8 ucActiveFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucUserAutoReselActiveFlg = ucActiveFlag;
}



VOS_VOID NAS_MML_SetMsMode(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enMsMode = enMsMode;
}


VOS_VOID NAS_MML_SetLteCsServiceCfg(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCsServiceCfg
                               = enLteCsServiceCfg;
}



VOS_VOID NAS_MML_SetLteCapabilityStatus(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCapabilityStatus = enLCapabilityStatus;
}


VOS_VOID NAS_MML_SetDisableLteReason(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enDisableLteReason = enDisableLteReason;
}


VOS_VOID NAS_MML_SetDisableLteRoamFlg(
    VOS_UINT32                          ulDisableFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ulDisableLteRoamFlg
                               = ulDisableFlg;
}


VOS_VOID NAS_MML_SetRoamEnabledMccList(VOS_UINT32 *pulMcc)
{
    VOS_UINT32      i;

    for (i=0; i<NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER; i++)
    {
        NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.aulRoamEnabledMccList[i] = pulMcc[i];
    }
}


VOS_VOID NAS_MML_SetRoamRplmnSearchFlg(VOS_UINT8 ucRoamSearchRPLMNFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.ucRoamSearchRPLMNFlg = ucRoamSearchRPLMNFlg;
}


VOS_UINT8 NAS_MML_GetRoamRplmnSearchFlg()
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.ucRoamSearchRPLMNFlg;
}


VOS_UINT32 *NAS_MML_GetNationalMCCList()
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.aucNationalMccList;
}


VOS_VOID NAS_MML_SetNationalMCCList(VOS_UINT32 *pulMcc)
{
    VOS_UINT32      i;

    for (i=0; i<NAS_MML_MAX_NATIONAL_MCC_NUM; i++)
    {
        NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.aucNationalMccList[i] = pulMcc[i];
    }
}



VOS_VOID NAS_MML_SetDisableLTEOnBandFlg(VOS_UINT8 ucDisableLTEOnBandFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDisableLTEOnBandFlg = ucDisableLTEOnBandFlg;
}


VOS_UINT8 NAS_MML_GetDisableLTEOnBandFlg()
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDisableLTEOnBandFlg;
}




VOS_VOID NAS_MML_SetUltraFlashCsfbSupportFlg(
    VOS_UINT8                           ucUltraFlashCsfbSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucUltraFlashCsfbSupportFlg = ucUltraFlashCsfbSupportFlg;
}


VOS_UINT8 NAS_MML_GetUltraFlashCsfbSupportFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucUltraFlashCsfbSupportFlg;
}



VOS_VOID NAS_MML_SetLteRoamAllowedFlg(
    VOS_UINT8                           ucAllowedFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.ucLteRoamAllowedFlg
                               = ucAllowedFlg;
}



VOS_VOID NAS_MML_SetEpsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enEpsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enEpsRegStatus = enEpsRegStatus;
}





VOS_VOID NAS_MML_SetRelCauseCsfbHighPrioFlg(
    VOS_UINT8       ucFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ucIsRelCauseCsfbHighPrio = ucFlg;
}


VOS_UINT32  NAS_MML_GetRelCauseCsfbHighPrioFlg()
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ucIsRelCauseCsfbHighPrio);
}




VOS_VOID NAS_MML_SetDailRejectCfg(
    VOS_UINT8                           ucEnableFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDailRejectCfg.ucEnableFlg
                               = ucEnableFlg;
}



VOS_VOID NAS_MML_SetCsfbServiceStatus(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                     enCsfbServiceStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.enCsfbServiceStatus = enCsfbServiceStatus;
}


VOS_VOID NAS_MML_SetVoiceDomainPreference(
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPrefer
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enVoiceDomainPreference = enVoiceDomainPrefer;
}


VOS_VOID NAS_MML_SetLteImsSupportFlg(
    VOS_UINT8                           ucImsSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsRatSupport.ucLteImsSupportFlag = ucImsSupportFlg;
}


VOS_VOID NAS_MML_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVoiceCallOnImsSupportFlag = ucVoiceCallOnImsSupportFlag;
}


VOS_VOID NAS_MML_SetSmsOnImsSupportFlag(
    VOS_UINT8                           ucSmsOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucSmsOnImsSupportFlag = ucSmsOnImsSupportFlag;
}


VOS_VOID NAS_MML_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                           ucVideoCallOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVideoCallOnImsSupportFlag = ucVideoCallOnImsSupportFlag;
}



VOS_VOID NAS_MML_SetUssdOnImsSupportFlag(
    VOS_UINT8                           ucUssdOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucUssdOnImsSupportFlag = ucUssdOnImsSupportFlag;
}




VOS_VOID NAS_MML_SetLteUeUsageSetting(
    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enUeUsageSetting
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteUeUsageSetting = enUeUsageSetting;
}

VOS_VOID NAS_MML_SetT3412Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3412Status = enTimerStatus;
}


VOS_VOID NAS_MML_SetT3423Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3423Status = enTimerStatus;
}


VOS_VOID NAS_MML_SetT3402Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3402Status = enTimerStatus;
}


VOS_VOID NAS_MML_SetAdditionUpdateRslt(
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdRslt
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enAdditionUpdateRsltInfo = enAdditionUpdRslt;
}


VOS_VOID NAS_MML_SetEmergencyNumList (
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmcNumList
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEmergencyNumList = *pstEmcNumList;
}


VOS_VOID NAS_MML_SetTinType(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enTinType = enTinType;
}


VOS_VOID NAS_MML_SetPsBearerCtx(
    VOS_UINT8                           ucRabId,
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.astPsBearerContext[ucRabId - NAS_MML_NSAPI_OFFSET] = *pstPsBearerCtx;
}


VOS_VOID NAS_MML_SetHoWaitSysinfoTimerLen(
    VOS_UINT32                          ulHoWaitSysinfoTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulHoWaitSysinfoTimeLen = ulHoWaitSysinfoTimeLen;
}


VOS_VOID NAS_MML_SetCsfbEmgCallEnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsfbEmgCallEnableLteTimerLen = ulEnalbeLteTimeLen;
}


VOS_VOID NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsPsMode13GPPEnableLteTimerLen = ulEnalbeLteTimeLen;
}


VOS_VOID NAS_MML_SetSvlteSupportFlag(
    VOS_UINT8                           ucSvlteSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSvlteSupportFlag = ucSvlteSupportFlag;
}


VOS_UINT8 NAS_MML_GetSvlteSupportFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSvlteSupportFlag);
}


VOS_VOID NAS_MML_SetPsTransferOffAreaModeFlag(
    VOS_UINT8                           ucPsTransferOffAreaMode
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsTransferOffAreaModeFlg = ucPsTransferOffAreaMode;
}


VOS_UINT8 NAS_MML_GetPsTransferOffAreaModeFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsTransferOffAreaModeFlg);
}




VOS_UINT32 NAS_MML_GetCsfbEmgCallEnableLteTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsfbEmgCallEnableLteTimerLen);
}


VOS_UINT32 NAS_MML_GetCsPsMode13GPPEnableLteTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsPsMode13GPPEnableLteTimerLen);
}



VOS_VOID NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucCsfbEmgCallLaiChgLauFirstFlg
                         = ucCsfbEmgCallLaiChgLauFirstFlg;
}


VOS_UINT8 NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucCsfbEmgCallLaiChgLauFirstFlg);
}



VOS_VOID NAS_MML_SetPsAutoAttachFlg(
    VOS_UINT8                           usPsAutoAttachFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucPsAutoAttachFlg = usPsAutoAttachFlg;
}


NAS_MML_MS_BAND_INFO_STRU* NAS_MML_GetMsSupportBand( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stMsBand);
}


NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MML_GetMsPrioRatList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList);
}


NAS_MML_3GPP2_RAT_PRIO_STRU* NAS_MML_GetMs3Gpp2PrioRatList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.st3Gpp2RatList);
}



NAS_MML_RPLMN_CFG_INFO_STRU* NAS_MML_GetRplmnCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg);
}


NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_GetLastRplmnRat( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enLastRplmnRat);
}


VOS_VOID NAS_MML_SetLastRplmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enLastRplmnRat = enRat;
    return;
}



NAS_MML_HPLMN_CFG_INFO_STRU* NAS_MML_GetHplmnCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg);
}




NAS_MML_ROAM_CFG_INFO_STRU* NAS_MML_GetRoamCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg);
}



NAS_MML_AIS_ROAMING_CFG_STRU* NAS_MML_GetAisRoamingCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.stAisRoamingCfg);
}







NAS_MML_PRIO_HPLMNACT_CFG_STRU* NAS_MML_GetPrioHplmnActCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.stPrioHplmnActCfg);
}




NAS_MML_BG_SEARCH_CFG_INFO_STRU* NAS_MML_GetBgSearchCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg);
}



NAS_MML_PLMN_LOCK_CFG_INFO_STRU* NAS_MML_GetPlmnLockCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stPlmnLockCfg);
}




NAS_MML_CUSTOM_CFG_INFO_STRU* NAS_MML_GetCustomCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg);
}



NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU* NAS_MML_GetDisabledRatPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stPlmnLockCfg.stDisabledRatPlmnInfo);
}



NAS_MML_RAT_FORBIDDEN_LIST_STRU* NAS_MML_GetRatForbiddenListCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatForbiddenListInfo);
}



NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetGsmForbiddenStatusFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucGsmCapaStatus);
}



VOS_VOID NAS_MML_SetGsmForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enGsmCapaStatus )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucGsmCapaStatus = enGsmCapaStatus;
}



NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetUtranForbiddenStatusFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucUtranCapaStatus);
}



VOS_VOID NAS_MML_SetUtranForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enUtranCapaStatus )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucUtranCapaStatus = enUtranCapaStatus;
}



NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetLteForbiddenStatusFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucLteCapaStatus);
}



VOS_VOID NAS_MML_SetLteForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enLteCapaStatus )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucLteCapaStatus = enLteCapaStatus;
}



VOS_UINT8 NAS_MML_GetImsiInForbiddenListFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucIsImsiInForbiddenListFlg);
}



VOS_VOID NAS_MML_SetImsiInForbiddenListFlg( VOS_UINT8 ucIsImsiInForbiddenList )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucIsImsiInForbiddenListFlg = ucIsImsiInForbiddenList;
}



NAS_MML_MISCELLANEOUS_CFG_INFO_STRU* NAS_MML_GetMiscellaneousCfgInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg);
}


VOS_UINT8 NAS_MML_GetStkSteeringOfRoamingSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucStkSteeringOfRoamingSupportFlg);
}


VOS_VOID NAS_MML_SetStkSteeringOfRoamingSupportFlg(
    VOS_UINT8                           ucStkSteeringOfRoamingSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucStkSteeringOfRoamingSupportFlg
                                             = ucStkSteeringOfRoamingSupportFlg;
}


NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU* NAS_MML_GetHighPrioRatHplmnTimerCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stHighRatHplmnTimerCfg);
}



VOS_UINT8  NAS_MML_GetHighPrioRatHplmnTimerActiveFlg( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ucActiveFLg;
}



VOS_UINT8  NAS_MML_GetHighPrioRatHplmnTimerTdThreshold(VOS_VOID)
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ucTdThreshold;
}



VOS_UINT8 NAS_MML_GetCsRejSearchSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucCsRejSearchSupportFlg);
}


VOS_UINT8 NAS_MML_GetRoamBrokerActiveFlag( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRoamBrokerActiveFlag);
}


VOS_UINT8 NAS_MML_GetRoamBrokerRegisterFailCnt( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRoamBrokerRegisterFailCnt);
}


VOS_VOID NAS_MML_SetRoamBrokerRegisterFailCnt(
    VOS_UINT8                           ucRoamBrokerRegisterFailCnt
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRoamBrokerRegisterFailCnt
                       = ucRoamBrokerRegisterFailCnt;
}

VOS_UINT8 NAS_MML_GetDtSingleDomainPlmnSearchFlag( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucSingleDomainFailPlmnSrchFlag);
}


VOS_VOID NAS_MML_SetDtSingleDomainPlmnSearchFlag(
    VOS_UINT8                           ucPlmnSrchFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucSingleDomainFailPlmnSrchFlag
                       = ucPlmnSrchFlag;
}


VOS_VOID NAS_MML_SetCsRejSearchSupportFlg(
    VOS_UINT8                           ucCsRejSearchSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucCsRejSearchSupportFlg
                                        = ucCsRejSearchSupportFlg;
}



NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU* NAS_MML_GetCarryEplmnWhenSrchRplmnCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCarryEplmnWhenSrchRplmnCfg);
}




NAS_MML_CAMP_PLMN_INFO_STRU* NAS_MML_GetCurrCampPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo) ;
}



NAS_MML_CAMP_CELL_INFO_STRU* NAS_MML_GetCampCellInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stCampCellInfo) ;
}



NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MML_GetCurrNetRatType( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enNetRatType) ;
}


VOS_VOID  NAS_MML_SetCurrNetRatType(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enNetRatType) = enNetRatType ;
}


VOS_UINT8 NAS_MML_GetRfAvailFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.ucRfAvailFlg;
}


VOS_VOID NAS_MML_SetRfAvailFlg(
    VOS_UINT8                           ucRfAvailFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.ucRfAvailFlg = ucRfAvailFlg;
}


NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_GetNoRfRatType( VOS_VOID )
{
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    return NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.enRatType;
}


VOS_VOID  NAS_MML_SetCurrRatRfAvailFlg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    VOS_UINT8                           ucRfAvail
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.ucRfAvailFlg  = ucRfAvail;
    NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.enRatType     = enRatType;

    return;
}




VOS_VOID  NAS_MML_SetCurrSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enSysSubMode) = enSysSubMode ;
}

NAS_MML_PLMN_ID_STRU*  NAS_MML_GetCurrCampPlmnId( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stLai.stPlmnId) ;
}


NAS_MML_LAI_STRU*  NAS_MML_GetCurrCampLai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stLai) ;
}


VOS_VOID NAS_MML_InitSimCsgInfo(
    NAS_MML_SIM_CSG_INFO_STRU          *pstSimCsgInfo
)
{
    VOS_UINT32                          ulIndex;

    PS_MEM_SET(&pstSimCsgInfo->stAllowedCsgList, 0, sizeof(pstSimCsgInfo->stAllowedCsgList));
    PS_MEM_SET(&pstSimCsgInfo->stOperatorCsgList, 0, sizeof(pstSimCsgInfo->stOperatorCsgList));
    PS_MEM_SET(&pstSimCsgInfo->stForbiddenCsgList, 0, sizeof(pstSimCsgInfo->stForbiddenCsgList));

    for (ulIndex = 0; ulIndex < NAS_MML_MAX_PLMN_CSG_ID_NUM; ulIndex++)
    {
        pstSimCsgInfo->stAllowedCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstSimCsgInfo->stAllowedCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstSimCsgInfo->stAllowedCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.ulCsgId        = NAS_MML_INVALID_CSG_ID_VALUE;

        pstSimCsgInfo->stOperatorCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstSimCsgInfo->stOperatorCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstSimCsgInfo->stOperatorCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.ulCsgId        = NAS_MML_INVALID_CSG_ID_VALUE;
    }

    for (ulIndex = 0; ulIndex <NAS_MML_MAX_FORBIDDEN_CSG_ID_NUM; ulIndex++)
    {
        pstSimCsgInfo->stForbiddenCsgList.astForbiddenCsgIdPeriodInfo[ulIndex].stPlmnWithCsgIdInfo.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstSimCsgInfo->stForbiddenCsgList.astForbiddenCsgIdPeriodInfo[ulIndex].stPlmnWithCsgIdInfo.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstSimCsgInfo->stForbiddenCsgList.astForbiddenCsgIdPeriodInfo[ulIndex].stPlmnWithCsgIdInfo.ulCsgId        = NAS_MML_INVALID_CSG_ID_VALUE;
    }

    return;
}


NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU*  NAS_MML_GetAllowedCsgList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimCsgInfo.stAllowedCsgList);
}

NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU* NAS_MML_GetOperatorCsgList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimCsgInfo.stOperatorCsgList);
}


NAS_MML_CSG_ID_WITH_FORBIDDEN_PERIOD_LIST_STRU* NAS_MML_GetForbiddenCsgList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimCsgInfo.stForbiddenCsgList);
}

VOS_UINT8 NAS_MML_GetCsgDisplayCtrlFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucCsgDisplayCtrlFlag);
}


VOS_VOID NAS_MML_SetCsgDisplayCtrlFlag(
    VOS_UINT8                           ucCsgDisplayCtrlFlag
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucCsgDisplayCtrlFlag = ucCsgDisplayCtrlFlag;
    return;
}



VOS_VOID NAS_MML_SetCsgSupportFlag(
    VOS_UINT8                           ucCsgSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucCsgSupportFlag = ucCsgSupportFlag;
    return;
}


VOS_UINT8 NAS_MML_GetCsgSupportFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucCsgSupportFlag;
}


VOS_UINT8 NAS_MML_GetOnlyReportOperatorCsgListFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucOnlyReportOperatorCsgListFlag;
}


VOS_VOID NAS_MML_SetOnlyReportOperatorCsgListFlag(
    VOS_UINT8                           ucOnlyReportOperatorCsgListFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucOnlyReportOperatorCsgListFlag = ucOnlyReportOperatorCsgListFlag;
    return;
}


NAS_MML_LAI_STRU*  NAS_MML_GetOldCampLai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOldLai) ;
}



VOS_UINT32  NAS_MML_GetCurrCampLac( VOS_VOID )
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo      = VOS_NULL_PTR;
    VOS_UINT32                          ulLac;

    pstCurCampInfo = &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo);

    ulLac  = (pstCurCampInfo->stLai.aucLac[0] << 8) & 0xFF00;
    ulLac |= pstCurCampInfo->stLai.aucLac[1];

    return ulLac;
}




VOS_UINT8 NAS_MML_GetCurrCampRac(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.ucRac;
}



VOS_UINT32 NAS_MML_GetCurrCampArfcn(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stCampCellInfo.ulArfcn;
}



VOS_VOID NAS_MML_SetCurrCampArfcn(
    VOS_UINT32                          ulArfcn
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stCampCellInfo.ulArfcn) = ulArfcn;
}



NAS_MML_MS_BAND_INFO_STRU* NAS_MML_GetCurrBandInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stBandInfo) ;
}



NAS_MML_CS_DOMAIN_INFO_STRU* NAS_MML_GetCsDomainInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo);
}


VOS_UINT32 NAS_GetT3212Len( VOS_VOID )
{
    return NAS_MML_GetCsDomainInfo()->ulT3212Len;
}


VOS_VOID NAS_MML_SetCsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enCsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
}


NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetCsRegStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus);
}



NAS_MML_LAI_STRU* NAS_MML_GetCsLastSuccLai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai)   ;
}


VOS_UINT32 NAS_MML_GetCsLastSuccLac( VOS_VOID )
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT32                          ulCsSuccLac;

    pstCsSuccLai    = &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai);

    ulCsSuccLac = (pstCsSuccLai->aucLac[0] << 8) & 0xFF00;
    ulCsSuccLac |= pstCsSuccLai->aucLac[1];

    return ulCsSuccLac;
}


NAS_MML_PLMN_ID_STRU*  NAS_MML_GetCsLastSuccPlmnId( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai.stPlmnId) ;
}



VOS_UINT32  NAS_MML_GetCsLastSuccMcc( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai.stPlmnId.ulMcc) ;
}



VOS_UINT32  NAS_MML_GetCsLastSuccMnc( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai.stPlmnId.ulMnc) ;
}




NAS_MML_RAI_STRU* NAS_MML_GetPsLastSuccRai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stLastSuccRai)   ;
}




NAS_MML_PS_DOMAIN_INFO_STRU* NAS_MML_GetPsDomainInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo);
}



NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetPsRegStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus);
}


VOS_VOID NAS_MML_SetPsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
}




NAS_MML_NETWORK_3GPP_REL_STRU* NAS_MML_GetNetwork3GppRel( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stNetwork3GppRel)  ;
}



NAS_MML_EQUPLMN_INFO_STRU* NAS_MML_GetEquPlmnList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stEquPlmnInfo);
}


NAS_MML_SUIT_PLMN_LIST_STRU* NAS_MML_GetSuitPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stSuitPlmnListInfo);
}





NAS_MML_GMM_PROC_INFO_STRU *NAS_MML_GetGmmProcInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stGmmProcInfo);
}


VOS_VOID NAS_MML_SetGmmProcType(
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16   enGmmProcType
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stGmmProcInfo.enGmmProcType = enGmmProcType;
    return;
}


VOS_VOID NAS_MML_SetGmmProcFlag(
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16   enGmmProcFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stGmmProcInfo.enGmmProcFlag = enGmmProcFlag;
    return;
}


VOS_VOID NAS_MML_SetSmProcFlag(
    NAS_MML_SM_PROC_FLAG_ENUM_UINT8     enSmProcFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enSmProcFlag = enSmProcFlag;
    return;
}


NAS_MML_SM_PROC_FLAG_ENUM_UINT8 NAS_MML_GetSmProcFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enSmProcFlag;
}


VOS_UINT8 NAS_MML_GetEpsServiceConnStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEpsServiceConnStatusFlg;
}


VOS_VOID  NAS_MML_InitSuitPlmnListInfo(
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnListInfo
)
{
    VOS_UINT32                          ucIndex;

    PS_MEM_SET(pstSuitPlmnListInfo, 0, sizeof(NAS_MML_SUIT_PLMN_LIST_STRU));
    pstSuitPlmnListInfo->ucSuitPlmnNum = 0;

    for (ucIndex = 0 ; ucIndex < MMC_LMM_MAX_SRCH_PLMN_NUM; ucIndex++ )
    {
        pstSuitPlmnListInfo->astSuitPlmnList[ucIndex].ulMcc = NAS_MML_INVALID_MCC;
        pstSuitPlmnListInfo->astSuitPlmnList[ucIndex].ulMnc = NAS_MML_INVALID_MNC;
    }

    return;
}




NAS_MML_CONN_STATUS_INFO_STRU* NAS_MML_GetConnStatus(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus)  ;
}


VOS_VOID NAS_MML_SetRrcConnStatusFlg(
    VOS_UINT8                           ucRrcStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucRrcStatusFlg
        = ucRrcStatusFlg;
}



VOS_VOID NAS_MML_SetCsSigConnStatusFlg(
    VOS_UINT8                           ucCsSigConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsSigConnStatusFlg
        = ucCsSigConnStatusFlg;
}


VOS_UINT8 NAS_MML_GetCsSigConnStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsSigConnStatusFlg;
}


VOS_VOID NAS_MML_SetPsSigConnStatusFlg(
    VOS_UINT8                           ucPsSigConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsSigConnStatusFlg
        = ucPsSigConnStatusFlg;
}



VOS_VOID NAS_MML_SetPsTbfStatusFlg(
    VOS_UINT8                           ucPsTbfStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsTbfStatusFlg
        = ucPsTbfStatusFlg;
}



VOS_UINT8 NAS_MML_GetPsTbfStatusFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsTbfStatusFlg;
}


VOS_VOID NAS_MML_SetEpsSigConnStatusFlg(
    VOS_UINT8                           ucEpsSigConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEpsSigConnStatusFlg
        = ucEpsSigConnStatusFlg;
}


VOS_VOID NAS_MML_SetEpsServiceConnStatusFlg(
    VOS_UINT8                           ucEpsServiceConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEpsServiceConnStatusFlg
        = ucEpsServiceConnStatusFlg;
}


VOS_VOID NAS_MML_SetCsServiceConnStatusFlg(
    VOS_UINT8                           ucCsServiceConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceConnStatusFlg
        = ucCsServiceConnStatusFlg;
}


VOS_UINT8 NAS_MML_GetCsServiceConnStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceConnStatusFlg;
}



VOS_VOID NAS_MML_SetCsServiceBufferStatusFlg(
    VOS_UINT8                           ucCsServiceBufferStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceBufferFlg
        = ucCsServiceBufferStatusFlg;
}



VOS_UINT8 NAS_MML_GetCsServiceBufferStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceBufferFlg;
}



VOS_VOID NAS_MML_SetPsServiceBufferStatusFlg(
    VOS_UINT8                           ucPsServiceBufferStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsServiceBufferFlg
        = ucPsServiceBufferStatusFlg;
}



VOS_UINT8 NAS_MML_GetPsServiceBufferStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsServiceBufferFlg;
}



VOS_VOID NAS_MML_SetCsEmergencyServiceFlg(
    VOS_UINT8                           ucEmergencyServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEmergencyServiceFlg
        = ucEmergencyServiceFlg;
}



VOS_UINT8 NAS_MML_GetCsEmergencyServiceFlg(VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEmergencyServiceFlg);
}


VOS_VOID NAS_MML_SetPsTcServiceFlg(
    VOS_UINT8                           ucPsTcServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsTcServiceFlg
        = ucPsTcServiceFlg;
}



VOS_UINT8 NAS_MML_GetEHplmnSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.ucEhplmnSupportFlg);
}



VOS_UINT8 NAS_MML_GetActingHplmnSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.ucActingHPlmnSupportFlg);
}


VOS_VOID NAS_MML_SetActingHplmnSupportFlg(VOS_UINT8 ucActingHPlmnSupportFlg)
{
   NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.ucActingHPlmnSupportFlg  = ucActingHPlmnSupportFlg;
}




VOS_UINT8 NAS_MML_GetCsAttachAllowFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllow);
}



VOS_UINT8 NAS_MML_GetPsAttachAllowFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllow);
}



VOS_VOID NAS_MML_SetCsAttachAllowFlg(
    VOS_UINT8                           ucCsAttachAllowFlg
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllow) = ucCsAttachAllowFlg;
}



NAS_MML_MO_CALL_STATUS_ENUM_UINT8 NAS_MML_GetMoCallStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoCallStatus);
}



VOS_VOID NAS_MML_SetMoCallStatus(
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enMoCallStatus
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoCallStatus) = enMoCallStatus;
}


NAS_MML_MO_SS_STATUS_ENUM_UINT8 NAS_MML_GetMoSsStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoSsStatus);
}


VOS_VOID NAS_MML_SetMoSsStatus(
    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enMoSsStatus
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoSsStatus) = enMoSsStatus;
}


VOS_UINT8 NAS_MML_GetPsLocalDetachFlag( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsLocalDetachFlag);
}


VOS_VOID NAS_MML_SetPsLocalDetachFlag(VOS_UINT8 ucPsLocalDetachFlag )
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsLocalDetachFlag = ucPsLocalDetachFlag;
}




VOS_VOID NAS_MML_SetPsAttachAllowFlg(
    VOS_UINT8                           ucPsAttachAllowFlg
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllow) = ucPsAttachAllowFlg;
}



VOS_UINT8 *NAS_MML_GetOperatorNameLong(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOperatorNameInfo.aucOperatorNameLong);
}




VOS_UINT8 *NAS_MML_GetOperatorNameShort(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOperatorNameInfo.aucOperatorNameShort);
}



NAS_MML_OPERATOR_NAME_INFO_STRU* NAS_MML_GetOperatorNameInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOperatorNameInfo);
}


VOS_UINT8 NAS_MML_GetPsRestrictRegisterFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictRegister);
}


VOS_UINT8 NAS_MML_GetPsRestrictPagingFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictPagingRsp);
}


VOS_UINT8 NAS_MML_GetPsRestrictNormalServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictNormalService);
}



VOS_UINT8 NAS_MML_GetPsRestrictEmergencyServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictEmergencyService);
}



VOS_UINT8 NAS_MML_GetCsRestrictRegisterFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictRegister);
}


VOS_UINT8 NAS_MML_GetCsRestrictPagingFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictPagingRsp);
}


NAS_MML_ACCESS_RESTRICTION_STRU* NAS_MML_GetCsAcRestrictionInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction);
}


NAS_MML_ACCESS_RESTRICTION_STRU* NAS_MML_GetPsAcRestrictionInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction);
}



VOS_UINT8 NAS_MML_GetCsRestrictNormalServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictNormalService);
}


VOS_UINT8 NAS_MML_GetCsRestrictEmergencyServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictEmergencyService);
}




VOS_VOID NAS_MML_SetCsRestrictRegisterFlg(
    VOS_UINT8                           ucCsRestrictionRegisterFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictRegister = ucCsRestrictionRegisterFlg;
}


VOS_VOID NAS_MML_SetCsRestrictPagingFlg(
    VOS_UINT8                           ucCsRestrictionPagingFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictPagingRsp = ucCsRestrictionPagingFlg;
}


VOS_VOID NAS_MML_SetCsRestrictNormalServiceFlg(
    VOS_UINT8                           ucCsRestrictiNormalServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictNormalService = ucCsRestrictiNormalServiceFlg;
}


VOS_VOID NAS_MML_SetCsRestrictEmergencyServiceFlg(
    VOS_UINT8                           ucCsRestrictiEmergencyServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictEmergencyService = ucCsRestrictiEmergencyServiceFlg;
}




VOS_VOID NAS_MML_SetPsRestrictRegisterFlg(
    VOS_UINT8                           ucPsRestrictionRegisterFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictRegister = ucPsRestrictionRegisterFlg;
}

VOS_VOID NAS_MML_SetPsRestrictPagingFlg(
    VOS_UINT8                           ucPsRestrictionPagingFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictPagingRsp = ucPsRestrictionPagingFlg;
}


VOS_VOID NAS_MML_SetPsRestrictNormalServiceFlg(
    VOS_UINT8                           ucPsRestrictNormalServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictNormalService = ucPsRestrictNormalServiceFlg;
}



VOS_VOID NAS_MML_SetPsRestrictEmergencyServiceFlg(
    VOS_UINT8                           ucPsRestrictiEmergencyServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictEmergencyService = ucPsRestrictiEmergencyServiceFlg;
}



VOS_VOID NAS_MML_ClearCsPsRestrictionAll()
{
    /* 清除CS接入受限信息 */
    NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
    NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
    NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

    /* 清除PS接入受限信息 */
    NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
    NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
    NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);
}


VOS_UINT32 NAS_MML_GetPsRegisterBarToUnBarFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ulPsRegisterBarToUnBarFlag);
}



VOS_VOID NAS_MML_SetPsRegisterBarToUnBarFlg(
    VOS_UINT32                           ulPsUnBarFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ulPsRegisterBarToUnBarFlag = ulPsUnBarFlag;
}


VOS_UINT32 NAS_MML_GetCsRegisterBarToUnBarFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ulCsRegisterBarToUnBarFlag);
}


VOS_VOID NAS_MML_SetCsRegisterBarToUnBarFlg(
    VOS_UINT32                           ulCsUnBarFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ulCsRegisterBarToUnBarFlag = ulCsUnBarFlag;
}


NAS_MML_TIN_TYPE_ENUM_UINT8 NAS_MML_GetTinType( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enTinType;
}


NAS_MML_UE_NETWORK_CAPABILITY_STRU* NAS_MML_GetUeNetWorkCapability(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stUeNetworkCapbility);
}


VOS_VOID NAS_MML_SetUeNetWorkCapability(NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNetworkCapbility)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stUeNetworkCapbility = *pstUeNetworkCapbility;
}


NAS_MML_PLATFORM_RAT_CAP_STRU* NAS_MML_GetPlatformRatCap(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stPlatformRatCap);
}



VOS_VOID NAS_MML_SetRoamCapability(
    NAS_MML_ROAM_CAPABILITY_ENUM_UINT8  enRoamCapability
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.enRoamCapability
                                        = enRoamCapability;
}





VOS_VOID NAS_MML_SetMsSysCfgBand(
    NAS_MML_MS_BAND_INFO_STRU          *pstMsBand
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stMsBand = *pstMsBand;
}



VOS_VOID NAS_MML_SetMsSysCfgPrioRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT8                           ucRatNum;
    VOS_UINT32                          i;

    ucRatNum        = 0;
    PS_MEM_SET(NAS_MML_GetMsPrioRatList()->aucRatPrio,
               NAS_MSCC_PIF_NET_RAT_TYPE_BUTT,
               sizeof(NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8) * NAS_MSCC_PIF_MAX_RAT_NUM);

    for (i = 0; i < NAS_MML_MIN(NAS_MSCC_PIF_MAX_RAT_NUM,pstPrioRatList->ucRatNum); i++)
    {
        if (VOS_FALSE == NAS_MML_Is3Gpp2Rat(pstPrioRatList->aucRatPrio[i]))
        {
            NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList.aucRatPrio[ucRatNum]= pstPrioRatList->aucRatPrio[i];
            ucRatNum ++;
        }
    }

    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList.ucRatNum = ucRatNum;
}




VOS_VOID NAS_MML_SaveEquPlmnList (
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstNewEquPlmnList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulEquPlmnNum;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId;

    /* 先添加当前驻留的plmn信息 */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEplmnList = NAS_MML_GetEquPlmnList();
    pstEplmnList->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEplmnList->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;

    /* 超过当前最大Eplmn容量时，使用最大容量,需要去除RPLMN个数 */
    if (ulPlmnNum > (NAS_MML_MAX_EQUPLMN_NUM - 1))
    {
        ulEquPlmnNum = NAS_MML_MAX_EQUPLMN_NUM - 1;
    }
    else
    {
        ulEquPlmnNum = ulPlmnNum;
    }

    /* EPLMN信息从第一个位置开始记录 */
    for ( i = 0; i < ulEquPlmnNum; i++ )
    {
        pstEplmnList->astEquPlmnAddr[1 + i].ulMcc = pstNewEquPlmnList[i].ulMcc;
        pstEplmnList->astEquPlmnAddr[1 + i].ulMnc = pstNewEquPlmnList[i].ulMnc;
    }

    ulEquPlmnNum ++;

    /* 1.紧急PDN连接存在时，不删除EPLMN列表中的forbidden plmn列表，待释放时删除：
         if there is no PDN connection for emergency bearer services established, the UE shall remove from
         the list any PLMN code that is already in the list of "forbidden PLMNs" or in the list of "forbidden
         PLMNs for GPRS service". If there is a PDN connection for emergency bearer services established, the
         UE shall remove from the list of equivalent PLMNs any PLMN code present in the list of forbidden PLMNs
         or in the list of "forbidden PLMNs for GPRS service" when the PDN connection for emergency bearer services
         is released.
       2.紧急注册时，不能删除EPLMN列表中的forbidden plmn列表(目前不支持)：
         and if the attach procedure is not for emergency bearer services, the UE shall remove from the list any
         PLMN code that is already in the list of "forbidden PLMNs" or in the list of "forbidden PLMNs for GPRS
         service". */
    if (VOS_FALSE == NAS_MML_GetEmcPdpStatusFlg())
    {
        /*从EPLMN列表中删除无效 、禁止和不允许漫游的网络*/
        ulEquPlmnNum = NAS_MML_DelInvalidPlmnFromList(ulEquPlmnNum, pstEplmnList->astEquPlmnAddr);
        ulEquPlmnNum = NAS_MML_DelForbPlmnInList(ulEquPlmnNum, pstEplmnList->astEquPlmnAddr);
    }

    pstEplmnList->ucEquPlmnNum = (VOS_UINT8)ulEquPlmnNum;

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    return;
}


VOS_VOID NAS_MML_UpdateGURplmn (
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 更新全局变量中的LastRPLMN的接入技术 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        NAS_MML_SetLastRplmnRat(enCurrRat);
    }

    /* 更新全局变量中的RPLMN */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        /* 不支持双RPLMN，则W和G的RPLMN都更新 */
        pstRplmnCfgInfo->stGRplmnInNV = *pstRPlmnId;
        pstRplmnCfgInfo->stWRplmnInNV = *pstRPlmnId;

    }
    else
    {
        /* 支持双RPLMN, 则只更新对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            pstRplmnCfgInfo->stGRplmnInNV = *pstRPlmnId;
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            pstRplmnCfgInfo->stWRplmnInNV = *pstRPlmnId;
        }
        else
        {
            ;
        }
    }

    return;
}



VOS_UINT8* NAS_MML_GetSimCsLociFileContent( VOS_VOID )
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    return pstSimInfo->stSimNativeContent.aucCsLociInfoFile;
}


VOS_UINT8* NAS_MML_GetSimPsLociFileContent( VOS_VOID )
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    return pstSimInfo->stSimNativeContent.aucPsLociInfoFile;
}


VOS_VOID  NAS_MML_UpdateSimCsLociFileContent(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    PS_MEM_CPY(pstSimInfo->stSimNativeContent.aucCsLociInfoFile,
               pucCsLociFileContent,
               NAS_MML_CS_LOCI_SIM_FILE_LEN);
}


VOS_VOID  NAS_MML_UpdateSimPsLociFileContent(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    PS_MEM_CPY(pstSimInfo->stSimNativeContent.aucPsLociInfoFile,
               pucPsLociFileContent,
               NAS_MML_PS_LOCI_SIM_FILE_LEN);
}





VOS_UINT8 NAS_MML_GetUePcRecurFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg);
}


VOS_VOID NAS_MML_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
)
{
    NAS_MML_GetMmlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg = ucUePcRecurFlg;
}


VOS_UINT8 NAS_MML_GetOmConnectFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmConnectFlg);
}


VOS_VOID NAS_MML_SetOmConnectFlg(
    VOS_UINT8                           ucOmConnectFlg
)
{
    NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmConnectFlg = ucOmConnectFlg;
}


VOS_UINT8 NAS_MML_GetOmPcRecurEnableFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmPcRecurEnableFlg);
}


VOS_VOID NAS_MML_SetOmPcRecurEnableFlg(
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmPcRecurEnableFlg = ucOmPcRecurEnableFlg;
}



VOS_UINT8 NAS_MML_GetScanCtrlEnableFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.ucScanCtrlFlg);
}


VOS_VOID NAS_MML_SetScanCtrlEnableFlg(VOS_UINT8 ucScanCtrlEnableFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.ucScanCtrlFlg = ucScanCtrlEnableFlg;
}


VOS_VOID NAS_MML_SetHPlmnType(
    NAS_MML_HPLMN_TYPE_ENUM_UINT8       enHPlmnType
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo.enHplmnType = enHPlmnType;
}


NAS_MML_HPLMN_TYPE_ENUM_UINT8 NAS_MML_GetHPlmnType(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo.enHplmnType);
}


VOS_UINT8  NAS_MML_GetSingleDomainRegFailActionSupportFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stSingleDomainFailActionCtx.ucActiveFlag);
}


NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU*  NAS_MML_GetSingleDomainFailActionCtx(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stSingleDomainFailActionCtx);
}


NAS_MML_SOR_ADDITIONAL_LAU_STRU*  NAS_MML_GetSorAdditionalLauCtx(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stAdditionalLau);
}


VOS_VOID NAS_MML_InitSorAdditionalLauCtx(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU    *pstAdditionalLau    = VOS_NULL_PTR;

    pstAdditionalLau = NAS_MML_GetSorAdditionalLauCtx();

    pstAdditionalLau->ucAdditionalLauFlag       = VOS_FALSE;
    pstAdditionalLau->stLai.stPlmnId.ulMcc      = NAS_MML_INVALID_MCC;
    pstAdditionalLau->stLai.stPlmnId.ulMnc      = NAS_MML_INVALID_MNC;
    pstAdditionalLau->stLai.aucLac[0]           = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstAdditionalLau->stLai.aucLac[1]           = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstAdditionalLau->stLai.enCampPlmnNetRat    = NAS_MML_NET_RAT_TYPE_BUTT;
    pstAdditionalLau->stLai.ucRac               = NAS_MML_RAC_INVALID;

    PS_MEM_SET(pstAdditionalLau->auReserv, 0X00, sizeof(pstAdditionalLau->auReserv));

    return ;
}


VOS_UINT8 NAS_MML_GetSorAdditionalLauFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stAdditionalLau.ucAdditionalLauFlag);
}


VOS_VOID NAS_MML_SetBgSearchRegardlessMccList(
    VOS_UINT32                         *pulMcc,
    VOS_UINT8                           ucMccNum
)
{
    VOS_UINT32                          i;

    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stBgSearchRegardlessMcc.ucCustomMccNum = ucMccNum;

    for (i = 0; i < ucMccNum; i++)
    {
        NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stBgSearchRegardlessMcc.aulCostumMccList[i] = pulMcc[i];
    }
}


NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU*  NAS_MML_GetBgSearchRegardlessMccCtx(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stBgSearchRegardlessMcc);
}



VOS_UINT8  NAS_MML_GetRegFailNetWorkFailureCustomFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRegFailNetWorkFailureCustomFlg);
}


VOS_VOID  NAS_MML_SetRegFailNetWorkFailureCustomFlag(VOS_UINT8 ucRegFailNetWorkFailureCustomFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRegFailNetWorkFailureCustomFlg = ucRegFailNetWorkFailureCustomFlg;
}



NAS_MML_PLMN_ID_STRU  NAS_MML_GetImsiHomePlmn(
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_PLMN_ID_STRU                stHplmn;

    VOS_UINT8                           ucUsimMncLenth;
    VOS_UINT8                           ucExactlyComparaFlag;

    ucUsimMncLenth       = NAS_MML_GetUsimMncLen();
    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();

    PS_MEM_SET(&stHplmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    stHplmn.ulMcc |= (pucImsi[1] & NAS_MML_OCTET_HIGH_FOUR_BITS) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stHplmn.ulMcc |= (pucImsi[2] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_EIGHT_BITS;
    stHplmn.ulMcc |= (pucImsi[2] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_TWELVE_BITS;
    stHplmn.ulMnc |= (pucImsi[3] & NAS_MML_OCTET_LOW_FOUR_BITS);
    stHplmn.ulMnc |= (pucImsi[3] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_FOUR_BITS;

    if ((NAS_MML_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucUsimMncLenth)
     && (VOS_TRUE == ucExactlyComparaFlag))
    {
        stHplmn.ulMnc |= (NAS_MML_LOW_BYTE_INVALID) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    else
    {
        stHplmn.ulMnc |= (pucImsi[4] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }

    /* 对于PLMN ID相同的比较，末位为0或者F的情况，已经在新的比较函数中
      处理:NAS_MMC_CompareBcchPlmnwithSimPlmn不需要添加两次PLMN ID，对于
      中移动卡的特殊处理需要保留,添加2位MNC的HPLMN到Hplmn列表中,
      移动MCC=460,MNC=02和07中国移动卡特殊处理
    */
    if (( 0x000604 == stHplmn.ulMcc )
     && ( (0x200   == (stHplmn.ulMnc & 0xFFFF ) )
       || (0x700   == (stHplmn.ulMnc & 0xFFFF))))
    {
        stHplmn.ulMnc &= 0xFF0000;
    }

    return stHplmn;
}




NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8  NAS_MML_GetEHplmnPresentInd( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo.enEHplmnPresentInd;
}



VOS_VOID  NAS_MML_SetPsRegContainDrx(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 enPsRegContainDrx)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.enPsRegisterContainDrx = enPsRegContainDrx;
}


NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 NAS_MML_GetPsRegContainDrx(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.enPsRegisterContainDrx;
}


VOS_VOID  NAS_MML_SetNonDrxTimer(VOS_UINT8  ucPsNonDrxTimerLength)
{
    /* 取值范围0-7，如果大于7则认为无效，取默认值0 */
    if (NAS_MML_NON_DRX_TIMER_MAX < ucPsNonDrxTimerLength)
    {
        ucPsNonDrxTimerLength = NAS_MML_PS_DEFAULT_NON_DRX_TIMER;
    }

    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucNonDrxTimer = ucPsNonDrxTimerLength;
}


VOS_VOID NAS_MML_SetSplitPgCycleCode(
    VOS_UINT8                           ucSplitPgCycleCode
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitPgCycleCode = ucSplitPgCycleCode;
}


VOS_UINT8 NAS_MML_GetNonDrxTimer(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucNonDrxTimer);
}


VOS_VOID  NAS_MML_SetUeUtranPsDrxLen(VOS_UINT8  ucUeUtranPsDrxLen)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeUtranPsDrxLen = ucUeUtranPsDrxLen;
}


VOS_UINT8 NAS_MML_GetUeUtranPsDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeUtranPsDrxLen);
}


VOS_VOID  NAS_MML_SetUeEutranPsDrxLen(VOS_UINT8  ucUeEutranPsDrxLen)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeEutranPsDrxLen = ucUeEutranPsDrxLen;
}


VOS_UINT8 NAS_MML_GetUeEutranPsDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeEutranPsDrxLen);
}


VOS_VOID  NAS_MML_SetWSysInfoDrxLen(VOS_UINT8  ucWSysInfoDrxLength)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucWSysInfoDrxLen = ucWSysInfoDrxLength;
}


VOS_UINT8 NAS_MML_GetWSysInfoDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucWSysInfoDrxLen);
}


VOS_VOID  NAS_MML_SetLSysInfoDrxLen(VOS_UINT8  ucLSysInfoDrxLength)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucLSysInfoDrxLen = ucLSysInfoDrxLength;
}


VOS_UINT8 NAS_MML_GetLSysInfoDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucLSysInfoDrxLen);
}

VOS_UINT8 NAS_MML_GetSplitPgCycleCode(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitPgCycleCode);
}


VOS_UINT8 NAS_MML_GetSplitOnCcch(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitOnCcch);
}


VOS_VOID NAS_MML_SetSplitOnCcch(VOS_UINT8 ucSplitOnCcch)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitOnCcch = ucSplitOnCcch;
}



VOS_VOID  NAS_MML_SetPlmnExactlyComparaFlg(VOS_UINT8  ucPlmnExactlyComparaFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPlmnExactlyCompareFlg = ucPlmnExactlyComparaFlag;
}


VOS_VOID  NAS_MML_SetHplmnRegisterCtrlFlg(VOS_UINT8  ucHplmnRegisterFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnRegisterCtrlFlg = ucHplmnRegisterFlg;
}



VOS_UINT8 NAS_MML_GetHplmnRegisterCtrlFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnRegisterCtrlFlg);
}



VOS_VOID  NAS_MML_SetH3gCtrlFlg(VOS_UINT8  ucH3gFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucH3gCtrlFlg = ucH3gFlg;
}



VOS_UINT8 NAS_MML_GetH3gCtrlFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucH3gCtrlFlg);
}



VOS_UINT8 NAS_MML_GetPlmnExactlyComparaFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPlmnExactlyCompareFlg);
}



VOS_VOID  NAS_MML_SetUsimMncLen(VOS_UINT8  ucUsimMncLength)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucUsimMncLen = ucUsimMncLength;
}


VOS_UINT8 NAS_MML_GetUsimMncLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucUsimMncLen);
}


VOS_VOID  NAS_MML_SetSupportCsServiceFLg(VOS_UINT8  ucCsServiceFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportCsServiceFlg = ucCsServiceFlg;
}


VOS_UINT8  NAS_MML_GetSupportCsServiceFLg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportCsServiceFlg;
}



NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU* NAS_MML_GetUserCfgExtEhplmnInfo( VOS_VOID )
{
    NAS_MML_HPLMN_CFG_INFO_STRU         *pstHplmnCfg;

    pstHplmnCfg = NAS_MML_GetHplmnCfg();


    return &(pstHplmnCfg->stUserCfgExtEhplmnInfo);
}




VOS_VOID NAS_MML_SetEplmnValidFlg(
    VOS_UINT8                           ucEplmnValidFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEquPlmnInfo.ucValidFlg = ucEplmnValidFlg;
}


VOS_UINT8 NAS_MML_GetEplmnValidFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEquPlmnInfo.ucValidFlg);
}



VOS_UINT8 NAS_MML_GetIsrSupportFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsrSupportFlg);
}


VOS_VOID NAS_MML_SetIsrSupportFlg(
    VOS_UINT8                           ucIsrSupport
)
{
    (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsrSupportFlg) = ucIsrSupport;
}





OM_RING_ID NAS_MML_GetErrLogRingBufAddr(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.pstRingBuffer;
}


VOS_VOID NAS_MML_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.pstRingBuffer = pRingBuffer;

    return;
}



VOS_UINT8 NAS_MML_GetErrlogCtrlFlag(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.ucErrLogCtrlFlag;
}


VOS_VOID NAS_MML_SetErrlogCtrlFlag(VOS_UINT8 ucFlag)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.ucErrLogCtrlFlag = ucFlag;

    return;
}


VOS_UINT16 NAS_MML_GetErrlogAlmLevel(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.usAlmLevel;
}


VOS_VOID NAS_MML_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.usAlmLevel = usAlmLevel;

    return;
}


VOS_UINT32 NAS_MML_GetErrlogOverflowCnt(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.ulOverflowCnt;
}


VOS_VOID NAS_MML_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.ulOverflowCnt = ulOverflowCnt;

    return;
}


NAS_MML_ERRLOG_CSFB_MT_INFO_STRU* NAS_MML_GetCsfbMtInfoAddr(VOS_VOID)
{
    return &g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo;
}


VOS_VOID NAS_MML_SetCsfbMtCurrState(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState
)
{
    NAS_MML_GetCsfbMtInfoAddr()->enCurrState = enCsfbMtState;

    return;
}


NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32 NAS_MML_GetCsfbMtCurrState(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.enCurrState;
}


VOS_VOID NAS_MML_AddCsfbMtRecordPositionNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulPositionNum++;

    return;
}


VOS_UINT32 NAS_MML_GetCsfbMtRecordPositionNum(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulPositionNum;
}


VOS_VOID NAS_MML_ClrCsfbMtRecordPositionNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulPositionNum = 0;

    return;
}


VOS_VOID NAS_MML_AddCsfbMtRecordStateNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulStateNum++;

    return;
}


VOS_UINT32 NAS_MML_GetCsfbMtRecordStateNum(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulStateNum;
}


VOS_VOID NAS_MML_ClrCsfbMtRecordStateNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulStateNum = 0;

    return;
}


VOS_VOID NAS_MML_InitCsfbMtInfo(VOS_VOID)
{
    NAS_MML_ERRLOG_CSFB_MT_INFO_STRU       *pstCsfbMtInfo   = VOS_NULL_PTR;
    NAS_MNTN_POSITION_INFO_STRU            *pstPositionInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU    *pstStateInfo    = VOS_NULL_PTR;
    VOS_UINT32                              i;

    pstCsfbMtInfo = NAS_MML_GetCsfbMtInfoAddr();

    NAS_MML_SetCsfbMtCurrState(NAS_ERR_LOG_CSFB_MT_STATE_NULL);

    for (i = 0; i < NAS_ERR_LOG_MAX_POSITION_RECORD_NUM; i++)
    {
        pstPositionInfo = &(pstCsfbMtInfo->astPositionInfo[i]);

        PS_MEM_SET(pstPositionInfo,
                   0x0,
                   sizeof(NAS_MNTN_POSITION_INFO_STRU));
    }

    NAS_MML_ClrCsfbMtRecordPositionNum();

    for (i = 0; i < NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM; i++)
    {
        pstStateInfo = &(pstCsfbMtInfo->astStateInfo[i]);
        pstStateInfo->enCsfbMtState  = NAS_ERR_LOG_CSFB_MT_STATE_NULL;
        pstStateInfo->ulMmState      = 0;
        pstStateInfo->ulCause        = 0;
        pstStateInfo->ulTick         = 0;
    }

    NAS_MML_ClrCsfbMtRecordStateNum();

    return;
}



NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU* NAS_MML_GetErrLogNwSearchInfoAddr(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stNwSrchInfo);
}


VOS_UINT8 NAS_MML_GetErrLogNwSrchCfgActiveFlag(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->ucCfgActiveFlag;
}


VOS_VOID NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_UINT8 ucFlag)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ucCfgActiveFlag = ucFlag;
}


VOS_UINT32 NAS_MML_GetErrLogNwSrchCfgRecordNum(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->ulCfgRecordNum;
}


VOS_VOID NAS_MML_SetErrLogNwSrchCfgRecordNum(VOS_UINT32 ulNum)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ulCfgRecordNum = ulNum;
}


VOS_VOID NAS_MML_AddErrLogNwSearchCount(VOS_VOID)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ulSearchCount++;
}


VOS_VOID NAS_MML_ClrErrLogNwSearchCount(VOS_VOID)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ulSearchCount = 0;
}


VOS_UINT32 NAS_MML_GetErrLogOosEvent(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->enOosEvent;
}


VOS_VOID NAS_MML_SetErrLogOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent
)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->enOosEvent = enOosEvent;
}



VOS_UINT32 NAS_MML_GetErrLogCsOosCause(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->enCsOosCause;
}


VOS_VOID NAS_MML_SetErrLogCsOosCause(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause
)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->enCsOosCause = enOosCause;
}


VOS_UINT32 NAS_MML_GetErrLogPsOosCause(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->enPsOosCause;
}


VOS_VOID NAS_MML_SetErrLogPsOosCause(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause
)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->enPsOosCause = enOosCause;
}


VOS_VOID NAS_MML_InitErrLogNwSearchInfo(VOS_VOID)
{
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU *pstNwSrchInfo = VOS_NULL_PTR;

    pstNwSrchInfo = NAS_MML_GetErrLogNwSearchInfoAddr();

    PS_MEM_SET(pstNwSrchInfo, 0x0, sizeof(NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU));

    pstNwSrchInfo->enCsOosCause   = NAS_ERR_LOG_OOS_CAUSE_NULL;
    pstNwSrchInfo->enPsOosCause   = NAS_ERR_LOG_OOS_CAUSE_NULL;
    pstNwSrchInfo->enSrchRat      = NAS_ERR_LOG_RATMODE_BUTT;
    pstNwSrchInfo->ulSearchType   = 0xFF;

    return;
}


VOS_VOID NAS_MML_SetErrLogGMsIdType(
    VOS_UINT8                               ucGMsIdType
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGMsIdType = ucGMsIdType;

    return;
}


VOS_UINT8 NAS_MML_GetErrLogGMsIdType(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGMsIdType;
}


VOS_VOID NAS_MML_SetErrLogGPagingType(
    VOS_UINT8                               ucGPagingType
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGPagingType = ucGPagingType;

    return;
}


VOS_UINT8 NAS_MML_GetErrLogGPagingType(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGPagingType;
}


VOS_VOID NAS_MML_SetErrLogWCnDomainId(
    VOS_UINT32                              ulWCnDomainId
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWCnDomainId = ulWCnDomainId;

    return;
}


VOS_UINT32 NAS_MML_GetErrLogWCnDomainId(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWCnDomainId;
}


VOS_VOID NAS_MML_SetErrLogWPagingType(
    VOS_UINT32                              ulWPagingType
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingType = ulWPagingType;

    return;
}


VOS_UINT32 NAS_MML_GetErrLogWPagingType(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingType;
}


VOS_VOID NAS_MML_SetErrLogWPagingCause(
    VOS_UINT32                              ulWPagingCause
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingCause = ulWPagingCause;

    return;
}


VOS_UINT32 NAS_MML_GetErrLogWPagingCause(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingCause;
}


VOS_VOID NAS_MML_SetErrLogWPagingUeId(
    VOS_UINT32                              ulWPagingUeId
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingUeId = ulWPagingUeId;

    return;
}


VOS_UINT32 NAS_MML_GetErrLogWPagingUeId(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingUeId;
}


VOS_VOID NAS_MML_InitErrLogPagingInfo(VOS_VOID)
{
    NAS_MML_SetErrLogGMsIdType(GAS_MS_ID_TYPE_BUTT);
    NAS_MML_SetErrLogGPagingType(GAS_PAGING_TYPE_BUTT);
    NAS_MML_SetErrLogWCnDomainId(RRC_NAS_CN_DOMAIN_TYPE_BUTT);
    NAS_MML_SetErrLogWPagingType(RRC_PAGE_CAUSE_BUTT);
    NAS_MML_SetErrLogWPagingCause(RRC_NAS_PAGING_TYPE_BUTT);
    NAS_MML_SetErrLogWPagingUeId(RRC_PAGE_UE_ID_BUTT);

    return;
}


VOS_UINT8 NAS_MML_GetFtmCtrlFlag(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stFtmMntnInfo.ucFtmCtrlFlag;
}



VOS_VOID NAS_MML_SetFtmCtrlFlag(VOS_UINT8 ucFlag)
{
    g_stNasMmlCtx.stMaintainInfo.stFtmMntnInfo.ucFtmCtrlFlag = ucFlag;

    return;
}

/*lint -e593 -e830*/


VOS_VOID NAS_MML_InitErrLogMntnInfo(
    NAS_MML_ERRLOG_MNTN_INFO_STRU          *pstErrLogInfo
)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_CHAR                               *pbuffer;
    OM_RING_ID                              pRingbuffer;
#endif

    pstErrLogInfo->stCtrlInfo.ucErrLogCtrlFlag         = VOS_FALSE;
    pstErrLogInfo->stCtrlInfo.usAlmLevel               = NAS_ERR_LOG_CTRL_LEVEL_CRITICAL;

#if (FEATURE_ON == FEATURE_PTM)
    /* 申请cache的动态内存 , 长度加1是因为读和写指针之间在写满时会相差一个字节 */
    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_MMC ,NAS_MML_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        pstErrLogInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
        return;
    }

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, NAS_MML_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pbuffer);
    }

    /* 保存ringbuffer指针 */
    pstErrLogInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrLogInfo->stBuffInfo.ulOverflowCnt = 0;
#endif

    NAS_MML_InitErrLogPagingInfo();

    NAS_MML_InitCsfbMtInfo();

    NAS_MML_InitErrLogNwSearchInfo();

    NAS_MML_InitErrLogFftSrchInfo();
    return;

}
/*lint +e593 +e830*/

#if (FEATURE_ON == FEATURE_PTM)

VOS_UINT32 NAS_MML_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = NAS_MML_GetErrLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* 如果写入比RING BUFFER还大则不写入 */
    if (ulbytes > NAS_MML_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = NAS_MML_GetErrlogOverflowCnt();
    /* 如果剩余空间不足写入的大小，则清空RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        NAS_MML_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}


VOS_UINT32 NAS_MML_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_MML_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGet(NAS_MML_GetErrLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}


VOS_UINT32 NAS_MML_GetErrLogRingBufUseBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_MML_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferNBytes(NAS_MML_GetErrLogRingBufAddr());
}


VOS_VOID NAS_MML_CleanErrLogRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_MML_GetErrLogRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(NAS_MML_GetErrLogRingBufAddr());

    return;
}
#endif


VOS_UINT32 NAS_MML_RegFailCauseNeedRecord(NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enRegFailCause)
{
    /*以下原因值不需要记录，其余原因需要记录 */
    if ((enRegFailCause == NAS_MML_REG_FAIL_CAUSE_NULL)
     || (enRegFailCause == NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 NAS_MML_GetDelayedCsfbLauFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucDelayedCsfbLauFlg);
}


VOS_VOID NAS_MML_SetDelayedCsfbLauFlg(VOS_UINT8 ucDelayedCsfbLauFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucDelayedCsfbLauFlg = ucDelayedCsfbLauFlg;
}


VOS_UINT8 NAS_MML_GetIsRauNeedFollowOnCsfbMtFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMtFlg);
}


VOS_VOID NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(VOS_UINT8 ucIsRauNeedFollowOnCsfbMtFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMtFlg = ucIsRauNeedFollowOnCsfbMtFlg;
}



VOS_UINT8 NAS_MML_GetIsRauNeedFollowOnCsfbMoFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMoFlg);
}


VOS_VOID NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(VOS_UINT8 ucIsRauNeedFollowOnCsfbMoFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMoFlg = ucIsRauNeedFollowOnCsfbMoFlg;
}



VOS_UINT8 NAS_MML_GetIsDelFddBandSwitchOnFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsDelFddBandSwitchOnFlg);
}


VOS_VOID NAS_MML_SetIsDelFddBandSwitchOnFlg(VOS_UINT8 ucIsDelFddBandSwitchOnFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsDelFddBandSwitchOnFlg = ucIsDelFddBandSwitchOnFlg;
}




VOS_VOID NAS_MML_SetSupportAccBarPlmnSearchFlg(
    VOS_UINT8                           ucAccBarPlmnSearchFlg
)
{
    (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportAccBarPlmnSearchFlg) = ucAccBarPlmnSearchFlg;
}


VOS_UINT8 NAS_MML_GetSupportAccBarPlmnSearchFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportAccBarPlmnSearchFlg);
}


NAS_MML_USER_CFG_OPLMN_INFO_STRU* NAS_MML_GetUserCfgOPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stUserCfgOPlmnInfo);
}


VOS_VOID NAS_MML_SetUserCfgOPlmnInfo(
    NAS_MML_USER_CFG_OPLMN_INFO_STRU       *pstUserCfgOPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stUserCfgOPlmnInfo),
               pstUserCfgOPlmnInfo,
               sizeof(NAS_MML_USER_CFG_OPLMN_INFO_STRU));
}


VOS_VOID  NAS_MML_InitUserCfgOPlmnInfo(
    NAS_MML_USER_CFG_OPLMN_INFO_STRU       *pstUserCfgOPlmnInfo
)
{
    /* 初始化特性使能开关为关闭  */
    pstUserCfgOPlmnInfo->ucActiveFlg    = VOS_FALSE;
    pstUserCfgOPlmnInfo->ucImsiCheckFlg = VOS_TRUE;

    /* 初始化OPLMN版本号信息 */
    PS_MEM_SET( pstUserCfgOPlmnInfo->aucVersion,
                (VOS_UINT8)0X00,
                sizeof(pstUserCfgOPlmnInfo->aucVersion));

    /* 初始化OPLMN信息个数为0 */
    pstUserCfgOPlmnInfo->usOplmnListNum    = 0;

    /* 初始化使能IMSI信息个数为0 */
    pstUserCfgOPlmnInfo->ucImsiPlmnListNum= 0;

    /* 初始化IMSI列表 */
    PS_MEM_SET( pstUserCfgOPlmnInfo->astImsiPlmnList,
                (VOS_UINT8)0X00,
                sizeof(pstUserCfgOPlmnInfo->astImsiPlmnList));

    return;
}




VOS_UINT8  NAS_MML_GetRrcUtranNcellExistFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucUtranNcellExist;
}



VOS_VOID  NAS_MML_SetRrcUtranNcellExistFlg(
    VOS_UINT8                           ucUtranNcellExist
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucUtranNcellExist = ucUtranNcellExist;
}


VOS_UINT8  NAS_MML_GetRrcLteNcellExistFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucLteNcellExist;
}



VOS_VOID  NAS_MML_SetRrcLteNcellExistFlg(
    VOS_UINT8                           ucLteNcellExist
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucLteNcellExist = ucLteNcellExist;
}




VOS_VOID  NAS_MML_SetDsdsRfShareFlg(
    VOS_UINT16                          usDsdsRfShareFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usDsdsRfShareSupportFlg = usDsdsRfShareFlg;

    return;
}


VOS_UINT16 NAS_MML_GetDsdsRfShareFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usDsdsRfShareSupportFlg;
}

VOS_VOID    NAS_MML_SetImsNormalRegStatus(
    NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8                enRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta = enRegStatus;

    return;
}


NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8   NAS_MML_GetImsNormalRegStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta;
}


VOS_VOID    NAS_MML_SetImsVoiceAvailFlg(
    VOS_UINT8                                               ucAvail
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsVoiceAvail = ucAvail;

    return;
}


VOS_UINT8   NAS_MML_GetImsVoiceAvailFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsVoiceAvail;
}


NAS_MML_3GPP_REL_ENUM_UINT8   NAS_MML_GetLte3gppRelVersion(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel.enLteNasRelease;
}


VOS_VOID  NAS_MML_SetLte3gppRelVersion(
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteNasRelease
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel.enLteNasRelease = enLteNasRelease;
    return;
}



VOS_VOID    NAS_MML_SetPersistentBearerState(
    NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8              enPersistentBearerState
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enPersistentBearerState = enPersistentBearerState;

    return;
}


NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MML_GetPersistentBearerState(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enPersistentBearerState;
}



VOS_VOID    NAS_MML_SetImsCallFlg(
    VOS_UINT8                                               ucImsCallFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsCallFlg = ucImsCallFlg;

    return;
}


VOS_UINT8   NAS_MML_GetImsCallFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsCallFlg;
}



VOS_VOID NAS_MML_SetGsmBandCapability(
    VOS_UINT32                          ulBand
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stPlatformBandCap.ulGsmCapability = ulBand;
}


VOS_UINT32 NAS_MML_GetGsmBandCapability(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stPlatformBandCap.ulGsmCapability;
}



VOS_VOID NAS_MML_SetEmcPdpStatusFlg(
    VOS_UINT8                           ucEmcPdpStatusFlg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    pstConnStatus->ucEmcPdpStatusFlg    = ucEmcPdpStatusFlg;
}



VOS_UINT8 NAS_MML_GetEmcPdpStatusFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEmcPdpStatusFlg;
}


VOS_UINT8 NAS_MML_GetImsVoiceInterSysLauEnableFlg (VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceInterSysLauEnable;
}


VOS_VOID NAS_MML_SetImsVoiceInterSysLauEnableFlg( VOS_UINT8 ucImsVoiceInterSysLauEnable )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceInterSysLauEnable = ucImsVoiceInterSysLauEnable;
}


VOS_UINT8 NAS_MML_GetImsVoiceMMEnableFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceMMEnable;
}


VOS_VOID NAS_MML_SetImsVoiceMMEnableFlg( VOS_UINT8 ucImsVoiceMMEnable)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceMMEnable = ucImsVoiceMMEnable;
}


NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 NAS_MML_GetGUNwImsVoiceSupportFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enNwImsVoCap;
}


VOS_VOID NAS_MML_SetGUNwImsVoiceSupportFlg( NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoCap )
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enNwImsVoCap = enNwImsVoCap;
}


NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 NAS_MML_GetLteNwImsVoiceSupportFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enNwImsVoCap;
}


VOS_VOID NAS_MML_SetLteNwImsVoiceSupportFlg( NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoCap )
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enNwImsVoCap = enNwImsVoCap;
}

VOS_UINT8 NAS_MML_GetPsSupportFLg(VOS_VOID)
{
    /* 由于LTE网络系统消息中无PS域支持项，默认填写支持 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enNetRatType)
    {
        return VOS_TRUE;
    }

    return NAS_MML_GetNetworkInfo()->stPsDomainInfo.ucPsSupportFlg;
}


VOS_VOID NAS_MML_SetLcEnableFlg(VOS_UINT8 ucLcEnableFLg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLcEnableFLg = ucLcEnableFLg;

    return;
}


VOS_UINT8 NAS_MML_GetLcEnableFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLcEnableFLg);
}



VOS_VOID NAS_MML_SetIgnoreAuthRejFlg(
    VOS_UINT8                           ucIgnoreAuthRejFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stIgnoreAuthRejInfo.ucIgnoreAuthRejFlg
                               = ucIgnoreAuthRejFlg;
}



VOS_VOID NAS_MML_SetMaxAuthRejNo(
    VOS_UINT8                           ucMaxAuthRejNo
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stIgnoreAuthRejInfo.ucMaxAuthRejNo
                               = ucMaxAuthRejNo;
}



NAS_MML_IGNORE_AUTH_REJ_INFO_STRU * NAS_MML_GetAuthRejInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stIgnoreAuthRejInfo);
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID NAS_MML_SetCallMode(
    NAS_MML_CALL_MODE_ENUM_UINT8       enCallMode
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.enCallMode = enCallMode;

}



NAS_MML_CALL_MODE_ENUM_UINT8  NAS_MML_GetCallMode(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.enCallMode);
}



#endif



VOS_VOID NAS_MML_InitHplmnAuthRejCounter(
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU                      *pstAuthRejInfo
)
{
    pstAuthRejInfo->ucMaxAuthRejNo = 0;
    pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;
    pstAuthRejInfo->ucHplmnPsAuthRejCounter = 0;
    pstAuthRejInfo->ucIgnoreAuthRejFlg = VOS_FALSE;

    return;
}


VOS_VOID  NAS_MML_InitHighPrioRatHplmnTimerCfgInfo(
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighHplmnTimerCfg
)
{
    pstHighHplmnTimerCfg->ulNonFirstSearchTimeLen   = TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER_NON_FIRST_LEN;
    pstHighHplmnTimerCfg->ulFirstSearchTimeLen      = TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_LEN;
    pstHighHplmnTimerCfg->ulFirstSearchTimeCount    = TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_SEARCH_COUNT;
    pstHighHplmnTimerCfg->ulRetrySearchTimeLen      = TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_LEN;
    pstHighHplmnTimerCfg->ucActiveFLg               = VOS_FALSE;
}



VOS_UINT8 NAS_MML_Get3GPP2UplmnNotPrefFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.uc3GPPUplmnNotPrefFlg;
}


VOS_VOID NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_UINT8 uc3GPPUplmnNotPrefFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.uc3GPPUplmnNotPrefFlg = uc3GPPUplmnNotPrefFlg;
}



VOS_UINT8 NAS_MML_GetPdpConnStateInfo( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPdpStatusFlg;
}


VOS_UINT8 NAS_MML_GetSupportSrvccFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportSrvccFlg;
}


VOS_VOID NAS_MML_SetSupportSrvccFlg(VOS_UINT8 ucSupportSrvccFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportSrvccFlg = ucSupportSrvccFlg;
}


VOS_UINT8 NAS_MML_GetSyscfgTriHighRatSrchFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucSyscfgTriHighRatSrchFlg);
}


VOS_VOID NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_UINT8 ucSyscfgTriHighRatSrchFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucSyscfgTriHighRatSrchFlg = ucSyscfgTriHighRatSrchFlg;
}


NAS_MML_DSDS_END_SESSION_DELAY_STRU* NAS_MML_GetDsdsSessionEndDelay(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDsdsEndSesssionDelay);
}


VOS_VOID NAS_MML_SetDsdsEndSessionDelay(NAS_MML_DSDS_END_SESSION_DELAY_STRU *pstDsdsEndSesssionDelay)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDsdsEndSesssionDelay.ulCsRegEndSessionDelayTime
                                                = pstDsdsEndSesssionDelay->ulCsRegEndSessionDelayTime;
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDsdsEndSesssionDelay.ulPsRegEndSessionDelayTime
                                                = pstDsdsEndSesssionDelay->ulPsRegEndSessionDelayTime;

    return;
}


VOS_VOID NAS_MML_InitDsdsSessionEndDelay(NAS_MML_DSDS_END_SESSION_DELAY_STRU *pstDsdsEndSesssionDelay)
{
    PS_MEM_SET(pstDsdsEndSesssionDelay, 0, sizeof(NAS_MML_DSDS_END_SESSION_DELAY_STRU));

    pstDsdsEndSesssionDelay->ulCsRegEndSessionDelayTime = NAS_MML_CS_REG_END_SESSION_DEFAULT_DELAY_TIME;
    pstDsdsEndSesssionDelay->ulPsRegEndSessionDelayTime = NAS_MML_PS_REG_END_SESSION_DEFAULT_DELAY_TIME;

    return;
}


NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *NAS_MML_CALL_GetCallUmtsCodecType(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallUmtsCodecType);
}


VOS_VOID NAS_MML_CALL_SetCallUmtsCodecType(NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *pstCodecType)
{
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU  *pstUmtsCodecType = VOS_NULL_PTR;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;

    ulDefaultValue          = VOS_FALSE;

    pstUmtsCodecType        = &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallUmtsCodecType);

    /* 检查参数是否合法,不合法则使用默认值,个数是否越界 */
    if ( pstCodecType->ucCnt > NAS_MML_CALL_MAX_UMTS_CODEC_TYPE_NUM )
    {
        ulDefaultValue      = VOS_TRUE;
        pstCodecType->ucCnt = NAS_MML_CALL_MAX_UMTS_CODEC_TYPE_NUM;
    }

    pstUmtsCodecType->ucCnt = 0;

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < pstCodecType->ucCnt; i++ )
    {
        if ( (NAS_MML_CALL_UMTS_CODEC_TYPE_AMR   != pstCodecType->aucUmtsCodec[i])
          && (NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2  != pstCodecType->aucUmtsCodec[i])
          && (NAS_MML_CALL_UMTS_CODEC_TYPE_AMRWB != pstCodecType->aucUmtsCodec[i]) )
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }

        /* 将NVIM中的语音能力加入到内存中 */
        pstUmtsCodecType->aucUmtsCodec[pstUmtsCodecType->ucCnt++] = pstCodecType->aucUmtsCodec[i];
    }

    if ( VOS_TRUE == ulDefaultValue )
    {
        pstUmtsCodecType->ucCnt                                   = 0;
        /*lint -e961*/
        pstUmtsCodecType->aucUmtsCodec[pstUmtsCodecType->ucCnt++] = NAS_MML_CALL_UMTS_CODEC_TYPE_AMR;
        pstUmtsCodecType->aucUmtsCodec[pstUmtsCodecType->ucCnt++] = NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2;
        /*lint +e961*/
    }
}


VOS_VOID NAS_MML_CALL_InitCallUmtsCodecType(NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *pstCodecType)
{
    PS_MEM_SET(pstCodecType, 0, sizeof(NAS_MML_CALL_UMTS_CODEC_TYPE_STRU));

    pstCodecType->ucCnt                              = 0;
    /*lint -e961*/
    pstCodecType->aucUmtsCodec[pstCodecType->ucCnt++]= NAS_MML_CALL_UMTS_CODEC_TYPE_AMR;
    pstCodecType->aucUmtsCodec[pstCodecType->ucCnt++]= NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2;
    /*lint -e961*/

    return;
}


NAS_MML_CALL_GSM_CODEC_TYPE_STRU *NAS_MML_CALL_GetCallGsmCodeType(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallGsmCodecType);
}


VOS_VOID NAS_MML_CALL_SetCallGsmCodecType(NAS_MML_CALL_GSM_CODEC_TYPE_STRU *pstCodecType)
{
    /* 初始化语音编码版本列表 */
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU   *pstGsmCodecType  = VOS_NULL_PTR;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;

    ulDefaultValue = VOS_FALSE;

    pstGsmCodecType = &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallGsmCodecType);

    /* 检查参数是否合法,不合法则使用默认值,个数是否越界 */
    if (pstCodecType->ucCodecTypeNum > NAS_MML_CALL_BC_MAX_SPH_VER_NUM )
    {
        ulDefaultValue               = VOS_TRUE;
        pstCodecType->ucCodecTypeNum = NAS_MML_CALL_BC_MAX_SPH_VER_NUM;
    }

    pstGsmCodecType->ucCodecTypeNum = 0;

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < pstCodecType->ucCodecTypeNum; i++ )
    {
        if ( (NAS_MML_CALL_BC_VAL_SPH_VER_FR_1 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_FR_2 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_FR_3 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_HR_1 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_HR_3 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_FR_5 != pstCodecType->aucCodecType[i]))
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }

        /* 将NVIM中的语音能力加入到内存中 */
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum] = pstCodecType->aucCodecType[i];
        pstGsmCodecType->ucCodecTypeNum++;
    }

    /* 此处表示需要使用默认值 */
    if ( VOS_TRUE == ulDefaultValue )
    {
        /*lint -e961*/
        pstGsmCodecType->ucCodecTypeNum                                   = 0;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_3;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_3;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_2;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_1;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_1;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_5;
        /*lint +e961*/
    }
}


VOS_VOID NAS_MML_CALL_InitCallGsmCodecType(NAS_MML_CALL_GSM_CODEC_TYPE_STRU *pstCodecType)
{
    PS_MEM_SET(pstCodecType, 0, sizeof(NAS_MML_CALL_GSM_CODEC_TYPE_STRU));

    /*lint -e961*/
    pstCodecType->ucCodecTypeNum                               = 0;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_3;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_3;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_2;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_1;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_1;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_5;
    /*lint -e961*/

    return;
}


VOS_VOID NAS_MML_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMesgHeader
)
{
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;

    /* 消息在忽略列表中，不进行记录 */
    if (VOS_TRUE == NAS_MML_IsNeedDiscardMsg(pstMesgHeader->ulSenderPid,
            pstMesgHeader->ulReceiverPid, pstMesgHeader->ulMsgName))
    {
        return;
    }

    /* 判断发送id是否是定时器 */
    if (VOS_PID_TIMER == pstMesgHeader->ulSenderPid)
    {
        ulSenderPid      =    ((REL_TIMER_MSG*)pstMesgHeader)->ulSenderPid;
        ulReceiverPid    =    ((REL_TIMER_MSG*)pstMesgHeader)->ulReceiverPid;
        ulMsgName        =    ((REL_TIMER_MSG*)pstMesgHeader)->ulName;
    }
    else
    {
        ulSenderPid      =    pstMesgHeader->ulSenderPid;
        ulReceiverPid    =    pstMesgHeader->ulReceiverPid;
        ulMsgName        =    pstMesgHeader->ulMsgName;
    }
    /* 打印消息 */
    NAS_MML_AddLogEventState((VOS_UINT16)ulSenderPid, (VOS_UINT16)ulReceiverPid, (VOS_UINT16)ulMsgName);

    return;
}



VOS_VOID NAS_MML_AddLogEventState(VOS_UINT16 usSendPid, VOS_UINT16 usReceivePid, VOS_UINT16 usMsgName)
{
    NAS_MML_LOG_EVENT_STATE_STRU       *pstLogEventState;
    NAS_UTRANCTRL_CTX_STRU             *pstUtranCtrlCtx;
    VOS_UINT8                           ucIndex;

    pstUtranCtrlCtx     = NAS_UTRANCTRL_GetUtranCtrlCtx();

    pstLogEventState = &(NAS_MML_GetMmlCtx()->stMaintainInfo.stLogEventState);

    pstLogEventState->ucLatestIndex = (pstLogEventState->ucLatestIndex + 1) % NAS_MML_MAX_LOG_EVENT_STATE_NUM;

    ucIndex                         = pstLogEventState->ucLatestIndex;

    pstLogEventState->stEventState[ucIndex].ulReceiveTime = VOS_GetTick();
    pstLogEventState->stEventState[ucIndex].usSendPid     = usSendPid;
    pstLogEventState->stEventState[ucIndex].usReceivePid  = usReceivePid;
    pstLogEventState->stEventState[ucIndex].usMsgName     = usMsgName;
    pstLogEventState->stEventState[ucIndex].ucMmcFsmId    = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    pstLogEventState->stEventState[ucIndex].ucMmcState    = (VOS_UINT8)NAS_MMC_GetFsmTopState();
    pstLogEventState->stEventState[ucIndex].ucGmmState    = g_GmmGlobalCtrl.ucState;
    pstLogEventState->stEventState[ucIndex].ucMmState     = g_MmGlobalInfo.ucState;
    pstLogEventState->stEventState[ucIndex].ucUtranCtrlFsmId = (VOS_UINT8)pstUtranCtrlCtx->stCurFsm.enFsmId;
    pstLogEventState->stEventState[ucIndex].ucUtranCtrlState = (VOS_UINT8)pstUtranCtrlCtx->stCurFsm.ulState;

    return;
}


VOS_VOID NAS_MML_UpdateExitTime(VOS_VOID)
{
    NAS_MML_LOG_EVENT_STATE_STRU       *pstLogEventState;

    pstLogEventState             = &(NAS_MML_GetMmlCtx()->stMaintainInfo.stLogEventState);

    pstLogEventState->ulExitTime = VOS_GetTick();

    return;
}


VOS_VOID NAS_MML_InitLogEventState(NAS_MML_LOG_EVENT_STATE_STRU *pstLogEventState)
{
    PS_MEM_SET(pstLogEventState, 0, sizeof(NAS_MML_LOG_EVENT_STATE_STRU));

    return;
}


VOS_VOID  NAS_MML_InitChangeNWCauseInfo(NAS_MML_CHANGE_NW_CAUSE_INFO_STRU *pstChangeNWCauseInfo)
{
    PS_MEM_SET(&(pstChangeNWCauseInfo->stChangeNWCauseCfg),
                (VOS_UINT8)0X00,
                sizeof(NAS_MML_CHANGE_NW_CAUSE_CFG_STRU));
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucCsRegCauseNum    = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucPsRegCauseNum    = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucDetachCauseNum   = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucPsSerRejCauseNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucMmAbortCauseNum  = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucCmSerRejCauseNum = 0;

    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucHplmnCsRejCauseChangTo17MaxNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucHplmnPsRejCauseChangTo17MaxNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucVplmnCsRejCauseChangTo17MaxNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucVplmnPsRejCauseChangTo17MaxNum = 0;

    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucHplmnPsRejCauseChangedCout = 0;
    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucHplmnCsRejCauseChangedCout = 0;
    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucVplmnPsRejCauseChangedCout = 0;
    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucVplmnCsRejCauseChangedCout = 0;
}


VOS_VOID NAS_MML_SetChangeNWCauseCfg(const NAS_MML_CHANGE_NW_CAUSE_CFG_STRU *pstChangeNWCauseCfg)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stChangeNWCauseInfo.stChangeNWCauseCfg),
               pstChangeNWCauseCfg,
               sizeof(NAS_MML_CHANGE_NW_CAUSE_CFG_STRU));
}


NAS_MML_CHANGE_NW_CAUSE_CFG_STRU* NAS_MML_GetChangeNWCauseCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stChangeNWCauseInfo.stChangeNWCauseCfg);
}


VOS_UINT8 NAS_MML_GetChangeNWCauseCfgByRejType(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   **pstAdaptCause
)
{
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU   *pstChangeNWCauseCfg  = VOS_NULL_PTR;

    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    switch (enChangeRejType)
    {
        /* CS域注册流程(LU)拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_CS_REG:
            *pstAdaptCause = pstChangeNWCauseCfg->astCsRegAdaptCause;
            return pstChangeNWCauseCfg->ucCsRegCauseNum;

        /* PS域注册流程(ATTACH/RAU)拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_PS_REG:
             *pstAdaptCause = pstChangeNWCauseCfg->astPsRegAdaptCause;
             return pstChangeNWCauseCfg->ucPsRegCauseNum;

        /* 网络GPRS Detach 流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_DETACH:
            *pstAdaptCause = pstChangeNWCauseCfg->astDetachAdaptCause;
            return pstChangeNWCauseCfg->ucDetachCauseNum;

        /* GMM service request流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ:
             *pstAdaptCause = pstChangeNWCauseCfg->astPsSerRejAdaptCause;
            return pstChangeNWCauseCfg->ucPsSerRejCauseNum;

        /* MM ABORT流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_MM_ABORT:
            *pstAdaptCause = pstChangeNWCauseCfg->astMmAbortAdaptCause;
            return pstChangeNWCauseCfg->ucMmAbortCauseNum;

        /* CM Service流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ:
            *pstAdaptCause = pstChangeNWCauseCfg->astCmSerRejAdaptCause;
            return pstChangeNWCauseCfg->ucCmSerRejCauseNum;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_GetChangeNWCauseCfgByRejType: The input in invalid" );
            *pstAdaptCause = VOS_NULL_PTR;
            return 0;
    }
}


VOS_UINT8 NAS_MML_GetHplmnChangeNWCause(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                           ucCause
)
{
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   *pstAdaptCause = VOS_NULL_PTR;
    VOS_UINT8                           ucAdaptCauseNum;
    VOS_UINT32                          i;

    ucAdaptCauseNum = NAS_MML_GetChangeNWCauseCfgByRejType(enChangeRejType, &pstAdaptCause);

    for (i = 0; i < ucAdaptCauseNum; i++)
    {
        if (ucCause == pstAdaptCause[i].ucCnCause)
        {
            return pstAdaptCause[i].ucHplmnCause;
        }
    }

    /* 未找到NV配置拒绝原因值，返回原有拒绝原因值 */
    return ucCause;
}


VOS_UINT8 NAS_MML_GetVplmnChangeNWCause(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                           ucCause
)
{
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   *pstAdaptCause = VOS_NULL_PTR;
    VOS_UINT8                           ucAdaptCauseNum;
    VOS_UINT32                          i;

    ucAdaptCauseNum = NAS_MML_GetChangeNWCauseCfgByRejType(enChangeRejType, &pstAdaptCause);

    for (i = 0; i < ucAdaptCauseNum; i++)
    {
        if (ucCause == pstAdaptCause[i].ucCnCause)
        {
            return pstAdaptCause[i].ucVplmnCause;
        }
    }

    /* 未找到NV配置拒绝原因值，返回原有拒绝原因值 */
    return ucCause;
}


VOS_UINT8 NAS_MML_GetHplmnPsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucHplmnPsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucHplmnPsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MML_GetHplmnCsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucHplmnCsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucHplmnCsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MML_GetVplmnPsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucVplmnPsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucVplmnPsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MML_GetVplmnCsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucVplmnCsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucVplmnCsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MML_IncHplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucHplmnPsRejCauseChangedCout)++;
}


VOS_VOID NAS_MML_IncHplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucHplmnCsRejCauseChangedCout)++;
}


VOS_VOID NAS_MML_IncVplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucVplmnPsRejCauseChangedCout)++;
}


VOS_VOID NAS_MML_IncVplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucVplmnCsRejCauseChangedCout)++;
}


VOS_VOID NAS_MML_ResetHplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucHplmnPsRejCauseChangedCout = 0;
}


VOS_VOID NAS_MML_ResetHplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucHplmnCsRejCauseChangedCout = 0;
}


VOS_VOID NAS_MML_ResetVplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucVplmnPsRejCauseChangedCout = 0;
}


VOS_VOID NAS_MML_ResetVplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucVplmnCsRejCauseChangedCout = 0;
}


NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU *NAS_MML_GetSupportDamPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDamPlmnInfoCfg.stDamPlmnList);
}


NAS_MML_DAM_IMSI_PLMN_LIST_STRU *NAS_MML_GetDamImsiPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDamPlmnInfoCfg.stImsiPlmnList);
}


NAS_MML_DAM_PLMN_INFO_CONFIG_STRU *NAS_MML_GetDamPlmnInfoCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDamPlmnInfoCfg);
}


VOS_UINT32 NAS_MML_GetT3402Len(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ulT3402Len);
}


VOS_VOID NAS_MML_SetT3402Len(
    VOS_UINT32                          ulT3402Len
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ulT3402Len = ulT3402Len;
    return;
}



VOS_VOID NAS_MML_SetEnableLteTrigPlmnSearchFlag(
    VOS_UINT8                           ucEnableLteTrigPlmnSearchFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucEnableLteTrigPlmnSearchFlag = ucEnableLteTrigPlmnSearchFlag;
    return;
}


VOS_VOID NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(
    VOS_UINT32                          ulLteVoiceNotAvailPlmnForbiddenPeriod
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteVoiceNotAvailPlmnForbiddenPeriod = ulLteVoiceNotAvailPlmnForbiddenPeriod;
    return;
}


VOS_UINT32 NAS_MML_GetVoiceNotAvailPlmnForbiddenPeriod(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteVoiceNotAvailPlmnForbiddenPeriod;
}



VOS_UINT8 NAS_MML_GetEnableLteTrigPlmnSearchFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucEnableLteTrigPlmnSearchFlag);
}


VOS_VOID NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(
    VOS_UINT8                           ucAddDamPlmnInDisablePlmnWithRatListFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucAddDamPlmnInDisablePlmnWithRatListFlag = ucAddDamPlmnInDisablePlmnWithRatListFlag;
    return;
}


VOS_UINT8 NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucAddDamPlmnInDisablePlmnWithRatListFlag;
}


VOS_VOID  NAS_MML_InitDamPlmnInfoCfg(
    NAS_MML_DAM_PLMN_INFO_CONFIG_STRU  *pstDamCfgPlmnInfo
)
{
    VOS_UINT32                          i;

    pstDamCfgPlmnInfo->stDamPlmnList.ucPlmnNum   = 0;
    pstDamCfgPlmnInfo->stImsiPlmnList.ucPlmnNum  = 0;
    PS_MEM_SET(pstDamCfgPlmnInfo->stDamPlmnList.aucReserved, 0, sizeof(pstDamCfgPlmnInfo->stDamPlmnList.aucReserved));
    PS_MEM_SET(pstDamCfgPlmnInfo->stImsiPlmnList.aucReserved, 0, sizeof(pstDamCfgPlmnInfo->stImsiPlmnList.aucReserved));

    for (i = 0; i < NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM; i++)
    {
        pstDamCfgPlmnInfo->stDamPlmnList.astPlmnId[i].ulMcc = NAS_MML_INVALID_MCC;
        pstDamCfgPlmnInfo->stDamPlmnList.astPlmnId[i].ulMnc = NAS_MML_INVALID_MNC;
        pstDamCfgPlmnInfo->stImsiPlmnList.astPlmnId[i].ulMcc  = NAS_MML_INVALID_MCC;
        pstDamCfgPlmnInfo->stImsiPlmnList.astPlmnId[i].ulMnc  = NAS_MML_INVALID_MNC;
    }

    return;
}



VOS_VOID NAS_MML_SetRelPsSigConFlg(VOS_UINT8 ucRelPsSigConFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucRelPsSigConFlg = ucRelPsSigConFlg;
}


VOS_UINT8 NAS_MML_GetRelPsSigConFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucRelPsSigConFlg);
}


VOS_UINT8 NAS_MML_GetPdpExistNotStartT3340Flag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucPdpExistNotStartT3340Flag);
}


VOS_VOID NAS_MML_SetPdpExistNotStartT3340Flag(VOS_UINT8 ucPdpExistNotStartT3340Flag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucPdpExistNotStartT3340Flag = ucPdpExistNotStartT3340Flag;
    return;
}



VOS_VOID NAS_MML_SetRelPsSigConCfg_T3340TimerLen(VOS_UINT32 ulTimerLen)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ulT3340TimerLen= ulTimerLen;
}


VOS_UINT32 NAS_MML_GetRelPsSigConCfg_T3340TimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ulT3340TimerLen);
}


VOS_VOID NAS_MML_SetLteRejCause14Flg(VOS_UINT8 ucLteRejCause14Flg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucLteRejCause14Flg = ucLteRejCause14Flg;
}


VOS_UINT8 NAS_MML_GetLteRejCause14Flg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucLteRejCause14Flg);
}


VOS_VOID NAS_MML_SetLteRejCause14EnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteRejCause14EnableLteTimerLen = ulEnalbeLteTimeLen;
}


VOS_UINT32 NAS_MML_GetLteRejCause14EnableLteTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteRejCause14EnableLteTimerLen);
}


VOS_VOID  NAS_MML_SetDsdsMultiModemModeFlg(
    VOS_UINT8                           ucDsdsMultiModemModeFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDsdsMultiModemModeFlg = ucDsdsMultiModemModeFlg;

    return;
}


VOS_UINT8 NAS_MML_GetDsdsMultiModemModeFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDsdsMultiModemModeFlg;
}


VOS_VOID  NAS_MML_SetLowPrioAnycellSearchLteFlg(
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLowPrioAnycellSearchLteFlg = ucLowPrioAnycellSearchLteFlg;

    return;
}


VOS_UINT8 NAS_MML_GetLowPrioAnycellSearchLteFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLowPrioAnycellSearchLteFlg;
}

VOS_VOID  NAS_MML_SetCsmoSupportedFlg(
    VOS_UINT8                           ucCsmoSupportedFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucCsmoSupportedFlg = ucCsmoSupportedFlg;

    return;
}


VOS_UINT8 NAS_MML_GetCsmoSupportedFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucCsmoSupportedFlg;
}



NAS_MML_T3212_TIMER_INFO_CONFIG_STRU* NAS_MML_GetT3212TimerInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stT3212Info);
}



VOS_VOID  NAS_MML_InitT3212TimerCfgInfo(
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212CfgInfo
)
{
    pstT3212CfgInfo->ulT3212NvActiveFlg             = VOS_FALSE;
    pstT3212CfgInfo->ulT3212StartSceneCtrlBitMask   = 0;
    pstT3212CfgInfo->ulT3212Phase1TimeLen           = 0;
    pstT3212CfgInfo->ulT3212Phase1Count             = 0;
    pstT3212CfgInfo->ulT3212Phase2TimeLen           = 0;
    pstT3212CfgInfo->ulT3212Phase2Count             = 0;

    return;
}



VOS_VOID  NAS_MML_InitGetGeoPrioRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoRatList
)
{
    PS_MEM_SET(pstGetGeoRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 默认从G模获取地理位置信息 */
    pstGetGeoRatList->ucRatNum             = 1;
    pstGetGeoRatList->aucRatPrio[0]        = NAS_MML_NET_RAT_TYPE_GSM;

    return;
}


VOS_VOID  NAS_MML_SetHplmnInEplmnDisplayHomeFlg(
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnInEplmnDisplayHomeFlg = ucHplmnInEplmnDisplayHomeFlg;

    return;
}


VOS_UINT8 NAS_MML_GetHplmnInEplmnDisplayHomeFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnInEplmnDisplayHomeFlg;
}


VOS_VOID  NAS_MML_SetProtectMtCsfbPagingProcedureLen(
    VOS_UINT16                          usMtCsfbPagingProcedureLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usMtCsfbPagingProcedureLen = usMtCsfbPagingProcedureLen;

    return;
}


VOS_UINT16 NAS_MML_GetProtectMtCsfbPagingProcedureLen(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usMtCsfbPagingProcedureLen;
}


VOS_VOID NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(
    VOS_UINT8                           ucDeleteRplmnWhenEplmnInvalidFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDeleteRplmnWhenEplmnInvalidFlg
                                                        = ucDeleteRplmnWhenEplmnInvalidFlg;
    return;
}


VOS_UINT8 NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDeleteRplmnWhenEplmnInvalidFlg;
}



VOS_VOID NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_UINT8 ucPsRegFailMaxTimesTrigLauOnceFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsRegFailMaxTimesTrigLauOnceFlg
                                                        = ucPsRegFailMaxTimesTrigLauOnceFlg;
    return;
}


VOS_UINT8 NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsRegFailMaxTimesTrigLauOnceFlg;
}


VOS_VOID NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_UINT8 ucKeepSrchHplmnEvenRejByCause13Flg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepSrchHplmnEvenRejByCause13Flg
                                                        = ucKeepSrchHplmnEvenRejByCause13Flg;
    return;
}


VOS_UINT8 NAS_MML_GetKeepSrchHplmnEvenRejByCause13Flg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepSrchHplmnEvenRejByCause13Flg;
}


VOS_VOID NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(
    VOS_UINT8 ucEpsRejByCause14InVplmnAllowPsRegFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucEpsRejByCause14InVplmnAllowPsRegFlg
                                                = ucEpsRejByCause14InVplmnAllowPsRegFlg;
    return;
}

VOS_UINT8 NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucEpsRejByCause14InVplmnAllowPsRegFlg;
}


NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU* NAS_MML_GetLauRejTrigPlmnSearchCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLauRejTrigPlmnSearchCfg);
}


VOS_VOID  NAS_MML_InitCarryEplmnWhenSrchRplmnCfg(
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU  *pstCarryEplmnWhenSrchRplmnCfg
)
{
    PS_MEM_SET(pstCarryEplmnWhenSrchRplmnCfg, 0x00, sizeof(NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU));

    pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag                           = NAS_MML_CARRY_EPLMN_SWITCH_OFF;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSwitchOn              = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAreaLost              = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAvailableTimerExpired = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneCSFBServiceRej        = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneDisableLte            = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneEnableLte             = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSysCfgSet             = VOS_FALSE;

    return;
}


VOS_VOID NAS_MML_InitLauRejNoRetryWhenCmSrvExistCfg(
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU *pstLauRejNoRetryWhenCmSrvExist
)
{
    PS_MEM_SET(pstLauRejNoRetryWhenCmSrvExist, 0, sizeof(NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU));

    pstLauRejNoRetryWhenCmSrvExist->ucLauRejCauseNum    = 0;

    return;
 }



VOS_VOID NAS_MML_InitLauRejTrigPlmnSearchCfg(
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejTrigPlmnSrchCfg
)
{
    PS_MEM_SET(pstLauRejTrigPlmnSrchCfg, 0x00, sizeof(NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU));

    pstLauRejTrigPlmnSrchCfg->ucCmSrvExistTrigPlmnSearch    = VOS_FALSE;

    pstLauRejTrigPlmnSrchCfg->ucCmSrvTrigPlmnSearchCauseNum = 0;

    return;
}


NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MML_GetGeoPrioRatList(VOS_VOID)
{
    return &(g_stNasMmlCtx.stMsCfgInfo.stCustomCfg.stGetGeoPrioRatList);
}


VOS_VOID NAS_MML_InitOriginalRejectCause(
    NAS_MML_ORIGNAL_REJECT_CAUSE_STRU   *pstOriginalRejectCause
)
{
    pstOriginalRejectCause->ucOriginalRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
}


VOS_VOID  NAS_MML_SetOriginalRejectCause(
    VOS_UINT8                           ucOriginalUeCause
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stOriginalRejectCause.ucOriginalRejectCause = ucOriginalUeCause;

    return;
}


VOS_UINT8  NAS_MML_GetOriginalRejectCause(VOS_UINT32 UlAdaptCause)
{
    if(UlAdaptCause > 255 || UlAdaptCause < 1)
    {
        return NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stOriginalRejectCause.ucOriginalRejectCause;
}



VOS_UINT8 NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchFlag(VOS_VOID)
{
    return (NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag);
}



VOS_UINT32 NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchDelayLen(VOS_VOID)
{
    return (NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ulSearchDelayLen);
}


VOS_VOID  NAS_MML_InitHighPrioPlmnRefreshTriggerBGSearchCfgInfo(
    NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU             *pstHighPrioPlmnRefreshTriggerBGSearchCfg
)
{
    pstHighPrioPlmnRefreshTriggerBGSearchCfg->ucTriggerBGSearchFlag   = 0;
    pstHighPrioPlmnRefreshTriggerBGSearchCfg->ulSearchDelayLen        = 0;
    PS_MEM_SET(pstHighPrioPlmnRefreshTriggerBGSearchCfg->aucReserve, 0x0, sizeof(pstHighPrioPlmnRefreshTriggerBGSearchCfg->aucReserve));
}


VOS_VOID NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchFlag(VOS_UINT8 ucTriggerBGSearchFlag)
{
    NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag = ucTriggerBGSearchFlag;
}



VOS_VOID NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchDelayLen(VOS_UINT32 ulSearchDelayLen)
{
    NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ulSearchDelayLen = ulSearchDelayLen;
}






VOS_VOID NAS_MML_SetDisableLteStartT3402EnableLteFlag(VOS_UINT8 ucT3402Flag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDiableLteStartT3402EnableLteFlg = ucT3402Flag;
}


VOS_UINT8 NAS_MML_GetDisableLteStartT3402EnableLteFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDiableLteStartT3402EnableLteFlg);
}


VOS_VOID NAS_MML_SetHighPrioRatBgEnableLteFlag(NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_ENUM_UINT8 enHighPrioRatTimerNotEnableLteFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.enHighPrioRatTimerNotEnableLteFlag = enHighPrioRatTimerNotEnableLteFlag;
}


NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_ENUM_UINT8 NAS_MML_GetHighPrioRatBgEnableLteFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.enHighPrioRatTimerNotEnableLteFlag);
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MML_InitLteOos2GPrefPlmnSelCfg(NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU *pstLteOos2GPrefPlmnSelCfg)
{
    VOS_UINT32                          i;

    pstLteOos2GPrefPlmnSelCfg->ucImsiListNum = 0;

    for (i = 0; i < NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM; i++)
    {
       pstLteOos2GPrefPlmnSelCfg->astImsiList[i].ulMcc = NAS_MML_INVALID_MCC;
       pstLteOos2GPrefPlmnSelCfg->astImsiList[i].ulMnc = NAS_MML_INVALID_MNC;
    }
}



NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU* NAS_MML_GetLteOos2GPrefPlmnSelCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteOos2GPrefPlmnSelCfg);
}
#endif



VOS_UINT32 NAS_MML_GetRatIndexInPrioRatList(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8         ucNetRat,
    NAS_MSCC_PIF_RAT_PRIO_STRU                  *pstPrioRatList
)
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstRatPrio         = VOS_NULL_PTR;           /* 接入优先级里列表 index表示优先级次序,0最高，2最低 */
    VOS_UINT8                                ucRatNum;                                    /* 接入技术个数  */
    VOS_UINT32                               ulRatIndex;

    ucRatNum                            = pstPrioRatList->ucRatNum;
    pstRatPrio                          = pstPrioRatList->aucRatPrio;

    for (ulRatIndex = 0; ulRatIndex < ucRatNum; ulRatIndex++)
    {
        if (ucNetRat == pstRatPrio[ulRatIndex])
        {
            return ulRatIndex;
        }
    }

    return NAS_MML_INVALID_INDEX;
}


NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU* NAS_MML_GetErrLogFftSrchInfoAddr(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo);
}

VOS_VOID NAS_MML_InitErrLogFftSrchInfo(VOS_VOID)
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU  *pstFftrchInfo = VOS_NULL_PTR;

    pstFftrchInfo = NAS_MML_GetErrLogFftSrchInfoAddr();

    PS_MEM_SET(pstFftrchInfo, 0x0, sizeof(NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU));

    pstFftrchInfo->enMccRatType      = NAS_MSCC_PIF_NET_RAT_TYPE_BUTT;

    /* 初始化 Band Scan结构体 */
    pstFftrchInfo->stCssBandScanInfo.enResult              = CSS_MULTI_BAND_SCAN_RESULT_FAIL_BUTT;
    pstFftrchInfo->stCssBandScanInfo.enGsmCoverageType     = CSS_COVERAGE_TYPE_BUTT;
    pstFftrchInfo->stCssBandScanInfo.enLteCoverageType     = CSS_COVERAGE_TYPE_BUTT;
    pstFftrchInfo->stCssBandScanInfo.enUmtsFddCoverageType = CSS_COVERAGE_TYPE_BUTT;
}


VOS_VOID NAS_MML_SetFftSrchStartTime(VOS_UINT32 ulFftStartSlice)
{
    NAS_TRACE_HIGH("NAS_MML_SetFftSrchStartTime: Start slice:%u", ulFftStartSlice);

    NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo.ulSrchStartSlice
                                                                       = ulFftStartSlice;

    return;
}


VOS_VOID NAS_MML_SetFftSrchBandScanStartTime(
    VOS_UINT32                           ulBandScanStartSlice
)
{
    NAS_TRACE_HIGH("NAS_MML_SetFftSrchBandScanStartTime: Start slice:%u", ulBandScanStartSlice);

    NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo.stCssBandScanInfo.ulBandScanStartSlice
                                                                                    = ulBandScanStartSlice;

    return;
}

VOS_VOID NAS_MML_SaveFftSrchBandScanResultAndFinishTime(
    CSS_MULTI_BAND_SCAN_CNF_STRU         *pstBandScanCnf
)
{
    NAS_MML_ERRLOG_FFT_BAND_SCAN_INFO_STRU *pstBandScanInfo = VOS_NULL_PTR;

    pstBandScanInfo = &(NAS_MML_GetErrLogFftSrchInfoAddr()->stCssBandScanInfo);
    pstBandScanInfo->ulBandScanFinishSlice = VOS_GetSlice();

    if (VOS_NULL_PTR == pstBandScanCnf)
    {
        /* 没有扫频结果，记录为默认值 */
        pstBandScanInfo->enResult               = CSS_MULTI_BAND_SCAN_RESULT_FAIL_BUTT;
        pstBandScanInfo->enGsmCoverageType      = CSS_COVERAGE_TYPE_BUTT;
        pstBandScanInfo->enLteCoverageType      = CSS_COVERAGE_TYPE_BUTT;
        pstBandScanInfo->enUmtsFddCoverageType  = CSS_COVERAGE_TYPE_BUTT;
    }
    else
    {
        pstBandScanInfo->enResult               = pstBandScanCnf->enResult;
        pstBandScanInfo->enGsmCoverageType      = pstBandScanCnf->enGsmCoverageType;
        pstBandScanInfo->enLteCoverageType      = pstBandScanCnf->enLteCoverageType;
        pstBandScanInfo->enUmtsFddCoverageType  = pstBandScanCnf->enUmtsFddCoverageType;

    }

    NAS_TRACE_HIGH("NAS_MML_SaveFftSrchBandScanResultAndFinishTime: result=%u, Coverage: G=%u, U=%u, L=%u",
                pstBandScanInfo->enResult,
                pstBandScanInfo->enGsmCoverageType,
                pstBandScanInfo->enUmtsFddCoverageType,
                pstBandScanInfo->enLteCoverageType);
    return;
}

VOS_VOID NAS_MML_SetFftSrchPlmnSrchRatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 enRatType
)
{
    NAS_TRACE_HIGH("NAS_MML_SetFftSrchPlmnSrchRatType: rat=%u", enRatType);

    NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo.enMccRatType = enRatType;

    return;
}

VOS_VOID NAS_MML_SaveFftSrchResultAndFinishTime(
    VOS_UINT8                            ucResult
)
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU *pstGetGeoSrchLogInfo = VOS_NULL_PTR;

    pstGetGeoSrchLogInfo                    = NAS_MML_GetErrLogFftSrchInfoAddr();
    pstGetGeoSrchLogInfo->ulSrchFinishSlice = VOS_GetSlice();
    pstGetGeoSrchLogInfo->ucSrchRslt        = ucResult;

    NAS_TRACE_HIGH("NAS_MML_SaveFftSrchResultAndFinishTime: result=%u, rat=%u,time: Begin=%u -> End=%u ",
                pstGetGeoSrchLogInfo->ucSrchRslt,
                pstGetGeoSrchLogInfo->enMccRatType,
                pstGetGeoSrchLogInfo->ulSrchStartSlice,
                pstGetGeoSrchLogInfo->ulSrchFinishSlice);

    return;
}


VOS_VOID NAS_MML_SetCellNotSupportCsmoFlg(
    VOS_UINT8                           ucCellNotSupportCsmoFlg
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.ucCellNotSupportCsmoFlg) = ucCellNotSupportCsmoFlg;
}


VOS_UINT8 NAS_MML_GetCellNotSupportCsmoFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.ucCellNotSupportCsmoFlg);
}


PS_BOOL_ENUM_UINT8 NAS_MML_GetCsMoSessionSndFlag(
    NAS_MML_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    PS_BOOL_ENUM_UINT8                  enSessionFlag = VOS_FALSE;

    switch(enSessionType)
    {
        case NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoNornalCallFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoEmergencyCallFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SS:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSsFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SMS:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSmsFlag;
            break;

        default:
            break;
    }

    return enSessionFlag;
}


VOS_VOID NAS_MML_SetCsMoSessionSndFlag(
    NAS_MML_SESSION_TYPE_ENUM_UINT8     enSessionType,
    PS_BOOL_ENUM_UINT8                  enFlag
)
{
    switch(enSessionType)
    {
        case NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoNornalCallFlag = enFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoEmergencyCallFlag = enFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SS:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSsFlag = enFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SMS:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSmsFlag = enFlag;
            break;

        default:
            break;
    }

    return;
}



/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

