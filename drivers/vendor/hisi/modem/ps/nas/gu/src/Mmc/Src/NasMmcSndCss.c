
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "CssInterface.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmcSndCss.h"
#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasMmcComFunc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_CSS_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID  NAS_MMC_SndCssMultiBandScanReq(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU        *pstMultiBandScanReq
)
{
    CSS_MULTI_BAND_SCAN_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_MULTI_BAND_SCAN_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(CSS_MULTI_BAND_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCssMultiBandScanReq: memery alloc failed.");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_CSS,
                        ID_CSS_MULTI_BAND_SCAN_REQ,
                        sizeof(CSS_MULTI_BAND_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息内容 */
    pstMsg->ulOpid                      = 0;
    pstMsg->enBandScanType              = pstMultiBandScanReq->enBandScanType;

    if (VOS_TRUE == pstMultiBandScanReq->bitOpMcc)
    {
        pstMsg->bitOpMcc                = VOS_TRUE;
        pstMsg->aucMcc[0]               = pstMultiBandScanReq->aucMcc[0];
        pstMsg->aucMcc[1]               = pstMultiBandScanReq->aucMcc[1];
    }

    pstMsg->bitOpHighRssi               = pstMultiBandScanReq->bitOpHighRssi;

    PS_MEM_CPY(&pstMsg->stRatList, &pstMultiBandScanReq->stRatList, sizeof(CSS_RAT_LIST));

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndCssStopBandScanReq(VOS_VOID)
{
    CSS_STOP_BAND_SCAN_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_STOP_BAND_SCAN_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(CSS_STOP_BAND_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCssStopBandScanReq: memery alloc failed.");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_CSS,
                        ID_CSS_STOP_BAND_SCAN_REQ,
                        sizeof(CSS_STOP_BAND_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息内容 */

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndCssCurrGeoInd(
    VOS_UINT32                          ulIsPowerOn,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstGeoPlmn
)
{
    CSS_CURR_GEO_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* 异常检查 */
    if ((0 == ulPlmnNum)
     || (VOS_NULL_PTR == pstGeoPlmn))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCssCurrGeoInd: plmn num error or plmn list null.");



        return;
    }

    pstMsg = (CSS_CURR_GEO_IND_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(CSS_CURR_GEO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCssCurrGeoInd: memery alloc failed.");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_CSS,
                        ID_CSS_CURR_GEO_IND,
                        sizeof(CSS_CURR_GEO_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 填充消息内容 */
    pstMsg->ulIsPowerOn = ulIsPowerOn;

    if (ulPlmnNum > CSS_MAX_PLMN_ID_NUM)
    {
        ulPlmnNum = CSS_MAX_PLMN_ID_NUM;
    }

    pstMsg->ulPlmnNum   = ulPlmnNum;

    PS_MEM_CPY(pstMsg->astPlmnId, pstGeoPlmn, ulPlmnNum * sizeof(CSS_PLMN_ID_STRU));

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

