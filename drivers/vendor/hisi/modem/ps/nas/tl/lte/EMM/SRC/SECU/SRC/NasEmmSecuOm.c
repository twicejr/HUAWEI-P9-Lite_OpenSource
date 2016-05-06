


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuInclude.h"
#include    "NasEmmSecuInterface.h"
#include    "NasCommPrint.h"
#include    "MmcLmmInterface.h"
#include    "GmmLmmInterface.h"


/*lint -e7*/
/*lint -e322*/
#include  "TlPsDrv.h"
/*lint +e322*/
/*lint +e7*/


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUOM_C
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
 Function Name   : NAS_EMM_SecuInit
 Description     : 安全模块的初始化函数
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhengjunyan 00148421      2010-3-3  Draft Enact
    2.zhengjunyan 00148421      2011-3-8  安全修改为调用BSP接口，不需要初始化引擎
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_EMM_SecuInit( VOS_VOID )
{

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuInit entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuInit_ENUM,LNAS_ENTRY);

    /* 清空SECU模块的全局控制结构 */
    NAS_LMM_MEM_SET_S(  &g_NasEmmSecuControl,
                        sizeof(NAS_LMM_SECU_CONTROL_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTROL_STRU));

    /* 初始化当前安全上下文和新安全上下文无效*/
    NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
    NAS_EMM_SetSecuCurKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
    NAS_EMM_SetSecuNewMappedKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
    NAS_EMM_SetSecuNewNativeKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
    NAS_EMM_SetSecuNonCurNativeKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    /* 初始化UMTS security context无效*/
    NAS_EMM_SetUmtsKsi(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    /* 初始化安全状态*/
    NAS_EMM_SecuStateConvert(           EMM_CUR_SECU_NOT_EXIST,
                                        EMM_NEW_SECU_NOT_EXIST);

    return;
}


VOS_VOID  NAS_EMM_FreeSecuDyn( VOS_VOID )
{
    /* 暂时为空 */
    return;
}


/*****************************************************************************
 Function Name   : NAS_Secu_FsmInit
 Description     : 安全模块状态机初始化
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhengjunyan 00148421      2010-3-3  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_Secu_FsmInit( VOS_VOID )
{

    NAS_LMM_FSM_STATE_STRU              *pSecuCurState;

    NAS_EMM_SECU_LOG_NORM("NAS_Secu_FsmInit                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_Secu_FsmInit_ENUM,LNAS_ENTRY);

    /* 当前状态初始化 */
    pSecuCurState = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_SECU);
    pSecuCurState->enFsmId               = NAS_LMM_PARALLEL_FSM_SECU;
    pSecuCurState->enMainState           = EMM_CUR_SECU_NOT_EXIST;
    pSecuCurState->enSubState            = EMM_NEW_SECU_NOT_EXIST;
    pSecuCurState->enStaTId              = NAS_LMM_STATE_TI_BUTT;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ConnToIdleTransSecuSta
 Description     : 连接态从CONN进入IDLE，导致当前安全上下文状态变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ConnToIdleTransSecuSta( VOS_VOID )
{

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ConnToIdleTransSecuSta entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ConnToIdleTransSecuSta_ENUM,LNAS_ENTRY);

    /*如果当前安全上下文存在且激活，则状态迁移到:EMM_CUR_SECU_EXIST_NOT_ACTIVE*/
    if(EMM_CUR_SECU_EXIST_ACTIVE == NAS_LMM_GetSecuCurFsmCS())
    {
        NAS_EMM_SecuStateConvert(       EMM_CUR_SECU_EXIST_NOT_ACTIVE,
                                        NAS_LMM_GetSecuCurFsmNS());
    }
    else
    {
       /*其他情况，安全上下文状态不变*/
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSetCurCntxt
 Description     : 开机读卡时，用从卡中读出的安全上下文设置当前安全上下文，
                   并根据该数据是否有效，设置当前安全上下文的状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-24  Draft Enact
    2.zhengjunyan 00148421      2011-08-10 DTS2011080301942

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuSetCurCntxt( const NAS_LMM_SECU_CONTEXT_STRU *pstCurSecuCntxt )
{
    VOS_UINT32                          ulRslt;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUpdateCurCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSetCurCntxt_ENUM,LNAS_ENTRY);

    /* 若读出来的安全上下文无效 */
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE <= pstCurSecuCntxt->ucKSIasme)
    {
        NAS_EMM_SECU_LOG_WARN("NAS_EMM_SecuUpdateCurCntxt: KSI is unAvailable");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSetCurCntxt_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*赋值给当前安全上下文*/
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurCntxtAddr(),
                                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                                        pstCurSecuCntxt,
                                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    /*EPS系统中KSIsgsn始终无效*/
    NAS_EMM_GetSecuCurKSIsgsn()         = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;

    /*如果开机成功获取当前安全上下文，计算NasCk,NasIk*/
    ulRslt = NAS_EMM_ComputeNasKey(     NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY,
                                        NAS_EMM_GetSecuEca());
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuSetCurCntxt:Compute NasCK Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuSetCurCntxt_ENUM,LNAS_FUNCTION_LABEL2);
    }

    ulRslt = NAS_EMM_ComputeNasKey(     NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY,
                                        NAS_EMM_GetSecuEia());
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuSetCurCntxt:Compute NasIK Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuSetCurCntxt_ENUM,LNAS_FUNCTION_LABEL3);
    }

    /*更新寄存器中的NAS密钥*/
    /*NasIK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);
    /*NasCK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    /*安全上下文状态*/
    NAS_EMM_SecuStateConvert(           EMM_CUR_SECU_EXIST_NOT_ACTIVE,
                                        NAS_LMM_GetSecuCurFsmNS());

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetCurCntxtAddr
 Description     : 获取当前安全上下文的地址
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-24  Draft Enact

*****************************************************************************/
NAS_LMM_SECU_CONTEXT_STRU *  NAS_EMM_SecuGetCurCntxtAddr(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuGetCurCntxtAddr entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetCurCntxtAddr_ENUM,LNAS_ENTRY);

    return NAS_EMM_GetSecuCurCntxtAddr();
}


/*****************************************************************************
 Function Name   : NAS_EMM_ClearCurSecuCntxt
 Description     : 删除当前安全上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ClearCurSecuCntxt(VOS_VOID)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_SUCC;

    (VOS_VOID)ulRslt;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ClearCurSecuCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearCurSecuCntxt_ENUM,LNAS_ENTRY);

    /*清空当前安全上下文MEM*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuCurCntxtAddr(),
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    /*清空寄存器中的密钥*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);

    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    /*当前ksi无效*/
    NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
    NAS_EMM_SetSecuCurKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    /*状态*/
    NAS_EMM_SecuStateConvert(           EMM_CUR_SECU_NOT_EXIST,
                                        NAS_LMM_GetSecuCurFsmNS());
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearNewMappedSecuCntxt
 Description     : 删除 new mapped security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearNewMappedSecuCntxt( VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ClearNewMappedSecuCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearNewMappedSecuCntxt_ENUM,LNAS_ENTRY);

    /*清空当前安全上下文MEM*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuNewMappedCntxtAddr(),
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    /*当前ksi无效*/
    NAS_EMM_SetSecuNewMappedKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearNewNativeSecuCntxt
 Description     : 删除 new native security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearNewNativeSecuCntxt( VOS_VOID )

{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ClearNewNativeSecuCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearNewNativeSecuCntxt_ENUM,LNAS_ENTRY);

    /*清空当前安全上下文MEM*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuNewNativeCntxtAddr(),
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    /*当前ksi无效*/
    NAS_EMM_SetSecuNewNativeKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearCurMappedSecuCntxt
 Description     : 删除 current mapped security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearCurMappedSecuCntxt( VOS_VOID )

