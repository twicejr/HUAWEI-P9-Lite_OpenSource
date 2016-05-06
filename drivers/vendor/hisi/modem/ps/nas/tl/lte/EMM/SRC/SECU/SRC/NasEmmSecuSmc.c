


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmTauSerInclude.h"
#include    "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUSMC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUSMC_C
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
VOS_UINT8                           g_aucEia0Kasme[NAS_LMM_SECU_AUTH_KEY_ASME_LEN] = {
        0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
        0x19,0x84,0x05,0x14,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
        0x66,0x66,0x66,0x66,};

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_EMM_DeriveNewNasKey
 Description     : 计算新的NasCK,NasIK
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-8  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_DeriveNewNasKey(      VOS_UINT8  *pucKasme,
                                        VOS_UINT8   ucEca,
                                        VOS_UINT8   ucEia)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveNewNasKey entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveNewNasKey_ENUM,LNAS_ENTRY);

    /*计算NasCk*/
    ulRslt = NAS_EMM_ComputeNasKey(     pucKasme,
                                        NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY,
                                        ucEca);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveNewNasKey:Compute NasCK Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveNewNasKey_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /*计算NasIk*/
    ulRslt = NAS_EMM_ComputeNasKey(     pucKasme,
                                        NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY,
                                        ucEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveNewNasKey:Compute NasIK Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveNewNasKey_ENUM,LNAS_FUNCTION_LABEL2);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ComputeNasKey
 Description     : 计算NAS密钥
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-8  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_ComputeNasKey(  VOS_UINT8  *pucKasme,
                                    VOS_UINT8  *pNasK,
                                    NAS_EMM_SECU_NAS_KEY_TYPE_ENUM_UINT8 enNasKeyType,
                                    VOS_UINT8   enProtAlgoType)
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ComputeNasKey entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ComputeNasKey_ENUM,LNAS_ENTRY);


    if(VOS_NULL_PTR == pucKasme)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_ComputeNasKey:-> pucKasme is null.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ComputeNasKey_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_SECU_FAIL;
    }

    /* 编码KDF算法需要的参数 */

    /*encode FC*/
    aucAlgParam[ulIndex++]          = NAS_EMM_SECU_ALG_PARAM_NAS_KEY_FC;

    if (NAS_EMM_SECU_CIPHER_KEY == enNasKeyType)
    {
        /* encode distinguisher */
        aucAlgParam[ulIndex++]      = NAS_EMM_SECU_ALG_PARAM_CK_DISTINGUISHER;

        aucAlgParam[ulIndex++]      = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]      = NAS_EMM_SECU_ALG_PARAM_DISTINGUISHER_LEN;

        /* encode algorithm identity */
        aucAlgParam[ulIndex++] = enProtAlgoType;

        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_IDENTITY_LEN;
    }
    else
    {
        /* encode distinguisher */
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_IK_DISTINGUISHER;

        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_DISTINGUISHER_LEN;

        /* encode algorithm identity */
        aucAlgParam[ulIndex++] = enProtAlgoType;

        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_IDENTITY_LEN;
    }

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,pucKasme,aucKeyParam);

    if (NAS_EMM_SECU_SUCC == ulRslt)
    {
        PS_GetLeastSignBitsByTrunc(aucKeyParam,pNasK);
        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_ComputeNasKey->PS_KDF_HmacSha256 run Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ComputeNasKey_ENUM,LNAS_FAIL);
        return NAS_EMM_SECU_FAIL;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateCurSecuCntxt
 Description     : 更新当前安全上下文的KSIasme,KEYasme
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact
    2.sunjitan 00193151         2014-9-6  Mod: DTS2014090904779规避GU重选到L后SMC CMP发送不成功导致的后续异常
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_UpdateCurSecuCntxt(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_UpdateCurSecuCntxt enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateCurSecuCntxt_ENUM,LNAS_ENTRY);

    /*将 new mapped secu cntxt更新为当前安全上下文*/
    if(NAS_EMM_SMC_UPDATE_NEW_MAPPED == NAS_EMM_GetSmcType())
    {
        NAS_EMM_SetSecuCurKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIsgsn(NAS_EMM_GetSecuNewMappedKSIsgsn());
        NAS_LMM_MEM_CPY_S(              NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        NAS_EMM_GetSecuNewMappedKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

        /* s00193151 delete DTS2014090904779 2014-09-06:
           GU重选到L后TAU流程SMC CMP发送不成功，后续重发TAU网侧直接激活时仍可能使用NEW MAPPED，
           保留KSIsgsn就可以了，NEW MAPPED会在计算新Kasme时自动覆盖 */

        /* 清空 new mapped security context */
        /* NAS_EMM_ClearNewMappedSecuCntxt(); */
    }
    /*将 new native secu cntxt更新为当前安全上下文*/
    else if(NAS_EMM_SMC_UPDATE_NEW_NATIVE == NAS_EMM_GetSmcType())
    {
        NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIasme(NAS_EMM_GetSecuNewNativeKSIasme());
        NAS_LMM_MEM_CPY_S(              NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        NAS_EMM_GetSecuNewNativeKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
        /*清空 new native security context*/
        NAS_EMM_ClearNewNativeSecuCntxt();

        /*清空 new mapped security context*/
        NAS_EMM_ClearNewMappedSecuCntxt();

    }
    /*将 non-current native secu cntxt更新为当前安全上下文*/
    else
    {
        NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIasme(NAS_EMM_GetSecuNonCurNativeKSIasme());
        NAS_LMM_MEM_CPY_S(              NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        NAS_EMM_GetSecuNonCurNativeKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
        /*清空 non-current native security context*/
        NAS_EMM_ClearNonCurNativeSecuCntxt();
    }


    NAS_EMM_SECU_LOG2_INFO("NAS_EMM_UpdateCurSecuCntxt: CurKSIasme = , CurKSIsgsn = .",
                        NAS_EMM_GetSecuCurKSIasme(),
                        NAS_EMM_GetSecuCurKSIsgsn());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_UpdateCurSecuCntxt_ENUM,LNAS_FUNCTION_LABEL1,
                        NAS_EMM_GetSecuCurKSIasme(),
                        NAS_EMM_GetSecuCurKSIsgsn());


   return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SmcVerifyKsi
 Description     : 启用EIA0时检查SMC消息携带的KSI
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-10-18  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_Eia0SmcVerifyKsi
(
    VOS_UINT8                           ucKsi
)
{
    VOS_UINT8                           ucKsiValue = NAS_EMM_NULL;
    VOS_UINT8                           ucKsiType  = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_Eia0SmcVerifyKsi enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_ENTRY);

    /* 获取 KSI类型和 KSI 的值*/
    ucKsiValue  = ucKsi & NAS_EMM_LOW_3_BITS_F;
    ucKsiType   = ucKsi>>NAS_EMM_SECU_KSI_TYPE_BIT_POS;
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SmcVerifyKsi:KSI is NO_KEY.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /* 为了兼容不同网络，实行宽进严出原则，暂不判断KSI是否为0 */
    if(0 != ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SmcVerifyKsi:KSI is not zero.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* 为了兼容不同网络，实行宽进严出原则，暂不判断是否为NATIVE */
    if (NAS_EMM_SECU_KSI_TYPE_NATIVE != ucKsiType)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SmcVerifyKsi:KSI type is not native.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL3);
    }

    NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_CUR);

    return  NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_NotEia0SmcVerifyKsi
 Description     : 非启用EIA0时检查SMC消息携带的KSI
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-5  Draft Enact
    2.zhengjunyan 00148421      2011-4-26 MOD:INTER RAT
