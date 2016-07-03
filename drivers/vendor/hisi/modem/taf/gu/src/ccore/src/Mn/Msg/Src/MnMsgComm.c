

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnMsgInclude.h"
#include "NasGmmInterface.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"

#include "TafCbaCtx.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "NasUsimmApi.h"
#include "TafSdcCtx.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasComm.h"
#include "TafSdcLib.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_COMM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_CLOSE_SMS_CAPABILITY_MSG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

MN_MSG_DISCARD_DELIVER_MSG_STRU         f_stMnMsgDiscardDeliverMsg;
MN_MSG_REPLACE_DELIVER_MSG_STRU         f_stMnMsgReplaceDeliverMsg;

MN_MSG_CLOSE_SMS_CAPABILITY_MSG_STRU    f_stMnMsgCloseSmsCapabilityMsg;

extern VOS_VOID NAS_MM_CsSimValid(VOS_BOOL *pbCsSimValid);
extern VOS_VOID NAS_MM_CsCellBar(VOS_BOOL *pbCsCellBar);


/*lint -save -e958 */


VOS_VOID MN_MSG_DeliverMsgNotSupport(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_BOOL                            *pbSupportFlag,
    MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
)
{
    VOS_UINT32                          ulLoop;
    const MN_MSG_DCS_CODE_STRU         *pstDcs;
    const MN_MSG_USER_DATA_STRU        *pstUserData;

    *penTpCause     = MN_MSG_TP_CAUSE_UNSPECIFIED_ERR;
    *pbSupportFlag  = VOS_TRUE;

    /* 判断是否启用短信丢弃特性，丢弃应用或UE侧不支持的短信 */
    if (MN_MSG_NVIM_ITEM_INACTIVE == f_stMnMsgDiscardDeliverMsg.ucActFlg)
    {
        return;
    }

    /* 丢弃TP-UD中包含Special SMS Message Indication IE的短信，该短信应用不支持 */
    pstUserData = &pstTsData->u.stDeliver.stUserData;
    for (ulLoop = 0; ulLoop < pstUserData->ucNumofHeaders; ulLoop++)
    {
        if (MN_MSG_UDH_SPECIAL_SM == pstUserData->astUserDataHeader[ulLoop].enHeaderID)
        {
            *pbSupportFlag = VOS_FALSE;
            return;
        }
    }

    /* 丢弃TP-DCS格式不为00XX格式的短信，该短信应用不支持 */
    pstDcs = &pstTsData->u.stDeliver.stDcs;
    if ((MN_MSG_MSG_WAITING_DISCARD == pstDcs->enMsgWaiting)
     || (MN_MSG_MSG_WAITING_STORE == pstDcs->enMsgWaiting)
     || (MN_MSG_MSG_WAITING_AUTO_DELETE == pstDcs->enMsgWaiting))
    {
        *pbSupportFlag = VOS_FALSE;
        *penTpCause = MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED;
        return;
    }

    if (MN_MSG_MSG_WAITING_NONE_1111 == pstDcs->enMsgWaiting)
    {
        *pbSupportFlag = VOS_FALSE;
        *penTpCause = MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED;
        return;
    }

    return;
}


VOS_VOID MN_MSG_MtSpecificFeatureInit(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = NV_Read(en_NV_Item_DISCARD_DELIVER_MSG_FEATURE,
                    &f_stMnMsgDiscardDeliverMsg,
                    sizeof(f_stMnMsgDiscardDeliverMsg));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_MtSpecificFeatureInit: Read en_NV_Item_Sms_MeStorageEnable Failed");
        f_stMnMsgDiscardDeliverMsg.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;
    }

    ulRet = NV_Read(en_NV_Item_REPLACE_DELIVER_MSG_FEATURE,
                    &f_stMnMsgReplaceDeliverMsg,
                    sizeof(f_stMnMsgReplaceDeliverMsg));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_MtSpecificFeatureInit: Read en_NV_Item_SMS_REPLACEMENT_FEATURE Failed");
        f_stMnMsgReplaceDeliverMsg.ucActFlg = MN_MSG_NVIM_ITEM_ACTIVE;
    }

    return;
}


VOS_VOID MN_MSG_GetReplaceFeature(VOS_UINT8 *pucActFlg)
{
    *pucActFlg = f_stMnMsgReplaceDeliverMsg.ucActFlg;
}


VOS_VOID MN_MSG_Init(VOS_VOID)
{
    MN_MSG_ReadNvimInfo();

    MN_MSG_SmInit();
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    TAF_CBA_Init();
#endif

    return;
}