{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ClearCurMappedSecuCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearCurMappedSecuCntxt_ENUM,LNAS_ENTRY);

    /*如果不存在 current mapped security context,则直接返回*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIsgsn())
    {
        return;
    }

    /*清空当前安全上下文MEM*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuCurCntxtAddr(),
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    /*设置KSIsgsn无效*/
    NAS_EMM_SetSecuCurKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
    NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearNonCurNativeSecuCntxt
 Description     : 删除 non-current native security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearNonCurNativeSecuCntxt( VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ClearNonCurNativeSecuCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearNonCurNativeSecuCntxt_ENUM,LNAS_ENTRY);

    /* 如果不存在 non-current native security context,则直接返回*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuNonCurNativeKSIasme())
    {
        return;
    }

    /* 清空 non-current native security context*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuNonCurNativeCntxtAddr(),
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    /* 设置KSIasme无效*/
    NAS_EMM_SetSecuNonCurNativeKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearAllSecuCntxt
 Description     : 删除所有的安全上下文，ATTACH/TAU/SERVICE/DETACH等流程收到
                   核心网特定原因值的处理，需要删除所有的安全上下文时，调用。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-12-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearAllSecuCntxt( VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ClearAllSecuCntxt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearAllSecuCntxt_ENUM,LNAS_ENTRY);

    /* 清空current security context*/
    NAS_EMM_ClearCurSecuCntxt();

    /* 清空new mapped security context*/
    NAS_EMM_ClearNewMappedSecuCntxt();

    /* 清空new native security context*/
    NAS_EMM_ClearNewNativeSecuCntxt();

    /* 清空non-current security context*/
    NAS_EMM_ClearNonCurNativeSecuCntxt();

    /* 安全上下文状态*/
    NAS_EMM_SecuStateConvert(           EMM_CUR_SECU_NOT_EXIST,
                                        EMM_NEW_SECU_NOT_EXIST);
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuDeregClrSecuCntxt
 Description     : EMM从REG态进入DEREG态，需要:
                  1)删除 new mapped security context
                  2)删除 current mapped security context,如果存在
                    non-current native security context则保存到current中
                  3)删除 new native security context

                  与HO相关，暂未完全实现
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuDeregClrSecuCntxt( VOS_VOID )
{
    /* 删除 new mapped secu cntxt*/
    NAS_EMM_ClearNewMappedSecuCntxt();

    /* 删除 new native secu cntext*/
    NAS_EMM_ClearNewNativeSecuCntxt();

    /* 删除 current mapped secu cntxt*/
    NAS_EMM_ClearCurMappedSecuCntxt();

    /* 如果存在 non-current native secu cntxt,
       则将其还原到 current native secu cntxt,
       并删除 non-current native secu cntxt*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNonCurNativeKSIasme())
    {
        NAS_EMM_SecuRecovNonCurNativeToCurNative();
        NAS_EMM_ClearNonCurNativeSecuCntxt();
    }

    /* 迁移安全上下文的状态*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuCurKSIasme())
    {
        NAS_LMM_SetSecuCurFsmCS(EMM_CUR_SECU_EXIST_NOT_ACTIVE);
    }
    else
    {
        NAS_LMM_SetSecuCurFsmCS(EMM_CUR_SECU_NOT_EXIST);
    }

    NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_NOT_EXIST);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetKSIValue
 Description     : NAS其他模块获取SECU模块中当前安全上下文的KSI
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID *

 History         :
    1.zhengjunyan 00148421      2010-3-16  Draft Enact
    2.zhengjunyan 00148421      2011-4-28  MOD:INTER RAT

*****************************************************************************/
VOS_UINT8   NAS_EMM_SecuGetKSIValue( VOS_VOID )
{
    VOS_UINT8                           ucKsi = 0;

    /* 判断如果 current KSIasme 和 KSIsgsn都无效，则返回 NO_KEY*/
    if((NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIasme())
     &&(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIsgsn()))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuGetKSIValue: KSIasme and KSIsgsn are all invalid.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetKSIValue_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;
    }

    /* 判断 KSIasme无效则返回 KSIsgsn;反之，返回 KSIasme*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIasme())
    {
        NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SecuGetKSIValue: KSIsgsn valid, is ",
                                NAS_EMM_GetSecuCurKSIsgsn());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuGetKSIValue_ENUM,LNAS_FUNCTION_LABEL2,
                                NAS_EMM_GetSecuCurKSIsgsn());
        ucKsi = (NAS_EMM_GetSecuCurKSIsgsn()|NAS_EMM_FOURTH_BITS_F);
    }
    else
    {
        NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SecuGetKSIValue: KSIasme valid, is ",
                                NAS_EMM_GetSecuCurKSIasme());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuGetKSIValue_ENUM,LNAS_FUNCTION_LABEL3,
                                NAS_EMM_GetSecuCurKSIasme());
        ucKsi = NAS_EMM_GetSecuCurKSIasme();
    }

    return ucKsi;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetUmtsKsi
 Description     : NAS其他模块获取SECU模块中的 UMTS KSI
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuGetUmtsKsi( VOS_VOID )
{
    return NAS_EMM_GetUmtsKsi();
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetUlNasCountVAlue
 Description     : NAS其他模块获取SECU模块中UL NAS COUNT 参数的值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuGetUlNasCountVAlue( VOS_VOID )
{
    return  NAS_EMM_GetSecuUlNasCount();
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetNonceUE
 Description     : NAS其他模块获取SECU模块中 NonceUE 的值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-16  Draft Enact

*****************************************************************************/
VOS_UINT8*  NAS_EMM_SecuGetNonceUE( VOS_VOID )
{
    return  NAS_EMM_GetSecuNonceUEAddr();
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetNonCurKSIasme
 Description     : NAS其他模块获取SECU模块中 non-current KSIasme的值。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-6-2  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_SecuGetNonCurKSIasme( VOS_VOID )
{
   return NAS_EMM_GetSecuNonCurNativeKSIasme();
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuPrintCipherPara
 Description     : 为了便于操作维护，打印与BSP_Cipher的安全接口
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h41410      2010-3-29  Draft Enact
    2.z00148421   2011-3-10  安全接口调整为调用 Cipher
*****************************************************************************/
VOS_VOID NAS_EMM_SecuPrintCipherPara(CIPHER_SINGLE_CFG_S const *pstSingleSecuPara,
                                                VOS_UINT8  const *pucSrc)
{
    /*VOS_UINT8                          *pucNasKeyAddr = VOS_NULL_PTR;*/
    VOS_UINT8                           aucKeyBuf[NAS_LMM_SECU_NAS_KEY_LEN];
    KEY_GET_S                           stKeyGet;
    VOS_UINT32                          ulRet;
    CIPHER_KEY_LEN_E                ulenKeyLen;

    NAS_EMM_SECU_LOG_INFO("======NAS SECU PRARM FOR CIPHER  are:======");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_EMM_SECU_PARA);

    NAS_EMM_SECU_LOG1_INFO("enOpType  = ", pstSingleSecuPara->enOpt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL1,pstSingleSecuPara->enOpt);
    NAS_EMM_SECU_LOG1_INFO("enEia = ", pstSingleSecuPara->stAlgKeyInfo.enAlgIntegrity);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL2,pstSingleSecuPara->stAlgKeyInfo.enAlgIntegrity);
    NAS_EMM_SECU_LOG1_INFO("enEea = ", pstSingleSecuPara->stAlgKeyInfo.enAlgSecurity);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL3,pstSingleSecuPara->stAlgKeyInfo.enAlgSecurity);
    NAS_EMM_SECU_LOG1_INFO("ulNasCount = ", pstSingleSecuPara->u32Count);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL4,pstSingleSecuPara->u32Count);
    NAS_EMM_SECU_LOG1_INFO("Direnction = ", pstSingleSecuPara->u8Direction);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL5,pstSingleSecuPara->u8Direction);

    NAS_EMM_SECU_LOG1_INFO("enNasIkIndex = ", pstSingleSecuPara->stAlgKeyInfo.u32KeyIndexInt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL6,pstSingleSecuPara->stAlgKeyInfo.u32KeyIndexInt);

    stKeyGet.enKeyLen       = CIPHER_KEY_L128;
    stKeyGet.pKeyAddr       = aucKeyBuf;
    stKeyGet.penOutKeyLen   = &ulenKeyLen;

    ulRet = NAS_EMM_SecuGetKeyByIndex(LTE_SECU_NAS_INTEGRITY_KEY_INDEX, &stKeyGet);
    if(VOS_OK != ulRet)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuPrintCipherPara: err!! NasIk.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_ERROR);
        return;
    }

    NAS_EMM_SECU_LOG1_INFO("NasIK, Outlength = , key = :", ulenKeyLen);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL7,ulenKeyLen);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                        stKeyGet.pKeyAddr,
                                        NAS_LMM_SECU_NAS_KEY_LEN);


    NAS_EMM_SECU_LOG1_INFO("enNasCkIndex = ", pstSingleSecuPara->stAlgKeyInfo.u32KeyIndexSec);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL8,pstSingleSecuPara->stAlgKeyInfo.u32KeyIndexSec);

    ulRet = NAS_EMM_SecuGetKeyByIndex(LTE_SECU_NAS_CIPHER_KEY_INDEX, &stKeyGet);
    if(VOS_OK != ulRet)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuPrintCipherPara:NULL_NasCk.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL9);
        return;
    }

    NAS_EMM_SECU_LOG1_INFO("NasCK, Outlength = , key = :", ulenKeyLen);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL10,ulenKeyLen);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                        stKeyGet.pKeyAddr,
                                        NAS_LMM_SECU_NAS_KEY_LEN);



    NAS_EMM_SECU_LOG1_INFO("ulSrcLen  = ", pstSingleSecuPara->u32BlockLen);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL11,pstSingleSecuPara->u32BlockLen);
    NAS_EMM_SECU_LOG_INFO("SrcMsg = ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuPrintCipherPara_ENUM,LNAS_FUNCTION_LABEL12);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(), pucSrc, pstSingleSecuPara->u32BlockLen);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSetKeyByKeyIndex
 Description     : 封装BSP提供的将NAS密钥写入寄存器的接口
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-3-8  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuSetKeyByKeyIndex( const VOS_UINT8 *pucKeyAddr,
                                    NAS_EMM_SECU_NAS_KEY_TYPE_ENUM_UINT8 enKeyType )
{
    VOS_INT32                           lRslt;
    VOS_UINT32                          ulKeyIndex;

    /* 入参检查*/
    if (VOS_NULL_PTR == pucKeyAddr)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuSetKeyByKeyIndex: NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuSetKeyByKeyIndex_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 根据密钥类型，获取索引*/
    switch (enKeyType)
    {
        case NAS_EMM_SECU_INTEGRITY_KEY:
            ulKeyIndex = LTE_SECU_NAS_INTEGRITY_KEY_INDEX;
            break;

        case NAS_EMM_SECU_CIPHER_KEY:
            ulKeyIndex = LTE_SECU_NAS_CIPHER_KEY_INDEX;
            break;

        default:
            NAS_EMM_SECU_LOG_WARN("NAS_EMM_SecuSetKeyByKeyIndex: KeyType Err.");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_SecuSetKeyByKeyIndex_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_SECU_FAIL;
    }

    /* 调用BSP接口，把NAS密钥写入寄存器*/
    /*lint -e64*/
    lRslt = LDRV_CIPHER_SET_KEY(pucKeyAddr, CIPHER_KEY_L128, ulKeyIndex);
    /*lint +e64*/
    if (CIPHER_SUCCESS != lRslt)
    {
        NAS_EMM_SECU_LOG1_ERR("NAS_EMM_SecuSetKeyByKeyIndex: BSP set Err.",ulKeyIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_SecuSetKeyByKeyIndex_ENUM,LNAS_FUNCTION_LABEL2,ulKeyIndex);
        return NAS_EMM_SECU_FAIL;
    }

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetKeyByIndex
 Description     : 读取Register中的密钥
 Input           : None
 Output          : None
 Return          : VOS_UINT8 *

 History         :
    1.zhengjunyan 00148421      2011-3-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SecuGetKeyByIndex(   VOS_UINT32      ulKeyIndex,
                                        KEY_GET_S      *pstKeyGet)
{
    VOS_INT32 lRet;

    lRet = LDRV_CIPHER_GET_KEY(  ulKeyIndex, pstKeyGet);
    /* coverity[unchecked_value] */
    NAS_EMM_SECU_LOG1_WARN("NAS_EMM_SecuGetKeyByIndex: LDRV_CIPHER_GET_KEY, lRet = ",
                            lRet);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_SecuGetKeyByIndex_ENUM,LNAS_FUNCTION_LABEL1,
                            lRet);

    return  (VOS_UINT32)lRet;
}



/*****************************************************************************
 Function Name   : NAS_CIPHER_SingleSubmitTask
 Description     : 封装 CIPHER 提供的接口函数 mdrv_cipher_single_submit_task
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-3-16  Draft Enact

*****************************************************************************/
VOS_INT32  NAS_CIPHER_SingleSubmitTask(CIPHER_SINGLE_CFG_S *pstSingleSecuPara)
{
    VOS_INT32                           lRslt;

    /* 调用BSP接口解保护*/
    /*lint -e64*/
    pstSingleSecuPara->enSubmAttr = CIPHER_SUBM_BLK_HOLD;
    pstSingleSecuPara->u32Private = NAS_EMM_SECU_NO_PRIVATE;

    lRslt = LDRV_CIPHER_SINGLE_SUBMIT_TASK(LTE_SECURITY_CHANNEL_NAS, pstSingleSecuPara);
    /*lint +e64*/

     return lRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcReselSecuInfoReq
 Description     : 重选场景下，GMM请求LMM计算 Mapped UMTS security context和
                   NAS TOKEN
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcReselSecuInfoReq( MsgBlock * pMsg )
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU   *pstLmmReselSecuInfoCnf = VOS_NULL_PTR;
    GMM_LMM_RESEL_SECU_INFO_REQ_STRU   *pstGmmReselSecuInfoReq = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_LMM_PreProcReselSecuInfoReq enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcReselSecuInfoReq_ENUM,LNAS_ENTRY);

    /* 获取 GMM_LMM_RESEL_SECU_INFO_REQ*/
    pstGmmReselSecuInfoReq = (GMM_LMM_RESEL_SECU_INFO_REQ_STRU *)pMsg;

    /* 申请LMM_GMM_RESEL_SECU_INFO_CNF消息内存*/
    pstLmmReselSecuInfoCnf = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_GMM_RESEL_SECU_INFO_CNF_STRU));
    if (NAS_EMM_NULL_PTR == pstLmmReselSecuInfoCnf)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_LMM_PreProcReselSecuInfoReq: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcReselSecuInfoReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLmmReselSecuInfoCnf,
                        sizeof(LMM_GMM_RESEL_SECU_INFO_CNF_STRU),
                        0,
                        sizeof(LMM_GMM_RESEL_SECU_INFO_CNF_STRU));

    /* LMM_GMM_RESEL_SECU_INFO_CNF组装:填充消息头和消息ID*/
    NAS_EMM_COMP_GMM_MSG_HEADER(        pstLmmReselSecuInfoCnf,
                                        (sizeof(LMM_GMM_RESEL_SECU_INFO_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));
    pstLmmReselSecuInfoCnf->ulMsgId = ID_LMM_GMM_RESEL_SECU_INFO_CNF;
    pstLmmReselSecuInfoCnf->ulOpId = pstGmmReselSecuInfoReq->ulOpId;

    /* LMM_GMM_RESEL_SECU_INFO_CNF组装: 消息体填充*/
    NAS_LMM_CompLmmReselSecuInfoCnf(pstLmmReselSecuInfoCnf);

    /* 发送 LMM_GMM_RESEL_SECU_INFO_CNF*/
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstLmmReselSecuInfoCnf);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_LMM_CompLmmReselSecuInfoCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact
    2.zhengjunyan 00148421      2011-6-02  DTS2011060202506:每计算一次NAS TOKEN，
                                           UpNasCount需要加1