*****************************************************************************/
VOS_UINT32 NAS_EMM_NotEia0SmcVerifyKsi
(
    VOS_UINT8                           ucSqn,
    VOS_UINT8                           ucKsi
)
{
    VOS_UINT8                               ucKsiType;
    VOS_UINT8                               ucKsiValue;
    VOS_UINT32                              ulRslt;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_NotEia0SmcVerifyKsi enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_ENTRY);

    /* 获取 KSI类型和 KSI 的值*/
    ucKsiType   = ucKsi>>NAS_EMM_SECU_KSI_TYPE_BIT_POS;
    ucKsiValue  = ucKsi&NAS_EMM_LOW_3_BITS_F;
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SmcVerifyKsi:KSI is NO_KEY.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /* 如果SMC携带的KSI为 native 类型*/
    if(NAS_EMM_SECU_KSI_TYPE_NATIVE == ucKsiType)
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_NotEia0SmcVerifyKsi:KSI is Native.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL2);
        ulRslt = NAS_EMM_SmcVerifyNativeKsi(ucKsiValue);
    }
    else/* 如果SMC携带的KSI为 Mapped 类型*/
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_NotEia0SmcVerifyKsi:KSI is Mapped.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL3);
        ulRslt = NAS_EMM_SmcVerifyMappedKsi(ucSqn, ucKsiValue);
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SmcVerifyNativeKsi
 Description     : 验证EPS native KSI
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact
    2.zhengjunyan 00148421      2011-9-22  MOD:为了适应GCF仪器下发AUTH REQ消息
                                    的KSIasme与UE当前安全上下文KSIasme相同的问题
                                    调整匹配的顺序
*****************************************************************************/
VOS_UINT32  NAS_EMM_SmcVerifyNativeKsi( VOS_UINT8 ucKsiValue)
{
    NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SmcVerifyNativeKsi: ucKsiValue = ", ucKsiValue);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SmcVerifyNativeKsi_ENUM,LNAS_FUNCTION_LABEL1,ucKsiValue);
    if(NAS_EMM_GetSecuNewNativeKSIasme() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NEW_NATIVE);
    }
    else if (NAS_EMM_GetSecuCurKSIasme() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_CUR);
    }
    else if(NAS_EMM_GetSecuNonCurNativeKSIasme() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE);
    }
    else
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyNativeKsi: NAS_EMM_SECU_FAIL");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyNativeKsi_ENUM,LNAS_FUNCTION_LABEL2);
        return  NAS_EMM_SECU_FAIL;
    }

    return  NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SmcVerifyMappedKsi
 Description     : 验证EPS mapped KSI
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SmcVerifyMappedKsi
(
    VOS_UINT8                           ucSqn,
    VOS_UINT8                           ucKsiValue
)
{
    /* 如果SQN刚好为0，GU重选到L时发起TAU消息中current安全上下文的KSI和mapped cksn相等，
       并且SMC消息中的KSI等于此二者，则优先使用new mapped，如此处理是为了规避
       网侧下发SMC消息时UE无法区分使用哪套，满足上述条件时优先使用new mapped */
    if(    (0 == ucSqn)
        && (NAS_EMM_GetSecuNewMappedKSIsgsn() == NAS_EMM_GetSecuCurKSIsgsn())
        && (NAS_EMM_GetSecuNewMappedKSIsgsn() == ucKsiValue)   )
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyMappedKsi: Update New mapped security context.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyMappedKsi_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NEW_MAPPED);
        return NAS_EMM_SECU_SUCC;
    }

    /* 非上述特殊情况的正常处理 */
    if (NAS_EMM_GetSecuCurKSIsgsn() == ucKsiValue)
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyMappedKsi: Update current mapped security context.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyMappedKsi_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_CUR);
    }
    else if(NAS_EMM_GetSecuNewMappedKSIsgsn() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NEW_MAPPED);
    }
    else
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyMappedKsi:NAS_EMM_SECU_FAIL.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyMappedKsi_ENUM,LNAS_FUNCTION_LABEL3);
        return  NAS_EMM_SECU_FAIL;
    }

    return  NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SmcVerifyAlg
 Description     : 启用EIA0时验证SMC消息携带的保护算法，加解密算法是否符合UeNetCap
                   加密算法是否为EEA0
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-10-18  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_Eia0SmcVerifyAlg( VOS_UINT8 ucSelEca, VOS_UINT8 ucSelEia)
{
    if (NAS_EMM_SECU_ALG_EEA0 != ucSelEca)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_EIA0,
                                       ucSelEca);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyAlg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    return NAS_EMM_IsAlgUeSupported(ucSelEca, ucSelEia);
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsAlgUeSupported
 Description     : 验证SMC消息携带的保护算法，加解密算法是否符合UeNetCap
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-8  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsAlgUeSupported( VOS_UINT8 ucSelEca, VOS_UINT8 ucSelEia)
{
    NAS_MM_UE_NET_CAP_STRU             *pstUeNetCap = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucEEA;
    VOS_UINT8                           ucEIA;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_IsAlgUeSupported entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAlgUeSupported_ENUM,LNAS_ENTRY);

    /*获取UE_NET_CAP*/
    pstUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();

    /*检查完整性保护或者加密算法，UE不支持*/
    ucEEA = pstUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EEA_POS];
    ucEIA = pstUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EIA_POS];

    /*lint -e701*/
    if((NAS_EMM_BIT_NO_SLCT == ((ucEIA << ucSelEia)& NAS_EMM_SECU_HIGHEST_BIT))
      ||(NAS_EMM_BIT_NO_SLCT == ((ucEEA << ucSelEca)& NAS_EMM_SECU_HIGHEST_BIT)))

    {
        return NAS_EMM_SECU_FAIL;
    }
    /*lint +e701*/

    return NAS_EMM_SECU_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetIntegrityAlg
 Description     : 将网侧携带的完整性保护算法进行转换，传给底软
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181       2013-06-05  Draft Enact

*****************************************************************************/
CIPHER_ALGORITHM_E NAS_EMM_GetIntegrityAlg( VOS_UINT8 ucSelEia)
{

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetIntegrityAlg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetIntegrityAlg_ENUM,LNAS_ENTRY);

    switch(ucSelEia)
    {
        case    NAS_EMM_SECU_ALG_EIA0:
            return CIPHER_ALG_NULL;

        case    NAS_EMM_SECU_ALG_EIA1:
            return CIPHER_ALG_SNOW3G;

        case    NAS_EMM_SECU_ALG_EIA2:
            return CIPHER_ALG_AES_128;

        case    NAS_EMM_SECU_ALG_EIA3:
            return CIPHER_ALG_ZUC;

        default:
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetIntegrityAlg entered: ucSelEia err");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_GetIntegrityAlg_ENUM,LNAS_ERROR);
            return CIPHER_ALG_BUTTOM;

    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetSecurityAlg
 Description     : 将网侧携带的加密算法进行转换，传给底软
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181       2013-06-05  Draft Enact

*****************************************************************************/
CIPHER_ALGORITHM_E NAS_EMM_GetSecurityAlg( VOS_UINT8 ucSelEca)
{

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetSecurityAlg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetSecurityAlg_ENUM,LNAS_ENTRY);

    switch(ucSelEca)
    {
        case    NAS_EMM_SECU_ALG_EEA0:

            return CIPHER_ALG_NULL;

        case    NAS_EMM_SECU_ALG_EEA1:
            return CIPHER_ALG_SNOW3G;

        case    NAS_EMM_SECU_ALG_EEA2:
            return CIPHER_ALG_AES_128;

        case    NAS_EMM_SECU_ALG_EEA3:
            return CIPHER_ALG_ZUC;

        default:
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetSecurityAlg entered: ucSelEca err");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_GetSecurityAlg_ENUM,LNAS_ERROR);
            return CIPHER_ALG_BUTTOM;

    }
}


