/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppSendMsg.c
  Description     :
  History         :
     1.XiaoJun       2015-7-30   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLppPublic.h"
#include  "LPPLRrcInterface.h"
#include  "NasLppIntraInterface.h"
#include  "NasLppEmmMsgProc.h"
#include  "NasLppOm.h"
#include  "OmCommon.h"
#include  "NasLppSendMsg.h"
#include  "NasLppEncode.h"
#include  "LPPLRrcInterface.h"



#define    THIS_FILE_ID            PS_FILE_ID_NASLPPSENDMSG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPSENDMSG_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LPP_SndLppLrrcEcidMeasReq
 Description    : 给LRRC发送ECID测量请求
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      XIAOJUN  2015-7-24  新开发
*****************************************************************************/

VOS_VOID NAS_LPP_SndLppLrrcEcidMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
)
{
    LPP_LRRC_ECID_MEAS_REQ_STRU *pstEcidMeasReq;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLppLrrcEcidMeasReq enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLppLrrcEcidMeasReq_ENUM, LNAS_LPP_Func_Enter);

    pstEcidMeasReq = (LPP_LRRC_ECID_MEAS_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU));
    if (NAS_LPP_NULL_PTR == pstEcidMeasReq)
    {
        NAS_LPP_ERR_LOG("lpp snd ecid meas req allocal msg null");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndLppLrrcEcidMeasReq_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstEcidMeasReq, sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU), 0, sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU));

    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstEcidMeasReq,ID_LPP_LRRC_ECID_MEAS_REQ);

    pstEcidMeasReq->ucLcsMeasCmd = ucLcsMeasCmd;
    pstEcidMeasReq->ucRxTxTimeDiffMeasFlag = PS_TRUE;

    NAS_LPP_SND_MSG(pstEcidMeasReq);

    NAS_LPP_SetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_ECID,NAS_LPP_SLCT);
}
/*****************************************************************************
 Function Name  : NAS_LPP_SndLppLrrcLocationInfo
 Description    : 给LRRC发送GNSS LOCATION INFORMATION
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      WANGENSHENG  2015-10-21  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_SndLppLrrcLocationInfo
(
    MTA_LPP_MEAS_REF_TIME_STRU                             *pstMtaLppMeasRefTime,
    LOC_COM_VELOCITY_STRU                                  *pstVelocityEstimate,
    LOC_COM_COORDINATE_STRU                                *pstLocationEstimate,
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                           ucGnssDataFlag
)
{
    LPP_LRRC_GNSS_DATA_INFO_IND_STRU                       *pstLppLrrcGnssDataInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_SERVING_CELL_STRU                              *pstServingCell = NAS_LPP_NULL_PTR;
    VOS_UINT16                                              usReturnRslt = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLppLrrcLocationInfo enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLppLrrcLocationInfo_ENUM, LNAS_LPP_Func_Enter);

    /* 每次给RRC发位置信息时清除小区改变标志位 */
    pstServingCell = NAS_LPP_GetServingCell();
    pstServingCell->bitCELLIDChng = NAS_LPP_NO_SLCT;

    /* 发消息 */
    pstLppLrrcGnssDataInfo = (LPP_LRRC_GNSS_DATA_INFO_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_GNSS_DATA_INFO_IND_STRU));
    if (NAS_LPP_NULL_PTR == pstLppLrrcGnssDataInfo)
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstLppLrrcGnssDataInfo, sizeof(LPP_LRRC_GNSS_DATA_INFO_IND_STRU), 0, sizeof(LPP_LRRC_GNSS_DATA_INFO_IND_STRU));

    /* TODO:MEM */
    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstLppLrrcGnssDataInfo,ID_LPP_LRRC_GNSS_DATA_INFO_IND);
    if (LPP_LRRC_INFO_FLAG_VALID == ucGnssDataFlag)
    {
        TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLppLrrcLocationInfo_ENUM, LNAS_LPP_SEND_RRC_EMPTY_LOC_INFO);
        pstLppLrrcGnssDataInfo->ucGnssDataFlag = LPP_LRRC_INFO_FLAG_VALID;
        usReturnRslt = NAS_LPP_EncodeRrcLocInfo(pstMtaLppMeasRefTime,
                                                pstVelocityEstimate,
                                                pstLocationEstimate,
                                                pstLppLrrcGnssDataInfo);
        if ( NAS_LPP_ENCODE_SUCC != usReturnRslt )
        {
            NAS_LPP_MEM_FREE(pstLppLrrcGnssDataInfo);
            return;
        }
    }
    else
    {
        pstLppLrrcGnssDataInfo->ucGnssDataFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    NAS_LPP_SND_MSG(pstLppLrrcGnssDataInfo);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndOtdoaMeasReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SndOtdoaMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
)
{
    LPP_LRRC_OTDOA_MEAS_REQ_STRU            *pstOtdoaMeasReq;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    NAS_LPP_COMM_CONFIG_INFO_STRU           *pstLppCommCfgInfo;

    NAS_LPP_NORM_LOG("NAS_LPP_SndOtdoaMeasReq enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndOtdoaMeasReq_ENUM, LNAS_LPP_Func_Enter);

    pstOtdoaMeasReq = (LPP_LRRC_OTDOA_MEAS_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU));

    if (NAS_LPP_NULL_PTR == pstOtdoaMeasReq)
    {
        NAS_LPP_ERR_LOG("lpp snd otdoa meas req allocal msg null");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndOtdoaMeasReq_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstOtdoaMeasReq, sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU), 0, sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU));

    pstTransEntity = NAS_LPP_GetTransEntity(ucSessionIndx, ucSessionTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG2("lpp snd otdoa meas req :with wrong index",ucSessionIndx, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndOtdoaMeasReq_ENUM, LNAS_LPP_WrongTransactionIndex);
        return;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo)
    {
        NAS_LPP_ERR_LOG1("lpp snd otdoa meas req :with wrong comm cfg index", pstTransEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndOtdoaMeasReq_ENUM, LNAS_LPP_WrongCommCfgIndx);
        return ;
    }

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstOtdoaMeasReq,ID_LPP_LRRC_OTDOA_MEAS_REQ);

    pstOtdoaMeasReq->ucLcsMeasCmd = ucLcsMeasCmd;


    if (LPP_LRRC_LCS_MEAS_CMD_SETUP == ucLcsMeasCmd)
    {
        pstOtdoaMeasReq->ucOtdoaMeasAssistanceDataFlag = LPP_LRRC_INFO_FLAG_VALID;

        if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstLppCommCfgInfo->stReportCriteria.enType)
        {
            pstOtdoaMeasReq->enOtdoaRprtInterval = pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.enOtdoaRprtInterval;
        }
        else
        {
            pstOtdoaMeasReq->enOtdoaRprtInterval = LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16;  /*REPORT ONCEDE ,给lrrc的是折中的时间长度*/
        }

        pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.ucOtdoaReferenceCellInfoFlag
            = pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag;

        pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.ucOtdoaNeighbourCellInfoFlag
            = pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag;

        NAS_LPP_MEM_CPY_S(&pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.stOtdoaReferenceCellInfo,
                        sizeof(LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU),
                        &pstOtdoaAssisCfg->stOtdoaReferenceCellInfo,
                        sizeof(LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU));

        NAS_LPP_MEM_CPY_S(&pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.stOtdoaNeighbourCellInfo,
                        sizeof(LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU),
                        &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo,
                        sizeof(LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU));
    }

    NAS_LPP_SND_MSG(pstOtdoaMeasReq);

    NAS_LPP_SetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_OTDOA,NAS_LPP_SLCT);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndUpLppAbortMsg
 Description     : 组装、编码上行的ABORT消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_SndUpLppAbortMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_COMMON_IES_ABORT_ENUM_UINT8     enAbortCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity   = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    LPP_MESSAGE_STRU                        *pstUpAbort = NAS_LPP_NULL_PTR;
    LPP_C1_EXT_ABORT_STRU                   *pstAbortExtC1 = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU                stLppMsgIdentity ={0};
    VOS_UINT16 usRslt,usBitPos = 0;
    VOS_UINT32 ulLppMsgLen;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUpLppAbortMsg enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppAbortMsg_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        /*释放申请的动态内存*/
        NAS_LPP_ERR_LOG1("snd abort: Don't find the session! ucSessionIndx",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUpLppAbortMsg_ENUM, LNAS_LPP_CanntFindSession);
        return NAS_LPP_FAILURE;
    }

    /*获取transaction实体*/
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /*释放申请的动态内存*/
        NAS_LPP_ERR_LOG1("snd abort: Don't find the transaction!ucTransIndx",ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUpLppAbortMsg_ENUM, LNAS_LPP_WrongTransactionIndex);
        return NAS_LPP_FAILURE;
    }

    /*分配编码之后码流的存储空间*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        return NAS_LPP_FAILURE;
    }

    /*清空*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg,sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);


    /*获取LPP MSG BUFF*/
    pstUpAbort = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET_S(pstUpAbort, sizeof(LPP_MESSAGE_STRU),0, sizeof(LPP_MESSAGE_STRU));

    pstUpAbort->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstUpAbort->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstUpAbort->bitOpLppMessageBody   = NAS_LPP_SLCT;

    if ( PS_TRUE == enNeedAck )
    {
         pstUpAbort->bitOpAcknowledgement  = NAS_LPP_SLCT;
         pstUpAbort->stAcknowledgement.bAckRequested = enNeedAck;

         /* 无需ack indicator*/
    }

    /*pstUpAbort->stTransactionId.bitOpTransactionIDExt暂时没用，默认为0*/
    pstUpAbort->stTransactionId.enInitiator = pstTransEntity->stTransId.enInitiator;
    pstUpAbort->stTransactionId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    pstUpAbort->bEndTransaction = bEndTransaction;

    pstUpAbort->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstUpAbort->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUpAbort->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN;
    pstUpAbort->stLppMessageBody.u.stC1.u.stAbort.stC1.ulChoice = LPP_CRITI_EXT_ABORT_CHOSEN;

    pstAbortExtC1 = &(pstUpAbort->stLppMessageBody.u.stC1.u.stAbort.stC1.u.stAbortExtC1);
    pstAbortExtC1->ulChoice = LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN;
    pstAbortExtC1->u.stAbortR9.bitOpAbortR9IEsExt  = NAS_LPP_SLCT;
    pstAbortExtC1->u.stAbortR9.bitOpCommonIesAbort = NAS_LPP_SLCT;
    pstAbortExtC1->u.stAbortR9.stCommonIesAbort.enCommonIesAbortCasue = enAbortCause;


    /*开始编码*/
    usRslt = NAS_LPP_EncodeMessage(pstUpAbort,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG(" Encode LPP abort msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUpLppAbortMsg_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return NAS_LPP_FAILURE;
    }

    ulLppMsgLen = usBitPos/8;

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_DOWN,
                          LNAS_LPP_ABORT_UP,
                          ulLppMsgLen,
                          pucEncodeOutMsg);

    stLppMsgIdentity.enUplinkMsgType = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    stLppMsgIdentity.stTransId.enInitiator = pstTransEntity->stTransId.enInitiator;
    stLppMsgIdentity.stTransId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    stLppMsgIdentity.ulSessionId = pstSessionEntity->ulSessionId;
    stLppMsgIdentity.usSequnceNum= pstUpAbort->stSequenceNumber.ucSequenceNumber;

    NAS_LPP_SendUplinkMsg(pstSessionEntity->ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndUpLppErrorMsg
 Description     : 组装、编码上行的error消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_SndUpLppErrorMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU              *pstTransID,
    LPP_COMMON_IES_ERROR_ENUM_UINT8     enErrorCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
)