*****************************************************************************/
VOS_VOID  NAS_LMM_CompLmmReselSecuInfoCnf(
                    LMM_GMM_RESEL_SECU_INFO_CNF_STRU   *pstLmmReselSecuInfoCnf )
{
    VOS_UINT32                          ulCurEmmStat;

    /* 获取 EMM 当前状态，根据当前状态不同处理*/
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);
    switch (ulCurEmmStat)
    {
        /* Dereg.NoCellAvailable状态下，
           如果当前安全上下文不存在，返回成功，置bitOpSecuInfo为0;
           如果当前安全上下文存在，返回成功，置bitOpSecuInfo为1,计算安全参数
        */
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_CELL_AVAILABLE):
            pstLmmReselSecuInfoCnf->enRslt = LMM_GMM_SECU_INFO_RSLT_SUCC;
            if (EMM_CUR_SECU_NOT_EXIST == NAS_LMM_GetSecuCurFsmCS())
            {
                pstLmmReselSecuInfoCnf->bitOpSecuInfo = NAS_EMM_BIT_NO_SLCT;
            }
            else
            {
                pstLmmReselSecuInfoCnf->bitOpSecuInfo = NAS_EMM_BIT_SLCT;
                NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle(
                                    &(pstLmmReselSecuInfoCnf->stReselSecuInfo));

                /* 每计算一次NAS_TOKEN,UP_NASCOUTN需要加1*/
                NAS_EMM_GetSecuUlNasCount()++;
            }
            break;

        /* Reg.NoCellAvailable状态下，
           如果当前安全上下文不存在，返回失败，置bitOpSecuInfo为0;
           如果当前安全上下文存在，返回成功，置bitOpSecuInfo为1,计算安全参数
        */
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NO_CELL_AVAILABLE):
            if (EMM_CUR_SECU_NOT_EXIST == NAS_LMM_GetSecuCurFsmCS())
            {
                pstLmmReselSecuInfoCnf->enRslt = LMM_GMM_SECU_INFO_RSLT_FAIL;
                pstLmmReselSecuInfoCnf->bitOpSecuInfo = NAS_EMM_BIT_NO_SLCT;
            }
            else
            {
                pstLmmReselSecuInfoCnf->enRslt = LMM_GMM_SECU_INFO_RSLT_SUCC;
                pstLmmReselSecuInfoCnf->bitOpSecuInfo = NAS_EMM_BIT_SLCT;
                NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle(
                                    &(pstLmmReselSecuInfoCnf->stReselSecuInfo));
                /* 每计算一次NAS_TOKEN,UP_NASCOUTN需要加1*/
                NAS_EMM_GetSecuUlNasCount()++;
            }
            break;

        /* 如果EMM不在挂起态，则直接回复GMM失败*/
        default:
            pstLmmReselSecuInfoCnf->enRslt = LMM_GMM_SECU_INFO_RSLT_FAIL;
            pstLmmReselSecuInfoCnf->bitOpSecuInfo = NAS_EMM_BIT_NO_SLCT;
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_CompLmmHoSecuInfoCnf
 Description     : 组装 LMM_GMM_HO_SECU_INFO_CNF消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_CompLmmHoSecuInfoCnf(
                    LMM_GMM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf )
{


    /* EMM状态正确:
       如果当前安全上下文不存在，回复失败，置bitOpSecuInfo为0;
       如果当前安全上下文存在，回复成功，置bitOpSecuInfo为1,计算安全参数*/
    if (EMM_CUR_SECU_NOT_EXIST == NAS_LMM_GetSecuCurFsmCS())
    {
        pstLmmHoSecuInfoCnf->enRslt         = LMM_GMM_SECU_INFO_RSLT_FAIL;
        pstLmmHoSecuInfoCnf->bitOpSecuCntxt = NAS_EMM_BIT_NO_SLCT;
    }
    else
    {
        pstLmmHoSecuInfoCnf->enRslt         = LMM_GMM_SECU_INFO_RSLT_SUCC;
        pstLmmHoSecuInfoCnf->bitOpSecuCntxt = NAS_EMM_BIT_SLCT;
        NAS_EMM_SecuGetUmtsSecuCntxtHo(&(pstLmmHoSecuInfoCnf->stHoUmtsSecuCntxt));
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_CompLmmMmHoSecuInfoCnf
 Description     : 组装 LMM_MM_HO_SECU_INFO_CNF消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-10-09  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_CompLmmMmHoSecuInfoCnf(
                    LMM_MM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf )
{
    NAS_LMM_SECU_CONTEXT_STRU           *pstCurSecuCntxt = VOS_NULL_PTR;

    /*获取当前安全上下文*/
    pstCurSecuCntxt = NAS_EMM_SecuGetCurCntxtAddr();

    /* 如果当前安全上下文不存在，回复失败，置bitOpSecuInfo为0;
       如果当前安全上下文存在，使用算法为EIA0，回复失败
       如果当前安全上下文存在，回复成功，置bitOpSecuInfo为1,计算安全参数*/
    if (EMM_CUR_SECU_NOT_EXIST == NAS_LMM_GetSecuCurFsmCS())
    {
        pstLmmHoSecuInfoCnf->enRslt         = MM_LMM_SECU_INFO_RSLT_FAIL_OTHERS;
        pstLmmHoSecuInfoCnf->bitOpSecuCntxt = NAS_EMM_BIT_NO_SLCT;
    }
    /* 如果算法是EIA0，则标示没有安全上下文 */
    else if (NAS_EMM_SECU_ALG_EIA0 == (pstCurSecuCntxt->ucSecuAlg & NAS_EMM_LOW_3_BITS_F))
    {
        pstLmmHoSecuInfoCnf->enRslt         = MM_LMM_SECU_INFO_RSLT_FAIL_EIA0;
        pstLmmHoSecuInfoCnf->bitOpSecuCntxt = NAS_EMM_BIT_NO_SLCT;
    }
    else
    {
        pstLmmHoSecuInfoCnf->enRslt         = MM_LMM_SECU_INFO_RSLT_SUCC;
        pstLmmHoSecuInfoCnf->bitOpSecuCntxt = NAS_EMM_BIT_SLCT;
        NAS_EMM_SecuGetMmUmtsSecuCntxtHo(&(pstLmmHoSecuInfoCnf->stHoSecuCntxt));
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcHoSecuInfoReq
 Description     : 切换场景下，GMM请求LMM计算 Mapped UMTS security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcHoSecuInfoReq(  MsgBlock * pMsg )
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf = VOS_NULL_PTR;
    GMM_LMM_HO_SECU_INFO_REQ_STRU   *pstGmmHoSecuInfoReq = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_LMM_PreProcHoSecuInfoReq enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcHoSecuInfoReq_ENUM,LNAS_ENTRY);

    /* 获取 GMM_LMM_HO_SECU_INFO_REQ*/
    pstGmmHoSecuInfoReq = (GMM_LMM_HO_SECU_INFO_REQ_STRU *)pMsg;

    /* 申请LMM_GMM_HO_SECU_INFO_CNF消息内存*/
    pstLmmHoSecuInfoCnf = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_GMM_HO_SECU_INFO_CNF_STRU));
    if (NAS_EMM_NULL_PTR == pstLmmHoSecuInfoCnf)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_LMM_PreProcHoSecuInfoReq: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcHoSecuInfoReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLmmHoSecuInfoCnf,
                        sizeof(LMM_GMM_HO_SECU_INFO_CNF_STRU),
                        0,
                        sizeof(LMM_GMM_HO_SECU_INFO_CNF_STRU));

    /* LMM_GMM_HO_SECU_INFO_CNF组装:填充消息头和消息ID*/
    NAS_EMM_COMP_GMM_MSG_HEADER(        pstLmmHoSecuInfoCnf,
                                        (sizeof(LMM_GMM_HO_SECU_INFO_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));
    pstLmmHoSecuInfoCnf->ulMsgId        = ID_LMM_GMM_HO_SECU_INFO_CNF;
    pstLmmHoSecuInfoCnf->ulOpId         = pstGmmHoSecuInfoReq->ulOpId;

    /* LMM_GMM_HO_SECU_INFO_CNF组装: 消息体填充*/
    NAS_LMM_CompLmmHoSecuInfoCnf(pstLmmHoSecuInfoCnf);

    /* 发送 LMM_GMM_HO_SECU_INFO_CNF*/
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstLmmHoSecuInfoCnf);

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgMmHoSecuInfoReq
 Description     : 切换场景下，MM请求LMM计算 Mapped UMTS security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-10-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgMmHoSecuInfoReq(  MsgBlock * pMsg )
{
    LMM_MM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf = VOS_NULL_PTR;
    MM_LMM_HO_SECU_INFO_REQ_STRU   *pstMmHoSecuInfoReq = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_LMM_PreProcMsgMmHoSecuInfoReq enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgMmHoSecuInfoReq_ENUM,LNAS_ENTRY);

    /* 获取 MM_LMM_HO_SECU_INFO_REQ*/
    pstMmHoSecuInfoReq = (MM_LMM_HO_SECU_INFO_REQ_STRU *)pMsg;

    /* 申请LMM_MM_HO_SECU_INFO_CNF消息内存*/
    pstLmmHoSecuInfoCnf = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_HO_SECU_INFO_CNF_STRU));
    if (NAS_EMM_NULL_PTR == pstLmmHoSecuInfoCnf)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_LMM_PreProcMsgMmHoSecuInfoReq: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMsgMmHoSecuInfoReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLmmHoSecuInfoCnf,
                        sizeof(LMM_MM_HO_SECU_INFO_CNF_STRU),
                        0,
                        sizeof(LMM_MM_HO_SECU_INFO_CNF_STRU));

    /* LMM_MM_HO_SECU_INFO_CNF组装:填充消息头和消息ID*/
    EMM_PUBU_COMP_MM_MSG_HEADER(        pstLmmHoSecuInfoCnf,
                                        (sizeof(LMM_MM_HO_SECU_INFO_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));
    pstLmmHoSecuInfoCnf->ulMsgId        = ID_LMM_MM_HO_SECU_INFO_CNF;
    pstLmmHoSecuInfoCnf->ulOpId         = pstMmHoSecuInfoReq->ulOpId;

    /* LMM_MM_HO_SECU_INFO_CNF组装: 消息体填充*/
    NAS_LMM_CompLmmMmHoSecuInfoCnf(pstLmmHoSecuInfoCnf);

    /* 发送 LMM_MM_HO_SECU_INFO_CNF*/
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstLmmHoSecuInfoCnf);

    return NAS_LMM_MSG_HANDLED;

}