/*****************************************************************************
 Function Name   : NAS_EMM_SmcVerifyUeSecuCap
 Description     : 检查SMC消息中携带的 replayed UE_SECURITY_CAP是否与本地匹配
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-8  Draft Enact
    2.zhengjunyan 00148421      2011-4-26 MOD:INTER RAT
    3.sunbing 49683             2012-04-25 DTS2012042501002
*****************************************************************************/
VOS_UINT32  NAS_EMM_SmcVerifyUeSecuCap(
                        const NAS_LMM_UE_SECURITY_CAP_STRU    *pstUeSecuCap )
{
    NAS_MM_UE_NET_CAP_STRU             *pstLocalUeNetCap = VOS_NULL_PTR;
    NAS_MM_MS_NET_CAP_STRU             *pstLocalMsNetCap = VOS_NULL_PTR;
    NAS_LMM_UE_SECURITY_CAP_STRU        stLocalUeSecuCap = {0};

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyUeSecuCap entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_ENTRY);

    if(NAS_EMM_SMC_CLOSE== g_ulUeSecuCapMatch)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyUeSecuCap: g_ulUeSecuCapMatch = NAS_EMM_SMC_CLOSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_SUCC;
    }

    /* 获取 UE 本地的 UE_NET_CAP和 MS_NET_CAP*/
    pstLocalUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();
    pstLocalMsNetCap = NAS_LMM_GetEmmInfoMsNetCapAddr();


    /* 如果是多模模式*/
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        /*stLocalUeSecuCap.ucUeSeuCapLen = pstLocalUeNetCap->ucUeNetCapLen + 1;*/
        stLocalUeSecuCap.ucEEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EEA_POS];
        stLocalUeSecuCap.ucEIA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EIA_POS];
        stLocalUeSecuCap.ucUEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UEA_POS];
        stLocalUeSecuCap.ucUIA = (pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UIA_POS])&NAS_EMM_7_BITS_F;
        stLocalUeSecuCap.ucGEA = ((pstLocalMsNetCap->aucMsNetCap[0]&NAS_EMM_HIGHES_BIT)
                                  >>NAS_LMM_MOVEMENT_1_BITS);
        stLocalUeSecuCap.ucGEA |= ((pstLocalMsNetCap->aucMsNetCap[1]&NAS_EMM_6_BITS_F)
                                  >>NAS_LMM_MOVEMENT_1_BITS);

        /* 比较SMC携带携带的UE_SECURITY_CAP和UE本地的UE_SECURITY_CAP，只比较内容,不再比较长度*/    /*lint -e420 -e831*/
        /*lint -e420 -e831*/
        if(NAS_EMM_SECU_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(  (VOS_VOID*)&(stLocalUeSecuCap.ucEEA),
                                                            (VOS_VOID*)&(pstUeSecuCap->ucEEA),
                                                            NAS_EMM_SMC_MAX_UE_SECU_CAP_LEN ))
        /*lint +e420 +e831*/
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SmcVerifyUeSecuCap: UE_SECU_CAP_NOT_MATCH.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SECU_FAIL;
        }
    }
    /* L模单模模式:只验证EEA,EIA是否与UE本地匹配，不关心UEA,UIA*/
    else
    {
        stLocalUeSecuCap.ucUeSeuCapLen = pstLocalUeNetCap->ucUeNetCapLen;
        stLocalUeSecuCap.ucEEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EEA_POS];
        stLocalUeSecuCap.ucEIA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EIA_POS];
        stLocalUeSecuCap.ucUEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UEA_POS];
        stLocalUeSecuCap.ucUIA = (pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UIA_POS])&NAS_EMM_7_BITS_F;

        /* 比较SMC携带的EEA,EIA和UE本地的EEA,EIA*/
        if((pstUeSecuCap->ucEEA != stLocalUeSecuCap.ucEEA)
         ||(pstUeSecuCap->ucEIA != stLocalUeSecuCap.ucEIA))
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SmcVerifyUeSecuCap: EEA or EIA NOT MATCH.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_FUNCTION_LABEL3);
            return NAS_EMM_SECU_FAIL;
        }

    }

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SmcVerifyNonceUE
 Description     : 检查SMC消息携带的 replayed NonceUE是否与UE本地的相同
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SmcVerifyNonceUE(
                                        const NAS_EMM_SECU_SMC_STRU *pstSmcStru )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyNonceUE entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyNonceUE_ENUM,LNAS_ENTRY);

    /* 确认regplayed NonceUE和 NonceMME信元必须存在*/
    if((NAS_EMM_BIT_NO_SLCT == pstSmcStru->bitNonceUe)
     ||(NAS_EMM_BIT_NO_SLCT == pstSmcStru->bitNonceMme))
    {
        return NAS_EMM_SECU_FAIL;
    }

    /* 与UE本地的 NonceUE比较，返回结果*/
    if(NAS_EMM_SECU_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(pstSmcStru->aucNonceUe,
                                                    NAS_EMM_GetSecuNonceUEAddr(),
                                                    NAS_EMM_SECU_NONCE_UE_LEN))
    {
        return NAS_EMM_SECU_FAIL;
    }

    return NAS_EMM_SECU_SUCC;

}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeSmcMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           :
 Output          :
 Return          :
 History         :
    1.zhengjunyan 00148421      2011-5-03  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeSmcMsg(
                                        LRRC_LNAS_MSG_STRU      *pstCnSmcMsg,
                                        NAS_EMM_SECU_SMC_STRU   *pstSecurModeCtrl)/*lint -e662 -e661 -e831 -e416 -e415*/