{
    VOS_UINT8                               *pucEncodeOutMsg    = NAS_LPP_NULL_PTR;
    LPP_MESSAGE_STRU                        *pstUpError         = NAS_LPP_NULL_PTR;
    LPP_ERROR_R9_STRU                       *pstErrorR9         = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU                stLppMsgIdentity   = {0};
    VOS_UINT16                               usRslt,usBitPos    = 0;
    VOS_UINT32                               ulLppMsgLen        = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUpLppErrorMsg enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppErrorMsg_ENUM, LNAS_LPP_Func_Enter);

    /*分配编码之后码流的存储空间*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        return NAS_LPP_FAILURE;
    }

    /*清空*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg,sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);


    /*获取LPP MSG BUFF*/
    pstUpError = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET_S(pstUpError,sizeof(LPP_MESSAGE_STRU), 0, sizeof(LPP_MESSAGE_STRU));

    pstUpError->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstUpError->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstUpError->bitOpLppMessageBody   = NAS_LPP_SLCT;

    if ( PS_TRUE == enNeedAck )
    {
         pstUpError->bitOpAcknowledgement  = NAS_LPP_SLCT;
         pstUpError->stAcknowledgement.bAckRequested = enNeedAck;

         /* 无需ack indicator*/
    }

    /*pstUpAbort->stTransactionId.bitOpTransactionIDExt暂时没用，默认为0*/
    pstUpError->stTransactionId.enInitiator = pstTransID->enInitiator;
    pstUpError->stTransactionId.ucTransactionNumber = pstTransID->ucTransactionNumber;

    pstUpError->bEndTransaction = bEndTransaction;

    pstUpError->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstUpError->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUpError->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN;
    pstUpError->stLppMessageBody.u.stC1.u.stError.ulChoice = LPP_ERROR_R9_IES_CHOSEN;

    pstErrorR9 = &(pstUpError->stLppMessageBody.u.stC1.u.stError.u.stErrorR9);
    pstErrorR9->bitOpCommonIesError = NAS_LPP_SLCT;
    /*pstErrorR9->stCommonIesError.bitOpCommonIEsErrorExt =*/
    pstErrorR9->stCommonIesError.enCommonIesErrorCasue= enErrorCause;


    /*开始编码*/
    usRslt = NAS_LPP_EncodeMessage(pstUpError,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG(" Encode LPP error msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUpLppErrorMsg_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return NAS_LPP_FAILURE;
    }

    ulLppMsgLen = usBitPos/8;

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_DOWN,
                          LNAS_LPP_ERROR_UP,
                          ulLppMsgLen,
                          pucEncodeOutMsg);

    stLppMsgIdentity.enUplinkMsgType = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    stLppMsgIdentity.stTransId.enInitiator = pstTransID->enInitiator;
    stLppMsgIdentity.stTransId.ucTransactionNumber = pstTransID->ucTransactionNumber;

    stLppMsgIdentity.ulSessionId = ulSessionId;
    stLppMsgIdentity.usSequnceNum= pstUpError->stSequenceNumber.ucSequenceNumber;

    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    NAS_LPP_MEM_FREE(pucEncodeOutMsg);
    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_PreGnssAssistDataParameter
 Description     : 准备辅助数据请求的待编码的参数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982      2015-10-22  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_PreGnssAssistDataParameter
