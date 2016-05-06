/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsUlProc.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : CDS上行处理
  函数列表   :

  修改历史   :
  1.日    期   : 2011年3月9日
    作    者   : l00164359
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsUlProc.h"
#include "CdsDebug.h"
#include "CdsMsgProc.h"
#include "CdsInterface.h"
#include "QosFcOm.h"
#include "CdsSoftFilter.h"
#include "CdsBastetProc.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_UL_PROC_C
/*lint +e767*/

extern VOS_UINT32 CDS_IpFragmentProc( VOS_UINT8       *pucEpsbID,
                                          TTF_MEM_ST      *pstIpPkt,
                                          const IPF_RESULT_STRU *pstIpfRslt,
                                          const CDS_ENTITY_STRU  *pstCdsEntity);

extern VOS_VOID CDS_LPDCP_TriggerUlDataProc(VOS_VOID);

extern VOS_VOID TL_OM_CdsStatInfoIndRpt(VOS_VOID);
/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CDS_ULStorePkt
 功能描述  : 缓存上行IP包
 输入参数  : CDS_ENTITY_STRU *pstCdsEntity,
             TTF_MEM_ST  *pstIpPkt

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
/*lint -e960*/

VOS_VOID CDS_ULStorePkt(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    /*IP包存入上行缓存队列*/
    if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue, pstIpPkt))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_BUFF_EN_QUE_FAIL_NUM(1);
        return;
    }

    CDS_DBG_UL_BUFF_EN_QUE_SUCC_NUM(1);

    /*启动保护定时器*/
    if (PS_SUCC != CDS_StartTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_ULStorePkt : Start UL DATA PROCTECT timer Fail.Modem Id",pstCdsEntity->usModemId);
        CDS_PRINT_ERROR1(CDS_ULStorePkt_ENUM,CDS_PRINT_START_TIMER_FAIL,pstCdsEntity->usModemId);
        return;
    }

    return;
}


#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)

extern VOS_VOID L2_UlAppThrStatProc(VOS_UINT32 ulLength);

