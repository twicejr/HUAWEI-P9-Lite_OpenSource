

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafMmaCtx.h"
#include "TafMmaProcNvim.h"
#include "TafLog.h"
#include "NasUsimmApi.h"
#include "TafMmaMntn.h"
#include "TafMmaComFunc.h"

#include "TafSdcCtx.h"

#include "TafStdlib.h"

#include "NasComm.h"
#include "TafMmaSndApp.h"
#include "Taf_Status.h"


#include "ApsCdsInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_COM_FUNC_C

/*****************************************************************************
  2 常量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

TAF_MMA_SESSION_STATUS_MAP_STRU          g_astTafMmaSessionStatusMapTbl[] =
{
    {HRPD_SESSION_STATUS_CLOSE,                    HSM_MMA_SESSION_STATUS_CLOSE},
    {HRPD_SESSION_STATUS_OPEN,                     HSM_MMA_SESSION_STATUS_OPEN},
    {HRPD_SESSION_STATUS_BUTT,                     HSM_MMA_SESSION_STATUS_BUTT},
};
TAF_MMA_CDMA_PHONE_MODE_MAP_STRU         g_astTafMmaCdmaPhoneModeMapTbl[] =
{
    {PHONE_MODE_MINI,                        TAF_SDC_PHONE_MODE_MINI},
    {PHONE_MODE_FULL,                        TAF_SDC_PHONE_MODE_FULL},
    {PHONE_MODE_TXOFF,                       TAF_SDC_PHONE_MODE_TXOFF},
    {PHONE_MODE_RXOFF,                       TAF_SDC_PHONE_MODE_RXOFF},
    {PHONE_MODE_RFOFF,                       TAF_SDC_PHONE_MODE_RFOFF},
    {PHONE_MODE_FT,                          TAF_SDC_PHONE_MODE_FT},
    {PHONE_MODE_RESET,                       TAF_SDC_PHONE_MODE_RESET},
    {PHONE_MODE_VDFMINI,                     TAF_SDC_PHONE_MODE_VDFMINI},
    {PHONE_MODE_POWEROFF,                    TAF_SDC_PHONE_MODE_POWEROFF},
    {PHONE_MODE_LOWPOWER,                    TAF_SDC_PHONE_MODE_LOWPOWER},
};
TAF_MMA_SYS_MODE_MAP_STRU          g_astTafMmaSysModeMapTbl[] =
{
    {SYS_MODE_GSM,                       TAF_SDC_SYS_MODE_GSM},
    {SYS_MODE_WCDMA,                     TAF_SDC_SYS_MODE_WCDMA},
    {SYS_MODE_LTE,                       TAF_SDC_SYS_MODE_LTE},
    {SYS_MODE_CDMA_1X,                   TAF_SDC_SYS_MODE_CDMA_1X},
    {SYS_MODE_EVDO,                      TAF_SDC_SYS_MODE_EVDO},
    {SYS_MODE_HYBRID,                    TAF_SDC_SYS_MODE_HYBRID},
    {SYS_MODE_SVLTE,                     TAF_SDC_SYS_MODE_SVLTE},
};

TAF_MMA_SYS_SUBMODE_MAP_STRU          g_astTafMmaSysSubModeMapTbl[] =
{
    {SYS_SUBMODE_NONE,                    TAF_SDC_SYS_SUBMODE_NONE},
    {SYS_SUBMODE_GSM,                     TAF_SDC_SYS_SUBMODE_GSM},
    {SYS_SUBMODE_GPRS,                    TAF_SDC_SYS_SUBMODE_GPRS},
    {SYS_SUBMODE_EDGE,                    TAF_SDC_SYS_SUBMODE_EDGE},
    {SYS_SUBMODE_WCDMA,                   TAF_SDC_SYS_SUBMODE_WCDMA},

    {SYS_SUBMODE_HSDPA,                   TAF_SDC_SYS_SUBMODE_HSDPA},
    {SYS_SUBMODE_HSUPA,                   TAF_SDC_SYS_SUBMODE_HSUPA},
    {SYS_SUBMODE_HSDPA_HSUPA,             TAF_SDC_SYS_SUBMODE_HSDPA_HSUPA},
    {SYS_SUBMODE_TD_SCDMA,                TAF_SDC_SYS_SUBMODE_TD_SCDMA},
    {SYS_SUBMODE_HSPA_PLUS,               TAF_SDC_SYS_SUBMODE_HSPA_PLUS},

    {SYS_SUBMODE_LTE,                     TAF_SDC_SYS_SUBMODE_LTE},
    {SYS_SUBMODE_DC_HSPA_PLUS,            TAF_SDC_SYS_SUBMODE_DC_HSPA_PLUS},
    {SYS_SUBMODE_DC_MIMO,                 TAF_SDC_SYS_SUBMODE_DC_MIMO},
    {SYS_SUBMODE_CDMA_1X,                 TAF_SDC_SYS_SUBMODE_CDMA_1X},
    {SYS_SUBMODE_EVDO_REL_0,              TAF_SDC_SYS_SUBMODE_EVDO_REL_0},

    {SYS_SUBMODE_EVDO_REL_A,              TAF_SDC_SYS_SUBMODE_EVDO_REL_A},
    {SYS_SUBMODE_HYBRID_EVDO_REL_0,       TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0},
    {SYS_SUBMODE_HYBRID_EVDO_REL_A,       TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A},
    {SYS_SUBMODE_EHRPD,                   TAF_SDC_SYS_SUBMODE_EHRPD},

};

#endif

TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 g_aenRatModeTypeTab[TAF_MMA_RAT_SET_BUTT][TAF_MMA_RAT_SET_BUTT] =
{
                        /* --> L only               ,        -->GUL              ,        -->CL         */
    /* L only --> */    {TAF_MMA_RAT_MODE_GUL_TO_GUL , TAF_MMA_RAT_MODE_GUL_TO_GUL, TAF_MMA_RAT_MODE_GUL_TO_CL} ,
    /* GUL    --> */    {TAF_MMA_RAT_MODE_GUL_TO_GUL , TAF_MMA_RAT_MODE_GUL_TO_GUL, TAF_MMA_RAT_MODE_GUL_TO_CL},
    /* CL     --> */    {TAF_MMA_RAT_MODE_CL_TO_CL   , TAF_MMA_RAT_MODE_CL_TO_GUL , TAF_MMA_RAT_MODE_CL_TO_CL}
};


/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

extern STATUS_CONTEXT_STRU              g_StatusContext;

/*****************************************************************************
  6 函数实现
*****************************************************************************/

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_UpdataVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    /* 如果没有发生变化则不需要更新 */
    if (enVoiceDomain == TAF_SDC_GetVoiceDomain())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_UpdataVoiceDomainNv((VOS_UINT32)enVoiceDomain))
    {
        /* warning打印 */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdataVoiceDomain: updata nv fail!");

        return VOS_FALSE;
    }

    /* 只有在NV更新成功后才能更新全局变量，以免出现状态不一致 */
    TAF_SDC_SetVoiceDomain(enVoiceDomain);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_UpdateLteImsSupportFlag(
    VOS_UINT8                           ucFlag
)
{
    VOS_UINT8                           ucLteImsSupportFlag;
    VOS_UINT8                           ucLteEmsSupportFlag;

    ucLteImsSupportFlag = TAF_SDC_GetLteImsSupportFlag();
    ucLteEmsSupportFlag = TAF_SDC_GetLteEmsSupportFlag();

    /* 如果没有发生变化则不需要更新 */
    if ((ucFlag != ucLteImsSupportFlag)
     || (ucFlag != ucLteEmsSupportFlag))
    {
        if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportNv(ucFlag))
        {
            /* warning打印 */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag: updata Lte Ims support nv fail!");

            return VOS_FALSE;
        }

        TAF_SDC_SetLteImsSupportFlag(ucFlag);
        TAF_SDC_SetLteEmsSupportFlag(ucFlag);
    }

    return VOS_TRUE;
}


VOS_VOID TAF_MMA_TransMsccImsStartResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
)
{
    switch (enResult)
    {
        case NAS_MSCC_PIF_IMS_START_RESULT_SUCC:
            *penErrorCode = TAF_ERR_NO_ERROR;
            break;

        case NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT:
            *penErrorCode = TAF_ERR_IMS_STACK_TIMEOUT;
            break;

        default:
            *penErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return;
}


VOS_VOID TAF_MMA_TransMsccImsStopResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
)
{
    switch (enResult)
    {
        case NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC:
            *penErrorCode = TAF_ERR_NO_ERROR;
            break;

        case NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT:
            *penErrorCode = TAF_ERR_IMS_STACK_TIMEOUT;
            break;

        default:
            *penErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return;
}
#endif


VOS_VOID TAF_MMA_SetSysCfgRatSetFlg(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType,
    VOS_UINT32                         *pucRatExistedFlg
)
{
    if (TAF_MMA_RAT_GSM == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_G_SET;
    }

    if (TAF_MMA_RAT_WCDMA == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_W_SET;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_MMA_RAT_1X == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_1X_SET;
    }

    if (TAF_MMA_RAT_HRPD == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_DO_SET;
    }
#endif

}



VOS_UINT32 TAF_MMA_GetSysCfgRatFlag(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
    VOS_UINT32                         *pulRatExistedFlg
)
{
    VOS_UINT32                          ulPlatformSuppFlg;
    VOS_UINT32                          i;

    /* 判断用户设置的接入技术是否是平台支持的接入技术 */
    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        ulPlatformSuppFlg = TAF_MMA_IsPlatformSupportSpecUserRat(pstRatOrder->aenRatOrder[i]);

        /* 如果不支持，返回失败，如果支持，继续检查下一个 */
        if (VOS_FALSE == ulPlatformSuppFlg)
        {
            return VOS_FALSE;
        }
        else
        {
            TAF_MMA_SetSysCfgRatSetFlg(pstRatOrder->aenRatOrder[i], pulRatExistedFlg);
        }
    }

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_IsUserSettedSysCfgParaValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucCardType;
    VOS_UINT8                           ucRatBalancingEnableFlg;
#endif
    VOS_UINT32                          ulRatExistedFlg;

#if (FEATURE_ON == FEATURE_LTE)
    ucRatBalancingEnableFlg = TAF_MMA_GetRatBalancingEnableFlg();

    ucCardType = USIMM_CARD_NOCARD;
#endif

    ulRatExistedFlg = TAF_MMA_SYS_CFG_RAT_NONE_SET;

    /* 接入技术用户设置没了 */
    if (0 == pstSysCfgPara->stRatOrder.ucRatOrderNum)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == TAF_MMA_GetSysCfgRatFlag(&pstSysCfgPara->stRatOrder, &ulRatExistedFlg))
    {
        return VOS_FALSE;
    }

    /* 如果UE不支持GSM，当设置成G单模时，返回失败;当设置成多模时，给MSCC发送请求时校正去掉G模
        如果UE不支持GSM，当设置成G单模时，已在TAF_MMA_IsPlatformSupportSpecUserRat函数中返回VOS_FALSE
     */

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果是SIM卡，当设置成L单模时，返回失败；当设置成多模时，给MSCC发送请求时校正去掉L模 */
    if (VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
    {
        (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType) ;

        if ( (USIMM_CARD_SIM == ucCardType)
          && (VOS_TRUE       == ucRatBalancingEnableFlg) )
        {
            return VOS_FALSE;
        }
    }
#endif

    /* 1x/HRPD和G/U的冲突判断 */
    if (TAF_MMA_SYS_CFG_RAT_NONE_SET != (ulRatExistedFlg & TAF_MMA_SYS_CFG_RAT_C_SET))
    {
        if (TAF_MMA_SYS_CFG_RAT_NONE_SET != (ulRatExistedFlg & TAF_MMA_SYS_CFG_RAT_GU_SET))
        {
            return VOS_FALSE;
        }
    }

    /* 判断用户设置的频段是否有效 */
    if (VOS_TRUE != TAF_MMA_IsUserSettedGuBandValid(&(pstSysCfgPara->stGuBand)))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE != TAF_MMA_IsUserSettedLBandValid(&(pstSysCfgPara->stLBand)))
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}