VOS_VOID MN_MSG_PowerOff()
{
    MN_MSG_FinishMoProc();

    MN_MSG_DestroyMtInfo();

    MN_MSG_UpdateSendFailFlag(MN_MSG_SEND_FAIL_NO_DOMAIN);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* 初始化CBA网络信息.  这里需要初始化为BUTT值的原因是: 当再此软开机收到MMC的NET MODE IND时,
       才会向AS发送激活CBS的请求 */
    TAF_CBA_InitNetworkInfo();
#endif


    /* 停止所有正在运行的定时器 */
    MN_MSG_StopAllRunningTimer();

    /*初始化定时器相关参数*/
    MN_MSG_InitAllTimers();
}


VOS_VOID MN_MSG_CfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_MSG_SmCfgDataInit(enUsimStatus);
}

VOS_VOID MN_MSG_PrintBcdAddrStru(
    MN_MSG_BCD_ADDR_STRU                *pstAddr
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: addr len is ", pstAddr->ucBcdLen);
    MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: addr type is ", pstAddr->addrType);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_BCD_NUM_LEN; ulLoop++)
    {
        MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: ", pstAddr->aucBcdNum[ulLoop]);
    }
    return;
}


VOS_VOID MN_MSG_PrintSrvParamStru(
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{

    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS SERVICE PARAM INFO ");
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: Parameter indicate ", pstSrvParam->ucParmInd);
    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS DEST ADDRESS");
    MN_MSG_PrintBcdAddrStru(&pstSrvParam->stDestAddr);
    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS SCA ADDRESS");
    MN_MSG_PrintBcdAddrStru(&pstSrvParam->stScAddr);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucPid ", pstSrvParam->ucPid);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucDcs ", pstSrvParam->ucDcs);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucValidPeriod ", pstSrvParam->ucValidPeriod);
    return;
}


VOS_VOID MN_MSG_InitSmsServiceData(MN_MSG_CONFIG_PARM_STRU  *pstServicePara)
{
    pstServicePara->enAppMemStatus = MN_MSG_MEM_FULL_UNSET;
    pstServicePara->enCbmMemStore = MN_MSG_MEM_STORE_NONE;
    pstServicePara->enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
    pstServicePara->enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstServicePara->enRcvStaRptAct = MN_MSG_RCVMSG_ACT_STORE;
    pstServicePara->enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
}


VOS_VOID MN_MSG_CsDomainAvailable(VOS_BOOL *pbCsDomainAvailable)
{
    VOS_BOOL                            bCsSimValid;
    VOS_BOOL                            bCsCellBar;
    VOS_UINT8                           ucUeServiceDomain;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucPsOnlyCsServiceSupportFlg)
    {
        ucUeServiceDomain = MN_MMA_GetServiceDomain();
        if (TAF_MMA_SERVICE_DOMAIN_PS == ucUeServiceDomain)
        {
            *pbCsDomainAvailable = VOS_FALSE;
            return;
        }
    }


    NAS_MM_CsSimValid(&bCsSimValid);
    NAS_MM_CsCellBar(&bCsCellBar);

    if ((VOS_TRUE == bCsSimValid) && (VOS_FALSE == bCsCellBar))
    {
        *pbCsDomainAvailable = VOS_TRUE;
    }
    else
    {
        *pbCsDomainAvailable = VOS_FALSE;
        
        MN_NORM_LOG("MN_MSG_CsDomainAvailable: IS FALSE.");
        
    }

    return;
}