/*****************************************************************************
 Function Name   : STUB_NAS_LMM_CompLmmHoSecuInfoCnf
 Description     : 前期的HO联调，为GMM提供该函数。
                   GMM提供HO功能后，此函数不再使用。
 Input           : None
 Output          : pstLmmHoSecuInfoCnf，
                   其中部分成员不使用，包括: |- VOS_MSG_HEADER
                                                |  ulMsgId;
                                                |  ulOpId;
                                                |  bitSpare
                                                |- bitOpSecuCntxt  :

                   使用的成员包括:            |- enRslt;
                                                |- stHoUmtsSecuCntxt;

                    enRslt: LMM_GMM_SECU_INFO_RSLT_SUCC时，表示获取成功;
                            LMM_GMM_SECU_INFO_RSLT_FAIL时，表示获取失败;

 Return          : MMC_LMM_RESULT_ID_ENUM,
                            GMM_LMM_FAIL时，表示输入空指针
                            GMM_LMM_SUCC时，表示输入指针非空
 History         :
    1.Hanlufeng 41410      2011-6-23  Draft Enact

*****************************************************************************/
GMM_LMM_RESULT_ID_ENUM_UINT32  STUB_NAS_LMM_CompLmmHoSecuInfoCnf(
                LMM_GMM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf )
{

    if(VOS_NULL_PTR == pstLmmHoSecuInfoCnf)
    {
        NAS_EMM_SECU_LOG_ERR("STUB_NAS_LMM_CompLmmHoSecuInfoCnf: NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(STUB_NAS_LMM_CompLmmHoSecuInfoCnf_ENUM,LNAS_NULL_PTR);
        return  GMM_LMM_FAIL;
    }

    NAS_EMM_SECU_LOG_INFO("STUB_NAS_LMM_CompLmmHoSecuInfoCnf: enter.");
    TLPS_PRINT2LAYER_INFO(STUB_NAS_LMM_CompLmmHoSecuInfoCnf_ENUM,LNAS_ENTRY);

    NAS_LMM_CompLmmHoSecuInfoCnf(pstLmmHoSecuInfoCnf);
    return  GMM_LMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetUmtsSecuContext
 Description     : 获取UMTS安全上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuGetUmtsSecuContext( VOS_VOID )
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       enRslt;
    NAS_GUMM_INFO_STRU                  stGummInfoStru;

    /*初始化*/
    NAS_LMM_MEM_SET_S(&stGummInfoStru, sizeof(NAS_GUMM_INFO_STRU), 0, sizeof(NAS_GUMM_INFO_STRU));

    NAS_EMM_SECU_LOG_NORM("NAS_EMM_SecuGetUmtsSecuContext is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetUmtsSecuContext_ENUM,LNAS_ENTRY);
    /* 调用GMM提供的接口，读取UMTS安全上下文*/
    enRslt = NAS_EMM_GetGuInfo(NAS_GUMM_UMTS_SECU_PARA, &stGummInfoStru);
    if(MMC_LMM_FAIL == enRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuGetUmtsSecuContext: Nas_GetGuInfo Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuGetUmtsSecuContext_ENUM,LNAS_ERROR);
        return NAS_EMM_SECU_FAIL;
    }

    /* 保存*/
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetUmtsSecuContextAddr(),
                                        sizeof(NAS_GUMM_UMTS_CONTEXT_STRU),
                                        &(stGummInfoStru.u.stSecuContext),
                                        sizeof(NAS_GUMM_UMTS_CONTEXT_STRU));
    return NAS_EMM_SECU_SUCC;
}


VOS_VOID  NAS_EMM_SecuResumeIdle(VOS_VOID )
{
    VOS_UINT32                          ulRslt;

    /* 检查Current安全上下文状态*/
    if (EMM_CUR_SECU_EXIST_ACTIVE == NAS_LMM_GetSecuCurFsmCS())
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuResumeIdle: Cur Sta Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuResumeIdle_ENUM,LNAS_ERROR);
        return;
    }

    /* 生成 NonceUE*/
    ulRslt = NAS_EMM_DeriveRandNonceUE(NAS_EMM_GetSecuNonceUEAddr());
    if(NAS_EMM_SECU_SUCC != ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuResumeIdle: NAS_EMM_DeriveRandNonceUE Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuResumeIdle_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /* 读取 UMTS secu context*/
    ulRslt = NAS_EMM_SecuGetUmtsSecuContext();
    if(NAS_EMM_SECU_SUCC != ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuResumeIdle: NAS_EMM_SecuGetUmtsSecuContext Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuResumeIdle_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* 将 new mapped secu cntxt中的 KSIsgsn赋值为 UMTS KSI*/
    NAS_EMM_SetSecuNewMappedKSIsgsn(NAS_EMM_GetUmtsKsi());

    /* 安全上下文状态迁移:主状态不变，子状态迁移到 EMM_NEW_SECU_EXIST*/
    NAS_EMM_SecuStateConvert(           NAS_LMM_GetSecuCurFsmCS(),
                                        EMM_NEW_SECU_EXIST);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuRrcSecuParamIndHo
 Description     : GU切换到L,根据LRRC上报的安全参数,
                   产生 current mapped security context
                   注:从24301协议分析 non-current native 和 new native任何时候不
                   应该同时存在
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.zhengjunyan 00148421      2011-9-13  DTS2011082202543
*****************************************************************************/
VOS_VOID  NAS_EMM_SecuRrcSecuParamIndHo(
                                                const VOS_UINT8 *pucSecuParaHo )
{
    NAS_LMM_HO_LRRC_SECU_PARA_STRU           stHoLrrcSecuPara;
    VOS_UINT32                               ulRslt;
    VOS_UINT8                                ucEia = NAS_EMM_NULL;

    NAS_LMM_MEM_SET_S(  &stHoLrrcSecuPara,
                        sizeof(NAS_LMM_HO_LRRC_SECU_PARA_STRU),
                        0,
                        sizeof(NAS_LMM_HO_LRRC_SECU_PARA_STRU));

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuRrcSecuParamIndHo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuRrcSecuParamIndHo_ENUM,LNAS_ENTRY);

    /* 解析LRRC上报的安全参数*/
    NAS_EMM_SecuDecodeRrcSecuPara(pucSecuParaHo, &stHoLrrcSecuPara);

    ucEia = stHoLrrcSecuPara.ucSecuAlg & NAS_LMM_LOW_3_BITS_F;
    if (NAS_EMM_SECU_ALG_EIA0 == ucEia)
    {
        /* 检查LRRC上报的安全参数的有效性:
           1)Eea,Eia是否是UE_NET_CAP支持的算法
           2)Eea为Eea0
           2)KsiType必须是 mapped 类型
           3)KsiValue取值范围[0,6]*/
        ulRslt = NAS_EMM_Eia0SecuVerifyRrcSecuPara(&stHoLrrcSecuPara);
    }
    else
    {
        /* 检查LRRC上报的安全参数的有效性:
           1)Eea,Eia是否是UE_NET_CAP支持的算法
           2)KsiType必须是 mapped 类型
           3)KsiValue取值范围[0,6]*/
        ulRslt = NAS_EMM_NotEia0SecuVerifyRrcSecuPara(&stHoLrrcSecuPara);
    }

    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return;
    }

    /* 如果存在current native security context，
       将其保存到 non-current native seucrity context,
       删除 new native security context*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuCurKSIasme())
    {
        NAS_EMM_SecuSaveCurNativeToNonCurNative();
        NAS_EMM_ClearNewNativeSecuCntxt();
    }

    /* 删除 current security context*/
    NAS_EMM_ClearCurSecuCntxt();

    /* 获取UMTS security context*/
    ulRslt = NAS_EMM_SecuGetUmtsSecuContext();
    if((NAS_EMM_SECU_SUCC != ulRslt) && (NAS_EMM_SECU_ALG_EIA0 != ucEia))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuRrcSecuParamIndHo:\
                                          NAS_EMM_SecuGetUmtsSecuContext Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuRrcSecuParamIndHo_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 保存LRRC上报的安全参数，产生current mapped security context*/
    ulRslt = NAS_EMM_SecuHoCurMappedSecuCntxt(&stHoLrrcSecuPara);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuRrcSecuParamIndHo:\
                                        NAS_EMM_SecuHoCurMappedSecuCntxt Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuRrcSecuParamIndHo_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* 记录产生了Mapped安全上下文，如果后续流程出现HO失败
       则根据该标志判断是否需要恢复安全上下文*/
    NAS_EMM_SetFlagInterRatHoMapped(NAS_EMM_SECU_INTER_RAT_HO_MAPPED);

    /* 回复LRRC_LMM_SECU_PARA_RSP*/
    NAS_EMM_SecuSendLrrcSecuParaRsp();

    /* 迁移安全上下文状态*/
    NAS_LMM_SetSecuCurFsmCS(EMM_CUR_SECU_EXIST_ACTIVE);
    if((NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNewMappedKSIsgsn())
     ||(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNewNativeKSIasme())
     ||(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNonCurNativeKSIasme()))
    {
        NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_EXIST);
    }
    else
    {
        NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_NOT_EXIST);
    }

    return;

}