{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT8                          *pucSmcMsg           = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgSize       = 0;
    VOS_UINT8                           ucReplayeUeSecuCapLen = 0;

    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_ENTRY);

    /* 判断空口消息SMC码流长度是否正确*/
    /* 只检查大于最短长度，
       超出消息最大长度的情况，在保证信元解码正确的情况下，对于多余的错误字节不予考虑*/
    ulMsgSize  = pstCnSmcMsg->ulNasMsgSize;
    if(NAS_EMM_SMC_MIN_LEN > ulMsgSize)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                       1);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*获取SMC消息码流*/
    pucSmcMsg = pstCnSmcMsg->aucNasMsg;

    /* 获取必选IE*/
    ulIndex = NAS_EMM_SECU_PLAIN_MSG_POS;

    /*Protolcal Disciriminator and security header type*/
    pstSecurModeCtrl->ucPdSt = pucSmcMsg[ulIndex];
    ulIndex++;

    /*Message Type*/
    pstSecurModeCtrl->ucMt = pucSmcMsg[ulIndex];
    ulIndex++;

    /*selected NAS security algorithm*/
    pstSecurModeCtrl->ucSelAlgrthm = pucSmcMsg[ulIndex];
    ulIndex++;

    /*Key Set Identifier*/
    pstSecurModeCtrl->ucKSI = pucSmcMsg[ulIndex]& NAS_EMM_LOW_HALF_BYTE_F;
    ulIndex++;

    /*replayed UE security capability*/
    ucReplayeUeSecuCapLen = pucSmcMsg[ulIndex];
    ulIndex++;

    /*replayed UE secutity capability len:[2,5]*/
    if((NAS_EMM_SMC_MIN_UE_SECU_CAP_LEN > ucReplayeUeSecuCapLen)
     ||(NAS_EMM_SMC_MAX_UE_SECU_CAP_LEN < ucReplayeUeSecuCapLen))
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                       2);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*检查剩余码流的长度是否满足要求*/
    if((ulIndex + ucReplayeUeSecuCapLen) > ulMsgSize)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                       3);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SECU_FAIL;
    }

    pstSecurModeCtrl->stUeSecuCap.ucUeSeuCapLen = ucReplayeUeSecuCapLen;
    NAS_LMM_MEM_CPY_S(              &(pstSecurModeCtrl->stUeSecuCap.ucEEA),
                                    ucReplayeUeSecuCapLen,
                                    &(pucSmcMsg[ulIndex]),
                                    ucReplayeUeSecuCapLen);
    ulIndex += ucReplayeUeSecuCapLen;

    /* 清除spare位为0 */
    pstSecurModeCtrl->stUeSecuCap.ucUIA &= NAS_EMM_7_BITS_F;
    pstSecurModeCtrl->stUeSecuCap.ucGEA &= NAS_EMM_7_BITS_F;
    /*必选信元解码完成后，剩余码流的长度*/
    ulTempMsgSize =  ulMsgSize -  ulIndex;
    if(0 == ulTempMsgSize)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: decode complete.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_SECU_SUCC;
    }

    /*获取可选信元*/
    /*IMEISV request*/
    if(NAS_EMM_SMC_IMEISV_REQ_IEI == (pucSmcMsg[ulIndex]&NAS_EMM_HIGH_HALF_BYTE_F))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: IMEISV request IE.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL5);
        pstSecurModeCtrl->bitImeisvReq = NAS_EMM_BIT_SLCT;
        pstSecurModeCtrl->ucImeisvRsq = pucSmcMsg[ulIndex];
        ulIndex++;
        ulTempMsgSize = ulMsgSize -  ulIndex;
    }

    /*判断如果剩余码流为0，则解码结束*/
    if(0 == ulTempMsgSize)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: decode complete.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL6);
        return NAS_EMM_SECU_SUCC;
    }

    /*replayed NonceUE*/
    if(NAS_EMM_SMC_NONCE_UE_IEI == pucSmcMsg[ulIndex])
    {
        ulIndex++;
        if((ulIndex + NAS_EMM_SECU_NONCE_UE_LEN) <= ulMsgSize)
        {
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: replayed Nonce IE.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL7);
            pstSecurModeCtrl->bitNonceUe = NAS_EMM_BIT_SLCT;

            NAS_LMM_MEM_CPY_S(          pstSecurModeCtrl->aucNonceUe,
                                        NAS_EMM_SECU_NONCE_UE_LEN,
                                        (pucSmcMsg + ulIndex),
                                        NAS_EMM_SECU_NONCE_UE_LEN);

            ulIndex += NAS_EMM_SECU_NONCE_UE_LEN;
            ulTempMsgSize = ulMsgSize -  ulIndex;

             /*判断如果剩余码流为0，则解码结束*/
            if(0 == ulTempMsgSize)
            {
                NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: decode complete.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL8);
                return NAS_EMM_SECU_SUCC;
            }
        }
        else
        {
            NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                           4);
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL9);
            return NAS_EMM_SECU_FAIL;
        }
    }

    /*NonceMME*/
    if(NAS_EMM_SMC_NONCE_MME_IEI == pucSmcMsg[ulIndex])
    {
        ulIndex++;
        if((ulIndex + NAS_EMM_SECU_NONCE_MME_LEN) <= ulMsgSize)
        {
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: NonceMME IE.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL10);
            pstSecurModeCtrl->bitNonceMme = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY_S(          pstSecurModeCtrl->aucNonceMme,
                                        NAS_EMM_SECU_NONCE_MME_LEN,
                                       (pucSmcMsg + ulIndex),
                                        NAS_EMM_SECU_NONCE_MME_LEN);
        }
        else
        {
            NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                           5);
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL11);
            return NAS_EMM_SECU_FAIL;
        }
    }

    return NAS_EMM_SECU_SUCC;

}/*lint +e662 +e661 +e831 +e416 +e415*/

/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SmcVerifyParam
 Description     : 启用EIA0时SMC携带的参数检查,包括:KSI, 算法, replayed UE_NET_CAP,
                                          replayed NONCEue
 Input           : SMC消息码流
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-10-18  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_NotEia0SmcVerifyParam
(
    const NAS_EMM_SECU_SMC_STRU              *pstSmcStru,
    VOS_UINT8                           ucSqn
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia    = NAS_EMM_NULL;
    VOS_UINT8                           ucSmcEca    = NAS_EMM_NULL;

    /*lint -e415 -e416*/
    ulRslt = NAS_EMM_NotEia0SmcVerifyKsi(ucSqn, pstSmcStru->ucKSI);
    /*lint +e415 +e416*/

    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH,
                                       ucSqn);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*检查算法*/
    ucSmcEia =  pstSmcStru->ucSelAlgrthm & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca =  (pstSmcStru->ucSelAlgrthm >>4) & NAS_EMM_LOW_3_BITS_F;
    ulRslt = NAS_EMM_IsAlgUeSupported(ucSmcEca, ucSmcEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*检查SMC携带的replayed UE_SECURITY_CAP是否与UE本地维护的相同*/
    ulRslt = NAS_EMM_SmcVerifyUeSecuCap(&(pstSmcStru->stUeSecuCap));
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_SECU_CAP_MISMATCH);
        /* coverity[unchecked_value] */
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH,
                                       NAS_EMM_CheckMutiModeSupport());
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SECU_FAIL;
    }

    /*如果SMC携带的KSI为new mapped ksi，则需要验证replaye NonceUE*/
    if(NAS_EMM_SMC_UPDATE_NEW_MAPPED == NAS_EMM_GetSmcType())
    {
        ulRslt = NAS_EMM_SmcVerifyNonceUE(pstSmcStru);
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
            NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NONCE_MISMATCH,
                                           0);
            TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL4);
            return NAS_EMM_SECU_FAIL;
        }
    }

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SmcVerifyParam
 Description     : 启用EIA0时SMC携带的参数检查,包括:KSI, 算法, replayed UE_NET_CAP,
                                          replayed NONCEue
 Input           : SMC消息码流
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-10-18  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_Eia0SmcVerifyParam
(
    const NAS_EMM_SECU_SMC_STRU              *pstSmcStru
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia    = NAS_EMM_NULL;
    VOS_UINT8                           ucSmcEca    = NAS_EMM_NULL;

    /*lint -e415 -e416*/
    ulRslt = NAS_EMM_Eia0SmcVerifyKsi(pstSmcStru->ucKSI);
    /*lint +e415 +e416*/

    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH,
                                       (pstSmcStru->ucKSI) & NAS_EMM_LOW_3_BITS_F);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*检查算法*/
    ucSmcEia =  pstSmcStru->ucSelAlgrthm & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca =  (pstSmcStru->ucSelAlgrthm >>4) & NAS_EMM_LOW_3_BITS_F;
    ulRslt = NAS_EMM_Eia0SmcVerifyAlg(ucSmcEca, ucSmcEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*检查SMC携带的replayed UE_SECURITY_CAP是否与UE本地维护的相同*/
    ulRslt = NAS_EMM_SmcVerifyUeSecuCap(&(pstSmcStru->stUeSecuCap));
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_SECU_CAP_MISMATCH);
        /* coverity[unchecked_value] */
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH,
                                       NAS_EMM_CheckMutiModeSupport());
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SECU_FAIL;
    }

    /* 为了兼容不同网络，实行宽进严出原则，暂不判断是否有紧急承载或者
       正在建立紧急承载 */

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SmcVerifyParam
 Description     : SMC携带的参数检查,包括:KSI, 算法, replayed UE_NET_CAP,
                                          replayed NONCEue
 Input           : SMC消息码流
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-10  Draft Enact
    2.zhengjunyan 00148421      2011-4-26  MOD:INTER RAT