VOS_UINT32 MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(
    SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPE_RSP_STRU            stMoSmsRsp;

    PS_MEM_SET(&stMoSmsRsp, 0, sizeof(stMoSmsRsp));

    if (VOS_OK != (pstEnvelope->stCmdResult.ulResult))
    {
        /*短信发送失败流程*/
        stMoSmsRsp.Result = SI_STK_CTRL_NOT_ALLOW;

        NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);

        return MN_ERR_CLASS_SMS_MO_CTRL_ACTION_NOT_ALLOWED;
    }
    if (0 != pstEnvelope->stCnfData.ulRspDataLen)
    {
        /* 解析消息中的短信中心号码和目的号码重新组装TPDU包待发送 */
        (VOS_VOID)NAS_STKAPI_EnvelopeRsp_Decode(pstEnvelope->enEnvelopeType, pstEnvelope->stCnfData.ulRspDataLen, pstEnvelope->stCnfData.aucRspData, &stMoSmsRsp);

        /* 响应消息中存在RP-DA更新短信中心号码 */
        if (SI_STK_CTRL_NOT_ALLOW == stMoSmsRsp.Result)
        {

            NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


            NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

            return MN_ERR_CLASS_SMS_MO_CTRL_ACTION_NOT_ALLOWED;
        }

        if(SI_STK_CTRL_ALLOW_MODIFY == stMoSmsRsp.Result)
        {
            ulRet = MN_MSG_MoCtrlAllowedWithModification(&stMoSmsRsp.uResp.MoSmsCtrlRsp,
                                           pstMoEntity);

            if (MN_ERR_NO_ERROR != ulRet)
            {
                stMoSmsRsp.Result = SI_STK_CTRL_NOT_ALLOW;

                NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


                NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

                return ulRet;
            }

            MN_MSG_CreateMoInfo(pstMoEntity);
        }

    }
    else
    {
        stMoSmsRsp.Result = SI_STK_CTRL_ALLOW_NOMODIFY;
    }


    NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


    NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

    /* 发送短信到SMS层 */
    ulRet = MN_MSG_SendSmsRpDataReq(pstMoEntity->enSendDomain,
                                    pstMoEntity->aucRpDataInfo,
                                    pstMoEntity->ucRpDataLen,
                                    pstMoEntity->enMsgSignallingType);

    if (VOS_ERR == ulRet)
    {
        return MN_ERR_SEND_MSG_ERROR;
    }

    return MN_ERR_NO_ERROR;
}



VOS_VOID MN_MSG_GetCloseSMSFeature(VOS_UINT8 *pucActFlg)
{
    *pucActFlg = f_stMnMsgCloseSmsCapabilityMsg.ucActFlg;
}


VOS_VOID MN_MSG_CloseSmsCapabilityFeatureInit(VOS_VOID)
{
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLength;

    NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU                  stCloseSmsCapabilityCfg;

    PS_MEM_SET(&stCloseSmsCapabilityCfg, 0, sizeof(NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU));

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Close_SMS_Capability_Config, &ulLength);

    if (ulLength > sizeof(stCloseSmsCapabilityCfg))
    {
        MN_ERR_LOG("MN_MSG_CloseSmsCapabilityFeatureInit():WARNING: en_NV_Item_Close_SMS_Capability_Config length Error");
        return;
    }

    ulRet = NV_Read(en_NV_Item_Close_SMS_Capability_Config,
                   &stCloseSmsCapabilityCfg,
                    ulLength);

    f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = stCloseSmsCapabilityCfg.ucActFlg;

    /* 读取关闭短信定制NV失败,默认不关闭短信功能 */
    if (NV_OK != ulRet)
    {
        f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;

        MN_ERR_LOG("MN_MSG_CloseSmsCapabilityFeatureInit: Read en_NV_Item_CLOSE_SMS_Capability_Config Failed");
    }

    return;
}



VOS_VOID MN_MSG_SetCloseSMSFeature(VOS_UINT8 ucActFlg)
{
    f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = ucActFlg;
}



VOS_VOID MN_MSG_GetMtCustomizeInfo(MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU       stMtCustomize;


    PS_MEM_SET(&stMtCustomize, 0x00, sizeof(stMtCustomize));

    *penMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;

    ulRet = NV_Read(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                    &stMtCustomize,
                    sizeof(stMtCustomize));
    if (NV_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_GetMtCustomizeInfo: Fail to read ");
        return;
    }

    if (MN_MSG_NVIM_ITEM_ACTIVE == stMtCustomize.ucActFlag)
    {
        *penMtCustomize = stMtCustomize.enMtCustomize;
    }

    return;
}


VOS_VOID MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;
    
    PS_MEM_SET(&stSmssInfo, 0, sizeof(MN_MSG_SMSS_INFO_STRU));

    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_UpdateMemExceedFlag: fail to MN_MSG_ReadSmssInfo. ");
        return;
    }

    if (enMemCapExcNotFlag != stSmssInfo.enMemCapExcNotFlag)
    {
        stSmssInfo.enMemCapExcNotFlag = enMemCapExcNotFlag;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }

    return;
}



