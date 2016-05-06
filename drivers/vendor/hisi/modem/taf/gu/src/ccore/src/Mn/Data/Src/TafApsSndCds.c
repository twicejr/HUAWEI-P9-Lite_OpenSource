/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndCds.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年09月18日
  最近修改   :
  功能描述   : TAF APS模块发送消息给CDS的函数实现文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月18日
    作    者   : y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "ApsCdsInterface.h"
#include "TafApsComFunc.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsCtx.h"
#include "ehsm_aps_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_CDS_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_APS_SndCdsSndBuffDataInd
 功能描述  : 发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndCdsSndBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *pstSndBuffData = VOS_NULL_PTR;

    pstSndBuffData = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstSndBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsSndBuffDataInd: Memory alloc failed");
        return;
    }

    pstSndBuffData->ulReceiverPid       = UEPS_PID_CDS;
    pstSndBuffData->enMsgId             = ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND;
    pstSndBuffData->usOpId              = 0;
    pstSndBuffData->ucRabId             = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndBuffData);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndCdsFreeBuffDataInd
 功能描述  : 发送ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndCdsFreeBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *pstFreeBuffData = VOS_NULL_PTR;

    pstFreeBuffData = (APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstFreeBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsFreeBuffDataInd: Memory alloc failed");
        return;
    }

    pstFreeBuffData->ulReceiverPid      = UEPS_PID_CDS;
    pstFreeBuffData->enMsgId            = ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND;
    pstFreeBuffData->usOpId             = 0;
    pstFreeBuffData->ucRabId            = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstFreeBuffData);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_SndCdsModeChangeInd
 功能描述  : 通知CDS当前的网络模式
 输入参数  : enMode   - 网络模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndCdsModeChangeInd(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{
    APS_CDS_MODE_CHANGE_IND_STRU       *pstSndMsg = VOS_NULL_PTR;
    APS_CDS_MODE_ENUM_UINT32            enMode;

    switch (enCurrCdataServiceMode)
    {
        case TAF_APS_RAT_TYPE_1X:
            enMode = APS_CDS_MODE_1X;
            break;
        case TAF_APS_RAT_TYPE_HRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            enMode = APS_CDS_MODE_GU;
            break;
        case TAF_APS_RAT_TYPE_LTE:
            enMode = APS_CDS_MODE_LTE;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Mode Error");
            return;
    }

    pstSndMsg = (APS_CDS_MODE_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_MODE_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Memory alloc failed");
        return;
    }

    pstSndMsg->ulReceiverPid    = UEPS_PID_CDS;
    pstSndMsg->enMsgId          = ID_APS_CDS_MODE_CHANGE_IND;
    pstSndMsg->usOpId           = 0;
    pstSndMsg->enMode           = enMode;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    return;

}


/*****************************************************************************
 函 数 名  : TAF_APS_GetCdataBearStatus
 功能描述  : 获取1X模式下的承载的状态
 输入参数  : VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : y00213812
    修改内容   : 新生成函数

  2.日    期   : 2015年1月6日
    作    者   : Y00213812
    修改内容   : 修改APS状态，区分PPP在A核或C核的处理

  3.日    期   : 2015年10月20日
    作    者   : y00322978
    修改内容   : 查询当前状态封装一个公共函数
*****************************************************************************/
APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatus(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                                               ucPdpId;
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8                    enBearStatus;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_CDATA_BEAR_STATUS_INACTIVE;
    }

    enBearStatus = AT_APS_ConvertPsCdataStatusToCsdCdataStatus(TAF_PS_GetCdataBearStatus(ucPdpId));

    return enBearStatus;
}


/*****************************************************************************
 函 数 名  : TAF_APS_MapPdnIdToRabId
 功能描述  : PDN ID映射为RABID
 输入参数  : VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_MapRabIdToPdnId(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_PDN_ID;
    }

    return TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
}

/*****************************************************************************
 函 数 名  : TAF_APS_MapPdnIdToRabId
 功能描述  : PDN ID 映射为RAB ID
 输入参数  : VOS_UINT8                           ucPndId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_MapPdnIdToRabId(
    VOS_UINT8                           ucPdnId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByPndId(ucPdnId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_RAB_ID;
    }

    return TAF_APS_GetPdpEntNsapi(ucPdpId);
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


