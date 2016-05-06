/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluProcNvim.c
  版 本 号   : 初稿
  作    者   : n00742771
  生成日期   : 2015年02月05日
  最近修改   :
  功能描述   : HLU消息处理主文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : n00742771
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NVIM_Interface.h"
#include "NasNvInterface.h"
#include "CnasHluComm.h"
#include "CnasHluProcNvim.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_HLU_ReadLocInfoNvim(VOS_VOID)
{
    CNAS_HLU_LOC_STRU                  *pstLocCtx;
    CNAS_NVIM_HRPD_LOC_INFO_STRU        stNvLocInfo;

    NAS_MEM_SET_S(&stNvLocInfo, sizeof(stNvLocInfo), 0x00, sizeof(CNAS_NVIM_HRPD_LOC_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_HRPD_LOC_INFO,
                         &stNvLocInfo, sizeof(CNAS_NVIM_HRPD_LOC_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_ReadLocInfoNvim:Read Nvim Failed");
        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_HRPD_LOC_INFO,
                            sizeof(CNAS_NVIM_HRPD_LOC_INFO_STRU),
                            UEPS_PID_HLU,
                            (VOS_UINT8 *)&stNvLocInfo);

    if (CNAS_HLU_IS_EQUAL(VOS_TRUE, stNvLocInfo.ulIsValid))
    {
        pstLocCtx = &(CNAS_HLU_GetLocCtxAddr()->stLocCtx);

        pstLocCtx->ucLocType               = stNvLocInfo.ucLocType;
        pstLocCtx->ucLocLen                = stNvLocInfo.ucLocLen;
        pstLocCtx->stLocVal.usSID          = stNvLocInfo.usSID;
        pstLocCtx->stLocVal.usNID          = stNvLocInfo.usNID;
        pstLocCtx->stLocVal.ucPacketZoneID = stNvLocInfo.ucPacketZoneID;
    }

    return;
}



VOS_VOID CNAS_HLU_WriteLocInfoNvim(VOS_VOID)
{
    CNAS_HLU_LOC_STRU                  *pstLocCtx;
    CNAS_NVIM_HRPD_LOC_INFO_STRU        stNvLocInfo;

    NAS_MEM_SET_S(&stNvLocInfo, sizeof(stNvLocInfo), 0x00, sizeof(CNAS_NVIM_HRPD_LOC_INFO_STRU));

    /* Get HLU LocCtx address */
    pstLocCtx = &(CNAS_HLU_GetLocCtxAddr()->stLocCtx);

    /* Take currently stored LocationValue from HLU LocCtx */
    stNvLocInfo.ulIsValid      = VOS_TRUE;
    stNvLocInfo.ucLocType      = pstLocCtx->ucLocType;
    stNvLocInfo.ucLocLen       = pstLocCtx->ucLocLen;
    stNvLocInfo.usSID          = pstLocCtx->stLocVal.usSID;
    stNvLocInfo.usNID          = pstLocCtx->stLocVal.usNID;
    stNvLocInfo.ucPacketZoneID = pstLocCtx->stLocVal.ucPacketZoneID;

    if (NV_OK != NV_Write(en_NV_Item_HRPD_LOC_INFO,
                         &stNvLocInfo, sizeof(CNAS_NVIM_HRPD_LOC_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_HLU_WriteLocInfoNvim:Write Nvim Failed");
        return;
    }

    return;
}



VOS_VOID CNAS_HLU_ReadStrgBlobNvim(VOS_VOID)
{
    CNAS_HLU_BLOB_STRU                 *pstStrgBlobCtx;
    CNAS_NVIM_HRPD_STORAGE_BLOB_STRU    stNvStrgBlob;

    NAS_MEM_SET_S(&stNvStrgBlob, sizeof(stNvStrgBlob), 0x00, sizeof(CNAS_NVIM_HRPD_STORAGE_BLOB_STRU));

    if (NV_OK != NV_Read(en_NV_Item_HRPD_STORAGE_BLOB,
                         &stNvStrgBlob, sizeof(CNAS_NVIM_HRPD_STORAGE_BLOB_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_ReadStrgBlobNvim:Read Nvim Failed");
        return;
    }


    if (VOS_TRUE == stNvStrgBlob.ulIsValid)
    {
        pstStrgBlobCtx = &(CNAS_HLU_GetLocCtxAddr()->stBLOBCtx);

        pstStrgBlobCtx->usStrgBLOBtype = stNvStrgBlob.usStrgBLOBType;
        pstStrgBlobCtx->ucStrgBLOBLen  = stNvStrgBlob.ucStrgBLOBLen;

        NAS_MEM_CPY_S(pstStrgBlobCtx->aucStorageBLOB,
                      sizeof(pstStrgBlobCtx->aucStorageBLOB),
                      stNvStrgBlob.aucStorageBLOB,
                      stNvStrgBlob.ucStrgBLOBLen);
    }

    return;
}



VOS_VOID CNAS_HLU_WriteStrgBlobNvim(VOS_VOID)
{
    CNAS_HLU_BLOB_STRU                 *pstStrgBlobCtx;
    CNAS_NVIM_HRPD_STORAGE_BLOB_STRU    stNvStrgBlob;

    NAS_MEM_SET_S(&stNvStrgBlob, sizeof(stNvStrgBlob), 0x00, sizeof(CNAS_NVIM_HRPD_STORAGE_BLOB_STRU));

    /* Get HLU LocCtx address */
    pstStrgBlobCtx = &(CNAS_HLU_GetLocCtxAddr()->stBLOBCtx);

    /* Take currently stored StorageBLOB from HLU LocCtx */
    stNvStrgBlob.ulIsValid      = VOS_TRUE;
    stNvStrgBlob.usStrgBLOBType = pstStrgBlobCtx->usStrgBLOBtype;
    stNvStrgBlob.ucStrgBLOBLen  = pstStrgBlobCtx->ucStrgBLOBLen;

    NAS_MEM_CPY_S(stNvStrgBlob.aucStorageBLOB,
                  sizeof(stNvStrgBlob.aucStorageBLOB),
                  pstStrgBlobCtx->aucStorageBLOB,
                  pstStrgBlobCtx->ucStrgBLOBLen);

    if (NV_OK != NV_Write(en_NV_Item_HRPD_STORAGE_BLOB,
                         &stNvStrgBlob, sizeof(CNAS_NVIM_HRPD_STORAGE_BLOB_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_HLU_WriteStrgBlobNvim:Write Nvim Failed");
        return;
    }

    return;
}



/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
