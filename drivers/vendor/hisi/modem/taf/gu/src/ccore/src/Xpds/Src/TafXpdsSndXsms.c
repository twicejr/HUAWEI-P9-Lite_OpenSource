/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsSndAt.c
  版 本 号   : 初稿
  作    者   : c00299064
  生成日期   : 2015年08月25日
  功能描述   : 发送消息给AT模块的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月25日
    作    者   : c00299064
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsSndXsms.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXpdsMntn.h"
#include "TafSdcCtx.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_SND_XSMS_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XPDS_FillXsmsMpcRejPosReqStru
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_SndXsmsDataReq(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr
)
{
    TAF_XPDS_XSMS_SEND_REQ_STRU        *pstSendReq;

    pstSendReq = (TAF_XPDS_XSMS_SEND_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_XPDS,
                    sizeof(TAF_XPDS_XSMS_SEND_REQ_STRU) + ulDataLen - 4 - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSendReq)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SendXsmsDataReq: Alloc msg fail!");
        return;
    }

    pstSendReq->ulReceiverPid   = UEPS_PID_XSMS;
    pstSendReq->ulReceiverCpuId = VOS_LOCAL_CPUID;

    pstSendReq->enMsgName       = ID_XPDS_XSMS_SEND_REQ;
    pstSendReq->usOpId          = 0;
    pstSendReq->usDataLen       = (VOS_UINT16)ulDataLen;

    /* 填写地址信息 */
    PS_MEM_CPY(&pstSendReq->stXsmsAddr, pstXsmsAddr, sizeof(TAF_XSMS_ADDR_STRU));

    /* 填写数据 */
    PS_MEM_CPY(pstSendReq->aucData, pucData, pstSendReq->usDataLen);

    PS_SEND_MSG(UEPS_PID_XPDS, pstSendReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SendXsmsRejNiPosReq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_SndXsmsRejNiPosReq(
    TAF_XPDS_REJ_POS_REASON_ENUM_UINT8  enRejReason
)
{
    VOS_UINT32                          ulDataLen   = 0;
    TAF_XPDS_XSMS_REJ_POS_REQ_STRU      stRejPosReq;
    VOS_UINT8                           aucData[50] = {0};

    PS_MEM_SET(&stRejPosReq, 0, sizeof(TAF_XPDS_XSMS_REJ_POS_REQ_STRU));

    /* 填写REJ_POS_REQ */
    stRejPosReq.enRejReason = enRejReason;

    TAF_XPDS_FillXsmsMpcRejPosReqStru(&stRejPosReq);

    /* 编码REJ_POS_REJ */
    TAF_XPDS_EncodeXsmsMpcRejPosReq(&stRejPosReq,
                                    &ulDataLen,
                                     aucData);

    TAF_XPDS_SndXsmsDataReq(ulDataLen,
                            aucData,
                            &(TAF_XPDS_GetMpcCtxAddr()->stXsmsAddr));

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SendXsmsCancelPosNotify
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_SndXsmsCancelPosNotify(
    TAF_XPDS_CANCEL_REASON_ENUM_UINT8   enCancelReason
)
{
    VOS_UINT32                                              ulDataLen   = 0;
    TAF_XPDS_XSMS_CANCEL_POS_NOTIFICATION_STRU              stCancelNotify;
    VOS_UINT8                                               aucData[50] = {0};

    PS_MEM_SET(&stCancelNotify, 0, sizeof(TAF_XPDS_XSMS_CANCEL_POS_NOTIFICATION_STRU));

    /* 填写CANCEL IND */
    stCancelNotify.ucVersion        = TAF_XPDS_CUR_VERSION;
    stCancelNotify.ucMsgType        = 0X02;
    stCancelNotify.ucCorrlationId   = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId;
    stCancelNotify.enCancelReason   = enCancelReason;


    /* 编码REJ_POS_REJ */
    TAF_XPDS_EncodeXsmsMpcCancelPosNotifty(&stCancelNotify,
                                           &ulDataLen,
                                           aucData);

    TAF_XPDS_SndXsmsDataReq(ulDataLen,
                            aucData,
                            &(TAF_XPDS_GetMpcCtxAddr()->stXsmsAddr));

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_FillXsmsMpcRejPosReqStru
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月18日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_FillXsmsMpcRejPosReqStru(
    TAF_XPDS_XSMS_REJ_POS_REQ_STRU  *pstRejPosReq
)
{
    pstRejPosReq->ucVersion         = TAF_XPDS_CUR_VERSION;
    pstRejPosReq->ucMsgType         = 0x01;
    pstRejPosReq->ucCorrlationId    = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId;

    pstRejPosReq->usSID             = (VOS_UINT16)TAF_SDC_Get1xSid();

    /* 判断需不需要CELL INFO */
    if (TAF_XPDS_REJ_POS_REASON_TCP_IP_NOT_OPEN == pstRejPosReq->enRejReason)
    {
        pstRejPosReq->ucCellInc     = VOS_TRUE;
        pstRejPosReq->usNID         = (VOS_UINT16)TAF_SDC_Get1xNid();
        pstRejPosReq->usBaseId      = TAF_SDC_Get1xSysInfo()->stBaseStationInfo.usBaseId;
        pstRejPosReq->ulBaseLat     = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLatitude;
        pstRejPosReq->ulBaseLong    = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLongitude;

        TAF_XPDS_SetTimeStamp(&pstRejPosReq->stTimeStamp);

    }
    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

