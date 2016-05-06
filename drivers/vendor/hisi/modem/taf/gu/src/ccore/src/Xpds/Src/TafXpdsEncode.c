/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsEncode.c
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月14日
  最近修改   :
  功能描述   : Modem Encode Msg
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月14日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_ENCODE_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsEncode.h"
#include "UsimPsInterface.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeMpcStartPosReq
 功能描述  : encode mpc start req to array refer(gpsone user plane ms-mpc ch4.2.2.1)
 输入参数  :    pstMpcStartReq:输入

 输出参数  :    *pucData:    目标数组
                *pulDataLen: 得到的长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_EncodeMpcStartPosReq(
    TAF_XPDS_MPC_START_POS_REQ_STRU   *pstMpcStartReq,
    VOS_UINT32                        *pulDataLen,
    VOS_UINT8                         *pucData
)
{
    VOS_UINT32                        ulTotNumOfBits;
    VOS_UINT32                        ulCurrIdx;
    VOS_UINT8                         ucLoopCount;

    ulTotNumOfBits    = 0;

    /* set version and msg type */
    pucData[0] = pstMpcStartReq->ucVersion;
    pucData[1] = pstMpcStartReq->enMsgType;

    ulCurrIdx         = 4;

    /* set Position capability  */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->enMsPosCap, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* application type indicator */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->enAppTypeIndicator, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set PQos */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ucPQoS, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Duration */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ulDuration, 32, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set correlation identifier */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ucCorrelationId, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* TODO - After finalizing MSID_REC Stru change the encode method*/
    for (ucLoopCount = 0; ucLoopCount < 8; ucLoopCount++)
    {

        /* set MSID rec */
        TAF_XPDS_EncodeSetValue(pstMpcStartReq->stMsIdRec.aucMsIdRec[ucLoopCount], 8, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

    }

    /* set SID */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->usSID, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set NID */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->usNID, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Base_ID */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ulBaseID, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Base_LAT */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ulBaseLat, 24, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Base_LONG */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ulBaseLong, 24, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Ref PN */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->usRefPn, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Band class */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->usBandClass, 8, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set CDMA freq */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ulCdmaFreq, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set CDMA time week */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->stTimeStamp.ulWeekNum, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set CDMA time sec */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->stTimeStamp.ulSecNum, 24, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Brew app id  */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->ulBrewAppId, 32, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set app id rec len */
    TAF_XPDS_EncodeSetValue(pstMpcStartReq->stAppIdRec.usAppRecLen, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);


    for (ucLoopCount = 0; ucLoopCount < pstMpcStartReq->stAppIdRec.usAppRecLen; ucLoopCount++)
    {
        /* set app id rec */
        TAF_XPDS_EncodeSetValue(pstMpcStartReq->stAppIdRec.aucAppIdRec[ucLoopCount], 8, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);
    }

    /* set the length */
    pucData[2]  = (VOS_UINT8)(((VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) & 0xFF00) >> 8);
    pucData[3]  = (VOS_UINT8)((VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) & 0x00FF) ;
    *pulDataLen = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 4;

    return ;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeMpcPosReportReq
 功能描述  : encode mpc pos report req to array,reference:gpsone user plane ms-mpc ch4.2.2.1
 输入参数  :    pstMpcStartReq:输入

 输出参数  :    *pucData:    目标数组
                *pulDataLen: 得到的长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_EncodeMpcPosReportReq(
    TAF_XPDS_MPC_POS_REPORT_STRU  *pstMpcPosReportReq,
    VOS_UINT32                    *pulDataLen,
    VOS_UINT8                     *pucData
)
{

    VOS_UINT32                     ulTotNumOfBits;
    VOS_UINT32                     ulCurrIdx;
    VOS_UINT8                      ucLoopCount;

    ulTotNumOfBits    = 0;

    /* set version and msg type */
    pucData[0] = pstMpcPosReportReq->ucVersion;
    pucData[1] = pstMpcPosReportReq->enMsgType;

    ulCurrIdx         = 4;

    /* set Fix number */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usFixNum, 16, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set corelation id */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usCorrelationId, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);


    /* TODO - After finalizing MSID_REC Stru change the encode method*/
    for (ucLoopCount = 0; ucLoopCount < 8; ucLoopCount++)
    {

        /* set MSID rec */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->stMsIdRec.aucMsIdRec[ucLoopCount], 8, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

    }

    /* set time week */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->stCellIdTimeStamp.ulWeekNum, 16, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set time sec */
     TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->stCellIdTimeStamp.ulSecNum, 24, &ulTotNumOfBits,
                                     &pucData[ulCurrIdx], &ulCurrIdx);

    /* set SID */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usSID, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set NID */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usNID, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Base_ID */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ulBaseID, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Base_LAT */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ulBaseLat, 24, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Base_LONG */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ulBaseLong, 24, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Ref PN */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usRefPn, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Band class */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usBandClass, 8, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set CDMA freq */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ulCdmaFreq, 16, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    /* set Position include flag */
    TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ulPosIncFlag, 8, &ulTotNumOfBits,
                                &pucData[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstMpcPosReportReq->ulPosIncFlag)
    {

        /* set Position time stamp week */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->stPosTimeStamp.ulWeekNum, 16, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set position time stamp sec */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->stPosTimeStamp.ulSecNum, 24, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set latitude */
        TAF_XPDS_EncodeSetValue((VOS_UINT32)pstMpcPosReportReq->lLat, 25, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set longitude */
        TAF_XPDS_EncodeSetValue((VOS_UINT32)pstMpcPosReportReq->lLong, 26, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set location uncertainity ang */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ucLocUncrtntyAng, 4, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set location uncertainity ang a */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ucLocUncrtntyA, 5, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set location uncertainity ang p */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ucLocUncrtntyP, 5, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set velocity inc flag */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->ucVelocityIncl, 1, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        if (VOS_TRUE == pstMpcPosReportReq->ucVelocityIncl)
        {
            /* set horizondal velocity */
            TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usVelocityHor, 9, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

            /* set heading */
            TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usHeading, 10, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

            /* set heading */
            TAF_XPDS_EncodeSetValue((VOS_UINT32)(VOS_UINT16)pstMpcPosReportReq->sVelocityVer, 8, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        }

        /* set height inc flag */
        TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usHeihtIncl, 1, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        if (VOS_TRUE == pstMpcPosReportReq->usHeihtIncl)
        {
            /* set height */
            TAF_XPDS_EncodeSetValue((VOS_UINT32)(VOS_UINT16)pstMpcPosReportReq->sHeiht, 14, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

            /* set uncertainity V */
            TAF_XPDS_EncodeSetValue(pstMpcPosReportReq->usLocUncrtntyV, 5, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        }

    }

    /* set the length */
    pucData[2]  = (VOS_UINT8)(((VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) & 0xFF00) >> 8);
    pucData[3]  = (VOS_UINT8)((VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) & 0x00FF) ;
    *pulDataLen = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 4;

    return ;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeMpcPosReportReq
 功能描述  : encode mpc pos report req to array,reference:gpsone user plane ms-mpc ch4.2.2.1
 输入参数  :    pstMpcStartReq:输入

 输出参数  :    *pucData:    目标数组
                *pulDataLen: 得到的长度
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_EncodeMpcCancelTrTrackReq(
    TAF_XPDS_MPC_CANCEL_TRACK_STRU    *pstMpcCancelTrack,
    VOS_UINT32                        *pulDataLen,
    VOS_UINT8                         *pucData
)
{

    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    VOS_UINT8                           ucLoopCount;

    ulTotNumOfBits    = 0;

    /* set version and msg type */
    pucData[0]  =   TAF_XPDS_CUR_VERSION;
    pucData[1]  =   ID_TAF_XPDS_MS_TO_MPC_CANCEL_TRACK_SESSION;
    ulCurrIdx   =   4;


    /* set co-relation id  */
    TAF_XPDS_EncodeSetValue((TAF_XPDS_GetCorrelationId()), 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* TODO - After finalizing MSID_REC Stru change the encode method*/
    for (ucLoopCount = 0; ucLoopCount < 8; ucLoopCount++)
    {

        /* set MSID rec */
        TAF_XPDS_EncodeSetValue(pstMpcCancelTrack->stMsIdRec.aucMsIdRec[ucLoopCount], 8, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

    }

    /* set the length */
    pucData[2]  = (VOS_UINT8)(((VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) & 0xFF00) >> 8);
    pucData[3]  = (VOS_UINT8)((VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) & 0x00FF) ;
    *pulDataLen = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 4;

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeXsmsMpcRejPosReq
 功能描述  : encode mpc pos report req to array,reference:gpsone user plane ms-mpc ch3.2.1.1
 输入参数  :    pstMpcStartReq:输入

 输出参数  :    *pucData:    目标数组
                *pulDataLen: 得到的长度
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_EncodeXsmsMpcRejPosReq(
    TAF_XPDS_XSMS_REJ_POS_REQ_STRU *pstRejPosReq,
    VOS_UINT32                     *pulDataLen,
    VOS_UINT8                      *pucData
)
{

    VOS_UINT32                      ulTotNumOfBits;
    VOS_UINT32                      ulCurrIdx;

    ulTotNumOfBits    = 0;

    /* set version and msg type */
    pucData[0]  =   pstRejPosReq->ucVersion;
    pucData[1]  =   pstRejPosReq->ucMsgType;
    ulCurrIdx   =   3;


    /* set co-relation id  */
    TAF_XPDS_EncodeSetValue(pstRejPosReq->ucCorrlationId, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);


    /* set reject reason  */
    TAF_XPDS_EncodeSetValue(pstRejPosReq->enRejReason, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set sid  */
    TAF_XPDS_EncodeSetValue(pstRejPosReq->usSID, 16, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);


    /* set cell inc flag  */
    TAF_XPDS_EncodeSetValue(pstRejPosReq->ucCellInc, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);


    if (VOS_TRUE == pstRejPosReq->ucCellInc)
    {
        /* set NID  */
        TAF_XPDS_EncodeSetValue(pstRejPosReq->usNID, 16, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set Base id  */
        TAF_XPDS_EncodeSetValue(pstRejPosReq->usBaseId, 16, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set Base lat  */
        TAF_XPDS_EncodeSetValue(pstRejPosReq->ulBaseLat, 24, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set Base longitude */
        TAF_XPDS_EncodeSetValue(pstRejPosReq->ulBaseLong, 24, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set timestamp week */
        TAF_XPDS_EncodeSetValue(pstRejPosReq->stTimeStamp.ulWeekNum, 16, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

        /* set timestamp sec */
        TAF_XPDS_EncodeSetValue(pstRejPosReq->stTimeStamp.ulSecNum, 24, &ulTotNumOfBits,
                                        &pucData[ulCurrIdx], &ulCurrIdx);

    }

    /* caluculate and set response parameter length */
    pucData[2] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulDataLen = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 3;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeXsmsMpcCancelPosNotifty
 功能描述  : encode mpc pos report req to array,reference:gpsone user plane ms-mpc ch3.2.1.2
 输入参数  :    pstMpcStartReq:输入

 输出参数  :    *pucData:    目标数组
                *pulDataLen: 得到的长度
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_EncodeXsmsMpcCancelPosNotifty(
    TAF_XPDS_XSMS_CANCEL_POS_NOTIFICATION_STRU         *pstCancelNotify,
    VOS_UINT32                                         *pulDataLen,
    VOS_UINT8                                          *pucData
)
{

    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;

    ulTotNumOfBits    = 0;

    /* set version and msg type */
    pucData[0]  =   pstCancelNotify->ucVersion;
    pucData[1]  =   pstCancelNotify->ucMsgType;
    ulCurrIdx   =   3;


    /* set co-relation id  */
    TAF_XPDS_EncodeSetValue(pstCancelNotify->ucCorrlationId, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);

    /* set cancel reason  */
    TAF_XPDS_EncodeSetValue(pstCancelNotify->enCancelReason, 8, &ulTotNumOfBits,
                                    &pucData[ulCurrIdx], &ulCurrIdx);


    /* caluculate and set response parameter length */
    pucData[2] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulDataLen = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 3;

    return VOS_OK;
}



VOS_UINT8 TAF_XPDS_GetMaskValue(
    VOS_UINT8                           ucBitsLeft
)
{
    switch (ucBitsLeft)
    {
        case 1:
            return 0x80;
        case 2:
            return 0xC0;
        case 3:
            return 0xE0;
        case 4:
            return 0xF0;
        case 5:
            return 0xF8;
        case 6:
            return 0xFC;
        case 7:
            return 0xFE;
        default:
            return 0x00;
    }
}


VOS_VOID TAF_XPDS_EncodeSetValue(
    VOS_UINT32                          ulValueToSet,
    VOS_UINT8                           ucNumOfBits,
    VOS_UINT32                         *pulTotalBitsPrc,
    VOS_UINT8                          *pucCurrBuf,
    VOS_UINT32                         *pulCurIdx
)
{

    VOS_UINT8                           ucShiftVal;
    VOS_UINT32                          ulTempVal;
    VOS_UINT32                          ulTempValRightShift;
    VOS_UINT8                           ucMSBPart;
    VOS_UINT8                           ucLSBPart;
    VOS_UINT8                           ucBitsProcessedinMSB;

    ulTempVal        = 0;

    /* caluculate the shift value */
    ucShiftVal       = 32 - ucNumOfBits;

    ucBitsProcessedinMSB    = (*pulTotalBitsPrc) % 8;
    ucLSBPart               = (VOS_UINT8)(ulValueToSet & 0x000000FF);

    /* get the value to set after left shift */
    ulTempVal               = (ulValueToSet << ucShiftVal);

    /* get the value to OR with MSB, and other bytes*/
    ulTempValRightShift     = ulTempVal >> ucBitsProcessedinMSB;

    ucMSBPart               = (VOS_UINT8)((ulTempValRightShift & 0xFF000000) >> 24);

    pucCurrBuf[0]    = (pucCurrBuf[0] | ucMSBPart);
    pucCurrBuf[1]    = (VOS_UINT8)((ulTempValRightShift & 0x00FF0000) >> 16);
    pucCurrBuf[2]    = (VOS_UINT8)((ulTempValRightShift & 0x0000FF00) >> 8);
    pucCurrBuf[3]    = (VOS_UINT8)((ulTempValRightShift & 0x000000FF));

    /* if the value to be set is greter than 3 bytes, appending the lost bits (during right shift)*/
    if (ucNumOfBits > 24)
    {
        if ((ucBitsProcessedinMSB + ucShiftVal) > 8)
        {
            /*lint -e701*/
            pucCurrBuf[4]    = (VOS_UINT8)(ucLSBPart << ((VOS_UINT8)(8UL - (VOS_UINT8)TAF_XPDS_ABS_DIFF(ucBitsProcessedinMSB, ucShiftVal))));
            /*lint +e701*/
        }
    }

    *pulTotalBitsPrc = (*pulTotalBitsPrc) + ucNumOfBits;

    *pulCurIdx       += ((ucNumOfBits + ucBitsProcessedinMSB ) / 8 );

    return;

}


VOS_VOID TAF_XPDS_EncodeReqGpsAcqAssist(
    TAF_XPDS_REVLINK_REQ_GPS_ACQ_ASSIST_STRU               *pstGpsAcqAssist,
    VOS_UINT8                                              *pucDestBuf,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT32                                              ulTotNumOfBits;
    VOS_UINT32                                              ulCurrIdx;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set request type */
    pucDestBuf[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;

    /* check and set drop req parameter */
    TAF_XPDS_EncodeSetValue(pstGpsAcqAssist->ucDopplerReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* check and set add drop req parameter */
    TAF_XPDS_EncodeSetValue(pstGpsAcqAssist->ucAddDopplerReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* check and set code ph parameter */
    TAF_XPDS_EncodeSetValue(pstGpsAcqAssist->ucCodePhParaReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* check and set azimuth and elevation parameter */
    TAF_XPDS_EncodeSetValue(pstGpsAcqAssist->ucAZELReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set request parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeReqLocRsp(
    TAF_XPDS_REVLINK_REQ_LOC_RSP_STRU     *pstReqLocRsp,
    VOS_UINT8                             *pucDestBuf,
    VOS_UINT32                            *pulLength
)
{
    VOS_UINT32                                  ulTotNumOfBits;
    VOS_UINT32                                  ulCurrIdx;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;

    /* check and set height req parameter */
    TAF_XPDS_EncodeSetValue(pstReqLocRsp->ucHeightReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* check and set clock correction GPS req parameter */
    TAF_XPDS_EncodeSetValue(pstReqLocRsp->ucClkCorGpsReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* check and set velocity request parameter */
    TAF_XPDS_EncodeSetValue(pstReqLocRsp->ucVelocityReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set request parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeReqGpsAlmanac(
    VOS_UINT8                          *pucDestBuf,
    VOS_UINT32                         *pulLength
)
{

    /* set request type */
    pucDestBuf[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ALM;

    /* caluculate and set request parameter length */
    pucDestBuf[1] = 0x00;

    *pulLength    = 2;
}


VOS_VOID TAF_XPDS_EncodeReqGpsEphimeries(
    TAF_XPDS_REVLINK_REQ_GPS_EPH_STRU  *pstReqEph,
    VOS_UINT8                          *pucDestBuf,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                                  ulTotNumOfBits;
    VOS_UINT32                                  ulCurrIdx;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_GPS_EPH;

    /* check and set alpha and beta req parameter */
    TAF_XPDS_EncodeSetValue(pstReqEph->ucAlphaBetaParaReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set request parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeReject(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU  *pstReject,
    VOS_UINT8                         *pucDestBuf,
    VOS_UINT32                        *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* for reject, Unsolicited response is always 0 */

    /* set response type */
    pucDestBuf[0] = (pucDestBuf[0] | TAF_XPDS_RL_MSGTYPE_RESP_REJECT);

    /* set reject type parameter */
    TAF_XPDS_EncodeSetValue(pstReject->ucRejReqType, 4, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set reject reason parameter */
    TAF_XPDS_EncodeSetValue(pstReject->ucRejReason, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set response parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}



VOS_VOID TAF_XPDS_EncodeProvMsInfo(
    VOS_UINT8                          *pucDestBuf,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqMsInfoFlag())
    {
        pucDestBuf[0] = (pucDestBuf[0] | (1 << 4));
    }

    TAF_XPDS_SetReqMsInfoFlag(VOS_FALSE);

    /* set response type */
    pucDestBuf[0] = (pucDestBuf[0] | TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO);

    /* set MS LS revision parameter */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_MSINFO_MS_LS_REV, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set MS mode parameter */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_MSINFO_MS_MODE, 4, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set Pilot Ph cap parameter */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_QUARTER_CHIP_CAP, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* usGpsAquiCap and usLocCalcCap need to set according to the CDMA mode */
    if (TAF_XPDS_MSB_MODE == TAF_XPDS_GetAgpsFixMode())
    {
        /* setting  usGpsAquiCap  */
        TAF_XPDS_EncodeSetValue(TAF_XPDS_MSINFO_GPSAQUI_CAP_MSB, 12, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* setting  usLocCalcCap  */
        TAF_XPDS_EncodeSetValue(TAF_XPDS_MSINFO_LOCCALC_CAP_MSB, 12, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }
    else
    {
        /* setting  usGpsAquiCap  */
        TAF_XPDS_EncodeSetValue(TAF_XPDS_MSINFO_GPSAQUI_CAP_MSA, 12, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* setting  usLocCalcCap  */
        TAF_XPDS_EncodeSetValue(TAF_XPDS_MSINFO_LOCCALC_CAP_MSA, 12, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }


    /* caluculate and set response parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeProvPseudoRangMeas(
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU         *pstProvPr,
    VOS_UINT8                                         *pucDestBuf,
    VOS_UINT32                                        *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    VOS_UINT8                           ucLoopCnt;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqPsuRangMeasFlag())
    {
        pucDestBuf[0] = (pucDestBuf[0] | (1 << 4));
    }

    TAF_XPDS_SetReqPsuRangMeasFlag(VOS_FALSE);

    /* set response type */
    pucDestBuf[0] = (pucDestBuf[0] | TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS);

    /* set part num parameter */
    TAF_XPDS_EncodeSetValue(pstProvPr->ucPartNum, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set total part parameter */
    TAF_XPDS_EncodeSetValue(pstProvPr->ucTotalparts, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set num of PS ranges parameter */
    TAF_XPDS_EncodeSetValue(pstProvPr->ucNumOfPS, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time reference parameter */
    TAF_XPDS_EncodeSetValue(pstProvPr->ulTimeRef, 24, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time reference source parameter */
    TAF_XPDS_EncodeSetValue(pstProvPr->ucTimeRefSrc, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set offset include parameter */
    TAF_XPDS_EncodeSetValue(pstProvPr->ucOffsetIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstProvPr->ucOffsetIncl)
    {
        /* set reference PN parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->usRefPN, 9, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set mobile system offset parameter */
        TAF_XPDS_EncodeSetValue((VOS_UINT16)(pstProvPr->sMobileSysOffset), 14, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set satellite record */
    for (ucLoopCnt = 0; ucLoopCnt <= pstProvPr->ucNumOfPS; ucLoopCnt++)
    {
        /* set sat PRN num parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->astPsuedoInfo[ucLoopCnt].ucSvPRNNum, 6, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set sv cno parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->astPsuedoInfo[ucLoopCnt].ucSvCNO, 6, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set ps doppler parameter */
        TAF_XPDS_EncodeSetValue((VOS_UINT16)(pstProvPr->astPsuedoInfo[ucLoopCnt].sPsDoppler), 16, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set sv code ph wh parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->astPsuedoInfo[ucLoopCnt].usSvCodePhWh, 10, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set sv code ph fr parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->astPsuedoInfo[ucLoopCnt].usSvCodePhFr, 10, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set mul path ind parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->astPsuedoInfo[ucLoopCnt].ucMulPathInd, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set ps range rms err parameter */
        TAF_XPDS_EncodeSetValue(pstProvPr->astPsuedoInfo[ucLoopCnt].ucPsRangeRmsEr, 6, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeProvPilotPhaseMeas
(
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU     *pstProvPp,
    VOS_UINT8                                      *pucDestBuf,
    VOS_UINT32                                     *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    VOS_UINT8                           ucLoopCnt;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqPilotPhaseMeasFlag())
    {
        pucDestBuf[0] = (pucDestBuf[0] | (1 << 4));
    }

    TAF_XPDS_SetReqPilotPhaseMeasFlag(VOS_FALSE);

    /* set response type */
    pucDestBuf[0] = (pucDestBuf[0] | TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS);

    /* set time ref MS parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ulTimeRefMS, 24, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set offset incl parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucOffsetIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstProvPp->ucOffsetIncl)
    {
        /* set mob sys T offset parameter */
        TAF_XPDS_EncodeSetValue((VOS_UINT16)(pstProvPp->sMobSysTOffst), 14, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set ref PN parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->usRefPn, 9, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set ref pilot strength parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucRefPilotStrgth, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set band class parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucBandClass, 5, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set cdma freq parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->usCdmaFreq, 11, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set base id parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->usBaseId, 16, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set SID parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->usSID, 15, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set NID parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->usNID, 16, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set total rx pow parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucTotalRxPow, 5, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set part num parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucPartNum, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set total parts parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucTotalParts, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set num of pilots parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucNumOfPilotP, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set pilot record */
    for (ucLoopCnt = 0; ucLoopCnt < pstProvPp->ucNumOfPilotP; ucLoopCnt++)
    {
        /* set Pilot pn phase parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->astPilotRec[ucLoopCnt].ulPilotPnPhase, 19, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set pilot strength parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->astPilotRec[ucLoopCnt].ucPilotStrgth, 6, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set rms err phase parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->astPilotRec[ucLoopCnt].ucRmsErrPhase, 6, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set add pilot incl parameter */
    TAF_XPDS_EncodeSetValue(pstProvPp->ucAddPilotIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstProvPp->ucAddPilotIncl)
    {
        /* set add band class parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->ucAddBandClass, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set add cdma freq parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->usAddCdmaFreq, 11, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set total rx pow parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->ucAddTotRxPow, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set num of add pilots parameter */
        TAF_XPDS_EncodeSetValue(pstProvPp->ucNumOfAddPilotP, 6, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set add pilot record */
        for (ucLoopCnt = 0; ucLoopCnt <= pstProvPp->ucNumOfAddPilotP; ucLoopCnt++)
        {
            /* set add Pilot pn phase parameter */
            TAF_XPDS_EncodeSetValue(pstProvPp->astAddPilotRec[ucLoopCnt].ulPilotPnPhase, 19, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set add pilot strength parameter */
            TAF_XPDS_EncodeSetValue(pstProvPp->astPilotRec[ucLoopCnt].ucPilotStrgth, 6, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set add rms err phase parameter */
            TAF_XPDS_EncodeSetValue(pstProvPp->astPilotRec[ucLoopCnt].ucRmsErrPhase, 6, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* caluculate and set response parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeProvLocRsp(
    TAF_XPDS_REVLINK_RSP_LOC_INFO_STRU      *pstLocResp,
    VOS_UINT8                               *pucDestBuf,
    VOS_UINT32                              *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 2;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqLocRespFlag())
    {
        pucDestBuf[0] = (pucDestBuf[0] | (1 << 4));
    }

    TAF_XPDS_SetReqLocRespFlag(VOS_FALSE);

    /* set response type */
    pucDestBuf[0] = (pucDestBuf[0] | TAF_XPDS_RL_MSGTYPE_RESP_PROV_LOC_RESP);

    /* set time ref cdma parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->usTimeRefCdma, 14, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time lattitude parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ulLattitude, 25, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time longitude parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ulLongitude, 26, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time loc uncert angle parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucLocUncerAng, 4, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    /* set time loc uncert A parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucLocUncerA, 5, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time loc uncert P parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucLocUncerP, 5, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time fix type parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucFixType, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set time velo incl parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucVelocityIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstLocResp->ucVelocityIncl)
    {
        /* set time velo hor parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->usVelocityHor, 9, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);


        /* set time heading parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->usHeading, 10, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set time velo ver parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->usVelocityVer, 8, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    /* set time clock incl parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucClockIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstLocResp->ucClockIncl)
    {
        /* set time velo hor parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->ulClockBias, 18, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);


        /* set time heading parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->usClockDrift, 16, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set time clock incl parameter */
    TAF_XPDS_EncodeSetValue(pstLocResp->ucHeightIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    if (VOS_TRUE == pstLocResp->ucHeightIncl)
    {
        /* set time velo hor parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->usHeight, 14, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);


        /* set time heading parameter */
        TAF_XPDS_EncodeSetValue(pstLocResp->ucLocUncerV, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length */
    pucDestBuf[1] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 2;
}


VOS_VOID TAF_XPDS_EncodeStartDeliverData(
    TAF_XPDS_START_DELV_DATA_STRU      *pstStartDl,
    VOS_UINT8                          *pucDestBuf,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;
    VOS_UINT8                           ucLoopCnt;
    TAF_XPDS_MS_ID_RECORD_STRU          stMsID;

    PS_MEM_SET(&stMsID, 0, sizeof(TAF_XPDS_MS_ID_RECORD_STRU));

    TAF_XPDS_EncodeMsIdRec(&stMsID);

    ulTotNumOfBits    = 0;
    ulCurrIdx         = 1;

    /* set reserved parameter */
    TAF_XPDS_EncodeSetValue(0x00, 8, &ulTotNumOfBits,
        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set MS ID record reserved parameter */
    for (ucLoopCnt = 0; ucLoopCnt < 8; ucLoopCnt++)
    {
        TAF_XPDS_EncodeSetValue(stMsID.aucMsIdRec[ucLoopCnt], 8, &ulTotNumOfBits,
            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length */
    pucDestBuf[0] = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    *pulLength = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits) + 1;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodePdMsgHeader
 功能描述  : Cagps Encode Session Header
 输入参数  : TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_EncodePdMsgHeader(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulTotNumOfBits;
    VOS_UINT32                          ulCurrIdx;

    ulTotNumOfBits = 0;
    ulCurrIdx      = 0;

    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucSessStart, 1, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);
    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucSessEnd,   1, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);
    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucSessSrc,   1, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);
    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucSessTag,   5, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);
    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucPdMsgType, 8, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);
    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucNumOfReq,  4, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);
    TAF_XPDS_EncodeSetValue(pstPdMsgHeader->ucNumOfResp, 4, &ulTotNumOfBits, &pucMsgBuff[ulCurrIdx], &ulCurrIdx);

   *pulLength   += TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeReverseLinkReqs
 功能描述  : Encode Multi Reqs
 输入参数  : TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo
             VOS_UINT8                          *pucMsgBuff
             VOS_UINT32                         *pulLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_EncodeReverseReqs(
    TAF_XPDS_ENCODE_RL_INFO_STRU                           *pstEncodeRlInfo,
    VOS_UINT8                                              *pucMsgBuff,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulTempLength;
    TAF_XPDS_REVLINK_REQ_LOC_RSP_STRU                       stReqLocRsp;
    TAF_XPDS_REVLINK_REQ_GPS_ACQ_ASSIST_STRU                stReqGpsAcqAssist;
    TAF_XPDS_REVLINK_REQ_GPS_EPH_STRU                       stReqGpsEph;

    for (ucIndex = 0; ucIndex < pstEncodeRlInfo->ucNumOfReq; ucIndex++)
    {
        ulTempLength = 0;

        switch (pstEncodeRlInfo->aucReqType[ucIndex])
        {
            case TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP:

                stReqLocRsp.ucHeightReq    = VOS_TRUE;
                stReqLocRsp.ucClkCorGpsReq = VOS_TRUE;
                stReqLocRsp.ucVelocityReq  = VOS_TRUE;

                TAF_XPDS_EncodeReqLocRsp(&stReqLocRsp, pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_LOC_RSP);

                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST:

                stReqGpsAcqAssist.ucDopplerReq    = VOS_TRUE;
                stReqGpsAcqAssist.ucAddDopplerReq = VOS_TRUE;
                stReqGpsAcqAssist.ucCodePhParaReq = VOS_TRUE;
                stReqGpsAcqAssist.ucAZELReq       = VOS_TRUE;

                TAF_XPDS_EncodeReqGpsAcqAssist(&stReqGpsAcqAssist, pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_GPS_ACQ_ASSIST);

                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_GPS_ALM:
                TAF_XPDS_EncodeReqGpsAlmanac(pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_GPS_ALM);

                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_GPS_EPH:
                stReqGpsEph.ucAlphaBetaParaReq = VOS_TRUE;

                TAF_XPDS_EncodeReqGpsEphimeries(&stReqGpsEph, pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_REQ_GPS_EPH);

                break;

            default:
                break;
        }

        pucMsgBuff += ulTempLength;
       *pulLength  += ulTempLength;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeReverseRsps
 功能描述  : Encode Multi Rsps
 输入参数  : TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo
             VOS_UINT8                          *pucMsgBuff
             VOS_UINT32                         *pulLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_EncodeReverseRsps(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
)
{
    TAF_XPDS_PDE_PUBLIC_DATA_STRU      *pstPdePubData = VOS_NULL_PTR;
    TAF_XPDS_PUBLIC_DATA_STRU          *pstPubData    = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulTempLength;

    pstPdePubData = TAF_XPDS_GetPdePublicData();
    pstPubData    = TAF_XPDS_GetPublicDataAddr();

    for (ucIndex = 0; ucIndex < pstEncodeRlInfo->ucNumOfResp; ucIndex++)
    {
        ulTempLength   = 0;

        switch (pstEncodeRlInfo->aucRspType[ucIndex])
        {
            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_LOC_RESP:
                TAF_XPDS_EncodeProvLocRsp(&(pstPubData->stRspLocInfo), pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_LOC_RSP);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO:
                TAF_XPDS_EncodeProvMsInfo(pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_MS_INFO);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS:
                TAF_XPDS_EncodeProvPilotPhaseMeas(&(pstPubData->stPilotInfo), pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_PH_MEAS);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS:
                TAF_XPDS_EncodeProvPseudoRangMeas(&(pstPdePubData->stRspPrmInfo), pucMsgBuff, &ulTempLength);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_PDE_RL_RSP_PROV_PSUEDO_MEAS);
                break;

            default:
                break;
        }

        pucMsgBuff += ulTempLength;
       *pulLength  += ulTempLength;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeReverseMsg
 功能描述  : Encode one Reverse Link Msg
 输入参数  : TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo
             VOS_UINT8                          *pcDestBuf
             VOS_UINT32                         *pulLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_EncodeReverseMsg(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8                          *pucMsgBuff;
    TAF_XPDS_PD_MSG_HEADER_STRU        stPdMsgHeader;

    pucMsgBuff  = pcDestBuf;

    /* 构造Session Header Info */
    PS_MEM_SET(&stPdMsgHeader, 0, sizeof(stPdMsgHeader));

    if (TAF_XPDS_PDE_SESSION_STATUS_NULL == TAF_XPDS_GetPdeSessionStatus())
    {
        stPdMsgHeader.ucSessStart = 1;

        TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_STARTED);
    }
    else
    {
        stPdMsgHeader.ucSessStart = 0;
    }

    stPdMsgHeader.ucSessEnd    = 0;

    if (TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS == TAF_XPDS_GetPdeSessionTriggerType())
    {
        stPdMsgHeader.ucSessSrc = 1;
    }
    else
    {
        stPdMsgHeader.ucSessSrc = 0;
    }

    stPdMsgHeader.ucSessTag   = TAF_XPDS_GetSessTagInRsvPdMsgHeader();
    stPdMsgHeader.ucPdMsgType = 0;
    stPdMsgHeader.ucNumOfReq  = pstEncodeRlInfo->ucNumOfReq;
    stPdMsgHeader.ucNumOfResp = pstEncodeRlInfo->ucNumOfResp;

   *pulLength   = 0;

    TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(&stPdMsgHeader);

    /* First Encode Multi Reqs Info */
    TAF_XPDS_EncodePdMsgHeader(&stPdMsgHeader, (pucMsgBuff + 1), pulLength);

    /* First Encode Multi Reqs Info */
    /* Skip the number of bytes of previous message */
    TAF_XPDS_EncodeReverseReqs(pstEncodeRlInfo, (pucMsgBuff + (*pulLength) + 1), pulLength);

    /* Second Encode Multi Rsps Info */
    TAF_XPDS_EncodeReverseRsps(pstEncodeRlInfo, (pucMsgBuff + (*pulLength) + 1), pulLength);

    /* assign the total length of message */
    pcDestBuf[0] = (VOS_UINT8)(*pulLength);

    /* add the first byte */
   *pulLength += 1;
}

#if 0


VOS_UINT32 TAF_XPDS_EncodeReqExtLocRsp(
    TAF_XPDS_REVLINK_REQ_EXT_LOC_RESP_STRU *pstReqExtLocRsp,
    VOS_UINT8                              *pucDestBuf,
    VOS_UINT32                             *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_EXT_LOC_RESP;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* set fix type req  */
    TAF_XPDS_EncodeSetValue(pstReqExtLocRsp->ucFixTypeReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* horiz location uncertainty requset */
    TAF_XPDS_EncodeSetValue(pstReqExtLocRsp->ucHoriLocUncerReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* height request */
    TAF_XPDS_EncodeSetValue(pstReqExtLocRsp->ucHeightReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* clock correction request */
    TAF_XPDS_EncodeSetValue(pstReqExtLocRsp->ucClockCorrReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* velocity request */
    TAF_XPDS_EncodeSetValue(pstReqExtLocRsp->ucVelocityReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* velocity uncertainity request */
    TAF_XPDS_EncodeSetValue(pstReqExtLocRsp->ucHoriVelUncerReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeReqEnhBsAlmanac(
    TAF_XPDS_REVLINK_REQ_ENH_BS_ALM_STRU  *pstEnhBsAlmn,
    VOS_UINT8                             *pucDestBuf,
    VOS_UINT32                            *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;
    VOS_UINT8       ucLoopCount;
    VOS_UINT8       ucLoopCount2;

    ucLoopCount             = 0;
    ucLoopCount2            = 0;
    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_ENH_BS_ALMN;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* pilot id information requested or not */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucPilotIdReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* repeater information requested or not */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucRepeatInfoReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* antena angle information requested or not */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucAntenaAngInfoReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* antena range information requested or not  */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucAntenaRngInfoReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* whether max no radius included or not */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucMaxRadIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstEnhBsAlmn->ucMaxRadIncl)
    {
        /* maximal radius */
        TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->usMaxRadius, 9, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* maximum no of pilots included or not */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucMaxNoPilotIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstEnhBsAlmn->ucMaxNoPilotIncl)
    {
        /* maximal number of pilots */
        TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->usMaxNoOfPilots, 9, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* whether freq list included or not */
    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucFreqListIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstEnhBsAlmn->ucFreqListIncl)
    {
        /* number of freq included */
        TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->ucNoOfFreq, 4, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount < pstEnhBsAlmn->ucNoOfFreq; ucLoopCount++)
        {
            /* band class */
            TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->astFreqInfo[ucLoopCount].ucBandClass, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* cdma frequency */
            TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->astFreqInfo[ucLoopCount].usCdmaFreq, 11, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* mode indicator */
            TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->astFreqInfo[ucLoopCount].ucModeInd, 2, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* pilot record is as previous or not */
            TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->astFreqInfo[ucLoopCount].ucPilotRecAsPrev, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_FALSE == pstEnhBsAlmn->astFreqInfo[ucLoopCount].ucPilotRecAsPrev)
            {
                /* number of pilot pn present */
                TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->astFreqInfo[ucLoopCount].ucNumOfPilots, 6, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

                for (ucLoopCount2 = 0; ucLoopCount2 < pstEnhBsAlmn->astFreqInfo[ucLoopCount].ucNumOfPilots; ucLoopCount2++)
                {
                    /* number of pilot pn present */
                    TAF_XPDS_EncodeSetValue(pstEnhBsAlmn->astFreqInfo[ucLoopCount].ausPilotPn[ucLoopCount2], 9, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
                }
            }
        }
    }

    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_EncodeReqGenAcqAssist(
    TAF_XPDS_REVLINK_REQ_GEN_AQUI_ASSI_STRU   *pstGenAcqAssist,
    VOS_UINT8                                 *pucDestBuf,
    VOS_UINT32                                *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;

    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_GEN_ACQUI_ASSIST;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* location reference information requested or not */
    TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucLocRefReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* clock correction for GPS time information requested or not */
    TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucClockCorrGpsReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* GPS satellite information requested or not */
    TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucSvInfoReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGenAcqAssist->ucSvInfoReq)
    {
        /* satellite operating mode information requested or not */
        TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucSvOptModeInfoReq, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* 2nd derivative of doppler requested or not */
        TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucDopp2Req, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* azimuth and elevation angle requested or not */
        TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucAzElAngleReq, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    /* BS information requested or not */
    TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucBSInfoReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGenAcqAssist->ucBSInfoReq)
    {
        /* repeater information requested or not */
        TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucRepeaterInfoReq, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* pilot aquisition threshold included or not */
        TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucPilotAquiThrIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (VOS_TRUE == pstGenAcqAssist->ucPilotAquiThrIncl)
        {
            /* pilot aquisition threshold */
            TAF_XPDS_EncodeSetValue(pstGenAcqAssist->ucPilotAquiThrsh, 3, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_EncodeReqExtGpsSensitivityAssist(
    TAF_XPDS_REVLINK_REQ_EXT_GPS_SENS_ASSI_STRU   *pstExtGpsSensAssist,
    VOS_UINT8                                     *pucDestBuf,
    VOS_UINT32                                    *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;
    VOS_UINT8       ucLoopCount;

    ucLoopCount             = 0;
    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_SENS_ASSIST;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* satellite bitmask information included or not */
    TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->ucSvMaskIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtGpsSensAssist->ucSvMaskIncl)
    {
        /* number of bitmask records */
        TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->ucNoOfSvMasks, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount <= pstExtGpsSensAssist->ucNoOfSvMasks; ucLoopCount++)
        {
            /* navigation message format */
            TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->astBitMaskRec[ucLoopCount].ucNavMsgFormat, 4, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* satellite bitmask msg as previous  or not */
            TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->astBitMaskRec[ucLoopCount].ucSvMaskAsPrev, 1, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_FALSE == pstExtGpsSensAssist->astBitMaskRec[ucLoopCount].ucSvMaskAsPrev)
            {
                /* satellite bitmask all ones */
                TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->astBitMaskRec[ucLoopCount].ucSvMaskAllOne, 1, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

                if (VOS_FALSE == pstExtGpsSensAssist->astBitMaskRec[ucLoopCount].ucSvMaskAllOne)
                {
                    /* satellite bitmask all ones */
                    TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->astBitMaskRec[ucLoopCount].ulSvMask, 32, &ulTotNumOfBits,
                                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);
                }
            }
        }
    }


    /* request reference bit number included or not */
    TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->ucReqRefBitIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtGpsSensAssist->ucReqRefBitIncl)
    {
        /* request reference bit number */
        TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->usReqRefBitNum, 11, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* DR size included or not */
    TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->ucReqDRSizeIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtGpsSensAssist->ucReqDRSizeIncl)
    {
        /* DR size */
        TAF_XPDS_EncodeSetValue(pstExtGpsSensAssist->ucReqDRSize, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}




VOS_UINT32 TAF_XPDS_EncodeReqExtGpsEphimeris(
    TAF_XPDS_REVLINK_REQ_EXT_GPS_EPH_STRU     *pstExtGpsEphi,
    VOS_UINT8                                 *pucDestBuf,
    VOS_UINT32                                *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;

    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_EPHI;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* alpha and beta parameter requested or not */
    TAF_XPDS_EncodeSetValue(pstExtGpsEphi->ucABparaReq, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* satellite bit mask include or not */
    TAF_XPDS_EncodeSetValue(pstExtGpsEphi->ucSVMaskIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtGpsEphi->ucSVMaskIncl)
    {
        /* satellite bit mask */
        TAF_XPDS_EncodeSetValue(pstExtGpsEphi->ulSVMask, 32, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }


    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeReqExtGpsNavMsgBits(
    TAF_XPDS_REVLINK_REQ_GPS_NAV_MSGBITS_STRU *pstExtGpsNavMsgBits,
    VOS_UINT8                                 *pucDestBuf,
    VOS_UINT32                                *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;

    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_NAV_MSG_BITS;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* alpha and beta parameter requested or not */
    TAF_XPDS_EncodeSetValue(pstExtGpsNavMsgBits->ucSubFrame4and5Req, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeReqDgpsAssistance(
    TAF_XPDS_REVLINK_REQ_DGPS_ASSI_STRU   *pstReqDgpsAssis,
    VOS_UINT8                             *pucDestBuf,
    VOS_UINT32                            *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT32      ulLenthFieldStartingBit;
    VOS_UINT8       ucLoopCount;

    ucLoopCount             = 0;
    ulTotNumOfBits          = 0;
    ulCurrIdx               = 2;
    ulLenthFieldStartingBit = 0;

    /* set request type */
    pucDestBuf[0]     = TAF_XPDS_RL_MSGTYPE_REQ_DGPS_ASSIST;

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits
        so the messagbe encoding starts in 3rd byte 3rd bit*/
    ulTotNumOfBits    = 2;

    /* number of satellite record */
    TAF_XPDS_EncodeSetValue(pstReqDgpsAssis->ucNumOfSV, 4, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* time limit of ephimeries included or not */
    TAF_XPDS_EncodeSetValue(pstReqDgpsAssis->ucTOELimitIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstReqDgpsAssis->ucTOELimitIncl)
    {
        /* time limit of ephimeries */
        TAF_XPDS_EncodeSetValue(pstReqDgpsAssis->ucTOELimit, 4, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* alpha and beta parameter requested or not */
        TAF_XPDS_EncodeSetValue(pstReqDgpsAssis->ucABparaReq, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    for (ucLoopCount = 0; ucLoopCount <= pstReqDgpsAssis->ucNumOfSV; ucLoopCount++)
    {
        /* issue of data */
        TAF_XPDS_EncodeSetValue(pstReqDgpsAssis->astSatInfo[ucLoopCount].ucIODE, 8, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* satellite ID */
        TAF_XPDS_EncodeSetValue(pstReqDgpsAssis->astSatInfo[ucLoopCount].ucSvId, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }


    /* caluculate and set response parameter length
        -2 because for encoding we added 2 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 2));

    /* since in PD_MSG_TYPE 1 , length field is 10 bit long */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_EncodeExtReject(
    TAF_XPDS_REVLINK_RSP_EXT_REJECT_STRU  *pstExtReject,
    VOS_UINT8                             *pucDestBuf,
    VOS_UINT32                            *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_EXT_REJECT, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* set reject type parameter */
    TAF_XPDS_EncodeSetValue(pstExtReject->ucRejReqType, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set reject reason parameter */
    TAF_XPDS_EncodeSetValue(pstExtReject->ucRejReason, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set retry time incl */
    TAF_XPDS_EncodeSetValue(pstExtReject->ucRetryTimeIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtReject->ucRetryTimeIncl)
    {
        /* set retry time incl */
        TAF_XPDS_EncodeSetValue(pstExtReject->ucRetryTime, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));


    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_EncodeProvExtLocRsp(
    TAF_XPDS_REVLINK_RSP_EXT_LOC_RESP_STRU    *pstExtLocResp,
    VOS_UINT8                                 *pucDestBuf,
    VOS_UINT32                                *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqExtLocRespFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqExtLocRespFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_LOC_RESP, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* set time ref included flag */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucTimeRefIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtLocResp->ucFixTypeIncl)
    {
        /* set time ref */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ulTimeRef, 22, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set fix type included flag */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucFixTypeIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtLocResp->ucFixTypeIncl)
    {
        /* set fix type */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucFixType, 4, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set latitude */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ulLattitude, 25, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set longitude */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ulLongitude, 26, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set loc uncertainty type H */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncHType, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtLocResp->ucLocUncHType)
    {
        /* set loc uncertainty H */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncH, 5, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        /* set loc uncertainty confidence */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncHCnf, 2, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set loc uncertainty angle */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncAng, 4, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set loc uncertainty angle error hori */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncA, 5, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set loc uncertainty angle error perp */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncP, 5, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set height incl */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucHeightIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    if (VOS_TRUE == pstExtLocResp->ucHeightIncl)
    {

        /* set height */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->usHeight, 14, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set vertical location uncertainty */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncV, 5, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set vertical location uncertainty confidence */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucLocUncVCnf, 2, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }


    /* set velocity incl */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtLocResp->ucVeloIncl)
    {

        /* set hori velocity */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->usVeloHor, 11, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set heading */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->usHeading, 10, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set hori velocity uncertainity type */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncHType, 1, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (VOS_FALSE == pstExtLocResp->ucVeloUncHType)
        {

            /* set hori velocity uncertainity */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncH, 4, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set hori velocity uncertainity confidence */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncHCnf, 2, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
        else
        {
            /* set angule of axis of standard error for hori velocity */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncAng, 4, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set standard deviation of error along angle for hor uncertainty */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncA, 4, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set standard deviation of error perpendicular to angle for hor uncertainty */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncP, 4, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }

        /* set vertical veloc incl */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloVertIncl, 1, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (VOS_TRUE == pstExtLocResp->ucVeloVertIncl)
        {
            /* set vertical veloc */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloVert, 8, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set vertical veloc uncertainty */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncV, 4, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set vertical veloc uncertainty confidence */
            TAF_XPDS_EncodeSetValue(pstExtLocResp->ucVeloUncVCnf, 2, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        }

    }

    /* set clock bias incl */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucClockBiasIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtLocResp->ucClockBiasIncl)
    {
        /* set clock bias */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ulClockBias, 18, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set clock drift incl */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucClockDriftIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstExtLocResp->ucClockBiasIncl)
    {
        /* set clock drift */
        TAF_XPDS_EncodeSetValue(pstExtLocResp->ulClockDrift, 17, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* set improved loc support */
    TAF_XPDS_EncodeSetValue(pstExtLocResp->ucImprLocSupp, 1, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));


    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeProvExtMsInfo(
    TAF_XPDS_REVLINK_RSP_EXT_MS_INFO_STRU     *pstProvExtMsInfo,
    VOS_UINT8                                 *pucDestBuf,
    VOS_UINT32                                *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8       ucLoopCount;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqExtMsInfoFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqExtMsInfoFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_MS_INFO, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* set MS LS revision parameter */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucMsLsRev, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set MS Capablity incl */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucMsCapincl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    if (VOS_TRUE == pstProvExtMsInfo->ucMsCapincl)
    {
        /* set acquisition Capablity */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->usAcqCap, 14, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set position calculation Capablity */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucLocCalcCap, 12, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* In big endian, bits 8 - 11 all are not zero*/
        if ((pstProvExtMsInfo->usAcqCap & 0x0780) != 0)
        {
            /* set prepetition detection capablity */
            TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucRptrDetCap, 1, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }

        /* set bearing capablity */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucBearingCap, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    /* set gps reciever capablity info included flag */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucGpsRxCapIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    if (VOS_TRUE == pstProvExtMsInfo->ucGpsRxCapIncl)
    {
        /* set gps reciever capablity length */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucGpsRxCapLen, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount <= pstProvExtMsInfo->ucGpsRxCapLen; ucLoopCount++)
        {
            /* set gps reciever capablity */
            TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->aucGpsRxCap[ucLoopCount], 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* set MS Band class capablity info included flag */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucMsBcCapIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstProvExtMsInfo->ucMsBcCapIncl)
    {
        /* set MS Band class capablity length */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucMsBcCapLen, 7, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount <= pstProvExtMsInfo->ucMsBcCapLen; ucLoopCount++)
        {
            /* set gps reciever capablity */
            TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->aucMsBcCap[ucLoopCount], 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* set Position determin for Emergncy only */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucEmerOnlyLcs, 1, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set Pilot detection sensitivity incl */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucPilDetSensIncl, 1, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstProvExtMsInfo->ucPilDetSensIncl)
    {
        /* set Pilot detection sensitivity incl */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucPilDetSens, 3, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    /* set MS Status incl */
    TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucMsStatusIncl, 1, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstProvExtMsInfo->ucMsStatusIncl)
    {
        /* set CDMA Protocol in use */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucPRevInUse, 8, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* set available info status */
        TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->usAvailInfStatus, 9, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* In big endian, if 5th LSB is set to 1 */
        if ((pstProvExtMsInfo->usAvailInfStatus & 0x010 ) != 0)
        {
            /* set loc uncertainity Hori - circular */
            TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucLocUncHc, 3, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* set loc uncertainity Hori - circular */
            TAF_XPDS_EncodeSetValue(pstProvExtMsInfo->ucLocAge, 4, &ulTotNumOfBits,
                                          &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        }

    }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_VOID TAF_XPDS_EncodeGenLocGlobalInfoRec(
    TAF_XPDS_GLOBAL_INFO_REC_STRU *pstGblInfRec,
    VOS_UINT8                     *pucDestBuf,
    VOS_UINT32                    *pulTotalBitsPrc
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8       ucLoopCount;
    VOS_UINT8      *pucDestStrt;
    VOS_UINT8       ucGloInfRecLen;
    VOS_UINT32      ulAlreadyProcInDest;
    VOS_UINT32      ulDummy;

    ulDummy             = 0;
    pucDestStrt         = pucDestBuf;
    ulAlreadyProcInDest = (*pulTotalBitsPrc) % 8;

    /* for the length field to encode*/
    ulTotNumOfBits      = 6 + ulAlreadyProcInDest;

    ulCurrIdx           = 0;

    if ( ulTotNumOfBits >= 8)
    {
        ulCurrIdx++;
        ulTotNumOfBits %= 8;
    }


    /* message seq */
    TAF_XPDS_EncodeSetValue(pstGblInfRec->ucMsgSeq, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* time ref */
    TAF_XPDS_EncodeSetValue(pstGblInfRec->ulTimeRef, 24, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* time ref source */
    TAF_XPDS_EncodeSetValue(pstGblInfRec->ucTimeRefSrc, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* pilot id incl */
    TAF_XPDS_EncodeSetValue(pstGblInfRec->ucPilotIdIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGblInfRec->ucPilotIdIncl)
    {
        /* mode ind */
        TAF_XPDS_EncodeSetValue(pstGblInfRec->ucModeInd, 2, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (0x00 == pstGblInfRec->ucModeInd)
        {
            /* SID */
            TAF_XPDS_EncodeSetValue(pstGblInfRec->usSID, 15, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* NID */
            TAF_XPDS_EncodeSetValue(pstGblInfRec->usNID, 16, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* BASE ID */
            TAF_XPDS_EncodeSetValue(pstGblInfRec->usBaseId, 16, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* MSC ID Incl */
            TAF_XPDS_EncodeSetValue(pstGblInfRec->ucMscIdIncl, 1, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_TRUE == pstGblInfRec->ucMscIdIncl)
            {
                /* MSC ID */
                TAF_XPDS_EncodeSetValue(pstGblInfRec->ulMscId, 24, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }
        }
        else if (0x01 == pstGblInfRec->ucModeInd)
        {
            for (ucLoopCount = 0; ucLoopCount < TAF_XPDS_RL_SECID_SIZE; ucLoopCount++)
            {
                /* SECTOR ID */
                TAF_XPDS_EncodeSetValue(pstGblInfRec->aucSectorId[ucLoopCount], 1, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }

        }
        else
        {
        }
    }


    /* caluculate and set request parameter length */
    ucGloInfRecLen = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    /* global info length */
    TAF_XPDS_EncodeSetValue(ucGloInfRecLen, 6, &ulAlreadyProcInDest,
                                    pucDestStrt, &ulDummy);
}



VOS_UINT32 TAF_XPDS_EncodeGenLocPrRec(
    TAF_XPDS_PSUEDO_RAND_REC_STRU                 *pstGblPRRec,
    TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU         *pstGenLocMeas,
    VOS_UINT8                                     *pucDestBuf,
    VOS_UINT32                                    *pulTotalBitsPrc
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8      *pucDestStrt;
    VOS_UINT8       ucGloInfRecLen;
    VOS_UINT32      ulAlreadyProcInDest;
    VOS_UINT32      ulDummy;

    ulDummy             = 0;
    pucDestStrt         = pucDestBuf;
    ulAlreadyProcInDest = (*pulTotalBitsPrc) % 8;

    /* for the length field to encode*/
    ulTotNumOfBits      = 5 + ulAlreadyProcInDest;

    ulCurrIdx           = 0;

    if ( ulTotNumOfBits >= 8)
    {
        ulCurrIdx++;
        ulTotNumOfBits %= 8;
    }

    /* PRN NUM */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPRNNum, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* PR FREQ AS Previous */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPRFreqAsPrev, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_FALSE == pstGblPRRec->ucPRFreqAsPrev)
    {
        /* PR FREQ AS Previous */
        TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPRFreq, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    if (VOS_TRUE == pstGenLocMeas->ucIndPrTimeRefIncl)
    {
        /* PR TIME referance as prev */
        TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPRTimeRefAsPrev, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (VOS_FALSE == pstGblPRRec->ucPRTimeRefAsPrev)
        {
            /* DELTA PR TIME REF */
            TAF_XPDS_EncodeSetValue(pstGblPRRec->usDeltaPRTimeRef, 16, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* satellite code phase whole chips */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->usSvCodePhWh, 10, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* satellite code phase fractional chips */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->usSvCodePhFr, 10, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* satellite code phase integer code included or not */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucSvCodePhIntIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGblPRRec->ucSvCodePhIntIncl)
    {
        /* satellite code phase integer code included or not */
        TAF_XPDS_EncodeSetValue(pstGblPRRec->ucSvCodePhInt, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* psuedo random range error indicator */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPrErrInd, 7, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* psuedorandom RMS error */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPrRmsErr, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* satellite psuedo doppler */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->usPrPsDoppler, 16, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* satellite psuedo doppler RMS error */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPrPsRmsDoppErr, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* satellite C/N */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucCNO, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* estimate psuedorange false alarm probability */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPrFalseAlarProb, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* estimate psuedorange false alarm range */
    TAF_XPDS_EncodeSetValue(pstGblPRRec->ucPrFalseAlarRange, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    /* caluculate and set request parameter length */
    ucGloInfRecLen = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    /* global info length */
    TAF_XPDS_EncodeSetValue(ucGloInfRecLen, 5, &ulAlreadyProcInDest,
                                    pucDestStrt, &ulDummy);


    return VOS_OK;
}



VOS_VOID TAF_XPDS_EncodeGenLocPrFreqPilotRec(
    TAF_XPDS_PP_FREQ_PILOT_REC_STRU   *pstFreqPilotRec,
    VOS_UINT8                         *pucDestBuf,
    VOS_UINT32                        *pulTotalBitsPrc,
    VOS_UINT8                          ucRptrInfoIncl,
    VOS_UINT8                          ucPpPsDopplrIncl
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8      *pucDestStrt;
    VOS_UINT8       ucGloInfRecLen;
    VOS_UINT32      ulAlreadyProcInDest;
    VOS_UINT32      ulDummy;
    VOS_UINT8       ucLoopCount;

    ulDummy             = 0;
    pucDestStrt         = pucDestBuf;
    ulAlreadyProcInDest = (*pulTotalBitsPrc) % 8;

    /* for the length field to encode*/
    ulTotNumOfBits      = 5 + ulAlreadyProcInDest;

    ulCurrIdx           = 0;

    if ( ulTotNumOfBits >= 8)
    {
        ulCurrIdx++;
        ulTotNumOfBits %= 8;
    }

    /* pilot phase */
    TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ulPilotPnPh,
                                    19,
                                    &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == ucRptrInfoIncl)
    {
        /* repeater detection status  */
        TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucRptrDetStatus,
                                        3,
                                        &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (0x03 == pstFreqPilotRec->ucRptrDetStatus)
        {
            /* repeater type */
            TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucRptrType,
                                            3,
                                            &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (0x01 == pstFreqPilotRec->ucRptrType)
            {
                /* repeater signal information included or not */
                TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucRptrIdIncl,
                                                1,
                                                &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

                if (VOS_TRUE == pstFreqPilotRec->ucRptrIdIncl)
                {
                    for (ucLoopCount = 0; ucLoopCount < TAF_XPDS_RL_RPTR_ID_SIZE; ucLoopCount++)
                    {
                        /* repeater signal identification ???*/
                        TAF_XPDS_EncodeSetValue(pstFreqPilotRec->aucRptrId[ucLoopCount],
                                                        1,
                                                        &ulTotNumOfBits,
                                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
                    }
                }
            }
        }
    }

    /* pilot phase measurement error indication */
    TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPpErrInd,
                                    6,
                                    &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* pilot phase RMS error */
    TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPpRmsEr,
                                    6,
                                    &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (ucPpPsDopplrIncl)
    {
        /* pilot phase psuedo doppler */
        TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPpPsDoppler,
                                        8,
                                        &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* psuedo doppler RMS error */
        TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPpPsDoppRmsErr,
                                        3,
                                        &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* pilot strength */
    TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPilotStrngth,
                                    6,
                                    &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* pilot phase false alarm probability */
    TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPpFalseAlmProb,
                                    2,
                                    &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* pilot phase false alarm range */
    TAF_XPDS_EncodeSetValue(pstFreqPilotRec->ucPpFalseAlmRange,
                                    2,
                                    &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);


    /* caluculate and set request parameter length */
    ucGloInfRecLen = (VOS_UINT8)TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    /* global info length */
    TAF_XPDS_EncodeSetValue(ucGloInfRecLen, 5, &ulAlreadyProcInDest,
                                    pucDestStrt, &ulDummy);
}



VOS_UINT32 TAF_XPDS_EncodeProvGenLocMeas(
    TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU         *pstGenLocMeas,
    VOS_UINT8                                     *pucDestBuf,
    VOS_UINT32                                    *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8       ucLoopCount;
    VOS_UINT8       ucLoopCount2;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;

    ucLoopCount             = 0;
    ucLoopCount2            = 0;
    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqGenLocMeasFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqGenLocMeasFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_GEN_LOC_MEAS, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* set Part number */
    TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucPartNum, 4, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set total number of Parts */
    TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucTotalParts, 4, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set total number of Parts */
    TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucGloInfoAsPrev, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_FALSE == pstGenLocMeas->ucGloInfoAsPrev)
    {
        TAF_XPDS_EncodeGenLocGlobalInfoRec(&(pstGenLocMeas->stGblInfRec), &pucDestBuf[ulCurrIdx], &ulTotNumOfBits);
    }

    /* PR INFO INCL */
    TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucPrInfIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGenLocMeas->ucPrInfIncl)
    {
        /* Individual PR TIME REF INCL */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucIndPrTimeRefIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* Number of PR */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucNoOfPrP, 5, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount < pstGenLocMeas->ucNoOfPrP; ucLoopCount++)
        {
            TAF_XPDS_EncodeGenLocPrRec(&(pstGenLocMeas->astPRRecord[ucLoopCount]),
                                            pstGenLocMeas,
                                            &pucDestBuf[ulCurrIdx],
                                            &ulTotNumOfBits);
        }
    }

    /* pilot phase information included or not */
    TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucPpInfInclP, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGenLocMeas->ucPpInfInclP)
    {

        /* indivisual pilot phase ref time included or not */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucIndPpTimeRefIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* pilot phase psuedo doppler information included or not */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucPpPsDopplrIncl, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* number of frequency records */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucNumOfFreq, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount < pstGenLocMeas->ucNumOfFreq; ucLoopCount++)
        {

            /* band class */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucBandClass, 5, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* frequency */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].usCdmaFreq, 11, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* mode indicator */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucModeInd, 2, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* total recieved power */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucTotRxPow, 5, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_TRUE == pstGenLocMeas->ucIndPpTimeRefIncl)
            {

                /* pilot phase time reference as previous */
                TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucPpTimeRefAsPrev, 1, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

                if (VOS_FALSE == pstGenLocMeas->astPPFreq[ucLoopCount].ucPpTimeRefAsPrev)
                {
                    /* reference time differemce between this measurement and common ref time */
                    TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].usDeltaPpTimeRef, 16, &ulTotNumOfBits,
                                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);
                }
            }

            /* repeator information included or not */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucRptrInfoIncl, 1, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_TRUE == pstGenLocMeas->astPPFreq[ucLoopCount].ucRptrInfoIncl)
            {
                /* repeater identification length */
                TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucRptrIdLen, 6, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }

            /* reserved */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucReserved, 4, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* number of pilot records */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astPPFreq[ucLoopCount].ucNumOfPilTxF, 6, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            for (ucLoopCount2 = 0; ucLoopCount2 < pstGenLocMeas->astPPFreq[ucLoopCount].ucNumOfPilTxF; ucLoopCount2++)
            {
                TAF_XPDS_EncodeGenLocPrFreqPilotRec( &(pstGenLocMeas->astPPFreq[ucLoopCount].astPilotRec[ucLoopCount2]),
                                                            &pucDestBuf[ulCurrIdx],
                                                            &ulTotNumOfBits,
                                                            pstGenLocMeas->astPPFreq[ucLoopCount].ucRptrInfoIncl,
                                                            pstGenLocMeas->ucPpPsDopplrIncl);

            }
        }
    }

    /* offset information included or not */
    TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucOffstInfoInclP, 1, &ulTotNumOfBits,
                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstGenLocMeas->ucOffstInfoInclP)
    {

        /* offset start reference time */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->usOffStartRefTime, 10, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

         /* offset reference time included or not */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucOffstRefTimeInc, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* offset variable included or not */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucOffstVarIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* Tx power included or not */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucTxPowIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* total number of offset records */
        TAF_XPDS_EncodeSetValue(pstGenLocMeas->ucNumOfOffRec, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount < pstGenLocMeas->ucNumOfOffRec; ucLoopCount++)
        {

            /* frequency offset */
            TAF_XPDS_EncodeSetValue(pstGenLocMeas->astOffsetRec[ucLoopCount].usCdmaTxOffst, 14, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_TRUE == pstGenLocMeas->ucOffstVarIncl)
            {
                 /* offset variable value */
                TAF_XPDS_EncodeSetValue(pstGenLocMeas->astOffsetRec[ucLoopCount].ucOffstVar, 3, &ulTotNumOfBits,
                                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }

            if (VOS_TRUE == pstGenLocMeas->ucTxPowIncl)
            {
                /* Tx power */
                TAF_XPDS_EncodeSetValue(pstGenLocMeas->astOffsetRec[ucLoopCount].ucTxPower, 5, &ulTotNumOfBits,
                                         &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }
        }

     }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));


    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_EncodeProvExtCancelAck(
    TAF_XPDS_REVLINK_RSP_EXT_CANC_ACK_STRU   *pstExtCancelAck,
    VOS_UINT8                                *pucDestBuf,
    VOS_UINT32                               *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqExtCancelReqFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqExtCancelReqFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_CANCEL_ACK, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* set cancel type */
    TAF_XPDS_EncodeSetValue(pstExtCancelAck->ucCanclTypeAck, 8, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* set number of outstanding reqs */
    TAF_XPDS_EncodeSetValue(pstExtCancelAck->ucNoOutReq, 1, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeGpsCoarseLoc(
    TAF_XPDS_REVLINK_RSP_GPS_COAR_LOC_STRU    *pstRspGpsCoarLoc,
    VOS_UINT8                                 *pucDestBuf,
    VOS_UINT32                                *pulLength
)
{

    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8       ucLoopCount;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;

    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqGpsCoarseLocReqFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqGpsCoarseLocReqFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_GPS_COARS_LOC_RESP, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* time of reference */
    TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->ulTimeRef, 20, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* reference lattitude correction */
    TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->ulDeltaLatitude, 20, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* reference longitude correction */
    TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->ulDeltaLongitude, 20, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* reference altitude correction */
    TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->ulDeltaAltitude, 22, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* reference altitude correction */
    TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->ulSatsList, 32, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* reference altitude correction */
    TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->ucPrErrThrsh, 4, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    for (ucLoopCount = 0; ucLoopCount < TAF_XPDS_RL_SAT_LIST_SIZE; ucLoopCount++)
    {
        /* inverse of weighting factor */
        TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->astSatsRec[ucLoopCount].ucInvWeiFact, 6, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* GPS week number of sub almanac */
        TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->astSatsRec[ucLoopCount].ucWeekNum, 8, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* reference time of sub almanac */
        TAF_XPDS_EncodeSetValue(pstRspGpsCoarLoc->astSatsRec[ucLoopCount].ucTOA, 8, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeMsgDelayMeas(
    TAF_XPDS_REVLINK_RSP_MSG_DELAY_MEAS_STRU          *pstRspMsgDelayMeas,
    VOS_UINT8                                         *pucDestBuf,
    VOS_UINT32                                        *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqMsgDelayMeasReqFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqMsgDelayMeasReqFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_MSG_DELAY_MEAS, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* message sequence number */
    TAF_XPDS_EncodeSetValue(pstRspMsgDelayMeas->ucMsgSeq, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* recieve time */
    TAF_XPDS_EncodeSetValue(pstRspMsgDelayMeas->usRxTime, 9, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* whether recieve to transmit time delay included or not */
    TAF_XPDS_EncodeSetValue(pstRspMsgDelayMeas->ucRxTxDelayIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspMsgDelayMeas->ucRxTxDelayIncl)
    {
        /* recieve to transmit time delay */
        TAF_XPDS_EncodeSetValue(pstRspMsgDelayMeas->ucRxTxDelay, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_EncodeBearingMeas(
    TAF_XPDS_REVLINK_RSP_BEAR_MEAS_STRU    *pstRspBearingMeas,
    VOS_UINT8                              *pucDestBuf,
    VOS_UINT32                             *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqBearingMeasReqFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqBearingMeasReqFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_BEARING_MEAS, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* bearing horizontal */
    TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucBearHor, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* whether data is true north or not */
    TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucTrueNorth, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* horizontal uncertainity */
    TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucHorUncert, 3, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* vertical data included or not */
    TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucVertIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspBearingMeas->ucVertIncl)
    {
        /* bearing vertical */
        TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucBearVerti, 7, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* vertical uncertainity */
        TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucVerUncert, 3, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* pitch and roll correction */
    TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucPitchRollCorr, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* roll angle included */
    TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucRollAngleIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspBearingMeas->ucRollAngleIncl)
    {
        /* roll angle included */
        TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucRollAngle, 8, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* roll uncertainity */
        TAF_XPDS_EncodeSetValue(pstRspBearingMeas->ucRollUncert, 3, &ulTotNumOfBits,
                                &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}



VOS_UINT32 TAF_XPDS_EncodeServSysInfo(
    TAF_XPDS_REVLINK_RSP_SERSYS_INFO_STRU         *pstRspServSysInfo,
    VOS_UINT8                                     *pucDestBuf,
    VOS_UINT32                                    *pulLength
)
{
    VOS_UINT32      ulTotNumOfBits;
    VOS_UINT32      ulCurrIdx;
    VOS_UINT8       ucLoopCount;
    VOS_UINT16      usLength;
    VOS_UINT8       ucUnsolRsp;
    VOS_UINT32      ulLenthFieldStartingBit;


    ulTotNumOfBits          = 0;
    ulCurrIdx               = 0;
    ucUnsolRsp              = 0;
    ulLenthFieldStartingBit = 1;

    /* set response type */
    if (VOS_FALSE == TAF_XPDS_GetReqServSysInfoReqFlag())
    {
        ucUnsolRsp = 1;
    }

    TAF_XPDS_SetReqServSysInfoReqFlag(VOS_FALSE);

    /* unsolicited resp flag */
    TAF_XPDS_EncodeSetValue(ucUnsolRsp, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* response type */
    TAF_XPDS_EncodeSetValue(TAF_XPDS_RL_MSGTYPE_RESP_PROV_SERV_SYS_INFO, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* for  PD_MSG_TYPE 1
        the length field is added 10 bits and ucUnsolRsp added 1 bit,
        so the messagbe encoding starts in 3rd byte 4th bit*/
    ulCurrIdx         = 2;
    ulTotNumOfBits    = 3;

    /* part number in total parts */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucPartNum, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* total number of parts */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucTotalParts, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* mode indicator */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucModeInd, 2, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* pilot id included or not */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucPilotIdIncl, 1, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspServSysInfo->ucPilotIdIncl)
    {
        if (0x00 == pstRspServSysInfo->ucModeInd)
        {
            /* system indicator  */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->usSID, 15, &ulTotNumOfBits,
                                            &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* network indicator  */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->usNID, 16, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* base station indicator  */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->usBaseID, 16, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* MSC identification included or not  */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucMscIdIncl, 1, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            if (VOS_TRUE == pstRspServSysInfo->ucMscIdIncl)
            {
                /* MSC identifier  */
                TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ulMscId, 24, &ulTotNumOfBits,
                                               &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }
        }
        else if (0x01 == pstRspServSysInfo->ucModeInd)
        {

            for (ucLoopCount = 0; ucLoopCount < TAF_XPDS_RL_SECID_SIZE; ucLoopCount++)
            {
                /* MSC identifier  */
                TAF_XPDS_EncodeSetValue(pstRspServSysInfo->aucSectorId[ucLoopCount], 8, &ulTotNumOfBits,
                                               &pucDestBuf[ulCurrIdx], &ulCurrIdx);
            }

        }
        else
        {
            ;
        }

        /* pilot identification age */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucPilotIdAge, 4, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* extended pilot identification included or not */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucExtPilotIdIncl, 1, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if (VOS_TRUE == pstRspServSysInfo->ucExtPilotIdIncl)
        {
            /* Pn sequence offset corrospomding to base station ID */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->usBaseIdPn, 9, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* band class corrosponding to base station ID */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucBaseIdBandCls, 5, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* band class corrosponding to base station ID */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->usBaseIdCdmaFreq, 11, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);

            /* extended pilot identification age */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucExtPilotIdAge, 4, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* active set included or not */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucActiveSetIncl, 1, &ulTotNumOfBits,
                                   &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspServSysInfo->ucActiveSetIncl)
    {
        /* number of active set pilots */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucNumActiveSetPn, 3, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount < pstRspServSysInfo->ucNumActiveSetPn; ucLoopCount++)
        {
            /* number of active set pilots */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ausActiveSetPn[ucLoopCount], 9, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* neighbour list  included or not */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucNeighListIncl, 1, &ulTotNumOfBits,
                                   &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspServSysInfo->ucNeighListIncl)
    {
        /* number of neighbour list */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucNumOfNeighList, 6, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        for (ucLoopCount = 0; ucLoopCount < pstRspServSysInfo->ucNumOfNeighList; ucLoopCount++)
        {
            /* neighbour list PN */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ausNeighbrPn[ucLoopCount], 9, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* BS location included or not */
    TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucBaseLocIncl, 1, &ulTotNumOfBits,
                                   &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    if (VOS_TRUE == pstRspServSysInfo->ucBaseLocIncl)
    {
        /* BS lattitude */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ulBaseLatitude, 22, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* BS longitude */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ulBaseLongitude, 23, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        /* base location information source */
        TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ulBaseLocSrc, 23, &ulTotNumOfBits,
                                       &pucDestBuf[ulCurrIdx], &ulCurrIdx);

        if ((pstRspServSysInfo->ulBaseLocSrc != 0x01)
             && (pstRspServSysInfo->ulBaseLocSrc != 0x02))
        {
            /* base location information source */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucCrseLocUnc, 5, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }

        if ((pstRspServSysInfo->ulBaseLocSrc != 0x00)
             && (pstRspServSysInfo->ulBaseLocSrc != 0x01))
        {
            /* base location information source */
            TAF_XPDS_EncodeSetValue(pstRspServSysInfo->ucBaseLocAge, 4, &ulTotNumOfBits,
                                           &pucDestBuf[ulCurrIdx], &ulCurrIdx);
        }
    }

    /* caluculate and set response parameter length
        -3 because for encoding we added 3 before */
    usLength    = (VOS_UINT16)TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits - 3));

    /* since in PD_MSG_TYPE 1 , the unsol resp flag is included,
        type field is 8 bits, so already processed is 1 in next byte */
    TAF_XPDS_EncodeSetValue(usLength, 10, &ulLenthFieldStartingBit,
                                        &pucDestBuf[1], &ulCurrIdx);

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE((ulTotNumOfBits + 16));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeExtReverseReqs
 功能描述  : Encode Multi Reqs
 输入参数  : TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo
             VOS_UINT8                          *pucMsgBuff
             VOS_UINT32                         *pulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月12日
    作    者   : Arjun A00903922
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_EncodeExtReverseReqs(
    TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulTempLength;

    /* Temperory code - the ctxt content moved here  begin */
    TAF_XPDS_REVLINK_REQ_EXT_LOC_RESP_STRU              stReqExtLocRsp;
    TAF_XPDS_REVLINK_REQ_ENH_BS_ALM_STRU               *pstReqEnhBsAlmn;
    TAF_XPDS_REVLINK_REQ_GEN_AQUI_ASSI_STRU             stReqGenAcqAssist;
    TAF_XPDS_REVLINK_REQ_EXT_GPS_SENS_ASSI_STRU         stReqExtGpsSensAssist;
    TAF_XPDS_REVLINK_REQ_EXT_GPS_EPH_STRU               stReqExtGpsEphi;
    TAF_XPDS_REVLINK_REQ_GPS_NAV_MSGBITS_STRU           stReqExtGpsNavMsgBits;
    TAF_XPDS_REVLINK_REQ_DGPS_ASSI_STRU                 stReqDgpsAssis;

    pstReqEnhBsAlmn = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_REVLINK_REQ_ENH_BS_ALM_STRU));
    if (VOS_NULL_PTR == pstReqEnhBsAlmn)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(&stReqExtLocRsp,         0x00, sizeof(stReqExtLocRsp));
    PS_MEM_SET(pstReqEnhBsAlmn,         0x00, sizeof(TAF_XPDS_REVLINK_REQ_ENH_BS_ALM_STRU));
    PS_MEM_SET(&stReqGenAcqAssist,      0x00, sizeof(stReqGenAcqAssist));
    PS_MEM_SET(&stReqExtGpsSensAssist,  0x00, sizeof(stReqExtGpsSensAssist));
    PS_MEM_SET(&stReqExtGpsEphi,        0x00, sizeof(stReqExtGpsEphi));
    PS_MEM_SET(&stReqExtGpsNavMsgBits,  0x00, sizeof(stReqExtGpsNavMsgBits));
    PS_MEM_SET(&stReqDgpsAssis,         0x00, sizeof(stReqDgpsAssis));
    /* Temperory code - the ctxt content moved here end */

    for (ucIndex = 0; ucIndex < pstEncodeRlInfo->ucNumOfReq; ucIndex++)
    {
        ulTempLength = 0;

        switch (pstEncodeRlInfo->aucReqType[ucIndex])
        {
            case TAF_XPDS_RL_MSGTYPE_REQ_EXT_LOC_RESP:
                TAF_XPDS_EncodeReqExtLocRsp(&stReqExtLocRsp, pucMsgBuff, &ulTempLength);
                break;
            case TAF_XPDS_RL_MSGTYPE_REQ_ENH_BS_ALMN:
                TAF_XPDS_EncodeReqEnhBsAlmanac(pstReqEnhBsAlmn, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_GEN_ACQUI_ASSIST:
                TAF_XPDS_EncodeReqGenAcqAssist(&stReqGenAcqAssist, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_SENS_ASSIST:
                TAF_XPDS_EncodeReqExtGpsSensitivityAssist(&stReqExtGpsSensAssist, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_EPHI:
                TAF_XPDS_EncodeReqExtGpsEphimeris(&stReqExtGpsEphi, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_NAV_MSG_BITS:
                TAF_XPDS_EncodeReqExtGpsNavMsgBits(&stReqExtGpsNavMsgBits, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_REQ_DGPS_ASSIST:
                TAF_XPDS_EncodeReqDgpsAssistance(&stReqDgpsAssis, pucMsgBuff, &ulTempLength);
                break;

            default:
                break;
        }

        pucMsgBuff += ulTempLength;
       *pulLength  += ulTempLength;
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstReqEnhBsAlmn);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeExtReverseRsps
 功能描述  : Encode Multi Rsps
 输入参数  : TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo
             VOS_UINT8                          *pucMsgBuff
             VOS_UINT32                         *pulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月12日
    作    者   : Arjun A00903922
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_EncodeExtReverseRsps(
    TAF_XPDS_ENCODE_RL_INFO_STRU  *pstEncodeRlInfo,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulTempLength;

    /* Temperory code - the ctxt content moved here begin */
    TAF_XPDS_REVLINK_RSP_EXT_LOC_RESP_STRU              stRspExtLocInfo;
    TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU              *pstRspGenLocMeas;
    TAF_XPDS_REVLINK_RSP_EXT_CANC_ACK_STRU              stRspExtCancAck;
    TAF_XPDS_REVLINK_RSP_EXT_REJECT_STRU                stRspExtReject;
    TAF_XPDS_REVLINK_RSP_EXT_MS_INFO_STRU               stRspExtMsInfo;
    TAF_XPDS_REVLINK_RSP_GPS_COAR_LOC_STRU              stRspGpsCoarLoc;
    TAF_XPDS_REVLINK_RSP_MSG_DELAY_MEAS_STRU            stRspMsgDelayMeas;
    TAF_XPDS_REVLINK_RSP_BEAR_MEAS_STRU                 stRspBearingMeas;
    TAF_XPDS_REVLINK_RSP_SERSYS_INFO_STRU               stRspServSysInfo;

    pstRspGenLocMeas = PS_MEM_ALLOC(UEPS_PID_XPDS, sizeof(TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU));
    if (VOS_NULL_PTR == pstRspGenLocMeas)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(&stRspExtLocInfo,    0x00, sizeof(stRspExtLocInfo));
    PS_MEM_SET(pstRspGenLocMeas,    0x00, sizeof(TAF_XPDS_REVLINK_RSP_GEN_LOCMEAS_STRU));
    PS_MEM_SET(&stRspExtCancAck,    0x00, sizeof(stRspExtCancAck));
    PS_MEM_SET(&stRspExtReject,     0x00, sizeof(stRspExtReject));
    PS_MEM_SET(&stRspExtMsInfo,     0x00, sizeof(stRspExtMsInfo));
    PS_MEM_SET(&stRspGpsCoarLoc,    0x00, sizeof(stRspGpsCoarLoc));
    PS_MEM_SET(&stRspMsgDelayMeas,  0x00, sizeof(stRspMsgDelayMeas));
    PS_MEM_SET(&stRspBearingMeas,   0x00, sizeof(stRspBearingMeas));
    PS_MEM_SET(&stRspServSysInfo,   0x00, sizeof(stRspServSysInfo));
    /* Temperory code - the ctxt content moved here end */


    for (ucIndex = 0; ucIndex < pstEncodeRlInfo->ucNumOfResp; ucIndex++)
    {
        ulTempLength   = 0;

        switch (pstEncodeRlInfo->aucRspType[ucIndex])
        {
            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_LOC_RESP:
                TAF_XPDS_EncodeProvExtLocRsp(&stRspExtLocInfo, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_GEN_LOC_MEAS:
                TAF_XPDS_EncodeProvGenLocMeas(pstRspGenLocMeas, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_CANCEL_ACK:
                TAF_XPDS_EncodeProvExtCancelAck(&stRspExtCancAck, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_EXT_REJECT:
                TAF_XPDS_EncodeExtReject(&stRspExtReject, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_MS_INFO:
                TAF_XPDS_EncodeProvExtMsInfo(&stRspExtMsInfo, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_GPS_COARS_LOC_RESP:
                TAF_XPDS_EncodeGpsCoarseLoc(&stRspGpsCoarLoc, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_MSG_DELAY_MEAS:
                TAF_XPDS_EncodeMsgDelayMeas(&stRspMsgDelayMeas, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_BEARING_MEAS:
                TAF_XPDS_EncodeBearingMeas(&stRspBearingMeas, pucMsgBuff, &ulTempLength);
                break;

            case TAF_XPDS_RL_MSGTYPE_RESP_PROV_SERV_SYS_INFO:
                TAF_XPDS_EncodeServSysInfo(&stRspServSysInfo, pucMsgBuff, &ulTempLength);
                break;

            default:
                break;
        }

        pucMsgBuff += ulTempLength;
       *pulLength  += ulTempLength;
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pstRspGenLocMeas);
    return VOS_OK;
}


#endif


VOS_UINT32 TAF_XPDS_EncodeDataBurstMsg(
    TAF_XPDS_DATA_BURST_MSG_STRU    *pstDataBurst,
    VOS_UINT8                       *pucDestBuf,
    VOS_UINT32                      *pulLength
)
{

    VOS_UINT32  ulTotNumOfBits;
    VOS_UINT32  ulCurrIdx;
    VOS_UINT8   ucLoopCount;

    ulTotNumOfBits  = 0;
    ulCurrIdx       = 0;

    /* Msg Number */
    TAF_XPDS_EncodeSetValue(pstDataBurst->ucMsgNum, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* burst type */
    TAF_XPDS_EncodeSetValue(pstDataBurst->ucBurstType, 6, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* Number of msgs */
    TAF_XPDS_EncodeSetValue(pstDataBurst->ucNumMsgs, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    /* total num of bits */
    TAF_XPDS_EncodeSetValue(pstDataBurst->ucNumFields, 8, &ulTotNumOfBits,
                                    &pucDestBuf[ulCurrIdx], &ulCurrIdx);

    for (ucLoopCount = 0; ucLoopCount < pstDataBurst->ucNumFields; ucLoopCount++)
    {
        /* chari fields */
        TAF_XPDS_EncodeSetValue(pstDataBurst->aucData[ucLoopCount], 8, &ulTotNumOfBits,
                                        &pucDestBuf[ulCurrIdx], &ulCurrIdx);
    }

    *pulLength  = TAF_XPDS_RL_BIT_TO_BYTE(ulTotNumOfBits);

    return VOS_OK;


}

/*****************************************************************************
 函 数 名  : TAF_XPDS_EncodeMsIdRec
 功能描述  : TAF_XPDS_EncodeMsIdRec to be fixed in IT2
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_EncodeMsIdRec(
    TAF_XPDS_MS_ID_RECORD_STRU           *pstMsIdRec
)
{
    TAF_XPDS_GetMsIdRecFromCard(pstMsIdRec->aucMsIdRec);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetMsIdRecFromCard
 功能描述  : TAF_XPDS_EncodeMsIdRec to be fixed in IT2
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_GetMsIdRecFromCard(
    VOS_UINT8                          *paucData
)
{
    VOS_UINT8                           aucImsiData[10] = {0};
    VOS_UINT32                          ulBytePos       = 0;
    VOS_UINT32                          ulBitPos        = 0;
    VOS_UINT16                          usMcc           = 0;
    VOS_UINT32                          ulS2            = 0;
    VOS_UINT32                          ulDataLen       = 0;
    VOS_UINT8                           ucMnc           = 0;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;
    VOS_UINT8                          *pucImsiData    = VOS_NULL_PTR;

    /* 得到卡文件中的IMSI */

    enCsimType =  TAF_SDC_GetCsimType();

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        if (VOS_OK != USIMM_GetCachedFile(USIMM_CSIM_EFIMSIM_STR, &ulDataLen, &pucImsiData, USIMM_CDMA_APP))
        {
            XPDS_ERROR_LOG("TAF_XPDS_GetMsIdRecFromCard: USIMM_GetCachedFile ERR");
            return;
        }
    }
    else if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        if (VOS_OK != USIMM_GetCachedFile(USIMM_CDMA_EFIMSIM_STR, &ulDataLen, &pucImsiData, USIMM_CDMA_APP))
        {
            XPDS_ERROR_LOG("TAF_XPDS_GetMsIdRecFromCard: USIMM_GetCachedFile ERR");
            return;
        }
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_GetMsIdRecFromCard: WRONG CARD TYPE");
        return;
    }

    if (VOS_NULL_PTR == pucImsiData)
    {
        XPDS_ERROR_LOG("TAF_XPDS_GetMsIdRecFromCard: pucImsiData null");
        return;
    }

    PS_MEM_CPY(aucImsiData, pucImsiData, 10);

    usMcc       = aucImsiData[9];

    usMcc       = ((aucImsiData[9] & 0x03) << 8) + aucImsiData[8];

    ucMnc       = aucImsiData[6];

    paucData[0] = 0x27;
    ulBitPos   += 8;
    ulBytePos   = 1;

    /* 前面5个BIT 默认是01100 */
    TAF_XPDS_EncodeSetValue(0x0c,
                            5,
                            &ulBitPos,
                            paucData + ulBytePos,
                            &ulBytePos);

    /* MCC 10 BITS */
    TAF_XPDS_EncodeSetValue((VOS_UINT32)usMcc,
                             10,
                             &ulBitPos,
                             paucData + ulBytePos,
                             &ulBytePos);

    /* mnc 7 BITS */
    TAF_XPDS_EncodeSetValue((VOS_UINT32)ucMnc,
                             7,
                             &ulBitPos,
                             paucData + ulBytePos,
                             &ulBytePos);

    ulS2        = ((aucImsiData[2] & 0x03) << 8) + aucImsiData[1];

    /* s2 10 BITS */
    TAF_XPDS_EncodeSetValue(ulS2,
                            10,
                            &ulBitPos,
                            paucData + ulBytePos,
                            &ulBytePos);

    paucData[5] = aucImsiData[5];
    paucData[6] = aucImsiData[4];
    paucData[7] = aucImsiData[3];

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