VOS_UINT32  TAF_MMA_IsUserSettedGuBandValid(
    TAF_USER_SET_PREF_BAND64           *pstGuBand
)
{
    TAF_MMA_USER_BAND_SET_UN           uGuBand;
    TAF_MMA_UE_BAND_CAPA_ST           *pstBandCap = VOS_NULL_PTR;

    /* 将GU频段 pstSysCfgPara->stGuBand 64位转换为32位的 */
    MN_MMA_Convert64BitBandTo32Bit(pstGuBand, &uGuBand.ulPrefBand);

    MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

    pstBandCap = TAF_MMA_GetUeSupportBandAddr();
    /* 单模或多模时,用户设置的GU和L的频段必须要与当前UE支持的GU和L的频段有重叠频段
       否则禁止用户设置频段下去;当UE支持的GU或L的频段无效时,不检查用户设置的频段 */
    if ((0 == (uGuBand.ulPrefBand & pstBandCap->ulUeGSptBand))
     && (0 != pstBandCap->ulUeGSptBand))
    {
        return VOS_FALSE;
    }

    if ((0 == (uGuBand.ulPrefBand & pstBandCap->ulUeWSptBand))
     && (0 != pstBandCap->ulUeWSptBand))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if(FEATURE_ON == FEATURE_LTE)

VOS_UINT32  TAF_MMA_IsUserSettedLBandValid(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;

    /* 获取用户设置的LBand */
    TAF_MMA_ConvertLteFrequencyBand(pstLBand);

    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    if ((0 == (pstLBand->ulBandLow & pstUeSupportLteBand->ulBandLow))
     && (0 == (pstLBand->ulBandHigh & pstUeSupportLteBand->ulBandHigh))
     && ((0 != pstUeSupportLteBand->ulBandLow)
      || (0 != pstUeSupportLteBand->ulBandHigh)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif





VOS_VOID TAF_MMA_SetAttachAllowFlg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8     ulAttachType
)
{
    if (TAF_MMA_ATTACH_TYPE_GPRS == ulAttachType)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);
    }

    if (TAF_MMA_ATTACH_TYPE_IMSI == ulAttachType)
    {
        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }

    if (TAF_MMA_ATTACH_TYPE_GPRS_IMSI == ulAttachType)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);

        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }

}


VOS_UINT32 TAF_MMA_IsRatOrderChange(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
)
{
    if (pstCurrRat->ucRatOrderNum == pstLastRat->ucRatOrderNum)
    {
        if (0 == PS_MEM_CMP(&(pstCurrRat->aenRatOrder[0]),
                            &(pstLastRat->aenRatOrder[0]),
                            pstLastRat->ucRatOrderNum * sizeof(TAF_MMA_RAT_TYPE_ENUM_UINT8)))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



VOS_VOID TAF_MMA_GetValidUserCfgEhplmnInfo(
    VOS_UINT8                                               ucHplmnMncLen,
    VOS_UINT8                                              *pucImsi,
    VOS_UINT8                                              *pucEhplmnListNum,
    TAF_SDC_PLMN_ID_STRU                                   *pstEhPlmnList,
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
)
{
    VOS_UINT32                                  i;
    VOS_UINT32                                  j;
    VOS_UINT32                                  k;
    VOS_UINT32                                  ulUserCfgEhplmnNum;
    TAF_SDC_PLMN_ID_STRU                        stHPlmn;
    TAF_SDC_PLMN_ID_STRU                        stPlmn;

    ulUserCfgEhplmnNum = pstNvimCfgExtEhplmnInfo->ulNvimEhplmnNum;

    /* 防止结构体数组越界 */
    if (ulUserCfgEhplmnNum > NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM)
    {
        ulUserCfgEhplmnNum = NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    /* 默认用户设置的EHplmn的个数为0个 */
    *pucEhplmnListNum = 0;

    /* 从当前的IMSI中取出home plmn */
    stHPlmn = TAF_SDC_GetImsiHomePlmn(pucImsi, ucHplmnMncLen);

    /* 如果当前的IMSI中的Home Plmn在astImsiPlmnList中，则取当前的EHplmn */
    for (j = 0 ; j < ulUserCfgEhplmnNum; j++)
    {
        for (i = 0 ; i < pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum; i++)
        {
            /* 用户配置的IMSI plmn网络是BCCH格式的 */
            TAF_SDC_ConvertSimPlmnToNasPLMN((TAF_SDC_SIM_FORMAT_PLMN_ID *)&(pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].astImsiPlmnList[i]), &stPlmn);

            if (VOS_TRUE == TAF_SDC_CompareBcchPlmnwithSimPlmn(&stPlmn, &stHPlmn))
            {
                break;
            }
        }

        /* 当前NV中配置的IMSI列表导出的plmn与Hplmn不同 */
        if (i == pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum)
        {
            continue;
        }

        *pucEhplmnListNum = pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum;

        for (k = 0; k < pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum; k++)
        {
            TAF_SDC_ConvertSimPlmnToNasPLMN((TAF_SDC_SIM_FORMAT_PLMN_ID *)&(pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].astEhPlmnList[k]), &stPlmn);
            pstEhPlmnList[k] = stPlmn;
        }

        break;
    }

    return ;
}



VOS_VOID TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penOutSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                         *penOutSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                   *ppTafSdcSysmodServiceRegStaUpdateFunc
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enGetSysmode;
    VOS_UINT32                          ulEntryCnt;
    VOS_UINT32                          i;

    TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU     astSysModeSearchTable[] =
    {
        /* 1.status ind , 2.old/current mode, 3.dest mode, 4.dest submode */
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_BUTT   , TAF_SDC_SYS_SUBMODE_NONE,              TAF_MMA_UpdateSerRegSta_HrpdToNone},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAT_MMA_UpdateSerRegSta_HybridTo1x},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},

        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              TAF_MMA_UpdateSerRegSta_1xToNone},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        TAF_MMA_UpdateSerRegSta_HybridToHrpd},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               TAF_MMA_UpdateSerRegSta_SvlteToLte},

        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_BUTT,              TAF_MMA_UpdateSerRegSta_LteToNone},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAF_MMA_UpdateSerRegSta_SvlteTo1x},

    };

    /* initialize the output param and the const struct here */
    *penOutSysMode                          = TAF_SDC_SYS_MODE_BUTT;
    *penOutSubMode                          = TAF_SDC_SYS_SUBMODE_NONE;

    enGetSysmode = TAF_SDC_GetSysMode();
    ulEntryCnt   = sizeof(astSysModeSearchTable)/sizeof(TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU);

    for (i = 0; i < ulEntryCnt; i++)
    {
        if ((enCdmaNetworkExist == astSysModeSearchTable[i].enCdmaNetworkExist)
         && (enGetSysmode == astSysModeSearchTable[i].enCurSysMode))
        {
            *penOutSysMode = astSysModeSearchTable[i].enNewSysMode;
            *penOutSubMode = astSysModeSearchTable[i].enNewSubMode;
            *ppTafSdcSysmodServiceRegStaUpdateFunc = astSysModeSearchTable[i].pfuncSysmodServiceRegStatusUpdate;
            return;
        }
    }
}


VOS_VOID TAF_MMA_UpdateSerRegSta_HrpdToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enPsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;
}



VOS_VOID TAT_MMA_UpdateSerRegSta_HybridTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta = VOS_TRUE;

    pstSrvInfo->enPsSrvSta    = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta    = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
}


VOS_VOID TAF_MMA_UpdateSerRegSta_1xToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;
}


VOS_VOID TAF_MMA_UpdateSerRegSta_HybridToHrpd(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_PS;

}


VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteToLte(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_PS;
}


VOS_VOID TAF_MMA_UpdateSerRegSta_LteToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enPsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;

}


VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta = VOS_TRUE;

    pstSrvInfo->enPsSrvSta    = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta    = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_MMA_UpdateSrvRegSta_Main(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo,
    TAF_PH_ACCESS_TECH_ENUM_UINT8       enAct
)
{
    if (VOS_TRUE == pstSrvInfo->bitOpCsSrvSta)
    {
        TAF_SDC_SetCsServiceStatus(pstSrvInfo->enCsSrvSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpPsSrvSta)
    {
        TAF_SDC_SetPsServiceStatus(pstSrvInfo->enPsSrvSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvDomain)
    {
        TAF_SDC_SetServiceDomain(pstSrvInfo->enSrvDomain);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvSta)
    {
        TAF_SDC_SetServiceStatus(pstSrvInfo->enSrvSta);
    }

    /* 如果服务状态变化已经启动定时器，注册状态就不需要再检查，
      相应的注册状态已经在上面更新，定时器超时后会再检查注册状态是否上报 */
    if (VOS_TRUE == pstSrvInfo->bitOpCsRegSta)
    {
        TAF_MMA_Report1xCregStatus(pstSrvInfo->enCsRegSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpPsRegSta)
    {
        TAF_MMA_ReportPsRegStatusInClMode(pstSrvInfo->enPsRegSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvSta)
    {
        /* CL模式下的服务状态上报拆分为2个函数，使用bitOpCsRegSta和bitOpPsRegSta区分
            bitOpCsRegSta 和 bitOpCsSrvSta同步设置
            bitOpPsRegSta 和 bitOpPsSrvSta同步设置
        */
        if (VOS_TRUE == pstSrvInfo->bitOpCsRegSta)
        {
            TAF_MMA_Report1xServiceState();
        }

        if (VOS_TRUE == pstSrvInfo->bitOpPsRegSta)
        {
            TAF_MMA_ReportHrpdAndLteServiceState();
        }
    }

}


VOS_VOID TAF_MMA_ChgSysModeAndSrvRegSta(
    TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct,
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate
)
{
    TAF_SDC_SRV_REG_INFO_STRU                               stSrvRegInfo;

    PS_MEM_SET(&stSrvRegInfo, 0x00, sizeof(stSrvRegInfo));

    /* 服务状态延时可维可测 */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    /* ^MODE命令上报处理 */
    Mma_ModeChgReport(enSysMode, enSubMode);

    /* 更新MMA维护的Mode/SubMode */
    TAF_SDC_SetSysMode(enSysMode);

    TAF_SDC_SetSysSubMode(enSubMode);

    /* 执行更新服务状态与注册状态函数 */
    if (VOS_NULL_PTR != pFuncTafSdcSysmodServiceRegStaUpdate)
    {
        pFuncTafSdcSysmodServiceRegStaUpdate(&stSrvRegInfo);

        /* 判断服务状态、注册状态是否变化，变化的话，就上报 */
        TAF_MMA_UpdateSrvRegSta_Main(&stSrvRegInfo, enAct);
    }

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);
}


VOS_UINT8 TAF_MMA_MapHsmSessionStatus(
    HSM_MMA_SESSION_STATUS_ENUM_UINT8  enSessionStatus
)
{
    TAF_MMA_SESSION_STATUS_MAP_STRU    *pstSessionStatusMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSesionStatusMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSessionStatusMapPtr = TAF_MMA_SESSION_STATUS_MAP_TBL_PTR();
    ulSesionStatusMapTblSize = TAF_MMA_SESSION_STATUS_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSesionStatusMapTblSize; ulCnt++)
    {
        if (pstSessionStatusMapPtr[ulCnt].enHsmSessionStatus == enSessionStatus)
        {
            return pstSessionStatusMapPtr[ulCnt].enMmaSessionStatus;
        }
    }

    return HSM_MMA_SESSION_STATUS_BUTT;
}


VOS_UINT8 TAF_MMA_MapCdmaPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
)
{
    TAF_MMA_CDMA_PHONE_MODE_MAP_STRU   *pstCdmaPhoneModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulCdmaPhoneModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstCdmaPhoneModeMapPtr = TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_PTR();
    ulCdmaPhoneModeMapTblSize = TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulCdmaPhoneModeMapTblSize; ulCnt++)
    {
        if (pstCdmaPhoneModeMapPtr[ulCnt].enTafCdmaPhoneMode == enPhoneMode)
        {
            return pstCdmaPhoneModeMapPtr[ulCnt].enNasOmCdmaPhoneMode;
        }
    }
    return PHONE_MODE_BUTT;

}


VOS_UINT8 TAF_MMA_MapSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    TAF_MMA_SYS_MODE_MAP_STRU          *pstSysModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSysModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSysModeMapPtr = TAF_MMA_SYS_MODE_MAP_TBL_PTR();
    ulSysModeMapTblSize = TAF_MMA_SYS_MODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSysModeMapTblSize; ulCnt++)
    {
        if (pstSysModeMapPtr[ulCnt].enTafCdmaSysMode == enSysMode)
        {
            return pstSysModeMapPtr[ulCnt].enNasOmCdmaSysMode;
        }
    }
    return SYS_MODE_BUTT;
}


VOS_UINT8 TAF_MMA_MapSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode
)
{
    TAF_MMA_SYS_SUBMODE_MAP_STRU       *pstSysSubModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSysSubModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSysSubModeMapPtr = TAF_MMA_SYS_SUBMODE_MAP_TBL_PTR();
    ulSysSubModeMapTblSize = TAF_MMA_SYS_SUBMODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSysSubModeMapTblSize; ulCnt++)
    {
        if (pstSysSubModeMapPtr[ulCnt].enTafSysSubMode == enSysSubMode)
        {
            return pstSysSubModeMapPtr[ulCnt].enNasOmSysSubMode;
        }
    }

    return NAS_OM_MMA_SYS_SUBMODE_BUTT;
}


VOS_UINT8 TAF_MMA_MapCdataBearStatus(
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8                     enBearStatus
)
{
    NAS_OM_MMA_PPP_STATUS_ENUM_UINT8                        enPppStatus;

    enPppStatus = PPP_STATUS_INACTIVE;

    if (TAF_PS_CDATA_BEAR_STATUS_ACTIVE == enBearStatus)
    {
        enPppStatus = PPP_STATUS_ACTIVE;
    }
    else if (TAF_PS_CDATA_BEAR_STATUS_IDLE == enBearStatus)
    {
        enPppStatus = PPP_STATUS_IDLE;
    }
    else if (TAF_PS_CDATA_BEAR_STATUS_SUSPEND == enBearStatus)
    {
        enPppStatus = PPP_STATUS_IDLE;
    }
    else
    {
        enPppStatus = PPP_STATUS_INACTIVE;
    }
    return enPppStatus;
}



