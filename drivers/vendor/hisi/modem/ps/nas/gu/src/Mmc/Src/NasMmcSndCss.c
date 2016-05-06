/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndCss.c
  版 本 号   : 初稿
  作    者   : sunjitan 00193151
  生成日期   : 2015年05月08日
  最近修改   :
  功能描述   : MMC发给CSS的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月08日
    作    者   : sunjitan 00193151
    修改内容   : 创建文件

******************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndCssMultiBandScanReq
 功能描述  : 发送消息ID_CSS_MULTI_BAND_SCAN_REQ
 输入参数  : CSS_MULTI_BAND_SCAN_REQ_STRU*
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月08日
    作    者   : sunjitan 00193151
    修改内容   : 新生成函数
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndCssStopBandScanReq
 功能描述  : 发送消息ID_CSS_STOP_BAND_SCAN_REQ
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月08日
    作    者   : sunjitan 00193151
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndCssCurrGeoInd
 功能描述  : 通知CSS ID_CSS_CURR_GEO_IND
 输入参数  : NAS_MML_PLMN_ID_STRU               *pstGetGeoPlmn
             VOS_UINT32                          ulModemState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年12月12日
    作    者   : s00217060
    修改内容   : DTS2015120901555:异常检查时还未分配消息内存，不用释放

*****************************************************************************/
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