VOS_VOID  NAS_EMM_SecuDecodeRrcSecuPara(
                                  const VOS_UINT8 *pucSecuParaHo,
                                        NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara)
{
    VOS_UINT8                           ucIndex = 0;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuDecodeRrcSecuPara entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuDecodeRrcSecuPara_ENUM,LNAS_ENTRY);

    /* 入参检查*/
    if((VOS_NULL_PTR == pucSecuParaHo)
     ||(VOS_NULL_PTR == pstHoLrrcSecuPara))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuDecodeRrcSecuPara:NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuDecodeRrcSecuPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 解析安全参数*/
    /* NonceMME*/
    NAS_LMM_MEM_CPY_S(                  pstHoLrrcSecuPara->aucNonceMME,
                                        NAS_EMM_SECU_NONCE_MME_LEN,
                                        pucSecuParaHo,
                                        NAS_EMM_SECU_NONCE_MME_LEN);
    ucIndex += NAS_EMM_SECU_NONCE_MME_LEN;

    /* SecuAlg*/
    pstHoLrrcSecuPara->ucSecuAlg = pucSecuParaHo[ucIndex];
    ucIndex++;

    /* KsiType, KsiValue*/
    pstHoLrrcSecuPara->ucKsiValue = (pucSecuParaHo[ucIndex]) & NAS_EMM_LOW_3_BITS_F;
    pstHoLrrcSecuPara->ucKsiType = ((pucSecuParaHo[ucIndex]) & NAS_EMM_FOURTH_BITS_F)
                                                >>NAS_EMM_SECU_KSI_TYPE_BIT_POS;

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SecuVerifyRrcSecuPara
 Description     : GU切换到L,验证LRRC上报的安全参数的有效性
                   KsiValue为MME产生，不一定与UMTS ksi一致。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-10-19  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_Eia0SecuVerifyRrcSecuPara