VOS_VOID TAF_MMA_ConvertMeidToUl(
    VOS_UINT8                          *pucMeid,
    VOS_UINT32                         *pMeid,
    VOS_UINT32                         *pMeidCnt
)
{
    VOS_UINT8                           aucMeid[NAS_OM_MMA_MEID_OCTET_NUM] = {0};
    VOS_UINT32                          ulMeid;
    VOS_UINT32                          ulMeidCnt;

    PS_MEM_CPY(aucMeid, pucMeid, NAS_OM_MMA_MEID_OCTET_NUM);
    ulMeid    = (((VOS_UINT32)aucMeid[0] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
               |(((VOS_UINT32)aucMeid[1] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
               |( (VOS_UINT32)aucMeid[2] & 0x000000ff);
    ulMeidCnt = (((VOS_UINT32)aucMeid[3] << TAF_SDC_MOVEMENT_24_BITS) & 0xff000000)
               |(((VOS_UINT32)aucMeid[4] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
               |(((VOS_UINT32)aucMeid[5] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
               |( (VOS_UINT32)aucMeid[6] & 0x000000ff);

    *pMeid = ulMeid;
    *pMeidCnt = ulMeidCnt;

}

VOS_VOID TAF_MMA_ConvertUimidToUl(
    VOS_UINT8                          *pucUimid,
    VOS_UINT32                         *pulUimidHigh,
    VOS_UINT32                         *pulUimidLow
)
{
    VOS_UINT8                           aucUimid[TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT] = {0};
    VOS_UINT32                          ulUimidHigh;
    VOS_UINT32                          ulUimidLow;

    if ((VOS_NULL_PTR == pucUimid) || ((TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT - 1) < pucUimid[0]))
    {
        return ;
    }

    PS_MEM_CPY(aucUimid, pucUimid, TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT);
    ulUimidHigh = (((VOS_UINT32)aucUimid[4] << TAF_SDC_MOVEMENT_24_BITS) & 0xff000000)
                 |(((VOS_UINT32)aucUimid[3] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
                 |(((VOS_UINT32)aucUimid[2] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
                 |( (VOS_UINT32)aucUimid[1] & 0x000000ff);
    ulUimidLow  = ((((VOS_UINT32)aucUimid[7] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
                 |(((VOS_UINT32)aucUimid[6] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
                 |( (VOS_UINT32)aucUimid[5] & 0x000000ff));


    *pulUimidHigh = ulUimidHigh;
    *pulUimidLow  = ulUimidLow;
}


VOS_VOID TAF_MMA_ConvertImsiToUl(
    VOS_UINT8                          *pucImsi,
    VOS_UINT32                         *pulImsiHigh,
    VOS_UINT32                         *pulImsiLow
)
{
    if ((VOS_NULL_PTR == pucImsi) || ((TAF_SDC_MAX_IMSI_LEN - 1 )< pucImsi[0]))
    {
        return ;
    }

    /*先转成字符串*/
    *pulImsiHigh = ( ((VOS_UINT32)(pucImsi[1]&0xf0) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[2]&0x0f) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[2]&0xf0) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[3]&0x0f) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[3]&0xf0) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[4]&0x0f) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[4]&0xf0) >> TAF_SDC_MOVEMENT_4_BITS));
    *pulImsiLow  = ( ((VOS_UINT32)(pucImsi[5]&0x0f) << TAF_SDC_MOVEMENT_28_BITS)
                   | ((VOS_UINT32)(pucImsi[5]&0xf0) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[6]&0x0f) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[6]&0xf0) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[7]&0x0f) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[7]&0xf0) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[8]&0x0f) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[8]&0xf0) >> TAF_SDC_MOVEMENT_4_BITS));
}



VOS_UINT32 TAF_MMA_ConvertUatiToUl(
    VOS_UINT8                          *pstUati
)
{
    VOS_UINT8                           aucUati[4] = {0};
    VOS_UINT32                          ulUati;

    ulUati = 0;

    PS_MEM_CPY(aucUati, pstUati, 4);

    ulUati = (((VOS_UINT32)aucUati[0] << TAF_SDC_MOVEMENT_24_BITS) & 0xff000000)
            |(((VOS_UINT32)aucUati[1] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
            |(((VOS_UINT32)aucUati[2] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
            |( (VOS_UINT32)aucUati[3] & 0x000000ff);


    return ulUati;

}

MODEM_ID_ASN_ENUM_UINT16 TAF_MMA_MapModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    MODEM_ID_ASN_ENUM_UINT16            enModemIdAsn;

    switch(enModemId)
    {
        case MODEM_ID_0:
            enModemIdAsn = MODEM_0;
            break;
        case MODEM_ID_1:
            enModemIdAsn = MODEM_1;
            break;
        case MODEM_ID_2:
            enModemIdAsn = MODEM_2;
            break;
        default:
            enModemIdAsn = MODEM_BUTT;
    }
    return enModemIdAsn;
}


VOS_UINT32 TAF_MMA_QryCdmaStatusInfo(
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             *pstCdmaCommInfo,
    NAS_OM_MMA_1X_SYS_INFO_STRU                         *pst1xSysInfo,
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                       *pstHrpdSysInfo
)
{
    TAF_SDC_SYS_INFO_STRU               *pstSysInfo;
    TAF_SDC_SYS_MODE_ENUM_UINT8          enSysMode;
    VOS_UINT8                            aucUati[NAS_OM_MMA_UATI_OCTET_LENGTH] = {0};

    TAF_SDC_PHONE_MODE_ENUM_UINT8       enCurPhoneMode;

    enCurPhoneMode = TAF_SDC_GetCurPhoneMode();
    pstSysInfo = TAF_SDC_GetSysInfo();
    enSysMode = TAF_SDC_GetSysMode();
    PS_MEM_CPY(aucUati, pstSysInfo->stHrpdSysInfo.aucCurUATI, NAS_OM_MMA_UATI_OCTET_LENGTH);

    /* clear coverity warning */
    if (TAF_SDC_PHONE_MODE_BUTT == enCurPhoneMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_QryCdmaStatusInfo: Curr Phone Mode is BUTT!");
    }

    /* clear coverity warning */
    if(TAF_SDC_SYS_MODE_BUTT == enSysMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_QryCdmaStatusInfo: Curr System Mode is BUTT!");
    }

    /*cdma comm info*/
    pstCdmaCommInfo->enPhoneMode = TAF_MMA_MapCdmaPhoneMode(enCurPhoneMode);
    pstCdmaCommInfo->enSysMode = TAF_MMA_MapSysMode(enSysMode);
    pstCdmaCommInfo->enModemId = TAF_MMA_MapModemId(pstSysInfo->enModemId);
    pstCdmaCommInfo->ulEsn = TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn;
    TAF_MMA_ConvertMeidToUl(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, &pstCdmaCommInfo->ulMeid, &pstCdmaCommInfo->ulMeidCnt);

    TAF_MMA_ConvertUimidToUl( TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.aucRuimid,
                             &pstCdmaCommInfo->ulRuimidHigh,
                             &pstCdmaCommInfo->ulRuimidLow);

    TAF_MMA_ConvertImsiToUl( TAF_SDC_GetCsimImsi(),
                            &pstCdmaCommInfo->ulImsiHigh,
                            &pstCdmaCommInfo->ulImsiLow);

    pstCdmaCommInfo->enPppStatus = TAF_MMA_MapCdataBearStatus(TAF_PS_GetPppStatus());

    //cdma 1x info
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        pst1xSysInfo->en1xCallState = TAF_SDC_GetXCallState();
        pst1xSysInfo->lNid = pstSysInfo->st1xSysInfo.lNid;
        pst1xSysInfo->lSid = pstSysInfo->st1xSysInfo.lSid;
        pst1xSysInfo->ulMcc = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(pstSysInfo->st1xSysInfo.stServiceInfo.ulMcc);
        pst1xSysInfo->usBandClass = pstSysInfo->st1xSysInfo.usBandClass;
        pst1xSysInfo->usMnc = (VOS_UINT32)TAF_STD_TransformBcdMncToDeciDigit(pstSysInfo->st1xSysInfo.stServiceInfo.usImsi11_12);
        pst1xSysInfo->usFreq = pstSysInfo->st1xSysInfo.usFreq;
        pst1xSysInfo->usBaseId = pstSysInfo->st1xSysInfo.stBaseStationInfo.usBaseId;
    }

    //cdma hrpd info
    if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        pstHrpdSysInfo->usBandClass = pstSysInfo->stHrpdSysInfo.usBandClass;
        pstHrpdSysInfo->ucColorCode = pstSysInfo->stHrpdSysInfo.ucColorCode;
        pstHrpdSysInfo->enSessionStatus = pstSysInfo->stHrpdSysInfo.ucSessionStatus;
        pstHrpdSysInfo->ucSubNetMask = pstSysInfo->stHrpdSysInfo.ucSubNetMask;
        pstHrpdSysInfo->ulMcc = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(pstSysInfo->stHrpdSysInfo.ulMcc);
        pstHrpdSysInfo->ulSessionSeed = pstSysInfo->stHrpdSysInfo.ulSessionSeed;
        pstHrpdSysInfo->usChannel = pstSysInfo->stHrpdSysInfo.usFreq;
        pstHrpdSysInfo->ulSector24 = pstSysInfo->stHrpdSysInfo.ulSector24;
        pstHrpdSysInfo->enSysSubMode = TAF_MMA_MapSysSubMode(pstSysInfo->enSysSubMode);
        pstHrpdSysInfo->ulCurUATI1 = TAF_MMA_ConvertUatiToUl(aucUati);
        pstHrpdSysInfo->ulCurUATI2 = TAF_MMA_ConvertUatiToUl(&aucUati[4]);
        pstHrpdSysInfo->ulCurUATI3 = TAF_MMA_ConvertUatiToUl(&aucUati[8]);
        pstHrpdSysInfo->ulCurUATI4 = TAF_MMA_ConvertUatiToUl(&aucUati[12]);
    }

    return VOS_TRUE;
}

 VOS_UINT8 TAF_MMA_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < PESN_NV_DATA_LEN; ucIndex++)
    {
        if (0x00 != pstPesn->aucPEsn[ucIndex])
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


 VOS_UINT8 TAF_MMA_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < MEID_NV_DATA_LEN_NEW; ucIndex++)
    {
        if (0x00 != pstMeid->aucMeID[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT8 TAF_MMA_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
)
{
    VOS_UINT8                           ucUIMIDByteNum;
    VOS_UINT8                           i;

    /* the first byte of EFRUIMID indicates the bytes num of UIMID (here,the num is 4) in EFRUIMID */
    ucUIMIDByteNum = pucEFRUIMID[0];

    /*
      according to the protocal C.S0023-D_v2.0_R-UIM ,the EF of EFRuimid store the 32-bit UIMID constructed in the following way:

      Bytes              Description                M/O                Length

        1               number of Bytes              M                  1byte

        2               lowest-order byte            M                  1byte

        3                   ...                      M                  1byte

        4                   ...                      M                  1byte

        5                   ...                      M                  1byte

        6                   ...                      O                  1byte

        7                   ...                      O                  1byte

        8               highest-order byte           O                  1byte

        the EF consists of 8 bytes,in which the first byte indicates the bytes num of UIMID (here,the num is 4) in EF,
        so,when check the validity of UIMID,just need to check from the second byte to the fifth byte
        if all the bits of the four bytes which indicates the UIMID value from the second byte to the fifth byte are 1,then UIMID is invalid
        vice versa
    */
    for (i = 1; i <= ucUIMIDByteNum; i++)
    {
        if (0xFF != pucEFRUIMID[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID TAF_MMA_RatFrequentlySwitchRecord(VOS_VOID)
{
    NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU           *pstRatFreqSwitchEvent = VOS_NULL_PTR;
    VOS_UINT32                                              ulNvSwitchNum;
    VOS_UINT32                                              ulEventLength;
    VOS_UINT32                                              ulActuallyReadLength;
    VOS_UINT8                                               ucActiveRptFlag;
    VOS_UINT8                                               ucRatSwitchRptFlag;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel             = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH);

    ucActiveRptFlag     = TAF_SDC_GetErrlogActiveRptFlag();
    ucRatSwitchRptFlag  = TAF_SDC_GetErrlogRatSwitchRptFlag();
    ulNvSwitchNum       = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulEventLength       = sizeof(NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU);

    /* 只有当主动上报的NV打开，才上报 */
    if ((VOS_FALSE == ucActiveRptFlag)
     || (VOS_FALSE == ucRatSwitchRptFlag))
    {
        return;
    }

    pstRatFreqSwitchEvent = (NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU *)PS_MEM_ALLOC(
                                WUEPS_PID_MMA, ulEventLength);

    if (VOS_NULL_PTR == pstRatFreqSwitchEvent)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RatFrequentlySwitchRecord(): PS_MEM_ALLOC error.");

        return;
    }

    PS_MEM_SET(pstRatFreqSwitchEvent, 0x00, ulEventLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&(pstRatFreqSwitchEvent->stHeader),
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulEventLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    pstRatFreqSwitchEvent->ulStatisticTime = TAF_SDC_GetErrlogRatSwitchStatisticTime();
    pstRatFreqSwitchEvent->ulSwitchNum     = ulNvSwitchNum;

    /* 填充结构体中astPositionInfo数组元素 */
    /* 从队列中rear位置开始到队列中front位置拷贝到stGutlFreqSwitchEvent中 */
    ulActuallyReadLength = TAF_SDC_GetRecordFromRatSwitchRingBuf((VOS_CHAR *)pstRatFreqSwitchEvent->astRatSwitchInfo,
                          ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

    if (ulActuallyReadLength != (ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU)))
    {
        PS_MEM_FREE(WUEPS_PID_MMA, pstRatFreqSwitchEvent);

        return;
    }

    TAF_SDC_CleanRatSwitchRingBuf();

    /* 将RAT频繁切换信息发送给ACPU OM模块 */
    TAF_SndAcpuOmFaultErrLogInd(pstRatFreqSwitchEvent, ulEventLength, NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH);

    /* RAT频繁切换，只需要上报，不需要记录到共享缓存中。*/

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)pstRatFreqSwitchEvent,
                           ulEventLength);

    PS_MEM_FREE(WUEPS_PID_MMA, pstRatFreqSwitchEvent);

    return;
}


VOS_VOID TAF_MMA_ReportErrlogOosBegin(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enLostDomain
)
{
    NAS_ERR_LOG_OOS_BEGIN_STRU          stOosBeginEvent;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    VOS_UINT32                          ulIsLogRecord;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_BEGIN);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_OOS_BEGIN_STRU);

    PS_MEM_SET(&stOosBeginEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stOosBeginEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_OOS_BEGIN,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stOosBeginEvent.stPositionInfo);

    /* 获取HPLMN */
    MN_PH_QryApHplmn(&stOosBeginEvent.stHomePlmnId.ulMcc, &stOosBeginEvent.stHomePlmnId.ulMnc);

    stOosBeginEvent.enOosCause      = enOosCause;
    stOosBeginEvent.enLostDomain    = enLostDomain;
    stOosBeginEvent.usGUTCellUlFreq = TAF_SDC_GetAppCellUlFreq();
    stOosBeginEvent.usGUTCellDlFreq = TAF_SDC_GetAppCellDlFreq();
    stOosBeginEvent.ucRssiValue     = TAF_SDC_GetAppRssiValue();

    stOosBeginEvent.ulLteArfcn      = TAF_SDC_GetAppLteArfcn();

    /* 主动上报给AP */
    TAF_SndAcpuOmFaultErrLogInd(&stOosBeginEvent,
                                ulLength,
                                NAS_ERR_LOG_ALM_OOS_BEGIN);

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_BEGIN,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)&stOosBeginEvent,
                           sizeof(stOosBeginEvent));

    return;
}



VOS_VOID TAF_MMA_ReportErrlogOosEnd(
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enResumeDomain
)
{
    NAS_ERR_LOG_OOS_END_STRU            stOosEndEvent;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    VOS_UINT32                          ulIsLogRecord;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_END);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_OOS_END_STRU);

    PS_MEM_SET(&stOosEndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stOosEndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_OOS_END,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stOosEndEvent.stPositionInfo);

    stOosEndEvent.enResumeDomain = enResumeDomain;

    if (NAS_ERR_LOG_OOS_DOMAIN_CS == enResumeDomain)
    {
        stOosEndEvent.ucReportFlag   = TAF_SDC_GetErrLogCsOosReportToAppFlag();

        TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_FALSE);
    }
    else
    {
        stOosEndEvent.ucReportFlag   = TAF_SDC_GetErrLogPsOosReportToAppFlag();

        TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_FALSE);
    }

    stOosEndEvent.usGUTCellDlFreq   = TAF_SDC_GetAppCellDlFreq();
    stOosEndEvent.usGUTCellUlFreq   = TAF_SDC_GetAppCellUlFreq();
    stOosEndEvent.ucRssiValue       = TAF_SDC_GetAppRssiValue();

    stOosEndEvent.ulLteArfcn        = TAF_SDC_GetAppLteArfcn();

    /* 主动上报给AP */
    TAF_SndAcpuOmFaultErrLogInd(&stOosEndEvent,
                                ulLength,
                                NAS_ERR_LOG_ALM_OOS_END);

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_END,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)&stOosEndEvent,
                           sizeof(stOosEndEvent));

    return;
}