*****************************************************************************/
VOS_UINT32  NAS_EMM_SmcVerifyParam( LRRC_LNAS_MSG_STRU  *pstSmcMsg )
{
    VOS_UINT8                           ucSmcEia = 0;
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    NAS_EMM_SECU_SMC_STRU              *pstSmcStru = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyParam enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyParam_ENUM,LNAS_ENTRY);

    /*SMC消息解码*/
    pstSmcStru = (NAS_EMM_SECU_SMC_STRU *)NAS_EMM_GetSecuBufSpace();

    NAS_LMM_MEM_SET_S(pstSmcStru, sizeof(NAS_EMM_SECU_SMC_STRU), 0, sizeof(NAS_EMM_SECU_SMC_STRU));

    ulRslt = NAS_EMM_DecodeSmcMsg(pstSmcMsg, pstSmcStru);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyParam:decode ERR.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*检查KSI*/
    NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SmcVerifyParam:pstSmcStru->ucKSI = ", pstSmcStru->ucKSI );
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL2,pstSmcStru->ucKSI);

    ucSmcEia =  pstSmcStru->ucSelAlgrthm & NAS_EMM_LOW_3_BITS_F;

    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        ulRslt = NAS_EMM_Eia0SmcVerifyParam(      pstSmcStru);
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SndOmLogEpsSecContextInfo();
        }
        return ulRslt;
    }
    else
    {
        /*lint -e416 -e415*/
        ulRslt = NAS_EMM_NotEia0SmcVerifyParam(   pstSmcStru,
                                                pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
        /*lint +e416 +e415*/
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SndOmLogEpsSecContextInfo();
        }
        return ulRslt;

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetNonceMmeInSmc
 Description     : 获取SMC消息中的 NONCEmme
                   ref:24301-950 8.2.20.1
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuGetNonceMmeInSmc( VOS_VOID )
{
    NAS_EMM_SECU_SMC_STRU              *pstSmcStru = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuGetNonceMmeInSmc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetNonceMmeInSmc_ENUM,LNAS_ENTRY);

    /* 从解码后的消息结构中获取 NONCEmme*/
    pstSmcStru = (NAS_EMM_SECU_SMC_STRU *)NAS_EMM_GetSecuBufSpace();
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuNonceMMEAddr(),
                                        NAS_EMM_SECU_NONCE_MME_LEN,
                                        pstSmcStru->aucNonceMme,
                                        NAS_EMM_SECU_NONCE_MME_LEN);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SmcIntCheckPara
 Description     : 启动EIA0时计算NAS CK和NAS IK
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_Eia0SmcIntCheckPara
(
    LRRC_LNAS_MSG_STRU                 *pstSmcMsg,
    NAS_EMM_PROT_PARAM_STRU            *pstUnProtParam
)
{
    VOS_UINT8                          *pucKasme        = VOS_NULL_PTR;
    VOS_UINT8                           ucSmcEia        = NAS_EMM_NULL;
    VOS_UINT8                           ucSmcEca        = NAS_EMM_NULL;
    VOS_UINT32                          ulDlForUnprot   = NAS_EMM_NULL;
    VOS_UINT8                           ucKsiValue      = NAS_EMM_NULL;
    VOS_UINT32                          ulRslt          = NAS_EMM_SECU_FAIL;


    /* 根据SMC携带的KSI的类型，获取安全上下文*/
    /*lint -e416 -e415*/
    ucKsiValue =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_KSI_POSE] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (ucKsiValue == NAS_EMM_GetSecuCurKSIasme())
    {
        pucKasme = NAS_EMM_GetSecuCurKasmeAddr();
    }
    else
    {
        pucKasme = NAS_EMM_GetEia0Kasme();
    }

    /*获取SMC携带的算法*/
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca = (pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE]>>4) & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/

    /*计算新的 NasCK,NasIK*/
    NAS_EMM_DeriveNewNasKey(pucKasme,ucSmcEca,ucSmcEia);

    (VOS_VOID)ulRslt;

    /*SMC消息完整性检查需要使用新生成的 NasCK,NasIK，替换Register中的密钥*/
    /*NasIK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);
    /*NasCK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    /*组装SMC消息完整性检查需要的参数*/
    pstUnProtParam->ulNasCount          = ulDlForUnprot;
    pstUnProtParam->ucSecuALg           = ucSmcEia;
    pstUnProtParam->pucMsg              = pstSmcMsg->aucNasMsg;
    pstUnProtParam->pulMsgSize          = &(pstSmcMsg->ulNasMsgSize);

    return;
}


