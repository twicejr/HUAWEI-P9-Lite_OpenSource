

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXccProcNvim.h"
#include  "CnasXccCtx.h"
#include  "NVIM_Interface.h"
#include  "CnasMntn.h"
#include  "NasNvInterface.h"
#include  "NasMntn.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_COM_FUNC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID CNAS_XCC_ReadCallCfgNvim()
{
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_CALL_NVIM_CFG_STRU     stCallNvimCfg;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    NAS_MEM_SET_S(&stCallNvimCfg, sizeof(stCallNvimCfg), 0x0, sizeof(stCallNvimCfg));

    if (NV_OK != NV_Read(en_NV_Item_1X_CALL_CFG,
                         &stCallNvimCfg, sizeof(stCallNvimCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ReadCallCfgNvim:Read Nvim Failed");

        pstCallNvimCfg->ucIsL3ErrReOrigCount = VOS_FALSE;

        pstCallNvimCfg->ucPrivacyMode        = VOS_FALSE;
        return;
    }

    pstCallNvimCfg->ucIsL3ErrReOrigCount = stCallNvimCfg.ucIsL3ErrReOrigCount;

    pstCallNvimCfg->ucPrivacyMode        = stCallNvimCfg.ucPrivacyMode;
}


VOS_UINT32 CNAS_XCC_WritePrivacyModeNvim(VOS_UINT8 ucPrivacyMode)
{
    CNAS_NVIM_1X_CALL_NVIM_CFG_STRU     stCallNvimCfg;

    NAS_MEM_SET_S(&stCallNvimCfg, sizeof(stCallNvimCfg), 0x0, sizeof(stCallNvimCfg));

    /* 更新privacy mode */
    stCallNvimCfg.ucPrivacyMode = ucPrivacyMode;

    if (NV_OK != NV_Write(en_NV_Item_1X_CALL_CFG,
                          &stCallNvimCfg,
                          sizeof(stCallNvimCfg)))
    {
        NAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_WritePrivacyModeNvim: Write Nvim Failed");

        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID CNAS_XCC_Read1xPagingRspSoCfg(VOS_VOID)
{
    CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU                     *pstPagingRspSoCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU                     stNvPagingRspSoCfg;

    pstPagingRspSoCfg      = &(CNAS_XCC_GetCtxAddr()->stPagingRspSoCfg);

    NAS_MEM_SET_S(&stNvPagingRspSoCfg, sizeof(CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU), 0x0, sizeof(CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_1X_PAGING_RSP_SO_CFG,
                         &stNvPagingRspSoCfg, sizeof(stNvPagingRspSoCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_Read1xPagingRspSoCfg:Read Nvim Failed");

        pstPagingRspSoCfg->ucNoDataSrvRspSo33Flg = VOS_FALSE;
        return;
    }

    pstPagingRspSoCfg->ucNoDataSrvRspSo33Flg = stNvPagingRspSoCfg.ucNoDataSrvRspSo33;

}


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

VOS_VOID CNAS_XCC_ReadVoiceEncryptCapCfgPara(VOS_VOID)
{
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU        stNvimEccSrvCapInfo;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);
    NAS_MEM_SET_S(&stNvimEccSrvCapInfo, sizeof(CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU), 0x00, sizeof(CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO,
                         &stNvimEccSrvCapInfo,
                         sizeof(CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU)))
    {
        pstCallNvimCfg->ucEccSrvCap     = VOS_FALSE;
        pstCallNvimCfg->ucEccSrvStatus  = VOS_FALSE;

        CNAS_ERROR_LOG(UEPS_PID_XCC,
                       "CNAS_XCC_ReadVoiceEncryptCapCfgPara():Read en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO Error");
        return;
    }

    /* 服务能力读取数值检查 */
    if (VOS_FALSE != stNvimEccSrvCapInfo.ucEccSrvCap)
    {
        stNvimEccSrvCapInfo.ucEccSrvCap     = VOS_TRUE;
    }

    /* 服务状态读取数值检查 */
    if (VOS_FALSE != stNvimEccSrvCapInfo.ucEccSrvStatus)
    {
        stNvimEccSrvCapInfo.ucEccSrvStatus  = VOS_TRUE;
    }

    pstCallNvimCfg->ucEccSrvCap         = stNvimEccSrvCapInfo.ucEccSrvCap;
    pstCallNvimCfg->ucEccSrvStatus      = stNvimEccSrvCapInfo.ucEccSrvStatus;
}
#endif

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