VOS_VOID TAF_MMA_ProcErrlogDomainOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldRegState,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState,
    VOS_UINT32                          ulOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enOosDomain
)
{
    VOS_UINT8                           ucReportPowerOnBeginFlag;
    VOS_UINT8                           ucReportPowerOffBeginFlag;


    ucReportPowerOnBeginFlag  = TAF_SDC_GetErrLogReportPowerOnBeginFlag();
    ucReportPowerOffBeginFlag = TAF_SDC_GetErrLogReportPowerOffBeginFlag();

    /* 某个域离开注册状态(即1或者5)时，给AP上报OOS BGEIN消息，
       某个域回到注册状态(即1或者5)时，给AP上报OOS END消息。
     */

    /* 离开注册状态 */
    if (((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == enOldRegState)
      || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == enOldRegState))
     && ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enNewRegState)
      && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enNewRegState)))
    {
        /* 如果之前已经上报过开关机Begin，则不再上报任何原因的Begin */
        if ((VOS_TRUE != ucReportPowerOnBeginFlag)
         && (VOS_TRUE != ucReportPowerOffBeginFlag))
        {
            TAF_MMA_ReportErrlogOosBegin((NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32)ulOosCause,
                                         enOosDomain);
        }

        return;
    }

    /* 回到注册状态 */
    if (((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enOldRegState)
      && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enOldRegState))
     && ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == enNewRegState)
      || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == enNewRegState)))
    {
        TAF_MMA_ReportErrlogOosEnd(enOosDomain);

        TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_FALSE);
        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);

        return;
    }

    return;
}


VOS_VOID TAF_MMA_ProcErrlogOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState,
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstServiceStatus->enCnDomainId)
    {
        TAF_MMA_ProcErrlogDomainOosReport(enOldCsRegState,
                                          pstServiceStatus->enRegState,
                                          pstServiceStatus->ulOosCause,
                                          NAS_ERR_LOG_OOS_DOMAIN_CS);
        return;
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstServiceStatus->enCnDomainId)
    {

        TAF_MMA_ProcErrlogDomainOosReport(enOldPsRegState,
                                          pstServiceStatus->enRegState,
                                          pstServiceStatus->ulOosCause,
                                          NAS_ERR_LOG_OOS_DOMAIN_PS);
        return;

    }

    return;
}


#endif


VOS_VOID TAF_MMA_RecordRegStatusReportFlag(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    /* 如果上报的是无服务，则记录已上报无服务 */
    if ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enRegState)
     && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enRegState))
    {
        if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
        {
            TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_TRUE);
        }
        else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
        {
            TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_TRUE);
        }
        else
        {
            return;
        }
    }

    return;
}


VOS_UINT32 TAF_MMA_IsUsimServiceAvailable(VOS_VOID)
{
    VOS_UINT32                           ulRslt;

    switch (TAF_SDC_GetUsimStatus())
    {
        case TAF_SDC_USIM_STATUS_ROMSIM:
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
            ulRslt = VOS_TRUE;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PIN:
        case TAF_SDC_USIM_STATUS_SIM_PUK:
        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:
        case TAF_SDC_USIM_STATUS_UNVALID:
        case TAF_SDC_USIM_STATUS_NO_PRESENT:
        case TAF_SDC_USIM_STATUS_BUTT:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            ulRslt = VOS_FALSE;
            break;

        default:
            ulRslt = VOS_FALSE;
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_IsUsimServiceAvailable(): something wrong!");
            break;
    }

    return ulRslt;
}



VOS_VOID TAF_MMA_UpdateGeoPlmnIdInfo(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV项关闭时不需要更新 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    pstGetGeoCtx->stGeoPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstGetGeoCtx->stGeoPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstGetGeoCtx->ulGetGeoTickTime  = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}


VOS_VOID TAF_MMA_ConvertSysInfoExSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSrcSysMode,
    MN_PH_SYS_MODE_EX_ENUM_U8          *penDestSysMode
)
{
    switch(enSrcSysMode)
    {

        case TAF_SDC_SYS_MODE_LTE:
           *penDestSysMode = MN_PH_SYS_MODE_EX_LTE_RAT;
            return;

        case TAF_SDC_SYS_MODE_CDMA_1X:
           *penDestSysMode = MN_PH_SYS_MODE_EX_CDMA_RAT;
            return;

        case TAF_SDC_SYS_MODE_EVDO:
           *penDestSysMode = MN_PH_SYS_MODE_EX_EVDO_RAT;
            return;

        case TAF_SDC_SYS_MODE_HYBRID:
           *penDestSysMode = MN_PH_SYS_MODE_EX_HYBRID_RAT;
            return;

        case TAF_SDC_SYS_MODE_SVLTE:
           *penDestSysMode = MN_PH_SYS_MODE_EX_SVLTE_RAT;
            return;

        case TAF_SDC_SYS_MODE_BUTT:
           *penDestSysMode = MN_PH_SYS_MODE_EX_NONE_RAT;
            return;

        default:
           *penDestSysMode = MN_PH_SYS_MODE_EX_BUTT_RAT;
           return;
    }
}


VOS_VOID TAF_MMA_ConvertSysInfoExSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    MN_PH_ConvertSysSubModeToAtFormat_FDD(enSrcSysSubMode, penDestSysSubMode);

    return;
}






VOS_UINT8 TAF_MMA_IsSameAsAppServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucOldCsAppServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucOldPsAppServiceStatus;
    VOS_UINT8                           ucIsSameAsAppSrvStatus;

    ucOldCsAppServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ucOldPsAppServiceStatus = TAF_SDC_GetAppPsServiceStatus();
    ucIsSameAsAppSrvStatus  = VOS_TRUE;


    switch (enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            if (ucOldCsAppServiceStatus != enServiceStatus)
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            if (ucOldPsAppServiceStatus != enServiceStatus)
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            if ( (ucOldCsAppServiceStatus != enServiceStatus)
               ||(ucOldPsAppServiceStatus != enServiceStatus))
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;
        default:
            break;
    }

    return ucIsSameAsAppSrvStatus;
}


VOS_VOID TAF_MMA_UpdateAppSrvStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*打印可维可测*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 系统模式和系统子模式更新到AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    /* 信号质量更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* 服务状态更新到AppNetworkInfo */
    switch(enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE:
        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            /* 这两种服务域只有MMC才会上报，因此PS/CS都需要更新 */
            TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
            TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);
            break;
        default:
            break;
    }

    /*更新总的服务状态*/
    TAF_MMA_UpdateAppReportSrvStatus();

    /*更新总的服务域*/
    TAF_MMA_UpdateAppReportSrvDomain(enCnDomainId);

    return ;

}


VOS_VOID TAF_MMA_UpdateAppRegStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*打印可维可测*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 系统模式和系统子模式更新到AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    /* 信号质量更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* 注册状态更新到AppNetworkInfo */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
    {
        TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
    {
        TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);
    }
    else if(NAS_MSCC_PIF_SRVDOMAIN_CS_PS == enCnDomainId)
    {
        TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
        TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);
    }
    else
    {
        TAF_ERROR_LOG (WUEPS_PID_MMA,
            "TAF_MMA_UpdateAppRegStatusInfo():WARNING:enCurRegStatus is TAF_SDC_REG_STATUS_BUTT");
    }

    return ;
}


VOS_VOID TAF_MMA_UpdateAppNetworkInfo(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*打印可维可测*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 系统模式和系统子模式更新到AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    /* 信号质量更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* 服务状态更新到AppNetworkInfo */
    TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
    TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);

    TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
    TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);

    TAF_SDC_SetAppServiceStatus(pstCurNwInfo->enReportSrvsta);
    TAF_SDC_SetAppServiceDomain(pstCurNwInfo->enServiceDomain);

    return ;

}


VOS_VOID TAF_MMA_UpdateAppServPlmnInfo(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;


    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId), &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId), sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 系统模式和系统子模式更新到AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    return ;

}


VOS_VOID TAF_MMA_UpdateAppReportSrvStatus(VOS_VOID)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppCsServiceStatus;


    ulAppCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ulAppPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

        /* 更新总的服务状态 */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus))
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus)
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_NO_IMSI == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_NO_IMSI == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);

        if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg )
        {
            TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP);
        }
    }

    return;
}


VOS_VOID TAF_MMA_UpdateAppReportSrvDomain(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppCsServiceStatus;


    ulAppCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ulAppPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

     /* 更新总的服务域 */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus)
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
    }

    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetAppServiceStatus() )
    {
        if(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING == enCnDomainId)
        {
            TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_SEARCHING);
        }
        else
        {
            switch(gstMmaValue.stSetMsClass.NewMsClassType)
            {
                case TAF_PH_MS_CLASS_A:
                case TAF_PH_MS_CLASS_B:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
                    break;
                case TAF_PH_MS_CLASS_CC:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
                    break;
                case TAF_PH_MS_CLASS_CG:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
                    break;
                case TAF_PH_MS_CLASS_NULL:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
                default:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
            }
        }
    }

    return;
}


VOS_VOID TAF_MMA_ProcDelayReport(VOS_VOID)
{
    if ( TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
    {
        /*需要延时上报，开启延时上报定时器*/
        TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS, (TAF_MMA_GetDelayReportServiceStatusCfgTimerLen()));
    }

    return;
}



VOS_VOID TAF_MMA_ProcServiceStatusImmediatelyReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    /*上报服务状态，停止延时定时器，更新APPINFO*/
    TAF_MMA_ProcServiceStatusReport(TAF_SDC_GetServiceStatus(), TAF_SDC_GetAppServiceStatus());

    if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);
    }

    TAF_MMA_UpdateAppSrvStatusInfo(pstServiceStatus->enCnDomainId);

    return;
}



VOS_VOID TAF_MMA_ProcServiceStatusNotReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    /*与当前APP保存的服务状态相同则不需要上报*/
    if (VOS_TRUE == TAF_MMA_IsSameAsAppServiceStatus((TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstServiceStatus->enServiceStatus, pstServiceStatus->enCnDomainId))
    {
        /* 当前域从normal service->normal service也更新一下驻留信息和信号强度 */
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);

            TAF_MMA_UpdateAppSrvStatusInfo(pstServiceStatus->enCnDomainId);
        }
    }

    return;
}


