/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsTafMsgProc.c
    Description : 处理TAF发给LCS的消息
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLcsPublic.h"
#include    "NasLcsOm.h"
#include    "NasLcsDecode.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsMmMsgProc.h"
#include    "NasLcsMain.h"
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



#define    THIS_FILE_ID            PS_FILE_ID_NASLCSTAFMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSTAFMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
Function Name  : NAS_LCS_SndTafEndInd
Description    : 给TAF发送LCS_TAF_END_IND消息
Input          : enLcsType-----------------LCS实体类型
                 enCause-------------------原因值
                 ucHandleId----------------HANDLE ID
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-29  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_SndTafEndInd
(
    TAF_LCS_LR_TYPE_EUNM_UINT8          enLcsType,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT8                           ucHandleId
)
{
    LCS_TAF_END_IND_STRU               *pstTafEndInd = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndTafEndInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndTafEndInd_ENUM, LNAS_ENTRY);

    pstTafEndInd   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_TAF_END_IND_STRU));
    if (NAS_LCS_NULL_PTR == pstTafEndInd)
    {
        return;
    }

    NAS_LCS_WRITE_TAF_MSG_HEAD( pstTafEndInd,
                                (sizeof(LCS_TAF_END_IND_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstTafEndInd->stMsgHeader.ulMsgName = ID_LCS_TAF_END_IND;
    pstTafEndInd->enLcsType             = enLcsType;
    pstTafEndInd->enCause               = enCause;
    pstTafEndInd->ucHandleId            = ucHandleId;

    NAS_LCS_SND_MSG(pstTafEndInd);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndTafFacilityInd
Description    : 给TAF发送LCS_TAF_FACILITY_IND消息
Input          : pstLocationEstimate---------地理位置信息指针
                 pstVelocityEstimate---------速度信息指针
                 enCause--------------------------原因值
                 ucHandleId----------------HANDLE ID
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-29  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_SndTafFacilityInd
(
    LOC_COM_COORDINATE_STRU            *pstLocationEstimate,
    LOC_COM_VELOCITY_STRU              *pstVelocityEstimate,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{
    LCS_TAF_FACILITY_IND_STRU          *pstTafEndFacilityInd = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndTafFacilityInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndTafEndInd_ENUM, LNAS_ENTRY);

    pstTafEndFacilityInd   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_TAF_FACILITY_IND_STRU));
    if (NAS_LCS_NULL_PTR == pstTafEndFacilityInd)
    {
        return;
    }

    NAS_LCS_MEM_SET_S(  &pstTafEndFacilityInd->stLocationParam,
                        sizeof(LCS_TAF_LOCATION_INFO_STRU),
                        0,
                        sizeof(LCS_TAF_LOCATION_INFO_STRU));

    NAS_LCS_WRITE_TAF_MSG_HEAD( pstTafEndFacilityInd,
                                (sizeof(LCS_TAF_FACILITY_IND_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstTafEndFacilityInd->stMsgHeader.ulMsgName = ID_LCS_TAF_FACILITY_IND;

    if (NAS_LCS_NULL_PTR != pstLocationEstimate)
    {
        pstTafEndFacilityInd->stLocationParam.bitOpLocationEstimate = NAS_LCS_OP_TRUE;

        NAS_LCS_MEM_CPY_S(  &pstTafEndFacilityInd->stLocationParam.stLocationEstimate,
                            sizeof(LOC_COM_COORDINATE_STRU),
                            pstLocationEstimate,
                            sizeof(LOC_COM_COORDINATE_STRU));
    }
    else
    {
        pstTafEndFacilityInd->stLocationParam.bitOpLocationEstimate = NAS_LCS_OP_FALSE;
    }

    if (NAS_LCS_NULL_PTR != pstVelocityEstimate)
    {
        pstTafEndFacilityInd->stLocationParam.bitOpVelocityEstimate = NAS_LCS_OP_TRUE;

        NAS_LCS_MEM_CPY_S(  &pstTafEndFacilityInd->stLocationParam.stVelocityEstimate,
                            sizeof(LOC_COM_VELOCITY_STRU),
                            pstVelocityEstimate,
                            sizeof(LOC_COM_VELOCITY_STRU));
    }
    else
    {
        pstTafEndFacilityInd->stLocationParam.bitOpVelocityEstimate = NAS_LCS_OP_FALSE;
    }

    pstTafEndFacilityInd->enCause = enCause;

    NAS_LCS_SND_MSG(pstTafEndFacilityInd);
}

/*****************************************************************************
Function Name  : NAS_LCS_LocationTypeTransform
Description    : 将空口LOCATION TYPE转为AT命令格式
Input          : enLocType----------------空口location type
Output         : VOS_VOID
Return Value   : LCS_LOCATION_TYPE_ENUM_UINT8

History        :
  lihong 00150010 2015-10-12  新开发
*****************************************************************************/
LCS_LOCATION_TYPE_ENUM_UINT8  NAS_LCS_LocationTypeTransform
(
    NAS_LCS_LOCATION_EST_TYPE_ENUM_UINT8    enLocType
)
{
    if (enLocType >= NAS_LCS_LOCATION_TYPE_ACT_DEFER_LOC)
    {
        return LCS_LOCATION_CURRENT;
    }

    return enLocType;
}

/*****************************************************************************
Function Name  : NAS_LCS_SndTafBeginInd
Description    : 给TAF发送LCS_TAF_BEGIN_IND消息
Input          : pstCnMsgStru-----------------空口消息译码后的内容指针
                 ucHandleId----------------HANDLE ID
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-29  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_SndTafBeginInd
(
    const NAS_LCS_LOC_NOTFICATION_STRU *pstLocNotication,
    VOS_UINT8                           ucHandleId
)
{
    LCS_TAF_BEGIN_IND_STRU             *pstTafBeginInd = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndTafBeginInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndTafBeginInd_ENUM, LNAS_ENTRY);

    pstTafBeginInd   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_TAF_BEGIN_IND_STRU));
    if (NAS_LCS_NULL_PTR == pstTafBeginInd)
    {
        return;
    }

    NAS_LCS_WRITE_TAF_MSG_HEAD( pstTafBeginInd,
                                (sizeof(LCS_TAF_BEGIN_IND_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    NAS_LCS_MEM_SET_S(  &pstTafBeginInd->stMtlrPara,
                        sizeof(LCS_MTLR_PARA_STRU),
                        0,
                        sizeof(LCS_MTLR_PARA_STRU));

    pstTafBeginInd->stMsgHeader.ulMsgName       = ID_LCS_TAF_BEGIN_IND;
    pstTafBeginInd->stMtlrPara.enNtfType        = pstLocNotication->enNtfType;
    pstTafBeginInd->stMtlrPara.enLocationType   = NAS_LCS_LocationTypeTransform(pstLocNotication->stLocationType.enLocType);
    pstTafBeginInd->stMtlrPara.ucHandleId       = ucHandleId;
    pstTafBeginInd->stMtlrPara.bitOpClientExId  = pstLocNotication->bitOpClientExternalId \
                                                    & pstLocNotication->stClientExternalId.bitOpExternalAddr;

    NAS_LCS_MEM_CPY_S(  &pstTafBeginInd->stMtlrPara.stClientExId,
                        sizeof(LCS_CLIENT_EXTERNAL_ID_STRU),
                        &pstLocNotication->stClientExternalId.stExternalAddr,
                        sizeof(LCS_CLIENT_EXTERNAL_ID_STRU));
    pstTafBeginInd->stMtlrPara.bitOpClientName  = pstLocNotication->bitOpClientName;
    NAS_LCS_MEM_CPY_S(  &pstTafBeginInd->stMtlrPara.stClientName,
                        sizeof(LCS_CLIENT_NAME_STRU),
                        &pstLocNotication->stClientName.stNameString,
                        sizeof(LCS_CLIENT_NAME_STRU));

    NAS_LCS_SND_MSG(pstTafBeginInd);
}

/*****************************************************************************
Function Name  : NAS_LCS_ValidateMoLrRecord
Description    : 参数合法性检测
Input          : None
Output         : None
Return Value   : None

History        :
  lihong 00150010 2015-9-29  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ValidateMoLrRecord( VOS_VOID )
{
    LCS_MOLR_PARA_STRU                 *pstMolrPara = NAS_LCS_NULL_PTR;

    pstMolrPara = NAS_LCS_GetTafMolrRecord();

    if (LCS_REP_MODE_BUTT == pstMolrPara->enRepMode)
    {
        pstMolrPara->enRepMode = LCS_REP_MODE_SINGLE_RPT;
    }

    if (0 == pstMolrPara->usTimeOut)
    {
        pstMolrPara->usTimeOut = NAS_LCS_WAIT_NW_RSP_TIMER_DFT_LEN;
    }

    if (pstMolrPara->usInterval < pstMolrPara->usTimeOut)
    {
        pstMolrPara->usInterval = pstMolrPara->usTimeOut;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvTafBeginReq
Description    : TAF_LCS_BEGIN_REQ消息处理函数
Input          : VOS_VOID *pstEstCnf
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-29  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvTafBeginReq
(
    const TAF_LCS_BEGIN_REQ_STRU       *pstBeginReq
)
{
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enMolrDomain    = NAS_LCS_DOMAIN_TYPE_BUTT;
    VOS_UINT32                          ulIndex         = 0;
    VOS_UINT8                           ucInvokeId      = 0;
    VOS_UINT8                           ucMoTi          = 0;

    /* 进行域选择，如果选择域选择失败，则直接给TAF回复LCS_TAF_END_IND */
    enMolrDomain = NAS_LCS_SelectMolrDomain();
    NAS_LCS_SndOmDomainSelectInfo(enMolrDomain);
    if (NAS_LCS_DOMAIN_TYPE_BUTT == enMolrDomain)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvTafBeginReq:select domain fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvTafBeginReq_ENUM, LNAS_LCS_SelectDomainFail);
        NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MO,TAF_LCS_CAUSE_LCS_NOT_SUPPORT,0);
        return ;
    }

    /* 创建TAF触发的MO-LR实体，如果创建失败，则直接给TAF回复LCS_TAF_END_IND */
    if (NAS_LCS_FAIL == NAS_LCS_CreateLcsEntity(    NAS_LCS_START_SOURCE_TAF,
                                                    &ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvTafBeginReq:create entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvTafBeginReq_ENUM, LNAS_LCS_CreateEntityFail);
        NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MO,TAF_LCS_CAUSE_MO_LR_ALREADY_EXISTED,0);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* 存储MO-LR实体信息 */
    NAS_LCS_MEM_CPY_S(  NAS_LCS_GetTafMolrRecord(),
                        sizeof(LCS_MOLR_PARA_STRU),
                        &pstBeginReq->stMolrPara,
                        sizeof(LCS_MOLR_PARA_STRU));

    /* 对一些参数进行合法性纠错 */
    NAS_LCS_ValidateMoLrRecord();

    /* 记录实体域信息为选择的域 */
    NAS_LCS_SetEntityLcsDomain(ulIndex, enMolrDomain);

    /* 创建TI，并存储 */
    ucMoTi = NAS_LCS_CreateMoTi(ulIndex);
    NAS_LCS_SetEntityTi(ulIndex, ucMoTi);

    /* 创建InvokeId,并存储 */
    ucInvokeId = NAS_LCS_CreateInvokeId();
    NAS_LCS_SetEntityInvokeId(ulIndex, ucInvokeId);

    /* 启动等待网侧响应定时器 */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WAIT_NW_RSP_TIMER);

    /* 给相应域发建链请求 */
    if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == enMolrDomain)
    {
        NAS_LCS_SndLmmEstReq(ucMoTi);
    }
    else
    {
        NAS_LCS_SndMmEstReq(ucMoTi);
    }

    /* 更新实体连接状态为建链过程中 */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvTafEndReq
Description    : TAF_LCS_END_REQ消息处理函数
Input          : VOS_VOID *pstEstCnf
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvTafEndReq
(
    const TAF_LCS_END_REQ_STRU         *pstEndReq
)
{
    VOS_UINT32                          ulIndex         = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity;

    if (TAF_LCS_LR_TYPE_MO == pstEndReq->enLcsType)
    {
        ulIndex = NAS_LCS_MO_LR_TAF_INDEX;

        pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
        if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
        {
            NAS_LCS_WARN_LOG("NAS_LCS_RcvTafEndReq:entity not exist!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvTafEndReq_ENUM, LNAS_LCS_EntityNotExist);
            NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MO,TAF_LCS_CAUSE_SUCCESS,0);

            return ;
        }
    }
    else
    {
        /* 根据Handle id查找MT LR实体 */
        if (NAS_LCS_FAIL == NAS_LCS_QueryMtLrEntity(pstEndReq->ucHandleId, &ulIndex))
        {
            NAS_LCS_WARN_LOG("NAS_LCS_RcvTafEndReq:Query mt lr fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvTafEndReq_ENUM, LNAS_LCS_QueryEntityFail);
            NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MT, TAF_LCS_CAUSE_SUCCESS, pstEndReq->ucHandleId);

            NAS_LCS_SndOmEntityInfo();
            return ;
        }
    }

    if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(ulIndex))
    {
        /* 编码RELEASE COMPLTE消息，发给网侧 */
        if (PS_TRUE == NAS_LCS_IsMoLr(ulIndex))
        {
            /* 当前实体为MOLR时回复网侧REL CMP不带原因值 */
            NAS_LCS_SndReleaseComplte(ulIndex);
        }
        else
        {
            /* 当前实体为MTLR时回复网侧MTLR结果 */
            NAS_LCS_SndMtlrRspReleaseComplte(ulIndex, pstEndReq->enAllow);
        }
    }

    /* 通知MM可以释放与此TI相关的LCS实体信息, MTLR接入层会通知MM是否允许释放链路 */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* 释放LCS实体 */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_SUCCESS);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvTafPowerStatusNtf
