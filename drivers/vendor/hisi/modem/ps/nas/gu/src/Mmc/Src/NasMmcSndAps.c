/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndAps.c
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2010年12月19日
  最近修改   :
  功能描述   : MMC发给APS的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月19日
    作    者   : h44270
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MmcApsInterface.h"
#include "NasMmlCtx.h"
#include "NasMmcSndAps.h"
#include "PsCommonDef.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_APS_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_ConverMmlRatTypeToAps
 功能描述  : 将MML子层定义的接入技术转换成APS定义的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
MMC_APS_RAT_TYPE_ENUM_UINT32 NAS_MMC_ConverMmlRatTypeToAps(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            return MMC_APS_RAT_TYPE_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            return MMC_APS_RAT_TYPE_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
            return MMC_APS_RAT_TYPE_LTE;

        default:
            return MMC_APS_RAT_TYPE_NULL;

    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndApsServiceStatusInd
 功能描述  : 发送消息MMC_APS_SERVICE_STATUS_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndApsServiceStatusInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType,
    VOS_UINT8                                   ucSimPsRegStatus
)
{
    MMC_APS_SERVICE_STATUS_IND_STRU            *pstMsg = VOS_NULL_PTR;


    pstMsg = (MMC_APS_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMC,
                        sizeof(MMC_APS_SERVICE_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: memery alloc failed.");

        return;
    }

    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMC_APS_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMC_APS_SERVICE_STATUS_IND;

    pstMsg->enRatType                   = NAS_MMC_ConverMmlRatTypeToAps(enRatType);

    pstMsg->ulPsSimRegStatus            = ucSimPsRegStatus;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: send message failed.");
    }

    return;
}
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