/*****************************************************************************
 函 数 名  : CDS_UlLteDispatchData
 功能描述  : L模按EPSBID分发数据,由用户保证输入合法
 输入参数  : VOS_UINT8 ucEpsbID,
             TTF_MEM_ST *pstIpPkt,
             CDS_ENTITY_STRU *pstCdsEntity

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2012年04月06日
      作    者   : y00151394
      修改内容   : 规避GU MMC问题，只统计ACTIVE状态，见问题单DTS2012033006788.

*****************************************************************************/
VOS_VOID CDS_UlLteDispatchData(VOS_UINT8 ucEpsbID,TTF_MEM_ST *pstIpPkt,CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT8                                 ucDrbId;
    CDS_ERABM_TRANSFER_RESULT_ENUM_UINT32     enERabmStatus;
    CDS_LPDCP_DATA_STRU                       stLPdcpData;

    CDS_ASSERT((ucEpsbID >= CDS_NAS_MIN_BEARER_ID)&&(ucEpsbID <= CDS_NAS_MAX_BEARER_ID));
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    L2_UlAppThrStatProc(pstIpPkt->usUsed);

    /*DRB 状态*/
    enERabmStatus = CDS_ERABM_GetDrbId(ucEpsbID,&ucDrbId);
    switch(enERabmStatus)
    {
    case CDS_ERABM_TRANSFER_RESULT_SUCC:

        /*上行流量统计-规避GU MMC问题，只统计ACTIVE状态下行流量*/
        CDS_ULDataFlowStats(ucEpsbID, pstIpPkt->usUsed,pstCdsEntity);

        stLPdcpData.ucRbId   = ucDrbId;
        stLPdcpData.ulSduLen = pstIpPkt->usUsed;
        stLPdcpData.pstSdu   = pstIpPkt;
        CDS_LPDCP_DataReq(&stLPdcpData);
        CDS_DBG_UL_LTE_SEND_TO_LPDCP_NUM(1);
        break;

    case CDS_ERABM_TRANSFER_RESULT_IDLE:
        if (PS_FALSE == pstCdsEntity->ulServiceReqFlg)
        {
            CDS_ERabmSerivceRequestNotify(ucEpsbID);
            pstCdsEntity->ulServiceReqFlg = PS_TRUE;
        }

        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_LTE_SAVE_PKT_NUM(1);
        break;

    case CDS_ERABM_TRANSFER_RESULT_DRB_SUSPEND:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_LTE_SAVE_PKT_NUM(1);
        break;

    default:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_LTE_ERABM_STATE_ERROR(1);
        break;

    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_LTEPktProc
 功能描述  : LTE模处理IP包
 输入参数  : pstCdsEntity: CDS上行实体
             pstIpPkt :    上行IP包

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_LTEPktProc(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    VOS_UINT8                                 ucEpsbId;
    IPF_RESULT_STRU                          *pstIpfRlst;
    VOS_UINT16                                usFilterResult;

    /*获得到EPSBID*/
    usFilterResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRlst = (IPF_RESULT_STRU *)&(usFilterResult);
    ucEpsbId = (VOS_UINT8)(pstIpfRlst->usBearedId);
    /*lint -e960*/
    if ((CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfRlst->usIpSegInfo)
         &&(PS_SUCC != CDS_IpFragmentProc(&ucEpsbId, pstIpPkt,pstIpfRlst,pstCdsEntity)))
    {
        /*IP分片包*/
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_LTE_PROC_IPSEG_FAIL_NUM(1);
        return;
    }
    /*lint +e960*/

    /* 流控丢包 */
    if(QosFc_IsDiscard(ucEpsbId,pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        FC_DBG_ULLTE_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_UL_LTE_FC_FREE_PKT_NUM(1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD);
        return;
    }

    CDS_UlLteDispatchData(ucEpsbId,pstIpPkt,pstCdsEntity);

    return;
}

#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 函 数 名  : CDS_APS_GetCdataBearStatus
 功能描述  : CDS封装APS接口

 输入参数  : VOS_UINT8 ucRabId, CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 enCDMABearStatus
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年10月27日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 CDS_APS_GetCdataBearStatus(VOS_UINT8 ucRabId, CDS_ENTITY_STRU *pstCdsEntity)
{
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8             enCDMABearStatus;

    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        enCDMABearStatus = TAF_APS_GetCdataBearStatus(ucRabId);
    }
    else if (MODEM_ID_1 == pstCdsEntity->usModemId)
    {
        enCDMABearStatus = I1_TAF_APS_GetCdataBearStatus(ucRabId);
    }
    else
    {
        enCDMABearStatus = I2_TAF_APS_GetCdataBearStatus(ucRabId);
    }

    return enCDMABearStatus;
}

/*****************************************************************************
 函 数 名  : CDS_APS_MapRabIdToPdnId
 功能描述  : CDS封装APS接口

 输入参数  : VOS_UINT8 ucRabId, VOS_UINT16 usModemId
 输出参数  : 无
 返 回 值  : VOS_UINT8 ucPdnId
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年10月27日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CDS_APS_MapRabIdToPdnId(VOS_UINT8 ucRabId, VOS_UINT16 usModemId)
{
    VOS_UINT8                                      ucPdnId;

    if (MODEM_ID_0 == usModemId)
    {
        ucPdnId = TAF_APS_MapRabIdToPdnId(ucRabId);
    }
    else if (MODEM_ID_1 == usModemId)
    {
        ucPdnId = I1_TAF_APS_MapRabIdToPdnId(ucRabId);
    }
    else
    {
        ucPdnId = I2_TAF_APS_MapRabIdToPdnId(ucRabId);
    }

    return ucPdnId;
}

/*****************************************************************************
 函 数 名  : CDS_UlCDMADataReq
 功能描述  : CDMA 按ucRabId分发数据,由用户保证输入合法
 输入参数  : VOS_UINT8 ucRabId,
             TTF_MEM_ST *pstIpPkt,

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年12月30日
      作    者   : l00304941
      修改内容   : 新生成函数
    2.日    期   : 2015年06月12日
      作    者   : l00304941
      修改内容   : 新增HRPD接口

*****************************************************************************/
VOS_VOID CDS_UlCDMADataReq(VOS_UINT8 ucRabId,TTF_MEM_ST *pstIpPkt,CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_CDMA_1X_TRANS_DATA_STRU          st1xUlData;
    CDS_CDMA_HRPD_TRANS_DATA_STRU        stHrpdUlData;
    VOS_UINT8                            ucPdnId;

    ucPdnId = CDS_APS_MapRabIdToPdnId(ucRabId, pstCdsEntity->usModemId);
    if (CDS_MAX_PDN_ID < ucPdnId)
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        return;
    }

    if (APS_CDS_MODE_1X == pstCdsEntity->enRanMode)
    {
        st1xUlData.ucPdnId   = ucPdnId;
        st1xUlData.ulSduLen  = pstIpPkt->usUsed;
        st1xUlData.pstSdu    = pstIpPkt;
        PPPC_1X_PullPacketEvent(&st1xUlData);
    }
    else
    {
        stHrpdUlData.ucPdnId   = ucPdnId;
        stHrpdUlData.ulSduLen  = pstIpPkt->usUsed;
        stHrpdUlData.pstSdu    = pstIpPkt;
        PPPC_HRPD_PullPacketEvent(&stHrpdUlData);
    }

    CDS_DBG_UL_CDMA_SEND_TO_PPP_NUM(pstCdsEntity->enRanMode, 1);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_UlCDMARlpDispatchData
 功能描述  : CDMA 按ucRabId分发数据,由用户保证输入合法
 输入参数  : VOS_UINT8 ucRabId,
             TTF_MEM_ST *pstIpPkt,
             CDS_ENTITY_STRU *pstCdsEntity

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年12月30日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_UlCDMADispatchData(VOS_UINT8 ucRabId,TTF_MEM_ST *pstIpPkt,CDS_ENTITY_STRU *pstCdsEntity)
{
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8             enCDMABearStatus;
    VOS_UINT32                                       ulRanMode;

    CDS_ASSERT((ucRabId >= CDS_NAS_MIN_BEARER_ID)&&(ucRabId <= CDS_NAS_MAX_BEARER_ID));
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    L2_UlAppThrStatProc(pstIpPkt->usUsed);
    ulRanMode = pstCdsEntity->enRanMode;

    /*获取RAB 状态*/
    enCDMABearStatus = CDS_APS_GetCdataBearStatus(ucRabId, pstCdsEntity);

    switch (enCDMABearStatus)
    {
    case APS_CDS_CDATA_BEAR_STATUS_ACTIVE:

        /*上行流量统计*/
        CDS_ULDataFlowStats(ucRabId, pstIpPkt->usUsed, pstCdsEntity);

        CDS_UlCDMADataReq(ucRabId, pstIpPkt, pstCdsEntity);
        break;

    case APS_CDS_CDATA_BEAR_STATUS_IDLE:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);

        /*通知APS建链*/
        CDS_APSServiceRequestNotify(pstCdsEntity, ucRabId);

        CDS_DBG_UL_CDMA_SAVE_PKT_NUM(ulRanMode, 1);
        break;

    case APS_CDS_CDATA_BEAR_STATUS_SUSPEND:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);

        CDS_DBG_UL_CDMA_SAVE_PKT_NUM(ulRanMode, 1);
        break;

    case APS_CDS_CDATA_BEAR_STATUS_INACTIVE:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);

        CDS_DBG_UL_CDMA_RAB_STATE_INACTIVE(ulRanMode, 1);
        break;

    default:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);

        CDS_DBG_UL_CDMA_RAB_STATE_ERROR(ulRanMode, 1);
        break;

    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_CDMAPktProc
 功能描述  : CDMA处理PPP帧
 输入参数  : pstCdsEntity: CDS上行实体
             pstIpPkt :    上行PPP帧

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_CDMAPktProc(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    VOS_UINT8                                     ucRabId;

    /*RABID:当前直接使用用户域中的RABID*/
    ucRabId = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

    /* 流控丢包 */
    if(QosFc_IsDiscard(ucRabId,pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        FC_DBG_ULCDMA_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_UL_CDMA_FC_FREE_PKT_NUM(pstCdsEntity->enRanMode, 1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD);
        return;
    }

    CDS_UlCDMADispatchData(ucRabId,pstIpPkt,pstCdsEntity);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_CheckUlBuffDataToSend
 功能描述  : 检查CDS实体上行缓存队列中是否有对应Rab的数据
 输入参数  :

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月15日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_CheckUlBuffDataToSend(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucRabId)
{
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          ulQueCnt;
    VOS_UINT32                          ucDataExist = PS_FALSE;
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT8                           ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return PS_FALSE;
    }

    /*遍历队列*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);

    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstTtfMem);

        /*检查指定承载*/
        if (ucPktRabId == ucRabId)
        {
            ucDataExist = PS_TRUE;
        }

        /*重新入队*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstTtfMem))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    return ucDataExist;
}

/*****************************************************************************
 函 数 名  : CDS_CheckUlDataToSend
 功能描述  : CDS检查是否有上行数据待发送
 输入参数  :

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月15日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_CheckUlDataToSend(MODEM_ID_ENUM_UINT16 enModemId,VOS_UINT8 ucRabId)
{
    CDS_ENTITY_STRU                               *pstCdsEntity;

    /* 根据ModemId 获得CDS实体指针*/
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_CheckUlDataToSend : Get CDS Entity Fail.ModemId",
                       enModemId);
        CDS_PRINT_ERROR1(CDS_CheckUlDataToSend_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        return PS_FALSE;
    }

    /*上行缓存不为空*/
    return CDS_CheckUlBuffDataToSend(pstCdsEntity,ucRabId);

}
#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_MULTI_MODEM)
/*****************************************************************************
 函 数 名  : I1_NAS_RABM_GetRabIdStatus
 功能描述  : 为了后续处理一致，当单Modem时，对Modem1上函数进行打桩处理。
 输入参数  : VOS_UINT8 ucRabId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 I1_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return RABM_RAB_STATUS_BUTT;
}


/*****************************************************************************
 函 数 名  : I1_NAS_RABM_UL_DataReq
 功能描述  : 为了后续处理一致，当单Modem时，对Modem1上函数进行打桩处理。
 输入参数  : CDS_RABM_TRANS_DATA_STRU *pstUlData

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID I1_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData)
{
    if (VOS_NULL_PTR == pstUlData)
    {
        return;
    }

    TTF_MemFree(UEPS_PID_CDS,pstUlData->pstSdu);
    return;
}

/*****************************************************************************
 函 数 名  : I1_TAF_APS_MapRabIdToPdnId
 功能描述  : 为了后续处理一致，当单Modem时，对Modem1上函数进行打桩处理。
 输入参数  : VOS_UINT8 ucRabId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 I1_TAF_APS_MapRabIdToPdnId(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return APS_CDS_INVALID_PDN_ID;
}

/*****************************************************************************
 函 数 名  : I1_TAF_APS_GetCdataBearStatus
 功能描述  : 为了后续处理一致，当单Modem时，对Modem1上函数进行打桩处理。
 输入参数  : VOS_UINT8 ucRabId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 I1_TAF_APS_GetCdataBearStatus(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return APS_CDS_CDATA_BEAR_STATUS_BUTT;
}

#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_MODEM_2)

/*****************************************************************************
 函 数 名  : I2_NAS_RABM_GetRabIdStatus
 功能描述  : 为了后续处理一致，当单Modem时，对Modem2上函数进行打桩处理。
 输入参数  : VOS_UINT8 ucRabId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 I2_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return RABM_RAB_STATUS_BUTT;
}


/*****************************************************************************
 函 数 名  : I2_NAS_RABM_UL_DataReq
 功能描述  : 为了后续处理一致，当单Modem时，对Modem2上函数进行打桩处理。
 输入参数  : CDS_RABM_TRANS_DATA_STRU *pstUlData

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID I2_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData)
{
    if (VOS_NULL_PTR == pstUlData)
    {
        return;
    }

    TTF_MemFree(UEPS_PID_CDS,pstUlData->pstSdu);
    return;
}

/*****************************************************************************
 函 数 名  : I2_TAF_APS_MapRabIdToPdnId
 功能描述  : 为了后续处理一致，当单Modem时，对Modem2上函数进行打桩处理。
 输入参数  : VOS_UINT8 ucRabId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 I2_TAF_APS_MapRabIdToPdnId(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return APS_CDS_INVALID_PDN_ID;
}

/*****************************************************************************
 函 数 名  : I2_TAF_APS_GetCdataBearStatus
 功能描述  : 为了后续处理一致，当单Modem时，对Modem2上函数进行打桩处理。
 输入参数  : VOS_UINT8 ucRabId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月7日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 I2_TAF_APS_GetCdataBearStatus(VOS_UINT8 ucRabId)
{
    (VOS_VOID)ucRabId;
    return APS_CDS_CDATA_BEAR_STATUS_BUTT;
}

#endif

/*****************************************************************************
 函 数 名  : CDS_GUGetRabIdStatus
 功能描述  : CDS对GU接口函数进行封装，根据ModemId调用不同的接口函数.
 输入参数  :

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 CDS_GUGetRabIdStatus(VOS_UINT8  ucRabId, VOS_UINT16 usModemId)
{
    if (MODEM_ID_0 == usModemId)
    {
        return NAS_RABM_GetRabIdStatus(ucRabId);
    }
    else if (MODEM_ID_1 == usModemId)
    {
        return I1_NAS_RABM_GetRabIdStatus(ucRabId);
    }
    else if (MODEM_ID_2 == usModemId)
    {
        return I2_NAS_RABM_GetRabIdStatus(ucRabId);
    }
    else
    {
        return RABM_RAB_STATUS_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : CDS_GUGetRabIdStatus
 功能描述  : CDS对GU接口函数进行封装，根据ModemId调用不同的接口函数.
 输入参数  :

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_GUUlDataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData, VOS_UINT16 usModemId)
{
    CDS_ASSERT(VOS_NULL_PTR != pstUlData);

    if (MODEM_ID_0 == usModemId)
    {
        NAS_RABM_UL_DataReq(pstUlData);
    }
    else if (MODEM_ID_1 == usModemId)
    {
        I1_NAS_RABM_UL_DataReq(pstUlData);
    }
    else if (MODEM_ID_2 == usModemId)
    {
        I2_NAS_RABM_UL_DataReq(pstUlData);
    }
    else
    {
        /*异常，释放内存*/
        TTF_MemFree(UEPS_PID_CDS, pstUlData->pstSdu);
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_UlGUDispatchData
 功能描述  : GU模按RABID分发数据,由用户保证输入合法
 输入参数  : VOS_UINT8 ucRabId,
             TTF_MEM_ST *pstIpPkt,
             CDS_ENTITY_STRU *pstCdsEntity

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_UlGUDispatchData(VOS_UINT8 ucRabId, TTF_MEM_ST *pstIpPkt, CDS_ENTITY_STRU *pstCdsEntity)
{
    RABM_RAB_STATUS_ENUM_UINT32      enRabStatus;
    CDS_RABM_TRANS_DATA_STRU         stRabmData;
    VOS_UINT16                       usModemId;

    CDS_ASSERT((ucRabId >= CDS_NAS_MIN_BEARER_ID)&&(ucRabId <= CDS_NAS_MAX_BEARER_ID));
    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);

    /*RAB 状态*/
    usModemId = pstCdsEntity->usModemId;
    enRabStatus = CDS_GUGetRabIdStatus(ucRabId, usModemId);
    switch(enRabStatus)
    {
    case RABM_RAB_STATUS_ACTIVE:

        /*上行流量统计*/
        CDS_ULDataFlowStats(ucRabId, pstIpPkt->usUsed,pstCdsEntity);

        stRabmData.ucRabId  = ucRabId;
        stRabmData.ulSduLen = pstIpPkt->usUsed;
        stRabmData.pstSdu   = pstIpPkt;
        CDS_GUUlDataReq(&stRabmData,usModemId);
        CDS_DBG_UL_GU_SEND_TO_RABM_NUM(1);
        CDS_DBG_MODEM_UL_GU_SEND_TO_RABM_NUM(usModemId,1);
        break;

    case RABM_RAB_STATUS_IDLE:
        CDS_RabmSerivceRequestNotify(ucRabId,pstCdsEntity);
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_GU_SAVE_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_SAVE_PKT_NUM(usModemId,1);
        break;

    case RABM_RAB_STATUS_SUSPEND:
        CDS_ULStorePkt(pstCdsEntity, pstIpPkt);
        CDS_DBG_UL_GU_SAVE_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_SAVE_PKT_NUM(usModemId,1);
        break;

    default:
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_GU_RABM_STATE_ERROR(1);
        CDS_DBG_MODEM_UL_GU_RABM_STATE_ERROR(usModemId,1);
        break;

    }

    return;
}