VOS_VOID MN_MSG_SetTpRd(MN_MSG_MO_ENTITY_STRU *pstMoEntity)
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           ulRpOaLength;
    VOS_UINT8                           ulRpDaLength;

    /* 获取TP-RD的位置 */
    ulPos = 0;

    /* RP层MESSGGE TYPE */
    ulPos++;

    /* RP层RP-MR */
    ulPos++;

    /* RP层RP-OA */
    ulRpOaLength = pstMoEntity->aucRpDataInfo[ulPos];
    ulPos++;
    ulPos       += ulRpOaLength;

    /* RP层RP-DA */
    ulRpDaLength = pstMoEntity->aucRpDataInfo[ulPos];
    ulPos++;
    ulPos       += ulRpDaLength;

    /* RP层RP-USERDATA length */
    ulPos++;

    MN_MSG_EncodeTpRd(VOS_TRUE, &pstMoEntity->aucRpDataInfo[ulPos]);

    return;
}


VOS_UINT32 MN_MSG_IsProtocolSendDomain(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU  stSmsSrvParam;

    ulRet = NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_IsProtocolSendDomain: Read Service Parm From Nvim Failed");
        return VOS_FALSE;
    }

    if (MN_MSG_MO_DOMAIN_CUSTOMIZE_PROTOCOL == (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_MO_DOMAIN_PROTOCOL_OFFSET])
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_VOID TAF_MSG_RcvMmaCsServiceChangeNotify(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSG_CS_SERVICE_IND             *pstCsServInd = VOS_NULL_PTR;
    VOS_UINT8                           ucUsimtatus;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    pstCsServInd    = (MMA_MSG_CS_SERVICE_IND*)pstMsg;
    ucUsimtatus     = TAF_MSG_GetUsimStatus();
    MN_MSG_GetUsimPowerState(&enPowerState);

    /* 卡不存在，不需要更新短信能力和USIM文件 */
    if (MN_MSG_SIM_NOT_EXIST == ucUsimtatus)
    {
        return;
    }

    if (TAF_CS_OFF == pstCsServInd->enCSState)
    {
        /* CS域能力不可用时，认为短信功能关闭 */
        MN_MSG_SetCloseSMSFeature(MN_MSG_NVIM_ITEM_ACTIVE);
    }
    else
    {
        /* CS域能力可用时，需要重新读下NV,以NV的值为准 */
        MN_MSG_CloseSmsCapabilityFeatureInit();

        /* 同步USIM文件，同步USIM文件是有顺序的，先读EF_SMS_SMSS_ID，
           收到回复后，会在MSG_ProcEfSmssGetFileRsp中给下一个文件发送读文件请求
           为了避免重复初始化，需要在上电已完成时，同步USIM文件 */
        if (MN_MSG_USIM_POWER_ON == enPowerState)
        {
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSS_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSS_ID);
            }
        }
    }
    return;

}

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID MN_MSG_FailErrRecord(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU                      stSmsMoFailEvent;
    MN_MSG_SEND_DOMAIN_ENUM_U8                              enAvailableSendDomain;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_SMS_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU);

    /* 填写短信发送失败事件信息 */
    PS_MEM_SET(&stSmsMoFailEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stSmsMoFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_SMS_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取卡状态信息 */
    NAS_MMA_OutputUsimInfo(&stSmsMoFailEvent.stUsimInfo);

    /* 获取位置信息 */
    NAS_MNTN_OutputPositionInfo(&stSmsMoFailEvent.stPositionInfo);

    MN_MSG_OutputSmsMoFailureInfo(enErrorCode, &stSmsMoFailEvent.stMoFail);

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_PS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_CS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stSmsMoFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_MSG_FailErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_SMS_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stSmsMoFailEvent,
                           sizeof(stSmsMoFailEvent));
    return;
}
#endif


VOS_VOID TAF_MSG_RcvSpmSmmaRsp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SMMA_RSP_STRU              *pstSmmaMsg  = VOS_NULL_PTR;

    pstSmmaMsg = (TAF_SPM_SMMA_RSP_STRU *)pstMsg;

    /* 如果域选择结果为BUFFER_MESSAGE或SEND_FAIL,信令类型为BUTT,丢弃不作处理 */
    if (TAF_MSG_SIGNALLING_TYPE_BUTT == pstSmmaMsg->enMsgSignallingType)
    {
        return;
    }

    /* 给SMS/IMSA发送SMMA消息 */
    (VOS_VOID)MN_MSG_SendSmma(pstSmmaMsg->clientId, pstSmmaMsg->opId, VOS_FALSE, pstSmmaMsg->enMsgSignallingType);

    return;

}

/* TAF_MSG_SendSpmSmmaInd已经移到MnMsgSendSpm.c文件中 */
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