VOS_VOID  NAS_EMM_NotEia0SmcIntCheckPara(
                                        LRRC_LNAS_MSG_STRU      *pstSmcMsg,
                                        NAS_EMM_PROT_PARAM_STRU *pstUnProtParam)
{
    VOS_UINT8                          *pucKasme = VOS_NULL_PTR;
    VOS_UINT8                           ucSmcEia = 0;
    VOS_UINT8                           ucSmcEca = 0;
    VOS_UINT32                          ulDlForUnprot = 0;
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;

    /* 根据SMC携带的KSI的类型，获取安全上下文*/
    switch (NAS_EMM_GetSmcType())
    {
        case NAS_EMM_SMC_UPDATE_CUR:
            /*lint -e415 -e416*/
            ulDlForUnprot = NAS_EMM_CompDlNasCount(NAS_EMM_GetSecuDlNasCount(),
                                pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
            /*lint +e415 +e416*/
            pucKasme = NAS_EMM_GetSecuCurKasmeAddr();
            break;

        case NAS_EMM_SMC_UPDATE_NEW_MAPPED:
            /*lint -e415 -e416*/
            ulDlForUnprot = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS];
            /*lint +e415 +e416*/

            pucKasme = NAS_EMM_GetSecuNewMappedKasmeAddr();

            /*获取SMC消息携带的 NONCEmme*/
            NAS_EMM_SecuGetNonceMmeInSmc();

            /*计算 new mapped security context中的 Kasme*/
            ulRslt = NAS_EMM_DeriveKasmeFromUmtsIdle(pucKasme);
            if(NAS_EMM_SECU_FAIL == ulRslt)
            {
                NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveKasmeFromUmtsIdle ERR.");
                TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SmcIntCheckPara_ENUM,LNAS_FUNCTION_LABEL1);
            }
            break;

        case NAS_EMM_SMC_UPDATE_NEW_NATIVE:
            /* 此处取网侧下发的SMC消息中的Sqn，NasCount的高3字节固定取0，如此实现的目的是
            防止刚鉴权完成后出现失步，收不到网侧的第1条SMC消息，网侧超时后再发SMC流程可能将
            Sqn加1，而UE一直用NasCount=0则无法解保护成功；不能用判断翻转的逻辑在于，防止出
            现网侧收不到UE发送的SMC CMP消息，重发时又用Sqn=0导致UE误认为翻转后续一直无法解
            保护成功，如此实现刚好能兼容这两种情况。                                     */
            /*lint -e415 -e416*/
            ulDlForUnprot = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS];
            /*lint +e415 +e416*/
            pucKasme = NAS_EMM_GetSecuNewNativeKasmeAddr();
            break;

        case NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE:
            /*lint -e416 -e415*/
            ulDlForUnprot = NAS_EMM_CompDlNasCount(
                                NAS_EMM_GetSecuNonCurDlNasCount(),
                                pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
            /*lint +e416 +e415*/
            pucKasme = NAS_EMM_GetSecuNonCurNativeKasmeAddr();
            break;

        default:
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SmcIntCheckPara:SmcType ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SmcIntCheckPara_ENUM,LNAS_FUNCTION_LABEL2);
            return;
    }

    /*获取SMC携带的算法*/
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca = (pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE]>>4) & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/

    /*计算新的 NasCK,NasIK*/
    NAS_EMM_DeriveNewNasKey(pucKasme,ucSmcEca,ucSmcEia);

    (VOS_VOID)ulRslt;

    /*SMC消息完整性检查需要使用新生成的 NasCK,NasIK，替换Register中的密钥*/
    /*NasIK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);
    /*NasCK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    /*组装SMC消息完整性检查需要的参数*/
    pstUnProtParam->ulNasCount          = ulDlForUnprot;
    pstUnProtParam->ucSecuALg           = ucSmcEia;
    pstUnProtParam->pucMsg              = pstSmcMsg->aucNasMsg;
    pstUnProtParam->pulMsgSize          = &(pstSmcMsg->ulNasMsgSize);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SmcIntCheck
 Description     : SMC消息完整性检查：需要根据enSmcType来获取不同的参数
 Input           : None
 Output          : 若解保护成功,
                   pstSmcMsg->aucNasMsg 为去掉 头类型/MAC/SN后的纯粹的SMC消息
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SmcIntCheck( LRRC_LNAS_MSG_STRU  *pstSmcMsg )
{
    VOS_UINT32                          ulRslt          = NAS_EMM_SECU_FAIL;
    NAS_EMM_PROT_PARAM_STRU             stUnProtParam   = {0};
    VOS_UINT8                           ucSmcEia        = NAS_EMM_NULL;

    /*根据SMC携带的参数，计算新的 NasCK,NasIK,保存SMC完整性检查的参数*/
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        NAS_EMM_Eia0SmcIntCheckPara(pstSmcMsg, &stUnProtParam);
    }
    else
    {

        NAS_EMM_NotEia0SmcIntCheckPara(pstSmcMsg, &stUnProtParam);
    }

    /*完整性检查*/
    /* coverity[var_deref_model] */
    ulRslt = NAS_EMM_SecuIntCheck(&stUnProtParam);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcIntCheck: SMC Int Check Fail.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcIntCheck_ENUM,LNAS_FUNCTION_LABEL1);

        /*本次安全流程失败，新的NasCK和NasIK没有生效，还原Register中的密钥*/
        /*NasIK*/
        (VOS_VOID) NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasIkAddr(),
                                            NAS_EMM_SECU_INTEGRITY_KEY);
        /*NasCK*/
        (VOS_VOID) NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasCkAddr(),
                                            NAS_EMM_SECU_CIPHER_KEY);
        NAS_EMM_SndOmLogEpsSecContextInfo();
        /* 完整性检查失败,使用还原后的密钥对smc rej空口进行加密 */
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        return NAS_EMM_SECU_FAIL;
    }

    /*完整性检查通过，则接受本次DL_NASCOUNT*/
    /* 计算的count值大于本地count值或者计算的count值为0才更新 */
    if((stUnProtParam.ulNasCount > NAS_EMM_GetSecuDlNasCount())
        ||(stUnProtParam.ulNasCount == 0))
    {
        NAS_EMM_GetSecuDlNasCount() = stUnProtParam.ulNasCount;
    }

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendSecuParamToRrc
 Description     : 发送RRC_MM_INFO_CHANGE_REQ给RRC,携带安全参数:Kasme + UL_NasCount
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-9-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendSecuParamToRrc( VOS_VOID )
{
    LRRC_LNAS_INFO_STRU                   stNasInfo;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendSecuParamToRrc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendSecuParamToRrc_ENUM,LNAS_ENTRY);

    /*清空内存*/
    NAS_LMM_MEM_SET_S(&stNasInfo, sizeof(LRRC_LNAS_INFO_STRU), 0, sizeof(LRRC_LNAS_INFO_STRU));

    /*填充安全参数: Kasme + UL_NasCount*/
    stNasInfo.bitOpSecurityKey = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY_S(                  stNasInfo.stSecurityKey.aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    stNasInfo.stSecurityKey.ulNasCount = NAS_EMM_GetSecuUlNasCount();

    /*发送RRC_MM_INFO_CHANGE_REQ消息给RRC*/
    NAS_EMM_SendInfoChangeReqMsg(&stNasInfo);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSendSmcCmp
 Description     : 向MRRC发送NAS_EMM_MRRC_DATA_REQ(SECURITY MODE COMPLETE)消息
 Input           : enIfImeisvReq:是否需要回复IMEISV
 Output          : None
 Return          : None
 History         :
    1.liuwenyu 00143951         2008-12-20  Draft Enact
    2.zhuyiqiang 00138739       2009-08-11  MODIFY    BJ9D01672,上行编码优化

*****************************************************************************/
VOS_VOID    NAS_EMM_SecuSendSmcCmp(
                        NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  enIfImeisvReq)
{
    VOS_UINT32                           ulPos                   = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg              = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU               *pstEmmInfo             = VOS_NULL_PTR;
    VOS_UINT32                          uldataReqMsgLenNoHeader;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSendSmcCmp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSendSmcCmp_ENUM,LNAS_ENTRY);

    /*申请消息内存*/
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*构造SMC COMPLETE消息*/
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++]     = EMM_CN_MSG_PD_EMM;
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++]     = NAS_EMM_CN_MT_SMC_CMP;

    if(NAS_EMM_IMEISV_REQUEST == enIfImeisvReq)
    {
        pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_SECU_IMEISV_IEI;

        /* 获得 IMEISV*/
        pstEmmInfo = NAS_LMM_GetEmmInfoAddr();
        /*lint -e419*/
        NAS_LMM_MEM_CPY_S( (VOS_VOID *)&pIntraMsg->stNasMsg.aucNasMsg[ulPos],
                            NAS_MM_MAX_UEID_BUF_SIZE,
                            pstEmmInfo->stMmUeId.aucImeisv,
                            NAS_MM_MAX_UEID_BUF_SIZE);
        /*lint +e419*/

        ulPos += NAS_MM_MAX_UEID_BUF_SIZE;
    }

    /*填充消息ID*/
    pIntraMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pIntraMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

    /*填充内部消息类型*/
    pIntraMsg->enEmmMsgType = NAS_EMM_MSG_SMC_COMPL;

    /*填充消息长度*/
    pIntraMsg->stNasMsg.ulNasMsgSize = ulPos;

    /*计算不包含消息头的消息长度*/
    uldataReqMsgLenNoHeader =
        NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(pIntraMsg->stNasMsg.ulNasMsgSize);

    /*填充消息头*/
    NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*空口消息上报 SECU_MODE_COMPLETE*/
    NAS_LMM_SendOmtAirMsg( NAS_EMM_OMT_AIR_MSG_UP,
                          NAS_EMM_SECU_CMP,
                          (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*关键事件上报 SECU_MODE_COMPLETE*/
    NAS_LMM_SendOmtKeyEvent(EMM_OMT_KE_SECU_CMP);

    /* 向MRRC发送SMC COMPLETE消息 */
    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSendSmcRej
 Description     : 向MRRC发送NAS_EMM_MRRC_DATA_REQ(SECURITY MODE REJECT)消息
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.zhengjunyan 00148421         2010-03-22  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_CAUSE_ENUM_UINT8 enCause)
{
    VOS_UINT32                          ulPos               = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pIntraMsg           = VOS_NULL;
    VOS_UINT32                          uldataReqMsgLenNoHeader;


    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSendSmcRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSendSmcRej_ENUM,LNAS_ENTRY);

    /* 申请消息内存 */
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(
                                        NAS_EMM_INTRA_MSG_MAX_SIZE);

    /* 判断申请结果，若失败退出 */
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
      return;
    }

    /*构造SMC Reject 消息*/
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = EMM_CN_MSG_PD_EMM;
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_CN_MT_SMC_REJ;

    /* 获得 EMM CAUSE*/
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = enCause;

    /* 填充消息ID */
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;
    pIntraMsg->enEmmMsgType             = NAS_EMM_MAS_SMC_REJ;

    /* 填充消息长度 */
    pIntraMsg->stNasMsg.ulNasMsgSize = ulPos;

    /*计算不包含消息头的消息长度*/
    uldataReqMsgLenNoHeader =
            NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(pIntraMsg->stNasMsg.ulNasMsgSize);

    /*填充消息头*/
    NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*空口消息上报 SECU_MODE_REJ*/
    NAS_LMM_SendOmtAirMsg( NAS_EMM_OMT_AIR_MSG_UP,
                          NAS_EMM_SECU_REJ,
                          (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*关键事件上报 SECU_MODE_REJ*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_SECU_REJ);

    /*向MRRC发送SMC Reject消息*/
    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsImeisvReq
 Description     : 判断SMC消息中是否要求回复IMEISV信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-11  Draft Enact

*****************************************************************************/
NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  NAS_EMM_IsImeisvReq( VOS_VOID)
{
    NAS_EMM_SECU_SMC_STRU              *pstSmcStru = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_IsImeisvReq enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsImeisvReq_ENUM,LNAS_ENTRY);
    pstSmcStru = (NAS_EMM_SECU_SMC_STRU *)NAS_EMM_GetSecuBufSpace();

    if((NAS_EMM_BIT_SLCT == pstSmcStru->bitImeisvReq)
     &&(NAS_EMM_SMC_IMEISV_REQ == pstSmcStru->ucImeisvRsq))
    {
        return NAS_EMM_IMEISV_REQUEST;
    }
    else
    {
        return NAS_EMM_IMEISV_NOT_REQUEST;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_SmcSucc
 Description     : SMC消息验证成功的处理函数
 Input           : pucSmcMsg: 包括安全头的 NAS CN SMC消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-10  Draft Enact
    2.zhengjunyan 00148421      2011-12-13 Mod:non-current security context还原时，
                                           NASCOUNT也要还原
    3.lihong 00150010           2012-10-18 Mod:emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_SmcSucc( const LRRC_LNAS_MSG_STRU    *pstSmcMsg )
{
    NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  enIfImeisvReq   = NAS_EMM_IMEISV_REQUEST_INFO_BUTT;
    VOS_UINT8                               ucSmcEia        = 0;
    VOS_UINT8                               ucKsiValue      = 0;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcSucc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcSucc_ENUM,LNAS_ENTRY);

    if((NAS_EMM_SMC_UPDATE_NEW_MAPPED == NAS_EMM_GetSmcType())
     ||(NAS_EMM_SMC_UPDATE_NEW_NATIVE == NAS_EMM_GetSmcType()))
    {
        /*DL_NASCOUNT和UP_NASCOUNT 清零*/
        NAS_EMM_GetSecuDlNasCount() = 0;
        NAS_EMM_GetSecuUlNasCount() = 0;

        /*更新上下文*/
        NAS_EMM_UpdateCurSecuCntxt();
    }
    else if(NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE == NAS_EMM_GetSmcType())
    {
        /*Dl_NasCount在SMC完整性检查成功时，已经还原，此处不必处理*/
        /*Ul_NasCount还原为non-current security context中的Ul_NasCount*/
        NAS_EMM_SetSecuUlNasCount(NAS_EMM_GetSecuNonCurUlNasCount());

        /*更新KSIasme和Kasme*/
        NAS_EMM_UpdateCurSecuCntxt();
    }
    else
    {
        /*删除 new mapped security context*/
        NAS_EMM_ClearNewMappedSecuCntxt();
    }

    /* 如果是启用EIA0，则需要赋值KSI，KASME，设置上下行NAS COUNT为0,
       删除卡或者NV中的安全上下文 */
    /*lint -e416 -e415*/
    ucSmcEia    = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE-NAS_EMM_SECU_PLAIN_MSG_POS] & NAS_EMM_LOW_3_BITS_F;
    ucKsiValue  = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_KSI_POSE-NAS_EMM_SECU_PLAIN_MSG_POS] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        if (ucKsiValue != NAS_EMM_GetSecuCurKSIasme())
        {
            NAS_LMM_MEM_CPY_S(  NAS_EMM_GetSecuCurKasmeAddr(),
                                NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                NAS_EMM_GetEia0Kasme(),
                                NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
        }

        NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIasme(ucKsiValue);

        /*DL_NASCOUNT和UP_NASCOUNT 清零*/
        NAS_EMM_GetSecuDlNasCount() = 0;
        NAS_EMM_GetSecuUlNasCount() = 0;

        /* 删除卡或者NV中的安全上下文 */
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);

        /* 通知EMM EIA0算法启用 */
        NAS_EMM_SendIntraEia0ActNotify();
    }

    /*更新NasCK,NasIK*/
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_LMM_SECU_NAS_KEY_LEN,
                                        NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_LMM_SECU_NAS_KEY_LEN);
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_LMM_SECU_NAS_KEY_LEN,
                                        NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_LMM_SECU_NAS_KEY_LEN);

    /*更新算法*/
    NAS_EMM_GetSecuAlg() = pstSmcMsg->aucNasMsg[NAS_EMM_PLAIN_SMC_ALG_POSE];

    /*发送RRC_MM_INFO_CHNG_REQ消息*/
    NAS_EMM_SendSecuParamToRrc();

    /*发送SECU_MODE_COMPLETE消息*/
    enIfImeisvReq = NAS_EMM_IsImeisvReq();
    NAS_EMM_SecuSendSmcCmp(enIfImeisvReq);
    /* 勾出当前安全上下文 */
    NAS_EMM_SndOmLogEpsSecContextInfo();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SmcCommProcess
 Description     : SMC消息处理函数:
                   1.检查消息类型，关键消息和关键事件上报
                   2.SMC携带的参数检查，包括:KSI,算法,replayed UE_NET_CAP,
                                             replayed NONCEue
                   3.完整性检查
                   4.检查成功，更新安全上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-5  Draft Enact