(
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU       *pstMtaLppGnssAssistDataReq,
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU     *pstRequestAsisstDataR9
)
{
    VOS_UINT32                  ulGNSSGenericAssistDataReqCnt = 0;
    VOS_UINT32                  ulLoop = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_PreGnssAssistDataParameter enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_PreGnssAssistDataParameter_ENUM, LNAS_LPP_Func_Enter);

    pstRequestAsisstDataR9->bitOpAGNSSRequestAssistData = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.bitOpGNSSCommAssistData =
        pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.bitOpGNSSCommAssistData;
    pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.bitOpGNSSGenericAssistData =
        pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.bitOpGNSSGenericAssistData;

    NAS_LPP_MEM_CPY_S(&(pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.stGNSSCommonAssistDataReq),
                    sizeof(LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU),
                    &(pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.stGNSSCommonAssistDataReq),
                    sizeof(MTA_LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU));

    ulGNSSGenericAssistDataReqCnt = pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.stGNSSGenericAssistDataReq.ulGNSSGenericAssistDataReqCnt;
    pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.stGNSSGenericAssistDataReq.ulGNSSGenericAssistDataReqCnt = ulGNSSGenericAssistDataReqCnt;
    for (ulLoop = 0;ulLoop < ulGNSSGenericAssistDataReqCnt;ulLoop++)
    {
        NAS_LPP_MEM_CPY_S(&(pstRequestAsisstDataR9->stAGNSSRequestAssistanceData.stGNSSGenericAssistDataReq.astGNSSGenericAssistDataReqElement[ulLoop]),
                          sizeof(LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU),
                          pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.stGNSSGenericAssistDataReq.pastGNSSGenericAssistDataReqElement[ulLoop],
                          sizeof(MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU) );
        NAS_LPP_MEM_FREE(pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.stGNSSGenericAssistDataReq.pastGNSSGenericAssistDataReqElement[ulLoop]);
        pstMtaLppGnssAssistDataReq->stGnssAssistDataReq.stGNSSGenericAssistDataReq.pastGNSSGenericAssistDataReqElement[ulLoop] = NAS_LPP_NULL_PTR;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndUplinkReqAssistDataMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-26  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_SndUplinkReqAssistDataMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    VOS_BOOL                            enOtdoaAssist,
    VOS_BOOL                            enGnssAssist,
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU  *pstMtaLppGnssAssistDataReq
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity   = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               *pucEncodeOutMsg  = NAS_LPP_NULL_PTR;
    LPP_MESSAGE_STRU                        *pstReqAssistData = NAS_LPP_NULL_PTR;
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU     *pstRequestAsisstDataR9;
    NAS_LPP_SERVING_CELL_STRU               *pstServingCell;
    NAS_LPP_MSG_IDENTITY_STRU                stLppMsgIdentity ={0};

    VOS_UINT16 usRslt,usBitPos = 0;
    VOS_UINT32 ulLppMsgLen = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUplinkReqAssistDataMsg enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUplinkReqAssistDataMsg_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        /*释放申请的动态内存*/
        NAS_LPP_ERR_LOG1("snd assist: Don't find the session! ucSessionIndx",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUplinkReqAssistDataMsg_ENUM, LNAS_LPP_CanntFindSession);
        return NAS_LPP_FAILURE;
    }

    /*获取transaction实体*/
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /*释放申请的动态内存*/
        NAS_LPP_ERR_LOG1("snd assist: Don't find the transaction!ucTransIndx",ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUplinkReqAssistDataMsg_ENUM, LNAS_LPP_CanntFindTransaction);
        return NAS_LPP_FAILURE;
    }

    pstServingCell = NAS_LPP_GetServingCell();

    /*分配编码之后码流的存储空间*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        return NAS_LPP_FAILURE;
    }

    /*清空*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN,0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);

    /*获取LPP MSG BUFF*/
    pstReqAssistData = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET_S(pstReqAssistData,sizeof(LPP_MESSAGE_STRU), 0, sizeof(LPP_MESSAGE_STRU));

    pstReqAssistData->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstReqAssistData->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpLppMessageBody   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpAcknowledgement  = NAS_LPP_SLCT;

    pstReqAssistData->stAcknowledgement.bAckRequested = VOS_TRUE;

     /* 无需ack indicator*/

    pstReqAssistData->bEndTransaction = VOS_FALSE;

    pstReqAssistData->stTransactionId.bitOpTransactionIDExt = NAS_LPP_NO_SLCT;
    pstReqAssistData->stTransactionId.ucTransactionNumber   = pstTransEntity->stTransId.ucTransactionNumber;
    pstReqAssistData->stTransactionId.enInitiator = LPP_INITIATOR_TYPE_TARGET_DEVICE;

    pstReqAssistData->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstReqAssistData->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN;
    pstRequestAsisstDataR9 = &pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.u.stRequestAssitDataR9;

    pstRequestAsisstDataR9->bitOpCommonIEsRequestAssitData = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.bitOpPrimaryCellID = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.ulCellIdentity = pstServingCell->ulCellIdentity;
    NAS_LPP_NasPlmn2LppPlmn(pstServingCell->aucPlmnId,
                            &pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.stPlmnIdentity);

    if (VOS_TRUE == enOtdoaAssist)
    {
        pstRequestAsisstDataR9->bitOpOTDOARequestAssistData    = NAS_LPP_SLCT;
        pstRequestAsisstDataR9->stOTDOARequestAssistanceData.usPhyCellId = pstServingCell->usPhyCellId;

        pstTransEntity->bitOpOtdoaAssistReq = NAS_LPP_SLCT;
    }

    if (VOS_TRUE == enGnssAssist)
    {
        NAS_LPP_PreGnssAssistDataParameter(pstMtaLppGnssAssistDataReq, pstRequestAsisstDataR9);
    }

    /*开始编码*/
    usRslt = NAS_LPP_EncodeMessage(pstReqAssistData,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG(" Encode assist data msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUplinkReqAssistDataMsg_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return NAS_LPP_FAILURE;
    }

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_UP,
                          LNAS_LPP_REQ_ASSIST_DATA,
                          ulLppMsgLen,
                          pucEncodeOutMsg);

    ulLppMsgLen = usBitPos/8;

    stLppMsgIdentity.enUplinkMsgType = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    stLppMsgIdentity.stTransId.enInitiator = pstTransEntity->stTransId.enInitiator;
    stLppMsgIdentity.stTransId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    stLppMsgIdentity.ulSessionId = pstSessionEntity->ulSessionId;
    stLppMsgIdentity.usSequnceNum= pstReqAssistData->stSequenceNumber.ucSequenceNumber;

    NAS_LPP_SendUplinkMsg(pstSessionEntity->ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                         &stLppMsgIdentity);

    pstTransEntity->enLastUpMsgId  = NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA;
    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvLppEmDataCnf
 Description    : LPP模块收到直传回复的消息处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_SndIntraLppMsg