Description    : TAF_LCS_POWER_STATUS_NTF消息处理函数
Input          : VOS_VOID *pstPowerStatusNtf
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-11  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvTafPowerStatusNtf
(
    const TAF_LCS_POWER_STATUS_NTF_STRU    *pstPowerStatusNtf
)
{

    if (TAF_LCS_POWER_STATUS_ON == pstPowerStatusNtf->enStatus)
    {
        /* 全局变量初始化 */
        NAS_LCS_Init();

        /* 读取LCS 功能NV项 */
        NAS_LCS_ReadLcsNvCommonConfig();

        /* 抛出NV信息到层间显示 */
        NAS_LCS_SndOmNvCommonConfig();
    }
    else
    {
        NAS_LCS_ClearResource();
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_TafMsgDistr
Description    : LCS模块TAF消息处理函数
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_TafMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pTafMsg  = VOS_NULL_PTR;

    pTafMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    NAS_LCS_INFO_LOG("NAS_LCS_TafMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_TafMsgDistr_ENUM, LNAS_ENTRY, pTafMsg->ulMsgName);

    /*根据消息名，调用相应的消息处理函数*/
    switch(pTafMsg->ulMsgName)
    {
        case ID_TAF_LCS_BEGIN_REQ:
            NAS_LCS_RcvTafBeginReq((TAF_LCS_BEGIN_REQ_STRU *)pRcvMsg);
            break;

        case ID_TAF_LCS_END_REQ:
            NAS_LCS_RcvTafEndReq((TAF_LCS_END_REQ_STRU *)pRcvMsg);
            break;

        case ID_TAF_LCS_POWER_STATUS_NTF:
            NAS_LCS_RcvTafPowerStatusNtf((TAF_LCS_POWER_STATUS_NTF_STRU *)pRcvMsg);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_TafMsgDistr:NORM: Error Msgid!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_TafMsgDistr_ENUM, LNAS_LCS_InvalidRsvMsgId);
            break;
    }

    return;
}


#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLcsTafMsgProc.c */
