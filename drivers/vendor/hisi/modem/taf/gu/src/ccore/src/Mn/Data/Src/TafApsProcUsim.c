

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsProcUsim.h"
#include  "NasUsimmApi.h"
#include  "TafSdcCtx.h"
#include  "TafApsComFunc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PROC_USIM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_APS_GetWaitSimFilesCnfFlg(VOS_VOID)
{
    return TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg;
}


VOS_VOID  TAF_APS_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
)
{
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enRead3GpdFileFlag;

    enRead3GpdFileFlag = TAF_APS_Map3GpdFileIdAndFlag(usEfId);

    TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg &= ~enRead3GpdFileFlag;
    return;
}


VOS_VOID    TAF_APS_SetWaitSimFilesCnfFlg(
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
)
{
    TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg |= enSimFileCnfFlg;
}


VOS_UINT32 TAF_APS_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                    enAppType,
                    usEfId,
                    0);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    return ulRet;

}


VOS_VOID TAF_APS_Read3GdpFile( VOS_VOID )
{
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;

    enCsimType                          = TAF_SDC_GetCsimType();

    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        return;
    }

    if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPCAP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPCAP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPUPP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPUPP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPSP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPSP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPPAPSS_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPPAPSS_ID_FLG);
    }

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPCAP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPCAP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPUPP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPUPP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPSP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPSP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPPAPSS_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPPAPSS_ID_FLG);

    }

    return;
}

#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