*****************************************************************************/

/*lint -e416*/
/*lint -e415*/
/*lint -e831*/

VOS_UINT32  NAS_EMM_SmcCommProcess(LRRC_LNAS_MSG_STRU  *pstSmcMsg)/*lint -e416 -e415*/
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcCommProcess enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcCommProcess_ENUM,LNAS_ENTRY);

    /*检查消息类型*/
    if(NAS_EMM_CN_MT_SMC_CMD != pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_MT_POSE])
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SmcCommProcess:SMC MT ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SmcCommProcess_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*SMC消息上报*/
    NAS_LMM_SendOmtAirMsg(               NAS_EMM_OMT_AIR_MSG_DOWN,
                                        NAS_EMM_SECU_CMD,
                         (NAS_MSG_STRU*)pstSmcMsg);

    /*关键事件上报 SECU_MODE_CMD*/
    NAS_LMM_SendOmtKeyEvent(EMM_OMT_KE_SECU_CMD);

    /*停止T3416,删除 RAND和 RES*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();


#if (VOS_OS_VER != VOS_WIN32)
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;

    /* 如果是EIA0，先判断是否满足可以使用EIA0的条件 */
    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        /* 如果 (既不是紧急注册过程中也不包含紧急承载)即商用模式且不是紧急呼)，不可以使用EIA0 */
        if(NAS_EMM_YES != NAS_EMM_IsRegStatusEmcRegingOrContainEmcBear())
        {
            NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcCommProcess:Rejected! it's not allowed to use EIA0.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcCommProcess_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
            return NAS_EMM_SECU_FAIL;
        }
    }