/*****************************************************************************
 函 数 名  : CDS_GUPktProc
 功能描述  : GU模处理IP包
 输入参数  : pstCdsEntity: CDS上行实体
             pstIpPkt :    上行IP包

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_GUPktProc(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST  *pstIpPkt)
{
    VOS_UINT8                        ucRabId;
    VOS_UINT16                       usFilterResult;
    IPF_RESULT_STRU                 *pstIpfRlst;


    /* 语音优先生效后丢弃上行数据包 */
    if (PS_TRUE == CDS_GET_VOICEPREFER_ACT_FLAG(pstCdsEntity))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        return;
    }

    usFilterResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRlst = (IPF_RESULT_STRU *)&(usFilterResult);
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfRlst->usIpSegInfo)
    {
        (VOS_VOID)CDS_IpFragmentProc(&ucRabId, pstIpPkt,pstIpfRlst,pstCdsEntity);
    }

    /*RABID:当前GU未实现多承载，也为做IP分片处理，当前直接使用用户域中的RABID*/
    ucRabId = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

    /* 流控丢包 */
    if(QosFc_IsDiscard(ucRabId,pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        FC_DBG_ULGU_CDS_DISCARD_PKT_STAT(1);
        CDS_DBG_UL_GU_FC_FREE_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_FC_FREE_PKT_NUM(pstCdsEntity->usModemId,1);
        CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD);
        return;
    }

    CDS_UlGUDispatchData(ucRabId,pstIpPkt,pstCdsEntity);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_UlDispatchDataByRanMode
 功能：上行数据按接入模式分发处理，调用者保证输入合法
 输入参数  : CDS_ENTITY_STRU *pstCdsEntity,
             TTF_MEM_ST *pstIpPkt

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_UlDispatchDataByRanMode(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt)
{

    CDS_DBG_UL_AS_RX_IP_PKT_NUM(1);

    /* 流量统计 */
    CDS_ULFlowAdd(pstIpPkt->usUsed);

    /*测试需求，内存直接释放*/
    if (PS_TRUE == pstCdsEntity->ulULPktDiscardFlg)
    {
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_DIRECT_FREE_PKT_NUM(1);
        return;
    }

    /*按接入模式分发*/
    switch(pstCdsEntity->enRanMode)
    {
    case MMC_CDS_MODE_NULL:
        CDS_ULStorePkt(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_NULL_RX_PKT_NUM(1);
        break;

    case MMC_CDS_MODE_GU:
        CDS_GUPktProc(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_GU_RX_PKT_NUM(1);
        CDS_DBG_MODEM_UL_GU_FC_FREE_PKT_NUM(pstCdsEntity->usModemId,1);
        break;

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    case MMC_CDS_MODE_LTE:
        CDS_LTEPktProc(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_LTE_RX_PKT_NUM(1);
        break;
#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
    case APS_CDS_MODE_1X:
    case APS_CDS_MODE_EVDO:
        CDS_CDMAPktProc(pstCdsEntity,pstIpPkt);
        CDS_DBG_UL_CDMA_RX_PKT_NUM(pstCdsEntity->enRanMode, 1);
        break;
#endif
    default :
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        CDS_DBG_UL_RAN_MODE_ERROR_FREE_NUM(1);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_UlDispatchDataByRanMode : Current Ran Mode Error.Ran Mode :",pstCdsEntity->enRanMode);
        CDS_PRINT_ERROR1(CDS_UlDispatchDataByRanMode_ENUM,CDS_PRINT_GET_ACCESS_MODE_FAIL,pstCdsEntity->enRanMode);
        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_PreProcUlRD
 功能描述  : 预先处理RD，根据过滤结果将RD进行分类。对IP分片，将本地处理的结果
             放到IPF Result的usBearedId中
 输入参数  : IPF_RD_DESC_S *pstRdDesc ，调用者保证参数非NULL

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
CDS_UL_IP_PKT_TYPE_ENUM_UINT32 CDS_PreProcUlRD(TTF_MEM_ST *pstIpPkt)
{
    IPF_RESULT_STRU       *pstIpfRslt;
    VOS_UINT16             usIpfResult;

    usIpfResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRslt  = (IPF_RESULT_STRU *)&usIpfResult;

    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfRslt->usIpSegInfo)
    {
        /*IP分片处理,将IP分片包走到缺省承载*/
        CDS_DBG_UL_IPF_RX_IP_SEG_NUM(1);
        return CDS_UL_IP_PKT_TYPE_NORMAL;
    }

    /*根据BID进行分类*/
    if ((pstIpfRslt->usBearedId >= CDS_UL_IPF_BEARER_ID_EPSBID5)
        && (pstIpfRslt->usBearedId <= CDS_UL_IPF_BEARER_ID_EPSBID15))
    {
        /*[5,15]，正常IP包*/
        CDS_DBG_UL_IPF_RX_IP_PKT_NUM(1);
        return CDS_UL_IP_PKT_TYPE_NORMAL;
    }
    else if ( (CDS_UL_IPF_BEARER_ID_DHCPV4 <= pstIpfRslt->usBearedId)
            &&(CDS_UL_IPF_BEARER_ID_LL_FF >= pstIpfRslt->usBearedId))
    {
        /*[16,21],NDIS*/
        CDS_DBG_UL_IPF_RX_NDIS_PKT_NUM(1);
        return CDS_UL_IP_PKT_TYPE_NDIS;
    }
    else
    {
        if (usIpfResult & CDS_UL_IPF_RESULT_PKT_ERROR_MASK)
        {
            /*对于IPF指示IP包存在错误的，将其发送到对应的缺省承载上；为了规避NAT KEEP-ALIVE问题*/
            CDS_DBG_UL_IPF_FILTER_ERROR_NUM(1);
            CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_IPF_ERR);
            usIpfResult = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);
            CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt, usIpfResult);
            return CDS_UL_IP_PKT_TYPE_NORMAL;
        }
        else
        {
            /*对于IPF指示IP正确但没有匹配到正确承载上的，直接丢弃；俄罗斯准入问题*/
            CDS_DBG_UL_IPF_FILTER_ERROR_NUM(1);
            CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_IPF_ERR);
            return CDS_UL_IP_PKT_TYPE_ERROR;
        }
    }
}