(
    const NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara
)
{
    VOS_UINT32                      ulRslt;
    VOS_UINT8                       ucEea;
    VOS_UINT8                       ucEia;


    NAS_EMM_SECU_LOG_INFO("NAS_EMM_Eia0SecuVerifyRrcSecuPara entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SecuVerifyRrcSecuPara_ENUM,LNAS_ENTRY);

    /* 检查EEA,EIA*/
    ucEia =  (pstHoLrrcSecuPara->ucSecuAlg) & NAS_EMM_LOW_3_BITS_F;
    ucEea =  (pstHoLrrcSecuPara->ucSecuAlg>>4) & NAS_EMM_LOW_3_BITS_F;
    ulRslt = NAS_EMM_Eia0SmcVerifyAlg(ucEea, ucEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SecuVerifyRrcSecuPara:Alg Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /* 检查KsiValue:[0,6]*/
    if(NAS_EMM_SECU_MAX_KSI < pstHoLrrcSecuPara->ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SecuVerifyRrcSecuPara:KsiValue Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /* 检查KSI是否为0 */
    if (0 != pstHoLrrcSecuPara->ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SecuVerifyRrcSecuPara:KsiType is not zero.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL3);
    }

    /* 检查KsiType:必须是Mapped类型*/
    if(NAS_EMM_SECU_KSI_TYPE_MAPPED != pstHoLrrcSecuPara->ucKsiType)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SecuVerifyRrcSecuPara:KsiType Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL4);
    }

    /* 为了兼容不同网络，实行宽进严出原则，暂不判断是否有紧急承载 */

    return NAS_EMM_SECU_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_NotEia0SecuVerifyRrcSecuPara
 Description     : GU切换到L,验证LRRC上报的安全参数的有效性
                   KsiValue为MME产生，不一定与UMTS ksi一致。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_NotEia0SecuVerifyRrcSecuPara(
                        const NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara )
{
    VOS_UINT32                      ulRslt;
    VOS_UINT8                       ucEea;
    VOS_UINT8                       ucEia;


    NAS_EMM_SECU_LOG_INFO("NAS_EMM_NotEia0SecuVerifyRrcSecuPara entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SecuVerifyRrcSecuPara_ENUM,LNAS_ENTRY);

    /* 检查EEA,EIA*/
    ucEia =  (pstHoLrrcSecuPara->ucSecuAlg) & NAS_EMM_LOW_3_BITS_F;
    ucEea =  (pstHoLrrcSecuPara->ucSecuAlg>>4) & NAS_EMM_LOW_3_BITS_F;
    ulRslt = NAS_EMM_IsAlgUeSupported(ucEea, ucEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SecuVerifyRrcSecuPara:Alg Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /* 检查KsiValue:[0,6]*/
    if(NAS_EMM_SECU_MAX_KSI < pstHoLrrcSecuPara->ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SecuVerifyRrcSecuPara:KsiValue Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /* 检查KsiType:必须是Mapped类型*/
    if(NAS_EMM_SECU_KSI_TYPE_MAPPED != pstHoLrrcSecuPara->ucKsiType)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SecuVerifyRrcSecuPara:KsiType Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SecuVerifyRrcSecuPara_ENUM,LNAS_FUNCTION_LABEL3);
    }

    return NAS_EMM_SECU_SUCC;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSaveCurNativeToNonCurNative
 Description     : 将 current native security context
                   保存到 non-current native security context中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuSaveCurNativeToNonCurNative( VOS_VOID )
{
    NAS_LMM_SECU_CONTEXT_STRU          *pstNonCurNatvieSecuCntxt = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSaveCurNativeToNonCurNative entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSaveCurNativeToNonCurNative_ENUM,LNAS_ENTRY);

    /* 获取 non-current native security context*/
    pstNonCurNatvieSecuCntxt = NAS_EMM_GetSecuNonCurNativeCntxtAddr();

    /* 将 current native security context
       保存到 non-current native security context*/
    /* KSIasme*/
    pstNonCurNatvieSecuCntxt->ucKSIasme = NAS_EMM_GetSecuCurKSIasme();

    /* Kasme*/
    NAS_LMM_MEM_CPY_S(      pstNonCurNatvieSecuCntxt->aucKasme,
                            NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                            NAS_EMM_GetSecuCurKasmeAddr(),
                            NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    /* UP_NASCOUNT 和 DL_NASCOUNT*/
    pstNonCurNatvieSecuCntxt->ulUlNasCount = NAS_EMM_GetSecuUlNasCount();
    pstNonCurNatvieSecuCntxt->ulDlNasCount = NAS_EMM_GetSecuDlNasCount();

    /* Eea,Eia*/
    pstNonCurNatvieSecuCntxt->ucSecuAlg = NAS_EMM_GetSecuAlg();

    /* NasCK, NasIK*/
    NAS_LMM_MEM_CPY_S(        &(pstNonCurNatvieSecuCntxt->stNasKey),
                              sizeof(NAS_LMM_SECU_KEY_STRU),
                              NAS_EMM_GetSecuCurNasKeyAddr(),
                              sizeof(NAS_LMM_SECU_KEY_STRU));
    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuRecovNonCurNativeToCurNative
 Description     : 将 non-current native security context
                   还原到 current native security context中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuRecovNonCurNativeToCurNative( VOS_VOID )
{
    NAS_LMM_SECU_CONTEXT_STRU          *pstNonCurNatvieSecuCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_SUCC;

    (VOS_VOID)ulRslt;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuRecovNonCurNativeToCurNative entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuRecovNonCurNativeToCurNative_ENUM,LNAS_ENTRY);

    /* 获取 non-current native security context*/
    pstNonCurNatvieSecuCntxt = NAS_EMM_GetSecuNonCurNativeCntxtAddr();

    /* KSIasme*/
    NAS_EMM_SetSecuCurKSIasme(NAS_EMM_GetSecuNonCurNativeKSIasme());

    /* KSIsgsn*/
    NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    /* Kasme*/
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        pstNonCurNatvieSecuCntxt->aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    /* UP_NASCOUNT 和 DL_NASCOUNT*/
    NAS_EMM_GetSecuUlNasCount() = pstNonCurNatvieSecuCntxt->ulUlNasCount;
    NAS_EMM_GetSecuDlNasCount() = pstNonCurNatvieSecuCntxt->ulDlNasCount;

    /* Eea,Eia*/
    NAS_EMM_SetSecuAlg(pstNonCurNatvieSecuCntxt->ucSecuAlg);

    /* NasCK, NasIK*/
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurNasKeyAddr(),
                                        sizeof(NAS_LMM_SECU_KEY_STRU),
                                       &(pstNonCurNatvieSecuCntxt->stNasKey),
                                        sizeof(NAS_LMM_SECU_KEY_STRU));
    /* 写入寄存器*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasIkAddr(),
                                    NAS_EMM_SECU_INTEGRITY_KEY);

    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasCkAddr(),
                                    NAS_EMM_SECU_CIPHER_KEY);
    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuHoCurMappedSecuCntxt
 Description     : GU切换到 L,产生映射的安全上下文作为当前安全上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuHoCurMappedSecuCntxt(
                        const NAS_LMM_HO_LRRC_SECU_PARA_STRU *pstHoLrrcSecuPara )

{
    VOS_UINT32                          ulRslt;
     VOS_UINT8                          ucEea;
    VOS_UINT8                           ucEia;

    /* KSIsgsn*/
    NAS_EMM_SetSecuCurKSIsgsn(pstHoLrrcSecuPara->ucKsiValue);
    NAS_EMM_SetSecuCurKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);

    /* SecuAlg*/
    NAS_EMM_SetSecuAlg(pstHoLrrcSecuPara->ucSecuAlg);

    /* NonceMME*/
    NAS_LMM_MEM_CPY_S(      NAS_EMM_GetSecuNonceMMEAddr(),
                            NAS_EMM_SECU_NONCE_MME_LEN,
                            pstHoLrrcSecuPara->aucNonceMME,
                            NAS_EMM_SECU_NONCE_MME_LEN);
    /* 计算 Kasme*/
    ucEia =  (pstHoLrrcSecuPara->ucSecuAlg) & NAS_EMM_LOW_3_BITS_F;
    ucEea =  (pstHoLrrcSecuPara->ucSecuAlg>>4) & NAS_EMM_LOW_3_BITS_F;

    /* 产生K'ASME */
    if (NAS_EMM_SECU_ALG_EIA0 == ucEia)
    {
        NAS_LMM_MEM_CPY_S(  NAS_EMM_GetSecuCurKasmeAddr(),
                            NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                            NAS_EMM_GetEia0Kasme(),
                            NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    }
    else
    {
        ulRslt = NAS_EMM_DeriveKasmeFromUmtsHo(NAS_EMM_GetSecuCurKasmeAddr());
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuHoCurMappedSecuCntxt:\
                                            NAS_EMM_DeriveKasmeFromUmtsHo Err.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuHoCurMappedSecuCntxt_ENUM,LNAS_FAIL);
            return NAS_EMM_SECU_FAIL;
        }
    }

    /* UP_NASCOUNT,DL_NASCOUNT清零*/
    NAS_EMM_GetSecuDlNasCount() = 0;
    NAS_EMM_GetSecuUlNasCount() = 0;

    /* 计算 NasCk,NasIk*/
    NAS_EMM_DeriveNewNasKey(NAS_EMM_GetSecuCurKasmeAddr(), ucEea, ucEia);
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_NAS_INT_LEN,
                                        NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_NAS_INT_LEN);
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_NAS_ENC_LEN,
                                        NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_NAS_ENC_LEN);

    /* 将 NasCk,NasIk写入寄存器*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);

    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSendLrrcSecuParaRsp
 Description     : 成功处理LRRC_LMM_SECU_PARA_IND，回复LRRC_LMM_SECU_PARA_RSP
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact
    2.zhengjunyan 00148421      2011-9-19  DTS2011090201417

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuSendLrrcSecuParaRsp( VOS_VOID )
{
    LRRC_LMM_SECU_PARA_RSP_STRU        *pstLrrcSecuParaRsp = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* 计算长度不包含VOS消息头*/
    ulMsgLen     = NAS_EMM_MSG_ID_LEN + sizeof(LRRC_LNAS_SECURITY_KEY_STRU);

    /* 分配内存*/
    pstLrrcSecuParaRsp = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulMsgLen + NAS_EMM_LEN_VOS_MSG_HEADER);
    if(NAS_EMM_NULL_PTR == pstLrrcSecuParaRsp)
    {
        return;
    }

    /* 清空申请到的消息空间*/
    NAS_LMM_MEM_SET_S(  pstLrrcSecuParaRsp,
                        sizeof(LRRC_LMM_SECU_PARA_RSP_STRU),
                        0,
                        sizeof(LRRC_LMM_SECU_PARA_RSP_STRU));

    /* 填充VOS消息头*/
    NAS_EMM_SET_RRC_MSG_HEADER(pstLrrcSecuParaRsp, ulMsgLen);

    /* 填充消息ID*/
    pstLrrcSecuParaRsp->enMsgId           = ID_LRRC_LMM_SECU_PARA_RSP;

    /* 填充消息体 */
    /* UP_NASCOUNT*/
    pstLrrcSecuParaRsp->stSecuKey.ulNasCount = 0xFFFFFFFF;

    /* Kasme*/
    NAS_LMM_MEM_CPY_S(                  pstLrrcSecuParaRsp->stSecuKey.aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    /* 发送 LRRC_LMM_SECU_PARA_RSP */
    NAS_LMM_SEND_MSG(pstLrrcSecuParaRsp);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuRrcRelIndHoFail
 Description     : LRRC执行GU到L的切换失败，需要删除本次产生的 current mapped
                   security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact
    2.zhengjunyan 00148421      2011-9-13  DTS2011082202543
*****************************************************************************/
VOS_VOID  NAS_EMM_SecuRrcRelIndHoFail(VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuRrcRelIndHoFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuRrcRelIndHoFail_ENUM,LNAS_ENTRY);

    /* 判断如果没有产生Mapped安全上下文，则不需要改变安全上下文*/
    if(NAS_EMM_SECU_INTER_RAT_HO_NOT_MAPPED == NAS_EMM_GetFlagInterRatHoMapped())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuRrcRelIndHoFail:no need recovery.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuRrcRelIndHoFail_ENUM,LNAS_FUNCTION_LABEL1 );
        return;
    }

    /* 删除当前安全上下文*/
    NAS_EMM_ClearCurSecuCntxt();

    /* 如果存在 non-current native security context，则将其还原到 current,
       删除 non-current native security context*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNonCurNativeKSIasme())
    {
        NAS_EMM_SecuRecovNonCurNativeToCurNative();
        NAS_EMM_ClearNonCurNativeSecuCntxt();
    }

    /* HO失败，恢复安全上下文后，清除标志*/
    NAS_EMM_SetFlagInterRatHoMapped(NAS_EMM_SECU_INTER_RAT_HO_NOT_MAPPED);

    /* 迁移安全上下文的状态*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuCurKSIasme())
    {
        NAS_LMM_SetSecuCurFsmCS(EMM_CUR_SECU_EXIST_NOT_ACTIVE);
    }
    else
    {
        NAS_LMM_SetSecuCurFsmCS(EMM_CUR_SECU_NOT_EXIST);
    }

    if((NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNewMappedKSIsgsn())
     ||(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNewNativeKSIasme())
     ||(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNonCurNativeKSIasme()))
    {
        NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_EXIST);
    }
    else
    {
        NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_NOT_EXIST);
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuUpdateDlNasCountHo
 Description     : 从 L向 G/U切换，更新DL_NASCOUNT(第一阶段暂不实现)
                   24301 9.9.2.6 NAS security parameters from E-UTRA
                        ---------------------------------------
                         8   7   6   5   4   3   2   1
                         --------------------------------------
                         0 | 0 | 0 | 0 |  DL NAS COUNT value
                         --------------------------------------
 (short)
 octet 2
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuUpdateDlNasCountHo( VOS_UINT8 ucCnDlNasCount )
{
    VOS_UINT32                          ulUeDlNasCount = 0;
    VOS_UINT8                           ucUeLow4Bit = 0;
    VOS_UINT32                          ucLocDlCountHighByte = 0;

    NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuUpdateDlNasCountHo entered.");
    TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuUpdateDlNasCountHo_ENUM,LNAS_ENTRY);

    /* 获取UE本地 DL_NASCOUNT 的低4bit*/
    ulUeDlNasCount = NAS_EMM_GetSecuDlNasCount();
    ucUeLow4Bit = (VOS_UINT8)(ulUeDlNasCount & NAS_EMM_LOW_HALF_BYTE_F);

    /* LOCAL SQN大于等于窗体时，如果LOCAL COUNT低4位大于ucHoSecuPara并且LOCAL COUNT低4位减
    去ucHoSecuPara大于窗体则第5位加1，其他情况正常处理。LOCAL COUNT低4位小于窗体时，
    如果COUNT值高位大于0,LOCAL COUNT低4位小于RCV SQN并且RCV SQN减去LOCAL COUNT低4位大于0xF减
    去窗体则第5位减去1，其他情况正常处理 */
    ucLocDlCountHighByte =  ulUeDlNasCount & NAS_EMM_SECU_MASK_HO_OVERFLOW_COUNT;
    if(ucUeLow4Bit >= NAS_EMM_SECU_DL_COUNT_WINDOW)
    {
        if((ucUeLow4Bit > ucCnDlNasCount)
            &&(ucUeLow4Bit - ucCnDlNasCount > NAS_EMM_SECU_DL_COUNT_WINDOW))
        {
            ulUeDlNasCount += NAS_EMM_SECU_HO_DL_OVERFLOW;
        }
    }
    else
    {
        if((ucLocDlCountHighByte > 0)
        &&(ucCnDlNasCount > ucUeLow4Bit)
        &&(ucCnDlNasCount - ucUeLow4Bit >= (0x0F - NAS_EMM_SECU_DL_COUNT_WINDOW)))
        {
            ulUeDlNasCount -= NAS_EMM_SECU_HO_DL_OVERFLOW;
        }
    }

    /* 清空UE DL_NASCOUNT的低 4bit*/
    ulUeDlNasCount &= NAS_EMM_SECU_MASK_HO_OVERFLOW_COUNT;

    /* 低4bit赋值为网侧下发的值*/
    ulUeDlNasCount += ucCnDlNasCount;

    /* 计算的count值大于current count值，则更新 current DL_NASCOUNT */
    if(ulUeDlNasCount > NAS_EMM_GetSecuDlNasCount())
    {
        NAS_EMM_SetSecuDlNasCount(ulUeDlNasCount);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuHoOrCcoReverse
 Description     : 切换或者CCO回退，当前安全上下文的状态要恢复到激活态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-6-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuHoOrCcoReverse( VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuHoOrCcoReverse entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuHoOrCcoReverse_ENUM,LNAS_ENTRY);

    /* 如果当前安全上下文状态不是存在未激活，则报错*/
    if(EMM_CUR_SECU_EXIST_NOT_ACTIVE != NAS_LMM_GetSecuCurFsmCS())
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuHoOrCcoReverse: Cur Secu Sta Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuHoOrCcoReverse_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }


    /* 当前安全上下文状态恢复到激活态*/
    NAS_EMM_SecuStateConvert(           EMM_CUR_SECU_EXIST_ACTIVE,
                                        NAS_LMM_GetSecuCurFsmNS());
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle
 Description     : IDLE态下为G/U模计算UMTS secu context和 NAS TOKEN
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle(
                        LMM_GMM_RESEL_SECU_INFO_STRU       *pstReselSecuInfo )
{
    LMM_GMM_UMTS_SECU_CONTEXT_STRU     *pstUmtsSecuCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = 0;

    /* 入参指针检查*/
    if (VOS_NULL_PTR == pstReselSecuInfo)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle:NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstUmtsSecuCntxt = &(pstReselSecuInfo->stUmtsSecuContext);

    /* 获取 mapped UMTS security context*/
    /* KSI: 当前安全上下文的KSI*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIsgsn())
    {
        pstUmtsSecuCntxt->KSI = NAS_EMM_GetSecuCurKSIasme();
    }
    else
    {
        pstUmtsSecuCntxt->KSI = NAS_EMM_GetSecuCurKSIsgsn();
    }

    /* CK,IK*/
    ulRslt = NAS_EMM_DeriveUmtsCkIkFromEpsIdle(
                            pstReselSecuInfo->stUmtsSecuContext.aucUmtsCk,
                            pstReselSecuInfo->stUmtsSecuContext.aucUmtsIk);
    if(NAS_EMM_SECU_SUCC != ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle: NAS CK||IK ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /* 获取NAS TOKEN*/
    ulRslt = NAS_EMM_DeriveNasToken(pstReselSecuInfo->aucNasToken);
    if(NAS_EMM_SECU_SUCC != ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle: NAS TOKEN ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuGetUmtsSecuCntxtAndNasTokenIdle_ENUM,LNAS_FUNCTION_LABEL1);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetUmtsSecuCntxtHo
 Description     : 切换场景下为G/U模计算UMTS security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuGetUmtsSecuCntxtHo(
                                LMM_GMM_UMTS_SECU_CONTEXT_STRU *pstUmtsSecuCntxt)
{
    VOS_UINT32                          ulRslt;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuGetUmtsSecuCntxtHo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetUmtsSecuCntxtHo_ENUM,LNAS_ENTRY);

    /* KSI:current KSIasme or KSIsgsn*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIasme())
    {
        pstUmtsSecuCntxt->KSI           = NAS_EMM_GetSecuCurKSIsgsn();
    }
    else
    {
        pstUmtsSecuCntxt->KSI           = NAS_EMM_GetSecuCurKSIasme();
    }

    /* UmtsCK, UmtsIK*/
    ulRslt = NAS_EMM_DeriveUmtsCkIkFromEpsHo(pstUmtsSecuCntxt->aucUmtsCk,
                                             pstUmtsSecuCntxt->aucUmtsIk);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuGetUmtsSecuCntxtHo:\
                                        NAS_EMM_DeriveUmtsCkIkFromEpsHo Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuGetUmtsSecuCntxtHo_ENUM,LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuGetMmUmtsSecuCntxtHo
 Description     : SRVCC切换场景下为U模计算UMTS security context
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-10-09   Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuGetMmUmtsSecuCntxtHo(
                                MM_LMM_GU_SECU_CONTEXT_STRU *pstUmtsSecuCntxt)
{
    VOS_UINT32                          ulRslt;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuGetMmUmtsSecuCntxtHo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetMmUmtsSecuCntxtHo_ENUM,LNAS_ENTRY);

    /* KSI:current KSIasme or KSIsgsn*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_GetSecuCurKSIasme())
    {
        pstUmtsSecuCntxt->ulKSI           = NAS_EMM_GetSecuCurKSIsgsn();
    }
    else
    {
        pstUmtsSecuCntxt->ulKSI           = NAS_EMM_GetSecuCurKSIasme();
    }

    /* UmtsCK, UmtsIK*/
    ulRslt = NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc(pstUmtsSecuCntxt->aucCk,
                                                pstUmtsSecuCntxt->aucIk);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuGetMmUmtsSecuCntxtHo:\
                                        NAS_EMM_DeriveUmtsCkIkFromEpsHo Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuGetMmUmtsSecuCntxtHo_ENUM,LNAS_ERROR);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DeriveRandNonceUE
 Description     : 随机产生NONCEue
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-21  Draft Enact
    2.zhengjunyan 00148421      2011-5-18  为了GTR测试能够匹配，在PC环境下固定NonceUE
*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveRandNonceUE( VOS_UINT8 *pucNonceUE )
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulRandom;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveRandNonceUE entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveRandNonceUE_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if (VOS_NULL_PTR == pucNonceUE)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveRandNonceUE:NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveRandNonceUE_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 清空原 NonceUE*/
    NAS_LMM_MEM_SET_S(pucNonceUE, NAS_EMM_SECU_NONCE_UE_LEN, 0, NAS_EMM_SECU_NONCE_UE_LEN);

#if(VOS_WIN32 == VOS_OS_VER)
    /* 数据来源于真实测试环境*/
    pucNonceUE[0] = 0xdf;
    pucNonceUE[1] = 0xdd;
    pucNonceUE[2] = 0xf5;
    pucNonceUE[3] = 0xe9;
#else
    /* 生成随机数*/
    for (i = 0; i < NAS_EMM_SECU_NONCE_UE_LEN; i++)
    {
        ulRandom = VOS_Rand(NAS_EMM_SECU_RANDOM_RANGE);
        pucNonceUE[i] = (VOS_UINT8)ulRandom;
    }
#endif

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DeriveKasmeFromUmtsIdle
 Description     : 从 G/U 模重选,重定向或者CCO到 L 模，计算K'asme
                   reference:33401-960 A.11
                     -   FC = 0x19,
                     -   P0 = NONCEUE
                     -   L0 = length of the NONCEUE (i.e. 0x00 0x04)
                     -   P1 = NONCEMME
                     -   L1 = length of the NONCEMME (i.e. 0x00 0x04)
                   The input key shall be the concatenation of CK || IK.

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveKasmeFromUmtsIdle( VOS_UINT8 *pucKasme )
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                      *pucNonceUE = VOS_NULL_PTR;
    VOS_UINT8                      *pucNonceMME = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveKasmeFromUmtsIdle entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveKasmeFromUmtsIdle_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if (VOS_NULL_PTR == pucKasme)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveKasmeFromUmtsIdle: NULL PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveKasmeFromUmtsIdle_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 编码KDF算法需要的参数 */

    /* encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_MAPPED_KASME_IDLE_FC;

    /* encode NONCEue&Len*/
    pucNonceUE = NAS_EMM_GetSecuNonceUEAddr();

    aucAlgParam[ulIndex++] = pucNonceUE[0];
    aucAlgParam[ulIndex++] = pucNonceUE[1];
    aucAlgParam[ulIndex++] = pucNonceUE[2];
    aucAlgParam[ulIndex++] = pucNonceUE[3];

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NONCE_UE_LEN;

    /* encode NONCEmme&Len */
    pucNonceMME = NAS_EMM_GetSecuNonceMMEAddr();

    aucAlgParam[ulIndex++] = pucNonceMME[0];
    aucAlgParam[ulIndex++] = pucNonceMME[1];
    aucAlgParam[ulIndex++] = pucNonceMME[2];
    aucAlgParam[ulIndex++] = pucNonceMME[3];

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NONCE_MME_LEN;

    /* encode UMTS CK||IK*/

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_UMTS_CK_LENGTH,
                        NAS_EMM_GetUmtsCkAddr(),
                        NAS_UMTS_CK_LENGTH);

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)&aucKeyParam[NAS_UMTS_CK_LENGTH],
                        NAS_UMTS_IK_LENGTH,
                        NAS_EMM_GetUmtsIkAddr(),
                        NAS_UMTS_IK_LENGTH);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,pucKasme);

    return ulRslt;

}