VOS_VOID TAF_MMA_FillActForAtCmdCregInClMode(
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enQryRegStaType,
    TAF_PH_ACCESS_TECH_ENUM_UINT8                          *pucAct
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    *pucAct = TAF_PH_ACCESS_TECH_BUTT;

    /* CL模式下CREG查询是1X下的CS注册状态 */
    if (TAF_MMA_QRY_REG_STATUS_TYPE_CS == enQryRegStaType)
    {
        if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_HYBRID  == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_CDMA_1X;
        }
    }
    /* CL模式下CGREG查询的是LTE或HRPD的PS注册状态 */
    else if (TAF_MMA_QRY_REG_STATUS_TYPE_PS == enQryRegStaType)
    {
        if ((TAF_SDC_SYS_MODE_LTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
        }

        if ((TAF_SDC_SYS_MODE_EVDO   == enSysMode)
         || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_EVDO;
        }
    }
    /* EPS状态查询 */
    else
    {
        if ((TAF_SDC_SYS_MODE_LTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
        }
    }

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 更新上报的系统模式和系统子模式 */
    pstAppNwInfo->stAppSysInfo.enSysMode    = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode = pstCurNwInfo->stSysInfo.enSysSubMode;

    return;
}




VOS_VOID TAF_MMA_Add1XToAppSysModeAndSysSubMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penNewAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                             *penNewAppSubMode
)
{
    VOS_UINT32                                              i;
    TAF_SDC_MODIFY_SYSMODE_MAP_TLB_STRU                     astAdd1xSysModeMapTlb[] =
    {
        {TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_0, TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0},
        {TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_A, TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A},
        {TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EHRPD,      TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_EHRPD},
        {TAF_SDC_SYS_MODE_LTE,  TAF_SDC_SYS_SUBMODE_LTE,        TAF_SDC_SYS_MODE_SVLTE,    TAF_SDC_SYS_SUBMODE_LTE},
        {TAF_SDC_SYS_MODE_BUTT, TAF_SDC_SYS_SUBMODE_BUTT,       TAF_SDC_SYS_MODE_CDMA_1X,  TAF_SDC_SYS_SUBMODE_CDMA_1X}
    };

    for (i = 0; i < sizeof(astAdd1xSysModeMapTlb)/sizeof(astAdd1xSysModeMapTlb[0]); i++)
    {
        if ((enCurAppSysMode == astAdd1xSysModeMapTlb[i].enCurAppSysMode)
         && (enCurAppSubMode == astAdd1xSysModeMapTlb[i].enCurAppSubMode))
        {
            *penNewAppSysMode = astAdd1xSysModeMapTlb[i].enNewAppSysMode;
            *penNewAppSubMode = astAdd1xSysModeMapTlb[i].enNewAppSubMode;

            return;
        }
    }

    *penNewAppSysMode = enCurAppSysMode;
    *penNewAppSubMode = enCurAppSubMode;

    return;
}


VOS_VOID TAF_MMA_Del1XFromAppSysModeAndSysSubMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penNewAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                             *penNewAppSubMode
)
{
    VOS_UINT32                                              i;
    TAF_SDC_MODIFY_SYSMODE_MAP_TLB_STRU                     astDel1xSysModeMapTlb[] =
    {
        {TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_0},
        {TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A, TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_A},
        {TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_EHRPD,             TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EHRPD},
        {TAF_SDC_SYS_MODE_SVLTE,    TAF_SDC_SYS_SUBMODE_LTE,               TAF_SDC_SYS_MODE_LTE,  TAF_SDC_SYS_SUBMODE_LTE},
        {TAF_SDC_SYS_MODE_CDMA_1X,  TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAF_SDC_SYS_MODE_BUTT, TAF_SDC_SYS_SUBMODE_BUTT}

    };

    for (i = 0; i < sizeof(astDel1xSysModeMapTlb)/sizeof(astDel1xSysModeMapTlb[0]); i++)
    {
        if ((enCurAppSysMode == astDel1xSysModeMapTlb[i].enCurAppSysMode)
         && (enCurAppSubMode == astDel1xSysModeMapTlb[i].enCurAppSubMode))
        {
            *penNewAppSysMode = astDel1xSysModeMapTlb[i].enNewAppSysMode;
            *penNewAppSubMode = astDel1xSysModeMapTlb[i].enNewAppSubMode;

            return;
        }
    }

    *penNewAppSysMode = enCurAppSysMode;
    *penNewAppSubMode = enCurAppSubMode;

    return;
}


VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   en1xNetworkExist
)
{
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 1X从无服务到有服务 */
    if (TAF_SDC_1X_NETWORK_EXIST == en1xNetworkExist)
    {
        /* PS延时定时器在运行时，如果appnetwork中是evdo或者lte，APP network中需要加上1x */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_Add1XToAppSysModeAndSysSubMode(pstAppNwInfo->stAppSysInfo.enSysMode,
                                                   pstAppNwInfo->stAppSysInfo.enSysSubMode,
                                                   &(pstAppNwInfo->stAppSysInfo.enSysMode),
                                                   &(pstAppNwInfo->stAppSysInfo.enSysSubMode));
        }
        else
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }
    }

    /* 1X从有服务到无服务 */
    if (TAF_SDC_1X_NETWORK_NOT_EXIST == en1xNetworkExist)
    {
        /* CS延时定时器在运行，等定时器超时更新。否则，从APP network中删掉1X */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            /* 如果PS延迟上报定时器在运行，需要将APP network中1X去掉 */
            if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
            {
                TAF_MMA_Del1XFromAppSysModeAndSysSubMode(pstAppNwInfo->stAppSysInfo.enSysMode,
                                                         pstAppNwInfo->stAppSysInfo.enSysSubMode,
                                                         &(pstAppNwInfo->stAppSysInfo.enSysMode),
                                                         &(pstAppNwInfo->stAppSysInfo.enSysSubMode));
            }
            else
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
            }
        }
    }

    return;
}


VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enHrpdNetworkExist
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* HRPD从无到有 */
    if (TAF_SDC_HRPD_NETWORK_EXIST == enHrpdNetworkExist)
    {
        /* CS延时定时器在运行时，APP network中需要加上evdo */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_HYBRID;

            if (TAF_SDC_SYS_SUBMODE_EVDO_REL_0 == pstCurNwInfo->stSysInfo.enSysSubMode)
            {
                pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0;
            }
            else if (TAF_SDC_SYS_SUBMODE_EVDO_REL_A == pstCurNwInfo->stSysInfo.enSysSubMode)
            {
                pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A;
            }
            else
            {
                pstAppNwInfo->stAppSysInfo.enSysSubMode = pstCurNwInfo->stSysInfo.enSysSubMode;
            }
        }
        else
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

    }

    /* HRPD从有到无 */
    if (TAF_SDC_HRPD_NETWORK_NOT_EXIST == enHrpdNetworkExist)
    {
        /* PS延时定时器在运行时，等超时后更新 */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            /* CS延时定时器在运行，APP network中去掉evdo */
            if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
            {
                if (TAF_SDC_SYS_MODE_HYBRID == pstAppNwInfo->stAppSysInfo.enSysMode)
                {
                    pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_CDMA_1X;

                    pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
                }
            }
            else
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
            }
        }
    }

    return;
}


VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enLteNetworkExist
)
{
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* LTE从无到有 */
    if (TAF_SDC_LTE_NETWORK_EXIST == enLteNetworkExist)
    {
        /* CS延时定时器在运行时，如果appnetwork中是1x，APP network中需要加上lte */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_SVLTE;

            pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_LTE;
        }
        else
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

    }

    /* LTE从有到无 */
    if (TAF_SDC_LTE_NETWORK_NOT_EXIST == enLteNetworkExist)
    {
        /* PS延时定时器在运行时，等超时后更新 */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            /* CS延时定时器在运行，APP network中去掉LTE */
            if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
            {
                if (TAF_SDC_SYS_MODE_SVLTE == pstAppNwInfo->stAppSysInfo.enSysMode)
                {
                    pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_CDMA_1X;

                    pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
                }
            }
            else
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
            }
        }
    }

    return;
}





VOS_VOID TAF_MMA_UpdateAppCsSrvInfoInClMode(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsSrvStatus;

    /*更新系统信息和信号强度*/
    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo),
               &(pstCurNwInfo->stSysInfo.st1xSysInfo),
               sizeof(TAF_SDC_1X_SYS_INFO_STRU));

    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo),
               &(pstCurNwInfo->stSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo),
               sizeof(TAF_SDC_1X_SIG_QUALITY_INFO_STRU));


    /*更新CS域服务状态*/
    enCsSrvStatus = TAF_SDC_GetCsServiceStatus();
    TAF_SDC_SetAppCsServiceStatus(enCsSrvStatus);

    TAF_SDC_SetAppCsRegStatus(TAF_SDC_GetCsRegStatus());
}


VOS_VOID TAF_MMA_UpdateAppPsSrvInfoInClMode(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsSrvStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    /*LTE下，需要更新plmn信息和信号质量*/
    enSysMode = TAF_SDC_GetSysMode();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    if ((TAF_SDC_SYS_MODE_LTE == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        /* LTE相关的系统信息，主要是PLMN信息 */
        PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                   &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                   sizeof(TAF_SDC_PLMN_ID_STRU));

        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

        /* 信号质量更新到AppNetworkInfo */
        PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));
    }


    /*更新PS域服务状态*/
    enPsSrvStatus = TAF_SDC_GetPsServiceStatus();
    TAF_SDC_SetAppPsServiceStatus(enPsSrvStatus);
    /*更新PS注册状态*/
    TAF_SDC_SetAppPsRegStatus(TAF_SDC_GetPsRegStatus());
}


VOS_VOID TAF_MMA_SndCsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppCsRegStatus;

    TAF_PH_REG_STATE_STRU               stRegStatus;

    enCsRegStatus      = TAF_SDC_GetCsRegStatus();
    enAppCsRegStatus   = TAF_SDC_GetAppCsRegStatus();
    if (enAppCsRegStatus != enCsRegStatus)
    {
        /*注册状态有更改，需要上报*/
        PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

        stRegStatus.OP_CsRegState = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.RegState      = enCsRegStatus;
        stRegStatus.ucAct         = TAF_PH_ACCESS_TECH_CDMA_1X;

        if (VOS_TRUE == TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
        {
            TAF_MMA_SndRegStatusInd(&stRegStatus);
        }
    }
}


VOS_VOID TAF_MMA_Report1xSidInClMode(
    VOS_INT32                          lSid
)
{
    TAF_SDC_CTX_STRU                   *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx = TAF_SDC_GetSdcCtx();

    if (VOS_TRUE == TAF_MMA_IsSidChangeNeedRpt())
    {
        if (lSid != pstSdcCtx->stNetworkInfo.lSid)
        {
            /*Sid有更改，需要上报*/
            TAF_MMA_ReportCSid(lSid);
        }
    }

    pstSdcCtx->stNetworkInfo.lSid = lSid;
}