(
    VOS_UINT32                                  ulOpId,
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity,
    NAS_LPP_ERROR_CODE_ENUM_UINT32       enErrorCode
)
{
    NAS_LPP_INTRA_DATA_CNF_STRU           *pstInterDataCnf;

    NAS_LPP_NORM_LOG("NAS_LPP_SndIntraLppMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndIntraLppMsg_ENUM, LNAS_LPP_Func_Enter);

    /* 申请内存  */
    pstInterDataCnf = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(NAS_LPP_INTRA_DATA_CNF_STRU));
    if( NAS_LPP_NULL_PTR == pstInterDataCnf )
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstInterDataCnf, sizeof(NAS_LPP_INTRA_DATA_CNF_STRU), 0, sizeof(NAS_LPP_INTRA_DATA_CNF_STRU));

    if(NAS_LPP_NULL_PTR != pstLppMsgIdentity)
    {
        NAS_LPP_MEM_CPY_S(&(pstInterDataCnf->stLppMsgIdentity),
                        sizeof(NAS_LPP_MSG_IDENTITY_STRU),
                        pstLppMsgIdentity,
                        sizeof(NAS_LPP_MSG_IDENTITY_STRU));
    }
    pstInterDataCnf->enRslt = enErrorCode;
    pstInterDataCnf->ulOpId = ulOpId;

    /*填写消息头*/
    NAS_LPP_INTER_WRITE_EMM_MSG_HEAD(pstInterDataCnf, ID_NAS_LPP_INTRA_DATA_CNF);

    /*调用消息发送函数 */
    NAS_LPP_SND_MSG(pstInterDataCnf);

    return;

}


#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