/*****************************************************************************
 Function Name   : NAS_EMM_DeriveKasmeFromUmtsHo
 Description     : 从 G/U 模切换到 L 模，计算K'asme
                   reference:33401-960 A.10
                 -   FC = 0x18
                 -   P0 = NONCEMME
                 -   L0  = length of NONCEMME (i.e. 0x00 0x04)
                 The input key shall be the concatenation of CK || IK.

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveKasmeFromUmtsHo( VOS_UINT8 *pucKasme )
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                      *pucNonceMME = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveKasmeFromUmtsHo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveKasmeFromUmtsHo_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if (VOS_NULL_PTR == pucKasme)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveKasmeFromUmtsHo: NULL PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveKasmeFromUmtsHo_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }


    /* 编码KDF算法需要的参数 */

    /* encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_MAPPED_KASME_HO_FC;

    /* encode NONCEmme&Len */
    pucNonceMME = NAS_EMM_GetSecuNonceMMEAddr();

    aucAlgParam[ulIndex++] = pucNonceMME[0];
    aucAlgParam[ulIndex++] = pucNonceMME[1];
    aucAlgParam[ulIndex++] = pucNonceMME[2];
    aucAlgParam[ulIndex++] = pucNonceMME[3];

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NONCE_MME_LEN;

    /* encode UMTS CK||IK*/

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_UMTS_CK_LENGTH,
                        NAS_EMM_GetUmtsCkAddr(),
                        NAS_UMTS_CK_LENGTH);

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)&aucKeyParam[NAS_UMTS_CK_LENGTH],
                        NAS_UMTS_IK_LENGTH,
                        NAS_EMM_GetUmtsIkAddr(),
                        NAS_UMTS_IK_LENGTH);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,pucKasme);

    return ulRslt;

}

/*****************************************************************************
 Function Name   : NAS_EMM_DeriveUmtsCkIkFromEpsIdle
 Description     : 从 L 模重选、重定向或者CCO到 G/U 模，产生UMTS安全上下文的CK,IK
                   reference:33401-960 A.13
                 -   FC = 0x1B
                 -   P0 = NAS uplink COUNT value
                 -   L0 = length of NAS uplink COUNT value (i.e. 0x00 0x04)
                 The input key shall be KASME.
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveUmtsCkIkFromEpsIdle(       VOS_UINT8 *pucUmtsCK,
                                                                   VOS_UINT8 *pucUmtsIk )
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                       aucUmtsCKIK[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT8                      *pucEpsKasme = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveUmtsCkIkFromEpsIdle entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveUmtsCkIkFromEpsIdle_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if ((VOS_NULL_PTR == pucUmtsCK)||(VOS_NULL_PTR == pucUmtsIk))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveUmtsCkIkFromEpsIdle: NULL PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveUmtsCkIkFromEpsIdle_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 编码KDF算法需要的参数 */

    /* encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_UMTS_CKIK_IDLE_FC;

    /* encode UP_NASCOUNT&Len */

    /*编码UP_NASCOUNT为P0*/
    NAS_SECU_SET_32BIT_PARA(&(aucAlgParam[ulIndex]), NAS_EMM_GetSecuUlNasCount());
    ulIndex += NAS_EMM_SECU_NASCOUNT_LEN;

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NASCOUNT_LEN;

    /* encode Kasme*/
    pucEpsKasme = NAS_EMM_GetSecuCurKasmeAddr();

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                        pucEpsKasme,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,aucUmtsCKIK);

    if (NAS_EMM_SECU_SUCC == ulRslt)
    {
        /* UmtsCK*/
        NAS_LMM_MEM_CPY_S(pucUmtsCK, NAS_UMTS_CK_LENGTH, aucUmtsCKIK, NAS_UMTS_CK_LENGTH);

        /* UmtsIK*/
        NAS_LMM_MEM_CPY_S(  pucUmtsIk,
                            NAS_UMTS_IK_LENGTH,
                            &(aucUmtsCKIK[NAS_UMTS_CK_LENGTH]),
                            NAS_UMTS_IK_LENGTH);

        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        return NAS_EMM_SECU_FAIL;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_DeriveUmtsCkIkFromEpsHo
 Description     : 从 L 模切换到 G/U 模，产生UMTS安全上下文的CK,IK
                   reference:33401-960 A.8
                 -   FC = 0x16
                 -   P0 = NAS downlink COUNT value
                 -   L0 = length of NAS downlink COUNT value (i.e. 0x00 0x04)
                 The input key shall be KASME.

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveUmtsCkIkFromEpsHo( VOS_UINT8 *pucUmtsCK,
                                                            VOS_UINT8 *pucUmtsIk)
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                       aucUmtsCKIK[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT8                      *pucEpsKasme = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveUmtsCkIkFromEpsHo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveUmtsCkIkFromEpsHo_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if ((VOS_NULL_PTR == pucUmtsCK)||(VOS_NULL_PTR == pucUmtsIk))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveUmtsCkIkFromEpsHo: NULL PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveUmtsCkIkFromEpsHo_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 编码KDF算法需要的参数 */

    /* encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_UMTS_CKIK_HO_FC;

    /* encode DL_NASCOUNT&Len */

    /*编码DL_NASCOUNT为P0*/
    NAS_SECU_SET_32BIT_PARA(&(aucAlgParam[ulIndex]), NAS_EMM_GetSecuDlNasCount());
    ulIndex += NAS_EMM_SECU_NASCOUNT_LEN;

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NASCOUNT_LEN;

    /* encode Kasme*/
    pucEpsKasme = NAS_EMM_GetSecuCurKasmeAddr();

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                        pucEpsKasme,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,aucUmtsCKIK);

    if (NAS_EMM_SECU_SUCC == ulRslt)
    {
        /* UmtsCK*/
        NAS_LMM_MEM_CPY_S(pucUmtsCK, NAS_UMTS_CK_LENGTH, aucUmtsCKIK, NAS_UMTS_CK_LENGTH);

        /* UmtsIK*/
        NAS_LMM_MEM_CPY_S(pucUmtsIk, NAS_UMTS_IK_LENGTH, &(aucUmtsCKIK[NAS_UMTS_CK_LENGTH]), NAS_UMTS_IK_LENGTH);

        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        return NAS_EMM_SECU_FAIL;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc
 Description     : 从 L 模切换到 G/U 模，产生UMTS安全上下文的CK,IK
                   reference:33401-960 A.12
                 -   FC = 0x1A
                 -   P0 = NAS downlink COUNT value
                 -   L0 = length of NAS downlink COUNT value (i.e. 0x00 0x04)
                 The input key shall be KASME.

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-10-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc( VOS_UINT8 *pucUmtsCK,
                                                            VOS_UINT8 *pucUmtsIk)
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                       aucUmtsCKIK[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT8                      *pucEpsKasme = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if ((VOS_NULL_PTR == pucUmtsCK)||(VOS_NULL_PTR == pucUmtsIk))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc: NULL PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveUmtsCkIkFromEpsSrvcc_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 编码KDF算法需要的参数 */

    /* encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_UMTS_CKIK_SRVCC_FC;

    /* encode DL_NASCOUNT&Len */

    /*编码DL_NASCOUNT为P0*/
    NAS_SECU_SET_32BIT_PARA(&(aucAlgParam[ulIndex]), NAS_EMM_GetSecuDlNasCount());
    ulIndex += NAS_EMM_SECU_NASCOUNT_LEN;

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NASCOUNT_LEN;

    /* encode Kasme*/
    pucEpsKasme = NAS_EMM_GetSecuCurKasmeAddr();

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                        pucEpsKasme,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,aucUmtsCKIK);

    if (NAS_EMM_SECU_SUCC == ulRslt)
    {
        /* UmtsCK*/
        NAS_LMM_MEM_CPY_S(pucUmtsCK, NAS_UMTS_CK_LENGTH, aucUmtsCKIK, NAS_UMTS_CK_LENGTH);

        /* UmtsIK*/
        NAS_LMM_MEM_CPY_S(pucUmtsIk, NAS_UMTS_IK_LENGTH, &(aucUmtsCKIK[NAS_UMTS_CK_LENGTH]), NAS_UMTS_IK_LENGTH);

        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        return NAS_EMM_SECU_FAIL;
    }

}


/*****************************************************************************
 Function Name   : NAS_EMM_DeriveNasToken
 Description     : 计算NAS TOKEN 33401 A.9
                 -   FC = 0x17
                 -   P0 = Uplink NAS COUNT
                 -   L0 = length of uplink NAS COUNT (i.e. 0x00 0x04)
                 The input key shall be the 256-bit KASME.

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DeriveNasToken( VOS_UINT8 *pucNasToken )
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                      *pucEpsKasme = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveNasToken entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveNasToken_ENUM,LNAS_ENTRY);

    /* 空指针检查*/
    if (VOS_NULL_PTR == pucNasToken)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveNasToken: NULL PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveNasToken_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 编码KDF算法需要的参数 */

    /* encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_NAS_TOKEN_FC;

    /* encode UP_NASCOUNT&Len */

    /*编码UP_NASCOUNT为P0*/
    NAS_SECU_SET_32BIT_PARA(&(aucAlgParam[ulIndex]), NAS_EMM_GetSecuUlNasCount());
    ulIndex += NAS_EMM_SECU_NASCOUNT_LEN;

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_NASCOUNT_LEN;

    /* encode Kasme*/
    pucEpsKasme = NAS_EMM_GetSecuCurKasmeAddr();

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                        pucEpsKasme,
                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,pucNasToken);

    return ulRslt;

}