/*****************************************************************************
 函 数 名  : CDS_UlProcIpfResult
 功能描述  : 处理上行IPF过滤结果
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_UlProcIpfResult(VOS_VOID)
{
    VOS_UINT32                            ulRdNum = IPF_ULRD_DESC_SIZE;
    VOS_UINT32                         ulCnt;
    IPF_RD_DESC_S                     *pstRD;
    CDS_UL_IP_PKT_TYPE_ENUM_UINT32     enIpType;
    IPF_RD_DESC_S                     *pstUlRdBuff;
    CDS_ENTITY_STRU                   *pstCdsEntity;
    VOS_UINT16                         usModemId;
    TTF_MEM_ST                        *pstIpPkt;
    VOS_UINT8                          ucPktType;

    /*拷贝IPF RD结果*/
    pstUlRdBuff = CDS_GET_UL_RD_BUFF();
    CDS_ASSERT(VOS_NULL_PTR != pstUlRdBuff);

    LDRV_IPF_GET_ULRD(&ulRdNum,pstUlRdBuff);
    if (0 == ulRdNum)
    {
        /*NO RD*/
        return;
    }

    /*增加统计计数*/
    CDS_DBG_UL_IPF_RX_RD_NUM(ulRdNum);
    Cds_LomTraceRcvUlData();

    /*处理RD*/
    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt ++)
    {
        pstRD = &(pstUlRdBuff[ulCnt]);

        /*转换为TTF内存*/
        pstIpPkt = CDS_RdTransferTtfMem(pstRD);
        if (VOS_NULL_PTR == pstIpPkt)
        {
            CDS_DBG_UL_IPF_TRANS_MEM_FAIL_NUM(1);
            continue;
        }

        /*获得对应Modem实体指针*/
        usModemId = CDS_UL_GET_MODEMID_FROM_TTF(pstIpPkt);

        ucPktType = CDS_UL_GET_PKT_TYPE_FROM_TTF(pstIpPkt);

        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_UL_LTE_IP_PKT_HOOK(pstIpPkt);

        pstCdsEntity = CDS_GetCdsEntity(usModemId);
        if (VOS_NULL_PTR == pstCdsEntity)
        {
            TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
            CDS_DBG_UL_IPF_MODEMID_ERROR_NUM(1);
            continue;
        }

        /*环回模式，直接丢弃*/
        if (PS_TRUE == pstCdsEntity->ulTestModeFlg)
        {
            TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
            CDS_DBG_UL_IPF_FREE_PKT_IN_LB(1);
            continue;
        }

        /*对RD进行分类处理*/
        enIpType = CDS_PreProcUlRD(pstIpPkt);
        if (CDS_UL_IP_PKT_TYPE_NORMAL == enIpType)
        {
            /*按模式分发*/
            /*有其他非bastet模块的上行数据发送，需要通知bastet模块*/
            CDS_BstSendTxInd();
            CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);
        }
        else if (CDS_UL_IP_PKT_TYPE_NDIS == enIpType)
        {
            /*将数据发送到ADS*/
            CDS_UlDataIndToAds(pstIpPkt);
        }
        else
        {
            if (ADS_CDS_IPF_PKT_TYPE_PPP == ucPktType)
            {
                CDS_UlDispatchDataByRanMode(pstCdsEntity, pstIpPkt);
            }
            else
            {
                /* 释放内存 */
                TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            }
        }
    }

    /*为ADQ补充内存，防止未执行完被切走*/
    CDS_AllocMemForAdq();

    /*所有RD处理完之后，通过发送事件触发接入层进行上行数传处理*/
    CDS_TriggerUlProcOnFinalRD();

    return;
}