VOS_VOID TAF_MMA_Report1xSigQulityInClMode(VOS_VOID)
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU   *pstSdc1xSigQualityInfo    = VOS_NULL_PTR;

    pstSdc1xSigQualityInfo    = TAF_SDC_Get1xSigQualityInfo();
    if (TAF_MMA_CDMA_CSQ_MODE_ENABLE == pstSdc1xSigQualityInfo->enMode)
    {
        if(VOS_TRUE == pstSdc1xSigQualityInfo->cDelayRptFLag)
        {
            /*延迟上报信号强度标志位为VOS_TRUE，清标志位，并上报一次信号强度*/
            pstSdc1xSigQualityInfo->cDelayRptFLag = VOS_FALSE;

            TAF_MMA_SndCdmaCsqInd(pstSdc1xSigQualityInfo->sCdmaRssi,pstSdc1xSigQualityInfo->sCdmaEcIo);
        }
    }
}


VOS_VOID TAF_MMA_DelayReportCsReferCmdInClMode(VOS_VOID)
{
    /* 信号质量是否上报的处理 */
    TAF_MMA_Report1xSigQulityInClMode();

    /* CLOCINFO是否上报的处理 */
    TAF_MMA_Report1xLocinfoInClMode();
}


VOS_VOID TAF_MMA_SndPsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppPsRegStatus;

    TAF_PH_REG_STATE_STRU               stRegStatus;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    TAF_SDC_PLMN_ID_STRU               *pstPlmnId     = VOS_NULL_PTR;

    enSysMode = TAF_SDC_GetSysMode();

    enPsRegStatus      = TAF_SDC_GetPsRegStatus();
    enAppPsRegStatus   = TAF_SDC_GetAppPsRegStatus();

    /*HRPD或LTE模式下的上报*/
    /*注册状态有更改，需要上报*/
    if (enAppPsRegStatus == enPsRegStatus)
    {
        return;
    }
    /* 初始化 */
    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    if ((TAF_SDC_SYS_MODE_SVLTE == enSysMode)
     || (TAF_SDC_SYS_MODE_LTE == enSysMode))
     {
        /* 驻留信息 */
        stRegStatus.OP_Lac              = VOS_TRUE;
        stRegStatus.OP_Rac              = VOS_TRUE;
        stRegStatus.OP_CellId           = VOS_TRUE;
        stRegStatus.OP_Plmn             = VOS_TRUE;
        stRegStatus.ucRac               = TAF_SDC_GetCurrCampRac();
        stRegStatus.CellId.ucCellNum    = 1;
        stRegStatus.CellId.aulCellId[0] = TAF_SDC_GetCurrCampCellId();
        stRegStatus.usLac               = TAF_SDC_GetCurrCampLac();

        pstPlmnId     = TAF_SDC_GetCurrCampPlmnId();
        PS_MEM_CPY(&stRegStatus.Plmn, pstPlmnId, sizeof(TAF_PLMN_ID_STRU));

        /* 将MMC上报的系统子模式转为+CREG/+CGREG命令参数[ACT]中协议规定的接入技术值 */
        stRegStatus.OP_ucAct        = VOS_TRUE;
        stRegStatus.ucAct           = TAF_PH_ACCESS_TECH_E_UTRAN;

        stRegStatus.OP_PsRegState   = VOS_TRUE;
        stRegStatus.ucPsRegState    = enPsRegStatus;

        stRegStatus.ucRatType       = TAF_PH_INFO_LTE_RAT;
    }
    else if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
          || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))  /*HRPD模式下的上报*/
    {
        stRegStatus.OP_PsRegState = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.ucPsRegState  = enPsRegStatus;
        stRegStatus.ucAct         = TAF_PH_ACCESS_TECH_EVDO;
    }
    else
    {
        stRegStatus.OP_PsRegState = VOS_TRUE;
        stRegStatus.ucPsRegState  = enPsRegStatus;
    }


    if (VOS_TRUE == TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
    {
        TAF_MMA_SndRegStatusInd(&stRegStatus);
    }
}





VOS_UINT8 TAF_MMA_IsDelayReportFeatureActiveInClMode(VOS_VOID)
{
    if (VOS_FALSE == TAF_MMA_GetCLDelayReptSrvStatusFlg())
    {
        /*NV 未开启延时上报功能*/
        return VOS_FALSE;
    }

    if (0 == TAF_MMA_GetCLDelayReptSrvStatusTimerLen())
    {
        /*延时上报定时器时长配置为0,不启用延时上报功能*/
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_IsNeedDelayReportServiceStatusInClMode(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNetSrvStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppNetSrvStatus;

    /*延迟上报NV是否开启,返回FALSE为关闭 */
    if (VOS_FALSE == TAF_MMA_IsDelayReportFeatureActiveInClMode())
    {
        return VOS_FALSE;
    }

    /* 用户操作导致的服务状态改变,不启用延时上报 */
    if (VOS_TRUE == TAF_MMA_IsUserOperate())
    {
        return VOS_FALSE;
    }

    enNetSrvStatus    = TAF_SDC_GetServiceStatus();
    enAppNetSrvStatus = TAF_SDC_GetAppServiceStatus();

    /*AppNetInfo记录的是旧的服务状态，与当前服务状态不一致，且是有服务->无服务或限制服务，需要延迟上报*/
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == enAppNetSrvStatus)
    {
        if ((TAF_SDC_REPORT_SRVSTA_NO_SERVICE == enNetSrvStatus)
         || (TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE == enNetSrvStatus))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_IsNeedDelayReportCsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppNetCsRegStatus;

    /*延迟上报NV是否开启 */
    if (VOS_FALSE == TAF_MMA_IsDelayReportFeatureActiveInClMode())
    {
        return VOS_FALSE;
    }

    /* 用户操作导致的服务状态改变,不启用延时上报 */
    if (VOS_TRUE == TAF_MMA_IsUserOperate())
    {
        return VOS_FALSE;
    }

    enNetCsRegStatus    = TAF_SDC_GetCsRegStatus();
    enAppNetCsRegStatus = TAF_SDC_GetAppCsRegStatus();

    /*AppNetInfo记录的是旧的注册状态，与当前注册状态不一致，且是有注册->无注册，需要延迟上报*/
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enAppNetCsRegStatus)
     || (TAF_SDC_REG_REGISTERED_ROAM == enAppNetCsRegStatus))
    {
        if ((TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH == enNetCsRegStatus)
         || (TAF_SDC_REG_NOT_REGISTERED_SEARCHING == enNetCsRegStatus))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_IsNeedDelayReportPsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetPsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppNetPsRegStatus;

    /*延迟上报NV是否开启, FALSE为为开启 */
    if (VOS_FALSE == TAF_MMA_IsDelayReportFeatureActiveInClMode())
    {
        return VOS_FALSE;
    }

    /* 用户操作导致的服务状态改变,不启用延时上报 */
    if (VOS_TRUE == TAF_MMA_IsUserOperate())
    {
        return VOS_FALSE;
    }

    enNetPsRegStatus    = TAF_SDC_GetPsRegStatus();
    enAppNetPsRegStatus = TAF_SDC_GetAppPsRegStatus();

    /*AppNetInfo记录的是旧的注册状态，与当前注册状态不一致，且是有注册->无注册，需要延迟上报*/
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enAppNetPsRegStatus)
     || (TAF_SDC_REG_REGISTERED_ROAM == enAppNetPsRegStatus))
    {
        if ((TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH == enNetPsRegStatus)
         || (TAF_SDC_REG_NOT_REGISTERED_SEARCHING == enNetPsRegStatus))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enDelayTimerId
)
{
    /*根据输入判断需要关闭CS还是PS的延迟上报定时器*/
    if (TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE == enDelayTimerId)
    {
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }

        /* 检查CS域相关AT命令是否需要上报 */
        TAF_MMA_DelayReportCsReferCmdInClMode();

        /* 从stNetworkInfo更新stAppNwInfo,仅CS域相关 */
        TAF_MMA_UpdateAppCsSrvInfoInClMode();
    }
    else if (TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE == enDelayTimerId)
    {
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }

        /* 从stNetworkInfo更新stAppNwInfo,仅PS域相关信息 */
        TAF_MMA_UpdateAppPsSrvInfoInClMode();

        /* 检查PS业务有无延时上报 */
        TAF_MMA_DelayReportPsCmdInClMode();
    }
    else
    {
        /* do nothing */
    }
}


VOS_VOID TAF_MMA_UpdateServiceDomainInClMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8        enSysMode
)
{
    /* 单1X的情况下，更新成CS_PS */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if((TAF_SDC_SYS_MODE_EVDO == enSysMode)
         || (TAF_SDC_SYS_MODE_LTE == enSysMode))
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
    }
}


VOS_VOID TAF_MMA_DelayReportPsCmdInClMode(VOS_VOID)
{
    /*信号质量是否上报的处理*/
    TAF_MMA_ReportHdrSigQulityInClMode();
}


VOS_VOID TAF_MMA_ReportHdrSigQulityInClMode(VOS_VOID)
{
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU   *pstSdcHrpdSigQualityInfo    = VOS_NULL_PTR;

    pstSdcHrpdSigQualityInfo    = TAF_SDC_GetHrpdSigQualityInfo();

    if (TAF_MMA_HDR_CSQ_MODE_ENABLE == pstSdcHrpdSigQualityInfo->enMode)
    {
        if(VOS_TRUE == pstSdcHrpdSigQualityInfo->ucIsDelayReportEnable)
        {
            /*延迟上报信号强度标志位为VOS_TRUE，清标志位，并上报一次信号强度*/
            pstSdcHrpdSigQualityInfo->ucIsDelayReportEnable = VOS_FALSE;

            TAF_MMA_SndHdrCsqInd(pstSdcHrpdSigQualityInfo->sHdrRssi,
                pstSdcHrpdSigQualityInfo->sHdrSnr,
                pstSdcHrpdSigQualityInfo->sHdrEcio);
        }
    }
}


VOS_VOID TAF_MMA_UpdateAppServiceDomainInClMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8        enSysMode
)
{
    /* 单1X的情况下，更新成CS_PS */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if((TAF_SDC_SYS_MODE_EVDO == enSysMode)
         || (TAF_SDC_SYS_MODE_LTE == enSysMode))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
    }
}