/*****************************************************************************
 Function Name   : NAS_EMM_KDF_HmacSha256
 Description     : 调用HMAC-SHA-256算法进行密钥派生
 Input           : VOS_UINT8 *pucBuf   :输入的数据
                   VOS_UINT32 ulBuflen :输入的数据长度
                   VOS_UINT8 *pucKey   :输入的密钥
                   VOS_UINT8 aucDigest[MAX_HMAC_HASH_SIZE]:最终生成的256bit密钥
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-06-24  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_KDF_HmacSha256
(
    VOS_UINT8 *pucBuf,
    VOS_UINT32 ulBuflen,
    VOS_UINT8 *pucKey,
    VOS_UINT8 aucDigest[NAS_LMM_SECU_AUTH_KEY_ASME_LEN]
)
{
    KEY_CONFIG_INFO_S                   stKeyCfgInfo;
    S_CONFIG_INFO_S                     stSCfgInfo;
    VOS_INT32                             lRslt;
    KEY_MAKE_S                          stKeyMake;
    CIPHER_KEY_LEN_E                ulenKeyLen;
    NAS_LMM_BSP_INPUT_PARA_STRU         stBspInputPara;
    NAS_LMM_BSP_OUTPUT_PARA_STRU        stBspOutputPara;

    NAS_LMM_MEM_SET_S(  &stBspInputPara,
                        sizeof(NAS_LMM_BSP_INPUT_PARA_STRU),
                        0,
                        sizeof(NAS_LMM_BSP_INPUT_PARA_STRU));
    NAS_LMM_MEM_SET_S(  &stBspOutputPara,
                        sizeof(NAS_LMM_BSP_OUTPUT_PARA_STRU),
                        0,
                        sizeof(NAS_LMM_BSP_OUTPUT_PARA_STRU));

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_KDF_HmacSha256 entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_ENTRY);

    (void)aucDigest;
    if ((NAS_EMM_NULL_PTR == pucBuf) ||
        (NAS_EMM_NULL_PTR == pucKey) ||
        (NAS_EMM_NULL_PTR == aucDigest))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_KDF_HmacSha256: Input Para is valid");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_SECU_FAIL;
    }

    NAS_LMM_MEM_SET_S(&stKeyCfgInfo, sizeof(KEY_CONFIG_INFO_S), NAS_EMM_NULL, sizeof(KEY_CONFIG_INFO_S));
    NAS_LMM_MEM_SET_S(&stSCfgInfo, sizeof(S_CONFIG_INFO_S), NAS_EMM_NULL, sizeof(S_CONFIG_INFO_S));

    /*赋值KEY 参数信息*/
    stKeyCfgInfo.enShaKeySource         = SHA_KEY_SOURCE_DDR;
    stKeyCfgInfo.u32ShaKeyIndex         = NAS_EMM_NULL;
    stKeyCfgInfo.pKeySourceAddr         = pucKey;

    /*赋值S 参数信息*/
    stSCfgInfo.enShaSSource             = SHA_S_SOURCE_DDR;
    stSCfgInfo.u32ShaSIndex             = NAS_EMM_NULL;
    stSCfgInfo.u32ShaSLength            = ulBuflen;
    stSCfgInfo.pSAddr                   = pucBuf;

    /* 输出密钥的结构准备 */
    stKeyMake.enKeyOutput               = CIPHER_KEY_OUTPUT;
    stKeyMake.stKeyGet.enKeyLen         = CIPHER_KEY_L256;
    stKeyMake.stKeyGet.pKeyAddr         = aucDigest;    /* 密钥码流的输出地址 */
    stKeyMake.stKeyGet.penOutKeyLen     = &ulenKeyLen;  /* 密钥长度的输出地址 */

    /*PC回放功能所需的参数*/
    stBspInputPara.ulBuflen = ulBuflen;
    NAS_LMM_MEM_CPY_S(                  stBspInputPara.aucAlgParam,
                                        NAS_EMM_SECU_MAX_ALG_PARAM_LEN,
                                        pucBuf,
                                        ulBuflen);
    NAS_LMM_MEM_CPY_S(                  stBspInputPara.aucKeyParam,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        pucKey,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);



    TLPS_PRINT2LAYER_INFO1(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL1,stSCfgInfo.pSAddr);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL2,stKeyCfgInfo.pKeySourceAddr);

    NAS_EMM_SECU_LOG1_INFO("hard input s len:",stSCfgInfo.u32ShaSLength);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL3,stSCfgInfo.u32ShaSLength);
    NAS_EMM_SECU_LOG_INFO("hard input s:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL4);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                        stSCfgInfo.pSAddr ,
                                        stSCfgInfo.u32ShaSLength);
    NAS_EMM_SECU_LOG_INFO("hard input key:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL5);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                        stKeyCfgInfo.pKeySourceAddr ,
                                        32);
    #ifndef __PS_WIN32_RECUR__
    /*lint -e64*/
    lRslt = LDRV_CIPHER_GEN_KEY(            &stKeyCfgInfo,
                                        &stSCfgInfo,
                                        LTE_SECU_LMM_KDF_OUTPUT_INDEX,
                                        &stKeyMake);
    /*lint +e64*/
    if (VOS_OK == lRslt)
    {
        NAS_EMM_SECU_LOG2_INFO("NAS_EMM_KDF_HmacSha256:  enKeyOutput = , enKeyLen = ",
                                        stKeyMake.enKeyOutput,
                                        stKeyMake.stKeyGet.enKeyLen);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL6,
                                        stKeyMake.enKeyOutput,
                                        stKeyMake.stKeyGet.enKeyLen);

        NAS_EMM_SECU_LOG2_INFO("NAS_EMM_KDF_HmacSha256:  pKeyAddr = , penOutKeyLen = ",
                                        stKeyMake.stKeyGet.pKeyAddr,
                                        stKeyMake.stKeyGet.penOutKeyLen);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL7,
                                        stKeyMake.stKeyGet.pKeyAddr,
                                        stKeyMake.stKeyGet.penOutKeyLen);

        NAS_EMM_SECU_LOG1_INFO("NAS_EMM_KDF_HmacSha256: from LDRV_CIPHER_GEN_KEY, KeyLen = , key = ",
                                        ulenKeyLen);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL8,
                                        ulenKeyLen);
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                                        aucDigest,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);


        NAS_LMM_LogBspKdfKeyMake(&stBspInputPara,&stBspOutputPara,lRslt);
        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        NAS_EMM_SECU_LOG1_INFO("NAS_EMM_KDF_HmacSha256: from LDRV_CIPHER_GEN_KEY, err! lRslt = ",
                                        lRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_KDF_HmacSha256_ENUM,LNAS_FUNCTION_LABEL9,
                                        lRslt);
        NAS_LMM_LogBspKdfKeyMake(&stBspInputPara,&stBspOutputPara,lRslt);
        return NAS_EMM_SECU_FAIL;
    }
    #else

    lRslt = Stub_BSP_KDF_KeyMake(stBspInputPara, &stBspOutputPara);
    if (VOS_OK == lRslt)
    {
        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        return NAS_EMM_SECU_FAIL;
    }

    #endif

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSetInterRatHoNotMapped
 Description     : 其他模块调用该函数清除Mapped安全上下文标志
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-9-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuSetInterRatHoNotMapped( VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSetInterRatHoNotMapped entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSetInterRatHoNotMapped_ENUM,LNAS_ENTRY);
    NAS_EMM_SetFlagInterRatHoMapped(NAS_EMM_SECU_INTER_RAT_HO_NOT_MAPPED);
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuCurrentContextUpNasCountBack
 Description     : 上行NAS COUNT回退，主要用于空口消息发送失败的场景
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2012-10-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SecuCurrentContextUpNasCountBack(VOS_VOID)
{
    if(NAS_EMM_SMC_OPEN == g_ulSmcControl)
    {
        if((EMM_CUR_SECU_EXIST_ACTIVE == NAS_LMM_GetSecuCurFsmCS())
            || (EMM_CUR_SECU_EXIST_NOT_ACTIVE == NAS_LMM_GetSecuCurFsmCS()))
        {
            if(0 < NAS_EMM_GetSecuUlNasCount())
            {
                NAS_EMM_GetSecuUlNasCount()--;
            }

        }
    }

    return;
}
/*lint +e961*/
/*lint +e960*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