/*****************************************************************************
 函 数 名  : CDS_TriggerUlProcOnFinalRD
 功能描述  : 上行最后一个RD处理完之后，通过发送事件触发上行数传
 输入参数  : VOS_VOID


 输出参数  : None
 返 回 值  : VOS_VOID


 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年4月22日
      作    者   : h00218138
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_TriggerUlProcOnFinalRD(VOS_VOID)
{
    CDS_ENTITY_STRU *pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);

    if(VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_TriggerUlProcOnFinalRD : CDS_GetCdsEntity return NULL");
        CDS_PRINT_ERROR(CDS_TriggerUlProcOnFinalRD_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return;
    }

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    if(MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode)
    {
        CDS_LPDCP_TriggerUlDataProc();
    }
#endif

    if(MMC_CDS_MODE_GU == pstCdsEntity->enRanMode)
    {
        NAS_RABM_SetFinIpInRdFlag(PS_TRUE);
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ClearUlBuffData
 功能描述  : 清空上行缓存数据.调用者保证入参正确性.
 输入参数  : CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ClearUlBuffData(CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32           ulCnt;
    TTF_MEM_ST          *pstTtfMem;

    /*停止保护定时器*/
    CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);

    /*清除Service Request标志位*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*重置GU SR标志*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*遍历队列*/
    for(ulCnt = 0; ulCnt < CDS_UL_IDLE_QUE_SIZE; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
        CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_SendUlBuffData
 功能描述  : 发送上行缓存数据.调用者保证入参正确性.
 输入参数  : CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstIpPkt;
    VOS_UINT16                  usResult;

    /*停止保护定时器*/
    CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);

    /*清除Service Request标志位*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*重置GU SR标志*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*遍历队列*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        /*调用软过滤接口*/
        if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usResult,pstCdsEntity))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_UL_BUFF_SOFT_FILTER_FAIL_NUM(1);
            CDS_UP_EVENT_RPT(CDS_UP_EVENT_UL_SOFT_IPF_ERR);
            continue;
        }

        /*将过滤结果存到TTF中*/
        CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt,usResult);

        CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);

        CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_UlGUClearBuffData
 功能描述  : GU清空指定承载的上行缓存数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月22日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_SendUlBuffDataToRabm(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucSendRabId)
{
    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstTtfMem;
    VOS_UINT8                   ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*遍历队列*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstTtfMem);

        /*全部发送或发送指定承载*/
        if ((ucPktRabId == ucSendRabId) || (CDS_NAS_ALL_BEARER_ID == ucSendRabId))
        {
            CDS_UlDispatchDataByRanMode(pstCdsEntity,pstTtfMem);
            CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(1);
            continue;
        }

        /*不发送，则重新入队*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstTtfMem))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    /*缓存为空，停止保护定时器*/
    if (PS_TRUE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_CDMASendUlBuffData
 功能描述  : CDMA发送上行缓存数据.调用者保证入参正确性.
 输入参数  : CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_CDMASendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucSendRabId)
{
    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstIpPkt;
    VOS_UINT8                   ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*清除Service Request标志位*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*遍历队列*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

        /*全部发送或发送指定承载*/
        if ((ucPktRabId == ucSendRabId) || (CDS_NAS_ALL_BEARER_ID == ucSendRabId))
        {
            CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);
            CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(1);
            continue;
        }

        /*不发送，则重新入队*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstIpPkt))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    /*缓存为空，停止保护定时器*/
    if (PS_TRUE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_UlGUClearBuffData
 功能描述  : GU清空指定承载的上行缓存数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月22日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_UlGUClearBuffData(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucRabId)
{

    VOS_UINT32                  ulCnt;
    VOS_UINT32                  ulQueCnt;
    TTF_MEM_ST                 *pstTtfMem;
    VOS_UINT8                   ucPktRabId;

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*遍历队列*/
    ulQueCnt = LUP_QueCnt(pstCdsEntity->pstUlDataQue);
    for(ulCnt = 0; ulCnt < ulQueCnt; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstUlDataQue, (VOS_VOID **)&pstTtfMem))
        {
            break;
        }

        ucPktRabId = CDS_UL_GET_RABID_FROM_TTF(pstTtfMem);

        /*全部发送或发送指定承载*/
        if ((ucPktRabId == ucRabId) || (CDS_NAS_ALL_BEARER_ID == ucRabId))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
            continue;
        }

        /*不发送，则重新入队*/
        if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstUlDataQue,pstTtfMem))
        {
            TTF_MemFree(UEPS_PID_CDS, pstTtfMem);
            CDS_DBG_UL_BUFF_FREE_PKT_NUM(1);
        }

    }

    /*缓存为空，停止保护定时器*/
    if (PS_TRUE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        CDS_StopTimer(pstCdsEntity, CDS_TMR_ID_UL_DATA_PROCTECT);
    }

    return;

}

/*****************************************************************************
 函 数 名  : CDS_IsPsDataAvail
 功能描述  : 判断CDS上行是否存在PS缓存数据。
 输入参数  :
 输出参数  :
 返 回 值  : PS_TRUE : CDS存在上行缓存数据
             PS_FALSE: CDS没有上行缓存数据
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2013年09月16日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CDS_IsPsDataAvail(VOS_VOID)
{

    CDS_ENTITY_STRU    *pstCdsEntity;

    /*默认MODEM_0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return PS_FALSE;
    }

    /*上行缓存不为空*/
    if (PS_FALSE == LUP_IsQueEmpty(pstCdsEntity->pstUlDataQue))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }

}
/*lint +e960*/

/*****************************************************************************
 函 数 名  : CDS_APS_CdsOmReport
 功能描述  : 在非LTE模式下上报CDS统计量，供APS调用
 输入参数  :

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2016年1月20日
      作    者   : c00253308
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_APS_CdsOmReport(VOS_VOID)
{
    CDS_ENTITY_STRU *pstCdsEntity;
    
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);

    if (MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode)
    {
        return;
    }
    
    /*CDS统计量上报*/
    TL_OM_CdsStatInfoIndRpt();
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