VOS_VOID TAF_MMA_Report1xLocinfoInClMode(VOS_VOID)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo     = VOS_NULL_PTR;
    TAF_SDC_1X_SYS_INFO_STRU           *pstAppSdc1xSysInfo  = VOS_NULL_PTR;
    TAF_MMA_CLOCINFO_PARA_STRU          stClocinfoPara;
    VOS_UINT32                          ulClocinfoNeedRpt;
    VOS_UINT32                          ulMccTmp;
    VOS_UINT16                          usMncTmp;

    pstSdc1xSysInfo    = TAF_SDC_Get1xSysInfo();
    pstAppSdc1xSysInfo = TAF_SDC_GetApp1xSysInfo();
    ulClocinfoNeedRpt  = TAF_MMA_IsClocinfoChangeNeedRpt();

    /* 不允许CLOCINFO上报，返回 */
    if (VOS_FALSE == ulClocinfoNeedRpt)
    {
        return;
    }

    if ((pstSdc1xSysInfo->lSid                       != pstAppSdc1xSysInfo->lSid)
     || (pstSdc1xSysInfo->lNid                       != pstAppSdc1xSysInfo->lNid)
     || (pstSdc1xSysInfo->enBaseStationInfoIncl      != pstAppSdc1xSysInfo->enBaseStationInfoIncl)
     || ((PS_TRUE == pstSdc1xSysInfo->enBaseStationInfoIncl)
      && (pstSdc1xSysInfo->stBaseStationInfo.usBaseId != pstAppSdc1xSysInfo->stBaseStationInfo.usBaseId)))
    {
        PS_MEM_SET(&stClocinfoPara, 0, sizeof(TAF_MMA_CLOCINFO_PARA_STRU));
        stClocinfoPara.lSid                 = pstSdc1xSysInfo->lSid;
        stClocinfoPara.lNid                 = pstSdc1xSysInfo->lNid;
        stClocinfoPara.usPrevInUse          = pstSdc1xSysInfo->ucPrevInUse;

        if (PS_TRUE == pstSdc1xSysInfo->enServiceInfoIncl)
        {
            ulMccTmp = pstSdc1xSysInfo->stServiceInfo.ulMcc;
            usMncTmp = pstSdc1xSysInfo->stServiceInfo.usImsi11_12;
        }
        else
        {
            ulMccTmp = MMA_INVALID_MCC;
            usMncTmp = (VOS_UINT16)MMA_INVALID_MNC;
        }

        stClocinfoPara.ulMcc            = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(ulMccTmp);
        stClocinfoPara.ulMnc            = (VOS_UINT32)TAF_STD_TransformBcdMncToDeciDigit(usMncTmp);

        if (PS_TRUE == pstSdc1xSysInfo->enBaseStationInfoIncl)
        {
            stClocinfoPara.ulBaseId         = pstSdc1xSysInfo->stBaseStationInfo.usBaseId;
            stClocinfoPara.lBaseLatitude    = pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude;
            stClocinfoPara.lBaseLongitude   = pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude;
        }
        else
        {
            stClocinfoPara.ulBaseId         = TAF_MMA_INVALID_BASE_ID;
            stClocinfoPara.lBaseLatitude    = TAF_MMA_INVALID_BASE_LATITUDE;
            stClocinfoPara.lBaseLongitude   = TAF_MMA_INVALID_BASE_LONGITUDE;
        }

        TAF_MMA_ReportClocinfo(&stClocinfoPara);
    }
}


TAF_ERROR_CODE_ENUM_UINT32 TAF_MMA_ConvertCsimCardStatusToTafErrorCode(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus
)
{
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;

    switch (enCsimStatus)
    {
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_ROMSIM:
            enErrorCode = TAF_ERR_NO_ERROR;
            break;

        case TAF_SDC_USIM_STATUS_NO_PRESENT:
            enErrorCode = TAF_ERR_USIM_SIM_CARD_NOTEXIST;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PIN:
            enErrorCode = TAF_ERR_NEED_PIN1;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PUK:
            enErrorCode = TAF_ERR_NEED_PUK1;
            break;

        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:
            enErrorCode = TAF_ERR_SIM_LOCK;
            break;

        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            enErrorCode = TAF_ERR_SIM_FAIL;
            break;

        case TAF_SDC_USIM_STATUS_UNVALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        default:
            enErrorCode = TAF_ERR_USIM_SIM_INVALIDATION;
            break;
    }

    return enErrorCode;
}
#endif



VOS_VOID TAF_MMA_UpdateReportService(VOS_VOID)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* 更新总的服务状态 */
    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
     || (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == enCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == enCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);

        /* LTE注册使用 */
        if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg)
        {
            TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP);
        }
    }

    return;
}



VOS_UINT32 TAF_MMA_IsUserOperate(VOS_VOID)
{
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;

    enFsmId = TAF_MMA_GetCurrFsmId();

    if ((TAF_MMA_FSM_SYS_CFG == enFsmId)
     || (TAF_MMA_FSM_PHONE_MODE == enFsmId)
     || (STA_FSM_ENABLE != g_StatusContext.ulFsmState))
    {
        /* 用户主动操作 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_MMA_ProcMsccSystemAcquireEndInd3GppType(
    MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU    *pstSysAcqEndInd
)
{
    TAF_MMA_PLMN_SELECTION_INFO_STRU                        stTafPlmnSelectInfo;

    PS_MEM_SET(&stTafPlmnSelectInfo, 0, sizeof(TAF_MMA_PLMN_SELECTION_INFO_STRU));

    /* RoamingBroker功能使能则向SIM卡发送Location事件 */
    if (VOS_TRUE == MN_MMA_GetRoamingBrokerFlg())
    {
        if (( MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE == pstSysAcqEndInd->enResult)
         || ( MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE      == pstSysAcqEndInd->enResult))
        {
            NAS_MMA_ReportLociStatus();
        }
    }
    /* 开机搜网，一个网络都没有搜索到后，UE处于无服务，而由于开机初始化时
       服务状态也是无服务，因此通过服务状态改变无法报location status事件，
       需要在此处报一次,有AT&T认证用例验证此场景 */
    else
    {
        if ((VOS_FALSE == g_StatusContext.ucIsReportedLocStatus)
         && ( MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE == pstSysAcqEndInd->enResult))
        {
            NAS_MMA_ReportLociStatus();
        }
    }

    stTafPlmnSelectInfo.ulPlmnSelectRlst = TAF_MMA_ConvertServiceTypeToAtType(pstSysAcqEndInd->enResult);

    if (TAF_PH_PLMN_SELECTION_RESULT_INTERRUPT == stTafPlmnSelectInfo.ulPlmnSelectRlst)
    {
        stTafPlmnSelectInfo.ulPlmnSelectFlag = TAF_PH_PLMN_SELECTION_INTERRUPT;
    }
    else
    {
        stTafPlmnSelectInfo.ulPlmnSelectFlag = TAF_PH_PLMN_SELECTION_END;
    }

    if (VOS_TRUE == TAF_MMA_IsPlmnSelectInfoNeedRpt())
    {
        TAF_MMA_SndPlmnSelectionInd(&stTafPlmnSelectInfo);
    }

    return;
}


VOS_VOID TAF_MMA_UpdateRatPrioFromClToGul(
    TAF_MMA_RAT_ORDER_STRU             *pstSndRatPrioList
)
{
    VOS_UINT8                           ucIsClMode;
    VOS_UINT32                          ulIndex;
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx;

    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();
    /* get geo NV关闭,不需要更新 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    /* 初始化为VOS_FALSE,表示不支持；如果等于VOS_TRUE，表示支持 */
    ucIsClMode   = VOS_FALSE;

    /* 先判断当前接入技术是否是1x+HRPD+LTE */
    for (ulIndex = 0; ulIndex < pstSndRatPrioList->ucRatOrderNum; ulIndex++)
    {
        if ((TAF_MMA_RAT_1X == pstSndRatPrioList->aenRatOrder[ulIndex])
         || (TAF_MMA_RAT_HRPD == pstSndRatPrioList->aenRatOrder[ulIndex]))
        {
            ucIsClMode = VOS_TRUE;
            break;
        }
    }

    /* 如是CL模式，则修改为GUL模式 */
    if (VOS_TRUE == ucIsClMode)
    {
        pstSndRatPrioList->aenRatOrder[0] = TAF_MMA_RAT_GSM;
        pstSndRatPrioList->aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
        pstSndRatPrioList->aenRatOrder[2] = TAF_MMA_RAT_LTE;

        pstSndRatPrioList->ucRatOrderNum = 3;
    }
}


VOS_UINT32 TAF_MMA_IsNeedProcessSystemAcquireResult(
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult
)
{
    switch (enResult)
    {
        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE:
        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE:
        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_RF:

            return VOS_TRUE;

        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT:

            return VOS_FALSE;

        default :

            return VOS_FALSE;
    }
}


TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 TAF_MMA_GetRatModeType(
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8     enLastRatType,
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8     enCurrRatType
)
{
    return (g_aenRatModeTypeTab[enLastRatType][enCurrRatType]);
}


TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 TAF_MMA_GetRatModeChangeType(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
)
{
    VOS_UINT16                              i;
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8         enLastRatFlag;
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8         enCurrRatFlag;

    enLastRatFlag = TAF_MMA_RAT_SET_L_ONLY;
    enCurrRatFlag = TAF_MMA_RAT_SET_L_ONLY;

    /* 在用户当前设置的syscfg参数中是否有1x或者HRPD */
    for (i = 0; i < pstCurrRat->ucRatOrderNum; i++)
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* 如果1X或HRPD存在，属于CL类型 */
        if ((TAF_MMA_RAT_1X   == pstCurrRat->aenRatOrder[i])
         || (TAF_MMA_RAT_HRPD == pstCurrRat->aenRatOrder[i]))
        {
            enCurrRatFlag = TAF_MMA_RAT_SET_CL;
            break;
        }
#endif

        /* 如果GSM或UTRAN存在，属于GUL类型 */
        if ((TAF_MMA_RAT_GSM   == pstCurrRat->aenRatOrder[i])
         || (TAF_MMA_RAT_WCDMA == pstCurrRat->aenRatOrder[i]))
        {
            enCurrRatFlag = TAF_MMA_RAT_SET_GUL;
            break;
        }
    }

    /* 在用户上次设置的syscfg参数中是否有1x或者HRPD */
    for (i = 0; i < pstLastRat->ucRatOrderNum; i++)
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_MMA_RAT_1X   == pstLastRat->aenRatOrder[i])
         || (TAF_MMA_RAT_HRPD == pstLastRat->aenRatOrder[i]))
        {
            enLastRatFlag = TAF_MMA_RAT_SET_CL;
            break;
        }
#endif

        if ((TAF_MMA_RAT_GSM   == pstLastRat->aenRatOrder[i])
         || (TAF_MMA_RAT_WCDMA == pstLastRat->aenRatOrder[i]))
        {
            enLastRatFlag = TAF_MMA_RAT_SET_GUL;
            break;
        }
    }

    /* 根据上次的RAT设置以及当前的RAT设置，获取RAT变化的类型 */
    return (TAF_MMA_GetRatModeType(enLastRatFlag, enCurrRatFlag));
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