#endif


    /*SMC携带的参数检查:首先对空口消息解码，然后对SMC消息携带的参数进行检验
      包括:KSI, 算法, replayed UE_NET_CAP, replayed NONCEue,码流长度*/
    ulRslt = NAS_EMM_SmcVerifyParam(pstSmcMsg);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return NAS_EMM_SECU_FAIL;
    }

    /*对SMC消息进行完整性检查*/
    ulRslt = NAS_EMM_SmcIntCheck(pstSmcMsg);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return NAS_EMM_SECU_FAIL;
    }

    /*SMC消息验证成功的处理*/
    /*NAS_EMM_SmcSucc(pstSmcMsg);*/

    return NAS_EMM_SECU_SUCC;
}
/*lint +e831*/
/*lint +e415*/
/*lint +e416*/


/*****************************************************************************
 Function Name   : NAS_EMM_HandleLrrcMsgSndFailForHandOver
 Description     : LRRC_LMM_SEND_RSLT_FAILURE发送失败时的处理
 Input           : None
 Output          : None
 Return          : None

 History         : leixiantiao 00258641    2013-12-03      Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_HandleLrrcMsgSndFailForHandOver(
                                        NAS_EMM_MRRC_MGMT_DATA_STRU  *pEmmMrrcMgmtData,
                                        VOS_UINT32 *pulIsDelBuff)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;

    /* 从当前状态机中获取状态 */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();

    if (EMM_MS_TAU_INIT == enMainState)
    {
        /*停止T3430定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

        /*停止T3440定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif
        /* 大数据:更新TAU以及COMM流程DATA REQ发送失败次数 */
        NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);
    }
    else if (EMM_MS_SER_INIT == enMainState)
    {
        /* 大数据: 更新Ser Comm流程DATA REQ发送失败次数 */
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
        /*  需要将对应的缓存消息的ulHoWaitSysInfoFlag设置为true */
        pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_TRUE;
        *pulIsDelBuff = VOS_FALSE;
    }
    else
    {

    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_SndCommonProcedureMsgFailProc
 Description     : GUTI CMP,IDEN RSP,SMC CMP,SMC REJ,AUTH RSP,AUTH FAILURE发送失败时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen 00209181    2013-03-30      Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndCommonProcedureMsgFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SndCommonProcedureMsgFailProc enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SndCommonProcedureMsgFailProc_ENUM,LNAS_FUNCTION_LABEL1);
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SndCommonProcedureMsgFailProc enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SndCommonProcedureMsgFailProc_ENUM,LNAS_FUNCTION_LABEL2);
            break;
    }


    /* 从当前状态机中获取状态 */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();
    enSubState                          = NAS_LMM_GetEmmCurFsmSS();

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            /*l00258641 2013-12-3 圈复杂度太高，重构代码 begin*/
            NAS_EMM_HandleLrrcMsgSndFailForHandOver(pEmmMrrcMgmtData, pulIsDelBuff);
            /*l00258641 2013-12-3 圈复杂度太高，重构代码 end*/

            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            if (EMM_MS_REG_INIT == enMainState)
            {
                /* 大数据: 统计attach Comm流程DATA REQ发送失败次数 */
                NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
                /* 重启ATTACH流程 */
                NAS_EMM_RestartAttProcedural();
            }
            else if (EMM_MS_DEREG_INIT == enMainState)
            {
                NAS_LMM_StopStateTimer(     TI_NAS_EMM_T3421);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*发送end notify消息给RRC，通知RRC释放资源*/
                NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                #endif

                /*发送DETACH REQUEST消息*/
                NAS_EMM_SendDetachReqMo();
            }
            else if ((EMM_MS_REG == enMainState)
                       && (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == enSubState))
            {
                NAS_LMM_StopStateTimer(     TI_NAS_EMM_T3421);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*发送end notify消息给RRC，通知RRC释放资源*/
                NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                #endif


                /* 发起IMSI DETACH流程 */
                NAS_EMM_SendImsiDetachReqMo();
            }
            else if (EMM_MS_TAU_INIT == enMainState)
            {
                /*停止T3430定时器*/
                NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*发送end notify消息给RRC，通知RRC释放资源*/
                NAS_EMM_TAU_SendRrcDsdsEndNotify();
                #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
                NAS_EMM_SendMtcTAUEndType();
#endif

                /*停止T3440定时器*/
                NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
                /* 大数据:更新TAU COMM流程DATA REQ发送失败次数 */
                NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);

                /* 新增入参TAU发起原因 */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);
            }
            else if (EMM_MS_SER_INIT == enMainState)
            {
                /* 大数据: 更新Ser Comm流程DATA REQ发送失败次数 */
                NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
                NAS_EMM_RestartSerProcedural();
            }
            else
            {

            }

            break;

        default:
            break;
        }

    return NAS_EMM_SUCC;

}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

